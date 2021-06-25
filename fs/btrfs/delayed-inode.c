<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Fujitsu.  All rights reserved.
 * Written by Miao Xie <miaox@cn.fujitsu.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/iversion.h>
#समावेश <linux/sched/mm.h>
#समावेश "misc.h"
#समावेश "delayed-inode.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "ctree.h"
#समावेश "qgroup.h"
#समावेश "locking.h"

#घोषणा BTRFS_DELAYED_WRITEBACK		512
#घोषणा BTRFS_DELAYED_BACKGROUND	128
#घोषणा BTRFS_DELAYED_BATCH		16

अटल काष्ठा kmem_cache *delayed_node_cache;

पूर्णांक __init btrfs_delayed_inode_init(व्योम)
अणु
	delayed_node_cache = kmem_cache_create("btrfs_delayed_node",
					माप(काष्ठा btrfs_delayed_node),
					0,
					SLAB_MEM_SPREAD,
					शून्य);
	अगर (!delayed_node_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम __cold btrfs_delayed_inode_निकास(व्योम)
अणु
	kmem_cache_destroy(delayed_node_cache);
पूर्ण

अटल अंतरभूत व्योम btrfs_init_delayed_node(
				काष्ठा btrfs_delayed_node *delayed_node,
				काष्ठा btrfs_root *root, u64 inode_id)
अणु
	delayed_node->root = root;
	delayed_node->inode_id = inode_id;
	refcount_set(&delayed_node->refs, 0);
	delayed_node->ins_root = RB_ROOT_CACHED;
	delayed_node->del_root = RB_ROOT_CACHED;
	mutex_init(&delayed_node->mutex);
	INIT_LIST_HEAD(&delayed_node->n_list);
	INIT_LIST_HEAD(&delayed_node->p_list);
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_is_continuous_delayed_item(
					काष्ठा btrfs_delayed_item *item1,
					काष्ठा btrfs_delayed_item *item2)
अणु
	अगर (item1->key.type == BTRFS_सूची_INDEX_KEY &&
	    item1->key.objectid == item2->key.objectid &&
	    item1->key.type == item2->key.type &&
	    item1->key.offset + 1 == item2->key.offset)
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा btrfs_delayed_node *btrfs_get_delayed_node(
		काष्ठा btrfs_inode *btrfs_inode)
अणु
	काष्ठा btrfs_root *root = btrfs_inode->root;
	u64 ino = btrfs_ino(btrfs_inode);
	काष्ठा btrfs_delayed_node *node;

	node = READ_ONCE(btrfs_inode->delayed_node);
	अगर (node) अणु
		refcount_inc(&node->refs);
		वापस node;
	पूर्ण

	spin_lock(&root->inode_lock);
	node = radix_tree_lookup(&root->delayed_nodes_tree, ino);

	अगर (node) अणु
		अगर (btrfs_inode->delayed_node) अणु
			refcount_inc(&node->refs);	/* can be accessed */
			BUG_ON(btrfs_inode->delayed_node != node);
			spin_unlock(&root->inode_lock);
			वापस node;
		पूर्ण

		/*
		 * It's possible that we're racing पूर्णांकo the middle of removing
		 * this node from the radix tree.  In this हाल, the refcount
		 * was zero and it should never go back to one.  Just वापस
		 * शून्य like it was never in the radix at all; our release
		 * function is in the process of removing it.
		 *
		 * Some implementations of refcount_inc refuse to bump the
		 * refcount once it has hit zero.  If we करोn't करो this dance
		 * here, refcount_inc() may decide to just WARN_ONCE() instead
		 * of actually bumping the refcount.
		 *
		 * If this node is properly in the radix, we want to bump the
		 * refcount twice, once क्रम the inode and once क्रम this get
		 * operation.
		 */
		अगर (refcount_inc_not_zero(&node->refs)) अणु
			refcount_inc(&node->refs);
			btrfs_inode->delayed_node = node;
		पूर्ण अन्यथा अणु
			node = शून्य;
		पूर्ण

		spin_unlock(&root->inode_lock);
		वापस node;
	पूर्ण
	spin_unlock(&root->inode_lock);

	वापस शून्य;
पूर्ण

/* Will वापस either the node or PTR_ERR(-ENOMEM) */
अटल काष्ठा btrfs_delayed_node *btrfs_get_or_create_delayed_node(
		काष्ठा btrfs_inode *btrfs_inode)
अणु
	काष्ठा btrfs_delayed_node *node;
	काष्ठा btrfs_root *root = btrfs_inode->root;
	u64 ino = btrfs_ino(btrfs_inode);
	पूर्णांक ret;

again:
	node = btrfs_get_delayed_node(btrfs_inode);
	अगर (node)
		वापस node;

	node = kmem_cache_zalloc(delayed_node_cache, GFP_NOFS);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);
	btrfs_init_delayed_node(node, root, ino);

	/* cached in the btrfs inode and can be accessed */
	refcount_set(&node->refs, 2);

	ret = radix_tree_preload(GFP_NOFS);
	अगर (ret) अणु
		kmem_cache_मुक्त(delayed_node_cache, node);
		वापस ERR_PTR(ret);
	पूर्ण

	spin_lock(&root->inode_lock);
	ret = radix_tree_insert(&root->delayed_nodes_tree, ino, node);
	अगर (ret == -EEXIST) अणु
		spin_unlock(&root->inode_lock);
		kmem_cache_मुक्त(delayed_node_cache, node);
		radix_tree_preload_end();
		जाओ again;
	पूर्ण
	btrfs_inode->delayed_node = node;
	spin_unlock(&root->inode_lock);
	radix_tree_preload_end();

	वापस node;
पूर्ण

/*
 * Call it when holding delayed_node->mutex
 *
 * If mod = 1, add this node पूर्णांकo the prepared list.
 */
अटल व्योम btrfs_queue_delayed_node(काष्ठा btrfs_delayed_root *root,
				     काष्ठा btrfs_delayed_node *node,
				     पूर्णांक mod)
अणु
	spin_lock(&root->lock);
	अगर (test_bit(BTRFS_DELAYED_NODE_IN_LIST, &node->flags)) अणु
		अगर (!list_empty(&node->p_list))
			list_move_tail(&node->p_list, &root->prepare_list);
		अन्यथा अगर (mod)
			list_add_tail(&node->p_list, &root->prepare_list);
	पूर्ण अन्यथा अणु
		list_add_tail(&node->n_list, &root->node_list);
		list_add_tail(&node->p_list, &root->prepare_list);
		refcount_inc(&node->refs);	/* inserted पूर्णांकo list */
		root->nodes++;
		set_bit(BTRFS_DELAYED_NODE_IN_LIST, &node->flags);
	पूर्ण
	spin_unlock(&root->lock);
पूर्ण

/* Call it when holding delayed_node->mutex */
अटल व्योम btrfs_dequeue_delayed_node(काष्ठा btrfs_delayed_root *root,
				       काष्ठा btrfs_delayed_node *node)
अणु
	spin_lock(&root->lock);
	अगर (test_bit(BTRFS_DELAYED_NODE_IN_LIST, &node->flags)) अणु
		root->nodes--;
		refcount_dec(&node->refs);	/* not in the list */
		list_del_init(&node->n_list);
		अगर (!list_empty(&node->p_list))
			list_del_init(&node->p_list);
		clear_bit(BTRFS_DELAYED_NODE_IN_LIST, &node->flags);
	पूर्ण
	spin_unlock(&root->lock);
पूर्ण

अटल काष्ठा btrfs_delayed_node *btrfs_first_delayed_node(
			काष्ठा btrfs_delayed_root *delayed_root)
अणु
	काष्ठा list_head *p;
	काष्ठा btrfs_delayed_node *node = शून्य;

	spin_lock(&delayed_root->lock);
	अगर (list_empty(&delayed_root->node_list))
		जाओ out;

	p = delayed_root->node_list.next;
	node = list_entry(p, काष्ठा btrfs_delayed_node, n_list);
	refcount_inc(&node->refs);
out:
	spin_unlock(&delayed_root->lock);

	वापस node;
पूर्ण

अटल काष्ठा btrfs_delayed_node *btrfs_next_delayed_node(
						काष्ठा btrfs_delayed_node *node)
अणु
	काष्ठा btrfs_delayed_root *delayed_root;
	काष्ठा list_head *p;
	काष्ठा btrfs_delayed_node *next = शून्य;

	delayed_root = node->root->fs_info->delayed_root;
	spin_lock(&delayed_root->lock);
	अगर (!test_bit(BTRFS_DELAYED_NODE_IN_LIST, &node->flags)) अणु
		/* not in the list */
		अगर (list_empty(&delayed_root->node_list))
			जाओ out;
		p = delayed_root->node_list.next;
	पूर्ण अन्यथा अगर (list_is_last(&node->n_list, &delayed_root->node_list))
		जाओ out;
	अन्यथा
		p = node->n_list.next;

	next = list_entry(p, काष्ठा btrfs_delayed_node, n_list);
	refcount_inc(&next->refs);
out:
	spin_unlock(&delayed_root->lock);

	वापस next;
पूर्ण

अटल व्योम __btrfs_release_delayed_node(
				काष्ठा btrfs_delayed_node *delayed_node,
				पूर्णांक mod)
अणु
	काष्ठा btrfs_delayed_root *delayed_root;

	अगर (!delayed_node)
		वापस;

	delayed_root = delayed_node->root->fs_info->delayed_root;

	mutex_lock(&delayed_node->mutex);
	अगर (delayed_node->count)
		btrfs_queue_delayed_node(delayed_root, delayed_node, mod);
	अन्यथा
		btrfs_dequeue_delayed_node(delayed_root, delayed_node);
	mutex_unlock(&delayed_node->mutex);

	अगर (refcount_dec_and_test(&delayed_node->refs)) अणु
		काष्ठा btrfs_root *root = delayed_node->root;

		spin_lock(&root->inode_lock);
		/*
		 * Once our refcount goes to zero, nobody is allowed to bump it
		 * back up.  We can delete it now.
		 */
		ASSERT(refcount_पढ़ो(&delayed_node->refs) == 0);
		radix_tree_delete(&root->delayed_nodes_tree,
				  delayed_node->inode_id);
		spin_unlock(&root->inode_lock);
		kmem_cache_मुक्त(delayed_node_cache, delayed_node);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम btrfs_release_delayed_node(काष्ठा btrfs_delayed_node *node)
अणु
	__btrfs_release_delayed_node(node, 0);
पूर्ण

अटल काष्ठा btrfs_delayed_node *btrfs_first_prepared_delayed_node(
					काष्ठा btrfs_delayed_root *delayed_root)
अणु
	काष्ठा list_head *p;
	काष्ठा btrfs_delayed_node *node = शून्य;

	spin_lock(&delayed_root->lock);
	अगर (list_empty(&delayed_root->prepare_list))
		जाओ out;

	p = delayed_root->prepare_list.next;
	list_del_init(p);
	node = list_entry(p, काष्ठा btrfs_delayed_node, p_list);
	refcount_inc(&node->refs);
out:
	spin_unlock(&delayed_root->lock);

	वापस node;
पूर्ण

अटल अंतरभूत व्योम btrfs_release_prepared_delayed_node(
					काष्ठा btrfs_delayed_node *node)
अणु
	__btrfs_release_delayed_node(node, 1);
पूर्ण

अटल काष्ठा btrfs_delayed_item *btrfs_alloc_delayed_item(u32 data_len)
अणु
	काष्ठा btrfs_delayed_item *item;
	item = kदो_स्मृति(माप(*item) + data_len, GFP_NOFS);
	अगर (item) अणु
		item->data_len = data_len;
		item->ins_or_del = 0;
		item->bytes_reserved = 0;
		item->delayed_node = शून्य;
		refcount_set(&item->refs, 1);
	पूर्ण
	वापस item;
पूर्ण

/*
 * __btrfs_lookup_delayed_item - look up the delayed item by key
 * @delayed_node: poपूर्णांकer to the delayed node
 * @key:	  the key to look up
 * @prev:	  used to store the prev item अगर the right item isn't found
 * @next:	  used to store the next item अगर the right item isn't found
 *
 * Note: अगर we करोn't find the right item, we will वापस the prev item and
 * the next item.
 */
अटल काष्ठा btrfs_delayed_item *__btrfs_lookup_delayed_item(
				काष्ठा rb_root *root,
				काष्ठा btrfs_key *key,
				काष्ठा btrfs_delayed_item **prev,
				काष्ठा btrfs_delayed_item **next)
अणु
	काष्ठा rb_node *node, *prev_node = शून्य;
	काष्ठा btrfs_delayed_item *delayed_item = शून्य;
	पूर्णांक ret = 0;

	node = root->rb_node;

	जबतक (node) अणु
		delayed_item = rb_entry(node, काष्ठा btrfs_delayed_item,
					rb_node);
		prev_node = node;
		ret = btrfs_comp_cpu_keys(&delayed_item->key, key);
		अगर (ret < 0)
			node = node->rb_right;
		अन्यथा अगर (ret > 0)
			node = node->rb_left;
		अन्यथा
			वापस delayed_item;
	पूर्ण

	अगर (prev) अणु
		अगर (!prev_node)
			*prev = शून्य;
		अन्यथा अगर (ret < 0)
			*prev = delayed_item;
		अन्यथा अगर ((node = rb_prev(prev_node)) != शून्य) अणु
			*prev = rb_entry(node, काष्ठा btrfs_delayed_item,
					 rb_node);
		पूर्ण अन्यथा
			*prev = शून्य;
	पूर्ण

	अगर (next) अणु
		अगर (!prev_node)
			*next = शून्य;
		अन्यथा अगर (ret > 0)
			*next = delayed_item;
		अन्यथा अगर ((node = rb_next(prev_node)) != शून्य) अणु
			*next = rb_entry(node, काष्ठा btrfs_delayed_item,
					 rb_node);
		पूर्ण अन्यथा
			*next = शून्य;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा btrfs_delayed_item *__btrfs_lookup_delayed_insertion_item(
					काष्ठा btrfs_delayed_node *delayed_node,
					काष्ठा btrfs_key *key)
अणु
	वापस __btrfs_lookup_delayed_item(&delayed_node->ins_root.rb_root, key,
					   शून्य, शून्य);
पूर्ण

अटल पूर्णांक __btrfs_add_delayed_item(काष्ठा btrfs_delayed_node *delayed_node,
				    काष्ठा btrfs_delayed_item *ins,
				    पूर्णांक action)
अणु
	काष्ठा rb_node **p, *node;
	काष्ठा rb_node *parent_node = शून्य;
	काष्ठा rb_root_cached *root;
	काष्ठा btrfs_delayed_item *item;
	पूर्णांक cmp;
	bool lefपंचांगost = true;

	अगर (action == BTRFS_DELAYED_INSERTION_ITEM)
		root = &delayed_node->ins_root;
	अन्यथा अगर (action == BTRFS_DELAYED_DELETION_ITEM)
		root = &delayed_node->del_root;
	अन्यथा
		BUG();
	p = &root->rb_root.rb_node;
	node = &ins->rb_node;

	जबतक (*p) अणु
		parent_node = *p;
		item = rb_entry(parent_node, काष्ठा btrfs_delayed_item,
				 rb_node);

		cmp = btrfs_comp_cpu_keys(&item->key, &ins->key);
		अगर (cmp < 0) अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण अन्यथा अगर (cmp > 0) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अणु
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	rb_link_node(node, parent_node, p);
	rb_insert_color_cached(node, root, lefपंचांगost);
	ins->delayed_node = delayed_node;
	ins->ins_or_del = action;

	अगर (ins->key.type == BTRFS_सूची_INDEX_KEY &&
	    action == BTRFS_DELAYED_INSERTION_ITEM &&
	    ins->key.offset >= delayed_node->index_cnt)
			delayed_node->index_cnt = ins->key.offset + 1;

	delayed_node->count++;
	atomic_inc(&delayed_node->root->fs_info->delayed_root->items);
	वापस 0;
पूर्ण

अटल पूर्णांक __btrfs_add_delayed_insertion_item(काष्ठा btrfs_delayed_node *node,
					      काष्ठा btrfs_delayed_item *item)
अणु
	वापस __btrfs_add_delayed_item(node, item,
					BTRFS_DELAYED_INSERTION_ITEM);
पूर्ण

अटल पूर्णांक __btrfs_add_delayed_deletion_item(काष्ठा btrfs_delayed_node *node,
					     काष्ठा btrfs_delayed_item *item)
अणु
	वापस __btrfs_add_delayed_item(node, item,
					BTRFS_DELAYED_DELETION_ITEM);
पूर्ण

अटल व्योम finish_one_item(काष्ठा btrfs_delayed_root *delayed_root)
अणु
	पूर्णांक seq = atomic_inc_वापस(&delayed_root->items_seq);

	/* atomic_dec_वापस implies a barrier */
	अगर ((atomic_dec_वापस(&delayed_root->items) <
	    BTRFS_DELAYED_BACKGROUND || seq % BTRFS_DELAYED_BATCH == 0))
		cond_wake_up_nomb(&delayed_root->रुको);
पूर्ण

अटल व्योम __btrfs_हटाओ_delayed_item(काष्ठा btrfs_delayed_item *delayed_item)
अणु
	काष्ठा rb_root_cached *root;
	काष्ठा btrfs_delayed_root *delayed_root;

	/* Not associated with any delayed_node */
	अगर (!delayed_item->delayed_node)
		वापस;
	delayed_root = delayed_item->delayed_node->root->fs_info->delayed_root;

	BUG_ON(!delayed_root);
	BUG_ON(delayed_item->ins_or_del != BTRFS_DELAYED_DELETION_ITEM &&
	       delayed_item->ins_or_del != BTRFS_DELAYED_INSERTION_ITEM);

	अगर (delayed_item->ins_or_del == BTRFS_DELAYED_INSERTION_ITEM)
		root = &delayed_item->delayed_node->ins_root;
	अन्यथा
		root = &delayed_item->delayed_node->del_root;

	rb_erase_cached(&delayed_item->rb_node, root);
	delayed_item->delayed_node->count--;

	finish_one_item(delayed_root);
पूर्ण

अटल व्योम btrfs_release_delayed_item(काष्ठा btrfs_delayed_item *item)
अणु
	अगर (item) अणु
		__btrfs_हटाओ_delayed_item(item);
		अगर (refcount_dec_and_test(&item->refs))
			kमुक्त(item);
	पूर्ण
पूर्ण

अटल काष्ठा btrfs_delayed_item *__btrfs_first_delayed_insertion_item(
					काष्ठा btrfs_delayed_node *delayed_node)
अणु
	काष्ठा rb_node *p;
	काष्ठा btrfs_delayed_item *item = शून्य;

	p = rb_first_cached(&delayed_node->ins_root);
	अगर (p)
		item = rb_entry(p, काष्ठा btrfs_delayed_item, rb_node);

	वापस item;
पूर्ण

अटल काष्ठा btrfs_delayed_item *__btrfs_first_delayed_deletion_item(
					काष्ठा btrfs_delayed_node *delayed_node)
अणु
	काष्ठा rb_node *p;
	काष्ठा btrfs_delayed_item *item = शून्य;

	p = rb_first_cached(&delayed_node->del_root);
	अगर (p)
		item = rb_entry(p, काष्ठा btrfs_delayed_item, rb_node);

	वापस item;
पूर्ण

अटल काष्ठा btrfs_delayed_item *__btrfs_next_delayed_item(
						काष्ठा btrfs_delayed_item *item)
अणु
	काष्ठा rb_node *p;
	काष्ठा btrfs_delayed_item *next = शून्य;

	p = rb_next(&item->rb_node);
	अगर (p)
		next = rb_entry(p, काष्ठा btrfs_delayed_item, rb_node);

	वापस next;
पूर्ण

अटल पूर्णांक btrfs_delayed_item_reserve_metadata(काष्ठा btrfs_trans_handle *trans,
					       काष्ठा btrfs_root *root,
					       काष्ठा btrfs_delayed_item *item)
अणु
	काष्ठा btrfs_block_rsv *src_rsv;
	काष्ठा btrfs_block_rsv *dst_rsv;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	u64 num_bytes;
	पूर्णांक ret;

	अगर (!trans->bytes_reserved)
		वापस 0;

	src_rsv = trans->block_rsv;
	dst_rsv = &fs_info->delayed_block_rsv;

	num_bytes = btrfs_calc_insert_metadata_size(fs_info, 1);

	/*
	 * Here we migrate space rsv from transaction rsv, since have alपढ़ोy
	 * reserved space when starting a transaction.  So no need to reserve
	 * qgroup space here.
	 */
	ret = btrfs_block_rsv_migrate(src_rsv, dst_rsv, num_bytes, true);
	अगर (!ret) अणु
		trace_btrfs_space_reservation(fs_info, "delayed_item",
					      item->key.objectid,
					      num_bytes, 1);
		item->bytes_reserved = num_bytes;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम btrfs_delayed_item_release_metadata(काष्ठा btrfs_root *root,
						काष्ठा btrfs_delayed_item *item)
अणु
	काष्ठा btrfs_block_rsv *rsv;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;

	अगर (!item->bytes_reserved)
		वापस;

	rsv = &fs_info->delayed_block_rsv;
	/*
	 * Check btrfs_delayed_item_reserve_metadata() to see why we करोn't need
	 * to release/reserve qgroup space.
	 */
	trace_btrfs_space_reservation(fs_info, "delayed_item",
				      item->key.objectid, item->bytes_reserved,
				      0);
	btrfs_block_rsv_release(fs_info, rsv, item->bytes_reserved, शून्य);
पूर्ण

अटल पूर्णांक btrfs_delayed_inode_reserve_metadata(
					काष्ठा btrfs_trans_handle *trans,
					काष्ठा btrfs_root *root,
					काष्ठा btrfs_delayed_node *node)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_block_rsv *src_rsv;
	काष्ठा btrfs_block_rsv *dst_rsv;
	u64 num_bytes;
	पूर्णांक ret;

	src_rsv = trans->block_rsv;
	dst_rsv = &fs_info->delayed_block_rsv;

	num_bytes = btrfs_calc_metadata_size(fs_info, 1);

	/*
	 * btrfs_dirty_inode will update the inode under btrfs_join_transaction
	 * which करोesn't reserve space क्रम speed.  This is a problem since we
	 * still need to reserve space क्रम this update, so try to reserve the
	 * space.
	 *
	 * Now अगर src_rsv == delalloc_block_rsv we'll let it just steal since
	 * we always reserve enough to update the inode item.
	 */
	अगर (!src_rsv || (!trans->bytes_reserved &&
			 src_rsv->type != BTRFS_BLOCK_RSV_DELALLOC)) अणु
		ret = btrfs_qgroup_reserve_meta(root, num_bytes,
					  BTRFS_QGROUP_RSV_META_PREALLOC, true);
		अगर (ret < 0)
			वापस ret;
		ret = btrfs_block_rsv_add(root, dst_rsv, num_bytes,
					  BTRFS_RESERVE_NO_FLUSH);
		/* NO_FLUSH could only fail with -ENOSPC */
		ASSERT(ret == 0 || ret == -ENOSPC);
		अगर (ret)
			btrfs_qgroup_मुक्त_meta_pपुनः_स्मृति(root, num_bytes);
	पूर्ण अन्यथा अणु
		ret = btrfs_block_rsv_migrate(src_rsv, dst_rsv, num_bytes, true);
	पूर्ण

	अगर (!ret) अणु
		trace_btrfs_space_reservation(fs_info, "delayed_inode",
					      node->inode_id, num_bytes, 1);
		node->bytes_reserved = num_bytes;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम btrfs_delayed_inode_release_metadata(काष्ठा btrfs_fs_info *fs_info,
						काष्ठा btrfs_delayed_node *node,
						bool qgroup_मुक्त)
अणु
	काष्ठा btrfs_block_rsv *rsv;

	अगर (!node->bytes_reserved)
		वापस;

	rsv = &fs_info->delayed_block_rsv;
	trace_btrfs_space_reservation(fs_info, "delayed_inode",
				      node->inode_id, node->bytes_reserved, 0);
	btrfs_block_rsv_release(fs_info, rsv, node->bytes_reserved, शून्य);
	अगर (qgroup_मुक्त)
		btrfs_qgroup_मुक्त_meta_pपुनः_स्मृति(node->root,
				node->bytes_reserved);
	अन्यथा
		btrfs_qgroup_convert_reserved_meta(node->root,
				node->bytes_reserved);
	node->bytes_reserved = 0;
पूर्ण

/*
 * This helper will insert some continuous items पूर्णांकo the same leaf according
 * to the मुक्त space of the leaf.
 */
अटल पूर्णांक btrfs_batch_insert_items(काष्ठा btrfs_root *root,
				    काष्ठा btrfs_path *path,
				    काष्ठा btrfs_delayed_item *item)
अणु
	काष्ठा btrfs_delayed_item *curr, *next;
	पूर्णांक मुक्त_space;
	पूर्णांक total_data_size = 0, total_size = 0;
	काष्ठा extent_buffer *leaf;
	अक्षर *data_ptr;
	काष्ठा btrfs_key *keys;
	u32 *data_size;
	काष्ठा list_head head;
	पूर्णांक slot;
	पूर्णांक nitems;
	पूर्णांक i;
	पूर्णांक ret = 0;

	BUG_ON(!path->nodes[0]);

	leaf = path->nodes[0];
	मुक्त_space = btrfs_leaf_मुक्त_space(leaf);
	INIT_LIST_HEAD(&head);

	next = item;
	nitems = 0;

	/*
	 * count the number of the continuous items that we can insert in batch
	 */
	जबतक (total_size + next->data_len + माप(काष्ठा btrfs_item) <=
	       मुक्त_space) अणु
		total_data_size += next->data_len;
		total_size += next->data_len + माप(काष्ठा btrfs_item);
		list_add_tail(&next->tree_list, &head);
		nitems++;

		curr = next;
		next = __btrfs_next_delayed_item(curr);
		अगर (!next)
			अवरोध;

		अगर (!btrfs_is_continuous_delayed_item(curr, next))
			अवरोध;
	पूर्ण

	अगर (!nitems) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	keys = kदो_स्मृति_array(nitems, माप(काष्ठा btrfs_key), GFP_NOFS);
	अगर (!keys) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	data_size = kदो_स्मृति_array(nitems, माप(u32), GFP_NOFS);
	अगर (!data_size) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/* get keys of all the delayed items */
	i = 0;
	list_क्रम_each_entry(next, &head, tree_list) अणु
		keys[i] = next->key;
		data_size[i] = next->data_len;
		i++;
	पूर्ण

	/* insert the keys of the items */
	setup_items_क्रम_insert(root, path, keys, data_size, nitems);

	/* insert the dir index items */
	slot = path->slots[0];
	list_क्रम_each_entry_safe(curr, next, &head, tree_list) अणु
		data_ptr = btrfs_item_ptr(leaf, slot, अक्षर);
		ग_लिखो_extent_buffer(leaf, &curr->data,
				    (अचिन्हित दीर्घ)data_ptr,
				    curr->data_len);
		slot++;

		btrfs_delayed_item_release_metadata(root, curr);

		list_del(&curr->tree_list);
		btrfs_release_delayed_item(curr);
	पूर्ण

error:
	kमुक्त(data_size);
	kमुक्त(keys);
out:
	वापस ret;
पूर्ण

/*
 * This helper can just करो simple insertion that needn't extend item क्रम new
 * data, such as directory name index insertion, inode insertion.
 */
अटल पूर्णांक btrfs_insert_delayed_item(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_root *root,
				     काष्ठा btrfs_path *path,
				     काष्ठा btrfs_delayed_item *delayed_item)
अणु
	काष्ठा extent_buffer *leaf;
	अचिन्हित पूर्णांक nofs_flag;
	अक्षर *ptr;
	पूर्णांक ret;

	nofs_flag = meदो_स्मृति_nofs_save();
	ret = btrfs_insert_empty_item(trans, root, path, &delayed_item->key,
				      delayed_item->data_len);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (ret < 0 && ret != -EEXIST)
		वापस ret;

	leaf = path->nodes[0];

	ptr = btrfs_item_ptr(leaf, path->slots[0], अक्षर);

	ग_लिखो_extent_buffer(leaf, delayed_item->data, (अचिन्हित दीर्घ)ptr,
			    delayed_item->data_len);
	btrfs_mark_buffer_dirty(leaf);

	btrfs_delayed_item_release_metadata(root, delayed_item);
	वापस 0;
पूर्ण

/*
 * we insert an item first, then अगर there are some continuous items, we try
 * to insert those items पूर्णांकo the same leaf.
 */
अटल पूर्णांक btrfs_insert_delayed_items(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_path *path,
				      काष्ठा btrfs_root *root,
				      काष्ठा btrfs_delayed_node *node)
अणु
	काष्ठा btrfs_delayed_item *curr, *prev;
	पूर्णांक ret = 0;

करो_again:
	mutex_lock(&node->mutex);
	curr = __btrfs_first_delayed_insertion_item(node);
	अगर (!curr)
		जाओ insert_end;

	ret = btrfs_insert_delayed_item(trans, root, path, curr);
	अगर (ret < 0) अणु
		btrfs_release_path(path);
		जाओ insert_end;
	पूर्ण

	prev = curr;
	curr = __btrfs_next_delayed_item(prev);
	अगर (curr && btrfs_is_continuous_delayed_item(prev, curr)) अणु
		/* insert the continuous items पूर्णांकo the same leaf */
		path->slots[0]++;
		btrfs_batch_insert_items(root, path, curr);
	पूर्ण
	btrfs_release_delayed_item(prev);
	btrfs_mark_buffer_dirty(path->nodes[0]);

	btrfs_release_path(path);
	mutex_unlock(&node->mutex);
	जाओ करो_again;

insert_end:
	mutex_unlock(&node->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_batch_delete_items(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_root *root,
				    काष्ठा btrfs_path *path,
				    काष्ठा btrfs_delayed_item *item)
अणु
	काष्ठा btrfs_delayed_item *curr, *next;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	काष्ठा list_head head;
	पूर्णांक nitems, i, last_item;
	पूर्णांक ret = 0;

	BUG_ON(!path->nodes[0]);

	leaf = path->nodes[0];

	i = path->slots[0];
	last_item = btrfs_header_nritems(leaf) - 1;
	अगर (i > last_item)
		वापस -ENOENT;	/* FIXME: Is त्रुटि_सं suitable? */

	next = item;
	INIT_LIST_HEAD(&head);
	btrfs_item_key_to_cpu(leaf, &key, i);
	nitems = 0;
	/*
	 * count the number of the dir index items that we can delete in batch
	 */
	जबतक (btrfs_comp_cpu_keys(&next->key, &key) == 0) अणु
		list_add_tail(&next->tree_list, &head);
		nitems++;

		curr = next;
		next = __btrfs_next_delayed_item(curr);
		अगर (!next)
			अवरोध;

		अगर (!btrfs_is_continuous_delayed_item(curr, next))
			अवरोध;

		i++;
		अगर (i > last_item)
			अवरोध;
		btrfs_item_key_to_cpu(leaf, &key, i);
	पूर्ण

	अगर (!nitems)
		वापस 0;

	ret = btrfs_del_items(trans, root, path, path->slots[0], nitems);
	अगर (ret)
		जाओ out;

	list_क्रम_each_entry_safe(curr, next, &head, tree_list) अणु
		btrfs_delayed_item_release_metadata(root, curr);
		list_del(&curr->tree_list);
		btrfs_release_delayed_item(curr);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_delete_delayed_items(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_path *path,
				      काष्ठा btrfs_root *root,
				      काष्ठा btrfs_delayed_node *node)
अणु
	काष्ठा btrfs_delayed_item *curr, *prev;
	अचिन्हित पूर्णांक nofs_flag;
	पूर्णांक ret = 0;

करो_again:
	mutex_lock(&node->mutex);
	curr = __btrfs_first_delayed_deletion_item(node);
	अगर (!curr)
		जाओ delete_fail;

	nofs_flag = meदो_स्मृति_nofs_save();
	ret = btrfs_search_slot(trans, root, &curr->key, path, -1, 1);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (ret < 0)
		जाओ delete_fail;
	अन्यथा अगर (ret > 0) अणु
		/*
		 * can't find the item which the node poपूर्णांकs to, so this node
		 * is invalid, just drop it.
		 */
		prev = curr;
		curr = __btrfs_next_delayed_item(prev);
		btrfs_release_delayed_item(prev);
		ret = 0;
		btrfs_release_path(path);
		अगर (curr) अणु
			mutex_unlock(&node->mutex);
			जाओ करो_again;
		पूर्ण अन्यथा
			जाओ delete_fail;
	पूर्ण

	btrfs_batch_delete_items(trans, root, path, curr);
	btrfs_release_path(path);
	mutex_unlock(&node->mutex);
	जाओ करो_again;

delete_fail:
	btrfs_release_path(path);
	mutex_unlock(&node->mutex);
	वापस ret;
पूर्ण

अटल व्योम btrfs_release_delayed_inode(काष्ठा btrfs_delayed_node *delayed_node)
अणु
	काष्ठा btrfs_delayed_root *delayed_root;

	अगर (delayed_node &&
	    test_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &delayed_node->flags)) अणु
		BUG_ON(!delayed_node->root);
		clear_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &delayed_node->flags);
		delayed_node->count--;

		delayed_root = delayed_node->root->fs_info->delayed_root;
		finish_one_item(delayed_root);
	पूर्ण
पूर्ण

अटल व्योम btrfs_release_delayed_iref(काष्ठा btrfs_delayed_node *delayed_node)
अणु
	काष्ठा btrfs_delayed_root *delayed_root;

	ASSERT(delayed_node->root);
	clear_bit(BTRFS_DELAYED_NODE_DEL_IREF, &delayed_node->flags);
	delayed_node->count--;

	delayed_root = delayed_node->root->fs_info->delayed_root;
	finish_one_item(delayed_root);
पूर्ण

अटल पूर्णांक __btrfs_update_delayed_inode(काष्ठा btrfs_trans_handle *trans,
					काष्ठा btrfs_root *root,
					काष्ठा btrfs_path *path,
					काष्ठा btrfs_delayed_node *node)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_inode_item *inode_item;
	काष्ठा extent_buffer *leaf;
	अचिन्हित पूर्णांक nofs_flag;
	पूर्णांक mod;
	पूर्णांक ret;

	key.objectid = node->inode_id;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	अगर (test_bit(BTRFS_DELAYED_NODE_DEL_IREF, &node->flags))
		mod = -1;
	अन्यथा
		mod = 1;

	nofs_flag = meदो_स्मृति_nofs_save();
	ret = btrfs_lookup_inode(trans, root, path, &key, mod);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (ret > 0) अणु
		btrfs_release_path(path);
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		वापस ret;
	पूर्ण

	leaf = path->nodes[0];
	inode_item = btrfs_item_ptr(leaf, path->slots[0],
				    काष्ठा btrfs_inode_item);
	ग_लिखो_extent_buffer(leaf, &node->inode_item, (अचिन्हित दीर्घ)inode_item,
			    माप(काष्ठा btrfs_inode_item));
	btrfs_mark_buffer_dirty(leaf);

	अगर (!test_bit(BTRFS_DELAYED_NODE_DEL_IREF, &node->flags))
		जाओ no_iref;

	path->slots[0]++;
	अगर (path->slots[0] >= btrfs_header_nritems(leaf))
		जाओ search;
again:
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
	अगर (key.objectid != node->inode_id)
		जाओ out;

	अगर (key.type != BTRFS_INODE_REF_KEY &&
	    key.type != BTRFS_INODE_EXTREF_KEY)
		जाओ out;

	/*
	 * Delayed iref deletion is क्रम the inode who has only one link,
	 * so there is only one iref. The हाल that several irefs are
	 * in the same item करोesn't exist.
	 */
	btrfs_del_item(trans, root, path);
out:
	btrfs_release_delayed_iref(node);
no_iref:
	btrfs_release_path(path);
err_out:
	btrfs_delayed_inode_release_metadata(fs_info, node, (ret < 0));
	btrfs_release_delayed_inode(node);

	वापस ret;

search:
	btrfs_release_path(path);

	key.type = BTRFS_INODE_EXTREF_KEY;
	key.offset = -1;

	nofs_flag = meदो_स्मृति_nofs_save();
	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (ret < 0)
		जाओ err_out;
	ASSERT(ret);

	ret = 0;
	leaf = path->nodes[0];
	path->slots[0]--;
	जाओ again;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_update_delayed_inode(काष्ठा btrfs_trans_handle *trans,
					     काष्ठा btrfs_root *root,
					     काष्ठा btrfs_path *path,
					     काष्ठा btrfs_delayed_node *node)
अणु
	पूर्णांक ret;

	mutex_lock(&node->mutex);
	अगर (!test_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &node->flags)) अणु
		mutex_unlock(&node->mutex);
		वापस 0;
	पूर्ण

	ret = __btrfs_update_delayed_inode(trans, root, path, node);
	mutex_unlock(&node->mutex);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
__btrfs_commit_inode_delayed_items(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_path *path,
				   काष्ठा btrfs_delayed_node *node)
अणु
	पूर्णांक ret;

	ret = btrfs_insert_delayed_items(trans, path, node->root, node);
	अगर (ret)
		वापस ret;

	ret = btrfs_delete_delayed_items(trans, path, node->root, node);
	अगर (ret)
		वापस ret;

	ret = btrfs_update_delayed_inode(trans, node->root, path, node);
	वापस ret;
पूर्ण

/*
 * Called when committing the transaction.
 * Returns 0 on success.
 * Returns < 0 on error and वापसs with an पातed transaction with any
 * outstanding delayed items cleaned up.
 */
अटल पूर्णांक __btrfs_run_delayed_items(काष्ठा btrfs_trans_handle *trans, पूर्णांक nr)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_delayed_root *delayed_root;
	काष्ठा btrfs_delayed_node *curr_node, *prev_node;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_block_rsv *block_rsv;
	पूर्णांक ret = 0;
	bool count = (nr > 0);

	अगर (TRANS_ABORTED(trans))
		वापस -EIO;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	block_rsv = trans->block_rsv;
	trans->block_rsv = &fs_info->delayed_block_rsv;

	delayed_root = fs_info->delayed_root;

	curr_node = btrfs_first_delayed_node(delayed_root);
	जबतक (curr_node && (!count || nr--)) अणु
		ret = __btrfs_commit_inode_delayed_items(trans, path,
							 curr_node);
		अगर (ret) अणु
			btrfs_release_delayed_node(curr_node);
			curr_node = शून्य;
			btrfs_पात_transaction(trans, ret);
			अवरोध;
		पूर्ण

		prev_node = curr_node;
		curr_node = btrfs_next_delayed_node(curr_node);
		btrfs_release_delayed_node(prev_node);
	पूर्ण

	अगर (curr_node)
		btrfs_release_delayed_node(curr_node);
	btrfs_मुक्त_path(path);
	trans->block_rsv = block_rsv;

	वापस ret;
पूर्ण

पूर्णांक btrfs_run_delayed_items(काष्ठा btrfs_trans_handle *trans)
अणु
	वापस __btrfs_run_delayed_items(trans, -1);
पूर्ण

पूर्णांक btrfs_run_delayed_items_nr(काष्ठा btrfs_trans_handle *trans, पूर्णांक nr)
अणु
	वापस __btrfs_run_delayed_items(trans, nr);
पूर्ण

पूर्णांक btrfs_commit_inode_delayed_items(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_delayed_node *delayed_node = btrfs_get_delayed_node(inode);
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_block_rsv *block_rsv;
	पूर्णांक ret;

	अगर (!delayed_node)
		वापस 0;

	mutex_lock(&delayed_node->mutex);
	अगर (!delayed_node->count) अणु
		mutex_unlock(&delayed_node->mutex);
		btrfs_release_delayed_node(delayed_node);
		वापस 0;
	पूर्ण
	mutex_unlock(&delayed_node->mutex);

	path = btrfs_alloc_path();
	अगर (!path) अणु
		btrfs_release_delayed_node(delayed_node);
		वापस -ENOMEM;
	पूर्ण

	block_rsv = trans->block_rsv;
	trans->block_rsv = &delayed_node->root->fs_info->delayed_block_rsv;

	ret = __btrfs_commit_inode_delayed_items(trans, path, delayed_node);

	btrfs_release_delayed_node(delayed_node);
	btrfs_मुक्त_path(path);
	trans->block_rsv = block_rsv;

	वापस ret;
पूर्ण

पूर्णांक btrfs_commit_inode_delayed_inode(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_delayed_node *delayed_node = btrfs_get_delayed_node(inode);
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_block_rsv *block_rsv;
	पूर्णांक ret;

	अगर (!delayed_node)
		वापस 0;

	mutex_lock(&delayed_node->mutex);
	अगर (!test_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &delayed_node->flags)) अणु
		mutex_unlock(&delayed_node->mutex);
		btrfs_release_delayed_node(delayed_node);
		वापस 0;
	पूर्ण
	mutex_unlock(&delayed_node->mutex);

	trans = btrfs_join_transaction(delayed_node->root);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ out;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ trans_out;
	पूर्ण

	block_rsv = trans->block_rsv;
	trans->block_rsv = &fs_info->delayed_block_rsv;

	mutex_lock(&delayed_node->mutex);
	अगर (test_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &delayed_node->flags))
		ret = __btrfs_update_delayed_inode(trans, delayed_node->root,
						   path, delayed_node);
	अन्यथा
		ret = 0;
	mutex_unlock(&delayed_node->mutex);

	btrfs_मुक्त_path(path);
	trans->block_rsv = block_rsv;
trans_out:
	btrfs_end_transaction(trans);
	btrfs_btree_balance_dirty(fs_info);
out:
	btrfs_release_delayed_node(delayed_node);

	वापस ret;
पूर्ण

व्योम btrfs_हटाओ_delayed_node(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_delayed_node *delayed_node;

	delayed_node = READ_ONCE(inode->delayed_node);
	अगर (!delayed_node)
		वापस;

	inode->delayed_node = शून्य;
	btrfs_release_delayed_node(delayed_node);
पूर्ण

काष्ठा btrfs_async_delayed_work अणु
	काष्ठा btrfs_delayed_root *delayed_root;
	पूर्णांक nr;
	काष्ठा btrfs_work work;
पूर्ण;

अटल व्योम btrfs_async_run_delayed_root(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_async_delayed_work *async_work;
	काष्ठा btrfs_delayed_root *delayed_root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_delayed_node *delayed_node = शून्य;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_block_rsv *block_rsv;
	पूर्णांक total_करोne = 0;

	async_work = container_of(work, काष्ठा btrfs_async_delayed_work, work);
	delayed_root = async_work->delayed_root;

	path = btrfs_alloc_path();
	अगर (!path)
		जाओ out;

	करो अणु
		अगर (atomic_पढ़ो(&delayed_root->items) <
		    BTRFS_DELAYED_BACKGROUND / 2)
			अवरोध;

		delayed_node = btrfs_first_prepared_delayed_node(delayed_root);
		अगर (!delayed_node)
			अवरोध;

		root = delayed_node->root;

		trans = btrfs_join_transaction(root);
		अगर (IS_ERR(trans)) अणु
			btrfs_release_path(path);
			btrfs_release_prepared_delayed_node(delayed_node);
			total_करोne++;
			जारी;
		पूर्ण

		block_rsv = trans->block_rsv;
		trans->block_rsv = &root->fs_info->delayed_block_rsv;

		__btrfs_commit_inode_delayed_items(trans, path, delayed_node);

		trans->block_rsv = block_rsv;
		btrfs_end_transaction(trans);
		btrfs_btree_balance_dirty_nodelay(root->fs_info);

		btrfs_release_path(path);
		btrfs_release_prepared_delayed_node(delayed_node);
		total_करोne++;

	पूर्ण जबतक ((async_work->nr == 0 && total_करोne < BTRFS_DELAYED_WRITEBACK)
		 || total_करोne < async_work->nr);

	btrfs_मुक्त_path(path);
out:
	wake_up(&delayed_root->रुको);
	kमुक्त(async_work);
पूर्ण


अटल पूर्णांक btrfs_wq_run_delayed_node(काष्ठा btrfs_delayed_root *delayed_root,
				     काष्ठा btrfs_fs_info *fs_info, पूर्णांक nr)
अणु
	काष्ठा btrfs_async_delayed_work *async_work;

	async_work = kदो_स्मृति(माप(*async_work), GFP_NOFS);
	अगर (!async_work)
		वापस -ENOMEM;

	async_work->delayed_root = delayed_root;
	btrfs_init_work(&async_work->work, btrfs_async_run_delayed_root, शून्य,
			शून्य);
	async_work->nr = nr;

	btrfs_queue_work(fs_info->delayed_workers, &async_work->work);
	वापस 0;
पूर्ण

व्योम btrfs_निश्चित_delayed_root_empty(काष्ठा btrfs_fs_info *fs_info)
अणु
	WARN_ON(btrfs_first_delayed_node(fs_info->delayed_root));
पूर्ण

अटल पूर्णांक could_end_रुको(काष्ठा btrfs_delayed_root *delayed_root, पूर्णांक seq)
अणु
	पूर्णांक val = atomic_पढ़ो(&delayed_root->items_seq);

	अगर (val < seq || val >= seq + BTRFS_DELAYED_BATCH)
		वापस 1;

	अगर (atomic_पढ़ो(&delayed_root->items) < BTRFS_DELAYED_BACKGROUND)
		वापस 1;

	वापस 0;
पूर्ण

व्योम btrfs_balance_delayed_items(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_delayed_root *delayed_root = fs_info->delayed_root;

	अगर ((atomic_पढ़ो(&delayed_root->items) < BTRFS_DELAYED_BACKGROUND) ||
		btrfs_workqueue_normal_congested(fs_info->delayed_workers))
		वापस;

	अगर (atomic_पढ़ो(&delayed_root->items) >= BTRFS_DELAYED_WRITEBACK) अणु
		पूर्णांक seq;
		पूर्णांक ret;

		seq = atomic_पढ़ो(&delayed_root->items_seq);

		ret = btrfs_wq_run_delayed_node(delayed_root, fs_info, 0);
		अगर (ret)
			वापस;

		रुको_event_पूर्णांकerruptible(delayed_root->रुको,
					 could_end_रुको(delayed_root, seq));
		वापस;
	पूर्ण

	btrfs_wq_run_delayed_node(delayed_root, fs_info, BTRFS_DELAYED_BATCH);
पूर्ण

/* Will वापस 0 or -ENOMEM */
पूर्णांक btrfs_insert_delayed_dir_index(काष्ठा btrfs_trans_handle *trans,
				   स्थिर अक्षर *name, पूर्णांक name_len,
				   काष्ठा btrfs_inode *dir,
				   काष्ठा btrfs_disk_key *disk_key, u8 type,
				   u64 index)
अणु
	काष्ठा btrfs_delayed_node *delayed_node;
	काष्ठा btrfs_delayed_item *delayed_item;
	काष्ठा btrfs_dir_item *dir_item;
	पूर्णांक ret;

	delayed_node = btrfs_get_or_create_delayed_node(dir);
	अगर (IS_ERR(delayed_node))
		वापस PTR_ERR(delayed_node);

	delayed_item = btrfs_alloc_delayed_item(माप(*dir_item) + name_len);
	अगर (!delayed_item) अणु
		ret = -ENOMEM;
		जाओ release_node;
	पूर्ण

	delayed_item->key.objectid = btrfs_ino(dir);
	delayed_item->key.type = BTRFS_सूची_INDEX_KEY;
	delayed_item->key.offset = index;

	dir_item = (काष्ठा btrfs_dir_item *)delayed_item->data;
	dir_item->location = *disk_key;
	btrfs_set_stack_dir_transid(dir_item, trans->transid);
	btrfs_set_stack_dir_data_len(dir_item, 0);
	btrfs_set_stack_dir_name_len(dir_item, name_len);
	btrfs_set_stack_dir_type(dir_item, type);
	स_नकल((अक्षर *)(dir_item + 1), name, name_len);

	ret = btrfs_delayed_item_reserve_metadata(trans, dir->root, delayed_item);
	/*
	 * we have reserved enough space when we start a new transaction,
	 * so reserving metadata failure is impossible
	 */
	BUG_ON(ret);

	mutex_lock(&delayed_node->mutex);
	ret = __btrfs_add_delayed_insertion_item(delayed_node, delayed_item);
	अगर (unlikely(ret)) अणु
		btrfs_err(trans->fs_info,
			  "err add delayed dir index item(name: %.*s) into the insertion tree of the delayed node(root id: %llu, inode id: %llu, errno: %d)",
			  name_len, name, delayed_node->root->root_key.objectid,
			  delayed_node->inode_id, ret);
		BUG();
	पूर्ण
	mutex_unlock(&delayed_node->mutex);

release_node:
	btrfs_release_delayed_node(delayed_node);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_delete_delayed_insertion_item(काष्ठा btrfs_fs_info *fs_info,
					       काष्ठा btrfs_delayed_node *node,
					       काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_delayed_item *item;

	mutex_lock(&node->mutex);
	item = __btrfs_lookup_delayed_insertion_item(node, key);
	अगर (!item) अणु
		mutex_unlock(&node->mutex);
		वापस 1;
	पूर्ण

	btrfs_delayed_item_release_metadata(node->root, item);
	btrfs_release_delayed_item(item);
	mutex_unlock(&node->mutex);
	वापस 0;
पूर्ण

पूर्णांक btrfs_delete_delayed_dir_index(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_inode *dir, u64 index)
अणु
	काष्ठा btrfs_delayed_node *node;
	काष्ठा btrfs_delayed_item *item;
	काष्ठा btrfs_key item_key;
	पूर्णांक ret;

	node = btrfs_get_or_create_delayed_node(dir);
	अगर (IS_ERR(node))
		वापस PTR_ERR(node);

	item_key.objectid = btrfs_ino(dir);
	item_key.type = BTRFS_सूची_INDEX_KEY;
	item_key.offset = index;

	ret = btrfs_delete_delayed_insertion_item(trans->fs_info, node,
						  &item_key);
	अगर (!ret)
		जाओ end;

	item = btrfs_alloc_delayed_item(0);
	अगर (!item) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	item->key = item_key;

	ret = btrfs_delayed_item_reserve_metadata(trans, dir->root, item);
	/*
	 * we have reserved enough space when we start a new transaction,
	 * so reserving metadata failure is impossible.
	 */
	अगर (ret < 0) अणु
		btrfs_err(trans->fs_info,
"metadata reservation failed for delayed dir item deltiona, should have been reserved");
		btrfs_release_delayed_item(item);
		जाओ end;
	पूर्ण

	mutex_lock(&node->mutex);
	ret = __btrfs_add_delayed_deletion_item(node, item);
	अगर (unlikely(ret)) अणु
		btrfs_err(trans->fs_info,
			  "err add delayed dir index item(index: %llu) into the deletion tree of the delayed node(root id: %llu, inode id: %llu, errno: %d)",
			  index, node->root->root_key.objectid,
			  node->inode_id, ret);
		btrfs_delayed_item_release_metadata(dir->root, item);
		btrfs_release_delayed_item(item);
	पूर्ण
	mutex_unlock(&node->mutex);
end:
	btrfs_release_delayed_node(node);
	वापस ret;
पूर्ण

पूर्णांक btrfs_inode_delayed_dir_index_count(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_delayed_node *delayed_node = btrfs_get_delayed_node(inode);

	अगर (!delayed_node)
		वापस -ENOENT;

	/*
	 * Since we have held i_mutex of this directory, it is impossible that
	 * a new directory index is added पूर्णांकo the delayed node and index_cnt
	 * is updated now. So we needn't lock the delayed node.
	 */
	अगर (!delayed_node->index_cnt) अणु
		btrfs_release_delayed_node(delayed_node);
		वापस -EINVAL;
	पूर्ण

	inode->index_cnt = delayed_node->index_cnt;
	btrfs_release_delayed_node(delayed_node);
	वापस 0;
पूर्ण

bool btrfs_सूची_पढ़ो_get_delayed_items(काष्ठा inode *inode,
				     काष्ठा list_head *ins_list,
				     काष्ठा list_head *del_list)
अणु
	काष्ठा btrfs_delayed_node *delayed_node;
	काष्ठा btrfs_delayed_item *item;

	delayed_node = btrfs_get_delayed_node(BTRFS_I(inode));
	अगर (!delayed_node)
		वापस false;

	/*
	 * We can only करो one सूची_पढ़ो with delayed items at a समय because of
	 * item->सूची_पढ़ो_list.
	 */
	btrfs_inode_unlock(inode, BTRFS_ILOCK_SHARED);
	btrfs_inode_lock(inode, 0);

	mutex_lock(&delayed_node->mutex);
	item = __btrfs_first_delayed_insertion_item(delayed_node);
	जबतक (item) अणु
		refcount_inc(&item->refs);
		list_add_tail(&item->सूची_पढ़ो_list, ins_list);
		item = __btrfs_next_delayed_item(item);
	पूर्ण

	item = __btrfs_first_delayed_deletion_item(delayed_node);
	जबतक (item) अणु
		refcount_inc(&item->refs);
		list_add_tail(&item->सूची_पढ़ो_list, del_list);
		item = __btrfs_next_delayed_item(item);
	पूर्ण
	mutex_unlock(&delayed_node->mutex);
	/*
	 * This delayed node is still cached in the btrfs inode, so refs
	 * must be > 1 now, and we needn't check it is going to be मुक्तd
	 * or not.
	 *
	 * Besides that, this function is used to पढ़ो dir, we करो not
	 * insert/delete delayed items in this period. So we also needn't
	 * requeue or dequeue this delayed node.
	 */
	refcount_dec(&delayed_node->refs);

	वापस true;
पूर्ण

व्योम btrfs_सूची_पढ़ो_put_delayed_items(काष्ठा inode *inode,
				     काष्ठा list_head *ins_list,
				     काष्ठा list_head *del_list)
अणु
	काष्ठा btrfs_delayed_item *curr, *next;

	list_क्रम_each_entry_safe(curr, next, ins_list, सूची_पढ़ो_list) अणु
		list_del(&curr->सूची_पढ़ो_list);
		अगर (refcount_dec_and_test(&curr->refs))
			kमुक्त(curr);
	पूर्ण

	list_क्रम_each_entry_safe(curr, next, del_list, सूची_पढ़ो_list) अणु
		list_del(&curr->सूची_पढ़ो_list);
		अगर (refcount_dec_and_test(&curr->refs))
			kमुक्त(curr);
	पूर्ण

	/*
	 * The VFS is going to करो up_पढ़ो(), so we need to करोwngrade back to a
	 * पढ़ो lock.
	 */
	करोwngrade_ग_लिखो(&inode->i_rwsem);
पूर्ण

पूर्णांक btrfs_should_delete_dir_index(काष्ठा list_head *del_list,
				  u64 index)
अणु
	काष्ठा btrfs_delayed_item *curr;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(curr, del_list, सूची_पढ़ो_list) अणु
		अगर (curr->key.offset > index)
			अवरोध;
		अगर (curr->key.offset == index) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * btrfs_सूची_पढ़ो_delayed_dir_index - पढ़ो dir info stored in the delayed tree
 *
 */
पूर्णांक btrfs_सूची_पढ़ो_delayed_dir_index(काष्ठा dir_context *ctx,
				    काष्ठा list_head *ins_list)
अणु
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_delayed_item *curr, *next;
	काष्ठा btrfs_key location;
	अक्षर *name;
	पूर्णांक name_len;
	पूर्णांक over = 0;
	अचिन्हित अक्षर d_type;

	अगर (list_empty(ins_list))
		वापस 0;

	/*
	 * Changing the data of the delayed item is impossible. So
	 * we needn't lock them. And we have held i_mutex of the
	 * directory, nobody can delete any directory indexes now.
	 */
	list_क्रम_each_entry_safe(curr, next, ins_list, सूची_पढ़ो_list) अणु
		list_del(&curr->सूची_पढ़ो_list);

		अगर (curr->key.offset < ctx->pos) अणु
			अगर (refcount_dec_and_test(&curr->refs))
				kमुक्त(curr);
			जारी;
		पूर्ण

		ctx->pos = curr->key.offset;

		di = (काष्ठा btrfs_dir_item *)curr->data;
		name = (अक्षर *)(di + 1);
		name_len = btrfs_stack_dir_name_len(di);

		d_type = fs_ftype_to_dtype(di->type);
		btrfs_disk_key_to_cpu(&location, &di->location);

		over = !dir_emit(ctx, name, name_len,
			       location.objectid, d_type);

		अगर (refcount_dec_and_test(&curr->refs))
			kमुक्त(curr);

		अगर (over)
			वापस 1;
		ctx->pos++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fill_stack_inode_item(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_inode_item *inode_item,
				  काष्ठा inode *inode)
अणु
	btrfs_set_stack_inode_uid(inode_item, i_uid_पढ़ो(inode));
	btrfs_set_stack_inode_gid(inode_item, i_gid_पढ़ो(inode));
	btrfs_set_stack_inode_size(inode_item, BTRFS_I(inode)->disk_i_size);
	btrfs_set_stack_inode_mode(inode_item, inode->i_mode);
	btrfs_set_stack_inode_nlink(inode_item, inode->i_nlink);
	btrfs_set_stack_inode_nbytes(inode_item, inode_get_bytes(inode));
	btrfs_set_stack_inode_generation(inode_item,
					 BTRFS_I(inode)->generation);
	btrfs_set_stack_inode_sequence(inode_item,
				       inode_peek_iversion(inode));
	btrfs_set_stack_inode_transid(inode_item, trans->transid);
	btrfs_set_stack_inode_rdev(inode_item, inode->i_rdev);
	btrfs_set_stack_inode_flags(inode_item, BTRFS_I(inode)->flags);
	btrfs_set_stack_inode_block_group(inode_item, 0);

	btrfs_set_stack_बारpec_sec(&inode_item->aसमय,
				     inode->i_aसमय.tv_sec);
	btrfs_set_stack_बारpec_nsec(&inode_item->aसमय,
				      inode->i_aसमय.tv_nsec);

	btrfs_set_stack_बारpec_sec(&inode_item->mसमय,
				     inode->i_mसमय.tv_sec);
	btrfs_set_stack_बारpec_nsec(&inode_item->mसमय,
				      inode->i_mसमय.tv_nsec);

	btrfs_set_stack_बारpec_sec(&inode_item->स_समय,
				     inode->i_स_समय.tv_sec);
	btrfs_set_stack_बारpec_nsec(&inode_item->स_समय,
				      inode->i_स_समय.tv_nsec);

	btrfs_set_stack_बारpec_sec(&inode_item->oसमय,
				     BTRFS_I(inode)->i_oसमय.tv_sec);
	btrfs_set_stack_बारpec_nsec(&inode_item->oसमय,
				     BTRFS_I(inode)->i_oसमय.tv_nsec);
पूर्ण

पूर्णांक btrfs_fill_inode(काष्ठा inode *inode, u32 *rdev)
अणु
	काष्ठा btrfs_fs_info *fs_info = BTRFS_I(inode)->root->fs_info;
	काष्ठा btrfs_delayed_node *delayed_node;
	काष्ठा btrfs_inode_item *inode_item;

	delayed_node = btrfs_get_delayed_node(BTRFS_I(inode));
	अगर (!delayed_node)
		वापस -ENOENT;

	mutex_lock(&delayed_node->mutex);
	अगर (!test_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &delayed_node->flags)) अणु
		mutex_unlock(&delayed_node->mutex);
		btrfs_release_delayed_node(delayed_node);
		वापस -ENOENT;
	पूर्ण

	inode_item = &delayed_node->inode_item;

	i_uid_ग_लिखो(inode, btrfs_stack_inode_uid(inode_item));
	i_gid_ग_लिखो(inode, btrfs_stack_inode_gid(inode_item));
	btrfs_i_size_ग_लिखो(BTRFS_I(inode), btrfs_stack_inode_size(inode_item));
	btrfs_inode_set_file_extent_range(BTRFS_I(inode), 0,
			round_up(i_size_पढ़ो(inode), fs_info->sectorsize));
	inode->i_mode = btrfs_stack_inode_mode(inode_item);
	set_nlink(inode, btrfs_stack_inode_nlink(inode_item));
	inode_set_bytes(inode, btrfs_stack_inode_nbytes(inode_item));
	BTRFS_I(inode)->generation = btrfs_stack_inode_generation(inode_item);
        BTRFS_I(inode)->last_trans = btrfs_stack_inode_transid(inode_item);

	inode_set_iversion_queried(inode,
				   btrfs_stack_inode_sequence(inode_item));
	inode->i_rdev = 0;
	*rdev = btrfs_stack_inode_rdev(inode_item);
	BTRFS_I(inode)->flags = btrfs_stack_inode_flags(inode_item);

	inode->i_aसमय.tv_sec = btrfs_stack_बारpec_sec(&inode_item->aसमय);
	inode->i_aसमय.tv_nsec = btrfs_stack_बारpec_nsec(&inode_item->aसमय);

	inode->i_mसमय.tv_sec = btrfs_stack_बारpec_sec(&inode_item->mसमय);
	inode->i_mसमय.tv_nsec = btrfs_stack_बारpec_nsec(&inode_item->mसमय);

	inode->i_स_समय.tv_sec = btrfs_stack_बारpec_sec(&inode_item->स_समय);
	inode->i_स_समय.tv_nsec = btrfs_stack_बारpec_nsec(&inode_item->स_समय);

	BTRFS_I(inode)->i_oसमय.tv_sec =
		btrfs_stack_बारpec_sec(&inode_item->oसमय);
	BTRFS_I(inode)->i_oसमय.tv_nsec =
		btrfs_stack_बारpec_nsec(&inode_item->oसमय);

	inode->i_generation = BTRFS_I(inode)->generation;
	BTRFS_I(inode)->index_cnt = (u64)-1;

	mutex_unlock(&delayed_node->mutex);
	btrfs_release_delayed_node(delayed_node);
	वापस 0;
पूर्ण

पूर्णांक btrfs_delayed_update_inode(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_root *root,
			       काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_delayed_node *delayed_node;
	पूर्णांक ret = 0;

	delayed_node = btrfs_get_or_create_delayed_node(inode);
	अगर (IS_ERR(delayed_node))
		वापस PTR_ERR(delayed_node);

	mutex_lock(&delayed_node->mutex);
	अगर (test_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &delayed_node->flags)) अणु
		fill_stack_inode_item(trans, &delayed_node->inode_item,
				      &inode->vfs_inode);
		जाओ release_node;
	पूर्ण

	ret = btrfs_delayed_inode_reserve_metadata(trans, root, delayed_node);
	अगर (ret)
		जाओ release_node;

	fill_stack_inode_item(trans, &delayed_node->inode_item, &inode->vfs_inode);
	set_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &delayed_node->flags);
	delayed_node->count++;
	atomic_inc(&root->fs_info->delayed_root->items);
release_node:
	mutex_unlock(&delayed_node->mutex);
	btrfs_release_delayed_node(delayed_node);
	वापस ret;
पूर्ण

पूर्णांक btrfs_delayed_delete_inode_ref(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_delayed_node *delayed_node;

	/*
	 * we करोn't करो delayed inode updates during log recovery because it
	 * leads to enospc problems.  This means we also can't करो
	 * delayed inode refs
	 */
	अगर (test_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags))
		वापस -EAGAIN;

	delayed_node = btrfs_get_or_create_delayed_node(inode);
	अगर (IS_ERR(delayed_node))
		वापस PTR_ERR(delayed_node);

	/*
	 * We करोn't reserve space क्रम inode ref deletion is because:
	 * - We ONLY करो async inode ref deletion क्रम the inode who has only
	 *   one link(i_nlink == 1), it means there is only one inode ref.
	 *   And in most हाल, the inode ref and the inode item are in the
	 *   same leaf, and we will deal with them at the same समय.
	 *   Since we are sure we will reserve the space क्रम the inode item,
	 *   it is unnecessary to reserve space क्रम inode ref deletion.
	 * - If the inode ref and the inode item are not in the same leaf,
	 *   We also needn't worry about enospc problem, because we reserve
	 *   much more space क्रम the inode update than it needs.
	 * - At the worst, we can steal some space from the global reservation.
	 *   It is very rare.
	 */
	mutex_lock(&delayed_node->mutex);
	अगर (test_bit(BTRFS_DELAYED_NODE_DEL_IREF, &delayed_node->flags))
		जाओ release_node;

	set_bit(BTRFS_DELAYED_NODE_DEL_IREF, &delayed_node->flags);
	delayed_node->count++;
	atomic_inc(&fs_info->delayed_root->items);
release_node:
	mutex_unlock(&delayed_node->mutex);
	btrfs_release_delayed_node(delayed_node);
	वापस 0;
पूर्ण

अटल व्योम __btrfs_समाप्त_delayed_node(काष्ठा btrfs_delayed_node *delayed_node)
अणु
	काष्ठा btrfs_root *root = delayed_node->root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_delayed_item *curr_item, *prev_item;

	mutex_lock(&delayed_node->mutex);
	curr_item = __btrfs_first_delayed_insertion_item(delayed_node);
	जबतक (curr_item) अणु
		btrfs_delayed_item_release_metadata(root, curr_item);
		prev_item = curr_item;
		curr_item = __btrfs_next_delayed_item(prev_item);
		btrfs_release_delayed_item(prev_item);
	पूर्ण

	curr_item = __btrfs_first_delayed_deletion_item(delayed_node);
	जबतक (curr_item) अणु
		btrfs_delayed_item_release_metadata(root, curr_item);
		prev_item = curr_item;
		curr_item = __btrfs_next_delayed_item(prev_item);
		btrfs_release_delayed_item(prev_item);
	पूर्ण

	अगर (test_bit(BTRFS_DELAYED_NODE_DEL_IREF, &delayed_node->flags))
		btrfs_release_delayed_iref(delayed_node);

	अगर (test_bit(BTRFS_DELAYED_NODE_INODE_सूचीTY, &delayed_node->flags)) अणु
		btrfs_delayed_inode_release_metadata(fs_info, delayed_node, false);
		btrfs_release_delayed_inode(delayed_node);
	पूर्ण
	mutex_unlock(&delayed_node->mutex);
पूर्ण

व्योम btrfs_समाप्त_delayed_inode_items(काष्ठा btrfs_inode *inode)
अणु
	काष्ठा btrfs_delayed_node *delayed_node;

	delayed_node = btrfs_get_delayed_node(inode);
	अगर (!delayed_node)
		वापस;

	__btrfs_समाप्त_delayed_node(delayed_node);
	btrfs_release_delayed_node(delayed_node);
पूर्ण

व्योम btrfs_समाप्त_all_delayed_nodes(काष्ठा btrfs_root *root)
अणु
	u64 inode_id = 0;
	काष्ठा btrfs_delayed_node *delayed_nodes[8];
	पूर्णांक i, n;

	जबतक (1) अणु
		spin_lock(&root->inode_lock);
		n = radix_tree_gang_lookup(&root->delayed_nodes_tree,
					   (व्योम **)delayed_nodes, inode_id,
					   ARRAY_SIZE(delayed_nodes));
		अगर (!n) अणु
			spin_unlock(&root->inode_lock);
			अवरोध;
		पूर्ण

		inode_id = delayed_nodes[n - 1]->inode_id + 1;
		क्रम (i = 0; i < n; i++) अणु
			/*
			 * Don't increase refs in हाल the node is dead and
			 * about to be हटाओd from the tree in the loop below
			 */
			अगर (!refcount_inc_not_zero(&delayed_nodes[i]->refs))
				delayed_nodes[i] = शून्य;
		पूर्ण
		spin_unlock(&root->inode_lock);

		क्रम (i = 0; i < n; i++) अणु
			अगर (!delayed_nodes[i])
				जारी;
			__btrfs_समाप्त_delayed_node(delayed_nodes[i]);
			btrfs_release_delayed_node(delayed_nodes[i]);
		पूर्ण
	पूर्ण
पूर्ण

व्योम btrfs_destroy_delayed_inodes(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_delayed_node *curr_node, *prev_node;

	curr_node = btrfs_first_delayed_node(fs_info->delayed_root);
	जबतक (curr_node) अणु
		__btrfs_समाप्त_delayed_node(curr_node);

		prev_node = curr_node;
		curr_node = btrfs_next_delayed_node(curr_node);
		btrfs_release_delayed_node(prev_node);
	पूर्ण
पूर्ण

