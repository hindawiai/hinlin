<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 STRATO.  All rights reserved.
 */

#समावेश <linux/mm.h>
#समावेश <linux/rbtree.h>
#समावेश <trace/events/btrfs.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "backref.h"
#समावेश "ulist.h"
#समावेश "transaction.h"
#समावेश "delayed-ref.h"
#समावेश "locking.h"
#समावेश "misc.h"
#समावेश "tree-mod-log.h"

/* Just an arbitrary number so we can be sure this happened */
#घोषणा BACKREF_FOUND_SHARED 6

काष्ठा extent_inode_elem अणु
	u64 inum;
	u64 offset;
	काष्ठा extent_inode_elem *next;
पूर्ण;

अटल पूर्णांक check_extent_in_eb(स्थिर काष्ठा btrfs_key *key,
			      स्थिर काष्ठा extent_buffer *eb,
			      स्थिर काष्ठा btrfs_file_extent_item *fi,
			      u64 extent_item_pos,
			      काष्ठा extent_inode_elem **eie,
			      bool ignore_offset)
अणु
	u64 offset = 0;
	काष्ठा extent_inode_elem *e;

	अगर (!ignore_offset &&
	    !btrfs_file_extent_compression(eb, fi) &&
	    !btrfs_file_extent_encryption(eb, fi) &&
	    !btrfs_file_extent_other_encoding(eb, fi)) अणु
		u64 data_offset;
		u64 data_len;

		data_offset = btrfs_file_extent_offset(eb, fi);
		data_len = btrfs_file_extent_num_bytes(eb, fi);

		अगर (extent_item_pos < data_offset ||
		    extent_item_pos >= data_offset + data_len)
			वापस 1;
		offset = extent_item_pos - data_offset;
	पूर्ण

	e = kदो_स्मृति(माप(*e), GFP_NOFS);
	अगर (!e)
		वापस -ENOMEM;

	e->next = *eie;
	e->inum = key->objectid;
	e->offset = key->offset + offset;
	*eie = e;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_inode_elem_list(काष्ठा extent_inode_elem *eie)
अणु
	काष्ठा extent_inode_elem *eie_next;

	क्रम (; eie; eie = eie_next) अणु
		eie_next = eie->next;
		kमुक्त(eie);
	पूर्ण
पूर्ण

अटल पूर्णांक find_extent_in_eb(स्थिर काष्ठा extent_buffer *eb,
			     u64 wanted_disk_byte, u64 extent_item_pos,
			     काष्ठा extent_inode_elem **eie,
			     bool ignore_offset)
अणु
	u64 disk_byte;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_file_extent_item *fi;
	पूर्णांक slot;
	पूर्णांक nritems;
	पूर्णांक extent_type;
	पूर्णांक ret;

	/*
	 * from the shared data ref, we only have the leaf but we need
	 * the key. thus, we must look पूर्णांकo all items and see that we
	 * find one (some) with a reference to our extent item.
	 */
	nritems = btrfs_header_nritems(eb);
	क्रम (slot = 0; slot < nritems; ++slot) अणु
		btrfs_item_key_to_cpu(eb, &key, slot);
		अगर (key.type != BTRFS_EXTENT_DATA_KEY)
			जारी;
		fi = btrfs_item_ptr(eb, slot, काष्ठा btrfs_file_extent_item);
		extent_type = btrfs_file_extent_type(eb, fi);
		अगर (extent_type == BTRFS_खाता_EXTENT_INLINE)
			जारी;
		/* करोn't skip BTRFS_खाता_EXTENT_PREALLOC, we can handle that */
		disk_byte = btrfs_file_extent_disk_bytenr(eb, fi);
		अगर (disk_byte != wanted_disk_byte)
			जारी;

		ret = check_extent_in_eb(&key, eb, fi, extent_item_pos, eie, ignore_offset);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा preftree अणु
	काष्ठा rb_root_cached root;
	अचिन्हित पूर्णांक count;
पूर्ण;

#घोषणा PREFTREE_INIT	अणु .root = RB_ROOT_CACHED, .count = 0 पूर्ण

काष्ठा preftrees अणु
	काष्ठा preftree direct;    /* BTRFS_SHARED_[DATA|BLOCK]_REF_KEY */
	काष्ठा preftree indirect;  /* BTRFS_[TREE_BLOCK|EXTENT_DATA]_REF_KEY */
	काष्ठा preftree indirect_missing_keys;
पूर्ण;

/*
 * Checks क्रम a shared extent during backref search.
 *
 * The share_count tracks prelim_refs (direct and indirect) having a
 * ref->count >0:
 *  - incremented when a ref->count transitions to >0
 *  - decremented when a ref->count transitions to <1
 */
काष्ठा share_check अणु
	u64 root_objectid;
	u64 inum;
	पूर्णांक share_count;
पूर्ण;

अटल अंतरभूत पूर्णांक extent_is_shared(काष्ठा share_check *sc)
अणु
	वापस (sc && sc->share_count > 1) ? BACKREF_FOUND_SHARED : 0;
पूर्ण

अटल काष्ठा kmem_cache *btrfs_prelim_ref_cache;

पूर्णांक __init btrfs_prelim_ref_init(व्योम)
अणु
	btrfs_prelim_ref_cache = kmem_cache_create("btrfs_prelim_ref",
					माप(काष्ठा prelim_ref),
					0,
					SLAB_MEM_SPREAD,
					शून्य);
	अगर (!btrfs_prelim_ref_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम __cold btrfs_prelim_ref_निकास(व्योम)
अणु
	kmem_cache_destroy(btrfs_prelim_ref_cache);
पूर्ण

अटल व्योम मुक्त_pref(काष्ठा prelim_ref *ref)
अणु
	kmem_cache_मुक्त(btrfs_prelim_ref_cache, ref);
पूर्ण

/*
 * Return 0 when both refs are क्रम the same block (and can be merged).
 * A -1 वापस indicates ref1 is a 'lower' block than ref2, जबतक 1
 * indicates a 'higher' block.
 */
अटल पूर्णांक prelim_ref_compare(काष्ठा prelim_ref *ref1,
			      काष्ठा prelim_ref *ref2)
अणु
	अगर (ref1->level < ref2->level)
		वापस -1;
	अगर (ref1->level > ref2->level)
		वापस 1;
	अगर (ref1->root_id < ref2->root_id)
		वापस -1;
	अगर (ref1->root_id > ref2->root_id)
		वापस 1;
	अगर (ref1->key_क्रम_search.type < ref2->key_क्रम_search.type)
		वापस -1;
	अगर (ref1->key_क्रम_search.type > ref2->key_क्रम_search.type)
		वापस 1;
	अगर (ref1->key_क्रम_search.objectid < ref2->key_क्रम_search.objectid)
		वापस -1;
	अगर (ref1->key_क्रम_search.objectid > ref2->key_क्रम_search.objectid)
		वापस 1;
	अगर (ref1->key_क्रम_search.offset < ref2->key_क्रम_search.offset)
		वापस -1;
	अगर (ref1->key_क्रम_search.offset > ref2->key_क्रम_search.offset)
		वापस 1;
	अगर (ref1->parent < ref2->parent)
		वापस -1;
	अगर (ref1->parent > ref2->parent)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम update_share_count(काष्ठा share_check *sc, पूर्णांक oldcount,
			       पूर्णांक newcount)
अणु
	अगर ((!sc) || (oldcount == 0 && newcount < 1))
		वापस;

	अगर (oldcount > 0 && newcount < 1)
		sc->share_count--;
	अन्यथा अगर (oldcount < 1 && newcount > 0)
		sc->share_count++;
पूर्ण

/*
 * Add @newref to the @root rbtree, merging identical refs.
 *
 * Callers should assume that newref has been मुक्तd after calling.
 */
अटल व्योम prelim_ref_insert(स्थिर काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा preftree *preftree,
			      काष्ठा prelim_ref *newref,
			      काष्ठा share_check *sc)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा prelim_ref *ref;
	पूर्णांक result;
	bool lefपंचांगost = true;

	root = &preftree->root;
	p = &root->rb_root.rb_node;

	जबतक (*p) अणु
		parent = *p;
		ref = rb_entry(parent, काष्ठा prelim_ref, rbnode);
		result = prelim_ref_compare(ref, newref);
		अगर (result < 0) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (result > 0) अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण अन्यथा अणु
			/* Identical refs, merge them and मुक्त @newref */
			काष्ठा extent_inode_elem *eie = ref->inode_list;

			जबतक (eie && eie->next)
				eie = eie->next;

			अगर (!eie)
				ref->inode_list = newref->inode_list;
			अन्यथा
				eie->next = newref->inode_list;
			trace_btrfs_prelim_ref_merge(fs_info, ref, newref,
						     preftree->count);
			/*
			 * A delayed ref can have newref->count < 0.
			 * The ref->count is updated to follow any
			 * BTRFS_[ADD|DROP]_DELAYED_REF actions.
			 */
			update_share_count(sc, ref->count,
					   ref->count + newref->count);
			ref->count += newref->count;
			मुक्त_pref(newref);
			वापस;
		पूर्ण
	पूर्ण

	update_share_count(sc, 0, newref->count);
	preftree->count++;
	trace_btrfs_prelim_ref_insert(fs_info, newref, शून्य, preftree->count);
	rb_link_node(&newref->rbnode, parent, p);
	rb_insert_color_cached(&newref->rbnode, root, lefपंचांगost);
पूर्ण

/*
 * Release the entire tree.  We करोn't care about पूर्णांकernal consistency so
 * just मुक्त everything and then reset the tree root.
 */
अटल व्योम prelim_release(काष्ठा preftree *preftree)
अणु
	काष्ठा prelim_ref *ref, *next_ref;

	rbtree_postorder_क्रम_each_entry_safe(ref, next_ref,
					     &preftree->root.rb_root, rbnode)
		मुक्त_pref(ref);

	preftree->root = RB_ROOT_CACHED;
	preftree->count = 0;
पूर्ण

/*
 * the rules क्रम all callers of this function are:
 * - obtaining the parent is the goal
 * - अगर you add a key, you must know that it is a correct key
 * - अगर you cannot add the parent or a correct key, then we will look पूर्णांकo the
 *   block later to set a correct key
 *
 * delayed refs
 * ============
 *        backref type | shared | indirect | shared | indirect
 * inक्रमmation         |   tree |     tree |   data |     data
 * --------------------+--------+----------+--------+----------
 *      parent logical |    y   |     -    |    -   |     -
 *      key to resolve |    -   |     y    |    y   |     y
 *  tree block logical |    -   |     -    |    -   |     -
 *  root क्रम resolving |    y   |     y    |    y   |     y
 *
 * - column 1:       we've the parent -> करोne
 * - column 2, 3, 4: we use the key to find the parent
 *
 * on disk refs (अंतरभूत or keyed)
 * ==============================
 *        backref type | shared | indirect | shared | indirect
 * inक्रमmation         |   tree |     tree |   data |     data
 * --------------------+--------+----------+--------+----------
 *      parent logical |    y   |     -    |    y   |     -
 *      key to resolve |    -   |     -    |    -   |     y
 *  tree block logical |    y   |     y    |    y   |     y
 *  root क्रम resolving |    -   |     y    |    y   |     y
 *
 * - column 1, 3: we've the parent -> करोne
 * - column 2:    we take the first key from the block to find the parent
 *                (see add_missing_keys)
 * - column 4:    we use the key to find the parent
 *
 * additional inक्रमmation that's available but not required to find the parent
 * block might help in merging entries to gain some speed.
 */
अटल पूर्णांक add_prelim_ref(स्थिर काष्ठा btrfs_fs_info *fs_info,
			  काष्ठा preftree *preftree, u64 root_id,
			  स्थिर काष्ठा btrfs_key *key, पूर्णांक level, u64 parent,
			  u64 wanted_disk_byte, पूर्णांक count,
			  काष्ठा share_check *sc, gfp_t gfp_mask)
अणु
	काष्ठा prelim_ref *ref;

	अगर (root_id == BTRFS_DATA_RELOC_TREE_OBJECTID)
		वापस 0;

	ref = kmem_cache_alloc(btrfs_prelim_ref_cache, gfp_mask);
	अगर (!ref)
		वापस -ENOMEM;

	ref->root_id = root_id;
	अगर (key)
		ref->key_क्रम_search = *key;
	अन्यथा
		स_रखो(&ref->key_क्रम_search, 0, माप(ref->key_क्रम_search));

	ref->inode_list = शून्य;
	ref->level = level;
	ref->count = count;
	ref->parent = parent;
	ref->wanted_disk_byte = wanted_disk_byte;
	prelim_ref_insert(fs_info, preftree, ref, sc);
	वापस extent_is_shared(sc);
पूर्ण

/* direct refs use root == 0, key == शून्य */
अटल पूर्णांक add_direct_ref(स्थिर काष्ठा btrfs_fs_info *fs_info,
			  काष्ठा preftrees *preftrees, पूर्णांक level, u64 parent,
			  u64 wanted_disk_byte, पूर्णांक count,
			  काष्ठा share_check *sc, gfp_t gfp_mask)
अणु
	वापस add_prelim_ref(fs_info, &preftrees->direct, 0, शून्य, level,
			      parent, wanted_disk_byte, count, sc, gfp_mask);
पूर्ण

/* indirect refs use parent == 0 */
अटल पूर्णांक add_indirect_ref(स्थिर काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा preftrees *preftrees, u64 root_id,
			    स्थिर काष्ठा btrfs_key *key, पूर्णांक level,
			    u64 wanted_disk_byte, पूर्णांक count,
			    काष्ठा share_check *sc, gfp_t gfp_mask)
अणु
	काष्ठा preftree *tree = &preftrees->indirect;

	अगर (!key)
		tree = &preftrees->indirect_missing_keys;
	वापस add_prelim_ref(fs_info, tree, root_id, key, level, 0,
			      wanted_disk_byte, count, sc, gfp_mask);
पूर्ण

अटल पूर्णांक is_shared_data_backref(काष्ठा preftrees *preftrees, u64 bytenr)
अणु
	काष्ठा rb_node **p = &preftrees->direct.root.rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा prelim_ref *ref = शून्य;
	काष्ठा prelim_ref target = अणुपूर्ण;
	पूर्णांक result;

	target.parent = bytenr;

	जबतक (*p) अणु
		parent = *p;
		ref = rb_entry(parent, काष्ठा prelim_ref, rbnode);
		result = prelim_ref_compare(ref, &target);

		अगर (result < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (result > 0)
			p = &(*p)->rb_right;
		अन्यथा
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक add_all_parents(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			   काष्ठा ulist *parents,
			   काष्ठा preftrees *preftrees, काष्ठा prelim_ref *ref,
			   पूर्णांक level, u64 समय_seq, स्थिर u64 *extent_item_pos,
			   bool ignore_offset)
अणु
	पूर्णांक ret = 0;
	पूर्णांक slot;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key *key_क्रम_search = &ref->key_क्रम_search;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा extent_inode_elem *eie = शून्य, *old = शून्य;
	u64 disk_byte;
	u64 wanted_disk_byte = ref->wanted_disk_byte;
	u64 count = 0;
	u64 data_offset;

	अगर (level != 0) अणु
		eb = path->nodes[level];
		ret = ulist_add(parents, eb->start, 0, GFP_NOFS);
		अगर (ret < 0)
			वापस ret;
		वापस 0;
	पूर्ण

	/*
	 * 1. We normally enter this function with the path alपढ़ोy poपूर्णांकing to
	 *    the first item to check. But someबार, we may enter it with
	 *    slot == nritems.
	 * 2. We are searching क्रम normal backref but bytenr of this leaf
	 *    matches shared data backref
	 * 3. The leaf owner is not equal to the root we are searching
	 *
	 * For these हालs, go to the next leaf beक्रमe we जारी.
	 */
	eb = path->nodes[0];
	अगर (path->slots[0] >= btrfs_header_nritems(eb) ||
	    is_shared_data_backref(preftrees, eb->start) ||
	    ref->root_id != btrfs_header_owner(eb)) अणु
		अगर (समय_seq == BTRFS_SEQ_LAST)
			ret = btrfs_next_leaf(root, path);
		अन्यथा
			ret = btrfs_next_old_leaf(root, path, समय_seq);
	पूर्ण

	जबतक (!ret && count < ref->count) अणु
		eb = path->nodes[0];
		slot = path->slots[0];

		btrfs_item_key_to_cpu(eb, &key, slot);

		अगर (key.objectid != key_क्रम_search->objectid ||
		    key.type != BTRFS_EXTENT_DATA_KEY)
			अवरोध;

		/*
		 * We are searching क्रम normal backref but bytenr of this leaf
		 * matches shared data backref, OR
		 * the leaf owner is not equal to the root we are searching क्रम
		 */
		अगर (slot == 0 &&
		    (is_shared_data_backref(preftrees, eb->start) ||
		     ref->root_id != btrfs_header_owner(eb))) अणु
			अगर (समय_seq == BTRFS_SEQ_LAST)
				ret = btrfs_next_leaf(root, path);
			अन्यथा
				ret = btrfs_next_old_leaf(root, path, समय_seq);
			जारी;
		पूर्ण
		fi = btrfs_item_ptr(eb, slot, काष्ठा btrfs_file_extent_item);
		disk_byte = btrfs_file_extent_disk_bytenr(eb, fi);
		data_offset = btrfs_file_extent_offset(eb, fi);

		अगर (disk_byte == wanted_disk_byte) अणु
			eie = शून्य;
			old = शून्य;
			अगर (ref->key_क्रम_search.offset == key.offset - data_offset)
				count++;
			अन्यथा
				जाओ next;
			अगर (extent_item_pos) अणु
				ret = check_extent_in_eb(&key, eb, fi,
						*extent_item_pos,
						&eie, ignore_offset);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
			अगर (ret > 0)
				जाओ next;
			ret = ulist_add_merge_ptr(parents, eb->start,
						  eie, (व्योम **)&old, GFP_NOFS);
			अगर (ret < 0)
				अवरोध;
			अगर (!ret && extent_item_pos) अणु
				जबतक (old->next)
					old = old->next;
				old->next = eie;
			पूर्ण
			eie = शून्य;
		पूर्ण
next:
		अगर (समय_seq == BTRFS_SEQ_LAST)
			ret = btrfs_next_item(root, path);
		अन्यथा
			ret = btrfs_next_old_item(root, path, समय_seq);
	पूर्ण

	अगर (ret > 0)
		ret = 0;
	अन्यथा अगर (ret < 0)
		मुक्त_inode_elem_list(eie);
	वापस ret;
पूर्ण

/*
 * resolve an indirect backref in the क्रमm (root_id, key, level)
 * to a logical address
 */
अटल पूर्णांक resolve_indirect_ref(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_path *path, u64 समय_seq,
				काष्ठा preftrees *preftrees,
				काष्ठा prelim_ref *ref, काष्ठा ulist *parents,
				स्थिर u64 *extent_item_pos, bool ignore_offset)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा extent_buffer *eb;
	पूर्णांक ret = 0;
	पूर्णांक root_level;
	पूर्णांक level = ref->level;
	काष्ठा btrfs_key search_key = ref->key_क्रम_search;

	/*
	 * If we're search_commit_root we could possibly be holding locks on
	 * other tree nodes.  This happens when qgroups करोes backref walks when
	 * adding new delayed refs.  To deal with this we need to look in cache
	 * क्रम the root, and अगर we करोn't find it then we need to search the
	 * tree_root's commit root, thus the btrfs_get_fs_root_commit_root usage
	 * here.
	 */
	अगर (path->search_commit_root)
		root = btrfs_get_fs_root_commit_root(fs_info, path, ref->root_id);
	अन्यथा
		root = btrfs_get_fs_root(fs_info, ref->root_id, false);
	अगर (IS_ERR(root)) अणु
		ret = PTR_ERR(root);
		जाओ out_मुक्त;
	पूर्ण

	अगर (!path->search_commit_root &&
	    test_bit(BTRFS_ROOT_DELETING, &root->state)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (btrfs_is_testing(fs_info)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (path->search_commit_root)
		root_level = btrfs_header_level(root->commit_root);
	अन्यथा अगर (समय_seq == BTRFS_SEQ_LAST)
		root_level = btrfs_header_level(root->node);
	अन्यथा
		root_level = btrfs_old_root_level(root, समय_seq);

	अगर (root_level + 1 == level)
		जाओ out;

	/*
	 * We can often find data backrefs with an offset that is too large
	 * (>= Lदीर्घ_उच्च, maximum allowed file offset) due to underflows when
	 * subtracting a file's offset with the data offset of its
	 * corresponding extent data item. This can happen क्रम example in the
	 * clone ioctl.
	 *
	 * So अगर we detect such हाल we set the search key's offset to zero to
	 * make sure we will find the matching file extent item at
	 * add_all_parents(), otherwise we will miss it because the offset
	 * taken क्रमm the backref is much larger then the offset of the file
	 * extent item. This can make us scan a very large number of file
	 * extent items, but at least it will not make us miss any.
	 *
	 * This is an ugly workaround क्रम a behaviour that should have never
	 * existed, but it करोes and a fix क्रम the clone ioctl would touch a lot
	 * of places, cause backwards incompatibility and would not fix the
	 * problem क्रम extents cloned with older kernels.
	 */
	अगर (search_key.type == BTRFS_EXTENT_DATA_KEY &&
	    search_key.offset >= Lदीर्घ_उच्च)
		search_key.offset = 0;
	path->lowest_level = level;
	अगर (समय_seq == BTRFS_SEQ_LAST)
		ret = btrfs_search_slot(शून्य, root, &search_key, path, 0, 0);
	अन्यथा
		ret = btrfs_search_old_slot(root, &search_key, path, समय_seq);

	btrfs_debug(fs_info,
		"search slot in root %llu (level %d, ref count %d) returned %d for key (%llu %u %llu)",
		 ref->root_id, level, ref->count, ret,
		 ref->key_क्रम_search.objectid, ref->key_क्रम_search.type,
		 ref->key_क्रम_search.offset);
	अगर (ret < 0)
		जाओ out;

	eb = path->nodes[level];
	जबतक (!eb) अणु
		अगर (WARN_ON(!level)) अणु
			ret = 1;
			जाओ out;
		पूर्ण
		level--;
		eb = path->nodes[level];
	पूर्ण

	ret = add_all_parents(root, path, parents, preftrees, ref, level,
			      समय_seq, extent_item_pos, ignore_offset);
out:
	btrfs_put_root(root);
out_मुक्त:
	path->lowest_level = 0;
	btrfs_release_path(path);
	वापस ret;
पूर्ण

अटल काष्ठा extent_inode_elem *
unode_aux_to_inode_list(काष्ठा ulist_node *node)
अणु
	अगर (!node)
		वापस शून्य;
	वापस (काष्ठा extent_inode_elem *)(uपूर्णांकptr_t)node->aux;
पूर्ण

/*
 * We मुख्यtain three separate rbtrees: one क्रम direct refs, one क्रम
 * indirect refs which have a key, and one क्रम indirect refs which करो not
 * have a key. Each tree करोes merge on insertion.
 *
 * Once all of the references are located, we iterate over the tree of
 * indirect refs with missing keys. An appropriate key is located and
 * the ref is moved onto the tree क्रम indirect refs. After all missing
 * keys are thus located, we iterate over the indirect ref tree, resolve
 * each reference, and then insert the resolved reference onto the
 * direct tree (merging there too).
 *
 * New backrefs (i.e., क्रम parent nodes) are added to the appropriate
 * rbtree as they are encountered. The new backrefs are subsequently
 * resolved as above.
 */
अटल पूर्णांक resolve_indirect_refs(काष्ठा btrfs_fs_info *fs_info,
				 काष्ठा btrfs_path *path, u64 समय_seq,
				 काष्ठा preftrees *preftrees,
				 स्थिर u64 *extent_item_pos,
				 काष्ठा share_check *sc, bool ignore_offset)
अणु
	पूर्णांक err;
	पूर्णांक ret = 0;
	काष्ठा ulist *parents;
	काष्ठा ulist_node *node;
	काष्ठा ulist_iterator uiter;
	काष्ठा rb_node *rnode;

	parents = ulist_alloc(GFP_NOFS);
	अगर (!parents)
		वापस -ENOMEM;

	/*
	 * We could trade memory usage क्रम perक्रमmance here by iterating
	 * the tree, allocating new refs क्रम each insertion, and then
	 * मुक्तing the entire indirect tree when we're करोne.  In some test
	 * हालs, the tree can grow quite large (~200k objects).
	 */
	जबतक ((rnode = rb_first_cached(&preftrees->indirect.root))) अणु
		काष्ठा prelim_ref *ref;

		ref = rb_entry(rnode, काष्ठा prelim_ref, rbnode);
		अगर (WARN(ref->parent,
			 "BUG: direct ref found in indirect tree")) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		rb_erase_cached(&ref->rbnode, &preftrees->indirect.root);
		preftrees->indirect.count--;

		अगर (ref->count == 0) अणु
			मुक्त_pref(ref);
			जारी;
		पूर्ण

		अगर (sc && sc->root_objectid &&
		    ref->root_id != sc->root_objectid) अणु
			मुक्त_pref(ref);
			ret = BACKREF_FOUND_SHARED;
			जाओ out;
		पूर्ण
		err = resolve_indirect_ref(fs_info, path, समय_seq, preftrees,
					   ref, parents, extent_item_pos,
					   ignore_offset);
		/*
		 * we can only tolerate ENOENT,otherwise,we should catch error
		 * and वापस directly.
		 */
		अगर (err == -ENOENT) अणु
			prelim_ref_insert(fs_info, &preftrees->direct, ref,
					  शून्य);
			जारी;
		पूर्ण अन्यथा अगर (err) अणु
			मुक्त_pref(ref);
			ret = err;
			जाओ out;
		पूर्ण

		/* we put the first parent पूर्णांकo the ref at hand */
		ULIST_ITER_INIT(&uiter);
		node = ulist_next(parents, &uiter);
		ref->parent = node ? node->val : 0;
		ref->inode_list = unode_aux_to_inode_list(node);

		/* Add a prelim_ref(s) क्रम any other parent(s). */
		जबतक ((node = ulist_next(parents, &uiter))) अणु
			काष्ठा prelim_ref *new_ref;

			new_ref = kmem_cache_alloc(btrfs_prelim_ref_cache,
						   GFP_NOFS);
			अगर (!new_ref) अणु
				मुक्त_pref(ref);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			स_नकल(new_ref, ref, माप(*ref));
			new_ref->parent = node->val;
			new_ref->inode_list = unode_aux_to_inode_list(node);
			prelim_ref_insert(fs_info, &preftrees->direct,
					  new_ref, शून्य);
		पूर्ण

		/*
		 * Now it's a direct ref, put it in the direct tree. We must
		 * करो this last because the ref could be merged/मुक्तd here.
		 */
		prelim_ref_insert(fs_info, &preftrees->direct, ref, शून्य);

		ulist_reinit(parents);
		cond_resched();
	पूर्ण
out:
	ulist_मुक्त(parents);
	वापस ret;
पूर्ण

/*
 * पढ़ो tree blocks and add keys where required.
 */
अटल पूर्णांक add_missing_keys(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा preftrees *preftrees, bool lock)
अणु
	काष्ठा prelim_ref *ref;
	काष्ठा extent_buffer *eb;
	काष्ठा preftree *tree = &preftrees->indirect_missing_keys;
	काष्ठा rb_node *node;

	जबतक ((node = rb_first_cached(&tree->root))) अणु
		ref = rb_entry(node, काष्ठा prelim_ref, rbnode);
		rb_erase_cached(node, &tree->root);

		BUG_ON(ref->parent);	/* should not be a direct ref */
		BUG_ON(ref->key_क्रम_search.type);
		BUG_ON(!ref->wanted_disk_byte);

		eb = पढ़ो_tree_block(fs_info, ref->wanted_disk_byte,
				     ref->root_id, 0, ref->level - 1, शून्य);
		अगर (IS_ERR(eb)) अणु
			मुक्त_pref(ref);
			वापस PTR_ERR(eb);
		पूर्ण अन्यथा अगर (!extent_buffer_uptodate(eb)) अणु
			मुक्त_pref(ref);
			मुक्त_extent_buffer(eb);
			वापस -EIO;
		पूर्ण
		अगर (lock)
			btrfs_tree_पढ़ो_lock(eb);
		अगर (btrfs_header_level(eb) == 0)
			btrfs_item_key_to_cpu(eb, &ref->key_क्रम_search, 0);
		अन्यथा
			btrfs_node_key_to_cpu(eb, &ref->key_क्रम_search, 0);
		अगर (lock)
			btrfs_tree_पढ़ो_unlock(eb);
		मुक्त_extent_buffer(eb);
		prelim_ref_insert(fs_info, &preftrees->indirect, ref, शून्य);
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * add all currently queued delayed refs from this head whose seq nr is
 * smaller or equal that seq to the list
 */
अटल पूर्णांक add_delayed_refs(स्थिर काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_delayed_ref_head *head, u64 seq,
			    काष्ठा preftrees *preftrees, काष्ठा share_check *sc)
अणु
	काष्ठा btrfs_delayed_ref_node *node;
	काष्ठा btrfs_delayed_extent_op *extent_op = head->extent_op;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key पंचांगp_op_key;
	काष्ठा rb_node *n;
	पूर्णांक count;
	पूर्णांक ret = 0;

	अगर (extent_op && extent_op->update_key)
		btrfs_disk_key_to_cpu(&पंचांगp_op_key, &extent_op->key);

	spin_lock(&head->lock);
	क्रम (n = rb_first_cached(&head->ref_tree); n; n = rb_next(n)) अणु
		node = rb_entry(n, काष्ठा btrfs_delayed_ref_node,
				ref_node);
		अगर (node->seq > seq)
			जारी;

		चयन (node->action) अणु
		हाल BTRFS_ADD_DELAYED_EXTENT:
		हाल BTRFS_UPDATE_DELAYED_HEAD:
			WARN_ON(1);
			जारी;
		हाल BTRFS_ADD_DELAYED_REF:
			count = node->ref_mod;
			अवरोध;
		हाल BTRFS_DROP_DELAYED_REF:
			count = node->ref_mod * -1;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		चयन (node->type) अणु
		हाल BTRFS_TREE_BLOCK_REF_KEY: अणु
			/* NORMAL INसूचीECT METADATA backref */
			काष्ठा btrfs_delayed_tree_ref *ref;

			ref = btrfs_delayed_node_to_tree_ref(node);
			ret = add_indirect_ref(fs_info, preftrees, ref->root,
					       &पंचांगp_op_key, ref->level + 1,
					       node->bytenr, count, sc,
					       GFP_ATOMIC);
			अवरोध;
		पूर्ण
		हाल BTRFS_SHARED_BLOCK_REF_KEY: अणु
			/* SHARED सूचीECT METADATA backref */
			काष्ठा btrfs_delayed_tree_ref *ref;

			ref = btrfs_delayed_node_to_tree_ref(node);

			ret = add_direct_ref(fs_info, preftrees, ref->level + 1,
					     ref->parent, node->bytenr, count,
					     sc, GFP_ATOMIC);
			अवरोध;
		पूर्ण
		हाल BTRFS_EXTENT_DATA_REF_KEY: अणु
			/* NORMAL INसूचीECT DATA backref */
			काष्ठा btrfs_delayed_data_ref *ref;
			ref = btrfs_delayed_node_to_data_ref(node);

			key.objectid = ref->objectid;
			key.type = BTRFS_EXTENT_DATA_KEY;
			key.offset = ref->offset;

			/*
			 * Found a inum that करोesn't match our known inum, we
			 * know it's shared.
			 */
			अगर (sc && sc->inum && ref->objectid != sc->inum) अणु
				ret = BACKREF_FOUND_SHARED;
				जाओ out;
			पूर्ण

			ret = add_indirect_ref(fs_info, preftrees, ref->root,
					       &key, 0, node->bytenr, count, sc,
					       GFP_ATOMIC);
			अवरोध;
		पूर्ण
		हाल BTRFS_SHARED_DATA_REF_KEY: अणु
			/* SHARED सूचीECT FULL backref */
			काष्ठा btrfs_delayed_data_ref *ref;

			ref = btrfs_delayed_node_to_data_ref(node);

			ret = add_direct_ref(fs_info, preftrees, 0, ref->parent,
					     node->bytenr, count, sc,
					     GFP_ATOMIC);
			अवरोध;
		पूर्ण
		शेष:
			WARN_ON(1);
		पूर्ण
		/*
		 * We must ignore BACKREF_FOUND_SHARED until all delayed
		 * refs have been checked.
		 */
		अगर (ret && (ret != BACKREF_FOUND_SHARED))
			अवरोध;
	पूर्ण
	अगर (!ret)
		ret = extent_is_shared(sc);
out:
	spin_unlock(&head->lock);
	वापस ret;
पूर्ण

/*
 * add all अंतरभूत backrefs क्रम bytenr to the list
 *
 * Returns 0 on success, <0 on error, or BACKREF_FOUND_SHARED.
 */
अटल पूर्णांक add_अंतरभूत_refs(स्थिर काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_path *path, u64 bytenr,
			   पूर्णांक *info_level, काष्ठा preftrees *preftrees,
			   काष्ठा share_check *sc)
अणु
	पूर्णांक ret = 0;
	पूर्णांक slot;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	अचिन्हित दीर्घ ptr;
	अचिन्हित दीर्घ end;
	काष्ठा btrfs_extent_item *ei;
	u64 flags;
	u64 item_size;

	/*
	 * क्रमागतerate all अंतरभूत refs
	 */
	leaf = path->nodes[0];
	slot = path->slots[0];

	item_size = btrfs_item_size_nr(leaf, slot);
	BUG_ON(item_size < माप(*ei));

	ei = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_extent_item);
	flags = btrfs_extent_flags(leaf, ei);
	btrfs_item_key_to_cpu(leaf, &found_key, slot);

	ptr = (अचिन्हित दीर्घ)(ei + 1);
	end = (अचिन्हित दीर्घ)ei + item_size;

	अगर (found_key.type == BTRFS_EXTENT_ITEM_KEY &&
	    flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
		काष्ठा btrfs_tree_block_info *info;

		info = (काष्ठा btrfs_tree_block_info *)ptr;
		*info_level = btrfs_tree_block_level(leaf, info);
		ptr += माप(काष्ठा btrfs_tree_block_info);
		BUG_ON(ptr > end);
	पूर्ण अन्यथा अगर (found_key.type == BTRFS_METADATA_ITEM_KEY) अणु
		*info_level = found_key.offset;
	पूर्ण अन्यथा अणु
		BUG_ON(!(flags & BTRFS_EXTENT_FLAG_DATA));
	पूर्ण

	जबतक (ptr < end) अणु
		काष्ठा btrfs_extent_अंतरभूत_ref *iref;
		u64 offset;
		पूर्णांक type;

		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)ptr;
		type = btrfs_get_extent_अंतरभूत_ref_type(leaf, iref,
							BTRFS_REF_TYPE_ANY);
		अगर (type == BTRFS_REF_TYPE_INVALID)
			वापस -EUCLEAN;

		offset = btrfs_extent_अंतरभूत_ref_offset(leaf, iref);

		चयन (type) अणु
		हाल BTRFS_SHARED_BLOCK_REF_KEY:
			ret = add_direct_ref(fs_info, preftrees,
					     *info_level + 1, offset,
					     bytenr, 1, शून्य, GFP_NOFS);
			अवरोध;
		हाल BTRFS_SHARED_DATA_REF_KEY: अणु
			काष्ठा btrfs_shared_data_ref *sdref;
			पूर्णांक count;

			sdref = (काष्ठा btrfs_shared_data_ref *)(iref + 1);
			count = btrfs_shared_data_ref_count(leaf, sdref);

			ret = add_direct_ref(fs_info, preftrees, 0, offset,
					     bytenr, count, sc, GFP_NOFS);
			अवरोध;
		पूर्ण
		हाल BTRFS_TREE_BLOCK_REF_KEY:
			ret = add_indirect_ref(fs_info, preftrees, offset,
					       शून्य, *info_level + 1,
					       bytenr, 1, शून्य, GFP_NOFS);
			अवरोध;
		हाल BTRFS_EXTENT_DATA_REF_KEY: अणु
			काष्ठा btrfs_extent_data_ref *dref;
			पूर्णांक count;
			u64 root;

			dref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
			count = btrfs_extent_data_ref_count(leaf, dref);
			key.objectid = btrfs_extent_data_ref_objectid(leaf,
								      dref);
			key.type = BTRFS_EXTENT_DATA_KEY;
			key.offset = btrfs_extent_data_ref_offset(leaf, dref);

			अगर (sc && sc->inum && key.objectid != sc->inum) अणु
				ret = BACKREF_FOUND_SHARED;
				अवरोध;
			पूर्ण

			root = btrfs_extent_data_ref_root(leaf, dref);

			ret = add_indirect_ref(fs_info, preftrees, root,
					       &key, 0, bytenr, count,
					       sc, GFP_NOFS);
			अवरोध;
		पूर्ण
		शेष:
			WARN_ON(1);
		पूर्ण
		अगर (ret)
			वापस ret;
		ptr += btrfs_extent_अंतरभूत_ref_size(type);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * add all non-अंतरभूत backrefs क्रम bytenr to the list
 *
 * Returns 0 on success, <0 on error, or BACKREF_FOUND_SHARED.
 */
अटल पूर्णांक add_keyed_refs(काष्ठा btrfs_fs_info *fs_info,
			  काष्ठा btrfs_path *path, u64 bytenr,
			  पूर्णांक info_level, काष्ठा preftrees *preftrees,
			  काष्ठा share_check *sc)
अणु
	काष्ठा btrfs_root *extent_root = fs_info->extent_root;
	पूर्णांक ret;
	पूर्णांक slot;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;

	जबतक (1) अणु
		ret = btrfs_next_item(extent_root, path);
		अगर (ret < 0)
			अवरोध;
		अगर (ret) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		slot = path->slots[0];
		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &key, slot);

		अगर (key.objectid != bytenr)
			अवरोध;
		अगर (key.type < BTRFS_TREE_BLOCK_REF_KEY)
			जारी;
		अगर (key.type > BTRFS_SHARED_DATA_REF_KEY)
			अवरोध;

		चयन (key.type) अणु
		हाल BTRFS_SHARED_BLOCK_REF_KEY:
			/* SHARED सूचीECT METADATA backref */
			ret = add_direct_ref(fs_info, preftrees,
					     info_level + 1, key.offset,
					     bytenr, 1, शून्य, GFP_NOFS);
			अवरोध;
		हाल BTRFS_SHARED_DATA_REF_KEY: अणु
			/* SHARED सूचीECT FULL backref */
			काष्ठा btrfs_shared_data_ref *sdref;
			पूर्णांक count;

			sdref = btrfs_item_ptr(leaf, slot,
					      काष्ठा btrfs_shared_data_ref);
			count = btrfs_shared_data_ref_count(leaf, sdref);
			ret = add_direct_ref(fs_info, preftrees, 0,
					     key.offset, bytenr, count,
					     sc, GFP_NOFS);
			अवरोध;
		पूर्ण
		हाल BTRFS_TREE_BLOCK_REF_KEY:
			/* NORMAL INसूचीECT METADATA backref */
			ret = add_indirect_ref(fs_info, preftrees, key.offset,
					       शून्य, info_level + 1, bytenr,
					       1, शून्य, GFP_NOFS);
			अवरोध;
		हाल BTRFS_EXTENT_DATA_REF_KEY: अणु
			/* NORMAL INसूचीECT DATA backref */
			काष्ठा btrfs_extent_data_ref *dref;
			पूर्णांक count;
			u64 root;

			dref = btrfs_item_ptr(leaf, slot,
					      काष्ठा btrfs_extent_data_ref);
			count = btrfs_extent_data_ref_count(leaf, dref);
			key.objectid = btrfs_extent_data_ref_objectid(leaf,
								      dref);
			key.type = BTRFS_EXTENT_DATA_KEY;
			key.offset = btrfs_extent_data_ref_offset(leaf, dref);

			अगर (sc && sc->inum && key.objectid != sc->inum) अणु
				ret = BACKREF_FOUND_SHARED;
				अवरोध;
			पूर्ण

			root = btrfs_extent_data_ref_root(leaf, dref);
			ret = add_indirect_ref(fs_info, preftrees, root,
					       &key, 0, bytenr, count,
					       sc, GFP_NOFS);
			अवरोध;
		पूर्ण
		शेष:
			WARN_ON(1);
		पूर्ण
		अगर (ret)
			वापस ret;

	पूर्ण

	वापस ret;
पूर्ण

/*
 * this adds all existing backrefs (अंतरभूत backrefs, backrefs and delayed
 * refs) क्रम the given bytenr to the refs list, merges duplicates and resolves
 * indirect refs to their parent bytenr.
 * When roots are found, they're added to the roots list
 *
 * If समय_seq is set to BTRFS_SEQ_LAST, it will not search delayed_refs, and
 * behave much like trans == शून्य हाल, the dअगरference only lies in it will not
 * commit root.
 * The special हाल is क्रम qgroup to search roots in commit_transaction().
 *
 * @sc - अगर !शून्य, then immediately वापस BACKREF_FOUND_SHARED when a
 * shared extent is detected.
 *
 * Otherwise this वापसs 0 क्रम success and <0 क्रम an error.
 *
 * If ignore_offset is set to false, only extent refs whose offsets match
 * extent_item_pos are वापसed.  If true, every extent ref is वापसed
 * and extent_item_pos is ignored.
 *
 * FIXME some caching might speed things up
 */
अटल पूर्णांक find_parent_nodes(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			     u64 समय_seq, काष्ठा ulist *refs,
			     काष्ठा ulist *roots, स्थिर u64 *extent_item_pos,
			     काष्ठा share_check *sc, bool ignore_offset)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_delayed_ref_root *delayed_refs = शून्य;
	काष्ठा btrfs_delayed_ref_head *head;
	पूर्णांक info_level = 0;
	पूर्णांक ret;
	काष्ठा prelim_ref *ref;
	काष्ठा rb_node *node;
	काष्ठा extent_inode_elem *eie = शून्य;
	काष्ठा preftrees preftrees = अणु
		.direct = PREFTREE_INIT,
		.indirect = PREFTREE_INIT,
		.indirect_missing_keys = PREFTREE_INIT
	पूर्ण;

	key.objectid = bytenr;
	key.offset = (u64)-1;
	अगर (btrfs_fs_incompat(fs_info, SKINNY_METADATA))
		key.type = BTRFS_METADATA_ITEM_KEY;
	अन्यथा
		key.type = BTRFS_EXTENT_ITEM_KEY;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	अगर (!trans) अणु
		path->search_commit_root = 1;
		path->skip_locking = 1;
	पूर्ण

	अगर (समय_seq == BTRFS_SEQ_LAST)
		path->skip_locking = 1;

	/*
	 * grab both a lock on the path and a lock on the delayed ref head.
	 * We need both to get a consistent picture of how the refs look
	 * at a specअगरied poपूर्णांक in समय
	 */
again:
	head = शून्य;

	ret = btrfs_search_slot(trans, fs_info->extent_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	BUG_ON(ret == 0);

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
	अगर (trans && likely(trans->type != __TRANS_DUMMY) &&
	    समय_seq != BTRFS_SEQ_LAST) अणु
#अन्यथा
	अगर (trans && समय_seq != BTRFS_SEQ_LAST) अणु
#पूर्ण_अगर
		/*
		 * look अगर there are updates क्रम this ref queued and lock the
		 * head
		 */
		delayed_refs = &trans->transaction->delayed_refs;
		spin_lock(&delayed_refs->lock);
		head = btrfs_find_delayed_ref_head(delayed_refs, bytenr);
		अगर (head) अणु
			अगर (!mutex_trylock(&head->mutex)) अणु
				refcount_inc(&head->refs);
				spin_unlock(&delayed_refs->lock);

				btrfs_release_path(path);

				/*
				 * Mutex was contended, block until it's
				 * released and try again
				 */
				mutex_lock(&head->mutex);
				mutex_unlock(&head->mutex);
				btrfs_put_delayed_ref_head(head);
				जाओ again;
			पूर्ण
			spin_unlock(&delayed_refs->lock);
			ret = add_delayed_refs(fs_info, head, समय_seq,
					       &preftrees, sc);
			mutex_unlock(&head->mutex);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अणु
			spin_unlock(&delayed_refs->lock);
		पूर्ण
	पूर्ण

	अगर (path->slots[0]) अणु
		काष्ठा extent_buffer *leaf;
		पूर्णांक slot;

		path->slots[0]--;
		leaf = path->nodes[0];
		slot = path->slots[0];
		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.objectid == bytenr &&
		    (key.type == BTRFS_EXTENT_ITEM_KEY ||
		     key.type == BTRFS_METADATA_ITEM_KEY)) अणु
			ret = add_अंतरभूत_refs(fs_info, path, bytenr,
					      &info_level, &preftrees, sc);
			अगर (ret)
				जाओ out;
			ret = add_keyed_refs(fs_info, path, bytenr, info_level,
					     &preftrees, sc);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

	btrfs_release_path(path);

	ret = add_missing_keys(fs_info, &preftrees, path->skip_locking == 0);
	अगर (ret)
		जाओ out;

	WARN_ON(!RB_EMPTY_ROOT(&preftrees.indirect_missing_keys.root.rb_root));

	ret = resolve_indirect_refs(fs_info, path, समय_seq, &preftrees,
				    extent_item_pos, sc, ignore_offset);
	अगर (ret)
		जाओ out;

	WARN_ON(!RB_EMPTY_ROOT(&preftrees.indirect.root.rb_root));

	/*
	 * This walks the tree of merged and resolved refs. Tree blocks are
	 * पढ़ो in as needed. Unique entries are added to the ulist, and
	 * the list of found roots is updated.
	 *
	 * We release the entire tree in one go beक्रमe वापसing.
	 */
	node = rb_first_cached(&preftrees.direct.root);
	जबतक (node) अणु
		ref = rb_entry(node, काष्ठा prelim_ref, rbnode);
		node = rb_next(&ref->rbnode);
		/*
		 * ref->count < 0 can happen here अगर there are delayed
		 * refs with a node->action of BTRFS_DROP_DELAYED_REF.
		 * prelim_ref_insert() relies on this when merging
		 * identical refs to keep the overall count correct.
		 * prelim_ref_insert() will merge only those refs
		 * which compare identically.  Any refs having
		 * e.g. dअगरferent offsets would not be merged,
		 * and would retain their original ref->count < 0.
		 */
		अगर (roots && ref->count && ref->root_id && ref->parent == 0) अणु
			अगर (sc && sc->root_objectid &&
			    ref->root_id != sc->root_objectid) अणु
				ret = BACKREF_FOUND_SHARED;
				जाओ out;
			पूर्ण

			/* no parent == root of tree */
			ret = ulist_add(roots, ref->root_id, 0, GFP_NOFS);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
		अगर (ref->count && ref->parent) अणु
			अगर (extent_item_pos && !ref->inode_list &&
			    ref->level == 0) अणु
				काष्ठा extent_buffer *eb;

				eb = पढ़ो_tree_block(fs_info, ref->parent, 0,
						     0, ref->level, शून्य);
				अगर (IS_ERR(eb)) अणु
					ret = PTR_ERR(eb);
					जाओ out;
				पूर्ण अन्यथा अगर (!extent_buffer_uptodate(eb)) अणु
					मुक्त_extent_buffer(eb);
					ret = -EIO;
					जाओ out;
				पूर्ण

				अगर (!path->skip_locking)
					btrfs_tree_पढ़ो_lock(eb);
				ret = find_extent_in_eb(eb, bytenr,
							*extent_item_pos, &eie, ignore_offset);
				अगर (!path->skip_locking)
					btrfs_tree_पढ़ो_unlock(eb);
				मुक्त_extent_buffer(eb);
				अगर (ret < 0)
					जाओ out;
				ref->inode_list = eie;
			पूर्ण
			ret = ulist_add_merge_ptr(refs, ref->parent,
						  ref->inode_list,
						  (व्योम **)&eie, GFP_NOFS);
			अगर (ret < 0)
				जाओ out;
			अगर (!ret && extent_item_pos) अणु
				/*
				 * we've recorded that parent, so we must extend
				 * its inode list here
				 */
				BUG_ON(!eie);
				जबतक (eie->next)
					eie = eie->next;
				eie->next = ref->inode_list;
			पूर्ण
			eie = शून्य;
		पूर्ण
		cond_resched();
	पूर्ण

out:
	btrfs_मुक्त_path(path);

	prelim_release(&preftrees.direct);
	prelim_release(&preftrees.indirect);
	prelim_release(&preftrees.indirect_missing_keys);

	अगर (ret < 0)
		मुक्त_inode_elem_list(eie);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_leaf_list(काष्ठा ulist *blocks)
अणु
	काष्ठा ulist_node *node = शून्य;
	काष्ठा extent_inode_elem *eie;
	काष्ठा ulist_iterator uiter;

	ULIST_ITER_INIT(&uiter);
	जबतक ((node = ulist_next(blocks, &uiter))) अणु
		अगर (!node->aux)
			जारी;
		eie = unode_aux_to_inode_list(node);
		मुक्त_inode_elem_list(eie);
		node->aux = 0;
	पूर्ण

	ulist_मुक्त(blocks);
पूर्ण

/*
 * Finds all leafs with a reference to the specअगरied combination of bytenr and
 * offset. key_list_head will poपूर्णांक to a list of corresponding keys (caller must
 * मुक्त each list element). The leafs will be stored in the leafs ulist, which
 * must be मुक्तd with ulist_मुक्त.
 *
 * वापसs 0 on success, <0 on error
 */
पूर्णांक btrfs_find_all_leafs(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			 u64 समय_seq, काष्ठा ulist **leafs,
			 स्थिर u64 *extent_item_pos, bool ignore_offset)
अणु
	पूर्णांक ret;

	*leafs = ulist_alloc(GFP_NOFS);
	अगर (!*leafs)
		वापस -ENOMEM;

	ret = find_parent_nodes(trans, fs_info, bytenr, समय_seq,
				*leafs, शून्य, extent_item_pos, शून्य, ignore_offset);
	अगर (ret < 0 && ret != -ENOENT) अणु
		मुक्त_leaf_list(*leafs);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * walk all backrefs क्रम a given extent to find all roots that reference this
 * extent. Walking a backref means finding all extents that reference this
 * extent and in turn walk the backrefs of those, too. Naturally this is a
 * recursive process, but here it is implemented in an iterative fashion: We
 * find all referencing extents क्रम the extent in question and put them on a
 * list. In turn, we find all referencing extents क्रम those, further appending
 * to the list. The way we iterate the list allows adding more elements after
 * the current जबतक iterating. The process stops when we reach the end of the
 * list. Found roots are added to the roots list.
 *
 * वापसs 0 on success, < 0 on error.
 */
अटल पूर्णांक btrfs_find_all_roots_safe(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
				     u64 समय_seq, काष्ठा ulist **roots,
				     bool ignore_offset)
अणु
	काष्ठा ulist *पंचांगp;
	काष्ठा ulist_node *node = शून्य;
	काष्ठा ulist_iterator uiter;
	पूर्णांक ret;

	पंचांगp = ulist_alloc(GFP_NOFS);
	अगर (!पंचांगp)
		वापस -ENOMEM;
	*roots = ulist_alloc(GFP_NOFS);
	अगर (!*roots) अणु
		ulist_मुक्त(पंचांगp);
		वापस -ENOMEM;
	पूर्ण

	ULIST_ITER_INIT(&uiter);
	जबतक (1) अणु
		ret = find_parent_nodes(trans, fs_info, bytenr, समय_seq,
					पंचांगp, *roots, शून्य, शून्य, ignore_offset);
		अगर (ret < 0 && ret != -ENOENT) अणु
			ulist_मुक्त(पंचांगp);
			ulist_मुक्त(*roots);
			*roots = शून्य;
			वापस ret;
		पूर्ण
		node = ulist_next(पंचांगp, &uiter);
		अगर (!node)
			अवरोध;
		bytenr = node->val;
		cond_resched();
	पूर्ण

	ulist_मुक्त(पंचांगp);
	वापस 0;
पूर्ण

पूर्णांक btrfs_find_all_roots(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			 u64 समय_seq, काष्ठा ulist **roots,
			 bool ignore_offset)
अणु
	पूर्णांक ret;

	अगर (!trans)
		करोwn_पढ़ो(&fs_info->commit_root_sem);
	ret = btrfs_find_all_roots_safe(trans, fs_info, bytenr,
					समय_seq, roots, ignore_offset);
	अगर (!trans)
		up_पढ़ो(&fs_info->commit_root_sem);
	वापस ret;
पूर्ण

/**
 * Check अगर an extent is shared or not
 *
 * @root:   root inode beदीर्घs to
 * @inum:   inode number of the inode whose extent we are checking
 * @bytenr: logical bytenr of the extent we are checking
 * @roots:  list of roots this extent is shared among
 * @पंचांगp:    temporary list used क्रम iteration
 *
 * btrfs_check_shared uses the backref walking code but will लघु
 * circuit as soon as it finds a root or inode that करोesn't match the
 * one passed in. This provides a signअगरicant perक्रमmance benefit क्रम
 * callers (such as fiemap) which want to know whether the extent is
 * shared but करो not need a ref count.
 *
 * This attempts to attach to the running transaction in order to account क्रम
 * delayed refs, but जारीs on even when no running transaction exists.
 *
 * Return: 0 अगर extent is not shared, 1 अगर it is shared, < 0 on error.
 */
पूर्णांक btrfs_check_shared(काष्ठा btrfs_root *root, u64 inum, u64 bytenr,
		काष्ठा ulist *roots, काष्ठा ulist *पंचांगp)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा ulist_iterator uiter;
	काष्ठा ulist_node *node;
	काष्ठा btrfs_seq_list elem = BTRFS_SEQ_LIST_INIT(elem);
	पूर्णांक ret = 0;
	काष्ठा share_check shared = अणु
		.root_objectid = root->root_key.objectid,
		.inum = inum,
		.share_count = 0,
	पूर्ण;

	ulist_init(roots);
	ulist_init(पंचांगp);

	trans = btrfs_join_transaction_nostart(root);
	अगर (IS_ERR(trans)) अणु
		अगर (PTR_ERR(trans) != -ENOENT && PTR_ERR(trans) != -EROFS) अणु
			ret = PTR_ERR(trans);
			जाओ out;
		पूर्ण
		trans = शून्य;
		करोwn_पढ़ो(&fs_info->commit_root_sem);
	पूर्ण अन्यथा अणु
		btrfs_get_tree_mod_seq(fs_info, &elem);
	पूर्ण

	ULIST_ITER_INIT(&uiter);
	जबतक (1) अणु
		ret = find_parent_nodes(trans, fs_info, bytenr, elem.seq, पंचांगp,
					roots, शून्य, &shared, false);
		अगर (ret == BACKREF_FOUND_SHARED) अणु
			/* this is the only condition under which we वापस 1 */
			ret = 1;
			अवरोध;
		पूर्ण
		अगर (ret < 0 && ret != -ENOENT)
			अवरोध;
		ret = 0;
		node = ulist_next(पंचांगp, &uiter);
		अगर (!node)
			अवरोध;
		bytenr = node->val;
		shared.share_count = 0;
		cond_resched();
	पूर्ण

	अगर (trans) अणु
		btrfs_put_tree_mod_seq(fs_info, &elem);
		btrfs_end_transaction(trans);
	पूर्ण अन्यथा अणु
		up_पढ़ो(&fs_info->commit_root_sem);
	पूर्ण
out:
	ulist_release(roots);
	ulist_release(पंचांगp);
	वापस ret;
पूर्ण

पूर्णांक btrfs_find_one_extref(काष्ठा btrfs_root *root, u64 inode_objectid,
			  u64 start_off, काष्ठा btrfs_path *path,
			  काष्ठा btrfs_inode_extref **ret_extref,
			  u64 *found_off)
अणु
	पूर्णांक ret, slot;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_inode_extref *extref;
	स्थिर काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ ptr;

	key.objectid = inode_objectid;
	key.type = BTRFS_INODE_EXTREF_KEY;
	key.offset = start_off;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;

	जबतक (1) अणु
		leaf = path->nodes[0];
		slot = path->slots[0];
		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			/*
			 * If the item at offset is not found,
			 * btrfs_search_slot will poपूर्णांक us to the slot
			 * where it should be inserted. In our हाल
			 * that will be the slot directly beक्रमe the
			 * next INODE_REF_KEY_V2 item. In the हाल
			 * that we're poपूर्णांकing to the last slot in a
			 * leaf, we must move one leaf over.
			 */
			ret = btrfs_next_leaf(root, path);
			अगर (ret) अणु
				अगर (ret >= 1)
					ret = -ENOENT;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &found_key, slot);

		/*
		 * Check that we're still looking at an extended ref key क्रम
		 * this particular objectid. If we have dअगरferent
		 * objectid or type then there are no more to be found
		 * in the tree and we can निकास.
		 */
		ret = -ENOENT;
		अगर (found_key.objectid != inode_objectid)
			अवरोध;
		अगर (found_key.type != BTRFS_INODE_EXTREF_KEY)
			अवरोध;

		ret = 0;
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		extref = (काष्ठा btrfs_inode_extref *)ptr;
		*ret_extref = extref;
		अगर (found_off)
			*found_off = found_key.offset;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * this iterates to turn a name (from iref/extref) पूर्णांकo a full fileप्रणाली path.
 * Elements of the path are separated by '/' and the path is guaranteed to be
 * 0-terminated. the path is only given within the current file प्रणाली.
 * Thereक्रमe, it never starts with a '/'. the caller is responsible to provide
 * "size" bytes in "dest". the dest buffer will be filled backwards. finally,
 * the start poपूर्णांक of the resulting string is वापसed. this poपूर्णांकer is within
 * dest, normally.
 * in हाल the path buffer would overflow, the poपूर्णांकer is decremented further
 * as अगर output was written to the buffer, though no more output is actually
 * generated. that way, the caller can determine how much space would be
 * required क्रम the path to fit पूर्णांकo the buffer. in that हाल, the वापसed
 * value will be smaller than dest. callers must check this!
 */
अक्षर *btrfs_ref_to_path(काष्ठा btrfs_root *fs_root, काष्ठा btrfs_path *path,
			u32 name_len, अचिन्हित दीर्घ name_off,
			काष्ठा extent_buffer *eb_in, u64 parent,
			अक्षर *dest, u32 size)
अणु
	पूर्णांक slot;
	u64 next_inum;
	पूर्णांक ret;
	s64 bytes_left = ((s64)size) - 1;
	काष्ठा extent_buffer *eb = eb_in;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_inode_ref *iref;

	अगर (bytes_left >= 0)
		dest[bytes_left] = '\0';

	जबतक (1) अणु
		bytes_left -= name_len;
		अगर (bytes_left >= 0)
			पढ़ो_extent_buffer(eb, dest + bytes_left,
					   name_off, name_len);
		अगर (eb != eb_in) अणु
			अगर (!path->skip_locking)
				btrfs_tree_पढ़ो_unlock(eb);
			मुक्त_extent_buffer(eb);
		पूर्ण
		ret = btrfs_find_item(fs_root, path, parent, 0,
				BTRFS_INODE_REF_KEY, &found_key);
		अगर (ret > 0)
			ret = -ENOENT;
		अगर (ret)
			अवरोध;

		next_inum = found_key.offset;

		/* regular निकास ahead */
		अगर (parent == next_inum)
			अवरोध;

		slot = path->slots[0];
		eb = path->nodes[0];
		/* make sure we can use eb after releasing the path */
		अगर (eb != eb_in) अणु
			path->nodes[0] = शून्य;
			path->locks[0] = 0;
		पूर्ण
		btrfs_release_path(path);
		iref = btrfs_item_ptr(eb, slot, काष्ठा btrfs_inode_ref);

		name_len = btrfs_inode_ref_name_len(eb, iref);
		name_off = (अचिन्हित दीर्घ)(iref + 1);

		parent = next_inum;
		--bytes_left;
		अगर (bytes_left >= 0)
			dest[bytes_left] = '/';
	पूर्ण

	btrfs_release_path(path);

	अगर (ret)
		वापस ERR_PTR(ret);

	वापस dest + bytes_left;
पूर्ण

/*
 * this makes the path poपूर्णांक to (logical EXTENT_ITEM *)
 * वापसs BTRFS_EXTENT_FLAG_DATA क्रम data, BTRFS_EXTENT_FLAG_TREE_BLOCK क्रम
 * tree blocks and <0 on error.
 */
पूर्णांक extent_from_logical(काष्ठा btrfs_fs_info *fs_info, u64 logical,
			काष्ठा btrfs_path *path, काष्ठा btrfs_key *found_key,
			u64 *flags_ret)
अणु
	पूर्णांक ret;
	u64 flags;
	u64 size = 0;
	u32 item_size;
	स्थिर काष्ठा extent_buffer *eb;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_key key;

	अगर (btrfs_fs_incompat(fs_info, SKINNY_METADATA))
		key.type = BTRFS_METADATA_ITEM_KEY;
	अन्यथा
		key.type = BTRFS_EXTENT_ITEM_KEY;
	key.objectid = logical;
	key.offset = (u64)-1;

	ret = btrfs_search_slot(शून्य, fs_info->extent_root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;

	ret = btrfs_previous_extent_item(fs_info->extent_root, path, 0);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = -ENOENT;
		वापस ret;
	पूर्ण
	btrfs_item_key_to_cpu(path->nodes[0], found_key, path->slots[0]);
	अगर (found_key->type == BTRFS_METADATA_ITEM_KEY)
		size = fs_info->nodesize;
	अन्यथा अगर (found_key->type == BTRFS_EXTENT_ITEM_KEY)
		size = found_key->offset;

	अगर (found_key->objectid > logical ||
	    found_key->objectid + size <= logical) अणु
		btrfs_debug(fs_info,
			"logical %llu is not within any extent", logical);
		वापस -ENOENT;
	पूर्ण

	eb = path->nodes[0];
	item_size = btrfs_item_size_nr(eb, path->slots[0]);
	BUG_ON(item_size < माप(*ei));

	ei = btrfs_item_ptr(eb, path->slots[0], काष्ठा btrfs_extent_item);
	flags = btrfs_extent_flags(eb, ei);

	btrfs_debug(fs_info,
		"logical %llu is at position %llu within the extent (%llu EXTENT_ITEM %llu) flags %#llx size %u",
		 logical, logical - found_key->objectid, found_key->objectid,
		 found_key->offset, flags, item_size);

	WARN_ON(!flags_ret);
	अगर (flags_ret) अणु
		अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK)
			*flags_ret = BTRFS_EXTENT_FLAG_TREE_BLOCK;
		अन्यथा अगर (flags & BTRFS_EXTENT_FLAG_DATA)
			*flags_ret = BTRFS_EXTENT_FLAG_DATA;
		अन्यथा
			BUG();
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

/*
 * helper function to iterate extent अंतरभूत refs. ptr must poपूर्णांक to a 0 value
 * क्रम the first call and may be modअगरied. it is used to track state.
 * अगर more refs exist, 0 is वापसed and the next call to
 * get_extent_अंतरभूत_ref must pass the modअगरied ptr parameter to get the
 * next ref. after the last ref was processed, 1 is वापसed.
 * वापसs <0 on error
 */
अटल पूर्णांक get_extent_अंतरभूत_ref(अचिन्हित दीर्घ *ptr,
				 स्थिर काष्ठा extent_buffer *eb,
				 स्थिर काष्ठा btrfs_key *key,
				 स्थिर काष्ठा btrfs_extent_item *ei,
				 u32 item_size,
				 काष्ठा btrfs_extent_अंतरभूत_ref **out_eiref,
				 पूर्णांक *out_type)
अणु
	अचिन्हित दीर्घ end;
	u64 flags;
	काष्ठा btrfs_tree_block_info *info;

	अगर (!*ptr) अणु
		/* first call */
		flags = btrfs_extent_flags(eb, ei);
		अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
			अगर (key->type == BTRFS_METADATA_ITEM_KEY) अणु
				/* a skinny metadata extent */
				*out_eiref =
				     (काष्ठा btrfs_extent_अंतरभूत_ref *)(ei + 1);
			पूर्ण अन्यथा अणु
				WARN_ON(key->type != BTRFS_EXTENT_ITEM_KEY);
				info = (काष्ठा btrfs_tree_block_info *)(ei + 1);
				*out_eiref =
				   (काष्ठा btrfs_extent_अंतरभूत_ref *)(info + 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			*out_eiref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(ei + 1);
		पूर्ण
		*ptr = (अचिन्हित दीर्घ)*out_eiref;
		अगर ((अचिन्हित दीर्घ)(*ptr) >= (अचिन्हित दीर्घ)ei + item_size)
			वापस -ENOENT;
	पूर्ण

	end = (अचिन्हित दीर्घ)ei + item_size;
	*out_eiref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(*ptr);
	*out_type = btrfs_get_extent_अंतरभूत_ref_type(eb, *out_eiref,
						     BTRFS_REF_TYPE_ANY);
	अगर (*out_type == BTRFS_REF_TYPE_INVALID)
		वापस -EUCLEAN;

	*ptr += btrfs_extent_अंतरभूत_ref_size(*out_type);
	WARN_ON(*ptr > end);
	अगर (*ptr == end)
		वापस 1; /* last */

	वापस 0;
पूर्ण

/*
 * पढ़ोs the tree block backref क्रम an extent. tree level and root are वापसed
 * through out_level and out_root. ptr must poपूर्णांक to a 0 value क्रम the first
 * call and may be modअगरied (see get_extent_अंतरभूत_ref comment).
 * वापसs 0 अगर data was provided, 1 अगर there was no more data to provide or
 * <0 on error.
 */
पूर्णांक tree_backref_क्रम_extent(अचिन्हित दीर्घ *ptr, काष्ठा extent_buffer *eb,
			    काष्ठा btrfs_key *key, काष्ठा btrfs_extent_item *ei,
			    u32 item_size, u64 *out_root, u8 *out_level)
अणु
	पूर्णांक ret;
	पूर्णांक type;
	काष्ठा btrfs_extent_अंतरभूत_ref *eiref;

	अगर (*ptr == (अचिन्हित दीर्घ)-1)
		वापस 1;

	जबतक (1) अणु
		ret = get_extent_अंतरभूत_ref(ptr, eb, key, ei, item_size,
					      &eiref, &type);
		अगर (ret < 0)
			वापस ret;

		अगर (type == BTRFS_TREE_BLOCK_REF_KEY ||
		    type == BTRFS_SHARED_BLOCK_REF_KEY)
			अवरोध;

		अगर (ret == 1)
			वापस 1;
	पूर्ण

	/* we can treat both ref types equally here */
	*out_root = btrfs_extent_अंतरभूत_ref_offset(eb, eiref);

	अगर (key->type == BTRFS_EXTENT_ITEM_KEY) अणु
		काष्ठा btrfs_tree_block_info *info;

		info = (काष्ठा btrfs_tree_block_info *)(ei + 1);
		*out_level = btrfs_tree_block_level(eb, info);
	पूर्ण अन्यथा अणु
		ASSERT(key->type == BTRFS_METADATA_ITEM_KEY);
		*out_level = (u8)key->offset;
	पूर्ण

	अगर (ret == 1)
		*ptr = (अचिन्हित दीर्घ)-1;

	वापस 0;
पूर्ण

अटल पूर्णांक iterate_leaf_refs(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा extent_inode_elem *inode_list,
			     u64 root, u64 extent_item_objectid,
			     iterate_extent_inodes_t *iterate, व्योम *ctx)
अणु
	काष्ठा extent_inode_elem *eie;
	पूर्णांक ret = 0;

	क्रम (eie = inode_list; eie; eie = eie->next) अणु
		btrfs_debug(fs_info,
			    "ref for %llu resolved, key (%llu EXTEND_DATA %llu), root %llu",
			    extent_item_objectid, eie->inum,
			    eie->offset, root);
		ret = iterate(eie->inum, eie->offset, root, ctx);
		अगर (ret) अणु
			btrfs_debug(fs_info,
				    "stopping iteration for %llu due to ret=%d",
				    extent_item_objectid, ret);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * calls iterate() क्रम every inode that references the extent identअगरied by
 * the given parameters.
 * when the iterator function वापसs a non-zero value, iteration stops.
 */
पूर्णांक iterate_extent_inodes(काष्ठा btrfs_fs_info *fs_info,
				u64 extent_item_objectid, u64 extent_item_pos,
				पूर्णांक search_commit_root,
				iterate_extent_inodes_t *iterate, व्योम *ctx,
				bool ignore_offset)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	काष्ठा ulist *refs = शून्य;
	काष्ठा ulist *roots = शून्य;
	काष्ठा ulist_node *ref_node = शून्य;
	काष्ठा ulist_node *root_node = शून्य;
	काष्ठा btrfs_seq_list seq_elem = BTRFS_SEQ_LIST_INIT(seq_elem);
	काष्ठा ulist_iterator ref_uiter;
	काष्ठा ulist_iterator root_uiter;

	btrfs_debug(fs_info, "resolving all inodes for extent %llu",
			extent_item_objectid);

	अगर (!search_commit_root) अणु
		trans = btrfs_attach_transaction(fs_info->extent_root);
		अगर (IS_ERR(trans)) अणु
			अगर (PTR_ERR(trans) != -ENOENT &&
			    PTR_ERR(trans) != -EROFS)
				वापस PTR_ERR(trans);
			trans = शून्य;
		पूर्ण
	पूर्ण

	अगर (trans)
		btrfs_get_tree_mod_seq(fs_info, &seq_elem);
	अन्यथा
		करोwn_पढ़ो(&fs_info->commit_root_sem);

	ret = btrfs_find_all_leafs(trans, fs_info, extent_item_objectid,
				   seq_elem.seq, &refs,
				   &extent_item_pos, ignore_offset);
	अगर (ret)
		जाओ out;

	ULIST_ITER_INIT(&ref_uiter);
	जबतक (!ret && (ref_node = ulist_next(refs, &ref_uiter))) अणु
		ret = btrfs_find_all_roots_safe(trans, fs_info, ref_node->val,
						seq_elem.seq, &roots,
						ignore_offset);
		अगर (ret)
			अवरोध;
		ULIST_ITER_INIT(&root_uiter);
		जबतक (!ret && (root_node = ulist_next(roots, &root_uiter))) अणु
			btrfs_debug(fs_info,
				    "root %llu references leaf %llu, data list %#llx",
				    root_node->val, ref_node->val,
				    ref_node->aux);
			ret = iterate_leaf_refs(fs_info,
						(काष्ठा extent_inode_elem *)
						(uपूर्णांकptr_t)ref_node->aux,
						root_node->val,
						extent_item_objectid,
						iterate, ctx);
		पूर्ण
		ulist_मुक्त(roots);
	पूर्ण

	मुक्त_leaf_list(refs);
out:
	अगर (trans) अणु
		btrfs_put_tree_mod_seq(fs_info, &seq_elem);
		btrfs_end_transaction(trans);
	पूर्ण अन्यथा अणु
		up_पढ़ो(&fs_info->commit_root_sem);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक iterate_inodes_from_logical(u64 logical, काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_path *path,
				iterate_extent_inodes_t *iterate, व्योम *ctx,
				bool ignore_offset)
अणु
	पूर्णांक ret;
	u64 extent_item_pos;
	u64 flags = 0;
	काष्ठा btrfs_key found_key;
	पूर्णांक search_commit_root = path->search_commit_root;

	ret = extent_from_logical(fs_info, logical, path, &found_key, &flags);
	btrfs_release_path(path);
	अगर (ret < 0)
		वापस ret;
	अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK)
		वापस -EINVAL;

	extent_item_pos = logical - found_key.objectid;
	ret = iterate_extent_inodes(fs_info, found_key.objectid,
					extent_item_pos, search_commit_root,
					iterate, ctx, ignore_offset);

	वापस ret;
पूर्ण

प्रकार पूर्णांक (iterate_irefs_t)(u64 parent, u32 name_len, अचिन्हित दीर्घ name_off,
			      काष्ठा extent_buffer *eb, व्योम *ctx);

अटल पूर्णांक iterate_inode_refs(u64 inum, काष्ठा btrfs_root *fs_root,
			      काष्ठा btrfs_path *path,
			      iterate_irefs_t *iterate, व्योम *ctx)
अणु
	पूर्णांक ret = 0;
	पूर्णांक slot;
	u32 cur;
	u32 len;
	u32 name_len;
	u64 parent = 0;
	पूर्णांक found = 0;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_item *item;
	काष्ठा btrfs_inode_ref *iref;
	काष्ठा btrfs_key found_key;

	जबतक (!ret) अणु
		ret = btrfs_find_item(fs_root, path, inum,
				parent ? parent + 1 : 0, BTRFS_INODE_REF_KEY,
				&found_key);

		अगर (ret < 0)
			अवरोध;
		अगर (ret) अणु
			ret = found ? 0 : -ENOENT;
			अवरोध;
		पूर्ण
		++found;

		parent = found_key.offset;
		slot = path->slots[0];
		eb = btrfs_clone_extent_buffer(path->nodes[0]);
		अगर (!eb) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		btrfs_release_path(path);

		item = btrfs_item_nr(slot);
		iref = btrfs_item_ptr(eb, slot, काष्ठा btrfs_inode_ref);

		क्रम (cur = 0; cur < btrfs_item_size(eb, item); cur += len) अणु
			name_len = btrfs_inode_ref_name_len(eb, iref);
			/* path must be released beक्रमe calling iterate()! */
			btrfs_debug(fs_root->fs_info,
				"following ref at offset %u for inode %llu in tree %llu",
				cur, found_key.objectid,
				fs_root->root_key.objectid);
			ret = iterate(parent, name_len,
				      (अचिन्हित दीर्घ)(iref + 1), eb, ctx);
			अगर (ret)
				अवरोध;
			len = माप(*iref) + name_len;
			iref = (काष्ठा btrfs_inode_ref *)((अक्षर *)iref + len);
		पूर्ण
		मुक्त_extent_buffer(eb);
	पूर्ण

	btrfs_release_path(path);

	वापस ret;
पूर्ण

अटल पूर्णांक iterate_inode_extrefs(u64 inum, काष्ठा btrfs_root *fs_root,
				 काष्ठा btrfs_path *path,
				 iterate_irefs_t *iterate, व्योम *ctx)
अणु
	पूर्णांक ret;
	पूर्णांक slot;
	u64 offset = 0;
	u64 parent;
	पूर्णांक found = 0;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_inode_extref *extref;
	u32 item_size;
	u32 cur_offset;
	अचिन्हित दीर्घ ptr;

	जबतक (1) अणु
		ret = btrfs_find_one_extref(fs_root, inum, offset, path, &extref,
					    &offset);
		अगर (ret < 0)
			अवरोध;
		अगर (ret) अणु
			ret = found ? 0 : -ENOENT;
			अवरोध;
		पूर्ण
		++found;

		slot = path->slots[0];
		eb = btrfs_clone_extent_buffer(path->nodes[0]);
		अगर (!eb) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		btrfs_release_path(path);

		item_size = btrfs_item_size_nr(eb, slot);
		ptr = btrfs_item_ptr_offset(eb, slot);
		cur_offset = 0;

		जबतक (cur_offset < item_size) अणु
			u32 name_len;

			extref = (काष्ठा btrfs_inode_extref *)(ptr + cur_offset);
			parent = btrfs_inode_extref_parent(eb, extref);
			name_len = btrfs_inode_extref_name_len(eb, extref);
			ret = iterate(parent, name_len,
				      (अचिन्हित दीर्घ)&extref->name, eb, ctx);
			अगर (ret)
				अवरोध;

			cur_offset += btrfs_inode_extref_name_len(eb, extref);
			cur_offset += माप(*extref);
		पूर्ण
		मुक्त_extent_buffer(eb);

		offset++;
	पूर्ण

	btrfs_release_path(path);

	वापस ret;
पूर्ण

अटल पूर्णांक iterate_irefs(u64 inum, काष्ठा btrfs_root *fs_root,
			 काष्ठा btrfs_path *path, iterate_irefs_t *iterate,
			 व्योम *ctx)
अणु
	पूर्णांक ret;
	पूर्णांक found_refs = 0;

	ret = iterate_inode_refs(inum, fs_root, path, iterate, ctx);
	अगर (!ret)
		++found_refs;
	अन्यथा अगर (ret != -ENOENT)
		वापस ret;

	ret = iterate_inode_extrefs(inum, fs_root, path, iterate, ctx);
	अगर (ret == -ENOENT && found_refs)
		वापस 0;

	वापस ret;
पूर्ण

/*
 * वापसs 0 अगर the path could be dumped (probably truncated)
 * वापसs <0 in हाल of an error
 */
अटल पूर्णांक inode_to_path(u64 inum, u32 name_len, अचिन्हित दीर्घ name_off,
			 काष्ठा extent_buffer *eb, व्योम *ctx)
अणु
	काष्ठा inode_fs_paths *ipath = ctx;
	अक्षर *fspath;
	अक्षर *fspath_min;
	पूर्णांक i = ipath->fspath->elem_cnt;
	स्थिर पूर्णांक s_ptr = माप(अक्षर *);
	u32 bytes_left;

	bytes_left = ipath->fspath->bytes_left > s_ptr ?
					ipath->fspath->bytes_left - s_ptr : 0;

	fspath_min = (अक्षर *)ipath->fspath->val + (i + 1) * s_ptr;
	fspath = btrfs_ref_to_path(ipath->fs_root, ipath->btrfs_path, name_len,
				   name_off, eb, inum, fspath_min, bytes_left);
	अगर (IS_ERR(fspath))
		वापस PTR_ERR(fspath);

	अगर (fspath > fspath_min) अणु
		ipath->fspath->val[i] = (u64)(अचिन्हित दीर्घ)fspath;
		++ipath->fspath->elem_cnt;
		ipath->fspath->bytes_left = fspath - fspath_min;
	पूर्ण अन्यथा अणु
		++ipath->fspath->elem_missed;
		ipath->fspath->bytes_missing += fspath_min - fspath;
		ipath->fspath->bytes_left = 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * this dumps all file प्रणाली paths to the inode पूर्णांकo the ipath काष्ठा, provided
 * is has been created large enough. each path is zero-terminated and accessed
 * from ipath->fspath->val[i].
 * when it वापसs, there are ipath->fspath->elem_cnt number of paths available
 * in ipath->fspath->val[]. when the allocated space wasn't sufficient, the
 * number of missed paths is recorded in ipath->fspath->elem_missed, otherwise,
 * it's zero. ipath->fspath->bytes_missing holds the number of bytes that would
 * have been needed to वापस all paths.
 */
पूर्णांक paths_from_inode(u64 inum, काष्ठा inode_fs_paths *ipath)
अणु
	वापस iterate_irefs(inum, ipath->fs_root, ipath->btrfs_path,
			     inode_to_path, ipath);
पूर्ण

काष्ठा btrfs_data_container *init_data_container(u32 total_bytes)
अणु
	काष्ठा btrfs_data_container *data;
	माप_प्रकार alloc_bytes;

	alloc_bytes = max_t(माप_प्रकार, total_bytes, माप(*data));
	data = kvदो_स्मृति(alloc_bytes, GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	अगर (total_bytes >= माप(*data)) अणु
		data->bytes_left = total_bytes - माप(*data);
		data->bytes_missing = 0;
	पूर्ण अन्यथा अणु
		data->bytes_missing = माप(*data) - total_bytes;
		data->bytes_left = 0;
	पूर्ण

	data->elem_cnt = 0;
	data->elem_missed = 0;

	वापस data;
पूर्ण

/*
 * allocates space to वापस multiple file प्रणाली paths क्रम an inode.
 * total_bytes to allocate are passed, note that space usable क्रम actual path
 * inक्रमmation will be total_bytes - माप(काष्ठा inode_fs_paths).
 * the वापसed poपूर्णांकer must be मुक्तd with मुक्त_ipath() in the end.
 */
काष्ठा inode_fs_paths *init_ipath(s32 total_bytes, काष्ठा btrfs_root *fs_root,
					काष्ठा btrfs_path *path)
अणु
	काष्ठा inode_fs_paths *अगरp;
	काष्ठा btrfs_data_container *fspath;

	fspath = init_data_container(total_bytes);
	अगर (IS_ERR(fspath))
		वापस ERR_CAST(fspath);

	अगरp = kदो_स्मृति(माप(*अगरp), GFP_KERNEL);
	अगर (!अगरp) अणु
		kvमुक्त(fspath);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगरp->btrfs_path = path;
	अगरp->fspath = fspath;
	अगरp->fs_root = fs_root;

	वापस अगरp;
पूर्ण

व्योम मुक्त_ipath(काष्ठा inode_fs_paths *ipath)
अणु
	अगर (!ipath)
		वापस;
	kvमुक्त(ipath->fspath);
	kमुक्त(ipath);
पूर्ण

काष्ठा btrfs_backref_iter *btrfs_backref_iter_alloc(
		काष्ठा btrfs_fs_info *fs_info, gfp_t gfp_flag)
अणु
	काष्ठा btrfs_backref_iter *ret;

	ret = kzalloc(माप(*ret), gfp_flag);
	अगर (!ret)
		वापस शून्य;

	ret->path = btrfs_alloc_path();
	अगर (!ret->path) अणु
		kमुक्त(ret);
		वापस शून्य;
	पूर्ण

	/* Current backref iterator only supports iteration in commit root */
	ret->path->search_commit_root = 1;
	ret->path->skip_locking = 1;
	ret->fs_info = fs_info;

	वापस ret;
पूर्ण

पूर्णांक btrfs_backref_iter_start(काष्ठा btrfs_backref_iter *iter, u64 bytenr)
अणु
	काष्ठा btrfs_fs_info *fs_info = iter->fs_info;
	काष्ठा btrfs_path *path = iter->path;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	key.objectid = bytenr;
	key.type = BTRFS_METADATA_ITEM_KEY;
	key.offset = (u64)-1;
	iter->bytenr = bytenr;

	ret = btrfs_search_slot(शून्य, fs_info->extent_root, &key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0) अणु
		ret = -EUCLEAN;
		जाओ release;
	पूर्ण
	अगर (path->slots[0] == 0) अणु
		WARN_ON(IS_ENABLED(CONFIG_BTRFS_DEBUG));
		ret = -EUCLEAN;
		जाओ release;
	पूर्ण
	path->slots[0]--;

	btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
	अगर ((key.type != BTRFS_EXTENT_ITEM_KEY &&
	     key.type != BTRFS_METADATA_ITEM_KEY) || key.objectid != bytenr) अणु
		ret = -ENOENT;
		जाओ release;
	पूर्ण
	स_नकल(&iter->cur_key, &key, माप(key));
	iter->item_ptr = (u32)btrfs_item_ptr_offset(path->nodes[0],
						    path->slots[0]);
	iter->end_ptr = (u32)(iter->item_ptr +
			btrfs_item_size_nr(path->nodes[0], path->slots[0]));
	ei = btrfs_item_ptr(path->nodes[0], path->slots[0],
			    काष्ठा btrfs_extent_item);

	/*
	 * Only support iteration on tree backref yet.
	 *
	 * This is an extra precaution क्रम non skinny-metadata, where
	 * EXTENT_ITEM is also used क्रम tree blocks, that we can only use
	 * extent flags to determine अगर it's a tree block.
	 */
	अगर (btrfs_extent_flags(path->nodes[0], ei) & BTRFS_EXTENT_FLAG_DATA) अणु
		ret = -ENOTSUPP;
		जाओ release;
	पूर्ण
	iter->cur_ptr = (u32)(iter->item_ptr + माप(*ei));

	/* If there is no अंतरभूत backref, go search क्रम keyed backref */
	अगर (iter->cur_ptr >= iter->end_ptr) अणु
		ret = btrfs_next_item(fs_info->extent_root, path);

		/* No अंतरभूत nor keyed ref */
		अगर (ret > 0) अणु
			ret = -ENOENT;
			जाओ release;
		पूर्ण
		अगर (ret < 0)
			जाओ release;

		btrfs_item_key_to_cpu(path->nodes[0], &iter->cur_key,
				path->slots[0]);
		अगर (iter->cur_key.objectid != bytenr ||
		    (iter->cur_key.type != BTRFS_SHARED_BLOCK_REF_KEY &&
		     iter->cur_key.type != BTRFS_TREE_BLOCK_REF_KEY)) अणु
			ret = -ENOENT;
			जाओ release;
		पूर्ण
		iter->cur_ptr = (u32)btrfs_item_ptr_offset(path->nodes[0],
							   path->slots[0]);
		iter->item_ptr = iter->cur_ptr;
		iter->end_ptr = (u32)(iter->item_ptr + btrfs_item_size_nr(
				      path->nodes[0], path->slots[0]));
	पूर्ण

	वापस 0;
release:
	btrfs_backref_iter_release(iter);
	वापस ret;
पूर्ण

/*
 * Go to the next backref item of current bytenr, can be either अंतरभूतd or
 * keyed.
 *
 * Caller needs to check whether it's अंतरभूत ref or not by iter->cur_key.
 *
 * Return 0 अगर we get next backref without problem.
 * Return >0 अगर there is no extra backref क्रम this bytenr.
 * Return <0 अगर there is something wrong happened.
 */
पूर्णांक btrfs_backref_iter_next(काष्ठा btrfs_backref_iter *iter)
अणु
	काष्ठा extent_buffer *eb = btrfs_backref_get_eb(iter);
	काष्ठा btrfs_path *path = iter->path;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	पूर्णांक ret;
	u32 size;

	अगर (btrfs_backref_iter_is_अंतरभूत_ref(iter)) अणु
		/* We're still inside the अंतरभूत refs */
		ASSERT(iter->cur_ptr < iter->end_ptr);

		अगर (btrfs_backref_has_tree_block_info(iter)) अणु
			/* First tree block info */
			size = माप(काष्ठा btrfs_tree_block_info);
		पूर्ण अन्यथा अणु
			/* Use अंतरभूत ref type to determine the size */
			पूर्णांक type;

			iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)
				((अचिन्हित दीर्घ)iter->cur_ptr);
			type = btrfs_extent_अंतरभूत_ref_type(eb, iref);

			size = btrfs_extent_अंतरभूत_ref_size(type);
		पूर्ण
		iter->cur_ptr += size;
		अगर (iter->cur_ptr < iter->end_ptr)
			वापस 0;

		/* All अंतरभूत items iterated, fall through */
	पूर्ण

	/* We're at keyed items, there is no अंतरभूत item, go to the next one */
	ret = btrfs_next_item(iter->fs_info->extent_root, iter->path);
	अगर (ret)
		वापस ret;

	btrfs_item_key_to_cpu(path->nodes[0], &iter->cur_key, path->slots[0]);
	अगर (iter->cur_key.objectid != iter->bytenr ||
	    (iter->cur_key.type != BTRFS_TREE_BLOCK_REF_KEY &&
	     iter->cur_key.type != BTRFS_SHARED_BLOCK_REF_KEY))
		वापस 1;
	iter->item_ptr = (u32)btrfs_item_ptr_offset(path->nodes[0],
					path->slots[0]);
	iter->cur_ptr = iter->item_ptr;
	iter->end_ptr = iter->item_ptr + (u32)btrfs_item_size_nr(path->nodes[0],
						path->slots[0]);
	वापस 0;
पूर्ण

व्योम btrfs_backref_init_cache(काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा btrfs_backref_cache *cache, पूर्णांक is_reloc)
अणु
	पूर्णांक i;

	cache->rb_root = RB_ROOT;
	क्रम (i = 0; i < BTRFS_MAX_LEVEL; i++)
		INIT_LIST_HEAD(&cache->pending[i]);
	INIT_LIST_HEAD(&cache->changed);
	INIT_LIST_HEAD(&cache->detached);
	INIT_LIST_HEAD(&cache->leaves);
	INIT_LIST_HEAD(&cache->pending_edge);
	INIT_LIST_HEAD(&cache->useless_node);
	cache->fs_info = fs_info;
	cache->is_reloc = is_reloc;
पूर्ण

काष्ठा btrfs_backref_node *btrfs_backref_alloc_node(
		काष्ठा btrfs_backref_cache *cache, u64 bytenr, पूर्णांक level)
अणु
	काष्ठा btrfs_backref_node *node;

	ASSERT(level >= 0 && level < BTRFS_MAX_LEVEL);
	node = kzalloc(माप(*node), GFP_NOFS);
	अगर (!node)
		वापस node;

	INIT_LIST_HEAD(&node->list);
	INIT_LIST_HEAD(&node->upper);
	INIT_LIST_HEAD(&node->lower);
	RB_CLEAR_NODE(&node->rb_node);
	cache->nr_nodes++;
	node->level = level;
	node->bytenr = bytenr;

	वापस node;
पूर्ण

काष्ठा btrfs_backref_edge *btrfs_backref_alloc_edge(
		काष्ठा btrfs_backref_cache *cache)
अणु
	काष्ठा btrfs_backref_edge *edge;

	edge = kzalloc(माप(*edge), GFP_NOFS);
	अगर (edge)
		cache->nr_edges++;
	वापस edge;
पूर्ण

/*
 * Drop the backref node from cache, also cleaning up all its
 * upper edges and any uncached nodes in the path.
 *
 * This cleanup happens bottom up, thus the node should either
 * be the lowest node in the cache or a detached node.
 */
व्योम btrfs_backref_cleanup_node(काष्ठा btrfs_backref_cache *cache,
				काष्ठा btrfs_backref_node *node)
अणु
	काष्ठा btrfs_backref_node *upper;
	काष्ठा btrfs_backref_edge *edge;

	अगर (!node)
		वापस;

	BUG_ON(!node->lowest && !node->detached);
	जबतक (!list_empty(&node->upper)) अणु
		edge = list_entry(node->upper.next, काष्ठा btrfs_backref_edge,
				  list[LOWER]);
		upper = edge->node[UPPER];
		list_del(&edge->list[LOWER]);
		list_del(&edge->list[UPPER]);
		btrfs_backref_मुक्त_edge(cache, edge);

		/*
		 * Add the node to leaf node list अगर no other child block
		 * cached.
		 */
		अगर (list_empty(&upper->lower)) अणु
			list_add_tail(&upper->lower, &cache->leaves);
			upper->lowest = 1;
		पूर्ण
	पूर्ण

	btrfs_backref_drop_node(cache, node);
पूर्ण

/*
 * Release all nodes/edges from current cache
 */
व्योम btrfs_backref_release_cache(काष्ठा btrfs_backref_cache *cache)
अणु
	काष्ठा btrfs_backref_node *node;
	पूर्णांक i;

	जबतक (!list_empty(&cache->detached)) अणु
		node = list_entry(cache->detached.next,
				  काष्ठा btrfs_backref_node, list);
		btrfs_backref_cleanup_node(cache, node);
	पूर्ण

	जबतक (!list_empty(&cache->leaves)) अणु
		node = list_entry(cache->leaves.next,
				  काष्ठा btrfs_backref_node, lower);
		btrfs_backref_cleanup_node(cache, node);
	पूर्ण

	cache->last_trans = 0;

	क्रम (i = 0; i < BTRFS_MAX_LEVEL; i++)
		ASSERT(list_empty(&cache->pending[i]));
	ASSERT(list_empty(&cache->pending_edge));
	ASSERT(list_empty(&cache->useless_node));
	ASSERT(list_empty(&cache->changed));
	ASSERT(list_empty(&cache->detached));
	ASSERT(RB_EMPTY_ROOT(&cache->rb_root));
	ASSERT(!cache->nr_nodes);
	ASSERT(!cache->nr_edges);
पूर्ण

/*
 * Handle direct tree backref
 *
 * Direct tree backref means, the backref item shows its parent bytenr
 * directly. This is क्रम SHARED_BLOCK_REF backref (keyed or अंतरभूतd).
 *
 * @ref_key:	The converted backref key.
 *		For keyed backref, it's the item key.
 *		For अंतरभूतd backref, objectid is the bytenr,
 *		type is btrfs_अंतरभूत_ref_type, offset is
 *		btrfs_अंतरभूत_ref_offset.
 */
अटल पूर्णांक handle_direct_tree_backref(काष्ठा btrfs_backref_cache *cache,
				      काष्ठा btrfs_key *ref_key,
				      काष्ठा btrfs_backref_node *cur)
अणु
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा btrfs_backref_node *upper;
	काष्ठा rb_node *rb_node;

	ASSERT(ref_key->type == BTRFS_SHARED_BLOCK_REF_KEY);

	/* Only reloc root uses backref poपूर्णांकing to itself */
	अगर (ref_key->objectid == ref_key->offset) अणु
		काष्ठा btrfs_root *root;

		cur->is_reloc_root = 1;
		/* Only reloc backref cache cares about a specअगरic root */
		अगर (cache->is_reloc) अणु
			root = find_reloc_root(cache->fs_info, cur->bytenr);
			अगर (!root)
				वापस -ENOENT;
			cur->root = root;
		पूर्ण अन्यथा अणु
			/*
			 * For generic purpose backref cache, reloc root node
			 * is useless.
			 */
			list_add(&cur->list, &cache->useless_node);
		पूर्ण
		वापस 0;
	पूर्ण

	edge = btrfs_backref_alloc_edge(cache);
	अगर (!edge)
		वापस -ENOMEM;

	rb_node = rb_simple_search(&cache->rb_root, ref_key->offset);
	अगर (!rb_node) अणु
		/* Parent node not yet cached */
		upper = btrfs_backref_alloc_node(cache, ref_key->offset,
					   cur->level + 1);
		अगर (!upper) अणु
			btrfs_backref_मुक्त_edge(cache, edge);
			वापस -ENOMEM;
		पूर्ण

		/*
		 *  Backrefs क्रम the upper level block isn't cached, add the
		 *  block to pending list
		 */
		list_add_tail(&edge->list[UPPER], &cache->pending_edge);
	पूर्ण अन्यथा अणु
		/* Parent node alपढ़ोy cached */
		upper = rb_entry(rb_node, काष्ठा btrfs_backref_node, rb_node);
		ASSERT(upper->checked);
		INIT_LIST_HEAD(&edge->list[UPPER]);
	पूर्ण
	btrfs_backref_link_edge(edge, cur, upper, LINK_LOWER);
	वापस 0;
पूर्ण

/*
 * Handle indirect tree backref
 *
 * Indirect tree backref means, we only know which tree the node beदीर्घs to.
 * We still need to करो a tree search to find out the parents. This is क्रम
 * TREE_BLOCK_REF backref (keyed or अंतरभूतd).
 *
 * @ref_key:	The same as @ref_key in  handle_direct_tree_backref()
 * @tree_key:	The first key of this tree block.
 * @path:	A clean (released) path, to aव्योम allocating path everyसमय
 *		the function get called.
 */
अटल पूर्णांक handle_indirect_tree_backref(काष्ठा btrfs_backref_cache *cache,
					काष्ठा btrfs_path *path,
					काष्ठा btrfs_key *ref_key,
					काष्ठा btrfs_key *tree_key,
					काष्ठा btrfs_backref_node *cur)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा btrfs_backref_node *upper;
	काष्ठा btrfs_backref_node *lower;
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_root *root;
	काष्ठा rb_node *rb_node;
	पूर्णांक level;
	bool need_check = true;
	पूर्णांक ret;

	root = btrfs_get_fs_root(fs_info, ref_key->offset, false);
	अगर (IS_ERR(root))
		वापस PTR_ERR(root);
	अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
		cur->cowonly = 1;

	अगर (btrfs_root_level(&root->root_item) == cur->level) अणु
		/* Tree root */
		ASSERT(btrfs_root_bytenr(&root->root_item) == cur->bytenr);
		/*
		 * For reloc backref cache, we may ignore reloc root.  But क्रम
		 * general purpose backref cache, we can't rely on
		 * btrfs_should_ignore_reloc_root() as it may conflict with
		 * current running relocation and lead to missing root.
		 *
		 * For general purpose backref cache, reloc root detection is
		 * completely relying on direct backref (key->offset is parent
		 * bytenr), thus only करो such check क्रम reloc cache.
		 */
		अगर (btrfs_should_ignore_reloc_root(root) && cache->is_reloc) अणु
			btrfs_put_root(root);
			list_add(&cur->list, &cache->useless_node);
		पूर्ण अन्यथा अणु
			cur->root = root;
		पूर्ण
		वापस 0;
	पूर्ण

	level = cur->level + 1;

	/* Search the tree to find parent blocks referring to the block */
	path->search_commit_root = 1;
	path->skip_locking = 1;
	path->lowest_level = level;
	ret = btrfs_search_slot(शून्य, root, tree_key, path, 0, 0);
	path->lowest_level = 0;
	अगर (ret < 0) अणु
		btrfs_put_root(root);
		वापस ret;
	पूर्ण
	अगर (ret > 0 && path->slots[level] > 0)
		path->slots[level]--;

	eb = path->nodes[level];
	अगर (btrfs_node_blockptr(eb, path->slots[level]) != cur->bytenr) अणु
		btrfs_err(fs_info,
"couldn't find block (%llu) (level %d) in tree (%llu) with key (%llu %u %llu)",
			  cur->bytenr, level - 1, root->root_key.objectid,
			  tree_key->objectid, tree_key->type, tree_key->offset);
		btrfs_put_root(root);
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	lower = cur;

	/* Add all nodes and edges in the path */
	क्रम (; level < BTRFS_MAX_LEVEL; level++) अणु
		अगर (!path->nodes[level]) अणु
			ASSERT(btrfs_root_bytenr(&root->root_item) ==
			       lower->bytenr);
			/* Same as previous should_ignore_reloc_root() call */
			अगर (btrfs_should_ignore_reloc_root(root) &&
			    cache->is_reloc) अणु
				btrfs_put_root(root);
				list_add(&lower->list, &cache->useless_node);
			पूर्ण अन्यथा अणु
				lower->root = root;
			पूर्ण
			अवरोध;
		पूर्ण

		edge = btrfs_backref_alloc_edge(cache);
		अगर (!edge) अणु
			btrfs_put_root(root);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		eb = path->nodes[level];
		rb_node = rb_simple_search(&cache->rb_root, eb->start);
		अगर (!rb_node) अणु
			upper = btrfs_backref_alloc_node(cache, eb->start,
							 lower->level + 1);
			अगर (!upper) अणु
				btrfs_put_root(root);
				btrfs_backref_मुक्त_edge(cache, edge);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			upper->owner = btrfs_header_owner(eb);
			अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
				upper->cowonly = 1;

			/*
			 * If we know the block isn't shared we can aव्योम
			 * checking its backrefs.
			 */
			अगर (btrfs_block_can_be_shared(root, eb))
				upper->checked = 0;
			अन्यथा
				upper->checked = 1;

			/*
			 * Add the block to pending list अगर we need to check its
			 * backrefs, we only करो this once जबतक walking up a
			 * tree as we will catch anything अन्यथा later on.
			 */
			अगर (!upper->checked && need_check) अणु
				need_check = false;
				list_add_tail(&edge->list[UPPER],
					      &cache->pending_edge);
			पूर्ण अन्यथा अणु
				अगर (upper->checked)
					need_check = true;
				INIT_LIST_HEAD(&edge->list[UPPER]);
			पूर्ण
		पूर्ण अन्यथा अणु
			upper = rb_entry(rb_node, काष्ठा btrfs_backref_node,
					 rb_node);
			ASSERT(upper->checked);
			INIT_LIST_HEAD(&edge->list[UPPER]);
			अगर (!upper->owner)
				upper->owner = btrfs_header_owner(eb);
		पूर्ण
		btrfs_backref_link_edge(edge, lower, upper, LINK_LOWER);

		अगर (rb_node) अणु
			btrfs_put_root(root);
			अवरोध;
		पूर्ण
		lower = upper;
		upper = शून्य;
	पूर्ण
out:
	btrfs_release_path(path);
	वापस ret;
पूर्ण

/*
 * Add backref node @cur पूर्णांकo @cache.
 *
 * NOTE: Even अगर the function वापसed 0, @cur is not yet cached as its upper
 *	 links aren't yet bi-directional. Needs to finish such links.
 *	 Use btrfs_backref_finish_upper_links() to finish such linkage.
 *
 * @path:	Released path क्रम indirect tree backref lookup
 * @iter:	Released backref iter क्रम extent tree search
 * @node_key:	The first key of the tree block
 */
पूर्णांक btrfs_backref_add_tree_node(काष्ठा btrfs_backref_cache *cache,
				काष्ठा btrfs_path *path,
				काष्ठा btrfs_backref_iter *iter,
				काष्ठा btrfs_key *node_key,
				काष्ठा btrfs_backref_node *cur)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा btrfs_backref_node *exist;
	पूर्णांक ret;

	ret = btrfs_backref_iter_start(iter, cur->bytenr);
	अगर (ret < 0)
		वापस ret;
	/*
	 * We skip the first btrfs_tree_block_info, as we करोn't use the key
	 * stored in it, but fetch it from the tree block
	 */
	अगर (btrfs_backref_has_tree_block_info(iter)) अणु
		ret = btrfs_backref_iter_next(iter);
		अगर (ret < 0)
			जाओ out;
		/* No extra backref? This means the tree block is corrupted */
		अगर (ret > 0) अणु
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
	पूर्ण
	WARN_ON(cur->checked);
	अगर (!list_empty(&cur->upper)) अणु
		/*
		 * The backref was added previously when processing backref of
		 * type BTRFS_TREE_BLOCK_REF_KEY
		 */
		ASSERT(list_is_singular(&cur->upper));
		edge = list_entry(cur->upper.next, काष्ठा btrfs_backref_edge,
				  list[LOWER]);
		ASSERT(list_empty(&edge->list[UPPER]));
		exist = edge->node[UPPER];
		/*
		 * Add the upper level block to pending list अगर we need check
		 * its backrefs
		 */
		अगर (!exist->checked)
			list_add_tail(&edge->list[UPPER], &cache->pending_edge);
	पूर्ण अन्यथा अणु
		exist = शून्य;
	पूर्ण

	क्रम (; ret == 0; ret = btrfs_backref_iter_next(iter)) अणु
		काष्ठा extent_buffer *eb;
		काष्ठा btrfs_key key;
		पूर्णांक type;

		cond_resched();
		eb = btrfs_backref_get_eb(iter);

		key.objectid = iter->bytenr;
		अगर (btrfs_backref_iter_is_अंतरभूत_ref(iter)) अणु
			काष्ठा btrfs_extent_अंतरभूत_ref *iref;

			/* Update key क्रम अंतरभूत backref */
			iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)
				((अचिन्हित दीर्घ)iter->cur_ptr);
			type = btrfs_get_extent_अंतरभूत_ref_type(eb, iref,
							BTRFS_REF_TYPE_BLOCK);
			अगर (type == BTRFS_REF_TYPE_INVALID) अणु
				ret = -EUCLEAN;
				जाओ out;
			पूर्ण
			key.type = type;
			key.offset = btrfs_extent_अंतरभूत_ref_offset(eb, iref);
		पूर्ण अन्यथा अणु
			key.type = iter->cur_key.type;
			key.offset = iter->cur_key.offset;
		पूर्ण

		/*
		 * Parent node found and matches current अंतरभूत ref, no need to
		 * rebuild this node क्रम this अंतरभूत ref
		 */
		अगर (exist &&
		    ((key.type == BTRFS_TREE_BLOCK_REF_KEY &&
		      exist->owner == key.offset) ||
		     (key.type == BTRFS_SHARED_BLOCK_REF_KEY &&
		      exist->bytenr == key.offset))) अणु
			exist = शून्य;
			जारी;
		पूर्ण

		/* SHARED_BLOCK_REF means key.offset is the parent bytenr */
		अगर (key.type == BTRFS_SHARED_BLOCK_REF_KEY) अणु
			ret = handle_direct_tree_backref(cache, &key, cur);
			अगर (ret < 0)
				जाओ out;
			जारी;
		पूर्ण अन्यथा अगर (unlikely(key.type == BTRFS_EXTENT_REF_V0_KEY)) अणु
			ret = -EINVAL;
			btrfs_prपूर्णांक_v0_err(fs_info);
			btrfs_handle_fs_error(fs_info, ret, शून्य);
			जाओ out;
		पूर्ण अन्यथा अगर (key.type != BTRFS_TREE_BLOCK_REF_KEY) अणु
			जारी;
		पूर्ण

		/*
		 * key.type == BTRFS_TREE_BLOCK_REF_KEY, अंतरभूत ref offset
		 * means the root objectid. We need to search the tree to get
		 * its parent bytenr.
		 */
		ret = handle_indirect_tree_backref(cache, path, &key, node_key,
						   cur);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
	ret = 0;
	cur->checked = 1;
	WARN_ON(exist);
out:
	btrfs_backref_iter_release(iter);
	वापस ret;
पूर्ण

/*
 * Finish the upwards linkage created by btrfs_backref_add_tree_node()
 */
पूर्णांक btrfs_backref_finish_upper_links(काष्ठा btrfs_backref_cache *cache,
				     काष्ठा btrfs_backref_node *start)
अणु
	काष्ठा list_head *useless_node = &cache->useless_node;
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा rb_node *rb_node;
	LIST_HEAD(pending_edge);

	ASSERT(start->checked);

	/* Insert this node to cache अगर it's not COW-only */
	अगर (!start->cowonly) अणु
		rb_node = rb_simple_insert(&cache->rb_root, start->bytenr,
					   &start->rb_node);
		अगर (rb_node)
			btrfs_backref_panic(cache->fs_info, start->bytenr,
					    -EEXIST);
		list_add_tail(&start->lower, &cache->leaves);
	पूर्ण

	/*
	 * Use bपढ़ोth first search to iterate all related edges.
	 *
	 * The starting poपूर्णांकs are all the edges of this node
	 */
	list_क्रम_each_entry(edge, &start->upper, list[LOWER])
		list_add_tail(&edge->list[UPPER], &pending_edge);

	जबतक (!list_empty(&pending_edge)) अणु
		काष्ठा btrfs_backref_node *upper;
		काष्ठा btrfs_backref_node *lower;

		edge = list_first_entry(&pending_edge,
				काष्ठा btrfs_backref_edge, list[UPPER]);
		list_del_init(&edge->list[UPPER]);
		upper = edge->node[UPPER];
		lower = edge->node[LOWER];

		/* Parent is detached, no need to keep any edges */
		अगर (upper->detached) अणु
			list_del(&edge->list[LOWER]);
			btrfs_backref_मुक्त_edge(cache, edge);

			/* Lower node is orphan, queue क्रम cleanup */
			अगर (list_empty(&lower->upper))
				list_add(&lower->list, useless_node);
			जारी;
		पूर्ण

		/*
		 * All new nodes added in current build_backref_tree() haven't
		 * been linked to the cache rb tree.
		 * So अगर we have upper->rb_node populated, this means a cache
		 * hit. We only need to link the edge, as @upper and all its
		 * parents have alपढ़ोy been linked.
		 */
		अगर (!RB_EMPTY_NODE(&upper->rb_node)) अणु
			अगर (upper->lowest) अणु
				list_del_init(&upper->lower);
				upper->lowest = 0;
			पूर्ण

			list_add_tail(&edge->list[UPPER], &upper->lower);
			जारी;
		पूर्ण

		/* Sanity check, we shouldn't have any unchecked nodes */
		अगर (!upper->checked) अणु
			ASSERT(0);
			वापस -EUCLEAN;
		पूर्ण

		/* Sanity check, COW-only node has non-COW-only parent */
		अगर (start->cowonly != upper->cowonly) अणु
			ASSERT(0);
			वापस -EUCLEAN;
		पूर्ण

		/* Only cache non-COW-only (subvolume trees) tree blocks */
		अगर (!upper->cowonly) अणु
			rb_node = rb_simple_insert(&cache->rb_root, upper->bytenr,
						   &upper->rb_node);
			अगर (rb_node) अणु
				btrfs_backref_panic(cache->fs_info,
						upper->bytenr, -EEXIST);
				वापस -EUCLEAN;
			पूर्ण
		पूर्ण

		list_add_tail(&edge->list[UPPER], &upper->lower);

		/*
		 * Also queue all the parent edges of this uncached node
		 * to finish the upper linkage
		 */
		list_क्रम_each_entry(edge, &upper->upper, list[LOWER])
			list_add_tail(&edge->list[UPPER], &pending_edge);
	पूर्ण
	वापस 0;
पूर्ण

व्योम btrfs_backref_error_cleanup(काष्ठा btrfs_backref_cache *cache,
				 काष्ठा btrfs_backref_node *node)
अणु
	काष्ठा btrfs_backref_node *lower;
	काष्ठा btrfs_backref_node *upper;
	काष्ठा btrfs_backref_edge *edge;

	जबतक (!list_empty(&cache->useless_node)) अणु
		lower = list_first_entry(&cache->useless_node,
				   काष्ठा btrfs_backref_node, list);
		list_del_init(&lower->list);
	पूर्ण
	जबतक (!list_empty(&cache->pending_edge)) अणु
		edge = list_first_entry(&cache->pending_edge,
				काष्ठा btrfs_backref_edge, list[UPPER]);
		list_del(&edge->list[UPPER]);
		list_del(&edge->list[LOWER]);
		lower = edge->node[LOWER];
		upper = edge->node[UPPER];
		btrfs_backref_मुक्त_edge(cache, edge);

		/*
		 * Lower is no दीर्घer linked to any upper backref nodes and
		 * isn't in the cache, we can मुक्त it ourselves.
		 */
		अगर (list_empty(&lower->upper) &&
		    RB_EMPTY_NODE(&lower->rb_node))
			list_add(&lower->list, &cache->useless_node);

		अगर (!RB_EMPTY_NODE(&upper->rb_node))
			जारी;

		/* Add this guy's upper edges to the list to process */
		list_क्रम_each_entry(edge, &upper->upper, list[LOWER])
			list_add_tail(&edge->list[UPPER],
				      &cache->pending_edge);
		अगर (list_empty(&upper->upper))
			list_add(&upper->list, &cache->useless_node);
	पूर्ण

	जबतक (!list_empty(&cache->useless_node)) अणु
		lower = list_first_entry(&cache->useless_node,
				   काष्ठा btrfs_backref_node, list);
		list_del_init(&lower->list);
		अगर (lower == node)
			node = शून्य;
		btrfs_backref_drop_node(cache, lower);
	पूर्ण

	btrfs_backref_cleanup_node(cache, node);
	ASSERT(list_empty(&cache->useless_node) &&
	       list_empty(&cache->pending_edge));
पूर्ण
