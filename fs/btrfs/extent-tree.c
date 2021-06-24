<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/sort.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/crc32c.h>
#समावेश "misc.h"
#समावेश "tree-log.h"
#समावेश "disk-io.h"
#समावेश "print-tree.h"
#समावेश "volumes.h"
#समावेश "raid56.h"
#समावेश "locking.h"
#समावेश "free-space-cache.h"
#समावेश "free-space-tree.h"
#समावेश "sysfs.h"
#समावेश "qgroup.h"
#समावेश "ref-verify.h"
#समावेश "space-info.h"
#समावेश "block-rsv.h"
#समावेश "delalloc-space.h"
#समावेश "block-group.h"
#समावेश "discard.h"
#समावेश "rcu-string.h"
#समावेश "zoned.h"
#समावेश "dev-replace.h"

#अघोषित SCRAMBLE_DELAYED_REFS


अटल पूर्णांक __btrfs_मुक्त_extent(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_delayed_ref_node *node, u64 parent,
			       u64 root_objectid, u64 owner_objectid,
			       u64 owner_offset, पूर्णांक refs_to_drop,
			       काष्ठा btrfs_delayed_extent_op *extra_op);
अटल व्योम __run_delayed_extent_op(काष्ठा btrfs_delayed_extent_op *extent_op,
				    काष्ठा extent_buffer *leaf,
				    काष्ठा btrfs_extent_item *ei);
अटल पूर्णांक alloc_reserved_file_extent(काष्ठा btrfs_trans_handle *trans,
				      u64 parent, u64 root_objectid,
				      u64 flags, u64 owner, u64 offset,
				      काष्ठा btrfs_key *ins, पूर्णांक ref_mod);
अटल पूर्णांक alloc_reserved_tree_block(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_delayed_ref_node *node,
				     काष्ठा btrfs_delayed_extent_op *extent_op);
अटल पूर्णांक find_next_key(काष्ठा btrfs_path *path, पूर्णांक level,
			 काष्ठा btrfs_key *key);

अटल पूर्णांक block_group_bits(काष्ठा btrfs_block_group *cache, u64 bits)
अणु
	वापस (cache->flags & bits) == bits;
पूर्ण

पूर्णांक btrfs_add_excluded_extent(काष्ठा btrfs_fs_info *fs_info,
			      u64 start, u64 num_bytes)
अणु
	u64 end = start + num_bytes - 1;
	set_extent_bits(&fs_info->excluded_extents, start, end,
			EXTENT_UPTODATE);
	वापस 0;
पूर्ण

व्योम btrfs_मुक्त_excluded_extents(काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	u64 start, end;

	start = cache->start;
	end = start + cache->length - 1;

	clear_extent_bits(&fs_info->excluded_extents, start, end,
			  EXTENT_UPTODATE);
पूर्ण

/* simple helper to search क्रम an existing data extent at a given offset */
पूर्णांक btrfs_lookup_data_extent(काष्ठा btrfs_fs_info *fs_info, u64 start, u64 len)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = start;
	key.offset = len;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	ret = btrfs_search_slot(शून्य, fs_info->extent_root, &key, path, 0, 0);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * helper function to lookup reference count and flags of a tree block.
 *
 * the head node क्रम delayed ref is used to store the sum of all the
 * reference count modअगरications queued up in the rbtree. the head
 * node may also store the extent flags to set. This way you can check
 * to see what the reference count and extent flags would be अगर all of
 * the delayed refs are not processed.
 */
पूर्णांक btrfs_lookup_extent_info(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			     u64 offset, पूर्णांक metadata, u64 *refs, u64 *flags)
अणु
	काष्ठा btrfs_delayed_ref_head *head;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	u32 item_size;
	u64 num_refs;
	u64 extent_flags;
	पूर्णांक ret;

	/*
	 * If we करोn't have skinny metadata, don't bother करोing anything
	 * dअगरferent
	 */
	अगर (metadata && !btrfs_fs_incompat(fs_info, SKINNY_METADATA)) अणु
		offset = fs_info->nodesize;
		metadata = 0;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	अगर (!trans) अणु
		path->skip_locking = 1;
		path->search_commit_root = 1;
	पूर्ण

search_again:
	key.objectid = bytenr;
	key.offset = offset;
	अगर (metadata)
		key.type = BTRFS_METADATA_ITEM_KEY;
	अन्यथा
		key.type = BTRFS_EXTENT_ITEM_KEY;

	ret = btrfs_search_slot(trans, fs_info->extent_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out_मुक्त;

	अगर (ret > 0 && metadata && key.type == BTRFS_METADATA_ITEM_KEY) अणु
		अगर (path->slots[0]) अणु
			path->slots[0]--;
			btrfs_item_key_to_cpu(path->nodes[0], &key,
					      path->slots[0]);
			अगर (key.objectid == bytenr &&
			    key.type == BTRFS_EXTENT_ITEM_KEY &&
			    key.offset == fs_info->nodesize)
				ret = 0;
		पूर्ण
	पूर्ण

	अगर (ret == 0) अणु
		leaf = path->nodes[0];
		item_size = btrfs_item_size_nr(leaf, path->slots[0]);
		अगर (item_size >= माप(*ei)) अणु
			ei = btrfs_item_ptr(leaf, path->slots[0],
					    काष्ठा btrfs_extent_item);
			num_refs = btrfs_extent_refs(leaf, ei);
			extent_flags = btrfs_extent_flags(leaf, ei);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			btrfs_prपूर्णांक_v0_err(fs_info);
			अगर (trans)
				btrfs_पात_transaction(trans, ret);
			अन्यथा
				btrfs_handle_fs_error(fs_info, ret, शून्य);

			जाओ out_मुक्त;
		पूर्ण

		BUG_ON(num_refs == 0);
	पूर्ण अन्यथा अणु
		num_refs = 0;
		extent_flags = 0;
		ret = 0;
	पूर्ण

	अगर (!trans)
		जाओ out;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);
	head = btrfs_find_delayed_ref_head(delayed_refs, bytenr);
	अगर (head) अणु
		अगर (!mutex_trylock(&head->mutex)) अणु
			refcount_inc(&head->refs);
			spin_unlock(&delayed_refs->lock);

			btrfs_release_path(path);

			/*
			 * Mutex was contended, block until it's released and try
			 * again
			 */
			mutex_lock(&head->mutex);
			mutex_unlock(&head->mutex);
			btrfs_put_delayed_ref_head(head);
			जाओ search_again;
		पूर्ण
		spin_lock(&head->lock);
		अगर (head->extent_op && head->extent_op->update_flags)
			extent_flags |= head->extent_op->flags_to_set;
		अन्यथा
			BUG_ON(num_refs == 0);

		num_refs += head->ref_mod;
		spin_unlock(&head->lock);
		mutex_unlock(&head->mutex);
	पूर्ण
	spin_unlock(&delayed_refs->lock);
out:
	WARN_ON(num_refs == 0);
	अगर (refs)
		*refs = num_refs;
	अगर (flags)
		*flags = extent_flags;
out_मुक्त:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Back reference rules.  Back refs have three मुख्य goals:
 *
 * 1) dअगरferentiate between all holders of references to an extent so that
 *    when a reference is dropped we can make sure it was a valid reference
 *    beक्रमe मुक्तing the extent.
 *
 * 2) Provide enough inक्रमmation to quickly find the holders of an extent
 *    अगर we notice a given block is corrupted or bad.
 *
 * 3) Make it easy to migrate blocks क्रम FS shrinking or storage pool
 *    मुख्यtenance.  This is actually the same as #2, but with a slightly
 *    dअगरferent use हाल.
 *
 * There are two kinds of back refs. The implicit back refs is optimized
 * क्रम poपूर्णांकers in non-shared tree blocks. For a given poपूर्णांकer in a block,
 * back refs of this kind provide inक्रमmation about the block's owner tree
 * and the poपूर्णांकer's key. These inक्रमmation allow us to find the block by
 * b-tree searching. The full back refs is क्रम poपूर्णांकers in tree blocks not
 * referenced by their owner trees. The location of tree block is recorded
 * in the back refs. Actually the full back refs is generic, and can be
 * used in all हालs the implicit back refs is used. The major लघुcoming
 * of the full back refs is its overhead. Every समय a tree block माला_लो
 * COWed, we have to update back refs entry क्रम all poपूर्णांकers in it.
 *
 * For a newly allocated tree block, we use implicit back refs क्रम
 * poपूर्णांकers in it. This means most tree related operations only involve
 * implicit back refs. For a tree block created in old transaction, the
 * only way to drop a reference to it is COW it. So we can detect the
 * event that tree block loses its owner tree's reference and करो the
 * back refs conversion.
 *
 * When a tree block is COWed through a tree, there are four हालs:
 *
 * The reference count of the block is one and the tree is the block's
 * owner tree. Nothing to करो in this हाल.
 *
 * The reference count of the block is one and the tree is not the
 * block's owner tree. In this हाल, full back refs is used क्रम poपूर्णांकers
 * in the block. Remove these full back refs, add implicit back refs क्रम
 * every poपूर्णांकers in the new block.
 *
 * The reference count of the block is greater than one and the tree is
 * the block's owner tree. In this हाल, implicit back refs is used क्रम
 * poपूर्णांकers in the block. Add full back refs क्रम every poपूर्णांकers in the
 * block, increase lower level extents' reference counts. The original
 * implicit back refs are entailed to the new block.
 *
 * The reference count of the block is greater than one and the tree is
 * not the block's owner tree. Add implicit back refs क्रम every poपूर्णांकer in
 * the new block, increase lower level extents' reference count.
 *
 * Back Reference Key composing:
 *
 * The key objectid corresponds to the first byte in the extent,
 * The key type is used to dअगरferentiate between types of back refs.
 * There are dअगरferent meanings of the key offset क्रम dअगरferent types
 * of back refs.
 *
 * File extents can be referenced by:
 *
 * - multiple snapshots, subvolumes, or dअगरferent generations in one subvol
 * - dअगरferent files inside a single subvolume
 * - dअगरferent offsets inside a file (bookend extents in file.c)
 *
 * The extent ref काष्ठाure क्रम the implicit back refs has fields क्रम:
 *
 * - Objectid of the subvolume root
 * - objectid of the file holding the reference
 * - original offset in the file
 * - how many bookend extents
 *
 * The key offset क्रम the implicit back refs is hash of the first
 * three fields.
 *
 * The extent ref काष्ठाure क्रम the full back refs has field क्रम:
 *
 * - number of poपूर्णांकers in the tree leaf
 *
 * The key offset क्रम the implicit back refs is the first byte of
 * the tree leaf
 *
 * When a file extent is allocated, The implicit back refs is used.
 * the fields are filled in:
 *
 *     (root_key.objectid, inode objectid, offset in file, 1)
 *
 * When a file extent is हटाओd file truncation, we find the
 * corresponding implicit back refs and check the following fields:
 *
 *     (btrfs_header_owner(leaf), inode objectid, offset in file)
 *
 * Btree extents can be referenced by:
 *
 * - Dअगरferent subvolumes
 *
 * Both the implicit back refs and the full back refs क्रम tree blocks
 * only consist of key. The key offset क्रम the implicit back refs is
 * objectid of block's owner tree. The key offset क्रम the full back refs
 * is the first byte of parent block.
 *
 * When implicit back refs is used, inक्रमmation about the lowest key and
 * level of the tree block are required. These inक्रमmation are stored in
 * tree block info काष्ठाure.
 */

/*
 * is_data == BTRFS_REF_TYPE_BLOCK, tree block type is required,
 * is_data == BTRFS_REF_TYPE_DATA, data type is requiried,
 * is_data == BTRFS_REF_TYPE_ANY, either type is OK.
 */
पूर्णांक btrfs_get_extent_अंतरभूत_ref_type(स्थिर काष्ठा extent_buffer *eb,
				     काष्ठा btrfs_extent_अंतरभूत_ref *iref,
				     क्रमागत btrfs_अंतरभूत_ref_type is_data)
अणु
	पूर्णांक type = btrfs_extent_अंतरभूत_ref_type(eb, iref);
	u64 offset = btrfs_extent_अंतरभूत_ref_offset(eb, iref);

	अगर (type == BTRFS_TREE_BLOCK_REF_KEY ||
	    type == BTRFS_SHARED_BLOCK_REF_KEY ||
	    type == BTRFS_SHARED_DATA_REF_KEY ||
	    type == BTRFS_EXTENT_DATA_REF_KEY) अणु
		अगर (is_data == BTRFS_REF_TYPE_BLOCK) अणु
			अगर (type == BTRFS_TREE_BLOCK_REF_KEY)
				वापस type;
			अगर (type == BTRFS_SHARED_BLOCK_REF_KEY) अणु
				ASSERT(eb->fs_info);
				/*
				 * Every shared one has parent tree block,
				 * which must be aligned to sector size.
				 */
				अगर (offset &&
				    IS_ALIGNED(offset, eb->fs_info->sectorsize))
					वापस type;
			पूर्ण
		पूर्ण अन्यथा अगर (is_data == BTRFS_REF_TYPE_DATA) अणु
			अगर (type == BTRFS_EXTENT_DATA_REF_KEY)
				वापस type;
			अगर (type == BTRFS_SHARED_DATA_REF_KEY) अणु
				ASSERT(eb->fs_info);
				/*
				 * Every shared one has parent tree block,
				 * which must be aligned to sector size.
				 */
				अगर (offset &&
				    IS_ALIGNED(offset, eb->fs_info->sectorsize))
					वापस type;
			पूर्ण
		पूर्ण अन्यथा अणु
			ASSERT(is_data == BTRFS_REF_TYPE_ANY);
			वापस type;
		पूर्ण
	पूर्ण

	btrfs_prपूर्णांक_leaf((काष्ठा extent_buffer *)eb);
	btrfs_err(eb->fs_info,
		  "eb %llu iref 0x%lx invalid extent inline ref type %d",
		  eb->start, (अचिन्हित दीर्घ)iref, type);
	WARN_ON(1);

	वापस BTRFS_REF_TYPE_INVALID;
पूर्ण

u64 hash_extent_data_ref(u64 root_objectid, u64 owner, u64 offset)
अणु
	u32 high_crc = ~(u32)0;
	u32 low_crc = ~(u32)0;
	__le64 lक्रमागत;

	lक्रमागत = cpu_to_le64(root_objectid);
	high_crc = btrfs_crc32c(high_crc, &lक्रमागत, माप(lक्रमागत));
	lक्रमागत = cpu_to_le64(owner);
	low_crc = btrfs_crc32c(low_crc, &lक्रमागत, माप(lक्रमागत));
	lक्रमागत = cpu_to_le64(offset);
	low_crc = btrfs_crc32c(low_crc, &lक्रमागत, माप(lक्रमागत));

	वापस ((u64)high_crc << 31) ^ (u64)low_crc;
पूर्ण

अटल u64 hash_extent_data_ref_item(काष्ठा extent_buffer *leaf,
				     काष्ठा btrfs_extent_data_ref *ref)
अणु
	वापस hash_extent_data_ref(btrfs_extent_data_ref_root(leaf, ref),
				    btrfs_extent_data_ref_objectid(leaf, ref),
				    btrfs_extent_data_ref_offset(leaf, ref));
पूर्ण

अटल पूर्णांक match_extent_data_ref(काष्ठा extent_buffer *leaf,
				 काष्ठा btrfs_extent_data_ref *ref,
				 u64 root_objectid, u64 owner, u64 offset)
अणु
	अगर (btrfs_extent_data_ref_root(leaf, ref) != root_objectid ||
	    btrfs_extent_data_ref_objectid(leaf, ref) != owner ||
	    btrfs_extent_data_ref_offset(leaf, ref) != offset)
		वापस 0;
	वापस 1;
पूर्ण

अटल noअंतरभूत पूर्णांक lookup_extent_data_ref(काष्ठा btrfs_trans_handle *trans,
					   काष्ठा btrfs_path *path,
					   u64 bytenr, u64 parent,
					   u64 root_objectid,
					   u64 owner, u64 offset)
अणु
	काष्ठा btrfs_root *root = trans->fs_info->extent_root;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_extent_data_ref *ref;
	काष्ठा extent_buffer *leaf;
	u32 nritems;
	पूर्णांक ret;
	पूर्णांक recow;
	पूर्णांक err = -ENOENT;

	key.objectid = bytenr;
	अगर (parent) अणु
		key.type = BTRFS_SHARED_DATA_REF_KEY;
		key.offset = parent;
	पूर्ण अन्यथा अणु
		key.type = BTRFS_EXTENT_DATA_REF_KEY;
		key.offset = hash_extent_data_ref(root_objectid,
						  owner, offset);
	पूर्ण
again:
	recow = 0;
	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret < 0) अणु
		err = ret;
		जाओ fail;
	पूर्ण

	अगर (parent) अणु
		अगर (!ret)
			वापस 0;
		जाओ fail;
	पूर्ण

	leaf = path->nodes[0];
	nritems = btrfs_header_nritems(leaf);
	जबतक (1) अणु
		अगर (path->slots[0] >= nritems) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				err = ret;
			अगर (ret)
				जाओ fail;

			leaf = path->nodes[0];
			nritems = btrfs_header_nritems(leaf);
			recow = 1;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		अगर (key.objectid != bytenr ||
		    key.type != BTRFS_EXTENT_DATA_REF_KEY)
			जाओ fail;

		ref = btrfs_item_ptr(leaf, path->slots[0],
				     काष्ठा btrfs_extent_data_ref);

		अगर (match_extent_data_ref(leaf, ref, root_objectid,
					  owner, offset)) अणु
			अगर (recow) अणु
				btrfs_release_path(path);
				जाओ again;
			पूर्ण
			err = 0;
			अवरोध;
		पूर्ण
		path->slots[0]++;
	पूर्ण
fail:
	वापस err;
पूर्ण

अटल noअंतरभूत पूर्णांक insert_extent_data_ref(काष्ठा btrfs_trans_handle *trans,
					   काष्ठा btrfs_path *path,
					   u64 bytenr, u64 parent,
					   u64 root_objectid, u64 owner,
					   u64 offset, पूर्णांक refs_to_add)
अणु
	काष्ठा btrfs_root *root = trans->fs_info->extent_root;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	u32 size;
	u32 num_refs;
	पूर्णांक ret;

	key.objectid = bytenr;
	अगर (parent) अणु
		key.type = BTRFS_SHARED_DATA_REF_KEY;
		key.offset = parent;
		size = माप(काष्ठा btrfs_shared_data_ref);
	पूर्ण अन्यथा अणु
		key.type = BTRFS_EXTENT_DATA_REF_KEY;
		key.offset = hash_extent_data_ref(root_objectid,
						  owner, offset);
		size = माप(काष्ठा btrfs_extent_data_ref);
	पूर्ण

	ret = btrfs_insert_empty_item(trans, root, path, &key, size);
	अगर (ret && ret != -EEXIST)
		जाओ fail;

	leaf = path->nodes[0];
	अगर (parent) अणु
		काष्ठा btrfs_shared_data_ref *ref;
		ref = btrfs_item_ptr(leaf, path->slots[0],
				     काष्ठा btrfs_shared_data_ref);
		अगर (ret == 0) अणु
			btrfs_set_shared_data_ref_count(leaf, ref, refs_to_add);
		पूर्ण अन्यथा अणु
			num_refs = btrfs_shared_data_ref_count(leaf, ref);
			num_refs += refs_to_add;
			btrfs_set_shared_data_ref_count(leaf, ref, num_refs);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_extent_data_ref *ref;
		जबतक (ret == -EEXIST) अणु
			ref = btrfs_item_ptr(leaf, path->slots[0],
					     काष्ठा btrfs_extent_data_ref);
			अगर (match_extent_data_ref(leaf, ref, root_objectid,
						  owner, offset))
				अवरोध;
			btrfs_release_path(path);
			key.offset++;
			ret = btrfs_insert_empty_item(trans, root, path, &key,
						      size);
			अगर (ret && ret != -EEXIST)
				जाओ fail;

			leaf = path->nodes[0];
		पूर्ण
		ref = btrfs_item_ptr(leaf, path->slots[0],
				     काष्ठा btrfs_extent_data_ref);
		अगर (ret == 0) अणु
			btrfs_set_extent_data_ref_root(leaf, ref,
						       root_objectid);
			btrfs_set_extent_data_ref_objectid(leaf, ref, owner);
			btrfs_set_extent_data_ref_offset(leaf, ref, offset);
			btrfs_set_extent_data_ref_count(leaf, ref, refs_to_add);
		पूर्ण अन्यथा अणु
			num_refs = btrfs_extent_data_ref_count(leaf, ref);
			num_refs += refs_to_add;
			btrfs_set_extent_data_ref_count(leaf, ref, num_refs);
		पूर्ण
	पूर्ण
	btrfs_mark_buffer_dirty(leaf);
	ret = 0;
fail:
	btrfs_release_path(path);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक हटाओ_extent_data_ref(काष्ठा btrfs_trans_handle *trans,
					   काष्ठा btrfs_path *path,
					   पूर्णांक refs_to_drop, पूर्णांक *last_ref)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_extent_data_ref *ref1 = शून्य;
	काष्ठा btrfs_shared_data_ref *ref2 = शून्य;
	काष्ठा extent_buffer *leaf;
	u32 num_refs = 0;
	पूर्णांक ret = 0;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);

	अगर (key.type == BTRFS_EXTENT_DATA_REF_KEY) अणु
		ref1 = btrfs_item_ptr(leaf, path->slots[0],
				      काष्ठा btrfs_extent_data_ref);
		num_refs = btrfs_extent_data_ref_count(leaf, ref1);
	पूर्ण अन्यथा अगर (key.type == BTRFS_SHARED_DATA_REF_KEY) अणु
		ref2 = btrfs_item_ptr(leaf, path->slots[0],
				      काष्ठा btrfs_shared_data_ref);
		num_refs = btrfs_shared_data_ref_count(leaf, ref2);
	पूर्ण अन्यथा अगर (unlikely(key.type == BTRFS_EXTENT_REF_V0_KEY)) अणु
		btrfs_prपूर्णांक_v0_err(trans->fs_info);
		btrfs_पात_transaction(trans, -EINVAL);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	BUG_ON(num_refs < refs_to_drop);
	num_refs -= refs_to_drop;

	अगर (num_refs == 0) अणु
		ret = btrfs_del_item(trans, trans->fs_info->extent_root, path);
		*last_ref = 1;
	पूर्ण अन्यथा अणु
		अगर (key.type == BTRFS_EXTENT_DATA_REF_KEY)
			btrfs_set_extent_data_ref_count(leaf, ref1, num_refs);
		अन्यथा अगर (key.type == BTRFS_SHARED_DATA_REF_KEY)
			btrfs_set_shared_data_ref_count(leaf, ref2, num_refs);
		btrfs_mark_buffer_dirty(leaf);
	पूर्ण
	वापस ret;
पूर्ण

अटल noअंतरभूत u32 extent_data_ref_count(काष्ठा btrfs_path *path,
					  काष्ठा btrfs_extent_अंतरभूत_ref *iref)
अणु
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_extent_data_ref *ref1;
	काष्ठा btrfs_shared_data_ref *ref2;
	u32 num_refs = 0;
	पूर्णांक type;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);

	BUG_ON(key.type == BTRFS_EXTENT_REF_V0_KEY);
	अगर (iref) अणु
		/*
		 * If type is invalid, we should have bailed out earlier than
		 * this call.
		 */
		type = btrfs_get_extent_अंतरभूत_ref_type(leaf, iref, BTRFS_REF_TYPE_DATA);
		ASSERT(type != BTRFS_REF_TYPE_INVALID);
		अगर (type == BTRFS_EXTENT_DATA_REF_KEY) अणु
			ref1 = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
			num_refs = btrfs_extent_data_ref_count(leaf, ref1);
		पूर्ण अन्यथा अणु
			ref2 = (काष्ठा btrfs_shared_data_ref *)(iref + 1);
			num_refs = btrfs_shared_data_ref_count(leaf, ref2);
		पूर्ण
	पूर्ण अन्यथा अगर (key.type == BTRFS_EXTENT_DATA_REF_KEY) अणु
		ref1 = btrfs_item_ptr(leaf, path->slots[0],
				      काष्ठा btrfs_extent_data_ref);
		num_refs = btrfs_extent_data_ref_count(leaf, ref1);
	पूर्ण अन्यथा अगर (key.type == BTRFS_SHARED_DATA_REF_KEY) अणु
		ref2 = btrfs_item_ptr(leaf, path->slots[0],
				      काष्ठा btrfs_shared_data_ref);
		num_refs = btrfs_shared_data_ref_count(leaf, ref2);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
	पूर्ण
	वापस num_refs;
पूर्ण

अटल noअंतरभूत पूर्णांक lookup_tree_block_ref(काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_path *path,
					  u64 bytenr, u64 parent,
					  u64 root_objectid)
अणु
	काष्ठा btrfs_root *root = trans->fs_info->extent_root;
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	key.objectid = bytenr;
	अगर (parent) अणु
		key.type = BTRFS_SHARED_BLOCK_REF_KEY;
		key.offset = parent;
	पूर्ण अन्यथा अणु
		key.type = BTRFS_TREE_BLOCK_REF_KEY;
		key.offset = root_objectid;
	पूर्ण

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret > 0)
		ret = -ENOENT;
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक insert_tree_block_ref(काष्ठा btrfs_trans_handle *trans,
					  काष्ठा btrfs_path *path,
					  u64 bytenr, u64 parent,
					  u64 root_objectid)
अणु
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	key.objectid = bytenr;
	अगर (parent) अणु
		key.type = BTRFS_SHARED_BLOCK_REF_KEY;
		key.offset = parent;
	पूर्ण अन्यथा अणु
		key.type = BTRFS_TREE_BLOCK_REF_KEY;
		key.offset = root_objectid;
	पूर्ण

	ret = btrfs_insert_empty_item(trans, trans->fs_info->extent_root,
				      path, &key, 0);
	btrfs_release_path(path);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक extent_ref_type(u64 parent, u64 owner)
अणु
	पूर्णांक type;
	अगर (owner < BTRFS_FIRST_FREE_OBJECTID) अणु
		अगर (parent > 0)
			type = BTRFS_SHARED_BLOCK_REF_KEY;
		अन्यथा
			type = BTRFS_TREE_BLOCK_REF_KEY;
	पूर्ण अन्यथा अणु
		अगर (parent > 0)
			type = BTRFS_SHARED_DATA_REF_KEY;
		अन्यथा
			type = BTRFS_EXTENT_DATA_REF_KEY;
	पूर्ण
	वापस type;
पूर्ण

अटल पूर्णांक find_next_key(काष्ठा btrfs_path *path, पूर्णांक level,
			 काष्ठा btrfs_key *key)

अणु
	क्रम (; level < BTRFS_MAX_LEVEL; level++) अणु
		अगर (!path->nodes[level])
			अवरोध;
		अगर (path->slots[level] + 1 >=
		    btrfs_header_nritems(path->nodes[level]))
			जारी;
		अगर (level == 0)
			btrfs_item_key_to_cpu(path->nodes[level], key,
					      path->slots[level] + 1);
		अन्यथा
			btrfs_node_key_to_cpu(path->nodes[level], key,
					      path->slots[level] + 1);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * look क्रम अंतरभूत back ref. अगर back ref is found, *ref_ret is set
 * to the address of अंतरभूत back ref, and 0 is वापसed.
 *
 * अगर back ref isn't found, *ref_ret is set to the address where it
 * should be inserted, and -ENOENT is वापसed.
 *
 * अगर insert is true and there are too many अंतरभूत back refs, the path
 * poपूर्णांकs to the extent item, and -EAGAIN is वापसed.
 *
 * NOTE: अंतरभूत back refs are ordered in the same way that back ref
 *	 items in the tree are ordered.
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक lookup_अंतरभूत_extent_backref(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_path *path,
				 काष्ठा btrfs_extent_अंतरभूत_ref **ref_ret,
				 u64 bytenr, u64 num_bytes,
				 u64 parent, u64 root_objectid,
				 u64 owner, u64 offset, पूर्णांक insert)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root = fs_info->extent_root;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	u64 flags;
	u64 item_size;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ end;
	पूर्णांक extra_size;
	पूर्णांक type;
	पूर्णांक want;
	पूर्णांक ret;
	पूर्णांक err = 0;
	bool skinny_metadata = btrfs_fs_incompat(fs_info, SKINNY_METADATA);
	पूर्णांक needed;

	key.objectid = bytenr;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	want = extent_ref_type(parent, owner);
	अगर (insert) अणु
		extra_size = btrfs_extent_अंतरभूत_ref_size(want);
		path->search_क्रम_extension = 1;
		path->keep_locks = 1;
	पूर्ण अन्यथा
		extra_size = -1;

	/*
	 * Owner is our level, so we can just add one to get the level क्रम the
	 * block we are पूर्णांकerested in.
	 */
	अगर (skinny_metadata && owner < BTRFS_FIRST_FREE_OBJECTID) अणु
		key.type = BTRFS_METADATA_ITEM_KEY;
		key.offset = owner;
	पूर्ण

again:
	ret = btrfs_search_slot(trans, root, &key, path, extra_size, 1);
	अगर (ret < 0) अणु
		err = ret;
		जाओ out;
	पूर्ण

	/*
	 * We may be a newly converted file प्रणाली which still has the old fat
	 * extent entries क्रम metadata, so try and see अगर we have one of those.
	 */
	अगर (ret > 0 && skinny_metadata) अणु
		skinny_metadata = false;
		अगर (path->slots[0]) अणु
			path->slots[0]--;
			btrfs_item_key_to_cpu(path->nodes[0], &key,
					      path->slots[0]);
			अगर (key.objectid == bytenr &&
			    key.type == BTRFS_EXTENT_ITEM_KEY &&
			    key.offset == num_bytes)
				ret = 0;
		पूर्ण
		अगर (ret) अणु
			key.objectid = bytenr;
			key.type = BTRFS_EXTENT_ITEM_KEY;
			key.offset = num_bytes;
			btrfs_release_path(path);
			जाओ again;
		पूर्ण
	पूर्ण

	अगर (ret && !insert) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण अन्यथा अगर (WARN_ON(ret)) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	अगर (unlikely(item_size < माप(*ei))) अणु
		err = -EINVAL;
		btrfs_prपूर्णांक_v0_err(fs_info);
		btrfs_पात_transaction(trans, err);
		जाओ out;
	पूर्ण

	ei = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_extent_item);
	flags = btrfs_extent_flags(leaf, ei);

	ptr = (अचिन्हित दीर्घ)(ei + 1);
	end = (अचिन्हित दीर्घ)ei + item_size;

	अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK && !skinny_metadata) अणु
		ptr += माप(काष्ठा btrfs_tree_block_info);
		BUG_ON(ptr > end);
	पूर्ण

	अगर (owner >= BTRFS_FIRST_FREE_OBJECTID)
		needed = BTRFS_REF_TYPE_DATA;
	अन्यथा
		needed = BTRFS_REF_TYPE_BLOCK;

	err = -ENOENT;
	जबतक (1) अणु
		अगर (ptr >= end) अणु
			WARN_ON(ptr > end);
			अवरोध;
		पूर्ण
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)ptr;
		type = btrfs_get_extent_अंतरभूत_ref_type(leaf, iref, needed);
		अगर (type == BTRFS_REF_TYPE_INVALID) अणु
			err = -EUCLEAN;
			जाओ out;
		पूर्ण

		अगर (want < type)
			अवरोध;
		अगर (want > type) अणु
			ptr += btrfs_extent_अंतरभूत_ref_size(type);
			जारी;
		पूर्ण

		अगर (type == BTRFS_EXTENT_DATA_REF_KEY) अणु
			काष्ठा btrfs_extent_data_ref *dref;
			dref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
			अगर (match_extent_data_ref(leaf, dref, root_objectid,
						  owner, offset)) अणु
				err = 0;
				अवरोध;
			पूर्ण
			अगर (hash_extent_data_ref_item(leaf, dref) <
			    hash_extent_data_ref(root_objectid, owner, offset))
				अवरोध;
		पूर्ण अन्यथा अणु
			u64 ref_offset;
			ref_offset = btrfs_extent_अंतरभूत_ref_offset(leaf, iref);
			अगर (parent > 0) अणु
				अगर (parent == ref_offset) अणु
					err = 0;
					अवरोध;
				पूर्ण
				अगर (ref_offset < parent)
					अवरोध;
			पूर्ण अन्यथा अणु
				अगर (root_objectid == ref_offset) अणु
					err = 0;
					अवरोध;
				पूर्ण
				अगर (ref_offset < root_objectid)
					अवरोध;
			पूर्ण
		पूर्ण
		ptr += btrfs_extent_अंतरभूत_ref_size(type);
	पूर्ण
	अगर (err == -ENOENT && insert) अणु
		अगर (item_size + extra_size >=
		    BTRFS_MAX_EXTENT_ITEM_SIZE(root)) अणु
			err = -EAGAIN;
			जाओ out;
		पूर्ण
		/*
		 * To add new अंतरभूत back ref, we have to make sure
		 * there is no corresponding back ref item.
		 * For simplicity, we just करो not add new अंतरभूत back
		 * ref अगर there is any kind of item क्रम this block
		 */
		अगर (find_next_key(path, 0, &key) == 0 &&
		    key.objectid == bytenr &&
		    key.type < BTRFS_BLOCK_GROUP_ITEM_KEY) अणु
			err = -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण
	*ref_ret = (काष्ठा btrfs_extent_अंतरभूत_ref *)ptr;
out:
	अगर (insert) अणु
		path->keep_locks = 0;
		path->search_क्रम_extension = 0;
		btrfs_unlock_up_safe(path, 1);
	पूर्ण
	वापस err;
पूर्ण

/*
 * helper to add new अंतरभूत back ref
 */
अटल noअंतरभूत_क्रम_stack
व्योम setup_अंतरभूत_extent_backref(काष्ठा btrfs_fs_info *fs_info,
				 काष्ठा btrfs_path *path,
				 काष्ठा btrfs_extent_अंतरभूत_ref *iref,
				 u64 parent, u64 root_objectid,
				 u64 owner, u64 offset, पूर्णांक refs_to_add,
				 काष्ठा btrfs_delayed_extent_op *extent_op)
अणु
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_extent_item *ei;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ item_offset;
	u64 refs;
	पूर्णांक size;
	पूर्णांक type;

	leaf = path->nodes[0];
	ei = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_extent_item);
	item_offset = (अचिन्हित दीर्घ)iref - (अचिन्हित दीर्घ)ei;

	type = extent_ref_type(parent, owner);
	size = btrfs_extent_अंतरभूत_ref_size(type);

	btrfs_extend_item(path, size);

	ei = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_extent_item);
	refs = btrfs_extent_refs(leaf, ei);
	refs += refs_to_add;
	btrfs_set_extent_refs(leaf, ei, refs);
	अगर (extent_op)
		__run_delayed_extent_op(extent_op, leaf, ei);

	ptr = (अचिन्हित दीर्घ)ei + item_offset;
	end = (अचिन्हित दीर्घ)ei + btrfs_item_size_nr(leaf, path->slots[0]);
	अगर (ptr < end - size)
		स_हटाओ_extent_buffer(leaf, ptr + size, ptr,
				      end - size - ptr);

	iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)ptr;
	btrfs_set_extent_अंतरभूत_ref_type(leaf, iref, type);
	अगर (type == BTRFS_EXTENT_DATA_REF_KEY) अणु
		काष्ठा btrfs_extent_data_ref *dref;
		dref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
		btrfs_set_extent_data_ref_root(leaf, dref, root_objectid);
		btrfs_set_extent_data_ref_objectid(leaf, dref, owner);
		btrfs_set_extent_data_ref_offset(leaf, dref, offset);
		btrfs_set_extent_data_ref_count(leaf, dref, refs_to_add);
	पूर्ण अन्यथा अगर (type == BTRFS_SHARED_DATA_REF_KEY) अणु
		काष्ठा btrfs_shared_data_ref *sref;
		sref = (काष्ठा btrfs_shared_data_ref *)(iref + 1);
		btrfs_set_shared_data_ref_count(leaf, sref, refs_to_add);
		btrfs_set_extent_अंतरभूत_ref_offset(leaf, iref, parent);
	पूर्ण अन्यथा अगर (type == BTRFS_SHARED_BLOCK_REF_KEY) अणु
		btrfs_set_extent_अंतरभूत_ref_offset(leaf, iref, parent);
	पूर्ण अन्यथा अणु
		btrfs_set_extent_अंतरभूत_ref_offset(leaf, iref, root_objectid);
	पूर्ण
	btrfs_mark_buffer_dirty(leaf);
पूर्ण

अटल पूर्णांक lookup_extent_backref(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_path *path,
				 काष्ठा btrfs_extent_अंतरभूत_ref **ref_ret,
				 u64 bytenr, u64 num_bytes, u64 parent,
				 u64 root_objectid, u64 owner, u64 offset)
अणु
	पूर्णांक ret;

	ret = lookup_अंतरभूत_extent_backref(trans, path, ref_ret, bytenr,
					   num_bytes, parent, root_objectid,
					   owner, offset, 0);
	अगर (ret != -ENOENT)
		वापस ret;

	btrfs_release_path(path);
	*ref_ret = शून्य;

	अगर (owner < BTRFS_FIRST_FREE_OBJECTID) अणु
		ret = lookup_tree_block_ref(trans, path, bytenr, parent,
					    root_objectid);
	पूर्ण अन्यथा अणु
		ret = lookup_extent_data_ref(trans, path, bytenr, parent,
					     root_objectid, owner, offset);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * helper to update/हटाओ अंतरभूत back ref
 */
अटल noअंतरभूत_क्रम_stack
व्योम update_अंतरभूत_extent_backref(काष्ठा btrfs_path *path,
				  काष्ठा btrfs_extent_अंतरभूत_ref *iref,
				  पूर्णांक refs_to_mod,
				  काष्ठा btrfs_delayed_extent_op *extent_op,
				  पूर्णांक *last_ref)
अणु
	काष्ठा extent_buffer *leaf = path->nodes[0];
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_extent_data_ref *dref = शून्य;
	काष्ठा btrfs_shared_data_ref *sref = शून्य;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ end;
	u32 item_size;
	पूर्णांक size;
	पूर्णांक type;
	u64 refs;

	ei = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_extent_item);
	refs = btrfs_extent_refs(leaf, ei);
	WARN_ON(refs_to_mod < 0 && refs + refs_to_mod <= 0);
	refs += refs_to_mod;
	btrfs_set_extent_refs(leaf, ei, refs);
	अगर (extent_op)
		__run_delayed_extent_op(extent_op, leaf, ei);

	/*
	 * If type is invalid, we should have bailed out after
	 * lookup_अंतरभूत_extent_backref().
	 */
	type = btrfs_get_extent_अंतरभूत_ref_type(leaf, iref, BTRFS_REF_TYPE_ANY);
	ASSERT(type != BTRFS_REF_TYPE_INVALID);

	अगर (type == BTRFS_EXTENT_DATA_REF_KEY) अणु
		dref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
		refs = btrfs_extent_data_ref_count(leaf, dref);
	पूर्ण अन्यथा अगर (type == BTRFS_SHARED_DATA_REF_KEY) अणु
		sref = (काष्ठा btrfs_shared_data_ref *)(iref + 1);
		refs = btrfs_shared_data_ref_count(leaf, sref);
	पूर्ण अन्यथा अणु
		refs = 1;
		BUG_ON(refs_to_mod != -1);
	पूर्ण

	BUG_ON(refs_to_mod < 0 && refs < -refs_to_mod);
	refs += refs_to_mod;

	अगर (refs > 0) अणु
		अगर (type == BTRFS_EXTENT_DATA_REF_KEY)
			btrfs_set_extent_data_ref_count(leaf, dref, refs);
		अन्यथा
			btrfs_set_shared_data_ref_count(leaf, sref, refs);
	पूर्ण अन्यथा अणु
		*last_ref = 1;
		size =  btrfs_extent_अंतरभूत_ref_size(type);
		item_size = btrfs_item_size_nr(leaf, path->slots[0]);
		ptr = (अचिन्हित दीर्घ)iref;
		end = (अचिन्हित दीर्घ)ei + item_size;
		अगर (ptr + size < end)
			स_हटाओ_extent_buffer(leaf, ptr, ptr + size,
					      end - ptr - size);
		item_size -= size;
		btrfs_truncate_item(path, item_size, 1);
	पूर्ण
	btrfs_mark_buffer_dirty(leaf);
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक insert_अंतरभूत_extent_backref(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_path *path,
				 u64 bytenr, u64 num_bytes, u64 parent,
				 u64 root_objectid, u64 owner,
				 u64 offset, पूर्णांक refs_to_add,
				 काष्ठा btrfs_delayed_extent_op *extent_op)
अणु
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	पूर्णांक ret;

	ret = lookup_अंतरभूत_extent_backref(trans, path, &iref, bytenr,
					   num_bytes, parent, root_objectid,
					   owner, offset, 1);
	अगर (ret == 0) अणु
		/*
		 * We're adding refs to a tree block we alपढ़ोy own, this
		 * should not happen at all.
		 */
		अगर (owner < BTRFS_FIRST_FREE_OBJECTID) अणु
			btrfs_crit(trans->fs_info,
"adding refs to an existing tree ref, bytenr %llu num_bytes %llu root_objectid %llu",
				   bytenr, num_bytes, root_objectid);
			अगर (IS_ENABLED(CONFIG_BTRFS_DEBUG)) अणु
				WARN_ON(1);
				btrfs_crit(trans->fs_info,
			"path->slots[0]=%d path->nodes[0]:", path->slots[0]);
				btrfs_prपूर्णांक_leaf(path->nodes[0]);
			पूर्ण
			वापस -EUCLEAN;
		पूर्ण
		update_अंतरभूत_extent_backref(path, iref, refs_to_add,
					     extent_op, शून्य);
	पूर्ण अन्यथा अगर (ret == -ENOENT) अणु
		setup_अंतरभूत_extent_backref(trans->fs_info, path, iref, parent,
					    root_objectid, owner, offset,
					    refs_to_add, extent_op);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक हटाओ_extent_backref(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_path *path,
				 काष्ठा btrfs_extent_अंतरभूत_ref *iref,
				 पूर्णांक refs_to_drop, पूर्णांक is_data, पूर्णांक *last_ref)
अणु
	पूर्णांक ret = 0;

	BUG_ON(!is_data && refs_to_drop != 1);
	अगर (iref) अणु
		update_अंतरभूत_extent_backref(path, iref, -refs_to_drop, शून्य,
					     last_ref);
	पूर्ण अन्यथा अगर (is_data) अणु
		ret = हटाओ_extent_data_ref(trans, path, refs_to_drop,
					     last_ref);
	पूर्ण अन्यथा अणु
		*last_ref = 1;
		ret = btrfs_del_item(trans, trans->fs_info->extent_root, path);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_issue_discard(काष्ठा block_device *bdev, u64 start, u64 len,
			       u64 *discarded_bytes)
अणु
	पूर्णांक j, ret = 0;
	u64 bytes_left, end;
	u64 aligned_start = ALIGN(start, 1 << 9);

	अगर (WARN_ON(start != aligned_start)) अणु
		len -= aligned_start - start;
		len = round_करोwn(len, 1 << 9);
		start = aligned_start;
	पूर्ण

	*discarded_bytes = 0;

	अगर (!len)
		वापस 0;

	end = start + len;
	bytes_left = len;

	/* Skip any superblocks on this device. */
	क्रम (j = 0; j < BTRFS_SUPER_MIRROR_MAX; j++) अणु
		u64 sb_start = btrfs_sb_offset(j);
		u64 sb_end = sb_start + BTRFS_SUPER_INFO_SIZE;
		u64 size = sb_start - start;

		अगर (!in_range(sb_start, start, bytes_left) &&
		    !in_range(sb_end, start, bytes_left) &&
		    !in_range(start, sb_start, BTRFS_SUPER_INFO_SIZE))
			जारी;

		/*
		 * Superblock spans beginning of range.  Adjust start and
		 * try again.
		 */
		अगर (sb_start <= start) अणु
			start += sb_end - start;
			अगर (start > end) अणु
				bytes_left = 0;
				अवरोध;
			पूर्ण
			bytes_left = end - start;
			जारी;
		पूर्ण

		अगर (size) अणु
			ret = blkdev_issue_discard(bdev, start >> 9, size >> 9,
						   GFP_NOFS, 0);
			अगर (!ret)
				*discarded_bytes += size;
			अन्यथा अगर (ret != -EOPNOTSUPP)
				वापस ret;
		पूर्ण

		start = sb_end;
		अगर (start > end) अणु
			bytes_left = 0;
			अवरोध;
		पूर्ण
		bytes_left = end - start;
	पूर्ण

	अगर (bytes_left) अणु
		ret = blkdev_issue_discard(bdev, start >> 9, bytes_left >> 9,
					   GFP_NOFS, 0);
		अगर (!ret)
			*discarded_bytes += bytes_left;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक करो_discard_extent(काष्ठा btrfs_bio_stripe *stripe, u64 *bytes)
अणु
	काष्ठा btrfs_device *dev = stripe->dev;
	काष्ठा btrfs_fs_info *fs_info = dev->fs_info;
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	u64 phys = stripe->physical;
	u64 len = stripe->length;
	u64 discarded = 0;
	पूर्णांक ret = 0;

	/* Zone reset on a zoned fileप्रणाली */
	अगर (btrfs_can_zone_reset(dev, phys, len)) अणु
		u64 src_disc;

		ret = btrfs_reset_device_zone(dev, phys, len, &discarded);
		अगर (ret)
			जाओ out;

		अगर (!btrfs_dev_replace_is_ongoing(dev_replace) ||
		    dev != dev_replace->srcdev)
			जाओ out;

		src_disc = discarded;

		/* Send to replace target as well */
		ret = btrfs_reset_device_zone(dev_replace->tgtdev, phys, len,
					      &discarded);
		discarded += src_disc;
	पूर्ण अन्यथा अगर (blk_queue_discard(bdev_get_queue(stripe->dev->bdev))) अणु
		ret = btrfs_issue_discard(dev->bdev, phys, len, &discarded);
	पूर्ण अन्यथा अणु
		ret = 0;
		*bytes = 0;
	पूर्ण

out:
	*bytes = discarded;
	वापस ret;
पूर्ण

पूर्णांक btrfs_discard_extent(काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			 u64 num_bytes, u64 *actual_bytes)
अणु
	पूर्णांक ret = 0;
	u64 discarded_bytes = 0;
	u64 end = bytenr + num_bytes;
	u64 cur = bytenr;
	काष्ठा btrfs_bio *bbio = शून्य;


	/*
	 * Aव्योम races with device replace and make sure our bbio has devices
	 * associated to its stripes that करोn't go away जबतक we are discarding.
	 */
	btrfs_bio_counter_inc_blocked(fs_info);
	जबतक (cur < end) अणु
		काष्ठा btrfs_bio_stripe *stripe;
		पूर्णांक i;

		num_bytes = end - cur;
		/* Tell the block device(s) that the sectors can be discarded */
		ret = btrfs_map_block(fs_info, BTRFS_MAP_DISCARD, cur,
				      &num_bytes, &bbio, 0);
		/*
		 * Error can be -ENOMEM, -ENOENT (no such chunk mapping) or
		 * -EOPNOTSUPP. For any such error, @num_bytes is not updated,
		 * thus we can't जारी anyway.
		 */
		अगर (ret < 0)
			जाओ out;

		stripe = bbio->stripes;
		क्रम (i = 0; i < bbio->num_stripes; i++, stripe++) अणु
			u64 bytes;
			काष्ठा btrfs_device *device = stripe->dev;

			अगर (!device->bdev) अणु
				ASSERT(btrfs_test_opt(fs_info, DEGRADED));
				जारी;
			पूर्ण

			अगर (!test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state))
				जारी;

			ret = करो_discard_extent(stripe, &bytes);
			अगर (!ret) अणु
				discarded_bytes += bytes;
			पूर्ण अन्यथा अगर (ret != -EOPNOTSUPP) अणु
				/*
				 * Logic errors or -ENOMEM, or -EIO, but
				 * unlikely to happen.
				 *
				 * And since there are two loops, explicitly
				 * go to out to aव्योम confusion.
				 */
				btrfs_put_bbio(bbio);
				जाओ out;
			पूर्ण

			/*
			 * Just in हाल we get back EOPNOTSUPP क्रम some reason,
			 * just ignore the वापस value so we करोn't screw up
			 * people calling discard_extent.
			 */
			ret = 0;
		पूर्ण
		btrfs_put_bbio(bbio);
		cur += num_bytes;
	पूर्ण
out:
	btrfs_bio_counter_dec(fs_info);

	अगर (actual_bytes)
		*actual_bytes = discarded_bytes;


	अगर (ret == -EOPNOTSUPP)
		ret = 0;
	वापस ret;
पूर्ण

/* Can वापस -ENOMEM */
पूर्णांक btrfs_inc_extent_ref(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_ref *generic_ref)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret;

	ASSERT(generic_ref->type != BTRFS_REF_NOT_SET &&
	       generic_ref->action);
	BUG_ON(generic_ref->type == BTRFS_REF_METADATA &&
	       generic_ref->tree_ref.root == BTRFS_TREE_LOG_OBJECTID);

	अगर (generic_ref->type == BTRFS_REF_METADATA)
		ret = btrfs_add_delayed_tree_ref(trans, generic_ref, शून्य);
	अन्यथा
		ret = btrfs_add_delayed_data_ref(trans, generic_ref, 0);

	btrfs_ref_tree_mod(fs_info, generic_ref);

	वापस ret;
पूर्ण

/*
 * __btrfs_inc_extent_ref - insert backreference क्रम a given extent
 *
 * The counterpart is in __btrfs_मुक्त_extent(), with examples and more details
 * how it works.
 *
 * @trans:	    Handle of transaction
 *
 * @node:	    The delayed ref node used to get the bytenr/length क्रम
 *		    extent whose references are incremented.
 *
 * @parent:	    If this is a shared extent (BTRFS_SHARED_DATA_REF_KEY/
 *		    BTRFS_SHARED_BLOCK_REF_KEY) then it holds the logical
 *		    bytenr of the parent block. Since new extents are always
 *		    created with indirect references, this will only be the हाल
 *		    when relocating a shared extent. In that हाल, root_objectid
 *		    will be BTRFS_TREE_RELOC_OBJECTID. Otheriwse, parent must
 *		    be 0
 *
 * @root_objectid:  The id of the root where this modअगरication has originated,
 *		    this can be either one of the well-known metadata trees or
 *		    the subvolume id which references this extent.
 *
 * @owner:	    For data extents it is the inode number of the owning file.
 *		    For metadata extents this parameter holds the level in the
 *		    tree of the extent.
 *
 * @offset:	    For metadata extents the offset is ignored and is currently
 *		    always passed as 0. For data extents it is the fileoffset
 *		    this extent beदीर्घs to.
 *
 * @refs_to_add     Number of references to add
 *
 * @extent_op       Poपूर्णांकer to a काष्ठाure, holding inक्रमmation necessary when
 *                  updating a tree block's flags
 *
 */
अटल पूर्णांक __btrfs_inc_extent_ref(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_delayed_ref_node *node,
				  u64 parent, u64 root_objectid,
				  u64 owner, u64 offset, पूर्णांक refs_to_add,
				  काष्ठा btrfs_delayed_extent_op *extent_op)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_extent_item *item;
	काष्ठा btrfs_key key;
	u64 bytenr = node->bytenr;
	u64 num_bytes = node->num_bytes;
	u64 refs;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/* this will setup the path even अगर it fails to insert the back ref */
	ret = insert_अंतरभूत_extent_backref(trans, path, bytenr, num_bytes,
					   parent, root_objectid, owner,
					   offset, refs_to_add, extent_op);
	अगर ((ret < 0 && ret != -EAGAIN) || !ret)
		जाओ out;

	/*
	 * Ok we had -EAGAIN which means we didn't have space to insert and
	 * अंतरभूत extent ref, so just update the reference count and add a
	 * normal backref.
	 */
	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
	item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_extent_item);
	refs = btrfs_extent_refs(leaf, item);
	btrfs_set_extent_refs(leaf, item, refs + refs_to_add);
	अगर (extent_op)
		__run_delayed_extent_op(extent_op, leaf, item);

	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	/* now insert the actual backref */
	अगर (owner < BTRFS_FIRST_FREE_OBJECTID) अणु
		BUG_ON(refs_to_add != 1);
		ret = insert_tree_block_ref(trans, path, bytenr, parent,
					    root_objectid);
	पूर्ण अन्यथा अणु
		ret = insert_extent_data_ref(trans, path, bytenr, parent,
					     root_objectid, owner, offset,
					     refs_to_add);
	पूर्ण
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक run_delayed_data_ref(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_delayed_ref_node *node,
				काष्ठा btrfs_delayed_extent_op *extent_op,
				पूर्णांक insert_reserved)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_delayed_data_ref *ref;
	काष्ठा btrfs_key ins;
	u64 parent = 0;
	u64 ref_root = 0;
	u64 flags = 0;

	ins.objectid = node->bytenr;
	ins.offset = node->num_bytes;
	ins.type = BTRFS_EXTENT_ITEM_KEY;

	ref = btrfs_delayed_node_to_data_ref(node);
	trace_run_delayed_data_ref(trans->fs_info, node, ref, node->action);

	अगर (node->type == BTRFS_SHARED_DATA_REF_KEY)
		parent = ref->parent;
	ref_root = ref->root;

	अगर (node->action == BTRFS_ADD_DELAYED_REF && insert_reserved) अणु
		अगर (extent_op)
			flags |= extent_op->flags_to_set;
		ret = alloc_reserved_file_extent(trans, parent, ref_root,
						 flags, ref->objectid,
						 ref->offset, &ins,
						 node->ref_mod);
	पूर्ण अन्यथा अगर (node->action == BTRFS_ADD_DELAYED_REF) अणु
		ret = __btrfs_inc_extent_ref(trans, node, parent, ref_root,
					     ref->objectid, ref->offset,
					     node->ref_mod, extent_op);
	पूर्ण अन्यथा अगर (node->action == BTRFS_DROP_DELAYED_REF) अणु
		ret = __btrfs_मुक्त_extent(trans, node, parent,
					  ref_root, ref->objectid,
					  ref->offset, node->ref_mod,
					  extent_op);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __run_delayed_extent_op(काष्ठा btrfs_delayed_extent_op *extent_op,
				    काष्ठा extent_buffer *leaf,
				    काष्ठा btrfs_extent_item *ei)
अणु
	u64 flags = btrfs_extent_flags(leaf, ei);
	अगर (extent_op->update_flags) अणु
		flags |= extent_op->flags_to_set;
		btrfs_set_extent_flags(leaf, ei, flags);
	पूर्ण

	अगर (extent_op->update_key) अणु
		काष्ठा btrfs_tree_block_info *bi;
		BUG_ON(!(flags & BTRFS_EXTENT_FLAG_TREE_BLOCK));
		bi = (काष्ठा btrfs_tree_block_info *)(ei + 1);
		btrfs_set_tree_block_key(leaf, bi, &extent_op->key);
	पूर्ण
पूर्ण

अटल पूर्णांक run_delayed_extent_op(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_delayed_ref_head *head,
				 काष्ठा btrfs_delayed_extent_op *extent_op)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा extent_buffer *leaf;
	u32 item_size;
	पूर्णांक ret;
	पूर्णांक err = 0;
	पूर्णांक metadata = !extent_op->is_data;

	अगर (TRANS_ABORTED(trans))
		वापस 0;

	अगर (metadata && !btrfs_fs_incompat(fs_info, SKINNY_METADATA))
		metadata = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = head->bytenr;

	अगर (metadata) अणु
		key.type = BTRFS_METADATA_ITEM_KEY;
		key.offset = extent_op->level;
	पूर्ण अन्यथा अणु
		key.type = BTRFS_EXTENT_ITEM_KEY;
		key.offset = head->num_bytes;
	पूर्ण

again:
	ret = btrfs_search_slot(trans, fs_info->extent_root, &key, path, 0, 1);
	अगर (ret < 0) अणु
		err = ret;
		जाओ out;
	पूर्ण
	अगर (ret > 0) अणु
		अगर (metadata) अणु
			अगर (path->slots[0] > 0) अणु
				path->slots[0]--;
				btrfs_item_key_to_cpu(path->nodes[0], &key,
						      path->slots[0]);
				अगर (key.objectid == head->bytenr &&
				    key.type == BTRFS_EXTENT_ITEM_KEY &&
				    key.offset == head->num_bytes)
					ret = 0;
			पूर्ण
			अगर (ret > 0) अणु
				btrfs_release_path(path);
				metadata = 0;

				key.objectid = head->bytenr;
				key.offset = head->num_bytes;
				key.type = BTRFS_EXTENT_ITEM_KEY;
				जाओ again;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);

	अगर (unlikely(item_size < माप(*ei))) अणु
		err = -EINVAL;
		btrfs_prपूर्णांक_v0_err(fs_info);
		btrfs_पात_transaction(trans, err);
		जाओ out;
	पूर्ण

	ei = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_extent_item);
	__run_delayed_extent_op(extent_op, leaf, ei);

	btrfs_mark_buffer_dirty(leaf);
out:
	btrfs_मुक्त_path(path);
	वापस err;
पूर्ण

अटल पूर्णांक run_delayed_tree_ref(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_delayed_ref_node *node,
				काष्ठा btrfs_delayed_extent_op *extent_op,
				पूर्णांक insert_reserved)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_delayed_tree_ref *ref;
	u64 parent = 0;
	u64 ref_root = 0;

	ref = btrfs_delayed_node_to_tree_ref(node);
	trace_run_delayed_tree_ref(trans->fs_info, node, ref, node->action);

	अगर (node->type == BTRFS_SHARED_BLOCK_REF_KEY)
		parent = ref->parent;
	ref_root = ref->root;

	अगर (node->ref_mod != 1) अणु
		btrfs_err(trans->fs_info,
	"btree block(%llu) has %d references rather than 1: action %d ref_root %llu parent %llu",
			  node->bytenr, node->ref_mod, node->action, ref_root,
			  parent);
		वापस -EIO;
	पूर्ण
	अगर (node->action == BTRFS_ADD_DELAYED_REF && insert_reserved) अणु
		BUG_ON(!extent_op || !extent_op->update_flags);
		ret = alloc_reserved_tree_block(trans, node, extent_op);
	पूर्ण अन्यथा अगर (node->action == BTRFS_ADD_DELAYED_REF) अणु
		ret = __btrfs_inc_extent_ref(trans, node, parent, ref_root,
					     ref->level, 0, 1, extent_op);
	पूर्ण अन्यथा अगर (node->action == BTRFS_DROP_DELAYED_REF) अणु
		ret = __btrfs_मुक्त_extent(trans, node, parent, ref_root,
					  ref->level, 0, 1, extent_op);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
	वापस ret;
पूर्ण

/* helper function to actually process a single delayed ref entry */
अटल पूर्णांक run_one_delayed_ref(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_delayed_ref_node *node,
			       काष्ठा btrfs_delayed_extent_op *extent_op,
			       पूर्णांक insert_reserved)
अणु
	पूर्णांक ret = 0;

	अगर (TRANS_ABORTED(trans)) अणु
		अगर (insert_reserved)
			btrfs_pin_extent(trans, node->bytenr, node->num_bytes, 1);
		वापस 0;
	पूर्ण

	अगर (node->type == BTRFS_TREE_BLOCK_REF_KEY ||
	    node->type == BTRFS_SHARED_BLOCK_REF_KEY)
		ret = run_delayed_tree_ref(trans, node, extent_op,
					   insert_reserved);
	अन्यथा अगर (node->type == BTRFS_EXTENT_DATA_REF_KEY ||
		 node->type == BTRFS_SHARED_DATA_REF_KEY)
		ret = run_delayed_data_ref(trans, node, extent_op,
					   insert_reserved);
	अन्यथा
		BUG();
	अगर (ret && insert_reserved)
		btrfs_pin_extent(trans, node->bytenr, node->num_bytes, 1);
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा btrfs_delayed_ref_node *
select_delayed_ref(काष्ठा btrfs_delayed_ref_head *head)
अणु
	काष्ठा btrfs_delayed_ref_node *ref;

	अगर (RB_EMPTY_ROOT(&head->ref_tree.rb_root))
		वापस शून्य;

	/*
	 * Select a delayed ref of type BTRFS_ADD_DELAYED_REF first.
	 * This is to prevent a ref count from going करोwn to zero, which deletes
	 * the extent item from the extent tree, when there still are references
	 * to add, which would fail because they would not find the extent item.
	 */
	अगर (!list_empty(&head->ref_add_list))
		वापस list_first_entry(&head->ref_add_list,
				काष्ठा btrfs_delayed_ref_node, add_list);

	ref = rb_entry(rb_first_cached(&head->ref_tree),
		       काष्ठा btrfs_delayed_ref_node, ref_node);
	ASSERT(list_empty(&ref->add_list));
	वापस ref;
पूर्ण

अटल व्योम unselect_delayed_ref_head(काष्ठा btrfs_delayed_ref_root *delayed_refs,
				      काष्ठा btrfs_delayed_ref_head *head)
अणु
	spin_lock(&delayed_refs->lock);
	head->processing = 0;
	delayed_refs->num_heads_पढ़ोy++;
	spin_unlock(&delayed_refs->lock);
	btrfs_delayed_ref_unlock(head);
पूर्ण

अटल काष्ठा btrfs_delayed_extent_op *cleanup_extent_op(
				काष्ठा btrfs_delayed_ref_head *head)
अणु
	काष्ठा btrfs_delayed_extent_op *extent_op = head->extent_op;

	अगर (!extent_op)
		वापस शून्य;

	अगर (head->must_insert_reserved) अणु
		head->extent_op = शून्य;
		btrfs_मुक्त_delayed_extent_op(extent_op);
		वापस शून्य;
	पूर्ण
	वापस extent_op;
पूर्ण

अटल पूर्णांक run_and_cleanup_extent_op(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_delayed_ref_head *head)
अणु
	काष्ठा btrfs_delayed_extent_op *extent_op;
	पूर्णांक ret;

	extent_op = cleanup_extent_op(head);
	अगर (!extent_op)
		वापस 0;
	head->extent_op = शून्य;
	spin_unlock(&head->lock);
	ret = run_delayed_extent_op(trans, head, extent_op);
	btrfs_मुक्त_delayed_extent_op(extent_op);
	वापस ret ? ret : 1;
पूर्ण

व्योम btrfs_cleanup_ref_head_accounting(काष्ठा btrfs_fs_info *fs_info,
				  काष्ठा btrfs_delayed_ref_root *delayed_refs,
				  काष्ठा btrfs_delayed_ref_head *head)
अणु
	पूर्णांक nr_items = 1;	/* Dropping this ref head update. */

	/*
	 * We had csum deletions accounted क्रम in our delayed refs rsv, we need
	 * to drop the csum leaves क्रम this update from our delayed_refs_rsv.
	 */
	अगर (head->total_ref_mod < 0 && head->is_data) अणु
		spin_lock(&delayed_refs->lock);
		delayed_refs->pending_csums -= head->num_bytes;
		spin_unlock(&delayed_refs->lock);
		nr_items += btrfs_csum_bytes_to_leaves(fs_info, head->num_bytes);
	पूर्ण

	/*
	 * We were dropping refs, or had a new ref and dropped it, and thus must
	 * adjust करोwn our total_bytes_pinned, the space may or may not have
	 * been pinned and so is accounted क्रम properly in the pinned space by
	 * now.
	 */
	अगर (head->total_ref_mod < 0 ||
	    (head->total_ref_mod == 0 && head->must_insert_reserved)) अणु
		u64 flags = btrfs_ref_head_to_space_flags(head);

		btrfs_mod_total_bytes_pinned(fs_info, flags, -head->num_bytes);
	पूर्ण

	btrfs_delayed_refs_rsv_release(fs_info, nr_items);
पूर्ण

अटल पूर्णांक cleanup_ref_head(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_delayed_ref_head *head)
अणु

	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	पूर्णांक ret;

	delayed_refs = &trans->transaction->delayed_refs;

	ret = run_and_cleanup_extent_op(trans, head);
	अगर (ret < 0) अणु
		unselect_delayed_ref_head(delayed_refs, head);
		btrfs_debug(fs_info, "run_delayed_extent_op returned %d", ret);
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		वापस ret;
	पूर्ण

	/*
	 * Need to drop our head ref lock and re-acquire the delayed ref lock
	 * and then re-check to make sure nobody got added.
	 */
	spin_unlock(&head->lock);
	spin_lock(&delayed_refs->lock);
	spin_lock(&head->lock);
	अगर (!RB_EMPTY_ROOT(&head->ref_tree.rb_root) || head->extent_op) अणु
		spin_unlock(&head->lock);
		spin_unlock(&delayed_refs->lock);
		वापस 1;
	पूर्ण
	btrfs_delete_ref_head(delayed_refs, head);
	spin_unlock(&head->lock);
	spin_unlock(&delayed_refs->lock);

	अगर (head->must_insert_reserved) अणु
		btrfs_pin_extent(trans, head->bytenr, head->num_bytes, 1);
		अगर (head->is_data) अणु
			ret = btrfs_del_csums(trans, fs_info->csum_root,
					      head->bytenr, head->num_bytes);
		पूर्ण
	पूर्ण

	btrfs_cleanup_ref_head_accounting(fs_info, delayed_refs, head);

	trace_run_delayed_ref_head(fs_info, head, 0);
	btrfs_delayed_ref_unlock(head);
	btrfs_put_delayed_ref_head(head);
	वापस ret;
पूर्ण

अटल काष्ठा btrfs_delayed_ref_head *btrfs_obtain_ref_head(
					काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_delayed_ref_root *delayed_refs =
		&trans->transaction->delayed_refs;
	काष्ठा btrfs_delayed_ref_head *head = शून्य;
	पूर्णांक ret;

	spin_lock(&delayed_refs->lock);
	head = btrfs_select_ref_head(delayed_refs);
	अगर (!head) अणु
		spin_unlock(&delayed_refs->lock);
		वापस head;
	पूर्ण

	/*
	 * Grab the lock that says we are going to process all the refs क्रम
	 * this head
	 */
	ret = btrfs_delayed_ref_lock(delayed_refs, head);
	spin_unlock(&delayed_refs->lock);

	/*
	 * We may have dropped the spin lock to get the head mutex lock, and
	 * that might have given someone अन्यथा समय to मुक्त the head.  If that's
	 * true, it has been हटाओd from our list and we can move on.
	 */
	अगर (ret == -EAGAIN)
		head = ERR_PTR(-EAGAIN);

	वापस head;
पूर्ण

अटल पूर्णांक btrfs_run_delayed_refs_क्रम_head(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_delayed_ref_head *locked_ref,
				    अचिन्हित दीर्घ *run_refs)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा btrfs_delayed_extent_op *extent_op;
	काष्ठा btrfs_delayed_ref_node *ref;
	पूर्णांक must_insert_reserved = 0;
	पूर्णांक ret;

	delayed_refs = &trans->transaction->delayed_refs;

	lockdep_निश्चित_held(&locked_ref->mutex);
	lockdep_निश्चित_held(&locked_ref->lock);

	जबतक ((ref = select_delayed_ref(locked_ref))) अणु
		अगर (ref->seq &&
		    btrfs_check_delayed_seq(fs_info, ref->seq)) अणु
			spin_unlock(&locked_ref->lock);
			unselect_delayed_ref_head(delayed_refs, locked_ref);
			वापस -EAGAIN;
		पूर्ण

		(*run_refs)++;
		ref->in_tree = 0;
		rb_erase_cached(&ref->ref_node, &locked_ref->ref_tree);
		RB_CLEAR_NODE(&ref->ref_node);
		अगर (!list_empty(&ref->add_list))
			list_del(&ref->add_list);
		/*
		 * When we play the delayed ref, also correct the ref_mod on
		 * head
		 */
		चयन (ref->action) अणु
		हाल BTRFS_ADD_DELAYED_REF:
		हाल BTRFS_ADD_DELAYED_EXTENT:
			locked_ref->ref_mod -= ref->ref_mod;
			अवरोध;
		हाल BTRFS_DROP_DELAYED_REF:
			locked_ref->ref_mod += ref->ref_mod;
			अवरोध;
		शेष:
			WARN_ON(1);
		पूर्ण
		atomic_dec(&delayed_refs->num_entries);

		/*
		 * Record the must_insert_reserved flag beक्रमe we drop the
		 * spin lock.
		 */
		must_insert_reserved = locked_ref->must_insert_reserved;
		locked_ref->must_insert_reserved = 0;

		extent_op = locked_ref->extent_op;
		locked_ref->extent_op = शून्य;
		spin_unlock(&locked_ref->lock);

		ret = run_one_delayed_ref(trans, ref, extent_op,
					  must_insert_reserved);

		btrfs_मुक्त_delayed_extent_op(extent_op);
		अगर (ret) अणु
			unselect_delayed_ref_head(delayed_refs, locked_ref);
			btrfs_put_delayed_ref(ref);
			btrfs_debug(fs_info, "run_one_delayed_ref returned %d",
				    ret);
			वापस ret;
		पूर्ण

		btrfs_put_delayed_ref(ref);
		cond_resched();

		spin_lock(&locked_ref->lock);
		btrfs_merge_delayed_refs(trans, delayed_refs, locked_ref);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Returns 0 on success or अगर called with an alपढ़ोy पातed transaction.
 * Returns -ENOMEM or -EIO on failure and will पात the transaction.
 */
अटल noअंतरभूत पूर्णांक __btrfs_run_delayed_refs(काष्ठा btrfs_trans_handle *trans,
					     अचिन्हित दीर्घ nr)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा btrfs_delayed_ref_head *locked_ref = शून्य;
	kसमय_प्रकार start = kसमय_get();
	पूर्णांक ret;
	अचिन्हित दीर्घ count = 0;
	अचिन्हित दीर्घ actual_count = 0;

	delayed_refs = &trans->transaction->delayed_refs;
	करो अणु
		अगर (!locked_ref) अणु
			locked_ref = btrfs_obtain_ref_head(trans);
			अगर (IS_ERR_OR_शून्य(locked_ref)) अणु
				अगर (PTR_ERR(locked_ref) == -EAGAIN) अणु
					जारी;
				पूर्ण अन्यथा अणु
					अवरोध;
				पूर्ण
			पूर्ण
			count++;
		पूर्ण
		/*
		 * We need to try and merge add/drops of the same ref since we
		 * can run पूर्णांकo issues with relocate dropping the implicit ref
		 * and then it being added back again beक्रमe the drop can
		 * finish.  If we merged anything we need to re-loop so we can
		 * get a good ref.
		 * Or we can get node references of the same type that weren't
		 * merged when created due to bumps in the tree mod seq, and
		 * we need to merge them to prevent adding an अंतरभूत extent
		 * backref beक्रमe dropping it (triggering a BUG_ON at
		 * insert_अंतरभूत_extent_backref()).
		 */
		spin_lock(&locked_ref->lock);
		btrfs_merge_delayed_refs(trans, delayed_refs, locked_ref);

		ret = btrfs_run_delayed_refs_क्रम_head(trans, locked_ref,
						      &actual_count);
		अगर (ret < 0 && ret != -EAGAIN) अणु
			/*
			 * Error, btrfs_run_delayed_refs_क्रम_head alपढ़ोy
			 * unlocked everything so just bail out
			 */
			वापस ret;
		पूर्ण अन्यथा अगर (!ret) अणु
			/*
			 * Success, perक्रमm the usual cleanup of a processed
			 * head
			 */
			ret = cleanup_ref_head(trans, locked_ref);
			अगर (ret > 0 ) अणु
				/* We dropped our lock, we need to loop. */
				ret = 0;
				जारी;
			पूर्ण अन्यथा अगर (ret) अणु
				वापस ret;
			पूर्ण
		पूर्ण

		/*
		 * Either success हाल or btrfs_run_delayed_refs_क्रम_head
		 * वापसed -EAGAIN, meaning we need to select another head
		 */

		locked_ref = शून्य;
		cond_resched();
	पूर्ण जबतक ((nr != -1 && count < nr) || locked_ref);

	/*
	 * We करोn't want to include ref heads since we can have empty ref heads
	 * and those will drastically skew our runसमय करोwn since we just करो
	 * accounting, no actual extent tree updates.
	 */
	अगर (actual_count > 0) अणु
		u64 runसमय = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), start));
		u64 avg;

		/*
		 * We weigh the current average higher than our current runसमय
		 * to aव्योम large swings in the average.
		 */
		spin_lock(&delayed_refs->lock);
		avg = fs_info->avg_delayed_ref_runसमय * 3 + runसमय;
		fs_info->avg_delayed_ref_runसमय = avg >> 2;	/* भाग by 4 */
		spin_unlock(&delayed_refs->lock);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित SCRAMBLE_DELAYED_REFS
/*
 * Normally delayed refs get processed in ascending bytenr order. This
 * correlates in most हालs to the order added. To expose dependencies on this
 * order, we start to process the tree in the middle instead of the beginning
 */
अटल u64 find_middle(काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *n = root->rb_node;
	काष्ठा btrfs_delayed_ref_node *entry;
	पूर्णांक alt = 1;
	u64 middle;
	u64 first = 0, last = 0;

	n = rb_first(root);
	अगर (n) अणु
		entry = rb_entry(n, काष्ठा btrfs_delayed_ref_node, rb_node);
		first = entry->bytenr;
	पूर्ण
	n = rb_last(root);
	अगर (n) अणु
		entry = rb_entry(n, काष्ठा btrfs_delayed_ref_node, rb_node);
		last = entry->bytenr;
	पूर्ण
	n = root->rb_node;

	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा btrfs_delayed_ref_node, rb_node);
		WARN_ON(!entry->in_tree);

		middle = entry->bytenr;

		अगर (alt)
			n = n->rb_left;
		अन्यथा
			n = n->rb_right;

		alt = 1 - alt;
	पूर्ण
	वापस middle;
पूर्ण
#पूर्ण_अगर

/*
 * this starts processing the delayed reference count updates and
 * extent insertions we have queued up so far.  count can be
 * 0, which means to process everything in the tree at the start
 * of the run (but not newly added entries), or it can be some target
 * number you'd like to process.
 *
 * Returns 0 on success or अगर called with an पातed transaction
 * Returns <0 on error and पातs the transaction
 */
पूर्णांक btrfs_run_delayed_refs(काष्ठा btrfs_trans_handle *trans,
			   अचिन्हित दीर्घ count)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा rb_node *node;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा btrfs_delayed_ref_head *head;
	पूर्णांक ret;
	पूर्णांक run_all = count == (अचिन्हित दीर्घ)-1;

	/* We'll clean this up in btrfs_cleanup_transaction */
	अगर (TRANS_ABORTED(trans))
		वापस 0;

	अगर (test_bit(BTRFS_FS_CREATING_FREE_SPACE_TREE, &fs_info->flags))
		वापस 0;

	delayed_refs = &trans->transaction->delayed_refs;
	अगर (count == 0)
		count = delayed_refs->num_heads_पढ़ोy;

again:
#अगर_घोषित SCRAMBLE_DELAYED_REFS
	delayed_refs->run_delayed_start = find_middle(&delayed_refs->root);
#पूर्ण_अगर
	ret = __btrfs_run_delayed_refs(trans, count);
	अगर (ret < 0) अणु
		btrfs_पात_transaction(trans, ret);
		वापस ret;
	पूर्ण

	अगर (run_all) अणु
		btrfs_create_pending_block_groups(trans);

		spin_lock(&delayed_refs->lock);
		node = rb_first_cached(&delayed_refs->href_root);
		अगर (!node) अणु
			spin_unlock(&delayed_refs->lock);
			जाओ out;
		पूर्ण
		head = rb_entry(node, काष्ठा btrfs_delayed_ref_head,
				href_node);
		refcount_inc(&head->refs);
		spin_unlock(&delayed_refs->lock);

		/* Mutex was contended, block until it's released and retry. */
		mutex_lock(&head->mutex);
		mutex_unlock(&head->mutex);

		btrfs_put_delayed_ref_head(head);
		cond_resched();
		जाओ again;
	पूर्ण
out:
	वापस 0;
पूर्ण

पूर्णांक btrfs_set_disk_extent_flags(काष्ठा btrfs_trans_handle *trans,
				काष्ठा extent_buffer *eb, u64 flags,
				पूर्णांक level, पूर्णांक is_data)
अणु
	काष्ठा btrfs_delayed_extent_op *extent_op;
	पूर्णांक ret;

	extent_op = btrfs_alloc_delayed_extent_op();
	अगर (!extent_op)
		वापस -ENOMEM;

	extent_op->flags_to_set = flags;
	extent_op->update_flags = true;
	extent_op->update_key = false;
	extent_op->is_data = is_data ? true : false;
	extent_op->level = level;

	ret = btrfs_add_delayed_extent_op(trans, eb->start, eb->len, extent_op);
	अगर (ret)
		btrfs_मुक्त_delayed_extent_op(extent_op);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक check_delayed_ref(काष्ठा btrfs_root *root,
				      काष्ठा btrfs_path *path,
				      u64 objectid, u64 offset, u64 bytenr)
अणु
	काष्ठा btrfs_delayed_ref_head *head;
	काष्ठा btrfs_delayed_ref_node *ref;
	काष्ठा btrfs_delayed_data_ref *data_ref;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा btrfs_transaction *cur_trans;
	काष्ठा rb_node *node;
	पूर्णांक ret = 0;

	spin_lock(&root->fs_info->trans_lock);
	cur_trans = root->fs_info->running_transaction;
	अगर (cur_trans)
		refcount_inc(&cur_trans->use_count);
	spin_unlock(&root->fs_info->trans_lock);
	अगर (!cur_trans)
		वापस 0;

	delayed_refs = &cur_trans->delayed_refs;
	spin_lock(&delayed_refs->lock);
	head = btrfs_find_delayed_ref_head(delayed_refs, bytenr);
	अगर (!head) अणु
		spin_unlock(&delayed_refs->lock);
		btrfs_put_transaction(cur_trans);
		वापस 0;
	पूर्ण

	अगर (!mutex_trylock(&head->mutex)) अणु
		refcount_inc(&head->refs);
		spin_unlock(&delayed_refs->lock);

		btrfs_release_path(path);

		/*
		 * Mutex was contended, block until it's released and let
		 * caller try again
		 */
		mutex_lock(&head->mutex);
		mutex_unlock(&head->mutex);
		btrfs_put_delayed_ref_head(head);
		btrfs_put_transaction(cur_trans);
		वापस -EAGAIN;
	पूर्ण
	spin_unlock(&delayed_refs->lock);

	spin_lock(&head->lock);
	/*
	 * XXX: We should replace this with a proper search function in the
	 * future.
	 */
	क्रम (node = rb_first_cached(&head->ref_tree); node;
	     node = rb_next(node)) अणु
		ref = rb_entry(node, काष्ठा btrfs_delayed_ref_node, ref_node);
		/* If it's a shared ref we know a cross reference exists */
		अगर (ref->type != BTRFS_EXTENT_DATA_REF_KEY) अणु
			ret = 1;
			अवरोध;
		पूर्ण

		data_ref = btrfs_delayed_node_to_data_ref(ref);

		/*
		 * If our ref करोesn't match the one we're currently looking at
		 * then we have a cross reference.
		 */
		अगर (data_ref->root != root->root_key.objectid ||
		    data_ref->objectid != objectid ||
		    data_ref->offset != offset) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&head->lock);
	mutex_unlock(&head->mutex);
	btrfs_put_transaction(cur_trans);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक check_committed_ref(काष्ठा btrfs_root *root,
					काष्ठा btrfs_path *path,
					u64 objectid, u64 offset, u64 bytenr,
					bool strict)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *extent_root = fs_info->extent_root;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_extent_data_ref *ref;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_key key;
	u32 item_size;
	पूर्णांक type;
	पूर्णांक ret;

	key.objectid = bytenr;
	key.offset = (u64)-1;
	key.type = BTRFS_EXTENT_ITEM_KEY;

	ret = btrfs_search_slot(शून्य, extent_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	BUG_ON(ret == 0); /* Corruption */

	ret = -ENOENT;
	अगर (path->slots[0] == 0)
		जाओ out;

	path->slots[0]--;
	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);

	अगर (key.objectid != bytenr || key.type != BTRFS_EXTENT_ITEM_KEY)
		जाओ out;

	ret = 1;
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	ei = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_extent_item);

	/* If extent item has more than 1 अंतरभूत ref then it's shared */
	अगर (item_size != माप(*ei) +
	    btrfs_extent_अंतरभूत_ref_size(BTRFS_EXTENT_DATA_REF_KEY))
		जाओ out;

	/*
	 * If extent created beक्रमe last snapshot => it's shared unless the
	 * snapshot has been deleted. Use the heuristic अगर strict is false.
	 */
	अगर (!strict &&
	    (btrfs_extent_generation(leaf, ei) <=
	     btrfs_root_last_snapshot(&root->root_item)))
		जाओ out;

	iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(ei + 1);

	/* If this extent has SHARED_DATA_REF then it's shared */
	type = btrfs_get_extent_अंतरभूत_ref_type(leaf, iref, BTRFS_REF_TYPE_DATA);
	अगर (type != BTRFS_EXTENT_DATA_REF_KEY)
		जाओ out;

	ref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
	अगर (btrfs_extent_refs(leaf, ei) !=
	    btrfs_extent_data_ref_count(leaf, ref) ||
	    btrfs_extent_data_ref_root(leaf, ref) !=
	    root->root_key.objectid ||
	    btrfs_extent_data_ref_objectid(leaf, ref) != objectid ||
	    btrfs_extent_data_ref_offset(leaf, ref) != offset)
		जाओ out;

	ret = 0;
out:
	वापस ret;
पूर्ण

पूर्णांक btrfs_cross_ref_exist(काष्ठा btrfs_root *root, u64 objectid, u64 offset,
			  u64 bytenr, bool strict)
अणु
	काष्ठा btrfs_path *path;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	करो अणु
		ret = check_committed_ref(root, path, objectid,
					  offset, bytenr, strict);
		अगर (ret && ret != -ENOENT)
			जाओ out;

		ret = check_delayed_ref(root, path, objectid, offset, bytenr);
	पूर्ण जबतक (ret == -EAGAIN);

out:
	btrfs_मुक्त_path(path);
	अगर (root->root_key.objectid == BTRFS_DATA_RELOC_TREE_OBJECTID)
		WARN_ON(ret > 0);
	वापस ret;
पूर्ण

अटल पूर्णांक __btrfs_mod_ref(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   काष्ठा extent_buffer *buf,
			   पूर्णांक full_backref, पूर्णांक inc)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 bytenr;
	u64 num_bytes;
	u64 parent;
	u64 ref_root;
	u32 nritems;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा btrfs_ref generic_ref = अणु 0 पूर्ण;
	bool क्रम_reloc = btrfs_header_flag(buf, BTRFS_HEADER_FLAG_RELOC);
	पूर्णांक i;
	पूर्णांक action;
	पूर्णांक level;
	पूर्णांक ret = 0;

	अगर (btrfs_is_testing(fs_info))
		वापस 0;

	ref_root = btrfs_header_owner(buf);
	nritems = btrfs_header_nritems(buf);
	level = btrfs_header_level(buf);

	अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state) && level == 0)
		वापस 0;

	अगर (full_backref)
		parent = buf->start;
	अन्यथा
		parent = 0;
	अगर (inc)
		action = BTRFS_ADD_DELAYED_REF;
	अन्यथा
		action = BTRFS_DROP_DELAYED_REF;

	क्रम (i = 0; i < nritems; i++) अणु
		अगर (level == 0) अणु
			btrfs_item_key_to_cpu(buf, &key, i);
			अगर (key.type != BTRFS_EXTENT_DATA_KEY)
				जारी;
			fi = btrfs_item_ptr(buf, i,
					    काष्ठा btrfs_file_extent_item);
			अगर (btrfs_file_extent_type(buf, fi) ==
			    BTRFS_खाता_EXTENT_INLINE)
				जारी;
			bytenr = btrfs_file_extent_disk_bytenr(buf, fi);
			अगर (bytenr == 0)
				जारी;

			num_bytes = btrfs_file_extent_disk_num_bytes(buf, fi);
			key.offset -= btrfs_file_extent_offset(buf, fi);
			btrfs_init_generic_ref(&generic_ref, action, bytenr,
					       num_bytes, parent);
			generic_ref.real_root = root->root_key.objectid;
			btrfs_init_data_ref(&generic_ref, ref_root, key.objectid,
					    key.offset);
			generic_ref.skip_qgroup = क्रम_reloc;
			अगर (inc)
				ret = btrfs_inc_extent_ref(trans, &generic_ref);
			अन्यथा
				ret = btrfs_मुक्त_extent(trans, &generic_ref);
			अगर (ret)
				जाओ fail;
		पूर्ण अन्यथा अणु
			bytenr = btrfs_node_blockptr(buf, i);
			num_bytes = fs_info->nodesize;
			btrfs_init_generic_ref(&generic_ref, action, bytenr,
					       num_bytes, parent);
			generic_ref.real_root = root->root_key.objectid;
			btrfs_init_tree_ref(&generic_ref, level - 1, ref_root);
			generic_ref.skip_qgroup = क्रम_reloc;
			अगर (inc)
				ret = btrfs_inc_extent_ref(trans, &generic_ref);
			अन्यथा
				ret = btrfs_मुक्त_extent(trans, &generic_ref);
			अगर (ret)
				जाओ fail;
		पूर्ण
	पूर्ण
	वापस 0;
fail:
	वापस ret;
पूर्ण

पूर्णांक btrfs_inc_ref(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		  काष्ठा extent_buffer *buf, पूर्णांक full_backref)
अणु
	वापस __btrfs_mod_ref(trans, root, buf, full_backref, 1);
पूर्ण

पूर्णांक btrfs_dec_ref(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		  काष्ठा extent_buffer *buf, पूर्णांक full_backref)
अणु
	वापस __btrfs_mod_ref(trans, root, buf, full_backref, 0);
पूर्ण

अटल u64 get_alloc_profile_by_root(काष्ठा btrfs_root *root, पूर्णांक data)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 flags;
	u64 ret;

	अगर (data)
		flags = BTRFS_BLOCK_GROUP_DATA;
	अन्यथा अगर (root == fs_info->chunk_root)
		flags = BTRFS_BLOCK_GROUP_SYSTEM;
	अन्यथा
		flags = BTRFS_BLOCK_GROUP_METADATA;

	ret = btrfs_get_alloc_profile(fs_info, flags);
	वापस ret;
पूर्ण

अटल u64 first_logical_byte(काष्ठा btrfs_fs_info *fs_info, u64 search_start)
अणु
	काष्ठा btrfs_block_group *cache;
	u64 bytenr;

	spin_lock(&fs_info->block_group_cache_lock);
	bytenr = fs_info->first_logical_byte;
	spin_unlock(&fs_info->block_group_cache_lock);

	अगर (bytenr < (u64)-1)
		वापस bytenr;

	cache = btrfs_lookup_first_block_group(fs_info, search_start);
	अगर (!cache)
		वापस 0;

	bytenr = cache->start;
	btrfs_put_block_group(cache);

	वापस bytenr;
पूर्ण

अटल पूर्णांक pin_करोwn_extent(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_block_group *cache,
			   u64 bytenr, u64 num_bytes, पूर्णांक reserved)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;

	spin_lock(&cache->space_info->lock);
	spin_lock(&cache->lock);
	cache->pinned += num_bytes;
	btrfs_space_info_update_bytes_pinned(fs_info, cache->space_info,
					     num_bytes);
	अगर (reserved) अणु
		cache->reserved -= num_bytes;
		cache->space_info->bytes_reserved -= num_bytes;
	पूर्ण
	spin_unlock(&cache->lock);
	spin_unlock(&cache->space_info->lock);

	__btrfs_mod_total_bytes_pinned(cache->space_info, num_bytes);
	set_extent_dirty(&trans->transaction->pinned_extents, bytenr,
			 bytenr + num_bytes - 1, GFP_NOFS | __GFP_NOFAIL);
	वापस 0;
पूर्ण

पूर्णांक btrfs_pin_extent(काष्ठा btrfs_trans_handle *trans,
		     u64 bytenr, u64 num_bytes, पूर्णांक reserved)
अणु
	काष्ठा btrfs_block_group *cache;

	cache = btrfs_lookup_block_group(trans->fs_info, bytenr);
	BUG_ON(!cache); /* Logic error */

	pin_करोwn_extent(trans, cache, bytenr, num_bytes, reserved);

	btrfs_put_block_group(cache);
	वापस 0;
पूर्ण

/*
 * this function must be called within transaction
 */
पूर्णांक btrfs_pin_extent_क्रम_log_replay(काष्ठा btrfs_trans_handle *trans,
				    u64 bytenr, u64 num_bytes)
अणु
	काष्ठा btrfs_block_group *cache;
	पूर्णांक ret;

	cache = btrfs_lookup_block_group(trans->fs_info, bytenr);
	अगर (!cache)
		वापस -EINVAL;

	/*
	 * pull in the मुक्त space cache (अगर any) so that our pin
	 * हटाओs the मुक्त space from the cache.  We have load_only set
	 * to one because the slow code to पढ़ो in the मुक्त extents करोes check
	 * the pinned extents.
	 */
	btrfs_cache_block_group(cache, 1);
	/*
	 * Make sure we रुको until the cache is completely built in हाल it is
	 * missing or is invalid and thereक्रमe needs to be rebuilt.
	 */
	ret = btrfs_रुको_block_group_cache_करोne(cache);
	अगर (ret)
		जाओ out;

	pin_करोwn_extent(trans, cache, bytenr, num_bytes, 0);

	/* हटाओ us from the मुक्त space cache (अगर we're there at all) */
	ret = btrfs_हटाओ_मुक्त_space(cache, bytenr, num_bytes);
out:
	btrfs_put_block_group(cache);
	वापस ret;
पूर्ण

अटल पूर्णांक __exclude_logged_extent(काष्ठा btrfs_fs_info *fs_info,
				   u64 start, u64 num_bytes)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_block_group *block_group;

	block_group = btrfs_lookup_block_group(fs_info, start);
	अगर (!block_group)
		वापस -EINVAL;

	btrfs_cache_block_group(block_group, 1);
	/*
	 * Make sure we रुको until the cache is completely built in हाल it is
	 * missing or is invalid and thereक्रमe needs to be rebuilt.
	 */
	ret = btrfs_रुको_block_group_cache_करोne(block_group);
	अगर (ret)
		जाओ out;

	ret = btrfs_हटाओ_मुक्त_space(block_group, start, num_bytes);
out:
	btrfs_put_block_group(block_group);
	वापस ret;
पूर्ण

पूर्णांक btrfs_exclude_logged_extents(काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा btrfs_file_extent_item *item;
	काष्ठा btrfs_key key;
	पूर्णांक found_type;
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!btrfs_fs_incompat(fs_info, MIXED_GROUPS))
		वापस 0;

	क्रम (i = 0; i < btrfs_header_nritems(eb); i++) अणु
		btrfs_item_key_to_cpu(eb, &key, i);
		अगर (key.type != BTRFS_EXTENT_DATA_KEY)
			जारी;
		item = btrfs_item_ptr(eb, i, काष्ठा btrfs_file_extent_item);
		found_type = btrfs_file_extent_type(eb, item);
		अगर (found_type == BTRFS_खाता_EXTENT_INLINE)
			जारी;
		अगर (btrfs_file_extent_disk_bytenr(eb, item) == 0)
			जारी;
		key.objectid = btrfs_file_extent_disk_bytenr(eb, item);
		key.offset = btrfs_file_extent_disk_num_bytes(eb, item);
		ret = __exclude_logged_extent(fs_info, key.objectid, key.offset);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
btrfs_inc_block_group_reservations(काष्ठा btrfs_block_group *bg)
अणु
	atomic_inc(&bg->reservations);
पूर्ण

/*
 * Returns the मुक्त cluster क्रम the given space info and sets empty_cluster to
 * what it should be based on the mount options.
 */
अटल काष्ठा btrfs_मुक्त_cluster *
fetch_cluster_info(काष्ठा btrfs_fs_info *fs_info,
		   काष्ठा btrfs_space_info *space_info, u64 *empty_cluster)
अणु
	काष्ठा btrfs_मुक्त_cluster *ret = शून्य;

	*empty_cluster = 0;
	अगर (btrfs_mixed_space_info(space_info))
		वापस ret;

	अगर (space_info->flags & BTRFS_BLOCK_GROUP_METADATA) अणु
		ret = &fs_info->meta_alloc_cluster;
		अगर (btrfs_test_opt(fs_info, SSD))
			*empty_cluster = SZ_2M;
		अन्यथा
			*empty_cluster = SZ_64K;
	पूर्ण अन्यथा अगर ((space_info->flags & BTRFS_BLOCK_GROUP_DATA) &&
		   btrfs_test_opt(fs_info, SSD_SPREAD)) अणु
		*empty_cluster = SZ_2M;
		ret = &fs_info->data_alloc_cluster;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक unpin_extent_range(काष्ठा btrfs_fs_info *fs_info,
			      u64 start, u64 end,
			      स्थिर bool वापस_मुक्त_space)
अणु
	काष्ठा btrfs_block_group *cache = शून्य;
	काष्ठा btrfs_space_info *space_info;
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	काष्ठा btrfs_मुक्त_cluster *cluster = शून्य;
	u64 len;
	u64 total_unpinned = 0;
	u64 empty_cluster = 0;
	bool पढ़ोonly;

	जबतक (start <= end) अणु
		पढ़ोonly = false;
		अगर (!cache ||
		    start >= cache->start + cache->length) अणु
			अगर (cache)
				btrfs_put_block_group(cache);
			total_unpinned = 0;
			cache = btrfs_lookup_block_group(fs_info, start);
			BUG_ON(!cache); /* Logic error */

			cluster = fetch_cluster_info(fs_info,
						     cache->space_info,
						     &empty_cluster);
			empty_cluster <<= 1;
		पूर्ण

		len = cache->start + cache->length - start;
		len = min(len, end + 1 - start);

		करोwn_पढ़ो(&fs_info->commit_root_sem);
		अगर (start < cache->last_byte_to_unpin && वापस_मुक्त_space) अणु
			u64 add_len = min(len, cache->last_byte_to_unpin - start);

			btrfs_add_मुक्त_space(cache, start, add_len);
		पूर्ण
		up_पढ़ो(&fs_info->commit_root_sem);

		start += len;
		total_unpinned += len;
		space_info = cache->space_info;

		/*
		 * If this space cluster has been marked as fragmented and we've
		 * unpinned enough in this block group to potentially allow a
		 * cluster to be created inside of it go ahead and clear the
		 * fragmented check.
		 */
		अगर (cluster && cluster->fragmented &&
		    total_unpinned > empty_cluster) अणु
			spin_lock(&cluster->lock);
			cluster->fragmented = 0;
			spin_unlock(&cluster->lock);
		पूर्ण

		spin_lock(&space_info->lock);
		spin_lock(&cache->lock);
		cache->pinned -= len;
		btrfs_space_info_update_bytes_pinned(fs_info, space_info, -len);
		space_info->max_extent_size = 0;
		__btrfs_mod_total_bytes_pinned(space_info, -len);
		अगर (cache->ro) अणु
			space_info->bytes_पढ़ोonly += len;
			पढ़ोonly = true;
		पूर्ण अन्यथा अगर (btrfs_is_zoned(fs_info)) अणु
			/* Need reset beक्रमe reusing in a zoned block group */
			space_info->bytes_zone_unusable += len;
			पढ़ोonly = true;
		पूर्ण
		spin_unlock(&cache->lock);
		अगर (!पढ़ोonly && वापस_मुक्त_space &&
		    global_rsv->space_info == space_info) अणु
			u64 to_add = len;

			spin_lock(&global_rsv->lock);
			अगर (!global_rsv->full) अणु
				to_add = min(len, global_rsv->size -
					     global_rsv->reserved);
				global_rsv->reserved += to_add;
				btrfs_space_info_update_bytes_may_use(fs_info,
						space_info, to_add);
				अगर (global_rsv->reserved >= global_rsv->size)
					global_rsv->full = 1;
				len -= to_add;
			पूर्ण
			spin_unlock(&global_rsv->lock);
		पूर्ण
		/* Add to any tickets we may have */
		अगर (!पढ़ोonly && वापस_मुक्त_space && len)
			btrfs_try_granting_tickets(fs_info, space_info);
		spin_unlock(&space_info->lock);
	पूर्ण

	अगर (cache)
		btrfs_put_block_group(cache);
	वापस 0;
पूर्ण

पूर्णांक btrfs_finish_extent_commit(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_block_group *block_group, *पंचांगp;
	काष्ठा list_head *deleted_bgs;
	काष्ठा extent_io_tree *unpin;
	u64 start;
	u64 end;
	पूर्णांक ret;

	unpin = &trans->transaction->pinned_extents;

	जबतक (!TRANS_ABORTED(trans)) अणु
		काष्ठा extent_state *cached_state = शून्य;

		mutex_lock(&fs_info->unused_bg_unpin_mutex);
		ret = find_first_extent_bit(unpin, 0, &start, &end,
					    EXTENT_सूचीTY, &cached_state);
		अगर (ret) अणु
			mutex_unlock(&fs_info->unused_bg_unpin_mutex);
			अवरोध;
		पूर्ण

		अगर (btrfs_test_opt(fs_info, DISCARD_SYNC))
			ret = btrfs_discard_extent(fs_info, start,
						   end + 1 - start, शून्य);

		clear_extent_dirty(unpin, start, end, &cached_state);
		unpin_extent_range(fs_info, start, end, true);
		mutex_unlock(&fs_info->unused_bg_unpin_mutex);
		मुक्त_extent_state(cached_state);
		cond_resched();
	पूर्ण

	अगर (btrfs_test_opt(fs_info, DISCARD_ASYNC)) अणु
		btrfs_discard_calc_delay(&fs_info->discard_ctl);
		btrfs_discard_schedule_work(&fs_info->discard_ctl, true);
	पूर्ण

	/*
	 * Transaction is finished.  We करोn't need the lock anymore.  We
	 * करो need to clean up the block groups in हाल of a transaction
	 * पात.
	 */
	deleted_bgs = &trans->transaction->deleted_bgs;
	list_क्रम_each_entry_safe(block_group, पंचांगp, deleted_bgs, bg_list) अणु
		u64 trimmed = 0;

		ret = -EROFS;
		अगर (!TRANS_ABORTED(trans))
			ret = btrfs_discard_extent(fs_info,
						   block_group->start,
						   block_group->length,
						   &trimmed);

		list_del_init(&block_group->bg_list);
		btrfs_unमुक्तze_block_group(block_group);
		btrfs_put_block_group(block_group);

		अगर (ret) अणु
			स्थिर अक्षर *errstr = btrfs_decode_error(ret);
			btrfs_warn(fs_info,
			   "discard failed while removing blockgroup: errno=%d %s",
				   ret, errstr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Drop one or more refs of @node.
 *
 * 1. Locate the extent refs.
 *    It's either अंतरभूत in EXTENT/METADATA_ITEM or in keyed SHARED_* item.
 *    Locate it, then reduce the refs number or हटाओ the ref line completely.
 *
 * 2. Update the refs count in EXTENT/METADATA_ITEM
 *
 * Inline backref हाल:
 *
 * in extent tree we have:
 *
 * 	item 0 key (13631488 EXTENT_ITEM 1048576) itemoff 16201 itemsize 82
 *		refs 2 gen 6 flags DATA
 *		extent data backref root FS_TREE objectid 258 offset 0 count 1
 *		extent data backref root FS_TREE objectid 257 offset 0 count 1
 *
 * This function माला_लो called with:
 *
 *    node->bytenr = 13631488
 *    node->num_bytes = 1048576
 *    root_objectid = FS_TREE
 *    owner_objectid = 257
 *    owner_offset = 0
 *    refs_to_drop = 1
 *
 * Then we should get some like:
 *
 * 	item 0 key (13631488 EXTENT_ITEM 1048576) itemoff 16201 itemsize 82
 *		refs 1 gen 6 flags DATA
 *		extent data backref root FS_TREE objectid 258 offset 0 count 1
 *
 * Keyed backref हाल:
 *
 * in extent tree we have:
 *
 *	item 0 key (13631488 EXTENT_ITEM 1048576) itemoff 3971 itemsize 24
 *		refs 754 gen 6 flags DATA
 *	[...]
 *	item 2 key (13631488 EXTENT_DATA_REF <HASH>) itemoff 3915 itemsize 28
 *		extent data backref root FS_TREE objectid 866 offset 0 count 1
 *
 * This function get called with:
 *
 *    node->bytenr = 13631488
 *    node->num_bytes = 1048576
 *    root_objectid = FS_TREE
 *    owner_objectid = 866
 *    owner_offset = 0
 *    refs_to_drop = 1
 *
 * Then we should get some like:
 *
 *	item 0 key (13631488 EXTENT_ITEM 1048576) itemoff 3971 itemsize 24
 *		refs 753 gen 6 flags DATA
 *
 * And that (13631488 EXTENT_DATA_REF <HASH>) माला_लो हटाओd.
 */
अटल पूर्णांक __btrfs_मुक्त_extent(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_delayed_ref_node *node, u64 parent,
			       u64 root_objectid, u64 owner_objectid,
			       u64 owner_offset, पूर्णांक refs_to_drop,
			       काष्ठा btrfs_delayed_extent_op *extent_op)
अणु
	काष्ठा btrfs_fs_info *info = trans->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *extent_root = info->extent_root;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	पूर्णांक ret;
	पूर्णांक is_data;
	पूर्णांक extent_slot = 0;
	पूर्णांक found_extent = 0;
	पूर्णांक num_to_del = 1;
	u32 item_size;
	u64 refs;
	u64 bytenr = node->bytenr;
	u64 num_bytes = node->num_bytes;
	पूर्णांक last_ref = 0;
	bool skinny_metadata = btrfs_fs_incompat(info, SKINNY_METADATA);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	is_data = owner_objectid >= BTRFS_FIRST_FREE_OBJECTID;

	अगर (!is_data && refs_to_drop != 1) अणु
		btrfs_crit(info,
"invalid refs_to_drop, dropping more than 1 refs for tree block %llu refs_to_drop %u",
			   node->bytenr, refs_to_drop);
		ret = -EINVAL;
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	अगर (is_data)
		skinny_metadata = false;

	ret = lookup_extent_backref(trans, path, &iref, bytenr, num_bytes,
				    parent, root_objectid, owner_objectid,
				    owner_offset);
	अगर (ret == 0) अणु
		/*
		 * Either the अंतरभूत backref or the SHARED_DATA_REF/
		 * SHARED_BLOCK_REF is found
		 *
		 * Here is a quick path to locate EXTENT/METADATA_ITEM.
		 * It's possible the EXTENT/METADATA_ITEM is near current slot.
		 */
		extent_slot = path->slots[0];
		जबतक (extent_slot >= 0) अणु
			btrfs_item_key_to_cpu(path->nodes[0], &key,
					      extent_slot);
			अगर (key.objectid != bytenr)
				अवरोध;
			अगर (key.type == BTRFS_EXTENT_ITEM_KEY &&
			    key.offset == num_bytes) अणु
				found_extent = 1;
				अवरोध;
			पूर्ण
			अगर (key.type == BTRFS_METADATA_ITEM_KEY &&
			    key.offset == owner_objectid) अणु
				found_extent = 1;
				अवरोध;
			पूर्ण

			/* Quick path didn't find the EXTEMT/METADATA_ITEM */
			अगर (path->slots[0] - extent_slot > 5)
				अवरोध;
			extent_slot--;
		पूर्ण

		अगर (!found_extent) अणु
			अगर (iref) अणु
				btrfs_crit(info,
"invalid iref, no EXTENT/METADATA_ITEM found but has inline extent ref");
				btrfs_पात_transaction(trans, -EUCLEAN);
				जाओ err_dump;
			पूर्ण
			/* Must be SHARED_* item, हटाओ the backref first */
			ret = हटाओ_extent_backref(trans, path, शून्य,
						    refs_to_drop,
						    is_data, &last_ref);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				जाओ out;
			पूर्ण
			btrfs_release_path(path);

			/* Slow path to locate EXTENT/METADATA_ITEM */
			key.objectid = bytenr;
			key.type = BTRFS_EXTENT_ITEM_KEY;
			key.offset = num_bytes;

			अगर (!is_data && skinny_metadata) अणु
				key.type = BTRFS_METADATA_ITEM_KEY;
				key.offset = owner_objectid;
			पूर्ण

			ret = btrfs_search_slot(trans, extent_root,
						&key, path, -1, 1);
			अगर (ret > 0 && skinny_metadata && path->slots[0]) अणु
				/*
				 * Couldn't find our skinny metadata item,
				 * see अगर we have ye olde extent item.
				 */
				path->slots[0]--;
				btrfs_item_key_to_cpu(path->nodes[0], &key,
						      path->slots[0]);
				अगर (key.objectid == bytenr &&
				    key.type == BTRFS_EXTENT_ITEM_KEY &&
				    key.offset == num_bytes)
					ret = 0;
			पूर्ण

			अगर (ret > 0 && skinny_metadata) अणु
				skinny_metadata = false;
				key.objectid = bytenr;
				key.type = BTRFS_EXTENT_ITEM_KEY;
				key.offset = num_bytes;
				btrfs_release_path(path);
				ret = btrfs_search_slot(trans, extent_root,
							&key, path, -1, 1);
			पूर्ण

			अगर (ret) अणु
				btrfs_err(info,
					  "umm, got %d back from search, was looking for %llu",
					  ret, bytenr);
				अगर (ret > 0)
					btrfs_prपूर्णांक_leaf(path->nodes[0]);
			पूर्ण
			अगर (ret < 0) अणु
				btrfs_पात_transaction(trans, ret);
				जाओ out;
			पूर्ण
			extent_slot = path->slots[0];
		पूर्ण
	पूर्ण अन्यथा अगर (WARN_ON(ret == -ENOENT)) अणु
		btrfs_prपूर्णांक_leaf(path->nodes[0]);
		btrfs_err(info,
			"unable to find ref byte nr %llu parent %llu root %llu  owner %llu offset %llu",
			bytenr, parent, root_objectid, owner_objectid,
			owner_offset);
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण अन्यथा अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, extent_slot);
	अगर (unlikely(item_size < माप(*ei))) अणु
		ret = -EINVAL;
		btrfs_prपूर्णांक_v0_err(info);
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण
	ei = btrfs_item_ptr(leaf, extent_slot,
			    काष्ठा btrfs_extent_item);
	अगर (owner_objectid < BTRFS_FIRST_FREE_OBJECTID &&
	    key.type == BTRFS_EXTENT_ITEM_KEY) अणु
		काष्ठा btrfs_tree_block_info *bi;
		अगर (item_size < माप(*ei) + माप(*bi)) अणु
			btrfs_crit(info,
"invalid extent item size for key (%llu, %u, %llu) owner %llu, has %u expect >= %zu",
				   key.objectid, key.type, key.offset,
				   owner_objectid, item_size,
				   माप(*ei) + माप(*bi));
			btrfs_पात_transaction(trans, -EUCLEAN);
			जाओ err_dump;
		पूर्ण
		bi = (काष्ठा btrfs_tree_block_info *)(ei + 1);
		WARN_ON(owner_objectid != btrfs_tree_block_level(leaf, bi));
	पूर्ण

	refs = btrfs_extent_refs(leaf, ei);
	अगर (refs < refs_to_drop) अणु
		btrfs_crit(info,
		"trying to drop %d refs but we only have %llu for bytenr %llu",
			  refs_to_drop, refs, bytenr);
		btrfs_पात_transaction(trans, -EUCLEAN);
		जाओ err_dump;
	पूर्ण
	refs -= refs_to_drop;

	अगर (refs > 0) अणु
		अगर (extent_op)
			__run_delayed_extent_op(extent_op, leaf, ei);
		/*
		 * In the हाल of अंतरभूत back ref, reference count will
		 * be updated by हटाओ_extent_backref
		 */
		अगर (iref) अणु
			अगर (!found_extent) अणु
				btrfs_crit(info,
"invalid iref, got inlined extent ref but no EXTENT/METADATA_ITEM found");
				btrfs_पात_transaction(trans, -EUCLEAN);
				जाओ err_dump;
			पूर्ण
		पूर्ण अन्यथा अणु
			btrfs_set_extent_refs(leaf, ei, refs);
			btrfs_mark_buffer_dirty(leaf);
		पूर्ण
		अगर (found_extent) अणु
			ret = हटाओ_extent_backref(trans, path, iref,
						    refs_to_drop, is_data,
						    &last_ref);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* In this branch refs == 1 */
		अगर (found_extent) अणु
			अगर (is_data && refs_to_drop !=
			    extent_data_ref_count(path, iref)) अणु
				btrfs_crit(info,
		"invalid refs_to_drop, current refs %u refs_to_drop %u",
					   extent_data_ref_count(path, iref),
					   refs_to_drop);
				btrfs_पात_transaction(trans, -EUCLEAN);
				जाओ err_dump;
			पूर्ण
			अगर (iref) अणु
				अगर (path->slots[0] != extent_slot) अणु
					btrfs_crit(info,
"invalid iref, extent item key (%llu %u %llu) doesn't have wanted iref",
						   key.objectid, key.type,
						   key.offset);
					btrfs_पात_transaction(trans, -EUCLEAN);
					जाओ err_dump;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * No अंतरभूत ref, we must be at SHARED_* item,
				 * And it's single ref, it must be:
				 * |	extent_slot	  ||extent_slot + 1|
				 * [ EXTENT/METADATA_ITEM ][ SHARED_* ITEM ]
				 */
				अगर (path->slots[0] != extent_slot + 1) अणु
					btrfs_crit(info,
	"invalid SHARED_* item, previous item is not EXTENT/METADATA_ITEM");
					btrfs_पात_transaction(trans, -EUCLEAN);
					जाओ err_dump;
				पूर्ण
				path->slots[0] = extent_slot;
				num_to_del = 2;
			पूर्ण
		पूर्ण

		last_ref = 1;
		ret = btrfs_del_items(trans, extent_root, path, path->slots[0],
				      num_to_del);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
		btrfs_release_path(path);

		अगर (is_data) अणु
			ret = btrfs_del_csums(trans, info->csum_root, bytenr,
					      num_bytes);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				जाओ out;
			पूर्ण
		पूर्ण

		ret = add_to_मुक्त_space_tree(trans, bytenr, num_bytes);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण

		ret = btrfs_update_block_group(trans, bytenr, num_bytes, 0);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
	पूर्ण
	btrfs_release_path(path);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
err_dump:
	/*
	 * Leaf dump can take up a lot of log buffer, so we only करो full leaf
	 * dump क्रम debug build.
	 */
	अगर (IS_ENABLED(CONFIG_BTRFS_DEBUG)) अणु
		btrfs_crit(info, "path->slots[0]=%d extent_slot=%d",
			   path->slots[0], extent_slot);
		btrfs_prपूर्णांक_leaf(path->nodes[0]);
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस -EUCLEAN;
पूर्ण

/*
 * when we मुक्त an block, it is possible (and likely) that we मुक्त the last
 * delayed ref क्रम that extent as well.  This searches the delayed ref tree क्रम
 * a given extent, and अगर there are no other delayed refs to be processed, it
 * हटाओs it from the tree.
 */
अटल noअंतरभूत पूर्णांक check_ref_cleanup(काष्ठा btrfs_trans_handle *trans,
				      u64 bytenr)
अणु
	काष्ठा btrfs_delayed_ref_head *head;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	पूर्णांक ret = 0;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);
	head = btrfs_find_delayed_ref_head(delayed_refs, bytenr);
	अगर (!head)
		जाओ out_delayed_unlock;

	spin_lock(&head->lock);
	अगर (!RB_EMPTY_ROOT(&head->ref_tree.rb_root))
		जाओ out;

	अगर (cleanup_extent_op(head) != शून्य)
		जाओ out;

	/*
	 * रुकोing क्रम the lock here would deadlock.  If someone अन्यथा has it
	 * locked they are alपढ़ोy in the process of dropping it anyway
	 */
	अगर (!mutex_trylock(&head->mutex))
		जाओ out;

	btrfs_delete_ref_head(delayed_refs, head);
	head->processing = 0;

	spin_unlock(&head->lock);
	spin_unlock(&delayed_refs->lock);

	BUG_ON(head->extent_op);
	अगर (head->must_insert_reserved)
		ret = 1;

	btrfs_cleanup_ref_head_accounting(trans->fs_info, delayed_refs, head);
	mutex_unlock(&head->mutex);
	btrfs_put_delayed_ref_head(head);
	वापस ret;
out:
	spin_unlock(&head->lock);

out_delayed_unlock:
	spin_unlock(&delayed_refs->lock);
	वापस 0;
पूर्ण

व्योम btrfs_मुक्त_tree_block(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_root *root,
			   काष्ठा extent_buffer *buf,
			   u64 parent, पूर्णांक last_ref)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_ref generic_ref = अणु 0 पूर्ण;
	पूर्णांक ret;

	btrfs_init_generic_ref(&generic_ref, BTRFS_DROP_DELAYED_REF,
			       buf->start, buf->len, parent);
	btrfs_init_tree_ref(&generic_ref, btrfs_header_level(buf),
			    root->root_key.objectid);

	अगर (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID) अणु
		btrfs_ref_tree_mod(fs_info, &generic_ref);
		ret = btrfs_add_delayed_tree_ref(trans, &generic_ref, शून्य);
		BUG_ON(ret); /* -ENOMEM */
	पूर्ण

	अगर (last_ref && btrfs_header_generation(buf) == trans->transid) अणु
		काष्ठा btrfs_block_group *cache;
		bool must_pin = false;

		अगर (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID) अणु
			ret = check_ref_cleanup(trans, buf->start);
			अगर (!ret) अणु
				btrfs_redirty_list_add(trans->transaction, buf);
				जाओ out;
			पूर्ण
		पूर्ण

		cache = btrfs_lookup_block_group(fs_info, buf->start);

		अगर (btrfs_header_flag(buf, BTRFS_HEADER_FLAG_WRITTEN)) अणु
			pin_करोwn_extent(trans, cache, buf->start, buf->len, 1);
			btrfs_put_block_group(cache);
			जाओ out;
		पूर्ण

		/*
		 * If this is a leaf and there are tree mod log users, we may
		 * have recorded mod log operations that poपूर्णांक to this leaf.
		 * So we must make sure no one reuses this leaf's extent beक्रमe
		 * mod log operations are applied to a node, otherwise after
		 * शुरुआतing a node using the mod log operations we get an
		 * inconsistent btree, as the leaf's extent may now be used as
		 * a node or leaf क्रम another dअगरferent btree.
		 * We are safe from races here because at this poपूर्णांक no other
		 * node or root poपूर्णांकs to this extent buffer, so अगर after this
		 * check a new tree mod log user joins, it will not be able to
		 * find a node poपूर्णांकing to this leaf and record operations that
		 * poपूर्णांक to this leaf.
		 */
		अगर (btrfs_header_level(buf) == 0 &&
		    test_bit(BTRFS_FS_TREE_MOD_LOG_USERS, &fs_info->flags))
			must_pin = true;

		अगर (must_pin || btrfs_is_zoned(fs_info)) अणु
			btrfs_redirty_list_add(trans->transaction, buf);
			pin_करोwn_extent(trans, cache, buf->start, buf->len, 1);
			btrfs_put_block_group(cache);
			जाओ out;
		पूर्ण

		WARN_ON(test_bit(EXTENT_BUFFER_सूचीTY, &buf->bflags));

		btrfs_add_मुक्त_space(cache, buf->start, buf->len);
		btrfs_मुक्त_reserved_bytes(cache, buf->len, 0);
		btrfs_put_block_group(cache);
		trace_btrfs_reserved_extent_मुक्त(fs_info, buf->start, buf->len);
	पूर्ण
out:
	अगर (last_ref) अणु
		/*
		 * Deleting the buffer, clear the corrupt flag since it करोesn't
		 * matter anymore.
		 */
		clear_bit(EXTENT_BUFFER_CORRUPT, &buf->bflags);
	पूर्ण
पूर्ण

/* Can वापस -ENOMEM */
पूर्णांक btrfs_मुक्त_extent(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_ref *ref)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret;

	अगर (btrfs_is_testing(fs_info))
		वापस 0;

	/*
	 * tree log blocks never actually go पूर्णांकo the extent allocation
	 * tree, just update pinning info and निकास early.
	 */
	अगर ((ref->type == BTRFS_REF_METADATA &&
	     ref->tree_ref.root == BTRFS_TREE_LOG_OBJECTID) ||
	    (ref->type == BTRFS_REF_DATA &&
	     ref->data_ref.ref_root == BTRFS_TREE_LOG_OBJECTID)) अणु
		/* unlocks the pinned mutex */
		btrfs_pin_extent(trans, ref->bytenr, ref->len, 1);
		ret = 0;
	पूर्ण अन्यथा अगर (ref->type == BTRFS_REF_METADATA) अणु
		ret = btrfs_add_delayed_tree_ref(trans, ref, शून्य);
	पूर्ण अन्यथा अणु
		ret = btrfs_add_delayed_data_ref(trans, ref, 0);
	पूर्ण

	अगर (!((ref->type == BTRFS_REF_METADATA &&
	       ref->tree_ref.root == BTRFS_TREE_LOG_OBJECTID) ||
	      (ref->type == BTRFS_REF_DATA &&
	       ref->data_ref.ref_root == BTRFS_TREE_LOG_OBJECTID)))
		btrfs_ref_tree_mod(fs_info, ref);

	वापस ret;
पूर्ण

क्रमागत btrfs_loop_type अणु
	LOOP_CACHING_NOWAIT,
	LOOP_CACHING_WAIT,
	LOOP_ALLOC_CHUNK,
	LOOP_NO_EMPTY_SIZE,
पूर्ण;

अटल अंतरभूत व्योम
btrfs_lock_block_group(काष्ठा btrfs_block_group *cache,
		       पूर्णांक delalloc)
अणु
	अगर (delalloc)
		करोwn_पढ़ो(&cache->data_rwsem);
पूर्ण

अटल अंतरभूत व्योम btrfs_grab_block_group(काष्ठा btrfs_block_group *cache,
		       पूर्णांक delalloc)
अणु
	btrfs_get_block_group(cache);
	अगर (delalloc)
		करोwn_पढ़ो(&cache->data_rwsem);
पूर्ण

अटल काष्ठा btrfs_block_group *btrfs_lock_cluster(
		   काष्ठा btrfs_block_group *block_group,
		   काष्ठा btrfs_मुक्त_cluster *cluster,
		   पूर्णांक delalloc)
	__acquires(&cluster->refill_lock)
अणु
	काष्ठा btrfs_block_group *used_bg = शून्य;

	spin_lock(&cluster->refill_lock);
	जबतक (1) अणु
		used_bg = cluster->block_group;
		अगर (!used_bg)
			वापस शून्य;

		अगर (used_bg == block_group)
			वापस used_bg;

		btrfs_get_block_group(used_bg);

		अगर (!delalloc)
			वापस used_bg;

		अगर (करोwn_पढ़ो_trylock(&used_bg->data_rwsem))
			वापस used_bg;

		spin_unlock(&cluster->refill_lock);

		/* We should only have one-level nested. */
		करोwn_पढ़ो_nested(&used_bg->data_rwsem, SINGLE_DEPTH_NESTING);

		spin_lock(&cluster->refill_lock);
		अगर (used_bg == cluster->block_group)
			वापस used_bg;

		up_पढ़ो(&used_bg->data_rwsem);
		btrfs_put_block_group(used_bg);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
btrfs_release_block_group(काष्ठा btrfs_block_group *cache,
			 पूर्णांक delalloc)
अणु
	अगर (delalloc)
		up_पढ़ो(&cache->data_rwsem);
	btrfs_put_block_group(cache);
पूर्ण

क्रमागत btrfs_extent_allocation_policy अणु
	BTRFS_EXTENT_ALLOC_CLUSTERED,
	BTRFS_EXTENT_ALLOC_ZONED,
पूर्ण;

/*
 * Structure used पूर्णांकernally क्रम find_मुक्त_extent() function.  Wraps needed
 * parameters.
 */
काष्ठा find_मुक्त_extent_ctl अणु
	/* Basic allocation info */
	u64 num_bytes;
	u64 empty_size;
	u64 flags;
	पूर्णांक delalloc;

	/* Where to start the search inside the bg */
	u64 search_start;

	/* For clustered allocation */
	u64 empty_cluster;
	काष्ठा btrfs_मुक्त_cluster *last_ptr;
	bool use_cluster;

	bool have_caching_bg;
	bool orig_have_caching_bg;

	/* Allocation is called क्रम tree-log */
	bool क्रम_treelog;

	/* RAID index, converted from flags */
	पूर्णांक index;

	/*
	 * Current loop number, check find_मुक्त_extent_update_loop() क्रम details
	 */
	पूर्णांक loop;

	/*
	 * Whether we're refilling a cluster, अगर true we need to re-search
	 * current block group but करोn't try to refill the cluster again.
	 */
	bool retry_clustered;

	/*
	 * Whether we're updating मुक्त space cache, अगर true we need to re-search
	 * current block group but करोn't try updating मुक्त space cache again.
	 */
	bool retry_unclustered;

	/* If current block group is cached */
	पूर्णांक cached;

	/* Max contiguous hole found */
	u64 max_extent_size;

	/* Total मुक्त space from मुक्त space cache, not always contiguous */
	u64 total_मुक्त_space;

	/* Found result */
	u64 found_offset;

	/* Hपूर्णांक where to start looking क्रम an empty space */
	u64 hपूर्णांक_byte;

	/* Allocation policy */
	क्रमागत btrfs_extent_allocation_policy policy;
पूर्ण;


/*
 * Helper function क्रम find_मुक्त_extent().
 *
 * Return -ENOENT to inक्रमm caller that we need fallback to unclustered mode.
 * Return -EAGAIN to inक्रमm caller that we need to re-search this block group
 * Return >0 to inक्रमm caller that we find nothing
 * Return 0 means we have found a location and set ffe_ctl->found_offset.
 */
अटल पूर्णांक find_मुक्त_extent_clustered(काष्ठा btrfs_block_group *bg,
				      काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
				      काष्ठा btrfs_block_group **cluster_bg_ret)
अणु
	काष्ठा btrfs_block_group *cluster_bg;
	काष्ठा btrfs_मुक्त_cluster *last_ptr = ffe_ctl->last_ptr;
	u64 aligned_cluster;
	u64 offset;
	पूर्णांक ret;

	cluster_bg = btrfs_lock_cluster(bg, last_ptr, ffe_ctl->delalloc);
	अगर (!cluster_bg)
		जाओ refill_cluster;
	अगर (cluster_bg != bg && (cluster_bg->ro ||
	    !block_group_bits(cluster_bg, ffe_ctl->flags)))
		जाओ release_cluster;

	offset = btrfs_alloc_from_cluster(cluster_bg, last_ptr,
			ffe_ctl->num_bytes, cluster_bg->start,
			&ffe_ctl->max_extent_size);
	अगर (offset) अणु
		/* We have a block, we're करोne */
		spin_unlock(&last_ptr->refill_lock);
		trace_btrfs_reserve_extent_cluster(cluster_bg,
				ffe_ctl->search_start, ffe_ctl->num_bytes);
		*cluster_bg_ret = cluster_bg;
		ffe_ctl->found_offset = offset;
		वापस 0;
	पूर्ण
	WARN_ON(last_ptr->block_group != cluster_bg);

release_cluster:
	/*
	 * If we are on LOOP_NO_EMPTY_SIZE, we can't set up a new clusters, so
	 * lets just skip it and let the allocator find whatever block it can
	 * find. If we reach this poपूर्णांक, we will have tried the cluster
	 * allocator plenty of बार and not have found anything, so we are
	 * likely way too fragmented क्रम the clustering stuff to find anything.
	 *
	 * However, अगर the cluster is taken from the current block group,
	 * release the cluster first, so that we stand a better chance of
	 * succeeding in the unclustered allocation.
	 */
	अगर (ffe_ctl->loop >= LOOP_NO_EMPTY_SIZE && cluster_bg != bg) अणु
		spin_unlock(&last_ptr->refill_lock);
		btrfs_release_block_group(cluster_bg, ffe_ctl->delalloc);
		वापस -ENOENT;
	पूर्ण

	/* This cluster didn't work out, मुक्त it and start over */
	btrfs_वापस_cluster_to_मुक्त_space(शून्य, last_ptr);

	अगर (cluster_bg != bg)
		btrfs_release_block_group(cluster_bg, ffe_ctl->delalloc);

refill_cluster:
	अगर (ffe_ctl->loop >= LOOP_NO_EMPTY_SIZE) अणु
		spin_unlock(&last_ptr->refill_lock);
		वापस -ENOENT;
	पूर्ण

	aligned_cluster = max_t(u64,
			ffe_ctl->empty_cluster + ffe_ctl->empty_size,
			bg->full_stripe_len);
	ret = btrfs_find_space_cluster(bg, last_ptr, ffe_ctl->search_start,
			ffe_ctl->num_bytes, aligned_cluster);
	अगर (ret == 0) अणु
		/* Now pull our allocation out of this cluster */
		offset = btrfs_alloc_from_cluster(bg, last_ptr,
				ffe_ctl->num_bytes, ffe_ctl->search_start,
				&ffe_ctl->max_extent_size);
		अगर (offset) अणु
			/* We found one, proceed */
			spin_unlock(&last_ptr->refill_lock);
			trace_btrfs_reserve_extent_cluster(bg,
					ffe_ctl->search_start,
					ffe_ctl->num_bytes);
			ffe_ctl->found_offset = offset;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!ffe_ctl->cached && ffe_ctl->loop > LOOP_CACHING_NOWAIT &&
		   !ffe_ctl->retry_clustered) अणु
		spin_unlock(&last_ptr->refill_lock);

		ffe_ctl->retry_clustered = true;
		btrfs_रुको_block_group_cache_progress(bg, ffe_ctl->num_bytes +
				ffe_ctl->empty_cluster + ffe_ctl->empty_size);
		वापस -EAGAIN;
	पूर्ण
	/*
	 * At this poपूर्णांक we either didn't find a cluster or we weren't able to
	 * allocate a block from our cluster.  Free the cluster we've been
	 * trying to use, and go to the next block group.
	 */
	btrfs_वापस_cluster_to_मुक्त_space(शून्य, last_ptr);
	spin_unlock(&last_ptr->refill_lock);
	वापस 1;
पूर्ण

/*
 * Return >0 to inक्रमm caller that we find nothing
 * Return 0 when we found an मुक्त extent and set ffe_ctrl->found_offset
 * Return -EAGAIN to inक्रमm caller that we need to re-search this block group
 */
अटल पूर्णांक find_मुक्त_extent_unclustered(काष्ठा btrfs_block_group *bg,
					काष्ठा find_मुक्त_extent_ctl *ffe_ctl)
अणु
	काष्ठा btrfs_मुक्त_cluster *last_ptr = ffe_ctl->last_ptr;
	u64 offset;

	/*
	 * We are करोing an unclustered allocation, set the fragmented flag so
	 * we करोn't bother trying to setup a cluster again until we get more
	 * space.
	 */
	अगर (unlikely(last_ptr)) अणु
		spin_lock(&last_ptr->lock);
		last_ptr->fragmented = 1;
		spin_unlock(&last_ptr->lock);
	पूर्ण
	अगर (ffe_ctl->cached) अणु
		काष्ठा btrfs_मुक्त_space_ctl *मुक्त_space_ctl;

		मुक्त_space_ctl = bg->मुक्त_space_ctl;
		spin_lock(&मुक्त_space_ctl->tree_lock);
		अगर (मुक्त_space_ctl->मुक्त_space <
		    ffe_ctl->num_bytes + ffe_ctl->empty_cluster +
		    ffe_ctl->empty_size) अणु
			ffe_ctl->total_मुक्त_space = max_t(u64,
					ffe_ctl->total_मुक्त_space,
					मुक्त_space_ctl->मुक्त_space);
			spin_unlock(&मुक्त_space_ctl->tree_lock);
			वापस 1;
		पूर्ण
		spin_unlock(&मुक्त_space_ctl->tree_lock);
	पूर्ण

	offset = btrfs_find_space_क्रम_alloc(bg, ffe_ctl->search_start,
			ffe_ctl->num_bytes, ffe_ctl->empty_size,
			&ffe_ctl->max_extent_size);

	/*
	 * If we didn't find a chunk, and we haven't failed on this block group
	 * beक्रमe, and this block group is in the middle of caching and we are
	 * ok with रुकोing, then go ahead and रुको क्रम progress to be made, and
	 * set @retry_unclustered to true.
	 *
	 * If @retry_unclustered is true then we've alपढ़ोy रुकोed on this
	 * block group once and should move on to the next block group.
	 */
	अगर (!offset && !ffe_ctl->retry_unclustered && !ffe_ctl->cached &&
	    ffe_ctl->loop > LOOP_CACHING_NOWAIT) अणु
		btrfs_रुको_block_group_cache_progress(bg, ffe_ctl->num_bytes +
						      ffe_ctl->empty_size);
		ffe_ctl->retry_unclustered = true;
		वापस -EAGAIN;
	पूर्ण अन्यथा अगर (!offset) अणु
		वापस 1;
	पूर्ण
	ffe_ctl->found_offset = offset;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_allocation_clustered(काष्ठा btrfs_block_group *block_group,
				   काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
				   काष्ठा btrfs_block_group **bg_ret)
अणु
	पूर्णांक ret;

	/* We want to try and use the cluster allocator, so lets look there */
	अगर (ffe_ctl->last_ptr && ffe_ctl->use_cluster) अणु
		ret = find_मुक्त_extent_clustered(block_group, ffe_ctl, bg_ret);
		अगर (ret >= 0 || ret == -EAGAIN)
			वापस ret;
		/* ret == -ENOENT हाल falls through */
	पूर्ण

	वापस find_मुक्त_extent_unclustered(block_group, ffe_ctl);
पूर्ण

/*
 * Tree-log block group locking
 * ============================
 *
 * fs_info::treelog_bg_lock protects the fs_info::treelog_bg which
 * indicates the starting address of a block group, which is reserved only
 * क्रम tree-log metadata.
 *
 * Lock nesting
 * ============
 *
 * space_info::lock
 *   block_group::lock
 *     fs_info::treelog_bg_lock
 */

/*
 * Simple allocator क्रम sequential-only block group. It only allows sequential
 * allocation. No need to play with trees. This function also reserves the
 * bytes as in btrfs_add_reserved_bytes.
 */
अटल पूर्णांक करो_allocation_zoned(काष्ठा btrfs_block_group *block_group,
			       काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
			       काष्ठा btrfs_block_group **bg_ret)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_space_info *space_info = block_group->space_info;
	काष्ठा btrfs_मुक्त_space_ctl *ctl = block_group->मुक्त_space_ctl;
	u64 start = block_group->start;
	u64 num_bytes = ffe_ctl->num_bytes;
	u64 avail;
	u64 bytenr = block_group->start;
	u64 log_bytenr;
	पूर्णांक ret = 0;
	bool skip;

	ASSERT(btrfs_is_zoned(block_group->fs_info));

	/*
	 * Do not allow non-tree-log blocks in the dedicated tree-log block
	 * group, and vice versa.
	 */
	spin_lock(&fs_info->treelog_bg_lock);
	log_bytenr = fs_info->treelog_bg;
	skip = log_bytenr && ((ffe_ctl->क्रम_treelog && bytenr != log_bytenr) ||
			      (!ffe_ctl->क्रम_treelog && bytenr == log_bytenr));
	spin_unlock(&fs_info->treelog_bg_lock);
	अगर (skip)
		वापस 1;

	spin_lock(&space_info->lock);
	spin_lock(&block_group->lock);
	spin_lock(&fs_info->treelog_bg_lock);

	ASSERT(!ffe_ctl->क्रम_treelog ||
	       block_group->start == fs_info->treelog_bg ||
	       fs_info->treelog_bg == 0);

	अगर (block_group->ro) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	/*
	 * Do not allow currently using block group to be tree-log dedicated
	 * block group.
	 */
	अगर (ffe_ctl->क्रम_treelog && !fs_info->treelog_bg &&
	    (block_group->used || block_group->reserved)) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	avail = block_group->length - block_group->alloc_offset;
	अगर (avail < num_bytes) अणु
		अगर (ffe_ctl->max_extent_size < avail) अणु
			/*
			 * With sequential allocator, मुक्त space is always
			 * contiguous
			 */
			ffe_ctl->max_extent_size = avail;
			ffe_ctl->total_मुक्त_space = avail;
		पूर्ण
		ret = 1;
		जाओ out;
	पूर्ण

	अगर (ffe_ctl->क्रम_treelog && !fs_info->treelog_bg)
		fs_info->treelog_bg = block_group->start;

	ffe_ctl->found_offset = start + block_group->alloc_offset;
	block_group->alloc_offset += num_bytes;
	spin_lock(&ctl->tree_lock);
	ctl->मुक्त_space -= num_bytes;
	spin_unlock(&ctl->tree_lock);

	/*
	 * We करो not check अगर found_offset is aligned to stripesize. The
	 * address is anyway rewritten when using zone append writing.
	 */

	ffe_ctl->search_start = ffe_ctl->found_offset;

out:
	अगर (ret && ffe_ctl->क्रम_treelog)
		fs_info->treelog_bg = 0;
	spin_unlock(&fs_info->treelog_bg_lock);
	spin_unlock(&block_group->lock);
	spin_unlock(&space_info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_allocation(काष्ठा btrfs_block_group *block_group,
			 काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
			 काष्ठा btrfs_block_group **bg_ret)
अणु
	चयन (ffe_ctl->policy) अणु
	हाल BTRFS_EXTENT_ALLOC_CLUSTERED:
		वापस करो_allocation_clustered(block_group, ffe_ctl, bg_ret);
	हाल BTRFS_EXTENT_ALLOC_ZONED:
		वापस करो_allocation_zoned(block_group, ffe_ctl, bg_ret);
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम release_block_group(काष्ठा btrfs_block_group *block_group,
				काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
				पूर्णांक delalloc)
अणु
	चयन (ffe_ctl->policy) अणु
	हाल BTRFS_EXTENT_ALLOC_CLUSTERED:
		ffe_ctl->retry_clustered = false;
		ffe_ctl->retry_unclustered = false;
		अवरोध;
	हाल BTRFS_EXTENT_ALLOC_ZONED:
		/* Nothing to करो */
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	BUG_ON(btrfs_bg_flags_to_raid_index(block_group->flags) !=
	       ffe_ctl->index);
	btrfs_release_block_group(block_group, delalloc);
पूर्ण

अटल व्योम found_extent_clustered(काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
				   काष्ठा btrfs_key *ins)
अणु
	काष्ठा btrfs_मुक्त_cluster *last_ptr = ffe_ctl->last_ptr;

	अगर (!ffe_ctl->use_cluster && last_ptr) अणु
		spin_lock(&last_ptr->lock);
		last_ptr->winकरोw_start = ins->objectid;
		spin_unlock(&last_ptr->lock);
	पूर्ण
पूर्ण

अटल व्योम found_extent(काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
			 काष्ठा btrfs_key *ins)
अणु
	चयन (ffe_ctl->policy) अणु
	हाल BTRFS_EXTENT_ALLOC_CLUSTERED:
		found_extent_clustered(ffe_ctl, ins);
		अवरोध;
	हाल BTRFS_EXTENT_ALLOC_ZONED:
		/* Nothing to करो */
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक chunk_allocation_failed(काष्ठा find_मुक्त_extent_ctl *ffe_ctl)
अणु
	चयन (ffe_ctl->policy) अणु
	हाल BTRFS_EXTENT_ALLOC_CLUSTERED:
		/*
		 * If we can't allocate a new chunk we've alपढ़ोy looped through
		 * at least once, move on to the NO_EMPTY_SIZE हाल.
		 */
		ffe_ctl->loop = LOOP_NO_EMPTY_SIZE;
		वापस 0;
	हाल BTRFS_EXTENT_ALLOC_ZONED:
		/* Give up here */
		वापस -ENOSPC;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Return >0 means caller needs to re-search क्रम मुक्त extent
 * Return 0 means we have the needed मुक्त extent.
 * Return <0 means we failed to locate any मुक्त extent.
 */
अटल पूर्णांक find_मुक्त_extent_update_loop(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा btrfs_key *ins,
					काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
					bool full_search)
अणु
	काष्ठा btrfs_root *root = fs_info->extent_root;
	पूर्णांक ret;

	अगर ((ffe_ctl->loop == LOOP_CACHING_NOWAIT) &&
	    ffe_ctl->have_caching_bg && !ffe_ctl->orig_have_caching_bg)
		ffe_ctl->orig_have_caching_bg = true;

	अगर (!ins->objectid && ffe_ctl->loop >= LOOP_CACHING_WAIT &&
	    ffe_ctl->have_caching_bg)
		वापस 1;

	अगर (!ins->objectid && ++(ffe_ctl->index) < BTRFS_NR_RAID_TYPES)
		वापस 1;

	अगर (ins->objectid) अणु
		found_extent(ffe_ctl, ins);
		वापस 0;
	पूर्ण

	/*
	 * LOOP_CACHING_NOWAIT, search partially cached block groups, kicking
	 *			caching kthपढ़ोs as we move aदीर्घ
	 * LOOP_CACHING_WAIT, search everything, and रुको अगर our bg is caching
	 * LOOP_ALLOC_CHUNK, क्रमce a chunk allocation and try again
	 * LOOP_NO_EMPTY_SIZE, set empty_size and empty_cluster to 0 and try
	 *		       again
	 */
	अगर (ffe_ctl->loop < LOOP_NO_EMPTY_SIZE) अणु
		ffe_ctl->index = 0;
		अगर (ffe_ctl->loop == LOOP_CACHING_NOWAIT) अणु
			/*
			 * We want to skip the LOOP_CACHING_WAIT step अगर we
			 * करोn't have any uncached bgs and we've alपढ़ोy करोne a
			 * full search through.
			 */
			अगर (ffe_ctl->orig_have_caching_bg || !full_search)
				ffe_ctl->loop = LOOP_CACHING_WAIT;
			अन्यथा
				ffe_ctl->loop = LOOP_ALLOC_CHUNK;
		पूर्ण अन्यथा अणु
			ffe_ctl->loop++;
		पूर्ण

		अगर (ffe_ctl->loop == LOOP_ALLOC_CHUNK) अणु
			काष्ठा btrfs_trans_handle *trans;
			पूर्णांक exist = 0;

			trans = current->journal_info;
			अगर (trans)
				exist = 1;
			अन्यथा
				trans = btrfs_join_transaction(root);

			अगर (IS_ERR(trans)) अणु
				ret = PTR_ERR(trans);
				वापस ret;
			पूर्ण

			ret = btrfs_chunk_alloc(trans, ffe_ctl->flags,
						CHUNK_ALLOC_FORCE);

			/* Do not bail out on ENOSPC since we can करो more. */
			अगर (ret == -ENOSPC)
				ret = chunk_allocation_failed(ffe_ctl);
			अन्यथा अगर (ret < 0)
				btrfs_पात_transaction(trans, ret);
			अन्यथा
				ret = 0;
			अगर (!exist)
				btrfs_end_transaction(trans);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (ffe_ctl->loop == LOOP_NO_EMPTY_SIZE) अणु
			अगर (ffe_ctl->policy != BTRFS_EXTENT_ALLOC_CLUSTERED)
				वापस -ENOSPC;

			/*
			 * Don't loop again अगर we alपढ़ोy have no empty_size and
			 * no empty_cluster.
			 */
			अगर (ffe_ctl->empty_size == 0 &&
			    ffe_ctl->empty_cluster == 0)
				वापस -ENOSPC;
			ffe_ctl->empty_size = 0;
			ffe_ctl->empty_cluster = 0;
		पूर्ण
		वापस 1;
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक prepare_allocation_clustered(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
					काष्ठा btrfs_space_info *space_info,
					काष्ठा btrfs_key *ins)
अणु
	/*
	 * If our मुक्त space is heavily fragmented we may not be able to make
	 * big contiguous allocations, so instead of करोing the expensive search
	 * क्रम मुक्त space, simply वापस ENOSPC with our max_extent_size so we
	 * can go ahead and search क्रम a more manageable chunk.
	 *
	 * If our max_extent_size is large enough क्रम our allocation simply
	 * disable clustering since we will likely not be able to find enough
	 * space to create a cluster and induce latency trying.
	 */
	अगर (space_info->max_extent_size) अणु
		spin_lock(&space_info->lock);
		अगर (space_info->max_extent_size &&
		    ffe_ctl->num_bytes > space_info->max_extent_size) अणु
			ins->offset = space_info->max_extent_size;
			spin_unlock(&space_info->lock);
			वापस -ENOSPC;
		पूर्ण अन्यथा अगर (space_info->max_extent_size) अणु
			ffe_ctl->use_cluster = false;
		पूर्ण
		spin_unlock(&space_info->lock);
	पूर्ण

	ffe_ctl->last_ptr = fetch_cluster_info(fs_info, space_info,
					       &ffe_ctl->empty_cluster);
	अगर (ffe_ctl->last_ptr) अणु
		काष्ठा btrfs_मुक्त_cluster *last_ptr = ffe_ctl->last_ptr;

		spin_lock(&last_ptr->lock);
		अगर (last_ptr->block_group)
			ffe_ctl->hपूर्णांक_byte = last_ptr->winकरोw_start;
		अगर (last_ptr->fragmented) अणु
			/*
			 * We still set winकरोw_start so we can keep track of the
			 * last place we found an allocation to try and save
			 * some समय.
			 */
			ffe_ctl->hपूर्णांक_byte = last_ptr->winकरोw_start;
			ffe_ctl->use_cluster = false;
		पूर्ण
		spin_unlock(&last_ptr->lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prepare_allocation(काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा find_मुक्त_extent_ctl *ffe_ctl,
			      काष्ठा btrfs_space_info *space_info,
			      काष्ठा btrfs_key *ins)
अणु
	चयन (ffe_ctl->policy) अणु
	हाल BTRFS_EXTENT_ALLOC_CLUSTERED:
		वापस prepare_allocation_clustered(fs_info, ffe_ctl,
						    space_info, ins);
	हाल BTRFS_EXTENT_ALLOC_ZONED:
		अगर (ffe_ctl->क्रम_treelog) अणु
			spin_lock(&fs_info->treelog_bg_lock);
			अगर (fs_info->treelog_bg)
				ffe_ctl->hपूर्णांक_byte = fs_info->treelog_bg;
			spin_unlock(&fs_info->treelog_bg_lock);
		पूर्ण
		वापस 0;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * walks the btree of allocated extents and find a hole of a given size.
 * The key ins is changed to record the hole:
 * ins->objectid == start position
 * ins->flags = BTRFS_EXTENT_ITEM_KEY
 * ins->offset == the size of the hole.
 * Any available blocks beक्रमe search_start are skipped.
 *
 * If there is no suitable मुक्त space, we will record the max size of
 * the मुक्त space extent currently.
 *
 * The overall logic and call chain:
 *
 * find_मुक्त_extent()
 * |- Iterate through all block groups
 * |  |- Get a valid block group
 * |  |- Try to करो clustered allocation in that block group
 * |  |- Try to करो unclustered allocation in that block group
 * |  |- Check अगर the result is valid
 * |  |  |- If valid, then निकास
 * |  |- Jump to next block group
 * |
 * |- Push harder to find मुक्त extents
 *    |- If not found, re-iterate all block groups
 */
अटल noअंतरभूत पूर्णांक find_मुक्त_extent(काष्ठा btrfs_root *root,
				u64 ram_bytes, u64 num_bytes, u64 empty_size,
				u64 hपूर्णांक_byte_orig, काष्ठा btrfs_key *ins,
				u64 flags, पूर्णांक delalloc)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret = 0;
	पूर्णांक cache_block_group_error = 0;
	काष्ठा btrfs_block_group *block_group = शून्य;
	काष्ठा find_मुक्त_extent_ctl ffe_ctl = अणु0पूर्ण;
	काष्ठा btrfs_space_info *space_info;
	bool full_search = false;
	bool क्रम_treelog = (root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID);

	WARN_ON(num_bytes < fs_info->sectorsize);

	ffe_ctl.num_bytes = num_bytes;
	ffe_ctl.empty_size = empty_size;
	ffe_ctl.flags = flags;
	ffe_ctl.search_start = 0;
	ffe_ctl.delalloc = delalloc;
	ffe_ctl.index = btrfs_bg_flags_to_raid_index(flags);
	ffe_ctl.have_caching_bg = false;
	ffe_ctl.orig_have_caching_bg = false;
	ffe_ctl.found_offset = 0;
	ffe_ctl.hपूर्णांक_byte = hपूर्णांक_byte_orig;
	ffe_ctl.क्रम_treelog = क्रम_treelog;
	ffe_ctl.policy = BTRFS_EXTENT_ALLOC_CLUSTERED;

	/* For clustered allocation */
	ffe_ctl.retry_clustered = false;
	ffe_ctl.retry_unclustered = false;
	ffe_ctl.last_ptr = शून्य;
	ffe_ctl.use_cluster = true;

	अगर (btrfs_is_zoned(fs_info))
		ffe_ctl.policy = BTRFS_EXTENT_ALLOC_ZONED;

	ins->type = BTRFS_EXTENT_ITEM_KEY;
	ins->objectid = 0;
	ins->offset = 0;

	trace_find_मुक्त_extent(root, num_bytes, empty_size, flags);

	space_info = btrfs_find_space_info(fs_info, flags);
	अगर (!space_info) अणु
		btrfs_err(fs_info, "No space info for %llu", flags);
		वापस -ENOSPC;
	पूर्ण

	ret = prepare_allocation(fs_info, &ffe_ctl, space_info, ins);
	अगर (ret < 0)
		वापस ret;

	ffe_ctl.search_start = max(ffe_ctl.search_start,
				   first_logical_byte(fs_info, 0));
	ffe_ctl.search_start = max(ffe_ctl.search_start, ffe_ctl.hपूर्णांक_byte);
	अगर (ffe_ctl.search_start == ffe_ctl.hपूर्णांक_byte) अणु
		block_group = btrfs_lookup_block_group(fs_info,
						       ffe_ctl.search_start);
		/*
		 * we करोn't want to use the block group if it doesn't match our
		 * allocation bits, or अगर its not cached.
		 *
		 * However अगर we are re-searching with an ideal block group
		 * picked out then we करोn't care that the block group is cached.
		 */
		अगर (block_group && block_group_bits(block_group, flags) &&
		    block_group->cached != BTRFS_CACHE_NO) अणु
			करोwn_पढ़ो(&space_info->groups_sem);
			अगर (list_empty(&block_group->list) ||
			    block_group->ro) अणु
				/*
				 * someone is removing this block group,
				 * we can't jump पूर्णांकo the have_block_group
				 * target because our list poपूर्णांकers are not
				 * valid
				 */
				btrfs_put_block_group(block_group);
				up_पढ़ो(&space_info->groups_sem);
			पूर्ण अन्यथा अणु
				ffe_ctl.index = btrfs_bg_flags_to_raid_index(
						block_group->flags);
				btrfs_lock_block_group(block_group, delalloc);
				जाओ have_block_group;
			पूर्ण
		पूर्ण अन्यथा अगर (block_group) अणु
			btrfs_put_block_group(block_group);
		पूर्ण
	पूर्ण
search:
	ffe_ctl.have_caching_bg = false;
	अगर (ffe_ctl.index == btrfs_bg_flags_to_raid_index(flags) ||
	    ffe_ctl.index == 0)
		full_search = true;
	करोwn_पढ़ो(&space_info->groups_sem);
	list_क्रम_each_entry(block_group,
			    &space_info->block_groups[ffe_ctl.index], list) अणु
		काष्ठा btrfs_block_group *bg_ret;

		/* If the block group is पढ़ो-only, we can skip it entirely. */
		अगर (unlikely(block_group->ro)) अणु
			अगर (क्रम_treelog)
				btrfs_clear_treelog_bg(block_group);
			जारी;
		पूर्ण

		btrfs_grab_block_group(block_group, delalloc);
		ffe_ctl.search_start = block_group->start;

		/*
		 * this can happen अगर we end up cycling through all the
		 * raid types, but we want to make sure we only allocate
		 * क्रम the proper type.
		 */
		अगर (!block_group_bits(block_group, flags)) अणु
			u64 extra = BTRFS_BLOCK_GROUP_DUP |
				BTRFS_BLOCK_GROUP_RAID1_MASK |
				BTRFS_BLOCK_GROUP_RAID56_MASK |
				BTRFS_BLOCK_GROUP_RAID10;

			/*
			 * अगर they asked क्रम extra copies and this block group
			 * करोesn't provide them, bail.  This करोes allow us to
			 * fill raid0 from raid1.
			 */
			अगर ((flags & extra) && !(block_group->flags & extra))
				जाओ loop;

			/*
			 * This block group has dअगरferent flags than we want.
			 * It's possible that we have MIXED_GROUP flag but no
			 * block group is mixed.  Just skip such block group.
			 */
			btrfs_release_block_group(block_group, delalloc);
			जारी;
		पूर्ण

have_block_group:
		ffe_ctl.cached = btrfs_block_group_करोne(block_group);
		अगर (unlikely(!ffe_ctl.cached)) अणु
			ffe_ctl.have_caching_bg = true;
			ret = btrfs_cache_block_group(block_group, 0);

			/*
			 * If we get ENOMEM here or something अन्यथा we want to
			 * try other block groups, because it may not be fatal.
			 * However अगर we can't find anything अन्यथा we need to
			 * save our वापस here so that we वापस the actual
			 * error that caused problems, not ENOSPC.
			 */
			अगर (ret < 0) अणु
				अगर (!cache_block_group_error)
					cache_block_group_error = ret;
				ret = 0;
				जाओ loop;
			पूर्ण
			ret = 0;
		पूर्ण

		अगर (unlikely(block_group->cached == BTRFS_CACHE_ERROR))
			जाओ loop;

		bg_ret = शून्य;
		ret = करो_allocation(block_group, &ffe_ctl, &bg_ret);
		अगर (ret == 0) अणु
			अगर (bg_ret && bg_ret != block_group) अणु
				btrfs_release_block_group(block_group, delalloc);
				block_group = bg_ret;
			पूर्ण
		पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
			जाओ have_block_group;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			जाओ loop;
		पूर्ण

		/* Checks */
		ffe_ctl.search_start = round_up(ffe_ctl.found_offset,
					     fs_info->stripesize);

		/* move on to the next group */
		अगर (ffe_ctl.search_start + num_bytes >
		    block_group->start + block_group->length) अणु
			btrfs_add_मुक्त_space_unused(block_group,
					    ffe_ctl.found_offset, num_bytes);
			जाओ loop;
		पूर्ण

		अगर (ffe_ctl.found_offset < ffe_ctl.search_start)
			btrfs_add_मुक्त_space_unused(block_group,
					ffe_ctl.found_offset,
					ffe_ctl.search_start - ffe_ctl.found_offset);

		ret = btrfs_add_reserved_bytes(block_group, ram_bytes,
				num_bytes, delalloc);
		अगर (ret == -EAGAIN) अणु
			btrfs_add_मुक्त_space_unused(block_group,
					ffe_ctl.found_offset, num_bytes);
			जाओ loop;
		पूर्ण
		btrfs_inc_block_group_reservations(block_group);

		/* we are all good, lets वापस */
		ins->objectid = ffe_ctl.search_start;
		ins->offset = num_bytes;

		trace_btrfs_reserve_extent(block_group, ffe_ctl.search_start,
					   num_bytes);
		btrfs_release_block_group(block_group, delalloc);
		अवरोध;
loop:
		release_block_group(block_group, &ffe_ctl, delalloc);
		cond_resched();
	पूर्ण
	up_पढ़ो(&space_info->groups_sem);

	ret = find_मुक्त_extent_update_loop(fs_info, ins, &ffe_ctl, full_search);
	अगर (ret > 0)
		जाओ search;

	अगर (ret == -ENOSPC && !cache_block_group_error) अणु
		/*
		 * Use ffe_ctl->total_मुक्त_space as fallback अगर we can't find
		 * any contiguous hole.
		 */
		अगर (!ffe_ctl.max_extent_size)
			ffe_ctl.max_extent_size = ffe_ctl.total_मुक्त_space;
		spin_lock(&space_info->lock);
		space_info->max_extent_size = ffe_ctl.max_extent_size;
		spin_unlock(&space_info->lock);
		ins->offset = ffe_ctl.max_extent_size;
	पूर्ण अन्यथा अगर (ret == -ENOSPC) अणु
		ret = cache_block_group_error;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * btrfs_reserve_extent - entry poपूर्णांक to the extent allocator. Tries to find a
 *			  hole that is at least as big as @num_bytes.
 *
 * @root           -	The root that will contain this extent
 *
 * @ram_bytes      -	The amount of space in ram that @num_bytes take. This
 *			is used क्रम accounting purposes. This value dअगरfers
 *			from @num_bytes only in the हाल of compressed extents.
 *
 * @num_bytes      -	Number of bytes to allocate on-disk.
 *
 * @min_alloc_size -	Indicates the minimum amount of space that the
 *			allocator should try to satisfy. In some हालs
 *			@num_bytes may be larger than what is required and अगर
 *			the fileप्रणाली is fragmented then allocation fails.
 *			However, the presence of @min_alloc_size gives a
 *			chance to try and satisfy the smaller allocation.
 *
 * @empty_size     -	A hपूर्णांक that you plan on करोing more COW. This is the
 *			size in bytes the allocator should try to find मुक्त
 *			next to the block it वापसs.  This is just a hपूर्णांक and
 *			may be ignored by the allocator.
 *
 * @hपूर्णांक_byte      -	Hपूर्णांक to the allocator to start searching above the byte
 *			address passed. It might be ignored.
 *
 * @ins            -	This key is modअगरied to record the found hole. It will
 *			have the following values:
 *			ins->objectid == start position
 *			ins->flags = BTRFS_EXTENT_ITEM_KEY
 *			ins->offset == the size of the hole.
 *
 * @is_data        -	Boolean flag indicating whether an extent is
 *			allocated क्रम data (true) or metadata (false)
 *
 * @delalloc       -	Boolean flag indicating whether this allocation is क्रम
 *			delalloc or not. If 'true' data_rwsem of block groups
 *			is going to be acquired.
 *
 *
 * Returns 0 when an allocation succeeded or < 0 when an error occurred. In
 * हाल -ENOSPC is वापसed then @ins->offset will contain the size of the
 * largest available hole the allocator managed to find.
 */
पूर्णांक btrfs_reserve_extent(काष्ठा btrfs_root *root, u64 ram_bytes,
			 u64 num_bytes, u64 min_alloc_size,
			 u64 empty_size, u64 hपूर्णांक_byte,
			 काष्ठा btrfs_key *ins, पूर्णांक is_data, पूर्णांक delalloc)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	bool final_tried = num_bytes == min_alloc_size;
	u64 flags;
	पूर्णांक ret;
	bool क्रम_treelog = (root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID);

	flags = get_alloc_profile_by_root(root, is_data);
again:
	WARN_ON(num_bytes < fs_info->sectorsize);
	ret = find_मुक्त_extent(root, ram_bytes, num_bytes, empty_size,
			       hपूर्णांक_byte, ins, flags, delalloc);
	अगर (!ret && !is_data) अणु
		btrfs_dec_block_group_reservations(fs_info, ins->objectid);
	पूर्ण अन्यथा अगर (ret == -ENOSPC) अणु
		अगर (!final_tried && ins->offset) अणु
			num_bytes = min(num_bytes >> 1, ins->offset);
			num_bytes = round_करोwn(num_bytes,
					       fs_info->sectorsize);
			num_bytes = max(num_bytes, min_alloc_size);
			ram_bytes = num_bytes;
			अगर (num_bytes == min_alloc_size)
				final_tried = true;
			जाओ again;
		पूर्ण अन्यथा अगर (btrfs_test_opt(fs_info, ENOSPC_DEBUG)) अणु
			काष्ठा btrfs_space_info *sinfo;

			sinfo = btrfs_find_space_info(fs_info, flags);
			btrfs_err(fs_info,
			"allocation failed flags %llu, wanted %llu tree-log %d",
				  flags, num_bytes, क्रम_treelog);
			अगर (sinfo)
				btrfs_dump_space_info(fs_info, sinfo,
						      num_bytes, 1);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक btrfs_मुक्त_reserved_extent(काष्ठा btrfs_fs_info *fs_info,
			       u64 start, u64 len, पूर्णांक delalloc)
अणु
	काष्ठा btrfs_block_group *cache;

	cache = btrfs_lookup_block_group(fs_info, start);
	अगर (!cache) अणु
		btrfs_err(fs_info, "Unable to find block group for %llu",
			  start);
		वापस -ENOSPC;
	पूर्ण

	btrfs_add_मुक्त_space(cache, start, len);
	btrfs_मुक्त_reserved_bytes(cache, len, delalloc);
	trace_btrfs_reserved_extent_मुक्त(fs_info, start, len);

	btrfs_put_block_group(cache);
	वापस 0;
पूर्ण

पूर्णांक btrfs_pin_reserved_extent(काष्ठा btrfs_trans_handle *trans, u64 start,
			      u64 len)
अणु
	काष्ठा btrfs_block_group *cache;
	पूर्णांक ret = 0;

	cache = btrfs_lookup_block_group(trans->fs_info, start);
	अगर (!cache) अणु
		btrfs_err(trans->fs_info, "unable to find block group for %llu",
			  start);
		वापस -ENOSPC;
	पूर्ण

	ret = pin_करोwn_extent(trans, cache, start, len, 1);
	btrfs_put_block_group(cache);
	वापस ret;
पूर्ण

अटल पूर्णांक alloc_reserved_file_extent(काष्ठा btrfs_trans_handle *trans,
				      u64 parent, u64 root_objectid,
				      u64 flags, u64 owner, u64 offset,
				      काष्ठा btrfs_key *ins, पूर्णांक ref_mod)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret;
	काष्ठा btrfs_extent_item *extent_item;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	पूर्णांक type;
	u32 size;

	अगर (parent > 0)
		type = BTRFS_SHARED_DATA_REF_KEY;
	अन्यथा
		type = BTRFS_EXTENT_DATA_REF_KEY;

	size = माप(*extent_item) + btrfs_extent_अंतरभूत_ref_size(type);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_insert_empty_item(trans, fs_info->extent_root, path,
				      ins, size);
	अगर (ret) अणु
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण

	leaf = path->nodes[0];
	extent_item = btrfs_item_ptr(leaf, path->slots[0],
				     काष्ठा btrfs_extent_item);
	btrfs_set_extent_refs(leaf, extent_item, ref_mod);
	btrfs_set_extent_generation(leaf, extent_item, trans->transid);
	btrfs_set_extent_flags(leaf, extent_item,
			       flags | BTRFS_EXTENT_FLAG_DATA);

	iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(extent_item + 1);
	btrfs_set_extent_अंतरभूत_ref_type(leaf, iref, type);
	अगर (parent > 0) अणु
		काष्ठा btrfs_shared_data_ref *ref;
		ref = (काष्ठा btrfs_shared_data_ref *)(iref + 1);
		btrfs_set_extent_अंतरभूत_ref_offset(leaf, iref, parent);
		btrfs_set_shared_data_ref_count(leaf, ref, ref_mod);
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_extent_data_ref *ref;
		ref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
		btrfs_set_extent_data_ref_root(leaf, ref, root_objectid);
		btrfs_set_extent_data_ref_objectid(leaf, ref, owner);
		btrfs_set_extent_data_ref_offset(leaf, ref, offset);
		btrfs_set_extent_data_ref_count(leaf, ref, ref_mod);
	पूर्ण

	btrfs_mark_buffer_dirty(path->nodes[0]);
	btrfs_मुक्त_path(path);

	ret = हटाओ_from_मुक्त_space_tree(trans, ins->objectid, ins->offset);
	अगर (ret)
		वापस ret;

	ret = btrfs_update_block_group(trans, ins->objectid, ins->offset, 1);
	अगर (ret) अणु /* -ENOENT, logic error */
		btrfs_err(fs_info, "update block group failed for %llu %llu",
			ins->objectid, ins->offset);
		BUG();
	पूर्ण
	trace_btrfs_reserved_extent_alloc(fs_info, ins->objectid, ins->offset);
	वापस ret;
पूर्ण

अटल पूर्णांक alloc_reserved_tree_block(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_delayed_ref_node *node,
				     काष्ठा btrfs_delayed_extent_op *extent_op)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret;
	काष्ठा btrfs_extent_item *extent_item;
	काष्ठा btrfs_key extent_key;
	काष्ठा btrfs_tree_block_info *block_info;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_delayed_tree_ref *ref;
	u32 size = माप(*extent_item) + माप(*iref);
	u64 num_bytes;
	u64 flags = extent_op->flags_to_set;
	bool skinny_metadata = btrfs_fs_incompat(fs_info, SKINNY_METADATA);

	ref = btrfs_delayed_node_to_tree_ref(node);

	extent_key.objectid = node->bytenr;
	अगर (skinny_metadata) अणु
		extent_key.offset = ref->level;
		extent_key.type = BTRFS_METADATA_ITEM_KEY;
		num_bytes = fs_info->nodesize;
	पूर्ण अन्यथा अणु
		extent_key.offset = node->num_bytes;
		extent_key.type = BTRFS_EXTENT_ITEM_KEY;
		size += माप(*block_info);
		num_bytes = node->num_bytes;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_insert_empty_item(trans, fs_info->extent_root, path,
				      &extent_key, size);
	अगर (ret) अणु
		btrfs_मुक्त_path(path);
		वापस ret;
	पूर्ण

	leaf = path->nodes[0];
	extent_item = btrfs_item_ptr(leaf, path->slots[0],
				     काष्ठा btrfs_extent_item);
	btrfs_set_extent_refs(leaf, extent_item, 1);
	btrfs_set_extent_generation(leaf, extent_item, trans->transid);
	btrfs_set_extent_flags(leaf, extent_item,
			       flags | BTRFS_EXTENT_FLAG_TREE_BLOCK);

	अगर (skinny_metadata) अणु
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(extent_item + 1);
	पूर्ण अन्यथा अणु
		block_info = (काष्ठा btrfs_tree_block_info *)(extent_item + 1);
		btrfs_set_tree_block_key(leaf, block_info, &extent_op->key);
		btrfs_set_tree_block_level(leaf, block_info, ref->level);
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(block_info + 1);
	पूर्ण

	अगर (node->type == BTRFS_SHARED_BLOCK_REF_KEY) अणु
		btrfs_set_extent_अंतरभूत_ref_type(leaf, iref,
						 BTRFS_SHARED_BLOCK_REF_KEY);
		btrfs_set_extent_अंतरभूत_ref_offset(leaf, iref, ref->parent);
	पूर्ण अन्यथा अणु
		btrfs_set_extent_अंतरभूत_ref_type(leaf, iref,
						 BTRFS_TREE_BLOCK_REF_KEY);
		btrfs_set_extent_अंतरभूत_ref_offset(leaf, iref, ref->root);
	पूर्ण

	btrfs_mark_buffer_dirty(leaf);
	btrfs_मुक्त_path(path);

	ret = हटाओ_from_मुक्त_space_tree(trans, extent_key.objectid,
					  num_bytes);
	अगर (ret)
		वापस ret;

	ret = btrfs_update_block_group(trans, extent_key.objectid,
				       fs_info->nodesize, 1);
	अगर (ret) अणु /* -ENOENT, logic error */
		btrfs_err(fs_info, "update block group failed for %llu %llu",
			extent_key.objectid, extent_key.offset);
		BUG();
	पूर्ण

	trace_btrfs_reserved_extent_alloc(fs_info, extent_key.objectid,
					  fs_info->nodesize);
	वापस ret;
पूर्ण

पूर्णांक btrfs_alloc_reserved_file_extent(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_root *root, u64 owner,
				     u64 offset, u64 ram_bytes,
				     काष्ठा btrfs_key *ins)
अणु
	काष्ठा btrfs_ref generic_ref = अणु 0 पूर्ण;

	BUG_ON(root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID);

	btrfs_init_generic_ref(&generic_ref, BTRFS_ADD_DELAYED_EXTENT,
			       ins->objectid, ins->offset, 0);
	btrfs_init_data_ref(&generic_ref, root->root_key.objectid, owner, offset);
	btrfs_ref_tree_mod(root->fs_info, &generic_ref);

	वापस btrfs_add_delayed_data_ref(trans, &generic_ref, ram_bytes);
पूर्ण

/*
 * this is used by the tree logging recovery code.  It records that
 * an extent has been allocated and makes sure to clear the मुक्त
 * space cache bits as well
 */
पूर्णांक btrfs_alloc_logged_file_extent(काष्ठा btrfs_trans_handle *trans,
				   u64 root_objectid, u64 owner, u64 offset,
				   काष्ठा btrfs_key *ins)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret;
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_space_info *space_info;

	/*
	 * Mixed block groups will exclude beक्रमe processing the log so we only
	 * need to करो the exclude dance अगर this fs isn't mixed.
	 */
	अगर (!btrfs_fs_incompat(fs_info, MIXED_GROUPS)) अणु
		ret = __exclude_logged_extent(fs_info, ins->objectid,
					      ins->offset);
		अगर (ret)
			वापस ret;
	पूर्ण

	block_group = btrfs_lookup_block_group(fs_info, ins->objectid);
	अगर (!block_group)
		वापस -EINVAL;

	space_info = block_group->space_info;
	spin_lock(&space_info->lock);
	spin_lock(&block_group->lock);
	space_info->bytes_reserved += ins->offset;
	block_group->reserved += ins->offset;
	spin_unlock(&block_group->lock);
	spin_unlock(&space_info->lock);

	ret = alloc_reserved_file_extent(trans, 0, root_objectid, 0, owner,
					 offset, ins, 1);
	अगर (ret)
		btrfs_pin_extent(trans, ins->objectid, ins->offset, 1);
	btrfs_put_block_group(block_group);
	वापस ret;
पूर्ण

अटल काष्ठा extent_buffer *
btrfs_init_new_buffer(काष्ठा btrfs_trans_handle *trans, काष्ठा btrfs_root *root,
		      u64 bytenr, पूर्णांक level, u64 owner,
		      क्रमागत btrfs_lock_nesting nest)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *buf;

	buf = btrfs_find_create_tree_block(fs_info, bytenr, owner, level);
	अगर (IS_ERR(buf))
		वापस buf;

	/*
	 * Extra safety check in हाल the extent tree is corrupted and extent
	 * allocator chooses to use a tree block which is alपढ़ोy used and
	 * locked.
	 */
	अगर (buf->lock_owner == current->pid) अणु
		btrfs_err_rl(fs_info,
"tree block %llu owner %llu already locked by pid=%d, extent tree corruption detected",
			buf->start, btrfs_header_owner(buf), current->pid);
		मुक्त_extent_buffer(buf);
		वापस ERR_PTR(-EUCLEAN);
	पूर्ण

	/*
	 * This needs to stay, because we could allocate a मुक्तd block from an
	 * old tree पूर्णांकo a new tree, so we need to make sure this new block is
	 * set to the appropriate level and owner.
	 */
	btrfs_set_buffer_lockdep_class(owner, buf, level);
	__btrfs_tree_lock(buf, nest);
	btrfs_clean_tree_block(buf);
	clear_bit(EXTENT_BUFFER_STALE, &buf->bflags);
	clear_bit(EXTENT_BUFFER_NO_CHECK, &buf->bflags);

	set_extent_buffer_uptodate(buf);

	memzero_extent_buffer(buf, 0, माप(काष्ठा btrfs_header));
	btrfs_set_header_level(buf, level);
	btrfs_set_header_bytenr(buf, buf->start);
	btrfs_set_header_generation(buf, trans->transid);
	btrfs_set_header_backref_rev(buf, BTRFS_MIXED_BACKREF_REV);
	btrfs_set_header_owner(buf, owner);
	ग_लिखो_extent_buffer_fsid(buf, fs_info->fs_devices->metadata_uuid);
	ग_लिखो_extent_buffer_chunk_tree_uuid(buf, fs_info->chunk_tree_uuid);
	अगर (root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID) अणु
		buf->log_index = root->log_transid % 2;
		/*
		 * we allow two log transactions at a समय, use dअगरferent
		 * EXTENT bit to dअगरferentiate dirty pages.
		 */
		अगर (buf->log_index == 0)
			set_extent_dirty(&root->dirty_log_pages, buf->start,
					buf->start + buf->len - 1, GFP_NOFS);
		अन्यथा
			set_extent_new(&root->dirty_log_pages, buf->start,
					buf->start + buf->len - 1);
	पूर्ण अन्यथा अणु
		buf->log_index = -1;
		set_extent_dirty(&trans->transaction->dirty_pages, buf->start,
			 buf->start + buf->len - 1, GFP_NOFS);
	पूर्ण
	trans->dirty = true;
	/* this वापसs a buffer locked क्रम blocking */
	वापस buf;
पूर्ण

/*
 * finds a मुक्त extent and करोes all the dirty work required क्रम allocation
 * वापसs the tree buffer or an ERR_PTR on error.
 */
काष्ठा extent_buffer *btrfs_alloc_tree_block(काष्ठा btrfs_trans_handle *trans,
					     काष्ठा btrfs_root *root,
					     u64 parent, u64 root_objectid,
					     स्थिर काष्ठा btrfs_disk_key *key,
					     पूर्णांक level, u64 hपूर्णांक,
					     u64 empty_size,
					     क्रमागत btrfs_lock_nesting nest)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_key ins;
	काष्ठा btrfs_block_rsv *block_rsv;
	काष्ठा extent_buffer *buf;
	काष्ठा btrfs_delayed_extent_op *extent_op;
	काष्ठा btrfs_ref generic_ref = अणु 0 पूर्ण;
	u64 flags = 0;
	पूर्णांक ret;
	u32 blocksize = fs_info->nodesize;
	bool skinny_metadata = btrfs_fs_incompat(fs_info, SKINNY_METADATA);

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
	अगर (btrfs_is_testing(fs_info)) अणु
		buf = btrfs_init_new_buffer(trans, root, root->alloc_bytenr,
					    level, root_objectid, nest);
		अगर (!IS_ERR(buf))
			root->alloc_bytenr += blocksize;
		वापस buf;
	पूर्ण
#पूर्ण_अगर

	block_rsv = btrfs_use_block_rsv(trans, root, blocksize);
	अगर (IS_ERR(block_rsv))
		वापस ERR_CAST(block_rsv);

	ret = btrfs_reserve_extent(root, blocksize, blocksize, blocksize,
				   empty_size, hपूर्णांक, &ins, 0, 0);
	अगर (ret)
		जाओ out_unuse;

	buf = btrfs_init_new_buffer(trans, root, ins.objectid, level,
				    root_objectid, nest);
	अगर (IS_ERR(buf)) अणु
		ret = PTR_ERR(buf);
		जाओ out_मुक्त_reserved;
	पूर्ण

	अगर (root_objectid == BTRFS_TREE_RELOC_OBJECTID) अणु
		अगर (parent == 0)
			parent = ins.objectid;
		flags |= BTRFS_BLOCK_FLAG_FULL_BACKREF;
	पूर्ण अन्यथा
		BUG_ON(parent > 0);

	अगर (root_objectid != BTRFS_TREE_LOG_OBJECTID) अणु
		extent_op = btrfs_alloc_delayed_extent_op();
		अगर (!extent_op) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_buf;
		पूर्ण
		अगर (key)
			स_नकल(&extent_op->key, key, माप(extent_op->key));
		अन्यथा
			स_रखो(&extent_op->key, 0, माप(extent_op->key));
		extent_op->flags_to_set = flags;
		extent_op->update_key = skinny_metadata ? false : true;
		extent_op->update_flags = true;
		extent_op->is_data = false;
		extent_op->level = level;

		btrfs_init_generic_ref(&generic_ref, BTRFS_ADD_DELAYED_EXTENT,
				       ins.objectid, ins.offset, parent);
		generic_ref.real_root = root->root_key.objectid;
		btrfs_init_tree_ref(&generic_ref, level, root_objectid);
		btrfs_ref_tree_mod(fs_info, &generic_ref);
		ret = btrfs_add_delayed_tree_ref(trans, &generic_ref, extent_op);
		अगर (ret)
			जाओ out_मुक्त_delayed;
	पूर्ण
	वापस buf;

out_मुक्त_delayed:
	btrfs_मुक्त_delayed_extent_op(extent_op);
out_मुक्त_buf:
	मुक्त_extent_buffer(buf);
out_मुक्त_reserved:
	btrfs_मुक्त_reserved_extent(fs_info, ins.objectid, ins.offset, 0);
out_unuse:
	btrfs_unuse_block_rsv(fs_info, block_rsv, blocksize);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा walk_control अणु
	u64 refs[BTRFS_MAX_LEVEL];
	u64 flags[BTRFS_MAX_LEVEL];
	काष्ठा btrfs_key update_progress;
	काष्ठा btrfs_key drop_progress;
	पूर्णांक drop_level;
	पूर्णांक stage;
	पूर्णांक level;
	पूर्णांक shared_level;
	पूर्णांक update_ref;
	पूर्णांक keep_locks;
	पूर्णांक पढ़ोa_slot;
	पूर्णांक पढ़ोa_count;
	पूर्णांक restarted;
पूर्ण;

#घोषणा DROP_REFERENCE	1
#घोषणा UPDATE_BACKREF	2

अटल noअंतरभूत व्योम पढ़ोa_walk_करोwn(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_root *root,
				     काष्ठा walk_control *wc,
				     काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 bytenr;
	u64 generation;
	u64 refs;
	u64 flags;
	u32 nritems;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *eb;
	पूर्णांक ret;
	पूर्णांक slot;
	पूर्णांक nपढ़ो = 0;

	अगर (path->slots[wc->level] < wc->पढ़ोa_slot) अणु
		wc->पढ़ोa_count = wc->पढ़ोa_count * 2 / 3;
		wc->पढ़ोa_count = max(wc->पढ़ोa_count, 2);
	पूर्ण अन्यथा अणु
		wc->पढ़ोa_count = wc->पढ़ोa_count * 3 / 2;
		wc->पढ़ोa_count = min_t(पूर्णांक, wc->पढ़ोa_count,
					BTRFS_NODEPTRS_PER_BLOCK(fs_info));
	पूर्ण

	eb = path->nodes[wc->level];
	nritems = btrfs_header_nritems(eb);

	क्रम (slot = path->slots[wc->level]; slot < nritems; slot++) अणु
		अगर (nपढ़ो >= wc->पढ़ोa_count)
			अवरोध;

		cond_resched();
		bytenr = btrfs_node_blockptr(eb, slot);
		generation = btrfs_node_ptr_generation(eb, slot);

		अगर (slot == path->slots[wc->level])
			जाओ पढ़ोa;

		अगर (wc->stage == UPDATE_BACKREF &&
		    generation <= root->root_key.offset)
			जारी;

		/* We करोn't lock the tree block, it's OK to be racy here */
		ret = btrfs_lookup_extent_info(trans, fs_info, bytenr,
					       wc->level - 1, 1, &refs,
					       &flags);
		/* We करोn't care about errors in पढ़ोahead. */
		अगर (ret < 0)
			जारी;
		BUG_ON(refs == 0);

		अगर (wc->stage == DROP_REFERENCE) अणु
			अगर (refs == 1)
				जाओ पढ़ोa;

			अगर (wc->level == 1 &&
			    (flags & BTRFS_BLOCK_FLAG_FULL_BACKREF))
				जारी;
			अगर (!wc->update_ref ||
			    generation <= root->root_key.offset)
				जारी;
			btrfs_node_key_to_cpu(eb, &key, slot);
			ret = btrfs_comp_cpu_keys(&key,
						  &wc->update_progress);
			अगर (ret < 0)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (wc->level == 1 &&
			    (flags & BTRFS_BLOCK_FLAG_FULL_BACKREF))
				जारी;
		पूर्ण
पढ़ोa:
		btrfs_पढ़ोahead_node_child(eb, slot);
		nपढ़ो++;
	पूर्ण
	wc->पढ़ोa_slot = slot;
पूर्ण

/*
 * helper to process tree block जबतक walking करोwn the tree.
 *
 * when wc->stage == UPDATE_BACKREF, this function updates
 * back refs क्रम poपूर्णांकers in the block.
 *
 * NOTE: वापस value 1 means we should stop walking करोwn.
 */
अटल noअंतरभूत पूर्णांक walk_करोwn_proc(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_root *root,
				   काष्ठा btrfs_path *path,
				   काष्ठा walk_control *wc, पूर्णांक lookup_info)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक level = wc->level;
	काष्ठा extent_buffer *eb = path->nodes[level];
	u64 flag = BTRFS_BLOCK_FLAG_FULL_BACKREF;
	पूर्णांक ret;

	अगर (wc->stage == UPDATE_BACKREF &&
	    btrfs_header_owner(eb) != root->root_key.objectid)
		वापस 1;

	/*
	 * when reference count of tree block is 1, it won't increase
	 * again. once full backref flag is set, we never clear it.
	 */
	अगर (lookup_info &&
	    ((wc->stage == DROP_REFERENCE && wc->refs[level] != 1) ||
	     (wc->stage == UPDATE_BACKREF && !(wc->flags[level] & flag)))) अणु
		BUG_ON(!path->locks[level]);
		ret = btrfs_lookup_extent_info(trans, fs_info,
					       eb->start, level, 1,
					       &wc->refs[level],
					       &wc->flags[level]);
		BUG_ON(ret == -ENOMEM);
		अगर (ret)
			वापस ret;
		BUG_ON(wc->refs[level] == 0);
	पूर्ण

	अगर (wc->stage == DROP_REFERENCE) अणु
		अगर (wc->refs[level] > 1)
			वापस 1;

		अगर (path->locks[level] && !wc->keep_locks) अणु
			btrfs_tree_unlock_rw(eb, path->locks[level]);
			path->locks[level] = 0;
		पूर्ण
		वापस 0;
	पूर्ण

	/* wc->stage == UPDATE_BACKREF */
	अगर (!(wc->flags[level] & flag)) अणु
		BUG_ON(!path->locks[level]);
		ret = btrfs_inc_ref(trans, root, eb, 1);
		BUG_ON(ret); /* -ENOMEM */
		ret = btrfs_dec_ref(trans, root, eb, 0);
		BUG_ON(ret); /* -ENOMEM */
		ret = btrfs_set_disk_extent_flags(trans, eb, flag,
						  btrfs_header_level(eb), 0);
		BUG_ON(ret); /* -ENOMEM */
		wc->flags[level] |= flag;
	पूर्ण

	/*
	 * the block is shared by multiple trees, so it's not good to
	 * keep the tree lock
	 */
	अगर (path->locks[level] && level > 0) अणु
		btrfs_tree_unlock_rw(eb, path->locks[level]);
		path->locks[level] = 0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This is used to verअगरy a ref exists क्रम this root to deal with a bug where we
 * would have a drop_progress key that hadn't been updated properly.
 */
अटल पूर्णांक check_ref_exists(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root, u64 bytenr, u64 parent,
			    पूर्णांक level)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = lookup_extent_backref(trans, path, &iref, bytenr,
				    root->fs_info->nodesize, parent,
				    root->root_key.objectid, level, 0);
	btrfs_मुक्त_path(path);
	अगर (ret == -ENOENT)
		वापस 0;
	अगर (ret < 0)
		वापस ret;
	वापस 1;
पूर्ण

/*
 * helper to process tree block poपूर्णांकer.
 *
 * when wc->stage == DROP_REFERENCE, this function checks
 * reference count of the block poपूर्णांकed to. अगर the block
 * is shared and we need update back refs क्रम the subtree
 * rooted at the block, this function changes wc->stage to
 * UPDATE_BACKREF. अगर the block is shared and there is no
 * need to update back, this function drops the reference
 * to the block.
 *
 * NOTE: वापस value 1 means we should stop walking करोwn.
 */
अटल noअंतरभूत पूर्णांक करो_walk_करोwn(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root,
				 काष्ठा btrfs_path *path,
				 काष्ठा walk_control *wc, पूर्णांक *lookup_info)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 bytenr;
	u64 generation;
	u64 parent;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key first_key;
	काष्ठा btrfs_ref ref = अणु 0 पूर्ण;
	काष्ठा extent_buffer *next;
	पूर्णांक level = wc->level;
	पूर्णांक पढ़ोa = 0;
	पूर्णांक ret = 0;
	bool need_account = false;

	generation = btrfs_node_ptr_generation(path->nodes[level],
					       path->slots[level]);
	/*
	 * अगर the lower level block was created beक्रमe the snapshot
	 * was created, we know there is no need to update back refs
	 * क्रम the subtree
	 */
	अगर (wc->stage == UPDATE_BACKREF &&
	    generation <= root->root_key.offset) अणु
		*lookup_info = 1;
		वापस 1;
	पूर्ण

	bytenr = btrfs_node_blockptr(path->nodes[level], path->slots[level]);
	btrfs_node_key_to_cpu(path->nodes[level], &first_key,
			      path->slots[level]);

	next = find_extent_buffer(fs_info, bytenr);
	अगर (!next) अणु
		next = btrfs_find_create_tree_block(fs_info, bytenr,
				root->root_key.objectid, level - 1);
		अगर (IS_ERR(next))
			वापस PTR_ERR(next);
		पढ़ोa = 1;
	पूर्ण
	btrfs_tree_lock(next);

	ret = btrfs_lookup_extent_info(trans, fs_info, bytenr, level - 1, 1,
				       &wc->refs[level - 1],
				       &wc->flags[level - 1]);
	अगर (ret < 0)
		जाओ out_unlock;

	अगर (unlikely(wc->refs[level - 1] == 0)) अणु
		btrfs_err(fs_info, "Missing references.");
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण
	*lookup_info = 0;

	अगर (wc->stage == DROP_REFERENCE) अणु
		अगर (wc->refs[level - 1] > 1) अणु
			need_account = true;
			अगर (level == 1 &&
			    (wc->flags[0] & BTRFS_BLOCK_FLAG_FULL_BACKREF))
				जाओ skip;

			अगर (!wc->update_ref ||
			    generation <= root->root_key.offset)
				जाओ skip;

			btrfs_node_key_to_cpu(path->nodes[level], &key,
					      path->slots[level]);
			ret = btrfs_comp_cpu_keys(&key, &wc->update_progress);
			अगर (ret < 0)
				जाओ skip;

			wc->stage = UPDATE_BACKREF;
			wc->shared_level = level - 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (level == 1 &&
		    (wc->flags[0] & BTRFS_BLOCK_FLAG_FULL_BACKREF))
			जाओ skip;
	पूर्ण

	अगर (!btrfs_buffer_uptodate(next, generation, 0)) अणु
		btrfs_tree_unlock(next);
		मुक्त_extent_buffer(next);
		next = शून्य;
		*lookup_info = 1;
	पूर्ण

	अगर (!next) अणु
		अगर (पढ़ोa && level == 1)
			पढ़ोa_walk_करोwn(trans, root, wc, path);
		next = पढ़ो_tree_block(fs_info, bytenr, root->root_key.objectid,
				       generation, level - 1, &first_key);
		अगर (IS_ERR(next)) अणु
			वापस PTR_ERR(next);
		पूर्ण अन्यथा अगर (!extent_buffer_uptodate(next)) अणु
			मुक्त_extent_buffer(next);
			वापस -EIO;
		पूर्ण
		btrfs_tree_lock(next);
	पूर्ण

	level--;
	ASSERT(level == btrfs_header_level(next));
	अगर (level != btrfs_header_level(next)) अणु
		btrfs_err(root->fs_info, "mismatched level");
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण
	path->nodes[level] = next;
	path->slots[level] = 0;
	path->locks[level] = BTRFS_WRITE_LOCK;
	wc->level = level;
	अगर (wc->level == 1)
		wc->पढ़ोa_slot = 0;
	वापस 0;
skip:
	wc->refs[level - 1] = 0;
	wc->flags[level - 1] = 0;
	अगर (wc->stage == DROP_REFERENCE) अणु
		अगर (wc->flags[level] & BTRFS_BLOCK_FLAG_FULL_BACKREF) अणु
			parent = path->nodes[level]->start;
		पूर्ण अन्यथा अणु
			ASSERT(root->root_key.objectid ==
			       btrfs_header_owner(path->nodes[level]));
			अगर (root->root_key.objectid !=
			    btrfs_header_owner(path->nodes[level])) अणु
				btrfs_err(root->fs_info,
						"mismatched block owner");
				ret = -EIO;
				जाओ out_unlock;
			पूर्ण
			parent = 0;
		पूर्ण

		/*
		 * If we had a drop_progress we need to verअगरy the refs are set
		 * as expected.  If we find our ref then we know that from here
		 * on out everything should be correct, and we can clear the
		 * ->restarted flag.
		 */
		अगर (wc->restarted) अणु
			ret = check_ref_exists(trans, root, bytenr, parent,
					       level - 1);
			अगर (ret < 0)
				जाओ out_unlock;
			अगर (ret == 0)
				जाओ no_delete;
			ret = 0;
			wc->restarted = 0;
		पूर्ण

		/*
		 * Reloc tree करोesn't contribute to qgroup numbers, and we have
		 * alपढ़ोy accounted them at merge समय (replace_path),
		 * thus we could skip expensive subtree trace here.
		 */
		अगर (root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID &&
		    need_account) अणु
			ret = btrfs_qgroup_trace_subtree(trans, next,
							 generation, level - 1);
			अगर (ret) अणु
				btrfs_err_rl(fs_info,
					     "Error %d accounting shared subtree. Quota is out of sync, rescan required.",
					     ret);
			पूर्ण
		पूर्ण

		/*
		 * We need to update the next key in our walk control so we can
		 * update the drop_progress key accordingly.  We करोn't care अगर
		 * find_next_key करोesn't find a key because that means we're at
		 * the end and are going to clean up now.
		 */
		wc->drop_level = level;
		find_next_key(path, level, &wc->drop_progress);

		btrfs_init_generic_ref(&ref, BTRFS_DROP_DELAYED_REF, bytenr,
				       fs_info->nodesize, parent);
		btrfs_init_tree_ref(&ref, level - 1, root->root_key.objectid);
		ret = btrfs_मुक्त_extent(trans, &ref);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण
no_delete:
	*lookup_info = 1;
	ret = 1;

out_unlock:
	btrfs_tree_unlock(next);
	मुक्त_extent_buffer(next);

	वापस ret;
पूर्ण

/*
 * helper to process tree block जबतक walking up the tree.
 *
 * when wc->stage == DROP_REFERENCE, this function drops
 * reference count on the block.
 *
 * when wc->stage == UPDATE_BACKREF, this function changes
 * wc->stage back to DROP_REFERENCE अगर we changed wc->stage
 * to UPDATE_BACKREF previously जबतक processing the block.
 *
 * NOTE: वापस value 1 means we should stop walking up.
 */
अटल noअंतरभूत पूर्णांक walk_up_proc(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root,
				 काष्ठा btrfs_path *path,
				 काष्ठा walk_control *wc)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	पूर्णांक ret;
	पूर्णांक level = wc->level;
	काष्ठा extent_buffer *eb = path->nodes[level];
	u64 parent = 0;

	अगर (wc->stage == UPDATE_BACKREF) अणु
		BUG_ON(wc->shared_level < level);
		अगर (level < wc->shared_level)
			जाओ out;

		ret = find_next_key(path, level + 1, &wc->update_progress);
		अगर (ret > 0)
			wc->update_ref = 0;

		wc->stage = DROP_REFERENCE;
		wc->shared_level = -1;
		path->slots[level] = 0;

		/*
		 * check reference count again अगर the block isn't locked.
		 * we should start walking करोwn the tree again अगर reference
		 * count is one.
		 */
		अगर (!path->locks[level]) अणु
			BUG_ON(level == 0);
			btrfs_tree_lock(eb);
			path->locks[level] = BTRFS_WRITE_LOCK;

			ret = btrfs_lookup_extent_info(trans, fs_info,
						       eb->start, level, 1,
						       &wc->refs[level],
						       &wc->flags[level]);
			अगर (ret < 0) अणु
				btrfs_tree_unlock_rw(eb, path->locks[level]);
				path->locks[level] = 0;
				वापस ret;
			पूर्ण
			BUG_ON(wc->refs[level] == 0);
			अगर (wc->refs[level] == 1) अणु
				btrfs_tree_unlock_rw(eb, path->locks[level]);
				path->locks[level] = 0;
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* wc->stage == DROP_REFERENCE */
	BUG_ON(wc->refs[level] > 1 && !path->locks[level]);

	अगर (wc->refs[level] == 1) अणु
		अगर (level == 0) अणु
			अगर (wc->flags[level] & BTRFS_BLOCK_FLAG_FULL_BACKREF)
				ret = btrfs_dec_ref(trans, root, eb, 1);
			अन्यथा
				ret = btrfs_dec_ref(trans, root, eb, 0);
			BUG_ON(ret); /* -ENOMEM */
			अगर (is_fstree(root->root_key.objectid)) अणु
				ret = btrfs_qgroup_trace_leaf_items(trans, eb);
				अगर (ret) अणु
					btrfs_err_rl(fs_info,
	"error %d accounting leaf items, quota is out of sync, rescan required",
					     ret);
				पूर्ण
			पूर्ण
		पूर्ण
		/* make block locked निश्चितion in btrfs_clean_tree_block happy */
		अगर (!path->locks[level] &&
		    btrfs_header_generation(eb) == trans->transid) अणु
			btrfs_tree_lock(eb);
			path->locks[level] = BTRFS_WRITE_LOCK;
		पूर्ण
		btrfs_clean_tree_block(eb);
	पूर्ण

	अगर (eb == root->node) अणु
		अगर (wc->flags[level] & BTRFS_BLOCK_FLAG_FULL_BACKREF)
			parent = eb->start;
		अन्यथा अगर (root->root_key.objectid != btrfs_header_owner(eb))
			जाओ owner_mismatch;
	पूर्ण अन्यथा अणु
		अगर (wc->flags[level + 1] & BTRFS_BLOCK_FLAG_FULL_BACKREF)
			parent = path->nodes[level + 1]->start;
		अन्यथा अगर (root->root_key.objectid !=
			 btrfs_header_owner(path->nodes[level + 1]))
			जाओ owner_mismatch;
	पूर्ण

	btrfs_मुक्त_tree_block(trans, root, eb, parent, wc->refs[level] == 1);
out:
	wc->refs[level] = 0;
	wc->flags[level] = 0;
	वापस 0;

owner_mismatch:
	btrfs_err_rl(fs_info, "unexpected tree owner, have %llu expect %llu",
		     btrfs_header_owner(eb), root->root_key.objectid);
	वापस -EUCLEAN;
पूर्ण

अटल noअंतरभूत पूर्णांक walk_करोwn_tree(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_root *root,
				   काष्ठा btrfs_path *path,
				   काष्ठा walk_control *wc)
अणु
	पूर्णांक level = wc->level;
	पूर्णांक lookup_info = 1;
	पूर्णांक ret;

	जबतक (level >= 0) अणु
		ret = walk_करोwn_proc(trans, root, path, wc, lookup_info);
		अगर (ret > 0)
			अवरोध;

		अगर (level == 0)
			अवरोध;

		अगर (path->slots[level] >=
		    btrfs_header_nritems(path->nodes[level]))
			अवरोध;

		ret = करो_walk_करोwn(trans, root, path, wc, &lookup_info);
		अगर (ret > 0) अणु
			path->slots[level]++;
			जारी;
		पूर्ण अन्यथा अगर (ret < 0)
			वापस ret;
		level = wc->level;
	पूर्ण
	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक walk_up_tree(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root,
				 काष्ठा btrfs_path *path,
				 काष्ठा walk_control *wc, पूर्णांक max_level)
अणु
	पूर्णांक level = wc->level;
	पूर्णांक ret;

	path->slots[level] = btrfs_header_nritems(path->nodes[level]);
	जबतक (level < max_level && path->nodes[level]) अणु
		wc->level = level;
		अगर (path->slots[level] + 1 <
		    btrfs_header_nritems(path->nodes[level])) अणु
			path->slots[level]++;
			वापस 0;
		पूर्ण अन्यथा अणु
			ret = walk_up_proc(trans, root, path, wc);
			अगर (ret > 0)
				वापस 0;
			अगर (ret < 0)
				वापस ret;

			अगर (path->locks[level]) अणु
				btrfs_tree_unlock_rw(path->nodes[level],
						     path->locks[level]);
				path->locks[level] = 0;
			पूर्ण
			मुक्त_extent_buffer(path->nodes[level]);
			path->nodes[level] = शून्य;
			level++;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * drop a subvolume tree.
 *
 * this function traverses the tree मुक्तing any blocks that only
 * referenced by the tree.
 *
 * when a shared tree block is found. this function decreases its
 * reference count by one. अगर update_ref is true, this function
 * also make sure backrefs क्रम the shared block and all lower level
 * blocks are properly updated.
 *
 * If called with क्रम_reloc == 0, may निकास early with -EAGAIN
 */
पूर्णांक btrfs_drop_snapshot(काष्ठा btrfs_root *root, पूर्णांक update_ref, पूर्णांक क्रम_reloc)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा btrfs_root_item *root_item = &root->root_item;
	काष्ठा walk_control *wc;
	काष्ठा btrfs_key key;
	पूर्णांक err = 0;
	पूर्णांक ret;
	पूर्णांक level;
	bool root_dropped = false;

	btrfs_debug(fs_info, "Drop subvolume %llu", root->root_key.objectid);

	path = btrfs_alloc_path();
	अगर (!path) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	wc = kzalloc(माप(*wc), GFP_NOFS);
	अगर (!wc) अणु
		btrfs_मुक्त_path(path);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Use join to aव्योम potential EINTR from transaction start. See
	 * रुको_reserve_ticket and the whole reservation callchain.
	 */
	अगर (क्रम_reloc)
		trans = btrfs_join_transaction(tree_root);
	अन्यथा
		trans = btrfs_start_transaction(tree_root, 0);
	अगर (IS_ERR(trans)) अणु
		err = PTR_ERR(trans);
		जाओ out_मुक्त;
	पूर्ण

	err = btrfs_run_delayed_items(trans);
	अगर (err)
		जाओ out_end_trans;

	/*
	 * This will help us catch people modअगरying the fs tree जबतक we're
	 * dropping it.  It is unsafe to mess with the fs tree जबतक it's being
	 * dropped as we unlock the root node and parent nodes as we walk करोwn
	 * the tree, assuming nothing will change.  If something करोes change
	 * then we'll have stale information and drop references to blocks we've
	 * alपढ़ोy dropped.
	 */
	set_bit(BTRFS_ROOT_DELETING, &root->state);
	अगर (btrfs_disk_key_objectid(&root_item->drop_progress) == 0) अणु
		level = btrfs_header_level(root->node);
		path->nodes[level] = btrfs_lock_root_node(root);
		path->slots[level] = 0;
		path->locks[level] = BTRFS_WRITE_LOCK;
		स_रखो(&wc->update_progress, 0,
		       माप(wc->update_progress));
	पूर्ण अन्यथा अणु
		btrfs_disk_key_to_cpu(&key, &root_item->drop_progress);
		स_नकल(&wc->update_progress, &key,
		       माप(wc->update_progress));

		level = btrfs_root_drop_level(root_item);
		BUG_ON(level == 0);
		path->lowest_level = level;
		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		path->lowest_level = 0;
		अगर (ret < 0) अणु
			err = ret;
			जाओ out_end_trans;
		पूर्ण
		WARN_ON(ret > 0);

		/*
		 * unlock our path, this is safe because only this
		 * function is allowed to delete this snapshot
		 */
		btrfs_unlock_up_safe(path, 0);

		level = btrfs_header_level(root->node);
		जबतक (1) अणु
			btrfs_tree_lock(path->nodes[level]);
			path->locks[level] = BTRFS_WRITE_LOCK;

			ret = btrfs_lookup_extent_info(trans, fs_info,
						path->nodes[level]->start,
						level, 1, &wc->refs[level],
						&wc->flags[level]);
			अगर (ret < 0) अणु
				err = ret;
				जाओ out_end_trans;
			पूर्ण
			BUG_ON(wc->refs[level] == 0);

			अगर (level == btrfs_root_drop_level(root_item))
				अवरोध;

			btrfs_tree_unlock(path->nodes[level]);
			path->locks[level] = 0;
			WARN_ON(wc->refs[level] != 1);
			level--;
		पूर्ण
	पूर्ण

	wc->restarted = test_bit(BTRFS_ROOT_DEAD_TREE, &root->state);
	wc->level = level;
	wc->shared_level = -1;
	wc->stage = DROP_REFERENCE;
	wc->update_ref = update_ref;
	wc->keep_locks = 0;
	wc->पढ़ोa_count = BTRFS_NODEPTRS_PER_BLOCK(fs_info);

	जबतक (1) अणु

		ret = walk_करोwn_tree(trans, root, path, wc);
		अगर (ret < 0) अणु
			err = ret;
			अवरोध;
		पूर्ण

		ret = walk_up_tree(trans, root, path, wc, BTRFS_MAX_LEVEL);
		अगर (ret < 0) अणु
			err = ret;
			अवरोध;
		पूर्ण

		अगर (ret > 0) अणु
			BUG_ON(wc->stage != DROP_REFERENCE);
			अवरोध;
		पूर्ण

		अगर (wc->stage == DROP_REFERENCE) अणु
			wc->drop_level = wc->level;
			btrfs_node_key_to_cpu(path->nodes[wc->drop_level],
					      &wc->drop_progress,
					      path->slots[wc->drop_level]);
		पूर्ण
		btrfs_cpu_key_to_disk(&root_item->drop_progress,
				      &wc->drop_progress);
		btrfs_set_root_drop_level(root_item, wc->drop_level);

		BUG_ON(wc->level == 0);
		अगर (btrfs_should_end_transaction(trans) ||
		    (!क्रम_reloc && btrfs_need_cleaner_sleep(fs_info))) अणु
			ret = btrfs_update_root(trans, tree_root,
						&root->root_key,
						root_item);
			अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
				err = ret;
				जाओ out_end_trans;
			पूर्ण

			btrfs_end_transaction_throttle(trans);
			अगर (!क्रम_reloc && btrfs_need_cleaner_sleep(fs_info)) अणु
				btrfs_debug(fs_info,
					    "drop snapshot early exit");
				err = -EAGAIN;
				जाओ out_मुक्त;
			पूर्ण

		       /*
			* Use join to aव्योम potential EINTR from transaction
			* start. See रुको_reserve_ticket and the whole
			* reservation callchain.
			*/
			अगर (क्रम_reloc)
				trans = btrfs_join_transaction(tree_root);
			अन्यथा
				trans = btrfs_start_transaction(tree_root, 0);
			अगर (IS_ERR(trans)) अणु
				err = PTR_ERR(trans);
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
	पूर्ण
	btrfs_release_path(path);
	अगर (err)
		जाओ out_end_trans;

	ret = btrfs_del_root(trans, &root->root_key);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		err = ret;
		जाओ out_end_trans;
	पूर्ण

	अगर (root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID) अणु
		ret = btrfs_find_root(tree_root, &root->root_key, path,
				      शून्य, शून्य);
		अगर (ret < 0) अणु
			btrfs_पात_transaction(trans, ret);
			err = ret;
			जाओ out_end_trans;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			/* अगर we fail to delete the orphan item this समय
			 * around, it'll get picked up the next समय.
			 *
			 * The most common failure here is just -ENOENT.
			 */
			btrfs_del_orphan_item(trans, tree_root,
					      root->root_key.objectid);
		पूर्ण
	पूर्ण

	/*
	 * This subvolume is going to be completely dropped, and won't be
	 * recorded as dirty roots, thus pertrans meta rsv will not be मुक्तd at
	 * commit transaction समय.  So मुक्त it here manually.
	 */
	btrfs_qgroup_convert_reserved_meta(root, पूर्णांक_उच्च);
	btrfs_qgroup_मुक्त_meta_all_pertrans(root);

	अगर (test_bit(BTRFS_ROOT_IN_RADIX, &root->state))
		btrfs_add_dropped_root(trans, root);
	अन्यथा
		btrfs_put_root(root);
	root_dropped = true;
out_end_trans:
	btrfs_end_transaction_throttle(trans);
out_मुक्त:
	kमुक्त(wc);
	btrfs_मुक्त_path(path);
out:
	/*
	 * So अगर we need to stop dropping the snapshot क्रम whatever reason we
	 * need to make sure to add it back to the dead root list so that we
	 * keep trying to करो the work later.  This also cleans up roots अगर we
	 * करोn't have it in the radix (like when we recover after a घातer fail
	 * or unmount) so we करोn't leak memory.
	 */
	अगर (!क्रम_reloc && !root_dropped)
		btrfs_add_dead_root(root);
	वापस err;
पूर्ण

/*
 * drop subtree rooted at tree block 'node'.
 *
 * NOTE: this function will unlock and release tree block 'node'
 * only used by relocation code
 */
पूर्णांक btrfs_drop_subtree(काष्ठा btrfs_trans_handle *trans,
			काष्ठा btrfs_root *root,
			काष्ठा extent_buffer *node,
			काष्ठा extent_buffer *parent)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा walk_control *wc;
	पूर्णांक level;
	पूर्णांक parent_level;
	पूर्णांक ret = 0;
	पूर्णांक wret;

	BUG_ON(root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID);

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	wc = kzalloc(माप(*wc), GFP_NOFS);
	अगर (!wc) अणु
		btrfs_मुक्त_path(path);
		वापस -ENOMEM;
	पूर्ण

	btrfs_निश्चित_tree_locked(parent);
	parent_level = btrfs_header_level(parent);
	atomic_inc(&parent->refs);
	path->nodes[parent_level] = parent;
	path->slots[parent_level] = btrfs_header_nritems(parent);

	btrfs_निश्चित_tree_locked(node);
	level = btrfs_header_level(node);
	path->nodes[level] = node;
	path->slots[level] = 0;
	path->locks[level] = BTRFS_WRITE_LOCK;

	wc->refs[parent_level] = 1;
	wc->flags[parent_level] = BTRFS_BLOCK_FLAG_FULL_BACKREF;
	wc->level = level;
	wc->shared_level = -1;
	wc->stage = DROP_REFERENCE;
	wc->update_ref = 0;
	wc->keep_locks = 1;
	wc->पढ़ोa_count = BTRFS_NODEPTRS_PER_BLOCK(fs_info);

	जबतक (1) अणु
		wret = walk_करोwn_tree(trans, root, path, wc);
		अगर (wret < 0) अणु
			ret = wret;
			अवरोध;
		पूर्ण

		wret = walk_up_tree(trans, root, path, wc, parent_level);
		अगर (wret < 0)
			ret = wret;
		अगर (wret != 0)
			अवरोध;
	पूर्ण

	kमुक्त(wc);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * helper to account the unused space of all the पढ़ोonly block group in the
 * space_info. takes mirrors पूर्णांकo account.
 */
u64 btrfs_account_ro_block_groups_मुक्त_space(काष्ठा btrfs_space_info *sinfo)
अणु
	काष्ठा btrfs_block_group *block_group;
	u64 मुक्त_bytes = 0;
	पूर्णांक factor;

	/* It's df, we don't care if it's racy */
	अगर (list_empty(&sinfo->ro_bgs))
		वापस 0;

	spin_lock(&sinfo->lock);
	list_क्रम_each_entry(block_group, &sinfo->ro_bgs, ro_list) अणु
		spin_lock(&block_group->lock);

		अगर (!block_group->ro) अणु
			spin_unlock(&block_group->lock);
			जारी;
		पूर्ण

		factor = btrfs_bg_type_to_factor(block_group->flags);
		मुक्त_bytes += (block_group->length -
			       block_group->used) * factor;

		spin_unlock(&block_group->lock);
	पूर्ण
	spin_unlock(&sinfo->lock);

	वापस मुक्त_bytes;
पूर्ण

पूर्णांक btrfs_error_unpin_extent_range(काष्ठा btrfs_fs_info *fs_info,
				   u64 start, u64 end)
अणु
	वापस unpin_extent_range(fs_info, start, end, false);
पूर्ण

/*
 * It used to be that old block groups would be left around क्रमever.
 * Iterating over them would be enough to trim unused space.  Since we
 * now स्वतःmatically हटाओ them, we also need to iterate over unallocated
 * space.
 *
 * We करोn't want a transaction क्रम this since the discard may take a
 * substantial amount of समय.  We करोn't require that a transaction be
 * running, but we करो need to take a running transaction पूर्णांकo account
 * to ensure that we're not discarding chunks that were released or
 * allocated in the current transaction.
 *
 * Holding the chunks lock will prevent other thपढ़ोs from allocating
 * or releasing chunks, but it won't prevent a running transaction
 * from committing and releasing the memory that the pending chunks
 * list head uses.  For that, we need to take a reference to the
 * transaction and hold the commit root sem.  We only need to hold
 * it जबतक perक्रमming the मुक्त space search since we have alपढ़ोy
 * held back allocations.
 */
अटल पूर्णांक btrfs_trim_मुक्त_extents(काष्ठा btrfs_device *device, u64 *trimmed)
अणु
	u64 start = SZ_1M, len = 0, end = 0;
	पूर्णांक ret;

	*trimmed = 0;

	/* Discard not supported = nothing to करो. */
	अगर (!blk_queue_discard(bdev_get_queue(device->bdev)))
		वापस 0;

	/* Not writable = nothing to करो. */
	अगर (!test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state))
		वापस 0;

	/* No मुक्त space = nothing to करो. */
	अगर (device->total_bytes <= device->bytes_used)
		वापस 0;

	ret = 0;

	जबतक (1) अणु
		काष्ठा btrfs_fs_info *fs_info = device->fs_info;
		u64 bytes;

		ret = mutex_lock_पूर्णांकerruptible(&fs_info->chunk_mutex);
		अगर (ret)
			अवरोध;

		find_first_clear_extent_bit(&device->alloc_state, start,
					    &start, &end,
					    CHUNK_TRIMMED | CHUNK_ALLOCATED);

		/* Check अगर there are any CHUNK_* bits left */
		अगर (start > device->total_bytes) अणु
			WARN_ON(IS_ENABLED(CONFIG_BTRFS_DEBUG));
			btrfs_warn_in_rcu(fs_info,
"ignoring attempt to trim beyond device size: offset %llu length %llu device %s device size %llu",
					  start, end - start + 1,
					  rcu_str_deref(device->name),
					  device->total_bytes);
			mutex_unlock(&fs_info->chunk_mutex);
			ret = 0;
			अवरोध;
		पूर्ण

		/* Ensure we skip the reserved area in the first 1M */
		start = max_t(u64, start, SZ_1M);

		/*
		 * If find_first_clear_extent_bit find a range that spans the
		 * end of the device it will set end to -1, in this हाल it's up
		 * to the caller to trim the value to the size of the device.
		 */
		end = min(end, device->total_bytes - 1);

		len = end - start + 1;

		/* We didn't find any extents */
		अगर (!len) अणु
			mutex_unlock(&fs_info->chunk_mutex);
			ret = 0;
			अवरोध;
		पूर्ण

		ret = btrfs_issue_discard(device->bdev, start, len,
					  &bytes);
		अगर (!ret)
			set_extent_bits(&device->alloc_state, start,
					start + bytes - 1,
					CHUNK_TRIMMED);
		mutex_unlock(&fs_info->chunk_mutex);

		अगर (ret)
			अवरोध;

		start += len;
		*trimmed += bytes;

		अगर (fatal_संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		cond_resched();
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Trim the whole fileप्रणाली by:
 * 1) trimming the मुक्त space in each block group
 * 2) trimming the unallocated space on each device
 *
 * This will also जारी trimming even अगर a block group or device encounters
 * an error.  The वापस value will be the last error, or 0 अगर nothing bad
 * happens.
 */
पूर्णांक btrfs_trim_fs(काष्ठा btrfs_fs_info *fs_info, काष्ठा fstrim_range *range)
अणु
	काष्ठा btrfs_block_group *cache = शून्य;
	काष्ठा btrfs_device *device;
	काष्ठा list_head *devices;
	u64 group_trimmed;
	u64 range_end = U64_MAX;
	u64 start;
	u64 end;
	u64 trimmed = 0;
	u64 bg_failed = 0;
	u64 dev_failed = 0;
	पूर्णांक bg_ret = 0;
	पूर्णांक dev_ret = 0;
	पूर्णांक ret = 0;

	/*
	 * Check range overflow अगर range->len is set.
	 * The शेष range->len is U64_MAX.
	 */
	अगर (range->len != U64_MAX &&
	    check_add_overflow(range->start, range->len, &range_end))
		वापस -EINVAL;

	cache = btrfs_lookup_first_block_group(fs_info, range->start);
	क्रम (; cache; cache = btrfs_next_block_group(cache)) अणु
		अगर (cache->start >= range_end) अणु
			btrfs_put_block_group(cache);
			अवरोध;
		पूर्ण

		start = max(range->start, cache->start);
		end = min(range_end, cache->start + cache->length);

		अगर (end - start >= range->minlen) अणु
			अगर (!btrfs_block_group_करोne(cache)) अणु
				ret = btrfs_cache_block_group(cache, 0);
				अगर (ret) अणु
					bg_failed++;
					bg_ret = ret;
					जारी;
				पूर्ण
				ret = btrfs_रुको_block_group_cache_करोne(cache);
				अगर (ret) अणु
					bg_failed++;
					bg_ret = ret;
					जारी;
				पूर्ण
			पूर्ण
			ret = btrfs_trim_block_group(cache,
						     &group_trimmed,
						     start,
						     end,
						     range->minlen);

			trimmed += group_trimmed;
			अगर (ret) अणु
				bg_failed++;
				bg_ret = ret;
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (bg_failed)
		btrfs_warn(fs_info,
			"failed to trim %llu block group(s), last error %d",
			bg_failed, bg_ret);
	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	devices = &fs_info->fs_devices->devices;
	list_क्रम_each_entry(device, devices, dev_list) अणु
		ret = btrfs_trim_मुक्त_extents(device, &group_trimmed);
		अगर (ret) अणु
			dev_failed++;
			dev_ret = ret;
			अवरोध;
		पूर्ण

		trimmed += group_trimmed;
	पूर्ण
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	अगर (dev_failed)
		btrfs_warn(fs_info,
			"failed to trim %llu device(s), last error %d",
			dev_failed, dev_ret);
	range->len = trimmed;
	अगर (bg_ret)
		वापस bg_ret;
	वापस dev_ret;
पूर्ण
