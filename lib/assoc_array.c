<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Generic associative array implementation.
 *
 * See Documentation/core-api/assoc_array.rst क्रम inक्रमmation.
 *
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
//#घोषणा DEBUG
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/assoc_array_priv.h>

/*
 * Iterate over an associative array.  The caller must hold the RCU पढ़ो lock
 * or better.
 */
अटल पूर्णांक assoc_array_subtree_iterate(स्थिर काष्ठा assoc_array_ptr *root,
				       स्थिर काष्ठा assoc_array_ptr *stop,
				       पूर्णांक (*iterator)(स्थिर व्योम *leaf,
						       व्योम *iterator_data),
				       व्योम *iterator_data)
अणु
	स्थिर काष्ठा assoc_array_लघुcut *लघुcut;
	स्थिर काष्ठा assoc_array_node *node;
	स्थिर काष्ठा assoc_array_ptr *cursor, *ptr, *parent;
	अचिन्हित दीर्घ has_meta;
	पूर्णांक slot, ret;

	cursor = root;

begin_node:
	अगर (assoc_array_ptr_is_लघुcut(cursor)) अणु
		/* Descend through a लघुcut */
		लघुcut = assoc_array_ptr_to_लघुcut(cursor);
		cursor = READ_ONCE(लघुcut->next_node); /* Address dependency. */
	पूर्ण

	node = assoc_array_ptr_to_node(cursor);
	slot = 0;

	/* We perक्रमm two passes of each node.
	 *
	 * The first pass करोes all the leaves in this node.  This means we
	 * करोn't miss any leaves अगर the node is split up by insertion whilst
	 * we're iterating over the branches rooted here (we may, however, see
	 * some leaves twice).
	 */
	has_meta = 0;
	क्रम (; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
		ptr = READ_ONCE(node->slots[slot]); /* Address dependency. */
		has_meta |= (अचिन्हित दीर्घ)ptr;
		अगर (ptr && assoc_array_ptr_is_leaf(ptr)) अणु
			/* We need a barrier between the पढ़ो of the poपूर्णांकer,
			 * which is supplied by the above READ_ONCE().
			 */
			/* Invoke the callback */
			ret = iterator(assoc_array_ptr_to_leaf(ptr),
				       iterator_data);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* The second pass attends to all the metadata poपूर्णांकers.  If we follow
	 * one of these we may find that we करोn't come back here, but rather go
	 * back to a replacement node with the leaves in a dअगरferent layout.
	 *
	 * We are guaranteed to make progress, however, as the slot number क्रम
	 * a particular portion of the key space cannot change - and we
	 * जारी at the back poपूर्णांकer + 1.
	 */
	अगर (!(has_meta & ASSOC_ARRAY_PTR_META_TYPE))
		जाओ finished_node;
	slot = 0;

जारी_node:
	node = assoc_array_ptr_to_node(cursor);
	क्रम (; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
		ptr = READ_ONCE(node->slots[slot]); /* Address dependency. */
		अगर (assoc_array_ptr_is_meta(ptr)) अणु
			cursor = ptr;
			जाओ begin_node;
		पूर्ण
	पूर्ण

finished_node:
	/* Move up to the parent (may need to skip back over a लघुcut) */
	parent = READ_ONCE(node->back_poपूर्णांकer); /* Address dependency. */
	slot = node->parent_slot;
	अगर (parent == stop)
		वापस 0;

	अगर (assoc_array_ptr_is_लघुcut(parent)) अणु
		लघुcut = assoc_array_ptr_to_लघुcut(parent);
		cursor = parent;
		parent = READ_ONCE(लघुcut->back_poपूर्णांकer); /* Address dependency. */
		slot = लघुcut->parent_slot;
		अगर (parent == stop)
			वापस 0;
	पूर्ण

	/* Ascend to next slot in parent node */
	cursor = parent;
	slot++;
	जाओ जारी_node;
पूर्ण

/**
 * assoc_array_iterate - Pass all objects in the array to a callback
 * @array: The array to iterate over.
 * @iterator: The callback function.
 * @iterator_data: Private data क्रम the callback function.
 *
 * Iterate over all the objects in an associative array.  Each one will be
 * presented to the iterator function.
 *
 * If the array is being modअगरied concurrently with the iteration then it is
 * possible that some objects in the array will be passed to the iterator
 * callback more than once - though every object should be passed at least
 * once.  If this is undesirable then the caller must lock against modअगरication
 * क्रम the duration of this function.
 *
 * The function will वापस 0 अगर no objects were in the array or अन्यथा it will
 * वापस the result of the last iterator function called.  Iteration stops
 * immediately अगर any call to the iteration function results in a non-zero
 * वापस.
 *
 * The caller should hold the RCU पढ़ो lock or better अगर concurrent
 * modअगरication is possible.
 */
पूर्णांक assoc_array_iterate(स्थिर काष्ठा assoc_array *array,
			पूर्णांक (*iterator)(स्थिर व्योम *object,
					व्योम *iterator_data),
			व्योम *iterator_data)
अणु
	काष्ठा assoc_array_ptr *root = READ_ONCE(array->root); /* Address dependency. */

	अगर (!root)
		वापस 0;
	वापस assoc_array_subtree_iterate(root, शून्य, iterator, iterator_data);
पूर्ण

क्रमागत assoc_array_walk_status अणु
	assoc_array_walk_tree_empty,
	assoc_array_walk_found_terminal_node,
	assoc_array_walk_found_wrong_लघुcut,
पूर्ण;

काष्ठा assoc_array_walk_result अणु
	काष्ठा अणु
		काष्ठा assoc_array_node	*node;	/* Node in which leaf might be found */
		पूर्णांक		level;
		पूर्णांक		slot;
	पूर्ण terminal_node;
	काष्ठा अणु
		काष्ठा assoc_array_लघुcut *लघुcut;
		पूर्णांक		level;
		पूर्णांक		sc_level;
		अचिन्हित दीर्घ	sc_segments;
		अचिन्हित दीर्घ	dissimilarity;
	पूर्ण wrong_लघुcut;
पूर्ण;

/*
 * Navigate through the पूर्णांकernal tree looking क्रम the बंदst node to the key.
 */
अटल क्रमागत assoc_array_walk_status
assoc_array_walk(स्थिर काष्ठा assoc_array *array,
		 स्थिर काष्ठा assoc_array_ops *ops,
		 स्थिर व्योम *index_key,
		 काष्ठा assoc_array_walk_result *result)
अणु
	काष्ठा assoc_array_लघुcut *लघुcut;
	काष्ठा assoc_array_node *node;
	काष्ठा assoc_array_ptr *cursor, *ptr;
	अचिन्हित दीर्घ sc_segments, dissimilarity;
	अचिन्हित दीर्घ segments;
	पूर्णांक level, sc_level, next_sc_level;
	पूर्णांक slot;

	pr_devel("-->%s()\n", __func__);

	cursor = READ_ONCE(array->root);  /* Address dependency. */
	अगर (!cursor)
		वापस assoc_array_walk_tree_empty;

	level = 0;

	/* Use segments from the key क्रम the new leaf to navigate through the
	 * पूर्णांकernal tree, skipping through nodes and लघुcuts that are on
	 * route to the destination.  Eventually we'll come to a slot that is
	 * either empty or contains a leaf at which poपूर्णांक we've found a node in
	 * which the leaf we're looking क्रम might be found or पूर्णांकo which it
	 * should be inserted.
	 */
jumped:
	segments = ops->get_key_chunk(index_key, level);
	pr_devel("segments[%d]: %lx\n", level, segments);

	अगर (assoc_array_ptr_is_लघुcut(cursor))
		जाओ follow_लघुcut;

consider_node:
	node = assoc_array_ptr_to_node(cursor);
	slot = segments >> (level & ASSOC_ARRAY_KEY_CHUNK_MASK);
	slot &= ASSOC_ARRAY_FAN_MASK;
	ptr = READ_ONCE(node->slots[slot]); /* Address dependency. */

	pr_devel("consider slot %x [ix=%d type=%lu]\n",
		 slot, level, (अचिन्हित दीर्घ)ptr & 3);

	अगर (!assoc_array_ptr_is_meta(ptr)) अणु
		/* The node करोesn't have a node/लघुcut poपूर्णांकer in the slot
		 * corresponding to the index key that we have to follow.
		 */
		result->terminal_node.node = node;
		result->terminal_node.level = level;
		result->terminal_node.slot = slot;
		pr_devel("<--%s() = terminal_node\n", __func__);
		वापस assoc_array_walk_found_terminal_node;
	पूर्ण

	अगर (assoc_array_ptr_is_node(ptr)) अणु
		/* There is a poपूर्णांकer to a node in the slot corresponding to
		 * this index key segment, so we need to follow it.
		 */
		cursor = ptr;
		level += ASSOC_ARRAY_LEVEL_STEP;
		अगर ((level & ASSOC_ARRAY_KEY_CHUNK_MASK) != 0)
			जाओ consider_node;
		जाओ jumped;
	पूर्ण

	/* There is a लघुcut in the slot corresponding to the index key
	 * segment.  We follow the लघुcut अगर its partial index key matches
	 * this leaf's.  Otherwise we need to split the लघुcut.
	 */
	cursor = ptr;
follow_लघुcut:
	लघुcut = assoc_array_ptr_to_लघुcut(cursor);
	pr_devel("shortcut to %d\n", लघुcut->skip_to_level);
	sc_level = level + ASSOC_ARRAY_LEVEL_STEP;
	BUG_ON(sc_level > लघुcut->skip_to_level);

	करो अणु
		/* Check the leaf against the लघुcut's index key a word at a
		 * समय, trimming the final word (the लघुcut stores the index
		 * key completely from the root to the लघुcut's target).
		 */
		अगर ((sc_level & ASSOC_ARRAY_KEY_CHUNK_MASK) == 0)
			segments = ops->get_key_chunk(index_key, sc_level);

		sc_segments = लघुcut->index_key[sc_level >> ASSOC_ARRAY_KEY_CHUNK_SHIFT];
		dissimilarity = segments ^ sc_segments;

		अगर (round_up(sc_level, ASSOC_ARRAY_KEY_CHUNK_SIZE) > लघुcut->skip_to_level) अणु
			/* Trim segments that are beyond the लघुcut */
			पूर्णांक shअगरt = लघुcut->skip_to_level & ASSOC_ARRAY_KEY_CHUNK_MASK;
			dissimilarity &= ~(अच_दीर्घ_उच्च << shअगरt);
			next_sc_level = लघुcut->skip_to_level;
		पूर्ण अन्यथा अणु
			next_sc_level = sc_level + ASSOC_ARRAY_KEY_CHUNK_SIZE;
			next_sc_level = round_करोwn(next_sc_level, ASSOC_ARRAY_KEY_CHUNK_SIZE);
		पूर्ण

		अगर (dissimilarity != 0) अणु
			/* This लघुcut poपूर्णांकs अन्यथाwhere */
			result->wrong_लघुcut.लघुcut = लघुcut;
			result->wrong_लघुcut.level = level;
			result->wrong_लघुcut.sc_level = sc_level;
			result->wrong_लघुcut.sc_segments = sc_segments;
			result->wrong_लघुcut.dissimilarity = dissimilarity;
			वापस assoc_array_walk_found_wrong_लघुcut;
		पूर्ण

		sc_level = next_sc_level;
	पूर्ण जबतक (sc_level < लघुcut->skip_to_level);

	/* The लघुcut matches the leaf's index to this poपूर्णांक. */
	cursor = READ_ONCE(लघुcut->next_node); /* Address dependency. */
	अगर (((level ^ sc_level) & ~ASSOC_ARRAY_KEY_CHUNK_MASK) != 0) अणु
		level = sc_level;
		जाओ jumped;
	पूर्ण अन्यथा अणु
		level = sc_level;
		जाओ consider_node;
	पूर्ण
पूर्ण

/**
 * assoc_array_find - Find an object by index key
 * @array: The associative array to search.
 * @ops: The operations to use.
 * @index_key: The key to the object.
 *
 * Find an object in an associative array by walking through the पूर्णांकernal tree
 * to the node that should contain the object and then searching the leaves
 * there.  शून्य is वापसed अगर the requested object was not found in the array.
 *
 * The caller must hold the RCU पढ़ो lock or better.
 */
व्योम *assoc_array_find(स्थिर काष्ठा assoc_array *array,
		       स्थिर काष्ठा assoc_array_ops *ops,
		       स्थिर व्योम *index_key)
अणु
	काष्ठा assoc_array_walk_result result;
	स्थिर काष्ठा assoc_array_node *node;
	स्थिर काष्ठा assoc_array_ptr *ptr;
	स्थिर व्योम *leaf;
	पूर्णांक slot;

	अगर (assoc_array_walk(array, ops, index_key, &result) !=
	    assoc_array_walk_found_terminal_node)
		वापस शून्य;

	node = result.terminal_node.node;

	/* If the target key is available to us, it's has to be poपूर्णांकed to by
	 * the terminal node.
	 */
	क्रम (slot = 0; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
		ptr = READ_ONCE(node->slots[slot]); /* Address dependency. */
		अगर (ptr && assoc_array_ptr_is_leaf(ptr)) अणु
			/* We need a barrier between the पढ़ो of the poपूर्णांकer
			 * and dereferencing the poपूर्णांकer - but only अगर we are
			 * actually going to dereference it.
			 */
			leaf = assoc_array_ptr_to_leaf(ptr);
			अगर (ops->compare_object(leaf, index_key))
				वापस (व्योम *)leaf;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Deकाष्ठाively iterate over an associative array.  The caller must prevent
 * other simultaneous accesses.
 */
अटल व्योम assoc_array_destroy_subtree(काष्ठा assoc_array_ptr *root,
					स्थिर काष्ठा assoc_array_ops *ops)
अणु
	काष्ठा assoc_array_लघुcut *लघुcut;
	काष्ठा assoc_array_node *node;
	काष्ठा assoc_array_ptr *cursor, *parent = शून्य;
	पूर्णांक slot = -1;

	pr_devel("-->%s()\n", __func__);

	cursor = root;
	अगर (!cursor) अणु
		pr_devel("empty\n");
		वापस;
	पूर्ण

move_to_meta:
	अगर (assoc_array_ptr_is_लघुcut(cursor)) अणु
		/* Descend through a लघुcut */
		pr_devel("[%d] shortcut\n", slot);
		BUG_ON(!assoc_array_ptr_is_लघुcut(cursor));
		लघुcut = assoc_array_ptr_to_लघुcut(cursor);
		BUG_ON(लघुcut->back_poपूर्णांकer != parent);
		BUG_ON(slot != -1 && लघुcut->parent_slot != slot);
		parent = cursor;
		cursor = लघुcut->next_node;
		slot = -1;
		BUG_ON(!assoc_array_ptr_is_node(cursor));
	पूर्ण

	pr_devel("[%d] node\n", slot);
	node = assoc_array_ptr_to_node(cursor);
	BUG_ON(node->back_poपूर्णांकer != parent);
	BUG_ON(slot != -1 && node->parent_slot != slot);
	slot = 0;

जारी_node:
	pr_devel("Node %p [back=%p]\n", node, node->back_poपूर्णांकer);
	क्रम (; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
		काष्ठा assoc_array_ptr *ptr = node->slots[slot];
		अगर (!ptr)
			जारी;
		अगर (assoc_array_ptr_is_meta(ptr)) अणु
			parent = cursor;
			cursor = ptr;
			जाओ move_to_meta;
		पूर्ण

		अगर (ops) अणु
			pr_devel("[%d] free leaf\n", slot);
			ops->मुक्त_object(assoc_array_ptr_to_leaf(ptr));
		पूर्ण
	पूर्ण

	parent = node->back_poपूर्णांकer;
	slot = node->parent_slot;
	pr_devel("free node\n");
	kमुक्त(node);
	अगर (!parent)
		वापस; /* Done */

	/* Move back up to the parent (may need to मुक्त a लघुcut on
	 * the way up) */
	अगर (assoc_array_ptr_is_लघुcut(parent)) अणु
		लघुcut = assoc_array_ptr_to_लघुcut(parent);
		BUG_ON(लघुcut->next_node != cursor);
		cursor = parent;
		parent = लघुcut->back_poपूर्णांकer;
		slot = लघुcut->parent_slot;
		pr_devel("free shortcut\n");
		kमुक्त(लघुcut);
		अगर (!parent)
			वापस;

		BUG_ON(!assoc_array_ptr_is_node(parent));
	पूर्ण

	/* Ascend to next slot in parent node */
	pr_devel("ascend to %p[%d]\n", parent, slot);
	cursor = parent;
	node = assoc_array_ptr_to_node(cursor);
	slot++;
	जाओ जारी_node;
पूर्ण

/**
 * assoc_array_destroy - Destroy an associative array
 * @array: The array to destroy.
 * @ops: The operations to use.
 *
 * Discard all metadata and मुक्त all objects in an associative array.  The
 * array will be empty and पढ़ोy to use again upon completion.  This function
 * cannot fail.
 *
 * The caller must prevent all other accesses whilst this takes place as no
 * attempt is made to adjust poपूर्णांकers gracefully to permit RCU पढ़ोlock-holding
 * accesses to जारी.  On the other hand, no memory allocation is required.
 */
व्योम assoc_array_destroy(काष्ठा assoc_array *array,
			 स्थिर काष्ठा assoc_array_ops *ops)
अणु
	assoc_array_destroy_subtree(array->root, ops);
	array->root = शून्य;
पूर्ण

/*
 * Handle insertion पूर्णांकo an empty tree.
 */
अटल bool assoc_array_insert_in_empty_tree(काष्ठा assoc_array_edit *edit)
अणु
	काष्ठा assoc_array_node *new_n0;

	pr_devel("-->%s()\n", __func__);

	new_n0 = kzalloc(माप(काष्ठा assoc_array_node), GFP_KERNEL);
	अगर (!new_n0)
		वापस false;

	edit->new_meta[0] = assoc_array_node_to_ptr(new_n0);
	edit->leaf_p = &new_n0->slots[0];
	edit->adjust_count_on = new_n0;
	edit->set[0].ptr = &edit->array->root;
	edit->set[0].to = assoc_array_node_to_ptr(new_n0);

	pr_devel("<--%s() = ok [no root]\n", __func__);
	वापस true;
पूर्ण

/*
 * Handle insertion पूर्णांकo a terminal node.
 */
अटल bool assoc_array_insert_पूर्णांकo_terminal_node(काष्ठा assoc_array_edit *edit,
						  स्थिर काष्ठा assoc_array_ops *ops,
						  स्थिर व्योम *index_key,
						  काष्ठा assoc_array_walk_result *result)
अणु
	काष्ठा assoc_array_लघुcut *लघुcut, *new_s0;
	काष्ठा assoc_array_node *node, *new_n0, *new_n1, *side;
	काष्ठा assoc_array_ptr *ptr;
	अचिन्हित दीर्घ dissimilarity, base_seg, blank;
	माप_प्रकार keylen;
	bool have_meta;
	पूर्णांक level, dअगरf;
	पूर्णांक slot, next_slot, मुक्त_slot, i, j;

	node	= result->terminal_node.node;
	level	= result->terminal_node.level;
	edit->segment_cache[ASSOC_ARRAY_FAN_OUT] = result->terminal_node.slot;

	pr_devel("-->%s()\n", __func__);

	/* We arrived at a node which करोesn't have an onward node or लघुcut
	 * poपूर्णांकer that we have to follow.  This means that (a) the leaf we
	 * want must go here (either by insertion or replacement) or (b) we
	 * need to split this node and insert in one of the fragments.
	 */
	मुक्त_slot = -1;

	/* Firstly, we have to check the leaves in this node to see अगर there's
	 * a matching one we should replace in place.
	 */
	क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
		ptr = node->slots[i];
		अगर (!ptr) अणु
			मुक्त_slot = i;
			जारी;
		पूर्ण
		अगर (assoc_array_ptr_is_leaf(ptr) &&
		    ops->compare_object(assoc_array_ptr_to_leaf(ptr),
					index_key)) अणु
			pr_devel("replace in slot %d\n", i);
			edit->leaf_p = &node->slots[i];
			edit->dead_leaf = node->slots[i];
			pr_devel("<--%s() = ok [replace]\n", __func__);
			वापस true;
		पूर्ण
	पूर्ण

	/* If there is a मुक्त slot in this node then we can just insert the
	 * leaf here.
	 */
	अगर (मुक्त_slot >= 0) अणु
		pr_devel("insert in free slot %d\n", मुक्त_slot);
		edit->leaf_p = &node->slots[मुक्त_slot];
		edit->adjust_count_on = node;
		pr_devel("<--%s() = ok [insert]\n", __func__);
		वापस true;
	पूर्ण

	/* The node has no spare slots - so we're either going to have to split
	 * it or insert another node beक्रमe it.
	 *
	 * Whatever, we're going to need at least two new nodes - so allocate
	 * those now.  We may also need a new लघुcut, but we deal with that
	 * when we need it.
	 */
	new_n0 = kzalloc(माप(काष्ठा assoc_array_node), GFP_KERNEL);
	अगर (!new_n0)
		वापस false;
	edit->new_meta[0] = assoc_array_node_to_ptr(new_n0);
	new_n1 = kzalloc(माप(काष्ठा assoc_array_node), GFP_KERNEL);
	अगर (!new_n1)
		वापस false;
	edit->new_meta[1] = assoc_array_node_to_ptr(new_n1);

	/* We need to find out how similar the leaves are. */
	pr_devel("no spare slots\n");
	have_meta = false;
	क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
		ptr = node->slots[i];
		अगर (assoc_array_ptr_is_meta(ptr)) अणु
			edit->segment_cache[i] = 0xff;
			have_meta = true;
			जारी;
		पूर्ण
		base_seg = ops->get_object_key_chunk(
			assoc_array_ptr_to_leaf(ptr), level);
		base_seg >>= level & ASSOC_ARRAY_KEY_CHUNK_MASK;
		edit->segment_cache[i] = base_seg & ASSOC_ARRAY_FAN_MASK;
	पूर्ण

	अगर (have_meta) अणु
		pr_devel("have meta\n");
		जाओ split_node;
	पूर्ण

	/* The node contains only leaves */
	dissimilarity = 0;
	base_seg = edit->segment_cache[0];
	क्रम (i = 1; i < ASSOC_ARRAY_FAN_OUT; i++)
		dissimilarity |= edit->segment_cache[i] ^ base_seg;

	pr_devel("only leaves; dissimilarity=%lx\n", dissimilarity);

	अगर ((dissimilarity & ASSOC_ARRAY_FAN_MASK) == 0) अणु
		/* The old leaves all cluster in the same slot.  We will need
		 * to insert a लघुcut अगर the new node wants to cluster with them.
		 */
		अगर ((edit->segment_cache[ASSOC_ARRAY_FAN_OUT] ^ base_seg) == 0)
			जाओ all_leaves_cluster_together;

		/* Otherwise all the old leaves cluster in the same slot, but
		 * the new leaf wants to go पूर्णांकo a dअगरferent slot - so we
		 * create a new node (n0) to hold the new leaf and a poपूर्णांकer to
		 * a new node (n1) holding all the old leaves.
		 *
		 * This can be करोne by falling through to the node splitting
		 * path.
		 */
		pr_devel("present leaves cluster but not new leaf\n");
	पूर्ण

split_node:
	pr_devel("split node\n");

	/* We need to split the current node.  The node must contain anything
	 * from a single leaf (in the one leaf हाल, this leaf will cluster
	 * with the new leaf) and the rest meta-poपूर्णांकers, to all leaves, some
	 * of which may cluster.
	 *
	 * It won't contain the हाल in which all the current leaves plus the
	 * new leaves want to cluster in the same slot.
	 *
	 * We need to expel at least two leaves out of a set consisting of the
	 * leaves in the node and the new leaf.  The current meta poपूर्णांकers can
	 * just be copied as they shouldn't cluster with any of the leaves.
	 *
	 * We need a new node (n0) to replace the current one and a new node to
	 * take the expelled nodes (n1).
	 */
	edit->set[0].to = assoc_array_node_to_ptr(new_n0);
	new_n0->back_poपूर्णांकer = node->back_poपूर्णांकer;
	new_n0->parent_slot = node->parent_slot;
	new_n1->back_poपूर्णांकer = assoc_array_node_to_ptr(new_n0);
	new_n1->parent_slot = -1; /* Need to calculate this */

करो_split_node:
	pr_devel("do_split_node\n");

	new_n0->nr_leaves_on_branch = node->nr_leaves_on_branch;
	new_n1->nr_leaves_on_branch = 0;

	/* Begin by finding two matching leaves.  There have to be at least two
	 * that match - even अगर there are meta poपूर्णांकers - because any leaf that
	 * would match a slot with a meta poपूर्णांकer in it must be somewhere
	 * behind that meta poपूर्णांकer and cannot be here.  Further, given N
	 * reमुख्यing leaf slots, we now have N+1 leaves to go in them.
	 */
	क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
		slot = edit->segment_cache[i];
		अगर (slot != 0xff)
			क्रम (j = i + 1; j < ASSOC_ARRAY_FAN_OUT + 1; j++)
				अगर (edit->segment_cache[j] == slot)
					जाओ found_slot_क्रम_multiple_occupancy;
	पूर्ण
found_slot_क्रम_multiple_occupancy:
	pr_devel("same slot: %x %x [%02x]\n", i, j, slot);
	BUG_ON(i >= ASSOC_ARRAY_FAN_OUT);
	BUG_ON(j >= ASSOC_ARRAY_FAN_OUT + 1);
	BUG_ON(slot >= ASSOC_ARRAY_FAN_OUT);

	new_n1->parent_slot = slot;

	/* Metadata poपूर्णांकers cannot change slot */
	क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++)
		अगर (assoc_array_ptr_is_meta(node->slots[i]))
			new_n0->slots[i] = node->slots[i];
		अन्यथा
			new_n0->slots[i] = शून्य;
	BUG_ON(new_n0->slots[slot] != शून्य);
	new_n0->slots[slot] = assoc_array_node_to_ptr(new_n1);

	/* Filter the leaf poपूर्णांकers between the new nodes */
	मुक्त_slot = -1;
	next_slot = 0;
	क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
		अगर (assoc_array_ptr_is_meta(node->slots[i]))
			जारी;
		अगर (edit->segment_cache[i] == slot) अणु
			new_n1->slots[next_slot++] = node->slots[i];
			new_n1->nr_leaves_on_branch++;
		पूर्ण अन्यथा अणु
			करो अणु
				मुक्त_slot++;
			पूर्ण जबतक (new_n0->slots[मुक्त_slot] != शून्य);
			new_n0->slots[मुक्त_slot] = node->slots[i];
		पूर्ण
	पूर्ण

	pr_devel("filtered: f=%x n=%x\n", मुक्त_slot, next_slot);

	अगर (edit->segment_cache[ASSOC_ARRAY_FAN_OUT] != slot) अणु
		करो अणु
			मुक्त_slot++;
		पूर्ण जबतक (new_n0->slots[मुक्त_slot] != शून्य);
		edit->leaf_p = &new_n0->slots[मुक्त_slot];
		edit->adjust_count_on = new_n0;
	पूर्ण अन्यथा अणु
		edit->leaf_p = &new_n1->slots[next_slot++];
		edit->adjust_count_on = new_n1;
	पूर्ण

	BUG_ON(next_slot <= 1);

	edit->set_backpoपूर्णांकers_to = assoc_array_node_to_ptr(new_n0);
	क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
		अगर (edit->segment_cache[i] == 0xff) अणु
			ptr = node->slots[i];
			BUG_ON(assoc_array_ptr_is_leaf(ptr));
			अगर (assoc_array_ptr_is_node(ptr)) अणु
				side = assoc_array_ptr_to_node(ptr);
				edit->set_backpoपूर्णांकers[i] = &side->back_poपूर्णांकer;
			पूर्ण अन्यथा अणु
				लघुcut = assoc_array_ptr_to_लघुcut(ptr);
				edit->set_backpoपूर्णांकers[i] = &लघुcut->back_poपूर्णांकer;
			पूर्ण
		पूर्ण
	पूर्ण

	ptr = node->back_poपूर्णांकer;
	अगर (!ptr)
		edit->set[0].ptr = &edit->array->root;
	अन्यथा अगर (assoc_array_ptr_is_node(ptr))
		edit->set[0].ptr = &assoc_array_ptr_to_node(ptr)->slots[node->parent_slot];
	अन्यथा
		edit->set[0].ptr = &assoc_array_ptr_to_लघुcut(ptr)->next_node;
	edit->excised_meta[0] = assoc_array_node_to_ptr(node);
	pr_devel("<--%s() = ok [split node]\n", __func__);
	वापस true;

all_leaves_cluster_together:
	/* All the leaves, new and old, want to cluster together in this node
	 * in the same slot, so we have to replace this node with a लघुcut to
	 * skip over the identical parts of the key and then place a pair of
	 * nodes, one inside the other, at the end of the लघुcut and
	 * distribute the keys between them.
	 *
	 * Firstly we need to work out where the leaves start भागerging as a
	 * bit position पूर्णांकo their keys so that we know how big the लघुcut
	 * needs to be.
	 *
	 * We only need to make a single pass of N of the N+1 leaves because अगर
	 * any keys dअगरfer between themselves at bit X then at least one of
	 * them must also dअगरfer with the base key at bit X or beक्रमe.
	 */
	pr_devel("all leaves cluster together\n");
	dअगरf = पूर्णांक_उच्च;
	क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
		पूर्णांक x = ops->dअगरf_objects(assoc_array_ptr_to_leaf(node->slots[i]),
					  index_key);
		अगर (x < dअगरf) अणु
			BUG_ON(x < 0);
			dअगरf = x;
		पूर्ण
	पूर्ण
	BUG_ON(dअगरf == पूर्णांक_उच्च);
	BUG_ON(dअगरf < level + ASSOC_ARRAY_LEVEL_STEP);

	keylen = round_up(dअगरf, ASSOC_ARRAY_KEY_CHUNK_SIZE);
	keylen >>= ASSOC_ARRAY_KEY_CHUNK_SHIFT;

	new_s0 = kzalloc(माप(काष्ठा assoc_array_लघुcut) +
			 keylen * माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!new_s0)
		वापस false;
	edit->new_meta[2] = assoc_array_लघुcut_to_ptr(new_s0);

	edit->set[0].to = assoc_array_लघुcut_to_ptr(new_s0);
	new_s0->back_poपूर्णांकer = node->back_poपूर्णांकer;
	new_s0->parent_slot = node->parent_slot;
	new_s0->next_node = assoc_array_node_to_ptr(new_n0);
	new_n0->back_poपूर्णांकer = assoc_array_लघुcut_to_ptr(new_s0);
	new_n0->parent_slot = 0;
	new_n1->back_poपूर्णांकer = assoc_array_node_to_ptr(new_n0);
	new_n1->parent_slot = -1; /* Need to calculate this */

	new_s0->skip_to_level = level = dअगरf & ~ASSOC_ARRAY_LEVEL_STEP_MASK;
	pr_devel("skip_to_level = %d [diff %d]\n", level, dअगरf);
	BUG_ON(level <= 0);

	क्रम (i = 0; i < keylen; i++)
		new_s0->index_key[i] =
			ops->get_key_chunk(index_key, i * ASSOC_ARRAY_KEY_CHUNK_SIZE);

	अगर (level & ASSOC_ARRAY_KEY_CHUNK_MASK) अणु
		blank = अच_दीर्घ_उच्च << (level & ASSOC_ARRAY_KEY_CHUNK_MASK);
		pr_devel("blank off [%zu] %d: %lx\n", keylen - 1, level, blank);
		new_s0->index_key[keylen - 1] &= ~blank;
	पूर्ण

	/* This now reduces to a node splitting exercise क्रम which we'll need
	 * to regenerate the disparity table.
	 */
	क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
		ptr = node->slots[i];
		base_seg = ops->get_object_key_chunk(assoc_array_ptr_to_leaf(ptr),
						     level);
		base_seg >>= level & ASSOC_ARRAY_KEY_CHUNK_MASK;
		edit->segment_cache[i] = base_seg & ASSOC_ARRAY_FAN_MASK;
	पूर्ण

	base_seg = ops->get_key_chunk(index_key, level);
	base_seg >>= level & ASSOC_ARRAY_KEY_CHUNK_MASK;
	edit->segment_cache[ASSOC_ARRAY_FAN_OUT] = base_seg & ASSOC_ARRAY_FAN_MASK;
	जाओ करो_split_node;
पूर्ण

/*
 * Handle insertion पूर्णांकo the middle of a लघुcut.
 */
अटल bool assoc_array_insert_mid_लघुcut(काष्ठा assoc_array_edit *edit,
					    स्थिर काष्ठा assoc_array_ops *ops,
					    काष्ठा assoc_array_walk_result *result)
अणु
	काष्ठा assoc_array_लघुcut *लघुcut, *new_s0, *new_s1;
	काष्ठा assoc_array_node *node, *new_n0, *side;
	अचिन्हित दीर्घ sc_segments, dissimilarity, blank;
	माप_प्रकार keylen;
	पूर्णांक level, sc_level, dअगरf;
	पूर्णांक sc_slot;

	लघुcut	= result->wrong_लघुcut.लघुcut;
	level		= result->wrong_लघुcut.level;
	sc_level	= result->wrong_लघुcut.sc_level;
	sc_segments	= result->wrong_लघुcut.sc_segments;
	dissimilarity	= result->wrong_लघुcut.dissimilarity;

	pr_devel("-->%s(ix=%d dis=%lx scix=%d)\n",
		 __func__, level, dissimilarity, sc_level);

	/* We need to split a लघुcut and insert a node between the two
	 * pieces.  Zero-length pieces will be dispensed with entirely.
	 *
	 * First of all, we need to find out in which level the first
	 * dअगरference was.
	 */
	dअगरf = __ffs(dissimilarity);
	dअगरf &= ~ASSOC_ARRAY_LEVEL_STEP_MASK;
	dअगरf += sc_level & ~ASSOC_ARRAY_KEY_CHUNK_MASK;
	pr_devel("diff=%d\n", dअगरf);

	अगर (!लघुcut->back_poपूर्णांकer) अणु
		edit->set[0].ptr = &edit->array->root;
	पूर्ण अन्यथा अगर (assoc_array_ptr_is_node(लघुcut->back_poपूर्णांकer)) अणु
		node = assoc_array_ptr_to_node(लघुcut->back_poपूर्णांकer);
		edit->set[0].ptr = &node->slots[लघुcut->parent_slot];
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	edit->excised_meta[0] = assoc_array_लघुcut_to_ptr(लघुcut);

	/* Create a new node now since we're going to need it anyway */
	new_n0 = kzalloc(माप(काष्ठा assoc_array_node), GFP_KERNEL);
	अगर (!new_n0)
		वापस false;
	edit->new_meta[0] = assoc_array_node_to_ptr(new_n0);
	edit->adjust_count_on = new_n0;

	/* Insert a new लघुcut beक्रमe the new node अगर this segment isn't of
	 * zero length - otherwise we just connect the new node directly to the
	 * parent.
	 */
	level += ASSOC_ARRAY_LEVEL_STEP;
	अगर (dअगरf > level) अणु
		pr_devel("pre-shortcut %d...%d\n", level, dअगरf);
		keylen = round_up(dअगरf, ASSOC_ARRAY_KEY_CHUNK_SIZE);
		keylen >>= ASSOC_ARRAY_KEY_CHUNK_SHIFT;

		new_s0 = kzalloc(माप(काष्ठा assoc_array_लघुcut) +
				 keylen * माप(अचिन्हित दीर्घ), GFP_KERNEL);
		अगर (!new_s0)
			वापस false;
		edit->new_meta[1] = assoc_array_लघुcut_to_ptr(new_s0);
		edit->set[0].to = assoc_array_लघुcut_to_ptr(new_s0);
		new_s0->back_poपूर्णांकer = लघुcut->back_poपूर्णांकer;
		new_s0->parent_slot = लघुcut->parent_slot;
		new_s0->next_node = assoc_array_node_to_ptr(new_n0);
		new_s0->skip_to_level = dअगरf;

		new_n0->back_poपूर्णांकer = assoc_array_लघुcut_to_ptr(new_s0);
		new_n0->parent_slot = 0;

		स_नकल(new_s0->index_key, लघुcut->index_key,
		       keylen * माप(अचिन्हित दीर्घ));

		blank = अच_दीर्घ_उच्च << (dअगरf & ASSOC_ARRAY_KEY_CHUNK_MASK);
		pr_devel("blank off [%zu] %d: %lx\n", keylen - 1, dअगरf, blank);
		new_s0->index_key[keylen - 1] &= ~blank;
	पूर्ण अन्यथा अणु
		pr_devel("no pre-shortcut\n");
		edit->set[0].to = assoc_array_node_to_ptr(new_n0);
		new_n0->back_poपूर्णांकer = लघुcut->back_poपूर्णांकer;
		new_n0->parent_slot = लघुcut->parent_slot;
	पूर्ण

	side = assoc_array_ptr_to_node(लघुcut->next_node);
	new_n0->nr_leaves_on_branch = side->nr_leaves_on_branch;

	/* We need to know which slot in the new node is going to take a
	 * metadata poपूर्णांकer.
	 */
	sc_slot = sc_segments >> (dअगरf & ASSOC_ARRAY_KEY_CHUNK_MASK);
	sc_slot &= ASSOC_ARRAY_FAN_MASK;

	pr_devel("new slot %lx >> %d -> %d\n",
		 sc_segments, dअगरf & ASSOC_ARRAY_KEY_CHUNK_MASK, sc_slot);

	/* Determine whether we need to follow the new node with a replacement
	 * क्रम the current लघुcut.  We could in theory reuse the current
	 * लघुcut अगर its parent slot number करोesn't change - but that's a
	 * 1-in-16 chance so not worth expending the code upon.
	 */
	level = dअगरf + ASSOC_ARRAY_LEVEL_STEP;
	अगर (level < लघुcut->skip_to_level) अणु
		pr_devel("post-shortcut %d...%d\n", level, लघुcut->skip_to_level);
		keylen = round_up(लघुcut->skip_to_level, ASSOC_ARRAY_KEY_CHUNK_SIZE);
		keylen >>= ASSOC_ARRAY_KEY_CHUNK_SHIFT;

		new_s1 = kzalloc(माप(काष्ठा assoc_array_लघुcut) +
				 keylen * माप(अचिन्हित दीर्घ), GFP_KERNEL);
		अगर (!new_s1)
			वापस false;
		edit->new_meta[2] = assoc_array_लघुcut_to_ptr(new_s1);

		new_s1->back_poपूर्णांकer = assoc_array_node_to_ptr(new_n0);
		new_s1->parent_slot = sc_slot;
		new_s1->next_node = लघुcut->next_node;
		new_s1->skip_to_level = लघुcut->skip_to_level;

		new_n0->slots[sc_slot] = assoc_array_लघुcut_to_ptr(new_s1);

		स_नकल(new_s1->index_key, लघुcut->index_key,
		       keylen * माप(अचिन्हित दीर्घ));

		edit->set[1].ptr = &side->back_poपूर्णांकer;
		edit->set[1].to = assoc_array_लघुcut_to_ptr(new_s1);
	पूर्ण अन्यथा अणु
		pr_devel("no post-shortcut\n");

		/* We करोn't have to replace the poपूर्णांकed-to node as दीर्घ as we
		 * use memory barriers to make sure the parent slot number is
		 * changed beक्रमe the back poपूर्णांकer (the parent slot number is
		 * irrelevant to the old parent लघुcut).
		 */
		new_n0->slots[sc_slot] = लघुcut->next_node;
		edit->set_parent_slot[0].p = &side->parent_slot;
		edit->set_parent_slot[0].to = sc_slot;
		edit->set[1].ptr = &side->back_poपूर्णांकer;
		edit->set[1].to = assoc_array_node_to_ptr(new_n0);
	पूर्ण

	/* Install the new leaf in a spare slot in the new node. */
	अगर (sc_slot == 0)
		edit->leaf_p = &new_n0->slots[1];
	अन्यथा
		edit->leaf_p = &new_n0->slots[0];

	pr_devel("<--%s() = ok [split shortcut]\n", __func__);
	वापस edit;
पूर्ण

/**
 * assoc_array_insert - Script insertion of an object पूर्णांकo an associative array
 * @array: The array to insert पूर्णांकo.
 * @ops: The operations to use.
 * @index_key: The key to insert at.
 * @object: The object to insert.
 *
 * Precalculate and pपुनः_स्मृतिate a script क्रम the insertion or replacement of an
 * object in an associative array.  This results in an edit script that can
 * either be applied or cancelled.
 *
 * The function वापसs a poपूर्णांकer to an edit script or -ENOMEM.
 *
 * The caller should lock against other modअगरications and must जारी to hold
 * the lock until assoc_array_apply_edit() has been called.
 *
 * Accesses to the tree may take place concurrently with this function,
 * provided they hold the RCU पढ़ो lock.
 */
काष्ठा assoc_array_edit *assoc_array_insert(काष्ठा assoc_array *array,
					    स्थिर काष्ठा assoc_array_ops *ops,
					    स्थिर व्योम *index_key,
					    व्योम *object)
अणु
	काष्ठा assoc_array_walk_result result;
	काष्ठा assoc_array_edit *edit;

	pr_devel("-->%s()\n", __func__);

	/* The leaf poपूर्णांकer we're given must not have the bottom bit set as we
	 * use those क्रम type-marking the poपूर्णांकer.  शून्य poपूर्णांकers are also not
	 * allowed as they indicate an empty slot but we have to allow them
	 * here as they can be updated later.
	 */
	BUG_ON(assoc_array_ptr_is_meta(object));

	edit = kzalloc(माप(काष्ठा assoc_array_edit), GFP_KERNEL);
	अगर (!edit)
		वापस ERR_PTR(-ENOMEM);
	edit->array = array;
	edit->ops = ops;
	edit->leaf = assoc_array_leaf_to_ptr(object);
	edit->adjust_count_by = 1;

	चयन (assoc_array_walk(array, ops, index_key, &result)) अणु
	हाल assoc_array_walk_tree_empty:
		/* Allocate a root node अगर there isn't one yet */
		अगर (!assoc_array_insert_in_empty_tree(edit))
			जाओ enomem;
		वापस edit;

	हाल assoc_array_walk_found_terminal_node:
		/* We found a node that करोesn't have a node/लघुcut poपूर्णांकer in
		 * the slot corresponding to the index key that we have to
		 * follow.
		 */
		अगर (!assoc_array_insert_पूर्णांकo_terminal_node(edit, ops, index_key,
							   &result))
			जाओ enomem;
		वापस edit;

	हाल assoc_array_walk_found_wrong_लघुcut:
		/* We found a लघुcut that didn't match our key in a slot we
		 * needed to follow.
		 */
		अगर (!assoc_array_insert_mid_लघुcut(edit, ops, &result))
			जाओ enomem;
		वापस edit;
	पूर्ण

enomem:
	/* Clean up after an out of memory error */
	pr_devel("enomem\n");
	assoc_array_cancel_edit(edit);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * assoc_array_insert_set_object - Set the new object poपूर्णांकer in an edit script
 * @edit: The edit script to modअगरy.
 * @object: The object poपूर्णांकer to set.
 *
 * Change the object to be inserted in an edit script.  The object poपूर्णांकed to
 * by the old object is not मुक्तd.  This must be करोne prior to applying the
 * script.
 */
व्योम assoc_array_insert_set_object(काष्ठा assoc_array_edit *edit, व्योम *object)
अणु
	BUG_ON(!object);
	edit->leaf = assoc_array_leaf_to_ptr(object);
पूर्ण

काष्ठा assoc_array_delete_collapse_context अणु
	काष्ठा assoc_array_node	*node;
	स्थिर व्योम		*skip_leaf;
	पूर्णांक			slot;
पूर्ण;

/*
 * Subtree collapse to node iterator.
 */
अटल पूर्णांक assoc_array_delete_collapse_iterator(स्थिर व्योम *leaf,
						व्योम *iterator_data)
अणु
	काष्ठा assoc_array_delete_collapse_context *collapse = iterator_data;

	अगर (leaf == collapse->skip_leaf)
		वापस 0;

	BUG_ON(collapse->slot >= ASSOC_ARRAY_FAN_OUT);

	collapse->node->slots[collapse->slot++] = assoc_array_leaf_to_ptr(leaf);
	वापस 0;
पूर्ण

/**
 * assoc_array_delete - Script deletion of an object from an associative array
 * @array: The array to search.
 * @ops: The operations to use.
 * @index_key: The key to the object.
 *
 * Precalculate and pपुनः_स्मृतिate a script क्रम the deletion of an object from an
 * associative array.  This results in an edit script that can either be
 * applied or cancelled.
 *
 * The function वापसs a poपूर्णांकer to an edit script अगर the object was found,
 * शून्य अगर the object was not found or -ENOMEM.
 *
 * The caller should lock against other modअगरications and must जारी to hold
 * the lock until assoc_array_apply_edit() has been called.
 *
 * Accesses to the tree may take place concurrently with this function,
 * provided they hold the RCU पढ़ो lock.
 */
काष्ठा assoc_array_edit *assoc_array_delete(काष्ठा assoc_array *array,
					    स्थिर काष्ठा assoc_array_ops *ops,
					    स्थिर व्योम *index_key)
अणु
	काष्ठा assoc_array_delete_collapse_context collapse;
	काष्ठा assoc_array_walk_result result;
	काष्ठा assoc_array_node *node, *new_n0;
	काष्ठा assoc_array_edit *edit;
	काष्ठा assoc_array_ptr *ptr;
	bool has_meta;
	पूर्णांक slot, i;

	pr_devel("-->%s()\n", __func__);

	edit = kzalloc(माप(काष्ठा assoc_array_edit), GFP_KERNEL);
	अगर (!edit)
		वापस ERR_PTR(-ENOMEM);
	edit->array = array;
	edit->ops = ops;
	edit->adjust_count_by = -1;

	चयन (assoc_array_walk(array, ops, index_key, &result)) अणु
	हाल assoc_array_walk_found_terminal_node:
		/* We found a node that should contain the leaf we've been
		 * asked to हटाओ - *अगर* it's in the tree.
		 */
		pr_devel("terminal_node\n");
		node = result.terminal_node.node;

		क्रम (slot = 0; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
			ptr = node->slots[slot];
			अगर (ptr &&
			    assoc_array_ptr_is_leaf(ptr) &&
			    ops->compare_object(assoc_array_ptr_to_leaf(ptr),
						index_key))
				जाओ found_leaf;
		पूर्ण
		fallthrough;
	हाल assoc_array_walk_tree_empty:
	हाल assoc_array_walk_found_wrong_लघुcut:
	शेष:
		assoc_array_cancel_edit(edit);
		pr_devel("not found\n");
		वापस शून्य;
	पूर्ण

found_leaf:
	BUG_ON(array->nr_leaves_on_tree <= 0);

	/* In the simplest क्रमm of deletion we just clear the slot and release
	 * the leaf after a suitable पूर्णांकerval.
	 */
	edit->dead_leaf = node->slots[slot];
	edit->set[0].ptr = &node->slots[slot];
	edit->set[0].to = शून्य;
	edit->adjust_count_on = node;

	/* If that concludes erasure of the last leaf, then delete the entire
	 * पूर्णांकernal array.
	 */
	अगर (array->nr_leaves_on_tree == 1) अणु
		edit->set[1].ptr = &array->root;
		edit->set[1].to = शून्य;
		edit->adjust_count_on = शून्य;
		edit->excised_subtree = array->root;
		pr_devel("all gone\n");
		वापस edit;
	पूर्ण

	/* However, we'd also like to clear up some metadata blocks अगर we
	 * possibly can.
	 *
	 * We go क्रम a simple algorithm of: अगर this node has FAN_OUT or fewer
	 * leaves in it, then attempt to collapse it - and attempt to
	 * recursively collapse up the tree.
	 *
	 * We could also try and collapse in partially filled subtrees to take
	 * up space in this node.
	 */
	अगर (node->nr_leaves_on_branch <= ASSOC_ARRAY_FAN_OUT + 1) अणु
		काष्ठा assoc_array_node *parent, *gअक्रमparent;
		काष्ठा assoc_array_ptr *ptr;

		/* First of all, we need to know अगर this node has metadata so
		 * that we करोn't try collapsing अगर all the leaves are alपढ़ोy
		 * here.
		 */
		has_meta = false;
		क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
			ptr = node->slots[i];
			अगर (assoc_array_ptr_is_meta(ptr)) अणु
				has_meta = true;
				अवरोध;
			पूर्ण
		पूर्ण

		pr_devel("leaves: %ld [m=%d]\n",
			 node->nr_leaves_on_branch - 1, has_meta);

		/* Look further up the tree to see अगर we can collapse this node
		 * पूर्णांकo a more proximal node too.
		 */
		parent = node;
	collapse_up:
		pr_devel("collapse subtree: %ld\n", parent->nr_leaves_on_branch);

		ptr = parent->back_poपूर्णांकer;
		अगर (!ptr)
			जाओ करो_collapse;
		अगर (assoc_array_ptr_is_लघुcut(ptr)) अणु
			काष्ठा assoc_array_लघुcut *s = assoc_array_ptr_to_लघुcut(ptr);
			ptr = s->back_poपूर्णांकer;
			अगर (!ptr)
				जाओ करो_collapse;
		पूर्ण

		gअक्रमparent = assoc_array_ptr_to_node(ptr);
		अगर (gअक्रमparent->nr_leaves_on_branch <= ASSOC_ARRAY_FAN_OUT + 1) अणु
			parent = gअक्रमparent;
			जाओ collapse_up;
		पूर्ण

	करो_collapse:
		/* There's no poपूर्णांक collapsing अगर the original node has no meta
		 * poपूर्णांकers to discard and अगर we didn't merge पूर्णांकo one of that
		 * node's ancestry.
		 */
		अगर (has_meta || parent != node) अणु
			node = parent;

			/* Create a new node to collapse पूर्णांकo */
			new_n0 = kzalloc(माप(काष्ठा assoc_array_node), GFP_KERNEL);
			अगर (!new_n0)
				जाओ enomem;
			edit->new_meta[0] = assoc_array_node_to_ptr(new_n0);

			new_n0->back_poपूर्णांकer = node->back_poपूर्णांकer;
			new_n0->parent_slot = node->parent_slot;
			new_n0->nr_leaves_on_branch = node->nr_leaves_on_branch;
			edit->adjust_count_on = new_n0;

			collapse.node = new_n0;
			collapse.skip_leaf = assoc_array_ptr_to_leaf(edit->dead_leaf);
			collapse.slot = 0;
			assoc_array_subtree_iterate(assoc_array_node_to_ptr(node),
						    node->back_poपूर्णांकer,
						    assoc_array_delete_collapse_iterator,
						    &collapse);
			pr_devel("collapsed %d,%lu\n", collapse.slot, new_n0->nr_leaves_on_branch);
			BUG_ON(collapse.slot != new_n0->nr_leaves_on_branch - 1);

			अगर (!node->back_poपूर्णांकer) अणु
				edit->set[1].ptr = &array->root;
			पूर्ण अन्यथा अगर (assoc_array_ptr_is_leaf(node->back_poपूर्णांकer)) अणु
				BUG();
			पूर्ण अन्यथा अगर (assoc_array_ptr_is_node(node->back_poपूर्णांकer)) अणु
				काष्ठा assoc_array_node *p =
					assoc_array_ptr_to_node(node->back_poपूर्णांकer);
				edit->set[1].ptr = &p->slots[node->parent_slot];
			पूर्ण अन्यथा अगर (assoc_array_ptr_is_लघुcut(node->back_poपूर्णांकer)) अणु
				काष्ठा assoc_array_लघुcut *s =
					assoc_array_ptr_to_लघुcut(node->back_poपूर्णांकer);
				edit->set[1].ptr = &s->next_node;
			पूर्ण
			edit->set[1].to = assoc_array_node_to_ptr(new_n0);
			edit->excised_subtree = assoc_array_node_to_ptr(node);
		पूर्ण
	पूर्ण

	वापस edit;

enomem:
	/* Clean up after an out of memory error */
	pr_devel("enomem\n");
	assoc_array_cancel_edit(edit);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * assoc_array_clear - Script deletion of all objects from an associative array
 * @array: The array to clear.
 * @ops: The operations to use.
 *
 * Precalculate and pपुनः_स्मृतिate a script क्रम the deletion of all the objects
 * from an associative array.  This results in an edit script that can either
 * be applied or cancelled.
 *
 * The function वापसs a poपूर्णांकer to an edit script अगर there are objects to be
 * deleted, शून्य अगर there are no objects in the array or -ENOMEM.
 *
 * The caller should lock against other modअगरications and must जारी to hold
 * the lock until assoc_array_apply_edit() has been called.
 *
 * Accesses to the tree may take place concurrently with this function,
 * provided they hold the RCU पढ़ो lock.
 */
काष्ठा assoc_array_edit *assoc_array_clear(काष्ठा assoc_array *array,
					   स्थिर काष्ठा assoc_array_ops *ops)
अणु
	काष्ठा assoc_array_edit *edit;

	pr_devel("-->%s()\n", __func__);

	अगर (!array->root)
		वापस शून्य;

	edit = kzalloc(माप(काष्ठा assoc_array_edit), GFP_KERNEL);
	अगर (!edit)
		वापस ERR_PTR(-ENOMEM);
	edit->array = array;
	edit->ops = ops;
	edit->set[1].ptr = &array->root;
	edit->set[1].to = शून्य;
	edit->excised_subtree = array->root;
	edit->ops_क्रम_excised_subtree = ops;
	pr_devel("all gone\n");
	वापस edit;
पूर्ण

/*
 * Handle the deferred deकाष्ठाion after an applied edit.
 */
अटल व्योम assoc_array_rcu_cleanup(काष्ठा rcu_head *head)
अणु
	काष्ठा assoc_array_edit *edit =
		container_of(head, काष्ठा assoc_array_edit, rcu);
	पूर्णांक i;

	pr_devel("-->%s()\n", __func__);

	अगर (edit->dead_leaf)
		edit->ops->मुक्त_object(assoc_array_ptr_to_leaf(edit->dead_leaf));
	क्रम (i = 0; i < ARRAY_SIZE(edit->excised_meta); i++)
		अगर (edit->excised_meta[i])
			kमुक्त(assoc_array_ptr_to_node(edit->excised_meta[i]));

	अगर (edit->excised_subtree) अणु
		BUG_ON(assoc_array_ptr_is_leaf(edit->excised_subtree));
		अगर (assoc_array_ptr_is_node(edit->excised_subtree)) अणु
			काष्ठा assoc_array_node *n =
				assoc_array_ptr_to_node(edit->excised_subtree);
			n->back_poपूर्णांकer = शून्य;
		पूर्ण अन्यथा अणु
			काष्ठा assoc_array_लघुcut *s =
				assoc_array_ptr_to_लघुcut(edit->excised_subtree);
			s->back_poपूर्णांकer = शून्य;
		पूर्ण
		assoc_array_destroy_subtree(edit->excised_subtree,
					    edit->ops_क्रम_excised_subtree);
	पूर्ण

	kमुक्त(edit);
पूर्ण

/**
 * assoc_array_apply_edit - Apply an edit script to an associative array
 * @edit: The script to apply.
 *
 * Apply an edit script to an associative array to effect an insertion,
 * deletion or clearance.  As the edit script includes pपुनः_स्मृतिated memory,
 * this is guaranteed not to fail.
 *
 * The edit script, dead objects and dead metadata will be scheduled क्रम
 * deकाष्ठाion after an RCU grace period to permit those करोing पढ़ो-only
 * accesses on the array to जारी to करो so under the RCU पढ़ो lock whilst
 * the edit is taking place.
 */
व्योम assoc_array_apply_edit(काष्ठा assoc_array_edit *edit)
अणु
	काष्ठा assoc_array_लघुcut *लघुcut;
	काष्ठा assoc_array_node *node;
	काष्ठा assoc_array_ptr *ptr;
	पूर्णांक i;

	pr_devel("-->%s()\n", __func__);

	smp_wmb();
	अगर (edit->leaf_p)
		*edit->leaf_p = edit->leaf;

	smp_wmb();
	क्रम (i = 0; i < ARRAY_SIZE(edit->set_parent_slot); i++)
		अगर (edit->set_parent_slot[i].p)
			*edit->set_parent_slot[i].p = edit->set_parent_slot[i].to;

	smp_wmb();
	क्रम (i = 0; i < ARRAY_SIZE(edit->set_backpoपूर्णांकers); i++)
		अगर (edit->set_backpoपूर्णांकers[i])
			*edit->set_backpoपूर्णांकers[i] = edit->set_backpoपूर्णांकers_to;

	smp_wmb();
	क्रम (i = 0; i < ARRAY_SIZE(edit->set); i++)
		अगर (edit->set[i].ptr)
			*edit->set[i].ptr = edit->set[i].to;

	अगर (edit->array->root == शून्य) अणु
		edit->array->nr_leaves_on_tree = 0;
	पूर्ण अन्यथा अगर (edit->adjust_count_on) अणु
		node = edit->adjust_count_on;
		क्रम (;;) अणु
			node->nr_leaves_on_branch += edit->adjust_count_by;

			ptr = node->back_poपूर्णांकer;
			अगर (!ptr)
				अवरोध;
			अगर (assoc_array_ptr_is_लघुcut(ptr)) अणु
				लघुcut = assoc_array_ptr_to_लघुcut(ptr);
				ptr = लघुcut->back_poपूर्णांकer;
				अगर (!ptr)
					अवरोध;
			पूर्ण
			BUG_ON(!assoc_array_ptr_is_node(ptr));
			node = assoc_array_ptr_to_node(ptr);
		पूर्ण

		edit->array->nr_leaves_on_tree += edit->adjust_count_by;
	पूर्ण

	call_rcu(&edit->rcu, assoc_array_rcu_cleanup);
पूर्ण

/**
 * assoc_array_cancel_edit - Discard an edit script.
 * @edit: The script to discard.
 *
 * Free an edit script and all the pपुनः_स्मृतिated data it holds without making
 * any changes to the associative array it was पूर्णांकended क्रम.
 *
 * NOTE!  In the हाल of an insertion script, this करोes _not_ release the leaf
 * that was to be inserted.  That is left to the caller.
 */
व्योम assoc_array_cancel_edit(काष्ठा assoc_array_edit *edit)
अणु
	काष्ठा assoc_array_ptr *ptr;
	पूर्णांक i;

	pr_devel("-->%s()\n", __func__);

	/* Clean up after an out of memory error */
	क्रम (i = 0; i < ARRAY_SIZE(edit->new_meta); i++) अणु
		ptr = edit->new_meta[i];
		अगर (ptr) अणु
			अगर (assoc_array_ptr_is_node(ptr))
				kमुक्त(assoc_array_ptr_to_node(ptr));
			अन्यथा
				kमुक्त(assoc_array_ptr_to_लघुcut(ptr));
		पूर्ण
	पूर्ण
	kमुक्त(edit);
पूर्ण

/**
 * assoc_array_gc - Garbage collect an associative array.
 * @array: The array to clean.
 * @ops: The operations to use.
 * @iterator: A callback function to pass judgement on each object.
 * @iterator_data: Private data क्रम the callback function.
 *
 * Collect garbage from an associative array and pack करोwn the पूर्णांकernal tree to
 * save memory.
 *
 * The iterator function is asked to pass judgement upon each object in the
 * array.  If it वापसs false, the object is discard and अगर it वापसs true,
 * the object is kept.  If it वापसs true, it must increment the object's
 * usage count (or whatever it needs to करो to retain it) beक्रमe वापसing.
 *
 * This function वापसs 0 अगर successful or -ENOMEM अगर out of memory.  In the
 * latter हाल, the array is not changed.
 *
 * The caller should lock against other modअगरications and must जारी to hold
 * the lock until assoc_array_apply_edit() has been called.
 *
 * Accesses to the tree may take place concurrently with this function,
 * provided they hold the RCU पढ़ो lock.
 */
पूर्णांक assoc_array_gc(काष्ठा assoc_array *array,
		   स्थिर काष्ठा assoc_array_ops *ops,
		   bool (*iterator)(व्योम *object, व्योम *iterator_data),
		   व्योम *iterator_data)
अणु
	काष्ठा assoc_array_लघुcut *लघुcut, *new_s;
	काष्ठा assoc_array_node *node, *new_n;
	काष्ठा assoc_array_edit *edit;
	काष्ठा assoc_array_ptr *cursor, *ptr;
	काष्ठा assoc_array_ptr *new_root, *new_parent, **new_ptr_pp;
	अचिन्हित दीर्घ nr_leaves_on_tree;
	पूर्णांक keylen, slot, nr_मुक्त, next_slot, i;

	pr_devel("-->%s()\n", __func__);

	अगर (!array->root)
		वापस 0;

	edit = kzalloc(माप(काष्ठा assoc_array_edit), GFP_KERNEL);
	अगर (!edit)
		वापस -ENOMEM;
	edit->array = array;
	edit->ops = ops;
	edit->ops_क्रम_excised_subtree = ops;
	edit->set[0].ptr = &array->root;
	edit->excised_subtree = array->root;

	new_root = new_parent = शून्य;
	new_ptr_pp = &new_root;
	cursor = array->root;

descend:
	/* If this poपूर्णांक is a लघुcut, then we need to duplicate it and
	 * advance the target cursor.
	 */
	अगर (assoc_array_ptr_is_लघुcut(cursor)) अणु
		लघुcut = assoc_array_ptr_to_लघुcut(cursor);
		keylen = round_up(लघुcut->skip_to_level, ASSOC_ARRAY_KEY_CHUNK_SIZE);
		keylen >>= ASSOC_ARRAY_KEY_CHUNK_SHIFT;
		new_s = kदो_स्मृति(माप(काष्ठा assoc_array_लघुcut) +
				keylen * माप(अचिन्हित दीर्घ), GFP_KERNEL);
		अगर (!new_s)
			जाओ enomem;
		pr_devel("dup shortcut %p -> %p\n", लघुcut, new_s);
		स_नकल(new_s, लघुcut, (माप(काष्ठा assoc_array_लघुcut) +
					 keylen * माप(अचिन्हित दीर्घ)));
		new_s->back_poपूर्णांकer = new_parent;
		new_s->parent_slot = लघुcut->parent_slot;
		*new_ptr_pp = new_parent = assoc_array_लघुcut_to_ptr(new_s);
		new_ptr_pp = &new_s->next_node;
		cursor = लघुcut->next_node;
	पूर्ण

	/* Duplicate the node at this position */
	node = assoc_array_ptr_to_node(cursor);
	new_n = kzalloc(माप(काष्ठा assoc_array_node), GFP_KERNEL);
	अगर (!new_n)
		जाओ enomem;
	pr_devel("dup node %p -> %p\n", node, new_n);
	new_n->back_poपूर्णांकer = new_parent;
	new_n->parent_slot = node->parent_slot;
	*new_ptr_pp = new_parent = assoc_array_node_to_ptr(new_n);
	new_ptr_pp = शून्य;
	slot = 0;

जारी_node:
	/* Filter across any leaves and gc any subtrees */
	क्रम (; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
		ptr = node->slots[slot];
		अगर (!ptr)
			जारी;

		अगर (assoc_array_ptr_is_leaf(ptr)) अणु
			अगर (iterator(assoc_array_ptr_to_leaf(ptr),
				     iterator_data))
				/* The iterator will have करोne any reference
				 * counting on the object क्रम us.
				 */
				new_n->slots[slot] = ptr;
			जारी;
		पूर्ण

		new_ptr_pp = &new_n->slots[slot];
		cursor = ptr;
		जाओ descend;
	पूर्ण

	pr_devel("-- compress node %p --\n", new_n);

	/* Count up the number of empty slots in this node and work out the
	 * subtree leaf count.
	 */
	new_n->nr_leaves_on_branch = 0;
	nr_मुक्त = 0;
	क्रम (slot = 0; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
		ptr = new_n->slots[slot];
		अगर (!ptr)
			nr_मुक्त++;
		अन्यथा अगर (assoc_array_ptr_is_leaf(ptr))
			new_n->nr_leaves_on_branch++;
	पूर्ण
	pr_devel("free=%d, leaves=%lu\n", nr_मुक्त, new_n->nr_leaves_on_branch);

	/* See what we can fold in */
	next_slot = 0;
	क्रम (slot = 0; slot < ASSOC_ARRAY_FAN_OUT; slot++) अणु
		काष्ठा assoc_array_लघुcut *s;
		काष्ठा assoc_array_node *child;

		ptr = new_n->slots[slot];
		अगर (!ptr || assoc_array_ptr_is_leaf(ptr))
			जारी;

		s = शून्य;
		अगर (assoc_array_ptr_is_लघुcut(ptr)) अणु
			s = assoc_array_ptr_to_लघुcut(ptr);
			ptr = s->next_node;
		पूर्ण

		child = assoc_array_ptr_to_node(ptr);
		new_n->nr_leaves_on_branch += child->nr_leaves_on_branch;

		अगर (child->nr_leaves_on_branch <= nr_मुक्त + 1) अणु
			/* Fold the child node पूर्णांकo this one */
			pr_devel("[%d] fold node %lu/%d [nx %d]\n",
				 slot, child->nr_leaves_on_branch, nr_मुक्त + 1,
				 next_slot);

			/* We would alपढ़ोy have reaped an पूर्णांकervening लघुcut
			 * on the way back up the tree.
			 */
			BUG_ON(s);

			new_n->slots[slot] = शून्य;
			nr_मुक्त++;
			अगर (slot < next_slot)
				next_slot = slot;
			क्रम (i = 0; i < ASSOC_ARRAY_FAN_OUT; i++) अणु
				काष्ठा assoc_array_ptr *p = child->slots[i];
				अगर (!p)
					जारी;
				BUG_ON(assoc_array_ptr_is_meta(p));
				जबतक (new_n->slots[next_slot])
					next_slot++;
				BUG_ON(next_slot >= ASSOC_ARRAY_FAN_OUT);
				new_n->slots[next_slot++] = p;
				nr_मुक्त--;
			पूर्ण
			kमुक्त(child);
		पूर्ण अन्यथा अणु
			pr_devel("[%d] retain node %lu/%d [nx %d]\n",
				 slot, child->nr_leaves_on_branch, nr_मुक्त + 1,
				 next_slot);
		पूर्ण
	पूर्ण

	pr_devel("after: %lu\n", new_n->nr_leaves_on_branch);

	nr_leaves_on_tree = new_n->nr_leaves_on_branch;

	/* Excise this node अगर it is singly occupied by a लघुcut */
	अगर (nr_मुक्त == ASSOC_ARRAY_FAN_OUT - 1) अणु
		क्रम (slot = 0; slot < ASSOC_ARRAY_FAN_OUT; slot++)
			अगर ((ptr = new_n->slots[slot]))
				अवरोध;

		अगर (assoc_array_ptr_is_meta(ptr) &&
		    assoc_array_ptr_is_लघुcut(ptr)) अणु
			pr_devel("excise node %p with 1 shortcut\n", new_n);
			new_s = assoc_array_ptr_to_लघुcut(ptr);
			new_parent = new_n->back_poपूर्णांकer;
			slot = new_n->parent_slot;
			kमुक्त(new_n);
			अगर (!new_parent) अणु
				new_s->back_poपूर्णांकer = शून्य;
				new_s->parent_slot = 0;
				new_root = ptr;
				जाओ gc_complete;
			पूर्ण

			अगर (assoc_array_ptr_is_लघुcut(new_parent)) अणु
				/* We can discard any preceding लघुcut also */
				काष्ठा assoc_array_लघुcut *s =
					assoc_array_ptr_to_लघुcut(new_parent);

				pr_devel("excise preceding shortcut\n");

				new_parent = new_s->back_poपूर्णांकer = s->back_poपूर्णांकer;
				slot = new_s->parent_slot = s->parent_slot;
				kमुक्त(s);
				अगर (!new_parent) अणु
					new_s->back_poपूर्णांकer = शून्य;
					new_s->parent_slot = 0;
					new_root = ptr;
					जाओ gc_complete;
				पूर्ण
			पूर्ण

			new_s->back_poपूर्णांकer = new_parent;
			new_s->parent_slot = slot;
			new_n = assoc_array_ptr_to_node(new_parent);
			new_n->slots[slot] = ptr;
			जाओ ascend_old_tree;
		पूर्ण
	पूर्ण

	/* Excise any लघुcuts we might encounter that poपूर्णांक to nodes that
	 * only contain leaves.
	 */
	ptr = new_n->back_poपूर्णांकer;
	अगर (!ptr)
		जाओ gc_complete;

	अगर (assoc_array_ptr_is_लघुcut(ptr)) अणु
		new_s = assoc_array_ptr_to_लघुcut(ptr);
		new_parent = new_s->back_poपूर्णांकer;
		slot = new_s->parent_slot;

		अगर (new_n->nr_leaves_on_branch <= ASSOC_ARRAY_FAN_OUT) अणु
			काष्ठा assoc_array_node *n;

			pr_devel("excise shortcut\n");
			new_n->back_poपूर्णांकer = new_parent;
			new_n->parent_slot = slot;
			kमुक्त(new_s);
			अगर (!new_parent) अणु
				new_root = assoc_array_node_to_ptr(new_n);
				जाओ gc_complete;
			पूर्ण

			n = assoc_array_ptr_to_node(new_parent);
			n->slots[slot] = assoc_array_node_to_ptr(new_n);
		पूर्ण
	पूर्ण अन्यथा अणु
		new_parent = ptr;
	पूर्ण
	new_n = assoc_array_ptr_to_node(new_parent);

ascend_old_tree:
	ptr = node->back_poपूर्णांकer;
	अगर (assoc_array_ptr_is_लघुcut(ptr)) अणु
		लघुcut = assoc_array_ptr_to_लघुcut(ptr);
		slot = लघुcut->parent_slot;
		cursor = लघुcut->back_poपूर्णांकer;
		अगर (!cursor)
			जाओ gc_complete;
	पूर्ण अन्यथा अणु
		slot = node->parent_slot;
		cursor = ptr;
	पूर्ण
	BUG_ON(!cursor);
	node = assoc_array_ptr_to_node(cursor);
	slot++;
	जाओ जारी_node;

gc_complete:
	edit->set[0].to = new_root;
	assoc_array_apply_edit(edit);
	array->nr_leaves_on_tree = nr_leaves_on_tree;
	वापस 0;

enomem:
	pr_devel("enomem\n");
	assoc_array_destroy_subtree(new_root, edit->ops);
	kमुक्त(edit);
	वापस -ENOMEM;
पूर्ण
