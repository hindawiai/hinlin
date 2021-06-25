<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2019 Arrikto, Inc. All Rights Reserved.
 */

#समावेश <linux/mm.h>
#समावेश <linux/bपन.स>
#समावेश <linux/err.h>
#समावेश <linux/hash.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dm-पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mempool.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blk_types.h>
#समावेश <linux/dm-kcopyd.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/device-mapper.h>

#समावेश "dm.h"
#समावेश "dm-clone-metadata.h"

#घोषणा DM_MSG_PREFIX "clone"

/*
 * Minimum and maximum allowed region sizes
 */
#घोषणा MIN_REGION_SIZE (1 << 3)  /* 4KB */
#घोषणा MAX_REGION_SIZE (1 << 21) /* 1GB */

#घोषणा MIN_HYDRATIONS 256 /* Size of hydration mempool */
#घोषणा DEFAULT_HYDRATION_THRESHOLD 1 /* 1 region */
#घोषणा DEFAULT_HYDRATION_BATCH_SIZE 1 /* Hydrate in batches of 1 region */

#घोषणा COMMIT_PERIOD HZ /* 1 sec */

/*
 * Hydration hash table size: 1 << HASH_TABLE_BITS
 */
#घोषणा HASH_TABLE_BITS 15

DECLARE_DM_KCOPYD_THROTTLE_WITH_MODULE_PARM(clone_hydration_throttle,
	"A percentage of time allocated for hydrating regions");

/* Slab cache क्रम काष्ठा dm_clone_region_hydration */
अटल काष्ठा kmem_cache *_hydration_cache;

/* dm-clone metadata modes */
क्रमागत clone_metadata_mode अणु
	CM_WRITE,		/* metadata may be changed */
	CM_READ_ONLY,		/* metadata may not be changed */
	CM_FAIL,		/* all metadata I/O fails */
पूर्ण;

काष्ठा hash_table_bucket;

काष्ठा clone अणु
	काष्ठा dm_target *ti;

	काष्ठा dm_dev *metadata_dev;
	काष्ठा dm_dev *dest_dev;
	काष्ठा dm_dev *source_dev;

	अचिन्हित दीर्घ nr_regions;
	sector_t region_size;
	अचिन्हित पूर्णांक region_shअगरt;

	/*
	 * A metadata commit and the actions taken in हाल it fails should run
	 * as a single atomic step.
	 */
	काष्ठा mutex commit_lock;

	काष्ठा dm_clone_metadata *cmd;

	/* Region hydration hash table */
	काष्ठा hash_table_bucket *ht;

	atomic_t ios_in_flight;

	रुको_queue_head_t hydration_stopped;

	mempool_t hydration_pool;

	अचिन्हित दीर्घ last_commit_jअगरfies;

	/*
	 * We defer incoming WRITE bios क्रम regions that are not hydrated,
	 * until after these regions have been hydrated.
	 *
	 * Also, we defer REQ_FUA and REQ_PREFLUSH bios, until after the
	 * metadata have been committed.
	 */
	spinlock_t lock;
	काष्ठा bio_list deferred_bios;
	काष्ठा bio_list deferred_discard_bios;
	काष्ठा bio_list deferred_flush_bios;
	काष्ठा bio_list deferred_flush_completions;

	/* Maximum number of regions being copied during background hydration. */
	अचिन्हित पूर्णांक hydration_threshold;

	/* Number of regions to batch together during background hydration. */
	अचिन्हित पूर्णांक hydration_batch_size;

	/* Which region to hydrate next */
	अचिन्हित दीर्घ hydration_offset;

	atomic_t hydrations_in_flight;

	/*
	 * Save a copy of the table line rather than reस्थिरructing it क्रम the
	 * status.
	 */
	अचिन्हित पूर्णांक nr_ctr_args;
	स्थिर अक्षर **ctr_args;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा worker;
	काष्ठा delayed_work waker;

	काष्ठा dm_kcopyd_client *kcopyd_client;

	क्रमागत clone_metadata_mode mode;
	अचिन्हित दीर्घ flags;
पूर्ण;

/*
 * dm-clone flags
 */
#घोषणा DM_CLONE_DISCARD_PASSDOWN 0
#घोषणा DM_CLONE_HYDRATION_ENABLED 1
#घोषणा DM_CLONE_HYDRATION_SUSPENDED 2

/*---------------------------------------------------------------------------*/

/*
 * Metadata failure handling.
 */
अटल क्रमागत clone_metadata_mode get_clone_mode(काष्ठा clone *clone)
अणु
	वापस READ_ONCE(clone->mode);
पूर्ण

अटल स्थिर अक्षर *clone_device_name(काष्ठा clone *clone)
अणु
	वापस dm_table_device_name(clone->ti->table);
पूर्ण

अटल व्योम __set_clone_mode(काष्ठा clone *clone, क्रमागत clone_metadata_mode new_mode)
अणु
	स्थिर अक्षर *descs[] = अणु
		"read-write",
		"read-only",
		"fail"
	पूर्ण;

	क्रमागत clone_metadata_mode old_mode = get_clone_mode(clone);

	/* Never move out of fail mode */
	अगर (old_mode == CM_FAIL)
		new_mode = CM_FAIL;

	चयन (new_mode) अणु
	हाल CM_FAIL:
	हाल CM_READ_ONLY:
		dm_clone_metadata_set_पढ़ो_only(clone->cmd);
		अवरोध;

	हाल CM_WRITE:
		dm_clone_metadata_set_पढ़ो_ग_लिखो(clone->cmd);
		अवरोध;
	पूर्ण

	WRITE_ONCE(clone->mode, new_mode);

	अगर (new_mode != old_mode) अणु
		dm_table_event(clone->ti->table);
		DMINFO("%s: Switching to %s mode", clone_device_name(clone),
		       descs[(पूर्णांक)new_mode]);
	पूर्ण
पूर्ण

अटल व्योम __पात_transaction(काष्ठा clone *clone)
अणु
	स्थिर अक्षर *dev_name = clone_device_name(clone);

	अगर (get_clone_mode(clone) >= CM_READ_ONLY)
		वापस;

	DMERR("%s: Aborting current metadata transaction", dev_name);
	अगर (dm_clone_metadata_पात(clone->cmd)) अणु
		DMERR("%s: Failed to abort metadata transaction", dev_name);
		__set_clone_mode(clone, CM_FAIL);
	पूर्ण
पूर्ण

अटल व्योम __reload_in_core_bitset(काष्ठा clone *clone)
अणु
	स्थिर अक्षर *dev_name = clone_device_name(clone);

	अगर (get_clone_mode(clone) == CM_FAIL)
		वापस;

	/* Reload the on-disk bitset */
	DMINFO("%s: Reloading on-disk bitmap", dev_name);
	अगर (dm_clone_reload_in_core_bitset(clone->cmd)) अणु
		DMERR("%s: Failed to reload on-disk bitmap", dev_name);
		__set_clone_mode(clone, CM_FAIL);
	पूर्ण
पूर्ण

अटल व्योम __metadata_operation_failed(काष्ठा clone *clone, स्थिर अक्षर *op, पूर्णांक r)
अणु
	DMERR("%s: Metadata operation `%s' failed: error = %d",
	      clone_device_name(clone), op, r);

	__पात_transaction(clone);
	__set_clone_mode(clone, CM_READ_ONLY);

	/*
	 * dm_clone_reload_in_core_bitset() may run concurrently with either
	 * dm_clone_set_region_hydrated() or dm_clone_cond_set_range(), but
	 * it's safe as we have alपढ़ोy set the metadata to पढ़ो-only mode.
	 */
	__reload_in_core_bitset(clone);
पूर्ण

/*---------------------------------------------------------------------------*/

/* Wake up anyone रुकोing क्रम region hydrations to stop */
अटल अंतरभूत व्योम wakeup_hydration_रुकोers(काष्ठा clone *clone)
अणु
	wake_up_all(&clone->hydration_stopped);
पूर्ण

अटल अंतरभूत व्योम wake_worker(काष्ठा clone *clone)
अणु
	queue_work(clone->wq, &clone->worker);
पूर्ण

/*---------------------------------------------------------------------------*/

/*
 * bio helper functions.
 */
अटल अंतरभूत व्योम remap_to_source(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	bio_set_dev(bio, clone->source_dev->bdev);
पूर्ण

अटल अंतरभूत व्योम remap_to_dest(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	bio_set_dev(bio, clone->dest_dev->bdev);
पूर्ण

अटल bool bio_triggers_commit(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	वापस op_is_flush(bio->bi_opf) &&
		dm_clone_changed_this_transaction(clone->cmd);
पूर्ण

/* Get the address of the region in sectors */
अटल अंतरभूत sector_t region_to_sector(काष्ठा clone *clone, अचिन्हित दीर्घ region_nr)
अणु
	वापस ((sector_t)region_nr << clone->region_shअगरt);
पूर्ण

/* Get the region number of the bio */
अटल अंतरभूत अचिन्हित दीर्घ bio_to_region(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	वापस (bio->bi_iter.bi_sector >> clone->region_shअगरt);
पूर्ण

/* Get the region range covered by the bio */
अटल व्योम bio_region_range(काष्ठा clone *clone, काष्ठा bio *bio,
			     अचिन्हित दीर्घ *rs, अचिन्हित दीर्घ *nr_regions)
अणु
	अचिन्हित दीर्घ end;

	*rs = dm_sector_भाग_up(bio->bi_iter.bi_sector, clone->region_size);
	end = bio_end_sector(bio) >> clone->region_shअगरt;

	अगर (*rs >= end)
		*nr_regions = 0;
	अन्यथा
		*nr_regions = end - *rs;
पूर्ण

/* Check whether a bio overग_लिखोs a region */
अटल अंतरभूत bool is_overग_लिखो_bio(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	वापस (bio_data_dir(bio) == WRITE && bio_sectors(bio) == clone->region_size);
पूर्ण

अटल व्योम fail_bios(काष्ठा bio_list *bios, blk_status_t status)
अणु
	काष्ठा bio *bio;

	जबतक ((bio = bio_list_pop(bios))) अणु
		bio->bi_status = status;
		bio_endio(bio);
	पूर्ण
पूर्ण

अटल व्योम submit_bios(काष्ठा bio_list *bios)
अणु
	काष्ठा bio *bio;
	काष्ठा blk_plug plug;

	blk_start_plug(&plug);

	जबतक ((bio = bio_list_pop(bios)))
		submit_bio_noacct(bio);

	blk_finish_plug(&plug);
पूर्ण

/*
 * Submit bio to the underlying device.
 *
 * If the bio triggers a commit, delay it, until after the metadata have been
 * committed.
 *
 * NOTE: The bio remapping must be perक्रमmed by the caller.
 */
अटल व्योम issue_bio(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	अगर (!bio_triggers_commit(clone, bio)) अणु
		submit_bio_noacct(bio);
		वापस;
	पूर्ण

	/*
	 * If the metadata mode is RO or FAIL we won't be able to commit the
	 * metadata, so we complete the bio with an error.
	 */
	अगर (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) अणु
		bio_io_error(bio);
		वापस;
	पूर्ण

	/*
	 * Batch together any bios that trigger commits and then issue a single
	 * commit क्रम them in process_deferred_flush_bios().
	 */
	spin_lock_irq(&clone->lock);
	bio_list_add(&clone->deferred_flush_bios, bio);
	spin_unlock_irq(&clone->lock);

	wake_worker(clone);
पूर्ण

/*
 * Remap bio to the destination device and submit it.
 *
 * If the bio triggers a commit, delay it, until after the metadata have been
 * committed.
 */
अटल व्योम remap_and_issue(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	remap_to_dest(clone, bio);
	issue_bio(clone, bio);
पूर्ण

/*
 * Issue bios that have been deferred until after their region has finished
 * hydrating.
 *
 * We delegate the bio submission to the worker thपढ़ो, so this is safe to call
 * from पूर्णांकerrupt context.
 */
अटल व्योम issue_deferred_bios(काष्ठा clone *clone, काष्ठा bio_list *bios)
अणु
	काष्ठा bio *bio;
	अचिन्हित दीर्घ flags;
	काष्ठा bio_list flush_bios = BIO_EMPTY_LIST;
	काष्ठा bio_list normal_bios = BIO_EMPTY_LIST;

	अगर (bio_list_empty(bios))
		वापस;

	जबतक ((bio = bio_list_pop(bios))) अणु
		अगर (bio_triggers_commit(clone, bio))
			bio_list_add(&flush_bios, bio);
		अन्यथा
			bio_list_add(&normal_bios, bio);
	पूर्ण

	spin_lock_irqsave(&clone->lock, flags);
	bio_list_merge(&clone->deferred_bios, &normal_bios);
	bio_list_merge(&clone->deferred_flush_bios, &flush_bios);
	spin_unlock_irqrestore(&clone->lock, flags);

	wake_worker(clone);
पूर्ण

अटल व्योम complete_overग_लिखो_bio(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * If the bio has the REQ_FUA flag set we must commit the metadata
	 * beक्रमe संकेतing its completion.
	 *
	 * complete_overग_लिखो_bio() is only called by hydration_complete(),
	 * after having successfully updated the metadata. This means we करोn't
	 * need to call dm_clone_changed_this_transaction() to check अगर the
	 * metadata has changed and thus we can aव्योम taking the metadata spin
	 * lock.
	 */
	अगर (!(bio->bi_opf & REQ_FUA)) अणु
		bio_endio(bio);
		वापस;
	पूर्ण

	/*
	 * If the metadata mode is RO or FAIL we won't be able to commit the
	 * metadata, so we complete the bio with an error.
	 */
	अगर (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) अणु
		bio_io_error(bio);
		वापस;
	पूर्ण

	/*
	 * Batch together any bios that trigger commits and then issue a single
	 * commit क्रम them in process_deferred_flush_bios().
	 */
	spin_lock_irqsave(&clone->lock, flags);
	bio_list_add(&clone->deferred_flush_completions, bio);
	spin_unlock_irqrestore(&clone->lock, flags);

	wake_worker(clone);
पूर्ण

अटल व्योम trim_bio(काष्ठा bio *bio, sector_t sector, अचिन्हित पूर्णांक len)
अणु
	bio->bi_iter.bi_sector = sector;
	bio->bi_iter.bi_size = to_bytes(len);
पूर्ण

अटल व्योम complete_discard_bio(काष्ठा clone *clone, काष्ठा bio *bio, bool success)
अणु
	अचिन्हित दीर्घ rs, nr_regions;

	/*
	 * If the destination device supports discards, remap and trim the
	 * discard bio and pass it करोwn. Otherwise complete the bio
	 * immediately.
	 */
	अगर (test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags) && success) अणु
		remap_to_dest(clone, bio);
		bio_region_range(clone, bio, &rs, &nr_regions);
		trim_bio(bio, region_to_sector(clone, rs),
			 nr_regions << clone->region_shअगरt);
		submit_bio_noacct(bio);
	पूर्ण अन्यथा
		bio_endio(bio);
पूर्ण

अटल व्योम process_discard_bio(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ rs, nr_regions;

	bio_region_range(clone, bio, &rs, &nr_regions);
	अगर (!nr_regions) अणु
		bio_endio(bio);
		वापस;
	पूर्ण

	अगर (WARN_ON(rs >= clone->nr_regions || (rs + nr_regions) < rs ||
		    (rs + nr_regions) > clone->nr_regions)) अणु
		DMERR("%s: Invalid range (%lu + %lu, total regions %lu) for discard (%llu + %u)",
		      clone_device_name(clone), rs, nr_regions,
		      clone->nr_regions,
		      (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector,
		      bio_sectors(bio));
		bio_endio(bio);
		वापस;
	पूर्ण

	/*
	 * The covered regions are alपढ़ोy hydrated so we just need to pass
	 * करोwn the discard.
	 */
	अगर (dm_clone_is_range_hydrated(clone->cmd, rs, nr_regions)) अणु
		complete_discard_bio(clone, bio, true);
		वापस;
	पूर्ण

	/*
	 * If the metadata mode is RO or FAIL we won't be able to update the
	 * metadata क्रम the regions covered by the discard so we just ignore
	 * it.
	 */
	अगर (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) अणु
		bio_endio(bio);
		वापस;
	पूर्ण

	/*
	 * Defer discard processing.
	 */
	spin_lock_irq(&clone->lock);
	bio_list_add(&clone->deferred_discard_bios, bio);
	spin_unlock_irq(&clone->lock);

	wake_worker(clone);
पूर्ण

/*---------------------------------------------------------------------------*/

/*
 * dm-clone region hydrations.
 */
काष्ठा dm_clone_region_hydration अणु
	काष्ठा clone *clone;
	अचिन्हित दीर्घ region_nr;

	काष्ठा bio *overग_लिखो_bio;
	bio_end_io_t *overग_लिखो_bio_end_io;

	काष्ठा bio_list deferred_bios;

	blk_status_t status;

	/* Used by hydration batching */
	काष्ठा list_head list;

	/* Used by hydration hash table */
	काष्ठा hlist_node h;
पूर्ण;

/*
 * Hydration hash table implementation.
 *
 * Ideally we would like to use list_bl, which uses bit spin locks and employs
 * the least signअगरicant bit of the list head to lock the corresponding bucket,
 * reducing the memory overhead क्रम the locks. But, currently, list_bl and bit
 * spin locks करोn't support IRQ safe versions. Since we have to take the lock
 * in both process and पूर्णांकerrupt context, we must fall back to using regular
 * spin locks; one per hash table bucket.
 */
काष्ठा hash_table_bucket अणु
	काष्ठा hlist_head head;

	/* Spinlock protecting the bucket */
	spinlock_t lock;
पूर्ण;

#घोषणा bucket_lock_irqsave(bucket, flags) \
	spin_lock_irqsave(&(bucket)->lock, flags)

#घोषणा bucket_unlock_irqrestore(bucket, flags) \
	spin_unlock_irqrestore(&(bucket)->lock, flags)

#घोषणा bucket_lock_irq(bucket) \
	spin_lock_irq(&(bucket)->lock)

#घोषणा bucket_unlock_irq(bucket) \
	spin_unlock_irq(&(bucket)->lock)

अटल पूर्णांक hash_table_init(काष्ठा clone *clone)
अणु
	अचिन्हित पूर्णांक i, sz;
	काष्ठा hash_table_bucket *bucket;

	sz = 1 << HASH_TABLE_BITS;

	clone->ht = kvदो_स्मृति(sz * माप(काष्ठा hash_table_bucket), GFP_KERNEL);
	अगर (!clone->ht)
		वापस -ENOMEM;

	क्रम (i = 0; i < sz; i++) अणु
		bucket = clone->ht + i;

		INIT_HLIST_HEAD(&bucket->head);
		spin_lock_init(&bucket->lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hash_table_निकास(काष्ठा clone *clone)
अणु
	kvमुक्त(clone->ht);
पूर्ण

अटल काष्ठा hash_table_bucket *get_hash_table_bucket(काष्ठा clone *clone,
						       अचिन्हित दीर्घ region_nr)
अणु
	वापस &clone->ht[hash_दीर्घ(region_nr, HASH_TABLE_BITS)];
पूर्ण

/*
 * Search hash table क्रम a hydration with hd->region_nr == region_nr
 *
 * NOTE: Must be called with the bucket lock held
 */
अटल काष्ठा dm_clone_region_hydration *__hash_find(काष्ठा hash_table_bucket *bucket,
						     अचिन्हित दीर्घ region_nr)
अणु
	काष्ठा dm_clone_region_hydration *hd;

	hlist_क्रम_each_entry(hd, &bucket->head, h) अणु
		अगर (hd->region_nr == region_nr)
			वापस hd;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Insert a hydration पूर्णांकo the hash table.
 *
 * NOTE: Must be called with the bucket lock held.
 */
अटल अंतरभूत व्योम __insert_region_hydration(काष्ठा hash_table_bucket *bucket,
					     काष्ठा dm_clone_region_hydration *hd)
अणु
	hlist_add_head(&hd->h, &bucket->head);
पूर्ण

/*
 * This function inserts a hydration पूर्णांकo the hash table, unless someone अन्यथा
 * managed to insert a hydration क्रम the same region first. In the latter हाल
 * it वापसs the existing hydration descriptor क्रम this region.
 *
 * NOTE: Must be called with the hydration hash table lock held.
 */
अटल काष्ठा dm_clone_region_hydration *
__find_or_insert_region_hydration(काष्ठा hash_table_bucket *bucket,
				  काष्ठा dm_clone_region_hydration *hd)
अणु
	काष्ठा dm_clone_region_hydration *hd2;

	hd2 = __hash_find(bucket, hd->region_nr);
	अगर (hd2)
		वापस hd2;

	__insert_region_hydration(bucket, hd);

	वापस hd;
पूर्ण

/*---------------------------------------------------------------------------*/

/* Allocate a hydration */
अटल काष्ठा dm_clone_region_hydration *alloc_hydration(काष्ठा clone *clone)
अणु
	काष्ठा dm_clone_region_hydration *hd;

	/*
	 * Allocate a hydration from the hydration mempool.
	 * This might block but it can't fail.
	 */
	hd = mempool_alloc(&clone->hydration_pool, GFP_NOIO);
	hd->clone = clone;

	वापस hd;
पूर्ण

अटल अंतरभूत व्योम मुक्त_hydration(काष्ठा dm_clone_region_hydration *hd)
अणु
	mempool_मुक्त(hd, &hd->clone->hydration_pool);
पूर्ण

/* Initialize a hydration */
अटल व्योम hydration_init(काष्ठा dm_clone_region_hydration *hd, अचिन्हित दीर्घ region_nr)
अणु
	hd->region_nr = region_nr;
	hd->overग_लिखो_bio = शून्य;
	bio_list_init(&hd->deferred_bios);
	hd->status = 0;

	INIT_LIST_HEAD(&hd->list);
	INIT_HLIST_NODE(&hd->h);
पूर्ण

/*---------------------------------------------------------------------------*/

/*
 * Update dm-clone's metadata after a region has finished hydrating and हटाओ
 * hydration from the hash table.
 */
अटल पूर्णांक hydration_update_metadata(काष्ठा dm_clone_region_hydration *hd)
अणु
	पूर्णांक r = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा hash_table_bucket *bucket;
	काष्ठा clone *clone = hd->clone;

	अगर (unlikely(get_clone_mode(clone) >= CM_READ_ONLY))
		r = -EPERM;

	/* Update the metadata */
	अगर (likely(!r) && hd->status == BLK_STS_OK)
		r = dm_clone_set_region_hydrated(clone->cmd, hd->region_nr);

	bucket = get_hash_table_bucket(clone, hd->region_nr);

	/* Remove hydration from hash table */
	bucket_lock_irqsave(bucket, flags);
	hlist_del(&hd->h);
	bucket_unlock_irqrestore(bucket, flags);

	वापस r;
पूर्ण

/*
 * Complete a region's hydration:
 *
 *	1. Update dm-clone's metadata.
 *	2. Remove hydration from hash table.
 *	3. Complete overग_लिखो bio.
 *	4. Issue deferred bios.
 *	5. If this was the last hydration, wake up anyone रुकोing क्रम
 *	   hydrations to finish.
 */
अटल व्योम hydration_complete(काष्ठा dm_clone_region_hydration *hd)
अणु
	पूर्णांक r;
	blk_status_t status;
	काष्ठा clone *clone = hd->clone;

	r = hydration_update_metadata(hd);

	अगर (hd->status == BLK_STS_OK && likely(!r)) अणु
		अगर (hd->overग_लिखो_bio)
			complete_overग_लिखो_bio(clone, hd->overग_लिखो_bio);

		issue_deferred_bios(clone, &hd->deferred_bios);
	पूर्ण अन्यथा अणु
		status = r ? BLK_STS_IOERR : hd->status;

		अगर (hd->overग_लिखो_bio)
			bio_list_add(&hd->deferred_bios, hd->overग_लिखो_bio);

		fail_bios(&hd->deferred_bios, status);
	पूर्ण

	मुक्त_hydration(hd);

	अगर (atomic_dec_and_test(&clone->hydrations_in_flight))
		wakeup_hydration_रुकोers(clone);
पूर्ण

अटल व्योम hydration_kcopyd_callback(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err, व्योम *context)
अणु
	blk_status_t status;

	काष्ठा dm_clone_region_hydration *पंचांगp, *hd = context;
	काष्ठा clone *clone = hd->clone;

	LIST_HEAD(batched_hydrations);

	अगर (पढ़ो_err || ग_लिखो_err) अणु
		DMERR_LIMIT("%s: hydration failed", clone_device_name(clone));
		status = BLK_STS_IOERR;
	पूर्ण अन्यथा अणु
		status = BLK_STS_OK;
	पूर्ण
	list_splice_tail(&hd->list, &batched_hydrations);

	hd->status = status;
	hydration_complete(hd);

	/* Complete batched hydrations */
	list_क्रम_each_entry_safe(hd, पंचांगp, &batched_hydrations, list) अणु
		hd->status = status;
		hydration_complete(hd);
	पूर्ण

	/* Continue background hydration, अगर there is no I/O in-flight */
	अगर (test_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags) &&
	    !atomic_पढ़ो(&clone->ios_in_flight))
		wake_worker(clone);
पूर्ण

अटल व्योम hydration_copy(काष्ठा dm_clone_region_hydration *hd, अचिन्हित पूर्णांक nr_regions)
अणु
	अचिन्हित दीर्घ region_start, region_end;
	sector_t tail_size, region_size, total_size;
	काष्ठा dm_io_region from, to;
	काष्ठा clone *clone = hd->clone;

	अगर (WARN_ON(!nr_regions))
		वापस;

	region_size = clone->region_size;
	region_start = hd->region_nr;
	region_end = region_start + nr_regions - 1;

	total_size = region_to_sector(clone, nr_regions - 1);

	अगर (region_end == clone->nr_regions - 1) अणु
		/*
		 * The last region of the target might be smaller than
		 * region_size.
		 */
		tail_size = clone->ti->len & (region_size - 1);
		अगर (!tail_size)
			tail_size = region_size;
	पूर्ण अन्यथा अणु
		tail_size = region_size;
	पूर्ण

	total_size += tail_size;

	from.bdev = clone->source_dev->bdev;
	from.sector = region_to_sector(clone, region_start);
	from.count = total_size;

	to.bdev = clone->dest_dev->bdev;
	to.sector = from.sector;
	to.count = from.count;

	/* Issue copy */
	atomic_add(nr_regions, &clone->hydrations_in_flight);
	dm_kcopyd_copy(clone->kcopyd_client, &from, 1, &to, 0,
		       hydration_kcopyd_callback, hd);
पूर्ण

अटल व्योम overग_लिखो_endio(काष्ठा bio *bio)
अणु
	काष्ठा dm_clone_region_hydration *hd = bio->bi_निजी;

	bio->bi_end_io = hd->overग_लिखो_bio_end_io;
	hd->status = bio->bi_status;

	hydration_complete(hd);
पूर्ण

अटल व्योम hydration_overग_लिखो(काष्ठा dm_clone_region_hydration *hd, काष्ठा bio *bio)
अणु
	/*
	 * We करोn't need to save and restore bio->bi_निजी because device
	 * mapper core generates a new bio क्रम us to use, with clean
	 * bi_निजी.
	 */
	hd->overग_लिखो_bio = bio;
	hd->overग_लिखो_bio_end_io = bio->bi_end_io;

	bio->bi_end_io = overग_लिखो_endio;
	bio->bi_निजी = hd;

	atomic_inc(&hd->clone->hydrations_in_flight);
	submit_bio_noacct(bio);
पूर्ण

/*
 * Hydrate bio's region.
 *
 * This function starts the hydration of the bio's region and माला_दो the bio in
 * the list of deferred bios क्रम this region. In हाल, by the समय this
 * function is called, the region has finished hydrating it's submitted to the
 * destination device.
 *
 * NOTE: The bio remapping must be perक्रमmed by the caller.
 */
अटल व्योम hydrate_bio_region(काष्ठा clone *clone, काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ region_nr;
	काष्ठा hash_table_bucket *bucket;
	काष्ठा dm_clone_region_hydration *hd, *hd2;

	region_nr = bio_to_region(clone, bio);
	bucket = get_hash_table_bucket(clone, region_nr);

	bucket_lock_irq(bucket);

	hd = __hash_find(bucket, region_nr);
	अगर (hd) अणु
		/* Someone अन्यथा is hydrating the region */
		bio_list_add(&hd->deferred_bios, bio);
		bucket_unlock_irq(bucket);
		वापस;
	पूर्ण

	अगर (dm_clone_is_region_hydrated(clone->cmd, region_nr)) अणु
		/* The region has been hydrated */
		bucket_unlock_irq(bucket);
		issue_bio(clone, bio);
		वापस;
	पूर्ण

	/*
	 * We must allocate a hydration descriptor and start the hydration of
	 * the corresponding region.
	 */
	bucket_unlock_irq(bucket);

	hd = alloc_hydration(clone);
	hydration_init(hd, region_nr);

	bucket_lock_irq(bucket);

	/* Check अगर the region has been hydrated in the meanसमय. */
	अगर (dm_clone_is_region_hydrated(clone->cmd, region_nr)) अणु
		bucket_unlock_irq(bucket);
		मुक्त_hydration(hd);
		issue_bio(clone, bio);
		वापस;
	पूर्ण

	hd2 = __find_or_insert_region_hydration(bucket, hd);
	अगर (hd2 != hd) अणु
		/* Someone अन्यथा started the region's hydration. */
		bio_list_add(&hd2->deferred_bios, bio);
		bucket_unlock_irq(bucket);
		मुक्त_hydration(hd);
		वापस;
	पूर्ण

	/*
	 * If the metadata mode is RO or FAIL then there is no poपूर्णांक starting a
	 * hydration, since we will not be able to update the metadata when the
	 * hydration finishes.
	 */
	अगर (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) अणु
		hlist_del(&hd->h);
		bucket_unlock_irq(bucket);
		मुक्त_hydration(hd);
		bio_io_error(bio);
		वापस;
	पूर्ण

	/*
	 * Start region hydration.
	 *
	 * If a bio overग_लिखोs a region, i.e., its size is equal to the
	 * region's size, then we don't need to copy the region from the source
	 * to the destination device.
	 */
	अगर (is_overग_लिखो_bio(clone, bio)) अणु
		bucket_unlock_irq(bucket);
		hydration_overग_लिखो(hd, bio);
	पूर्ण अन्यथा अणु
		bio_list_add(&hd->deferred_bios, bio);
		bucket_unlock_irq(bucket);
		hydration_copy(hd, 1);
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------*/

/*
 * Background hydrations.
 */

/*
 * Batch region hydrations.
 *
 * To better utilize device bandwidth we batch together the hydration of
 * adjacent regions. This allows us to use small region sizes, e.g., 4KB, which
 * is good क्रम small, अक्रमom ग_लिखो perक्रमmance (because of the overwriting of
 * un-hydrated regions) and at the same समय issue big copy requests to kcopyd
 * to achieve high hydration bandwidth.
 */
काष्ठा batch_info अणु
	काष्ठा dm_clone_region_hydration *head;
	अचिन्हित पूर्णांक nr_batched_regions;
पूर्ण;

अटल व्योम __batch_hydration(काष्ठा batch_info *batch,
			      काष्ठा dm_clone_region_hydration *hd)
अणु
	काष्ठा clone *clone = hd->clone;
	अचिन्हित पूर्णांक max_batch_size = READ_ONCE(clone->hydration_batch_size);

	अगर (batch->head) अणु
		/* Try to extend the current batch */
		अगर (batch->nr_batched_regions < max_batch_size &&
		    (batch->head->region_nr + batch->nr_batched_regions) == hd->region_nr) अणु
			list_add_tail(&hd->list, &batch->head->list);
			batch->nr_batched_regions++;
			hd = शून्य;
		पूर्ण

		/* Check अगर we should issue the current batch */
		अगर (batch->nr_batched_regions >= max_batch_size || hd) अणु
			hydration_copy(batch->head, batch->nr_batched_regions);
			batch->head = शून्य;
			batch->nr_batched_regions = 0;
		पूर्ण
	पूर्ण

	अगर (!hd)
		वापस;

	/* We treat max batch sizes of zero and one equivalently */
	अगर (max_batch_size <= 1) अणु
		hydration_copy(hd, 1);
		वापस;
	पूर्ण

	/* Start a new batch */
	BUG_ON(!list_empty(&hd->list));
	batch->head = hd;
	batch->nr_batched_regions = 1;
पूर्ण

अटल अचिन्हित दीर्घ __start_next_hydration(काष्ठा clone *clone,
					    अचिन्हित दीर्घ offset,
					    काष्ठा batch_info *batch)
अणु
	काष्ठा hash_table_bucket *bucket;
	काष्ठा dm_clone_region_hydration *hd;
	अचिन्हित दीर्घ nr_regions = clone->nr_regions;

	hd = alloc_hydration(clone);

	/* Try to find a region to hydrate. */
	करो अणु
		offset = dm_clone_find_next_unhydrated_region(clone->cmd, offset);
		अगर (offset == nr_regions)
			अवरोध;

		bucket = get_hash_table_bucket(clone, offset);
		bucket_lock_irq(bucket);

		अगर (!dm_clone_is_region_hydrated(clone->cmd, offset) &&
		    !__hash_find(bucket, offset)) अणु
			hydration_init(hd, offset);
			__insert_region_hydration(bucket, hd);
			bucket_unlock_irq(bucket);

			/* Batch hydration */
			__batch_hydration(batch, hd);

			वापस (offset + 1);
		पूर्ण

		bucket_unlock_irq(bucket);

	पूर्ण जबतक (++offset < nr_regions);

	अगर (hd)
		मुक्त_hydration(hd);

	वापस offset;
पूर्ण

/*
 * This function searches क्रम regions that still reside in the source device
 * and starts their hydration.
 */
अटल व्योम करो_hydration(काष्ठा clone *clone)
अणु
	अचिन्हित पूर्णांक current_volume;
	अचिन्हित दीर्घ offset, nr_regions = clone->nr_regions;

	काष्ठा batch_info batch = अणु
		.head = शून्य,
		.nr_batched_regions = 0,
	पूर्ण;

	अगर (unlikely(get_clone_mode(clone) >= CM_READ_ONLY))
		वापस;

	अगर (dm_clone_is_hydration_करोne(clone->cmd))
		वापस;

	/*
	 * Aव्योम race with device suspension.
	 */
	atomic_inc(&clone->hydrations_in_flight);

	/*
	 * Make sure atomic_inc() is ordered beक्रमe test_bit(), otherwise we
	 * might race with clone_postsuspend() and start a region hydration
	 * after the target has been suspended.
	 *
	 * This is paired with the smp_mb__after_atomic() in
	 * clone_postsuspend().
	 */
	smp_mb__after_atomic();

	offset = clone->hydration_offset;
	जबतक (likely(!test_bit(DM_CLONE_HYDRATION_SUSPENDED, &clone->flags)) &&
	       !atomic_पढ़ो(&clone->ios_in_flight) &&
	       test_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags) &&
	       offset < nr_regions) अणु
		current_volume = atomic_पढ़ो(&clone->hydrations_in_flight);
		current_volume += batch.nr_batched_regions;

		अगर (current_volume > READ_ONCE(clone->hydration_threshold))
			अवरोध;

		offset = __start_next_hydration(clone, offset, &batch);
	पूर्ण

	अगर (batch.head)
		hydration_copy(batch.head, batch.nr_batched_regions);

	अगर (offset >= nr_regions)
		offset = 0;

	clone->hydration_offset = offset;

	अगर (atomic_dec_and_test(&clone->hydrations_in_flight))
		wakeup_hydration_रुकोers(clone);
पूर्ण

/*---------------------------------------------------------------------------*/

अटल bool need_commit_due_to_समय(काष्ठा clone *clone)
अणु
	वापस !समय_in_range(jअगरfies, clone->last_commit_jअगरfies,
			      clone->last_commit_jअगरfies + COMMIT_PERIOD);
पूर्ण

/*
 * A non-zero वापस indicates पढ़ो-only or fail mode.
 */
अटल पूर्णांक commit_metadata(काष्ठा clone *clone, bool *dest_dev_flushed)
अणु
	पूर्णांक r = 0;

	अगर (dest_dev_flushed)
		*dest_dev_flushed = false;

	mutex_lock(&clone->commit_lock);

	अगर (!dm_clone_changed_this_transaction(clone->cmd))
		जाओ out;

	अगर (unlikely(get_clone_mode(clone) >= CM_READ_ONLY)) अणु
		r = -EPERM;
		जाओ out;
	पूर्ण

	r = dm_clone_metadata_pre_commit(clone->cmd);
	अगर (unlikely(r)) अणु
		__metadata_operation_failed(clone, "dm_clone_metadata_pre_commit", r);
		जाओ out;
	पूर्ण

	r = blkdev_issue_flush(clone->dest_dev->bdev);
	अगर (unlikely(r)) अणु
		__metadata_operation_failed(clone, "flush destination device", r);
		जाओ out;
	पूर्ण

	अगर (dest_dev_flushed)
		*dest_dev_flushed = true;

	r = dm_clone_metadata_commit(clone->cmd);
	अगर (unlikely(r)) अणु
		__metadata_operation_failed(clone, "dm_clone_metadata_commit", r);
		जाओ out;
	पूर्ण

	अगर (dm_clone_is_hydration_करोne(clone->cmd))
		dm_table_event(clone->ti->table);
out:
	mutex_unlock(&clone->commit_lock);

	वापस r;
पूर्ण

अटल व्योम process_deferred_discards(काष्ठा clone *clone)
अणु
	पूर्णांक r = -EPERM;
	काष्ठा bio *bio;
	काष्ठा blk_plug plug;
	अचिन्हित दीर्घ rs, nr_regions;
	काष्ठा bio_list discards = BIO_EMPTY_LIST;

	spin_lock_irq(&clone->lock);
	bio_list_merge(&discards, &clone->deferred_discard_bios);
	bio_list_init(&clone->deferred_discard_bios);
	spin_unlock_irq(&clone->lock);

	अगर (bio_list_empty(&discards))
		वापस;

	अगर (unlikely(get_clone_mode(clone) >= CM_READ_ONLY))
		जाओ out;

	/* Update the metadata */
	bio_list_क्रम_each(bio, &discards) अणु
		bio_region_range(clone, bio, &rs, &nr_regions);
		/*
		 * A discard request might cover regions that have been alपढ़ोy
		 * hydrated. There is no need to update the metadata क्रम these
		 * regions.
		 */
		r = dm_clone_cond_set_range(clone->cmd, rs, nr_regions);
		अगर (unlikely(r))
			अवरोध;
	पूर्ण
out:
	blk_start_plug(&plug);
	जबतक ((bio = bio_list_pop(&discards)))
		complete_discard_bio(clone, bio, r == 0);
	blk_finish_plug(&plug);
पूर्ण

अटल व्योम process_deferred_bios(काष्ठा clone *clone)
अणु
	काष्ठा bio_list bios = BIO_EMPTY_LIST;

	spin_lock_irq(&clone->lock);
	bio_list_merge(&bios, &clone->deferred_bios);
	bio_list_init(&clone->deferred_bios);
	spin_unlock_irq(&clone->lock);

	अगर (bio_list_empty(&bios))
		वापस;

	submit_bios(&bios);
पूर्ण

अटल व्योम process_deferred_flush_bios(काष्ठा clone *clone)
अणु
	काष्ठा bio *bio;
	bool dest_dev_flushed;
	काष्ठा bio_list bios = BIO_EMPTY_LIST;
	काष्ठा bio_list bio_completions = BIO_EMPTY_LIST;

	/*
	 * If there are any deferred flush bios, we must commit the metadata
	 * beक्रमe issuing them or संकेतing their completion.
	 */
	spin_lock_irq(&clone->lock);
	bio_list_merge(&bios, &clone->deferred_flush_bios);
	bio_list_init(&clone->deferred_flush_bios);

	bio_list_merge(&bio_completions, &clone->deferred_flush_completions);
	bio_list_init(&clone->deferred_flush_completions);
	spin_unlock_irq(&clone->lock);

	अगर (bio_list_empty(&bios) && bio_list_empty(&bio_completions) &&
	    !(dm_clone_changed_this_transaction(clone->cmd) && need_commit_due_to_समय(clone)))
		वापस;

	अगर (commit_metadata(clone, &dest_dev_flushed)) अणु
		bio_list_merge(&bios, &bio_completions);

		जबतक ((bio = bio_list_pop(&bios)))
			bio_io_error(bio);

		वापस;
	पूर्ण

	clone->last_commit_jअगरfies = jअगरfies;

	जबतक ((bio = bio_list_pop(&bio_completions)))
		bio_endio(bio);

	जबतक ((bio = bio_list_pop(&bios))) अणु
		अगर ((bio->bi_opf & REQ_PREFLUSH) && dest_dev_flushed) अणु
			/* We just flushed the destination device as part of
			 * the metadata commit, so there is no reason to send
			 * another flush.
			 */
			bio_endio(bio);
		पूर्ण अन्यथा अणु
			submit_bio_noacct(bio);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम करो_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा clone *clone = container_of(work, typeof(*clone), worker);

	process_deferred_bios(clone);
	process_deferred_discards(clone);

	/*
	 * process_deferred_flush_bios():
	 *
	 *   - Commit metadata
	 *
	 *   - Process deferred REQ_FUA completions
	 *
	 *   - Process deferred REQ_PREFLUSH bios
	 */
	process_deferred_flush_bios(clone);

	/* Background hydration */
	करो_hydration(clone);
पूर्ण

/*
 * Commit periodically so that not too much unwritten data builds up.
 *
 * Also, restart background hydration, अगर it has been stopped by in-flight I/O.
 */
अटल व्योम करो_waker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा clone *clone = container_of(to_delayed_work(work), काष्ठा clone, waker);

	wake_worker(clone);
	queue_delayed_work(clone->wq, &clone->waker, COMMIT_PERIOD);
पूर्ण

/*---------------------------------------------------------------------------*/

/*
 * Target methods
 */
अटल पूर्णांक clone_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा clone *clone = ti->निजी;
	अचिन्हित दीर्घ region_nr;

	atomic_inc(&clone->ios_in_flight);

	अगर (unlikely(get_clone_mode(clone) == CM_FAIL))
		वापस DM_MAPIO_KILL;

	/*
	 * REQ_PREFLUSH bios carry no data:
	 *
	 * - Commit metadata, अगर changed
	 *
	 * - Pass करोwn to destination device
	 */
	अगर (bio->bi_opf & REQ_PREFLUSH) अणु
		remap_and_issue(clone, bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	bio->bi_iter.bi_sector = dm_target_offset(ti, bio->bi_iter.bi_sector);

	/*
	 * dm-clone पूर्णांकerprets discards and perक्रमms a fast hydration of the
	 * discarded regions, i.e., we skip the copy from the source device and
	 * just mark the regions as hydrated.
	 */
	अगर (bio_op(bio) == REQ_OP_DISCARD) अणु
		process_discard_bio(clone, bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	/*
	 * If the bio's region is hydrated, redirect it to the destination
	 * device.
	 *
	 * If the region is not hydrated and the bio is a READ, redirect it to
	 * the source device.
	 *
	 * Else, defer WRITE bio until after its region has been hydrated and
	 * start the region's hydration immediately.
	 */
	region_nr = bio_to_region(clone, bio);
	अगर (dm_clone_is_region_hydrated(clone->cmd, region_nr)) अणु
		remap_and_issue(clone, bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण अन्यथा अगर (bio_data_dir(bio) == READ) अणु
		remap_to_source(clone, bio);
		वापस DM_MAPIO_REMAPPED;
	पूर्ण

	remap_to_dest(clone, bio);
	hydrate_bio_region(clone, bio);

	वापस DM_MAPIO_SUBMITTED;
पूर्ण

अटल पूर्णांक clone_endio(काष्ठा dm_target *ti, काष्ठा bio *bio, blk_status_t *error)
अणु
	काष्ठा clone *clone = ti->निजी;

	atomic_dec(&clone->ios_in_flight);

	वापस DM_ENDIO_DONE;
पूर्ण

अटल व्योम emit_flags(काष्ठा clone *clone, अक्षर *result, अचिन्हित पूर्णांक maxlen,
		       sमाप_प्रकार *sz_ptr)
अणु
	sमाप_प्रकार sz = *sz_ptr;
	अचिन्हित पूर्णांक count;

	count = !test_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags);
	count += !test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags);

	DMEMIT("%u ", count);

	अगर (!test_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags))
		DMEMIT("no_hydration ");

	अगर (!test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags))
		DMEMIT("no_discard_passdown ");

	*sz_ptr = sz;
पूर्ण

अटल व्योम emit_core_args(काष्ठा clone *clone, अक्षर *result,
			   अचिन्हित पूर्णांक maxlen, sमाप_प्रकार *sz_ptr)
अणु
	sमाप_प्रकार sz = *sz_ptr;
	अचिन्हित पूर्णांक count = 4;

	DMEMIT("%u hydration_threshold %u hydration_batch_size %u ", count,
	       READ_ONCE(clone->hydration_threshold),
	       READ_ONCE(clone->hydration_batch_size));

	*sz_ptr = sz;
पूर्ण

/*
 * Status क्रमmat:
 *
 * <metadata block size> <#used metadata blocks>/<#total metadata blocks>
 * <clone region size> <#hydrated regions>/<#total regions> <#hydrating regions>
 * <#features> <features>* <#core args> <core args>* <clone metadata mode>
 */
अटल व्योम clone_status(काष्ठा dm_target *ti, status_type_t type,
			 अचिन्हित पूर्णांक status_flags, अक्षर *result,
			 अचिन्हित पूर्णांक maxlen)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक i;
	sमाप_प्रकार sz = 0;
	dm_block_t nr_मुक्त_metadata_blocks = 0;
	dm_block_t nr_metadata_blocks = 0;
	अक्षर buf[BDEVNAME_SIZE];
	काष्ठा clone *clone = ti->निजी;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		अगर (get_clone_mode(clone) == CM_FAIL) अणु
			DMEMIT("Fail");
			अवरोध;
		पूर्ण

		/* Commit to ensure statistics aren't out-of-date */
		अगर (!(status_flags & DM_STATUS_NOFLUSH_FLAG) && !dm_suspended(ti))
			(व्योम) commit_metadata(clone, शून्य);

		r = dm_clone_get_मुक्त_metadata_block_count(clone->cmd, &nr_मुक्त_metadata_blocks);

		अगर (r) अणु
			DMERR("%s: dm_clone_get_free_metadata_block_count returned %d",
			      clone_device_name(clone), r);
			जाओ error;
		पूर्ण

		r = dm_clone_get_metadata_dev_size(clone->cmd, &nr_metadata_blocks);

		अगर (r) अणु
			DMERR("%s: dm_clone_get_metadata_dev_size returned %d",
			      clone_device_name(clone), r);
			जाओ error;
		पूर्ण

		DMEMIT("%u %llu/%llu %llu %u/%lu %u ",
		       DM_CLONE_METADATA_BLOCK_SIZE,
		       (अचिन्हित दीर्घ दीर्घ)(nr_metadata_blocks - nr_मुक्त_metadata_blocks),
		       (अचिन्हित दीर्घ दीर्घ)nr_metadata_blocks,
		       (अचिन्हित दीर्घ दीर्घ)clone->region_size,
		       dm_clone_nr_of_hydrated_regions(clone->cmd),
		       clone->nr_regions,
		       atomic_पढ़ो(&clone->hydrations_in_flight));

		emit_flags(clone, result, maxlen, &sz);
		emit_core_args(clone, result, maxlen, &sz);

		चयन (get_clone_mode(clone)) अणु
		हाल CM_WRITE:
			DMEMIT("rw");
			अवरोध;
		हाल CM_READ_ONLY:
			DMEMIT("ro");
			अवरोध;
		हाल CM_FAIL:
			DMEMIT("Fail");
		पूर्ण

		अवरोध;

	हाल STATUSTYPE_TABLE:
		क्रमmat_dev_t(buf, clone->metadata_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);

		क्रमmat_dev_t(buf, clone->dest_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);

		क्रमmat_dev_t(buf, clone->source_dev->bdev->bd_dev);
		DMEMIT("%s", buf);

		क्रम (i = 0; i < clone->nr_ctr_args; i++)
			DMEMIT(" %s", clone->ctr_args[i]);
	पूर्ण

	वापस;

error:
	DMEMIT("Error");
पूर्ण

अटल sector_t get_dev_size(काष्ठा dm_dev *dev)
अणु
	वापस i_size_पढ़ो(dev->bdev->bd_inode) >> SECTOR_SHIFT;
पूर्ण

/*---------------------------------------------------------------------------*/

/*
 * Conकाष्ठा a clone device mapping:
 *
 * clone <metadata dev> <destination dev> <source dev> <region size>
 *	[<#feature args> [<feature arg>]* [<#core args> [key value]*]]
 *
 * metadata dev: Fast device holding the persistent metadata
 * destination dev: The destination device, which will become a clone of the
 *                  source device
 * source dev: The पढ़ो-only source device that माला_लो cloned
 * region size: dm-clone unit size in sectors
 *
 * #feature args: Number of feature arguments passed
 * feature args: E.g. no_hydration, no_discard_passकरोwn
 *
 * #core arguments: An even number of core arguments
 * core arguments: Key/value pairs क्रम tuning the core
 *		   E.g. 'hydration_threshold 256'
 */
अटल पूर्णांक parse_feature_args(काष्ठा dm_arg_set *as, काष्ठा clone *clone)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक argc;
	स्थिर अक्षर *arg_name;
	काष्ठा dm_target *ti = clone->ti;

	स्थिर काष्ठा dm_arg args = अणु
		.min = 0,
		.max = 2,
		.error = "Invalid number of feature arguments"
	पूर्ण;

	/* No feature arguments supplied */
	अगर (!as->argc)
		वापस 0;

	r = dm_पढ़ो_arg_group(&args, as, &argc, &ti->error);
	अगर (r)
		वापस r;

	जबतक (argc) अणु
		arg_name = dm_shअगरt_arg(as);
		argc--;

		अगर (!strहालcmp(arg_name, "no_hydration")) अणु
			__clear_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags);
		पूर्ण अन्यथा अगर (!strहालcmp(arg_name, "no_discard_passdown")) अणु
			__clear_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags);
		पूर्ण अन्यथा अणु
			ti->error = "Invalid feature argument";
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_core_args(काष्ठा dm_arg_set *as, काष्ठा clone *clone)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक argc;
	अचिन्हित पूर्णांक value;
	स्थिर अक्षर *arg_name;
	काष्ठा dm_target *ti = clone->ti;

	स्थिर काष्ठा dm_arg args = अणु
		.min = 0,
		.max = 4,
		.error = "Invalid number of core arguments"
	पूर्ण;

	/* Initialize core arguments */
	clone->hydration_batch_size = DEFAULT_HYDRATION_BATCH_SIZE;
	clone->hydration_threshold = DEFAULT_HYDRATION_THRESHOLD;

	/* No core arguments supplied */
	अगर (!as->argc)
		वापस 0;

	r = dm_पढ़ो_arg_group(&args, as, &argc, &ti->error);
	अगर (r)
		वापस r;

	अगर (argc & 1) अणु
		ti->error = "Number of core arguments must be even";
		वापस -EINVAL;
	पूर्ण

	जबतक (argc) अणु
		arg_name = dm_shअगरt_arg(as);
		argc -= 2;

		अगर (!strहालcmp(arg_name, "hydration_threshold")) अणु
			अगर (kstrtouपूर्णांक(dm_shअगरt_arg(as), 10, &value)) अणु
				ti->error = "Invalid value for argument `hydration_threshold'";
				वापस -EINVAL;
			पूर्ण
			clone->hydration_threshold = value;
		पूर्ण अन्यथा अगर (!strहालcmp(arg_name, "hydration_batch_size")) अणु
			अगर (kstrtouपूर्णांक(dm_shअगरt_arg(as), 10, &value)) अणु
				ti->error = "Invalid value for argument `hydration_batch_size'";
				वापस -EINVAL;
			पूर्ण
			clone->hydration_batch_size = value;
		पूर्ण अन्यथा अणु
			ti->error = "Invalid core argument";
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_region_size(काष्ठा clone *clone, काष्ठा dm_arg_set *as, अक्षर **error)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक region_size;
	काष्ठा dm_arg arg;

	arg.min = MIN_REGION_SIZE;
	arg.max = MAX_REGION_SIZE;
	arg.error = "Invalid region size";

	r = dm_पढ़ो_arg(&arg, as, &region_size, error);
	अगर (r)
		वापस r;

	/* Check region size is a घातer of 2 */
	अगर (!is_घातer_of_2(region_size)) अणु
		*error = "Region size is not a power of 2";
		वापस -EINVAL;
	पूर्ण

	/* Validate the region size against the device logical block size */
	अगर (region_size % (bdev_logical_block_size(clone->source_dev->bdev) >> 9) ||
	    region_size % (bdev_logical_block_size(clone->dest_dev->bdev) >> 9)) अणु
		*error = "Region size is not a multiple of device logical block size";
		वापस -EINVAL;
	पूर्ण

	clone->region_size = region_size;

	वापस 0;
पूर्ण

अटल पूर्णांक validate_nr_regions(अचिन्हित दीर्घ n, अक्षर **error)
अणु
	/*
	 * dm_bitset restricts us to 2^32 regions. test_bit & co. restrict us
	 * further to 2^31 regions.
	 */
	अगर (n > (1UL << 31)) अणु
		*error = "Too many regions. Consider increasing the region size";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_metadata_dev(काष्ठा clone *clone, काष्ठा dm_arg_set *as, अक्षर **error)
अणु
	पूर्णांक r;
	sector_t metadata_dev_size;
	अक्षर b[BDEVNAME_SIZE];

	r = dm_get_device(clone->ti, dm_shअगरt_arg(as), FMODE_READ | FMODE_WRITE,
			  &clone->metadata_dev);
	अगर (r) अणु
		*error = "Error opening metadata device";
		वापस r;
	पूर्ण

	metadata_dev_size = get_dev_size(clone->metadata_dev);
	अगर (metadata_dev_size > DM_CLONE_METADATA_MAX_SECTORS_WARNING)
		DMWARN("Metadata device %s is larger than %u sectors: excess space will not be used.",
		       bdevname(clone->metadata_dev->bdev, b), DM_CLONE_METADATA_MAX_SECTORS);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_dest_dev(काष्ठा clone *clone, काष्ठा dm_arg_set *as, अक्षर **error)
अणु
	पूर्णांक r;
	sector_t dest_dev_size;

	r = dm_get_device(clone->ti, dm_shअगरt_arg(as), FMODE_READ | FMODE_WRITE,
			  &clone->dest_dev);
	अगर (r) अणु
		*error = "Error opening destination device";
		वापस r;
	पूर्ण

	dest_dev_size = get_dev_size(clone->dest_dev);
	अगर (dest_dev_size < clone->ti->len) अणु
		dm_put_device(clone->ti, clone->dest_dev);
		*error = "Device size larger than destination device";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_source_dev(काष्ठा clone *clone, काष्ठा dm_arg_set *as, अक्षर **error)
अणु
	पूर्णांक r;
	sector_t source_dev_size;

	r = dm_get_device(clone->ti, dm_shअगरt_arg(as), FMODE_READ,
			  &clone->source_dev);
	अगर (r) अणु
		*error = "Error opening source device";
		वापस r;
	पूर्ण

	source_dev_size = get_dev_size(clone->source_dev);
	अगर (source_dev_size < clone->ti->len) अणु
		dm_put_device(clone->ti, clone->source_dev);
		*error = "Device size larger than source device";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक copy_ctr_args(काष्ठा clone *clone, पूर्णांक argc, स्थिर अक्षर **argv, अक्षर **error)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर **copy;

	copy = kसुस्मृति(argc, माप(*copy), GFP_KERNEL);
	अगर (!copy)
		जाओ error;

	क्रम (i = 0; i < argc; i++) अणु
		copy[i] = kstrdup(argv[i], GFP_KERNEL);

		अगर (!copy[i]) अणु
			जबतक (i--)
				kमुक्त(copy[i]);
			kमुक्त(copy);
			जाओ error;
		पूर्ण
	पूर्ण

	clone->nr_ctr_args = argc;
	clone->ctr_args = copy;
	वापस 0;

error:
	*error = "Failed to allocate memory for table line";
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक clone_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक r;
	sector_t nr_regions;
	काष्ठा clone *clone;
	काष्ठा dm_arg_set as;

	अगर (argc < 4) अणु
		ti->error = "Invalid number of arguments";
		वापस -EINVAL;
	पूर्ण

	as.argc = argc;
	as.argv = argv;

	clone = kzalloc(माप(*clone), GFP_KERNEL);
	अगर (!clone) अणु
		ti->error = "Failed to allocate clone structure";
		वापस -ENOMEM;
	पूर्ण

	clone->ti = ti;

	/* Initialize dm-clone flags */
	__set_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags);
	__set_bit(DM_CLONE_HYDRATION_SUSPENDED, &clone->flags);
	__set_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags);

	r = parse_metadata_dev(clone, &as, &ti->error);
	अगर (r)
		जाओ out_with_clone;

	r = parse_dest_dev(clone, &as, &ti->error);
	अगर (r)
		जाओ out_with_meta_dev;

	r = parse_source_dev(clone, &as, &ti->error);
	अगर (r)
		जाओ out_with_dest_dev;

	r = parse_region_size(clone, &as, &ti->error);
	अगर (r)
		जाओ out_with_source_dev;

	clone->region_shअगरt = __ffs(clone->region_size);
	nr_regions = dm_sector_भाग_up(ti->len, clone->region_size);

	/* Check क्रम overflow */
	अगर (nr_regions != (अचिन्हित दीर्घ)nr_regions) अणु
		ti->error = "Too many regions. Consider increasing the region size";
		r = -EOVERFLOW;
		जाओ out_with_source_dev;
	पूर्ण

	clone->nr_regions = nr_regions;

	r = validate_nr_regions(clone->nr_regions, &ti->error);
	अगर (r)
		जाओ out_with_source_dev;

	r = dm_set_target_max_io_len(ti, clone->region_size);
	अगर (r) अणु
		ti->error = "Failed to set max io len";
		जाओ out_with_source_dev;
	पूर्ण

	r = parse_feature_args(&as, clone);
	अगर (r)
		जाओ out_with_source_dev;

	r = parse_core_args(&as, clone);
	अगर (r)
		जाओ out_with_source_dev;

	/* Load metadata */
	clone->cmd = dm_clone_metadata_खोलो(clone->metadata_dev->bdev, ti->len,
					    clone->region_size);
	अगर (IS_ERR(clone->cmd)) अणु
		ti->error = "Failed to load metadata";
		r = PTR_ERR(clone->cmd);
		जाओ out_with_source_dev;
	पूर्ण

	__set_clone_mode(clone, CM_WRITE);

	अगर (get_clone_mode(clone) != CM_WRITE) अणु
		ti->error = "Unable to get write access to metadata, please check/repair metadata";
		r = -EPERM;
		जाओ out_with_metadata;
	पूर्ण

	clone->last_commit_jअगरfies = jअगरfies;

	/* Allocate hydration hash table */
	r = hash_table_init(clone);
	अगर (r) अणु
		ti->error = "Failed to allocate hydration hash table";
		जाओ out_with_metadata;
	पूर्ण

	atomic_set(&clone->ios_in_flight, 0);
	init_रुकोqueue_head(&clone->hydration_stopped);
	spin_lock_init(&clone->lock);
	bio_list_init(&clone->deferred_bios);
	bio_list_init(&clone->deferred_discard_bios);
	bio_list_init(&clone->deferred_flush_bios);
	bio_list_init(&clone->deferred_flush_completions);
	clone->hydration_offset = 0;
	atomic_set(&clone->hydrations_in_flight, 0);

	clone->wq = alloc_workqueue("dm-" DM_MSG_PREFIX, WQ_MEM_RECLAIM, 0);
	अगर (!clone->wq) अणु
		ti->error = "Failed to allocate workqueue";
		r = -ENOMEM;
		जाओ out_with_ht;
	पूर्ण

	INIT_WORK(&clone->worker, करो_worker);
	INIT_DELAYED_WORK(&clone->waker, करो_waker);

	clone->kcopyd_client = dm_kcopyd_client_create(&dm_kcopyd_throttle);
	अगर (IS_ERR(clone->kcopyd_client)) अणु
		r = PTR_ERR(clone->kcopyd_client);
		जाओ out_with_wq;
	पूर्ण

	r = mempool_init_slab_pool(&clone->hydration_pool, MIN_HYDRATIONS,
				   _hydration_cache);
	अगर (r) अणु
		ti->error = "Failed to create dm_clone_region_hydration memory pool";
		जाओ out_with_kcopyd;
	पूर्ण

	/* Save a copy of the table line */
	r = copy_ctr_args(clone, argc - 3, (स्थिर अक्षर **)argv + 3, &ti->error);
	अगर (r)
		जाओ out_with_mempool;

	mutex_init(&clone->commit_lock);

	/* Enable flushes */
	ti->num_flush_bios = 1;
	ti->flush_supported = true;

	/* Enable discards */
	ti->discards_supported = true;
	ti->num_discard_bios = 1;

	ti->निजी = clone;

	वापस 0;

out_with_mempool:
	mempool_निकास(&clone->hydration_pool);
out_with_kcopyd:
	dm_kcopyd_client_destroy(clone->kcopyd_client);
out_with_wq:
	destroy_workqueue(clone->wq);
out_with_ht:
	hash_table_निकास(clone);
out_with_metadata:
	dm_clone_metadata_बंद(clone->cmd);
out_with_source_dev:
	dm_put_device(ti, clone->source_dev);
out_with_dest_dev:
	dm_put_device(ti, clone->dest_dev);
out_with_meta_dev:
	dm_put_device(ti, clone->metadata_dev);
out_with_clone:
	kमुक्त(clone);

	वापस r;
पूर्ण

अटल व्योम clone_dtr(काष्ठा dm_target *ti)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा clone *clone = ti->निजी;

	mutex_destroy(&clone->commit_lock);

	क्रम (i = 0; i < clone->nr_ctr_args; i++)
		kमुक्त(clone->ctr_args[i]);
	kमुक्त(clone->ctr_args);

	mempool_निकास(&clone->hydration_pool);
	dm_kcopyd_client_destroy(clone->kcopyd_client);
	destroy_workqueue(clone->wq);
	hash_table_निकास(clone);
	dm_clone_metadata_बंद(clone->cmd);
	dm_put_device(ti, clone->source_dev);
	dm_put_device(ti, clone->dest_dev);
	dm_put_device(ti, clone->metadata_dev);

	kमुक्त(clone);
पूर्ण

/*---------------------------------------------------------------------------*/

अटल व्योम clone_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा clone *clone = ti->निजी;

	/*
	 * To successfully suspend the device:
	 *
	 *	- We cancel the delayed work क्रम periodic commits and रुको क्रम
	 *	  it to finish.
	 *
	 *	- We stop the background hydration, i.e. we prevent new region
	 *	  hydrations from starting.
	 *
	 *	- We रुको क्रम any in-flight hydrations to finish.
	 *
	 *	- We flush the workqueue.
	 *
	 *	- We commit the metadata.
	 */
	cancel_delayed_work_sync(&clone->waker);

	set_bit(DM_CLONE_HYDRATION_SUSPENDED, &clone->flags);

	/*
	 * Make sure set_bit() is ordered beक्रमe atomic_पढ़ो(), otherwise we
	 * might race with करो_hydration() and miss some started region
	 * hydrations.
	 *
	 * This is paired with smp_mb__after_atomic() in करो_hydration().
	 */
	smp_mb__after_atomic();

	रुको_event(clone->hydration_stopped, !atomic_पढ़ो(&clone->hydrations_in_flight));
	flush_workqueue(clone->wq);

	(व्योम) commit_metadata(clone, शून्य);
पूर्ण

अटल व्योम clone_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा clone *clone = ti->निजी;

	clear_bit(DM_CLONE_HYDRATION_SUSPENDED, &clone->flags);
	करो_waker(&clone->waker.work);
पूर्ण

अटल bool bdev_supports_discards(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	वापस (q && blk_queue_discard(q));
पूर्ण

/*
 * If discard_passकरोwn was enabled verअगरy that the destination device supports
 * discards. Disable discard_passकरोwn अगर not.
 */
अटल व्योम disable_passकरोwn_अगर_not_supported(काष्ठा clone *clone)
अणु
	काष्ठा block_device *dest_dev = clone->dest_dev->bdev;
	काष्ठा queue_limits *dest_limits = &bdev_get_queue(dest_dev)->limits;
	स्थिर अक्षर *reason = शून्य;
	अक्षर buf[BDEVNAME_SIZE];

	अगर (!test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags))
		वापस;

	अगर (!bdev_supports_discards(dest_dev))
		reason = "discard unsupported";
	अन्यथा अगर (dest_limits->max_discard_sectors < clone->region_size)
		reason = "max discard sectors smaller than a region";

	अगर (reason) अणु
		DMWARN("Destination device (%s) %s: Disabling discard passdown.",
		       bdevname(dest_dev, buf), reason);
		clear_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags);
	पूर्ण
पूर्ण

अटल व्योम set_discard_limits(काष्ठा clone *clone, काष्ठा queue_limits *limits)
अणु
	काष्ठा block_device *dest_bdev = clone->dest_dev->bdev;
	काष्ठा queue_limits *dest_limits = &bdev_get_queue(dest_bdev)->limits;

	अगर (!test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags)) अणु
		/* No passकरोwn is करोne so we set our own भव limits */
		limits->discard_granularity = clone->region_size << SECTOR_SHIFT;
		limits->max_discard_sectors = round_करोwn(अच_पूर्णांक_उच्च >> SECTOR_SHIFT, clone->region_size);
		वापस;
	पूर्ण

	/*
	 * clone_iterate_devices() is stacking both the source and destination
	 * device limits but discards aren't passed to the source device, so
	 * inherit destination's limits.
	 */
	limits->max_discard_sectors = dest_limits->max_discard_sectors;
	limits->max_hw_discard_sectors = dest_limits->max_hw_discard_sectors;
	limits->discard_granularity = dest_limits->discard_granularity;
	limits->discard_alignment = dest_limits->discard_alignment;
	limits->discard_misaligned = dest_limits->discard_misaligned;
	limits->max_discard_segments = dest_limits->max_discard_segments;
पूर्ण

अटल व्योम clone_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा clone *clone = ti->निजी;
	u64 io_opt_sectors = limits->io_opt >> SECTOR_SHIFT;

	/*
	 * If the प्रणाली-determined stacked limits are compatible with
	 * dm-clone's region size (io_opt is a factor) करो not override them.
	 */
	अगर (io_opt_sectors < clone->region_size ||
	    करो_भाग(io_opt_sectors, clone->region_size)) अणु
		blk_limits_io_min(limits, clone->region_size << SECTOR_SHIFT);
		blk_limits_io_opt(limits, clone->region_size << SECTOR_SHIFT);
	पूर्ण

	disable_passकरोwn_अगर_not_supported(clone);
	set_discard_limits(clone, limits);
पूर्ण

अटल पूर्णांक clone_iterate_devices(काष्ठा dm_target *ti,
				 iterate_devices_callout_fn fn, व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा clone *clone = ti->निजी;
	काष्ठा dm_dev *dest_dev = clone->dest_dev;
	काष्ठा dm_dev *source_dev = clone->source_dev;

	ret = fn(ti, source_dev, 0, ti->len, data);
	अगर (!ret)
		ret = fn(ti, dest_dev, 0, ti->len, data);
	वापस ret;
पूर्ण

/*
 * dm-clone message functions.
 */
अटल व्योम set_hydration_threshold(काष्ठा clone *clone, अचिन्हित पूर्णांक nr_regions)
अणु
	WRITE_ONCE(clone->hydration_threshold, nr_regions);

	/*
	 * If user space sets hydration_threshold to zero then the hydration
	 * will stop. If at a later समय the hydration_threshold is increased
	 * we must restart the hydration process by waking up the worker.
	 */
	wake_worker(clone);
पूर्ण

अटल व्योम set_hydration_batch_size(काष्ठा clone *clone, अचिन्हित पूर्णांक nr_regions)
अणु
	WRITE_ONCE(clone->hydration_batch_size, nr_regions);
पूर्ण

अटल व्योम enable_hydration(काष्ठा clone *clone)
अणु
	अगर (!test_and_set_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags))
		wake_worker(clone);
पूर्ण

अटल व्योम disable_hydration(काष्ठा clone *clone)
अणु
	clear_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags);
पूर्ण

अटल पूर्णांक clone_message(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv,
			 अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा clone *clone = ti->निजी;
	अचिन्हित पूर्णांक value;

	अगर (!argc)
		वापस -EINVAL;

	अगर (!strहालcmp(argv[0], "enable_hydration")) अणु
		enable_hydration(clone);
		वापस 0;
	पूर्ण

	अगर (!strहालcmp(argv[0], "disable_hydration")) अणु
		disable_hydration(clone);
		वापस 0;
	पूर्ण

	अगर (argc != 2)
		वापस -EINVAL;

	अगर (!strहालcmp(argv[0], "hydration_threshold")) अणु
		अगर (kstrtouपूर्णांक(argv[1], 10, &value))
			वापस -EINVAL;

		set_hydration_threshold(clone, value);

		वापस 0;
	पूर्ण

	अगर (!strहालcmp(argv[0], "hydration_batch_size")) अणु
		अगर (kstrtouपूर्णांक(argv[1], 10, &value))
			वापस -EINVAL;

		set_hydration_batch_size(clone, value);

		वापस 0;
	पूर्ण

	DMERR("%s: Unsupported message `%s'", clone_device_name(clone), argv[0]);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा target_type clone_target = अणु
	.name = "clone",
	.version = अणु1, 0, 0पूर्ण,
	.module = THIS_MODULE,
	.ctr = clone_ctr,
	.dtr =  clone_dtr,
	.map = clone_map,
	.end_io = clone_endio,
	.postsuspend = clone_postsuspend,
	.resume = clone_resume,
	.status = clone_status,
	.message = clone_message,
	.io_hपूर्णांकs = clone_io_hपूर्णांकs,
	.iterate_devices = clone_iterate_devices,
पूर्ण;

/*---------------------------------------------------------------------------*/

/* Module functions */
अटल पूर्णांक __init dm_clone_init(व्योम)
अणु
	पूर्णांक r;

	_hydration_cache = KMEM_CACHE(dm_clone_region_hydration, 0);
	अगर (!_hydration_cache)
		वापस -ENOMEM;

	r = dm_रेजिस्टर_target(&clone_target);
	अगर (r < 0) अणु
		DMERR("Failed to register clone target");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास dm_clone_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&clone_target);

	kmem_cache_destroy(_hydration_cache);
	_hydration_cache = शून्य;
पूर्ण

/* Module hooks */
module_init(dm_clone_init);
module_निकास(dm_clone_निकास);

MODULE_DESCRIPTION(DM_NAME " clone target");
MODULE_AUTHOR("Nikos Tsironis <ntsironis@arrikto.com>");
MODULE_LICENSE("GPL");
