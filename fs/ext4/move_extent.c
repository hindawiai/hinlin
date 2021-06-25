<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (c) 2008,2009 NEC Software Tohoku, Ltd.
 * Written by Takashi Sato <t-sato@yk.jp.nec.com>
 *            Akira Fujita <a-fujita@rs.jp.nec.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/slab.h>
#समावेश "ext4_jbd2.h"
#समावेश "ext4.h"
#समावेश "ext4_extents.h"

/**
 * get_ext_path() - Find an extent path क्रम designated logical block number.
 * @inode:	inode to be searched
 * @lblock:	logical block number to find an extent path
 * @ppath:	poपूर्णांकer to an extent path poपूर्णांकer (क्रम output)
 *
 * ext4_find_extent wrapper. Return 0 on success, or a negative error value
 * on failure.
 */
अटल अंतरभूत पूर्णांक
get_ext_path(काष्ठा inode *inode, ext4_lblk_t lblock,
		काष्ठा ext4_ext_path **ppath)
अणु
	काष्ठा ext4_ext_path *path;

	path = ext4_find_extent(inode, lblock, ppath, EXT4_EX_NOCACHE);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);
	अगर (path[ext_depth(inode)].p_ext == शून्य) अणु
		ext4_ext_drop_refs(path);
		kमुक्त(path);
		*ppath = शून्य;
		वापस -ENODATA;
	पूर्ण
	*ppath = path;
	वापस 0;
पूर्ण

/**
 * ext4_द्विगुन_करोwn_ग_लिखो_data_sem() - ग_लिखो lock two inodes's i_data_sem
 * @first: inode to be locked
 * @second: inode to be locked
 *
 * Acquire ग_लिखो lock of i_data_sem of the two inodes
 */
व्योम
ext4_द्विगुन_करोwn_ग_लिखो_data_sem(काष्ठा inode *first, काष्ठा inode *second)
अणु
	अगर (first < second) अणु
		करोwn_ग_लिखो(&EXT4_I(first)->i_data_sem);
		करोwn_ग_लिखो_nested(&EXT4_I(second)->i_data_sem, I_DATA_SEM_OTHER);
	पूर्ण अन्यथा अणु
		करोwn_ग_लिखो(&EXT4_I(second)->i_data_sem);
		करोwn_ग_लिखो_nested(&EXT4_I(first)->i_data_sem, I_DATA_SEM_OTHER);

	पूर्ण
पूर्ण

/**
 * ext4_द्विगुन_up_ग_लिखो_data_sem - Release two inodes' ग_लिखो lock of i_data_sem
 *
 * @orig_inode:		original inode काष्ठाure to be released its lock first
 * @करोnor_inode:	करोnor inode काष्ठाure to be released its lock second
 * Release ग_लिखो lock of i_data_sem of two inodes (orig and करोnor).
 */
व्योम
ext4_द्विगुन_up_ग_लिखो_data_sem(काष्ठा inode *orig_inode,
			      काष्ठा inode *करोnor_inode)
अणु
	up_ग_लिखो(&EXT4_I(orig_inode)->i_data_sem);
	up_ग_लिखो(&EXT4_I(करोnor_inode)->i_data_sem);
पूर्ण

/**
 * mext_check_coverage - Check that all extents in range has the same type
 *
 * @inode:		inode in question
 * @from:		block offset of inode
 * @count:		block count to be checked
 * @unwritten:		extents expected to be unwritten
 * @err:		poपूर्णांकer to save error value
 *
 * Return 1 अगर all extents in range has expected type, and zero otherwise.
 */
अटल पूर्णांक
mext_check_coverage(काष्ठा inode *inode, ext4_lblk_t from, ext4_lblk_t count,
		    पूर्णांक unwritten, पूर्णांक *err)
अणु
	काष्ठा ext4_ext_path *path = शून्य;
	काष्ठा ext4_extent *ext;
	पूर्णांक ret = 0;
	ext4_lblk_t last = from + count;
	जबतक (from < last) अणु
		*err = get_ext_path(inode, from, &path);
		अगर (*err)
			जाओ out;
		ext = path[ext_depth(inode)].p_ext;
		अगर (unwritten != ext4_ext_is_unwritten(ext))
			जाओ out;
		from += ext4_ext_get_actual_len(ext);
		ext4_ext_drop_refs(path);
	पूर्ण
	ret = 1;
out:
	ext4_ext_drop_refs(path);
	kमुक्त(path);
	वापस ret;
पूर्ण

/**
 * mext_page_द्विगुन_lock - Grab and lock pages on both @inode1 and @inode2
 *
 * @inode1:	the inode काष्ठाure
 * @inode2:	the inode काष्ठाure
 * @index1:	page index
 * @index2:	page index
 * @page:	result page vector
 *
 * Grab two locked pages क्रम inode's by inode order
 */
अटल पूर्णांक
mext_page_द्विगुन_lock(काष्ठा inode *inode1, काष्ठा inode *inode2,
		      pgoff_t index1, pgoff_t index2, काष्ठा page *page[2])
अणु
	काष्ठा address_space *mapping[2];
	अचिन्हित fl = AOP_FLAG_NOFS;

	BUG_ON(!inode1 || !inode2);
	अगर (inode1 < inode2) अणु
		mapping[0] = inode1->i_mapping;
		mapping[1] = inode2->i_mapping;
	पूर्ण अन्यथा अणु
		swap(index1, index2);
		mapping[0] = inode2->i_mapping;
		mapping[1] = inode1->i_mapping;
	पूर्ण

	page[0] = grab_cache_page_ग_लिखो_begin(mapping[0], index1, fl);
	अगर (!page[0])
		वापस -ENOMEM;

	page[1] = grab_cache_page_ग_लिखो_begin(mapping[1], index2, fl);
	अगर (!page[1]) अणु
		unlock_page(page[0]);
		put_page(page[0]);
		वापस -ENOMEM;
	पूर्ण
	/*
	 * grab_cache_page_ग_लिखो_begin() may not रुको on page's ग_लिखोback अगर
	 * BDI not demand that. But it is reasonable to be very conservative
	 * here and explicitly रुको on page's ग_लिखोback
	 */
	रुको_on_page_ग_लिखोback(page[0]);
	रुको_on_page_ग_लिखोback(page[1]);
	अगर (inode1 > inode2)
		swap(page[0], page[1]);

	वापस 0;
पूर्ण

/* Force page buffers uptodate w/o dropping page's lock */
अटल पूर्णांक
mext_page_mkuptodate(काष्ठा page *page, अचिन्हित from, अचिन्हित to)
अणु
	काष्ठा inode *inode = page->mapping->host;
	sector_t block;
	काष्ठा buffer_head *bh, *head, *arr[MAX_BUF_PER_PAGE];
	अचिन्हित पूर्णांक blocksize, block_start, block_end;
	पूर्णांक i, err,  nr = 0, partial = 0;
	BUG_ON(!PageLocked(page));
	BUG_ON(PageWriteback(page));

	अगर (PageUptodate(page))
		वापस 0;

	blocksize = i_blocksize(inode);
	अगर (!page_has_buffers(page))
		create_empty_buffers(page, blocksize, 0);

	head = page_buffers(page);
	block = (sector_t)page->index << (PAGE_SHIFT - inode->i_blkbits);
	क्रम (bh = head, block_start = 0; bh != head || !block_start;
	     block++, block_start = block_end, bh = bh->b_this_page) अणु
		block_end = block_start + blocksize;
		अगर (block_end <= from || block_start >= to) अणु
			अगर (!buffer_uptodate(bh))
				partial = 1;
			जारी;
		पूर्ण
		अगर (buffer_uptodate(bh))
			जारी;
		अगर (!buffer_mapped(bh)) अणु
			err = ext4_get_block(inode, block, bh, 0);
			अगर (err) अणु
				SetPageError(page);
				वापस err;
			पूर्ण
			अगर (!buffer_mapped(bh)) अणु
				zero_user(page, block_start, blocksize);
				set_buffer_uptodate(bh);
				जारी;
			पूर्ण
		पूर्ण
		BUG_ON(nr >= MAX_BUF_PER_PAGE);
		arr[nr++] = bh;
	पूर्ण
	/* No io required */
	अगर (!nr)
		जाओ out;

	क्रम (i = 0; i < nr; i++) अणु
		bh = arr[i];
		अगर (!bh_uptodate_or_lock(bh)) अणु
			err = ext4_पढ़ो_bh(bh, 0, शून्य);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
out:
	अगर (!partial)
		SetPageUptodate(page);
	वापस 0;
पूर्ण

/**
 * move_extent_per_page - Move extent data per page
 *
 * @o_filp:			file काष्ठाure of original file
 * @करोnor_inode:		करोnor inode
 * @orig_page_offset:		page index on original file
 * @करोnor_page_offset:		page index on करोnor file
 * @data_offset_in_page:	block index where data swapping starts
 * @block_len_in_page:		the number of blocks to be swapped
 * @unwritten:			orig extent is unwritten or not
 * @err:			poपूर्णांकer to save वापस value
 *
 * Save the data in original inode blocks and replace original inode extents
 * with करोnor inode extents by calling ext4_swap_extents().
 * Finally, ग_लिखो out the saved data in new original inode blocks. Return
 * replaced block count.
 */
अटल पूर्णांक
move_extent_per_page(काष्ठा file *o_filp, काष्ठा inode *करोnor_inode,
		     pgoff_t orig_page_offset, pgoff_t करोnor_page_offset,
		     पूर्णांक data_offset_in_page,
		     पूर्णांक block_len_in_page, पूर्णांक unwritten, पूर्णांक *err)
अणु
	काष्ठा inode *orig_inode = file_inode(o_filp);
	काष्ठा page *pagep[2] = अणुशून्य, शून्यपूर्ण;
	handle_t *handle;
	ext4_lblk_t orig_blk_offset, करोnor_blk_offset;
	अचिन्हित दीर्घ blocksize = orig_inode->i_sb->s_blocksize;
	अचिन्हित पूर्णांक पंचांगp_data_size, data_size, replaced_size;
	पूर्णांक i, err2, jblocks, retries = 0;
	पूर्णांक replaced_count = 0;
	पूर्णांक from = data_offset_in_page << orig_inode->i_blkbits;
	पूर्णांक blocks_per_page = PAGE_SIZE >> orig_inode->i_blkbits;
	काष्ठा super_block *sb = orig_inode->i_sb;
	काष्ठा buffer_head *bh = शून्य;

	/*
	 * It needs twice the amount of ordinary journal buffers because
	 * inode and करोnor_inode may change each dअगरferent metadata blocks.
	 */
again:
	*err = 0;
	jblocks = ext4_ग_लिखोpage_trans_blocks(orig_inode) * 2;
	handle = ext4_journal_start(orig_inode, EXT4_HT_MOVE_EXTENTS, jblocks);
	अगर (IS_ERR(handle)) अणु
		*err = PTR_ERR(handle);
		वापस 0;
	पूर्ण

	orig_blk_offset = orig_page_offset * blocks_per_page +
		data_offset_in_page;

	करोnor_blk_offset = करोnor_page_offset * blocks_per_page +
		data_offset_in_page;

	/* Calculate data_size */
	अगर ((orig_blk_offset + block_len_in_page - 1) ==
	    ((orig_inode->i_size - 1) >> orig_inode->i_blkbits)) अणु
		/* Replace the last block */
		पंचांगp_data_size = orig_inode->i_size & (blocksize - 1);
		/*
		 * If data_size equal zero, it shows data_size is multiples of
		 * blocksize. So we set appropriate value.
		 */
		अगर (पंचांगp_data_size == 0)
			पंचांगp_data_size = blocksize;

		data_size = पंचांगp_data_size +
			((block_len_in_page - 1) << orig_inode->i_blkbits);
	पूर्ण अन्यथा
		data_size = block_len_in_page << orig_inode->i_blkbits;

	replaced_size = data_size;

	*err = mext_page_द्विगुन_lock(orig_inode, करोnor_inode, orig_page_offset,
				     करोnor_page_offset, pagep);
	अगर (unlikely(*err < 0))
		जाओ stop_journal;
	/*
	 * If orig extent was unwritten it can become initialized
	 * at any समय after i_data_sem was dropped, in order to
	 * serialize with delalloc we have recheck extent जबतक we
	 * hold page's lock, अगर it is still the हाल data copy is not
	 * necessary, just swap data blocks between orig and करोnor.
	 */
	अगर (unwritten) अणु
		ext4_द्विगुन_करोwn_ग_लिखो_data_sem(orig_inode, करोnor_inode);
		/* If any of extents in range became initialized we have to
		 * fallback to data copying */
		unwritten = mext_check_coverage(orig_inode, orig_blk_offset,
						block_len_in_page, 1, err);
		अगर (*err)
			जाओ drop_data_sem;

		unwritten &= mext_check_coverage(करोnor_inode, करोnor_blk_offset,
						 block_len_in_page, 1, err);
		अगर (*err)
			जाओ drop_data_sem;

		अगर (!unwritten) अणु
			ext4_द्विगुन_up_ग_लिखो_data_sem(orig_inode, करोnor_inode);
			जाओ data_copy;
		पूर्ण
		अगर ((page_has_निजी(pagep[0]) &&
		     !try_to_release_page(pagep[0], 0)) ||
		    (page_has_निजी(pagep[1]) &&
		     !try_to_release_page(pagep[1], 0))) अणु
			*err = -EBUSY;
			जाओ drop_data_sem;
		पूर्ण
		replaced_count = ext4_swap_extents(handle, orig_inode,
						   करोnor_inode, orig_blk_offset,
						   करोnor_blk_offset,
						   block_len_in_page, 1, err);
	drop_data_sem:
		ext4_द्विगुन_up_ग_लिखो_data_sem(orig_inode, करोnor_inode);
		जाओ unlock_pages;
	पूर्ण
data_copy:
	*err = mext_page_mkuptodate(pagep[0], from, from + replaced_size);
	अगर (*err)
		जाओ unlock_pages;

	/* At this poपूर्णांक all buffers in range are uptodate, old mapping layout
	 * is no दीर्घer required, try to drop it now. */
	अगर ((page_has_निजी(pagep[0]) && !try_to_release_page(pagep[0], 0)) ||
	    (page_has_निजी(pagep[1]) && !try_to_release_page(pagep[1], 0))) अणु
		*err = -EBUSY;
		जाओ unlock_pages;
	पूर्ण
	ext4_द्विगुन_करोwn_ग_लिखो_data_sem(orig_inode, करोnor_inode);
	replaced_count = ext4_swap_extents(handle, orig_inode, करोnor_inode,
					       orig_blk_offset, करोnor_blk_offset,
					   block_len_in_page, 1, err);
	ext4_द्विगुन_up_ग_लिखो_data_sem(orig_inode, करोnor_inode);
	अगर (*err) अणु
		अगर (replaced_count) अणु
			block_len_in_page = replaced_count;
			replaced_size =
				block_len_in_page << orig_inode->i_blkbits;
		पूर्ण अन्यथा
			जाओ unlock_pages;
	पूर्ण
	/* Perक्रमm all necessary steps similar ग_लिखो_begin()/ग_लिखो_end()
	 * but keeping in mind that i_size will not change */
	अगर (!page_has_buffers(pagep[0]))
		create_empty_buffers(pagep[0], 1 << orig_inode->i_blkbits, 0);
	bh = page_buffers(pagep[0]);
	क्रम (i = 0; i < data_offset_in_page; i++)
		bh = bh->b_this_page;
	क्रम (i = 0; i < block_len_in_page; i++) अणु
		*err = ext4_get_block(orig_inode, orig_blk_offset + i, bh, 0);
		अगर (*err < 0)
			अवरोध;
		bh = bh->b_this_page;
	पूर्ण
	अगर (!*err)
		*err = block_commit_ग_लिखो(pagep[0], from, from + replaced_size);

	अगर (unlikely(*err < 0))
		जाओ repair_branches;

	/* Even in हाल of data=ग_लिखोback it is reasonable to pin
	 * inode to transaction, to prevent unexpected data loss */
	*err = ext4_jbd2_inode_add_ग_लिखो(handle, orig_inode,
			(loff_t)orig_page_offset << PAGE_SHIFT, replaced_size);

unlock_pages:
	unlock_page(pagep[0]);
	put_page(pagep[0]);
	unlock_page(pagep[1]);
	put_page(pagep[1]);
stop_journal:
	ext4_journal_stop(handle);
	अगर (*err == -ENOSPC &&
	    ext4_should_retry_alloc(sb, &retries))
		जाओ again;
	/* Buffer was busy because probably is pinned to journal transaction,
	 * क्रमce transaction commit may help to मुक्त it. */
	अगर (*err == -EBUSY && retries++ < 4 && EXT4_SB(sb)->s_journal &&
	    jbd2_journal_क्रमce_commit_nested(EXT4_SB(sb)->s_journal))
		जाओ again;
	वापस replaced_count;

repair_branches:
	/*
	 * This should never ever happen!
	 * Extents are swapped alपढ़ोy, but we are not able to copy data.
	 * Try to swap extents to it's original places
	 */
	ext4_द्विगुन_करोwn_ग_लिखो_data_sem(orig_inode, करोnor_inode);
	replaced_count = ext4_swap_extents(handle, करोnor_inode, orig_inode,
					       orig_blk_offset, करोnor_blk_offset,
					   block_len_in_page, 0, &err2);
	ext4_द्विगुन_up_ग_लिखो_data_sem(orig_inode, करोnor_inode);
	अगर (replaced_count != block_len_in_page) अणु
		ext4_error_inode_block(orig_inode, (sector_t)(orig_blk_offset),
				       EIO, "Unable to copy data block,"
				       " data will be lost.");
		*err = -EIO;
	पूर्ण
	replaced_count = 0;
	जाओ unlock_pages;
पूर्ण

/**
 * mext_check_arguments - Check whether move extent can be करोne
 *
 * @orig_inode:		original inode
 * @करोnor_inode:	करोnor inode
 * @orig_start:		logical start offset in block क्रम orig
 * @करोnor_start:	logical start offset in block क्रम करोnor
 * @len:		the number of blocks to be moved
 *
 * Check the arguments of ext4_move_extents() whether the files can be
 * exchanged with each other.
 * Return 0 on success, or a negative error value on failure.
 */
अटल पूर्णांक
mext_check_arguments(काष्ठा inode *orig_inode,
		     काष्ठा inode *करोnor_inode, __u64 orig_start,
		     __u64 करोnor_start, __u64 *len)
अणु
	__u64 orig_eof, करोnor_eof;
	अचिन्हित पूर्णांक blkbits = orig_inode->i_blkbits;
	अचिन्हित पूर्णांक blocksize = 1 << blkbits;

	orig_eof = (i_size_पढ़ो(orig_inode) + blocksize - 1) >> blkbits;
	करोnor_eof = (i_size_पढ़ो(करोnor_inode) + blocksize - 1) >> blkbits;


	अगर (करोnor_inode->i_mode & (S_ISUID|S_ISGID)) अणु
		ext4_debug("ext4 move extent: suid or sgid is set"
			   " to donor file [ino:orig %lu, donor %lu]\n",
			   orig_inode->i_ino, करोnor_inode->i_ino);
		वापस -EINVAL;
	पूर्ण

	अगर (IS_IMMUTABLE(करोnor_inode) || IS_APPEND(करोnor_inode))
		वापस -EPERM;

	/* Ext4 move extent करोes not support swapfile */
	अगर (IS_SWAPखाता(orig_inode) || IS_SWAPखाता(करोnor_inode)) अणु
		ext4_debug("ext4 move extent: The argument files should "
			"not be swapfile [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, करोnor_inode->i_ino);
		वापस -EBUSY;
	पूर्ण

	अगर (ext4_is_quota_file(orig_inode) && ext4_is_quota_file(करोnor_inode)) अणु
		ext4_debug("ext4 move extent: The argument files should "
			"not be quota files [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, करोnor_inode->i_ino);
		वापस -EBUSY;
	पूर्ण

	/* Ext4 move extent supports only extent based file */
	अगर (!(ext4_test_inode_flag(orig_inode, EXT4_INODE_EXTENTS))) अणु
		ext4_debug("ext4 move extent: orig file is not extents "
			"based file [ino:orig %lu]\n", orig_inode->i_ino);
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (!(ext4_test_inode_flag(करोnor_inode, EXT4_INODE_EXTENTS))) अणु
		ext4_debug("ext4 move extent: donor file is not extents "
			"based file [ino:donor %lu]\n", करोnor_inode->i_ino);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((!orig_inode->i_size) || (!करोnor_inode->i_size)) अणु
		ext4_debug("ext4 move extent: File size is 0 byte\n");
		वापस -EINVAL;
	पूर्ण

	/* Start offset should be same */
	अगर ((orig_start & ~(PAGE_MASK >> orig_inode->i_blkbits)) !=
	    (करोnor_start & ~(PAGE_MASK >> orig_inode->i_blkbits))) अणु
		ext4_debug("ext4 move extent: orig and donor's start "
			"offsets are not aligned [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, करोnor_inode->i_ino);
		वापस -EINVAL;
	पूर्ण

	अगर ((orig_start >= EXT_MAX_BLOCKS) ||
	    (करोnor_start >= EXT_MAX_BLOCKS) ||
	    (*len > EXT_MAX_BLOCKS) ||
	    (करोnor_start + *len >= EXT_MAX_BLOCKS) ||
	    (orig_start + *len >= EXT_MAX_BLOCKS))  अणु
		ext4_debug("ext4 move extent: Can't handle over [%u] blocks "
			"[ino:orig %lu, donor %lu]\n", EXT_MAX_BLOCKS,
			orig_inode->i_ino, करोnor_inode->i_ino);
		वापस -EINVAL;
	पूर्ण
	अगर (orig_eof <= orig_start)
		*len = 0;
	अन्यथा अगर (orig_eof < orig_start + *len - 1)
		*len = orig_eof - orig_start;
	अगर (करोnor_eof <= करोnor_start)
		*len = 0;
	अन्यथा अगर (करोnor_eof < करोnor_start + *len - 1)
		*len = करोnor_eof - करोnor_start;
	अगर (!*len) अणु
		ext4_debug("ext4 move extent: len should not be 0 "
			"[ino:orig %lu, donor %lu]\n", orig_inode->i_ino,
			करोnor_inode->i_ino);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ext4_move_extents - Exchange the specअगरied range of a file
 *
 * @o_filp:		file काष्ठाure of the original file
 * @d_filp:		file काष्ठाure of the करोnor file
 * @orig_blk:		start offset in block क्रम orig
 * @करोnor_blk:		start offset in block क्रम करोnor
 * @len:		the number of blocks to be moved
 * @moved_len:		moved block length
 *
 * This function वापसs 0 and moved block length is set in moved_len
 * अगर succeed, otherwise वापसs error value.
 *
 */
पूर्णांक
ext4_move_extents(काष्ठा file *o_filp, काष्ठा file *d_filp, __u64 orig_blk,
		  __u64 करोnor_blk, __u64 len, __u64 *moved_len)
अणु
	काष्ठा inode *orig_inode = file_inode(o_filp);
	काष्ठा inode *करोnor_inode = file_inode(d_filp);
	काष्ठा ext4_ext_path *path = शून्य;
	पूर्णांक blocks_per_page = PAGE_SIZE >> orig_inode->i_blkbits;
	ext4_lblk_t o_end, o_start = orig_blk;
	ext4_lblk_t d_start = करोnor_blk;
	पूर्णांक ret;

	अगर (orig_inode->i_sb != करोnor_inode->i_sb) अणु
		ext4_debug("ext4 move extent: The argument files "
			"should be in same FS [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, करोnor_inode->i_ino);
		वापस -EINVAL;
	पूर्ण

	/* orig and करोnor should be dअगरferent inodes */
	अगर (orig_inode == करोnor_inode) अणु
		ext4_debug("ext4 move extent: The argument files should not "
			"be same inode [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, करोnor_inode->i_ino);
		वापस -EINVAL;
	पूर्ण

	/* Regular file check */
	अगर (!S_ISREG(orig_inode->i_mode) || !S_ISREG(करोnor_inode->i_mode)) अणु
		ext4_debug("ext4 move extent: The argument files should be "
			"regular file [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, करोnor_inode->i_ino);
		वापस -EINVAL;
	पूर्ण

	/* TODO: it's not obvious how to swap blocks क्रम inodes with full
	   journaling enabled */
	अगर (ext4_should_journal_data(orig_inode) ||
	    ext4_should_journal_data(करोnor_inode)) अणु
		ext4_msg(orig_inode->i_sb, KERN_ERR,
			 "Online defrag not supported with data journaling");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (IS_ENCRYPTED(orig_inode) || IS_ENCRYPTED(करोnor_inode)) अणु
		ext4_msg(orig_inode->i_sb, KERN_ERR,
			 "Online defrag not supported for encrypted files");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Protect orig and करोnor inodes against a truncate */
	lock_two_nondirectories(orig_inode, करोnor_inode);

	/* Wait क्रम all existing dio workers */
	inode_dio_रुको(orig_inode);
	inode_dio_रुको(करोnor_inode);

	/* Protect extent tree against block allocations via delalloc */
	ext4_द्विगुन_करोwn_ग_लिखो_data_sem(orig_inode, करोnor_inode);
	/* Check the fileप्रणाली environment whether move_extent can be करोne */
	ret = mext_check_arguments(orig_inode, करोnor_inode, orig_blk,
				    करोnor_blk, &len);
	अगर (ret)
		जाओ out;
	o_end = o_start + len;

	जबतक (o_start < o_end) अणु
		काष्ठा ext4_extent *ex;
		ext4_lblk_t cur_blk, next_blk;
		pgoff_t orig_page_index, करोnor_page_index;
		पूर्णांक offset_in_page;
		पूर्णांक unwritten, cur_len;

		ret = get_ext_path(orig_inode, o_start, &path);
		अगर (ret)
			जाओ out;
		ex = path[path->p_depth].p_ext;
		next_blk = ext4_ext_next_allocated_block(path);
		cur_blk = le32_to_cpu(ex->ee_block);
		cur_len = ext4_ext_get_actual_len(ex);
		/* Check hole beक्रमe the start pos */
		अगर (cur_blk + cur_len - 1 < o_start) अणु
			अगर (next_blk == EXT_MAX_BLOCKS) अणु
				o_start = o_end;
				ret = -ENODATA;
				जाओ out;
			पूर्ण
			d_start += next_blk - o_start;
			o_start = next_blk;
			जारी;
		/* Check hole after the start pos */
		पूर्ण अन्यथा अगर (cur_blk > o_start) अणु
			/* Skip hole */
			d_start += cur_blk - o_start;
			o_start = cur_blk;
			/* Extent inside requested range ?*/
			अगर (cur_blk >= o_end)
				जाओ out;
		पूर्ण अन्यथा अणु /* in_range(o_start, o_blk, o_len) */
			cur_len += cur_blk - o_start;
		पूर्ण
		unwritten = ext4_ext_is_unwritten(ex);
		अगर (o_end - o_start < cur_len)
			cur_len = o_end - o_start;

		orig_page_index = o_start >> (PAGE_SHIFT -
					       orig_inode->i_blkbits);
		करोnor_page_index = d_start >> (PAGE_SHIFT -
					       करोnor_inode->i_blkbits);
		offset_in_page = o_start % blocks_per_page;
		अगर (cur_len > blocks_per_page- offset_in_page)
			cur_len = blocks_per_page - offset_in_page;
		/*
		 * Up semaphore to aव्योम following problems:
		 * a. transaction deadlock among ext4_journal_start,
		 *    ->ग_लिखो_begin via pagefault, and jbd2_journal_commit
		 * b. racing with ->पढ़ोpage, ->ग_लिखो_begin, and ext4_get_block
		 *    in move_extent_per_page
		 */
		ext4_द्विगुन_up_ग_लिखो_data_sem(orig_inode, करोnor_inode);
		/* Swap original branches with new branches */
		move_extent_per_page(o_filp, करोnor_inode,
				     orig_page_index, करोnor_page_index,
				     offset_in_page, cur_len,
				     unwritten, &ret);
		ext4_द्विगुन_करोwn_ग_लिखो_data_sem(orig_inode, करोnor_inode);
		अगर (ret < 0)
			अवरोध;
		o_start += cur_len;
		d_start += cur_len;
	पूर्ण
	*moved_len = o_start - orig_blk;
	अगर (*moved_len > len)
		*moved_len = len;

out:
	अगर (*moved_len) अणु
		ext4_discard_pपुनः_स्मृतिations(orig_inode, 0);
		ext4_discard_pपुनः_स्मृतिations(करोnor_inode, 0);
	पूर्ण

	ext4_ext_drop_refs(path);
	kमुक्त(path);
	ext4_द्विगुन_up_ग_लिखो_data_sem(orig_inode, करोnor_inode);
	unlock_two_nondirectories(orig_inode, करोnor_inode);

	वापस ret;
पूर्ण
