<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश <linux/error-injection.h>
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "volumes.h"
#समावेश "locking.h"
#समावेश "btrfs_inode.h"
#समावेश "async-thread.h"
#समावेश "free-space-cache.h"
#समावेश "qgroup.h"
#समावेश "print-tree.h"
#समावेश "delalloc-space.h"
#समावेश "block-group.h"
#समावेश "backref.h"
#समावेश "misc.h"

/*
 * Relocation overview
 *
 * [What करोes relocation करो]
 *
 * The objective of relocation is to relocate all extents of the target block
 * group to other block groups.
 * This is utilized by resize (shrink only), profile converting, compacting
 * space, or balance routine to spपढ़ो chunks over devices.
 *
 * 		Beक्रमe		|		After
 * ------------------------------------------------------------------
 *  BG A: 10 data extents	| BG A: deleted
 *  BG B:  2 data extents	| BG B: 10 data extents (2 old + 8 relocated)
 *  BG C:  1 extents		| BG C:  3 data extents (1 old + 2 relocated)
 *
 * [How करोes relocation work]
 *
 * 1.   Mark the target block group पढ़ो-only
 *      New extents won't be allocated from the target block group.
 *
 * 2.1  Record each extent in the target block group
 *      To build a proper map of extents to be relocated.
 *
 * 2.2  Build data reloc tree and reloc trees
 *      Data reloc tree will contain an inode, recording all newly relocated
 *      data extents.
 *      There will be only one data reloc tree क्रम one data block group.
 *
 *      Reloc tree will be a special snapshot of its source tree, containing
 *      relocated tree blocks.
 *      Each tree referring to a tree block in target block group will get its
 *      reloc tree built.
 *
 * 2.3  Swap source tree with its corresponding reloc tree
 *      Each involved tree only refers to new extents after swap.
 *
 * 3.   Cleanup reloc trees and data reloc tree.
 *      As old extents in the target block group are still referenced by reloc
 *      trees, we need to clean them up beक्रमe really मुक्तing the target block
 *      group.
 *
 * The मुख्य complनिकासy is in steps 2.2 and 2.3.
 *
 * The entry poपूर्णांक of relocation is relocate_block_group() function.
 */

#घोषणा RELOCATION_RESERVED_NODES	256
/*
 * map address of tree root to tree
 */
काष्ठा mapping_node अणु
	काष्ठा अणु
		काष्ठा rb_node rb_node;
		u64 bytenr;
	पूर्ण; /* Use rb_simle_node क्रम search/insert */
	व्योम *data;
पूर्ण;

काष्ठा mapping_tree अणु
	काष्ठा rb_root rb_root;
	spinlock_t lock;
पूर्ण;

/*
 * present a tree block to process
 */
काष्ठा tree_block अणु
	काष्ठा अणु
		काष्ठा rb_node rb_node;
		u64 bytenr;
	पूर्ण; /* Use rb_simple_node क्रम search/insert */
	u64 owner;
	काष्ठा btrfs_key key;
	अचिन्हित पूर्णांक level:8;
	अचिन्हित पूर्णांक key_पढ़ोy:1;
पूर्ण;

#घोषणा MAX_EXTENTS 128

काष्ठा file_extent_cluster अणु
	u64 start;
	u64 end;
	u64 boundary[MAX_EXTENTS];
	अचिन्हित पूर्णांक nr;
पूर्ण;

काष्ठा reloc_control अणु
	/* block group to relocate */
	काष्ठा btrfs_block_group *block_group;
	/* extent tree */
	काष्ठा btrfs_root *extent_root;
	/* inode क्रम moving data */
	काष्ठा inode *data_inode;

	काष्ठा btrfs_block_rsv *block_rsv;

	काष्ठा btrfs_backref_cache backref_cache;

	काष्ठा file_extent_cluster cluster;
	/* tree blocks have been processed */
	काष्ठा extent_io_tree processed_blocks;
	/* map start of tree root to corresponding reloc tree */
	काष्ठा mapping_tree reloc_root_tree;
	/* list of reloc trees */
	काष्ठा list_head reloc_roots;
	/* list of subvolume trees that get relocated */
	काष्ठा list_head dirty_subvol_roots;
	/* size of metadata reservation क्रम merging reloc trees */
	u64 merging_rsv_size;
	/* size of relocated tree nodes */
	u64 nodes_relocated;
	/* reserved size क्रम block group relocation*/
	u64 reserved_bytes;

	u64 search_start;
	u64 extents_found;

	अचिन्हित पूर्णांक stage:8;
	अचिन्हित पूर्णांक create_reloc_tree:1;
	अचिन्हित पूर्णांक merge_reloc_tree:1;
	अचिन्हित पूर्णांक found_file_extent:1;
पूर्ण;

/* stages of data relocation */
#घोषणा MOVE_DATA_EXTENTS	0
#घोषणा UPDATE_DATA_PTRS	1

अटल व्योम mark_block_processed(काष्ठा reloc_control *rc,
				 काष्ठा btrfs_backref_node *node)
अणु
	u32 blocksize;

	अगर (node->level == 0 ||
	    in_range(node->bytenr, rc->block_group->start,
		     rc->block_group->length)) अणु
		blocksize = rc->extent_root->fs_info->nodesize;
		set_extent_bits(&rc->processed_blocks, node->bytenr,
				node->bytenr + blocksize - 1, EXTENT_सूचीTY);
	पूर्ण
	node->processed = 1;
पूर्ण


अटल व्योम mapping_tree_init(काष्ठा mapping_tree *tree)
अणु
	tree->rb_root = RB_ROOT;
	spin_lock_init(&tree->lock);
पूर्ण

/*
 * walk up backref nodes until reach node presents tree root
 */
अटल काष्ठा btrfs_backref_node *walk_up_backref(
		काष्ठा btrfs_backref_node *node,
		काष्ठा btrfs_backref_edge *edges[], पूर्णांक *index)
अणु
	काष्ठा btrfs_backref_edge *edge;
	पूर्णांक idx = *index;

	जबतक (!list_empty(&node->upper)) अणु
		edge = list_entry(node->upper.next,
				  काष्ठा btrfs_backref_edge, list[LOWER]);
		edges[idx++] = edge;
		node = edge->node[UPPER];
	पूर्ण
	BUG_ON(node->detached);
	*index = idx;
	वापस node;
पूर्ण

/*
 * walk करोwn backref nodes to find start of next reference path
 */
अटल काष्ठा btrfs_backref_node *walk_करोwn_backref(
		काष्ठा btrfs_backref_edge *edges[], पूर्णांक *index)
अणु
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा btrfs_backref_node *lower;
	पूर्णांक idx = *index;

	जबतक (idx > 0) अणु
		edge = edges[idx - 1];
		lower = edge->node[LOWER];
		अगर (list_is_last(&edge->list[LOWER], &lower->upper)) अणु
			idx--;
			जारी;
		पूर्ण
		edge = list_entry(edge->list[LOWER].next,
				  काष्ठा btrfs_backref_edge, list[LOWER]);
		edges[idx - 1] = edge;
		*index = idx;
		वापस edge->node[UPPER];
	पूर्ण
	*index = 0;
	वापस शून्य;
पूर्ण

अटल व्योम update_backref_node(काष्ठा btrfs_backref_cache *cache,
				काष्ठा btrfs_backref_node *node, u64 bytenr)
अणु
	काष्ठा rb_node *rb_node;
	rb_erase(&node->rb_node, &cache->rb_root);
	node->bytenr = bytenr;
	rb_node = rb_simple_insert(&cache->rb_root, node->bytenr, &node->rb_node);
	अगर (rb_node)
		btrfs_backref_panic(cache->fs_info, bytenr, -EEXIST);
पूर्ण

/*
 * update backref cache after a transaction commit
 */
अटल पूर्णांक update_backref_cache(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_backref_cache *cache)
अणु
	काष्ठा btrfs_backref_node *node;
	पूर्णांक level = 0;

	अगर (cache->last_trans == 0) अणु
		cache->last_trans = trans->transid;
		वापस 0;
	पूर्ण

	अगर (cache->last_trans == trans->transid)
		वापस 0;

	/*
	 * detached nodes are used to aव्योम unnecessary backref
	 * lookup. transaction commit changes the extent tree.
	 * so the detached nodes are no दीर्घer useful.
	 */
	जबतक (!list_empty(&cache->detached)) अणु
		node = list_entry(cache->detached.next,
				  काष्ठा btrfs_backref_node, list);
		btrfs_backref_cleanup_node(cache, node);
	पूर्ण

	जबतक (!list_empty(&cache->changed)) अणु
		node = list_entry(cache->changed.next,
				  काष्ठा btrfs_backref_node, list);
		list_del_init(&node->list);
		BUG_ON(node->pending);
		update_backref_node(cache, node, node->new_bytenr);
	पूर्ण

	/*
	 * some nodes can be left in the pending list अगर there were
	 * errors during processing the pending nodes.
	 */
	क्रम (level = 0; level < BTRFS_MAX_LEVEL; level++) अणु
		list_क्रम_each_entry(node, &cache->pending[level], list) अणु
			BUG_ON(!node->pending);
			अगर (node->bytenr == node->new_bytenr)
				जारी;
			update_backref_node(cache, node, node->new_bytenr);
		पूर्ण
	पूर्ण

	cache->last_trans = 0;
	वापस 1;
पूर्ण

अटल bool reloc_root_is_dead(काष्ठा btrfs_root *root)
अणु
	/*
	 * Pair with set_bit/clear_bit in clean_dirty_subvols and
	 * btrfs_update_reloc_root. We need to see the updated bit beक्रमe
	 * trying to access reloc_root
	 */
	smp_rmb();
	अगर (test_bit(BTRFS_ROOT_DEAD_RELOC_TREE, &root->state))
		वापस true;
	वापस false;
पूर्ण

/*
 * Check अगर this subvolume tree has valid reloc tree.
 *
 * Reloc tree after swap is considered dead, thus not considered as valid.
 * This is enough क्रम most callers, as they करोn't distinguish dead reloc root
 * from no reloc root.  But btrfs_should_ignore_reloc_root() below is a
 * special हाल.
 */
अटल bool have_reloc_root(काष्ठा btrfs_root *root)
अणु
	अगर (reloc_root_is_dead(root))
		वापस false;
	अगर (!root->reloc_root)
		वापस false;
	वापस true;
पूर्ण

पूर्णांक btrfs_should_ignore_reloc_root(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_root *reloc_root;

	अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
		वापस 0;

	/* This root has been merged with its reloc tree, we can ignore it */
	अगर (reloc_root_is_dead(root))
		वापस 1;

	reloc_root = root->reloc_root;
	अगर (!reloc_root)
		वापस 0;

	अगर (btrfs_header_generation(reloc_root->commit_root) ==
	    root->fs_info->running_transaction->transid)
		वापस 0;
	/*
	 * अगर there is reloc tree and it was created in previous
	 * transaction backref lookup can find the reloc tree,
	 * so backref node क्रम the fs tree root is useless क्रम
	 * relocation.
	 */
	वापस 1;
पूर्ण

/*
 * find reloc tree by address of tree root
 */
काष्ठा btrfs_root *find_reloc_root(काष्ठा btrfs_fs_info *fs_info, u64 bytenr)
अणु
	काष्ठा reloc_control *rc = fs_info->reloc_ctl;
	काष्ठा rb_node *rb_node;
	काष्ठा mapping_node *node;
	काष्ठा btrfs_root *root = शून्य;

	ASSERT(rc);
	spin_lock(&rc->reloc_root_tree.lock);
	rb_node = rb_simple_search(&rc->reloc_root_tree.rb_root, bytenr);
	अगर (rb_node) अणु
		node = rb_entry(rb_node, काष्ठा mapping_node, rb_node);
		root = (काष्ठा btrfs_root *)node->data;
	पूर्ण
	spin_unlock(&rc->reloc_root_tree.lock);
	वापस btrfs_grab_root(root);
पूर्ण

/*
 * For useless nodes, करो two major clean ups:
 *
 * - Cleanup the children edges and nodes
 *   If child node is also orphan (no parent) during cleanup, then the child
 *   node will also be cleaned up.
 *
 * - Freeing up leaves (level 0), keeps nodes detached
 *   For nodes, the node is still cached as "detached"
 *
 * Return false अगर @node is not in the @useless_nodes list.
 * Return true अगर @node is in the @useless_nodes list.
 */
अटल bool handle_useless_nodes(काष्ठा reloc_control *rc,
				 काष्ठा btrfs_backref_node *node)
अणु
	काष्ठा btrfs_backref_cache *cache = &rc->backref_cache;
	काष्ठा list_head *useless_node = &cache->useless_node;
	bool ret = false;

	जबतक (!list_empty(useless_node)) अणु
		काष्ठा btrfs_backref_node *cur;

		cur = list_first_entry(useless_node, काष्ठा btrfs_backref_node,
				 list);
		list_del_init(&cur->list);

		/* Only tree root nodes can be added to @useless_nodes */
		ASSERT(list_empty(&cur->upper));

		अगर (cur == node)
			ret = true;

		/* The node is the lowest node */
		अगर (cur->lowest) अणु
			list_del_init(&cur->lower);
			cur->lowest = 0;
		पूर्ण

		/* Cleanup the lower edges */
		जबतक (!list_empty(&cur->lower)) अणु
			काष्ठा btrfs_backref_edge *edge;
			काष्ठा btrfs_backref_node *lower;

			edge = list_entry(cur->lower.next,
					काष्ठा btrfs_backref_edge, list[UPPER]);
			list_del(&edge->list[UPPER]);
			list_del(&edge->list[LOWER]);
			lower = edge->node[LOWER];
			btrfs_backref_मुक्त_edge(cache, edge);

			/* Child node is also orphan, queue क्रम cleanup */
			अगर (list_empty(&lower->upper))
				list_add(&lower->list, useless_node);
		पूर्ण
		/* Mark this block processed क्रम relocation */
		mark_block_processed(rc, cur);

		/*
		 * Backref nodes क्रम tree leaves are deleted from the cache.
		 * Backref nodes क्रम upper level tree blocks are left in the
		 * cache to aव्योम unnecessary backref lookup.
		 */
		अगर (cur->level > 0) अणु
			list_add(&cur->list, &cache->detached);
			cur->detached = 1;
		पूर्ण अन्यथा अणु
			rb_erase(&cur->rb_node, &cache->rb_root);
			btrfs_backref_मुक्त_node(cache, cur);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Build backref tree क्रम a given tree block. Root of the backref tree
 * corresponds the tree block, leaves of the backref tree correspond roots of
 * b-trees that reference the tree block.
 *
 * The basic idea of this function is check backrefs of a given block to find
 * upper level blocks that reference the block, and then check backrefs of
 * these upper level blocks recursively. The recursion stops when tree root is
 * reached or backrefs क्रम the block is cached.
 *
 * NOTE: अगर we find that backrefs क्रम a block are cached, we know backrefs क्रम
 * all upper level blocks that directly/indirectly reference the block are also
 * cached.
 */
अटल noअंतरभूत_क्रम_stack काष्ठा btrfs_backref_node *build_backref_tree(
			काष्ठा reloc_control *rc, काष्ठा btrfs_key *node_key,
			पूर्णांक level, u64 bytenr)
अणु
	काष्ठा btrfs_backref_iter *iter;
	काष्ठा btrfs_backref_cache *cache = &rc->backref_cache;
	/* For searching parent of TREE_BLOCK_REF */
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_backref_node *cur;
	काष्ठा btrfs_backref_node *node = शून्य;
	काष्ठा btrfs_backref_edge *edge;
	पूर्णांक ret;
	पूर्णांक err = 0;

	iter = btrfs_backref_iter_alloc(rc->extent_root->fs_info, GFP_NOFS);
	अगर (!iter)
		वापस ERR_PTR(-ENOMEM);
	path = btrfs_alloc_path();
	अगर (!path) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	node = btrfs_backref_alloc_node(cache, bytenr, level);
	अगर (!node) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	node->lowest = 1;
	cur = node;

	/* Bपढ़ोth-first search to build backref cache */
	करो अणु
		ret = btrfs_backref_add_tree_node(cache, path, iter, node_key,
						  cur);
		अगर (ret < 0) अणु
			err = ret;
			जाओ out;
		पूर्ण
		edge = list_first_entry_or_null(&cache->pending_edge,
				काष्ठा btrfs_backref_edge, list[UPPER]);
		/*
		 * The pending list isn't empty, take the first block to
		 * process
		 */
		अगर (edge) अणु
			list_del_init(&edge->list[UPPER]);
			cur = edge->node[UPPER];
		पूर्ण
	पूर्ण जबतक (edge);

	/* Finish the upper linkage of newly added edges/nodes */
	ret = btrfs_backref_finish_upper_links(cache, node);
	अगर (ret < 0) अणु
		err = ret;
		जाओ out;
	पूर्ण

	अगर (handle_useless_nodes(rc, node))
		node = शून्य;
out:
	btrfs_backref_iter_मुक्त(iter);
	btrfs_मुक्त_path(path);
	अगर (err) अणु
		btrfs_backref_error_cleanup(cache, node);
		वापस ERR_PTR(err);
	पूर्ण
	ASSERT(!node || !node->detached);
	ASSERT(list_empty(&cache->useless_node) &&
	       list_empty(&cache->pending_edge));
	वापस node;
पूर्ण

/*
 * helper to add backref node क्रम the newly created snapshot.
 * the backref node is created by cloning backref node that
 * corresponds to root of source tree
 */
अटल पूर्णांक clone_backref_node(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा reloc_control *rc,
			      काष्ठा btrfs_root *src,
			      काष्ठा btrfs_root *dest)
अणु
	काष्ठा btrfs_root *reloc_root = src->reloc_root;
	काष्ठा btrfs_backref_cache *cache = &rc->backref_cache;
	काष्ठा btrfs_backref_node *node = शून्य;
	काष्ठा btrfs_backref_node *new_node;
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा btrfs_backref_edge *new_edge;
	काष्ठा rb_node *rb_node;

	अगर (cache->last_trans > 0)
		update_backref_cache(trans, cache);

	rb_node = rb_simple_search(&cache->rb_root, src->commit_root->start);
	अगर (rb_node) अणु
		node = rb_entry(rb_node, काष्ठा btrfs_backref_node, rb_node);
		अगर (node->detached)
			node = शून्य;
		अन्यथा
			BUG_ON(node->new_bytenr != reloc_root->node->start);
	पूर्ण

	अगर (!node) अणु
		rb_node = rb_simple_search(&cache->rb_root,
					   reloc_root->commit_root->start);
		अगर (rb_node) अणु
			node = rb_entry(rb_node, काष्ठा btrfs_backref_node,
					rb_node);
			BUG_ON(node->detached);
		पूर्ण
	पूर्ण

	अगर (!node)
		वापस 0;

	new_node = btrfs_backref_alloc_node(cache, dest->node->start,
					    node->level);
	अगर (!new_node)
		वापस -ENOMEM;

	new_node->lowest = node->lowest;
	new_node->checked = 1;
	new_node->root = btrfs_grab_root(dest);
	ASSERT(new_node->root);

	अगर (!node->lowest) अणु
		list_क्रम_each_entry(edge, &node->lower, list[UPPER]) अणु
			new_edge = btrfs_backref_alloc_edge(cache);
			अगर (!new_edge)
				जाओ fail;

			btrfs_backref_link_edge(new_edge, edge->node[LOWER],
						new_node, LINK_UPPER);
		पूर्ण
	पूर्ण अन्यथा अणु
		list_add_tail(&new_node->lower, &cache->leaves);
	पूर्ण

	rb_node = rb_simple_insert(&cache->rb_root, new_node->bytenr,
				   &new_node->rb_node);
	अगर (rb_node)
		btrfs_backref_panic(trans->fs_info, new_node->bytenr, -EEXIST);

	अगर (!new_node->lowest) अणु
		list_क्रम_each_entry(new_edge, &new_node->lower, list[UPPER]) अणु
			list_add_tail(&new_edge->list[LOWER],
				      &new_edge->node[LOWER]->upper);
		पूर्ण
	पूर्ण
	वापस 0;
fail:
	जबतक (!list_empty(&new_node->lower)) अणु
		new_edge = list_entry(new_node->lower.next,
				      काष्ठा btrfs_backref_edge, list[UPPER]);
		list_del(&new_edge->list[UPPER]);
		btrfs_backref_मुक्त_edge(cache, new_edge);
	पूर्ण
	btrfs_backref_मुक्त_node(cache, new_node);
	वापस -ENOMEM;
पूर्ण

/*
 * helper to add 'address of tree root -> reloc tree' mapping
 */
अटल पूर्णांक __must_check __add_reloc_root(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा rb_node *rb_node;
	काष्ठा mapping_node *node;
	काष्ठा reloc_control *rc = fs_info->reloc_ctl;

	node = kदो_स्मृति(माप(*node), GFP_NOFS);
	अगर (!node)
		वापस -ENOMEM;

	node->bytenr = root->commit_root->start;
	node->data = root;

	spin_lock(&rc->reloc_root_tree.lock);
	rb_node = rb_simple_insert(&rc->reloc_root_tree.rb_root,
				   node->bytenr, &node->rb_node);
	spin_unlock(&rc->reloc_root_tree.lock);
	अगर (rb_node) अणु
		btrfs_err(fs_info,
			    "Duplicate root found for start=%llu while inserting into relocation tree",
			    node->bytenr);
		वापस -EEXIST;
	पूर्ण

	list_add_tail(&root->root_list, &rc->reloc_roots);
	वापस 0;
पूर्ण

/*
 * helper to delete the 'address of tree root -> reloc tree'
 * mapping
 */
अटल व्योम __del_reloc_root(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा rb_node *rb_node;
	काष्ठा mapping_node *node = शून्य;
	काष्ठा reloc_control *rc = fs_info->reloc_ctl;
	bool put_ref = false;

	अगर (rc && root->node) अणु
		spin_lock(&rc->reloc_root_tree.lock);
		rb_node = rb_simple_search(&rc->reloc_root_tree.rb_root,
					   root->commit_root->start);
		अगर (rb_node) अणु
			node = rb_entry(rb_node, काष्ठा mapping_node, rb_node);
			rb_erase(&node->rb_node, &rc->reloc_root_tree.rb_root);
			RB_CLEAR_NODE(&node->rb_node);
		पूर्ण
		spin_unlock(&rc->reloc_root_tree.lock);
		ASSERT(!node || (काष्ठा btrfs_root *)node->data == root);
	पूर्ण

	/*
	 * We only put the reloc root here अगर it's on the list.  There's a lot
	 * of places where the pattern is to splice the rc->reloc_roots, process
	 * the reloc roots, and then add the reloc root back onto
	 * rc->reloc_roots.  If we call __del_reloc_root जबतक it's off of the
	 * list we करोn't want the reference being dropped, because the guy
	 * messing with the list is in अक्षरge of the reference.
	 */
	spin_lock(&fs_info->trans_lock);
	अगर (!list_empty(&root->root_list)) अणु
		put_ref = true;
		list_del_init(&root->root_list);
	पूर्ण
	spin_unlock(&fs_info->trans_lock);
	अगर (put_ref)
		btrfs_put_root(root);
	kमुक्त(node);
पूर्ण

/*
 * helper to update the 'address of tree root -> reloc tree'
 * mapping
 */
अटल पूर्णांक __update_reloc_root(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा rb_node *rb_node;
	काष्ठा mapping_node *node = शून्य;
	काष्ठा reloc_control *rc = fs_info->reloc_ctl;

	spin_lock(&rc->reloc_root_tree.lock);
	rb_node = rb_simple_search(&rc->reloc_root_tree.rb_root,
				   root->commit_root->start);
	अगर (rb_node) अणु
		node = rb_entry(rb_node, काष्ठा mapping_node, rb_node);
		rb_erase(&node->rb_node, &rc->reloc_root_tree.rb_root);
	पूर्ण
	spin_unlock(&rc->reloc_root_tree.lock);

	अगर (!node)
		वापस 0;
	BUG_ON((काष्ठा btrfs_root *)node->data != root);

	spin_lock(&rc->reloc_root_tree.lock);
	node->bytenr = root->node->start;
	rb_node = rb_simple_insert(&rc->reloc_root_tree.rb_root,
				   node->bytenr, &node->rb_node);
	spin_unlock(&rc->reloc_root_tree.lock);
	अगर (rb_node)
		btrfs_backref_panic(fs_info, node->bytenr, -EEXIST);
	वापस 0;
पूर्ण

अटल काष्ठा btrfs_root *create_reloc_root(काष्ठा btrfs_trans_handle *trans,
					काष्ठा btrfs_root *root, u64 objectid)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *reloc_root;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_root_item *root_item;
	काष्ठा btrfs_key root_key;
	पूर्णांक ret = 0;
	bool must_पात = false;

	root_item = kदो_स्मृति(माप(*root_item), GFP_NOFS);
	अगर (!root_item)
		वापस ERR_PTR(-ENOMEM);

	root_key.objectid = BTRFS_TREE_RELOC_OBJECTID;
	root_key.type = BTRFS_ROOT_ITEM_KEY;
	root_key.offset = objectid;

	अगर (root->root_key.objectid == objectid) अणु
		u64 commit_root_gen;

		/* called by btrfs_init_reloc_root */
		ret = btrfs_copy_root(trans, root, root->commit_root, &eb,
				      BTRFS_TREE_RELOC_OBJECTID);
		अगर (ret)
			जाओ fail;

		/*
		 * Set the last_snapshot field to the generation of the commit
		 * root - like this ctree.c:btrfs_block_can_be_shared() behaves
		 * correctly (वापसs true) when the relocation root is created
		 * either inside the critical section of a transaction commit
		 * (through transaction.c:qgroup_account_snapshot()) and when
		 * it's created beक्रमe the transaction commit is started.
		 */
		commit_root_gen = btrfs_header_generation(root->commit_root);
		btrfs_set_root_last_snapshot(&root->root_item, commit_root_gen);
	पूर्ण अन्यथा अणु
		/*
		 * called by btrfs_reloc_post_snapshot_hook.
		 * the source tree is a reloc tree, all tree blocks
		 * modअगरied after it was created have RELOC flag
		 * set in their headers. so it's OK to not update
		 * the 'last_snapshot'.
		 */
		ret = btrfs_copy_root(trans, root, root->node, &eb,
				      BTRFS_TREE_RELOC_OBJECTID);
		अगर (ret)
			जाओ fail;
	पूर्ण

	/*
	 * We have changed references at this poपूर्णांक, we must पात the
	 * transaction अगर anything fails.
	 */
	must_पात = true;

	स_नकल(root_item, &root->root_item, माप(*root_item));
	btrfs_set_root_bytenr(root_item, eb->start);
	btrfs_set_root_level(root_item, btrfs_header_level(eb));
	btrfs_set_root_generation(root_item, trans->transid);

	अगर (root->root_key.objectid == objectid) अणु
		btrfs_set_root_refs(root_item, 0);
		स_रखो(&root_item->drop_progress, 0,
		       माप(काष्ठा btrfs_disk_key));
		btrfs_set_root_drop_level(root_item, 0);
	पूर्ण

	btrfs_tree_unlock(eb);
	मुक्त_extent_buffer(eb);

	ret = btrfs_insert_root(trans, fs_info->tree_root,
				&root_key, root_item);
	अगर (ret)
		जाओ fail;

	kमुक्त(root_item);

	reloc_root = btrfs_पढ़ो_tree_root(fs_info->tree_root, &root_key);
	अगर (IS_ERR(reloc_root)) अणु
		ret = PTR_ERR(reloc_root);
		जाओ पात;
	पूर्ण
	set_bit(BTRFS_ROOT_SHAREABLE, &reloc_root->state);
	reloc_root->last_trans = trans->transid;
	वापस reloc_root;
fail:
	kमुक्त(root_item);
पात:
	अगर (must_पात)
		btrfs_पात_transaction(trans, ret);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * create reloc tree क्रम a given fs tree. reloc tree is just a
 * snapshot of the fs tree with special root objectid.
 *
 * The reloc_root comes out of here with two references, one क्रम
 * root->reloc_root, and another क्रम being on the rc->reloc_roots list.
 */
पूर्णांक btrfs_init_reloc_root(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *reloc_root;
	काष्ठा reloc_control *rc = fs_info->reloc_ctl;
	काष्ठा btrfs_block_rsv *rsv;
	पूर्णांक clear_rsv = 0;
	पूर्णांक ret;

	अगर (!rc)
		वापस 0;

	/*
	 * The subvolume has reloc tree but the swap is finished, no need to
	 * create/update the dead reloc tree
	 */
	अगर (reloc_root_is_dead(root))
		वापस 0;

	/*
	 * This is subtle but important.  We करो not करो
	 * record_root_in_transaction क्रम reloc roots, instead we record their
	 * corresponding fs root, and then here we update the last trans क्रम the
	 * reloc root.  This means that we have to करो this क्रम the entire lअगरe
	 * of the reloc root, regardless of which stage of the relocation we are
	 * in.
	 */
	अगर (root->reloc_root) अणु
		reloc_root = root->reloc_root;
		reloc_root->last_trans = trans->transid;
		वापस 0;
	पूर्ण

	/*
	 * We are merging reloc roots, we करो not need new reloc trees.  Also
	 * reloc trees never need their own reloc tree.
	 */
	अगर (!rc->create_reloc_tree ||
	    root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID)
		वापस 0;

	अगर (!trans->reloc_reserved) अणु
		rsv = trans->block_rsv;
		trans->block_rsv = rc->block_rsv;
		clear_rsv = 1;
	पूर्ण
	reloc_root = create_reloc_root(trans, root, root->root_key.objectid);
	अगर (clear_rsv)
		trans->block_rsv = rsv;
	अगर (IS_ERR(reloc_root))
		वापस PTR_ERR(reloc_root);

	ret = __add_reloc_root(reloc_root);
	ASSERT(ret != -EEXIST);
	अगर (ret) अणु
		/* Pairs with create_reloc_root */
		btrfs_put_root(reloc_root);
		वापस ret;
	पूर्ण
	root->reloc_root = btrfs_grab_root(reloc_root);
	वापस 0;
पूर्ण

/*
 * update root item of reloc tree
 */
पूर्णांक btrfs_update_reloc_root(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *reloc_root;
	काष्ठा btrfs_root_item *root_item;
	पूर्णांक ret;

	अगर (!have_reloc_root(root))
		वापस 0;

	reloc_root = root->reloc_root;
	root_item = &reloc_root->root_item;

	/*
	 * We are probably ok here, but __del_reloc_root() will drop its ref of
	 * the root.  We have the ref क्रम root->reloc_root, but just in हाल
	 * hold it जबतक we update the reloc root.
	 */
	btrfs_grab_root(reloc_root);

	/* root->reloc_root will stay until current relocation finished */
	अगर (fs_info->reloc_ctl->merge_reloc_tree &&
	    btrfs_root_refs(root_item) == 0) अणु
		set_bit(BTRFS_ROOT_DEAD_RELOC_TREE, &root->state);
		/*
		 * Mark the tree as dead beक्रमe we change reloc_root so
		 * have_reloc_root will not touch it from now on.
		 */
		smp_wmb();
		__del_reloc_root(reloc_root);
	पूर्ण

	अगर (reloc_root->commit_root != reloc_root->node) अणु
		__update_reloc_root(reloc_root);
		btrfs_set_root_node(root_item, reloc_root->node);
		मुक्त_extent_buffer(reloc_root->commit_root);
		reloc_root->commit_root = btrfs_root_node(reloc_root);
	पूर्ण

	ret = btrfs_update_root(trans, fs_info->tree_root,
				&reloc_root->root_key, root_item);
	btrfs_put_root(reloc_root);
	वापस ret;
पूर्ण

/*
 * helper to find first cached inode with inode number >= objectid
 * in a subvolume
 */
अटल काष्ठा inode *find_next_inode(काष्ठा btrfs_root *root, u64 objectid)
अणु
	काष्ठा rb_node *node;
	काष्ठा rb_node *prev;
	काष्ठा btrfs_inode *entry;
	काष्ठा inode *inode;

	spin_lock(&root->inode_lock);
again:
	node = root->inode_tree.rb_node;
	prev = शून्य;
	जबतक (node) अणु
		prev = node;
		entry = rb_entry(node, काष्ठा btrfs_inode, rb_node);

		अगर (objectid < btrfs_ino(entry))
			node = node->rb_left;
		अन्यथा अगर (objectid > btrfs_ino(entry))
			node = node->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (!node) अणु
		जबतक (prev) अणु
			entry = rb_entry(prev, काष्ठा btrfs_inode, rb_node);
			अगर (objectid <= btrfs_ino(entry)) अणु
				node = prev;
				अवरोध;
			पूर्ण
			prev = rb_next(prev);
		पूर्ण
	पूर्ण
	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा btrfs_inode, rb_node);
		inode = igrab(&entry->vfs_inode);
		अगर (inode) अणु
			spin_unlock(&root->inode_lock);
			वापस inode;
		पूर्ण

		objectid = btrfs_ino(entry) + 1;
		अगर (cond_resched_lock(&root->inode_lock))
			जाओ again;

		node = rb_next(node);
	पूर्ण
	spin_unlock(&root->inode_lock);
	वापस शून्य;
पूर्ण

/*
 * get new location of data
 */
अटल पूर्णांक get_new_location(काष्ठा inode *reloc_inode, u64 *new_bytenr,
			    u64 bytenr, u64 num_bytes)
अणु
	काष्ठा btrfs_root *root = BTRFS_I(reloc_inode)->root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा extent_buffer *leaf;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	bytenr -= BTRFS_I(reloc_inode)->index_cnt;
	ret = btrfs_lookup_file_extent(शून्य, root, path,
			btrfs_ino(BTRFS_I(reloc_inode)), bytenr, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	fi = btrfs_item_ptr(leaf, path->slots[0],
			    काष्ठा btrfs_file_extent_item);

	BUG_ON(btrfs_file_extent_offset(leaf, fi) ||
	       btrfs_file_extent_compression(leaf, fi) ||
	       btrfs_file_extent_encryption(leaf, fi) ||
	       btrfs_file_extent_other_encoding(leaf, fi));

	अगर (num_bytes != btrfs_file_extent_disk_num_bytes(leaf, fi)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	*new_bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
	ret = 0;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * update file extent items in the tree leaf to poपूर्णांक to
 * the new locations.
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक replace_file_extents(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा reloc_control *rc,
			 काष्ठा btrfs_root *root,
			 काष्ठा extent_buffer *leaf)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा inode *inode = शून्य;
	u64 parent;
	u64 bytenr;
	u64 new_bytenr = 0;
	u64 num_bytes;
	u64 end;
	u32 nritems;
	u32 i;
	पूर्णांक ret = 0;
	पूर्णांक first = 1;
	पूर्णांक dirty = 0;

	अगर (rc->stage != UPDATE_DATA_PTRS)
		वापस 0;

	/* reloc trees always use full backref */
	अगर (root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID)
		parent = leaf->start;
	अन्यथा
		parent = 0;

	nritems = btrfs_header_nritems(leaf);
	क्रम (i = 0; i < nritems; i++) अणु
		काष्ठा btrfs_ref ref = अणु 0 पूर्ण;

		cond_resched();
		btrfs_item_key_to_cpu(leaf, &key, i);
		अगर (key.type != BTRFS_EXTENT_DATA_KEY)
			जारी;
		fi = btrfs_item_ptr(leaf, i, काष्ठा btrfs_file_extent_item);
		अगर (btrfs_file_extent_type(leaf, fi) ==
		    BTRFS_खाता_EXTENT_INLINE)
			जारी;
		bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
		num_bytes = btrfs_file_extent_disk_num_bytes(leaf, fi);
		अगर (bytenr == 0)
			जारी;
		अगर (!in_range(bytenr, rc->block_group->start,
			      rc->block_group->length))
			जारी;

		/*
		 * अगर we are modअगरying block in fs tree, रुको क्रम पढ़ोpage
		 * to complete and drop the extent cache
		 */
		अगर (root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID) अणु
			अगर (first) अणु
				inode = find_next_inode(root, key.objectid);
				first = 0;
			पूर्ण अन्यथा अगर (inode && btrfs_ino(BTRFS_I(inode)) < key.objectid) अणु
				btrfs_add_delayed_iput(inode);
				inode = find_next_inode(root, key.objectid);
			पूर्ण
			अगर (inode && btrfs_ino(BTRFS_I(inode)) == key.objectid) अणु
				end = key.offset +
				      btrfs_file_extent_num_bytes(leaf, fi);
				WARN_ON(!IS_ALIGNED(key.offset,
						    fs_info->sectorsize));
				WARN_ON(!IS_ALIGNED(end, fs_info->sectorsize));
				end--;
				ret = try_lock_extent(&BTRFS_I(inode)->io_tree,
						      key.offset, end);
				अगर (!ret)
					जारी;

				btrfs_drop_extent_cache(BTRFS_I(inode),
						key.offset,	end, 1);
				unlock_extent(&BTRFS_I(inode)->io_tree,
					      key.offset, end);
			पूर्ण
		पूर्ण

		ret = get_new_location(rc->data_inode, &new_bytenr,
				       bytenr, num_bytes);
		अगर (ret) अणु
			/*
			 * Don't have to abort since we've not changed anything
			 * in the file extent yet.
			 */
			अवरोध;
		पूर्ण

		btrfs_set_file_extent_disk_bytenr(leaf, fi, new_bytenr);
		dirty = 1;

		key.offset -= btrfs_file_extent_offset(leaf, fi);
		btrfs_init_generic_ref(&ref, BTRFS_ADD_DELAYED_REF, new_bytenr,
				       num_bytes, parent);
		ref.real_root = root->root_key.objectid;
		btrfs_init_data_ref(&ref, btrfs_header_owner(leaf),
				    key.objectid, key.offset);
		ret = btrfs_inc_extent_ref(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			अवरोध;
		पूर्ण

		btrfs_init_generic_ref(&ref, BTRFS_DROP_DELAYED_REF, bytenr,
				       num_bytes, parent);
		ref.real_root = root->root_key.objectid;
		btrfs_init_data_ref(&ref, btrfs_header_owner(leaf),
				    key.objectid, key.offset);
		ret = btrfs_मुक्त_extent(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (dirty)
		btrfs_mark_buffer_dirty(leaf);
	अगर (inode)
		btrfs_add_delayed_iput(inode);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक स_भेद_node_keys(काष्ठा extent_buffer *eb, पूर्णांक slot,
		     काष्ठा btrfs_path *path, पूर्णांक level)
अणु
	काष्ठा btrfs_disk_key key1;
	काष्ठा btrfs_disk_key key2;
	btrfs_node_key(eb, &key1, slot);
	btrfs_node_key(path->nodes[level], &key2, path->slots[level]);
	वापस स_भेद(&key1, &key2, माप(key1));
पूर्ण

/*
 * try to replace tree blocks in fs tree with the new blocks
 * in reloc tree. tree blocks haven't been modअगरied since the
 * reloc tree was create can be replaced.
 *
 * अगर a block was replaced, level of the block + 1 is वापसed.
 * अगर no block got replaced, 0 is वापसed. अगर there are other
 * errors, a negative error number is वापसed.
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक replace_path(काष्ठा btrfs_trans_handle *trans, काष्ठा reloc_control *rc,
		 काष्ठा btrfs_root *dest, काष्ठा btrfs_root *src,
		 काष्ठा btrfs_path *path, काष्ठा btrfs_key *next_key,
		 पूर्णांक lowest_level, पूर्णांक max_level)
अणु
	काष्ठा btrfs_fs_info *fs_info = dest->fs_info;
	काष्ठा extent_buffer *eb;
	काष्ठा extent_buffer *parent;
	काष्ठा btrfs_ref ref = अणु 0 पूर्ण;
	काष्ठा btrfs_key key;
	u64 old_bytenr;
	u64 new_bytenr;
	u64 old_ptr_gen;
	u64 new_ptr_gen;
	u64 last_snapshot;
	u32 blocksize;
	पूर्णांक cow = 0;
	पूर्णांक level;
	पूर्णांक ret;
	पूर्णांक slot;

	ASSERT(src->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID);
	ASSERT(dest->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID);

	last_snapshot = btrfs_root_last_snapshot(&src->root_item);
again:
	slot = path->slots[lowest_level];
	btrfs_node_key_to_cpu(path->nodes[lowest_level], &key, slot);

	eb = btrfs_lock_root_node(dest);
	level = btrfs_header_level(eb);

	अगर (level < lowest_level) अणु
		btrfs_tree_unlock(eb);
		मुक्त_extent_buffer(eb);
		वापस 0;
	पूर्ण

	अगर (cow) अणु
		ret = btrfs_cow_block(trans, dest, eb, शून्य, 0, &eb,
				      BTRFS_NESTING_COW);
		अगर (ret) अणु
			btrfs_tree_unlock(eb);
			मुक्त_extent_buffer(eb);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (next_key) अणु
		next_key->objectid = (u64)-1;
		next_key->type = (u8)-1;
		next_key->offset = (u64)-1;
	पूर्ण

	parent = eb;
	जबतक (1) अणु
		level = btrfs_header_level(parent);
		ASSERT(level >= lowest_level);

		ret = btrfs_bin_search(parent, &key, &slot);
		अगर (ret < 0)
			अवरोध;
		अगर (ret && slot > 0)
			slot--;

		अगर (next_key && slot + 1 < btrfs_header_nritems(parent))
			btrfs_node_key_to_cpu(parent, next_key, slot + 1);

		old_bytenr = btrfs_node_blockptr(parent, slot);
		blocksize = fs_info->nodesize;
		old_ptr_gen = btrfs_node_ptr_generation(parent, slot);

		अगर (level <= max_level) अणु
			eb = path->nodes[level];
			new_bytenr = btrfs_node_blockptr(eb,
							path->slots[level]);
			new_ptr_gen = btrfs_node_ptr_generation(eb,
							path->slots[level]);
		पूर्ण अन्यथा अणु
			new_bytenr = 0;
			new_ptr_gen = 0;
		पूर्ण

		अगर (WARN_ON(new_bytenr > 0 && new_bytenr == old_bytenr)) अणु
			ret = level;
			अवरोध;
		पूर्ण

		अगर (new_bytenr == 0 || old_ptr_gen > last_snapshot ||
		    स_भेद_node_keys(parent, slot, path, level)) अणु
			अगर (level <= lowest_level) अणु
				ret = 0;
				अवरोध;
			पूर्ण

			eb = btrfs_पढ़ो_node_slot(parent, slot);
			अगर (IS_ERR(eb)) अणु
				ret = PTR_ERR(eb);
				अवरोध;
			पूर्ण
			btrfs_tree_lock(eb);
			अगर (cow) अणु
				ret = btrfs_cow_block(trans, dest, eb, parent,
						      slot, &eb,
						      BTRFS_NESTING_COW);
				अगर (ret) अणु
					btrfs_tree_unlock(eb);
					मुक्त_extent_buffer(eb);
					अवरोध;
				पूर्ण
			पूर्ण

			btrfs_tree_unlock(parent);
			मुक्त_extent_buffer(parent);

			parent = eb;
			जारी;
		पूर्ण

		अगर (!cow) अणु
			btrfs_tree_unlock(parent);
			मुक्त_extent_buffer(parent);
			cow = 1;
			जाओ again;
		पूर्ण

		btrfs_node_key_to_cpu(path->nodes[level], &key,
				      path->slots[level]);
		btrfs_release_path(path);

		path->lowest_level = level;
		ret = btrfs_search_slot(trans, src, &key, path, 0, 1);
		path->lowest_level = 0;
		अगर (ret) अणु
			अगर (ret > 0)
				ret = -ENOENT;
			अवरोध;
		पूर्ण

		/*
		 * Info qgroup to trace both subtrees.
		 *
		 * We must trace both trees.
		 * 1) Tree reloc subtree
		 *    If not traced, we will leak data numbers
		 * 2) Fs subtree
		 *    If not traced, we will द्विगुन count old data
		 *
		 * We करोn't scan the subtree right now, but only record
		 * the swapped tree blocks.
		 * The real subtree rescan is delayed until we have new
		 * CoW on the subtree root node beक्रमe transaction commit.
		 */
		ret = btrfs_qgroup_add_swapped_blocks(trans, dest,
				rc->block_group, parent, slot,
				path->nodes[level], path->slots[level],
				last_snapshot);
		अगर (ret < 0)
			अवरोध;
		/*
		 * swap blocks in fs tree and reloc tree.
		 */
		btrfs_set_node_blockptr(parent, slot, new_bytenr);
		btrfs_set_node_ptr_generation(parent, slot, new_ptr_gen);
		btrfs_mark_buffer_dirty(parent);

		btrfs_set_node_blockptr(path->nodes[level],
					path->slots[level], old_bytenr);
		btrfs_set_node_ptr_generation(path->nodes[level],
					      path->slots[level], old_ptr_gen);
		btrfs_mark_buffer_dirty(path->nodes[level]);

		btrfs_init_generic_ref(&ref, BTRFS_ADD_DELAYED_REF, old_bytenr,
				       blocksize, path->nodes[level]->start);
		ref.skip_qgroup = true;
		btrfs_init_tree_ref(&ref, level - 1, src->root_key.objectid);
		ret = btrfs_inc_extent_ref(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			अवरोध;
		पूर्ण
		btrfs_init_generic_ref(&ref, BTRFS_ADD_DELAYED_REF, new_bytenr,
				       blocksize, 0);
		ref.skip_qgroup = true;
		btrfs_init_tree_ref(&ref, level - 1, dest->root_key.objectid);
		ret = btrfs_inc_extent_ref(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			अवरोध;
		पूर्ण

		btrfs_init_generic_ref(&ref, BTRFS_DROP_DELAYED_REF, new_bytenr,
				       blocksize, path->nodes[level]->start);
		btrfs_init_tree_ref(&ref, level - 1, src->root_key.objectid);
		ref.skip_qgroup = true;
		ret = btrfs_मुक्त_extent(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			अवरोध;
		पूर्ण

		btrfs_init_generic_ref(&ref, BTRFS_DROP_DELAYED_REF, old_bytenr,
				       blocksize, 0);
		btrfs_init_tree_ref(&ref, level - 1, dest->root_key.objectid);
		ref.skip_qgroup = true;
		ret = btrfs_मुक्त_extent(trans, &ref);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			अवरोध;
		पूर्ण

		btrfs_unlock_up_safe(path, 0);

		ret = level;
		अवरोध;
	पूर्ण
	btrfs_tree_unlock(parent);
	मुक्त_extent_buffer(parent);
	वापस ret;
पूर्ण

/*
 * helper to find next relocated block in reloc tree
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक walk_up_reloc_tree(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
		       पूर्णांक *level)
अणु
	काष्ठा extent_buffer *eb;
	पूर्णांक i;
	u64 last_snapshot;
	u32 nritems;

	last_snapshot = btrfs_root_last_snapshot(&root->root_item);

	क्रम (i = 0; i < *level; i++) अणु
		मुक्त_extent_buffer(path->nodes[i]);
		path->nodes[i] = शून्य;
	पूर्ण

	क्रम (i = *level; i < BTRFS_MAX_LEVEL && path->nodes[i]; i++) अणु
		eb = path->nodes[i];
		nritems = btrfs_header_nritems(eb);
		जबतक (path->slots[i] + 1 < nritems) अणु
			path->slots[i]++;
			अगर (btrfs_node_ptr_generation(eb, path->slots[i]) <=
			    last_snapshot)
				जारी;

			*level = i;
			वापस 0;
		पूर्ण
		मुक्त_extent_buffer(path->nodes[i]);
		path->nodes[i] = शून्य;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * walk करोwn reloc tree to find relocated block of lowest level
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक walk_करोwn_reloc_tree(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			 पूर्णांक *level)
अणु
	काष्ठा extent_buffer *eb = शून्य;
	पूर्णांक i;
	u64 ptr_gen = 0;
	u64 last_snapshot;
	u32 nritems;

	last_snapshot = btrfs_root_last_snapshot(&root->root_item);

	क्रम (i = *level; i > 0; i--) अणु
		eb = path->nodes[i];
		nritems = btrfs_header_nritems(eb);
		जबतक (path->slots[i] < nritems) अणु
			ptr_gen = btrfs_node_ptr_generation(eb, path->slots[i]);
			अगर (ptr_gen > last_snapshot)
				अवरोध;
			path->slots[i]++;
		पूर्ण
		अगर (path->slots[i] >= nritems) अणु
			अगर (i == *level)
				अवरोध;
			*level = i + 1;
			वापस 0;
		पूर्ण
		अगर (i == 1) अणु
			*level = i;
			वापस 0;
		पूर्ण

		eb = btrfs_पढ़ो_node_slot(eb, path->slots[i]);
		अगर (IS_ERR(eb))
			वापस PTR_ERR(eb);
		BUG_ON(btrfs_header_level(eb) != i - 1);
		path->nodes[i - 1] = eb;
		path->slots[i - 1] = 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * invalidate extent cache क्रम file extents whose key in range of
 * [min_key, max_key)
 */
अटल पूर्णांक invalidate_extent_cache(काष्ठा btrfs_root *root,
				   काष्ठा btrfs_key *min_key,
				   काष्ठा btrfs_key *max_key)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा inode *inode = शून्य;
	u64 objectid;
	u64 start, end;
	u64 ino;

	objectid = min_key->objectid;
	जबतक (1) अणु
		cond_resched();
		iput(inode);

		अगर (objectid > max_key->objectid)
			अवरोध;

		inode = find_next_inode(root, objectid);
		अगर (!inode)
			अवरोध;
		ino = btrfs_ino(BTRFS_I(inode));

		अगर (ino > max_key->objectid) अणु
			iput(inode);
			अवरोध;
		पूर्ण

		objectid = ino + 1;
		अगर (!S_ISREG(inode->i_mode))
			जारी;

		अगर (unlikely(min_key->objectid == ino)) अणु
			अगर (min_key->type > BTRFS_EXTENT_DATA_KEY)
				जारी;
			अगर (min_key->type < BTRFS_EXTENT_DATA_KEY)
				start = 0;
			अन्यथा अणु
				start = min_key->offset;
				WARN_ON(!IS_ALIGNED(start, fs_info->sectorsize));
			पूर्ण
		पूर्ण अन्यथा अणु
			start = 0;
		पूर्ण

		अगर (unlikely(max_key->objectid == ino)) अणु
			अगर (max_key->type < BTRFS_EXTENT_DATA_KEY)
				जारी;
			अगर (max_key->type > BTRFS_EXTENT_DATA_KEY) अणु
				end = (u64)-1;
			पूर्ण अन्यथा अणु
				अगर (max_key->offset == 0)
					जारी;
				end = max_key->offset;
				WARN_ON(!IS_ALIGNED(end, fs_info->sectorsize));
				end--;
			पूर्ण
		पूर्ण अन्यथा अणु
			end = (u64)-1;
		पूर्ण

		/* the lock_extent रुकोs क्रम पढ़ोpage to complete */
		lock_extent(&BTRFS_I(inode)->io_tree, start, end);
		btrfs_drop_extent_cache(BTRFS_I(inode), start, end, 1);
		unlock_extent(&BTRFS_I(inode)->io_tree, start, end);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक find_next_key(काष्ठा btrfs_path *path, पूर्णांक level,
			 काष्ठा btrfs_key *key)

अणु
	जबतक (level < BTRFS_MAX_LEVEL) अणु
		अगर (!path->nodes[level])
			अवरोध;
		अगर (path->slots[level] + 1 <
		    btrfs_header_nritems(path->nodes[level])) अणु
			btrfs_node_key_to_cpu(path->nodes[level], key,
					      path->slots[level] + 1);
			वापस 0;
		पूर्ण
		level++;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Insert current subvolume पूर्णांकo reloc_control::dirty_subvol_roots
 */
अटल पूर्णांक insert_dirty_subvol(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा reloc_control *rc,
			       काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_root *reloc_root = root->reloc_root;
	काष्ठा btrfs_root_item *reloc_root_item;
	पूर्णांक ret;

	/* @root must be a subvolume tree root with a valid reloc tree */
	ASSERT(root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID);
	ASSERT(reloc_root);

	reloc_root_item = &reloc_root->root_item;
	स_रखो(&reloc_root_item->drop_progress, 0,
		माप(reloc_root_item->drop_progress));
	btrfs_set_root_drop_level(reloc_root_item, 0);
	btrfs_set_root_refs(reloc_root_item, 0);
	ret = btrfs_update_reloc_root(trans, root);
	अगर (ret)
		वापस ret;

	अगर (list_empty(&root->reloc_dirty_list)) अणु
		btrfs_grab_root(root);
		list_add_tail(&root->reloc_dirty_list, &rc->dirty_subvol_roots);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक clean_dirty_subvols(काष्ठा reloc_control *rc)
अणु
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_root *next;
	पूर्णांक ret = 0;
	पूर्णांक ret2;

	list_क्रम_each_entry_safe(root, next, &rc->dirty_subvol_roots,
				 reloc_dirty_list) अणु
		अगर (root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID) अणु
			/* Merged subvolume, cleanup its reloc root */
			काष्ठा btrfs_root *reloc_root = root->reloc_root;

			list_del_init(&root->reloc_dirty_list);
			root->reloc_root = शून्य;
			/*
			 * Need barrier to ensure clear_bit() only happens after
			 * root->reloc_root = शून्य. Pairs with have_reloc_root.
			 */
			smp_wmb();
			clear_bit(BTRFS_ROOT_DEAD_RELOC_TREE, &root->state);
			अगर (reloc_root) अणु
				/*
				 * btrfs_drop_snapshot drops our ref we hold क्रम
				 * ->reloc_root.  If it fails however we must
				 * drop the ref ourselves.
				 */
				ret2 = btrfs_drop_snapshot(reloc_root, 0, 1);
				अगर (ret2 < 0) अणु
					btrfs_put_root(reloc_root);
					अगर (!ret)
						ret = ret2;
				पूर्ण
			पूर्ण
			btrfs_put_root(root);
		पूर्ण अन्यथा अणु
			/* Orphan reloc tree, just clean it up */
			ret2 = btrfs_drop_snapshot(root, 0, 1);
			अगर (ret2 < 0) अणु
				btrfs_put_root(root);
				अगर (!ret)
					ret = ret2;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * merge the relocated tree blocks in reloc tree with corresponding
 * fs tree.
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक merge_reloc_root(काष्ठा reloc_control *rc,
					       काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key next_key;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	काष्ठा btrfs_root *reloc_root;
	काष्ठा btrfs_root_item *root_item;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	पूर्णांक reserve_level;
	पूर्णांक level;
	पूर्णांक max_level;
	पूर्णांक replaced = 0;
	पूर्णांक ret = 0;
	u32 min_reserved;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	path->पढ़ोa = READA_FORWARD;

	reloc_root = root->reloc_root;
	root_item = &reloc_root->root_item;

	अगर (btrfs_disk_key_objectid(&root_item->drop_progress) == 0) अणु
		level = btrfs_root_level(root_item);
		atomic_inc(&reloc_root->node->refs);
		path->nodes[level] = reloc_root->node;
		path->slots[level] = 0;
	पूर्ण अन्यथा अणु
		btrfs_disk_key_to_cpu(&key, &root_item->drop_progress);

		level = btrfs_root_drop_level(root_item);
		BUG_ON(level == 0);
		path->lowest_level = level;
		ret = btrfs_search_slot(शून्य, reloc_root, &key, path, 0, 0);
		path->lowest_level = 0;
		अगर (ret < 0) अणु
			btrfs_मुक्त_path(path);
			वापस ret;
		पूर्ण

		btrfs_node_key_to_cpu(path->nodes[level], &next_key,
				      path->slots[level]);
		WARN_ON(स_भेद(&key, &next_key, माप(key)));

		btrfs_unlock_up_safe(path, 0);
	पूर्ण

	/*
	 * In merge_reloc_root(), we modअगरy the upper level poपूर्णांकer to swap the
	 * tree blocks between reloc tree and subvolume tree.  Thus क्रम tree
	 * block COW, we COW at most from level 1 to root level क्रम each tree.
	 *
	 * Thus the needed metadata size is at most root_level * nodesize,
	 * and * 2 since we have two trees to COW.
	 */
	reserve_level = max_t(पूर्णांक, 1, btrfs_root_level(root_item));
	min_reserved = fs_info->nodesize * reserve_level * 2;
	स_रखो(&next_key, 0, माप(next_key));

	जबतक (1) अणु
		ret = btrfs_block_rsv_refill(root, rc->block_rsv, min_reserved,
					     BTRFS_RESERVE_FLUSH_LIMIT);
		अगर (ret)
			जाओ out;
		trans = btrfs_start_transaction(root, 0);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			trans = शून्य;
			जाओ out;
		पूर्ण

		/*
		 * At this poपूर्णांक we no दीर्घer have a reloc_control, so we can't
		 * depend on btrfs_init_reloc_root to update our last_trans.
		 *
		 * But that's ok, we started the trans handle on our
		 * corresponding fs_root, which means it's been added to the
		 * dirty list.  At commit समय we'll still call
		 * btrfs_update_reloc_root() and update our root item
		 * appropriately.
		 */
		reloc_root->last_trans = trans->transid;
		trans->block_rsv = rc->block_rsv;

		replaced = 0;
		max_level = level;

		ret = walk_करोwn_reloc_tree(reloc_root, path, &level);
		अगर (ret < 0)
			जाओ out;
		अगर (ret > 0)
			अवरोध;

		अगर (!find_next_key(path, level, &key) &&
		    btrfs_comp_cpu_keys(&next_key, &key) >= 0) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = replace_path(trans, rc, root, reloc_root, path,
					   &next_key, level, max_level);
		पूर्ण
		अगर (ret < 0)
			जाओ out;
		अगर (ret > 0) अणु
			level = ret;
			btrfs_node_key_to_cpu(path->nodes[level], &key,
					      path->slots[level]);
			replaced = 1;
		पूर्ण

		ret = walk_up_reloc_tree(reloc_root, path, &level);
		अगर (ret > 0)
			अवरोध;

		BUG_ON(level == 0);
		/*
		 * save the merging progress in the drop_progress.
		 * this is OK since root refs == 1 in this हाल.
		 */
		btrfs_node_key(path->nodes[level], &root_item->drop_progress,
			       path->slots[level]);
		btrfs_set_root_drop_level(root_item, level);

		btrfs_end_transaction_throttle(trans);
		trans = शून्य;

		btrfs_btree_balance_dirty(fs_info);

		अगर (replaced && rc->stage == UPDATE_DATA_PTRS)
			invalidate_extent_cache(root, &key, &next_key);
	पूर्ण

	/*
	 * handle the हाल only one block in the fs tree need to be
	 * relocated and the block is tree root.
	 */
	leaf = btrfs_lock_root_node(root);
	ret = btrfs_cow_block(trans, root, leaf, शून्य, 0, &leaf,
			      BTRFS_NESTING_COW);
	btrfs_tree_unlock(leaf);
	मुक्त_extent_buffer(leaf);
out:
	btrfs_मुक्त_path(path);

	अगर (ret == 0) अणु
		ret = insert_dirty_subvol(trans, rc, root);
		अगर (ret)
			btrfs_पात_transaction(trans, ret);
	पूर्ण

	अगर (trans)
		btrfs_end_transaction_throttle(trans);

	btrfs_btree_balance_dirty(fs_info);

	अगर (replaced && rc->stage == UPDATE_DATA_PTRS)
		invalidate_extent_cache(root, &key, &next_key);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक prepare_to_merge(काष्ठा reloc_control *rc, पूर्णांक err)
अणु
	काष्ठा btrfs_root *root = rc->extent_root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_root *reloc_root;
	काष्ठा btrfs_trans_handle *trans;
	LIST_HEAD(reloc_roots);
	u64 num_bytes = 0;
	पूर्णांक ret;

	mutex_lock(&fs_info->reloc_mutex);
	rc->merging_rsv_size += fs_info->nodesize * (BTRFS_MAX_LEVEL - 1) * 2;
	rc->merging_rsv_size += rc->nodes_relocated * 2;
	mutex_unlock(&fs_info->reloc_mutex);

again:
	अगर (!err) अणु
		num_bytes = rc->merging_rsv_size;
		ret = btrfs_block_rsv_add(root, rc->block_rsv, num_bytes,
					  BTRFS_RESERVE_FLUSH_ALL);
		अगर (ret)
			err = ret;
	पूर्ण

	trans = btrfs_join_transaction(rc->extent_root);
	अगर (IS_ERR(trans)) अणु
		अगर (!err)
			btrfs_block_rsv_release(fs_info, rc->block_rsv,
						num_bytes, शून्य);
		वापस PTR_ERR(trans);
	पूर्ण

	अगर (!err) अणु
		अगर (num_bytes != rc->merging_rsv_size) अणु
			btrfs_end_transaction(trans);
			btrfs_block_rsv_release(fs_info, rc->block_rsv,
						num_bytes, शून्य);
			जाओ again;
		पूर्ण
	पूर्ण

	rc->merge_reloc_tree = 1;

	जबतक (!list_empty(&rc->reloc_roots)) अणु
		reloc_root = list_entry(rc->reloc_roots.next,
					काष्ठा btrfs_root, root_list);
		list_del_init(&reloc_root->root_list);

		root = btrfs_get_fs_root(fs_info, reloc_root->root_key.offset,
				false);
		अगर (IS_ERR(root)) अणु
			/*
			 * Even अगर we have an error we need this reloc root
			 * back on our list so we can clean up properly.
			 */
			list_add(&reloc_root->root_list, &reloc_roots);
			btrfs_पात_transaction(trans, (पूर्णांक)PTR_ERR(root));
			अगर (!err)
				err = PTR_ERR(root);
			अवरोध;
		पूर्ण
		ASSERT(root->reloc_root == reloc_root);

		/*
		 * set reference count to 1, so btrfs_recover_relocation
		 * knows it should resumes merging
		 */
		अगर (!err)
			btrfs_set_root_refs(&reloc_root->root_item, 1);
		ret = btrfs_update_reloc_root(trans, root);

		/*
		 * Even अगर we have an error we need this reloc root back on our
		 * list so we can clean up properly.
		 */
		list_add(&reloc_root->root_list, &reloc_roots);
		btrfs_put_root(root);

		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			अगर (!err)
				err = ret;
			अवरोध;
		पूर्ण
	पूर्ण

	list_splice(&reloc_roots, &rc->reloc_roots);

	अगर (!err)
		err = btrfs_commit_transaction(trans);
	अन्यथा
		btrfs_end_transaction(trans);
	वापस err;
पूर्ण

अटल noअंतरभूत_क्रम_stack
व्योम मुक्त_reloc_roots(काष्ठा list_head *list)
अणु
	काष्ठा btrfs_root *reloc_root, *पंचांगp;

	list_क्रम_each_entry_safe(reloc_root, पंचांगp, list, root_list)
		__del_reloc_root(reloc_root);
पूर्ण

अटल noअंतरभूत_क्रम_stack
व्योम merge_reloc_roots(काष्ठा reloc_control *rc)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_root *reloc_root;
	LIST_HEAD(reloc_roots);
	पूर्णांक found = 0;
	पूर्णांक ret = 0;
again:
	root = rc->extent_root;

	/*
	 * this serializes us with btrfs_record_root_in_transaction,
	 * we have to make sure nobody is in the middle of
	 * adding their roots to the list जबतक we are
	 * करोing this splice
	 */
	mutex_lock(&fs_info->reloc_mutex);
	list_splice_init(&rc->reloc_roots, &reloc_roots);
	mutex_unlock(&fs_info->reloc_mutex);

	जबतक (!list_empty(&reloc_roots)) अणु
		found = 1;
		reloc_root = list_entry(reloc_roots.next,
					काष्ठा btrfs_root, root_list);

		root = btrfs_get_fs_root(fs_info, reloc_root->root_key.offset,
					 false);
		अगर (btrfs_root_refs(&reloc_root->root_item) > 0) अणु
			अगर (IS_ERR(root)) अणु
				/*
				 * For recovery we पढ़ो the fs roots on mount,
				 * and अगर we didn't find the root then we marked
				 * the reloc root as a garbage root.  For normal
				 * relocation obviously the root should exist in
				 * memory.  However there's no reason we can't
				 * handle the error properly here just in हाल.
				 */
				ASSERT(0);
				ret = PTR_ERR(root);
				जाओ out;
			पूर्ण
			अगर (root->reloc_root != reloc_root) अणु
				/*
				 * This is actually impossible without something
				 * going really wrong (like weird race condition
				 * or cosmic rays).
				 */
				ASSERT(0);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ret = merge_reloc_root(rc, root);
			btrfs_put_root(root);
			अगर (ret) अणु
				अगर (list_empty(&reloc_root->root_list))
					list_add_tail(&reloc_root->root_list,
						      &reloc_roots);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!IS_ERR(root)) अणु
				अगर (root->reloc_root == reloc_root) अणु
					root->reloc_root = शून्य;
					btrfs_put_root(reloc_root);
				पूर्ण
				clear_bit(BTRFS_ROOT_DEAD_RELOC_TREE,
					  &root->state);
				btrfs_put_root(root);
			पूर्ण

			list_del_init(&reloc_root->root_list);
			/* Don't क्रमget to queue this reloc root क्रम cleanup */
			list_add_tail(&reloc_root->reloc_dirty_list,
				      &rc->dirty_subvol_roots);
		पूर्ण
	पूर्ण

	अगर (found) अणु
		found = 0;
		जाओ again;
	पूर्ण
out:
	अगर (ret) अणु
		btrfs_handle_fs_error(fs_info, ret, शून्य);
		मुक्त_reloc_roots(&reloc_roots);

		/* new reloc root may be added */
		mutex_lock(&fs_info->reloc_mutex);
		list_splice_init(&rc->reloc_roots, &reloc_roots);
		mutex_unlock(&fs_info->reloc_mutex);
		मुक्त_reloc_roots(&reloc_roots);
	पूर्ण

	/*
	 * We used to have
	 *
	 * BUG_ON(!RB_EMPTY_ROOT(&rc->reloc_root_tree.rb_root));
	 *
	 * here, but it's wrong.  If we fail to start the transaction in
	 * prepare_to_merge() we will have only 0 ref reloc roots, none of which
	 * have actually been हटाओd from the reloc_root_tree rb tree.  This is
	 * fine because we're bailing here, and we hold a reference on the root
	 * क्रम the list that holds it, so these roots will be cleaned up when we
	 * करो the reloc_dirty_list afterwards.  Meanजबतक the root->reloc_root
	 * will be cleaned up on unmount.
	 *
	 * The reमुख्यing nodes will be cleaned up by मुक्त_reloc_control.
	 */
पूर्ण

अटल व्योम मुक्त_block_list(काष्ठा rb_root *blocks)
अणु
	काष्ठा tree_block *block;
	काष्ठा rb_node *rb_node;
	जबतक ((rb_node = rb_first(blocks))) अणु
		block = rb_entry(rb_node, काष्ठा tree_block, rb_node);
		rb_erase(rb_node, blocks);
		kमुक्त(block);
	पूर्ण
पूर्ण

अटल पूर्णांक record_reloc_root_in_trans(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_root *reloc_root)
अणु
	काष्ठा btrfs_fs_info *fs_info = reloc_root->fs_info;
	काष्ठा btrfs_root *root;
	पूर्णांक ret;

	अगर (reloc_root->last_trans == trans->transid)
		वापस 0;

	root = btrfs_get_fs_root(fs_info, reloc_root->root_key.offset, false);

	/*
	 * This should succeed, since we can't have a reloc root without having
	 * alपढ़ोy looked up the actual root and created the reloc root क्रम this
	 * root.
	 *
	 * However अगर there's some sort of corruption where we have a ref to a
	 * reloc root without a corresponding root this could वापस ENOENT.
	 */
	अगर (IS_ERR(root)) अणु
		ASSERT(0);
		वापस PTR_ERR(root);
	पूर्ण
	अगर (root->reloc_root != reloc_root) अणु
		ASSERT(0);
		btrfs_err(fs_info,
			  "root %llu has two reloc roots associated with it",
			  reloc_root->root_key.offset);
		btrfs_put_root(root);
		वापस -EUCLEAN;
	पूर्ण
	ret = btrfs_record_root_in_trans(trans, root);
	btrfs_put_root(root);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack
काष्ठा btrfs_root *select_reloc_root(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा reloc_control *rc,
				     काष्ठा btrfs_backref_node *node,
				     काष्ठा btrfs_backref_edge *edges[])
अणु
	काष्ठा btrfs_backref_node *next;
	काष्ठा btrfs_root *root;
	पूर्णांक index = 0;
	पूर्णांक ret;

	next = node;
	जबतक (1) अणु
		cond_resched();
		next = walk_up_backref(next, edges, &index);
		root = next->root;

		/*
		 * If there is no root, then our references क्रम this block are
		 * incomplete, as we should be able to walk all the way up to a
		 * block that is owned by a root.
		 *
		 * This path is only क्रम SHAREABLE roots, so अगर we come upon a
		 * non-SHAREABLE root then we have backrefs that resolve
		 * improperly.
		 *
		 * Both of these हालs indicate file प्रणाली corruption, or a bug
		 * in the backref walking code.
		 */
		अगर (!root) अणु
			ASSERT(0);
			btrfs_err(trans->fs_info,
		"bytenr %llu doesn't have a backref path ending in a root",
				  node->bytenr);
			वापस ERR_PTR(-EUCLEAN);
		पूर्ण
		अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state)) अणु
			ASSERT(0);
			btrfs_err(trans->fs_info,
	"bytenr %llu has multiple refs with one ending in a non-shareable root",
				  node->bytenr);
			वापस ERR_PTR(-EUCLEAN);
		पूर्ण

		अगर (root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID) अणु
			ret = record_reloc_root_in_trans(trans, root);
			अगर (ret)
				वापस ERR_PTR(ret);
			अवरोध;
		पूर्ण

		ret = btrfs_record_root_in_trans(trans, root);
		अगर (ret)
			वापस ERR_PTR(ret);
		root = root->reloc_root;

		/*
		 * We could have raced with another thपढ़ो which failed, so
		 * root->reloc_root may not be set, वापस ENOENT in this हाल.
		 */
		अगर (!root)
			वापस ERR_PTR(-ENOENT);

		अगर (next->new_bytenr != root->node->start) अणु
			/*
			 * We just created the reloc root, so we shouldn't have
			 * ->new_bytenr set and this shouldn't be in the changed
			 *  list.  If it is then we have multiple roots poपूर्णांकing
			 *  at the same bytenr which indicates corruption, or
			 *  we've made a mistake in the backref walking code.
			 */
			ASSERT(next->new_bytenr == 0);
			ASSERT(list_empty(&next->list));
			अगर (next->new_bytenr || !list_empty(&next->list)) अणु
				btrfs_err(trans->fs_info,
	"bytenr %llu possibly has multiple roots pointing at the same bytenr %llu",
					  node->bytenr, next->bytenr);
				वापस ERR_PTR(-EUCLEAN);
			पूर्ण

			next->new_bytenr = root->node->start;
			btrfs_put_root(next->root);
			next->root = btrfs_grab_root(root);
			ASSERT(next->root);
			list_add_tail(&next->list,
				      &rc->backref_cache.changed);
			mark_block_processed(rc, next);
			अवरोध;
		पूर्ण

		WARN_ON(1);
		root = शून्य;
		next = walk_करोwn_backref(edges, &index);
		अगर (!next || next->level <= node->level)
			अवरोध;
	पूर्ण
	अगर (!root) अणु
		/*
		 * This can happen अगर there's fs corruption or if there's a bug
		 * in the backref lookup code.
		 */
		ASSERT(0);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	next = node;
	/* setup backref node path क्रम btrfs_reloc_cow_block */
	जबतक (1) अणु
		rc->backref_cache.path[next->level] = next;
		अगर (--index < 0)
			अवरोध;
		next = edges[index]->node[UPPER];
	पूर्ण
	वापस root;
पूर्ण

/*
 * Select a tree root क्रम relocation.
 *
 * Return शून्य अगर the block is not shareable. We should use करो_relocation() in
 * this हाल.
 *
 * Return a tree root poपूर्णांकer अगर the block is shareable.
 * Return -ENOENT अगर the block is root of reloc tree.
 */
अटल noअंतरभूत_क्रम_stack
काष्ठा btrfs_root *select_one_root(काष्ठा btrfs_backref_node *node)
अणु
	काष्ठा btrfs_backref_node *next;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_root *fs_root = शून्य;
	काष्ठा btrfs_backref_edge *edges[BTRFS_MAX_LEVEL - 1];
	पूर्णांक index = 0;

	next = node;
	जबतक (1) अणु
		cond_resched();
		next = walk_up_backref(next, edges, &index);
		root = next->root;

		/*
		 * This can occur अगर we have incomplete extent refs leading all
		 * the way up a particular path, in this हाल वापस -EUCLEAN.
		 */
		अगर (!root)
			वापस ERR_PTR(-EUCLEAN);

		/* No other choice क्रम non-shareable tree */
		अगर (!test_bit(BTRFS_ROOT_SHAREABLE, &root->state))
			वापस root;

		अगर (root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID)
			fs_root = root;

		अगर (next != node)
			वापस शून्य;

		next = walk_करोwn_backref(edges, &index);
		अगर (!next || next->level <= node->level)
			अवरोध;
	पूर्ण

	अगर (!fs_root)
		वापस ERR_PTR(-ENOENT);
	वापस fs_root;
पूर्ण

अटल noअंतरभूत_क्रम_stack
u64 calcu_metadata_size(काष्ठा reloc_control *rc,
			काष्ठा btrfs_backref_node *node, पूर्णांक reserve)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;
	काष्ठा btrfs_backref_node *next = node;
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा btrfs_backref_edge *edges[BTRFS_MAX_LEVEL - 1];
	u64 num_bytes = 0;
	पूर्णांक index = 0;

	BUG_ON(reserve && node->processed);

	जबतक (next) अणु
		cond_resched();
		जबतक (1) अणु
			अगर (next->processed && (reserve || next != node))
				अवरोध;

			num_bytes += fs_info->nodesize;

			अगर (list_empty(&next->upper))
				अवरोध;

			edge = list_entry(next->upper.next,
					काष्ठा btrfs_backref_edge, list[LOWER]);
			edges[index++] = edge;
			next = edge->node[UPPER];
		पूर्ण
		next = walk_करोwn_backref(edges, &index);
	पूर्ण
	वापस num_bytes;
पूर्ण

अटल पूर्णांक reserve_metadata_space(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा reloc_control *rc,
				  काष्ठा btrfs_backref_node *node)
अणु
	काष्ठा btrfs_root *root = rc->extent_root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 num_bytes;
	पूर्णांक ret;
	u64 पंचांगp;

	num_bytes = calcu_metadata_size(rc, node, 1) * 2;

	trans->block_rsv = rc->block_rsv;
	rc->reserved_bytes += num_bytes;

	/*
	 * We are under a transaction here so we can only करो limited flushing.
	 * If we get an enospc just kick back -EAGAIN so we know to drop the
	 * transaction and try to refill when we can flush all the things.
	 */
	ret = btrfs_block_rsv_refill(root, rc->block_rsv, num_bytes,
				BTRFS_RESERVE_FLUSH_LIMIT);
	अगर (ret) अणु
		पंचांगp = fs_info->nodesize * RELOCATION_RESERVED_NODES;
		जबतक (पंचांगp <= rc->reserved_bytes)
			पंचांगp <<= 1;
		/*
		 * only one thपढ़ो can access block_rsv at this poपूर्णांक,
		 * so we करोn't need hold lock to protect block_rsv.
		 * we expand more reservation size here to allow enough
		 * space क्रम relocation and we will वापस earlier in
		 * enospc हाल.
		 */
		rc->block_rsv->size = पंचांगp + fs_info->nodesize *
				      RELOCATION_RESERVED_NODES;
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * relocate a block tree, and then update poपूर्णांकers in upper level
 * blocks that reference the block to poपूर्णांक to the new location.
 *
 * अगर called by link_to_upper, the block has alपढ़ोy been relocated.
 * in that हाल this function just updates poपूर्णांकers.
 */
अटल पूर्णांक करो_relocation(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा reloc_control *rc,
			 काष्ठा btrfs_backref_node *node,
			 काष्ठा btrfs_key *key,
			 काष्ठा btrfs_path *path, पूर्णांक lowest)
अणु
	काष्ठा btrfs_backref_node *upper;
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा btrfs_backref_edge *edges[BTRFS_MAX_LEVEL - 1];
	काष्ठा btrfs_root *root;
	काष्ठा extent_buffer *eb;
	u32 blocksize;
	u64 bytenr;
	पूर्णांक slot;
	पूर्णांक ret = 0;

	/*
	 * If we are lowest then this is the first समय we're processing this
	 * block, and thus shouldn't have an eb associated with it yet.
	 */
	ASSERT(!lowest || !node->eb);

	path->lowest_level = node->level + 1;
	rc->backref_cache.path[node->level] = node;
	list_क्रम_each_entry(edge, &node->upper, list[LOWER]) अणु
		काष्ठा btrfs_ref ref = अणु 0 पूर्ण;

		cond_resched();

		upper = edge->node[UPPER];
		root = select_reloc_root(trans, rc, upper, edges);
		अगर (IS_ERR(root)) अणु
			ret = PTR_ERR(root);
			जाओ next;
		पूर्ण

		अगर (upper->eb && !upper->locked) अणु
			अगर (!lowest) अणु
				ret = btrfs_bin_search(upper->eb, key, &slot);
				अगर (ret < 0)
					जाओ next;
				BUG_ON(ret);
				bytenr = btrfs_node_blockptr(upper->eb, slot);
				अगर (node->eb->start == bytenr)
					जाओ next;
			पूर्ण
			btrfs_backref_drop_node_buffer(upper);
		पूर्ण

		अगर (!upper->eb) अणु
			ret = btrfs_search_slot(trans, root, key, path, 0, 1);
			अगर (ret) अणु
				अगर (ret > 0)
					ret = -ENOENT;

				btrfs_release_path(path);
				अवरोध;
			पूर्ण

			अगर (!upper->eb) अणु
				upper->eb = path->nodes[upper->level];
				path->nodes[upper->level] = शून्य;
			पूर्ण अन्यथा अणु
				BUG_ON(upper->eb != path->nodes[upper->level]);
			पूर्ण

			upper->locked = 1;
			path->locks[upper->level] = 0;

			slot = path->slots[upper->level];
			btrfs_release_path(path);
		पूर्ण अन्यथा अणु
			ret = btrfs_bin_search(upper->eb, key, &slot);
			अगर (ret < 0)
				जाओ next;
			BUG_ON(ret);
		पूर्ण

		bytenr = btrfs_node_blockptr(upper->eb, slot);
		अगर (lowest) अणु
			अगर (bytenr != node->bytenr) अणु
				btrfs_err(root->fs_info,
		"lowest leaf/node mismatch: bytenr %llu node->bytenr %llu slot %d upper %llu",
					  bytenr, node->bytenr, slot,
					  upper->eb->start);
				ret = -EIO;
				जाओ next;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (node->eb->start == bytenr)
				जाओ next;
		पूर्ण

		blocksize = root->fs_info->nodesize;
		eb = btrfs_पढ़ो_node_slot(upper->eb, slot);
		अगर (IS_ERR(eb)) अणु
			ret = PTR_ERR(eb);
			जाओ next;
		पूर्ण
		btrfs_tree_lock(eb);

		अगर (!node->eb) अणु
			ret = btrfs_cow_block(trans, root, eb, upper->eb,
					      slot, &eb, BTRFS_NESTING_COW);
			btrfs_tree_unlock(eb);
			मुक्त_extent_buffer(eb);
			अगर (ret < 0)
				जाओ next;
			/*
			 * We've just COWed this block, it should have updated
			 * the correct backref node entry.
			 */
			ASSERT(node->eb == eb);
		पूर्ण अन्यथा अणु
			btrfs_set_node_blockptr(upper->eb, slot,
						node->eb->start);
			btrfs_set_node_ptr_generation(upper->eb, slot,
						      trans->transid);
			btrfs_mark_buffer_dirty(upper->eb);

			btrfs_init_generic_ref(&ref, BTRFS_ADD_DELAYED_REF,
					       node->eb->start, blocksize,
					       upper->eb->start);
			ref.real_root = root->root_key.objectid;
			btrfs_init_tree_ref(&ref, node->level,
					    btrfs_header_owner(upper->eb));
			ret = btrfs_inc_extent_ref(trans, &ref);
			अगर (!ret)
				ret = btrfs_drop_subtree(trans, root, eb,
							 upper->eb);
			अगर (ret)
				btrfs_पात_transaction(trans, ret);
		पूर्ण
next:
		अगर (!upper->pending)
			btrfs_backref_drop_node_buffer(upper);
		अन्यथा
			btrfs_backref_unlock_node_buffer(upper);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (!ret && node->pending) अणु
		btrfs_backref_drop_node_buffer(node);
		list_move_tail(&node->list, &rc->backref_cache.changed);
		node->pending = 0;
	पूर्ण

	path->lowest_level = 0;

	/*
	 * We should have allocated all of our space in the block rsv and thus
	 * shouldn't ENOSPC.
	 */
	ASSERT(ret != -ENOSPC);
	वापस ret;
पूर्ण

अटल पूर्णांक link_to_upper(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा reloc_control *rc,
			 काष्ठा btrfs_backref_node *node,
			 काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_key key;

	btrfs_node_key_to_cpu(node->eb, &key, 0);
	वापस करो_relocation(trans, rc, node, &key, path, 0);
पूर्ण

अटल पूर्णांक finish_pending_nodes(काष्ठा btrfs_trans_handle *trans,
				काष्ठा reloc_control *rc,
				काष्ठा btrfs_path *path, पूर्णांक err)
अणु
	LIST_HEAD(list);
	काष्ठा btrfs_backref_cache *cache = &rc->backref_cache;
	काष्ठा btrfs_backref_node *node;
	पूर्णांक level;
	पूर्णांक ret;

	क्रम (level = 0; level < BTRFS_MAX_LEVEL; level++) अणु
		जबतक (!list_empty(&cache->pending[level])) अणु
			node = list_entry(cache->pending[level].next,
					  काष्ठा btrfs_backref_node, list);
			list_move_tail(&node->list, &list);
			BUG_ON(!node->pending);

			अगर (!err) अणु
				ret = link_to_upper(trans, rc, node, path);
				अगर (ret < 0)
					err = ret;
			पूर्ण
		पूर्ण
		list_splice_init(&list, &cache->pending[level]);
	पूर्ण
	वापस err;
पूर्ण

/*
 * mark a block and all blocks directly/indirectly reference the block
 * as processed.
 */
अटल व्योम update_processed_blocks(काष्ठा reloc_control *rc,
				    काष्ठा btrfs_backref_node *node)
अणु
	काष्ठा btrfs_backref_node *next = node;
	काष्ठा btrfs_backref_edge *edge;
	काष्ठा btrfs_backref_edge *edges[BTRFS_MAX_LEVEL - 1];
	पूर्णांक index = 0;

	जबतक (next) अणु
		cond_resched();
		जबतक (1) अणु
			अगर (next->processed)
				अवरोध;

			mark_block_processed(rc, next);

			अगर (list_empty(&next->upper))
				अवरोध;

			edge = list_entry(next->upper.next,
					काष्ठा btrfs_backref_edge, list[LOWER]);
			edges[index++] = edge;
			next = edge->node[UPPER];
		पूर्ण
		next = walk_करोwn_backref(edges, &index);
	पूर्ण
पूर्ण

अटल पूर्णांक tree_block_processed(u64 bytenr, काष्ठा reloc_control *rc)
अणु
	u32 blocksize = rc->extent_root->fs_info->nodesize;

	अगर (test_range_bit(&rc->processed_blocks, bytenr,
			   bytenr + blocksize - 1, EXTENT_सूचीTY, 1, शून्य))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक get_tree_block_key(काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा tree_block *block)
अणु
	काष्ठा extent_buffer *eb;

	eb = पढ़ो_tree_block(fs_info, block->bytenr, block->owner,
			     block->key.offset, block->level, शून्य);
	अगर (IS_ERR(eb)) अणु
		वापस PTR_ERR(eb);
	पूर्ण अन्यथा अगर (!extent_buffer_uptodate(eb)) अणु
		मुक्त_extent_buffer(eb);
		वापस -EIO;
	पूर्ण
	अगर (block->level == 0)
		btrfs_item_key_to_cpu(eb, &block->key, 0);
	अन्यथा
		btrfs_node_key_to_cpu(eb, &block->key, 0);
	मुक्त_extent_buffer(eb);
	block->key_पढ़ोy = 1;
	वापस 0;
पूर्ण

/*
 * helper function to relocate a tree block
 */
अटल पूर्णांक relocate_tree_block(काष्ठा btrfs_trans_handle *trans,
				काष्ठा reloc_control *rc,
				काष्ठा btrfs_backref_node *node,
				काष्ठा btrfs_key *key,
				काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_root *root;
	पूर्णांक ret = 0;

	अगर (!node)
		वापस 0;

	/*
	 * If we fail here we want to drop our backref_node because we are going
	 * to start over and regenerate the tree क्रम it.
	 */
	ret = reserve_metadata_space(trans, rc, node);
	अगर (ret)
		जाओ out;

	BUG_ON(node->processed);
	root = select_one_root(node);
	अगर (IS_ERR(root)) अणु
		ret = PTR_ERR(root);

		/* See explanation in select_one_root क्रम the -EUCLEAN हाल. */
		ASSERT(ret == -ENOENT);
		अगर (ret == -ENOENT) अणु
			ret = 0;
			update_processed_blocks(rc, node);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (root) अणु
		अगर (test_bit(BTRFS_ROOT_SHAREABLE, &root->state)) अणु
			/*
			 * This block was the root block of a root, and this is
			 * the first समय we're processing the block and thus it
			 * should not have had the ->new_bytenr modअगरied and
			 * should have not been included on the changed list.
			 *
			 * However in the हाल of corruption we could have
			 * multiple refs poपूर्णांकing to the same block improperly,
			 * and thus we would trip over these checks.  ASSERT()
			 * क्रम the developer हाल, because it could indicate a
			 * bug in the backref code, however error out क्रम a
			 * normal user in the हाल of corruption.
			 */
			ASSERT(node->new_bytenr == 0);
			ASSERT(list_empty(&node->list));
			अगर (node->new_bytenr || !list_empty(&node->list)) अणु
				btrfs_err(root->fs_info,
				  "bytenr %llu has improper references to it",
					  node->bytenr);
				ret = -EUCLEAN;
				जाओ out;
			पूर्ण
			ret = btrfs_record_root_in_trans(trans, root);
			अगर (ret)
				जाओ out;
			/*
			 * Another thपढ़ो could have failed, need to check अगर we
			 * have reloc_root actually set.
			 */
			अगर (!root->reloc_root) अणु
				ret = -ENOENT;
				जाओ out;
			पूर्ण
			root = root->reloc_root;
			node->new_bytenr = root->node->start;
			btrfs_put_root(node->root);
			node->root = btrfs_grab_root(root);
			ASSERT(node->root);
			list_add_tail(&node->list, &rc->backref_cache.changed);
		पूर्ण अन्यथा अणु
			path->lowest_level = node->level;
			ret = btrfs_search_slot(trans, root, key, path, 0, 1);
			btrfs_release_path(path);
			अगर (ret > 0)
				ret = 0;
		पूर्ण
		अगर (!ret)
			update_processed_blocks(rc, node);
	पूर्ण अन्यथा अणु
		ret = करो_relocation(trans, rc, node, key, path, 1);
	पूर्ण
out:
	अगर (ret || node->level == 0 || node->cowonly)
		btrfs_backref_cleanup_node(&rc->backref_cache, node);
	वापस ret;
पूर्ण

/*
 * relocate a list of blocks
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक relocate_tree_blocks(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा reloc_control *rc, काष्ठा rb_root *blocks)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;
	काष्ठा btrfs_backref_node *node;
	काष्ठा btrfs_path *path;
	काष्ठा tree_block *block;
	काष्ठा tree_block *next;
	पूर्णांक ret;
	पूर्णांक err = 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_blocks;
	पूर्ण

	/* Kick in पढ़ोahead क्रम tree blocks with missing keys */
	rbtree_postorder_क्रम_each_entry_safe(block, next, blocks, rb_node) अणु
		अगर (!block->key_पढ़ोy)
			btrfs_पढ़ोahead_tree_block(fs_info, block->bytenr,
						   block->owner, 0,
						   block->level);
	पूर्ण

	/* Get first keys */
	rbtree_postorder_क्रम_each_entry_safe(block, next, blocks, rb_node) अणु
		अगर (!block->key_पढ़ोy) अणु
			err = get_tree_block_key(fs_info, block);
			अगर (err)
				जाओ out_मुक्त_path;
		पूर्ण
	पूर्ण

	/* Do tree relocation */
	rbtree_postorder_क्रम_each_entry_safe(block, next, blocks, rb_node) अणु
		node = build_backref_tree(rc, &block->key,
					  block->level, block->bytenr);
		अगर (IS_ERR(node)) अणु
			err = PTR_ERR(node);
			जाओ out;
		पूर्ण

		ret = relocate_tree_block(trans, rc, node, &block->key,
					  path);
		अगर (ret < 0) अणु
			err = ret;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	err = finish_pending_nodes(trans, rc, path, err);

out_मुक्त_path:
	btrfs_मुक्त_path(path);
out_मुक्त_blocks:
	मुक्त_block_list(blocks);
	वापस err;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक pपुनः_स्मृति_file_extent_cluster(
				काष्ठा btrfs_inode *inode,
				काष्ठा file_extent_cluster *cluster)
अणु
	u64 alloc_hपूर्णांक = 0;
	u64 start;
	u64 end;
	u64 offset = inode->index_cnt;
	u64 num_bytes;
	पूर्णांक nr;
	पूर्णांक ret = 0;
	u64 pपुनः_स्मृति_start = cluster->start - offset;
	u64 pपुनः_स्मृति_end = cluster->end - offset;
	u64 cur_offset = pपुनः_स्मृति_start;

	BUG_ON(cluster->start != cluster->boundary[0]);
	ret = btrfs_alloc_data_chunk_ondemand(inode,
					      pपुनः_स्मृति_end + 1 - pपुनः_स्मृति_start);
	अगर (ret)
		वापस ret;

	/*
	 * On a zoned fileप्रणाली, we cannot pपुनः_स्मृतिate the file region.
	 * Instead, we dirty and fiemap_ग_लिखो the region.
	 */
	अगर (btrfs_is_zoned(inode->root->fs_info)) अणु
		काष्ठा btrfs_root *root = inode->root;
		काष्ठा btrfs_trans_handle *trans;

		end = cluster->end - offset + 1;
		trans = btrfs_start_transaction(root, 1);
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);

		inode->vfs_inode.i_स_समय = current_समय(&inode->vfs_inode);
		i_size_ग_लिखो(&inode->vfs_inode, end);
		ret = btrfs_update_inode(trans, root, inode);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			btrfs_end_transaction(trans);
			वापस ret;
		पूर्ण

		वापस btrfs_end_transaction(trans);
	पूर्ण

	btrfs_inode_lock(&inode->vfs_inode, 0);
	क्रम (nr = 0; nr < cluster->nr; nr++) अणु
		start = cluster->boundary[nr] - offset;
		अगर (nr + 1 < cluster->nr)
			end = cluster->boundary[nr + 1] - 1 - offset;
		अन्यथा
			end = cluster->end - offset;

		lock_extent(&inode->io_tree, start, end);
		num_bytes = end + 1 - start;
		ret = btrfs_pपुनः_स्मृति_file_range(&inode->vfs_inode, 0, start,
						num_bytes, num_bytes,
						end + 1, &alloc_hपूर्णांक);
		cur_offset = end + 1;
		unlock_extent(&inode->io_tree, start, end);
		अगर (ret)
			अवरोध;
	पूर्ण
	btrfs_inode_unlock(&inode->vfs_inode, 0);

	अगर (cur_offset < pपुनः_स्मृति_end)
		btrfs_मुक्त_reserved_data_space_noquota(inode->root->fs_info,
					       pपुनः_स्मृति_end + 1 - cur_offset);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक setup_extent_mapping(काष्ठा inode *inode, u64 start, u64 end,
			 u64 block_start)
अणु
	काष्ठा extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	काष्ठा extent_map *em;
	पूर्णांक ret = 0;

	em = alloc_extent_map();
	अगर (!em)
		वापस -ENOMEM;

	em->start = start;
	em->len = end + 1 - start;
	em->block_len = em->len;
	em->block_start = block_start;
	set_bit(EXTENT_FLAG_PINNED, &em->flags);

	lock_extent(&BTRFS_I(inode)->io_tree, start, end);
	जबतक (1) अणु
		ग_लिखो_lock(&em_tree->lock);
		ret = add_extent_mapping(em_tree, em, 0);
		ग_लिखो_unlock(&em_tree->lock);
		अगर (ret != -EEXIST) अणु
			मुक्त_extent_map(em);
			अवरोध;
		पूर्ण
		btrfs_drop_extent_cache(BTRFS_I(inode), start, end, 0);
	पूर्ण
	unlock_extent(&BTRFS_I(inode)->io_tree, start, end);
	वापस ret;
पूर्ण

/*
 * Allow error injection to test balance cancellation
 */
noअंतरभूत पूर्णांक btrfs_should_cancel_balance(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस atomic_पढ़ो(&fs_info->balance_cancel_req) ||
		fatal_संकेत_pending(current);
पूर्ण
ALLOW_ERROR_INJECTION(btrfs_should_cancel_balance, TRUE);

अटल पूर्णांक relocate_file_extent_cluster(काष्ठा inode *inode,
					काष्ठा file_extent_cluster *cluster)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	u64 page_start;
	u64 page_end;
	u64 offset = BTRFS_I(inode)->index_cnt;
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ last_index;
	काष्ठा page *page;
	काष्ठा file_ra_state *ra;
	gfp_t mask = btrfs_alloc_ग_लिखो_mask(inode->i_mapping);
	पूर्णांक nr = 0;
	पूर्णांक ret = 0;

	अगर (!cluster->nr)
		वापस 0;

	ra = kzalloc(माप(*ra), GFP_NOFS);
	अगर (!ra)
		वापस -ENOMEM;

	ret = pपुनः_स्मृति_file_extent_cluster(BTRFS_I(inode), cluster);
	अगर (ret)
		जाओ out;

	file_ra_state_init(ra, inode->i_mapping);

	ret = setup_extent_mapping(inode, cluster->start - offset,
				   cluster->end - offset, cluster->start);
	अगर (ret)
		जाओ out;

	index = (cluster->start - offset) >> PAGE_SHIFT;
	last_index = (cluster->end - offset) >> PAGE_SHIFT;
	जबतक (index <= last_index) अणु
		ret = btrfs_delalloc_reserve_metadata(BTRFS_I(inode),
				PAGE_SIZE);
		अगर (ret)
			जाओ out;

		page = find_lock_page(inode->i_mapping, index);
		अगर (!page) अणु
			page_cache_sync_पढ़ोahead(inode->i_mapping,
						  ra, शून्य, index,
						  last_index + 1 - index);
			page = find_or_create_page(inode->i_mapping, index,
						   mask);
			अगर (!page) अणु
				btrfs_delalloc_release_metadata(BTRFS_I(inode),
							PAGE_SIZE, true);
				btrfs_delalloc_release_extents(BTRFS_I(inode),
							PAGE_SIZE);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण
		ret = set_page_extent_mapped(page);
		अगर (ret < 0) अणु
			btrfs_delalloc_release_metadata(BTRFS_I(inode),
							PAGE_SIZE, true);
			btrfs_delalloc_release_extents(BTRFS_I(inode), PAGE_SIZE);
			unlock_page(page);
			put_page(page);
			जाओ out;
		पूर्ण

		अगर (PageReadahead(page)) अणु
			page_cache_async_पढ़ोahead(inode->i_mapping,
						   ra, शून्य, page, index,
						   last_index + 1 - index);
		पूर्ण

		अगर (!PageUptodate(page)) अणु
			btrfs_पढ़ोpage(शून्य, page);
			lock_page(page);
			अगर (!PageUptodate(page)) अणु
				unlock_page(page);
				put_page(page);
				btrfs_delalloc_release_metadata(BTRFS_I(inode),
							PAGE_SIZE, true);
				btrfs_delalloc_release_extents(BTRFS_I(inode),
							       PAGE_SIZE);
				ret = -EIO;
				जाओ out;
			पूर्ण
		पूर्ण

		page_start = page_offset(page);
		page_end = page_start + PAGE_SIZE - 1;

		lock_extent(&BTRFS_I(inode)->io_tree, page_start, page_end);

		अगर (nr < cluster->nr &&
		    page_start + offset == cluster->boundary[nr]) अणु
			set_extent_bits(&BTRFS_I(inode)->io_tree,
					page_start, page_end,
					EXTENT_BOUNDARY);
			nr++;
		पूर्ण

		ret = btrfs_set_extent_delalloc(BTRFS_I(inode), page_start,
						page_end, 0, शून्य);
		अगर (ret) अणु
			unlock_page(page);
			put_page(page);
			btrfs_delalloc_release_metadata(BTRFS_I(inode),
							 PAGE_SIZE, true);
			btrfs_delalloc_release_extents(BTRFS_I(inode),
			                               PAGE_SIZE);

			clear_extent_bits(&BTRFS_I(inode)->io_tree,
					  page_start, page_end,
					  EXTENT_LOCKED | EXTENT_BOUNDARY);
			जाओ out;

		पूर्ण
		set_page_dirty(page);

		unlock_extent(&BTRFS_I(inode)->io_tree,
			      page_start, page_end);
		unlock_page(page);
		put_page(page);

		index++;
		btrfs_delalloc_release_extents(BTRFS_I(inode), PAGE_SIZE);
		balance_dirty_pages_ratelimited(inode->i_mapping);
		btrfs_throttle(fs_info);
		अगर (btrfs_should_cancel_balance(fs_info)) अणु
			ret = -ECANCELED;
			जाओ out;
		पूर्ण
	पूर्ण
	WARN_ON(nr != cluster->nr);
	अगर (btrfs_is_zoned(fs_info) && !ret)
		ret = btrfs_रुको_ordered_range(inode, 0, (u64)-1);
out:
	kमुक्त(ra);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक relocate_data_extent(काष्ठा inode *inode, काष्ठा btrfs_key *extent_key,
			 काष्ठा file_extent_cluster *cluster)
अणु
	पूर्णांक ret;

	अगर (cluster->nr > 0 && extent_key->objectid != cluster->end + 1) अणु
		ret = relocate_file_extent_cluster(inode, cluster);
		अगर (ret)
			वापस ret;
		cluster->nr = 0;
	पूर्ण

	अगर (!cluster->nr)
		cluster->start = extent_key->objectid;
	अन्यथा
		BUG_ON(cluster->nr >= MAX_EXTENTS);
	cluster->end = extent_key->objectid + extent_key->offset - 1;
	cluster->boundary[cluster->nr] = extent_key->objectid;
	cluster->nr++;

	अगर (cluster->nr >= MAX_EXTENTS) अणु
		ret = relocate_file_extent_cluster(inode, cluster);
		अगर (ret)
			वापस ret;
		cluster->nr = 0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * helper to add a tree block to the list.
 * the major work is getting the generation and level of the block
 */
अटल पूर्णांक add_tree_block(काष्ठा reloc_control *rc,
			  काष्ठा btrfs_key *extent_key,
			  काष्ठा btrfs_path *path,
			  काष्ठा rb_root *blocks)
अणु
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा btrfs_tree_block_info *bi;
	काष्ठा tree_block *block;
	काष्ठा rb_node *rb_node;
	u32 item_size;
	पूर्णांक level = -1;
	u64 generation;
	u64 owner = 0;

	eb =  path->nodes[0];
	item_size = btrfs_item_size_nr(eb, path->slots[0]);

	अगर (extent_key->type == BTRFS_METADATA_ITEM_KEY ||
	    item_size >= माप(*ei) + माप(*bi)) अणु
		अचिन्हित दीर्घ ptr = 0, end;

		ei = btrfs_item_ptr(eb, path->slots[0],
				काष्ठा btrfs_extent_item);
		end = (अचिन्हित दीर्घ)ei + item_size;
		अगर (extent_key->type == BTRFS_EXTENT_ITEM_KEY) अणु
			bi = (काष्ठा btrfs_tree_block_info *)(ei + 1);
			level = btrfs_tree_block_level(eb, bi);
			ptr = (अचिन्हित दीर्घ)(bi + 1);
		पूर्ण अन्यथा अणु
			level = (पूर्णांक)extent_key->offset;
			ptr = (अचिन्हित दीर्घ)(ei + 1);
		पूर्ण
		generation = btrfs_extent_generation(eb, ei);

		/*
		 * We're पढ़ोing अक्रमom blocks without knowing their owner ahead
		 * of समय.  This is ok most of the समय, as all reloc roots and
		 * fs roots have the same lock type.  However normal trees करो
		 * not, and the only way to know ahead of समय is to पढ़ो the
		 * अंतरभूत ref offset.  We know it's an fs root अगर
		 *
		 * 1. There's more than one ref.
		 * 2. There's a SHARED_DATA_REF_KEY set.
		 * 3. FULL_BACKREF is set on the flags.
		 *
		 * Otherwise it's safe to assume that the ref offset == the
		 * owner of this block, so we can use that when calling
		 * पढ़ो_tree_block.
		 */
		अगर (btrfs_extent_refs(eb, ei) == 1 &&
		    !(btrfs_extent_flags(eb, ei) &
		      BTRFS_BLOCK_FLAG_FULL_BACKREF) &&
		    ptr < end) अणु
			काष्ठा btrfs_extent_अंतरभूत_ref *iref;
			पूर्णांक type;

			iref = (काष्ठा btrfs_extent_अंतरभूत_ref *)ptr;
			type = btrfs_get_extent_अंतरभूत_ref_type(eb, iref,
							BTRFS_REF_TYPE_BLOCK);
			अगर (type == BTRFS_REF_TYPE_INVALID)
				वापस -EINVAL;
			अगर (type == BTRFS_TREE_BLOCK_REF_KEY)
				owner = btrfs_extent_अंतरभूत_ref_offset(eb, iref);
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(item_size == माप(काष्ठा btrfs_extent_item_v0))) अणु
		btrfs_prपूर्णांक_v0_err(eb->fs_info);
		btrfs_handle_fs_error(eb->fs_info, -EINVAL, शून्य);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	btrfs_release_path(path);

	BUG_ON(level == -1);

	block = kदो_स्मृति(माप(*block), GFP_NOFS);
	अगर (!block)
		वापस -ENOMEM;

	block->bytenr = extent_key->objectid;
	block->key.objectid = rc->extent_root->fs_info->nodesize;
	block->key.offset = generation;
	block->level = level;
	block->key_पढ़ोy = 0;
	block->owner = owner;

	rb_node = rb_simple_insert(blocks, block->bytenr, &block->rb_node);
	अगर (rb_node)
		btrfs_backref_panic(rc->extent_root->fs_info, block->bytenr,
				    -EEXIST);

	वापस 0;
पूर्ण

/*
 * helper to add tree blocks क्रम backref of type BTRFS_SHARED_DATA_REF_KEY
 */
अटल पूर्णांक __add_tree_block(काष्ठा reloc_control *rc,
			    u64 bytenr, u32 blocksize,
			    काष्ठा rb_root *blocks)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक ret;
	bool skinny = btrfs_fs_incompat(fs_info, SKINNY_METADATA);

	अगर (tree_block_processed(bytenr, rc))
		वापस 0;

	अगर (rb_simple_search(blocks, bytenr))
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
again:
	key.objectid = bytenr;
	अगर (skinny) अणु
		key.type = BTRFS_METADATA_ITEM_KEY;
		key.offset = (u64)-1;
	पूर्ण अन्यथा अणु
		key.type = BTRFS_EXTENT_ITEM_KEY;
		key.offset = blocksize;
	पूर्ण

	path->search_commit_root = 1;
	path->skip_locking = 1;
	ret = btrfs_search_slot(शून्य, rc->extent_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	अगर (ret > 0 && skinny) अणु
		अगर (path->slots[0]) अणु
			path->slots[0]--;
			btrfs_item_key_to_cpu(path->nodes[0], &key,
					      path->slots[0]);
			अगर (key.objectid == bytenr &&
			    (key.type == BTRFS_METADATA_ITEM_KEY ||
			     (key.type == BTRFS_EXTENT_ITEM_KEY &&
			      key.offset == blocksize)))
				ret = 0;
		पूर्ण

		अगर (ret) अणु
			skinny = false;
			btrfs_release_path(path);
			जाओ again;
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		ASSERT(ret == 1);
		btrfs_prपूर्णांक_leaf(path->nodes[0]);
		btrfs_err(fs_info,
	     "tree block extent item (%llu) is not found in extent tree",
		     bytenr);
		WARN_ON(1);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = add_tree_block(rc, &key, path, blocks);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक delete_block_group_cache(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_block_group *block_group,
				    काष्ठा inode *inode,
				    u64 ino)
अणु
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret = 0;

	अगर (inode)
		जाओ truncate;

	inode = btrfs_iget(fs_info->sb, ino, root);
	अगर (IS_ERR(inode))
		वापस -ENOENT;

truncate:
	ret = btrfs_check_trunc_cache_मुक्त_space(fs_info,
						 &fs_info->global_block_rsv);
	अगर (ret)
		जाओ out;

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out;
	पूर्ण

	ret = btrfs_truncate_मुक्त_space_cache(trans, block_group, inode);

	btrfs_end_transaction(trans);
	btrfs_btree_balance_dirty(fs_info);
out:
	iput(inode);
	वापस ret;
पूर्ण

/*
 * Locate the मुक्त space cache EXTENT_DATA in root tree leaf and delete the
 * cache inode, to aव्योम मुक्त space cache data extent blocking data relocation.
 */
अटल पूर्णांक delete_v1_space_cache(काष्ठा extent_buffer *leaf,
				 काष्ठा btrfs_block_group *block_group,
				 u64 data_bytenr)
अणु
	u64 space_cache_ino;
	काष्ठा btrfs_file_extent_item *ei;
	काष्ठा btrfs_key key;
	bool found = false;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (btrfs_header_owner(leaf) != BTRFS_ROOT_TREE_OBJECTID)
		वापस 0;

	क्रम (i = 0; i < btrfs_header_nritems(leaf); i++) अणु
		u8 type;

		btrfs_item_key_to_cpu(leaf, &key, i);
		अगर (key.type != BTRFS_EXTENT_DATA_KEY)
			जारी;
		ei = btrfs_item_ptr(leaf, i, काष्ठा btrfs_file_extent_item);
		type = btrfs_file_extent_type(leaf, ei);

		अगर ((type == BTRFS_खाता_EXTENT_REG ||
		     type == BTRFS_खाता_EXTENT_PREALLOC) &&
		    btrfs_file_extent_disk_bytenr(leaf, ei) == data_bytenr) अणु
			found = true;
			space_cache_ino = key.objectid;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		वापस -ENOENT;
	ret = delete_block_group_cache(leaf->fs_info, block_group, शून्य,
					space_cache_ino);
	वापस ret;
पूर्ण

/*
 * helper to find all tree blocks that reference a given data extent
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक add_data_references(काष्ठा reloc_control *rc,
			काष्ठा btrfs_key *extent_key,
			काष्ठा btrfs_path *path,
			काष्ठा rb_root *blocks)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;
	काष्ठा ulist *leaves = शून्य;
	काष्ठा ulist_iterator leaf_uiter;
	काष्ठा ulist_node *ref_node = शून्य;
	स्थिर u32 blocksize = fs_info->nodesize;
	पूर्णांक ret = 0;

	btrfs_release_path(path);
	ret = btrfs_find_all_leafs(शून्य, fs_info, extent_key->objectid,
				   0, &leaves, शून्य, true);
	अगर (ret < 0)
		वापस ret;

	ULIST_ITER_INIT(&leaf_uiter);
	जबतक ((ref_node = ulist_next(leaves, &leaf_uiter))) अणु
		काष्ठा extent_buffer *eb;

		eb = पढ़ो_tree_block(fs_info, ref_node->val, 0, 0, 0, शून्य);
		अगर (IS_ERR(eb)) अणु
			ret = PTR_ERR(eb);
			अवरोध;
		पूर्ण
		ret = delete_v1_space_cache(eb, rc->block_group,
					    extent_key->objectid);
		मुक्त_extent_buffer(eb);
		अगर (ret < 0)
			अवरोध;
		ret = __add_tree_block(rc, ref_node->val, blocksize, blocks);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	अगर (ret < 0)
		मुक्त_block_list(blocks);
	ulist_मुक्त(leaves);
	वापस ret;
पूर्ण

/*
 * helper to find next unprocessed extent
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक find_next_extent(काष्ठा reloc_control *rc, काष्ठा btrfs_path *path,
		     काष्ठा btrfs_key *extent_key)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	u64 start, end, last;
	पूर्णांक ret;

	last = rc->block_group->start + rc->block_group->length;
	जबतक (1) अणु
		cond_resched();
		अगर (rc->search_start >= last) अणु
			ret = 1;
			अवरोध;
		पूर्ण

		key.objectid = rc->search_start;
		key.type = BTRFS_EXTENT_ITEM_KEY;
		key.offset = 0;

		path->search_commit_root = 1;
		path->skip_locking = 1;
		ret = btrfs_search_slot(शून्य, rc->extent_root, &key, path,
					0, 0);
		अगर (ret < 0)
			अवरोध;
next:
		leaf = path->nodes[0];
		अगर (path->slots[0] >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(rc->extent_root, path);
			अगर (ret != 0)
				अवरोध;
			leaf = path->nodes[0];
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		अगर (key.objectid >= last) अणु
			ret = 1;
			अवरोध;
		पूर्ण

		अगर (key.type != BTRFS_EXTENT_ITEM_KEY &&
		    key.type != BTRFS_METADATA_ITEM_KEY) अणु
			path->slots[0]++;
			जाओ next;
		पूर्ण

		अगर (key.type == BTRFS_EXTENT_ITEM_KEY &&
		    key.objectid + key.offset <= rc->search_start) अणु
			path->slots[0]++;
			जाओ next;
		पूर्ण

		अगर (key.type == BTRFS_METADATA_ITEM_KEY &&
		    key.objectid + fs_info->nodesize <=
		    rc->search_start) अणु
			path->slots[0]++;
			जाओ next;
		पूर्ण

		ret = find_first_extent_bit(&rc->processed_blocks,
					    key.objectid, &start, &end,
					    EXTENT_सूचीTY, शून्य);

		अगर (ret == 0 && start <= key.objectid) अणु
			btrfs_release_path(path);
			rc->search_start = end + 1;
		पूर्ण अन्यथा अणु
			अगर (key.type == BTRFS_EXTENT_ITEM_KEY)
				rc->search_start = key.objectid + key.offset;
			अन्यथा
				rc->search_start = key.objectid +
					fs_info->nodesize;
			स_नकल(extent_key, &key, माप(key));
			वापस 0;
		पूर्ण
	पूर्ण
	btrfs_release_path(path);
	वापस ret;
पूर्ण

अटल व्योम set_reloc_control(काष्ठा reloc_control *rc)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;

	mutex_lock(&fs_info->reloc_mutex);
	fs_info->reloc_ctl = rc;
	mutex_unlock(&fs_info->reloc_mutex);
पूर्ण

अटल व्योम unset_reloc_control(काष्ठा reloc_control *rc)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;

	mutex_lock(&fs_info->reloc_mutex);
	fs_info->reloc_ctl = शून्य;
	mutex_unlock(&fs_info->reloc_mutex);
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक prepare_to_relocate(काष्ठा reloc_control *rc)
अणु
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;

	rc->block_rsv = btrfs_alloc_block_rsv(rc->extent_root->fs_info,
					      BTRFS_BLOCK_RSV_TEMP);
	अगर (!rc->block_rsv)
		वापस -ENOMEM;

	स_रखो(&rc->cluster, 0, माप(rc->cluster));
	rc->search_start = rc->block_group->start;
	rc->extents_found = 0;
	rc->nodes_relocated = 0;
	rc->merging_rsv_size = 0;
	rc->reserved_bytes = 0;
	rc->block_rsv->size = rc->extent_root->fs_info->nodesize *
			      RELOCATION_RESERVED_NODES;
	ret = btrfs_block_rsv_refill(rc->extent_root,
				     rc->block_rsv, rc->block_rsv->size,
				     BTRFS_RESERVE_FLUSH_ALL);
	अगर (ret)
		वापस ret;

	rc->create_reloc_tree = 1;
	set_reloc_control(rc);

	trans = btrfs_join_transaction(rc->extent_root);
	अगर (IS_ERR(trans)) अणु
		unset_reloc_control(rc);
		/*
		 * extent tree is not a ref_cow tree and has no reloc_root to
		 * cleanup.  And callers are responsible to मुक्त the above
		 * block rsv.
		 */
		वापस PTR_ERR(trans);
	पूर्ण
	वापस btrfs_commit_transaction(trans);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक relocate_block_group(काष्ठा reloc_control *rc)
अणु
	काष्ठा btrfs_fs_info *fs_info = rc->extent_root->fs_info;
	काष्ठा rb_root blocks = RB_ROOT;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_extent_item *ei;
	u64 flags;
	पूर्णांक ret;
	पूर्णांक err = 0;
	पूर्णांक progress = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	path->पढ़ोa = READA_FORWARD;

	ret = prepare_to_relocate(rc);
	अगर (ret) अणु
		err = ret;
		जाओ out_मुक्त;
	पूर्ण

	जबतक (1) अणु
		rc->reserved_bytes = 0;
		ret = btrfs_block_rsv_refill(rc->extent_root,
					rc->block_rsv, rc->block_rsv->size,
					BTRFS_RESERVE_FLUSH_ALL);
		अगर (ret) अणु
			err = ret;
			अवरोध;
		पूर्ण
		progress++;
		trans = btrfs_start_transaction(rc->extent_root, 0);
		अगर (IS_ERR(trans)) अणु
			err = PTR_ERR(trans);
			trans = शून्य;
			अवरोध;
		पूर्ण
restart:
		अगर (update_backref_cache(trans, &rc->backref_cache)) अणु
			btrfs_end_transaction(trans);
			trans = शून्य;
			जारी;
		पूर्ण

		ret = find_next_extent(rc, path, &key);
		अगर (ret < 0)
			err = ret;
		अगर (ret != 0)
			अवरोध;

		rc->extents_found++;

		ei = btrfs_item_ptr(path->nodes[0], path->slots[0],
				    काष्ठा btrfs_extent_item);
		flags = btrfs_extent_flags(path->nodes[0], ei);

		अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
			ret = add_tree_block(rc, &key, path, &blocks);
		पूर्ण अन्यथा अगर (rc->stage == UPDATE_DATA_PTRS &&
			   (flags & BTRFS_EXTENT_FLAG_DATA)) अणु
			ret = add_data_references(rc, &key, path, &blocks);
		पूर्ण अन्यथा अणु
			btrfs_release_path(path);
			ret = 0;
		पूर्ण
		अगर (ret < 0) अणु
			err = ret;
			अवरोध;
		पूर्ण

		अगर (!RB_EMPTY_ROOT(&blocks)) अणु
			ret = relocate_tree_blocks(trans, rc, &blocks);
			अगर (ret < 0) अणु
				अगर (ret != -EAGAIN) अणु
					err = ret;
					अवरोध;
				पूर्ण
				rc->extents_found--;
				rc->search_start = key.objectid;
			पूर्ण
		पूर्ण

		btrfs_end_transaction_throttle(trans);
		btrfs_btree_balance_dirty(fs_info);
		trans = शून्य;

		अगर (rc->stage == MOVE_DATA_EXTENTS &&
		    (flags & BTRFS_EXTENT_FLAG_DATA)) अणु
			rc->found_file_extent = 1;
			ret = relocate_data_extent(rc->data_inode,
						   &key, &rc->cluster);
			अगर (ret < 0) अणु
				err = ret;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (btrfs_should_cancel_balance(fs_info)) अणु
			err = -ECANCELED;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (trans && progress && err == -ENOSPC) अणु
		ret = btrfs_क्रमce_chunk_alloc(trans, rc->block_group->flags);
		अगर (ret == 1) अणु
			err = 0;
			progress = 0;
			जाओ restart;
		पूर्ण
	पूर्ण

	btrfs_release_path(path);
	clear_extent_bits(&rc->processed_blocks, 0, (u64)-1, EXTENT_सूचीTY);

	अगर (trans) अणु
		btrfs_end_transaction_throttle(trans);
		btrfs_btree_balance_dirty(fs_info);
	पूर्ण

	अगर (!err) अणु
		ret = relocate_file_extent_cluster(rc->data_inode,
						   &rc->cluster);
		अगर (ret < 0)
			err = ret;
	पूर्ण

	rc->create_reloc_tree = 0;
	set_reloc_control(rc);

	btrfs_backref_release_cache(&rc->backref_cache);
	btrfs_block_rsv_release(fs_info, rc->block_rsv, (u64)-1, शून्य);

	/*
	 * Even in the हाल when the relocation is cancelled, we should all go
	 * through prepare_to_merge() and merge_reloc_roots().
	 *
	 * For error (including cancelled balance), prepare_to_merge() will
	 * mark all reloc trees orphan, then queue them क्रम cleanup in
	 * merge_reloc_roots()
	 */
	err = prepare_to_merge(rc, err);

	merge_reloc_roots(rc);

	rc->merge_reloc_tree = 0;
	unset_reloc_control(rc);
	btrfs_block_rsv_release(fs_info, rc->block_rsv, (u64)-1, शून्य);

	/* get rid of pinned extents */
	trans = btrfs_join_transaction(rc->extent_root);
	अगर (IS_ERR(trans)) अणु
		err = PTR_ERR(trans);
		जाओ out_मुक्त;
	पूर्ण
	ret = btrfs_commit_transaction(trans);
	अगर (ret && !err)
		err = ret;
out_मुक्त:
	ret = clean_dirty_subvols(rc);
	अगर (ret < 0 && !err)
		err = ret;
	btrfs_मुक्त_block_rsv(fs_info, rc->block_rsv);
	btrfs_मुक्त_path(path);
	वापस err;
पूर्ण

अटल पूर्णांक __insert_orphan_inode(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_root *root, u64 objectid)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_inode_item *item;
	काष्ठा extent_buffer *leaf;
	u64 flags = BTRFS_INODE_NOCOMPRESS | BTRFS_INODE_PREALLOC;
	पूर्णांक ret;

	अगर (btrfs_is_zoned(trans->fs_info))
		flags &= ~BTRFS_INODE_PREALLOC;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ret = btrfs_insert_empty_inode(trans, root, path, objectid);
	अगर (ret)
		जाओ out;

	leaf = path->nodes[0];
	item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_inode_item);
	memzero_extent_buffer(leaf, (अचिन्हित दीर्घ)item, माप(*item));
	btrfs_set_inode_generation(leaf, item, 1);
	btrfs_set_inode_size(leaf, item, 0);
	btrfs_set_inode_mode(leaf, item, S_IFREG | 0600);
	btrfs_set_inode_flags(leaf, item, flags);
	btrfs_mark_buffer_dirty(leaf);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल व्योम delete_orphan_inode(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_root *root, u64 objectid)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक ret = 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	key.objectid = objectid;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = -ENOENT;
		जाओ out;
	पूर्ण
	ret = btrfs_del_item(trans, root, path);
out:
	अगर (ret)
		btrfs_पात_transaction(trans, ret);
	btrfs_मुक्त_path(path);
पूर्ण

/*
 * helper to create inode क्रम data relocation.
 * the inode is in data relocation tree and its link count is 0
 */
अटल noअंतरभूत_क्रम_stack
काष्ठा inode *create_reloc_inode(काष्ठा btrfs_fs_info *fs_info,
				 काष्ठा btrfs_block_group *group)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root;
	u64 objectid;
	पूर्णांक err = 0;

	root = btrfs_grab_root(fs_info->data_reloc_root);
	trans = btrfs_start_transaction(root, 6);
	अगर (IS_ERR(trans)) अणु
		btrfs_put_root(root);
		वापस ERR_CAST(trans);
	पूर्ण

	err = btrfs_get_मुक्त_objectid(root, &objectid);
	अगर (err)
		जाओ out;

	err = __insert_orphan_inode(trans, root, objectid);
	अगर (err)
		जाओ out;

	inode = btrfs_iget(fs_info->sb, objectid, root);
	अगर (IS_ERR(inode)) अणु
		delete_orphan_inode(trans, root, objectid);
		err = PTR_ERR(inode);
		inode = शून्य;
		जाओ out;
	पूर्ण
	BTRFS_I(inode)->index_cnt = group->start;

	err = btrfs_orphan_add(trans, BTRFS_I(inode));
out:
	btrfs_put_root(root);
	btrfs_end_transaction(trans);
	btrfs_btree_balance_dirty(fs_info);
	अगर (err) अणु
		अगर (inode)
			iput(inode);
		inode = ERR_PTR(err);
	पूर्ण
	वापस inode;
पूर्ण

अटल काष्ठा reloc_control *alloc_reloc_control(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा reloc_control *rc;

	rc = kzalloc(माप(*rc), GFP_NOFS);
	अगर (!rc)
		वापस शून्य;

	INIT_LIST_HEAD(&rc->reloc_roots);
	INIT_LIST_HEAD(&rc->dirty_subvol_roots);
	btrfs_backref_init_cache(fs_info, &rc->backref_cache, 1);
	mapping_tree_init(&rc->reloc_root_tree);
	extent_io_tree_init(fs_info, &rc->processed_blocks,
			    IO_TREE_RELOC_BLOCKS, शून्य);
	वापस rc;
पूर्ण

अटल व्योम मुक्त_reloc_control(काष्ठा reloc_control *rc)
अणु
	काष्ठा mapping_node *node, *पंचांगp;

	मुक्त_reloc_roots(&rc->reloc_roots);
	rbtree_postorder_क्रम_each_entry_safe(node, पंचांगp,
			&rc->reloc_root_tree.rb_root, rb_node)
		kमुक्त(node);

	kमुक्त(rc);
पूर्ण

/*
 * Prपूर्णांक the block group being relocated
 */
अटल व्योम describe_relocation(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_block_group *block_group)
अणु
	अक्षर buf[128] = अणु'\0'पूर्ण;

	btrfs_describe_block_groups(block_group->flags, buf, माप(buf));

	btrfs_info(fs_info,
		   "relocating block group %llu flags %s",
		   block_group->start, buf);
पूर्ण

अटल स्थिर अक्षर *stage_to_string(पूर्णांक stage)
अणु
	अगर (stage == MOVE_DATA_EXTENTS)
		वापस "move data extents";
	अगर (stage == UPDATE_DATA_PTRS)
		वापस "update data pointers";
	वापस "unknown";
पूर्ण

/*
 * function to relocate all extents in a block group.
 */
पूर्णांक btrfs_relocate_block_group(काष्ठा btrfs_fs_info *fs_info, u64 group_start)
अणु
	काष्ठा btrfs_block_group *bg;
	काष्ठा btrfs_root *extent_root = fs_info->extent_root;
	काष्ठा reloc_control *rc;
	काष्ठा inode *inode;
	काष्ठा btrfs_path *path;
	पूर्णांक ret;
	पूर्णांक rw = 0;
	पूर्णांक err = 0;

	bg = btrfs_lookup_block_group(fs_info, group_start);
	अगर (!bg)
		वापस -ENOENT;

	अगर (btrfs_pinned_by_swapfile(fs_info, bg)) अणु
		btrfs_put_block_group(bg);
		वापस -ETXTBSY;
	पूर्ण

	rc = alloc_reloc_control(fs_info);
	अगर (!rc) अणु
		btrfs_put_block_group(bg);
		वापस -ENOMEM;
	पूर्ण

	rc->extent_root = extent_root;
	rc->block_group = bg;

	ret = btrfs_inc_block_group_ro(rc->block_group, true);
	अगर (ret) अणु
		err = ret;
		जाओ out;
	पूर्ण
	rw = 1;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	inode = lookup_मुक्त_space_inode(rc->block_group, path);
	btrfs_मुक्त_path(path);

	अगर (!IS_ERR(inode))
		ret = delete_block_group_cache(fs_info, rc->block_group, inode, 0);
	अन्यथा
		ret = PTR_ERR(inode);

	अगर (ret && ret != -ENOENT) अणु
		err = ret;
		जाओ out;
	पूर्ण

	rc->data_inode = create_reloc_inode(fs_info, rc->block_group);
	अगर (IS_ERR(rc->data_inode)) अणु
		err = PTR_ERR(rc->data_inode);
		rc->data_inode = शून्य;
		जाओ out;
	पूर्ण

	describe_relocation(fs_info, rc->block_group);

	btrfs_रुको_block_group_reservations(rc->block_group);
	btrfs_रुको_nocow_ग_लिखोrs(rc->block_group);
	btrfs_रुको_ordered_roots(fs_info, U64_MAX,
				 rc->block_group->start,
				 rc->block_group->length);

	जबतक (1) अणु
		पूर्णांक finishes_stage;

		mutex_lock(&fs_info->cleaner_mutex);
		ret = relocate_block_group(rc);
		mutex_unlock(&fs_info->cleaner_mutex);
		अगर (ret < 0)
			err = ret;

		finishes_stage = rc->stage;
		/*
		 * We may have gotten ENOSPC after we alपढ़ोy dirtied some
		 * extents.  If ग_लिखोout happens जबतक we're relocating a
		 * dअगरferent block group we could end up hitting the
		 * BUG_ON(rc->stage == UPDATE_DATA_PTRS) in
		 * btrfs_reloc_cow_block.  Make sure we ग_लिखो everything out
		 * properly so we करोn't trip over this problem, and then अवरोध
		 * out of the loop अगर we hit an error.
		 */
		अगर (rc->stage == MOVE_DATA_EXTENTS && rc->found_file_extent) अणु
			ret = btrfs_रुको_ordered_range(rc->data_inode, 0,
						       (u64)-1);
			अगर (ret)
				err = ret;
			invalidate_mapping_pages(rc->data_inode->i_mapping,
						 0, -1);
			rc->stage = UPDATE_DATA_PTRS;
		पूर्ण

		अगर (err < 0)
			जाओ out;

		अगर (rc->extents_found == 0)
			अवरोध;

		btrfs_info(fs_info, "found %llu extents, stage: %s",
			   rc->extents_found, stage_to_string(finishes_stage));
	पूर्ण

	WARN_ON(rc->block_group->pinned > 0);
	WARN_ON(rc->block_group->reserved > 0);
	WARN_ON(rc->block_group->used > 0);
out:
	अगर (err && rw)
		btrfs_dec_block_group_ro(rc->block_group);
	iput(rc->data_inode);
	btrfs_put_block_group(rc->block_group);
	मुक्त_reloc_control(rc);
	वापस err;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक mark_garbage_root(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret, err;

	trans = btrfs_start_transaction(fs_info->tree_root, 0);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	स_रखो(&root->root_item.drop_progress, 0,
		माप(root->root_item.drop_progress));
	btrfs_set_root_drop_level(&root->root_item, 0);
	btrfs_set_root_refs(&root->root_item, 0);
	ret = btrfs_update_root(trans, fs_info->tree_root,
				&root->root_key, &root->root_item);

	err = btrfs_end_transaction(trans);
	अगर (err)
		वापस err;
	वापस ret;
पूर्ण

/*
 * recover relocation पूर्णांकerrupted by प्रणाली crash.
 *
 * this function resumes merging reloc trees with corresponding fs trees.
 * this is important क्रम keeping the sharing of tree blocks
 */
पूर्णांक btrfs_recover_relocation(काष्ठा btrfs_root *root)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	LIST_HEAD(reloc_roots);
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root *fs_root;
	काष्ठा btrfs_root *reloc_root;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा reloc_control *rc = शून्य;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret;
	पूर्णांक err = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	path->पढ़ोa = READA_BACK;

	key.objectid = BTRFS_TREE_RELOC_OBJECTID;
	key.type = BTRFS_ROOT_ITEM_KEY;
	key.offset = (u64)-1;

	जबतक (1) अणु
		ret = btrfs_search_slot(शून्य, fs_info->tree_root, &key,
					path, 0, 0);
		अगर (ret < 0) अणु
			err = ret;
			जाओ out;
		पूर्ण
		अगर (ret > 0) अणु
			अगर (path->slots[0] == 0)
				अवरोध;
			path->slots[0]--;
		पूर्ण
		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		btrfs_release_path(path);

		अगर (key.objectid != BTRFS_TREE_RELOC_OBJECTID ||
		    key.type != BTRFS_ROOT_ITEM_KEY)
			अवरोध;

		reloc_root = btrfs_पढ़ो_tree_root(root, &key);
		अगर (IS_ERR(reloc_root)) अणु
			err = PTR_ERR(reloc_root);
			जाओ out;
		पूर्ण

		set_bit(BTRFS_ROOT_SHAREABLE, &reloc_root->state);
		list_add(&reloc_root->root_list, &reloc_roots);

		अगर (btrfs_root_refs(&reloc_root->root_item) > 0) अणु
			fs_root = btrfs_get_fs_root(fs_info,
					reloc_root->root_key.offset, false);
			अगर (IS_ERR(fs_root)) अणु
				ret = PTR_ERR(fs_root);
				अगर (ret != -ENOENT) अणु
					err = ret;
					जाओ out;
				पूर्ण
				ret = mark_garbage_root(reloc_root);
				अगर (ret < 0) अणु
					err = ret;
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा अणु
				btrfs_put_root(fs_root);
			पूर्ण
		पूर्ण

		अगर (key.offset == 0)
			अवरोध;

		key.offset--;
	पूर्ण
	btrfs_release_path(path);

	अगर (list_empty(&reloc_roots))
		जाओ out;

	rc = alloc_reloc_control(fs_info);
	अगर (!rc) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	rc->extent_root = fs_info->extent_root;

	set_reloc_control(rc);

	trans = btrfs_join_transaction(rc->extent_root);
	अगर (IS_ERR(trans)) अणु
		err = PTR_ERR(trans);
		जाओ out_unset;
	पूर्ण

	rc->merge_reloc_tree = 1;

	जबतक (!list_empty(&reloc_roots)) अणु
		reloc_root = list_entry(reloc_roots.next,
					काष्ठा btrfs_root, root_list);
		list_del(&reloc_root->root_list);

		अगर (btrfs_root_refs(&reloc_root->root_item) == 0) अणु
			list_add_tail(&reloc_root->root_list,
				      &rc->reloc_roots);
			जारी;
		पूर्ण

		fs_root = btrfs_get_fs_root(fs_info, reloc_root->root_key.offset,
					    false);
		अगर (IS_ERR(fs_root)) अणु
			err = PTR_ERR(fs_root);
			list_add_tail(&reloc_root->root_list, &reloc_roots);
			btrfs_end_transaction(trans);
			जाओ out_unset;
		पूर्ण

		err = __add_reloc_root(reloc_root);
		ASSERT(err != -EEXIST);
		अगर (err) अणु
			list_add_tail(&reloc_root->root_list, &reloc_roots);
			btrfs_put_root(fs_root);
			btrfs_end_transaction(trans);
			जाओ out_unset;
		पूर्ण
		fs_root->reloc_root = btrfs_grab_root(reloc_root);
		btrfs_put_root(fs_root);
	पूर्ण

	err = btrfs_commit_transaction(trans);
	अगर (err)
		जाओ out_unset;

	merge_reloc_roots(rc);

	unset_reloc_control(rc);

	trans = btrfs_join_transaction(rc->extent_root);
	अगर (IS_ERR(trans)) अणु
		err = PTR_ERR(trans);
		जाओ out_clean;
	पूर्ण
	err = btrfs_commit_transaction(trans);
out_clean:
	ret = clean_dirty_subvols(rc);
	अगर (ret < 0 && !err)
		err = ret;
out_unset:
	unset_reloc_control(rc);
	मुक्त_reloc_control(rc);
out:
	मुक्त_reloc_roots(&reloc_roots);

	btrfs_मुक्त_path(path);

	अगर (err == 0) अणु
		/* cleanup orphan inode in data relocation tree */
		fs_root = btrfs_grab_root(fs_info->data_reloc_root);
		ASSERT(fs_root);
		err = btrfs_orphan_cleanup(fs_root);
		btrfs_put_root(fs_root);
	पूर्ण
	वापस err;
पूर्ण

/*
 * helper to add ordered checksum क्रम data relocation.
 *
 * cloning checksum properly handles the nodatasum extents.
 * it also saves CPU समय to re-calculate the checksum.
 */
पूर्णांक btrfs_reloc_clone_csums(काष्ठा btrfs_inode *inode, u64 file_pos, u64 len)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_ordered_sum *sums;
	काष्ठा btrfs_ordered_extent *ordered;
	पूर्णांक ret;
	u64 disk_bytenr;
	u64 new_bytenr;
	LIST_HEAD(list);

	ordered = btrfs_lookup_ordered_extent(inode, file_pos);
	BUG_ON(ordered->file_offset != file_pos || ordered->num_bytes != len);

	disk_bytenr = file_pos + inode->index_cnt;
	ret = btrfs_lookup_csums_range(fs_info->csum_root, disk_bytenr,
				       disk_bytenr + len - 1, &list, 0);
	अगर (ret)
		जाओ out;

	जबतक (!list_empty(&list)) अणु
		sums = list_entry(list.next, काष्ठा btrfs_ordered_sum, list);
		list_del_init(&sums->list);

		/*
		 * We need to offset the new_bytenr based on where the csum is.
		 * We need to करो this because we will पढ़ो in entire pपुनः_स्मृति
		 * extents but we may have written to say the middle of the
		 * pपुनः_स्मृति extent, so we need to make sure the csum goes with
		 * the right disk offset.
		 *
		 * We can करो this because the data reloc inode refers strictly
		 * to the on disk bytes, so we करोn't have to worry about
		 * disk_len vs real len like with real inodes since it's all
		 * disk length.
		 */
		new_bytenr = ordered->disk_bytenr + sums->bytenr - disk_bytenr;
		sums->bytenr = new_bytenr;

		btrfs_add_ordered_sum(ordered, sums);
	पूर्ण
out:
	btrfs_put_ordered_extent(ordered);
	वापस ret;
पूर्ण

पूर्णांक btrfs_reloc_cow_block(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_root *root, काष्ठा extent_buffer *buf,
			  काष्ठा extent_buffer *cow)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा reloc_control *rc;
	काष्ठा btrfs_backref_node *node;
	पूर्णांक first_cow = 0;
	पूर्णांक level;
	पूर्णांक ret = 0;

	rc = fs_info->reloc_ctl;
	अगर (!rc)
		वापस 0;

	BUG_ON(rc->stage == UPDATE_DATA_PTRS &&
	       root->root_key.objectid == BTRFS_DATA_RELOC_TREE_OBJECTID);

	level = btrfs_header_level(buf);
	अगर (btrfs_header_generation(buf) <=
	    btrfs_root_last_snapshot(&root->root_item))
		first_cow = 1;

	अगर (root->root_key.objectid == BTRFS_TREE_RELOC_OBJECTID &&
	    rc->create_reloc_tree) अणु
		WARN_ON(!first_cow && level == 0);

		node = rc->backref_cache.path[level];
		BUG_ON(node->bytenr != buf->start &&
		       node->new_bytenr != buf->start);

		btrfs_backref_drop_node_buffer(node);
		atomic_inc(&cow->refs);
		node->eb = cow;
		node->new_bytenr = cow->start;

		अगर (!node->pending) अणु
			list_move_tail(&node->list,
				       &rc->backref_cache.pending[level]);
			node->pending = 1;
		पूर्ण

		अगर (first_cow)
			mark_block_processed(rc, node);

		अगर (first_cow && level > 0)
			rc->nodes_relocated += buf->len;
	पूर्ण

	अगर (level == 0 && first_cow && rc->stage == UPDATE_DATA_PTRS)
		ret = replace_file_extents(trans, rc, root, cow);
	वापस ret;
पूर्ण

/*
 * called beक्रमe creating snapshot. it calculates metadata reservation
 * required क्रम relocating tree blocks in the snapshot
 */
व्योम btrfs_reloc_pre_snapshot(काष्ठा btrfs_pending_snapshot *pending,
			      u64 *bytes_to_reserve)
अणु
	काष्ठा btrfs_root *root = pending->root;
	काष्ठा reloc_control *rc = root->fs_info->reloc_ctl;

	अगर (!rc || !have_reloc_root(root))
		वापस;

	अगर (!rc->merge_reloc_tree)
		वापस;

	root = root->reloc_root;
	BUG_ON(btrfs_root_refs(&root->root_item) == 0);
	/*
	 * relocation is in the stage of merging trees. the space
	 * used by merging a reloc tree is twice the size of
	 * relocated tree nodes in the worst हाल. half क्रम cowing
	 * the reloc tree, half क्रम cowing the fs tree. the space
	 * used by cowing the reloc tree will be मुक्तd after the
	 * tree is dropped. अगर we create snapshot, cowing the fs
	 * tree may use more space than it मुक्तs. so we need
	 * reserve extra space.
	 */
	*bytes_to_reserve += rc->nodes_relocated;
पूर्ण

/*
 * called after snapshot is created. migrate block reservation
 * and create reloc root क्रम the newly created snapshot
 *
 * This is similar to btrfs_init_reloc_root(), we come out of here with two
 * references held on the reloc_root, one क्रम root->reloc_root and one क्रम
 * rc->reloc_roots.
 */
पूर्णांक btrfs_reloc_post_snapshot(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_pending_snapshot *pending)
अणु
	काष्ठा btrfs_root *root = pending->root;
	काष्ठा btrfs_root *reloc_root;
	काष्ठा btrfs_root *new_root;
	काष्ठा reloc_control *rc = root->fs_info->reloc_ctl;
	पूर्णांक ret;

	अगर (!rc || !have_reloc_root(root))
		वापस 0;

	rc = root->fs_info->reloc_ctl;
	rc->merging_rsv_size += rc->nodes_relocated;

	अगर (rc->merge_reloc_tree) अणु
		ret = btrfs_block_rsv_migrate(&pending->block_rsv,
					      rc->block_rsv,
					      rc->nodes_relocated, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	new_root = pending->snap;
	reloc_root = create_reloc_root(trans, root->reloc_root,
				       new_root->root_key.objectid);
	अगर (IS_ERR(reloc_root))
		वापस PTR_ERR(reloc_root);

	ret = __add_reloc_root(reloc_root);
	ASSERT(ret != -EEXIST);
	अगर (ret) अणु
		/* Pairs with create_reloc_root */
		btrfs_put_root(reloc_root);
		वापस ret;
	पूर्ण
	new_root->reloc_root = btrfs_grab_root(reloc_root);

	अगर (rc->create_reloc_tree)
		ret = clone_backref_node(trans, rc, root, reloc_root);
	वापस ret;
पूर्ण
