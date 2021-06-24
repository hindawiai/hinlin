<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Main bcache entry poपूर्णांक - handle a पढ़ो or a ग_लिखो request and decide what to
 * करो with it; the make_request functions are called by the block layer.
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "btree.h"
#समावेश "debug.h"
#समावेश "request.h"
#समावेश "writeback.h"

#समावेश <linux/module.h>
#समावेश <linux/hash.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/backing-dev.h>

#समावेश <trace/events/bcache.h>

#घोषणा CUTOFF_CACHE_ADD	95
#घोषणा CUTOFF_CACHE_READA	90

काष्ठा kmem_cache *bch_search_cache;

अटल व्योम bch_data_insert_start(काष्ठा closure *cl);

अटल अचिन्हित पूर्णांक cache_mode(काष्ठा cached_dev *dc)
अणु
	वापस BDEV_CACHE_MODE(&dc->sb);
पूर्ण

अटल bool verअगरy(काष्ठा cached_dev *dc)
अणु
	वापस dc->verअगरy;
पूर्ण

अटल व्योम bio_csum(काष्ठा bio *bio, काष्ठा bkey *k)
अणु
	काष्ठा bio_vec bv;
	काष्ठा bvec_iter iter;
	uपूर्णांक64_t csum = 0;

	bio_क्रम_each_segment(bv, bio, iter) अणु
		व्योम *d = kmap(bv.bv_page) + bv.bv_offset;

		csum = bch_crc64_update(csum, d, bv.bv_len);
		kunmap(bv.bv_page);
	पूर्ण

	k->ptr[KEY_PTRS(k)] = csum & (~0ULL >> 1);
पूर्ण

/* Insert data पूर्णांकo cache */

अटल व्योम bch_data_insert_keys(काष्ठा closure *cl)
अणु
	काष्ठा data_insert_op *op = container_of(cl, काष्ठा data_insert_op, cl);
	atomic_t *journal_ref = शून्य;
	काष्ठा bkey *replace_key = op->replace ? &op->replace_key : शून्य;
	पूर्णांक ret;

	अगर (!op->replace)
		journal_ref = bch_journal(op->c, &op->insert_keys,
					  op->flush_journal ? cl : शून्य);

	ret = bch_btree_insert(op->c, &op->insert_keys,
			       journal_ref, replace_key);
	अगर (ret == -ESRCH) अणु
		op->replace_collision = true;
	पूर्ण अन्यथा अगर (ret) अणु
		op->status		= BLK_STS_RESOURCE;
		op->insert_data_करोne	= true;
	पूर्ण

	अगर (journal_ref)
		atomic_dec_bug(journal_ref);

	अगर (!op->insert_data_करोne) अणु
		जारी_at(cl, bch_data_insert_start, op->wq);
		वापस;
	पूर्ण

	bch_keylist_मुक्त(&op->insert_keys);
	closure_वापस(cl);
पूर्ण

अटल पूर्णांक bch_keylist_पुनः_स्मृति(काष्ठा keylist *l, अचिन्हित पूर्णांक u64s,
			       काष्ठा cache_set *c)
अणु
	माप_प्रकार oldsize = bch_keylist_nkeys(l);
	माप_प्रकार newsize = oldsize + u64s;

	/*
	 * The journalling code करोesn't handle the हाल where the keys to insert
	 * is bigger than an empty ग_लिखो: If we just वापस -ENOMEM here,
	 * bch_data_insert_keys() will insert the keys created so far
	 * and finish the rest when the keylist is empty.
	 */
	अगर (newsize * माप(uपूर्णांक64_t) > block_bytes(c->cache) - माप(काष्ठा jset))
		वापस -ENOMEM;

	वापस __bch_keylist_पुनः_स्मृति(l, u64s);
पूर्ण

अटल व्योम bch_data_invalidate(काष्ठा closure *cl)
अणु
	काष्ठा data_insert_op *op = container_of(cl, काष्ठा data_insert_op, cl);
	काष्ठा bio *bio = op->bio;

	pr_debug("invalidating %i sectors from %llu\n",
		 bio_sectors(bio), (uपूर्णांक64_t) bio->bi_iter.bi_sector);

	जबतक (bio_sectors(bio)) अणु
		अचिन्हित पूर्णांक sectors = min(bio_sectors(bio),
				       1U << (KEY_SIZE_BITS - 1));

		अगर (bch_keylist_पुनः_स्मृति(&op->insert_keys, 2, op->c))
			जाओ out;

		bio->bi_iter.bi_sector	+= sectors;
		bio->bi_iter.bi_size	-= sectors << 9;

		bch_keylist_add(&op->insert_keys,
				&KEY(op->inode,
				     bio->bi_iter.bi_sector,
				     sectors));
	पूर्ण

	op->insert_data_करोne = true;
	/* get in bch_data_insert() */
	bio_put(bio);
out:
	जारी_at(cl, bch_data_insert_keys, op->wq);
पूर्ण

अटल व्योम bch_data_insert_error(काष्ठा closure *cl)
अणु
	काष्ठा data_insert_op *op = container_of(cl, काष्ठा data_insert_op, cl);

	/*
	 * Our data ग_लिखो just errored, which means we've got a bunch of keys to
	 * insert that poपूर्णांक to data that wasn't successfully written.
	 *
	 * We करोn't have to insert those keys but we still have to invalidate
	 * that region of the cache - so, अगर we just strip off all the poपूर्णांकers
	 * from the keys we'll accomplish just that.
	 */

	काष्ठा bkey *src = op->insert_keys.keys, *dst = op->insert_keys.keys;

	जबतक (src != op->insert_keys.top) अणु
		काष्ठा bkey *n = bkey_next(src);

		SET_KEY_PTRS(src, 0);
		स_हटाओ(dst, src, bkey_bytes(src));

		dst = bkey_next(dst);
		src = n;
	पूर्ण

	op->insert_keys.top = dst;

	bch_data_insert_keys(cl);
पूर्ण

अटल व्योम bch_data_insert_endio(काष्ठा bio *bio)
अणु
	काष्ठा closure *cl = bio->bi_निजी;
	काष्ठा data_insert_op *op = container_of(cl, काष्ठा data_insert_op, cl);

	अगर (bio->bi_status) अणु
		/* TODO: We could try to recover from this. */
		अगर (op->ग_लिखोback)
			op->status = bio->bi_status;
		अन्यथा अगर (!op->replace)
			set_closure_fn(cl, bch_data_insert_error, op->wq);
		अन्यथा
			set_closure_fn(cl, शून्य, शून्य);
	पूर्ण

	bch_bbio_endio(op->c, bio, bio->bi_status, "writing data to cache");
पूर्ण

अटल व्योम bch_data_insert_start(काष्ठा closure *cl)
अणु
	काष्ठा data_insert_op *op = container_of(cl, काष्ठा data_insert_op, cl);
	काष्ठा bio *bio = op->bio, *n;

	अगर (op->bypass)
		वापस bch_data_invalidate(cl);

	अगर (atomic_sub_वापस(bio_sectors(bio), &op->c->sectors_to_gc) < 0)
		wake_up_gc(op->c);

	/*
	 * Journal ग_लिखोs are marked REQ_PREFLUSH; अगर the original ग_लिखो was a
	 * flush, it'll रुको on the journal ग_लिखो.
	 */
	bio->bi_opf &= ~(REQ_PREFLUSH|REQ_FUA);

	करो अणु
		अचिन्हित पूर्णांक i;
		काष्ठा bkey *k;
		काष्ठा bio_set *split = &op->c->bio_split;

		/* 1 क्रम the device poपूर्णांकer and 1 क्रम the chksum */
		अगर (bch_keylist_पुनः_स्मृति(&op->insert_keys,
					3 + (op->csum ? 1 : 0),
					op->c)) अणु
			जारी_at(cl, bch_data_insert_keys, op->wq);
			वापस;
		पूर्ण

		k = op->insert_keys.top;
		bkey_init(k);
		SET_KEY_INODE(k, op->inode);
		SET_KEY_OFFSET(k, bio->bi_iter.bi_sector);

		अगर (!bch_alloc_sectors(op->c, k, bio_sectors(bio),
				       op->ग_लिखो_poपूर्णांक, op->ग_लिखो_prio,
				       op->ग_लिखोback))
			जाओ err;

		n = bio_next_split(bio, KEY_SIZE(k), GFP_NOIO, split);

		n->bi_end_io	= bch_data_insert_endio;
		n->bi_निजी	= cl;

		अगर (op->ग_लिखोback) अणु
			SET_KEY_सूचीTY(k, true);

			क्रम (i = 0; i < KEY_PTRS(k); i++)
				SET_GC_MARK(PTR_BUCKET(op->c, k, i),
					    GC_MARK_सूचीTY);
		पूर्ण

		SET_KEY_CSUM(k, op->csum);
		अगर (KEY_CSUM(k))
			bio_csum(n, k);

		trace_bcache_cache_insert(k);
		bch_keylist_push(&op->insert_keys);

		bio_set_op_attrs(n, REQ_OP_WRITE, 0);
		bch_submit_bbio(n, op->c, k, 0);
	पूर्ण जबतक (n != bio);

	op->insert_data_करोne = true;
	जारी_at(cl, bch_data_insert_keys, op->wq);
	वापस;
err:
	/* bch_alloc_sectors() blocks अगर s->ग_लिखोback = true */
	BUG_ON(op->ग_लिखोback);

	/*
	 * But अगर it's not a writeback write we'd rather just bail out अगर
	 * there aren't any buckets पढ़ोy to ग_लिखो to - it might take aजबतक and
	 * we might be starving btree ग_लिखोs क्रम gc or something.
	 */

	अगर (!op->replace) अणु
		/*
		 * Writethrough ग_लिखो: We can't complete the write until we've
		 * updated the index. But we करोn't want to delay the ग_लिखो जबतक
		 * we रुको क्रम buckets to be मुक्तd up, so just invalidate the
		 * rest of the ग_लिखो.
		 */
		op->bypass = true;
		वापस bch_data_invalidate(cl);
	पूर्ण अन्यथा अणु
		/*
		 * From a cache miss, we can just insert the keys क्रम the data
		 * we have written or bail out अगर we didn't करो anything.
		 */
		op->insert_data_करोne = true;
		bio_put(bio);

		अगर (!bch_keylist_empty(&op->insert_keys))
			जारी_at(cl, bch_data_insert_keys, op->wq);
		अन्यथा
			closure_वापस(cl);
	पूर्ण
पूर्ण

/**
 * bch_data_insert - stick some data in the cache
 * @cl: closure poपूर्णांकer.
 *
 * This is the starting poपूर्णांक क्रम any data to end up in a cache device; it could
 * be from a normal ग_लिखो, or a ग_लिखोback ग_लिखो, or a ग_लिखो to a flash only
 * volume - it's also used by the moving garbage collector to compact data in
 * mostly empty buckets.
 *
 * It first ग_लिखोs the data to the cache, creating a list of keys to be inserted
 * (अगर the data had to be fragmented there will be multiple keys); after the
 * data is written it calls bch_journal, and after the keys have been added to
 * the next journal ग_लिखो they're inserted पूर्णांकo the btree.
 *
 * It inserts the data in op->bio; bi_sector is used क्रम the key offset,
 * and op->inode is used क्रम the key inode.
 *
 * If op->bypass is true, instead of inserting the data it invalidates the
 * region of the cache represented by op->bio and op->inode.
 */
व्योम bch_data_insert(काष्ठा closure *cl)
अणु
	काष्ठा data_insert_op *op = container_of(cl, काष्ठा data_insert_op, cl);

	trace_bcache_ग_लिखो(op->c, op->inode, op->bio,
			   op->ग_लिखोback, op->bypass);

	bch_keylist_init(&op->insert_keys);
	bio_get(op->bio);
	bch_data_insert_start(cl);
पूर्ण

/*
 * Congested?  Return 0 (not congested) or the limit (in sectors)
 * beyond which we should bypass the cache due to congestion.
 */
अचिन्हित पूर्णांक bch_get_congested(स्थिर काष्ठा cache_set *c)
अणु
	पूर्णांक i;

	अगर (!c->congested_पढ़ो_threshold_us &&
	    !c->congested_ग_लिखो_threshold_us)
		वापस 0;

	i = (local_घड़ी_us() - c->congested_last_us) / 1024;
	अगर (i < 0)
		वापस 0;

	i += atomic_पढ़ो(&c->congested);
	अगर (i >= 0)
		वापस 0;

	i += CONGESTED_MAX;

	अगर (i > 0)
		i = fract_exp_two(i, 6);

	i -= hweight32(get_अक्रमom_u32());

	वापस i > 0 ? i : 1;
पूर्ण

अटल व्योम add_sequential(काष्ठा task_काष्ठा *t)
अणु
	ewma_add(t->sequential_io_avg,
		 t->sequential_io, 8, 0);

	t->sequential_io = 0;
पूर्ण

अटल काष्ठा hlist_head *iohash(काष्ठा cached_dev *dc, uपूर्णांक64_t k)
अणु
	वापस &dc->io_hash[hash_64(k, RECENT_IO_BITS)];
पूर्ण

अटल bool check_should_bypass(काष्ठा cached_dev *dc, काष्ठा bio *bio)
अणु
	काष्ठा cache_set *c = dc->disk.c;
	अचिन्हित पूर्णांक mode = cache_mode(dc);
	अचिन्हित पूर्णांक sectors, congested;
	काष्ठा task_काष्ठा *task = current;
	काष्ठा io *i;

	अगर (test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags) ||
	    c->gc_stats.in_use > CUTOFF_CACHE_ADD ||
	    (bio_op(bio) == REQ_OP_DISCARD))
		जाओ skip;

	अगर (mode == CACHE_MODE_NONE ||
	    (mode == CACHE_MODE_WRITEAROUND &&
	     op_is_ग_लिखो(bio_op(bio))))
		जाओ skip;

	/*
	 * If the bio is क्रम पढ़ो-ahead or background IO, bypass it or
	 * not depends on the following situations,
	 * - If the IO is क्रम meta data, always cache it and no bypass
	 * - If the IO is not meta data, check dc->cache_पढ़ोa_policy,
	 *      BCH_CACHE_READA_ALL: cache it and not bypass
	 *      BCH_CACHE_READA_META_ONLY: not cache it and bypass
	 * That is, पढ़ो-ahead request क्रम metadata always get cached
	 * (eg, क्रम gfs2 or xfs).
	 */
	अगर ((bio->bi_opf & (REQ_RAHEAD|REQ_BACKGROUND))) अणु
		अगर (!(bio->bi_opf & (REQ_META|REQ_PRIO)) &&
		    (dc->cache_पढ़ोahead_policy != BCH_CACHE_READA_ALL))
			जाओ skip;
	पूर्ण

	अगर (bio->bi_iter.bi_sector & (c->cache->sb.block_size - 1) ||
	    bio_sectors(bio) & (c->cache->sb.block_size - 1)) अणु
		pr_debug("skipping unaligned io\n");
		जाओ skip;
	पूर्ण

	अगर (bypass_torture_test(dc)) अणु
		अगर ((get_अक्रमom_पूर्णांक() & 3) == 3)
			जाओ skip;
		अन्यथा
			जाओ rescale;
	पूर्ण

	congested = bch_get_congested(c);
	अगर (!congested && !dc->sequential_cutoff)
		जाओ rescale;

	spin_lock(&dc->io_lock);

	hlist_क्रम_each_entry(i, iohash(dc, bio->bi_iter.bi_sector), hash)
		अगर (i->last == bio->bi_iter.bi_sector &&
		    समय_beक्रमe(jअगरfies, i->jअगरfies))
			जाओ found;

	i = list_first_entry(&dc->io_lru, काष्ठा io, lru);

	add_sequential(task);
	i->sequential = 0;
found:
	अगर (i->sequential + bio->bi_iter.bi_size > i->sequential)
		i->sequential	+= bio->bi_iter.bi_size;

	i->last			 = bio_end_sector(bio);
	i->jअगरfies		 = jअगरfies + msecs_to_jअगरfies(5000);
	task->sequential_io	 = i->sequential;

	hlist_del(&i->hash);
	hlist_add_head(&i->hash, iohash(dc, i->last));
	list_move_tail(&i->lru, &dc->io_lru);

	spin_unlock(&dc->io_lock);

	sectors = max(task->sequential_io,
		      task->sequential_io_avg) >> 9;

	अगर (dc->sequential_cutoff &&
	    sectors >= dc->sequential_cutoff >> 9) अणु
		trace_bcache_bypass_sequential(bio);
		जाओ skip;
	पूर्ण

	अगर (congested && sectors >= congested) अणु
		trace_bcache_bypass_congested(bio);
		जाओ skip;
	पूर्ण

rescale:
	bch_rescale_priorities(c, bio_sectors(bio));
	वापस false;
skip:
	bch_mark_sectors_bypassed(c, dc, bio_sectors(bio));
	वापस true;
पूर्ण

/* Cache lookup */

काष्ठा search अणु
	/* Stack frame क्रम bio_complete */
	काष्ठा closure		cl;

	काष्ठा bbio		bio;
	काष्ठा bio		*orig_bio;
	काष्ठा bio		*cache_miss;
	काष्ठा bcache_device	*d;

	अचिन्हित पूर्णांक		insert_bio_sectors;
	अचिन्हित पूर्णांक		recoverable:1;
	अचिन्हित पूर्णांक		ग_लिखो:1;
	अचिन्हित पूर्णांक		पढ़ो_dirty_data:1;
	अचिन्हित पूर्णांक		cache_missed:1;

	काष्ठा block_device	*orig_bdev;
	अचिन्हित दीर्घ		start_समय;

	काष्ठा btree_op		op;
	काष्ठा data_insert_op	iop;
पूर्ण;

अटल व्योम bch_cache_पढ़ो_endio(काष्ठा bio *bio)
अणु
	काष्ठा bbio *b = container_of(bio, काष्ठा bbio, bio);
	काष्ठा closure *cl = bio->bi_निजी;
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);

	/*
	 * If the bucket was reused जबतक our bio was in flight, we might have
	 * पढ़ो the wrong data. Set s->error but not error so it करोesn't get
	 * counted against the cache device, but we'll still reपढ़ो the data
	 * from the backing device.
	 */

	अगर (bio->bi_status)
		s->iop.status = bio->bi_status;
	अन्यथा अगर (!KEY_सूचीTY(&b->key) &&
		 ptr_stale(s->iop.c, &b->key, 0)) अणु
		atomic_दीर्घ_inc(&s->iop.c->cache_पढ़ो_races);
		s->iop.status = BLK_STS_IOERR;
	पूर्ण

	bch_bbio_endio(s->iop.c, bio, bio->bi_status, "reading from cache");
पूर्ण

/*
 * Read from a single key, handling the initial cache miss अगर the key starts in
 * the middle of the bio
 */
अटल पूर्णांक cache_lookup_fn(काष्ठा btree_op *op, काष्ठा btree *b, काष्ठा bkey *k)
अणु
	काष्ठा search *s = container_of(op, काष्ठा search, op);
	काष्ठा bio *n, *bio = &s->bio.bio;
	काष्ठा bkey *bio_key;
	अचिन्हित पूर्णांक ptr;

	अगर (bkey_cmp(k, &KEY(s->iop.inode, bio->bi_iter.bi_sector, 0)) <= 0)
		वापस MAP_CONTINUE;

	अगर (KEY_INODE(k) != s->iop.inode ||
	    KEY_START(k) > bio->bi_iter.bi_sector) अणु
		अचिन्हित पूर्णांक bio_sectors = bio_sectors(bio);
		अचिन्हित पूर्णांक sectors = KEY_INODE(k) == s->iop.inode
			? min_t(uपूर्णांक64_t, पूर्णांक_उच्च,
				KEY_START(k) - bio->bi_iter.bi_sector)
			: पूर्णांक_उच्च;
		पूर्णांक ret = s->d->cache_miss(b, s, bio, sectors);

		अगर (ret != MAP_CONTINUE)
			वापस ret;

		/* अगर this was a complete miss we shouldn't get here */
		BUG_ON(bio_sectors <= sectors);
	पूर्ण

	अगर (!KEY_SIZE(k))
		वापस MAP_CONTINUE;

	/* XXX: figure out best poपूर्णांकer - क्रम multiple cache devices */
	ptr = 0;

	PTR_BUCKET(b->c, k, ptr)->prio = INITIAL_PRIO;

	अगर (KEY_सूचीTY(k))
		s->पढ़ो_dirty_data = true;

	n = bio_next_split(bio, min_t(uपूर्णांक64_t, पूर्णांक_उच्च,
				      KEY_OFFSET(k) - bio->bi_iter.bi_sector),
			   GFP_NOIO, &s->d->bio_split);

	bio_key = &container_of(n, काष्ठा bbio, bio)->key;
	bch_bkey_copy_single_ptr(bio_key, k, ptr);

	bch_cut_front(&KEY(s->iop.inode, n->bi_iter.bi_sector, 0), bio_key);
	bch_cut_back(&KEY(s->iop.inode, bio_end_sector(n), 0), bio_key);

	n->bi_end_io	= bch_cache_पढ़ो_endio;
	n->bi_निजी	= &s->cl;

	/*
	 * The bucket we're पढ़ोing from might be reused जबतक our bio
	 * is in flight, and we could then end up पढ़ोing the wrong
	 * data.
	 *
	 * We guard against this by checking (in cache_पढ़ो_endio()) अगर
	 * the poपूर्णांकer is stale again; अगर so, we treat it as an error
	 * and reपढ़ो from the backing device (but we करोn't pass that
	 * error up anywhere).
	 */

	__bch_submit_bbio(n, b->c);
	वापस n == bio ? MAP_DONE : MAP_CONTINUE;
पूर्ण

अटल व्योम cache_lookup(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, iop.cl);
	काष्ठा bio *bio = &s->bio.bio;
	काष्ठा cached_dev *dc;
	पूर्णांक ret;

	bch_btree_op_init(&s->op, -1);

	ret = bch_btree_map_keys(&s->op, s->iop.c,
				 &KEY(s->iop.inode, bio->bi_iter.bi_sector, 0),
				 cache_lookup_fn, MAP_END_KEY);
	अगर (ret == -EAGAIN) अणु
		जारी_at(cl, cache_lookup, bcache_wq);
		वापस;
	पूर्ण

	/*
	 * We might meet err when searching the btree, If that happens, we will
	 * get negative ret, in this scenario we should not recover data from
	 * backing device (when cache device is dirty) because we करोn't know
	 * whether bkeys the पढ़ो request covered are all clean.
	 *
	 * And after that happened, s->iop.status is still its initial value
	 * beक्रमe we submit s->bio.bio
	 */
	अगर (ret < 0) अणु
		BUG_ON(ret == -EINTR);
		अगर (s->d && s->d->c &&
				!UUID_FLASH_ONLY(&s->d->c->uuids[s->d->id])) अणु
			dc = container_of(s->d, काष्ठा cached_dev, disk);
			अगर (dc && atomic_पढ़ो(&dc->has_dirty))
				s->recoverable = false;
		पूर्ण
		अगर (!s->iop.status)
			s->iop.status = BLK_STS_IOERR;
	पूर्ण

	closure_वापस(cl);
पूर्ण

/* Common code क्रम the make_request functions */

अटल व्योम request_endio(काष्ठा bio *bio)
अणु
	काष्ठा closure *cl = bio->bi_निजी;

	अगर (bio->bi_status) अणु
		काष्ठा search *s = container_of(cl, काष्ठा search, cl);

		s->iop.status = bio->bi_status;
		/* Only cache पढ़ो errors are recoverable */
		s->recoverable = false;
	पूर्ण

	bio_put(bio);
	closure_put(cl);
पूर्ण

अटल व्योम backing_request_endio(काष्ठा bio *bio)
अणु
	काष्ठा closure *cl = bio->bi_निजी;

	अगर (bio->bi_status) अणु
		काष्ठा search *s = container_of(cl, काष्ठा search, cl);
		काष्ठा cached_dev *dc = container_of(s->d,
						     काष्ठा cached_dev, disk);
		/*
		 * If a bio has REQ_PREFLUSH क्रम ग_लिखोback mode, it is
		 * speically assembled in cached_dev_ग_लिखो() क्रम a non-zero
		 * ग_लिखो request which has REQ_PREFLUSH. we करोn't set
		 * s->iop.status by this failure, the status will be decided
		 * by result of bch_data_insert() operation.
		 */
		अगर (unlikely(s->iop.ग_लिखोback &&
			     bio->bi_opf & REQ_PREFLUSH)) अणु
			pr_err("Can't flush %s: returned bi_status %i\n",
				dc->backing_dev_name, bio->bi_status);
		पूर्ण अन्यथा अणु
			/* set to orig_bio->bi_status in bio_complete() */
			s->iop.status = bio->bi_status;
		पूर्ण
		s->recoverable = false;
		/* should count I/O error क्रम backing device here */
		bch_count_backing_io_errors(dc, bio);
	पूर्ण

	bio_put(bio);
	closure_put(cl);
पूर्ण

अटल व्योम bio_complete(काष्ठा search *s)
अणु
	अगर (s->orig_bio) अणु
		/* Count on bcache device */
		bio_end_io_acct_remapped(s->orig_bio, s->start_समय,
					 s->orig_bdev);
		trace_bcache_request_end(s->d, s->orig_bio);
		s->orig_bio->bi_status = s->iop.status;
		bio_endio(s->orig_bio);
		s->orig_bio = शून्य;
	पूर्ण
पूर्ण

अटल व्योम करो_bio_hook(काष्ठा search *s,
			काष्ठा bio *orig_bio,
			bio_end_io_t *end_io_fn)
अणु
	काष्ठा bio *bio = &s->bio.bio;

	bio_init(bio, शून्य, 0);
	__bio_clone_fast(bio, orig_bio);
	/*
	 * bi_end_io can be set separately somewhere अन्यथा, e.g. the
	 * variants in,
	 * - cache_bio->bi_end_io from cached_dev_cache_miss()
	 * - n->bi_end_io from cache_lookup_fn()
	 */
	bio->bi_end_io		= end_io_fn;
	bio->bi_निजी		= &s->cl;

	bio_cnt_set(bio, 3);
पूर्ण

अटल व्योम search_मुक्त(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);

	atomic_dec(&s->iop.c->search_inflight);

	अगर (s->iop.bio)
		bio_put(s->iop.bio);

	bio_complete(s);
	closure_debug_destroy(cl);
	mempool_मुक्त(s, &s->iop.c->search);
पूर्ण

अटल अंतरभूत काष्ठा search *search_alloc(काष्ठा bio *bio,
		काष्ठा bcache_device *d, काष्ठा block_device *orig_bdev,
		अचिन्हित दीर्घ start_समय)
अणु
	काष्ठा search *s;

	s = mempool_alloc(&d->c->search, GFP_NOIO);

	closure_init(&s->cl, शून्य);
	करो_bio_hook(s, bio, request_endio);
	atomic_inc(&d->c->search_inflight);

	s->orig_bio		= bio;
	s->cache_miss		= शून्य;
	s->cache_missed		= 0;
	s->d			= d;
	s->recoverable		= 1;
	s->ग_लिखो		= op_is_ग_लिखो(bio_op(bio));
	s->पढ़ो_dirty_data	= 0;
	/* Count on the bcache device */
	s->orig_bdev		= orig_bdev;
	s->start_समय		= start_समय;
	s->iop.c		= d->c;
	s->iop.bio		= शून्य;
	s->iop.inode		= d->id;
	s->iop.ग_लिखो_poपूर्णांक	= hash_दीर्घ((अचिन्हित दीर्घ) current, 16);
	s->iop.ग_लिखो_prio	= 0;
	s->iop.status		= 0;
	s->iop.flags		= 0;
	s->iop.flush_journal	= op_is_flush(bio->bi_opf);
	s->iop.wq		= bcache_wq;

	वापस s;
पूर्ण

/* Cached devices */

अटल व्योम cached_dev_bio_complete(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);
	काष्ठा cached_dev *dc = container_of(s->d, काष्ठा cached_dev, disk);

	cached_dev_put(dc);
	search_मुक्त(cl);
पूर्ण

/* Process पढ़ोs */

अटल व्योम cached_dev_पढ़ो_error_करोne(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);

	अगर (s->iop.replace_collision)
		bch_mark_cache_miss_collision(s->iop.c, s->d);

	अगर (s->iop.bio)
		bio_मुक्त_pages(s->iop.bio);

	cached_dev_bio_complete(cl);
पूर्ण

अटल व्योम cached_dev_पढ़ो_error(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);
	काष्ठा bio *bio = &s->bio.bio;

	/*
	 * If पढ़ो request hit dirty data (s->पढ़ो_dirty_data is true),
	 * then recovery a failed पढ़ो request from cached device may
	 * get a stale data back. So पढ़ो failure recovery is only
	 * permitted when पढ़ो request hit clean data in cache device,
	 * or when cache पढ़ो race happened.
	 */
	अगर (s->recoverable && !s->पढ़ो_dirty_data) अणु
		/* Retry from the backing device: */
		trace_bcache_पढ़ो_retry(s->orig_bio);

		s->iop.status = 0;
		करो_bio_hook(s, s->orig_bio, backing_request_endio);

		/* XXX: invalidate cache */

		/* I/O request sent to backing device */
		closure_bio_submit(s->iop.c, bio, cl);
	पूर्ण

	जारी_at(cl, cached_dev_पढ़ो_error_करोne, शून्य);
पूर्ण

अटल व्योम cached_dev_cache_miss_करोne(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);
	काष्ठा bcache_device *d = s->d;

	अगर (s->iop.replace_collision)
		bch_mark_cache_miss_collision(s->iop.c, s->d);

	अगर (s->iop.bio)
		bio_मुक्त_pages(s->iop.bio);

	cached_dev_bio_complete(cl);
	closure_put(&d->cl);
पूर्ण

अटल व्योम cached_dev_पढ़ो_करोne(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);
	काष्ठा cached_dev *dc = container_of(s->d, काष्ठा cached_dev, disk);

	/*
	 * We had a cache miss; cache_bio now contains data पढ़ोy to be inserted
	 * पूर्णांकo the cache.
	 *
	 * First, we copy the data we just पढ़ो from cache_bio's bounce buffers
	 * to the buffers the original bio poपूर्णांकed to:
	 */

	अगर (s->iop.bio) अणु
		bio_reset(s->iop.bio);
		s->iop.bio->bi_iter.bi_sector =
			s->cache_miss->bi_iter.bi_sector;
		bio_copy_dev(s->iop.bio, s->cache_miss);
		s->iop.bio->bi_iter.bi_size = s->insert_bio_sectors << 9;
		bch_bio_map(s->iop.bio, शून्य);

		bio_copy_data(s->cache_miss, s->iop.bio);

		bio_put(s->cache_miss);
		s->cache_miss = शून्य;
	पूर्ण

	अगर (verअगरy(dc) && s->recoverable && !s->पढ़ो_dirty_data)
		bch_data_verअगरy(dc, s->orig_bio);

	closure_get(&dc->disk.cl);
	bio_complete(s);

	अगर (s->iop.bio &&
	    !test_bit(CACHE_SET_STOPPING, &s->iop.c->flags)) अणु
		BUG_ON(!s->iop.replace);
		closure_call(&s->iop.cl, bch_data_insert, शून्य, cl);
	पूर्ण

	जारी_at(cl, cached_dev_cache_miss_करोne, शून्य);
पूर्ण

अटल व्योम cached_dev_पढ़ो_करोne_bh(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);
	काष्ठा cached_dev *dc = container_of(s->d, काष्ठा cached_dev, disk);

	bch_mark_cache_accounting(s->iop.c, s->d,
				  !s->cache_missed, s->iop.bypass);
	trace_bcache_पढ़ो(s->orig_bio, !s->cache_missed, s->iop.bypass);

	अगर (s->iop.status)
		जारी_at_nobarrier(cl, cached_dev_पढ़ो_error, bcache_wq);
	अन्यथा अगर (s->iop.bio || verअगरy(dc))
		जारी_at_nobarrier(cl, cached_dev_पढ़ो_करोne, bcache_wq);
	अन्यथा
		जारी_at_nobarrier(cl, cached_dev_bio_complete, शून्य);
पूर्ण

अटल पूर्णांक cached_dev_cache_miss(काष्ठा btree *b, काष्ठा search *s,
				 काष्ठा bio *bio, अचिन्हित पूर्णांक sectors)
अणु
	पूर्णांक ret = MAP_CONTINUE;
	काष्ठा cached_dev *dc = container_of(s->d, काष्ठा cached_dev, disk);
	काष्ठा bio *miss, *cache_bio;
	अचिन्हित पूर्णांक size_limit;

	s->cache_missed = 1;

	अगर (s->cache_miss || s->iop.bypass) अणु
		miss = bio_next_split(bio, sectors, GFP_NOIO, &s->d->bio_split);
		ret = miss == bio ? MAP_DONE : MAP_CONTINUE;
		जाओ out_submit;
	पूर्ण

	/* Limitation क्रम valid replace key size and cache_bio bvecs number */
	size_limit = min_t(अचिन्हित पूर्णांक, BIO_MAX_VECS * PAGE_SECTORS,
			   (1 << KEY_SIZE_BITS) - 1);
	s->insert_bio_sectors = min3(size_limit, sectors, bio_sectors(bio));

	s->iop.replace_key = KEY(s->iop.inode,
				 bio->bi_iter.bi_sector + s->insert_bio_sectors,
				 s->insert_bio_sectors);

	ret = bch_btree_insert_check_key(b, &s->op, &s->iop.replace_key);
	अगर (ret)
		वापस ret;

	s->iop.replace = true;

	miss = bio_next_split(bio, s->insert_bio_sectors, GFP_NOIO,
			      &s->d->bio_split);

	/* btree_search_recurse()'s btree iterator is no good anymore */
	ret = miss == bio ? MAP_DONE : -EINTR;

	cache_bio = bio_alloc_bioset(GFP_NOWAIT,
			DIV_ROUND_UP(s->insert_bio_sectors, PAGE_SECTORS),
			&dc->disk.bio_split);
	अगर (!cache_bio)
		जाओ out_submit;

	cache_bio->bi_iter.bi_sector	= miss->bi_iter.bi_sector;
	bio_copy_dev(cache_bio, miss);
	cache_bio->bi_iter.bi_size	= s->insert_bio_sectors << 9;

	cache_bio->bi_end_io	= backing_request_endio;
	cache_bio->bi_निजी	= &s->cl;

	bch_bio_map(cache_bio, शून्य);
	अगर (bch_bio_alloc_pages(cache_bio, __GFP_NOWARN|GFP_NOIO))
		जाओ out_put;

	s->cache_miss	= miss;
	s->iop.bio	= cache_bio;
	bio_get(cache_bio);
	/* I/O request sent to backing device */
	closure_bio_submit(s->iop.c, cache_bio, &s->cl);

	वापस ret;
out_put:
	bio_put(cache_bio);
out_submit:
	miss->bi_end_io		= backing_request_endio;
	miss->bi_निजी	= &s->cl;
	/* I/O request sent to backing device */
	closure_bio_submit(s->iop.c, miss, &s->cl);
	वापस ret;
पूर्ण

अटल व्योम cached_dev_पढ़ो(काष्ठा cached_dev *dc, काष्ठा search *s)
अणु
	काष्ठा closure *cl = &s->cl;

	closure_call(&s->iop.cl, cache_lookup, शून्य, cl);
	जारी_at(cl, cached_dev_पढ़ो_करोne_bh, शून्य);
पूर्ण

/* Process ग_लिखोs */

अटल व्योम cached_dev_ग_लिखो_complete(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);
	काष्ठा cached_dev *dc = container_of(s->d, काष्ठा cached_dev, disk);

	up_पढ़ो_non_owner(&dc->ग_लिखोback_lock);
	cached_dev_bio_complete(cl);
पूर्ण

अटल व्योम cached_dev_ग_लिखो(काष्ठा cached_dev *dc, काष्ठा search *s)
अणु
	काष्ठा closure *cl = &s->cl;
	काष्ठा bio *bio = &s->bio.bio;
	काष्ठा bkey start = KEY(dc->disk.id, bio->bi_iter.bi_sector, 0);
	काष्ठा bkey end = KEY(dc->disk.id, bio_end_sector(bio), 0);

	bch_keybuf_check_overlapping(&s->iop.c->moving_gc_keys, &start, &end);

	करोwn_पढ़ो_non_owner(&dc->ग_लिखोback_lock);
	अगर (bch_keybuf_check_overlapping(&dc->ग_लिखोback_keys, &start, &end)) अणु
		/*
		 * We overlap with some dirty data undergoing background
		 * ग_लिखोback, क्रमce this ग_लिखो to ग_लिखोback
		 */
		s->iop.bypass = false;
		s->iop.ग_लिखोback = true;
	पूर्ण

	/*
	 * Discards aren't _required_ to करो anything, so skipping अगर
	 * check_overlapping वापसed true is ok
	 *
	 * But check_overlapping drops dirty keys क्रम which io hasn't started,
	 * so we still want to call it.
	 */
	अगर (bio_op(bio) == REQ_OP_DISCARD)
		s->iop.bypass = true;

	अगर (should_ग_लिखोback(dc, s->orig_bio,
			     cache_mode(dc),
			     s->iop.bypass)) अणु
		s->iop.bypass = false;
		s->iop.ग_लिखोback = true;
	पूर्ण

	अगर (s->iop.bypass) अणु
		s->iop.bio = s->orig_bio;
		bio_get(s->iop.bio);

		अगर (bio_op(bio) == REQ_OP_DISCARD &&
		    !blk_queue_discard(bdev_get_queue(dc->bdev)))
			जाओ insert_data;

		/* I/O request sent to backing device */
		bio->bi_end_io = backing_request_endio;
		closure_bio_submit(s->iop.c, bio, cl);

	पूर्ण अन्यथा अगर (s->iop.ग_लिखोback) अणु
		bch_ग_लिखोback_add(dc);
		s->iop.bio = bio;

		अगर (bio->bi_opf & REQ_PREFLUSH) अणु
			/*
			 * Also need to send a flush to the backing
			 * device.
			 */
			काष्ठा bio *flush;

			flush = bio_alloc_bioset(GFP_NOIO, 0,
						 &dc->disk.bio_split);
			अगर (!flush) अणु
				s->iop.status = BLK_STS_RESOURCE;
				जाओ insert_data;
			पूर्ण
			bio_copy_dev(flush, bio);
			flush->bi_end_io = backing_request_endio;
			flush->bi_निजी = cl;
			flush->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
			/* I/O request sent to backing device */
			closure_bio_submit(s->iop.c, flush, cl);
		पूर्ण
	पूर्ण अन्यथा अणु
		s->iop.bio = bio_clone_fast(bio, GFP_NOIO, &dc->disk.bio_split);
		/* I/O request sent to backing device */
		bio->bi_end_io = backing_request_endio;
		closure_bio_submit(s->iop.c, bio, cl);
	पूर्ण

insert_data:
	closure_call(&s->iop.cl, bch_data_insert, शून्य, cl);
	जारी_at(cl, cached_dev_ग_लिखो_complete, शून्य);
पूर्ण

अटल व्योम cached_dev_nodata(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);
	काष्ठा bio *bio = &s->bio.bio;

	अगर (s->iop.flush_journal)
		bch_journal_meta(s->iop.c, cl);

	/* If it's a flush, we send the flush to the backing device too */
	bio->bi_end_io = backing_request_endio;
	closure_bio_submit(s->iop.c, bio, cl);

	जारी_at(cl, cached_dev_bio_complete, शून्य);
पूर्ण

काष्ठा detached_dev_io_निजी अणु
	काष्ठा bcache_device	*d;
	अचिन्हित दीर्घ		start_समय;
	bio_end_io_t		*bi_end_io;
	व्योम			*bi_निजी;
	काष्ठा block_device	*orig_bdev;
पूर्ण;

अटल व्योम detached_dev_end_io(काष्ठा bio *bio)
अणु
	काष्ठा detached_dev_io_निजी *ddip;

	ddip = bio->bi_निजी;
	bio->bi_end_io = ddip->bi_end_io;
	bio->bi_निजी = ddip->bi_निजी;

	/* Count on the bcache device */
	bio_end_io_acct_remapped(bio, ddip->start_समय, ddip->orig_bdev);

	अगर (bio->bi_status) अणु
		काष्ठा cached_dev *dc = container_of(ddip->d,
						     काष्ठा cached_dev, disk);
		/* should count I/O error क्रम backing device here */
		bch_count_backing_io_errors(dc, bio);
	पूर्ण

	kमुक्त(ddip);
	bio->bi_end_io(bio);
पूर्ण

अटल व्योम detached_dev_करो_request(काष्ठा bcache_device *d, काष्ठा bio *bio,
		काष्ठा block_device *orig_bdev, अचिन्हित दीर्घ start_समय)
अणु
	काष्ठा detached_dev_io_निजी *ddip;
	काष्ठा cached_dev *dc = container_of(d, काष्ठा cached_dev, disk);

	/*
	 * no need to call closure_get(&dc->disk.cl),
	 * because upper layer had alपढ़ोy खोलोed bcache device,
	 * which would call closure_get(&dc->disk.cl)
	 */
	ddip = kzalloc(माप(काष्ठा detached_dev_io_निजी), GFP_NOIO);
	ddip->d = d;
	/* Count on the bcache device */
	ddip->orig_bdev = orig_bdev;
	ddip->start_समय = start_समय;
	ddip->bi_end_io = bio->bi_end_io;
	ddip->bi_निजी = bio->bi_निजी;
	bio->bi_end_io = detached_dev_end_io;
	bio->bi_निजी = ddip;

	अगर ((bio_op(bio) == REQ_OP_DISCARD) &&
	    !blk_queue_discard(bdev_get_queue(dc->bdev)))
		bio->bi_end_io(bio);
	अन्यथा
		submit_bio_noacct(bio);
पूर्ण

अटल व्योम quit_max_ग_लिखोback_rate(काष्ठा cache_set *c,
				    काष्ठा cached_dev *this_dc)
अणु
	पूर्णांक i;
	काष्ठा bcache_device *d;
	काष्ठा cached_dev *dc;

	/*
	 * mutex bch_रेजिस्टर_lock may compete with other parallel requesters,
	 * or attach/detach operations on other backing device. Waiting to
	 * the mutex lock may increase I/O request latency क्रम seconds or more.
	 * To aव्योम such situation, अगर mutext_trylock() failed, only ग_लिखोback
	 * rate of current cached device is set to 1, and __update_ग_लिखो_back()
	 * will decide ग_लिखोback rate of other cached devices (remember now
	 * c->idle_counter is 0 alपढ़ोy).
	 */
	अगर (mutex_trylock(&bch_रेजिस्टर_lock)) अणु
		क्रम (i = 0; i < c->devices_max_used; i++) अणु
			अगर (!c->devices[i])
				जारी;

			अगर (UUID_FLASH_ONLY(&c->uuids[i]))
				जारी;

			d = c->devices[i];
			dc = container_of(d, काष्ठा cached_dev, disk);
			/*
			 * set ग_लिखोback rate to शेष minimum value,
			 * then let update_ग_लिखोback_rate() to decide the
			 * upcoming rate.
			 */
			atomic_दीर्घ_set(&dc->ग_लिखोback_rate.rate, 1);
		पूर्ण
		mutex_unlock(&bch_रेजिस्टर_lock);
	पूर्ण अन्यथा
		atomic_दीर्घ_set(&this_dc->ग_लिखोback_rate.rate, 1);
पूर्ण

/* Cached devices - पढ़ो & ग_लिखो stuff */

blk_qc_t cached_dev_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा search *s;
	काष्ठा block_device *orig_bdev = bio->bi_bdev;
	काष्ठा bcache_device *d = orig_bdev->bd_disk->निजी_data;
	काष्ठा cached_dev *dc = container_of(d, काष्ठा cached_dev, disk);
	अचिन्हित दीर्घ start_समय;
	पूर्णांक rw = bio_data_dir(bio);

	अगर (unlikely((d->c && test_bit(CACHE_SET_IO_DISABLE, &d->c->flags)) ||
		     dc->io_disable)) अणु
		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		वापस BLK_QC_T_NONE;
	पूर्ण

	अगर (likely(d->c)) अणु
		अगर (atomic_पढ़ो(&d->c->idle_counter))
			atomic_set(&d->c->idle_counter, 0);
		/*
		 * If at_max_ग_लिखोback_rate of cache set is true and new I/O
		 * comes, quit max ग_लिखोback rate of all cached devices
		 * attached to this cache set, and set at_max_ग_लिखोback_rate
		 * to false.
		 */
		अगर (unlikely(atomic_पढ़ो(&d->c->at_max_ग_लिखोback_rate) == 1)) अणु
			atomic_set(&d->c->at_max_ग_लिखोback_rate, 0);
			quit_max_ग_लिखोback_rate(d->c, dc);
		पूर्ण
	पूर्ण

	start_समय = bio_start_io_acct(bio);

	bio_set_dev(bio, dc->bdev);
	bio->bi_iter.bi_sector += dc->sb.data_offset;

	अगर (cached_dev_get(dc)) अणु
		s = search_alloc(bio, d, orig_bdev, start_समय);
		trace_bcache_request_start(s->d, bio);

		अगर (!bio->bi_iter.bi_size) अणु
			/*
			 * can't call bch_journal_meta from under
			 * submit_bio_noacct
			 */
			जारी_at_nobarrier(&s->cl,
					      cached_dev_nodata,
					      bcache_wq);
		पूर्ण अन्यथा अणु
			s->iop.bypass = check_should_bypass(dc, bio);

			अगर (rw)
				cached_dev_ग_लिखो(dc, s);
			अन्यथा
				cached_dev_पढ़ो(dc, s);
		पूर्ण
	पूर्ण अन्यथा
		/* I/O request sent to backing device */
		detached_dev_करो_request(d, bio, orig_bdev, start_समय);

	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक cached_dev_ioctl(काष्ठा bcache_device *d, भ_शेषe_t mode,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cached_dev *dc = container_of(d, काष्ठा cached_dev, disk);

	अगर (dc->io_disable)
		वापस -EIO;
	अगर (!dc->bdev->bd_disk->fops->ioctl)
		वापस -ENOTTY;
	वापस dc->bdev->bd_disk->fops->ioctl(dc->bdev, mode, cmd, arg);
पूर्ण

व्योम bch_cached_dev_request_init(काष्ठा cached_dev *dc)
अणु
	dc->disk.cache_miss			= cached_dev_cache_miss;
	dc->disk.ioctl				= cached_dev_ioctl;
पूर्ण

/* Flash backed devices */

अटल पूर्णांक flash_dev_cache_miss(काष्ठा btree *b, काष्ठा search *s,
				काष्ठा bio *bio, अचिन्हित पूर्णांक sectors)
अणु
	अचिन्हित पूर्णांक bytes = min(sectors, bio_sectors(bio)) << 9;

	swap(bio->bi_iter.bi_size, bytes);
	zero_fill_bio(bio);
	swap(bio->bi_iter.bi_size, bytes);

	bio_advance(bio, bytes);

	अगर (!bio->bi_iter.bi_size)
		वापस MAP_DONE;

	वापस MAP_CONTINUE;
पूर्ण

अटल व्योम flash_dev_nodata(काष्ठा closure *cl)
अणु
	काष्ठा search *s = container_of(cl, काष्ठा search, cl);

	अगर (s->iop.flush_journal)
		bch_journal_meta(s->iop.c, cl);

	जारी_at(cl, search_मुक्त, शून्य);
पूर्ण

blk_qc_t flash_dev_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा search *s;
	काष्ठा closure *cl;
	काष्ठा bcache_device *d = bio->bi_bdev->bd_disk->निजी_data;

	अगर (unlikely(d->c && test_bit(CACHE_SET_IO_DISABLE, &d->c->flags))) अणु
		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		वापस BLK_QC_T_NONE;
	पूर्ण

	s = search_alloc(bio, d, bio->bi_bdev, bio_start_io_acct(bio));
	cl = &s->cl;
	bio = &s->bio.bio;

	trace_bcache_request_start(s->d, bio);

	अगर (!bio->bi_iter.bi_size) अणु
		/*
		 * can't call bch_journal_meta from under submit_bio_noacct
		 */
		जारी_at_nobarrier(&s->cl,
				      flash_dev_nodata,
				      bcache_wq);
		वापस BLK_QC_T_NONE;
	पूर्ण अन्यथा अगर (bio_data_dir(bio)) अणु
		bch_keybuf_check_overlapping(&s->iop.c->moving_gc_keys,
					&KEY(d->id, bio->bi_iter.bi_sector, 0),
					&KEY(d->id, bio_end_sector(bio), 0));

		s->iop.bypass		= (bio_op(bio) == REQ_OP_DISCARD) != 0;
		s->iop.ग_लिखोback	= true;
		s->iop.bio		= bio;

		closure_call(&s->iop.cl, bch_data_insert, शून्य, cl);
	पूर्ण अन्यथा अणु
		closure_call(&s->iop.cl, cache_lookup, शून्य, cl);
	पूर्ण

	जारी_at(cl, search_मुक्त, शून्य);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक flash_dev_ioctl(काष्ठा bcache_device *d, भ_शेषe_t mode,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस -ENOTTY;
पूर्ण

व्योम bch_flash_dev_request_init(काष्ठा bcache_device *d)
अणु
	d->cache_miss				= flash_dev_cache_miss;
	d->ioctl				= flash_dev_ioctl;
पूर्ण

व्योम bch_request_निकास(व्योम)
अणु
	kmem_cache_destroy(bch_search_cache);
पूर्ण

पूर्णांक __init bch_request_init(व्योम)
अणु
	bch_search_cache = KMEM_CACHE(search, 0);
	अगर (!bch_search_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
