<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2017 Western Digital Corporation or its affiliates.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_ZONED_H
#घोषणा DM_ZONED_H

#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/dm-kcopyd.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/shrinker.h>

/*
 * dm-zoned creates block devices with 4KB blocks, always.
 */
#घोषणा DMZ_BLOCK_SHIFT		12
#घोषणा DMZ_BLOCK_SIZE		(1 << DMZ_BLOCK_SHIFT)
#घोषणा DMZ_BLOCK_MASK		(DMZ_BLOCK_SIZE - 1)

#घोषणा DMZ_BLOCK_SHIFT_BITS	(DMZ_BLOCK_SHIFT + 3)
#घोषणा DMZ_BLOCK_SIZE_BITS	(1 << DMZ_BLOCK_SHIFT_BITS)
#घोषणा DMZ_BLOCK_MASK_BITS	(DMZ_BLOCK_SIZE_BITS - 1)

#घोषणा DMZ_BLOCK_SECTORS_SHIFT	(DMZ_BLOCK_SHIFT - SECTOR_SHIFT)
#घोषणा DMZ_BLOCK_SECTORS	(DMZ_BLOCK_SIZE >> SECTOR_SHIFT)
#घोषणा DMZ_BLOCK_SECTORS_MASK	(DMZ_BLOCK_SECTORS - 1)

/*
 * 4KB block <-> 512B sector conversion.
 */
#घोषणा dmz_blk2sect(b)		((sector_t)(b) << DMZ_BLOCK_SECTORS_SHIFT)
#घोषणा dmz_sect2blk(s)		((sector_t)(s) >> DMZ_BLOCK_SECTORS_SHIFT)

#घोषणा dmz_bio_block(bio)	dmz_sect2blk((bio)->bi_iter.bi_sector)
#घोषणा dmz_bio_blocks(bio)	dmz_sect2blk(bio_sectors(bio))

काष्ठा dmz_metadata;
काष्ठा dmz_reclaim;

/*
 * Zoned block device inक्रमmation.
 */
काष्ठा dmz_dev अणु
	काष्ठा block_device	*bdev;
	काष्ठा dmz_metadata	*metadata;
	काष्ठा dmz_reclaim	*reclaim;

	अक्षर			name[BDEVNAME_SIZE];
	uuid_t			uuid;

	sector_t		capacity;

	अचिन्हित पूर्णांक		dev_idx;

	अचिन्हित पूर्णांक		nr_zones;
	अचिन्हित पूर्णांक		zone_offset;

	अचिन्हित पूर्णांक		flags;

	sector_t		zone_nr_sectors;

	अचिन्हित पूर्णांक		nr_rnd;
	atomic_t		unmap_nr_rnd;
	काष्ठा list_head	unmap_rnd_list;
	काष्ठा list_head	map_rnd_list;

	अचिन्हित पूर्णांक		nr_seq;
	atomic_t		unmap_nr_seq;
	काष्ठा list_head	unmap_seq_list;
	काष्ठा list_head	map_seq_list;
पूर्ण;

#घोषणा dmz_bio_chunk(zmd, bio)	((bio)->bi_iter.bi_sector >> \
				 dmz_zone_nr_sectors_shअगरt(zmd))
#घोषणा dmz_chunk_block(zmd, b)	((b) & (dmz_zone_nr_blocks(zmd) - 1))

/* Device flags. */
#घोषणा DMZ_BDEV_DYING		(1 << 0)
#घोषणा DMZ_CHECK_BDEV		(2 << 0)
#घोषणा DMZ_BDEV_REGULAR	(4 << 0)

/*
 * Zone descriptor.
 */
काष्ठा dm_zone अणु
	/* For listing the zone depending on its state */
	काष्ठा list_head	link;

	/* Device containing this zone */
	काष्ठा dmz_dev		*dev;

	/* Zone type and state */
	अचिन्हित दीर्घ		flags;

	/* Zone activation reference count */
	atomic_t		refcount;

	/* Zone id */
	अचिन्हित पूर्णांक		id;

	/* Zone ग_लिखो poपूर्णांकer block (relative to the zone start block) */
	अचिन्हित पूर्णांक		wp_block;

	/* Zone weight (number of valid blocks in the zone) */
	अचिन्हित पूर्णांक		weight;

	/* The chunk that the zone maps */
	अचिन्हित पूर्णांक		chunk;

	/*
	 * For a sequential data zone, poपूर्णांकer to the अक्रमom zone
	 * used as a buffer क्रम processing unaligned ग_लिखोs.
	 * For a buffer zone, this poपूर्णांकs back to the data zone.
	 */
	काष्ठा dm_zone		*bzone;
पूर्ण;

/*
 * Zone flags.
 */
क्रमागत अणु
	/* Zone ग_लिखो type */
	DMZ_CACHE,
	DMZ_RND,
	DMZ_SEQ,

	/* Zone critical condition */
	DMZ_OFFLINE,
	DMZ_READ_ONLY,

	/* How the zone is being used */
	DMZ_META,
	DMZ_DATA,
	DMZ_BUF,
	DMZ_RESERVED,

	/* Zone पूर्णांकernal state */
	DMZ_RECLAIM,
	DMZ_SEQ_WRITE_ERR,
	DMZ_RECLAIM_TERMINATE,
पूर्ण;

/*
 * Zone data accessors.
 */
#घोषणा dmz_is_cache(z)		test_bit(DMZ_CACHE, &(z)->flags)
#घोषणा dmz_is_rnd(z)		test_bit(DMZ_RND, &(z)->flags)
#घोषणा dmz_is_seq(z)		test_bit(DMZ_SEQ, &(z)->flags)
#घोषणा dmz_is_empty(z)		((z)->wp_block == 0)
#घोषणा dmz_is_offline(z)	test_bit(DMZ_OFFLINE, &(z)->flags)
#घोषणा dmz_is_पढ़ोonly(z)	test_bit(DMZ_READ_ONLY, &(z)->flags)
#घोषणा dmz_in_reclaim(z)	test_bit(DMZ_RECLAIM, &(z)->flags)
#घोषणा dmz_is_reserved(z)	test_bit(DMZ_RESERVED, &(z)->flags)
#घोषणा dmz_seq_ग_लिखो_err(z)	test_bit(DMZ_SEQ_WRITE_ERR, &(z)->flags)
#घोषणा dmz_reclaim_should_terminate(z) \
				test_bit(DMZ_RECLAIM_TERMINATE, &(z)->flags)

#घोषणा dmz_is_meta(z)		test_bit(DMZ_META, &(z)->flags)
#घोषणा dmz_is_buf(z)		test_bit(DMZ_BUF, &(z)->flags)
#घोषणा dmz_is_data(z)		test_bit(DMZ_DATA, &(z)->flags)

#घोषणा dmz_weight(z)		((z)->weight)

/*
 * Message functions.
 */
#घोषणा dmz_dev_info(dev, क्रमmat, args...)	\
	DMINFO("(%s): " क्रमmat, (dev)->name, ## args)

#घोषणा dmz_dev_err(dev, क्रमmat, args...)	\
	DMERR("(%s): " क्रमmat, (dev)->name, ## args)

#घोषणा dmz_dev_warn(dev, क्रमmat, args...)	\
	DMWARN("(%s): " क्रमmat, (dev)->name, ## args)

#घोषणा dmz_dev_debug(dev, क्रमmat, args...)	\
	DMDEBUG("(%s): " क्रमmat, (dev)->name, ## args)

/*
 * Functions defined in dm-zoned-metadata.c
 */
पूर्णांक dmz_ctr_metadata(काष्ठा dmz_dev *dev, पूर्णांक num_dev,
		     काष्ठा dmz_metadata **zmd, स्थिर अक्षर *devname);
व्योम dmz_dtr_metadata(काष्ठा dmz_metadata *zmd);
पूर्णांक dmz_resume_metadata(काष्ठा dmz_metadata *zmd);

व्योम dmz_lock_map(काष्ठा dmz_metadata *zmd);
व्योम dmz_unlock_map(काष्ठा dmz_metadata *zmd);
व्योम dmz_lock_metadata(काष्ठा dmz_metadata *zmd);
व्योम dmz_unlock_metadata(काष्ठा dmz_metadata *zmd);
व्योम dmz_lock_flush(काष्ठा dmz_metadata *zmd);
व्योम dmz_unlock_flush(काष्ठा dmz_metadata *zmd);
पूर्णांक dmz_flush_metadata(काष्ठा dmz_metadata *zmd);
स्थिर अक्षर *dmz_metadata_label(काष्ठा dmz_metadata *zmd);

sector_t dmz_start_sect(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone);
sector_t dmz_start_block(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone);
अचिन्हित पूर्णांक dmz_nr_chunks(काष्ठा dmz_metadata *zmd);

bool dmz_check_dev(काष्ठा dmz_metadata *zmd);
bool dmz_dev_is_dying(काष्ठा dmz_metadata *zmd);

#घोषणा DMZ_ALLOC_RND		0x01
#घोषणा DMZ_ALLOC_CACHE		0x02
#घोषणा DMZ_ALLOC_SEQ		0x04
#घोषणा DMZ_ALLOC_RECLAIM	0x10

काष्ठा dm_zone *dmz_alloc_zone(काष्ठा dmz_metadata *zmd,
			       अचिन्हित पूर्णांक dev_idx, अचिन्हित दीर्घ flags);
व्योम dmz_मुक्त_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone);

व्योम dmz_map_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
		  अचिन्हित पूर्णांक chunk);
व्योम dmz_unmap_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone);
अचिन्हित पूर्णांक dmz_nr_zones(काष्ठा dmz_metadata *zmd);
अचिन्हित पूर्णांक dmz_nr_cache_zones(काष्ठा dmz_metadata *zmd);
अचिन्हित पूर्णांक dmz_nr_unmap_cache_zones(काष्ठा dmz_metadata *zmd);
अचिन्हित पूर्णांक dmz_nr_rnd_zones(काष्ठा dmz_metadata *zmd, पूर्णांक idx);
अचिन्हित पूर्णांक dmz_nr_unmap_rnd_zones(काष्ठा dmz_metadata *zmd, पूर्णांक idx);
अचिन्हित पूर्णांक dmz_nr_seq_zones(काष्ठा dmz_metadata *zmd, पूर्णांक idx);
अचिन्हित पूर्णांक dmz_nr_unmap_seq_zones(काष्ठा dmz_metadata *zmd, पूर्णांक idx);
अचिन्हित पूर्णांक dmz_zone_nr_blocks(काष्ठा dmz_metadata *zmd);
अचिन्हित पूर्णांक dmz_zone_nr_blocks_shअगरt(काष्ठा dmz_metadata *zmd);
अचिन्हित पूर्णांक dmz_zone_nr_sectors(काष्ठा dmz_metadata *zmd);
अचिन्हित पूर्णांक dmz_zone_nr_sectors_shअगरt(काष्ठा dmz_metadata *zmd);

/*
 * Activate a zone (increment its reference count).
 */
अटल अंतरभूत व्योम dmz_activate_zone(काष्ठा dm_zone *zone)
अणु
	atomic_inc(&zone->refcount);
पूर्ण

पूर्णांक dmz_lock_zone_reclaim(काष्ठा dm_zone *zone);
व्योम dmz_unlock_zone_reclaim(काष्ठा dm_zone *zone);
काष्ठा dm_zone *dmz_get_zone_क्रम_reclaim(काष्ठा dmz_metadata *zmd,
					 अचिन्हित पूर्णांक dev_idx, bool idle);

काष्ठा dm_zone *dmz_get_chunk_mapping(काष्ठा dmz_metadata *zmd,
				      अचिन्हित पूर्णांक chunk, पूर्णांक op);
व्योम dmz_put_chunk_mapping(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone);
काष्ठा dm_zone *dmz_get_chunk_buffer(काष्ठा dmz_metadata *zmd,
				     काष्ठा dm_zone *dzone);

पूर्णांक dmz_validate_blocks(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
			sector_t chunk_block, अचिन्हित पूर्णांक nr_blocks);
पूर्णांक dmz_invalidate_blocks(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
			  sector_t chunk_block, अचिन्हित पूर्णांक nr_blocks);
पूर्णांक dmz_block_valid(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
		    sector_t chunk_block);
पूर्णांक dmz_first_valid_block(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
			  sector_t *chunk_block);
पूर्णांक dmz_copy_valid_blocks(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *from_zone,
			  काष्ठा dm_zone *to_zone);
पूर्णांक dmz_merge_valid_blocks(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *from_zone,
			   काष्ठा dm_zone *to_zone, sector_t chunk_block);

/*
 * Functions defined in dm-zoned-reclaim.c
 */
पूर्णांक dmz_ctr_reclaim(काष्ठा dmz_metadata *zmd, काष्ठा dmz_reclaim **zrc, पूर्णांक idx);
व्योम dmz_dtr_reclaim(काष्ठा dmz_reclaim *zrc);
व्योम dmz_suspend_reclaim(काष्ठा dmz_reclaim *zrc);
व्योम dmz_resume_reclaim(काष्ठा dmz_reclaim *zrc);
व्योम dmz_reclaim_bio_acc(काष्ठा dmz_reclaim *zrc);
व्योम dmz_schedule_reclaim(काष्ठा dmz_reclaim *zrc);

/*
 * Functions defined in dm-zoned-target.c
 */
bool dmz_bdev_is_dying(काष्ठा dmz_dev *dmz_dev);
bool dmz_check_bdev(काष्ठा dmz_dev *dmz_dev);

/*
 * Deactivate a zone. This decrement the zone reference counter
 * indicating that all BIOs to the zone have completed when the count is 0.
 */
अटल अंतरभूत व्योम dmz_deactivate_zone(काष्ठा dm_zone *zone)
अणु
	dmz_reclaim_bio_acc(zone->dev->reclaim);
	atomic_dec(&zone->refcount);
पूर्ण

/*
 * Test अगर a zone is active, that is, has a refcount > 0.
 */
अटल अंतरभूत bool dmz_is_active(काष्ठा dm_zone *zone)
अणु
	वापस atomic_पढ़ो(&zone->refcount);
पूर्ण

#पूर्ण_अगर /* DM_ZONED_H */
