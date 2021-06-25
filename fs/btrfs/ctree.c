<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007,2008 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/mm.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "print-tree.h"
#समावेश "locking.h"
#समावेश "volumes.h"
#समावेश "qgroup.h"
#समावेश "tree-mod-log.h"

अटल पूर्णांक split_node(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root
		      *root, काष्ठा btrfs_path *path, पूर्णांक level);
अटल पूर्णांक split_leaf(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		      स्थिर काष्ठा btrfs_key *ins_key, काष्ठा btrfs_path *path,
		      पूर्णांक data_size, पूर्णांक extend);
अटल पूर्णांक push_node_left(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा extent_buffer *dst,
			  काष्ठा extent_buffer *src, पूर्णांक empty);
अटल पूर्णांक balance_node_right(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा extent_buffer *dst_buf,
			      काष्ठा extent_buffer *src_buf);
अटल व्योम del_ptr(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
		    पूर्णांक level, पूर्णांक slot);

अटल स्थिर काष्ठा btrfs_csums अणु
	u16		size;
	स्थिर अक्षर	name[10];
	स्थिर अक्षर	driver[12];
पूर्ण btrfs_csums[] = अणु
	[BTRFS_CSUM_TYPE_CRC32] = अणु .size = 4, .name = "crc32c" पूर्ण,
	[BTRFS_CSUM_TYPE_XXHASH] = अणु .size = 8, .name = "xxhash64" पूर्ण,
	[BTRFS_CSUM_TYPE_SHA256] = अणु .size = 32, .name = "sha256" पूर्ण,
	[BTRFS_CSUM_TYPE_BLAKE2] = अणु .size = 32, .name = "blake2b",
				     .driver = "blake2b-256" पूर्ण,
पूर्ण;

पूर्णांक btrfs_super_csum_size(स्थिर काष्ठा btrfs_super_block *s)
अणु
	u16 t = btrfs_super_csum_type(s);
	/*
	 * csum type is validated at mount समय
	 */
	वापस btrfs_csums[t].size;
पूर्ण

स्थिर अक्षर *btrfs_super_csum_name(u16 csum_type)
अणु
	/* csum type is validated at mount समय */
	वापस btrfs_csums[csum_type].name;
पूर्ण

/*
 * Return driver name अगर defined, otherwise the name that's also a valid driver
 * name
 */
स्थिर अक्षर *btrfs_super_csum_driver(u16 csum_type)
अणु
	/* csum type is validated at mount समय */
	वापस btrfs_csums[csum_type].driver[0] ?
		btrfs_csums[csum_type].driver :
		btrfs_csums[csum_type].name;
पूर्ण

माप_प्रकार __attribute_स्थिर__ btrfs_get_num_csums(व्योम)
अणु
	वापस ARRAY_SIZE(btrfs_csums);
पूर्ण

काष्ठा btrfs_path *btrfs_alloc_path(व्योम)
अणु
	वापस kmem_cache_zalloc(btrfs_path_cachep, GFP_NOFS);
पूर्ण

/* this also releases the path */
व्योम btrfs_मुक्त_path(काष्ठा btrfs_path *p)
अणु
	अगर (!p)
		वापस;
	btrfs_release_path(p);
	kmem_cache_मुक्त(btrfs_path_cachep, p);
पूर्ण

/*
 * path release drops references on the extent buffers in the path
 * and it drops any locks held by this path
 *
 * It is safe to call this on paths that no locks or extent buffers held.
 */
noअंतरभूत व्योम btrfs_release_path(काष्ठा btrfs_path *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_MAX_LEVEL; i++) अणु
		p->slots[i] = 0;
		अगर (!p->nodes[i])
			जारी;
		अगर (p->locks[i]) अणु
			btrfs_tree_unlock_rw(p->nodes[i], p->locks[i]);
			p->locks[i] = 0;
		पूर्ण
		मुक्त_extent_buffer(p->nodes[i]);
		p->nodes[i] = शून्य;
	पूर्ण
पूर्ण

/*
 * safely माला_लो a reference on the root node of a tree.  A lock
 * is not taken, so a concurrent ग_लिखोr may put a dअगरferent node
 * at the root of the tree.  See btrfs_lock_root_node क्रम the
 * looping required.
 *
 * The extent buffer वापसed by this has a reference taken, so
 * it won't disappear.  It may stop being the root of the tree
 * at any समय because there are no locks held.
 */
काष्ठा extent_buffer *btrfs_root_node(काष्ठा btrfs_root *root)
अणु
	काष्ठा extent_buffer *eb;

	जबतक (1) अणु
		rcu_पढ़ो_lock();
		eb = rcu_dereference(root->node);

		/*
		 * RCU really hurts here, we could मुक्त up the root node because
		 * it was COWed but we may not get the new root node yet so करो
		 * the inc_not_zero dance and अगर it करोesn't work then
		 * synchronize_rcu and try again.
		 */
		अगर (atomic_inc_not_zero(&eb->refs)) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण
		rcu_पढ़ो_unlock();
		synchronize_rcu();
	पूर्ण
	वापस eb;
पूर्ण

/*
 * Cowonly root (not-shareable trees, everything not subvolume or reloc roots),
 * just get put onto a simple dirty list.  Transaction walks this list to make
 * sure they get properly updated on disk.
 */
अटल व्योम add_root_to_dirty_list(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	अगर (test_bit(BTRFS_ROOT_सूचीTY, &root->state) ||
	    !test_bit(BTRFS_ROOT_TRACK_सूचीTY, &root->state))
		वापस;

	spin_lock(&fs_info->trans_lock);
	अगर (!test_and_set_bit(BTRFS_ROOT_सूचीTY, &root->state)) अणु
		/* Want the extent tree to be the last on the list */
		अगर (root->root_key.objectid == BTRFS_EXTENT_TREE_OBJECTID)
			list_move_tail(&root->dirty_list,
				       &fs_info->dirty_cowonly_roots);
		अन्यथा
			list_move(&root->dirty_list,
				  &fs_info->dirty_cowonly_roots);
	पूर्ण
	spin_unlock(&fs_info->trans_lock);
पूर्ण

/*
 * used by snapshot creation to make a copy of a root क्रम a tree with
 * a given objectid.  The buffer with the new root node is वापसed in
 * cow_ret, and this func वापसs zero on success or a negative error code.
 */
पूर्णांक btrfs_copy_root(काष्ठा btrfs_trans_handle *trans,
		      काष्ठा btrfs_root *root,
		      काष्ठा extent_buffer *buf,
		      काष्ठा extent_buffer **cow_ret, u64 new_root_objectid)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *cow;
	पूर्णांक ret = 0;
	पूर्णांक level;
	काष्ठा btrfs_disk_key disk_key;

	WARN_ON(test_bit(BTRFS_ROOT_SHAREABLE, &root->state) &&
		trans->transid != fs_info->running_transaction->transid);
	WARN_ON(test_bit(BTRFS_ROOT_SHAREABLE, &root->state) &&
		trans->transid != root->last_trans);

	level = btrfs_header_level(buf);
	अगर (level == 0)
		btrfs_item_key(buf, &disk_key, 0);
	अन्यथा
		btrfs_node_key(buf, &disk_key, 0);

	cow = btrfs_alloc_tree_block(trans, root, 0, new_root_objectid,
				     &disk_key, level, buf->start, 0,
				     BTRFS_NESTING_NEW_ROOT);
	अगर (IS_ERR(cow))
		वापस PTR_ERR(cow);

	copy_extent_buffer_full(cow, buf);
	btrfs_set_header_bytenr(cow, cow->start);
	btrfs_set_header_generation(cow, trans->transid);
	btrfs_set_header_backref_rev(cow, BTRFS_MIXED_BACKREF_REV);
	btrfs_clear_header_flag(cow, BTRFS_HEADER_FLAG_WRITTEN |
				     BTRFS_HEADER_FLAG_RELOC);
	अगर (new_root_objectid == BTRFS_TREE_RELOC_OBJECTID)
		btrfs_set_header_flag(cow, BTRFS_HEADER_FLAG_RELOC);
	अन्यथा
		btrfs_set_header_owner(cow, new_root_objectid);

	ग_लिखो_extent_buffer_fsid(cow, fs_info->fs_devices->metadata_uuid);

	WARN_ON(btrfs_header_generation(buf) > trans->transid);
	अगर (new_root_objectid == BTRFS_TREE_RELOC_OBJECTID)
		ret = btrfs_inc_ref(trans, root, cow, 1);
	अन्यथा
		ret = btrfs_inc_ref(trans, root, cow, 0);
	अगर (ret) अणु
		btrfs_tree_unlock(cow);
		मुक्त_extent_buffer(cow);
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण

	btrfs_mark_buffer_dirty(cow);
	*cow_ret = cow;
	वापस 0;
पूर्ण

/*
 * check अगर the tree block can be shared by multiple trees
 */
पूर्णांक btrfs_block_can_be_shared(काष्ठा btrfs_root *root,
			      काष्ठा extent_buffer *buf)
अणु
	/*
	 * Tree blocks not in shareable trees and tree roots are never shared.
	 * If a block was allocated after the last snapshot and the block was
	 * not allocated by tree relocation, we know the block is not shared.
	 */
	अगर (test_bit(BTRFS_ROOT_SHAREABLE, &root->state) &&
	    buf != root->node && buf != root->commit_root &&
	    (btrfs_header_generation(buf) <=
	     btrfs_root_last_snapshot(&root->root_item) ||
	     btrfs_header_flag(buf, BTRFS_HEADER_FLAG_RELOC)))
		वापस 1;

	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक update_ref_क्रम_cow(काष्ठा btrfs_trans_handle *trans,
				       काष्ठा btrfs_root *root,
				       काष्ठा extent_buffer *buf,
				       काष्ठा extent_buffer *cow,
				       पूर्णांक *last_ref)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 refs;
	u64 owner;
	u64 flags;
	u64 new_flags = 0;
	पूर्णांक ret;

	/*
	 * Backrefs update rules:
	 *
	 * Always use full backrefs क्रम extent poपूर्णांकers in tree block
	 * allocated by tree relocation.
	 *
	 * If a shared tree block is no दीर्घer referenced by its owner
	 * tree (btrfs_header_owner(buf) == root->root_key.objectid),
	 * use full backrefs क्रम extent poपूर्णांकers in tree block.
	 *
	 * If a tree block is been relocating
	 * (root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID),
	 * use full backrefs क्रम extent poपूर्णांकers in tree block.
	 * The reason क्रम this is some operations (such as drop tree)
	 * are only allowed क्रम blocks use full backrefs.
	 */

	अगर (btrfs_block_can_be_shared(root, buf)) अणु
		ret = btrfs_lookup_extent_info(trans, fs_info, buf->start,
					       btrfs_header_level(buf), 1,
					       &refs, &flags);
		अगर (ret)
			वापस ret;
		अगर (refs == 0) अणु
			ret = -EROFS;
			btrfs_handle_fs_error(fs_info, ret, शून्य);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		refs = 1;
		अगर (root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID ||
		    btrfs_header_backref_rev(buf) < BTRFS_MIXED_BACKREF_REV)
			flags = BTRFS_BLOCK_FLAG_FULL_BACKREF;
		अन्यथा
			flags = 0;
	पूर्ण

	owner = btrfs_header_owner(buf);
	BUG_ON(owner == BTRFS_TREE_RELOC_OBJECTID &&
	       !(flags & BTRFS_BLOCK_FLAG_FULL_BACKREF));

	अगर (refs > 1) अणु
		अगर ((owner == root->root_key.objectid ||
		     root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID) &&
		    !(flags & BTRFS_BLOCK_FLAG_FULL_BACKREF)) अणु
			ret = btrfs_inc_ref(trans, root, buf, 1);
			अगर (ret)
				वापस ret;

			अगर (root->root_key.objectid ==
			    BTRFS_TREE_RELOC_OBJECTID) अणु
				ret = btrfs_dec_ref(trans, root, buf, 0);
				अगर (ret)
					वापस ret;
				ret = btrfs_inc_ref(trans, root, cow, 1);
				अगर (ret)
					वापस ret;
			पूर्ण
			new_flags |= BTRFS_BLOCK_FLAG_FULL_BACKREF;
		पूर्ण अन्यथा अणु

			अगर (root->root_key.objectid ==
			    BTRFS_TREE_RELOC_OBJECTID)
				ret = btrfs_inc_ref(trans, root, cow, 1);
			अन्यथा
				ret = btrfs_inc_ref(trans, root, cow, 0);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (new_flags != 0) अणु
			पूर्णांक level = btrfs_header_level(buf);

			ret = btrfs_set_disk_extent_flags(trans, buf,
							  new_flags, level, 0);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (flags & BTRFS_BLOCK_FLAG_FULL_BACKREF) अणु
			अगर (root->root_key.objectid ==
			    BTRFS_TREE_RELOC_OBJECTID)
				ret = btrfs_inc_ref(trans, root, cow, 1);
			अन्यथा
				ret = btrfs_inc_ref(trans, root, cow, 0);
			अगर (ret)
				वापस ret;
			ret = btrfs_dec_ref(trans, root, buf, 1);
			अगर (ret)
				वापस ret;
		पूर्ण
		btrfs_clean_tree_block(buf);
		*last_ref = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा extent_buffer *alloc_tree_block_no_bg_flush(
					  काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_root *root,
					  u64 parent_start,
					  स्थिर काष्ठा btrfs_disk_key *disk_key,
					  पूर्णांक level,
					  u64 hपूर्णांक,
					  u64 empty_size,
					  क्रमागत btrfs_lock_nesting nest)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *ret;

	/*
	 * If we are COWing a node/leaf from the extent, chunk, device or मुक्त
	 * space trees, make sure that we करो not finish block group creation of
	 * pending block groups. We करो this to aव्योम a deadlock.
	 * COWing can result in allocation of a new chunk, and flushing pending
	 * block groups (btrfs_create_pending_block_groups()) can be triggered
	 * when finishing allocation of a new chunk. Creation of a pending block
	 * group modअगरies the extent, chunk, device and मुक्त space trees,
	 * thereक्रमe we could deadlock with ourselves since we are holding a
	 * lock on an extent buffer that btrfs_create_pending_block_groups() may
	 * try to COW later.
	 * For similar reasons, we also need to delay flushing pending block
	 * groups when splitting a leaf or node, from one of those trees, since
	 * we are holding a ग_लिखो lock on it and its parent or when inserting a
	 * new root node क्रम one of those trees.
	 */
	अगर (root == fs_info->extent_root ||
	    root == fs_info->chunk_root ||
	    root == fs_info->dev_root ||
	    root == fs_info->मुक्त_space_root)
		trans->can_flush_pending_bgs = false;

	ret = btrfs_alloc_tree_block(trans, root, parent_start,
				     root->root_key.objectid, disk_key, level,
				     hपूर्णांक, empty_size, nest);
	trans->can_flush_pending_bgs = true;

	वापस ret;
पूर्ण

/*
 * करोes the dirty work in cow of a single block.  The parent block (अगर
 * supplied) is updated to poपूर्णांक to the new cow copy.  The new buffer is marked
 * dirty and वापसed locked.  If you modअगरy the block it needs to be marked
 * dirty again.
 *
 * search_start -- an allocation hपूर्णांक क्रम the new block
 *
 * empty_size -- a hपूर्णांक that you plan on करोing more cow.  This is the size in
 * bytes the allocator should try to find मुक्त next to the block it वापसs.
 * This is just a hपूर्णांक and may be ignored by the allocator.
 */
अटल noअंतरभूत पूर्णांक __btrfs_cow_block(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     काष्ठा extent_buffer *buf,
			     काष्ठा extent_buffer *parent, पूर्णांक parent_slot,
			     काष्ठा extent_buffer **cow_ret,
			     u64 search_start, u64 empty_size,
			     क्रमागत btrfs_lock_nesting nest)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा extent_buffer *cow;
	पूर्णांक level, ret;
	पूर्णांक last_ref = 0;
	पूर्णांक unlock_orig = 0;
	u64 parent_start = 0;

	अगर (*cow_ret == buf)
		unlock_orig = 1;

	btrfs_निश्चित_tree_locked(buf);

	WARN_ON(test_bit(BTRFS_ROOT_SHAREABLE, &root->state) &&
		trans->transid != fs_info->running_transaction->transid);
	WARN_ON(test_bit(BTRFS_ROOT_SHAREABLE, &root->state) &&
		trans->transid != root->last_trans);

	level = btrfs_header_level(buf);

	अगर (level == 0)
		btrfs_item_key(buf, &disk_key, 0);
	अन्यथा
		btrfs_node_key(buf, &disk_key, 0);

	अगर ((root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID) && parent)
		parent_start = parent->start;

	cow = alloc_tree_block_no_bg_flush(trans, root, parent_start, &disk_key,
					   level, search_start, empty_size, nest);
	अगर (IS_ERR(cow))
		वापस PTR_ERR(cow);

	/* cow is set to blocking by btrfs_init_new_buffer */

	copy_extent_buffer_full(cow, buf);
	btrfs_set_header_bytenr(cow, cow->start);
	btrfs_set_header_generation(cow, trans->transid);
	btrfs_set_header_backref_rev(cow, BTRFS_MIXED_BACKREF_REV);
	btrfs_clear_header_flag(cow, BTRFS_HEADER_FLAG_WRITTEN |
				     BTRFS_HEADER_FLAG_RELOC);
	अगर (root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID)
		btrfs_set_header_flag(cow, BTRFS_HEADER_FLAG_RELOC);
	अन्यथा
		btrfs_set_header_owner(cow, root->root_key.objectid);

	ग_लिखो_extent_buffer_fsid(cow, fs_info->fs_devices->metadata_uuid);

	ret = update_ref_क्रम_cow(trans, root, buf, cow, &last_ref);
	अगर (ret) अणु
		btrfs_tree_unlock(cow);
		मुक्त_extent_buffer(cow);
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण

	अगर (test_bit(BTRFS_ROOT_SHAREABLE, &root->state)) अणु
		ret = btrfs_reloc_cow_block(trans, root, buf, cow);
		अगर (ret) अणु
			btrfs_tree_unlock(cow);
			मुक्त_extent_buffer(cow);
			btrfs_पात_transaction(trans, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (buf == root->node) अणु
		WARN_ON(parent && parent != buf);
		अगर (root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID ||
		    btrfs_header_backref_rev(buf) < BTRFS_MIXED_BACKREF_REV)
			parent_start = buf->start;

		atomic_inc(&cow->refs);
		ret = btrfs_tree_mod_log_insert_root(root->node, cow, true);
		BUG_ON(ret < 0);
		rcu_assign_poपूर्णांकer(root->node, cow);

		btrfs_मुक्त_tree_block(trans, root, buf, parent_start,
				      last_ref);
		मुक्त_extent_buffer(buf);
		add_root_to_dirty_list(root);
	पूर्ण अन्यथा अणु
		WARN_ON(trans->transid != btrfs_header_generation(parent));
		btrfs_tree_mod_log_insert_key(parent, parent_slot,
					      BTRFS_MOD_LOG_KEY_REPLACE, GFP_NOFS);
		btrfs_set_node_blockptr(parent, parent_slot,
					cow->start);
		btrfs_set_node_ptr_generation(parent, parent_slot,
					      trans->transid);
		btrfs_mark_buffer_dirty(parent);
		अगर (last_ref) अणु
			ret = btrfs_tree_mod_log_मुक्त_eb(buf);
			अगर (ret) अणु
				btrfs_tree_unlock(cow);
				मुक्त_extent_buffer(cow);
				btrfs_पात_transaction(trans, ret);
				वापस ret;
			पूर्ण
		पूर्ण
		btrfs_मुक्त_tree_block(trans, root, buf, parent_start,
				      last_ref);
	पूर्ण
	अगर (unlock_orig)
		btrfs_tree_unlock(buf);
	मुक्त_extent_buffer_stale(buf);
	btrfs_mark_buffer_dirty(cow);
	*cow_ret = cow;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक should_cow_block(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_root *root,
				   काष्ठा extent_buffer *buf)
अणु
	अगर (btrfs_is_testing(root->fs_info))
		वापस 0;

	/* Ensure we can see the FORCE_COW bit */
	smp_mb__beक्रमe_atomic();

	/*
	 * We करो not need to cow a block अगर
	 * 1) this block is not created or changed in this transaction;
	 * 2) this block करोes not beदीर्घ to TREE_RELOC tree;
	 * 3) the root is not क्रमced COW.
	 *
	 * What is क्रमced COW:
	 *    when we create snapshot during committing the transaction,
	 *    after we've finished copying src root, we must COW the shared
	 *    block to ensure the metadata consistency.
	 */
	अगर (btrfs_header_generation(buf) == trans->transid &&
	    !btrfs_header_flag(buf, BTRFS_HEADER_FLAG_WRITTEN) &&
	    !(root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID &&
	      btrfs_header_flag(buf, BTRFS_HEADER_FLAG_RELOC)) &&
	    !test_bit(BTRFS_ROOT_FORCE_COW, &root->state))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * cows a single block, see __btrfs_cow_block क्रम the real work.
 * This version of it has extra checks so that a block isn't COWed more than
 * once per transaction, as दीर्घ as it hasn't been written yet
 */
noअंतरभूत पूर्णांक btrfs_cow_block(काष्ठा btrfs_trans_handle *trans,
		    काष्ठा btrfs_root *root, काष्ठा extent_buffer *buf,
		    काष्ठा extent_buffer *parent, पूर्णांक parent_slot,
		    काष्ठा extent_buffer **cow_ret,
		    क्रमागत btrfs_lock_nesting nest)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 search_start;
	पूर्णांक ret;

	अगर (test_bit(BTRFS_ROOT_DELETING, &root->state))
		btrfs_err(fs_info,
			"COW'ing blocks on a fs root that's being dropped");

	अगर (trans->transaction != fs_info->running_transaction)
		WARN(1, KERN_CRIT "trans %llu running %llu\n",
		       trans->transid,
		       fs_info->running_transaction->transid);

	अगर (trans->transid != fs_info->generation)
		WARN(1, KERN_CRIT "trans %llu running %llu\n",
		       trans->transid, fs_info->generation);

	अगर (!should_cow_block(trans, root, buf)) अणु
		trans->dirty = true;
		*cow_ret = buf;
		वापस 0;
	पूर्ण

	search_start = buf->start & ~((u64)SZ_1G - 1);

	/*
	 * Beक्रमe CoWing this block क्रम later modअगरication, check अगर it's
	 * the subtree root and करो the delayed subtree trace अगर needed.
	 *
	 * Also We करोn't care about the error, as it's handled पूर्णांकernally.
	 */
	btrfs_qgroup_trace_subtree_after_cow(trans, root, buf);
	ret = __btrfs_cow_block(trans, root, buf, parent,
				 parent_slot, cow_ret, search_start, 0, nest);

	trace_btrfs_cow_block(root, buf, *cow_ret);

	वापस ret;
पूर्ण
ALLOW_ERROR_INJECTION(btrfs_cow_block, ERRNO);

/*
 * helper function क्रम defrag to decide अगर two blocks poपूर्णांकed to by a
 * node are actually बंद by
 */
अटल पूर्णांक बंद_blocks(u64 blocknr, u64 other, u32 blocksize)
अणु
	अगर (blocknr < other && other - (blocknr + blocksize) < 32768)
		वापस 1;
	अगर (blocknr > other && blocknr - (other + blocksize) < 32768)
		वापस 1;
	वापस 0;
पूर्ण

#अगर_घोषित __LITTLE_ENDIAN

/*
 * Compare two keys, on little-endian the disk order is same as CPU order and
 * we can aव्योम the conversion.
 */
अटल पूर्णांक comp_keys(स्थिर काष्ठा btrfs_disk_key *disk_key,
		     स्थिर काष्ठा btrfs_key *k2)
अणु
	स्थिर काष्ठा btrfs_key *k1 = (स्थिर काष्ठा btrfs_key *)disk_key;

	वापस btrfs_comp_cpu_keys(k1, k2);
पूर्ण

#अन्यथा

/*
 * compare two keys in a स_भेद fashion
 */
अटल पूर्णांक comp_keys(स्थिर काष्ठा btrfs_disk_key *disk,
		     स्थिर काष्ठा btrfs_key *k2)
अणु
	काष्ठा btrfs_key k1;

	btrfs_disk_key_to_cpu(&k1, disk);

	वापस btrfs_comp_cpu_keys(&k1, k2);
पूर्ण
#पूर्ण_अगर

/*
 * same as comp_keys only with two btrfs_key's
 */
पूर्णांक __pure btrfs_comp_cpu_keys(स्थिर काष्ठा btrfs_key *k1, स्थिर काष्ठा btrfs_key *k2)
अणु
	अगर (k1->objectid > k2->objectid)
		वापस 1;
	अगर (k1->objectid < k2->objectid)
		वापस -1;
	अगर (k1->type > k2->type)
		वापस 1;
	अगर (k1->type < k2->type)
		वापस -1;
	अगर (k1->offset > k2->offset)
		वापस 1;
	अगर (k1->offset < k2->offset)
		वापस -1;
	वापस 0;
पूर्ण

/*
 * this is used by the defrag code to go through all the
 * leaves poपूर्णांकed to by a node and पुनः_स्मृतिate them so that
 * disk order is बंद to key order
 */
पूर्णांक btrfs_पुनः_स्मृति_node(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root, काष्ठा extent_buffer *parent,
		       पूर्णांक start_slot, u64 *last_ret,
		       काष्ठा btrfs_key *progress)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *cur;
	u64 blocknr;
	u64 search_start = *last_ret;
	u64 last_block = 0;
	u64 other;
	u32 parent_nritems;
	पूर्णांक end_slot;
	पूर्णांक i;
	पूर्णांक err = 0;
	u32 blocksize;
	पूर्णांक progress_passed = 0;
	काष्ठा btrfs_disk_key disk_key;

	WARN_ON(trans->transaction != fs_info->running_transaction);
	WARN_ON(trans->transid != fs_info->generation);

	parent_nritems = btrfs_header_nritems(parent);
	blocksize = fs_info->nodesize;
	end_slot = parent_nritems - 1;

	अगर (parent_nritems <= 1)
		वापस 0;

	क्रम (i = start_slot; i <= end_slot; i++) अणु
		पूर्णांक बंद = 1;

		btrfs_node_key(parent, &disk_key, i);
		अगर (!progress_passed && comp_keys(&disk_key, progress) < 0)
			जारी;

		progress_passed = 1;
		blocknr = btrfs_node_blockptr(parent, i);
		अगर (last_block == 0)
			last_block = blocknr;

		अगर (i > 0) अणु
			other = btrfs_node_blockptr(parent, i - 1);
			बंद = बंद_blocks(blocknr, other, blocksize);
		पूर्ण
		अगर (!बंद && i < end_slot) अणु
			other = btrfs_node_blockptr(parent, i + 1);
			बंद = बंद_blocks(blocknr, other, blocksize);
		पूर्ण
		अगर (बंद) अणु
			last_block = blocknr;
			जारी;
		पूर्ण

		cur = btrfs_पढ़ो_node_slot(parent, i);
		अगर (IS_ERR(cur))
			वापस PTR_ERR(cur);
		अगर (search_start == 0)
			search_start = last_block;

		btrfs_tree_lock(cur);
		err = __btrfs_cow_block(trans, root, cur, parent, i,
					&cur, search_start,
					min(16 * blocksize,
					    (end_slot - i) * blocksize),
					BTRFS_NESTING_COW);
		अगर (err) अणु
			btrfs_tree_unlock(cur);
			मुक्त_extent_buffer(cur);
			अवरोध;
		पूर्ण
		search_start = cur->start;
		last_block = cur->start;
		*last_ret = search_start;
		btrfs_tree_unlock(cur);
		मुक्त_extent_buffer(cur);
	पूर्ण
	वापस err;
पूर्ण

/*
 * search क्रम key in the extent_buffer.  The items start at offset p,
 * and they are item_size apart.  There are 'max' items in p.
 *
 * the slot in the array is वापसed via slot, and it poपूर्णांकs to
 * the place where you would insert key अगर it is not found in
 * the array.
 *
 * slot may poपूर्णांक to max अगर the key is bigger than all of the keys
 */
अटल noअंतरभूत पूर्णांक generic_bin_search(काष्ठा extent_buffer *eb,
				       अचिन्हित दीर्घ p, पूर्णांक item_size,
				       स्थिर काष्ठा btrfs_key *key,
				       पूर्णांक max, पूर्णांक *slot)
अणु
	पूर्णांक low = 0;
	पूर्णांक high = max;
	पूर्णांक ret;
	स्थिर पूर्णांक key_size = माप(काष्ठा btrfs_disk_key);

	अगर (low > high) अणु
		btrfs_err(eb->fs_info,
		 "%s: low (%d) > high (%d) eb %llu owner %llu level %d",
			  __func__, low, high, eb->start,
			  btrfs_header_owner(eb), btrfs_header_level(eb));
		वापस -EINVAL;
	पूर्ण

	जबतक (low < high) अणु
		अचिन्हित दीर्घ oip;
		अचिन्हित दीर्घ offset;
		काष्ठा btrfs_disk_key *पंचांगp;
		काष्ठा btrfs_disk_key unaligned;
		पूर्णांक mid;

		mid = (low + high) / 2;
		offset = p + mid * item_size;
		oip = offset_in_page(offset);

		अगर (oip + key_size <= PAGE_SIZE) अणु
			स्थिर अचिन्हित दीर्घ idx = get_eb_page_index(offset);
			अक्षर *kaddr = page_address(eb->pages[idx]);

			oip = get_eb_offset_in_page(eb, offset);
			पंचांगp = (काष्ठा btrfs_disk_key *)(kaddr + oip);
		पूर्ण अन्यथा अणु
			पढ़ो_extent_buffer(eb, &unaligned, offset, key_size);
			पंचांगp = &unaligned;
		पूर्ण

		ret = comp_keys(पंचांगp, key);

		अगर (ret < 0)
			low = mid + 1;
		अन्यथा अगर (ret > 0)
			high = mid;
		अन्यथा अणु
			*slot = mid;
			वापस 0;
		पूर्ण
	पूर्ण
	*slot = low;
	वापस 1;
पूर्ण

/*
 * simple bin_search frontend that करोes the right thing क्रम
 * leaves vs nodes
 */
पूर्णांक btrfs_bin_search(काष्ठा extent_buffer *eb, स्थिर काष्ठा btrfs_key *key,
		     पूर्णांक *slot)
अणु
	अगर (btrfs_header_level(eb) == 0)
		वापस generic_bin_search(eb,
					  दुरत्व(काष्ठा btrfs_leaf, items),
					  माप(काष्ठा btrfs_item),
					  key, btrfs_header_nritems(eb),
					  slot);
	अन्यथा
		वापस generic_bin_search(eb,
					  दुरत्व(काष्ठा btrfs_node, ptrs),
					  माप(काष्ठा btrfs_key_ptr),
					  key, btrfs_header_nritems(eb),
					  slot);
पूर्ण

अटल व्योम root_add_used(काष्ठा btrfs_root *root, u32 size)
अणु
	spin_lock(&root->accounting_lock);
	btrfs_set_root_used(&root->root_item,
			    btrfs_root_used(&root->root_item) + size);
	spin_unlock(&root->accounting_lock);
पूर्ण

अटल व्योम root_sub_used(काष्ठा btrfs_root *root, u32 size)
अणु
	spin_lock(&root->accounting_lock);
	btrfs_set_root_used(&root->root_item,
			    btrfs_root_used(&root->root_item) - size);
	spin_unlock(&root->accounting_lock);
पूर्ण

/* given a node and slot number, this पढ़ोs the blocks it poपूर्णांकs to.  The
 * extent buffer is वापसed with a reference taken (but unlocked).
 */
काष्ठा extent_buffer *btrfs_पढ़ो_node_slot(काष्ठा extent_buffer *parent,
					   पूर्णांक slot)
अणु
	पूर्णांक level = btrfs_header_level(parent);
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_key first_key;

	अगर (slot < 0 || slot >= btrfs_header_nritems(parent))
		वापस ERR_PTR(-ENOENT);

	BUG_ON(level == 0);

	btrfs_node_key_to_cpu(parent, &first_key, slot);
	eb = पढ़ो_tree_block(parent->fs_info, btrfs_node_blockptr(parent, slot),
			     btrfs_header_owner(parent),
			     btrfs_node_ptr_generation(parent, slot),
			     level - 1, &first_key);
	अगर (!IS_ERR(eb) && !extent_buffer_uptodate(eb)) अणु
		मुक्त_extent_buffer(eb);
		eb = ERR_PTR(-EIO);
	पूर्ण

	वापस eb;
पूर्ण

/*
 * node level balancing, used to make sure nodes are in proper order क्रम
 * item deletion.  We balance from the top करोwn, so we have to make sure
 * that a deletion won't leave an node completely empty later on.
 */
अटल noअंतरभूत पूर्णांक balance_level(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_root *root,
			 काष्ठा btrfs_path *path, पूर्णांक level)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *right = शून्य;
	काष्ठा extent_buffer *mid;
	काष्ठा extent_buffer *left = शून्य;
	काष्ठा extent_buffer *parent = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक wret;
	पूर्णांक pslot;
	पूर्णांक orig_slot = path->slots[level];
	u64 orig_ptr;

	ASSERT(level > 0);

	mid = path->nodes[level];

	WARN_ON(path->locks[level] != BTRFS_WRITE_LOCK);
	WARN_ON(btrfs_header_generation(mid) != trans->transid);

	orig_ptr = btrfs_node_blockptr(mid, orig_slot);

	अगर (level < BTRFS_MAX_LEVEL - 1) अणु
		parent = path->nodes[level + 1];
		pslot = path->slots[level + 1];
	पूर्ण

	/*
	 * deal with the हाल where there is only one poपूर्णांकer in the root
	 * by promoting the node below to a root
	 */
	अगर (!parent) अणु
		काष्ठा extent_buffer *child;

		अगर (btrfs_header_nritems(mid) != 1)
			वापस 0;

		/* promote the child to a root */
		child = btrfs_पढ़ो_node_slot(mid, 0);
		अगर (IS_ERR(child)) अणु
			ret = PTR_ERR(child);
			btrfs_handle_fs_error(fs_info, ret, शून्य);
			जाओ enospc;
		पूर्ण

		btrfs_tree_lock(child);
		ret = btrfs_cow_block(trans, root, child, mid, 0, &child,
				      BTRFS_NESTING_COW);
		अगर (ret) अणु
			btrfs_tree_unlock(child);
			मुक्त_extent_buffer(child);
			जाओ enospc;
		पूर्ण

		ret = btrfs_tree_mod_log_insert_root(root->node, child, true);
		BUG_ON(ret < 0);
		rcu_assign_poपूर्णांकer(root->node, child);

		add_root_to_dirty_list(root);
		btrfs_tree_unlock(child);

		path->locks[level] = 0;
		path->nodes[level] = शून्य;
		btrfs_clean_tree_block(mid);
		btrfs_tree_unlock(mid);
		/* once क्रम the path */
		मुक्त_extent_buffer(mid);

		root_sub_used(root, mid->len);
		btrfs_मुक्त_tree_block(trans, root, mid, 0, 1);
		/* once क्रम the root ptr */
		मुक्त_extent_buffer_stale(mid);
		वापस 0;
	पूर्ण
	अगर (btrfs_header_nritems(mid) >
	    BTRFS_NODEPTRS_PER_BLOCK(fs_info) / 4)
		वापस 0;

	left = btrfs_पढ़ो_node_slot(parent, pslot - 1);
	अगर (IS_ERR(left))
		left = शून्य;

	अगर (left) अणु
		__btrfs_tree_lock(left, BTRFS_NESTING_LEFT);
		wret = btrfs_cow_block(trans, root, left,
				       parent, pslot - 1, &left,
				       BTRFS_NESTING_LEFT_COW);
		अगर (wret) अणु
			ret = wret;
			जाओ enospc;
		पूर्ण
	पूर्ण

	right = btrfs_पढ़ो_node_slot(parent, pslot + 1);
	अगर (IS_ERR(right))
		right = शून्य;

	अगर (right) अणु
		__btrfs_tree_lock(right, BTRFS_NESTING_RIGHT);
		wret = btrfs_cow_block(trans, root, right,
				       parent, pslot + 1, &right,
				       BTRFS_NESTING_RIGHT_COW);
		अगर (wret) अणु
			ret = wret;
			जाओ enospc;
		पूर्ण
	पूर्ण

	/* first, try to make some room in the middle buffer */
	अगर (left) अणु
		orig_slot += btrfs_header_nritems(left);
		wret = push_node_left(trans, left, mid, 1);
		अगर (wret < 0)
			ret = wret;
	पूर्ण

	/*
	 * then try to empty the right most buffer पूर्णांकo the middle
	 */
	अगर (right) अणु
		wret = push_node_left(trans, mid, right, 1);
		अगर (wret < 0 && wret != -ENOSPC)
			ret = wret;
		अगर (btrfs_header_nritems(right) == 0) अणु
			btrfs_clean_tree_block(right);
			btrfs_tree_unlock(right);
			del_ptr(root, path, level + 1, pslot + 1);
			root_sub_used(root, right->len);
			btrfs_मुक्त_tree_block(trans, root, right, 0, 1);
			मुक्त_extent_buffer_stale(right);
			right = शून्य;
		पूर्ण अन्यथा अणु
			काष्ठा btrfs_disk_key right_key;
			btrfs_node_key(right, &right_key, 0);
			ret = btrfs_tree_mod_log_insert_key(parent, pslot + 1,
					BTRFS_MOD_LOG_KEY_REPLACE, GFP_NOFS);
			BUG_ON(ret < 0);
			btrfs_set_node_key(parent, &right_key, pslot + 1);
			btrfs_mark_buffer_dirty(parent);
		पूर्ण
	पूर्ण
	अगर (btrfs_header_nritems(mid) == 1) अणु
		/*
		 * we're not allowed to leave a node with one item in the
		 * tree during a delete.  A deletion from lower in the tree
		 * could try to delete the only poपूर्णांकer in this node.
		 * So, pull some keys from the left.
		 * There has to be a left poपूर्णांकer at this poपूर्णांक because
		 * otherwise we would have pulled some poपूर्णांकers from the
		 * right
		 */
		अगर (!left) अणु
			ret = -EROFS;
			btrfs_handle_fs_error(fs_info, ret, शून्य);
			जाओ enospc;
		पूर्ण
		wret = balance_node_right(trans, mid, left);
		अगर (wret < 0) अणु
			ret = wret;
			जाओ enospc;
		पूर्ण
		अगर (wret == 1) अणु
			wret = push_node_left(trans, left, mid, 1);
			अगर (wret < 0)
				ret = wret;
		पूर्ण
		BUG_ON(wret == 1);
	पूर्ण
	अगर (btrfs_header_nritems(mid) == 0) अणु
		btrfs_clean_tree_block(mid);
		btrfs_tree_unlock(mid);
		del_ptr(root, path, level + 1, pslot);
		root_sub_used(root, mid->len);
		btrfs_मुक्त_tree_block(trans, root, mid, 0, 1);
		मुक्त_extent_buffer_stale(mid);
		mid = शून्य;
	पूर्ण अन्यथा अणु
		/* update the parent key to reflect our changes */
		काष्ठा btrfs_disk_key mid_key;
		btrfs_node_key(mid, &mid_key, 0);
		ret = btrfs_tree_mod_log_insert_key(parent, pslot,
				BTRFS_MOD_LOG_KEY_REPLACE, GFP_NOFS);
		BUG_ON(ret < 0);
		btrfs_set_node_key(parent, &mid_key, pslot);
		btrfs_mark_buffer_dirty(parent);
	पूर्ण

	/* update the path */
	अगर (left) अणु
		अगर (btrfs_header_nritems(left) > orig_slot) अणु
			atomic_inc(&left->refs);
			/* left was locked after cow */
			path->nodes[level] = left;
			path->slots[level + 1] -= 1;
			path->slots[level] = orig_slot;
			अगर (mid) अणु
				btrfs_tree_unlock(mid);
				मुक्त_extent_buffer(mid);
			पूर्ण
		पूर्ण अन्यथा अणु
			orig_slot -= btrfs_header_nritems(left);
			path->slots[level] = orig_slot;
		पूर्ण
	पूर्ण
	/* द्विगुन check we haven't messed things up */
	अगर (orig_ptr !=
	    btrfs_node_blockptr(path->nodes[level], path->slots[level]))
		BUG();
enospc:
	अगर (right) अणु
		btrfs_tree_unlock(right);
		मुक्त_extent_buffer(right);
	पूर्ण
	अगर (left) अणु
		अगर (path->nodes[level] != left)
			btrfs_tree_unlock(left);
		मुक्त_extent_buffer(left);
	पूर्ण
	वापस ret;
पूर्ण

/* Node balancing क्रम insertion.  Here we only split or push nodes around
 * when they are completely full.  This is also करोne top करोwn, so we
 * have to be pessimistic.
 */
अटल noअंतरभूत पूर्णांक push_nodes_क्रम_insert(काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_root *root,
					  काष्ठा btrfs_path *path, पूर्णांक level)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *right = शून्य;
	काष्ठा extent_buffer *mid;
	काष्ठा extent_buffer *left = शून्य;
	काष्ठा extent_buffer *parent = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक wret;
	पूर्णांक pslot;
	पूर्णांक orig_slot = path->slots[level];

	अगर (level == 0)
		वापस 1;

	mid = path->nodes[level];
	WARN_ON(btrfs_header_generation(mid) != trans->transid);

	अगर (level < BTRFS_MAX_LEVEL - 1) अणु
		parent = path->nodes[level + 1];
		pslot = path->slots[level + 1];
	पूर्ण

	अगर (!parent)
		वापस 1;

	left = btrfs_पढ़ो_node_slot(parent, pslot - 1);
	अगर (IS_ERR(left))
		left = शून्य;

	/* first, try to make some room in the middle buffer */
	अगर (left) अणु
		u32 left_nr;

		__btrfs_tree_lock(left, BTRFS_NESTING_LEFT);

		left_nr = btrfs_header_nritems(left);
		अगर (left_nr >= BTRFS_NODEPTRS_PER_BLOCK(fs_info) - 1) अणु
			wret = 1;
		पूर्ण अन्यथा अणु
			ret = btrfs_cow_block(trans, root, left, parent,
					      pslot - 1, &left,
					      BTRFS_NESTING_LEFT_COW);
			अगर (ret)
				wret = 1;
			अन्यथा अणु
				wret = push_node_left(trans, left, mid, 0);
			पूर्ण
		पूर्ण
		अगर (wret < 0)
			ret = wret;
		अगर (wret == 0) अणु
			काष्ठा btrfs_disk_key disk_key;
			orig_slot += left_nr;
			btrfs_node_key(mid, &disk_key, 0);
			ret = btrfs_tree_mod_log_insert_key(parent, pslot,
					BTRFS_MOD_LOG_KEY_REPLACE, GFP_NOFS);
			BUG_ON(ret < 0);
			btrfs_set_node_key(parent, &disk_key, pslot);
			btrfs_mark_buffer_dirty(parent);
			अगर (btrfs_header_nritems(left) > orig_slot) अणु
				path->nodes[level] = left;
				path->slots[level + 1] -= 1;
				path->slots[level] = orig_slot;
				btrfs_tree_unlock(mid);
				मुक्त_extent_buffer(mid);
			पूर्ण अन्यथा अणु
				orig_slot -=
					btrfs_header_nritems(left);
				path->slots[level] = orig_slot;
				btrfs_tree_unlock(left);
				मुक्त_extent_buffer(left);
			पूर्ण
			वापस 0;
		पूर्ण
		btrfs_tree_unlock(left);
		मुक्त_extent_buffer(left);
	पूर्ण
	right = btrfs_पढ़ो_node_slot(parent, pslot + 1);
	अगर (IS_ERR(right))
		right = शून्य;

	/*
	 * then try to empty the right most buffer पूर्णांकo the middle
	 */
	अगर (right) अणु
		u32 right_nr;

		__btrfs_tree_lock(right, BTRFS_NESTING_RIGHT);

		right_nr = btrfs_header_nritems(right);
		अगर (right_nr >= BTRFS_NODEPTRS_PER_BLOCK(fs_info) - 1) अणु
			wret = 1;
		पूर्ण अन्यथा अणु
			ret = btrfs_cow_block(trans, root, right,
					      parent, pslot + 1,
					      &right, BTRFS_NESTING_RIGHT_COW);
			अगर (ret)
				wret = 1;
			अन्यथा अणु
				wret = balance_node_right(trans, right, mid);
			पूर्ण
		पूर्ण
		अगर (wret < 0)
			ret = wret;
		अगर (wret == 0) अणु
			काष्ठा btrfs_disk_key disk_key;

			btrfs_node_key(right, &disk_key, 0);
			ret = btrfs_tree_mod_log_insert_key(parent, pslot + 1,
					BTRFS_MOD_LOG_KEY_REPLACE, GFP_NOFS);
			BUG_ON(ret < 0);
			btrfs_set_node_key(parent, &disk_key, pslot + 1);
			btrfs_mark_buffer_dirty(parent);

			अगर (btrfs_header_nritems(mid) <= orig_slot) अणु
				path->nodes[level] = right;
				path->slots[level + 1] += 1;
				path->slots[level] = orig_slot -
					btrfs_header_nritems(mid);
				btrfs_tree_unlock(mid);
				मुक्त_extent_buffer(mid);
			पूर्ण अन्यथा अणु
				btrfs_tree_unlock(right);
				मुक्त_extent_buffer(right);
			पूर्ण
			वापस 0;
		पूर्ण
		btrfs_tree_unlock(right);
		मुक्त_extent_buffer(right);
	पूर्ण
	वापस 1;
पूर्ण

/*
 * पढ़ोahead one full node of leaves, finding things that are बंद
 * to the block in 'slot', and triggering ra on them.
 */
अटल व्योम पढ़ोa_क्रम_search(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा btrfs_path *path,
			     पूर्णांक level, पूर्णांक slot, u64 objectid)
अणु
	काष्ठा extent_buffer *node;
	काष्ठा btrfs_disk_key disk_key;
	u32 nritems;
	u64 search;
	u64 target;
	u64 nपढ़ो = 0;
	u64 nपढ़ो_max;
	काष्ठा extent_buffer *eb;
	u32 nr;
	u32 blocksize;
	u32 nscan = 0;

	अगर (level != 1 && path->पढ़ोa != READA_FORWARD_ALWAYS)
		वापस;

	अगर (!path->nodes[level])
		वापस;

	node = path->nodes[level];

	/*
	 * Since the समय between visiting leaves is much लघुer than the समय
	 * between visiting nodes, limit पढ़ो ahead of nodes to 1, to aव्योम too
	 * much IO at once (possibly अक्रमom).
	 */
	अगर (path->पढ़ोa == READA_FORWARD_ALWAYS) अणु
		अगर (level > 1)
			nपढ़ो_max = node->fs_info->nodesize;
		अन्यथा
			nपढ़ो_max = SZ_128K;
	पूर्ण अन्यथा अणु
		nपढ़ो_max = SZ_64K;
	पूर्ण

	search = btrfs_node_blockptr(node, slot);
	blocksize = fs_info->nodesize;
	eb = find_extent_buffer(fs_info, search);
	अगर (eb) अणु
		मुक्त_extent_buffer(eb);
		वापस;
	पूर्ण

	target = search;

	nritems = btrfs_header_nritems(node);
	nr = slot;

	जबतक (1) अणु
		अगर (path->पढ़ोa == READA_BACK) अणु
			अगर (nr == 0)
				अवरोध;
			nr--;
		पूर्ण अन्यथा अगर (path->पढ़ोa == READA_FORWARD ||
			   path->पढ़ोa == READA_FORWARD_ALWAYS) अणु
			nr++;
			अगर (nr >= nritems)
				अवरोध;
		पूर्ण
		अगर (path->पढ़ोa == READA_BACK && objectid) अणु
			btrfs_node_key(node, &disk_key, nr);
			अगर (btrfs_disk_key_objectid(&disk_key) != objectid)
				अवरोध;
		पूर्ण
		search = btrfs_node_blockptr(node, nr);
		अगर (path->पढ़ोa == READA_FORWARD_ALWAYS ||
		    (search <= target && target - search <= 65536) ||
		    (search > target && search - target <= 65536)) अणु
			btrfs_पढ़ोahead_node_child(node, nr);
			nपढ़ो += blocksize;
		पूर्ण
		nscan++;
		अगर (nपढ़ो > nपढ़ो_max || nscan > 32)
			अवरोध;
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम पढ़ोa_क्रम_balance(काष्ठा btrfs_path *path, पूर्णांक level)
अणु
	काष्ठा extent_buffer *parent;
	पूर्णांक slot;
	पूर्णांक nritems;

	parent = path->nodes[level + 1];
	अगर (!parent)
		वापस;

	nritems = btrfs_header_nritems(parent);
	slot = path->slots[level + 1];

	अगर (slot > 0)
		btrfs_पढ़ोahead_node_child(parent, slot - 1);
	अगर (slot + 1 < nritems)
		btrfs_पढ़ोahead_node_child(parent, slot + 1);
पूर्ण


/*
 * when we walk करोwn the tree, it is usually safe to unlock the higher layers
 * in the tree.  The exceptions are when our path goes through slot 0, because
 * operations on the tree might require changing key poपूर्णांकers higher up in the
 * tree.
 *
 * callers might also have set path->keep_locks, which tells this code to keep
 * the lock अगर the path poपूर्णांकs to the last slot in the block.  This is part of
 * walking through the tree, and selecting the next slot in the higher block.
 *
 * lowest_unlock sets the lowest level in the tree we're allowed to unlock.  so
 * अगर lowest_unlock is 1, level 0 won't be unlocked
 */
अटल noअंतरभूत व्योम unlock_up(काष्ठा btrfs_path *path, पूर्णांक level,
			       पूर्णांक lowest_unlock, पूर्णांक min_ग_लिखो_lock_level,
			       पूर्णांक *ग_लिखो_lock_level)
अणु
	पूर्णांक i;
	पूर्णांक skip_level = level;
	पूर्णांक no_skips = 0;
	काष्ठा extent_buffer *t;

	क्रम (i = level; i < BTRFS_MAX_LEVEL; i++) अणु
		अगर (!path->nodes[i])
			अवरोध;
		अगर (!path->locks[i])
			अवरोध;
		अगर (!no_skips && path->slots[i] == 0) अणु
			skip_level = i + 1;
			जारी;
		पूर्ण
		अगर (!no_skips && path->keep_locks) अणु
			u32 nritems;
			t = path->nodes[i];
			nritems = btrfs_header_nritems(t);
			अगर (nritems < 1 || path->slots[i] >= nritems - 1) अणु
				skip_level = i + 1;
				जारी;
			पूर्ण
		पूर्ण
		अगर (skip_level < i && i >= lowest_unlock)
			no_skips = 1;

		t = path->nodes[i];
		अगर (i >= lowest_unlock && i > skip_level) अणु
			btrfs_tree_unlock_rw(t, path->locks[i]);
			path->locks[i] = 0;
			अगर (ग_लिखो_lock_level &&
			    i > min_ग_लिखो_lock_level &&
			    i <= *ग_लिखो_lock_level) अणु
				*ग_लिखो_lock_level = i - 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * helper function क्रम btrfs_search_slot.  The goal is to find a block
 * in cache without setting the path to blocking.  If we find the block
 * we वापस zero and the path is unchanged.
 *
 * If we can't find the block, we set the path blocking and करो some
 * पढ़ोa.  -EAGAIN is वापसed and the search must be repeated.
 */
अटल पूर्णांक
पढ़ो_block_क्रम_search(काष्ठा btrfs_root *root, काष्ठा btrfs_path *p,
		      काष्ठा extent_buffer **eb_ret, पूर्णांक level, पूर्णांक slot,
		      स्थिर काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 blocknr;
	u64 gen;
	काष्ठा extent_buffer *पंचांगp;
	काष्ठा btrfs_key first_key;
	पूर्णांक ret;
	पूर्णांक parent_level;

	blocknr = btrfs_node_blockptr(*eb_ret, slot);
	gen = btrfs_node_ptr_generation(*eb_ret, slot);
	parent_level = btrfs_header_level(*eb_ret);
	btrfs_node_key_to_cpu(*eb_ret, &first_key, slot);

	पंचांगp = find_extent_buffer(fs_info, blocknr);
	अगर (पंचांगp) अणु
		अगर (p->पढ़ोa == READA_FORWARD_ALWAYS)
			पढ़ोa_क्रम_search(fs_info, p, level, slot, key->objectid);

		/* first we करो an atomic uptodate check */
		अगर (btrfs_buffer_uptodate(पंचांगp, gen, 1) > 0) अणु
			/*
			 * Do extra check क्रम first_key, eb can be stale due to
			 * being cached, पढ़ो from scrub, or have multiple
			 * parents (shared tree blocks).
			 */
			अगर (btrfs_verअगरy_level_key(पंचांगp,
					parent_level - 1, &first_key, gen)) अणु
				मुक्त_extent_buffer(पंचांगp);
				वापस -EUCLEAN;
			पूर्ण
			*eb_ret = पंचांगp;
			वापस 0;
		पूर्ण

		/* now we're allowed to करो a blocking uptodate check */
		ret = btrfs_पढ़ो_buffer(पंचांगp, gen, parent_level - 1, &first_key);
		अगर (!ret) अणु
			*eb_ret = पंचांगp;
			वापस 0;
		पूर्ण
		मुक्त_extent_buffer(पंचांगp);
		btrfs_release_path(p);
		वापस -EIO;
	पूर्ण

	/*
	 * reduce lock contention at high levels
	 * of the btree by dropping locks beक्रमe
	 * we पढ़ो.  Don't release the lock on the current
	 * level because we need to walk this node to figure
	 * out which blocks to पढ़ो.
	 */
	btrfs_unlock_up_safe(p, level + 1);

	अगर (p->पढ़ोa != READA_NONE)
		पढ़ोa_क्रम_search(fs_info, p, level, slot, key->objectid);

	ret = -EAGAIN;
	पंचांगp = पढ़ो_tree_block(fs_info, blocknr, root->root_key.objectid,
			      gen, parent_level - 1, &first_key);
	अगर (!IS_ERR(पंचांगp)) अणु
		/*
		 * If the पढ़ो above didn't mark this buffer up to date,
		 * it will never end up being up to date.  Set ret to EIO now
		 * and give up so that our caller करोesn't loop क्रमever
		 * on our EAGAINs.
		 */
		अगर (!extent_buffer_uptodate(पंचांगp))
			ret = -EIO;
		मुक्त_extent_buffer(पंचांगp);
	पूर्ण अन्यथा अणु
		ret = PTR_ERR(पंचांगp);
	पूर्ण

	btrfs_release_path(p);
	वापस ret;
पूर्ण

/*
 * helper function क्रम btrfs_search_slot.  This करोes all of the checks
 * क्रम node-level blocks and करोes any balancing required based on
 * the ins_len.
 *
 * If no extra work was required, zero is वापसed.  If we had to
 * drop the path, -EAGAIN is वापसed and btrfs_search_slot must
 * start over
 */
अटल पूर्णांक
setup_nodes_क्रम_search(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root, काष्ठा btrfs_path *p,
		       काष्ठा extent_buffer *b, पूर्णांक level, पूर्णांक ins_len,
		       पूर्णांक *ग_लिखो_lock_level)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret = 0;

	अगर ((p->search_क्रम_split || ins_len > 0) && btrfs_header_nritems(b) >=
	    BTRFS_NODEPTRS_PER_BLOCK(fs_info) - 3) अणु

		अगर (*ग_लिखो_lock_level < level + 1) अणु
			*ग_लिखो_lock_level = level + 1;
			btrfs_release_path(p);
			वापस -EAGAIN;
		पूर्ण

		पढ़ोa_क्रम_balance(p, level);
		ret = split_node(trans, root, p, level);

		b = p->nodes[level];
	पूर्ण अन्यथा अगर (ins_len < 0 && btrfs_header_nritems(b) <
		   BTRFS_NODEPTRS_PER_BLOCK(fs_info) / 2) अणु

		अगर (*ग_लिखो_lock_level < level + 1) अणु
			*ग_लिखो_lock_level = level + 1;
			btrfs_release_path(p);
			वापस -EAGAIN;
		पूर्ण

		पढ़ोa_क्रम_balance(p, level);
		ret = balance_level(trans, root, p, level);
		अगर (ret)
			वापस ret;

		b = p->nodes[level];
		अगर (!b) अणु
			btrfs_release_path(p);
			वापस -EAGAIN;
		पूर्ण
		BUG_ON(btrfs_header_nritems(b) == 1);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक btrfs_find_item(काष्ठा btrfs_root *fs_root, काष्ठा btrfs_path *path,
		u64 iobjectid, u64 ioff, u8 key_type,
		काष्ठा btrfs_key *found_key)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *eb;

	ASSERT(path);
	ASSERT(found_key);

	key.type = key_type;
	key.objectid = iobjectid;
	key.offset = ioff;

	ret = btrfs_search_slot(शून्य, fs_root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;

	eb = path->nodes[0];
	अगर (ret && path->slots[0] >= btrfs_header_nritems(eb)) अणु
		ret = btrfs_next_leaf(fs_root, path);
		अगर (ret)
			वापस ret;
		eb = path->nodes[0];
	पूर्ण

	btrfs_item_key_to_cpu(eb, found_key, path->slots[0]);
	अगर (found_key->type != key.type ||
			found_key->objectid != key.objectid)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा extent_buffer *btrfs_search_slot_get_root(काष्ठा btrfs_root *root,
							काष्ठा btrfs_path *p,
							पूर्णांक ग_लिखो_lock_level)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *b;
	पूर्णांक root_lock;
	पूर्णांक level = 0;

	/* We try very hard to करो पढ़ो locks on the root */
	root_lock = BTRFS_READ_LOCK;

	अगर (p->search_commit_root) अणु
		/*
		 * The commit roots are पढ़ो only so we always करो पढ़ो locks,
		 * and we always must hold the commit_root_sem when करोing
		 * searches on them, the only exception is send where we करोn't
		 * want to block transaction commits क्रम a दीर्घ समय, so
		 * we need to clone the commit root in order to aव्योम races
		 * with transaction commits that create a snapshot of one of
		 * the roots used by a send operation.
		 */
		अगर (p->need_commit_sem) अणु
			करोwn_पढ़ो(&fs_info->commit_root_sem);
			b = btrfs_clone_extent_buffer(root->commit_root);
			up_पढ़ो(&fs_info->commit_root_sem);
			अगर (!b)
				वापस ERR_PTR(-ENOMEM);

		पूर्ण अन्यथा अणु
			b = root->commit_root;
			atomic_inc(&b->refs);
		पूर्ण
		level = btrfs_header_level(b);
		/*
		 * Ensure that all callers have set skip_locking when
		 * p->search_commit_root = 1.
		 */
		ASSERT(p->skip_locking == 1);

		जाओ out;
	पूर्ण

	अगर (p->skip_locking) अणु
		b = btrfs_root_node(root);
		level = btrfs_header_level(b);
		जाओ out;
	पूर्ण

	/*
	 * If the level is set to maximum, we can skip trying to get the पढ़ो
	 * lock.
	 */
	अगर (ग_लिखो_lock_level < BTRFS_MAX_LEVEL) अणु
		/*
		 * We करोn't know the level of the root node until we actually
		 * have it पढ़ो locked
		 */
		b = btrfs_पढ़ो_lock_root_node(root);
		level = btrfs_header_level(b);
		अगर (level > ग_लिखो_lock_level)
			जाओ out;

		/* Whoops, must trade क्रम ग_लिखो lock */
		btrfs_tree_पढ़ो_unlock(b);
		मुक्त_extent_buffer(b);
	पूर्ण

	b = btrfs_lock_root_node(root);
	root_lock = BTRFS_WRITE_LOCK;

	/* The level might have changed, check again */
	level = btrfs_header_level(b);

out:
	p->nodes[level] = b;
	अगर (!p->skip_locking)
		p->locks[level] = root_lock;
	/*
	 * Callers are responsible क्रम dropping b's references.
	 */
	वापस b;
पूर्ण


/*
 * btrfs_search_slot - look क्रम a key in a tree and perक्रमm necessary
 * modअगरications to preserve tree invariants.
 *
 * @trans:	Handle of transaction, used when modअगरying the tree
 * @p:		Holds all btree nodes aदीर्घ the search path
 * @root:	The root node of the tree
 * @key:	The key we are looking क्रम
 * @ins_len:	Indicates purpose of search:
 *              >0  क्रम inserts it's size of item inserted (*)
 *              <0  क्रम deletions
 *               0  क्रम plain searches, not modअगरying the tree
 *
 *              (*) If size of item inserted करोesn't include
 *              माप(काष्ठा btrfs_item), then p->search_क्रम_extension must
 *              be set.
 * @cow:	boolean should CoW operations be perक्रमmed. Must always be 1
 *		when modअगरying the tree.
 *
 * If @ins_len > 0, nodes and leaves will be split as we walk करोwn the tree.
 * If @ins_len < 0, nodes will be merged as we walk करोwn the tree (अगर possible)
 *
 * If @key is found, 0 is वापसed and you can find the item in the leaf level
 * of the path (level 0)
 *
 * If @key isn't found, 1 is वापसed and the leaf level of the path (level 0)
 * poपूर्णांकs to the slot where it should be inserted
 *
 * If an error is encountered जबतक searching the tree a negative error number
 * is वापसed
 */
पूर्णांक btrfs_search_slot(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		      स्थिर काष्ठा btrfs_key *key, काष्ठा btrfs_path *p,
		      पूर्णांक ins_len, पूर्णांक cow)
अणु
	काष्ठा extent_buffer *b;
	पूर्णांक slot;
	पूर्णांक ret;
	पूर्णांक err;
	पूर्णांक level;
	पूर्णांक lowest_unlock = 1;
	/* everything at ग_लिखो_lock_level or lower must be ग_लिखो locked */
	पूर्णांक ग_लिखो_lock_level = 0;
	u8 lowest_level = 0;
	पूर्णांक min_ग_लिखो_lock_level;
	पूर्णांक prev_cmp;

	lowest_level = p->lowest_level;
	WARN_ON(lowest_level && ins_len > 0);
	WARN_ON(p->nodes[0] != शून्य);
	BUG_ON(!cow && ins_len);

	अगर (ins_len < 0) अणु
		lowest_unlock = 2;

		/* when we are removing items, we might have to go up to level
		 * two as we update tree poपूर्णांकers  Make sure we keep ग_लिखो
		 * क्रम those levels as well
		 */
		ग_लिखो_lock_level = 2;
	पूर्ण अन्यथा अगर (ins_len > 0) अणु
		/*
		 * क्रम inserting items, make sure we have a ग_लिखो lock on
		 * level 1 so we can update keys
		 */
		ग_लिखो_lock_level = 1;
	पूर्ण

	अगर (!cow)
		ग_लिखो_lock_level = -1;

	अगर (cow && (p->keep_locks || p->lowest_level))
		ग_लिखो_lock_level = BTRFS_MAX_LEVEL;

	min_ग_लिखो_lock_level = ग_लिखो_lock_level;

again:
	prev_cmp = -1;
	b = btrfs_search_slot_get_root(root, p, ग_लिखो_lock_level);
	अगर (IS_ERR(b)) अणु
		ret = PTR_ERR(b);
		जाओ करोne;
	पूर्ण

	जबतक (b) अणु
		पूर्णांक dec = 0;

		level = btrfs_header_level(b);

		अगर (cow) अणु
			bool last_level = (level == (BTRFS_MAX_LEVEL - 1));

			/*
			 * अगर we करोn't really need to cow this block
			 * then we करोn't want to set the path blocking,
			 * so we test it here
			 */
			अगर (!should_cow_block(trans, root, b)) अणु
				trans->dirty = true;
				जाओ cow_करोne;
			पूर्ण

			/*
			 * must have ग_लिखो locks on this node and the
			 * parent
			 */
			अगर (level > ग_लिखो_lock_level ||
			    (level + 1 > ग_लिखो_lock_level &&
			    level + 1 < BTRFS_MAX_LEVEL &&
			    p->nodes[level + 1])) अणु
				ग_लिखो_lock_level = level + 1;
				btrfs_release_path(p);
				जाओ again;
			पूर्ण

			अगर (last_level)
				err = btrfs_cow_block(trans, root, b, शून्य, 0,
						      &b,
						      BTRFS_NESTING_COW);
			अन्यथा
				err = btrfs_cow_block(trans, root, b,
						      p->nodes[level + 1],
						      p->slots[level + 1], &b,
						      BTRFS_NESTING_COW);
			अगर (err) अणु
				ret = err;
				जाओ करोne;
			पूर्ण
		पूर्ण
cow_करोne:
		p->nodes[level] = b;
		/*
		 * Leave path with blocking locks to aव्योम massive
		 * lock context चयन, this is made on purpose.
		 */

		/*
		 * we have a lock on b and as दीर्घ as we aren't changing
		 * the tree, there is no way to क्रम the items in b to change.
		 * It is safe to drop the lock on our parent beक्रमe we
		 * go through the expensive btree search on b.
		 *
		 * If we're inserting or deleting (ins_len != 0), then we might
		 * be changing slot zero, which may require changing the parent.
		 * So, we can't drop the lock until after we know which slot
		 * we're operating on.
		 */
		अगर (!ins_len && !p->keep_locks) अणु
			पूर्णांक u = level + 1;

			अगर (u < BTRFS_MAX_LEVEL && p->locks[u]) अणु
				btrfs_tree_unlock_rw(p->nodes[u], p->locks[u]);
				p->locks[u] = 0;
			पूर्ण
		पूर्ण

		/*
		 * If btrfs_bin_search वापसs an exact match (prev_cmp == 0)
		 * we can safely assume the target key will always be in slot 0
		 * on lower levels due to the invariants BTRFS' btree provides,
		 * namely that a btrfs_key_ptr entry always poपूर्णांकs to the
		 * lowest key in the child node, thus we can skip searching
		 * lower levels
		 */
		अगर (prev_cmp == 0) अणु
			slot = 0;
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = btrfs_bin_search(b, key, &slot);
			prev_cmp = ret;
			अगर (ret < 0)
				जाओ करोne;
		पूर्ण

		अगर (level == 0) अणु
			p->slots[level] = slot;
			/*
			 * Item key alपढ़ोy exists. In this हाल, अगर we are
			 * allowed to insert the item (क्रम example, in dir_item
			 * हाल, item key collision is allowed), it will be
			 * merged with the original item. Only the item size
			 * grows, no new btrfs item will be added. If
			 * search_क्रम_extension is not set, ins_len alपढ़ोy
			 * accounts the size btrfs_item, deduct it here so leaf
			 * space check will be correct.
			 */
			अगर (ret == 0 && ins_len > 0 && !p->search_क्रम_extension) अणु
				ASSERT(ins_len >= माप(काष्ठा btrfs_item));
				ins_len -= माप(काष्ठा btrfs_item);
			पूर्ण
			अगर (ins_len > 0 &&
			    btrfs_leaf_मुक्त_space(b) < ins_len) अणु
				अगर (ग_लिखो_lock_level < 1) अणु
					ग_लिखो_lock_level = 1;
					btrfs_release_path(p);
					जाओ again;
				पूर्ण

				err = split_leaf(trans, root, key,
						 p, ins_len, ret == 0);

				BUG_ON(err > 0);
				अगर (err) अणु
					ret = err;
					जाओ करोne;
				पूर्ण
			पूर्ण
			अगर (!p->search_क्रम_split)
				unlock_up(p, level, lowest_unlock,
					  min_ग_लिखो_lock_level, शून्य);
			जाओ करोne;
		पूर्ण
		अगर (ret && slot > 0) अणु
			dec = 1;
			slot--;
		पूर्ण
		p->slots[level] = slot;
		err = setup_nodes_क्रम_search(trans, root, p, b, level, ins_len,
					     &ग_लिखो_lock_level);
		अगर (err == -EAGAIN)
			जाओ again;
		अगर (err) अणु
			ret = err;
			जाओ करोne;
		पूर्ण
		b = p->nodes[level];
		slot = p->slots[level];

		/*
		 * Slot 0 is special, अगर we change the key we have to update
		 * the parent poपूर्णांकer which means we must have a ग_लिखो lock on
		 * the parent
		 */
		अगर (slot == 0 && ins_len && ग_लिखो_lock_level < level + 1) अणु
			ग_लिखो_lock_level = level + 1;
			btrfs_release_path(p);
			जाओ again;
		पूर्ण

		unlock_up(p, level, lowest_unlock, min_ग_लिखो_lock_level,
			  &ग_लिखो_lock_level);

		अगर (level == lowest_level) अणु
			अगर (dec)
				p->slots[level]++;
			जाओ करोne;
		पूर्ण

		err = पढ़ो_block_क्रम_search(root, p, &b, level, slot, key);
		अगर (err == -EAGAIN)
			जाओ again;
		अगर (err) अणु
			ret = err;
			जाओ करोne;
		पूर्ण

		अगर (!p->skip_locking) अणु
			level = btrfs_header_level(b);
			अगर (level <= ग_लिखो_lock_level) अणु
				btrfs_tree_lock(b);
				p->locks[level] = BTRFS_WRITE_LOCK;
			पूर्ण अन्यथा अणु
				btrfs_tree_पढ़ो_lock(b);
				p->locks[level] = BTRFS_READ_LOCK;
			पूर्ण
			p->nodes[level] = b;
		पूर्ण
	पूर्ण
	ret = 1;
करोne:
	अगर (ret < 0 && !p->skip_release_on_error)
		btrfs_release_path(p);
	वापस ret;
पूर्ण
ALLOW_ERROR_INJECTION(btrfs_search_slot, ERRNO);

/*
 * Like btrfs_search_slot, this looks क्रम a key in the given tree. It uses the
 * current state of the tree together with the operations recorded in the tree
 * modअगरication log to search क्रम the key in a previous version of this tree, as
 * denoted by the समय_seq parameter.
 *
 * Naturally, there is no support क्रम insert, delete or cow operations.
 *
 * The resulting path and वापस value will be set up as अगर we called
 * btrfs_search_slot at that poपूर्णांक in समय with ins_len and cow both set to 0.
 */
पूर्णांक btrfs_search_old_slot(काष्ठा btrfs_root *root, स्थिर काष्ठा btrfs_key *key,
			  काष्ठा btrfs_path *p, u64 समय_seq)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *b;
	पूर्णांक slot;
	पूर्णांक ret;
	पूर्णांक err;
	पूर्णांक level;
	पूर्णांक lowest_unlock = 1;
	u8 lowest_level = 0;

	lowest_level = p->lowest_level;
	WARN_ON(p->nodes[0] != शून्य);

	अगर (p->search_commit_root) अणु
		BUG_ON(समय_seq);
		वापस btrfs_search_slot(शून्य, root, key, p, 0, 0);
	पूर्ण

again:
	b = btrfs_get_old_root(root, समय_seq);
	अगर (!b) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण
	level = btrfs_header_level(b);
	p->locks[level] = BTRFS_READ_LOCK;

	जबतक (b) अणु
		पूर्णांक dec = 0;

		level = btrfs_header_level(b);
		p->nodes[level] = b;

		/*
		 * we have a lock on b and as दीर्घ as we aren't changing
		 * the tree, there is no way to क्रम the items in b to change.
		 * It is safe to drop the lock on our parent beक्रमe we
		 * go through the expensive btree search on b.
		 */
		btrfs_unlock_up_safe(p, level + 1);

		ret = btrfs_bin_search(b, key, &slot);
		अगर (ret < 0)
			जाओ करोne;

		अगर (level == 0) अणु
			p->slots[level] = slot;
			unlock_up(p, level, lowest_unlock, 0, शून्य);
			जाओ करोne;
		पूर्ण

		अगर (ret && slot > 0) अणु
			dec = 1;
			slot--;
		पूर्ण
		p->slots[level] = slot;
		unlock_up(p, level, lowest_unlock, 0, शून्य);

		अगर (level == lowest_level) अणु
			अगर (dec)
				p->slots[level]++;
			जाओ करोne;
		पूर्ण

		err = पढ़ो_block_क्रम_search(root, p, &b, level, slot, key);
		अगर (err == -EAGAIN)
			जाओ again;
		अगर (err) अणु
			ret = err;
			जाओ करोne;
		पूर्ण

		level = btrfs_header_level(b);
		btrfs_tree_पढ़ो_lock(b);
		b = btrfs_tree_mod_log_शुरुआत(fs_info, p, b, समय_seq);
		अगर (!b) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		p->locks[level] = BTRFS_READ_LOCK;
		p->nodes[level] = b;
	पूर्ण
	ret = 1;
करोne:
	अगर (ret < 0)
		btrfs_release_path(p);

	वापस ret;
पूर्ण

/*
 * helper to use instead of search slot अगर no exact match is needed but
 * instead the next or previous item should be वापसed.
 * When find_higher is true, the next higher item is वापसed, the next lower
 * otherwise.
 * When वापस_any and find_higher are both true, and no higher item is found,
 * वापस the next lower instead.
 * When वापस_any is true and find_higher is false, and no lower item is found,
 * वापस the next higher instead.
 * It वापसs 0 अगर any item is found, 1 अगर none is found (tree empty), and
 * < 0 on error
 */
पूर्णांक btrfs_search_slot_क्रम_पढ़ो(काष्ठा btrfs_root *root,
			       स्थिर काष्ठा btrfs_key *key,
			       काष्ठा btrfs_path *p, पूर्णांक find_higher,
			       पूर्णांक वापस_any)
अणु
	पूर्णांक ret;
	काष्ठा extent_buffer *leaf;

again:
	ret = btrfs_search_slot(शून्य, root, key, p, 0, 0);
	अगर (ret <= 0)
		वापस ret;
	/*
	 * a वापस value of 1 means the path is at the position where the
	 * item should be inserted. Normally this is the next bigger item,
	 * but in हाल the previous item is the last in a leaf, path poपूर्णांकs
	 * to the first मुक्त slot in the previous leaf, i.e. at an invalid
	 * item.
	 */
	leaf = p->nodes[0];

	अगर (find_higher) अणु
		अगर (p->slots[0] >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, p);
			अगर (ret <= 0)
				वापस ret;
			अगर (!वापस_any)
				वापस 1;
			/*
			 * no higher item found, वापस the next
			 * lower instead
			 */
			वापस_any = 0;
			find_higher = 0;
			btrfs_release_path(p);
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (p->slots[0] == 0) अणु
			ret = btrfs_prev_leaf(root, p);
			अगर (ret < 0)
				वापस ret;
			अगर (!ret) अणु
				leaf = p->nodes[0];
				अगर (p->slots[0] == btrfs_header_nritems(leaf))
					p->slots[0]--;
				वापस 0;
			पूर्ण
			अगर (!वापस_any)
				वापस 1;
			/*
			 * no lower item found, वापस the next
			 * higher instead
			 */
			वापस_any = 0;
			find_higher = 1;
			btrfs_release_path(p);
			जाओ again;
		पूर्ण अन्यथा अणु
			--p->slots[0];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * adjust the poपूर्णांकers going up the tree, starting at level
 * making sure the right key of each node is poपूर्णांकs to 'key'.
 * This is used after shअगरting poपूर्णांकers to the left, so it stops
 * fixing up poपूर्णांकers when a given leaf/node is not in slot 0 of the
 * higher levels
 *
 */
अटल व्योम fixup_low_keys(काष्ठा btrfs_path *path,
			   काष्ठा btrfs_disk_key *key, पूर्णांक level)
अणु
	पूर्णांक i;
	काष्ठा extent_buffer *t;
	पूर्णांक ret;

	क्रम (i = level; i < BTRFS_MAX_LEVEL; i++) अणु
		पूर्णांक tslot = path->slots[i];

		अगर (!path->nodes[i])
			अवरोध;
		t = path->nodes[i];
		ret = btrfs_tree_mod_log_insert_key(t, tslot,
				BTRFS_MOD_LOG_KEY_REPLACE, GFP_ATOMIC);
		BUG_ON(ret < 0);
		btrfs_set_node_key(t, key, tslot);
		btrfs_mark_buffer_dirty(path->nodes[i]);
		अगर (tslot != 0)
			अवरोध;
	पूर्ण
पूर्ण

/*
 * update item key.
 *
 * This function isn't completely safe. It's the caller's responsibility
 * that the new key won't अवरोध the order
 */
व्योम btrfs_set_item_key_safe(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा btrfs_path *path,
			     स्थिर काष्ठा btrfs_key *new_key)
अणु
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;

	eb = path->nodes[0];
	slot = path->slots[0];
	अगर (slot > 0) अणु
		btrfs_item_key(eb, &disk_key, slot - 1);
		अगर (unlikely(comp_keys(&disk_key, new_key) >= 0)) अणु
			btrfs_crit(fs_info,
		"slot %u key (%llu %u %llu) new key (%llu %u %llu)",
				   slot, btrfs_disk_key_objectid(&disk_key),
				   btrfs_disk_key_type(&disk_key),
				   btrfs_disk_key_offset(&disk_key),
				   new_key->objectid, new_key->type,
				   new_key->offset);
			btrfs_prपूर्णांक_leaf(eb);
			BUG();
		पूर्ण
	पूर्ण
	अगर (slot < btrfs_header_nritems(eb) - 1) अणु
		btrfs_item_key(eb, &disk_key, slot + 1);
		अगर (unlikely(comp_keys(&disk_key, new_key) <= 0)) अणु
			btrfs_crit(fs_info,
		"slot %u key (%llu %u %llu) new key (%llu %u %llu)",
				   slot, btrfs_disk_key_objectid(&disk_key),
				   btrfs_disk_key_type(&disk_key),
				   btrfs_disk_key_offset(&disk_key),
				   new_key->objectid, new_key->type,
				   new_key->offset);
			btrfs_prपूर्णांक_leaf(eb);
			BUG();
		पूर्ण
	पूर्ण

	btrfs_cpu_key_to_disk(&disk_key, new_key);
	btrfs_set_item_key(eb, &disk_key, slot);
	btrfs_mark_buffer_dirty(eb);
	अगर (slot == 0)
		fixup_low_keys(path, &disk_key, 1);
पूर्ण

/*
 * Check key order of two sibling extent buffers.
 *
 * Return true अगर something is wrong.
 * Return false अगर everything is fine.
 *
 * Tree-checker only works inside one tree block, thus the following
 * corruption can not be detected by tree-checker:
 *
 * Leaf @left			| Leaf @right
 * --------------------------------------------------------------
 * | 1 | 2 | 3 | 4 | 5 | f6 |   | 7 | 8 |
 *
 * Key f6 in leaf @left itself is valid, but not valid when the next
 * key in leaf @right is 7.
 * This can only be checked at tree block merge समय.
 * And since tree checker has ensured all key order in each tree block
 * is correct, we only need to bother the last key of @left and the first
 * key of @right.
 */
अटल bool check_sibling_keys(काष्ठा extent_buffer *left,
			       काष्ठा extent_buffer *right)
अणु
	काष्ठा btrfs_key left_last;
	काष्ठा btrfs_key right_first;
	पूर्णांक level = btrfs_header_level(left);
	पूर्णांक nr_left = btrfs_header_nritems(left);
	पूर्णांक nr_right = btrfs_header_nritems(right);

	/* No key to check in one of the tree blocks */
	अगर (!nr_left || !nr_right)
		वापस false;

	अगर (level) अणु
		btrfs_node_key_to_cpu(left, &left_last, nr_left - 1);
		btrfs_node_key_to_cpu(right, &right_first, 0);
	पूर्ण अन्यथा अणु
		btrfs_item_key_to_cpu(left, &left_last, nr_left - 1);
		btrfs_item_key_to_cpu(right, &right_first, 0);
	पूर्ण

	अगर (btrfs_comp_cpu_keys(&left_last, &right_first) >= 0) अणु
		btrfs_crit(left->fs_info,
"bad key order, sibling blocks, left last (%llu %u %llu) right first (%llu %u %llu)",
			   left_last.objectid, left_last.type,
			   left_last.offset, right_first.objectid,
			   right_first.type, right_first.offset);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * try to push data from one node पूर्णांकo the next node left in the
 * tree.
 *
 * वापसs 0 अगर some ptrs were pushed left, < 0 अगर there was some horrible
 * error, and > 0 अगर there was no room in the left hand block.
 */
अटल पूर्णांक push_node_left(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा extent_buffer *dst,
			  काष्ठा extent_buffer *src, पूर्णांक empty)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक push_items = 0;
	पूर्णांक src_nritems;
	पूर्णांक dst_nritems;
	पूर्णांक ret = 0;

	src_nritems = btrfs_header_nritems(src);
	dst_nritems = btrfs_header_nritems(dst);
	push_items = BTRFS_NODEPTRS_PER_BLOCK(fs_info) - dst_nritems;
	WARN_ON(btrfs_header_generation(src) != trans->transid);
	WARN_ON(btrfs_header_generation(dst) != trans->transid);

	अगर (!empty && src_nritems <= 8)
		वापस 1;

	अगर (push_items <= 0)
		वापस 1;

	अगर (empty) अणु
		push_items = min(src_nritems, push_items);
		अगर (push_items < src_nritems) अणु
			/* leave at least 8 poपूर्णांकers in the node अगर
			 * we aren't going to empty it
			 */
			अगर (src_nritems - push_items < 8) अणु
				अगर (push_items <= 8)
					वापस 1;
				push_items -= 8;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		push_items = min(src_nritems - 8, push_items);

	/* dst is the left eb, src is the middle eb */
	अगर (check_sibling_keys(dst, src)) अणु
		ret = -EUCLEAN;
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण
	ret = btrfs_tree_mod_log_eb_copy(dst, src, dst_nritems, 0, push_items);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण
	copy_extent_buffer(dst, src,
			   btrfs_node_key_ptr_offset(dst_nritems),
			   btrfs_node_key_ptr_offset(0),
			   push_items * माप(काष्ठा btrfs_key_ptr));

	अगर (push_items < src_nritems) अणु
		/*
		 * Don't call btrfs_tree_mod_log_insert_move() here, key removal
		 * was alपढ़ोy fully logged by btrfs_tree_mod_log_eb_copy() above.
		 */
		स_हटाओ_extent_buffer(src, btrfs_node_key_ptr_offset(0),
				      btrfs_node_key_ptr_offset(push_items),
				      (src_nritems - push_items) *
				      माप(काष्ठा btrfs_key_ptr));
	पूर्ण
	btrfs_set_header_nritems(src, src_nritems - push_items);
	btrfs_set_header_nritems(dst, dst_nritems + push_items);
	btrfs_mark_buffer_dirty(src);
	btrfs_mark_buffer_dirty(dst);

	वापस ret;
पूर्ण

/*
 * try to push data from one node पूर्णांकo the next node right in the
 * tree.
 *
 * वापसs 0 अगर some ptrs were pushed, < 0 अगर there was some horrible
 * error, and > 0 अगर there was no room in the right hand block.
 *
 * this will  only push up to 1/2 the contents of the left node over
 */
अटल पूर्णांक balance_node_right(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा extent_buffer *dst,
			      काष्ठा extent_buffer *src)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक push_items = 0;
	पूर्णांक max_push;
	पूर्णांक src_nritems;
	पूर्णांक dst_nritems;
	पूर्णांक ret = 0;

	WARN_ON(btrfs_header_generation(src) != trans->transid);
	WARN_ON(btrfs_header_generation(dst) != trans->transid);

	src_nritems = btrfs_header_nritems(src);
	dst_nritems = btrfs_header_nritems(dst);
	push_items = BTRFS_NODEPTRS_PER_BLOCK(fs_info) - dst_nritems;
	अगर (push_items <= 0)
		वापस 1;

	अगर (src_nritems < 4)
		वापस 1;

	max_push = src_nritems / 2 + 1;
	/* करोn't try to empty the node */
	अगर (max_push >= src_nritems)
		वापस 1;

	अगर (max_push < push_items)
		push_items = max_push;

	/* dst is the right eb, src is the middle eb */
	अगर (check_sibling_keys(src, dst)) अणु
		ret = -EUCLEAN;
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण
	ret = btrfs_tree_mod_log_insert_move(dst, push_items, 0, dst_nritems);
	BUG_ON(ret < 0);
	स_हटाओ_extent_buffer(dst, btrfs_node_key_ptr_offset(push_items),
				      btrfs_node_key_ptr_offset(0),
				      (dst_nritems) *
				      माप(काष्ठा btrfs_key_ptr));

	ret = btrfs_tree_mod_log_eb_copy(dst, src, 0, src_nritems - push_items,
					 push_items);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण
	copy_extent_buffer(dst, src,
			   btrfs_node_key_ptr_offset(0),
			   btrfs_node_key_ptr_offset(src_nritems - push_items),
			   push_items * माप(काष्ठा btrfs_key_ptr));

	btrfs_set_header_nritems(src, src_nritems - push_items);
	btrfs_set_header_nritems(dst, dst_nritems + push_items);

	btrfs_mark_buffer_dirty(src);
	btrfs_mark_buffer_dirty(dst);

	वापस ret;
पूर्ण

/*
 * helper function to insert a new root level in the tree.
 * A new node is allocated, and a single item is inserted to
 * poपूर्णांक to the existing root
 *
 * वापसs zero on success or < 0 on failure.
 */
अटल noअंतरभूत पूर्णांक insert_new_root(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   काष्ठा btrfs_path *path, पूर्णांक level)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 lower_gen;
	काष्ठा extent_buffer *lower;
	काष्ठा extent_buffer *c;
	काष्ठा extent_buffer *old;
	काष्ठा btrfs_disk_key lower_key;
	पूर्णांक ret;

	BUG_ON(path->nodes[level]);
	BUG_ON(path->nodes[level-1] != root->node);

	lower = path->nodes[level-1];
	अगर (level == 1)
		btrfs_item_key(lower, &lower_key, 0);
	अन्यथा
		btrfs_node_key(lower, &lower_key, 0);

	c = alloc_tree_block_no_bg_flush(trans, root, 0, &lower_key, level,
					 root->node->start, 0,
					 BTRFS_NESTING_NEW_ROOT);
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);

	root_add_used(root, fs_info->nodesize);

	btrfs_set_header_nritems(c, 1);
	btrfs_set_node_key(c, &lower_key, 0);
	btrfs_set_node_blockptr(c, 0, lower->start);
	lower_gen = btrfs_header_generation(lower);
	WARN_ON(lower_gen != trans->transid);

	btrfs_set_node_ptr_generation(c, 0, lower_gen);

	btrfs_mark_buffer_dirty(c);

	old = root->node;
	ret = btrfs_tree_mod_log_insert_root(root->node, c, false);
	BUG_ON(ret < 0);
	rcu_assign_poपूर्णांकer(root->node, c);

	/* the super has an extra ref to root->node */
	मुक्त_extent_buffer(old);

	add_root_to_dirty_list(root);
	atomic_inc(&c->refs);
	path->nodes[level] = c;
	path->locks[level] = BTRFS_WRITE_LOCK;
	path->slots[level] = 0;
	वापस 0;
पूर्ण

/*
 * worker function to insert a single poपूर्णांकer in a node.
 * the node should have enough room क्रम the poपूर्णांकer alपढ़ोy
 *
 * slot and level indicate where you want the key to go, and
 * blocknr is the block the key poपूर्णांकs to.
 */
अटल व्योम insert_ptr(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_path *path,
		       काष्ठा btrfs_disk_key *key, u64 bytenr,
		       पूर्णांक slot, पूर्णांक level)
अणु
	काष्ठा extent_buffer *lower;
	पूर्णांक nritems;
	पूर्णांक ret;

	BUG_ON(!path->nodes[level]);
	btrfs_निश्चित_tree_locked(path->nodes[level]);
	lower = path->nodes[level];
	nritems = btrfs_header_nritems(lower);
	BUG_ON(slot > nritems);
	BUG_ON(nritems == BTRFS_NODEPTRS_PER_BLOCK(trans->fs_info));
	अगर (slot != nritems) अणु
		अगर (level) अणु
			ret = btrfs_tree_mod_log_insert_move(lower, slot + 1,
					slot, nritems - slot);
			BUG_ON(ret < 0);
		पूर्ण
		स_हटाओ_extent_buffer(lower,
			      btrfs_node_key_ptr_offset(slot + 1),
			      btrfs_node_key_ptr_offset(slot),
			      (nritems - slot) * माप(काष्ठा btrfs_key_ptr));
	पूर्ण
	अगर (level) अणु
		ret = btrfs_tree_mod_log_insert_key(lower, slot,
					    BTRFS_MOD_LOG_KEY_ADD, GFP_NOFS);
		BUG_ON(ret < 0);
	पूर्ण
	btrfs_set_node_key(lower, key, slot);
	btrfs_set_node_blockptr(lower, slot, bytenr);
	WARN_ON(trans->transid == 0);
	btrfs_set_node_ptr_generation(lower, slot, trans->transid);
	btrfs_set_header_nritems(lower, nritems + 1);
	btrfs_mark_buffer_dirty(lower);
पूर्ण

/*
 * split the node at the specअगरied level in path in two.
 * The path is corrected to poपूर्णांक to the appropriate node after the split
 *
 * Beक्रमe splitting this tries to make some room in the node by pushing
 * left and right, अगर either one works, it वापसs right away.
 *
 * वापसs 0 on success and < 0 on failure
 */
अटल noअंतरभूत पूर्णांक split_node(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       काष्ठा btrfs_path *path, पूर्णांक level)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *c;
	काष्ठा extent_buffer *split;
	काष्ठा btrfs_disk_key disk_key;
	पूर्णांक mid;
	पूर्णांक ret;
	u32 c_nritems;

	c = path->nodes[level];
	WARN_ON(btrfs_header_generation(c) != trans->transid);
	अगर (c == root->node) अणु
		/*
		 * trying to split the root, lets make a new one
		 *
		 * tree mod log: We करोn't log_removal old root in
		 * insert_new_root, because that root buffer will be kept as a
		 * normal node. We are going to log removal of half of the
		 * elements below with btrfs_tree_mod_log_eb_copy(). We're
		 * holding a tree lock on the buffer, which is why we cannot
		 * race with other tree_mod_log users.
		 */
		ret = insert_new_root(trans, root, path, level + 1);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = push_nodes_क्रम_insert(trans, root, path, level);
		c = path->nodes[level];
		अगर (!ret && btrfs_header_nritems(c) <
		    BTRFS_NODEPTRS_PER_BLOCK(fs_info) - 3)
			वापस 0;
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	c_nritems = btrfs_header_nritems(c);
	mid = (c_nritems + 1) / 2;
	btrfs_node_key(c, &disk_key, mid);

	split = alloc_tree_block_no_bg_flush(trans, root, 0, &disk_key, level,
					     c->start, 0, BTRFS_NESTING_SPLIT);
	अगर (IS_ERR(split))
		वापस PTR_ERR(split);

	root_add_used(root, fs_info->nodesize);
	ASSERT(btrfs_header_level(c) == level);

	ret = btrfs_tree_mod_log_eb_copy(split, c, 0, mid, c_nritems - mid);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण
	copy_extent_buffer(split, c,
			   btrfs_node_key_ptr_offset(0),
			   btrfs_node_key_ptr_offset(mid),
			   (c_nritems - mid) * माप(काष्ठा btrfs_key_ptr));
	btrfs_set_header_nritems(split, c_nritems - mid);
	btrfs_set_header_nritems(c, mid);

	btrfs_mark_buffer_dirty(c);
	btrfs_mark_buffer_dirty(split);

	insert_ptr(trans, path, &disk_key, split->start,
		   path->slots[level + 1] + 1, level + 1);

	अगर (path->slots[level] >= mid) अणु
		path->slots[level] -= mid;
		btrfs_tree_unlock(c);
		मुक्त_extent_buffer(c);
		path->nodes[level] = split;
		path->slots[level + 1] += 1;
	पूर्ण अन्यथा अणु
		btrfs_tree_unlock(split);
		मुक्त_extent_buffer(split);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * how many bytes are required to store the items in a leaf.  start
 * and nr indicate which items in the leaf to check.  This totals up the
 * space used both by the item काष्ठाs and the item data
 */
अटल पूर्णांक leaf_space_used(काष्ठा extent_buffer *l, पूर्णांक start, पूर्णांक nr)
अणु
	काष्ठा btrfs_item *start_item;
	काष्ठा btrfs_item *end_item;
	पूर्णांक data_len;
	पूर्णांक nritems = btrfs_header_nritems(l);
	पूर्णांक end = min(nritems, start + nr) - 1;

	अगर (!nr)
		वापस 0;
	start_item = btrfs_item_nr(start);
	end_item = btrfs_item_nr(end);
	data_len = btrfs_item_offset(l, start_item) +
		   btrfs_item_size(l, start_item);
	data_len = data_len - btrfs_item_offset(l, end_item);
	data_len += माप(काष्ठा btrfs_item) * nr;
	WARN_ON(data_len < 0);
	वापस data_len;
पूर्ण

/*
 * The space between the end of the leaf items and
 * the start of the leaf data.  IOW, how much room
 * the leaf has left क्रम both items and data
 */
noअंतरभूत पूर्णांक btrfs_leaf_मुक्त_space(काष्ठा extent_buffer *leaf)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	पूर्णांक nritems = btrfs_header_nritems(leaf);
	पूर्णांक ret;

	ret = BTRFS_LEAF_DATA_SIZE(fs_info) - leaf_space_used(leaf, 0, nritems);
	अगर (ret < 0) अणु
		btrfs_crit(fs_info,
			   "leaf free space ret %d, leaf data size %lu, used %d nritems %d",
			   ret,
			   (अचिन्हित दीर्घ) BTRFS_LEAF_DATA_SIZE(fs_info),
			   leaf_space_used(leaf, 0, nritems), nritems);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * min slot controls the lowest index we're willing to push to the
 * right.  We'll push up to and including min_slot, but no lower
 */
अटल noअंतरभूत पूर्णांक __push_leaf_right(काष्ठा btrfs_path *path,
				      पूर्णांक data_size, पूर्णांक empty,
				      काष्ठा extent_buffer *right,
				      पूर्णांक मुक्त_space, u32 left_nritems,
				      u32 min_slot)
अणु
	काष्ठा btrfs_fs_info *fs_info = right->fs_info;
	काष्ठा extent_buffer *left = path->nodes[0];
	काष्ठा extent_buffer *upper = path->nodes[1];
	काष्ठा btrfs_map_token token;
	काष्ठा btrfs_disk_key disk_key;
	पूर्णांक slot;
	u32 i;
	पूर्णांक push_space = 0;
	पूर्णांक push_items = 0;
	काष्ठा btrfs_item *item;
	u32 nr;
	u32 right_nritems;
	u32 data_end;
	u32 this_item_size;

	अगर (empty)
		nr = 0;
	अन्यथा
		nr = max_t(u32, 1, min_slot);

	अगर (path->slots[0] >= left_nritems)
		push_space += data_size;

	slot = path->slots[1];
	i = left_nritems - 1;
	जबतक (i >= nr) अणु
		item = btrfs_item_nr(i);

		अगर (!empty && push_items > 0) अणु
			अगर (path->slots[0] > i)
				अवरोध;
			अगर (path->slots[0] == i) अणु
				पूर्णांक space = btrfs_leaf_मुक्त_space(left);

				अगर (space + push_space * 2 > मुक्त_space)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (path->slots[0] == i)
			push_space += data_size;

		this_item_size = btrfs_item_size(left, item);
		अगर (this_item_size + माप(*item) + push_space > मुक्त_space)
			अवरोध;

		push_items++;
		push_space += this_item_size + माप(*item);
		अगर (i == 0)
			अवरोध;
		i--;
	पूर्ण

	अगर (push_items == 0)
		जाओ out_unlock;

	WARN_ON(!empty && push_items == left_nritems);

	/* push left to right */
	right_nritems = btrfs_header_nritems(right);

	push_space = btrfs_item_end_nr(left, left_nritems - push_items);
	push_space -= leaf_data_end(left);

	/* make room in the right data area */
	data_end = leaf_data_end(right);
	स_हटाओ_extent_buffer(right,
			      BTRFS_LEAF_DATA_OFFSET + data_end - push_space,
			      BTRFS_LEAF_DATA_OFFSET + data_end,
			      BTRFS_LEAF_DATA_SIZE(fs_info) - data_end);

	/* copy from the left data area */
	copy_extent_buffer(right, left, BTRFS_LEAF_DATA_OFFSET +
		     BTRFS_LEAF_DATA_SIZE(fs_info) - push_space,
		     BTRFS_LEAF_DATA_OFFSET + leaf_data_end(left),
		     push_space);

	स_हटाओ_extent_buffer(right, btrfs_item_nr_offset(push_items),
			      btrfs_item_nr_offset(0),
			      right_nritems * माप(काष्ठा btrfs_item));

	/* copy the items from left to right */
	copy_extent_buffer(right, left, btrfs_item_nr_offset(0),
		   btrfs_item_nr_offset(left_nritems - push_items),
		   push_items * माप(काष्ठा btrfs_item));

	/* update the item poपूर्णांकers */
	btrfs_init_map_token(&token, right);
	right_nritems += push_items;
	btrfs_set_header_nritems(right, right_nritems);
	push_space = BTRFS_LEAF_DATA_SIZE(fs_info);
	क्रम (i = 0; i < right_nritems; i++) अणु
		item = btrfs_item_nr(i);
		push_space -= btrfs_token_item_size(&token, item);
		btrfs_set_token_item_offset(&token, item, push_space);
	पूर्ण

	left_nritems -= push_items;
	btrfs_set_header_nritems(left, left_nritems);

	अगर (left_nritems)
		btrfs_mark_buffer_dirty(left);
	अन्यथा
		btrfs_clean_tree_block(left);

	btrfs_mark_buffer_dirty(right);

	btrfs_item_key(right, &disk_key, 0);
	btrfs_set_node_key(upper, &disk_key, slot + 1);
	btrfs_mark_buffer_dirty(upper);

	/* then fixup the leaf poपूर्णांकer in the path */
	अगर (path->slots[0] >= left_nritems) अणु
		path->slots[0] -= left_nritems;
		अगर (btrfs_header_nritems(path->nodes[0]) == 0)
			btrfs_clean_tree_block(path->nodes[0]);
		btrfs_tree_unlock(path->nodes[0]);
		मुक्त_extent_buffer(path->nodes[0]);
		path->nodes[0] = right;
		path->slots[1] += 1;
	पूर्ण अन्यथा अणु
		btrfs_tree_unlock(right);
		मुक्त_extent_buffer(right);
	पूर्ण
	वापस 0;

out_unlock:
	btrfs_tree_unlock(right);
	मुक्त_extent_buffer(right);
	वापस 1;
पूर्ण

/*
 * push some data in the path leaf to the right, trying to मुक्त up at
 * least data_size bytes.  वापसs zero अगर the push worked, nonzero otherwise
 *
 * वापसs 1 अगर the push failed because the other node didn't have enough
 * room, 0 अगर everything worked out and < 0 अगर there were major errors.
 *
 * this will push starting from min_slot to the end of the leaf.  It won't
 * push any slot lower than min_slot
 */
अटल पूर्णांक push_leaf_right(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root
			   *root, काष्ठा btrfs_path *path,
			   पूर्णांक min_data_size, पूर्णांक data_size,
			   पूर्णांक empty, u32 min_slot)
अणु
	काष्ठा extent_buffer *left = path->nodes[0];
	काष्ठा extent_buffer *right;
	काष्ठा extent_buffer *upper;
	पूर्णांक slot;
	पूर्णांक मुक्त_space;
	u32 left_nritems;
	पूर्णांक ret;

	अगर (!path->nodes[1])
		वापस 1;

	slot = path->slots[1];
	upper = path->nodes[1];
	अगर (slot >= btrfs_header_nritems(upper) - 1)
		वापस 1;

	btrfs_निश्चित_tree_locked(path->nodes[1]);

	right = btrfs_पढ़ो_node_slot(upper, slot + 1);
	/*
	 * slot + 1 is not valid or we fail to पढ़ो the right node,
	 * no big deal, just वापस.
	 */
	अगर (IS_ERR(right))
		वापस 1;

	__btrfs_tree_lock(right, BTRFS_NESTING_RIGHT);

	मुक्त_space = btrfs_leaf_मुक्त_space(right);
	अगर (मुक्त_space < data_size)
		जाओ out_unlock;

	/* cow and द्विगुन check */
	ret = btrfs_cow_block(trans, root, right, upper,
			      slot + 1, &right, BTRFS_NESTING_RIGHT_COW);
	अगर (ret)
		जाओ out_unlock;

	मुक्त_space = btrfs_leaf_मुक्त_space(right);
	अगर (मुक्त_space < data_size)
		जाओ out_unlock;

	left_nritems = btrfs_header_nritems(left);
	अगर (left_nritems == 0)
		जाओ out_unlock;

	अगर (check_sibling_keys(left, right)) अणु
		ret = -EUCLEAN;
		btrfs_tree_unlock(right);
		मुक्त_extent_buffer(right);
		वापस ret;
	पूर्ण
	अगर (path->slots[0] == left_nritems && !empty) अणु
		/* Key greater than all keys in the leaf, right neighbor has
		 * enough room क्रम it and we're not emptying our leaf to delete
		 * it, thereक्रमe use right neighbor to insert the new item and
		 * no need to touch/dirty our left leaf. */
		btrfs_tree_unlock(left);
		मुक्त_extent_buffer(left);
		path->nodes[0] = right;
		path->slots[0] = 0;
		path->slots[1]++;
		वापस 0;
	पूर्ण

	वापस __push_leaf_right(path, min_data_size, empty,
				right, मुक्त_space, left_nritems, min_slot);
out_unlock:
	btrfs_tree_unlock(right);
	मुक्त_extent_buffer(right);
	वापस 1;
पूर्ण

/*
 * push some data in the path leaf to the left, trying to मुक्त up at
 * least data_size bytes.  वापसs zero अगर the push worked, nonzero otherwise
 *
 * max_slot can put a limit on how far पूर्णांकo the leaf we'll push items.  The
 * item at 'max_slot' won't be touched.  Use (u32)-1 to make us करो all the
 * items
 */
अटल noअंतरभूत पूर्णांक __push_leaf_left(काष्ठा btrfs_path *path, पूर्णांक data_size,
				     पूर्णांक empty, काष्ठा extent_buffer *left,
				     पूर्णांक मुक्त_space, u32 right_nritems,
				     u32 max_slot)
अणु
	काष्ठा btrfs_fs_info *fs_info = left->fs_info;
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा extent_buffer *right = path->nodes[0];
	पूर्णांक i;
	पूर्णांक push_space = 0;
	पूर्णांक push_items = 0;
	काष्ठा btrfs_item *item;
	u32 old_left_nritems;
	u32 nr;
	पूर्णांक ret = 0;
	u32 this_item_size;
	u32 old_left_item_size;
	काष्ठा btrfs_map_token token;

	अगर (empty)
		nr = min(right_nritems, max_slot);
	अन्यथा
		nr = min(right_nritems - 1, max_slot);

	क्रम (i = 0; i < nr; i++) अणु
		item = btrfs_item_nr(i);

		अगर (!empty && push_items > 0) अणु
			अगर (path->slots[0] < i)
				अवरोध;
			अगर (path->slots[0] == i) अणु
				पूर्णांक space = btrfs_leaf_मुक्त_space(right);

				अगर (space + push_space * 2 > मुक्त_space)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (path->slots[0] == i)
			push_space += data_size;

		this_item_size = btrfs_item_size(right, item);
		अगर (this_item_size + माप(*item) + push_space > मुक्त_space)
			अवरोध;

		push_items++;
		push_space += this_item_size + माप(*item);
	पूर्ण

	अगर (push_items == 0) अणु
		ret = 1;
		जाओ out;
	पूर्ण
	WARN_ON(!empty && push_items == btrfs_header_nritems(right));

	/* push data from right to left */
	copy_extent_buffer(left, right,
			   btrfs_item_nr_offset(btrfs_header_nritems(left)),
			   btrfs_item_nr_offset(0),
			   push_items * माप(काष्ठा btrfs_item));

	push_space = BTRFS_LEAF_DATA_SIZE(fs_info) -
		     btrfs_item_offset_nr(right, push_items - 1);

	copy_extent_buffer(left, right, BTRFS_LEAF_DATA_OFFSET +
		     leaf_data_end(left) - push_space,
		     BTRFS_LEAF_DATA_OFFSET +
		     btrfs_item_offset_nr(right, push_items - 1),
		     push_space);
	old_left_nritems = btrfs_header_nritems(left);
	BUG_ON(old_left_nritems <= 0);

	btrfs_init_map_token(&token, left);
	old_left_item_size = btrfs_item_offset_nr(left, old_left_nritems - 1);
	क्रम (i = old_left_nritems; i < old_left_nritems + push_items; i++) अणु
		u32 ioff;

		item = btrfs_item_nr(i);

		ioff = btrfs_token_item_offset(&token, item);
		btrfs_set_token_item_offset(&token, item,
		      ioff - (BTRFS_LEAF_DATA_SIZE(fs_info) - old_left_item_size));
	पूर्ण
	btrfs_set_header_nritems(left, old_left_nritems + push_items);

	/* fixup right node */
	अगर (push_items > right_nritems)
		WARN(1, KERN_CRIT "push items %d nr %u\n", push_items,
		       right_nritems);

	अगर (push_items < right_nritems) अणु
		push_space = btrfs_item_offset_nr(right, push_items - 1) -
						  leaf_data_end(right);
		स_हटाओ_extent_buffer(right, BTRFS_LEAF_DATA_OFFSET +
				      BTRFS_LEAF_DATA_SIZE(fs_info) - push_space,
				      BTRFS_LEAF_DATA_OFFSET +
				      leaf_data_end(right), push_space);

		स_हटाओ_extent_buffer(right, btrfs_item_nr_offset(0),
			      btrfs_item_nr_offset(push_items),
			     (btrfs_header_nritems(right) - push_items) *
			     माप(काष्ठा btrfs_item));
	पूर्ण

	btrfs_init_map_token(&token, right);
	right_nritems -= push_items;
	btrfs_set_header_nritems(right, right_nritems);
	push_space = BTRFS_LEAF_DATA_SIZE(fs_info);
	क्रम (i = 0; i < right_nritems; i++) अणु
		item = btrfs_item_nr(i);

		push_space = push_space - btrfs_token_item_size(&token, item);
		btrfs_set_token_item_offset(&token, item, push_space);
	पूर्ण

	btrfs_mark_buffer_dirty(left);
	अगर (right_nritems)
		btrfs_mark_buffer_dirty(right);
	अन्यथा
		btrfs_clean_tree_block(right);

	btrfs_item_key(right, &disk_key, 0);
	fixup_low_keys(path, &disk_key, 1);

	/* then fixup the leaf poपूर्णांकer in the path */
	अगर (path->slots[0] < push_items) अणु
		path->slots[0] += old_left_nritems;
		btrfs_tree_unlock(path->nodes[0]);
		मुक्त_extent_buffer(path->nodes[0]);
		path->nodes[0] = left;
		path->slots[1] -= 1;
	पूर्ण अन्यथा अणु
		btrfs_tree_unlock(left);
		मुक्त_extent_buffer(left);
		path->slots[0] -= push_items;
	पूर्ण
	BUG_ON(path->slots[0] < 0);
	वापस ret;
out:
	btrfs_tree_unlock(left);
	मुक्त_extent_buffer(left);
	वापस ret;
पूर्ण

/*
 * push some data in the path leaf to the left, trying to मुक्त up at
 * least data_size bytes.  वापसs zero अगर the push worked, nonzero otherwise
 *
 * max_slot can put a limit on how far पूर्णांकo the leaf we'll push items.  The
 * item at 'max_slot' won't be touched.  Use (u32)-1 to make us push all the
 * items
 */
अटल पूर्णांक push_leaf_left(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root
			  *root, काष्ठा btrfs_path *path, पूर्णांक min_data_size,
			  पूर्णांक data_size, पूर्णांक empty, u32 max_slot)
अणु
	काष्ठा extent_buffer *right = path->nodes[0];
	काष्ठा extent_buffer *left;
	पूर्णांक slot;
	पूर्णांक मुक्त_space;
	u32 right_nritems;
	पूर्णांक ret = 0;

	slot = path->slots[1];
	अगर (slot == 0)
		वापस 1;
	अगर (!path->nodes[1])
		वापस 1;

	right_nritems = btrfs_header_nritems(right);
	अगर (right_nritems == 0)
		वापस 1;

	btrfs_निश्चित_tree_locked(path->nodes[1]);

	left = btrfs_पढ़ो_node_slot(path->nodes[1], slot - 1);
	/*
	 * slot - 1 is not valid or we fail to पढ़ो the left node,
	 * no big deal, just वापस.
	 */
	अगर (IS_ERR(left))
		वापस 1;

	__btrfs_tree_lock(left, BTRFS_NESTING_LEFT);

	मुक्त_space = btrfs_leaf_मुक्त_space(left);
	अगर (मुक्त_space < data_size) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	/* cow and द्विगुन check */
	ret = btrfs_cow_block(trans, root, left,
			      path->nodes[1], slot - 1, &left,
			      BTRFS_NESTING_LEFT_COW);
	अगर (ret) अणु
		/* we hit -ENOSPC, but it isn't fatal here */
		अगर (ret == -ENOSPC)
			ret = 1;
		जाओ out;
	पूर्ण

	मुक्त_space = btrfs_leaf_मुक्त_space(left);
	अगर (मुक्त_space < data_size) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	अगर (check_sibling_keys(left, right)) अणु
		ret = -EUCLEAN;
		जाओ out;
	पूर्ण
	वापस __push_leaf_left(path, min_data_size,
			       empty, left, मुक्त_space, right_nritems,
			       max_slot);
out:
	btrfs_tree_unlock(left);
	मुक्त_extent_buffer(left);
	वापस ret;
पूर्ण

/*
 * split the path's leaf in two, making sure there is at least data_size
 * available क्रम the resulting leaf level of the path.
 */
अटल noअंतरभूत व्योम copy_क्रम_split(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_path *path,
				    काष्ठा extent_buffer *l,
				    काष्ठा extent_buffer *right,
				    पूर्णांक slot, पूर्णांक mid, पूर्णांक nritems)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक data_copy_size;
	पूर्णांक rt_data_off;
	पूर्णांक i;
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा btrfs_map_token token;

	nritems = nritems - mid;
	btrfs_set_header_nritems(right, nritems);
	data_copy_size = btrfs_item_end_nr(l, mid) - leaf_data_end(l);

	copy_extent_buffer(right, l, btrfs_item_nr_offset(0),
			   btrfs_item_nr_offset(mid),
			   nritems * माप(काष्ठा btrfs_item));

	copy_extent_buffer(right, l,
		     BTRFS_LEAF_DATA_OFFSET + BTRFS_LEAF_DATA_SIZE(fs_info) -
		     data_copy_size, BTRFS_LEAF_DATA_OFFSET +
		     leaf_data_end(l), data_copy_size);

	rt_data_off = BTRFS_LEAF_DATA_SIZE(fs_info) - btrfs_item_end_nr(l, mid);

	btrfs_init_map_token(&token, right);
	क्रम (i = 0; i < nritems; i++) अणु
		काष्ठा btrfs_item *item = btrfs_item_nr(i);
		u32 ioff;

		ioff = btrfs_token_item_offset(&token, item);
		btrfs_set_token_item_offset(&token, item, ioff + rt_data_off);
	पूर्ण

	btrfs_set_header_nritems(l, mid);
	btrfs_item_key(right, &disk_key, 0);
	insert_ptr(trans, path, &disk_key, right->start, path->slots[1] + 1, 1);

	btrfs_mark_buffer_dirty(right);
	btrfs_mark_buffer_dirty(l);
	BUG_ON(path->slots[0] != slot);

	अगर (mid <= slot) अणु
		btrfs_tree_unlock(path->nodes[0]);
		मुक्त_extent_buffer(path->nodes[0]);
		path->nodes[0] = right;
		path->slots[0] -= mid;
		path->slots[1] += 1;
	पूर्ण अन्यथा अणु
		btrfs_tree_unlock(right);
		मुक्त_extent_buffer(right);
	पूर्ण

	BUG_ON(path->slots[0] < 0);
पूर्ण

/*
 * द्विगुन splits happen when we need to insert a big item in the middle
 * of a leaf.  A द्विगुन split can leave us with 3 mostly empty leaves:
 * leaf: [ slots 0 - N] [ our target ] [ N + 1 - total in leaf ]
 *          A                 B                 C
 *
 * We aव्योम this by trying to push the items on either side of our target
 * पूर्णांकo the adjacent leaves.  If all goes well we can aव्योम the द्विगुन split
 * completely.
 */
अटल noअंतरभूत पूर्णांक push_क्रम_द्विगुन_split(काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_root *root,
					  काष्ठा btrfs_path *path,
					  पूर्णांक data_size)
अणु
	पूर्णांक ret;
	पूर्णांक progress = 0;
	पूर्णांक slot;
	u32 nritems;
	पूर्णांक space_needed = data_size;

	slot = path->slots[0];
	अगर (slot < btrfs_header_nritems(path->nodes[0]))
		space_needed -= btrfs_leaf_मुक्त_space(path->nodes[0]);

	/*
	 * try to push all the items after our slot पूर्णांकo the
	 * right leaf
	 */
	ret = push_leaf_right(trans, root, path, 1, space_needed, 0, slot);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0)
		progress++;

	nritems = btrfs_header_nritems(path->nodes[0]);
	/*
	 * our goal is to get our slot at the start or end of a leaf.  If
	 * we've done so we're करोne
	 */
	अगर (path->slots[0] == 0 || path->slots[0] == nritems)
		वापस 0;

	अगर (btrfs_leaf_मुक्त_space(path->nodes[0]) >= data_size)
		वापस 0;

	/* try to push all the items beक्रमe our slot पूर्णांकo the next leaf */
	slot = path->slots[0];
	space_needed = data_size;
	अगर (slot > 0)
		space_needed -= btrfs_leaf_मुक्त_space(path->nodes[0]);
	ret = push_leaf_left(trans, root, path, 1, space_needed, 0, slot);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0)
		progress++;

	अगर (progress)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * split the path's leaf in two, making sure there is at least data_size
 * available क्रम the resulting leaf level of the path.
 *
 * वापसs 0 अगर all went well and < 0 on failure.
 */
अटल noअंतरभूत पूर्णांक split_leaf(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       स्थिर काष्ठा btrfs_key *ins_key,
			       काष्ठा btrfs_path *path, पूर्णांक data_size,
			       पूर्णांक extend)
अणु
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा extent_buffer *l;
	u32 nritems;
	पूर्णांक mid;
	पूर्णांक slot;
	काष्ठा extent_buffer *right;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret = 0;
	पूर्णांक wret;
	पूर्णांक split;
	पूर्णांक num_द्विगुनs = 0;
	पूर्णांक tried_aव्योम_द्विगुन = 0;

	l = path->nodes[0];
	slot = path->slots[0];
	अगर (extend && data_size + btrfs_item_size_nr(l, slot) +
	    माप(काष्ठा btrfs_item) > BTRFS_LEAF_DATA_SIZE(fs_info))
		वापस -EOVERFLOW;

	/* first try to make some room by pushing left and right */
	अगर (data_size && path->nodes[1]) अणु
		पूर्णांक space_needed = data_size;

		अगर (slot < btrfs_header_nritems(l))
			space_needed -= btrfs_leaf_मुक्त_space(l);

		wret = push_leaf_right(trans, root, path, space_needed,
				       space_needed, 0, 0);
		अगर (wret < 0)
			वापस wret;
		अगर (wret) अणु
			space_needed = data_size;
			अगर (slot > 0)
				space_needed -= btrfs_leaf_मुक्त_space(l);
			wret = push_leaf_left(trans, root, path, space_needed,
					      space_needed, 0, (u32)-1);
			अगर (wret < 0)
				वापस wret;
		पूर्ण
		l = path->nodes[0];

		/* did the pushes work? */
		अगर (btrfs_leaf_मुक्त_space(l) >= data_size)
			वापस 0;
	पूर्ण

	अगर (!path->nodes[1]) अणु
		ret = insert_new_root(trans, root, path, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
again:
	split = 1;
	l = path->nodes[0];
	slot = path->slots[0];
	nritems = btrfs_header_nritems(l);
	mid = (nritems + 1) / 2;

	अगर (mid <= slot) अणु
		अगर (nritems == 1 ||
		    leaf_space_used(l, mid, nritems - mid) + data_size >
			BTRFS_LEAF_DATA_SIZE(fs_info)) अणु
			अगर (slot >= nritems) अणु
				split = 0;
			पूर्ण अन्यथा अणु
				mid = slot;
				अगर (mid != nritems &&
				    leaf_space_used(l, mid, nritems - mid) +
				    data_size > BTRFS_LEAF_DATA_SIZE(fs_info)) अणु
					अगर (data_size && !tried_aव्योम_द्विगुन)
						जाओ push_क्रम_द्विगुन;
					split = 2;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (leaf_space_used(l, 0, mid) + data_size >
			BTRFS_LEAF_DATA_SIZE(fs_info)) अणु
			अगर (!extend && data_size && slot == 0) अणु
				split = 0;
			पूर्ण अन्यथा अगर ((extend || !data_size) && slot == 0) अणु
				mid = 1;
			पूर्ण अन्यथा अणु
				mid = slot;
				अगर (mid != nritems &&
				    leaf_space_used(l, mid, nritems - mid) +
				    data_size > BTRFS_LEAF_DATA_SIZE(fs_info)) अणु
					अगर (data_size && !tried_aव्योम_द्विगुन)
						जाओ push_क्रम_द्विगुन;
					split = 2;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (split == 0)
		btrfs_cpu_key_to_disk(&disk_key, ins_key);
	अन्यथा
		btrfs_item_key(l, &disk_key, mid);

	/*
	 * We have to about BTRFS_NESTING_NEW_ROOT here अगर we've करोne a द्विगुन
	 * split, because we're only allowed to have MAX_LOCKDEP_SUBCLASSES
	 * subclasses, which is 8 at the समय of this patch, and we've maxed it
	 * out.  In the future we could add a
	 * BTRFS_NESTING_SPLIT_THE_SPLITTENING अगर we need to, but क्रम now just
	 * use BTRFS_NESTING_NEW_ROOT.
	 */
	right = alloc_tree_block_no_bg_flush(trans, root, 0, &disk_key, 0,
					     l->start, 0, num_द्विगुनs ?
					     BTRFS_NESTING_NEW_ROOT :
					     BTRFS_NESTING_SPLIT);
	अगर (IS_ERR(right))
		वापस PTR_ERR(right);

	root_add_used(root, fs_info->nodesize);

	अगर (split == 0) अणु
		अगर (mid <= slot) अणु
			btrfs_set_header_nritems(right, 0);
			insert_ptr(trans, path, &disk_key,
				   right->start, path->slots[1] + 1, 1);
			btrfs_tree_unlock(path->nodes[0]);
			मुक्त_extent_buffer(path->nodes[0]);
			path->nodes[0] = right;
			path->slots[0] = 0;
			path->slots[1] += 1;
		पूर्ण अन्यथा अणु
			btrfs_set_header_nritems(right, 0);
			insert_ptr(trans, path, &disk_key,
				   right->start, path->slots[1], 1);
			btrfs_tree_unlock(path->nodes[0]);
			मुक्त_extent_buffer(path->nodes[0]);
			path->nodes[0] = right;
			path->slots[0] = 0;
			अगर (path->slots[1] == 0)
				fixup_low_keys(path, &disk_key, 1);
		पूर्ण
		/*
		 * We create a new leaf 'right' क्रम the required ins_len and
		 * we'll करो btrfs_mark_buffer_dirty() on this leaf after copying
		 * the content of ins_len to 'right'.
		 */
		वापस ret;
	पूर्ण

	copy_क्रम_split(trans, path, l, right, slot, mid, nritems);

	अगर (split == 2) अणु
		BUG_ON(num_द्विगुनs != 0);
		num_द्विगुनs++;
		जाओ again;
	पूर्ण

	वापस 0;

push_क्रम_द्विगुन:
	push_क्रम_द्विगुन_split(trans, root, path, data_size);
	tried_aव्योम_द्विगुन = 1;
	अगर (btrfs_leaf_मुक्त_space(path->nodes[0]) >= data_size)
		वापस 0;
	जाओ again;
पूर्ण

अटल noअंतरभूत पूर्णांक setup_leaf_क्रम_split(काष्ठा btrfs_trans_handle *trans,
					 काष्ठा btrfs_root *root,
					 काष्ठा btrfs_path *path, पूर्णांक ins_len)
अणु
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_file_extent_item *fi;
	u64 extent_len = 0;
	u32 item_size;
	पूर्णांक ret;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);

	BUG_ON(key.type != BTRFS_EXTENT_DATA_KEY &&
	       key.type != BTRFS_EXTENT_CSUM_KEY);

	अगर (btrfs_leaf_मुक्त_space(leaf) >= ins_len)
		वापस 0;

	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	अगर (key.type == BTRFS_EXTENT_DATA_KEY) अणु
		fi = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		extent_len = btrfs_file_extent_num_bytes(leaf, fi);
	पूर्ण
	btrfs_release_path(path);

	path->keep_locks = 1;
	path->search_क्रम_split = 1;
	ret = btrfs_search_slot(trans, root, &key, path, 0, 1);
	path->search_क्रम_split = 0;
	अगर (ret > 0)
		ret = -EAGAIN;
	अगर (ret < 0)
		जाओ err;

	ret = -EAGAIN;
	leaf = path->nodes[0];
	/* अगर our item isn't there, वापस now */
	अगर (item_size != btrfs_item_size_nr(leaf, path->slots[0]))
		जाओ err;

	/* the leaf has  changed, it now has room.  वापस now */
	अगर (btrfs_leaf_मुक्त_space(path->nodes[0]) >= ins_len)
		जाओ err;

	अगर (key.type == BTRFS_EXTENT_DATA_KEY) अणु
		fi = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		अगर (extent_len != btrfs_file_extent_num_bytes(leaf, fi))
			जाओ err;
	पूर्ण

	ret = split_leaf(trans, root, &key, path, ins_len, 1);
	अगर (ret)
		जाओ err;

	path->keep_locks = 0;
	btrfs_unlock_up_safe(path, 1);
	वापस 0;
err:
	path->keep_locks = 0;
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक split_item(काष्ठा btrfs_path *path,
			       स्थिर काष्ठा btrfs_key *new_key,
			       अचिन्हित दीर्घ split_offset)
अणु
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_item *item;
	काष्ठा btrfs_item *new_item;
	पूर्णांक slot;
	अक्षर *buf;
	u32 nritems;
	u32 item_size;
	u32 orig_offset;
	काष्ठा btrfs_disk_key disk_key;

	leaf = path->nodes[0];
	BUG_ON(btrfs_leaf_मुक्त_space(leaf) < माप(काष्ठा btrfs_item));

	item = btrfs_item_nr(path->slots[0]);
	orig_offset = btrfs_item_offset(leaf, item);
	item_size = btrfs_item_size(leaf, item);

	buf = kदो_स्मृति(item_size, GFP_NOFS);
	अगर (!buf)
		वापस -ENOMEM;

	पढ़ो_extent_buffer(leaf, buf, btrfs_item_ptr_offset(leaf,
			    path->slots[0]), item_size);

	slot = path->slots[0] + 1;
	nritems = btrfs_header_nritems(leaf);
	अगर (slot != nritems) अणु
		/* shअगरt the items */
		स_हटाओ_extent_buffer(leaf, btrfs_item_nr_offset(slot + 1),
				btrfs_item_nr_offset(slot),
				(nritems - slot) * माप(काष्ठा btrfs_item));
	पूर्ण

	btrfs_cpu_key_to_disk(&disk_key, new_key);
	btrfs_set_item_key(leaf, &disk_key, slot);

	new_item = btrfs_item_nr(slot);

	btrfs_set_item_offset(leaf, new_item, orig_offset);
	btrfs_set_item_size(leaf, new_item, item_size - split_offset);

	btrfs_set_item_offset(leaf, item,
			      orig_offset + item_size - split_offset);
	btrfs_set_item_size(leaf, item, split_offset);

	btrfs_set_header_nritems(leaf, nritems + 1);

	/* ग_लिखो the data क्रम the start of the original item */
	ग_लिखो_extent_buffer(leaf, buf,
			    btrfs_item_ptr_offset(leaf, path->slots[0]),
			    split_offset);

	/* ग_लिखो the data क्रम the new item */
	ग_लिखो_extent_buffer(leaf, buf + split_offset,
			    btrfs_item_ptr_offset(leaf, slot),
			    item_size - split_offset);
	btrfs_mark_buffer_dirty(leaf);

	BUG_ON(btrfs_leaf_मुक्त_space(leaf) < 0);
	kमुक्त(buf);
	वापस 0;
पूर्ण

/*
 * This function splits a single item पूर्णांकo two items,
 * giving 'new_key' to the new item and splitting the
 * old one at split_offset (from the start of the item).
 *
 * The path may be released by this operation.  After
 * the split, the path is poपूर्णांकing to the old item.  The
 * new item is going to be in the same node as the old one.
 *
 * Note, the item being split must be smaller enough to live alone on
 * a tree block with room क्रम one extra काष्ठा btrfs_item
 *
 * This allows us to split the item in place, keeping a lock on the
 * leaf the entire समय.
 */
पूर्णांक btrfs_split_item(काष्ठा btrfs_trans_handle *trans,
		     काष्ठा btrfs_root *root,
		     काष्ठा btrfs_path *path,
		     स्थिर काष्ठा btrfs_key *new_key,
		     अचिन्हित दीर्घ split_offset)
अणु
	पूर्णांक ret;
	ret = setup_leaf_क्रम_split(trans, root, path,
				   माप(काष्ठा btrfs_item));
	अगर (ret)
		वापस ret;

	ret = split_item(path, new_key, split_offset);
	वापस ret;
पूर्ण

/*
 * This function duplicate a item, giving 'new_key' to the new item.
 * It guarantees both items live in the same tree leaf and the new item
 * is contiguous with the original item.
 *
 * This allows us to split file extent in place, keeping a lock on the
 * leaf the entire समय.
 */
पूर्णांक btrfs_duplicate_item(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_root *root,
			 काष्ठा btrfs_path *path,
			 स्थिर काष्ठा btrfs_key *new_key)
अणु
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret;
	u32 item_size;

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	ret = setup_leaf_क्रम_split(trans, root, path,
				   item_size + माप(काष्ठा btrfs_item));
	अगर (ret)
		वापस ret;

	path->slots[0]++;
	setup_items_क्रम_insert(root, path, new_key, &item_size, 1);
	leaf = path->nodes[0];
	स_नकल_extent_buffer(leaf,
			     btrfs_item_ptr_offset(leaf, path->slots[0]),
			     btrfs_item_ptr_offset(leaf, path->slots[0] - 1),
			     item_size);
	वापस 0;
पूर्ण

/*
 * make the item poपूर्णांकed to by the path smaller.  new_size indicates
 * how small to make it, and from_end tells us अगर we just chop bytes
 * off the end of the item or अगर we shअगरt the item to chop bytes off
 * the front.
 */
व्योम btrfs_truncate_item(काष्ठा btrfs_path *path, u32 new_size, पूर्णांक from_end)
अणु
	पूर्णांक slot;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_item *item;
	u32 nritems;
	अचिन्हित पूर्णांक data_end;
	अचिन्हित पूर्णांक old_data_start;
	अचिन्हित पूर्णांक old_size;
	अचिन्हित पूर्णांक size_dअगरf;
	पूर्णांक i;
	काष्ठा btrfs_map_token token;

	leaf = path->nodes[0];
	slot = path->slots[0];

	old_size = btrfs_item_size_nr(leaf, slot);
	अगर (old_size == new_size)
		वापस;

	nritems = btrfs_header_nritems(leaf);
	data_end = leaf_data_end(leaf);

	old_data_start = btrfs_item_offset_nr(leaf, slot);

	size_dअगरf = old_size - new_size;

	BUG_ON(slot < 0);
	BUG_ON(slot >= nritems);

	/*
	 * item0..itemN ... dataN.offset..dataN.size .. data0.size
	 */
	/* first correct the data poपूर्णांकers */
	btrfs_init_map_token(&token, leaf);
	क्रम (i = slot; i < nritems; i++) अणु
		u32 ioff;
		item = btrfs_item_nr(i);

		ioff = btrfs_token_item_offset(&token, item);
		btrfs_set_token_item_offset(&token, item, ioff + size_dअगरf);
	पूर्ण

	/* shअगरt the data */
	अगर (from_end) अणु
		स_हटाओ_extent_buffer(leaf, BTRFS_LEAF_DATA_OFFSET +
			      data_end + size_dअगरf, BTRFS_LEAF_DATA_OFFSET +
			      data_end, old_data_start + new_size - data_end);
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_disk_key disk_key;
		u64 offset;

		btrfs_item_key(leaf, &disk_key, slot);

		अगर (btrfs_disk_key_type(&disk_key) == BTRFS_EXTENT_DATA_KEY) अणु
			अचिन्हित दीर्घ ptr;
			काष्ठा btrfs_file_extent_item *fi;

			fi = btrfs_item_ptr(leaf, slot,
					    काष्ठा btrfs_file_extent_item);
			fi = (काष्ठा btrfs_file_extent_item *)(
			     (अचिन्हित दीर्घ)fi - size_dअगरf);

			अगर (btrfs_file_extent_type(leaf, fi) ==
			    BTRFS_खाता_EXTENT_INLINE) अणु
				ptr = btrfs_item_ptr_offset(leaf, slot);
				स_हटाओ_extent_buffer(leaf, ptr,
				      (अचिन्हित दीर्घ)fi,
				      BTRFS_खाता_EXTENT_INLINE_DATA_START);
			पूर्ण
		पूर्ण

		स_हटाओ_extent_buffer(leaf, BTRFS_LEAF_DATA_OFFSET +
			      data_end + size_dअगरf, BTRFS_LEAF_DATA_OFFSET +
			      data_end, old_data_start - data_end);

		offset = btrfs_disk_key_offset(&disk_key);
		btrfs_set_disk_key_offset(&disk_key, offset + size_dअगरf);
		btrfs_set_item_key(leaf, &disk_key, slot);
		अगर (slot == 0)
			fixup_low_keys(path, &disk_key, 1);
	पूर्ण

	item = btrfs_item_nr(slot);
	btrfs_set_item_size(leaf, item, new_size);
	btrfs_mark_buffer_dirty(leaf);

	अगर (btrfs_leaf_मुक्त_space(leaf) < 0) अणु
		btrfs_prपूर्णांक_leaf(leaf);
		BUG();
	पूर्ण
पूर्ण

/*
 * make the item poपूर्णांकed to by the path bigger, data_size is the added size.
 */
व्योम btrfs_extend_item(काष्ठा btrfs_path *path, u32 data_size)
अणु
	पूर्णांक slot;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_item *item;
	u32 nritems;
	अचिन्हित पूर्णांक data_end;
	अचिन्हित पूर्णांक old_data;
	अचिन्हित पूर्णांक old_size;
	पूर्णांक i;
	काष्ठा btrfs_map_token token;

	leaf = path->nodes[0];

	nritems = btrfs_header_nritems(leaf);
	data_end = leaf_data_end(leaf);

	अगर (btrfs_leaf_मुक्त_space(leaf) < data_size) अणु
		btrfs_prपूर्णांक_leaf(leaf);
		BUG();
	पूर्ण
	slot = path->slots[0];
	old_data = btrfs_item_end_nr(leaf, slot);

	BUG_ON(slot < 0);
	अगर (slot >= nritems) अणु
		btrfs_prपूर्णांक_leaf(leaf);
		btrfs_crit(leaf->fs_info, "slot %d too large, nritems %d",
			   slot, nritems);
		BUG();
	पूर्ण

	/*
	 * item0..itemN ... dataN.offset..dataN.size .. data0.size
	 */
	/* first correct the data poपूर्णांकers */
	btrfs_init_map_token(&token, leaf);
	क्रम (i = slot; i < nritems; i++) अणु
		u32 ioff;
		item = btrfs_item_nr(i);

		ioff = btrfs_token_item_offset(&token, item);
		btrfs_set_token_item_offset(&token, item, ioff - data_size);
	पूर्ण

	/* shअगरt the data */
	स_हटाओ_extent_buffer(leaf, BTRFS_LEAF_DATA_OFFSET +
		      data_end - data_size, BTRFS_LEAF_DATA_OFFSET +
		      data_end, old_data - data_end);

	data_end = old_data;
	old_size = btrfs_item_size_nr(leaf, slot);
	item = btrfs_item_nr(slot);
	btrfs_set_item_size(leaf, item, old_size + data_size);
	btrfs_mark_buffer_dirty(leaf);

	अगर (btrfs_leaf_मुक्त_space(leaf) < 0) अणु
		btrfs_prपूर्णांक_leaf(leaf);
		BUG();
	पूर्ण
पूर्ण

/**
 * setup_items_क्रम_insert - Helper called beक्रमe inserting one or more items
 * to a leaf. Main purpose is to save stack depth by करोing the bulk of the work
 * in a function that करोesn't call btrfs_search_slot
 *
 * @root:	root we are inserting items to
 * @path:	poपूर्णांकs to the leaf/slot where we are going to insert new items
 * @cpu_key:	array of keys क्रम items to be inserted
 * @data_size:	size of the body of each item we are going to insert
 * @nr:		size of @cpu_key/@data_size arrays
 */
व्योम setup_items_क्रम_insert(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			    स्थिर काष्ठा btrfs_key *cpu_key, u32 *data_size,
			    पूर्णांक nr)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_item *item;
	पूर्णांक i;
	u32 nritems;
	अचिन्हित पूर्णांक data_end;
	काष्ठा btrfs_disk_key disk_key;
	काष्ठा extent_buffer *leaf;
	पूर्णांक slot;
	काष्ठा btrfs_map_token token;
	u32 total_size;
	u32 total_data = 0;

	क्रम (i = 0; i < nr; i++)
		total_data += data_size[i];
	total_size = total_data + (nr * माप(काष्ठा btrfs_item));

	अगर (path->slots[0] == 0) अणु
		btrfs_cpu_key_to_disk(&disk_key, cpu_key);
		fixup_low_keys(path, &disk_key, 1);
	पूर्ण
	btrfs_unlock_up_safe(path, 1);

	leaf = path->nodes[0];
	slot = path->slots[0];

	nritems = btrfs_header_nritems(leaf);
	data_end = leaf_data_end(leaf);

	अगर (btrfs_leaf_मुक्त_space(leaf) < total_size) अणु
		btrfs_prपूर्णांक_leaf(leaf);
		btrfs_crit(fs_info, "not enough freespace need %u have %d",
			   total_size, btrfs_leaf_मुक्त_space(leaf));
		BUG();
	पूर्ण

	btrfs_init_map_token(&token, leaf);
	अगर (slot != nritems) अणु
		अचिन्हित पूर्णांक old_data = btrfs_item_end_nr(leaf, slot);

		अगर (old_data < data_end) अणु
			btrfs_prपूर्णांक_leaf(leaf);
			btrfs_crit(fs_info,
		"item at slot %d with data offset %u beyond data end of leaf %u",
				   slot, old_data, data_end);
			BUG();
		पूर्ण
		/*
		 * item0..itemN ... dataN.offset..dataN.size .. data0.size
		 */
		/* first correct the data poपूर्णांकers */
		क्रम (i = slot; i < nritems; i++) अणु
			u32 ioff;

			item = btrfs_item_nr(i);
			ioff = btrfs_token_item_offset(&token, item);
			btrfs_set_token_item_offset(&token, item,
						    ioff - total_data);
		पूर्ण
		/* shअगरt the items */
		स_हटाओ_extent_buffer(leaf, btrfs_item_nr_offset(slot + nr),
			      btrfs_item_nr_offset(slot),
			      (nritems - slot) * माप(काष्ठा btrfs_item));

		/* shअगरt the data */
		स_हटाओ_extent_buffer(leaf, BTRFS_LEAF_DATA_OFFSET +
			      data_end - total_data, BTRFS_LEAF_DATA_OFFSET +
			      data_end, old_data - data_end);
		data_end = old_data;
	पूर्ण

	/* setup the item क्रम the new data */
	क्रम (i = 0; i < nr; i++) अणु
		btrfs_cpu_key_to_disk(&disk_key, cpu_key + i);
		btrfs_set_item_key(leaf, &disk_key, slot + i);
		item = btrfs_item_nr(slot + i);
		data_end -= data_size[i];
		btrfs_set_token_item_offset(&token, item, data_end);
		btrfs_set_token_item_size(&token, item, data_size[i]);
	पूर्ण

	btrfs_set_header_nritems(leaf, nritems + nr);
	btrfs_mark_buffer_dirty(leaf);

	अगर (btrfs_leaf_मुक्त_space(leaf) < 0) अणु
		btrfs_prपूर्णांक_leaf(leaf);
		BUG();
	पूर्ण
पूर्ण

/*
 * Given a key and some data, insert items पूर्णांकo the tree.
 * This करोes all the path init required, making room in the tree अगर needed.
 */
पूर्णांक btrfs_insert_empty_items(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root,
			    काष्ठा btrfs_path *path,
			    स्थिर काष्ठा btrfs_key *cpu_key, u32 *data_size,
			    पूर्णांक nr)
अणु
	पूर्णांक ret = 0;
	पूर्णांक slot;
	पूर्णांक i;
	u32 total_size = 0;
	u32 total_data = 0;

	क्रम (i = 0; i < nr; i++)
		total_data += data_size[i];

	total_size = total_data + (nr * माप(काष्ठा btrfs_item));
	ret = btrfs_search_slot(trans, root, cpu_key, path, total_size, 1);
	अगर (ret == 0)
		वापस -EEXIST;
	अगर (ret < 0)
		वापस ret;

	slot = path->slots[0];
	BUG_ON(slot < 0);

	setup_items_क्रम_insert(root, path, cpu_key, data_size, nr);
	वापस 0;
पूर्ण

/*
 * Given a key and some data, insert an item पूर्णांकo the tree.
 * This करोes all the path init required, making room in the tree अगर needed.
 */
पूर्णांक btrfs_insert_item(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		      स्थिर काष्ठा btrfs_key *cpu_key, व्योम *data,
		      u32 data_size)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ ptr;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	ret = btrfs_insert_empty_item(trans, root, path, cpu_key, data_size);
	अगर (!ret) अणु
		leaf = path->nodes[0];
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		ग_लिखो_extent_buffer(leaf, data, ptr, data_size);
		btrfs_mark_buffer_dirty(leaf);
	पूर्ण
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * delete the poपूर्णांकer from a given node.
 *
 * the tree should have been previously balanced so the deletion करोes not
 * empty a node.
 */
अटल व्योम del_ptr(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
		    पूर्णांक level, पूर्णांक slot)
अणु
	काष्ठा extent_buffer *parent = path->nodes[level];
	u32 nritems;
	पूर्णांक ret;

	nritems = btrfs_header_nritems(parent);
	अगर (slot != nritems - 1) अणु
		अगर (level) अणु
			ret = btrfs_tree_mod_log_insert_move(parent, slot,
					slot + 1, nritems - slot - 1);
			BUG_ON(ret < 0);
		पूर्ण
		स_हटाओ_extent_buffer(parent,
			      btrfs_node_key_ptr_offset(slot),
			      btrfs_node_key_ptr_offset(slot + 1),
			      माप(काष्ठा btrfs_key_ptr) *
			      (nritems - slot - 1));
	पूर्ण अन्यथा अगर (level) अणु
		ret = btrfs_tree_mod_log_insert_key(parent, slot,
				BTRFS_MOD_LOG_KEY_REMOVE, GFP_NOFS);
		BUG_ON(ret < 0);
	पूर्ण

	nritems--;
	btrfs_set_header_nritems(parent, nritems);
	अगर (nritems == 0 && parent == root->node) अणु
		BUG_ON(btrfs_header_level(root->node) != 1);
		/* just turn the root पूर्णांकo a leaf and अवरोध */
		btrfs_set_header_level(root->node, 0);
	पूर्ण अन्यथा अगर (slot == 0) अणु
		काष्ठा btrfs_disk_key disk_key;

		btrfs_node_key(parent, &disk_key, 0);
		fixup_low_keys(path, &disk_key, level + 1);
	पूर्ण
	btrfs_mark_buffer_dirty(parent);
पूर्ण

/*
 * a helper function to delete the leaf poपूर्णांकed to by path->slots[1] and
 * path->nodes[1].
 *
 * This deletes the poपूर्णांकer in path->nodes[1] and मुक्तs the leaf
 * block extent.  zero is वापसed अगर it all worked out, < 0 otherwise.
 *
 * The path must have alपढ़ोy been setup क्रम deleting the leaf, including
 * all the proper balancing.  path->nodes[1] must be locked.
 */
अटल noअंतरभूत व्योम btrfs_del_leaf(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_root *root,
				    काष्ठा btrfs_path *path,
				    काष्ठा extent_buffer *leaf)
अणु
	WARN_ON(btrfs_header_generation(leaf) != trans->transid);
	del_ptr(root, path, 1, path->slots[1]);

	/*
	 * btrfs_मुक्त_extent is expensive, we want to make sure we
	 * aren't holding any locks when we call it
	 */
	btrfs_unlock_up_safe(path, 0);

	root_sub_used(root, leaf->len);

	atomic_inc(&leaf->refs);
	btrfs_मुक्त_tree_block(trans, root, leaf, 0, 1);
	मुक्त_extent_buffer_stale(leaf);
पूर्ण
/*
 * delete the item at the leaf level in path.  If that empties
 * the leaf, हटाओ it from the tree
 */
पूर्णांक btrfs_del_items(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		    काष्ठा btrfs_path *path, पूर्णांक slot, पूर्णांक nr)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_item *item;
	u32 last_off;
	u32 dsize = 0;
	पूर्णांक ret = 0;
	पूर्णांक wret;
	पूर्णांक i;
	u32 nritems;

	leaf = path->nodes[0];
	last_off = btrfs_item_offset_nr(leaf, slot + nr - 1);

	क्रम (i = 0; i < nr; i++)
		dsize += btrfs_item_size_nr(leaf, slot + i);

	nritems = btrfs_header_nritems(leaf);

	अगर (slot + nr != nritems) अणु
		पूर्णांक data_end = leaf_data_end(leaf);
		काष्ठा btrfs_map_token token;

		स_हटाओ_extent_buffer(leaf, BTRFS_LEAF_DATA_OFFSET +
			      data_end + dsize,
			      BTRFS_LEAF_DATA_OFFSET + data_end,
			      last_off - data_end);

		btrfs_init_map_token(&token, leaf);
		क्रम (i = slot + nr; i < nritems; i++) अणु
			u32 ioff;

			item = btrfs_item_nr(i);
			ioff = btrfs_token_item_offset(&token, item);
			btrfs_set_token_item_offset(&token, item, ioff + dsize);
		पूर्ण

		स_हटाओ_extent_buffer(leaf, btrfs_item_nr_offset(slot),
			      btrfs_item_nr_offset(slot + nr),
			      माप(काष्ठा btrfs_item) *
			      (nritems - slot - nr));
	पूर्ण
	btrfs_set_header_nritems(leaf, nritems - nr);
	nritems -= nr;

	/* delete the leaf अगर we've emptied it */
	अगर (nritems == 0) अणु
		अगर (leaf == root->node) अणु
			btrfs_set_header_level(leaf, 0);
		पूर्ण अन्यथा अणु
			btrfs_clean_tree_block(leaf);
			btrfs_del_leaf(trans, root, path, leaf);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक used = leaf_space_used(leaf, 0, nritems);
		अगर (slot == 0) अणु
			काष्ठा btrfs_disk_key disk_key;

			btrfs_item_key(leaf, &disk_key, 0);
			fixup_low_keys(path, &disk_key, 1);
		पूर्ण

		/* delete the leaf अगर it is mostly empty */
		अगर (used < BTRFS_LEAF_DATA_SIZE(fs_info) / 3) अणु
			/* push_leaf_left fixes the path.
			 * make sure the path still poपूर्णांकs to our leaf
			 * क्रम possible call to del_ptr below
			 */
			slot = path->slots[1];
			atomic_inc(&leaf->refs);

			wret = push_leaf_left(trans, root, path, 1, 1,
					      1, (u32)-1);
			अगर (wret < 0 && wret != -ENOSPC)
				ret = wret;

			अगर (path->nodes[0] == leaf &&
			    btrfs_header_nritems(leaf)) अणु
				wret = push_leaf_right(trans, root, path, 1,
						       1, 1, 0);
				अगर (wret < 0 && wret != -ENOSPC)
					ret = wret;
			पूर्ण

			अगर (btrfs_header_nritems(leaf) == 0) अणु
				path->slots[1] = slot;
				btrfs_del_leaf(trans, root, path, leaf);
				मुक्त_extent_buffer(leaf);
				ret = 0;
			पूर्ण अन्यथा अणु
				/* अगर we're still in the path, make sure
				 * we're dirty.  Otherwise, one of the
				 * push_leaf functions must have alपढ़ोy
				 * dirtied this buffer
				 */
				अगर (path->nodes[0] == leaf)
					btrfs_mark_buffer_dirty(leaf);
				मुक्त_extent_buffer(leaf);
			पूर्ण
		पूर्ण अन्यथा अणु
			btrfs_mark_buffer_dirty(leaf);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * search the tree again to find a leaf with lesser keys
 * वापसs 0 अगर it found something or 1 अगर there are no lesser leaves.
 * वापसs < 0 on io errors.
 *
 * This may release the path, and so you may lose any locks held at the
 * समय you call it.
 */
पूर्णांक btrfs_prev_leaf(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_disk_key found_key;
	पूर्णांक ret;

	btrfs_item_key_to_cpu(path->nodes[0], &key, 0);

	अगर (key.offset > 0) अणु
		key.offset--;
	पूर्ण अन्यथा अगर (key.type > 0) अणु
		key.type--;
		key.offset = (u64)-1;
	पूर्ण अन्यथा अगर (key.objectid > 0) अणु
		key.objectid--;
		key.type = (u8)-1;
		key.offset = (u64)-1;
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण

	btrfs_release_path(path);
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;
	btrfs_item_key(path->nodes[0], &found_key, 0);
	ret = comp_keys(&found_key, &key);
	/*
	 * We might have had an item with the previous key in the tree right
	 * beक्रमe we released our path. And after we released our path, that
	 * item might have been pushed to the first slot (0) of the leaf we
	 * were holding due to a tree balance. Alternatively, an item with the
	 * previous key can exist as the only element of a leaf (big fat item).
	 * Thereक्रमe account क्रम these 2 हालs, so that our callers (like
	 * btrfs_previous_item) करोn't miss an existing item with a key matching
	 * the previous key we computed above.
	 */
	अगर (ret <= 0)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * A helper function to walk करोwn the tree starting at min_key, and looking
 * क्रम nodes or leaves that are have a minimum transaction id.
 * This is used by the btree defrag code, and tree logging
 *
 * This करोes not cow, but it करोes stuff the starting key it finds back
 * पूर्णांकo min_key, so you can call btrfs_search_slot with cow=1 on the
 * key and get a writable path.
 *
 * This honors path->lowest_level to prevent descent past a given level
 * of the tree.
 *
 * min_trans indicates the oldest transaction that you are पूर्णांकerested
 * in walking through.  Any nodes or leaves older than min_trans are
 * skipped over (without पढ़ोing them).
 *
 * वापसs zero अगर something useful was found, < 0 on error and 1 अगर there
 * was nothing in the tree that matched the search criteria.
 */
पूर्णांक btrfs_search_क्रमward(काष्ठा btrfs_root *root, काष्ठा btrfs_key *min_key,
			 काष्ठा btrfs_path *path,
			 u64 min_trans)
अणु
	काष्ठा extent_buffer *cur;
	काष्ठा btrfs_key found_key;
	पूर्णांक slot;
	पूर्णांक sret;
	u32 nritems;
	पूर्णांक level;
	पूर्णांक ret = 1;
	पूर्णांक keep_locks = path->keep_locks;

	path->keep_locks = 1;
again:
	cur = btrfs_पढ़ो_lock_root_node(root);
	level = btrfs_header_level(cur);
	WARN_ON(path->nodes[level]);
	path->nodes[level] = cur;
	path->locks[level] = BTRFS_READ_LOCK;

	अगर (btrfs_header_generation(cur) < min_trans) अणु
		ret = 1;
		जाओ out;
	पूर्ण
	जबतक (1) अणु
		nritems = btrfs_header_nritems(cur);
		level = btrfs_header_level(cur);
		sret = btrfs_bin_search(cur, min_key, &slot);
		अगर (sret < 0) अणु
			ret = sret;
			जाओ out;
		पूर्ण

		/* at the lowest level, we're करोne, setup the path and निकास */
		अगर (level == path->lowest_level) अणु
			अगर (slot >= nritems)
				जाओ find_next_key;
			ret = 0;
			path->slots[level] = slot;
			btrfs_item_key_to_cpu(cur, &found_key, slot);
			जाओ out;
		पूर्ण
		अगर (sret && slot > 0)
			slot--;
		/*
		 * check this node poपूर्णांकer against the min_trans parameters.
		 * If it is too old, skip to the next one.
		 */
		जबतक (slot < nritems) अणु
			u64 gen;

			gen = btrfs_node_ptr_generation(cur, slot);
			अगर (gen < min_trans) अणु
				slot++;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
find_next_key:
		/*
		 * we didn't find a candidate key in this node, walk क्रमward
		 * and find another one
		 */
		अगर (slot >= nritems) अणु
			path->slots[level] = slot;
			sret = btrfs_find_next_key(root, path, min_key, level,
						  min_trans);
			अगर (sret == 0) अणु
				btrfs_release_path(path);
				जाओ again;
			पूर्ण अन्यथा अणु
				जाओ out;
			पूर्ण
		पूर्ण
		/* save our key क्रम वापसing back */
		btrfs_node_key_to_cpu(cur, &found_key, slot);
		path->slots[level] = slot;
		अगर (level == path->lowest_level) अणु
			ret = 0;
			जाओ out;
		पूर्ण
		cur = btrfs_पढ़ो_node_slot(cur, slot);
		अगर (IS_ERR(cur)) अणु
			ret = PTR_ERR(cur);
			जाओ out;
		पूर्ण

		btrfs_tree_पढ़ो_lock(cur);

		path->locks[level - 1] = BTRFS_READ_LOCK;
		path->nodes[level - 1] = cur;
		unlock_up(path, level, 1, 0, शून्य);
	पूर्ण
out:
	path->keep_locks = keep_locks;
	अगर (ret == 0) अणु
		btrfs_unlock_up_safe(path, path->lowest_level + 1);
		स_नकल(min_key, &found_key, माप(found_key));
	पूर्ण
	वापस ret;
पूर्ण

/*
 * this is similar to btrfs_next_leaf, but करोes not try to preserve
 * and fixup the path.  It looks क्रम and वापसs the next key in the
 * tree based on the current path and the min_trans parameters.
 *
 * 0 is वापसed अगर another key is found, < 0 अगर there are any errors
 * and 1 is वापसed अगर there are no higher keys in the tree
 *
 * path->keep_locks should be set to 1 on the search made beक्रमe
 * calling this function.
 */
पूर्णांक btrfs_find_next_key(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			काष्ठा btrfs_key *key, पूर्णांक level, u64 min_trans)
अणु
	पूर्णांक slot;
	काष्ठा extent_buffer *c;

	WARN_ON(!path->keep_locks && !path->skip_locking);
	जबतक (level < BTRFS_MAX_LEVEL) अणु
		अगर (!path->nodes[level])
			वापस 1;

		slot = path->slots[level] + 1;
		c = path->nodes[level];
next:
		अगर (slot >= btrfs_header_nritems(c)) अणु
			पूर्णांक ret;
			पूर्णांक orig_lowest;
			काष्ठा btrfs_key cur_key;
			अगर (level + 1 >= BTRFS_MAX_LEVEL ||
			    !path->nodes[level + 1])
				वापस 1;

			अगर (path->locks[level + 1] || path->skip_locking) अणु
				level++;
				जारी;
			पूर्ण

			slot = btrfs_header_nritems(c) - 1;
			अगर (level == 0)
				btrfs_item_key_to_cpu(c, &cur_key, slot);
			अन्यथा
				btrfs_node_key_to_cpu(c, &cur_key, slot);

			orig_lowest = path->lowest_level;
			btrfs_release_path(path);
			path->lowest_level = level;
			ret = btrfs_search_slot(शून्य, root, &cur_key, path,
						0, 0);
			path->lowest_level = orig_lowest;
			अगर (ret < 0)
				वापस ret;

			c = path->nodes[level];
			slot = path->slots[level];
			अगर (ret == 0)
				slot++;
			जाओ next;
		पूर्ण

		अगर (level == 0)
			btrfs_item_key_to_cpu(c, key, slot);
		अन्यथा अणु
			u64 gen = btrfs_node_ptr_generation(c, slot);

			अगर (gen < min_trans) अणु
				slot++;
				जाओ next;
			पूर्ण
			btrfs_node_key_to_cpu(c, key, slot);
		पूर्ण
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * search the tree again to find a leaf with greater keys
 * वापसs 0 अगर it found something or 1 अगर there are no greater leaves.
 * वापसs < 0 on io errors.
 */
पूर्णांक btrfs_next_leaf(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path)
अणु
	वापस btrfs_next_old_leaf(root, path, 0);
पूर्ण

पूर्णांक btrfs_next_old_leaf(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			u64 समय_seq)
अणु
	पूर्णांक slot;
	पूर्णांक level;
	काष्ठा extent_buffer *c;
	काष्ठा extent_buffer *next;
	काष्ठा btrfs_key key;
	u32 nritems;
	पूर्णांक ret;
	पूर्णांक i;

	nritems = btrfs_header_nritems(path->nodes[0]);
	अगर (nritems == 0)
		वापस 1;

	btrfs_item_key_to_cpu(path->nodes[0], &key, nritems - 1);
again:
	level = 1;
	next = शून्य;
	btrfs_release_path(path);

	path->keep_locks = 1;

	अगर (समय_seq)
		ret = btrfs_search_old_slot(root, &key, path, समय_seq);
	अन्यथा
		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	path->keep_locks = 0;

	अगर (ret < 0)
		वापस ret;

	nritems = btrfs_header_nritems(path->nodes[0]);
	/*
	 * by releasing the path above we dropped all our locks.  A balance
	 * could have added more items next to the key that used to be
	 * at the very end of the block.  So, check again here and
	 * advance the path अगर there are now more items available.
	 */
	अगर (nritems > 0 && path->slots[0] < nritems - 1) अणु
		अगर (ret == 0)
			path->slots[0]++;
		ret = 0;
		जाओ करोne;
	पूर्ण
	/*
	 * So the above check misses one हाल:
	 * - after releasing the path above, someone has हटाओd the item that
	 *   used to be at the very end of the block, and balance between leafs
	 *   माला_लो another one with bigger key.offset to replace it.
	 *
	 * This one should be वापसed as well, or we can get leaf corruption
	 * later(esp. in __btrfs_drop_extents()).
	 *
	 * And a bit more explanation about this check,
	 * with ret > 0, the key isn't found, the path poपूर्णांकs to the slot
	 * where it should be inserted, so the path->slots[0] item must be the
	 * bigger one.
	 */
	अगर (nritems > 0 && ret > 0 && path->slots[0] == nritems - 1) अणु
		ret = 0;
		जाओ करोne;
	पूर्ण

	जबतक (level < BTRFS_MAX_LEVEL) अणु
		अगर (!path->nodes[level]) अणु
			ret = 1;
			जाओ करोne;
		पूर्ण

		slot = path->slots[level] + 1;
		c = path->nodes[level];
		अगर (slot >= btrfs_header_nritems(c)) अणु
			level++;
			अगर (level == BTRFS_MAX_LEVEL) अणु
				ret = 1;
				जाओ करोne;
			पूर्ण
			जारी;
		पूर्ण


		/*
		 * Our current level is where we're going to start from, and to
		 * make sure lockdep करोesn't complain we need to drop our locks
		 * and nodes from 0 to our current level.
		 */
		क्रम (i = 0; i < level; i++) अणु
			अगर (path->locks[level]) अणु
				btrfs_tree_पढ़ो_unlock(path->nodes[i]);
				path->locks[i] = 0;
			पूर्ण
			मुक्त_extent_buffer(path->nodes[i]);
			path->nodes[i] = शून्य;
		पूर्ण

		next = c;
		ret = पढ़ो_block_क्रम_search(root, path, &next, level,
					    slot, &key);
		अगर (ret == -EAGAIN)
			जाओ again;

		अगर (ret < 0) अणु
			btrfs_release_path(path);
			जाओ करोne;
		पूर्ण

		अगर (!path->skip_locking) अणु
			ret = btrfs_try_tree_पढ़ो_lock(next);
			अगर (!ret && समय_seq) अणु
				/*
				 * If we करोn't get the lock, we may be racing
				 * with push_leaf_left, holding that lock जबतक
				 * itself रुकोing क्रम the leaf we've currently
				 * locked. To solve this situation, we give up
				 * on our lock and cycle.
				 */
				मुक्त_extent_buffer(next);
				btrfs_release_path(path);
				cond_resched();
				जाओ again;
			पूर्ण
			अगर (!ret)
				btrfs_tree_पढ़ो_lock(next);
		पूर्ण
		अवरोध;
	पूर्ण
	path->slots[level] = slot;
	जबतक (1) अणु
		level--;
		path->nodes[level] = next;
		path->slots[level] = 0;
		अगर (!path->skip_locking)
			path->locks[level] = BTRFS_READ_LOCK;
		अगर (!level)
			अवरोध;

		ret = पढ़ो_block_क्रम_search(root, path, &next, level,
					    0, &key);
		अगर (ret == -EAGAIN)
			जाओ again;

		अगर (ret < 0) अणु
			btrfs_release_path(path);
			जाओ करोne;
		पूर्ण

		अगर (!path->skip_locking)
			btrfs_tree_पढ़ो_lock(next);
	पूर्ण
	ret = 0;
करोne:
	unlock_up(path, 0, 1, 0, शून्य);

	वापस ret;
पूर्ण

/*
 * this uses btrfs_prev_leaf to walk backwards in the tree, and keeps
 * searching until it माला_लो past min_objectid or finds an item of 'type'
 *
 * वापसs 0 अगर something is found, 1 अगर nothing was found and < 0 on error
 */
पूर्णांक btrfs_previous_item(काष्ठा btrfs_root *root,
			काष्ठा btrfs_path *path, u64 min_objectid,
			पूर्णांक type)
अणु
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *leaf;
	u32 nritems;
	पूर्णांक ret;

	जबतक (1) अणु
		अगर (path->slots[0] == 0) अणु
			ret = btrfs_prev_leaf(root, path);
			अगर (ret != 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			path->slots[0]--;
		पूर्ण
		leaf = path->nodes[0];
		nritems = btrfs_header_nritems(leaf);
		अगर (nritems == 0)
			वापस 1;
		अगर (path->slots[0] == nritems)
			path->slots[0]--;

		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
		अगर (found_key.objectid < min_objectid)
			अवरोध;
		अगर (found_key.type == type)
			वापस 0;
		अगर (found_key.objectid == min_objectid &&
		    found_key.type < type)
			अवरोध;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * search in extent tree to find a previous Metadata/Data extent item with
 * min objecitd.
 *
 * वापसs 0 अगर something is found, 1 अगर nothing was found and < 0 on error
 */
पूर्णांक btrfs_previous_extent_item(काष्ठा btrfs_root *root,
			काष्ठा btrfs_path *path, u64 min_objectid)
अणु
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *leaf;
	u32 nritems;
	पूर्णांक ret;

	जबतक (1) अणु
		अगर (path->slots[0] == 0) अणु
			ret = btrfs_prev_leaf(root, path);
			अगर (ret != 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			path->slots[0]--;
		पूर्ण
		leaf = path->nodes[0];
		nritems = btrfs_header_nritems(leaf);
		अगर (nritems == 0)
			वापस 1;
		अगर (path->slots[0] == nritems)
			path->slots[0]--;

		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
		अगर (found_key.objectid < min_objectid)
			अवरोध;
		अगर (found_key.type == BTRFS_EXTENT_ITEM_KEY ||
		    found_key.type == BTRFS_METADATA_ITEM_KEY)
			वापस 0;
		अगर (found_key.objectid == min_objectid &&
		    found_key.type < BTRFS_EXTENT_ITEM_KEY)
			अवरोध;
	पूर्ण
	वापस 1;
पूर्ण
