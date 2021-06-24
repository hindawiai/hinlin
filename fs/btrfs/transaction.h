<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_TRANSACTION_H
#घोषणा BTRFS_TRANSACTION_H

#समावेश <linux/refcount.h>
#समावेश "btrfs_inode.h"
#समावेश "delayed-ref.h"
#समावेश "ctree.h"

क्रमागत btrfs_trans_state अणु
	TRANS_STATE_RUNNING,
	TRANS_STATE_COMMIT_START,
	TRANS_STATE_COMMIT_DOING,
	TRANS_STATE_UNBLOCKED,
	TRANS_STATE_SUPER_COMMITTED,
	TRANS_STATE_COMPLETED,
	TRANS_STATE_MAX,
पूर्ण;

#घोषणा BTRFS_TRANS_HAVE_FREE_BGS	0
#घोषणा BTRFS_TRANS_सूचीTY_BG_RUN	1
#घोषणा BTRFS_TRANS_CACHE_ENOSPC	2

काष्ठा btrfs_transaction अणु
	u64 transid;
	/*
	 * total बाह्यal ग_लिखोrs(USERSPACE/START/ATTACH) in this
	 * transaction, it must be zero beक्रमe the transaction is
	 * being committed
	 */
	atomic_t num_extग_लिखोrs;
	/*
	 * total ग_लिखोrs in this transaction, it must be zero beक्रमe the
	 * transaction can end
	 */
	atomic_t num_ग_लिखोrs;
	refcount_t use_count;

	अचिन्हित दीर्घ flags;

	/* Be रक्षित by fs_info->trans_lock when we want to change it. */
	क्रमागत btrfs_trans_state state;
	पूर्णांक पातed;
	काष्ठा list_head list;
	काष्ठा extent_io_tree dirty_pages;
	समय64_t start_समय;
	रुको_queue_head_t ग_लिखोr_रुको;
	रुको_queue_head_t commit_रुको;
	काष्ठा list_head pending_snapshots;
	काष्ठा list_head dev_update_list;
	काष्ठा list_head चयन_commits;
	काष्ठा list_head dirty_bgs;

	/*
	 * There is no explicit lock which protects io_bgs, rather its
	 * consistency is implied by the fact that all the sites which modअगरy
	 * it करो so under some क्रमm of transaction critical section, namely:
	 *
	 * - btrfs_start_dirty_block_groups - This function can only ever be
	 *   run by one of the transaction committers. Refer to
	 *   BTRFS_TRANS_सूचीTY_BG_RUN usage in btrfs_commit_transaction
	 *
	 * - btrfs_ग_लिखो_dirty_blockgroups - this is called by
	 *   commit_cowonly_roots from transaction critical section
	 *   (TRANS_STATE_COMMIT_DOING)
	 *
	 * - btrfs_cleanup_dirty_bgs - called on transaction पात
	 */
	काष्ठा list_head io_bgs;
	काष्ठा list_head dropped_roots;
	काष्ठा extent_io_tree pinned_extents;

	/*
	 * we need to make sure block group deletion करोesn't race with
	 * मुक्त space cache ग_लिखोout.  This mutex keeps them from stomping
	 * on each other
	 */
	काष्ठा mutex cache_ग_लिखो_mutex;
	spinlock_t dirty_bgs_lock;
	/* Protected by spin lock fs_info->unused_bgs_lock. */
	काष्ठा list_head deleted_bgs;
	spinlock_t dropped_roots_lock;
	काष्ठा btrfs_delayed_ref_root delayed_refs;
	काष्ठा btrfs_fs_info *fs_info;

	/*
	 * Number of ordered extents the transaction must रुको क्रम beक्रमe
	 * committing. These are ordered extents started by a fast fsync.
	 */
	atomic_t pending_ordered;
	रुको_queue_head_t pending_रुको;

	spinlock_t releasing_ebs_lock;
	काष्ठा list_head releasing_ebs;

	/*
	 * The number of bytes currently reserved, by all transaction handles
	 * attached to this transaction, क्रम metadata extents of the chunk tree.
	 */
	atomic64_t chunk_bytes_reserved;
	रुको_queue_head_t chunk_reserve_रुको;
पूर्ण;

#घोषणा __TRANS_FREEZABLE	(1U << 0)

#घोषणा __TRANS_START		(1U << 9)
#घोषणा __TRANS_ATTACH		(1U << 10)
#घोषणा __TRANS_JOIN		(1U << 11)
#घोषणा __TRANS_JOIN_NOLOCK	(1U << 12)
#घोषणा __TRANS_DUMMY		(1U << 13)
#घोषणा __TRANS_JOIN_NOSTART	(1U << 14)

#घोषणा TRANS_START		(__TRANS_START | __TRANS_FREEZABLE)
#घोषणा TRANS_ATTACH		(__TRANS_ATTACH)
#घोषणा TRANS_JOIN		(__TRANS_JOIN | __TRANS_FREEZABLE)
#घोषणा TRANS_JOIN_NOLOCK	(__TRANS_JOIN_NOLOCK)
#घोषणा TRANS_JOIN_NOSTART	(__TRANS_JOIN_NOSTART)

#घोषणा TRANS_EXTWRITERS	(__TRANS_START | __TRANS_ATTACH)

#घोषणा BTRFS_SEND_TRANS_STUB	((व्योम *)1)

काष्ठा btrfs_trans_handle अणु
	u64 transid;
	u64 bytes_reserved;
	u64 chunk_bytes_reserved;
	अचिन्हित दीर्घ delayed_ref_updates;
	काष्ठा btrfs_transaction *transaction;
	काष्ठा btrfs_block_rsv *block_rsv;
	काष्ठा btrfs_block_rsv *orig_rsv;
	refcount_t use_count;
	अचिन्हित पूर्णांक type;
	/*
	 * Error code of transaction पात, set outside of locks and must use
	 * the READ_ONCE/WRITE_ONCE access
	 */
	लघु पातed;
	bool adding_csums;
	bool allocating_chunk;
	bool can_flush_pending_bgs;
	bool reloc_reserved;
	bool dirty;
	bool in_fsync;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा list_head new_bgs;
पूर्ण;

/*
 * The पात status can be changed between calls and is not रक्षित by locks.
 * This accepts btrfs_transaction and btrfs_trans_handle as types. Once it's
 * set to a non-zero value it करोes not change, so the macro should be in checks
 * but is not necessary क्रम further पढ़ोs of the value.
 */
#घोषणा TRANS_ABORTED(trans)		(unlikely(READ_ONCE((trans)->पातed)))

काष्ठा btrfs_pending_snapshot अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *dir;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_root_item *root_item;
	काष्ठा btrfs_root *snap;
	काष्ठा btrfs_qgroup_inherit *inherit;
	काष्ठा btrfs_path *path;
	/* block reservation क्रम the operation */
	काष्ठा btrfs_block_rsv block_rsv;
	/* extra metadata reservation क्रम relocation */
	पूर्णांक error;
	/* Pपुनः_स्मृतिated anonymous block device number */
	dev_t anon_dev;
	bool पढ़ोonly;
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत व्योम btrfs_set_inode_last_trans(काष्ठा btrfs_trans_handle *trans,
					      काष्ठा btrfs_inode *inode)
अणु
	spin_lock(&inode->lock);
	inode->last_trans = trans->transaction->transid;
	inode->last_sub_trans = inode->root->log_transid;
	inode->last_log_commit = inode->last_sub_trans - 1;
	spin_unlock(&inode->lock);
पूर्ण

/*
 * Make qgroup codes to skip given qgroupid, means the old/new_roots क्रम
 * qgroup won't contain the qgroupid in it.
 */
अटल अंतरभूत व्योम btrfs_set_skip_qgroup(काष्ठा btrfs_trans_handle *trans,
					 u64 qgroupid)
अणु
	काष्ठा btrfs_delayed_ref_root *delayed_refs;

	delayed_refs = &trans->transaction->delayed_refs;
	WARN_ON(delayed_refs->qgroup_to_skip);
	delayed_refs->qgroup_to_skip = qgroupid;
पूर्ण

अटल अंतरभूत व्योम btrfs_clear_skip_qgroup(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_delayed_ref_root *delayed_refs;

	delayed_refs = &trans->transaction->delayed_refs;
	WARN_ON(!delayed_refs->qgroup_to_skip);
	delayed_refs->qgroup_to_skip = 0;
पूर्ण

पूर्णांक btrfs_end_transaction(काष्ठा btrfs_trans_handle *trans);
काष्ठा btrfs_trans_handle *btrfs_start_transaction(काष्ठा btrfs_root *root,
						   अचिन्हित पूर्णांक num_items);
काष्ठा btrfs_trans_handle *btrfs_start_transaction_fallback_global_rsv(
					काष्ठा btrfs_root *root,
					अचिन्हित पूर्णांक num_items);
काष्ठा btrfs_trans_handle *btrfs_join_transaction(काष्ठा btrfs_root *root);
काष्ठा btrfs_trans_handle *btrfs_join_transaction_spacecache(काष्ठा btrfs_root *root);
काष्ठा btrfs_trans_handle *btrfs_join_transaction_nostart(काष्ठा btrfs_root *root);
काष्ठा btrfs_trans_handle *btrfs_attach_transaction(काष्ठा btrfs_root *root);
काष्ठा btrfs_trans_handle *btrfs_attach_transaction_barrier(
					काष्ठा btrfs_root *root);
पूर्णांक btrfs_रुको_क्रम_commit(काष्ठा btrfs_fs_info *fs_info, u64 transid);

व्योम btrfs_add_dead_root(काष्ठा btrfs_root *root);
पूर्णांक btrfs_defrag_root(काष्ठा btrfs_root *root);
पूर्णांक btrfs_clean_one_deleted_snapshot(काष्ठा btrfs_root *root);
पूर्णांक btrfs_commit_transaction(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_commit_transaction_async(काष्ठा btrfs_trans_handle *trans,
				   पूर्णांक रुको_क्रम_unblock);
पूर्णांक btrfs_end_transaction_throttle(काष्ठा btrfs_trans_handle *trans);
bool btrfs_should_end_transaction(काष्ठा btrfs_trans_handle *trans);
व्योम btrfs_throttle(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_record_root_in_trans(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root);
पूर्णांक btrfs_ग_लिखो_marked_extents(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा extent_io_tree *dirty_pages, पूर्णांक mark);
पूर्णांक btrfs_रुको_tree_log_extents(काष्ठा btrfs_root *root, पूर्णांक mark);
पूर्णांक btrfs_transaction_blocked(काष्ठा btrfs_fs_info *info);
पूर्णांक btrfs_transaction_in_commit(काष्ठा btrfs_fs_info *info);
व्योम btrfs_put_transaction(काष्ठा btrfs_transaction *transaction);
व्योम btrfs_apply_pending_changes(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_add_dropped_root(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root);
व्योम btrfs_trans_release_chunk_metadata(काष्ठा btrfs_trans_handle *trans);

#पूर्ण_अगर
