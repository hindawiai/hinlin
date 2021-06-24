<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * inode.c - NILFS inode operations.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 *
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mpage.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/uपन.स>
#समावेश <linux/fiemap.h>
#समावेश "nilfs.h"
#समावेश "btnode.h"
#समावेश "segment.h"
#समावेश "page.h"
#समावेश "mdt.h"
#समावेश "cpfile.h"
#समावेश "ifile.h"

/**
 * काष्ठा nilfs_iget_args - arguments used during comparison between inodes
 * @ino: inode number
 * @cno: checkpoपूर्णांक number
 * @root: poपूर्णांकer on NILFS root object (mounted checkpoपूर्णांक)
 * @क्रम_gc: inode क्रम GC flag
 */
काष्ठा nilfs_iget_args अणु
	u64 ino;
	__u64 cno;
	काष्ठा nilfs_root *root;
	पूर्णांक क्रम_gc;
पूर्ण;

अटल पूर्णांक nilfs_iget_test(काष्ठा inode *inode, व्योम *opaque);

व्योम nilfs_inode_add_blocks(काष्ठा inode *inode, पूर्णांक n)
अणु
	काष्ठा nilfs_root *root = NILFS_I(inode)->i_root;

	inode_add_bytes(inode, i_blocksize(inode) * n);
	अगर (root)
		atomic64_add(n, &root->blocks_count);
पूर्ण

व्योम nilfs_inode_sub_blocks(काष्ठा inode *inode, पूर्णांक n)
अणु
	काष्ठा nilfs_root *root = NILFS_I(inode)->i_root;

	inode_sub_bytes(inode, i_blocksize(inode) * n);
	अगर (root)
		atomic64_sub(n, &root->blocks_count);
पूर्ण

/**
 * nilfs_get_block() - get a file block on the fileप्रणाली (callback function)
 * @inode - inode काष्ठा of the target file
 * @blkoff - file block number
 * @bh_result - buffer head to be mapped on
 * @create - indicate whether allocating the block or not when it has not
 *      been allocated yet.
 *
 * This function करोes not issue actual पढ़ो request of the specअगरied data
 * block. It is करोne by VFS.
 */
पूर्णांक nilfs_get_block(काष्ठा inode *inode, sector_t blkoff,
		    काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	__u64 blknum = 0;
	पूर्णांक err = 0, ret;
	अचिन्हित पूर्णांक maxblocks = bh_result->b_size >> inode->i_blkbits;

	करोwn_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	ret = nilfs_bmap_lookup_contig(ii->i_bmap, blkoff, &blknum, maxblocks);
	up_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	अगर (ret >= 0) अणु	/* found */
		map_bh(bh_result, inode->i_sb, blknum);
		अगर (ret > 0)
			bh_result->b_size = (ret << inode->i_blkbits);
		जाओ out;
	पूर्ण
	/* data block was not found */
	अगर (ret == -ENOENT && create) अणु
		काष्ठा nilfs_transaction_info ti;

		bh_result->b_blocknr = 0;
		err = nilfs_transaction_begin(inode->i_sb, &ti, 1);
		अगर (unlikely(err))
			जाओ out;
		err = nilfs_bmap_insert(ii->i_bmap, blkoff,
					(अचिन्हित दीर्घ)bh_result);
		अगर (unlikely(err != 0)) अणु
			अगर (err == -EEXIST) अणु
				/*
				 * The get_block() function could be called
				 * from multiple callers क्रम an inode.
				 * However, the page having this block must
				 * be locked in this हाल.
				 */
				nilfs_warn(inode->i_sb,
					   "%s (ino=%lu): a race condition while inserting a data block at offset=%llu",
					   __func__, inode->i_ino,
					   (अचिन्हित दीर्घ दीर्घ)blkoff);
				err = 0;
			पूर्ण
			nilfs_transaction_पात(inode->i_sb);
			जाओ out;
		पूर्ण
		nilfs_mark_inode_dirty_sync(inode);
		nilfs_transaction_commit(inode->i_sb); /* never fails */
		/* Error handling should be detailed */
		set_buffer_new(bh_result);
		set_buffer_delay(bh_result);
		map_bh(bh_result, inode->i_sb, 0);
		/* Disk block number must be changed to proper value */

	पूर्ण अन्यथा अगर (ret == -ENOENT) अणु
		/*
		 * not found is not error (e.g. hole); must वापस without
		 * the mapped state flag.
		 */
		;
	पूर्ण अन्यथा अणु
		err = ret;
	पूर्ण

 out:
	वापस err;
पूर्ण

/**
 * nilfs_पढ़ोpage() - implement पढ़ोpage() method of nilfs_aops अणुपूर्ण
 * address_space_operations.
 * @file - file काष्ठा of the file to be पढ़ो
 * @page - the page to be पढ़ो
 */
अटल पूर्णांक nilfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, nilfs_get_block);
पूर्ण

अटल व्योम nilfs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, nilfs_get_block);
पूर्ण

अटल पूर्णांक nilfs_ग_लिखोpages(काष्ठा address_space *mapping,
			    काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = mapping->host;
	पूर्णांक err = 0;

	अगर (sb_rकरोnly(inode->i_sb)) अणु
		nilfs_clear_dirty_pages(mapping, false);
		वापस -EROFS;
	पूर्ण

	अगर (wbc->sync_mode == WB_SYNC_ALL)
		err = nilfs_स्थिरruct_dsync_segment(inode->i_sb, inode,
						    wbc->range_start,
						    wbc->range_end);
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक err;

	अगर (sb_rकरोnly(inode->i_sb)) अणु
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

	अगर (wbc->sync_mode == WB_SYNC_ALL) अणु
		err = nilfs_स्थिरruct_segment(inode->i_sb);
		अगर (unlikely(err))
			वापस err;
	पूर्ण अन्यथा अगर (wbc->क्रम_reclaim)
		nilfs_flush_segment(inode->i_sb, inode->i_ino);

	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_set_page_dirty(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक ret = __set_page_dirty_nobuffers(page);

	अगर (page_has_buffers(page)) अणु
		अचिन्हित पूर्णांक nr_dirty = 0;
		काष्ठा buffer_head *bh, *head;

		/*
		 * This page is locked by callers, and no other thपढ़ो
		 * concurrently marks its buffers dirty since they are
		 * only dirtied through routines in fs/buffer.c in
		 * which call sites of mark_buffer_dirty are रक्षित
		 * by page lock.
		 */
		bh = head = page_buffers(page);
		करो अणु
			/* Do not mark hole blocks dirty */
			अगर (buffer_dirty(bh) || !buffer_mapped(bh))
				जारी;

			set_buffer_dirty(bh);
			nr_dirty++;
		पूर्ण जबतक (bh = bh->b_this_page, bh != head);

		अगर (nr_dirty)
			nilfs_set_file_dirty(inode, nr_dirty);
	पूर्ण अन्यथा अगर (ret) अणु
		अचिन्हित पूर्णांक nr_dirty = 1 << (PAGE_SHIFT - inode->i_blkbits);

		nilfs_set_file_dirty(inode, nr_dirty);
	पूर्ण
	वापस ret;
पूर्ण

व्योम nilfs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		nilfs_truncate(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक nilfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			     loff_t pos, अचिन्हित len, अचिन्हित flags,
			     काष्ठा page **pagep, व्योम **fsdata)

अणु
	काष्ठा inode *inode = mapping->host;
	पूर्णांक err = nilfs_transaction_begin(inode->i_sb, शून्य, 1);

	अगर (unlikely(err))
		वापस err;

	err = block_ग_लिखो_begin(mapping, pos, len, flags, pagep,
				nilfs_get_block);
	अगर (unlikely(err)) अणु
		nilfs_ग_लिखो_failed(mapping, pos + len);
		nilfs_transaction_पात(inode->i_sb);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			   loff_t pos, अचिन्हित len, अचिन्हित copied,
			   काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	अचिन्हित पूर्णांक start = pos & (PAGE_SIZE - 1);
	अचिन्हित पूर्णांक nr_dirty;
	पूर्णांक err;

	nr_dirty = nilfs_page_count_clean_buffers(page, start,
						  start + copied);
	copied = generic_ग_लिखो_end(file, mapping, pos, len, copied, page,
				   fsdata);
	nilfs_set_file_dirty(inode, nr_dirty);
	err = nilfs_transaction_commit(inode->i_sb);
	वापस err ? : copied;
पूर्ण

अटल sमाप_प्रकार
nilfs_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (iov_iter_rw(iter) == WRITE)
		वापस 0;

	/* Needs synchronization with the cleaner */
	वापस blockdev_direct_IO(iocb, inode, iter, nilfs_get_block);
पूर्ण

स्थिर काष्ठा address_space_operations nilfs_aops = अणु
	.ग_लिखोpage		= nilfs_ग_लिखोpage,
	.पढ़ोpage		= nilfs_पढ़ोpage,
	.ग_लिखोpages		= nilfs_ग_लिखोpages,
	.set_page_dirty		= nilfs_set_page_dirty,
	.पढ़ोahead		= nilfs_पढ़ोahead,
	.ग_लिखो_begin		= nilfs_ग_लिखो_begin,
	.ग_लिखो_end		= nilfs_ग_लिखो_end,
	/* .releasepage		= nilfs_releasepage, */
	.invalidatepage		= block_invalidatepage,
	.direct_IO		= nilfs_direct_IO,
	.is_partially_uptodate  = block_is_partially_uptodate,
पूर्ण;

अटल पूर्णांक nilfs_insert_inode_locked(काष्ठा inode *inode,
				     काष्ठा nilfs_root *root,
				     अचिन्हित दीर्घ ino)
अणु
	काष्ठा nilfs_iget_args args = अणु
		.ino = ino, .root = root, .cno = 0, .क्रम_gc = 0
	पूर्ण;

	वापस insert_inode_locked4(inode, ino, nilfs_iget_test, &args);
पूर्ण

काष्ठा inode *nilfs_new_inode(काष्ठा inode *dir, umode_t mode)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा inode *inode;
	काष्ठा nilfs_inode_info *ii;
	काष्ठा nilfs_root *root;
	पूर्णांक err = -ENOMEM;
	ino_t ino;

	inode = new_inode(sb);
	अगर (unlikely(!inode))
		जाओ failed;

	mapping_set_gfp_mask(inode->i_mapping,
			   mapping_gfp_स्थिरraपूर्णांक(inode->i_mapping, ~__GFP_FS));

	root = NILFS_I(dir)->i_root;
	ii = NILFS_I(inode);
	ii->i_state = BIT(NILFS_I_NEW);
	ii->i_root = root;

	err = nilfs_अगरile_create_inode(root->अगरile, &ino, &ii->i_bh);
	अगर (unlikely(err))
		जाओ failed_अगरile_create_inode;
	/* reference count of i_bh inherits from nilfs_mdt_पढ़ो_block() */

	atomic64_inc(&root->inodes_count);
	inode_init_owner(&init_user_ns, inode, dir, mode);
	inode->i_ino = ino;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);

	अगर (S_ISREG(mode) || S_ISसूची(mode) || S_ISLNK(mode)) अणु
		err = nilfs_bmap_पढ़ो(ii->i_bmap, शून्य);
		अगर (err < 0)
			जाओ failed_after_creation;

		set_bit(NILFS_I_BMAP, &ii->i_state);
		/* No lock is needed; iget() ensures it. */
	पूर्ण

	ii->i_flags = nilfs_mask_flags(
		mode, NILFS_I(dir)->i_flags & NILFS_FL_INHERITED);

	/* ii->i_file_acl = 0; */
	/* ii->i_dir_acl = 0; */
	ii->i_dir_start_lookup = 0;
	nilfs_set_inode_flags(inode);
	spin_lock(&nilfs->ns_next_gen_lock);
	inode->i_generation = nilfs->ns_next_generation++;
	spin_unlock(&nilfs->ns_next_gen_lock);
	अगर (nilfs_insert_inode_locked(inode, root, ino) < 0) अणु
		err = -EIO;
		जाओ failed_after_creation;
	पूर्ण

	err = nilfs_init_acl(inode, dir);
	अगर (unlikely(err))
		/*
		 * Never occur.  When supporting nilfs_init_acl(),
		 * proper cancellation of above jobs should be considered.
		 */
		जाओ failed_after_creation;

	वापस inode;

 failed_after_creation:
	clear_nlink(inode);
	अगर (inode->i_state & I_NEW)
		unlock_new_inode(inode);
	iput(inode);  /*
		       * raw_inode will be deleted through
		       * nilfs_evict_inode().
		       */
	जाओ failed;

 failed_अगरile_create_inode:
	make_bad_inode(inode);
	iput(inode);
 failed:
	वापस ERR_PTR(err);
पूर्ण

व्योम nilfs_set_inode_flags(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक flags = NILFS_I(inode)->i_flags;
	अचिन्हित पूर्णांक new_fl = 0;

	अगर (flags & FS_SYNC_FL)
		new_fl |= S_SYNC;
	अगर (flags & FS_APPEND_FL)
		new_fl |= S_APPEND;
	अगर (flags & FS_IMMUTABLE_FL)
		new_fl |= S_IMMUTABLE;
	अगर (flags & FS_NOATIME_FL)
		new_fl |= S_NOATIME;
	अगर (flags & FS_सूचीSYNC_FL)
		new_fl |= S_सूचीSYNC;
	inode_set_flags(inode, new_fl, S_SYNC | S_APPEND | S_IMMUTABLE |
			S_NOATIME | S_सूचीSYNC);
पूर्ण

पूर्णांक nilfs_पढ़ो_inode_common(काष्ठा inode *inode,
			    काष्ठा nilfs_inode *raw_inode)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	पूर्णांक err;

	inode->i_mode = le16_to_cpu(raw_inode->i_mode);
	i_uid_ग_लिखो(inode, le32_to_cpu(raw_inode->i_uid));
	i_gid_ग_लिखो(inode, le32_to_cpu(raw_inode->i_gid));
	set_nlink(inode, le16_to_cpu(raw_inode->i_links_count));
	inode->i_size = le64_to_cpu(raw_inode->i_size);
	inode->i_aसमय.tv_sec = le64_to_cpu(raw_inode->i_mसमय);
	inode->i_स_समय.tv_sec = le64_to_cpu(raw_inode->i_स_समय);
	inode->i_mसमय.tv_sec = le64_to_cpu(raw_inode->i_mसमय);
	inode->i_aसमय.tv_nsec = le32_to_cpu(raw_inode->i_mसमय_nsec);
	inode->i_स_समय.tv_nsec = le32_to_cpu(raw_inode->i_स_समय_nsec);
	inode->i_mसमय.tv_nsec = le32_to_cpu(raw_inode->i_mसमय_nsec);
	अगर (inode->i_nlink == 0)
		वापस -ESTALE; /* this inode is deleted */

	inode->i_blocks = le64_to_cpu(raw_inode->i_blocks);
	ii->i_flags = le32_to_cpu(raw_inode->i_flags);
#अगर 0
	ii->i_file_acl = le32_to_cpu(raw_inode->i_file_acl);
	ii->i_dir_acl = S_ISREG(inode->i_mode) ?
		0 : le32_to_cpu(raw_inode->i_dir_acl);
#पूर्ण_अगर
	ii->i_dir_start_lookup = 0;
	inode->i_generation = le32_to_cpu(raw_inode->i_generation);

	अगर (S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
	    S_ISLNK(inode->i_mode)) अणु
		err = nilfs_bmap_पढ़ो(ii->i_bmap, raw_inode);
		अगर (err < 0)
			वापस err;
		set_bit(NILFS_I_BMAP, &ii->i_state);
		/* No lock is needed; iget() ensures it. */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __nilfs_पढ़ो_inode(काष्ठा super_block *sb,
			      काष्ठा nilfs_root *root, अचिन्हित दीर्घ ino,
			      काष्ठा inode *inode)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_inode *raw_inode;
	पूर्णांक err;

	करोwn_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	err = nilfs_अगरile_get_inode_block(root->अगरile, ino, &bh);
	अगर (unlikely(err))
		जाओ bad_inode;

	raw_inode = nilfs_अगरile_map_inode(root->अगरile, ino, bh);

	err = nilfs_पढ़ो_inode_common(inode, raw_inode);
	अगर (err)
		जाओ failed_unmap;

	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = &nilfs_file_inode_operations;
		inode->i_fop = &nilfs_file_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &nilfs_dir_inode_operations;
		inode->i_fop = &nilfs_dir_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = &nilfs_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &nilfs_aops;
	पूर्ण अन्यथा अणु
		inode->i_op = &nilfs_special_inode_operations;
		init_special_inode(
			inode, inode->i_mode,
			huge_decode_dev(le64_to_cpu(raw_inode->i_device_code)));
	पूर्ण
	nilfs_अगरile_unmap_inode(root->अगरile, ino, bh);
	brअन्यथा(bh);
	up_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	nilfs_set_inode_flags(inode);
	mapping_set_gfp_mask(inode->i_mapping,
			   mapping_gfp_स्थिरraपूर्णांक(inode->i_mapping, ~__GFP_FS));
	वापस 0;

 failed_unmap:
	nilfs_अगरile_unmap_inode(root->अगरile, ino, bh);
	brअन्यथा(bh);

 bad_inode:
	up_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_iget_test(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा nilfs_iget_args *args = opaque;
	काष्ठा nilfs_inode_info *ii;

	अगर (args->ino != inode->i_ino || args->root != NILFS_I(inode)->i_root)
		वापस 0;

	ii = NILFS_I(inode);
	अगर (!test_bit(NILFS_I_GCINODE, &ii->i_state))
		वापस !args->क्रम_gc;

	वापस args->क्रम_gc && args->cno == ii->i_cno;
पूर्ण

अटल पूर्णांक nilfs_iget_set(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा nilfs_iget_args *args = opaque;

	inode->i_ino = args->ino;
	अगर (args->क्रम_gc) अणु
		NILFS_I(inode)->i_state = BIT(NILFS_I_GCINODE);
		NILFS_I(inode)->i_cno = args->cno;
		NILFS_I(inode)->i_root = शून्य;
	पूर्ण अन्यथा अणु
		अगर (args->root && args->ino == NILFS_ROOT_INO)
			nilfs_get_root(args->root);
		NILFS_I(inode)->i_root = args->root;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा inode *nilfs_ilookup(काष्ठा super_block *sb, काष्ठा nilfs_root *root,
			    अचिन्हित दीर्घ ino)
अणु
	काष्ठा nilfs_iget_args args = अणु
		.ino = ino, .root = root, .cno = 0, .क्रम_gc = 0
	पूर्ण;

	वापस ilookup5(sb, ino, nilfs_iget_test, &args);
पूर्ण

काष्ठा inode *nilfs_iget_locked(काष्ठा super_block *sb, काष्ठा nilfs_root *root,
				अचिन्हित दीर्घ ino)
अणु
	काष्ठा nilfs_iget_args args = अणु
		.ino = ino, .root = root, .cno = 0, .क्रम_gc = 0
	पूर्ण;

	वापस iget5_locked(sb, ino, nilfs_iget_test, nilfs_iget_set, &args);
पूर्ण

काष्ठा inode *nilfs_iget(काष्ठा super_block *sb, काष्ठा nilfs_root *root,
			 अचिन्हित दीर्घ ino)
अणु
	काष्ठा inode *inode;
	पूर्णांक err;

	inode = nilfs_iget_locked(sb, root, ino);
	अगर (unlikely(!inode))
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	err = __nilfs_पढ़ो_inode(sb, root, ino, inode);
	अगर (unlikely(err)) अणु
		iget_failed(inode);
		वापस ERR_PTR(err);
	पूर्ण
	unlock_new_inode(inode);
	वापस inode;
पूर्ण

काष्ठा inode *nilfs_iget_क्रम_gc(काष्ठा super_block *sb, अचिन्हित दीर्घ ino,
				__u64 cno)
अणु
	काष्ठा nilfs_iget_args args = अणु
		.ino = ino, .root = शून्य, .cno = cno, .क्रम_gc = 1
	पूर्ण;
	काष्ठा inode *inode;
	पूर्णांक err;

	inode = iget5_locked(sb, ino, nilfs_iget_test, nilfs_iget_set, &args);
	अगर (unlikely(!inode))
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	err = nilfs_init_gcinode(inode);
	अगर (unlikely(err)) अणु
		iget_failed(inode);
		वापस ERR_PTR(err);
	पूर्ण
	unlock_new_inode(inode);
	वापस inode;
पूर्ण

व्योम nilfs_ग_लिखो_inode_common(काष्ठा inode *inode,
			      काष्ठा nilfs_inode *raw_inode, पूर्णांक has_bmap)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);

	raw_inode->i_mode = cpu_to_le16(inode->i_mode);
	raw_inode->i_uid = cpu_to_le32(i_uid_पढ़ो(inode));
	raw_inode->i_gid = cpu_to_le32(i_gid_पढ़ो(inode));
	raw_inode->i_links_count = cpu_to_le16(inode->i_nlink);
	raw_inode->i_size = cpu_to_le64(inode->i_size);
	raw_inode->i_स_समय = cpu_to_le64(inode->i_स_समय.tv_sec);
	raw_inode->i_mसमय = cpu_to_le64(inode->i_mसमय.tv_sec);
	raw_inode->i_स_समय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);
	raw_inode->i_mसमय_nsec = cpu_to_le32(inode->i_mसमय.tv_nsec);
	raw_inode->i_blocks = cpu_to_le64(inode->i_blocks);

	raw_inode->i_flags = cpu_to_le32(ii->i_flags);
	raw_inode->i_generation = cpu_to_le32(inode->i_generation);

	अगर (NILFS_ROOT_METADATA_खाता(inode->i_ino)) अणु
		काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;

		/* zero-fill unused portion in the हाल of super root block */
		raw_inode->i_xattr = 0;
		raw_inode->i_pad = 0;
		स_रखो((व्योम *)raw_inode + माप(*raw_inode), 0,
		       nilfs->ns_inode_size - माप(*raw_inode));
	पूर्ण

	अगर (has_bmap)
		nilfs_bmap_ग_लिखो(ii->i_bmap, raw_inode);
	अन्यथा अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		raw_inode->i_device_code =
			cpu_to_le64(huge_encode_dev(inode->i_rdev));
	/*
	 * When extending inode, nilfs->ns_inode_size should be checked
	 * क्रम substitutions of appended fields.
	 */
पूर्ण

व्योम nilfs_update_inode(काष्ठा inode *inode, काष्ठा buffer_head *ibh, पूर्णांक flags)
अणु
	ino_t ino = inode->i_ino;
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	काष्ठा inode *अगरile = ii->i_root->अगरile;
	काष्ठा nilfs_inode *raw_inode;

	raw_inode = nilfs_अगरile_map_inode(अगरile, ino, ibh);

	अगर (test_and_clear_bit(NILFS_I_NEW, &ii->i_state))
		स_रखो(raw_inode, 0, NILFS_MDT(अगरile)->mi_entry_size);
	अगर (flags & I_सूचीTY_DATASYNC)
		set_bit(NILFS_I_INODE_SYNC, &ii->i_state);

	nilfs_ग_लिखो_inode_common(inode, raw_inode, 0);
		/*
		 * XXX: call with has_bmap = 0 is a workaround to aव्योम
		 * deadlock of bmap.  This delays update of i_bmap to just
		 * beक्रमe writing.
		 */

	nilfs_अगरile_unmap_inode(अगरile, ino, ibh);
पूर्ण

#घोषणा NILFS_MAX_TRUNCATE_BLOCKS	16384  /* 64MB क्रम 4KB block */

अटल व्योम nilfs_truncate_bmap(काष्ठा nilfs_inode_info *ii,
				अचिन्हित दीर्घ from)
अणु
	__u64 b;
	पूर्णांक ret;

	अगर (!test_bit(NILFS_I_BMAP, &ii->i_state))
		वापस;
repeat:
	ret = nilfs_bmap_last_key(ii->i_bmap, &b);
	अगर (ret == -ENOENT)
		वापस;
	अन्यथा अगर (ret < 0)
		जाओ failed;

	अगर (b < from)
		वापस;

	b -= min_t(__u64, NILFS_MAX_TRUNCATE_BLOCKS, b - from);
	ret = nilfs_bmap_truncate(ii->i_bmap, b);
	nilfs_relax_pressure_in_lock(ii->vfs_inode.i_sb);
	अगर (!ret || (ret == -ENOMEM &&
		     nilfs_bmap_truncate(ii->i_bmap, b) == 0))
		जाओ repeat;

failed:
	nilfs_warn(ii->vfs_inode.i_sb, "error %d truncating bmap (ino=%lu)",
		   ret, ii->vfs_inode.i_ino);
पूर्ण

व्योम nilfs_truncate(काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ blkoff;
	अचिन्हित पूर्णांक blocksize;
	काष्ठा nilfs_transaction_info ti;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);

	अगर (!test_bit(NILFS_I_BMAP, &ii->i_state))
		वापस;
	अगर (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		वापस;

	blocksize = sb->s_blocksize;
	blkoff = (inode->i_size + blocksize - 1) >> sb->s_blocksize_bits;
	nilfs_transaction_begin(sb, &ti, 0); /* never fails */

	block_truncate_page(inode->i_mapping, inode->i_size, nilfs_get_block);

	nilfs_truncate_bmap(ii, blkoff);

	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	अगर (IS_SYNC(inode))
		nilfs_set_transaction_flag(NILFS_TI_SYNC);

	nilfs_mark_inode_dirty(inode);
	nilfs_set_file_dirty(inode, 0);
	nilfs_transaction_commit(sb);
	/*
	 * May स्थिरruct a logical segment and may fail in sync mode.
	 * But truncate has no वापस value.
	 */
पूर्ण

अटल व्योम nilfs_clear_inode(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);

	/*
	 * Free resources allocated in nilfs_पढ़ो_inode(), here.
	 */
	BUG_ON(!list_empty(&ii->i_dirty));
	brअन्यथा(ii->i_bh);
	ii->i_bh = शून्य;

	अगर (nilfs_is_metadata_file_inode(inode))
		nilfs_mdt_clear(inode);

	अगर (test_bit(NILFS_I_BMAP, &ii->i_state))
		nilfs_bmap_clear(ii->i_bmap);

	nilfs_btnode_cache_clear(&ii->i_btnode_cache);

	अगर (ii->i_root && inode->i_ino == NILFS_ROOT_INO)
		nilfs_put_root(ii->i_root);
पूर्ण

व्योम nilfs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_transaction_info ti;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	पूर्णांक ret;

	अगर (inode->i_nlink || !ii->i_root || unlikely(is_bad_inode(inode))) अणु
		truncate_inode_pages_final(&inode->i_data);
		clear_inode(inode);
		nilfs_clear_inode(inode);
		वापस;
	पूर्ण
	nilfs_transaction_begin(sb, &ti, 0); /* never fails */

	truncate_inode_pages_final(&inode->i_data);

	/* TODO: some of the following operations may fail.  */
	nilfs_truncate_bmap(ii, 0);
	nilfs_mark_inode_dirty(inode);
	clear_inode(inode);

	ret = nilfs_अगरile_delete_inode(ii->i_root->अगरile, inode->i_ino);
	अगर (!ret)
		atomic64_dec(&ii->i_root->inodes_count);

	nilfs_clear_inode(inode);

	अगर (IS_SYNC(inode))
		nilfs_set_transaction_flag(NILFS_TI_SYNC);
	nilfs_transaction_commit(sb);
	/*
	 * May स्थिरruct a logical segment and may fail in sync mode.
	 * But delete_inode has no वापस value.
	 */
पूर्ण

पूर्णांक nilfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		  काष्ठा iattr *iattr)
अणु
	काष्ठा nilfs_transaction_info ti;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक err;

	err = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (err)
		वापस err;

	err = nilfs_transaction_begin(sb, &ti, 0);
	अगर (unlikely(err))
		वापस err;

	अगर ((iattr->ia_valid & ATTR_SIZE) &&
	    iattr->ia_size != i_size_पढ़ो(inode)) अणु
		inode_dio_रुको(inode);
		truncate_setsize(inode, iattr->ia_size);
		nilfs_truncate(inode);
	पूर्ण

	setattr_copy(&init_user_ns, inode, iattr);
	mark_inode_dirty(inode);

	अगर (iattr->ia_valid & ATTR_MODE) अणु
		err = nilfs_acl_chmod(inode);
		अगर (unlikely(err))
			जाओ out_err;
	पूर्ण

	वापस nilfs_transaction_commit(sb);

out_err:
	nilfs_transaction_पात(sb);
	वापस err;
पूर्ण

पूर्णांक nilfs_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		     पूर्णांक mask)
अणु
	काष्ठा nilfs_root *root = NILFS_I(inode)->i_root;

	अगर ((mask & MAY_WRITE) && root &&
	    root->cno != NILFS_CPTREE_CURRENT_CNO)
		वापस -EROFS; /* snapshot is not writable */

	वापस generic_permission(&init_user_ns, inode, mask);
पूर्ण

पूर्णांक nilfs_load_inode_block(काष्ठा inode *inode, काष्ठा buffer_head **pbh)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	पूर्णांक err;

	spin_lock(&nilfs->ns_inode_lock);
	अगर (ii->i_bh == शून्य) अणु
		spin_unlock(&nilfs->ns_inode_lock);
		err = nilfs_अगरile_get_inode_block(ii->i_root->अगरile,
						  inode->i_ino, pbh);
		अगर (unlikely(err))
			वापस err;
		spin_lock(&nilfs->ns_inode_lock);
		अगर (ii->i_bh == शून्य)
			ii->i_bh = *pbh;
		अन्यथा अणु
			brअन्यथा(*pbh);
			*pbh = ii->i_bh;
		पूर्ण
	पूर्ण अन्यथा
		*pbh = ii->i_bh;

	get_bh(*pbh);
	spin_unlock(&nilfs->ns_inode_lock);
	वापस 0;
पूर्ण

पूर्णांक nilfs_inode_dirty(काष्ठा inode *inode)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	पूर्णांक ret = 0;

	अगर (!list_empty(&ii->i_dirty)) अणु
		spin_lock(&nilfs->ns_inode_lock);
		ret = test_bit(NILFS_I_सूचीTY, &ii->i_state) ||
			test_bit(NILFS_I_BUSY, &ii->i_state);
		spin_unlock(&nilfs->ns_inode_lock);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक nilfs_set_file_dirty(काष्ठा inode *inode, अचिन्हित पूर्णांक nr_dirty)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;

	atomic_add(nr_dirty, &nilfs->ns_ndirtyblks);

	अगर (test_and_set_bit(NILFS_I_सूचीTY, &ii->i_state))
		वापस 0;

	spin_lock(&nilfs->ns_inode_lock);
	अगर (!test_bit(NILFS_I_QUEUED, &ii->i_state) &&
	    !test_bit(NILFS_I_BUSY, &ii->i_state)) अणु
		/*
		 * Because this routine may race with nilfs_dispose_list(),
		 * we have to check NILFS_I_QUEUED here, too.
		 */
		अगर (list_empty(&ii->i_dirty) && igrab(inode) == शून्य) अणु
			/*
			 * This will happen when somebody is मुक्तing
			 * this inode.
			 */
			nilfs_warn(inode->i_sb,
				   "cannot set file dirty (ino=%lu): the file is being freed",
				   inode->i_ino);
			spin_unlock(&nilfs->ns_inode_lock);
			वापस -EINVAL; /*
					 * NILFS_I_सूचीTY may reमुख्य क्रम
					 * मुक्तing inode.
					 */
		पूर्ण
		list_move_tail(&ii->i_dirty, &nilfs->ns_dirty_files);
		set_bit(NILFS_I_QUEUED, &ii->i_state);
	पूर्ण
	spin_unlock(&nilfs->ns_inode_lock);
	वापस 0;
पूर्ण

पूर्णांक __nilfs_mark_inode_dirty(काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा buffer_head *ibh;
	पूर्णांक err;

	err = nilfs_load_inode_block(inode, &ibh);
	अगर (unlikely(err)) अणु
		nilfs_warn(inode->i_sb,
			   "cannot mark inode dirty (ino=%lu): error %d loading inode block",
			   inode->i_ino, err);
		वापस err;
	पूर्ण
	nilfs_update_inode(inode, ibh, flags);
	mark_buffer_dirty(ibh);
	nilfs_mdt_mark_dirty(NILFS_I(inode)->i_root->अगरile);
	brअन्यथा(ibh);
	वापस 0;
पूर्ण

/**
 * nilfs_dirty_inode - reflect changes on given inode to an inode block.
 * @inode: inode of the file to be रेजिस्टरed.
 *
 * nilfs_dirty_inode() loads a inode block containing the specअगरied
 * @inode and copies data from a nilfs_inode to a corresponding inode
 * entry in the inode block. This operation is excluded from the segment
 * स्थिरruction. This function can be called both as a single operation
 * and as a part of inभागisible file operations.
 */
व्योम nilfs_dirty_inode(काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा nilfs_transaction_info ti;
	काष्ठा nilfs_mdt_info *mdi = NILFS_MDT(inode);

	अगर (is_bad_inode(inode)) अणु
		nilfs_warn(inode->i_sb,
			   "tried to mark bad_inode dirty. ignored.");
		dump_stack();
		वापस;
	पूर्ण
	अगर (mdi) अणु
		nilfs_mdt_mark_dirty(inode);
		वापस;
	पूर्ण
	nilfs_transaction_begin(inode->i_sb, &ti, 0);
	__nilfs_mark_inode_dirty(inode, flags);
	nilfs_transaction_commit(inode->i_sb); /* never fails */
पूर्ण

पूर्णांक nilfs_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		 __u64 start, __u64 len)
अणु
	काष्ठा the_nilfs *nilfs = inode->i_sb->s_fs_info;
	__u64 logical = 0, phys = 0, size = 0;
	__u32 flags = 0;
	loff_t isize;
	sector_t blkoff, end_blkoff;
	sector_t delalloc_blkoff;
	अचिन्हित दीर्घ delalloc_blklen;
	अचिन्हित पूर्णांक blkbits = inode->i_blkbits;
	पूर्णांक ret, n;

	ret = fiemap_prep(inode, fieinfo, start, &len, 0);
	अगर (ret)
		वापस ret;

	inode_lock(inode);

	isize = i_size_पढ़ो(inode);

	blkoff = start >> blkbits;
	end_blkoff = (start + len - 1) >> blkbits;

	delalloc_blklen = nilfs_find_uncommitted_extent(inode, blkoff,
							&delalloc_blkoff);

	करो अणु
		__u64 blkphy;
		अचिन्हित पूर्णांक maxblocks;

		अगर (delalloc_blklen && blkoff == delalloc_blkoff) अणु
			अगर (size) अणु
				/* End of the current extent */
				ret = fiemap_fill_next_extent(
					fieinfo, logical, phys, size, flags);
				अगर (ret)
					अवरोध;
			पूर्ण
			अगर (blkoff > end_blkoff)
				अवरोध;

			flags = FIEMAP_EXTENT_MERGED | FIEMAP_EXTENT_DELALLOC;
			logical = blkoff << blkbits;
			phys = 0;
			size = delalloc_blklen << blkbits;

			blkoff = delalloc_blkoff + delalloc_blklen;
			delalloc_blklen = nilfs_find_uncommitted_extent(
				inode, blkoff, &delalloc_blkoff);
			जारी;
		पूर्ण

		/*
		 * Limit the number of blocks that we look up so as
		 * not to get पूर्णांकo the next delayed allocation extent.
		 */
		maxblocks = पूर्णांक_उच्च;
		अगर (delalloc_blklen)
			maxblocks = min_t(sector_t, delalloc_blkoff - blkoff,
					  maxblocks);
		blkphy = 0;

		करोwn_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
		n = nilfs_bmap_lookup_contig(
			NILFS_I(inode)->i_bmap, blkoff, &blkphy, maxblocks);
		up_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);

		अगर (n < 0) अणु
			पूर्णांक past_eof;

			अगर (unlikely(n != -ENOENT))
				अवरोध; /* error */

			/* HOLE */
			blkoff++;
			past_eof = ((blkoff << blkbits) >= isize);

			अगर (size) अणु
				/* End of the current extent */

				अगर (past_eof)
					flags |= FIEMAP_EXTENT_LAST;

				ret = fiemap_fill_next_extent(
					fieinfo, logical, phys, size, flags);
				अगर (ret)
					अवरोध;
				size = 0;
			पूर्ण
			अगर (blkoff > end_blkoff || past_eof)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (size) अणु
				अगर (phys && blkphy << blkbits == phys + size) अणु
					/* The current extent goes on */
					size += n << blkbits;
				पूर्ण अन्यथा अणु
					/* Terminate the current extent */
					ret = fiemap_fill_next_extent(
						fieinfo, logical, phys, size,
						flags);
					अगर (ret || blkoff > end_blkoff)
						अवरोध;

					/* Start another extent */
					flags = FIEMAP_EXTENT_MERGED;
					logical = blkoff << blkbits;
					phys = blkphy << blkbits;
					size = n << blkbits;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Start a new extent */
				flags = FIEMAP_EXTENT_MERGED;
				logical = blkoff << blkbits;
				phys = blkphy << blkbits;
				size = n << blkbits;
			पूर्ण
			blkoff += n;
		पूर्ण
		cond_resched();
	पूर्ण जबतक (true);

	/* If ret is 1 then we just hit the end of the extent array */
	अगर (ret == 1)
		ret = 0;

	inode_unlock(inode);
	वापस ret;
पूर्ण
