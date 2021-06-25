<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/uuid.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "locking.h"
#समावेश "tree-log.h"
#समावेश "volumes.h"
#समावेश "dev-replace.h"
#समावेश "qgroup.h"
#समावेश "block-group.h"
#समावेश "space-info.h"
#समावेश "zoned.h"

#घोषणा BTRFS_ROOT_TRANS_TAG 0

/*
 * Transaction states and transitions
 *
 * No running transaction (fs tree blocks are not modअगरied)
 * |
 * | To next stage:
 * |  Call start_transaction() variants. Except btrfs_join_transaction_nostart().
 * V
 * Transaction N [[TRANS_STATE_RUNNING]]
 * |
 * | New trans handles can be attached to transaction N by calling all
 * | start_transaction() variants.
 * |
 * | To next stage:
 * |  Call btrfs_commit_transaction() on any trans handle attached to
 * |  transaction N
 * V
 * Transaction N [[TRANS_STATE_COMMIT_START]]
 * |
 * | Will रुको क्रम previous running transaction to completely finish अगर there
 * | is one
 * |
 * | Then one of the following happes:
 * | - Wait क्रम all other trans handle holders to release.
 * |   The btrfs_commit_transaction() caller will करो the commit work.
 * | - Wait क्रम current transaction to be committed by others.
 * |   Other btrfs_commit_transaction() caller will करो the commit work.
 * |
 * | At this stage, only btrfs_join_transaction*() variants can attach
 * | to this running transaction.
 * | All other variants will रुको क्रम current one to finish and attach to
 * | transaction N+1.
 * |
 * | To next stage:
 * |  Caller is chosen to commit transaction N, and all other trans handle
 * |  haven been released.
 * V
 * Transaction N [[TRANS_STATE_COMMIT_DOING]]
 * |
 * | The heavy lअगरting transaction work is started.
 * | From running delayed refs (modअगरying extent tree) to creating pending
 * | snapshots, running qgroups.
 * | In लघु, modअगरy supporting trees to reflect modअगरications of subvolume
 * | trees.
 * |
 * | At this stage, all start_transaction() calls will रुको क्रम this
 * | transaction to finish and attach to transaction N+1.
 * |
 * | To next stage:
 * |  Until all supporting trees are updated.
 * V
 * Transaction N [[TRANS_STATE_UNBLOCKED]]
 * |						    Transaction N+1
 * | All needed trees are modअगरied, thus we only    [[TRANS_STATE_RUNNING]]
 * | need to ग_लिखो them back to disk and update	    |
 * | super blocks.				    |
 * |						    |
 * | At this stage, new transaction is allowed to   |
 * | start.					    |
 * | All new start_transaction() calls will be	    |
 * | attached to transid N+1.			    |
 * |						    |
 * | To next stage:				    |
 * |  Until all tree blocks are super blocks are    |
 * |  written to block devices			    |
 * V						    |
 * Transaction N [[TRANS_STATE_COMPLETED]]	    V
 *   All tree blocks and super blocks are written.  Transaction N+1
 *   This transaction is finished and all its	    [[TRANS_STATE_COMMIT_START]]
 *   data काष्ठाures will be cleaned up.	    | Lअगरe goes on
 */
अटल स्थिर अचिन्हित पूर्णांक btrfs_blocked_trans_types[TRANS_STATE_MAX] = अणु
	[TRANS_STATE_RUNNING]		= 0U,
	[TRANS_STATE_COMMIT_START]	= (__TRANS_START | __TRANS_ATTACH),
	[TRANS_STATE_COMMIT_DOING]	= (__TRANS_START |
					   __TRANS_ATTACH |
					   __TRANS_JOIN |
					   __TRANS_JOIN_NOSTART),
	[TRANS_STATE_UNBLOCKED]		= (__TRANS_START |
					   __TRANS_ATTACH |
					   __TRANS_JOIN |
					   __TRANS_JOIN_NOLOCK |
					   __TRANS_JOIN_NOSTART),
	[TRANS_STATE_SUPER_COMMITTED]	= (__TRANS_START |
					   __TRANS_ATTACH |
					   __TRANS_JOIN |
					   __TRANS_JOIN_NOLOCK |
					   __TRANS_JOIN_NOSTART),
	[TRANS_STATE_COMPLETED]		= (__TRANS_START |
					   __TRANS_ATTACH |
					   __TRANS_JOIN |
					   __TRANS_JOIN_NOLOCK |
					   __TRANS_JOIN_NOSTART),
पूर्ण;

व्योम btrfs_put_transaction(काष्ठा btrfs_transaction *transaction)
अणु
	WARN_ON(refcount_पढ़ो(&transaction->use_count) == 0);
	अगर (refcount_dec_and_test(&transaction->use_count)) अणु
		BUG_ON(!list_empty(&transaction->list));
		WARN_ON(!RB_EMPTY_ROOT(
				&transaction->delayed_refs.href_root.rb_root));
		WARN_ON(!RB_EMPTY_ROOT(
				&transaction->delayed_refs.dirty_extent_root));
		अगर (transaction->delayed_refs.pending_csums)
			btrfs_err(transaction->fs_info,
				  "pending csums is %llu",
				  transaction->delayed_refs.pending_csums);
		/*
		 * If any block groups are found in ->deleted_bgs then it's
		 * because the transaction was पातed and a commit did not
		 * happen (things failed beक्रमe writing the new superblock
		 * and calling btrfs_finish_extent_commit()), so we can not
		 * discard the physical locations of the block groups.
		 */
		जबतक (!list_empty(&transaction->deleted_bgs)) अणु
			काष्ठा btrfs_block_group *cache;

			cache = list_first_entry(&transaction->deleted_bgs,
						 काष्ठा btrfs_block_group,
						 bg_list);
			list_del_init(&cache->bg_list);
			btrfs_unमुक्तze_block_group(cache);
			btrfs_put_block_group(cache);
		पूर्ण
		WARN_ON(!list_empty(&transaction->dev_update_list));
		kमुक्त(transaction);
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम चयन_commit_roots(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root, *पंचांगp;
	काष्ठा btrfs_caching_control *caching_ctl, *next;

	करोwn_ग_लिखो(&fs_info->commit_root_sem);
	list_क्रम_each_entry_safe(root, पंचांगp, &cur_trans->चयन_commits,
				 dirty_list) अणु
		list_del_init(&root->dirty_list);
		मुक्त_extent_buffer(root->commit_root);
		root->commit_root = btrfs_root_node(root);
		extent_io_tree_release(&root->dirty_log_pages);
		btrfs_qgroup_clean_swapped_blocks(root);
	पूर्ण

	/* We can मुक्त old roots now. */
	spin_lock(&cur_trans->dropped_roots_lock);
	जबतक (!list_empty(&cur_trans->dropped_roots)) अणु
		root = list_first_entry(&cur_trans->dropped_roots,
					काष्ठा btrfs_root, root_list);
		list_del_init(&root->root_list);
		spin_unlock(&cur_trans->dropped_roots_lock);
		btrfs_मुक्त_log(trans, root);
		btrfs_drop_and_मुक्त_fs_root(fs_info, root);
		spin_lock(&cur_trans->dropped_roots_lock);
	पूर्ण
	spin_unlock(&cur_trans->dropped_roots_lock);

	/*
	 * We have to update the last_byte_to_unpin under the commit_root_sem,
	 * at the same समय we swap out the commit roots.
	 *
	 * This is because we must have a real view of the last spot the caching
	 * kthपढ़ोs were जबतक caching.  Consider the following views of the
	 * extent tree क्रम a block group
	 *
	 * commit root
	 * +----+----+----+----+----+----+----+
	 * |\\\\|    |\\\\|\\\\|    |\\\\|\\\\|
	 * +----+----+----+----+----+----+----+
	 * 0    1    2    3    4    5    6    7
	 *
	 * new commit root
	 * +----+----+----+----+----+----+----+
	 * |    |    |    |\\\\|    |    |\\\\|
	 * +----+----+----+----+----+----+----+
	 * 0    1    2    3    4    5    6    7
	 *
	 * If the cache_ctl->progress was at 3, then we are only allowed to
	 * unpin [0,1) and [2,3], because the caching thपढ़ो has alपढ़ोy
	 * processed those extents.  We are not allowed to unpin [5,6), because
	 * the caching thपढ़ो will re-start it's search from 3, and thus find
	 * the hole from [4,6) to add to the मुक्त space cache.
	 */
	spin_lock(&fs_info->block_group_cache_lock);
	list_क्रम_each_entry_safe(caching_ctl, next,
				 &fs_info->caching_block_groups, list) अणु
		काष्ठा btrfs_block_group *cache = caching_ctl->block_group;

		अगर (btrfs_block_group_करोne(cache)) अणु
			cache->last_byte_to_unpin = (u64)-1;
			list_del_init(&caching_ctl->list);
			btrfs_put_caching_control(caching_ctl);
		पूर्ण अन्यथा अणु
			cache->last_byte_to_unpin = caching_ctl->progress;
		पूर्ण
	पूर्ण
	spin_unlock(&fs_info->block_group_cache_lock);
	up_ग_लिखो(&fs_info->commit_root_sem);
पूर्ण

अटल अंतरभूत व्योम extग_लिखोr_counter_inc(काष्ठा btrfs_transaction *trans,
					 अचिन्हित पूर्णांक type)
अणु
	अगर (type & TRANS_EXTWRITERS)
		atomic_inc(&trans->num_extग_लिखोrs);
पूर्ण

अटल अंतरभूत व्योम extग_लिखोr_counter_dec(काष्ठा btrfs_transaction *trans,
					 अचिन्हित पूर्णांक type)
अणु
	अगर (type & TRANS_EXTWRITERS)
		atomic_dec(&trans->num_extग_लिखोrs);
पूर्ण

अटल अंतरभूत व्योम extग_लिखोr_counter_init(काष्ठा btrfs_transaction *trans,
					  अचिन्हित पूर्णांक type)
अणु
	atomic_set(&trans->num_extग_लिखोrs, ((type & TRANS_EXTWRITERS) ? 1 : 0));
पूर्ण

अटल अंतरभूत पूर्णांक extग_लिखोr_counter_पढ़ो(काष्ठा btrfs_transaction *trans)
अणु
	वापस atomic_पढ़ो(&trans->num_extग_लिखोrs);
पूर्ण

/*
 * To be called after all the new block groups attached to the transaction
 * handle have been created (btrfs_create_pending_block_groups()).
 */
व्योम btrfs_trans_release_chunk_metadata(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;

	अगर (!trans->chunk_bytes_reserved)
		वापस;

	WARN_ON_ONCE(!list_empty(&trans->new_bgs));

	btrfs_block_rsv_release(fs_info, &fs_info->chunk_block_rsv,
				trans->chunk_bytes_reserved, शून्य);
	atomic64_sub(trans->chunk_bytes_reserved, &cur_trans->chunk_bytes_reserved);
	cond_wake_up(&cur_trans->chunk_reserve_रुको);
	trans->chunk_bytes_reserved = 0;
पूर्ण

/*
 * either allocate a new transaction or hop पूर्णांकo the existing one
 */
अटल noअंतरभूत पूर्णांक join_transaction(काष्ठा btrfs_fs_info *fs_info,
				     अचिन्हित पूर्णांक type)
अणु
	काष्ठा btrfs_transaction *cur_trans;

	spin_lock(&fs_info->trans_lock);
loop:
	/* The file प्रणाली has been taken offline. No new transactions. */
	अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state)) अणु
		spin_unlock(&fs_info->trans_lock);
		वापस -EROFS;
	पूर्ण

	cur_trans = fs_info->running_transaction;
	अगर (cur_trans) अणु
		अगर (TRANS_ABORTED(cur_trans)) अणु
			spin_unlock(&fs_info->trans_lock);
			वापस cur_trans->पातed;
		पूर्ण
		अगर (btrfs_blocked_trans_types[cur_trans->state] & type) अणु
			spin_unlock(&fs_info->trans_lock);
			वापस -EBUSY;
		पूर्ण
		refcount_inc(&cur_trans->use_count);
		atomic_inc(&cur_trans->num_ग_लिखोrs);
		extग_लिखोr_counter_inc(cur_trans, type);
		spin_unlock(&fs_info->trans_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&fs_info->trans_lock);

	/*
	 * If we are ATTACH, we just want to catch the current transaction,
	 * and commit it. If there is no transaction, just वापस ENOENT.
	 */
	अगर (type == TRANS_ATTACH)
		वापस -ENOENT;

	/*
	 * JOIN_NOLOCK only happens during the transaction commit, so
	 * it is impossible that ->running_transaction is शून्य
	 */
	BUG_ON(type == TRANS_JOIN_NOLOCK);

	cur_trans = kदो_स्मृति(माप(*cur_trans), GFP_NOFS);
	अगर (!cur_trans)
		वापस -ENOMEM;

	spin_lock(&fs_info->trans_lock);
	अगर (fs_info->running_transaction) अणु
		/*
		 * someone started a transaction after we unlocked.  Make sure
		 * to reकरो the checks above
		 */
		kमुक्त(cur_trans);
		जाओ loop;
	पूर्ण अन्यथा अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state)) अणु
		spin_unlock(&fs_info->trans_lock);
		kमुक्त(cur_trans);
		वापस -EROFS;
	पूर्ण

	cur_trans->fs_info = fs_info;
	atomic_set(&cur_trans->pending_ordered, 0);
	init_रुकोqueue_head(&cur_trans->pending_रुको);
	atomic_set(&cur_trans->num_ग_लिखोrs, 1);
	extग_लिखोr_counter_init(cur_trans, type);
	init_रुकोqueue_head(&cur_trans->ग_लिखोr_रुको);
	init_रुकोqueue_head(&cur_trans->commit_रुको);
	cur_trans->state = TRANS_STATE_RUNNING;
	/*
	 * One क्रम this trans handle, one so it will live on until we
	 * commit the transaction.
	 */
	refcount_set(&cur_trans->use_count, 2);
	cur_trans->flags = 0;
	cur_trans->start_समय = kसमय_get_seconds();

	स_रखो(&cur_trans->delayed_refs, 0, माप(cur_trans->delayed_refs));

	cur_trans->delayed_refs.href_root = RB_ROOT_CACHED;
	cur_trans->delayed_refs.dirty_extent_root = RB_ROOT;
	atomic_set(&cur_trans->delayed_refs.num_entries, 0);

	/*
	 * although the tree mod log is per file प्रणाली and not per transaction,
	 * the log must never go across transaction boundaries.
	 */
	smp_mb();
	अगर (!list_empty(&fs_info->tree_mod_seq_list))
		WARN(1, KERN_ERR "BTRFS: tree_mod_seq_list not empty when creating a fresh transaction\n");
	अगर (!RB_EMPTY_ROOT(&fs_info->tree_mod_log))
		WARN(1, KERN_ERR "BTRFS: tree_mod_log rb tree not empty when creating a fresh transaction\n");
	atomic64_set(&fs_info->tree_mod_seq, 0);

	spin_lock_init(&cur_trans->delayed_refs.lock);

	INIT_LIST_HEAD(&cur_trans->pending_snapshots);
	INIT_LIST_HEAD(&cur_trans->dev_update_list);
	INIT_LIST_HEAD(&cur_trans->चयन_commits);
	INIT_LIST_HEAD(&cur_trans->dirty_bgs);
	INIT_LIST_HEAD(&cur_trans->io_bgs);
	INIT_LIST_HEAD(&cur_trans->dropped_roots);
	mutex_init(&cur_trans->cache_ग_लिखो_mutex);
	spin_lock_init(&cur_trans->dirty_bgs_lock);
	INIT_LIST_HEAD(&cur_trans->deleted_bgs);
	spin_lock_init(&cur_trans->dropped_roots_lock);
	INIT_LIST_HEAD(&cur_trans->releasing_ebs);
	spin_lock_init(&cur_trans->releasing_ebs_lock);
	atomic64_set(&cur_trans->chunk_bytes_reserved, 0);
	init_रुकोqueue_head(&cur_trans->chunk_reserve_रुको);
	list_add_tail(&cur_trans->list, &fs_info->trans_list);
	extent_io_tree_init(fs_info, &cur_trans->dirty_pages,
			IO_TREE_TRANS_सूचीTY_PAGES, fs_info->btree_inode);
	extent_io_tree_init(fs_info, &cur_trans->pinned_extents,
			IO_TREE_FS_PINNED_EXTENTS, शून्य);
	fs_info->generation++;
	cur_trans->transid = fs_info->generation;
	fs_info->running_transaction = cur_trans;
	cur_trans->पातed = 0;
	spin_unlock(&fs_info->trans_lock);

	वापस 0;
पूर्ण

/*
 * This करोes all the record keeping required to make sure that a shareable root
 * is properly recorded in a given transaction.  This is required to make sure
 * the old root from beक्रमe we joined the transaction is deleted when the
 * transaction commits.
 */
अटल पूर्णांक record_root_in_trans(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       पूर्णांक क्रमce)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret = 0;

	अगर ((test_bit(BTRFS_ROOT_SHAREABLE, &root->state) &&
	    root->last_trans < trans->transid) || क्रमce) अणु
		WARN_ON(root == fs_info->extent_root);
		WARN_ON(!क्रमce && root->commit_root != root->node);

		/*
		 * see below क्रम IN_TRANS_SETUP usage rules
		 * we have the reloc mutex held now, so there
		 * is only one ग_लिखोr in this function
		 */
		set_bit(BTRFS_ROOT_IN_TRANS_SETUP, &root->state);

		/* make sure पढ़ोers find IN_TRANS_SETUP beक्रमe
		 * they find our root->last_trans update
		 */
		smp_wmb();

		spin_lock(&fs_info->fs_roots_radix_lock);
		अगर (root->last_trans == trans->transid && !क्रमce) अणु
			spin_unlock(&fs_info->fs_roots_radix_lock);
			वापस 0;
		पूर्ण
		radix_tree_tag_set(&fs_info->fs_roots_radix,
				   (अचिन्हित दीर्घ)root->root_key.objectid,
				   BTRFS_ROOT_TRANS_TAG);
		spin_unlock(&fs_info->fs_roots_radix_lock);
		root->last_trans = trans->transid;

		/* this is pretty tricky.  We करोn't want to
		 * take the relocation lock in btrfs_record_root_in_trans
		 * unless we're really करोing the first setup क्रम this root in
		 * this transaction.
		 *
		 * Normally we'd use root->last_trans as a flag to decide
		 * अगर we want to take the expensive mutex.
		 *
		 * But, we have to set root->last_trans beक्रमe we
		 * init the relocation root, otherwise, we trip over warnings
		 * in ctree.c.  The solution used here is to flag ourselves
		 * with root IN_TRANS_SETUP.  When this is 1, we're still
		 * fixing up the reloc trees and everyone must रुको.
		 *
		 * When this is zero, they can trust root->last_trans and fly
		 * through btrfs_record_root_in_trans without having to take the
		 * lock.  smp_wmb() makes sure that all the ग_लिखोs above are
		 * करोne beक्रमe we pop in the zero below
		 */
		ret = btrfs_init_reloc_root(trans, root);
		smp_mb__beक्रमe_atomic();
		clear_bit(BTRFS_ROOT_IN_TRANS_SETUP, &root->state);
	पूर्ण
	वापस ret;
पूर्ण


व्योम btrfs_add_dropped_root(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;

	/* Add ourselves to the transaction dropped list */
	spin_lock(&cur_trans->dropped_roots_lock);
	list_add_tail(&root->root_list, &cur_trans->dropped_roots);
	spin_unlock(&cur_trans->dropped_roots_lock);

	/* Make sure we करोn't try to update the root at commit समय */
	spin_lock(&fs_info->fs_roots_radix_lock);
	radix_tree_tag_clear(&fs_info->fs_roots_radix,
			     (अचिन्हित दीर्घ)root->root_key.objectid,
			     BTRFS_ROOT_TRANS_TAG);
	spin_unlock(&fs_info->fs_roots_radix_lock);
पूर्ण

पूर्णांक btrfs_record_root_in_trans(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret;

	अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
		वापस 0;

	/*
	 * see record_root_in_trans क्रम comments about IN_TRANS_SETUP usage
	 * and barriers
	 */
	smp_rmb();
	अगर (root->last_trans == trans->transid &&
	    !test_bit(BTRFS_ROOT_IN_TRANS_SETUP, &root->state))
		वापस 0;

	mutex_lock(&fs_info->reloc_mutex);
	ret = record_root_in_trans(trans, root, 0);
	mutex_unlock(&fs_info->reloc_mutex);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक is_transaction_blocked(काष्ठा btrfs_transaction *trans)
अणु
	वापस (trans->state >= TRANS_STATE_COMMIT_START &&
		trans->state < TRANS_STATE_UNBLOCKED &&
		!TRANS_ABORTED(trans));
पूर्ण

/* रुको क्रम commit against the current transaction to become unblocked
 * when this is करोne, it is safe to start a new transaction, but the current
 * transaction might not be fully on disk.
 */
अटल व्योम रुको_current_trans(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_transaction *cur_trans;

	spin_lock(&fs_info->trans_lock);
	cur_trans = fs_info->running_transaction;
	अगर (cur_trans && is_transaction_blocked(cur_trans)) अणु
		refcount_inc(&cur_trans->use_count);
		spin_unlock(&fs_info->trans_lock);

		रुको_event(fs_info->transaction_रुको,
			   cur_trans->state >= TRANS_STATE_UNBLOCKED ||
			   TRANS_ABORTED(cur_trans));
		btrfs_put_transaction(cur_trans);
	पूर्ण अन्यथा अणु
		spin_unlock(&fs_info->trans_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक may_रुको_transaction(काष्ठा btrfs_fs_info *fs_info, पूर्णांक type)
अणु
	अगर (test_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags))
		वापस 0;

	अगर (type == TRANS_START)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत bool need_reserve_reloc_root(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	अगर (!fs_info->reloc_ctl ||
	    !test_bit(BTRFS_ROOT_SHAREABLE, &root->state) ||
	    root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID ||
	    root->reloc_root)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा btrfs_trans_handle *
start_transaction(काष्ठा btrfs_root *root, अचिन्हित पूर्णांक num_items,
		  अचिन्हित पूर्णांक type, क्रमागत btrfs_reserve_flush_क्रमागत flush,
		  bool enक्रमce_qgroups)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_block_rsv *delayed_refs_rsv = &fs_info->delayed_refs_rsv;
	काष्ठा btrfs_trans_handle *h;
	काष्ठा btrfs_transaction *cur_trans;
	u64 num_bytes = 0;
	u64 qgroup_reserved = 0;
	bool reloc_reserved = false;
	bool करो_chunk_alloc = false;
	पूर्णांक ret;

	/* Send isn't supposed to start transactions. */
	ASSERT(current->journal_info != BTRFS_SEND_TRANS_STUB);

	अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state))
		वापस ERR_PTR(-EROFS);

	अगर (current->journal_info) अणु
		WARN_ON(type & TRANS_EXTWRITERS);
		h = current->journal_info;
		refcount_inc(&h->use_count);
		WARN_ON(refcount_पढ़ो(&h->use_count) > 2);
		h->orig_rsv = h->block_rsv;
		h->block_rsv = शून्य;
		जाओ got_it;
	पूर्ण

	/*
	 * Do the reservation beक्रमe we join the transaction so we can करो all
	 * the appropriate flushing अगर need be.
	 */
	अगर (num_items && root != fs_info->chunk_root) अणु
		काष्ठा btrfs_block_rsv *rsv = &fs_info->trans_block_rsv;
		u64 delayed_refs_bytes = 0;

		qgroup_reserved = num_items * fs_info->nodesize;
		ret = btrfs_qgroup_reserve_meta_pertrans(root, qgroup_reserved,
				enक्रमce_qgroups);
		अगर (ret)
			वापस ERR_PTR(ret);

		/*
		 * We want to reserve all the bytes we may need all at once, so
		 * we only करो 1 enospc flushing cycle per transaction start.  We
		 * accomplish this by simply assuming we'll करो 2 x num_items
		 * worth of delayed refs updates in this trans handle, and
		 * refill that amount क्रम whatever is missing in the reserve.
		 */
		num_bytes = btrfs_calc_insert_metadata_size(fs_info, num_items);
		अगर (flush == BTRFS_RESERVE_FLUSH_ALL &&
		    delayed_refs_rsv->full == 0) अणु
			delayed_refs_bytes = num_bytes;
			num_bytes <<= 1;
		पूर्ण

		/*
		 * Do the reservation क्रम the relocation root creation
		 */
		अगर (need_reserve_reloc_root(root)) अणु
			num_bytes += fs_info->nodesize;
			reloc_reserved = true;
		पूर्ण

		ret = btrfs_block_rsv_add(root, rsv, num_bytes, flush);
		अगर (ret)
			जाओ reserve_fail;
		अगर (delayed_refs_bytes) अणु
			btrfs_migrate_to_delayed_refs_rsv(fs_info, rsv,
							  delayed_refs_bytes);
			num_bytes -= delayed_refs_bytes;
		पूर्ण

		अगर (rsv->space_info->क्रमce_alloc)
			करो_chunk_alloc = true;
	पूर्ण अन्यथा अगर (num_items == 0 && flush == BTRFS_RESERVE_FLUSH_ALL &&
		   !delayed_refs_rsv->full) अणु
		/*
		 * Some people call with btrfs_start_transaction(root, 0)
		 * because they can be throttled, but have some other mechanism
		 * क्रम reserving space.  We still want these guys to refill the
		 * delayed block_rsv so just add 1 items worth of reservation
		 * here.
		 */
		ret = btrfs_delayed_refs_rsv_refill(fs_info, flush);
		अगर (ret)
			जाओ reserve_fail;
	पूर्ण
again:
	h = kmem_cache_zalloc(btrfs_trans_handle_cachep, GFP_NOFS);
	अगर (!h) अणु
		ret = -ENOMEM;
		जाओ alloc_fail;
	पूर्ण

	/*
	 * If we are JOIN_NOLOCK we're alपढ़ोy committing a transaction and
	 * रुकोing on this guy, so we करोn't need to करो the sb_start_पूर्णांकग_लिखो
	 * because we're alपढ़ोy holding a ref.  We need this because we could
	 * have raced in and did an fsync() on a file which can kick a commit
	 * and then we deadlock with somebody करोing a मुक्तze.
	 *
	 * If we are ATTACH, it means we just want to catch the current
	 * transaction and commit it, so we needn't करो sb_start_पूर्णांकग_लिखो(). 
	 */
	अगर (type & __TRANS_FREEZABLE)
		sb_start_पूर्णांकग_लिखो(fs_info->sb);

	अगर (may_रुको_transaction(fs_info, type))
		रुको_current_trans(fs_info);

	करो अणु
		ret = join_transaction(fs_info, type);
		अगर (ret == -EBUSY) अणु
			रुको_current_trans(fs_info);
			अगर (unlikely(type == TRANS_ATTACH ||
				     type == TRANS_JOIN_NOSTART))
				ret = -ENOENT;
		पूर्ण
	पूर्ण जबतक (ret == -EBUSY);

	अगर (ret < 0)
		जाओ join_fail;

	cur_trans = fs_info->running_transaction;

	h->transid = cur_trans->transid;
	h->transaction = cur_trans;
	h->root = root;
	refcount_set(&h->use_count, 1);
	h->fs_info = root->fs_info;

	h->type = type;
	h->can_flush_pending_bgs = true;
	INIT_LIST_HEAD(&h->new_bgs);

	smp_mb();
	अगर (cur_trans->state >= TRANS_STATE_COMMIT_START &&
	    may_रुको_transaction(fs_info, type)) अणु
		current->journal_info = h;
		btrfs_commit_transaction(h);
		जाओ again;
	पूर्ण

	अगर (num_bytes) अणु
		trace_btrfs_space_reservation(fs_info, "transaction",
					      h->transid, num_bytes, 1);
		h->block_rsv = &fs_info->trans_block_rsv;
		h->bytes_reserved = num_bytes;
		h->reloc_reserved = reloc_reserved;
	पूर्ण

got_it:
	अगर (!current->journal_info)
		current->journal_info = h;

	/*
	 * If the space_info is marked ALLOC_FORCE then we'll get upgraded to
	 * ALLOC_FORCE the first run through, and then we won't allocate क्रम
	 * anybody अन्यथा who races in later.  We करोn't care about the वापस
	 * value here.
	 */
	अगर (करो_chunk_alloc && num_bytes) अणु
		u64 flags = h->block_rsv->space_info->flags;

		btrfs_chunk_alloc(h, btrfs_get_alloc_profile(fs_info, flags),
				  CHUNK_ALLOC_NO_FORCE);
	पूर्ण

	/*
	 * btrfs_record_root_in_trans() needs to alloc new extents, and may
	 * call btrfs_join_transaction() जबतक we're also starting a
	 * transaction.
	 *
	 * Thus it need to be called after current->journal_info initialized,
	 * or we can deadlock.
	 */
	ret = btrfs_record_root_in_trans(h, root);
	अगर (ret) अणु
		/*
		 * The transaction handle is fully initialized and linked with
		 * other काष्ठाures so it needs to be ended in हाल of errors,
		 * not just मुक्तd.
		 */
		btrfs_end_transaction(h);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस h;

join_fail:
	अगर (type & __TRANS_FREEZABLE)
		sb_end_पूर्णांकग_लिखो(fs_info->sb);
	kmem_cache_मुक्त(btrfs_trans_handle_cachep, h);
alloc_fail:
	अगर (num_bytes)
		btrfs_block_rsv_release(fs_info, &fs_info->trans_block_rsv,
					num_bytes, शून्य);
reserve_fail:
	btrfs_qgroup_मुक्त_meta_pertrans(root, qgroup_reserved);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा btrfs_trans_handle *btrfs_start_transaction(काष्ठा btrfs_root *root,
						   अचिन्हित पूर्णांक num_items)
अणु
	वापस start_transaction(root, num_items, TRANS_START,
				 BTRFS_RESERVE_FLUSH_ALL, true);
पूर्ण

काष्ठा btrfs_trans_handle *btrfs_start_transaction_fallback_global_rsv(
					काष्ठा btrfs_root *root,
					अचिन्हित पूर्णांक num_items)
अणु
	वापस start_transaction(root, num_items, TRANS_START,
				 BTRFS_RESERVE_FLUSH_ALL_STEAL, false);
पूर्ण

काष्ठा btrfs_trans_handle *btrfs_join_transaction(काष्ठा btrfs_root *root)
अणु
	वापस start_transaction(root, 0, TRANS_JOIN, BTRFS_RESERVE_NO_FLUSH,
				 true);
पूर्ण

काष्ठा btrfs_trans_handle *btrfs_join_transaction_spacecache(काष्ठा btrfs_root *root)
अणु
	वापस start_transaction(root, 0, TRANS_JOIN_NOLOCK,
				 BTRFS_RESERVE_NO_FLUSH, true);
पूर्ण

/*
 * Similar to regular join but it never starts a transaction when none is
 * running or after रुकोing क्रम the current one to finish.
 */
काष्ठा btrfs_trans_handle *btrfs_join_transaction_nostart(काष्ठा btrfs_root *root)
अणु
	वापस start_transaction(root, 0, TRANS_JOIN_NOSTART,
				 BTRFS_RESERVE_NO_FLUSH, true);
पूर्ण

/*
 * btrfs_attach_transaction() - catch the running transaction
 *
 * It is used when we want to commit the current the transaction, but
 * करोn't want to start a new one.
 *
 * Note: If this function वापस -ENOENT, it just means there is no
 * running transaction. But it is possible that the inactive transaction
 * is still in the memory, not fully on disk. If you hope there is no
 * inactive transaction in the fs when -ENOENT is वापसed, you should
 * invoke
 *     btrfs_attach_transaction_barrier()
 */
काष्ठा btrfs_trans_handle *btrfs_attach_transaction(काष्ठा btrfs_root *root)
अणु
	वापस start_transaction(root, 0, TRANS_ATTACH,
				 BTRFS_RESERVE_NO_FLUSH, true);
पूर्ण

/*
 * btrfs_attach_transaction_barrier() - catch the running transaction
 *
 * It is similar to the above function, the dअगरference is this one
 * will रुको क्रम all the inactive transactions until they fully
 * complete.
 */
काष्ठा btrfs_trans_handle *
btrfs_attach_transaction_barrier(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_trans_handle *trans;

	trans = start_transaction(root, 0, TRANS_ATTACH,
				  BTRFS_RESERVE_NO_FLUSH, true);
	अगर (trans == ERR_PTR(-ENOENT))
		btrfs_रुको_क्रम_commit(root->fs_info, 0);

	वापस trans;
पूर्ण

/* Wait क्रम a transaction commit to reach at least the given state. */
अटल noअंतरभूत व्योम रुको_क्रम_commit(काष्ठा btrfs_transaction *commit,
				     स्थिर क्रमागत btrfs_trans_state min_state)
अणु
	रुको_event(commit->commit_रुको, commit->state >= min_state);
पूर्ण

पूर्णांक btrfs_रुको_क्रम_commit(काष्ठा btrfs_fs_info *fs_info, u64 transid)
अणु
	काष्ठा btrfs_transaction *cur_trans = शून्य, *t;
	पूर्णांक ret = 0;

	अगर (transid) अणु
		अगर (transid <= fs_info->last_trans_committed)
			जाओ out;

		/* find specअगरied transaction */
		spin_lock(&fs_info->trans_lock);
		list_क्रम_each_entry(t, &fs_info->trans_list, list) अणु
			अगर (t->transid == transid) अणु
				cur_trans = t;
				refcount_inc(&cur_trans->use_count);
				ret = 0;
				अवरोध;
			पूर्ण
			अगर (t->transid > transid) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&fs_info->trans_lock);

		/*
		 * The specअगरied transaction करोesn't exist, or we
		 * raced with btrfs_commit_transaction
		 */
		अगर (!cur_trans) अणु
			अगर (transid > fs_info->last_trans_committed)
				ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* find newest transaction that is committing | committed */
		spin_lock(&fs_info->trans_lock);
		list_क्रम_each_entry_reverse(t, &fs_info->trans_list,
					    list) अणु
			अगर (t->state >= TRANS_STATE_COMMIT_START) अणु
				अगर (t->state == TRANS_STATE_COMPLETED)
					अवरोध;
				cur_trans = t;
				refcount_inc(&cur_trans->use_count);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&fs_info->trans_lock);
		अगर (!cur_trans)
			जाओ out;  /* nothing committing|committed */
	पूर्ण

	रुको_क्रम_commit(cur_trans, TRANS_STATE_COMPLETED);
	btrfs_put_transaction(cur_trans);
out:
	वापस ret;
पूर्ण

व्योम btrfs_throttle(काष्ठा btrfs_fs_info *fs_info)
अणु
	रुको_current_trans(fs_info);
पूर्ण

अटल bool should_end_transaction(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;

	अगर (btrfs_check_space_क्रम_delayed_refs(fs_info))
		वापस true;

	वापस !!btrfs_block_rsv_check(&fs_info->global_block_rsv, 5);
पूर्ण

bool btrfs_should_end_transaction(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;

	अगर (cur_trans->state >= TRANS_STATE_COMMIT_START ||
	    test_bit(BTRFS_DELAYED_REFS_FLUSHING, &cur_trans->delayed_refs.flags))
		वापस true;

	वापस should_end_transaction(trans);
पूर्ण

अटल व्योम btrfs_trans_release_metadata(काष्ठा btrfs_trans_handle *trans)

अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;

	अगर (!trans->block_rsv) अणु
		ASSERT(!trans->bytes_reserved);
		वापस;
	पूर्ण

	अगर (!trans->bytes_reserved)
		वापस;

	ASSERT(trans->block_rsv == &fs_info->trans_block_rsv);
	trace_btrfs_space_reservation(fs_info, "transaction",
				      trans->transid, trans->bytes_reserved, 0);
	btrfs_block_rsv_release(fs_info, trans->block_rsv,
				trans->bytes_reserved, शून्य);
	trans->bytes_reserved = 0;
पूर्ण

अटल पूर्णांक __btrfs_end_transaction(काष्ठा btrfs_trans_handle *trans,
				   पूर्णांक throttle)
अणु
	काष्ठा btrfs_fs_info *info = trans->fs_info;
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;
	पूर्णांक err = 0;

	अगर (refcount_पढ़ो(&trans->use_count) > 1) अणु
		refcount_dec(&trans->use_count);
		trans->block_rsv = trans->orig_rsv;
		वापस 0;
	पूर्ण

	btrfs_trans_release_metadata(trans);
	trans->block_rsv = शून्य;

	btrfs_create_pending_block_groups(trans);

	btrfs_trans_release_chunk_metadata(trans);

	अगर (trans->type & __TRANS_FREEZABLE)
		sb_end_पूर्णांकग_लिखो(info->sb);

	WARN_ON(cur_trans != info->running_transaction);
	WARN_ON(atomic_पढ़ो(&cur_trans->num_ग_लिखोrs) < 1);
	atomic_dec(&cur_trans->num_ग_लिखोrs);
	extग_लिखोr_counter_dec(cur_trans, trans->type);

	cond_wake_up(&cur_trans->ग_लिखोr_रुको);
	btrfs_put_transaction(cur_trans);

	अगर (current->journal_info == trans)
		current->journal_info = शून्य;

	अगर (throttle)
		btrfs_run_delayed_iमाला_दो(info);

	अगर (TRANS_ABORTED(trans) ||
	    test_bit(BTRFS_FS_STATE_ERROR, &info->fs_state)) अणु
		wake_up_process(info->transaction_kthपढ़ो);
		अगर (TRANS_ABORTED(trans))
			err = trans->पातed;
		अन्यथा
			err = -EROFS;
	पूर्ण

	kmem_cache_मुक्त(btrfs_trans_handle_cachep, trans);
	वापस err;
पूर्ण

पूर्णांक btrfs_end_transaction(काष्ठा btrfs_trans_handle *trans)
अणु
	वापस __btrfs_end_transaction(trans, 0);
पूर्ण

पूर्णांक btrfs_end_transaction_throttle(काष्ठा btrfs_trans_handle *trans)
अणु
	वापस __btrfs_end_transaction(trans, 1);
पूर्ण

/*
 * when btree blocks are allocated, they have some corresponding bits set क्रम
 * them in one of two extent_io trees.  This is used to make sure all of
 * those extents are sent to disk but करोes not रुको on them
 */
पूर्णांक btrfs_ग_लिखो_marked_extents(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा extent_io_tree *dirty_pages, पूर्णांक mark)
अणु
	पूर्णांक err = 0;
	पूर्णांक werr = 0;
	काष्ठा address_space *mapping = fs_info->btree_inode->i_mapping;
	काष्ठा extent_state *cached_state = शून्य;
	u64 start = 0;
	u64 end;

	atomic_inc(&BTRFS_I(fs_info->btree_inode)->sync_ग_लिखोrs);
	जबतक (!find_first_extent_bit(dirty_pages, start, &start, &end,
				      mark, &cached_state)) अणु
		bool रुको_ग_लिखोback = false;

		err = convert_extent_bit(dirty_pages, start, end,
					 EXTENT_NEED_WAIT,
					 mark, &cached_state);
		/*
		 * convert_extent_bit can वापस -ENOMEM, which is most of the
		 * समय a temporary error. So when it happens, ignore the error
		 * and रुको क्रम ग_लिखोback of this range to finish - because we
		 * failed to set the bit EXTENT_NEED_WAIT क्रम the range, a call
		 * to __btrfs_रुको_marked_extents() would not know that
		 * ग_लिखोback क्रम this range started and thereक्रमe wouldn't
		 * रुको क्रम it to finish - we करोn't want to commit a
		 * superblock that poपूर्णांकs to btree nodes/leafs क्रम which
		 * ग_लिखोback hasn't finished yet (and without errors).
		 * We cleanup any entries left in the io tree when committing
		 * the transaction (through extent_io_tree_release()).
		 */
		अगर (err == -ENOMEM) अणु
			err = 0;
			रुको_ग_लिखोback = true;
		पूर्ण
		अगर (!err)
			err = filemap_fdataग_लिखो_range(mapping, start, end);
		अगर (err)
			werr = err;
		अन्यथा अगर (रुको_ग_लिखोback)
			werr = filemap_fdataरुको_range(mapping, start, end);
		मुक्त_extent_state(cached_state);
		cached_state = शून्य;
		cond_resched();
		start = end + 1;
	पूर्ण
	atomic_dec(&BTRFS_I(fs_info->btree_inode)->sync_ग_लिखोrs);
	वापस werr;
पूर्ण

/*
 * when btree blocks are allocated, they have some corresponding bits set क्रम
 * them in one of two extent_io trees.  This is used to make sure all of
 * those extents are on disk क्रम transaction or log commit.  We रुको
 * on all the pages and clear them from the dirty pages state tree
 */
अटल पूर्णांक __btrfs_रुको_marked_extents(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा extent_io_tree *dirty_pages)
अणु
	पूर्णांक err = 0;
	पूर्णांक werr = 0;
	काष्ठा address_space *mapping = fs_info->btree_inode->i_mapping;
	काष्ठा extent_state *cached_state = शून्य;
	u64 start = 0;
	u64 end;

	जबतक (!find_first_extent_bit(dirty_pages, start, &start, &end,
				      EXTENT_NEED_WAIT, &cached_state)) अणु
		/*
		 * Ignore -ENOMEM errors वापसed by clear_extent_bit().
		 * When committing the transaction, we'll हटाओ any entries
		 * left in the io tree. For a log commit, we करोn't हटाओ them
		 * after committing the log because the tree can be accessed
		 * concurrently - we करो it only at transaction commit समय when
		 * it's safe to करो it (through extent_io_tree_release()).
		 */
		err = clear_extent_bit(dirty_pages, start, end,
				       EXTENT_NEED_WAIT, 0, 0, &cached_state);
		अगर (err == -ENOMEM)
			err = 0;
		अगर (!err)
			err = filemap_fdataरुको_range(mapping, start, end);
		अगर (err)
			werr = err;
		मुक्त_extent_state(cached_state);
		cached_state = शून्य;
		cond_resched();
		start = end + 1;
	पूर्ण
	अगर (err)
		werr = err;
	वापस werr;
पूर्ण

अटल पूर्णांक btrfs_रुको_extents(काष्ठा btrfs_fs_info *fs_info,
		       काष्ठा extent_io_tree *dirty_pages)
अणु
	bool errors = false;
	पूर्णांक err;

	err = __btrfs_रुको_marked_extents(fs_info, dirty_pages);
	अगर (test_and_clear_bit(BTRFS_FS_BTREE_ERR, &fs_info->flags))
		errors = true;

	अगर (errors && !err)
		err = -EIO;
	वापस err;
पूर्ण

पूर्णांक btrfs_रुको_tree_log_extents(काष्ठा btrfs_root *log_root, पूर्णांक mark)
अणु
	काष्ठा btrfs_fs_info *fs_info = log_root->fs_info;
	काष्ठा extent_io_tree *dirty_pages = &log_root->dirty_log_pages;
	bool errors = false;
	पूर्णांक err;

	ASSERT(log_root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID);

	err = __btrfs_रुको_marked_extents(fs_info, dirty_pages);
	अगर ((mark & EXTENT_सूचीTY) &&
	    test_and_clear_bit(BTRFS_FS_LOG1_ERR, &fs_info->flags))
		errors = true;

	अगर ((mark & EXTENT_NEW) &&
	    test_and_clear_bit(BTRFS_FS_LOG2_ERR, &fs_info->flags))
		errors = true;

	अगर (errors && !err)
		err = -EIO;
	वापस err;
पूर्ण

/*
 * When btree blocks are allocated the corresponding extents are marked dirty.
 * This function ensures such extents are persisted on disk क्रम transaction or
 * log commit.
 *
 * @trans: transaction whose dirty pages we'd like to ग_लिखो
 */
अटल पूर्णांक btrfs_ग_लिखो_and_रुको_transaction(काष्ठा btrfs_trans_handle *trans)
अणु
	पूर्णांक ret;
	पूर्णांक ret2;
	काष्ठा extent_io_tree *dirty_pages = &trans->transaction->dirty_pages;
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा blk_plug plug;

	blk_start_plug(&plug);
	ret = btrfs_ग_लिखो_marked_extents(fs_info, dirty_pages, EXTENT_सूचीTY);
	blk_finish_plug(&plug);
	ret2 = btrfs_रुको_extents(fs_info, dirty_pages);

	extent_io_tree_release(&trans->transaction->dirty_pages);

	अगर (ret)
		वापस ret;
	अन्यथा अगर (ret2)
		वापस ret2;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * this is used to update the root poपूर्णांकer in the tree of tree roots.
 *
 * But, in the हाल of the extent allocation tree, updating the root
 * poपूर्णांकer may allocate blocks which may change the root of the extent
 * allocation tree.
 *
 * So, this loops and repeats and makes sure the cowonly root didn't
 * change जबतक the root poपूर्णांकer was being updated in the metadata.
 */
अटल पूर्णांक update_cowonly_root(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root)
अणु
	पूर्णांक ret;
	u64 old_root_bytenr;
	u64 old_root_used;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;

	old_root_used = btrfs_root_used(&root->root_item);

	जबतक (1) अणु
		old_root_bytenr = btrfs_root_bytenr(&root->root_item);
		अगर (old_root_bytenr == root->node->start &&
		    old_root_used == btrfs_root_used(&root->root_item))
			अवरोध;

		btrfs_set_root_node(&root->root_item, root->node);
		ret = btrfs_update_root(trans, tree_root,
					&root->root_key,
					&root->root_item);
		अगर (ret)
			वापस ret;

		old_root_used = btrfs_root_used(&root->root_item);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * update all the cowonly tree roots on disk
 *
 * The error handling in this function may not be obvious. Any of the
 * failures will cause the file प्रणाली to go offline. We still need
 * to clean up the delayed refs.
 */
अटल noअंतरभूत पूर्णांक commit_cowonly_roots(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा list_head *dirty_bgs = &trans->transaction->dirty_bgs;
	काष्ठा list_head *io_bgs = &trans->transaction->io_bgs;
	काष्ठा list_head *next;
	काष्ठा extent_buffer *eb;
	पूर्णांक ret;

	eb = btrfs_lock_root_node(fs_info->tree_root);
	ret = btrfs_cow_block(trans, fs_info->tree_root, eb, शून्य,
			      0, &eb, BTRFS_NESTING_COW);
	btrfs_tree_unlock(eb);
	मुक्त_extent_buffer(eb);

	अगर (ret)
		वापस ret;

	ret = btrfs_run_dev_stats(trans);
	अगर (ret)
		वापस ret;
	ret = btrfs_run_dev_replace(trans);
	अगर (ret)
		वापस ret;
	ret = btrfs_run_qgroups(trans);
	अगर (ret)
		वापस ret;

	ret = btrfs_setup_space_cache(trans);
	अगर (ret)
		वापस ret;

again:
	जबतक (!list_empty(&fs_info->dirty_cowonly_roots)) अणु
		काष्ठा btrfs_root *root;
		next = fs_info->dirty_cowonly_roots.next;
		list_del_init(next);
		root = list_entry(next, काष्ठा btrfs_root, dirty_list);
		clear_bit(BTRFS_ROOT_सूचीTY, &root->state);

		अगर (root != fs_info->extent_root)
			list_add_tail(&root->dirty_list,
				      &trans->transaction->चयन_commits);
		ret = update_cowonly_root(trans, root);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Now flush any delayed refs generated by updating all of the roots */
	ret = btrfs_run_delayed_refs(trans, (अचिन्हित दीर्घ)-1);
	अगर (ret)
		वापस ret;

	जबतक (!list_empty(dirty_bgs) || !list_empty(io_bgs)) अणु
		ret = btrfs_ग_लिखो_dirty_block_groups(trans);
		अगर (ret)
			वापस ret;

		/*
		 * We're writing the dirty block groups, which could generate
		 * delayed refs, which could generate more dirty block groups,
		 * so we want to keep this flushing in this loop to make sure
		 * everything माला_लो run.
		 */
		ret = btrfs_run_delayed_refs(trans, (अचिन्हित दीर्घ)-1);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!list_empty(&fs_info->dirty_cowonly_roots))
		जाओ again;

	list_add_tail(&fs_info->extent_root->dirty_list,
		      &trans->transaction->चयन_commits);

	/* Update dev-replace poपूर्णांकer once everything is committed */
	fs_info->dev_replace.committed_cursor_left =
		fs_info->dev_replace.cursor_left_last_ग_लिखो_of_item;

	वापस 0;
पूर्ण

/*
 * dead roots are old snapshots that need to be deleted.  This allocates
 * a dirty root काष्ठा and adds it पूर्णांकo the list of dead roots that need to
 * be deleted
 */
व्योम btrfs_add_dead_root(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	spin_lock(&fs_info->trans_lock);
	अगर (list_empty(&root->root_list)) अणु
		btrfs_grab_root(root);
		list_add_tail(&root->root_list, &fs_info->dead_roots);
	पूर्ण
	spin_unlock(&fs_info->trans_lock);
पूर्ण

/*
 * update all the cowonly tree roots on disk
 */
अटल noअंतरभूत पूर्णांक commit_fs_roots(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *gang[8];
	पूर्णांक i;
	पूर्णांक ret;

	spin_lock(&fs_info->fs_roots_radix_lock);
	जबतक (1) अणु
		ret = radix_tree_gang_lookup_tag(&fs_info->fs_roots_radix,
						 (व्योम **)gang, 0,
						 ARRAY_SIZE(gang),
						 BTRFS_ROOT_TRANS_TAG);
		अगर (ret == 0)
			अवरोध;
		क्रम (i = 0; i < ret; i++) अणु
			काष्ठा btrfs_root *root = gang[i];
			पूर्णांक ret2;

			radix_tree_tag_clear(&fs_info->fs_roots_radix,
					(अचिन्हित दीर्घ)root->root_key.objectid,
					BTRFS_ROOT_TRANS_TAG);
			spin_unlock(&fs_info->fs_roots_radix_lock);

			btrfs_मुक्त_log(trans, root);
			ret2 = btrfs_update_reloc_root(trans, root);
			अगर (ret2)
				वापस ret2;

			/* see comments in should_cow_block() */
			clear_bit(BTRFS_ROOT_FORCE_COW, &root->state);
			smp_mb__after_atomic();

			अगर (root->commit_root != root->node) अणु
				list_add_tail(&root->dirty_list,
					&trans->transaction->चयन_commits);
				btrfs_set_root_node(&root->root_item,
						    root->node);
			पूर्ण

			ret2 = btrfs_update_root(trans, fs_info->tree_root,
						&root->root_key,
						&root->root_item);
			अगर (ret2)
				वापस ret2;
			spin_lock(&fs_info->fs_roots_radix_lock);
			btrfs_qgroup_मुक्त_meta_all_pertrans(root);
		पूर्ण
	पूर्ण
	spin_unlock(&fs_info->fs_roots_radix_lock);
	वापस 0;
पूर्ण

/*
 * defrag a given btree.
 * Every leaf in the btree is पढ़ो and defragged.
 */
पूर्णांक btrfs_defrag_root(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *info = root->fs_info;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;

	अगर (test_and_set_bit(BTRFS_ROOT_DEFRAG_RUNNING, &root->state))
		वापस 0;

	जबतक (1) अणु
		trans = btrfs_start_transaction(root, 0);
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);

		ret = btrfs_defrag_leaves(trans, root);

		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty(info);
		cond_resched();

		अगर (btrfs_fs_closing(info) || ret != -EAGAIN)
			अवरोध;

		अगर (btrfs_defrag_cancelled(info)) अणु
			btrfs_debug(info, "defrag_root cancelled");
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
	पूर्ण
	clear_bit(BTRFS_ROOT_DEFRAG_RUNNING, &root->state);
	वापस ret;
पूर्ण

/*
 * Do all special snapshot related qgroup dirty hack.
 *
 * Will करो all needed qgroup inherit and dirty hack like चयन commit
 * roots inside one transaction and ग_लिखो all btree पूर्णांकo disk, to make
 * qgroup works.
 */
अटल पूर्णांक qgroup_account_snapshot(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_root *src,
				   काष्ठा btrfs_root *parent,
				   काष्ठा btrfs_qgroup_inherit *inherit,
				   u64 dst_objectid)
अणु
	काष्ठा btrfs_fs_info *fs_info = src->fs_info;
	पूर्णांक ret;

	/*
	 * Save some perक्रमmance in the हाल that qgroups are not
	 * enabled. If this check races with the ioctl, rescan will
	 * kick in anyway.
	 */
	अगर (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		वापस 0;

	/*
	 * Ensure dirty @src will be committed.  Or, after coming
	 * commit_fs_roots() and चयन_commit_roots(), any dirty but not
	 * recorded root will never be updated again, causing an outdated root
	 * item.
	 */
	ret = record_root_in_trans(trans, src, 1);
	अगर (ret)
		वापस ret;

	/*
	 * btrfs_qgroup_inherit relies on a consistent view of the usage क्रम the
	 * src root, so we must run the delayed refs here.
	 *
	 * However this isn't particularly fool proof, because there's no
	 * synchronization keeping us from changing the tree after this poपूर्णांक
	 * beक्रमe we करो the qgroup_inherit, or even from making changes जबतक
	 * we're doing the qgroup_inherit.  But that's a problem क्रम the future,
	 * क्रम now flush the delayed refs to narrow the race winकरोw where the
	 * qgroup counters could end up wrong.
	 */
	ret = btrfs_run_delayed_refs(trans, (अचिन्हित दीर्घ)-1);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	/*
	 * We are going to commit transaction, see btrfs_commit_transaction()
	 * comment क्रम reason locking tree_log_mutex
	 */
	mutex_lock(&fs_info->tree_log_mutex);

	ret = commit_fs_roots(trans);
	अगर (ret)
		जाओ out;
	ret = btrfs_qgroup_account_extents(trans);
	अगर (ret < 0)
		जाओ out;

	/* Now qgroup are all updated, we can inherit it to new qgroups */
	ret = btrfs_qgroup_inherit(trans, src->root_key.objectid, dst_objectid,
				   inherit);
	अगर (ret < 0)
		जाओ out;

	/*
	 * Now we करो a simplअगरied commit transaction, which will:
	 * 1) commit all subvolume and extent tree
	 *    To ensure all subvolume and extent tree have a valid
	 *    commit_root to accounting later insert_dir_item()
	 * 2) ग_लिखो all btree blocks onto disk
	 *    This is to make sure later btree modअगरication will be cowed
	 *    Or commit_root can be populated and cause wrong qgroup numbers
	 * In this simplअगरied commit, we करोn't really care about other trees
	 * like chunk and root tree, as they won't affect qgroup.
	 * And we करोn't ग_लिखो super to aव्योम half committed status.
	 */
	ret = commit_cowonly_roots(trans);
	अगर (ret)
		जाओ out;
	चयन_commit_roots(trans);
	ret = btrfs_ग_लिखो_and_रुको_transaction(trans);
	अगर (ret)
		btrfs_handle_fs_error(fs_info, ret,
			"Error while writing out transaction for qgroup");

out:
	mutex_unlock(&fs_info->tree_log_mutex);

	/*
	 * Force parent root to be updated, as we recorded it beक्रमe so its
	 * last_trans == cur_transid.
	 * Or it won't be committed again onto disk after later
	 * insert_dir_item()
	 */
	अगर (!ret)
		ret = record_root_in_trans(trans, parent, 1);
	वापस ret;
पूर्ण

/*
 * new snapshots need to be created at a very specअगरic समय in the
 * transaction commit.  This करोes the actual creation.
 *
 * Note:
 * If the error which may affect the commiपंचांगent of the current transaction
 * happens, we should वापस the error number. If the error which just affect
 * the creation of the pending snapshots, just वापस 0.
 */
अटल noअंतरभूत पूर्णांक create_pending_snapshot(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_pending_snapshot *pending)
अणु

	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root_item *new_root_item;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा btrfs_root *root = pending->root;
	काष्ठा btrfs_root *parent_root;
	काष्ठा btrfs_block_rsv *rsv;
	काष्ठा inode *parent_inode;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_dir_item *dir_item;
	काष्ठा dentry *dentry;
	काष्ठा extent_buffer *पंचांगp;
	काष्ठा extent_buffer *old;
	काष्ठा बारpec64 cur_समय;
	पूर्णांक ret = 0;
	u64 to_reserve = 0;
	u64 index = 0;
	u64 objectid;
	u64 root_flags;

	ASSERT(pending->path);
	path = pending->path;

	ASSERT(pending->root_item);
	new_root_item = pending->root_item;

	pending->error = btrfs_get_मुक्त_objectid(tree_root, &objectid);
	अगर (pending->error)
		जाओ no_मुक्त_objectid;

	/*
	 * Make qgroup to skip current new snapshot's qgroupid, as it is
	 * accounted by later btrfs_qgroup_inherit().
	 */
	btrfs_set_skip_qgroup(trans, objectid);

	btrfs_reloc_pre_snapshot(pending, &to_reserve);

	अगर (to_reserve > 0) अणु
		pending->error = btrfs_block_rsv_add(root,
						     &pending->block_rsv,
						     to_reserve,
						     BTRFS_RESERVE_NO_FLUSH);
		अगर (pending->error)
			जाओ clear_skip_qgroup;
	पूर्ण

	key.objectid = objectid;
	key.offset = (u64)-1;
	key.type = BTRFS_ROOT_ITEM_KEY;

	rsv = trans->block_rsv;
	trans->block_rsv = &pending->block_rsv;
	trans->bytes_reserved = trans->block_rsv->reserved;
	trace_btrfs_space_reservation(fs_info, "transaction",
				      trans->transid,
				      trans->bytes_reserved, 1);
	dentry = pending->dentry;
	parent_inode = pending->dir;
	parent_root = BTRFS_I(parent_inode)->root;
	ret = record_root_in_trans(trans, parent_root, 0);
	अगर (ret)
		जाओ fail;
	cur_समय = current_समय(parent_inode);

	/*
	 * insert the directory item
	 */
	ret = btrfs_set_inode_index(BTRFS_I(parent_inode), &index);
	BUG_ON(ret); /* -ENOMEM */

	/* check अगर there is a file/dir which has the same name. */
	dir_item = btrfs_lookup_dir_item(शून्य, parent_root, path,
					 btrfs_ino(BTRFS_I(parent_inode)),
					 dentry->d_name.name,
					 dentry->d_name.len, 0);
	अगर (dir_item != शून्य && !IS_ERR(dir_item)) अणु
		pending->error = -EEXIST;
		जाओ dir_item_existed;
	पूर्ण अन्यथा अगर (IS_ERR(dir_item)) अणु
		ret = PTR_ERR(dir_item);
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण
	btrfs_release_path(path);

	/*
	 * pull in the delayed directory update
	 * and the delayed inode item
	 * otherwise we corrupt the FS during
	 * snapshot
	 */
	ret = btrfs_run_delayed_items(trans);
	अगर (ret) अणु	/* Transaction पातed */
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	ret = record_root_in_trans(trans, root, 0);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण
	btrfs_set_root_last_snapshot(&root->root_item, trans->transid);
	स_नकल(new_root_item, &root->root_item, माप(*new_root_item));
	btrfs_check_and_init_root_item(new_root_item);

	root_flags = btrfs_root_flags(new_root_item);
	अगर (pending->पढ़ोonly)
		root_flags |= BTRFS_ROOT_SUBVOL_RDONLY;
	अन्यथा
		root_flags &= ~BTRFS_ROOT_SUBVOL_RDONLY;
	btrfs_set_root_flags(new_root_item, root_flags);

	btrfs_set_root_generation_v2(new_root_item,
			trans->transid);
	generate_अक्रमom_guid(new_root_item->uuid);
	स_नकल(new_root_item->parent_uuid, root->root_item.uuid,
			BTRFS_UUID_SIZE);
	अगर (!(root_flags & BTRFS_ROOT_SUBVOL_RDONLY)) अणु
		स_रखो(new_root_item->received_uuid, 0,
		       माप(new_root_item->received_uuid));
		स_रखो(&new_root_item->sसमय, 0, माप(new_root_item->sसमय));
		स_रखो(&new_root_item->rसमय, 0, माप(new_root_item->rसमय));
		btrfs_set_root_stransid(new_root_item, 0);
		btrfs_set_root_rtransid(new_root_item, 0);
	पूर्ण
	btrfs_set_stack_बारpec_sec(&new_root_item->oसमय, cur_समय.tv_sec);
	btrfs_set_stack_बारpec_nsec(&new_root_item->oसमय, cur_समय.tv_nsec);
	btrfs_set_root_otransid(new_root_item, trans->transid);

	old = btrfs_lock_root_node(root);
	ret = btrfs_cow_block(trans, root, old, शून्य, 0, &old,
			      BTRFS_NESTING_COW);
	अगर (ret) अणु
		btrfs_tree_unlock(old);
		मुक्त_extent_buffer(old);
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	ret = btrfs_copy_root(trans, root, old, &पंचांगp, objectid);
	/* clean up in any हाल */
	btrfs_tree_unlock(old);
	मुक्त_extent_buffer(old);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण
	/* see comments in should_cow_block() */
	set_bit(BTRFS_ROOT_FORCE_COW, &root->state);
	smp_wmb();

	btrfs_set_root_node(new_root_item, पंचांगp);
	/* record when the snapshot was created in key.offset */
	key.offset = trans->transid;
	ret = btrfs_insert_root(trans, tree_root, &key, new_root_item);
	btrfs_tree_unlock(पंचांगp);
	मुक्त_extent_buffer(पंचांगp);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	/*
	 * insert root back/क्रमward references
	 */
	ret = btrfs_add_root_ref(trans, objectid,
				 parent_root->root_key.objectid,
				 btrfs_ino(BTRFS_I(parent_inode)), index,
				 dentry->d_name.name, dentry->d_name.len);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	key.offset = (u64)-1;
	pending->snap = btrfs_get_new_fs_root(fs_info, objectid, pending->anon_dev);
	अगर (IS_ERR(pending->snap)) अणु
		ret = PTR_ERR(pending->snap);
		pending->snap = शून्य;
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	ret = btrfs_reloc_post_snapshot(trans, pending);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	/*
	 * Do special qgroup accounting क्रम snapshot, as we करो some qgroup
	 * snapshot hack to करो fast snapshot.
	 * To co-operate with that hack, we करो hack again.
	 * Or snapshot will be greatly slowed करोwn by a subtree qgroup rescan
	 */
	ret = qgroup_account_snapshot(trans, root, parent_root,
				      pending->inherit, objectid);
	अगर (ret < 0)
		जाओ fail;

	ret = btrfs_insert_dir_item(trans, dentry->d_name.name,
				    dentry->d_name.len, BTRFS_I(parent_inode),
				    &key, BTRFS_FT_सूची, index);
	/* We have check then name at the beginning, so it is impossible. */
	BUG_ON(ret == -EEXIST || ret == -EOVERFLOW);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण

	btrfs_i_size_ग_लिखो(BTRFS_I(parent_inode), parent_inode->i_size +
					 dentry->d_name.len * 2);
	parent_inode->i_mसमय = parent_inode->i_स_समय =
		current_समय(parent_inode);
	ret = btrfs_update_inode_fallback(trans, parent_root, BTRFS_I(parent_inode));
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण
	ret = btrfs_uuid_tree_add(trans, new_root_item->uuid,
				  BTRFS_UUID_KEY_SUBVOL,
				  objectid);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ fail;
	पूर्ण
	अगर (!btrfs_is_empty_uuid(new_root_item->received_uuid)) अणु
		ret = btrfs_uuid_tree_add(trans, new_root_item->received_uuid,
					  BTRFS_UUID_KEY_RECEIVED_SUBVOL,
					  objectid);
		अगर (ret && ret != -EEXIST) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ fail;
		पूर्ण
	पूर्ण

fail:
	pending->error = ret;
dir_item_existed:
	trans->block_rsv = rsv;
	trans->bytes_reserved = 0;
clear_skip_qgroup:
	btrfs_clear_skip_qgroup(trans);
no_मुक्त_objectid:
	kमुक्त(new_root_item);
	pending->root_item = शून्य;
	btrfs_मुक्त_path(path);
	pending->path = शून्य;

	वापस ret;
पूर्ण

/*
 * create all the snapshots we've scheduled क्रम creation
 */
अटल noअंतरभूत पूर्णांक create_pending_snapshots(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_pending_snapshot *pending, *next;
	काष्ठा list_head *head = &trans->transaction->pending_snapshots;
	पूर्णांक ret = 0;

	list_क्रम_each_entry_safe(pending, next, head, list) अणु
		list_del(&pending->list);
		ret = create_pending_snapshot(trans, pending);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम update_super_roots(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root_item *root_item;
	काष्ठा btrfs_super_block *super;

	super = fs_info->super_copy;

	root_item = &fs_info->chunk_root->root_item;
	super->chunk_root = root_item->bytenr;
	super->chunk_root_generation = root_item->generation;
	super->chunk_root_level = root_item->level;

	root_item = &fs_info->tree_root->root_item;
	super->root = root_item->bytenr;
	super->generation = root_item->generation;
	super->root_level = root_item->level;
	अगर (btrfs_test_opt(fs_info, SPACE_CACHE))
		super->cache_generation = root_item->generation;
	अन्यथा अगर (test_bit(BTRFS_FS_CLEANUP_SPACE_CACHE_V1, &fs_info->flags))
		super->cache_generation = 0;
	अगर (test_bit(BTRFS_FS_UPDATE_UUID_TREE_GEN, &fs_info->flags))
		super->uuid_tree_generation = root_item->generation;
पूर्ण

पूर्णांक btrfs_transaction_in_commit(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा btrfs_transaction *trans;
	पूर्णांक ret = 0;

	spin_lock(&info->trans_lock);
	trans = info->running_transaction;
	अगर (trans)
		ret = (trans->state >= TRANS_STATE_COMMIT_START);
	spin_unlock(&info->trans_lock);
	वापस ret;
पूर्ण

पूर्णांक btrfs_transaction_blocked(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा btrfs_transaction *trans;
	पूर्णांक ret = 0;

	spin_lock(&info->trans_lock);
	trans = info->running_transaction;
	अगर (trans)
		ret = is_transaction_blocked(trans);
	spin_unlock(&info->trans_lock);
	वापस ret;
पूर्ण

/*
 * रुको क्रम the current transaction commit to start and block subsequent
 * transaction joins
 */
अटल व्योम रुको_current_trans_commit_start(काष्ठा btrfs_fs_info *fs_info,
					    काष्ठा btrfs_transaction *trans)
अणु
	रुको_event(fs_info->transaction_blocked_रुको,
		   trans->state >= TRANS_STATE_COMMIT_START ||
		   TRANS_ABORTED(trans));
पूर्ण

/*
 * रुको क्रम the current transaction to start and then become unblocked.
 * caller holds ref.
 */
अटल व्योम रुको_current_trans_commit_start_and_unblock(
					काष्ठा btrfs_fs_info *fs_info,
					काष्ठा btrfs_transaction *trans)
अणु
	रुको_event(fs_info->transaction_रुको,
		   trans->state >= TRANS_STATE_UNBLOCKED ||
		   TRANS_ABORTED(trans));
पूर्ण

/*
 * commit transactions asynchronously. once btrfs_commit_transaction_async
 * वापसs, any subsequent transaction will not be allowed to join.
 */
काष्ठा btrfs_async_commit अणु
	काष्ठा btrfs_trans_handle *newtrans;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल व्योम करो_async_commit(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btrfs_async_commit *ac =
		container_of(work, काष्ठा btrfs_async_commit, work);

	/*
	 * We've got मुक्तze protection passed with the transaction.
	 * Tell lockdep about it.
	 */
	अगर (ac->newtrans->type & __TRANS_FREEZABLE)
		__sb_ग_लिखोrs_acquired(ac->newtrans->fs_info->sb, SB_FREEZE_FS);

	current->journal_info = ac->newtrans;

	btrfs_commit_transaction(ac->newtrans);
	kमुक्त(ac);
पूर्ण

पूर्णांक btrfs_commit_transaction_async(काष्ठा btrfs_trans_handle *trans,
				   पूर्णांक रुको_क्रम_unblock)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_async_commit *ac;
	काष्ठा btrfs_transaction *cur_trans;

	ac = kदो_स्मृति(माप(*ac), GFP_NOFS);
	अगर (!ac)
		वापस -ENOMEM;

	INIT_WORK(&ac->work, करो_async_commit);
	ac->newtrans = btrfs_join_transaction(trans->root);
	अगर (IS_ERR(ac->newtrans)) अणु
		पूर्णांक err = PTR_ERR(ac->newtrans);
		kमुक्त(ac);
		वापस err;
	पूर्ण

	/* take transaction reference */
	cur_trans = trans->transaction;
	refcount_inc(&cur_trans->use_count);

	btrfs_end_transaction(trans);

	/*
	 * Tell lockdep we've released the मुक्तze rwsem, since the
	 * async commit thपढ़ो will be the one to unlock it.
	 */
	अगर (ac->newtrans->type & __TRANS_FREEZABLE)
		__sb_ग_लिखोrs_release(fs_info->sb, SB_FREEZE_FS);

	schedule_work(&ac->work);

	/* रुको क्रम transaction to start and unblock */
	अगर (रुको_क्रम_unblock)
		रुको_current_trans_commit_start_and_unblock(fs_info, cur_trans);
	अन्यथा
		रुको_current_trans_commit_start(fs_info, cur_trans);

	अगर (current->journal_info == trans)
		current->journal_info = शून्य;

	btrfs_put_transaction(cur_trans);
	वापस 0;
पूर्ण


अटल व्योम cleanup_transaction(काष्ठा btrfs_trans_handle *trans, पूर्णांक err)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;

	WARN_ON(refcount_पढ़ो(&trans->use_count) > 1);

	btrfs_पात_transaction(trans, err);

	spin_lock(&fs_info->trans_lock);

	/*
	 * If the transaction is हटाओd from the list, it means this
	 * transaction has been committed successfully, so it is impossible
	 * to call the cleanup function.
	 */
	BUG_ON(list_empty(&cur_trans->list));

	अगर (cur_trans == fs_info->running_transaction) अणु
		cur_trans->state = TRANS_STATE_COMMIT_DOING;
		spin_unlock(&fs_info->trans_lock);
		रुको_event(cur_trans->ग_लिखोr_रुको,
			   atomic_पढ़ो(&cur_trans->num_ग_लिखोrs) == 1);

		spin_lock(&fs_info->trans_lock);
	पूर्ण

	/*
	 * Now that we know no one अन्यथा is still using the transaction we can
	 * हटाओ the transaction from the list of transactions. This aव्योमs
	 * the transaction kthपढ़ो from cleaning up the transaction जबतक some
	 * other task is still using it, which could result in a use-after-मुक्त
	 * on things like log trees, as it क्रमces the transaction kthपढ़ो to
	 * रुको क्रम this transaction to be cleaned up by us.
	 */
	list_del_init(&cur_trans->list);

	spin_unlock(&fs_info->trans_lock);

	btrfs_cleanup_one_transaction(trans->transaction, fs_info);

	spin_lock(&fs_info->trans_lock);
	अगर (cur_trans == fs_info->running_transaction)
		fs_info->running_transaction = शून्य;
	spin_unlock(&fs_info->trans_lock);

	अगर (trans->type & __TRANS_FREEZABLE)
		sb_end_पूर्णांकग_लिखो(fs_info->sb);
	btrfs_put_transaction(cur_trans);
	btrfs_put_transaction(cur_trans);

	trace_btrfs_transaction_commit(trans->root);

	अगर (current->journal_info == trans)
		current->journal_info = शून्य;
	btrfs_scrub_cancel(fs_info);

	kmem_cache_मुक्त(btrfs_trans_handle_cachep, trans);
पूर्ण

/*
 * Release reserved delayed ref space of all pending block groups of the
 * transaction and हटाओ them from the list
 */
अटल व्योम btrfs_cleanup_pending_block_groups(काष्ठा btrfs_trans_handle *trans)
अणु
       काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
       काष्ठा btrfs_block_group *block_group, *पंचांगp;

       list_क्रम_each_entry_safe(block_group, पंचांगp, &trans->new_bgs, bg_list) अणु
               btrfs_delayed_refs_rsv_release(fs_info, 1);
               list_del_init(&block_group->bg_list);
       पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_start_delalloc_flush(काष्ठा btrfs_fs_info *fs_info)
अणु
	/*
	 * We use ग_लिखोback_inodes_sb here because अगर we used
	 * btrfs_start_delalloc_roots we would deadlock with fs मुक्तze.
	 * Currently are holding the fs मुक्तze lock, अगर we करो an async flush
	 * we'll करो btrfs_join_transaction() and deadlock because we need to
	 * रुको क्रम the fs मुक्तze lock.  Using the direct flushing we benefit
	 * from alपढ़ोy being in a transaction and our join_transaction करोesn't
	 * have to re-take the fs मुक्तze lock.
	 */
	अगर (btrfs_test_opt(fs_info, FLUSHONCOMMIT))
		ग_लिखोback_inodes_sb(fs_info->sb, WB_REASON_SYNC);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम btrfs_रुको_delalloc_flush(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (btrfs_test_opt(fs_info, FLUSHONCOMMIT))
		btrfs_रुको_ordered_roots(fs_info, U64_MAX, 0, (u64)-1);
पूर्ण

पूर्णांक btrfs_commit_transaction(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;
	काष्ठा btrfs_transaction *prev_trans = शून्य;
	पूर्णांक ret;

	ASSERT(refcount_पढ़ो(&trans->use_count) == 1);

	/*
	 * Some places just start a transaction to commit it.  We need to make
	 * sure that अगर this commit fails that the पात code actually marks the
	 * transaction as failed, so set trans->dirty to make the पात code करो
	 * the right thing.
	 */
	trans->dirty = true;

	/* Stop the commit early अगर ->पातed is set */
	अगर (TRANS_ABORTED(cur_trans)) अणु
		ret = cur_trans->पातed;
		btrfs_end_transaction(trans);
		वापस ret;
	पूर्ण

	btrfs_trans_release_metadata(trans);
	trans->block_rsv = शून्य;

	/*
	 * We only want one transaction commit करोing the flushing so we करो not
	 * waste a bunch of समय on lock contention on the extent root node.
	 */
	अगर (!test_and_set_bit(BTRFS_DELAYED_REFS_FLUSHING,
			      &cur_trans->delayed_refs.flags)) अणु
		/*
		 * Make a pass through all the delayed refs we have so far.
		 * Any running thपढ़ोs may add more जबतक we are here.
		 */
		ret = btrfs_run_delayed_refs(trans, 0);
		अगर (ret) अणु
			btrfs_end_transaction(trans);
			वापस ret;
		पूर्ण
	पूर्ण

	btrfs_create_pending_block_groups(trans);

	अगर (!test_bit(BTRFS_TRANS_सूचीTY_BG_RUN, &cur_trans->flags)) अणु
		पूर्णांक run_it = 0;

		/* this mutex is also taken beक्रमe trying to set
		 * block groups पढ़ोonly.  We need to make sure
		 * that nobody has set a block group पढ़ोonly
		 * after a extents from that block group have been
		 * allocated क्रम cache files.  btrfs_set_block_group_ro
		 * will रुको क्रम the transaction to commit अगर it
		 * finds BTRFS_TRANS_सूचीTY_BG_RUN set.
		 *
		 * The BTRFS_TRANS_सूचीTY_BG_RUN flag is also used to make sure
		 * only one process starts all the block group IO.  It wouldn't
		 * hurt to have more than one go through, but there's no
		 * real advantage to it either.
		 */
		mutex_lock(&fs_info->ro_block_group_mutex);
		अगर (!test_and_set_bit(BTRFS_TRANS_सूचीTY_BG_RUN,
				      &cur_trans->flags))
			run_it = 1;
		mutex_unlock(&fs_info->ro_block_group_mutex);

		अगर (run_it) अणु
			ret = btrfs_start_dirty_block_groups(trans);
			अगर (ret) अणु
				btrfs_end_transaction(trans);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock(&fs_info->trans_lock);
	अगर (cur_trans->state >= TRANS_STATE_COMMIT_START) अणु
		क्रमागत btrfs_trans_state want_state = TRANS_STATE_COMPLETED;

		spin_unlock(&fs_info->trans_lock);
		refcount_inc(&cur_trans->use_count);

		अगर (trans->in_fsync)
			want_state = TRANS_STATE_SUPER_COMMITTED;
		ret = btrfs_end_transaction(trans);
		रुको_क्रम_commit(cur_trans, want_state);

		अगर (TRANS_ABORTED(cur_trans))
			ret = cur_trans->पातed;

		btrfs_put_transaction(cur_trans);

		वापस ret;
	पूर्ण

	cur_trans->state = TRANS_STATE_COMMIT_START;
	wake_up(&fs_info->transaction_blocked_रुको);

	अगर (cur_trans->list.prev != &fs_info->trans_list) अणु
		क्रमागत btrfs_trans_state want_state = TRANS_STATE_COMPLETED;

		अगर (trans->in_fsync)
			want_state = TRANS_STATE_SUPER_COMMITTED;

		prev_trans = list_entry(cur_trans->list.prev,
					काष्ठा btrfs_transaction, list);
		अगर (prev_trans->state < want_state) अणु
			refcount_inc(&prev_trans->use_count);
			spin_unlock(&fs_info->trans_lock);

			रुको_क्रम_commit(prev_trans, want_state);

			ret = READ_ONCE(prev_trans->पातed);

			btrfs_put_transaction(prev_trans);
			अगर (ret)
				जाओ cleanup_transaction;
		पूर्ण अन्यथा अणु
			spin_unlock(&fs_info->trans_lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock(&fs_info->trans_lock);
		/*
		 * The previous transaction was पातed and was alपढ़ोy हटाओd
		 * from the list of transactions at fs_info->trans_list. So we
		 * पात to prevent writing a new superblock that reflects a
		 * corrupt state (poपूर्णांकing to trees with unwritten nodes/leafs).
		 */
		अगर (test_bit(BTRFS_FS_STATE_TRANS_ABORTED, &fs_info->fs_state)) अणु
			ret = -EROFS;
			जाओ cleanup_transaction;
		पूर्ण
	पूर्ण

	extग_लिखोr_counter_dec(cur_trans, trans->type);

	ret = btrfs_start_delalloc_flush(fs_info);
	अगर (ret)
		जाओ cleanup_transaction;

	ret = btrfs_run_delayed_items(trans);
	अगर (ret)
		जाओ cleanup_transaction;

	रुको_event(cur_trans->ग_लिखोr_रुको,
		   extग_लिखोr_counter_पढ़ो(cur_trans) == 0);

	/* some pending stuffs might be added after the previous flush. */
	ret = btrfs_run_delayed_items(trans);
	अगर (ret)
		जाओ cleanup_transaction;

	btrfs_रुको_delalloc_flush(fs_info);

	/*
	 * Wait क्रम all ordered extents started by a fast fsync that joined this
	 * transaction. Otherwise अगर this transaction commits beक्रमe the ordered
	 * extents complete we lose logged data after a घातer failure.
	 */
	रुको_event(cur_trans->pending_रुको,
		   atomic_पढ़ो(&cur_trans->pending_ordered) == 0);

	btrfs_scrub_छोड़ो(fs_info);
	/*
	 * Ok now we need to make sure to block out any other joins जबतक we
	 * commit the transaction.  We could have started a join beक्रमe setting
	 * COMMIT_DOING so make sure to रुको क्रम num_ग_लिखोrs to == 1 again.
	 */
	spin_lock(&fs_info->trans_lock);
	cur_trans->state = TRANS_STATE_COMMIT_DOING;
	spin_unlock(&fs_info->trans_lock);
	रुको_event(cur_trans->ग_लिखोr_रुको,
		   atomic_पढ़ो(&cur_trans->num_ग_लिखोrs) == 1);

	अगर (TRANS_ABORTED(cur_trans)) अणु
		ret = cur_trans->पातed;
		जाओ scrub_जारी;
	पूर्ण
	/*
	 * the reloc mutex makes sure that we stop
	 * the balancing code from coming in and moving
	 * extents around in the middle of the commit
	 */
	mutex_lock(&fs_info->reloc_mutex);

	/*
	 * We needn't worry about the delayed items because we will
	 * deal with them in create_pending_snapshot(), which is the
	 * core function of the snapshot creation.
	 */
	ret = create_pending_snapshots(trans);
	अगर (ret)
		जाओ unlock_reloc;

	/*
	 * We insert the dir indexes of the snapshots and update the inode
	 * of the snapshots' parents after the snapshot creation, so there
	 * are some delayed items which are not dealt with. Now deal with
	 * them.
	 *
	 * We needn't worry that this operation will corrupt the snapshots,
	 * because all the tree which are snapshoted will be क्रमced to COW
	 * the nodes and leaves.
	 */
	ret = btrfs_run_delayed_items(trans);
	अगर (ret)
		जाओ unlock_reloc;

	ret = btrfs_run_delayed_refs(trans, (अचिन्हित दीर्घ)-1);
	अगर (ret)
		जाओ unlock_reloc;

	/*
	 * make sure none of the code above managed to slip in a
	 * delayed item
	 */
	btrfs_निश्चित_delayed_root_empty(fs_info);

	WARN_ON(cur_trans != trans->transaction);

	/* btrfs_commit_tree_roots is responsible क्रम getting the
	 * various roots consistent with each other.  Every poपूर्णांकer
	 * in the tree of tree roots has to poपूर्णांक to the most up to date
	 * root क्रम every subvolume and other tree.  So, we have to keep
	 * the tree logging code from jumping in and changing any
	 * of the trees.
	 *
	 * At this poपूर्णांक in the commit, there can't be any tree-log
	 * ग_लिखोrs, but a little lower करोwn we drop the trans mutex
	 * and let new people in.  By holding the tree_log_mutex
	 * from now until after the super is written, we aव्योम races
	 * with the tree-log code.
	 */
	mutex_lock(&fs_info->tree_log_mutex);

	ret = commit_fs_roots(trans);
	अगर (ret)
		जाओ unlock_tree_log;

	/*
	 * Since the transaction is करोne, we can apply the pending changes
	 * beक्रमe the next transaction.
	 */
	btrfs_apply_pending_changes(fs_info);

	/* commit_fs_roots माला_लो rid of all the tree log roots, it is now
	 * safe to मुक्त the root of tree log roots
	 */
	btrfs_मुक्त_log_root_tree(trans, fs_info);

	/*
	 * Since fs roots are all committed, we can get a quite accurate
	 * new_roots. So let's करो quota accounting.
	 */
	ret = btrfs_qgroup_account_extents(trans);
	अगर (ret < 0)
		जाओ unlock_tree_log;

	ret = commit_cowonly_roots(trans);
	अगर (ret)
		जाओ unlock_tree_log;

	/*
	 * The tasks which save the space cache and inode cache may also
	 * update ->पातed, check it.
	 */
	अगर (TRANS_ABORTED(cur_trans)) अणु
		ret = cur_trans->पातed;
		जाओ unlock_tree_log;
	पूर्ण

	cur_trans = fs_info->running_transaction;

	btrfs_set_root_node(&fs_info->tree_root->root_item,
			    fs_info->tree_root->node);
	list_add_tail(&fs_info->tree_root->dirty_list,
		      &cur_trans->चयन_commits);

	btrfs_set_root_node(&fs_info->chunk_root->root_item,
			    fs_info->chunk_root->node);
	list_add_tail(&fs_info->chunk_root->dirty_list,
		      &cur_trans->चयन_commits);

	चयन_commit_roots(trans);

	ASSERT(list_empty(&cur_trans->dirty_bgs));
	ASSERT(list_empty(&cur_trans->io_bgs));
	update_super_roots(fs_info);

	btrfs_set_super_log_root(fs_info->super_copy, 0);
	btrfs_set_super_log_root_level(fs_info->super_copy, 0);
	स_नकल(fs_info->super_क्रम_commit, fs_info->super_copy,
	       माप(*fs_info->super_copy));

	btrfs_commit_device_sizes(cur_trans);

	clear_bit(BTRFS_FS_LOG1_ERR, &fs_info->flags);
	clear_bit(BTRFS_FS_LOG2_ERR, &fs_info->flags);

	btrfs_trans_release_chunk_metadata(trans);

	spin_lock(&fs_info->trans_lock);
	cur_trans->state = TRANS_STATE_UNBLOCKED;
	fs_info->running_transaction = शून्य;
	spin_unlock(&fs_info->trans_lock);
	mutex_unlock(&fs_info->reloc_mutex);

	wake_up(&fs_info->transaction_रुको);

	ret = btrfs_ग_लिखो_and_रुको_transaction(trans);
	अगर (ret) अणु
		btrfs_handle_fs_error(fs_info, ret,
				      "Error while writing out transaction");
		/*
		 * reloc_mutex has been unlocked, tree_log_mutex is still held
		 * but we can't jump to unlock_tree_log causing द्विगुन unlock
		 */
		mutex_unlock(&fs_info->tree_log_mutex);
		जाओ scrub_जारी;
	पूर्ण

	/*
	 * At this poपूर्णांक, we should have written all the tree blocks allocated
	 * in this transaction. So it's now safe to मुक्त the redirtyied extent
	 * buffers.
	 */
	btrfs_मुक्त_redirty_list(cur_trans);

	ret = ग_लिखो_all_supers(fs_info, 0);
	/*
	 * the super is written, we can safely allow the tree-loggers
	 * to go about their business
	 */
	mutex_unlock(&fs_info->tree_log_mutex);
	अगर (ret)
		जाओ scrub_जारी;

	/*
	 * We needn't acquire the lock here because there is no other task
	 * which can change it.
	 */
	cur_trans->state = TRANS_STATE_SUPER_COMMITTED;
	wake_up(&cur_trans->commit_रुको);

	btrfs_finish_extent_commit(trans);

	अगर (test_bit(BTRFS_TRANS_HAVE_FREE_BGS, &cur_trans->flags))
		btrfs_clear_space_info_full(fs_info);

	fs_info->last_trans_committed = cur_trans->transid;
	/*
	 * We needn't acquire the lock here because there is no other task
	 * which can change it.
	 */
	cur_trans->state = TRANS_STATE_COMPLETED;
	wake_up(&cur_trans->commit_रुको);

	spin_lock(&fs_info->trans_lock);
	list_del_init(&cur_trans->list);
	spin_unlock(&fs_info->trans_lock);

	btrfs_put_transaction(cur_trans);
	btrfs_put_transaction(cur_trans);

	अगर (trans->type & __TRANS_FREEZABLE)
		sb_end_पूर्णांकग_लिखो(fs_info->sb);

	trace_btrfs_transaction_commit(trans->root);

	btrfs_scrub_जारी(fs_info);

	अगर (current->journal_info == trans)
		current->journal_info = शून्य;

	kmem_cache_मुक्त(btrfs_trans_handle_cachep, trans);

	वापस ret;

unlock_tree_log:
	mutex_unlock(&fs_info->tree_log_mutex);
unlock_reloc:
	mutex_unlock(&fs_info->reloc_mutex);
scrub_जारी:
	btrfs_scrub_जारी(fs_info);
cleanup_transaction:
	btrfs_trans_release_metadata(trans);
	btrfs_cleanup_pending_block_groups(trans);
	btrfs_trans_release_chunk_metadata(trans);
	trans->block_rsv = शून्य;
	btrfs_warn(fs_info, "Skipping commit of aborted transaction.");
	अगर (current->journal_info == trans)
		current->journal_info = शून्य;
	cleanup_transaction(trans, ret);

	वापस ret;
पूर्ण

/*
 * वापस < 0 अगर error
 * 0 अगर there are no more dead_roots at the समय of call
 * 1 there are more to be processed, call me again
 *
 * The वापस value indicates there are certainly more snapshots to delete, but
 * अगर there comes a new one during processing, it may वापस 0. We करोn't mind,
 * because btrfs_commit_super will poke cleaner thपढ़ो and it will process it a
 * few seconds later.
 */
पूर्णांक btrfs_clean_one_deleted_snapshot(काष्ठा btrfs_root *root)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	spin_lock(&fs_info->trans_lock);
	अगर (list_empty(&fs_info->dead_roots)) अणु
		spin_unlock(&fs_info->trans_lock);
		वापस 0;
	पूर्ण
	root = list_first_entry(&fs_info->dead_roots,
			काष्ठा btrfs_root, root_list);
	list_del_init(&root->root_list);
	spin_unlock(&fs_info->trans_lock);

	btrfs_debug(fs_info, "cleaner removing %llu", root->root_key.objectid);

	btrfs_समाप्त_all_delayed_nodes(root);

	अगर (btrfs_header_backref_rev(root->node) <
			BTRFS_MIXED_BACKREF_REV)
		ret = btrfs_drop_snapshot(root, 0, 0);
	अन्यथा
		ret = btrfs_drop_snapshot(root, 1, 0);

	btrfs_put_root(root);
	वापस (ret < 0) ? 0 : 1;
पूर्ण

व्योम btrfs_apply_pending_changes(काष्ठा btrfs_fs_info *fs_info)
अणु
	अचिन्हित दीर्घ prev;
	अचिन्हित दीर्घ bit;

	prev = xchg(&fs_info->pending_changes, 0);
	अगर (!prev)
		वापस;

	bit = 1 << BTRFS_PENDING_COMMIT;
	अगर (prev & bit)
		btrfs_debug(fs_info, "pending commit done");
	prev &= ~bit;

	अगर (prev)
		btrfs_warn(fs_info,
			"unknown pending changes left 0x%lx, ignoring", prev);
पूर्ण
