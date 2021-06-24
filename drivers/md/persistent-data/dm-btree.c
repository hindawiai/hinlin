<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-btree-internal.h"
#समावेश "dm-space-map.h"
#समावेश "dm-transaction-manager.h"

#समावेश <linux/export.h>
#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "btree"

/*----------------------------------------------------------------
 * Array manipulation
 *--------------------------------------------------------------*/
अटल व्योम स_नकल_disk(व्योम *dest, स्थिर व्योम *src, माप_प्रकार len)
	__dm_written_to_disk(src)
अणु
	स_नकल(dest, src, len);
	__dm_unbless_क्रम_disk(src);
पूर्ण

अटल व्योम array_insert(व्योम *base, माप_प्रकार elt_size, अचिन्हित nr_elts,
			 अचिन्हित index, व्योम *elt)
	__dm_written_to_disk(elt)
अणु
	अगर (index < nr_elts)
		स_हटाओ(base + (elt_size * (index + 1)),
			base + (elt_size * index),
			(nr_elts - index) * elt_size);

	स_नकल_disk(base + (elt_size * index), elt, elt_size);
पूर्ण

/*----------------------------------------------------------------*/

/* makes the assumption that no two keys are the same. */
अटल पूर्णांक द्वा_खोज(काष्ठा btree_node *n, uपूर्णांक64_t key, पूर्णांक want_hi)
अणु
	पूर्णांक lo = -1, hi = le32_to_cpu(n->header.nr_entries);

	जबतक (hi - lo > 1) अणु
		पूर्णांक mid = lo + ((hi - lo) / 2);
		uपूर्णांक64_t mid_key = le64_to_cpu(n->keys[mid]);

		अगर (mid_key == key)
			वापस mid;

		अगर (mid_key < key)
			lo = mid;
		अन्यथा
			hi = mid;
	पूर्ण

	वापस want_hi ? hi : lo;
पूर्ण

पूर्णांक lower_bound(काष्ठा btree_node *n, uपूर्णांक64_t key)
अणु
	वापस द्वा_खोज(n, key, 0);
पूर्ण

अटल पूर्णांक upper_bound(काष्ठा btree_node *n, uपूर्णांक64_t key)
अणु
	वापस द्वा_खोज(n, key, 1);
पूर्ण

व्योम inc_children(काष्ठा dm_transaction_manager *पंचांग, काष्ठा btree_node *n,
		  काष्ठा dm_btree_value_type *vt)
अणु
	अचिन्हित i;
	uपूर्णांक32_t nr_entries = le32_to_cpu(n->header.nr_entries);

	अगर (le32_to_cpu(n->header.flags) & INTERNAL_NODE)
		क्रम (i = 0; i < nr_entries; i++)
			dm_पंचांग_inc(पंचांग, value64(n, i));
	अन्यथा अगर (vt->inc)
		क्रम (i = 0; i < nr_entries; i++)
			vt->inc(vt->context, value_ptr(n, i));
पूर्ण

अटल पूर्णांक insert_at(माप_प्रकार value_size, काष्ठा btree_node *node, अचिन्हित index,
		      uपूर्णांक64_t key, व्योम *value)
		      __dm_written_to_disk(value)
अणु
	uपूर्णांक32_t nr_entries = le32_to_cpu(node->header.nr_entries);
	__le64 key_le = cpu_to_le64(key);

	अगर (index > nr_entries ||
	    index >= le32_to_cpu(node->header.max_entries)) अणु
		DMERR("too many entries in btree node for insert");
		__dm_unbless_क्रम_disk(value);
		वापस -ENOMEM;
	पूर्ण

	__dm_bless_क्रम_disk(&key_le);

	array_insert(node->keys, माप(*node->keys), nr_entries, index, &key_le);
	array_insert(value_base(node), value_size, nr_entries, index, value);
	node->header.nr_entries = cpu_to_le32(nr_entries + 1);

	वापस 0;
पूर्ण

/*----------------------------------------------------------------*/

/*
 * We want 3n entries (क्रम some n).  This works more nicely क्रम repeated
 * insert हटाओ loops than (2n + 1).
 */
अटल uपूर्णांक32_t calc_max_entries(माप_प्रकार value_size, माप_प्रकार block_size)
अणु
	uपूर्णांक32_t total, n;
	माप_प्रकार elt_size = माप(uपूर्णांक64_t) + value_size; /* key + value */

	block_size -= माप(काष्ठा node_header);
	total = block_size / elt_size;
	n = total / 3;		/* rounds करोwn */

	वापस 3 * n;
पूर्ण

पूर्णांक dm_btree_empty(काष्ठा dm_btree_info *info, dm_block_t *root)
अणु
	पूर्णांक r;
	काष्ठा dm_block *b;
	काष्ठा btree_node *n;
	माप_प्रकार block_size;
	uपूर्णांक32_t max_entries;

	r = new_block(info, &b);
	अगर (r < 0)
		वापस r;

	block_size = dm_bm_block_size(dm_पंचांग_get_bm(info->पंचांग));
	max_entries = calc_max_entries(info->value_type.size, block_size);

	n = dm_block_data(b);
	स_रखो(n, 0, block_size);
	n->header.flags = cpu_to_le32(LEAF_NODE);
	n->header.nr_entries = cpu_to_le32(0);
	n->header.max_entries = cpu_to_le32(max_entries);
	n->header.value_size = cpu_to_le32(info->value_type.size);

	*root = dm_block_location(b);
	unlock_block(info, b);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_empty);

/*----------------------------------------------------------------*/

/*
 * Deletion uses a recursive algorithm, since we have limited stack space
 * we explicitly manage our own stack on the heap.
 */
#घोषणा MAX_SPINE_DEPTH 64
काष्ठा frame अणु
	काष्ठा dm_block *b;
	काष्ठा btree_node *n;
	अचिन्हित level;
	अचिन्हित nr_children;
	अचिन्हित current_child;
पूर्ण;

काष्ठा del_stack अणु
	काष्ठा dm_btree_info *info;
	काष्ठा dm_transaction_manager *पंचांग;
	पूर्णांक top;
	काष्ठा frame spine[MAX_SPINE_DEPTH];
पूर्ण;

अटल पूर्णांक top_frame(काष्ठा del_stack *s, काष्ठा frame **f)
अणु
	अगर (s->top < 0) अणु
		DMERR("btree deletion stack empty");
		वापस -EINVAL;
	पूर्ण

	*f = s->spine + s->top;

	वापस 0;
पूर्ण

अटल पूर्णांक unprocessed_frames(काष्ठा del_stack *s)
अणु
	वापस s->top >= 0;
पूर्ण

अटल व्योम prefetch_children(काष्ठा del_stack *s, काष्ठा frame *f)
अणु
	अचिन्हित i;
	काष्ठा dm_block_manager *bm = dm_पंचांग_get_bm(s->पंचांग);

	क्रम (i = 0; i < f->nr_children; i++)
		dm_bm_prefetch(bm, value64(f->n, i));
पूर्ण

अटल bool is_पूर्णांकernal_level(काष्ठा dm_btree_info *info, काष्ठा frame *f)
अणु
	वापस f->level < (info->levels - 1);
पूर्ण

अटल पूर्णांक push_frame(काष्ठा del_stack *s, dm_block_t b, अचिन्हित level)
अणु
	पूर्णांक r;
	uपूर्णांक32_t ref_count;

	अगर (s->top >= MAX_SPINE_DEPTH - 1) अणु
		DMERR("btree deletion stack out of memory");
		वापस -ENOMEM;
	पूर्ण

	r = dm_पंचांग_ref(s->पंचांग, b, &ref_count);
	अगर (r)
		वापस r;

	अगर (ref_count > 1)
		/*
		 * This is a shared node, so we can just decrement it's
		 * reference counter and leave the children.
		 */
		dm_पंचांग_dec(s->पंचांग, b);

	अन्यथा अणु
		uपूर्णांक32_t flags;
		काष्ठा frame *f = s->spine + ++s->top;

		r = dm_पंचांग_पढ़ो_lock(s->पंचांग, b, &btree_node_validator, &f->b);
		अगर (r) अणु
			s->top--;
			वापस r;
		पूर्ण

		f->n = dm_block_data(f->b);
		f->level = level;
		f->nr_children = le32_to_cpu(f->n->header.nr_entries);
		f->current_child = 0;

		flags = le32_to_cpu(f->n->header.flags);
		अगर (flags & INTERNAL_NODE || is_पूर्णांकernal_level(s->info, f))
			prefetch_children(s, f);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pop_frame(काष्ठा del_stack *s)
अणु
	काष्ठा frame *f = s->spine + s->top--;

	dm_पंचांग_dec(s->पंचांग, dm_block_location(f->b));
	dm_पंचांग_unlock(s->पंचांग, f->b);
पूर्ण

अटल व्योम unlock_all_frames(काष्ठा del_stack *s)
अणु
	काष्ठा frame *f;

	जबतक (unprocessed_frames(s)) अणु
		f = s->spine + s->top--;
		dm_पंचांग_unlock(s->पंचांग, f->b);
	पूर्ण
पूर्ण

पूर्णांक dm_btree_del(काष्ठा dm_btree_info *info, dm_block_t root)
अणु
	पूर्णांक r;
	काष्ठा del_stack *s;

	/*
	 * dm_btree_del() is called via an ioctl, as such should be
	 * considered an FS op.  We can't recurse back पूर्णांकo the FS, so we
	 * allocate GFP_NOFS.
	 */
	s = kदो_स्मृति(माप(*s), GFP_NOFS);
	अगर (!s)
		वापस -ENOMEM;
	s->info = info;
	s->पंचांग = info->पंचांग;
	s->top = -1;

	r = push_frame(s, root, 0);
	अगर (r)
		जाओ out;

	जबतक (unprocessed_frames(s)) अणु
		uपूर्णांक32_t flags;
		काष्ठा frame *f;
		dm_block_t b;

		r = top_frame(s, &f);
		अगर (r)
			जाओ out;

		अगर (f->current_child >= f->nr_children) अणु
			pop_frame(s);
			जारी;
		पूर्ण

		flags = le32_to_cpu(f->n->header.flags);
		अगर (flags & INTERNAL_NODE) अणु
			b = value64(f->n, f->current_child);
			f->current_child++;
			r = push_frame(s, b, f->level);
			अगर (r)
				जाओ out;

		पूर्ण अन्यथा अगर (is_पूर्णांकernal_level(info, f)) अणु
			b = value64(f->n, f->current_child);
			f->current_child++;
			r = push_frame(s, b, f->level + 1);
			अगर (r)
				जाओ out;

		पूर्ण अन्यथा अणु
			अगर (info->value_type.dec) अणु
				अचिन्हित i;

				क्रम (i = 0; i < f->nr_children; i++)
					info->value_type.dec(info->value_type.context,
							     value_ptr(f->n, i));
			पूर्ण
			pop_frame(s);
		पूर्ण
	पूर्ण
out:
	अगर (r) अणु
		/* cleanup all frames of del_stack */
		unlock_all_frames(s);
	पूर्ण
	kमुक्त(s);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_del);

/*----------------------------------------------------------------*/

अटल पूर्णांक btree_lookup_raw(काष्ठा ro_spine *s, dm_block_t block, uपूर्णांक64_t key,
			    पूर्णांक (*search_fn)(काष्ठा btree_node *, uपूर्णांक64_t),
			    uपूर्णांक64_t *result_key, व्योम *v, माप_प्रकार value_size)
अणु
	पूर्णांक i, r;
	uपूर्णांक32_t flags, nr_entries;

	करो अणु
		r = ro_step(s, block);
		अगर (r < 0)
			वापस r;

		i = search_fn(ro_node(s), key);

		flags = le32_to_cpu(ro_node(s)->header.flags);
		nr_entries = le32_to_cpu(ro_node(s)->header.nr_entries);
		अगर (i < 0 || i >= nr_entries)
			वापस -ENODATA;

		अगर (flags & INTERNAL_NODE)
			block = value64(ro_node(s), i);

	पूर्ण जबतक (!(flags & LEAF_NODE));

	*result_key = le64_to_cpu(ro_node(s)->keys[i]);
	अगर (v)
		स_नकल(v, value_ptr(ro_node(s), i), value_size);

	वापस 0;
पूर्ण

पूर्णांक dm_btree_lookup(काष्ठा dm_btree_info *info, dm_block_t root,
		    uपूर्णांक64_t *keys, व्योम *value_le)
अणु
	अचिन्हित level, last_level = info->levels - 1;
	पूर्णांक r = -ENODATA;
	uपूर्णांक64_t rkey;
	__le64 पूर्णांकernal_value_le;
	काष्ठा ro_spine spine;

	init_ro_spine(&spine, info);
	क्रम (level = 0; level < info->levels; level++) अणु
		माप_प्रकार size;
		व्योम *value_p;

		अगर (level == last_level) अणु
			value_p = value_le;
			size = info->value_type.size;

		पूर्ण अन्यथा अणु
			value_p = &पूर्णांकernal_value_le;
			size = माप(uपूर्णांक64_t);
		पूर्ण

		r = btree_lookup_raw(&spine, root, keys[level],
				     lower_bound, &rkey,
				     value_p, size);

		अगर (!r) अणु
			अगर (rkey != keys[level]) अणु
				निकास_ro_spine(&spine);
				वापस -ENODATA;
			पूर्ण
		पूर्ण अन्यथा अणु
			निकास_ro_spine(&spine);
			वापस r;
		पूर्ण

		root = le64_to_cpu(पूर्णांकernal_value_le);
	पूर्ण
	निकास_ro_spine(&spine);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_lookup);

अटल पूर्णांक dm_btree_lookup_next_single(काष्ठा dm_btree_info *info, dm_block_t root,
				       uपूर्णांक64_t key, uपूर्णांक64_t *rkey, व्योम *value_le)
अणु
	पूर्णांक r, i;
	uपूर्णांक32_t flags, nr_entries;
	काष्ठा dm_block *node;
	काष्ठा btree_node *n;

	r = bn_पढ़ो_lock(info, root, &node);
	अगर (r)
		वापस r;

	n = dm_block_data(node);
	flags = le32_to_cpu(n->header.flags);
	nr_entries = le32_to_cpu(n->header.nr_entries);

	अगर (flags & INTERNAL_NODE) अणु
		i = lower_bound(n, key);
		अगर (i < 0) अणु
			/*
			 * aव्योम early -ENODATA वापस when all entries are
			 * higher than the search @key.
			 */
			i = 0;
		पूर्ण
		अगर (i >= nr_entries) अणु
			r = -ENODATA;
			जाओ out;
		पूर्ण

		r = dm_btree_lookup_next_single(info, value64(n, i), key, rkey, value_le);
		अगर (r == -ENODATA && i < (nr_entries - 1)) अणु
			i++;
			r = dm_btree_lookup_next_single(info, value64(n, i), key, rkey, value_le);
		पूर्ण

	पूर्ण अन्यथा अणु
		i = upper_bound(n, key);
		अगर (i < 0 || i >= nr_entries) अणु
			r = -ENODATA;
			जाओ out;
		पूर्ण

		*rkey = le64_to_cpu(n->keys[i]);
		स_नकल(value_le, value_ptr(n, i), info->value_type.size);
	पूर्ण
out:
	dm_पंचांग_unlock(info->पंचांग, node);
	वापस r;
पूर्ण

पूर्णांक dm_btree_lookup_next(काष्ठा dm_btree_info *info, dm_block_t root,
			 uपूर्णांक64_t *keys, uपूर्णांक64_t *rkey, व्योम *value_le)
अणु
	अचिन्हित level;
	पूर्णांक r = -ENODATA;
	__le64 पूर्णांकernal_value_le;
	काष्ठा ro_spine spine;

	init_ro_spine(&spine, info);
	क्रम (level = 0; level < info->levels - 1u; level++) अणु
		r = btree_lookup_raw(&spine, root, keys[level],
				     lower_bound, rkey,
				     &पूर्णांकernal_value_le, माप(uपूर्णांक64_t));
		अगर (r)
			जाओ out;

		अगर (*rkey != keys[level]) अणु
			r = -ENODATA;
			जाओ out;
		पूर्ण

		root = le64_to_cpu(पूर्णांकernal_value_le);
	पूर्ण

	r = dm_btree_lookup_next_single(info, root, keys[level], rkey, value_le);
out:
	निकास_ro_spine(&spine);
	वापस r;
पूर्ण

EXPORT_SYMBOL_GPL(dm_btree_lookup_next);

/*
 * Splits a node by creating a sibling node and shअगरting half the nodes
 * contents across.  Assumes there is a parent node, and it has room क्रम
 * another child.
 *
 * Beक्रमe:
 *	  +--------+
 *	  | Parent |
 *	  +--------+
 *	     |
 *	     v
 *	+----------+
 *	| A ++++++ |
 *	+----------+
 *
 *
 * After:
 *		+--------+
 *		| Parent |
 *		+--------+
 *		  |	|
 *		  v	+------+
 *	    +---------+	       |
 *	    | A* +++  |	       v
 *	    +---------+	  +-------+
 *			  | B +++ |
 *			  +-------+
 *
 * Where A* is a shaकरोw of A.
 */
अटल पूर्णांक btree_split_sibling(काष्ठा shaकरोw_spine *s, अचिन्हित parent_index,
			       uपूर्णांक64_t key)
अणु
	पूर्णांक r;
	माप_प्रकार size;
	अचिन्हित nr_left, nr_right;
	काष्ठा dm_block *left, *right, *parent;
	काष्ठा btree_node *ln, *rn, *pn;
	__le64 location;

	left = shaकरोw_current(s);

	r = new_block(s->info, &right);
	अगर (r < 0)
		वापस r;

	ln = dm_block_data(left);
	rn = dm_block_data(right);

	nr_left = le32_to_cpu(ln->header.nr_entries) / 2;
	nr_right = le32_to_cpu(ln->header.nr_entries) - nr_left;

	ln->header.nr_entries = cpu_to_le32(nr_left);

	rn->header.flags = ln->header.flags;
	rn->header.nr_entries = cpu_to_le32(nr_right);
	rn->header.max_entries = ln->header.max_entries;
	rn->header.value_size = ln->header.value_size;
	स_नकल(rn->keys, ln->keys + nr_left, nr_right * माप(rn->keys[0]));

	size = le32_to_cpu(ln->header.flags) & INTERNAL_NODE ?
		माप(uपूर्णांक64_t) : s->info->value_type.size;
	स_नकल(value_ptr(rn, 0), value_ptr(ln, nr_left),
	       size * nr_right);

	/*
	 * Patch up the parent
	 */
	parent = shaकरोw_parent(s);

	pn = dm_block_data(parent);
	location = cpu_to_le64(dm_block_location(left));
	__dm_bless_क्रम_disk(&location);
	स_नकल_disk(value_ptr(pn, parent_index),
		    &location, माप(__le64));

	location = cpu_to_le64(dm_block_location(right));
	__dm_bless_क्रम_disk(&location);

	r = insert_at(माप(__le64), pn, parent_index + 1,
		      le64_to_cpu(rn->keys[0]), &location);
	अगर (r) अणु
		unlock_block(s->info, right);
		वापस r;
	पूर्ण

	अगर (key < le64_to_cpu(rn->keys[0])) अणु
		unlock_block(s->info, right);
		s->nodes[1] = left;
	पूर्ण अन्यथा अणु
		unlock_block(s->info, left);
		s->nodes[1] = right;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Splits a node by creating two new children beneath the given node.
 *
 * Beक्रमe:
 *	  +----------+
 *	  | A ++++++ |
 *	  +----------+
 *
 *
 * After:
 *	+------------+
 *	| A (shaकरोw) |
 *	+------------+
 *	    |	|
 *   +------+	+----+
 *   |		     |
 *   v		     v
 * +-------+	 +-------+
 * | B +++ |	 | C +++ |
 * +-------+	 +-------+
 */
अटल पूर्णांक btree_split_beneath(काष्ठा shaकरोw_spine *s, uपूर्णांक64_t key)
अणु
	पूर्णांक r;
	माप_प्रकार size;
	अचिन्हित nr_left, nr_right;
	काष्ठा dm_block *left, *right, *new_parent;
	काष्ठा btree_node *pn, *ln, *rn;
	__le64 val;

	new_parent = shaकरोw_current(s);

	pn = dm_block_data(new_parent);
	size = le32_to_cpu(pn->header.flags) & INTERNAL_NODE ?
		माप(__le64) : s->info->value_type.size;

	/* create & init the left block */
	r = new_block(s->info, &left);
	अगर (r < 0)
		वापस r;

	ln = dm_block_data(left);
	nr_left = le32_to_cpu(pn->header.nr_entries) / 2;

	ln->header.flags = pn->header.flags;
	ln->header.nr_entries = cpu_to_le32(nr_left);
	ln->header.max_entries = pn->header.max_entries;
	ln->header.value_size = pn->header.value_size;
	स_नकल(ln->keys, pn->keys, nr_left * माप(pn->keys[0]));
	स_नकल(value_ptr(ln, 0), value_ptr(pn, 0), nr_left * size);

	/* create & init the right block */
	r = new_block(s->info, &right);
	अगर (r < 0) अणु
		unlock_block(s->info, left);
		वापस r;
	पूर्ण

	rn = dm_block_data(right);
	nr_right = le32_to_cpu(pn->header.nr_entries) - nr_left;

	rn->header.flags = pn->header.flags;
	rn->header.nr_entries = cpu_to_le32(nr_right);
	rn->header.max_entries = pn->header.max_entries;
	rn->header.value_size = pn->header.value_size;
	स_नकल(rn->keys, pn->keys + nr_left, nr_right * माप(pn->keys[0]));
	स_नकल(value_ptr(rn, 0), value_ptr(pn, nr_left),
	       nr_right * size);

	/* new_parent should just poपूर्णांक to l and r now */
	pn->header.flags = cpu_to_le32(INTERNAL_NODE);
	pn->header.nr_entries = cpu_to_le32(2);
	pn->header.max_entries = cpu_to_le32(
		calc_max_entries(माप(__le64),
				 dm_bm_block_size(
					 dm_पंचांग_get_bm(s->info->पंचांग))));
	pn->header.value_size = cpu_to_le32(माप(__le64));

	val = cpu_to_le64(dm_block_location(left));
	__dm_bless_क्रम_disk(&val);
	pn->keys[0] = ln->keys[0];
	स_नकल_disk(value_ptr(pn, 0), &val, माप(__le64));

	val = cpu_to_le64(dm_block_location(right));
	__dm_bless_क्रम_disk(&val);
	pn->keys[1] = rn->keys[0];
	स_नकल_disk(value_ptr(pn, 1), &val, माप(__le64));

	unlock_block(s->info, left);
	unlock_block(s->info, right);
	वापस 0;
पूर्ण

अटल पूर्णांक btree_insert_raw(काष्ठा shaकरोw_spine *s, dm_block_t root,
			    काष्ठा dm_btree_value_type *vt,
			    uपूर्णांक64_t key, अचिन्हित *index)
अणु
	पूर्णांक r, i = *index, top = 1;
	काष्ठा btree_node *node;

	क्रम (;;) अणु
		r = shaकरोw_step(s, root, vt);
		अगर (r < 0)
			वापस r;

		node = dm_block_data(shaकरोw_current(s));

		/*
		 * We have to patch up the parent node, ugly, but I करोn't
		 * see a way to करो this स्वतःmatically as part of the spine
		 * op.
		 */
		अगर (shaकरोw_has_parent(s) && i >= 0) अणु /* FIXME: second clause unness. */
			__le64 location = cpu_to_le64(dm_block_location(shaकरोw_current(s)));

			__dm_bless_क्रम_disk(&location);
			स_नकल_disk(value_ptr(dm_block_data(shaकरोw_parent(s)), i),
				    &location, माप(__le64));
		पूर्ण

		node = dm_block_data(shaकरोw_current(s));

		अगर (node->header.nr_entries == node->header.max_entries) अणु
			अगर (top)
				r = btree_split_beneath(s, key);
			अन्यथा
				r = btree_split_sibling(s, i, key);

			अगर (r < 0)
				वापस r;
		पूर्ण

		node = dm_block_data(shaकरोw_current(s));

		i = lower_bound(node, key);

		अगर (le32_to_cpu(node->header.flags) & LEAF_NODE)
			अवरोध;

		अगर (i < 0) अणु
			/* change the bounds on the lowest key */
			node->keys[0] = cpu_to_le64(key);
			i = 0;
		पूर्ण

		root = value64(node, i);
		top = 0;
	पूर्ण

	अगर (i < 0 || le64_to_cpu(node->keys[i]) != key)
		i++;

	*index = i;
	वापस 0;
पूर्ण

अटल bool need_insert(काष्ठा btree_node *node, uपूर्णांक64_t *keys,
			अचिन्हित level, अचिन्हित index)
अणु
        वापस ((index >= le32_to_cpu(node->header.nr_entries)) ||
		(le64_to_cpu(node->keys[index]) != keys[level]));
पूर्ण

अटल पूर्णांक insert(काष्ठा dm_btree_info *info, dm_block_t root,
		  uपूर्णांक64_t *keys, व्योम *value, dm_block_t *new_root,
		  पूर्णांक *inserted)
		  __dm_written_to_disk(value)
अणु
	पूर्णांक r;
	अचिन्हित level, index = -1, last_level = info->levels - 1;
	dm_block_t block = root;
	काष्ठा shaकरोw_spine spine;
	काष्ठा btree_node *n;
	काष्ठा dm_btree_value_type le64_type;

	init_le64_type(info->पंचांग, &le64_type);
	init_shaकरोw_spine(&spine, info);

	क्रम (level = 0; level < (info->levels - 1); level++) अणु
		r = btree_insert_raw(&spine, block, &le64_type, keys[level], &index);
		अगर (r < 0)
			जाओ bad;

		n = dm_block_data(shaकरोw_current(&spine));

		अगर (need_insert(n, keys, level, index)) अणु
			dm_block_t new_tree;
			__le64 new_le;

			r = dm_btree_empty(info, &new_tree);
			अगर (r < 0)
				जाओ bad;

			new_le = cpu_to_le64(new_tree);
			__dm_bless_क्रम_disk(&new_le);

			r = insert_at(माप(uपूर्णांक64_t), n, index,
				      keys[level], &new_le);
			अगर (r)
				जाओ bad;
		पूर्ण

		अगर (level < last_level)
			block = value64(n, index);
	पूर्ण

	r = btree_insert_raw(&spine, block, &info->value_type,
			     keys[level], &index);
	अगर (r < 0)
		जाओ bad;

	n = dm_block_data(shaकरोw_current(&spine));

	अगर (need_insert(n, keys, level, index)) अणु
		अगर (inserted)
			*inserted = 1;

		r = insert_at(info->value_type.size, n, index,
			      keys[level], value);
		अगर (r)
			जाओ bad_unblessed;
	पूर्ण अन्यथा अणु
		अगर (inserted)
			*inserted = 0;

		अगर (info->value_type.dec &&
		    (!info->value_type.equal ||
		     !info->value_type.equal(
			     info->value_type.context,
			     value_ptr(n, index),
			     value))) अणु
			info->value_type.dec(info->value_type.context,
					     value_ptr(n, index));
		पूर्ण
		स_नकल_disk(value_ptr(n, index),
			    value, info->value_type.size);
	पूर्ण

	*new_root = shaकरोw_root(&spine);
	निकास_shaकरोw_spine(&spine);

	वापस 0;

bad:
	__dm_unbless_क्रम_disk(value);
bad_unblessed:
	निकास_shaकरोw_spine(&spine);
	वापस r;
पूर्ण

पूर्णांक dm_btree_insert(काष्ठा dm_btree_info *info, dm_block_t root,
		    uपूर्णांक64_t *keys, व्योम *value, dm_block_t *new_root)
		    __dm_written_to_disk(value)
अणु
	वापस insert(info, root, keys, value, new_root, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_insert);

पूर्णांक dm_btree_insert_notअगरy(काष्ठा dm_btree_info *info, dm_block_t root,
			   uपूर्णांक64_t *keys, व्योम *value, dm_block_t *new_root,
			   पूर्णांक *inserted)
			   __dm_written_to_disk(value)
अणु
	वापस insert(info, root, keys, value, new_root, inserted);
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_insert_notअगरy);

/*----------------------------------------------------------------*/

अटल पूर्णांक find_key(काष्ठा ro_spine *s, dm_block_t block, bool find_highest,
		    uपूर्णांक64_t *result_key, dm_block_t *next_block)
अणु
	पूर्णांक i, r;
	uपूर्णांक32_t flags;

	करो अणु
		r = ro_step(s, block);
		अगर (r < 0)
			वापस r;

		flags = le32_to_cpu(ro_node(s)->header.flags);
		i = le32_to_cpu(ro_node(s)->header.nr_entries);
		अगर (!i)
			वापस -ENODATA;
		अन्यथा
			i--;

		अगर (find_highest)
			*result_key = le64_to_cpu(ro_node(s)->keys[i]);
		अन्यथा
			*result_key = le64_to_cpu(ro_node(s)->keys[0]);

		अगर (next_block || flags & INTERNAL_NODE) अणु
			अगर (find_highest)
				block = value64(ro_node(s), i);
			अन्यथा
				block = value64(ro_node(s), 0);
		पूर्ण

	पूर्ण जबतक (flags & INTERNAL_NODE);

	अगर (next_block)
		*next_block = block;
	वापस 0;
पूर्ण

अटल पूर्णांक dm_btree_find_key(काष्ठा dm_btree_info *info, dm_block_t root,
			     bool find_highest, uपूर्णांक64_t *result_keys)
अणु
	पूर्णांक r = 0, count = 0, level;
	काष्ठा ro_spine spine;

	init_ro_spine(&spine, info);
	क्रम (level = 0; level < info->levels; level++) अणु
		r = find_key(&spine, root, find_highest, result_keys + level,
			     level == info->levels - 1 ? शून्य : &root);
		अगर (r == -ENODATA) अणु
			r = 0;
			अवरोध;

		पूर्ण अन्यथा अगर (r)
			अवरोध;

		count++;
	पूर्ण
	निकास_ro_spine(&spine);

	वापस r ? r : count;
पूर्ण

पूर्णांक dm_btree_find_highest_key(काष्ठा dm_btree_info *info, dm_block_t root,
			      uपूर्णांक64_t *result_keys)
अणु
	वापस dm_btree_find_key(info, root, true, result_keys);
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_find_highest_key);

पूर्णांक dm_btree_find_lowest_key(काष्ठा dm_btree_info *info, dm_block_t root,
			     uपूर्णांक64_t *result_keys)
अणु
	वापस dm_btree_find_key(info, root, false, result_keys);
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_find_lowest_key);

/*----------------------------------------------------------------*/

/*
 * FIXME: We shouldn't use a recursive algorithm when we have limited stack
 * space.  Also this only works क्रम single level trees.
 */
अटल पूर्णांक walk_node(काष्ठा dm_btree_info *info, dm_block_t block,
		     पूर्णांक (*fn)(व्योम *context, uपूर्णांक64_t *keys, व्योम *leaf),
		     व्योम *context)
अणु
	पूर्णांक r;
	अचिन्हित i, nr;
	काष्ठा dm_block *node;
	काष्ठा btree_node *n;
	uपूर्णांक64_t keys;

	r = bn_पढ़ो_lock(info, block, &node);
	अगर (r)
		वापस r;

	n = dm_block_data(node);

	nr = le32_to_cpu(n->header.nr_entries);
	क्रम (i = 0; i < nr; i++) अणु
		अगर (le32_to_cpu(n->header.flags) & INTERNAL_NODE) अणु
			r = walk_node(info, value64(n, i), fn, context);
			अगर (r)
				जाओ out;
		पूर्ण अन्यथा अणु
			keys = le64_to_cpu(*key_ptr(n, i));
			r = fn(context, &keys, value_ptr(n, i));
			अगर (r)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	dm_पंचांग_unlock(info->पंचांग, node);
	वापस r;
पूर्ण

पूर्णांक dm_btree_walk(काष्ठा dm_btree_info *info, dm_block_t root,
		  पूर्णांक (*fn)(व्योम *context, uपूर्णांक64_t *keys, व्योम *leaf),
		  व्योम *context)
अणु
	BUG_ON(info->levels > 1);
	वापस walk_node(info, root, fn, context);
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_walk);

/*----------------------------------------------------------------*/

अटल व्योम prefetch_values(काष्ठा dm_btree_cursor *c)
अणु
	अचिन्हित i, nr;
	__le64 value_le;
	काष्ठा cursor_node *n = c->nodes + c->depth - 1;
	काष्ठा btree_node *bn = dm_block_data(n->b);
	काष्ठा dm_block_manager *bm = dm_पंचांग_get_bm(c->info->पंचांग);

	BUG_ON(c->info->value_type.size != माप(value_le));

	nr = le32_to_cpu(bn->header.nr_entries);
	क्रम (i = 0; i < nr; i++) अणु
		स_नकल(&value_le, value_ptr(bn, i), माप(value_le));
		dm_bm_prefetch(bm, le64_to_cpu(value_le));
	पूर्ण
पूर्ण

अटल bool leaf_node(काष्ठा dm_btree_cursor *c)
अणु
	काष्ठा cursor_node *n = c->nodes + c->depth - 1;
	काष्ठा btree_node *bn = dm_block_data(n->b);

	वापस le32_to_cpu(bn->header.flags) & LEAF_NODE;
पूर्ण

अटल पूर्णांक push_node(काष्ठा dm_btree_cursor *c, dm_block_t b)
अणु
	पूर्णांक r;
	काष्ठा cursor_node *n = c->nodes + c->depth;

	अगर (c->depth >= DM_BTREE_CURSOR_MAX_DEPTH - 1) अणु
		DMERR("couldn't push cursor node, stack depth too high");
		वापस -EINVAL;
	पूर्ण

	r = bn_पढ़ो_lock(c->info, b, &n->b);
	अगर (r)
		वापस r;

	n->index = 0;
	c->depth++;

	अगर (c->prefetch_leaves || !leaf_node(c))
		prefetch_values(c);

	वापस 0;
पूर्ण

अटल व्योम pop_node(काष्ठा dm_btree_cursor *c)
अणु
	c->depth--;
	unlock_block(c->info, c->nodes[c->depth].b);
पूर्ण

अटल पूर्णांक inc_or_backtrack(काष्ठा dm_btree_cursor *c)
अणु
	काष्ठा cursor_node *n;
	काष्ठा btree_node *bn;

	क्रम (;;) अणु
		अगर (!c->depth)
			वापस -ENODATA;

		n = c->nodes + c->depth - 1;
		bn = dm_block_data(n->b);

		n->index++;
		अगर (n->index < le32_to_cpu(bn->header.nr_entries))
			अवरोध;

		pop_node(c);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक find_leaf(काष्ठा dm_btree_cursor *c)
अणु
	पूर्णांक r = 0;
	काष्ठा cursor_node *n;
	काष्ठा btree_node *bn;
	__le64 value_le;

	क्रम (;;) अणु
		n = c->nodes + c->depth - 1;
		bn = dm_block_data(n->b);

		अगर (le32_to_cpu(bn->header.flags) & LEAF_NODE)
			अवरोध;

		स_नकल(&value_le, value_ptr(bn, n->index), माप(value_le));
		r = push_node(c, le64_to_cpu(value_le));
		अगर (r) अणु
			DMERR("push_node failed");
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!r && (le32_to_cpu(bn->header.nr_entries) == 0))
		वापस -ENODATA;

	वापस r;
पूर्ण

पूर्णांक dm_btree_cursor_begin(काष्ठा dm_btree_info *info, dm_block_t root,
			  bool prefetch_leaves, काष्ठा dm_btree_cursor *c)
अणु
	पूर्णांक r;

	c->info = info;
	c->root = root;
	c->depth = 0;
	c->prefetch_leaves = prefetch_leaves;

	r = push_node(c, root);
	अगर (r)
		वापस r;

	वापस find_leaf(c);
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_cursor_begin);

व्योम dm_btree_cursor_end(काष्ठा dm_btree_cursor *c)
अणु
	जबतक (c->depth)
		pop_node(c);
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_cursor_end);

पूर्णांक dm_btree_cursor_next(काष्ठा dm_btree_cursor *c)
अणु
	पूर्णांक r = inc_or_backtrack(c);
	अगर (!r) अणु
		r = find_leaf(c);
		अगर (r)
			DMERR("find_leaf failed");
	पूर्ण

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_cursor_next);

पूर्णांक dm_btree_cursor_skip(काष्ठा dm_btree_cursor *c, uपूर्णांक32_t count)
अणु
	पूर्णांक r = 0;

	जबतक (count-- && !r)
		r = dm_btree_cursor_next(c);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_cursor_skip);

पूर्णांक dm_btree_cursor_get_value(काष्ठा dm_btree_cursor *c, uपूर्णांक64_t *key, व्योम *value_le)
अणु
	अगर (c->depth) अणु
		काष्ठा cursor_node *n = c->nodes + c->depth - 1;
		काष्ठा btree_node *bn = dm_block_data(n->b);

		अगर (le32_to_cpu(bn->header.flags) & INTERNAL_NODE)
			वापस -EINVAL;

		*key = le64_to_cpu(*key_ptr(bn, n->index));
		स_नकल(value_le, value_ptr(bn, n->index), c->info->value_type.size);
		वापस 0;

	पूर्ण अन्यथा
		वापस -ENODATA;
पूर्ण
EXPORT_SYMBOL_GPL(dm_btree_cursor_get_value);
