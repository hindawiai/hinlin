<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Western Digital Corporation or its affiliates.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-zoned.h"

#समावेश <linux/module.h>

#घोषणा	DM_MSG_PREFIX		"zoned"

#घोषणा DMZ_MIN_BIOS		8192

/*
 * Zone BIO context.
 */
काष्ठा dmz_bioctx अणु
	काष्ठा dmz_dev		*dev;
	काष्ठा dm_zone		*zone;
	काष्ठा bio		*bio;
	refcount_t		ref;
पूर्ण;

/*
 * Chunk work descriptor.
 */
काष्ठा dm_chunk_work अणु
	काष्ठा work_काष्ठा	work;
	refcount_t		refcount;
	काष्ठा dmz_target	*target;
	अचिन्हित पूर्णांक		chunk;
	काष्ठा bio_list		bio_list;
पूर्ण;

/*
 * Target descriptor.
 */
काष्ठा dmz_target अणु
	काष्ठा dm_dev		**ddev;
	अचिन्हित पूर्णांक		nr_ddevs;

	अचिन्हित पूर्णांक		flags;

	/* Zoned block device inक्रमmation */
	काष्ठा dmz_dev		*dev;

	/* For metadata handling */
	काष्ठा dmz_metadata     *metadata;

	/* For chunk work */
	काष्ठा radix_tree_root	chunk_rxtree;
	काष्ठा workqueue_काष्ठा *chunk_wq;
	काष्ठा mutex		chunk_lock;

	/* For cloned BIOs to zones */
	काष्ठा bio_set		bio_set;

	/* For flush */
	spinlock_t		flush_lock;
	काष्ठा bio_list		flush_list;
	काष्ठा delayed_work	flush_work;
	काष्ठा workqueue_काष्ठा *flush_wq;
पूर्ण;

/*
 * Flush पूर्णांकervals (seconds).
 */
#घोषणा DMZ_FLUSH_PERIOD	(10 * HZ)

/*
 * Target BIO completion.
 */
अटल अंतरभूत व्योम dmz_bio_endio(काष्ठा bio *bio, blk_status_t status)
अणु
	काष्ठा dmz_bioctx *bioctx =
		dm_per_bio_data(bio, माप(काष्ठा dmz_bioctx));

	अगर (status != BLK_STS_OK && bio->bi_status == BLK_STS_OK)
		bio->bi_status = status;
	अगर (bioctx->dev && bio->bi_status != BLK_STS_OK)
		bioctx->dev->flags |= DMZ_CHECK_BDEV;

	अगर (refcount_dec_and_test(&bioctx->ref)) अणु
		काष्ठा dm_zone *zone = bioctx->zone;

		अगर (zone) अणु
			अगर (bio->bi_status != BLK_STS_OK &&
			    bio_op(bio) == REQ_OP_WRITE &&
			    dmz_is_seq(zone))
				set_bit(DMZ_SEQ_WRITE_ERR, &zone->flags);
			dmz_deactivate_zone(zone);
		पूर्ण
		bio_endio(bio);
	पूर्ण
पूर्ण

/*
 * Completion callback क्रम an पूर्णांकernally cloned target BIO. This terminates the
 * target BIO when there are no more references to its context.
 */
अटल व्योम dmz_clone_endio(काष्ठा bio *clone)
अणु
	काष्ठा dmz_bioctx *bioctx = clone->bi_निजी;
	blk_status_t status = clone->bi_status;

	bio_put(clone);
	dmz_bio_endio(bioctx->bio, status);
पूर्ण

/*
 * Issue a clone of a target BIO. The clone may only partially process the
 * original target BIO.
 */
अटल पूर्णांक dmz_submit_bio(काष्ठा dmz_target *dmz, काष्ठा dm_zone *zone,
			  काष्ठा bio *bio, sector_t chunk_block,
			  अचिन्हित पूर्णांक nr_blocks)
अणु
	काष्ठा dmz_bioctx *bioctx =
		dm_per_bio_data(bio, माप(काष्ठा dmz_bioctx));
	काष्ठा dmz_dev *dev = zone->dev;
	काष्ठा bio *clone;

	अगर (dev->flags & DMZ_BDEV_DYING)
		वापस -EIO;

	clone = bio_clone_fast(bio, GFP_NOIO, &dmz->bio_set);
	अगर (!clone)
		वापस -ENOMEM;

	bio_set_dev(clone, dev->bdev);
	bioctx->dev = dev;
	clone->bi_iter.bi_sector =
		dmz_start_sect(dmz->metadata, zone) + dmz_blk2sect(chunk_block);
	clone->bi_iter.bi_size = dmz_blk2sect(nr_blocks) << SECTOR_SHIFT;
	clone->bi_end_io = dmz_clone_endio;
	clone->bi_निजी = bioctx;

	bio_advance(bio, clone->bi_iter.bi_size);

	refcount_inc(&bioctx->ref);
	submit_bio_noacct(clone);

	अगर (bio_op(bio) == REQ_OP_WRITE && dmz_is_seq(zone))
		zone->wp_block += nr_blocks;

	वापस 0;
पूर्ण

/*
 * Zero out pages of discarded blocks accessed by a पढ़ो BIO.
 */
अटल व्योम dmz_handle_पढ़ो_zero(काष्ठा dmz_target *dmz, काष्ठा bio *bio,
				 sector_t chunk_block, अचिन्हित पूर्णांक nr_blocks)
अणु
	अचिन्हित पूर्णांक size = nr_blocks << DMZ_BLOCK_SHIFT;

	/* Clear nr_blocks */
	swap(bio->bi_iter.bi_size, size);
	zero_fill_bio(bio);
	swap(bio->bi_iter.bi_size, size);

	bio_advance(bio, size);
पूर्ण

/*
 * Process a पढ़ो BIO.
 */
अटल पूर्णांक dmz_handle_पढ़ो(काष्ठा dmz_target *dmz, काष्ठा dm_zone *zone,
			   काष्ठा bio *bio)
अणु
	काष्ठा dmz_metadata *zmd = dmz->metadata;
	sector_t chunk_block = dmz_chunk_block(zmd, dmz_bio_block(bio));
	अचिन्हित पूर्णांक nr_blocks = dmz_bio_blocks(bio);
	sector_t end_block = chunk_block + nr_blocks;
	काष्ठा dm_zone *rzone, *bzone;
	पूर्णांक ret;

	/* Read पूर्णांकo unmapped chunks need only zeroing the BIO buffer */
	अगर (!zone) अणु
		zero_fill_bio(bio);
		वापस 0;
	पूर्ण

	DMDEBUG("(%s): READ chunk %llu -> %s zone %u, block %llu, %u blocks",
		dmz_metadata_label(zmd),
		(अचिन्हित दीर्घ दीर्घ)dmz_bio_chunk(zmd, bio),
		(dmz_is_rnd(zone) ? "RND" :
		 (dmz_is_cache(zone) ? "CACHE" : "SEQ")),
		zone->id,
		(अचिन्हित दीर्घ दीर्घ)chunk_block, nr_blocks);

	/* Check block validity to determine the पढ़ो location */
	bzone = zone->bzone;
	जबतक (chunk_block < end_block) अणु
		nr_blocks = 0;
		अगर (dmz_is_rnd(zone) || dmz_is_cache(zone) ||
		    chunk_block < zone->wp_block) अणु
			/* Test block validity in the data zone */
			ret = dmz_block_valid(zmd, zone, chunk_block);
			अगर (ret < 0)
				वापस ret;
			अगर (ret > 0) अणु
				/* Read data zone blocks */
				nr_blocks = ret;
				rzone = zone;
			पूर्ण
		पूर्ण

		/*
		 * No valid blocks found in the data zone.
		 * Check the buffer zone, अगर there is one.
		 */
		अगर (!nr_blocks && bzone) अणु
			ret = dmz_block_valid(zmd, bzone, chunk_block);
			अगर (ret < 0)
				वापस ret;
			अगर (ret > 0) अणु
				/* Read buffer zone blocks */
				nr_blocks = ret;
				rzone = bzone;
			पूर्ण
		पूर्ण

		अगर (nr_blocks) अणु
			/* Valid blocks found: पढ़ो them */
			nr_blocks = min_t(अचिन्हित पूर्णांक, nr_blocks,
					  end_block - chunk_block);
			ret = dmz_submit_bio(dmz, rzone, bio,
					     chunk_block, nr_blocks);
			अगर (ret)
				वापस ret;
			chunk_block += nr_blocks;
		पूर्ण अन्यथा अणु
			/* No valid block: zeroout the current BIO block */
			dmz_handle_पढ़ो_zero(dmz, bio, chunk_block, 1);
			chunk_block++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write blocks directly in a data zone, at the ग_लिखो poपूर्णांकer.
 * If a buffer zone is asचिन्हित, invalidate the blocks written
 * in place.
 */
अटल पूर्णांक dmz_handle_direct_ग_लिखो(काष्ठा dmz_target *dmz,
				   काष्ठा dm_zone *zone, काष्ठा bio *bio,
				   sector_t chunk_block,
				   अचिन्हित पूर्णांक nr_blocks)
अणु
	काष्ठा dmz_metadata *zmd = dmz->metadata;
	काष्ठा dm_zone *bzone = zone->bzone;
	पूर्णांक ret;

	अगर (dmz_is_पढ़ोonly(zone))
		वापस -EROFS;

	/* Submit ग_लिखो */
	ret = dmz_submit_bio(dmz, zone, bio, chunk_block, nr_blocks);
	अगर (ret)
		वापस ret;

	/*
	 * Validate the blocks in the data zone and invalidate
	 * in the buffer zone, अगर there is one.
	 */
	ret = dmz_validate_blocks(zmd, zone, chunk_block, nr_blocks);
	अगर (ret == 0 && bzone)
		ret = dmz_invalidate_blocks(zmd, bzone, chunk_block, nr_blocks);

	वापस ret;
पूर्ण

/*
 * Write blocks in the buffer zone of @zone.
 * If no buffer zone is asचिन्हित yet, get one.
 * Called with @zone ग_लिखो locked.
 */
अटल पूर्णांक dmz_handle_buffered_ग_लिखो(काष्ठा dmz_target *dmz,
				     काष्ठा dm_zone *zone, काष्ठा bio *bio,
				     sector_t chunk_block,
				     अचिन्हित पूर्णांक nr_blocks)
अणु
	काष्ठा dmz_metadata *zmd = dmz->metadata;
	काष्ठा dm_zone *bzone;
	पूर्णांक ret;

	/* Get the buffer zone. One will be allocated अगर needed */
	bzone = dmz_get_chunk_buffer(zmd, zone);
	अगर (IS_ERR(bzone))
		वापस PTR_ERR(bzone);

	अगर (dmz_is_पढ़ोonly(bzone))
		वापस -EROFS;

	/* Submit ग_लिखो */
	ret = dmz_submit_bio(dmz, bzone, bio, chunk_block, nr_blocks);
	अगर (ret)
		वापस ret;

	/*
	 * Validate the blocks in the buffer zone
	 * and invalidate in the data zone.
	 */
	ret = dmz_validate_blocks(zmd, bzone, chunk_block, nr_blocks);
	अगर (ret == 0 && chunk_block < zone->wp_block)
		ret = dmz_invalidate_blocks(zmd, zone, chunk_block, nr_blocks);

	वापस ret;
पूर्ण

/*
 * Process a ग_लिखो BIO.
 */
अटल पूर्णांक dmz_handle_ग_लिखो(काष्ठा dmz_target *dmz, काष्ठा dm_zone *zone,
			    काष्ठा bio *bio)
अणु
	काष्ठा dmz_metadata *zmd = dmz->metadata;
	sector_t chunk_block = dmz_chunk_block(zmd, dmz_bio_block(bio));
	अचिन्हित पूर्णांक nr_blocks = dmz_bio_blocks(bio);

	अगर (!zone)
		वापस -ENOSPC;

	DMDEBUG("(%s): WRITE chunk %llu -> %s zone %u, block %llu, %u blocks",
		dmz_metadata_label(zmd),
		(अचिन्हित दीर्घ दीर्घ)dmz_bio_chunk(zmd, bio),
		(dmz_is_rnd(zone) ? "RND" :
		 (dmz_is_cache(zone) ? "CACHE" : "SEQ")),
		zone->id,
		(अचिन्हित दीर्घ दीर्घ)chunk_block, nr_blocks);

	अगर (dmz_is_rnd(zone) || dmz_is_cache(zone) ||
	    chunk_block == zone->wp_block) अणु
		/*
		 * zone is a अक्रमom zone or it is a sequential zone
		 * and the BIO is aligned to the zone ग_लिखो poपूर्णांकer:
		 * direct ग_लिखो the zone.
		 */
		वापस dmz_handle_direct_ग_लिखो(dmz, zone, bio,
					       chunk_block, nr_blocks);
	पूर्ण

	/*
	 * This is an unaligned ग_लिखो in a sequential zone:
	 * use buffered ग_लिखो.
	 */
	वापस dmz_handle_buffered_ग_लिखो(dmz, zone, bio, chunk_block, nr_blocks);
पूर्ण

/*
 * Process a discard BIO.
 */
अटल पूर्णांक dmz_handle_discard(काष्ठा dmz_target *dmz, काष्ठा dm_zone *zone,
			      काष्ठा bio *bio)
अणु
	काष्ठा dmz_metadata *zmd = dmz->metadata;
	sector_t block = dmz_bio_block(bio);
	अचिन्हित पूर्णांक nr_blocks = dmz_bio_blocks(bio);
	sector_t chunk_block = dmz_chunk_block(zmd, block);
	पूर्णांक ret = 0;

	/* For unmapped chunks, there is nothing to करो */
	अगर (!zone)
		वापस 0;

	अगर (dmz_is_पढ़ोonly(zone))
		वापस -EROFS;

	DMDEBUG("(%s): DISCARD chunk %llu -> zone %u, block %llu, %u blocks",
		dmz_metadata_label(dmz->metadata),
		(अचिन्हित दीर्घ दीर्घ)dmz_bio_chunk(zmd, bio),
		zone->id,
		(अचिन्हित दीर्घ दीर्घ)chunk_block, nr_blocks);

	/*
	 * Invalidate blocks in the data zone and its
	 * buffer zone अगर one is mapped.
	 */
	अगर (dmz_is_rnd(zone) || dmz_is_cache(zone) ||
	    chunk_block < zone->wp_block)
		ret = dmz_invalidate_blocks(zmd, zone, chunk_block, nr_blocks);
	अगर (ret == 0 && zone->bzone)
		ret = dmz_invalidate_blocks(zmd, zone->bzone,
					    chunk_block, nr_blocks);
	वापस ret;
पूर्ण

/*
 * Process a BIO.
 */
अटल व्योम dmz_handle_bio(काष्ठा dmz_target *dmz, काष्ठा dm_chunk_work *cw,
			   काष्ठा bio *bio)
अणु
	काष्ठा dmz_bioctx *bioctx =
		dm_per_bio_data(bio, माप(काष्ठा dmz_bioctx));
	काष्ठा dmz_metadata *zmd = dmz->metadata;
	काष्ठा dm_zone *zone;
	पूर्णांक ret;

	dmz_lock_metadata(zmd);

	/*
	 * Get the data zone mapping the chunk. There may be no
	 * mapping क्रम पढ़ो and discard. If a mapping is obtained,
	 + the zone वापसed will be set to active state.
	 */
	zone = dmz_get_chunk_mapping(zmd, dmz_bio_chunk(zmd, bio),
				     bio_op(bio));
	अगर (IS_ERR(zone)) अणु
		ret = PTR_ERR(zone);
		जाओ out;
	पूर्ण

	/* Process the BIO */
	अगर (zone) अणु
		dmz_activate_zone(zone);
		bioctx->zone = zone;
		dmz_reclaim_bio_acc(zone->dev->reclaim);
	पूर्ण

	चयन (bio_op(bio)) अणु
	हाल REQ_OP_READ:
		ret = dmz_handle_पढ़ो(dmz, zone, bio);
		अवरोध;
	हाल REQ_OP_WRITE:
		ret = dmz_handle_ग_लिखो(dmz, zone, bio);
		अवरोध;
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_WRITE_ZEROES:
		ret = dmz_handle_discard(dmz, zone, bio);
		अवरोध;
	शेष:
		DMERR("(%s): Unsupported BIO operation 0x%x",
		      dmz_metadata_label(dmz->metadata), bio_op(bio));
		ret = -EIO;
	पूर्ण

	/*
	 * Release the chunk mapping. This will check that the mapping
	 * is still valid, that is, that the zone used still has valid blocks.
	 */
	अगर (zone)
		dmz_put_chunk_mapping(zmd, zone);
out:
	dmz_bio_endio(bio, त्रुटि_सं_to_blk_status(ret));

	dmz_unlock_metadata(zmd);
पूर्ण

/*
 * Increment a chunk reference counter.
 */
अटल अंतरभूत व्योम dmz_get_chunk_work(काष्ठा dm_chunk_work *cw)
अणु
	refcount_inc(&cw->refcount);
पूर्ण

/*
 * Decrement a chunk work reference count and
 * मुक्त it अगर it becomes 0.
 */
अटल व्योम dmz_put_chunk_work(काष्ठा dm_chunk_work *cw)
अणु
	अगर (refcount_dec_and_test(&cw->refcount)) अणु
		WARN_ON(!bio_list_empty(&cw->bio_list));
		radix_tree_delete(&cw->target->chunk_rxtree, cw->chunk);
		kमुक्त(cw);
	पूर्ण
पूर्ण

/*
 * Chunk BIO work function.
 */
अटल व्योम dmz_chunk_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_chunk_work *cw = container_of(work, काष्ठा dm_chunk_work, work);
	काष्ठा dmz_target *dmz = cw->target;
	काष्ठा bio *bio;

	mutex_lock(&dmz->chunk_lock);

	/* Process the chunk BIOs */
	जबतक ((bio = bio_list_pop(&cw->bio_list))) अणु
		mutex_unlock(&dmz->chunk_lock);
		dmz_handle_bio(dmz, cw, bio);
		mutex_lock(&dmz->chunk_lock);
		dmz_put_chunk_work(cw);
	पूर्ण

	/* Queueing the work incremented the work refcount */
	dmz_put_chunk_work(cw);

	mutex_unlock(&dmz->chunk_lock);
पूर्ण

/*
 * Flush work.
 */
अटल व्योम dmz_flush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dmz_target *dmz = container_of(work, काष्ठा dmz_target, flush_work.work);
	काष्ठा bio *bio;
	पूर्णांक ret;

	/* Flush dirty metadata blocks */
	ret = dmz_flush_metadata(dmz->metadata);
	अगर (ret)
		DMDEBUG("(%s): Metadata flush failed, rc=%d",
			dmz_metadata_label(dmz->metadata), ret);

	/* Process queued flush requests */
	जबतक (1) अणु
		spin_lock(&dmz->flush_lock);
		bio = bio_list_pop(&dmz->flush_list);
		spin_unlock(&dmz->flush_lock);

		अगर (!bio)
			अवरोध;

		dmz_bio_endio(bio, त्रुटि_सं_to_blk_status(ret));
	पूर्ण

	queue_delayed_work(dmz->flush_wq, &dmz->flush_work, DMZ_FLUSH_PERIOD);
पूर्ण

/*
 * Get a chunk work and start it to process a new BIO.
 * If the BIO chunk has no work yet, create one.
 */
अटल पूर्णांक dmz_queue_chunk_work(काष्ठा dmz_target *dmz, काष्ठा bio *bio)
अणु
	अचिन्हित पूर्णांक chunk = dmz_bio_chunk(dmz->metadata, bio);
	काष्ठा dm_chunk_work *cw;
	पूर्णांक ret = 0;

	mutex_lock(&dmz->chunk_lock);

	/* Get the BIO chunk work. If one is not active yet, create one */
	cw = radix_tree_lookup(&dmz->chunk_rxtree, chunk);
	अगर (cw) अणु
		dmz_get_chunk_work(cw);
	पूर्ण अन्यथा अणु
		/* Create a new chunk work */
		cw = kदो_स्मृति(माप(काष्ठा dm_chunk_work), GFP_NOIO);
		अगर (unlikely(!cw)) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		INIT_WORK(&cw->work, dmz_chunk_work);
		refcount_set(&cw->refcount, 1);
		cw->target = dmz;
		cw->chunk = chunk;
		bio_list_init(&cw->bio_list);

		ret = radix_tree_insert(&dmz->chunk_rxtree, chunk, cw);
		अगर (unlikely(ret)) अणु
			kमुक्त(cw);
			जाओ out;
		पूर्ण
	पूर्ण

	bio_list_add(&cw->bio_list, bio);

	अगर (queue_work(dmz->chunk_wq, &cw->work))
		dmz_get_chunk_work(cw);
out:
	mutex_unlock(&dmz->chunk_lock);
	वापस ret;
पूर्ण

/*
 * Check अगर the backing device is being हटाओd. If it's on the way out,
 * start failing I/O. Reclaim and metadata components also call this
 * function to cleanly पात operation in the event of such failure.
 */
bool dmz_bdev_is_dying(काष्ठा dmz_dev *dmz_dev)
अणु
	अगर (dmz_dev->flags & DMZ_BDEV_DYING)
		वापस true;

	अगर (dmz_dev->flags & DMZ_CHECK_BDEV)
		वापस !dmz_check_bdev(dmz_dev);

	अगर (blk_queue_dying(bdev_get_queue(dmz_dev->bdev))) अणु
		dmz_dev_warn(dmz_dev, "Backing device queue dying");
		dmz_dev->flags |= DMZ_BDEV_DYING;
	पूर्ण

	वापस dmz_dev->flags & DMZ_BDEV_DYING;
पूर्ण

/*
 * Check the backing device availability. This detects such events as
 * backing device going offline due to errors, media removals, etc.
 * This check is less efficient than dmz_bdev_is_dying() and should
 * only be perक्रमmed as a part of error handling.
 */
bool dmz_check_bdev(काष्ठा dmz_dev *dmz_dev)
अणु
	काष्ठा gendisk *disk;

	dmz_dev->flags &= ~DMZ_CHECK_BDEV;

	अगर (dmz_bdev_is_dying(dmz_dev))
		वापस false;

	disk = dmz_dev->bdev->bd_disk;
	अगर (disk->fops->check_events &&
	    disk->fops->check_events(disk, 0) & DISK_EVENT_MEDIA_CHANGE) अणु
		dmz_dev_warn(dmz_dev, "Backing device offline");
		dmz_dev->flags |= DMZ_BDEV_DYING;
	पूर्ण

	वापस !(dmz_dev->flags & DMZ_BDEV_DYING);
पूर्ण

/*
 * Process a new BIO.
 */
अटल पूर्णांक dmz_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	काष्ठा dmz_metadata *zmd = dmz->metadata;
	काष्ठा dmz_bioctx *bioctx = dm_per_bio_data(bio, माप(काष्ठा dmz_bioctx));
	sector_t sector = bio->bi_iter.bi_sector;
	अचिन्हित पूर्णांक nr_sectors = bio_sectors(bio);
	sector_t chunk_sector;
	पूर्णांक ret;

	अगर (dmz_dev_is_dying(zmd))
		वापस DM_MAPIO_KILL;

	DMDEBUG("(%s): BIO op %d sector %llu + %u => chunk %llu, block %llu, %u blocks",
		dmz_metadata_label(zmd),
		bio_op(bio), (अचिन्हित दीर्घ दीर्घ)sector, nr_sectors,
		(अचिन्हित दीर्घ दीर्घ)dmz_bio_chunk(zmd, bio),
		(अचिन्हित दीर्घ दीर्घ)dmz_chunk_block(zmd, dmz_bio_block(bio)),
		(अचिन्हित पूर्णांक)dmz_bio_blocks(bio));

	अगर (!nr_sectors && bio_op(bio) != REQ_OP_WRITE)
		वापस DM_MAPIO_REMAPPED;

	/* The BIO should be block aligned */
	अगर ((nr_sectors & DMZ_BLOCK_SECTORS_MASK) || (sector & DMZ_BLOCK_SECTORS_MASK))
		वापस DM_MAPIO_KILL;

	/* Initialize the BIO context */
	bioctx->dev = शून्य;
	bioctx->zone = शून्य;
	bioctx->bio = bio;
	refcount_set(&bioctx->ref, 1);

	/* Set the BIO pending in the flush list */
	अगर (!nr_sectors && bio_op(bio) == REQ_OP_WRITE) अणु
		spin_lock(&dmz->flush_lock);
		bio_list_add(&dmz->flush_list, bio);
		spin_unlock(&dmz->flush_lock);
		mod_delayed_work(dmz->flush_wq, &dmz->flush_work, 0);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	/* Split zone BIOs to fit entirely पूर्णांकo a zone */
	chunk_sector = sector & (dmz_zone_nr_sectors(zmd) - 1);
	अगर (chunk_sector + nr_sectors > dmz_zone_nr_sectors(zmd))
		dm_accept_partial_bio(bio, dmz_zone_nr_sectors(zmd) - chunk_sector);

	/* Now पढ़ोy to handle this BIO */
	ret = dmz_queue_chunk_work(dmz, bio);
	अगर (ret) अणु
		DMDEBUG("(%s): BIO op %d, can't process chunk %llu, err %i",
			dmz_metadata_label(zmd),
			bio_op(bio), (u64)dmz_bio_chunk(zmd, bio),
			ret);
		वापस DM_MAPIO_REQUEUE;
	पूर्ण

	वापस DM_MAPIO_SUBMITTED;
पूर्ण

/*
 * Get zoned device inक्रमmation.
 */
अटल पूर्णांक dmz_get_zoned_device(काष्ठा dm_target *ti, अक्षर *path,
				पूर्णांक idx, पूर्णांक nr_devs)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	काष्ठा dm_dev *ddev;
	काष्ठा dmz_dev *dev;
	पूर्णांक ret;
	काष्ठा block_device *bdev;

	/* Get the target device */
	ret = dm_get_device(ti, path, dm_table_get_mode(ti->table), &ddev);
	अगर (ret) अणु
		ti->error = "Get target device failed";
		वापस ret;
	पूर्ण

	bdev = ddev->bdev;
	अगर (bdev_zoned_model(bdev) == BLK_ZONED_NONE) अणु
		अगर (nr_devs == 1) अणु
			ti->error = "Invalid regular device";
			जाओ err;
		पूर्ण
		अगर (idx != 0) अणु
			ti->error = "First device must be a regular device";
			जाओ err;
		पूर्ण
		अगर (dmz->ddev[0]) अणु
			ti->error = "Too many regular devices";
			जाओ err;
		पूर्ण
		dev = &dmz->dev[idx];
		dev->flags = DMZ_BDEV_REGULAR;
	पूर्ण अन्यथा अणु
		अगर (dmz->ddev[idx]) अणु
			ti->error = "Too many zoned devices";
			जाओ err;
		पूर्ण
		अगर (nr_devs > 1 && idx == 0) अणु
			ti->error = "First device must be a regular device";
			जाओ err;
		पूर्ण
		dev = &dmz->dev[idx];
	पूर्ण
	dev->bdev = bdev;
	dev->dev_idx = idx;
	(व्योम)bdevname(dev->bdev, dev->name);

	dev->capacity = i_size_पढ़ो(bdev->bd_inode) >> SECTOR_SHIFT;
	अगर (ti->begin) अणु
		ti->error = "Partial mapping is not supported";
		जाओ err;
	पूर्ण

	dmz->ddev[idx] = ddev;

	वापस 0;
err:
	dm_put_device(ti, ddev);
	वापस -EINVAL;
पूर्ण

/*
 * Cleanup zoned device inक्रमmation.
 */
अटल व्योम dmz_put_zoned_device(काष्ठा dm_target *ti)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < dmz->nr_ddevs; i++) अणु
		अगर (dmz->ddev[i]) अणु
			dm_put_device(ti, dmz->ddev[i]);
			dmz->ddev[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dmz_fixup_devices(काष्ठा dm_target *ti)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	काष्ठा dmz_dev *reg_dev, *zoned_dev;
	काष्ठा request_queue *q;
	sector_t zone_nr_sectors = 0;
	पूर्णांक i;

	/*
	 * When we have more than on devices, the first one must be a
	 * regular block device and the others zoned block devices.
	 */
	अगर (dmz->nr_ddevs > 1) अणु
		reg_dev = &dmz->dev[0];
		अगर (!(reg_dev->flags & DMZ_BDEV_REGULAR)) अणु
			ti->error = "Primary disk is not a regular device";
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 1; i < dmz->nr_ddevs; i++) अणु
			zoned_dev = &dmz->dev[i];
			अगर (zoned_dev->flags & DMZ_BDEV_REGULAR) अणु
				ti->error = "Secondary disk is not a zoned device";
				वापस -EINVAL;
			पूर्ण
			q = bdev_get_queue(zoned_dev->bdev);
			अगर (zone_nr_sectors &&
			    zone_nr_sectors != blk_queue_zone_sectors(q)) अणु
				ti->error = "Zone nr sectors mismatch";
				वापस -EINVAL;
			पूर्ण
			zone_nr_sectors = blk_queue_zone_sectors(q);
			zoned_dev->zone_nr_sectors = zone_nr_sectors;
			zoned_dev->nr_zones =
				blkdev_nr_zones(zoned_dev->bdev->bd_disk);
		पूर्ण
	पूर्ण अन्यथा अणु
		reg_dev = शून्य;
		zoned_dev = &dmz->dev[0];
		अगर (zoned_dev->flags & DMZ_BDEV_REGULAR) अणु
			ti->error = "Disk is not a zoned device";
			वापस -EINVAL;
		पूर्ण
		q = bdev_get_queue(zoned_dev->bdev);
		zoned_dev->zone_nr_sectors = blk_queue_zone_sectors(q);
		zoned_dev->nr_zones = blkdev_nr_zones(zoned_dev->bdev->bd_disk);
	पूर्ण

	अगर (reg_dev) अणु
		sector_t zone_offset;

		reg_dev->zone_nr_sectors = zone_nr_sectors;
		reg_dev->nr_zones =
			DIV_ROUND_UP_SECTOR_T(reg_dev->capacity,
					      reg_dev->zone_nr_sectors);
		reg_dev->zone_offset = 0;
		zone_offset = reg_dev->nr_zones;
		क्रम (i = 1; i < dmz->nr_ddevs; i++) अणु
			dmz->dev[i].zone_offset = zone_offset;
			zone_offset += dmz->dev[i].nr_zones;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Setup target.
 */
अटल पूर्णांक dmz_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा dmz_target *dmz;
	पूर्णांक ret, i;

	/* Check arguments */
	अगर (argc < 1) अणु
		ti->error = "Invalid argument count";
		वापस -EINVAL;
	पूर्ण

	/* Allocate and initialize the target descriptor */
	dmz = kzalloc(माप(काष्ठा dmz_target), GFP_KERNEL);
	अगर (!dmz) अणु
		ti->error = "Unable to allocate the zoned target descriptor";
		वापस -ENOMEM;
	पूर्ण
	dmz->dev = kसुस्मृति(argc, माप(काष्ठा dmz_dev), GFP_KERNEL);
	अगर (!dmz->dev) अणु
		ti->error = "Unable to allocate the zoned device descriptors";
		kमुक्त(dmz);
		वापस -ENOMEM;
	पूर्ण
	dmz->ddev = kसुस्मृति(argc, माप(काष्ठा dm_dev *), GFP_KERNEL);
	अगर (!dmz->ddev) अणु
		ti->error = "Unable to allocate the dm device descriptors";
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	dmz->nr_ddevs = argc;

	ti->निजी = dmz;

	/* Get the target zoned block device */
	क्रम (i = 0; i < argc; i++) अणु
		ret = dmz_get_zoned_device(ti, argv[i], i, argc);
		अगर (ret)
			जाओ err_dev;
	पूर्ण
	ret = dmz_fixup_devices(ti);
	अगर (ret)
		जाओ err_dev;

	/* Initialize metadata */
	ret = dmz_ctr_metadata(dmz->dev, argc, &dmz->metadata,
			       dm_table_device_name(ti->table));
	अगर (ret) अणु
		ti->error = "Metadata initialization failed";
		जाओ err_dev;
	पूर्ण

	/* Set target (no ग_लिखो same support) */
	ti->max_io_len = dmz_zone_nr_sectors(dmz->metadata);
	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->num_ग_लिखो_zeroes_bios = 1;
	ti->per_io_data_size = माप(काष्ठा dmz_bioctx);
	ti->flush_supported = true;
	ti->discards_supported = true;

	/* The exposed capacity is the number of chunks that can be mapped */
	ti->len = (sector_t)dmz_nr_chunks(dmz->metadata) <<
		dmz_zone_nr_sectors_shअगरt(dmz->metadata);

	/* Zone BIO */
	ret = bioset_init(&dmz->bio_set, DMZ_MIN_BIOS, 0, 0);
	अगर (ret) अणु
		ti->error = "Create BIO set failed";
		जाओ err_meta;
	पूर्ण

	/* Chunk BIO work */
	mutex_init(&dmz->chunk_lock);
	INIT_RADIX_TREE(&dmz->chunk_rxtree, GFP_NOIO);
	dmz->chunk_wq = alloc_workqueue("dmz_cwq_%s",
					WQ_MEM_RECLAIM | WQ_UNBOUND, 0,
					dmz_metadata_label(dmz->metadata));
	अगर (!dmz->chunk_wq) अणु
		ti->error = "Create chunk workqueue failed";
		ret = -ENOMEM;
		जाओ err_bio;
	पूर्ण

	/* Flush work */
	spin_lock_init(&dmz->flush_lock);
	bio_list_init(&dmz->flush_list);
	INIT_DELAYED_WORK(&dmz->flush_work, dmz_flush_work);
	dmz->flush_wq = alloc_ordered_workqueue("dmz_fwq_%s", WQ_MEM_RECLAIM,
						dmz_metadata_label(dmz->metadata));
	अगर (!dmz->flush_wq) अणु
		ti->error = "Create flush workqueue failed";
		ret = -ENOMEM;
		जाओ err_cwq;
	पूर्ण
	mod_delayed_work(dmz->flush_wq, &dmz->flush_work, DMZ_FLUSH_PERIOD);

	/* Initialize reclaim */
	क्रम (i = 0; i < dmz->nr_ddevs; i++) अणु
		ret = dmz_ctr_reclaim(dmz->metadata, &dmz->dev[i].reclaim, i);
		अगर (ret) अणु
			ti->error = "Zone reclaim initialization failed";
			जाओ err_fwq;
		पूर्ण
	पूर्ण

	DMINFO("(%s): Target device: %llu 512-byte logical sectors (%llu blocks)",
	       dmz_metadata_label(dmz->metadata),
	       (अचिन्हित दीर्घ दीर्घ)ti->len,
	       (अचिन्हित दीर्घ दीर्घ)dmz_sect2blk(ti->len));

	वापस 0;
err_fwq:
	destroy_workqueue(dmz->flush_wq);
err_cwq:
	destroy_workqueue(dmz->chunk_wq);
err_bio:
	mutex_destroy(&dmz->chunk_lock);
	bioset_निकास(&dmz->bio_set);
err_meta:
	dmz_dtr_metadata(dmz->metadata);
err_dev:
	dmz_put_zoned_device(ti);
err:
	kमुक्त(dmz->dev);
	kमुक्त(dmz);

	वापस ret;
पूर्ण

/*
 * Cleanup target.
 */
अटल व्योम dmz_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	पूर्णांक i;

	flush_workqueue(dmz->chunk_wq);
	destroy_workqueue(dmz->chunk_wq);

	क्रम (i = 0; i < dmz->nr_ddevs; i++)
		dmz_dtr_reclaim(dmz->dev[i].reclaim);

	cancel_delayed_work_sync(&dmz->flush_work);
	destroy_workqueue(dmz->flush_wq);

	(व्योम) dmz_flush_metadata(dmz->metadata);

	dmz_dtr_metadata(dmz->metadata);

	bioset_निकास(&dmz->bio_set);

	dmz_put_zoned_device(ti);

	mutex_destroy(&dmz->chunk_lock);

	kमुक्त(dmz->dev);
	kमुक्त(dmz);
पूर्ण

/*
 * Setup target request queue limits.
 */
अटल व्योम dmz_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	अचिन्हित पूर्णांक chunk_sectors = dmz_zone_nr_sectors(dmz->metadata);

	limits->logical_block_size = DMZ_BLOCK_SIZE;
	limits->physical_block_size = DMZ_BLOCK_SIZE;

	blk_limits_io_min(limits, DMZ_BLOCK_SIZE);
	blk_limits_io_opt(limits, DMZ_BLOCK_SIZE);

	limits->discard_alignment = DMZ_BLOCK_SIZE;
	limits->discard_granularity = DMZ_BLOCK_SIZE;
	limits->max_discard_sectors = chunk_sectors;
	limits->max_hw_discard_sectors = chunk_sectors;
	limits->max_ग_लिखो_zeroes_sectors = chunk_sectors;

	/* FS hपूर्णांक to try to align to the device zone size */
	limits->chunk_sectors = chunk_sectors;
	limits->max_sectors = chunk_sectors;

	/* We are exposing a drive-managed zoned block device */
	limits->zoned = BLK_ZONED_NONE;
पूर्ण

/*
 * Pass on ioctl to the backend device.
 */
अटल पूर्णांक dmz_prepare_ioctl(काष्ठा dm_target *ti, काष्ठा block_device **bdev)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	काष्ठा dmz_dev *dev = &dmz->dev[0];

	अगर (!dmz_check_bdev(dev))
		वापस -EIO;

	*bdev = dev->bdev;

	वापस 0;
पूर्ण

/*
 * Stop works on suspend.
 */
अटल व्योम dmz_suspend(काष्ठा dm_target *ti)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	पूर्णांक i;

	flush_workqueue(dmz->chunk_wq);
	क्रम (i = 0; i < dmz->nr_ddevs; i++)
		dmz_suspend_reclaim(dmz->dev[i].reclaim);
	cancel_delayed_work_sync(&dmz->flush_work);
पूर्ण

/*
 * Restart works on resume or अगर suspend failed.
 */
अटल व्योम dmz_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	पूर्णांक i;

	queue_delayed_work(dmz->flush_wq, &dmz->flush_work, DMZ_FLUSH_PERIOD);
	क्रम (i = 0; i < dmz->nr_ddevs; i++)
		dmz_resume_reclaim(dmz->dev[i].reclaim);
पूर्ण

अटल पूर्णांक dmz_iterate_devices(काष्ठा dm_target *ti,
			       iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	अचिन्हित पूर्णांक zone_nr_sectors = dmz_zone_nr_sectors(dmz->metadata);
	sector_t capacity;
	पूर्णांक i, r;

	क्रम (i = 0; i < dmz->nr_ddevs; i++) अणु
		capacity = dmz->dev[i].capacity & ~(zone_nr_sectors - 1);
		r = fn(ti, dmz->ddev[i], 0, capacity, data);
		अगर (r)
			अवरोध;
	पूर्ण
	वापस r;
पूर्ण

अटल व्योम dmz_status(काष्ठा dm_target *ti, status_type_t type,
		       अचिन्हित पूर्णांक status_flags, अक्षर *result,
		       अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	sमाप_प्रकार sz = 0;
	अक्षर buf[BDEVNAME_SIZE];
	काष्ठा dmz_dev *dev;
	पूर्णांक i;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%u zones %u/%u cache",
		       dmz_nr_zones(dmz->metadata),
		       dmz_nr_unmap_cache_zones(dmz->metadata),
		       dmz_nr_cache_zones(dmz->metadata));
		क्रम (i = 0; i < dmz->nr_ddevs; i++) अणु
			/*
			 * For a multi-device setup the first device
			 * contains only cache zones.
			 */
			अगर ((i == 0) &&
			    (dmz_nr_cache_zones(dmz->metadata) > 0))
				जारी;
			DMEMIT(" %u/%u random %u/%u sequential",
			       dmz_nr_unmap_rnd_zones(dmz->metadata, i),
			       dmz_nr_rnd_zones(dmz->metadata, i),
			       dmz_nr_unmap_seq_zones(dmz->metadata, i),
			       dmz_nr_seq_zones(dmz->metadata, i));
		पूर्ण
		अवरोध;
	हाल STATUSTYPE_TABLE:
		dev = &dmz->dev[0];
		क्रमmat_dev_t(buf, dev->bdev->bd_dev);
		DMEMIT("%s", buf);
		क्रम (i = 1; i < dmz->nr_ddevs; i++) अणु
			dev = &dmz->dev[i];
			क्रमmat_dev_t(buf, dev->bdev->bd_dev);
			DMEMIT(" %s", buf);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक dmz_message(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv,
		       अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा dmz_target *dmz = ti->निजी;
	पूर्णांक r = -EINVAL;

	अगर (!strहालcmp(argv[0], "reclaim")) अणु
		पूर्णांक i;

		क्रम (i = 0; i < dmz->nr_ddevs; i++)
			dmz_schedule_reclaim(dmz->dev[i].reclaim);
		r = 0;
	पूर्ण अन्यथा
		DMERR("unrecognized message %s", argv[0]);
	वापस r;
पूर्ण

अटल काष्ठा target_type dmz_type = अणु
	.name		 = "zoned",
	.version	 = अणु2, 0, 0पूर्ण,
	.features	 = DM_TARGET_SINGLETON | DM_TARGET_MIXED_ZONED_MODEL,
	.module		 = THIS_MODULE,
	.ctr		 = dmz_ctr,
	.dtr		 = dmz_dtr,
	.map		 = dmz_map,
	.io_hपूर्णांकs	 = dmz_io_hपूर्णांकs,
	.prepare_ioctl	 = dmz_prepare_ioctl,
	.postsuspend	 = dmz_suspend,
	.resume		 = dmz_resume,
	.iterate_devices = dmz_iterate_devices,
	.status		 = dmz_status,
	.message	 = dmz_message,
पूर्ण;

अटल पूर्णांक __init dmz_init(व्योम)
अणु
	वापस dm_रेजिस्टर_target(&dmz_type);
पूर्ण

अटल व्योम __निकास dmz_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&dmz_type);
पूर्ण

module_init(dmz_init);
module_निकास(dmz_निकास);

MODULE_DESCRIPTION(DM_NAME " target for zoned block devices");
MODULE_AUTHOR("Damien Le Moal <damien.lemoal@wdc.com>");
MODULE_LICENSE("GPL");
