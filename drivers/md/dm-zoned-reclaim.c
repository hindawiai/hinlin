<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Western Digital Corporation or its affiliates.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-zoned.h"

#समावेश <linux/module.h>

#घोषणा	DM_MSG_PREFIX		"zoned reclaim"

काष्ठा dmz_reclaim अणु
	काष्ठा dmz_metadata     *metadata;

	काष्ठा delayed_work	work;
	काष्ठा workqueue_काष्ठा *wq;

	काष्ठा dm_kcopyd_client	*kc;
	काष्ठा dm_kcopyd_throttle kc_throttle;
	पूर्णांक			kc_err;

	पूर्णांक			dev_idx;

	अचिन्हित दीर्घ		flags;

	/* Last target access समय */
	अचिन्हित दीर्घ		aसमय;
पूर्ण;

/*
 * Reclaim state flags.
 */
क्रमागत अणु
	DMZ_RECLAIM_KCOPY,
पूर्ण;

/*
 * Number of seconds of target BIO inactivity to consider the target idle.
 */
#घोषणा DMZ_IDLE_PERIOD			(10UL * HZ)

/*
 * Percentage of unmapped (मुक्त) अक्रमom zones below which reclaim starts
 * even अगर the target is busy.
 */
#घोषणा DMZ_RECLAIM_LOW_UNMAP_ZONES	30

/*
 * Percentage of unmapped (मुक्त) अक्रमom zones above which reclaim will
 * stop अगर the target is busy.
 */
#घोषणा DMZ_RECLAIM_HIGH_UNMAP_ZONES	50

/*
 * Align a sequential zone ग_लिखो poपूर्णांकer to chunk_block.
 */
अटल पूर्णांक dmz_reclaim_align_wp(काष्ठा dmz_reclaim *zrc, काष्ठा dm_zone *zone,
				sector_t block)
अणु
	काष्ठा dmz_metadata *zmd = zrc->metadata;
	काष्ठा dmz_dev *dev = zone->dev;
	sector_t wp_block = zone->wp_block;
	अचिन्हित पूर्णांक nr_blocks;
	पूर्णांक ret;

	अगर (wp_block == block)
		वापस 0;

	अगर (wp_block > block)
		वापस -EIO;

	/*
	 * Zeroout the space between the ग_लिखो
	 * poपूर्णांकer and the requested position.
	 */
	nr_blocks = block - wp_block;
	ret = blkdev_issue_zeroout(dev->bdev,
				   dmz_start_sect(zmd, zone) + dmz_blk2sect(wp_block),
				   dmz_blk2sect(nr_blocks), GFP_NOIO, 0);
	अगर (ret) अणु
		dmz_dev_err(dev,
			    "Align zone %u wp %llu to %llu (wp+%u) blocks failed %d",
			    zone->id, (अचिन्हित दीर्घ दीर्घ)wp_block,
			    (अचिन्हित दीर्घ दीर्घ)block, nr_blocks, ret);
		dmz_check_bdev(dev);
		वापस ret;
	पूर्ण

	zone->wp_block = block;

	वापस 0;
पूर्ण

/*
 * dm_kcopyd_copy end notअगरication.
 */
अटल व्योम dmz_reclaim_kcopy_end(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err,
				  व्योम *context)
अणु
	काष्ठा dmz_reclaim *zrc = context;

	अगर (पढ़ो_err || ग_लिखो_err)
		zrc->kc_err = -EIO;
	अन्यथा
		zrc->kc_err = 0;

	clear_bit_unlock(DMZ_RECLAIM_KCOPY, &zrc->flags);
	smp_mb__after_atomic();
	wake_up_bit(&zrc->flags, DMZ_RECLAIM_KCOPY);
पूर्ण

/*
 * Copy valid blocks of src_zone पूर्णांकo dst_zone.
 */
अटल पूर्णांक dmz_reclaim_copy(काष्ठा dmz_reclaim *zrc,
			    काष्ठा dm_zone *src_zone, काष्ठा dm_zone *dst_zone)
अणु
	काष्ठा dmz_metadata *zmd = zrc->metadata;
	काष्ठा dm_io_region src, dst;
	sector_t block = 0, end_block;
	sector_t nr_blocks;
	sector_t src_zone_block;
	sector_t dst_zone_block;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	अगर (dmz_is_seq(src_zone))
		end_block = src_zone->wp_block;
	अन्यथा
		end_block = dmz_zone_nr_blocks(zmd);
	src_zone_block = dmz_start_block(zmd, src_zone);
	dst_zone_block = dmz_start_block(zmd, dst_zone);

	अगर (dmz_is_seq(dst_zone))
		set_bit(DM_KCOPYD_WRITE_SEQ, &flags);

	जबतक (block < end_block) अणु
		अगर (src_zone->dev->flags & DMZ_BDEV_DYING)
			वापस -EIO;
		अगर (dst_zone->dev->flags & DMZ_BDEV_DYING)
			वापस -EIO;

		अगर (dmz_reclaim_should_terminate(src_zone))
			वापस -EINTR;

		/* Get a valid region from the source zone */
		ret = dmz_first_valid_block(zmd, src_zone, &block);
		अगर (ret <= 0)
			वापस ret;
		nr_blocks = ret;

		/*
		 * If we are writing in a sequential zone, we must make sure
		 * that ग_लिखोs are sequential. So Zeroout any eventual hole
		 * between ग_लिखोs.
		 */
		अगर (dmz_is_seq(dst_zone)) अणु
			ret = dmz_reclaim_align_wp(zrc, dst_zone, block);
			अगर (ret)
				वापस ret;
		पूर्ण

		src.bdev = src_zone->dev->bdev;
		src.sector = dmz_blk2sect(src_zone_block + block);
		src.count = dmz_blk2sect(nr_blocks);

		dst.bdev = dst_zone->dev->bdev;
		dst.sector = dmz_blk2sect(dst_zone_block + block);
		dst.count = src.count;

		/* Copy the valid region */
		set_bit(DMZ_RECLAIM_KCOPY, &zrc->flags);
		dm_kcopyd_copy(zrc->kc, &src, 1, &dst, flags,
			       dmz_reclaim_kcopy_end, zrc);

		/* Wait क्रम copy to complete */
		रुको_on_bit_io(&zrc->flags, DMZ_RECLAIM_KCOPY,
			       TASK_UNINTERRUPTIBLE);
		अगर (zrc->kc_err)
			वापस zrc->kc_err;

		block += nr_blocks;
		अगर (dmz_is_seq(dst_zone))
			dst_zone->wp_block = block;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Move valid blocks of dzone buffer zone पूर्णांकo dzone (after its ग_लिखो poपूर्णांकer)
 * and मुक्त the buffer zone.
 */
अटल पूर्णांक dmz_reclaim_buf(काष्ठा dmz_reclaim *zrc, काष्ठा dm_zone *dzone)
अणु
	काष्ठा dm_zone *bzone = dzone->bzone;
	sector_t chunk_block = dzone->wp_block;
	काष्ठा dmz_metadata *zmd = zrc->metadata;
	पूर्णांक ret;

	DMDEBUG("(%s/%u): Chunk %u, move buf zone %u (weight %u) to data zone %u (weight %u)",
		dmz_metadata_label(zmd), zrc->dev_idx,
		dzone->chunk, bzone->id, dmz_weight(bzone),
		dzone->id, dmz_weight(dzone));

	/* Flush data zone पूर्णांकo the buffer zone */
	ret = dmz_reclaim_copy(zrc, bzone, dzone);
	अगर (ret < 0)
		वापस ret;

	dmz_lock_flush(zmd);

	/* Validate copied blocks */
	ret = dmz_merge_valid_blocks(zmd, bzone, dzone, chunk_block);
	अगर (ret == 0) अणु
		/* Free the buffer zone */
		dmz_invalidate_blocks(zmd, bzone, 0, dmz_zone_nr_blocks(zmd));
		dmz_lock_map(zmd);
		dmz_unmap_zone(zmd, bzone);
		dmz_unlock_zone_reclaim(dzone);
		dmz_मुक्त_zone(zmd, bzone);
		dmz_unlock_map(zmd);
	पूर्ण

	dmz_unlock_flush(zmd);

	वापस ret;
पूर्ण

/*
 * Merge valid blocks of dzone पूर्णांकo its buffer zone and मुक्त dzone.
 */
अटल पूर्णांक dmz_reclaim_seq_data(काष्ठा dmz_reclaim *zrc, काष्ठा dm_zone *dzone)
अणु
	अचिन्हित पूर्णांक chunk = dzone->chunk;
	काष्ठा dm_zone *bzone = dzone->bzone;
	काष्ठा dmz_metadata *zmd = zrc->metadata;
	पूर्णांक ret = 0;

	DMDEBUG("(%s/%u): Chunk %u, move data zone %u (weight %u) to buf zone %u (weight %u)",
		dmz_metadata_label(zmd), zrc->dev_idx,
		chunk, dzone->id, dmz_weight(dzone),
		bzone->id, dmz_weight(bzone));

	/* Flush data zone पूर्णांकo the buffer zone */
	ret = dmz_reclaim_copy(zrc, dzone, bzone);
	अगर (ret < 0)
		वापस ret;

	dmz_lock_flush(zmd);

	/* Validate copied blocks */
	ret = dmz_merge_valid_blocks(zmd, dzone, bzone, 0);
	अगर (ret == 0) अणु
		/*
		 * Free the data zone and remap the chunk to
		 * the buffer zone.
		 */
		dmz_invalidate_blocks(zmd, dzone, 0, dmz_zone_nr_blocks(zmd));
		dmz_lock_map(zmd);
		dmz_unmap_zone(zmd, bzone);
		dmz_unmap_zone(zmd, dzone);
		dmz_unlock_zone_reclaim(dzone);
		dmz_मुक्त_zone(zmd, dzone);
		dmz_map_zone(zmd, bzone, chunk);
		dmz_unlock_map(zmd);
	पूर्ण

	dmz_unlock_flush(zmd);

	वापस ret;
पूर्ण

/*
 * Move valid blocks of the अक्रमom data zone dzone पूर्णांकo a मुक्त sequential zone.
 * Once blocks are moved, remap the zone chunk to the sequential zone.
 */
अटल पूर्णांक dmz_reclaim_rnd_data(काष्ठा dmz_reclaim *zrc, काष्ठा dm_zone *dzone)
अणु
	अचिन्हित पूर्णांक chunk = dzone->chunk;
	काष्ठा dm_zone *szone = शून्य;
	काष्ठा dmz_metadata *zmd = zrc->metadata;
	पूर्णांक ret;
	पूर्णांक alloc_flags = DMZ_ALLOC_SEQ;

	/* Get a मुक्त अक्रमom or sequential zone */
	dmz_lock_map(zmd);
again:
	szone = dmz_alloc_zone(zmd, zrc->dev_idx,
			       alloc_flags | DMZ_ALLOC_RECLAIM);
	अगर (!szone && alloc_flags == DMZ_ALLOC_SEQ && dmz_nr_cache_zones(zmd)) अणु
		alloc_flags = DMZ_ALLOC_RND;
		जाओ again;
	पूर्ण
	dmz_unlock_map(zmd);
	अगर (!szone)
		वापस -ENOSPC;

	DMDEBUG("(%s/%u): Chunk %u, move %s zone %u (weight %u) to %s zone %u",
		dmz_metadata_label(zmd), zrc->dev_idx, chunk,
		dmz_is_cache(dzone) ? "cache" : "rnd",
		dzone->id, dmz_weight(dzone),
		dmz_is_rnd(szone) ? "rnd" : "seq", szone->id);

	/* Flush the अक्रमom data zone पूर्णांकo the sequential zone */
	ret = dmz_reclaim_copy(zrc, dzone, szone);

	dmz_lock_flush(zmd);

	अगर (ret == 0) अणु
		/* Validate copied blocks */
		ret = dmz_copy_valid_blocks(zmd, dzone, szone);
	पूर्ण
	अगर (ret) अणु
		/* Free the sequential zone */
		dmz_lock_map(zmd);
		dmz_मुक्त_zone(zmd, szone);
		dmz_unlock_map(zmd);
	पूर्ण अन्यथा अणु
		/* Free the data zone and remap the chunk */
		dmz_invalidate_blocks(zmd, dzone, 0, dmz_zone_nr_blocks(zmd));
		dmz_lock_map(zmd);
		dmz_unmap_zone(zmd, dzone);
		dmz_unlock_zone_reclaim(dzone);
		dmz_मुक्त_zone(zmd, dzone);
		dmz_map_zone(zmd, szone, chunk);
		dmz_unlock_map(zmd);
	पूर्ण

	dmz_unlock_flush(zmd);

	वापस ret;
पूर्ण

/*
 * Reclaim an empty zone.
 */
अटल व्योम dmz_reclaim_empty(काष्ठा dmz_reclaim *zrc, काष्ठा dm_zone *dzone)
अणु
	काष्ठा dmz_metadata *zmd = zrc->metadata;

	dmz_lock_flush(zmd);
	dmz_lock_map(zmd);
	dmz_unmap_zone(zmd, dzone);
	dmz_unlock_zone_reclaim(dzone);
	dmz_मुक्त_zone(zmd, dzone);
	dmz_unlock_map(zmd);
	dmz_unlock_flush(zmd);
पूर्ण

/*
 * Test अगर the target device is idle.
 */
अटल अंतरभूत पूर्णांक dmz_target_idle(काष्ठा dmz_reclaim *zrc)
अणु
	वापस समय_is_beक्रमe_jअगरfies(zrc->aसमय + DMZ_IDLE_PERIOD);
पूर्ण

/*
 * Find a candidate zone क्रम reclaim and process it.
 */
अटल पूर्णांक dmz_करो_reclaim(काष्ठा dmz_reclaim *zrc)
अणु
	काष्ठा dmz_metadata *zmd = zrc->metadata;
	काष्ठा dm_zone *dzone;
	काष्ठा dm_zone *rzone;
	अचिन्हित दीर्घ start;
	पूर्णांक ret;

	/* Get a data zone */
	dzone = dmz_get_zone_क्रम_reclaim(zmd, zrc->dev_idx,
					 dmz_target_idle(zrc));
	अगर (!dzone) अणु
		DMDEBUG("(%s/%u): No zone found to reclaim",
			dmz_metadata_label(zmd), zrc->dev_idx);
		वापस -EBUSY;
	पूर्ण
	rzone = dzone;

	start = jअगरfies;
	अगर (dmz_is_cache(dzone) || dmz_is_rnd(dzone)) अणु
		अगर (!dmz_weight(dzone)) अणु
			/* Empty zone */
			dmz_reclaim_empty(zrc, dzone);
			ret = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Reclaim the अक्रमom data zone by moving its
			 * valid data blocks to a मुक्त sequential zone.
			 */
			ret = dmz_reclaim_rnd_data(zrc, dzone);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा dm_zone *bzone = dzone->bzone;
		sector_t chunk_block = 0;

		ret = dmz_first_valid_block(zmd, bzone, &chunk_block);
		अगर (ret < 0)
			जाओ out;

		अगर (ret == 0 || chunk_block >= dzone->wp_block) अणु
			/*
			 * The buffer zone is empty or its valid blocks are
			 * after the data zone ग_लिखो poपूर्णांकer.
			 */
			ret = dmz_reclaim_buf(zrc, dzone);
			rzone = bzone;
		पूर्ण अन्यथा अणु
			/*
			 * Reclaim the data zone by merging it पूर्णांकo the
			 * buffer zone so that the buffer zone itself can
			 * be later reclaimed.
			 */
			ret = dmz_reclaim_seq_data(zrc, dzone);
		पूर्ण
	पूर्ण
out:
	अगर (ret) अणु
		अगर (ret == -EINTR)
			DMDEBUG("(%s/%u): reclaim zone %u interrupted",
				dmz_metadata_label(zmd), zrc->dev_idx,
				rzone->id);
		अन्यथा
			DMDEBUG("(%s/%u): Failed to reclaim zone %u, err %d",
				dmz_metadata_label(zmd), zrc->dev_idx,
				rzone->id, ret);
		dmz_unlock_zone_reclaim(dzone);
		वापस ret;
	पूर्ण

	ret = dmz_flush_metadata(zrc->metadata);
	अगर (ret) अणु
		DMDEBUG("(%s/%u): Metadata flush for zone %u failed, err %d",
			dmz_metadata_label(zmd), zrc->dev_idx, rzone->id, ret);
		वापस ret;
	पूर्ण

	DMDEBUG("(%s/%u): Reclaimed zone %u in %u ms",
		dmz_metadata_label(zmd), zrc->dev_idx,
		rzone->id, jअगरfies_to_msecs(jअगरfies - start));
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक dmz_reclaim_percentage(काष्ठा dmz_reclaim *zrc)
अणु
	काष्ठा dmz_metadata *zmd = zrc->metadata;
	अचिन्हित पूर्णांक nr_cache = dmz_nr_cache_zones(zmd);
	अचिन्हित पूर्णांक nr_unmap, nr_zones;

	अगर (nr_cache) अणु
		nr_zones = nr_cache;
		nr_unmap = dmz_nr_unmap_cache_zones(zmd);
	पूर्ण अन्यथा अणु
		nr_zones = dmz_nr_rnd_zones(zmd, zrc->dev_idx);
		nr_unmap = dmz_nr_unmap_rnd_zones(zmd, zrc->dev_idx);
	पूर्ण
	अगर (nr_unmap <= 1)
		वापस 0;
	वापस nr_unmap * 100 / nr_zones;
पूर्ण

/*
 * Test अगर reclaim is necessary.
 */
अटल bool dmz_should_reclaim(काष्ठा dmz_reclaim *zrc, अचिन्हित पूर्णांक p_unmap)
अणु
	अचिन्हित पूर्णांक nr_reclaim;

	nr_reclaim = dmz_nr_rnd_zones(zrc->metadata, zrc->dev_idx);

	अगर (dmz_nr_cache_zones(zrc->metadata)) अणु
		/*
		 * The first device in a multi-device
		 * setup only contains cache zones, so
		 * never start reclaim there.
		 */
		अगर (zrc->dev_idx == 0)
			वापस false;
		nr_reclaim += dmz_nr_cache_zones(zrc->metadata);
	पूर्ण

	/* Reclaim when idle */
	अगर (dmz_target_idle(zrc) && nr_reclaim)
		वापस true;

	/* If there are still plenty of cache zones, करो not reclaim */
	अगर (p_unmap >= DMZ_RECLAIM_HIGH_UNMAP_ZONES)
		वापस false;

	/*
	 * If the percentage of unmapped cache zones is low,
	 * reclaim even अगर the target is busy.
	 */
	वापस p_unmap <= DMZ_RECLAIM_LOW_UNMAP_ZONES;
पूर्ण

/*
 * Reclaim work function.
 */
अटल व्योम dmz_reclaim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dmz_reclaim *zrc = container_of(work, काष्ठा dmz_reclaim, work.work);
	काष्ठा dmz_metadata *zmd = zrc->metadata;
	अचिन्हित पूर्णांक p_unmap;
	पूर्णांक ret;

	अगर (dmz_dev_is_dying(zmd))
		वापस;

	p_unmap = dmz_reclaim_percentage(zrc);
	अगर (!dmz_should_reclaim(zrc, p_unmap)) अणु
		mod_delayed_work(zrc->wq, &zrc->work, DMZ_IDLE_PERIOD);
		वापस;
	पूर्ण

	/*
	 * We need to start reclaiming अक्रमom zones: set up zone copy
	 * throttling to either go fast अगर we are very low on अक्रमom zones
	 * and slower अगर there are still some मुक्त अक्रमom zones to aव्योम
	 * as much as possible to negatively impact the user workload.
	 */
	अगर (dmz_target_idle(zrc) || p_unmap < DMZ_RECLAIM_LOW_UNMAP_ZONES / 2) अणु
		/* Idle or very low percentage: go fast */
		zrc->kc_throttle.throttle = 100;
	पूर्ण अन्यथा अणु
		/* Busy but we still have some अक्रमom zone: throttle */
		zrc->kc_throttle.throttle = min(75U, 100U - p_unmap / 2);
	पूर्ण

	DMDEBUG("(%s/%u): Reclaim (%u): %s, %u%% free zones (%u/%u cache %u/%u random)",
		dmz_metadata_label(zmd), zrc->dev_idx,
		zrc->kc_throttle.throttle,
		(dmz_target_idle(zrc) ? "Idle" : "Busy"),
		p_unmap, dmz_nr_unmap_cache_zones(zmd),
		dmz_nr_cache_zones(zmd),
		dmz_nr_unmap_rnd_zones(zmd, zrc->dev_idx),
		dmz_nr_rnd_zones(zmd, zrc->dev_idx));

	ret = dmz_करो_reclaim(zrc);
	अगर (ret && ret != -EINTR) अणु
		अगर (!dmz_check_dev(zmd))
			वापस;
	पूर्ण

	dmz_schedule_reclaim(zrc);
पूर्ण

/*
 * Initialize reclaim.
 */
पूर्णांक dmz_ctr_reclaim(काष्ठा dmz_metadata *zmd,
		    काष्ठा dmz_reclaim **reclaim, पूर्णांक idx)
अणु
	काष्ठा dmz_reclaim *zrc;
	पूर्णांक ret;

	zrc = kzalloc(माप(काष्ठा dmz_reclaim), GFP_KERNEL);
	अगर (!zrc)
		वापस -ENOMEM;

	zrc->metadata = zmd;
	zrc->aसमय = jअगरfies;
	zrc->dev_idx = idx;

	/* Reclaim kcopyd client */
	zrc->kc = dm_kcopyd_client_create(&zrc->kc_throttle);
	अगर (IS_ERR(zrc->kc)) अणु
		ret = PTR_ERR(zrc->kc);
		zrc->kc = शून्य;
		जाओ err;
	पूर्ण

	/* Reclaim work */
	INIT_DELAYED_WORK(&zrc->work, dmz_reclaim_work);
	zrc->wq = alloc_ordered_workqueue("dmz_rwq_%s_%d", WQ_MEM_RECLAIM,
					  dmz_metadata_label(zmd), idx);
	अगर (!zrc->wq) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	*reclaim = zrc;
	queue_delayed_work(zrc->wq, &zrc->work, 0);

	वापस 0;
err:
	अगर (zrc->kc)
		dm_kcopyd_client_destroy(zrc->kc);
	kमुक्त(zrc);

	वापस ret;
पूर्ण

/*
 * Terminate reclaim.
 */
व्योम dmz_dtr_reclaim(काष्ठा dmz_reclaim *zrc)
अणु
	cancel_delayed_work_sync(&zrc->work);
	destroy_workqueue(zrc->wq);
	dm_kcopyd_client_destroy(zrc->kc);
	kमुक्त(zrc);
पूर्ण

/*
 * Suspend reclaim.
 */
व्योम dmz_suspend_reclaim(काष्ठा dmz_reclaim *zrc)
अणु
	cancel_delayed_work_sync(&zrc->work);
पूर्ण

/*
 * Resume reclaim.
 */
व्योम dmz_resume_reclaim(काष्ठा dmz_reclaim *zrc)
अणु
	queue_delayed_work(zrc->wq, &zrc->work, DMZ_IDLE_PERIOD);
पूर्ण

/*
 * BIO accounting.
 */
व्योम dmz_reclaim_bio_acc(काष्ठा dmz_reclaim *zrc)
अणु
	zrc->aसमय = jअगरfies;
पूर्ण

/*
 * Start reclaim अगर necessary.
 */
व्योम dmz_schedule_reclaim(काष्ठा dmz_reclaim *zrc)
अणु
	अचिन्हित पूर्णांक p_unmap = dmz_reclaim_percentage(zrc);

	अगर (dmz_should_reclaim(zrc, p_unmap))
		mod_delayed_work(zrc->wq, &zrc->work, 0);
पूर्ण
