<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Kent Overstreet <kent.overstreet@gmail.com>
 *
 * Uses a block device as cache क्रम other block devices; optimized क्रम SSDs.
 * All allocation is करोne in buckets, which should match the erase block size
 * of the device.
 *
 * Buckets containing cached data are kept on a heap sorted by priority;
 * bucket priority is increased on cache hit, and periodically all the buckets
 * on the heap have their priority scaled करोwn. This currently is just used as
 * an LRU but in the future should allow क्रम more पूर्णांकelligent heuristics.
 *
 * Buckets have an 8 bit counter; मुक्तing is accomplished by incrementing the
 * counter. Garbage collection is used to हटाओ stale poपूर्णांकers.
 *
 * Indexing is करोne via a btree; nodes are not necessarily fully sorted, rather
 * as keys are inserted we only sort the pages that have not yet been written.
 * When garbage collection is run, we resort the entire node.
 *
 * All configuration is करोne via sysfs; see Documentation/admin-guide/bcache.rst.
 */

#समावेश "bcache.h"
#समावेश "btree.h"
#समावेश "debug.h"
#समावेश "extents.h"

#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/hash.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/rculist.h>
#समावेश <linux/delay.h>
#समावेश <trace/events/bcache.h>

/*
 * Toकरो:
 * रेजिस्टर_bcache: Return errors out to userspace correctly
 *
 * Writeback: करोn't undirty key until after a cache flush
 *
 * Create an iterator क्रम key poपूर्णांकers
 *
 * On btree ग_लिखो error, mark bucket such that it won't be मुक्तd from the cache
 *
 * Journalling:
 *   Check क्रम bad keys in replay
 *   Propagate barriers
 *   Refcount journal entries in journal_replay
 *
 * Garbage collection:
 *   Finish incremental gc
 *   Gc should मुक्त old UUIDs, data क्रम invalid UUIDs
 *
 * Provide a way to list backing device UUIDs we have data cached क्रम, and
 * probably how दीर्घ it's been since we've seen them, and a way to invalidate
 * dirty data क्रम devices that will never be attached again
 *
 * Keep 1 min/5 min/15 min statistics of how busy a block device has been, so
 * that based on that and how much dirty data we have we can keep ग_लिखोback
 * from being starved
 *
 * Add a tracepoपूर्णांक or somesuch to watch क्रम ग_लिखोback starvation
 *
 * When btree depth > 1 and splitting an पूर्णांकerior node, we have to make sure
 * alloc_bucket() cannot fail. This should be true but is not completely
 * obvious.
 *
 * Plugging?
 *
 * If data ग_लिखो is less than hard sector size of ssd, round up offset in खोलो
 * bucket to the next whole sector
 *
 * Superblock needs to be fleshed out क्रम multiple cache devices
 *
 * Add a sysfs tunable क्रम the number of ग_लिखोback IOs in flight
 *
 * Add a sysfs tunable क्रम the number of खोलो data buckets
 *
 * IO tracking: Can we track when one process is करोing io on behalf of another?
 * IO tracking: Don't use just an average, weigh more recent stuff higher
 *
 * Test module load/unload
 */

#घोषणा MAX_NEED_GC		64
#घोषणा MAX_SAVE_PRIO		72
#घोषणा MAX_GC_TIMES		100
#घोषणा MIN_GC_NODES		100
#घोषणा GC_SLEEP_MS		100

#घोषणा PTR_सूचीTY_BIT		(((uपूर्णांक64_t) 1 << 36))

#घोषणा PTR_HASH(c, k)							\
	(((k)->ptr[0] >> c->bucket_bits) | PTR_GEN(k, 0))

अटल काष्ठा workqueue_काष्ठा *btree_io_wq;

#घोषणा insert_lock(s, b)	((b)->level <= (s)->lock)


अटल अंतरभूत काष्ठा bset *ग_लिखो_block(काष्ठा btree *b)
अणु
	वापस ((व्योम *) btree_bset_first(b)) + b->written * block_bytes(b->c->cache);
पूर्ण

अटल व्योम bch_btree_init_next(काष्ठा btree *b)
अणु
	/* If not a leaf node, always sort */
	अगर (b->level && b->keys.nsets)
		bch_btree_sort(&b->keys, &b->c->sort);
	अन्यथा
		bch_btree_sort_lazy(&b->keys, &b->c->sort);

	अगर (b->written < btree_blocks(b))
		bch_bset_init_next(&b->keys, ग_लिखो_block(b),
				   bset_magic(&b->c->cache->sb));

पूर्ण

/* Btree key manipulation */

व्योम bkey_put(काष्ठा cache_set *c, काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		अगर (ptr_available(c, k, i))
			atomic_dec_bug(&PTR_BUCKET(c, k, i)->pin);
पूर्ण

/* Btree IO */

अटल uपूर्णांक64_t btree_csum_set(काष्ठा btree *b, काष्ठा bset *i)
अणु
	uपूर्णांक64_t crc = b->key.ptr[0];
	व्योम *data = (व्योम *) i + 8, *end = bset_bkey_last(i);

	crc = bch_crc64_update(crc, data, end - data);
	वापस crc ^ 0xffffffffffffffffULL;
पूर्ण

व्योम bch_btree_node_पढ़ो_करोne(काष्ठा btree *b)
अणु
	स्थिर अक्षर *err = "bad btree header";
	काष्ठा bset *i = btree_bset_first(b);
	काष्ठा btree_iter *iter;

	/*
	 * c->fill_iter can allocate an iterator with more memory space
	 * than अटल MAX_BSETS.
	 * See the comment arount cache_set->fill_iter.
	 */
	iter = mempool_alloc(&b->c->fill_iter, GFP_NOIO);
	iter->size = b->c->cache->sb.bucket_size / b->c->cache->sb.block_size;
	iter->used = 0;

#अगर_घोषित CONFIG_BCACHE_DEBUG
	iter->b = &b->keys;
#पूर्ण_अगर

	अगर (!i->seq)
		जाओ err;

	क्रम (;
	     b->written < btree_blocks(b) && i->seq == b->keys.set[0].data->seq;
	     i = ग_लिखो_block(b)) अणु
		err = "unsupported bset version";
		अगर (i->version > BCACHE_BSET_VERSION)
			जाओ err;

		err = "bad btree header";
		अगर (b->written + set_blocks(i, block_bytes(b->c->cache)) >
		    btree_blocks(b))
			जाओ err;

		err = "bad magic";
		अगर (i->magic != bset_magic(&b->c->cache->sb))
			जाओ err;

		err = "bad checksum";
		चयन (i->version) अणु
		हाल 0:
			अगर (i->csum != csum_set(i))
				जाओ err;
			अवरोध;
		हाल BCACHE_BSET_VERSION:
			अगर (i->csum != btree_csum_set(b, i))
				जाओ err;
			अवरोध;
		पूर्ण

		err = "empty set";
		अगर (i != b->keys.set[0].data && !i->keys)
			जाओ err;

		bch_btree_iter_push(iter, i->start, bset_bkey_last(i));

		b->written += set_blocks(i, block_bytes(b->c->cache));
	पूर्ण

	err = "corrupted btree";
	क्रम (i = ग_लिखो_block(b);
	     bset_sector_offset(&b->keys, i) < KEY_SIZE(&b->key);
	     i = ((व्योम *) i) + block_bytes(b->c->cache))
		अगर (i->seq == b->keys.set[0].data->seq)
			जाओ err;

	bch_btree_sort_and_fix_extents(&b->keys, iter, &b->c->sort);

	i = b->keys.set[0].data;
	err = "short btree key";
	अगर (b->keys.set[0].size &&
	    bkey_cmp(&b->key, &b->keys.set[0].end) < 0)
		जाओ err;

	अगर (b->written < btree_blocks(b))
		bch_bset_init_next(&b->keys, ग_लिखो_block(b),
				   bset_magic(&b->c->cache->sb));
out:
	mempool_मुक्त(iter, &b->c->fill_iter);
	वापस;
err:
	set_btree_node_io_error(b);
	bch_cache_set_error(b->c, "%s at bucket %zu, block %u, %u keys",
			    err, PTR_BUCKET_NR(b->c, &b->key, 0),
			    bset_block_offset(b, i), i->keys);
	जाओ out;
पूर्ण

अटल व्योम btree_node_पढ़ो_endio(काष्ठा bio *bio)
अणु
	काष्ठा closure *cl = bio->bi_निजी;

	closure_put(cl);
पूर्ण

अटल व्योम bch_btree_node_पढ़ो(काष्ठा btree *b)
अणु
	uपूर्णांक64_t start_समय = local_घड़ी();
	काष्ठा closure cl;
	काष्ठा bio *bio;

	trace_bcache_btree_पढ़ो(b);

	closure_init_stack(&cl);

	bio = bch_bbio_alloc(b->c);
	bio->bi_iter.bi_size = KEY_SIZE(&b->key) << 9;
	bio->bi_end_io	= btree_node_पढ़ो_endio;
	bio->bi_निजी	= &cl;
	bio->bi_opf = REQ_OP_READ | REQ_META;

	bch_bio_map(bio, b->keys.set[0].data);

	bch_submit_bbio(bio, b->c, &b->key, 0);
	closure_sync(&cl);

	अगर (bio->bi_status)
		set_btree_node_io_error(b);

	bch_bbio_मुक्त(bio, b->c);

	अगर (btree_node_io_error(b))
		जाओ err;

	bch_btree_node_पढ़ो_करोne(b);
	bch_समय_stats_update(&b->c->btree_पढ़ो_समय, start_समय);

	वापस;
err:
	bch_cache_set_error(b->c, "io error reading bucket %zu",
			    PTR_BUCKET_NR(b->c, &b->key, 0));
पूर्ण

अटल व्योम btree_complete_ग_लिखो(काष्ठा btree *b, काष्ठा btree_ग_लिखो *w)
अणु
	अगर (w->prio_blocked &&
	    !atomic_sub_वापस(w->prio_blocked, &b->c->prio_blocked))
		wake_up_allocators(b->c);

	अगर (w->journal) अणु
		atomic_dec_bug(w->journal);
		__closure_wake_up(&b->c->journal.रुको);
	पूर्ण

	w->prio_blocked	= 0;
	w->journal	= शून्य;
पूर्ण

अटल व्योम btree_node_ग_लिखो_unlock(काष्ठा closure *cl)
अणु
	काष्ठा btree *b = container_of(cl, काष्ठा btree, io);

	up(&b->io_mutex);
पूर्ण

अटल व्योम __btree_node_ग_लिखो_करोne(काष्ठा closure *cl)
अणु
	काष्ठा btree *b = container_of(cl, काष्ठा btree, io);
	काष्ठा btree_ग_लिखो *w = btree_prev_ग_लिखो(b);

	bch_bbio_मुक्त(b->bio, b->c);
	b->bio = शून्य;
	btree_complete_ग_लिखो(b, w);

	अगर (btree_node_dirty(b))
		queue_delayed_work(btree_io_wq, &b->work, 30 * HZ);

	closure_वापस_with_deकाष्ठाor(cl, btree_node_ग_लिखो_unlock);
पूर्ण

अटल व्योम btree_node_ग_लिखो_करोne(काष्ठा closure *cl)
अणु
	काष्ठा btree *b = container_of(cl, काष्ठा btree, io);

	bio_मुक्त_pages(b->bio);
	__btree_node_ग_लिखो_करोne(cl);
पूर्ण

अटल व्योम btree_node_ग_लिखो_endio(काष्ठा bio *bio)
अणु
	काष्ठा closure *cl = bio->bi_निजी;
	काष्ठा btree *b = container_of(cl, काष्ठा btree, io);

	अगर (bio->bi_status)
		set_btree_node_io_error(b);

	bch_bbio_count_io_errors(b->c, bio, bio->bi_status, "writing btree");
	closure_put(cl);
पूर्ण

अटल व्योम करो_btree_node_ग_लिखो(काष्ठा btree *b)
अणु
	काष्ठा closure *cl = &b->io;
	काष्ठा bset *i = btree_bset_last(b);
	BKEY_PADDED(key) k;

	i->version	= BCACHE_BSET_VERSION;
	i->csum		= btree_csum_set(b, i);

	BUG_ON(b->bio);
	b->bio = bch_bbio_alloc(b->c);

	b->bio->bi_end_io	= btree_node_ग_लिखो_endio;
	b->bio->bi_निजी	= cl;
	b->bio->bi_iter.bi_size	= roundup(set_bytes(i), block_bytes(b->c->cache));
	b->bio->bi_opf		= REQ_OP_WRITE | REQ_META | REQ_FUA;
	bch_bio_map(b->bio, i);

	/*
	 * If we're appending to a leaf node, we don't technically need FUA -
	 * this ग_लिखो just needs to be persisted beक्रमe the next journal ग_लिखो,
	 * which will be marked FLUSH|FUA.
	 *
	 * Similarly अगर we're writing a new btree root - the poपूर्णांकer is going to
	 * be in the next journal entry.
	 *
	 * But अगर we're writing a new btree node (that isn't a root) or
	 * appending to a non leaf btree node, we need either FUA or a flush
	 * when we ग_लिखो the parent with the new poपूर्णांकer. FUA is cheaper than a
	 * flush, and ग_लिखोs appending to leaf nodes aren't blocking anything so
	 * just make all btree node ग_लिखोs FUA to keep things sane.
	 */

	bkey_copy(&k.key, &b->key);
	SET_PTR_OFFSET(&k.key, 0, PTR_OFFSET(&k.key, 0) +
		       bset_sector_offset(&b->keys, i));

	अगर (!bch_bio_alloc_pages(b->bio, __GFP_NOWARN|GFP_NOWAIT)) अणु
		काष्ठा bio_vec *bv;
		व्योम *addr = (व्योम *) ((अचिन्हित दीर्घ) i & ~(PAGE_SIZE - 1));
		काष्ठा bvec_iter_all iter_all;

		bio_क्रम_each_segment_all(bv, b->bio, iter_all) अणु
			स_नकल(page_address(bv->bv_page), addr, PAGE_SIZE);
			addr += PAGE_SIZE;
		पूर्ण

		bch_submit_bbio(b->bio, b->c, &k.key, 0);

		जारी_at(cl, btree_node_ग_लिखो_करोne, शून्य);
	पूर्ण अन्यथा अणु
		/*
		 * No problem क्रम multipage bvec since the bio is
		 * just allocated
		 */
		b->bio->bi_vcnt = 0;
		bch_bio_map(b->bio, i);

		bch_submit_bbio(b->bio, b->c, &k.key, 0);

		closure_sync(cl);
		जारी_at_nobarrier(cl, __btree_node_ग_लिखो_करोne, शून्य);
	पूर्ण
पूर्ण

व्योम __bch_btree_node_ग_लिखो(काष्ठा btree *b, काष्ठा closure *parent)
अणु
	काष्ठा bset *i = btree_bset_last(b);

	lockdep_निश्चित_held(&b->ग_लिखो_lock);

	trace_bcache_btree_ग_लिखो(b);

	BUG_ON(current->bio_list);
	BUG_ON(b->written >= btree_blocks(b));
	BUG_ON(b->written && !i->keys);
	BUG_ON(btree_bset_first(b)->seq != i->seq);
	bch_check_keys(&b->keys, "writing");

	cancel_delayed_work(&b->work);

	/* If caller isn't रुकोing क्रम ग_लिखो, parent refcount is cache set */
	करोwn(&b->io_mutex);
	closure_init(&b->io, parent ?: &b->c->cl);

	clear_bit(BTREE_NODE_dirty,	 &b->flags);
	change_bit(BTREE_NODE_ग_लिखो_idx, &b->flags);

	करो_btree_node_ग_लिखो(b);

	atomic_दीर्घ_add(set_blocks(i, block_bytes(b->c->cache)) * b->c->cache->sb.block_size,
			&b->c->cache->btree_sectors_written);

	b->written += set_blocks(i, block_bytes(b->c->cache));
पूर्ण

व्योम bch_btree_node_ग_लिखो(काष्ठा btree *b, काष्ठा closure *parent)
अणु
	अचिन्हित पूर्णांक nsets = b->keys.nsets;

	lockdep_निश्चित_held(&b->lock);

	__bch_btree_node_ग_लिखो(b, parent);

	/*
	 * करो verअगरy अगर there was more than one set initially (i.e. we did a
	 * sort) and we sorted करोwn to a single set:
	 */
	अगर (nsets && !b->keys.nsets)
		bch_btree_verअगरy(b);

	bch_btree_init_next(b);
पूर्ण

अटल व्योम bch_btree_node_ग_लिखो_sync(काष्ठा btree *b)
अणु
	काष्ठा closure cl;

	closure_init_stack(&cl);

	mutex_lock(&b->ग_लिखो_lock);
	bch_btree_node_ग_लिखो(b, &cl);
	mutex_unlock(&b->ग_लिखो_lock);

	closure_sync(&cl);
पूर्ण

अटल व्योम btree_node_ग_लिखो_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा btree *b = container_of(to_delayed_work(w), काष्ठा btree, work);

	mutex_lock(&b->ग_लिखो_lock);
	अगर (btree_node_dirty(b))
		__bch_btree_node_ग_लिखो(b, शून्य);
	mutex_unlock(&b->ग_लिखो_lock);
पूर्ण

अटल व्योम bch_btree_leaf_dirty(काष्ठा btree *b, atomic_t *journal_ref)
अणु
	काष्ठा bset *i = btree_bset_last(b);
	काष्ठा btree_ग_लिखो *w = btree_current_ग_लिखो(b);

	lockdep_निश्चित_held(&b->ग_लिखो_lock);

	BUG_ON(!b->written);
	BUG_ON(!i->keys);

	अगर (!btree_node_dirty(b))
		queue_delayed_work(btree_io_wq, &b->work, 30 * HZ);

	set_btree_node_dirty(b);

	/*
	 * w->journal is always the oldest journal pin of all bkeys
	 * in the leaf node, to make sure the oldest jset seq won't
	 * be increased beक्रमe this btree node is flushed.
	 */
	अगर (journal_ref) अणु
		अगर (w->journal &&
		    journal_pin_cmp(b->c, w->journal, journal_ref)) अणु
			atomic_dec_bug(w->journal);
			w->journal = शून्य;
		पूर्ण

		अगर (!w->journal) अणु
			w->journal = journal_ref;
			atomic_inc(w->journal);
		पूर्ण
	पूर्ण

	/* Force ग_लिखो अगर set is too big */
	अगर (set_bytes(i) > PAGE_SIZE - 48 &&
	    !current->bio_list)
		bch_btree_node_ग_लिखो(b, शून्य);
पूर्ण

/*
 * Btree in memory cache - allocation/मुक्तing
 * mca -> memory cache
 */

#घोषणा mca_reserve(c)	(((!IS_ERR_OR_शून्य(c->root) && c->root->level) \
			  ? c->root->level : 1) * 8 + 16)
#घोषणा mca_can_मुक्त(c)						\
	max_t(पूर्णांक, 0, c->btree_cache_used - mca_reserve(c))

अटल व्योम mca_data_मुक्त(काष्ठा btree *b)
अणु
	BUG_ON(b->io_mutex.count != 1);

	bch_btree_keys_मुक्त(&b->keys);

	b->c->btree_cache_used--;
	list_move(&b->list, &b->c->btree_cache_मुक्तd);
पूर्ण

अटल व्योम mca_bucket_मुक्त(काष्ठा btree *b)
अणु
	BUG_ON(btree_node_dirty(b));

	b->key.ptr[0] = 0;
	hlist_del_init_rcu(&b->hash);
	list_move(&b->list, &b->c->btree_cache_मुक्तable);
पूर्ण

अटल अचिन्हित पूर्णांक btree_order(काष्ठा bkey *k)
अणु
	वापस ilog2(KEY_SIZE(k) / PAGE_SECTORS ?: 1);
पूर्ण

अटल व्योम mca_data_alloc(काष्ठा btree *b, काष्ठा bkey *k, gfp_t gfp)
अणु
	अगर (!bch_btree_keys_alloc(&b->keys,
				  max_t(अचिन्हित पूर्णांक,
					ilog2(b->c->btree_pages),
					btree_order(k)),
				  gfp)) अणु
		b->c->btree_cache_used++;
		list_move(&b->list, &b->c->btree_cache);
	पूर्ण अन्यथा अणु
		list_move(&b->list, &b->c->btree_cache_मुक्तd);
	पूर्ण
पूर्ण

अटल काष्ठा btree *mca_bucket_alloc(काष्ठा cache_set *c,
				      काष्ठा bkey *k, gfp_t gfp)
अणु
	/*
	 * kzalloc() is necessary here क्रम initialization,
	 * see code comments in bch_btree_keys_init().
	 */
	काष्ठा btree *b = kzalloc(माप(काष्ठा btree), gfp);

	अगर (!b)
		वापस शून्य;

	init_rwsem(&b->lock);
	lockdep_set_novalidate_class(&b->lock);
	mutex_init(&b->ग_लिखो_lock);
	lockdep_set_novalidate_class(&b->ग_लिखो_lock);
	INIT_LIST_HEAD(&b->list);
	INIT_DELAYED_WORK(&b->work, btree_node_ग_लिखो_work);
	b->c = c;
	sema_init(&b->io_mutex, 1);

	mca_data_alloc(b, k, gfp);
	वापस b;
पूर्ण

अटल पूर्णांक mca_reap(काष्ठा btree *b, अचिन्हित पूर्णांक min_order, bool flush)
अणु
	काष्ठा closure cl;

	closure_init_stack(&cl);
	lockdep_निश्चित_held(&b->c->bucket_lock);

	अगर (!करोwn_ग_लिखो_trylock(&b->lock))
		वापस -ENOMEM;

	BUG_ON(btree_node_dirty(b) && !b->keys.set[0].data);

	अगर (b->keys.page_order < min_order)
		जाओ out_unlock;

	अगर (!flush) अणु
		अगर (btree_node_dirty(b))
			जाओ out_unlock;

		अगर (करोwn_trylock(&b->io_mutex))
			जाओ out_unlock;
		up(&b->io_mutex);
	पूर्ण

retry:
	/*
	 * BTREE_NODE_dirty might be cleared in btree_flush_btree() by
	 * __bch_btree_node_ग_लिखो(). To aव्योम an extra flush, acquire
	 * b->ग_लिखो_lock beक्रमe checking BTREE_NODE_dirty bit.
	 */
	mutex_lock(&b->ग_लिखो_lock);
	/*
	 * If this btree node is selected in btree_flush_ग_लिखो() by journal
	 * code, delay and retry until the node is flushed by journal code
	 * and BTREE_NODE_journal_flush bit cleared by btree_flush_ग_लिखो().
	 */
	अगर (btree_node_journal_flush(b)) अणु
		pr_debug("bnode %p is flushing by journal, retry\n", b);
		mutex_unlock(&b->ग_लिखो_lock);
		udelay(1);
		जाओ retry;
	पूर्ण

	अगर (btree_node_dirty(b))
		__bch_btree_node_ग_लिखो(b, &cl);
	mutex_unlock(&b->ग_लिखो_lock);

	closure_sync(&cl);

	/* रुको क्रम any in flight btree ग_लिखो */
	करोwn(&b->io_mutex);
	up(&b->io_mutex);

	वापस 0;
out_unlock:
	rw_unlock(true, b);
	वापस -ENOMEM;
पूर्ण

अटल अचिन्हित दीर्घ bch_mca_scan(काष्ठा shrinker *shrink,
				  काष्ठा shrink_control *sc)
अणु
	काष्ठा cache_set *c = container_of(shrink, काष्ठा cache_set, shrink);
	काष्ठा btree *b, *t;
	अचिन्हित दीर्घ i, nr = sc->nr_to_scan;
	अचिन्हित दीर्घ मुक्तd = 0;
	अचिन्हित पूर्णांक btree_cache_used;

	अगर (c->shrinker_disabled)
		वापस SHRINK_STOP;

	अगर (c->btree_cache_alloc_lock)
		वापस SHRINK_STOP;

	/* Return -1 अगर we can't करो anything right now */
	अगर (sc->gfp_mask & __GFP_IO)
		mutex_lock(&c->bucket_lock);
	अन्यथा अगर (!mutex_trylock(&c->bucket_lock))
		वापस -1;

	/*
	 * It's _really_ critical that we don't मुक्त too many btree nodes - we
	 * have to always leave ourselves a reserve. The reserve is how we
	 * guarantee that allocating memory क्रम a new btree node can always
	 * succeed, so that inserting keys पूर्णांकo the btree can always succeed and
	 * IO can always make क्रमward progress:
	 */
	nr /= c->btree_pages;
	अगर (nr == 0)
		nr = 1;
	nr = min_t(अचिन्हित दीर्घ, nr, mca_can_मुक्त(c));

	i = 0;
	btree_cache_used = c->btree_cache_used;
	list_क्रम_each_entry_safe_reverse(b, t, &c->btree_cache_मुक्तable, list) अणु
		अगर (nr <= 0)
			जाओ out;

		अगर (!mca_reap(b, 0, false)) अणु
			mca_data_मुक्त(b);
			rw_unlock(true, b);
			मुक्तd++;
		पूर्ण
		nr--;
		i++;
	पूर्ण

	list_क्रम_each_entry_safe_reverse(b, t, &c->btree_cache, list) अणु
		अगर (nr <= 0 || i >= btree_cache_used)
			जाओ out;

		अगर (!mca_reap(b, 0, false)) अणु
			mca_bucket_मुक्त(b);
			mca_data_मुक्त(b);
			rw_unlock(true, b);
			मुक्तd++;
		पूर्ण

		nr--;
		i++;
	पूर्ण
out:
	mutex_unlock(&c->bucket_lock);
	वापस मुक्तd * c->btree_pages;
पूर्ण

अटल अचिन्हित दीर्घ bch_mca_count(काष्ठा shrinker *shrink,
				   काष्ठा shrink_control *sc)
अणु
	काष्ठा cache_set *c = container_of(shrink, काष्ठा cache_set, shrink);

	अगर (c->shrinker_disabled)
		वापस 0;

	अगर (c->btree_cache_alloc_lock)
		वापस 0;

	वापस mca_can_मुक्त(c) * c->btree_pages;
पूर्ण

व्योम bch_btree_cache_मुक्त(काष्ठा cache_set *c)
अणु
	काष्ठा btree *b;
	काष्ठा closure cl;

	closure_init_stack(&cl);

	अगर (c->shrink.list.next)
		unरेजिस्टर_shrinker(&c->shrink);

	mutex_lock(&c->bucket_lock);

#अगर_घोषित CONFIG_BCACHE_DEBUG
	अगर (c->verअगरy_data)
		list_move(&c->verअगरy_data->list, &c->btree_cache);

	मुक्त_pages((अचिन्हित दीर्घ) c->verअगरy_ondisk, ilog2(meta_bucket_pages(&c->cache->sb)));
#पूर्ण_अगर

	list_splice(&c->btree_cache_मुक्तable,
		    &c->btree_cache);

	जबतक (!list_empty(&c->btree_cache)) अणु
		b = list_first_entry(&c->btree_cache, काष्ठा btree, list);

		/*
		 * This function is called by cache_set_मुक्त(), no I/O
		 * request on cache now, it is unnecessary to acquire
		 * b->ग_लिखो_lock beक्रमe clearing BTREE_NODE_dirty anymore.
		 */
		अगर (btree_node_dirty(b)) अणु
			btree_complete_ग_लिखो(b, btree_current_ग_लिखो(b));
			clear_bit(BTREE_NODE_dirty, &b->flags);
		पूर्ण
		mca_data_मुक्त(b);
	पूर्ण

	जबतक (!list_empty(&c->btree_cache_मुक्तd)) अणु
		b = list_first_entry(&c->btree_cache_मुक्तd,
				     काष्ठा btree, list);
		list_del(&b->list);
		cancel_delayed_work_sync(&b->work);
		kमुक्त(b);
	पूर्ण

	mutex_unlock(&c->bucket_lock);
पूर्ण

पूर्णांक bch_btree_cache_alloc(काष्ठा cache_set *c)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mca_reserve(c); i++)
		अगर (!mca_bucket_alloc(c, &ZERO_KEY, GFP_KERNEL))
			वापस -ENOMEM;

	list_splice_init(&c->btree_cache,
			 &c->btree_cache_मुक्तable);

#अगर_घोषित CONFIG_BCACHE_DEBUG
	mutex_init(&c->verअगरy_lock);

	c->verअगरy_ondisk = (व्योम *)
		__get_मुक्त_pages(GFP_KERNEL|__GFP_COMP,
				 ilog2(meta_bucket_pages(&c->cache->sb)));
	अगर (!c->verअगरy_ondisk) अणु
		/*
		 * Don't worry about the mca_rereserve buckets
		 * allocated in previous क्रम-loop, they will be
		 * handled properly in bch_cache_set_unरेजिस्टर().
		 */
		वापस -ENOMEM;
	पूर्ण

	c->verअगरy_data = mca_bucket_alloc(c, &ZERO_KEY, GFP_KERNEL);

	अगर (c->verअगरy_data &&
	    c->verअगरy_data->keys.set->data)
		list_del_init(&c->verअगरy_data->list);
	अन्यथा
		c->verअगरy_data = शून्य;
#पूर्ण_अगर

	c->shrink.count_objects = bch_mca_count;
	c->shrink.scan_objects = bch_mca_scan;
	c->shrink.seeks = 4;
	c->shrink.batch = c->btree_pages * 2;

	अगर (रेजिस्टर_shrinker(&c->shrink))
		pr_warn("bcache: %s: could not register shrinker\n",
				__func__);

	वापस 0;
पूर्ण

/* Btree in memory cache - hash table */

अटल काष्ठा hlist_head *mca_hash(काष्ठा cache_set *c, काष्ठा bkey *k)
अणु
	वापस &c->bucket_hash[hash_32(PTR_HASH(c, k), BUCKET_HASH_BITS)];
पूर्ण

अटल काष्ठा btree *mca_find(काष्ठा cache_set *c, काष्ठा bkey *k)
अणु
	काष्ठा btree *b;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(b, mca_hash(c, k), hash)
		अगर (PTR_HASH(c, &b->key) == PTR_HASH(c, k))
			जाओ out;
	b = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस b;
पूर्ण

अटल पूर्णांक mca_cannibalize_lock(काष्ठा cache_set *c, काष्ठा btree_op *op)
अणु
	spin_lock(&c->btree_cannibalize_lock);
	अगर (likely(c->btree_cache_alloc_lock == शून्य)) अणु
		c->btree_cache_alloc_lock = current;
	पूर्ण अन्यथा अगर (c->btree_cache_alloc_lock != current) अणु
		अगर (op)
			prepare_to_रुको(&c->btree_cache_रुको, &op->रुको,
					TASK_UNINTERRUPTIBLE);
		spin_unlock(&c->btree_cannibalize_lock);
		वापस -EINTR;
	पूर्ण
	spin_unlock(&c->btree_cannibalize_lock);

	वापस 0;
पूर्ण

अटल काष्ठा btree *mca_cannibalize(काष्ठा cache_set *c, काष्ठा btree_op *op,
				     काष्ठा bkey *k)
अणु
	काष्ठा btree *b;

	trace_bcache_btree_cache_cannibalize(c);

	अगर (mca_cannibalize_lock(c, op))
		वापस ERR_PTR(-EINTR);

	list_क्रम_each_entry_reverse(b, &c->btree_cache, list)
		अगर (!mca_reap(b, btree_order(k), false))
			वापस b;

	list_क्रम_each_entry_reverse(b, &c->btree_cache, list)
		अगर (!mca_reap(b, btree_order(k), true))
			वापस b;

	WARN(1, "btree cache cannibalize failed\n");
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * We can only have one thपढ़ो cannibalizing other cached btree nodes at a समय,
 * or we'll deadlock. We use an खोलो coded mutex to ensure that, which a
 * cannibalize_bucket() will take. This means every समय we unlock the root of
 * the btree, we need to release this lock अगर we have it held.
 */
अटल व्योम bch_cannibalize_unlock(काष्ठा cache_set *c)
अणु
	spin_lock(&c->btree_cannibalize_lock);
	अगर (c->btree_cache_alloc_lock == current) अणु
		c->btree_cache_alloc_lock = शून्य;
		wake_up(&c->btree_cache_रुको);
	पूर्ण
	spin_unlock(&c->btree_cannibalize_lock);
पूर्ण

अटल काष्ठा btree *mca_alloc(काष्ठा cache_set *c, काष्ठा btree_op *op,
			       काष्ठा bkey *k, पूर्णांक level)
अणु
	काष्ठा btree *b;

	BUG_ON(current->bio_list);

	lockdep_निश्चित_held(&c->bucket_lock);

	अगर (mca_find(c, k))
		वापस शून्य;

	/* btree_मुक्त() करोesn't मुक्त memory; it sticks the node on the end of
	 * the list. Check अगर there's any मुक्तd nodes there:
	 */
	list_क्रम_each_entry(b, &c->btree_cache_मुक्तable, list)
		अगर (!mca_reap(b, btree_order(k), false))
			जाओ out;

	/* We never मुक्त काष्ठा btree itself, just the memory that holds the on
	 * disk node. Check the मुक्तd list beक्रमe allocating a new one:
	 */
	list_क्रम_each_entry(b, &c->btree_cache_मुक्तd, list)
		अगर (!mca_reap(b, 0, false)) अणु
			mca_data_alloc(b, k, __GFP_NOWARN|GFP_NOIO);
			अगर (!b->keys.set[0].data)
				जाओ err;
			अन्यथा
				जाओ out;
		पूर्ण

	b = mca_bucket_alloc(c, k, __GFP_NOWARN|GFP_NOIO);
	अगर (!b)
		जाओ err;

	BUG_ON(!करोwn_ग_लिखो_trylock(&b->lock));
	अगर (!b->keys.set->data)
		जाओ err;
out:
	BUG_ON(b->io_mutex.count != 1);

	bkey_copy(&b->key, k);
	list_move(&b->list, &c->btree_cache);
	hlist_del_init_rcu(&b->hash);
	hlist_add_head_rcu(&b->hash, mca_hash(c, k));

	lock_set_subclass(&b->lock.dep_map, level + 1, _THIS_IP_);
	b->parent	= (व्योम *) ~0UL;
	b->flags	= 0;
	b->written	= 0;
	b->level	= level;

	अगर (!b->level)
		bch_btree_keys_init(&b->keys, &bch_extent_keys_ops,
				    &b->c->expensive_debug_checks);
	अन्यथा
		bch_btree_keys_init(&b->keys, &bch_btree_keys_ops,
				    &b->c->expensive_debug_checks);

	वापस b;
err:
	अगर (b)
		rw_unlock(true, b);

	b = mca_cannibalize(c, op, k);
	अगर (!IS_ERR(b))
		जाओ out;

	वापस b;
पूर्ण

/*
 * bch_btree_node_get - find a btree node in the cache and lock it, पढ़ोing it
 * in from disk अगर necessary.
 *
 * If IO is necessary and running under submit_bio_noacct, वापसs -EAGAIN.
 *
 * The btree node will have either a पढ़ो or a ग_लिखो lock held, depending on
 * level and op->lock.
 */
काष्ठा btree *bch_btree_node_get(काष्ठा cache_set *c, काष्ठा btree_op *op,
				 काष्ठा bkey *k, पूर्णांक level, bool ग_लिखो,
				 काष्ठा btree *parent)
अणु
	पूर्णांक i = 0;
	काष्ठा btree *b;

	BUG_ON(level < 0);
retry:
	b = mca_find(c, k);

	अगर (!b) अणु
		अगर (current->bio_list)
			वापस ERR_PTR(-EAGAIN);

		mutex_lock(&c->bucket_lock);
		b = mca_alloc(c, op, k, level);
		mutex_unlock(&c->bucket_lock);

		अगर (!b)
			जाओ retry;
		अगर (IS_ERR(b))
			वापस b;

		bch_btree_node_पढ़ो(b);

		अगर (!ग_लिखो)
			करोwngrade_ग_लिखो(&b->lock);
	पूर्ण अन्यथा अणु
		rw_lock(ग_लिखो, b, level);
		अगर (PTR_HASH(c, &b->key) != PTR_HASH(c, k)) अणु
			rw_unlock(ग_लिखो, b);
			जाओ retry;
		पूर्ण
		BUG_ON(b->level != level);
	पूर्ण

	अगर (btree_node_io_error(b)) अणु
		rw_unlock(ग_लिखो, b);
		वापस ERR_PTR(-EIO);
	पूर्ण

	BUG_ON(!b->written);

	b->parent = parent;

	क्रम (; i <= b->keys.nsets && b->keys.set[i].size; i++) अणु
		prefetch(b->keys.set[i].tree);
		prefetch(b->keys.set[i].data);
	पूर्ण

	क्रम (; i <= b->keys.nsets; i++)
		prefetch(b->keys.set[i].data);

	वापस b;
पूर्ण

अटल व्योम btree_node_prefetch(काष्ठा btree *parent, काष्ठा bkey *k)
अणु
	काष्ठा btree *b;

	mutex_lock(&parent->c->bucket_lock);
	b = mca_alloc(parent->c, शून्य, k, parent->level - 1);
	mutex_unlock(&parent->c->bucket_lock);

	अगर (!IS_ERR_OR_शून्य(b)) अणु
		b->parent = parent;
		bch_btree_node_पढ़ो(b);
		rw_unlock(true, b);
	पूर्ण
पूर्ण

/* Btree alloc */

अटल व्योम btree_node_मुक्त(काष्ठा btree *b)
अणु
	trace_bcache_btree_node_मुक्त(b);

	BUG_ON(b == b->c->root);

retry:
	mutex_lock(&b->ग_लिखो_lock);
	/*
	 * If the btree node is selected and flushing in btree_flush_ग_लिखो(),
	 * delay and retry until the BTREE_NODE_journal_flush bit cleared,
	 * then it is safe to मुक्त the btree node here. Otherwise this btree
	 * node will be in race condition.
	 */
	अगर (btree_node_journal_flush(b)) अणु
		mutex_unlock(&b->ग_लिखो_lock);
		pr_debug("bnode %p journal_flush set, retry\n", b);
		udelay(1);
		जाओ retry;
	पूर्ण

	अगर (btree_node_dirty(b)) अणु
		btree_complete_ग_लिखो(b, btree_current_ग_लिखो(b));
		clear_bit(BTREE_NODE_dirty, &b->flags);
	पूर्ण

	mutex_unlock(&b->ग_लिखो_lock);

	cancel_delayed_work(&b->work);

	mutex_lock(&b->c->bucket_lock);
	bch_bucket_मुक्त(b->c, &b->key);
	mca_bucket_मुक्त(b);
	mutex_unlock(&b->c->bucket_lock);
पूर्ण

काष्ठा btree *__bch_btree_node_alloc(काष्ठा cache_set *c, काष्ठा btree_op *op,
				     पूर्णांक level, bool रुको,
				     काष्ठा btree *parent)
अणु
	BKEY_PADDED(key) k;
	काष्ठा btree *b = ERR_PTR(-EAGAIN);

	mutex_lock(&c->bucket_lock);
retry:
	अगर (__bch_bucket_alloc_set(c, RESERVE_BTREE, &k.key, रुको))
		जाओ err;

	bkey_put(c, &k.key);
	SET_KEY_SIZE(&k.key, c->btree_pages * PAGE_SECTORS);

	b = mca_alloc(c, op, &k.key, level);
	अगर (IS_ERR(b))
		जाओ err_मुक्त;

	अगर (!b) अणु
		cache_bug(c,
			"Tried to allocate bucket that was in btree cache");
		जाओ retry;
	पूर्ण

	b->parent = parent;
	bch_bset_init_next(&b->keys, b->keys.set->data, bset_magic(&b->c->cache->sb));

	mutex_unlock(&c->bucket_lock);

	trace_bcache_btree_node_alloc(b);
	वापस b;
err_मुक्त:
	bch_bucket_मुक्त(c, &k.key);
err:
	mutex_unlock(&c->bucket_lock);

	trace_bcache_btree_node_alloc_fail(c);
	वापस b;
पूर्ण

अटल काष्ठा btree *bch_btree_node_alloc(काष्ठा cache_set *c,
					  काष्ठा btree_op *op, पूर्णांक level,
					  काष्ठा btree *parent)
अणु
	वापस __bch_btree_node_alloc(c, op, level, op != शून्य, parent);
पूर्ण

अटल काष्ठा btree *btree_node_alloc_replacement(काष्ठा btree *b,
						  काष्ठा btree_op *op)
अणु
	काष्ठा btree *n = bch_btree_node_alloc(b->c, op, b->level, b->parent);

	अगर (!IS_ERR_OR_शून्य(n)) अणु
		mutex_lock(&n->ग_लिखो_lock);
		bch_btree_sort_पूर्णांकo(&b->keys, &n->keys, &b->c->sort);
		bkey_copy_key(&n->key, &b->key);
		mutex_unlock(&n->ग_लिखो_lock);
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम make_btree_मुक्तing_key(काष्ठा btree *b, काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i;

	mutex_lock(&b->c->bucket_lock);

	atomic_inc(&b->c->prio_blocked);

	bkey_copy(k, &b->key);
	bkey_copy_key(k, &ZERO_KEY);

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		SET_PTR_GEN(k, i,
			    bch_inc_gen(b->c->cache,
					PTR_BUCKET(b->c, &b->key, i)));

	mutex_unlock(&b->c->bucket_lock);
पूर्ण

अटल पूर्णांक btree_check_reserve(काष्ठा btree *b, काष्ठा btree_op *op)
अणु
	काष्ठा cache_set *c = b->c;
	काष्ठा cache *ca = c->cache;
	अचिन्हित पूर्णांक reserve = (c->root->level - b->level) * 2 + 1;

	mutex_lock(&c->bucket_lock);

	अगर (fअगरo_used(&ca->मुक्त[RESERVE_BTREE]) < reserve) अणु
		अगर (op)
			prepare_to_रुको(&c->btree_cache_रुको, &op->रुको,
					TASK_UNINTERRUPTIBLE);
		mutex_unlock(&c->bucket_lock);
		वापस -EINTR;
	पूर्ण

	mutex_unlock(&c->bucket_lock);

	वापस mca_cannibalize_lock(b->c, op);
पूर्ण

/* Garbage collection */

अटल uपूर्णांक8_t __bch_btree_mark_key(काष्ठा cache_set *c, पूर्णांक level,
				    काष्ठा bkey *k)
अणु
	uपूर्णांक8_t stale = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा bucket *g;

	/*
	 * ptr_invalid() can't वापस true क्रम the keys that mark btree nodes as
	 * मुक्तd, but since ptr_bad() वापसs true we'll never actually use them
	 * क्रम anything and thus we करोn't want mark their poपूर्णांकers here
	 */
	अगर (!bkey_cmp(k, &ZERO_KEY))
		वापस stale;

	क्रम (i = 0; i < KEY_PTRS(k); i++) अणु
		अगर (!ptr_available(c, k, i))
			जारी;

		g = PTR_BUCKET(c, k, i);

		अगर (gen_after(g->last_gc, PTR_GEN(k, i)))
			g->last_gc = PTR_GEN(k, i);

		अगर (ptr_stale(c, k, i)) अणु
			stale = max(stale, ptr_stale(c, k, i));
			जारी;
		पूर्ण

		cache_bug_on(GC_MARK(g) &&
			     (GC_MARK(g) == GC_MARK_METADATA) != (level != 0),
			     c, "inconsistent ptrs: mark = %llu, level = %i",
			     GC_MARK(g), level);

		अगर (level)
			SET_GC_MARK(g, GC_MARK_METADATA);
		अन्यथा अगर (KEY_सूचीTY(k))
			SET_GC_MARK(g, GC_MARK_सूचीTY);
		अन्यथा अगर (!GC_MARK(g))
			SET_GC_MARK(g, GC_MARK_RECLAIMABLE);

		/* guard against overflow */
		SET_GC_SECTORS_USED(g, min_t(अचिन्हित पूर्णांक,
					     GC_SECTORS_USED(g) + KEY_SIZE(k),
					     MAX_GC_SECTORS_USED));

		BUG_ON(!GC_SECTORS_USED(g));
	पूर्ण

	वापस stale;
पूर्ण

#घोषणा btree_mark_key(b, k)	__bch_btree_mark_key(b->c, b->level, k)

व्योम bch_initial_mark_key(काष्ठा cache_set *c, पूर्णांक level, काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		अगर (ptr_available(c, k, i) &&
		    !ptr_stale(c, k, i)) अणु
			काष्ठा bucket *b = PTR_BUCKET(c, k, i);

			b->gen = PTR_GEN(k, i);

			अगर (level && bkey_cmp(k, &ZERO_KEY))
				b->prio = BTREE_PRIO;
			अन्यथा अगर (!level && b->prio == BTREE_PRIO)
				b->prio = INITIAL_PRIO;
		पूर्ण

	__bch_btree_mark_key(c, level, k);
पूर्ण

व्योम bch_update_bucket_in_use(काष्ठा cache_set *c, काष्ठा gc_stat *stats)
अणु
	stats->in_use = (c->nbuckets - c->avail_nbuckets) * 100 / c->nbuckets;
पूर्ण

अटल bool btree_gc_mark_node(काष्ठा btree *b, काष्ठा gc_stat *gc)
अणु
	uपूर्णांक8_t stale = 0;
	अचिन्हित पूर्णांक keys = 0, good_keys = 0;
	काष्ठा bkey *k;
	काष्ठा btree_iter iter;
	काष्ठा bset_tree *t;

	gc->nodes++;

	क्रम_each_key_filter(&b->keys, k, &iter, bch_ptr_invalid) अणु
		stale = max(stale, btree_mark_key(b, k));
		keys++;

		अगर (bch_ptr_bad(&b->keys, k))
			जारी;

		gc->key_bytes += bkey_u64s(k);
		gc->nkeys++;
		good_keys++;

		gc->data += KEY_SIZE(k);
	पूर्ण

	क्रम (t = b->keys.set; t <= &b->keys.set[b->keys.nsets]; t++)
		btree_bug_on(t->size &&
			     bset_written(&b->keys, t) &&
			     bkey_cmp(&b->key, &t->end) < 0,
			     b, "found short btree key in gc");

	अगर (b->c->gc_always_reग_लिखो)
		वापस true;

	अगर (stale > 10)
		वापस true;

	अगर ((keys - good_keys) * 2 > keys)
		वापस true;

	वापस false;
पूर्ण

#घोषणा GC_MERGE_NODES	4U

काष्ठा gc_merge_info अणु
	काष्ठा btree	*b;
	अचिन्हित पूर्णांक	keys;
पूर्ण;

अटल पूर्णांक bch_btree_insert_node(काष्ठा btree *b, काष्ठा btree_op *op,
				 काष्ठा keylist *insert_keys,
				 atomic_t *journal_ref,
				 काष्ठा bkey *replace_key);

अटल पूर्णांक btree_gc_coalesce(काष्ठा btree *b, काष्ठा btree_op *op,
			     काष्ठा gc_stat *gc, काष्ठा gc_merge_info *r)
अणु
	अचिन्हित पूर्णांक i, nodes = 0, keys = 0, blocks;
	काष्ठा btree *new_nodes[GC_MERGE_NODES];
	काष्ठा keylist keylist;
	काष्ठा closure cl;
	काष्ठा bkey *k;

	bch_keylist_init(&keylist);

	अगर (btree_check_reserve(b, शून्य))
		वापस 0;

	स_रखो(new_nodes, 0, माप(new_nodes));
	closure_init_stack(&cl);

	जबतक (nodes < GC_MERGE_NODES && !IS_ERR_OR_शून्य(r[nodes].b))
		keys += r[nodes++].keys;

	blocks = btree_शेष_blocks(b->c) * 2 / 3;

	अगर (nodes < 2 ||
	    __set_blocks(b->keys.set[0].data, keys,
			 block_bytes(b->c->cache)) > blocks * (nodes - 1))
		वापस 0;

	क्रम (i = 0; i < nodes; i++) अणु
		new_nodes[i] = btree_node_alloc_replacement(r[i].b, शून्य);
		अगर (IS_ERR_OR_शून्य(new_nodes[i]))
			जाओ out_nocoalesce;
	पूर्ण

	/*
	 * We have to check the reserve here, after we've allocated our new
	 * nodes, to make sure the insert below will succeed - we also check
	 * beक्रमe as an optimization to potentially aव्योम a bunch of expensive
	 * allocs/sorts
	 */
	अगर (btree_check_reserve(b, शून्य))
		जाओ out_nocoalesce;

	क्रम (i = 0; i < nodes; i++)
		mutex_lock(&new_nodes[i]->ग_लिखो_lock);

	क्रम (i = nodes - 1; i > 0; --i) अणु
		काष्ठा bset *n1 = btree_bset_first(new_nodes[i]);
		काष्ठा bset *n2 = btree_bset_first(new_nodes[i - 1]);
		काष्ठा bkey *k, *last = शून्य;

		keys = 0;

		अगर (i > 1) अणु
			क्रम (k = n2->start;
			     k < bset_bkey_last(n2);
			     k = bkey_next(k)) अणु
				अगर (__set_blocks(n1, n1->keys + keys +
						 bkey_u64s(k),
						 block_bytes(b->c->cache)) > blocks)
					अवरोध;

				last = k;
				keys += bkey_u64s(k);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Last node we're not getting rid of - we're getting
			 * rid of the node at r[0]. Have to try and fit all of
			 * the reमुख्यing keys पूर्णांकo this node; we can't ensure
			 * they will always fit due to rounding and variable
			 * length keys (shouldn't be possible in practice,
			 * though)
			 */
			अगर (__set_blocks(n1, n1->keys + n2->keys,
					 block_bytes(b->c->cache)) >
			    btree_blocks(new_nodes[i]))
				जाओ out_unlock_nocoalesce;

			keys = n2->keys;
			/* Take the key of the node we're getting rid of */
			last = &r->b->key;
		पूर्ण

		BUG_ON(__set_blocks(n1, n1->keys + keys, block_bytes(b->c->cache)) >
		       btree_blocks(new_nodes[i]));

		अगर (last)
			bkey_copy_key(&new_nodes[i]->key, last);

		स_नकल(bset_bkey_last(n1),
		       n2->start,
		       (व्योम *) bset_bkey_idx(n2, keys) - (व्योम *) n2->start);

		n1->keys += keys;
		r[i].keys = n1->keys;

		स_हटाओ(n2->start,
			bset_bkey_idx(n2, keys),
			(व्योम *) bset_bkey_last(n2) -
			(व्योम *) bset_bkey_idx(n2, keys));

		n2->keys -= keys;

		अगर (__bch_keylist_पुनः_स्मृति(&keylist,
					  bkey_u64s(&new_nodes[i]->key)))
			जाओ out_unlock_nocoalesce;

		bch_btree_node_ग_लिखो(new_nodes[i], &cl);
		bch_keylist_add(&keylist, &new_nodes[i]->key);
	पूर्ण

	क्रम (i = 0; i < nodes; i++)
		mutex_unlock(&new_nodes[i]->ग_लिखो_lock);

	closure_sync(&cl);

	/* We emptied out this node */
	BUG_ON(btree_bset_first(new_nodes[0])->keys);
	btree_node_मुक्त(new_nodes[0]);
	rw_unlock(true, new_nodes[0]);
	new_nodes[0] = शून्य;

	क्रम (i = 0; i < nodes; i++) अणु
		अगर (__bch_keylist_पुनः_स्मृति(&keylist, bkey_u64s(&r[i].b->key)))
			जाओ out_nocoalesce;

		make_btree_मुक्तing_key(r[i].b, keylist.top);
		bch_keylist_push(&keylist);
	पूर्ण

	bch_btree_insert_node(b, op, &keylist, शून्य, शून्य);
	BUG_ON(!bch_keylist_empty(&keylist));

	क्रम (i = 0; i < nodes; i++) अणु
		btree_node_मुक्त(r[i].b);
		rw_unlock(true, r[i].b);

		r[i].b = new_nodes[i];
	पूर्ण

	स_हटाओ(r, r + 1, माप(r[0]) * (nodes - 1));
	r[nodes - 1].b = ERR_PTR(-EINTR);

	trace_bcache_btree_gc_coalesce(nodes);
	gc->nodes--;

	bch_keylist_मुक्त(&keylist);

	/* Invalidated our iterator */
	वापस -EINTR;

out_unlock_nocoalesce:
	क्रम (i = 0; i < nodes; i++)
		mutex_unlock(&new_nodes[i]->ग_लिखो_lock);

out_nocoalesce:
	closure_sync(&cl);

	जबतक ((k = bch_keylist_pop(&keylist)))
		अगर (!bkey_cmp(k, &ZERO_KEY))
			atomic_dec(&b->c->prio_blocked);
	bch_keylist_मुक्त(&keylist);

	क्रम (i = 0; i < nodes; i++)
		अगर (!IS_ERR_OR_शून्य(new_nodes[i])) अणु
			btree_node_मुक्त(new_nodes[i]);
			rw_unlock(true, new_nodes[i]);
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btree_gc_reग_लिखो_node(काष्ठा btree *b, काष्ठा btree_op *op,
				 काष्ठा btree *replace)
अणु
	काष्ठा keylist keys;
	काष्ठा btree *n;

	अगर (btree_check_reserve(b, शून्य))
		वापस 0;

	n = btree_node_alloc_replacement(replace, शून्य);

	/* recheck reserve after allocating replacement node */
	अगर (btree_check_reserve(b, शून्य)) अणु
		btree_node_मुक्त(n);
		rw_unlock(true, n);
		वापस 0;
	पूर्ण

	bch_btree_node_ग_लिखो_sync(n);

	bch_keylist_init(&keys);
	bch_keylist_add(&keys, &n->key);

	make_btree_मुक्तing_key(replace, keys.top);
	bch_keylist_push(&keys);

	bch_btree_insert_node(b, op, &keys, शून्य, शून्य);
	BUG_ON(!bch_keylist_empty(&keys));

	btree_node_मुक्त(replace);
	rw_unlock(true, n);

	/* Invalidated our iterator */
	वापस -EINTR;
पूर्ण

अटल अचिन्हित पूर्णांक btree_gc_count_keys(काष्ठा btree *b)
अणु
	काष्ठा bkey *k;
	काष्ठा btree_iter iter;
	अचिन्हित पूर्णांक ret = 0;

	क्रम_each_key_filter(&b->keys, k, &iter, bch_ptr_bad)
		ret += bkey_u64s(k);

	वापस ret;
पूर्ण

अटल माप_प्रकार btree_gc_min_nodes(काष्ठा cache_set *c)
अणु
	माप_प्रकार min_nodes;

	/*
	 * Since incremental GC would stop 100ms when front
	 * side I/O comes, so when there are many btree nodes,
	 * अगर GC only processes स्थिरant (100) nodes each समय,
	 * GC would last a दीर्घ समय, and the front side I/Os
	 * would run out of the buckets (since no new bucket
	 * can be allocated during GC), and be blocked again.
	 * So GC should not process स्थिरant nodes, but varied
	 * nodes according to the number of btree nodes, which
	 * realized by भागiding GC पूर्णांकo स्थिरant(100) बार,
	 * so when there are many btree nodes, GC can process
	 * more nodes each समय, otherwise, GC will process less
	 * nodes each समय (but no less than MIN_GC_NODES)
	 */
	min_nodes = c->gc_stats.nodes / MAX_GC_TIMES;
	अगर (min_nodes < MIN_GC_NODES)
		min_nodes = MIN_GC_NODES;

	वापस min_nodes;
पूर्ण


अटल पूर्णांक btree_gc_recurse(काष्ठा btree *b, काष्ठा btree_op *op,
			    काष्ठा closure *ग_लिखोs, काष्ठा gc_stat *gc)
अणु
	पूर्णांक ret = 0;
	bool should_reग_लिखो;
	काष्ठा bkey *k;
	काष्ठा btree_iter iter;
	काष्ठा gc_merge_info r[GC_MERGE_NODES];
	काष्ठा gc_merge_info *i, *last = r + ARRAY_SIZE(r) - 1;

	bch_btree_iter_init(&b->keys, &iter, &b->c->gc_करोne);

	क्रम (i = r; i < r + ARRAY_SIZE(r); i++)
		i->b = ERR_PTR(-EINTR);

	जबतक (1) अणु
		k = bch_btree_iter_next_filter(&iter, &b->keys, bch_ptr_bad);
		अगर (k) अणु
			r->b = bch_btree_node_get(b->c, op, k, b->level - 1,
						  true, b);
			अगर (IS_ERR(r->b)) अणु
				ret = PTR_ERR(r->b);
				अवरोध;
			पूर्ण

			r->keys = btree_gc_count_keys(r->b);

			ret = btree_gc_coalesce(b, op, gc, r);
			अगर (ret)
				अवरोध;
		पूर्ण

		अगर (!last->b)
			अवरोध;

		अगर (!IS_ERR(last->b)) अणु
			should_reग_लिखो = btree_gc_mark_node(last->b, gc);
			अगर (should_reग_लिखो) अणु
				ret = btree_gc_reग_लिखो_node(b, op, last->b);
				अगर (ret)
					अवरोध;
			पूर्ण

			अगर (last->b->level) अणु
				ret = btree_gc_recurse(last->b, op, ग_लिखोs, gc);
				अगर (ret)
					अवरोध;
			पूर्ण

			bkey_copy_key(&b->c->gc_करोne, &last->b->key);

			/*
			 * Must flush leaf nodes beक्रमe gc ends, since replace
			 * operations aren't journalled
			 */
			mutex_lock(&last->b->ग_लिखो_lock);
			अगर (btree_node_dirty(last->b))
				bch_btree_node_ग_लिखो(last->b, ग_लिखोs);
			mutex_unlock(&last->b->ग_लिखो_lock);
			rw_unlock(true, last->b);
		पूर्ण

		स_हटाओ(r + 1, r, माप(r[0]) * (GC_MERGE_NODES - 1));
		r->b = शून्य;

		अगर (atomic_पढ़ो(&b->c->search_inflight) &&
		    gc->nodes >= gc->nodes_pre + btree_gc_min_nodes(b->c)) अणु
			gc->nodes_pre =  gc->nodes;
			ret = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (need_resched()) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = r; i < r + ARRAY_SIZE(r); i++)
		अगर (!IS_ERR_OR_शून्य(i->b)) अणु
			mutex_lock(&i->b->ग_लिखो_lock);
			अगर (btree_node_dirty(i->b))
				bch_btree_node_ग_लिखो(i->b, ग_लिखोs);
			mutex_unlock(&i->b->ग_लिखो_lock);
			rw_unlock(true, i->b);
		पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bch_btree_gc_root(काष्ठा btree *b, काष्ठा btree_op *op,
			     काष्ठा closure *ग_लिखोs, काष्ठा gc_stat *gc)
अणु
	काष्ठा btree *n = शून्य;
	पूर्णांक ret = 0;
	bool should_reग_लिखो;

	should_reग_लिखो = btree_gc_mark_node(b, gc);
	अगर (should_reग_लिखो) अणु
		n = btree_node_alloc_replacement(b, शून्य);

		अगर (!IS_ERR_OR_शून्य(n)) अणु
			bch_btree_node_ग_लिखो_sync(n);

			bch_btree_set_root(n);
			btree_node_मुक्त(b);
			rw_unlock(true, n);

			वापस -EINTR;
		पूर्ण
	पूर्ण

	__bch_btree_mark_key(b->c, b->level + 1, &b->key);

	अगर (b->level) अणु
		ret = btree_gc_recurse(b, op, ग_लिखोs, gc);
		अगर (ret)
			वापस ret;
	पूर्ण

	bkey_copy_key(&b->c->gc_करोne, &b->key);

	वापस ret;
पूर्ण

अटल व्योम btree_gc_start(काष्ठा cache_set *c)
अणु
	काष्ठा cache *ca;
	काष्ठा bucket *b;

	अगर (!c->gc_mark_valid)
		वापस;

	mutex_lock(&c->bucket_lock);

	c->gc_mark_valid = 0;
	c->gc_करोne = ZERO_KEY;

	ca = c->cache;
	क्रम_each_bucket(b, ca) अणु
		b->last_gc = b->gen;
		अगर (!atomic_पढ़ो(&b->pin)) अणु
			SET_GC_MARK(b, 0);
			SET_GC_SECTORS_USED(b, 0);
		पूर्ण
	पूर्ण

	mutex_unlock(&c->bucket_lock);
पूर्ण

अटल व्योम bch_btree_gc_finish(काष्ठा cache_set *c)
अणु
	काष्ठा bucket *b;
	काष्ठा cache *ca;
	अचिन्हित पूर्णांक i, j;
	uपूर्णांक64_t *k;

	mutex_lock(&c->bucket_lock);

	set_gc_sectors(c);
	c->gc_mark_valid = 1;
	c->need_gc	= 0;

	क्रम (i = 0; i < KEY_PTRS(&c->uuid_bucket); i++)
		SET_GC_MARK(PTR_BUCKET(c, &c->uuid_bucket, i),
			    GC_MARK_METADATA);

	/* करोn't reclaim buckets to which ग_लिखोback keys poपूर्णांक */
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < c->devices_max_used; i++) अणु
		काष्ठा bcache_device *d = c->devices[i];
		काष्ठा cached_dev *dc;
		काष्ठा keybuf_key *w, *n;

		अगर (!d || UUID_FLASH_ONLY(&c->uuids[i]))
			जारी;
		dc = container_of(d, काष्ठा cached_dev, disk);

		spin_lock(&dc->ग_लिखोback_keys.lock);
		rbtree_postorder_क्रम_each_entry_safe(w, n,
					&dc->ग_लिखोback_keys.keys, node)
			क्रम (j = 0; j < KEY_PTRS(&w->key); j++)
				SET_GC_MARK(PTR_BUCKET(c, &w->key, j),
					    GC_MARK_सूचीTY);
		spin_unlock(&dc->ग_लिखोback_keys.lock);
	पूर्ण
	rcu_पढ़ो_unlock();

	c->avail_nbuckets = 0;

	ca = c->cache;
	ca->invalidate_needs_gc = 0;

	क्रम (k = ca->sb.d; k < ca->sb.d + ca->sb.keys; k++)
		SET_GC_MARK(ca->buckets + *k, GC_MARK_METADATA);

	क्रम (k = ca->prio_buckets;
	     k < ca->prio_buckets + prio_buckets(ca) * 2; k++)
		SET_GC_MARK(ca->buckets + *k, GC_MARK_METADATA);

	क्रम_each_bucket(b, ca) अणु
		c->need_gc	= max(c->need_gc, bucket_gc_gen(b));

		अगर (atomic_पढ़ो(&b->pin))
			जारी;

		BUG_ON(!GC_MARK(b) && GC_SECTORS_USED(b));

		अगर (!GC_MARK(b) || GC_MARK(b) == GC_MARK_RECLAIMABLE)
			c->avail_nbuckets++;
	पूर्ण

	mutex_unlock(&c->bucket_lock);
पूर्ण

अटल व्योम bch_btree_gc(काष्ठा cache_set *c)
अणु
	पूर्णांक ret;
	काष्ठा gc_stat stats;
	काष्ठा closure ग_लिखोs;
	काष्ठा btree_op op;
	uपूर्णांक64_t start_समय = local_घड़ी();

	trace_bcache_gc_start(c);

	स_रखो(&stats, 0, माप(काष्ठा gc_stat));
	closure_init_stack(&ग_लिखोs);
	bch_btree_op_init(&op, लघु_उच्च);

	btree_gc_start(c);

	/* अगर CACHE_SET_IO_DISABLE set, gc thपढ़ो should stop too */
	करो अणु
		ret = bcache_btree_root(gc_root, c, &op, &ग_लिखोs, &stats);
		closure_sync(&ग_लिखोs);
		cond_resched();

		अगर (ret == -EAGAIN)
			schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies
						       (GC_SLEEP_MS));
		अन्यथा अगर (ret)
			pr_warn("gc failed!\n");
	पूर्ण जबतक (ret && !test_bit(CACHE_SET_IO_DISABLE, &c->flags));

	bch_btree_gc_finish(c);
	wake_up_allocators(c);

	bch_समय_stats_update(&c->btree_gc_समय, start_समय);

	stats.key_bytes *= माप(uपूर्णांक64_t);
	stats.data	<<= 9;
	bch_update_bucket_in_use(c, &stats);
	स_नकल(&c->gc_stats, &stats, माप(काष्ठा gc_stat));

	trace_bcache_gc_end(c);

	bch_moving_gc(c);
पूर्ण

अटल bool gc_should_run(काष्ठा cache_set *c)
अणु
	काष्ठा cache *ca = c->cache;

	अगर (ca->invalidate_needs_gc)
		वापस true;

	अगर (atomic_पढ़ो(&c->sectors_to_gc) < 0)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक bch_gc_thपढ़ो(व्योम *arg)
अणु
	काष्ठा cache_set *c = arg;

	जबतक (1) अणु
		रुको_event_पूर्णांकerruptible(c->gc_रुको,
			   kthपढ़ो_should_stop() ||
			   test_bit(CACHE_SET_IO_DISABLE, &c->flags) ||
			   gc_should_run(c));

		अगर (kthपढ़ो_should_stop() ||
		    test_bit(CACHE_SET_IO_DISABLE, &c->flags))
			अवरोध;

		set_gc_sectors(c);
		bch_btree_gc(c);
	पूर्ण

	रुको_क्रम_kthपढ़ो_stop();
	वापस 0;
पूर्ण

पूर्णांक bch_gc_thपढ़ो_start(काष्ठा cache_set *c)
अणु
	c->gc_thपढ़ो = kthपढ़ो_run(bch_gc_thपढ़ो, c, "bcache_gc");
	वापस PTR_ERR_OR_ZERO(c->gc_thपढ़ो);
पूर्ण

/* Initial partial gc */

अटल पूर्णांक bch_btree_check_recurse(काष्ठा btree *b, काष्ठा btree_op *op)
अणु
	पूर्णांक ret = 0;
	काष्ठा bkey *k, *p = शून्य;
	काष्ठा btree_iter iter;

	क्रम_each_key_filter(&b->keys, k, &iter, bch_ptr_invalid)
		bch_initial_mark_key(b->c, b->level, k);

	bch_initial_mark_key(b->c, b->level + 1, &b->key);

	अगर (b->level) अणु
		bch_btree_iter_init(&b->keys, &iter, शून्य);

		करो अणु
			k = bch_btree_iter_next_filter(&iter, &b->keys,
						       bch_ptr_bad);
			अगर (k) अणु
				btree_node_prefetch(b, k);
				/*
				 * initiallize c->gc_stats.nodes
				 * क्रम incremental GC
				 */
				b->c->gc_stats.nodes++;
			पूर्ण

			अगर (p)
				ret = bcache_btree(check_recurse, p, b, op);

			p = k;
		पूर्ण जबतक (p && !ret);
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक bch_btree_check_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक ret;
	काष्ठा btree_check_info *info = arg;
	काष्ठा btree_check_state *check_state = info->state;
	काष्ठा cache_set *c = check_state->c;
	काष्ठा btree_iter iter;
	काष्ठा bkey *k, *p;
	पूर्णांक cur_idx, prev_idx, skip_nr;

	k = p = शून्य;
	cur_idx = prev_idx = 0;
	ret = 0;

	/* root node keys are checked beक्रमe thपढ़ो created */
	bch_btree_iter_init(&c->root->keys, &iter, शून्य);
	k = bch_btree_iter_next_filter(&iter, &c->root->keys, bch_ptr_bad);
	BUG_ON(!k);

	p = k;
	जबतक (k) अणु
		/*
		 * Fetch a root node key index, skip the keys which
		 * should be fetched by other thपढ़ोs, then check the
		 * sub-tree indexed by the fetched key.
		 */
		spin_lock(&check_state->idx_lock);
		cur_idx = check_state->key_idx;
		check_state->key_idx++;
		spin_unlock(&check_state->idx_lock);

		skip_nr = cur_idx - prev_idx;

		जबतक (skip_nr) अणु
			k = bch_btree_iter_next_filter(&iter,
						       &c->root->keys,
						       bch_ptr_bad);
			अगर (k)
				p = k;
			अन्यथा अणु
				/*
				 * No more keys to check in root node,
				 * current checking thपढ़ोs are enough,
				 * stop creating more.
				 */
				atomic_set(&check_state->enough, 1);
				/* Update check_state->enough earlier */
				smp_mb__after_atomic();
				जाओ out;
			पूर्ण
			skip_nr--;
			cond_resched();
		पूर्ण

		अगर (p) अणु
			काष्ठा btree_op op;

			btree_node_prefetch(c->root, p);
			c->gc_stats.nodes++;
			bch_btree_op_init(&op, 0);
			ret = bcache_btree(check_recurse, p, c->root, &op);
			अगर (ret)
				जाओ out;
		पूर्ण
		p = शून्य;
		prev_idx = cur_idx;
		cond_resched();
	पूर्ण

out:
	info->result = ret;
	/* update check_state->started among all CPUs */
	smp_mb__beक्रमe_atomic();
	अगर (atomic_dec_and_test(&check_state->started))
		wake_up(&check_state->रुको);

	वापस ret;
पूर्ण



अटल पूर्णांक bch_btree_chkthपढ़ो_nr(व्योम)
अणु
	पूर्णांक n = num_online_cpus()/2;

	अगर (n == 0)
		n = 1;
	अन्यथा अगर (n > BCH_BTR_CHKTHREAD_MAX)
		n = BCH_BTR_CHKTHREAD_MAX;

	वापस n;
पूर्ण

पूर्णांक bch_btree_check(काष्ठा cache_set *c)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	काष्ठा bkey *k = शून्य;
	काष्ठा btree_iter iter;
	काष्ठा btree_check_state *check_state;
	अक्षर name[32];

	/* check and mark root node keys */
	क्रम_each_key_filter(&c->root->keys, k, &iter, bch_ptr_invalid)
		bch_initial_mark_key(c, c->root->level, k);

	bch_initial_mark_key(c, c->root->level + 1, &c->root->key);

	अगर (c->root->level == 0)
		वापस 0;

	check_state = kzalloc(माप(काष्ठा btree_check_state), GFP_KERNEL);
	अगर (!check_state)
		वापस -ENOMEM;

	check_state->c = c;
	check_state->total_thपढ़ोs = bch_btree_chkthपढ़ो_nr();
	check_state->key_idx = 0;
	spin_lock_init(&check_state->idx_lock);
	atomic_set(&check_state->started, 0);
	atomic_set(&check_state->enough, 0);
	init_रुकोqueue_head(&check_state->रुको);

	/*
	 * Run multiple thपढ़ोs to check btree nodes in parallel,
	 * अगर check_state->enough is non-zero, it means current
	 * running check thपढ़ोs are enough, unncessary to create
	 * more.
	 */
	क्रम (i = 0; i < check_state->total_thपढ़ोs; i++) अणु
		/* fetch latest check_state->enough earlier */
		smp_mb__beक्रमe_atomic();
		अगर (atomic_पढ़ो(&check_state->enough))
			अवरोध;

		check_state->infos[i].result = 0;
		check_state->infos[i].state = check_state;
		snम_लिखो(name, माप(name), "bch_btrchk[%u]", i);
		atomic_inc(&check_state->started);

		check_state->infos[i].thपढ़ो =
			kthपढ़ो_run(bch_btree_check_thपढ़ो,
				    &check_state->infos[i],
				    name);
		अगर (IS_ERR(check_state->infos[i].thपढ़ो)) अणु
			pr_err("fails to run thread bch_btrchk[%d]\n", i);
			क्रम (--i; i >= 0; i--)
				kthपढ़ो_stop(check_state->infos[i].thपढ़ो);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	रुको_event_पूर्णांकerruptible(check_state->रुको,
				 atomic_पढ़ो(&check_state->started) == 0 ||
				  test_bit(CACHE_SET_IO_DISABLE, &c->flags));

	क्रम (i = 0; i < check_state->total_thपढ़ोs; i++) अणु
		अगर (check_state->infos[i].result) अणु
			ret = check_state->infos[i].result;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	kमुक्त(check_state);
	वापस ret;
पूर्ण

व्योम bch_initial_gc_finish(काष्ठा cache_set *c)
अणु
	काष्ठा cache *ca = c->cache;
	काष्ठा bucket *b;

	bch_btree_gc_finish(c);

	mutex_lock(&c->bucket_lock);

	/*
	 * We need to put some unused buckets directly on the prio मुक्तlist in
	 * order to get the allocator thपढ़ो started - it needs मुक्तd buckets in
	 * order to reग_लिखो the prios and gens, and it needs to reग_लिखो prios
	 * and gens in order to मुक्त buckets.
	 *
	 * This is only safe क्रम buckets that have no live data in them, which
	 * there should always be some of.
	 */
	क्रम_each_bucket(b, ca) अणु
		अगर (fअगरo_full(&ca->मुक्त[RESERVE_PRIO]) &&
		    fअगरo_full(&ca->मुक्त[RESERVE_BTREE]))
			अवरोध;

		अगर (bch_can_invalidate_bucket(ca, b) &&
		    !GC_MARK(b)) अणु
			__bch_invalidate_one_bucket(ca, b);
			अगर (!fअगरo_push(&ca->मुक्त[RESERVE_PRIO],
			   b - ca->buckets))
				fअगरo_push(&ca->मुक्त[RESERVE_BTREE],
					  b - ca->buckets);
		पूर्ण
	पूर्ण

	mutex_unlock(&c->bucket_lock);
पूर्ण

/* Btree insertion */

अटल bool btree_insert_key(काष्ठा btree *b, काष्ठा bkey *k,
			     काष्ठा bkey *replace_key)
अणु
	अचिन्हित पूर्णांक status;

	BUG_ON(bkey_cmp(k, &b->key) > 0);

	status = bch_btree_insert_key(&b->keys, k, replace_key);
	अगर (status != BTREE_INSERT_STATUS_NO_INSERT) अणु
		bch_check_keys(&b->keys, "%u for %s", status,
			       replace_key ? "replace" : "insert");

		trace_bcache_btree_insert_key(b, k, replace_key != शून्य,
					      status);
		वापस true;
	पूर्ण अन्यथा
		वापस false;
पूर्ण

अटल माप_प्रकार insert_u64s_reमुख्यing(काष्ठा btree *b)
अणु
	दीर्घ ret = bch_btree_keys_u64s_reमुख्यing(&b->keys);

	/*
	 * Might land in the middle of an existing extent and have to split it
	 */
	अगर (b->keys.ops->is_extents)
		ret -= KEY_MAX_U64S;

	वापस max(ret, 0L);
पूर्ण

अटल bool bch_btree_insert_keys(काष्ठा btree *b, काष्ठा btree_op *op,
				  काष्ठा keylist *insert_keys,
				  काष्ठा bkey *replace_key)
अणु
	bool ret = false;
	पूर्णांक oldsize = bch_count_data(&b->keys);

	जबतक (!bch_keylist_empty(insert_keys)) अणु
		काष्ठा bkey *k = insert_keys->keys;

		अगर (bkey_u64s(k) > insert_u64s_reमुख्यing(b))
			अवरोध;

		अगर (bkey_cmp(k, &b->key) <= 0) अणु
			अगर (!b->level)
				bkey_put(b->c, k);

			ret |= btree_insert_key(b, k, replace_key);
			bch_keylist_pop_front(insert_keys);
		पूर्ण अन्यथा अगर (bkey_cmp(&START_KEY(k), &b->key) < 0) अणु
			BKEY_PADDED(key) temp;
			bkey_copy(&temp.key, insert_keys->keys);

			bch_cut_back(&b->key, &temp.key);
			bch_cut_front(&b->key, insert_keys->keys);

			ret |= btree_insert_key(b, &temp.key, replace_key);
			अवरोध;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ret)
		op->insert_collision = true;

	BUG_ON(!bch_keylist_empty(insert_keys) && b->level);

	BUG_ON(bch_count_data(&b->keys) < oldsize);
	वापस ret;
पूर्ण

अटल पूर्णांक btree_split(काष्ठा btree *b, काष्ठा btree_op *op,
		       काष्ठा keylist *insert_keys,
		       काष्ठा bkey *replace_key)
अणु
	bool split;
	काष्ठा btree *n1, *n2 = शून्य, *n3 = शून्य;
	uपूर्णांक64_t start_समय = local_घड़ी();
	काष्ठा closure cl;
	काष्ठा keylist parent_keys;

	closure_init_stack(&cl);
	bch_keylist_init(&parent_keys);

	अगर (btree_check_reserve(b, op)) अणु
		अगर (!b->level)
			वापस -EINTR;
		अन्यथा
			WARN(1, "insufficient reserve for split\n");
	पूर्ण

	n1 = btree_node_alloc_replacement(b, op);
	अगर (IS_ERR(n1))
		जाओ err;

	split = set_blocks(btree_bset_first(n1),
			   block_bytes(n1->c->cache)) > (btree_blocks(b) * 4) / 5;

	अगर (split) अणु
		अचिन्हित पूर्णांक keys = 0;

		trace_bcache_btree_node_split(b, btree_bset_first(n1)->keys);

		n2 = bch_btree_node_alloc(b->c, op, b->level, b->parent);
		अगर (IS_ERR(n2))
			जाओ err_मुक्त1;

		अगर (!b->parent) अणु
			n3 = bch_btree_node_alloc(b->c, op, b->level + 1, शून्य);
			अगर (IS_ERR(n3))
				जाओ err_मुक्त2;
		पूर्ण

		mutex_lock(&n1->ग_लिखो_lock);
		mutex_lock(&n2->ग_लिखो_lock);

		bch_btree_insert_keys(n1, op, insert_keys, replace_key);

		/*
		 * Has to be a linear search because we करोn't have an auxiliary
		 * search tree yet
		 */

		जबतक (keys < (btree_bset_first(n1)->keys * 3) / 5)
			keys += bkey_u64s(bset_bkey_idx(btree_bset_first(n1),
							keys));

		bkey_copy_key(&n1->key,
			      bset_bkey_idx(btree_bset_first(n1), keys));
		keys += bkey_u64s(bset_bkey_idx(btree_bset_first(n1), keys));

		btree_bset_first(n2)->keys = btree_bset_first(n1)->keys - keys;
		btree_bset_first(n1)->keys = keys;

		स_नकल(btree_bset_first(n2)->start,
		       bset_bkey_last(btree_bset_first(n1)),
		       btree_bset_first(n2)->keys * माप(uपूर्णांक64_t));

		bkey_copy_key(&n2->key, &b->key);

		bch_keylist_add(&parent_keys, &n2->key);
		bch_btree_node_ग_लिखो(n2, &cl);
		mutex_unlock(&n2->ग_लिखो_lock);
		rw_unlock(true, n2);
	पूर्ण अन्यथा अणु
		trace_bcache_btree_node_compact(b, btree_bset_first(n1)->keys);

		mutex_lock(&n1->ग_लिखो_lock);
		bch_btree_insert_keys(n1, op, insert_keys, replace_key);
	पूर्ण

	bch_keylist_add(&parent_keys, &n1->key);
	bch_btree_node_ग_लिखो(n1, &cl);
	mutex_unlock(&n1->ग_लिखो_lock);

	अगर (n3) अणु
		/* Depth increases, make a new root */
		mutex_lock(&n3->ग_लिखो_lock);
		bkey_copy_key(&n3->key, &MAX_KEY);
		bch_btree_insert_keys(n3, op, &parent_keys, शून्य);
		bch_btree_node_ग_लिखो(n3, &cl);
		mutex_unlock(&n3->ग_लिखो_lock);

		closure_sync(&cl);
		bch_btree_set_root(n3);
		rw_unlock(true, n3);
	पूर्ण अन्यथा अगर (!b->parent) अणु
		/* Root filled up but didn't need to be split */
		closure_sync(&cl);
		bch_btree_set_root(n1);
	पूर्ण अन्यथा अणु
		/* Split a non root node */
		closure_sync(&cl);
		make_btree_मुक्तing_key(b, parent_keys.top);
		bch_keylist_push(&parent_keys);

		bch_btree_insert_node(b->parent, op, &parent_keys, शून्य, शून्य);
		BUG_ON(!bch_keylist_empty(&parent_keys));
	पूर्ण

	btree_node_मुक्त(b);
	rw_unlock(true, n1);

	bch_समय_stats_update(&b->c->btree_split_समय, start_समय);

	वापस 0;
err_मुक्त2:
	bkey_put(b->c, &n2->key);
	btree_node_मुक्त(n2);
	rw_unlock(true, n2);
err_मुक्त1:
	bkey_put(b->c, &n1->key);
	btree_node_मुक्त(n1);
	rw_unlock(true, n1);
err:
	WARN(1, "bcache: btree split failed (level %u)", b->level);

	अगर (n3 == ERR_PTR(-EAGAIN) ||
	    n2 == ERR_PTR(-EAGAIN) ||
	    n1 == ERR_PTR(-EAGAIN))
		वापस -EAGAIN;

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक bch_btree_insert_node(काष्ठा btree *b, काष्ठा btree_op *op,
				 काष्ठा keylist *insert_keys,
				 atomic_t *journal_ref,
				 काष्ठा bkey *replace_key)
अणु
	काष्ठा closure cl;

	BUG_ON(b->level && replace_key);

	closure_init_stack(&cl);

	mutex_lock(&b->ग_लिखो_lock);

	अगर (ग_लिखो_block(b) != btree_bset_last(b) &&
	    b->keys.last_set_unwritten)
		bch_btree_init_next(b); /* just wrote a set */

	अगर (bch_keylist_nkeys(insert_keys) > insert_u64s_reमुख्यing(b)) अणु
		mutex_unlock(&b->ग_लिखो_lock);
		जाओ split;
	पूर्ण

	BUG_ON(ग_लिखो_block(b) != btree_bset_last(b));

	अगर (bch_btree_insert_keys(b, op, insert_keys, replace_key)) अणु
		अगर (!b->level)
			bch_btree_leaf_dirty(b, journal_ref);
		अन्यथा
			bch_btree_node_ग_लिखो(b, &cl);
	पूर्ण

	mutex_unlock(&b->ग_लिखो_lock);

	/* रुको क्रम btree node ग_लिखो अगर necessary, after unlock */
	closure_sync(&cl);

	वापस 0;
split:
	अगर (current->bio_list) अणु
		op->lock = b->c->root->level + 1;
		वापस -EAGAIN;
	पूर्ण अन्यथा अगर (op->lock <= b->c->root->level) अणु
		op->lock = b->c->root->level + 1;
		वापस -EINTR;
	पूर्ण अन्यथा अणु
		/* Invalidated all iterators */
		पूर्णांक ret = btree_split(b, op, insert_keys, replace_key);

		अगर (bch_keylist_empty(insert_keys))
			वापस 0;
		अन्यथा अगर (!ret)
			वापस -EINTR;
		वापस ret;
	पूर्ण
पूर्ण

पूर्णांक bch_btree_insert_check_key(काष्ठा btree *b, काष्ठा btree_op *op,
			       काष्ठा bkey *check_key)
अणु
	पूर्णांक ret = -EINTR;
	uपूर्णांक64_t btree_ptr = b->key.ptr[0];
	अचिन्हित दीर्घ seq = b->seq;
	काष्ठा keylist insert;
	bool upgrade = op->lock == -1;

	bch_keylist_init(&insert);

	अगर (upgrade) अणु
		rw_unlock(false, b);
		rw_lock(true, b, b->level);

		अगर (b->key.ptr[0] != btree_ptr ||
		    b->seq != seq + 1) अणु
			op->lock = b->level;
			जाओ out;
		पूर्ण
	पूर्ण

	SET_KEY_PTRS(check_key, 1);
	get_अक्रमom_bytes(&check_key->ptr[0], माप(uपूर्णांक64_t));

	SET_PTR_DEV(check_key, 0, PTR_CHECK_DEV);

	bch_keylist_add(&insert, check_key);

	ret = bch_btree_insert_node(b, op, &insert, शून्य, शून्य);

	BUG_ON(!ret && !bch_keylist_empty(&insert));
out:
	अगर (upgrade)
		करोwngrade_ग_लिखो(&b->lock);
	वापस ret;
पूर्ण

काष्ठा btree_insert_op अणु
	काष्ठा btree_op	op;
	काष्ठा keylist	*keys;
	atomic_t	*journal_ref;
	काष्ठा bkey	*replace_key;
पूर्ण;

अटल पूर्णांक btree_insert_fn(काष्ठा btree_op *b_op, काष्ठा btree *b)
अणु
	काष्ठा btree_insert_op *op = container_of(b_op,
					काष्ठा btree_insert_op, op);

	पूर्णांक ret = bch_btree_insert_node(b, &op->op, op->keys,
					op->journal_ref, op->replace_key);
	अगर (ret && !bch_keylist_empty(op->keys))
		वापस ret;
	अन्यथा
		वापस MAP_DONE;
पूर्ण

पूर्णांक bch_btree_insert(काष्ठा cache_set *c, काष्ठा keylist *keys,
		     atomic_t *journal_ref, काष्ठा bkey *replace_key)
अणु
	काष्ठा btree_insert_op op;
	पूर्णांक ret = 0;

	BUG_ON(current->bio_list);
	BUG_ON(bch_keylist_empty(keys));

	bch_btree_op_init(&op.op, 0);
	op.keys		= keys;
	op.journal_ref	= journal_ref;
	op.replace_key	= replace_key;

	जबतक (!ret && !bch_keylist_empty(keys)) अणु
		op.op.lock = 0;
		ret = bch_btree_map_leaf_nodes(&op.op, c,
					       &START_KEY(keys->keys),
					       btree_insert_fn);
	पूर्ण

	अगर (ret) अणु
		काष्ठा bkey *k;

		pr_err("error %i\n", ret);

		जबतक ((k = bch_keylist_pop(keys)))
			bkey_put(c, k);
	पूर्ण अन्यथा अगर (op.op.insert_collision)
		ret = -ESRCH;

	वापस ret;
पूर्ण

व्योम bch_btree_set_root(काष्ठा btree *b)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा closure cl;

	closure_init_stack(&cl);

	trace_bcache_btree_set_root(b);

	BUG_ON(!b->written);

	क्रम (i = 0; i < KEY_PTRS(&b->key); i++)
		BUG_ON(PTR_BUCKET(b->c, &b->key, i)->prio != BTREE_PRIO);

	mutex_lock(&b->c->bucket_lock);
	list_del_init(&b->list);
	mutex_unlock(&b->c->bucket_lock);

	b->c->root = b;

	bch_journal_meta(b->c, &cl);
	closure_sync(&cl);
पूर्ण

/* Map across nodes or keys */

अटल पूर्णांक bch_btree_map_nodes_recurse(काष्ठा btree *b, काष्ठा btree_op *op,
				       काष्ठा bkey *from,
				       btree_map_nodes_fn *fn, पूर्णांक flags)
अणु
	पूर्णांक ret = MAP_CONTINUE;

	अगर (b->level) अणु
		काष्ठा bkey *k;
		काष्ठा btree_iter iter;

		bch_btree_iter_init(&b->keys, &iter, from);

		जबतक ((k = bch_btree_iter_next_filter(&iter, &b->keys,
						       bch_ptr_bad))) अणु
			ret = bcache_btree(map_nodes_recurse, k, b,
				    op, from, fn, flags);
			from = शून्य;

			अगर (ret != MAP_CONTINUE)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (!b->level || flags == MAP_ALL_NODES)
		ret = fn(op, b);

	वापस ret;
पूर्ण

पूर्णांक __bch_btree_map_nodes(काष्ठा btree_op *op, काष्ठा cache_set *c,
			  काष्ठा bkey *from, btree_map_nodes_fn *fn, पूर्णांक flags)
अणु
	वापस bcache_btree_root(map_nodes_recurse, c, op, from, fn, flags);
पूर्ण

पूर्णांक bch_btree_map_keys_recurse(काष्ठा btree *b, काष्ठा btree_op *op,
				      काष्ठा bkey *from, btree_map_keys_fn *fn,
				      पूर्णांक flags)
अणु
	पूर्णांक ret = MAP_CONTINUE;
	काष्ठा bkey *k;
	काष्ठा btree_iter iter;

	bch_btree_iter_init(&b->keys, &iter, from);

	जबतक ((k = bch_btree_iter_next_filter(&iter, &b->keys, bch_ptr_bad))) अणु
		ret = !b->level
			? fn(op, b, k)
			: bcache_btree(map_keys_recurse, k,
				       b, op, from, fn, flags);
		from = शून्य;

		अगर (ret != MAP_CONTINUE)
			वापस ret;
	पूर्ण

	अगर (!b->level && (flags & MAP_END_KEY))
		ret = fn(op, b, &KEY(KEY_INODE(&b->key),
				     KEY_OFFSET(&b->key), 0));

	वापस ret;
पूर्ण

पूर्णांक bch_btree_map_keys(काष्ठा btree_op *op, काष्ठा cache_set *c,
		       काष्ठा bkey *from, btree_map_keys_fn *fn, पूर्णांक flags)
अणु
	वापस bcache_btree_root(map_keys_recurse, c, op, from, fn, flags);
पूर्ण

/* Keybuf code */

अटल अंतरभूत पूर्णांक keybuf_cmp(काष्ठा keybuf_key *l, काष्ठा keybuf_key *r)
अणु
	/* Overlapping keys compare equal */
	अगर (bkey_cmp(&l->key, &START_KEY(&r->key)) <= 0)
		वापस -1;
	अगर (bkey_cmp(&START_KEY(&l->key), &r->key) >= 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक keybuf_nonoverlapping_cmp(काष्ठा keybuf_key *l,
					    काष्ठा keybuf_key *r)
अणु
	वापस clamp_t(पूर्णांक64_t, bkey_cmp(&l->key, &r->key), -1, 1);
पूर्ण

काष्ठा refill अणु
	काष्ठा btree_op	op;
	अचिन्हित पूर्णांक	nr_found;
	काष्ठा keybuf	*buf;
	काष्ठा bkey	*end;
	keybuf_pred_fn	*pred;
पूर्ण;

अटल पूर्णांक refill_keybuf_fn(काष्ठा btree_op *op, काष्ठा btree *b,
			    काष्ठा bkey *k)
अणु
	काष्ठा refill *refill = container_of(op, काष्ठा refill, op);
	काष्ठा keybuf *buf = refill->buf;
	पूर्णांक ret = MAP_CONTINUE;

	अगर (bkey_cmp(k, refill->end) > 0) अणु
		ret = MAP_DONE;
		जाओ out;
	पूर्ण

	अगर (!KEY_SIZE(k)) /* end key */
		जाओ out;

	अगर (refill->pred(buf, k)) अणु
		काष्ठा keybuf_key *w;

		spin_lock(&buf->lock);

		w = array_alloc(&buf->मुक्तlist);
		अगर (!w) अणु
			spin_unlock(&buf->lock);
			वापस MAP_DONE;
		पूर्ण

		w->निजी = शून्य;
		bkey_copy(&w->key, k);

		अगर (RB_INSERT(&buf->keys, w, node, keybuf_cmp))
			array_मुक्त(&buf->मुक्तlist, w);
		अन्यथा
			refill->nr_found++;

		अगर (array_मुक्तlist_empty(&buf->मुक्तlist))
			ret = MAP_DONE;

		spin_unlock(&buf->lock);
	पूर्ण
out:
	buf->last_scanned = *k;
	वापस ret;
पूर्ण

व्योम bch_refill_keybuf(काष्ठा cache_set *c, काष्ठा keybuf *buf,
		       काष्ठा bkey *end, keybuf_pred_fn *pred)
अणु
	काष्ठा bkey start = buf->last_scanned;
	काष्ठा refill refill;

	cond_resched();

	bch_btree_op_init(&refill.op, -1);
	refill.nr_found	= 0;
	refill.buf	= buf;
	refill.end	= end;
	refill.pred	= pred;

	bch_btree_map_keys(&refill.op, c, &buf->last_scanned,
			   refill_keybuf_fn, MAP_END_KEY);

	trace_bcache_keyscan(refill.nr_found,
			     KEY_INODE(&start), KEY_OFFSET(&start),
			     KEY_INODE(&buf->last_scanned),
			     KEY_OFFSET(&buf->last_scanned));

	spin_lock(&buf->lock);

	अगर (!RB_EMPTY_ROOT(&buf->keys)) अणु
		काष्ठा keybuf_key *w;

		w = RB_FIRST(&buf->keys, काष्ठा keybuf_key, node);
		buf->start	= START_KEY(&w->key);

		w = RB_LAST(&buf->keys, काष्ठा keybuf_key, node);
		buf->end	= w->key;
	पूर्ण अन्यथा अणु
		buf->start	= MAX_KEY;
		buf->end	= MAX_KEY;
	पूर्ण

	spin_unlock(&buf->lock);
पूर्ण

अटल व्योम __bch_keybuf_del(काष्ठा keybuf *buf, काष्ठा keybuf_key *w)
अणु
	rb_erase(&w->node, &buf->keys);
	array_मुक्त(&buf->मुक्तlist, w);
पूर्ण

व्योम bch_keybuf_del(काष्ठा keybuf *buf, काष्ठा keybuf_key *w)
अणु
	spin_lock(&buf->lock);
	__bch_keybuf_del(buf, w);
	spin_unlock(&buf->lock);
पूर्ण

bool bch_keybuf_check_overlapping(काष्ठा keybuf *buf, काष्ठा bkey *start,
				  काष्ठा bkey *end)
अणु
	bool ret = false;
	काष्ठा keybuf_key *p, *w, s;

	s.key = *start;

	अगर (bkey_cmp(end, &buf->start) <= 0 ||
	    bkey_cmp(start, &buf->end) >= 0)
		वापस false;

	spin_lock(&buf->lock);
	w = RB_GREATER(&buf->keys, s, node, keybuf_nonoverlapping_cmp);

	जबतक (w && bkey_cmp(&START_KEY(&w->key), end) < 0) अणु
		p = w;
		w = RB_NEXT(w, node);

		अगर (p->निजी)
			ret = true;
		अन्यथा
			__bch_keybuf_del(buf, p);
	पूर्ण

	spin_unlock(&buf->lock);
	वापस ret;
पूर्ण

काष्ठा keybuf_key *bch_keybuf_next(काष्ठा keybuf *buf)
अणु
	काष्ठा keybuf_key *w;

	spin_lock(&buf->lock);

	w = RB_FIRST(&buf->keys, काष्ठा keybuf_key, node);

	जबतक (w && w->निजी)
		w = RB_NEXT(w, node);

	अगर (w)
		w->निजी = ERR_PTR(-EINTR);

	spin_unlock(&buf->lock);
	वापस w;
पूर्ण

काष्ठा keybuf_key *bch_keybuf_next_rescan(काष्ठा cache_set *c,
					  काष्ठा keybuf *buf,
					  काष्ठा bkey *end,
					  keybuf_pred_fn *pred)
अणु
	काष्ठा keybuf_key *ret;

	जबतक (1) अणु
		ret = bch_keybuf_next(buf);
		अगर (ret)
			अवरोध;

		अगर (bkey_cmp(&buf->last_scanned, end) >= 0) अणु
			pr_debug("scan finished\n");
			अवरोध;
		पूर्ण

		bch_refill_keybuf(c, buf, end, pred);
	पूर्ण

	वापस ret;
पूर्ण

व्योम bch_keybuf_init(काष्ठा keybuf *buf)
अणु
	buf->last_scanned	= MAX_KEY;
	buf->keys		= RB_ROOT;

	spin_lock_init(&buf->lock);
	array_allocator_init(&buf->मुक्तlist);
पूर्ण

व्योम bch_btree_निकास(व्योम)
अणु
	अगर (btree_io_wq)
		destroy_workqueue(btree_io_wq);
पूर्ण

पूर्णांक __init bch_btree_init(व्योम)
अणु
	btree_io_wq = alloc_workqueue("bch_btree_io", WQ_MEM_RECLAIM, 0);
	अगर (!btree_io_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
