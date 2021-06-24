<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Fusion IO.  All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश "btrfs-tests.h"
#समावेश "../ctree.h"
#समावेश "../extent_io.h"
#समावेश "../disk-io.h"

अटल पूर्णांक test_btrfs_split_item(u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_root *root = शून्य;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_item *item;
	अक्षर *value = "mary had a little lamb";
	अक्षर *split1 = "mary had a little";
	अक्षर *split2 = " lamb";
	अक्षर *split3 = "mary";
	अक्षर *split4 = " had a little";
	अक्षर buf[32];
	काष्ठा btrfs_key key;
	u32 value_len = म_माप(value);
	पूर्णांक ret = 0;

	test_msg("running btrfs_split_item tests");

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

	path = btrfs_alloc_path();
	अगर (!path) अणु
		test_std_err(TEST_ALLOC_PATH);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	path->nodes[0] = eb = alloc_dummy_extent_buffer(fs_info, nodesize);
	अगर (!eb) अणु
		test_std_err(TEST_ALLOC_EXTENT_BUFFER);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	path->slots[0] = 0;

	key.objectid = 0;
	key.type = BTRFS_EXTENT_CSUM_KEY;
	key.offset = 0;

	setup_items_क्रम_insert(root, path, &key, &value_len, 1);
	item = btrfs_item_nr(0);
	ग_लिखो_extent_buffer(eb, value, btrfs_item_ptr_offset(eb, 0),
			    value_len);

	key.offset = 3;

	/*
	 * Passing शून्य trans here should be safe because we have plenty of
	 * space in this leaf to split the item without having to split the
	 * leaf.
	 */
	ret = btrfs_split_item(शून्य, root, path, &key, 17);
	अगर (ret) अणु
		test_err("split item failed %d", ret);
		जाओ out;
	पूर्ण

	/*
	 * Read the first slot, it should have the original key and contain only
	 * 'mary had a little'
	 */
	btrfs_item_key_to_cpu(eb, &key, 0);
	अगर (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 0) अणु
		test_err("invalid key at slot 0");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	item = btrfs_item_nr(0);
	अगर (btrfs_item_size(eb, item) != म_माप(split1)) अणु
		test_err("invalid len in the first split");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	पढ़ो_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 0),
			   म_माप(split1));
	अगर (स_भेद(buf, split1, म_माप(split1))) अणु
		test_err(
"data in the buffer doesn't match what it should in the first split have='%.*s' want '%s'",
			 (पूर्णांक)म_माप(split1), buf, split1);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	btrfs_item_key_to_cpu(eb, &key, 1);
	अगर (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 3) अणु
		test_err("invalid key at slot 1");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	item = btrfs_item_nr(1);
	अगर (btrfs_item_size(eb, item) != म_माप(split2)) अणु
		test_err("invalid len in the second split");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	पढ़ो_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 1),
			   म_माप(split2));
	अगर (स_भेद(buf, split2, म_माप(split2))) अणु
		test_err(
	"data in the buffer doesn't match what it should in the second split");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	key.offset = 1;
	/* Do it again so we test memmoving the other items in the leaf */
	ret = btrfs_split_item(शून्य, root, path, &key, 4);
	अगर (ret) अणु
		test_err("second split item failed %d", ret);
		जाओ out;
	पूर्ण

	btrfs_item_key_to_cpu(eb, &key, 0);
	अगर (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 0) अणु
		test_err("invalid key at slot 0");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	item = btrfs_item_nr(0);
	अगर (btrfs_item_size(eb, item) != म_माप(split3)) अणु
		test_err("invalid len in the first split");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	पढ़ो_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 0),
			   म_माप(split3));
	अगर (स_भेद(buf, split3, म_माप(split3))) अणु
		test_err(
	"data in the buffer doesn't match what it should in the third split");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	btrfs_item_key_to_cpu(eb, &key, 1);
	अगर (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 1) अणु
		test_err("invalid key at slot 1");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	item = btrfs_item_nr(1);
	अगर (btrfs_item_size(eb, item) != म_माप(split4)) अणु
		test_err("invalid len in the second split");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	पढ़ो_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 1),
			   म_माप(split4));
	अगर (स_भेद(buf, split4, म_माप(split4))) अणु
		test_err(
	"data in the buffer doesn't match what it should in the fourth split");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	btrfs_item_key_to_cpu(eb, &key, 2);
	अगर (key.objectid != 0 || key.type != BTRFS_EXTENT_CSUM_KEY ||
	    key.offset != 3) अणु
		test_err("invalid key at slot 2");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	item = btrfs_item_nr(2);
	अगर (btrfs_item_size(eb, item) != म_माप(split2)) अणु
		test_err("invalid len in the second split");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	पढ़ो_extent_buffer(eb, buf, btrfs_item_ptr_offset(eb, 2),
			   म_माप(split2));
	अगर (स_भेद(buf, split2, म_माप(split2))) अणु
		test_err(
	"data in the buffer doesn't match what it should in the last chunk");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	btrfs_मुक्त_dummy_root(root);
	btrfs_मुक्त_dummy_fs_info(fs_info);
	वापस ret;
पूर्ण

पूर्णांक btrfs_test_extent_buffer_operations(u32 sectorsize, u32 nodesize)
अणु
	test_msg("running extent buffer operation tests");
	वापस test_btrfs_split_item(sectorsize, nodesize);
पूर्ण
