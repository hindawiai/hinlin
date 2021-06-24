<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Facebook.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश "btrfs-tests.h"
#समावेश "../ctree.h"
#समावेश "../transaction.h"
#समावेश "../disk-io.h"
#समावेश "../qgroup.h"
#समावेश "../backref.h"

अटल पूर्णांक insert_normal_tree_ref(काष्ठा btrfs_root *root, u64 bytenr,
				  u64 num_bytes, u64 parent, u64 root_objectid)
अणु
	काष्ठा btrfs_trans_handle trans;
	काष्ठा btrfs_extent_item *item;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	काष्ठा btrfs_tree_block_info *block_info;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key ins;
	u32 size = माप(*item) + माप(*iref) + माप(*block_info);
	पूर्णांक ret;

	btrfs_init_dummy_trans(&trans, शून्य);

	ins.objectid = bytenr;
	ins.type = BTRFS_EXTENT_ITEM_KEY;
	ins.offset = num_bytes;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		test_std_err(TEST_ALLOC_ROOT);
		वापस -ENOMEM;
	पूर्ण

	ret = btrfs_insert_empty_item(&trans, root, path, &ins, size);
	अगर (ret) अणु
		test_err("couldn't insert ref %d", ret);
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण

	leaf = path->nodes[0];
	item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_extent_item);
	btrfs_set_extent_refs(leaf, item, 1);
	btrfs_set_extent_generation(leaf, item, 1);
	btrfs_set_extent_flags(leaf, item, BTRFS_EXTENT_FLAG_TREE_BLOCK);
	block_info = (काष्ठा btrfs_tree_block_info *)(item + 1);
	btrfs_set_tree_block_level(leaf, block_info, 0);
	iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(block_info + 1);
	अगर (parent > 0) अणु
		btrfs_set_extent_अंतरभूत_ref_type(leaf, iref,
						 BTRFS_SHARED_BLOCK_REF_KEY);
		btrfs_set_extent_अंतरभूत_ref_offset(leaf, iref, parent);
	पूर्ण अन्यथा अणु
		btrfs_set_extent_अंतरभूत_ref_type(leaf, iref, BTRFS_TREE_BLOCK_REF_KEY);
		btrfs_set_extent_अंतरभूत_ref_offset(leaf, iref, root_objectid);
	पूर्ण
	btrfs_मुक्त_path(path);
	वापस 0;
पूर्ण

अटल पूर्णांक add_tree_ref(काष्ठा btrfs_root *root, u64 bytenr, u64 num_bytes,
			u64 parent, u64 root_objectid)
अणु
	काष्ठा btrfs_trans_handle trans;
	काष्ठा btrfs_extent_item *item;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	u64 refs;
	पूर्णांक ret;

	btrfs_init_dummy_trans(&trans, शून्य);

	key.objectid = bytenr;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		test_std_err(TEST_ALLOC_ROOT);
		वापस -ENOMEM;
	पूर्ण

	ret = btrfs_search_slot(&trans, root, &key, path, 0, 1);
	अगर (ret) अणु
		test_err("couldn't find extent ref");
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण

	item = btrfs_item_ptr(path->nodes[0], path->slots[0],
			      काष्ठा btrfs_extent_item);
	refs = btrfs_extent_refs(path->nodes[0], item);
	btrfs_set_extent_refs(path->nodes[0], item, refs + 1);
	btrfs_release_path(path);

	key.objectid = bytenr;
	अगर (parent) अणु
		key.type = BTRFS_SHARED_BLOCK_REF_KEY;
		key.offset = parent;
	पूर्ण अन्यथा अणु
		key.type = BTRFS_TREE_BLOCK_REF_KEY;
		key.offset = root_objectid;
	पूर्ण

	ret = btrfs_insert_empty_item(&trans, root, path, &key, 0);
	अगर (ret)
		test_err("failed to insert backref");
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक हटाओ_extent_item(काष्ठा btrfs_root *root, u64 bytenr,
			      u64 num_bytes)
अणु
	काष्ठा btrfs_trans_handle trans;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	पूर्णांक ret;

	btrfs_init_dummy_trans(&trans, शून्य);

	key.objectid = bytenr;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		test_std_err(TEST_ALLOC_ROOT);
		वापस -ENOMEM;
	पूर्ण

	ret = btrfs_search_slot(&trans, root, &key, path, -1, 1);
	अगर (ret) अणु
		test_err("didn't find our key %d", ret);
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण
	btrfs_del_item(&trans, root, path);
	btrfs_मुक्त_path(path);
	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_extent_ref(काष्ठा btrfs_root *root, u64 bytenr,
			     u64 num_bytes, u64 parent, u64 root_objectid)
अणु
	काष्ठा btrfs_trans_handle trans;
	काष्ठा btrfs_extent_item *item;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	u64 refs;
	पूर्णांक ret;

	btrfs_init_dummy_trans(&trans, शून्य);

	key.objectid = bytenr;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		test_std_err(TEST_ALLOC_ROOT);
		वापस -ENOMEM;
	पूर्ण

	ret = btrfs_search_slot(&trans, root, &key, path, 0, 1);
	अगर (ret) अणु
		test_err("couldn't find extent ref");
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण

	item = btrfs_item_ptr(path->nodes[0], path->slots[0],
			      काष्ठा btrfs_extent_item);
	refs = btrfs_extent_refs(path->nodes[0], item);
	btrfs_set_extent_refs(path->nodes[0], item, refs - 1);
	btrfs_release_path(path);

	key.objectid = bytenr;
	अगर (parent) अणु
		key.type = BTRFS_SHARED_BLOCK_REF_KEY;
		key.offset = parent;
	पूर्ण अन्यथा अणु
		key.type = BTRFS_TREE_BLOCK_REF_KEY;
		key.offset = root_objectid;
	पूर्ण

	ret = btrfs_search_slot(&trans, root, &key, path, -1, 1);
	अगर (ret) अणु
		test_err("couldn't find backref %d", ret);
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण
	btrfs_del_item(&trans, root, path);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक test_no_shared_qgroup(काष्ठा btrfs_root *root,
		u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_trans_handle trans;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा ulist *old_roots = शून्य;
	काष्ठा ulist *new_roots = शून्य;
	पूर्णांक ret;

	btrfs_init_dummy_trans(&trans, fs_info);

	test_msg("running qgroup add/remove tests");
	ret = btrfs_create_qgroup(&trans, BTRFS_FS_TREE_OBJECTID);
	अगर (ret) अणु
		test_err("couldn't create a qgroup %d", ret);
		वापस ret;
	पूर्ण

	/*
	 * Since the test trans करोesn't have the complicated delayed refs,
	 * we can only call btrfs_qgroup_account_extent() directly to test
	 * quota.
	 */
	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &old_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = insert_normal_tree_ref(root, nodesize, nodesize, 0,
				BTRFS_FS_TREE_OBJECTID);
	अगर (ret)
		वापस ret;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &new_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		ulist_मुक्त(new_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_qgroup_account_extent(&trans, nodesize, nodesize, old_roots,
					  new_roots);
	अगर (ret) अणु
		test_err("couldn't account space for a qgroup %d", ret);
		वापस ret;
	पूर्ण

	अगर (btrfs_verअगरy_qgroup_counts(fs_info, BTRFS_FS_TREE_OBJECTID,
				nodesize, nodesize)) अणु
		test_err("qgroup counts didn't match expected values");
		वापस -EINVAL;
	पूर्ण
	old_roots = शून्य;
	new_roots = शून्य;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &old_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = हटाओ_extent_item(root, nodesize, nodesize);
	अगर (ret)
		वापस -EINVAL;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &new_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		ulist_मुक्त(new_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_qgroup_account_extent(&trans, nodesize, nodesize, old_roots,
					  new_roots);
	अगर (ret) अणु
		test_err("couldn't account space for a qgroup %d", ret);
		वापस -EINVAL;
	पूर्ण

	अगर (btrfs_verअगरy_qgroup_counts(fs_info, BTRFS_FS_TREE_OBJECTID, 0, 0)) अणु
		test_err("qgroup counts didn't match expected values");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Add a ref क्रम two dअगरferent roots to make sure the shared value comes out
 * right, also हटाओ one of the roots and make sure the exclusive count is
 * adjusted properly.
 */
अटल पूर्णांक test_multiple_refs(काष्ठा btrfs_root *root,
		u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_trans_handle trans;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा ulist *old_roots = शून्य;
	काष्ठा ulist *new_roots = शून्य;
	पूर्णांक ret;

	btrfs_init_dummy_trans(&trans, fs_info);

	test_msg("running qgroup multiple refs test");

	/*
	 * We have BTRFS_FS_TREE_OBJECTID created alपढ़ोy from the
	 * previous test.
	 */
	ret = btrfs_create_qgroup(&trans, BTRFS_FIRST_FREE_OBJECTID);
	अगर (ret) अणु
		test_err("couldn't create a qgroup %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &old_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = insert_normal_tree_ref(root, nodesize, nodesize, 0,
				BTRFS_FS_TREE_OBJECTID);
	अगर (ret)
		वापस ret;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &new_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		ulist_मुक्त(new_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_qgroup_account_extent(&trans, nodesize, nodesize, old_roots,
					  new_roots);
	अगर (ret) अणु
		test_err("couldn't account space for a qgroup %d", ret);
		वापस ret;
	पूर्ण

	अगर (btrfs_verअगरy_qgroup_counts(fs_info, BTRFS_FS_TREE_OBJECTID,
				       nodesize, nodesize)) अणु
		test_err("qgroup counts didn't match expected values");
		वापस -EINVAL;
	पूर्ण

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &old_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = add_tree_ref(root, nodesize, nodesize, 0,
			BTRFS_FIRST_FREE_OBJECTID);
	अगर (ret)
		वापस ret;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &new_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		ulist_मुक्त(new_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_qgroup_account_extent(&trans, nodesize, nodesize, old_roots,
					  new_roots);
	अगर (ret) अणु
		test_err("couldn't account space for a qgroup %d", ret);
		वापस ret;
	पूर्ण

	अगर (btrfs_verअगरy_qgroup_counts(fs_info, BTRFS_FS_TREE_OBJECTID,
					nodesize, 0)) अणु
		test_err("qgroup counts didn't match expected values");
		वापस -EINVAL;
	पूर्ण

	अगर (btrfs_verअगरy_qgroup_counts(fs_info, BTRFS_FIRST_FREE_OBJECTID,
					nodesize, 0)) अणु
		test_err("qgroup counts didn't match expected values");
		वापस -EINVAL;
	पूर्ण

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &old_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = हटाओ_extent_ref(root, nodesize, nodesize, 0,
				BTRFS_FIRST_FREE_OBJECTID);
	अगर (ret)
		वापस ret;

	ret = btrfs_find_all_roots(&trans, fs_info, nodesize, 0, &new_roots,
			false);
	अगर (ret) अणु
		ulist_मुक्त(old_roots);
		ulist_मुक्त(new_roots);
		test_err("couldn't find old roots: %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_qgroup_account_extent(&trans, nodesize, nodesize, old_roots,
					  new_roots);
	अगर (ret) अणु
		test_err("couldn't account space for a qgroup %d", ret);
		वापस ret;
	पूर्ण

	अगर (btrfs_verअगरy_qgroup_counts(fs_info, BTRFS_FIRST_FREE_OBJECTID,
					0, 0)) अणु
		test_err("qgroup counts didn't match expected values");
		वापस -EINVAL;
	पूर्ण

	अगर (btrfs_verअगरy_qgroup_counts(fs_info, BTRFS_FS_TREE_OBJECTID,
					nodesize, nodesize)) अणु
		test_err("qgroup counts didn't match expected values");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btrfs_test_qgroups(u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_fs_info *fs_info = शून्य;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_root *पंचांगp_root;
	पूर्णांक ret = 0;

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	अगर (!fs_info) अणु
		test_std_err(TEST_ALLOC_FS_INFO);
		वापस -ENOMEM;
	पूर्ण

	root = btrfs_alloc_dummy_root(fs_info);
	अगर (IS_ERR(root)) अणु
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(root);
		जाओ out;
	पूर्ण

	/* We are using this root as our extent root */
	root->fs_info->extent_root = root;

	/*
	 * Some of the paths we test assume we have a filled out fs_info, so we
	 * just need to add the root in there so we करोn't panic.
	 */
	root->fs_info->tree_root = root;
	root->fs_info->quota_root = root;
	set_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags);

	/*
	 * Can't use bytenr 0, some things freak out
	 * *cough*backref walking code*cough*
	 */
	root->node = alloc_test_extent_buffer(root->fs_info, nodesize);
	अगर (IS_ERR(root->node)) अणु
		test_err("couldn't allocate dummy buffer");
		ret = PTR_ERR(root->node);
		जाओ out;
	पूर्ण
	btrfs_set_header_level(root->node, 0);
	btrfs_set_header_nritems(root->node, 0);
	root->alloc_bytenr += 2 * nodesize;

	पंचांगp_root = btrfs_alloc_dummy_root(fs_info);
	अगर (IS_ERR(पंचांगp_root)) अणु
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(पंचांगp_root);
		जाओ out;
	पूर्ण

	पंचांगp_root->root_key.objectid = BTRFS_FS_TREE_OBJECTID;
	root->fs_info->fs_root = पंचांगp_root;
	ret = btrfs_insert_fs_root(root->fs_info, पंचांगp_root);
	अगर (ret) अणु
		test_err("couldn't insert fs root %d", ret);
		जाओ out;
	पूर्ण
	btrfs_put_root(पंचांगp_root);

	पंचांगp_root = btrfs_alloc_dummy_root(fs_info);
	अगर (IS_ERR(पंचांगp_root)) अणु
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(पंचांगp_root);
		जाओ out;
	पूर्ण

	पंचांगp_root->root_key.objectid = BTRFS_FIRST_FREE_OBJECTID;
	ret = btrfs_insert_fs_root(root->fs_info, पंचांगp_root);
	अगर (ret) अणु
		test_err("couldn't insert fs root %d", ret);
		जाओ out;
	पूर्ण
	btrfs_put_root(पंचांगp_root);

	test_msg("running qgroup tests");
	ret = test_no_shared_qgroup(root, sectorsize, nodesize);
	अगर (ret)
		जाओ out;
	ret = test_multiple_refs(root, sectorsize, nodesize);
out:
	btrfs_मुक्त_dummy_root(root);
	btrfs_मुक्त_dummy_fs_info(fs_info);
	वापस ret;
पूर्ण
