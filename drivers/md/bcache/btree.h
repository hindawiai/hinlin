<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_BTREE_H
#घोषणा _BCACHE_BTREE_H

/*
 * THE BTREE:
 *
 * At a high level, bcache's btree is relatively standard b+ tree. All keys and
 * poपूर्णांकers are in the leaves; पूर्णांकerior nodes only have poपूर्णांकers to the child
 * nodes.
 *
 * In the पूर्णांकerior nodes, a काष्ठा bkey always poपूर्णांकs to a child btree node, and
 * the key is the highest key in the child node - except that the highest key in
 * an पूर्णांकerior node is always MAX_KEY. The size field refers to the size on disk
 * of the child node - this would allow us to have variable sized btree nodes
 * (handy क्रम keeping the depth of the btree 1 by expanding just the root).
 *
 * Btree nodes are themselves log काष्ठाured, but this is hidden fairly
 * thoroughly. Btree nodes on disk will in practice have extents that overlap
 * (because they were written at dअगरferent बार), but in memory we never have
 * overlapping extents - when we पढ़ो in a btree node from disk, the first thing
 * we करो is resort all the sets of keys with a mergesort, and in the same pass
 * we check क्रम overlapping extents and adjust them appropriately.
 *
 * काष्ठा btree_op is a central पूर्णांकerface to the btree code. It's used क्रम
 * specअगरying पढ़ो vs. ग_लिखो locking, and the embedded closure is used क्रम
 * रुकोing on IO or reserve memory.
 *
 * BTREE CACHE:
 *
 * Btree nodes are cached in memory; traversing the btree might require पढ़ोing
 * in btree nodes which is handled mostly transparently.
 *
 * bch_btree_node_get() looks up a btree node in the cache and पढ़ोs it in from
 * disk अगर necessary. This function is almost never called directly though - the
 * btree() macro is used to get a btree node, call some function on it, and
 * unlock the node after the function वापसs.
 *
 * The root is special हालd - it's taken out of the cache's lru (thus pinning
 * it in memory), so we can find the root of the btree by just dereferencing a
 * poपूर्णांकer instead of looking it up in the cache. This makes locking a bit
 * tricky, since the root poपूर्णांकer is रक्षित by the lock in the btree node it
 * poपूर्णांकs to - the btree_root() macro handles this.
 *
 * In various places we must be able to allocate memory क्रम multiple btree nodes
 * in order to make क्रमward progress. To करो this we use the btree cache itself
 * as a reserve; अगर __get_मुक्त_pages() fails, we'll find a node in the btree
 * cache we can reuse. We can't allow more than one thपढ़ो to be करोing this at a
 * समय, so there's a lock, implemented by a poपूर्णांकer to the btree_op closure -
 * this allows the btree_root() macro to implicitly release this lock.
 *
 * BTREE IO:
 *
 * Btree nodes never have to be explicitly पढ़ो in; bch_btree_node_get() handles
 * this.
 *
 * For writing, we have two btree_ग_लिखो काष्ठाs embeddded in काष्ठा btree - one
 * ग_लिखो in flight, and one being set up, and we toggle between them.
 *
 * Writing is करोne with a single function -  bch_btree_ग_लिखो() really serves two
 * dअगरferent purposes and should be broken up पूर्णांकo two dअगरferent functions. When
 * passing now = false, it merely indicates that the node is now dirty - calling
 * it ensures that the dirty keys will be written at some poपूर्णांक in the future.
 *
 * When passing now = true, bch_btree_ग_लिखो() causes a ग_लिखो to happen
 * "immediately" (अगर there was alपढ़ोy a ग_लिखो in flight, it'll cause the ग_लिखो
 * to happen as soon as the previous ग_लिखो completes). It वापसs immediately
 * though - but it takes a refcount on the closure in काष्ठा btree_op you passed
 * to it, so a closure_sync() later can be used to रुको क्रम the ग_लिखो to
 * complete.
 *
 * This is handy because btree_split() and garbage collection can issue ग_लिखोs
 * in parallel, reducing the amount of समय they have to hold ग_लिखो locks.
 *
 * LOCKING:
 *
 * When traversing the btree, we may need ग_लिखो locks starting at some level -
 * inserting a key पूर्णांकo the btree will typically only require a ग_लिखो lock on
 * the leaf node.
 *
 * This is specअगरied with the lock field in काष्ठा btree_op; lock = 0 means we
 * take ग_लिखो locks at level <= 0, i.e. only leaf nodes. bch_btree_node_get()
 * checks this field and वापसs the node with the appropriate lock held.
 *
 * If, after traversing the btree, the insertion code discovers it has to split
 * then it must restart from the root and take new locks - to करो this it changes
 * the lock field and वापसs -EINTR, which causes the btree_root() macro to
 * loop.
 *
 * Handling cache misses require a dअगरferent mechanism क्रम upgrading to a ग_लिखो
 * lock. We करो cache lookups with only a पढ़ो lock held, but अगर we get a cache
 * miss and we wish to insert this data पूर्णांकo the cache, we have to insert a
 * placeholder key to detect races - otherwise, we could race with a ग_लिखो and
 * overग_लिखो the data that was just written to the cache with stale data from
 * the backing device.
 *
 * For this we use a sequence number that ग_लिखो locks and unlocks increment - to
 * insert the check key it unlocks the btree node and then takes a ग_लिखो lock,
 * and fails अगर the sequence number करोesn't match.
 */

#समावेश "bset.h"
#समावेश "debug.h"

काष्ठा btree_ग_लिखो अणु
	atomic_t		*journal;

	/* If btree_split() मुक्तs a btree node, it ग_लिखोs a new poपूर्णांकer to that
	 * btree node indicating it was मुक्तd; it takes a refcount on
	 * c->prio_blocked because we can't ग_लिखो the gens until the new
	 * poपूर्णांकer is on disk. This allows btree_ग_लिखो_endio() to release the
	 * refcount that btree_split() took.
	 */
	पूर्णांक			prio_blocked;
पूर्ण;

काष्ठा btree अणु
	/* Hottest entries first */
	काष्ठा hlist_node	hash;

	/* Key/poपूर्णांकer क्रम this btree node */
	BKEY_PADDED(key);

	अचिन्हित दीर्घ		seq;
	काष्ठा rw_semaphore	lock;
	काष्ठा cache_set	*c;
	काष्ठा btree		*parent;

	काष्ठा mutex		ग_लिखो_lock;

	अचिन्हित दीर्घ		flags;
	uपूर्णांक16_t		written;	/* would be nice to समाप्त */
	uपूर्णांक8_t			level;

	काष्ठा btree_keys	keys;

	/* For outstanding btree ग_लिखोs, used as a lock - protects ग_लिखो_idx */
	काष्ठा closure		io;
	काष्ठा semaphore	io_mutex;

	काष्ठा list_head	list;
	काष्ठा delayed_work	work;

	काष्ठा btree_ग_लिखो	ग_लिखोs[2];
	काष्ठा bio		*bio;
पूर्ण;




#घोषणा BTREE_FLAG(flag)						\
अटल अंतरभूत bool btree_node_ ## flag(काष्ठा btree *b)			\
अणु	वापस test_bit(BTREE_NODE_ ## flag, &b->flags); पूर्ण		\
									\
अटल अंतरभूत व्योम set_btree_node_ ## flag(काष्ठा btree *b)		\
अणु	set_bit(BTREE_NODE_ ## flag, &b->flags); पूर्ण

क्रमागत btree_flags अणु
	BTREE_NODE_io_error,
	BTREE_NODE_dirty,
	BTREE_NODE_ग_लिखो_idx,
	BTREE_NODE_journal_flush,
पूर्ण;

BTREE_FLAG(io_error);
BTREE_FLAG(dirty);
BTREE_FLAG(ग_लिखो_idx);
BTREE_FLAG(journal_flush);

अटल अंतरभूत काष्ठा btree_ग_लिखो *btree_current_ग_लिखो(काष्ठा btree *b)
अणु
	वापस b->ग_लिखोs + btree_node_ग_लिखो_idx(b);
पूर्ण

अटल अंतरभूत काष्ठा btree_ग_लिखो *btree_prev_ग_लिखो(काष्ठा btree *b)
अणु
	वापस b->ग_लिखोs + (btree_node_ग_लिखो_idx(b) ^ 1);
पूर्ण

अटल अंतरभूत काष्ठा bset *btree_bset_first(काष्ठा btree *b)
अणु
	वापस b->keys.set->data;
पूर्ण

अटल अंतरभूत काष्ठा bset *btree_bset_last(काष्ठा btree *b)
अणु
	वापस bset_tree_last(&b->keys)->data;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bset_block_offset(काष्ठा btree *b, काष्ठा bset *i)
अणु
	वापस bset_sector_offset(&b->keys, i) >> b->c->block_bits;
पूर्ण

अटल अंतरभूत व्योम set_gc_sectors(काष्ठा cache_set *c)
अणु
	atomic_set(&c->sectors_to_gc, c->cache->sb.bucket_size * c->nbuckets / 16);
पूर्ण

व्योम bkey_put(काष्ठा cache_set *c, काष्ठा bkey *k);

/* Looping macros */

#घोषणा क्रम_each_cached_btree(b, c, iter)				\
	क्रम (iter = 0;							\
	     iter < ARRAY_SIZE((c)->bucket_hash);			\
	     iter++)							\
		hlist_क्रम_each_entry_rcu((b), (c)->bucket_hash + iter, hash)

/* Recursing करोwn the btree */

काष्ठा btree_op अणु
	/* क्रम रुकोing on btree reserve in btree_split() */
	रुको_queue_entry_t		रुको;

	/* Btree level at which we start taking ग_लिखो locks */
	लघु			lock;

	अचिन्हित पूर्णांक		insert_collision:1;
पूर्ण;

काष्ठा btree_check_state;
काष्ठा btree_check_info अणु
	काष्ठा btree_check_state	*state;
	काष्ठा task_काष्ठा		*thपढ़ो;
	पूर्णांक				result;
पूर्ण;

#घोषणा BCH_BTR_CHKTHREAD_MAX	64
काष्ठा btree_check_state अणु
	काष्ठा cache_set		*c;
	पूर्णांक				total_thपढ़ोs;
	पूर्णांक				key_idx;
	spinlock_t			idx_lock;
	atomic_t			started;
	atomic_t			enough;
	रुको_queue_head_t		रुको;
	काष्ठा btree_check_info		infos[BCH_BTR_CHKTHREAD_MAX];
पूर्ण;

अटल अंतरभूत व्योम bch_btree_op_init(काष्ठा btree_op *op, पूर्णांक ग_लिखो_lock_level)
अणु
	स_रखो(op, 0, माप(काष्ठा btree_op));
	init_रुको(&op->रुको);
	op->lock = ग_लिखो_lock_level;
पूर्ण

अटल अंतरभूत व्योम rw_lock(bool w, काष्ठा btree *b, पूर्णांक level)
अणु
	w ? करोwn_ग_लिखो_nested(&b->lock, level + 1)
	  : करोwn_पढ़ो_nested(&b->lock, level + 1);
	अगर (w)
		b->seq++;
पूर्ण

अटल अंतरभूत व्योम rw_unlock(bool w, काष्ठा btree *b)
अणु
	अगर (w)
		b->seq++;
	(w ? up_ग_लिखो : up_पढ़ो)(&b->lock);
पूर्ण

व्योम bch_btree_node_पढ़ो_करोne(काष्ठा btree *b);
व्योम __bch_btree_node_ग_लिखो(काष्ठा btree *b, काष्ठा closure *parent);
व्योम bch_btree_node_ग_लिखो(काष्ठा btree *b, काष्ठा closure *parent);

व्योम bch_btree_set_root(काष्ठा btree *b);
काष्ठा btree *__bch_btree_node_alloc(काष्ठा cache_set *c, काष्ठा btree_op *op,
				     पूर्णांक level, bool रुको,
				     काष्ठा btree *parent);
काष्ठा btree *bch_btree_node_get(काष्ठा cache_set *c, काष्ठा btree_op *op,
				 काष्ठा bkey *k, पूर्णांक level, bool ग_लिखो,
				 काष्ठा btree *parent);

पूर्णांक bch_btree_insert_check_key(काष्ठा btree *b, काष्ठा btree_op *op,
			       काष्ठा bkey *check_key);
पूर्णांक bch_btree_insert(काष्ठा cache_set *c, काष्ठा keylist *keys,
		     atomic_t *journal_ref, काष्ठा bkey *replace_key);

पूर्णांक bch_gc_thपढ़ो_start(काष्ठा cache_set *c);
व्योम bch_initial_gc_finish(काष्ठा cache_set *c);
व्योम bch_moving_gc(काष्ठा cache_set *c);
पूर्णांक bch_btree_check(काष्ठा cache_set *c);
व्योम bch_initial_mark_key(काष्ठा cache_set *c, पूर्णांक level, काष्ठा bkey *k);

अटल अंतरभूत व्योम wake_up_gc(काष्ठा cache_set *c)
अणु
	wake_up(&c->gc_रुको);
पूर्ण

अटल अंतरभूत व्योम क्रमce_wake_up_gc(काष्ठा cache_set *c)
अणु
	/*
	 * Garbage collection thपढ़ो only works when sectors_to_gc < 0,
	 * calling wake_up_gc() won't start gc thपढ़ो अगर sectors_to_gc is
	 * not a nagetive value.
	 * Thereक्रमe sectors_to_gc is set to -1 here, beक्रमe waking up
	 * gc thपढ़ो by calling wake_up_gc(). Then gc_should_run() will
	 * give a chance to permit gc thपढ़ो to run. "Give a chance" means
	 * beक्रमe going पूर्णांकo gc_should_run(), there is still possibility
	 * that c->sectors_to_gc being set to other positive value. So
	 * this routine won't 100% make sure gc thपढ़ो will be woken up
	 * to run.
	 */
	atomic_set(&c->sectors_to_gc, -1);
	wake_up_gc(c);
पूर्ण

/*
 * These macros are क्रम recursing करोwn the btree - they handle the details of
 * locking and looking up nodes in the cache क्रम you. They're best treated as
 * mere syntax when पढ़ोing code that uses them.
 *
 * op->lock determines whether we take a पढ़ो or a ग_लिखो lock at a given depth.
 * If you've got a read lock and find that you need a write lock (i.e. you're
 * going to have to split), set op->lock and वापस -EINTR; btree_root() will
 * call you again and you'll have the correct lock.
 */

/**
 * btree - recurse करोwn the btree on a specअगरied key
 * @fn:		function to call, which will be passed the child node
 * @key:	key to recurse on
 * @b:		parent btree node
 * @op:		poपूर्णांकer to काष्ठा btree_op
 */
#घोषणा bcache_btree(fn, key, b, op, ...)				\
(अणु									\
	पूर्णांक _r, l = (b)->level - 1;					\
	bool _w = l <= (op)->lock;					\
	काष्ठा btree *_child = bch_btree_node_get((b)->c, op, key, l,	\
						  _w, b);		\
	अगर (!IS_ERR(_child)) अणु						\
		_r = bch_btree_ ## fn(_child, op, ##__VA_ARGS__);	\
		rw_unlock(_w, _child);					\
	पूर्ण अन्यथा								\
		_r = PTR_ERR(_child);					\
	_r;								\
पूर्ण)

/**
 * btree_root - call a function on the root of the btree
 * @fn:		function to call, which will be passed the child node
 * @c:		cache set
 * @op:		poपूर्णांकer to काष्ठा btree_op
 */
#घोषणा bcache_btree_root(fn, c, op, ...)				\
(अणु									\
	पूर्णांक _r = -EINTR;						\
	करो अणु								\
		काष्ठा btree *_b = (c)->root;				\
		bool _w = insert_lock(op, _b);				\
		rw_lock(_w, _b, _b->level);				\
		अगर (_b == (c)->root &&					\
		    _w == insert_lock(op, _b)) अणु			\
			_r = bch_btree_ ## fn(_b, op, ##__VA_ARGS__);	\
		पूर्ण							\
		rw_unlock(_w, _b);					\
		bch_cannibalize_unlock(c);                              \
		अगर (_r == -EINTR)                                       \
			schedule();                                     \
	पूर्ण जबतक (_r == -EINTR);                                         \
									\
	finish_रुको(&(c)->btree_cache_रुको, &(op)->रुको);               \
	_r;                                                             \
पूर्ण)

#घोषणा MAP_DONE	0
#घोषणा MAP_CONTINUE	1

#घोषणा MAP_ALL_NODES	0
#घोषणा MAP_LEAF_NODES	1

#घोषणा MAP_END_KEY	1

प्रकार पूर्णांक (btree_map_nodes_fn)(काष्ठा btree_op *b_op, काष्ठा btree *b);
पूर्णांक __bch_btree_map_nodes(काष्ठा btree_op *op, काष्ठा cache_set *c,
			  काष्ठा bkey *from, btree_map_nodes_fn *fn, पूर्णांक flags);

अटल अंतरभूत पूर्णांक bch_btree_map_nodes(काष्ठा btree_op *op, काष्ठा cache_set *c,
				      काष्ठा bkey *from, btree_map_nodes_fn *fn)
अणु
	वापस __bch_btree_map_nodes(op, c, from, fn, MAP_ALL_NODES);
पूर्ण

अटल अंतरभूत पूर्णांक bch_btree_map_leaf_nodes(काष्ठा btree_op *op,
					   काष्ठा cache_set *c,
					   काष्ठा bkey *from,
					   btree_map_nodes_fn *fn)
अणु
	वापस __bch_btree_map_nodes(op, c, from, fn, MAP_LEAF_NODES);
पूर्ण

प्रकार पूर्णांक (btree_map_keys_fn)(काष्ठा btree_op *op, काष्ठा btree *b,
				काष्ठा bkey *k);
पूर्णांक bch_btree_map_keys(काष्ठा btree_op *op, काष्ठा cache_set *c,
		       काष्ठा bkey *from, btree_map_keys_fn *fn, पूर्णांक flags);
पूर्णांक bch_btree_map_keys_recurse(काष्ठा btree *b, काष्ठा btree_op *op,
			       काष्ठा bkey *from, btree_map_keys_fn *fn,
			       पूर्णांक flags);

प्रकार bool (keybuf_pred_fn)(काष्ठा keybuf *buf, काष्ठा bkey *k);

व्योम bch_keybuf_init(काष्ठा keybuf *buf);
व्योम bch_refill_keybuf(काष्ठा cache_set *c, काष्ठा keybuf *buf,
		       काष्ठा bkey *end, keybuf_pred_fn *pred);
bool bch_keybuf_check_overlapping(काष्ठा keybuf *buf, काष्ठा bkey *start,
				  काष्ठा bkey *end);
व्योम bch_keybuf_del(काष्ठा keybuf *buf, काष्ठा keybuf_key *w);
काष्ठा keybuf_key *bch_keybuf_next(काष्ठा keybuf *buf);
काष्ठा keybuf_key *bch_keybuf_next_rescan(काष्ठा cache_set *c,
					  काष्ठा keybuf *buf,
					  काष्ठा bkey *end,
					  keybuf_pred_fn *pred);
व्योम bch_update_bucket_in_use(काष्ठा cache_set *c, काष्ठा gc_stat *stats);
#पूर्ण_अगर
