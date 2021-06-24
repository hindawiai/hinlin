<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Primary bucket allocation code
 *
 * Copyright 2012 Google, Inc.
 *
 * Allocation in bcache is करोne in terms of buckets:
 *
 * Each bucket has associated an 8 bit gen; this gen corresponds to the gen in
 * btree poपूर्णांकers - they must match क्रम the poपूर्णांकer to be considered valid.
 *
 * Thus (assuming a bucket has no dirty data or metadata in it) we can reuse a
 * bucket simply by incrementing its gen.
 *
 * The gens (aदीर्घ with the priorities; it's really the gens are important but
 * the code is named as अगर it's the priorities) are written in an arbitrary list
 * of buckets on disk, with a poपूर्णांकer to them in the journal header.
 *
 * When we invalidate a bucket, we have to ग_लिखो its new gen to disk and रुको
 * क्रम that ग_लिखो to complete beक्रमe we use it - otherwise after a crash we
 * could have poपूर्णांकers that appeared to be good but poपूर्णांकed to data that had
 * been overwritten.
 *
 * Since the gens and priorities are all stored contiguously on disk, we can
 * batch this up: We fill up the मुक्त_inc list with freshly invalidated buckets,
 * call prio_ग_लिखो(), and when prio_ग_लिखो() finishes we pull buckets off the
 * मुक्त_inc list and optionally discard them.
 *
 * मुक्त_inc isn't the only freelist - if it was, we'd often to sleep जबतक
 * priorities and gens were being written beक्रमe we could allocate. c->मुक्त is a
 * smaller मुक्तlist, and buckets on that list are always पढ़ोy to be used.
 *
 * If we've got discards enabled, that happens when a bucket moves from the
 * मुक्त_inc list to the मुक्त list.
 *
 * There is another मुक्तlist, because someबार we have buckets that we know
 * have nothing poपूर्णांकing पूर्णांकo them - these we can reuse without रुकोing क्रम
 * priorities to be rewritten. These come from मुक्तd btree nodes and buckets
 * that garbage collection discovered no दीर्घer had valid keys poपूर्णांकing पूर्णांकo
 * them (because they were overwritten). That's the unused list - buckets on the
 * unused list move to the मुक्त list, optionally being discarded in the process.
 *
 * It's also important to ensure that gens don't wrap around - with respect to
 * either the oldest gen in the btree or the gen on disk. This is quite
 * dअगरficult to करो in practice, but we explicitly guard against it anyways - अगर
 * a bucket is in danger of wrapping around we simply skip invalidating it that
 * समय around, and we garbage collect or reग_लिखो the priorities sooner than we
 * would have otherwise.
 *
 * bch_bucket_alloc() allocates a single bucket from a specअगरic cache.
 *
 * bch_bucket_alloc_set() allocates one  bucket from dअगरferent caches
 * out of a cache set.
 *
 * मुक्त_some_buckets() drives all the processes described above. It's called
 * from bch_bucket_alloc() and a few other places that need to make sure मुक्त
 * buckets are पढ़ोy.
 *
 * invalidate_buckets_(lru|fअगरo)() find buckets that are available to be
 * invalidated, and then invalidate them and stick them on the मुक्त_inc list -
 * in either lru or fअगरo order.
 */

#समावेश "bcache.h"
#समावेश "btree.h"

#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/अक्रमom.h>
#समावेश <trace/events/bcache.h>

#घोषणा MAX_OPEN_BUCKETS 128

/* Bucket heap / gen */

uपूर्णांक8_t bch_inc_gen(काष्ठा cache *ca, काष्ठा bucket *b)
अणु
	uपूर्णांक8_t ret = ++b->gen;

	ca->set->need_gc = max(ca->set->need_gc, bucket_gc_gen(b));
	WARN_ON_ONCE(ca->set->need_gc > BUCKET_GC_GEN_MAX);

	वापस ret;
पूर्ण

व्योम bch_rescale_priorities(काष्ठा cache_set *c, पूर्णांक sectors)
अणु
	काष्ठा cache *ca;
	काष्ठा bucket *b;
	अचिन्हित दीर्घ next = c->nbuckets * c->cache->sb.bucket_size / 1024;
	पूर्णांक r;

	atomic_sub(sectors, &c->rescale);

	करो अणु
		r = atomic_पढ़ो(&c->rescale);

		अगर (r >= 0)
			वापस;
	पूर्ण जबतक (atomic_cmpxchg(&c->rescale, r, r + next) != r);

	mutex_lock(&c->bucket_lock);

	c->min_prio = अच_लघु_उच्च;

	ca = c->cache;
	क्रम_each_bucket(b, ca)
		अगर (b->prio &&
		    b->prio != BTREE_PRIO &&
		    !atomic_पढ़ो(&b->pin)) अणु
			b->prio--;
			c->min_prio = min(c->min_prio, b->prio);
		पूर्ण

	mutex_unlock(&c->bucket_lock);
पूर्ण

/*
 * Background allocation thपढ़ो: scans क्रम buckets to be invalidated,
 * invalidates them, reग_लिखोs prios/gens (marking them as invalidated on disk),
 * then optionally issues discard commands to the newly मुक्त buckets, then माला_दो
 * them on the various मुक्तlists.
 */

अटल अंतरभूत bool can_inc_bucket_gen(काष्ठा bucket *b)
अणु
	वापस bucket_gc_gen(b) < BUCKET_GC_GEN_MAX;
पूर्ण

bool bch_can_invalidate_bucket(काष्ठा cache *ca, काष्ठा bucket *b)
अणु
	BUG_ON(!ca->set->gc_mark_valid);

	वापस (!GC_MARK(b) ||
		GC_MARK(b) == GC_MARK_RECLAIMABLE) &&
		!atomic_पढ़ो(&b->pin) &&
		can_inc_bucket_gen(b);
पूर्ण

व्योम __bch_invalidate_one_bucket(काष्ठा cache *ca, काष्ठा bucket *b)
अणु
	lockdep_निश्चित_held(&ca->set->bucket_lock);
	BUG_ON(GC_MARK(b) && GC_MARK(b) != GC_MARK_RECLAIMABLE);

	अगर (GC_SECTORS_USED(b))
		trace_bcache_invalidate(ca, b - ca->buckets);

	bch_inc_gen(ca, b);
	b->prio = INITIAL_PRIO;
	atomic_inc(&b->pin);
पूर्ण

अटल व्योम bch_invalidate_one_bucket(काष्ठा cache *ca, काष्ठा bucket *b)
अणु
	__bch_invalidate_one_bucket(ca, b);

	fअगरo_push(&ca->मुक्त_inc, b - ca->buckets);
पूर्ण

/*
 * Determines what order we're going to reuse buckets, smallest bucket_prio()
 * first: we also take पूर्णांकo account the number of sectors of live data in that
 * bucket, and in order क्रम that multiply to make sense we have to scale bucket
 *
 * Thus, we scale the bucket priorities so that the bucket with the smallest
 * prio is worth 1/8th of what INITIAL_PRIO is worth.
 */

#घोषणा bucket_prio(b)							\
(अणु									\
	अचिन्हित पूर्णांक min_prio = (INITIAL_PRIO - ca->set->min_prio) / 8;	\
									\
	(b->prio - ca->set->min_prio + min_prio) * GC_SECTORS_USED(b);	\
पूर्ण)

#घोषणा bucket_max_cmp(l, r)	(bucket_prio(l) < bucket_prio(r))
#घोषणा bucket_min_cmp(l, r)	(bucket_prio(l) > bucket_prio(r))

अटल व्योम invalidate_buckets_lru(काष्ठा cache *ca)
अणु
	काष्ठा bucket *b;
	sमाप_प्रकार i;

	ca->heap.used = 0;

	क्रम_each_bucket(b, ca) अणु
		अगर (!bch_can_invalidate_bucket(ca, b))
			जारी;

		अगर (!heap_full(&ca->heap))
			heap_add(&ca->heap, b, bucket_max_cmp);
		अन्यथा अगर (bucket_max_cmp(b, heap_peek(&ca->heap))) अणु
			ca->heap.data[0] = b;
			heap_sअगरt(&ca->heap, 0, bucket_max_cmp);
		पूर्ण
	पूर्ण

	क्रम (i = ca->heap.used / 2 - 1; i >= 0; --i)
		heap_sअगरt(&ca->heap, i, bucket_min_cmp);

	जबतक (!fअगरo_full(&ca->मुक्त_inc)) अणु
		अगर (!heap_pop(&ca->heap, b, bucket_min_cmp)) अणु
			/*
			 * We करोn't want to be calling invalidate_buckets()
			 * multiple बार when it can't करो anything
			 */
			ca->invalidate_needs_gc = 1;
			wake_up_gc(ca->set);
			वापस;
		पूर्ण

		bch_invalidate_one_bucket(ca, b);
	पूर्ण
पूर्ण

अटल व्योम invalidate_buckets_fअगरo(काष्ठा cache *ca)
अणु
	काष्ठा bucket *b;
	माप_प्रकार checked = 0;

	जबतक (!fअगरo_full(&ca->मुक्त_inc)) अणु
		अगर (ca->fअगरo_last_bucket <  ca->sb.first_bucket ||
		    ca->fअगरo_last_bucket >= ca->sb.nbuckets)
			ca->fअगरo_last_bucket = ca->sb.first_bucket;

		b = ca->buckets + ca->fअगरo_last_bucket++;

		अगर (bch_can_invalidate_bucket(ca, b))
			bch_invalidate_one_bucket(ca, b);

		अगर (++checked >= ca->sb.nbuckets) अणु
			ca->invalidate_needs_gc = 1;
			wake_up_gc(ca->set);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम invalidate_buckets_अक्रमom(काष्ठा cache *ca)
अणु
	काष्ठा bucket *b;
	माप_प्रकार checked = 0;

	जबतक (!fअगरo_full(&ca->मुक्त_inc)) अणु
		माप_प्रकार n;

		get_अक्रमom_bytes(&n, माप(n));

		n %= (माप_प्रकार) (ca->sb.nbuckets - ca->sb.first_bucket);
		n += ca->sb.first_bucket;

		b = ca->buckets + n;

		अगर (bch_can_invalidate_bucket(ca, b))
			bch_invalidate_one_bucket(ca, b);

		अगर (++checked >= ca->sb.nbuckets / 2) अणु
			ca->invalidate_needs_gc = 1;
			wake_up_gc(ca->set);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम invalidate_buckets(काष्ठा cache *ca)
अणु
	BUG_ON(ca->invalidate_needs_gc);

	चयन (CACHE_REPLACEMENT(&ca->sb)) अणु
	हाल CACHE_REPLACEMENT_LRU:
		invalidate_buckets_lru(ca);
		अवरोध;
	हाल CACHE_REPLACEMENT_FIFO:
		invalidate_buckets_fअगरo(ca);
		अवरोध;
	हाल CACHE_REPLACEMENT_RANDOM:
		invalidate_buckets_अक्रमom(ca);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा allocator_रुको(ca, cond)					\
करो अणु									\
	जबतक (1) अणु							\
		set_current_state(TASK_INTERRUPTIBLE);			\
		अगर (cond)						\
			अवरोध;						\
									\
		mutex_unlock(&(ca)->set->bucket_lock);			\
		अगर (kthपढ़ो_should_stop() ||				\
		    test_bit(CACHE_SET_IO_DISABLE, &ca->set->flags)) अणु	\
			set_current_state(TASK_RUNNING);		\
			जाओ out;					\
		पूर्ण							\
									\
		schedule();						\
		mutex_lock(&(ca)->set->bucket_lock);			\
	पूर्ण								\
	__set_current_state(TASK_RUNNING);				\
पूर्ण जबतक (0)

अटल पूर्णांक bch_allocator_push(काष्ठा cache *ca, दीर्घ bucket)
अणु
	अचिन्हित पूर्णांक i;

	/* Prios/gens are actually the most important reserve */
	अगर (fअगरo_push(&ca->मुक्त[RESERVE_PRIO], bucket))
		वापस true;

	क्रम (i = 0; i < RESERVE_NR; i++)
		अगर (fअगरo_push(&ca->मुक्त[i], bucket))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक bch_allocator_thपढ़ो(व्योम *arg)
अणु
	काष्ठा cache *ca = arg;

	mutex_lock(&ca->set->bucket_lock);

	जबतक (1) अणु
		/*
		 * First, we pull buckets off of the unused and मुक्त_inc lists,
		 * possibly issue discards to them, then we add the bucket to
		 * the मुक्त list:
		 */
		जबतक (1) अणु
			दीर्घ bucket;

			अगर (!fअगरo_pop(&ca->मुक्त_inc, bucket))
				अवरोध;

			अगर (ca->discard) अणु
				mutex_unlock(&ca->set->bucket_lock);
				blkdev_issue_discard(ca->bdev,
					bucket_to_sector(ca->set, bucket),
					ca->sb.bucket_size, GFP_KERNEL, 0);
				mutex_lock(&ca->set->bucket_lock);
			पूर्ण

			allocator_रुको(ca, bch_allocator_push(ca, bucket));
			wake_up(&ca->set->btree_cache_रुको);
			wake_up(&ca->set->bucket_रुको);
		पूर्ण

		/*
		 * We've run out of मुक्त buckets, we need to find some buckets
		 * we can invalidate. First, invalidate them in memory and add
		 * them to the मुक्त_inc list:
		 */

retry_invalidate:
		allocator_रुको(ca, ca->set->gc_mark_valid &&
			       !ca->invalidate_needs_gc);
		invalidate_buckets(ca);

		/*
		 * Now, we ग_लिखो their new gens to disk so we can start writing
		 * new stuff to them:
		 */
		allocator_रुको(ca, !atomic_पढ़ो(&ca->set->prio_blocked));
		अगर (CACHE_SYNC(&ca->sb)) अणु
			/*
			 * This could deadlock अगर an allocation with a btree
			 * node locked ever blocked - having the btree node
			 * locked would block garbage collection, but here we're
			 * रुकोing on garbage collection beक्रमe we invalidate
			 * and मुक्त anything.
			 *
			 * But this should be safe since the btree code always
			 * uses btree_check_reserve() beक्रमe allocating now, and
			 * अगर it fails it blocks without btree nodes locked.
			 */
			अगर (!fअगरo_full(&ca->मुक्त_inc))
				जाओ retry_invalidate;

			अगर (bch_prio_ग_लिखो(ca, false) < 0) अणु
				ca->invalidate_needs_gc = 1;
				wake_up_gc(ca->set);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	रुको_क्रम_kthपढ़ो_stop();
	वापस 0;
पूर्ण

/* Allocation */

दीर्घ bch_bucket_alloc(काष्ठा cache *ca, अचिन्हित पूर्णांक reserve, bool रुको)
अणु
	DEFINE_WAIT(w);
	काष्ठा bucket *b;
	दीर्घ r;


	/* No allocation अगर CACHE_SET_IO_DISABLE bit is set */
	अगर (unlikely(test_bit(CACHE_SET_IO_DISABLE, &ca->set->flags)))
		वापस -1;

	/* fastpath */
	अगर (fअगरo_pop(&ca->मुक्त[RESERVE_NONE], r) ||
	    fअगरo_pop(&ca->मुक्त[reserve], r))
		जाओ out;

	अगर (!रुको) अणु
		trace_bcache_alloc_fail(ca, reserve);
		वापस -1;
	पूर्ण

	करो अणु
		prepare_to_रुको(&ca->set->bucket_रुको, &w,
				TASK_UNINTERRUPTIBLE);

		mutex_unlock(&ca->set->bucket_lock);
		schedule();
		mutex_lock(&ca->set->bucket_lock);
	पूर्ण जबतक (!fअगरo_pop(&ca->मुक्त[RESERVE_NONE], r) &&
		 !fअगरo_pop(&ca->मुक्त[reserve], r));

	finish_रुको(&ca->set->bucket_रुको, &w);
out:
	अगर (ca->alloc_thपढ़ो)
		wake_up_process(ca->alloc_thपढ़ो);

	trace_bcache_alloc(ca, reserve);

	अगर (expensive_debug_checks(ca->set)) अणु
		माप_प्रकार iter;
		दीर्घ i;
		अचिन्हित पूर्णांक j;

		क्रम (iter = 0; iter < prio_buckets(ca) * 2; iter++)
			BUG_ON(ca->prio_buckets[iter] == (uपूर्णांक64_t) r);

		क्रम (j = 0; j < RESERVE_NR; j++)
			fअगरo_क्रम_each(i, &ca->मुक्त[j], iter)
				BUG_ON(i == r);
		fअगरo_क्रम_each(i, &ca->मुक्त_inc, iter)
			BUG_ON(i == r);
	पूर्ण

	b = ca->buckets + r;

	BUG_ON(atomic_पढ़ो(&b->pin) != 1);

	SET_GC_SECTORS_USED(b, ca->sb.bucket_size);

	अगर (reserve <= RESERVE_PRIO) अणु
		SET_GC_MARK(b, GC_MARK_METADATA);
		SET_GC_MOVE(b, 0);
		b->prio = BTREE_PRIO;
	पूर्ण अन्यथा अणु
		SET_GC_MARK(b, GC_MARK_RECLAIMABLE);
		SET_GC_MOVE(b, 0);
		b->prio = INITIAL_PRIO;
	पूर्ण

	अगर (ca->set->avail_nbuckets > 0) अणु
		ca->set->avail_nbuckets--;
		bch_update_bucket_in_use(ca->set, &ca->set->gc_stats);
	पूर्ण

	वापस r;
पूर्ण

व्योम __bch_bucket_मुक्त(काष्ठा cache *ca, काष्ठा bucket *b)
अणु
	SET_GC_MARK(b, 0);
	SET_GC_SECTORS_USED(b, 0);

	अगर (ca->set->avail_nbuckets < ca->set->nbuckets) अणु
		ca->set->avail_nbuckets++;
		bch_update_bucket_in_use(ca->set, &ca->set->gc_stats);
	पूर्ण
पूर्ण

व्योम bch_bucket_मुक्त(काष्ठा cache_set *c, काष्ठा bkey *k)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < KEY_PTRS(k); i++)
		__bch_bucket_मुक्त(c->cache, PTR_BUCKET(c, k, i));
पूर्ण

पूर्णांक __bch_bucket_alloc_set(काष्ठा cache_set *c, अचिन्हित पूर्णांक reserve,
			   काष्ठा bkey *k, bool रुको)
अणु
	काष्ठा cache *ca;
	दीर्घ b;

	/* No allocation अगर CACHE_SET_IO_DISABLE bit is set */
	अगर (unlikely(test_bit(CACHE_SET_IO_DISABLE, &c->flags)))
		वापस -1;

	lockdep_निश्चित_held(&c->bucket_lock);

	bkey_init(k);

	ca = c->cache;
	b = bch_bucket_alloc(ca, reserve, रुको);
	अगर (b == -1)
		जाओ err;

	k->ptr[0] = MAKE_PTR(ca->buckets[b].gen,
			     bucket_to_sector(c, b),
			     ca->sb.nr_this_dev);

	SET_KEY_PTRS(k, 1);

	वापस 0;
err:
	bch_bucket_मुक्त(c, k);
	bkey_put(c, k);
	वापस -1;
पूर्ण

पूर्णांक bch_bucket_alloc_set(काष्ठा cache_set *c, अचिन्हित पूर्णांक reserve,
			 काष्ठा bkey *k, bool रुको)
अणु
	पूर्णांक ret;

	mutex_lock(&c->bucket_lock);
	ret = __bch_bucket_alloc_set(c, reserve, k, रुको);
	mutex_unlock(&c->bucket_lock);
	वापस ret;
पूर्ण

/* Sector allocator */

काष्ठा खोलो_bucket अणु
	काष्ठा list_head	list;
	अचिन्हित पूर्णांक		last_ग_लिखो_poपूर्णांक;
	अचिन्हित पूर्णांक		sectors_मुक्त;
	BKEY_PADDED(key);
पूर्ण;

/*
 * We keep multiple buckets खोलो क्रम ग_लिखोs, and try to segregate dअगरferent
 * ग_लिखो streams क्रम better cache utilization: first we try to segregate flash
 * only volume ग_लिखो streams from cached devices, secondly we look क्रम a bucket
 * where the last ग_लिखो to it was sequential with the current ग_लिखो, and
 * failing that we look क्रम a bucket that was last used by the same task.
 *
 * The ideas is अगर you've got multiple tasks pulling data पूर्णांकo the cache at the
 * same समय, you'll get better cache utilization अगर you try to segregate their
 * data and preserve locality.
 *
 * For example, dirty sectors of flash only volume is not reclaimable, अगर their
 * dirty sectors mixed with dirty sectors of cached device, such buckets will
 * be marked as dirty and won't be reclaimed, though the dirty data of cached
 * device have been written back to backend device.
 *
 * And say you've starting Firefox at the same time you're copying a
 * bunch of files. Firefox will likely end up being fairly hot and stay in the
 * cache aजबतक, but the data you copied might not be; अगर you wrote all that
 * data to the same buckets it'd get invalidated at the same समय.
 *
 * Both of those tasks will be करोing fairly अक्रमom IO so we can't rely on
 * detecting sequential IO to segregate their data, but going off of the task
 * should be a sane heuristic.
 */
अटल काष्ठा खोलो_bucket *pick_data_bucket(काष्ठा cache_set *c,
					    स्थिर काष्ठा bkey *search,
					    अचिन्हित पूर्णांक ग_लिखो_poपूर्णांक,
					    काष्ठा bkey *alloc)
अणु
	काष्ठा खोलो_bucket *ret, *ret_task = शून्य;

	list_क्रम_each_entry_reverse(ret, &c->data_buckets, list)
		अगर (UUID_FLASH_ONLY(&c->uuids[KEY_INODE(&ret->key)]) !=
		    UUID_FLASH_ONLY(&c->uuids[KEY_INODE(search)]))
			जारी;
		अन्यथा अगर (!bkey_cmp(&ret->key, search))
			जाओ found;
		अन्यथा अगर (ret->last_ग_लिखो_poपूर्णांक == ग_लिखो_poपूर्णांक)
			ret_task = ret;

	ret = ret_task ?: list_first_entry(&c->data_buckets,
					   काष्ठा खोलो_bucket, list);
found:
	अगर (!ret->sectors_मुक्त && KEY_PTRS(alloc)) अणु
		ret->sectors_मुक्त = c->cache->sb.bucket_size;
		bkey_copy(&ret->key, alloc);
		bkey_init(alloc);
	पूर्ण

	अगर (!ret->sectors_मुक्त)
		ret = शून्य;

	वापस ret;
पूर्ण

/*
 * Allocates some space in the cache to ग_लिखो to, and k to poपूर्णांक to the newly
 * allocated space, and updates KEY_SIZE(k) and KEY_OFFSET(k) (to poपूर्णांक to the
 * end of the newly allocated space).
 *
 * May allocate fewer sectors than @sectors, KEY_SIZE(k) indicates how many
 * sectors were actually allocated.
 *
 * If s->ग_लिखोback is true, will not fail.
 */
bool bch_alloc_sectors(काष्ठा cache_set *c,
		       काष्ठा bkey *k,
		       अचिन्हित पूर्णांक sectors,
		       अचिन्हित पूर्णांक ग_लिखो_poपूर्णांक,
		       अचिन्हित पूर्णांक ग_लिखो_prio,
		       bool रुको)
अणु
	काष्ठा खोलो_bucket *b;
	BKEY_PADDED(key) alloc;
	अचिन्हित पूर्णांक i;

	/*
	 * We might have to allocate a new bucket, which we can't करो with a
	 * spinlock held. So अगर we have to allocate, we drop the lock, allocate
	 * and then retry. KEY_PTRS() indicates whether alloc poपूर्णांकs to
	 * allocated bucket(s).
	 */

	bkey_init(&alloc.key);
	spin_lock(&c->data_bucket_lock);

	जबतक (!(b = pick_data_bucket(c, k, ग_लिखो_poपूर्णांक, &alloc.key))) अणु
		अचिन्हित पूर्णांक watermark = ग_लिखो_prio
			? RESERVE_MOVINGGC
			: RESERVE_NONE;

		spin_unlock(&c->data_bucket_lock);

		अगर (bch_bucket_alloc_set(c, watermark, &alloc.key, रुको))
			वापस false;

		spin_lock(&c->data_bucket_lock);
	पूर्ण

	/*
	 * If we had to allocate, we might race and not need to allocate the
	 * second समय we call pick_data_bucket(). If we allocated a bucket but
	 * didn't use it, drop the refcount bch_bucket_alloc_set() took:
	 */
	अगर (KEY_PTRS(&alloc.key))
		bkey_put(c, &alloc.key);

	क्रम (i = 0; i < KEY_PTRS(&b->key); i++)
		EBUG_ON(ptr_stale(c, &b->key, i));

	/* Set up the poपूर्णांकer to the space we're allocating: */

	क्रम (i = 0; i < KEY_PTRS(&b->key); i++)
		k->ptr[i] = b->key.ptr[i];

	sectors = min(sectors, b->sectors_मुक्त);

	SET_KEY_OFFSET(k, KEY_OFFSET(k) + sectors);
	SET_KEY_SIZE(k, sectors);
	SET_KEY_PTRS(k, KEY_PTRS(&b->key));

	/*
	 * Move b to the end of the lru, and keep track of what this bucket was
	 * last used क्रम:
	 */
	list_move_tail(&b->list, &c->data_buckets);
	bkey_copy_key(&b->key, k);
	b->last_ग_लिखो_poपूर्णांक = ग_लिखो_poपूर्णांक;

	b->sectors_मुक्त	-= sectors;

	क्रम (i = 0; i < KEY_PTRS(&b->key); i++) अणु
		SET_PTR_OFFSET(&b->key, i, PTR_OFFSET(&b->key, i) + sectors);

		atomic_दीर्घ_add(sectors,
				&c->cache->sectors_written);
	पूर्ण

	अगर (b->sectors_मुक्त < c->cache->sb.block_size)
		b->sectors_मुक्त = 0;

	/*
	 * k takes refcounts on the buckets it poपूर्णांकs to until it's inserted
	 * पूर्णांकo the btree, but अगर we're करोne with this bucket we just transfer
	 * get_data_bucket()'s refcount.
	 */
	अगर (b->sectors_मुक्त)
		क्रम (i = 0; i < KEY_PTRS(&b->key); i++)
			atomic_inc(&PTR_BUCKET(c, &b->key, i)->pin);

	spin_unlock(&c->data_bucket_lock);
	वापस true;
पूर्ण

/* Init */

व्योम bch_खोलो_buckets_मुक्त(काष्ठा cache_set *c)
अणु
	काष्ठा खोलो_bucket *b;

	जबतक (!list_empty(&c->data_buckets)) अणु
		b = list_first_entry(&c->data_buckets,
				     काष्ठा खोलो_bucket, list);
		list_del(&b->list);
		kमुक्त(b);
	पूर्ण
पूर्ण

पूर्णांक bch_खोलो_buckets_alloc(काष्ठा cache_set *c)
अणु
	पूर्णांक i;

	spin_lock_init(&c->data_bucket_lock);

	क्रम (i = 0; i < MAX_OPEN_BUCKETS; i++) अणु
		काष्ठा खोलो_bucket *b = kzalloc(माप(*b), GFP_KERNEL);

		अगर (!b)
			वापस -ENOMEM;

		list_add(&b->list, &c->data_buckets);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bch_cache_allocator_start(काष्ठा cache *ca)
अणु
	काष्ठा task_काष्ठा *k = kthपढ़ो_run(bch_allocator_thपढ़ो,
					    ca, "bcache_allocator");
	अगर (IS_ERR(k))
		वापस PTR_ERR(k);

	ca->alloc_thपढ़ो = k;
	वापस 0;
पूर्ण
