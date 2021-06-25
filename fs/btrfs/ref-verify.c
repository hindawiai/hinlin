<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Facebook.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/stacktrace.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "locking.h"
#समावेश "delayed-ref.h"
#समावेश "ref-verify.h"

/*
 * Used to keep track the roots and number of refs each root has क्रम a given
 * bytenr.  This just tracks the number of direct references, no shared
 * references.
 */
काष्ठा root_entry अणु
	u64 root_objectid;
	u64 num_refs;
	काष्ठा rb_node node;
पूर्ण;

/*
 * These are meant to represent what should exist in the extent tree, these can
 * be used to verअगरy the extent tree is consistent as these should all match
 * what the extent tree says.
 */
काष्ठा ref_entry अणु
	u64 root_objectid;
	u64 parent;
	u64 owner;
	u64 offset;
	u64 num_refs;
	काष्ठा rb_node node;
पूर्ण;

#घोषणा MAX_TRACE	16

/*
 * Whenever we add/हटाओ a reference we record the action.  The action maps
 * back to the delayed ref action.  We hold the ref we are changing in the
 * action so we can account क्रम the history properly, and we record the root we
 * were called with since it could be dअगरferent from ref_root.  We also store
 * stack traces because that's how I roll.
 */
काष्ठा ref_action अणु
	पूर्णांक action;
	u64 root;
	काष्ठा ref_entry ref;
	काष्ठा list_head list;
	अचिन्हित दीर्घ trace[MAX_TRACE];
	अचिन्हित पूर्णांक trace_len;
पूर्ण;

/*
 * One of these क्रम every block we reference, it holds the roots and references
 * to it as well as all of the ref actions that have occurred to it.  We never
 * मुक्त it until we unmount the file प्रणाली in order to make sure re-allocations
 * are happening properly.
 */
काष्ठा block_entry अणु
	u64 bytenr;
	u64 len;
	u64 num_refs;
	पूर्णांक metadata;
	पूर्णांक from_disk;
	काष्ठा rb_root roots;
	काष्ठा rb_root refs;
	काष्ठा rb_node node;
	काष्ठा list_head actions;
पूर्ण;

अटल काष्ठा block_entry *insert_block_entry(काष्ठा rb_root *root,
					      काष्ठा block_entry *be)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent_node = शून्य;
	काष्ठा block_entry *entry;

	जबतक (*p) अणु
		parent_node = *p;
		entry = rb_entry(parent_node, काष्ठा block_entry, node);
		अगर (entry->bytenr > be->bytenr)
			p = &(*p)->rb_left;
		अन्यथा अगर (entry->bytenr < be->bytenr)
			p = &(*p)->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण

	rb_link_node(&be->node, parent_node, p);
	rb_insert_color(&be->node, root);
	वापस शून्य;
पूर्ण

अटल काष्ठा block_entry *lookup_block_entry(काष्ठा rb_root *root, u64 bytenr)
अणु
	काष्ठा rb_node *n;
	काष्ठा block_entry *entry = शून्य;

	n = root->rb_node;
	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा block_entry, node);
		अगर (entry->bytenr < bytenr)
			n = n->rb_right;
		अन्यथा अगर (entry->bytenr > bytenr)
			n = n->rb_left;
		अन्यथा
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा root_entry *insert_root_entry(काष्ठा rb_root *root,
					    काष्ठा root_entry *re)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent_node = शून्य;
	काष्ठा root_entry *entry;

	जबतक (*p) अणु
		parent_node = *p;
		entry = rb_entry(parent_node, काष्ठा root_entry, node);
		अगर (entry->root_objectid > re->root_objectid)
			p = &(*p)->rb_left;
		अन्यथा अगर (entry->root_objectid < re->root_objectid)
			p = &(*p)->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण

	rb_link_node(&re->node, parent_node, p);
	rb_insert_color(&re->node, root);
	वापस शून्य;

पूर्ण

अटल पूर्णांक comp_refs(काष्ठा ref_entry *ref1, काष्ठा ref_entry *ref2)
अणु
	अगर (ref1->root_objectid < ref2->root_objectid)
		वापस -1;
	अगर (ref1->root_objectid > ref2->root_objectid)
		वापस 1;
	अगर (ref1->parent < ref2->parent)
		वापस -1;
	अगर (ref1->parent > ref2->parent)
		वापस 1;
	अगर (ref1->owner < ref2->owner)
		वापस -1;
	अगर (ref1->owner > ref2->owner)
		वापस 1;
	अगर (ref1->offset < ref2->offset)
		वापस -1;
	अगर (ref1->offset > ref2->offset)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा ref_entry *insert_ref_entry(काष्ठा rb_root *root,
					  काष्ठा ref_entry *ref)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent_node = शून्य;
	काष्ठा ref_entry *entry;
	पूर्णांक cmp;

	जबतक (*p) अणु
		parent_node = *p;
		entry = rb_entry(parent_node, काष्ठा ref_entry, node);
		cmp = comp_refs(entry, ref);
		अगर (cmp > 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (cmp < 0)
			p = &(*p)->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण

	rb_link_node(&ref->node, parent_node, p);
	rb_insert_color(&ref->node, root);
	वापस शून्य;

पूर्ण

अटल काष्ठा root_entry *lookup_root_entry(काष्ठा rb_root *root, u64 objectid)
अणु
	काष्ठा rb_node *n;
	काष्ठा root_entry *entry = शून्य;

	n = root->rb_node;
	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा root_entry, node);
		अगर (entry->root_objectid < objectid)
			n = n->rb_right;
		अन्यथा अगर (entry->root_objectid > objectid)
			n = n->rb_left;
		अन्यथा
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE
अटल व्योम __save_stack_trace(काष्ठा ref_action *ra)
अणु
	ra->trace_len = stack_trace_save(ra->trace, MAX_TRACE, 2);
पूर्ण

अटल व्योम __prपूर्णांक_stack_trace(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा ref_action *ra)
अणु
	अगर (ra->trace_len == 0) अणु
		btrfs_err(fs_info, "  ref-verify: no stacktrace");
		वापस;
	पूर्ण
	stack_trace_prपूर्णांक(ra->trace, ra->trace_len, 2);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __save_stack_trace(काष्ठा ref_action *ra)
अणु
पूर्ण

अटल अंतरभूत व्योम __prपूर्णांक_stack_trace(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा ref_action *ra)
अणु
	btrfs_err(fs_info, "  ref-verify: no stacktrace support");
पूर्ण
#पूर्ण_अगर

अटल व्योम मुक्त_block_entry(काष्ठा block_entry *be)
अणु
	काष्ठा root_entry *re;
	काष्ठा ref_entry *ref;
	काष्ठा ref_action *ra;
	काष्ठा rb_node *n;

	जबतक ((n = rb_first(&be->roots))) अणु
		re = rb_entry(n, काष्ठा root_entry, node);
		rb_erase(&re->node, &be->roots);
		kमुक्त(re);
	पूर्ण

	जबतक((n = rb_first(&be->refs))) अणु
		ref = rb_entry(n, काष्ठा ref_entry, node);
		rb_erase(&ref->node, &be->refs);
		kमुक्त(ref);
	पूर्ण

	जबतक (!list_empty(&be->actions)) अणु
		ra = list_first_entry(&be->actions, काष्ठा ref_action,
				      list);
		list_del(&ra->list);
		kमुक्त(ra);
	पूर्ण
	kमुक्त(be);
पूर्ण

अटल काष्ठा block_entry *add_block_entry(काष्ठा btrfs_fs_info *fs_info,
					   u64 bytenr, u64 len,
					   u64 root_objectid)
अणु
	काष्ठा block_entry *be = शून्य, *exist;
	काष्ठा root_entry *re = शून्य;

	re = kzalloc(माप(काष्ठा root_entry), GFP_KERNEL);
	be = kzalloc(माप(काष्ठा block_entry), GFP_KERNEL);
	अगर (!be || !re) अणु
		kमुक्त(re);
		kमुक्त(be);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	be->bytenr = bytenr;
	be->len = len;

	re->root_objectid = root_objectid;
	re->num_refs = 0;

	spin_lock(&fs_info->ref_verअगरy_lock);
	exist = insert_block_entry(&fs_info->block_tree, be);
	अगर (exist) अणु
		अगर (root_objectid) अणु
			काष्ठा root_entry *exist_re;

			exist_re = insert_root_entry(&exist->roots, re);
			अगर (exist_re)
				kमुक्त(re);
		पूर्ण अन्यथा अणु
			kमुक्त(re);
		पूर्ण
		kमुक्त(be);
		वापस exist;
	पूर्ण

	be->num_refs = 0;
	be->metadata = 0;
	be->from_disk = 0;
	be->roots = RB_ROOT;
	be->refs = RB_ROOT;
	INIT_LIST_HEAD(&be->actions);
	अगर (root_objectid)
		insert_root_entry(&be->roots, re);
	अन्यथा
		kमुक्त(re);
	वापस be;
पूर्ण

अटल पूर्णांक add_tree_block(काष्ठा btrfs_fs_info *fs_info, u64 ref_root,
			  u64 parent, u64 bytenr, पूर्णांक level)
अणु
	काष्ठा block_entry *be;
	काष्ठा root_entry *re;
	काष्ठा ref_entry *ref = शून्य, *exist;

	ref = kदो_स्मृति(माप(काष्ठा ref_entry), GFP_KERNEL);
	अगर (!ref)
		वापस -ENOMEM;

	अगर (parent)
		ref->root_objectid = 0;
	अन्यथा
		ref->root_objectid = ref_root;
	ref->parent = parent;
	ref->owner = level;
	ref->offset = 0;
	ref->num_refs = 1;

	be = add_block_entry(fs_info, bytenr, fs_info->nodesize, ref_root);
	अगर (IS_ERR(be)) अणु
		kमुक्त(ref);
		वापस PTR_ERR(be);
	पूर्ण
	be->num_refs++;
	be->from_disk = 1;
	be->metadata = 1;

	अगर (!parent) अणु
		ASSERT(ref_root);
		re = lookup_root_entry(&be->roots, ref_root);
		ASSERT(re);
		re->num_refs++;
	पूर्ण
	exist = insert_ref_entry(&be->refs, ref);
	अगर (exist) अणु
		exist->num_refs++;
		kमुक्त(ref);
	पूर्ण
	spin_unlock(&fs_info->ref_verअगरy_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक add_shared_data_ref(काष्ठा btrfs_fs_info *fs_info,
			       u64 parent, u32 num_refs, u64 bytenr,
			       u64 num_bytes)
अणु
	काष्ठा block_entry *be;
	काष्ठा ref_entry *ref;

	ref = kzalloc(माप(काष्ठा ref_entry), GFP_KERNEL);
	अगर (!ref)
		वापस -ENOMEM;
	be = add_block_entry(fs_info, bytenr, num_bytes, 0);
	अगर (IS_ERR(be)) अणु
		kमुक्त(ref);
		वापस PTR_ERR(be);
	पूर्ण
	be->num_refs += num_refs;

	ref->parent = parent;
	ref->num_refs = num_refs;
	अगर (insert_ref_entry(&be->refs, ref)) अणु
		spin_unlock(&fs_info->ref_verअगरy_lock);
		btrfs_err(fs_info, "existing shared ref when reading from disk?");
		kमुक्त(ref);
		वापस -EINVAL;
	पूर्ण
	spin_unlock(&fs_info->ref_verअगरy_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक add_extent_data_ref(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा extent_buffer *leaf,
			       काष्ठा btrfs_extent_data_ref *dref,
			       u64 bytenr, u64 num_bytes)
अणु
	काष्ठा block_entry *be;
	काष्ठा ref_entry *ref;
	काष्ठा root_entry *re;
	u64 ref_root = btrfs_extent_data_ref_root(leaf, dref);
	u64 owner = btrfs_extent_data_ref_objectid(leaf, dref);
	u64 offset = btrfs_extent_data_ref_offset(leaf, dref);
	u32 num_refs = btrfs_extent_data_ref_count(leaf, dref);

	ref = kzalloc(माप(काष्ठा ref_entry), GFP_KERNEL);
	अगर (!ref)
		वापस -ENOMEM;
	be = add_block_entry(fs_info, bytenr, num_bytes, ref_root);
	अगर (IS_ERR(be)) अणु
		kमुक्त(ref);
		वापस PTR_ERR(be);
	पूर्ण
	be->num_refs += num_refs;

	ref->parent = 0;
	ref->owner = owner;
	ref->root_objectid = ref_root;
	ref->offset = offset;
	ref->num_refs = num_refs;
	अगर (insert_ref_entry(&be->refs, ref)) अणु
		spin_unlock(&fs_info->ref_verअगरy_lock);
		btrfs_err(fs_info, "existing ref when reading from disk?");
		kमुक्त(ref);
		वापस -EINVAL;
	पूर्ण

	re = lookup_root_entry(&be->roots, ref_root);
	अगर (!re) अणु
		spin_unlock(&fs_info->ref_verअगरy_lock);
		btrfs_err(fs_info, "missing root in new block entry?");
		वापस -EINVAL;
	पूर्ण
	re->num_refs += num_refs;
	spin_unlock(&fs_info->ref_verअगरy_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक process_extent_item(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा btrfs_path *path, काष्ठा btrfs_key *key,
			       पूर्णांक slot, पूर्णांक *tree_block_level)
अणु
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_extent_अंतरभूत_ref *iref;
	काष्ठा btrfs_extent_data_ref *dref;
	काष्ठा btrfs_shared_data_ref *sref;
	काष्ठा extent_buffer *leaf = path->nodes[0];
	u32 item_size = btrfs_item_size_nr(leaf, slot);
	अचिन्हित दीर्घ end, ptr;
	u64 offset, flags, count;
	पूर्णांक type, ret;

	ei = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_extent_item);
	flags = btrfs_extent_flags(leaf, ei);

	अगर ((key->type == BTRFS_EXTENT_ITEM_KEY) &&
	    flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
		काष्ठा btrfs_tree_block_info *info;

		info = (काष्ठा btrfs_tree_block_info *)(ei + 1);
		*tree_block_level = btrfs_tree_block_level(leaf, info);
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(info + 1);
	पूर्ण अन्यथा अणु
		अगर (key->type == BTRFS_METADATA_ITEM_KEY)
			*tree_block_level = key->offset;
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)(ei + 1);
	पूर्ण

	ptr = (अचिन्हित दीर्घ)iref;
	end = (अचिन्हित दीर्घ)ei + item_size;
	जबतक (ptr < end) अणु
		iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)ptr;
		type = btrfs_extent_अंतरभूत_ref_type(leaf, iref);
		offset = btrfs_extent_अंतरभूत_ref_offset(leaf, iref);
		चयन (type) अणु
		हाल BTRFS_TREE_BLOCK_REF_KEY:
			ret = add_tree_block(fs_info, offset, 0, key->objectid,
					     *tree_block_level);
			अवरोध;
		हाल BTRFS_SHARED_BLOCK_REF_KEY:
			ret = add_tree_block(fs_info, 0, offset, key->objectid,
					     *tree_block_level);
			अवरोध;
		हाल BTRFS_EXTENT_DATA_REF_KEY:
			dref = (काष्ठा btrfs_extent_data_ref *)(&iref->offset);
			ret = add_extent_data_ref(fs_info, leaf, dref,
						  key->objectid, key->offset);
			अवरोध;
		हाल BTRFS_SHARED_DATA_REF_KEY:
			sref = (काष्ठा btrfs_shared_data_ref *)(iref + 1);
			count = btrfs_shared_data_ref_count(leaf, sref);
			ret = add_shared_data_ref(fs_info, offset, count,
						  key->objectid, key->offset);
			अवरोध;
		शेष:
			btrfs_err(fs_info, "invalid key type in iref");
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (ret)
			अवरोध;
		ptr += btrfs_extent_अंतरभूत_ref_size(type);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक process_leaf(काष्ठा btrfs_root *root,
			काष्ठा btrfs_path *path, u64 *bytenr, u64 *num_bytes,
			पूर्णांक *tree_block_level)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा extent_buffer *leaf = path->nodes[0];
	काष्ठा btrfs_extent_data_ref *dref;
	काष्ठा btrfs_shared_data_ref *sref;
	u32 count;
	पूर्णांक i = 0, ret = 0;
	काष्ठा btrfs_key key;
	पूर्णांक nritems = btrfs_header_nritems(leaf);

	क्रम (i = 0; i < nritems; i++) अणु
		btrfs_item_key_to_cpu(leaf, &key, i);
		चयन (key.type) अणु
		हाल BTRFS_EXTENT_ITEM_KEY:
			*num_bytes = key.offset;
			fallthrough;
		हाल BTRFS_METADATA_ITEM_KEY:
			*bytenr = key.objectid;
			ret = process_extent_item(fs_info, path, &key, i,
						  tree_block_level);
			अवरोध;
		हाल BTRFS_TREE_BLOCK_REF_KEY:
			ret = add_tree_block(fs_info, key.offset, 0,
					     key.objectid, *tree_block_level);
			अवरोध;
		हाल BTRFS_SHARED_BLOCK_REF_KEY:
			ret = add_tree_block(fs_info, 0, key.offset,
					     key.objectid, *tree_block_level);
			अवरोध;
		हाल BTRFS_EXTENT_DATA_REF_KEY:
			dref = btrfs_item_ptr(leaf, i,
					      काष्ठा btrfs_extent_data_ref);
			ret = add_extent_data_ref(fs_info, leaf, dref, *bytenr,
						  *num_bytes);
			अवरोध;
		हाल BTRFS_SHARED_DATA_REF_KEY:
			sref = btrfs_item_ptr(leaf, i,
					      काष्ठा btrfs_shared_data_ref);
			count = btrfs_shared_data_ref_count(leaf, sref);
			ret = add_shared_data_ref(fs_info, key.offset, count,
						  *bytenr, *num_bytes);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/* Walk करोwn to the leaf from the given level */
अटल पूर्णांक walk_करोwn_tree(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			  पूर्णांक level, u64 *bytenr, u64 *num_bytes,
			  पूर्णांक *tree_block_level)
अणु
	काष्ठा extent_buffer *eb;
	पूर्णांक ret = 0;

	जबतक (level >= 0) अणु
		अगर (level) अणु
			eb = btrfs_पढ़ो_node_slot(path->nodes[level],
						  path->slots[level]);
			अगर (IS_ERR(eb))
				वापस PTR_ERR(eb);
			btrfs_tree_पढ़ो_lock(eb);
			path->nodes[level-1] = eb;
			path->slots[level-1] = 0;
			path->locks[level-1] = BTRFS_READ_LOCK;
		पूर्ण अन्यथा अणु
			ret = process_leaf(root, path, bytenr, num_bytes,
					   tree_block_level);
			अगर (ret)
				अवरोध;
		पूर्ण
		level--;
	पूर्ण
	वापस ret;
पूर्ण

/* Walk up to the next node that needs to be processed */
अटल पूर्णांक walk_up_tree(काष्ठा btrfs_path *path, पूर्णांक *level)
अणु
	पूर्णांक l;

	क्रम (l = 0; l < BTRFS_MAX_LEVEL; l++) अणु
		अगर (!path->nodes[l])
			जारी;
		अगर (l) अणु
			path->slots[l]++;
			अगर (path->slots[l] <
			    btrfs_header_nritems(path->nodes[l])) अणु
				*level = l;
				वापस 0;
			पूर्ण
		पूर्ण
		btrfs_tree_unlock_rw(path->nodes[l], path->locks[l]);
		मुक्त_extent_buffer(path->nodes[l]);
		path->nodes[l] = शून्य;
		path->slots[l] = 0;
		path->locks[l] = 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम dump_ref_action(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा ref_action *ra)
अणु
	btrfs_err(fs_info,
"  Ref action %d, root %llu, ref_root %llu, parent %llu, owner %llu, offset %llu, num_refs %llu",
		  ra->action, ra->root, ra->ref.root_objectid, ra->ref.parent,
		  ra->ref.owner, ra->ref.offset, ra->ref.num_refs);
	__prपूर्णांक_stack_trace(fs_info, ra);
पूर्ण

/*
 * Dumps all the inक्रमmation from the block entry to prपूर्णांकk, it's going to be
 * awesome.
 */
अटल व्योम dump_block_entry(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा block_entry *be)
अणु
	काष्ठा ref_entry *ref;
	काष्ठा root_entry *re;
	काष्ठा ref_action *ra;
	काष्ठा rb_node *n;

	btrfs_err(fs_info,
"dumping block entry [%llu %llu], num_refs %llu, metadata %d, from disk %d",
		  be->bytenr, be->len, be->num_refs, be->metadata,
		  be->from_disk);

	क्रम (n = rb_first(&be->refs); n; n = rb_next(n)) अणु
		ref = rb_entry(n, काष्ठा ref_entry, node);
		btrfs_err(fs_info,
"  ref root %llu, parent %llu, owner %llu, offset %llu, num_refs %llu",
			  ref->root_objectid, ref->parent, ref->owner,
			  ref->offset, ref->num_refs);
	पूर्ण

	क्रम (n = rb_first(&be->roots); n; n = rb_next(n)) अणु
		re = rb_entry(n, काष्ठा root_entry, node);
		btrfs_err(fs_info, "  root entry %llu, num_refs %llu",
			  re->root_objectid, re->num_refs);
	पूर्ण

	list_क्रम_each_entry(ra, &be->actions, list)
		dump_ref_action(fs_info, ra);
पूर्ण

/*
 * btrfs_ref_tree_mod: called when we modअगरy a ref क्रम a bytenr
 *
 * This will add an action item to the given bytenr and करो sanity checks to make
 * sure we haven't messed something up.  If we are making a new allocation and
 * this block entry has history we will delete all previous actions as दीर्घ as
 * our sanity checks pass as they are no दीर्घer needed.
 */
पूर्णांक btrfs_ref_tree_mod(काष्ठा btrfs_fs_info *fs_info,
		       काष्ठा btrfs_ref *generic_ref)
अणु
	काष्ठा ref_entry *ref = शून्य, *exist;
	काष्ठा ref_action *ra = शून्य;
	काष्ठा block_entry *be = शून्य;
	काष्ठा root_entry *re = शून्य;
	पूर्णांक action = generic_ref->action;
	पूर्णांक ret = 0;
	bool metadata;
	u64 bytenr = generic_ref->bytenr;
	u64 num_bytes = generic_ref->len;
	u64 parent = generic_ref->parent;
	u64 ref_root = 0;
	u64 owner = 0;
	u64 offset = 0;

	अगर (!btrfs_test_opt(fs_info, REF_VERIFY))
		वापस 0;

	अगर (generic_ref->type == BTRFS_REF_METADATA) अणु
		अगर (!parent)
			ref_root = generic_ref->tree_ref.root;
		owner = generic_ref->tree_ref.level;
	पूर्ण अन्यथा अगर (!parent) अणु
		ref_root = generic_ref->data_ref.ref_root;
		owner = generic_ref->data_ref.ino;
		offset = generic_ref->data_ref.offset;
	पूर्ण
	metadata = owner < BTRFS_FIRST_FREE_OBJECTID;

	ref = kzalloc(माप(काष्ठा ref_entry), GFP_NOFS);
	ra = kदो_स्मृति(माप(काष्ठा ref_action), GFP_NOFS);
	अगर (!ra || !ref) अणु
		kमुक्त(ref);
		kमुक्त(ra);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ref->parent = parent;
	ref->owner = owner;
	ref->root_objectid = ref_root;
	ref->offset = offset;
	ref->num_refs = (action == BTRFS_DROP_DELAYED_REF) ? -1 : 1;

	स_नकल(&ra->ref, ref, माप(काष्ठा ref_entry));
	/*
	 * Save the extra info from the delayed ref in the ref action to make it
	 * easier to figure out what is happening.  The real ref's we add to the
	 * ref tree need to reflect what we save on disk so it matches any
	 * on-disk refs we pre-loaded.
	 */
	ra->ref.owner = owner;
	ra->ref.offset = offset;
	ra->ref.root_objectid = ref_root;
	__save_stack_trace(ra);

	INIT_LIST_HEAD(&ra->list);
	ra->action = action;
	ra->root = generic_ref->real_root;

	/*
	 * This is an allocation, pपुनः_स्मृतिate the block_entry in हाल we haven't
	 * used it beक्रमe.
	 */
	ret = -EINVAL;
	अगर (action == BTRFS_ADD_DELAYED_EXTENT) अणु
		/*
		 * For subvol_create we'll just pass in whatever the parent root
		 * is and the new root objectid, so let's not treat the passed
		 * in root as अगर it really has a ref क्रम this bytenr.
		 */
		be = add_block_entry(fs_info, bytenr, num_bytes, ref_root);
		अगर (IS_ERR(be)) अणु
			kमुक्त(ref);
			kमुक्त(ra);
			ret = PTR_ERR(be);
			जाओ out;
		पूर्ण
		be->num_refs++;
		अगर (metadata)
			be->metadata = 1;

		अगर (be->num_refs != 1) अणु
			btrfs_err(fs_info,
			"re-allocated a block that still has references to it!");
			dump_block_entry(fs_info, be);
			dump_ref_action(fs_info, ra);
			kमुक्त(ref);
			kमुक्त(ra);
			जाओ out_unlock;
		पूर्ण

		जबतक (!list_empty(&be->actions)) अणु
			काष्ठा ref_action *पंचांगp;

			पंचांगp = list_first_entry(&be->actions, काष्ठा ref_action,
					       list);
			list_del(&पंचांगp->list);
			kमुक्त(पंचांगp);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा root_entry *पंचांगp;

		अगर (!parent) अणु
			re = kदो_स्मृति(माप(काष्ठा root_entry), GFP_NOFS);
			अगर (!re) अणु
				kमुक्त(ref);
				kमुक्त(ra);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			/*
			 * This is the root that is modअगरying us, so it's the
			 * one we want to lookup below when we modअगरy the
			 * re->num_refs.
			 */
			ref_root = generic_ref->real_root;
			re->root_objectid = generic_ref->real_root;
			re->num_refs = 0;
		पूर्ण

		spin_lock(&fs_info->ref_verअगरy_lock);
		be = lookup_block_entry(&fs_info->block_tree, bytenr);
		अगर (!be) अणु
			btrfs_err(fs_info,
"trying to do action %d to bytenr %llu num_bytes %llu but there is no existing entry!",
				  action, bytenr, num_bytes);
			dump_ref_action(fs_info, ra);
			kमुक्त(ref);
			kमुक्त(ra);
			जाओ out_unlock;
		पूर्ण अन्यथा अगर (be->num_refs == 0) अणु
			btrfs_err(fs_info,
		"trying to do action %d for a bytenr that has 0 total references",
				action);
			dump_block_entry(fs_info, be);
			dump_ref_action(fs_info, ra);
			kमुक्त(ref);
			kमुक्त(ra);
			जाओ out_unlock;
		पूर्ण

		अगर (!parent) अणु
			पंचांगp = insert_root_entry(&be->roots, re);
			अगर (पंचांगp) अणु
				kमुक्त(re);
				re = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण

	exist = insert_ref_entry(&be->refs, ref);
	अगर (exist) अणु
		अगर (action == BTRFS_DROP_DELAYED_REF) अणु
			अगर (exist->num_refs == 0) अणु
				btrfs_err(fs_info,
"dropping a ref for a existing root that doesn't have a ref on the block");
				dump_block_entry(fs_info, be);
				dump_ref_action(fs_info, ra);
				kमुक्त(ref);
				kमुक्त(ra);
				जाओ out_unlock;
			पूर्ण
			exist->num_refs--;
			अगर (exist->num_refs == 0) अणु
				rb_erase(&exist->node, &be->refs);
				kमुक्त(exist);
			पूर्ण
		पूर्ण अन्यथा अगर (!be->metadata) अणु
			exist->num_refs++;
		पूर्ण अन्यथा अणु
			btrfs_err(fs_info,
"attempting to add another ref for an existing ref on a tree block");
			dump_block_entry(fs_info, be);
			dump_ref_action(fs_info, ra);
			kमुक्त(ref);
			kमुक्त(ra);
			जाओ out_unlock;
		पूर्ण
		kमुक्त(ref);
	पूर्ण अन्यथा अणु
		अगर (action == BTRFS_DROP_DELAYED_REF) अणु
			btrfs_err(fs_info,
"dropping a ref for a root that doesn't have a ref on the block");
			dump_block_entry(fs_info, be);
			dump_ref_action(fs_info, ra);
			kमुक्त(ref);
			kमुक्त(ra);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर (!parent && !re) अणु
		re = lookup_root_entry(&be->roots, ref_root);
		अगर (!re) अणु
			/*
			 * This shouldn't happen because we will add our re
			 * above when we lookup the be with !parent, but just in
			 * हाल catch this हाल so we करोn't panic because I
			 * didn't think of some other corner हाल.
			 */
			btrfs_err(fs_info, "failed to find root %llu for %llu",
				  generic_ref->real_root, be->bytenr);
			dump_block_entry(fs_info, be);
			dump_ref_action(fs_info, ra);
			kमुक्त(ra);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	अगर (action == BTRFS_DROP_DELAYED_REF) अणु
		अगर (re)
			re->num_refs--;
		be->num_refs--;
	पूर्ण अन्यथा अगर (action == BTRFS_ADD_DELAYED_REF) अणु
		be->num_refs++;
		अगर (re)
			re->num_refs++;
	पूर्ण
	list_add_tail(&ra->list, &be->actions);
	ret = 0;
out_unlock:
	spin_unlock(&fs_info->ref_verअगरy_lock);
out:
	अगर (ret)
		btrfs_clear_opt(fs_info->mount_opt, REF_VERIFY);
	वापस ret;
पूर्ण

/* Free up the ref cache */
व्योम btrfs_मुक्त_ref_cache(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा block_entry *be;
	काष्ठा rb_node *n;

	अगर (!btrfs_test_opt(fs_info, REF_VERIFY))
		वापस;

	spin_lock(&fs_info->ref_verअगरy_lock);
	जबतक ((n = rb_first(&fs_info->block_tree))) अणु
		be = rb_entry(n, काष्ठा block_entry, node);
		rb_erase(&be->node, &fs_info->block_tree);
		मुक्त_block_entry(be);
		cond_resched_lock(&fs_info->ref_verअगरy_lock);
	पूर्ण
	spin_unlock(&fs_info->ref_verअगरy_lock);
पूर्ण

व्योम btrfs_मुक्त_ref_tree_range(काष्ठा btrfs_fs_info *fs_info, u64 start,
			       u64 len)
अणु
	काष्ठा block_entry *be = शून्य, *entry;
	काष्ठा rb_node *n;

	अगर (!btrfs_test_opt(fs_info, REF_VERIFY))
		वापस;

	spin_lock(&fs_info->ref_verअगरy_lock);
	n = fs_info->block_tree.rb_node;
	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा block_entry, node);
		अगर (entry->bytenr < start) अणु
			n = n->rb_right;
		पूर्ण अन्यथा अगर (entry->bytenr > start) अणु
			n = n->rb_left;
		पूर्ण अन्यथा अणु
			be = entry;
			अवरोध;
		पूर्ण
		/* We want to get as बंद to start as possible */
		अगर (be == शून्य ||
		    (entry->bytenr < start && be->bytenr > start) ||
		    (entry->bytenr < start && entry->bytenr > be->bytenr))
			be = entry;
	पूर्ण

	/*
	 * Could have an empty block group, maybe have something to check क्रम
	 * this हाल to verअगरy we were actually empty?
	 */
	अगर (!be) अणु
		spin_unlock(&fs_info->ref_verअगरy_lock);
		वापस;
	पूर्ण

	n = &be->node;
	जबतक (n) अणु
		be = rb_entry(n, काष्ठा block_entry, node);
		n = rb_next(n);
		अगर (be->bytenr < start && be->bytenr + be->len > start) अणु
			btrfs_err(fs_info,
				"block entry overlaps a block group [%llu,%llu]!",
				start, len);
			dump_block_entry(fs_info, be);
			जारी;
		पूर्ण
		अगर (be->bytenr < start)
			जारी;
		अगर (be->bytenr >= start + len)
			अवरोध;
		अगर (be->bytenr + be->len > start + len) अणु
			btrfs_err(fs_info,
				"block entry overlaps a block group [%llu,%llu]!",
				start, len);
			dump_block_entry(fs_info, be);
		पूर्ण
		rb_erase(&be->node, &fs_info->block_tree);
		मुक्त_block_entry(be);
	पूर्ण
	spin_unlock(&fs_info->ref_verअगरy_lock);
पूर्ण

/* Walk करोwn all roots and build the ref tree, meant to be called at mount */
पूर्णांक btrfs_build_ref_tree(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *eb;
	पूर्णांक tree_block_level = 0;
	u64 bytenr = 0, num_bytes = 0;
	पूर्णांक ret, level;

	अगर (!btrfs_test_opt(fs_info, REF_VERIFY))
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	eb = btrfs_पढ़ो_lock_root_node(fs_info->extent_root);
	level = btrfs_header_level(eb);
	path->nodes[level] = eb;
	path->slots[level] = 0;
	path->locks[level] = BTRFS_READ_LOCK;

	जबतक (1) अणु
		/*
		 * We have to keep track of the bytenr/num_bytes we last hit
		 * because we could have run out of space क्रम an अंतरभूत ref, and
		 * would have had to added a ref key item which may appear on a
		 * dअगरferent leaf from the original extent item.
		 */
		ret = walk_करोwn_tree(fs_info->extent_root, path, level,
				     &bytenr, &num_bytes, &tree_block_level);
		अगर (ret)
			अवरोध;
		ret = walk_up_tree(path, &level);
		अगर (ret < 0)
			अवरोध;
		अगर (ret > 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		btrfs_clear_opt(fs_info->mount_opt, REF_VERIFY);
		btrfs_मुक्त_ref_cache(fs_info);
	पूर्ण
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण
