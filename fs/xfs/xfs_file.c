<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_ioctl.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_log.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_pnfs.h"
#समावेश "xfs_iomap.h"
#समावेश "xfs_reflink.h"

#समावेश <linux/fभाग.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mman.h>
#समावेश <linux/fadvise.h>
#समावेश <linux/mount.h>

अटल स्थिर काष्ठा vm_operations_काष्ठा xfs_file_vm_ops;

/*
 * Decide अगर the given file range is aligned to the size of the fundamental
 * allocation unit क्रम the file.
 */
अटल bool
xfs_is_falloc_aligned(
	काष्ठा xfs_inode	*ip,
	loff_t			pos,
	दीर्घ दीर्घ पूर्णांक		len)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	uपूर्णांक64_t		mask;

	अगर (XFS_IS_REALTIME_INODE(ip)) अणु
		अगर (!is_घातer_of_2(mp->m_sb.sb_rextsize)) अणु
			u64	rextbytes;
			u32	mod;

			rextbytes = XFS_FSB_TO_B(mp, mp->m_sb.sb_rextsize);
			भाग_u64_rem(pos, rextbytes, &mod);
			अगर (mod)
				वापस false;
			भाग_u64_rem(len, rextbytes, &mod);
			वापस mod == 0;
		पूर्ण
		mask = XFS_FSB_TO_B(mp, mp->m_sb.sb_rextsize) - 1;
	पूर्ण अन्यथा अणु
		mask = mp->m_sb.sb_blocksize - 1;
	पूर्ण

	वापस !((pos | len) & mask);
पूर्ण

पूर्णांक
xfs_update_pपुनः_स्मृति_flags(
	काष्ठा xfs_inode	*ip,
	क्रमागत xfs_pपुनः_स्मृति_flags	flags)
अणु
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	error = xfs_trans_alloc(ip->i_mount, &M_RES(ip->i_mount)->tr_ग_लिखोid,
			0, 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

	अगर (!(flags & XFS_PREALLOC_INVISIBLE)) अणु
		VFS_I(ip)->i_mode &= ~S_ISUID;
		अगर (VFS_I(ip)->i_mode & S_IXGRP)
			VFS_I(ip)->i_mode &= ~S_ISGID;
		xfs_trans_ichgसमय(tp, ip, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	पूर्ण

	अगर (flags & XFS_PREALLOC_SET)
		ip->i_dअगरlags |= XFS_DIFLAG_PREALLOC;
	अगर (flags & XFS_PREALLOC_CLEAR)
		ip->i_dअगरlags &= ~XFS_DIFLAG_PREALLOC;

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	अगर (flags & XFS_PREALLOC_SYNC)
		xfs_trans_set_sync(tp);
	वापस xfs_trans_commit(tp);
पूर्ण

/*
 * Fsync operations on directories are much simpler than on regular files,
 * as there is no file data to flush, and thus also no need क्रम explicit
 * cache flush operations, and there are no non-transaction metadata updates
 * on directories either.
 */
STATIC पूर्णांक
xfs_dir_fsync(
	काष्ठा file		*file,
	loff_t			start,
	loff_t			end,
	पूर्णांक			datasync)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(file->f_mapping->host);

	trace_xfs_dir_fsync(ip);
	वापस xfs_log_क्रमce_inode(ip);
पूर्ण

अटल xfs_lsn_t
xfs_fsync_lsn(
	काष्ठा xfs_inode	*ip,
	bool			datasync)
अणु
	अगर (!xfs_ipincount(ip))
		वापस 0;
	अगर (datasync && !(ip->i_itemp->ili_fsync_fields & ~XFS_ILOG_TIMESTAMP))
		वापस 0;
	वापस ip->i_itemp->ili_last_lsn;
पूर्ण

/*
 * All metadata updates are logged, which means that we just have to flush the
 * log up to the latest LSN that touched the inode.
 *
 * If we have concurrent fsync/fdatasync() calls, we need them to all block on
 * the log क्रमce beक्रमe we clear the ili_fsync_fields field. This ensures that
 * we करोn't get a racing sync operation that करोes not रुको क्रम the metadata to
 * hit the journal beक्रमe वापसing.  If we race with clearing ili_fsync_fields,
 * then all that will happen is the log क्रमce will करो nothing as the lsn will
 * alपढ़ोy be on disk.  We can't race with setting ili_fsync_fields because that
 * is करोne under XFS_ILOCK_EXCL, and that can't happen because we hold the lock
 * shared until after the ili_fsync_fields is cleared.
 */
अटल  पूर्णांक
xfs_fsync_flush_log(
	काष्ठा xfs_inode	*ip,
	bool			datasync,
	पूर्णांक			*log_flushed)
अणु
	पूर्णांक			error = 0;
	xfs_lsn_t		lsn;

	xfs_ilock(ip, XFS_ILOCK_SHARED);
	lsn = xfs_fsync_lsn(ip, datasync);
	अगर (lsn) अणु
		error = xfs_log_क्रमce_lsn(ip->i_mount, lsn, XFS_LOG_SYNC,
					  log_flushed);

		spin_lock(&ip->i_itemp->ili_lock);
		ip->i_itemp->ili_fsync_fields = 0;
		spin_unlock(&ip->i_itemp->ili_lock);
	पूर्ण
	xfs_iunlock(ip, XFS_ILOCK_SHARED);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_file_fsync(
	काष्ठा file		*file,
	loff_t			start,
	loff_t			end,
	पूर्णांक			datasync)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(file->f_mapping->host);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			error = 0;
	पूर्णांक			log_flushed = 0;

	trace_xfs_file_fsync(ip);

	error = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (error)
		वापस error;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	xfs_अगरlags_clear(ip, XFS_ITRUNCATED);

	/*
	 * If we have an RT and/or log subvolume we need to make sure to flush
	 * the ग_लिखो cache the device used क्रम file data first.  This is to
	 * ensure newly written file data make it to disk beक्रमe logging the new
	 * inode size in हाल of an extending ग_लिखो.
	 */
	अगर (XFS_IS_REALTIME_INODE(ip))
		xfs_blkdev_issue_flush(mp->m_rtdev_targp);
	अन्यथा अगर (mp->m_logdev_targp != mp->m_ddev_targp)
		xfs_blkdev_issue_flush(mp->m_ddev_targp);

	/*
	 * Any inode that has dirty modअगरications in the log is pinned.  The
	 * racy check here क्रम a pinned inode जबतक not catch modअगरications
	 * that happen concurrently to the fsync call, but fsync semantics
	 * only require to sync previously completed I/O.
	 */
	अगर (xfs_ipincount(ip))
		error = xfs_fsync_flush_log(ip, datasync, &log_flushed);

	/*
	 * If we only have a single device, and the log क्रमce about was
	 * a no-op we might have to flush the data device cache here.
	 * This can only happen क्रम fdatasync/O_DSYNC अगर we were overwriting
	 * an alपढ़ोy allocated file and thus करो not have any metadata to
	 * commit.
	 */
	अगर (!log_flushed && !XFS_IS_REALTIME_INODE(ip) &&
	    mp->m_logdev_targp == mp->m_ddev_targp)
		xfs_blkdev_issue_flush(mp->m_ddev_targp);

	वापस error;
पूर्ण

अटल पूर्णांक
xfs_ilock_iocb(
	काष्ठा kiocb		*iocb,
	अचिन्हित पूर्णांक		lock_mode)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(file_inode(iocb->ki_filp));

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!xfs_ilock_noरुको(ip, lock_mode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		xfs_ilock(ip, lock_mode);
	पूर्ण

	वापस 0;
पूर्ण

STATIC sमाप_प्रकार
xfs_file_dio_पढ़ो(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*to)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(file_inode(iocb->ki_filp));
	sमाप_प्रकार			ret;

	trace_xfs_file_direct_पढ़ो(iocb, to);

	अगर (!iov_iter_count(to))
		वापस 0; /* skip aसमय */

	file_accessed(iocb->ki_filp);

	ret = xfs_ilock_iocb(iocb, XFS_IOLOCK_SHARED);
	अगर (ret)
		वापस ret;
	ret = iomap_dio_rw(iocb, to, &xfs_पढ़ो_iomap_ops, शून्य, 0);
	xfs_iunlock(ip, XFS_IOLOCK_SHARED);

	वापस ret;
पूर्ण

अटल noअंतरभूत sमाप_प्रकार
xfs_file_dax_पढ़ो(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*to)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(iocb->ki_filp->f_mapping->host);
	sमाप_प्रकार			ret = 0;

	trace_xfs_file_dax_पढ़ो(iocb, to);

	अगर (!iov_iter_count(to))
		वापस 0; /* skip aसमय */

	ret = xfs_ilock_iocb(iocb, XFS_IOLOCK_SHARED);
	अगर (ret)
		वापस ret;
	ret = dax_iomap_rw(iocb, to, &xfs_पढ़ो_iomap_ops);
	xfs_iunlock(ip, XFS_IOLOCK_SHARED);

	file_accessed(iocb->ki_filp);
	वापस ret;
पूर्ण

STATIC sमाप_प्रकार
xfs_file_buffered_पढ़ो(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*to)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(file_inode(iocb->ki_filp));
	sमाप_प्रकार			ret;

	trace_xfs_file_buffered_पढ़ो(iocb, to);

	ret = xfs_ilock_iocb(iocb, XFS_IOLOCK_SHARED);
	अगर (ret)
		वापस ret;
	ret = generic_file_पढ़ो_iter(iocb, to);
	xfs_iunlock(ip, XFS_IOLOCK_SHARED);

	वापस ret;
पूर्ण

STATIC sमाप_प्रकार
xfs_file_पढ़ो_iter(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*to)
अणु
	काष्ठा inode		*inode = file_inode(iocb->ki_filp);
	काष्ठा xfs_mount	*mp = XFS_I(inode)->i_mount;
	sमाप_प्रकार			ret = 0;

	XFS_STATS_INC(mp, xs_पढ़ो_calls);

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	अगर (IS_DAX(inode))
		ret = xfs_file_dax_पढ़ो(iocb, to);
	अन्यथा अगर (iocb->ki_flags & IOCB_सूचीECT)
		ret = xfs_file_dio_पढ़ो(iocb, to);
	अन्यथा
		ret = xfs_file_buffered_पढ़ो(iocb, to);

	अगर (ret > 0)
		XFS_STATS_ADD(mp, xs_पढ़ो_bytes, ret);
	वापस ret;
पूर्ण

/*
 * Common pre-ग_लिखो limit and setup checks.
 *
 * Called with the iolocked held either shared and exclusive according to
 * @iolock, and वापसs with it held.  Might upgrade the iolock to exclusive
 * अगर called क्रम a direct ग_लिखो beyond i_size.
 */
STATIC sमाप_प्रकार
xfs_file_ग_लिखो_checks(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*from,
	पूर्णांक			*iolock)
अणु
	काष्ठा file		*file = iocb->ki_filp;
	काष्ठा inode		*inode = file->f_mapping->host;
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	sमाप_प्रकार			error = 0;
	माप_प्रकार			count = iov_iter_count(from);
	bool			drained_dio = false;
	loff_t			isize;

restart:
	error = generic_ग_लिखो_checks(iocb, from);
	अगर (error <= 0)
		वापस error;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		error = अवरोध_layout(inode, false);
		अगर (error == -EWOULDBLOCK)
			error = -EAGAIN;
	पूर्ण अन्यथा अणु
		error = xfs_अवरोध_layouts(inode, iolock, BREAK_WRITE);
	पूर्ण

	अगर (error)
		वापस error;

	/*
	 * For changing security info in file_हटाओ_privs() we need i_rwsem
	 * exclusively.
	 */
	अगर (*iolock == XFS_IOLOCK_SHARED && !IS_NOSEC(inode)) अणु
		xfs_iunlock(ip, *iolock);
		*iolock = XFS_IOLOCK_EXCL;
		error = xfs_ilock_iocb(iocb, *iolock);
		अगर (error) अणु
			*iolock = 0;
			वापस error;
		पूर्ण
		जाओ restart;
	पूर्ण
	/*
	 * If the offset is beyond the size of the file, we need to zero any
	 * blocks that fall between the existing खातापूर्ण and the start of this
	 * ग_लिखो.  If zeroing is needed and we are currently holding the
	 * iolock shared, we need to update it to exclusive which implies
	 * having to reकरो all checks beक्रमe.
	 *
	 * We need to serialise against खातापूर्ण updates that occur in IO
	 * completions here. We want to make sure that nobody is changing the
	 * size जबतक we करो this check until we have placed an IO barrier (i.e.
	 * hold the XFS_IOLOCK_EXCL) that prevents new IO from being dispatched.
	 * The spinlock effectively क्रमms a memory barrier once we have the
	 * XFS_IOLOCK_EXCL so we are guaranteed to see the latest खातापूर्ण value
	 * and hence be able to correctly determine अगर we need to run zeroing.
	 */
	spin_lock(&ip->i_flags_lock);
	isize = i_size_पढ़ो(inode);
	अगर (iocb->ki_pos > isize) अणु
		spin_unlock(&ip->i_flags_lock);

		अगर (iocb->ki_flags & IOCB_NOWAIT)
			वापस -EAGAIN;

		अगर (!drained_dio) अणु
			अगर (*iolock == XFS_IOLOCK_SHARED) अणु
				xfs_iunlock(ip, *iolock);
				*iolock = XFS_IOLOCK_EXCL;
				xfs_ilock(ip, *iolock);
				iov_iter_reexpand(from, count);
			पूर्ण
			/*
			 * We now have an IO submission barrier in place, but
			 * AIO can करो खातापूर्ण updates during IO completion and hence
			 * we now need to रुको क्रम all of them to drain. Non-AIO
			 * DIO will have drained beक्रमe we are given the
			 * XFS_IOLOCK_EXCL, and so क्रम most हालs this रुको is a
			 * no-op.
			 */
			inode_dio_रुको(inode);
			drained_dio = true;
			जाओ restart;
		पूर्ण
	
		trace_xfs_zero_eof(ip, isize, iocb->ki_pos - isize);
		error = iomap_zero_range(inode, isize, iocb->ki_pos - isize,
				शून्य, &xfs_buffered_ग_लिखो_iomap_ops);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा
		spin_unlock(&ip->i_flags_lock);

	वापस file_modअगरied(file);
पूर्ण

अटल पूर्णांक
xfs_dio_ग_लिखो_end_io(
	काष्ठा kiocb		*iocb,
	sमाप_प्रकार			size,
	पूर्णांक			error,
	अचिन्हित		flags)
अणु
	काष्ठा inode		*inode = file_inode(iocb->ki_filp);
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	loff_t			offset = iocb->ki_pos;
	अचिन्हित पूर्णांक		nofs_flag;

	trace_xfs_end_io_direct_ग_लिखो(ip, offset, size);

	अगर (XFS_FORCED_SHUTDOWN(ip->i_mount))
		वापस -EIO;

	अगर (error)
		वापस error;
	अगर (!size)
		वापस 0;

	/*
	 * Capture amount written on completion as we can't reliably account
	 * क्रम it on submission.
	 */
	XFS_STATS_ADD(ip->i_mount, xs_ग_लिखो_bytes, size);

	/*
	 * We can allocate memory here जबतक करोing ग_लिखोback on behalf of
	 * memory reclaim.  To aव्योम memory allocation deadlocks set the
	 * task-wide nofs context क्रम the following operations.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();

	अगर (flags & IOMAP_DIO_COW) अणु
		error = xfs_reflink_end_cow(ip, offset, size);
		अगर (error)
			जाओ out;
	पूर्ण

	/*
	 * Unwritten conversion updates the in-core isize after extent
	 * conversion but beक्रमe updating the on-disk size. Updating isize any
	 * earlier allows a racing dio पढ़ो to find unwritten extents beक्रमe
	 * they are converted.
	 */
	अगर (flags & IOMAP_DIO_UNWRITTEN) अणु
		error = xfs_iomap_ग_लिखो_unwritten(ip, offset, size, true);
		जाओ out;
	पूर्ण

	/*
	 * We need to update the in-core inode size here so that we करोn't end up
	 * with the on-disk inode size being outside the in-core inode size. We
	 * have no other method of updating खातापूर्ण क्रम AIO, so always करो it here
	 * अगर necessary.
	 *
	 * We need to lock the test/set खातापूर्ण update as we can be racing with
	 * other IO completions here to update the खातापूर्ण. Failing to serialise
	 * here can result in खातापूर्ण moving backwards and Bad Things Happen when
	 * that occurs.
	 */
	spin_lock(&ip->i_flags_lock);
	अगर (offset + size > i_size_पढ़ो(inode)) अणु
		i_size_ग_लिखो(inode, offset + size);
		spin_unlock(&ip->i_flags_lock);
		error = xfs_setfilesize(ip, offset, size);
	पूर्ण अन्यथा अणु
		spin_unlock(&ip->i_flags_lock);
	पूर्ण

out:
	meदो_स्मृति_nofs_restore(nofs_flag);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा iomap_dio_ops xfs_dio_ग_लिखो_ops = अणु
	.end_io		= xfs_dio_ग_लिखो_end_io,
पूर्ण;

/*
 * Handle block aligned direct I/O ग_लिखोs
 */
अटल noअंतरभूत sमाप_प्रकार
xfs_file_dio_ग_लिखो_aligned(
	काष्ठा xfs_inode	*ip,
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*from)
अणु
	पूर्णांक			iolock = XFS_IOLOCK_SHARED;
	sमाप_प्रकार			ret;

	ret = xfs_ilock_iocb(iocb, iolock);
	अगर (ret)
		वापस ret;
	ret = xfs_file_ग_लिखो_checks(iocb, from, &iolock);
	अगर (ret)
		जाओ out_unlock;

	/*
	 * We करोn't need to hold the IOLOCK exclusively across the IO, so demote
	 * the iolock back to shared अगर we had to take the exclusive lock in
	 * xfs_file_ग_लिखो_checks() क्रम other reasons.
	 */
	अगर (iolock == XFS_IOLOCK_EXCL) अणु
		xfs_ilock_demote(ip, XFS_IOLOCK_EXCL);
		iolock = XFS_IOLOCK_SHARED;
	पूर्ण
	trace_xfs_file_direct_ग_लिखो(iocb, from);
	ret = iomap_dio_rw(iocb, from, &xfs_direct_ग_लिखो_iomap_ops,
			   &xfs_dio_ग_लिखो_ops, 0);
out_unlock:
	अगर (iolock)
		xfs_iunlock(ip, iolock);
	वापस ret;
पूर्ण

/*
 * Handle block unaligned direct I/O ग_लिखोs
 *
 * In most हालs direct I/O ग_लिखोs will be करोne holding IOLOCK_SHARED, allowing
 * them to be करोne in parallel with पढ़ोs and other direct I/O ग_लिखोs.  However,
 * अगर the I/O is not aligned to fileप्रणाली blocks, the direct I/O layer may need
 * to करो sub-block zeroing and that requires serialisation against other direct
 * I/O to the same block.  In this हाल we need to serialise the submission of
 * the unaligned I/O so that we करोn't get racing block zeroing in the dio layer.
 * In the हाल where sub-block zeroing is not required, we can करो concurrent
 * sub-block dios to the same block successfully.
 *
 * Optimistically submit the I/O using the shared lock first, but use the
 * IOMAP_DIO_OVERWRITE_ONLY flag to tell the lower layers to वापस -EAGAIN
 * अगर block allocation or partial block zeroing would be required.  In that हाल
 * we try again with the exclusive lock.
 */
अटल noअंतरभूत sमाप_प्रकार
xfs_file_dio_ग_लिखो_unaligned(
	काष्ठा xfs_inode	*ip,
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*from)
अणु
	माप_प्रकार			isize = i_size_पढ़ो(VFS_I(ip));
	माप_प्रकार			count = iov_iter_count(from);
	पूर्णांक			iolock = XFS_IOLOCK_SHARED;
	अचिन्हित पूर्णांक		flags = IOMAP_DIO_OVERWRITE_ONLY;
	sमाप_प्रकार			ret;

	/*
	 * Extending ग_लिखोs need exclusivity because of the sub-block zeroing
	 * that the DIO code always करोes क्रम partial tail blocks beyond खातापूर्ण, so
	 * करोn't even bother trying the fast path in this हाल.
	 */
	अगर (iocb->ki_pos > isize || iocb->ki_pos + count >= isize) अणु
retry_exclusive:
		अगर (iocb->ki_flags & IOCB_NOWAIT)
			वापस -EAGAIN;
		iolock = XFS_IOLOCK_EXCL;
		flags = IOMAP_DIO_FORCE_WAIT;
	पूर्ण

	ret = xfs_ilock_iocb(iocb, iolock);
	अगर (ret)
		वापस ret;

	/*
	 * We can't properly handle unaligned direct I/O to reflink files yet,
	 * as we can't unshare a partial block.
	 */
	अगर (xfs_is_cow_inode(ip)) अणु
		trace_xfs_reflink_bounce_dio_ग_लिखो(iocb, from);
		ret = -ENOTBLK;
		जाओ out_unlock;
	पूर्ण

	ret = xfs_file_ग_लिखो_checks(iocb, from, &iolock);
	अगर (ret)
		जाओ out_unlock;

	/*
	 * If we are करोing exclusive unaligned I/O, this must be the only I/O
	 * in-flight.  Otherwise we risk data corruption due to unwritten extent
	 * conversions from the AIO end_io handler.  Wait क्रम all other I/O to
	 * drain first.
	 */
	अगर (flags & IOMAP_DIO_FORCE_WAIT)
		inode_dio_रुको(VFS_I(ip));

	trace_xfs_file_direct_ग_लिखो(iocb, from);
	ret = iomap_dio_rw(iocb, from, &xfs_direct_ग_लिखो_iomap_ops,
			   &xfs_dio_ग_लिखो_ops, flags);

	/*
	 * Retry unaligned I/O with exclusive blocking semantics अगर the DIO
	 * layer rejected it क्रम mapping or locking reasons. If we are करोing
	 * nonblocking user I/O, propagate the error.
	 */
	अगर (ret == -EAGAIN && !(iocb->ki_flags & IOCB_NOWAIT)) अणु
		ASSERT(flags & IOMAP_DIO_OVERWRITE_ONLY);
		xfs_iunlock(ip, iolock);
		जाओ retry_exclusive;
	पूर्ण

out_unlock:
	अगर (iolock)
		xfs_iunlock(ip, iolock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
xfs_file_dio_ग_लिखो(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*from)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(file_inode(iocb->ki_filp));
	काष्ठा xfs_buftarg      *target = xfs_inode_buftarg(ip);
	माप_प्रकार			count = iov_iter_count(from);

	/* direct I/O must be aligned to device logical sector size */
	अगर ((iocb->ki_pos | count) & target->bt_logical_sectormask)
		वापस -EINVAL;
	अगर ((iocb->ki_pos | count) & ip->i_mount->m_blockmask)
		वापस xfs_file_dio_ग_लिखो_unaligned(ip, iocb, from);
	वापस xfs_file_dio_ग_लिखो_aligned(ip, iocb, from);
पूर्ण

अटल noअंतरभूत sमाप_प्रकार
xfs_file_dax_ग_लिखो(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*from)
अणु
	काष्ठा inode		*inode = iocb->ki_filp->f_mapping->host;
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	पूर्णांक			iolock = XFS_IOLOCK_EXCL;
	sमाप_प्रकार			ret, error = 0;
	loff_t			pos;

	ret = xfs_ilock_iocb(iocb, iolock);
	अगर (ret)
		वापस ret;
	ret = xfs_file_ग_लिखो_checks(iocb, from, &iolock);
	अगर (ret)
		जाओ out;

	pos = iocb->ki_pos;

	trace_xfs_file_dax_ग_लिखो(iocb, from);
	ret = dax_iomap_rw(iocb, from, &xfs_direct_ग_लिखो_iomap_ops);
	अगर (ret > 0 && iocb->ki_pos > i_size_पढ़ो(inode)) अणु
		i_size_ग_लिखो(inode, iocb->ki_pos);
		error = xfs_setfilesize(ip, pos, ret);
	पूर्ण
out:
	अगर (iolock)
		xfs_iunlock(ip, iolock);
	अगर (error)
		वापस error;

	अगर (ret > 0) अणु
		XFS_STATS_ADD(ip->i_mount, xs_ग_लिखो_bytes, ret);

		/* Handle various SYNC-type ग_लिखोs */
		ret = generic_ग_लिखो_sync(iocb, ret);
	पूर्ण
	वापस ret;
पूर्ण

STATIC sमाप_प्रकार
xfs_file_buffered_ग_लिखो(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*from)
अणु
	काष्ठा file		*file = iocb->ki_filp;
	काष्ठा address_space	*mapping = file->f_mapping;
	काष्ठा inode		*inode = mapping->host;
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	sमाप_प्रकार			ret;
	bool			cleared_space = false;
	पूर्णांक			iolock;

	अगर (iocb->ki_flags & IOCB_NOWAIT)
		वापस -EOPNOTSUPP;

ग_लिखो_retry:
	iolock = XFS_IOLOCK_EXCL;
	xfs_ilock(ip, iolock);

	ret = xfs_file_ग_लिखो_checks(iocb, from, &iolock);
	अगर (ret)
		जाओ out;

	/* We can ग_लिखो back this queue in page reclaim */
	current->backing_dev_info = inode_to_bdi(inode);

	trace_xfs_file_buffered_ग_लिखो(iocb, from);
	ret = iomap_file_buffered_ग_लिखो(iocb, from,
			&xfs_buffered_ग_लिखो_iomap_ops);
	अगर (likely(ret >= 0))
		iocb->ki_pos += ret;

	/*
	 * If we hit a space limit, try to मुक्त up some lingering pपुनः_स्मृतिated
	 * space beक्रमe वापसing an error. In the हाल of ENOSPC, first try to
	 * ग_लिखो back all dirty inodes to मुक्त up some of the excess reserved
	 * metadata space. This reduces the chances that the eofblocks scan
	 * रुकोs on dirty mappings. Since xfs_flush_inodes() is serialized, this
	 * also behaves as a filter to prevent too many eofblocks scans from
	 * running at the same समय.  Use a synchronous scan to increase the
	 * effectiveness of the scan.
	 */
	अगर (ret == -EDQUOT && !cleared_space) अणु
		xfs_iunlock(ip, iolock);
		xfs_blockgc_मुक्त_quota(ip, XFS_खातापूर्ण_FLAGS_SYNC);
		cleared_space = true;
		जाओ ग_लिखो_retry;
	पूर्ण अन्यथा अगर (ret == -ENOSPC && !cleared_space) अणु
		काष्ठा xfs_eofblocks eofb = अणु0पूर्ण;

		cleared_space = true;
		xfs_flush_inodes(ip->i_mount);

		xfs_iunlock(ip, iolock);
		eofb.eof_flags = XFS_खातापूर्ण_FLAGS_SYNC;
		xfs_blockgc_मुक्त_space(ip->i_mount, &eofb);
		जाओ ग_लिखो_retry;
	पूर्ण

	current->backing_dev_info = शून्य;
out:
	अगर (iolock)
		xfs_iunlock(ip, iolock);

	अगर (ret > 0) अणु
		XFS_STATS_ADD(ip->i_mount, xs_ग_लिखो_bytes, ret);
		/* Handle various SYNC-type ग_लिखोs */
		ret = generic_ग_लिखो_sync(iocb, ret);
	पूर्ण
	वापस ret;
पूर्ण

STATIC sमाप_प्रकार
xfs_file_ग_लिखो_iter(
	काष्ठा kiocb		*iocb,
	काष्ठा iov_iter		*from)
अणु
	काष्ठा file		*file = iocb->ki_filp;
	काष्ठा address_space	*mapping = file->f_mapping;
	काष्ठा inode		*inode = mapping->host;
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	sमाप_प्रकार			ret;
	माप_प्रकार			ocount = iov_iter_count(from);

	XFS_STATS_INC(ip->i_mount, xs_ग_लिखो_calls);

	अगर (ocount == 0)
		वापस 0;

	अगर (XFS_FORCED_SHUTDOWN(ip->i_mount))
		वापस -EIO;

	अगर (IS_DAX(inode))
		वापस xfs_file_dax_ग_लिखो(iocb, from);

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		/*
		 * Allow a directio ग_लिखो to fall back to a buffered
		 * ग_लिखो *only* in the हाल that we're करोing a reflink
		 * CoW.  In all other directio scenarios we करो not
		 * allow an operation to fall back to buffered mode.
		 */
		ret = xfs_file_dio_ग_लिखो(iocb, from);
		अगर (ret != -ENOTBLK)
			वापस ret;
	पूर्ण

	वापस xfs_file_buffered_ग_लिखो(iocb, from);
पूर्ण

अटल व्योम
xfs_रुको_dax_page(
	काष्ठा inode		*inode)
अणु
	काष्ठा xfs_inode        *ip = XFS_I(inode);

	xfs_iunlock(ip, XFS_MMAPLOCK_EXCL);
	schedule();
	xfs_ilock(ip, XFS_MMAPLOCK_EXCL);
पूर्ण

अटल पूर्णांक
xfs_अवरोध_dax_layouts(
	काष्ठा inode		*inode,
	bool			*retry)
अणु
	काष्ठा page		*page;

	ASSERT(xfs_isilocked(XFS_I(inode), XFS_MMAPLOCK_EXCL));

	page = dax_layout_busy_page(inode->i_mapping);
	अगर (!page)
		वापस 0;

	*retry = true;
	वापस ___रुको_var_event(&page->_refcount,
			atomic_पढ़ो(&page->_refcount) == 1, TASK_INTERRUPTIBLE,
			0, 0, xfs_रुको_dax_page(inode));
पूर्ण

पूर्णांक
xfs_अवरोध_layouts(
	काष्ठा inode		*inode,
	uपूर्णांक			*iolock,
	क्रमागत layout_अवरोध_reason reason)
अणु
	bool			retry;
	पूर्णांक			error;

	ASSERT(xfs_isilocked(XFS_I(inode), XFS_IOLOCK_SHARED|XFS_IOLOCK_EXCL));

	करो अणु
		retry = false;
		चयन (reason) अणु
		हाल BREAK_UNMAP:
			error = xfs_अवरोध_dax_layouts(inode, &retry);
			अगर (error || retry)
				अवरोध;
			/* fall through */
		हाल BREAK_WRITE:
			error = xfs_अवरोध_leased_layouts(inode, iolock, &retry);
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			error = -EINVAL;
		पूर्ण
	पूर्ण जबतक (error == 0 && retry);

	वापस error;
पूर्ण

#घोषणा	XFS_FALLOC_FL_SUPPORTED						\
		(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE |		\
		 FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE |	\
		 FALLOC_FL_INSERT_RANGE | FALLOC_FL_UNSHARE_RANGE)

STATIC दीर्घ
xfs_file_fallocate(
	काष्ठा file		*file,
	पूर्णांक			mode,
	loff_t			offset,
	loff_t			len)
अणु
	काष्ठा inode		*inode = file_inode(file);
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	दीर्घ			error;
	क्रमागत xfs_pपुनः_स्मृति_flags	flags = 0;
	uपूर्णांक			iolock = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;
	loff_t			new_size = 0;
	bool			करो_file_insert = false;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;
	अगर (mode & ~XFS_FALLOC_FL_SUPPORTED)
		वापस -EOPNOTSUPP;

	xfs_ilock(ip, iolock);
	error = xfs_अवरोध_layouts(inode, &iolock, BREAK_UNMAP);
	अगर (error)
		जाओ out_unlock;

	/*
	 * Must रुको क्रम all AIO to complete beक्रमe we जारी as AIO can
	 * change the file size on completion without holding any locks we
	 * currently hold. We must करो this first because AIO can update both
	 * the on disk and in memory inode sizes, and the operations that follow
	 * require the in-memory size to be fully up-to-date.
	 */
	inode_dio_रुको(inode);

	/*
	 * Now AIO and DIO has drained we flush and (अगर necessary) invalidate
	 * the cached range over the first operation we are about to run.
	 *
	 * We care about zero and collapse here because they both run a hole
	 * punch over the range first. Because that can zero data, and the range
	 * of invalidation क्रम the shअगरt operations is much larger, we still करो
	 * the required flush क्रम collapse in xfs_prepare_shअगरt().
	 *
	 * Insert has the same range requirements as collapse, and we extend the
	 * file first which can zero data. Hence insert has the same
	 * flush/invalidate requirements as collapse and so they are both
	 * handled at the right समय by xfs_prepare_shअगरt().
	 */
	अगर (mode & (FALLOC_FL_PUNCH_HOLE | FALLOC_FL_ZERO_RANGE |
		    FALLOC_FL_COLLAPSE_RANGE)) अणु
		error = xfs_flush_unmap_range(ip, offset, len);
		अगर (error)
			जाओ out_unlock;
	पूर्ण

	अगर (mode & FALLOC_FL_PUNCH_HOLE) अणु
		error = xfs_मुक्त_file_space(ip, offset, len);
		अगर (error)
			जाओ out_unlock;
	पूर्ण अन्यथा अगर (mode & FALLOC_FL_COLLAPSE_RANGE) अणु
		अगर (!xfs_is_falloc_aligned(ip, offset, len)) अणु
			error = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		/*
		 * There is no need to overlap collapse range with खातापूर्ण,
		 * in which हाल it is effectively a truncate operation
		 */
		अगर (offset + len >= i_size_पढ़ो(inode)) अणु
			error = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		new_size = i_size_पढ़ो(inode) - len;

		error = xfs_collapse_file_space(ip, offset, len);
		अगर (error)
			जाओ out_unlock;
	पूर्ण अन्यथा अगर (mode & FALLOC_FL_INSERT_RANGE) अणु
		loff_t		isize = i_size_पढ़ो(inode);

		अगर (!xfs_is_falloc_aligned(ip, offset, len)) अणु
			error = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		/*
		 * New inode size must not exceed ->s_maxbytes, accounting क्रम
		 * possible चिन्हित overflow.
		 */
		अगर (inode->i_sb->s_maxbytes - isize < len) अणु
			error = -EFBIG;
			जाओ out_unlock;
		पूर्ण
		new_size = isize + len;

		/* Offset should be less than i_size */
		अगर (offset >= isize) अणु
			error = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		करो_file_insert = true;
	पूर्ण अन्यथा अणु
		flags |= XFS_PREALLOC_SET;

		अगर (!(mode & FALLOC_FL_KEEP_SIZE) &&
		    offset + len > i_size_पढ़ो(inode)) अणु
			new_size = offset + len;
			error = inode_newsize_ok(inode, new_size);
			अगर (error)
				जाओ out_unlock;
		पूर्ण

		अगर (mode & FALLOC_FL_ZERO_RANGE) अणु
			/*
			 * Punch a hole and pपुनः_स्मृति the range.  We use a hole
			 * punch rather than unwritten extent conversion क्रम two
			 * reasons:
			 *
			 *   1.) Hole punch handles partial block zeroing क्रम us.
			 *   2.) If pपुनः_स्मृति वापसs ENOSPC, the file range is
			 *       still zero-valued by virtue of the hole punch.
			 */
			अचिन्हित पूर्णांक blksize = i_blocksize(inode);

			trace_xfs_zero_file_space(ip);

			error = xfs_मुक्त_file_space(ip, offset, len);
			अगर (error)
				जाओ out_unlock;

			len = round_up(offset + len, blksize) -
			      round_करोwn(offset, blksize);
			offset = round_करोwn(offset, blksize);
		पूर्ण अन्यथा अगर (mode & FALLOC_FL_UNSHARE_RANGE) अणु
			error = xfs_reflink_unshare(ip, offset, len);
			अगर (error)
				जाओ out_unlock;
		पूर्ण अन्यथा अणु
			/*
			 * If always_cow mode we can't use pपुनः_स्मृतिations and
			 * thus should not create them.
			 */
			अगर (xfs_is_always_cow_inode(ip)) अणु
				error = -EOPNOTSUPP;
				जाओ out_unlock;
			पूर्ण
		पूर्ण

		अगर (!xfs_is_always_cow_inode(ip)) अणु
			error = xfs_alloc_file_space(ip, offset, len,
						     XFS_BMAPI_PREALLOC);
			अगर (error)
				जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर (file->f_flags & O_DSYNC)
		flags |= XFS_PREALLOC_SYNC;

	error = xfs_update_pपुनः_स्मृति_flags(ip, flags);
	अगर (error)
		जाओ out_unlock;

	/* Change file size अगर needed */
	अगर (new_size) अणु
		काष्ठा iattr iattr;

		iattr.ia_valid = ATTR_SIZE;
		iattr.ia_size = new_size;
		error = xfs_vn_setattr_size(file_mnt_user_ns(file),
					    file_dentry(file), &iattr);
		अगर (error)
			जाओ out_unlock;
	पूर्ण

	/*
	 * Perक्रमm hole insertion now that the file size has been
	 * updated so that अगर we crash during the operation we करोn't
	 * leave shअगरted extents past खातापूर्ण and hence losing access to
	 * the data that is contained within them.
	 */
	अगर (करो_file_insert)
		error = xfs_insert_file_space(ip, offset, len);

out_unlock:
	xfs_iunlock(ip, iolock);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_file_fadvise(
	काष्ठा file	*file,
	loff_t		start,
	loff_t		end,
	पूर्णांक		advice)
अणु
	काष्ठा xfs_inode *ip = XFS_I(file_inode(file));
	पूर्णांक ret;
	पूर्णांक lockflags = 0;

	/*
	 * Operations creating pages in page cache need protection from hole
	 * punching and similar ops
	 */
	अगर (advice == POSIX_FADV_WILLNEED) अणु
		lockflags = XFS_IOLOCK_SHARED;
		xfs_ilock(ip, lockflags);
	पूर्ण
	ret = generic_fadvise(file, start, end, advice);
	अगर (lockflags)
		xfs_iunlock(ip, lockflags);
	वापस ret;
पूर्ण

/* Does this file, inode, or mount want synchronous ग_लिखोs? */
अटल अंतरभूत bool xfs_file_sync_ग_लिखोs(काष्ठा file *filp)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(file_inode(filp));

	अगर (ip->i_mount->m_flags & XFS_MOUNT_WSYNC)
		वापस true;
	अगर (filp->f_flags & (__O_SYNC | O_DSYNC))
		वापस true;
	अगर (IS_SYNC(file_inode(filp)))
		वापस true;

	वापस false;
पूर्ण

STATIC loff_t
xfs_file_remap_range(
	काष्ठा file		*file_in,
	loff_t			pos_in,
	काष्ठा file		*file_out,
	loff_t			pos_out,
	loff_t			len,
	अचिन्हित पूर्णांक		remap_flags)
अणु
	काष्ठा inode		*inode_in = file_inode(file_in);
	काष्ठा xfs_inode	*src = XFS_I(inode_in);
	काष्ठा inode		*inode_out = file_inode(file_out);
	काष्ठा xfs_inode	*dest = XFS_I(inode_out);
	काष्ठा xfs_mount	*mp = src->i_mount;
	loff_t			remapped = 0;
	xfs_extlen_t		cowextsize;
	पूर्णांक			ret;

	अगर (remap_flags & ~(REMAP_खाता_DEDUP | REMAP_खाता_ADVISORY))
		वापस -EINVAL;

	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस -EOPNOTSUPP;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	/* Prepare and then clone file data. */
	ret = xfs_reflink_remap_prep(file_in, pos_in, file_out, pos_out,
			&len, remap_flags);
	अगर (ret || len == 0)
		वापस ret;

	trace_xfs_reflink_remap_range(src, pos_in, len, dest, pos_out);

	ret = xfs_reflink_remap_blocks(src, pos_in, dest, pos_out, len,
			&remapped);
	अगर (ret)
		जाओ out_unlock;

	/*
	 * Carry the cowextsize hपूर्णांक from src to dest अगर we're sharing the
	 * entire source file to the entire destination file, the source file
	 * has a cowextsize hपूर्णांक, and the destination file करोes not.
	 */
	cowextsize = 0;
	अगर (pos_in == 0 && len == i_size_पढ़ो(inode_in) &&
	    (src->i_dअगरlags2 & XFS_DIFLAG2_COWEXTSIZE) &&
	    pos_out == 0 && len >= i_size_पढ़ो(inode_out) &&
	    !(dest->i_dअगरlags2 & XFS_DIFLAG2_COWEXTSIZE))
		cowextsize = src->i_cowextsize;

	ret = xfs_reflink_update_dest(dest, pos_out + len, cowextsize,
			remap_flags);
	अगर (ret)
		जाओ out_unlock;

	अगर (xfs_file_sync_ग_लिखोs(file_in) || xfs_file_sync_ग_लिखोs(file_out))
		xfs_log_क्रमce_inode(dest);
out_unlock:
	xfs_iunlock2_io_mmap(src, dest);
	अगर (ret)
		trace_xfs_reflink_remap_range_error(dest, ret, _RET_IP_);
	वापस remapped > 0 ? remapped : ret;
पूर्ण

STATIC पूर्णांक
xfs_file_खोलो(
	काष्ठा inode	*inode,
	काष्ठा file	*file)
अणु
	अगर (!(file->f_flags & O_LARGEखाता) && i_size_पढ़ो(inode) > MAX_NON_LFS)
		वापस -EFBIG;
	अगर (XFS_FORCED_SHUTDOWN(XFS_M(inode->i_sb)))
		वापस -EIO;
	file->f_mode |= FMODE_NOWAIT | FMODE_BUF_RASYNC;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_dir_खोलो(
	काष्ठा inode	*inode,
	काष्ठा file	*file)
अणु
	काष्ठा xfs_inode *ip = XFS_I(inode);
	पूर्णांक		mode;
	पूर्णांक		error;

	error = xfs_file_खोलो(inode, file);
	अगर (error)
		वापस error;

	/*
	 * If there are any blocks, पढ़ो-ahead block 0 as we're almost
	 * certain to have the next operation be a पढ़ो there.
	 */
	mode = xfs_ilock_data_map_shared(ip);
	अगर (ip->i_df.अगर_nextents > 0)
		error = xfs_dir3_data_पढ़ोahead(ip, 0, 0);
	xfs_iunlock(ip, mode);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_file_release(
	काष्ठा inode	*inode,
	काष्ठा file	*filp)
अणु
	वापस xfs_release(XFS_I(inode));
पूर्ण

STATIC पूर्णांक
xfs_file_सूची_पढ़ो(
	काष्ठा file	*file,
	काष्ठा dir_context *ctx)
अणु
	काष्ठा inode	*inode = file_inode(file);
	xfs_inode_t	*ip = XFS_I(inode);
	माप_प्रकार		bufsize;

	/*
	 * The Linux API करोesn't pass करोwn the total size of the buffer
	 * we पढ़ो पूर्णांकo करोwn to the fileप्रणाली.  With the filldir concept
	 * it's not needed क्रम correct inक्रमmation, but the XFS dir2 leaf
	 * code wants an estimate of the buffer size to calculate it's
	 * पढ़ोahead winकरोw and size the buffers used क्रम mapping to
	 * physical blocks.
	 *
	 * Try to give it an estimate that's good enough, maybe at some
	 * poपूर्णांक we can change the ->सूची_पढ़ो prototype to include the
	 * buffer size.  For now we use the current glibc buffer size.
	 */
	bufsize = (माप_प्रकार)min_t(loff_t, XFS_READसूची_बफ_मानE, ip->i_disk_size);

	वापस xfs_सूची_पढ़ो(शून्य, ip, ctx, bufsize);
पूर्ण

STATIC loff_t
xfs_file_llseek(
	काष्ठा file	*file,
	loff_t		offset,
	पूर्णांक		whence)
अणु
	काष्ठा inode		*inode = file->f_mapping->host;

	अगर (XFS_FORCED_SHUTDOWN(XFS_I(inode)->i_mount))
		वापस -EIO;

	चयन (whence) अणु
	शेष:
		वापस generic_file_llseek(file, offset, whence);
	हाल SEEK_HOLE:
		offset = iomap_seek_hole(inode, offset, &xfs_seek_iomap_ops);
		अवरोध;
	हाल SEEK_DATA:
		offset = iomap_seek_data(inode, offset, &xfs_seek_iomap_ops);
		अवरोध;
	पूर्ण

	अगर (offset < 0)
		वापस offset;
	वापस vfs_setpos(file, offset, inode->i_sb->s_maxbytes);
पूर्ण

/*
 * Locking क्रम serialisation of IO during page faults. This results in a lock
 * ordering of:
 *
 * mmap_lock (MM)
 *   sb_start_pagefault(vfs, मुक्तze)
 *     i_mmaplock (XFS - truncate serialisation)
 *       page_lock (MM)
 *         i_lock (XFS - extent map serialisation)
 */
अटल vm_fault_t
__xfs_filemap_fault(
	काष्ठा vm_fault		*vmf,
	क्रमागत page_entry_size	pe_size,
	bool			ग_लिखो_fault)
अणु
	काष्ठा inode		*inode = file_inode(vmf->vma->vm_file);
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	vm_fault_t		ret;

	trace_xfs_filemap_fault(ip, pe_size, ग_लिखो_fault);

	अगर (ग_लिखो_fault) अणु
		sb_start_pagefault(inode->i_sb);
		file_update_समय(vmf->vma->vm_file);
	पूर्ण

	xfs_ilock(XFS_I(inode), XFS_MMAPLOCK_SHARED);
	अगर (IS_DAX(inode)) अणु
		pfn_t pfn;

		ret = dax_iomap_fault(vmf, pe_size, &pfn, शून्य,
				(ग_लिखो_fault && !vmf->cow_page) ?
				 &xfs_direct_ग_लिखो_iomap_ops :
				 &xfs_पढ़ो_iomap_ops);
		अगर (ret & VM_FAULT_NEEDDSYNC)
			ret = dax_finish_sync_fault(vmf, pe_size, pfn);
	पूर्ण अन्यथा अणु
		अगर (ग_लिखो_fault)
			ret = iomap_page_mkग_लिखो(vmf,
					&xfs_buffered_ग_लिखो_iomap_ops);
		अन्यथा
			ret = filemap_fault(vmf);
	पूर्ण
	xfs_iunlock(XFS_I(inode), XFS_MMAPLOCK_SHARED);

	अगर (ग_लिखो_fault)
		sb_end_pagefault(inode->i_sb);
	वापस ret;
पूर्ण

अटल अंतरभूत bool
xfs_is_ग_लिखो_fault(
	काष्ठा vm_fault		*vmf)
अणु
	वापस (vmf->flags & FAULT_FLAG_WRITE) &&
	       (vmf->vma->vm_flags & VM_SHARED);
पूर्ण

अटल vm_fault_t
xfs_filemap_fault(
	काष्ठा vm_fault		*vmf)
अणु
	/* DAX can लघुcut the normal fault path on ग_लिखो faults! */
	वापस __xfs_filemap_fault(vmf, PE_SIZE_PTE,
			IS_DAX(file_inode(vmf->vma->vm_file)) &&
			xfs_is_ग_लिखो_fault(vmf));
पूर्ण

अटल vm_fault_t
xfs_filemap_huge_fault(
	काष्ठा vm_fault		*vmf,
	क्रमागत page_entry_size	pe_size)
अणु
	अगर (!IS_DAX(file_inode(vmf->vma->vm_file)))
		वापस VM_FAULT_FALLBACK;

	/* DAX can लघुcut the normal fault path on ग_लिखो faults! */
	वापस __xfs_filemap_fault(vmf, pe_size,
			xfs_is_ग_लिखो_fault(vmf));
पूर्ण

अटल vm_fault_t
xfs_filemap_page_mkग_लिखो(
	काष्ठा vm_fault		*vmf)
अणु
	वापस __xfs_filemap_fault(vmf, PE_SIZE_PTE, true);
पूर्ण

/*
 * pfn_mkग_लिखो was originally पूर्णांकended to ensure we capture समय stamp updates
 * on ग_लिखो faults. In reality, it needs to serialise against truncate and
 * prepare memory क्रम writing so handle is as standard ग_लिखो fault.
 */
अटल vm_fault_t
xfs_filemap_pfn_mkग_लिखो(
	काष्ठा vm_fault		*vmf)
अणु

	वापस __xfs_filemap_fault(vmf, PE_SIZE_PTE, true);
पूर्ण

अटल vm_fault_t
xfs_filemap_map_pages(
	काष्ठा vm_fault		*vmf,
	pgoff_t			start_pgoff,
	pgoff_t			end_pgoff)
अणु
	काष्ठा inode		*inode = file_inode(vmf->vma->vm_file);
	vm_fault_t ret;

	xfs_ilock(XFS_I(inode), XFS_MMAPLOCK_SHARED);
	ret = filemap_map_pages(vmf, start_pgoff, end_pgoff);
	xfs_iunlock(XFS_I(inode), XFS_MMAPLOCK_SHARED);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा xfs_file_vm_ops = अणु
	.fault		= xfs_filemap_fault,
	.huge_fault	= xfs_filemap_huge_fault,
	.map_pages	= xfs_filemap_map_pages,
	.page_mkग_लिखो	= xfs_filemap_page_mkग_लिखो,
	.pfn_mkग_लिखो	= xfs_filemap_pfn_mkग_लिखो,
पूर्ण;

STATIC पूर्णांक
xfs_file_mmap(
	काष्ठा file		*file,
	काष्ठा vm_area_काष्ठा	*vma)
अणु
	काष्ठा inode		*inode = file_inode(file);
	काष्ठा xfs_buftarg	*target = xfs_inode_buftarg(XFS_I(inode));

	/*
	 * We करोn't support synchronous mappings क्रम non-DAX files and
	 * क्रम DAX files अगर underneath dax_device is not synchronous.
	 */
	अगर (!daxdev_mapping_supported(vma, target->bt_daxdev))
		वापस -EOPNOTSUPP;

	file_accessed(file);
	vma->vm_ops = &xfs_file_vm_ops;
	अगर (IS_DAX(inode))
		vma->vm_flags |= VM_HUGEPAGE;
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations xfs_file_operations = अणु
	.llseek		= xfs_file_llseek,
	.पढ़ो_iter	= xfs_file_पढ़ो_iter,
	.ग_लिखो_iter	= xfs_file_ग_लिखो_iter,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.iopoll		= iomap_dio_iopoll,
	.unlocked_ioctl	= xfs_file_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= xfs_file_compat_ioctl,
#पूर्ण_अगर
	.mmap		= xfs_file_mmap,
	.mmap_supported_flags = MAP_SYNC,
	.खोलो		= xfs_file_खोलो,
	.release	= xfs_file_release,
	.fsync		= xfs_file_fsync,
	.get_unmapped_area = thp_get_unmapped_area,
	.fallocate	= xfs_file_fallocate,
	.fadvise	= xfs_file_fadvise,
	.remap_file_range = xfs_file_remap_range,
पूर्ण;

स्थिर काष्ठा file_operations xfs_dir_file_operations = अणु
	.खोलो		= xfs_dir_खोलो,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= xfs_file_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
	.unlocked_ioctl	= xfs_file_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= xfs_file_compat_ioctl,
#पूर्ण_अगर
	.fsync		= xfs_dir_fsync,
पूर्ण;
