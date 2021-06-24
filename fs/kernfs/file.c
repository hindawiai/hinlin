<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/kernfs/file.c - kernfs file implementation
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007, 2013 Tejun Heo <tj@kernel.org>
 */

#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/uपन.स>

#समावेश "kernfs-internal.h"

/*
 * There's one kernfs_खोलो_file क्रम each खोलो file and one kernfs_खोलो_node
 * क्रम each kernfs_node with one or more खोलो files.
 *
 * kernfs_node->attr.खोलो poपूर्णांकs to kernfs_खोलो_node.  attr.खोलो is
 * रक्षित by kernfs_खोलो_node_lock.
 *
 * filp->निजी_data poपूर्णांकs to seq_file whose ->निजी poपूर्णांकs to
 * kernfs_खोलो_file.  kernfs_खोलो_files are chained at
 * kernfs_खोलो_node->files, which is रक्षित by kernfs_खोलो_file_mutex.
 */
अटल DEFINE_SPINLOCK(kernfs_खोलो_node_lock);
अटल DEFINE_MUTEX(kernfs_खोलो_file_mutex);

काष्ठा kernfs_खोलो_node अणु
	atomic_t		refcnt;
	atomic_t		event;
	रुको_queue_head_t	poll;
	काष्ठा list_head	files; /* goes through kernfs_खोलो_file.list */
पूर्ण;

/*
 * kernfs_notअगरy() may be called from any context and bounces notअगरications
 * through a work item.  To minimize space overhead in kernfs_node, the
 * pending queue is implemented as a singly linked list of kernfs_nodes.
 * The list is terminated with the self poपूर्णांकer so that whether a
 * kernfs_node is on the list or not can be determined by testing the next
 * poपूर्णांकer क्रम शून्य.
 */
#घोषणा KERNFS_NOTIFY_EOL			((व्योम *)&kernfs_notअगरy_list)

अटल DEFINE_SPINLOCK(kernfs_notअगरy_lock);
अटल काष्ठा kernfs_node *kernfs_notअगरy_list = KERNFS_NOTIFY_EOL;

अटल काष्ठा kernfs_खोलो_file *kernfs_of(काष्ठा file *file)
अणु
	वापस ((काष्ठा seq_file *)file->निजी_data)->निजी;
पूर्ण

/*
 * Determine the kernfs_ops क्रम the given kernfs_node.  This function must
 * be called जबतक holding an active reference.
 */
अटल स्थिर काष्ठा kernfs_ops *kernfs_ops(काष्ठा kernfs_node *kn)
अणु
	अगर (kn->flags & KERNFS_LOCKDEP)
		lockdep_निश्चित_held(kn);
	वापस kn->attr.ops;
पूर्ण

/*
 * As kernfs_seq_stop() is also called after kernfs_seq_start() or
 * kernfs_seq_next() failure, it needs to distinguish whether it's stopping
 * a seq_file iteration which is fully initialized with an active reference
 * or an पातed kernfs_seq_start() due to get_active failure.  The
 * position poपूर्णांकer is the only context क्रम each seq_file iteration and
 * thus the stop condition should be encoded in it.  As the वापस value is
 * directly visible to userland, ERR_PTR(-ENODEV) is the only acceptable
 * choice to indicate get_active failure.
 *
 * Unक्रमtunately, this is complicated due to the optional custom seq_file
 * operations which may वापस ERR_PTR(-ENODEV) too.  kernfs_seq_stop()
 * can't distinguish whether ERR_PTR(-ENODEV) is from get_active failure or
 * custom seq_file operations and thus can't decide whether put_active
 * should be perक्रमmed or not only on ERR_PTR(-ENODEV).
 *
 * This is worked around by factoring out the custom seq_stop() and
 * put_active part पूर्णांकo kernfs_seq_stop_active(), skipping it from
 * kernfs_seq_stop() अगर ERR_PTR(-ENODEV) जबतक invoking it directly after
 * custom seq_file operations fail with ERR_PTR(-ENODEV) - this ensures
 * that kernfs_seq_stop_active() is skipped only after get_active failure.
 */
अटल व्योम kernfs_seq_stop_active(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा kernfs_खोलो_file *of = sf->निजी;
	स्थिर काष्ठा kernfs_ops *ops = kernfs_ops(of->kn);

	अगर (ops->seq_stop)
		ops->seq_stop(sf, v);
	kernfs_put_active(of->kn);
पूर्ण

अटल व्योम *kernfs_seq_start(काष्ठा seq_file *sf, loff_t *ppos)
अणु
	काष्ठा kernfs_खोलो_file *of = sf->निजी;
	स्थिर काष्ठा kernfs_ops *ops;

	/*
	 * @of->mutex nests outside active ref and is primarily to ensure that
	 * the ops aren't called concurrently क्रम the same खोलो file.
	 */
	mutex_lock(&of->mutex);
	अगर (!kernfs_get_active(of->kn))
		वापस ERR_PTR(-ENODEV);

	ops = kernfs_ops(of->kn);
	अगर (ops->seq_start) अणु
		व्योम *next = ops->seq_start(sf, ppos);
		/* see the comment above kernfs_seq_stop_active() */
		अगर (next == ERR_PTR(-ENODEV))
			kernfs_seq_stop_active(sf, next);
		वापस next;
	पूर्ण अन्यथा अणु
		/*
		 * The same behavior and code as single_खोलो().  Returns
		 * !शून्य अगर pos is at the beginning; otherwise, शून्य.
		 */
		वापस शून्य + !*ppos;
	पूर्ण
पूर्ण

अटल व्योम *kernfs_seq_next(काष्ठा seq_file *sf, व्योम *v, loff_t *ppos)
अणु
	काष्ठा kernfs_खोलो_file *of = sf->निजी;
	स्थिर काष्ठा kernfs_ops *ops = kernfs_ops(of->kn);

	अगर (ops->seq_next) अणु
		व्योम *next = ops->seq_next(sf, v, ppos);
		/* see the comment above kernfs_seq_stop_active() */
		अगर (next == ERR_PTR(-ENODEV))
			kernfs_seq_stop_active(sf, next);
		वापस next;
	पूर्ण अन्यथा अणु
		/*
		 * The same behavior and code as single_खोलो(), always
		 * terminate after the initial पढ़ो.
		 */
		++*ppos;
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम kernfs_seq_stop(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा kernfs_खोलो_file *of = sf->निजी;

	अगर (v != ERR_PTR(-ENODEV))
		kernfs_seq_stop_active(sf, v);
	mutex_unlock(&of->mutex);
पूर्ण

अटल पूर्णांक kernfs_seq_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा kernfs_खोलो_file *of = sf->निजी;

	of->event = atomic_पढ़ो(&of->kn->attr.खोलो->event);

	वापस of->kn->attr.ops->seq_show(sf, v);
पूर्ण

अटल स्थिर काष्ठा seq_operations kernfs_seq_ops = अणु
	.start = kernfs_seq_start,
	.next = kernfs_seq_next,
	.stop = kernfs_seq_stop,
	.show = kernfs_seq_show,
पूर्ण;

/*
 * As पढ़ोing a bin file can have side-effects, the exact offset and bytes
 * specअगरied in पढ़ो(2) call should be passed to the पढ़ो callback making
 * it dअगरficult to use seq_file.  Implement simplistic custom buffering क्रम
 * bin files.
 */
अटल sमाप_प्रकार kernfs_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा kernfs_खोलो_file *of = kernfs_of(iocb->ki_filp);
	sमाप_प्रकार len = min_t(माप_प्रकार, iov_iter_count(iter), PAGE_SIZE);
	स्थिर काष्ठा kernfs_ops *ops;
	अक्षर *buf;

	buf = of->pपुनः_स्मृति_buf;
	अगर (buf)
		mutex_lock(&of->pपुनः_स्मृति_mutex);
	अन्यथा
		buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/*
	 * @of->mutex nests outside active ref and is used both to ensure that
	 * the ops aren't called concurrently क्रम the same खोलो file.
	 */
	mutex_lock(&of->mutex);
	अगर (!kernfs_get_active(of->kn)) अणु
		len = -ENODEV;
		mutex_unlock(&of->mutex);
		जाओ out_मुक्त;
	पूर्ण

	of->event = atomic_पढ़ो(&of->kn->attr.खोलो->event);
	ops = kernfs_ops(of->kn);
	अगर (ops->पढ़ो)
		len = ops->पढ़ो(of, buf, len, iocb->ki_pos);
	अन्यथा
		len = -EINVAL;

	kernfs_put_active(of->kn);
	mutex_unlock(&of->mutex);

	अगर (len < 0)
		जाओ out_मुक्त;

	अगर (copy_to_iter(buf, len, iter) != len) अणु
		len = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	iocb->ki_pos += len;

 out_मुक्त:
	अगर (buf == of->pपुनः_स्मृति_buf)
		mutex_unlock(&of->pपुनः_स्मृति_mutex);
	अन्यथा
		kमुक्त(buf);
	वापस len;
पूर्ण

अटल sमाप_प्रकार kernfs_fop_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	अगर (kernfs_of(iocb->ki_filp)->kn->flags & KERNFS_HAS_SEQ_SHOW)
		वापस seq_पढ़ो_iter(iocb, iter);
	वापस kernfs_file_पढ़ो_iter(iocb, iter);
पूर्ण

/*
 * Copy data in from userland and pass it to the matching kernfs ग_लिखो
 * operation.
 *
 * There is no easy way क्रम us to know अगर userspace is only करोing a partial
 * ग_लिखो, so we करोn't support them. We expect the entire buffer to come on
 * the first ग_लिखो.  Hपूर्णांक: अगर you're writing a value, first पढ़ो the file,
 * modअगरy only the the value you're changing, then ग_लिखो entire buffer
 * back.
 */
अटल sमाप_प्रकार kernfs_fop_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा kernfs_खोलो_file *of = kernfs_of(iocb->ki_filp);
	sमाप_प्रकार len = iov_iter_count(iter);
	स्थिर काष्ठा kernfs_ops *ops;
	अक्षर *buf;

	अगर (of->atomic_ग_लिखो_len) अणु
		अगर (len > of->atomic_ग_लिखो_len)
			वापस -E2BIG;
	पूर्ण अन्यथा अणु
		len = min_t(माप_प्रकार, len, PAGE_SIZE);
	पूर्ण

	buf = of->pपुनः_स्मृति_buf;
	अगर (buf)
		mutex_lock(&of->pपुनः_स्मृति_mutex);
	अन्यथा
		buf = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (copy_from_iter(buf, len, iter) != len) अणु
		len = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	buf[len] = '\0';	/* guarantee string termination */

	/*
	 * @of->mutex nests outside active ref and is used both to ensure that
	 * the ops aren't called concurrently क्रम the same खोलो file.
	 */
	mutex_lock(&of->mutex);
	अगर (!kernfs_get_active(of->kn)) अणु
		mutex_unlock(&of->mutex);
		len = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	ops = kernfs_ops(of->kn);
	अगर (ops->ग_लिखो)
		len = ops->ग_लिखो(of, buf, len, iocb->ki_pos);
	अन्यथा
		len = -EINVAL;

	kernfs_put_active(of->kn);
	mutex_unlock(&of->mutex);

	अगर (len > 0)
		iocb->ki_pos += len;

out_मुक्त:
	अगर (buf == of->pपुनः_स्मृति_buf)
		mutex_unlock(&of->pपुनः_स्मृति_mutex);
	अन्यथा
		kमुक्त(buf);
	वापस len;
पूर्ण

अटल व्योम kernfs_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा kernfs_खोलो_file *of = kernfs_of(file);

	अगर (!of->vm_ops)
		वापस;

	अगर (!kernfs_get_active(of->kn))
		वापस;

	अगर (of->vm_ops->खोलो)
		of->vm_ops->खोलो(vma);

	kernfs_put_active(of->kn);
पूर्ण

अटल vm_fault_t kernfs_vma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा file *file = vmf->vma->vm_file;
	काष्ठा kernfs_खोलो_file *of = kernfs_of(file);
	vm_fault_t ret;

	अगर (!of->vm_ops)
		वापस VM_FAULT_SIGBUS;

	अगर (!kernfs_get_active(of->kn))
		वापस VM_FAULT_SIGBUS;

	ret = VM_FAULT_SIGBUS;
	अगर (of->vm_ops->fault)
		ret = of->vm_ops->fault(vmf);

	kernfs_put_active(of->kn);
	वापस ret;
पूर्ण

अटल vm_fault_t kernfs_vma_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा file *file = vmf->vma->vm_file;
	काष्ठा kernfs_खोलो_file *of = kernfs_of(file);
	vm_fault_t ret;

	अगर (!of->vm_ops)
		वापस VM_FAULT_SIGBUS;

	अगर (!kernfs_get_active(of->kn))
		वापस VM_FAULT_SIGBUS;

	ret = 0;
	अगर (of->vm_ops->page_mkग_लिखो)
		ret = of->vm_ops->page_mkग_लिखो(vmf);
	अन्यथा
		file_update_समय(file);

	kernfs_put_active(of->kn);
	वापस ret;
पूर्ण

अटल पूर्णांक kernfs_vma_access(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			     व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा kernfs_खोलो_file *of = kernfs_of(file);
	पूर्णांक ret;

	अगर (!of->vm_ops)
		वापस -EINVAL;

	अगर (!kernfs_get_active(of->kn))
		वापस -EINVAL;

	ret = -EINVAL;
	अगर (of->vm_ops->access)
		ret = of->vm_ops->access(vma, addr, buf, len, ग_लिखो);

	kernfs_put_active(of->kn);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल पूर्णांक kernfs_vma_set_policy(काष्ठा vm_area_काष्ठा *vma,
				 काष्ठा mempolicy *new)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा kernfs_खोलो_file *of = kernfs_of(file);
	पूर्णांक ret;

	अगर (!of->vm_ops)
		वापस 0;

	अगर (!kernfs_get_active(of->kn))
		वापस -EINVAL;

	ret = 0;
	अगर (of->vm_ops->set_policy)
		ret = of->vm_ops->set_policy(vma, new);

	kernfs_put_active(of->kn);
	वापस ret;
पूर्ण

अटल काष्ठा mempolicy *kernfs_vma_get_policy(काष्ठा vm_area_काष्ठा *vma,
					       अचिन्हित दीर्घ addr)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा kernfs_खोलो_file *of = kernfs_of(file);
	काष्ठा mempolicy *pol;

	अगर (!of->vm_ops)
		वापस vma->vm_policy;

	अगर (!kernfs_get_active(of->kn))
		वापस vma->vm_policy;

	pol = vma->vm_policy;
	अगर (of->vm_ops->get_policy)
		pol = of->vm_ops->get_policy(vma, addr);

	kernfs_put_active(of->kn);
	वापस pol;
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा vm_operations_काष्ठा kernfs_vm_ops = अणु
	.खोलो		= kernfs_vma_खोलो,
	.fault		= kernfs_vma_fault,
	.page_mkग_लिखो	= kernfs_vma_page_mkग_लिखो,
	.access		= kernfs_vma_access,
#अगर_घोषित CONFIG_NUMA
	.set_policy	= kernfs_vma_set_policy,
	.get_policy	= kernfs_vma_get_policy,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक kernfs_fop_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा kernfs_खोलो_file *of = kernfs_of(file);
	स्थिर काष्ठा kernfs_ops *ops;
	पूर्णांक rc;

	/*
	 * mmap path and of->mutex are prone to triggering spurious lockdep
	 * warnings and we करोn't want to add spurious locking dependency
	 * between the two.  Check whether mmap is actually implemented
	 * without grabbing @of->mutex by testing HAS_MMAP flag.  See the
	 * comment in kernfs_file_खोलो() क्रम more details.
	 */
	अगर (!(of->kn->flags & KERNFS_HAS_MMAP))
		वापस -ENODEV;

	mutex_lock(&of->mutex);

	rc = -ENODEV;
	अगर (!kernfs_get_active(of->kn))
		जाओ out_unlock;

	ops = kernfs_ops(of->kn);
	rc = ops->mmap(of, vma);
	अगर (rc)
		जाओ out_put;

	/*
	 * PowerPC's pci_mmap of legacy_mem uses shmem_zero_setup()
	 * to satisfy versions of X which crash अगर the mmap fails: that
	 * substitutes a new vm_file, and we करोn't then want bin_vm_ops.
	 */
	अगर (vma->vm_file != file)
		जाओ out_put;

	rc = -EINVAL;
	अगर (of->mmapped && of->vm_ops != vma->vm_ops)
		जाओ out_put;

	/*
	 * It is not possible to successfully wrap बंद.
	 * So error अगर someone is trying to use बंद.
	 */
	rc = -EINVAL;
	अगर (vma->vm_ops && vma->vm_ops->बंद)
		जाओ out_put;

	rc = 0;
	of->mmapped = true;
	of->vm_ops = vma->vm_ops;
	vma->vm_ops = &kernfs_vm_ops;
out_put:
	kernfs_put_active(of->kn);
out_unlock:
	mutex_unlock(&of->mutex);

	वापस rc;
पूर्ण

/**
 *	kernfs_get_खोलो_node - get or create kernfs_खोलो_node
 *	@kn: target kernfs_node
 *	@of: kernfs_खोलो_file क्रम this instance of खोलो
 *
 *	If @kn->attr.खोलो exists, increment its reference count; otherwise,
 *	create one.  @of is chained to the files list.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक kernfs_get_खोलो_node(काष्ठा kernfs_node *kn,
				काष्ठा kernfs_खोलो_file *of)
अणु
	काष्ठा kernfs_खोलो_node *on, *new_on = शून्य;

 retry:
	mutex_lock(&kernfs_खोलो_file_mutex);
	spin_lock_irq(&kernfs_खोलो_node_lock);

	अगर (!kn->attr.खोलो && new_on) अणु
		kn->attr.खोलो = new_on;
		new_on = शून्य;
	पूर्ण

	on = kn->attr.खोलो;
	अगर (on) अणु
		atomic_inc(&on->refcnt);
		list_add_tail(&of->list, &on->files);
	पूर्ण

	spin_unlock_irq(&kernfs_खोलो_node_lock);
	mutex_unlock(&kernfs_खोलो_file_mutex);

	अगर (on) अणु
		kमुक्त(new_on);
		वापस 0;
	पूर्ण

	/* not there, initialize a new one and retry */
	new_on = kदो_स्मृति(माप(*new_on), GFP_KERNEL);
	अगर (!new_on)
		वापस -ENOMEM;

	atomic_set(&new_on->refcnt, 0);
	atomic_set(&new_on->event, 1);
	init_रुकोqueue_head(&new_on->poll);
	INIT_LIST_HEAD(&new_on->files);
	जाओ retry;
पूर्ण

/**
 *	kernfs_put_खोलो_node - put kernfs_खोलो_node
 *	@kn: target kernfs_nodet
 *	@of: associated kernfs_खोलो_file
 *
 *	Put @kn->attr.खोलो and unlink @of from the files list.  If
 *	reference count reaches zero, disassociate and मुक्त it.
 *
 *	LOCKING:
 *	None.
 */
अटल व्योम kernfs_put_खोलो_node(काष्ठा kernfs_node *kn,
				 काष्ठा kernfs_खोलो_file *of)
अणु
	काष्ठा kernfs_खोलो_node *on = kn->attr.खोलो;
	अचिन्हित दीर्घ flags;

	mutex_lock(&kernfs_खोलो_file_mutex);
	spin_lock_irqsave(&kernfs_खोलो_node_lock, flags);

	अगर (of)
		list_del(&of->list);

	अगर (atomic_dec_and_test(&on->refcnt))
		kn->attr.खोलो = शून्य;
	अन्यथा
		on = शून्य;

	spin_unlock_irqrestore(&kernfs_खोलो_node_lock, flags);
	mutex_unlock(&kernfs_खोलो_file_mutex);

	kमुक्त(on);
पूर्ण

अटल पूर्णांक kernfs_fop_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा kernfs_node *kn = inode->i_निजी;
	काष्ठा kernfs_root *root = kernfs_root(kn);
	स्थिर काष्ठा kernfs_ops *ops;
	काष्ठा kernfs_खोलो_file *of;
	bool has_पढ़ो, has_ग_लिखो, has_mmap;
	पूर्णांक error = -EACCES;

	अगर (!kernfs_get_active(kn))
		वापस -ENODEV;

	ops = kernfs_ops(kn);

	has_पढ़ो = ops->seq_show || ops->पढ़ो || ops->mmap;
	has_ग_लिखो = ops->ग_लिखो || ops->mmap;
	has_mmap = ops->mmap;

	/* see the flag definition क्रम details */
	अगर (root->flags & KERNFS_ROOT_EXTRA_OPEN_PERM_CHECK) अणु
		अगर ((file->f_mode & FMODE_WRITE) &&
		    (!(inode->i_mode & S_IWUGO) || !has_ग_लिखो))
			जाओ err_out;

		अगर ((file->f_mode & FMODE_READ) &&
		    (!(inode->i_mode & S_IRUGO) || !has_पढ़ो))
			जाओ err_out;
	पूर्ण

	/* allocate a kernfs_खोलो_file क्रम the file */
	error = -ENOMEM;
	of = kzalloc(माप(काष्ठा kernfs_खोलो_file), GFP_KERNEL);
	अगर (!of)
		जाओ err_out;

	/*
	 * The following is करोne to give a dअगरferent lockdep key to
	 * @of->mutex क्रम files which implement mmap.  This is a rather
	 * crude way to aव्योम false positive lockdep warning around
	 * mm->mmap_lock - mmap nests @of->mutex under mm->mmap_lock and
	 * पढ़ोing /sys/block/sda/trace/act_mask grअसल sr_mutex, under
	 * which mm->mmap_lock nests, जबतक holding @of->mutex.  As each
	 * खोलो file has a separate mutex, it's okay as long as those don't
	 * happen on the same file.  At this poपूर्णांक, we can't easily give
	 * each file a separate locking class.  Let's dअगरferentiate on
	 * whether the file has mmap or not क्रम now.
	 *
	 * Both paths of the branch look the same.  They're supposed to
	 * look that way and give @of->mutex dअगरferent अटल lockdep keys.
	 */
	अगर (has_mmap)
		mutex_init(&of->mutex);
	अन्यथा
		mutex_init(&of->mutex);

	of->kn = kn;
	of->file = file;

	/*
	 * Write path needs to atomic_ग_लिखो_len outside active reference.
	 * Cache it in खोलो_file.  See kernfs_fop_ग_लिखो_iter() क्रम details.
	 */
	of->atomic_ग_लिखो_len = ops->atomic_ग_लिखो_len;

	error = -EINVAL;
	/*
	 * ->seq_show is incompatible with ->pपुनः_स्मृति,
	 * as seq_पढ़ो करोes its own allocation.
	 * ->पढ़ो must be used instead.
	 */
	अगर (ops->pपुनः_स्मृति && ops->seq_show)
		जाओ err_मुक्त;
	अगर (ops->pपुनः_स्मृति) अणु
		पूर्णांक len = of->atomic_ग_लिखो_len ?: PAGE_SIZE;
		of->pपुनः_स्मृति_buf = kदो_स्मृति(len + 1, GFP_KERNEL);
		error = -ENOMEM;
		अगर (!of->pपुनः_स्मृति_buf)
			जाओ err_मुक्त;
		mutex_init(&of->pपुनः_स्मृति_mutex);
	पूर्ण

	/*
	 * Always instantiate seq_file even अगर पढ़ो access करोesn't use
	 * seq_file or is not requested.  This unअगरies निजी data access
	 * and पढ़ोable regular files are the vast majority anyway.
	 */
	अगर (ops->seq_show)
		error = seq_खोलो(file, &kernfs_seq_ops);
	अन्यथा
		error = seq_खोलो(file, शून्य);
	अगर (error)
		जाओ err_मुक्त;

	of->seq_file = file->निजी_data;
	of->seq_file->निजी = of;

	/* seq_file clears PWRITE unconditionally, restore it अगर WRITE */
	अगर (file->f_mode & FMODE_WRITE)
		file->f_mode |= FMODE_PWRITE;

	/* make sure we have खोलो node काष्ठा */
	error = kernfs_get_खोलो_node(kn, of);
	अगर (error)
		जाओ err_seq_release;

	अगर (ops->खोलो) अणु
		/* nobody has access to @of yet, skip @of->mutex */
		error = ops->खोलो(of);
		अगर (error)
			जाओ err_put_node;
	पूर्ण

	/* खोलो succeeded, put active references */
	kernfs_put_active(kn);
	वापस 0;

err_put_node:
	kernfs_put_खोलो_node(kn, of);
err_seq_release:
	seq_release(inode, file);
err_मुक्त:
	kमुक्त(of->pपुनः_स्मृति_buf);
	kमुक्त(of);
err_out:
	kernfs_put_active(kn);
	वापस error;
पूर्ण

/* used from release/drain to ensure that ->release() is called exactly once */
अटल व्योम kernfs_release_file(काष्ठा kernfs_node *kn,
				काष्ठा kernfs_खोलो_file *of)
अणु
	/*
	 * @of is guaranteed to have no other file operations in flight and
	 * we just want to synchronize release and drain paths.
	 * @kernfs_खोलो_file_mutex is enough.  @of->mutex can't be used
	 * here because drain path may be called from places which can
	 * cause circular dependency.
	 */
	lockdep_निश्चित_held(&kernfs_खोलो_file_mutex);

	अगर (!of->released) अणु
		/*
		 * A file is never detached without being released and we
		 * need to be able to release files which are deactivated
		 * and being drained.  Don't use kernfs_ops().
		 */
		kn->attr.ops->release(of);
		of->released = true;
	पूर्ण
पूर्ण

अटल पूर्णांक kernfs_fop_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kernfs_node *kn = inode->i_निजी;
	काष्ठा kernfs_खोलो_file *of = kernfs_of(filp);

	अगर (kn->flags & KERNFS_HAS_RELEASE) अणु
		mutex_lock(&kernfs_खोलो_file_mutex);
		kernfs_release_file(kn, of);
		mutex_unlock(&kernfs_खोलो_file_mutex);
	पूर्ण

	kernfs_put_खोलो_node(kn, of);
	seq_release(inode, filp);
	kमुक्त(of->pपुनः_स्मृति_buf);
	kमुक्त(of);

	वापस 0;
पूर्ण

व्योम kernfs_drain_खोलो_files(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kernfs_खोलो_node *on;
	काष्ठा kernfs_खोलो_file *of;

	अगर (!(kn->flags & (KERNFS_HAS_MMAP | KERNFS_HAS_RELEASE)))
		वापस;

	spin_lock_irq(&kernfs_खोलो_node_lock);
	on = kn->attr.खोलो;
	अगर (on)
		atomic_inc(&on->refcnt);
	spin_unlock_irq(&kernfs_खोलो_node_lock);
	अगर (!on)
		वापस;

	mutex_lock(&kernfs_खोलो_file_mutex);

	list_क्रम_each_entry(of, &on->files, list) अणु
		काष्ठा inode *inode = file_inode(of->file);

		अगर (kn->flags & KERNFS_HAS_MMAP)
			unmap_mapping_range(inode->i_mapping, 0, 0, 1);

		अगर (kn->flags & KERNFS_HAS_RELEASE)
			kernfs_release_file(kn, of);
	पूर्ण

	mutex_unlock(&kernfs_खोलो_file_mutex);

	kernfs_put_खोलो_node(kn, शून्य);
पूर्ण

/*
 * Kernfs attribute files are pollable.  The idea is that you पढ़ो
 * the content and then you use 'poll' or 'select' to रुको क्रम
 * the content to change.  When the content changes (assuming the
 * manager क्रम the kobject supports notअगरication), poll will
 * वापस EPOLLERR|EPOLLPRI, and select will वापस the fd whether
 * it is रुकोing क्रम पढ़ो, ग_लिखो, or exceptions.
 * Once poll/select indicates that the value has changed, you
 * need to बंद and re-खोलो the file, or seek to 0 and पढ़ो again.
 * Reminder: this only works क्रम attributes which actively support
 * it, and it is not possible to test an attribute from userspace
 * to see अगर it supports poll (Neither 'poll' nor 'select' वापस
 * an appropriate error code).  When in करोubt, set a suitable समयout value.
 */
__poll_t kernfs_generic_poll(काष्ठा kernfs_खोलो_file *of, poll_table *रुको)
अणु
	काष्ठा kernfs_node *kn = kernfs_dentry_node(of->file->f_path.dentry);
	काष्ठा kernfs_खोलो_node *on = kn->attr.खोलो;

	poll_रुको(of->file, &on->poll, रुको);

	अगर (of->event != atomic_पढ़ो(&on->event))
		वापस DEFAULT_POLLMASK|EPOLLERR|EPOLLPRI;

	वापस DEFAULT_POLLMASK;
पूर्ण

अटल __poll_t kernfs_fop_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा kernfs_खोलो_file *of = kernfs_of(filp);
	काष्ठा kernfs_node *kn = kernfs_dentry_node(filp->f_path.dentry);
	__poll_t ret;

	अगर (!kernfs_get_active(kn))
		वापस DEFAULT_POLLMASK|EPOLLERR|EPOLLPRI;

	अगर (kn->attr.ops->poll)
		ret = kn->attr.ops->poll(of, रुको);
	अन्यथा
		ret = kernfs_generic_poll(of, रुको);

	kernfs_put_active(kn);
	वापस ret;
पूर्ण

अटल व्योम kernfs_notअगरy_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kernfs_node *kn;
	काष्ठा kernfs_super_info *info;
repeat:
	/* pop one off the notअगरy_list */
	spin_lock_irq(&kernfs_notअगरy_lock);
	kn = kernfs_notअगरy_list;
	अगर (kn == KERNFS_NOTIFY_EOL) अणु
		spin_unlock_irq(&kernfs_notअगरy_lock);
		वापस;
	पूर्ण
	kernfs_notअगरy_list = kn->attr.notअगरy_next;
	kn->attr.notअगरy_next = शून्य;
	spin_unlock_irq(&kernfs_notअगरy_lock);

	/* kick fsnotअगरy */
	mutex_lock(&kernfs_mutex);

	list_क्रम_each_entry(info, &kernfs_root(kn)->supers, node) अणु
		काष्ठा kernfs_node *parent;
		काष्ठा inode *p_inode = शून्य;
		काष्ठा inode *inode;
		काष्ठा qstr name;

		/*
		 * We want fsnotअगरy_modअगरy() on @kn but as the
		 * modअगरications aren't originating from userland don't
		 * have the matching @file available.  Look up the inodes
		 * and generate the events manually.
		 */
		inode = ilookup(info->sb, kernfs_ino(kn));
		अगर (!inode)
			जारी;

		name = (काष्ठा qstr)QSTR_INIT(kn->name, म_माप(kn->name));
		parent = kernfs_get_parent(kn);
		अगर (parent) अणु
			p_inode = ilookup(info->sb, kernfs_ino(parent));
			अगर (p_inode) अणु
				fsnotअगरy(FS_MODIFY | FS_EVENT_ON_CHILD,
					 inode, FSNOTIFY_EVENT_INODE,
					 p_inode, &name, inode, 0);
				iput(p_inode);
			पूर्ण

			kernfs_put(parent);
		पूर्ण

		अगर (!p_inode)
			fsnotअगरy_inode(inode, FS_MODIFY);

		iput(inode);
	पूर्ण

	mutex_unlock(&kernfs_mutex);
	kernfs_put(kn);
	जाओ repeat;
पूर्ण

/**
 * kernfs_notअगरy - notअगरy a kernfs file
 * @kn: file to notअगरy
 *
 * Notअगरy @kn such that poll(2) on @kn wakes up.  Maybe be called from any
 * context.
 */
व्योम kernfs_notअगरy(काष्ठा kernfs_node *kn)
अणु
	अटल DECLARE_WORK(kernfs_notअगरy_work, kernfs_notअगरy_workfn);
	अचिन्हित दीर्घ flags;
	काष्ठा kernfs_खोलो_node *on;

	अगर (WARN_ON(kernfs_type(kn) != KERNFS_खाता))
		वापस;

	/* kick poll immediately */
	spin_lock_irqsave(&kernfs_खोलो_node_lock, flags);
	on = kn->attr.खोलो;
	अगर (on) अणु
		atomic_inc(&on->event);
		wake_up_पूर्णांकerruptible(&on->poll);
	पूर्ण
	spin_unlock_irqrestore(&kernfs_खोलो_node_lock, flags);

	/* schedule work to kick fsnotअगरy */
	spin_lock_irqsave(&kernfs_notअगरy_lock, flags);
	अगर (!kn->attr.notअगरy_next) अणु
		kernfs_get(kn);
		kn->attr.notअगरy_next = kernfs_notअगरy_list;
		kernfs_notअगरy_list = kn;
		schedule_work(&kernfs_notअगरy_work);
	पूर्ण
	spin_unlock_irqrestore(&kernfs_notअगरy_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(kernfs_notअगरy);

स्थिर काष्ठा file_operations kernfs_file_fops = अणु
	.पढ़ो_iter	= kernfs_fop_पढ़ो_iter,
	.ग_लिखो_iter	= kernfs_fop_ग_लिखो_iter,
	.llseek		= generic_file_llseek,
	.mmap		= kernfs_fop_mmap,
	.खोलो		= kernfs_fop_खोलो,
	.release	= kernfs_fop_release,
	.poll		= kernfs_fop_poll,
	.fsync		= noop_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
पूर्ण;

/**
 * __kernfs_create_file - kernfs पूर्णांकernal function to create a file
 * @parent: directory to create the file in
 * @name: name of the file
 * @mode: mode of the file
 * @uid: uid of the file
 * @gid: gid of the file
 * @size: size of the file
 * @ops: kernfs operations क्रम the file
 * @priv: निजी data क्रम the file
 * @ns: optional namespace tag of the file
 * @key: lockdep key क्रम the file's active_ref, %शून्य to disable lockdep
 *
 * Returns the created node on success, ERR_PTR() value on error.
 */
काष्ठा kernfs_node *__kernfs_create_file(काष्ठा kernfs_node *parent,
					 स्थिर अक्षर *name,
					 umode_t mode, kuid_t uid, kgid_t gid,
					 loff_t size,
					 स्थिर काष्ठा kernfs_ops *ops,
					 व्योम *priv, स्थिर व्योम *ns,
					 काष्ठा lock_class_key *key)
अणु
	काष्ठा kernfs_node *kn;
	अचिन्हित flags;
	पूर्णांक rc;

	flags = KERNFS_खाता;

	kn = kernfs_new_node(parent, name, (mode & S_IALLUGO) | S_IFREG,
			     uid, gid, flags);
	अगर (!kn)
		वापस ERR_PTR(-ENOMEM);

	kn->attr.ops = ops;
	kn->attr.size = size;
	kn->ns = ns;
	kn->priv = priv;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	अगर (key) अणु
		lockdep_init_map(&kn->dep_map, "kn->active", key, 0);
		kn->flags |= KERNFS_LOCKDEP;
	पूर्ण
#पूर्ण_अगर

	/*
	 * kn->attr.ops is accesible only जबतक holding active ref.  We
	 * need to know whether some ops are implemented outside active
	 * ref.  Cache their existence in flags.
	 */
	अगर (ops->seq_show)
		kn->flags |= KERNFS_HAS_SEQ_SHOW;
	अगर (ops->mmap)
		kn->flags |= KERNFS_HAS_MMAP;
	अगर (ops->release)
		kn->flags |= KERNFS_HAS_RELEASE;

	rc = kernfs_add_one(kn);
	अगर (rc) अणु
		kernfs_put(kn);
		वापस ERR_PTR(rc);
	पूर्ण
	वापस kn;
पूर्ण
