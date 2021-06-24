<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * background ग_लिखोback - scan btree क्रम dirty data and ग_लिखो it to the backing
 * device
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "btree.h"
#समावेश "debug.h"
#समावेश "writeback.h"

#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <trace/events/bcache.h>

अटल व्योम update_gc_after_ग_लिखोback(काष्ठा cache_set *c)
अणु
	अगर (c->gc_after_ग_लिखोback != (BCH_ENABLE_AUTO_GC) ||
	    c->gc_stats.in_use < BCH_AUTO_GC_सूचीTY_THRESHOLD)
		वापस;

	c->gc_after_ग_लिखोback |= BCH_DO_AUTO_GC;
पूर्ण

/* Rate limiting */
अटल uपूर्णांक64_t __calc_target_rate(काष्ठा cached_dev *dc)
अणु
	काष्ठा cache_set *c = dc->disk.c;

	/*
	 * This is the size of the cache, minus the amount used क्रम
	 * flash-only devices
	 */
	uपूर्णांक64_t cache_sectors = c->nbuckets * c->cache->sb.bucket_size -
				atomic_दीर्घ_पढ़ो(&c->flash_dev_dirty_sectors);

	/*
	 * Unक्रमtunately there is no control of global dirty data.  If the
	 * user states that they want 10% dirty data in the cache, and has,
	 * e.g., 5 backing volumes of equal size, we try and ensure each
	 * backing volume uses about 2% of the cache क्रम dirty data.
	 */
	uपूर्णांक32_t bdev_share =
		भाग64_u64(bdev_sectors(dc->bdev) << WRITEBACK_SHARE_SHIFT,
				c->cached_dev_sectors);

	uपूर्णांक64_t cache_dirty_target =
		भाग_u64(cache_sectors * dc->ग_लिखोback_percent, 100);

	/* Ensure each backing dev माला_लो at least one dirty share */
	अगर (bdev_share < 1)
		bdev_share = 1;

	वापस (cache_dirty_target * bdev_share) >> WRITEBACK_SHARE_SHIFT;
पूर्ण

अटल व्योम __update_ग_लिखोback_rate(काष्ठा cached_dev *dc)
अणु
	/*
	 * PI controller:
	 * Figures out the amount that should be written per second.
	 *
	 * First, the error (number of sectors that are dirty beyond our
	 * target) is calculated.  The error is accumulated (numerically
	 * पूर्णांकegrated).
	 *
	 * Then, the proportional value and पूर्णांकegral value are scaled
	 * based on configured values.  These are stored as inverses to
	 * aव्योम fixed poपूर्णांक math and to make configuration easy-- e.g.
	 * the शेष value of 40 क्रम ग_लिखोback_rate_p_term_inverse
	 * attempts to ग_लिखो at a rate that would retire all the dirty
	 * blocks in 40 seconds.
	 *
	 * The ग_लिखोback_rate_i_inverse value of 10000 means that 1/10000th
	 * of the error is accumulated in the पूर्णांकegral term per second.
	 * This acts as a slow, दीर्घ-term average that is not subject to
	 * variations in usage like the p term.
	 */
	पूर्णांक64_t target = __calc_target_rate(dc);
	पूर्णांक64_t dirty = bcache_dev_sectors_dirty(&dc->disk);
	पूर्णांक64_t error = dirty - target;
	पूर्णांक64_t proportional_scaled =
		भाग_s64(error, dc->ग_लिखोback_rate_p_term_inverse);
	पूर्णांक64_t पूर्णांकegral_scaled;
	uपूर्णांक32_t new_rate;

	/*
	 * We need to consider the number of dirty buckets as well
	 * when calculating the proportional_scaled, Otherwise we might
	 * have an unreasonable small ग_लिखोback rate at a highly fragmented situation
	 * when very few dirty sectors consumed a lot dirty buckets, the
	 * worst हाल is when dirty buckets reached cutoff_ग_लिखोback_sync and
	 * dirty data is still not even reached to ग_लिखोback percent, so the rate
	 * still will be at the minimum value, which will cause the ग_लिखो
	 * stuck at a non-ग_लिखोback mode.
	 */
	काष्ठा cache_set *c = dc->disk.c;

	पूर्णांक64_t dirty_buckets = c->nbuckets - c->avail_nbuckets;

	अगर (dc->ग_लिखोback_consider_fragment &&
		c->gc_stats.in_use > BCH_WRITEBACK_FRAGMENT_THRESHOLD_LOW && dirty > 0) अणु
		पूर्णांक64_t fragment =
			भाग_s64((dirty_buckets *  c->cache->sb.bucket_size), dirty);
		पूर्णांक64_t fp_term;
		पूर्णांक64_t fps;

		अगर (c->gc_stats.in_use <= BCH_WRITEBACK_FRAGMENT_THRESHOLD_MID) अणु
			fp_term = (पूर्णांक64_t)dc->ग_लिखोback_rate_fp_term_low *
			(c->gc_stats.in_use - BCH_WRITEBACK_FRAGMENT_THRESHOLD_LOW);
		पूर्ण अन्यथा अगर (c->gc_stats.in_use <= BCH_WRITEBACK_FRAGMENT_THRESHOLD_HIGH) अणु
			fp_term = (पूर्णांक64_t)dc->ग_लिखोback_rate_fp_term_mid *
			(c->gc_stats.in_use - BCH_WRITEBACK_FRAGMENT_THRESHOLD_MID);
		पूर्ण अन्यथा अणु
			fp_term = (पूर्णांक64_t)dc->ग_लिखोback_rate_fp_term_high *
			(c->gc_stats.in_use - BCH_WRITEBACK_FRAGMENT_THRESHOLD_HIGH);
		पूर्ण
		fps = भाग_s64(dirty, dirty_buckets) * fp_term;
		अगर (fragment > 3 && fps > proportional_scaled) अणु
			/* Only overrite the p when fragment > 3 */
			proportional_scaled = fps;
		पूर्ण
	पूर्ण

	अगर ((error < 0 && dc->ग_लिखोback_rate_पूर्णांकegral > 0) ||
	    (error > 0 && समय_beक्रमe64(local_घड़ी(),
			 dc->ग_लिखोback_rate.next + NSEC_PER_MSEC))) अणु
		/*
		 * Only decrease the पूर्णांकegral term अगर it's more than
		 * zero.  Only increase the पूर्णांकegral term अगर the device
		 * is keeping up.  (Don't wind up the पूर्णांकegral
		 * ineffectively in either हाल).
		 *
		 * It's necessary to scale this by
		 * ग_लिखोback_rate_update_seconds to keep the पूर्णांकegral
		 * term dimensioned properly.
		 */
		dc->ग_लिखोback_rate_पूर्णांकegral += error *
			dc->ग_लिखोback_rate_update_seconds;
	पूर्ण

	पूर्णांकegral_scaled = भाग_s64(dc->ग_लिखोback_rate_पूर्णांकegral,
			dc->ग_लिखोback_rate_i_term_inverse);

	new_rate = clamp_t(पूर्णांक32_t, (proportional_scaled + पूर्णांकegral_scaled),
			dc->ग_लिखोback_rate_minimum, NSEC_PER_SEC);

	dc->ग_लिखोback_rate_proportional = proportional_scaled;
	dc->ग_लिखोback_rate_पूर्णांकegral_scaled = पूर्णांकegral_scaled;
	dc->ग_लिखोback_rate_change = new_rate -
			atomic_दीर्घ_पढ़ो(&dc->ग_लिखोback_rate.rate);
	atomic_दीर्घ_set(&dc->ग_लिखोback_rate.rate, new_rate);
	dc->ग_लिखोback_rate_target = target;
पूर्ण

अटल bool set_at_max_ग_लिखोback_rate(काष्ठा cache_set *c,
				       काष्ठा cached_dev *dc)
अणु
	/* Don't sst max ग_लिखोback rate अगर it is disabled */
	अगर (!c->idle_max_ग_लिखोback_rate_enabled)
		वापस false;

	/* Don't set max ग_लिखोback rate अगर gc is running */
	अगर (!c->gc_mark_valid)
		वापस false;
	/*
	 * Idle_counter is increased everyसमय when update_ग_लिखोback_rate() is
	 * called. If all backing devices attached to the same cache set have
	 * identical dc->ग_लिखोback_rate_update_seconds values, it is about 6
	 * rounds of update_ग_लिखोback_rate() on each backing device beक्रमe
	 * c->at_max_ग_लिखोback_rate is set to 1, and then max wrteback rate set
	 * to each dc->ग_लिखोback_rate.rate.
	 * In order to aव्योम extra locking cost क्रम counting exact dirty cached
	 * devices number, c->attached_dev_nr is used to calculate the idle
	 * throushold. It might be bigger अगर not all cached device are in ग_लिखो-
	 * back mode, but it still works well with limited extra rounds of
	 * update_ग_लिखोback_rate().
	 */
	अगर (atomic_inc_वापस(&c->idle_counter) <
	    atomic_पढ़ो(&c->attached_dev_nr) * 6)
		वापस false;

	अगर (atomic_पढ़ो(&c->at_max_ग_लिखोback_rate) != 1)
		atomic_set(&c->at_max_ग_लिखोback_rate, 1);

	atomic_दीर्घ_set(&dc->ग_लिखोback_rate.rate, पूर्णांक_उच्च);

	/* keep ग_लिखोback_rate_target as existing value */
	dc->ग_लिखोback_rate_proportional = 0;
	dc->ग_लिखोback_rate_पूर्णांकegral_scaled = 0;
	dc->ग_लिखोback_rate_change = 0;

	/*
	 * Check c->idle_counter and c->at_max_ग_लिखोback_rate agagain in हाल
	 * new I/O arrives during beक्रमe set_at_max_ग_लिखोback_rate() वापसs.
	 * Then the ग_लिखोback rate is set to 1, and its new value should be
	 * decided via __update_ग_लिखोback_rate().
	 */
	अगर ((atomic_पढ़ो(&c->idle_counter) <
	     atomic_पढ़ो(&c->attached_dev_nr) * 6) ||
	    !atomic_पढ़ो(&c->at_max_ग_लिखोback_rate))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम update_ग_लिखोback_rate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cached_dev *dc = container_of(to_delayed_work(work),
					     काष्ठा cached_dev,
					     ग_लिखोback_rate_update);
	काष्ठा cache_set *c = dc->disk.c;

	/*
	 * should check BCACHE_DEV_RATE_DW_RUNNING beक्रमe calling
	 * cancel_delayed_work_sync().
	 */
	set_bit(BCACHE_DEV_RATE_DW_RUNNING, &dc->disk.flags);
	/* paired with where BCACHE_DEV_RATE_DW_RUNNING is tested */
	smp_mb__after_atomic();

	/*
	 * CACHE_SET_IO_DISABLE might be set via sysfs पूर्णांकerface,
	 * check it here too.
	 */
	अगर (!test_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags) ||
	    test_bit(CACHE_SET_IO_DISABLE, &c->flags)) अणु
		clear_bit(BCACHE_DEV_RATE_DW_RUNNING, &dc->disk.flags);
		/* paired with where BCACHE_DEV_RATE_DW_RUNNING is tested */
		smp_mb__after_atomic();
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&dc->has_dirty) && dc->ग_लिखोback_percent) अणु
		/*
		 * If the whole cache set is idle, set_at_max_ग_लिखोback_rate()
		 * will set ग_लिखोback rate to a max number. Then it is
		 * unncessary to update ग_लिखोback rate क्रम an idle cache set
		 * in maximum ग_लिखोback rate number(s).
		 */
		अगर (!set_at_max_ग_लिखोback_rate(c, dc)) अणु
			करोwn_पढ़ो(&dc->ग_लिखोback_lock);
			__update_ग_लिखोback_rate(dc);
			update_gc_after_ग_लिखोback(c);
			up_पढ़ो(&dc->ग_लिखोback_lock);
		पूर्ण
	पूर्ण


	/*
	 * CACHE_SET_IO_DISABLE might be set via sysfs पूर्णांकerface,
	 * check it here too.
	 */
	अगर (test_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags) &&
	    !test_bit(CACHE_SET_IO_DISABLE, &c->flags)) अणु
		schedule_delayed_work(&dc->ग_लिखोback_rate_update,
			      dc->ग_लिखोback_rate_update_seconds * HZ);
	पूर्ण

	/*
	 * should check BCACHE_DEV_RATE_DW_RUNNING beक्रमe calling
	 * cancel_delayed_work_sync().
	 */
	clear_bit(BCACHE_DEV_RATE_DW_RUNNING, &dc->disk.flags);
	/* paired with where BCACHE_DEV_RATE_DW_RUNNING is tested */
	smp_mb__after_atomic();
पूर्ण

अटल अचिन्हित पूर्णांक ग_लिखोback_delay(काष्ठा cached_dev *dc,
				    अचिन्हित पूर्णांक sectors)
अणु
	अगर (test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags) ||
	    !dc->ग_लिखोback_percent)
		वापस 0;

	वापस bch_next_delay(&dc->ग_लिखोback_rate, sectors);
पूर्ण

काष्ठा dirty_io अणु
	काष्ठा closure		cl;
	काष्ठा cached_dev	*dc;
	uपूर्णांक16_t		sequence;
	काष्ठा bio		bio;
पूर्ण;

अटल व्योम dirty_init(काष्ठा keybuf_key *w)
अणु
	काष्ठा dirty_io *io = w->निजी;
	काष्ठा bio *bio = &io->bio;

	bio_init(bio, bio->bi_अंतरभूत_vecs,
		 DIV_ROUND_UP(KEY_SIZE(&w->key), PAGE_SECTORS));
	अगर (!io->dc->ग_लिखोback_percent)
		bio_set_prio(bio, IOPRIO_PRIO_VALUE(IOPRIO_CLASS_IDLE, 0));

	bio->bi_iter.bi_size	= KEY_SIZE(&w->key) << 9;
	bio->bi_निजी		= w;
	bch_bio_map(bio, शून्य);
पूर्ण

अटल व्योम dirty_io_deकाष्ठाor(काष्ठा closure *cl)
अणु
	काष्ठा dirty_io *io = container_of(cl, काष्ठा dirty_io, cl);

	kमुक्त(io);
पूर्ण

अटल व्योम ग_लिखो_dirty_finish(काष्ठा closure *cl)
अणु
	काष्ठा dirty_io *io = container_of(cl, काष्ठा dirty_io, cl);
	काष्ठा keybuf_key *w = io->bio.bi_निजी;
	काष्ठा cached_dev *dc = io->dc;

	bio_मुक्त_pages(&io->bio);

	/* This is kind of a dumb way of संकेतling errors. */
	अगर (KEY_सूचीTY(&w->key)) अणु
		पूर्णांक ret;
		अचिन्हित पूर्णांक i;
		काष्ठा keylist keys;

		bch_keylist_init(&keys);

		bkey_copy(keys.top, &w->key);
		SET_KEY_सूचीTY(keys.top, false);
		bch_keylist_push(&keys);

		क्रम (i = 0; i < KEY_PTRS(&w->key); i++)
			atomic_inc(&PTR_BUCKET(dc->disk.c, &w->key, i)->pin);

		ret = bch_btree_insert(dc->disk.c, &keys, शून्य, &w->key);

		अगर (ret)
			trace_bcache_ग_लिखोback_collision(&w->key);

		atomic_दीर्घ_inc(ret
				? &dc->disk.c->ग_लिखोback_keys_failed
				: &dc->disk.c->ग_लिखोback_keys_करोne);
	पूर्ण

	bch_keybuf_del(&dc->ग_लिखोback_keys, w);
	up(&dc->in_flight);

	closure_वापस_with_deकाष्ठाor(cl, dirty_io_deकाष्ठाor);
पूर्ण

अटल व्योम dirty_endio(काष्ठा bio *bio)
अणु
	काष्ठा keybuf_key *w = bio->bi_निजी;
	काष्ठा dirty_io *io = w->निजी;

	अगर (bio->bi_status) अणु
		SET_KEY_सूचीTY(&w->key, false);
		bch_count_backing_io_errors(io->dc, bio);
	पूर्ण

	closure_put(&io->cl);
पूर्ण

अटल व्योम ग_लिखो_dirty(काष्ठा closure *cl)
अणु
	काष्ठा dirty_io *io = container_of(cl, काष्ठा dirty_io, cl);
	काष्ठा keybuf_key *w = io->bio.bi_निजी;
	काष्ठा cached_dev *dc = io->dc;

	uपूर्णांक16_t next_sequence;

	अगर (atomic_पढ़ो(&dc->ग_लिखोback_sequence_next) != io->sequence) अणु
		/* Not our turn to ग_लिखो; रुको क्रम a ग_लिखो to complete */
		closure_रुको(&dc->ग_लिखोback_ordering_रुको, cl);

		अगर (atomic_पढ़ो(&dc->ग_लिखोback_sequence_next) == io->sequence) अणु
			/*
			 * Edge हाल-- it happened in indeterminate order
			 * relative to when we were added to रुको list..
			 */
			closure_wake_up(&dc->ग_लिखोback_ordering_रुको);
		पूर्ण

		जारी_at(cl, ग_लिखो_dirty, io->dc->ग_लिखोback_ग_लिखो_wq);
		वापस;
	पूर्ण

	next_sequence = io->sequence + 1;

	/*
	 * IO errors are संकेतled using the dirty bit on the key.
	 * If we failed to पढ़ो, we should not attempt to ग_लिखो to the
	 * backing device.  Instead, immediately go to ग_लिखो_dirty_finish
	 * to clean up.
	 */
	अगर (KEY_सूचीTY(&w->key)) अणु
		dirty_init(w);
		bio_set_op_attrs(&io->bio, REQ_OP_WRITE, 0);
		io->bio.bi_iter.bi_sector = KEY_START(&w->key);
		bio_set_dev(&io->bio, io->dc->bdev);
		io->bio.bi_end_io	= dirty_endio;

		/* I/O request sent to backing device */
		closure_bio_submit(io->dc->disk.c, &io->bio, cl);
	पूर्ण

	atomic_set(&dc->ग_लिखोback_sequence_next, next_sequence);
	closure_wake_up(&dc->ग_लिखोback_ordering_रुको);

	जारी_at(cl, ग_लिखो_dirty_finish, io->dc->ग_लिखोback_ग_लिखो_wq);
पूर्ण

अटल व्योम पढ़ो_dirty_endio(काष्ठा bio *bio)
अणु
	काष्ठा keybuf_key *w = bio->bi_निजी;
	काष्ठा dirty_io *io = w->निजी;

	/* is_पढ़ो = 1 */
	bch_count_io_errors(io->dc->disk.c->cache,
			    bio->bi_status, 1,
			    "reading dirty data from cache");

	dirty_endio(bio);
पूर्ण

अटल व्योम पढ़ो_dirty_submit(काष्ठा closure *cl)
अणु
	काष्ठा dirty_io *io = container_of(cl, काष्ठा dirty_io, cl);

	closure_bio_submit(io->dc->disk.c, &io->bio, cl);

	जारी_at(cl, ग_लिखो_dirty, io->dc->ग_लिखोback_ग_लिखो_wq);
पूर्ण

अटल व्योम पढ़ो_dirty(काष्ठा cached_dev *dc)
अणु
	अचिन्हित पूर्णांक delay = 0;
	काष्ठा keybuf_key *next, *keys[MAX_WRITEBACKS_IN_PASS], *w;
	माप_प्रकार size;
	पूर्णांक nk, i;
	काष्ठा dirty_io *io;
	काष्ठा closure cl;
	uपूर्णांक16_t sequence = 0;

	BUG_ON(!llist_empty(&dc->ग_लिखोback_ordering_रुको.list));
	atomic_set(&dc->ग_लिखोback_sequence_next, sequence);
	closure_init_stack(&cl);

	/*
	 * XXX: अगर we error, background ग_लिखोback just spins. Should use some
	 * mempools.
	 */

	next = bch_keybuf_next(&dc->ग_लिखोback_keys);

	जबतक (!kthपढ़ो_should_stop() &&
	       !test_bit(CACHE_SET_IO_DISABLE, &dc->disk.c->flags) &&
	       next) अणु
		size = 0;
		nk = 0;

		करो अणु
			BUG_ON(ptr_stale(dc->disk.c, &next->key, 0));

			/*
			 * Don't combine too many operations, even अगर they
			 * are all small.
			 */
			अगर (nk >= MAX_WRITEBACKS_IN_PASS)
				अवरोध;

			/*
			 * If the current operation is very large, करोn't
			 * further combine operations.
			 */
			अगर (size >= MAX_WRITESIZE_IN_PASS)
				अवरोध;

			/*
			 * Operations are only eligible to be combined
			 * अगर they are contiguous.
			 *
			 * TODO: add a heuristic willing to fire a
			 * certain amount of non-contiguous IO per pass,
			 * so that we can benefit from backing device
			 * command queueing.
			 */
			अगर ((nk != 0) && bkey_cmp(&keys[nk-1]->key,
						&START_KEY(&next->key)))
				अवरोध;

			size += KEY_SIZE(&next->key);
			keys[nk++] = next;
		पूर्ण जबतक ((next = bch_keybuf_next(&dc->ग_लिखोback_keys)));

		/* Now we have gathered a set of 1..5 keys to ग_लिखो back. */
		क्रम (i = 0; i < nk; i++) अणु
			w = keys[i];

			io = kzalloc(काष्ठा_size(io, bio.bi_अंतरभूत_vecs,
						DIV_ROUND_UP(KEY_SIZE(&w->key), PAGE_SECTORS)),
				     GFP_KERNEL);
			अगर (!io)
				जाओ err;

			w->निजी	= io;
			io->dc		= dc;
			io->sequence    = sequence++;

			dirty_init(w);
			bio_set_op_attrs(&io->bio, REQ_OP_READ, 0);
			io->bio.bi_iter.bi_sector = PTR_OFFSET(&w->key, 0);
			bio_set_dev(&io->bio, dc->disk.c->cache->bdev);
			io->bio.bi_end_io	= पढ़ो_dirty_endio;

			अगर (bch_bio_alloc_pages(&io->bio, GFP_KERNEL))
				जाओ err_मुक्त;

			trace_bcache_ग_लिखोback(&w->key);

			करोwn(&dc->in_flight);

			/*
			 * We've acquired a semaphore क्रम the maximum
			 * simultaneous number of ग_लिखोbacks; from here
			 * everything happens asynchronously.
			 */
			closure_call(&io->cl, पढ़ो_dirty_submit, शून्य, &cl);
		पूर्ण

		delay = ग_लिखोback_delay(dc, size);

		जबतक (!kthपढ़ो_should_stop() &&
		       !test_bit(CACHE_SET_IO_DISABLE, &dc->disk.c->flags) &&
		       delay) अणु
			schedule_समयout_पूर्णांकerruptible(delay);
			delay = ग_लिखोback_delay(dc, 0);
		पूर्ण
	पूर्ण

	अगर (0) अणु
err_मुक्त:
		kमुक्त(w->निजी);
err:
		bch_keybuf_del(&dc->ग_लिखोback_keys, w);
	पूर्ण

	/*
	 * Wait क्रम outstanding ग_लिखोback IOs to finish (and keybuf slots to be
	 * मुक्तd) beक्रमe refilling again
	 */
	closure_sync(&cl);
पूर्ण

/* Scan क्रम dirty data */

व्योम bcache_dev_sectors_dirty_add(काष्ठा cache_set *c, अचिन्हित पूर्णांक inode,
				  uपूर्णांक64_t offset, पूर्णांक nr_sectors)
अणु
	काष्ठा bcache_device *d = c->devices[inode];
	अचिन्हित पूर्णांक stripe_offset, sectors_dirty;
	पूर्णांक stripe;

	अगर (!d)
		वापस;

	stripe = offset_to_stripe(d, offset);
	अगर (stripe < 0)
		वापस;

	अगर (UUID_FLASH_ONLY(&c->uuids[inode]))
		atomic_दीर्घ_add(nr_sectors, &c->flash_dev_dirty_sectors);

	stripe_offset = offset & (d->stripe_size - 1);

	जबतक (nr_sectors) अणु
		पूर्णांक s = min_t(अचिन्हित पूर्णांक, असल(nr_sectors),
			      d->stripe_size - stripe_offset);

		अगर (nr_sectors < 0)
			s = -s;

		अगर (stripe >= d->nr_stripes)
			वापस;

		sectors_dirty = atomic_add_वापस(s,
					d->stripe_sectors_dirty + stripe);
		अगर (sectors_dirty == d->stripe_size)
			set_bit(stripe, d->full_dirty_stripes);
		अन्यथा
			clear_bit(stripe, d->full_dirty_stripes);

		nr_sectors -= s;
		stripe_offset = 0;
		stripe++;
	पूर्ण
पूर्ण

अटल bool dirty_pred(काष्ठा keybuf *buf, काष्ठा bkey *k)
अणु
	काष्ठा cached_dev *dc = container_of(buf,
					     काष्ठा cached_dev,
					     ग_लिखोback_keys);

	BUG_ON(KEY_INODE(k) != dc->disk.id);

	वापस KEY_सूचीTY(k);
पूर्ण

अटल व्योम refill_full_stripes(काष्ठा cached_dev *dc)
अणु
	काष्ठा keybuf *buf = &dc->ग_लिखोback_keys;
	अचिन्हित पूर्णांक start_stripe, next_stripe;
	पूर्णांक stripe;
	bool wrapped = false;

	stripe = offset_to_stripe(&dc->disk, KEY_OFFSET(&buf->last_scanned));
	अगर (stripe < 0)
		stripe = 0;

	start_stripe = stripe;

	जबतक (1) अणु
		stripe = find_next_bit(dc->disk.full_dirty_stripes,
				       dc->disk.nr_stripes, stripe);

		अगर (stripe == dc->disk.nr_stripes)
			जाओ next;

		next_stripe = find_next_zero_bit(dc->disk.full_dirty_stripes,
						 dc->disk.nr_stripes, stripe);

		buf->last_scanned = KEY(dc->disk.id,
					stripe * dc->disk.stripe_size, 0);

		bch_refill_keybuf(dc->disk.c, buf,
				  &KEY(dc->disk.id,
				       next_stripe * dc->disk.stripe_size, 0),
				  dirty_pred);

		अगर (array_मुक्तlist_empty(&buf->मुक्तlist))
			वापस;

		stripe = next_stripe;
next:
		अगर (wrapped && stripe > start_stripe)
			वापस;

		अगर (stripe == dc->disk.nr_stripes) अणु
			stripe = 0;
			wrapped = true;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Returns true अगर we scanned the entire disk
 */
अटल bool refill_dirty(काष्ठा cached_dev *dc)
अणु
	काष्ठा keybuf *buf = &dc->ग_लिखोback_keys;
	काष्ठा bkey start = KEY(dc->disk.id, 0, 0);
	काष्ठा bkey end = KEY(dc->disk.id, MAX_KEY_OFFSET, 0);
	काष्ठा bkey start_pos;

	/*
	 * make sure keybuf pos is inside the range क्रम this disk - at bringup
	 * we might not be attached yet so this disk's inode nr isn't
	 * initialized then
	 */
	अगर (bkey_cmp(&buf->last_scanned, &start) < 0 ||
	    bkey_cmp(&buf->last_scanned, &end) > 0)
		buf->last_scanned = start;

	अगर (dc->partial_stripes_expensive) अणु
		refill_full_stripes(dc);
		अगर (array_मुक्तlist_empty(&buf->मुक्तlist))
			वापस false;
	पूर्ण

	start_pos = buf->last_scanned;
	bch_refill_keybuf(dc->disk.c, buf, &end, dirty_pred);

	अगर (bkey_cmp(&buf->last_scanned, &end) < 0)
		वापस false;

	/*
	 * If we get to the end start scanning again from the beginning, and
	 * only scan up to where we initially started scanning from:
	 */
	buf->last_scanned = start;
	bch_refill_keybuf(dc->disk.c, buf, &start_pos, dirty_pred);

	वापस bkey_cmp(&buf->last_scanned, &start_pos) >= 0;
पूर्ण

अटल पूर्णांक bch_ग_लिखोback_thपढ़ो(व्योम *arg)
अणु
	काष्ठा cached_dev *dc = arg;
	काष्ठा cache_set *c = dc->disk.c;
	bool searched_full_index;

	bch_ratelimit_reset(&dc->ग_लिखोback_rate);

	जबतक (!kthपढ़ो_should_stop() &&
	       !test_bit(CACHE_SET_IO_DISABLE, &c->flags)) अणु
		करोwn_ग_लिखो(&dc->ग_लिखोback_lock);
		set_current_state(TASK_INTERRUPTIBLE);
		/*
		 * If the bache device is detaching, skip here and जारी
		 * to perक्रमm ग_लिखोback. Otherwise, अगर no dirty data on cache,
		 * or there is dirty data on cache but ग_लिखोback is disabled,
		 * the ग_लिखोback thपढ़ो should sleep here and रुको क्रम others
		 * to wake up it.
		 */
		अगर (!test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags) &&
		    (!atomic_पढ़ो(&dc->has_dirty) || !dc->ग_लिखोback_running)) अणु
			up_ग_लिखो(&dc->ग_लिखोback_lock);

			अगर (kthपढ़ो_should_stop() ||
			    test_bit(CACHE_SET_IO_DISABLE, &c->flags)) अणु
				set_current_state(TASK_RUNNING);
				अवरोध;
			पूर्ण

			schedule();
			जारी;
		पूर्ण
		set_current_state(TASK_RUNNING);

		searched_full_index = refill_dirty(dc);

		अगर (searched_full_index &&
		    RB_EMPTY_ROOT(&dc->ग_लिखोback_keys.keys)) अणु
			atomic_set(&dc->has_dirty, 0);
			SET_BDEV_STATE(&dc->sb, BDEV_STATE_CLEAN);
			bch_ग_लिखो_bdev_super(dc, शून्य);
			/*
			 * If bcache device is detaching via sysfs पूर्णांकerface,
			 * ग_लिखोback thपढ़ो should stop after there is no dirty
			 * data on cache. BCACHE_DEV_DETACHING flag is set in
			 * bch_cached_dev_detach().
			 */
			अगर (test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags)) अणु
				काष्ठा closure cl;

				closure_init_stack(&cl);
				स_रखो(&dc->sb.set_uuid, 0, 16);
				SET_BDEV_STATE(&dc->sb, BDEV_STATE_NONE);

				bch_ग_लिखो_bdev_super(dc, &cl);
				closure_sync(&cl);

				up_ग_लिखो(&dc->ग_लिखोback_lock);
				अवरोध;
			पूर्ण

			/*
			 * When dirty data rate is high (e.g. 50%+), there might
			 * be heavy buckets fragmentation after ग_लिखोback
			 * finished, which hurts following ग_लिखो perक्रमmance.
			 * If users really care about ग_लिखो perक्रमmance they
			 * may set BCH_ENABLE_AUTO_GC via sysfs, then when
			 * BCH_DO_AUTO_GC is set, garbage collection thपढ़ो
			 * will be wake up here. After moving gc, the shrunk
			 * btree and discarded मुक्त buckets SSD space may be
			 * helpful क्रम following ग_लिखो requests.
			 */
			अगर (c->gc_after_ग_लिखोback ==
			    (BCH_ENABLE_AUTO_GC|BCH_DO_AUTO_GC)) अणु
				c->gc_after_ग_लिखोback &= ~BCH_DO_AUTO_GC;
				क्रमce_wake_up_gc(c);
			पूर्ण
		पूर्ण

		up_ग_लिखो(&dc->ग_लिखोback_lock);

		पढ़ो_dirty(dc);

		अगर (searched_full_index) अणु
			अचिन्हित पूर्णांक delay = dc->ग_लिखोback_delay * HZ;

			जबतक (delay &&
			       !kthपढ़ो_should_stop() &&
			       !test_bit(CACHE_SET_IO_DISABLE, &c->flags) &&
			       !test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags))
				delay = schedule_समयout_पूर्णांकerruptible(delay);

			bch_ratelimit_reset(&dc->ग_लिखोback_rate);
		पूर्ण
	पूर्ण

	अगर (dc->ग_लिखोback_ग_लिखो_wq) अणु
		flush_workqueue(dc->ग_लिखोback_ग_लिखो_wq);
		destroy_workqueue(dc->ग_लिखोback_ग_लिखो_wq);
	पूर्ण
	cached_dev_put(dc);
	रुको_क्रम_kthपढ़ो_stop();

	वापस 0;
पूर्ण

/* Init */
#घोषणा INIT_KEYS_EACH_TIME	500000
#घोषणा INIT_KEYS_SLEEP_MS	100

काष्ठा sectors_dirty_init अणु
	काष्ठा btree_op	op;
	अचिन्हित पूर्णांक	inode;
	माप_प्रकार		count;
	काष्ठा bkey	start;
पूर्ण;

अटल पूर्णांक sectors_dirty_init_fn(काष्ठा btree_op *_op, काष्ठा btree *b,
				 काष्ठा bkey *k)
अणु
	काष्ठा sectors_dirty_init *op = container_of(_op,
						काष्ठा sectors_dirty_init, op);
	अगर (KEY_INODE(k) > op->inode)
		वापस MAP_DONE;

	अगर (KEY_सूचीTY(k))
		bcache_dev_sectors_dirty_add(b->c, KEY_INODE(k),
					     KEY_START(k), KEY_SIZE(k));

	op->count++;
	अगर (atomic_पढ़ो(&b->c->search_inflight) &&
	    !(op->count % INIT_KEYS_EACH_TIME)) अणु
		bkey_copy_key(&op->start, k);
		वापस -EAGAIN;
	पूर्ण

	वापस MAP_CONTINUE;
पूर्ण

अटल पूर्णांक bch_root_node_dirty_init(काष्ठा cache_set *c,
				     काष्ठा bcache_device *d,
				     काष्ठा bkey *k)
अणु
	काष्ठा sectors_dirty_init op;
	पूर्णांक ret;

	bch_btree_op_init(&op.op, -1);
	op.inode = d->id;
	op.count = 0;
	op.start = KEY(op.inode, 0, 0);

	करो अणु
		ret = bcache_btree(map_keys_recurse,
				   k,
				   c->root,
				   &op.op,
				   &op.start,
				   sectors_dirty_init_fn,
				   0);
		अगर (ret == -EAGAIN)
			schedule_समयout_पूर्णांकerruptible(
				msecs_to_jअगरfies(INIT_KEYS_SLEEP_MS));
		अन्यथा अगर (ret < 0) अणु
			pr_warn("sectors dirty init failed, ret=%d!\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (ret == -EAGAIN);

	वापस ret;
पूर्ण

अटल पूर्णांक bch_dirty_init_thपढ़ो(व्योम *arg)
अणु
	काष्ठा dirty_init_thrd_info *info = arg;
	काष्ठा bch_dirty_init_state *state = info->state;
	काष्ठा cache_set *c = state->c;
	काष्ठा btree_iter iter;
	काष्ठा bkey *k, *p;
	पूर्णांक cur_idx, prev_idx, skip_nr;

	k = p = शून्य;
	cur_idx = prev_idx = 0;

	bch_btree_iter_init(&c->root->keys, &iter, शून्य);
	k = bch_btree_iter_next_filter(&iter, &c->root->keys, bch_ptr_bad);
	BUG_ON(!k);

	p = k;

	जबतक (k) अणु
		spin_lock(&state->idx_lock);
		cur_idx = state->key_idx;
		state->key_idx++;
		spin_unlock(&state->idx_lock);

		skip_nr = cur_idx - prev_idx;

		जबतक (skip_nr) अणु
			k = bch_btree_iter_next_filter(&iter,
						       &c->root->keys,
						       bch_ptr_bad);
			अगर (k)
				p = k;
			अन्यथा अणु
				atomic_set(&state->enough, 1);
				/* Update state->enough earlier */
				smp_mb__after_atomic();
				जाओ out;
			पूर्ण
			skip_nr--;
			cond_resched();
		पूर्ण

		अगर (p) अणु
			अगर (bch_root_node_dirty_init(c, state->d, p) < 0)
				जाओ out;
		पूर्ण

		p = शून्य;
		prev_idx = cur_idx;
		cond_resched();
	पूर्ण

out:
	/* In order to wake up state->रुको in समय */
	smp_mb__beक्रमe_atomic();
	अगर (atomic_dec_and_test(&state->started))
		wake_up(&state->रुको);

	वापस 0;
पूर्ण

अटल पूर्णांक bch_btre_dirty_init_thपढ़ो_nr(व्योम)
अणु
	पूर्णांक n = num_online_cpus()/2;

	अगर (n == 0)
		n = 1;
	अन्यथा अगर (n > BCH_सूचीTY_INIT_THRD_MAX)
		n = BCH_सूचीTY_INIT_THRD_MAX;

	वापस n;
पूर्ण

व्योम bch_sectors_dirty_init(काष्ठा bcache_device *d)
अणु
	पूर्णांक i;
	काष्ठा bkey *k = शून्य;
	काष्ठा btree_iter iter;
	काष्ठा sectors_dirty_init op;
	काष्ठा cache_set *c = d->c;
	काष्ठा bch_dirty_init_state *state;
	अक्षर name[32];

	/* Just count root keys अगर no leaf node */
	अगर (c->root->level == 0) अणु
		bch_btree_op_init(&op.op, -1);
		op.inode = d->id;
		op.count = 0;
		op.start = KEY(op.inode, 0, 0);

		क्रम_each_key_filter(&c->root->keys,
				    k, &iter, bch_ptr_invalid)
			sectors_dirty_init_fn(&op.op, c->root, k);
		वापस;
	पूर्ण

	state = kzalloc(माप(काष्ठा bch_dirty_init_state), GFP_KERNEL);
	अगर (!state) अणु
		pr_warn("sectors dirty init failed: cannot allocate memory\n");
		वापस;
	पूर्ण

	state->c = c;
	state->d = d;
	state->total_thपढ़ोs = bch_btre_dirty_init_thपढ़ो_nr();
	state->key_idx = 0;
	spin_lock_init(&state->idx_lock);
	atomic_set(&state->started, 0);
	atomic_set(&state->enough, 0);
	init_रुकोqueue_head(&state->रुको);

	क्रम (i = 0; i < state->total_thपढ़ोs; i++) अणु
		/* Fetch latest state->enough earlier */
		smp_mb__beक्रमe_atomic();
		अगर (atomic_पढ़ो(&state->enough))
			अवरोध;

		state->infos[i].state = state;
		atomic_inc(&state->started);
		snम_लिखो(name, माप(name), "bch_dirty_init[%d]", i);

		state->infos[i].thपढ़ो =
			kthपढ़ो_run(bch_dirty_init_thपढ़ो,
				    &state->infos[i],
				    name);
		अगर (IS_ERR(state->infos[i].thपढ़ो)) अणु
			pr_err("fails to run thread bch_dirty_init[%d]\n", i);
			क्रम (--i; i >= 0; i--)
				kthपढ़ो_stop(state->infos[i].thपढ़ो);
			जाओ out;
		पूर्ण
	पूर्ण

	रुको_event_पूर्णांकerruptible(state->रुको,
		 atomic_पढ़ो(&state->started) == 0 ||
		 test_bit(CACHE_SET_IO_DISABLE, &c->flags));

out:
	kमुक्त(state);
पूर्ण

व्योम bch_cached_dev_ग_लिखोback_init(काष्ठा cached_dev *dc)
अणु
	sema_init(&dc->in_flight, 64);
	init_rwsem(&dc->ग_लिखोback_lock);
	bch_keybuf_init(&dc->ग_लिखोback_keys);

	dc->ग_लिखोback_metadata		= true;
	dc->ग_लिखोback_running		= false;
	dc->ग_लिखोback_consider_fragment = true;
	dc->ग_लिखोback_percent		= 10;
	dc->ग_लिखोback_delay		= 30;
	atomic_दीर्घ_set(&dc->ग_लिखोback_rate.rate, 1024);
	dc->ग_लिखोback_rate_minimum	= 8;

	dc->ग_लिखोback_rate_update_seconds = WRITEBACK_RATE_UPDATE_SECS_DEFAULT;
	dc->ग_लिखोback_rate_p_term_inverse = 40;
	dc->ग_लिखोback_rate_fp_term_low = 1;
	dc->ग_लिखोback_rate_fp_term_mid = 10;
	dc->ग_लिखोback_rate_fp_term_high = 1000;
	dc->ग_लिखोback_rate_i_term_inverse = 10000;

	WARN_ON(test_and_clear_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags));
	INIT_DELAYED_WORK(&dc->ग_लिखोback_rate_update, update_ग_लिखोback_rate);
पूर्ण

पूर्णांक bch_cached_dev_ग_लिखोback_start(काष्ठा cached_dev *dc)
अणु
	dc->ग_लिखोback_ग_लिखो_wq = alloc_workqueue("bcache_writeback_wq",
						WQ_MEM_RECLAIM, 0);
	अगर (!dc->ग_लिखोback_ग_लिखो_wq)
		वापस -ENOMEM;

	cached_dev_get(dc);
	dc->ग_लिखोback_thपढ़ो = kthपढ़ो_create(bch_ग_लिखोback_thपढ़ो, dc,
					      "bcache_writeback");
	अगर (IS_ERR(dc->ग_लिखोback_thपढ़ो)) अणु
		cached_dev_put(dc);
		destroy_workqueue(dc->ग_लिखोback_ग_लिखो_wq);
		वापस PTR_ERR(dc->ग_लिखोback_thपढ़ो);
	पूर्ण
	dc->ग_लिखोback_running = true;

	WARN_ON(test_and_set_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags));
	schedule_delayed_work(&dc->ग_लिखोback_rate_update,
			      dc->ग_लिखोback_rate_update_seconds * HZ);

	bch_ग_लिखोback_queue(dc);

	वापस 0;
पूर्ण
