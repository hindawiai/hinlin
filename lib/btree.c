<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lib/btree.c	- Simple In-memory B+Tree
 *
 * Copyright (c) 2007-2008 Joern Engel <joern@purestorage.com>
 * Bits and pieces stolen from Peter Zijlstra's code, which is
 * Copyright 2007, Red Hat Inc. Peter Zijlstra
 *
 * see http://programming.kicks-ass.net/kernel-patches/vma_lookup/btree.patch
 *
 * A relatively simple B+Tree implementation.  I have written it as a learning
 * exercise to understand how B+Trees work.  Turned out to be useful as well.
 *
 * B+Trees can be used similar to Linux radix trees (which करोn't have anything
 * in common with textbook radix trees, beware).  Prerequisite क्रम them working
 * well is that access to a अक्रमom tree node is much faster than a large number
 * of operations within each node.
 *
 * Disks have fulfilled the prerequisite क्रम a दीर्घ समय.  More recently DRAM
 * has gained similar properties, as memory access बार, when measured in cpu
 * cycles, have increased.  Cacheline sizes have increased as well, which also
 * helps B+Trees.
 *
 * Compared to radix trees, B+Trees are more efficient when dealing with a
 * sparsely populated address space.  Between 25% and 50% of the memory is
 * occupied with valid poपूर्णांकers.  When densely populated, radix trees contain
 * ~98% poपूर्णांकers - hard to beat.  Very sparse radix trees contain only ~2%
 * poपूर्णांकers.
 *
 * This particular implementation stores poपूर्णांकers identअगरied by a दीर्घ value.
 * Storing शून्य poपूर्णांकers is illegal, lookup will वापस शून्य when no entry
 * was found.
 *
 * A tricks was used that is not commonly found in textbooks.  The lowest
 * values are to the right, not to the left.  All used slots within a node
 * are on the left, all unused slots contain NUL values.  Most operations
 * simply loop once over all slots and terminate on the first NUL.
 */

#समावेश <linux/btree.h>
#समावेश <linux/cache.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा MAX(a, b) ((a) > (b) ? (a) : (b))
#घोषणा NODESIZE MAX(L1_CACHE_BYTES, 128)

काष्ठा btree_geo अणु
	पूर्णांक keylen;
	पूर्णांक no_pairs;
	पूर्णांक no_दीर्घs;
पूर्ण;

काष्ठा btree_geo btree_geo32 = अणु
	.keylen = 1,
	.no_pairs = NODESIZE / माप(दीर्घ) / 2,
	.no_दीर्घs = NODESIZE / माप(दीर्घ) / 2,
पूर्ण;
EXPORT_SYMBOL_GPL(btree_geo32);

#घोषणा LONG_PER_U64 (64 / BITS_PER_LONG)
काष्ठा btree_geo btree_geo64 = अणु
	.keylen = LONG_PER_U64,
	.no_pairs = NODESIZE / माप(दीर्घ) / (1 + LONG_PER_U64),
	.no_दीर्घs = LONG_PER_U64 * (NODESIZE / माप(दीर्घ) / (1 + LONG_PER_U64)),
पूर्ण;
EXPORT_SYMBOL_GPL(btree_geo64);

काष्ठा btree_geo btree_geo128 = अणु
	.keylen = 2 * LONG_PER_U64,
	.no_pairs = NODESIZE / माप(दीर्घ) / (1 + 2 * LONG_PER_U64),
	.no_दीर्घs = 2 * LONG_PER_U64 * (NODESIZE / माप(दीर्घ) / (1 + 2 * LONG_PER_U64)),
पूर्ण;
EXPORT_SYMBOL_GPL(btree_geo128);

#घोषणा MAX_KEYLEN	(2 * LONG_PER_U64)

अटल काष्ठा kmem_cache *btree_cachep;

व्योम *btree_alloc(gfp_t gfp_mask, व्योम *pool_data)
अणु
	वापस kmem_cache_alloc(btree_cachep, gfp_mask);
पूर्ण
EXPORT_SYMBOL_GPL(btree_alloc);

व्योम btree_मुक्त(व्योम *element, व्योम *pool_data)
अणु
	kmem_cache_मुक्त(btree_cachep, element);
पूर्ण
EXPORT_SYMBOL_GPL(btree_मुक्त);

अटल अचिन्हित दीर्घ *btree_node_alloc(काष्ठा btree_head *head, gfp_t gfp)
अणु
	अचिन्हित दीर्घ *node;

	node = mempool_alloc(head->mempool, gfp);
	अगर (likely(node))
		स_रखो(node, 0, NODESIZE);
	वापस node;
पूर्ण

अटल पूर्णांक दीर्घcmp(स्थिर अचिन्हित दीर्घ *l1, स्थिर अचिन्हित दीर्घ *l2, माप_प्रकार n)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < n; i++) अणु
		अगर (l1[i] < l2[i])
			वापस -1;
		अगर (l1[i] > l2[i])
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ *दीर्घcpy(अचिन्हित दीर्घ *dest, स्थिर अचिन्हित दीर्घ *src,
		माप_प्रकार n)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < n; i++)
		dest[i] = src[i];
	वापस dest;
पूर्ण

अटल अचिन्हित दीर्घ *दीर्घset(अचिन्हित दीर्घ *s, अचिन्हित दीर्घ c, माप_प्रकार n)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < n; i++)
		s[i] = c;
	वापस s;
पूर्ण

अटल व्योम dec_key(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *key)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	क्रम (i = geo->keylen - 1; i >= 0; i--) अणु
		val = key[i];
		key[i] = val - 1;
		अगर (val)
			अवरोध;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ *bkey(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *node, पूर्णांक n)
अणु
	वापस &node[n * geo->keylen];
पूर्ण

अटल व्योम *bval(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *node, पूर्णांक n)
अणु
	वापस (व्योम *)node[geo->no_दीर्घs + n];
पूर्ण

अटल व्योम setkey(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *node, पूर्णांक n,
		   अचिन्हित दीर्घ *key)
अणु
	दीर्घcpy(bkey(geo, node, n), key, geo->keylen);
पूर्ण

अटल व्योम setval(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *node, पूर्णांक n,
		   व्योम *val)
अणु
	node[geo->no_दीर्घs + n] = (अचिन्हित दीर्घ) val;
पूर्ण

अटल व्योम clearpair(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *node, पूर्णांक n)
अणु
	दीर्घset(bkey(geo, node, n), 0, geo->keylen);
	node[geo->no_दीर्घs + n] = 0;
पूर्ण

अटल अंतरभूत व्योम __btree_init(काष्ठा btree_head *head)
अणु
	head->node = शून्य;
	head->height = 0;
पूर्ण

व्योम btree_init_mempool(काष्ठा btree_head *head, mempool_t *mempool)
अणु
	__btree_init(head);
	head->mempool = mempool;
पूर्ण
EXPORT_SYMBOL_GPL(btree_init_mempool);

पूर्णांक btree_init(काष्ठा btree_head *head)
अणु
	__btree_init(head);
	head->mempool = mempool_create(0, btree_alloc, btree_मुक्त, शून्य);
	अगर (!head->mempool)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btree_init);

व्योम btree_destroy(काष्ठा btree_head *head)
अणु
	mempool_मुक्त(head->node, head->mempool);
	mempool_destroy(head->mempool);
	head->mempool = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(btree_destroy);

व्योम *btree_last(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		 अचिन्हित दीर्घ *key)
अणु
	पूर्णांक height = head->height;
	अचिन्हित दीर्घ *node = head->node;

	अगर (height == 0)
		वापस शून्य;

	क्रम ( ; height > 1; height--)
		node = bval(geo, node, 0);

	दीर्घcpy(key, bkey(geo, node, 0), geo->keylen);
	वापस bval(geo, node, 0);
पूर्ण
EXPORT_SYMBOL_GPL(btree_last);

अटल पूर्णांक keycmp(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *node, पूर्णांक pos,
		  अचिन्हित दीर्घ *key)
अणु
	वापस दीर्घcmp(bkey(geo, node, pos), key, geo->keylen);
पूर्ण

अटल पूर्णांक keyzero(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *key)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < geo->keylen; i++)
		अगर (key[i])
			वापस 0;

	वापस 1;
पूर्ण

व्योम *btree_lookup(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		अचिन्हित दीर्घ *key)
अणु
	पूर्णांक i, height = head->height;
	अचिन्हित दीर्घ *node = head->node;

	अगर (height == 0)
		वापस शून्य;

	क्रम ( ; height > 1; height--) अणु
		क्रम (i = 0; i < geo->no_pairs; i++)
			अगर (keycmp(geo, node, i, key) <= 0)
				अवरोध;
		अगर (i == geo->no_pairs)
			वापस शून्य;
		node = bval(geo, node, i);
		अगर (!node)
			वापस शून्य;
	पूर्ण

	अगर (!node)
		वापस शून्य;

	क्रम (i = 0; i < geo->no_pairs; i++)
		अगर (keycmp(geo, node, i, key) == 0)
			वापस bval(geo, node, i);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(btree_lookup);

पूर्णांक btree_update(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		 अचिन्हित दीर्घ *key, व्योम *val)
अणु
	पूर्णांक i, height = head->height;
	अचिन्हित दीर्घ *node = head->node;

	अगर (height == 0)
		वापस -ENOENT;

	क्रम ( ; height > 1; height--) अणु
		क्रम (i = 0; i < geo->no_pairs; i++)
			अगर (keycmp(geo, node, i, key) <= 0)
				अवरोध;
		अगर (i == geo->no_pairs)
			वापस -ENOENT;
		node = bval(geo, node, i);
		अगर (!node)
			वापस -ENOENT;
	पूर्ण

	अगर (!node)
		वापस -ENOENT;

	क्रम (i = 0; i < geo->no_pairs; i++)
		अगर (keycmp(geo, node, i, key) == 0) अणु
			setval(geo, node, i, val);
			वापस 0;
		पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(btree_update);

/*
 * Usually this function is quite similar to normal lookup.  But the key of
 * a parent node may be smaller than the smallest key of all its siblings.
 * In such a हाल we cannot just वापस शून्य, as we have only proven that no
 * key smaller than __key, but larger than this parent key exists.
 * So we set __key to the parent key and retry.  We have to use the smallest
 * such parent key, which is the last parent key we encountered.
 */
व्योम *btree_get_prev(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		     अचिन्हित दीर्घ *__key)
अणु
	पूर्णांक i, height;
	अचिन्हित दीर्घ *node, *oldnode;
	अचिन्हित दीर्घ *retry_key = शून्य, key[MAX_KEYLEN];

	अगर (keyzero(geo, __key))
		वापस शून्य;

	अगर (head->height == 0)
		वापस शून्य;
	दीर्घcpy(key, __key, geo->keylen);
retry:
	dec_key(geo, key);

	node = head->node;
	क्रम (height = head->height ; height > 1; height--) अणु
		क्रम (i = 0; i < geo->no_pairs; i++)
			अगर (keycmp(geo, node, i, key) <= 0)
				अवरोध;
		अगर (i == geo->no_pairs)
			जाओ miss;
		oldnode = node;
		node = bval(geo, node, i);
		अगर (!node)
			जाओ miss;
		retry_key = bkey(geo, oldnode, i);
	पूर्ण

	अगर (!node)
		जाओ miss;

	क्रम (i = 0; i < geo->no_pairs; i++) अणु
		अगर (keycmp(geo, node, i, key) <= 0) अणु
			अगर (bval(geo, node, i)) अणु
				दीर्घcpy(__key, bkey(geo, node, i), geo->keylen);
				वापस bval(geo, node, i);
			पूर्ण अन्यथा
				जाओ miss;
		पूर्ण
	पूर्ण
miss:
	अगर (retry_key) अणु
		दीर्घcpy(key, retry_key, geo->keylen);
		retry_key = शून्य;
		जाओ retry;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(btree_get_prev);

अटल पूर्णांक getpos(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *node,
		अचिन्हित दीर्घ *key)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < geo->no_pairs; i++) अणु
		अगर (keycmp(geo, node, i, key) <= 0)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक getfill(काष्ठा btree_geo *geo, अचिन्हित दीर्घ *node, पूर्णांक start)
अणु
	पूर्णांक i;

	क्रम (i = start; i < geo->no_pairs; i++)
		अगर (!bval(geo, node, i))
			अवरोध;
	वापस i;
पूर्ण

/*
 * locate the correct leaf node in the btree
 */
अटल अचिन्हित दीर्घ *find_level(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		अचिन्हित दीर्घ *key, पूर्णांक level)
अणु
	अचिन्हित दीर्घ *node = head->node;
	पूर्णांक i, height;

	क्रम (height = head->height; height > level; height--) अणु
		क्रम (i = 0; i < geo->no_pairs; i++)
			अगर (keycmp(geo, node, i, key) <= 0)
				अवरोध;

		अगर ((i == geo->no_pairs) || !bval(geo, node, i)) अणु
			/* right-most key is too large, update it */
			/* FIXME: If the right-most key on higher levels is
			 * always zero, this wouldn't be necessary. */
			i--;
			setkey(geo, node, i, key);
		पूर्ण
		BUG_ON(i < 0);
		node = bval(geo, node, i);
	पूर्ण
	BUG_ON(!node);
	वापस node;
पूर्ण

अटल पूर्णांक btree_grow(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		      gfp_t gfp)
अणु
	अचिन्हित दीर्घ *node;
	पूर्णांक fill;

	node = btree_node_alloc(head, gfp);
	अगर (!node)
		वापस -ENOMEM;
	अगर (head->node) अणु
		fill = getfill(geo, head->node, 0);
		setkey(geo, node, 0, bkey(geo, head->node, fill - 1));
		setval(geo, node, 0, head->node);
	पूर्ण
	head->node = node;
	head->height++;
	वापस 0;
पूर्ण

अटल व्योम btree_shrink(काष्ठा btree_head *head, काष्ठा btree_geo *geo)
अणु
	अचिन्हित दीर्घ *node;
	पूर्णांक fill;

	अगर (head->height <= 1)
		वापस;

	node = head->node;
	fill = getfill(geo, node, 0);
	BUG_ON(fill > 1);
	head->node = bval(geo, node, 0);
	head->height--;
	mempool_मुक्त(node, head->mempool);
पूर्ण

अटल पूर्णांक btree_insert_level(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
			      अचिन्हित दीर्घ *key, व्योम *val, पूर्णांक level,
			      gfp_t gfp)
अणु
	अचिन्हित दीर्घ *node;
	पूर्णांक i, pos, fill, err;

	BUG_ON(!val);
	अगर (head->height < level) अणु
		err = btree_grow(head, geo, gfp);
		अगर (err)
			वापस err;
	पूर्ण

retry:
	node = find_level(head, geo, key, level);
	pos = getpos(geo, node, key);
	fill = getfill(geo, node, pos);
	/* two identical keys are not allowed */
	BUG_ON(pos < fill && keycmp(geo, node, pos, key) == 0);

	अगर (fill == geo->no_pairs) अणु
		/* need to split node */
		अचिन्हित दीर्घ *new;

		new = btree_node_alloc(head, gfp);
		अगर (!new)
			वापस -ENOMEM;
		err = btree_insert_level(head, geo,
				bkey(geo, node, fill / 2 - 1),
				new, level + 1, gfp);
		अगर (err) अणु
			mempool_मुक्त(new, head->mempool);
			वापस err;
		पूर्ण
		क्रम (i = 0; i < fill / 2; i++) अणु
			setkey(geo, new, i, bkey(geo, node, i));
			setval(geo, new, i, bval(geo, node, i));
			setkey(geo, node, i, bkey(geo, node, i + fill / 2));
			setval(geo, node, i, bval(geo, node, i + fill / 2));
			clearpair(geo, node, i + fill / 2);
		पूर्ण
		अगर (fill & 1) अणु
			setkey(geo, node, i, bkey(geo, node, fill - 1));
			setval(geo, node, i, bval(geo, node, fill - 1));
			clearpair(geo, node, fill - 1);
		पूर्ण
		जाओ retry;
	पूर्ण
	BUG_ON(fill >= geo->no_pairs);

	/* shअगरt and insert */
	क्रम (i = fill; i > pos; i--) अणु
		setkey(geo, node, i, bkey(geo, node, i - 1));
		setval(geo, node, i, bval(geo, node, i - 1));
	पूर्ण
	setkey(geo, node, pos, key);
	setval(geo, node, pos, val);

	वापस 0;
पूर्ण

पूर्णांक btree_insert(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		अचिन्हित दीर्घ *key, व्योम *val, gfp_t gfp)
अणु
	BUG_ON(!val);
	वापस btree_insert_level(head, geo, key, val, 1, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(btree_insert);

अटल व्योम *btree_हटाओ_level(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		अचिन्हित दीर्घ *key, पूर्णांक level);
अटल व्योम merge(काष्ठा btree_head *head, काष्ठा btree_geo *geo, पूर्णांक level,
		अचिन्हित दीर्घ *left, पूर्णांक lfill,
		अचिन्हित दीर्घ *right, पूर्णांक rfill,
		अचिन्हित दीर्घ *parent, पूर्णांक lpos)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rfill; i++) अणु
		/* Move all keys to the left */
		setkey(geo, left, lfill + i, bkey(geo, right, i));
		setval(geo, left, lfill + i, bval(geo, right, i));
	पूर्ण
	/* Exchange left and right child in parent */
	setval(geo, parent, lpos, right);
	setval(geo, parent, lpos + 1, left);
	/* Remove left (क्रमmerly right) child from parent */
	btree_हटाओ_level(head, geo, bkey(geo, parent, lpos), level + 1);
	mempool_मुक्त(right, head->mempool);
पूर्ण

अटल व्योम rebalance(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		अचिन्हित दीर्घ *key, पूर्णांक level, अचिन्हित दीर्घ *child, पूर्णांक fill)
अणु
	अचिन्हित दीर्घ *parent, *left = शून्य, *right = शून्य;
	पूर्णांक i, no_left, no_right;

	अगर (fill == 0) अणु
		/* Because we करोn't steal entries from a neighbour, this हाल
		 * can happen.  Parent node contains a single child, this
		 * node, so merging with a sibling never happens.
		 */
		btree_हटाओ_level(head, geo, key, level + 1);
		mempool_मुक्त(child, head->mempool);
		वापस;
	पूर्ण

	parent = find_level(head, geo, key, level + 1);
	i = getpos(geo, parent, key);
	BUG_ON(bval(geo, parent, i) != child);

	अगर (i > 0) अणु
		left = bval(geo, parent, i - 1);
		no_left = getfill(geo, left, 0);
		अगर (fill + no_left <= geo->no_pairs) अणु
			merge(head, geo, level,
					left, no_left,
					child, fill,
					parent, i - 1);
			वापस;
		पूर्ण
	पूर्ण
	अगर (i + 1 < getfill(geo, parent, i)) अणु
		right = bval(geo, parent, i + 1);
		no_right = getfill(geo, right, 0);
		अगर (fill + no_right <= geo->no_pairs) अणु
			merge(head, geo, level,
					child, fill,
					right, no_right,
					parent, i);
			वापस;
		पूर्ण
	पूर्ण
	/*
	 * We could also try to steal one entry from the left or right
	 * neighbor.  By not करोing so we changed the invariant from
	 * "all nodes are at least half full" to "no two neighboring
	 * nodes can be merged".  Which means that the average fill of
	 * all nodes is still half or better.
	 */
पूर्ण

अटल व्योम *btree_हटाओ_level(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		अचिन्हित दीर्घ *key, पूर्णांक level)
अणु
	अचिन्हित दीर्घ *node;
	पूर्णांक i, pos, fill;
	व्योम *ret;

	अगर (level > head->height) अणु
		/* we recursed all the way up */
		head->height = 0;
		head->node = शून्य;
		वापस शून्य;
	पूर्ण

	node = find_level(head, geo, key, level);
	pos = getpos(geo, node, key);
	fill = getfill(geo, node, pos);
	अगर ((level == 1) && (keycmp(geo, node, pos, key) != 0))
		वापस शून्य;
	ret = bval(geo, node, pos);

	/* हटाओ and shअगरt */
	क्रम (i = pos; i < fill - 1; i++) अणु
		setkey(geo, node, i, bkey(geo, node, i + 1));
		setval(geo, node, i, bval(geo, node, i + 1));
	पूर्ण
	clearpair(geo, node, fill - 1);

	अगर (fill - 1 < geo->no_pairs / 2) अणु
		अगर (level < head->height)
			rebalance(head, geo, key, level, node, fill - 1);
		अन्यथा अगर (fill - 1 == 1)
			btree_shrink(head, geo);
	पूर्ण

	वापस ret;
पूर्ण

व्योम *btree_हटाओ(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		अचिन्हित दीर्घ *key)
अणु
	अगर (head->height == 0)
		वापस शून्य;

	वापस btree_हटाओ_level(head, geo, key, 1);
पूर्ण
EXPORT_SYMBOL_GPL(btree_हटाओ);

पूर्णांक btree_merge(काष्ठा btree_head *target, काष्ठा btree_head *victim,
		काष्ठा btree_geo *geo, gfp_t gfp)
अणु
	अचिन्हित दीर्घ key[MAX_KEYLEN];
	अचिन्हित दीर्घ dup[MAX_KEYLEN];
	व्योम *val;
	पूर्णांक err;

	BUG_ON(target == victim);

	अगर (!(target->node)) अणु
		/* target is empty, just copy fields over */
		target->node = victim->node;
		target->height = victim->height;
		__btree_init(victim);
		वापस 0;
	पूर्ण

	/* TODO: This needs some optimizations.  Currently we करो three tree
	 * walks to हटाओ a single object from the victim.
	 */
	क्रम (;;) अणु
		अगर (!btree_last(victim, geo, key))
			अवरोध;
		val = btree_lookup(victim, geo, key);
		err = btree_insert(target, geo, key, val, gfp);
		अगर (err)
			वापस err;
		/* We must make a copy of the key, as the original will get
		 * mangled inside btree_हटाओ. */
		दीर्घcpy(dup, key, geo->keylen);
		btree_हटाओ(victim, geo, dup);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btree_merge);

अटल माप_प्रकार __btree_क्रम_each(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
			       अचिन्हित दीर्घ *node, अचिन्हित दीर्घ opaque,
			       व्योम (*func)(व्योम *elem, अचिन्हित दीर्घ opaque,
					    अचिन्हित दीर्घ *key, माप_प्रकार index,
					    व्योम *func2),
			       व्योम *func2, पूर्णांक reap, पूर्णांक height, माप_प्रकार count)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ *child;

	क्रम (i = 0; i < geo->no_pairs; i++) अणु
		child = bval(geo, node, i);
		अगर (!child)
			अवरोध;
		अगर (height > 1)
			count = __btree_क्रम_each(head, geo, child, opaque,
					func, func2, reap, height - 1, count);
		अन्यथा
			func(child, opaque, bkey(geo, node, i), count++,
					func2);
	पूर्ण
	अगर (reap)
		mempool_मुक्त(node, head->mempool);
	वापस count;
पूर्ण

अटल व्योम empty(व्योम *elem, अचिन्हित दीर्घ opaque, अचिन्हित दीर्घ *key,
		  माप_प्रकार index, व्योम *func2)
अणु
पूर्ण

व्योम visitorl(व्योम *elem, अचिन्हित दीर्घ opaque, अचिन्हित दीर्घ *key,
	      माप_प्रकार index, व्योम *__func)
अणु
	visitorl_t func = __func;

	func(elem, opaque, *key, index);
पूर्ण
EXPORT_SYMBOL_GPL(visitorl);

व्योम visitor32(व्योम *elem, अचिन्हित दीर्घ opaque, अचिन्हित दीर्घ *__key,
	       माप_प्रकार index, व्योम *__func)
अणु
	visitor32_t func = __func;
	u32 *key = (व्योम *)__key;

	func(elem, opaque, *key, index);
पूर्ण
EXPORT_SYMBOL_GPL(visitor32);

व्योम visitor64(व्योम *elem, अचिन्हित दीर्घ opaque, अचिन्हित दीर्घ *__key,
	       माप_प्रकार index, व्योम *__func)
अणु
	visitor64_t func = __func;
	u64 *key = (व्योम *)__key;

	func(elem, opaque, *key, index);
पूर्ण
EXPORT_SYMBOL_GPL(visitor64);

व्योम visitor128(व्योम *elem, अचिन्हित दीर्घ opaque, अचिन्हित दीर्घ *__key,
		माप_प्रकार index, व्योम *__func)
अणु
	visitor128_t func = __func;
	u64 *key = (व्योम *)__key;

	func(elem, opaque, key[0], key[1], index);
पूर्ण
EXPORT_SYMBOL_GPL(visitor128);

माप_प्रकार btree_visitor(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		     अचिन्हित दीर्घ opaque,
		     व्योम (*func)(व्योम *elem, अचिन्हित दीर्घ opaque,
		     		  अचिन्हित दीर्घ *key,
		     		  माप_प्रकार index, व्योम *func2),
		     व्योम *func2)
अणु
	माप_प्रकार count = 0;

	अगर (!func2)
		func = empty;
	अगर (head->node)
		count = __btree_क्रम_each(head, geo, head->node, opaque, func,
				func2, 0, head->height, 0);
	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(btree_visitor);

माप_प्रकार btree_grim_visitor(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
			  अचिन्हित दीर्घ opaque,
			  व्योम (*func)(व्योम *elem, अचिन्हित दीर्घ opaque,
				       अचिन्हित दीर्घ *key,
				       माप_प्रकार index, व्योम *func2),
			  व्योम *func2)
अणु
	माप_प्रकार count = 0;

	अगर (!func2)
		func = empty;
	अगर (head->node)
		count = __btree_क्रम_each(head, geo, head->node, opaque, func,
				func2, 1, head->height, 0);
	__btree_init(head);
	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(btree_grim_visitor);

अटल पूर्णांक __init btree_module_init(व्योम)
अणु
	btree_cachep = kmem_cache_create("btree_node", NODESIZE, 0,
			SLAB_HWCACHE_ALIGN, शून्य);
	वापस 0;
पूर्ण

अटल व्योम __निकास btree_module_निकास(व्योम)
अणु
	kmem_cache_destroy(btree_cachep);
पूर्ण

/* If core code starts using btree, initialization should happen even earlier */
module_init(btree_module_init);
module_निकास(btree_module_निकास);

MODULE_AUTHOR("Joern Engel <joern@logfs.org>");
MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_LICENSE("GPL");
