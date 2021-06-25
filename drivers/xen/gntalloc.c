<शैली गुरु>
/******************************************************************************
 * gntalloc.c
 *
 * Device क्रम creating grant references (in user-space) that may be shared
 * with other करोमुख्यs.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * This driver exists to allow userspace programs in Linux to allocate kernel
 * memory that will later be shared with another करोमुख्य.  Without this device,
 * Linux userspace programs cannot create grant references.
 *
 * How this stuff works:
 *   X -> granting a page to Y
 *   Y -> mapping the grant from X
 *
 *   1. X uses the gntalloc device to allocate a page of kernel memory, P.
 *   2. X creates an entry in the grant table that says करोmid(Y) can access P.
 *      This is करोne without a hypercall unless the grant table needs expansion.
 *   3. X gives the grant reference identअगरier, GREF, to Y.
 *   4. Y maps the page, either directly पूर्णांकo kernel memory क्रम use in a backend
 *      driver, or via a the gntdev device to map पूर्णांकo the address space of an
 *      application running in Y. This is the first poपूर्णांक at which Xen करोes any
 *      tracking of the page.
 *   5. A program in X mmap()s a segment of the gntalloc device that corresponds
 *      to the shared page, and can now communicate with Y over the shared page.
 *
 *
 * NOTE TO USERSPACE LIBRARIES:
 *   The grant allocation and mmap()ing are, naturally, two separate operations.
 *   You set up the sharing by calling the create ioctl() and then the mmap().
 *   Tearकरोwn requires munmap() and either बंद() or ioctl().
 *
 * WARNING: Since Xen करोes not allow a guest to क्रमcibly end the use of a grant
 * reference, this device can be used to consume kernel memory by leaving grant
 * references mapped by another करोमुख्य when an application निकासs. Thereक्रमe,
 * there is a global limit on the number of pages that can be allocated. When
 * all references to the page are unmapped, it will be मुक्तd during the next
 * grant operation.
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/highस्मृति.स>

#समावेश <xen/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/gntभाग.स>
#समावेश <xen/events.h>

अटल पूर्णांक limit = 1024;
module_param(limit, पूर्णांक, 0644);
MODULE_PARM_DESC(limit, "Maximum number of grants that may be allocated by "
		"the gntalloc device");

अटल LIST_HEAD(gref_list);
अटल DEFINE_MUTEX(gref_mutex);
अटल पूर्णांक gref_size;

काष्ठा notअगरy_info अणु
	uपूर्णांक16_t pgoff:12;    /* Bits 0-11: Offset of the byte to clear */
	uपूर्णांक16_t flags:2;     /* Bits 12-13: Unmap notअगरication flags */
	पूर्णांक event;            /* Port (event channel) to notअगरy */
पूर्ण;

/* Metadata on a grant reference. */
काष्ठा gntalloc_gref अणु
	काष्ठा list_head next_gref;  /* list entry gref_list */
	काष्ठा list_head next_file;  /* list entry file->list, अगर खोलो */
	काष्ठा page *page;	     /* The shared page */
	uपूर्णांक64_t file_index;         /* File offset क्रम mmap() */
	अचिन्हित पूर्णांक users;          /* Use count - when zero, रुकोing on Xen */
	grant_ref_t gref_id;         /* The grant reference number */
	काष्ठा notअगरy_info notअगरy;   /* Unmap notअगरication */
पूर्ण;

काष्ठा gntalloc_file_निजी_data अणु
	काष्ठा list_head list;
	uपूर्णांक64_t index;
पूर्ण;

काष्ठा gntalloc_vma_निजी_data अणु
	काष्ठा gntalloc_gref *gref;
	पूर्णांक users;
	पूर्णांक count;
पूर्ण;

अटल व्योम __del_gref(काष्ठा gntalloc_gref *gref);

अटल व्योम करो_cleanup(व्योम)
अणु
	काष्ठा gntalloc_gref *gref, *n;
	list_क्रम_each_entry_safe(gref, n, &gref_list, next_gref) अणु
		अगर (!gref->users)
			__del_gref(gref);
	पूर्ण
पूर्ण

अटल पूर्णांक add_grefs(काष्ठा ioctl_gntalloc_alloc_gref *op,
	uपूर्णांक32_t *gref_ids, काष्ठा gntalloc_file_निजी_data *priv)
अणु
	पूर्णांक i, rc, पढ़ोonly;
	LIST_HEAD(queue_gref);
	LIST_HEAD(queue_file);
	काष्ठा gntalloc_gref *gref, *next;

	पढ़ोonly = !(op->flags & GNTALLOC_FLAG_WRITABLE);
	क्रम (i = 0; i < op->count; i++) अणु
		gref = kzalloc(माप(*gref), GFP_KERNEL);
		अगर (!gref) अणु
			rc = -ENOMEM;
			जाओ unकरो;
		पूर्ण
		list_add_tail(&gref->next_gref, &queue_gref);
		list_add_tail(&gref->next_file, &queue_file);
		gref->users = 1;
		gref->file_index = op->index + i * PAGE_SIZE;
		gref->page = alloc_page(GFP_KERNEL|__GFP_ZERO);
		अगर (!gref->page) अणु
			rc = -ENOMEM;
			जाओ unकरो;
		पूर्ण

		/* Grant क्रमeign access to the page. */
		rc = gnttab_grant_क्रमeign_access(op->करोmid,
						 xen_page_to_gfn(gref->page),
						 पढ़ोonly);
		अगर (rc < 0)
			जाओ unकरो;
		gref_ids[i] = gref->gref_id = rc;
	पूर्ण

	/* Add to gref lists. */
	mutex_lock(&gref_mutex);
	list_splice_tail(&queue_gref, &gref_list);
	list_splice_tail(&queue_file, &priv->list);
	mutex_unlock(&gref_mutex);

	वापस 0;

unकरो:
	mutex_lock(&gref_mutex);
	gref_size -= (op->count - i);

	list_क्रम_each_entry_safe(gref, next, &queue_file, next_file) अणु
		list_del(&gref->next_file);
		__del_gref(gref);
	पूर्ण

	/* It's possible क्रम the target करोमुख्य to map the just-allocated grant
	 * references by blindly guessing their IDs; अगर this is करोne, then
	 * __del_gref will leave them in the queue_gref list. They need to be
	 * added to the global list so that we can मुक्त them when they are no
	 * दीर्घer referenced.
	 */
	अगर (unlikely(!list_empty(&queue_gref)))
		list_splice_tail(&queue_gref, &gref_list);
	mutex_unlock(&gref_mutex);
	वापस rc;
पूर्ण

अटल व्योम __del_gref(काष्ठा gntalloc_gref *gref)
अणु
	अगर (gref->notअगरy.flags & UNMAP_NOTIFY_CLEAR_BYTE) अणु
		uपूर्णांक8_t *पंचांगp = kmap(gref->page);
		पंचांगp[gref->notअगरy.pgoff] = 0;
		kunmap(gref->page);
	पूर्ण
	अगर (gref->notअगरy.flags & UNMAP_NOTIFY_SEND_EVENT) अणु
		notअगरy_remote_via_evtchn(gref->notअगरy.event);
		evtchn_put(gref->notअगरy.event);
	पूर्ण

	gref->notअगरy.flags = 0;

	अगर (gref->gref_id) अणु
		अगर (gnttab_query_क्रमeign_access(gref->gref_id))
			वापस;

		अगर (!gnttab_end_क्रमeign_access_ref(gref->gref_id, 0))
			वापस;

		gnttab_मुक्त_grant_reference(gref->gref_id);
	पूर्ण

	gref_size--;
	list_del(&gref->next_gref);

	अगर (gref->page)
		__मुक्त_page(gref->page);

	kमुक्त(gref);
पूर्ण

/* finds contiguous grant references in a file, वापसs the first */
अटल काष्ठा gntalloc_gref *find_grefs(काष्ठा gntalloc_file_निजी_data *priv,
		uपूर्णांक64_t index, uपूर्णांक32_t count)
अणु
	काष्ठा gntalloc_gref *rv = शून्य, *gref;
	list_क्रम_each_entry(gref, &priv->list, next_file) अणु
		अगर (gref->file_index == index && !rv)
			rv = gref;
		अगर (rv) अणु
			अगर (gref->file_index != index)
				वापस शून्य;
			index += PAGE_SIZE;
			count--;
			अगर (count == 0)
				वापस rv;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * -------------------------------------
 *  File operations.
 * -------------------------------------
 */
अटल पूर्णांक gntalloc_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा gntalloc_file_निजी_data *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		जाओ out_nomem;
	INIT_LIST_HEAD(&priv->list);

	filp->निजी_data = priv;

	pr_debug("%s: priv %p\n", __func__, priv);

	वापस 0;

out_nomem:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक gntalloc_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा gntalloc_file_निजी_data *priv = filp->निजी_data;
	काष्ठा gntalloc_gref *gref;

	pr_debug("%s: priv %p\n", __func__, priv);

	mutex_lock(&gref_mutex);
	जबतक (!list_empty(&priv->list)) अणु
		gref = list_entry(priv->list.next,
			काष्ठा gntalloc_gref, next_file);
		list_del(&gref->next_file);
		gref->users--;
		अगर (gref->users == 0)
			__del_gref(gref);
	पूर्ण
	kमुक्त(priv);
	mutex_unlock(&gref_mutex);

	वापस 0;
पूर्ण

अटल दीर्घ gntalloc_ioctl_alloc(काष्ठा gntalloc_file_निजी_data *priv,
		काष्ठा ioctl_gntalloc_alloc_gref __user *arg)
अणु
	पूर्णांक rc = 0;
	काष्ठा ioctl_gntalloc_alloc_gref op;
	uपूर्णांक32_t *gref_ids;

	pr_debug("%s: priv %p\n", __func__, priv);

	अगर (copy_from_user(&op, arg, माप(op))) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	gref_ids = kसुस्मृति(op.count, माप(gref_ids[0]), GFP_KERNEL);
	अगर (!gref_ids) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_lock(&gref_mutex);
	/* Clean up pages that were at zero (local) users but were still mapped
	 * by remote करोमुख्यs. Since those pages count towards the limit that we
	 * are about to enक्रमce, removing them here is a good idea.
	 */
	करो_cleanup();
	अगर (gref_size + op.count > limit) अणु
		mutex_unlock(&gref_mutex);
		rc = -ENOSPC;
		जाओ out_मुक्त;
	पूर्ण
	gref_size += op.count;
	op.index = priv->index;
	priv->index += op.count * PAGE_SIZE;
	mutex_unlock(&gref_mutex);

	rc = add_grefs(&op, gref_ids, priv);
	अगर (rc < 0)
		जाओ out_मुक्त;

	/* Once we finish add_grefs, it is unsafe to touch the new reference,
	 * since it is possible क्रम a concurrent ioctl to हटाओ it (by guessing
	 * its index). If the userspace application करोesn't provide valid memory
	 * to ग_लिखो the IDs to, then it will need to बंद the file in order to
	 * release - which it will करो by segfaulting when it tries to access the
	 * IDs to बंद them.
	 */
	अगर (copy_to_user(arg, &op, माप(op))) अणु
		rc = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	अगर (copy_to_user(arg->gref_ids, gref_ids,
			माप(gref_ids[0]) * op.count)) अणु
		rc = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(gref_ids);
out:
	वापस rc;
पूर्ण

अटल दीर्घ gntalloc_ioctl_dealloc(काष्ठा gntalloc_file_निजी_data *priv,
		व्योम __user *arg)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा ioctl_gntalloc_dealloc_gref op;
	काष्ठा gntalloc_gref *gref, *n;

	pr_debug("%s: priv %p\n", __func__, priv);

	अगर (copy_from_user(&op, arg, माप(op))) अणु
		rc = -EFAULT;
		जाओ dealloc_grant_out;
	पूर्ण

	mutex_lock(&gref_mutex);
	gref = find_grefs(priv, op.index, op.count);
	अगर (gref) अणु
		/* Remove from the file list only, and decrease reference count.
		 * The later call to करो_cleanup() will हटाओ from gref_list and
		 * मुक्त the memory अगर the pages aren't mapped anywhere.
		 */
		क्रम (i = 0; i < op.count; i++) अणु
			n = list_entry(gref->next_file.next,
				काष्ठा gntalloc_gref, next_file);
			list_del(&gref->next_file);
			gref->users--;
			gref = n;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
	पूर्ण

	करो_cleanup();

	mutex_unlock(&gref_mutex);
dealloc_grant_out:
	वापस rc;
पूर्ण

अटल दीर्घ gntalloc_ioctl_unmap_notअगरy(काष्ठा gntalloc_file_निजी_data *priv,
		व्योम __user *arg)
अणु
	काष्ठा ioctl_gntalloc_unmap_notअगरy op;
	काष्ठा gntalloc_gref *gref;
	uपूर्णांक64_t index;
	पूर्णांक pgoff;
	पूर्णांक rc;

	अगर (copy_from_user(&op, arg, माप(op)))
		वापस -EFAULT;

	index = op.index & ~(PAGE_SIZE - 1);
	pgoff = op.index & (PAGE_SIZE - 1);

	mutex_lock(&gref_mutex);

	gref = find_grefs(priv, index, 1);
	अगर (!gref) अणु
		rc = -ENOENT;
		जाओ unlock_out;
	पूर्ण

	अगर (op.action & ~(UNMAP_NOTIFY_CLEAR_BYTE|UNMAP_NOTIFY_SEND_EVENT)) अणु
		rc = -EINVAL;
		जाओ unlock_out;
	पूर्ण

	/* We need to grab a reference to the event channel we are going to use
	 * to send the notअगरy beक्रमe releasing the reference we may alपढ़ोy have
	 * (अगर someone has called this ioctl twice). This is required so that
	 * it is possible to change the clear_byte part of the notअगरication
	 * without disturbing the event channel part, which may now be the last
	 * reference to that event channel.
	 */
	अगर (op.action & UNMAP_NOTIFY_SEND_EVENT) अणु
		अगर (evtchn_get(op.event_channel_port)) अणु
			rc = -EINVAL;
			जाओ unlock_out;
		पूर्ण
	पूर्ण

	अगर (gref->notअगरy.flags & UNMAP_NOTIFY_SEND_EVENT)
		evtchn_put(gref->notअगरy.event);

	gref->notअगरy.flags = op.action;
	gref->notअगरy.pgoff = pgoff;
	gref->notअगरy.event = op.event_channel_port;
	rc = 0;

 unlock_out:
	mutex_unlock(&gref_mutex);
	वापस rc;
पूर्ण

अटल दीर्घ gntalloc_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	काष्ठा gntalloc_file_निजी_data *priv = filp->निजी_data;

	चयन (cmd) अणु
	हाल IOCTL_GNTALLOC_ALLOC_GREF:
		वापस gntalloc_ioctl_alloc(priv, (व्योम __user *)arg);

	हाल IOCTL_GNTALLOC_DEALLOC_GREF:
		वापस gntalloc_ioctl_dealloc(priv, (व्योम __user *)arg);

	हाल IOCTL_GNTALLOC_SET_UNMAP_NOTIFY:
		वापस gntalloc_ioctl_unmap_notअगरy(priv, (व्योम __user *)arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gntalloc_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gntalloc_vma_निजी_data *priv = vma->vm_निजी_data;

	अगर (!priv)
		वापस;

	mutex_lock(&gref_mutex);
	priv->users++;
	mutex_unlock(&gref_mutex);
पूर्ण

अटल व्योम gntalloc_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gntalloc_vma_निजी_data *priv = vma->vm_निजी_data;
	काष्ठा gntalloc_gref *gref, *next;
	पूर्णांक i;

	अगर (!priv)
		वापस;

	mutex_lock(&gref_mutex);
	priv->users--;
	अगर (priv->users == 0) अणु
		gref = priv->gref;
		क्रम (i = 0; i < priv->count; i++) अणु
			gref->users--;
			next = list_entry(gref->next_gref.next,
					  काष्ठा gntalloc_gref, next_gref);
			अगर (gref->users == 0)
				__del_gref(gref);
			gref = next;
		पूर्ण
		kमुक्त(priv);
	पूर्ण
	mutex_unlock(&gref_mutex);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा gntalloc_vmops = अणु
	.खोलो = gntalloc_vma_खोलो,
	.बंद = gntalloc_vma_बंद,
पूर्ण;

अटल पूर्णांक gntalloc_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gntalloc_file_निजी_data *priv = filp->निजी_data;
	काष्ठा gntalloc_vma_निजी_data *vm_priv;
	काष्ठा gntalloc_gref *gref;
	पूर्णांक count = vma_pages(vma);
	पूर्णांक rv, i;

	अगर (!(vma->vm_flags & VM_SHARED)) अणु
		pr_err("%s: Mapping must be shared\n", __func__);
		वापस -EINVAL;
	पूर्ण

	vm_priv = kदो_स्मृति(माप(*vm_priv), GFP_KERNEL);
	अगर (!vm_priv)
		वापस -ENOMEM;

	mutex_lock(&gref_mutex);

	pr_debug("%s: priv %p,%p, page %lu+%d\n", __func__,
		       priv, vm_priv, vma->vm_pgoff, count);

	gref = find_grefs(priv, vma->vm_pgoff << PAGE_SHIFT, count);
	अगर (gref == शून्य) अणु
		rv = -ENOENT;
		pr_debug("%s: Could not find grant reference",
				__func__);
		kमुक्त(vm_priv);
		जाओ out_unlock;
	पूर्ण

	vm_priv->gref = gref;
	vm_priv->users = 1;
	vm_priv->count = count;

	vma->vm_निजी_data = vm_priv;

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;

	vma->vm_ops = &gntalloc_vmops;

	क्रम (i = 0; i < count; i++) अणु
		gref->users++;
		rv = vm_insert_page(vma, vma->vm_start + i * PAGE_SIZE,
				gref->page);
		अगर (rv)
			जाओ out_unlock;

		gref = list_entry(gref->next_file.next,
				काष्ठा gntalloc_gref, next_file);
	पूर्ण
	rv = 0;

out_unlock:
	mutex_unlock(&gref_mutex);
	वापस rv;
पूर्ण

अटल स्थिर काष्ठा file_operations gntalloc_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = gntalloc_खोलो,
	.release = gntalloc_release,
	.unlocked_ioctl = gntalloc_ioctl,
	.mmap = gntalloc_mmap
पूर्ण;

/*
 * -------------------------------------
 * Module creation/deकाष्ठाion.
 * -------------------------------------
 */
अटल काष्ठा miscdevice gntalloc_miscdev = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "xen/gntalloc",
	.fops	= &gntalloc_fops,
पूर्ण;

अटल पूर्णांक __init gntalloc_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	err = misc_रेजिस्टर(&gntalloc_miscdev);
	अगर (err != 0) अणु
		pr_err("Could not register misc gntalloc device\n");
		वापस err;
	पूर्ण

	pr_debug("Created grant allocation device at %d,%d\n",
			MISC_MAJOR, gntalloc_miscdev.minor);

	वापस 0;
पूर्ण

अटल व्योम __निकास gntalloc_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&gntalloc_miscdev);
पूर्ण

module_init(gntalloc_init);
module_निकास(gntalloc_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Carter Weatherly <carter.weatherly@jhuapl.edu>, "
		"Daniel De Graaf <dgdegra@tycho.nsa.gov>");
MODULE_DESCRIPTION("User-space grant reference allocator driver");
