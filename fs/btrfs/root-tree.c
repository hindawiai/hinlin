<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/uuid.h>
#समावेश "ctree.h"
#समावेश "transaction.h"
#समावेश "disk-io.h"
#समावेश "print-tree.h"
#समावेश "qgroup.h"
#समावेश "space-info.h"

/*
 * Read a root item from the tree. In हाल we detect a root item smaller then
 * माप(root_item), we know it's an old version of the root काष्ठाure and
 * initialize all new fields to zero. The same happens अगर we detect mismatching
 * generation numbers as then we know the root was once mounted with an older
 * kernel that was not aware of the root item काष्ठाure change.
 */
अटल व्योम btrfs_पढ़ो_root_item(काष्ठा extent_buffer *eb, पूर्णांक slot,
				काष्ठा btrfs_root_item *item)
अणु
	u32 len;
	पूर्णांक need_reset = 0;

	len = btrfs_item_size_nr(eb, slot);
	पढ़ो_extent_buffer(eb, item, btrfs_item_ptr_offset(eb, slot),
			   min_t(u32, len, माप(*item)));
	अगर (len < माप(*item))
		need_reset = 1;
	अगर (!need_reset && btrfs_root_generation(item)
		!= btrfs_root_generation_v2(item)) अणु
		अगर (btrfs_root_generation_v2(item) != 0) अणु
			btrfs_warn(eb->fs_info,
					"mismatching generation and generation_v2 found in root item. This root was probably mounted with an older kernel. Resetting all new fields.");
		पूर्ण
		need_reset = 1;
	पूर्ण
	अगर (need_reset) अणु
		स_रखो(&item->generation_v2, 0,
			माप(*item) - दुरत्व(काष्ठा btrfs_root_item,
					generation_v2));

		generate_अक्रमom_guid(item->uuid);
	पूर्ण
पूर्ण

/*
 * btrfs_find_root - lookup the root by the key.
 * root: the root of the root tree
 * search_key: the key to search
 * path: the path we search
 * root_item: the root item of the tree we look क्रम
 * root_key: the root key of the tree we look क्रम
 *
 * If ->offset of 'search_key' is -1ULL, it means we are not sure the offset
 * of the search key, just lookup the root with the highest offset क्रम a
 * given objectid.
 *
 * If we find something वापस 0, otherwise > 0, < 0 on error.
 */
पूर्णांक btrfs_find_root(काष्ठा btrfs_root *root, स्थिर काष्ठा btrfs_key *search_key,
		    काष्ठा btrfs_path *path, काष्ठा btrfs_root_item *root_item,
		    काष्ठा btrfs_key *root_key)
अणु
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *l;
	पूर्णांक ret;
	पूर्णांक slot;

	ret = btrfs_search_slot(शून्य, root, search_key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (search_key->offset != -1ULL) अणु	/* the search key is exact */
		अगर (ret > 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		BUG_ON(ret == 0);		/* Logical error */
		अगर (path->slots[0] == 0)
			जाओ out;
		path->slots[0]--;
		ret = 0;
	पूर्ण

	l = path->nodes[0];
	slot = path->slots[0];

	btrfs_item_key_to_cpu(l, &found_key, slot);
	अगर (found_key.objectid != search_key->objectid ||
	    found_key.type != BTRFS_ROOT_ITEM_KEY) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	अगर (root_item)
		btrfs_पढ़ो_root_item(l, slot, root_item);
	अगर (root_key)
		स_नकल(root_key, &found_key, माप(found_key));
out:
	btrfs_release_path(path);
	वापस ret;
पूर्ण

व्योम btrfs_set_root_node(काष्ठा btrfs_root_item *item,
			 काष्ठा extent_buffer *node)
अणु
	btrfs_set_root_bytenr(item, node->start);
	btrfs_set_root_level(item, btrfs_header_level(node));
	btrfs_set_root_generation(item, btrfs_header_generation(node));
पूर्ण

/*
 * copy the data in 'item' पूर्णांकo the btree
 */
पूर्णांक btrfs_update_root(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root
		      *root, काष्ठा btrfs_key *key, काष्ठा btrfs_root_item
		      *item)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *l;
	पूर्णांक ret;
	पूर्णांक slot;
	अचिन्हित दीर्घ ptr;
	u32 old_len;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(trans, root, key, path, 0, 1);
	अगर (ret < 0)
		जाओ out;

	अगर (ret > 0) अणु
		btrfs_crit(fs_info,
			"unable to find root key (%llu %u %llu) in tree %llu",
			key->objectid, key->type, key->offset,
			root->root_key.objectid);
		ret = -EUCLEAN;
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	l = path->nodes[0];
	slot = path->slots[0];
	ptr = btrfs_item_ptr_offset(l, slot);
	old_len = btrfs_item_size_nr(l, slot);

	/*
	 * If this is the first समय we update the root item which originated
	 * from an older kernel, we need to enlarge the item size to make room
	 * क्रम the added fields.
	 */
	अगर (old_len < माप(*item)) अणु
		btrfs_release_path(path);
		ret = btrfs_search_slot(trans, root, key, path,
				-1, 1);
		अगर (ret < 0) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण

		ret = btrfs_del_item(trans, root, path);
		अगर (ret < 0) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
		btrfs_release_path(path);
		ret = btrfs_insert_empty_item(trans, root, path,
				key, माप(*item));
		अगर (ret < 0) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
		l = path->nodes[0];
		slot = path->slots[0];
		ptr = btrfs_item_ptr_offset(l, slot);
	पूर्ण

	/*
	 * Update generation_v2 so at the next mount we know the new root
	 * fields are valid.
	 */
	btrfs_set_root_generation_v2(item, btrfs_root_generation(item));

	ग_लिखो_extent_buffer(l, item, ptr, माप(*item));
	btrfs_mark_buffer_dirty(path->nodes[0]);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_insert_root(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		      स्थिर काष्ठा btrfs_key *key, काष्ठा btrfs_root_item *item)
अणु
	/*
	 * Make sure generation v1 and v2 match. See update_root क्रम details.
	 */
	btrfs_set_root_generation_v2(item, btrfs_root_generation(item));
	वापस btrfs_insert_item(trans, root, key, item, माप(*item));
पूर्ण

पूर्णांक btrfs_find_orphan_roots(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root *root;
	पूर्णांक err = 0;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = BTRFS_ORPHAN_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = 0;

	जबतक (1) अणु
		u64 root_objectid;

		ret = btrfs_search_slot(शून्य, tree_root, &key, path, 0, 0);
		अगर (ret < 0) अणु
			err = ret;
			अवरोध;
		पूर्ण

		leaf = path->nodes[0];
		अगर (path->slots[0] >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(tree_root, path);
			अगर (ret < 0)
				err = ret;
			अगर (ret != 0)
				अवरोध;
			leaf = path->nodes[0];
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		btrfs_release_path(path);

		अगर (key.objectid != BTRFS_ORPHAN_OBJECTID ||
		    key.type != BTRFS_ORPHAN_ITEM_KEY)
			अवरोध;

		root_objectid = key.offset;
		key.offset++;

		root = btrfs_get_fs_root(fs_info, root_objectid, false);
		err = PTR_ERR_OR_ZERO(root);
		अगर (err && err != -ENOENT) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (err == -ENOENT) अणु
			काष्ठा btrfs_trans_handle *trans;

			btrfs_release_path(path);

			trans = btrfs_join_transaction(tree_root);
			अगर (IS_ERR(trans)) अणु
				err = PTR_ERR(trans);
				btrfs_handle_fs_error(fs_info, err,
					    "Failed to start trans to delete orphan item");
				अवरोध;
			पूर्ण
			err = btrfs_del_orphan_item(trans, tree_root,
						    root_objectid);
			btrfs_end_transaction(trans);
			अगर (err) अणु
				btrfs_handle_fs_error(fs_info, err,
					    "Failed to delete root orphan item");
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		WARN_ON(!test_bit(BTRFS_ROOT_ORPHAN_ITEM_INSERTED, &root->state));
		अगर (btrfs_root_refs(&root->root_item) == 0) अणु
			set_bit(BTRFS_ROOT_DEAD_TREE, &root->state);
			btrfs_add_dead_root(root);
		पूर्ण
		btrfs_put_root(root);
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस err;
पूर्ण

/* drop the root item क्रम 'key' from the tree root */
पूर्णांक btrfs_del_root(काष्ठा btrfs_trans_handle *trans,
		   स्थिर काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_root *root = trans->fs_info->tree_root;
	काष्ठा btrfs_path *path;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	ret = btrfs_search_slot(trans, root, key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;

	BUG_ON(ret != 0);

	ret = btrfs_del_item(trans, root, path);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_del_root_ref(काष्ठा btrfs_trans_handle *trans, u64 root_id,
		       u64 ref_id, u64 dirid, u64 *sequence, स्थिर अक्षर *name,
		       पूर्णांक name_len)

अणु
	काष्ठा btrfs_root *tree_root = trans->fs_info->tree_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root_ref *ref;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	अचिन्हित दीर्घ ptr;
	पूर्णांक err = 0;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = root_id;
	key.type = BTRFS_ROOT_BACKREF_KEY;
	key.offset = ref_id;
again:
	ret = btrfs_search_slot(trans, tree_root, &key, path, -1, 1);
	BUG_ON(ret < 0);
	अगर (ret == 0) अणु
		leaf = path->nodes[0];
		ref = btrfs_item_ptr(leaf, path->slots[0],
				     काष्ठा btrfs_root_ref);
		ptr = (अचिन्हित दीर्घ)(ref + 1);
		अगर ((btrfs_root_ref_dirid(leaf, ref) != dirid) ||
		    (btrfs_root_ref_name_len(leaf, ref) != name_len) ||
		    स_भेद_extent_buffer(leaf, name, ptr, name_len)) अणु
			err = -ENOENT;
			जाओ out;
		पूर्ण
		*sequence = btrfs_root_ref_sequence(leaf, ref);

		ret = btrfs_del_item(trans, tree_root, path);
		अगर (ret) अणु
			err = ret;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		err = -ENOENT;

	अगर (key.type == BTRFS_ROOT_BACKREF_KEY) अणु
		btrfs_release_path(path);
		key.objectid = ref_id;
		key.type = BTRFS_ROOT_REF_KEY;
		key.offset = root_id;
		जाओ again;
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस err;
पूर्ण

/*
 * add a btrfs_root_ref item.  type is either BTRFS_ROOT_REF_KEY
 * or BTRFS_ROOT_BACKREF_KEY.
 *
 * The dirid, sequence, name and name_len refer to the directory entry
 * that is referencing the root.
 *
 * For a क्रमward ref, the root_id is the id of the tree referencing
 * the root and ref_id is the id of the subvol  or snapshot.
 *
 * For a back ref the root_id is the id of the subvol or snapshot and
 * ref_id is the id of the tree referencing it.
 *
 * Will वापस 0, -ENOMEM, or anything from the CoW path
 */
पूर्णांक btrfs_add_root_ref(काष्ठा btrfs_trans_handle *trans, u64 root_id,
		       u64 ref_id, u64 dirid, u64 sequence, स्थिर अक्षर *name,
		       पूर्णांक name_len)
अणु
	काष्ठा btrfs_root *tree_root = trans->fs_info->tree_root;
	काष्ठा btrfs_key key;
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root_ref *ref;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ ptr;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = root_id;
	key.type = BTRFS_ROOT_BACKREF_KEY;
	key.offset = ref_id;
again:
	ret = btrfs_insert_empty_item(trans, tree_root, path, &key,
				      माप(*ref) + name_len);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण

	leaf = path->nodes[0];
	ref = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_root_ref);
	btrfs_set_root_ref_dirid(leaf, ref, dirid);
	btrfs_set_root_ref_sequence(leaf, ref, sequence);
	btrfs_set_root_ref_name_len(leaf, ref, name_len);
	ptr = (अचिन्हित दीर्घ)(ref + 1);
	ग_लिखो_extent_buffer(leaf, name, ptr, name_len);
	btrfs_mark_buffer_dirty(leaf);

	अगर (key.type == BTRFS_ROOT_BACKREF_KEY) अणु
		btrfs_release_path(path);
		key.objectid = ref_id;
		key.type = BTRFS_ROOT_REF_KEY;
		key.offset = root_id;
		जाओ again;
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस 0;
पूर्ण

/*
 * Old btrfs क्रममाला_लो to init root_item->flags and root_item->byte_limit
 * क्रम subvolumes. To work around this problem, we steal a bit from
 * root_item->inode_item->flags, and use it to indicate अगर those fields
 * have been properly initialized.
 */
व्योम btrfs_check_and_init_root_item(काष्ठा btrfs_root_item *root_item)
अणु
	u64 inode_flags = btrfs_stack_inode_flags(&root_item->inode);

	अगर (!(inode_flags & BTRFS_INODE_ROOT_ITEM_INIT)) अणु
		inode_flags |= BTRFS_INODE_ROOT_ITEM_INIT;
		btrfs_set_stack_inode_flags(&root_item->inode, inode_flags);
		btrfs_set_root_flags(root_item, 0);
		btrfs_set_root_limit(root_item, 0);
	पूर्ण
पूर्ण

व्योम btrfs_update_root_बार(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_root_item *item = &root->root_item;
	काष्ठा बारpec64 ct;

	kसमय_get_real_ts64(&ct);
	spin_lock(&root->root_item_lock);
	btrfs_set_root_ctransid(item, trans->transid);
	btrfs_set_stack_बारpec_sec(&item->स_समय, ct.tv_sec);
	btrfs_set_stack_बारpec_nsec(&item->स_समय, ct.tv_nsec);
	spin_unlock(&root->root_item_lock);
पूर्ण

/*
 * btrfs_subvolume_reserve_metadata() - reserve space क्रम subvolume operation
 * root: the root of the parent directory
 * rsv: block reservation
 * items: the number of items that we need करो reservation
 * use_global_rsv: allow fallback to the global block reservation
 *
 * This function is used to reserve the space क्रम snapshot/subvolume
 * creation and deletion. Those operations are dअगरferent with the
 * common file/directory operations, they change two fs/file trees
 * and root tree, the number of items that the qgroup reserves is
 * dअगरferent with the मुक्त space reservation. So we can not use
 * the space reservation mechanism in start_transaction().
 */
पूर्णांक btrfs_subvolume_reserve_metadata(काष्ठा btrfs_root *root,
				     काष्ठा btrfs_block_rsv *rsv, पूर्णांक items,
				     bool use_global_rsv)
अणु
	u64 qgroup_num_bytes = 0;
	u64 num_bytes;
	पूर्णांक ret;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;

	अगर (test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags)) अणु
		/* One क्रम parent inode, two क्रम dir entries */
		qgroup_num_bytes = 3 * fs_info->nodesize;
		ret = btrfs_qgroup_reserve_meta_pपुनः_स्मृति(root,
				qgroup_num_bytes, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	num_bytes = btrfs_calc_insert_metadata_size(fs_info, items);
	rsv->space_info = btrfs_find_space_info(fs_info,
					    BTRFS_BLOCK_GROUP_METADATA);
	ret = btrfs_block_rsv_add(root, rsv, num_bytes,
				  BTRFS_RESERVE_FLUSH_ALL);

	अगर (ret == -ENOSPC && use_global_rsv)
		ret = btrfs_block_rsv_migrate(global_rsv, rsv, num_bytes, true);

	अगर (ret && qgroup_num_bytes)
		btrfs_qgroup_मुक्त_meta_pपुनः_स्मृति(root, qgroup_num_bytes);

	अगर (!ret) अणु
		spin_lock(&rsv->lock);
		rsv->qgroup_rsv_reserved += qgroup_num_bytes;
		spin_unlock(&rsv->lock);
	पूर्ण
	वापस ret;
पूर्ण

व्योम btrfs_subvolume_release_metadata(काष्ठा btrfs_root *root,
				      काष्ठा btrfs_block_rsv *rsv)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 qgroup_to_release;

	btrfs_block_rsv_release(fs_info, rsv, (u64)-1, &qgroup_to_release);
	btrfs_qgroup_convert_reserved_meta(root, qgroup_to_release);
पूर्ण
