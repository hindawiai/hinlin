<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 * Copyright 2018 Omnibond Systems, L.L.C.
 *
 * See COPYING in top-level directory.
 */

/*
 *  Linux VFS file operations.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-bufmap.h"
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>

अटल पूर्णांक flush_racache(काष्ठा inode *inode)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op;
	पूर्णांक ret;

	gossip_debug(GOSSIP_UTILS_DEBUG,
	    "%s: %pU: Handle is %pU | fs_id %d\n", __func__,
	    get_khandle_from_ino(inode), &orangefs_inode->refn.khandle,
	    orangefs_inode->refn.fs_id);

	new_op = op_alloc(ORANGEFS_VFS_OP_RA_FLUSH);
	अगर (!new_op)
		वापस -ENOMEM;
	new_op->upcall.req.ra_cache_flush.refn = orangefs_inode->refn;

	ret = service_operation(new_op, "orangefs_flush_racache",
	    get_पूर्णांकerruptible_flag(inode));

	gossip_debug(GOSSIP_UTILS_DEBUG, "%s: got return value of %d\n",
	    __func__, ret);

	op_release(new_op);
	वापस ret;
पूर्ण

/*
 * Post and रुको क्रम the I/O upcall to finish
 */
sमाप_प्रकार रुको_क्रम_direct_io(क्रमागत ORANGEFS_io_type type, काष्ठा inode *inode,
	loff_t *offset, काष्ठा iov_iter *iter, माप_प्रकार total_size,
	loff_t पढ़ोahead_size, काष्ठा orangefs_ग_लिखो_range *wr,
	पूर्णांक *index_वापस, काष्ठा file *file)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_khandle *handle = &orangefs_inode->refn.khandle;
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;
	पूर्णांक buffer_index;
	sमाप_प्रकार ret;
	माप_प्रकार copy_amount;
	पूर्णांक खोलो_क्रम_पढ़ो;
	पूर्णांक खोलो_क्रम_ग_लिखो;

	new_op = op_alloc(ORANGEFS_VFS_OP_खाता_IO);
	अगर (!new_op)
		वापस -ENOMEM;

	/* synchronous I/O */
	new_op->upcall.req.io.पढ़ोahead_size = पढ़ोahead_size;
	new_op->upcall.req.io.io_type = type;
	new_op->upcall.req.io.refn = orangefs_inode->refn;

populate_shared_memory:
	/* get a shared buffer index */
	buffer_index = orangefs_bufmap_get();
	अगर (buffer_index < 0) अणु
		ret = buffer_index;
		gossip_debug(GOSSIP_खाता_DEBUG,
			     "%s: orangefs_bufmap_get failure (%zd)\n",
			     __func__, ret);
		जाओ out;
	पूर्ण
	gossip_debug(GOSSIP_खाता_DEBUG,
		     "%s(%pU): GET op %p -> buffer_index %d\n",
		     __func__,
		     handle,
		     new_op,
		     buffer_index);

	new_op->uses_shared_memory = 1;
	new_op->upcall.req.io.buf_index = buffer_index;
	new_op->upcall.req.io.count = total_size;
	new_op->upcall.req.io.offset = *offset;
	अगर (type == ORANGEFS_IO_WRITE && wr) अणु
		new_op->upcall.uid = from_kuid(&init_user_ns, wr->uid);
		new_op->upcall.gid = from_kgid(&init_user_ns, wr->gid);
	पूर्ण
	/*
	 * Orangefs has no खोलो, and orangefs checks file permissions
	 * on each file access. Posix requires that file permissions
	 * be checked on खोलो and nowhere अन्यथा. Orangefs-through-the-kernel
	 * needs to seem posix compliant.
	 *
	 * The VFS खोलोs files, even अगर the fileप्रणाली provides no
	 * method. We can see अगर a file was successfully खोलोed क्रम
	 * पढ़ो and or क्रम ग_लिखो by looking at file->f_mode.
	 *
	 * When ग_लिखोs are flowing from the page cache, file is no
	 * दीर्घer available. We can trust the VFS to have checked
	 * file->f_mode beक्रमe writing to the page cache.
	 *
	 * The mode of a file might change between when it is खोलोed
	 * and IO commences, or it might be created with an arbitrary mode.
	 *
	 * We'll make sure we don't hit EACCES during the IO stage by
	 * using UID 0. Some of the समय we have access without changing
	 * to UID 0 - how to check?
	 */
	अगर (file) अणु
		खोलो_क्रम_ग_लिखो = file->f_mode & FMODE_WRITE;
		खोलो_क्रम_पढ़ो = file->f_mode & FMODE_READ;
	पूर्ण अन्यथा अणु
		खोलो_क्रम_ग_लिखो = 1;
		खोलो_क्रम_पढ़ो = 0; /* not relevant? */
	पूर्ण
	अगर ((type == ORANGEFS_IO_WRITE) && खोलो_क्रम_ग_लिखो)
		new_op->upcall.uid = 0;
	अगर ((type == ORANGEFS_IO_READ) && खोलो_क्रम_पढ़ो)
		new_op->upcall.uid = 0;

	gossip_debug(GOSSIP_खाता_DEBUG,
		     "%s(%pU): offset: %llu total_size: %zd\n",
		     __func__,
		     handle,
		     llu(*offset),
		     total_size);
	/*
	 * Stage 1: copy the buffers पूर्णांकo client-core's address space
	 */
	अगर (type == ORANGEFS_IO_WRITE && total_size) अणु
		ret = orangefs_bufmap_copy_from_iovec(iter, buffer_index,
		    total_size);
		अगर (ret < 0) अणु
			gossip_err("%s: Failed to copy-in buffers. Please make sure that the pvfs2-client is running. %ld\n",
			    __func__, (दीर्घ)ret);
			जाओ out;
		पूर्ण
	पूर्ण

	gossip_debug(GOSSIP_खाता_DEBUG,
		     "%s(%pU): Calling post_io_request with tag (%llu)\n",
		     __func__,
		     handle,
		     llu(new_op->tag));

	/* Stage 2: Service the I/O operation */
	ret = service_operation(new_op,
				type == ORANGEFS_IO_WRITE ?
					"file_write" :
					"file_read",
				get_पूर्णांकerruptible_flag(inode));

	/*
	 * If service_operation() वापसs -EAGAIN #and# the operation was
	 * purged from orangefs_request_list or htable_ops_in_progress, then
	 * we know that the client was restarted, causing the shared memory
	 * area to be wiped clean.  To restart a  ग_लिखो operation in this
	 * हाल, we must re-copy the data from the user's iovec to a NEW
	 * shared memory location. To restart a पढ़ो operation, we must get
	 * a new shared memory location.
	 */
	अगर (ret == -EAGAIN && op_state_purged(new_op)) अणु
		orangefs_bufmap_put(buffer_index);
		अगर (type == ORANGEFS_IO_WRITE)
			iov_iter_revert(iter, total_size);
		gossip_debug(GOSSIP_खाता_DEBUG,
			     "%s:going to repopulate_shared_memory.\n",
			     __func__);
		जाओ populate_shared_memory;
	पूर्ण

	अगर (ret < 0) अणु
		अगर (ret == -EINTR) अणु
			/*
			 * We can't वापस EINTR अगर any data was written,
			 * it's not POSIX. It is minimally acceptable
			 * to give a partial ग_लिखो, the way NFS करोes.
			 *
			 * It would be optimal to वापस all or nothing,
			 * but अगर a userspace ग_लिखो is bigger than
			 * an IO buffer, and the पूर्णांकerrupt occurs
			 * between buffer ग_लिखोs, that would not be
			 * possible.
			 */
			चयन (new_op->op_state - OP_VFS_STATE_GIVEN_UP) अणु
			/*
			 * If the op was रुकोing when the पूर्णांकerrupt
			 * occurred, then the client-core did not
			 * trigger the ग_लिखो.
			 */
			हाल OP_VFS_STATE_WAITING:
				अगर (*offset == 0)
					ret = -EINTR;
				अन्यथा
					ret = 0;
				अवरोध;
			/*
			 * If the op was in progress when the पूर्णांकerrupt
			 * occurred, then the client-core was able to
			 * trigger the ग_लिखो.
			 */
			हाल OP_VFS_STATE_INPROGR:
				अगर (type == ORANGEFS_IO_READ)
					ret = -EINTR;
				अन्यथा
					ret = total_size;
				अवरोध;
			शेष:
				gossip_err("%s: unexpected op state :%d:.\n",
					   __func__,
					   new_op->op_state);
				ret = 0;
				अवरोध;
			पूर्ण
			gossip_debug(GOSSIP_खाता_DEBUG,
				     "%s: got EINTR, state:%d: %p\n",
				     __func__,
				     new_op->op_state,
				     new_op);
		पूर्ण अन्यथा अणु
			gossip_err("%s: error in %s handle %pU, returning %zd\n",
				__func__,
				type == ORANGEFS_IO_READ ?
					"read from" : "write to",
				handle, ret);
		पूर्ण
		अगर (orangefs_cancel_op_in_progress(new_op))
			वापस ret;

		जाओ out;
	पूर्ण

	/*
	 * Stage 3: Post copy buffers from client-core's address space
	 */
	अगर (type == ORANGEFS_IO_READ && new_op->करोwncall.resp.io.amt_complete) अणु
		/*
		 * NOTE: the iovector can either contain addresses which
		 *       can futher be kernel-space or user-space addresses.
		 *       or it can poपूर्णांकers to काष्ठा page's
		 */

		copy_amount = new_op->करोwncall.resp.io.amt_complete;

		ret = orangefs_bufmap_copy_to_iovec(iter, buffer_index,
			copy_amount);
		अगर (ret < 0) अणु
			gossip_err("%s: Failed to copy-out buffers. Please make sure that the pvfs2-client is running (%ld)\n",
			    __func__, (दीर्घ)ret);
			जाओ out;
		पूर्ण
	पूर्ण
	gossip_debug(GOSSIP_खाता_DEBUG,
	    "%s(%pU): Amount %s, returned by the sys-io call:%d\n",
	    __func__,
	    handle,
	    type == ORANGEFS_IO_READ ?  "read" : "written",
	    (पूर्णांक)new_op->करोwncall.resp.io.amt_complete);

	ret = new_op->करोwncall.resp.io.amt_complete;

out:
	अगर (buffer_index >= 0) अणु
		orangefs_bufmap_put(buffer_index);
		gossip_debug(GOSSIP_खाता_DEBUG,
			"%s(%pU): PUT buffer_index %d\n",
			__func__, handle, buffer_index);
		buffer_index = -1;
	पूर्ण
	op_release(new_op);
	वापस ret;
पूर्ण

पूर्णांक orangefs_revalidate_mapping(काष्ठा inode *inode)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	अचिन्हित दीर्घ *bitlock = &orangefs_inode->bitlock;
	पूर्णांक ret;

	जबतक (1) अणु
		ret = रुको_on_bit(bitlock, 1, TASK_KILLABLE);
		अगर (ret)
			वापस ret;
		spin_lock(&inode->i_lock);
		अगर (test_bit(1, bitlock)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		अगर (!समय_beक्रमe(jअगरfies, orangefs_inode->mapping_समय))
			अवरोध;
		spin_unlock(&inode->i_lock);
		वापस 0;
	पूर्ण

	set_bit(1, bitlock);
	smp_wmb();
	spin_unlock(&inode->i_lock);

	unmap_mapping_range(mapping, 0, 0, 0);
	ret = filemap_ग_लिखो_and_रुको(mapping);
	अगर (!ret)
		ret = invalidate_inode_pages2(mapping);

	orangefs_inode->mapping_समय = jअगरfies +
	    orangefs_cache_समयout_msecs*HZ/1000;

	clear_bit(1, bitlock);
	smp_mb__after_atomic();
	wake_up_bit(bitlock, 1);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार orangefs_file_पढ़ो_iter(काष्ठा kiocb *iocb,
    काष्ठा iov_iter *iter)
अणु
	पूर्णांक ret;
	orangefs_stats.पढ़ोs++;

	करोwn_पढ़ो(&file_inode(iocb->ki_filp)->i_rwsem);
	ret = orangefs_revalidate_mapping(file_inode(iocb->ki_filp));
	अगर (ret)
		जाओ out;

	ret = generic_file_पढ़ो_iter(iocb, iter);
out:
	up_पढ़ो(&file_inode(iocb->ki_filp)->i_rwsem);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार orangefs_file_ग_लिखो_iter(काष्ठा kiocb *iocb,
    काष्ठा iov_iter *iter)
अणु
	पूर्णांक ret;
	orangefs_stats.ग_लिखोs++;

	अगर (iocb->ki_pos > i_size_पढ़ो(file_inode(iocb->ki_filp))) अणु
		ret = orangefs_revalidate_mapping(file_inode(iocb->ki_filp));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = generic_file_ग_लिखो_iter(iocb, iter);
	वापस ret;
पूर्ण

अटल vm_fault_t orangefs_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा file *file = vmf->vma->vm_file;
	पूर्णांक ret;
	ret = orangefs_inode_getattr(file->f_mapping->host,
	    ORANGEFS_GETATTR_SIZE);
	अगर (ret == -ESTALE)
		ret = -EIO;
	अगर (ret) अणु
		gossip_err("%s: orangefs_inode_getattr failed, "
		    "ret:%d:.\n", __func__, ret);
		वापस VM_FAULT_SIGBUS;
	पूर्ण
	वापस filemap_fault(vmf);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा orangefs_file_vm_ops = अणु
	.fault = orangefs_fault,
	.map_pages = filemap_map_pages,
	.page_mkग_लिखो = orangefs_page_mkग_लिखो,
पूर्ण;

/*
 * Memory map a region of a file.
 */
अटल पूर्णांक orangefs_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = orangefs_revalidate_mapping(file_inode(file));
	अगर (ret)
		वापस ret;

	gossip_debug(GOSSIP_खाता_DEBUG,
		     "orangefs_file_mmap: called on %pD\n", file);

	/* set the sequential पढ़ोahead hपूर्णांक */
	vma->vm_flags |= VM_SEQ_READ;
	vma->vm_flags &= ~VM_RAND_READ;

	file_accessed(file);
	vma->vm_ops = &orangefs_file_vm_ops;
	वापस 0;
पूर्ण

#घोषणा mapping_nrpages(idata) ((idata)->nrpages)

/*
 * Called to notअगरy the module that there are no more references to
 * this file (i.e. no processes have it खोलो).
 *
 * \नote Not called when each file is बंदd.
 */
अटल पूर्णांक orangefs_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	gossip_debug(GOSSIP_खाता_DEBUG,
		     "orangefs_file_release: called on %pD\n",
		     file);

	/*
	 * हटाओ all associated inode pages from the page cache and
	 * पढ़ोahead cache (अगर any); this क्रमces an expensive refresh of
	 * data क्रम the next caller of mmap (or 'get_block' accesses)
	 */
	अगर (file_inode(file) &&
	    file_inode(file)->i_mapping &&
	    mapping_nrpages(&file_inode(file)->i_data)) अणु
		अगर (orangefs_features & ORANGEFS_FEATURE_READAHEAD) अणु
			gossip_debug(GOSSIP_INODE_DEBUG,
			    "calling flush_racache on %pU\n",
			    get_khandle_from_ino(inode));
			flush_racache(inode);
			gossip_debug(GOSSIP_INODE_DEBUG,
			    "flush_racache finished\n");
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

/*
 * Push all data क्रम a specअगरic file onto permanent storage.
 */
अटल पूर्णांक orangefs_fsync(काष्ठा file *file,
		       loff_t start,
		       loff_t end,
		       पूर्णांक datasync)
अणु
	पूर्णांक ret;
	काष्ठा orangefs_inode_s *orangefs_inode =
		ORANGEFS_I(file_inode(file));
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;

	ret = filemap_ग_लिखो_and_रुको_range(file_inode(file)->i_mapping,
	    start, end);
	अगर (ret < 0)
		वापस ret;

	new_op = op_alloc(ORANGEFS_VFS_OP_FSYNC);
	अगर (!new_op)
		वापस -ENOMEM;
	new_op->upcall.req.fsync.refn = orangefs_inode->refn;

	ret = service_operation(new_op,
			"orangefs_fsync",
			get_पूर्णांकerruptible_flag(file_inode(file)));

	gossip_debug(GOSSIP_खाता_DEBUG,
		     "orangefs_fsync got return value of %d\n",
		     ret);

	op_release(new_op);
	वापस ret;
पूर्ण

/*
 * Change the file poपूर्णांकer position क्रम an instance of an खोलो file.
 *
 * \नote If .llseek is overriden, we must acquire lock as described in
 *       Documentation/fileप्रणालीs/locking.rst.
 *
 * Future upgrade could support SEEK_DATA and SEEK_HOLE but would
 * require much changes to the FS
 */
अटल loff_t orangefs_file_llseek(काष्ठा file *file, loff_t offset, पूर्णांक origin)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा inode *inode = file_inode(file);

	अगर (origin == अंत_से) अणु
		/*
		 * revalidate the inode's file size.
		 * NOTE: We are only पूर्णांकerested in file size here,
		 * so we set mask accordingly.
		 */
		ret = orangefs_inode_getattr(file->f_mapping->host,
		    ORANGEFS_GETATTR_SIZE);
		अगर (ret == -ESTALE)
			ret = -EIO;
		अगर (ret) अणु
			gossip_debug(GOSSIP_खाता_DEBUG,
				     "%s:%s:%d calling make bad inode\n",
				     __खाता__,
				     __func__,
				     __LINE__);
			वापस ret;
		पूर्ण
	पूर्ण

	gossip_debug(GOSSIP_खाता_DEBUG,
		     "orangefs_file_llseek: offset is %ld | origin is %d"
		     " | inode size is %lu\n",
		     (दीर्घ)offset,
		     origin,
		     (अचिन्हित दीर्घ)i_size_पढ़ो(inode));

	वापस generic_file_llseek(file, offset, origin);
पूर्ण

/*
 * Support local locks (locks that only this kernel knows about)
 * अगर Orangefs was mounted -o local_lock.
 */
अटल पूर्णांक orangefs_lock(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	पूर्णांक rc = -EINVAL;

	अगर (ORANGEFS_SB(file_inode(filp)->i_sb)->flags & ORANGEFS_OPT_LOCAL_LOCK) अणु
		अगर (cmd == F_GETLK) अणु
			rc = 0;
			posix_test_lock(filp, fl);
		पूर्ण अन्यथा अणु
			rc = posix_lock_file(filp, fl, शून्य);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक orangefs_flush(काष्ठा file *file, fl_owner_t id)
अणु
	/*
	 * This is vfs_fsync_range(file, 0, Lदीर्घ_उच्च, 0) without the
	 * service_operation in orangefs_fsync.
	 *
	 * Do not send fsync to OrangeFS server on a बंद.  Do send fsync
	 * on an explicit fsync call.  This duplicates historical OrangeFS
	 * behavior.
	 */
	पूर्णांक r;

	r = filemap_ग_लिखो_and_रुको_range(file->f_mapping, 0, Lदीर्घ_उच्च);
	अगर (r > 0)
		वापस 0;
	अन्यथा
		वापस r;
पूर्ण

/** ORANGEFS implementation of VFS file operations */
स्थिर काष्ठा file_operations orangefs_file_operations = अणु
	.llseek		= orangefs_file_llseek,
	.पढ़ो_iter	= orangefs_file_पढ़ो_iter,
	.ग_लिखो_iter	= orangefs_file_ग_लिखो_iter,
	.lock		= orangefs_lock,
	.mmap		= orangefs_file_mmap,
	.खोलो		= generic_file_खोलो,
	.splice_पढ़ो    = generic_file_splice_पढ़ो,
	.splice_ग_लिखो   = iter_file_splice_ग_लिखो,
	.flush		= orangefs_flush,
	.release	= orangefs_file_release,
	.fsync		= orangefs_fsync,
पूर्ण;
