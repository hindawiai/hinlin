<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * gcinode.c - dummy inodes to buffer blocks क्रम garbage collection
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Seiji Kihara, Amagai Yoshiji, and Ryusuke Konishi.
 * Revised by Ryusuke Konishi.
 *
 */
/*
 * This file adds the cache of on-disk blocks to be moved in garbage
 * collection.  The disk blocks are held with dummy inodes (called
 * gcinodes), and this file provides lookup function of the dummy
 * inodes and their buffer पढ़ो function.
 *
 * Buffers and pages held by the dummy inodes will be released each
 * समय after they are copied to a new log.  Dirty blocks made on the
 * current generation and the blocks to be moved by GC never overlap
 * because the dirty blocks make a new generation; they rather must be
 * written inभागidually.
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/mpage.h>
#समावेश <linux/hash.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश "nilfs.h"
#समावेश "btree.h"
#समावेश "btnode.h"
#समावेश "page.h"
#समावेश "mdt.h"
#समावेश "dat.h"
#समावेश "ifile.h"

/*
 * nilfs_gccache_submit_पढ़ो_data() - add data buffer and submit पढ़ो request
 * @inode - gc inode
 * @blkoff - dummy offset treated as the key क्रम the page cache
 * @pbn - physical block number of the block
 * @vbn - भव block number of the block, 0 क्रम non-भव block
 * @out_bh - indirect poपूर्णांकer to a buffer_head काष्ठा to receive the results
 *
 * Description: nilfs_gccache_submit_पढ़ो_data() रेजिस्टरs the data buffer
 * specअगरied by @pbn to the GC pagecache with the key @blkoff.
 * This function sets @vbn (@pbn अगर @vbn is zero) in b_blocknr of the buffer.
 *
 * Return Value: On success, 0 is वापसed. On Error, one of the following
 * negative error code is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - The block specअगरied with @pbn करोes not exist.
 */
पूर्णांक nilfs_gccache_submit_पढ़ो_data(काष्ठा inode *inode, sector_t blkoff,
				   sector_t pbn, __u64 vbn,
				   काष्ठा buffer_head **out_bh)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	bh = nilfs_grab_buffer(inode, inode->i_mapping, blkoff, 0);
	अगर (unlikely(!bh))
		वापस -ENOMEM;

	अगर (buffer_uptodate(bh))
		जाओ out;

	अगर (pbn == 0) अणु
		काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;

		err = nilfs_dat_translate(nilfs->ns_dat, vbn, &pbn);
		अगर (unlikely(err)) अणु /* -EIO, -ENOMEM, -ENOENT */
			brअन्यथा(bh);
			जाओ failed;
		पूर्ण
	पूर्ण

	lock_buffer(bh);
	अगर (buffer_uptodate(bh)) अणु
		unlock_buffer(bh);
		जाओ out;
	पूर्ण

	अगर (!buffer_mapped(bh)) अणु
		bh->b_bdev = inode->i_sb->s_bdev;
		set_buffer_mapped(bh);
	पूर्ण
	bh->b_blocknr = pbn;
	bh->b_end_io = end_buffer_पढ़ो_sync;
	get_bh(bh);
	submit_bh(REQ_OP_READ, 0, bh);
	अगर (vbn)
		bh->b_blocknr = vbn;
 out:
	err = 0;
	*out_bh = bh;

 failed:
	unlock_page(bh->b_page);
	put_page(bh->b_page);
	वापस err;
पूर्ण

/*
 * nilfs_gccache_submit_पढ़ो_node() - add node buffer and submit पढ़ो request
 * @inode - gc inode
 * @pbn - physical block number क्रम the block
 * @vbn - भव block number क्रम the block
 * @out_bh - indirect poपूर्णांकer to a buffer_head काष्ठा to receive the results
 *
 * Description: nilfs_gccache_submit_पढ़ो_node() रेजिस्टरs the node buffer
 * specअगरied by @vbn to the GC pagecache.  @pbn can be supplied by the
 * caller to aव्योम translation of the disk block address.
 *
 * Return Value: On success, 0 is वापसed. On Error, one of the following
 * negative error code is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_gccache_submit_पढ़ो_node(काष्ठा inode *inode, sector_t pbn,
				   __u64 vbn, काष्ठा buffer_head **out_bh)
अणु
	पूर्णांक ret;

	ret = nilfs_btnode_submit_block(&NILFS_I(inode)->i_btnode_cache,
					vbn ? : pbn, pbn, REQ_OP_READ, 0,
					out_bh, &pbn);
	अगर (ret == -EEXIST) /* पूर्णांकernal code (cache hit) */
		ret = 0;
	वापस ret;
पूर्ण

पूर्णांक nilfs_gccache_रुको_and_mark_dirty(काष्ठा buffer_head *bh)
अणु
	रुको_on_buffer(bh);
	अगर (!buffer_uptodate(bh)) अणु
		काष्ठा inode *inode = bh->b_page->mapping->host;

		nilfs_err(inode->i_sb,
			  "I/O error reading %s block for GC (ino=%lu, vblocknr=%llu)",
			  buffer_nilfs_node(bh) ? "node" : "data",
			  inode->i_ino, (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस -EIO;
	पूर्ण
	अगर (buffer_dirty(bh))
		वापस -EEXIST;

	अगर (buffer_nilfs_node(bh) && nilfs_btree_broken_node_block(bh)) अणु
		clear_buffer_uptodate(bh);
		वापस -EIO;
	पूर्ण
	mark_buffer_dirty(bh);
	वापस 0;
पूर्ण

पूर्णांक nilfs_init_gcinode(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);

	inode->i_mode = S_IFREG;
	mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);
	inode->i_mapping->a_ops = &empty_aops;

	ii->i_flags = 0;
	nilfs_bmap_init_gc(ii->i_bmap);

	वापस 0;
पूर्ण

/**
 * nilfs_हटाओ_all_gcinodes() - हटाओ all unprocessed gc inodes
 */
व्योम nilfs_हटाओ_all_gcinodes(काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा list_head *head = &nilfs->ns_gc_inodes;
	काष्ठा nilfs_inode_info *ii;

	जबतक (!list_empty(head)) अणु
		ii = list_first_entry(head, काष्ठा nilfs_inode_info, i_dirty);
		list_del_init(&ii->i_dirty);
		truncate_inode_pages(&ii->vfs_inode.i_data, 0);
		nilfs_btnode_cache_clear(&ii->i_btnode_cache);
		iput(&ii->vfs_inode);
	पूर्ण
पूर्ण
