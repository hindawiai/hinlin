<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "print-tree.h"
#समावेश "transaction.h"
#समावेश "locking.h"

/*
 * Defrag all the leaves in a given btree.
 * Read all the leaves and try to get key order to
 * better reflect disk order
 */

पूर्णांक btrfs_defrag_leaves(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_key key;
	पूर्णांक ret = 0;
	पूर्णांक wret;
	पूर्णांक level;
	पूर्णांक next_key_ret = 0;
	u64 last_ret = 0;

	अगर (root->fs_info->extent_root == root) अणु
		/*
		 * there's recursion here right now in the tree locking,
		 * we can't defrag the extent root without deadlock
		 */
		जाओ out;
	पूर्ण

	अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
		जाओ out;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	level = btrfs_header_level(root->node);

	अगर (level == 0)
		जाओ out;

	अगर (root->defrag_progress.objectid == 0) अणु
		काष्ठा extent_buffer *root_node;
		u32 nritems;

		root_node = btrfs_lock_root_node(root);
		nritems = btrfs_header_nritems(root_node);
		root->defrag_max.objectid = 0;
		/* from above we know this is not a leaf */
		btrfs_node_key_to_cpu(root_node, &root->defrag_max,
				      nritems - 1);
		btrfs_tree_unlock(root_node);
		मुक्त_extent_buffer(root_node);
		स_रखो(&key, 0, माप(key));
	पूर्ण अन्यथा अणु
		स_नकल(&key, &root->defrag_progress, माप(key));
	पूर्ण

	path->keep_locks = 1;

	ret = btrfs_search_क्रमward(root, &key, path, BTRFS_OLDEST_GENERATION);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	btrfs_release_path(path);
	/*
	 * We करोn't need a lock on a leaf. btrfs_पुनः_स्मृति_node() will lock all
	 * leafs from path->nodes[1], so set lowest_level to 1 to aव्योम later
	 * a deadlock (attempting to ग_लिखो lock an alपढ़ोy ग_लिखो locked leaf).
	 */
	path->lowest_level = 1;
	wret = btrfs_search_slot(trans, root, &key, path, 0, 1);

	अगर (wret < 0) अणु
		ret = wret;
		जाओ out;
	पूर्ण
	अगर (!path->nodes[1]) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	/*
	 * The node at level 1 must always be locked when our path has
	 * keep_locks set and lowest_level is 1, regardless of the value of
	 * path->slots[1].
	 */
	BUG_ON(path->locks[1] == 0);
	ret = btrfs_पुनः_स्मृति_node(trans, root,
				 path->nodes[1], 0,
				 &last_ret,
				 &root->defrag_progress);
	अगर (ret) अणु
		WARN_ON(ret == -EAGAIN);
		जाओ out;
	पूर्ण
	/*
	 * Now that we पुनः_स्मृतिated the node we can find the next key. Note that
	 * btrfs_find_next_key() can release our path and करो another search
	 * without COWing, this is because even with path->keep_locks = 1,
	 * btrfs_search_slot() / ctree.c:unlock_up() करोes not keeps a lock on a
	 * node when path->slots[node_level - 1] करोes not poपूर्णांक to the last
	 * item or a slot beyond the last item (ctree.c:unlock_up()). Thereक्रमe
	 * we search क्रम the next key after पुनः_स्मृतिating our node.
	 */
	path->slots[1] = btrfs_header_nritems(path->nodes[1]);
	next_key_ret = btrfs_find_next_key(root, path, &key, 1,
					   BTRFS_OLDEST_GENERATION);
	अगर (next_key_ret == 0) अणु
		स_नकल(&root->defrag_progress, &key, माप(key));
		ret = -EAGAIN;
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	अगर (ret == -EAGAIN) अणु
		अगर (root->defrag_max.objectid > root->defrag_progress.objectid)
			जाओ करोne;
		अगर (root->defrag_max.type > root->defrag_progress.type)
			जाओ करोne;
		अगर (root->defrag_max.offset > root->defrag_progress.offset)
			जाओ करोne;
		ret = 0;
	पूर्ण
करोne:
	अगर (ret != -EAGAIN)
		स_रखो(&root->defrag_progress, 0,
		       माप(root->defrag_progress));

	वापस ret;
पूर्ण
