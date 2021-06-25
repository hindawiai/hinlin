<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Red Hat.  All rights reserved.
 */

#समावेश "ctree.h"
#समावेश "disk-io.h"

पूर्णांक btrfs_insert_orphan_item(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root, u64 offset)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक ret = 0;

	key.objectid = BTRFS_ORPHAN_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = offset;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_insert_empty_item(trans, root, path, &key, 0);

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_del_orphan_item(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root, u64 offset)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक ret = 0;

	key.objectid = BTRFS_ORPHAN_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = offset;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;
	अगर (ret) अणु /* JDM: Really? */
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = btrfs_del_item(trans, root, path);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण
