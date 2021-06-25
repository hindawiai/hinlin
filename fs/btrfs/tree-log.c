<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/iversion.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "tree-log.h"
#समावेश "disk-io.h"
#समावेश "locking.h"
#समावेश "print-tree.h"
#समावेश "backref.h"
#समावेश "compression.h"
#समावेश "qgroup.h"
#समावेश "block-group.h"
#समावेश "space-info.h"
#समावेश "zoned.h"

/* magic values क्रम the inode_only field in btrfs_log_inode:
 *
 * LOG_INODE_ALL means to log everything
 * LOG_INODE_EXISTS means to log just enough to recreate the inode
 * during log replay
 */
क्रमागत अणु
	LOG_INODE_ALL,
	LOG_INODE_EXISTS,
	LOG_OTHER_INODE,
	LOG_OTHER_INODE_ALL,
पूर्ण;

/*
 * directory trouble हालs
 *
 * 1) on नाम or unlink, अगर the inode being unlinked isn't in the fsync
 * log, we must क्रमce a full commit beक्रमe करोing an fsync of the directory
 * where the unlink was करोne.
 * ---> record transid of last unlink/नाम per directory
 *
 * सूची_गढ़ो foo/some_dir
 * normal commit
 * नाम foo/some_dir foo2/some_dir
 * सूची_गढ़ो foo/some_dir
 * fsync foo/some_dir/some_file
 *
 * The fsync above will unlink the original some_dir without recording
 * it in its new location (foo2).  After a crash, some_dir will be gone
 * unless the fsync of some_file क्रमces a full commit
 *
 * 2) we must log any new names क्रम any file or dir that is in the fsync
 * log. ---> check inode जबतक renaming/linking.
 *
 * 2a) we must log any new names क्रम any file or dir during नाम
 * when the directory they are being हटाओd from was logged.
 * ---> check inode and old parent dir during नाम
 *
 *  2a is actually the more important variant.  With the extra logging
 *  a crash might unlink the old name without recreating the new one
 *
 * 3) after a crash, we must go through any directories with a link count
 * of zero and reकरो the rm -rf
 *
 * सूची_गढ़ो f1/foo
 * normal commit
 * rm -rf f1/foo
 * fsync(f1)
 *
 * The directory f1 was fully हटाओd from the FS, but fsync was never
 * called on f1, only its parent dir.  After a crash the rm -rf must
 * be replayed.  This must be able to recurse करोwn the entire
 * directory tree.  The inode link count fixup code takes care of the
 * ugly details.
 */

/*
 * stages क्रम the tree walking.  The first
 * stage (0) is to only pin करोwn the blocks we find
 * the second stage (1) is to make sure that all the inodes
 * we find in the log are created in the subvolume.
 *
 * The last stage is to deal with directories and links and extents
 * and all the other fun semantics
 */
क्रमागत अणु
	LOG_WALK_PIN_ONLY,
	LOG_WALK_REPLAY_INODES,
	LOG_WALK_REPLAY_सूची_INDEX,
	LOG_WALK_REPLAY_ALL,
पूर्ण;

अटल पूर्णांक btrfs_log_inode(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode,
			   पूर्णांक inode_only,
			   काष्ठा btrfs_log_ctx *ctx);
अटल पूर्णांक link_to_fixup_dir(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     काष्ठा btrfs_path *path, u64 objectid);
अटल noअंतरभूत पूर्णांक replay_dir_deletes(काष्ठा btrfs_trans_handle *trans,
				       काष्ठा btrfs_root *root,
				       काष्ठा btrfs_root *log,
				       काष्ठा btrfs_path *path,
				       u64 dirid, पूर्णांक del_all);
अटल व्योम रुको_log_commit(काष्ठा btrfs_root *root, पूर्णांक transid);

/*
 * tree logging is a special ग_लिखो ahead log used to make sure that
 * fsyncs and O_SYNCs can happen without करोing full tree commits.
 *
 * Full tree commits are expensive because they require commonly
 * modअगरied blocks to be recowed, creating many dirty pages in the
 * extent tree an 4x-6x higher ग_लिखो load than ext3.
 *
 * Instead of करोing a tree commit on every fsync, we use the
 * key ranges and transaction ids to find items क्रम a given file or directory
 * that have changed in this transaction.  Those items are copied पूर्णांकo
 * a special tree (one per subvolume root), that tree is written to disk
 * and then the fsync is considered complete.
 *
 * After a crash, items are copied out of the log-tree back पूर्णांकo the
 * subvolume tree.  Any file data extents found are recorded in the extent
 * allocation tree, and the log-tree मुक्तd.
 *
 * The log tree is पढ़ो three बार, once to pin करोwn all the extents it is
 * using in ram and once, once to create all the inodes logged in the tree
 * and once to करो all the other items.
 */

/*
 * start a sub transaction and setup the log tree
 * this increments the log tree ग_लिखोr count to make the people
 * syncing the tree रुको क्रम us to finish
 */
अटल पूर्णांक start_log_trans(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	स्थिर bool zoned = btrfs_is_zoned(fs_info);
	पूर्णांक ret = 0;
	bool created = false;

	/*
	 * First check अगर the log root tree was alपढ़ोy created. If not, create
	 * it beक्रमe locking the root's log_mutex, just to keep lockdep happy.
	 */
	अगर (!test_bit(BTRFS_ROOT_HAS_LOG_TREE, &tree_root->state)) अणु
		mutex_lock(&tree_root->log_mutex);
		अगर (!fs_info->log_root_tree) अणु
			ret = btrfs_init_log_root_tree(trans, fs_info);
			अगर (!ret) अणु
				set_bit(BTRFS_ROOT_HAS_LOG_TREE, &tree_root->state);
				created = true;
			पूर्ण
		पूर्ण
		mutex_unlock(&tree_root->log_mutex);
		अगर (ret)
			वापस ret;
	पूर्ण

	mutex_lock(&root->log_mutex);

again:
	अगर (root->log_root) अणु
		पूर्णांक index = (root->log_transid + 1) % 2;

		अगर (btrfs_need_log_full_commit(trans)) अणु
			ret = -EAGAIN;
			जाओ out;
		पूर्ण

		अगर (zoned && atomic_पढ़ो(&root->log_commit[index])) अणु
			रुको_log_commit(root, root->log_transid - 1);
			जाओ again;
		पूर्ण

		अगर (!root->log_start_pid) अणु
			clear_bit(BTRFS_ROOT_MULTI_LOG_TASKS, &root->state);
			root->log_start_pid = current->pid;
		पूर्ण अन्यथा अगर (root->log_start_pid != current->pid) अणु
			set_bit(BTRFS_ROOT_MULTI_LOG_TASKS, &root->state);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * This means fs_info->log_root_tree was alपढ़ोy created
		 * क्रम some other FS trees. Do the full commit not to mix
		 * nodes from multiple log transactions to करो sequential
		 * writing.
		 */
		अगर (zoned && !created) अणु
			ret = -EAGAIN;
			जाओ out;
		पूर्ण

		ret = btrfs_add_log_tree(trans, root);
		अगर (ret)
			जाओ out;

		set_bit(BTRFS_ROOT_HAS_LOG_TREE, &root->state);
		clear_bit(BTRFS_ROOT_MULTI_LOG_TASKS, &root->state);
		root->log_start_pid = current->pid;
	पूर्ण

	atomic_inc(&root->log_ग_लिखोrs);
	अगर (ctx && !ctx->logging_new_name) अणु
		पूर्णांक index = root->log_transid % 2;
		list_add_tail(&ctx->list, &root->log_ctxs[index]);
		ctx->log_transid = root->log_transid;
	पूर्ण

out:
	mutex_unlock(&root->log_mutex);
	वापस ret;
पूर्ण

/*
 * वापसs 0 अगर there was a log transaction running and we were able
 * to join, or वापसs -ENOENT अगर there were not transactions
 * in progress
 */
अटल पूर्णांक join_running_log_trans(काष्ठा btrfs_root *root)
अणु
	स्थिर bool zoned = btrfs_is_zoned(root->fs_info);
	पूर्णांक ret = -ENOENT;

	अगर (!test_bit(BTRFS_ROOT_HAS_LOG_TREE, &root->state))
		वापस ret;

	mutex_lock(&root->log_mutex);
again:
	अगर (root->log_root) अणु
		पूर्णांक index = (root->log_transid + 1) % 2;

		ret = 0;
		अगर (zoned && atomic_पढ़ो(&root->log_commit[index])) अणु
			रुको_log_commit(root, root->log_transid - 1);
			जाओ again;
		पूर्ण
		atomic_inc(&root->log_ग_लिखोrs);
	पूर्ण
	mutex_unlock(&root->log_mutex);
	वापस ret;
पूर्ण

/*
 * This either makes the current running log transaction रुको
 * until you call btrfs_end_log_trans() or it makes any future
 * log transactions रुको until you call btrfs_end_log_trans()
 */
व्योम btrfs_pin_log_trans(काष्ठा btrfs_root *root)
अणु
	atomic_inc(&root->log_ग_लिखोrs);
पूर्ण

/*
 * indicate we're करोne making changes to the log tree
 * and wake up anyone रुकोing to करो a sync
 */
व्योम btrfs_end_log_trans(काष्ठा btrfs_root *root)
अणु
	अगर (atomic_dec_and_test(&root->log_ग_लिखोrs)) अणु
		/* atomic_dec_and_test implies a barrier */
		cond_wake_up_nomb(&root->log_ग_लिखोr_रुको);
	पूर्ण
पूर्ण

अटल पूर्णांक btrfs_ग_लिखो_tree_block(काष्ठा extent_buffer *buf)
अणु
	वापस filemap_fdataग_लिखो_range(buf->pages[0]->mapping, buf->start,
					buf->start + buf->len - 1);
पूर्ण

अटल व्योम btrfs_रुको_tree_block_ग_लिखोback(काष्ठा extent_buffer *buf)
अणु
	filemap_fdataरुको_range(buf->pages[0]->mapping,
			        buf->start, buf->start + buf->len - 1);
पूर्ण

/*
 * the walk control काष्ठा is used to pass state करोwn the chain when
 * processing the log tree.  The stage field tells us which part
 * of the log tree processing we are currently करोing.  The others
 * are state fields used क्रम that specअगरic part
 */
काष्ठा walk_control अणु
	/* should we मुक्त the extent on disk when करोne?  This is used
	 * at transaction commit समय जबतक मुक्तing a log tree
	 */
	पूर्णांक मुक्त;

	/* should we ग_लिखो out the extent buffer?  This is used
	 * जबतक flushing the log tree to disk during a sync
	 */
	पूर्णांक ग_लिखो;

	/* should we रुको क्रम the extent buffer io to finish?  Also used
	 * जबतक flushing the log tree to disk क्रम a sync
	 */
	पूर्णांक रुको;

	/* pin only walk, we record which extents on disk beदीर्घ to the
	 * log trees
	 */
	पूर्णांक pin;

	/* what stage of the replay code we're currently in */
	पूर्णांक stage;

	/*
	 * Ignore any items from the inode currently being processed. Needs
	 * to be set every समय we find a BTRFS_INODE_ITEM_KEY and we are in
	 * the LOG_WALK_REPLAY_INODES stage.
	 */
	bool ignore_cur_inode;

	/* the root we are currently replaying */
	काष्ठा btrfs_root *replay_dest;

	/* the trans handle क्रम the current replay */
	काष्ठा btrfs_trans_handle *trans;

	/* the function that माला_लो used to process blocks we find in the
	 * tree.  Note the extent_buffer might not be up to date when it is
	 * passed in, and it must be checked or पढ़ो अगर you need the data
	 * inside it
	 */
	पूर्णांक (*process_func)(काष्ठा btrfs_root *log, काष्ठा extent_buffer *eb,
			    काष्ठा walk_control *wc, u64 gen, पूर्णांक level);
पूर्ण;

/*
 * process_func used to pin करोwn extents, ग_लिखो them or रुको on them
 */
अटल पूर्णांक process_one_buffer(काष्ठा btrfs_root *log,
			      काष्ठा extent_buffer *eb,
			      काष्ठा walk_control *wc, u64 gen, पूर्णांक level)
अणु
	काष्ठा btrfs_fs_info *fs_info = log->fs_info;
	पूर्णांक ret = 0;

	/*
	 * If this fs is mixed then we need to be able to process the leaves to
	 * pin करोwn any logged extents, so we have to पढ़ो the block.
	 */
	अगर (btrfs_fs_incompat(fs_info, MIXED_GROUPS)) अणु
		ret = btrfs_पढ़ो_buffer(eb, gen, level, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (wc->pin)
		ret = btrfs_pin_extent_क्रम_log_replay(wc->trans, eb->start,
						      eb->len);

	अगर (!ret && btrfs_buffer_uptodate(eb, gen, 0)) अणु
		अगर (wc->pin && btrfs_header_level(eb) == 0)
			ret = btrfs_exclude_logged_extents(eb);
		अगर (wc->ग_लिखो)
			btrfs_ग_लिखो_tree_block(eb);
		अगर (wc->रुको)
			btrfs_रुको_tree_block_ग_लिखोback(eb);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Item overग_लिखो used by replay and tree logging.  eb, slot and key all refer
 * to the src data we are copying out.
 *
 * root is the tree we are copying पूर्णांकo, and path is a scratch
 * path क्रम use in this function (it should be released on entry and
 * will be released on निकास).
 *
 * If the key is alपढ़ोy in the destination tree the existing item is
 * overwritten.  If the existing item isn't big enough, it is extended.
 * If it is too large, it is truncated.
 *
 * If the key isn't in the destination yet, a new item is inserted.
 */
अटल noअंतरभूत पूर्णांक overग_लिखो_item(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_root *root,
				   काष्ठा btrfs_path *path,
				   काष्ठा extent_buffer *eb, पूर्णांक slot,
				   काष्ठा btrfs_key *key)
अणु
	पूर्णांक ret;
	u32 item_size;
	u64 saved_i_size = 0;
	पूर्णांक save_old_i_size = 0;
	अचिन्हित दीर्घ src_ptr;
	अचिन्हित दीर्घ dst_ptr;
	पूर्णांक overग_लिखो_root = 0;
	bool inode_item = key->type == BTRFS_INODE_ITEM_KEY;

	अगर (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID)
		overग_लिखो_root = 1;

	item_size = btrfs_item_size_nr(eb, slot);
	src_ptr = btrfs_item_ptr_offset(eb, slot);

	/* look क्रम the key in the destination tree */
	ret = btrfs_search_slot(शून्य, root, key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0) अणु
		अक्षर *src_copy;
		अक्षर *dst_copy;
		u32 dst_size = btrfs_item_size_nr(path->nodes[0],
						  path->slots[0]);
		अगर (dst_size != item_size)
			जाओ insert;

		अगर (item_size == 0) अणु
			btrfs_release_path(path);
			वापस 0;
		पूर्ण
		dst_copy = kदो_स्मृति(item_size, GFP_NOFS);
		src_copy = kदो_स्मृति(item_size, GFP_NOFS);
		अगर (!dst_copy || !src_copy) अणु
			btrfs_release_path(path);
			kमुक्त(dst_copy);
			kमुक्त(src_copy);
			वापस -ENOMEM;
		पूर्ण

		पढ़ो_extent_buffer(eb, src_copy, src_ptr, item_size);

		dst_ptr = btrfs_item_ptr_offset(path->nodes[0], path->slots[0]);
		पढ़ो_extent_buffer(path->nodes[0], dst_copy, dst_ptr,
				   item_size);
		ret = स_भेद(dst_copy, src_copy, item_size);

		kमुक्त(dst_copy);
		kमुक्त(src_copy);
		/*
		 * they have the same contents, just वापस, this saves
		 * us from cowing blocks in the destination tree and करोing
		 * extra ग_लिखोs that may not have been करोne by a previous
		 * sync
		 */
		अगर (ret == 0) अणु
			btrfs_release_path(path);
			वापस 0;
		पूर्ण

		/*
		 * We need to load the old nbytes पूर्णांकo the inode so when we
		 * replay the extents we've logged we get the right nbytes.
		 */
		अगर (inode_item) अणु
			काष्ठा btrfs_inode_item *item;
			u64 nbytes;
			u32 mode;

			item = btrfs_item_ptr(path->nodes[0], path->slots[0],
					      काष्ठा btrfs_inode_item);
			nbytes = btrfs_inode_nbytes(path->nodes[0], item);
			item = btrfs_item_ptr(eb, slot,
					      काष्ठा btrfs_inode_item);
			btrfs_set_inode_nbytes(eb, item, nbytes);

			/*
			 * If this is a directory we need to reset the i_size to
			 * 0 so that we can set it up properly when replaying
			 * the rest of the items in this log.
			 */
			mode = btrfs_inode_mode(eb, item);
			अगर (S_ISसूची(mode))
				btrfs_set_inode_size(eb, item, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (inode_item) अणु
		काष्ठा btrfs_inode_item *item;
		u32 mode;

		/*
		 * New inode, set nbytes to 0 so that the nbytes comes out
		 * properly when we replay the extents.
		 */
		item = btrfs_item_ptr(eb, slot, काष्ठा btrfs_inode_item);
		btrfs_set_inode_nbytes(eb, item, 0);

		/*
		 * If this is a directory we need to reset the i_size to 0 so
		 * that we can set it up properly when replaying the rest of
		 * the items in this log.
		 */
		mode = btrfs_inode_mode(eb, item);
		अगर (S_ISसूची(mode))
			btrfs_set_inode_size(eb, item, 0);
	पूर्ण
insert:
	btrfs_release_path(path);
	/* try to insert the key पूर्णांकo the destination tree */
	path->skip_release_on_error = 1;
	ret = btrfs_insert_empty_item(trans, root, path,
				      key, item_size);
	path->skip_release_on_error = 0;

	/* make sure any existing item is the correct size */
	अगर (ret == -EEXIST || ret == -EOVERFLOW) अणु
		u32 found_size;
		found_size = btrfs_item_size_nr(path->nodes[0],
						path->slots[0]);
		अगर (found_size > item_size)
			btrfs_truncate_item(path, item_size, 1);
		अन्यथा अगर (found_size < item_size)
			btrfs_extend_item(path, item_size - found_size);
	पूर्ण अन्यथा अगर (ret) अणु
		वापस ret;
	पूर्ण
	dst_ptr = btrfs_item_ptr_offset(path->nodes[0],
					path->slots[0]);

	/* करोn't overग_लिखो an existing inode अगर the generation number
	 * was logged as zero.  This is करोne when the tree logging code
	 * is just logging an inode to make sure it exists after recovery.
	 *
	 * Also, करोn't overग_लिखो i_size on directories during replay.
	 * log replay inserts and हटाओs directory items based on the
	 * state of the tree found in the subvolume, and i_size is modअगरied
	 * as it goes
	 */
	अगर (key->type == BTRFS_INODE_ITEM_KEY && ret == -EEXIST) अणु
		काष्ठा btrfs_inode_item *src_item;
		काष्ठा btrfs_inode_item *dst_item;

		src_item = (काष्ठा btrfs_inode_item *)src_ptr;
		dst_item = (काष्ठा btrfs_inode_item *)dst_ptr;

		अगर (btrfs_inode_generation(eb, src_item) == 0) अणु
			काष्ठा extent_buffer *dst_eb = path->nodes[0];
			स्थिर u64 ino_size = btrfs_inode_size(eb, src_item);

			/*
			 * For regular files an ino_size == 0 is used only when
			 * logging that an inode exists, as part of a directory
			 * fsync, and the inode wasn't fsynced beक्रमe. In this
			 * हाल करोn't set the size of the inode in the fs/subvol
			 * tree, otherwise we would be throwing valid data away.
			 */
			अगर (S_ISREG(btrfs_inode_mode(eb, src_item)) &&
			    S_ISREG(btrfs_inode_mode(dst_eb, dst_item)) &&
			    ino_size != 0)
				btrfs_set_inode_size(dst_eb, dst_item, ino_size);
			जाओ no_copy;
		पूर्ण

		अगर (overग_लिखो_root &&
		    S_ISसूची(btrfs_inode_mode(eb, src_item)) &&
		    S_ISसूची(btrfs_inode_mode(path->nodes[0], dst_item))) अणु
			save_old_i_size = 1;
			saved_i_size = btrfs_inode_size(path->nodes[0],
							dst_item);
		पूर्ण
	पूर्ण

	copy_extent_buffer(path->nodes[0], eb, dst_ptr,
			   src_ptr, item_size);

	अगर (save_old_i_size) अणु
		काष्ठा btrfs_inode_item *dst_item;
		dst_item = (काष्ठा btrfs_inode_item *)dst_ptr;
		btrfs_set_inode_size(path->nodes[0], dst_item, saved_i_size);
	पूर्ण

	/* make sure the generation is filled in */
	अगर (key->type == BTRFS_INODE_ITEM_KEY) अणु
		काष्ठा btrfs_inode_item *dst_item;
		dst_item = (काष्ठा btrfs_inode_item *)dst_ptr;
		अगर (btrfs_inode_generation(path->nodes[0], dst_item) == 0) अणु
			btrfs_set_inode_generation(path->nodes[0], dst_item,
						   trans->transid);
		पूर्ण
	पूर्ण
no_copy:
	btrfs_mark_buffer_dirty(path->nodes[0]);
	btrfs_release_path(path);
	वापस 0;
पूर्ण

/*
 * simple helper to पढ़ो an inode off the disk from a given root
 * This can only be called क्रम subvolume roots and not क्रम the log
 */
अटल noअंतरभूत काष्ठा inode *पढ़ो_one_inode(काष्ठा btrfs_root *root,
					     u64 objectid)
अणु
	काष्ठा inode *inode;

	inode = btrfs_iget(root->fs_info->sb, objectid, root);
	अगर (IS_ERR(inode))
		inode = शून्य;
	वापस inode;
पूर्ण

/* replays a single extent in 'eb' at 'slot' with 'key' पूर्णांकo the
 * subvolume 'root'.  path is released on entry and should be released
 * on निकास.
 *
 * extents in the log tree have not been allocated out of the extent
 * tree yet.  So, this completes the allocation, taking a reference
 * as required अगर the extent alपढ़ोy exists or creating a new extent
 * अगर it isn't in the extent allocation tree yet.
 *
 * The extent is inserted पूर्णांकo the file, dropping any existing extents
 * from the file that overlap the new one.
 */
अटल noअंतरभूत पूर्णांक replay_one_extent(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_root *root,
				      काष्ठा btrfs_path *path,
				      काष्ठा extent_buffer *eb, पूर्णांक slot,
				      काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_drop_extents_args drop_args = अणु 0 पूर्ण;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक found_type;
	u64 extent_end;
	u64 start = key->offset;
	u64 nbytes = 0;
	काष्ठा btrfs_file_extent_item *item;
	काष्ठा inode *inode = शून्य;
	अचिन्हित दीर्घ size;
	पूर्णांक ret = 0;

	item = btrfs_item_ptr(eb, slot, काष्ठा btrfs_file_extent_item);
	found_type = btrfs_file_extent_type(eb, item);

	अगर (found_type == BTRFS_खाता_EXTENT_REG ||
	    found_type == BTRFS_खाता_EXTENT_PREALLOC) अणु
		nbytes = btrfs_file_extent_num_bytes(eb, item);
		extent_end = start + nbytes;

		/*
		 * We करोn't add to the inodes nbytes अगर we are pपुनः_स्मृति or a
		 * hole.
		 */
		अगर (btrfs_file_extent_disk_bytenr(eb, item) == 0)
			nbytes = 0;
	पूर्ण अन्यथा अगर (found_type == BTRFS_खाता_EXTENT_INLINE) अणु
		size = btrfs_file_extent_ram_bytes(eb, item);
		nbytes = btrfs_file_extent_ram_bytes(eb, item);
		extent_end = ALIGN(start + size,
				   fs_info->sectorsize);
	पूर्ण अन्यथा अणु
		ret = 0;
		जाओ out;
	पूर्ण

	inode = पढ़ो_one_inode(root, key->objectid);
	अगर (!inode) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/*
	 * first check to see अगर we alपढ़ोy have this extent in the
	 * file.  This must be करोne beक्रमe the btrfs_drop_extents run
	 * so we करोn't try to drop this extent.
	 */
	ret = btrfs_lookup_file_extent(trans, root, path,
			btrfs_ino(BTRFS_I(inode)), start, 0);

	अगर (ret == 0 &&
	    (found_type == BTRFS_खाता_EXTENT_REG ||
	     found_type == BTRFS_खाता_EXTENT_PREALLOC)) अणु
		काष्ठा btrfs_file_extent_item cmp1;
		काष्ठा btrfs_file_extent_item cmp2;
		काष्ठा btrfs_file_extent_item *existing;
		काष्ठा extent_buffer *leaf;

		leaf = path->nodes[0];
		existing = btrfs_item_ptr(leaf, path->slots[0],
					  काष्ठा btrfs_file_extent_item);

		पढ़ो_extent_buffer(eb, &cmp1, (अचिन्हित दीर्घ)item,
				   माप(cmp1));
		पढ़ो_extent_buffer(leaf, &cmp2, (अचिन्हित दीर्घ)existing,
				   माप(cmp2));

		/*
		 * we alपढ़ोy have a poपूर्णांकer to this exact extent,
		 * we करोn't have to करो anything
		 */
		अगर (स_भेद(&cmp1, &cmp2, माप(cmp1)) == 0) अणु
			btrfs_release_path(path);
			जाओ out;
		पूर्ण
	पूर्ण
	btrfs_release_path(path);

	/* drop any overlapping extents */
	drop_args.start = start;
	drop_args.end = extent_end;
	drop_args.drop_cache = true;
	ret = btrfs_drop_extents(trans, root, BTRFS_I(inode), &drop_args);
	अगर (ret)
		जाओ out;

	अगर (found_type == BTRFS_खाता_EXTENT_REG ||
	    found_type == BTRFS_खाता_EXTENT_PREALLOC) अणु
		u64 offset;
		अचिन्हित दीर्घ dest_offset;
		काष्ठा btrfs_key ins;

		अगर (btrfs_file_extent_disk_bytenr(eb, item) == 0 &&
		    btrfs_fs_incompat(fs_info, NO_HOLES))
			जाओ update_inode;

		ret = btrfs_insert_empty_item(trans, root, path, key,
					      माप(*item));
		अगर (ret)
			जाओ out;
		dest_offset = btrfs_item_ptr_offset(path->nodes[0],
						    path->slots[0]);
		copy_extent_buffer(path->nodes[0], eb, dest_offset,
				(अचिन्हित दीर्घ)item,  माप(*item));

		ins.objectid = btrfs_file_extent_disk_bytenr(eb, item);
		ins.offset = btrfs_file_extent_disk_num_bytes(eb, item);
		ins.type = BTRFS_EXTENT_ITEM_KEY;
		offset = key->offset - btrfs_file_extent_offset(eb, item);

		/*
		 * Manually record dirty extent, as here we did a shallow
		 * file extent item copy and skip normal backref update,
		 * but modअगरying extent tree all by ourselves.
		 * So need to manually record dirty extent क्रम qgroup,
		 * as the owner of the file extent changed from log tree
		 * (करोesn't affect qgroup) to fs/file tree(affects qgroup)
		 */
		ret = btrfs_qgroup_trace_extent(trans,
				btrfs_file_extent_disk_bytenr(eb, item),
				btrfs_file_extent_disk_num_bytes(eb, item),
				GFP_NOFS);
		अगर (ret < 0)
			जाओ out;

		अगर (ins.objectid > 0) अणु
			काष्ठा btrfs_ref ref = अणु 0 पूर्ण;
			u64 csum_start;
			u64 csum_end;
			LIST_HEAD(ordered_sums);

			/*
			 * is this extent alपढ़ोy allocated in the extent
			 * allocation tree?  If so, just add a reference
			 */
			ret = btrfs_lookup_data_extent(fs_info, ins.objectid,
						ins.offset);
			अगर (ret == 0) अणु
				btrfs_init_generic_ref(&ref,
						BTRFS_ADD_DELAYED_REF,
						ins.objectid, ins.offset, 0);
				btrfs_init_data_ref(&ref,
						root->root_key.objectid,
						key->objectid, offset);
				ret = btrfs_inc_extent_ref(trans, &ref);
				अगर (ret)
					जाओ out;
			पूर्ण अन्यथा अणु
				/*
				 * insert the extent poपूर्णांकer in the extent
				 * allocation tree
				 */
				ret = btrfs_alloc_logged_file_extent(trans,
						root->root_key.objectid,
						key->objectid, offset, &ins);
				अगर (ret)
					जाओ out;
			पूर्ण
			btrfs_release_path(path);

			अगर (btrfs_file_extent_compression(eb, item)) अणु
				csum_start = ins.objectid;
				csum_end = csum_start + ins.offset;
			पूर्ण अन्यथा अणु
				csum_start = ins.objectid +
					btrfs_file_extent_offset(eb, item);
				csum_end = csum_start +
					btrfs_file_extent_num_bytes(eb, item);
			पूर्ण

			ret = btrfs_lookup_csums_range(root->log_root,
						csum_start, csum_end - 1,
						&ordered_sums, 0);
			अगर (ret)
				जाओ out;
			/*
			 * Now delete all existing cums in the csum root that
			 * cover our range. We करो this because we can have an
			 * extent that is completely referenced by one file
			 * extent item and partially referenced by another
			 * file extent item (like after using the clone or
			 * extent_same ioctls). In this हाल अगर we end up करोing
			 * the replay of the one that partially references the
			 * extent first, and we करो not करो the csum deletion
			 * below, we can get 2 csum items in the csum tree that
			 * overlap each other. For example, imagine our log has
			 * the two following file extent items:
			 *
			 * key (257 EXTENT_DATA 409600)
			 *     extent data disk byte 12845056 nr 102400
			 *     extent data offset 20480 nr 20480 ram 102400
			 *
			 * key (257 EXTENT_DATA 819200)
			 *     extent data disk byte 12845056 nr 102400
			 *     extent data offset 0 nr 102400 ram 102400
			 *
			 * Where the second one fully references the 100K extent
			 * that starts at disk byte 12845056, and the log tree
			 * has a single csum item that covers the entire range
			 * of the extent:
			 *
			 * key (EXTENT_CSUM EXTENT_CSUM 12845056) itemsize 100
			 *
			 * After the first file extent item is replayed, the
			 * csum tree माला_लो the following csum item:
			 *
			 * key (EXTENT_CSUM EXTENT_CSUM 12865536) itemsize 20
			 *
			 * Which covers the 20K sub-range starting at offset 20K
			 * of our extent. Now when we replay the second file
			 * extent item, अगर we करो not delete existing csum items
			 * that cover any of its blocks, we end up getting two
			 * csum items in our csum tree that overlap each other:
			 *
			 * key (EXTENT_CSUM EXTENT_CSUM 12845056) itemsize 100
			 * key (EXTENT_CSUM EXTENT_CSUM 12865536) itemsize 20
			 *
			 * Which is a problem, because after this anyone trying
			 * to lookup up क्रम the checksum of any block of our
			 * extent starting at an offset of 40K or higher, will
			 * end up looking at the second csum item only, which
			 * करोes not contain the checksum क्रम any block starting
			 * at offset 40K or higher of our extent.
			 */
			जबतक (!list_empty(&ordered_sums)) अणु
				काष्ठा btrfs_ordered_sum *sums;
				sums = list_entry(ordered_sums.next,
						काष्ठा btrfs_ordered_sum,
						list);
				अगर (!ret)
					ret = btrfs_del_csums(trans,
							      fs_info->csum_root,
							      sums->bytenr,
							      sums->len);
				अगर (!ret)
					ret = btrfs_csum_file_blocks(trans,
						fs_info->csum_root, sums);
				list_del(&sums->list);
				kमुक्त(sums);
			पूर्ण
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अणु
			btrfs_release_path(path);
		पूर्ण
	पूर्ण अन्यथा अगर (found_type == BTRFS_खाता_EXTENT_INLINE) अणु
		/* अंतरभूत extents are easy, we just overग_लिखो them */
		ret = overग_लिखो_item(trans, root, path, eb, slot, key);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = btrfs_inode_set_file_extent_range(BTRFS_I(inode), start,
						extent_end - start);
	अगर (ret)
		जाओ out;

update_inode:
	btrfs_update_inode_bytes(BTRFS_I(inode), nbytes, drop_args.bytes_found);
	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
out:
	अगर (inode)
		iput(inode);
	वापस ret;
पूर्ण

/*
 * when cleaning up conflicts between the directory names in the
 * subvolume, directory names in the log and directory names in the
 * inode back references, we may have to unlink inodes from directories.
 *
 * This is a helper function to करो the unlink of a specअगरic directory
 * item
 */
अटल noअंतरभूत पूर्णांक drop_one_dir_item(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_root *root,
				      काष्ठा btrfs_path *path,
				      काष्ठा btrfs_inode *dir,
				      काष्ठा btrfs_dir_item *di)
अणु
	काष्ठा inode *inode;
	अक्षर *name;
	पूर्णांक name_len;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key location;
	पूर्णांक ret;

	leaf = path->nodes[0];

	btrfs_dir_item_key_to_cpu(leaf, di, &location);
	name_len = btrfs_dir_name_len(leaf, di);
	name = kदो_स्मृति(name_len, GFP_NOFS);
	अगर (!name)
		वापस -ENOMEM;

	पढ़ो_extent_buffer(leaf, name, (अचिन्हित दीर्घ)(di + 1), name_len);
	btrfs_release_path(path);

	inode = पढ़ो_one_inode(root, location.objectid);
	अगर (!inode) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = link_to_fixup_dir(trans, root, path, location.objectid);
	अगर (ret)
		जाओ out;

	ret = btrfs_unlink_inode(trans, root, dir, BTRFS_I(inode), name,
			name_len);
	अगर (ret)
		जाओ out;
	अन्यथा
		ret = btrfs_run_delayed_items(trans);
out:
	kमुक्त(name);
	iput(inode);
	वापस ret;
पूर्ण

/*
 * helper function to see अगर a given name and sequence number found
 * in an inode back reference are alपढ़ोy in a directory and correctly
 * poपूर्णांक to this inode
 */
अटल noअंतरभूत पूर्णांक inode_in_dir(काष्ठा btrfs_root *root,
				 काष्ठा btrfs_path *path,
				 u64 dirid, u64 objectid, u64 index,
				 स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_key location;
	पूर्णांक match = 0;

	di = btrfs_lookup_dir_index_item(शून्य, root, path, dirid,
					 index, name, name_len, 0);
	अगर (di && !IS_ERR(di)) अणु
		btrfs_dir_item_key_to_cpu(path->nodes[0], di, &location);
		अगर (location.objectid != objectid)
			जाओ out;
	पूर्ण अन्यथा
		जाओ out;
	btrfs_release_path(path);

	di = btrfs_lookup_dir_item(शून्य, root, path, dirid, name, name_len, 0);
	अगर (di && !IS_ERR(di)) अणु
		btrfs_dir_item_key_to_cpu(path->nodes[0], di, &location);
		अगर (location.objectid != objectid)
			जाओ out;
	पूर्ण अन्यथा
		जाओ out;
	match = 1;
out:
	btrfs_release_path(path);
	वापस match;
पूर्ण

/*
 * helper function to check a log tree क्रम a named back reference in
 * an inode.  This is used to decide अगर a back reference that is
 * found in the subvolume conflicts with what we find in the log.
 *
 * inode backreferences may have multiple refs in a single item,
 * during replay we process one reference at a समय, and we करोn't
 * want to delete valid links to a file from the subvolume अगर that
 * link is also in the log.
 */
अटल noअंतरभूत पूर्णांक backref_in_log(काष्ठा btrfs_root *log,
				   काष्ठा btrfs_key *key,
				   u64 ref_objectid,
				   स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा btrfs_path *path;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_search_slot(शून्य, log, key, path, 0, 0);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (ret == 1) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (key->type == BTRFS_INODE_EXTREF_KEY)
		ret = !!btrfs_find_name_in_ext_backref(path->nodes[0],
						       path->slots[0],
						       ref_objectid,
						       name, namelen);
	अन्यथा
		ret = !!btrfs_find_name_in_backref(path->nodes[0],
						   path->slots[0],
						   name, namelen);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __add_inode_ref(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_root *root,
				  काष्ठा btrfs_path *path,
				  काष्ठा btrfs_root *log_root,
				  काष्ठा btrfs_inode *dir,
				  काष्ठा btrfs_inode *inode,
				  u64 inode_objectid, u64 parent_objectid,
				  u64 ref_index, अक्षर *name, पूर्णांक namelen,
				  पूर्णांक *search_करोne)
अणु
	पूर्णांक ret;
	अक्षर *victim_name;
	पूर्णांक victim_name_len;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_key search_key;
	काष्ठा btrfs_inode_extref *extref;

again:
	/* Search old style refs */
	search_key.objectid = inode_objectid;
	search_key.type = BTRFS_INODE_REF_KEY;
	search_key.offset = parent_objectid;
	ret = btrfs_search_slot(शून्य, root, &search_key, path, 0, 0);
	अगर (ret == 0) अणु
		काष्ठा btrfs_inode_ref *victim_ref;
		अचिन्हित दीर्घ ptr;
		अचिन्हित दीर्घ ptr_end;

		leaf = path->nodes[0];

		/* are we trying to overग_लिखो a back ref क्रम the root directory
		 * अगर so, just jump out, we're करोne
		 */
		अगर (search_key.objectid == search_key.offset)
			वापस 1;

		/* check all the names in this back reference to see
		 * अगर they are in the log.  अगर so, we allow them to stay
		 * otherwise they must be unlinked as a conflict
		 */
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		ptr_end = ptr + btrfs_item_size_nr(leaf, path->slots[0]);
		जबतक (ptr < ptr_end) अणु
			victim_ref = (काष्ठा btrfs_inode_ref *)ptr;
			victim_name_len = btrfs_inode_ref_name_len(leaf,
								   victim_ref);
			victim_name = kदो_स्मृति(victim_name_len, GFP_NOFS);
			अगर (!victim_name)
				वापस -ENOMEM;

			पढ़ो_extent_buffer(leaf, victim_name,
					   (अचिन्हित दीर्घ)(victim_ref + 1),
					   victim_name_len);

			ret = backref_in_log(log_root, &search_key,
					     parent_objectid, victim_name,
					     victim_name_len);
			अगर (ret < 0) अणु
				kमुक्त(victim_name);
				वापस ret;
			पूर्ण अन्यथा अगर (!ret) अणु
				inc_nlink(&inode->vfs_inode);
				btrfs_release_path(path);

				ret = btrfs_unlink_inode(trans, root, dir, inode,
						victim_name, victim_name_len);
				kमुक्त(victim_name);
				अगर (ret)
					वापस ret;
				ret = btrfs_run_delayed_items(trans);
				अगर (ret)
					वापस ret;
				*search_करोne = 1;
				जाओ again;
			पूर्ण
			kमुक्त(victim_name);

			ptr = (अचिन्हित दीर्घ)(victim_ref + 1) + victim_name_len;
		पूर्ण

		/*
		 * NOTE: we have searched root tree and checked the
		 * corresponding ref, it करोes not need to check again.
		 */
		*search_करोne = 1;
	पूर्ण
	btrfs_release_path(path);

	/* Same search but क्रम extended refs */
	extref = btrfs_lookup_inode_extref(शून्य, root, path, name, namelen,
					   inode_objectid, parent_objectid, 0,
					   0);
	अगर (!IS_ERR_OR_शून्य(extref)) अणु
		u32 item_size;
		u32 cur_offset = 0;
		अचिन्हित दीर्घ base;
		काष्ठा inode *victim_parent;

		leaf = path->nodes[0];

		item_size = btrfs_item_size_nr(leaf, path->slots[0]);
		base = btrfs_item_ptr_offset(leaf, path->slots[0]);

		जबतक (cur_offset < item_size) अणु
			extref = (काष्ठा btrfs_inode_extref *)(base + cur_offset);

			victim_name_len = btrfs_inode_extref_name_len(leaf, extref);

			अगर (btrfs_inode_extref_parent(leaf, extref) != parent_objectid)
				जाओ next;

			victim_name = kदो_स्मृति(victim_name_len, GFP_NOFS);
			अगर (!victim_name)
				वापस -ENOMEM;
			पढ़ो_extent_buffer(leaf, victim_name, (अचिन्हित दीर्घ)&extref->name,
					   victim_name_len);

			search_key.objectid = inode_objectid;
			search_key.type = BTRFS_INODE_EXTREF_KEY;
			search_key.offset = btrfs_extref_hash(parent_objectid,
							      victim_name,
							      victim_name_len);
			ret = backref_in_log(log_root, &search_key,
					     parent_objectid, victim_name,
					     victim_name_len);
			अगर (ret < 0) अणु
				वापस ret;
			पूर्ण अन्यथा अगर (!ret) अणु
				ret = -ENOENT;
				victim_parent = पढ़ो_one_inode(root,
						parent_objectid);
				अगर (victim_parent) अणु
					inc_nlink(&inode->vfs_inode);
					btrfs_release_path(path);

					ret = btrfs_unlink_inode(trans, root,
							BTRFS_I(victim_parent),
							inode,
							victim_name,
							victim_name_len);
					अगर (!ret)
						ret = btrfs_run_delayed_items(
								  trans);
				पूर्ण
				iput(victim_parent);
				kमुक्त(victim_name);
				अगर (ret)
					वापस ret;
				*search_करोne = 1;
				जाओ again;
			पूर्ण
			kमुक्त(victim_name);
next:
			cur_offset += victim_name_len + माप(*extref);
		पूर्ण
		*search_करोne = 1;
	पूर्ण
	btrfs_release_path(path);

	/* look क्रम a conflicting sequence number */
	di = btrfs_lookup_dir_index_item(trans, root, path, btrfs_ino(dir),
					 ref_index, name, namelen, 0);
	अगर (di && !IS_ERR(di)) अणु
		ret = drop_one_dir_item(trans, root, path, dir, di);
		अगर (ret)
			वापस ret;
	पूर्ण
	btrfs_release_path(path);

	/* look क्रम a conflicting name */
	di = btrfs_lookup_dir_item(trans, root, path, btrfs_ino(dir),
				   name, namelen, 0);
	अगर (di && !IS_ERR(di)) अणु
		ret = drop_one_dir_item(trans, root, path, dir, di);
		अगर (ret)
			वापस ret;
	पूर्ण
	btrfs_release_path(path);

	वापस 0;
पूर्ण

अटल पूर्णांक extref_get_fields(काष्ठा extent_buffer *eb, अचिन्हित दीर्घ ref_ptr,
			     u32 *namelen, अक्षर **name, u64 *index,
			     u64 *parent_objectid)
अणु
	काष्ठा btrfs_inode_extref *extref;

	extref = (काष्ठा btrfs_inode_extref *)ref_ptr;

	*namelen = btrfs_inode_extref_name_len(eb, extref);
	*name = kदो_स्मृति(*namelen, GFP_NOFS);
	अगर (*name == शून्य)
		वापस -ENOMEM;

	पढ़ो_extent_buffer(eb, *name, (अचिन्हित दीर्घ)&extref->name,
			   *namelen);

	अगर (index)
		*index = btrfs_inode_extref_index(eb, extref);
	अगर (parent_objectid)
		*parent_objectid = btrfs_inode_extref_parent(eb, extref);

	वापस 0;
पूर्ण

अटल पूर्णांक ref_get_fields(काष्ठा extent_buffer *eb, अचिन्हित दीर्घ ref_ptr,
			  u32 *namelen, अक्षर **name, u64 *index)
अणु
	काष्ठा btrfs_inode_ref *ref;

	ref = (काष्ठा btrfs_inode_ref *)ref_ptr;

	*namelen = btrfs_inode_ref_name_len(eb, ref);
	*name = kदो_स्मृति(*namelen, GFP_NOFS);
	अगर (*name == शून्य)
		वापस -ENOMEM;

	पढ़ो_extent_buffer(eb, *name, (अचिन्हित दीर्घ)(ref + 1), *namelen);

	अगर (index)
		*index = btrfs_inode_ref_index(eb, ref);

	वापस 0;
पूर्ण

/*
 * Take an inode reference item from the log tree and iterate all names from the
 * inode reference item in the subvolume tree with the same key (अगर it exists).
 * For any name that is not in the inode reference item from the log tree, करो a
 * proper unlink of that name (that is, हटाओ its entry from the inode
 * reference item and both dir index keys).
 */
अटल पूर्णांक unlink_old_inode_refs(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root,
				 काष्ठा btrfs_path *path,
				 काष्ठा btrfs_inode *inode,
				 काष्ठा extent_buffer *log_eb,
				 पूर्णांक log_slot,
				 काष्ठा btrfs_key *key)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ ref_ptr;
	अचिन्हित दीर्घ ref_end;
	काष्ठा extent_buffer *eb;

again:
	btrfs_release_path(path);
	ret = btrfs_search_slot(शून्य, root, key, path, 0, 0);
	अगर (ret > 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	eb = path->nodes[0];
	ref_ptr = btrfs_item_ptr_offset(eb, path->slots[0]);
	ref_end = ref_ptr + btrfs_item_size_nr(eb, path->slots[0]);
	जबतक (ref_ptr < ref_end) अणु
		अक्षर *name = शून्य;
		पूर्णांक namelen;
		u64 parent_id;

		अगर (key->type == BTRFS_INODE_EXTREF_KEY) अणु
			ret = extref_get_fields(eb, ref_ptr, &namelen, &name,
						शून्य, &parent_id);
		पूर्ण अन्यथा अणु
			parent_id = key->offset;
			ret = ref_get_fields(eb, ref_ptr, &namelen, &name,
					     शून्य);
		पूर्ण
		अगर (ret)
			जाओ out;

		अगर (key->type == BTRFS_INODE_EXTREF_KEY)
			ret = !!btrfs_find_name_in_ext_backref(log_eb, log_slot,
							       parent_id, name,
							       namelen);
		अन्यथा
			ret = !!btrfs_find_name_in_backref(log_eb, log_slot,
							   name, namelen);

		अगर (!ret) अणु
			काष्ठा inode *dir;

			btrfs_release_path(path);
			dir = पढ़ो_one_inode(root, parent_id);
			अगर (!dir) अणु
				ret = -ENOENT;
				kमुक्त(name);
				जाओ out;
			पूर्ण
			ret = btrfs_unlink_inode(trans, root, BTRFS_I(dir),
						 inode, name, namelen);
			kमुक्त(name);
			iput(dir);
			अगर (ret)
				जाओ out;
			जाओ again;
		पूर्ण

		kमुक्त(name);
		ref_ptr += namelen;
		अगर (key->type == BTRFS_INODE_EXTREF_KEY)
			ref_ptr += माप(काष्ठा btrfs_inode_extref);
		अन्यथा
			ref_ptr += माप(काष्ठा btrfs_inode_ref);
	पूर्ण
	ret = 0;
 out:
	btrfs_release_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_inode_ref_exists(काष्ठा inode *inode, काष्ठा inode *dir,
				  स्थिर u8 ref_type, स्थिर अक्षर *name,
				  स्थिर पूर्णांक namelen)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	स्थिर u64 parent_id = btrfs_ino(BTRFS_I(dir));
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = btrfs_ino(BTRFS_I(inode));
	key.type = ref_type;
	अगर (key.type == BTRFS_INODE_REF_KEY)
		key.offset = parent_id;
	अन्यथा
		key.offset = btrfs_extref_hash(parent_id, name, namelen);

	ret = btrfs_search_slot(शून्य, BTRFS_I(inode)->root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	अगर (key.type == BTRFS_INODE_EXTREF_KEY)
		ret = !!btrfs_find_name_in_ext_backref(path->nodes[0],
				path->slots[0], parent_id, name, namelen);
	अन्यथा
		ret = !!btrfs_find_name_in_backref(path->nodes[0], path->slots[0],
						   name, namelen);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक add_link(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		    काष्ठा inode *dir, काष्ठा inode *inode, स्थिर अक्षर *name,
		    पूर्णांक namelen, u64 ref_index)
अणु
	काष्ठा btrfs_dir_item *dir_item;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	काष्ठा inode *other_inode = शून्य;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	dir_item = btrfs_lookup_dir_item(शून्य, root, path,
					 btrfs_ino(BTRFS_I(dir)),
					 name, namelen, 0);
	अगर (!dir_item) अणु
		btrfs_release_path(path);
		जाओ add_link;
	पूर्ण अन्यथा अगर (IS_ERR(dir_item)) अणु
		ret = PTR_ERR(dir_item);
		जाओ out;
	पूर्ण

	/*
	 * Our inode's dentry collides with the dentry of another inode which is
	 * in the log but not yet processed since it has a higher inode number.
	 * So delete that other dentry.
	 */
	btrfs_dir_item_key_to_cpu(path->nodes[0], dir_item, &key);
	btrfs_release_path(path);
	other_inode = पढ़ो_one_inode(root, key.objectid);
	अगर (!other_inode) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	ret = btrfs_unlink_inode(trans, root, BTRFS_I(dir), BTRFS_I(other_inode),
				 name, namelen);
	अगर (ret)
		जाओ out;
	/*
	 * If we dropped the link count to 0, bump it so that later the iput()
	 * on the inode will not मुक्त it. We will fixup the link count later.
	 */
	अगर (other_inode->i_nlink == 0)
		inc_nlink(other_inode);

	ret = btrfs_run_delayed_items(trans);
	अगर (ret)
		जाओ out;
add_link:
	ret = btrfs_add_link(trans, BTRFS_I(dir), BTRFS_I(inode),
			     name, namelen, 0, ref_index);
out:
	iput(other_inode);
	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

/*
 * replay one inode back reference item found in the log tree.
 * eb, slot and key refer to the buffer and key found in the log tree.
 * root is the destination we are replaying पूर्णांकo, and path is क्रम temp
 * use by this function.  (it should be released on वापस).
 */
अटल noअंतरभूत पूर्णांक add_inode_ref(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_root *root,
				  काष्ठा btrfs_root *log,
				  काष्ठा btrfs_path *path,
				  काष्ठा extent_buffer *eb, पूर्णांक slot,
				  काष्ठा btrfs_key *key)
अणु
	काष्ठा inode *dir = शून्य;
	काष्ठा inode *inode = शून्य;
	अचिन्हित दीर्घ ref_ptr;
	अचिन्हित दीर्घ ref_end;
	अक्षर *name = शून्य;
	पूर्णांक namelen;
	पूर्णांक ret;
	पूर्णांक search_करोne = 0;
	पूर्णांक log_ref_ver = 0;
	u64 parent_objectid;
	u64 inode_objectid;
	u64 ref_index = 0;
	पूर्णांक ref_काष्ठा_size;

	ref_ptr = btrfs_item_ptr_offset(eb, slot);
	ref_end = ref_ptr + btrfs_item_size_nr(eb, slot);

	अगर (key->type == BTRFS_INODE_EXTREF_KEY) अणु
		काष्ठा btrfs_inode_extref *r;

		ref_काष्ठा_size = माप(काष्ठा btrfs_inode_extref);
		log_ref_ver = 1;
		r = (काष्ठा btrfs_inode_extref *)ref_ptr;
		parent_objectid = btrfs_inode_extref_parent(eb, r);
	पूर्ण अन्यथा अणु
		ref_काष्ठा_size = माप(काष्ठा btrfs_inode_ref);
		parent_objectid = key->offset;
	पूर्ण
	inode_objectid = key->objectid;

	/*
	 * it is possible that we didn't log all the parent directories
	 * क्रम a given inode.  If we करोn't find the dir, just don't
	 * copy the back ref in.  The link count fixup code will take
	 * care of the rest
	 */
	dir = पढ़ो_one_inode(root, parent_objectid);
	अगर (!dir) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	inode = पढ़ो_one_inode(root, inode_objectid);
	अगर (!inode) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	जबतक (ref_ptr < ref_end) अणु
		अगर (log_ref_ver) अणु
			ret = extref_get_fields(eb, ref_ptr, &namelen, &name,
						&ref_index, &parent_objectid);
			/*
			 * parent object can change from one array
			 * item to another.
			 */
			अगर (!dir)
				dir = पढ़ो_one_inode(root, parent_objectid);
			अगर (!dir) अणु
				ret = -ENOENT;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = ref_get_fields(eb, ref_ptr, &namelen, &name,
					     &ref_index);
		पूर्ण
		अगर (ret)
			जाओ out;

		/* अगर we alपढ़ोy have a perfect match, we're करोne */
		अगर (!inode_in_dir(root, path, btrfs_ino(BTRFS_I(dir)),
					btrfs_ino(BTRFS_I(inode)), ref_index,
					name, namelen)) अणु
			/*
			 * look क्रम a conflicting back reference in the
			 * metadata. अगर we find one we have to unlink that name
			 * of the file beक्रमe we add our new link.  Later on, we
			 * overग_लिखो any existing back reference, and we करोn't
			 * want to create dangling poपूर्णांकers in the directory.
			 */

			अगर (!search_करोne) अणु
				ret = __add_inode_ref(trans, root, path, log,
						      BTRFS_I(dir),
						      BTRFS_I(inode),
						      inode_objectid,
						      parent_objectid,
						      ref_index, name, namelen,
						      &search_करोne);
				अगर (ret) अणु
					अगर (ret == 1)
						ret = 0;
					जाओ out;
				पूर्ण
			पूर्ण

			/*
			 * If a reference item alपढ़ोy exists क्रम this inode
			 * with the same parent and name, but dअगरferent index,
			 * drop it and the corresponding directory index entries
			 * from the parent beक्रमe adding the new reference item
			 * and dir index entries, otherwise we would fail with
			 * -EEXIST वापसed from btrfs_add_link() below.
			 */
			ret = btrfs_inode_ref_exists(inode, dir, key->type,
						     name, namelen);
			अगर (ret > 0) अणु
				ret = btrfs_unlink_inode(trans, root,
							 BTRFS_I(dir),
							 BTRFS_I(inode),
							 name, namelen);
				/*
				 * If we dropped the link count to 0, bump it so
				 * that later the iput() on the inode will not
				 * मुक्त it. We will fixup the link count later.
				 */
				अगर (!ret && inode->i_nlink == 0)
					inc_nlink(inode);
			पूर्ण
			अगर (ret < 0)
				जाओ out;

			/* insert our name */
			ret = add_link(trans, root, dir, inode, name, namelen,
				       ref_index);
			अगर (ret)
				जाओ out;

			ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
			अगर (ret)
				जाओ out;
		पूर्ण

		ref_ptr = (अचिन्हित दीर्घ)(ref_ptr + ref_काष्ठा_size) + namelen;
		kमुक्त(name);
		name = शून्य;
		अगर (log_ref_ver) अणु
			iput(dir);
			dir = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * Beक्रमe we overग_लिखो the inode reference item in the subvolume tree
	 * with the item from the log tree, we must unlink all names from the
	 * parent directory that are in the subvolume's tree inode reference
	 * item, otherwise we end up with an inconsistent subvolume tree where
	 * dir index entries exist क्रम a name but there is no inode reference
	 * item with the same name.
	 */
	ret = unlink_old_inode_refs(trans, root, path, BTRFS_I(inode), eb, slot,
				    key);
	अगर (ret)
		जाओ out;

	/* finally ग_लिखो the back reference in the inode */
	ret = overग_लिखो_item(trans, root, path, eb, slot, key);
out:
	btrfs_release_path(path);
	kमुक्त(name);
	iput(dir);
	iput(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक count_inode_extrefs(काष्ठा btrfs_root *root,
		काष्ठा btrfs_inode *inode, काष्ठा btrfs_path *path)
अणु
	पूर्णांक ret = 0;
	पूर्णांक name_len;
	अचिन्हित पूर्णांक nlink = 0;
	u32 item_size;
	u32 cur_offset = 0;
	u64 inode_objectid = btrfs_ino(inode);
	u64 offset = 0;
	अचिन्हित दीर्घ ptr;
	काष्ठा btrfs_inode_extref *extref;
	काष्ठा extent_buffer *leaf;

	जबतक (1) अणु
		ret = btrfs_find_one_extref(root, inode_objectid, offset, path,
					    &extref, &offset);
		अगर (ret)
			अवरोध;

		leaf = path->nodes[0];
		item_size = btrfs_item_size_nr(leaf, path->slots[0]);
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		cur_offset = 0;

		जबतक (cur_offset < item_size) अणु
			extref = (काष्ठा btrfs_inode_extref *) (ptr + cur_offset);
			name_len = btrfs_inode_extref_name_len(leaf, extref);

			nlink++;

			cur_offset += name_len + माप(*extref);
		पूर्ण

		offset++;
		btrfs_release_path(path);
	पूर्ण
	btrfs_release_path(path);

	अगर (ret < 0 && ret != -ENOENT)
		वापस ret;
	वापस nlink;
पूर्ण

अटल पूर्णांक count_inode_refs(काष्ठा btrfs_root *root,
			काष्ठा btrfs_inode *inode, काष्ठा btrfs_path *path)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	अचिन्हित पूर्णांक nlink = 0;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ ptr_end;
	पूर्णांक name_len;
	u64 ino = btrfs_ino(inode);

	key.objectid = ino;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = (u64)-1;

	जबतक (1) अणु
		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0)
			अवरोध;
		अगर (ret > 0) अणु
			अगर (path->slots[0] == 0)
				अवरोध;
			path->slots[0]--;
		पूर्ण
process_slot:
		btrfs_item_key_to_cpu(path->nodes[0], &key,
				      path->slots[0]);
		अगर (key.objectid != ino ||
		    key.type != BTRFS_INODE_REF_KEY)
			अवरोध;
		ptr = btrfs_item_ptr_offset(path->nodes[0], path->slots[0]);
		ptr_end = ptr + btrfs_item_size_nr(path->nodes[0],
						   path->slots[0]);
		जबतक (ptr < ptr_end) अणु
			काष्ठा btrfs_inode_ref *ref;

			ref = (काष्ठा btrfs_inode_ref *)ptr;
			name_len = btrfs_inode_ref_name_len(path->nodes[0],
							    ref);
			ptr = (अचिन्हित दीर्घ)(ref + 1) + name_len;
			nlink++;
		पूर्ण

		अगर (key.offset == 0)
			अवरोध;
		अगर (path->slots[0] > 0) अणु
			path->slots[0]--;
			जाओ process_slot;
		पूर्ण
		key.offset--;
		btrfs_release_path(path);
	पूर्ण
	btrfs_release_path(path);

	वापस nlink;
पूर्ण

/*
 * There are a few corners where the link count of the file can't
 * be properly मुख्यtained during replay.  So, instead of adding
 * lots of complनिकासy to the log code, we just scan the backrefs
 * क्रम any file that has been through replay.
 *
 * The scan will update the link count on the inode to reflect the
 * number of back refs found.  If it goes करोwn to zero, the iput
 * will मुक्त the inode.
 */
अटल noअंतरभूत पूर्णांक fixup_inode_link_count(काष्ठा btrfs_trans_handle *trans,
					   काष्ठा btrfs_root *root,
					   काष्ठा inode *inode)
अणु
	काष्ठा btrfs_path *path;
	पूर्णांक ret;
	u64 nlink = 0;
	u64 ino = btrfs_ino(BTRFS_I(inode));

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = count_inode_refs(root, BTRFS_I(inode), path);
	अगर (ret < 0)
		जाओ out;

	nlink = ret;

	ret = count_inode_extrefs(root, BTRFS_I(inode), path);
	अगर (ret < 0)
		जाओ out;

	nlink += ret;

	ret = 0;

	अगर (nlink != inode->i_nlink) अणु
		set_nlink(inode, nlink);
		ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
		अगर (ret)
			जाओ out;
	पूर्ण
	BTRFS_I(inode)->index_cnt = (u64)-1;

	अगर (inode->i_nlink == 0) अणु
		अगर (S_ISसूची(inode->i_mode)) अणु
			ret = replay_dir_deletes(trans, root, शून्य, path,
						 ino, 1);
			अगर (ret)
				जाओ out;
		पूर्ण
		ret = btrfs_insert_orphan_item(trans, root, ino);
		अगर (ret == -EEXIST)
			ret = 0;
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक fixup_inode_link_counts(काष्ठा btrfs_trans_handle *trans,
					    काष्ठा btrfs_root *root,
					    काष्ठा btrfs_path *path)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	काष्ठा inode *inode;

	key.objectid = BTRFS_TREE_LOG_FIXUP_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = (u64)-1;
	जबतक (1) अणु
		ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
		अगर (ret < 0)
			अवरोध;

		अगर (ret == 1) अणु
			ret = 0;
			अगर (path->slots[0] == 0)
				अवरोध;
			path->slots[0]--;
		पूर्ण

		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
		अगर (key.objectid != BTRFS_TREE_LOG_FIXUP_OBJECTID ||
		    key.type != BTRFS_ORPHAN_ITEM_KEY)
			अवरोध;

		ret = btrfs_del_item(trans, root, path);
		अगर (ret)
			अवरोध;

		btrfs_release_path(path);
		inode = पढ़ो_one_inode(root, key.offset);
		अगर (!inode) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण

		ret = fixup_inode_link_count(trans, root, inode);
		iput(inode);
		अगर (ret)
			अवरोध;

		/*
		 * fixup on a directory may create new entries,
		 * make sure we always look क्रम the highset possible
		 * offset
		 */
		key.offset = (u64)-1;
	पूर्ण
	btrfs_release_path(path);
	वापस ret;
पूर्ण


/*
 * record a given inode in the fixup dir so we can check its link
 * count when replay is करोne.  The link count is incremented here
 * so the inode won't go away until we check it
 */
अटल noअंतरभूत पूर्णांक link_to_fixup_dir(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_root *root,
				      काष्ठा btrfs_path *path,
				      u64 objectid)
अणु
	काष्ठा btrfs_key key;
	पूर्णांक ret = 0;
	काष्ठा inode *inode;

	inode = पढ़ो_one_inode(root, objectid);
	अगर (!inode)
		वापस -EIO;

	key.objectid = BTRFS_TREE_LOG_FIXUP_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = objectid;

	ret = btrfs_insert_empty_item(trans, root, path, &key, 0);

	btrfs_release_path(path);
	अगर (ret == 0) अणु
		अगर (!inode->i_nlink)
			set_nlink(inode, 1);
		अन्यथा
			inc_nlink(inode);
		ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	पूर्ण अन्यथा अगर (ret == -EEXIST) अणु
		ret = 0;
	पूर्ण
	iput(inode);

	वापस ret;
पूर्ण

/*
 * when replaying the log क्रम a directory, we only insert names
 * क्रम inodes that actually exist.  This means an fsync on a directory
 * करोes not implicitly fsync all the new files in it
 */
अटल noअंतरभूत पूर्णांक insert_one_name(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_root *root,
				    u64 dirid, u64 index,
				    अक्षर *name, पूर्णांक name_len,
				    काष्ठा btrfs_key *location)
अणु
	काष्ठा inode *inode;
	काष्ठा inode *dir;
	पूर्णांक ret;

	inode = पढ़ो_one_inode(root, location->objectid);
	अगर (!inode)
		वापस -ENOENT;

	dir = पढ़ो_one_inode(root, dirid);
	अगर (!dir) अणु
		iput(inode);
		वापस -EIO;
	पूर्ण

	ret = btrfs_add_link(trans, BTRFS_I(dir), BTRFS_I(inode), name,
			name_len, 1, index);

	/* FIXME, put inode पूर्णांकo FIXUP list */

	iput(inode);
	iput(dir);
	वापस ret;
पूर्ण

/*
 * take a single entry in a log directory item and replay it पूर्णांकo
 * the subvolume.
 *
 * अगर a conflicting item exists in the subdirectory alपढ़ोy,
 * the inode it poपूर्णांकs to is unlinked and put पूर्णांकo the link count
 * fix up tree.
 *
 * If a name from the log poपूर्णांकs to a file or directory that करोes
 * not exist in the FS, it is skipped.  fsyncs on directories
 * करो not क्रमce करोwn inodes inside that directory, just changes to the
 * names or unlinks in a directory.
 *
 * Returns < 0 on error, 0 अगर the name wasn't replayed (dentry poपूर्णांकs to a
 * non-existing inode) and 1 अगर the name was replayed.
 */
अटल noअंतरभूत पूर्णांक replay_one_name(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_root *root,
				    काष्ठा btrfs_path *path,
				    काष्ठा extent_buffer *eb,
				    काष्ठा btrfs_dir_item *di,
				    काष्ठा btrfs_key *key)
अणु
	अक्षर *name;
	पूर्णांक name_len;
	काष्ठा btrfs_dir_item *dst_di;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_key log_key;
	काष्ठा inode *dir;
	u8 log_type;
	पूर्णांक exists;
	पूर्णांक ret = 0;
	bool update_size = (key->type == BTRFS_सूची_INDEX_KEY);
	bool name_added = false;

	dir = पढ़ो_one_inode(root, key->objectid);
	अगर (!dir)
		वापस -EIO;

	name_len = btrfs_dir_name_len(eb, di);
	name = kदो_स्मृति(name_len, GFP_NOFS);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	log_type = btrfs_dir_type(eb, di);
	पढ़ो_extent_buffer(eb, name, (अचिन्हित दीर्घ)(di + 1),
		   name_len);

	btrfs_dir_item_key_to_cpu(eb, di, &log_key);
	exists = btrfs_lookup_inode(trans, root, path, &log_key, 0);
	अगर (exists == 0)
		exists = 1;
	अन्यथा
		exists = 0;
	btrfs_release_path(path);

	अगर (key->type == BTRFS_सूची_ITEM_KEY) अणु
		dst_di = btrfs_lookup_dir_item(trans, root, path, key->objectid,
				       name, name_len, 1);
	पूर्ण अन्यथा अगर (key->type == BTRFS_सूची_INDEX_KEY) अणु
		dst_di = btrfs_lookup_dir_index_item(trans, root, path,
						     key->objectid,
						     key->offset, name,
						     name_len, 1);
	पूर्ण अन्यथा अणु
		/* Corruption */
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (IS_ERR_OR_शून्य(dst_di)) अणु
		/* we need a sequence number to insert, so we only
		 * करो inserts क्रम the BTRFS_सूची_INDEX_KEY types
		 */
		अगर (key->type != BTRFS_सूची_INDEX_KEY)
			जाओ out;
		जाओ insert;
	पूर्ण

	btrfs_dir_item_key_to_cpu(path->nodes[0], dst_di, &found_key);
	/* the existing item matches the logged item */
	अगर (found_key.objectid == log_key.objectid &&
	    found_key.type == log_key.type &&
	    found_key.offset == log_key.offset &&
	    btrfs_dir_type(path->nodes[0], dst_di) == log_type) अणु
		update_size = false;
		जाओ out;
	पूर्ण

	/*
	 * करोn't drop the conflicting directory entry अगर the inode
	 * क्रम the new entry करोesn't exist
	 */
	अगर (!exists)
		जाओ out;

	ret = drop_one_dir_item(trans, root, path, BTRFS_I(dir), dst_di);
	अगर (ret)
		जाओ out;

	अगर (key->type == BTRFS_सूची_INDEX_KEY)
		जाओ insert;
out:
	btrfs_release_path(path);
	अगर (!ret && update_size) अणु
		btrfs_i_size_ग_लिखो(BTRFS_I(dir), dir->i_size + name_len * 2);
		ret = btrfs_update_inode(trans, root, BTRFS_I(dir));
	पूर्ण
	kमुक्त(name);
	iput(dir);
	अगर (!ret && name_added)
		ret = 1;
	वापस ret;

insert:
	/*
	 * Check अगर the inode reference exists in the log क्रम the given name,
	 * inode and parent inode
	 */
	found_key.objectid = log_key.objectid;
	found_key.type = BTRFS_INODE_REF_KEY;
	found_key.offset = key->objectid;
	ret = backref_in_log(root->log_root, &found_key, 0, name, name_len);
	अगर (ret < 0) अणु
	        जाओ out;
	पूर्ण अन्यथा अगर (ret) अणु
	        /* The dentry will be added later. */
	        ret = 0;
	        update_size = false;
	        जाओ out;
	पूर्ण

	found_key.objectid = log_key.objectid;
	found_key.type = BTRFS_INODE_EXTREF_KEY;
	found_key.offset = key->objectid;
	ret = backref_in_log(root->log_root, &found_key, key->objectid, name,
			     name_len);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (ret) अणु
		/* The dentry will be added later. */
		ret = 0;
		update_size = false;
		जाओ out;
	पूर्ण
	btrfs_release_path(path);
	ret = insert_one_name(trans, root, key->objectid, key->offset,
			      name, name_len, &log_key);
	अगर (ret && ret != -ENOENT && ret != -EEXIST)
		जाओ out;
	अगर (!ret)
		name_added = true;
	update_size = false;
	ret = 0;
	जाओ out;
पूर्ण

/*
 * find all the names in a directory item and reconcile them पूर्णांकo
 * the subvolume.  Only BTRFS_सूची_ITEM_KEY types will have more than
 * one name in a directory item, but the same code माला_लो used क्रम
 * both directory index types
 */
अटल noअंतरभूत पूर्णांक replay_one_dir_item(काष्ठा btrfs_trans_handle *trans,
					काष्ठा btrfs_root *root,
					काष्ठा btrfs_path *path,
					काष्ठा extent_buffer *eb, पूर्णांक slot,
					काष्ठा btrfs_key *key)
अणु
	पूर्णांक ret = 0;
	u32 item_size = btrfs_item_size_nr(eb, slot);
	काष्ठा btrfs_dir_item *di;
	पूर्णांक name_len;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ ptr_end;
	काष्ठा btrfs_path *fixup_path = शून्य;

	ptr = btrfs_item_ptr_offset(eb, slot);
	ptr_end = ptr + item_size;
	जबतक (ptr < ptr_end) अणु
		di = (काष्ठा btrfs_dir_item *)ptr;
		name_len = btrfs_dir_name_len(eb, di);
		ret = replay_one_name(trans, root, path, eb, di, key);
		अगर (ret < 0)
			अवरोध;
		ptr = (अचिन्हित दीर्घ)(di + 1);
		ptr += name_len;

		/*
		 * If this entry refers to a non-directory (directories can not
		 * have a link count > 1) and it was added in the transaction
		 * that was not committed, make sure we fixup the link count of
		 * the inode it the entry poपूर्णांकs to. Otherwise something like
		 * the following would result in a directory poपूर्णांकing to an
		 * inode with a wrong link that करोes not account क्रम this dir
		 * entry:
		 *
		 * सूची_गढ़ो testdir
		 * touch testdir/foo
		 * touch testdir/bar
		 * sync
		 *
		 * ln testdir/bar testdir/bar_link
		 * ln testdir/foo testdir/foo_link
		 * xfs_io -c "fsync" testdir/bar
		 *
		 * <घातer failure>
		 *
		 * mount fs, log replay happens
		 *
		 * File foo would reमुख्य with a link count of 1 when it has two
		 * entries poपूर्णांकing to it in the directory testdir. This would
		 * make it impossible to ever delete the parent directory has
		 * it would result in stale dentries that can never be deleted.
		 */
		अगर (ret == 1 && btrfs_dir_type(eb, di) != BTRFS_FT_सूची) अणु
			काष्ठा btrfs_key di_key;

			अगर (!fixup_path) अणु
				fixup_path = btrfs_alloc_path();
				अगर (!fixup_path) अणु
					ret = -ENOMEM;
					अवरोध;
				पूर्ण
			पूर्ण

			btrfs_dir_item_key_to_cpu(eb, di, &di_key);
			ret = link_to_fixup_dir(trans, root, fixup_path,
						di_key.objectid);
			अगर (ret)
				अवरोध;
		पूर्ण
		ret = 0;
	पूर्ण
	btrfs_मुक्त_path(fixup_path);
	वापस ret;
पूर्ण

/*
 * directory replay has two parts.  There are the standard directory
 * items in the log copied from the subvolume, and range items
 * created in the log जबतक the subvolume was logged.
 *
 * The range items tell us which parts of the key space the log
 * is authoritative क्रम.  During replay, अगर a key in the subvolume
 * directory is in a logged range item, but not actually in the log
 * that means it was deleted from the directory beक्रमe the fsync
 * and should be हटाओd.
 */
अटल noअंतरभूत पूर्णांक find_dir_range(काष्ठा btrfs_root *root,
				   काष्ठा btrfs_path *path,
				   u64 dirid, पूर्णांक key_type,
				   u64 *start_ret, u64 *end_ret)
अणु
	काष्ठा btrfs_key key;
	u64 found_end;
	काष्ठा btrfs_dir_log_item *item;
	पूर्णांक ret;
	पूर्णांक nritems;

	अगर (*start_ret == (u64)-1)
		वापस 1;

	key.objectid = dirid;
	key.type = key_type;
	key.offset = *start_ret;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0) अणु
		अगर (path->slots[0] == 0)
			जाओ out;
		path->slots[0]--;
	पूर्ण
	अगर (ret != 0)
		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);

	अगर (key.type != key_type || key.objectid != dirid) अणु
		ret = 1;
		जाओ next;
	पूर्ण
	item = btrfs_item_ptr(path->nodes[0], path->slots[0],
			      काष्ठा btrfs_dir_log_item);
	found_end = btrfs_dir_log_end(path->nodes[0], item);

	अगर (*start_ret >= key.offset && *start_ret <= found_end) अणु
		ret = 0;
		*start_ret = key.offset;
		*end_ret = found_end;
		जाओ out;
	पूर्ण
	ret = 1;
next:
	/* check the next slot in the tree to see अगर it is a valid item */
	nritems = btrfs_header_nritems(path->nodes[0]);
	path->slots[0]++;
	अगर (path->slots[0] >= nritems) अणु
		ret = btrfs_next_leaf(root, path);
		अगर (ret)
			जाओ out;
	पूर्ण

	btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);

	अगर (key.type != key_type || key.objectid != dirid) अणु
		ret = 1;
		जाओ out;
	पूर्ण
	item = btrfs_item_ptr(path->nodes[0], path->slots[0],
			      काष्ठा btrfs_dir_log_item);
	found_end = btrfs_dir_log_end(path->nodes[0], item);
	*start_ret = key.offset;
	*end_ret = found_end;
	ret = 0;
out:
	btrfs_release_path(path);
	वापस ret;
पूर्ण

/*
 * this looks क्रम a given directory item in the log.  If the directory
 * item is not in the log, the item is हटाओd and the inode it poपूर्णांकs
 * to is unlinked
 */
अटल noअंतरभूत पूर्णांक check_item_in_log(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_root *root,
				      काष्ठा btrfs_root *log,
				      काष्ठा btrfs_path *path,
				      काष्ठा btrfs_path *log_path,
				      काष्ठा inode *dir,
				      काष्ठा btrfs_key *dir_key)
अणु
	पूर्णांक ret;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;
	u32 item_size;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_dir_item *log_di;
	पूर्णांक name_len;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ ptr_end;
	अक्षर *name;
	काष्ठा inode *inode;
	काष्ठा btrfs_key location;

again:
	eb = path->nodes[0];
	slot = path->slots[0];
	item_size = btrfs_item_size_nr(eb, slot);
	ptr = btrfs_item_ptr_offset(eb, slot);
	ptr_end = ptr + item_size;
	जबतक (ptr < ptr_end) अणु
		di = (काष्ठा btrfs_dir_item *)ptr;
		name_len = btrfs_dir_name_len(eb, di);
		name = kदो_स्मृति(name_len, GFP_NOFS);
		अगर (!name) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		पढ़ो_extent_buffer(eb, name, (अचिन्हित दीर्घ)(di + 1),
				  name_len);
		log_di = शून्य;
		अगर (log && dir_key->type == BTRFS_सूची_ITEM_KEY) अणु
			log_di = btrfs_lookup_dir_item(trans, log, log_path,
						       dir_key->objectid,
						       name, name_len, 0);
		पूर्ण अन्यथा अगर (log && dir_key->type == BTRFS_सूची_INDEX_KEY) अणु
			log_di = btrfs_lookup_dir_index_item(trans, log,
						     log_path,
						     dir_key->objectid,
						     dir_key->offset,
						     name, name_len, 0);
		पूर्ण
		अगर (!log_di || log_di == ERR_PTR(-ENOENT)) अणु
			btrfs_dir_item_key_to_cpu(eb, di, &location);
			btrfs_release_path(path);
			btrfs_release_path(log_path);
			inode = पढ़ो_one_inode(root, location.objectid);
			अगर (!inode) अणु
				kमुक्त(name);
				वापस -EIO;
			पूर्ण

			ret = link_to_fixup_dir(trans, root,
						path, location.objectid);
			अगर (ret) अणु
				kमुक्त(name);
				iput(inode);
				जाओ out;
			पूर्ण

			inc_nlink(inode);
			ret = btrfs_unlink_inode(trans, root, BTRFS_I(dir),
					BTRFS_I(inode), name, name_len);
			अगर (!ret)
				ret = btrfs_run_delayed_items(trans);
			kमुक्त(name);
			iput(inode);
			अगर (ret)
				जाओ out;

			/* there might still be more names under this key
			 * check and repeat अगर required
			 */
			ret = btrfs_search_slot(शून्य, root, dir_key, path,
						0, 0);
			अगर (ret == 0)
				जाओ again;
			ret = 0;
			जाओ out;
		पूर्ण अन्यथा अगर (IS_ERR(log_di)) अणु
			kमुक्त(name);
			वापस PTR_ERR(log_di);
		पूर्ण
		btrfs_release_path(log_path);
		kमुक्त(name);

		ptr = (अचिन्हित दीर्घ)(di + 1);
		ptr += name_len;
	पूर्ण
	ret = 0;
out:
	btrfs_release_path(path);
	btrfs_release_path(log_path);
	वापस ret;
पूर्ण

अटल पूर्णांक replay_xattr_deletes(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_root *root,
			      काष्ठा btrfs_root *log,
			      काष्ठा btrfs_path *path,
			      स्थिर u64 ino)
अणु
	काष्ठा btrfs_key search_key;
	काष्ठा btrfs_path *log_path;
	पूर्णांक i;
	पूर्णांक nritems;
	पूर्णांक ret;

	log_path = btrfs_alloc_path();
	अगर (!log_path)
		वापस -ENOMEM;

	search_key.objectid = ino;
	search_key.type = BTRFS_XATTR_ITEM_KEY;
	search_key.offset = 0;
again:
	ret = btrfs_search_slot(शून्य, root, &search_key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
process_leaf:
	nritems = btrfs_header_nritems(path->nodes[0]);
	क्रम (i = path->slots[0]; i < nritems; i++) अणु
		काष्ठा btrfs_key key;
		काष्ठा btrfs_dir_item *di;
		काष्ठा btrfs_dir_item *log_di;
		u32 total_size;
		u32 cur;

		btrfs_item_key_to_cpu(path->nodes[0], &key, i);
		अगर (key.objectid != ino || key.type != BTRFS_XATTR_ITEM_KEY) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		di = btrfs_item_ptr(path->nodes[0], i, काष्ठा btrfs_dir_item);
		total_size = btrfs_item_size_nr(path->nodes[0], i);
		cur = 0;
		जबतक (cur < total_size) अणु
			u16 name_len = btrfs_dir_name_len(path->nodes[0], di);
			u16 data_len = btrfs_dir_data_len(path->nodes[0], di);
			u32 this_len = माप(*di) + name_len + data_len;
			अक्षर *name;

			name = kदो_स्मृति(name_len, GFP_NOFS);
			अगर (!name) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			पढ़ो_extent_buffer(path->nodes[0], name,
					   (अचिन्हित दीर्घ)(di + 1), name_len);

			log_di = btrfs_lookup_xattr(शून्य, log, log_path, ino,
						    name, name_len, 0);
			btrfs_release_path(log_path);
			अगर (!log_di) अणु
				/* Doesn't exist in log tree, so delete it. */
				btrfs_release_path(path);
				di = btrfs_lookup_xattr(trans, root, path, ino,
							name, name_len, -1);
				kमुक्त(name);
				अगर (IS_ERR(di)) अणु
					ret = PTR_ERR(di);
					जाओ out;
				पूर्ण
				ASSERT(di);
				ret = btrfs_delete_one_dir_name(trans, root,
								path, di);
				अगर (ret)
					जाओ out;
				btrfs_release_path(path);
				search_key = key;
				जाओ again;
			पूर्ण
			kमुक्त(name);
			अगर (IS_ERR(log_di)) अणु
				ret = PTR_ERR(log_di);
				जाओ out;
			पूर्ण
			cur += this_len;
			di = (काष्ठा btrfs_dir_item *)((अक्षर *)di + this_len);
		पूर्ण
	पूर्ण
	ret = btrfs_next_leaf(root, path);
	अगर (ret > 0)
		ret = 0;
	अन्यथा अगर (ret == 0)
		जाओ process_leaf;
out:
	btrfs_मुक्त_path(log_path);
	btrfs_release_path(path);
	वापस ret;
पूर्ण


/*
 * deletion replay happens beक्रमe we copy any new directory items
 * out of the log or out of backreferences from inodes.  It
 * scans the log to find ranges of keys that log is authoritative क्रम,
 * and then scans the directory to find items in those ranges that are
 * not present in the log.
 *
 * Anything we करोn't find in the log is unlinked and हटाओd from the
 * directory.
 */
अटल noअंतरभूत पूर्णांक replay_dir_deletes(काष्ठा btrfs_trans_handle *trans,
				       काष्ठा btrfs_root *root,
				       काष्ठा btrfs_root *log,
				       काष्ठा btrfs_path *path,
				       u64 dirid, पूर्णांक del_all)
अणु
	u64 range_start;
	u64 range_end;
	पूर्णांक key_type = BTRFS_सूची_LOG_ITEM_KEY;
	पूर्णांक ret = 0;
	काष्ठा btrfs_key dir_key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_path *log_path;
	काष्ठा inode *dir;

	dir_key.objectid = dirid;
	dir_key.type = BTRFS_सूची_ITEM_KEY;
	log_path = btrfs_alloc_path();
	अगर (!log_path)
		वापस -ENOMEM;

	dir = पढ़ो_one_inode(root, dirid);
	/* it isn't an error if the inode isn't there, that can happen
	 * because we replay the deletes beक्रमe we copy in the inode item
	 * from the log
	 */
	अगर (!dir) अणु
		btrfs_मुक्त_path(log_path);
		वापस 0;
	पूर्ण
again:
	range_start = 0;
	range_end = 0;
	जबतक (1) अणु
		अगर (del_all)
			range_end = (u64)-1;
		अन्यथा अणु
			ret = find_dir_range(log, path, dirid, key_type,
					     &range_start, &range_end);
			अगर (ret != 0)
				अवरोध;
		पूर्ण

		dir_key.offset = range_start;
		जबतक (1) अणु
			पूर्णांक nritems;
			ret = btrfs_search_slot(शून्य, root, &dir_key, path,
						0, 0);
			अगर (ret < 0)
				जाओ out;

			nritems = btrfs_header_nritems(path->nodes[0]);
			अगर (path->slots[0] >= nritems) अणु
				ret = btrfs_next_leaf(root, path);
				अगर (ret == 1)
					अवरोध;
				अन्यथा अगर (ret < 0)
					जाओ out;
			पूर्ण
			btrfs_item_key_to_cpu(path->nodes[0], &found_key,
					      path->slots[0]);
			अगर (found_key.objectid != dirid ||
			    found_key.type != dir_key.type)
				जाओ next_type;

			अगर (found_key.offset > range_end)
				अवरोध;

			ret = check_item_in_log(trans, root, log, path,
						log_path, dir,
						&found_key);
			अगर (ret)
				जाओ out;
			अगर (found_key.offset == (u64)-1)
				अवरोध;
			dir_key.offset = found_key.offset + 1;
		पूर्ण
		btrfs_release_path(path);
		अगर (range_end == (u64)-1)
			अवरोध;
		range_start = range_end + 1;
	पूर्ण

next_type:
	ret = 0;
	अगर (key_type == BTRFS_सूची_LOG_ITEM_KEY) अणु
		key_type = BTRFS_सूची_LOG_INDEX_KEY;
		dir_key.type = BTRFS_सूची_INDEX_KEY;
		btrfs_release_path(path);
		जाओ again;
	पूर्ण
out:
	btrfs_release_path(path);
	btrfs_मुक्त_path(log_path);
	iput(dir);
	वापस ret;
पूर्ण

/*
 * the process_func used to replay items from the log tree.  This
 * माला_लो called in two dअगरferent stages.  The first stage just looks
 * क्रम inodes and makes sure they are all copied पूर्णांकo the subvolume.
 *
 * The second stage copies all the other item types from the log पूर्णांकo
 * the subvolume.  The two stage approach is slower, but माला_लो rid of
 * lots of complनिकासy around inodes referencing other inodes that exist
 * only in the log (references come from either directory items or inode
 * back refs).
 */
अटल पूर्णांक replay_one_buffer(काष्ठा btrfs_root *log, काष्ठा extent_buffer *eb,
			     काष्ठा walk_control *wc, u64 gen, पूर्णांक level)
अणु
	पूर्णांक nritems;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *root = wc->replay_dest;
	काष्ठा btrfs_key key;
	पूर्णांक i;
	पूर्णांक ret;

	ret = btrfs_पढ़ो_buffer(eb, gen, level, शून्य);
	अगर (ret)
		वापस ret;

	level = btrfs_header_level(eb);

	अगर (level != 0)
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	nritems = btrfs_header_nritems(eb);
	क्रम (i = 0; i < nritems; i++) अणु
		btrfs_item_key_to_cpu(eb, &key, i);

		/* inode keys are करोne during the first stage */
		अगर (key.type == BTRFS_INODE_ITEM_KEY &&
		    wc->stage == LOG_WALK_REPLAY_INODES) अणु
			काष्ठा btrfs_inode_item *inode_item;
			u32 mode;

			inode_item = btrfs_item_ptr(eb, i,
					    काष्ठा btrfs_inode_item);
			/*
			 * If we have a क्षणिक_ख (O_TMPखाता) that got fsync'ed
			 * and never got linked beक्रमe the fsync, skip it, as
			 * replaying it is poपूर्णांकless since it would be deleted
			 * later. We skip logging क्षणिक_खs, but it's always
			 * possible we are replaying a log created with a kernel
			 * that used to log क्षणिक_खs.
			 */
			अगर (btrfs_inode_nlink(eb, inode_item) == 0) अणु
				wc->ignore_cur_inode = true;
				जारी;
			पूर्ण अन्यथा अणु
				wc->ignore_cur_inode = false;
			पूर्ण
			ret = replay_xattr_deletes(wc->trans, root, log,
						   path, key.objectid);
			अगर (ret)
				अवरोध;
			mode = btrfs_inode_mode(eb, inode_item);
			अगर (S_ISसूची(mode)) अणु
				ret = replay_dir_deletes(wc->trans,
					 root, log, path, key.objectid, 0);
				अगर (ret)
					अवरोध;
			पूर्ण
			ret = overग_लिखो_item(wc->trans, root, path,
					     eb, i, &key);
			अगर (ret)
				अवरोध;

			/*
			 * Beक्रमe replaying extents, truncate the inode to its
			 * size. We need to करो it now and not after log replay
			 * because beक्रमe an fsync we can have pपुनः_स्मृति extents
			 * added beyond the inode's i_size. If we did it after,
			 * through orphan cleanup क्रम example, we would drop
			 * those pपुनः_स्मृति extents just after replaying them.
			 */
			अगर (S_ISREG(mode)) अणु
				काष्ठा btrfs_drop_extents_args drop_args = अणु 0 पूर्ण;
				काष्ठा inode *inode;
				u64 from;

				inode = पढ़ो_one_inode(root, key.objectid);
				अगर (!inode) अणु
					ret = -EIO;
					अवरोध;
				पूर्ण
				from = ALIGN(i_size_पढ़ो(inode),
					     root->fs_info->sectorsize);
				drop_args.start = from;
				drop_args.end = (u64)-1;
				drop_args.drop_cache = true;
				ret = btrfs_drop_extents(wc->trans, root,
							 BTRFS_I(inode),
							 &drop_args);
				अगर (!ret) अणु
					inode_sub_bytes(inode,
							drop_args.bytes_found);
					/* Update the inode's nbytes. */
					ret = btrfs_update_inode(wc->trans,
							root, BTRFS_I(inode));
				पूर्ण
				iput(inode);
				अगर (ret)
					अवरोध;
			पूर्ण

			ret = link_to_fixup_dir(wc->trans, root,
						path, key.objectid);
			अगर (ret)
				अवरोध;
		पूर्ण

		अगर (wc->ignore_cur_inode)
			जारी;

		अगर (key.type == BTRFS_सूची_INDEX_KEY &&
		    wc->stage == LOG_WALK_REPLAY_सूची_INDEX) अणु
			ret = replay_one_dir_item(wc->trans, root, path,
						  eb, i, &key);
			अगर (ret)
				अवरोध;
		पूर्ण

		अगर (wc->stage < LOG_WALK_REPLAY_ALL)
			जारी;

		/* these keys are simply copied */
		अगर (key.type == BTRFS_XATTR_ITEM_KEY) अणु
			ret = overग_लिखो_item(wc->trans, root, path,
					     eb, i, &key);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अगर (key.type == BTRFS_INODE_REF_KEY ||
			   key.type == BTRFS_INODE_EXTREF_KEY) अणु
			ret = add_inode_ref(wc->trans, root, log, path,
					    eb, i, &key);
			अगर (ret && ret != -ENOENT)
				अवरोध;
			ret = 0;
		पूर्ण अन्यथा अगर (key.type == BTRFS_EXTENT_DATA_KEY) अणु
			ret = replay_one_extent(wc->trans, root, path,
						eb, i, &key);
			अगर (ret)
				अवरोध;
		पूर्ण अन्यथा अगर (key.type == BTRFS_सूची_ITEM_KEY) अणु
			ret = replay_one_dir_item(wc->trans, root, path,
						  eb, i, &key);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Correctly adjust the reserved bytes occupied by a log tree extent buffer
 */
अटल व्योम unaccount_log_buffer(काष्ठा btrfs_fs_info *fs_info, u64 start)
अणु
	काष्ठा btrfs_block_group *cache;

	cache = btrfs_lookup_block_group(fs_info, start);
	अगर (!cache) अणु
		btrfs_err(fs_info, "unable to find block group for %llu", start);
		वापस;
	पूर्ण

	spin_lock(&cache->space_info->lock);
	spin_lock(&cache->lock);
	cache->reserved -= fs_info->nodesize;
	cache->space_info->bytes_reserved -= fs_info->nodesize;
	spin_unlock(&cache->lock);
	spin_unlock(&cache->space_info->lock);

	btrfs_put_block_group(cache);
पूर्ण

अटल noअंतरभूत पूर्णांक walk_करोwn_log_tree(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_root *root,
				   काष्ठा btrfs_path *path, पूर्णांक *level,
				   काष्ठा walk_control *wc)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 bytenr;
	u64 ptr_gen;
	काष्ठा extent_buffer *next;
	काष्ठा extent_buffer *cur;
	u32 blocksize;
	पूर्णांक ret = 0;

	जबतक (*level > 0) अणु
		काष्ठा btrfs_key first_key;

		cur = path->nodes[*level];

		WARN_ON(btrfs_header_level(cur) != *level);

		अगर (path->slots[*level] >=
		    btrfs_header_nritems(cur))
			अवरोध;

		bytenr = btrfs_node_blockptr(cur, path->slots[*level]);
		ptr_gen = btrfs_node_ptr_generation(cur, path->slots[*level]);
		btrfs_node_key_to_cpu(cur, &first_key, path->slots[*level]);
		blocksize = fs_info->nodesize;

		next = btrfs_find_create_tree_block(fs_info, bytenr,
						    btrfs_header_owner(cur),
						    *level - 1);
		अगर (IS_ERR(next))
			वापस PTR_ERR(next);

		अगर (*level == 1) अणु
			ret = wc->process_func(root, next, wc, ptr_gen,
					       *level - 1);
			अगर (ret) अणु
				मुक्त_extent_buffer(next);
				वापस ret;
			पूर्ण

			path->slots[*level]++;
			अगर (wc->मुक्त) अणु
				ret = btrfs_पढ़ो_buffer(next, ptr_gen,
							*level - 1, &first_key);
				अगर (ret) अणु
					मुक्त_extent_buffer(next);
					वापस ret;
				पूर्ण

				अगर (trans) अणु
					btrfs_tree_lock(next);
					btrfs_clean_tree_block(next);
					btrfs_रुको_tree_block_ग_लिखोback(next);
					btrfs_tree_unlock(next);
					ret = btrfs_pin_reserved_extent(trans,
							bytenr, blocksize);
					अगर (ret) अणु
						मुक्त_extent_buffer(next);
						वापस ret;
					पूर्ण
					btrfs_redirty_list_add(
						trans->transaction, next);
				पूर्ण अन्यथा अणु
					अगर (test_and_clear_bit(EXTENT_BUFFER_सूचीTY, &next->bflags))
						clear_extent_buffer_dirty(next);
					unaccount_log_buffer(fs_info, bytenr);
				पूर्ण
			पूर्ण
			मुक्त_extent_buffer(next);
			जारी;
		पूर्ण
		ret = btrfs_पढ़ो_buffer(next, ptr_gen, *level - 1, &first_key);
		अगर (ret) अणु
			मुक्त_extent_buffer(next);
			वापस ret;
		पूर्ण

		अगर (path->nodes[*level-1])
			मुक्त_extent_buffer(path->nodes[*level-1]);
		path->nodes[*level-1] = next;
		*level = btrfs_header_level(next);
		path->slots[*level] = 0;
		cond_resched();
	पूर्ण
	path->slots[*level] = btrfs_header_nritems(path->nodes[*level]);

	cond_resched();
	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक walk_up_log_tree(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root,
				 काष्ठा btrfs_path *path, पूर्णांक *level,
				 काष्ठा walk_control *wc)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक i;
	पूर्णांक slot;
	पूर्णांक ret;

	क्रम (i = *level; i < BTRFS_MAX_LEVEL - 1 && path->nodes[i]; i++) अणु
		slot = path->slots[i];
		अगर (slot + 1 < btrfs_header_nritems(path->nodes[i])) अणु
			path->slots[i]++;
			*level = i;
			WARN_ON(*level == 0);
			वापस 0;
		पूर्ण अन्यथा अणु
			ret = wc->process_func(root, path->nodes[*level], wc,
				 btrfs_header_generation(path->nodes[*level]),
				 *level);
			अगर (ret)
				वापस ret;

			अगर (wc->मुक्त) अणु
				काष्ठा extent_buffer *next;

				next = path->nodes[*level];

				अगर (trans) अणु
					btrfs_tree_lock(next);
					btrfs_clean_tree_block(next);
					btrfs_रुको_tree_block_ग_लिखोback(next);
					btrfs_tree_unlock(next);
					ret = btrfs_pin_reserved_extent(trans,
						     path->nodes[*level]->start,
						     path->nodes[*level]->len);
					अगर (ret)
						वापस ret;
				पूर्ण अन्यथा अणु
					अगर (test_and_clear_bit(EXTENT_BUFFER_सूचीTY, &next->bflags))
						clear_extent_buffer_dirty(next);

					unaccount_log_buffer(fs_info,
						path->nodes[*level]->start);
				पूर्ण
			पूर्ण
			मुक्त_extent_buffer(path->nodes[*level]);
			path->nodes[*level] = शून्य;
			*level = i + 1;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * drop the reference count on the tree rooted at 'snap'.  This traverses
 * the tree मुक्तing any blocks that have a ref count of zero after being
 * decremented.
 */
अटल पूर्णांक walk_log_tree(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_root *log, काष्ठा walk_control *wc)
अणु
	काष्ठा btrfs_fs_info *fs_info = log->fs_info;
	पूर्णांक ret = 0;
	पूर्णांक wret;
	पूर्णांक level;
	काष्ठा btrfs_path *path;
	पूर्णांक orig_level;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	level = btrfs_header_level(log->node);
	orig_level = level;
	path->nodes[level] = log->node;
	atomic_inc(&log->node->refs);
	path->slots[level] = 0;

	जबतक (1) अणु
		wret = walk_करोwn_log_tree(trans, log, path, &level, wc);
		अगर (wret > 0)
			अवरोध;
		अगर (wret < 0) अणु
			ret = wret;
			जाओ out;
		पूर्ण

		wret = walk_up_log_tree(trans, log, path, &level, wc);
		अगर (wret > 0)
			अवरोध;
		अगर (wret < 0) अणु
			ret = wret;
			जाओ out;
		पूर्ण
	पूर्ण

	/* was the root node processed? अगर not, catch it here */
	अगर (path->nodes[orig_level]) अणु
		ret = wc->process_func(log, path->nodes[orig_level], wc,
			 btrfs_header_generation(path->nodes[orig_level]),
			 orig_level);
		अगर (ret)
			जाओ out;
		अगर (wc->मुक्त) अणु
			काष्ठा extent_buffer *next;

			next = path->nodes[orig_level];

			अगर (trans) अणु
				btrfs_tree_lock(next);
				btrfs_clean_tree_block(next);
				btrfs_रुको_tree_block_ग_लिखोback(next);
				btrfs_tree_unlock(next);
				ret = btrfs_pin_reserved_extent(trans,
						next->start, next->len);
				अगर (ret)
					जाओ out;
			पूर्ण अन्यथा अणु
				अगर (test_and_clear_bit(EXTENT_BUFFER_सूचीTY, &next->bflags))
					clear_extent_buffer_dirty(next);
				unaccount_log_buffer(fs_info, next->start);
			पूर्ण
		पूर्ण
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * helper function to update the item क्रम a given subvolumes log root
 * in the tree of log roots
 */
अटल पूर्णांक update_log_root(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *log,
			   काष्ठा btrfs_root_item *root_item)
अणु
	काष्ठा btrfs_fs_info *fs_info = log->fs_info;
	पूर्णांक ret;

	अगर (log->log_transid == 1) अणु
		/* insert root item on the first sync */
		ret = btrfs_insert_root(trans, fs_info->log_root_tree,
				&log->root_key, root_item);
	पूर्ण अन्यथा अणु
		ret = btrfs_update_root(trans, fs_info->log_root_tree,
				&log->root_key, root_item);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम रुको_log_commit(काष्ठा btrfs_root *root, पूर्णांक transid)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक index = transid % 2;

	/*
	 * we only allow two pending log transactions at a समय,
	 * so we know that अगर ours is more than 2 older than the
	 * current transaction, we're करोne
	 */
	क्रम (;;) अणु
		prepare_to_रुको(&root->log_commit_रुको[index],
				&रुको, TASK_UNINTERRUPTIBLE);

		अगर (!(root->log_transid_committed < transid &&
		      atomic_पढ़ो(&root->log_commit[index])))
			अवरोध;

		mutex_unlock(&root->log_mutex);
		schedule();
		mutex_lock(&root->log_mutex);
	पूर्ण
	finish_रुको(&root->log_commit_रुको[index], &रुको);
पूर्ण

अटल व्योम रुको_क्रम_ग_लिखोr(काष्ठा btrfs_root *root)
अणु
	DEFINE_WAIT(रुको);

	क्रम (;;) अणु
		prepare_to_रुको(&root->log_ग_लिखोr_रुको, &रुको,
				TASK_UNINTERRUPTIBLE);
		अगर (!atomic_पढ़ो(&root->log_ग_लिखोrs))
			अवरोध;

		mutex_unlock(&root->log_mutex);
		schedule();
		mutex_lock(&root->log_mutex);
	पूर्ण
	finish_रुको(&root->log_ग_लिखोr_रुको, &रुको);
पूर्ण

अटल अंतरभूत व्योम btrfs_हटाओ_log_ctx(काष्ठा btrfs_root *root,
					काष्ठा btrfs_log_ctx *ctx)
अणु
	अगर (!ctx)
		वापस;

	mutex_lock(&root->log_mutex);
	list_del_init(&ctx->list);
	mutex_unlock(&root->log_mutex);
पूर्ण

/* 
 * Invoked in log mutex context, or be sure there is no other task which
 * can access the list.
 */
अटल अंतरभूत व्योम btrfs_हटाओ_all_log_ctxs(काष्ठा btrfs_root *root,
					     पूर्णांक index, पूर्णांक error)
अणु
	काष्ठा btrfs_log_ctx *ctx;
	काष्ठा btrfs_log_ctx *safe;

	list_क्रम_each_entry_safe(ctx, safe, &root->log_ctxs[index], list) अणु
		list_del_init(&ctx->list);
		ctx->log_ret = error;
	पूर्ण

	INIT_LIST_HEAD(&root->log_ctxs[index]);
पूर्ण

/*
 * btrfs_sync_log करोes sends a given tree log करोwn to the disk and
 * updates the super blocks to record it.  When this call is करोne,
 * you know that any inodes previously logged are safely on disk only
 * अगर it वापसs 0.
 *
 * Any other वापस value means you need to call btrfs_commit_transaction.
 * Some of the edge हालs क्रम fsyncing directories that have had unlinks
 * or नामs करोne in the past mean that someबार the only safe
 * fsync is to commit the whole FS.  When btrfs_sync_log वापसs -EAGAIN,
 * that has happened.
 */
पूर्णांक btrfs_sync_log(काष्ठा btrfs_trans_handle *trans,
		   काष्ठा btrfs_root *root, काष्ठा btrfs_log_ctx *ctx)
अणु
	पूर्णांक index1;
	पूर्णांक index2;
	पूर्णांक mark;
	पूर्णांक ret;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *log = root->log_root;
	काष्ठा btrfs_root *log_root_tree = fs_info->log_root_tree;
	काष्ठा btrfs_root_item new_root_item;
	पूर्णांक log_transid = 0;
	काष्ठा btrfs_log_ctx root_log_ctx;
	काष्ठा blk_plug plug;
	u64 log_root_start;
	u64 log_root_level;

	mutex_lock(&root->log_mutex);
	log_transid = ctx->log_transid;
	अगर (root->log_transid_committed >= log_transid) अणु
		mutex_unlock(&root->log_mutex);
		वापस ctx->log_ret;
	पूर्ण

	index1 = log_transid % 2;
	अगर (atomic_पढ़ो(&root->log_commit[index1])) अणु
		रुको_log_commit(root, log_transid);
		mutex_unlock(&root->log_mutex);
		वापस ctx->log_ret;
	पूर्ण
	ASSERT(log_transid == root->log_transid);
	atomic_set(&root->log_commit[index1], 1);

	/* रुको क्रम previous tree log sync to complete */
	अगर (atomic_पढ़ो(&root->log_commit[(index1 + 1) % 2]))
		रुको_log_commit(root, log_transid - 1);

	जबतक (1) अणु
		पूर्णांक batch = atomic_पढ़ो(&root->log_batch);
		/* when we're on an ssd, just kick the log commit out */
		अगर (!btrfs_test_opt(fs_info, SSD) &&
		    test_bit(BTRFS_ROOT_MULTI_LOG_TASKS, &root->state)) अणु
			mutex_unlock(&root->log_mutex);
			schedule_समयout_unपूर्णांकerruptible(1);
			mutex_lock(&root->log_mutex);
		पूर्ण
		रुको_क्रम_ग_लिखोr(root);
		अगर (batch == atomic_पढ़ो(&root->log_batch))
			अवरोध;
	पूर्ण

	/* bail out अगर we need to करो a full commit */
	अगर (btrfs_need_log_full_commit(trans)) अणु
		ret = -EAGAIN;
		mutex_unlock(&root->log_mutex);
		जाओ out;
	पूर्ण

	अगर (log_transid % 2 == 0)
		mark = EXTENT_सूचीTY;
	अन्यथा
		mark = EXTENT_NEW;

	/* we start IO on  all the marked extents here, but we करोn't actually
	 * रुको क्रम them until later.
	 */
	blk_start_plug(&plug);
	ret = btrfs_ग_लिखो_marked_extents(fs_info, &log->dirty_log_pages, mark);
	/*
	 * -EAGAIN happens when someone, e.g., a concurrent transaction
	 *  commit, ग_लिखोs a dirty extent in this tree-log commit. This
	 *  concurrent ग_लिखो will create a hole writing out the extents,
	 *  and we cannot proceed on a zoned fileप्रणाली, requiring
	 *  sequential writing. While we can bail out to a full commit
	 *  here, but we can जारी hoping the concurrent writing fills
	 *  the hole.
	 */
	अगर (ret == -EAGAIN && btrfs_is_zoned(fs_info))
		ret = 0;
	अगर (ret) अणु
		blk_finish_plug(&plug);
		btrfs_पात_transaction(trans, ret);
		btrfs_set_log_full_commit(trans);
		mutex_unlock(&root->log_mutex);
		जाओ out;
	पूर्ण

	/*
	 * We _must_ update under the root->log_mutex in order to make sure we
	 * have a consistent view of the log root we are trying to commit at
	 * this moment.
	 *
	 * We _must_ copy this पूर्णांकo a local copy, because we are not holding the
	 * log_root_tree->log_mutex yet.  This is important because when we
	 * commit the log_root_tree we must have a consistent view of the
	 * log_root_tree when we update the super block to poपूर्णांक at the
	 * log_root_tree bytenr.  If we update the log_root_tree here we'll race
	 * with the commit and possibly poपूर्णांक at the new block which we may not
	 * have written out.
	 */
	btrfs_set_root_node(&log->root_item, log->node);
	स_नकल(&new_root_item, &log->root_item, माप(new_root_item));

	root->log_transid++;
	log->log_transid = root->log_transid;
	root->log_start_pid = 0;
	/*
	 * IO has been started, blocks of the log tree have WRITTEN flag set
	 * in their headers. new modअगरications of the log will be written to
	 * new positions. so it's safe to allow log ग_लिखोrs to go in.
	 */
	mutex_unlock(&root->log_mutex);

	अगर (btrfs_is_zoned(fs_info)) अणु
		mutex_lock(&fs_info->tree_root->log_mutex);
		अगर (!log_root_tree->node) अणु
			ret = btrfs_alloc_log_tree_node(trans, log_root_tree);
			अगर (ret) अणु
				mutex_unlock(&fs_info->tree_log_mutex);
				जाओ out;
			पूर्ण
		पूर्ण
		mutex_unlock(&fs_info->tree_root->log_mutex);
	पूर्ण

	btrfs_init_log_ctx(&root_log_ctx, शून्य);

	mutex_lock(&log_root_tree->log_mutex);

	index2 = log_root_tree->log_transid % 2;
	list_add_tail(&root_log_ctx.list, &log_root_tree->log_ctxs[index2]);
	root_log_ctx.log_transid = log_root_tree->log_transid;

	/*
	 * Now we are safe to update the log_root_tree because we're under the
	 * log_mutex, and we're a current writer so we're holding the commit
	 * खोलो until we drop the log_mutex.
	 */
	ret = update_log_root(trans, log, &new_root_item);
	अगर (ret) अणु
		अगर (!list_empty(&root_log_ctx.list))
			list_del_init(&root_log_ctx.list);

		blk_finish_plug(&plug);
		btrfs_set_log_full_commit(trans);

		अगर (ret != -ENOSPC) अणु
			btrfs_पात_transaction(trans, ret);
			mutex_unlock(&log_root_tree->log_mutex);
			जाओ out;
		पूर्ण
		btrfs_रुको_tree_log_extents(log, mark);
		mutex_unlock(&log_root_tree->log_mutex);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (log_root_tree->log_transid_committed >= root_log_ctx.log_transid) अणु
		blk_finish_plug(&plug);
		list_del_init(&root_log_ctx.list);
		mutex_unlock(&log_root_tree->log_mutex);
		ret = root_log_ctx.log_ret;
		जाओ out;
	पूर्ण

	index2 = root_log_ctx.log_transid % 2;
	अगर (atomic_पढ़ो(&log_root_tree->log_commit[index2])) अणु
		blk_finish_plug(&plug);
		ret = btrfs_रुको_tree_log_extents(log, mark);
		रुको_log_commit(log_root_tree,
				root_log_ctx.log_transid);
		mutex_unlock(&log_root_tree->log_mutex);
		अगर (!ret)
			ret = root_log_ctx.log_ret;
		जाओ out;
	पूर्ण
	ASSERT(root_log_ctx.log_transid == log_root_tree->log_transid);
	atomic_set(&log_root_tree->log_commit[index2], 1);

	अगर (atomic_पढ़ो(&log_root_tree->log_commit[(index2 + 1) % 2])) अणु
		रुको_log_commit(log_root_tree,
				root_log_ctx.log_transid - 1);
	पूर्ण

	/*
	 * now that we've moved on to the tree of log tree roots,
	 * check the full commit flag again
	 */
	अगर (btrfs_need_log_full_commit(trans)) अणु
		blk_finish_plug(&plug);
		btrfs_रुको_tree_log_extents(log, mark);
		mutex_unlock(&log_root_tree->log_mutex);
		ret = -EAGAIN;
		जाओ out_wake_log_root;
	पूर्ण

	ret = btrfs_ग_लिखो_marked_extents(fs_info,
					 &log_root_tree->dirty_log_pages,
					 EXTENT_सूचीTY | EXTENT_NEW);
	blk_finish_plug(&plug);
	/*
	 * As described above, -EAGAIN indicates a hole in the extents. We
	 * cannot रुको क्रम these ग_लिखो outs since the रुकोing cause a
	 * deadlock. Bail out to the full commit instead.
	 */
	अगर (ret == -EAGAIN && btrfs_is_zoned(fs_info)) अणु
		btrfs_set_log_full_commit(trans);
		btrfs_रुको_tree_log_extents(log, mark);
		mutex_unlock(&log_root_tree->log_mutex);
		जाओ out_wake_log_root;
	पूर्ण अन्यथा अगर (ret) अणु
		btrfs_set_log_full_commit(trans);
		btrfs_पात_transaction(trans, ret);
		mutex_unlock(&log_root_tree->log_mutex);
		जाओ out_wake_log_root;
	पूर्ण
	ret = btrfs_रुको_tree_log_extents(log, mark);
	अगर (!ret)
		ret = btrfs_रुको_tree_log_extents(log_root_tree,
						  EXTENT_NEW | EXTENT_सूचीTY);
	अगर (ret) अणु
		btrfs_set_log_full_commit(trans);
		mutex_unlock(&log_root_tree->log_mutex);
		जाओ out_wake_log_root;
	पूर्ण

	log_root_start = log_root_tree->node->start;
	log_root_level = btrfs_header_level(log_root_tree->node);
	log_root_tree->log_transid++;
	mutex_unlock(&log_root_tree->log_mutex);

	/*
	 * Here we are guaranteed that nobody is going to ग_लिखो the superblock
	 * क्रम the current transaction beक्रमe us and that neither we करो ग_लिखो
	 * our superblock beक्रमe the previous transaction finishes its commit
	 * and ग_लिखोs its superblock, because:
	 *
	 * 1) We are holding a handle on the current transaction, so no body
	 *    can commit it until we release the handle;
	 *
	 * 2) Beक्रमe writing our superblock we acquire the tree_log_mutex, so
	 *    अगर the previous transaction is still committing, and hasn't yet
	 *    written its superblock, we रुको क्रम it to करो it, because a
	 *    transaction commit acquires the tree_log_mutex when the commit
	 *    begins and releases it only after writing its superblock.
	 */
	mutex_lock(&fs_info->tree_log_mutex);

	/*
	 * The previous transaction ग_लिखोout phase could have failed, and thus
	 * marked the fs in an error state.  We must not commit here, as we
	 * could have updated our generation in the super_क्रम_commit and
	 * writing the super here would result in transid mismatches.  If there
	 * is an error here just bail.
	 */
	अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state)) अणु
		ret = -EIO;
		btrfs_set_log_full_commit(trans);
		btrfs_पात_transaction(trans, ret);
		mutex_unlock(&fs_info->tree_log_mutex);
		जाओ out_wake_log_root;
	पूर्ण

	btrfs_set_super_log_root(fs_info->super_क्रम_commit, log_root_start);
	btrfs_set_super_log_root_level(fs_info->super_क्रम_commit, log_root_level);
	ret = ग_लिखो_all_supers(fs_info, 1);
	mutex_unlock(&fs_info->tree_log_mutex);
	अगर (ret) अणु
		btrfs_set_log_full_commit(trans);
		btrfs_पात_transaction(trans, ret);
		जाओ out_wake_log_root;
	पूर्ण

	mutex_lock(&root->log_mutex);
	अगर (root->last_log_commit < log_transid)
		root->last_log_commit = log_transid;
	mutex_unlock(&root->log_mutex);

out_wake_log_root:
	mutex_lock(&log_root_tree->log_mutex);
	btrfs_हटाओ_all_log_ctxs(log_root_tree, index2, ret);

	log_root_tree->log_transid_committed++;
	atomic_set(&log_root_tree->log_commit[index2], 0);
	mutex_unlock(&log_root_tree->log_mutex);

	/*
	 * The barrier beक्रमe रुकोqueue_active (in cond_wake_up) is needed so
	 * all the updates above are seen by the woken thपढ़ोs. It might not be
	 * necessary, but proving that seems to be hard.
	 */
	cond_wake_up(&log_root_tree->log_commit_रुको[index2]);
out:
	mutex_lock(&root->log_mutex);
	btrfs_हटाओ_all_log_ctxs(root, index1, ret);
	root->log_transid_committed++;
	atomic_set(&root->log_commit[index1], 0);
	mutex_unlock(&root->log_mutex);

	/*
	 * The barrier beक्रमe रुकोqueue_active (in cond_wake_up) is needed so
	 * all the updates above are seen by the woken thपढ़ोs. It might not be
	 * necessary, but proving that seems to be hard.
	 */
	cond_wake_up(&root->log_commit_रुको[index1]);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_log_tree(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *log)
अणु
	पूर्णांक ret;
	काष्ठा walk_control wc = अणु
		.मुक्त = 1,
		.process_func = process_one_buffer
	पूर्ण;

	अगर (log->node) अणु
		ret = walk_log_tree(trans, log, &wc);
		अगर (ret) अणु
			अगर (trans)
				btrfs_पात_transaction(trans, ret);
			अन्यथा
				btrfs_handle_fs_error(log->fs_info, ret, शून्य);
		पूर्ण
	पूर्ण

	clear_extent_bits(&log->dirty_log_pages, 0, (u64)-1,
			  EXTENT_सूचीTY | EXTENT_NEW | EXTENT_NEED_WAIT);
	extent_io_tree_release(&log->log_csum_range);

	अगर (trans && log->node)
		btrfs_redirty_list_add(trans->transaction, log->node);
	btrfs_put_root(log);
पूर्ण

/*
 * मुक्त all the extents used by the tree log.  This should be called
 * at commit समय of the full transaction
 */
पूर्णांक btrfs_मुक्त_log(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root)
अणु
	अगर (root->log_root) अणु
		मुक्त_log_tree(trans, root->log_root);
		root->log_root = शून्य;
		clear_bit(BTRFS_ROOT_HAS_LOG_TREE, &root->state);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक btrfs_मुक्त_log_root_tree(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (fs_info->log_root_tree) अणु
		मुक्त_log_tree(trans, fs_info->log_root_tree);
		fs_info->log_root_tree = शून्य;
		clear_bit(BTRFS_ROOT_HAS_LOG_TREE, &fs_info->tree_root->state);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check अगर an inode was logged in the current transaction. We can't always rely
 * on an inode's logged_trans value, because it's an in-memory only field and
 * thereक्रमe not persisted. This means that its value is lost अगर the inode माला_लो
 * evicted and loaded again from disk (in which हाल it has a value of 0, and
 * certainly it is smaller then any possible transaction ID), when that happens
 * the full_sync flag is set in the inode's runसमय flags, so on that हाल we
 * assume eviction happened and ignore the logged_trans value, assuming the
 * worst हाल, that the inode was logged beक्रमe in the current transaction.
 */
अटल bool inode_logged(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_inode *inode)
अणु
	अगर (inode->logged_trans == trans->transid)
		वापस true;

	अगर (inode->last_trans == trans->transid &&
	    test_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &inode->runसमय_flags) &&
	    !test_bit(BTRFS_FS_LOG_RECOVERING, &trans->fs_info->flags))
		वापस true;

	वापस false;
पूर्ण

/*
 * If both a file and directory are logged, and unlinks or नामs are
 * mixed in, we have a few पूर्णांकeresting corners:
 *
 * create file X in dir Y
 * link file X to X.link in dir Y
 * fsync file X
 * unlink file X but leave X.link
 * fsync dir Y
 *
 * After a crash we would expect only X.link to exist.  But file X
 * didn't get fsync'd again so the log has back refs क्रम X and X.link.
 *
 * We solve this by removing directory entries and inode backrefs from the
 * log when a file that was logged in the current transaction is
 * unlinked.  Any later fsync will include the updated log entries, and
 * we'll be able to reस्थिरruct the proper directory items from backrefs.
 *
 * This optimizations allows us to aव्योम relogging the entire inode
 * or the entire directory.
 */
पूर्णांक btrfs_del_dir_entries_in_log(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root,
				 स्थिर अक्षर *name, पूर्णांक name_len,
				 काष्ठा btrfs_inode *dir, u64 index)
अणु
	काष्ठा btrfs_root *log;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_path *path;
	पूर्णांक ret;
	पूर्णांक err = 0;
	u64 dir_ino = btrfs_ino(dir);

	अगर (!inode_logged(trans, dir))
		वापस 0;

	ret = join_running_log_trans(root);
	अगर (ret)
		वापस 0;

	mutex_lock(&dir->log_mutex);

	log = root->log_root;
	path = btrfs_alloc_path();
	अगर (!path) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	di = btrfs_lookup_dir_item(trans, log, path, dir_ino,
				   name, name_len, -1);
	अगर (IS_ERR(di)) अणु
		err = PTR_ERR(di);
		जाओ fail;
	पूर्ण
	अगर (di) अणु
		ret = btrfs_delete_one_dir_name(trans, log, path, di);
		अगर (ret) अणु
			err = ret;
			जाओ fail;
		पूर्ण
	पूर्ण
	btrfs_release_path(path);
	di = btrfs_lookup_dir_index_item(trans, log, path, dir_ino,
					 index, name, name_len, -1);
	अगर (IS_ERR(di)) अणु
		err = PTR_ERR(di);
		जाओ fail;
	पूर्ण
	अगर (di) अणु
		ret = btrfs_delete_one_dir_name(trans, log, path, di);
		अगर (ret) अणु
			err = ret;
			जाओ fail;
		पूर्ण
	पूर्ण

	/*
	 * We करो not need to update the size field of the directory's inode item
	 * because on log replay we update the field to reflect all existing
	 * entries in the directory (see overग_लिखो_item()).
	 */
fail:
	btrfs_मुक्त_path(path);
out_unlock:
	mutex_unlock(&dir->log_mutex);
	अगर (err == -ENOSPC) अणु
		btrfs_set_log_full_commit(trans);
		err = 0;
	पूर्ण अन्यथा अगर (err < 0 && err != -ENOENT) अणु
		/* ENOENT can be वापसed अगर the entry hasn't been fsynced yet */
		btrfs_पात_transaction(trans, err);
	पूर्ण

	btrfs_end_log_trans(root);

	वापस err;
पूर्ण

/* see comments क्रम btrfs_del_dir_entries_in_log */
पूर्णांक btrfs_del_inode_ref_in_log(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       स्थिर अक्षर *name, पूर्णांक name_len,
			       काष्ठा btrfs_inode *inode, u64 dirid)
अणु
	काष्ठा btrfs_root *log;
	u64 index;
	पूर्णांक ret;

	अगर (!inode_logged(trans, inode))
		वापस 0;

	ret = join_running_log_trans(root);
	अगर (ret)
		वापस 0;
	log = root->log_root;
	mutex_lock(&inode->log_mutex);

	ret = btrfs_del_inode_ref(trans, log, name, name_len, btrfs_ino(inode),
				  dirid, &index);
	mutex_unlock(&inode->log_mutex);
	अगर (ret == -ENOSPC) अणु
		btrfs_set_log_full_commit(trans);
		ret = 0;
	पूर्ण अन्यथा अगर (ret < 0 && ret != -ENOENT)
		btrfs_पात_transaction(trans, ret);
	btrfs_end_log_trans(root);

	वापस ret;
पूर्ण

/*
 * creates a range item in the log क्रम 'dirid'.  first_offset and
 * last_offset tell us which parts of the key space the log should
 * be considered authoritative क्रम.
 */
अटल noअंतरभूत पूर्णांक insert_dir_log_key(काष्ठा btrfs_trans_handle *trans,
				       काष्ठा btrfs_root *log,
				       काष्ठा btrfs_path *path,
				       पूर्णांक key_type, u64 dirid,
				       u64 first_offset, u64 last_offset)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_dir_log_item *item;

	key.objectid = dirid;
	key.offset = first_offset;
	अगर (key_type == BTRFS_सूची_ITEM_KEY)
		key.type = BTRFS_सूची_LOG_ITEM_KEY;
	अन्यथा
		key.type = BTRFS_सूची_LOG_INDEX_KEY;
	ret = btrfs_insert_empty_item(trans, log, path, &key, माप(*item));
	अगर (ret)
		वापस ret;

	item = btrfs_item_ptr(path->nodes[0], path->slots[0],
			      काष्ठा btrfs_dir_log_item);
	btrfs_set_dir_log_end(path->nodes[0], item, last_offset);
	btrfs_mark_buffer_dirty(path->nodes[0]);
	btrfs_release_path(path);
	वापस 0;
पूर्ण

/*
 * log all the items included in the current transaction क्रम a given
 * directory.  This also creates the range items in the log tree required
 * to replay anything deleted beक्रमe the fsync
 */
अटल noअंतरभूत पूर्णांक log_dir_items(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode,
			  काष्ठा btrfs_path *path,
			  काष्ठा btrfs_path *dst_path, पूर्णांक key_type,
			  काष्ठा btrfs_log_ctx *ctx,
			  u64 min_offset, u64 *last_offset_ret)
अणु
	काष्ठा btrfs_key min_key;
	काष्ठा btrfs_root *log = root->log_root;
	काष्ठा extent_buffer *src;
	पूर्णांक err = 0;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक nritems;
	u64 first_offset = min_offset;
	u64 last_offset = (u64)-1;
	u64 ino = btrfs_ino(inode);

	log = root->log_root;

	min_key.objectid = ino;
	min_key.type = key_type;
	min_key.offset = min_offset;

	ret = btrfs_search_क्रमward(root, &min_key, path, trans->transid);

	/*
	 * we didn't find anything from this transaction, see अगर there
	 * is anything at all
	 */
	अगर (ret != 0 || min_key.objectid != ino || min_key.type != key_type) अणु
		min_key.objectid = ino;
		min_key.type = key_type;
		min_key.offset = (u64)-1;
		btrfs_release_path(path);
		ret = btrfs_search_slot(शून्य, root, &min_key, path, 0, 0);
		अगर (ret < 0) अणु
			btrfs_release_path(path);
			वापस ret;
		पूर्ण
		ret = btrfs_previous_item(root, path, ino, key_type);

		/* अगर ret == 0 there are items क्रम this type,
		 * create a range to tell us the last key of this type.
		 * otherwise, there are no items in this directory after
		 * *min_offset, and we create a range to indicate that.
		 */
		अगर (ret == 0) अणु
			काष्ठा btrfs_key पंचांगp;
			btrfs_item_key_to_cpu(path->nodes[0], &पंचांगp,
					      path->slots[0]);
			अगर (key_type == पंचांगp.type)
				first_offset = max(min_offset, पंचांगp.offset) + 1;
		पूर्ण
		जाओ करोne;
	पूर्ण

	/* go backward to find any previous key */
	ret = btrfs_previous_item(root, path, ino, key_type);
	अगर (ret == 0) अणु
		काष्ठा btrfs_key पंचांगp;
		btrfs_item_key_to_cpu(path->nodes[0], &पंचांगp, path->slots[0]);
		अगर (key_type == पंचांगp.type) अणु
			first_offset = पंचांगp.offset;
			ret = overग_लिखो_item(trans, log, dst_path,
					     path->nodes[0], path->slots[0],
					     &पंचांगp);
			अगर (ret) अणु
				err = ret;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
	btrfs_release_path(path);

	/*
	 * Find the first key from this transaction again.  See the note क्रम
	 * log_new_dir_dentries, अगर we're logging a directory recursively we
	 * won't be holding its i_mutex, which means we can modअगरy the directory
	 * जबतक we're logging it.  If we हटाओ an entry between our first
	 * search and this search we'll not find the key again and can just
	 * bail.
	 */
search:
	ret = btrfs_search_slot(शून्य, root, &min_key, path, 0, 0);
	अगर (ret != 0)
		जाओ करोne;

	/*
	 * we have a block from this transaction, log every item in it
	 * from our directory
	 */
	जबतक (1) अणु
		काष्ठा btrfs_key पंचांगp;
		src = path->nodes[0];
		nritems = btrfs_header_nritems(src);
		क्रम (i = path->slots[0]; i < nritems; i++) अणु
			काष्ठा btrfs_dir_item *di;

			btrfs_item_key_to_cpu(src, &min_key, i);

			अगर (min_key.objectid != ino || min_key.type != key_type)
				जाओ करोne;

			अगर (need_resched()) अणु
				btrfs_release_path(path);
				cond_resched();
				जाओ search;
			पूर्ण

			ret = overग_लिखो_item(trans, log, dst_path, src, i,
					     &min_key);
			अगर (ret) अणु
				err = ret;
				जाओ करोne;
			पूर्ण

			/*
			 * We must make sure that when we log a directory entry,
			 * the corresponding inode, after log replay, has a
			 * matching link count. For example:
			 *
			 * touch foo
			 * सूची_गढ़ो mydir
			 * sync
			 * ln foo mydir/bar
			 * xfs_io -c "fsync" mydir
			 * <crash>
			 * <mount fs and log replay>
			 *
			 * Would result in a fsync log that when replayed, our
			 * file inode would have a link count of 1, but we get
			 * two directory entries poपूर्णांकing to the same inode.
			 * After removing one of the names, it would not be
			 * possible to हटाओ the other name, which resulted
			 * always in stale file handle errors, and would not
			 * be possible to सूची_हटाओ the parent directory, since
			 * its i_size could never decrement to the value
			 * BTRFS_EMPTY_सूची_SIZE, resulting in -ENOTEMPTY errors.
			 */
			di = btrfs_item_ptr(src, i, काष्ठा btrfs_dir_item);
			btrfs_dir_item_key_to_cpu(src, di, &पंचांगp);
			अगर (ctx &&
			    (btrfs_dir_transid(src, di) == trans->transid ||
			     btrfs_dir_type(src, di) == BTRFS_FT_सूची) &&
			    पंचांगp.type != BTRFS_ROOT_ITEM_KEY)
				ctx->log_new_dentries = true;
		पूर्ण
		path->slots[0] = nritems;

		/*
		 * look ahead to the next item and see अगर it is also
		 * from this directory and from this transaction
		 */
		ret = btrfs_next_leaf(root, path);
		अगर (ret) अणु
			अगर (ret == 1)
				last_offset = (u64)-1;
			अन्यथा
				err = ret;
			जाओ करोne;
		पूर्ण
		btrfs_item_key_to_cpu(path->nodes[0], &पंचांगp, path->slots[0]);
		अगर (पंचांगp.objectid != ino || पंचांगp.type != key_type) अणु
			last_offset = (u64)-1;
			जाओ करोne;
		पूर्ण
		अगर (btrfs_header_generation(path->nodes[0]) != trans->transid) अणु
			ret = overग_लिखो_item(trans, log, dst_path,
					     path->nodes[0], path->slots[0],
					     &पंचांगp);
			अगर (ret)
				err = ret;
			अन्यथा
				last_offset = पंचांगp.offset;
			जाओ करोne;
		पूर्ण
	पूर्ण
करोne:
	btrfs_release_path(path);
	btrfs_release_path(dst_path);

	अगर (err == 0) अणु
		*last_offset_ret = last_offset;
		/*
		 * insert the log range keys to indicate where the log
		 * is valid
		 */
		ret = insert_dir_log_key(trans, log, path, key_type,
					 ino, first_offset, last_offset);
		अगर (ret)
			err = ret;
	पूर्ण
	वापस err;
पूर्ण

/*
 * logging directories is very similar to logging inodes, We find all the items
 * from the current transaction and ग_लिखो them to the log.
 *
 * The recovery code scans the directory in the subvolume, and अगर it finds a
 * key in the range logged that is not present in the log tree, then it means
 * that dir entry was unlinked during the transaction.
 *
 * In order क्रम that scan to work, we must include one key smaller than
 * the smallest logged by this transaction and one key larger than the largest
 * key logged by this transaction.
 */
अटल noअंतरभूत पूर्णांक log_directory_changes(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode,
			  काष्ठा btrfs_path *path,
			  काष्ठा btrfs_path *dst_path,
			  काष्ठा btrfs_log_ctx *ctx)
अणु
	u64 min_key;
	u64 max_key;
	पूर्णांक ret;
	पूर्णांक key_type = BTRFS_सूची_ITEM_KEY;

again:
	min_key = 0;
	max_key = 0;
	जबतक (1) अणु
		ret = log_dir_items(trans, root, inode, path, dst_path, key_type,
				ctx, min_key, &max_key);
		अगर (ret)
			वापस ret;
		अगर (max_key == (u64)-1)
			अवरोध;
		min_key = max_key + 1;
	पूर्ण

	अगर (key_type == BTRFS_सूची_ITEM_KEY) अणु
		key_type = BTRFS_सूची_INDEX_KEY;
		जाओ again;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * a helper function to drop items from the log beक्रमe we relog an
 * inode.  max_key_type indicates the highest item type to हटाओ.
 * This cannot be run क्रम file data extents because it करोes not
 * मुक्त the extents they poपूर्णांक to.
 */
अटल पूर्णांक drop_objectid_items(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_root *log,
				  काष्ठा btrfs_path *path,
				  u64 objectid, पूर्णांक max_key_type)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	पूर्णांक start_slot;

	key.objectid = objectid;
	key.type = max_key_type;
	key.offset = (u64)-1;

	जबतक (1) अणु
		ret = btrfs_search_slot(trans, log, &key, path, -1, 1);
		BUG_ON(ret == 0); /* Logic error */
		अगर (ret < 0)
			अवरोध;

		अगर (path->slots[0] == 0)
			अवरोध;

		path->slots[0]--;
		btrfs_item_key_to_cpu(path->nodes[0], &found_key,
				      path->slots[0]);

		अगर (found_key.objectid != objectid)
			अवरोध;

		found_key.offset = 0;
		found_key.type = 0;
		ret = btrfs_bin_search(path->nodes[0], &found_key, &start_slot);
		अगर (ret < 0)
			अवरोध;

		ret = btrfs_del_items(trans, log, path, start_slot,
				      path->slots[0] - start_slot + 1);
		/*
		 * If start slot isn't 0 then we don't need to re-search, we've
		 * found the last guy with the objectid in this tree.
		 */
		अगर (ret || start_slot != 0)
			अवरोध;
		btrfs_release_path(path);
	पूर्ण
	btrfs_release_path(path);
	अगर (ret > 0)
		ret = 0;
	वापस ret;
पूर्ण

अटल व्योम fill_inode_item(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा extent_buffer *leaf,
			    काष्ठा btrfs_inode_item *item,
			    काष्ठा inode *inode, पूर्णांक log_inode_only,
			    u64 logged_isize)
अणु
	काष्ठा btrfs_map_token token;

	btrfs_init_map_token(&token, leaf);

	अगर (log_inode_only) अणु
		/* set the generation to zero so the recover code
		 * can tell the dअगरference between an logging
		 * just to say 'this inode exists' and a logging
		 * to say 'update this inode with these values'
		 */
		btrfs_set_token_inode_generation(&token, item, 0);
		btrfs_set_token_inode_size(&token, item, logged_isize);
	पूर्ण अन्यथा अणु
		btrfs_set_token_inode_generation(&token, item,
						 BTRFS_I(inode)->generation);
		btrfs_set_token_inode_size(&token, item, inode->i_size);
	पूर्ण

	btrfs_set_token_inode_uid(&token, item, i_uid_पढ़ो(inode));
	btrfs_set_token_inode_gid(&token, item, i_gid_पढ़ो(inode));
	btrfs_set_token_inode_mode(&token, item, inode->i_mode);
	btrfs_set_token_inode_nlink(&token, item, inode->i_nlink);

	btrfs_set_token_बारpec_sec(&token, &item->aसमय,
				     inode->i_aसमय.tv_sec);
	btrfs_set_token_बारpec_nsec(&token, &item->aसमय,
				      inode->i_aसमय.tv_nsec);

	btrfs_set_token_बारpec_sec(&token, &item->mसमय,
				     inode->i_mसमय.tv_sec);
	btrfs_set_token_बारpec_nsec(&token, &item->mसमय,
				      inode->i_mसमय.tv_nsec);

	btrfs_set_token_बारpec_sec(&token, &item->स_समय,
				     inode->i_स_समय.tv_sec);
	btrfs_set_token_बारpec_nsec(&token, &item->स_समय,
				      inode->i_स_समय.tv_nsec);

	/*
	 * We करो not need to set the nbytes field, in fact during a fast fsync
	 * its value may not even be correct, since a fast fsync करोes not रुको
	 * क्रम ordered extent completion, which is where we update nbytes, it
	 * only रुकोs क्रम ग_लिखोback to complete. During log replay as we find
	 * file extent items and replay them, we adjust the nbytes field of the
	 * inode item in subvolume tree as needed (see overग_लिखो_item()).
	 */

	btrfs_set_token_inode_sequence(&token, item, inode_peek_iversion(inode));
	btrfs_set_token_inode_transid(&token, item, trans->transid);
	btrfs_set_token_inode_rdev(&token, item, inode->i_rdev);
	btrfs_set_token_inode_flags(&token, item, BTRFS_I(inode)->flags);
	btrfs_set_token_inode_block_group(&token, item, 0);
पूर्ण

अटल पूर्णांक log_inode_item(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *log, काष्ठा btrfs_path *path,
			  काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_inode_item *inode_item;
	पूर्णांक ret;

	ret = btrfs_insert_empty_item(trans, log, path,
				      &inode->location, माप(*inode_item));
	अगर (ret && ret != -EEXIST)
		वापस ret;
	inode_item = btrfs_item_ptr(path->nodes[0], path->slots[0],
				    काष्ठा btrfs_inode_item);
	fill_inode_item(trans, path->nodes[0], inode_item, &inode->vfs_inode,
			0, 0);
	btrfs_release_path(path);
	वापस 0;
पूर्ण

अटल पूर्णांक log_csums(काष्ठा btrfs_trans_handle *trans,
		     काष्ठा btrfs_inode *inode,
		     काष्ठा btrfs_root *log_root,
		     काष्ठा btrfs_ordered_sum *sums)
अणु
	स्थिर u64 lock_end = sums->bytenr + sums->len - 1;
	काष्ठा extent_state *cached_state = शून्य;
	पूर्णांक ret;

	/*
	 * If this inode was not used क्रम reflink operations in the current
	 * transaction with new extents, then करो the fast path, no need to
	 * worry about logging checksum items with overlapping ranges.
	 */
	अगर (inode->last_reflink_trans < trans->transid)
		वापस btrfs_csum_file_blocks(trans, log_root, sums);

	/*
	 * Serialize logging क्रम checksums. This is to aव्योम racing with the
	 * same checksum being logged by another task that is logging another
	 * file which happens to refer to the same extent as well. Such races
	 * can leave checksum items in the log with overlapping ranges.
	 */
	ret = lock_extent_bits(&log_root->log_csum_range, sums->bytenr,
			       lock_end, &cached_state);
	अगर (ret)
		वापस ret;
	/*
	 * Due to extent cloning, we might have logged a csum item that covers a
	 * subrange of a cloned extent, and later we can end up logging a csum
	 * item क्रम a larger subrange of the same extent or the entire range.
	 * This would leave csum items in the log tree that cover the same range
	 * and अवरोध the searches क्रम checksums in the log tree, resulting in
	 * some checksums missing in the fs/subvolume tree. So just delete (or
	 * trim and adjust) any existing csum items in the log क्रम this range.
	 */
	ret = btrfs_del_csums(trans, log_root, sums->bytenr, sums->len);
	अगर (!ret)
		ret = btrfs_csum_file_blocks(trans, log_root, sums);

	unlock_extent_cached(&log_root->log_csum_range, sums->bytenr, lock_end,
			     &cached_state);

	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक copy_items(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_inode *inode,
			       काष्ठा btrfs_path *dst_path,
			       काष्ठा btrfs_path *src_path,
			       पूर्णांक start_slot, पूर्णांक nr, पूर्णांक inode_only,
			       u64 logged_isize)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	अचिन्हित दीर्घ src_offset;
	अचिन्हित दीर्घ dst_offset;
	काष्ठा btrfs_root *log = inode->root->log_root;
	काष्ठा btrfs_file_extent_item *extent;
	काष्ठा btrfs_inode_item *inode_item;
	काष्ठा extent_buffer *src = src_path->nodes[0];
	पूर्णांक ret;
	काष्ठा btrfs_key *ins_keys;
	u32 *ins_sizes;
	अक्षर *ins_data;
	पूर्णांक i;
	काष्ठा list_head ordered_sums;
	पूर्णांक skip_csum = inode->flags & BTRFS_INODE_NODATASUM;

	INIT_LIST_HEAD(&ordered_sums);

	ins_data = kदो_स्मृति(nr * माप(काष्ठा btrfs_key) +
			   nr * माप(u32), GFP_NOFS);
	अगर (!ins_data)
		वापस -ENOMEM;

	ins_sizes = (u32 *)ins_data;
	ins_keys = (काष्ठा btrfs_key *)(ins_data + nr * माप(u32));

	क्रम (i = 0; i < nr; i++) अणु
		ins_sizes[i] = btrfs_item_size_nr(src, i + start_slot);
		btrfs_item_key_to_cpu(src, ins_keys + i, i + start_slot);
	पूर्ण
	ret = btrfs_insert_empty_items(trans, log, dst_path,
				       ins_keys, ins_sizes, nr);
	अगर (ret) अणु
		kमुक्त(ins_data);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < nr; i++, dst_path->slots[0]++) अणु
		dst_offset = btrfs_item_ptr_offset(dst_path->nodes[0],
						   dst_path->slots[0]);

		src_offset = btrfs_item_ptr_offset(src, start_slot + i);

		अगर (ins_keys[i].type == BTRFS_INODE_ITEM_KEY) अणु
			inode_item = btrfs_item_ptr(dst_path->nodes[0],
						    dst_path->slots[0],
						    काष्ठा btrfs_inode_item);
			fill_inode_item(trans, dst_path->nodes[0], inode_item,
					&inode->vfs_inode,
					inode_only == LOG_INODE_EXISTS,
					logged_isize);
		पूर्ण अन्यथा अणु
			copy_extent_buffer(dst_path->nodes[0], src, dst_offset,
					   src_offset, ins_sizes[i]);
		पूर्ण

		/* take a reference on file data extents so that truncates
		 * or deletes of this inode करोn't have to relog the inode
		 * again
		 */
		अगर (ins_keys[i].type == BTRFS_EXTENT_DATA_KEY &&
		    !skip_csum) अणु
			पूर्णांक found_type;
			extent = btrfs_item_ptr(src, start_slot + i,
						काष्ठा btrfs_file_extent_item);

			अगर (btrfs_file_extent_generation(src, extent) < trans->transid)
				जारी;

			found_type = btrfs_file_extent_type(src, extent);
			अगर (found_type == BTRFS_खाता_EXTENT_REG) अणु
				u64 ds, dl, cs, cl;
				ds = btrfs_file_extent_disk_bytenr(src,
								extent);
				/* ds == 0 is a hole */
				अगर (ds == 0)
					जारी;

				dl = btrfs_file_extent_disk_num_bytes(src,
								extent);
				cs = btrfs_file_extent_offset(src, extent);
				cl = btrfs_file_extent_num_bytes(src,
								extent);
				अगर (btrfs_file_extent_compression(src,
								  extent)) अणु
					cs = 0;
					cl = dl;
				पूर्ण

				ret = btrfs_lookup_csums_range(
						fs_info->csum_root,
						ds + cs, ds + cs + cl - 1,
						&ordered_sums, 0);
				अगर (ret)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	btrfs_mark_buffer_dirty(dst_path->nodes[0]);
	btrfs_release_path(dst_path);
	kमुक्त(ins_data);

	/*
	 * we have to करो this after the loop above to aव्योम changing the
	 * log tree जबतक trying to change the log tree.
	 */
	जबतक (!list_empty(&ordered_sums)) अणु
		काष्ठा btrfs_ordered_sum *sums = list_entry(ordered_sums.next,
						   काष्ठा btrfs_ordered_sum,
						   list);
		अगर (!ret)
			ret = log_csums(trans, inode, log, sums);
		list_del(&sums->list);
		kमुक्त(sums);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक extent_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
		      स्थिर काष्ठा list_head *b)
अणु
	काष्ठा extent_map *em1, *em2;

	em1 = list_entry(a, काष्ठा extent_map, list);
	em2 = list_entry(b, काष्ठा extent_map, list);

	अगर (em1->start < em2->start)
		वापस -1;
	अन्यथा अगर (em1->start > em2->start)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक log_extent_csums(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_inode *inode,
			    काष्ठा btrfs_root *log_root,
			    स्थिर काष्ठा extent_map *em,
			    काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_ordered_extent *ordered;
	u64 csum_offset;
	u64 csum_len;
	u64 mod_start = em->mod_start;
	u64 mod_len = em->mod_len;
	LIST_HEAD(ordered_sums);
	पूर्णांक ret = 0;

	अगर (inode->flags & BTRFS_INODE_NODATASUM ||
	    test_bit(EXTENT_FLAG_PREALLOC, &em->flags) ||
	    em->block_start == EXTENT_MAP_HOLE)
		वापस 0;

	list_क्रम_each_entry(ordered, &ctx->ordered_extents, log_list) अणु
		स्थिर u64 ordered_end = ordered->file_offset + ordered->num_bytes;
		स्थिर u64 mod_end = mod_start + mod_len;
		काष्ठा btrfs_ordered_sum *sums;

		अगर (mod_len == 0)
			अवरोध;

		अगर (ordered_end <= mod_start)
			जारी;
		अगर (mod_end <= ordered->file_offset)
			अवरोध;

		/*
		 * We are going to copy all the csums on this ordered extent, so
		 * go ahead and adjust mod_start and mod_len in हाल this ordered
		 * extent has alपढ़ोy been logged.
		 */
		अगर (ordered->file_offset > mod_start) अणु
			अगर (ordered_end >= mod_end)
				mod_len = ordered->file_offset - mod_start;
			/*
			 * If we have this हाल
			 *
			 * |--------- logged extent ---------|
			 *       |----- ordered extent ----|
			 *
			 * Just करोn't mess with mod_start and mod_len, we'll
			 * just end up logging more csums than we need and it
			 * will be ok.
			 */
		पूर्ण अन्यथा अणु
			अगर (ordered_end < mod_end) अणु
				mod_len = mod_end - ordered_end;
				mod_start = ordered_end;
			पूर्ण अन्यथा अणु
				mod_len = 0;
			पूर्ण
		पूर्ण

		/*
		 * To keep us from looping क्रम the above हाल of an ordered
		 * extent that falls inside of the logged extent.
		 */
		अगर (test_and_set_bit(BTRFS_ORDERED_LOGGED_CSUM, &ordered->flags))
			जारी;

		list_क्रम_each_entry(sums, &ordered->list, list) अणु
			ret = log_csums(trans, inode, log_root, sums);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* We're करोne, found all csums in the ordered extents. */
	अगर (mod_len == 0)
		वापस 0;

	/* If we're compressed we have to save the entire range of csums. */
	अगर (em->compress_type) अणु
		csum_offset = 0;
		csum_len = max(em->block_len, em->orig_block_len);
	पूर्ण अन्यथा अणु
		csum_offset = mod_start - em->start;
		csum_len = mod_len;
	पूर्ण

	/* block start is alपढ़ोy adjusted क्रम the file extent offset. */
	ret = btrfs_lookup_csums_range(trans->fs_info->csum_root,
				       em->block_start + csum_offset,
				       em->block_start + csum_offset +
				       csum_len - 1, &ordered_sums, 0);
	अगर (ret)
		वापस ret;

	जबतक (!list_empty(&ordered_sums)) अणु
		काष्ठा btrfs_ordered_sum *sums = list_entry(ordered_sums.next,
						   काष्ठा btrfs_ordered_sum,
						   list);
		अगर (!ret)
			ret = log_csums(trans, inode, log_root, sums);
		list_del(&sums->list);
		kमुक्त(sums);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक log_one_extent(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_inode *inode, काष्ठा btrfs_root *root,
			  स्थिर काष्ठा extent_map *em,
			  काष्ठा btrfs_path *path,
			  काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_drop_extents_args drop_args = अणु 0 पूर्ण;
	काष्ठा btrfs_root *log = root->log_root;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_map_token token;
	काष्ठा btrfs_key key;
	u64 extent_offset = em->start - em->orig_start;
	u64 block_len;
	पूर्णांक ret;

	ret = log_extent_csums(trans, inode, log, em, ctx);
	अगर (ret)
		वापस ret;

	drop_args.path = path;
	drop_args.start = em->start;
	drop_args.end = em->start + em->len;
	drop_args.replace_extent = true;
	drop_args.extent_item_size = माप(*fi);
	ret = btrfs_drop_extents(trans, log, inode, &drop_args);
	अगर (ret)
		वापस ret;

	अगर (!drop_args.extent_inserted) अणु
		key.objectid = btrfs_ino(inode);
		key.type = BTRFS_EXTENT_DATA_KEY;
		key.offset = em->start;

		ret = btrfs_insert_empty_item(trans, log, path, &key,
					      माप(*fi));
		अगर (ret)
			वापस ret;
	पूर्ण
	leaf = path->nodes[0];
	btrfs_init_map_token(&token, leaf);
	fi = btrfs_item_ptr(leaf, path->slots[0],
			    काष्ठा btrfs_file_extent_item);

	btrfs_set_token_file_extent_generation(&token, fi, trans->transid);
	अगर (test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
		btrfs_set_token_file_extent_type(&token, fi,
						 BTRFS_खाता_EXTENT_PREALLOC);
	अन्यथा
		btrfs_set_token_file_extent_type(&token, fi,
						 BTRFS_खाता_EXTENT_REG);

	block_len = max(em->block_len, em->orig_block_len);
	अगर (em->compress_type != BTRFS_COMPRESS_NONE) अणु
		btrfs_set_token_file_extent_disk_bytenr(&token, fi,
							em->block_start);
		btrfs_set_token_file_extent_disk_num_bytes(&token, fi, block_len);
	पूर्ण अन्यथा अगर (em->block_start < EXTENT_MAP_LAST_BYTE) अणु
		btrfs_set_token_file_extent_disk_bytenr(&token, fi,
							em->block_start -
							extent_offset);
		btrfs_set_token_file_extent_disk_num_bytes(&token, fi, block_len);
	पूर्ण अन्यथा अणु
		btrfs_set_token_file_extent_disk_bytenr(&token, fi, 0);
		btrfs_set_token_file_extent_disk_num_bytes(&token, fi, 0);
	पूर्ण

	btrfs_set_token_file_extent_offset(&token, fi, extent_offset);
	btrfs_set_token_file_extent_num_bytes(&token, fi, em->len);
	btrfs_set_token_file_extent_ram_bytes(&token, fi, em->ram_bytes);
	btrfs_set_token_file_extent_compression(&token, fi, em->compress_type);
	btrfs_set_token_file_extent_encryption(&token, fi, 0);
	btrfs_set_token_file_extent_other_encoding(&token, fi, 0);
	btrfs_mark_buffer_dirty(leaf);

	btrfs_release_path(path);

	वापस ret;
पूर्ण

/*
 * Log all pपुनः_स्मृति extents beyond the inode's i_size to make sure we करो not
 * lose them after करोing a fast fsync and replaying the log. We scan the
 * subvolume's root instead of iterating the inode's extent map tree because
 * otherwise we can log incorrect extent items based on extent map conversion.
 * That can happen due to the fact that extent maps are merged when they
 * are not in the extent map tree's list of modअगरied extents.
 */
अटल पूर्णांक btrfs_log_pपुनः_स्मृति_extents(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_inode *inode,
				      काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_key key;
	स्थिर u64 i_size = i_size_पढ़ो(&inode->vfs_inode);
	स्थिर u64 ino = btrfs_ino(inode);
	काष्ठा btrfs_path *dst_path = शून्य;
	bool dropped_extents = false;
	u64 truncate_offset = i_size;
	काष्ठा extent_buffer *leaf;
	पूर्णांक slot;
	पूर्णांक ins_nr = 0;
	पूर्णांक start_slot;
	पूर्णांक ret;

	अगर (!(inode->flags & BTRFS_INODE_PREALLOC))
		वापस 0;

	key.objectid = ino;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = i_size;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	/*
	 * We must check अगर there is a pपुनः_स्मृति extent that starts beक्रमe the
	 * i_size and crosses the i_size boundary. This is to ensure later we
	 * truncate करोwn to the end of that extent and not to the i_size, as
	 * otherwise we end up losing part of the pपुनः_स्मृति extent after a log
	 * replay and with an implicit hole अगर there is another pपुनः_स्मृति extent
	 * that starts at an offset beyond i_size.
	 */
	ret = btrfs_previous_item(root, path, ino, BTRFS_EXTENT_DATA_KEY);
	अगर (ret < 0)
		जाओ out;

	अगर (ret == 0) अणु
		काष्ठा btrfs_file_extent_item *ei;

		leaf = path->nodes[0];
		slot = path->slots[0];
		ei = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);

		अगर (btrfs_file_extent_type(leaf, ei) ==
		    BTRFS_खाता_EXTENT_PREALLOC) अणु
			u64 extent_end;

			btrfs_item_key_to_cpu(leaf, &key, slot);
			extent_end = key.offset +
				btrfs_file_extent_num_bytes(leaf, ei);

			अगर (extent_end > i_size)
				truncate_offset = extent_end;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	जबतक (true) अणु
		leaf = path->nodes[0];
		slot = path->slots[0];

		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			अगर (ins_nr > 0) अणु
				ret = copy_items(trans, inode, dst_path, path,
						 start_slot, ins_nr, 1, 0);
				अगर (ret < 0)
					जाओ out;
				ins_nr = 0;
			पूर्ण
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अगर (ret > 0) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.objectid > ino)
			अवरोध;
		अगर (WARN_ON_ONCE(key.objectid < ino) ||
		    key.type < BTRFS_EXTENT_DATA_KEY ||
		    key.offset < i_size) अणु
			path->slots[0]++;
			जारी;
		पूर्ण
		अगर (!dropped_extents) अणु
			/*
			 * Aव्योम logging extent items logged in past fsync calls
			 * and leading to duplicate keys in the log tree.
			 */
			करो अणु
				ret = btrfs_truncate_inode_items(trans,
							 root->log_root,
							 inode, truncate_offset,
							 BTRFS_EXTENT_DATA_KEY);
			पूर्ण जबतक (ret == -EAGAIN);
			अगर (ret)
				जाओ out;
			dropped_extents = true;
		पूर्ण
		अगर (ins_nr == 0)
			start_slot = slot;
		ins_nr++;
		path->slots[0]++;
		अगर (!dst_path) अणु
			dst_path = btrfs_alloc_path();
			अगर (!dst_path) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (ins_nr > 0)
		ret = copy_items(trans, inode, dst_path, path,
				 start_slot, ins_nr, 1, 0);
out:
	btrfs_release_path(path);
	btrfs_मुक्त_path(dst_path);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_log_changed_extents(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_root *root,
				     काष्ठा btrfs_inode *inode,
				     काष्ठा btrfs_path *path,
				     काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_ordered_extent *ordered;
	काष्ठा btrfs_ordered_extent *पंचांगp;
	काष्ठा extent_map *em, *n;
	काष्ठा list_head extents;
	काष्ठा extent_map_tree *tree = &inode->extent_tree;
	पूर्णांक ret = 0;
	पूर्णांक num = 0;

	INIT_LIST_HEAD(&extents);

	ग_लिखो_lock(&tree->lock);

	list_क्रम_each_entry_safe(em, n, &tree->modअगरied_extents, list) अणु
		list_del_init(&em->list);
		/*
		 * Just an arbitrary number, this can be really CPU पूर्णांकensive
		 * once we start getting a lot of extents, and really once we
		 * have a bunch of extents we just want to commit since it will
		 * be faster.
		 */
		अगर (++num > 32768) अणु
			list_del_init(&tree->modअगरied_extents);
			ret = -EFBIG;
			जाओ process;
		पूर्ण

		अगर (em->generation < trans->transid)
			जारी;

		/* We log pपुनः_स्मृति extents beyond eof later. */
		अगर (test_bit(EXTENT_FLAG_PREALLOC, &em->flags) &&
		    em->start >= i_size_पढ़ो(&inode->vfs_inode))
			जारी;

		/* Need a ref to keep it from getting evicted from cache */
		refcount_inc(&em->refs);
		set_bit(EXTENT_FLAG_LOGGING, &em->flags);
		list_add_tail(&em->list, &extents);
		num++;
	पूर्ण

	list_sort(शून्य, &extents, extent_cmp);
process:
	जबतक (!list_empty(&extents)) अणु
		em = list_entry(extents.next, काष्ठा extent_map, list);

		list_del_init(&em->list);

		/*
		 * If we had an error we just need to delete everybody from our
		 * निजी list.
		 */
		अगर (ret) अणु
			clear_em_logging(tree, em);
			मुक्त_extent_map(em);
			जारी;
		पूर्ण

		ग_लिखो_unlock(&tree->lock);

		ret = log_one_extent(trans, inode, root, em, path, ctx);
		ग_लिखो_lock(&tree->lock);
		clear_em_logging(tree, em);
		मुक्त_extent_map(em);
	पूर्ण
	WARN_ON(!list_empty(&extents));
	ग_लिखो_unlock(&tree->lock);

	btrfs_release_path(path);
	अगर (!ret)
		ret = btrfs_log_pपुनः_स्मृति_extents(trans, inode, path);
	अगर (ret)
		वापस ret;

	/*
	 * We have logged all extents successfully, now make sure the commit of
	 * the current transaction रुकोs क्रम the ordered extents to complete
	 * beक्रमe it commits and wipes out the log trees, otherwise we would
	 * lose data अगर an ordered extents completes after the transaction
	 * commits and a घातer failure happens after the transaction commit.
	 */
	list_क्रम_each_entry_safe(ordered, पंचांगp, &ctx->ordered_extents, log_list) अणु
		list_del_init(&ordered->log_list);
		set_bit(BTRFS_ORDERED_LOGGED, &ordered->flags);

		अगर (!test_bit(BTRFS_ORDERED_COMPLETE, &ordered->flags)) अणु
			spin_lock_irq(&inode->ordered_tree.lock);
			अगर (!test_bit(BTRFS_ORDERED_COMPLETE, &ordered->flags)) अणु
				set_bit(BTRFS_ORDERED_PENDING, &ordered->flags);
				atomic_inc(&trans->transaction->pending_ordered);
			पूर्ण
			spin_unlock_irq(&inode->ordered_tree.lock);
		पूर्ण
		btrfs_put_ordered_extent(ordered);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक logged_inode_size(काष्ठा btrfs_root *log, काष्ठा btrfs_inode *inode,
			     काष्ठा btrfs_path *path, u64 *size_ret)
अणु
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	key.objectid = btrfs_ino(inode);
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, log, &key, path, 0, 0);
	अगर (ret < 0) अणु
		वापस ret;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		*size_ret = 0;
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_inode_item *item;

		item = btrfs_item_ptr(path->nodes[0], path->slots[0],
				      काष्ठा btrfs_inode_item);
		*size_ret = btrfs_inode_size(path->nodes[0], item);
		/*
		 * If the in-memory inode's i_size is smaller then the inode
		 * size stored in the btree, वापस the inode's i_size, so
		 * that we get a correct inode size after replaying the log
		 * when beक्रमe a घातer failure we had a shrinking truncate
		 * followed by addition of a new name (नाम / new hard link).
		 * Otherwise वापस the inode size from the btree, to aव्योम
		 * data loss when replaying a log due to previously करोing a
		 * ग_लिखो that expands the inode's size and logging a new name
		 * immediately after.
		 */
		अगर (*size_ret > inode->vfs_inode.i_size)
			*size_ret = inode->vfs_inode.i_size;
	पूर्ण

	btrfs_release_path(path);
	वापस 0;
पूर्ण

/*
 * At the moment we always log all xattrs. This is to figure out at log replay
 * समय which xattrs must have their deletion replayed. If a xattr is missing
 * in the log tree and exists in the fs/subvol tree, we delete it. This is
 * because अगर a xattr is deleted, the inode is fsynced and a घातer failure
 * happens, causing the log to be replayed the next समय the fs is mounted,
 * we want the xattr to not exist anymore (same behaviour as other fileप्रणालीs
 * with a journal, ext3/4, xfs, f2fs, etc).
 */
अटल पूर्णांक btrfs_log_all_xattrs(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root,
				काष्ठा btrfs_inode *inode,
				काष्ठा btrfs_path *path,
				काष्ठा btrfs_path *dst_path)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	स्थिर u64 ino = btrfs_ino(inode);
	पूर्णांक ins_nr = 0;
	पूर्णांक start_slot = 0;
	bool found_xattrs = false;

	अगर (test_bit(BTRFS_INODE_NO_XATTRS, &inode->runसमय_flags))
		वापस 0;

	key.objectid = ino;
	key.type = BTRFS_XATTR_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;

	जबतक (true) अणु
		पूर्णांक slot = path->slots[0];
		काष्ठा extent_buffer *leaf = path->nodes[0];
		पूर्णांक nritems = btrfs_header_nritems(leaf);

		अगर (slot >= nritems) अणु
			अगर (ins_nr > 0) अणु
				ret = copy_items(trans, inode, dst_path, path,
						 start_slot, ins_nr, 1, 0);
				अगर (ret < 0)
					वापस ret;
				ins_nr = 0;
			पूर्ण
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				वापस ret;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.objectid != ino || key.type != BTRFS_XATTR_ITEM_KEY)
			अवरोध;

		अगर (ins_nr == 0)
			start_slot = slot;
		ins_nr++;
		path->slots[0]++;
		found_xattrs = true;
		cond_resched();
	पूर्ण
	अगर (ins_nr > 0) अणु
		ret = copy_items(trans, inode, dst_path, path,
				 start_slot, ins_nr, 1, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!found_xattrs)
		set_bit(BTRFS_INODE_NO_XATTRS, &inode->runसमय_flags);

	वापस 0;
पूर्ण

/*
 * When using the NO_HOLES feature अगर we punched a hole that causes the
 * deletion of entire leafs or all the extent items of the first leaf (the one
 * that contains the inode item and references) we may end up not processing
 * any extents, because there are no leafs with a generation matching the
 * current transaction that have extent items क्रम our inode. So we need to find
 * अगर any holes exist and then log them. We also need to log holes after any
 * truncate operation that changes the inode's size.
 */
अटल पूर्णांक btrfs_log_holes(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   काष्ठा btrfs_inode *inode,
			   काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_key key;
	स्थिर u64 ino = btrfs_ino(inode);
	स्थिर u64 i_size = i_size_पढ़ो(&inode->vfs_inode);
	u64 prev_extent_end = 0;
	पूर्णांक ret;

	अगर (!btrfs_fs_incompat(fs_info, NO_HOLES) || i_size == 0)
		वापस 0;

	key.objectid = ino;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;

	जबतक (true) अणु
		काष्ठा extent_buffer *leaf = path->nodes[0];

		अगर (path->slots[0] >= btrfs_header_nritems(path->nodes[0])) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				वापस ret;
			अगर (ret > 0) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			leaf = path->nodes[0];
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		अगर (key.objectid != ino || key.type != BTRFS_EXTENT_DATA_KEY)
			अवरोध;

		/* We have a hole, log it. */
		अगर (prev_extent_end < key.offset) अणु
			स्थिर u64 hole_len = key.offset - prev_extent_end;

			/*
			 * Release the path to aव्योम deadlocks with other code
			 * paths that search the root जबतक holding locks on
			 * leafs from the log root.
			 */
			btrfs_release_path(path);
			ret = btrfs_insert_file_extent(trans, root->log_root,
						       ino, prev_extent_end, 0,
						       0, hole_len, 0, hole_len,
						       0, 0, 0);
			अगर (ret < 0)
				वापस ret;

			/*
			 * Search क्रम the same key again in the root. Since it's
			 * an extent item and we are holding the inode lock, the
			 * key must still exist. If it करोesn't just emit warning
			 * and वापस an error to fall back to a transaction
			 * commit.
			 */
			ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
			अगर (ret < 0)
				वापस ret;
			अगर (WARN_ON(ret > 0))
				वापस -ENOENT;
			leaf = path->nodes[0];
		पूर्ण

		prev_extent_end = btrfs_file_extent_end(path);
		path->slots[0]++;
		cond_resched();
	पूर्ण

	अगर (prev_extent_end < i_size) अणु
		u64 hole_len;

		btrfs_release_path(path);
		hole_len = ALIGN(i_size - prev_extent_end, fs_info->sectorsize);
		ret = btrfs_insert_file_extent(trans, root->log_root,
					       ino, prev_extent_end, 0, 0,
					       hole_len, 0, hole_len,
					       0, 0, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * When we are logging a new inode X, check अगर it करोesn't have a reference that
 * matches the reference from some other inode Y created in a past transaction
 * and that was नामd in the current transaction. If we करोn't करो this, then at
 * log replay समय we can lose inode Y (and all its files अगर it's a directory):
 *
 * सूची_गढ़ो /mnt/x
 * echo "hello world" > /mnt/x/foobar
 * sync
 * mv /mnt/x /mnt/y
 * सूची_गढ़ो /mnt/x                 # or touch /mnt/x
 * xfs_io -c fsync /mnt/x
 * <घातer fail>
 * mount fs, trigger log replay
 *
 * After the log replay procedure, we would lose the first directory and all its
 * files (file foobar).
 * For the हाल where inode Y is not a directory we simply end up losing it:
 *
 * echo "123" > /mnt/foo
 * sync
 * mv /mnt/foo /mnt/bar
 * echo "abc" > /mnt/foo
 * xfs_io -c fsync /mnt/foo
 * <घातer fail>
 *
 * We also need this क्रम हालs where a snapshot entry is replaced by some other
 * entry (file or directory) otherwise we end up with an unreplayable log due to
 * attempts to delete the snapshot entry (entry of type BTRFS_ROOT_ITEM_KEY) as
 * अगर it were a regular entry:
 *
 * सूची_गढ़ो /mnt/x
 * btrfs subvolume snapshot /mnt /mnt/x/snap
 * btrfs subvolume delete /mnt/x/snap
 * सूची_हटाओ /mnt/x
 * सूची_गढ़ो /mnt/x
 * fsync /mnt/x or fsync some new file inside it
 * <घातer fail>
 *
 * The snapshot delete, सूची_हटाओ of x, सूची_गढ़ो of a new x and the fsync all happen in
 * the same transaction.
 */
अटल पूर्णांक btrfs_check_ref_name_override(काष्ठा extent_buffer *eb,
					 स्थिर पूर्णांक slot,
					 स्थिर काष्ठा btrfs_key *key,
					 काष्ठा btrfs_inode *inode,
					 u64 *other_ino, u64 *other_parent)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_path *search_path;
	अक्षर *name = शून्य;
	u32 name_len = 0;
	u32 item_size = btrfs_item_size_nr(eb, slot);
	u32 cur_offset = 0;
	अचिन्हित दीर्घ ptr = btrfs_item_ptr_offset(eb, slot);

	search_path = btrfs_alloc_path();
	अगर (!search_path)
		वापस -ENOMEM;
	search_path->search_commit_root = 1;
	search_path->skip_locking = 1;

	जबतक (cur_offset < item_size) अणु
		u64 parent;
		u32 this_name_len;
		u32 this_len;
		अचिन्हित दीर्घ name_ptr;
		काष्ठा btrfs_dir_item *di;

		अगर (key->type == BTRFS_INODE_REF_KEY) अणु
			काष्ठा btrfs_inode_ref *iref;

			iref = (काष्ठा btrfs_inode_ref *)(ptr + cur_offset);
			parent = key->offset;
			this_name_len = btrfs_inode_ref_name_len(eb, iref);
			name_ptr = (अचिन्हित दीर्घ)(iref + 1);
			this_len = माप(*iref) + this_name_len;
		पूर्ण अन्यथा अणु
			काष्ठा btrfs_inode_extref *extref;

			extref = (काष्ठा btrfs_inode_extref *)(ptr +
							       cur_offset);
			parent = btrfs_inode_extref_parent(eb, extref);
			this_name_len = btrfs_inode_extref_name_len(eb, extref);
			name_ptr = (अचिन्हित दीर्घ)&extref->name;
			this_len = माप(*extref) + this_name_len;
		पूर्ण

		अगर (this_name_len > name_len) अणु
			अक्षर *new_name;

			new_name = kपुनः_स्मृति(name, this_name_len, GFP_NOFS);
			अगर (!new_name) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			name_len = this_name_len;
			name = new_name;
		पूर्ण

		पढ़ो_extent_buffer(eb, name, name_ptr, this_name_len);
		di = btrfs_lookup_dir_item(शून्य, inode->root, search_path,
				parent, name, this_name_len, 0);
		अगर (di && !IS_ERR(di)) अणु
			काष्ठा btrfs_key di_key;

			btrfs_dir_item_key_to_cpu(search_path->nodes[0],
						  di, &di_key);
			अगर (di_key.type == BTRFS_INODE_ITEM_KEY) अणु
				अगर (di_key.objectid != key->objectid) अणु
					ret = 1;
					*other_ino = di_key.objectid;
					*other_parent = parent;
				पूर्ण अन्यथा अणु
					ret = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				ret = -EAGAIN;
			पूर्ण
			जाओ out;
		पूर्ण अन्यथा अगर (IS_ERR(di)) अणु
			ret = PTR_ERR(di);
			जाओ out;
		पूर्ण
		btrfs_release_path(search_path);

		cur_offset += this_len;
	पूर्ण
	ret = 0;
out:
	btrfs_मुक्त_path(search_path);
	kमुक्त(name);
	वापस ret;
पूर्ण

काष्ठा btrfs_ino_list अणु
	u64 ino;
	u64 parent;
	काष्ठा list_head list;
पूर्ण;

अटल पूर्णांक log_conflicting_inodes(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_root *root,
				  काष्ठा btrfs_path *path,
				  काष्ठा btrfs_log_ctx *ctx,
				  u64 ino, u64 parent)
अणु
	काष्ठा btrfs_ino_list *ino_elem;
	LIST_HEAD(inode_list);
	पूर्णांक ret = 0;

	ino_elem = kदो_स्मृति(माप(*ino_elem), GFP_NOFS);
	अगर (!ino_elem)
		वापस -ENOMEM;
	ino_elem->ino = ino;
	ino_elem->parent = parent;
	list_add_tail(&ino_elem->list, &inode_list);

	जबतक (!list_empty(&inode_list)) अणु
		काष्ठा btrfs_fs_info *fs_info = root->fs_info;
		काष्ठा btrfs_key key;
		काष्ठा inode *inode;

		ino_elem = list_first_entry(&inode_list, काष्ठा btrfs_ino_list,
					    list);
		ino = ino_elem->ino;
		parent = ino_elem->parent;
		list_del(&ino_elem->list);
		kमुक्त(ino_elem);
		अगर (ret)
			जारी;

		btrfs_release_path(path);

		inode = btrfs_iget(fs_info->sb, ino, root);
		/*
		 * If the other inode that had a conflicting dir entry was
		 * deleted in the current transaction, we need to log its parent
		 * directory.
		 */
		अगर (IS_ERR(inode)) अणु
			ret = PTR_ERR(inode);
			अगर (ret == -ENOENT) अणु
				inode = btrfs_iget(fs_info->sb, parent, root);
				अगर (IS_ERR(inode)) अणु
					ret = PTR_ERR(inode);
				पूर्ण अन्यथा अणु
					ret = btrfs_log_inode(trans, root,
						      BTRFS_I(inode),
						      LOG_OTHER_INODE_ALL,
						      ctx);
					btrfs_add_delayed_iput(inode);
				पूर्ण
			पूर्ण
			जारी;
		पूर्ण
		/*
		 * If the inode was alपढ़ोy logged skip it - otherwise we can
		 * hit an infinite loop. Example:
		 *
		 * From the commit root (previous transaction) we have the
		 * following inodes:
		 *
		 * inode 257 a directory
		 * inode 258 with references "zz" and "zz_link" on inode 257
		 * inode 259 with reference "a" on inode 257
		 *
		 * And in the current (uncommitted) transaction we have:
		 *
		 * inode 257 a directory, unchanged
		 * inode 258 with references "a" and "a2" on inode 257
		 * inode 259 with reference "zz_link" on inode 257
		 * inode 261 with reference "zz" on inode 257
		 *
		 * When logging inode 261 the following infinite loop could
		 * happen अगर we करोn't skip alपढ़ोy logged inodes:
		 *
		 * - we detect inode 258 as a conflicting inode, with inode 261
		 *   on reference "zz", and log it;
		 *
		 * - we detect inode 259 as a conflicting inode, with inode 258
		 *   on reference "a", and log it;
		 *
		 * - we detect inode 258 as a conflicting inode, with inode 259
		 *   on reference "zz_link", and log it - again! After this we
		 *   repeat the above steps क्रमever.
		 */
		spin_lock(&BTRFS_I(inode)->lock);
		/*
		 * Check the inode's logged_trans only instead of
		 * btrfs_inode_in_log(). This is because the last_log_commit of
		 * the inode is not updated when we only log that it exists and
		 * it has the full sync bit set (see btrfs_log_inode()).
		 */
		अगर (BTRFS_I(inode)->logged_trans == trans->transid) अणु
			spin_unlock(&BTRFS_I(inode)->lock);
			btrfs_add_delayed_iput(inode);
			जारी;
		पूर्ण
		spin_unlock(&BTRFS_I(inode)->lock);
		/*
		 * We are safe logging the other inode without acquiring its
		 * lock as दीर्घ as we log with the LOG_INODE_EXISTS mode. We
		 * are safe against concurrent नामs of the other inode as
		 * well because during a नाम we pin the log and update the
		 * log with the new name beक्रमe we unpin it.
		 */
		ret = btrfs_log_inode(trans, root, BTRFS_I(inode),
				      LOG_OTHER_INODE, ctx);
		अगर (ret) अणु
			btrfs_add_delayed_iput(inode);
			जारी;
		पूर्ण

		key.objectid = ino;
		key.type = BTRFS_INODE_REF_KEY;
		key.offset = 0;
		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0) अणु
			btrfs_add_delayed_iput(inode);
			जारी;
		पूर्ण

		जबतक (true) अणु
			काष्ठा extent_buffer *leaf = path->nodes[0];
			पूर्णांक slot = path->slots[0];
			u64 other_ino = 0;
			u64 other_parent = 0;

			अगर (slot >= btrfs_header_nritems(leaf)) अणु
				ret = btrfs_next_leaf(root, path);
				अगर (ret < 0) अणु
					अवरोध;
				पूर्ण अन्यथा अगर (ret > 0) अणु
					ret = 0;
					अवरोध;
				पूर्ण
				जारी;
			पूर्ण

			btrfs_item_key_to_cpu(leaf, &key, slot);
			अगर (key.objectid != ino ||
			    (key.type != BTRFS_INODE_REF_KEY &&
			     key.type != BTRFS_INODE_EXTREF_KEY)) अणु
				ret = 0;
				अवरोध;
			पूर्ण

			ret = btrfs_check_ref_name_override(leaf, slot, &key,
					BTRFS_I(inode), &other_ino,
					&other_parent);
			अगर (ret < 0)
				अवरोध;
			अगर (ret > 0) अणु
				ino_elem = kदो_स्मृति(माप(*ino_elem), GFP_NOFS);
				अगर (!ino_elem) अणु
					ret = -ENOMEM;
					अवरोध;
				पूर्ण
				ino_elem->ino = other_ino;
				ino_elem->parent = other_parent;
				list_add_tail(&ino_elem->list, &inode_list);
				ret = 0;
			पूर्ण
			path->slots[0]++;
		पूर्ण
		btrfs_add_delayed_iput(inode);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक copy_inode_items_to_log(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_inode *inode,
				   काष्ठा btrfs_key *min_key,
				   स्थिर काष्ठा btrfs_key *max_key,
				   काष्ठा btrfs_path *path,
				   काष्ठा btrfs_path *dst_path,
				   स्थिर u64 logged_isize,
				   स्थिर bool recursive_logging,
				   स्थिर पूर्णांक inode_only,
				   काष्ठा btrfs_log_ctx *ctx,
				   bool *need_log_inode_item)
अणु
	काष्ठा btrfs_root *root = inode->root;
	पूर्णांक ins_start_slot = 0;
	पूर्णांक ins_nr = 0;
	पूर्णांक ret;

	जबतक (1) अणु
		ret = btrfs_search_क्रमward(root, min_key, path, trans->transid);
		अगर (ret < 0)
			वापस ret;
		अगर (ret > 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
again:
		/* Note, ins_nr might be > 0 here, cleanup outside the loop */
		अगर (min_key->objectid != max_key->objectid)
			अवरोध;
		अगर (min_key->type > max_key->type)
			अवरोध;

		अगर (min_key->type == BTRFS_INODE_ITEM_KEY)
			*need_log_inode_item = false;

		अगर ((min_key->type == BTRFS_INODE_REF_KEY ||
		     min_key->type == BTRFS_INODE_EXTREF_KEY) &&
		    inode->generation == trans->transid &&
		    !recursive_logging) अणु
			u64 other_ino = 0;
			u64 other_parent = 0;

			ret = btrfs_check_ref_name_override(path->nodes[0],
					path->slots[0], min_key, inode,
					&other_ino, &other_parent);
			अगर (ret < 0) अणु
				वापस ret;
			पूर्ण अन्यथा अगर (ret > 0 && ctx &&
				   other_ino != btrfs_ino(BTRFS_I(ctx->inode))) अणु
				अगर (ins_nr > 0) अणु
					ins_nr++;
				पूर्ण अन्यथा अणु
					ins_nr = 1;
					ins_start_slot = path->slots[0];
				पूर्ण
				ret = copy_items(trans, inode, dst_path, path,
						 ins_start_slot, ins_nr,
						 inode_only, logged_isize);
				अगर (ret < 0)
					वापस ret;
				ins_nr = 0;

				ret = log_conflicting_inodes(trans, root, path,
						ctx, other_ino, other_parent);
				अगर (ret)
					वापस ret;
				btrfs_release_path(path);
				जाओ next_key;
			पूर्ण
		पूर्ण

		/* Skip xattrs, we log them later with btrfs_log_all_xattrs() */
		अगर (min_key->type == BTRFS_XATTR_ITEM_KEY) अणु
			अगर (ins_nr == 0)
				जाओ next_slot;
			ret = copy_items(trans, inode, dst_path, path,
					 ins_start_slot,
					 ins_nr, inode_only, logged_isize);
			अगर (ret < 0)
				वापस ret;
			ins_nr = 0;
			जाओ next_slot;
		पूर्ण

		अगर (ins_nr && ins_start_slot + ins_nr == path->slots[0]) अणु
			ins_nr++;
			जाओ next_slot;
		पूर्ण अन्यथा अगर (!ins_nr) अणु
			ins_start_slot = path->slots[0];
			ins_nr = 1;
			जाओ next_slot;
		पूर्ण

		ret = copy_items(trans, inode, dst_path, path, ins_start_slot,
				 ins_nr, inode_only, logged_isize);
		अगर (ret < 0)
			वापस ret;
		ins_nr = 1;
		ins_start_slot = path->slots[0];
next_slot:
		path->slots[0]++;
		अगर (path->slots[0] < btrfs_header_nritems(path->nodes[0])) अणु
			btrfs_item_key_to_cpu(path->nodes[0], min_key,
					      path->slots[0]);
			जाओ again;
		पूर्ण
		अगर (ins_nr) अणु
			ret = copy_items(trans, inode, dst_path, path,
					 ins_start_slot, ins_nr, inode_only,
					 logged_isize);
			अगर (ret < 0)
				वापस ret;
			ins_nr = 0;
		पूर्ण
		btrfs_release_path(path);
next_key:
		अगर (min_key->offset < (u64)-1) अणु
			min_key->offset++;
		पूर्ण अन्यथा अगर (min_key->type < max_key->type) अणु
			min_key->type++;
			min_key->offset = 0;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ins_nr)
		ret = copy_items(trans, inode, dst_path, path, ins_start_slot,
				 ins_nr, inode_only, logged_isize);

	वापस ret;
पूर्ण

/* log a single inode in the tree log.
 * At least one parent directory क्रम this inode must exist in the tree
 * or be logged alपढ़ोy.
 *
 * Any items from this inode changed by the current transaction are copied
 * to the log tree.  An extra reference is taken on any extents in this
 * file, allowing us to aव्योम a whole pile of corner हालs around logging
 * blocks that have been हटाओd from the tree.
 *
 * See LOG_INODE_ALL and related defines क्रम a description of what inode_only
 * करोes.
 *
 * This handles both files and directories.
 */
अटल पूर्णांक btrfs_log_inode(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root, काष्ठा btrfs_inode *inode,
			   पूर्णांक inode_only,
			   काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_path *dst_path;
	काष्ठा btrfs_key min_key;
	काष्ठा btrfs_key max_key;
	काष्ठा btrfs_root *log = root->log_root;
	पूर्णांक err = 0;
	पूर्णांक ret = 0;
	bool fast_search = false;
	u64 ino = btrfs_ino(inode);
	काष्ठा extent_map_tree *em_tree = &inode->extent_tree;
	u64 logged_isize = 0;
	bool need_log_inode_item = true;
	bool xattrs_logged = false;
	bool recursive_logging = false;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	dst_path = btrfs_alloc_path();
	अगर (!dst_path) अणु
		btrfs_मुक्त_path(path);
		वापस -ENOMEM;
	पूर्ण

	min_key.objectid = ino;
	min_key.type = BTRFS_INODE_ITEM_KEY;
	min_key.offset = 0;

	max_key.objectid = ino;


	/* today the code can only करो partial logging of directories */
	अगर (S_ISसूची(inode->vfs_inode.i_mode) ||
	    (!test_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
		       &inode->runसमय_flags) &&
	     inode_only >= LOG_INODE_EXISTS))
		max_key.type = BTRFS_XATTR_ITEM_KEY;
	अन्यथा
		max_key.type = (u8)-1;
	max_key.offset = (u64)-1;

	/*
	 * Only run delayed items अगर we are a directory. We want to make sure
	 * all directory indexes hit the fs/subvolume tree so we can find them
	 * and figure out which index ranges have to be logged.
	 *
	 * Otherwise commit the delayed inode only अगर the full sync flag is set,
	 * as we want to make sure an up to date version is in the subvolume
	 * tree so copy_inode_items_to_log() / copy_items() can find it and copy
	 * it to the log tree. For a non full sync, we always log the inode item
	 * based on the in-memory काष्ठा btrfs_inode which is always up to date.
	 */
	अगर (S_ISसूची(inode->vfs_inode.i_mode))
		ret = btrfs_commit_inode_delayed_items(trans, inode);
	अन्यथा अगर (test_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &inode->runसमय_flags))
		ret = btrfs_commit_inode_delayed_inode(inode);

	अगर (ret) अणु
		btrfs_मुक्त_path(path);
		btrfs_मुक्त_path(dst_path);
		वापस ret;
	पूर्ण

	अगर (inode_only == LOG_OTHER_INODE || inode_only == LOG_OTHER_INODE_ALL) अणु
		recursive_logging = true;
		अगर (inode_only == LOG_OTHER_INODE)
			inode_only = LOG_INODE_EXISTS;
		अन्यथा
			inode_only = LOG_INODE_ALL;
		mutex_lock_nested(&inode->log_mutex, SINGLE_DEPTH_NESTING);
	पूर्ण अन्यथा अणु
		mutex_lock(&inode->log_mutex);
	पूर्ण

	/*
	 * This is क्रम हालs where logging a directory could result in losing a
	 * a file after replaying the log. For example, अगर we move a file from a
	 * directory A to a directory B, then fsync directory A, we have no way
	 * to known the file was moved from A to B, so logging just A would
	 * result in losing the file after a log replay.
	 */
	अगर (S_ISसूची(inode->vfs_inode.i_mode) &&
	    inode_only == LOG_INODE_ALL &&
	    inode->last_unlink_trans >= trans->transid) अणु
		btrfs_set_log_full_commit(trans);
		err = 1;
		जाओ out_unlock;
	पूर्ण

	/*
	 * a brute क्रमce approach to making sure we get the most uptodate
	 * copies of everything.
	 */
	अगर (S_ISसूची(inode->vfs_inode.i_mode)) अणु
		पूर्णांक max_key_type = BTRFS_सूची_LOG_INDEX_KEY;

		clear_bit(BTRFS_INODE_COPY_EVERYTHING, &inode->runसमय_flags);
		अगर (inode_only == LOG_INODE_EXISTS)
			max_key_type = BTRFS_XATTR_ITEM_KEY;
		ret = drop_objectid_items(trans, log, path, ino, max_key_type);
	पूर्ण अन्यथा अणु
		अगर (inode_only == LOG_INODE_EXISTS) अणु
			/*
			 * Make sure the new inode item we ग_लिखो to the log has
			 * the same isize as the current one (अगर it exists).
			 * This is necessary to prevent data loss after log
			 * replay, and also to prevent करोing a wrong expanding
			 * truncate - क्रम e.g. create file, ग_लिखो 4K पूर्णांकo offset
			 * 0, fsync, ग_लिखो 4K पूर्णांकo offset 4096, add hard link,
			 * fsync some other file (to sync log), घातer fail - अगर
			 * we use the inode's current i_size, after log replay
			 * we get a 8Kb file, with the last 4Kb extent as a hole
			 * (zeroes), as अगर an expanding truncate happened,
			 * instead of getting a file of 4Kb only.
			 */
			err = logged_inode_size(log, inode, path, &logged_isize);
			अगर (err)
				जाओ out_unlock;
		पूर्ण
		अगर (test_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
			     &inode->runसमय_flags)) अणु
			अगर (inode_only == LOG_INODE_EXISTS) अणु
				max_key.type = BTRFS_XATTR_ITEM_KEY;
				ret = drop_objectid_items(trans, log, path, ino,
							  max_key.type);
			पूर्ण अन्यथा अणु
				clear_bit(BTRFS_INODE_NEEDS_FULL_SYNC,
					  &inode->runसमय_flags);
				clear_bit(BTRFS_INODE_COPY_EVERYTHING,
					  &inode->runसमय_flags);
				जबतक(1) अणु
					ret = btrfs_truncate_inode_items(trans,
						log, inode, 0, 0);
					अगर (ret != -EAGAIN)
						अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (test_and_clear_bit(BTRFS_INODE_COPY_EVERYTHING,
					      &inode->runसमय_flags) ||
			   inode_only == LOG_INODE_EXISTS) अणु
			अगर (inode_only == LOG_INODE_ALL)
				fast_search = true;
			max_key.type = BTRFS_XATTR_ITEM_KEY;
			ret = drop_objectid_items(trans, log, path, ino,
						  max_key.type);
		पूर्ण अन्यथा अणु
			अगर (inode_only == LOG_INODE_ALL)
				fast_search = true;
			जाओ log_extents;
		पूर्ण

	पूर्ण
	अगर (ret) अणु
		err = ret;
		जाओ out_unlock;
	पूर्ण

	err = copy_inode_items_to_log(trans, inode, &min_key, &max_key,
				      path, dst_path, logged_isize,
				      recursive_logging, inode_only, ctx,
				      &need_log_inode_item);
	अगर (err)
		जाओ out_unlock;

	btrfs_release_path(path);
	btrfs_release_path(dst_path);
	err = btrfs_log_all_xattrs(trans, root, inode, path, dst_path);
	अगर (err)
		जाओ out_unlock;
	xattrs_logged = true;
	अगर (max_key.type >= BTRFS_EXTENT_DATA_KEY && !fast_search) अणु
		btrfs_release_path(path);
		btrfs_release_path(dst_path);
		err = btrfs_log_holes(trans, root, inode, path);
		अगर (err)
			जाओ out_unlock;
	पूर्ण
log_extents:
	btrfs_release_path(path);
	btrfs_release_path(dst_path);
	अगर (need_log_inode_item) अणु
		err = log_inode_item(trans, log, dst_path, inode);
		अगर (!err && !xattrs_logged) अणु
			err = btrfs_log_all_xattrs(trans, root, inode, path,
						   dst_path);
			btrfs_release_path(path);
		पूर्ण
		अगर (err)
			जाओ out_unlock;
	पूर्ण
	अगर (fast_search) अणु
		ret = btrfs_log_changed_extents(trans, root, inode, dst_path,
						ctx);
		अगर (ret) अणु
			err = ret;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अगर (inode_only == LOG_INODE_ALL) अणु
		काष्ठा extent_map *em, *n;

		ग_लिखो_lock(&em_tree->lock);
		list_क्रम_each_entry_safe(em, n, &em_tree->modअगरied_extents, list)
			list_del_init(&em->list);
		ग_लिखो_unlock(&em_tree->lock);
	पूर्ण

	अगर (inode_only == LOG_INODE_ALL && S_ISसूची(inode->vfs_inode.i_mode)) अणु
		ret = log_directory_changes(trans, root, inode, path, dst_path,
					ctx);
		अगर (ret) अणु
			err = ret;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/*
	 * If we are logging that an ancestor inode exists as part of logging a
	 * new name from a link or नाम operation, करोn't mark the inode as
	 * logged - otherwise अगर an explicit fsync is made against an ancestor,
	 * the fsync considers the inode in the log and करोesn't sync the log,
	 * resulting in the ancestor missing after a घातer failure unless the
	 * log was synced as part of an fsync against any other unrelated inode.
	 * So keep it simple क्रम this हाल and just करोn't flag the ancestors as
	 * logged.
	 */
	अगर (!ctx ||
	    !(S_ISसूची(inode->vfs_inode.i_mode) && ctx->logging_new_name &&
	      &inode->vfs_inode != ctx->inode)) अणु
		spin_lock(&inode->lock);
		inode->logged_trans = trans->transid;
		/*
		 * Don't update last_log_commit अगर we logged that an inode exists
		 * after it was loaded to memory (full_sync bit set).
		 * This is to prevent data loss when we करो a ग_लिखो to the inode,
		 * then the inode माला_लो evicted after all delalloc was flushed,
		 * then we log it exists (due to a नाम क्रम example) and then
		 * fsync it. This last fsync would करो nothing (not logging the
		 * extents previously written).
		 */
		अगर (inode_only != LOG_INODE_EXISTS ||
		    !test_bit(BTRFS_INODE_NEEDS_FULL_SYNC, &inode->runसमय_flags))
			inode->last_log_commit = inode->last_sub_trans;
		spin_unlock(&inode->lock);
	पूर्ण
out_unlock:
	mutex_unlock(&inode->log_mutex);

	btrfs_मुक्त_path(path);
	btrfs_मुक्त_path(dst_path);
	वापस err;
पूर्ण

/*
 * Check अगर we need to log an inode. This is used in contexts where जबतक
 * logging an inode we need to log another inode (either that it exists or in
 * full mode). This is used instead of btrfs_inode_in_log() because the later
 * requires the inode to be in the log and have the log transaction committed,
 * जबतक here we करो not care अगर the log transaction was alपढ़ोy committed - our
 * caller will commit the log later - and we want to aव्योम logging an inode
 * multiple बार when multiple tasks have joined the same log transaction.
 */
अटल bool need_log_inode(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_inode *inode)
अणु
	/*
	 * If this inode करोes not have new/updated/deleted xattrs since the last
	 * समय it was logged and is flagged as logged in the current transaction,
	 * we can skip logging it. As क्रम new/deleted names, those are updated in
	 * the log by link/unlink/नाम operations.
	 * In हाल the inode was logged and then evicted and reloaded, its
	 * logged_trans will be 0, in which हाल we have to fully log it since
	 * logged_trans is a transient field, not persisted.
	 */
	अगर (inode->logged_trans == trans->transid &&
	    !test_bit(BTRFS_INODE_COPY_EVERYTHING, &inode->runसमय_flags))
		वापस false;

	वापस true;
पूर्ण

काष्ठा btrfs_dir_list अणु
	u64 ino;
	काष्ठा list_head list;
पूर्ण;

/*
 * Log the inodes of the new dentries of a directory. See log_dir_items() क्रम
 * details about the why it is needed.
 * This is a recursive operation - अगर an existing dentry corresponds to a
 * directory, that directory's new entries are logged too (same behaviour as
 * ext3/4, xfs, f2fs, reiserfs, nilfs2). Note that when logging the inodes
 * the dentries poपूर्णांक to we करो not lock their i_mutex, otherwise lockdep
 * complains about the following circular lock dependency / possible deadlock:
 *
 *        CPU0                                        CPU1
 *        ----                                        ----
 * lock(&type->i_mutex_dir_key#3/2);
 *                                            lock(sb_पूर्णांकernal#2);
 *                                            lock(&type->i_mutex_dir_key#3/2);
 * lock(&sb->s_type->i_mutex_key#14);
 *
 * Where sb_पूर्णांकernal is the lock (a counter that works as a lock) acquired by
 * sb_start_पूर्णांकग_लिखो() in btrfs_start_transaction().
 * Not locking i_mutex of the inodes is still safe because:
 *
 * 1) For regular files we log with a mode of LOG_INODE_EXISTS. It's possible
 *    that जबतक logging the inode new references (names) are added or हटाओd
 *    from the inode, leaving the logged inode item with a link count that करोes
 *    not match the number of logged inode reference items. This is fine because
 *    at log replay समय we compute the real number of links and correct the
 *    link count in the inode item (see replay_one_buffer() and
 *    link_to_fixup_dir());
 *
 * 2) For directories we log with a mode of LOG_INODE_ALL. It's possible that
 *    जबतक logging the inode's items new items with keys BTRFS_सूची_ITEM_KEY and
 *    BTRFS_सूची_INDEX_KEY are added to fs/subvol tree and the logged inode item
 *    has a size that करोesn't match the sum of the lengths of all the logged
 *    names. This करोes not result in a problem because अगर a dir_item key is
 *    logged but its matching dir_index key is not logged, at log replay समय we
 *    करोn't use it to replay the respective name (see replay_one_name()). On the
 *    other hand अगर only the dir_index key ends up being logged, the respective
 *    name is added to the fs/subvol tree with both the dir_item and dir_index
 *    keys created (see replay_one_name()).
 *    The directory's inode item with a wrong i_size is not a problem as well,
 *    since we करोn't use it at log replay समय to set the i_size in the inode
 *    item of the fs/subvol tree (see overग_लिखो_item()).
 */
अटल पूर्णांक log_new_dir_dentries(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root,
				काष्ठा btrfs_inode *start_inode,
				काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *log = root->log_root;
	काष्ठा btrfs_path *path;
	LIST_HEAD(dir_list);
	काष्ठा btrfs_dir_list *dir_elem;
	पूर्णांक ret = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	dir_elem = kदो_स्मृति(माप(*dir_elem), GFP_NOFS);
	अगर (!dir_elem) अणु
		btrfs_मुक्त_path(path);
		वापस -ENOMEM;
	पूर्ण
	dir_elem->ino = btrfs_ino(start_inode);
	list_add_tail(&dir_elem->list, &dir_list);

	जबतक (!list_empty(&dir_list)) अणु
		काष्ठा extent_buffer *leaf;
		काष्ठा btrfs_key min_key;
		पूर्णांक nritems;
		पूर्णांक i;

		dir_elem = list_first_entry(&dir_list, काष्ठा btrfs_dir_list,
					    list);
		अगर (ret)
			जाओ next_dir_inode;

		min_key.objectid = dir_elem->ino;
		min_key.type = BTRFS_सूची_ITEM_KEY;
		min_key.offset = 0;
again:
		btrfs_release_path(path);
		ret = btrfs_search_क्रमward(log, &min_key, path, trans->transid);
		अगर (ret < 0) अणु
			जाओ next_dir_inode;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			ret = 0;
			जाओ next_dir_inode;
		पूर्ण

process_leaf:
		leaf = path->nodes[0];
		nritems = btrfs_header_nritems(leaf);
		क्रम (i = path->slots[0]; i < nritems; i++) अणु
			काष्ठा btrfs_dir_item *di;
			काष्ठा btrfs_key di_key;
			काष्ठा inode *di_inode;
			काष्ठा btrfs_dir_list *new_dir_elem;
			पूर्णांक log_mode = LOG_INODE_EXISTS;
			पूर्णांक type;

			btrfs_item_key_to_cpu(leaf, &min_key, i);
			अगर (min_key.objectid != dir_elem->ino ||
			    min_key.type != BTRFS_सूची_ITEM_KEY)
				जाओ next_dir_inode;

			di = btrfs_item_ptr(leaf, i, काष्ठा btrfs_dir_item);
			type = btrfs_dir_type(leaf, di);
			अगर (btrfs_dir_transid(leaf, di) < trans->transid &&
			    type != BTRFS_FT_सूची)
				जारी;
			btrfs_dir_item_key_to_cpu(leaf, di, &di_key);
			अगर (di_key.type == BTRFS_ROOT_ITEM_KEY)
				जारी;

			btrfs_release_path(path);
			di_inode = btrfs_iget(fs_info->sb, di_key.objectid, root);
			अगर (IS_ERR(di_inode)) अणु
				ret = PTR_ERR(di_inode);
				जाओ next_dir_inode;
			पूर्ण

			अगर (!need_log_inode(trans, BTRFS_I(di_inode))) अणु
				btrfs_add_delayed_iput(di_inode);
				अवरोध;
			पूर्ण

			ctx->log_new_dentries = false;
			अगर (type == BTRFS_FT_सूची || type == BTRFS_FT_SYMLINK)
				log_mode = LOG_INODE_ALL;
			ret = btrfs_log_inode(trans, root, BTRFS_I(di_inode),
					      log_mode, ctx);
			btrfs_add_delayed_iput(di_inode);
			अगर (ret)
				जाओ next_dir_inode;
			अगर (ctx->log_new_dentries) अणु
				new_dir_elem = kदो_स्मृति(माप(*new_dir_elem),
						       GFP_NOFS);
				अगर (!new_dir_elem) अणु
					ret = -ENOMEM;
					जाओ next_dir_inode;
				पूर्ण
				new_dir_elem->ino = di_key.objectid;
				list_add_tail(&new_dir_elem->list, &dir_list);
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (i == nritems) अणु
			ret = btrfs_next_leaf(log, path);
			अगर (ret < 0) अणु
				जाओ next_dir_inode;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = 0;
				जाओ next_dir_inode;
			पूर्ण
			जाओ process_leaf;
		पूर्ण
		अगर (min_key.offset < (u64)-1) अणु
			min_key.offset++;
			जाओ again;
		पूर्ण
next_dir_inode:
		list_del(&dir_elem->list);
		kमुक्त(dir_elem);
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_log_all_parents(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_inode *inode,
				 काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root *root = inode->root;
	स्थिर u64 ino = btrfs_ino(inode);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	path->skip_locking = 1;
	path->search_commit_root = 1;

	key.objectid = ino;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	जबतक (true) अणु
		काष्ठा extent_buffer *leaf = path->nodes[0];
		पूर्णांक slot = path->slots[0];
		u32 cur_offset = 0;
		u32 item_size;
		अचिन्हित दीर्घ ptr;

		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, slot);
		/* BTRFS_INODE_EXTREF_KEY is BTRFS_INODE_REF_KEY + 1 */
		अगर (key.objectid != ino || key.type > BTRFS_INODE_EXTREF_KEY)
			अवरोध;

		item_size = btrfs_item_size_nr(leaf, slot);
		ptr = btrfs_item_ptr_offset(leaf, slot);
		जबतक (cur_offset < item_size) अणु
			काष्ठा btrfs_key inode_key;
			काष्ठा inode *dir_inode;

			inode_key.type = BTRFS_INODE_ITEM_KEY;
			inode_key.offset = 0;

			अगर (key.type == BTRFS_INODE_EXTREF_KEY) अणु
				काष्ठा btrfs_inode_extref *extref;

				extref = (काष्ठा btrfs_inode_extref *)
					(ptr + cur_offset);
				inode_key.objectid = btrfs_inode_extref_parent(
					leaf, extref);
				cur_offset += माप(*extref);
				cur_offset += btrfs_inode_extref_name_len(leaf,
					extref);
			पूर्ण अन्यथा अणु
				inode_key.objectid = key.offset;
				cur_offset = item_size;
			पूर्ण

			dir_inode = btrfs_iget(fs_info->sb, inode_key.objectid,
					       root);
			/*
			 * If the parent inode was deleted, वापस an error to
			 * fallback to a transaction commit. This is to prevent
			 * getting an inode that was moved from one parent A to
			 * a parent B, got its क्रमmer parent A deleted and then
			 * it got fsync'ed, from existing at both parents after
			 * a log replay (and the old parent still existing).
			 * Example:
			 *
			 * सूची_गढ़ो /mnt/A
			 * सूची_गढ़ो /mnt/B
			 * touch /mnt/B/bar
			 * sync
			 * mv /mnt/B/bar /mnt/A/bar
			 * mv -T /mnt/A /mnt/B
			 * fsync /mnt/B/bar
			 * <घातer fail>
			 *
			 * If we ignore the old parent B which got deleted,
			 * after a log replay we would have file bar linked
			 * at both parents and the old parent B would still
			 * exist.
			 */
			अगर (IS_ERR(dir_inode)) अणु
				ret = PTR_ERR(dir_inode);
				जाओ out;
			पूर्ण

			अगर (!need_log_inode(trans, BTRFS_I(dir_inode))) अणु
				btrfs_add_delayed_iput(dir_inode);
				जारी;
			पूर्ण

			अगर (ctx)
				ctx->log_new_dentries = false;
			ret = btrfs_log_inode(trans, root, BTRFS_I(dir_inode),
					      LOG_INODE_ALL, ctx);
			अगर (!ret && ctx && ctx->log_new_dentries)
				ret = log_new_dir_dentries(trans, root,
						   BTRFS_I(dir_inode), ctx);
			btrfs_add_delayed_iput(dir_inode);
			अगर (ret)
				जाओ out;
		पूर्ण
		path->slots[0]++;
	पूर्ण
	ret = 0;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक log_new_ancestors(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_root *root,
			     काष्ठा btrfs_path *path,
			     काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_key found_key;

	btrfs_item_key_to_cpu(path->nodes[0], &found_key, path->slots[0]);

	जबतक (true) अणु
		काष्ठा btrfs_fs_info *fs_info = root->fs_info;
		काष्ठा extent_buffer *leaf = path->nodes[0];
		पूर्णांक slot = path->slots[0];
		काष्ठा btrfs_key search_key;
		काष्ठा inode *inode;
		u64 ino;
		पूर्णांक ret = 0;

		btrfs_release_path(path);

		ino = found_key.offset;

		search_key.objectid = found_key.offset;
		search_key.type = BTRFS_INODE_ITEM_KEY;
		search_key.offset = 0;
		inode = btrfs_iget(fs_info->sb, ino, root);
		अगर (IS_ERR(inode))
			वापस PTR_ERR(inode);

		अगर (BTRFS_I(inode)->generation >= trans->transid &&
		    need_log_inode(trans, BTRFS_I(inode)))
			ret = btrfs_log_inode(trans, root, BTRFS_I(inode),
					      LOG_INODE_EXISTS, ctx);
		btrfs_add_delayed_iput(inode);
		अगर (ret)
			वापस ret;

		अगर (search_key.objectid == BTRFS_FIRST_FREE_OBJECTID)
			अवरोध;

		search_key.type = BTRFS_INODE_REF_KEY;
		ret = btrfs_search_slot(शून्य, root, &search_key, path, 0, 0);
		अगर (ret < 0)
			वापस ret;

		leaf = path->nodes[0];
		slot = path->slots[0];
		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				वापस ret;
			अन्यथा अगर (ret > 0)
				वापस -ENOENT;
			leaf = path->nodes[0];
			slot = path->slots[0];
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &found_key, slot);
		अगर (found_key.objectid != search_key.objectid ||
		    found_key.type != BTRFS_INODE_REF_KEY)
			वापस -ENOENT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक log_new_ancestors_fast(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_inode *inode,
				  काष्ठा dentry *parent,
				  काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा dentry *old_parent = शून्य;
	काष्ठा super_block *sb = inode->vfs_inode.i_sb;
	पूर्णांक ret = 0;

	जबतक (true) अणु
		अगर (!parent || d_really_is_negative(parent) ||
		    sb != parent->d_sb)
			अवरोध;

		inode = BTRFS_I(d_inode(parent));
		अगर (root != inode->root)
			अवरोध;

		अगर (inode->generation >= trans->transid &&
		    need_log_inode(trans, inode)) अणु
			ret = btrfs_log_inode(trans, root, inode,
					      LOG_INODE_EXISTS, ctx);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (IS_ROOT(parent))
			अवरोध;

		parent = dget_parent(parent);
		dput(old_parent);
		old_parent = parent;
	पूर्ण
	dput(old_parent);

	वापस ret;
पूर्ण

अटल पूर्णांक log_all_new_ancestors(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_inode *inode,
				 काष्ठा dentry *parent,
				 काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_root *root = inode->root;
	स्थिर u64 ino = btrfs_ino(inode);
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key search_key;
	पूर्णांक ret;

	/*
	 * For a single hard link हाल, go through a fast path that करोes not
	 * need to iterate the fs/subvolume tree.
	 */
	अगर (inode->vfs_inode.i_nlink < 2)
		वापस log_new_ancestors_fast(trans, inode, parent, ctx);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	search_key.objectid = ino;
	search_key.type = BTRFS_INODE_REF_KEY;
	search_key.offset = 0;
again:
	ret = btrfs_search_slot(शून्य, root, &search_key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret == 0)
		path->slots[0]++;

	जबतक (true) अणु
		काष्ठा extent_buffer *leaf = path->nodes[0];
		पूर्णांक slot = path->slots[0];
		काष्ठा btrfs_key found_key;

		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &found_key, slot);
		अगर (found_key.objectid != ino ||
		    found_key.type > BTRFS_INODE_EXTREF_KEY)
			अवरोध;

		/*
		 * Don't deal with extended references because they are rare
		 * हालs and too complex to deal with (we would need to keep
		 * track of which subitem we are processing क्रम each item in
		 * this loop, etc). So just वापस some error to fallback to
		 * a transaction commit.
		 */
		अगर (found_key.type == BTRFS_INODE_EXTREF_KEY) अणु
			ret = -EMLINK;
			जाओ out;
		पूर्ण

		/*
		 * Logging ancestors needs to करो more searches on the fs/subvol
		 * tree, so it releases the path as needed to aव्योम deadlocks.
		 * Keep track of the last inode ref key and resume from that key
		 * after logging all new ancestors क्रम the current hard link.
		 */
		स_नकल(&search_key, &found_key, माप(search_key));

		ret = log_new_ancestors(trans, root, path, ctx);
		अगर (ret)
			जाओ out;
		btrfs_release_path(path);
		जाओ again;
	पूर्ण
	ret = 0;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * helper function around btrfs_log_inode to make sure newly created
 * parent directories also end up in the log.  A minimal inode and backref
 * only logging is करोne of any parent directories that are older than
 * the last committed transaction
 */
अटल पूर्णांक btrfs_log_inode_parent(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_inode *inode,
				  काष्ठा dentry *parent,
				  पूर्णांक inode_only,
				  काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret = 0;
	bool log_dentries = false;

	अगर (btrfs_test_opt(fs_info, NOTREELOG)) अणु
		ret = 1;
		जाओ end_no_trans;
	पूर्ण

	अगर (btrfs_root_refs(&root->root_item) == 0) अणु
		ret = 1;
		जाओ end_no_trans;
	पूर्ण

	/*
	 * Skip alपढ़ोy logged inodes or inodes corresponding to क्षणिक_खs
	 * (since logging them is poपूर्णांकless, a link count of 0 means they
	 * will never be accessible).
	 */
	अगर ((btrfs_inode_in_log(inode, trans->transid) &&
	     list_empty(&ctx->ordered_extents)) ||
	    inode->vfs_inode.i_nlink == 0) अणु
		ret = BTRFS_NO_LOG_SYNC;
		जाओ end_no_trans;
	पूर्ण

	ret = start_log_trans(trans, root, ctx);
	अगर (ret)
		जाओ end_no_trans;

	ret = btrfs_log_inode(trans, root, inode, inode_only, ctx);
	अगर (ret)
		जाओ end_trans;

	/*
	 * क्रम regular files, अगर its inode is alपढ़ोy on disk, we करोn't
	 * have to worry about the parents at all.  This is because
	 * we can use the last_unlink_trans field to record नामs
	 * and other fun in this file.
	 */
	अगर (S_ISREG(inode->vfs_inode.i_mode) &&
	    inode->generation < trans->transid &&
	    inode->last_unlink_trans < trans->transid) अणु
		ret = 0;
		जाओ end_trans;
	पूर्ण

	अगर (S_ISसूची(inode->vfs_inode.i_mode) && ctx && ctx->log_new_dentries)
		log_dentries = true;

	/*
	 * On unlink we must make sure all our current and old parent directory
	 * inodes are fully logged. This is to prevent leaving dangling
	 * directory index entries in directories that were our parents but are
	 * not anymore. Not करोing this results in old parent directory being
	 * impossible to delete after log replay (सूची_हटाओ will always fail with
	 * error -ENOTEMPTY).
	 *
	 * Example 1:
	 *
	 * सूची_गढ़ो testdir
	 * touch testdir/foo
	 * ln testdir/foo testdir/bar
	 * sync
	 * unlink testdir/bar
	 * xfs_io -c fsync testdir/foo
	 * <घातer failure>
	 * mount fs, triggers log replay
	 *
	 * If we करोn't log the parent directory (testdir), after log replay the
	 * directory still has an entry poपूर्णांकing to the file inode using the bar
	 * name, but a matching BTRFS_INODE_[REF|EXTREF]_KEY करोes not exist and
	 * the file inode has a link count of 1.
	 *
	 * Example 2:
	 *
	 * सूची_गढ़ो testdir
	 * touch foo
	 * ln foo testdir/foo2
	 * ln foo testdir/foo3
	 * sync
	 * unlink testdir/foo3
	 * xfs_io -c fsync foo
	 * <घातer failure>
	 * mount fs, triggers log replay
	 *
	 * Similar as the first example, after log replay the parent directory
	 * testdir still has an entry poपूर्णांकing to the inode file with name foo3
	 * but the file inode करोes not have a matching BTRFS_INODE_REF_KEY item
	 * and has a link count of 2.
	 */
	अगर (inode->last_unlink_trans >= trans->transid) अणु
		ret = btrfs_log_all_parents(trans, inode, ctx);
		अगर (ret)
			जाओ end_trans;
	पूर्ण

	ret = log_all_new_ancestors(trans, inode, parent, ctx);
	अगर (ret)
		जाओ end_trans;

	अगर (log_dentries)
		ret = log_new_dir_dentries(trans, root, inode, ctx);
	अन्यथा
		ret = 0;
end_trans:
	अगर (ret < 0) अणु
		btrfs_set_log_full_commit(trans);
		ret = 1;
	पूर्ण

	अगर (ret)
		btrfs_हटाओ_log_ctx(root, ctx);
	btrfs_end_log_trans(root);
end_no_trans:
	वापस ret;
पूर्ण

/*
 * it is not safe to log dentry अगर the chunk root has added new
 * chunks.  This वापसs 0 अगर the dentry was logged, and 1 otherwise.
 * If this वापसs 1, you must commit the transaction to safely get your
 * data on disk.
 */
पूर्णांक btrfs_log_dentry_safe(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा dentry *dentry,
			  काष्ठा btrfs_log_ctx *ctx)
अणु
	काष्ठा dentry *parent = dget_parent(dentry);
	पूर्णांक ret;

	ret = btrfs_log_inode_parent(trans, BTRFS_I(d_inode(dentry)), parent,
				     LOG_INODE_ALL, ctx);
	dput(parent);

	वापस ret;
पूर्ण

/*
 * should be called during mount to recover any replay any log trees
 * from the FS
 */
पूर्णांक btrfs_recover_log_trees(काष्ठा btrfs_root *log_root_tree)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_root *log;
	काष्ठा btrfs_fs_info *fs_info = log_root_tree->fs_info;
	काष्ठा walk_control wc = अणु
		.process_func = process_one_buffer,
		.stage = LOG_WALK_PIN_ONLY,
	पूर्ण;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	set_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags);

	trans = btrfs_start_transaction(fs_info->tree_root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ error;
	पूर्ण

	wc.trans = trans;
	wc.pin = 1;

	ret = walk_log_tree(trans, log_root_tree, &wc);
	अगर (ret) अणु
		btrfs_handle_fs_error(fs_info, ret,
			"Failed to pin buffers while recovering log root tree.");
		जाओ error;
	पूर्ण

again:
	key.objectid = BTRFS_TREE_LOG_OBJECTID;
	key.offset = (u64)-1;
	key.type = BTRFS_ROOT_ITEM_KEY;

	जबतक (1) अणु
		ret = btrfs_search_slot(शून्य, log_root_tree, &key, path, 0, 0);

		अगर (ret < 0) अणु
			btrfs_handle_fs_error(fs_info, ret,
				    "Couldn't find tree log root.");
			जाओ error;
		पूर्ण
		अगर (ret > 0) अणु
			अगर (path->slots[0] == 0)
				अवरोध;
			path->slots[0]--;
		पूर्ण
		btrfs_item_key_to_cpu(path->nodes[0], &found_key,
				      path->slots[0]);
		btrfs_release_path(path);
		अगर (found_key.objectid != BTRFS_TREE_LOG_OBJECTID)
			अवरोध;

		log = btrfs_पढ़ो_tree_root(log_root_tree, &found_key);
		अगर (IS_ERR(log)) अणु
			ret = PTR_ERR(log);
			btrfs_handle_fs_error(fs_info, ret,
				    "Couldn't read tree log root.");
			जाओ error;
		पूर्ण

		wc.replay_dest = btrfs_get_fs_root(fs_info, found_key.offset,
						   true);
		अगर (IS_ERR(wc.replay_dest)) अणु
			ret = PTR_ERR(wc.replay_dest);

			/*
			 * We didn't find the subvol, likely because it was
			 * deleted.  This is ok, simply skip this log and go to
			 * the next one.
			 *
			 * We need to exclude the root because we can't have
			 * other log replays overwriting this log as we'll पढ़ो
			 * it back in a few more बार.  This will keep our
			 * block from being modअगरied, and we'll just bail क्रम
			 * each subsequent pass.
			 */
			अगर (ret == -ENOENT)
				ret = btrfs_pin_extent_क्रम_log_replay(trans,
							log->node->start,
							log->node->len);
			btrfs_put_root(log);

			अगर (!ret)
				जाओ next;
			btrfs_handle_fs_error(fs_info, ret,
				"Couldn't read target root for tree log recovery.");
			जाओ error;
		पूर्ण

		wc.replay_dest->log_root = log;
		ret = btrfs_record_root_in_trans(trans, wc.replay_dest);
		अगर (ret)
			/* The loop needs to जारी due to the root refs */
			btrfs_handle_fs_error(fs_info, ret,
				"failed to record the log root in transaction");
		अन्यथा
			ret = walk_log_tree(trans, log, &wc);

		अगर (!ret && wc.stage == LOG_WALK_REPLAY_ALL) अणु
			ret = fixup_inode_link_counts(trans, wc.replay_dest,
						      path);
		पूर्ण

		अगर (!ret && wc.stage == LOG_WALK_REPLAY_ALL) अणु
			काष्ठा btrfs_root *root = wc.replay_dest;

			btrfs_release_path(path);

			/*
			 * We have just replayed everything, and the highest
			 * objectid of fs roots probably has changed in हाल
			 * some inode_item's got replayed.
			 *
			 * root->objectid_mutex is not acquired as log replay
			 * could only happen during mount.
			 */
			ret = btrfs_init_root_मुक्त_objectid(root);
		पूर्ण

		wc.replay_dest->log_root = शून्य;
		btrfs_put_root(wc.replay_dest);
		btrfs_put_root(log);

		अगर (ret)
			जाओ error;
next:
		अगर (found_key.offset == 0)
			अवरोध;
		key.offset = found_key.offset - 1;
	पूर्ण
	btrfs_release_path(path);

	/* step one is to pin it all, step two is to replay just inodes */
	अगर (wc.pin) अणु
		wc.pin = 0;
		wc.process_func = replay_one_buffer;
		wc.stage = LOG_WALK_REPLAY_INODES;
		जाओ again;
	पूर्ण
	/* step three is to replay everything */
	अगर (wc.stage < LOG_WALK_REPLAY_ALL) अणु
		wc.stage++;
		जाओ again;
	पूर्ण

	btrfs_मुक्त_path(path);

	/* step 4: commit the transaction, which also unpins the blocks */
	ret = btrfs_commit_transaction(trans);
	अगर (ret)
		वापस ret;

	log_root_tree->log_root = शून्य;
	clear_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags);
	btrfs_put_root(log_root_tree);

	वापस 0;
error:
	अगर (wc.trans)
		btrfs_end_transaction(wc.trans);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * there are some corner हालs where we want to क्रमce a full
 * commit instead of allowing a directory to be logged.
 *
 * They revolve around files there were unlinked from the directory, and
 * this function updates the parent directory so that a full commit is
 * properly करोne अगर it is fsync'd later after the unlinks are करोne.
 *
 * Must be called beक्रमe the unlink operations (updates to the subvolume tree,
 * inodes, etc) are करोne.
 */
व्योम btrfs_record_unlink_dir(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_inode *dir, काष्ठा btrfs_inode *inode,
			     पूर्णांक क्रम_नाम)
अणु
	/*
	 * when we're logging a file, if it hasn't been नामd
	 * or unlinked, and its inode is fully committed on disk,
	 * we करोn't have to worry about walking up the directory chain
	 * to log its parents.
	 *
	 * So, we use the last_unlink_trans field to put this transid
	 * पूर्णांकo the file.  When the file is logged we check it and
	 * करोn't log the parents अगर the file is fully on disk.
	 */
	mutex_lock(&inode->log_mutex);
	inode->last_unlink_trans = trans->transid;
	mutex_unlock(&inode->log_mutex);

	/*
	 * अगर this directory was alपढ़ोy logged any new
	 * names क्रम this file/dir will get recorded
	 */
	अगर (dir->logged_trans == trans->transid)
		वापस;

	/*
	 * अगर the inode we're about to unlink was logged,
	 * the log will be properly updated क्रम any new names
	 */
	अगर (inode->logged_trans == trans->transid)
		वापस;

	/*
	 * when renaming files across directories, अगर the directory
	 * there we're unlinking from gets fsync'd later on, there's
	 * no way to find the destination directory later and fsync it
	 * properly.  So, we have to be conservative and क्रमce commits
	 * so the new name माला_लो discovered.
	 */
	अगर (क्रम_नाम)
		जाओ record;

	/* we can safely करो the unlink without any special recording */
	वापस;

record:
	mutex_lock(&dir->log_mutex);
	dir->last_unlink_trans = trans->transid;
	mutex_unlock(&dir->log_mutex);
पूर्ण

/*
 * Make sure that अगर someone attempts to fsync the parent directory of a deleted
 * snapshot, it ends up triggering a transaction commit. This is to guarantee
 * that after replaying the log tree of the parent directory's root we will not
 * see the snapshot anymore and at log replay समय we will not see any log tree
 * corresponding to the deleted snapshot's root, which could lead to replaying
 * it after replaying the log tree of the parent directory (which would replay
 * the snapshot delete operation).
 *
 * Must be called beक्रमe the actual snapshot destroy operation (updates to the
 * parent root and tree of tree roots trees, etc) are करोne.
 */
व्योम btrfs_record_snapshot_destroy(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_inode *dir)
अणु
	mutex_lock(&dir->log_mutex);
	dir->last_unlink_trans = trans->transid;
	mutex_unlock(&dir->log_mutex);
पूर्ण

/*
 * Call this after adding a new name क्रम a file and it will properly
 * update the log to reflect the new name.
 */
व्योम btrfs_log_new_name(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_inode *inode, काष्ठा btrfs_inode *old_dir,
			काष्ठा dentry *parent)
अणु
	काष्ठा btrfs_log_ctx ctx;

	/*
	 * this will क्रमce the logging code to walk the dentry chain
	 * up क्रम the file
	 */
	अगर (!S_ISसूची(inode->vfs_inode.i_mode))
		inode->last_unlink_trans = trans->transid;

	/*
	 * अगर this inode hasn't been logged and directory we're renaming it
	 * from hasn't been logged, we don't need to log it
	 */
	अगर (inode->logged_trans < trans->transid &&
	    (!old_dir || old_dir->logged_trans < trans->transid))
		वापस;

	/*
	 * If we are करोing a नाम (old_dir is not शून्य) from a directory that
	 * was previously logged, make sure the next log attempt on the directory
	 * is not skipped and logs the inode again. This is because the log may
	 * not currently be authoritative क्रम a range including the old
	 * BTRFS_सूची_ITEM_KEY and BTRFS_सूची_INDEX_KEY keys, so we want to make
	 * sure after a log replay we करो not end up with both the new and old
	 * dentries around (in हाल the inode is a directory we would have a
	 * directory with two hard links and 2 inode references क्रम dअगरferent
	 * parents). The next log attempt of old_dir will happen at
	 * btrfs_log_all_parents(), called through btrfs_log_inode_parent()
	 * below, because we have previously set inode->last_unlink_trans to the
	 * current transaction ID, either here or at btrfs_record_unlink_dir() in
	 * हाल inode is a directory.
	 */
	अगर (old_dir)
		old_dir->logged_trans = 0;

	btrfs_init_log_ctx(&ctx, &inode->vfs_inode);
	ctx.logging_new_name = true;
	/*
	 * We करोn't care about the वापस value. If we fail to log the new name
	 * then we know the next attempt to sync the log will fallback to a full
	 * transaction commit (due to a call to btrfs_set_log_full_commit()), so
	 * we करोn't need to worry about getting a log committed that has an
	 * inconsistent state after a नाम operation.
	 */
	btrfs_log_inode_parent(trans, inode, parent, LOG_INODE_EXISTS, &ctx);
पूर्ण

