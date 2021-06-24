<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-btree.h"
#समावेश "dm-btree-internal.h"
#समावेश "dm-transaction-manager.h"

#समावेश <linux/export.h>

/*
 * Removing an entry from a btree
 * ==============================
 *
 * A very important स्थिरraपूर्णांक क्रम our btree is that no node, except the
 * root, may have fewer than a certain number of entries.
 * (MIN_ENTRIES <= nr_entries <= MAX_ENTRIES).
 *
 * Ensuring this is complicated by the way we want to only ever hold the
 * locks on 2 nodes concurrently, and only change nodes in a top to bottom
 * fashion.
 *
 * Each node may have a left or right sibling.  When decending the spine,
 * अगर a node contains only MIN_ENTRIES then we try and increase this to at
 * least MIN_ENTRIES + 1.  We करो this in the following ways:
 *
 * [A] No siblings => this can only happen अगर the node is the root, in which
 *     हाल we copy the childs contents over the root.
 *
 * [B] No left sibling
 *     ==> rebalance(node, right sibling)
 *
 * [C] No right sibling
 *     ==> rebalance(left sibling, node)
 *
 * [D] Both siblings, total_entries(left, node, right) <= DEL_THRESHOLD
 *     ==> delete node adding it's contents to left and right
 *
 * [E] Both siblings, total_entries(left, node, right) > DEL_THRESHOLD
 *     ==> rebalance(left, node, right)
 *
 * After these operations it's possible that the our original node no
 * दीर्घer contains the desired sub tree.  For this reason this rebalancing
 * is perक्रमmed on the children of the current node.  This also aव्योमs
 * having a special हाल क्रम the root.
 *
 * Once this rebalancing has occurred we can then step पूर्णांकo the child node
 * क्रम पूर्णांकernal nodes.  Or delete the entry क्रम leaf nodes.
 */

/*
 * Some little utilities क्रम moving node data around.
 */
अटल व्योम node_shअगरt(काष्ठा btree_node *n, पूर्णांक shअगरt)
अणु
	uपूर्णांक32_t nr_entries = le32_to_cpu(n->header.nr_entries);
	uपूर्णांक32_t value_size = le32_to_cpu(n->header.value_size);

	अगर (shअगरt < 0) अणु
		shअगरt = -shअगरt;
		BUG_ON(shअगरt > nr_entries);
		BUG_ON((व्योम *) key_ptr(n, shअगरt) >= value_ptr(n, shअगरt));
		स_हटाओ(key_ptr(n, 0),
			key_ptr(n, shअगरt),
			(nr_entries - shअगरt) * माप(__le64));
		स_हटाओ(value_ptr(n, 0),
			value_ptr(n, shअगरt),
			(nr_entries - shअगरt) * value_size);
	पूर्ण अन्यथा अणु
		BUG_ON(nr_entries + shअगरt > le32_to_cpu(n->header.max_entries));
		स_हटाओ(key_ptr(n, shअगरt),
			key_ptr(n, 0),
			nr_entries * माप(__le64));
		स_हटाओ(value_ptr(n, shअगरt),
			value_ptr(n, 0),
			nr_entries * value_size);
	पूर्ण
पूर्ण

अटल व्योम node_copy(काष्ठा btree_node *left, काष्ठा btree_node *right, पूर्णांक shअगरt)
अणु
	uपूर्णांक32_t nr_left = le32_to_cpu(left->header.nr_entries);
	uपूर्णांक32_t value_size = le32_to_cpu(left->header.value_size);
	BUG_ON(value_size != le32_to_cpu(right->header.value_size));

	अगर (shअगरt < 0) अणु
		shअगरt = -shअगरt;
		BUG_ON(nr_left + shअगरt > le32_to_cpu(left->header.max_entries));
		स_नकल(key_ptr(left, nr_left),
		       key_ptr(right, 0),
		       shअगरt * माप(__le64));
		स_नकल(value_ptr(left, nr_left),
		       value_ptr(right, 0),
		       shअगरt * value_size);
	पूर्ण अन्यथा अणु
		BUG_ON(shअगरt > le32_to_cpu(right->header.max_entries));
		स_नकल(key_ptr(right, 0),
		       key_ptr(left, nr_left - shअगरt),
		       shअगरt * माप(__le64));
		स_नकल(value_ptr(right, 0),
		       value_ptr(left, nr_left - shअगरt),
		       shअगरt * value_size);
	पूर्ण
पूर्ण

/*
 * Delete a specअगरic entry from a leaf node.
 */
अटल व्योम delete_at(काष्ठा btree_node *n, अचिन्हित index)
अणु
	अचिन्हित nr_entries = le32_to_cpu(n->header.nr_entries);
	अचिन्हित nr_to_copy = nr_entries - (index + 1);
	uपूर्णांक32_t value_size = le32_to_cpu(n->header.value_size);
	BUG_ON(index >= nr_entries);

	अगर (nr_to_copy) अणु
		स_हटाओ(key_ptr(n, index),
			key_ptr(n, index + 1),
			nr_to_copy * माप(__le64));

		स_हटाओ(value_ptr(n, index),
			value_ptr(n, index + 1),
			nr_to_copy * value_size);
	पूर्ण

	n->header.nr_entries = cpu_to_le32(nr_entries - 1);
पूर्ण

अटल अचिन्हित merge_threshold(काष्ठा btree_node *n)
अणु
	वापस le32_to_cpu(n->header.max_entries) / 3;
पूर्ण

काष्ठा child अणु
	अचिन्हित index;
	काष्ठा dm_block *block;
	काष्ठा btree_node *n;
पूर्ण;

अटल पूर्णांक init_child(काष्ठा dm_btree_info *info, काष्ठा dm_btree_value_type *vt,
		      काष्ठा btree_node *parent,
		      अचिन्हित index, काष्ठा child *result)
अणु
	पूर्णांक r, inc;
	dm_block_t root;

	result->index = index;
	root = value64(parent, index);

	r = dm_पंचांग_shaकरोw_block(info->पंचांग, root, &btree_node_validator,
			       &result->block, &inc);
	अगर (r)
		वापस r;

	result->n = dm_block_data(result->block);

	अगर (inc)
		inc_children(info->पंचांग, result->n, vt);

	*((__le64 *) value_ptr(parent, index)) =
		cpu_to_le64(dm_block_location(result->block));

	वापस 0;
पूर्ण

अटल व्योम निकास_child(काष्ठा dm_btree_info *info, काष्ठा child *c)
अणु
	dm_पंचांग_unlock(info->पंचांग, c->block);
पूर्ण

अटल व्योम shअगरt(काष्ठा btree_node *left, काष्ठा btree_node *right, पूर्णांक count)
अणु
	uपूर्णांक32_t nr_left = le32_to_cpu(left->header.nr_entries);
	uपूर्णांक32_t nr_right = le32_to_cpu(right->header.nr_entries);
	uपूर्णांक32_t max_entries = le32_to_cpu(left->header.max_entries);
	uपूर्णांक32_t r_max_entries = le32_to_cpu(right->header.max_entries);

	BUG_ON(max_entries != r_max_entries);
	BUG_ON(nr_left - count > max_entries);
	BUG_ON(nr_right + count > max_entries);

	अगर (!count)
		वापस;

	अगर (count > 0) अणु
		node_shअगरt(right, count);
		node_copy(left, right, count);
	पूर्ण अन्यथा अणु
		node_copy(left, right, count);
		node_shअगरt(right, count);
	पूर्ण

	left->header.nr_entries = cpu_to_le32(nr_left - count);
	right->header.nr_entries = cpu_to_le32(nr_right + count);
पूर्ण

अटल व्योम __rebalance2(काष्ठा dm_btree_info *info, काष्ठा btree_node *parent,
			 काष्ठा child *l, काष्ठा child *r)
अणु
	काष्ठा btree_node *left = l->n;
	काष्ठा btree_node *right = r->n;
	uपूर्णांक32_t nr_left = le32_to_cpu(left->header.nr_entries);
	uपूर्णांक32_t nr_right = le32_to_cpu(right->header.nr_entries);
	/*
	 * Ensure the number of entries in each child will be greater
	 * than or equal to (max_entries / 3 + 1), so no matter which
	 * child is used क्रम removal, the number will still be not
	 * less than (max_entries / 3).
	 */
	अचिन्हित पूर्णांक threshold = 2 * (merge_threshold(left) + 1);

	अगर (nr_left + nr_right < threshold) अणु
		/*
		 * Merge
		 */
		node_copy(left, right, -nr_right);
		left->header.nr_entries = cpu_to_le32(nr_left + nr_right);
		delete_at(parent, r->index);

		/*
		 * We need to decrement the right block, but not it's
		 * children, since they're still referenced by left.
		 */
		dm_पंचांग_dec(info->पंचांग, dm_block_location(r->block));
	पूर्ण अन्यथा अणु
		/*
		 * Rebalance.
		 */
		अचिन्हित target_left = (nr_left + nr_right) / 2;
		shअगरt(left, right, nr_left - target_left);
		*key_ptr(parent, r->index) = right->keys[0];
	पूर्ण
पूर्ण

अटल पूर्णांक rebalance2(काष्ठा shaकरोw_spine *s, काष्ठा dm_btree_info *info,
		      काष्ठा dm_btree_value_type *vt, अचिन्हित left_index)
अणु
	पूर्णांक r;
	काष्ठा btree_node *parent;
	काष्ठा child left, right;

	parent = dm_block_data(shaकरोw_current(s));

	r = init_child(info, vt, parent, left_index, &left);
	अगर (r)
		वापस r;

	r = init_child(info, vt, parent, left_index + 1, &right);
	अगर (r) अणु
		निकास_child(info, &left);
		वापस r;
	पूर्ण

	__rebalance2(info, parent, &left, &right);

	निकास_child(info, &left);
	निकास_child(info, &right);

	वापस 0;
पूर्ण

/*
 * We dump as many entries from center as possible पूर्णांकo left, then the rest
 * in right, then rebalance2.  This wastes some cpu, but I want something
 * simple aपंचांग.
 */
अटल व्योम delete_center_node(काष्ठा dm_btree_info *info, काष्ठा btree_node *parent,
			       काष्ठा child *l, काष्ठा child *c, काष्ठा child *r,
			       काष्ठा btree_node *left, काष्ठा btree_node *center, काष्ठा btree_node *right,
			       uपूर्णांक32_t nr_left, uपूर्णांक32_t nr_center, uपूर्णांक32_t nr_right)
अणु
	uपूर्णांक32_t max_entries = le32_to_cpu(left->header.max_entries);
	अचिन्हित shअगरt = min(max_entries - nr_left, nr_center);

	BUG_ON(nr_left + shअगरt > max_entries);
	node_copy(left, center, -shअगरt);
	left->header.nr_entries = cpu_to_le32(nr_left + shअगरt);

	अगर (shअगरt != nr_center) अणु
		shअगरt = nr_center - shअगरt;
		BUG_ON((nr_right + shअगरt) > max_entries);
		node_shअगरt(right, shअगरt);
		node_copy(center, right, shअगरt);
		right->header.nr_entries = cpu_to_le32(nr_right + shअगरt);
	पूर्ण
	*key_ptr(parent, r->index) = right->keys[0];

	delete_at(parent, c->index);
	r->index--;

	dm_पंचांग_dec(info->पंचांग, dm_block_location(c->block));
	__rebalance2(info, parent, l, r);
पूर्ण

/*
 * Redistributes entries among 3 sibling nodes.
 */
अटल व्योम redistribute3(काष्ठा dm_btree_info *info, काष्ठा btree_node *parent,
			  काष्ठा child *l, काष्ठा child *c, काष्ठा child *r,
			  काष्ठा btree_node *left, काष्ठा btree_node *center, काष्ठा btree_node *right,
			  uपूर्णांक32_t nr_left, uपूर्णांक32_t nr_center, uपूर्णांक32_t nr_right)
अणु
	पूर्णांक s;
	uपूर्णांक32_t max_entries = le32_to_cpu(left->header.max_entries);
	अचिन्हित total = nr_left + nr_center + nr_right;
	अचिन्हित target_right = total / 3;
	अचिन्हित reमुख्यder = (target_right * 3) != total;
	अचिन्हित target_left = target_right + reमुख्यder;

	BUG_ON(target_left > max_entries);
	BUG_ON(target_right > max_entries);

	अगर (nr_left < nr_right) अणु
		s = nr_left - target_left;

		अगर (s < 0 && nr_center < -s) अणु
			/* not enough in central node */
			shअगरt(left, center, -nr_center);
			s += nr_center;
			shअगरt(left, right, s);
			nr_right += s;
		पूर्ण अन्यथा
			shअगरt(left, center, s);

		shअगरt(center, right, target_right - nr_right);

	पूर्ण अन्यथा अणु
		s = target_right - nr_right;
		अगर (s > 0 && nr_center < s) अणु
			/* not enough in central node */
			shअगरt(center, right, nr_center);
			s -= nr_center;
			shअगरt(left, right, s);
			nr_left -= s;
		पूर्ण अन्यथा
			shअगरt(center, right, s);

		shअगरt(left, center, nr_left - target_left);
	पूर्ण

	*key_ptr(parent, c->index) = center->keys[0];
	*key_ptr(parent, r->index) = right->keys[0];
पूर्ण

अटल व्योम __rebalance3(काष्ठा dm_btree_info *info, काष्ठा btree_node *parent,
			 काष्ठा child *l, काष्ठा child *c, काष्ठा child *r)
अणु
	काष्ठा btree_node *left = l->n;
	काष्ठा btree_node *center = c->n;
	काष्ठा btree_node *right = r->n;

	uपूर्णांक32_t nr_left = le32_to_cpu(left->header.nr_entries);
	uपूर्णांक32_t nr_center = le32_to_cpu(center->header.nr_entries);
	uपूर्णांक32_t nr_right = le32_to_cpu(right->header.nr_entries);

	अचिन्हित threshold = merge_threshold(left) * 4 + 1;

	BUG_ON(left->header.max_entries != center->header.max_entries);
	BUG_ON(center->header.max_entries != right->header.max_entries);

	अगर ((nr_left + nr_center + nr_right) < threshold)
		delete_center_node(info, parent, l, c, r, left, center, right,
				   nr_left, nr_center, nr_right);
	अन्यथा
		redistribute3(info, parent, l, c, r, left, center, right,
			      nr_left, nr_center, nr_right);
पूर्ण

अटल पूर्णांक rebalance3(काष्ठा shaकरोw_spine *s, काष्ठा dm_btree_info *info,
		      काष्ठा dm_btree_value_type *vt, अचिन्हित left_index)
अणु
	पूर्णांक r;
	काष्ठा btree_node *parent = dm_block_data(shaकरोw_current(s));
	काष्ठा child left, center, right;

	/*
	 * FIXME: fill out an array?
	 */
	r = init_child(info, vt, parent, left_index, &left);
	अगर (r)
		वापस r;

	r = init_child(info, vt, parent, left_index + 1, &center);
	अगर (r) अणु
		निकास_child(info, &left);
		वापस r;
	पूर्ण

	r = init_child(info, vt, parent, left_index + 2, &right);
	अगर (r) अणु
		निकास_child(info, &left);
		निकास_child(info, &center);
		वापस r;
	पूर्ण

	__rebalance3(info, parent, &left, &center, &right);

	निकास_child(info, &left);
	निकास_child(info, &center);
	निकास_child(info, &right);

	वापस 0;
पूर्ण

अटल पूर्णांक rebalance_children(काष्ठा shaकरोw_spine *s,
			      काष्ठा dm_btree_info *info,
			      काष्ठा dm_btree_value_type *vt, uपूर्णांक64_t key)
अणु
	पूर्णांक i, r, has_left_sibling, has_right_sibling;
	काष्ठा btree_node *n;

	n = dm_block_data(shaकरोw_current(s));

	अगर (le32_to_cpu(n->header.nr_entries) == 1) अणु
		काष्ठा dm_block *child;
		dm_block_t b = value64(n, 0);

		r = dm_पंचांग_पढ़ो_lock(info->पंचांग, b, &btree_node_validator, &child);
		अगर (r)
			वापस r;

		स_नकल(n, dm_block_data(child),
		       dm_bm_block_size(dm_पंचांग_get_bm(info->पंचांग)));
		dm_पंचांग_unlock(info->पंचांग, child);

		dm_पंचांग_dec(info->पंचांग, dm_block_location(child));
		वापस 0;
	पूर्ण

	i = lower_bound(n, key);
	अगर (i < 0)
		वापस -ENODATA;

	has_left_sibling = i > 0;
	has_right_sibling = i < (le32_to_cpu(n->header.nr_entries) - 1);

	अगर (!has_left_sibling)
		r = rebalance2(s, info, vt, i);

	अन्यथा अगर (!has_right_sibling)
		r = rebalance2(s, info, vt, i - 1);

	अन्यथा
		r = rebalance3(s, info, vt, i - 1);

	वापस r;
पूर्ण

अटल पूर्णांक करो_leaf(काष्ठा btree_node *n, uपूर्णांक64_t key, अचिन्हित *index)
अणु
	पूर्णांक i = lower_bound(n, key);

	अगर ((i < 0) ||
	    (i >= le32_to_cpu(n->header.nr_entries)) ||
	    (le64_to_cpu(n->keys[i]) != key))
		वापस -ENODATA;

	*index = i;

	वापस 0;
पूर्ण

/*
 * Prepares क्रम removal from one level of the hierarchy.  The caller must
 * call delete_at() to हटाओ the entry at index.
 */
अटल पूर्णांक हटाओ_raw(काष्ठा shaकरोw_spine *s, काष्ठा dm_btree_info *info,
		      काष्ठा dm_btree_value_type *vt, dm_block_t root,
		      uपूर्णांक64_t key, अचिन्हित *index)
अणु
	पूर्णांक i = *index, r;
	काष्ठा btree_node *n;

	क्रम (;;) अणु
		r = shaकरोw_step(s, root, vt);
		अगर (r < 0)
			अवरोध;

		/*
		 * We have to patch up the parent node, ugly, but I करोn't
		 * see a way to करो this स्वतःmatically as part of the spine
		 * op.
		 */
		अगर (shaकरोw_has_parent(s)) अणु
			__le64 location = cpu_to_le64(dm_block_location(shaकरोw_current(s)));
			स_नकल(value_ptr(dm_block_data(shaकरोw_parent(s)), i),
			       &location, माप(__le64));
		पूर्ण

		n = dm_block_data(shaकरोw_current(s));

		अगर (le32_to_cpu(n->header.flags) & LEAF_NODE)
			वापस करो_leaf(n, key, index);

		r = rebalance_children(s, info, vt, key);
		अगर (r)
			अवरोध;

		n = dm_block_data(shaकरोw_current(s));
		अगर (le32_to_cpu(n->header.flags) & LEAF_NODE)
			वापस करो_leaf(n, key, index);

		i = lower_bound(n, key);

		/*
		 * We know the key is present, or अन्यथा
		 * rebalance_children would have वापसed
		 * -ENODATA
		 */
		root = value64(n, i);
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक dm_btree_हटाओ(काष्ठा dm_btree_info *info, dm_block_t root,
		    uपूर्णांक64_t *keys, dm_block_t *new_root)
अणु
	अचिन्हित level, last_level = info->levels - 1;
	पूर्णांक index = 0, r = 0;
	काष्ठा shaकरोw_spine spine;
	काष्ठा btree_node *n;
	काष्ठा dm_btree_value_type le64_vt;

	init_le64_type(info->पंचांग, &le64_vt);
	init_shaकरोw_spine(&spine, info);
	क्रम (level = 0; level < info->levels; level++) अणु
		r = हटाओ_raw(&spine, info,
			       (level == last_level ?
				&info->value_type : &le64_vt),
			       root, keys[level], (अचिन्हित *)&index);
		अगर (r < 0)
			अवरोध;

		n = dm_block_data(shaकरोw_current(&spine));
		अगर (level != last_level) अणु
			root = value64(n, index);
			जारी;
		पूर्ण

		BUG_ON(index < 0 || index >= le32_to_cpu(n->header.nr_entries));

		अगर (info->value_type.dec)
			info->value_type.dec(info->value_type.context,
					     value_ptr(n, index));

		delete_at(n, index);
	पूर्ण

	*new_root = shaकरोw_root(&spine);
	निकास_shaकरोw_spine(&spine);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_हटाओ);

/*----------------------------------------------------------------*/

अटल पूर्णांक हटाओ_nearest(काष्ठा shaकरोw_spine *s, काष्ठा dm_btree_info *info,
			  काष्ठा dm_btree_value_type *vt, dm_block_t root,
			  uपूर्णांक64_t key, पूर्णांक *index)
अणु
	पूर्णांक i = *index, r;
	काष्ठा btree_node *n;

	क्रम (;;) अणु
		r = shaकरोw_step(s, root, vt);
		अगर (r < 0)
			अवरोध;

		/*
		 * We have to patch up the parent node, ugly, but I करोn't
		 * see a way to करो this स्वतःmatically as part of the spine
		 * op.
		 */
		अगर (shaकरोw_has_parent(s)) अणु
			__le64 location = cpu_to_le64(dm_block_location(shaकरोw_current(s)));
			स_नकल(value_ptr(dm_block_data(shaकरोw_parent(s)), i),
			       &location, माप(__le64));
		पूर्ण

		n = dm_block_data(shaकरोw_current(s));

		अगर (le32_to_cpu(n->header.flags) & LEAF_NODE) अणु
			*index = lower_bound(n, key);
			वापस 0;
		पूर्ण

		r = rebalance_children(s, info, vt, key);
		अगर (r)
			अवरोध;

		n = dm_block_data(shaकरोw_current(s));
		अगर (le32_to_cpu(n->header.flags) & LEAF_NODE) अणु
			*index = lower_bound(n, key);
			वापस 0;
		पूर्ण

		i = lower_bound(n, key);

		/*
		 * We know the key is present, or अन्यथा
		 * rebalance_children would have वापसed
		 * -ENODATA
		 */
		root = value64(n, i);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक हटाओ_one(काष्ठा dm_btree_info *info, dm_block_t root,
		      uपूर्णांक64_t *keys, uपूर्णांक64_t end_key,
		      dm_block_t *new_root, अचिन्हित *nr_हटाओd)
अणु
	अचिन्हित level, last_level = info->levels - 1;
	पूर्णांक index = 0, r = 0;
	काष्ठा shaकरोw_spine spine;
	काष्ठा btree_node *n;
	काष्ठा dm_btree_value_type le64_vt;
	uपूर्णांक64_t k;

	init_le64_type(info->पंचांग, &le64_vt);
	init_shaकरोw_spine(&spine, info);
	क्रम (level = 0; level < last_level; level++) अणु
		r = हटाओ_raw(&spine, info, &le64_vt,
			       root, keys[level], (अचिन्हित *) &index);
		अगर (r < 0)
			जाओ out;

		n = dm_block_data(shaकरोw_current(&spine));
		root = value64(n, index);
	पूर्ण

	r = हटाओ_nearest(&spine, info, &info->value_type,
			   root, keys[last_level], &index);
	अगर (r < 0)
		जाओ out;

	n = dm_block_data(shaकरोw_current(&spine));

	अगर (index < 0)
		index = 0;

	अगर (index >= le32_to_cpu(n->header.nr_entries)) अणु
		r = -ENODATA;
		जाओ out;
	पूर्ण

	k = le64_to_cpu(n->keys[index]);
	अगर (k >= keys[last_level] && k < end_key) अणु
		अगर (info->value_type.dec)
			info->value_type.dec(info->value_type.context,
					     value_ptr(n, index));

		delete_at(n, index);
		keys[last_level] = k + 1ull;

	पूर्ण अन्यथा
		r = -ENODATA;

out:
	*new_root = shaकरोw_root(&spine);
	निकास_shaकरोw_spine(&spine);

	वापस r;
पूर्ण

पूर्णांक dm_btree_हटाओ_leaves(काष्ठा dm_btree_info *info, dm_block_t root,
			   uपूर्णांक64_t *first_key, uपूर्णांक64_t end_key,
			   dm_block_t *new_root, अचिन्हित *nr_हटाओd)
अणु
	पूर्णांक r;

	*nr_हटाओd = 0;
	करो अणु
		r = हटाओ_one(info, root, first_key, end_key, &root, nr_हटाओd);
		अगर (!r)
			(*nr_हटाओd)++;
	पूर्ण जबतक (!r);

	*new_root = root;
	वापस r == -ENODATA ? 0 : r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_हटाओ_leaves);
