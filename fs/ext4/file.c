<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/file.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/file.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext4 fs regular file handling primitives
 *
 *  64-bit file support on 64-bit platक्रमms by Jakub Jelinek
 *	(jj@sunsite.ms.mff.cuni.cz)
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/mount.h>
#समावेश <linux/path.h>
#समावेश <linux/dax.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/uपन.स>
#समावेश <linux/mman.h>
#समावेश <linux/backing-dev.h>
#समावेश "ext4.h"
#समावेश "ext4_jbd2.h"
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश "truncate.h"

अटल bool ext4_dio_supported(काष्ठा inode *inode)
अणु
	अगर (IS_ENABLED(CONFIG_FS_ENCRYPTION) && IS_ENCRYPTED(inode))
		वापस false;
	अगर (fsverity_active(inode))
		वापस false;
	अगर (ext4_should_journal_data(inode))
		वापस false;
	अगर (ext4_has_अंतरभूत_data(inode))
		वापस false;
	वापस true;
पूर्ण

अटल sमाप_प्रकार ext4_dio_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	sमाप_प्रकार ret;
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock_shared(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		inode_lock_shared(inode);
	पूर्ण

	अगर (!ext4_dio_supported(inode)) अणु
		inode_unlock_shared(inode);
		/*
		 * Fallback to buffered I/O अगर the operation being perक्रमmed on
		 * the inode is not supported by direct I/O. The IOCB_सूचीECT
		 * flag needs to be cleared here in order to ensure that the
		 * direct I/O path within generic_file_पढ़ो_iter() is not
		 * taken.
		 */
		iocb->ki_flags &= ~IOCB_सूचीECT;
		वापस generic_file_पढ़ो_iter(iocb, to);
	पूर्ण

	ret = iomap_dio_rw(iocb, to, &ext4_iomap_ops, शून्य, 0);
	inode_unlock_shared(inode);

	file_accessed(iocb->ki_filp);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_FS_DAX
अटल sमाप_प्रकार ext4_dax_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	sमाप_प्रकार ret;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock_shared(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		inode_lock_shared(inode);
	पूर्ण
	/*
	 * Recheck under inode lock - at this poपूर्णांक we are sure it cannot
	 * change anymore
	 */
	अगर (!IS_DAX(inode)) अणु
		inode_unlock_shared(inode);
		/* Fallback to buffered IO in हाल we cannot support DAX */
		वापस generic_file_पढ़ो_iter(iocb, to);
	पूर्ण
	ret = dax_iomap_rw(iocb, to, &ext4_iomap_ops);
	inode_unlock_shared(inode);

	file_accessed(iocb->ki_filp);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार ext4_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	अगर (!iov_iter_count(to))
		वापस 0; /* skip aसमय */

#अगर_घोषित CONFIG_FS_DAX
	अगर (IS_DAX(inode))
		वापस ext4_dax_पढ़ो_iter(iocb, to);
#पूर्ण_अगर
	अगर (iocb->ki_flags & IOCB_सूचीECT)
		वापस ext4_dio_पढ़ो_iter(iocb, to);

	वापस generic_file_पढ़ो_iter(iocb, to);
पूर्ण

/*
 * Called when an inode is released. Note that this is dअगरferent
 * from ext4_file_खोलो: खोलो माला_लो called at every खोलो, but release
 * माला_लो called only when /all/ the files are बंदd.
 */
अटल पूर्णांक ext4_release_file(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर (ext4_test_inode_state(inode, EXT4_STATE_DA_ALLOC_CLOSE)) अणु
		ext4_alloc_da_blocks(inode);
		ext4_clear_inode_state(inode, EXT4_STATE_DA_ALLOC_CLOSE);
	पूर्ण
	/* अगर we are the last ग_लिखोr on the inode, drop the block reservation */
	अगर ((filp->f_mode & FMODE_WRITE) &&
			(atomic_पढ़ो(&inode->i_ग_लिखोcount) == 1) &&
			!EXT4_I(inode)->i_reserved_data_blocks) अणु
		करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		ext4_discard_pपुनः_स्मृतिations(inode, 0);
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	पूर्ण
	अगर (is_dx(inode) && filp->निजी_data)
		ext4_htree_मुक्त_dir_info(filp->निजी_data);

	वापस 0;
पूर्ण

/*
 * This tests whether the IO in question is block-aligned or not.
 * Ext4 utilizes unwritten extents when hole-filling during direct IO, and they
 * are converted to written only after the IO is complete.  Until they are
 * mapped, these blocks appear as holes, so dio_zero_block() will assume that
 * it needs to zero out portions of the start and/or end block.  If 2 AIO
 * thपढ़ोs are at work on the same unwritten block, they must be synchronized
 * or one thपढ़ो will zero the other's data, causing corruption.
 */
अटल bool
ext4_unaligned_io(काष्ठा inode *inode, काष्ठा iov_iter *from, loff_t pos)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित दीर्घ blockmask = sb->s_blocksize - 1;

	अगर ((pos | iov_iter_alignment(from)) & blockmask)
		वापस true;

	वापस false;
पूर्ण

अटल bool
ext4_extending_io(काष्ठा inode *inode, loff_t offset, माप_प्रकार len)
अणु
	अगर (offset + len > i_size_पढ़ो(inode) ||
	    offset + len > EXT4_I(inode)->i_disksize)
		वापस true;
	वापस false;
पूर्ण

/* Is IO overwriting allocated and initialized blocks? */
अटल bool ext4_overग_लिखो_io(काष्ठा inode *inode, loff_t pos, loff_t len)
अणु
	काष्ठा ext4_map_blocks map;
	अचिन्हित पूर्णांक blkbits = inode->i_blkbits;
	पूर्णांक err, blklen;

	अगर (pos + len > i_size_पढ़ो(inode))
		वापस false;

	map.m_lblk = pos >> blkbits;
	map.m_len = EXT4_MAX_BLOCKS(len, pos, blkbits);
	blklen = map.m_len;

	err = ext4_map_blocks(शून्य, inode, &map, 0);
	/*
	 * 'err==len' means that all of the blocks have been pपुनः_स्मृतिated,
	 * regardless of whether they have been initialized or not. To exclude
	 * unwritten extents, we need to check m_flags.
	 */
	वापस err == blklen && (map.m_flags & EXT4_MAP_MAPPED);
पूर्ण

अटल sमाप_प्रकार ext4_generic_ग_लिखो_checks(काष्ठा kiocb *iocb,
					 काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	sमाप_प्रकार ret;

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस -EPERM;

	ret = generic_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0)
		वापस ret;

	/*
	 * If we have encountered a biपंचांगap-क्रमmat file, the size limit
	 * is smaller than s_maxbytes, which is क्रम extent-mapped files.
	 */
	अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) अणु
		काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

		अगर (iocb->ki_pos >= sbi->s_biपंचांगap_maxbytes)
			वापस -EFBIG;
		iov_iter_truncate(from, sbi->s_biपंचांगap_maxbytes - iocb->ki_pos);
	पूर्ण

	वापस iov_iter_count(from);
पूर्ण

अटल sमाप_प्रकार ext4_ग_लिखो_checks(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	sमाप_प्रकार ret, count;

	count = ext4_generic_ग_लिखो_checks(iocb, from);
	अगर (count <= 0)
		वापस count;

	ret = file_modअगरied(iocb->ki_filp);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार ext4_buffered_ग_लिखो_iter(काष्ठा kiocb *iocb,
					काष्ठा iov_iter *from)
अणु
	sमाप_प्रकार ret;
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (iocb->ki_flags & IOCB_NOWAIT)
		वापस -EOPNOTSUPP;

	ext4_fc_start_update(inode);
	inode_lock(inode);
	ret = ext4_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0)
		जाओ out;

	current->backing_dev_info = inode_to_bdi(inode);
	ret = generic_perक्रमm_ग_लिखो(iocb->ki_filp, from, iocb->ki_pos);
	current->backing_dev_info = शून्य;

out:
	inode_unlock(inode);
	ext4_fc_stop_update(inode);
	अगर (likely(ret > 0)) अणु
		iocb->ki_pos += ret;
		ret = generic_ग_लिखो_sync(iocb, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ext4_handle_inode_extension(काष्ठा inode *inode, loff_t offset,
					   sमाप_प्रकार written, माप_प्रकार count)
अणु
	handle_t *handle;
	bool truncate = false;
	u8 blkbits = inode->i_blkbits;
	ext4_lblk_t written_blk, end_blk;
	पूर्णांक ret;

	/*
	 * Note that EXT4_I(inode)->i_disksize can get extended up to
	 * inode->i_size जबतक the I/O was running due to ग_लिखोback of delalloc
	 * blocks. But, the code in ext4_iomap_alloc() is careful to use
	 * zeroed/unwritten extents अगर this is possible; thus we won't leave
	 * uninitialized blocks in a file even अगर we didn't succeed in writing
	 * as much as we पूर्णांकended.
	 */
	WARN_ON_ONCE(i_size_पढ़ो(inode) < EXT4_I(inode)->i_disksize);
	अगर (offset + count <= EXT4_I(inode)->i_disksize) अणु
		/*
		 * We need to ensure that the inode is हटाओd from the orphan
		 * list अगर it has been added prematurely, due to ग_लिखोback of
		 * delalloc blocks.
		 */
		अगर (!list_empty(&EXT4_I(inode)->i_orphan) && inode->i_nlink) अणु
			handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);

			अगर (IS_ERR(handle)) अणु
				ext4_orphan_del(शून्य, inode);
				वापस PTR_ERR(handle);
			पूर्ण

			ext4_orphan_del(handle, inode);
			ext4_journal_stop(handle);
		पूर्ण

		वापस written;
	पूर्ण

	अगर (written < 0)
		जाओ truncate;

	handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
	अगर (IS_ERR(handle)) अणु
		written = PTR_ERR(handle);
		जाओ truncate;
	पूर्ण

	अगर (ext4_update_inode_size(inode, offset + written)) अणु
		ret = ext4_mark_inode_dirty(handle, inode);
		अगर (unlikely(ret)) अणु
			written = ret;
			ext4_journal_stop(handle);
			जाओ truncate;
		पूर्ण
	पूर्ण

	/*
	 * We may need to truncate allocated but not written blocks beyond खातापूर्ण.
	 */
	written_blk = ALIGN(offset + written, 1 << blkbits);
	end_blk = ALIGN(offset + count, 1 << blkbits);
	अगर (written_blk < end_blk && ext4_can_truncate(inode))
		truncate = true;

	/*
	 * Remove the inode from the orphan list अगर it has been extended and
	 * everything went OK.
	 */
	अगर (!truncate && inode->i_nlink)
		ext4_orphan_del(handle, inode);
	ext4_journal_stop(handle);

	अगर (truncate) अणु
truncate:
		ext4_truncate_failed_ग_लिखो(inode);
		/*
		 * If the truncate operation failed early, then the inode may
		 * still be on the orphan list. In that हाल, we need to try
		 * हटाओ the inode from the in-memory linked list.
		 */
		अगर (inode->i_nlink)
			ext4_orphan_del(शून्य, inode);
	पूर्ण

	वापस written;
पूर्ण

अटल पूर्णांक ext4_dio_ग_लिखो_end_io(काष्ठा kiocb *iocb, sमाप_प्रकार size,
				 पूर्णांक error, अचिन्हित पूर्णांक flags)
अणु
	loff_t pos = iocb->ki_pos;
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (error)
		वापस error;

	अगर (size && flags & IOMAP_DIO_UNWRITTEN) अणु
		error = ext4_convert_unwritten_extents(शून्य, inode, pos, size);
		अगर (error < 0)
			वापस error;
	पूर्ण
	/*
	 * If we are extending the file, we have to update i_size here beक्रमe
	 * page cache माला_लो invalidated in iomap_dio_rw(). Otherwise racing
	 * buffered पढ़ोs could zero out too much from page cache pages. Update
	 * of on-disk size will happen later in ext4_dio_ग_लिखो_iter() where
	 * we have enough inक्रमmation to also perक्रमm orphan list handling etc.
	 * Note that we perक्रमm all extending ग_लिखोs synchronously under
	 * i_rwsem held exclusively so i_size update is safe here in that हाल.
	 * If the ग_लिखो was not extending, we cannot see pos > i_size here
	 * because operations reducing i_size like truncate रुको क्रम all
	 * outstanding DIO beक्रमe updating i_size.
	 */
	pos += size;
	अगर (pos > i_size_पढ़ो(inode))
		i_size_ग_लिखो(inode, pos);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iomap_dio_ops ext4_dio_ग_लिखो_ops = अणु
	.end_io = ext4_dio_ग_लिखो_end_io,
पूर्ण;

/*
 * The पूर्णांकention here is to start with shared lock acquired then see अगर any
 * condition requires an exclusive inode lock. If yes, then we restart the
 * whole operation by releasing the shared lock and acquiring exclusive lock.
 *
 * - For unaligned_io we never take shared lock as it may cause data corruption
 *   when two unaligned IO tries to modअगरy the same block e.g. जबतक zeroing.
 *
 * - For extending ग_लिखोs हाल we करोn't take the shared lock, since it requires
 *   updating inode i_disksize and/or orphan handling with exclusive lock.
 *
 * - shared locking will only be true mostly with overग_लिखोs. Otherwise we will
 *   चयन to exclusive i_rwsem lock.
 */
अटल sमाप_प्रकार ext4_dio_ग_लिखो_checks(काष्ठा kiocb *iocb, काष्ठा iov_iter *from,
				     bool *ilock_shared, bool *extend)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	loff_t offset;
	माप_प्रकार count;
	sमाप_प्रकार ret;

restart:
	ret = ext4_generic_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0)
		जाओ out;

	offset = iocb->ki_pos;
	count = ret;
	अगर (ext4_extending_io(inode, offset, count))
		*extend = true;
	/*
	 * Determine whether the IO operation will overग_लिखो allocated
	 * and initialized blocks.
	 * We need exclusive i_rwsem क्रम changing security info
	 * in file_modअगरied().
	 */
	अगर (*ilock_shared && (!IS_NOSEC(inode) || *extend ||
	     !ext4_overग_लिखो_io(inode, offset, count))) अणु
		अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
			ret = -EAGAIN;
			जाओ out;
		पूर्ण
		inode_unlock_shared(inode);
		*ilock_shared = false;
		inode_lock(inode);
		जाओ restart;
	पूर्ण

	ret = file_modअगरied(file);
	अगर (ret < 0)
		जाओ out;

	वापस count;
out:
	अगर (*ilock_shared)
		inode_unlock_shared(inode);
	अन्यथा
		inode_unlock(inode);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ext4_dio_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	sमाप_प्रकार ret;
	handle_t *handle;
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	loff_t offset = iocb->ki_pos;
	माप_प्रकार count = iov_iter_count(from);
	स्थिर काष्ठा iomap_ops *iomap_ops = &ext4_iomap_ops;
	bool extend = false, unaligned_io = false;
	bool ilock_shared = true;

	/*
	 * We initially start with shared inode lock unless it is
	 * unaligned IO which needs exclusive lock anyways.
	 */
	अगर (ext4_unaligned_io(inode, from, offset)) अणु
		unaligned_io = true;
		ilock_shared = false;
	पूर्ण
	/*
	 * Quick check here without any i_rwsem lock to see अगर it is extending
	 * IO. A more reliable check is करोne in ext4_dio_ग_लिखो_checks() with
	 * proper locking in place.
	 */
	अगर (offset + count > i_size_पढ़ो(inode))
		ilock_shared = false;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (ilock_shared) अणु
			अगर (!inode_trylock_shared(inode))
				वापस -EAGAIN;
		पूर्ण अन्यथा अणु
			अगर (!inode_trylock(inode))
				वापस -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ilock_shared)
			inode_lock_shared(inode);
		अन्यथा
			inode_lock(inode);
	पूर्ण

	/* Fallback to buffered I/O अगर the inode करोes not support direct I/O. */
	अगर (!ext4_dio_supported(inode)) अणु
		अगर (ilock_shared)
			inode_unlock_shared(inode);
		अन्यथा
			inode_unlock(inode);
		वापस ext4_buffered_ग_लिखो_iter(iocb, from);
	पूर्ण

	ret = ext4_dio_ग_लिखो_checks(iocb, from, &ilock_shared, &extend);
	अगर (ret <= 0)
		वापस ret;

	/* अगर we're going to block and IOCB_NOWAIT is set, वापस -EAGAIN */
	अगर ((iocb->ki_flags & IOCB_NOWAIT) && (unaligned_io || extend)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	offset = iocb->ki_pos;
	count = ret;

	/*
	 * Unaligned direct IO must be serialized among each other as zeroing
	 * of partial blocks of two competing unaligned IOs can result in data
	 * corruption.
	 *
	 * So we make sure we करोn't allow any unaligned IO in flight.
	 * For IOs where we need not रुको (like unaligned non-AIO DIO),
	 * below inode_dio_रुको() may anyway become a no-op, since we start
	 * with exclusive lock.
	 */
	अगर (unaligned_io)
		inode_dio_रुको(inode);

	अगर (extend) अणु
		handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
		अगर (IS_ERR(handle)) अणु
			ret = PTR_ERR(handle);
			जाओ out;
		पूर्ण

		ext4_fc_start_update(inode);
		ret = ext4_orphan_add(handle, inode);
		ext4_fc_stop_update(inode);
		अगर (ret) अणु
			ext4_journal_stop(handle);
			जाओ out;
		पूर्ण

		ext4_journal_stop(handle);
	पूर्ण

	अगर (ilock_shared)
		iomap_ops = &ext4_iomap_overग_लिखो_ops;
	ret = iomap_dio_rw(iocb, from, iomap_ops, &ext4_dio_ग_लिखो_ops,
			   (unaligned_io || extend) ? IOMAP_DIO_FORCE_WAIT : 0);
	अगर (ret == -ENOTBLK)
		ret = 0;

	अगर (extend)
		ret = ext4_handle_inode_extension(inode, offset, ret, count);

out:
	अगर (ilock_shared)
		inode_unlock_shared(inode);
	अन्यथा
		inode_unlock(inode);

	अगर (ret >= 0 && iov_iter_count(from)) अणु
		sमाप_प्रकार err;
		loff_t endbyte;

		offset = iocb->ki_pos;
		err = ext4_buffered_ग_लिखो_iter(iocb, from);
		अगर (err < 0)
			वापस err;

		/*
		 * We need to ensure that the pages within the page cache क्रम
		 * the range covered by this I/O are written to disk and
		 * invalidated. This is in attempt to preserve the expected
		 * direct I/O semantics in the हाल we fallback to buffered I/O
		 * to complete off the I/O request.
		 */
		ret += err;
		endbyte = offset + err - 1;
		err = filemap_ग_लिखो_and_रुको_range(iocb->ki_filp->f_mapping,
						   offset, endbyte);
		अगर (!err)
			invalidate_mapping_pages(iocb->ki_filp->f_mapping,
						 offset >> PAGE_SHIFT,
						 endbyte >> PAGE_SHIFT);
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_FS_DAX
अटल sमाप_प्रकार
ext4_dax_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	sमाप_प्रकार ret;
	माप_प्रकार count;
	loff_t offset;
	handle_t *handle;
	bool extend = false;
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock(inode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		inode_lock(inode);
	पूर्ण

	ret = ext4_ग_लिखो_checks(iocb, from);
	अगर (ret <= 0)
		जाओ out;

	offset = iocb->ki_pos;
	count = iov_iter_count(from);

	अगर (offset + count > EXT4_I(inode)->i_disksize) अणु
		handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
		अगर (IS_ERR(handle)) अणु
			ret = PTR_ERR(handle);
			जाओ out;
		पूर्ण

		ret = ext4_orphan_add(handle, inode);
		अगर (ret) अणु
			ext4_journal_stop(handle);
			जाओ out;
		पूर्ण

		extend = true;
		ext4_journal_stop(handle);
	पूर्ण

	ret = dax_iomap_rw(iocb, from, &ext4_iomap_ops);

	अगर (extend)
		ret = ext4_handle_inode_extension(inode, offset, ret, count);
out:
	inode_unlock(inode);
	अगर (ret > 0)
		ret = generic_ग_लिखो_sync(iocb, ret);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार
ext4_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

#अगर_घोषित CONFIG_FS_DAX
	अगर (IS_DAX(inode))
		वापस ext4_dax_ग_लिखो_iter(iocb, from);
#पूर्ण_अगर
	अगर (iocb->ki_flags & IOCB_सूचीECT)
		वापस ext4_dio_ग_लिखो_iter(iocb, from);
	अन्यथा
		वापस ext4_buffered_ग_लिखो_iter(iocb, from);
पूर्ण

#अगर_घोषित CONFIG_FS_DAX
अटल vm_fault_t ext4_dax_huge_fault(काष्ठा vm_fault *vmf,
		क्रमागत page_entry_size pe_size)
अणु
	पूर्णांक error = 0;
	vm_fault_t result;
	पूर्णांक retries = 0;
	handle_t *handle = शून्य;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा super_block *sb = inode->i_sb;

	/*
	 * We have to distinguish real ग_लिखोs from ग_लिखोs which will result in a
	 * COW page; COW ग_लिखोs should *not* poke the journal (the file will not
	 * be changed). Doing so would cause unपूर्णांकended failures when mounted
	 * पढ़ो-only.
	 *
	 * We check क्रम VM_SHARED rather than vmf->cow_page since the latter is
	 * unset क्रम pe_size != PE_SIZE_PTE (i.e. only in करो_cow_fault); क्रम
	 * other sizes, dax_iomap_fault will handle splitting / fallback so that
	 * we eventually come back with a COW page.
	 */
	bool ग_लिखो = (vmf->flags & FAULT_FLAG_WRITE) &&
		(vmf->vma->vm_flags & VM_SHARED);
	pfn_t pfn;

	अगर (ग_लिखो) अणु
		sb_start_pagefault(sb);
		file_update_समय(vmf->vma->vm_file);
		करोwn_पढ़ो(&EXT4_I(inode)->i_mmap_sem);
retry:
		handle = ext4_journal_start_sb(sb, EXT4_HT_WRITE_PAGE,
					       EXT4_DATA_TRANS_BLOCKS(sb));
		अगर (IS_ERR(handle)) अणु
			up_पढ़ो(&EXT4_I(inode)->i_mmap_sem);
			sb_end_pagefault(sb);
			वापस VM_FAULT_SIGBUS;
		पूर्ण
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&EXT4_I(inode)->i_mmap_sem);
	पूर्ण
	result = dax_iomap_fault(vmf, pe_size, &pfn, &error, &ext4_iomap_ops);
	अगर (ग_लिखो) अणु
		ext4_journal_stop(handle);

		अगर ((result & VM_FAULT_ERROR) && error == -ENOSPC &&
		    ext4_should_retry_alloc(sb, &retries))
			जाओ retry;
		/* Handling synchronous page fault? */
		अगर (result & VM_FAULT_NEEDDSYNC)
			result = dax_finish_sync_fault(vmf, pe_size, pfn);
		up_पढ़ो(&EXT4_I(inode)->i_mmap_sem);
		sb_end_pagefault(sb);
	पूर्ण अन्यथा अणु
		up_पढ़ो(&EXT4_I(inode)->i_mmap_sem);
	पूर्ण

	वापस result;
पूर्ण

अटल vm_fault_t ext4_dax_fault(काष्ठा vm_fault *vmf)
अणु
	वापस ext4_dax_huge_fault(vmf, PE_SIZE_PTE);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा ext4_dax_vm_ops = अणु
	.fault		= ext4_dax_fault,
	.huge_fault	= ext4_dax_huge_fault,
	.page_mkग_लिखो	= ext4_dax_fault,
	.pfn_mkग_लिखो	= ext4_dax_fault,
पूर्ण;
#अन्यथा
#घोषणा ext4_dax_vm_ops	ext4_file_vm_ops
#पूर्ण_अगर

अटल स्थिर काष्ठा vm_operations_काष्ठा ext4_file_vm_ops = अणु
	.fault		= ext4_filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो   = ext4_page_mkग_लिखो,
पूर्ण;

अटल पूर्णांक ext4_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा dax_device *dax_dev = sbi->s_daxdev;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(sbi)))
		वापस -EIO;

	/*
	 * We करोn't support synchronous mappings क्रम non-DAX files and
	 * क्रम DAX files अगर underneath dax_device is not synchronous.
	 */
	अगर (!daxdev_mapping_supported(vma, dax_dev))
		वापस -EOPNOTSUPP;

	file_accessed(file);
	अगर (IS_DAX(file_inode(file))) अणु
		vma->vm_ops = &ext4_dax_vm_ops;
		vma->vm_flags |= VM_HUGEPAGE;
	पूर्ण अन्यथा अणु
		vma->vm_ops = &ext4_file_vm_ops;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_sample_last_mounted(काष्ठा super_block *sb,
				    काष्ठा vfsmount *mnt)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा path path;
	अक्षर buf[64], *cp;
	handle_t *handle;
	पूर्णांक err;

	अगर (likely(ext4_test_mount_flag(sb, EXT4_MF_MNTसूची_SAMPLED)))
		वापस 0;

	अगर (sb_rकरोnly(sb) || !sb_start_पूर्णांकग_लिखो_trylock(sb))
		वापस 0;

	ext4_set_mount_flag(sb, EXT4_MF_MNTसूची_SAMPLED);
	/*
	 * Sample where the fileप्रणाली has been mounted and
	 * store it in the superblock क्रम sysadmin convenience
	 * when trying to sort through large numbers of block
	 * devices or fileप्रणाली images.
	 */
	स_रखो(buf, 0, माप(buf));
	path.mnt = mnt;
	path.dentry = mnt->mnt_root;
	cp = d_path(&path, buf, माप(buf));
	err = 0;
	अगर (IS_ERR(cp))
		जाओ out;

	handle = ext4_journal_start_sb(sb, EXT4_HT_MISC, 1);
	err = PTR_ERR(handle);
	अगर (IS_ERR(handle))
		जाओ out;
	BUFFER_TRACE(sbi->s_sbh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, sbi->s_sbh);
	अगर (err)
		जाओ out_journal;
	lock_buffer(sbi->s_sbh);
	म_नकलन(sbi->s_es->s_last_mounted, cp,
		माप(sbi->s_es->s_last_mounted));
	ext4_superblock_csum_set(sb);
	unlock_buffer(sbi->s_sbh);
	ext4_handle_dirty_metadata(handle, शून्य, sbi->s_sbh);
out_journal:
	ext4_journal_stop(handle);
out:
	sb_end_पूर्णांकग_लिखो(sb);
	वापस err;
पूर्ण

अटल पूर्णांक ext4_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	ret = ext4_sample_last_mounted(inode->i_sb, filp->f_path.mnt);
	अगर (ret)
		वापस ret;

	ret = fscrypt_file_खोलो(inode, filp);
	अगर (ret)
		वापस ret;

	ret = fsverity_file_खोलो(inode, filp);
	अगर (ret)
		वापस ret;

	/*
	 * Set up the jbd2_inode अगर we are खोलोing the inode क्रम
	 * writing and the journal is present
	 */
	अगर (filp->f_mode & FMODE_WRITE) अणु
		ret = ext4_inode_attach_jinode(inode);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	filp->f_mode |= FMODE_NOWAIT | FMODE_BUF_RASYNC;
	वापस dquot_file_खोलो(inode, filp);
पूर्ण

/*
 * ext4_llseek() handles both block-mapped and extent-mapped maxbytes values
 * by calling generic_file_llseek_size() with the appropriate maxbytes
 * value क्रम each.
 */
loff_t ext4_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	loff_t maxbytes;

	अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		maxbytes = EXT4_SB(inode->i_sb)->s_biपंचांगap_maxbytes;
	अन्यथा
		maxbytes = inode->i_sb->s_maxbytes;

	चयन (whence) अणु
	शेष:
		वापस generic_file_llseek_size(file, offset, whence,
						maxbytes, i_size_पढ़ो(inode));
	हाल SEEK_HOLE:
		inode_lock_shared(inode);
		offset = iomap_seek_hole(inode, offset,
					 &ext4_iomap_report_ops);
		inode_unlock_shared(inode);
		अवरोध;
	हाल SEEK_DATA:
		inode_lock_shared(inode);
		offset = iomap_seek_data(inode, offset,
					 &ext4_iomap_report_ops);
		inode_unlock_shared(inode);
		अवरोध;
	पूर्ण

	अगर (offset < 0)
		वापस offset;
	वापस vfs_setpos(file, offset, maxbytes);
पूर्ण

स्थिर काष्ठा file_operations ext4_file_operations = अणु
	.llseek		= ext4_llseek,
	.पढ़ो_iter	= ext4_file_पढ़ो_iter,
	.ग_लिखो_iter	= ext4_file_ग_लिखो_iter,
	.iopoll		= iomap_dio_iopoll,
	.unlocked_ioctl = ext4_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= ext4_compat_ioctl,
#पूर्ण_अगर
	.mmap		= ext4_file_mmap,
	.mmap_supported_flags = MAP_SYNC,
	.खोलो		= ext4_file_खोलो,
	.release	= ext4_release_file,
	.fsync		= ext4_sync_file,
	.get_unmapped_area = thp_get_unmapped_area,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.fallocate	= ext4_fallocate,
पूर्ण;

स्थिर काष्ठा inode_operations ext4_file_inode_operations = अणु
	.setattr	= ext4_setattr,
	.getattr	= ext4_file_getattr,
	.listxattr	= ext4_listxattr,
	.get_acl	= ext4_get_acl,
	.set_acl	= ext4_set_acl,
	.fiemap		= ext4_fiemap,
	.fileattr_get	= ext4_fileattr_get,
	.fileattr_set	= ext4_fileattr_set,
पूर्ण;

