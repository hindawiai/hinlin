<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Code क्रम working with inभागidual keys, and sorted sets of keys with in a
 * btree node
 *
 * Copyright 2012 Google, Inc.
 */

#घोषणा pr_fmt(fmt) "bcache: %s() " fmt, __func__

#समावेश "util.h"
#समावेश "bset.h"

#समावेश <linux/console.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/prefetch.h>

#अगर_घोषित CONFIG_BCACHE_DEBUG

व्योम bch_dump_bset(काष्ठा btree_keys *b, काष्ठा bset *i, अचिन्हित पूर्णांक set)
अणु
	काष्ठा bkey *k, *next;

	क्रम (k = i->start; k < bset_bkey_last(i); k = next) अणु
		next = bkey_next(k);

		pr_err("block %u key %u/%u: ", set,
		       (अचिन्हित पूर्णांक) ((u64 *) k - i->d), i->keys);

		अगर (b->ops->key_dump)
			b->ops->key_dump(b, k);
		अन्यथा
			pr_cont("%llu:%llu\n", KEY_INODE(k), KEY_OFFSET(k));

		अगर (next < bset_bkey_last(i) &&
		    bkey_cmp(k, b->ops->is_extents ?
			     &START_KEY(next) : next) > 0)
			pr_err("Key skipped backwards\n");
	पूर्ण
पूर्ण

व्योम bch_dump_bucket(काष्ठा btree_keys *b)
अणु
	अचिन्हित पूर्णांक i;

	console_lock();
	क्रम (i = 0; i <= b->nsets; i++)
		bch_dump_bset(b, b->set[i].data,
			      bset_sector_offset(b, b->set[i].data));
	console_unlock();
पूर्ण

पूर्णांक __bch_count_data(काष्ठा btree_keys *b)
अणु
	अचिन्हित पूर्णांक ret = 0;
	काष्ठा btree_iter iter;
	काष्ठा bkey *k;

	अगर (b->ops->is_extents)
		क्रम_each_key(b, k, &iter)
			ret += KEY_SIZE(k);
	वापस ret;
पूर्ण

व्योम __bch_check_keys(काष्ठा btree_keys *b, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	काष्ठा bkey *k, *p = शून्य;
	काष्ठा btree_iter iter;
	स्थिर अक्षर *err;

	क्रम_each_key(b, k, &iter) अणु
		अगर (b->ops->is_extents) अणु
			err = "Keys out of order";
			अगर (p && bkey_cmp(&START_KEY(p), &START_KEY(k)) > 0)
				जाओ bug;

			अगर (bch_ptr_invalid(b, k))
				जारी;

			err =  "Overlapping keys";
			अगर (p && bkey_cmp(p, &START_KEY(k)) > 0)
				जाओ bug;
		पूर्ण अन्यथा अणु
			अगर (bch_ptr_bad(b, k))
				जारी;

			err = "Duplicate keys";
			अगर (p && !bkey_cmp(p, k))
				जाओ bug;
		पूर्ण
		p = k;
	पूर्ण
#अगर 0
	err = "Key larger than btree node key";
	अगर (p && bkey_cmp(p, &b->key) > 0)
		जाओ bug;
#पूर्ण_अगर
	वापस;
bug:
	bch_dump_bucket(b);

	बहु_शुरू(args, fmt);
	vprपूर्णांकk(fmt, args);
	बहु_पूर्ण(args);

	panic("bch_check_keys error:  %s:\n", err);
पूर्ण

अटल व्योम bch_btree_iter_next_check(काष्ठा btree_iter *iter)
अणु
	काष्ठा bkey *k = iter->data->k, *next = bkey_next(k);

	अगर (next < iter->data->end &&
	    bkey_cmp(k, iter->b->ops->is_extents ?
		     &START_KEY(next) : next) > 0) अणु
		bch_dump_bucket(iter->b);
		panic("Key skipped backwards\n");
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम bch_btree_iter_next_check(काष्ठा btree_iter *iter) अणुपूर्ण

#पूर्ण_अगर

/* Keylists */

पूर्णांक __bch_keylist_पुनः_स्मृति(काष्ठा keylist *l, अचिन्हित पूर्णांक u64s)
अणु
	माप_प्रकार oldsize = bch_keylist_nkeys(l);
	माप_प्रकार newsize = oldsize + u64s;
	uपूर्णांक64_t *old_keys = l->keys_p == l->अंतरभूत_keys ? शून्य : l->keys_p;
	uपूर्णांक64_t *new_keys;

	newsize = roundup_घात_of_two(newsize);

	अगर (newsize <= KEYLIST_INLINE ||
	    roundup_घात_of_two(oldsize) == newsize)
		वापस 0;

	new_keys = kपुनः_स्मृति(old_keys, माप(uपूर्णांक64_t) * newsize, GFP_NOIO);

	अगर (!new_keys)
		वापस -ENOMEM;

	अगर (!old_keys)
		स_नकल(new_keys, l->अंतरभूत_keys, माप(uपूर्णांक64_t) * oldsize);

	l->keys_p = new_keys;
	l->top_p = new_keys + oldsize;

	वापस 0;
पूर्ण

/* Pop the top key of keylist by poपूर्णांकing l->top to its previous key */
काष्ठा bkey *bch_keylist_pop(काष्ठा keylist *l)
अणु
	काष्ठा bkey *k = l->keys;

	अगर (k == l->top)
		वापस शून्य;

	जबतक (bkey_next(k) != l->top)
		k = bkey_next(k);

	वापस l->top = k;
पूर्ण

/* Pop the bottom key of keylist and update l->top_p */
व्योम bch_keylist_pop_front(काष्ठा keylist *l)
अणु
	l->top_p -= bkey_u64s(l->keys);

	स_हटाओ(l->keys,
		bkey_next(l->keys),
		bch_keylist_bytes(l));
पूर्ण

/* Key/poपूर्णांकer manipulation */

व्योम bch_bkey_copy_single_ptr(काष्ठा bkey *dest, स्थिर काष्ठा bkey *src,
			      अचिन्हित पूर्णांक i)
अणु
	BUG_ON(i > KEY_PTRS(src));

	/* Only copy the header, key, and one poपूर्णांकer. */
	स_नकल(dest, src, 2 * माप(uपूर्णांक64_t));
	dest->ptr[0] = src->ptr[i];
	SET_KEY_PTRS(dest, 1);
	/* We didn't copy the checksum so clear that bit. */
	SET_KEY_CSUM(dest, 0);
पूर्ण

bool __bch_cut_front(स्थिर काष्ठा bkey *where, काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i, len = 0;

	अगर (bkey_cmp(where, &START_KEY(k)) <= 0)
		वापस false;

	अगर (bkey_cmp(where, k) < 0)
		len = KEY_OFFSET(k) - KEY_OFFSET(where);
	अन्यथा
		bkey_copy_key(k, where);

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		SET_PTR_OFFSET(k, i, PTR_OFFSET(k, i) + KEY_SIZE(k) - len);

	BUG_ON(len > KEY_SIZE(k));
	SET_KEY_SIZE(k, len);
	वापस true;
पूर्ण

bool __bch_cut_back(स्थिर काष्ठा bkey *where, काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक len = 0;

	अगर (bkey_cmp(where, k) >= 0)
		वापस false;

	BUG_ON(KEY_INODE(where) != KEY_INODE(k));

	अगर (bkey_cmp(where, &START_KEY(k)) > 0)
		len = KEY_OFFSET(where) - KEY_START(k);

	bkey_copy_key(k, where);

	BUG_ON(len > KEY_SIZE(k));
	SET_KEY_SIZE(k, len);
	वापस true;
पूर्ण

/* Auxiliary search trees */

/* 32 bits total: */
#घोषणा BKEY_MID_BITS		3
#घोषणा BKEY_EXPONENT_BITS	7
#घोषणा BKEY_MANTISSA_BITS	(32 - BKEY_MID_BITS - BKEY_EXPONENT_BITS)
#घोषणा BKEY_MANTISSA_MASK	((1 << BKEY_MANTISSA_BITS) - 1)

काष्ठा bkey_भग्न अणु
	अचिन्हित पूर्णांक	exponent:BKEY_EXPONENT_BITS;
	अचिन्हित पूर्णांक	m:BKEY_MID_BITS;
	अचिन्हित पूर्णांक	mantissa:BKEY_MANTISSA_BITS;
पूर्ण __packed;

/*
 * BSET_CACHELINE was originally पूर्णांकended to match the hardware cacheline size -
 * it used to be 64, but I realized the lookup code would touch slightly less
 * memory अगर it was 128.
 *
 * It definites the number of bytes (in काष्ठा bset) per काष्ठा bkey_भग्न in
 * the auxiliar search tree - when we're करोne searching the bset_भग्न tree we
 * have this many bytes left that we करो a linear search over.
 *
 * Since (after level 5) every level of the bset_tree is on a new cacheline,
 * we're touching one fewer cacheline in the bset tree in exchange क्रम one more
 * cacheline in the linear search - but the linear search might stop beक्रमe it
 * माला_लो to the second cacheline.
 */

#घोषणा BSET_CACHELINE		128

/* Space required क्रम the btree node keys */
अटल अंतरभूत माप_प्रकार btree_keys_bytes(काष्ठा btree_keys *b)
अणु
	वापस PAGE_SIZE << b->page_order;
पूर्ण

अटल अंतरभूत माप_प्रकार btree_keys_cachelines(काष्ठा btree_keys *b)
अणु
	वापस btree_keys_bytes(b) / BSET_CACHELINE;
पूर्ण

/* Space required क्रम the auxiliary search trees */
अटल अंतरभूत माप_प्रकार bset_tree_bytes(काष्ठा btree_keys *b)
अणु
	वापस btree_keys_cachelines(b) * माप(काष्ठा bkey_भग्न);
पूर्ण

/* Space required क्रम the prev poपूर्णांकers */
अटल अंतरभूत माप_प्रकार bset_prev_bytes(काष्ठा btree_keys *b)
अणु
	वापस btree_keys_cachelines(b) * माप(uपूर्णांक8_t);
पूर्ण

/* Memory allocation */

व्योम bch_btree_keys_मुक्त(काष्ठा btree_keys *b)
अणु
	काष्ठा bset_tree *t = b->set;

	अगर (bset_prev_bytes(b) < PAGE_SIZE)
		kमुक्त(t->prev);
	अन्यथा
		मुक्त_pages((अचिन्हित दीर्घ) t->prev,
			   get_order(bset_prev_bytes(b)));

	अगर (bset_tree_bytes(b) < PAGE_SIZE)
		kमुक्त(t->tree);
	अन्यथा
		मुक्त_pages((अचिन्हित दीर्घ) t->tree,
			   get_order(bset_tree_bytes(b)));

	मुक्त_pages((अचिन्हित दीर्घ) t->data, b->page_order);

	t->prev = शून्य;
	t->tree = शून्य;
	t->data = शून्य;
पूर्ण

पूर्णांक bch_btree_keys_alloc(काष्ठा btree_keys *b,
			 अचिन्हित पूर्णांक page_order,
			 gfp_t gfp)
अणु
	काष्ठा bset_tree *t = b->set;

	BUG_ON(t->data);

	b->page_order = page_order;

	t->data = (व्योम *) __get_मुक्त_pages(__GFP_COMP|gfp, b->page_order);
	अगर (!t->data)
		जाओ err;

	t->tree = bset_tree_bytes(b) < PAGE_SIZE
		? kदो_स्मृति(bset_tree_bytes(b), gfp)
		: (व्योम *) __get_मुक्त_pages(gfp, get_order(bset_tree_bytes(b)));
	अगर (!t->tree)
		जाओ err;

	t->prev = bset_prev_bytes(b) < PAGE_SIZE
		? kदो_स्मृति(bset_prev_bytes(b), gfp)
		: (व्योम *) __get_मुक्त_pages(gfp, get_order(bset_prev_bytes(b)));
	अगर (!t->prev)
		जाओ err;

	वापस 0;
err:
	bch_btree_keys_मुक्त(b);
	वापस -ENOMEM;
पूर्ण

व्योम bch_btree_keys_init(काष्ठा btree_keys *b, स्थिर काष्ठा btree_keys_ops *ops,
			 bool *expensive_debug_checks)
अणु
	b->ops = ops;
	b->expensive_debug_checks = expensive_debug_checks;
	b->nsets = 0;
	b->last_set_unwritten = 0;

	/*
	 * काष्ठा btree_keys in embedded in काष्ठा btree, and काष्ठा
	 * bset_tree is embedded पूर्णांकo काष्ठा btree_keys. They are all
	 * initialized as 0 by kzalloc() in mca_bucket_alloc(), and
	 * b->set[0].data is allocated in bch_btree_keys_alloc(), so we
	 * करोn't have to initiate b->set[].size and b->set[].data here
	 * any more.
	 */
पूर्ण

/* Binary tree stuff क्रम auxiliary search trees */

/*
 * वापस array index next to j when करोes in-order traverse
 * of a binary tree which is stored in a linear array
 */
अटल अचिन्हित पूर्णांक inorder_next(अचिन्हित पूर्णांक j, अचिन्हित पूर्णांक size)
अणु
	अगर (j * 2 + 1 < size) अणु
		j = j * 2 + 1;

		जबतक (j * 2 < size)
			j *= 2;
	पूर्ण अन्यथा
		j >>= ffz(j) + 1;

	वापस j;
पूर्ण

/*
 * वापस array index previous to j when करोes in-order traverse
 * of a binary tree which is stored in a linear array
 */
अटल अचिन्हित पूर्णांक inorder_prev(अचिन्हित पूर्णांक j, अचिन्हित पूर्णांक size)
अणु
	अगर (j * 2 < size) अणु
		j = j * 2;

		जबतक (j * 2 + 1 < size)
			j = j * 2 + 1;
	पूर्ण अन्यथा
		j >>= ffs(j);

	वापस j;
पूर्ण

/*
 * I have no idea why this code works... and I'm the one who wrote it
 *
 * However, I करो know what it करोes:
 * Given a binary tree स्थिरructed in an array (i.e. how you normally implement
 * a heap), it converts a node in the tree - referenced by array index - to the
 * index it would have अगर you did an inorder traversal.
 *
 * Also tested क्रम every j, size up to size somewhere around 6 million.
 *
 * The binary tree starts at array index 1, not 0
 * extra is a function of size:
 *   extra = (size - roundकरोwn_घात_of_two(size - 1)) << 1;
 */
अटल अचिन्हित पूर्णांक __to_inorder(अचिन्हित पूर्णांक j,
				  अचिन्हित पूर्णांक size,
				  अचिन्हित पूर्णांक extra)
अणु
	अचिन्हित पूर्णांक b = fls(j);
	अचिन्हित पूर्णांक shअगरt = fls(size - 1) - b;

	j  ^= 1U << (b - 1);
	j <<= 1;
	j  |= 1;
	j <<= shअगरt;

	अगर (j > extra)
		j -= (j - extra) >> 1;

	वापस j;
पूर्ण

/*
 * Return the cacheline index in bset_tree->data, where j is index
 * from a linear array which stores the auxiliar binary tree
 */
अटल अचिन्हित पूर्णांक to_inorder(अचिन्हित पूर्णांक j, काष्ठा bset_tree *t)
अणु
	वापस __to_inorder(j, t->size, t->extra);
पूर्ण

अटल अचिन्हित पूर्णांक __inorder_to_tree(अचिन्हित पूर्णांक j,
				      अचिन्हित पूर्णांक size,
				      अचिन्हित पूर्णांक extra)
अणु
	अचिन्हित पूर्णांक shअगरt;

	अगर (j > extra)
		j += j - extra;

	shअगरt = ffs(j);

	j >>= shअगरt;
	j  |= roundup_घात_of_two(size) >> shअगरt;

	वापस j;
पूर्ण

/*
 * Return an index from a linear array which stores the auxiliar binary
 * tree, j is the cacheline index of t->data.
 */
अटल अचिन्हित पूर्णांक inorder_to_tree(अचिन्हित पूर्णांक j, काष्ठा bset_tree *t)
अणु
	वापस __inorder_to_tree(j, t->size, t->extra);
पूर्ण

#अगर 0
व्योम inorder_test(व्योम)
अणु
	अचिन्हित दीर्घ करोne = 0;
	kसमय_प्रकार start = kसमय_get();

	क्रम (अचिन्हित पूर्णांक size = 2;
	     size < 65536000;
	     size++) अणु
		अचिन्हित पूर्णांक extra =
			(size - roundकरोwn_घात_of_two(size - 1)) << 1;
		अचिन्हित पूर्णांक i = 1, j = roundकरोwn_घात_of_two(size - 1);

		अगर (!(size % 4096))
			pr_notice("loop %u, %llu per us\n", size,
			       करोne / kसमय_us_delta(kसमय_get(), start));

		जबतक (1) अणु
			अगर (__inorder_to_tree(i, size, extra) != j)
				panic("size %10u j %10u i %10u", size, j, i);

			अगर (__to_inorder(j, size, extra) != i)
				panic("size %10u j %10u i %10u", size, j, i);

			अगर (j == roundकरोwn_घात_of_two(size) - 1)
				अवरोध;

			BUG_ON(inorder_prev(inorder_next(j, size), size) != j);

			j = inorder_next(j, size);
			i++;
		पूर्ण

		करोne += size - 1;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * Cacheline/offset <-> bkey poपूर्णांकer arithmetic:
 *
 * t->tree is a binary search tree in an array; each node corresponds to a key
 * in one cacheline in t->set (BSET_CACHELINE bytes).
 *
 * This means we करोn't have to store the full index of the key that a node in
 * the binary tree poपूर्णांकs to; to_inorder() gives us the cacheline, and then
 * bkey_भग्न->m gives us the offset within that cacheline, in units of 8 bytes.
 *
 * cacheline_to_bkey() and मित्रs असलtract out all the poपूर्णांकer arithmetic to
 * make this work.
 *
 * To स्थिरruct the bभग्न क्रम an arbitrary key we need to know what the key
 * immediately preceding it is: we have to check अगर the two keys dअगरfer in the
 * bits we're going to store in bkey_भग्न->mantissa. t->prev[j] stores the size
 * of the previous key so we can walk backwards to it from t->tree[j]'s key.
 */

अटल काष्ठा bkey *cacheline_to_bkey(काष्ठा bset_tree *t,
				      अचिन्हित पूर्णांक cacheline,
				      अचिन्हित पूर्णांक offset)
अणु
	वापस ((व्योम *) t->data) + cacheline * BSET_CACHELINE + offset * 8;
पूर्ण

अटल अचिन्हित पूर्णांक bkey_to_cacheline(काष्ठा bset_tree *t, काष्ठा bkey *k)
अणु
	वापस ((व्योम *) k - (व्योम *) t->data) / BSET_CACHELINE;
पूर्ण

अटल अचिन्हित पूर्णांक bkey_to_cacheline_offset(काष्ठा bset_tree *t,
					 अचिन्हित पूर्णांक cacheline,
					 काष्ठा bkey *k)
अणु
	वापस (u64 *) k - (u64 *) cacheline_to_bkey(t, cacheline, 0);
पूर्ण

अटल काष्ठा bkey *tree_to_bkey(काष्ठा bset_tree *t, अचिन्हित पूर्णांक j)
अणु
	वापस cacheline_to_bkey(t, to_inorder(j, t), t->tree[j].m);
पूर्ण

अटल काष्ठा bkey *tree_to_prev_bkey(काष्ठा bset_tree *t, अचिन्हित पूर्णांक j)
अणु
	वापस (व्योम *) (((uपूर्णांक64_t *) tree_to_bkey(t, j)) - t->prev[j]);
पूर्ण

/*
 * For the ग_लिखो set - the one we're currently inserting keys into - we don't
 * मुख्यtain a full search tree, we just keep a simple lookup table in t->prev.
 */
अटल काष्ठा bkey *table_to_bkey(काष्ठा bset_tree *t, अचिन्हित पूर्णांक cacheline)
अणु
	वापस cacheline_to_bkey(t, cacheline, t->prev[cacheline]);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t shrd128(uपूर्णांक64_t high, uपूर्णांक64_t low, uपूर्णांक8_t shअगरt)
अणु
	low >>= shअगरt;
	low  |= (high << 1) << (63U - shअगरt);
	वापस low;
पूर्ण

/*
 * Calculate mantissa value क्रम काष्ठा bkey_भग्न.
 * If most signअगरicant bit of f->exponent is not set, then
 *  - f->exponent >> 6 is 0
 *  - p[0] poपूर्णांकs to bkey->low
 *  - p[-1] borrows bits from KEY_INODE() of bkey->high
 * अगर most isgnअगरicant bits of f->exponent is set, then
 *  - f->exponent >> 6 is 1
 *  - p[0] poपूर्णांकs to bits from KEY_INODE() of bkey->high
 *  - p[-1] poपूर्णांकs to other bits from KEY_INODE() of
 *    bkey->high too.
 * See make_bभग्न() to check when most signअगरicant bit of f->exponent
 * is set or not.
 */
अटल अंतरभूत अचिन्हित पूर्णांक bभग्न_mantissa(स्थिर काष्ठा bkey *k,
				       काष्ठा bkey_भग्न *f)
अणु
	स्थिर uपूर्णांक64_t *p = &k->low - (f->exponent >> 6);

	वापस shrd128(p[-1], p[0], f->exponent & 63) & BKEY_MANTISSA_MASK;
पूर्ण

अटल व्योम make_bभग्न(काष्ठा bset_tree *t, अचिन्हित पूर्णांक j)
अणु
	काष्ठा bkey_भग्न *f = &t->tree[j];
	काष्ठा bkey *m = tree_to_bkey(t, j);
	काष्ठा bkey *p = tree_to_prev_bkey(t, j);

	काष्ठा bkey *l = is_घातer_of_2(j)
		? t->data->start
		: tree_to_prev_bkey(t, j >> ffs(j));

	काष्ठा bkey *r = is_घातer_of_2(j + 1)
		? bset_bkey_idx(t->data, t->data->keys - bkey_u64s(&t->end))
		: tree_to_bkey(t, j >> (ffz(j) + 1));

	BUG_ON(m < l || m > r);
	BUG_ON(bkey_next(p) != m);

	/*
	 * If l and r have dअगरferent KEY_INODE values (dअगरferent backing
	 * device), f->exponent records how many least signअगरicant bits
	 * are dअगरferent in KEY_INODE values and sets most signअगरicant
	 * bits to 1 (by +64).
	 * If l and r have same KEY_INODE value, f->exponent records
	 * how many dअगरferent bits in least signअगरicant bits of bkey->low.
	 * See bभग्न_mantiss() how the most signअगरicant bit of
	 * f->exponent is used to calculate bभग्न mantissa value.
	 */
	अगर (KEY_INODE(l) != KEY_INODE(r))
		f->exponent = fls64(KEY_INODE(r) ^ KEY_INODE(l)) + 64;
	अन्यथा
		f->exponent = fls64(r->low ^ l->low);

	f->exponent = max_t(पूर्णांक, f->exponent - BKEY_MANTISSA_BITS, 0);

	/*
	 * Setting f->exponent = 127 flags this node as failed, and causes the
	 * lookup code to fall back to comparing against the original key.
	 */

	अगर (bभग्न_mantissa(m, f) != bभग्न_mantissa(p, f))
		f->mantissa = bभग्न_mantissa(m, f) - 1;
	अन्यथा
		f->exponent = 127;
पूर्ण

अटल व्योम bset_alloc_tree(काष्ठा btree_keys *b, काष्ठा bset_tree *t)
अणु
	अगर (t != b->set) अणु
		अचिन्हित पूर्णांक j = roundup(t[-1].size,
				     64 / माप(काष्ठा bkey_भग्न));

		t->tree = t[-1].tree + j;
		t->prev = t[-1].prev + j;
	पूर्ण

	जबतक (t < b->set + MAX_BSETS)
		t++->size = 0;
पूर्ण

अटल व्योम bch_bset_build_unwritten_tree(काष्ठा btree_keys *b)
अणु
	काष्ठा bset_tree *t = bset_tree_last(b);

	BUG_ON(b->last_set_unwritten);
	b->last_set_unwritten = 1;

	bset_alloc_tree(b, t);

	अगर (t->tree != b->set->tree + btree_keys_cachelines(b)) अणु
		t->prev[0] = bkey_to_cacheline_offset(t, 0, t->data->start);
		t->size = 1;
	पूर्ण
पूर्ण

व्योम bch_bset_init_next(काष्ठा btree_keys *b, काष्ठा bset *i, uपूर्णांक64_t magic)
अणु
	अगर (i != b->set->data) अणु
		b->set[++b->nsets].data = i;
		i->seq = b->set->data->seq;
	पूर्ण अन्यथा
		get_अक्रमom_bytes(&i->seq, माप(uपूर्णांक64_t));

	i->magic	= magic;
	i->version	= 0;
	i->keys		= 0;

	bch_bset_build_unwritten_tree(b);
पूर्ण

/*
 * Build auxiliary binary tree 'struct bset_tree *t', this tree is used to
 * accelerate bkey search in a btree node (poपूर्णांकed by bset_tree->data in
 * memory). After search in the auxiliar tree by calling bset_search_tree(),
 * a काष्ठा bset_search_iter is वापसed which indicates range [l, r] from
 * bset_tree->data where the searching bkey might be inside. Then a followed
 * linear comparison करोes the exact search, see __bch_bset_search() क्रम how
 * the auxiliary tree is used.
 */
व्योम bch_bset_build_written_tree(काष्ठा btree_keys *b)
अणु
	काष्ठा bset_tree *t = bset_tree_last(b);
	काष्ठा bkey *prev = शून्य, *k = t->data->start;
	अचिन्हित पूर्णांक j, cacheline = 1;

	b->last_set_unwritten = 0;

	bset_alloc_tree(b, t);

	t->size = min_t(अचिन्हित पूर्णांक,
			bkey_to_cacheline(t, bset_bkey_last(t->data)),
			b->set->tree + btree_keys_cachelines(b) - t->tree);

	अगर (t->size < 2) अणु
		t->size = 0;
		वापस;
	पूर्ण

	t->extra = (t->size - roundकरोwn_घात_of_two(t->size - 1)) << 1;

	/* First we figure out where the first key in each cacheline is */
	क्रम (j = inorder_next(0, t->size);
	     j;
	     j = inorder_next(j, t->size)) अणु
		जबतक (bkey_to_cacheline(t, k) < cacheline) अणु
			prev = k;
			k = bkey_next(k);
		पूर्ण

		t->prev[j] = bkey_u64s(prev);
		t->tree[j].m = bkey_to_cacheline_offset(t, cacheline++, k);
	पूर्ण

	जबतक (bkey_next(k) != bset_bkey_last(t->data))
		k = bkey_next(k);

	t->end = *k;

	/* Then we build the tree */
	क्रम (j = inorder_next(0, t->size);
	     j;
	     j = inorder_next(j, t->size))
		make_bभग्न(t, j);
पूर्ण

/* Insert */

व्योम bch_bset_fix_invalidated_key(काष्ठा btree_keys *b, काष्ठा bkey *k)
अणु
	काष्ठा bset_tree *t;
	अचिन्हित पूर्णांक inorder, j = 1;

	क्रम (t = b->set; t <= bset_tree_last(b); t++)
		अगर (k < bset_bkey_last(t->data))
			जाओ found_set;

	BUG();
found_set:
	अगर (!t->size || !bset_written(b, t))
		वापस;

	inorder = bkey_to_cacheline(t, k);

	अगर (k == t->data->start)
		जाओ fix_left;

	अगर (bkey_next(k) == bset_bkey_last(t->data)) अणु
		t->end = *k;
		जाओ fix_right;
	पूर्ण

	j = inorder_to_tree(inorder, t);

	अगर (j &&
	    j < t->size &&
	    k == tree_to_bkey(t, j))
fix_left:	करो अणु
			make_bभग्न(t, j);
			j = j * 2;
		पूर्ण जबतक (j < t->size);

	j = inorder_to_tree(inorder + 1, t);

	अगर (j &&
	    j < t->size &&
	    k == tree_to_prev_bkey(t, j))
fix_right:	करो अणु
			make_bभग्न(t, j);
			j = j * 2 + 1;
		पूर्ण जबतक (j < t->size);
पूर्ण

अटल व्योम bch_bset_fix_lookup_table(काष्ठा btree_keys *b,
				      काष्ठा bset_tree *t,
				      काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक shअगरt = bkey_u64s(k);
	अचिन्हित पूर्णांक j = bkey_to_cacheline(t, k);

	/* We're getting called from btree_split() or btree_gc, just bail out */
	अगर (!t->size)
		वापस;

	/*
	 * k is the key we just inserted; we need to find the entry in the
	 * lookup table क्रम the first key that is strictly greater than k:
	 * it's either k's cacheline or the next one
	 */
	जबतक (j < t->size &&
	       table_to_bkey(t, j) <= k)
		j++;

	/*
	 * Adjust all the lookup table entries, and find a new key क्रम any that
	 * have gotten too big
	 */
	क्रम (; j < t->size; j++) अणु
		t->prev[j] += shअगरt;

		अगर (t->prev[j] > 7) अणु
			k = table_to_bkey(t, j - 1);

			जबतक (k < cacheline_to_bkey(t, j, 0))
				k = bkey_next(k);

			t->prev[j] = bkey_to_cacheline_offset(t, j, k);
		पूर्ण
	पूर्ण

	अगर (t->size == b->set->tree + btree_keys_cachelines(b) - t->tree)
		वापस;

	/* Possibly add a new entry to the end of the lookup table */

	क्रम (k = table_to_bkey(t, t->size - 1);
	     k != bset_bkey_last(t->data);
	     k = bkey_next(k))
		अगर (t->size == bkey_to_cacheline(t, k)) अणु
			t->prev[t->size] =
				bkey_to_cacheline_offset(t, t->size, k);
			t->size++;
		पूर्ण
पूर्ण

/*
 * Tries to merge l and r: l should be lower than r
 * Returns true अगर we were able to merge. If we did merge, l will be the merged
 * key, r will be untouched.
 */
bool bch_bkey_try_merge(काष्ठा btree_keys *b, काष्ठा bkey *l, काष्ठा bkey *r)
अणु
	अगर (!b->ops->key_merge)
		वापस false;

	/*
	 * Generic header checks
	 * Assumes left and right are in order
	 * Left and right must be exactly aligned
	 */
	अगर (!bch_bkey_equal_header(l, r) ||
	     bkey_cmp(l, &START_KEY(r)))
		वापस false;

	वापस b->ops->key_merge(b, l, r);
पूर्ण

व्योम bch_bset_insert(काष्ठा btree_keys *b, काष्ठा bkey *where,
		     काष्ठा bkey *insert)
अणु
	काष्ठा bset_tree *t = bset_tree_last(b);

	BUG_ON(!b->last_set_unwritten);
	BUG_ON(bset_byte_offset(b, t->data) +
	       __set_bytes(t->data, t->data->keys + bkey_u64s(insert)) >
	       PAGE_SIZE << b->page_order);

	स_हटाओ((uपूर्णांक64_t *) where + bkey_u64s(insert),
		where,
		(व्योम *) bset_bkey_last(t->data) - (व्योम *) where);

	t->data->keys += bkey_u64s(insert);
	bkey_copy(where, insert);
	bch_bset_fix_lookup_table(b, t, where);
पूर्ण

अचिन्हित पूर्णांक bch_btree_insert_key(काष्ठा btree_keys *b, काष्ठा bkey *k,
			      काष्ठा bkey *replace_key)
अणु
	अचिन्हित पूर्णांक status = BTREE_INSERT_STATUS_NO_INSERT;
	काष्ठा bset *i = bset_tree_last(b)->data;
	काष्ठा bkey *m, *prev = शून्य;
	काष्ठा btree_iter iter;
	काष्ठा bkey preceding_key_on_stack = ZERO_KEY;
	काष्ठा bkey *preceding_key_p = &preceding_key_on_stack;

	BUG_ON(b->ops->is_extents && !KEY_SIZE(k));

	/*
	 * If k has preceding key, preceding_key_p will be set to address
	 *  of k's preceding key; otherwise preceding_key_p will be set
	 * to शून्य inside preceding_key().
	 */
	अगर (b->ops->is_extents)
		preceding_key(&START_KEY(k), &preceding_key_p);
	अन्यथा
		preceding_key(k, &preceding_key_p);

	m = bch_btree_iter_init(b, &iter, preceding_key_p);

	अगर (b->ops->insert_fixup(b, k, &iter, replace_key))
		वापस status;

	status = BTREE_INSERT_STATUS_INSERT;

	जबतक (m != bset_bkey_last(i) &&
	       bkey_cmp(k, b->ops->is_extents ? &START_KEY(m) : m) > 0) अणु
		prev = m;
		m = bkey_next(m);
	पूर्ण

	/* prev is in the tree, अगर we merge we're करोne */
	status = BTREE_INSERT_STATUS_BACK_MERGE;
	अगर (prev &&
	    bch_bkey_try_merge(b, prev, k))
		जाओ merged;
#अगर 0
	status = BTREE_INSERT_STATUS_OVERWROTE;
	अगर (m != bset_bkey_last(i) &&
	    KEY_PTRS(m) == KEY_PTRS(k) && !KEY_SIZE(m))
		जाओ copy;
#पूर्ण_अगर
	status = BTREE_INSERT_STATUS_FRONT_MERGE;
	अगर (m != bset_bkey_last(i) &&
	    bch_bkey_try_merge(b, k, m))
		जाओ copy;

	bch_bset_insert(b, m, k);
copy:	bkey_copy(m, k);
merged:
	वापस status;
पूर्ण

/* Lookup */

काष्ठा bset_search_iter अणु
	काष्ठा bkey *l, *r;
पूर्ण;

अटल काष्ठा bset_search_iter bset_search_ग_लिखो_set(काष्ठा bset_tree *t,
						     स्थिर काष्ठा bkey *search)
अणु
	अचिन्हित पूर्णांक li = 0, ri = t->size;

	जबतक (li + 1 != ri) अणु
		अचिन्हित पूर्णांक m = (li + ri) >> 1;

		अगर (bkey_cmp(table_to_bkey(t, m), search) > 0)
			ri = m;
		अन्यथा
			li = m;
	पूर्ण

	वापस (काष्ठा bset_search_iter) अणु
		table_to_bkey(t, li),
		ri < t->size ? table_to_bkey(t, ri) : bset_bkey_last(t->data)
	पूर्ण;
पूर्ण

अटल काष्ठा bset_search_iter bset_search_tree(काष्ठा bset_tree *t,
						स्थिर काष्ठा bkey *search)
अणु
	काष्ठा bkey *l, *r;
	काष्ठा bkey_भग्न *f;
	अचिन्हित पूर्णांक inorder, j, n = 1;

	करो अणु
		अचिन्हित पूर्णांक p = n << 4;

		अगर (p < t->size)
			prefetch(&t->tree[p]);

		j = n;
		f = &t->tree[j];

		अगर (likely(f->exponent != 127)) अणु
			अगर (f->mantissa >= bभग्न_mantissa(search, f))
				n = j * 2;
			अन्यथा
				n = j * 2 + 1;
		पूर्ण अन्यथा अणु
			अगर (bkey_cmp(tree_to_bkey(t, j), search) > 0)
				n = j * 2;
			अन्यथा
				n = j * 2 + 1;
		पूर्ण
	पूर्ण जबतक (n < t->size);

	inorder = to_inorder(j, t);

	/*
	 * n would have been the node we recursed to - the low bit tells us अगर
	 * we recursed left or recursed right.
	 */
	अगर (n & 1) अणु
		l = cacheline_to_bkey(t, inorder, f->m);

		अगर (++inorder != t->size) अणु
			f = &t->tree[inorder_next(j, t->size)];
			r = cacheline_to_bkey(t, inorder, f->m);
		पूर्ण अन्यथा
			r = bset_bkey_last(t->data);
	पूर्ण अन्यथा अणु
		r = cacheline_to_bkey(t, inorder, f->m);

		अगर (--inorder) अणु
			f = &t->tree[inorder_prev(j, t->size)];
			l = cacheline_to_bkey(t, inorder, f->m);
		पूर्ण अन्यथा
			l = t->data->start;
	पूर्ण

	वापस (काष्ठा bset_search_iter) अणुl, rपूर्ण;
पूर्ण

काष्ठा bkey *__bch_bset_search(काष्ठा btree_keys *b, काष्ठा bset_tree *t,
			       स्थिर काष्ठा bkey *search)
अणु
	काष्ठा bset_search_iter i;

	/*
	 * First, we search क्रम a cacheline, then lastly we करो a linear search
	 * within that cacheline.
	 *
	 * To search क्रम the cacheline, there's three dअगरferent possibilities:
	 *  * The set is too small to have a search tree, so we just करो a linear
	 *    search over the whole set.
	 *  * The set is the one we're currently inserting पूर्णांकo; keeping a full
	 *    auxiliary search tree up to date would be too expensive, so we
	 *    use a much simpler lookup table to करो a binary search -
	 *    bset_search_ग_लिखो_set().
	 *  * Or we use the auxiliary search tree we स्थिरructed earlier -
	 *    bset_search_tree()
	 */

	अगर (unlikely(!t->size)) अणु
		i.l = t->data->start;
		i.r = bset_bkey_last(t->data);
	पूर्ण अन्यथा अगर (bset_written(b, t)) अणु
		/*
		 * Each node in the auxiliary search tree covers a certain range
		 * of bits, and keys above and below the set it covers might
		 * dअगरfer outside those bits - so we have to special हाल the
		 * start and end - handle that here:
		 */

		अगर (unlikely(bkey_cmp(search, &t->end) >= 0))
			वापस bset_bkey_last(t->data);

		अगर (unlikely(bkey_cmp(search, t->data->start) < 0))
			वापस t->data->start;

		i = bset_search_tree(t, search);
	पूर्ण अन्यथा अणु
		BUG_ON(!b->nsets &&
		       t->size < bkey_to_cacheline(t, bset_bkey_last(t->data)));

		i = bset_search_ग_लिखो_set(t, search);
	पूर्ण

	अगर (btree_keys_expensive_checks(b)) अणु
		BUG_ON(bset_written(b, t) &&
		       i.l != t->data->start &&
		       bkey_cmp(tree_to_prev_bkey(t,
			  inorder_to_tree(bkey_to_cacheline(t, i.l), t)),
				search) > 0);

		BUG_ON(i.r != bset_bkey_last(t->data) &&
		       bkey_cmp(i.r, search) <= 0);
	पूर्ण

	जबतक (likely(i.l != i.r) &&
	       bkey_cmp(i.l, search) <= 0)
		i.l = bkey_next(i.l);

	वापस i.l;
पूर्ण

/* Btree iterator */

प्रकार bool (btree_iter_cmp_fn)(काष्ठा btree_iter_set,
				 काष्ठा btree_iter_set);

अटल अंतरभूत bool btree_iter_cmp(काष्ठा btree_iter_set l,
				  काष्ठा btree_iter_set r)
अणु
	वापस bkey_cmp(l.k, r.k) > 0;
पूर्ण

अटल अंतरभूत bool btree_iter_end(काष्ठा btree_iter *iter)
अणु
	वापस !iter->used;
पूर्ण

व्योम bch_btree_iter_push(काष्ठा btree_iter *iter, काष्ठा bkey *k,
			 काष्ठा bkey *end)
अणु
	अगर (k != end)
		BUG_ON(!heap_add(iter,
				 ((काष्ठा btree_iter_set) अणु k, end पूर्ण),
				 btree_iter_cmp));
पूर्ण

अटल काष्ठा bkey *__bch_btree_iter_init(काष्ठा btree_keys *b,
					  काष्ठा btree_iter *iter,
					  काष्ठा bkey *search,
					  काष्ठा bset_tree *start)
अणु
	काष्ठा bkey *ret = शून्य;

	iter->size = ARRAY_SIZE(iter->data);
	iter->used = 0;

#अगर_घोषित CONFIG_BCACHE_DEBUG
	iter->b = b;
#पूर्ण_अगर

	क्रम (; start <= bset_tree_last(b); start++) अणु
		ret = bch_bset_search(b, start, search);
		bch_btree_iter_push(iter, ret, bset_bkey_last(start->data));
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा bkey *bch_btree_iter_init(काष्ठा btree_keys *b,
				 काष्ठा btree_iter *iter,
				 काष्ठा bkey *search)
अणु
	वापस __bch_btree_iter_init(b, iter, search, b->set);
पूर्ण

अटल अंतरभूत काष्ठा bkey *__bch_btree_iter_next(काष्ठा btree_iter *iter,
						 btree_iter_cmp_fn *cmp)
अणु
	काष्ठा btree_iter_set b __maybe_unused;
	काष्ठा bkey *ret = शून्य;

	अगर (!btree_iter_end(iter)) अणु
		bch_btree_iter_next_check(iter);

		ret = iter->data->k;
		iter->data->k = bkey_next(iter->data->k);

		अगर (iter->data->k > iter->data->end) अणु
			WARN_ONCE(1, "bset was corrupt!\n");
			iter->data->k = iter->data->end;
		पूर्ण

		अगर (iter->data->k == iter->data->end)
			heap_pop(iter, b, cmp);
		अन्यथा
			heap_sअगरt(iter, 0, cmp);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा bkey *bch_btree_iter_next(काष्ठा btree_iter *iter)
अणु
	वापस __bch_btree_iter_next(iter, btree_iter_cmp);

पूर्ण

काष्ठा bkey *bch_btree_iter_next_filter(काष्ठा btree_iter *iter,
					काष्ठा btree_keys *b, ptr_filter_fn fn)
अणु
	काष्ठा bkey *ret;

	करो अणु
		ret = bch_btree_iter_next(iter);
	पूर्ण जबतक (ret && fn(b, ret));

	वापस ret;
पूर्ण

/* Mergesort */

व्योम bch_bset_sort_state_मुक्त(काष्ठा bset_sort_state *state)
अणु
	mempool_निकास(&state->pool);
पूर्ण

पूर्णांक bch_bset_sort_state_init(काष्ठा bset_sort_state *state,
			     अचिन्हित पूर्णांक page_order)
अणु
	spin_lock_init(&state->समय.lock);

	state->page_order = page_order;
	state->crit_factor = पूर्णांक_वर्ग_मूल(1 << page_order);

	वापस mempool_init_page_pool(&state->pool, 1, page_order);
पूर्ण

अटल व्योम btree_mergesort(काष्ठा btree_keys *b, काष्ठा bset *out,
			    काष्ठा btree_iter *iter,
			    bool fixup, bool हटाओ_stale)
अणु
	पूर्णांक i;
	काष्ठा bkey *k, *last = शून्य;
	BKEY_PADDED(k) पंचांगp;
	bool (*bad)(काष्ठा btree_keys *, स्थिर काष्ठा bkey *) = हटाओ_stale
		? bch_ptr_bad
		: bch_ptr_invalid;

	/* Heapअगरy the iterator, using our comparison function */
	क्रम (i = iter->used / 2 - 1; i >= 0; --i)
		heap_sअगरt(iter, i, b->ops->sort_cmp);

	जबतक (!btree_iter_end(iter)) अणु
		अगर (b->ops->sort_fixup && fixup)
			k = b->ops->sort_fixup(iter, &पंचांगp.k);
		अन्यथा
			k = शून्य;

		अगर (!k)
			k = __bch_btree_iter_next(iter, b->ops->sort_cmp);

		अगर (bad(b, k))
			जारी;

		अगर (!last) अणु
			last = out->start;
			bkey_copy(last, k);
		पूर्ण अन्यथा अगर (!bch_bkey_try_merge(b, last, k)) अणु
			last = bkey_next(last);
			bkey_copy(last, k);
		पूर्ण
	पूर्ण

	out->keys = last ? (uपूर्णांक64_t *) bkey_next(last) - out->d : 0;

	pr_debug("sorted %i keys\n", out->keys);
पूर्ण

अटल व्योम __btree_sort(काष्ठा btree_keys *b, काष्ठा btree_iter *iter,
			 अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक order, bool fixup,
			 काष्ठा bset_sort_state *state)
अणु
	uपूर्णांक64_t start_समय;
	bool used_mempool = false;
	काष्ठा bset *out = (व्योम *) __get_मुक्त_pages(__GFP_NOWARN|GFP_NOWAIT,
						     order);
	अगर (!out) अणु
		काष्ठा page *outp;

		BUG_ON(order > state->page_order);

		outp = mempool_alloc(&state->pool, GFP_NOIO);
		out = page_address(outp);
		used_mempool = true;
		order = state->page_order;
	पूर्ण

	start_समय = local_घड़ी();

	btree_mergesort(b, out, iter, fixup, false);
	b->nsets = start;

	अगर (!start && order == b->page_order) अणु
		/*
		 * Our temporary buffer is the same size as the btree node's
		 * buffer, we can just swap buffers instead of करोing a big
		 * स_नकल()
		 *
		 * Don't worry event 'out' is allocated from mempool, it can
		 * still be swapped here. Because state->pool is a page mempool
		 * creaated by by mempool_init_page_pool(), which allocates
		 * pages by alloc_pages() indeed.
		 */

		out->magic	= b->set->data->magic;
		out->seq	= b->set->data->seq;
		out->version	= b->set->data->version;
		swap(out, b->set->data);
	पूर्ण अन्यथा अणु
		b->set[start].data->keys = out->keys;
		स_नकल(b->set[start].data->start, out->start,
		       (व्योम *) bset_bkey_last(out) - (व्योम *) out->start);
	पूर्ण

	अगर (used_mempool)
		mempool_मुक्त(virt_to_page(out), &state->pool);
	अन्यथा
		मुक्त_pages((अचिन्हित दीर्घ) out, order);

	bch_bset_build_written_tree(b);

	अगर (!start)
		bch_समय_stats_update(&state->समय, start_समय);
पूर्ण

व्योम bch_btree_sort_partial(काष्ठा btree_keys *b, अचिन्हित पूर्णांक start,
			    काष्ठा bset_sort_state *state)
अणु
	माप_प्रकार order = b->page_order, keys = 0;
	काष्ठा btree_iter iter;
	पूर्णांक oldsize = bch_count_data(b);

	__bch_btree_iter_init(b, &iter, शून्य, &b->set[start]);

	अगर (start) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = start; i <= b->nsets; i++)
			keys += b->set[i].data->keys;

		order = get_order(__set_bytes(b->set->data, keys));
	पूर्ण

	__btree_sort(b, &iter, start, order, false, state);

	EBUG_ON(oldsize >= 0 && bch_count_data(b) != oldsize);
पूर्ण

व्योम bch_btree_sort_and_fix_extents(काष्ठा btree_keys *b,
				    काष्ठा btree_iter *iter,
				    काष्ठा bset_sort_state *state)
अणु
	__btree_sort(b, iter, 0, b->page_order, true, state);
पूर्ण

व्योम bch_btree_sort_पूर्णांकo(काष्ठा btree_keys *b, काष्ठा btree_keys *new,
			 काष्ठा bset_sort_state *state)
अणु
	uपूर्णांक64_t start_समय = local_घड़ी();
	काष्ठा btree_iter iter;

	bch_btree_iter_init(b, &iter, शून्य);

	btree_mergesort(b, new->set->data, &iter, false, true);

	bch_समय_stats_update(&state->समय, start_समय);

	new->set->size = 0; // XXX: why?
पूर्ण

#घोषणा SORT_CRIT	(4096 / माप(uपूर्णांक64_t))

व्योम bch_btree_sort_lazy(काष्ठा btree_keys *b, काष्ठा bset_sort_state *state)
अणु
	अचिन्हित पूर्णांक crit = SORT_CRIT;
	पूर्णांक i;

	/* Don't sort अगर nothing to करो */
	अगर (!b->nsets)
		जाओ out;

	क्रम (i = b->nsets - 1; i >= 0; --i) अणु
		crit *= state->crit_factor;

		अगर (b->set[i].data->keys < crit) अणु
			bch_btree_sort_partial(b, i, state);
			वापस;
		पूर्ण
	पूर्ण

	/* Sort अगर we'd overflow */
	अगर (b->nsets + 1 == MAX_BSETS) अणु
		bch_btree_sort(b, state);
		वापस;
	पूर्ण

out:
	bch_bset_build_written_tree(b);
पूर्ण

व्योम bch_btree_keys_stats(काष्ठा btree_keys *b, काष्ठा bset_stats *stats)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i <= b->nsets; i++) अणु
		काष्ठा bset_tree *t = &b->set[i];
		माप_प्रकार bytes = t->data->keys * माप(uपूर्णांक64_t);
		माप_प्रकार j;

		अगर (bset_written(b, t)) अणु
			stats->sets_written++;
			stats->bytes_written += bytes;

			stats->भग्नs += t->size - 1;

			क्रम (j = 1; j < t->size; j++)
				अगर (t->tree[j].exponent == 127)
					stats->failed++;
		पूर्ण अन्यथा अणु
			stats->sets_unwritten++;
			stats->bytes_unwritten += bytes;
		पूर्ण
	पूर्ण
पूर्ण
