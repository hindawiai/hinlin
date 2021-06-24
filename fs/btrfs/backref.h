<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2011 STRATO.  All rights reserved.
 */

#अगर_अघोषित BTRFS_BACKREF_H
#घोषणा BTRFS_BACKREF_H

#समावेश <linux/btrfs.h>
#समावेश "ulist.h"
#समावेश "disk-io.h"
#समावेश "extent_io.h"

काष्ठा inode_fs_paths अणु
	काष्ठा btrfs_path		*btrfs_path;
	काष्ठा btrfs_root		*fs_root;
	काष्ठा btrfs_data_container	*fspath;
पूर्ण;

प्रकार पूर्णांक (iterate_extent_inodes_t)(u64 inum, u64 offset, u64 root,
		व्योम *ctx);

पूर्णांक extent_from_logical(काष्ठा btrfs_fs_info *fs_info, u64 logical,
			काष्ठा btrfs_path *path, काष्ठा btrfs_key *found_key,
			u64 *flags);

पूर्णांक tree_backref_क्रम_extent(अचिन्हित दीर्घ *ptr, काष्ठा extent_buffer *eb,
			    काष्ठा btrfs_key *key, काष्ठा btrfs_extent_item *ei,
			    u32 item_size, u64 *out_root, u8 *out_level);

पूर्णांक iterate_extent_inodes(काष्ठा btrfs_fs_info *fs_info,
				u64 extent_item_objectid,
				u64 extent_offset, पूर्णांक search_commit_root,
				iterate_extent_inodes_t *iterate, व्योम *ctx,
				bool ignore_offset);

पूर्णांक iterate_inodes_from_logical(u64 logical, काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_path *path,
				iterate_extent_inodes_t *iterate, व्योम *ctx,
				bool ignore_offset);

पूर्णांक paths_from_inode(u64 inum, काष्ठा inode_fs_paths *ipath);

पूर्णांक btrfs_find_all_leafs(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			 u64 समय_seq, काष्ठा ulist **leafs,
			 स्थिर u64 *extent_item_pos, bool ignore_offset);
पूर्णांक btrfs_find_all_roots(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			 u64 समय_seq, काष्ठा ulist **roots, bool ignore_offset);
अक्षर *btrfs_ref_to_path(काष्ठा btrfs_root *fs_root, काष्ठा btrfs_path *path,
			u32 name_len, अचिन्हित दीर्घ name_off,
			काष्ठा extent_buffer *eb_in, u64 parent,
			अक्षर *dest, u32 size);

काष्ठा btrfs_data_container *init_data_container(u32 total_bytes);
काष्ठा inode_fs_paths *init_ipath(s32 total_bytes, काष्ठा btrfs_root *fs_root,
					काष्ठा btrfs_path *path);
व्योम मुक्त_ipath(काष्ठा inode_fs_paths *ipath);

पूर्णांक btrfs_find_one_extref(काष्ठा btrfs_root *root, u64 inode_objectid,
			  u64 start_off, काष्ठा btrfs_path *path,
			  काष्ठा btrfs_inode_extref **ret_extref,
			  u64 *found_off);
पूर्णांक btrfs_check_shared(काष्ठा btrfs_root *root, u64 inum, u64 bytenr,
		काष्ठा ulist *roots, काष्ठा ulist *पंचांगp_ulist);

पूर्णांक __init btrfs_prelim_ref_init(व्योम);
व्योम __cold btrfs_prelim_ref_निकास(व्योम);

काष्ठा prelim_ref अणु
	काष्ठा rb_node rbnode;
	u64 root_id;
	काष्ठा btrfs_key key_क्रम_search;
	पूर्णांक level;
	पूर्णांक count;
	काष्ठा extent_inode_elem *inode_list;
	u64 parent;
	u64 wanted_disk_byte;
पूर्ण;

/*
 * Iterate backrefs of one extent.
 *
 * Now it only supports iteration of tree block in commit root.
 */
काष्ठा btrfs_backref_iter अणु
	u64 bytenr;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_key cur_key;
	u32 item_ptr;
	u32 cur_ptr;
	u32 end_ptr;
पूर्ण;

काष्ठा btrfs_backref_iter *btrfs_backref_iter_alloc(
		काष्ठा btrfs_fs_info *fs_info, gfp_t gfp_flag);

अटल अंतरभूत व्योम btrfs_backref_iter_मुक्त(काष्ठा btrfs_backref_iter *iter)
अणु
	अगर (!iter)
		वापस;
	btrfs_मुक्त_path(iter->path);
	kमुक्त(iter);
पूर्ण

अटल अंतरभूत काष्ठा extent_buffer *btrfs_backref_get_eb(
		काष्ठा btrfs_backref_iter *iter)
अणु
	अगर (!iter)
		वापस शून्य;
	वापस iter->path->nodes[0];
पूर्ण

/*
 * For metadata with EXTENT_ITEM key (non-skinny) हाल, the first अंतरभूत data
 * is btrfs_tree_block_info, without a btrfs_extent_अंतरभूत_ref header.
 *
 * This helper determines अगर that's the हाल.
 */
अटल अंतरभूत bool btrfs_backref_has_tree_block_info(
		काष्ठा btrfs_backref_iter *iter)
अणु
	अगर (iter->cur_key.type == BTRFS_EXTENT_ITEM_KEY &&
	    iter->cur_ptr - iter->item_ptr == माप(काष्ठा btrfs_extent_item))
		वापस true;
	वापस false;
पूर्ण

पूर्णांक btrfs_backref_iter_start(काष्ठा btrfs_backref_iter *iter, u64 bytenr);

पूर्णांक btrfs_backref_iter_next(काष्ठा btrfs_backref_iter *iter);

अटल अंतरभूत bool btrfs_backref_iter_is_अंतरभूत_ref(
		काष्ठा btrfs_backref_iter *iter)
अणु
	अगर (iter->cur_key.type == BTRFS_EXTENT_ITEM_KEY ||
	    iter->cur_key.type == BTRFS_METADATA_ITEM_KEY)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत व्योम btrfs_backref_iter_release(काष्ठा btrfs_backref_iter *iter)
अणु
	iter->bytenr = 0;
	iter->item_ptr = 0;
	iter->cur_ptr = 0;
	iter->end_ptr = 0;
	btrfs_release_path(iter->path);
	स_रखो(&iter->cur_key, 0, माप(iter->cur_key));
पूर्ण

/*
 * Backref cache related काष्ठाures
 *
 * The whole objective of backref_cache is to build a bi-directional map
 * of tree blocks (represented by backref_node) and all their parents.
 */

/*
 * Represent a tree block in the backref cache
 */
काष्ठा btrfs_backref_node अणु
	काष्ठा अणु
		काष्ठा rb_node rb_node;
		u64 bytenr;
	पूर्ण; /* Use rb_simple_node क्रम search/insert */

	u64 new_bytenr;
	/* Objectid of tree block owner, can be not uptodate */
	u64 owner;
	/* Link to pending, changed or detached list */
	काष्ठा list_head list;

	/* List of upper level edges, which link this node to its parents */
	काष्ठा list_head upper;
	/* List of lower level edges, which link this node to its children */
	काष्ठा list_head lower;

	/* शून्य अगर this node is not tree root */
	काष्ठा btrfs_root *root;
	/* Extent buffer got by COWing the block */
	काष्ठा extent_buffer *eb;
	/* Level of the tree block */
	अचिन्हित पूर्णांक level:8;
	/* Is the block in a non-shareable tree */
	अचिन्हित पूर्णांक cowonly:1;
	/* 1 अगर no child node is in the cache */
	अचिन्हित पूर्णांक lowest:1;
	/* Is the extent buffer locked */
	अचिन्हित पूर्णांक locked:1;
	/* Has the block been processed */
	अचिन्हित पूर्णांक processed:1;
	/* Have backrefs of this block been checked */
	अचिन्हित पूर्णांक checked:1;
	/*
	 * 1 अगर corresponding block has been COWed but some upper level block
	 * poपूर्णांकers may not poपूर्णांक to the new location
	 */
	अचिन्हित पूर्णांक pending:1;
	/* 1 अगर the backref node isn't connected to any other backref node */
	अचिन्हित पूर्णांक detached:1;

	/*
	 * For generic purpose backref cache, where we only care अगर it's a reloc
	 * root, करोesn't care the source subvolid.
	 */
	अचिन्हित पूर्णांक is_reloc_root:1;
पूर्ण;

#घोषणा LOWER	0
#घोषणा UPPER	1

/*
 * Represent an edge connecting upper and lower backref nodes.
 */
काष्ठा btrfs_backref_edge अणु
	/*
	 * list[LOWER] is linked to btrfs_backref_node::upper of lower level
	 * node, and list[UPPER] is linked to btrfs_backref_node::lower of
	 * upper level node.
	 *
	 * Also, build_backref_tree() uses list[UPPER] क्रम pending edges, beक्रमe
	 * linking list[UPPER] to its upper level nodes.
	 */
	काष्ठा list_head list[2];

	/* Two related nodes */
	काष्ठा btrfs_backref_node *node[2];
पूर्ण;

काष्ठा btrfs_backref_cache अणु
	/* Red black tree of all backref nodes in the cache */
	काष्ठा rb_root rb_root;
	/* For passing backref nodes to btrfs_reloc_cow_block */
	काष्ठा btrfs_backref_node *path[BTRFS_MAX_LEVEL];
	/*
	 * List of blocks that have been COWed but some block poपूर्णांकers in upper
	 * level blocks may not reflect the new location
	 */
	काष्ठा list_head pending[BTRFS_MAX_LEVEL];
	/* List of backref nodes with no child node */
	काष्ठा list_head leaves;
	/* List of blocks that have been COWed in current transaction */
	काष्ठा list_head changed;
	/* List of detached backref node. */
	काष्ठा list_head detached;

	u64 last_trans;

	पूर्णांक nr_nodes;
	पूर्णांक nr_edges;

	/* List of unchecked backref edges during backref cache build */
	काष्ठा list_head pending_edge;

	/* List of useless backref nodes during backref cache build */
	काष्ठा list_head useless_node;

	काष्ठा btrfs_fs_info *fs_info;

	/*
	 * Whether this cache is क्रम relocation
	 *
	 * Reloction backref cache require more info क्रम reloc root compared
	 * to generic backref cache.
	 */
	अचिन्हित पूर्णांक is_reloc;
पूर्ण;

व्योम btrfs_backref_init_cache(काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा btrfs_backref_cache *cache, पूर्णांक is_reloc);
काष्ठा btrfs_backref_node *btrfs_backref_alloc_node(
		काष्ठा btrfs_backref_cache *cache, u64 bytenr, पूर्णांक level);
काष्ठा btrfs_backref_edge *btrfs_backref_alloc_edge(
		काष्ठा btrfs_backref_cache *cache);

#घोषणा		LINK_LOWER	(1 << 0)
#घोषणा		LINK_UPPER	(1 << 1)
अटल अंतरभूत व्योम btrfs_backref_link_edge(काष्ठा btrfs_backref_edge *edge,
					   काष्ठा btrfs_backref_node *lower,
					   काष्ठा btrfs_backref_node *upper,
					   पूर्णांक link_which)
अणु
	ASSERT(upper && lower && upper->level == lower->level + 1);
	edge->node[LOWER] = lower;
	edge->node[UPPER] = upper;
	अगर (link_which & LINK_LOWER)
		list_add_tail(&edge->list[LOWER], &lower->upper);
	अगर (link_which & LINK_UPPER)
		list_add_tail(&edge->list[UPPER], &upper->lower);
पूर्ण

अटल अंतरभूत व्योम btrfs_backref_मुक्त_node(काष्ठा btrfs_backref_cache *cache,
					   काष्ठा btrfs_backref_node *node)
अणु
	अगर (node) अणु
		ASSERT(list_empty(&node->list));
		ASSERT(list_empty(&node->lower));
		ASSERT(node->eb == शून्य);
		cache->nr_nodes--;
		btrfs_put_root(node->root);
		kमुक्त(node);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम btrfs_backref_मुक्त_edge(काष्ठा btrfs_backref_cache *cache,
					   काष्ठा btrfs_backref_edge *edge)
अणु
	अगर (edge) अणु
		cache->nr_edges--;
		kमुक्त(edge);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम btrfs_backref_unlock_node_buffer(
		काष्ठा btrfs_backref_node *node)
अणु
	अगर (node->locked) अणु
		btrfs_tree_unlock(node->eb);
		node->locked = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम btrfs_backref_drop_node_buffer(
		काष्ठा btrfs_backref_node *node)
अणु
	अगर (node->eb) अणु
		btrfs_backref_unlock_node_buffer(node);
		मुक्त_extent_buffer(node->eb);
		node->eb = शून्य;
	पूर्ण
पूर्ण

/*
 * Drop the backref node from cache without cleaning up its children
 * edges.
 *
 * This can only be called on node without parent edges.
 * The children edges are still kept as is.
 */
अटल अंतरभूत व्योम btrfs_backref_drop_node(काष्ठा btrfs_backref_cache *tree,
					   काष्ठा btrfs_backref_node *node)
अणु
	ASSERT(list_empty(&node->upper));

	btrfs_backref_drop_node_buffer(node);
	list_del_init(&node->list);
	list_del_init(&node->lower);
	अगर (!RB_EMPTY_NODE(&node->rb_node))
		rb_erase(&node->rb_node, &tree->rb_root);
	btrfs_backref_मुक्त_node(tree, node);
पूर्ण

व्योम btrfs_backref_cleanup_node(काष्ठा btrfs_backref_cache *cache,
				काष्ठा btrfs_backref_node *node);

व्योम btrfs_backref_release_cache(काष्ठा btrfs_backref_cache *cache);

अटल अंतरभूत व्योम btrfs_backref_panic(काष्ठा btrfs_fs_info *fs_info,
				       u64 bytenr, पूर्णांक त्रुटि_सं)
अणु
	btrfs_panic(fs_info, त्रुटि_सं,
		    "Inconsistency in backref cache found at offset %llu",
		    bytenr);
पूर्ण

पूर्णांक btrfs_backref_add_tree_node(काष्ठा btrfs_backref_cache *cache,
				काष्ठा btrfs_path *path,
				काष्ठा btrfs_backref_iter *iter,
				काष्ठा btrfs_key *node_key,
				काष्ठा btrfs_backref_node *cur);

पूर्णांक btrfs_backref_finish_upper_links(काष्ठा btrfs_backref_cache *cache,
				     काष्ठा btrfs_backref_node *start);

व्योम btrfs_backref_error_cleanup(काष्ठा btrfs_backref_cache *cache,
				 काष्ठा btrfs_backref_node *node);

#पूर्ण_अगर
