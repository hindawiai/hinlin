<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * High-level sync()-related operations
 */

#समावेश <linux/kernel.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/namei.h>
#समावेश <linux/sched.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/linkage.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/backing-dev.h>
#समावेश "internal.h"

#घोषणा VALID_FLAGS (SYNC_खाता_RANGE_WAIT_BEFORE|SYNC_खाता_RANGE_WRITE| \
			SYNC_खाता_RANGE_WAIT_AFTER)

/*
 * Do the fileप्रणाली syncing work. For simple fileप्रणालीs
 * ग_लिखोback_inodes_sb(sb) just dirties buffers with inodes so we have to
 * submit IO क्रम these buffers via __sync_blockdev(). This also speeds up the
 * रुको == 1 हाल since in that हाल ग_लिखो_inode() functions करो
 * sync_dirty_buffer() and thus effectively ग_लिखो one block at a समय.
 */
अटल पूर्णांक __sync_fileप्रणाली(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	अगर (रुको)
		sync_inodes_sb(sb);
	अन्यथा
		ग_लिखोback_inodes_sb(sb, WB_REASON_SYNC);

	अगर (sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, रुको);
	वापस __sync_blockdev(sb->s_bdev, रुको);
पूर्ण

/*
 * Write out and रुको upon all dirty data associated with this
 * superblock.  Fileप्रणाली data as well as the underlying block
 * device.  Takes the superblock lock.
 */
पूर्णांक sync_fileप्रणाली(काष्ठा super_block *sb)
अणु
	पूर्णांक ret;

	/*
	 * We need to be रक्षित against the fileप्रणाली going from
	 * r/o to r/w or vice versa.
	 */
	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	/*
	 * No poपूर्णांक in syncing out anything अगर the fileप्रणाली is पढ़ो-only.
	 */
	अगर (sb_rकरोnly(sb))
		वापस 0;

	ret = __sync_fileप्रणाली(sb, 0);
	अगर (ret < 0)
		वापस ret;
	वापस __sync_fileप्रणाली(sb, 1);
पूर्ण
EXPORT_SYMBOL(sync_fileप्रणाली);

अटल व्योम sync_inodes_one_sb(काष्ठा super_block *sb, व्योम *arg)
अणु
	अगर (!sb_rकरोnly(sb))
		sync_inodes_sb(sb);
पूर्ण

अटल व्योम sync_fs_one_sb(काष्ठा super_block *sb, व्योम *arg)
अणु
	अगर (!sb_rकरोnly(sb) && !(sb->s_अगरlags & SB_I_SKIP_SYNC) &&
	    sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, *(पूर्णांक *)arg);
पूर्ण

अटल व्योम fdataग_लिखो_one_bdev(काष्ठा block_device *bdev, व्योम *arg)
अणु
	filemap_fdataग_लिखो(bdev->bd_inode->i_mapping);
पूर्ण

अटल व्योम fdataरुको_one_bdev(काष्ठा block_device *bdev, व्योम *arg)
अणु
	/*
	 * We keep the error status of inभागidual mapping so that
	 * applications can catch the ग_लिखोback error using fsync(2).
	 * See filemap_fdataरुको_keep_errors() क्रम details.
	 */
	filemap_fdataरुको_keep_errors(bdev->bd_inode->i_mapping);
पूर्ण

/*
 * Sync everything. We start by waking flusher thपढ़ोs so that most of
 * ग_लिखोback runs on all devices in parallel. Then we sync all inodes reliably
 * which effectively also रुकोs क्रम all flusher thपढ़ोs to finish करोing
 * ग_लिखोback. At this poपूर्णांक all data is on disk so metadata should be stable
 * and we tell fileप्रणालीs to sync their metadata via ->sync_fs() calls.
 * Finally, we ग_लिखोout all block devices because some fileप्रणालीs (e.g. ext2)
 * just ग_लिखो metadata (such as inodes or biपंचांगaps) to block device page cache
 * and करो not sync it on their own in ->sync_fs().
 */
व्योम ksys_sync(व्योम)
अणु
	पूर्णांक noरुको = 0, रुको = 1;

	wakeup_flusher_thपढ़ोs(WB_REASON_SYNC);
	iterate_supers(sync_inodes_one_sb, शून्य);
	iterate_supers(sync_fs_one_sb, &noरुको);
	iterate_supers(sync_fs_one_sb, &रुको);
	iterate_bdevs(fdataग_लिखो_one_bdev, शून्य);
	iterate_bdevs(fdataरुको_one_bdev, शून्य);
	अगर (unlikely(laptop_mode))
		laptop_sync_completion();
पूर्ण

SYSCALL_DEFINE0(sync)
अणु
	ksys_sync();
	वापस 0;
पूर्ण

अटल व्योम करो_sync_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक noरुको = 0;

	/*
	 * Sync twice to reduce the possibility we skipped some inodes / pages
	 * because they were temporarily locked
	 */
	iterate_supers(sync_inodes_one_sb, &noरुको);
	iterate_supers(sync_fs_one_sb, &noरुको);
	iterate_bdevs(fdataग_लिखो_one_bdev, शून्य);
	iterate_supers(sync_inodes_one_sb, &noरुको);
	iterate_supers(sync_fs_one_sb, &noरुको);
	iterate_bdevs(fdataग_लिखो_one_bdev, शून्य);
	prपूर्णांकk("Emergency Sync complete\n");
	kमुक्त(work);
पूर्ण

व्योम emergency_sync(व्योम)
अणु
	काष्ठा work_काष्ठा *work;

	work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
	अगर (work) अणु
		INIT_WORK(work, करो_sync_work);
		schedule_work(work);
	पूर्ण
पूर्ण

/*
 * sync a single super
 */
SYSCALL_DEFINE1(syncfs, पूर्णांक, fd)
अणु
	काष्ठा fd f = fdget(fd);
	काष्ठा super_block *sb;
	पूर्णांक ret, ret2;

	अगर (!f.file)
		वापस -EBADF;
	sb = f.file->f_path.dentry->d_sb;

	करोwn_पढ़ो(&sb->s_umount);
	ret = sync_fileप्रणाली(sb);
	up_पढ़ो(&sb->s_umount);

	ret2 = errseq_check_and_advance(&sb->s_wb_err, &f.file->f_sb_err);

	fdput(f);
	वापस ret ? ret : ret2;
पूर्ण

/**
 * vfs_fsync_range - helper to sync a range of data & metadata to disk
 * @file:		file to sync
 * @start:		offset in bytes of the beginning of data range to sync
 * @end:		offset in bytes of the end of data range (inclusive)
 * @datasync:		perक्रमm only datasync
 *
 * Write back data in range @start..@end and metadata क्रम @file to disk.  If
 * @datasync is set only metadata needed to access modअगरied file data is
 * written.
 */
पूर्णांक vfs_fsync_range(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;

	अगर (!file->f_op->fsync)
		वापस -EINVAL;
	अगर (!datasync && (inode->i_state & I_सूचीTY_TIME))
		mark_inode_dirty_sync(inode);
	वापस file->f_op->fsync(file, start, end, datasync);
पूर्ण
EXPORT_SYMBOL(vfs_fsync_range);

/**
 * vfs_fsync - perक्रमm a fsync or fdatasync on a file
 * @file:		file to sync
 * @datasync:		only perक्रमm a fdatasync operation
 *
 * Write back data and metadata क्रम @file to disk.  If @datasync is
 * set only metadata needed to access modअगरied file data is written.
 */
पूर्णांक vfs_fsync(काष्ठा file *file, पूर्णांक datasync)
अणु
	वापस vfs_fsync_range(file, 0, Lदीर्घ_उच्च, datasync);
पूर्ण
EXPORT_SYMBOL(vfs_fsync);

अटल पूर्णांक करो_fsync(अचिन्हित पूर्णांक fd, पूर्णांक datasync)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक ret = -EBADF;

	अगर (f.file) अणु
		ret = vfs_fsync(f.file, datasync);
		fdput(f);
	पूर्ण
	वापस ret;
पूर्ण

SYSCALL_DEFINE1(fsync, अचिन्हित पूर्णांक, fd)
अणु
	वापस करो_fsync(fd, 0);
पूर्ण

SYSCALL_DEFINE1(fdatasync, अचिन्हित पूर्णांक, fd)
अणु
	वापस करो_fsync(fd, 1);
पूर्ण

पूर्णांक sync_file_range(काष्ठा file *file, loff_t offset, loff_t nbytes,
		    अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;
	काष्ठा address_space *mapping;
	loff_t endbyte;			/* inclusive */
	umode_t i_mode;

	ret = -EINVAL;
	अगर (flags & ~VALID_FLAGS)
		जाओ out;

	endbyte = offset + nbytes;

	अगर ((s64)offset < 0)
		जाओ out;
	अगर ((s64)endbyte < 0)
		जाओ out;
	अगर (endbyte < offset)
		जाओ out;

	अगर (माप(pgoff_t) == 4) अणु
		अगर (offset >= (0x100000000ULL << PAGE_SHIFT)) अणु
			/*
			 * The range starts outside a 32 bit machine's
			 * pagecache addressing capabilities.  Let it "succeed"
			 */
			ret = 0;
			जाओ out;
		पूर्ण
		अगर (endbyte >= (0x100000000ULL << PAGE_SHIFT)) अणु
			/*
			 * Out to खातापूर्ण
			 */
			nbytes = 0;
		पूर्ण
	पूर्ण

	अगर (nbytes == 0)
		endbyte = Lदीर्घ_उच्च;
	अन्यथा
		endbyte--;		/* inclusive */

	i_mode = file_inode(file)->i_mode;
	ret = -ESPIPE;
	अगर (!S_ISREG(i_mode) && !S_ISBLK(i_mode) && !S_ISसूची(i_mode) &&
			!S_ISLNK(i_mode))
		जाओ out;

	mapping = file->f_mapping;
	ret = 0;
	अगर (flags & SYNC_खाता_RANGE_WAIT_BEFORE) अणु
		ret = file_fdataरुको_range(file, offset, endbyte);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (flags & SYNC_खाता_RANGE_WRITE) अणु
		पूर्णांक sync_mode = WB_SYNC_NONE;

		अगर ((flags & SYNC_खाता_RANGE_WRITE_AND_WAIT) ==
			     SYNC_खाता_RANGE_WRITE_AND_WAIT)
			sync_mode = WB_SYNC_ALL;

		ret = __filemap_fdataग_लिखो_range(mapping, offset, endbyte,
						 sync_mode);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (flags & SYNC_खाता_RANGE_WAIT_AFTER)
		ret = file_fdataरुको_range(file, offset, endbyte);

out:
	वापस ret;
पूर्ण

/*
 * ksys_sync_file_range() permits finely controlled syncing over a segment of
 * a file in the range offset .. (offset+nbytes-1) inclusive.  If nbytes is
 * zero then ksys_sync_file_range() will operate from offset out to खातापूर्ण.
 *
 * The flag bits are:
 *
 * SYNC_खाता_RANGE_WAIT_BEFORE: रुको upon ग_लिखोout of all pages in the range
 * beक्रमe perक्रमming the ग_लिखो.
 *
 * SYNC_खाता_RANGE_WRITE: initiate ग_लिखोout of all those dirty pages in the
 * range which are not presently under ग_लिखोback. Note that this may block क्रम
 * signअगरicant periods due to exhaustion of disk request काष्ठाures.
 *
 * SYNC_खाता_RANGE_WAIT_AFTER: रुको upon ग_लिखोout of all pages in the range
 * after perक्रमming the ग_लिखो.
 *
 * Useful combinations of the flag bits are:
 *
 * SYNC_खाता_RANGE_WAIT_BEFORE|SYNC_खाता_RANGE_WRITE: ensures that all pages
 * in the range which were dirty on entry to ksys_sync_file_range() are placed
 * under ग_लिखोout.  This is a start-ग_लिखो-क्रम-data-पूर्णांकegrity operation.
 *
 * SYNC_खाता_RANGE_WRITE: start ग_लिखोout of all dirty pages in the range which
 * are not presently under ग_लिखोout.  This is an asynchronous flush-to-disk
 * operation.  Not suitable क्रम data पूर्णांकegrity operations.
 *
 * SYNC_खाता_RANGE_WAIT_BEFORE (or SYNC_खाता_RANGE_WAIT_AFTER): रुको क्रम
 * completion of ग_लिखोout of all pages in the range.  This will be used after an
 * earlier SYNC_खाता_RANGE_WAIT_BEFORE|SYNC_खाता_RANGE_WRITE operation to रुको
 * क्रम that operation to complete and to वापस the result.
 *
 * SYNC_खाता_RANGE_WAIT_BEFORE|SYNC_खाता_RANGE_WRITE|SYNC_खाता_RANGE_WAIT_AFTER
 * (a.k.a. SYNC_खाता_RANGE_WRITE_AND_WAIT):
 * a traditional sync() operation.  This is a ग_लिखो-क्रम-data-पूर्णांकegrity operation
 * which will ensure that all pages in the range which were dirty on entry to
 * ksys_sync_file_range() are written to disk.  It should be noted that disk
 * caches are not flushed by this call, so there are no guarantees here that the
 * data will be available on disk after a crash.
 *
 *
 * SYNC_खाता_RANGE_WAIT_BEFORE and SYNC_खाता_RANGE_WAIT_AFTER will detect any
 * I/O errors or ENOSPC conditions and will वापस those to the caller, after
 * clearing the EIO and ENOSPC flags in the address_space.
 *
 * It should be noted that none of these operations ग_लिखो out the file's
 * metadata.  So unless the application is strictly perक्रमming overग_लिखोs of
 * alपढ़ोy-instantiated disk blocks, there are no guarantees here that the data
 * will be available after a crash.
 */
पूर्णांक ksys_sync_file_range(पूर्णांक fd, loff_t offset, loff_t nbytes,
			 अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;
	काष्ठा fd f;

	ret = -EBADF;
	f = fdget(fd);
	अगर (f.file)
		ret = sync_file_range(f.file, offset, nbytes, flags);

	fdput(f);
	वापस ret;
पूर्ण

SYSCALL_DEFINE4(sync_file_range, पूर्णांक, fd, loff_t, offset, loff_t, nbytes,
				अचिन्हित पूर्णांक, flags)
अणु
	वापस ksys_sync_file_range(fd, offset, nbytes, flags);
पूर्ण

/* It would be nice अगर people remember that not all the world's an i386
   when they पूर्णांकroduce new प्रणाली calls */
SYSCALL_DEFINE4(sync_file_range2, पूर्णांक, fd, अचिन्हित पूर्णांक, flags,
				 loff_t, offset, loff_t, nbytes)
अणु
	वापस ksys_sync_file_range(fd, offset, nbytes, flags);
पूर्ण
