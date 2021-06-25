<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_BSET_H
#घोषणा _BCACHE_BSET_H

#समावेश <linux/bcache.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "util.h" /* क्रम समय_stats */

/*
 * BKEYS:
 *
 * A bkey contains a key, a size field, a variable number of poपूर्णांकers, and some
 * ancillary flag bits.
 *
 * We use two dअगरferent functions क्रम validating bkeys, bch_ptr_invalid and
 * bch_ptr_bad().
 *
 * bch_ptr_invalid() primarily filters out keys and poपूर्णांकers that would be
 * invalid due to some sort of bug, whereas bch_ptr_bad() filters out keys and
 * poपूर्णांकer that occur in normal practice but करोn't poपूर्णांक to real data.
 *
 * The one exception to the rule that ptr_invalid() filters out invalid keys is
 * that it also filters out keys of size 0 - these are keys that have been
 * completely overwritten. It'd be safe to delete these in memory जबतक leaving
 * them on disk, just unnecessary work - so we filter them out when resorting
 * instead.
 *
 * We can't filter out stale keys when we're resorting, because garbage
 * collection needs to find them to ensure bucket gens करोn't wrap around -
 * unless we're rewriting the btree node those stale keys still exist on disk.
 *
 * We also implement functions here क्रम removing some number of sectors from the
 * front or the back of a bkey - this is मुख्यly used क्रम fixing overlapping
 * extents, by removing the overlapping sectors from the older key.
 *
 * BSETS:
 *
 * A bset is an array of bkeys laid out contiguously in memory in sorted order,
 * aदीर्घ with a header. A btree node is made up of a number of these, written at
 * dअगरferent बार.
 *
 * There could be many of them on disk, but we never allow there to be more than
 * 4 in memory - we lazily resort as needed.
 *
 * We implement code here क्रम creating and मुख्यtaining auxiliary search trees
 * (described below) क्रम searching an inभागidial bset, and on top of that we
 * implement a btree iterator.
 *
 * BTREE ITERATOR:
 *
 * Most of the code in bcache करोesn't care about an inभागidual bset - it needs
 * to search entire btree nodes and iterate over them in sorted order.
 *
 * The btree iterator code serves both functions; it iterates through the keys
 * in a btree node in sorted order, starting from either keys after a specअगरic
 * poपूर्णांक (अगर you pass it a search key) or the start of the btree node.
 *
 * AUXILIARY SEARCH TREES:
 *
 * Since keys are variable length, we can't use a binary search on a bset - we
 * wouldn't be able to find the start of the next key. But binary searches are
 * slow anyways, due to terrible cache behaviour; bcache originally used binary
 * searches and that code topped out at under 50k lookups/second.
 *
 * So we need to स्थिरruct some sort of lookup table. Since we only insert keys
 * पूर्णांकo the last (unwritten) set, most of the keys within a given btree node are
 * usually in sets that are mostly स्थिरant. We use two dअगरferent types of
 * lookup tables to take advantage of this.
 *
 * Both lookup tables share in common that they करोn't index every key in the
 * set; they index one key every BSET_CACHELINE bytes, and then a linear search
 * is used क्रम the rest.
 *
 * For sets that have been written to disk and are no दीर्घer being inserted
 * पूर्णांकo, we स्थिरruct a binary search tree in an array - traversing a binary
 * search tree in an array gives excellent locality of reference and is very
 * fast, since both children of any node are adjacent to each other in memory
 * (and their gअक्रमchildren, and great gअक्रमchildren...) - this means
 * prefetching can be used to great effect.
 *
 * It's quite useful perक्रमmance wise to keep these nodes small - not just
 * because they're more likely to be in L2, but also because we can prefetch
 * more nodes on a single cacheline and thus prefetch more iterations in advance
 * when traversing this tree.
 *
 * Nodes in the auxiliary search tree must contain both a key to compare against
 * (we करोn't want to fetch the key from the set, that would defeat the purpose),
 * and a poपूर्णांकer to the key. We use a few tricks to compress both of these.
 *
 * To compress the poपूर्णांकer, we take advantage of the fact that one node in the
 * search tree corresponds to precisely BSET_CACHELINE bytes in the set. We have
 * a function (to_inorder()) that takes the index of a node in a binary tree and
 * वापसs what its index would be in an inorder traversal, so we only have to
 * store the low bits of the offset.
 *
 * The key is 84 bits (KEY_DEV + key->key, the offset on the device). To
 * compress that,  we take advantage of the fact that when we're traversing the
 * search tree at every iteration we know that both our search key and the key
 * we're looking क्रम lie within some range - bounded by our previous
 * comparisons. (We special हाल the start of a search so that this is true even
 * at the root of the tree).
 *
 * So we know the key we're looking for is between a and b, and a and b don't
 * dअगरfer higher than bit 50, we करोn't need to check anything higher than bit
 * 50.
 *
 * We करोn't usually need the rest of the bits, either; we only need enough bits
 * to partition the key range we're currently checking.  Consider key n - the
 * key our auxiliary search tree node corresponds to, and key p, the key
 * immediately preceding n.  The lowest bit we need to store in the auxiliary
 * search tree is the highest bit that dअगरfers between n and p.
 *
 * Note that this could be bit 0 - we might someबार need all 80 bits to करो the
 * comparison. But we'd really like our nodes in the auxiliary search tree to be
 * of fixed size.
 *
 * The solution is to make them fixed size, and when we're स्थिरructing a node
 * check अगर p and n dअगरfered in the bits we needed them to. If they करोn't we
 * flag that node, and when करोing lookups we fallback to comparing against the
 * real key. As दीर्घ as this करोesn't happen to often (and it seems to reliably
 * happen a bit less than 1% of the समय), we win - even on failures, that key
 * is then more likely to be in cache than अगर we were करोing binary searches all
 * the way, since we're touching so much less memory.
 *
 * The keys in the auxiliary search tree are stored in (software) भग्नing
 * poपूर्णांक, with an exponent and a mantissa. The exponent needs to be big enough
 * to address all the bits in the original key, but the number of bits in the
 * mantissa is somewhat arbitrary; more bits just माला_लो us fewer failures.
 *
 * We need 7 bits क्रम the exponent and 3 bits क्रम the key's offset (since keys
 * are 8 byte aligned); using 22 bits क्रम the mantissa means a node is 4 bytes.
 * We need one node per 128 bytes in the btree node, which means the auxiliary
 * search trees take up 3% as much memory as the btree itself.
 *
 * Conकाष्ठाing these auxiliary search trees is moderately expensive, and we
 * करोn't want to be स्थिरantly rebuilding the search tree क्रम the last set
 * whenever we insert another key पूर्णांकo it. For the unwritten set, we use a much
 * simpler lookup table - it's just a flat array, so index i in the lookup table
 * corresponds to the i range of BSET_CACHELINE bytes in the set. Indexing
 * within each byte range works the same as with the auxiliary search trees.
 *
 * These are much easier to keep up to date when we insert a key - we करो it
 * somewhat lazily; when we shअगरt a key up we usually just increment the poपूर्णांकer
 * to it, only when it would overflow करो we go to the trouble of finding the
 * first key in that range of bytes again.
 */

काष्ठा btree_keys;
काष्ठा btree_iter;
काष्ठा btree_iter_set;
काष्ठा bkey_भग्न;

#घोषणा MAX_BSETS		4U

काष्ठा bset_tree अणु
	/*
	 * We स्थिरruct a binary tree in an array as अगर the array
	 * started at 1, so that things line up on the same cachelines
	 * better: see comments in bset.c at cacheline_to_bkey() क्रम
	 * details
	 */

	/* size of the binary tree and prev array */
	अचिन्हित पूर्णांक		size;

	/* function of size - precalculated क्रम to_inorder() */
	अचिन्हित पूर्णांक		extra;

	/* copy of the last key in the set */
	काष्ठा bkey		end;
	काष्ठा bkey_भग्न	*tree;

	/*
	 * The nodes in the bset tree poपूर्णांक to specअगरic keys - this
	 * array holds the sizes of the previous key.
	 *
	 * Conceptually it's a member of काष्ठा bkey_भग्न, but we want
	 * to keep bkey_भग्न to 4 bytes and prev isn't used in the fast
	 * path.
	 */
	uपूर्णांक8_t			*prev;

	/* The actual btree node, with poपूर्णांकers to each sorted set */
	काष्ठा bset		*data;
पूर्ण;

काष्ठा btree_keys_ops अणु
	bool		(*sort_cmp)(काष्ठा btree_iter_set l,
				    काष्ठा btree_iter_set r);
	काष्ठा bkey	*(*sort_fixup)(काष्ठा btree_iter *iter,
				       काष्ठा bkey *पंचांगp);
	bool		(*insert_fixup)(काष्ठा btree_keys *b,
					काष्ठा bkey *insert,
					काष्ठा btree_iter *iter,
					काष्ठा bkey *replace_key);
	bool		(*key_invalid)(काष्ठा btree_keys *bk,
				       स्थिर काष्ठा bkey *k);
	bool		(*key_bad)(काष्ठा btree_keys *bk,
				   स्थिर काष्ठा bkey *k);
	bool		(*key_merge)(काष्ठा btree_keys *bk,
				     काष्ठा bkey *l, काष्ठा bkey *r);
	व्योम		(*key_to_text)(अक्षर *buf,
				       माप_प्रकार size,
				       स्थिर काष्ठा bkey *k);
	व्योम		(*key_dump)(काष्ठा btree_keys *keys,
				    स्थिर काष्ठा bkey *k);

	/*
	 * Only used क्रम deciding whether to use START_KEY(k) or just the key
	 * itself in a couple places
	 */
	bool		is_extents;
पूर्ण;

काष्ठा btree_keys अणु
	स्थिर काष्ठा btree_keys_ops	*ops;
	uपूर्णांक8_t			page_order;
	uपूर्णांक8_t			nsets;
	अचिन्हित पूर्णांक		last_set_unwritten:1;
	bool			*expensive_debug_checks;

	/*
	 * Sets of sorted keys - the real btree node - plus a binary search tree
	 *
	 * set[0] is special; set[0]->tree, set[0]->prev and set[0]->data poपूर्णांक
	 * to the memory we have allocated क्रम this btree node. Additionally,
	 * set[0]->data poपूर्णांकs to the entire btree node as it exists on disk.
	 */
	काष्ठा bset_tree	set[MAX_BSETS];
पूर्ण;

अटल अंतरभूत काष्ठा bset_tree *bset_tree_last(काष्ठा btree_keys *b)
अणु
	वापस b->set + b->nsets;
पूर्ण

अटल अंतरभूत bool bset_written(काष्ठा btree_keys *b, काष्ठा bset_tree *t)
अणु
	वापस t <= b->set + b->nsets - b->last_set_unwritten;
पूर्ण

अटल अंतरभूत bool bkey_written(काष्ठा btree_keys *b, काष्ठा bkey *k)
अणु
	वापस !b->last_set_unwritten || k < b->set[b->nsets].data->start;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bset_byte_offset(काष्ठा btree_keys *b,
					    काष्ठा bset *i)
अणु
	वापस ((माप_प्रकार) i) - ((माप_प्रकार) b->set->data);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bset_sector_offset(काष्ठा btree_keys *b,
					      काष्ठा bset *i)
अणु
	वापस bset_byte_offset(b, i) >> 9;
पूर्ण

#घोषणा __set_bytes(i, k)	(माप(*(i)) + (k) * माप(uपूर्णांक64_t))
#घोषणा set_bytes(i)		__set_bytes(i, i->keys)

#घोषणा __set_blocks(i, k, block_bytes)				\
	DIV_ROUND_UP(__set_bytes(i, k), block_bytes)
#घोषणा set_blocks(i, block_bytes)				\
	__set_blocks(i, (i)->keys, block_bytes)

अटल अंतरभूत माप_प्रकार bch_btree_keys_u64s_reमुख्यing(काष्ठा btree_keys *b)
अणु
	काष्ठा bset_tree *t = bset_tree_last(b);

	BUG_ON((PAGE_SIZE << b->page_order) <
	       (bset_byte_offset(b, t->data) + set_bytes(t->data)));

	अगर (!b->last_set_unwritten)
		वापस 0;

	वापस ((PAGE_SIZE << b->page_order) -
		(bset_byte_offset(b, t->data) + set_bytes(t->data))) /
		माप(u64);
पूर्ण

अटल अंतरभूत काष्ठा bset *bset_next_set(काष्ठा btree_keys *b,
					 अचिन्हित पूर्णांक block_bytes)
अणु
	काष्ठा bset *i = bset_tree_last(b)->data;

	वापस ((व्योम *) i) + roundup(set_bytes(i), block_bytes);
पूर्ण

व्योम bch_btree_keys_मुक्त(काष्ठा btree_keys *b);
पूर्णांक bch_btree_keys_alloc(काष्ठा btree_keys *b, अचिन्हित पूर्णांक page_order,
			 gfp_t gfp);
व्योम bch_btree_keys_init(काष्ठा btree_keys *b, स्थिर काष्ठा btree_keys_ops *ops,
			 bool *expensive_debug_checks);

व्योम bch_bset_init_next(काष्ठा btree_keys *b, काष्ठा bset *i, uपूर्णांक64_t magic);
व्योम bch_bset_build_written_tree(काष्ठा btree_keys *b);
व्योम bch_bset_fix_invalidated_key(काष्ठा btree_keys *b, काष्ठा bkey *k);
bool bch_bkey_try_merge(काष्ठा btree_keys *b, काष्ठा bkey *l, काष्ठा bkey *r);
व्योम bch_bset_insert(काष्ठा btree_keys *b, काष्ठा bkey *where,
		     काष्ठा bkey *insert);
अचिन्हित पूर्णांक bch_btree_insert_key(काष्ठा btree_keys *b, काष्ठा bkey *k,
			      काष्ठा bkey *replace_key);

क्रमागत अणु
	BTREE_INSERT_STATUS_NO_INSERT = 0,
	BTREE_INSERT_STATUS_INSERT,
	BTREE_INSERT_STATUS_BACK_MERGE,
	BTREE_INSERT_STATUS_OVERWROTE,
	BTREE_INSERT_STATUS_FRONT_MERGE,
पूर्ण;

/* Btree key iteration */

काष्ठा btree_iter अणु
	माप_प्रकार size, used;
#अगर_घोषित CONFIG_BCACHE_DEBUG
	काष्ठा btree_keys *b;
#पूर्ण_अगर
	काष्ठा btree_iter_set अणु
		काष्ठा bkey *k, *end;
	पूर्ण data[MAX_BSETS];
पूर्ण;

प्रकार bool (*ptr_filter_fn)(काष्ठा btree_keys *b, स्थिर काष्ठा bkey *k);

काष्ठा bkey *bch_btree_iter_next(काष्ठा btree_iter *iter);
काष्ठा bkey *bch_btree_iter_next_filter(काष्ठा btree_iter *iter,
					काष्ठा btree_keys *b,
					ptr_filter_fn fn);

व्योम bch_btree_iter_push(काष्ठा btree_iter *iter, काष्ठा bkey *k,
			 काष्ठा bkey *end);
काष्ठा bkey *bch_btree_iter_init(काष्ठा btree_keys *b,
				 काष्ठा btree_iter *iter,
				 काष्ठा bkey *search);

काष्ठा bkey *__bch_bset_search(काष्ठा btree_keys *b, काष्ठा bset_tree *t,
			       स्थिर काष्ठा bkey *search);

/*
 * Returns the first key that is strictly greater than search
 */
अटल अंतरभूत काष्ठा bkey *bch_bset_search(काष्ठा btree_keys *b,
					   काष्ठा bset_tree *t,
					   स्थिर काष्ठा bkey *search)
अणु
	वापस search ? __bch_bset_search(b, t, search) : t->data->start;
पूर्ण

#घोषणा क्रम_each_key_filter(b, k, iter, filter)				\
	क्रम (bch_btree_iter_init((b), (iter), शून्य);			\
	     ((k) = bch_btree_iter_next_filter((iter), (b), filter));)

#घोषणा क्रम_each_key(b, k, iter)					\
	क्रम (bch_btree_iter_init((b), (iter), शून्य);			\
	     ((k) = bch_btree_iter_next(iter));)

/* Sorting */

काष्ठा bset_sort_state अणु
	mempool_t		pool;

	अचिन्हित पूर्णांक		page_order;
	अचिन्हित पूर्णांक		crit_factor;

	काष्ठा समय_stats	समय;
पूर्ण;

व्योम bch_bset_sort_state_मुक्त(काष्ठा bset_sort_state *state);
पूर्णांक bch_bset_sort_state_init(काष्ठा bset_sort_state *state,
			     अचिन्हित पूर्णांक page_order);
व्योम bch_btree_sort_lazy(काष्ठा btree_keys *b, काष्ठा bset_sort_state *state);
व्योम bch_btree_sort_पूर्णांकo(काष्ठा btree_keys *b, काष्ठा btree_keys *new,
			 काष्ठा bset_sort_state *state);
व्योम bch_btree_sort_and_fix_extents(काष्ठा btree_keys *b,
				    काष्ठा btree_iter *iter,
				    काष्ठा bset_sort_state *state);
व्योम bch_btree_sort_partial(काष्ठा btree_keys *b, अचिन्हित पूर्णांक start,
			    काष्ठा bset_sort_state *state);

अटल अंतरभूत व्योम bch_btree_sort(काष्ठा btree_keys *b,
				  काष्ठा bset_sort_state *state)
अणु
	bch_btree_sort_partial(b, 0, state);
पूर्ण

काष्ठा bset_stats अणु
	माप_प्रकार sets_written, sets_unwritten;
	माप_प्रकार bytes_written, bytes_unwritten;
	माप_प्रकार भग्नs, failed;
पूर्ण;

व्योम bch_btree_keys_stats(काष्ठा btree_keys *b, काष्ठा bset_stats *state);

/* Bkey utility code */

#घोषणा bset_bkey_last(i)	bkey_idx((काष्ठा bkey *) (i)->d, \
					 (अचिन्हित पूर्णांक)(i)->keys)

अटल अंतरभूत काष्ठा bkey *bset_bkey_idx(काष्ठा bset *i, अचिन्हित पूर्णांक idx)
अणु
	वापस bkey_idx(i->start, idx);
पूर्ण

अटल अंतरभूत व्योम bkey_init(काष्ठा bkey *k)
अणु
	*k = ZERO_KEY;
पूर्ण

अटल __always_अंतरभूत पूर्णांक64_t bkey_cmp(स्थिर काष्ठा bkey *l,
					स्थिर काष्ठा bkey *r)
अणु
	वापस unlikely(KEY_INODE(l) != KEY_INODE(r))
		? (पूर्णांक64_t) KEY_INODE(l) - (पूर्णांक64_t) KEY_INODE(r)
		: (पूर्णांक64_t) KEY_OFFSET(l) - (पूर्णांक64_t) KEY_OFFSET(r);
पूर्ण

व्योम bch_bkey_copy_single_ptr(काष्ठा bkey *dest, स्थिर काष्ठा bkey *src,
			      अचिन्हित पूर्णांक i);
bool __bch_cut_front(स्थिर काष्ठा bkey *where, काष्ठा bkey *k);
bool __bch_cut_back(स्थिर काष्ठा bkey *where, काष्ठा bkey *k);

अटल अंतरभूत bool bch_cut_front(स्थिर काष्ठा bkey *where, काष्ठा bkey *k)
अणु
	BUG_ON(bkey_cmp(where, k) > 0);
	वापस __bch_cut_front(where, k);
पूर्ण

अटल अंतरभूत bool bch_cut_back(स्थिर काष्ठा bkey *where, काष्ठा bkey *k)
अणु
	BUG_ON(bkey_cmp(where, &START_KEY(k)) < 0);
	वापस __bch_cut_back(where, k);
पूर्ण

/*
 * Poपूर्णांकer '*preceding_key_p' poपूर्णांकs to a memory object to store preceding
 * key of k. If the preceding key करोes not exist, set '*preceding_key_p' to
 * शून्य. So the caller of preceding_key() needs to take care of memory
 * which '*preceding_key_p' poपूर्णांकed to beक्रमe calling preceding_key().
 * Currently the only caller of preceding_key() is bch_btree_insert_key(),
 * and it poपूर्णांकs to an on-stack variable, so the memory release is handled
 * by stackframe itself.
 */
अटल अंतरभूत व्योम preceding_key(काष्ठा bkey *k, काष्ठा bkey **preceding_key_p)
अणु
	अगर (KEY_INODE(k) || KEY_OFFSET(k)) अणु
		(**preceding_key_p) = KEY(KEY_INODE(k), KEY_OFFSET(k), 0);
		अगर (!(*preceding_key_p)->low)
			(*preceding_key_p)->high--;
		(*preceding_key_p)->low--;
	पूर्ण अन्यथा अणु
		(*preceding_key_p) = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत bool bch_ptr_invalid(काष्ठा btree_keys *b, स्थिर काष्ठा bkey *k)
अणु
	वापस b->ops->key_invalid(b, k);
पूर्ण

अटल अंतरभूत bool bch_ptr_bad(काष्ठा btree_keys *b, स्थिर काष्ठा bkey *k)
अणु
	वापस b->ops->key_bad(b, k);
पूर्ण

अटल अंतरभूत व्योम bch_bkey_to_text(काष्ठा btree_keys *b, अक्षर *buf,
				    माप_प्रकार size, स्थिर काष्ठा bkey *k)
अणु
	वापस b->ops->key_to_text(buf, size, k);
पूर्ण

अटल अंतरभूत bool bch_bkey_equal_header(स्थिर काष्ठा bkey *l,
					 स्थिर काष्ठा bkey *r)
अणु
	वापस (KEY_सूचीTY(l) == KEY_सूचीTY(r) &&
		KEY_PTRS(l) == KEY_PTRS(r) &&
		KEY_CSUM(l) == KEY_CSUM(r));
पूर्ण

/* Keylists */

काष्ठा keylist अणु
	जोड़ अणु
		काष्ठा bkey		*keys;
		uपूर्णांक64_t		*keys_p;
	पूर्ण;
	जोड़ अणु
		काष्ठा bkey		*top;
		uपूर्णांक64_t		*top_p;
	पूर्ण;

	/* Enough room क्रम btree_split's keys without पुनः_स्मृति */
#घोषणा KEYLIST_INLINE		16
	uपूर्णांक64_t		अंतरभूत_keys[KEYLIST_INLINE];
पूर्ण;

अटल अंतरभूत व्योम bch_keylist_init(काष्ठा keylist *l)
अणु
	l->top_p = l->keys_p = l->अंतरभूत_keys;
पूर्ण

अटल अंतरभूत व्योम bch_keylist_init_single(काष्ठा keylist *l, काष्ठा bkey *k)
अणु
	l->keys = k;
	l->top = bkey_next(k);
पूर्ण

अटल अंतरभूत व्योम bch_keylist_push(काष्ठा keylist *l)
अणु
	l->top = bkey_next(l->top);
पूर्ण

अटल अंतरभूत व्योम bch_keylist_add(काष्ठा keylist *l, काष्ठा bkey *k)
अणु
	bkey_copy(l->top, k);
	bch_keylist_push(l);
पूर्ण

अटल अंतरभूत bool bch_keylist_empty(काष्ठा keylist *l)
अणु
	वापस l->top == l->keys;
पूर्ण

अटल अंतरभूत व्योम bch_keylist_reset(काष्ठा keylist *l)
अणु
	l->top = l->keys;
पूर्ण

अटल अंतरभूत व्योम bch_keylist_मुक्त(काष्ठा keylist *l)
अणु
	अगर (l->keys_p != l->अंतरभूत_keys)
		kमुक्त(l->keys_p);
पूर्ण

अटल अंतरभूत माप_प्रकार bch_keylist_nkeys(काष्ठा keylist *l)
अणु
	वापस l->top_p - l->keys_p;
पूर्ण

अटल अंतरभूत माप_प्रकार bch_keylist_bytes(काष्ठा keylist *l)
अणु
	वापस bch_keylist_nkeys(l) * माप(uपूर्णांक64_t);
पूर्ण

काष्ठा bkey *bch_keylist_pop(काष्ठा keylist *l);
व्योम bch_keylist_pop_front(काष्ठा keylist *l);
पूर्णांक __bch_keylist_पुनः_स्मृति(काष्ठा keylist *l, अचिन्हित पूर्णांक u64s);

/* Debug stuff */

#अगर_घोषित CONFIG_BCACHE_DEBUG

पूर्णांक __bch_count_data(काष्ठा btree_keys *b);
व्योम __म_लिखो(2, 3) __bch_check_keys(काष्ठा btree_keys *b,
				     स्थिर अक्षर *fmt,
				     ...);
व्योम bch_dump_bset(काष्ठा btree_keys *b, काष्ठा bset *i, अचिन्हित पूर्णांक set);
व्योम bch_dump_bucket(काष्ठा btree_keys *b);

#अन्यथा

अटल अंतरभूत पूर्णांक __bch_count_data(काष्ठा btree_keys *b) अणु वापस -1; पूर्ण
अटल अंतरभूत व्योम __म_लिखो(2, 3)
	__bch_check_keys(काष्ठा btree_keys *b, स्थिर अक्षर *fmt, ...) अणुपूर्ण
अटल अंतरभूत व्योम bch_dump_bucket(काष्ठा btree_keys *b) अणुपूर्ण
व्योम bch_dump_bset(काष्ठा btree_keys *b, काष्ठा bset *i, अचिन्हित पूर्णांक set);

#पूर्ण_अगर

अटल अंतरभूत bool btree_keys_expensive_checks(काष्ठा btree_keys *b)
अणु
#अगर_घोषित CONFIG_BCACHE_DEBUG
	वापस *b->expensive_debug_checks;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक bch_count_data(काष्ठा btree_keys *b)
अणु
	वापस btree_keys_expensive_checks(b) ? __bch_count_data(b) : -1;
पूर्ण

#घोषणा bch_check_keys(b, ...)						\
करो अणु									\
	अगर (btree_keys_expensive_checks(b))				\
		__bch_check_keys(b, __VA_ARGS__);			\
पूर्ण जबतक (0)

#पूर्ण_अगर
