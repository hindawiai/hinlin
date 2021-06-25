<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/sched/mm.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "transaction.h"
#समावेश "btrfs_inode.h"
#समावेश "extent_io.h"
#समावेश "disk-io.h"
#समावेश "compression.h"
#समावेश "delalloc-space.h"
#समावेश "qgroup.h"

अटल काष्ठा kmem_cache *btrfs_ordered_extent_cache;

अटल u64 entry_end(काष्ठा btrfs_ordered_extent *entry)
अणु
	अगर (entry->file_offset + entry->num_bytes < entry->file_offset)
		वापस (u64)-1;
	वापस entry->file_offset + entry->num_bytes;
पूर्ण

/* वापसs शून्य अगर the insertion worked, or it वापसs the node it did find
 * in the tree
 */
अटल काष्ठा rb_node *tree_insert(काष्ठा rb_root *root, u64 file_offset,
				   काष्ठा rb_node *node)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा btrfs_ordered_extent *entry;

	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा btrfs_ordered_extent, rb_node);

		अगर (file_offset < entry->file_offset)
			p = &(*p)->rb_left;
		अन्यथा अगर (file_offset >= entry_end(entry))
			p = &(*p)->rb_right;
		अन्यथा
			वापस parent;
	पूर्ण

	rb_link_node(node, parent, p);
	rb_insert_color(node, root);
	वापस शून्य;
पूर्ण

/*
 * look क्रम a given offset in the tree, and अगर it can't be found वापस the
 * first lesser offset
 */
अटल काष्ठा rb_node *__tree_search(काष्ठा rb_root *root, u64 file_offset,
				     काष्ठा rb_node **prev_ret)
अणु
	काष्ठा rb_node *n = root->rb_node;
	काष्ठा rb_node *prev = शून्य;
	काष्ठा rb_node *test;
	काष्ठा btrfs_ordered_extent *entry;
	काष्ठा btrfs_ordered_extent *prev_entry = शून्य;

	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा btrfs_ordered_extent, rb_node);
		prev = n;
		prev_entry = entry;

		अगर (file_offset < entry->file_offset)
			n = n->rb_left;
		अन्यथा अगर (file_offset >= entry_end(entry))
			n = n->rb_right;
		अन्यथा
			वापस n;
	पूर्ण
	अगर (!prev_ret)
		वापस शून्य;

	जबतक (prev && file_offset >= entry_end(prev_entry)) अणु
		test = rb_next(prev);
		अगर (!test)
			अवरोध;
		prev_entry = rb_entry(test, काष्ठा btrfs_ordered_extent,
				      rb_node);
		अगर (file_offset < entry_end(prev_entry))
			अवरोध;

		prev = test;
	पूर्ण
	अगर (prev)
		prev_entry = rb_entry(prev, काष्ठा btrfs_ordered_extent,
				      rb_node);
	जबतक (prev && file_offset < entry_end(prev_entry)) अणु
		test = rb_prev(prev);
		अगर (!test)
			अवरोध;
		prev_entry = rb_entry(test, काष्ठा btrfs_ordered_extent,
				      rb_node);
		prev = test;
	पूर्ण
	*prev_ret = prev;
	वापस शून्य;
पूर्ण

अटल पूर्णांक range_overlaps(काष्ठा btrfs_ordered_extent *entry, u64 file_offset,
			  u64 len)
अणु
	अगर (file_offset + len <= entry->file_offset ||
	    entry->file_offset + entry->num_bytes <= file_offset)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * look find the first ordered काष्ठा that has this offset, otherwise
 * the first one less than this offset
 */
अटल अंतरभूत काष्ठा rb_node *tree_search(काष्ठा btrfs_ordered_inode_tree *tree,
					  u64 file_offset)
अणु
	काष्ठा rb_root *root = &tree->tree;
	काष्ठा rb_node *prev = शून्य;
	काष्ठा rb_node *ret;
	काष्ठा btrfs_ordered_extent *entry;

	अगर (tree->last) अणु
		entry = rb_entry(tree->last, काष्ठा btrfs_ordered_extent,
				 rb_node);
		अगर (in_range(file_offset, entry->file_offset, entry->num_bytes))
			वापस tree->last;
	पूर्ण
	ret = __tree_search(root, file_offset, &prev);
	अगर (!ret)
		ret = prev;
	अगर (ret)
		tree->last = ret;
	वापस ret;
पूर्ण

/*
 * Allocate and add a new ordered_extent पूर्णांकo the per-inode tree.
 *
 * The tree is given a single reference on the ordered extent that was
 * inserted.
 */
अटल पूर्णांक __btrfs_add_ordered_extent(काष्ठा btrfs_inode *inode, u64 file_offset,
				      u64 disk_bytenr, u64 num_bytes,
				      u64 disk_num_bytes, पूर्णांक type, पूर्णांक dio,
				      पूर्णांक compress_type)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_ordered_inode_tree *tree = &inode->ordered_tree;
	काष्ठा rb_node *node;
	काष्ठा btrfs_ordered_extent *entry;
	पूर्णांक ret;

	अगर (type == BTRFS_ORDERED_NOCOW || type == BTRFS_ORDERED_PREALLOC) अणु
		/* For nocow ग_लिखो, we can release the qgroup rsv right now */
		ret = btrfs_qgroup_मुक्त_data(inode, शून्य, file_offset, num_bytes);
		अगर (ret < 0)
			वापस ret;
		ret = 0;
	पूर्ण अन्यथा अणु
		/*
		 * The ordered extent has reserved qgroup space, release now
		 * and pass the reserved number क्रम qgroup_record to मुक्त.
		 */
		ret = btrfs_qgroup_release_data(inode, file_offset, num_bytes);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	entry = kmem_cache_zalloc(btrfs_ordered_extent_cache, GFP_NOFS);
	अगर (!entry)
		वापस -ENOMEM;

	entry->file_offset = file_offset;
	entry->disk_bytenr = disk_bytenr;
	entry->num_bytes = num_bytes;
	entry->disk_num_bytes = disk_num_bytes;
	entry->bytes_left = num_bytes;
	entry->inode = igrab(&inode->vfs_inode);
	entry->compress_type = compress_type;
	entry->truncated_len = (u64)-1;
	entry->qgroup_rsv = ret;
	entry->physical = (u64)-1;
	entry->disk = शून्य;
	entry->partno = (u8)-1;

	ASSERT(type == BTRFS_ORDERED_REGULAR ||
	       type == BTRFS_ORDERED_NOCOW ||
	       type == BTRFS_ORDERED_PREALLOC ||
	       type == BTRFS_ORDERED_COMPRESSED);
	set_bit(type, &entry->flags);

	percpu_counter_add_batch(&fs_info->ordered_bytes, num_bytes,
				 fs_info->delalloc_batch);

	अगर (dio)
		set_bit(BTRFS_ORDERED_सूचीECT, &entry->flags);

	/* one ref क्रम the tree */
	refcount_set(&entry->refs, 1);
	init_रुकोqueue_head(&entry->रुको);
	INIT_LIST_HEAD(&entry->list);
	INIT_LIST_HEAD(&entry->log_list);
	INIT_LIST_HEAD(&entry->root_extent_list);
	INIT_LIST_HEAD(&entry->work_list);
	init_completion(&entry->completion);

	trace_btrfs_ordered_extent_add(inode, entry);

	spin_lock_irq(&tree->lock);
	node = tree_insert(&tree->tree, file_offset,
			   &entry->rb_node);
	अगर (node)
		btrfs_panic(fs_info, -EEXIST,
				"inconsistency in ordered tree at offset %llu",
				file_offset);
	spin_unlock_irq(&tree->lock);

	spin_lock(&root->ordered_extent_lock);
	list_add_tail(&entry->root_extent_list,
		      &root->ordered_extents);
	root->nr_ordered_extents++;
	अगर (root->nr_ordered_extents == 1) अणु
		spin_lock(&fs_info->ordered_root_lock);
		BUG_ON(!list_empty(&root->ordered_root));
		list_add_tail(&root->ordered_root, &fs_info->ordered_roots);
		spin_unlock(&fs_info->ordered_root_lock);
	पूर्ण
	spin_unlock(&root->ordered_extent_lock);

	/*
	 * We करोn't need the count_max_extents here, we can assume that all of
	 * that work has been करोne at higher layers, so this is truly the
	 * smallest the extent is going to get.
	 */
	spin_lock(&inode->lock);
	btrfs_mod_outstanding_extents(inode, 1);
	spin_unlock(&inode->lock);

	वापस 0;
पूर्ण

पूर्णांक btrfs_add_ordered_extent(काष्ठा btrfs_inode *inode, u64 file_offset,
			     u64 disk_bytenr, u64 num_bytes, u64 disk_num_bytes,
			     पूर्णांक type)
अणु
	ASSERT(type == BTRFS_ORDERED_REGULAR ||
	       type == BTRFS_ORDERED_NOCOW ||
	       type == BTRFS_ORDERED_PREALLOC);
	वापस __btrfs_add_ordered_extent(inode, file_offset, disk_bytenr,
					  num_bytes, disk_num_bytes, type, 0,
					  BTRFS_COMPRESS_NONE);
पूर्ण

पूर्णांक btrfs_add_ordered_extent_dio(काष्ठा btrfs_inode *inode, u64 file_offset,
				 u64 disk_bytenr, u64 num_bytes,
				 u64 disk_num_bytes, पूर्णांक type)
अणु
	ASSERT(type == BTRFS_ORDERED_REGULAR ||
	       type == BTRFS_ORDERED_NOCOW ||
	       type == BTRFS_ORDERED_PREALLOC);
	वापस __btrfs_add_ordered_extent(inode, file_offset, disk_bytenr,
					  num_bytes, disk_num_bytes, type, 1,
					  BTRFS_COMPRESS_NONE);
पूर्ण

पूर्णांक btrfs_add_ordered_extent_compress(काष्ठा btrfs_inode *inode, u64 file_offset,
				      u64 disk_bytenr, u64 num_bytes,
				      u64 disk_num_bytes, पूर्णांक compress_type)
अणु
	ASSERT(compress_type != BTRFS_COMPRESS_NONE);
	वापस __btrfs_add_ordered_extent(inode, file_offset, disk_bytenr,
					  num_bytes, disk_num_bytes,
					  BTRFS_ORDERED_COMPRESSED, 0,
					  compress_type);
पूर्ण

/*
 * Add a काष्ठा btrfs_ordered_sum पूर्णांकo the list of checksums to be inserted
 * when an ordered extent is finished.  If the list covers more than one
 * ordered extent, it is split across multiples.
 */
व्योम btrfs_add_ordered_sum(काष्ठा btrfs_ordered_extent *entry,
			   काष्ठा btrfs_ordered_sum *sum)
अणु
	काष्ठा btrfs_ordered_inode_tree *tree;

	tree = &BTRFS_I(entry->inode)->ordered_tree;
	spin_lock_irq(&tree->lock);
	list_add_tail(&sum->list, &entry->list);
	spin_unlock_irq(&tree->lock);
पूर्ण

/*
 * Finish IO क्रम one ordered extent across a given range.  The range can
 * contain several ordered extents.
 *
 * @found_ret:	 Return the finished ordered extent
 * @file_offset: File offset क्रम the finished IO
 * 		 Will also be updated to one byte past the range that is
 * 		 recordered as finished. This allows caller to walk क्रमward.
 * @io_size:	 Length of the finish IO range
 * @uptodate:	 If the IO finished without problem
 *
 * Return true अगर any ordered extent is finished in the range, and update
 * @found_ret and @file_offset.
 * Return false otherwise.
 *
 * NOTE: Although The range can cross multiple ordered extents, only one
 * ordered extent will be updated during one call. The caller is responsible to
 * iterate all ordered extents in the range.
 */
bool btrfs_dec_test_first_ordered_pending(काष्ठा btrfs_inode *inode,
				   काष्ठा btrfs_ordered_extent **finished_ret,
				   u64 *file_offset, u64 io_size, पूर्णांक uptodate)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_ordered_inode_tree *tree = &inode->ordered_tree;
	काष्ठा rb_node *node;
	काष्ठा btrfs_ordered_extent *entry = शून्य;
	bool finished = false;
	अचिन्हित दीर्घ flags;
	u64 dec_end;
	u64 dec_start;
	u64 to_dec;

	spin_lock_irqsave(&tree->lock, flags);
	node = tree_search(tree, *file_offset);
	अगर (!node)
		जाओ out;

	entry = rb_entry(node, काष्ठा btrfs_ordered_extent, rb_node);
	अगर (!in_range(*file_offset, entry->file_offset, entry->num_bytes))
		जाओ out;

	dec_start = max(*file_offset, entry->file_offset);
	dec_end = min(*file_offset + io_size,
		      entry->file_offset + entry->num_bytes);
	*file_offset = dec_end;
	अगर (dec_start > dec_end) अणु
		btrfs_crit(fs_info, "bad ordering dec_start %llu end %llu",
			   dec_start, dec_end);
	पूर्ण
	to_dec = dec_end - dec_start;
	अगर (to_dec > entry->bytes_left) अणु
		btrfs_crit(fs_info,
			   "bad ordered accounting left %llu size %llu",
			   entry->bytes_left, to_dec);
	पूर्ण
	entry->bytes_left -= to_dec;
	अगर (!uptodate)
		set_bit(BTRFS_ORDERED_IOERR, &entry->flags);

	अगर (entry->bytes_left == 0) अणु
		/*
		 * Ensure only one caller can set the flag and finished_ret
		 * accordingly
		 */
		finished = !test_and_set_bit(BTRFS_ORDERED_IO_DONE, &entry->flags);
		/* test_and_set_bit implies a barrier */
		cond_wake_up_nomb(&entry->रुको);
	पूर्ण
out:
	अगर (finished && finished_ret && entry) अणु
		*finished_ret = entry;
		refcount_inc(&entry->refs);
	पूर्ण
	spin_unlock_irqrestore(&tree->lock, flags);
	वापस finished;
पूर्ण

/*
 * Finish IO क्रम one ordered extent across a given range.  The range can only
 * contain one ordered extent.
 *
 * @cached:	 The cached ordered extent. If not शून्य, we can skip the tree
 *               search and use the ordered extent directly.
 * 		 Will be also used to store the finished ordered extent.
 * @file_offset: File offset क्रम the finished IO
 * @io_size:	 Length of the finish IO range
 * @uptodate:	 If the IO finishes without problem
 *
 * Return true अगर the ordered extent is finished in the range, and update
 * @cached.
 * Return false otherwise.
 *
 * NOTE: The range can NOT cross multiple ordered extents.
 * Thus caller should ensure the range करोesn't cross ordered extents.
 */
bool btrfs_dec_test_ordered_pending(काष्ठा btrfs_inode *inode,
				    काष्ठा btrfs_ordered_extent **cached,
				    u64 file_offset, u64 io_size, पूर्णांक uptodate)
अणु
	काष्ठा btrfs_ordered_inode_tree *tree = &inode->ordered_tree;
	काष्ठा rb_node *node;
	काष्ठा btrfs_ordered_extent *entry = शून्य;
	अचिन्हित दीर्घ flags;
	bool finished = false;

	spin_lock_irqsave(&tree->lock, flags);
	अगर (cached && *cached) अणु
		entry = *cached;
		जाओ have_entry;
	पूर्ण

	node = tree_search(tree, file_offset);
	अगर (!node)
		जाओ out;

	entry = rb_entry(node, काष्ठा btrfs_ordered_extent, rb_node);
have_entry:
	अगर (!in_range(file_offset, entry->file_offset, entry->num_bytes))
		जाओ out;

	अगर (io_size > entry->bytes_left)
		btrfs_crit(inode->root->fs_info,
			   "bad ordered accounting left %llu size %llu",
		       entry->bytes_left, io_size);

	entry->bytes_left -= io_size;
	अगर (!uptodate)
		set_bit(BTRFS_ORDERED_IOERR, &entry->flags);

	अगर (entry->bytes_left == 0) अणु
		/*
		 * Ensure only one caller can set the flag and finished_ret
		 * accordingly
		 */
		finished = !test_and_set_bit(BTRFS_ORDERED_IO_DONE, &entry->flags);
		/* test_and_set_bit implies a barrier */
		cond_wake_up_nomb(&entry->रुको);
	पूर्ण
out:
	अगर (finished && cached && entry) अणु
		*cached = entry;
		refcount_inc(&entry->refs);
	पूर्ण
	spin_unlock_irqrestore(&tree->lock, flags);
	वापस finished;
पूर्ण

/*
 * used to drop a reference on an ordered extent.  This will मुक्त
 * the extent अगर the last reference is dropped
 */
व्योम btrfs_put_ordered_extent(काष्ठा btrfs_ordered_extent *entry)
अणु
	काष्ठा list_head *cur;
	काष्ठा btrfs_ordered_sum *sum;

	trace_btrfs_ordered_extent_put(BTRFS_I(entry->inode), entry);

	अगर (refcount_dec_and_test(&entry->refs)) अणु
		ASSERT(list_empty(&entry->root_extent_list));
		ASSERT(list_empty(&entry->log_list));
		ASSERT(RB_EMPTY_NODE(&entry->rb_node));
		अगर (entry->inode)
			btrfs_add_delayed_iput(entry->inode);
		जबतक (!list_empty(&entry->list)) अणु
			cur = entry->list.next;
			sum = list_entry(cur, काष्ठा btrfs_ordered_sum, list);
			list_del(&sum->list);
			kvमुक्त(sum);
		पूर्ण
		kmem_cache_मुक्त(btrfs_ordered_extent_cache, entry);
	पूर्ण
पूर्ण

/*
 * हटाओ an ordered extent from the tree.  No references are dropped
 * and रुकोers are woken up.
 */
व्योम btrfs_हटाओ_ordered_extent(काष्ठा btrfs_inode *btrfs_inode,
				 काष्ठा btrfs_ordered_extent *entry)
अणु
	काष्ठा btrfs_ordered_inode_tree *tree;
	काष्ठा btrfs_root *root = btrfs_inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा rb_node *node;
	bool pending;

	/* This is paired with btrfs_add_ordered_extent. */
	spin_lock(&btrfs_inode->lock);
	btrfs_mod_outstanding_extents(btrfs_inode, -1);
	spin_unlock(&btrfs_inode->lock);
	अगर (root != fs_info->tree_root)
		btrfs_delalloc_release_metadata(btrfs_inode, entry->num_bytes,
						false);

	percpu_counter_add_batch(&fs_info->ordered_bytes, -entry->num_bytes,
				 fs_info->delalloc_batch);

	tree = &btrfs_inode->ordered_tree;
	spin_lock_irq(&tree->lock);
	node = &entry->rb_node;
	rb_erase(node, &tree->tree);
	RB_CLEAR_NODE(node);
	अगर (tree->last == node)
		tree->last = शून्य;
	set_bit(BTRFS_ORDERED_COMPLETE, &entry->flags);
	pending = test_and_clear_bit(BTRFS_ORDERED_PENDING, &entry->flags);
	spin_unlock_irq(&tree->lock);

	/*
	 * The current running transaction is रुकोing on us, we need to let it
	 * know that we're complete and wake it up.
	 */
	अगर (pending) अणु
		काष्ठा btrfs_transaction *trans;

		/*
		 * The checks क्रम trans are just a क्रमmality, it should be set,
		 * but अगर it isn't we don't want to deref/निश्चित under the spin
		 * lock, so be nice and check अगर trans is set, but ASSERT() so
		 * अगर it isn't set a developer will notice.
		 */
		spin_lock(&fs_info->trans_lock);
		trans = fs_info->running_transaction;
		अगर (trans)
			refcount_inc(&trans->use_count);
		spin_unlock(&fs_info->trans_lock);

		ASSERT(trans);
		अगर (trans) अणु
			अगर (atomic_dec_and_test(&trans->pending_ordered))
				wake_up(&trans->pending_रुको);
			btrfs_put_transaction(trans);
		पूर्ण
	पूर्ण

	spin_lock(&root->ordered_extent_lock);
	list_del_init(&entry->root_extent_list);
	root->nr_ordered_extents--;

	trace_btrfs_ordered_extent_हटाओ(btrfs_inode, entry);

	अगर (!root->nr_ordered_extents) अणु
		spin_lock(&fs_info->ordered_root_lock);
		BUG_ON(list_empty(&root->ordered_root));
		list_del_init(&root->ordered_root);
		spin_unlock(&fs_info->ordered_root_lock);
	पूर्ण
	spin_unlock(&root->ordered_extent_lock);
	wake_up(&entry->रुको);
पूर्ण

अटल व्योम btrfs_run_ordered_extent_work(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_ordered_extent *ordered;

	ordered = container_of(work, काष्ठा btrfs_ordered_extent, flush_work);
	btrfs_start_ordered_extent(ordered, 1);
	complete(&ordered->completion);
पूर्ण

/*
 * रुको क्रम all the ordered extents in a root.  This is करोne when balancing
 * space between drives.
 */
u64 btrfs_रुको_ordered_extents(काष्ठा btrfs_root *root, u64 nr,
			       स्थिर u64 range_start, स्थिर u64 range_len)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	LIST_HEAD(splice);
	LIST_HEAD(skipped);
	LIST_HEAD(works);
	काष्ठा btrfs_ordered_extent *ordered, *next;
	u64 count = 0;
	स्थिर u64 range_end = range_start + range_len;

	mutex_lock(&root->ordered_extent_mutex);
	spin_lock(&root->ordered_extent_lock);
	list_splice_init(&root->ordered_extents, &splice);
	जबतक (!list_empty(&splice) && nr) अणु
		ordered = list_first_entry(&splice, काष्ठा btrfs_ordered_extent,
					   root_extent_list);

		अगर (range_end <= ordered->disk_bytenr ||
		    ordered->disk_bytenr + ordered->disk_num_bytes <= range_start) अणु
			list_move_tail(&ordered->root_extent_list, &skipped);
			cond_resched_lock(&root->ordered_extent_lock);
			जारी;
		पूर्ण

		list_move_tail(&ordered->root_extent_list,
			       &root->ordered_extents);
		refcount_inc(&ordered->refs);
		spin_unlock(&root->ordered_extent_lock);

		btrfs_init_work(&ordered->flush_work,
				btrfs_run_ordered_extent_work, शून्य, शून्य);
		list_add_tail(&ordered->work_list, &works);
		btrfs_queue_work(fs_info->flush_workers, &ordered->flush_work);

		cond_resched();
		spin_lock(&root->ordered_extent_lock);
		अगर (nr != U64_MAX)
			nr--;
		count++;
	पूर्ण
	list_splice_tail(&skipped, &root->ordered_extents);
	list_splice_tail(&splice, &root->ordered_extents);
	spin_unlock(&root->ordered_extent_lock);

	list_क्रम_each_entry_safe(ordered, next, &works, work_list) अणु
		list_del_init(&ordered->work_list);
		रुको_क्रम_completion(&ordered->completion);
		btrfs_put_ordered_extent(ordered);
		cond_resched();
	पूर्ण
	mutex_unlock(&root->ordered_extent_mutex);

	वापस count;
पूर्ण

व्योम btrfs_रुको_ordered_roots(काष्ठा btrfs_fs_info *fs_info, u64 nr,
			     स्थिर u64 range_start, स्थिर u64 range_len)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा list_head splice;
	u64 करोne;

	INIT_LIST_HEAD(&splice);

	mutex_lock(&fs_info->ordered_operations_mutex);
	spin_lock(&fs_info->ordered_root_lock);
	list_splice_init(&fs_info->ordered_roots, &splice);
	जबतक (!list_empty(&splice) && nr) अणु
		root = list_first_entry(&splice, काष्ठा btrfs_root,
					ordered_root);
		root = btrfs_grab_root(root);
		BUG_ON(!root);
		list_move_tail(&root->ordered_root,
			       &fs_info->ordered_roots);
		spin_unlock(&fs_info->ordered_root_lock);

		करोne = btrfs_रुको_ordered_extents(root, nr,
						  range_start, range_len);
		btrfs_put_root(root);

		spin_lock(&fs_info->ordered_root_lock);
		अगर (nr != U64_MAX) अणु
			nr -= करोne;
		पूर्ण
	पूर्ण
	list_splice_tail(&splice, &fs_info->ordered_roots);
	spin_unlock(&fs_info->ordered_root_lock);
	mutex_unlock(&fs_info->ordered_operations_mutex);
पूर्ण

/*
 * Used to start IO or रुको क्रम a given ordered extent to finish.
 *
 * If रुको is one, this effectively रुकोs on page ग_लिखोback क्रम all the pages
 * in the extent, and it रुकोs on the io completion code to insert
 * metadata पूर्णांकo the btree corresponding to the extent
 */
व्योम btrfs_start_ordered_extent(काष्ठा btrfs_ordered_extent *entry, पूर्णांक रुको)
अणु
	u64 start = entry->file_offset;
	u64 end = start + entry->num_bytes - 1;
	काष्ठा btrfs_inode *inode = BTRFS_I(entry->inode);

	trace_btrfs_ordered_extent_start(inode, entry);

	/*
	 * pages in the range can be dirty, clean or ग_लिखोback.  We
	 * start IO on any dirty ones so the रुको करोesn't stall रुकोing
	 * क्रम the flusher thपढ़ो to find them
	 */
	अगर (!test_bit(BTRFS_ORDERED_सूचीECT, &entry->flags))
		filemap_fdataग_लिखो_range(inode->vfs_inode.i_mapping, start, end);
	अगर (रुको) अणु
		रुको_event(entry->रुको, test_bit(BTRFS_ORDERED_COMPLETE,
						 &entry->flags));
	पूर्ण
पूर्ण

/*
 * Used to रुको on ordered extents across a large range of bytes.
 */
पूर्णांक btrfs_रुको_ordered_range(काष्ठा inode *inode, u64 start, u64 len)
अणु
	पूर्णांक ret = 0;
	पूर्णांक ret_wb = 0;
	u64 end;
	u64 orig_end;
	काष्ठा btrfs_ordered_extent *ordered;

	अगर (start + len < start) अणु
		orig_end = INT_LIMIT(loff_t);
	पूर्ण अन्यथा अणु
		orig_end = start + len - 1;
		अगर (orig_end > INT_LIMIT(loff_t))
			orig_end = INT_LIMIT(loff_t);
	पूर्ण

	/* start IO across the range first to instantiate any delalloc
	 * extents
	 */
	ret = btrfs_fdataग_लिखो_range(inode, start, orig_end);
	अगर (ret)
		वापस ret;

	/*
	 * If we have a ग_लिखोback error करोn't वापस immediately. Wait first
	 * क्रम any ordered extents that haven't completed yet. This is to make
	 * sure no one can dirty the same page ranges and call ग_लिखोpages()
	 * beक्रमe the ordered extents complete - to aव्योम failures (-EEXIST)
	 * when adding the new ordered extents to the ordered tree.
	 */
	ret_wb = filemap_fdataरुको_range(inode->i_mapping, start, orig_end);

	end = orig_end;
	जबतक (1) अणु
		ordered = btrfs_lookup_first_ordered_extent(BTRFS_I(inode), end);
		अगर (!ordered)
			अवरोध;
		अगर (ordered->file_offset > orig_end) अणु
			btrfs_put_ordered_extent(ordered);
			अवरोध;
		पूर्ण
		अगर (ordered->file_offset + ordered->num_bytes <= start) अणु
			btrfs_put_ordered_extent(ordered);
			अवरोध;
		पूर्ण
		btrfs_start_ordered_extent(ordered, 1);
		end = ordered->file_offset;
		/*
		 * If the ordered extent had an error save the error but करोn't
		 * निकास without रुकोing first क्रम all other ordered extents in
		 * the range to complete.
		 */
		अगर (test_bit(BTRFS_ORDERED_IOERR, &ordered->flags))
			ret = -EIO;
		btrfs_put_ordered_extent(ordered);
		अगर (end == 0 || end == start)
			अवरोध;
		end--;
	पूर्ण
	वापस ret_wb ? ret_wb : ret;
पूर्ण

/*
 * find an ordered extent corresponding to file_offset.  वापस शून्य अगर
 * nothing is found, otherwise take a reference on the extent and वापस it
 */
काष्ठा btrfs_ordered_extent *btrfs_lookup_ordered_extent(काष्ठा btrfs_inode *inode,
							 u64 file_offset)
अणु
	काष्ठा btrfs_ordered_inode_tree *tree;
	काष्ठा rb_node *node;
	काष्ठा btrfs_ordered_extent *entry = शून्य;
	अचिन्हित दीर्घ flags;

	tree = &inode->ordered_tree;
	spin_lock_irqsave(&tree->lock, flags);
	node = tree_search(tree, file_offset);
	अगर (!node)
		जाओ out;

	entry = rb_entry(node, काष्ठा btrfs_ordered_extent, rb_node);
	अगर (!in_range(file_offset, entry->file_offset, entry->num_bytes))
		entry = शून्य;
	अगर (entry)
		refcount_inc(&entry->refs);
out:
	spin_unlock_irqrestore(&tree->lock, flags);
	वापस entry;
पूर्ण

/* Since the DIO code tries to lock a wide area we need to look क्रम any ordered
 * extents that exist in the range, rather than just the start of the range.
 */
काष्ठा btrfs_ordered_extent *btrfs_lookup_ordered_range(
		काष्ठा btrfs_inode *inode, u64 file_offset, u64 len)
अणु
	काष्ठा btrfs_ordered_inode_tree *tree;
	काष्ठा rb_node *node;
	काष्ठा btrfs_ordered_extent *entry = शून्य;

	tree = &inode->ordered_tree;
	spin_lock_irq(&tree->lock);
	node = tree_search(tree, file_offset);
	अगर (!node) अणु
		node = tree_search(tree, file_offset + len);
		अगर (!node)
			जाओ out;
	पूर्ण

	जबतक (1) अणु
		entry = rb_entry(node, काष्ठा btrfs_ordered_extent, rb_node);
		अगर (range_overlaps(entry, file_offset, len))
			अवरोध;

		अगर (entry->file_offset >= file_offset + len) अणु
			entry = शून्य;
			अवरोध;
		पूर्ण
		entry = शून्य;
		node = rb_next(node);
		अगर (!node)
			अवरोध;
	पूर्ण
out:
	अगर (entry)
		refcount_inc(&entry->refs);
	spin_unlock_irq(&tree->lock);
	वापस entry;
पूर्ण

/*
 * Adds all ordered extents to the given list. The list ends up sorted by the
 * file_offset of the ordered extents.
 */
व्योम btrfs_get_ordered_extents_क्रम_logging(काष्ठा btrfs_inode *inode,
					   काष्ठा list_head *list)
अणु
	काष्ठा btrfs_ordered_inode_tree *tree = &inode->ordered_tree;
	काष्ठा rb_node *n;

	ASSERT(inode_is_locked(&inode->vfs_inode));

	spin_lock_irq(&tree->lock);
	क्रम (n = rb_first(&tree->tree); n; n = rb_next(n)) अणु
		काष्ठा btrfs_ordered_extent *ordered;

		ordered = rb_entry(n, काष्ठा btrfs_ordered_extent, rb_node);

		अगर (test_bit(BTRFS_ORDERED_LOGGED, &ordered->flags))
			जारी;

		ASSERT(list_empty(&ordered->log_list));
		list_add_tail(&ordered->log_list, list);
		refcount_inc(&ordered->refs);
	पूर्ण
	spin_unlock_irq(&tree->lock);
पूर्ण

/*
 * lookup and वापस any extent beक्रमe 'file_offset'.  शून्य is वापसed
 * अगर none is found
 */
काष्ठा btrfs_ordered_extent *
btrfs_lookup_first_ordered_extent(काष्ठा btrfs_inode *inode, u64 file_offset)
अणु
	काष्ठा btrfs_ordered_inode_tree *tree;
	काष्ठा rb_node *node;
	काष्ठा btrfs_ordered_extent *entry = शून्य;

	tree = &inode->ordered_tree;
	spin_lock_irq(&tree->lock);
	node = tree_search(tree, file_offset);
	अगर (!node)
		जाओ out;

	entry = rb_entry(node, काष्ठा btrfs_ordered_extent, rb_node);
	refcount_inc(&entry->refs);
out:
	spin_unlock_irq(&tree->lock);
	वापस entry;
पूर्ण

/*
 * btrfs_flush_ordered_range - Lock the passed range and ensures all pending
 * ordered extents in it are run to completion.
 *
 * @inode:        Inode whose ordered tree is to be searched
 * @start:        Beginning of range to flush
 * @end:          Last byte of range to lock
 * @cached_state: If passed, will वापस the extent state responsible क्रम the
 * locked range. It's the caller's responsibility to मुक्त the cached state.
 *
 * This function always वापसs with the given range locked, ensuring after it's
 * called no order extent can be pending.
 */
व्योम btrfs_lock_and_flush_ordered_range(काष्ठा btrfs_inode *inode, u64 start,
					u64 end,
					काष्ठा extent_state **cached_state)
अणु
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा extent_state *cache = शून्य;
	काष्ठा extent_state **cachedp = &cache;

	अगर (cached_state)
		cachedp = cached_state;

	जबतक (1) अणु
		lock_extent_bits(&inode->io_tree, start, end, cachedp);
		ordered = btrfs_lookup_ordered_range(inode, start,
						     end - start + 1);
		अगर (!ordered) अणु
			/*
			 * If no बाह्यal cached_state has been passed then
			 * decrement the extra ref taken क्रम cachedp since we
			 * aren't exposing it outside of this function
			 */
			अगर (!cached_state)
				refcount_dec(&cache->refs);
			अवरोध;
		पूर्ण
		unlock_extent_cached(&inode->io_tree, start, end, cachedp);
		btrfs_start_ordered_extent(ordered, 1);
		btrfs_put_ordered_extent(ordered);
	पूर्ण
पूर्ण

अटल पूर्णांक clone_ordered_extent(काष्ठा btrfs_ordered_extent *ordered, u64 pos,
				u64 len)
अणु
	काष्ठा inode *inode = ordered->inode;
	u64 file_offset = ordered->file_offset + pos;
	u64 disk_bytenr = ordered->disk_bytenr + pos;
	u64 num_bytes = len;
	u64 disk_num_bytes = len;
	पूर्णांक type;
	अचिन्हित दीर्घ flags_masked = ordered->flags & ~(1 << BTRFS_ORDERED_सूचीECT);
	पूर्णांक compress_type = ordered->compress_type;
	अचिन्हित दीर्घ weight;
	पूर्णांक ret;

	weight = hweight_दीर्घ(flags_masked);
	WARN_ON_ONCE(weight > 1);
	अगर (!weight)
		type = 0;
	अन्यथा
		type = __ffs(flags_masked);

	अगर (test_bit(BTRFS_ORDERED_COMPRESSED, &ordered->flags)) अणु
		WARN_ON_ONCE(1);
		ret = btrfs_add_ordered_extent_compress(BTRFS_I(inode),
				file_offset, disk_bytenr, num_bytes,
				disk_num_bytes, compress_type);
	पूर्ण अन्यथा अगर (test_bit(BTRFS_ORDERED_सूचीECT, &ordered->flags)) अणु
		ret = btrfs_add_ordered_extent_dio(BTRFS_I(inode), file_offset,
				disk_bytenr, num_bytes, disk_num_bytes, type);
	पूर्ण अन्यथा अणु
		ret = btrfs_add_ordered_extent(BTRFS_I(inode), file_offset,
				disk_bytenr, num_bytes, disk_num_bytes, type);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक btrfs_split_ordered_extent(काष्ठा btrfs_ordered_extent *ordered, u64 pre,
				u64 post)
अणु
	काष्ठा inode *inode = ordered->inode;
	काष्ठा btrfs_ordered_inode_tree *tree = &BTRFS_I(inode)->ordered_tree;
	काष्ठा rb_node *node;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	पूर्णांक ret = 0;

	spin_lock_irq(&tree->lock);
	/* Remove from tree once */
	node = &ordered->rb_node;
	rb_erase(node, &tree->tree);
	RB_CLEAR_NODE(node);
	अगर (tree->last == node)
		tree->last = शून्य;

	ordered->file_offset += pre;
	ordered->disk_bytenr += pre;
	ordered->num_bytes -= (pre + post);
	ordered->disk_num_bytes -= (pre + post);
	ordered->bytes_left -= (pre + post);

	/* Re-insert the node */
	node = tree_insert(&tree->tree, ordered->file_offset, &ordered->rb_node);
	अगर (node)
		btrfs_panic(fs_info, -EEXIST,
			"zoned: inconsistency in ordered tree at offset %llu",
			    ordered->file_offset);

	spin_unlock_irq(&tree->lock);

	अगर (pre)
		ret = clone_ordered_extent(ordered, 0, pre);
	अगर (ret == 0 && post)
		ret = clone_ordered_extent(ordered, pre + ordered->disk_num_bytes,
					   post);

	वापस ret;
पूर्ण

पूर्णांक __init ordered_data_init(व्योम)
अणु
	btrfs_ordered_extent_cache = kmem_cache_create("btrfs_ordered_extent",
				     माप(काष्ठा btrfs_ordered_extent), 0,
				     SLAB_MEM_SPREAD,
				     शून्य);
	अगर (!btrfs_ordered_extent_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम __cold ordered_data_निकास(व्योम)
अणु
	kmem_cache_destroy(btrfs_ordered_extent_cache);
पूर्ण
