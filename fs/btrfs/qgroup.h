<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014 Facebook.  All rights reserved.
 */

#अगर_अघोषित BTRFS_QGROUP_H
#घोषणा BTRFS_QGROUP_H

#समावेश <linux/spinlock.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/kobject.h>
#समावेश "ulist.h"
#समावेश "delayed-ref.h"

/*
 * Btrfs qgroup overview
 *
 * Btrfs qgroup splits पूर्णांकo 3 मुख्य part:
 * 1) Reserve
 *    Reserve metadata/data space क्रम incoming operations
 *    Affect how qgroup limit works
 *
 * 2) Trace
 *    Tell btrfs qgroup to trace dirty extents.
 *
 *    Dirty extents including:
 *    - Newly allocated extents
 *    - Extents going to be deleted (in this trans)
 *    - Extents whose owner is going to be modअगरied
 *
 *    This is the मुख्य part affects whether qgroup numbers will stay
 *    consistent.
 *    Btrfs qgroup can trace clean extents and won't cause any problem,
 *    but it will consume extra CPU समय, it should be aव्योमed अगर possible.
 *
 * 3) Account
 *    Btrfs qgroup will updates its numbers, based on dirty extents traced
 *    in previous step.
 *
 *    Normally at qgroup rescan and transaction commit समय.
 */

/*
 * Special perक्रमmance optimization क्रम balance.
 *
 * For balance, we need to swap subtree of subvolume and reloc trees.
 * In theory, we need to trace all subtree blocks of both subvolume and reloc
 * trees, since their owner has changed during such swap.
 *
 * However since balance has ensured that both subtrees are containing the
 * same contents and have the same tree काष्ठाures, such swap won't cause
 * qgroup number change.
 *
 * But there is a race winकरोw between subtree swap and transaction commit,
 * during that winकरोw, अगर we increase/decrease tree level or merge/split tree
 * blocks, we still need to trace the original subtrees.
 *
 * So क्रम balance, we use a delayed subtree tracing, whose workflow is:
 *
 * 1) Record the subtree root block get swapped.
 *
 *    During subtree swap:
 *    O = Old tree blocks
 *    N = New tree blocks
 *          reloc tree                     subvolume tree X
 *             Root                               Root
 *            /    \                             /    \
 *          NA     OB                          OA      OB
 *        /  |     |  \                      /  |      |  \
 *      NC  ND     OE  OF                   OC  OD     OE  OF
 *
 *   In this हाल, NA and OA are going to be swapped, record (NA, OA) पूर्णांकo
 *   subvolume tree X.
 *
 * 2) After subtree swap.
 *          reloc tree                     subvolume tree X
 *             Root                               Root
 *            /    \                             /    \
 *          OA     OB                          NA      OB
 *        /  |     |  \                      /  |      |  \
 *      OC  OD     OE  OF                   NC  ND     OE  OF
 *
 * 3a) COW happens क्रम OB
 *     If we are going to COW tree block OB, we check OB's bytenr against
 *     tree X's swapped_blocks काष्ठाure.
 *     If it करोesn't fit any, nothing will happen.
 *
 * 3b) COW happens क्रम NA
 *     Check NA's bytenr against tree X's swapped_blocks, and get a hit.
 *     Then we करो subtree scan on both subtrees OA and NA.
 *     Resulting 6 tree blocks to be scanned (OA, OC, OD, NA, NC, ND).
 *
 *     Then no matter what we करो to subvolume tree X, qgroup numbers will
 *     still be correct.
 *     Then NA's record gets removed from X's swapped_blocks.
 *
 * 4)  Transaction commit
 *     Any record in X's swapped_blocks माला_लो हटाओd, since there is no
 *     modअगरication to the swapped subtrees, no need to trigger heavy qgroup
 *     subtree rescan क्रम them.
 */

/*
 * Record a dirty extent, and info qgroup to update quota on it
 * TODO: Use kmem cache to alloc it.
 */
काष्ठा btrfs_qgroup_extent_record अणु
	काष्ठा rb_node node;
	u64 bytenr;
	u64 num_bytes;

	/*
	 * For qgroup reserved data space मुक्तing.
	 *
	 * @data_rsv_refroot and @data_rsv will be recorded after
	 * BTRFS_ADD_DELAYED_EXTENT is called.
	 * And will be used to मुक्त reserved qgroup space at
	 * transaction commit समय.
	 */
	u32 data_rsv;		/* reserved data space needs to be मुक्तd */
	u64 data_rsv_refroot;	/* which root the reserved data beदीर्घs to */
	काष्ठा ulist *old_roots;
पूर्ण;

काष्ठा btrfs_qgroup_swapped_block अणु
	काष्ठा rb_node node;

	पूर्णांक level;
	bool trace_leaf;

	/* bytenr/generation of the tree block in subvolume tree after swap */
	u64 subvol_bytenr;
	u64 subvol_generation;

	/* bytenr/generation of the tree block in reloc tree after swap */
	u64 reloc_bytenr;
	u64 reloc_generation;

	u64 last_snapshot;
	काष्ठा btrfs_key first_key;
पूर्ण;

/*
 * Qgroup reservation types:
 *
 * DATA:
 *	space reserved क्रम data
 *
 * META_PERTRANS:
 * 	Space reserved क्रम metadata (per-transaction)
 * 	Due to the fact that qgroup data is only updated at transaction commit
 * 	समय, reserved space क्रम metadata must be kept until transaction
 * 	commits.
 * 	Any metadata reserved that are used in btrfs_start_transaction() should
 * 	be of this type.
 *
 * META_PREALLOC:
 *	There are हालs where metadata space is reserved beक्रमe starting
 *	transaction, and then btrfs_join_transaction() to get a trans handle.
 *	Any metadata reserved क्रम such usage should be of this type.
 *	And after join_transaction() part (or all) of such reservation should
 *	be converted पूर्णांकo META_PERTRANS.
 */
क्रमागत btrfs_qgroup_rsv_type अणु
	BTRFS_QGROUP_RSV_DATA,
	BTRFS_QGROUP_RSV_META_PERTRANS,
	BTRFS_QGROUP_RSV_META_PREALLOC,
	BTRFS_QGROUP_RSV_LAST,
पूर्ण;

/*
 * Represents how many bytes we have reserved क्रम this qgroup.
 *
 * Each type should have dअगरferent reservation behavior.
 * E.g, data follows its io_tree flag modअगरication, जबतक
 * *currently* meta is just reserve-and-clear during transaction.
 *
 * TODO: Add new type क्रम reservation which can survive transaction commit.
 * Current metadata reservation behavior is not suitable क्रम such हाल.
 */
काष्ठा btrfs_qgroup_rsv अणु
	u64 values[BTRFS_QGROUP_RSV_LAST];
पूर्ण;

/*
 * one काष्ठा क्रम each qgroup, organized in fs_info->qgroup_tree.
 */
काष्ठा btrfs_qgroup अणु
	u64 qgroupid;

	/*
	 * state
	 */
	u64 rfer;	/* referenced */
	u64 rfer_cmpr;	/* referenced compressed */
	u64 excl;	/* exclusive */
	u64 excl_cmpr;	/* exclusive compressed */

	/*
	 * limits
	 */
	u64 lim_flags;	/* which limits are set */
	u64 max_rfer;
	u64 max_excl;
	u64 rsv_rfer;
	u64 rsv_excl;

	/*
	 * reservation tracking
	 */
	काष्ठा btrfs_qgroup_rsv rsv;

	/*
	 * lists
	 */
	काष्ठा list_head groups;  /* groups this group is member of */
	काष्ठा list_head members; /* groups that are members of this group */
	काष्ठा list_head dirty;   /* dirty groups */
	काष्ठा rb_node node;	  /* tree of qgroups */

	/*
	 * temp variables क्रम accounting operations
	 * Refer to qgroup_shared_accounting() क्रम details.
	 */
	u64 old_refcnt;
	u64 new_refcnt;

	/*
	 * Sysfs kobjectid
	 */
	काष्ठा kobject kobj;
पूर्ण;

अटल अंतरभूत u64 btrfs_qgroup_subvolid(u64 qgroupid)
अणु
	वापस (qgroupid & ((1ULL << BTRFS_QGROUP_LEVEL_SHIFT) - 1));
पूर्ण

/*
 * For qgroup event trace poपूर्णांकs only
 */
#घोषणा QGROUP_RESERVE		(1<<0)
#घोषणा QGROUP_RELEASE		(1<<1)
#घोषणा QGROUP_FREE		(1<<2)

पूर्णांक btrfs_quota_enable(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_quota_disable(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_qgroup_rescan(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_qgroup_rescan_resume(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_qgroup_रुको_क्रम_completion(काष्ठा btrfs_fs_info *fs_info,
				     bool पूर्णांकerruptible);
पूर्णांक btrfs_add_qgroup_relation(काष्ठा btrfs_trans_handle *trans, u64 src,
			      u64 dst);
पूर्णांक btrfs_del_qgroup_relation(काष्ठा btrfs_trans_handle *trans, u64 src,
			      u64 dst);
पूर्णांक btrfs_create_qgroup(काष्ठा btrfs_trans_handle *trans, u64 qgroupid);
पूर्णांक btrfs_हटाओ_qgroup(काष्ठा btrfs_trans_handle *trans, u64 qgroupid);
पूर्णांक btrfs_limit_qgroup(काष्ठा btrfs_trans_handle *trans, u64 qgroupid,
		       काष्ठा btrfs_qgroup_limit *limit);
पूर्णांक btrfs_पढ़ो_qgroup_config(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_मुक्त_qgroup_config(काष्ठा btrfs_fs_info *fs_info);
काष्ठा btrfs_delayed_extent_op;

/*
 * Inक्रमm qgroup to trace one dirty extent, its info is recorded in @record.
 * So qgroup can account it at transaction committing समय.
 *
 * No lock version, caller must acquire delayed ref lock and allocated memory,
 * then call btrfs_qgroup_trace_extent_post() after निकासing lock context.
 *
 * Return 0 क्रम success insert
 * Return >0 क्रम existing record, caller can मुक्त @record safely.
 * Error is not possible
 */
पूर्णांक btrfs_qgroup_trace_extent_nolock(
		काष्ठा btrfs_fs_info *fs_info,
		काष्ठा btrfs_delayed_ref_root *delayed_refs,
		काष्ठा btrfs_qgroup_extent_record *record);

/*
 * Post handler after qgroup_trace_extent_nolock().
 *
 * NOTE: Current qgroup करोes the expensive backref walk at transaction
 * committing समय with TRANS_STATE_COMMIT_DOING, this blocks incoming
 * new transaction.
 * This is deचिन्हित to allow btrfs_find_all_roots() to get correct new_roots
 * result.
 *
 * However क्रम old_roots there is no need to करो backref walk at that समय,
 * since we search commit roots to walk backref and result will always be
 * correct.
 *
 * Due to the nature of no lock version, we can't करो backref there.
 * So we must call btrfs_qgroup_trace_extent_post() after निकासing
 * spinlock context.
 *
 * TODO: If we can fix and prove btrfs_find_all_roots() can get correct result
 * using current root, then we can move all expensive backref walk out of
 * transaction committing, but not now as qgroup accounting will be wrong again.
 */
पूर्णांक btrfs_qgroup_trace_extent_post(काष्ठा btrfs_fs_info *fs_info,
				   काष्ठा btrfs_qgroup_extent_record *qrecord);

/*
 * Inक्रमm qgroup to trace one dirty extent, specअगरied by @bytenr and
 * @num_bytes.
 * So qgroup can account it at commit trans समय.
 *
 * Better encapsulated version, with memory allocation and backref walk क्रम
 * commit roots.
 * So this can sleep.
 *
 * Return 0 अगर the operation is करोne.
 * Return <0 क्रम error, like memory allocation failure or invalid parameter
 * (शून्य trans)
 */
पूर्णांक btrfs_qgroup_trace_extent(काष्ठा btrfs_trans_handle *trans, u64 bytenr,
			      u64 num_bytes, gfp_t gfp_flag);

/*
 * Inक्रमm qgroup to trace all leaf items of data
 *
 * Return 0 क्रम success
 * Return <0 क्रम error(ENOMEM)
 */
पूर्णांक btrfs_qgroup_trace_leaf_items(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा extent_buffer *eb);
/*
 * Inक्रमm qgroup to trace a whole subtree, including all its child tree
 * blocks and data.
 * The root tree block is specअगरied by @root_eb.
 *
 * Normally used by relocation(tree block swap) and subvolume deletion.
 *
 * Return 0 क्रम success
 * Return <0 क्रम error(ENOMEM or tree search error)
 */
पूर्णांक btrfs_qgroup_trace_subtree(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा extent_buffer *root_eb,
			       u64 root_gen, पूर्णांक root_level);
पूर्णांक btrfs_qgroup_account_extent(काष्ठा btrfs_trans_handle *trans, u64 bytenr,
				u64 num_bytes, काष्ठा ulist *old_roots,
				काष्ठा ulist *new_roots);
पूर्णांक btrfs_qgroup_account_extents(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_run_qgroups(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_qgroup_inherit(काष्ठा btrfs_trans_handle *trans, u64 srcid,
			 u64 objectid, काष्ठा btrfs_qgroup_inherit *inherit);
व्योम btrfs_qgroup_मुक्त_refroot(काष्ठा btrfs_fs_info *fs_info,
			       u64 ref_root, u64 num_bytes,
			       क्रमागत btrfs_qgroup_rsv_type type);

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
पूर्णांक btrfs_verअगरy_qgroup_counts(काष्ठा btrfs_fs_info *fs_info, u64 qgroupid,
			       u64 rfer, u64 excl);
#पूर्ण_अगर

/* New io_tree based accurate qgroup reserve API */
पूर्णांक btrfs_qgroup_reserve_data(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset **reserved, u64 start, u64 len);
पूर्णांक btrfs_qgroup_release_data(काष्ठा btrfs_inode *inode, u64 start, u64 len);
पूर्णांक btrfs_qgroup_मुक्त_data(काष्ठा btrfs_inode *inode,
			   काष्ठा extent_changeset *reserved, u64 start,
			   u64 len);
पूर्णांक btrfs_qgroup_reserve_meta(काष्ठा btrfs_root *root, पूर्णांक num_bytes,
			      क्रमागत btrfs_qgroup_rsv_type type, bool enक्रमce);
पूर्णांक __btrfs_qgroup_reserve_meta(काष्ठा btrfs_root *root, पूर्णांक num_bytes,
				क्रमागत btrfs_qgroup_rsv_type type, bool enक्रमce);
/* Reserve metadata space क्रम pertrans and pपुनः_स्मृति type */
अटल अंतरभूत पूर्णांक btrfs_qgroup_reserve_meta_pertrans(काष्ठा btrfs_root *root,
				पूर्णांक num_bytes, bool enक्रमce)
अणु
	वापस __btrfs_qgroup_reserve_meta(root, num_bytes,
			BTRFS_QGROUP_RSV_META_PERTRANS, enक्रमce);
पूर्ण
अटल अंतरभूत पूर्णांक btrfs_qgroup_reserve_meta_pपुनः_स्मृति(काष्ठा btrfs_root *root,
				पूर्णांक num_bytes, bool enक्रमce)
अणु
	वापस __btrfs_qgroup_reserve_meta(root, num_bytes,
			BTRFS_QGROUP_RSV_META_PREALLOC, enक्रमce);
पूर्ण

व्योम __btrfs_qgroup_मुक्त_meta(काष्ठा btrfs_root *root, पूर्णांक num_bytes,
			     क्रमागत btrfs_qgroup_rsv_type type);

/* Free per-transaction meta reservation क्रम error handling */
अटल अंतरभूत व्योम btrfs_qgroup_मुक्त_meta_pertrans(काष्ठा btrfs_root *root,
						   पूर्णांक num_bytes)
अणु
	__btrfs_qgroup_मुक्त_meta(root, num_bytes,
			BTRFS_QGROUP_RSV_META_PERTRANS);
पूर्ण

/* Pre-allocated meta reservation can be मुक्तd at need */
अटल अंतरभूत व्योम btrfs_qgroup_मुक्त_meta_pपुनः_स्मृति(काष्ठा btrfs_root *root,
						   पूर्णांक num_bytes)
अणु
	__btrfs_qgroup_मुक्त_meta(root, num_bytes,
			BTRFS_QGROUP_RSV_META_PREALLOC);
पूर्ण

/*
 * Per-transaction meta reservation should be all मुक्तd at transaction commit
 * समय
 */
व्योम btrfs_qgroup_मुक्त_meta_all_pertrans(काष्ठा btrfs_root *root);

/*
 * Convert @num_bytes of META_PREALLOCATED reservation to META_PERTRANS.
 *
 * This is called when pपुनः_स्मृतिated meta reservation needs to be used.
 * Normally after btrfs_join_transaction() call.
 */
व्योम btrfs_qgroup_convert_reserved_meta(काष्ठा btrfs_root *root, पूर्णांक num_bytes);

व्योम btrfs_qgroup_check_reserved_leak(काष्ठा btrfs_inode *inode);

/* btrfs_qgroup_swapped_blocks related functions */
व्योम btrfs_qgroup_init_swapped_blocks(
	काष्ठा btrfs_qgroup_swapped_blocks *swapped_blocks);

व्योम btrfs_qgroup_clean_swapped_blocks(काष्ठा btrfs_root *root);
पूर्णांक btrfs_qgroup_add_swapped_blocks(काष्ठा btrfs_trans_handle *trans,
		काष्ठा btrfs_root *subvol_root,
		काष्ठा btrfs_block_group *bg,
		काष्ठा extent_buffer *subvol_parent, पूर्णांक subvol_slot,
		काष्ठा extent_buffer *reloc_parent, पूर्णांक reloc_slot,
		u64 last_snapshot);
पूर्णांक btrfs_qgroup_trace_subtree_after_cow(काष्ठा btrfs_trans_handle *trans,
		काष्ठा btrfs_root *root, काष्ठा extent_buffer *eb);
व्योम btrfs_qgroup_destroy_extent_records(काष्ठा btrfs_transaction *trans);
bool btrfs_check_quota_leak(काष्ठा btrfs_fs_info *fs_info);

#पूर्ण_अगर
