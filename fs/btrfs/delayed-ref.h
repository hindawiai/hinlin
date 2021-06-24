<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_DELAYED_REF_H
#घोषणा BTRFS_DELAYED_REF_H

#समावेश <linux/refcount.h>

/* these are the possible values of काष्ठा btrfs_delayed_ref_node->action */
#घोषणा BTRFS_ADD_DELAYED_REF    1 /* add one backref to the tree */
#घोषणा BTRFS_DROP_DELAYED_REF   2 /* delete one backref from the tree */
#घोषणा BTRFS_ADD_DELAYED_EXTENT 3 /* record a full extent allocation */
#घोषणा BTRFS_UPDATE_DELAYED_HEAD 4 /* not changing ref count on head ref */

काष्ठा btrfs_delayed_ref_node अणु
	काष्ठा rb_node ref_node;
	/*
	 * If action is BTRFS_ADD_DELAYED_REF, also link this node to
	 * ref_head->ref_add_list, then we करो not need to iterate the
	 * whole ref_head->ref_list to find BTRFS_ADD_DELAYED_REF nodes.
	 */
	काष्ठा list_head add_list;

	/* the starting bytenr of the extent */
	u64 bytenr;

	/* the size of the extent */
	u64 num_bytes;

	/* seq number to keep track of insertion order */
	u64 seq;

	/* ref count on this data काष्ठाure */
	refcount_t refs;

	/*
	 * how many refs is this entry adding or deleting.  For
	 * head refs, this may be a negative number because it is keeping
	 * track of the total mods करोne to the reference count.
	 * For inभागidual refs, this will always be a positive number
	 *
	 * It may be more than one, since it is possible क्रम a single
	 * parent to have more than one ref on an extent
	 */
	पूर्णांक ref_mod;

	अचिन्हित पूर्णांक action:8;
	अचिन्हित पूर्णांक type:8;
	/* is this node still in the rbtree? */
	अचिन्हित पूर्णांक is_head:1;
	अचिन्हित पूर्णांक in_tree:1;
पूर्ण;

काष्ठा btrfs_delayed_extent_op अणु
	काष्ठा btrfs_disk_key key;
	u8 level;
	bool update_key;
	bool update_flags;
	bool is_data;
	u64 flags_to_set;
पूर्ण;

/*
 * the head refs are used to hold a lock on a given extent, which allows us
 * to make sure that only one process is running the delayed refs
 * at a समय क्रम a single extent.  They also store the sum of all the
 * reference count modअगरications we've queued up.
 */
काष्ठा btrfs_delayed_ref_head अणु
	u64 bytenr;
	u64 num_bytes;
	refcount_t refs;
	/*
	 * the mutex is held जबतक running the refs, and it is also
	 * held when checking the sum of reference modअगरications.
	 */
	काष्ठा mutex mutex;

	spinlock_t lock;
	काष्ठा rb_root_cached ref_tree;
	/* accumulate add BTRFS_ADD_DELAYED_REF nodes to this ref_add_list. */
	काष्ठा list_head ref_add_list;

	काष्ठा rb_node href_node;

	काष्ठा btrfs_delayed_extent_op *extent_op;

	/*
	 * This is used to track the final ref_mod from all the refs associated
	 * with this head ref, this is not adjusted as delayed refs are run,
	 * this is meant to track अगर we need to करो the csum accounting or not.
	 */
	पूर्णांक total_ref_mod;

	/*
	 * This is the current outstanding mod references क्रम this bytenr.  This
	 * is used with lookup_extent_info to get an accurate reference count
	 * क्रम a bytenr, so it is adjusted as delayed refs are run so that any
	 * on disk reference count + ref_mod is accurate.
	 */
	पूर्णांक ref_mod;

	/*
	 * when a new extent is allocated, it is just reserved in memory
	 * The actual extent isn't inserted पूर्णांकo the extent allocation tree
	 * until the delayed ref is processed.  must_insert_reserved is
	 * used to flag a delayed ref so the accounting can be updated
	 * when a full insert is करोne.
	 *
	 * It is possible the extent will be मुक्तd beक्रमe it is ever
	 * inserted पूर्णांकo the extent allocation tree.  In this हाल
	 * we need to update the in ram accounting to properly reflect
	 * the मुक्त has happened.
	 */
	अचिन्हित पूर्णांक must_insert_reserved:1;
	अचिन्हित पूर्णांक is_data:1;
	अचिन्हित पूर्णांक is_प्रणाली:1;
	अचिन्हित पूर्णांक processing:1;
पूर्ण;

काष्ठा btrfs_delayed_tree_ref अणु
	काष्ठा btrfs_delayed_ref_node node;
	u64 root;
	u64 parent;
	पूर्णांक level;
पूर्ण;

काष्ठा btrfs_delayed_data_ref अणु
	काष्ठा btrfs_delayed_ref_node node;
	u64 root;
	u64 parent;
	u64 objectid;
	u64 offset;
पूर्ण;

क्रमागत btrfs_delayed_ref_flags अणु
	/* Indicate that we are flushing delayed refs क्रम the commit */
	BTRFS_DELAYED_REFS_FLUSHING,
पूर्ण;

काष्ठा btrfs_delayed_ref_root अणु
	/* head ref rbtree */
	काष्ठा rb_root_cached href_root;

	/* dirty extent records */
	काष्ठा rb_root dirty_extent_root;

	/* this spin lock protects the rbtree and the entries inside */
	spinlock_t lock;

	/* how many delayed ref updates we've queued, used by the
	 * throttling code
	 */
	atomic_t num_entries;

	/* total number of head nodes in tree */
	अचिन्हित दीर्घ num_heads;

	/* total number of head nodes पढ़ोy क्रम processing */
	अचिन्हित दीर्घ num_heads_पढ़ोy;

	u64 pending_csums;

	अचिन्हित दीर्घ flags;

	u64 run_delayed_start;

	/*
	 * To make qgroup to skip given root.
	 * This is क्रम snapshot, as btrfs_qgroup_inherit() will manually
	 * modअगरy counters क्रम snapshot and its source, so we should skip
	 * the snapshot in new_root/old_roots or it will get calculated twice
	 */
	u64 qgroup_to_skip;
पूर्ण;

क्रमागत btrfs_ref_type अणु
	BTRFS_REF_NOT_SET,
	BTRFS_REF_DATA,
	BTRFS_REF_METADATA,
	BTRFS_REF_LAST,
पूर्ण;

काष्ठा btrfs_data_ref अणु
	/* For EXTENT_DATA_REF */

	/* Root which refers to this data extent */
	u64 ref_root;

	/* Inode which refers to this data extent */
	u64 ino;

	/*
	 * file_offset - extent_offset
	 *
	 * file_offset is the key.offset of the EXTENT_DATA key.
	 * extent_offset is btrfs_file_extent_offset() of the EXTENT_DATA data.
	 */
	u64 offset;
पूर्ण;

काष्ठा btrfs_tree_ref अणु
	/*
	 * Level of this tree block
	 *
	 * Shared क्रम skinny (TREE_BLOCK_REF) and normal tree ref.
	 */
	पूर्णांक level;

	/*
	 * Root which refers to this tree block.
	 *
	 * For TREE_BLOCK_REF (skinny metadata, either अंतरभूत or keyed)
	 */
	u64 root;

	/* For non-skinny metadata, no special member needed */
पूर्ण;

काष्ठा btrfs_ref अणु
	क्रमागत btrfs_ref_type type;
	पूर्णांक action;

	/*
	 * Whether this extent should go through qgroup record.
	 *
	 * Normally false, but क्रम certain हालs like delayed subtree scan,
	 * setting this flag can hugely reduce qgroup overhead.
	 */
	bool skip_qgroup;

	/*
	 * Optional. For which root is this modअगरication.
	 * Mostly used क्रम qgroup optimization.
	 *
	 * When unset, data/tree ref init code will populate it.
	 * In certain हालs, we're modअगरying reference क्रम a dअगरferent root.
	 * E.g. COW fs tree blocks क्रम balance.
	 * In that हाल, tree_ref::root will be fs tree, but we're करोing this
	 * क्रम reloc tree, then we should set @real_root to reloc tree.
	 */
	u64 real_root;
	u64 bytenr;
	u64 len;

	/* Bytenr of the parent tree block */
	u64 parent;
	जोड़ अणु
		काष्ठा btrfs_data_ref data_ref;
		काष्ठा btrfs_tree_ref tree_ref;
	पूर्ण;
पूर्ण;

बाह्य काष्ठा kmem_cache *btrfs_delayed_ref_head_cachep;
बाह्य काष्ठा kmem_cache *btrfs_delayed_tree_ref_cachep;
बाह्य काष्ठा kmem_cache *btrfs_delayed_data_ref_cachep;
बाह्य काष्ठा kmem_cache *btrfs_delayed_extent_op_cachep;

पूर्णांक __init btrfs_delayed_ref_init(व्योम);
व्योम __cold btrfs_delayed_ref_निकास(व्योम);

अटल अंतरभूत व्योम btrfs_init_generic_ref(काष्ठा btrfs_ref *generic_ref,
				पूर्णांक action, u64 bytenr, u64 len, u64 parent)
अणु
	generic_ref->action = action;
	generic_ref->bytenr = bytenr;
	generic_ref->len = len;
	generic_ref->parent = parent;
पूर्ण

अटल अंतरभूत व्योम btrfs_init_tree_ref(काष्ठा btrfs_ref *generic_ref,
				पूर्णांक level, u64 root)
अणु
	/* If @real_root not set, use @root as fallback */
	अगर (!generic_ref->real_root)
		generic_ref->real_root = root;
	generic_ref->tree_ref.level = level;
	generic_ref->tree_ref.root = root;
	generic_ref->type = BTRFS_REF_METADATA;
पूर्ण

अटल अंतरभूत व्योम btrfs_init_data_ref(काष्ठा btrfs_ref *generic_ref,
				u64 ref_root, u64 ino, u64 offset)
अणु
	/* If @real_root not set, use @root as fallback */
	अगर (!generic_ref->real_root)
		generic_ref->real_root = ref_root;
	generic_ref->data_ref.ref_root = ref_root;
	generic_ref->data_ref.ino = ino;
	generic_ref->data_ref.offset = offset;
	generic_ref->type = BTRFS_REF_DATA;
पूर्ण

अटल अंतरभूत काष्ठा btrfs_delayed_extent_op *
btrfs_alloc_delayed_extent_op(व्योम)
अणु
	वापस kmem_cache_alloc(btrfs_delayed_extent_op_cachep, GFP_NOFS);
पूर्ण

अटल अंतरभूत व्योम
btrfs_मुक्त_delayed_extent_op(काष्ठा btrfs_delayed_extent_op *op)
अणु
	अगर (op)
		kmem_cache_मुक्त(btrfs_delayed_extent_op_cachep, op);
पूर्ण

अटल अंतरभूत व्योम btrfs_put_delayed_ref(काष्ठा btrfs_delayed_ref_node *ref)
अणु
	WARN_ON(refcount_पढ़ो(&ref->refs) == 0);
	अगर (refcount_dec_and_test(&ref->refs)) अणु
		WARN_ON(ref->in_tree);
		चयन (ref->type) अणु
		हाल BTRFS_TREE_BLOCK_REF_KEY:
		हाल BTRFS_SHARED_BLOCK_REF_KEY:
			kmem_cache_मुक्त(btrfs_delayed_tree_ref_cachep, ref);
			अवरोध;
		हाल BTRFS_EXTENT_DATA_REF_KEY:
		हाल BTRFS_SHARED_DATA_REF_KEY:
			kmem_cache_मुक्त(btrfs_delayed_data_ref_cachep, ref);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत u64 btrfs_ref_head_to_space_flags(
				काष्ठा btrfs_delayed_ref_head *head_ref)
अणु
	अगर (head_ref->is_data)
		वापस BTRFS_BLOCK_GROUP_DATA;
	अन्यथा अगर (head_ref->is_प्रणाली)
		वापस BTRFS_BLOCK_GROUP_SYSTEM;
	वापस BTRFS_BLOCK_GROUP_METADATA;
पूर्ण

अटल अंतरभूत व्योम btrfs_put_delayed_ref_head(काष्ठा btrfs_delayed_ref_head *head)
अणु
	अगर (refcount_dec_and_test(&head->refs))
		kmem_cache_मुक्त(btrfs_delayed_ref_head_cachep, head);
पूर्ण

पूर्णांक btrfs_add_delayed_tree_ref(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_ref *generic_ref,
			       काष्ठा btrfs_delayed_extent_op *extent_op);
पूर्णांक btrfs_add_delayed_data_ref(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_ref *generic_ref,
			       u64 reserved);
पूर्णांक btrfs_add_delayed_extent_op(काष्ठा btrfs_trans_handle *trans,
				u64 bytenr, u64 num_bytes,
				काष्ठा btrfs_delayed_extent_op *extent_op);
व्योम btrfs_merge_delayed_refs(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_delayed_ref_root *delayed_refs,
			      काष्ठा btrfs_delayed_ref_head *head);

काष्ठा btrfs_delayed_ref_head *
btrfs_find_delayed_ref_head(काष्ठा btrfs_delayed_ref_root *delayed_refs,
			    u64 bytenr);
पूर्णांक btrfs_delayed_ref_lock(काष्ठा btrfs_delayed_ref_root *delayed_refs,
			   काष्ठा btrfs_delayed_ref_head *head);
अटल अंतरभूत व्योम btrfs_delayed_ref_unlock(काष्ठा btrfs_delayed_ref_head *head)
अणु
	mutex_unlock(&head->mutex);
पूर्ण
व्योम btrfs_delete_ref_head(काष्ठा btrfs_delayed_ref_root *delayed_refs,
			   काष्ठा btrfs_delayed_ref_head *head);

काष्ठा btrfs_delayed_ref_head *btrfs_select_ref_head(
		काष्ठा btrfs_delayed_ref_root *delayed_refs);

पूर्णांक btrfs_check_delayed_seq(काष्ठा btrfs_fs_info *fs_info, u64 seq);

व्योम btrfs_delayed_refs_rsv_release(काष्ठा btrfs_fs_info *fs_info, पूर्णांक nr);
व्योम btrfs_update_delayed_refs_rsv(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_delayed_refs_rsv_refill(काष्ठा btrfs_fs_info *fs_info,
				  क्रमागत btrfs_reserve_flush_क्रमागत flush);
व्योम btrfs_migrate_to_delayed_refs_rsv(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा btrfs_block_rsv *src,
				       u64 num_bytes);
पूर्णांक btrfs_should_throttle_delayed_refs(काष्ठा btrfs_trans_handle *trans);
bool btrfs_check_space_क्रम_delayed_refs(काष्ठा btrfs_fs_info *fs_info);

/*
 * helper functions to cast a node पूर्णांकo its container
 */
अटल अंतरभूत काष्ठा btrfs_delayed_tree_ref *
btrfs_delayed_node_to_tree_ref(काष्ठा btrfs_delayed_ref_node *node)
अणु
	वापस container_of(node, काष्ठा btrfs_delayed_tree_ref, node);
पूर्ण

अटल अंतरभूत काष्ठा btrfs_delayed_data_ref *
btrfs_delayed_node_to_data_ref(काष्ठा btrfs_delayed_ref_node *node)
अणु
	वापस container_of(node, काष्ठा btrfs_delayed_data_ref, node);
पूर्ण

#पूर्ण_अगर
