<शैली गुरु>
/*
 *  linux/drivers/video/fb_defio.c
 *
 *  Copyright (C) 2006 Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/list.h>

/* to support deferred IO */
#समावेश <linux/rmap.h>
#समावेश <linux/pagemap.h>

अटल काष्ठा page *fb_deferred_io_page(काष्ठा fb_info *info, अचिन्हित दीर्घ offs)
अणु
	व्योम *screen_base = (व्योम __क्रमce *) info->screen_base;
	काष्ठा page *page;

	अगर (is_vदो_स्मृति_addr(screen_base + offs))
		page = vदो_स्मृति_to_page(screen_base + offs);
	अन्यथा
		page = pfn_to_page((info->fix.smem_start + offs) >> PAGE_SHIFT);

	वापस page;
पूर्ण

/* this is to find and वापस the vदो_स्मृति-ed fb pages */
अटल vm_fault_t fb_deferred_io_fault(काष्ठा vm_fault *vmf)
अणु
	अचिन्हित दीर्घ offset;
	काष्ठा page *page;
	काष्ठा fb_info *info = vmf->vma->vm_निजी_data;

	offset = vmf->pgoff << PAGE_SHIFT;
	अगर (offset >= info->fix.smem_len)
		वापस VM_FAULT_SIGBUS;

	page = fb_deferred_io_page(info, offset);
	अगर (!page)
		वापस VM_FAULT_SIGBUS;

	get_page(page);

	अगर (vmf->vma->vm_file)
		page->mapping = vmf->vma->vm_file->f_mapping;
	अन्यथा
		prपूर्णांकk(KERN_ERR "no mapping available\n");

	BUG_ON(!page->mapping);
	page->index = vmf->pgoff;

	vmf->page = page;
	वापस 0;
पूर्ण

पूर्णांक fb_deferred_io_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा fb_info *info = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक err = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (err)
		वापस err;

	/* Skip अगर deferred io is compiled-in but disabled on this fbdev */
	अगर (!info->fbdefio)
		वापस 0;

	inode_lock(inode);
	/* Kill off the delayed work */
	cancel_delayed_work_sync(&info->deferred_work);

	/* Run it immediately */
	schedule_delayed_work(&info->deferred_work, 0);
	inode_unlock(inode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fb_deferred_io_fsync);

/* vm_ops->page_mkग_लिखो handler */
अटल vm_fault_t fb_deferred_io_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा fb_info *info = vmf->vma->vm_निजी_data;
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;
	काष्ठा page *cur;

	/* this is a callback we get when userspace first tries to
	ग_लिखो to the page. we schedule a workqueue. that workqueue
	will eventually mkclean the touched pages and execute the
	deferred framebuffer IO. then अगर userspace touches a page
	again, we repeat the same scheme */

	file_update_समय(vmf->vma->vm_file);

	/* protect against the workqueue changing the page list */
	mutex_lock(&fbdefio->lock);

	/* first ग_लिखो in this cycle, notअगरy the driver */
	अगर (fbdefio->first_io && list_empty(&fbdefio->pagelist))
		fbdefio->first_io(info);

	/*
	 * We want the page to reमुख्य locked from ->page_mkग_लिखो until
	 * the PTE is marked dirty to aव्योम page_mkclean() being called
	 * beक्रमe the PTE is updated, which would leave the page ignored
	 * by defio.
	 * Do this by locking the page here and inक्रमming the caller
	 * about it with VM_FAULT_LOCKED.
	 */
	lock_page(page);

	/* we loop through the pagelist beक्रमe adding in order
	to keep the pagelist sorted */
	list_क्रम_each_entry(cur, &fbdefio->pagelist, lru) अणु
		/* this check is to catch the हाल where a new
		process could start writing to the same page
		through a new pte. this new access can cause the
		mkग_लिखो even when the original ps's pte is marked
		writable */
		अगर (unlikely(cur == page))
			जाओ page_alपढ़ोy_added;
		अन्यथा अगर (cur->index > page->index)
			अवरोध;
	पूर्ण

	list_add_tail(&page->lru, &cur->lru);

page_alपढ़ोy_added:
	mutex_unlock(&fbdefio->lock);

	/* come back after delay to process the deferred IO */
	schedule_delayed_work(&info->deferred_work, fbdefio->delay);
	वापस VM_FAULT_LOCKED;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा fb_deferred_io_vm_ops = अणु
	.fault		= fb_deferred_io_fault,
	.page_mkग_लिखो	= fb_deferred_io_mkग_लिखो,
पूर्ण;

अटल पूर्णांक fb_deferred_io_set_page_dirty(काष्ठा page *page)
अणु
	अगर (!PageDirty(page))
		SetPageDirty(page);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा address_space_operations fb_deferred_io_aops = अणु
	.set_page_dirty = fb_deferred_io_set_page_dirty,
पूर्ण;

पूर्णांक fb_deferred_io_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_ops = &fb_deferred_io_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	अगर (!(info->flags & FBINFO_VIRTFB))
		vma->vm_flags |= VM_IO;
	vma->vm_निजी_data = info;
	वापस 0;
पूर्ण

/* workqueue callback */
अटल व्योम fb_deferred_io_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fb_info *info = container_of(work, काष्ठा fb_info,
						deferred_work.work);
	काष्ठा list_head *node, *next;
	काष्ठा page *cur;
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;

	/* here we mkclean the pages, then करो all deferred IO */
	mutex_lock(&fbdefio->lock);
	list_क्रम_each_entry(cur, &fbdefio->pagelist, lru) अणु
		lock_page(cur);
		page_mkclean(cur);
		unlock_page(cur);
	पूर्ण

	/* driver's callback with pagelist */
	fbdefio->deferred_io(info, &fbdefio->pagelist);

	/* clear the list */
	list_क्रम_each_safe(node, next, &fbdefio->pagelist) अणु
		list_del(node);
	पूर्ण
	mutex_unlock(&fbdefio->lock);
पूर्ण

व्योम fb_deferred_io_init(काष्ठा fb_info *info)
अणु
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;

	BUG_ON(!fbdefio);
	mutex_init(&fbdefio->lock);
	INIT_DELAYED_WORK(&info->deferred_work, fb_deferred_io_work);
	INIT_LIST_HEAD(&fbdefio->pagelist);
	अगर (fbdefio->delay == 0) /* set a शेष of 1 s */
		fbdefio->delay = HZ;
पूर्ण
EXPORT_SYMBOL_GPL(fb_deferred_io_init);

व्योम fb_deferred_io_खोलो(काष्ठा fb_info *info,
			 काष्ठा inode *inode,
			 काष्ठा file *file)
अणु
	file->f_mapping->a_ops = &fb_deferred_io_aops;
पूर्ण
EXPORT_SYMBOL_GPL(fb_deferred_io_खोलो);

व्योम fb_deferred_io_cleanup(काष्ठा fb_info *info)
अणु
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;
	काष्ठा page *page;
	पूर्णांक i;

	BUG_ON(!fbdefio);
	cancel_delayed_work_sync(&info->deferred_work);

	/* clear out the mapping that we setup */
	क्रम (i = 0 ; i < info->fix.smem_len; i += PAGE_SIZE) अणु
		page = fb_deferred_io_page(info, i);
		page->mapping = शून्य;
	पूर्ण

	mutex_destroy(&fbdefio->lock);
पूर्ण
EXPORT_SYMBOL_GPL(fb_deferred_io_cleanup);
