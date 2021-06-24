<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश "ctree.h"
#समावेश "delayed-ref.h"
#समावेश "transaction.h"
#समावेश "qgroup.h"
#समावेश "space-info.h"
#समावेश "tree-mod-log.h"

काष्ठा kmem_cache *btrfs_delayed_ref_head_cachep;
काष्ठा kmem_cache *btrfs_delayed_tree_ref_cachep;
काष्ठा kmem_cache *btrfs_delayed_data_ref_cachep;
काष्ठा kmem_cache *btrfs_delayed_extent_op_cachep;
/*
 * delayed back reference update tracking.  For subvolume trees
 * we queue up extent allocations and backref मुख्यtenance क्रम
 * delayed processing.   This aव्योमs deep call chains where we
 * add extents in the middle of btrfs_search_slot, and it allows
 * us to buffer up frequently modअगरied backrefs in an rb tree instead
 * of hammering updates on the extent allocation tree.
 */

bool btrfs_check_space_क्रम_delayed_refs(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_block_rsv *delayed_refs_rsv = &fs_info->delayed_refs_rsv;
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	bool ret = false;
	u64 reserved;

	spin_lock(&global_rsv->lock);
	reserved = global_rsv->reserved;
	spin_unlock(&global_rsv->lock);

	/*
	 * Since the global reserve is just kind of magic we करोn't really want
	 * to rely on it to save our bacon, so अगर our size is more than the
	 * delayed_refs_rsv and the global rsv then it's समय to think about
	 * bailing.
	 */
	spin_lock(&delayed_refs_rsv->lock);
	reserved += delayed_refs_rsv->reserved;
	अगर (delayed_refs_rsv->size >= reserved)
		ret = true;
	spin_unlock(&delayed_refs_rsv->lock);
	वापस ret;
पूर्ण

पूर्णांक btrfs_should_throttle_delayed_refs(काष्ठा btrfs_trans_handle *trans)
अणु
	u64 num_entries =
		atomic_पढ़ो(&trans->transaction->delayed_refs.num_entries);
	u64 avg_runसमय;
	u64 val;

	smp_mb();
	avg_runसमय = trans->fs_info->avg_delayed_ref_runसमय;
	val = num_entries * avg_runसमय;
	अगर (val >= NSEC_PER_SEC)
		वापस 1;
	अगर (val >= NSEC_PER_SEC / 2)
		वापस 2;

	वापस btrfs_check_space_क्रम_delayed_refs(trans->fs_info);
पूर्ण

/**
 * Release a ref head's reservation
 *
 * @fs_info:  the fileप्रणाली
 * @nr:       number of items to drop
 *
 * This drops the delayed ref head's count from the delayed refs rsv and मुक्तs
 * any excess reservation we had.
 */
व्योम btrfs_delayed_refs_rsv_release(काष्ठा btrfs_fs_info *fs_info, पूर्णांक nr)
अणु
	काष्ठा btrfs_block_rsv *block_rsv = &fs_info->delayed_refs_rsv;
	u64 num_bytes = btrfs_calc_insert_metadata_size(fs_info, nr);
	u64 released = 0;

	released = btrfs_block_rsv_release(fs_info, block_rsv, num_bytes, शून्य);
	अगर (released)
		trace_btrfs_space_reservation(fs_info, "delayed_refs_rsv",
					      0, released, 0);
पूर्ण

/*
 * btrfs_update_delayed_refs_rsv - adjust the size of the delayed refs rsv
 * @trans - the trans that may have generated delayed refs
 *
 * This is to be called anyसमय we may have adjusted trans->delayed_ref_updates,
 * it'll calculate the additional size and add it to the delayed_refs_rsv.
 */
व्योम btrfs_update_delayed_refs_rsv(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_block_rsv *delayed_rsv = &fs_info->delayed_refs_rsv;
	u64 num_bytes;

	अगर (!trans->delayed_ref_updates)
		वापस;

	num_bytes = btrfs_calc_insert_metadata_size(fs_info,
						    trans->delayed_ref_updates);
	spin_lock(&delayed_rsv->lock);
	delayed_rsv->size += num_bytes;
	delayed_rsv->full = 0;
	spin_unlock(&delayed_rsv->lock);
	trans->delayed_ref_updates = 0;
पूर्ण

/**
 * Transfer bytes to our delayed refs rsv
 *
 * @fs_info:   the fileप्रणाली
 * @src:       source block rsv to transfer from
 * @num_bytes: number of bytes to transfer
 *
 * This transfers up to the num_bytes amount from the src rsv to the
 * delayed_refs_rsv.  Any extra bytes are वापसed to the space info.
 */
व्योम btrfs_migrate_to_delayed_refs_rsv(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा btrfs_block_rsv *src,
				       u64 num_bytes)
अणु
	काष्ठा btrfs_block_rsv *delayed_refs_rsv = &fs_info->delayed_refs_rsv;
	u64 to_मुक्त = 0;

	spin_lock(&src->lock);
	src->reserved -= num_bytes;
	src->size -= num_bytes;
	spin_unlock(&src->lock);

	spin_lock(&delayed_refs_rsv->lock);
	अगर (delayed_refs_rsv->size > delayed_refs_rsv->reserved) अणु
		u64 delta = delayed_refs_rsv->size -
			delayed_refs_rsv->reserved;
		अगर (num_bytes > delta) अणु
			to_मुक्त = num_bytes - delta;
			num_bytes = delta;
		पूर्ण
	पूर्ण अन्यथा अणु
		to_मुक्त = num_bytes;
		num_bytes = 0;
	पूर्ण

	अगर (num_bytes)
		delayed_refs_rsv->reserved += num_bytes;
	अगर (delayed_refs_rsv->reserved >= delayed_refs_rsv->size)
		delayed_refs_rsv->full = 1;
	spin_unlock(&delayed_refs_rsv->lock);

	अगर (num_bytes)
		trace_btrfs_space_reservation(fs_info, "delayed_refs_rsv",
					      0, num_bytes, 1);
	अगर (to_मुक्त)
		btrfs_space_info_मुक्त_bytes_may_use(fs_info,
				delayed_refs_rsv->space_info, to_मुक्त);
पूर्ण

/**
 * Refill based on our delayed refs usage
 *
 * @fs_info: the fileप्रणाली
 * @flush:   control how we can flush क्रम this reservation.
 *
 * This will refill the delayed block_rsv up to 1 items size worth of space and
 * will वापस -ENOSPC अगर we can't make the reservation.
 */
पूर्णांक btrfs_delayed_refs_rsv_refill(काष्ठा btrfs_fs_info *fs_info,
				  क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	काष्ठा btrfs_block_rsv *block_rsv = &fs_info->delayed_refs_rsv;
	u64 limit = btrfs_calc_insert_metadata_size(fs_info, 1);
	u64 num_bytes = 0;
	पूर्णांक ret = -ENOSPC;

	spin_lock(&block_rsv->lock);
	अगर (block_rsv->reserved < block_rsv->size) अणु
		num_bytes = block_rsv->size - block_rsv->reserved;
		num_bytes = min(num_bytes, limit);
	पूर्ण
	spin_unlock(&block_rsv->lock);

	अगर (!num_bytes)
		वापस 0;

	ret = btrfs_reserve_metadata_bytes(fs_info->extent_root, block_rsv,
					   num_bytes, flush);
	अगर (ret)
		वापस ret;
	btrfs_block_rsv_add_bytes(block_rsv, num_bytes, 0);
	trace_btrfs_space_reservation(fs_info, "delayed_refs_rsv",
				      0, num_bytes, 1);
	वापस 0;
पूर्ण

/*
 * compare two delayed tree backrefs with same bytenr and type
 */
अटल पूर्णांक comp_tree_refs(काष्ठा btrfs_delayed_tree_ref *ref1,
			  काष्ठा btrfs_delayed_tree_ref *ref2)
अणु
	अगर (ref1->node.type == BTRFS_TREE_BLOCK_REF_KEY) अणु
		अगर (ref1->root < ref2->root)
			वापस -1;
		अगर (ref1->root > ref2->root)
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (ref1->parent < ref2->parent)
			वापस -1;
		अगर (ref1->parent > ref2->parent)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * compare two delayed data backrefs with same bytenr and type
 */
अटल पूर्णांक comp_data_refs(काष्ठा btrfs_delayed_data_ref *ref1,
			  काष्ठा btrfs_delayed_data_ref *ref2)
अणु
	अगर (ref1->node.type == BTRFS_EXTENT_DATA_REF_KEY) अणु
		अगर (ref1->root < ref2->root)
			वापस -1;
		अगर (ref1->root > ref2->root)
			वापस 1;
		अगर (ref1->objectid < ref2->objectid)
			वापस -1;
		अगर (ref1->objectid > ref2->objectid)
			वापस 1;
		अगर (ref1->offset < ref2->offset)
			वापस -1;
		अगर (ref1->offset > ref2->offset)
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (ref1->parent < ref2->parent)
			वापस -1;
		अगर (ref1->parent > ref2->parent)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक comp_refs(काष्ठा btrfs_delayed_ref_node *ref1,
		     काष्ठा btrfs_delayed_ref_node *ref2,
		     bool check_seq)
अणु
	पूर्णांक ret = 0;

	अगर (ref1->type < ref2->type)
		वापस -1;
	अगर (ref1->type > ref2->type)
		वापस 1;
	अगर (ref1->type == BTRFS_TREE_BLOCK_REF_KEY ||
	    ref1->type == BTRFS_SHARED_BLOCK_REF_KEY)
		ret = comp_tree_refs(btrfs_delayed_node_to_tree_ref(ref1),
				     btrfs_delayed_node_to_tree_ref(ref2));
	अन्यथा
		ret = comp_data_refs(btrfs_delayed_node_to_data_ref(ref1),
				     btrfs_delayed_node_to_data_ref(ref2));
	अगर (ret)
		वापस ret;
	अगर (check_seq) अणु
		अगर (ref1->seq < ref2->seq)
			वापस -1;
		अगर (ref1->seq > ref2->seq)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* insert a new ref to head ref rbtree */
अटल काष्ठा btrfs_delayed_ref_head *htree_insert(काष्ठा rb_root_cached *root,
						   काष्ठा rb_node *node)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_node *parent_node = शून्य;
	काष्ठा btrfs_delayed_ref_head *entry;
	काष्ठा btrfs_delayed_ref_head *ins;
	u64 bytenr;
	bool lefपंचांगost = true;

	ins = rb_entry(node, काष्ठा btrfs_delayed_ref_head, href_node);
	bytenr = ins->bytenr;
	जबतक (*p) अणु
		parent_node = *p;
		entry = rb_entry(parent_node, काष्ठा btrfs_delayed_ref_head,
				 href_node);

		अगर (bytenr < entry->bytenr) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (bytenr > entry->bytenr) अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण अन्यथा अणु
			वापस entry;
		पूर्ण
	पूर्ण

	rb_link_node(node, parent_node, p);
	rb_insert_color_cached(node, root, lefपंचांगost);
	वापस शून्य;
पूर्ण

अटल काष्ठा btrfs_delayed_ref_node* tree_insert(काष्ठा rb_root_cached *root,
		काष्ठा btrfs_delayed_ref_node *ins)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_node *node = &ins->ref_node;
	काष्ठा rb_node *parent_node = शून्य;
	काष्ठा btrfs_delayed_ref_node *entry;
	bool lefपंचांगost = true;

	जबतक (*p) अणु
		पूर्णांक comp;

		parent_node = *p;
		entry = rb_entry(parent_node, काष्ठा btrfs_delayed_ref_node,
				 ref_node);
		comp = comp_refs(ins, entry, true);
		अगर (comp < 0) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (comp > 0) अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण अन्यथा अणु
			वापस entry;
		पूर्ण
	पूर्ण

	rb_link_node(node, parent_node, p);
	rb_insert_color_cached(node, root, lefपंचांगost);
	वापस शून्य;
पूर्ण

अटल काष्ठा btrfs_delayed_ref_head *find_first_ref_head(
		काष्ठा btrfs_delayed_ref_root *dr)
अणु
	काष्ठा rb_node *n;
	काष्ठा btrfs_delayed_ref_head *entry;

	n = rb_first_cached(&dr->href_root);
	अगर (!n)
		वापस शून्य;

	entry = rb_entry(n, काष्ठा btrfs_delayed_ref_head, href_node);

	वापस entry;
पूर्ण

/*
 * Find a head entry based on bytenr. This वापसs the delayed ref head अगर it
 * was able to find one, or शून्य अगर nothing was in that spot.  If वापस_bigger
 * is given, the next bigger entry is वापसed अगर no exact match is found.
 */
अटल काष्ठा btrfs_delayed_ref_head *find_ref_head(
		काष्ठा btrfs_delayed_ref_root *dr, u64 bytenr,
		bool वापस_bigger)
अणु
	काष्ठा rb_root *root = &dr->href_root.rb_root;
	काष्ठा rb_node *n;
	काष्ठा btrfs_delayed_ref_head *entry;

	n = root->rb_node;
	entry = शून्य;
	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा btrfs_delayed_ref_head, href_node);

		अगर (bytenr < entry->bytenr)
			n = n->rb_left;
		अन्यथा अगर (bytenr > entry->bytenr)
			n = n->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण
	अगर (entry && वापस_bigger) अणु
		अगर (bytenr > entry->bytenr) अणु
			n = rb_next(&entry->href_node);
			अगर (!n)
				वापस शून्य;
			entry = rb_entry(n, काष्ठा btrfs_delayed_ref_head,
					 href_node);
		पूर्ण
		वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक btrfs_delayed_ref_lock(काष्ठा btrfs_delayed_ref_root *delayed_refs,
			   काष्ठा btrfs_delayed_ref_head *head)
अणु
	lockdep_निश्चित_held(&delayed_refs->lock);
	अगर (mutex_trylock(&head->mutex))
		वापस 0;

	refcount_inc(&head->refs);
	spin_unlock(&delayed_refs->lock);

	mutex_lock(&head->mutex);
	spin_lock(&delayed_refs->lock);
	अगर (RB_EMPTY_NODE(&head->href_node)) अणु
		mutex_unlock(&head->mutex);
		btrfs_put_delayed_ref_head(head);
		वापस -EAGAIN;
	पूर्ण
	btrfs_put_delayed_ref_head(head);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम drop_delayed_ref(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_delayed_ref_root *delayed_refs,
				    काष्ठा btrfs_delayed_ref_head *head,
				    काष्ठा btrfs_delayed_ref_node *ref)
अणु
	lockdep_निश्चित_held(&head->lock);
	rb_erase_cached(&ref->ref_node, &head->ref_tree);
	RB_CLEAR_NODE(&ref->ref_node);
	अगर (!list_empty(&ref->add_list))
		list_del(&ref->add_list);
	ref->in_tree = 0;
	btrfs_put_delayed_ref(ref);
	atomic_dec(&delayed_refs->num_entries);
पूर्ण

अटल bool merge_ref(काष्ठा btrfs_trans_handle *trans,
		      काष्ठा btrfs_delayed_ref_root *delayed_refs,
		      काष्ठा btrfs_delayed_ref_head *head,
		      काष्ठा btrfs_delayed_ref_node *ref,
		      u64 seq)
अणु
	काष्ठा btrfs_delayed_ref_node *next;
	काष्ठा rb_node *node = rb_next(&ref->ref_node);
	bool करोne = false;

	जबतक (!करोne && node) अणु
		पूर्णांक mod;

		next = rb_entry(node, काष्ठा btrfs_delayed_ref_node, ref_node);
		node = rb_next(node);
		अगर (seq && next->seq >= seq)
			अवरोध;
		अगर (comp_refs(ref, next, false))
			अवरोध;

		अगर (ref->action == next->action) अणु
			mod = next->ref_mod;
		पूर्ण अन्यथा अणु
			अगर (ref->ref_mod < next->ref_mod) अणु
				swap(ref, next);
				करोne = true;
			पूर्ण
			mod = -next->ref_mod;
		पूर्ण

		drop_delayed_ref(trans, delayed_refs, head, next);
		ref->ref_mod += mod;
		अगर (ref->ref_mod == 0) अणु
			drop_delayed_ref(trans, delayed_refs, head, ref);
			करोne = true;
		पूर्ण अन्यथा अणु
			/*
			 * Can't have multiples of the same ref on a tree block.
			 */
			WARN_ON(ref->type == BTRFS_TREE_BLOCK_REF_KEY ||
				ref->type == BTRFS_SHARED_BLOCK_REF_KEY);
		पूर्ण
	पूर्ण

	वापस करोne;
पूर्ण

व्योम btrfs_merge_delayed_refs(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_delayed_ref_root *delayed_refs,
			      काष्ठा btrfs_delayed_ref_head *head)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_delayed_ref_node *ref;
	काष्ठा rb_node *node;
	u64 seq = 0;

	lockdep_निश्चित_held(&head->lock);

	अगर (RB_EMPTY_ROOT(&head->ref_tree.rb_root))
		वापस;

	/* We करोn't have too many refs to merge क्रम data. */
	अगर (head->is_data)
		वापस;

	seq = btrfs_tree_mod_log_lowest_seq(fs_info);
again:
	क्रम (node = rb_first_cached(&head->ref_tree); node;
	     node = rb_next(node)) अणु
		ref = rb_entry(node, काष्ठा btrfs_delayed_ref_node, ref_node);
		अगर (seq && ref->seq >= seq)
			जारी;
		अगर (merge_ref(trans, delayed_refs, head, ref, seq))
			जाओ again;
	पूर्ण
पूर्ण

पूर्णांक btrfs_check_delayed_seq(काष्ठा btrfs_fs_info *fs_info, u64 seq)
अणु
	पूर्णांक ret = 0;
	u64 min_seq = btrfs_tree_mod_log_lowest_seq(fs_info);

	अगर (min_seq != 0 && seq >= min_seq) अणु
		btrfs_debug(fs_info,
			    "holding back delayed_ref %llu, lowest is %llu",
			    seq, min_seq);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा btrfs_delayed_ref_head *btrfs_select_ref_head(
		काष्ठा btrfs_delayed_ref_root *delayed_refs)
अणु
	काष्ठा btrfs_delayed_ref_head *head;

again:
	head = find_ref_head(delayed_refs, delayed_refs->run_delayed_start,
			     true);
	अगर (!head && delayed_refs->run_delayed_start != 0) अणु
		delayed_refs->run_delayed_start = 0;
		head = find_first_ref_head(delayed_refs);
	पूर्ण
	अगर (!head)
		वापस शून्य;

	जबतक (head->processing) अणु
		काष्ठा rb_node *node;

		node = rb_next(&head->href_node);
		अगर (!node) अणु
			अगर (delayed_refs->run_delayed_start == 0)
				वापस शून्य;
			delayed_refs->run_delayed_start = 0;
			जाओ again;
		पूर्ण
		head = rb_entry(node, काष्ठा btrfs_delayed_ref_head,
				href_node);
	पूर्ण

	head->processing = 1;
	WARN_ON(delayed_refs->num_heads_पढ़ोy == 0);
	delayed_refs->num_heads_पढ़ोy--;
	delayed_refs->run_delayed_start = head->bytenr +
		head->num_bytes;
	वापस head;
पूर्ण

व्योम btrfs_delete_ref_head(काष्ठा btrfs_delayed_ref_root *delayed_refs,
			   काष्ठा btrfs_delayed_ref_head *head)
अणु
	lockdep_निश्चित_held(&delayed_refs->lock);
	lockdep_निश्चित_held(&head->lock);

	rb_erase_cached(&head->href_node, &delayed_refs->href_root);
	RB_CLEAR_NODE(&head->href_node);
	atomic_dec(&delayed_refs->num_entries);
	delayed_refs->num_heads--;
	अगर (head->processing == 0)
		delayed_refs->num_heads_पढ़ोy--;
पूर्ण

/*
 * Helper to insert the ref_node to the tail or merge with tail.
 *
 * Return 0 क्रम insert.
 * Return >0 क्रम merge.
 */
अटल पूर्णांक insert_delayed_ref(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_delayed_ref_root *root,
			      काष्ठा btrfs_delayed_ref_head *href,
			      काष्ठा btrfs_delayed_ref_node *ref)
अणु
	काष्ठा btrfs_delayed_ref_node *exist;
	पूर्णांक mod;
	पूर्णांक ret = 0;

	spin_lock(&href->lock);
	exist = tree_insert(&href->ref_tree, ref);
	अगर (!exist)
		जाओ inserted;

	/* Now we are sure we can merge */
	ret = 1;
	अगर (exist->action == ref->action) अणु
		mod = ref->ref_mod;
	पूर्ण अन्यथा अणु
		/* Need to change action */
		अगर (exist->ref_mod < ref->ref_mod) अणु
			exist->action = ref->action;
			mod = -exist->ref_mod;
			exist->ref_mod = ref->ref_mod;
			अगर (ref->action == BTRFS_ADD_DELAYED_REF)
				list_add_tail(&exist->add_list,
					      &href->ref_add_list);
			अन्यथा अगर (ref->action == BTRFS_DROP_DELAYED_REF) अणु
				ASSERT(!list_empty(&exist->add_list));
				list_del(&exist->add_list);
			पूर्ण अन्यथा अणु
				ASSERT(0);
			पूर्ण
		पूर्ण अन्यथा
			mod = -ref->ref_mod;
	पूर्ण
	exist->ref_mod += mod;

	/* हटाओ existing tail अगर its ref_mod is zero */
	अगर (exist->ref_mod == 0)
		drop_delayed_ref(trans, root, href, exist);
	spin_unlock(&href->lock);
	वापस ret;
inserted:
	अगर (ref->action == BTRFS_ADD_DELAYED_REF)
		list_add_tail(&ref->add_list, &href->ref_add_list);
	atomic_inc(&root->num_entries);
	spin_unlock(&href->lock);
	वापस ret;
पूर्ण

/*
 * helper function to update the accounting in the head ref
 * existing and update must have the same bytenr
 */
अटल noअंतरभूत व्योम update_existing_head_ref(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा btrfs_delayed_ref_head *existing,
			 काष्ठा btrfs_delayed_ref_head *update)
अणु
	काष्ठा btrfs_delayed_ref_root *delayed_refs =
		&trans->transaction->delayed_refs;
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	u64 flags = btrfs_ref_head_to_space_flags(existing);
	पूर्णांक old_ref_mod;

	BUG_ON(existing->is_data != update->is_data);

	spin_lock(&existing->lock);
	अगर (update->must_insert_reserved) अणु
		/* अगर the extent was मुक्तd and then
		 * पुनः_स्मृतिated beक्रमe the delayed ref
		 * entries were processed, we can end up
		 * with an existing head ref without
		 * the must_insert_reserved flag set.
		 * Set it again here
		 */
		existing->must_insert_reserved = update->must_insert_reserved;

		/*
		 * update the num_bytes so we make sure the accounting
		 * is करोne correctly
		 */
		existing->num_bytes = update->num_bytes;

	पूर्ण

	अगर (update->extent_op) अणु
		अगर (!existing->extent_op) अणु
			existing->extent_op = update->extent_op;
		पूर्ण अन्यथा अणु
			अगर (update->extent_op->update_key) अणु
				स_नकल(&existing->extent_op->key,
				       &update->extent_op->key,
				       माप(update->extent_op->key));
				existing->extent_op->update_key = true;
			पूर्ण
			अगर (update->extent_op->update_flags) अणु
				existing->extent_op->flags_to_set |=
					update->extent_op->flags_to_set;
				existing->extent_op->update_flags = true;
			पूर्ण
			btrfs_मुक्त_delayed_extent_op(update->extent_op);
		पूर्ण
	पूर्ण
	/*
	 * update the reference mod on the head to reflect this new operation,
	 * only need the lock क्रम this हाल cause we could be processing it
	 * currently, क्रम refs we just added we know we're a-ok.
	 */
	old_ref_mod = existing->total_ref_mod;
	existing->ref_mod += update->ref_mod;
	existing->total_ref_mod += update->ref_mod;

	/*
	 * If we are going to from a positive ref mod to a negative or vice
	 * versa we need to make sure to adjust pending_csums accordingly.
	 */
	अगर (existing->is_data) अणु
		u64 csum_leaves =
			btrfs_csum_bytes_to_leaves(fs_info,
						   existing->num_bytes);

		अगर (existing->total_ref_mod >= 0 && old_ref_mod < 0) अणु
			delayed_refs->pending_csums -= existing->num_bytes;
			btrfs_delayed_refs_rsv_release(fs_info, csum_leaves);
		पूर्ण
		अगर (existing->total_ref_mod < 0 && old_ref_mod >= 0) अणु
			delayed_refs->pending_csums += existing->num_bytes;
			trans->delayed_ref_updates += csum_leaves;
		पूर्ण
	पूर्ण

	/*
	 * This handles the following conditions:
	 *
	 * 1. We had a ref mod of 0 or more and went negative, indicating that
	 *    we may be मुक्तing space, so add our space to the
	 *    total_bytes_pinned counter.
	 * 2. We were negative and went to 0 or positive, so no दीर्घer can say
	 *    that the space would be pinned, decrement our counter from the
	 *    total_bytes_pinned counter.
	 * 3. We are now at 0 and have ->must_insert_reserved set, which means
	 *    this was a new allocation and then we dropped it, and thus must
	 *    add our space to the total_bytes_pinned counter.
	 */
	अगर (existing->total_ref_mod < 0 && old_ref_mod >= 0)
		btrfs_mod_total_bytes_pinned(fs_info, flags, existing->num_bytes);
	अन्यथा अगर (existing->total_ref_mod >= 0 && old_ref_mod < 0)
		btrfs_mod_total_bytes_pinned(fs_info, flags, -existing->num_bytes);
	अन्यथा अगर (existing->total_ref_mod == 0 && existing->must_insert_reserved)
		btrfs_mod_total_bytes_pinned(fs_info, flags, existing->num_bytes);

	spin_unlock(&existing->lock);
पूर्ण

अटल व्योम init_delayed_ref_head(काष्ठा btrfs_delayed_ref_head *head_ref,
				  काष्ठा btrfs_qgroup_extent_record *qrecord,
				  u64 bytenr, u64 num_bytes, u64 ref_root,
				  u64 reserved, पूर्णांक action, bool is_data,
				  bool is_प्रणाली)
अणु
	पूर्णांक count_mod = 1;
	पूर्णांक must_insert_reserved = 0;

	/* If reserved is provided, it must be a data extent. */
	BUG_ON(!is_data && reserved);

	/*
	 * The head node stores the sum of all the mods, so dropping a ref
	 * should drop the sum in the head node by one.
	 */
	अगर (action == BTRFS_UPDATE_DELAYED_HEAD)
		count_mod = 0;
	अन्यथा अगर (action == BTRFS_DROP_DELAYED_REF)
		count_mod = -1;

	/*
	 * BTRFS_ADD_DELAYED_EXTENT means that we need to update the reserved
	 * accounting when the extent is finally added, or अगर a later
	 * modअगरication deletes the delayed ref without ever inserting the
	 * extent पूर्णांकo the extent allocation tree.  ref->must_insert_reserved
	 * is the flag used to record that accounting mods are required.
	 *
	 * Once we record must_insert_reserved, चयन the action to
	 * BTRFS_ADD_DELAYED_REF because other special casing is not required.
	 */
	अगर (action == BTRFS_ADD_DELAYED_EXTENT)
		must_insert_reserved = 1;
	अन्यथा
		must_insert_reserved = 0;

	refcount_set(&head_ref->refs, 1);
	head_ref->bytenr = bytenr;
	head_ref->num_bytes = num_bytes;
	head_ref->ref_mod = count_mod;
	head_ref->must_insert_reserved = must_insert_reserved;
	head_ref->is_data = is_data;
	head_ref->is_प्रणाली = is_प्रणाली;
	head_ref->ref_tree = RB_ROOT_CACHED;
	INIT_LIST_HEAD(&head_ref->ref_add_list);
	RB_CLEAR_NODE(&head_ref->href_node);
	head_ref->processing = 0;
	head_ref->total_ref_mod = count_mod;
	spin_lock_init(&head_ref->lock);
	mutex_init(&head_ref->mutex);

	अगर (qrecord) अणु
		अगर (ref_root && reserved) अणु
			qrecord->data_rsv = reserved;
			qrecord->data_rsv_refroot = ref_root;
		पूर्ण
		qrecord->bytenr = bytenr;
		qrecord->num_bytes = num_bytes;
		qrecord->old_roots = शून्य;
	पूर्ण
पूर्ण

/*
 * helper function to actually insert a head node पूर्णांकo the rbtree.
 * this करोes all the dirty work in terms of मुख्यtaining the correct
 * overall modअगरication count.
 */
अटल noअंतरभूत काष्ठा btrfs_delayed_ref_head *
add_delayed_ref_head(काष्ठा btrfs_trans_handle *trans,
		     काष्ठा btrfs_delayed_ref_head *head_ref,
		     काष्ठा btrfs_qgroup_extent_record *qrecord,
		     पूर्णांक action, पूर्णांक *qrecord_inserted_ret)
अणु
	काष्ठा btrfs_delayed_ref_head *existing;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	पूर्णांक qrecord_inserted = 0;

	delayed_refs = &trans->transaction->delayed_refs;

	/* Record qgroup extent info अगर provided */
	अगर (qrecord) अणु
		अगर (btrfs_qgroup_trace_extent_nolock(trans->fs_info,
					delayed_refs, qrecord))
			kमुक्त(qrecord);
		अन्यथा
			qrecord_inserted = 1;
	पूर्ण

	trace_add_delayed_ref_head(trans->fs_info, head_ref, action);

	existing = htree_insert(&delayed_refs->href_root,
				&head_ref->href_node);
	अगर (existing) अणु
		update_existing_head_ref(trans, existing, head_ref);
		/*
		 * we've updated the existing ref, मुक्त the newly
		 * allocated ref
		 */
		kmem_cache_मुक्त(btrfs_delayed_ref_head_cachep, head_ref);
		head_ref = existing;
	पूर्ण अन्यथा अणु
		u64 flags = btrfs_ref_head_to_space_flags(head_ref);

		अगर (head_ref->is_data && head_ref->ref_mod < 0) अणु
			delayed_refs->pending_csums += head_ref->num_bytes;
			trans->delayed_ref_updates +=
				btrfs_csum_bytes_to_leaves(trans->fs_info,
							   head_ref->num_bytes);
		पूर्ण
		अगर (head_ref->ref_mod < 0)
			btrfs_mod_total_bytes_pinned(trans->fs_info, flags,
						     head_ref->num_bytes);
		delayed_refs->num_heads++;
		delayed_refs->num_heads_पढ़ोy++;
		atomic_inc(&delayed_refs->num_entries);
		trans->delayed_ref_updates++;
	पूर्ण
	अगर (qrecord_inserted_ret)
		*qrecord_inserted_ret = qrecord_inserted;

	वापस head_ref;
पूर्ण

/*
 * init_delayed_ref_common - Initialize the काष्ठाure which represents a
 *			     modअगरication to a an extent.
 *
 * @fs_info:    Internal to the mounted fileप्रणाली mount काष्ठाure.
 *
 * @ref:	The काष्ठाure which is going to be initialized.
 *
 * @bytenr:	The logical address of the extent क्रम which a modअगरication is
 *		going to be recorded.
 *
 * @num_bytes:  Size of the extent whose modअगरication is being recorded.
 *
 * @ref_root:	The id of the root where this modअगरication has originated, this
 *		can be either one of the well-known metadata trees or the
 *		subvolume id which references this extent.
 *
 * @action:	Can be one of BTRFS_ADD_DELAYED_REF/BTRFS_DROP_DELAYED_REF or
 *		BTRFS_ADD_DELAYED_EXTENT
 *
 * @ref_type:	Holds the type of the extent which is being recorded, can be
 *		one of BTRFS_SHARED_BLOCK_REF_KEY/BTRFS_TREE_BLOCK_REF_KEY
 *		when recording a metadata extent or BTRFS_SHARED_DATA_REF_KEY/
 *		BTRFS_EXTENT_DATA_REF_KEY when recording data extent
 */
अटल व्योम init_delayed_ref_common(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_delayed_ref_node *ref,
				    u64 bytenr, u64 num_bytes, u64 ref_root,
				    पूर्णांक action, u8 ref_type)
अणु
	u64 seq = 0;

	अगर (action == BTRFS_ADD_DELAYED_EXTENT)
		action = BTRFS_ADD_DELAYED_REF;

	अगर (is_fstree(ref_root))
		seq = atomic64_पढ़ो(&fs_info->tree_mod_seq);

	refcount_set(&ref->refs, 1);
	ref->bytenr = bytenr;
	ref->num_bytes = num_bytes;
	ref->ref_mod = 1;
	ref->action = action;
	ref->is_head = 0;
	ref->in_tree = 1;
	ref->seq = seq;
	ref->type = ref_type;
	RB_CLEAR_NODE(&ref->ref_node);
	INIT_LIST_HEAD(&ref->add_list);
पूर्ण

/*
 * add a delayed tree ref.  This करोes all of the accounting required
 * to make sure the delayed ref is eventually processed beक्रमe this
 * transaction commits.
 */
पूर्णांक btrfs_add_delayed_tree_ref(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_ref *generic_ref,
			       काष्ठा btrfs_delayed_extent_op *extent_op)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_delayed_tree_ref *ref;
	काष्ठा btrfs_delayed_ref_head *head_ref;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा btrfs_qgroup_extent_record *record = शून्य;
	पूर्णांक qrecord_inserted;
	bool is_प्रणाली;
	पूर्णांक action = generic_ref->action;
	पूर्णांक level = generic_ref->tree_ref.level;
	पूर्णांक ret;
	u64 bytenr = generic_ref->bytenr;
	u64 num_bytes = generic_ref->len;
	u64 parent = generic_ref->parent;
	u8 ref_type;

	is_प्रणाली = (generic_ref->real_root == BTRFS_CHUNK_TREE_OBJECTID);

	ASSERT(generic_ref->type == BTRFS_REF_METADATA && generic_ref->action);
	BUG_ON(extent_op && extent_op->is_data);
	ref = kmem_cache_alloc(btrfs_delayed_tree_ref_cachep, GFP_NOFS);
	अगर (!ref)
		वापस -ENOMEM;

	head_ref = kmem_cache_alloc(btrfs_delayed_ref_head_cachep, GFP_NOFS);
	अगर (!head_ref) अणु
		kmem_cache_मुक्त(btrfs_delayed_tree_ref_cachep, ref);
		वापस -ENOMEM;
	पूर्ण

	अगर (test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) &&
	    is_fstree(generic_ref->real_root) &&
	    is_fstree(generic_ref->tree_ref.root) &&
	    !generic_ref->skip_qgroup) अणु
		record = kzalloc(माप(*record), GFP_NOFS);
		अगर (!record) अणु
			kmem_cache_मुक्त(btrfs_delayed_tree_ref_cachep, ref);
			kmem_cache_मुक्त(btrfs_delayed_ref_head_cachep, head_ref);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (parent)
		ref_type = BTRFS_SHARED_BLOCK_REF_KEY;
	अन्यथा
		ref_type = BTRFS_TREE_BLOCK_REF_KEY;

	init_delayed_ref_common(fs_info, &ref->node, bytenr, num_bytes,
				generic_ref->tree_ref.root, action, ref_type);
	ref->root = generic_ref->tree_ref.root;
	ref->parent = parent;
	ref->level = level;

	init_delayed_ref_head(head_ref, record, bytenr, num_bytes,
			      generic_ref->tree_ref.root, 0, action, false,
			      is_प्रणाली);
	head_ref->extent_op = extent_op;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);

	/*
	 * insert both the head node and the new ref without dropping
	 * the spin lock
	 */
	head_ref = add_delayed_ref_head(trans, head_ref, record,
					action, &qrecord_inserted);

	ret = insert_delayed_ref(trans, delayed_refs, head_ref, &ref->node);
	spin_unlock(&delayed_refs->lock);

	/*
	 * Need to update the delayed_refs_rsv with any changes we may have
	 * made.
	 */
	btrfs_update_delayed_refs_rsv(trans);

	trace_add_delayed_tree_ref(fs_info, &ref->node, ref,
				   action == BTRFS_ADD_DELAYED_EXTENT ?
				   BTRFS_ADD_DELAYED_REF : action);
	अगर (ret > 0)
		kmem_cache_मुक्त(btrfs_delayed_tree_ref_cachep, ref);

	अगर (qrecord_inserted)
		btrfs_qgroup_trace_extent_post(fs_info, record);

	वापस 0;
पूर्ण

/*
 * add a delayed data ref. it's similar to btrfs_add_delayed_tree_ref.
 */
पूर्णांक btrfs_add_delayed_data_ref(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_ref *generic_ref,
			       u64 reserved)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_delayed_data_ref *ref;
	काष्ठा btrfs_delayed_ref_head *head_ref;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;
	काष्ठा btrfs_qgroup_extent_record *record = शून्य;
	पूर्णांक qrecord_inserted;
	पूर्णांक action = generic_ref->action;
	पूर्णांक ret;
	u64 bytenr = generic_ref->bytenr;
	u64 num_bytes = generic_ref->len;
	u64 parent = generic_ref->parent;
	u64 ref_root = generic_ref->data_ref.ref_root;
	u64 owner = generic_ref->data_ref.ino;
	u64 offset = generic_ref->data_ref.offset;
	u8 ref_type;

	ASSERT(generic_ref->type == BTRFS_REF_DATA && action);
	ref = kmem_cache_alloc(btrfs_delayed_data_ref_cachep, GFP_NOFS);
	अगर (!ref)
		वापस -ENOMEM;

	अगर (parent)
	        ref_type = BTRFS_SHARED_DATA_REF_KEY;
	अन्यथा
	        ref_type = BTRFS_EXTENT_DATA_REF_KEY;
	init_delayed_ref_common(fs_info, &ref->node, bytenr, num_bytes,
				ref_root, action, ref_type);
	ref->root = ref_root;
	ref->parent = parent;
	ref->objectid = owner;
	ref->offset = offset;


	head_ref = kmem_cache_alloc(btrfs_delayed_ref_head_cachep, GFP_NOFS);
	अगर (!head_ref) अणु
		kmem_cache_मुक्त(btrfs_delayed_data_ref_cachep, ref);
		वापस -ENOMEM;
	पूर्ण

	अगर (test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) &&
	    is_fstree(ref_root) &&
	    is_fstree(generic_ref->real_root) &&
	    !generic_ref->skip_qgroup) अणु
		record = kzalloc(माप(*record), GFP_NOFS);
		अगर (!record) अणु
			kmem_cache_मुक्त(btrfs_delayed_data_ref_cachep, ref);
			kmem_cache_मुक्त(btrfs_delayed_ref_head_cachep,
					head_ref);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	init_delayed_ref_head(head_ref, record, bytenr, num_bytes, ref_root,
			      reserved, action, true, false);
	head_ref->extent_op = शून्य;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);

	/*
	 * insert both the head node and the new ref without dropping
	 * the spin lock
	 */
	head_ref = add_delayed_ref_head(trans, head_ref, record,
					action, &qrecord_inserted);

	ret = insert_delayed_ref(trans, delayed_refs, head_ref, &ref->node);
	spin_unlock(&delayed_refs->lock);

	/*
	 * Need to update the delayed_refs_rsv with any changes we may have
	 * made.
	 */
	btrfs_update_delayed_refs_rsv(trans);

	trace_add_delayed_data_ref(trans->fs_info, &ref->node, ref,
				   action == BTRFS_ADD_DELAYED_EXTENT ?
				   BTRFS_ADD_DELAYED_REF : action);
	अगर (ret > 0)
		kmem_cache_मुक्त(btrfs_delayed_data_ref_cachep, ref);


	अगर (qrecord_inserted)
		वापस btrfs_qgroup_trace_extent_post(fs_info, record);
	वापस 0;
पूर्ण

पूर्णांक btrfs_add_delayed_extent_op(काष्ठा btrfs_trans_handle *trans,
				u64 bytenr, u64 num_bytes,
				काष्ठा btrfs_delayed_extent_op *extent_op)
अणु
	काष्ठा btrfs_delayed_ref_head *head_ref;
	काष्ठा btrfs_delayed_ref_root *delayed_refs;

	head_ref = kmem_cache_alloc(btrfs_delayed_ref_head_cachep, GFP_NOFS);
	अगर (!head_ref)
		वापस -ENOMEM;

	init_delayed_ref_head(head_ref, शून्य, bytenr, num_bytes, 0, 0,
			      BTRFS_UPDATE_DELAYED_HEAD, extent_op->is_data,
			      false);
	head_ref->extent_op = extent_op;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);

	add_delayed_ref_head(trans, head_ref, शून्य, BTRFS_UPDATE_DELAYED_HEAD,
			     शून्य);

	spin_unlock(&delayed_refs->lock);

	/*
	 * Need to update the delayed_refs_rsv with any changes we may have
	 * made.
	 */
	btrfs_update_delayed_refs_rsv(trans);
	वापस 0;
पूर्ण

/*
 * This करोes a simple search क्रम the head node क्रम a given extent.  Returns the
 * head node अगर found, or शून्य अगर not.
 */
काष्ठा btrfs_delayed_ref_head *
btrfs_find_delayed_ref_head(काष्ठा btrfs_delayed_ref_root *delayed_refs, u64 bytenr)
अणु
	lockdep_निश्चित_held(&delayed_refs->lock);

	वापस find_ref_head(delayed_refs, bytenr, false);
पूर्ण

व्योम __cold btrfs_delayed_ref_निकास(व्योम)
अणु
	kmem_cache_destroy(btrfs_delayed_ref_head_cachep);
	kmem_cache_destroy(btrfs_delayed_tree_ref_cachep);
	kmem_cache_destroy(btrfs_delayed_data_ref_cachep);
	kmem_cache_destroy(btrfs_delayed_extent_op_cachep);
पूर्ण

पूर्णांक __init btrfs_delayed_ref_init(व्योम)
अणु
	btrfs_delayed_ref_head_cachep = kmem_cache_create(
				"btrfs_delayed_ref_head",
				माप(काष्ठा btrfs_delayed_ref_head), 0,
				SLAB_MEM_SPREAD, शून्य);
	अगर (!btrfs_delayed_ref_head_cachep)
		जाओ fail;

	btrfs_delayed_tree_ref_cachep = kmem_cache_create(
				"btrfs_delayed_tree_ref",
				माप(काष्ठा btrfs_delayed_tree_ref), 0,
				SLAB_MEM_SPREAD, शून्य);
	अगर (!btrfs_delayed_tree_ref_cachep)
		जाओ fail;

	btrfs_delayed_data_ref_cachep = kmem_cache_create(
				"btrfs_delayed_data_ref",
				माप(काष्ठा btrfs_delayed_data_ref), 0,
				SLAB_MEM_SPREAD, शून्य);
	अगर (!btrfs_delayed_data_ref_cachep)
		जाओ fail;

	btrfs_delayed_extent_op_cachep = kmem_cache_create(
				"btrfs_delayed_extent_op",
				माप(काष्ठा btrfs_delayed_extent_op), 0,
				SLAB_MEM_SPREAD, शून्य);
	अगर (!btrfs_delayed_extent_op_cachep)
		जाओ fail;

	वापस 0;
fail:
	btrfs_delayed_ref_निकास();
	वापस -ENOMEM;
पूर्ण
