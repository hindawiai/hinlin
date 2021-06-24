<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Christoph Hellwig.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_iomap.h"
#समावेश "xfs_pnfs.h"

/*
 * Ensure that we करो not have any outstanding pNFS layouts that can be used by
 * clients to directly पढ़ो from or ग_लिखो to this inode.  This must be called
 * beक्रमe every operation that can हटाओ blocks from the extent map.
 * Additionally we call it during the ग_लिखो operation, where aren't concerned
 * about exposing unallocated blocks but just want to provide basic
 * synchronization between a local ग_लिखोr and pNFS clients.  mmap ग_लिखोs would
 * also benefit from this sort of synchronization, but due to the tricky locking
 * rules in the page fault path we करोn't bother.
 */
पूर्णांक
xfs_अवरोध_leased_layouts(
	काष्ठा inode		*inode,
	uपूर्णांक			*iolock,
	bool			*did_unlock)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	पूर्णांक			error;

	जबतक ((error = अवरोध_layout(inode, false)) == -EWOULDBLOCK) अणु
		xfs_iunlock(ip, *iolock);
		*did_unlock = true;
		error = अवरोध_layout(inode, true);
		*iolock &= ~XFS_IOLOCK_SHARED;
		*iolock |= XFS_IOLOCK_EXCL;
		xfs_ilock(ip, *iolock);
	पूर्ण

	वापस error;
पूर्ण

/*
 * Get a unique ID including its location so that the client can identअगरy
 * the exported device.
 */
पूर्णांक
xfs_fs_get_uuid(
	काष्ठा super_block	*sb,
	u8			*buf,
	u32			*len,
	u64			*offset)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);

	xfs_notice_once(mp,
"Using experimental pNFS feature, use at your own risk!");

	अगर (*len < माप(uuid_t))
		वापस -EINVAL;

	स_नकल(buf, &mp->m_sb.sb_uuid, माप(uuid_t));
	*len = माप(uuid_t);
	*offset = दुरत्व(काष्ठा xfs_dsb, sb_uuid);
	वापस 0;
पूर्ण

/*
 * Get a layout क्रम the pNFS client.
 */
पूर्णांक
xfs_fs_map_blocks(
	काष्ठा inode		*inode,
	loff_t			offset,
	u64			length,
	काष्ठा iomap		*iomap,
	bool			ग_लिखो,
	u32			*device_generation)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_bmbt_irec	imap;
	xfs_fileoff_t		offset_fsb, end_fsb;
	loff_t			limit;
	पूर्णांक			bmapi_flags = XFS_BMAPI_ENTIRE;
	पूर्णांक			nimaps = 1;
	uपूर्णांक			lock_flags;
	पूर्णांक			error = 0;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	/*
	 * We can't export inodes residing on the realसमय device.  The realसमय
	 * device करोesn't have a UUID to identअगरy it, so the client has no way
	 * to find it.
	 */
	अगर (XFS_IS_REALTIME_INODE(ip))
		वापस -ENXIO;

	/*
	 * The pNFS block layout spec actually supports reflink like
	 * functionality, but the Linux pNFS server करोesn't implement it yet.
	 */
	अगर (xfs_is_reflink_inode(ip))
		वापस -ENXIO;

	/*
	 * Lock out any other I/O beक्रमe we flush and invalidate the pagecache,
	 * and then hand out a layout to the remote प्रणाली.  This is very
	 * similar to direct I/O, except that the synchronization is much more
	 * complicated.  See the comment near xfs_अवरोध_leased_layouts
	 * क्रम a detailed explanation.
	 */
	xfs_ilock(ip, XFS_IOLOCK_EXCL);

	error = -EINVAL;
	limit = mp->m_super->s_maxbytes;
	अगर (!ग_लिखो)
		limit = max(limit, round_up(i_size_पढ़ो(inode),
				     inode->i_sb->s_blocksize));
	अगर (offset > limit)
		जाओ out_unlock;
	अगर (offset > limit - length)
		length = limit - offset;

	error = filemap_ग_लिखो_and_रुको(inode->i_mapping);
	अगर (error)
		जाओ out_unlock;
	error = invalidate_inode_pages2(inode->i_mapping);
	अगर (WARN_ON_ONCE(error))
		जाओ out_unlock;

	end_fsb = XFS_B_TO_FSB(mp, (xfs_ufमाप_प्रकार)offset + length);
	offset_fsb = XFS_B_TO_FSBT(mp, offset);

	lock_flags = xfs_ilock_data_map_shared(ip);
	error = xfs_bmapi_पढ़ो(ip, offset_fsb, end_fsb - offset_fsb,
				&imap, &nimaps, bmapi_flags);

	ASSERT(!nimaps || imap.br_startblock != DELAYSTARTBLOCK);

	अगर (!error && ग_लिखो &&
	    (!nimaps || imap.br_startblock == HOLESTARTBLOCK)) अणु
		अगर (offset + length > XFS_ISIZE(ip))
			end_fsb = xfs_iomap_eof_align_last_fsb(ip, end_fsb);
		अन्यथा अगर (nimaps && imap.br_startblock == HOLESTARTBLOCK)
			end_fsb = min(end_fsb, imap.br_startoff +
					       imap.br_blockcount);
		xfs_iunlock(ip, lock_flags);

		error = xfs_iomap_ग_लिखो_direct(ip, offset_fsb,
				end_fsb - offset_fsb, &imap);
		अगर (error)
			जाओ out_unlock;

		/*
		 * Ensure the next transaction is committed synchronously so
		 * that the blocks allocated and handed out to the client are
		 * guaranteed to be present even after a server crash.
		 */
		error = xfs_update_pपुनः_स्मृति_flags(ip,
				XFS_PREALLOC_SET | XFS_PREALLOC_SYNC);
		अगर (error)
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		xfs_iunlock(ip, lock_flags);
	पूर्ण
	xfs_iunlock(ip, XFS_IOLOCK_EXCL);

	error = xfs_bmbt_to_iomap(ip, iomap, &imap, 0);
	*device_generation = mp->m_generation;
	वापस error;
out_unlock:
	xfs_iunlock(ip, XFS_IOLOCK_EXCL);
	वापस error;
पूर्ण

/*
 * Ensure the size update falls पूर्णांकo a valid allocated block.
 */
अटल पूर्णांक
xfs_pnfs_validate_isize(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		isize)
अणु
	काष्ठा xfs_bmbt_irec	imap;
	पूर्णांक			nimaps = 1;
	पूर्णांक			error = 0;

	xfs_ilock(ip, XFS_ILOCK_SHARED);
	error = xfs_bmapi_पढ़ो(ip, XFS_B_TO_FSBT(ip->i_mount, isize - 1), 1,
				&imap, &nimaps, 0);
	xfs_iunlock(ip, XFS_ILOCK_SHARED);
	अगर (error)
		वापस error;

	अगर (imap.br_startblock == HOLESTARTBLOCK ||
	    imap.br_startblock == DELAYSTARTBLOCK ||
	    imap.br_state == XFS_EXT_UNWRITTEN)
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * Make sure the blocks described by maps are stable on disk.  This includes
 * converting any unwritten extents, flushing the disk cache and updating the
 * समय stamps.
 *
 * Note that we rely on the caller to always send us a बारtamp update so that
 * we always commit a transaction here.  If that stops being true we will have
 * to manually flush the cache here similar to what the fsync code path करोes
 * क्रम datasyncs on files that have no dirty metadata.
 */
पूर्णांक
xfs_fs_commit_blocks(
	काष्ठा inode		*inode,
	काष्ठा iomap		*maps,
	पूर्णांक			nr_maps,
	काष्ठा iattr		*iattr)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	bool			update_isize = false;
	पूर्णांक			error, i;
	loff_t			size;

	ASSERT(iattr->ia_valid & (ATTR_ATIME|ATTR_CTIME|ATTR_MTIME));

	xfs_ilock(ip, XFS_IOLOCK_EXCL);

	size = i_size_पढ़ो(inode);
	अगर ((iattr->ia_valid & ATTR_SIZE) && iattr->ia_size > size) अणु
		update_isize = true;
		size = iattr->ia_size;
	पूर्ण

	क्रम (i = 0; i < nr_maps; i++) अणु
		u64 start, length, end;

		start = maps[i].offset;
		अगर (start > size)
			जारी;

		end = start + maps[i].length;
		अगर (end > size)
			end = size;

		length = end - start;
		अगर (!length)
			जारी;
	
		/*
		 * Make sure पढ़ोs through the pagecache see the new data.
		 */
		error = invalidate_inode_pages2_range(inode->i_mapping,
					start >> PAGE_SHIFT,
					(end - 1) >> PAGE_SHIFT);
		WARN_ON_ONCE(error);

		error = xfs_iomap_ग_लिखो_unwritten(ip, start, length, false);
		अगर (error)
			जाओ out_drop_iolock;
	पूर्ण

	अगर (update_isize) अणु
		error = xfs_pnfs_validate_isize(ip, size);
		अगर (error)
			जाओ out_drop_iolock;
	पूर्ण

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ichange, 0, 0, 0, &tp);
	अगर (error)
		जाओ out_drop_iolock;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	xfs_setattr_समय(ip, iattr);
	अगर (update_isize) अणु
		i_size_ग_लिखो(inode, iattr->ia_size);
		ip->i_disk_size = iattr->ia_size;
	पूर्ण

	xfs_trans_set_sync(tp);
	error = xfs_trans_commit(tp);

out_drop_iolock:
	xfs_iunlock(ip, XFS_IOLOCK_EXCL);
	वापस error;
पूर्ण
