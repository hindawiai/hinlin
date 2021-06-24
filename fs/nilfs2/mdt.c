<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * mdt.c - meta data file क्रम NILFS
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/mpage.h>
#समावेश <linux/mm.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश "nilfs.h"
#समावेश "btnode.h"
#समावेश "segment.h"
#समावेश "page.h"
#समावेश "mdt.h"
#समावेश "alloc.h"		/* nilfs_palloc_destroy_cache() */

#समावेश <trace/events/nilfs2.h>

#घोषणा NILFS_MDT_MAX_RA_BLOCKS		(16 - 1)


अटल पूर्णांक
nilfs_mdt_insert_new_block(काष्ठा inode *inode, अचिन्हित दीर्घ block,
			   काष्ठा buffer_head *bh,
			   व्योम (*init_block)(काष्ठा inode *,
					      काष्ठा buffer_head *, व्योम *))
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	व्योम *kaddr;
	पूर्णांक ret;

	/* Caller exclude पढ़ो accesses using page lock */

	/* set_buffer_new(bh); */
	bh->b_blocknr = 0;

	ret = nilfs_bmap_insert(ii->i_bmap, block, (अचिन्हित दीर्घ)bh);
	अगर (unlikely(ret))
		वापस ret;

	set_buffer_mapped(bh);

	kaddr = kmap_atomic(bh->b_page);
	स_रखो(kaddr + bh_offset(bh), 0, i_blocksize(inode));
	अगर (init_block)
		init_block(inode, bh, kaddr);
	flush_dcache_page(bh->b_page);
	kunmap_atomic(kaddr);

	set_buffer_uptodate(bh);
	mark_buffer_dirty(bh);
	nilfs_mdt_mark_dirty(inode);

	trace_nilfs2_mdt_insert_new_block(inode, inode->i_ino, block);

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_mdt_create_block(काष्ठा inode *inode, अचिन्हित दीर्घ block,
				  काष्ठा buffer_head **out_bh,
				  व्योम (*init_block)(काष्ठा inode *,
						     काष्ठा buffer_head *,
						     व्योम *))
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा nilfs_transaction_info ti;
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	nilfs_transaction_begin(sb, &ti, 0);

	err = -ENOMEM;
	bh = nilfs_grab_buffer(inode, inode->i_mapping, block, 0);
	अगर (unlikely(!bh))
		जाओ failed_unlock;

	err = -EEXIST;
	अगर (buffer_uptodate(bh))
		जाओ failed_bh;

	रुको_on_buffer(bh);
	अगर (buffer_uptodate(bh))
		जाओ failed_bh;

	bh->b_bdev = sb->s_bdev;
	err = nilfs_mdt_insert_new_block(inode, block, bh, init_block);
	अगर (likely(!err)) अणु
		get_bh(bh);
		*out_bh = bh;
	पूर्ण

 failed_bh:
	unlock_page(bh->b_page);
	put_page(bh->b_page);
	brअन्यथा(bh);

 failed_unlock:
	अगर (likely(!err))
		err = nilfs_transaction_commit(sb);
	अन्यथा
		nilfs_transaction_पात(sb);

	वापस err;
पूर्ण

अटल पूर्णांक
nilfs_mdt_submit_block(काष्ठा inode *inode, अचिन्हित दीर्घ blkoff,
		       पूर्णांक mode, पूर्णांक mode_flags, काष्ठा buffer_head **out_bh)
अणु
	काष्ठा buffer_head *bh;
	__u64 blknum = 0;
	पूर्णांक ret = -ENOMEM;

	bh = nilfs_grab_buffer(inode, inode->i_mapping, blkoff, 0);
	अगर (unlikely(!bh))
		जाओ failed;

	ret = -EEXIST; /* पूर्णांकernal code */
	अगर (buffer_uptodate(bh))
		जाओ out;

	अगर (mode_flags & REQ_RAHEAD) अणु
		अगर (!trylock_buffer(bh)) अणु
			ret = -EBUSY;
			जाओ failed_bh;
		पूर्ण
	पूर्ण अन्यथा /* mode == READ */
		lock_buffer(bh);

	अगर (buffer_uptodate(bh)) अणु
		unlock_buffer(bh);
		जाओ out;
	पूर्ण

	ret = nilfs_bmap_lookup(NILFS_I(inode)->i_bmap, blkoff, &blknum);
	अगर (unlikely(ret)) अणु
		unlock_buffer(bh);
		जाओ failed_bh;
	पूर्ण
	map_bh(bh, inode->i_sb, (sector_t)blknum);

	bh->b_end_io = end_buffer_पढ़ो_sync;
	get_bh(bh);
	submit_bh(mode, mode_flags, bh);
	ret = 0;

	trace_nilfs2_mdt_submit_block(inode, inode->i_ino, blkoff, mode);
 out:
	get_bh(bh);
	*out_bh = bh;

 failed_bh:
	unlock_page(bh->b_page);
	put_page(bh->b_page);
	brअन्यथा(bh);
 failed:
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_mdt_पढ़ो_block(काष्ठा inode *inode, अचिन्हित दीर्घ block,
				पूर्णांक पढ़ोahead, काष्ठा buffer_head **out_bh)
अणु
	काष्ठा buffer_head *first_bh, *bh;
	अचिन्हित दीर्घ blkoff;
	पूर्णांक i, nr_ra_blocks = NILFS_MDT_MAX_RA_BLOCKS;
	पूर्णांक err;

	err = nilfs_mdt_submit_block(inode, block, REQ_OP_READ, 0, &first_bh);
	अगर (err == -EEXIST) /* पूर्णांकernal code */
		जाओ out;

	अगर (unlikely(err))
		जाओ failed;

	अगर (पढ़ोahead) अणु
		blkoff = block + 1;
		क्रम (i = 0; i < nr_ra_blocks; i++, blkoff++) अणु
			err = nilfs_mdt_submit_block(inode, blkoff, REQ_OP_READ,
						     REQ_RAHEAD, &bh);
			अगर (likely(!err || err == -EEXIST))
				brअन्यथा(bh);
			अन्यथा अगर (err != -EBUSY)
				अवरोध;
				/* पात पढ़ोahead अगर bmap lookup failed */
			अगर (!buffer_locked(first_bh))
				जाओ out_no_रुको;
		पूर्ण
	पूर्ण

	रुको_on_buffer(first_bh);

 out_no_रुको:
	err = -EIO;
	अगर (!buffer_uptodate(first_bh)) अणु
		nilfs_err(inode->i_sb,
			  "I/O error reading meta-data file (ino=%lu, block-offset=%lu)",
			  inode->i_ino, block);
		जाओ failed_bh;
	पूर्ण
 out:
	*out_bh = first_bh;
	वापस 0;

 failed_bh:
	brअन्यथा(first_bh);
 failed:
	वापस err;
पूर्ण

/**
 * nilfs_mdt_get_block - पढ़ो or create a buffer on meta data file.
 * @inode: inode of the meta data file
 * @blkoff: block offset
 * @create: create flag
 * @init_block: initializer used क्रम newly allocated block
 * @out_bh: output of a poपूर्णांकer to the buffer_head
 *
 * nilfs_mdt_get_block() looks up the specअगरied buffer and tries to create
 * a new buffer अगर @create is not zero.  On success, the वापसed buffer is
 * assured to be either existing or क्रमmatted using a buffer lock on success.
 * @out_bh is substituted only when zero is वापसed.
 *
 * Return Value: On success, it वापसs 0. On error, the following negative
 * error code is वापसed.
 *
 * %-ENOMEM - Insufficient memory available.
 *
 * %-EIO - I/O error
 *
 * %-ENOENT - the specअगरied block करोes not exist (hole block)
 *
 * %-EROFS - Read only fileप्रणाली (क्रम create mode)
 */
पूर्णांक nilfs_mdt_get_block(काष्ठा inode *inode, अचिन्हित दीर्घ blkoff, पूर्णांक create,
			व्योम (*init_block)(काष्ठा inode *,
					   काष्ठा buffer_head *, व्योम *),
			काष्ठा buffer_head **out_bh)
अणु
	पूर्णांक ret;

	/* Should be rewritten with merging nilfs_mdt_पढ़ो_block() */
 retry:
	ret = nilfs_mdt_पढ़ो_block(inode, blkoff, !create, out_bh);
	अगर (!create || ret != -ENOENT)
		वापस ret;

	ret = nilfs_mdt_create_block(inode, blkoff, out_bh, init_block);
	अगर (unlikely(ret == -EEXIST)) अणु
		/* create = 0; */  /* limit पढ़ो-create loop retries */
		जाओ retry;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nilfs_mdt_find_block - find and get a buffer on meta data file.
 * @inode: inode of the meta data file
 * @start: start block offset (inclusive)
 * @end: end block offset (inclusive)
 * @blkoff: block offset
 * @out_bh: place to store a poपूर्णांकer to buffer_head काष्ठा
 *
 * nilfs_mdt_find_block() looks up an existing block in range of
 * [@start, @end] and stores poपूर्णांकer to a buffer head of the block to
 * @out_bh, and block offset to @blkoff, respectively.  @out_bh and
 * @blkoff are substituted only when zero is वापसed.
 *
 * Return Value: On success, it वापसs 0. On error, the following negative
 * error code is वापसed.
 *
 * %-ENOMEM - Insufficient memory available.
 *
 * %-EIO - I/O error
 *
 * %-ENOENT - no block was found in the range
 */
पूर्णांक nilfs_mdt_find_block(काष्ठा inode *inode, अचिन्हित दीर्घ start,
			 अचिन्हित दीर्घ end, अचिन्हित दीर्घ *blkoff,
			 काष्ठा buffer_head **out_bh)
अणु
	__u64 next;
	पूर्णांक ret;

	अगर (unlikely(start > end))
		वापस -ENOENT;

	ret = nilfs_mdt_पढ़ो_block(inode, start, true, out_bh);
	अगर (!ret) अणु
		*blkoff = start;
		जाओ out;
	पूर्ण
	अगर (unlikely(ret != -ENOENT || start == अच_दीर्घ_उच्च))
		जाओ out;

	ret = nilfs_bmap_seek_key(NILFS_I(inode)->i_bmap, start + 1, &next);
	अगर (!ret) अणु
		अगर (next <= end) अणु
			ret = nilfs_mdt_पढ़ो_block(inode, next, true, out_bh);
			अगर (!ret)
				*blkoff = next;
		पूर्ण अन्यथा अणु
			ret = -ENOENT;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

/**
 * nilfs_mdt_delete_block - make a hole on the meta data file.
 * @inode: inode of the meta data file
 * @block: block offset
 *
 * Return Value: On success, zero is वापसed.
 * On error, one of the following negative error code is वापसed.
 *
 * %-ENOMEM - Insufficient memory available.
 *
 * %-EIO - I/O error
 */
पूर्णांक nilfs_mdt_delete_block(काष्ठा inode *inode, अचिन्हित दीर्घ block)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	पूर्णांक err;

	err = nilfs_bmap_delete(ii->i_bmap, block);
	अगर (!err || err == -ENOENT) अणु
		nilfs_mdt_mark_dirty(inode);
		nilfs_mdt_क्रमget_block(inode, block);
	पूर्ण
	वापस err;
पूर्ण

/**
 * nilfs_mdt_क्रमget_block - discard dirty state and try to हटाओ the page
 * @inode: inode of the meta data file
 * @block: block offset
 *
 * nilfs_mdt_क्रमget_block() clears a dirty flag of the specअगरied buffer, and
 * tries to release the page including the buffer from a page cache.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error code is वापसed.
 *
 * %-EBUSY - page has an active buffer.
 *
 * %-ENOENT - page cache has no page addressed by the offset.
 */
पूर्णांक nilfs_mdt_क्रमget_block(काष्ठा inode *inode, अचिन्हित दीर्घ block)
अणु
	pgoff_t index = (pgoff_t)block >>
		(PAGE_SHIFT - inode->i_blkbits);
	काष्ठा page *page;
	अचिन्हित दीर्घ first_block;
	पूर्णांक ret = 0;
	पूर्णांक still_dirty;

	page = find_lock_page(inode->i_mapping, index);
	अगर (!page)
		वापस -ENOENT;

	रुको_on_page_ग_लिखोback(page);

	first_block = (अचिन्हित दीर्घ)index <<
		(PAGE_SHIFT - inode->i_blkbits);
	अगर (page_has_buffers(page)) अणु
		काष्ठा buffer_head *bh;

		bh = nilfs_page_get_nth_block(page, block - first_block);
		nilfs_क्रमget_buffer(bh);
	पूर्ण
	still_dirty = PageDirty(page);
	unlock_page(page);
	put_page(page);

	अगर (still_dirty ||
	    invalidate_inode_pages2_range(inode->i_mapping, index, index) != 0)
		ret = -EBUSY;
	वापस ret;
पूर्ण

पूर्णांक nilfs_mdt_fetch_dirty(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);

	अगर (nilfs_bmap_test_and_clear_dirty(ii->i_bmap)) अणु
		set_bit(NILFS_I_सूचीTY, &ii->i_state);
		वापस 1;
	पूर्ण
	वापस test_bit(NILFS_I_सूचीTY, &ii->i_state);
पूर्ण

अटल पूर्णांक
nilfs_mdt_ग_लिखो_page(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा super_block *sb;
	पूर्णांक err = 0;

	अगर (inode && sb_rकरोnly(inode->i_sb)) अणु
		/*
		 * It means that fileप्रणाली was remounted in पढ़ो-only
		 * mode because of error or metadata corruption. But we
		 * have dirty pages that try to be flushed in background.
		 * So, here we simply discard this dirty page.
		 */
		nilfs_clear_dirty_page(page, false);
		unlock_page(page);
		वापस -EROFS;
	पूर्ण

	redirty_page_क्रम_ग_लिखोpage(wbc, page);
	unlock_page(page);

	अगर (!inode)
		वापस 0;

	sb = inode->i_sb;

	अगर (wbc->sync_mode == WB_SYNC_ALL)
		err = nilfs_स्थिरruct_segment(sb);
	अन्यथा अगर (wbc->क्रम_reclaim)
		nilfs_flush_segment(sb, inode->i_ino);

	वापस err;
पूर्ण


अटल स्थिर काष्ठा address_space_operations def_mdt_aops = अणु
	.ग_लिखोpage		= nilfs_mdt_ग_लिखो_page,
पूर्ण;

अटल स्थिर काष्ठा inode_operations def_mdt_iops;
अटल स्थिर काष्ठा file_operations def_mdt_fops;


पूर्णांक nilfs_mdt_init(काष्ठा inode *inode, gfp_t gfp_mask, माप_प्रकार objsz)
अणु
	काष्ठा nilfs_mdt_info *mi;

	mi = kzalloc(max(माप(*mi), objsz), GFP_NOFS);
	अगर (!mi)
		वापस -ENOMEM;

	init_rwsem(&mi->mi_sem);
	inode->i_निजी = mi;

	inode->i_mode = S_IFREG;
	mapping_set_gfp_mask(inode->i_mapping, gfp_mask);

	inode->i_op = &def_mdt_iops;
	inode->i_fop = &def_mdt_fops;
	inode->i_mapping->a_ops = &def_mdt_aops;

	वापस 0;
पूर्ण

/**
 * nilfs_mdt_clear - करो cleanup क्रम the metadata file
 * @inode: inode of the metadata file
 */
व्योम nilfs_mdt_clear(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_mdt_info *mdi = NILFS_MDT(inode);

	अगर (mdi->mi_palloc_cache)
		nilfs_palloc_destroy_cache(inode);
पूर्ण

/**
 * nilfs_mdt_destroy - release resources used by the metadata file
 * @inode: inode of the metadata file
 */
व्योम nilfs_mdt_destroy(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_mdt_info *mdi = NILFS_MDT(inode);

	kमुक्त(mdi->mi_bgl); /* kमुक्त(शून्य) is safe */
	kमुक्त(mdi);
पूर्ण

व्योम nilfs_mdt_set_entry_size(काष्ठा inode *inode, अचिन्हित पूर्णांक entry_size,
			      अचिन्हित पूर्णांक header_size)
अणु
	काष्ठा nilfs_mdt_info *mi = NILFS_MDT(inode);

	mi->mi_entry_size = entry_size;
	mi->mi_entries_per_block = i_blocksize(inode) / entry_size;
	mi->mi_first_entry_offset = DIV_ROUND_UP(header_size, entry_size);
पूर्ण

/**
 * nilfs_mdt_setup_shaकरोw_map - setup shaकरोw map and bind it to metadata file
 * @inode: inode of the metadata file
 * @shaकरोw: shaकरोw mapping
 */
पूर्णांक nilfs_mdt_setup_shaकरोw_map(काष्ठा inode *inode,
			       काष्ठा nilfs_shaकरोw_map *shaकरोw)
अणु
	काष्ठा nilfs_mdt_info *mi = NILFS_MDT(inode);

	INIT_LIST_HEAD(&shaकरोw->frozen_buffers);
	address_space_init_once(&shaकरोw->frozen_data);
	nilfs_mapping_init(&shaकरोw->frozen_data, inode);
	address_space_init_once(&shaकरोw->frozen_btnodes);
	nilfs_mapping_init(&shaकरोw->frozen_btnodes, inode);
	mi->mi_shaकरोw = shaकरोw;
	वापस 0;
पूर्ण

/**
 * nilfs_mdt_save_to_shaकरोw_map - copy bmap and dirty pages to shaकरोw map
 * @inode: inode of the metadata file
 */
पूर्णांक nilfs_mdt_save_to_shaकरोw_map(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_mdt_info *mi = NILFS_MDT(inode);
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	काष्ठा nilfs_shaकरोw_map *shaकरोw = mi->mi_shaकरोw;
	पूर्णांक ret;

	ret = nilfs_copy_dirty_pages(&shaकरोw->frozen_data, inode->i_mapping);
	अगर (ret)
		जाओ out;

	ret = nilfs_copy_dirty_pages(&shaकरोw->frozen_btnodes,
				     &ii->i_btnode_cache);
	अगर (ret)
		जाओ out;

	nilfs_bmap_save(ii->i_bmap, &shaकरोw->bmap_store);
 out:
	वापस ret;
पूर्ण

पूर्णांक nilfs_mdt_मुक्तze_buffer(काष्ठा inode *inode, काष्ठा buffer_head *bh)
अणु
	काष्ठा nilfs_shaकरोw_map *shaकरोw = NILFS_MDT(inode)->mi_shaकरोw;
	काष्ठा buffer_head *bh_frozen;
	काष्ठा page *page;
	पूर्णांक blkbits = inode->i_blkbits;

	page = grab_cache_page(&shaकरोw->frozen_data, bh->b_page->index);
	अगर (!page)
		वापस -ENOMEM;

	अगर (!page_has_buffers(page))
		create_empty_buffers(page, 1 << blkbits, 0);

	bh_frozen = nilfs_page_get_nth_block(page, bh_offset(bh) >> blkbits);

	अगर (!buffer_uptodate(bh_frozen))
		nilfs_copy_buffer(bh_frozen, bh);
	अगर (list_empty(&bh_frozen->b_assoc_buffers)) अणु
		list_add_tail(&bh_frozen->b_assoc_buffers,
			      &shaकरोw->frozen_buffers);
		set_buffer_nilfs_redirected(bh);
	पूर्ण अन्यथा अणु
		brअन्यथा(bh_frozen); /* alपढ़ोy frozen */
	पूर्ण

	unlock_page(page);
	put_page(page);
	वापस 0;
पूर्ण

काष्ठा buffer_head *
nilfs_mdt_get_frozen_buffer(काष्ठा inode *inode, काष्ठा buffer_head *bh)
अणु
	काष्ठा nilfs_shaकरोw_map *shaकरोw = NILFS_MDT(inode)->mi_shaकरोw;
	काष्ठा buffer_head *bh_frozen = शून्य;
	काष्ठा page *page;
	पूर्णांक n;

	page = find_lock_page(&shaकरोw->frozen_data, bh->b_page->index);
	अगर (page) अणु
		अगर (page_has_buffers(page)) अणु
			n = bh_offset(bh) >> inode->i_blkbits;
			bh_frozen = nilfs_page_get_nth_block(page, n);
		पूर्ण
		unlock_page(page);
		put_page(page);
	पूर्ण
	वापस bh_frozen;
पूर्ण

अटल व्योम nilfs_release_frozen_buffers(काष्ठा nilfs_shaकरोw_map *shaकरोw)
अणु
	काष्ठा list_head *head = &shaकरोw->frozen_buffers;
	काष्ठा buffer_head *bh;

	जबतक (!list_empty(head)) अणु
		bh = list_first_entry(head, काष्ठा buffer_head,
				      b_assoc_buffers);
		list_del_init(&bh->b_assoc_buffers);
		brअन्यथा(bh); /* drop ref-count to make it releasable */
	पूर्ण
पूर्ण

/**
 * nilfs_mdt_restore_from_shaकरोw_map - restore dirty pages and bmap state
 * @inode: inode of the metadata file
 */
व्योम nilfs_mdt_restore_from_shaकरोw_map(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_mdt_info *mi = NILFS_MDT(inode);
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	काष्ठा nilfs_shaकरोw_map *shaकरोw = mi->mi_shaकरोw;

	करोwn_ग_लिखो(&mi->mi_sem);

	अगर (mi->mi_palloc_cache)
		nilfs_palloc_clear_cache(inode);

	nilfs_clear_dirty_pages(inode->i_mapping, true);
	nilfs_copy_back_pages(inode->i_mapping, &shaकरोw->frozen_data);

	nilfs_clear_dirty_pages(&ii->i_btnode_cache, true);
	nilfs_copy_back_pages(&ii->i_btnode_cache, &shaकरोw->frozen_btnodes);

	nilfs_bmap_restore(ii->i_bmap, &shaकरोw->bmap_store);

	up_ग_लिखो(&mi->mi_sem);
पूर्ण

/**
 * nilfs_mdt_clear_shaकरोw_map - truncate pages in shaकरोw map caches
 * @inode: inode of the metadata file
 */
व्योम nilfs_mdt_clear_shaकरोw_map(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_mdt_info *mi = NILFS_MDT(inode);
	काष्ठा nilfs_shaकरोw_map *shaकरोw = mi->mi_shaकरोw;

	करोwn_ग_लिखो(&mi->mi_sem);
	nilfs_release_frozen_buffers(shaकरोw);
	truncate_inode_pages(&shaकरोw->frozen_data, 0);
	truncate_inode_pages(&shaकरोw->frozen_btnodes, 0);
	up_ग_लिखो(&mi->mi_sem);
पूर्ण
