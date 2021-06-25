<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software Limited.
 * Copyright (C) 2004-2008 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/dm-dirty-log.h>
#समावेश <linux/dm-region-hash.h>

#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "dm.h"

#घोषणा	DM_MSG_PREFIX	"region hash"

/*-----------------------------------------------------------------
 * Region hash
 *
 * The mirror splits itself up पूर्णांकo discrete regions.  Each
 * region can be in one of three states: clean, dirty,
 * nosync.  There is no need to put clean regions in the hash.
 *
 * In addition to being present in the hash table a region _may_
 * be present on one of three lists.
 *
 *   clean_regions: Regions on this list have no io pending to
 *   them, they are in sync, we are no दीर्घer पूर्णांकerested in them,
 *   they are dull.  dm_rh_update_states() will हटाओ them from the
 *   hash table.
 *
 *   quiesced_regions: These regions have been spun करोwn, पढ़ोy
 *   क्रम recovery.  rh_recovery_start() will हटाओ regions from
 *   this list and hand them to kmirrord, which will schedule the
 *   recovery io with kcopyd.
 *
 *   recovered_regions: Regions that kcopyd has successfully
 *   recovered.  dm_rh_update_states() will now schedule any delayed
 *   io, up the recovery_count, and हटाओ the region from the
 *   hash.
 *
 * There are 2 locks:
 *   A rw spin lock 'hash_lock' protects just the hash table,
 *   this is never held in ग_लिखो mode from पूर्णांकerrupt context,
 *   which I believe means that we only have to disable irqs when
 *   करोing a ग_लिखो lock.
 *
 *   An ordinary spin lock 'region_lock' that protects the three
 *   lists in the region_hash, with the 'state', 'list' and
 *   'delayed_bios' fields of the regions.  This is used from irq
 *   context, so all other uses will have to suspend local irqs.
 *---------------------------------------------------------------*/
काष्ठा dm_region_hash अणु
	uपूर्णांक32_t region_size;
	अचिन्हित region_shअगरt;

	/* holds persistent region state */
	काष्ठा dm_dirty_log *log;

	/* hash table */
	rwlock_t hash_lock;
	अचिन्हित mask;
	अचिन्हित nr_buckets;
	अचिन्हित prime;
	अचिन्हित shअगरt;
	काष्ठा list_head *buckets;

	/*
	 * If there was a flush failure no regions can be marked clean.
	 */
	पूर्णांक flush_failure;

	अचिन्हित max_recovery; /* Max # of regions to recover in parallel */

	spinlock_t region_lock;
	atomic_t recovery_in_flight;
	काष्ठा list_head clean_regions;
	काष्ठा list_head quiesced_regions;
	काष्ठा list_head recovered_regions;
	काष्ठा list_head failed_recovered_regions;
	काष्ठा semaphore recovery_count;

	mempool_t region_pool;

	व्योम *context;
	sector_t target_begin;

	/* Callback function to schedule bios ग_लिखोs */
	व्योम (*dispatch_bios)(व्योम *context, काष्ठा bio_list *bios);

	/* Callback function to wakeup callers worker thपढ़ो. */
	व्योम (*wakeup_workers)(व्योम *context);

	/* Callback function to wakeup callers recovery रुकोers. */
	व्योम (*wakeup_all_recovery_रुकोers)(व्योम *context);
पूर्ण;

काष्ठा dm_region अणु
	काष्ठा dm_region_hash *rh;	/* FIXME: can we get rid of this ? */
	region_t key;
	पूर्णांक state;

	काष्ठा list_head hash_list;
	काष्ठा list_head list;

	atomic_t pending;
	काष्ठा bio_list delayed_bios;
पूर्ण;

/*
 * Conversion fns
 */
अटल region_t dm_rh_sector_to_region(काष्ठा dm_region_hash *rh, sector_t sector)
अणु
	वापस sector >> rh->region_shअगरt;
पूर्ण

sector_t dm_rh_region_to_sector(काष्ठा dm_region_hash *rh, region_t region)
अणु
	वापस region << rh->region_shअगरt;
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_region_to_sector);

region_t dm_rh_bio_to_region(काष्ठा dm_region_hash *rh, काष्ठा bio *bio)
अणु
	वापस dm_rh_sector_to_region(rh, bio->bi_iter.bi_sector -
				      rh->target_begin);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_bio_to_region);

व्योम *dm_rh_region_context(काष्ठा dm_region *reg)
अणु
	वापस reg->rh->context;
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_region_context);

region_t dm_rh_get_region_key(काष्ठा dm_region *reg)
अणु
	वापस reg->key;
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_get_region_key);

sector_t dm_rh_get_region_size(काष्ठा dm_region_hash *rh)
अणु
	वापस rh->region_size;
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_get_region_size);

/*
 * FIXME: shall we pass in a काष्ठाure instead of all these args to
 * dm_region_hash_create()????
 */
#घोषणा RH_HASH_MULT 2654435387U
#घोषणा RH_HASH_SHIFT 12

#घोषणा MIN_REGIONS 64
काष्ठा dm_region_hash *dm_region_hash_create(
		व्योम *context, व्योम (*dispatch_bios)(व्योम *context,
						     काष्ठा bio_list *bios),
		व्योम (*wakeup_workers)(व्योम *context),
		व्योम (*wakeup_all_recovery_रुकोers)(व्योम *context),
		sector_t target_begin, अचिन्हित max_recovery,
		काष्ठा dm_dirty_log *log, uपूर्णांक32_t region_size,
		region_t nr_regions)
अणु
	काष्ठा dm_region_hash *rh;
	अचिन्हित nr_buckets, max_buckets;
	माप_प्रकार i;
	पूर्णांक ret;

	/*
	 * Calculate a suitable number of buckets क्रम our hash
	 * table.
	 */
	max_buckets = nr_regions >> 6;
	क्रम (nr_buckets = 128u; nr_buckets < max_buckets; nr_buckets <<= 1)
		;
	nr_buckets >>= 1;

	rh = kzalloc(माप(*rh), GFP_KERNEL);
	अगर (!rh) अणु
		DMERR("unable to allocate region hash memory");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	rh->context = context;
	rh->dispatch_bios = dispatch_bios;
	rh->wakeup_workers = wakeup_workers;
	rh->wakeup_all_recovery_रुकोers = wakeup_all_recovery_रुकोers;
	rh->target_begin = target_begin;
	rh->max_recovery = max_recovery;
	rh->log = log;
	rh->region_size = region_size;
	rh->region_shअगरt = __ffs(region_size);
	rwlock_init(&rh->hash_lock);
	rh->mask = nr_buckets - 1;
	rh->nr_buckets = nr_buckets;

	rh->shअगरt = RH_HASH_SHIFT;
	rh->prime = RH_HASH_MULT;

	rh->buckets = vदो_स्मृति(array_size(nr_buckets, माप(*rh->buckets)));
	अगर (!rh->buckets) अणु
		DMERR("unable to allocate region hash bucket memory");
		kमुक्त(rh);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < nr_buckets; i++)
		INIT_LIST_HEAD(rh->buckets + i);

	spin_lock_init(&rh->region_lock);
	sema_init(&rh->recovery_count, 0);
	atomic_set(&rh->recovery_in_flight, 0);
	INIT_LIST_HEAD(&rh->clean_regions);
	INIT_LIST_HEAD(&rh->quiesced_regions);
	INIT_LIST_HEAD(&rh->recovered_regions);
	INIT_LIST_HEAD(&rh->failed_recovered_regions);
	rh->flush_failure = 0;

	ret = mempool_init_kदो_स्मृति_pool(&rh->region_pool, MIN_REGIONS,
					माप(काष्ठा dm_region));
	अगर (ret) अणु
		vमुक्त(rh->buckets);
		kमुक्त(rh);
		rh = ERR_PTR(-ENOMEM);
	पूर्ण

	वापस rh;
पूर्ण
EXPORT_SYMBOL_GPL(dm_region_hash_create);

व्योम dm_region_hash_destroy(काष्ठा dm_region_hash *rh)
अणु
	अचिन्हित h;
	काष्ठा dm_region *reg, *nreg;

	BUG_ON(!list_empty(&rh->quiesced_regions));
	क्रम (h = 0; h < rh->nr_buckets; h++) अणु
		list_क्रम_each_entry_safe(reg, nreg, rh->buckets + h,
					 hash_list) अणु
			BUG_ON(atomic_पढ़ो(&reg->pending));
			mempool_मुक्त(reg, &rh->region_pool);
		पूर्ण
	पूर्ण

	अगर (rh->log)
		dm_dirty_log_destroy(rh->log);

	mempool_निकास(&rh->region_pool);
	vमुक्त(rh->buckets);
	kमुक्त(rh);
पूर्ण
EXPORT_SYMBOL_GPL(dm_region_hash_destroy);

काष्ठा dm_dirty_log *dm_rh_dirty_log(काष्ठा dm_region_hash *rh)
अणु
	वापस rh->log;
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_dirty_log);

अटल अचिन्हित rh_hash(काष्ठा dm_region_hash *rh, region_t region)
अणु
	वापस (अचिन्हित) ((region * rh->prime) >> rh->shअगरt) & rh->mask;
पूर्ण

अटल काष्ठा dm_region *__rh_lookup(काष्ठा dm_region_hash *rh, region_t region)
अणु
	काष्ठा dm_region *reg;
	काष्ठा list_head *bucket = rh->buckets + rh_hash(rh, region);

	list_क्रम_each_entry(reg, bucket, hash_list)
		अगर (reg->key == region)
			वापस reg;

	वापस शून्य;
पूर्ण

अटल व्योम __rh_insert(काष्ठा dm_region_hash *rh, काष्ठा dm_region *reg)
अणु
	list_add(&reg->hash_list, rh->buckets + rh_hash(rh, reg->key));
पूर्ण

अटल काष्ठा dm_region *__rh_alloc(काष्ठा dm_region_hash *rh, region_t region)
अणु
	काष्ठा dm_region *reg, *nreg;

	nreg = mempool_alloc(&rh->region_pool, GFP_ATOMIC);
	अगर (unlikely(!nreg))
		nreg = kदो_स्मृति(माप(*nreg), GFP_NOIO | __GFP_NOFAIL);

	nreg->state = rh->log->type->in_sync(rh->log, region, 1) ?
		      DM_RH_CLEAN : DM_RH_NOSYNC;
	nreg->rh = rh;
	nreg->key = region;
	INIT_LIST_HEAD(&nreg->list);
	atomic_set(&nreg->pending, 0);
	bio_list_init(&nreg->delayed_bios);

	ग_लिखो_lock_irq(&rh->hash_lock);
	reg = __rh_lookup(rh, region);
	अगर (reg)
		/* We lost the race. */
		mempool_मुक्त(nreg, &rh->region_pool);
	अन्यथा अणु
		__rh_insert(rh, nreg);
		अगर (nreg->state == DM_RH_CLEAN) अणु
			spin_lock(&rh->region_lock);
			list_add(&nreg->list, &rh->clean_regions);
			spin_unlock(&rh->region_lock);
		पूर्ण

		reg = nreg;
	पूर्ण
	ग_लिखो_unlock_irq(&rh->hash_lock);

	वापस reg;
पूर्ण

अटल काष्ठा dm_region *__rh_find(काष्ठा dm_region_hash *rh, region_t region)
अणु
	काष्ठा dm_region *reg;

	reg = __rh_lookup(rh, region);
	अगर (!reg) अणु
		पढ़ो_unlock(&rh->hash_lock);
		reg = __rh_alloc(rh, region);
		पढ़ो_lock(&rh->hash_lock);
	पूर्ण

	वापस reg;
पूर्ण

पूर्णांक dm_rh_get_state(काष्ठा dm_region_hash *rh, region_t region, पूर्णांक may_block)
अणु
	पूर्णांक r;
	काष्ठा dm_region *reg;

	पढ़ो_lock(&rh->hash_lock);
	reg = __rh_lookup(rh, region);
	पढ़ो_unlock(&rh->hash_lock);

	अगर (reg)
		वापस reg->state;

	/*
	 * The region wasn't in the hash, so we fall back to the
	 * dirty log.
	 */
	r = rh->log->type->in_sync(rh->log, region, may_block);

	/*
	 * Any error from the dirty log (eg. -EWOULDBLOCK) माला_लो
	 * taken as a DM_RH_NOSYNC
	 */
	वापस r == 1 ? DM_RH_CLEAN : DM_RH_NOSYNC;
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_get_state);

अटल व्योम complete_resync_work(काष्ठा dm_region *reg, पूर्णांक success)
अणु
	काष्ठा dm_region_hash *rh = reg->rh;

	rh->log->type->set_region_sync(rh->log, reg->key, success);

	/*
	 * Dispatch the bios beक्रमe we call 'wake_up_all'.
	 * This is important because अगर we are suspending,
	 * we want to know that recovery is complete and
	 * the work queue is flushed.  If we wake_up_all
	 * beक्रमe we dispatch_bios (queue bios and call wake()),
	 * then we risk suspending beक्रमe the work queue
	 * has been properly flushed.
	 */
	rh->dispatch_bios(rh->context, &reg->delayed_bios);
	अगर (atomic_dec_and_test(&rh->recovery_in_flight))
		rh->wakeup_all_recovery_रुकोers(rh->context);
	up(&rh->recovery_count);
पूर्ण

/* dm_rh_mark_nosync
 * @ms
 * @bio
 *
 * The bio was written on some mirror(s) but failed on other mirror(s).
 * We can successfully endio the bio but should aव्योम the region being
 * marked clean by setting the state DM_RH_NOSYNC.
 *
 * This function is _not_ safe in पूर्णांकerrupt context!
 */
व्योम dm_rh_mark_nosync(काष्ठा dm_region_hash *rh, काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dm_dirty_log *log = rh->log;
	काष्ठा dm_region *reg;
	region_t region = dm_rh_bio_to_region(rh, bio);
	पूर्णांक recovering = 0;

	अगर (bio->bi_opf & REQ_PREFLUSH) अणु
		rh->flush_failure = 1;
		वापस;
	पूर्ण

	अगर (bio_op(bio) == REQ_OP_DISCARD)
		वापस;

	/* We must inक्रमm the log that the sync count has changed. */
	log->type->set_region_sync(log, region, 0);

	पढ़ो_lock(&rh->hash_lock);
	reg = __rh_find(rh, region);
	पढ़ो_unlock(&rh->hash_lock);

	/* region hash entry should exist because ग_लिखो was in-flight */
	BUG_ON(!reg);
	BUG_ON(!list_empty(&reg->list));

	spin_lock_irqsave(&rh->region_lock, flags);
	/*
	 * Possible हालs:
	 *   1) DM_RH_सूचीTY
	 *   2) DM_RH_NOSYNC: was dirty, other preceding ग_लिखोs failed
	 *   3) DM_RH_RECOVERING: flushing pending ग_लिखोs
	 * Either हाल, the region should have not been connected to list.
	 */
	recovering = (reg->state == DM_RH_RECOVERING);
	reg->state = DM_RH_NOSYNC;
	BUG_ON(!list_empty(&reg->list));
	spin_unlock_irqrestore(&rh->region_lock, flags);

	अगर (recovering)
		complete_resync_work(reg, 0);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_mark_nosync);

व्योम dm_rh_update_states(काष्ठा dm_region_hash *rh, पूर्णांक errors_handled)
अणु
	काष्ठा dm_region *reg, *next;

	LIST_HEAD(clean);
	LIST_HEAD(recovered);
	LIST_HEAD(failed_recovered);

	/*
	 * Quickly grab the lists.
	 */
	ग_लिखो_lock_irq(&rh->hash_lock);
	spin_lock(&rh->region_lock);
	अगर (!list_empty(&rh->clean_regions)) अणु
		list_splice_init(&rh->clean_regions, &clean);

		list_क्रम_each_entry(reg, &clean, list)
			list_del(&reg->hash_list);
	पूर्ण

	अगर (!list_empty(&rh->recovered_regions)) अणु
		list_splice_init(&rh->recovered_regions, &recovered);

		list_क्रम_each_entry(reg, &recovered, list)
			list_del(&reg->hash_list);
	पूर्ण

	अगर (!list_empty(&rh->failed_recovered_regions)) अणु
		list_splice_init(&rh->failed_recovered_regions,
				 &failed_recovered);

		list_क्रम_each_entry(reg, &failed_recovered, list)
			list_del(&reg->hash_list);
	पूर्ण

	spin_unlock(&rh->region_lock);
	ग_लिखो_unlock_irq(&rh->hash_lock);

	/*
	 * All the regions on the recovered and clean lists have
	 * now been pulled out of the प्रणाली, so no need to करो
	 * any more locking.
	 */
	list_क्रम_each_entry_safe(reg, next, &recovered, list) अणु
		rh->log->type->clear_region(rh->log, reg->key);
		complete_resync_work(reg, 1);
		mempool_मुक्त(reg, &rh->region_pool);
	पूर्ण

	list_क्रम_each_entry_safe(reg, next, &failed_recovered, list) अणु
		complete_resync_work(reg, errors_handled ? 0 : 1);
		mempool_मुक्त(reg, &rh->region_pool);
	पूर्ण

	list_क्रम_each_entry_safe(reg, next, &clean, list) अणु
		rh->log->type->clear_region(rh->log, reg->key);
		mempool_मुक्त(reg, &rh->region_pool);
	पूर्ण

	rh->log->type->flush(rh->log);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_update_states);

अटल व्योम rh_inc(काष्ठा dm_region_hash *rh, region_t region)
अणु
	काष्ठा dm_region *reg;

	पढ़ो_lock(&rh->hash_lock);
	reg = __rh_find(rh, region);

	spin_lock_irq(&rh->region_lock);
	atomic_inc(&reg->pending);

	अगर (reg->state == DM_RH_CLEAN) अणु
		reg->state = DM_RH_सूचीTY;
		list_del_init(&reg->list);	/* take off the clean list */
		spin_unlock_irq(&rh->region_lock);

		rh->log->type->mark_region(rh->log, reg->key);
	पूर्ण अन्यथा
		spin_unlock_irq(&rh->region_lock);


	पढ़ो_unlock(&rh->hash_lock);
पूर्ण

व्योम dm_rh_inc_pending(काष्ठा dm_region_hash *rh, काष्ठा bio_list *bios)
अणु
	काष्ठा bio *bio;

	क्रम (bio = bios->head; bio; bio = bio->bi_next) अणु
		अगर (bio->bi_opf & REQ_PREFLUSH || bio_op(bio) == REQ_OP_DISCARD)
			जारी;
		rh_inc(rh, dm_rh_bio_to_region(rh, bio));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_inc_pending);

व्योम dm_rh_dec(काष्ठा dm_region_hash *rh, region_t region)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dm_region *reg;
	पूर्णांक should_wake = 0;

	पढ़ो_lock(&rh->hash_lock);
	reg = __rh_lookup(rh, region);
	पढ़ो_unlock(&rh->hash_lock);

	spin_lock_irqsave(&rh->region_lock, flags);
	अगर (atomic_dec_and_test(&reg->pending)) अणु
		/*
		 * There is no pending I/O क्रम this region.
		 * We can move the region to corresponding list क्रम next action.
		 * At this poपूर्णांक, the region is not yet connected to any list.
		 *
		 * If the state is DM_RH_NOSYNC, the region should be kept off
		 * from clean list.
		 * The hash entry क्रम DM_RH_NOSYNC will reमुख्य in memory
		 * until the region is recovered or the map is reloaded.
		 */

		/* करो nothing क्रम DM_RH_NOSYNC */
		अगर (unlikely(rh->flush_failure)) अणु
			/*
			 * If a ग_लिखो flush failed some समय ago, we
			 * करोn't know whether or not this ग_लिखो made it
			 * to the disk, so we must resync the device.
			 */
			reg->state = DM_RH_NOSYNC;
		पूर्ण अन्यथा अगर (reg->state == DM_RH_RECOVERING) अणु
			list_add_tail(&reg->list, &rh->quiesced_regions);
		पूर्ण अन्यथा अगर (reg->state == DM_RH_सूचीTY) अणु
			reg->state = DM_RH_CLEAN;
			list_add(&reg->list, &rh->clean_regions);
		पूर्ण
		should_wake = 1;
	पूर्ण
	spin_unlock_irqrestore(&rh->region_lock, flags);

	अगर (should_wake)
		rh->wakeup_workers(rh->context);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_dec);

/*
 * Starts quiescing a region in preparation क्रम recovery.
 */
अटल पूर्णांक __rh_recovery_prepare(काष्ठा dm_region_hash *rh)
अणु
	पूर्णांक r;
	region_t region;
	काष्ठा dm_region *reg;

	/*
	 * Ask the dirty log what's next.
	 */
	r = rh->log->type->get_resync_work(rh->log, &region);
	अगर (r <= 0)
		वापस r;

	/*
	 * Get this region, and start it quiescing by setting the
	 * recovering flag.
	 */
	पढ़ो_lock(&rh->hash_lock);
	reg = __rh_find(rh, region);
	पढ़ो_unlock(&rh->hash_lock);

	spin_lock_irq(&rh->region_lock);
	reg->state = DM_RH_RECOVERING;

	/* Alपढ़ोy quiesced ? */
	अगर (atomic_पढ़ो(&reg->pending))
		list_del_init(&reg->list);
	अन्यथा
		list_move(&reg->list, &rh->quiesced_regions);

	spin_unlock_irq(&rh->region_lock);

	वापस 1;
पूर्ण

व्योम dm_rh_recovery_prepare(काष्ठा dm_region_hash *rh)
अणु
	/* Extra reference to aव्योम race with dm_rh_stop_recovery */
	atomic_inc(&rh->recovery_in_flight);

	जबतक (!करोwn_trylock(&rh->recovery_count)) अणु
		atomic_inc(&rh->recovery_in_flight);
		अगर (__rh_recovery_prepare(rh) <= 0) अणु
			atomic_dec(&rh->recovery_in_flight);
			up(&rh->recovery_count);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Drop the extra reference */
	अगर (atomic_dec_and_test(&rh->recovery_in_flight))
		rh->wakeup_all_recovery_रुकोers(rh->context);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_recovery_prepare);

/*
 * Returns any quiesced regions.
 */
काष्ठा dm_region *dm_rh_recovery_start(काष्ठा dm_region_hash *rh)
अणु
	काष्ठा dm_region *reg = शून्य;

	spin_lock_irq(&rh->region_lock);
	अगर (!list_empty(&rh->quiesced_regions)) अणु
		reg = list_entry(rh->quiesced_regions.next,
				 काष्ठा dm_region, list);
		list_del_init(&reg->list);  /* हटाओ from the quiesced list */
	पूर्ण
	spin_unlock_irq(&rh->region_lock);

	वापस reg;
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_recovery_start);

व्योम dm_rh_recovery_end(काष्ठा dm_region *reg, पूर्णांक success)
अणु
	काष्ठा dm_region_hash *rh = reg->rh;

	spin_lock_irq(&rh->region_lock);
	अगर (success)
		list_add(&reg->list, &reg->rh->recovered_regions);
	अन्यथा
		list_add(&reg->list, &reg->rh->failed_recovered_regions);

	spin_unlock_irq(&rh->region_lock);

	rh->wakeup_workers(rh->context);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_recovery_end);

/* Return recovery in flight count. */
पूर्णांक dm_rh_recovery_in_flight(काष्ठा dm_region_hash *rh)
अणु
	वापस atomic_पढ़ो(&rh->recovery_in_flight);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_recovery_in_flight);

पूर्णांक dm_rh_flush(काष्ठा dm_region_hash *rh)
अणु
	वापस rh->log->type->flush(rh->log);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_flush);

व्योम dm_rh_delay(काष्ठा dm_region_hash *rh, काष्ठा bio *bio)
अणु
	काष्ठा dm_region *reg;

	पढ़ो_lock(&rh->hash_lock);
	reg = __rh_find(rh, dm_rh_bio_to_region(rh, bio));
	bio_list_add(&reg->delayed_bios, bio);
	पढ़ो_unlock(&rh->hash_lock);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_delay);

व्योम dm_rh_stop_recovery(काष्ठा dm_region_hash *rh)
अणु
	पूर्णांक i;

	/* रुको क्रम any recovering regions */
	क्रम (i = 0; i < rh->max_recovery; i++)
		करोwn(&rh->recovery_count);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_stop_recovery);

व्योम dm_rh_start_recovery(काष्ठा dm_region_hash *rh)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rh->max_recovery; i++)
		up(&rh->recovery_count);

	rh->wakeup_workers(rh->context);
पूर्ण
EXPORT_SYMBOL_GPL(dm_rh_start_recovery);

MODULE_DESCRIPTION(DM_NAME " region hash");
MODULE_AUTHOR("Joe Thornber/Heinz Mauelshagen <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
