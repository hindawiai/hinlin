<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm.h"
#समावेश "dm-bio-prison-v2.h"
#समावेश "dm-bio-record.h"
#समावेश "dm-cache-metadata.h"

#समावेश <linux/dm-पन.स>
#समावेश <linux/dm-kcopyd.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/init.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#घोषणा DM_MSG_PREFIX "cache"

DECLARE_DM_KCOPYD_THROTTLE_WITH_MODULE_PARM(cache_copy_throttle,
	"A percentage of time allocated for copying to and/or from cache");

/*----------------------------------------------------------------*/

/*
 * Glossary:
 *
 * oblock: index of an origin block
 * cblock: index of a cache block
 * promotion: movement of a block from origin to cache
 * demotion: movement of a block from cache to origin
 * migration: movement of a block between the origin and cache device,
 *	      either direction
 */

/*----------------------------------------------------------------*/

काष्ठा io_tracker अणु
	spinlock_t lock;

	/*
	 * Sectors of in-flight IO.
	 */
	sector_t in_flight;

	/*
	 * The समय, in jअगरfies, when this device became idle (अगर it is
	 * indeed idle).
	 */
	अचिन्हित दीर्घ idle_समय;
	अचिन्हित दीर्घ last_update_समय;
पूर्ण;

अटल व्योम iot_init(काष्ठा io_tracker *iot)
अणु
	spin_lock_init(&iot->lock);
	iot->in_flight = 0ul;
	iot->idle_समय = 0ul;
	iot->last_update_समय = jअगरfies;
पूर्ण

अटल bool __iot_idle_क्रम(काष्ठा io_tracker *iot, अचिन्हित दीर्घ jअगरs)
अणु
	अगर (iot->in_flight)
		वापस false;

	वापस समय_after(jअगरfies, iot->idle_समय + jअगरs);
पूर्ण

अटल bool iot_idle_क्रम(काष्ठा io_tracker *iot, अचिन्हित दीर्घ jअगरs)
अणु
	bool r;

	spin_lock_irq(&iot->lock);
	r = __iot_idle_क्रम(iot, jअगरs);
	spin_unlock_irq(&iot->lock);

	वापस r;
पूर्ण

अटल व्योम iot_io_begin(काष्ठा io_tracker *iot, sector_t len)
अणु
	spin_lock_irq(&iot->lock);
	iot->in_flight += len;
	spin_unlock_irq(&iot->lock);
पूर्ण

अटल व्योम __iot_io_end(काष्ठा io_tracker *iot, sector_t len)
अणु
	अगर (!len)
		वापस;

	iot->in_flight -= len;
	अगर (!iot->in_flight)
		iot->idle_समय = jअगरfies;
पूर्ण

अटल व्योम iot_io_end(काष्ठा io_tracker *iot, sector_t len)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iot->lock, flags);
	__iot_io_end(iot, len);
	spin_unlock_irqrestore(&iot->lock, flags);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Represents a chunk of future work.  'input' allows continuations to pass
 * values between themselves, typically error values.
 */
काष्ठा continuation अणु
	काष्ठा work_काष्ठा ws;
	blk_status_t input;
पूर्ण;

अटल अंतरभूत व्योम init_continuation(काष्ठा continuation *k,
				     व्योम (*fn)(काष्ठा work_काष्ठा *))
अणु
	INIT_WORK(&k->ws, fn);
	k->input = 0;
पूर्ण

अटल अंतरभूत व्योम queue_continuation(काष्ठा workqueue_काष्ठा *wq,
				      काष्ठा continuation *k)
अणु
	queue_work(wq, &k->ws);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * The batcher collects together pieces of work that need a particular
 * operation to occur beक्रमe they can proceed (typically a commit).
 */
काष्ठा batcher अणु
	/*
	 * The operation that everyone is रुकोing क्रम.
	 */
	blk_status_t (*commit_op)(व्योम *context);
	व्योम *commit_context;

	/*
	 * This is how bios should be issued once the commit op is complete
	 * (accounted_request).
	 */
	व्योम (*issue_op)(काष्ठा bio *bio, व्योम *context);
	व्योम *issue_context;

	/*
	 * Queued work माला_लो put on here after commit.
	 */
	काष्ठा workqueue_काष्ठा *wq;

	spinlock_t lock;
	काष्ठा list_head work_items;
	काष्ठा bio_list bios;
	काष्ठा work_काष्ठा commit_work;

	bool commit_scheduled;
पूर्ण;

अटल व्योम __commit(काष्ठा work_काष्ठा *_ws)
अणु
	काष्ठा batcher *b = container_of(_ws, काष्ठा batcher, commit_work);
	blk_status_t r;
	काष्ठा list_head work_items;
	काष्ठा work_काष्ठा *ws, *पंचांगp;
	काष्ठा continuation *k;
	काष्ठा bio *bio;
	काष्ठा bio_list bios;

	INIT_LIST_HEAD(&work_items);
	bio_list_init(&bios);

	/*
	 * We have to grab these beक्रमe the commit_op to aव्योम a race
	 * condition.
	 */
	spin_lock_irq(&b->lock);
	list_splice_init(&b->work_items, &work_items);
	bio_list_merge(&bios, &b->bios);
	bio_list_init(&b->bios);
	b->commit_scheduled = false;
	spin_unlock_irq(&b->lock);

	r = b->commit_op(b->commit_context);

	list_क्रम_each_entry_safe(ws, पंचांगp, &work_items, entry) अणु
		k = container_of(ws, काष्ठा continuation, ws);
		k->input = r;
		INIT_LIST_HEAD(&ws->entry); /* to aव्योम a WARN_ON */
		queue_work(b->wq, ws);
	पूर्ण

	जबतक ((bio = bio_list_pop(&bios))) अणु
		अगर (r) अणु
			bio->bi_status = r;
			bio_endio(bio);
		पूर्ण अन्यथा
			b->issue_op(bio, b->issue_context);
	पूर्ण
पूर्ण

अटल व्योम batcher_init(काष्ठा batcher *b,
			 blk_status_t (*commit_op)(व्योम *),
			 व्योम *commit_context,
			 व्योम (*issue_op)(काष्ठा bio *bio, व्योम *),
			 व्योम *issue_context,
			 काष्ठा workqueue_काष्ठा *wq)
अणु
	b->commit_op = commit_op;
	b->commit_context = commit_context;
	b->issue_op = issue_op;
	b->issue_context = issue_context;
	b->wq = wq;

	spin_lock_init(&b->lock);
	INIT_LIST_HEAD(&b->work_items);
	bio_list_init(&b->bios);
	INIT_WORK(&b->commit_work, __commit);
	b->commit_scheduled = false;
पूर्ण

अटल व्योम async_commit(काष्ठा batcher *b)
अणु
	queue_work(b->wq, &b->commit_work);
पूर्ण

अटल व्योम जारी_after_commit(काष्ठा batcher *b, काष्ठा continuation *k)
अणु
	bool commit_scheduled;

	spin_lock_irq(&b->lock);
	commit_scheduled = b->commit_scheduled;
	list_add_tail(&k->ws.entry, &b->work_items);
	spin_unlock_irq(&b->lock);

	अगर (commit_scheduled)
		async_commit(b);
पूर्ण

/*
 * Bios are errored अगर commit failed.
 */
अटल व्योम issue_after_commit(काष्ठा batcher *b, काष्ठा bio *bio)
अणु
       bool commit_scheduled;

       spin_lock_irq(&b->lock);
       commit_scheduled = b->commit_scheduled;
       bio_list_add(&b->bios, bio);
       spin_unlock_irq(&b->lock);

       अगर (commit_scheduled)
	       async_commit(b);
पूर्ण

/*
 * Call this अगर some urgent work is रुकोing क्रम the commit to complete.
 */
अटल व्योम schedule_commit(काष्ठा batcher *b)
अणु
	bool immediate;

	spin_lock_irq(&b->lock);
	immediate = !list_empty(&b->work_items) || !bio_list_empty(&b->bios);
	b->commit_scheduled = true;
	spin_unlock_irq(&b->lock);

	अगर (immediate)
		async_commit(b);
पूर्ण

/*
 * There are a couple of places where we let a bio run, but want to करो some
 * work beक्रमe calling its endio function.  We करो this by temporarily
 * changing the endio fn.
 */
काष्ठा dm_hook_info अणु
	bio_end_io_t *bi_end_io;
पूर्ण;

अटल व्योम dm_hook_bio(काष्ठा dm_hook_info *h, काष्ठा bio *bio,
			bio_end_io_t *bi_end_io, व्योम *bi_निजी)
अणु
	h->bi_end_io = bio->bi_end_io;

	bio->bi_end_io = bi_end_io;
	bio->bi_निजी = bi_निजी;
पूर्ण

अटल व्योम dm_unhook_bio(काष्ठा dm_hook_info *h, काष्ठा bio *bio)
अणु
	bio->bi_end_io = h->bi_end_io;
पूर्ण

/*----------------------------------------------------------------*/

#घोषणा MIGRATION_POOL_SIZE 128
#घोषणा COMMIT_PERIOD HZ
#घोषणा MIGRATION_COUNT_WINDOW 10

/*
 * The block size of the device holding cache data must be
 * between 32KB and 1GB.
 */
#घोषणा DATA_DEV_BLOCK_SIZE_MIN_SECTORS (32 * 1024 >> SECTOR_SHIFT)
#घोषणा DATA_DEV_BLOCK_SIZE_MAX_SECTORS (1024 * 1024 * 1024 >> SECTOR_SHIFT)

क्रमागत cache_metadata_mode अणु
	CM_WRITE,		/* metadata may be changed */
	CM_READ_ONLY,		/* metadata may not be changed */
	CM_FAIL
पूर्ण;

क्रमागत cache_io_mode अणु
	/*
	 * Data is written to cached blocks only.  These blocks are marked
	 * dirty.  If you lose the cache device you will lose data.
	 * Potential perक्रमmance increase क्रम both पढ़ोs and ग_लिखोs.
	 */
	CM_IO_WRITEBACK,

	/*
	 * Data is written to both cache and origin.  Blocks are never
	 * dirty.  Potential perक्रमmance benfit क्रम पढ़ोs only.
	 */
	CM_IO_WRITETHROUGH,

	/*
	 * A degraded mode useful क्रम various cache coherency situations
	 * (eg, rolling back snapshots).  Reads and ग_लिखोs always go to the
	 * origin.  If a ग_लिखो goes to a cached oblock, then the cache
	 * block is invalidated.
	 */
	CM_IO_PASSTHROUGH
पूर्ण;

काष्ठा cache_features अणु
	क्रमागत cache_metadata_mode mode;
	क्रमागत cache_io_mode io_mode;
	अचिन्हित metadata_version;
	bool discard_passकरोwn:1;
पूर्ण;

काष्ठा cache_stats अणु
	atomic_t पढ़ो_hit;
	atomic_t पढ़ो_miss;
	atomic_t ग_लिखो_hit;
	atomic_t ग_लिखो_miss;
	atomic_t demotion;
	atomic_t promotion;
	atomic_t ग_लिखोback;
	atomic_t copies_aव्योमed;
	atomic_t cache_cell_clash;
	atomic_t commit_count;
	atomic_t discard_count;
पूर्ण;

काष्ठा cache अणु
	काष्ठा dm_target *ti;
	spinlock_t lock;

	/*
	 * Fields क्रम converting from sectors to blocks.
	 */
	पूर्णांक sectors_per_block_shअगरt;
	sector_t sectors_per_block;

	काष्ठा dm_cache_metadata *cmd;

	/*
	 * Metadata is written to this device.
	 */
	काष्ठा dm_dev *metadata_dev;

	/*
	 * The slower of the two data devices.  Typically a spindle.
	 */
	काष्ठा dm_dev *origin_dev;

	/*
	 * The faster of the two data devices.  Typically an SSD.
	 */
	काष्ठा dm_dev *cache_dev;

	/*
	 * Size of the origin device in _complete_ blocks and native sectors.
	 */
	dm_oblock_t origin_blocks;
	sector_t origin_sectors;

	/*
	 * Size of the cache device in blocks.
	 */
	dm_cblock_t cache_size;

	/*
	 * Invalidation fields.
	 */
	spinlock_t invalidation_lock;
	काष्ठा list_head invalidation_requests;

	sector_t migration_threshold;
	रुको_queue_head_t migration_रुको;
	atomic_t nr_allocated_migrations;

	/*
	 * The number of in flight migrations that are perक्रमming
	 * background io. eg, promotion, ग_लिखोback.
	 */
	atomic_t nr_io_migrations;

	काष्ठा bio_list deferred_bios;

	काष्ठा rw_semaphore quiesce_lock;

	/*
	 * origin_blocks entries, discarded अगर set.
	 */
	dm_dblock_t discard_nr_blocks;
	अचिन्हित दीर्घ *discard_bitset;
	uपूर्णांक32_t discard_block_size; /* a घातer of 2 बार sectors per block */

	/*
	 * Rather than reस्थिरructing the table line क्रम the status we just
	 * save it and regurgitate.
	 */
	अचिन्हित nr_ctr_args;
	स्थिर अक्षर **ctr_args;

	काष्ठा dm_kcopyd_client *copier;
	काष्ठा work_काष्ठा deferred_bio_worker;
	काष्ठा work_काष्ठा migration_worker;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा delayed_work waker;
	काष्ठा dm_bio_prison_v2 *prison;

	/*
	 * cache_size entries, dirty अगर set
	 */
	अचिन्हित दीर्घ *dirty_bitset;
	atomic_t nr_dirty;

	अचिन्हित policy_nr_args;
	काष्ठा dm_cache_policy *policy;

	/*
	 * Cache features such as ग_लिखो-through.
	 */
	काष्ठा cache_features features;

	काष्ठा cache_stats stats;

	bool need_tick_bio:1;
	bool sized:1;
	bool invalidate:1;
	bool commit_requested:1;
	bool loaded_mappings:1;
	bool loaded_discards:1;

	काष्ठा rw_semaphore background_work_lock;

	काष्ठा batcher committer;
	काष्ठा work_काष्ठा commit_ws;

	काष्ठा io_tracker tracker;

	mempool_t migration_pool;

	काष्ठा bio_set bs;
पूर्ण;

काष्ठा per_bio_data अणु
	bool tick:1;
	अचिन्हित req_nr:2;
	काष्ठा dm_bio_prison_cell_v2 *cell;
	काष्ठा dm_hook_info hook_info;
	sector_t len;
पूर्ण;

काष्ठा dm_cache_migration अणु
	काष्ठा continuation k;
	काष्ठा cache *cache;

	काष्ठा policy_work *op;
	काष्ठा bio *overग_लिखो_bio;
	काष्ठा dm_bio_prison_cell_v2 *cell;

	dm_cblock_t invalidate_cblock;
	dm_oblock_t invalidate_oblock;
पूर्ण;

/*----------------------------------------------------------------*/

अटल bool ग_लिखोthrough_mode(काष्ठा cache *cache)
अणु
	वापस cache->features.io_mode == CM_IO_WRITETHROUGH;
पूर्ण

अटल bool ग_लिखोback_mode(काष्ठा cache *cache)
अणु
	वापस cache->features.io_mode == CM_IO_WRITEBACK;
पूर्ण

अटल अंतरभूत bool passthrough_mode(काष्ठा cache *cache)
अणु
	वापस unlikely(cache->features.io_mode == CM_IO_PASSTHROUGH);
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम wake_deferred_bio_worker(काष्ठा cache *cache)
अणु
	queue_work(cache->wq, &cache->deferred_bio_worker);
पूर्ण

अटल व्योम wake_migration_worker(काष्ठा cache *cache)
अणु
	अगर (passthrough_mode(cache))
		वापस;

	queue_work(cache->wq, &cache->migration_worker);
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा dm_bio_prison_cell_v2 *alloc_prison_cell(काष्ठा cache *cache)
अणु
	वापस dm_bio_prison_alloc_cell_v2(cache->prison, GFP_NOIO);
पूर्ण

अटल व्योम मुक्त_prison_cell(काष्ठा cache *cache, काष्ठा dm_bio_prison_cell_v2 *cell)
अणु
	dm_bio_prison_मुक्त_cell_v2(cache->prison, cell);
पूर्ण

अटल काष्ठा dm_cache_migration *alloc_migration(काष्ठा cache *cache)
अणु
	काष्ठा dm_cache_migration *mg;

	mg = mempool_alloc(&cache->migration_pool, GFP_NOIO);

	स_रखो(mg, 0, माप(*mg));

	mg->cache = cache;
	atomic_inc(&cache->nr_allocated_migrations);

	वापस mg;
पूर्ण

अटल व्योम मुक्त_migration(काष्ठा dm_cache_migration *mg)
अणु
	काष्ठा cache *cache = mg->cache;

	अगर (atomic_dec_and_test(&cache->nr_allocated_migrations))
		wake_up(&cache->migration_रुको);

	mempool_मुक्त(mg, &cache->migration_pool);
पूर्ण

/*----------------------------------------------------------------*/

अटल अंतरभूत dm_oblock_t oblock_succ(dm_oblock_t b)
अणु
	वापस to_oblock(from_oblock(b) + 1ull);
पूर्ण

अटल व्योम build_key(dm_oblock_t begin, dm_oblock_t end, काष्ठा dm_cell_key_v2 *key)
अणु
	key->भव = 0;
	key->dev = 0;
	key->block_begin = from_oblock(begin);
	key->block_end = from_oblock(end);
पूर्ण

/*
 * We have two lock levels.  Level 0, which is used to prevent WRITEs, and
 * level 1 which prevents *both* READs and WRITEs.
 */
#घोषणा WRITE_LOCK_LEVEL 0
#घोषणा READ_WRITE_LOCK_LEVEL 1

अटल अचिन्हित lock_level(काष्ठा bio *bio)
अणु
	वापस bio_data_dir(bio) == WRITE ?
		WRITE_LOCK_LEVEL :
		READ_WRITE_LOCK_LEVEL;
पूर्ण

/*----------------------------------------------------------------
 * Per bio data
 *--------------------------------------------------------------*/

अटल काष्ठा per_bio_data *get_per_bio_data(काष्ठा bio *bio)
अणु
	काष्ठा per_bio_data *pb = dm_per_bio_data(bio, माप(काष्ठा per_bio_data));
	BUG_ON(!pb);
	वापस pb;
पूर्ण

अटल काष्ठा per_bio_data *init_per_bio_data(काष्ठा bio *bio)
अणु
	काष्ठा per_bio_data *pb = get_per_bio_data(bio);

	pb->tick = false;
	pb->req_nr = dm_bio_get_target_bio_nr(bio);
	pb->cell = शून्य;
	pb->len = 0;

	वापस pb;
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम defer_bio(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	spin_lock_irq(&cache->lock);
	bio_list_add(&cache->deferred_bios, bio);
	spin_unlock_irq(&cache->lock);

	wake_deferred_bio_worker(cache);
पूर्ण

अटल व्योम defer_bios(काष्ठा cache *cache, काष्ठा bio_list *bios)
अणु
	spin_lock_irq(&cache->lock);
	bio_list_merge(&cache->deferred_bios, bios);
	bio_list_init(bios);
	spin_unlock_irq(&cache->lock);

	wake_deferred_bio_worker(cache);
पूर्ण

/*----------------------------------------------------------------*/

अटल bool bio_detain_shared(काष्ठा cache *cache, dm_oblock_t oblock, काष्ठा bio *bio)
अणु
	bool r;
	काष्ठा per_bio_data *pb;
	काष्ठा dm_cell_key_v2 key;
	dm_oblock_t end = to_oblock(from_oblock(oblock) + 1ULL);
	काष्ठा dm_bio_prison_cell_v2 *cell_pपुनः_स्मृति, *cell;

	cell_pपुनः_स्मृति = alloc_prison_cell(cache); /* FIXME: allow रुको अगर calling from worker */

	build_key(oblock, end, &key);
	r = dm_cell_get_v2(cache->prison, &key, lock_level(bio), bio, cell_pपुनः_स्मृति, &cell);
	अगर (!r) अणु
		/*
		 * Failed to get the lock.
		 */
		मुक्त_prison_cell(cache, cell_pपुनः_स्मृति);
		वापस r;
	पूर्ण

	अगर (cell != cell_pपुनः_स्मृति)
		मुक्त_prison_cell(cache, cell_pपुनः_स्मृति);

	pb = get_per_bio_data(bio);
	pb->cell = cell;

	वापस r;
पूर्ण

/*----------------------------------------------------------------*/

अटल bool is_dirty(काष्ठा cache *cache, dm_cblock_t b)
अणु
	वापस test_bit(from_cblock(b), cache->dirty_bitset);
पूर्ण

अटल व्योम set_dirty(काष्ठा cache *cache, dm_cblock_t cblock)
अणु
	अगर (!test_and_set_bit(from_cblock(cblock), cache->dirty_bitset)) अणु
		atomic_inc(&cache->nr_dirty);
		policy_set_dirty(cache->policy, cblock);
	पूर्ण
पूर्ण

/*
 * These two are called when setting after migrations to क्रमce the policy
 * and dirty bitset to be in sync.
 */
अटल व्योम क्रमce_set_dirty(काष्ठा cache *cache, dm_cblock_t cblock)
अणु
	अगर (!test_and_set_bit(from_cblock(cblock), cache->dirty_bitset))
		atomic_inc(&cache->nr_dirty);
	policy_set_dirty(cache->policy, cblock);
पूर्ण

अटल व्योम क्रमce_clear_dirty(काष्ठा cache *cache, dm_cblock_t cblock)
अणु
	अगर (test_and_clear_bit(from_cblock(cblock), cache->dirty_bitset)) अणु
		अगर (atomic_dec_वापस(&cache->nr_dirty) == 0)
			dm_table_event(cache->ti->table);
	पूर्ण

	policy_clear_dirty(cache->policy, cblock);
पूर्ण

/*----------------------------------------------------------------*/

अटल bool block_size_is_घातer_of_two(काष्ठा cache *cache)
अणु
	वापस cache->sectors_per_block_shअगरt >= 0;
पूर्ण

अटल dm_block_t block_भाग(dm_block_t b, uपूर्णांक32_t n)
अणु
	करो_भाग(b, n);

	वापस b;
पूर्ण

अटल dm_block_t oblocks_per_dblock(काष्ठा cache *cache)
अणु
	dm_block_t oblocks = cache->discard_block_size;

	अगर (block_size_is_घातer_of_two(cache))
		oblocks >>= cache->sectors_per_block_shअगरt;
	अन्यथा
		oblocks = block_भाग(oblocks, cache->sectors_per_block);

	वापस oblocks;
पूर्ण

अटल dm_dblock_t oblock_to_dblock(काष्ठा cache *cache, dm_oblock_t oblock)
अणु
	वापस to_dblock(block_भाग(from_oblock(oblock),
				   oblocks_per_dblock(cache)));
पूर्ण

अटल व्योम set_discard(काष्ठा cache *cache, dm_dblock_t b)
अणु
	BUG_ON(from_dblock(b) >= from_dblock(cache->discard_nr_blocks));
	atomic_inc(&cache->stats.discard_count);

	spin_lock_irq(&cache->lock);
	set_bit(from_dblock(b), cache->discard_bitset);
	spin_unlock_irq(&cache->lock);
पूर्ण

अटल व्योम clear_discard(काष्ठा cache *cache, dm_dblock_t b)
अणु
	spin_lock_irq(&cache->lock);
	clear_bit(from_dblock(b), cache->discard_bitset);
	spin_unlock_irq(&cache->lock);
पूर्ण

अटल bool is_discarded(काष्ठा cache *cache, dm_dblock_t b)
अणु
	पूर्णांक r;
	spin_lock_irq(&cache->lock);
	r = test_bit(from_dblock(b), cache->discard_bitset);
	spin_unlock_irq(&cache->lock);

	वापस r;
पूर्ण

अटल bool is_discarded_oblock(काष्ठा cache *cache, dm_oblock_t b)
अणु
	पूर्णांक r;
	spin_lock_irq(&cache->lock);
	r = test_bit(from_dblock(oblock_to_dblock(cache, b)),
		     cache->discard_bitset);
	spin_unlock_irq(&cache->lock);

	वापस r;
पूर्ण

/*----------------------------------------------------------------
 * Remapping
 *--------------------------------------------------------------*/
अटल व्योम remap_to_origin(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	bio_set_dev(bio, cache->origin_dev->bdev);
पूर्ण

अटल व्योम remap_to_cache(काष्ठा cache *cache, काष्ठा bio *bio,
			   dm_cblock_t cblock)
अणु
	sector_t bi_sector = bio->bi_iter.bi_sector;
	sector_t block = from_cblock(cblock);

	bio_set_dev(bio, cache->cache_dev->bdev);
	अगर (!block_size_is_घातer_of_two(cache))
		bio->bi_iter.bi_sector =
			(block * cache->sectors_per_block) +
			sector_भाग(bi_sector, cache->sectors_per_block);
	अन्यथा
		bio->bi_iter.bi_sector =
			(block << cache->sectors_per_block_shअगरt) |
			(bi_sector & (cache->sectors_per_block - 1));
पूर्ण

अटल व्योम check_अगर_tick_bio_needed(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	काष्ठा per_bio_data *pb;

	spin_lock_irq(&cache->lock);
	अगर (cache->need_tick_bio && !op_is_flush(bio->bi_opf) &&
	    bio_op(bio) != REQ_OP_DISCARD) अणु
		pb = get_per_bio_data(bio);
		pb->tick = true;
		cache->need_tick_bio = false;
	पूर्ण
	spin_unlock_irq(&cache->lock);
पूर्ण

अटल व्योम __remap_to_origin_clear_discard(काष्ठा cache *cache, काष्ठा bio *bio,
					    dm_oblock_t oblock, bool bio_has_pbd)
अणु
	अगर (bio_has_pbd)
		check_अगर_tick_bio_needed(cache, bio);
	remap_to_origin(cache, bio);
	अगर (bio_data_dir(bio) == WRITE)
		clear_discard(cache, oblock_to_dblock(cache, oblock));
पूर्ण

अटल व्योम remap_to_origin_clear_discard(काष्ठा cache *cache, काष्ठा bio *bio,
					  dm_oblock_t oblock)
अणु
	// FIXME: check_अगर_tick_bio_needed() is called way too much through this पूर्णांकerface
	__remap_to_origin_clear_discard(cache, bio, oblock, true);
पूर्ण

अटल व्योम remap_to_cache_dirty(काष्ठा cache *cache, काष्ठा bio *bio,
				 dm_oblock_t oblock, dm_cblock_t cblock)
अणु
	check_अगर_tick_bio_needed(cache, bio);
	remap_to_cache(cache, bio, cblock);
	अगर (bio_data_dir(bio) == WRITE) अणु
		set_dirty(cache, cblock);
		clear_discard(cache, oblock_to_dblock(cache, oblock));
	पूर्ण
पूर्ण

अटल dm_oblock_t get_bio_block(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	sector_t block_nr = bio->bi_iter.bi_sector;

	अगर (!block_size_is_घातer_of_two(cache))
		(व्योम) sector_भाग(block_nr, cache->sectors_per_block);
	अन्यथा
		block_nr >>= cache->sectors_per_block_shअगरt;

	वापस to_oblock(block_nr);
पूर्ण

अटल bool accountable_bio(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	वापस bio_op(bio) != REQ_OP_DISCARD;
पूर्ण

अटल व्योम accounted_begin(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	काष्ठा per_bio_data *pb;

	अगर (accountable_bio(cache, bio)) अणु
		pb = get_per_bio_data(bio);
		pb->len = bio_sectors(bio);
		iot_io_begin(&cache->tracker, pb->len);
	पूर्ण
पूर्ण

अटल व्योम accounted_complete(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	काष्ठा per_bio_data *pb = get_per_bio_data(bio);

	iot_io_end(&cache->tracker, pb->len);
पूर्ण

अटल व्योम accounted_request(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	accounted_begin(cache, bio);
	submit_bio_noacct(bio);
पूर्ण

अटल व्योम issue_op(काष्ठा bio *bio, व्योम *context)
अणु
	काष्ठा cache *cache = context;
	accounted_request(cache, bio);
पूर्ण

/*
 * When running in ग_लिखोthrough mode we need to send ग_लिखोs to clean blocks
 * to both the cache and origin devices.  Clone the bio and send them in parallel.
 */
अटल व्योम remap_to_origin_and_cache(काष्ठा cache *cache, काष्ठा bio *bio,
				      dm_oblock_t oblock, dm_cblock_t cblock)
अणु
	काष्ठा bio *origin_bio = bio_clone_fast(bio, GFP_NOIO, &cache->bs);

	BUG_ON(!origin_bio);

	bio_chain(origin_bio, bio);
	/*
	 * Passing false to __remap_to_origin_clear_discard() skips
	 * all code that might use per_bio_data (since clone करोesn't have it)
	 */
	__remap_to_origin_clear_discard(cache, origin_bio, oblock, false);
	submit_bio(origin_bio);

	remap_to_cache(cache, bio, cblock);
पूर्ण

/*----------------------------------------------------------------
 * Failure modes
 *--------------------------------------------------------------*/
अटल क्रमागत cache_metadata_mode get_cache_mode(काष्ठा cache *cache)
अणु
	वापस cache->features.mode;
पूर्ण

अटल स्थिर अक्षर *cache_device_name(काष्ठा cache *cache)
अणु
	वापस dm_table_device_name(cache->ti->table);
पूर्ण

अटल व्योम notअगरy_mode_चयन(काष्ठा cache *cache, क्रमागत cache_metadata_mode mode)
अणु
	स्थिर अक्षर *descs[] = अणु
		"write",
		"read-only",
		"fail"
	पूर्ण;

	dm_table_event(cache->ti->table);
	DMINFO("%s: switching cache to %s mode",
	       cache_device_name(cache), descs[(पूर्णांक)mode]);
पूर्ण

अटल व्योम set_cache_mode(काष्ठा cache *cache, क्रमागत cache_metadata_mode new_mode)
अणु
	bool needs_check;
	क्रमागत cache_metadata_mode old_mode = get_cache_mode(cache);

	अगर (dm_cache_metadata_needs_check(cache->cmd, &needs_check)) अणु
		DMERR("%s: unable to read needs_check flag, setting failure mode.",
		      cache_device_name(cache));
		new_mode = CM_FAIL;
	पूर्ण

	अगर (new_mode == CM_WRITE && needs_check) अणु
		DMERR("%s: unable to switch cache to write mode until repaired.",
		      cache_device_name(cache));
		अगर (old_mode != new_mode)
			new_mode = old_mode;
		अन्यथा
			new_mode = CM_READ_ONLY;
	पूर्ण

	/* Never move out of fail mode */
	अगर (old_mode == CM_FAIL)
		new_mode = CM_FAIL;

	चयन (new_mode) अणु
	हाल CM_FAIL:
	हाल CM_READ_ONLY:
		dm_cache_metadata_set_पढ़ो_only(cache->cmd);
		अवरोध;

	हाल CM_WRITE:
		dm_cache_metadata_set_पढ़ो_ग_लिखो(cache->cmd);
		अवरोध;
	पूर्ण

	cache->features.mode = new_mode;

	अगर (new_mode != old_mode)
		notअगरy_mode_चयन(cache, new_mode);
पूर्ण

अटल व्योम पात_transaction(काष्ठा cache *cache)
अणु
	स्थिर अक्षर *dev_name = cache_device_name(cache);

	अगर (get_cache_mode(cache) >= CM_READ_ONLY)
		वापस;

	अगर (dm_cache_metadata_set_needs_check(cache->cmd)) अणु
		DMERR("%s: failed to set 'needs_check' flag in metadata", dev_name);
		set_cache_mode(cache, CM_FAIL);
	पूर्ण

	DMERR_LIMIT("%s: aborting current metadata transaction", dev_name);
	अगर (dm_cache_metadata_पात(cache->cmd)) अणु
		DMERR("%s: failed to abort metadata transaction", dev_name);
		set_cache_mode(cache, CM_FAIL);
	पूर्ण
पूर्ण

अटल व्योम metadata_operation_failed(काष्ठा cache *cache, स्थिर अक्षर *op, पूर्णांक r)
अणु
	DMERR_LIMIT("%s: metadata operation '%s' failed: error = %d",
		    cache_device_name(cache), op, r);
	पात_transaction(cache);
	set_cache_mode(cache, CM_READ_ONLY);
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम load_stats(काष्ठा cache *cache)
अणु
	काष्ठा dm_cache_statistics stats;

	dm_cache_metadata_get_stats(cache->cmd, &stats);
	atomic_set(&cache->stats.पढ़ो_hit, stats.पढ़ो_hits);
	atomic_set(&cache->stats.पढ़ो_miss, stats.पढ़ो_misses);
	atomic_set(&cache->stats.ग_लिखो_hit, stats.ग_लिखो_hits);
	atomic_set(&cache->stats.ग_लिखो_miss, stats.ग_लिखो_misses);
पूर्ण

अटल व्योम save_stats(काष्ठा cache *cache)
अणु
	काष्ठा dm_cache_statistics stats;

	अगर (get_cache_mode(cache) >= CM_READ_ONLY)
		वापस;

	stats.पढ़ो_hits = atomic_पढ़ो(&cache->stats.पढ़ो_hit);
	stats.पढ़ो_misses = atomic_पढ़ो(&cache->stats.पढ़ो_miss);
	stats.ग_लिखो_hits = atomic_पढ़ो(&cache->stats.ग_लिखो_hit);
	stats.ग_लिखो_misses = atomic_पढ़ो(&cache->stats.ग_लिखो_miss);

	dm_cache_metadata_set_stats(cache->cmd, &stats);
पूर्ण

अटल व्योम update_stats(काष्ठा cache_stats *stats, क्रमागत policy_operation op)
अणु
	चयन (op) अणु
	हाल POLICY_PROMOTE:
		atomic_inc(&stats->promotion);
		अवरोध;

	हाल POLICY_DEMOTE:
		atomic_inc(&stats->demotion);
		अवरोध;

	हाल POLICY_WRITEBACK:
		atomic_inc(&stats->ग_लिखोback);
		अवरोध;
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * Migration processing
 *
 * Migration covers moving data from the origin device to the cache, or
 * vice versa.
 *--------------------------------------------------------------*/

अटल व्योम inc_io_migrations(काष्ठा cache *cache)
अणु
	atomic_inc(&cache->nr_io_migrations);
पूर्ण

अटल व्योम dec_io_migrations(काष्ठा cache *cache)
अणु
	atomic_dec(&cache->nr_io_migrations);
पूर्ण

अटल bool discard_or_flush(काष्ठा bio *bio)
अणु
	वापस bio_op(bio) == REQ_OP_DISCARD || op_is_flush(bio->bi_opf);
पूर्ण

अटल व्योम calc_discard_block_range(काष्ठा cache *cache, काष्ठा bio *bio,
				     dm_dblock_t *b, dm_dblock_t *e)
अणु
	sector_t sb = bio->bi_iter.bi_sector;
	sector_t se = bio_end_sector(bio);

	*b = to_dblock(dm_sector_भाग_up(sb, cache->discard_block_size));

	अगर (se - sb < cache->discard_block_size)
		*e = *b;
	अन्यथा
		*e = to_dblock(block_भाग(se, cache->discard_block_size));
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम prevent_background_work(काष्ठा cache *cache)
अणु
	lockdep_off();
	करोwn_ग_लिखो(&cache->background_work_lock);
	lockdep_on();
पूर्ण

अटल व्योम allow_background_work(काष्ठा cache *cache)
अणु
	lockdep_off();
	up_ग_लिखो(&cache->background_work_lock);
	lockdep_on();
पूर्ण

अटल bool background_work_begin(काष्ठा cache *cache)
अणु
	bool r;

	lockdep_off();
	r = करोwn_पढ़ो_trylock(&cache->background_work_lock);
	lockdep_on();

	वापस r;
पूर्ण

अटल व्योम background_work_end(काष्ठा cache *cache)
अणु
	lockdep_off();
	up_पढ़ो(&cache->background_work_lock);
	lockdep_on();
पूर्ण

/*----------------------------------------------------------------*/

अटल bool bio_ग_लिखोs_complete_block(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	वापस (bio_data_dir(bio) == WRITE) &&
		(bio->bi_iter.bi_size == (cache->sectors_per_block << SECTOR_SHIFT));
पूर्ण

अटल bool optimisable_bio(काष्ठा cache *cache, काष्ठा bio *bio, dm_oblock_t block)
अणु
	वापस ग_लिखोback_mode(cache) &&
		(is_discarded_oblock(cache, block) || bio_ग_लिखोs_complete_block(cache, bio));
पूर्ण

अटल व्योम quiesce(काष्ठा dm_cache_migration *mg,
		    व्योम (*continuation)(काष्ठा work_काष्ठा *))
अणु
	init_continuation(&mg->k, continuation);
	dm_cell_quiesce_v2(mg->cache->prison, mg->cell, &mg->k.ws);
पूर्ण

अटल काष्ठा dm_cache_migration *ws_to_mg(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा continuation *k = container_of(ws, काष्ठा continuation, ws);
	वापस container_of(k, काष्ठा dm_cache_migration, k);
पूर्ण

अटल व्योम copy_complete(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err, व्योम *context)
अणु
	काष्ठा dm_cache_migration *mg = container_of(context, काष्ठा dm_cache_migration, k);

	अगर (पढ़ो_err || ग_लिखो_err)
		mg->k.input = BLK_STS_IOERR;

	queue_continuation(mg->cache->wq, &mg->k);
पूर्ण

अटल व्योम copy(काष्ठा dm_cache_migration *mg, bool promote)
अणु
	काष्ठा dm_io_region o_region, c_region;
	काष्ठा cache *cache = mg->cache;

	o_region.bdev = cache->origin_dev->bdev;
	o_region.sector = from_oblock(mg->op->oblock) * cache->sectors_per_block;
	o_region.count = cache->sectors_per_block;

	c_region.bdev = cache->cache_dev->bdev;
	c_region.sector = from_cblock(mg->op->cblock) * cache->sectors_per_block;
	c_region.count = cache->sectors_per_block;

	अगर (promote)
		dm_kcopyd_copy(cache->copier, &o_region, 1, &c_region, 0, copy_complete, &mg->k);
	अन्यथा
		dm_kcopyd_copy(cache->copier, &c_region, 1, &o_region, 0, copy_complete, &mg->k);
पूर्ण

अटल व्योम bio_drop_shared_lock(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	काष्ठा per_bio_data *pb = get_per_bio_data(bio);

	अगर (pb->cell && dm_cell_put_v2(cache->prison, pb->cell))
		मुक्त_prison_cell(cache, pb->cell);
	pb->cell = शून्य;
पूर्ण

अटल व्योम overग_लिखो_endio(काष्ठा bio *bio)
अणु
	काष्ठा dm_cache_migration *mg = bio->bi_निजी;
	काष्ठा cache *cache = mg->cache;
	काष्ठा per_bio_data *pb = get_per_bio_data(bio);

	dm_unhook_bio(&pb->hook_info, bio);

	अगर (bio->bi_status)
		mg->k.input = bio->bi_status;

	queue_continuation(cache->wq, &mg->k);
पूर्ण

अटल व्योम overग_लिखो(काष्ठा dm_cache_migration *mg,
		      व्योम (*continuation)(काष्ठा work_काष्ठा *))
अणु
	काष्ठा bio *bio = mg->overग_लिखो_bio;
	काष्ठा per_bio_data *pb = get_per_bio_data(bio);

	dm_hook_bio(&pb->hook_info, bio, overग_लिखो_endio, mg);

	/*
	 * The overग_लिखो bio is part of the copy operation, as such it करोes
	 * not set/clear discard or dirty flags.
	 */
	अगर (mg->op->op == POLICY_PROMOTE)
		remap_to_cache(mg->cache, bio, mg->op->cblock);
	अन्यथा
		remap_to_origin(mg->cache, bio);

	init_continuation(&mg->k, continuation);
	accounted_request(mg->cache, bio);
पूर्ण

/*
 * Migration steps:
 *
 * 1) exclusive lock preventing WRITEs
 * 2) quiesce
 * 3) copy or issue overग_लिखो bio
 * 4) upgrade to exclusive lock preventing READs and WRITEs
 * 5) quiesce
 * 6) update metadata and commit
 * 7) unlock
 */
अटल व्योम mg_complete(काष्ठा dm_cache_migration *mg, bool success)
अणु
	काष्ठा bio_list bios;
	काष्ठा cache *cache = mg->cache;
	काष्ठा policy_work *op = mg->op;
	dm_cblock_t cblock = op->cblock;

	अगर (success)
		update_stats(&cache->stats, op->op);

	चयन (op->op) अणु
	हाल POLICY_PROMOTE:
		clear_discard(cache, oblock_to_dblock(cache, op->oblock));
		policy_complete_background_work(cache->policy, op, success);

		अगर (mg->overग_लिखो_bio) अणु
			अगर (success)
				क्रमce_set_dirty(cache, cblock);
			अन्यथा अगर (mg->k.input)
				mg->overग_लिखो_bio->bi_status = mg->k.input;
			अन्यथा
				mg->overग_लिखो_bio->bi_status = BLK_STS_IOERR;
			bio_endio(mg->overग_लिखो_bio);
		पूर्ण अन्यथा अणु
			अगर (success)
				क्रमce_clear_dirty(cache, cblock);
			dec_io_migrations(cache);
		पूर्ण
		अवरोध;

	हाल POLICY_DEMOTE:
		/*
		 * We clear dirty here to update the nr_dirty counter.
		 */
		अगर (success)
			क्रमce_clear_dirty(cache, cblock);
		policy_complete_background_work(cache->policy, op, success);
		dec_io_migrations(cache);
		अवरोध;

	हाल POLICY_WRITEBACK:
		अगर (success)
			क्रमce_clear_dirty(cache, cblock);
		policy_complete_background_work(cache->policy, op, success);
		dec_io_migrations(cache);
		अवरोध;
	पूर्ण

	bio_list_init(&bios);
	अगर (mg->cell) अणु
		अगर (dm_cell_unlock_v2(cache->prison, mg->cell, &bios))
			मुक्त_prison_cell(cache, mg->cell);
	पूर्ण

	मुक्त_migration(mg);
	defer_bios(cache, &bios);
	wake_migration_worker(cache);

	background_work_end(cache);
पूर्ण

अटल व्योम mg_success(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा dm_cache_migration *mg = ws_to_mg(ws);
	mg_complete(mg, mg->k.input == 0);
पूर्ण

अटल व्योम mg_update_metadata(काष्ठा work_काष्ठा *ws)
अणु
	पूर्णांक r;
	काष्ठा dm_cache_migration *mg = ws_to_mg(ws);
	काष्ठा cache *cache = mg->cache;
	काष्ठा policy_work *op = mg->op;

	चयन (op->op) अणु
	हाल POLICY_PROMOTE:
		r = dm_cache_insert_mapping(cache->cmd, op->cblock, op->oblock);
		अगर (r) अणु
			DMERR_LIMIT("%s: migration failed; couldn't insert mapping",
				    cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_insert_mapping", r);

			mg_complete(mg, false);
			वापस;
		पूर्ण
		mg_complete(mg, true);
		अवरोध;

	हाल POLICY_DEMOTE:
		r = dm_cache_हटाओ_mapping(cache->cmd, op->cblock);
		अगर (r) अणु
			DMERR_LIMIT("%s: migration failed; couldn't update on disk metadata",
				    cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_remove_mapping", r);

			mg_complete(mg, false);
			वापस;
		पूर्ण

		/*
		 * It would be nice अगर we only had to commit when a REQ_FLUSH
		 * comes through.  But there's one scenario that we have to
		 * look out क्रम:
		 *
		 * - vblock x in a cache block
		 * - करोmotion occurs
		 * - cache block माला_लो पुनः_स्मृतिated and over written
		 * - crash
		 *
		 * When we recover, because there was no commit the cache will
		 * rollback to having the data क्रम vblock x in the cache block.
		 * But the cache block has since been overwritten, so it'll end
		 * up poपूर्णांकing to data that was never in 'x' during the history
		 * of the device.
		 *
		 * To aव्योम this issue we require a commit as part of the
		 * demotion operation.
		 */
		init_continuation(&mg->k, mg_success);
		जारी_after_commit(&cache->committer, &mg->k);
		schedule_commit(&cache->committer);
		अवरोध;

	हाल POLICY_WRITEBACK:
		mg_complete(mg, true);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mg_update_metadata_after_copy(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा dm_cache_migration *mg = ws_to_mg(ws);

	/*
	 * Did the copy succeed?
	 */
	अगर (mg->k.input)
		mg_complete(mg, false);
	अन्यथा
		mg_update_metadata(ws);
पूर्ण

अटल व्योम mg_upgrade_lock(काष्ठा work_काष्ठा *ws)
अणु
	पूर्णांक r;
	काष्ठा dm_cache_migration *mg = ws_to_mg(ws);

	/*
	 * Did the copy succeed?
	 */
	अगर (mg->k.input)
		mg_complete(mg, false);

	अन्यथा अणु
		/*
		 * Now we want the lock to prevent both पढ़ोs and ग_लिखोs.
		 */
		r = dm_cell_lock_promote_v2(mg->cache->prison, mg->cell,
					    READ_WRITE_LOCK_LEVEL);
		अगर (r < 0)
			mg_complete(mg, false);

		अन्यथा अगर (r)
			quiesce(mg, mg_update_metadata);

		अन्यथा
			mg_update_metadata(ws);
	पूर्ण
पूर्ण

अटल व्योम mg_full_copy(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा dm_cache_migration *mg = ws_to_mg(ws);
	काष्ठा cache *cache = mg->cache;
	काष्ठा policy_work *op = mg->op;
	bool is_policy_promote = (op->op == POLICY_PROMOTE);

	अगर ((!is_policy_promote && !is_dirty(cache, op->cblock)) ||
	    is_discarded_oblock(cache, op->oblock)) अणु
		mg_upgrade_lock(ws);
		वापस;
	पूर्ण

	init_continuation(&mg->k, mg_upgrade_lock);
	copy(mg, is_policy_promote);
पूर्ण

अटल व्योम mg_copy(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा dm_cache_migration *mg = ws_to_mg(ws);

	अगर (mg->overग_लिखो_bio) अणु
		/*
		 * No exclusive lock was held when we last checked अगर the bio
		 * was optimisable.  So we have to check again in हाल things
		 * have changed (eg, the block may no दीर्घer be discarded).
		 */
		अगर (!optimisable_bio(mg->cache, mg->overग_लिखो_bio, mg->op->oblock)) अणु
			/*
			 * Fallback to a real full copy after करोing some tidying up.
			 */
			bool rb = bio_detain_shared(mg->cache, mg->op->oblock, mg->overग_लिखो_bio);
			BUG_ON(rb); /* An exclussive lock must _not_ be held क्रम this block */
			mg->overग_लिखो_bio = शून्य;
			inc_io_migrations(mg->cache);
			mg_full_copy(ws);
			वापस;
		पूर्ण

		/*
		 * It's safe to do this here, even though it's new data
		 * because all IO has been locked out of the block.
		 *
		 * mg_lock_ग_लिखोs() alपढ़ोy took READ_WRITE_LOCK_LEVEL
		 * so _not_ using mg_upgrade_lock() as continutation.
		 */
		overग_लिखो(mg, mg_update_metadata_after_copy);

	पूर्ण अन्यथा
		mg_full_copy(ws);
पूर्ण

अटल पूर्णांक mg_lock_ग_लिखोs(काष्ठा dm_cache_migration *mg)
अणु
	पूर्णांक r;
	काष्ठा dm_cell_key_v2 key;
	काष्ठा cache *cache = mg->cache;
	काष्ठा dm_bio_prison_cell_v2 *pपुनः_स्मृति;

	pपुनः_स्मृति = alloc_prison_cell(cache);

	/*
	 * Prevent ग_लिखोs to the block, but allow पढ़ोs to जारी.
	 * Unless we're using an overग_लिखो bio, in which हाल we lock
	 * everything.
	 */
	build_key(mg->op->oblock, oblock_succ(mg->op->oblock), &key);
	r = dm_cell_lock_v2(cache->prison, &key,
			    mg->overग_लिखो_bio ?  READ_WRITE_LOCK_LEVEL : WRITE_LOCK_LEVEL,
			    pपुनः_स्मृति, &mg->cell);
	अगर (r < 0) अणु
		मुक्त_prison_cell(cache, pपुनः_स्मृति);
		mg_complete(mg, false);
		वापस r;
	पूर्ण

	अगर (mg->cell != pपुनः_स्मृति)
		मुक्त_prison_cell(cache, pपुनः_स्मृति);

	अगर (r == 0)
		mg_copy(&mg->k.ws);
	अन्यथा
		quiesce(mg, mg_copy);

	वापस 0;
पूर्ण

अटल पूर्णांक mg_start(काष्ठा cache *cache, काष्ठा policy_work *op, काष्ठा bio *bio)
अणु
	काष्ठा dm_cache_migration *mg;

	अगर (!background_work_begin(cache)) अणु
		policy_complete_background_work(cache->policy, op, false);
		वापस -EPERM;
	पूर्ण

	mg = alloc_migration(cache);

	mg->op = op;
	mg->overग_लिखो_bio = bio;

	अगर (!bio)
		inc_io_migrations(cache);

	वापस mg_lock_ग_लिखोs(mg);
पूर्ण

/*----------------------------------------------------------------
 * invalidation processing
 *--------------------------------------------------------------*/

अटल व्योम invalidate_complete(काष्ठा dm_cache_migration *mg, bool success)
अणु
	काष्ठा bio_list bios;
	काष्ठा cache *cache = mg->cache;

	bio_list_init(&bios);
	अगर (dm_cell_unlock_v2(cache->prison, mg->cell, &bios))
		मुक्त_prison_cell(cache, mg->cell);

	अगर (!success && mg->overग_लिखो_bio)
		bio_io_error(mg->overग_लिखो_bio);

	मुक्त_migration(mg);
	defer_bios(cache, &bios);

	background_work_end(cache);
पूर्ण

अटल व्योम invalidate_completed(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा dm_cache_migration *mg = ws_to_mg(ws);
	invalidate_complete(mg, !mg->k.input);
पूर्ण

अटल पूर्णांक invalidate_cblock(काष्ठा cache *cache, dm_cblock_t cblock)
अणु
	पूर्णांक r = policy_invalidate_mapping(cache->policy, cblock);
	अगर (!r) अणु
		r = dm_cache_हटाओ_mapping(cache->cmd, cblock);
		अगर (r) अणु
			DMERR_LIMIT("%s: invalidation failed; couldn't update on disk metadata",
				    cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_remove_mapping", r);
		पूर्ण

	पूर्ण अन्यथा अगर (r == -ENODATA) अणु
		/*
		 * Harmless, alपढ़ोy unmapped.
		 */
		r = 0;

	पूर्ण अन्यथा
		DMERR("%s: policy_invalidate_mapping failed", cache_device_name(cache));

	वापस r;
पूर्ण

अटल व्योम invalidate_हटाओ(काष्ठा work_काष्ठा *ws)
अणु
	पूर्णांक r;
	काष्ठा dm_cache_migration *mg = ws_to_mg(ws);
	काष्ठा cache *cache = mg->cache;

	r = invalidate_cblock(cache, mg->invalidate_cblock);
	अगर (r) अणु
		invalidate_complete(mg, false);
		वापस;
	पूर्ण

	init_continuation(&mg->k, invalidate_completed);
	जारी_after_commit(&cache->committer, &mg->k);
	remap_to_origin_clear_discard(cache, mg->overग_लिखो_bio, mg->invalidate_oblock);
	mg->overग_लिखो_bio = शून्य;
	schedule_commit(&cache->committer);
पूर्ण

अटल पूर्णांक invalidate_lock(काष्ठा dm_cache_migration *mg)
अणु
	पूर्णांक r;
	काष्ठा dm_cell_key_v2 key;
	काष्ठा cache *cache = mg->cache;
	काष्ठा dm_bio_prison_cell_v2 *pपुनः_स्मृति;

	pपुनः_स्मृति = alloc_prison_cell(cache);

	build_key(mg->invalidate_oblock, oblock_succ(mg->invalidate_oblock), &key);
	r = dm_cell_lock_v2(cache->prison, &key,
			    READ_WRITE_LOCK_LEVEL, pपुनः_स्मृति, &mg->cell);
	अगर (r < 0) अणु
		मुक्त_prison_cell(cache, pपुनः_स्मृति);
		invalidate_complete(mg, false);
		वापस r;
	पूर्ण

	अगर (mg->cell != pपुनः_स्मृति)
		मुक्त_prison_cell(cache, pपुनः_स्मृति);

	अगर (r)
		quiesce(mg, invalidate_हटाओ);

	अन्यथा अणु
		/*
		 * We can't call invalidate_हटाओ() directly here because we
		 * might still be in request context.
		 */
		init_continuation(&mg->k, invalidate_हटाओ);
		queue_work(cache->wq, &mg->k.ws);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक invalidate_start(काष्ठा cache *cache, dm_cblock_t cblock,
			    dm_oblock_t oblock, काष्ठा bio *bio)
अणु
	काष्ठा dm_cache_migration *mg;

	अगर (!background_work_begin(cache))
		वापस -EPERM;

	mg = alloc_migration(cache);

	mg->overग_लिखो_bio = bio;
	mg->invalidate_cblock = cblock;
	mg->invalidate_oblock = oblock;

	वापस invalidate_lock(mg);
पूर्ण

/*----------------------------------------------------------------
 * bio processing
 *--------------------------------------------------------------*/

क्रमागत busy अणु
	IDLE,
	BUSY
पूर्ण;

अटल क्रमागत busy spare_migration_bandwidth(काष्ठा cache *cache)
अणु
	bool idle = iot_idle_क्रम(&cache->tracker, HZ);
	sector_t current_volume = (atomic_पढ़ो(&cache->nr_io_migrations) + 1) *
		cache->sectors_per_block;

	अगर (idle && current_volume <= cache->migration_threshold)
		वापस IDLE;
	अन्यथा
		वापस BUSY;
पूर्ण

अटल व्योम inc_hit_counter(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	atomic_inc(bio_data_dir(bio) == READ ?
		   &cache->stats.पढ़ो_hit : &cache->stats.ग_लिखो_hit);
पूर्ण

अटल व्योम inc_miss_counter(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	atomic_inc(bio_data_dir(bio) == READ ?
		   &cache->stats.पढ़ो_miss : &cache->stats.ग_लिखो_miss);
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक map_bio(काष्ठा cache *cache, काष्ठा bio *bio, dm_oblock_t block,
		   bool *commit_needed)
अणु
	पूर्णांक r, data_dir;
	bool rb, background_queued;
	dm_cblock_t cblock;

	*commit_needed = false;

	rb = bio_detain_shared(cache, block, bio);
	अगर (!rb) अणु
		/*
		 * An exclusive lock is held क्रम this block, so we have to
		 * रुको.  We set the commit_needed flag so the current
		 * transaction will be committed asap, allowing this lock
		 * to be dropped.
		 */
		*commit_needed = true;
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	data_dir = bio_data_dir(bio);

	अगर (optimisable_bio(cache, bio, block)) अणु
		काष्ठा policy_work *op = शून्य;

		r = policy_lookup_with_work(cache->policy, block, &cblock, data_dir, true, &op);
		अगर (unlikely(r && r != -ENOENT)) अणु
			DMERR_LIMIT("%s: policy_lookup_with_work() failed with r = %d",
				    cache_device_name(cache), r);
			bio_io_error(bio);
			वापस DM_MAPIO_SUBMITTED;
		पूर्ण

		अगर (r == -ENOENT && op) अणु
			bio_drop_shared_lock(cache, bio);
			BUG_ON(op->op != POLICY_PROMOTE);
			mg_start(cache, op, bio);
			वापस DM_MAPIO_SUBMITTED;
		पूर्ण
	पूर्ण अन्यथा अणु
		r = policy_lookup(cache->policy, block, &cblock, data_dir, false, &background_queued);
		अगर (unlikely(r && r != -ENOENT)) अणु
			DMERR_LIMIT("%s: policy_lookup() failed with r = %d",
				    cache_device_name(cache), r);
			bio_io_error(bio);
			वापस DM_MAPIO_SUBMITTED;
		पूर्ण

		अगर (background_queued)
			wake_migration_worker(cache);
	पूर्ण

	अगर (r == -ENOENT) अणु
		काष्ठा per_bio_data *pb = get_per_bio_data(bio);

		/*
		 * Miss.
		 */
		inc_miss_counter(cache, bio);
		अगर (pb->req_nr == 0) अणु
			accounted_begin(cache, bio);
			remap_to_origin_clear_discard(cache, bio, block);
		पूर्ण अन्यथा अणु
			/*
			 * This is a duplicate ग_लिखोthrough io that is no
			 * दीर्घer needed because the block has been demoted.
			 */
			bio_endio(bio);
			वापस DM_MAPIO_SUBMITTED;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Hit.
		 */
		inc_hit_counter(cache, bio);

		/*
		 * Passthrough always maps to the origin, invalidating any
		 * cache blocks that are written to.
		 */
		अगर (passthrough_mode(cache)) अणु
			अगर (bio_data_dir(bio) == WRITE) अणु
				bio_drop_shared_lock(cache, bio);
				atomic_inc(&cache->stats.demotion);
				invalidate_start(cache, cblock, block, bio);
			पूर्ण अन्यथा
				remap_to_origin_clear_discard(cache, bio, block);
		पूर्ण अन्यथा अणु
			अगर (bio_data_dir(bio) == WRITE && ग_लिखोthrough_mode(cache) &&
			    !is_dirty(cache, cblock)) अणु
				remap_to_origin_and_cache(cache, bio, block, cblock);
				accounted_begin(cache, bio);
			पूर्ण अन्यथा
				remap_to_cache_dirty(cache, bio, block, cblock);
		पूर्ण
	पूर्ण

	/*
	 * dm core turns FUA requests पूर्णांकo a separate payload and FLUSH req.
	 */
	अगर (bio->bi_opf & REQ_FUA) अणु
		/*
		 * issue_after_commit will call accounted_begin a second समय.  So
		 * we call accounted_complete() to aव्योम द्विगुन accounting.
		 */
		accounted_complete(cache, bio);
		issue_after_commit(&cache->committer, bio);
		*commit_needed = true;
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल bool process_bio(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	bool commit_needed;

	अगर (map_bio(cache, bio, get_bio_block(cache, bio), &commit_needed) == DM_MAPIO_REMAPPED)
		submit_bio_noacct(bio);

	वापस commit_needed;
पूर्ण

/*
 * A non-zero वापस indicates पढ़ो_only or fail_io mode.
 */
अटल पूर्णांक commit(काष्ठा cache *cache, bool clean_shutकरोwn)
अणु
	पूर्णांक r;

	अगर (get_cache_mode(cache) >= CM_READ_ONLY)
		वापस -EINVAL;

	atomic_inc(&cache->stats.commit_count);
	r = dm_cache_commit(cache->cmd, clean_shutकरोwn);
	अगर (r)
		metadata_operation_failed(cache, "dm_cache_commit", r);

	वापस r;
पूर्ण

/*
 * Used by the batcher.
 */
अटल blk_status_t commit_op(व्योम *context)
अणु
	काष्ठा cache *cache = context;

	अगर (dm_cache_changed_this_transaction(cache->cmd))
		वापस त्रुटि_सं_to_blk_status(commit(cache, false));

	वापस 0;
पूर्ण

/*----------------------------------------------------------------*/

अटल bool process_flush_bio(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	काष्ठा per_bio_data *pb = get_per_bio_data(bio);

	अगर (!pb->req_nr)
		remap_to_origin(cache, bio);
	अन्यथा
		remap_to_cache(cache, bio, 0);

	issue_after_commit(&cache->committer, bio);
	वापस true;
पूर्ण

अटल bool process_discard_bio(काष्ठा cache *cache, काष्ठा bio *bio)
अणु
	dm_dblock_t b, e;

	// FIXME: करो we need to lock the region?  Or can we just assume the
	// user wont be so foolish as to issue discard concurrently with
	// other IO?
	calc_discard_block_range(cache, bio, &b, &e);
	जबतक (b != e) अणु
		set_discard(cache, b);
		b = to_dblock(from_dblock(b) + 1);
	पूर्ण

	अगर (cache->features.discard_passकरोwn) अणु
		remap_to_origin(cache, bio);
		submit_bio_noacct(bio);
	पूर्ण अन्यथा
		bio_endio(bio);

	वापस false;
पूर्ण

अटल व्योम process_deferred_bios(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा cache *cache = container_of(ws, काष्ठा cache, deferred_bio_worker);

	bool commit_needed = false;
	काष्ठा bio_list bios;
	काष्ठा bio *bio;

	bio_list_init(&bios);

	spin_lock_irq(&cache->lock);
	bio_list_merge(&bios, &cache->deferred_bios);
	bio_list_init(&cache->deferred_bios);
	spin_unlock_irq(&cache->lock);

	जबतक ((bio = bio_list_pop(&bios))) अणु
		अगर (bio->bi_opf & REQ_PREFLUSH)
			commit_needed = process_flush_bio(cache, bio) || commit_needed;

		अन्यथा अगर (bio_op(bio) == REQ_OP_DISCARD)
			commit_needed = process_discard_bio(cache, bio) || commit_needed;

		अन्यथा
			commit_needed = process_bio(cache, bio) || commit_needed;
	पूर्ण

	अगर (commit_needed)
		schedule_commit(&cache->committer);
पूर्ण

/*----------------------------------------------------------------
 * Main worker loop
 *--------------------------------------------------------------*/

अटल व्योम requeue_deferred_bios(काष्ठा cache *cache)
अणु
	काष्ठा bio *bio;
	काष्ठा bio_list bios;

	bio_list_init(&bios);
	bio_list_merge(&bios, &cache->deferred_bios);
	bio_list_init(&cache->deferred_bios);

	जबतक ((bio = bio_list_pop(&bios))) अणु
		bio->bi_status = BLK_STS_DM_REQUEUE;
		bio_endio(bio);
	पूर्ण
पूर्ण

/*
 * We want to commit periodically so that not too much
 * unwritten metadata builds up.
 */
अटल व्योम करो_waker(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा cache *cache = container_of(to_delayed_work(ws), काष्ठा cache, waker);

	policy_tick(cache->policy, true);
	wake_migration_worker(cache);
	schedule_commit(&cache->committer);
	queue_delayed_work(cache->wq, &cache->waker, COMMIT_PERIOD);
पूर्ण

अटल व्योम check_migrations(काष्ठा work_काष्ठा *ws)
अणु
	पूर्णांक r;
	काष्ठा policy_work *op;
	काष्ठा cache *cache = container_of(ws, काष्ठा cache, migration_worker);
	क्रमागत busy b;

	क्रम (;;) अणु
		b = spare_migration_bandwidth(cache);

		r = policy_get_background_work(cache->policy, b == IDLE, &op);
		अगर (r == -ENODATA)
			अवरोध;

		अगर (r) अणु
			DMERR_LIMIT("%s: policy_background_work failed",
				    cache_device_name(cache));
			अवरोध;
		पूर्ण

		r = mg_start(cache, op, शून्य);
		अगर (r)
			अवरोध;
	पूर्ण
पूर्ण

/*----------------------------------------------------------------
 * Target methods
 *--------------------------------------------------------------*/

/*
 * This function माला_लो called on the error paths of the स्थिरructor, so we
 * have to cope with a partially initialised काष्ठा.
 */
अटल व्योम destroy(काष्ठा cache *cache)
अणु
	अचिन्हित i;

	mempool_निकास(&cache->migration_pool);

	अगर (cache->prison)
		dm_bio_prison_destroy_v2(cache->prison);

	अगर (cache->wq)
		destroy_workqueue(cache->wq);

	अगर (cache->dirty_bitset)
		मुक्त_bitset(cache->dirty_bitset);

	अगर (cache->discard_bitset)
		मुक्त_bitset(cache->discard_bitset);

	अगर (cache->copier)
		dm_kcopyd_client_destroy(cache->copier);

	अगर (cache->cmd)
		dm_cache_metadata_बंद(cache->cmd);

	अगर (cache->metadata_dev)
		dm_put_device(cache->ti, cache->metadata_dev);

	अगर (cache->origin_dev)
		dm_put_device(cache->ti, cache->origin_dev);

	अगर (cache->cache_dev)
		dm_put_device(cache->ti, cache->cache_dev);

	अगर (cache->policy)
		dm_cache_policy_destroy(cache->policy);

	क्रम (i = 0; i < cache->nr_ctr_args ; i++)
		kमुक्त(cache->ctr_args[i]);
	kमुक्त(cache->ctr_args);

	bioset_निकास(&cache->bs);

	kमुक्त(cache);
पूर्ण

अटल व्योम cache_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा cache *cache = ti->निजी;

	destroy(cache);
पूर्ण

अटल sector_t get_dev_size(काष्ठा dm_dev *dev)
अणु
	वापस i_size_पढ़ो(dev->bdev->bd_inode) >> SECTOR_SHIFT;
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Conकाष्ठा a cache device mapping.
 *
 * cache <metadata dev> <cache dev> <origin dev> <block size>
 *       <#feature args> [<feature arg>]*
 *       <policy> <#policy args> [<policy arg>]*
 *
 * metadata dev    : fast device holding the persistent metadata
 * cache dev	   : fast device holding cached data blocks
 * origin dev	   : slow device holding original data blocks
 * block size	   : cache unit size in sectors
 *
 * #feature args   : number of feature arguments passed
 * feature args    : ग_लिखोthrough.  (The शेष is ग_लिखोback.)
 *
 * policy	   : the replacement policy to use
 * #policy args    : an even number of policy arguments corresponding
 *		     to key/value pairs passed to the policy
 * policy args	   : key/value pairs passed to the policy
 *		     E.g. 'sequential_threshold 1024'
 *		     See cache-policies.txt क्रम details.
 *
 * Optional feature arguments are:
 *   ग_लिखोthrough  : ग_लिखो through caching that prohibits cache block
 *		     content from being dअगरferent from origin block content.
 *		     Without this argument, the शेष behaviour is to ग_लिखो
 *		     back cache block contents later क्रम perक्रमmance reasons,
 *		     so they may dअगरfer from the corresponding origin blocks.
 */
काष्ठा cache_args अणु
	काष्ठा dm_target *ti;

	काष्ठा dm_dev *metadata_dev;

	काष्ठा dm_dev *cache_dev;
	sector_t cache_sectors;

	काष्ठा dm_dev *origin_dev;
	sector_t origin_sectors;

	uपूर्णांक32_t block_size;

	स्थिर अक्षर *policy_name;
	पूर्णांक policy_argc;
	स्थिर अक्षर **policy_argv;

	काष्ठा cache_features features;
पूर्ण;

अटल व्योम destroy_cache_args(काष्ठा cache_args *ca)
अणु
	अगर (ca->metadata_dev)
		dm_put_device(ca->ti, ca->metadata_dev);

	अगर (ca->cache_dev)
		dm_put_device(ca->ti, ca->cache_dev);

	अगर (ca->origin_dev)
		dm_put_device(ca->ti, ca->origin_dev);

	kमुक्त(ca);
पूर्ण

अटल bool at_least_one_arg(काष्ठा dm_arg_set *as, अक्षर **error)
अणु
	अगर (!as->argc) अणु
		*error = "Insufficient args";
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक parse_metadata_dev(काष्ठा cache_args *ca, काष्ठा dm_arg_set *as,
			      अक्षर **error)
अणु
	पूर्णांक r;
	sector_t metadata_dev_size;
	अक्षर b[BDEVNAME_SIZE];

	अगर (!at_least_one_arg(as, error))
		वापस -EINVAL;

	r = dm_get_device(ca->ti, dm_shअगरt_arg(as), FMODE_READ | FMODE_WRITE,
			  &ca->metadata_dev);
	अगर (r) अणु
		*error = "Error opening metadata device";
		वापस r;
	पूर्ण

	metadata_dev_size = get_dev_size(ca->metadata_dev);
	अगर (metadata_dev_size > DM_CACHE_METADATA_MAX_SECTORS_WARNING)
		DMWARN("Metadata device %s is larger than %u sectors: excess space will not be used.",
		       bdevname(ca->metadata_dev->bdev, b), THIN_METADATA_MAX_SECTORS);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_cache_dev(काष्ठा cache_args *ca, काष्ठा dm_arg_set *as,
			   अक्षर **error)
अणु
	पूर्णांक r;

	अगर (!at_least_one_arg(as, error))
		वापस -EINVAL;

	r = dm_get_device(ca->ti, dm_shअगरt_arg(as), FMODE_READ | FMODE_WRITE,
			  &ca->cache_dev);
	अगर (r) अणु
		*error = "Error opening cache device";
		वापस r;
	पूर्ण
	ca->cache_sectors = get_dev_size(ca->cache_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_origin_dev(काष्ठा cache_args *ca, काष्ठा dm_arg_set *as,
			    अक्षर **error)
अणु
	पूर्णांक r;

	अगर (!at_least_one_arg(as, error))
		वापस -EINVAL;

	r = dm_get_device(ca->ti, dm_shअगरt_arg(as), FMODE_READ | FMODE_WRITE,
			  &ca->origin_dev);
	अगर (r) अणु
		*error = "Error opening origin device";
		वापस r;
	पूर्ण

	ca->origin_sectors = get_dev_size(ca->origin_dev);
	अगर (ca->ti->len > ca->origin_sectors) अणु
		*error = "Device size larger than cached device";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_block_size(काष्ठा cache_args *ca, काष्ठा dm_arg_set *as,
			    अक्षर **error)
अणु
	अचिन्हित दीर्घ block_size;

	अगर (!at_least_one_arg(as, error))
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(dm_shअगरt_arg(as), 10, &block_size) || !block_size ||
	    block_size < DATA_DEV_BLOCK_SIZE_MIN_SECTORS ||
	    block_size > DATA_DEV_BLOCK_SIZE_MAX_SECTORS ||
	    block_size & (DATA_DEV_BLOCK_SIZE_MIN_SECTORS - 1)) अणु
		*error = "Invalid data block size";
		वापस -EINVAL;
	पूर्ण

	अगर (block_size > ca->cache_sectors) अणु
		*error = "Data block size is larger than the cache device";
		वापस -EINVAL;
	पूर्ण

	ca->block_size = block_size;

	वापस 0;
पूर्ण

अटल व्योम init_features(काष्ठा cache_features *cf)
अणु
	cf->mode = CM_WRITE;
	cf->io_mode = CM_IO_WRITEBACK;
	cf->metadata_version = 1;
	cf->discard_passकरोwn = true;
पूर्ण

अटल पूर्णांक parse_features(काष्ठा cache_args *ca, काष्ठा dm_arg_set *as,
			  अक्षर **error)
अणु
	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 3, "Invalid number of cache feature arguments"पूर्ण,
	पूर्ण;

	पूर्णांक r, mode_ctr = 0;
	अचिन्हित argc;
	स्थिर अक्षर *arg;
	काष्ठा cache_features *cf = &ca->features;

	init_features(cf);

	r = dm_पढ़ो_arg_group(_args, as, &argc, error);
	अगर (r)
		वापस -EINVAL;

	जबतक (argc--) अणु
		arg = dm_shअगरt_arg(as);

		अगर (!strहालcmp(arg, "writeback")) अणु
			cf->io_mode = CM_IO_WRITEBACK;
			mode_ctr++;
		पूर्ण

		अन्यथा अगर (!strहालcmp(arg, "writethrough")) अणु
			cf->io_mode = CM_IO_WRITETHROUGH;
			mode_ctr++;
		पूर्ण

		अन्यथा अगर (!strहालcmp(arg, "passthrough")) अणु
			cf->io_mode = CM_IO_PASSTHROUGH;
			mode_ctr++;
		पूर्ण

		अन्यथा अगर (!strहालcmp(arg, "metadata2"))
			cf->metadata_version = 2;

		अन्यथा अगर (!strहालcmp(arg, "no_discard_passdown"))
			cf->discard_passकरोwn = false;

		अन्यथा अणु
			*error = "Unrecognised cache feature requested";
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (mode_ctr > 1) अणु
		*error = "Duplicate cache io_mode features requested";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_policy(काष्ठा cache_args *ca, काष्ठा dm_arg_set *as,
			अक्षर **error)
अणु
	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 1024, "Invalid number of policy arguments"पूर्ण,
	पूर्ण;

	पूर्णांक r;

	अगर (!at_least_one_arg(as, error))
		वापस -EINVAL;

	ca->policy_name = dm_shअगरt_arg(as);

	r = dm_पढ़ो_arg_group(_args, as, &ca->policy_argc, error);
	अगर (r)
		वापस -EINVAL;

	ca->policy_argv = (स्थिर अक्षर **)as->argv;
	dm_consume_args(as, ca->policy_argc);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_cache_args(काष्ठा cache_args *ca, पूर्णांक argc, अक्षर **argv,
			    अक्षर **error)
अणु
	पूर्णांक r;
	काष्ठा dm_arg_set as;

	as.argc = argc;
	as.argv = argv;

	r = parse_metadata_dev(ca, &as, error);
	अगर (r)
		वापस r;

	r = parse_cache_dev(ca, &as, error);
	अगर (r)
		वापस r;

	r = parse_origin_dev(ca, &as, error);
	अगर (r)
		वापस r;

	r = parse_block_size(ca, &as, error);
	अगर (r)
		वापस r;

	r = parse_features(ca, &as, error);
	अगर (r)
		वापस r;

	r = parse_policy(ca, &as, error);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा kmem_cache *migration_cache;

#घोषणा NOT_CORE_OPTION 1

अटल पूर्णांक process_config_option(काष्ठा cache *cache, स्थिर अक्षर *key, स्थिर अक्षर *value)
अणु
	अचिन्हित दीर्घ पंचांगp;

	अगर (!strहालcmp(key, "migration_threshold")) अणु
		अगर (kम_से_अदीर्घ(value, 10, &पंचांगp))
			वापस -EINVAL;

		cache->migration_threshold = पंचांगp;
		वापस 0;
	पूर्ण

	वापस NOT_CORE_OPTION;
पूर्ण

अटल पूर्णांक set_config_value(काष्ठा cache *cache, स्थिर अक्षर *key, स्थिर अक्षर *value)
अणु
	पूर्णांक r = process_config_option(cache, key, value);

	अगर (r == NOT_CORE_OPTION)
		r = policy_set_config_value(cache->policy, key, value);

	अगर (r)
		DMWARN("bad config value for %s: %s", key, value);

	वापस r;
पूर्ण

अटल पूर्णांक set_config_values(काष्ठा cache *cache, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक r = 0;

	अगर (argc & 1) अणु
		DMWARN("Odd number of policy arguments given but they should be <key> <value> pairs.");
		वापस -EINVAL;
	पूर्ण

	जबतक (argc) अणु
		r = set_config_value(cache, argv[0], argv[1]);
		अगर (r)
			अवरोध;

		argc -= 2;
		argv += 2;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक create_cache_policy(काष्ठा cache *cache, काष्ठा cache_args *ca,
			       अक्षर **error)
अणु
	काष्ठा dm_cache_policy *p = dm_cache_policy_create(ca->policy_name,
							   cache->cache_size,
							   cache->origin_sectors,
							   cache->sectors_per_block);
	अगर (IS_ERR(p)) अणु
		*error = "Error creating cache's policy";
		वापस PTR_ERR(p);
	पूर्ण
	cache->policy = p;
	BUG_ON(!cache->policy);

	वापस 0;
पूर्ण

/*
 * We want the discard block size to be at least the size of the cache
 * block size and have no more than 2^14 discard blocks across the origin.
 */
#घोषणा MAX_DISCARD_BLOCKS (1 << 14)

अटल bool too_many_discard_blocks(sector_t discard_block_size,
				    sector_t origin_size)
अणु
	(व्योम) sector_भाग(origin_size, discard_block_size);

	वापस origin_size > MAX_DISCARD_BLOCKS;
पूर्ण

अटल sector_t calculate_discard_block_size(sector_t cache_block_size,
					     sector_t origin_size)
अणु
	sector_t discard_block_size = cache_block_size;

	अगर (origin_size)
		जबतक (too_many_discard_blocks(discard_block_size, origin_size))
			discard_block_size *= 2;

	वापस discard_block_size;
पूर्ण

अटल व्योम set_cache_size(काष्ठा cache *cache, dm_cblock_t size)
अणु
	dm_block_t nr_blocks = from_cblock(size);

	अगर (nr_blocks > (1 << 20) && cache->cache_size != size)
		DMWARN_LIMIT("You have created a cache device with a lot of individual cache blocks (%llu)\n"
			     "All these mappings can consume a lot of kernel memory, and take some time to read/write.\n"
			     "Please consider increasing the cache block size to reduce the overall cache block count.",
			     (अचिन्हित दीर्घ दीर्घ) nr_blocks);

	cache->cache_size = size;
पूर्ण

#घोषणा DEFAULT_MIGRATION_THRESHOLD 2048

अटल पूर्णांक cache_create(काष्ठा cache_args *ca, काष्ठा cache **result)
अणु
	पूर्णांक r = 0;
	अक्षर **error = &ca->ti->error;
	काष्ठा cache *cache;
	काष्ठा dm_target *ti = ca->ti;
	dm_block_t origin_blocks;
	काष्ठा dm_cache_metadata *cmd;
	bool may_क्रमmat = ca->features.mode == CM_WRITE;

	cache = kzalloc(माप(*cache), GFP_KERNEL);
	अगर (!cache)
		वापस -ENOMEM;

	cache->ti = ca->ti;
	ti->निजी = cache;
	ti->num_flush_bios = 2;
	ti->flush_supported = true;

	ti->num_discard_bios = 1;
	ti->discards_supported = true;

	ti->per_io_data_size = माप(काष्ठा per_bio_data);

	cache->features = ca->features;
	अगर (ग_लिखोthrough_mode(cache)) अणु
		/* Create bioset क्रम ग_लिखोthrough bios issued to origin */
		r = bioset_init(&cache->bs, BIO_POOL_SIZE, 0, 0);
		अगर (r)
			जाओ bad;
	पूर्ण

	cache->metadata_dev = ca->metadata_dev;
	cache->origin_dev = ca->origin_dev;
	cache->cache_dev = ca->cache_dev;

	ca->metadata_dev = ca->origin_dev = ca->cache_dev = शून्य;

	origin_blocks = cache->origin_sectors = ca->origin_sectors;
	origin_blocks = block_भाग(origin_blocks, ca->block_size);
	cache->origin_blocks = to_oblock(origin_blocks);

	cache->sectors_per_block = ca->block_size;
	अगर (dm_set_target_max_io_len(ti, cache->sectors_per_block)) अणु
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (ca->block_size & (ca->block_size - 1)) अणु
		dm_block_t cache_size = ca->cache_sectors;

		cache->sectors_per_block_shअगरt = -1;
		cache_size = block_भाग(cache_size, ca->block_size);
		set_cache_size(cache, to_cblock(cache_size));
	पूर्ण अन्यथा अणु
		cache->sectors_per_block_shअगरt = __ffs(ca->block_size);
		set_cache_size(cache, to_cblock(ca->cache_sectors >> cache->sectors_per_block_shअगरt));
	पूर्ण

	r = create_cache_policy(cache, ca, error);
	अगर (r)
		जाओ bad;

	cache->policy_nr_args = ca->policy_argc;
	cache->migration_threshold = DEFAULT_MIGRATION_THRESHOLD;

	r = set_config_values(cache, ca->policy_argc, ca->policy_argv);
	अगर (r) अणु
		*error = "Error setting cache policy's config values";
		जाओ bad;
	पूर्ण

	cmd = dm_cache_metadata_खोलो(cache->metadata_dev->bdev,
				     ca->block_size, may_क्रमmat,
				     dm_cache_policy_get_hपूर्णांक_size(cache->policy),
				     ca->features.metadata_version);
	अगर (IS_ERR(cmd)) अणु
		*error = "Error creating metadata object";
		r = PTR_ERR(cmd);
		जाओ bad;
	पूर्ण
	cache->cmd = cmd;
	set_cache_mode(cache, CM_WRITE);
	अगर (get_cache_mode(cache) != CM_WRITE) अणु
		*error = "Unable to get write access to metadata, please check/repair metadata.";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (passthrough_mode(cache)) अणु
		bool all_clean;

		r = dm_cache_metadata_all_clean(cache->cmd, &all_clean);
		अगर (r) अणु
			*error = "dm_cache_metadata_all_clean() failed";
			जाओ bad;
		पूर्ण

		अगर (!all_clean) अणु
			*error = "Cannot enter passthrough mode unless all blocks are clean";
			r = -EINVAL;
			जाओ bad;
		पूर्ण

		policy_allow_migrations(cache->policy, false);
	पूर्ण

	spin_lock_init(&cache->lock);
	bio_list_init(&cache->deferred_bios);
	atomic_set(&cache->nr_allocated_migrations, 0);
	atomic_set(&cache->nr_io_migrations, 0);
	init_रुकोqueue_head(&cache->migration_रुको);

	r = -ENOMEM;
	atomic_set(&cache->nr_dirty, 0);
	cache->dirty_bitset = alloc_bitset(from_cblock(cache->cache_size));
	अगर (!cache->dirty_bitset) अणु
		*error = "could not allocate dirty bitset";
		जाओ bad;
	पूर्ण
	clear_bitset(cache->dirty_bitset, from_cblock(cache->cache_size));

	cache->discard_block_size =
		calculate_discard_block_size(cache->sectors_per_block,
					     cache->origin_sectors);
	cache->discard_nr_blocks = to_dblock(dm_sector_भाग_up(cache->origin_sectors,
							      cache->discard_block_size));
	cache->discard_bitset = alloc_bitset(from_dblock(cache->discard_nr_blocks));
	अगर (!cache->discard_bitset) अणु
		*error = "could not allocate discard bitset";
		जाओ bad;
	पूर्ण
	clear_bitset(cache->discard_bitset, from_dblock(cache->discard_nr_blocks));

	cache->copier = dm_kcopyd_client_create(&dm_kcopyd_throttle);
	अगर (IS_ERR(cache->copier)) अणु
		*error = "could not create kcopyd client";
		r = PTR_ERR(cache->copier);
		जाओ bad;
	पूर्ण

	cache->wq = alloc_workqueue("dm-" DM_MSG_PREFIX, WQ_MEM_RECLAIM, 0);
	अगर (!cache->wq) अणु
		*error = "could not create workqueue for metadata object";
		जाओ bad;
	पूर्ण
	INIT_WORK(&cache->deferred_bio_worker, process_deferred_bios);
	INIT_WORK(&cache->migration_worker, check_migrations);
	INIT_DELAYED_WORK(&cache->waker, करो_waker);

	cache->prison = dm_bio_prison_create_v2(cache->wq);
	अगर (!cache->prison) अणु
		*error = "could not create bio prison";
		जाओ bad;
	पूर्ण

	r = mempool_init_slab_pool(&cache->migration_pool, MIGRATION_POOL_SIZE,
				   migration_cache);
	अगर (r) अणु
		*error = "Error creating cache's migration mempool";
		जाओ bad;
	पूर्ण

	cache->need_tick_bio = true;
	cache->sized = false;
	cache->invalidate = false;
	cache->commit_requested = false;
	cache->loaded_mappings = false;
	cache->loaded_discards = false;

	load_stats(cache);

	atomic_set(&cache->stats.demotion, 0);
	atomic_set(&cache->stats.promotion, 0);
	atomic_set(&cache->stats.copies_aव्योमed, 0);
	atomic_set(&cache->stats.cache_cell_clash, 0);
	atomic_set(&cache->stats.commit_count, 0);
	atomic_set(&cache->stats.discard_count, 0);

	spin_lock_init(&cache->invalidation_lock);
	INIT_LIST_HEAD(&cache->invalidation_requests);

	batcher_init(&cache->committer, commit_op, cache,
		     issue_op, cache, cache->wq);
	iot_init(&cache->tracker);

	init_rwsem(&cache->background_work_lock);
	prevent_background_work(cache);

	*result = cache;
	वापस 0;
bad:
	destroy(cache);
	वापस r;
पूर्ण

अटल पूर्णांक copy_ctr_args(काष्ठा cache *cache, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित i;
	स्थिर अक्षर **copy;

	copy = kसुस्मृति(argc, माप(*copy), GFP_KERNEL);
	अगर (!copy)
		वापस -ENOMEM;
	क्रम (i = 0; i < argc; i++) अणु
		copy[i] = kstrdup(argv[i], GFP_KERNEL);
		अगर (!copy[i]) अणु
			जबतक (i--)
				kमुक्त(copy[i]);
			kमुक्त(copy);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	cache->nr_ctr_args = argc;
	cache->ctr_args = copy;

	वापस 0;
पूर्ण

अटल पूर्णांक cache_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा cache_args *ca;
	काष्ठा cache *cache = शून्य;

	ca = kzalloc(माप(*ca), GFP_KERNEL);
	अगर (!ca) अणु
		ti->error = "Error allocating memory for cache";
		वापस -ENOMEM;
	पूर्ण
	ca->ti = ti;

	r = parse_cache_args(ca, argc, argv, &ti->error);
	अगर (r)
		जाओ out;

	r = cache_create(ca, &cache);
	अगर (r)
		जाओ out;

	r = copy_ctr_args(cache, argc - 3, (स्थिर अक्षर **)argv + 3);
	अगर (r) अणु
		destroy(cache);
		जाओ out;
	पूर्ण

	ti->निजी = cache;
out:
	destroy_cache_args(ca);
	वापस r;
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक cache_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा cache *cache = ti->निजी;

	पूर्णांक r;
	bool commit_needed;
	dm_oblock_t block = get_bio_block(cache, bio);

	init_per_bio_data(bio);
	अगर (unlikely(from_oblock(block) >= from_oblock(cache->origin_blocks))) अणु
		/*
		 * This can only occur अगर the io goes to a partial block at
		 * the end of the origin device.  We करोn't cache these.
		 * Just remap to the origin and carry on.
		 */
		remap_to_origin(cache, bio);
		accounted_begin(cache, bio);
		वापस DM_MAPIO_REMAPPED;
	पूर्ण

	अगर (discard_or_flush(bio)) अणु
		defer_bio(cache, bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	r = map_bio(cache, bio, block, &commit_needed);
	अगर (commit_needed)
		schedule_commit(&cache->committer);

	वापस r;
पूर्ण

अटल पूर्णांक cache_end_io(काष्ठा dm_target *ti, काष्ठा bio *bio, blk_status_t *error)
अणु
	काष्ठा cache *cache = ti->निजी;
	अचिन्हित दीर्घ flags;
	काष्ठा per_bio_data *pb = get_per_bio_data(bio);

	अगर (pb->tick) अणु
		policy_tick(cache->policy, false);

		spin_lock_irqsave(&cache->lock, flags);
		cache->need_tick_bio = true;
		spin_unlock_irqrestore(&cache->lock, flags);
	पूर्ण

	bio_drop_shared_lock(cache, bio);
	accounted_complete(cache, bio);

	वापस DM_ENDIO_DONE;
पूर्ण

अटल पूर्णांक ग_लिखो_dirty_bitset(काष्ठा cache *cache)
अणु
	पूर्णांक r;

	अगर (get_cache_mode(cache) >= CM_READ_ONLY)
		वापस -EINVAL;

	r = dm_cache_set_dirty_bits(cache->cmd, from_cblock(cache->cache_size), cache->dirty_bitset);
	अगर (r)
		metadata_operation_failed(cache, "dm_cache_set_dirty_bits", r);

	वापस r;
पूर्ण

अटल पूर्णांक ग_लिखो_discard_bitset(काष्ठा cache *cache)
अणु
	अचिन्हित i, r;

	अगर (get_cache_mode(cache) >= CM_READ_ONLY)
		वापस -EINVAL;

	r = dm_cache_discard_bitset_resize(cache->cmd, cache->discard_block_size,
					   cache->discard_nr_blocks);
	अगर (r) अणु
		DMERR("%s: could not resize on-disk discard bitset", cache_device_name(cache));
		metadata_operation_failed(cache, "dm_cache_discard_bitset_resize", r);
		वापस r;
	पूर्ण

	क्रम (i = 0; i < from_dblock(cache->discard_nr_blocks); i++) अणु
		r = dm_cache_set_discard(cache->cmd, to_dblock(i),
					 is_discarded(cache, to_dblock(i)));
		अगर (r) अणु
			metadata_operation_failed(cache, "dm_cache_set_discard", r);
			वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_hपूर्णांकs(काष्ठा cache *cache)
अणु
	पूर्णांक r;

	अगर (get_cache_mode(cache) >= CM_READ_ONLY)
		वापस -EINVAL;

	r = dm_cache_ग_लिखो_hपूर्णांकs(cache->cmd, cache->policy);
	अगर (r) अणु
		metadata_operation_failed(cache, "dm_cache_write_hints", r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * वापसs true on success
 */
अटल bool sync_metadata(काष्ठा cache *cache)
अणु
	पूर्णांक r1, r2, r3, r4;

	r1 = ग_लिखो_dirty_bitset(cache);
	अगर (r1)
		DMERR("%s: could not write dirty bitset", cache_device_name(cache));

	r2 = ग_लिखो_discard_bitset(cache);
	अगर (r2)
		DMERR("%s: could not write discard bitset", cache_device_name(cache));

	save_stats(cache);

	r3 = ग_लिखो_hपूर्णांकs(cache);
	अगर (r3)
		DMERR("%s: could not write hints", cache_device_name(cache));

	/*
	 * If writing the above metadata failed, we still commit, but करोn't
	 * set the clean shutकरोwn flag.  This will effectively क्रमce every
	 * dirty bit to be set on reload.
	 */
	r4 = commit(cache, !r1 && !r2 && !r3);
	अगर (r4)
		DMERR("%s: could not write cache metadata", cache_device_name(cache));

	वापस !r1 && !r2 && !r3 && !r4;
पूर्ण

अटल व्योम cache_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा cache *cache = ti->निजी;

	prevent_background_work(cache);
	BUG_ON(atomic_पढ़ो(&cache->nr_io_migrations));

	cancel_delayed_work_sync(&cache->waker);
	drain_workqueue(cache->wq);
	WARN_ON(cache->tracker.in_flight);

	/*
	 * If it's a flush suspend there won't be any deferred bios, so this
	 * call is harmless.
	 */
	requeue_deferred_bios(cache);

	अगर (get_cache_mode(cache) == CM_WRITE)
		(व्योम) sync_metadata(cache);
पूर्ण

अटल पूर्णांक load_mapping(व्योम *context, dm_oblock_t oblock, dm_cblock_t cblock,
			bool dirty, uपूर्णांक32_t hपूर्णांक, bool hपूर्णांक_valid)
अणु
	काष्ठा cache *cache = context;

	अगर (dirty) अणु
		set_bit(from_cblock(cblock), cache->dirty_bitset);
		atomic_inc(&cache->nr_dirty);
	पूर्ण अन्यथा
		clear_bit(from_cblock(cblock), cache->dirty_bitset);

	वापस policy_load_mapping(cache->policy, oblock, cblock, dirty, hपूर्णांक, hपूर्णांक_valid);
पूर्ण

/*
 * The discard block size in the on disk metadata is not
 * neccessarily the same as we're currently using.  So we have to
 * be careful to only set the discarded attribute अगर we know it
 * covers a complete block of the new size.
 */
काष्ठा discard_load_info अणु
	काष्ठा cache *cache;

	/*
	 * These blocks are sized using the on disk dblock size, rather
	 * than the current one.
	 */
	dm_block_t block_size;
	dm_block_t discard_begin, discard_end;
पूर्ण;

अटल व्योम discard_load_info_init(काष्ठा cache *cache,
				   काष्ठा discard_load_info *li)
अणु
	li->cache = cache;
	li->discard_begin = li->discard_end = 0;
पूर्ण

अटल व्योम set_discard_range(काष्ठा discard_load_info *li)
अणु
	sector_t b, e;

	अगर (li->discard_begin == li->discard_end)
		वापस;

	/*
	 * Convert to sectors.
	 */
	b = li->discard_begin * li->block_size;
	e = li->discard_end * li->block_size;

	/*
	 * Then convert back to the current dblock size.
	 */
	b = dm_sector_भाग_up(b, li->cache->discard_block_size);
	sector_भाग(e, li->cache->discard_block_size);

	/*
	 * The origin may have shrunk, so we need to check we're still in
	 * bounds.
	 */
	अगर (e > from_dblock(li->cache->discard_nr_blocks))
		e = from_dblock(li->cache->discard_nr_blocks);

	क्रम (; b < e; b++)
		set_discard(li->cache, to_dblock(b));
पूर्ण

अटल पूर्णांक load_discard(व्योम *context, sector_t discard_block_size,
			dm_dblock_t dblock, bool discard)
अणु
	काष्ठा discard_load_info *li = context;

	li->block_size = discard_block_size;

	अगर (discard) अणु
		अगर (from_dblock(dblock) == li->discard_end)
			/*
			 * We're alपढ़ोy in a discard range, just extend it.
			 */
			li->discard_end = li->discard_end + 1ULL;

		अन्यथा अणु
			/*
			 * Emit the old range and start a new one.
			 */
			set_discard_range(li);
			li->discard_begin = from_dblock(dblock);
			li->discard_end = li->discard_begin + 1ULL;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_discard_range(li);
		li->discard_begin = li->discard_end = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल dm_cblock_t get_cache_dev_size(काष्ठा cache *cache)
अणु
	sector_t size = get_dev_size(cache->cache_dev);
	(व्योम) sector_भाग(size, cache->sectors_per_block);
	वापस to_cblock(size);
पूर्ण

अटल bool can_resize(काष्ठा cache *cache, dm_cblock_t new_size)
अणु
	अगर (from_cblock(new_size) > from_cblock(cache->cache_size)) अणु
		अगर (cache->sized) अणु
			DMERR("%s: unable to extend cache due to missing cache table reload",
			      cache_device_name(cache));
			वापस false;
		पूर्ण
	पूर्ण

	/*
	 * We can't drop a dirty block when shrinking the cache.
	 */
	जबतक (from_cblock(new_size) < from_cblock(cache->cache_size)) अणु
		new_size = to_cblock(from_cblock(new_size) + 1);
		अगर (is_dirty(cache, new_size)) अणु
			DMERR("%s: unable to shrink cache; cache block %llu is dirty",
			      cache_device_name(cache),
			      (अचिन्हित दीर्घ दीर्घ) from_cblock(new_size));
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक resize_cache_dev(काष्ठा cache *cache, dm_cblock_t new_size)
अणु
	पूर्णांक r;

	r = dm_cache_resize(cache->cmd, new_size);
	अगर (r) अणु
		DMERR("%s: could not resize cache metadata", cache_device_name(cache));
		metadata_operation_failed(cache, "dm_cache_resize", r);
		वापस r;
	पूर्ण

	set_cache_size(cache, new_size);

	वापस 0;
पूर्ण

अटल पूर्णांक cache_preresume(काष्ठा dm_target *ti)
अणु
	पूर्णांक r = 0;
	काष्ठा cache *cache = ti->निजी;
	dm_cblock_t csize = get_cache_dev_size(cache);

	/*
	 * Check to see अगर the cache has resized.
	 */
	अगर (!cache->sized) अणु
		r = resize_cache_dev(cache, csize);
		अगर (r)
			वापस r;

		cache->sized = true;

	पूर्ण अन्यथा अगर (csize != cache->cache_size) अणु
		अगर (!can_resize(cache, csize))
			वापस -EINVAL;

		r = resize_cache_dev(cache, csize);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (!cache->loaded_mappings) अणु
		r = dm_cache_load_mappings(cache->cmd, cache->policy,
					   load_mapping, cache);
		अगर (r) अणु
			DMERR("%s: could not load cache mappings", cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_load_mappings", r);
			वापस r;
		पूर्ण

		cache->loaded_mappings = true;
	पूर्ण

	अगर (!cache->loaded_discards) अणु
		काष्ठा discard_load_info li;

		/*
		 * The discard bitset could have been resized, or the
		 * discard block size changed.  To be safe we start by
		 * setting every dblock to not discarded.
		 */
		clear_bitset(cache->discard_bitset, from_dblock(cache->discard_nr_blocks));

		discard_load_info_init(cache, &li);
		r = dm_cache_load_discards(cache->cmd, load_discard, &li);
		अगर (r) अणु
			DMERR("%s: could not load origin discards", cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_load_discards", r);
			वापस r;
		पूर्ण
		set_discard_range(&li);

		cache->loaded_discards = true;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम cache_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा cache *cache = ti->निजी;

	cache->need_tick_bio = true;
	allow_background_work(cache);
	करो_waker(&cache->waker.work);
पूर्ण

अटल व्योम emit_flags(काष्ठा cache *cache, अक्षर *result,
		       अचिन्हित maxlen, sमाप_प्रकार *sz_ptr)
अणु
	sमाप_प्रकार sz = *sz_ptr;
	काष्ठा cache_features *cf = &cache->features;
	अचिन्हित count = (cf->metadata_version == 2) + !cf->discard_passकरोwn + 1;

	DMEMIT("%u ", count);

	अगर (cf->metadata_version == 2)
		DMEMIT("metadata2 ");

	अगर (ग_लिखोthrough_mode(cache))
		DMEMIT("writethrough ");

	अन्यथा अगर (passthrough_mode(cache))
		DMEMIT("passthrough ");

	अन्यथा अगर (ग_लिखोback_mode(cache))
		DMEMIT("writeback ");

	अन्यथा अणु
		DMEMIT("unknown ");
		DMERR("%s: internal error: unknown io mode: %d",
		      cache_device_name(cache), (पूर्णांक) cf->io_mode);
	पूर्ण

	अगर (!cf->discard_passकरोwn)
		DMEMIT("no_discard_passdown ");

	*sz_ptr = sz;
पूर्ण

/*
 * Status क्रमmat:
 *
 * <metadata block size> <#used metadata blocks>/<#total metadata blocks>
 * <cache block size> <#used cache blocks>/<#total cache blocks>
 * <#पढ़ो hits> <#पढ़ो misses> <#ग_लिखो hits> <#ग_लिखो misses>
 * <#demotions> <#promotions> <#dirty>
 * <#features> <features>*
 * <#core args> <core args>
 * <policy name> <#policy args> <policy args>* <cache metadata mode> <needs_check>
 */
अटल व्योम cache_status(काष्ठा dm_target *ti, status_type_t type,
			 अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r = 0;
	अचिन्हित i;
	sमाप_प्रकार sz = 0;
	dm_block_t nr_मुक्त_blocks_metadata = 0;
	dm_block_t nr_blocks_metadata = 0;
	अक्षर buf[BDEVNAME_SIZE];
	काष्ठा cache *cache = ti->निजी;
	dm_cblock_t residency;
	bool needs_check;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		अगर (get_cache_mode(cache) == CM_FAIL) अणु
			DMEMIT("Fail");
			अवरोध;
		पूर्ण

		/* Commit to ensure statistics aren't out-of-date */
		अगर (!(status_flags & DM_STATUS_NOFLUSH_FLAG) && !dm_suspended(ti))
			(व्योम) commit(cache, false);

		r = dm_cache_get_मुक्त_metadata_block_count(cache->cmd, &nr_मुक्त_blocks_metadata);
		अगर (r) अणु
			DMERR("%s: dm_cache_get_free_metadata_block_count returned %d",
			      cache_device_name(cache), r);
			जाओ err;
		पूर्ण

		r = dm_cache_get_metadata_dev_size(cache->cmd, &nr_blocks_metadata);
		अगर (r) अणु
			DMERR("%s: dm_cache_get_metadata_dev_size returned %d",
			      cache_device_name(cache), r);
			जाओ err;
		पूर्ण

		residency = policy_residency(cache->policy);

		DMEMIT("%u %llu/%llu %llu %llu/%llu %u %u %u %u %u %u %lu ",
		       (अचिन्हित)DM_CACHE_METADATA_BLOCK_SIZE,
		       (अचिन्हित दीर्घ दीर्घ)(nr_blocks_metadata - nr_मुक्त_blocks_metadata),
		       (अचिन्हित दीर्घ दीर्घ)nr_blocks_metadata,
		       (अचिन्हित दीर्घ दीर्घ)cache->sectors_per_block,
		       (अचिन्हित दीर्घ दीर्घ) from_cblock(residency),
		       (अचिन्हित दीर्घ दीर्घ) from_cblock(cache->cache_size),
		       (अचिन्हित) atomic_पढ़ो(&cache->stats.पढ़ो_hit),
		       (अचिन्हित) atomic_पढ़ो(&cache->stats.पढ़ो_miss),
		       (अचिन्हित) atomic_पढ़ो(&cache->stats.ग_लिखो_hit),
		       (अचिन्हित) atomic_पढ़ो(&cache->stats.ग_लिखो_miss),
		       (अचिन्हित) atomic_पढ़ो(&cache->stats.demotion),
		       (अचिन्हित) atomic_पढ़ो(&cache->stats.promotion),
		       (अचिन्हित दीर्घ) atomic_पढ़ो(&cache->nr_dirty));

		emit_flags(cache, result, maxlen, &sz);

		DMEMIT("2 migration_threshold %llu ", (अचिन्हित दीर्घ दीर्घ) cache->migration_threshold);

		DMEMIT("%s ", dm_cache_policy_get_name(cache->policy));
		अगर (sz < maxlen) अणु
			r = policy_emit_config_values(cache->policy, result, maxlen, &sz);
			अगर (r)
				DMERR("%s: policy_emit_config_values returned %d",
				      cache_device_name(cache), r);
		पूर्ण

		अगर (get_cache_mode(cache) == CM_READ_ONLY)
			DMEMIT("ro ");
		अन्यथा
			DMEMIT("rw ");

		r = dm_cache_metadata_needs_check(cache->cmd, &needs_check);

		अगर (r || needs_check)
			DMEMIT("needs_check ");
		अन्यथा
			DMEMIT("- ");

		अवरोध;

	हाल STATUSTYPE_TABLE:
		क्रमmat_dev_t(buf, cache->metadata_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);
		क्रमmat_dev_t(buf, cache->cache_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);
		क्रमmat_dev_t(buf, cache->origin_dev->bdev->bd_dev);
		DMEMIT("%s", buf);

		क्रम (i = 0; i < cache->nr_ctr_args - 1; i++)
			DMEMIT(" %s", cache->ctr_args[i]);
		अगर (cache->nr_ctr_args)
			DMEMIT(" %s", cache->ctr_args[cache->nr_ctr_args - 1]);
	पूर्ण

	वापस;

err:
	DMEMIT("Error");
पूर्ण

/*
 * Defines a range of cblocks, begin to (end - 1) are in the range.  end is
 * the one-past-the-end value.
 */
काष्ठा cblock_range अणु
	dm_cblock_t begin;
	dm_cblock_t end;
पूर्ण;

/*
 * A cache block range can take two क्रमms:
 *
 * i) A single cblock, eg. '3456'
 * ii) A begin and end cblock with a dash between, eg. 123-234
 */
अटल पूर्णांक parse_cblock_range(काष्ठा cache *cache, स्थिर अक्षर *str,
			      काष्ठा cblock_range *result)
अणु
	अक्षर dummy;
	uपूर्णांक64_t b, e;
	पूर्णांक r;

	/*
	 * Try and parse क्रमm (ii) first.
	 */
	r = माला_पूछो(str, "%llu-%llu%c", &b, &e, &dummy);
	अगर (r < 0)
		वापस r;

	अगर (r == 2) अणु
		result->begin = to_cblock(b);
		result->end = to_cblock(e);
		वापस 0;
	पूर्ण

	/*
	 * That didn't work, try क्रमm (i).
	 */
	r = माला_पूछो(str, "%llu%c", &b, &dummy);
	अगर (r < 0)
		वापस r;

	अगर (r == 1) अणु
		result->begin = to_cblock(b);
		result->end = to_cblock(from_cblock(result->begin) + 1u);
		वापस 0;
	पूर्ण

	DMERR("%s: invalid cblock range '%s'", cache_device_name(cache), str);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक validate_cblock_range(काष्ठा cache *cache, काष्ठा cblock_range *range)
अणु
	uपूर्णांक64_t b = from_cblock(range->begin);
	uपूर्णांक64_t e = from_cblock(range->end);
	uपूर्णांक64_t n = from_cblock(cache->cache_size);

	अगर (b >= n) अणु
		DMERR("%s: begin cblock out of range: %llu >= %llu",
		      cache_device_name(cache), b, n);
		वापस -EINVAL;
	पूर्ण

	अगर (e > n) अणु
		DMERR("%s: end cblock out of range: %llu > %llu",
		      cache_device_name(cache), e, n);
		वापस -EINVAL;
	पूर्ण

	अगर (b >= e) अणु
		DMERR("%s: invalid cblock range: %llu >= %llu",
		      cache_device_name(cache), b, e);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत dm_cblock_t cblock_succ(dm_cblock_t b)
अणु
	वापस to_cblock(from_cblock(b) + 1);
पूर्ण

अटल पूर्णांक request_invalidation(काष्ठा cache *cache, काष्ठा cblock_range *range)
अणु
	पूर्णांक r = 0;

	/*
	 * We करोn't need to do any locking here because we know we're in
	 * passthrough mode.  There's is potential क्रम a race between an
	 * invalidation triggered by an io and an invalidation message.  This
	 * is harmless, we must not worry अगर the policy call fails.
	 */
	जबतक (range->begin != range->end) अणु
		r = invalidate_cblock(cache, range->begin);
		अगर (r)
			वापस r;

		range->begin = cblock_succ(range->begin);
	पूर्ण

	cache->commit_requested = true;
	वापस r;
पूर्ण

अटल पूर्णांक process_invalidate_cblocks_message(काष्ठा cache *cache, अचिन्हित count,
					      स्थिर अक्षर **cblock_ranges)
अणु
	पूर्णांक r = 0;
	अचिन्हित i;
	काष्ठा cblock_range range;

	अगर (!passthrough_mode(cache)) अणु
		DMERR("%s: cache has to be in passthrough mode for invalidation",
		      cache_device_name(cache));
		वापस -EPERM;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		r = parse_cblock_range(cache, cblock_ranges[i], &range);
		अगर (r)
			अवरोध;

		r = validate_cblock_range(cache, &range);
		अगर (r)
			अवरोध;

		/*
		 * Pass begin and end origin blocks to the worker and wake it.
		 */
		r = request_invalidation(cache, &range);
		अगर (r)
			अवरोध;
	पूर्ण

	वापस r;
पूर्ण

/*
 * Supports
 *	"<key> <value>"
 * and
 *     "invalidate_cblocks [(<begin>)|(<begin>-<end>)]*
 *
 * The key migration_threshold is supported by the cache target core.
 */
अटल पूर्णांक cache_message(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
			 अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा cache *cache = ti->निजी;

	अगर (!argc)
		वापस -EINVAL;

	अगर (get_cache_mode(cache) >= CM_READ_ONLY) अणु
		DMERR("%s: unable to service cache target messages in READ_ONLY or FAIL mode",
		      cache_device_name(cache));
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!strहालcmp(argv[0], "invalidate_cblocks"))
		वापस process_invalidate_cblocks_message(cache, argc - 1, (स्थिर अक्षर **) argv + 1);

	अगर (argc != 2)
		वापस -EINVAL;

	वापस set_config_value(cache, argv[0], argv[1]);
पूर्ण

अटल पूर्णांक cache_iterate_devices(काष्ठा dm_target *ti,
				 iterate_devices_callout_fn fn, व्योम *data)
अणु
	पूर्णांक r = 0;
	काष्ठा cache *cache = ti->निजी;

	r = fn(ti, cache->cache_dev, 0, get_dev_size(cache->cache_dev), data);
	अगर (!r)
		r = fn(ti, cache->origin_dev, 0, ti->len, data);

	वापस r;
पूर्ण

अटल bool origin_dev_supports_discard(काष्ठा block_device *origin_bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(origin_bdev);

	वापस blk_queue_discard(q);
पूर्ण

/*
 * If discard_passकरोwn was enabled verअगरy that the origin device
 * supports discards.  Disable discard_passकरोwn अगर not.
 */
अटल व्योम disable_passकरोwn_अगर_not_supported(काष्ठा cache *cache)
अणु
	काष्ठा block_device *origin_bdev = cache->origin_dev->bdev;
	काष्ठा queue_limits *origin_limits = &bdev_get_queue(origin_bdev)->limits;
	स्थिर अक्षर *reason = शून्य;
	अक्षर buf[BDEVNAME_SIZE];

	अगर (!cache->features.discard_passकरोwn)
		वापस;

	अगर (!origin_dev_supports_discard(origin_bdev))
		reason = "discard unsupported";

	अन्यथा अगर (origin_limits->max_discard_sectors < cache->sectors_per_block)
		reason = "max discard sectors smaller than a block";

	अगर (reason) अणु
		DMWARN("Origin device (%s) %s: Disabling discard passdown.",
		       bdevname(origin_bdev, buf), reason);
		cache->features.discard_passकरोwn = false;
	पूर्ण
पूर्ण

अटल व्योम set_discard_limits(काष्ठा cache *cache, काष्ठा queue_limits *limits)
अणु
	काष्ठा block_device *origin_bdev = cache->origin_dev->bdev;
	काष्ठा queue_limits *origin_limits = &bdev_get_queue(origin_bdev)->limits;

	अगर (!cache->features.discard_passकरोwn) अणु
		/* No passकरोwn is करोne so setting own भव limits */
		limits->max_discard_sectors = min_t(sector_t, cache->discard_block_size * 1024,
						    cache->origin_sectors);
		limits->discard_granularity = cache->discard_block_size << SECTOR_SHIFT;
		वापस;
	पूर्ण

	/*
	 * cache_iterate_devices() is stacking both origin and fast device limits
	 * but discards aren't passed to fast device, so inherit origin's limits.
	 */
	limits->max_discard_sectors = origin_limits->max_discard_sectors;
	limits->max_hw_discard_sectors = origin_limits->max_hw_discard_sectors;
	limits->discard_granularity = origin_limits->discard_granularity;
	limits->discard_alignment = origin_limits->discard_alignment;
	limits->discard_misaligned = origin_limits->discard_misaligned;
पूर्ण

अटल व्योम cache_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा cache *cache = ti->निजी;
	uपूर्णांक64_t io_opt_sectors = limits->io_opt >> SECTOR_SHIFT;

	/*
	 * If the प्रणाली-determined stacked limits are compatible with the
	 * cache's blocksize (io_opt is a factor) करो not override them.
	 */
	अगर (io_opt_sectors < cache->sectors_per_block ||
	    करो_भाग(io_opt_sectors, cache->sectors_per_block)) अणु
		blk_limits_io_min(limits, cache->sectors_per_block << SECTOR_SHIFT);
		blk_limits_io_opt(limits, cache->sectors_per_block << SECTOR_SHIFT);
	पूर्ण

	disable_passकरोwn_अगर_not_supported(cache);
	set_discard_limits(cache, limits);
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा target_type cache_target = अणु
	.name = "cache",
	.version = अणु2, 2, 0पूर्ण,
	.module = THIS_MODULE,
	.ctr = cache_ctr,
	.dtr = cache_dtr,
	.map = cache_map,
	.end_io = cache_end_io,
	.postsuspend = cache_postsuspend,
	.preresume = cache_preresume,
	.resume = cache_resume,
	.status = cache_status,
	.message = cache_message,
	.iterate_devices = cache_iterate_devices,
	.io_hपूर्णांकs = cache_io_hपूर्णांकs,
पूर्ण;

अटल पूर्णांक __init dm_cache_init(व्योम)
अणु
	पूर्णांक r;

	migration_cache = KMEM_CACHE(dm_cache_migration, 0);
	अगर (!migration_cache)
		वापस -ENOMEM;

	r = dm_रेजिस्टर_target(&cache_target);
	अगर (r) अणु
		DMERR("cache target registration failed: %d", r);
		kmem_cache_destroy(migration_cache);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास dm_cache_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&cache_target);
	kmem_cache_destroy(migration_cache);
पूर्ण

module_init(dm_cache_init);
module_निकास(dm_cache_निकास);

MODULE_DESCRIPTION(DM_NAME " cache target");
MODULE_AUTHOR("Joe Thornber <ejt@redhat.com>");
MODULE_LICENSE("GPL");
