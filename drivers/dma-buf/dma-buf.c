<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Framework क्रम buffer objects that can be shared across devices/subप्रणालीs.
 *
 * Copyright(C) 2011 Linaro Limited. All rights reserved.
 * Author: Sumit Semwal <sumit.semwal@ti.com>
 *
 * Many thanks to linaro-mm-sig list, and specially
 * Arnd Bergmann <arnd@arndb.de>, Rob Clark <rob@ti.com> and
 * Daniel Vetter <daniel@ffwll.ch> क्रम their support in creation and
 * refining of this idea.
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/export.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/poll.h>
#समावेश <linux/dma-resv.h>
#समावेश <linux/mm.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>

#समावेश <uapi/linux/dma-buf.h>
#समावेश <uapi/linux/magic.h>

अटल अंतरभूत पूर्णांक is_dma_buf_file(काष्ठा file *);

काष्ठा dma_buf_list अणु
	काष्ठा list_head head;
	काष्ठा mutex lock;
पूर्ण;

अटल काष्ठा dma_buf_list db_list;

अटल अक्षर *dmabuffs_dname(काष्ठा dentry *dentry, अक्षर *buffer, पूर्णांक buflen)
अणु
	काष्ठा dma_buf *dmabuf;
	अक्षर name[DMA_BUF_NAME_LEN];
	माप_प्रकार ret = 0;

	dmabuf = dentry->d_fsdata;
	spin_lock(&dmabuf->name_lock);
	अगर (dmabuf->name)
		ret = strlcpy(name, dmabuf->name, DMA_BUF_NAME_LEN);
	spin_unlock(&dmabuf->name_lock);

	वापस dynamic_dname(dentry, buffer, buflen, "/%s:%s",
			     dentry->d_name.name, ret > 0 ? name : "");
पूर्ण

अटल व्योम dma_buf_release(काष्ठा dentry *dentry)
अणु
	काष्ठा dma_buf *dmabuf;

	dmabuf = dentry->d_fsdata;
	अगर (unlikely(!dmabuf))
		वापस;

	BUG_ON(dmabuf->vmapping_counter);

	/*
	 * Any fences that a dma-buf poll can रुको on should be संकेतed
	 * beक्रमe releasing dma-buf. This is the responsibility of each
	 * driver that uses the reservation objects.
	 *
	 * If you hit this BUG() it means someone dropped their ref to the
	 * dma-buf जबतक still having pending operation to the buffer.
	 */
	BUG_ON(dmabuf->cb_shared.active || dmabuf->cb_excl.active);

	dmabuf->ops->release(dmabuf);

	अगर (dmabuf->resv == (काष्ठा dma_resv *)&dmabuf[1])
		dma_resv_fini(dmabuf->resv);

	module_put(dmabuf->owner);
	kमुक्त(dmabuf->name);
	kमुक्त(dmabuf);
पूर्ण

अटल पूर्णांक dma_buf_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dma_buf *dmabuf;

	अगर (!is_dma_buf_file(file))
		वापस -EINVAL;

	dmabuf = file->निजी_data;

	mutex_lock(&db_list.lock);
	list_del(&dmabuf->list_node);
	mutex_unlock(&db_list.lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dentry_operations dma_buf_dentry_ops = अणु
	.d_dname = dmabuffs_dname,
	.d_release = dma_buf_release,
पूर्ण;

अटल काष्ठा vfsmount *dma_buf_mnt;

अटल पूर्णांक dma_buf_fs_init_context(काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx;

	ctx = init_pseuकरो(fc, DMA_BUF_MAGIC);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->करोps = &dma_buf_dentry_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type dma_buf_fs_type = अणु
	.name = "dmabuf",
	.init_fs_context = dma_buf_fs_init_context,
	.समाप्त_sb = समाप्त_anon_super,
पूर्ण;

अटल पूर्णांक dma_buf_mmap_पूर्णांकernal(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा dma_buf *dmabuf;

	अगर (!is_dma_buf_file(file))
		वापस -EINVAL;

	dmabuf = file->निजी_data;

	/* check अगर buffer supports mmap */
	अगर (!dmabuf->ops->mmap)
		वापस -EINVAL;

	/* check क्रम overflowing the buffer's size */
	अगर (vma->vm_pgoff + vma_pages(vma) >
	    dmabuf->size >> PAGE_SHIFT)
		वापस -EINVAL;

	वापस dmabuf->ops->mmap(dmabuf, vma);
पूर्ण

अटल loff_t dma_buf_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा dma_buf *dmabuf;
	loff_t base;

	अगर (!is_dma_buf_file(file))
		वापस -EBADF;

	dmabuf = file->निजी_data;

	/* only support discovering the end of the buffer,
	   but also allow शुरू_से to मुख्यtain the idiomatic
	   अंत_से(0), प्रस्तुत_से(0) pattern */
	अगर (whence == अंत_से)
		base = dmabuf->size;
	अन्यथा अगर (whence == शुरू_से)
		base = 0;
	अन्यथा
		वापस -EINVAL;

	अगर (offset != 0)
		वापस -EINVAL;

	वापस base + offset;
पूर्ण

/**
 * DOC: implicit fence polling
 *
 * To support cross-device and cross-driver synchronization of buffer access
 * implicit fences (represented पूर्णांकernally in the kernel with &काष्ठा dma_fence)
 * can be attached to a &dma_buf. The glue क्रम that and a few related things are
 * provided in the &dma_resv काष्ठाure.
 *
 * Userspace can query the state of these implicitly tracked fences using poll()
 * and related प्रणाली calls:
 *
 * - Checking क्रम EPOLLIN, i.e. पढ़ो access, can be use to query the state of the
 *   most recent ग_लिखो or exclusive fence.
 *
 * - Checking क्रम EPOLLOUT, i.e. ग_लिखो access, can be used to query the state of
 *   all attached fences, shared and exclusive ones.
 *
 * Note that this only संकेतs the completion of the respective fences, i.e. the
 * DMA transfers are complete. Cache flushing and any other necessary
 * preparations beक्रमe CPU access can begin still need to happen.
 */

अटल व्योम dma_buf_poll_cb(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा dma_buf_poll_cb_t *dcb = (काष्ठा dma_buf_poll_cb_t *)cb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dcb->poll->lock, flags);
	wake_up_locked_poll(dcb->poll, dcb->active);
	dcb->active = 0;
	spin_unlock_irqrestore(&dcb->poll->lock, flags);
पूर्ण

अटल __poll_t dma_buf_poll(काष्ठा file *file, poll_table *poll)
अणु
	काष्ठा dma_buf *dmabuf;
	काष्ठा dma_resv *resv;
	काष्ठा dma_resv_list *fobj;
	काष्ठा dma_fence *fence_excl;
	__poll_t events;
	अचिन्हित shared_count, seq;

	dmabuf = file->निजी_data;
	अगर (!dmabuf || !dmabuf->resv)
		वापस EPOLLERR;

	resv = dmabuf->resv;

	poll_रुको(file, &dmabuf->poll, poll);

	events = poll_requested_events(poll) & (EPOLLIN | EPOLLOUT);
	अगर (!events)
		वापस 0;

retry:
	seq = पढ़ो_seqcount_begin(&resv->seq);
	rcu_पढ़ो_lock();

	fobj = rcu_dereference(resv->fence);
	अगर (fobj)
		shared_count = fobj->shared_count;
	अन्यथा
		shared_count = 0;
	fence_excl = rcu_dereference(resv->fence_excl);
	अगर (पढ़ो_seqcount_retry(&resv->seq, seq)) अणु
		rcu_पढ़ो_unlock();
		जाओ retry;
	पूर्ण

	अगर (fence_excl && (!(events & EPOLLOUT) || shared_count == 0)) अणु
		काष्ठा dma_buf_poll_cb_t *dcb = &dmabuf->cb_excl;
		__poll_t pevents = EPOLLIN;

		अगर (shared_count == 0)
			pevents |= EPOLLOUT;

		spin_lock_irq(&dmabuf->poll.lock);
		अगर (dcb->active) अणु
			dcb->active |= pevents;
			events &= ~pevents;
		पूर्ण अन्यथा
			dcb->active = pevents;
		spin_unlock_irq(&dmabuf->poll.lock);

		अगर (events & pevents) अणु
			अगर (!dma_fence_get_rcu(fence_excl)) अणु
				/* क्रमce a recheck */
				events &= ~pevents;
				dma_buf_poll_cb(शून्य, &dcb->cb);
			पूर्ण अन्यथा अगर (!dma_fence_add_callback(fence_excl, &dcb->cb,
							   dma_buf_poll_cb)) अणु
				events &= ~pevents;
				dma_fence_put(fence_excl);
			पूर्ण अन्यथा अणु
				/*
				 * No callback queued, wake up any additional
				 * रुकोers.
				 */
				dma_fence_put(fence_excl);
				dma_buf_poll_cb(शून्य, &dcb->cb);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((events & EPOLLOUT) && shared_count > 0) अणु
		काष्ठा dma_buf_poll_cb_t *dcb = &dmabuf->cb_shared;
		पूर्णांक i;

		/* Only queue a new callback अगर no event has fired yet */
		spin_lock_irq(&dmabuf->poll.lock);
		अगर (dcb->active)
			events &= ~EPOLLOUT;
		अन्यथा
			dcb->active = EPOLLOUT;
		spin_unlock_irq(&dmabuf->poll.lock);

		अगर (!(events & EPOLLOUT))
			जाओ out;

		क्रम (i = 0; i < shared_count; ++i) अणु
			काष्ठा dma_fence *fence = rcu_dereference(fobj->shared[i]);

			अगर (!dma_fence_get_rcu(fence)) अणु
				/*
				 * fence refcount dropped to zero, this means
				 * that fobj has been मुक्तd
				 *
				 * call dma_buf_poll_cb and क्रमce a recheck!
				 */
				events &= ~EPOLLOUT;
				dma_buf_poll_cb(शून्य, &dcb->cb);
				अवरोध;
			पूर्ण
			अगर (!dma_fence_add_callback(fence, &dcb->cb,
						    dma_buf_poll_cb)) अणु
				dma_fence_put(fence);
				events &= ~EPOLLOUT;
				अवरोध;
			पूर्ण
			dma_fence_put(fence);
		पूर्ण

		/* No callback queued, wake up any additional रुकोers. */
		अगर (i == shared_count)
			dma_buf_poll_cb(शून्य, &dcb->cb);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस events;
पूर्ण

/**
 * dma_buf_set_name - Set a name to a specअगरic dma_buf to track the usage.
 * The name of the dma-buf buffer can only be set when the dma-buf is not
 * attached to any devices. It could theoritically support changing the
 * name of the dma-buf अगर the same piece of memory is used क्रम multiple
 * purpose between dअगरferent devices.
 *
 * @dmabuf: [in]     dmabuf buffer that will be नामd.
 * @buf:    [in]     A piece of userspace memory that contains the name of
 *                   the dma-buf.
 *
 * Returns 0 on success. If the dma-buf buffer is alपढ़ोy attached to
 * devices, वापस -EBUSY.
 *
 */
अटल दीर्घ dma_buf_set_name(काष्ठा dma_buf *dmabuf, स्थिर अक्षर __user *buf)
अणु
	अक्षर *name = strndup_user(buf, DMA_BUF_NAME_LEN);
	दीर्घ ret = 0;

	अगर (IS_ERR(name))
		वापस PTR_ERR(name);

	dma_resv_lock(dmabuf->resv, शून्य);
	अगर (!list_empty(&dmabuf->attachments)) अणु
		ret = -EBUSY;
		kमुक्त(name);
		जाओ out_unlock;
	पूर्ण
	spin_lock(&dmabuf->name_lock);
	kमुक्त(dmabuf->name);
	dmabuf->name = name;
	spin_unlock(&dmabuf->name_lock);

out_unlock:
	dma_resv_unlock(dmabuf->resv);
	वापस ret;
पूर्ण

अटल दीर्घ dma_buf_ioctl(काष्ठा file *file,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा dma_buf *dmabuf;
	काष्ठा dma_buf_sync sync;
	क्रमागत dma_data_direction direction;
	पूर्णांक ret;

	dmabuf = file->निजी_data;

	चयन (cmd) अणु
	हाल DMA_BUF_IOCTL_SYNC:
		अगर (copy_from_user(&sync, (व्योम __user *) arg, माप(sync)))
			वापस -EFAULT;

		अगर (sync.flags & ~DMA_BUF_SYNC_VALID_FLAGS_MASK)
			वापस -EINVAL;

		चयन (sync.flags & DMA_BUF_SYNC_RW) अणु
		हाल DMA_BUF_SYNC_READ:
			direction = DMA_FROM_DEVICE;
			अवरोध;
		हाल DMA_BUF_SYNC_WRITE:
			direction = DMA_TO_DEVICE;
			अवरोध;
		हाल DMA_BUF_SYNC_RW:
			direction = DMA_BIसूचीECTIONAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (sync.flags & DMA_BUF_SYNC_END)
			ret = dma_buf_end_cpu_access(dmabuf, direction);
		अन्यथा
			ret = dma_buf_begin_cpu_access(dmabuf, direction);

		वापस ret;

	हाल DMA_BUF_SET_NAME_A:
	हाल DMA_BUF_SET_NAME_B:
		वापस dma_buf_set_name(dmabuf, (स्थिर अक्षर __user *)arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल व्योम dma_buf_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *file)
अणु
	काष्ठा dma_buf *dmabuf = file->निजी_data;

	seq_म_लिखो(m, "size:\t%zu\n", dmabuf->size);
	/* Don't count the temporary reference taken inside procfs seq_show */
	seq_म_लिखो(m, "count:\t%ld\n", file_count(dmabuf->file) - 1);
	seq_म_लिखो(m, "exp_name:\t%s\n", dmabuf->exp_name);
	spin_lock(&dmabuf->name_lock);
	अगर (dmabuf->name)
		seq_म_लिखो(m, "name:\t%s\n", dmabuf->name);
	spin_unlock(&dmabuf->name_lock);
पूर्ण

अटल स्थिर काष्ठा file_operations dma_buf_fops = अणु
	.release	= dma_buf_file_release,
	.mmap		= dma_buf_mmap_पूर्णांकernal,
	.llseek		= dma_buf_llseek,
	.poll		= dma_buf_poll,
	.unlocked_ioctl	= dma_buf_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.show_fdinfo	= dma_buf_show_fdinfo,
पूर्ण;

/*
 * is_dma_buf_file - Check अगर काष्ठा file* is associated with dma_buf
 */
अटल अंतरभूत पूर्णांक is_dma_buf_file(काष्ठा file *file)
अणु
	वापस file->f_op == &dma_buf_fops;
पूर्ण

अटल काष्ठा file *dma_buf_getfile(काष्ठा dma_buf *dmabuf, पूर्णांक flags)
अणु
	काष्ठा file *file;
	काष्ठा inode *inode = alloc_anon_inode(dma_buf_mnt->mnt_sb);

	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	inode->i_size = dmabuf->size;
	inode_set_bytes(inode, dmabuf->size);

	file = alloc_file_pseuकरो(inode, dma_buf_mnt, "dmabuf",
				 flags, &dma_buf_fops);
	अगर (IS_ERR(file))
		जाओ err_alloc_file;
	file->f_flags = flags & (O_ACCMODE | O_NONBLOCK);
	file->निजी_data = dmabuf;
	file->f_path.dentry->d_fsdata = dmabuf;

	वापस file;

err_alloc_file:
	iput(inode);
	वापस file;
पूर्ण

/**
 * DOC: dma buf device access
 *
 * For device DMA access to a shared DMA buffer the usual sequence of operations
 * is fairly simple:
 *
 * 1. The exporter defines his exporter instance using
 *    DEFINE_DMA_BUF_EXPORT_INFO() and calls dma_buf_export() to wrap a निजी
 *    buffer object पूर्णांकo a &dma_buf. It then exports that &dma_buf to userspace
 *    as a file descriptor by calling dma_buf_fd().
 *
 * 2. Userspace passes this file-descriptors to all drivers it wants this buffer
 *    to share with: First the filedescriptor is converted to a &dma_buf using
 *    dma_buf_get(). Then the buffer is attached to the device using
 *    dma_buf_attach().
 *
 *    Up to this stage the exporter is still मुक्त to migrate or पुनः_स्मृतिate the
 *    backing storage.
 *
 * 3. Once the buffer is attached to all devices userspace can initiate DMA
 *    access to the shared buffer. In the kernel this is करोne by calling
 *    dma_buf_map_attachment() and dma_buf_unmap_attachment().
 *
 * 4. Once a driver is करोne with a shared buffer it needs to call
 *    dma_buf_detach() (after cleaning up any mappings) and then release the
 *    reference acquired with dma_buf_get() by calling dma_buf_put().
 *
 * For the detailed semantics exporters are expected to implement see
 * &dma_buf_ops.
 */

/**
 * dma_buf_export - Creates a new dma_buf, and associates an anon file
 * with this buffer, so it can be exported.
 * Also connect the allocator specअगरic data and ops to the buffer.
 * Additionally, provide a name string क्रम exporter; useful in debugging.
 *
 * @exp_info:	[in]	holds all the export related inक्रमmation provided
 *			by the exporter. see &काष्ठा dma_buf_export_info
 *			क्रम further details.
 *
 * Returns, on success, a newly created काष्ठा dma_buf object, which wraps the
 * supplied निजी data and operations क्रम काष्ठा dma_buf_ops. On either
 * missing ops, or error in allocating काष्ठा dma_buf, will वापस negative
 * error.
 *
 * For most हालs the easiest way to create @exp_info is through the
 * %DEFINE_DMA_BUF_EXPORT_INFO macro.
 */
काष्ठा dma_buf *dma_buf_export(स्थिर काष्ठा dma_buf_export_info *exp_info)
अणु
	काष्ठा dma_buf *dmabuf;
	काष्ठा dma_resv *resv = exp_info->resv;
	काष्ठा file *file;
	माप_प्रकार alloc_size = माप(काष्ठा dma_buf);
	पूर्णांक ret;

	अगर (!exp_info->resv)
		alloc_size += माप(काष्ठा dma_resv);
	अन्यथा
		/* prevent &dma_buf[1] == dma_buf->resv */
		alloc_size += 1;

	अगर (WARN_ON(!exp_info->priv
			  || !exp_info->ops
			  || !exp_info->ops->map_dma_buf
			  || !exp_info->ops->unmap_dma_buf
			  || !exp_info->ops->release)) अणु
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (WARN_ON(exp_info->ops->cache_sgt_mapping &&
		    (exp_info->ops->pin || exp_info->ops->unpin)))
		वापस ERR_PTR(-EINVAL);

	अगर (WARN_ON(!exp_info->ops->pin != !exp_info->ops->unpin))
		वापस ERR_PTR(-EINVAL);

	अगर (!try_module_get(exp_info->owner))
		वापस ERR_PTR(-ENOENT);

	dmabuf = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!dmabuf) अणु
		ret = -ENOMEM;
		जाओ err_module;
	पूर्ण

	dmabuf->priv = exp_info->priv;
	dmabuf->ops = exp_info->ops;
	dmabuf->size = exp_info->size;
	dmabuf->exp_name = exp_info->exp_name;
	dmabuf->owner = exp_info->owner;
	spin_lock_init(&dmabuf->name_lock);
	init_रुकोqueue_head(&dmabuf->poll);
	dmabuf->cb_excl.poll = dmabuf->cb_shared.poll = &dmabuf->poll;
	dmabuf->cb_excl.active = dmabuf->cb_shared.active = 0;

	अगर (!resv) अणु
		resv = (काष्ठा dma_resv *)&dmabuf[1];
		dma_resv_init(resv);
	पूर्ण
	dmabuf->resv = resv;

	file = dma_buf_getfile(dmabuf, exp_info->flags);
	अगर (IS_ERR(file)) अणु
		ret = PTR_ERR(file);
		जाओ err_dmabuf;
	पूर्ण

	file->f_mode |= FMODE_LSEEK;
	dmabuf->file = file;

	mutex_init(&dmabuf->lock);
	INIT_LIST_HEAD(&dmabuf->attachments);

	mutex_lock(&db_list.lock);
	list_add(&dmabuf->list_node, &db_list.head);
	mutex_unlock(&db_list.lock);

	वापस dmabuf;

err_dmabuf:
	kमुक्त(dmabuf);
err_module:
	module_put(exp_info->owner);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_export);

/**
 * dma_buf_fd - वापसs a file descriptor क्रम the given काष्ठा dma_buf
 * @dmabuf:	[in]	poपूर्णांकer to dma_buf क्रम which fd is required.
 * @flags:      [in]    flags to give to fd
 *
 * On success, वापसs an associated 'fd'. Else, वापसs error.
 */
पूर्णांक dma_buf_fd(काष्ठा dma_buf *dmabuf, पूर्णांक flags)
अणु
	पूर्णांक fd;

	अगर (!dmabuf || !dmabuf->file)
		वापस -EINVAL;

	fd = get_unused_fd_flags(flags);
	अगर (fd < 0)
		वापस fd;

	fd_install(fd, dmabuf->file);

	वापस fd;
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_fd);

/**
 * dma_buf_get - वापसs the काष्ठा dma_buf related to an fd
 * @fd:	[in]	fd associated with the काष्ठा dma_buf to be वापसed
 *
 * On success, वापसs the काष्ठा dma_buf associated with an fd; uses
 * file's refcounting करोne by fget to increase refcount. वापसs ERR_PTR
 * otherwise.
 */
काष्ठा dma_buf *dma_buf_get(पूर्णांक fd)
अणु
	काष्ठा file *file;

	file = fget(fd);

	अगर (!file)
		वापस ERR_PTR(-EBADF);

	अगर (!is_dma_buf_file(file)) अणु
		fput(file);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस file->निजी_data;
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_get);

/**
 * dma_buf_put - decreases refcount of the buffer
 * @dmabuf:	[in]	buffer to reduce refcount of
 *
 * Uses file's refcounting करोne implicitly by fput().
 *
 * If, as a result of this call, the refcount becomes 0, the 'release' file
 * operation related to this fd is called. It calls &dma_buf_ops.release vfunc
 * in turn, and मुक्तs the memory allocated क्रम dmabuf when exported.
 */
व्योम dma_buf_put(काष्ठा dma_buf *dmabuf)
अणु
	अगर (WARN_ON(!dmabuf || !dmabuf->file))
		वापस;

	fput(dmabuf->file);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_put);

अटल व्योम mangle_sg_table(काष्ठा sg_table *sg_table)
अणु
#अगर_घोषित CONFIG_DMABUF_DEBUG
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	/* To catch abuse of the underlying काष्ठा page by importers mix
	 * up the bits, but take care to preserve the low SG_ bits to
	 * not corrupt the sgt. The mixing is unकरोne in __unmap_dma_buf
	 * beक्रमe passing the sgt back to the exporter. */
	क्रम_each_sgtable_sg(sg_table, sg, i)
		sg->page_link ^= ~0xffUL;
#पूर्ण_अगर

पूर्ण
अटल काष्ठा sg_table * __map_dma_buf(काष्ठा dma_buf_attachment *attach,
				       क्रमागत dma_data_direction direction)
अणु
	काष्ठा sg_table *sg_table;

	sg_table = attach->dmabuf->ops->map_dma_buf(attach, direction);

	अगर (!IS_ERR_OR_शून्य(sg_table))
		mangle_sg_table(sg_table);

	वापस sg_table;
पूर्ण

/**
 * dma_buf_dynamic_attach - Add the device to dma_buf's attachments list
 * @dmabuf:		[in]	buffer to attach device to.
 * @dev:		[in]	device to be attached.
 * @importer_ops:	[in]	importer operations क्रम the attachment
 * @importer_priv:	[in]	importer निजी poपूर्णांकer क्रम the attachment
 *
 * Returns काष्ठा dma_buf_attachment poपूर्णांकer क्रम this attachment. Attachments
 * must be cleaned up by calling dma_buf_detach().
 *
 * Optionally this calls &dma_buf_ops.attach to allow device-specअगरic attach
 * functionality.
 *
 * Returns:
 *
 * A poपूर्णांकer to newly created &dma_buf_attachment on success, or a negative
 * error code wrapped पूर्णांकo a poपूर्णांकer on failure.
 *
 * Note that this can fail अगर the backing storage of @dmabuf is in a place not
 * accessible to @dev, and cannot be moved to a more suitable place. This is
 * indicated with the error code -EBUSY.
 */
काष्ठा dma_buf_attachment *
dma_buf_dynamic_attach(काष्ठा dma_buf *dmabuf, काष्ठा device *dev,
		       स्थिर काष्ठा dma_buf_attach_ops *importer_ops,
		       व्योम *importer_priv)
अणु
	काष्ठा dma_buf_attachment *attach;
	पूर्णांक ret;

	अगर (WARN_ON(!dmabuf || !dev))
		वापस ERR_PTR(-EINVAL);

	अगर (WARN_ON(importer_ops && !importer_ops->move_notअगरy))
		वापस ERR_PTR(-EINVAL);

	attach = kzalloc(माप(*attach), GFP_KERNEL);
	अगर (!attach)
		वापस ERR_PTR(-ENOMEM);

	attach->dev = dev;
	attach->dmabuf = dmabuf;
	अगर (importer_ops)
		attach->peer2peer = importer_ops->allow_peer2peer;
	attach->importer_ops = importer_ops;
	attach->importer_priv = importer_priv;

	अगर (dmabuf->ops->attach) अणु
		ret = dmabuf->ops->attach(dmabuf, attach);
		अगर (ret)
			जाओ err_attach;
	पूर्ण
	dma_resv_lock(dmabuf->resv, शून्य);
	list_add(&attach->node, &dmabuf->attachments);
	dma_resv_unlock(dmabuf->resv);

	/* When either the importer or the exporter can't handle dynamic
	 * mappings we cache the mapping here to aव्योम issues with the
	 * reservation object lock.
	 */
	अगर (dma_buf_attachment_is_dynamic(attach) !=
	    dma_buf_is_dynamic(dmabuf)) अणु
		काष्ठा sg_table *sgt;

		अगर (dma_buf_is_dynamic(attach->dmabuf)) अणु
			dma_resv_lock(attach->dmabuf->resv, शून्य);
			ret = dmabuf->ops->pin(attach);
			अगर (ret)
				जाओ err_unlock;
		पूर्ण

		sgt = __map_dma_buf(attach, DMA_BIसूचीECTIONAL);
		अगर (!sgt)
			sgt = ERR_PTR(-ENOMEM);
		अगर (IS_ERR(sgt)) अणु
			ret = PTR_ERR(sgt);
			जाओ err_unpin;
		पूर्ण
		अगर (dma_buf_is_dynamic(attach->dmabuf))
			dma_resv_unlock(attach->dmabuf->resv);
		attach->sgt = sgt;
		attach->dir = DMA_BIसूचीECTIONAL;
	पूर्ण

	वापस attach;

err_attach:
	kमुक्त(attach);
	वापस ERR_PTR(ret);

err_unpin:
	अगर (dma_buf_is_dynamic(attach->dmabuf))
		dmabuf->ops->unpin(attach);

err_unlock:
	अगर (dma_buf_is_dynamic(attach->dmabuf))
		dma_resv_unlock(attach->dmabuf->resv);

	dma_buf_detach(dmabuf, attach);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_dynamic_attach);

/**
 * dma_buf_attach - Wrapper क्रम dma_buf_dynamic_attach
 * @dmabuf:	[in]	buffer to attach device to.
 * @dev:	[in]	device to be attached.
 *
 * Wrapper to call dma_buf_dynamic_attach() क्रम drivers which still use a अटल
 * mapping.
 */
काष्ठा dma_buf_attachment *dma_buf_attach(काष्ठा dma_buf *dmabuf,
					  काष्ठा device *dev)
अणु
	वापस dma_buf_dynamic_attach(dmabuf, dev, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_attach);

अटल व्योम __unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
			    काष्ठा sg_table *sg_table,
			    क्रमागत dma_data_direction direction)
अणु
	/* uses XOR, hence this unmangles */
	mangle_sg_table(sg_table);

	attach->dmabuf->ops->unmap_dma_buf(attach, sg_table, direction);
पूर्ण

/**
 * dma_buf_detach - Remove the given attachment from dmabuf's attachments list
 * @dmabuf:	[in]	buffer to detach from.
 * @attach:	[in]	attachment to be detached; is मुक्त'd after this call.
 *
 * Clean up a device attachment obtained by calling dma_buf_attach().
 *
 * Optionally this calls &dma_buf_ops.detach क्रम device-specअगरic detach.
 */
व्योम dma_buf_detach(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_attachment *attach)
अणु
	अगर (WARN_ON(!dmabuf || !attach))
		वापस;

	अगर (attach->sgt) अणु
		अगर (dma_buf_is_dynamic(attach->dmabuf))
			dma_resv_lock(attach->dmabuf->resv, शून्य);

		__unmap_dma_buf(attach, attach->sgt, attach->dir);

		अगर (dma_buf_is_dynamic(attach->dmabuf)) अणु
			dmabuf->ops->unpin(attach);
			dma_resv_unlock(attach->dmabuf->resv);
		पूर्ण
	पूर्ण

	dma_resv_lock(dmabuf->resv, शून्य);
	list_del(&attach->node);
	dma_resv_unlock(dmabuf->resv);
	अगर (dmabuf->ops->detach)
		dmabuf->ops->detach(dmabuf, attach);

	kमुक्त(attach);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_detach);

/**
 * dma_buf_pin - Lock करोwn the DMA-buf
 * @attach:	[in]	attachment which should be pinned
 *
 * Only dynamic importers (who set up @attach with dma_buf_dynamic_attach()) may
 * call this, and only क्रम limited use हालs like scanout and not क्रम temporary
 * pin operations. It is not permitted to allow userspace to pin arbitrary
 * amounts of buffers through this पूर्णांकerface.
 *
 * Buffers must be unpinned by calling dma_buf_unpin().
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
पूर्णांक dma_buf_pin(काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा dma_buf *dmabuf = attach->dmabuf;
	पूर्णांक ret = 0;

	WARN_ON(!dma_buf_attachment_is_dynamic(attach));

	dma_resv_निश्चित_held(dmabuf->resv);

	अगर (dmabuf->ops->pin)
		ret = dmabuf->ops->pin(attach);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_pin);

/**
 * dma_buf_unpin - Unpin a DMA-buf
 * @attach:	[in]	attachment which should be unpinned
 *
 * This unpins a buffer pinned by dma_buf_pin() and allows the exporter to move
 * any mapping of @attach again and inक्रमm the importer through
 * &dma_buf_attach_ops.move_notअगरy.
 */
व्योम dma_buf_unpin(काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा dma_buf *dmabuf = attach->dmabuf;

	WARN_ON(!dma_buf_attachment_is_dynamic(attach));

	dma_resv_निश्चित_held(dmabuf->resv);

	अगर (dmabuf->ops->unpin)
		dmabuf->ops->unpin(attach);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_unpin);

/**
 * dma_buf_map_attachment - Returns the scatterlist table of the attachment;
 * mapped पूर्णांकo _device_ address space. Is a wrapper क्रम map_dma_buf() of the
 * dma_buf_ops.
 * @attach:	[in]	attachment whose scatterlist is to be वापसed
 * @direction:	[in]	direction of DMA transfer
 *
 * Returns sg_table containing the scatterlist to be वापसed; वापसs ERR_PTR
 * on error. May वापस -EINTR अगर it is पूर्णांकerrupted by a संकेत.
 *
 * On success, the DMA addresses and lengths in the वापसed scatterlist are
 * PAGE_SIZE aligned.
 *
 * A mapping must be unmapped by using dma_buf_unmap_attachment(). Note that
 * the underlying backing storage is pinned क्रम as दीर्घ as a mapping exists,
 * thereक्रमe users/importers should not hold onto a mapping क्रम undue amounts of
 * समय.
 */
काष्ठा sg_table *dma_buf_map_attachment(काष्ठा dma_buf_attachment *attach,
					क्रमागत dma_data_direction direction)
अणु
	काष्ठा sg_table *sg_table;
	पूर्णांक r;

	might_sleep();

	अगर (WARN_ON(!attach || !attach->dmabuf))
		वापस ERR_PTR(-EINVAL);

	अगर (dma_buf_attachment_is_dynamic(attach))
		dma_resv_निश्चित_held(attach->dmabuf->resv);

	अगर (attach->sgt) अणु
		/*
		 * Two mappings with dअगरferent directions क्रम the same
		 * attachment are not allowed.
		 */
		अगर (attach->dir != direction &&
		    attach->dir != DMA_BIसूचीECTIONAL)
			वापस ERR_PTR(-EBUSY);

		वापस attach->sgt;
	पूर्ण

	अगर (dma_buf_is_dynamic(attach->dmabuf)) अणु
		dma_resv_निश्चित_held(attach->dmabuf->resv);
		अगर (!IS_ENABLED(CONFIG_DMABUF_MOVE_NOTIFY)) अणु
			r = attach->dmabuf->ops->pin(attach);
			अगर (r)
				वापस ERR_PTR(r);
		पूर्ण
	पूर्ण

	sg_table = __map_dma_buf(attach, direction);
	अगर (!sg_table)
		sg_table = ERR_PTR(-ENOMEM);

	अगर (IS_ERR(sg_table) && dma_buf_is_dynamic(attach->dmabuf) &&
	     !IS_ENABLED(CONFIG_DMABUF_MOVE_NOTIFY))
		attach->dmabuf->ops->unpin(attach);

	अगर (!IS_ERR(sg_table) && attach->dmabuf->ops->cache_sgt_mapping) अणु
		attach->sgt = sg_table;
		attach->dir = direction;
	पूर्ण

#अगर_घोषित CONFIG_DMA_API_DEBUG
	अगर (!IS_ERR(sg_table)) अणु
		काष्ठा scatterlist *sg;
		u64 addr;
		पूर्णांक len;
		पूर्णांक i;

		क्रम_each_sgtable_dma_sg(sg_table, sg, i) अणु
			addr = sg_dma_address(sg);
			len = sg_dma_len(sg);
			अगर (!PAGE_ALIGNED(addr) || !PAGE_ALIGNED(len)) अणु
				pr_debug("%s: addr %llx or len %x is not page aligned!\n",
					 __func__, addr, len);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_API_DEBUG */

	वापस sg_table;
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_map_attachment);

/**
 * dma_buf_unmap_attachment - unmaps and decreases usecount of the buffer;might
 * deallocate the scatterlist associated. Is a wrapper क्रम unmap_dma_buf() of
 * dma_buf_ops.
 * @attach:	[in]	attachment to unmap buffer from
 * @sg_table:	[in]	scatterlist info of the buffer to unmap
 * @direction:  [in]    direction of DMA transfer
 *
 * This unmaps a DMA mapping क्रम @attached obtained by dma_buf_map_attachment().
 */
व्योम dma_buf_unmap_attachment(काष्ठा dma_buf_attachment *attach,
				काष्ठा sg_table *sg_table,
				क्रमागत dma_data_direction direction)
अणु
	might_sleep();

	अगर (WARN_ON(!attach || !attach->dmabuf || !sg_table))
		वापस;

	अगर (dma_buf_attachment_is_dynamic(attach))
		dma_resv_निश्चित_held(attach->dmabuf->resv);

	अगर (attach->sgt == sg_table)
		वापस;

	अगर (dma_buf_is_dynamic(attach->dmabuf))
		dma_resv_निश्चित_held(attach->dmabuf->resv);

	__unmap_dma_buf(attach, sg_table, direction);

	अगर (dma_buf_is_dynamic(attach->dmabuf) &&
	    !IS_ENABLED(CONFIG_DMABUF_MOVE_NOTIFY))
		dma_buf_unpin(attach);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_unmap_attachment);

/**
 * dma_buf_move_notअगरy - notअगरy attachments that DMA-buf is moving
 *
 * @dmabuf:	[in]	buffer which is moving
 *
 * Inक्रमms all attachmenst that they need to destroy and recreated all their
 * mappings.
 */
व्योम dma_buf_move_notअगरy(काष्ठा dma_buf *dmabuf)
अणु
	काष्ठा dma_buf_attachment *attach;

	dma_resv_निश्चित_held(dmabuf->resv);

	list_क्रम_each_entry(attach, &dmabuf->attachments, node)
		अगर (attach->importer_ops)
			attach->importer_ops->move_notअगरy(attach);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_move_notअगरy);

/**
 * DOC: cpu access
 *
 * There are mutliple reasons क्रम supporting CPU access to a dma buffer object:
 *
 * - Fallback operations in the kernel, क्रम example when a device is connected
 *   over USB and the kernel needs to shuffle the data around first beक्रमe
 *   sending it away. Cache coherency is handled by braketing any transactions
 *   with calls to dma_buf_begin_cpu_access() and dma_buf_end_cpu_access()
 *   access.
 *
 *   Since क्रम most kernel पूर्णांकernal dma-buf accesses need the entire buffer, a
 *   vmap पूर्णांकerface is पूर्णांकroduced. Note that on very old 32-bit architectures
 *   vदो_स्मृति space might be limited and result in vmap calls failing.
 *
 *   Interfaces::
 *
 *      व्योम \*dma_buf_vmap(काष्ठा dma_buf \*dmabuf)
 *      व्योम dma_buf_vunmap(काष्ठा dma_buf \*dmabuf, व्योम \*vaddr)
 *
 *   The vmap call can fail अगर there is no vmap support in the exporter, or अगर
 *   it runs out of vदो_स्मृति space. Note that the dma-buf layer keeps a reference
 *   count क्रम all vmap access and calls करोwn पूर्णांकo the exporter's vmap function
 *   only when no vmapping exists, and only unmaps it once. Protection against
 *   concurrent vmap/vunmap calls is provided by taking the &dma_buf.lock mutex.
 *
 * - For full compatibility on the importer side with existing userspace
 *   पूर्णांकerfaces, which might alपढ़ोy support mmap'ing buffers. This is needed in
 *   many processing pipelines (e.g. feeding a software rendered image पूर्णांकo a
 *   hardware pipeline, thumbnail creation, snapshots, ...). Also, Android's ION
 *   framework alपढ़ोy supported this and क्रम DMA buffer file descriptors to
 *   replace ION buffers mmap support was needed.
 *
 *   There is no special पूर्णांकerfaces, userspace simply calls mmap on the dma-buf
 *   fd. But like क्रम CPU access there's a need to braket the actual access,
 *   which is handled by the ioctl (DMA_BUF_IOCTL_SYNC). Note that
 *   DMA_BUF_IOCTL_SYNC can fail with -EAGAIN or -EINTR, in which हाल it must
 *   be restarted.
 *
 *   Some प्रणालीs might need some sort of cache coherency management e.g. when
 *   CPU and GPU करोमुख्यs are being accessed through dma-buf at the same समय.
 *   To circumvent this problem there are begin/end coherency markers, that
 *   क्रमward directly to existing dma-buf device drivers vfunc hooks. Userspace
 *   can make use of those markers through the DMA_BUF_IOCTL_SYNC ioctl. The
 *   sequence would be used like following:
 *
 *     - mmap dma-buf fd
 *     - क्रम each drawing/upload cycle in CPU 1. SYNC_START ioctl, 2. पढ़ो/ग_लिखो
 *       to mmap area 3. SYNC_END ioctl. This can be repeated as often as you
 *       want (with the new data being consumed by say the GPU or the scanout
 *       device)
 *     - munmap once you करोn't need the buffer any more
 *
 *    For correctness and optimal perक्रमmance, it is always required to use
 *    SYNC_START and SYNC_END beक्रमe and after, respectively, when accessing the
 *    mapped address. Userspace cannot rely on coherent access, even when there
 *    are प्रणालीs where it just works without calling these ioctls.
 *
 * - And as a CPU fallback in userspace processing pipelines.
 *
 *   Similar to the motivation क्रम kernel cpu access it is again important that
 *   the userspace code of a given importing subप्रणाली can use the same
 *   पूर्णांकerfaces with a imported dma-buf buffer object as with a native buffer
 *   object. This is especially important क्रम drm where the userspace part of
 *   contemporary OpenGL, X, and other drivers is huge, and reworking them to
 *   use a dअगरferent way to mmap a buffer rather invasive.
 *
 *   The assumption in the current dma-buf पूर्णांकerfaces is that redirecting the
 *   initial mmap is all that's needed. A survey of some of the existing
 *   subप्रणालीs shows that no driver seems to करो any nefarious thing like
 *   syncing up with outstanding asynchronous processing on the device or
 *   allocating special resources at fault समय. So hopefully this is good
 *   enough, since adding पूर्णांकerfaces to पूर्णांकercept pagefaults and allow pte
 *   shootकरोwns would increase the complनिकासy quite a bit.
 *
 *   Interface::
 *
 *      पूर्णांक dma_buf_mmap(काष्ठा dma_buf \*, काष्ठा vm_area_काष्ठा \*,
 *		       अचिन्हित दीर्घ);
 *
 *   If the importing subप्रणाली simply provides a special-purpose mmap call to
 *   set up a mapping in userspace, calling करो_mmap with &dma_buf.file will
 *   equally achieve that क्रम a dma-buf object.
 */

अटल पूर्णांक __dma_buf_begin_cpu_access(काष्ठा dma_buf *dmabuf,
				      क्रमागत dma_data_direction direction)
अणु
	bool ग_लिखो = (direction == DMA_BIसूचीECTIONAL ||
		      direction == DMA_TO_DEVICE);
	काष्ठा dma_resv *resv = dmabuf->resv;
	दीर्घ ret;

	/* Wait on any implicit rendering fences */
	ret = dma_resv_रुको_समयout_rcu(resv, ग_लिखो, true,
						  MAX_SCHEDULE_TIMEOUT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * dma_buf_begin_cpu_access - Must be called beक्रमe accessing a dma_buf from the
 * cpu in the kernel context. Calls begin_cpu_access to allow exporter-specअगरic
 * preparations. Coherency is only guaranteed in the specअगरied range क्रम the
 * specअगरied access direction.
 * @dmabuf:	[in]	buffer to prepare cpu access क्रम.
 * @direction:	[in]	length of range क्रम cpu access.
 *
 * After the cpu access is complete the caller should call
 * dma_buf_end_cpu_access(). Only when cpu access is braketed by both calls is
 * it guaranteed to be coherent with other DMA access.
 *
 * This function will also रुको क्रम any DMA transactions tracked through
 * implicit synchronization in &dma_buf.resv. For DMA transactions with explicit
 * synchronization this function will only ensure cache coherency, callers must
 * ensure synchronization with such DMA transactions on their own.
 *
 * Can वापस negative error values, वापसs 0 on success.
 */
पूर्णांक dma_buf_begin_cpu_access(काष्ठा dma_buf *dmabuf,
			     क्रमागत dma_data_direction direction)
अणु
	पूर्णांक ret = 0;

	अगर (WARN_ON(!dmabuf))
		वापस -EINVAL;

	might_lock(&dmabuf->resv->lock.base);

	अगर (dmabuf->ops->begin_cpu_access)
		ret = dmabuf->ops->begin_cpu_access(dmabuf, direction);

	/* Ensure that all fences are रुकोed upon - but we first allow
	 * the native handler the chance to करो so more efficiently अगर it
	 * chooses. A द्विगुन invocation here will be reasonably cheap no-op.
	 */
	अगर (ret == 0)
		ret = __dma_buf_begin_cpu_access(dmabuf, direction);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_begin_cpu_access);

/**
 * dma_buf_end_cpu_access - Must be called after accessing a dma_buf from the
 * cpu in the kernel context. Calls end_cpu_access to allow exporter-specअगरic
 * actions. Coherency is only guaranteed in the specअगरied range क्रम the
 * specअगरied access direction.
 * @dmabuf:	[in]	buffer to complete cpu access क्रम.
 * @direction:	[in]	length of range क्रम cpu access.
 *
 * This terminates CPU access started with dma_buf_begin_cpu_access().
 *
 * Can वापस negative error values, वापसs 0 on success.
 */
पूर्णांक dma_buf_end_cpu_access(काष्ठा dma_buf *dmabuf,
			   क्रमागत dma_data_direction direction)
अणु
	पूर्णांक ret = 0;

	WARN_ON(!dmabuf);

	might_lock(&dmabuf->resv->lock.base);

	अगर (dmabuf->ops->end_cpu_access)
		ret = dmabuf->ops->end_cpu_access(dmabuf, direction);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_end_cpu_access);


/**
 * dma_buf_mmap - Setup up a userspace mmap with the given vma
 * @dmabuf:	[in]	buffer that should back the vma
 * @vma:	[in]	vma क्रम the mmap
 * @pgoff:	[in]	offset in pages where this mmap should start within the
 *			dma-buf buffer.
 *
 * This function adjusts the passed in vma so that it poपूर्णांकs at the file of the
 * dma_buf operation. It also adjusts the starting pgoff and करोes bounds
 * checking on the size of the vma. Then it calls the exporters mmap function to
 * set up the mapping.
 *
 * Can वापस negative error values, वापसs 0 on success.
 */
पूर्णांक dma_buf_mmap(काष्ठा dma_buf *dmabuf, काष्ठा vm_area_काष्ठा *vma,
		 अचिन्हित दीर्घ pgoff)
अणु
	अगर (WARN_ON(!dmabuf || !vma))
		वापस -EINVAL;

	/* check अगर buffer supports mmap */
	अगर (!dmabuf->ops->mmap)
		वापस -EINVAL;

	/* check क्रम offset overflow */
	अगर (pgoff + vma_pages(vma) < pgoff)
		वापस -EOVERFLOW;

	/* check क्रम overflowing the buffer's size */
	अगर (pgoff + vma_pages(vma) >
	    dmabuf->size >> PAGE_SHIFT)
		वापस -EINVAL;

	/* पढ़ोjust the vma */
	vma_set_file(vma, dmabuf->file);
	vma->vm_pgoff = pgoff;

	वापस dmabuf->ops->mmap(dmabuf, vma);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_mmap);

/**
 * dma_buf_vmap - Create भव mapping क्रम the buffer object पूर्णांकo kernel
 * address space. Same restrictions as क्रम vmap and मित्रs apply.
 * @dmabuf:	[in]	buffer to vmap
 * @map:	[out]	वापसs the vmap poपूर्णांकer
 *
 * This call may fail due to lack of भव mapping address space.
 * These calls are optional in drivers. The पूर्णांकended use क्रम them
 * is क्रम mapping objects linear in kernel space क्रम high use objects.
 *
 * To ensure coherency users must call dma_buf_begin_cpu_access() and
 * dma_buf_end_cpu_access() around any cpu access perक्रमmed through this
 * mapping.
 *
 * Returns 0 on success, or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक dma_buf_vmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा dma_buf_map ptr;
	पूर्णांक ret = 0;

	dma_buf_map_clear(map);

	अगर (WARN_ON(!dmabuf))
		वापस -EINVAL;

	अगर (!dmabuf->ops->vmap)
		वापस -EINVAL;

	mutex_lock(&dmabuf->lock);
	अगर (dmabuf->vmapping_counter) अणु
		dmabuf->vmapping_counter++;
		BUG_ON(dma_buf_map_is_null(&dmabuf->vmap_ptr));
		*map = dmabuf->vmap_ptr;
		जाओ out_unlock;
	पूर्ण

	BUG_ON(dma_buf_map_is_set(&dmabuf->vmap_ptr));

	ret = dmabuf->ops->vmap(dmabuf, &ptr);
	अगर (WARN_ON_ONCE(ret))
		जाओ out_unlock;

	dmabuf->vmap_ptr = ptr;
	dmabuf->vmapping_counter = 1;

	*map = dmabuf->vmap_ptr;

out_unlock:
	mutex_unlock(&dmabuf->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_vmap);

/**
 * dma_buf_vunmap - Unmap a vmap obtained by dma_buf_vmap.
 * @dmabuf:	[in]	buffer to vunmap
 * @map:	[in]	vmap poपूर्णांकer to vunmap
 */
व्योम dma_buf_vunmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map)
अणु
	अगर (WARN_ON(!dmabuf))
		वापस;

	BUG_ON(dma_buf_map_is_null(&dmabuf->vmap_ptr));
	BUG_ON(dmabuf->vmapping_counter == 0);
	BUG_ON(!dma_buf_map_is_equal(&dmabuf->vmap_ptr, map));

	mutex_lock(&dmabuf->lock);
	अगर (--dmabuf->vmapping_counter == 0) अणु
		अगर (dmabuf->ops->vunmap)
			dmabuf->ops->vunmap(dmabuf, map);
		dma_buf_map_clear(&dmabuf->vmap_ptr);
	पूर्ण
	mutex_unlock(&dmabuf->lock);
पूर्ण
EXPORT_SYMBOL_GPL(dma_buf_vunmap);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक dma_buf_debug_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	पूर्णांक ret;
	काष्ठा dma_buf *buf_obj;
	काष्ठा dma_buf_attachment *attach_obj;
	काष्ठा dma_resv *robj;
	काष्ठा dma_resv_list *fobj;
	काष्ठा dma_fence *fence;
	अचिन्हित seq;
	पूर्णांक count = 0, attach_count, shared_count, i;
	माप_प्रकार size = 0;

	ret = mutex_lock_पूर्णांकerruptible(&db_list.lock);

	अगर (ret)
		वापस ret;

	seq_माला_दो(s, "\nDma-buf Objects:\n");
	seq_म_लिखो(s, "%-8s\t%-8s\t%-8s\t%-8s\texp_name\t%-8s\n",
		   "size", "flags", "mode", "count", "ino");

	list_क्रम_each_entry(buf_obj, &db_list.head, list_node) अणु

		ret = dma_resv_lock_पूर्णांकerruptible(buf_obj->resv, शून्य);
		अगर (ret)
			जाओ error_unlock;

		seq_म_लिखो(s, "%08zu\t%08x\t%08x\t%08ld\t%s\t%08lu\t%s\n",
				buf_obj->size,
				buf_obj->file->f_flags, buf_obj->file->f_mode,
				file_count(buf_obj->file),
				buf_obj->exp_name,
				file_inode(buf_obj->file)->i_ino,
				buf_obj->name ?: "");

		robj = buf_obj->resv;
		जबतक (true) अणु
			seq = पढ़ो_seqcount_begin(&robj->seq);
			rcu_पढ़ो_lock();
			fobj = rcu_dereference(robj->fence);
			shared_count = fobj ? fobj->shared_count : 0;
			fence = rcu_dereference(robj->fence_excl);
			अगर (!पढ़ो_seqcount_retry(&robj->seq, seq))
				अवरोध;
			rcu_पढ़ो_unlock();
		पूर्ण

		अगर (fence)
			seq_म_लिखो(s, "\tExclusive fence: %s %s %ssignalled\n",
				   fence->ops->get_driver_name(fence),
				   fence->ops->get_समयline_name(fence),
				   dma_fence_is_संकेतed(fence) ? "" : "un");
		क्रम (i = 0; i < shared_count; i++) अणु
			fence = rcu_dereference(fobj->shared[i]);
			अगर (!dma_fence_get_rcu(fence))
				जारी;
			seq_म_लिखो(s, "\tShared fence: %s %s %ssignalled\n",
				   fence->ops->get_driver_name(fence),
				   fence->ops->get_समयline_name(fence),
				   dma_fence_is_संकेतed(fence) ? "" : "un");
			dma_fence_put(fence);
		पूर्ण
		rcu_पढ़ो_unlock();

		seq_माला_दो(s, "\tAttached Devices:\n");
		attach_count = 0;

		list_क्रम_each_entry(attach_obj, &buf_obj->attachments, node) अणु
			seq_म_लिखो(s, "\t%s\n", dev_name(attach_obj->dev));
			attach_count++;
		पूर्ण
		dma_resv_unlock(buf_obj->resv);

		seq_म_लिखो(s, "Total %d devices attached\n\n",
				attach_count);

		count++;
		size += buf_obj->size;
	पूर्ण

	seq_म_लिखो(s, "\nTotal %d objects, %zu bytes\n", count, size);

	mutex_unlock(&db_list.lock);
	वापस 0;

error_unlock:
	mutex_unlock(&db_list.lock);
	वापस ret;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dma_buf_debug);

अटल काष्ठा dentry *dma_buf_debugfs_dir;

अटल पूर्णांक dma_buf_init_debugfs(व्योम)
अणु
	काष्ठा dentry *d;
	पूर्णांक err = 0;

	d = debugfs_create_dir("dma_buf", शून्य);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);

	dma_buf_debugfs_dir = d;

	d = debugfs_create_file("bufinfo", S_IRUGO, dma_buf_debugfs_dir,
				शून्य, &dma_buf_debug_fops);
	अगर (IS_ERR(d)) अणु
		pr_debug("dma_buf: debugfs: failed to create node bufinfo\n");
		debugfs_हटाओ_recursive(dma_buf_debugfs_dir);
		dma_buf_debugfs_dir = शून्य;
		err = PTR_ERR(d);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम dma_buf_uninit_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(dma_buf_debugfs_dir);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक dma_buf_init_debugfs(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम dma_buf_uninit_debugfs(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init dma_buf_init(व्योम)
अणु
	dma_buf_mnt = kern_mount(&dma_buf_fs_type);
	अगर (IS_ERR(dma_buf_mnt))
		वापस PTR_ERR(dma_buf_mnt);

	mutex_init(&db_list.lock);
	INIT_LIST_HEAD(&db_list.head);
	dma_buf_init_debugfs();
	वापस 0;
पूर्ण
subsys_initcall(dma_buf_init);

अटल व्योम __निकास dma_buf_deinit(व्योम)
अणु
	dma_buf_uninit_debugfs();
	kern_unmount(dma_buf_mnt);
पूर्ण
__निकासcall(dma_buf_deinit);
