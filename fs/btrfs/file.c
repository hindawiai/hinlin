<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/compat.h>
#समावेश <linux/slab.h>
#समावेश <linux/btrfs.h>
#समावेश <linux/uपन.स>
#समावेश <linux/iversion.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "btrfs_inode.h"
#समावेश "print-tree.h"
#समावेश "tree-log.h"
#समावेश "locking.h"
#समावेश "volumes.h"
#समावेश "qgroup.h"
#समावेश "compression.h"
#समावेश "delalloc-space.h"
#समावेश "reflink.h"

अटल काष्ठा kmem_cache *btrfs_inode_defrag_cachep;
/*
 * when स्वतः defrag is enabled we
 * queue up these defrag काष्ठाs to remember which
 * inodes need defragging passes
 */
काष्ठा inode_defrag अणु
	काष्ठा rb_node rb_node;
	/* objectid */
	u64 ino;
	/*
	 * transid where the defrag was added, we search क्रम
	 * extents newer than this
	 */
	u64 transid;

	/* root objectid */
	u64 root;

	/* last offset we were able to defrag */
	u64 last_offset;

	/* अगर we've wrapped around back to zero once alपढ़ोy */
	पूर्णांक cycled;
पूर्ण;

अटल पूर्णांक __compare_inode_defrag(काष्ठा inode_defrag *defrag1,
				  काष्ठा inode_defrag *defrag2)
अणु
	अगर (defrag1->root > defrag2->root)
		वापस 1;
	अन्यथा अगर (defrag1->root < defrag2->root)
		वापस -1;
	अन्यथा अगर (defrag1->ino > defrag2->ino)
		वापस 1;
	अन्यथा अगर (defrag1->ino < defrag2->ino)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

/* pop a record क्रम an inode पूर्णांकo the defrag tree.  The lock
 * must be held alपढ़ोy
 *
 * If you're inserting a record क्रम an older transid than an
 * existing record, the transid alपढ़ोy in the tree is lowered
 *
 * If an existing record is found the defrag item you
 * pass in is मुक्तd
 */
अटल पूर्णांक __btrfs_add_inode_defrag(काष्ठा btrfs_inode *inode,
				    काष्ठा inode_defrag *defrag)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा inode_defrag *entry;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	पूर्णांक ret;

	p = &fs_info->defrag_inodes.rb_node;
	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा inode_defrag, rb_node);

		ret = __compare_inode_defrag(defrag, entry);
		अगर (ret < 0)
			p = &parent->rb_left;
		अन्यथा अगर (ret > 0)
			p = &parent->rb_right;
		अन्यथा अणु
			/* अगर we're reinserting an entry क्रम
			 * an old defrag run, make sure to
			 * lower the transid of our existing record
			 */
			अगर (defrag->transid < entry->transid)
				entry->transid = defrag->transid;
			अगर (defrag->last_offset > entry->last_offset)
				entry->last_offset = defrag->last_offset;
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	set_bit(BTRFS_INODE_IN_DEFRAG, &inode->runसमय_flags);
	rb_link_node(&defrag->rb_node, parent, p);
	rb_insert_color(&defrag->rb_node, &fs_info->defrag_inodes);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __need_स्वतः_defrag(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!btrfs_test_opt(fs_info, AUTO_DEFRAG))
		वापस 0;

	अगर (btrfs_fs_closing(fs_info))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * insert a defrag record क्रम this inode अगर स्वतः defrag is
 * enabled
 */
पूर्णांक btrfs_add_inode_defrag(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा inode_defrag *defrag;
	u64 transid;
	पूर्णांक ret;

	अगर (!__need_स्वतः_defrag(fs_info))
		वापस 0;

	अगर (test_bit(BTRFS_INODE_IN_DEFRAG, &inode->runसमय_flags))
		वापस 0;

	अगर (trans)
		transid = trans->transid;
	अन्यथा
		transid = inode->root->last_trans;

	defrag = kmem_cache_zalloc(btrfs_inode_defrag_cachep, GFP_NOFS);
	अगर (!defrag)
		वापस -ENOMEM;

	defrag->ino = btrfs_ino(inode);
	defrag->transid = transid;
	defrag->root = root->root_key.objectid;

	spin_lock(&fs_info->defrag_inodes_lock);
	अगर (!test_bit(BTRFS_INODE_IN_DEFRAG, &inode->runसमय_flags)) अणु
		/*
		 * If we set IN_DEFRAG flag and evict the inode from memory,
		 * and then re-पढ़ो this inode, this new inode करोesn't have
		 * IN_DEFRAG flag. At the हाल, we may find the existed defrag.
		 */
		ret = __btrfs_add_inode_defrag(inode, defrag);
		अगर (ret)
			kmem_cache_मुक्त(btrfs_inode_defrag_cachep, defrag);
	पूर्ण अन्यथा अणु
		kmem_cache_मुक्त(btrfs_inode_defrag_cachep, defrag);
	पूर्ण
	spin_unlock(&fs_info->defrag_inodes_lock);
	वापस 0;
पूर्ण

/*
 * Requeue the defrag object. If there is a defrag object that poपूर्णांकs to
 * the same inode in the tree, we will merge them together (by
 * __btrfs_add_inode_defrag()) and मुक्त the one that we want to requeue.
 */
अटल व्योम btrfs_requeue_inode_defrag(काष्ठा btrfs_inode *inode,
				       काष्ठा inode_defrag *defrag)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	पूर्णांक ret;

	अगर (!__need_स्वतः_defrag(fs_info))
		जाओ out;

	/*
	 * Here we करोn't check the IN_DEFRAG flag, because we need merge
	 * them together.
	 */
	spin_lock(&fs_info->defrag_inodes_lock);
	ret = __btrfs_add_inode_defrag(inode, defrag);
	spin_unlock(&fs_info->defrag_inodes_lock);
	अगर (ret)
		जाओ out;
	वापस;
out:
	kmem_cache_मुक्त(btrfs_inode_defrag_cachep, defrag);
पूर्ण

/*
 * pick the defragable inode that we want, अगर it करोesn't exist, we will get
 * the next one.
 */
अटल काष्ठा inode_defrag *
btrfs_pick_defrag_inode(काष्ठा btrfs_fs_info *fs_info, u64 root, u64 ino)
अणु
	काष्ठा inode_defrag *entry = शून्य;
	काष्ठा inode_defrag पंचांगp;
	काष्ठा rb_node *p;
	काष्ठा rb_node *parent = शून्य;
	पूर्णांक ret;

	पंचांगp.ino = ino;
	पंचांगp.root = root;

	spin_lock(&fs_info->defrag_inodes_lock);
	p = fs_info->defrag_inodes.rb_node;
	जबतक (p) अणु
		parent = p;
		entry = rb_entry(parent, काष्ठा inode_defrag, rb_node);

		ret = __compare_inode_defrag(&पंचांगp, entry);
		अगर (ret < 0)
			p = parent->rb_left;
		अन्यथा अगर (ret > 0)
			p = parent->rb_right;
		अन्यथा
			जाओ out;
	पूर्ण

	अगर (parent && __compare_inode_defrag(&पंचांगp, entry) > 0) अणु
		parent = rb_next(parent);
		अगर (parent)
			entry = rb_entry(parent, काष्ठा inode_defrag, rb_node);
		अन्यथा
			entry = शून्य;
	पूर्ण
out:
	अगर (entry)
		rb_erase(parent, &fs_info->defrag_inodes);
	spin_unlock(&fs_info->defrag_inodes_lock);
	वापस entry;
पूर्ण

व्योम btrfs_cleanup_defrag_inodes(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा inode_defrag *defrag;
	काष्ठा rb_node *node;

	spin_lock(&fs_info->defrag_inodes_lock);
	node = rb_first(&fs_info->defrag_inodes);
	जबतक (node) अणु
		rb_erase(node, &fs_info->defrag_inodes);
		defrag = rb_entry(node, काष्ठा inode_defrag, rb_node);
		kmem_cache_मुक्त(btrfs_inode_defrag_cachep, defrag);

		cond_resched_lock(&fs_info->defrag_inodes_lock);

		node = rb_first(&fs_info->defrag_inodes);
	पूर्ण
	spin_unlock(&fs_info->defrag_inodes_lock);
पूर्ण

#घोषणा BTRFS_DEFRAG_BATCH	1024

अटल पूर्णांक __btrfs_run_defrag_inode(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा inode_defrag *defrag)
अणु
	काष्ठा btrfs_root *inode_root;
	काष्ठा inode *inode;
	काष्ठा btrfs_ioctl_defrag_range_args range;
	पूर्णांक num_defrag;
	पूर्णांक ret;

	/* get the inode */
	inode_root = btrfs_get_fs_root(fs_info, defrag->root, true);
	अगर (IS_ERR(inode_root)) अणु
		ret = PTR_ERR(inode_root);
		जाओ cleanup;
	पूर्ण

	inode = btrfs_iget(fs_info->sb, defrag->ino, inode_root);
	btrfs_put_root(inode_root);
	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		जाओ cleanup;
	पूर्ण

	/* करो a chunk of defrag */
	clear_bit(BTRFS_INODE_IN_DEFRAG, &BTRFS_I(inode)->runसमय_flags);
	स_रखो(&range, 0, माप(range));
	range.len = (u64)-1;
	range.start = defrag->last_offset;

	sb_start_ग_लिखो(fs_info->sb);
	num_defrag = btrfs_defrag_file(inode, शून्य, &range, defrag->transid,
				       BTRFS_DEFRAG_BATCH);
	sb_end_ग_लिखो(fs_info->sb);
	/*
	 * अगर we filled the whole defrag batch, there
	 * must be more work to करो.  Queue this defrag
	 * again
	 */
	अगर (num_defrag == BTRFS_DEFRAG_BATCH) अणु
		defrag->last_offset = range.start;
		btrfs_requeue_inode_defrag(BTRFS_I(inode), defrag);
	पूर्ण अन्यथा अगर (defrag->last_offset && !defrag->cycled) अणु
		/*
		 * we didn't fill our defrag batch, but
		 * we didn't start at zero.  Make sure we loop
		 * around to the start of the file.
		 */
		defrag->last_offset = 0;
		defrag->cycled = 1;
		btrfs_requeue_inode_defrag(BTRFS_I(inode), defrag);
	पूर्ण अन्यथा अणु
		kmem_cache_मुक्त(btrfs_inode_defrag_cachep, defrag);
	पूर्ण

	iput(inode);
	वापस 0;
cleanup:
	kmem_cache_मुक्त(btrfs_inode_defrag_cachep, defrag);
	वापस ret;
पूर्ण

/*
 * run through the list of inodes in the FS that need
 * defragging
 */
पूर्णांक btrfs_run_defrag_inodes(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा inode_defrag *defrag;
	u64 first_ino = 0;
	u64 root_objectid = 0;

	atomic_inc(&fs_info->defrag_running);
	जबतक (1) अणु
		/* Pause the स्वतः defragger. */
		अगर (test_bit(BTRFS_FS_STATE_REMOUNTING,
			     &fs_info->fs_state))
			अवरोध;

		अगर (!__need_स्वतः_defrag(fs_info))
			अवरोध;

		/* find an inode to defrag */
		defrag = btrfs_pick_defrag_inode(fs_info, root_objectid,
						 first_ino);
		अगर (!defrag) अणु
			अगर (root_objectid || first_ino) अणु
				root_objectid = 0;
				first_ino = 0;
				जारी;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		first_ino = defrag->ino + 1;
		root_objectid = defrag->root;

		__btrfs_run_defrag_inode(fs_info, defrag);
	पूर्ण
	atomic_dec(&fs_info->defrag_running);

	/*
	 * during unmount, we use the transaction_रुको queue to
	 * रुको क्रम the defragger to stop
	 */
	wake_up(&fs_info->transaction_रुको);
	वापस 0;
पूर्ण

/* simple helper to fault in pages and copy.  This should go away
 * and be replaced with calls पूर्णांकo generic code.
 */
अटल noअंतरभूत पूर्णांक btrfs_copy_from_user(loff_t pos, माप_प्रकार ग_लिखो_bytes,
					 काष्ठा page **prepared_pages,
					 काष्ठा iov_iter *i)
अणु
	माप_प्रकार copied = 0;
	माप_प्रकार total_copied = 0;
	पूर्णांक pg = 0;
	पूर्णांक offset = offset_in_page(pos);

	जबतक (ग_लिखो_bytes > 0) अणु
		माप_प्रकार count = min_t(माप_प्रकार,
				     PAGE_SIZE - offset, ग_लिखो_bytes);
		काष्ठा page *page = prepared_pages[pg];
		/*
		 * Copy data from userspace to the current page
		 */
		copied = iov_iter_copy_from_user_atomic(page, i, offset, count);

		/* Flush processor's dcache क्रम this page */
		flush_dcache_page(page);

		/*
		 * अगर we get a partial ग_लिखो, we can end up with
		 * partially up to date pages.  These add
		 * a lot of complनिकासy, so make sure they करोn't
		 * happen by क्रमcing this copy to be retried.
		 *
		 * The rest of the btrfs_file_ग_लिखो code will fall
		 * back to page at a समय copies after we वापस 0.
		 */
		अगर (!PageUptodate(page) && copied < count)
			copied = 0;

		iov_iter_advance(i, copied);
		ग_लिखो_bytes -= copied;
		total_copied += copied;

		/* Return to btrfs_file_ग_लिखो_iter to fault page */
		अगर (unlikely(copied == 0))
			अवरोध;

		अगर (copied < PAGE_SIZE - offset) अणु
			offset += copied;
		पूर्ण अन्यथा अणु
			pg++;
			offset = 0;
		पूर्ण
	पूर्ण
	वापस total_copied;
पूर्ण

/*
 * unlocks pages after btrfs_file_ग_लिखो is करोne with them
 */
अटल व्योम btrfs_drop_pages(काष्ठा page **pages, माप_प्रकार num_pages)
अणु
	माप_प्रकार i;
	क्रम (i = 0; i < num_pages; i++) अणु
		/* page checked is some magic around finding pages that
		 * have been modअगरied without going through btrfs_set_page_dirty
		 * clear it here. There should be no need to mark the pages
		 * accessed as prepare_pages should have marked them accessed
		 * in prepare_pages via find_or_create_page()
		 */
		ClearPageChecked(pages[i]);
		unlock_page(pages[i]);
		put_page(pages[i]);
	पूर्ण
पूर्ण

/*
 * After btrfs_copy_from_user(), update the following things क्रम delalloc:
 * - Mark newly dirtied pages as DELALLOC in the io tree.
 *   Used to advise which range is to be written back.
 * - Mark modअगरied pages as Uptodate/Dirty and not needing COW fixup
 * - Update inode size क्रम past खातापूर्ण ग_लिखो
 */
पूर्णांक btrfs_dirty_pages(काष्ठा btrfs_inode *inode, काष्ठा page **pages,
		      माप_प्रकार num_pages, loff_t pos, माप_प्रकार ग_लिखो_bytes,
		      काष्ठा extent_state **cached, bool noreserve)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	पूर्णांक err = 0;
	पूर्णांक i;
	u64 num_bytes;
	u64 start_pos;
	u64 end_of_last_block;
	u64 end_pos = pos + ग_लिखो_bytes;
	loff_t isize = i_size_पढ़ो(&inode->vfs_inode);
	अचिन्हित पूर्णांक extra_bits = 0;

	अगर (ग_लिखो_bytes == 0)
		वापस 0;

	अगर (noreserve)
		extra_bits |= EXTENT_NORESERVE;

	start_pos = round_करोwn(pos, fs_info->sectorsize);
	num_bytes = round_up(ग_लिखो_bytes + pos - start_pos,
			     fs_info->sectorsize);

	end_of_last_block = start_pos + num_bytes - 1;

	/*
	 * The pages may have alपढ़ोy been dirty, clear out old accounting so
	 * we can set things up properly
	 */
	clear_extent_bit(&inode->io_tree, start_pos, end_of_last_block,
			 EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING | EXTENT_DEFRAG,
			 0, 0, cached);

	err = btrfs_set_extent_delalloc(inode, start_pos, end_of_last_block,
					extra_bits, cached);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < num_pages; i++) अणु
		काष्ठा page *p = pages[i];
		SetPageUptodate(p);
		ClearPageChecked(p);
		set_page_dirty(p);
	पूर्ण

	/*
	 * we've only changed i_size in ram, and we haven't updated
	 * the disk i_size.  There is no need to log the inode
	 * at this समय.
	 */
	अगर (end_pos > isize)
		i_size_ग_लिखो(&inode->vfs_inode, end_pos);
	वापस 0;
पूर्ण

/*
 * this drops all the extents in the cache that पूर्णांकersect the range
 * [start, end].  Existing extents are split as required.
 */
व्योम btrfs_drop_extent_cache(काष्ठा btrfs_inode *inode, u64 start, u64 end,
			     पूर्णांक skip_pinned)
अणु
	काष्ठा extent_map *em;
	काष्ठा extent_map *split = शून्य;
	काष्ठा extent_map *split2 = शून्य;
	काष्ठा extent_map_tree *em_tree = &inode->extent_tree;
	u64 len = end - start + 1;
	u64 gen;
	पूर्णांक ret;
	पूर्णांक testend = 1;
	अचिन्हित दीर्घ flags;
	पूर्णांक compressed = 0;
	bool modअगरied;

	WARN_ON(end < start);
	अगर (end == (u64)-1) अणु
		len = (u64)-1;
		testend = 0;
	पूर्ण
	जबतक (1) अणु
		पूर्णांक no_splits = 0;

		modअगरied = false;
		अगर (!split)
			split = alloc_extent_map();
		अगर (!split2)
			split2 = alloc_extent_map();
		अगर (!split || !split2)
			no_splits = 1;

		ग_लिखो_lock(&em_tree->lock);
		em = lookup_extent_mapping(em_tree, start, len);
		अगर (!em) अणु
			ग_लिखो_unlock(&em_tree->lock);
			अवरोध;
		पूर्ण
		flags = em->flags;
		gen = em->generation;
		अगर (skip_pinned && test_bit(EXTENT_FLAG_PINNED, &em->flags)) अणु
			अगर (testend && em->start + em->len >= start + len) अणु
				मुक्त_extent_map(em);
				ग_लिखो_unlock(&em_tree->lock);
				अवरोध;
			पूर्ण
			start = em->start + em->len;
			अगर (testend)
				len = start + len - (em->start + em->len);
			मुक्त_extent_map(em);
			ग_लिखो_unlock(&em_tree->lock);
			जारी;
		पूर्ण
		compressed = test_bit(EXTENT_FLAG_COMPRESSED, &em->flags);
		clear_bit(EXTENT_FLAG_PINNED, &em->flags);
		clear_bit(EXTENT_FLAG_LOGGING, &flags);
		modअगरied = !list_empty(&em->list);
		अगर (no_splits)
			जाओ next;

		अगर (em->start < start) अणु
			split->start = em->start;
			split->len = start - em->start;

			अगर (em->block_start < EXTENT_MAP_LAST_BYTE) अणु
				split->orig_start = em->orig_start;
				split->block_start = em->block_start;

				अगर (compressed)
					split->block_len = em->block_len;
				अन्यथा
					split->block_len = split->len;
				split->orig_block_len = max(split->block_len,
						em->orig_block_len);
				split->ram_bytes = em->ram_bytes;
			पूर्ण अन्यथा अणु
				split->orig_start = split->start;
				split->block_len = 0;
				split->block_start = em->block_start;
				split->orig_block_len = 0;
				split->ram_bytes = split->len;
			पूर्ण

			split->generation = gen;
			split->flags = flags;
			split->compress_type = em->compress_type;
			replace_extent_mapping(em_tree, em, split, modअगरied);
			मुक्त_extent_map(split);
			split = split2;
			split2 = शून्य;
		पूर्ण
		अगर (testend && em->start + em->len > start + len) अणु
			u64 dअगरf = start + len - em->start;

			split->start = start + len;
			split->len = em->start + em->len - (start + len);
			split->flags = flags;
			split->compress_type = em->compress_type;
			split->generation = gen;

			अगर (em->block_start < EXTENT_MAP_LAST_BYTE) अणु
				split->orig_block_len = max(em->block_len,
						    em->orig_block_len);

				split->ram_bytes = em->ram_bytes;
				अगर (compressed) अणु
					split->block_len = em->block_len;
					split->block_start = em->block_start;
					split->orig_start = em->orig_start;
				पूर्ण अन्यथा अणु
					split->block_len = split->len;
					split->block_start = em->block_start
						+ dअगरf;
					split->orig_start = em->orig_start;
				पूर्ण
			पूर्ण अन्यथा अणु
				split->ram_bytes = split->len;
				split->orig_start = split->start;
				split->block_len = 0;
				split->block_start = em->block_start;
				split->orig_block_len = 0;
			पूर्ण

			अगर (extent_map_in_tree(em)) अणु
				replace_extent_mapping(em_tree, em, split,
						       modअगरied);
			पूर्ण अन्यथा अणु
				ret = add_extent_mapping(em_tree, split,
							 modअगरied);
				ASSERT(ret == 0); /* Logic error */
			पूर्ण
			मुक्त_extent_map(split);
			split = शून्य;
		पूर्ण
next:
		अगर (extent_map_in_tree(em))
			हटाओ_extent_mapping(em_tree, em);
		ग_लिखो_unlock(&em_tree->lock);

		/* once क्रम us */
		मुक्त_extent_map(em);
		/* once क्रम the tree*/
		मुक्त_extent_map(em);
	पूर्ण
	अगर (split)
		मुक्त_extent_map(split);
	अगर (split2)
		मुक्त_extent_map(split2);
पूर्ण

/*
 * this is very complex, but the basic idea is to drop all extents
 * in the range start - end.  hपूर्णांक_block is filled in with a block number
 * that would be a good hपूर्णांक to the block allocator क्रम this file.
 *
 * If an extent पूर्णांकersects the range but is not entirely inside the range
 * it is either truncated or split.  Anything entirely inside the range
 * is deleted from the tree.
 *
 * Note: the VFS' inode number of bytes is not updated, it's up to the caller
 * to deal with that. We set the field 'bytes_found' of the arguments काष्ठाure
 * with the number of allocated bytes found in the target range, so that the
 * caller can update the inode's number of bytes in an atomic way when
 * replacing extents in a range to aव्योम races with stat(2).
 */
पूर्णांक btrfs_drop_extents(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode,
		       काष्ठा btrfs_drop_extents_args *args)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_ref ref = अणु 0 पूर्ण;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key new_key;
	u64 ino = btrfs_ino(inode);
	u64 search_start = args->start;
	u64 disk_bytenr = 0;
	u64 num_bytes = 0;
	u64 extent_offset = 0;
	u64 extent_end = 0;
	u64 last_end = args->start;
	पूर्णांक del_nr = 0;
	पूर्णांक del_slot = 0;
	पूर्णांक extent_type;
	पूर्णांक recow;
	पूर्णांक ret;
	पूर्णांक modअगरy_tree = -1;
	पूर्णांक update_refs;
	पूर्णांक found = 0;
	पूर्णांक leafs_visited = 0;
	काष्ठा btrfs_path *path = args->path;

	args->bytes_found = 0;
	args->extent_inserted = false;

	/* Must always have a path अगर ->replace_extent is true */
	ASSERT(!(args->replace_extent && !args->path));

	अगर (!path) अणु
		path = btrfs_alloc_path();
		अगर (!path) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (args->drop_cache)
		btrfs_drop_extent_cache(inode, args->start, args->end - 1, 0);

	अगर (args->start >= inode->disk_i_size && !args->replace_extent)
		modअगरy_tree = 0;

	update_refs = (test_bit(BTRFS_ROOT_SHAREABLE, &root->state) ||
		       root == fs_info->tree_root);
	जबतक (1) अणु
		recow = 0;
		ret = btrfs_lookup_file_extent(trans, root, path, ino,
					       search_start, modअगरy_tree);
		अगर (ret < 0)
			अवरोध;
		अगर (ret > 0 && path->slots[0] > 0 && search_start == args->start) अणु
			leaf = path->nodes[0];
			btrfs_item_key_to_cpu(leaf, &key, path->slots[0] - 1);
			अगर (key.objectid == ino &&
			    key.type == BTRFS_EXTENT_DATA_KEY)
				path->slots[0]--;
		पूर्ण
		ret = 0;
		leafs_visited++;
next_slot:
		leaf = path->nodes[0];
		अगर (path->slots[0] >= btrfs_header_nritems(leaf)) अणु
			BUG_ON(del_nr > 0);
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				अवरोध;
			अगर (ret > 0) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			leafs_visited++;
			leaf = path->nodes[0];
			recow = 1;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);

		अगर (key.objectid > ino)
			अवरोध;
		अगर (WARN_ON_ONCE(key.objectid < ino) ||
		    key.type < BTRFS_EXTENT_DATA_KEY) अणु
			ASSERT(del_nr == 0);
			path->slots[0]++;
			जाओ next_slot;
		पूर्ण
		अगर (key.type > BTRFS_EXTENT_DATA_KEY || key.offset >= args->end)
			अवरोध;

		fi = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		extent_type = btrfs_file_extent_type(leaf, fi);

		अगर (extent_type == BTRFS_खाता_EXTENT_REG ||
		    extent_type == BTRFS_खाता_EXTENT_PREALLOC) अणु
			disk_bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
			num_bytes = btrfs_file_extent_disk_num_bytes(leaf, fi);
			extent_offset = btrfs_file_extent_offset(leaf, fi);
			extent_end = key.offset +
				btrfs_file_extent_num_bytes(leaf, fi);
		पूर्ण अन्यथा अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
			extent_end = key.offset +
				btrfs_file_extent_ram_bytes(leaf, fi);
		पूर्ण अन्यथा अणु
			/* can't happen */
			BUG();
		पूर्ण

		/*
		 * Don't skip extent items representing 0 byte lengths. They
		 * used to be created (bug) अगर जबतक punching holes we hit
		 * -ENOSPC condition. So अगर we find one here, just ensure we
		 * delete it, otherwise we would insert a new file extent item
		 * with the same key (offset) as that 0 bytes length file
		 * extent item in the call to setup_items_क्रम_insert() later
		 * in this function.
		 */
		अगर (extent_end == key.offset && extent_end >= search_start) अणु
			last_end = extent_end;
			जाओ delete_extent_item;
		पूर्ण

		अगर (extent_end <= search_start) अणु
			path->slots[0]++;
			जाओ next_slot;
		पूर्ण

		found = 1;
		search_start = max(key.offset, args->start);
		अगर (recow || !modअगरy_tree) अणु
			modअगरy_tree = -1;
			btrfs_release_path(path);
			जारी;
		पूर्ण

		/*
		 *     | - range to drop - |
		 *  | -------- extent -------- |
		 */
		अगर (args->start > key.offset && args->end < extent_end) अणु
			BUG_ON(del_nr > 0);
			अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण

			स_नकल(&new_key, &key, माप(new_key));
			new_key.offset = args->start;
			ret = btrfs_duplicate_item(trans, root, path,
						   &new_key);
			अगर (ret == -EAGAIN) अणु
				btrfs_release_path(path);
				जारी;
			पूर्ण
			अगर (ret < 0)
				अवरोध;

			leaf = path->nodes[0];
			fi = btrfs_item_ptr(leaf, path->slots[0] - 1,
					    काष्ठा btrfs_file_extent_item);
			btrfs_set_file_extent_num_bytes(leaf, fi,
							args->start - key.offset);

			fi = btrfs_item_ptr(leaf, path->slots[0],
					    काष्ठा btrfs_file_extent_item);

			extent_offset += args->start - key.offset;
			btrfs_set_file_extent_offset(leaf, fi, extent_offset);
			btrfs_set_file_extent_num_bytes(leaf, fi,
							extent_end - args->start);
			btrfs_mark_buffer_dirty(leaf);

			अगर (update_refs && disk_bytenr > 0) अणु
				btrfs_init_generic_ref(&ref,
						BTRFS_ADD_DELAYED_REF,
						disk_bytenr, num_bytes, 0);
				btrfs_init_data_ref(&ref,
						root->root_key.objectid,
						new_key.objectid,
						args->start - extent_offset);
				ret = btrfs_inc_extent_ref(trans, &ref);
				BUG_ON(ret); /* -ENOMEM */
			पूर्ण
			key.offset = args->start;
		पूर्ण
		/*
		 * From here on out we will have actually dropped something, so
		 * last_end can be updated.
		 */
		last_end = extent_end;

		/*
		 *  | ---- range to drop ----- |
		 *      | -------- extent -------- |
		 */
		अगर (args->start <= key.offset && args->end < extent_end) अणु
			अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण

			स_नकल(&new_key, &key, माप(new_key));
			new_key.offset = args->end;
			btrfs_set_item_key_safe(fs_info, path, &new_key);

			extent_offset += args->end - key.offset;
			btrfs_set_file_extent_offset(leaf, fi, extent_offset);
			btrfs_set_file_extent_num_bytes(leaf, fi,
							extent_end - args->end);
			btrfs_mark_buffer_dirty(leaf);
			अगर (update_refs && disk_bytenr > 0)
				args->bytes_found += args->end - key.offset;
			अवरोध;
		पूर्ण

		search_start = extent_end;
		/*
		 *       | ---- range to drop ----- |
		 *  | -------- extent -------- |
		 */
		अगर (args->start > key.offset && args->end >= extent_end) अणु
			BUG_ON(del_nr > 0);
			अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण

			btrfs_set_file_extent_num_bytes(leaf, fi,
							args->start - key.offset);
			btrfs_mark_buffer_dirty(leaf);
			अगर (update_refs && disk_bytenr > 0)
				args->bytes_found += extent_end - args->start;
			अगर (args->end == extent_end)
				अवरोध;

			path->slots[0]++;
			जाओ next_slot;
		पूर्ण

		/*
		 *  | ---- range to drop ----- |
		 *    | ------ extent ------ |
		 */
		अगर (args->start <= key.offset && args->end >= extent_end) अणु
delete_extent_item:
			अगर (del_nr == 0) अणु
				del_slot = path->slots[0];
				del_nr = 1;
			पूर्ण अन्यथा अणु
				BUG_ON(del_slot + del_nr != path->slots[0]);
				del_nr++;
			पूर्ण

			अगर (update_refs &&
			    extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
				args->bytes_found += extent_end - key.offset;
				extent_end = ALIGN(extent_end,
						   fs_info->sectorsize);
			पूर्ण अन्यथा अगर (update_refs && disk_bytenr > 0) अणु
				btrfs_init_generic_ref(&ref,
						BTRFS_DROP_DELAYED_REF,
						disk_bytenr, num_bytes, 0);
				btrfs_init_data_ref(&ref,
						root->root_key.objectid,
						key.objectid,
						key.offset - extent_offset);
				ret = btrfs_मुक्त_extent(trans, &ref);
				BUG_ON(ret); /* -ENOMEM */
				args->bytes_found += extent_end - key.offset;
			पूर्ण

			अगर (args->end == extent_end)
				अवरोध;

			अगर (path->slots[0] + 1 < btrfs_header_nritems(leaf)) अणु
				path->slots[0]++;
				जाओ next_slot;
			पूर्ण

			ret = btrfs_del_items(trans, root, path, del_slot,
					      del_nr);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				अवरोध;
			पूर्ण

			del_nr = 0;
			del_slot = 0;

			btrfs_release_path(path);
			जारी;
		पूर्ण

		BUG();
	पूर्ण

	अगर (!ret && del_nr > 0) अणु
		/*
		 * Set path->slots[0] to first slot, so that after the delete
		 * अगर items are move off from our leaf to its immediate left or
		 * right neighbor leafs, we end up with a correct and adjusted
		 * path->slots[0] क्रम our insertion (अगर args->replace_extent).
		 */
		path->slots[0] = del_slot;
		ret = btrfs_del_items(trans, root, path, del_slot, del_nr);
		अगर (ret)
			btrfs_पात_transaction(trans, ret);
	पूर्ण

	leaf = path->nodes[0];
	/*
	 * If btrfs_del_items() was called, it might have deleted a leaf, in
	 * which हाल it unlocked our path, so check path->locks[0] matches a
	 * ग_लिखो lock.
	 */
	अगर (!ret && args->replace_extent && leafs_visited == 1 &&
	    path->locks[0] == BTRFS_WRITE_LOCK &&
	    btrfs_leaf_मुक्त_space(leaf) >=
	    माप(काष्ठा btrfs_item) + args->extent_item_size) अणु

		key.objectid = ino;
		key.type = BTRFS_EXTENT_DATA_KEY;
		key.offset = args->start;
		अगर (!del_nr && path->slots[0] < btrfs_header_nritems(leaf)) अणु
			काष्ठा btrfs_key slot_key;

			btrfs_item_key_to_cpu(leaf, &slot_key, path->slots[0]);
			अगर (btrfs_comp_cpu_keys(&key, &slot_key) > 0)
				path->slots[0]++;
		पूर्ण
		setup_items_क्रम_insert(root, path, &key,
				       &args->extent_item_size, 1);
		args->extent_inserted = true;
	पूर्ण

	अगर (!args->path)
		btrfs_मुक्त_path(path);
	अन्यथा अगर (!args->extent_inserted)
		btrfs_release_path(path);
out:
	args->drop_end = found ? min(args->end, last_end) : args->end;

	वापस ret;
पूर्ण

अटल पूर्णांक extent_mergeable(काष्ठा extent_buffer *leaf, पूर्णांक slot,
			    u64 objectid, u64 bytenr, u64 orig_offset,
			    u64 *start, u64 *end)
अणु
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_key key;
	u64 extent_end;

	अगर (slot < 0 || slot >= btrfs_header_nritems(leaf))
		वापस 0;

	btrfs_item_key_to_cpu(leaf, &key, slot);
	अगर (key.objectid != objectid || key.type != BTRFS_EXTENT_DATA_KEY)
		वापस 0;

	fi = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);
	अगर (btrfs_file_extent_type(leaf, fi) != BTRFS_खाता_EXTENT_REG ||
	    btrfs_file_extent_disk_bytenr(leaf, fi) != bytenr ||
	    btrfs_file_extent_offset(leaf, fi) != key.offset - orig_offset ||
	    btrfs_file_extent_compression(leaf, fi) ||
	    btrfs_file_extent_encryption(leaf, fi) ||
	    btrfs_file_extent_other_encoding(leaf, fi))
		वापस 0;

	extent_end = key.offset + btrfs_file_extent_num_bytes(leaf, fi);
	अगर ((*start && *start != key.offset) || (*end && *end != extent_end))
		वापस 0;

	*start = key.offset;
	*end = extent_end;
	वापस 1;
पूर्ण

/*
 * Mark extent in the range start - end as written.
 *
 * This changes extent type from 'pre-allocated' to 'regular'. If only
 * part of extent is marked as written, the extent will be split पूर्णांकo
 * two or three.
 */
पूर्णांक btrfs_mark_extent_written(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_inode *inode, u64 start, u64 end)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_ref ref = अणु 0 पूर्ण;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key new_key;
	u64 bytenr;
	u64 num_bytes;
	u64 extent_end;
	u64 orig_offset;
	u64 other_start;
	u64 other_end;
	u64 split;
	पूर्णांक del_nr = 0;
	पूर्णांक del_slot = 0;
	पूर्णांक recow;
	पूर्णांक ret = 0;
	u64 ino = btrfs_ino(inode);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
again:
	recow = 0;
	split = start;
	key.objectid = ino;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = split;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0 && path->slots[0] > 0)
		path->slots[0]--;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
	अगर (key.objectid != ino ||
	    key.type != BTRFS_EXTENT_DATA_KEY) अणु
		ret = -EINVAL;
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण
	fi = btrfs_item_ptr(leaf, path->slots[0],
			    काष्ठा btrfs_file_extent_item);
	अगर (btrfs_file_extent_type(leaf, fi) != BTRFS_खाता_EXTENT_PREALLOC) अणु
		ret = -EINVAL;
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण
	extent_end = key.offset + btrfs_file_extent_num_bytes(leaf, fi);
	अगर (key.offset > start || extent_end < end) अणु
		ret = -EINVAL;
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
	num_bytes = btrfs_file_extent_disk_num_bytes(leaf, fi);
	orig_offset = key.offset - btrfs_file_extent_offset(leaf, fi);
	स_नकल(&new_key, &key, माप(new_key));

	अगर (start == key.offset && end < extent_end) अणु
		other_start = 0;
		other_end = start;
		अगर (extent_mergeable(leaf, path->slots[0] - 1,
				     ino, bytenr, orig_offset,
				     &other_start, &other_end)) अणु
			new_key.offset = end;
			btrfs_set_item_key_safe(fs_info, path, &new_key);
			fi = btrfs_item_ptr(leaf, path->slots[0],
					    काष्ठा btrfs_file_extent_item);
			btrfs_set_file_extent_generation(leaf, fi,
							 trans->transid);
			btrfs_set_file_extent_num_bytes(leaf, fi,
							extent_end - end);
			btrfs_set_file_extent_offset(leaf, fi,
						     end - orig_offset);
			fi = btrfs_item_ptr(leaf, path->slots[0] - 1,
					    काष्ठा btrfs_file_extent_item);
			btrfs_set_file_extent_generation(leaf, fi,
							 trans->transid);
			btrfs_set_file_extent_num_bytes(leaf, fi,
							end - other_start);
			btrfs_mark_buffer_dirty(leaf);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (start > key.offset && end == extent_end) अणु
		other_start = end;
		other_end = 0;
		अगर (extent_mergeable(leaf, path->slots[0] + 1,
				     ino, bytenr, orig_offset,
				     &other_start, &other_end)) अणु
			fi = btrfs_item_ptr(leaf, path->slots[0],
					    काष्ठा btrfs_file_extent_item);
			btrfs_set_file_extent_num_bytes(leaf, fi,
							start - key.offset);
			btrfs_set_file_extent_generation(leaf, fi,
							 trans->transid);
			path->slots[0]++;
			new_key.offset = start;
			btrfs_set_item_key_safe(fs_info, path, &new_key);

			fi = btrfs_item_ptr(leaf, path->slots[0],
					    काष्ठा btrfs_file_extent_item);
			btrfs_set_file_extent_generation(leaf, fi,
							 trans->transid);
			btrfs_set_file_extent_num_bytes(leaf, fi,
							other_end - start);
			btrfs_set_file_extent_offset(leaf, fi,
						     start - orig_offset);
			btrfs_mark_buffer_dirty(leaf);
			जाओ out;
		पूर्ण
	पूर्ण

	जबतक (start > key.offset || end < extent_end) अणु
		अगर (key.offset == start)
			split = end;

		new_key.offset = split;
		ret = btrfs_duplicate_item(trans, root, path, &new_key);
		अगर (ret == -EAGAIN) अणु
			btrfs_release_path(path);
			जाओ again;
		पूर्ण
		अगर (ret < 0) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण

		leaf = path->nodes[0];
		fi = btrfs_item_ptr(leaf, path->slots[0] - 1,
				    काष्ठा btrfs_file_extent_item);
		btrfs_set_file_extent_generation(leaf, fi, trans->transid);
		btrfs_set_file_extent_num_bytes(leaf, fi,
						split - key.offset);

		fi = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_file_extent_item);

		btrfs_set_file_extent_generation(leaf, fi, trans->transid);
		btrfs_set_file_extent_offset(leaf, fi, split - orig_offset);
		btrfs_set_file_extent_num_bytes(leaf, fi,
						extent_end - split);
		btrfs_mark_buffer_dirty(leaf);

		btrfs_init_generic_ref(&ref, BTRFS_ADD_DELAYED_REF, bytenr,
				       num_bytes, 0);
		btrfs_init_data_ref(&ref, root->root_key.objectid, ino,
				    orig_offset);
		ret = btrfs_inc_extent_ref(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण

		अगर (split == start) अणु
			key.offset = start;
		पूर्ण अन्यथा अणु
			अगर (start != key.offset) अणु
				ret = -EINVAL;
				btrfs_पात_transaction(trans, ret);
				जाओ out;
			पूर्ण
			path->slots[0]--;
			extent_end = end;
		पूर्ण
		recow = 1;
	पूर्ण

	other_start = end;
	other_end = 0;
	btrfs_init_generic_ref(&ref, BTRFS_DROP_DELAYED_REF, bytenr,
			       num_bytes, 0);
	btrfs_init_data_ref(&ref, root->root_key.objectid, ino, orig_offset);
	अगर (extent_mergeable(leaf, path->slots[0] + 1,
			     ino, bytenr, orig_offset,
			     &other_start, &other_end)) अणु
		अगर (recow) अणु
			btrfs_release_path(path);
			जाओ again;
		पूर्ण
		extent_end = other_end;
		del_slot = path->slots[0] + 1;
		del_nr++;
		ret = btrfs_मुक्त_extent(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
	पूर्ण
	other_start = 0;
	other_end = start;
	अगर (extent_mergeable(leaf, path->slots[0] - 1,
			     ino, bytenr, orig_offset,
			     &other_start, &other_end)) अणु
		अगर (recow) अणु
			btrfs_release_path(path);
			जाओ again;
		पूर्ण
		key.offset = other_start;
		del_slot = path->slots[0];
		del_nr++;
		ret = btrfs_मुक्त_extent(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (del_nr == 0) अणु
		fi = btrfs_item_ptr(leaf, path->slots[0],
			   काष्ठा btrfs_file_extent_item);
		btrfs_set_file_extent_type(leaf, fi,
					   BTRFS_खाता_EXTENT_REG);
		btrfs_set_file_extent_generation(leaf, fi, trans->transid);
		btrfs_mark_buffer_dirty(leaf);
	पूर्ण अन्यथा अणु
		fi = btrfs_item_ptr(leaf, del_slot - 1,
			   काष्ठा btrfs_file_extent_item);
		btrfs_set_file_extent_type(leaf, fi,
					   BTRFS_खाता_EXTENT_REG);
		btrfs_set_file_extent_generation(leaf, fi, trans->transid);
		btrfs_set_file_extent_num_bytes(leaf, fi,
						extent_end - key.offset);
		btrfs_mark_buffer_dirty(leaf);

		ret = btrfs_del_items(trans, root, path, del_slot, del_nr);
		अगर (ret < 0) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * on error we वापस an unlocked page and the error value
 * on success we वापस a locked page and 0
 */
अटल पूर्णांक prepare_uptodate_page(काष्ठा inode *inode,
				 काष्ठा page *page, u64 pos,
				 bool क्रमce_uptodate)
अणु
	पूर्णांक ret = 0;

	अगर (((pos & (PAGE_SIZE - 1)) || क्रमce_uptodate) &&
	    !PageUptodate(page)) अणु
		ret = btrfs_पढ़ोpage(शून्य, page);
		अगर (ret)
			वापस ret;
		lock_page(page);
		अगर (!PageUptodate(page)) अणु
			unlock_page(page);
			वापस -EIO;
		पूर्ण
		अगर (page->mapping != inode->i_mapping) अणु
			unlock_page(page);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * this just माला_लो pages पूर्णांकo the page cache and locks them करोwn.
 */
अटल noअंतरभूत पूर्णांक prepare_pages(काष्ठा inode *inode, काष्ठा page **pages,
				  माप_प्रकार num_pages, loff_t pos,
				  माप_प्रकार ग_लिखो_bytes, bool क्रमce_uptodate)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ index = pos >> PAGE_SHIFT;
	gfp_t mask = btrfs_alloc_ग_लिखो_mask(inode->i_mapping);
	पूर्णांक err = 0;
	पूर्णांक faili;

	क्रम (i = 0; i < num_pages; i++) अणु
again:
		pages[i] = find_or_create_page(inode->i_mapping, index + i,
					       mask | __GFP_WRITE);
		अगर (!pages[i]) अणु
			faili = i - 1;
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		err = set_page_extent_mapped(pages[i]);
		अगर (err < 0) अणु
			faili = i;
			जाओ fail;
		पूर्ण

		अगर (i == 0)
			err = prepare_uptodate_page(inode, pages[i], pos,
						    क्रमce_uptodate);
		अगर (!err && i == num_pages - 1)
			err = prepare_uptodate_page(inode, pages[i],
						    pos + ग_लिखो_bytes, false);
		अगर (err) अणु
			put_page(pages[i]);
			अगर (err == -EAGAIN) अणु
				err = 0;
				जाओ again;
			पूर्ण
			faili = i - 1;
			जाओ fail;
		पूर्ण
		रुको_on_page_ग_लिखोback(pages[i]);
	पूर्ण

	वापस 0;
fail:
	जबतक (faili >= 0) अणु
		unlock_page(pages[faili]);
		put_page(pages[faili]);
		faili--;
	पूर्ण
	वापस err;

पूर्ण

/*
 * This function locks the extent and properly रुकोs क्रम data=ordered extents
 * to finish beक्रमe allowing the pages to be modअगरied अगर need.
 *
 * The वापस value:
 * 1 - the extent is locked
 * 0 - the extent is not locked, and everything is OK
 * -EAGAIN - need re-prepare the pages
 * the other < 0 number - Something wrong happens
 */
अटल noअंतरभूत पूर्णांक
lock_and_cleanup_extent_अगर_need(काष्ठा btrfs_inode *inode, काष्ठा page **pages,
				माप_प्रकार num_pages, loff_t pos,
				माप_प्रकार ग_लिखो_bytes,
				u64 *lockstart, u64 *lockend,
				काष्ठा extent_state **cached_state)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	u64 start_pos;
	u64 last_pos;
	पूर्णांक i;
	पूर्णांक ret = 0;

	start_pos = round_करोwn(pos, fs_info->sectorsize);
	last_pos = round_up(pos + ग_लिखो_bytes, fs_info->sectorsize) - 1;

	अगर (start_pos < inode->vfs_inode.i_size) अणु
		काष्ठा btrfs_ordered_extent *ordered;

		lock_extent_bits(&inode->io_tree, start_pos, last_pos,
				cached_state);
		ordered = btrfs_lookup_ordered_range(inode, start_pos,
						     last_pos - start_pos + 1);
		अगर (ordered &&
		    ordered->file_offset + ordered->num_bytes > start_pos &&
		    ordered->file_offset <= last_pos) अणु
			unlock_extent_cached(&inode->io_tree, start_pos,
					last_pos, cached_state);
			क्रम (i = 0; i < num_pages; i++) अणु
				unlock_page(pages[i]);
				put_page(pages[i]);
			पूर्ण
			btrfs_start_ordered_extent(ordered, 1);
			btrfs_put_ordered_extent(ordered);
			वापस -EAGAIN;
		पूर्ण
		अगर (ordered)
			btrfs_put_ordered_extent(ordered);

		*lockstart = start_pos;
		*lockend = last_pos;
		ret = 1;
	पूर्ण

	/*
	 * We should be called after prepare_pages() which should have locked
	 * all pages in the range.
	 */
	क्रम (i = 0; i < num_pages; i++)
		WARN_ON(!PageLocked(pages[i]));

	वापस ret;
पूर्ण

अटल पूर्णांक check_can_nocow(काष्ठा btrfs_inode *inode, loff_t pos,
			   माप_प्रकार *ग_लिखो_bytes, bool noरुको)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_root *root = inode->root;
	u64 lockstart, lockend;
	u64 num_bytes;
	पूर्णांक ret;

	अगर (!(inode->flags & (BTRFS_INODE_NODATACOW | BTRFS_INODE_PREALLOC)))
		वापस 0;

	अगर (!noरुको && !btrfs_drew_try_ग_लिखो_lock(&root->snapshot_lock))
		वापस -EAGAIN;

	lockstart = round_करोwn(pos, fs_info->sectorsize);
	lockend = round_up(pos + *ग_लिखो_bytes,
			   fs_info->sectorsize) - 1;
	num_bytes = lockend - lockstart + 1;

	अगर (noरुको) अणु
		काष्ठा btrfs_ordered_extent *ordered;

		अगर (!try_lock_extent(&inode->io_tree, lockstart, lockend))
			वापस -EAGAIN;

		ordered = btrfs_lookup_ordered_range(inode, lockstart,
						     num_bytes);
		अगर (ordered) अणु
			btrfs_put_ordered_extent(ordered);
			ret = -EAGAIN;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		btrfs_lock_and_flush_ordered_range(inode, lockstart,
						   lockend, शून्य);
	पूर्ण

	ret = can_nocow_extent(&inode->vfs_inode, lockstart, &num_bytes,
			शून्य, शून्य, शून्य, false);
	अगर (ret <= 0) अणु
		ret = 0;
		अगर (!noरुको)
			btrfs_drew_ग_लिखो_unlock(&root->snapshot_lock);
	पूर्ण अन्यथा अणु
		*ग_लिखो_bytes = min_t(माप_प्रकार, *ग_लिखो_bytes ,
				     num_bytes - pos + lockstart);
	पूर्ण
out_unlock:
	unlock_extent(&inode->io_tree, lockstart, lockend);

	वापस ret;
पूर्ण

अटल पूर्णांक check_nocow_nolock(काष्ठा btrfs_inode *inode, loff_t pos,
			      माप_प्रकार *ग_लिखो_bytes)
अणु
	वापस check_can_nocow(inode, pos, ग_लिखो_bytes, true);
पूर्ण

/*
 * Check अगर we can करो nocow ग_लिखो पूर्णांकo the range [@pos, @pos + @ग_लिखो_bytes)
 *
 * @pos:	 File offset
 * @ग_लिखो_bytes: The length to ग_लिखो, will be updated to the nocow ग_लिखोable
 *		 range
 *
 * This function will flush ordered extents in the range to ensure proper
 * nocow checks.
 *
 * Return:
 * >0		and update @ग_लिखो_bytes अगर we can करो nocow ग_लिखो
 *  0		अगर we can't करो nocow ग_लिखो
 * -EAGAIN	अगर we can't get the needed lock or there are ordered extents
 * 		क्रम * (noरुको == true) हाल
 * <0		अगर other error happened
 *
 * NOTE: Callers need to release the lock by btrfs_check_nocow_unlock().
 */
पूर्णांक btrfs_check_nocow_lock(काष्ठा btrfs_inode *inode, loff_t pos,
			   माप_प्रकार *ग_लिखो_bytes)
अणु
	वापस check_can_nocow(inode, pos, ग_लिखो_bytes, false);
पूर्ण

व्योम btrfs_check_nocow_unlock(काष्ठा btrfs_inode *inode)
अणु
	btrfs_drew_ग_लिखो_unlock(&inode->root->snapshot_lock);
पूर्ण

अटल व्योम update_समय_क्रम_ग_लिखो(काष्ठा inode *inode)
अणु
	काष्ठा बारpec64 now;

	अगर (IS_NOCMTIME(inode))
		वापस;

	now = current_समय(inode);
	अगर (!बारpec64_equal(&inode->i_mसमय, &now))
		inode->i_mसमय = now;

	अगर (!बारpec64_equal(&inode->i_स_समय, &now))
		inode->i_स_समय = now;

	अगर (IS_I_VERSION(inode))
		inode_inc_iversion(inode);
पूर्ण

अटल पूर्णांक btrfs_ग_लिखो_check(काष्ठा kiocb *iocb, काष्ठा iov_iter *from,
			     माप_प्रकार count)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	loff_t pos = iocb->ki_pos;
	पूर्णांक ret;
	loff_t oldsize;
	loff_t start_pos;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		माप_प्रकार nocow_bytes = count;

		/* We will allocate space in हाल nodatacow is not set, so bail */
		अगर (check_nocow_nolock(BTRFS_I(inode), pos, &nocow_bytes) <= 0)
			वापस -EAGAIN;
		/*
		 * There are holes in the range or parts of the range that must
		 * be COWed (shared extents, RO block groups, etc), so just bail
		 * out.
		 */
		अगर (nocow_bytes < count)
			वापस -EAGAIN;
	पूर्ण

	current->backing_dev_info = inode_to_bdi(inode);
	ret = file_हटाओ_privs(file);
	अगर (ret)
		वापस ret;

	/*
	 * We reserve space क्रम updating the inode when we reserve space क्रम the
	 * extent we are going to ग_लिखो, so we will enospc out there.  We करोn't
	 * need to start yet another transaction to update the inode as we will
	 * update the inode when we finish writing whatever data we ग_लिखो.
	 */
	update_समय_क्रम_ग_लिखो(inode);

	start_pos = round_करोwn(pos, fs_info->sectorsize);
	oldsize = i_size_पढ़ो(inode);
	अगर (start_pos > oldsize) अणु
		/* Expand hole size to cover ग_लिखो data, preventing empty gap */
		loff_t end_pos = round_up(pos + count, fs_info->sectorsize);

		ret = btrfs_cont_expand(BTRFS_I(inode), oldsize, end_pos);
		अगर (ret) अणु
			current->backing_dev_info = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत sमाप_प्रकार btrfs_buffered_ग_लिखो(काष्ठा kiocb *iocb,
					       काष्ठा iov_iter *i)
अणु
	काष्ठा file *file = iocb->ki_filp;
	loff_t pos;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा page **pages = शून्य;
	काष्ठा extent_changeset *data_reserved = शून्य;
	u64 release_bytes = 0;
	u64 lockstart;
	u64 lockend;
	माप_प्रकार num_written = 0;
	पूर्णांक nrptrs;
	sमाप_प्रकार ret;
	bool only_release_metadata = false;
	bool क्रमce_page_uptodate = false;
	loff_t old_isize = i_size_पढ़ो(inode);
	अचिन्हित पूर्णांक ilock_flags = 0;

	अगर (iocb->ki_flags & IOCB_NOWAIT)
		ilock_flags |= BTRFS_ILOCK_TRY;

	ret = btrfs_inode_lock(inode, ilock_flags);
	अगर (ret < 0)
		वापस ret;

	ret = generic_ग_लिखो_checks(iocb, i);
	अगर (ret <= 0)
		जाओ out;

	ret = btrfs_ग_लिखो_check(iocb, i, ret);
	अगर (ret < 0)
		जाओ out;

	pos = iocb->ki_pos;
	nrptrs = min(DIV_ROUND_UP(iov_iter_count(i), PAGE_SIZE),
			PAGE_SIZE / (माप(काष्ठा page *)));
	nrptrs = min(nrptrs, current->nr_dirtied_छोड़ो - current->nr_dirtied);
	nrptrs = max(nrptrs, 8);
	pages = kदो_स्मृति_array(nrptrs, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	जबतक (iov_iter_count(i) > 0) अणु
		काष्ठा extent_state *cached_state = शून्य;
		माप_प्रकार offset = offset_in_page(pos);
		माप_प्रकार sector_offset;
		माप_प्रकार ग_लिखो_bytes = min(iov_iter_count(i),
					 nrptrs * (माप_प्रकार)PAGE_SIZE -
					 offset);
		माप_प्रकार num_pages;
		माप_प्रकार reserve_bytes;
		माप_प्रकार dirty_pages;
		माप_प्रकार copied;
		माप_प्रकार dirty_sectors;
		माप_प्रकार num_sectors;
		पूर्णांक extents_locked;

		/*
		 * Fault pages beक्रमe locking them in prepare_pages
		 * to aव्योम recursive lock
		 */
		अगर (unlikely(iov_iter_fault_in_पढ़ोable(i, ग_लिखो_bytes))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		only_release_metadata = false;
		sector_offset = pos & (fs_info->sectorsize - 1);

		extent_changeset_release(data_reserved);
		ret = btrfs_check_data_मुक्त_space(BTRFS_I(inode),
						  &data_reserved, pos,
						  ग_लिखो_bytes);
		अगर (ret < 0) अणु
			/*
			 * If we करोn't have to COW at the offset, reserve
			 * metadata only. ग_लिखो_bytes may get smaller than
			 * requested here.
			 */
			अगर (btrfs_check_nocow_lock(BTRFS_I(inode), pos,
						   &ग_लिखो_bytes) > 0)
				only_release_metadata = true;
			अन्यथा
				अवरोध;
		पूर्ण

		num_pages = DIV_ROUND_UP(ग_लिखो_bytes + offset, PAGE_SIZE);
		WARN_ON(num_pages > nrptrs);
		reserve_bytes = round_up(ग_लिखो_bytes + sector_offset,
					 fs_info->sectorsize);
		WARN_ON(reserve_bytes == 0);
		ret = btrfs_delalloc_reserve_metadata(BTRFS_I(inode),
				reserve_bytes);
		अगर (ret) अणु
			अगर (!only_release_metadata)
				btrfs_मुक्त_reserved_data_space(BTRFS_I(inode),
						data_reserved, pos,
						ग_लिखो_bytes);
			अन्यथा
				btrfs_check_nocow_unlock(BTRFS_I(inode));
			अवरोध;
		पूर्ण

		release_bytes = reserve_bytes;
again:
		/*
		 * This is going to setup the pages array with the number of
		 * pages we want, so we करोn't really need to worry about the
		 * contents of pages from loop to loop
		 */
		ret = prepare_pages(inode, pages, num_pages,
				    pos, ग_लिखो_bytes,
				    क्रमce_page_uptodate);
		अगर (ret) अणु
			btrfs_delalloc_release_extents(BTRFS_I(inode),
						       reserve_bytes);
			अवरोध;
		पूर्ण

		extents_locked = lock_and_cleanup_extent_अगर_need(
				BTRFS_I(inode), pages,
				num_pages, pos, ग_लिखो_bytes, &lockstart,
				&lockend, &cached_state);
		अगर (extents_locked < 0) अणु
			अगर (extents_locked == -EAGAIN)
				जाओ again;
			btrfs_delalloc_release_extents(BTRFS_I(inode),
						       reserve_bytes);
			ret = extents_locked;
			अवरोध;
		पूर्ण

		copied = btrfs_copy_from_user(pos, ग_लिखो_bytes, pages, i);

		num_sectors = BTRFS_BYTES_TO_BLKS(fs_info, reserve_bytes);
		dirty_sectors = round_up(copied + sector_offset,
					fs_info->sectorsize);
		dirty_sectors = BTRFS_BYTES_TO_BLKS(fs_info, dirty_sectors);

		/*
		 * अगर we have trouble faulting in the pages, fall
		 * back to one page at a समय
		 */
		अगर (copied < ग_लिखो_bytes)
			nrptrs = 1;

		अगर (copied == 0) अणु
			क्रमce_page_uptodate = true;
			dirty_sectors = 0;
			dirty_pages = 0;
		पूर्ण अन्यथा अणु
			क्रमce_page_uptodate = false;
			dirty_pages = DIV_ROUND_UP(copied + offset,
						   PAGE_SIZE);
		पूर्ण

		अगर (num_sectors > dirty_sectors) अणु
			/* release everything except the sectors we dirtied */
			release_bytes -= dirty_sectors << fs_info->sectorsize_bits;
			अगर (only_release_metadata) अणु
				btrfs_delalloc_release_metadata(BTRFS_I(inode),
							release_bytes, true);
			पूर्ण अन्यथा अणु
				u64 __pos;

				__pos = round_करोwn(pos,
						   fs_info->sectorsize) +
					(dirty_pages << PAGE_SHIFT);
				btrfs_delalloc_release_space(BTRFS_I(inode),
						data_reserved, __pos,
						release_bytes, true);
			पूर्ण
		पूर्ण

		release_bytes = round_up(copied + sector_offset,
					fs_info->sectorsize);

		ret = btrfs_dirty_pages(BTRFS_I(inode), pages,
					dirty_pages, pos, copied,
					&cached_state, only_release_metadata);

		/*
		 * If we have not locked the extent range, because the range's
		 * start offset is >= i_size, we might still have a non-शून्य
		 * cached extent state, acquired जबतक marking the extent range
		 * as delalloc through btrfs_dirty_pages(). Thereक्रमe मुक्त any
		 * possible cached extent state to aव्योम a memory leak.
		 */
		अगर (extents_locked)
			unlock_extent_cached(&BTRFS_I(inode)->io_tree,
					     lockstart, lockend, &cached_state);
		अन्यथा
			मुक्त_extent_state(cached_state);

		btrfs_delalloc_release_extents(BTRFS_I(inode), reserve_bytes);
		अगर (ret) अणु
			btrfs_drop_pages(pages, num_pages);
			अवरोध;
		पूर्ण

		release_bytes = 0;
		अगर (only_release_metadata)
			btrfs_check_nocow_unlock(BTRFS_I(inode));

		btrfs_drop_pages(pages, num_pages);

		cond_resched();

		balance_dirty_pages_ratelimited(inode->i_mapping);

		pos += copied;
		num_written += copied;
	पूर्ण

	kमुक्त(pages);

	अगर (release_bytes) अणु
		अगर (only_release_metadata) अणु
			btrfs_check_nocow_unlock(BTRFS_I(inode));
			btrfs_delalloc_release_metadata(BTRFS_I(inode),
					release_bytes, true);
		पूर्ण अन्यथा अणु
			btrfs_delalloc_release_space(BTRFS_I(inode),
					data_reserved,
					round_करोwn(pos, fs_info->sectorsize),
					release_bytes, true);
		पूर्ण
	पूर्ण

	extent_changeset_मुक्त(data_reserved);
	अगर (num_written > 0) अणु
		pagecache_isize_extended(inode, old_isize, iocb->ki_pos);
		iocb->ki_pos += num_written;
	पूर्ण
out:
	btrfs_inode_unlock(inode, ilock_flags);
	वापस num_written ? num_written : ret;
पूर्ण

अटल sमाप_प्रकार check_direct_IO(काष्ठा btrfs_fs_info *fs_info,
			       स्थिर काष्ठा iov_iter *iter, loff_t offset)
अणु
	स्थिर u32 blocksize_mask = fs_info->sectorsize - 1;

	अगर (offset & blocksize_mask)
		वापस -EINVAL;

	अगर (iov_iter_alignment(iter) & blocksize_mask)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार btrfs_direct_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	loff_t pos;
	sमाप_प्रकार written = 0;
	sमाप_प्रकार written_buffered;
	loff_t endbyte;
	sमाप_प्रकार err;
	अचिन्हित पूर्णांक ilock_flags = 0;
	काष्ठा iomap_dio *dio = शून्य;

	अगर (iocb->ki_flags & IOCB_NOWAIT)
		ilock_flags |= BTRFS_ILOCK_TRY;

	/* If the ग_लिखो DIO is within खातापूर्ण, use a shared lock */
	अगर (iocb->ki_pos + iov_iter_count(from) <= i_size_पढ़ो(inode))
		ilock_flags |= BTRFS_ILOCK_SHARED;

relock:
	err = btrfs_inode_lock(inode, ilock_flags);
	अगर (err < 0)
		वापस err;

	err = generic_ग_लिखो_checks(iocb, from);
	अगर (err <= 0) अणु
		btrfs_inode_unlock(inode, ilock_flags);
		वापस err;
	पूर्ण

	err = btrfs_ग_लिखो_check(iocb, from, err);
	अगर (err < 0) अणु
		btrfs_inode_unlock(inode, ilock_flags);
		जाओ out;
	पूर्ण

	pos = iocb->ki_pos;
	/*
	 * Re-check since file size may have changed just beक्रमe taking the
	 * lock or pos may have changed because of O_APPEND in generic_ग_लिखो_check()
	 */
	अगर ((ilock_flags & BTRFS_ILOCK_SHARED) &&
	    pos + iov_iter_count(from) > i_size_पढ़ो(inode)) अणु
		btrfs_inode_unlock(inode, ilock_flags);
		ilock_flags &= ~BTRFS_ILOCK_SHARED;
		जाओ relock;
	पूर्ण

	अगर (check_direct_IO(fs_info, from, pos)) अणु
		btrfs_inode_unlock(inode, ilock_flags);
		जाओ buffered;
	पूर्ण

	dio = __iomap_dio_rw(iocb, from, &btrfs_dio_iomap_ops, &btrfs_dio_ops,
			     0);

	btrfs_inode_unlock(inode, ilock_flags);

	अगर (IS_ERR_OR_शून्य(dio)) अणु
		err = PTR_ERR_OR_ZERO(dio);
		अगर (err < 0 && err != -ENOTBLK)
			जाओ out;
	पूर्ण अन्यथा अणु
		written = iomap_dio_complete(dio);
	पूर्ण

	अगर (written < 0 || !iov_iter_count(from)) अणु
		err = written;
		जाओ out;
	पूर्ण

buffered:
	pos = iocb->ki_pos;
	written_buffered = btrfs_buffered_ग_लिखो(iocb, from);
	अगर (written_buffered < 0) अणु
		err = written_buffered;
		जाओ out;
	पूर्ण
	/*
	 * Ensure all data is persisted. We want the next direct IO पढ़ो to be
	 * able to पढ़ो what was just written.
	 */
	endbyte = pos + written_buffered - 1;
	err = btrfs_fdataग_लिखो_range(inode, pos, endbyte);
	अगर (err)
		जाओ out;
	err = filemap_fdataरुको_range(inode->i_mapping, pos, endbyte);
	अगर (err)
		जाओ out;
	written += written_buffered;
	iocb->ki_pos = pos + written_buffered;
	invalidate_mapping_pages(file->f_mapping, pos >> PAGE_SHIFT,
				 endbyte >> PAGE_SHIFT);
out:
	वापस written ? written : err;
पूर्ण

अटल sमाप_प्रकार btrfs_file_ग_लिखो_iter(काष्ठा kiocb *iocb,
				    काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा btrfs_inode *inode = BTRFS_I(file_inode(file));
	sमाप_प्रकार num_written = 0;
	स्थिर bool sync = iocb->ki_flags & IOCB_DSYNC;

	/*
	 * If the fs flips पढ़ोonly due to some impossible error, although we
	 * have खोलोed a file as writable, we have to stop this ग_लिखो operation
	 * to ensure consistency.
	 */
	अगर (test_bit(BTRFS_FS_STATE_ERROR, &inode->root->fs_info->fs_state))
		वापस -EROFS;

	अगर (!(iocb->ki_flags & IOCB_सूचीECT) &&
	    (iocb->ki_flags & IOCB_NOWAIT))
		वापस -EOPNOTSUPP;

	अगर (sync)
		atomic_inc(&inode->sync_ग_लिखोrs);

	अगर (iocb->ki_flags & IOCB_सूचीECT)
		num_written = btrfs_direct_ग_लिखो(iocb, from);
	अन्यथा
		num_written = btrfs_buffered_ग_लिखो(iocb, from);

	btrfs_set_inode_last_sub_trans(inode);

	अगर (num_written > 0)
		num_written = generic_ग_लिखो_sync(iocb, num_written);

	अगर (sync)
		atomic_dec(&inode->sync_ग_लिखोrs);

	current->backing_dev_info = शून्य;
	वापस num_written;
पूर्ण

पूर्णांक btrfs_release_file(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा btrfs_file_निजी *निजी = filp->निजी_data;

	अगर (निजी && निजी->filldir_buf)
		kमुक्त(निजी->filldir_buf);
	kमुक्त(निजी);
	filp->निजी_data = शून्य;

	/*
	 * Set by setattr when we are about to truncate a file from a non-zero
	 * size to a zero size.  This tries to flush करोwn new bytes that may
	 * have been written अगर the application were using truncate to replace
	 * a file in place.
	 */
	अगर (test_and_clear_bit(BTRFS_INODE_FLUSH_ON_CLOSE,
			       &BTRFS_I(inode)->runसमय_flags))
			filemap_flush(inode->i_mapping);
	वापस 0;
पूर्ण

अटल पूर्णांक start_ordered_ops(काष्ठा inode *inode, loff_t start, loff_t end)
अणु
	पूर्णांक ret;
	काष्ठा blk_plug plug;

	/*
	 * This is only called in fsync, which would करो synchronous ग_लिखोs, so
	 * a plug can merge adjacent IOs as much as possible.  Esp. in हाल of
	 * multiple disks using raid profile, a large IO can be split to
	 * several segments of stripe length (currently 64K).
	 */
	blk_start_plug(&plug);
	atomic_inc(&BTRFS_I(inode)->sync_ग_लिखोrs);
	ret = btrfs_fdataग_लिखो_range(inode, start, end);
	atomic_dec(&BTRFS_I(inode)->sync_ग_लिखोrs);
	blk_finish_plug(&plug);

	वापस ret;
पूर्ण

अटल अंतरभूत bool skip_inode_logging(स्थिर काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(ctx->inode);
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;

	अगर (btrfs_inode_in_log(inode, fs_info->generation) &&
	    list_empty(&ctx->ordered_extents))
		वापस true;

	/*
	 * If we are करोing a fast fsync we can not bail out अगर the inode's
	 * last_trans is <= then the last committed transaction, because we only
	 * update the last_trans of the inode during ordered extent completion,
	 * and क्रम a fast fsync we करोn't रुको क्रम that, we only रुको क्रम the
	 * ग_लिखोback to complete.
	 */
	अगर (inode->last_trans <= fs_info->last_trans_committed &&
	    (test_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &inode->runसमय_flags) ||
	     list_empty(&ctx->ordered_extents)))
		वापस true;

	वापस false;
पूर्ण

/*
 * fsync call क्रम both files and directories.  This logs the inode पूर्णांकo
 * the tree log instead of क्रमcing full commits whenever possible.
 *
 * It needs to call filemap_fdataरुको so that all ordered extent updates are
 * in the metadata btree are up to date क्रम copying to the log.
 *
 * It drops the inode mutex beक्रमe करोing the tree log commit.  This is an
 * important optimization क्रम directories because holding the mutex prevents
 * new operations on the dir जबतक we ग_लिखो to disk.
 */
पूर्णांक btrfs_sync_file(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा dentry *dentry = file_dentry(file);
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_log_ctx ctx;
	पूर्णांक ret = 0, err;
	u64 len;
	bool full_sync;

	trace_btrfs_sync_file(file, datasync);

	btrfs_init_log_ctx(&ctx, inode);

	/*
	 * Always set the range to a full range, otherwise we can get पूर्णांकo
	 * several problems, from missing file extent items to represent holes
	 * when not using the NO_HOLES feature, to log tree corruption due to
	 * races between hole detection during logging and completion of ordered
	 * extents outside the range, to missing checksums due to ordered extents
	 * क्रम which we flushed only a subset of their pages.
	 */
	start = 0;
	end = Lदीर्घ_उच्च;
	len = (u64)Lदीर्घ_उच्च + 1;

	/*
	 * We ग_लिखो the dirty pages in the range and रुको until they complete
	 * out of the ->i_mutex. If so, we can flush the dirty pages by
	 * multi-task, and make the perक्रमmance up.  See
	 * btrfs_रुको_ordered_range क्रम an explanation of the ASYNC check.
	 */
	ret = start_ordered_ops(inode, start, end);
	अगर (ret)
		जाओ out;

	btrfs_inode_lock(inode, BTRFS_ILOCK_MMAP);

	atomic_inc(&root->log_batch);

	/*
	 * Always check क्रम the full sync flag जबतक holding the inode's lock,
	 * to aव्योम races with other tasks. The flag must be either set all the
	 * समय during logging or always off all the समय जबतक logging.
	 */
	full_sync = test_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
			     &BTRFS_I(inode)->runसमय_flags);

	/*
	 * Beक्रमe we acquired the inode's lock and the mmap lock, someone may
	 * have dirtied more pages in the target range. We need to make sure
	 * that ग_लिखोback क्रम any such pages करोes not start जबतक we are logging
	 * the inode, because अगर it करोes, any of the following might happen when
	 * we are not करोing a full inode sync:
	 *
	 * 1) We log an extent after its ग_लिखोback finishes but beक्रमe its
	 *    checksums are added to the csum tree, leading to -EIO errors
	 *    when attempting to पढ़ो the extent after a log replay.
	 *
	 * 2) We can end up logging an extent beक्रमe its ग_लिखोback finishes.
	 *    Thereक्रमe after the log replay we will have a file extent item
	 *    poपूर्णांकing to an unwritten extent (and no data checksums as well).
	 *
	 * So trigger ग_लिखोback क्रम any eventual new dirty pages and then we
	 * रुको क्रम all ordered extents to complete below.
	 */
	ret = start_ordered_ops(inode, start, end);
	अगर (ret) अणु
		btrfs_inode_unlock(inode, BTRFS_ILOCK_MMAP);
		जाओ out;
	पूर्ण

	/*
	 * We have to करो this here to aव्योम the priority inversion of रुकोing on
	 * IO of a lower priority task जबतक holding a transaction खोलो.
	 *
	 * For a full fsync we रुको क्रम the ordered extents to complete जबतक
	 * क्रम a fast fsync we रुको just क्रम ग_लिखोback to complete, and then
	 * attach the ordered extents to the transaction so that a transaction
	 * commit रुकोs क्रम their completion, to aव्योम data loss अगर we fsync,
	 * the current transaction commits beक्रमe the ordered extents complete
	 * and a घातer failure happens right after that.
	 *
	 * For zoned fileप्रणाली, अगर a ग_लिखो IO uses a ZONE_APPEND command, the
	 * logical address recorded in the ordered extent may change. We need
	 * to रुको क्रम the IO to stabilize the logical address.
	 */
	अगर (full_sync || btrfs_is_zoned(fs_info)) अणु
		ret = btrfs_रुको_ordered_range(inode, start, len);
	पूर्ण अन्यथा अणु
		/*
		 * Get our ordered extents as soon as possible to aव्योम करोing
		 * checksum lookups in the csum tree, and use instead the
		 * checksums attached to the ordered extents.
		 */
		btrfs_get_ordered_extents_क्रम_logging(BTRFS_I(inode),
						      &ctx.ordered_extents);
		ret = filemap_fdataरुको_range(inode->i_mapping, start, end);
	पूर्ण

	अगर (ret)
		जाओ out_release_extents;

	atomic_inc(&root->log_batch);

	smp_mb();
	अगर (skip_inode_logging(&ctx)) अणु
		/*
		 * We've had everything committed since the last समय we were
		 * modअगरied so clear this flag in हाल it was set क्रम whatever
		 * reason, it's no दीर्घer relevant.
		 */
		clear_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
			  &BTRFS_I(inode)->runसमय_flags);
		/*
		 * An ordered extent might have started beक्रमe and completed
		 * alपढ़ोy with io errors, in which हाल the inode was not
		 * updated and we end up here. So check the inode's mapping
		 * क्रम any errors that might have happened since we last
		 * checked called fsync.
		 */
		ret = filemap_check_wb_err(inode->i_mapping, file->f_wb_err);
		जाओ out_release_extents;
	पूर्ण

	/*
	 * We use start here because we will need to रुको on the IO to complete
	 * in btrfs_sync_log, which could require joining a transaction (क्रम
	 * example checking cross references in the nocow path).  If we use join
	 * here we could get पूर्णांकo a situation where we're रुकोing on IO to
	 * happen that is blocked on a transaction trying to commit.  With start
	 * we inc the extग_लिखोr counter, so we रुको क्रम all extग_लिखोrs to निकास
	 * beक्रमe we start blocking joiners.  This comment is to keep somebody
	 * from thinking they are super smart and changing this to
	 * btrfs_join_transaction *cough*Josef*cough*.
	 */
	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out_release_extents;
	पूर्ण
	trans->in_fsync = true;

	ret = btrfs_log_dentry_safe(trans, dentry, &ctx);
	btrfs_release_log_ctx_extents(&ctx);
	अगर (ret < 0) अणु
		/* Fallthrough and commit/मुक्त transaction. */
		ret = 1;
	पूर्ण

	/* we've logged all the items and now have a consistent
	 * version of the file in the log.  It is possible that
	 * someone will come in and modअगरy the file, but that's
	 * fine because the log is consistent on disk, and we
	 * have references to all of the file's extents
	 *
	 * It is possible that someone will come in and log the
	 * file again, but that will end up using the synchronization
	 * inside btrfs_sync_log to keep things safe.
	 */
	btrfs_inode_unlock(inode, BTRFS_ILOCK_MMAP);

	अगर (ret != BTRFS_NO_LOG_SYNC) अणु
		अगर (!ret) अणु
			ret = btrfs_sync_log(trans, root, &ctx);
			अगर (!ret) अणु
				ret = btrfs_end_transaction(trans);
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (!full_sync) अणु
			ret = btrfs_रुको_ordered_range(inode, start, len);
			अगर (ret) अणु
				btrfs_end_transaction(trans);
				जाओ out;
			पूर्ण
		पूर्ण
		ret = btrfs_commit_transaction(trans);
	पूर्ण अन्यथा अणु
		ret = btrfs_end_transaction(trans);
	पूर्ण
out:
	ASSERT(list_empty(&ctx.list));
	err = file_check_and_advance_wb_err(file);
	अगर (!ret)
		ret = err;
	वापस ret > 0 ? -EIO : ret;

out_release_extents:
	btrfs_release_log_ctx_extents(&ctx);
	btrfs_inode_unlock(inode, BTRFS_ILOCK_MMAP);
	जाओ out;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा btrfs_file_vm_ops = अणु
	.fault		= filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो	= btrfs_page_mkग_लिखो,
पूर्ण;

अटल पूर्णांक btrfs_file_mmap(काष्ठा file	*filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा address_space *mapping = filp->f_mapping;

	अगर (!mapping->a_ops->पढ़ोpage)
		वापस -ENOEXEC;

	file_accessed(filp);
	vma->vm_ops = &btrfs_file_vm_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक hole_mergeable(काष्ठा btrfs_inode *inode, काष्ठा extent_buffer *leaf,
			  पूर्णांक slot, u64 start, u64 end)
अणु
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_key key;

	अगर (slot < 0 || slot >= btrfs_header_nritems(leaf))
		वापस 0;

	btrfs_item_key_to_cpu(leaf, &key, slot);
	अगर (key.objectid != btrfs_ino(inode) ||
	    key.type != BTRFS_EXTENT_DATA_KEY)
		वापस 0;

	fi = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);

	अगर (btrfs_file_extent_type(leaf, fi) != BTRFS_खाता_EXTENT_REG)
		वापस 0;

	अगर (btrfs_file_extent_disk_bytenr(leaf, fi))
		वापस 0;

	अगर (key.offset == end)
		वापस 1;
	अगर (key.offset + btrfs_file_extent_num_bytes(leaf, fi) == start)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक fill_holes(काष्ठा btrfs_trans_handle *trans,
		काष्ठा btrfs_inode *inode,
		काष्ठा btrfs_path *path, u64 offset, u64 end)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा extent_map *hole_em;
	काष्ठा extent_map_tree *em_tree = &inode->extent_tree;
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	अगर (btrfs_fs_incompat(fs_info, NO_HOLES))
		जाओ out;

	key.objectid = btrfs_ino(inode);
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = offset;

	ret = btrfs_search_slot(trans, root, &key, path, 0, 1);
	अगर (ret <= 0) अणु
		/*
		 * We should have dropped this offset, so अगर we find it then
		 * something has gone horribly wrong.
		 */
		अगर (ret == 0)
			ret = -EINVAL;
		वापस ret;
	पूर्ण

	leaf = path->nodes[0];
	अगर (hole_mergeable(inode, leaf, path->slots[0] - 1, offset, end)) अणु
		u64 num_bytes;

		path->slots[0]--;
		fi = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		num_bytes = btrfs_file_extent_num_bytes(leaf, fi) +
			end - offset;
		btrfs_set_file_extent_num_bytes(leaf, fi, num_bytes);
		btrfs_set_file_extent_ram_bytes(leaf, fi, num_bytes);
		btrfs_set_file_extent_offset(leaf, fi, 0);
		btrfs_mark_buffer_dirty(leaf);
		जाओ out;
	पूर्ण

	अगर (hole_mergeable(inode, leaf, path->slots[0], offset, end)) अणु
		u64 num_bytes;

		key.offset = offset;
		btrfs_set_item_key_safe(fs_info, path, &key);
		fi = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		num_bytes = btrfs_file_extent_num_bytes(leaf, fi) + end -
			offset;
		btrfs_set_file_extent_num_bytes(leaf, fi, num_bytes);
		btrfs_set_file_extent_ram_bytes(leaf, fi, num_bytes);
		btrfs_set_file_extent_offset(leaf, fi, 0);
		btrfs_mark_buffer_dirty(leaf);
		जाओ out;
	पूर्ण
	btrfs_release_path(path);

	ret = btrfs_insert_file_extent(trans, root, btrfs_ino(inode),
			offset, 0, 0, end - offset, 0, end - offset, 0, 0, 0);
	अगर (ret)
		वापस ret;

out:
	btrfs_release_path(path);

	hole_em = alloc_extent_map();
	अगर (!hole_em) अणु
		btrfs_drop_extent_cache(inode, offset, end - 1, 0);
		set_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &inode->runसमय_flags);
	पूर्ण अन्यथा अणु
		hole_em->start = offset;
		hole_em->len = end - offset;
		hole_em->ram_bytes = hole_em->len;
		hole_em->orig_start = offset;

		hole_em->block_start = EXTENT_MAP_HOLE;
		hole_em->block_len = 0;
		hole_em->orig_block_len = 0;
		hole_em->compress_type = BTRFS_COMPRESS_NONE;
		hole_em->generation = trans->transid;

		करो अणु
			btrfs_drop_extent_cache(inode, offset, end - 1, 0);
			ग_लिखो_lock(&em_tree->lock);
			ret = add_extent_mapping(em_tree, hole_em, 1);
			ग_लिखो_unlock(&em_tree->lock);
		पूर्ण जबतक (ret == -EEXIST);
		मुक्त_extent_map(hole_em);
		अगर (ret)
			set_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
					&inode->runसमय_flags);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Find a hole extent on given inode and change start/len to the end of hole
 * extent.(hole/vacuum extent whose em->start <= start &&
 *	   em->start + em->len > start)
 * When a hole extent is found, वापस 1 and modअगरy start/len.
 */
अटल पूर्णांक find_first_non_hole(काष्ठा btrfs_inode *inode, u64 *start, u64 *len)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा extent_map *em;
	पूर्णांक ret = 0;

	em = btrfs_get_extent(inode, शून्य, 0,
			      round_करोwn(*start, fs_info->sectorsize),
			      round_up(*len, fs_info->sectorsize));
	अगर (IS_ERR(em))
		वापस PTR_ERR(em);

	/* Hole or vacuum extent(only exists in no-hole mode) */
	अगर (em->block_start == EXTENT_MAP_HOLE) अणु
		ret = 1;
		*len = em->start + em->len > *start + *len ?
		       0 : *start + *len - em->start - em->len;
		*start = em->start + em->len;
	पूर्ण
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_punch_hole_lock_range(काष्ठा inode *inode,
				       स्थिर u64 lockstart,
				       स्थिर u64 lockend,
				       काष्ठा extent_state **cached_state)
अणु
	जबतक (1) अणु
		काष्ठा btrfs_ordered_extent *ordered;
		पूर्णांक ret;

		truncate_pagecache_range(inode, lockstart, lockend);

		lock_extent_bits(&BTRFS_I(inode)->io_tree, lockstart, lockend,
				 cached_state);
		ordered = btrfs_lookup_first_ordered_extent(BTRFS_I(inode),
							    lockend);

		/*
		 * We need to make sure we have no ordered extents in this range
		 * and nobody raced in and पढ़ो a page in this range, अगर we did
		 * we need to try again.
		 */
		अगर ((!ordered ||
		    (ordered->file_offset + ordered->num_bytes <= lockstart ||
		     ordered->file_offset > lockend)) &&
		     !filemap_range_has_page(inode->i_mapping,
					     lockstart, lockend)) अणु
			अगर (ordered)
				btrfs_put_ordered_extent(ordered);
			अवरोध;
		पूर्ण
		अगर (ordered)
			btrfs_put_ordered_extent(ordered);
		unlock_extent_cached(&BTRFS_I(inode)->io_tree, lockstart,
				     lockend, cached_state);
		ret = btrfs_रुको_ordered_range(inode, lockstart,
					       lockend - lockstart + 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_insert_replace_extent(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_inode *inode,
				     काष्ठा btrfs_path *path,
				     काष्ठा btrfs_replace_extent_info *extent_info,
				     स्थिर u64 replace_len,
				     स्थिर u64 bytes_to_drop)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_file_extent_item *extent;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	पूर्णांक slot;
	काष्ठा btrfs_ref ref = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (replace_len == 0)
		वापस 0;

	अगर (extent_info->disk_offset == 0 &&
	    btrfs_fs_incompat(fs_info, NO_HOLES)) अणु
		btrfs_update_inode_bytes(inode, 0, bytes_to_drop);
		वापस 0;
	पूर्ण

	key.objectid = btrfs_ino(inode);
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = extent_info->file_offset;
	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      माप(काष्ठा btrfs_file_extent_item));
	अगर (ret)
		वापस ret;
	leaf = path->nodes[0];
	slot = path->slots[0];
	ग_लिखो_extent_buffer(leaf, extent_info->extent_buf,
			    btrfs_item_ptr_offset(leaf, slot),
			    माप(काष्ठा btrfs_file_extent_item));
	extent = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);
	ASSERT(btrfs_file_extent_type(leaf, extent) != BTRFS_खाता_EXTENT_INLINE);
	btrfs_set_file_extent_offset(leaf, extent, extent_info->data_offset);
	btrfs_set_file_extent_num_bytes(leaf, extent, replace_len);
	अगर (extent_info->is_new_extent)
		btrfs_set_file_extent_generation(leaf, extent, trans->transid);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	ret = btrfs_inode_set_file_extent_range(inode, extent_info->file_offset,
						replace_len);
	अगर (ret)
		वापस ret;

	/* If it's a hole, nothing more needs to be करोne. */
	अगर (extent_info->disk_offset == 0) अणु
		btrfs_update_inode_bytes(inode, 0, bytes_to_drop);
		वापस 0;
	पूर्ण

	btrfs_update_inode_bytes(inode, replace_len, bytes_to_drop);

	अगर (extent_info->is_new_extent && extent_info->insertions == 0) अणु
		key.objectid = extent_info->disk_offset;
		key.type = BTRFS_EXTENT_ITEM_KEY;
		key.offset = extent_info->disk_len;
		ret = btrfs_alloc_reserved_file_extent(trans, root,
						       btrfs_ino(inode),
						       extent_info->file_offset,
						       extent_info->qgroup_reserved,
						       &key);
	पूर्ण अन्यथा अणु
		u64 ref_offset;

		btrfs_init_generic_ref(&ref, BTRFS_ADD_DELAYED_REF,
				       extent_info->disk_offset,
				       extent_info->disk_len, 0);
		ref_offset = extent_info->file_offset - extent_info->data_offset;
		btrfs_init_data_ref(&ref, root->root_key.objectid,
				    btrfs_ino(inode), ref_offset);
		ret = btrfs_inc_extent_ref(trans, &ref);
	पूर्ण

	extent_info->insertions++;

	वापस ret;
पूर्ण

/*
 * The respective range must have been previously locked, as well as the inode.
 * The end offset is inclusive (last byte of the range).
 * @extent_info is शून्य क्रम fallocate's hole punching and non-शून्य when replacing
 * the file range with an extent.
 * When not punching a hole, we करोn't want to end up in a state where we dropped
 * extents without inserting a new one, so we must पात the transaction to aव्योम
 * a corruption.
 */
पूर्णांक btrfs_replace_file_extents(काष्ठा btrfs_inode *inode,
			       काष्ठा btrfs_path *path, स्थिर u64 start,
			       स्थिर u64 end,
			       काष्ठा btrfs_replace_extent_info *extent_info,
			       काष्ठा btrfs_trans_handle **trans_out)
अणु
	काष्ठा btrfs_drop_extents_args drop_args = अणु 0 पूर्ण;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 min_size = btrfs_calc_insert_metadata_size(fs_info, 1);
	u64 ino_size = round_up(inode->vfs_inode.i_size, fs_info->sectorsize);
	काष्ठा btrfs_trans_handle *trans = शून्य;
	काष्ठा btrfs_block_rsv *rsv;
	अचिन्हित पूर्णांक rsv_count;
	u64 cur_offset;
	u64 len = end - start;
	पूर्णांक ret = 0;

	अगर (end <= start)
		वापस -EINVAL;

	rsv = btrfs_alloc_block_rsv(fs_info, BTRFS_BLOCK_RSV_TEMP);
	अगर (!rsv) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	rsv->size = btrfs_calc_insert_metadata_size(fs_info, 1);
	rsv->failfast = 1;

	/*
	 * 1 - update the inode
	 * 1 - removing the extents in the range
	 * 1 - adding the hole extent अगर no_holes isn't set or अगर we are
	 *     replacing the range with a new extent
	 */
	अगर (!btrfs_fs_incompat(fs_info, NO_HOLES) || extent_info)
		rsv_count = 3;
	अन्यथा
		rsv_count = 2;

	trans = btrfs_start_transaction(root, rsv_count);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		trans = शून्य;
		जाओ out_मुक्त;
	पूर्ण

	ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv, rsv,
				      min_size, false);
	BUG_ON(ret);
	trans->block_rsv = rsv;

	cur_offset = start;
	drop_args.path = path;
	drop_args.end = end + 1;
	drop_args.drop_cache = true;
	जबतक (cur_offset < end) अणु
		drop_args.start = cur_offset;
		ret = btrfs_drop_extents(trans, root, inode, &drop_args);
		/* If we are punching a hole decrement the inode's byte count */
		अगर (!extent_info)
			btrfs_update_inode_bytes(inode, 0,
						 drop_args.bytes_found);
		अगर (ret != -ENOSPC) अणु
			/*
			 * When cloning we want to aव्योम transaction पातs when
			 * nothing was करोne and we are attempting to clone parts
			 * of अंतरभूत extents, in such हालs -EOPNOTSUPP is
			 * वापसed by __btrfs_drop_extents() without having
			 * changed anything in the file.
			 */
			अगर (extent_info && !extent_info->is_new_extent &&
			    ret && ret != -EOPNOTSUPP)
				btrfs_पात_transaction(trans, ret);
			अवरोध;
		पूर्ण

		trans->block_rsv = &fs_info->trans_block_rsv;

		अगर (!extent_info && cur_offset < drop_args.drop_end &&
		    cur_offset < ino_size) अणु
			ret = fill_holes(trans, inode, path, cur_offset,
					 drop_args.drop_end);
			अगर (ret) अणु
				/*
				 * If we failed then we didn't insert our hole
				 * entries क्रम the area we dropped, so now the
				 * fs is corrupted, so we must पात the
				 * transaction.
				 */
				btrfs_पात_transaction(trans, ret);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (!extent_info && cur_offset < drop_args.drop_end) अणु
			/*
			 * We are past the i_size here, but since we didn't
			 * insert holes we need to clear the mapped area so we
			 * know to not set disk_i_size in this area until a new
			 * file extent is inserted here.
			 */
			ret = btrfs_inode_clear_file_extent_range(inode,
					cur_offset,
					drop_args.drop_end - cur_offset);
			अगर (ret) अणु
				/*
				 * We couldn't clear our area, so we could
				 * presumably adjust up and corrupt the fs, so
				 * we need to पात.
				 */
				btrfs_पात_transaction(trans, ret);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (extent_info &&
		    drop_args.drop_end > extent_info->file_offset) अणु
			u64 replace_len = drop_args.drop_end -
					  extent_info->file_offset;

			ret = btrfs_insert_replace_extent(trans, inode,	path,
					extent_info, replace_len,
					drop_args.bytes_found);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				अवरोध;
			पूर्ण
			extent_info->data_len -= replace_len;
			extent_info->data_offset += replace_len;
			extent_info->file_offset += replace_len;
		पूर्ण

		ret = btrfs_update_inode(trans, root, inode);
		अगर (ret)
			अवरोध;

		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(fs_info);

		trans = btrfs_start_transaction(root, rsv_count);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			trans = शून्य;
			अवरोध;
		पूर्ण

		ret = btrfs_block_rsv_migrate(&fs_info->trans_block_rsv,
					      rsv, min_size, false);
		BUG_ON(ret);	/* shouldn't happen */
		trans->block_rsv = rsv;

		cur_offset = drop_args.drop_end;
		len = end - cur_offset;
		अगर (!extent_info && len) अणु
			ret = find_first_non_hole(inode, &cur_offset, &len);
			अगर (unlikely(ret < 0))
				अवरोध;
			अगर (ret && !len) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If we were cloning, क्रमce the next fsync to be a full one since we
	 * we replaced (or just dropped in the हाल of cloning holes when
	 * NO_HOLES is enabled) file extent items and did not setup new extent
	 * maps क्रम the replacement extents (or holes).
	 */
	अगर (extent_info && !extent_info->is_new_extent)
		set_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &inode->runसमय_flags);

	अगर (ret)
		जाओ out_trans;

	trans->block_rsv = &fs_info->trans_block_rsv;
	/*
	 * If we are using the NO_HOLES feature we might have had alपढ़ोy an
	 * hole that overlaps a part of the region [lockstart, lockend] and
	 * ends at (or beyond) lockend. Since we have no file extent items to
	 * represent holes, drop_end can be less than lockend and so we must
	 * make sure we have an extent map representing the existing hole (the
	 * call to __btrfs_drop_extents() might have dropped the existing extent
	 * map representing the existing hole), otherwise the fast fsync path
	 * will not record the existence of the hole region
	 * [existing_hole_start, lockend].
	 */
	अगर (drop_args.drop_end <= end)
		drop_args.drop_end = end + 1;
	/*
	 * Don't insert file hole extent item if it's क्रम a range beyond eof
	 * (because it's useless) or अगर it represents a 0 bytes range (when
	 * cur_offset == drop_end).
	 */
	अगर (!extent_info && cur_offset < ino_size &&
	    cur_offset < drop_args.drop_end) अणु
		ret = fill_holes(trans, inode, path, cur_offset,
				 drop_args.drop_end);
		अगर (ret) अणु
			/* Same comment as above. */
			btrfs_पात_transaction(trans, ret);
			जाओ out_trans;
		पूर्ण
	पूर्ण अन्यथा अगर (!extent_info && cur_offset < drop_args.drop_end) अणु
		/* See the comment in the loop above क्रम the reasoning here. */
		ret = btrfs_inode_clear_file_extent_range(inode, cur_offset,
					drop_args.drop_end - cur_offset);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_trans;
		पूर्ण

	पूर्ण
	अगर (extent_info) अणु
		ret = btrfs_insert_replace_extent(trans, inode, path,
				extent_info, extent_info->data_len,
				drop_args.bytes_found);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out_trans;
		पूर्ण
	पूर्ण

out_trans:
	अगर (!trans)
		जाओ out_मुक्त;

	trans->block_rsv = &fs_info->trans_block_rsv;
	अगर (ret)
		btrfs_end_transaction(trans);
	अन्यथा
		*trans_out = trans;
out_मुक्त:
	btrfs_मुक्त_block_rsv(fs_info, rsv);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_punch_hole(काष्ठा inode *inode, loff_t offset, loff_t len)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	u64 lockstart;
	u64 lockend;
	u64 tail_start;
	u64 tail_len;
	u64 orig_start = offset;
	पूर्णांक ret = 0;
	bool same_block;
	u64 ino_size;
	bool truncated_block = false;
	bool updated_inode = false;

	ret = btrfs_रुको_ordered_range(inode, offset, len);
	अगर (ret)
		वापस ret;

	btrfs_inode_lock(inode, BTRFS_ILOCK_MMAP);
	ino_size = round_up(inode->i_size, fs_info->sectorsize);
	ret = find_first_non_hole(BTRFS_I(inode), &offset, &len);
	अगर (ret < 0)
		जाओ out_only_mutex;
	अगर (ret && !len) अणु
		/* Alपढ़ोy in a large hole */
		ret = 0;
		जाओ out_only_mutex;
	पूर्ण

	lockstart = round_up(offset, btrfs_inode_sectorsize(BTRFS_I(inode)));
	lockend = round_करोwn(offset + len,
			     btrfs_inode_sectorsize(BTRFS_I(inode))) - 1;
	same_block = (BTRFS_BYTES_TO_BLKS(fs_info, offset))
		== (BTRFS_BYTES_TO_BLKS(fs_info, offset + len - 1));
	/*
	 * We needn't truncate any block which is beyond the end of the file
	 * because we are sure there is no data there.
	 */
	/*
	 * Only करो this अगर we are in the same block and we aren't करोing the
	 * entire block.
	 */
	अगर (same_block && len < fs_info->sectorsize) अणु
		अगर (offset < ino_size) अणु
			truncated_block = true;
			ret = btrfs_truncate_block(BTRFS_I(inode), offset, len,
						   0);
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
		जाओ out_only_mutex;
	पूर्ण

	/* zero back part of the first block */
	अगर (offset < ino_size) अणु
		truncated_block = true;
		ret = btrfs_truncate_block(BTRFS_I(inode), offset, 0, 0);
		अगर (ret) अणु
			btrfs_inode_unlock(inode, BTRFS_ILOCK_MMAP);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Check the aligned pages after the first unaligned page,
	 * अगर offset != orig_start, which means the first unaligned page
	 * including several following pages are alपढ़ोy in holes,
	 * the extra check can be skipped */
	अगर (offset == orig_start) अणु
		/* after truncate page, check hole again */
		len = offset + len - lockstart;
		offset = lockstart;
		ret = find_first_non_hole(BTRFS_I(inode), &offset, &len);
		अगर (ret < 0)
			जाओ out_only_mutex;
		अगर (ret && !len) अणु
			ret = 0;
			जाओ out_only_mutex;
		पूर्ण
		lockstart = offset;
	पूर्ण

	/* Check the tail unaligned part is in a hole */
	tail_start = lockend + 1;
	tail_len = offset + len - tail_start;
	अगर (tail_len) अणु
		ret = find_first_non_hole(BTRFS_I(inode), &tail_start, &tail_len);
		अगर (unlikely(ret < 0))
			जाओ out_only_mutex;
		अगर (!ret) अणु
			/* zero the front end of the last page */
			अगर (tail_start + tail_len < ino_size) अणु
				truncated_block = true;
				ret = btrfs_truncate_block(BTRFS_I(inode),
							tail_start + tail_len,
							0, 1);
				अगर (ret)
					जाओ out_only_mutex;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (lockend < lockstart) अणु
		ret = 0;
		जाओ out_only_mutex;
	पूर्ण

	ret = btrfs_punch_hole_lock_range(inode, lockstart, lockend,
					  &cached_state);
	अगर (ret)
		जाओ out_only_mutex;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = btrfs_replace_file_extents(BTRFS_I(inode), path, lockstart,
					 lockend, शून्य, &trans);
	btrfs_मुक्त_path(path);
	अगर (ret)
		जाओ out;

	ASSERT(trans != शून्य);
	inode_inc_iversion(inode);
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	updated_inode = true;
	btrfs_end_transaction(trans);
	btrfs_btree_balance_dirty(fs_info);
out:
	unlock_extent_cached(&BTRFS_I(inode)->io_tree, lockstart, lockend,
			     &cached_state);
out_only_mutex:
	अगर (!updated_inode && truncated_block && !ret) अणु
		/*
		 * If we only end up zeroing part of a page, we still need to
		 * update the inode item, so that all the समय fields are
		 * updated as well as the necessary btrfs inode in memory fields
		 * क्रम detecting, at fsync समय, अगर the inode isn't yet in the
		 * log tree or it's there but not up to date.
		 */
		काष्ठा बारpec64 now = current_समय(inode);

		inode_inc_iversion(inode);
		inode->i_mसमय = now;
		inode->i_स_समय = now;
		trans = btrfs_start_transaction(root, 1);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
		पूर्ण अन्यथा अणु
			पूर्णांक ret2;

			ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
			ret2 = btrfs_end_transaction(trans);
			अगर (!ret)
				ret = ret2;
		पूर्ण
	पूर्ण
	btrfs_inode_unlock(inode, BTRFS_ILOCK_MMAP);
	वापस ret;
पूर्ण

/* Helper काष्ठाure to record which range is alपढ़ोy reserved */
काष्ठा falloc_range अणु
	काष्ठा list_head list;
	u64 start;
	u64 len;
पूर्ण;

/*
 * Helper function to add falloc range
 *
 * Caller should have locked the larger range of extent containing
 * [start, len)
 */
अटल पूर्णांक add_falloc_range(काष्ठा list_head *head, u64 start, u64 len)
अणु
	काष्ठा falloc_range *prev = शून्य;
	काष्ठा falloc_range *range = शून्य;

	अगर (list_empty(head))
		जाओ insert;

	/*
	 * As fallocate iterate by bytenr order, we only need to check
	 * the last range.
	 */
	prev = list_entry(head->prev, काष्ठा falloc_range, list);
	अगर (prev->start + prev->len == start) अणु
		prev->len += len;
		वापस 0;
	पूर्ण
insert:
	range = kदो_स्मृति(माप(*range), GFP_KERNEL);
	अगर (!range)
		वापस -ENOMEM;
	range->start = start;
	range->len = len;
	list_add_tail(&range->list, head);
	वापस 0;
पूर्ण

अटल पूर्णांक btrfs_fallocate_update_isize(काष्ठा inode *inode,
					स्थिर u64 end,
					स्थिर पूर्णांक mode)
अणु
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = BTRFS_I(inode)->root;
	पूर्णांक ret;
	पूर्णांक ret2;

	अगर (mode & FALLOC_FL_KEEP_SIZE || end <= i_size_पढ़ो(inode))
		वापस 0;

	trans = btrfs_start_transaction(root, 1);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	inode->i_स_समय = current_समय(inode);
	i_size_ग_लिखो(inode, end);
	btrfs_inode_safe_disk_i_size_ग_लिखो(BTRFS_I(inode), 0);
	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	ret2 = btrfs_end_transaction(trans);

	वापस ret ? ret : ret2;
पूर्ण

क्रमागत अणु
	RANGE_BOUNDARY_WRITTEN_EXTENT,
	RANGE_BOUNDARY_PREALLOC_EXTENT,
	RANGE_BOUNDARY_HOLE,
पूर्ण;

अटल पूर्णांक btrfs_zero_range_check_range_boundary(काष्ठा btrfs_inode *inode,
						 u64 offset)
अणु
	स्थिर u64 sectorsize = btrfs_inode_sectorsize(inode);
	काष्ठा extent_map *em;
	पूर्णांक ret;

	offset = round_करोwn(offset, sectorsize);
	em = btrfs_get_extent(inode, शून्य, 0, offset, sectorsize);
	अगर (IS_ERR(em))
		वापस PTR_ERR(em);

	अगर (em->block_start == EXTENT_MAP_HOLE)
		ret = RANGE_BOUNDARY_HOLE;
	अन्यथा अगर (test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
		ret = RANGE_BOUNDARY_PREALLOC_EXTENT;
	अन्यथा
		ret = RANGE_BOUNDARY_WRITTEN_EXTENT;

	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_zero_range(काष्ठा inode *inode,
			    loff_t offset,
			    loff_t len,
			    स्थिर पूर्णांक mode)
अणु
	काष्ठा btrfs_fs_info *fs_info = BTRFS_I(inode)->root->fs_info;
	काष्ठा extent_map *em;
	काष्ठा extent_changeset *data_reserved = शून्य;
	पूर्णांक ret;
	u64 alloc_hपूर्णांक = 0;
	स्थिर u64 sectorsize = btrfs_inode_sectorsize(BTRFS_I(inode));
	u64 alloc_start = round_करोwn(offset, sectorsize);
	u64 alloc_end = round_up(offset + len, sectorsize);
	u64 bytes_to_reserve = 0;
	bool space_reserved = false;

	inode_dio_रुको(inode);

	em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, alloc_start,
			      alloc_end - alloc_start);
	अगर (IS_ERR(em)) अणु
		ret = PTR_ERR(em);
		जाओ out;
	पूर्ण

	/*
	 * Aव्योम hole punching and extent allocation क्रम some हालs. More हालs
	 * could be considered, but these are unlikely common and we keep things
	 * as simple as possible क्रम now. Also, पूर्णांकentionally, अगर the target
	 * range contains one or more pपुनः_स्मृति extents together with regular
	 * extents and holes, we drop all the existing extents and allocate a
	 * new pपुनः_स्मृति extent, so that we get a larger contiguous disk extent.
	 */
	अगर (em->start <= alloc_start &&
	    test_bit(EXTENT_FLAG_PREALLOC, &em->flags)) अणु
		स्थिर u64 em_end = em->start + em->len;

		अगर (em_end >= offset + len) अणु
			/*
			 * The whole range is alपढ़ोy a pपुनः_स्मृति extent,
			 * करो nothing except updating the inode's i_size अगर
			 * needed.
			 */
			मुक्त_extent_map(em);
			ret = btrfs_fallocate_update_isize(inode, offset + len,
							   mode);
			जाओ out;
		पूर्ण
		/*
		 * Part of the range is alपढ़ोy a pपुनः_स्मृति extent, so operate
		 * only on the reमुख्यing part of the range.
		 */
		alloc_start = em_end;
		ASSERT(IS_ALIGNED(alloc_start, sectorsize));
		len = offset + len - alloc_start;
		offset = alloc_start;
		alloc_hपूर्णांक = em->block_start + em->len;
	पूर्ण
	मुक्त_extent_map(em);

	अगर (BTRFS_BYTES_TO_BLKS(fs_info, offset) ==
	    BTRFS_BYTES_TO_BLKS(fs_info, offset + len - 1)) अणु
		em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, alloc_start,
				      sectorsize);
		अगर (IS_ERR(em)) अणु
			ret = PTR_ERR(em);
			जाओ out;
		पूर्ण

		अगर (test_bit(EXTENT_FLAG_PREALLOC, &em->flags)) अणु
			मुक्त_extent_map(em);
			ret = btrfs_fallocate_update_isize(inode, offset + len,
							   mode);
			जाओ out;
		पूर्ण
		अगर (len < sectorsize && em->block_start != EXTENT_MAP_HOLE) अणु
			मुक्त_extent_map(em);
			ret = btrfs_truncate_block(BTRFS_I(inode), offset, len,
						   0);
			अगर (!ret)
				ret = btrfs_fallocate_update_isize(inode,
								   offset + len,
								   mode);
			वापस ret;
		पूर्ण
		मुक्त_extent_map(em);
		alloc_start = round_करोwn(offset, sectorsize);
		alloc_end = alloc_start + sectorsize;
		जाओ reserve_space;
	पूर्ण

	alloc_start = round_up(offset, sectorsize);
	alloc_end = round_करोwn(offset + len, sectorsize);

	/*
	 * For unaligned ranges, check the pages at the boundaries, they might
	 * map to an extent, in which हाल we need to partially zero them, or
	 * they might map to a hole, in which हाल we need our allocation range
	 * to cover them.
	 */
	अगर (!IS_ALIGNED(offset, sectorsize)) अणु
		ret = btrfs_zero_range_check_range_boundary(BTRFS_I(inode),
							    offset);
		अगर (ret < 0)
			जाओ out;
		अगर (ret == RANGE_BOUNDARY_HOLE) अणु
			alloc_start = round_करोwn(offset, sectorsize);
			ret = 0;
		पूर्ण अन्यथा अगर (ret == RANGE_BOUNDARY_WRITTEN_EXTENT) अणु
			ret = btrfs_truncate_block(BTRFS_I(inode), offset, 0, 0);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
	पूर्ण

	अगर (!IS_ALIGNED(offset + len, sectorsize)) अणु
		ret = btrfs_zero_range_check_range_boundary(BTRFS_I(inode),
							    offset + len);
		अगर (ret < 0)
			जाओ out;
		अगर (ret == RANGE_BOUNDARY_HOLE) अणु
			alloc_end = round_up(offset + len, sectorsize);
			ret = 0;
		पूर्ण अन्यथा अगर (ret == RANGE_BOUNDARY_WRITTEN_EXTENT) अणु
			ret = btrfs_truncate_block(BTRFS_I(inode), offset + len,
						   0, 1);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
	पूर्ण

reserve_space:
	अगर (alloc_start < alloc_end) अणु
		काष्ठा extent_state *cached_state = शून्य;
		स्थिर u64 lockstart = alloc_start;
		स्थिर u64 lockend = alloc_end - 1;

		bytes_to_reserve = alloc_end - alloc_start;
		ret = btrfs_alloc_data_chunk_ondemand(BTRFS_I(inode),
						      bytes_to_reserve);
		अगर (ret < 0)
			जाओ out;
		space_reserved = true;
		ret = btrfs_punch_hole_lock_range(inode, lockstart, lockend,
						  &cached_state);
		अगर (ret)
			जाओ out;
		ret = btrfs_qgroup_reserve_data(BTRFS_I(inode), &data_reserved,
						alloc_start, bytes_to_reserve);
		अगर (ret) अणु
			unlock_extent_cached(&BTRFS_I(inode)->io_tree, lockstart,
					     lockend, &cached_state);
			जाओ out;
		पूर्ण
		ret = btrfs_pपुनः_स्मृति_file_range(inode, mode, alloc_start,
						alloc_end - alloc_start,
						i_blocksize(inode),
						offset + len, &alloc_hपूर्णांक);
		unlock_extent_cached(&BTRFS_I(inode)->io_tree, lockstart,
				     lockend, &cached_state);
		/* btrfs_pपुनः_स्मृति_file_range releases reserved space on error */
		अगर (ret) अणु
			space_reserved = false;
			जाओ out;
		पूर्ण
	पूर्ण
	ret = btrfs_fallocate_update_isize(inode, offset + len, mode);
 out:
	अगर (ret && space_reserved)
		btrfs_मुक्त_reserved_data_space(BTRFS_I(inode), data_reserved,
					       alloc_start, bytes_to_reserve);
	extent_changeset_मुक्त(data_reserved);

	वापस ret;
पूर्ण

अटल दीर्घ btrfs_fallocate(काष्ठा file *file, पूर्णांक mode,
			    loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा extent_changeset *data_reserved = शून्य;
	काष्ठा falloc_range *range;
	काष्ठा falloc_range *पंचांगp;
	काष्ठा list_head reserve_list;
	u64 cur_offset;
	u64 last_byte;
	u64 alloc_start;
	u64 alloc_end;
	u64 alloc_hपूर्णांक = 0;
	u64 locked_end;
	u64 actual_end = 0;
	काष्ठा extent_map *em;
	पूर्णांक blocksize = btrfs_inode_sectorsize(BTRFS_I(inode));
	पूर्णांक ret;

	/* Do not allow fallocate in ZONED mode */
	अगर (btrfs_is_zoned(btrfs_sb(inode->i_sb)))
		वापस -EOPNOTSUPP;

	alloc_start = round_करोwn(offset, blocksize);
	alloc_end = round_up(offset + len, blocksize);
	cur_offset = alloc_start;

	/* Make sure we aren't being give some crap mode */
	अगर (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE |
		     FALLOC_FL_ZERO_RANGE))
		वापस -EOPNOTSUPP;

	अगर (mode & FALLOC_FL_PUNCH_HOLE)
		वापस btrfs_punch_hole(inode, offset, len);

	/*
	 * Only trigger disk allocation, करोn't trigger qgroup reserve
	 *
	 * For qgroup space, it will be checked later.
	 */
	अगर (!(mode & FALLOC_FL_ZERO_RANGE)) अणु
		ret = btrfs_alloc_data_chunk_ondemand(BTRFS_I(inode),
						      alloc_end - alloc_start);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	btrfs_inode_lock(inode, BTRFS_ILOCK_MMAP);

	अगर (!(mode & FALLOC_FL_KEEP_SIZE) && offset + len > inode->i_size) अणु
		ret = inode_newsize_ok(inode, offset + len);
		अगर (ret)
			जाओ out;
	पूर्ण

	/*
	 * TODO: Move these two operations after we have checked
	 * accurate reserved space, or fallocate can still fail but
	 * with page truncated or size expanded.
	 *
	 * But that's a minor problem and won't करो much harm BTW.
	 */
	अगर (alloc_start > inode->i_size) अणु
		ret = btrfs_cont_expand(BTRFS_I(inode), i_size_पढ़ो(inode),
					alloc_start);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अगर (offset + len > inode->i_size) अणु
		/*
		 * If we are fallocating from the end of the file onward we
		 * need to zero out the end of the block अगर i_size lands in the
		 * middle of a block.
		 */
		ret = btrfs_truncate_block(BTRFS_I(inode), inode->i_size, 0, 0);
		अगर (ret)
			जाओ out;
	पूर्ण

	/*
	 * रुको क्रम ordered IO beक्रमe we have any locks.  We'll loop again
	 * below with the locks held.
	 */
	ret = btrfs_रुको_ordered_range(inode, alloc_start,
				       alloc_end - alloc_start);
	अगर (ret)
		जाओ out;

	अगर (mode & FALLOC_FL_ZERO_RANGE) अणु
		ret = btrfs_zero_range(inode, offset, len, mode);
		btrfs_inode_unlock(inode, BTRFS_ILOCK_MMAP);
		वापस ret;
	पूर्ण

	locked_end = alloc_end - 1;
	जबतक (1) अणु
		काष्ठा btrfs_ordered_extent *ordered;

		/* the extent lock is ordered inside the running
		 * transaction
		 */
		lock_extent_bits(&BTRFS_I(inode)->io_tree, alloc_start,
				 locked_end, &cached_state);
		ordered = btrfs_lookup_first_ordered_extent(BTRFS_I(inode),
							    locked_end);

		अगर (ordered &&
		    ordered->file_offset + ordered->num_bytes > alloc_start &&
		    ordered->file_offset < alloc_end) अणु
			btrfs_put_ordered_extent(ordered);
			unlock_extent_cached(&BTRFS_I(inode)->io_tree,
					     alloc_start, locked_end,
					     &cached_state);
			/*
			 * we can't रुको on the range with the transaction
			 * running or with the extent lock held
			 */
			ret = btrfs_रुको_ordered_range(inode, alloc_start,
						       alloc_end - alloc_start);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अणु
			अगर (ordered)
				btrfs_put_ordered_extent(ordered);
			अवरोध;
		पूर्ण
	पूर्ण

	/* First, check अगर we exceed the qgroup limit */
	INIT_LIST_HEAD(&reserve_list);
	जबतक (cur_offset < alloc_end) अणु
		em = btrfs_get_extent(BTRFS_I(inode), शून्य, 0, cur_offset,
				      alloc_end - cur_offset);
		अगर (IS_ERR(em)) अणु
			ret = PTR_ERR(em);
			अवरोध;
		पूर्ण
		last_byte = min(extent_map_end(em), alloc_end);
		actual_end = min_t(u64, extent_map_end(em), offset + len);
		last_byte = ALIGN(last_byte, blocksize);
		अगर (em->block_start == EXTENT_MAP_HOLE ||
		    (cur_offset >= inode->i_size &&
		     !test_bit(EXTENT_FLAG_PREALLOC, &em->flags))) अणु
			ret = add_falloc_range(&reserve_list, cur_offset,
					       last_byte - cur_offset);
			अगर (ret < 0) अणु
				मुक्त_extent_map(em);
				अवरोध;
			पूर्ण
			ret = btrfs_qgroup_reserve_data(BTRFS_I(inode),
					&data_reserved, cur_offset,
					last_byte - cur_offset);
			अगर (ret < 0) अणु
				cur_offset = last_byte;
				मुक्त_extent_map(em);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Do not need to reserve unwritten extent क्रम this
			 * range, मुक्त reserved data space first, otherwise
			 * it'll result in false ENOSPC error.
			 */
			btrfs_मुक्त_reserved_data_space(BTRFS_I(inode),
				data_reserved, cur_offset,
				last_byte - cur_offset);
		पूर्ण
		मुक्त_extent_map(em);
		cur_offset = last_byte;
	पूर्ण

	/*
	 * If ret is still 0, means we're OK to fallocate.
	 * Or just cleanup the list and निकास.
	 */
	list_क्रम_each_entry_safe(range, पंचांगp, &reserve_list, list) अणु
		अगर (!ret)
			ret = btrfs_pपुनः_स्मृति_file_range(inode, mode,
					range->start,
					range->len, i_blocksize(inode),
					offset + len, &alloc_hपूर्णांक);
		अन्यथा
			btrfs_मुक्त_reserved_data_space(BTRFS_I(inode),
					data_reserved, range->start,
					range->len);
		list_del(&range->list);
		kमुक्त(range);
	पूर्ण
	अगर (ret < 0)
		जाओ out_unlock;

	/*
	 * We didn't need to allocate any more space, but we still extended the
	 * size of the file so we need to update i_size and the inode item.
	 */
	ret = btrfs_fallocate_update_isize(inode, actual_end, mode);
out_unlock:
	unlock_extent_cached(&BTRFS_I(inode)->io_tree, alloc_start, locked_end,
			     &cached_state);
out:
	btrfs_inode_unlock(inode, BTRFS_ILOCK_MMAP);
	/* Let go of our reservation. */
	अगर (ret != 0 && !(mode & FALLOC_FL_ZERO_RANGE))
		btrfs_मुक्त_reserved_data_space(BTRFS_I(inode), data_reserved,
				cur_offset, alloc_end - cur_offset);
	extent_changeset_मुक्त(data_reserved);
	वापस ret;
पूर्ण

अटल loff_t find_desired_extent(काष्ठा btrfs_inode *inode, loff_t offset,
				  पूर्णांक whence)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा extent_map *em = शून्य;
	काष्ठा extent_state *cached_state = शून्य;
	loff_t i_size = inode->vfs_inode.i_size;
	u64 lockstart;
	u64 lockend;
	u64 start;
	u64 len;
	पूर्णांक ret = 0;

	अगर (i_size == 0 || offset >= i_size)
		वापस -ENXIO;

	/*
	 * offset can be negative, in this हाल we start finding DATA/HOLE from
	 * the very start of the file.
	 */
	start = max_t(loff_t, 0, offset);

	lockstart = round_करोwn(start, fs_info->sectorsize);
	lockend = round_up(i_size, fs_info->sectorsize);
	अगर (lockend <= lockstart)
		lockend = lockstart + fs_info->sectorsize;
	lockend--;
	len = lockend - lockstart + 1;

	lock_extent_bits(&inode->io_tree, lockstart, lockend, &cached_state);

	जबतक (start < i_size) अणु
		em = btrfs_get_extent_fiemap(inode, start, len);
		अगर (IS_ERR(em)) अणु
			ret = PTR_ERR(em);
			em = शून्य;
			अवरोध;
		पूर्ण

		अगर (whence == SEEK_HOLE &&
		    (em->block_start == EXTENT_MAP_HOLE ||
		     test_bit(EXTENT_FLAG_PREALLOC, &em->flags)))
			अवरोध;
		अन्यथा अगर (whence == SEEK_DATA &&
			   (em->block_start != EXTENT_MAP_HOLE &&
			    !test_bit(EXTENT_FLAG_PREALLOC, &em->flags)))
			अवरोध;

		start = em->start + em->len;
		मुक्त_extent_map(em);
		em = शून्य;
		cond_resched();
	पूर्ण
	मुक्त_extent_map(em);
	unlock_extent_cached(&inode->io_tree, lockstart, lockend,
			     &cached_state);
	अगर (ret) अणु
		offset = ret;
	पूर्ण अन्यथा अणु
		अगर (whence == SEEK_DATA && start >= i_size)
			offset = -ENXIO;
		अन्यथा
			offset = min_t(loff_t, start, i_size);
	पूर्ण

	वापस offset;
पूर्ण

अटल loff_t btrfs_file_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;

	चयन (whence) अणु
	शेष:
		वापस generic_file_llseek(file, offset, whence);
	हाल SEEK_DATA:
	हाल SEEK_HOLE:
		btrfs_inode_lock(inode, BTRFS_ILOCK_SHARED);
		offset = find_desired_extent(BTRFS_I(inode), offset, whence);
		btrfs_inode_unlock(inode, BTRFS_ILOCK_SHARED);
		अवरोध;
	पूर्ण

	अगर (offset < 0)
		वापस offset;

	वापस vfs_setpos(file, offset, inode->i_sb->s_maxbytes);
पूर्ण

अटल पूर्णांक btrfs_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	filp->f_mode |= FMODE_NOWAIT | FMODE_BUF_RASYNC;
	वापस generic_file_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक check_direct_पढ़ो(काष्ठा btrfs_fs_info *fs_info,
			     स्थिर काष्ठा iov_iter *iter, loff_t offset)
अणु
	पूर्णांक ret;
	पूर्णांक i, seg;

	ret = check_direct_IO(fs_info, iter, offset);
	अगर (ret < 0)
		वापस ret;

	अगर (!iter_is_iovec(iter))
		वापस 0;

	क्रम (seg = 0; seg < iter->nr_segs; seg++)
		क्रम (i = seg + 1; i < iter->nr_segs; i++)
			अगर (iter->iov[seg].iov_base == iter->iov[i].iov_base)
				वापस -EINVAL;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार btrfs_direct_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	sमाप_प्रकार ret;

	अगर (check_direct_पढ़ो(btrfs_sb(inode->i_sb), to, iocb->ki_pos))
		वापस 0;

	btrfs_inode_lock(inode, BTRFS_ILOCK_SHARED);
	ret = iomap_dio_rw(iocb, to, &btrfs_dio_iomap_ops, &btrfs_dio_ops, 0);
	btrfs_inode_unlock(inode, BTRFS_ILOCK_SHARED);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार btrfs_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	sमाप_प्रकार ret = 0;

	अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
		ret = btrfs_direct_पढ़ो(iocb, to);
		अगर (ret < 0 || !iov_iter_count(to) ||
		    iocb->ki_pos >= i_size_पढ़ो(file_inode(iocb->ki_filp)))
			वापस ret;
	पूर्ण

	वापस filemap_पढ़ो(iocb, to, ret);
पूर्ण

स्थिर काष्ठा file_operations btrfs_file_operations = अणु
	.llseek		= btrfs_file_llseek,
	.पढ़ो_iter      = btrfs_file_पढ़ो_iter,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.ग_लिखो_iter	= btrfs_file_ग_लिखो_iter,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.mmap		= btrfs_file_mmap,
	.खोलो		= btrfs_file_खोलो,
	.release	= btrfs_release_file,
	.fsync		= btrfs_sync_file,
	.fallocate	= btrfs_fallocate,
	.unlocked_ioctl	= btrfs_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= btrfs_compat_ioctl,
#पूर्ण_अगर
	.remap_file_range = btrfs_remap_file_range,
पूर्ण;

व्योम __cold btrfs_स्वतः_defrag_निकास(व्योम)
अणु
	kmem_cache_destroy(btrfs_inode_defrag_cachep);
पूर्ण

पूर्णांक __init btrfs_स्वतः_defrag_init(व्योम)
अणु
	btrfs_inode_defrag_cachep = kmem_cache_create("btrfs_inode_defrag",
					माप(काष्ठा inode_defrag), 0,
					SLAB_MEM_SPREAD,
					शून्य);
	अगर (!btrfs_inode_defrag_cachep)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक btrfs_fdataग_लिखो_range(काष्ठा inode *inode, loff_t start, loff_t end)
अणु
	पूर्णांक ret;

	/*
	 * So with compression we will find and lock a dirty page and clear the
	 * first one as dirty, setup an async extent, and immediately वापस
	 * with the entire range locked but with nobody actually marked with
	 * ग_लिखोback.  So we can't just filemap_ग_लिखो_and_रुको_range() and
	 * expect it to work since it will just kick off a thपढ़ो to करो the
	 * actual work.  So we need to call filemap_fdataग_लिखो_range _again_
	 * since it will रुको on the page lock, which won't be unlocked until
	 * after the pages have been marked as ग_लिखोback and so we're good to go
	 * from there.  We have to करो this otherwise we'll miss the ordered
	 * extents and that results in badness.  Please Josef, करो not think you
	 * know better and pull this out at some poपूर्णांक in the future, it is
	 * right and you are wrong.
	 */
	ret = filemap_fdataग_लिखो_range(inode->i_mapping, start, end);
	अगर (!ret && test_bit(BTRFS_INODE_HAS_ASYNC_EXTENT,
			     &BTRFS_I(inode)->runसमय_flags))
		ret = filemap_fdataग_लिखो_range(inode->i_mapping, start, end);

	वापस ret;
पूर्ण
