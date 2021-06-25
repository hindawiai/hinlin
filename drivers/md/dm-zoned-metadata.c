<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Western Digital Corporation or its affiliates.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-zoned.h"

#समावेश <linux/module.h>
#समावेश <linux/crc32.h>
#समावेश <linux/sched/mm.h>

#घोषणा	DM_MSG_PREFIX		"zoned metadata"

/*
 * Metadata version.
 */
#घोषणा DMZ_META_VER	2

/*
 * On-disk super block magic.
 */
#घोषणा DMZ_MAGIC	((((अचिन्हित पूर्णांक)('D')) << 24) | \
			 (((अचिन्हित पूर्णांक)('Z')) << 16) | \
			 (((अचिन्हित पूर्णांक)('B')) <<  8) | \
			 ((अचिन्हित पूर्णांक)('D')))

/*
 * On disk super block.
 * This uses only 512 B but uses on disk a full 4KB block. This block is
 * followed on disk by the mapping table of chunks to zones and the biपंचांगap
 * blocks indicating zone block validity.
 * The overall resulting metadata क्रमmat is:
 *    (1) Super block (1 block)
 *    (2) Chunk mapping table (nr_map_blocks)
 *    (3) Biपंचांगap blocks (nr_biपंचांगap_blocks)
 * All metadata blocks are stored in conventional zones, starting from
 * the first conventional zone found on disk.
 */
काष्ठा dmz_super अणु
	/* Magic number */
	__le32		magic;			/*   4 */

	/* Metadata version number */
	__le32		version;		/*   8 */

	/* Generation number */
	__le64		gen;			/*  16 */

	/* This block number */
	__le64		sb_block;		/*  24 */

	/* The number of metadata blocks, including this super block */
	__le32		nr_meta_blocks;		/*  28 */

	/* The number of sequential zones reserved क्रम reclaim */
	__le32		nr_reserved_seq;	/*  32 */

	/* The number of entries in the mapping table */
	__le32		nr_chunks;		/*  36 */

	/* The number of blocks used क्रम the chunk mapping table */
	__le32		nr_map_blocks;		/*  40 */

	/* The number of blocks used क्रम the block biपंचांगaps */
	__le32		nr_biपंचांगap_blocks;	/*  44 */

	/* Checksum */
	__le32		crc;			/*  48 */

	/* DM-Zoned label */
	u8		dmz_label[32];		/*  80 */

	/* DM-Zoned UUID */
	u8		dmz_uuid[16];		/*  96 */

	/* Device UUID */
	u8		dev_uuid[16];		/* 112 */

	/* Padding to full 512B sector */
	u8		reserved[400];		/* 512 */
पूर्ण;

/*
 * Chunk mapping entry: entries are indexed by chunk number
 * and give the zone ID (dzone_id) mapping the chunk on disk.
 * This zone may be sequential or अक्रमom. If it is a sequential
 * zone, a second zone (bzone_id) used as a ग_लिखो buffer may
 * also be specअगरied. This second zone will always be a अक्रमomly
 * ग_लिखोable zone.
 */
काष्ठा dmz_map अणु
	__le32			dzone_id;
	__le32			bzone_id;
पूर्ण;

/*
 * Chunk mapping table metadata: 512 8-bytes entries per 4KB block.
 */
#घोषणा DMZ_MAP_ENTRIES		(DMZ_BLOCK_SIZE / माप(काष्ठा dmz_map))
#घोषणा DMZ_MAP_ENTRIES_SHIFT	(ilog2(DMZ_MAP_ENTRIES))
#घोषणा DMZ_MAP_ENTRIES_MASK	(DMZ_MAP_ENTRIES - 1)
#घोषणा DMZ_MAP_UNMAPPED	अच_पूर्णांक_उच्च

/*
 * Meta data block descriptor (क्रम cached metadata blocks).
 */
काष्ठा dmz_mblock अणु
	काष्ठा rb_node		node;
	काष्ठा list_head	link;
	sector_t		no;
	अचिन्हित पूर्णांक		ref;
	अचिन्हित दीर्घ		state;
	काष्ठा page		*page;
	व्योम			*data;
पूर्ण;

/*
 * Metadata block state flags.
 */
क्रमागत अणु
	DMZ_META_सूचीTY,
	DMZ_META_READING,
	DMZ_META_WRITING,
	DMZ_META_ERROR,
पूर्ण;

/*
 * Super block inक्रमmation (one per metadata set).
 */
काष्ठा dmz_sb अणु
	sector_t		block;
	काष्ठा dmz_dev		*dev;
	काष्ठा dmz_mblock	*mblk;
	काष्ठा dmz_super	*sb;
	काष्ठा dm_zone		*zone;
पूर्ण;

/*
 * In-memory metadata.
 */
काष्ठा dmz_metadata अणु
	काष्ठा dmz_dev		*dev;
	अचिन्हित पूर्णांक		nr_devs;

	अक्षर			devname[BDEVNAME_SIZE];
	अक्षर			label[BDEVNAME_SIZE];
	uuid_t			uuid;

	sector_t		zone_biपंचांगap_size;
	अचिन्हित पूर्णांक		zone_nr_biपंचांगap_blocks;
	अचिन्हित पूर्णांक		zone_bits_per_mblk;

	sector_t		zone_nr_blocks;
	sector_t		zone_nr_blocks_shअगरt;

	sector_t		zone_nr_sectors;
	sector_t		zone_nr_sectors_shअगरt;

	अचिन्हित पूर्णांक		nr_biपंचांगap_blocks;
	अचिन्हित पूर्णांक		nr_map_blocks;

	अचिन्हित पूर्णांक		nr_zones;
	अचिन्हित पूर्णांक		nr_useable_zones;
	अचिन्हित पूर्णांक		nr_meta_blocks;
	अचिन्हित पूर्णांक		nr_meta_zones;
	अचिन्हित पूर्णांक		nr_data_zones;
	अचिन्हित पूर्णांक		nr_cache_zones;
	अचिन्हित पूर्णांक		nr_rnd_zones;
	अचिन्हित पूर्णांक		nr_reserved_seq;
	अचिन्हित पूर्णांक		nr_chunks;

	/* Zone inक्रमmation array */
	काष्ठा xarray		zones;

	काष्ठा dmz_sb		sb[2];
	अचिन्हित पूर्णांक		mblk_primary;
	अचिन्हित पूर्णांक		sb_version;
	u64			sb_gen;
	अचिन्हित पूर्णांक		min_nr_mblks;
	अचिन्हित पूर्णांक		max_nr_mblks;
	atomic_t		nr_mblks;
	काष्ठा rw_semaphore	mblk_sem;
	काष्ठा mutex		mblk_flush_lock;
	spinlock_t		mblk_lock;
	काष्ठा rb_root		mblk_rbtree;
	काष्ठा list_head	mblk_lru_list;
	काष्ठा list_head	mblk_dirty_list;
	काष्ठा shrinker		mblk_shrinker;

	/* Zone allocation management */
	काष्ठा mutex		map_lock;
	काष्ठा dmz_mblock	**map_mblk;

	अचिन्हित पूर्णांक		nr_cache;
	atomic_t		unmap_nr_cache;
	काष्ठा list_head	unmap_cache_list;
	काष्ठा list_head	map_cache_list;

	atomic_t		nr_reserved_seq_zones;
	काष्ठा list_head	reserved_seq_zones_list;

	रुको_queue_head_t	मुक्त_wq;
पूर्ण;

#घोषणा dmz_zmd_info(zmd, क्रमmat, args...)	\
	DMINFO("(%s): " क्रमmat, (zmd)->label, ## args)

#घोषणा dmz_zmd_err(zmd, क्रमmat, args...)	\
	DMERR("(%s): " क्रमmat, (zmd)->label, ## args)

#घोषणा dmz_zmd_warn(zmd, क्रमmat, args...)	\
	DMWARN("(%s): " क्रमmat, (zmd)->label, ## args)

#घोषणा dmz_zmd_debug(zmd, क्रमmat, args...)	\
	DMDEBUG("(%s): " क्रमmat, (zmd)->label, ## args)
/*
 * Various accessors
 */
अटल अचिन्हित पूर्णांक dmz_dev_zone_id(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	अगर (WARN_ON(!zone))
		वापस 0;

	वापस zone->id - zone->dev->zone_offset;
पूर्ण

sector_t dmz_start_sect(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	अचिन्हित पूर्णांक zone_id = dmz_dev_zone_id(zmd, zone);

	वापस (sector_t)zone_id << zmd->zone_nr_sectors_shअगरt;
पूर्ण

sector_t dmz_start_block(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	अचिन्हित पूर्णांक zone_id = dmz_dev_zone_id(zmd, zone);

	वापस (sector_t)zone_id << zmd->zone_nr_blocks_shअगरt;
पूर्ण

अचिन्हित पूर्णांक dmz_zone_nr_blocks(काष्ठा dmz_metadata *zmd)
अणु
	वापस zmd->zone_nr_blocks;
पूर्ण

अचिन्हित पूर्णांक dmz_zone_nr_blocks_shअगरt(काष्ठा dmz_metadata *zmd)
अणु
	वापस zmd->zone_nr_blocks_shअगरt;
पूर्ण

अचिन्हित पूर्णांक dmz_zone_nr_sectors(काष्ठा dmz_metadata *zmd)
अणु
	वापस zmd->zone_nr_sectors;
पूर्ण

अचिन्हित पूर्णांक dmz_zone_nr_sectors_shअगरt(काष्ठा dmz_metadata *zmd)
अणु
	वापस zmd->zone_nr_sectors_shअगरt;
पूर्ण

अचिन्हित पूर्णांक dmz_nr_zones(काष्ठा dmz_metadata *zmd)
अणु
	वापस zmd->nr_zones;
पूर्ण

अचिन्हित पूर्णांक dmz_nr_chunks(काष्ठा dmz_metadata *zmd)
अणु
	वापस zmd->nr_chunks;
पूर्ण

अचिन्हित पूर्णांक dmz_nr_rnd_zones(काष्ठा dmz_metadata *zmd, पूर्णांक idx)
अणु
	वापस zmd->dev[idx].nr_rnd;
पूर्ण

अचिन्हित पूर्णांक dmz_nr_unmap_rnd_zones(काष्ठा dmz_metadata *zmd, पूर्णांक idx)
अणु
	वापस atomic_पढ़ो(&zmd->dev[idx].unmap_nr_rnd);
पूर्ण

अचिन्हित पूर्णांक dmz_nr_cache_zones(काष्ठा dmz_metadata *zmd)
अणु
	वापस zmd->nr_cache;
पूर्ण

अचिन्हित पूर्णांक dmz_nr_unmap_cache_zones(काष्ठा dmz_metadata *zmd)
अणु
	वापस atomic_पढ़ो(&zmd->unmap_nr_cache);
पूर्ण

अचिन्हित पूर्णांक dmz_nr_seq_zones(काष्ठा dmz_metadata *zmd, पूर्णांक idx)
अणु
	वापस zmd->dev[idx].nr_seq;
पूर्ण

अचिन्हित पूर्णांक dmz_nr_unmap_seq_zones(काष्ठा dmz_metadata *zmd, पूर्णांक idx)
अणु
	वापस atomic_पढ़ो(&zmd->dev[idx].unmap_nr_seq);
पूर्ण

अटल काष्ठा dm_zone *dmz_get(काष्ठा dmz_metadata *zmd, अचिन्हित पूर्णांक zone_id)
अणु
	वापस xa_load(&zmd->zones, zone_id);
पूर्ण

अटल काष्ठा dm_zone *dmz_insert(काष्ठा dmz_metadata *zmd,
				  अचिन्हित पूर्णांक zone_id, काष्ठा dmz_dev *dev)
अणु
	काष्ठा dm_zone *zone = kzalloc(माप(काष्ठा dm_zone), GFP_KERNEL);

	अगर (!zone)
		वापस ERR_PTR(-ENOMEM);

	अगर (xa_insert(&zmd->zones, zone_id, zone, GFP_KERNEL)) अणु
		kमुक्त(zone);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	INIT_LIST_HEAD(&zone->link);
	atomic_set(&zone->refcount, 0);
	zone->id = zone_id;
	zone->chunk = DMZ_MAP_UNMAPPED;
	zone->dev = dev;

	वापस zone;
पूर्ण

स्थिर अक्षर *dmz_metadata_label(काष्ठा dmz_metadata *zmd)
अणु
	वापस (स्थिर अक्षर *)zmd->label;
पूर्ण

bool dmz_check_dev(काष्ठा dmz_metadata *zmd)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < zmd->nr_devs; i++) अणु
		अगर (!dmz_check_bdev(&zmd->dev[i]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

bool dmz_dev_is_dying(काष्ठा dmz_metadata *zmd)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < zmd->nr_devs; i++) अणु
		अगर (dmz_bdev_is_dying(&zmd->dev[i]))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Lock/unlock mapping table.
 * The map lock also protects all the zone lists.
 */
व्योम dmz_lock_map(काष्ठा dmz_metadata *zmd)
अणु
	mutex_lock(&zmd->map_lock);
पूर्ण

व्योम dmz_unlock_map(काष्ठा dmz_metadata *zmd)
अणु
	mutex_unlock(&zmd->map_lock);
पूर्ण

/*
 * Lock/unlock metadata access. This is a "read" lock on a semaphore
 * that prevents metadata flush from running जबतक metadata are being
 * modअगरied. The actual metadata ग_लिखो mutual exclusion is achieved with
 * the map lock and zone state management (active and reclaim state are
 * mutually exclusive).
 */
व्योम dmz_lock_metadata(काष्ठा dmz_metadata *zmd)
अणु
	करोwn_पढ़ो(&zmd->mblk_sem);
पूर्ण

व्योम dmz_unlock_metadata(काष्ठा dmz_metadata *zmd)
अणु
	up_पढ़ो(&zmd->mblk_sem);
पूर्ण

/*
 * Lock/unlock flush: prevent concurrent executions
 * of dmz_flush_metadata as well as metadata modअगरication in reclaim
 * जबतक flush is being executed.
 */
व्योम dmz_lock_flush(काष्ठा dmz_metadata *zmd)
अणु
	mutex_lock(&zmd->mblk_flush_lock);
पूर्ण

व्योम dmz_unlock_flush(काष्ठा dmz_metadata *zmd)
अणु
	mutex_unlock(&zmd->mblk_flush_lock);
पूर्ण

/*
 * Allocate a metadata block.
 */
अटल काष्ठा dmz_mblock *dmz_alloc_mblock(काष्ठा dmz_metadata *zmd,
					   sector_t mblk_no)
अणु
	काष्ठा dmz_mblock *mblk = शून्य;

	/* See अगर we can reuse cached blocks */
	अगर (zmd->max_nr_mblks && atomic_पढ़ो(&zmd->nr_mblks) > zmd->max_nr_mblks) अणु
		spin_lock(&zmd->mblk_lock);
		mblk = list_first_entry_or_null(&zmd->mblk_lru_list,
						काष्ठा dmz_mblock, link);
		अगर (mblk) अणु
			list_del_init(&mblk->link);
			rb_erase(&mblk->node, &zmd->mblk_rbtree);
			mblk->no = mblk_no;
		पूर्ण
		spin_unlock(&zmd->mblk_lock);
		अगर (mblk)
			वापस mblk;
	पूर्ण

	/* Allocate a new block */
	mblk = kदो_स्मृति(माप(काष्ठा dmz_mblock), GFP_NOIO);
	अगर (!mblk)
		वापस शून्य;

	mblk->page = alloc_page(GFP_NOIO);
	अगर (!mblk->page) अणु
		kमुक्त(mblk);
		वापस शून्य;
	पूर्ण

	RB_CLEAR_NODE(&mblk->node);
	INIT_LIST_HEAD(&mblk->link);
	mblk->ref = 0;
	mblk->state = 0;
	mblk->no = mblk_no;
	mblk->data = page_address(mblk->page);

	atomic_inc(&zmd->nr_mblks);

	वापस mblk;
पूर्ण

/*
 * Free a metadata block.
 */
अटल व्योम dmz_मुक्त_mblock(काष्ठा dmz_metadata *zmd, काष्ठा dmz_mblock *mblk)
अणु
	__मुक्त_pages(mblk->page, 0);
	kमुक्त(mblk);

	atomic_dec(&zmd->nr_mblks);
पूर्ण

/*
 * Insert a metadata block in the rbtree.
 */
अटल व्योम dmz_insert_mblock(काष्ठा dmz_metadata *zmd, काष्ठा dmz_mblock *mblk)
अणु
	काष्ठा rb_root *root = &zmd->mblk_rbtree;
	काष्ठा rb_node **new = &(root->rb_node), *parent = शून्य;
	काष्ठा dmz_mblock *b;

	/* Figure out where to put the new node */
	जबतक (*new) अणु
		b = container_of(*new, काष्ठा dmz_mblock, node);
		parent = *new;
		new = (b->no < mblk->no) ? &((*new)->rb_left) : &((*new)->rb_right);
	पूर्ण

	/* Add new node and rebalance tree */
	rb_link_node(&mblk->node, parent, new);
	rb_insert_color(&mblk->node, root);
पूर्ण

/*
 * Lookup a metadata block in the rbtree. If the block is found, increment
 * its reference count.
 */
अटल काष्ठा dmz_mblock *dmz_get_mblock_fast(काष्ठा dmz_metadata *zmd,
					      sector_t mblk_no)
अणु
	काष्ठा rb_root *root = &zmd->mblk_rbtree;
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा dmz_mblock *mblk;

	जबतक (node) अणु
		mblk = container_of(node, काष्ठा dmz_mblock, node);
		अगर (mblk->no == mblk_no) अणु
			/*
			 * If this is the first reference to the block,
			 * हटाओ it from the LRU list.
			 */
			mblk->ref++;
			अगर (mblk->ref == 1 &&
			    !test_bit(DMZ_META_सूचीTY, &mblk->state))
				list_del_init(&mblk->link);
			वापस mblk;
		पूर्ण
		node = (mblk->no < mblk_no) ? node->rb_left : node->rb_right;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Metadata block BIO end callback.
 */
अटल व्योम dmz_mblock_bio_end_io(काष्ठा bio *bio)
अणु
	काष्ठा dmz_mblock *mblk = bio->bi_निजी;
	पूर्णांक flag;

	अगर (bio->bi_status)
		set_bit(DMZ_META_ERROR, &mblk->state);

	अगर (bio_op(bio) == REQ_OP_WRITE)
		flag = DMZ_META_WRITING;
	अन्यथा
		flag = DMZ_META_READING;

	clear_bit_unlock(flag, &mblk->state);
	smp_mb__after_atomic();
	wake_up_bit(&mblk->state, flag);

	bio_put(bio);
पूर्ण

/*
 * Read an uncached metadata block from disk and add it to the cache.
 */
अटल काष्ठा dmz_mblock *dmz_get_mblock_slow(काष्ठा dmz_metadata *zmd,
					      sector_t mblk_no)
अणु
	काष्ठा dmz_mblock *mblk, *m;
	sector_t block = zmd->sb[zmd->mblk_primary].block + mblk_no;
	काष्ठा dmz_dev *dev = zmd->sb[zmd->mblk_primary].dev;
	काष्ठा bio *bio;

	अगर (dmz_bdev_is_dying(dev))
		वापस ERR_PTR(-EIO);

	/* Get a new block and a BIO to पढ़ो it */
	mblk = dmz_alloc_mblock(zmd, mblk_no);
	अगर (!mblk)
		वापस ERR_PTR(-ENOMEM);

	bio = bio_alloc(GFP_NOIO, 1);
	अगर (!bio) अणु
		dmz_मुक्त_mblock(zmd, mblk);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	spin_lock(&zmd->mblk_lock);

	/*
	 * Make sure that another context did not start पढ़ोing
	 * the block alपढ़ोy.
	 */
	m = dmz_get_mblock_fast(zmd, mblk_no);
	अगर (m) अणु
		spin_unlock(&zmd->mblk_lock);
		dmz_मुक्त_mblock(zmd, mblk);
		bio_put(bio);
		वापस m;
	पूर्ण

	mblk->ref++;
	set_bit(DMZ_META_READING, &mblk->state);
	dmz_insert_mblock(zmd, mblk);

	spin_unlock(&zmd->mblk_lock);

	/* Submit पढ़ो BIO */
	bio->bi_iter.bi_sector = dmz_blk2sect(block);
	bio_set_dev(bio, dev->bdev);
	bio->bi_निजी = mblk;
	bio->bi_end_io = dmz_mblock_bio_end_io;
	bio_set_op_attrs(bio, REQ_OP_READ, REQ_META | REQ_PRIO);
	bio_add_page(bio, mblk->page, DMZ_BLOCK_SIZE, 0);
	submit_bio(bio);

	वापस mblk;
पूर्ण

/*
 * Free metadata blocks.
 */
अटल अचिन्हित दीर्घ dmz_shrink_mblock_cache(काष्ठा dmz_metadata *zmd,
					     अचिन्हित दीर्घ limit)
अणु
	काष्ठा dmz_mblock *mblk;
	अचिन्हित दीर्घ count = 0;

	अगर (!zmd->max_nr_mblks)
		वापस 0;

	जबतक (!list_empty(&zmd->mblk_lru_list) &&
	       atomic_पढ़ो(&zmd->nr_mblks) > zmd->min_nr_mblks &&
	       count < limit) अणु
		mblk = list_first_entry(&zmd->mblk_lru_list,
					काष्ठा dmz_mblock, link);
		list_del_init(&mblk->link);
		rb_erase(&mblk->node, &zmd->mblk_rbtree);
		dmz_मुक्त_mblock(zmd, mblk);
		count++;
	पूर्ण

	वापस count;
पूर्ण

/*
 * For mblock shrinker: get the number of unused metadata blocks in the cache.
 */
अटल अचिन्हित दीर्घ dmz_mblock_shrinker_count(काष्ठा shrinker *shrink,
					       काष्ठा shrink_control *sc)
अणु
	काष्ठा dmz_metadata *zmd = container_of(shrink, काष्ठा dmz_metadata, mblk_shrinker);

	वापस atomic_पढ़ो(&zmd->nr_mblks);
पूर्ण

/*
 * For mblock shrinker: scan unused metadata blocks and shrink the cache.
 */
अटल अचिन्हित दीर्घ dmz_mblock_shrinker_scan(काष्ठा shrinker *shrink,
					      काष्ठा shrink_control *sc)
अणु
	काष्ठा dmz_metadata *zmd = container_of(shrink, काष्ठा dmz_metadata, mblk_shrinker);
	अचिन्हित दीर्घ count;

	spin_lock(&zmd->mblk_lock);
	count = dmz_shrink_mblock_cache(zmd, sc->nr_to_scan);
	spin_unlock(&zmd->mblk_lock);

	वापस count ? count : SHRINK_STOP;
पूर्ण

/*
 * Release a metadata block.
 */
अटल व्योम dmz_release_mblock(काष्ठा dmz_metadata *zmd,
			       काष्ठा dmz_mblock *mblk)
अणु

	अगर (!mblk)
		वापस;

	spin_lock(&zmd->mblk_lock);

	mblk->ref--;
	अगर (mblk->ref == 0) अणु
		अगर (test_bit(DMZ_META_ERROR, &mblk->state)) अणु
			rb_erase(&mblk->node, &zmd->mblk_rbtree);
			dmz_मुक्त_mblock(zmd, mblk);
		पूर्ण अन्यथा अगर (!test_bit(DMZ_META_सूचीTY, &mblk->state)) अणु
			list_add_tail(&mblk->link, &zmd->mblk_lru_list);
			dmz_shrink_mblock_cache(zmd, 1);
		पूर्ण
	पूर्ण

	spin_unlock(&zmd->mblk_lock);
पूर्ण

/*
 * Get a metadata block from the rbtree. If the block
 * is not present, पढ़ो it from disk.
 */
अटल काष्ठा dmz_mblock *dmz_get_mblock(काष्ठा dmz_metadata *zmd,
					 sector_t mblk_no)
अणु
	काष्ठा dmz_mblock *mblk;
	काष्ठा dmz_dev *dev = zmd->sb[zmd->mblk_primary].dev;

	/* Check rbtree */
	spin_lock(&zmd->mblk_lock);
	mblk = dmz_get_mblock_fast(zmd, mblk_no);
	spin_unlock(&zmd->mblk_lock);

	अगर (!mblk) अणु
		/* Cache miss: पढ़ो the block from disk */
		mblk = dmz_get_mblock_slow(zmd, mblk_no);
		अगर (IS_ERR(mblk))
			वापस mblk;
	पूर्ण

	/* Wait क्रम on-going पढ़ो I/O and check क्रम error */
	रुको_on_bit_io(&mblk->state, DMZ_META_READING,
		       TASK_UNINTERRUPTIBLE);
	अगर (test_bit(DMZ_META_ERROR, &mblk->state)) अणु
		dmz_release_mblock(zmd, mblk);
		dmz_check_bdev(dev);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस mblk;
पूर्ण

/*
 * Mark a metadata block dirty.
 */
अटल व्योम dmz_dirty_mblock(काष्ठा dmz_metadata *zmd, काष्ठा dmz_mblock *mblk)
अणु
	spin_lock(&zmd->mblk_lock);
	अगर (!test_and_set_bit(DMZ_META_सूचीTY, &mblk->state))
		list_add_tail(&mblk->link, &zmd->mblk_dirty_list);
	spin_unlock(&zmd->mblk_lock);
पूर्ण

/*
 * Issue a metadata block ग_लिखो BIO.
 */
अटल पूर्णांक dmz_ग_लिखो_mblock(काष्ठा dmz_metadata *zmd, काष्ठा dmz_mblock *mblk,
			    अचिन्हित पूर्णांक set)
अणु
	काष्ठा dmz_dev *dev = zmd->sb[set].dev;
	sector_t block = zmd->sb[set].block + mblk->no;
	काष्ठा bio *bio;

	अगर (dmz_bdev_is_dying(dev))
		वापस -EIO;

	bio = bio_alloc(GFP_NOIO, 1);
	अगर (!bio) अणु
		set_bit(DMZ_META_ERROR, &mblk->state);
		वापस -ENOMEM;
	पूर्ण

	set_bit(DMZ_META_WRITING, &mblk->state);

	bio->bi_iter.bi_sector = dmz_blk2sect(block);
	bio_set_dev(bio, dev->bdev);
	bio->bi_निजी = mblk;
	bio->bi_end_io = dmz_mblock_bio_end_io;
	bio_set_op_attrs(bio, REQ_OP_WRITE, REQ_META | REQ_PRIO);
	bio_add_page(bio, mblk->page, DMZ_BLOCK_SIZE, 0);
	submit_bio(bio);

	वापस 0;
पूर्ण

/*
 * Read/ग_लिखो a metadata block.
 */
अटल पूर्णांक dmz_rdwr_block(काष्ठा dmz_dev *dev, पूर्णांक op,
			  sector_t block, काष्ठा page *page)
अणु
	काष्ठा bio *bio;
	पूर्णांक ret;

	अगर (WARN_ON(!dev))
		वापस -EIO;

	अगर (dmz_bdev_is_dying(dev))
		वापस -EIO;

	bio = bio_alloc(GFP_NOIO, 1);
	अगर (!bio)
		वापस -ENOMEM;

	bio->bi_iter.bi_sector = dmz_blk2sect(block);
	bio_set_dev(bio, dev->bdev);
	bio_set_op_attrs(bio, op, REQ_SYNC | REQ_META | REQ_PRIO);
	bio_add_page(bio, page, DMZ_BLOCK_SIZE, 0);
	ret = submit_bio_रुको(bio);
	bio_put(bio);

	अगर (ret)
		dmz_check_bdev(dev);
	वापस ret;
पूर्ण

/*
 * Write super block of the specअगरied metadata set.
 */
अटल पूर्णांक dmz_ग_लिखो_sb(काष्ठा dmz_metadata *zmd, अचिन्हित पूर्णांक set)
अणु
	काष्ठा dmz_mblock *mblk = zmd->sb[set].mblk;
	काष्ठा dmz_super *sb = zmd->sb[set].sb;
	काष्ठा dmz_dev *dev = zmd->sb[set].dev;
	sector_t sb_block;
	u64 sb_gen = zmd->sb_gen + 1;
	पूर्णांक ret;

	sb->magic = cpu_to_le32(DMZ_MAGIC);

	sb->version = cpu_to_le32(zmd->sb_version);
	अगर (zmd->sb_version > 1) अणु
		BUILD_BUG_ON(UUID_SIZE != 16);
		export_uuid(sb->dmz_uuid, &zmd->uuid);
		स_नकल(sb->dmz_label, zmd->label, BDEVNAME_SIZE);
		export_uuid(sb->dev_uuid, &dev->uuid);
	पूर्ण

	sb->gen = cpu_to_le64(sb_gen);

	/*
	 * The metadata always references the असलolute block address,
	 * ie relative to the entire block range, not the per-device
	 * block address.
	 */
	sb_block = zmd->sb[set].zone->id << zmd->zone_nr_blocks_shअगरt;
	sb->sb_block = cpu_to_le64(sb_block);
	sb->nr_meta_blocks = cpu_to_le32(zmd->nr_meta_blocks);
	sb->nr_reserved_seq = cpu_to_le32(zmd->nr_reserved_seq);
	sb->nr_chunks = cpu_to_le32(zmd->nr_chunks);

	sb->nr_map_blocks = cpu_to_le32(zmd->nr_map_blocks);
	sb->nr_biपंचांगap_blocks = cpu_to_le32(zmd->nr_biपंचांगap_blocks);

	sb->crc = 0;
	sb->crc = cpu_to_le32(crc32_le(sb_gen, (अचिन्हित अक्षर *)sb, DMZ_BLOCK_SIZE));

	ret = dmz_rdwr_block(dev, REQ_OP_WRITE, zmd->sb[set].block,
			     mblk->page);
	अगर (ret == 0)
		ret = blkdev_issue_flush(dev->bdev);

	वापस ret;
पूर्ण

/*
 * Write dirty metadata blocks to the specअगरied set.
 */
अटल पूर्णांक dmz_ग_लिखो_dirty_mblocks(काष्ठा dmz_metadata *zmd,
				   काष्ठा list_head *ग_लिखो_list,
				   अचिन्हित पूर्णांक set)
अणु
	काष्ठा dmz_mblock *mblk;
	काष्ठा dmz_dev *dev = zmd->sb[set].dev;
	काष्ठा blk_plug plug;
	पूर्णांक ret = 0, nr_mblks_submitted = 0;

	/* Issue ग_लिखोs */
	blk_start_plug(&plug);
	list_क्रम_each_entry(mblk, ग_लिखो_list, link) अणु
		ret = dmz_ग_लिखो_mblock(zmd, mblk, set);
		अगर (ret)
			अवरोध;
		nr_mblks_submitted++;
	पूर्ण
	blk_finish_plug(&plug);

	/* Wait क्रम completion */
	list_क्रम_each_entry(mblk, ग_लिखो_list, link) अणु
		अगर (!nr_mblks_submitted)
			अवरोध;
		रुको_on_bit_io(&mblk->state, DMZ_META_WRITING,
			       TASK_UNINTERRUPTIBLE);
		अगर (test_bit(DMZ_META_ERROR, &mblk->state)) अणु
			clear_bit(DMZ_META_ERROR, &mblk->state);
			dmz_check_bdev(dev);
			ret = -EIO;
		पूर्ण
		nr_mblks_submitted--;
	पूर्ण

	/* Flush drive cache (this will also sync data) */
	अगर (ret == 0)
		ret = blkdev_issue_flush(dev->bdev);

	वापस ret;
पूर्ण

/*
 * Log dirty metadata blocks.
 */
अटल पूर्णांक dmz_log_dirty_mblocks(काष्ठा dmz_metadata *zmd,
				 काष्ठा list_head *ग_लिखो_list)
अणु
	अचिन्हित पूर्णांक log_set = zmd->mblk_primary ^ 0x1;
	पूर्णांक ret;

	/* Write dirty blocks to the log */
	ret = dmz_ग_लिखो_dirty_mblocks(zmd, ग_लिखो_list, log_set);
	अगर (ret)
		वापस ret;

	/*
	 * No error so far: now validate the log by updating the
	 * log index super block generation.
	 */
	ret = dmz_ग_लिखो_sb(zmd, log_set);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Flush dirty metadata blocks.
 */
पूर्णांक dmz_flush_metadata(काष्ठा dmz_metadata *zmd)
अणु
	काष्ठा dmz_mblock *mblk;
	काष्ठा list_head ग_लिखो_list;
	काष्ठा dmz_dev *dev;
	पूर्णांक ret;

	अगर (WARN_ON(!zmd))
		वापस 0;

	INIT_LIST_HEAD(&ग_लिखो_list);

	/*
	 * Make sure that metadata blocks are stable beक्रमe logging: take
	 * the ग_लिखो lock on the metadata semaphore to prevent target BIOs
	 * from modअगरying metadata.
	 */
	करोwn_ग_लिखो(&zmd->mblk_sem);
	dev = zmd->sb[zmd->mblk_primary].dev;

	/*
	 * This is called from the target flush work and reclaim work.
	 * Concurrent execution is not allowed.
	 */
	dmz_lock_flush(zmd);

	अगर (dmz_bdev_is_dying(dev)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Get dirty blocks */
	spin_lock(&zmd->mblk_lock);
	list_splice_init(&zmd->mblk_dirty_list, &ग_लिखो_list);
	spin_unlock(&zmd->mblk_lock);

	/* If there are no dirty metadata blocks, just flush the device cache */
	अगर (list_empty(&ग_लिखो_list)) अणु
		ret = blkdev_issue_flush(dev->bdev);
		जाओ err;
	पूर्ण

	/*
	 * The primary metadata set is still clean. Keep it this way until
	 * all updates are successful in the secondary set. That is, use
	 * the secondary set as a log.
	 */
	ret = dmz_log_dirty_mblocks(zmd, &ग_लिखो_list);
	अगर (ret)
		जाओ err;

	/*
	 * The log is on disk. It is now safe to update in place
	 * in the primary metadata set.
	 */
	ret = dmz_ग_लिखो_dirty_mblocks(zmd, &ग_लिखो_list, zmd->mblk_primary);
	अगर (ret)
		जाओ err;

	ret = dmz_ग_लिखो_sb(zmd, zmd->mblk_primary);
	अगर (ret)
		जाओ err;

	जबतक (!list_empty(&ग_लिखो_list)) अणु
		mblk = list_first_entry(&ग_लिखो_list, काष्ठा dmz_mblock, link);
		list_del_init(&mblk->link);

		spin_lock(&zmd->mblk_lock);
		clear_bit(DMZ_META_सूचीTY, &mblk->state);
		अगर (mblk->ref == 0)
			list_add_tail(&mblk->link, &zmd->mblk_lru_list);
		spin_unlock(&zmd->mblk_lock);
	पूर्ण

	zmd->sb_gen++;
out:
	dmz_unlock_flush(zmd);
	up_ग_लिखो(&zmd->mblk_sem);

	वापस ret;

err:
	अगर (!list_empty(&ग_लिखो_list)) अणु
		spin_lock(&zmd->mblk_lock);
		list_splice(&ग_लिखो_list, &zmd->mblk_dirty_list);
		spin_unlock(&zmd->mblk_lock);
	पूर्ण
	अगर (!dmz_check_bdev(dev))
		ret = -EIO;
	जाओ out;
पूर्ण

/*
 * Check super block.
 */
अटल पूर्णांक dmz_check_sb(काष्ठा dmz_metadata *zmd, काष्ठा dmz_sb *dsb,
			bool tertiary)
अणु
	काष्ठा dmz_super *sb = dsb->sb;
	काष्ठा dmz_dev *dev = dsb->dev;
	अचिन्हित पूर्णांक nr_meta_zones, nr_data_zones;
	u32 crc, stored_crc;
	u64 gen, sb_block;

	अगर (le32_to_cpu(sb->magic) != DMZ_MAGIC) अणु
		dmz_dev_err(dev, "Invalid meta magic (needed 0x%08x, got 0x%08x)",
			    DMZ_MAGIC, le32_to_cpu(sb->magic));
		वापस -ENXIO;
	पूर्ण

	zmd->sb_version = le32_to_cpu(sb->version);
	अगर (zmd->sb_version > DMZ_META_VER) अणु
		dmz_dev_err(dev, "Invalid meta version (needed %d, got %d)",
			    DMZ_META_VER, zmd->sb_version);
		वापस -EINVAL;
	पूर्ण
	अगर (zmd->sb_version < 2 && tertiary) अणु
		dmz_dev_err(dev, "Tertiary superblocks are not supported");
		वापस -EINVAL;
	पूर्ण

	gen = le64_to_cpu(sb->gen);
	stored_crc = le32_to_cpu(sb->crc);
	sb->crc = 0;
	crc = crc32_le(gen, (अचिन्हित अक्षर *)sb, DMZ_BLOCK_SIZE);
	अगर (crc != stored_crc) अणु
		dmz_dev_err(dev, "Invalid checksum (needed 0x%08x, got 0x%08x)",
			    crc, stored_crc);
		वापस -ENXIO;
	पूर्ण

	sb_block = le64_to_cpu(sb->sb_block);
	अगर (sb_block != (u64)dsb->zone->id << zmd->zone_nr_blocks_shअगरt ) अणु
		dmz_dev_err(dev, "Invalid superblock position "
			    "(is %llu expected %llu)",
			    sb_block,
			    (u64)dsb->zone->id << zmd->zone_nr_blocks_shअगरt);
		वापस -EINVAL;
	पूर्ण
	अगर (zmd->sb_version > 1) अणु
		uuid_t sb_uuid;

		import_uuid(&sb_uuid, sb->dmz_uuid);
		अगर (uuid_is_null(&sb_uuid)) अणु
			dmz_dev_err(dev, "NULL DM-Zoned uuid");
			वापस -ENXIO;
		पूर्ण अन्यथा अगर (uuid_is_null(&zmd->uuid)) अणु
			uuid_copy(&zmd->uuid, &sb_uuid);
		पूर्ण अन्यथा अगर (!uuid_equal(&zmd->uuid, &sb_uuid)) अणु
			dmz_dev_err(dev, "mismatching DM-Zoned uuid, "
				    "is %pUl expected %pUl",
				    &sb_uuid, &zmd->uuid);
			वापस -ENXIO;
		पूर्ण
		अगर (!म_माप(zmd->label))
			स_नकल(zmd->label, sb->dmz_label, BDEVNAME_SIZE);
		अन्यथा अगर (स_भेद(zmd->label, sb->dmz_label, BDEVNAME_SIZE)) अणु
			dmz_dev_err(dev, "mismatching DM-Zoned label, "
				    "is %s expected %s",
				    sb->dmz_label, zmd->label);
			वापस -ENXIO;
		पूर्ण
		import_uuid(&dev->uuid, sb->dev_uuid);
		अगर (uuid_is_null(&dev->uuid)) अणु
			dmz_dev_err(dev, "NULL device uuid");
			वापस -ENXIO;
		पूर्ण

		अगर (tertiary) अणु
			/*
			 * Generation number should be 0, but it करोesn't
			 * really matter अगर it isn't.
			 */
			अगर (gen != 0)
				dmz_dev_warn(dev, "Invalid generation %llu",
					    gen);
			वापस 0;
		पूर्ण
	पूर्ण

	nr_meta_zones = (le32_to_cpu(sb->nr_meta_blocks) + zmd->zone_nr_blocks - 1)
		>> zmd->zone_nr_blocks_shअगरt;
	अगर (!nr_meta_zones ||
	    (zmd->nr_devs <= 1 && nr_meta_zones >= zmd->nr_rnd_zones) ||
	    (zmd->nr_devs > 1 && nr_meta_zones >= zmd->nr_cache_zones)) अणु
		dmz_dev_err(dev, "Invalid number of metadata blocks");
		वापस -ENXIO;
	पूर्ण

	अगर (!le32_to_cpu(sb->nr_reserved_seq) ||
	    le32_to_cpu(sb->nr_reserved_seq) >= (zmd->nr_useable_zones - nr_meta_zones)) अणु
		dmz_dev_err(dev, "Invalid number of reserved sequential zones");
		वापस -ENXIO;
	पूर्ण

	nr_data_zones = zmd->nr_useable_zones -
		(nr_meta_zones * 2 + le32_to_cpu(sb->nr_reserved_seq));
	अगर (le32_to_cpu(sb->nr_chunks) > nr_data_zones) अणु
		dmz_dev_err(dev, "Invalid number of chunks %u / %u",
			    le32_to_cpu(sb->nr_chunks), nr_data_zones);
		वापस -ENXIO;
	पूर्ण

	/* OK */
	zmd->nr_meta_blocks = le32_to_cpu(sb->nr_meta_blocks);
	zmd->nr_reserved_seq = le32_to_cpu(sb->nr_reserved_seq);
	zmd->nr_chunks = le32_to_cpu(sb->nr_chunks);
	zmd->nr_map_blocks = le32_to_cpu(sb->nr_map_blocks);
	zmd->nr_biपंचांगap_blocks = le32_to_cpu(sb->nr_biपंचांगap_blocks);
	zmd->nr_meta_zones = nr_meta_zones;
	zmd->nr_data_zones = nr_data_zones;

	वापस 0;
पूर्ण

/*
 * Read the first or second super block from disk.
 */
अटल पूर्णांक dmz_पढ़ो_sb(काष्ठा dmz_metadata *zmd, काष्ठा dmz_sb *sb, पूर्णांक set)
अणु
	dmz_zmd_debug(zmd, "read superblock set %d dev %s block %llu",
		      set, sb->dev->name, sb->block);

	वापस dmz_rdwr_block(sb->dev, REQ_OP_READ,
			      sb->block, sb->mblk->page);
पूर्ण

/*
 * Determine the position of the secondary super blocks on disk.
 * This is used only अगर a corruption of the primary super block
 * is detected.
 */
अटल पूर्णांक dmz_lookup_secondary_sb(काष्ठा dmz_metadata *zmd)
अणु
	अचिन्हित पूर्णांक zone_nr_blocks = zmd->zone_nr_blocks;
	काष्ठा dmz_mblock *mblk;
	अचिन्हित पूर्णांक zone_id = zmd->sb[0].zone->id;
	पूर्णांक i;

	/* Allocate a block */
	mblk = dmz_alloc_mblock(zmd, 0);
	अगर (!mblk)
		वापस -ENOMEM;

	zmd->sb[1].mblk = mblk;
	zmd->sb[1].sb = mblk->data;

	/* Bad first super block: search क्रम the second one */
	zmd->sb[1].block = zmd->sb[0].block + zone_nr_blocks;
	zmd->sb[1].zone = dmz_get(zmd, zone_id + 1);
	zmd->sb[1].dev = zmd->sb[0].dev;
	क्रम (i = 1; i < zmd->nr_rnd_zones; i++) अणु
		अगर (dmz_पढ़ो_sb(zmd, &zmd->sb[1], 1) != 0)
			अवरोध;
		अगर (le32_to_cpu(zmd->sb[1].sb->magic) == DMZ_MAGIC)
			वापस 0;
		zmd->sb[1].block += zone_nr_blocks;
		zmd->sb[1].zone = dmz_get(zmd, zone_id + i);
	पूर्ण

	dmz_मुक्त_mblock(zmd, mblk);
	zmd->sb[1].mblk = शून्य;
	zmd->sb[1].zone = शून्य;
	zmd->sb[1].dev = शून्य;

	वापस -EIO;
पूर्ण

/*
 * Read a super block from disk.
 */
अटल पूर्णांक dmz_get_sb(काष्ठा dmz_metadata *zmd, काष्ठा dmz_sb *sb, पूर्णांक set)
अणु
	काष्ठा dmz_mblock *mblk;
	पूर्णांक ret;

	/* Allocate a block */
	mblk = dmz_alloc_mblock(zmd, 0);
	अगर (!mblk)
		वापस -ENOMEM;

	sb->mblk = mblk;
	sb->sb = mblk->data;

	/* Read super block */
	ret = dmz_पढ़ो_sb(zmd, sb, set);
	अगर (ret) अणु
		dmz_मुक्त_mblock(zmd, mblk);
		sb->mblk = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Recover a metadata set.
 */
अटल पूर्णांक dmz_recover_mblocks(काष्ठा dmz_metadata *zmd, अचिन्हित पूर्णांक dst_set)
अणु
	अचिन्हित पूर्णांक src_set = dst_set ^ 0x1;
	काष्ठा page *page;
	पूर्णांक i, ret;

	dmz_dev_warn(zmd->sb[dst_set].dev,
		     "Metadata set %u invalid: recovering", dst_set);

	अगर (dst_set == 0)
		zmd->sb[0].block = dmz_start_block(zmd, zmd->sb[0].zone);
	अन्यथा
		zmd->sb[1].block = dmz_start_block(zmd, zmd->sb[1].zone);

	page = alloc_page(GFP_NOIO);
	अगर (!page)
		वापस -ENOMEM;

	/* Copy metadata blocks */
	क्रम (i = 1; i < zmd->nr_meta_blocks; i++) अणु
		ret = dmz_rdwr_block(zmd->sb[src_set].dev, REQ_OP_READ,
				     zmd->sb[src_set].block + i, page);
		अगर (ret)
			जाओ out;
		ret = dmz_rdwr_block(zmd->sb[dst_set].dev, REQ_OP_WRITE,
				     zmd->sb[dst_set].block + i, page);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Finalize with the super block */
	अगर (!zmd->sb[dst_set].mblk) अणु
		zmd->sb[dst_set].mblk = dmz_alloc_mblock(zmd, 0);
		अगर (!zmd->sb[dst_set].mblk) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		zmd->sb[dst_set].sb = zmd->sb[dst_set].mblk->data;
	पूर्ण

	ret = dmz_ग_लिखो_sb(zmd, dst_set);
out:
	__मुक्त_pages(page, 0);

	वापस ret;
पूर्ण

/*
 * Get super block from disk.
 */
अटल पूर्णांक dmz_load_sb(काष्ठा dmz_metadata *zmd)
अणु
	bool sb_good[2] = अणुfalse, falseपूर्ण;
	u64 sb_gen[2] = अणु0, 0पूर्ण;
	पूर्णांक ret;

	अगर (!zmd->sb[0].zone) अणु
		dmz_zmd_err(zmd, "Primary super block zone not set");
		वापस -ENXIO;
	पूर्ण

	/* Read and check the primary super block */
	zmd->sb[0].block = dmz_start_block(zmd, zmd->sb[0].zone);
	zmd->sb[0].dev = zmd->sb[0].zone->dev;
	ret = dmz_get_sb(zmd, &zmd->sb[0], 0);
	अगर (ret) अणु
		dmz_dev_err(zmd->sb[0].dev, "Read primary super block failed");
		वापस ret;
	पूर्ण

	ret = dmz_check_sb(zmd, &zmd->sb[0], false);

	/* Read and check secondary super block */
	अगर (ret == 0) अणु
		sb_good[0] = true;
		अगर (!zmd->sb[1].zone) अणु
			अचिन्हित पूर्णांक zone_id =
				zmd->sb[0].zone->id + zmd->nr_meta_zones;

			zmd->sb[1].zone = dmz_get(zmd, zone_id);
		पूर्ण
		zmd->sb[1].block = dmz_start_block(zmd, zmd->sb[1].zone);
		zmd->sb[1].dev = zmd->sb[0].dev;
		ret = dmz_get_sb(zmd, &zmd->sb[1], 1);
	पूर्ण अन्यथा
		ret = dmz_lookup_secondary_sb(zmd);

	अगर (ret) अणु
		dmz_dev_err(zmd->sb[1].dev, "Read secondary super block failed");
		वापस ret;
	पूर्ण

	ret = dmz_check_sb(zmd, &zmd->sb[1], false);
	अगर (ret == 0)
		sb_good[1] = true;

	/* Use highest generation sb first */
	अगर (!sb_good[0] && !sb_good[1]) अणु
		dmz_zmd_err(zmd, "No valid super block found");
		वापस -EIO;
	पूर्ण

	अगर (sb_good[0])
		sb_gen[0] = le64_to_cpu(zmd->sb[0].sb->gen);
	अन्यथा अणु
		ret = dmz_recover_mblocks(zmd, 0);
		अगर (ret) अणु
			dmz_dev_err(zmd->sb[0].dev,
				    "Recovery of superblock 0 failed");
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (sb_good[1])
		sb_gen[1] = le64_to_cpu(zmd->sb[1].sb->gen);
	अन्यथा अणु
		ret = dmz_recover_mblocks(zmd, 1);

		अगर (ret) अणु
			dmz_dev_err(zmd->sb[1].dev,
				    "Recovery of superblock 1 failed");
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (sb_gen[0] >= sb_gen[1]) अणु
		zmd->sb_gen = sb_gen[0];
		zmd->mblk_primary = 0;
	पूर्ण अन्यथा अणु
		zmd->sb_gen = sb_gen[1];
		zmd->mblk_primary = 1;
	पूर्ण

	dmz_dev_debug(zmd->sb[zmd->mblk_primary].dev,
		      "Using super block %u (gen %llu)",
		      zmd->mblk_primary, zmd->sb_gen);

	अगर (zmd->sb_version > 1) अणु
		पूर्णांक i;
		काष्ठा dmz_sb *sb;

		sb = kzalloc(माप(काष्ठा dmz_sb), GFP_KERNEL);
		अगर (!sb)
			वापस -ENOMEM;
		क्रम (i = 1; i < zmd->nr_devs; i++) अणु
			sb->block = 0;
			sb->zone = dmz_get(zmd, zmd->dev[i].zone_offset);
			sb->dev = &zmd->dev[i];
			अगर (!dmz_is_meta(sb->zone)) अणु
				dmz_dev_err(sb->dev,
					    "Tertiary super block zone %u not marked as metadata zone",
					    sb->zone->id);
				ret = -EINVAL;
				जाओ out_kमुक्त;
			पूर्ण
			ret = dmz_get_sb(zmd, sb, i + 1);
			अगर (ret) अणु
				dmz_dev_err(sb->dev,
					    "Read tertiary super block failed");
				dmz_मुक्त_mblock(zmd, sb->mblk);
				जाओ out_kमुक्त;
			पूर्ण
			ret = dmz_check_sb(zmd, sb, true);
			dmz_मुक्त_mblock(zmd, sb->mblk);
			अगर (ret == -EINVAL)
				जाओ out_kमुक्त;
		पूर्ण
	out_kमुक्त:
		kमुक्त(sb);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Initialize a zone descriptor.
 */
अटल पूर्णांक dmz_init_zone(काष्ठा blk_zone *blkz, अचिन्हित पूर्णांक num, व्योम *data)
अणु
	काष्ठा dmz_dev *dev = data;
	काष्ठा dmz_metadata *zmd = dev->metadata;
	पूर्णांक idx = num + dev->zone_offset;
	काष्ठा dm_zone *zone;

	zone = dmz_insert(zmd, idx, dev);
	अगर (IS_ERR(zone))
		वापस PTR_ERR(zone);

	अगर (blkz->len != zmd->zone_nr_sectors) अणु
		अगर (zmd->sb_version > 1) अणु
			/* Ignore the eventual runt (smaller) zone */
			set_bit(DMZ_OFFLINE, &zone->flags);
			वापस 0;
		पूर्ण अन्यथा अगर (blkz->start + blkz->len == dev->capacity)
			वापस 0;
		वापस -ENXIO;
	पूर्ण

	चयन (blkz->type) अणु
	हाल BLK_ZONE_TYPE_CONVENTIONAL:
		set_bit(DMZ_RND, &zone->flags);
		अवरोध;
	हाल BLK_ZONE_TYPE_SEQWRITE_REQ:
	हाल BLK_ZONE_TYPE_SEQWRITE_PREF:
		set_bit(DMZ_SEQ, &zone->flags);
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	अगर (dmz_is_rnd(zone))
		zone->wp_block = 0;
	अन्यथा
		zone->wp_block = dmz_sect2blk(blkz->wp - blkz->start);

	अगर (blkz->cond == BLK_ZONE_COND_OFFLINE)
		set_bit(DMZ_OFFLINE, &zone->flags);
	अन्यथा अगर (blkz->cond == BLK_ZONE_COND_READONLY)
		set_bit(DMZ_READ_ONLY, &zone->flags);
	अन्यथा अणु
		zmd->nr_useable_zones++;
		अगर (dmz_is_rnd(zone)) अणु
			zmd->nr_rnd_zones++;
			अगर (zmd->nr_devs == 1 && !zmd->sb[0].zone) अणु
				/* Primary super block zone */
				zmd->sb[0].zone = zone;
			पूर्ण
		पूर्ण
		अगर (zmd->nr_devs > 1 && num == 0) अणु
			/*
			 * Tertiary superblock zones are always at the
			 * start of the zoned devices, so mark them
			 * as metadata zone.
			 */
			set_bit(DMZ_META, &zone->flags);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dmz_emulate_zones(काष्ठा dmz_metadata *zmd, काष्ठा dmz_dev *dev)
अणु
	पूर्णांक idx;
	sector_t zone_offset = 0;

	क्रम(idx = 0; idx < dev->nr_zones; idx++) अणु
		काष्ठा dm_zone *zone;

		zone = dmz_insert(zmd, idx, dev);
		अगर (IS_ERR(zone))
			वापस PTR_ERR(zone);
		set_bit(DMZ_CACHE, &zone->flags);
		zone->wp_block = 0;
		zmd->nr_cache_zones++;
		zmd->nr_useable_zones++;
		अगर (dev->capacity - zone_offset < zmd->zone_nr_sectors) अणु
			/* Disable runt zone */
			set_bit(DMZ_OFFLINE, &zone->flags);
			अवरोध;
		पूर्ण
		zone_offset += zmd->zone_nr_sectors;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Free zones descriptors.
 */
अटल व्योम dmz_drop_zones(काष्ठा dmz_metadata *zmd)
अणु
	पूर्णांक idx;

	क्रम(idx = 0; idx < zmd->nr_zones; idx++) अणु
		काष्ठा dm_zone *zone = xa_load(&zmd->zones, idx);

		kमुक्त(zone);
		xa_erase(&zmd->zones, idx);
	पूर्ण
	xa_destroy(&zmd->zones);
पूर्ण

/*
 * Allocate and initialize zone descriptors using the zone
 * inक्रमmation from disk.
 */
अटल पूर्णांक dmz_init_zones(काष्ठा dmz_metadata *zmd)
अणु
	पूर्णांक i, ret;
	काष्ठा dmz_dev *zoned_dev = &zmd->dev[0];

	/* Init */
	zmd->zone_nr_sectors = zmd->dev[0].zone_nr_sectors;
	zmd->zone_nr_sectors_shअगरt = ilog2(zmd->zone_nr_sectors);
	zmd->zone_nr_blocks = dmz_sect2blk(zmd->zone_nr_sectors);
	zmd->zone_nr_blocks_shअगरt = ilog2(zmd->zone_nr_blocks);
	zmd->zone_biपंचांगap_size = zmd->zone_nr_blocks >> 3;
	zmd->zone_nr_biपंचांगap_blocks =
		max_t(sector_t, 1, zmd->zone_biपंचांगap_size >> DMZ_BLOCK_SHIFT);
	zmd->zone_bits_per_mblk = min_t(sector_t, zmd->zone_nr_blocks,
					DMZ_BLOCK_SIZE_BITS);

	/* Allocate zone array */
	zmd->nr_zones = 0;
	क्रम (i = 0; i < zmd->nr_devs; i++) अणु
		काष्ठा dmz_dev *dev = &zmd->dev[i];

		dev->metadata = zmd;
		zmd->nr_zones += dev->nr_zones;

		atomic_set(&dev->unmap_nr_rnd, 0);
		INIT_LIST_HEAD(&dev->unmap_rnd_list);
		INIT_LIST_HEAD(&dev->map_rnd_list);

		atomic_set(&dev->unmap_nr_seq, 0);
		INIT_LIST_HEAD(&dev->unmap_seq_list);
		INIT_LIST_HEAD(&dev->map_seq_list);
	पूर्ण

	अगर (!zmd->nr_zones) अणु
		DMERR("(%s): No zones found", zmd->devname);
		वापस -ENXIO;
	पूर्ण
	xa_init(&zmd->zones);

	DMDEBUG("(%s): Using %zu B for zone information",
		zmd->devname, माप(काष्ठा dm_zone) * zmd->nr_zones);

	अगर (zmd->nr_devs > 1) अणु
		ret = dmz_emulate_zones(zmd, &zmd->dev[0]);
		अगर (ret < 0) अणु
			DMDEBUG("(%s): Failed to emulate zones, error %d",
				zmd->devname, ret);
			dmz_drop_zones(zmd);
			वापस ret;
		पूर्ण

		/*
		 * Primary superblock zone is always at zone 0 when multiple
		 * drives are present.
		 */
		zmd->sb[0].zone = dmz_get(zmd, 0);

		क्रम (i = 1; i < zmd->nr_devs; i++) अणु
			zoned_dev = &zmd->dev[i];

			ret = blkdev_report_zones(zoned_dev->bdev, 0,
						  BLK_ALL_ZONES,
						  dmz_init_zone, zoned_dev);
			अगर (ret < 0) अणु
				DMDEBUG("(%s): Failed to report zones, error %d",
					zmd->devname, ret);
				dmz_drop_zones(zmd);
				वापस ret;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * Get zone inक्रमmation and initialize zone descriptors.  At the same
	 * समय, determine where the super block should be: first block of the
	 * first अक्रमomly writable zone.
	 */
	ret = blkdev_report_zones(zoned_dev->bdev, 0, BLK_ALL_ZONES,
				  dmz_init_zone, zoned_dev);
	अगर (ret < 0) अणु
		DMDEBUG("(%s): Failed to report zones, error %d",
			zmd->devname, ret);
		dmz_drop_zones(zmd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dmz_update_zone_cb(काष्ठा blk_zone *blkz, अचिन्हित पूर्णांक idx,
			      व्योम *data)
अणु
	काष्ठा dm_zone *zone = data;

	clear_bit(DMZ_OFFLINE, &zone->flags);
	clear_bit(DMZ_READ_ONLY, &zone->flags);
	अगर (blkz->cond == BLK_ZONE_COND_OFFLINE)
		set_bit(DMZ_OFFLINE, &zone->flags);
	अन्यथा अगर (blkz->cond == BLK_ZONE_COND_READONLY)
		set_bit(DMZ_READ_ONLY, &zone->flags);

	अगर (dmz_is_seq(zone))
		zone->wp_block = dmz_sect2blk(blkz->wp - blkz->start);
	अन्यथा
		zone->wp_block = 0;
	वापस 0;
पूर्ण

/*
 * Update a zone inक्रमmation.
 */
अटल पूर्णांक dmz_update_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	काष्ठा dmz_dev *dev = zone->dev;
	अचिन्हित पूर्णांक noio_flag;
	पूर्णांक ret;

	अगर (dev->flags & DMZ_BDEV_REGULAR)
		वापस 0;

	/*
	 * Get zone inक्रमmation from disk. Since blkdev_report_zones() uses
	 * GFP_KERNEL by शेष क्रम memory allocations, set the per-task
	 * PF_MEMALLOC_NOIO flag so that all allocations are करोne as अगर
	 * GFP_NOIO was specअगरied.
	 */
	noio_flag = meदो_स्मृति_noio_save();
	ret = blkdev_report_zones(dev->bdev, dmz_start_sect(zmd, zone), 1,
				  dmz_update_zone_cb, zone);
	meदो_स्मृति_noio_restore(noio_flag);

	अगर (ret == 0)
		ret = -EIO;
	अगर (ret < 0) अणु
		dmz_dev_err(dev, "Get zone %u report failed",
			    zone->id);
		dmz_check_bdev(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Check a zone ग_लिखो poपूर्णांकer position when the zone is marked
 * with the sequential ग_लिखो error flag.
 */
अटल पूर्णांक dmz_handle_seq_ग_लिखो_err(काष्ठा dmz_metadata *zmd,
				    काष्ठा dm_zone *zone)
अणु
	काष्ठा dmz_dev *dev = zone->dev;
	अचिन्हित पूर्णांक wp = 0;
	पूर्णांक ret;

	wp = zone->wp_block;
	ret = dmz_update_zone(zmd, zone);
	अगर (ret)
		वापस ret;

	dmz_dev_warn(dev, "Processing zone %u write error (zone wp %u/%u)",
		     zone->id, zone->wp_block, wp);

	अगर (zone->wp_block < wp) अणु
		dmz_invalidate_blocks(zmd, zone, zone->wp_block,
				      wp - zone->wp_block);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Reset a zone ग_लिखो poपूर्णांकer.
 */
अटल पूर्णांक dmz_reset_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	पूर्णांक ret;

	/*
	 * Ignore offline zones, पढ़ो only zones,
	 * and conventional zones.
	 */
	अगर (dmz_is_offline(zone) ||
	    dmz_is_पढ़ोonly(zone) ||
	    dmz_is_rnd(zone))
		वापस 0;

	अगर (!dmz_is_empty(zone) || dmz_seq_ग_लिखो_err(zone)) अणु
		काष्ठा dmz_dev *dev = zone->dev;

		ret = blkdev_zone_mgmt(dev->bdev, REQ_OP_ZONE_RESET,
				       dmz_start_sect(zmd, zone),
				       zmd->zone_nr_sectors, GFP_NOIO);
		अगर (ret) अणु
			dmz_dev_err(dev, "Reset zone %u failed %d",
				    zone->id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Clear ग_लिखो error bit and शुरुआत ग_लिखो poपूर्णांकer position */
	clear_bit(DMZ_SEQ_WRITE_ERR, &zone->flags);
	zone->wp_block = 0;

	वापस 0;
पूर्ण

अटल व्योम dmz_get_zone_weight(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone);

/*
 * Initialize chunk mapping.
 */
अटल पूर्णांक dmz_load_mapping(काष्ठा dmz_metadata *zmd)
अणु
	काष्ठा dm_zone *dzone, *bzone;
	काष्ठा dmz_mblock *dmap_mblk = शून्य;
	काष्ठा dmz_map *dmap;
	अचिन्हित पूर्णांक i = 0, e = 0, chunk = 0;
	अचिन्हित पूर्णांक dzone_id;
	अचिन्हित पूर्णांक bzone_id;

	/* Metadata block array क्रम the chunk mapping table */
	zmd->map_mblk = kसुस्मृति(zmd->nr_map_blocks,
				माप(काष्ठा dmz_mblk *), GFP_KERNEL);
	अगर (!zmd->map_mblk)
		वापस -ENOMEM;

	/* Get chunk mapping table blocks and initialize zone mapping */
	जबतक (chunk < zmd->nr_chunks) अणु
		अगर (!dmap_mblk) अणु
			/* Get mapping block */
			dmap_mblk = dmz_get_mblock(zmd, i + 1);
			अगर (IS_ERR(dmap_mblk))
				वापस PTR_ERR(dmap_mblk);
			zmd->map_mblk[i] = dmap_mblk;
			dmap = (काष्ठा dmz_map *) dmap_mblk->data;
			i++;
			e = 0;
		पूर्ण

		/* Check data zone */
		dzone_id = le32_to_cpu(dmap[e].dzone_id);
		अगर (dzone_id == DMZ_MAP_UNMAPPED)
			जाओ next;

		अगर (dzone_id >= zmd->nr_zones) अणु
			dmz_zmd_err(zmd, "Chunk %u mapping: invalid data zone ID %u",
				    chunk, dzone_id);
			वापस -EIO;
		पूर्ण

		dzone = dmz_get(zmd, dzone_id);
		अगर (!dzone) अणु
			dmz_zmd_err(zmd, "Chunk %u mapping: data zone %u not present",
				    chunk, dzone_id);
			वापस -EIO;
		पूर्ण
		set_bit(DMZ_DATA, &dzone->flags);
		dzone->chunk = chunk;
		dmz_get_zone_weight(zmd, dzone);

		अगर (dmz_is_cache(dzone))
			list_add_tail(&dzone->link, &zmd->map_cache_list);
		अन्यथा अगर (dmz_is_rnd(dzone))
			list_add_tail(&dzone->link, &dzone->dev->map_rnd_list);
		अन्यथा
			list_add_tail(&dzone->link, &dzone->dev->map_seq_list);

		/* Check buffer zone */
		bzone_id = le32_to_cpu(dmap[e].bzone_id);
		अगर (bzone_id == DMZ_MAP_UNMAPPED)
			जाओ next;

		अगर (bzone_id >= zmd->nr_zones) अणु
			dmz_zmd_err(zmd, "Chunk %u mapping: invalid buffer zone ID %u",
				    chunk, bzone_id);
			वापस -EIO;
		पूर्ण

		bzone = dmz_get(zmd, bzone_id);
		अगर (!bzone) अणु
			dmz_zmd_err(zmd, "Chunk %u mapping: buffer zone %u not present",
				    chunk, bzone_id);
			वापस -EIO;
		पूर्ण
		अगर (!dmz_is_rnd(bzone) && !dmz_is_cache(bzone)) अणु
			dmz_zmd_err(zmd, "Chunk %u mapping: invalid buffer zone %u",
				    chunk, bzone_id);
			वापस -EIO;
		पूर्ण

		set_bit(DMZ_DATA, &bzone->flags);
		set_bit(DMZ_BUF, &bzone->flags);
		bzone->chunk = chunk;
		bzone->bzone = dzone;
		dzone->bzone = bzone;
		dmz_get_zone_weight(zmd, bzone);
		अगर (dmz_is_cache(bzone))
			list_add_tail(&bzone->link, &zmd->map_cache_list);
		अन्यथा
			list_add_tail(&bzone->link, &bzone->dev->map_rnd_list);
next:
		chunk++;
		e++;
		अगर (e >= DMZ_MAP_ENTRIES)
			dmap_mblk = शून्य;
	पूर्ण

	/*
	 * At this poपूर्णांक, only meta zones and mapped data zones were
	 * fully initialized. All reमुख्यing zones are unmapped data
	 * zones. Finish initializing those here.
	 */
	क्रम (i = 0; i < zmd->nr_zones; i++) अणु
		dzone = dmz_get(zmd, i);
		अगर (!dzone)
			जारी;
		अगर (dmz_is_meta(dzone))
			जारी;
		अगर (dmz_is_offline(dzone))
			जारी;

		अगर (dmz_is_cache(dzone))
			zmd->nr_cache++;
		अन्यथा अगर (dmz_is_rnd(dzone))
			dzone->dev->nr_rnd++;
		अन्यथा
			dzone->dev->nr_seq++;

		अगर (dmz_is_data(dzone)) अणु
			/* Alपढ़ोy initialized */
			जारी;
		पूर्ण

		/* Unmapped data zone */
		set_bit(DMZ_DATA, &dzone->flags);
		dzone->chunk = DMZ_MAP_UNMAPPED;
		अगर (dmz_is_cache(dzone)) अणु
			list_add_tail(&dzone->link, &zmd->unmap_cache_list);
			atomic_inc(&zmd->unmap_nr_cache);
		पूर्ण अन्यथा अगर (dmz_is_rnd(dzone)) अणु
			list_add_tail(&dzone->link,
				      &dzone->dev->unmap_rnd_list);
			atomic_inc(&dzone->dev->unmap_nr_rnd);
		पूर्ण अन्यथा अगर (atomic_पढ़ो(&zmd->nr_reserved_seq_zones) < zmd->nr_reserved_seq) अणु
			list_add_tail(&dzone->link, &zmd->reserved_seq_zones_list);
			set_bit(DMZ_RESERVED, &dzone->flags);
			atomic_inc(&zmd->nr_reserved_seq_zones);
			dzone->dev->nr_seq--;
		पूर्ण अन्यथा अणु
			list_add_tail(&dzone->link,
				      &dzone->dev->unmap_seq_list);
			atomic_inc(&dzone->dev->unmap_nr_seq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set a data chunk mapping.
 */
अटल व्योम dmz_set_chunk_mapping(काष्ठा dmz_metadata *zmd, अचिन्हित पूर्णांक chunk,
				  अचिन्हित पूर्णांक dzone_id, अचिन्हित पूर्णांक bzone_id)
अणु
	काष्ठा dmz_mblock *dmap_mblk = zmd->map_mblk[chunk >> DMZ_MAP_ENTRIES_SHIFT];
	काष्ठा dmz_map *dmap = (काष्ठा dmz_map *) dmap_mblk->data;
	पूर्णांक map_idx = chunk & DMZ_MAP_ENTRIES_MASK;

	dmap[map_idx].dzone_id = cpu_to_le32(dzone_id);
	dmap[map_idx].bzone_id = cpu_to_le32(bzone_id);
	dmz_dirty_mblock(zmd, dmap_mblk);
पूर्ण

/*
 * The list of mapped zones is मुख्यtained in LRU order.
 * This rotates a zone at the end of its map list.
 */
अटल व्योम __dmz_lru_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	अगर (list_empty(&zone->link))
		वापस;

	list_del_init(&zone->link);
	अगर (dmz_is_seq(zone)) अणु
		/* LRU rotate sequential zone */
		list_add_tail(&zone->link, &zone->dev->map_seq_list);
	पूर्ण अन्यथा अगर (dmz_is_cache(zone)) अणु
		/* LRU rotate cache zone */
		list_add_tail(&zone->link, &zmd->map_cache_list);
	पूर्ण अन्यथा अणु
		/* LRU rotate अक्रमom zone */
		list_add_tail(&zone->link, &zone->dev->map_rnd_list);
	पूर्ण
पूर्ण

/*
 * The list of mapped अक्रमom zones is मुख्यtained
 * in LRU order. This rotates a zone at the end of the list.
 */
अटल व्योम dmz_lru_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	__dmz_lru_zone(zmd, zone);
	अगर (zone->bzone)
		__dmz_lru_zone(zmd, zone->bzone);
पूर्ण

/*
 * Wait क्रम any zone to be मुक्तd.
 */
अटल व्योम dmz_रुको_क्रम_मुक्त_zones(काष्ठा dmz_metadata *zmd)
अणु
	DEFINE_WAIT(रुको);

	prepare_to_रुको(&zmd->मुक्त_wq, &रुको, TASK_UNINTERRUPTIBLE);
	dmz_unlock_map(zmd);
	dmz_unlock_metadata(zmd);

	io_schedule_समयout(HZ);

	dmz_lock_metadata(zmd);
	dmz_lock_map(zmd);
	finish_रुको(&zmd->मुक्त_wq, &रुको);
पूर्ण

/*
 * Lock a zone क्रम reclaim (set the zone RECLAIM bit).
 * Returns false अगर the zone cannot be locked or अगर it is alपढ़ोy locked
 * and 1 otherwise.
 */
पूर्णांक dmz_lock_zone_reclaim(काष्ठा dm_zone *zone)
अणु
	/* Active zones cannot be reclaimed */
	अगर (dmz_is_active(zone))
		वापस 0;

	वापस !test_and_set_bit(DMZ_RECLAIM, &zone->flags);
पूर्ण

/*
 * Clear a zone reclaim flag.
 */
व्योम dmz_unlock_zone_reclaim(काष्ठा dm_zone *zone)
अणु
	WARN_ON(dmz_is_active(zone));
	WARN_ON(!dmz_in_reclaim(zone));

	clear_bit_unlock(DMZ_RECLAIM, &zone->flags);
	smp_mb__after_atomic();
	wake_up_bit(&zone->flags, DMZ_RECLAIM);
पूर्ण

/*
 * Wait क्रम a zone reclaim to complete.
 */
अटल व्योम dmz_रुको_क्रम_reclaim(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	dmz_unlock_map(zmd);
	dmz_unlock_metadata(zmd);
	set_bit(DMZ_RECLAIM_TERMINATE, &zone->flags);
	रुको_on_bit_समयout(&zone->flags, DMZ_RECLAIM, TASK_UNINTERRUPTIBLE, HZ);
	clear_bit(DMZ_RECLAIM_TERMINATE, &zone->flags);
	dmz_lock_metadata(zmd);
	dmz_lock_map(zmd);
पूर्ण

/*
 * Select a cache or अक्रमom ग_लिखो zone क्रम reclaim.
 */
अटल काष्ठा dm_zone *dmz_get_rnd_zone_क्रम_reclaim(काष्ठा dmz_metadata *zmd,
						    अचिन्हित पूर्णांक idx, bool idle)
अणु
	काष्ठा dm_zone *dzone = शून्य;
	काष्ठा dm_zone *zone, *maxw_z = शून्य;
	काष्ठा list_head *zone_list;

	/* If we have cache zones select from the cache zone list */
	अगर (zmd->nr_cache) अणु
		zone_list = &zmd->map_cache_list;
		/* Try to relaim अक्रमom zones, too, when idle */
		अगर (idle && list_empty(zone_list))
			zone_list = &zmd->dev[idx].map_rnd_list;
	पूर्ण अन्यथा
		zone_list = &zmd->dev[idx].map_rnd_list;

	/*
	 * Find the buffer zone with the heaviest weight or the first (oldest)
	 * data zone that can be reclaimed.
	 */
	list_क्रम_each_entry(zone, zone_list, link) अणु
		अगर (dmz_is_buf(zone)) अणु
			dzone = zone->bzone;
			अगर (dmz_is_rnd(dzone) && dzone->dev->dev_idx != idx)
				जारी;
			अगर (!maxw_z || maxw_z->weight < dzone->weight)
				maxw_z = dzone;
		पूर्ण अन्यथा अणु
			dzone = zone;
			अगर (dmz_lock_zone_reclaim(dzone))
				वापस dzone;
		पूर्ण
	पूर्ण

	अगर (maxw_z && dmz_lock_zone_reclaim(maxw_z))
		वापस maxw_z;

	/*
	 * If we come here, none of the zones inspected could be locked क्रम
	 * reclaim. Try again, being more aggressive, that is, find the
	 * first zone that can be reclaimed regardless of its weitght.
	 */
	list_क्रम_each_entry(zone, zone_list, link) अणु
		अगर (dmz_is_buf(zone)) अणु
			dzone = zone->bzone;
			अगर (dmz_is_rnd(dzone) && dzone->dev->dev_idx != idx)
				जारी;
		पूर्ण अन्यथा
			dzone = zone;
		अगर (dmz_lock_zone_reclaim(dzone))
			वापस dzone;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Select a buffered sequential zone क्रम reclaim.
 */
अटल काष्ठा dm_zone *dmz_get_seq_zone_क्रम_reclaim(काष्ठा dmz_metadata *zmd,
						    अचिन्हित पूर्णांक idx)
अणु
	काष्ठा dm_zone *zone;

	list_क्रम_each_entry(zone, &zmd->dev[idx].map_seq_list, link) अणु
		अगर (!zone->bzone)
			जारी;
		अगर (dmz_lock_zone_reclaim(zone))
			वापस zone;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Select a zone क्रम reclaim.
 */
काष्ठा dm_zone *dmz_get_zone_क्रम_reclaim(काष्ठा dmz_metadata *zmd,
					 अचिन्हित पूर्णांक dev_idx, bool idle)
अणु
	काष्ठा dm_zone *zone = शून्य;

	/*
	 * Search क्रम a zone candidate to reclaim: 2 हालs are possible.
	 * (1) There is no मुक्त sequential zones. Then a अक्रमom data zone
	 *     cannot be reclaimed. So choose a sequential zone to reclaim so
	 *     that afterward a अक्रमom zone can be reclaimed.
	 * (2) At least one मुक्त sequential zone is available, then choose
	 *     the oldest अक्रमom zone (data or buffer) that can be locked.
	 */
	dmz_lock_map(zmd);
	अगर (list_empty(&zmd->reserved_seq_zones_list))
		zone = dmz_get_seq_zone_क्रम_reclaim(zmd, dev_idx);
	अगर (!zone)
		zone = dmz_get_rnd_zone_क्रम_reclaim(zmd, dev_idx, idle);
	dmz_unlock_map(zmd);

	वापस zone;
पूर्ण

/*
 * Get the zone mapping a chunk, अगर the chunk is mapped alपढ़ोy.
 * If no mapping exist and the operation is WRITE, a zone is
 * allocated and used to map the chunk.
 * The zone वापसed will be set to the active state.
 */
काष्ठा dm_zone *dmz_get_chunk_mapping(काष्ठा dmz_metadata *zmd, अचिन्हित पूर्णांक chunk, पूर्णांक op)
अणु
	काष्ठा dmz_mblock *dmap_mblk = zmd->map_mblk[chunk >> DMZ_MAP_ENTRIES_SHIFT];
	काष्ठा dmz_map *dmap = (काष्ठा dmz_map *) dmap_mblk->data;
	पूर्णांक dmap_idx = chunk & DMZ_MAP_ENTRIES_MASK;
	अचिन्हित पूर्णांक dzone_id;
	काष्ठा dm_zone *dzone = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक alloc_flags = zmd->nr_cache ? DMZ_ALLOC_CACHE : DMZ_ALLOC_RND;

	dmz_lock_map(zmd);
again:
	/* Get the chunk mapping */
	dzone_id = le32_to_cpu(dmap[dmap_idx].dzone_id);
	अगर (dzone_id == DMZ_MAP_UNMAPPED) अणु
		/*
		 * Read or discard in unmapped chunks are fine. But क्रम
		 * ग_लिखोs, we need a mapping, so get one.
		 */
		अगर (op != REQ_OP_WRITE)
			जाओ out;

		/* Allocate a अक्रमom zone */
		dzone = dmz_alloc_zone(zmd, 0, alloc_flags);
		अगर (!dzone) अणु
			अगर (dmz_dev_is_dying(zmd)) अणु
				dzone = ERR_PTR(-EIO);
				जाओ out;
			पूर्ण
			dmz_रुको_क्रम_मुक्त_zones(zmd);
			जाओ again;
		पूर्ण

		dmz_map_zone(zmd, dzone, chunk);

	पूर्ण अन्यथा अणु
		/* The chunk is alपढ़ोy mapped: get the mapping zone */
		dzone = dmz_get(zmd, dzone_id);
		अगर (!dzone) अणु
			dzone = ERR_PTR(-EIO);
			जाओ out;
		पूर्ण
		अगर (dzone->chunk != chunk) अणु
			dzone = ERR_PTR(-EIO);
			जाओ out;
		पूर्ण

		/* Repair ग_लिखो poपूर्णांकer अगर the sequential dzone has error */
		अगर (dmz_seq_ग_लिखो_err(dzone)) अणु
			ret = dmz_handle_seq_ग_लिखो_err(zmd, dzone);
			अगर (ret) अणु
				dzone = ERR_PTR(-EIO);
				जाओ out;
			पूर्ण
			clear_bit(DMZ_SEQ_WRITE_ERR, &dzone->flags);
		पूर्ण
	पूर्ण

	/*
	 * If the zone is being reclaimed, the chunk mapping may change
	 * to a dअगरferent zone. So रुको क्रम reclaim and retry. Otherwise,
	 * activate the zone (this will prevent reclaim from touching it).
	 */
	अगर (dmz_in_reclaim(dzone)) अणु
		dmz_रुको_क्रम_reclaim(zmd, dzone);
		जाओ again;
	पूर्ण
	dmz_activate_zone(dzone);
	dmz_lru_zone(zmd, dzone);
out:
	dmz_unlock_map(zmd);

	वापस dzone;
पूर्ण

/*
 * Write and discard change the block validity of data zones and their buffer
 * zones. Check here that valid blocks are still present. If all blocks are
 * invalid, the zones can be unmapped on the fly without रुकोing क्रम reclaim
 * to करो it.
 */
व्योम dmz_put_chunk_mapping(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *dzone)
अणु
	काष्ठा dm_zone *bzone;

	dmz_lock_map(zmd);

	bzone = dzone->bzone;
	अगर (bzone) अणु
		अगर (dmz_weight(bzone))
			dmz_lru_zone(zmd, bzone);
		अन्यथा अणु
			/* Empty buffer zone: reclaim it */
			dmz_unmap_zone(zmd, bzone);
			dmz_मुक्त_zone(zmd, bzone);
			bzone = शून्य;
		पूर्ण
	पूर्ण

	/* Deactivate the data zone */
	dmz_deactivate_zone(dzone);
	अगर (dmz_is_active(dzone) || bzone || dmz_weight(dzone))
		dmz_lru_zone(zmd, dzone);
	अन्यथा अणु
		/* Unbuffered inactive empty data zone: reclaim it */
		dmz_unmap_zone(zmd, dzone);
		dmz_मुक्त_zone(zmd, dzone);
	पूर्ण

	dmz_unlock_map(zmd);
पूर्ण

/*
 * Allocate and map a अक्रमom zone to buffer a chunk
 * alपढ़ोy mapped to a sequential zone.
 */
काष्ठा dm_zone *dmz_get_chunk_buffer(काष्ठा dmz_metadata *zmd,
				     काष्ठा dm_zone *dzone)
अणु
	काष्ठा dm_zone *bzone;
	पूर्णांक alloc_flags = zmd->nr_cache ? DMZ_ALLOC_CACHE : DMZ_ALLOC_RND;

	dmz_lock_map(zmd);
again:
	bzone = dzone->bzone;
	अगर (bzone)
		जाओ out;

	/* Allocate a अक्रमom zone */
	bzone = dmz_alloc_zone(zmd, 0, alloc_flags);
	अगर (!bzone) अणु
		अगर (dmz_dev_is_dying(zmd)) अणु
			bzone = ERR_PTR(-EIO);
			जाओ out;
		पूर्ण
		dmz_रुको_क्रम_मुक्त_zones(zmd);
		जाओ again;
	पूर्ण

	/* Update the chunk mapping */
	dmz_set_chunk_mapping(zmd, dzone->chunk, dzone->id, bzone->id);

	set_bit(DMZ_BUF, &bzone->flags);
	bzone->chunk = dzone->chunk;
	bzone->bzone = dzone;
	dzone->bzone = bzone;
	अगर (dmz_is_cache(bzone))
		list_add_tail(&bzone->link, &zmd->map_cache_list);
	अन्यथा
		list_add_tail(&bzone->link, &bzone->dev->map_rnd_list);
out:
	dmz_unlock_map(zmd);

	वापस bzone;
पूर्ण

/*
 * Get an unmapped (मुक्त) zone.
 * This must be called with the mapping lock held.
 */
काष्ठा dm_zone *dmz_alloc_zone(काष्ठा dmz_metadata *zmd, अचिन्हित पूर्णांक dev_idx,
			       अचिन्हित दीर्घ flags)
अणु
	काष्ठा list_head *list;
	काष्ठा dm_zone *zone;
	पूर्णांक i;

	/* Schedule reclaim to ensure मुक्त zones are available */
	अगर (!(flags & DMZ_ALLOC_RECLAIM)) अणु
		क्रम (i = 0; i < zmd->nr_devs; i++)
			dmz_schedule_reclaim(zmd->dev[i].reclaim);
	पूर्ण

	i = 0;
again:
	अगर (flags & DMZ_ALLOC_CACHE)
		list = &zmd->unmap_cache_list;
	अन्यथा अगर (flags & DMZ_ALLOC_RND)
		list = &zmd->dev[dev_idx].unmap_rnd_list;
	अन्यथा
		list = &zmd->dev[dev_idx].unmap_seq_list;

	अगर (list_empty(list)) अणु
		/*
		 * No मुक्त zone: वापस शून्य अगर this is क्रम not reclaim.
		 */
		अगर (!(flags & DMZ_ALLOC_RECLAIM))
			वापस शून्य;
		/*
		 * Try to allocate from other devices
		 */
		अगर (i < zmd->nr_devs) अणु
			dev_idx = (dev_idx + 1) % zmd->nr_devs;
			i++;
			जाओ again;
		पूर्ण

		/*
		 * Fallback to the reserved sequential zones
		 */
		zone = list_first_entry_or_null(&zmd->reserved_seq_zones_list,
						काष्ठा dm_zone, link);
		अगर (zone) अणु
			list_del_init(&zone->link);
			atomic_dec(&zmd->nr_reserved_seq_zones);
		पूर्ण
		वापस zone;
	पूर्ण

	zone = list_first_entry(list, काष्ठा dm_zone, link);
	list_del_init(&zone->link);

	अगर (dmz_is_cache(zone))
		atomic_dec(&zmd->unmap_nr_cache);
	अन्यथा अगर (dmz_is_rnd(zone))
		atomic_dec(&zone->dev->unmap_nr_rnd);
	अन्यथा
		atomic_dec(&zone->dev->unmap_nr_seq);

	अगर (dmz_is_offline(zone)) अणु
		dmz_zmd_warn(zmd, "Zone %u is offline", zone->id);
		zone = शून्य;
		जाओ again;
	पूर्ण
	अगर (dmz_is_meta(zone)) अणु
		dmz_zmd_warn(zmd, "Zone %u has metadata", zone->id);
		zone = शून्य;
		जाओ again;
	पूर्ण
	वापस zone;
पूर्ण

/*
 * Free a zone.
 * This must be called with the mapping lock held.
 */
व्योम dmz_मुक्त_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	/* If this is a sequential zone, reset it */
	अगर (dmz_is_seq(zone))
		dmz_reset_zone(zmd, zone);

	/* Return the zone to its type unmap list */
	अगर (dmz_is_cache(zone)) अणु
		list_add_tail(&zone->link, &zmd->unmap_cache_list);
		atomic_inc(&zmd->unmap_nr_cache);
	पूर्ण अन्यथा अगर (dmz_is_rnd(zone)) अणु
		list_add_tail(&zone->link, &zone->dev->unmap_rnd_list);
		atomic_inc(&zone->dev->unmap_nr_rnd);
	पूर्ण अन्यथा अगर (dmz_is_reserved(zone)) अणु
		list_add_tail(&zone->link, &zmd->reserved_seq_zones_list);
		atomic_inc(&zmd->nr_reserved_seq_zones);
	पूर्ण अन्यथा अणु
		list_add_tail(&zone->link, &zone->dev->unmap_seq_list);
		atomic_inc(&zone->dev->unmap_nr_seq);
	पूर्ण

	wake_up_all(&zmd->मुक्त_wq);
पूर्ण

/*
 * Map a chunk to a zone.
 * This must be called with the mapping lock held.
 */
व्योम dmz_map_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *dzone,
		  अचिन्हित पूर्णांक chunk)
अणु
	/* Set the chunk mapping */
	dmz_set_chunk_mapping(zmd, chunk, dzone->id,
			      DMZ_MAP_UNMAPPED);
	dzone->chunk = chunk;
	अगर (dmz_is_cache(dzone))
		list_add_tail(&dzone->link, &zmd->map_cache_list);
	अन्यथा अगर (dmz_is_rnd(dzone))
		list_add_tail(&dzone->link, &dzone->dev->map_rnd_list);
	अन्यथा
		list_add_tail(&dzone->link, &dzone->dev->map_seq_list);
पूर्ण

/*
 * Unmap a zone.
 * This must be called with the mapping lock held.
 */
व्योम dmz_unmap_zone(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	अचिन्हित पूर्णांक chunk = zone->chunk;
	अचिन्हित पूर्णांक dzone_id;

	अगर (chunk == DMZ_MAP_UNMAPPED) अणु
		/* Alपढ़ोy unmapped */
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(DMZ_BUF, &zone->flags)) अणु
		/*
		 * Unmapping the chunk buffer zone: clear only
		 * the chunk buffer mapping
		 */
		dzone_id = zone->bzone->id;
		zone->bzone->bzone = शून्य;
		zone->bzone = शून्य;

	पूर्ण अन्यथा अणु
		/*
		 * Unmapping the chunk data zone: the zone must
		 * not be buffered.
		 */
		अगर (WARN_ON(zone->bzone)) अणु
			zone->bzone->bzone = शून्य;
			zone->bzone = शून्य;
		पूर्ण
		dzone_id = DMZ_MAP_UNMAPPED;
	पूर्ण

	dmz_set_chunk_mapping(zmd, chunk, dzone_id, DMZ_MAP_UNMAPPED);

	zone->chunk = DMZ_MAP_UNMAPPED;
	list_del_init(&zone->link);
पूर्ण

/*
 * Set @nr_bits bits in @biपंचांगap starting from @bit.
 * Return the number of bits changed from 0 to 1.
 */
अटल अचिन्हित पूर्णांक dmz_set_bits(अचिन्हित दीर्घ *biपंचांगap,
				 अचिन्हित पूर्णांक bit, अचिन्हित पूर्णांक nr_bits)
अणु
	अचिन्हित दीर्घ *addr;
	अचिन्हित पूर्णांक end = bit + nr_bits;
	अचिन्हित पूर्णांक n = 0;

	जबतक (bit < end) अणु
		अगर (((bit & (BITS_PER_LONG - 1)) == 0) &&
		    ((end - bit) >= BITS_PER_LONG)) अणु
			/* Try to set the whole word at once */
			addr = biपंचांगap + BIT_WORD(bit);
			अगर (*addr == 0) अणु
				*addr = अच_दीर्घ_उच्च;
				n += BITS_PER_LONG;
				bit += BITS_PER_LONG;
				जारी;
			पूर्ण
		पूर्ण

		अगर (!test_and_set_bit(bit, biपंचांगap))
			n++;
		bit++;
	पूर्ण

	वापस n;
पूर्ण

/*
 * Get the biपंचांगap block storing the bit क्रम chunk_block in zone.
 */
अटल काष्ठा dmz_mblock *dmz_get_biपंचांगap(काष्ठा dmz_metadata *zmd,
					 काष्ठा dm_zone *zone,
					 sector_t chunk_block)
अणु
	sector_t biपंचांगap_block = 1 + zmd->nr_map_blocks +
		(sector_t)(zone->id * zmd->zone_nr_biपंचांगap_blocks) +
		(chunk_block >> DMZ_BLOCK_SHIFT_BITS);

	वापस dmz_get_mblock(zmd, biपंचांगap_block);
पूर्ण

/*
 * Copy the valid blocks biपंचांगap of from_zone to the biपंचांगap of to_zone.
 */
पूर्णांक dmz_copy_valid_blocks(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *from_zone,
			  काष्ठा dm_zone *to_zone)
अणु
	काष्ठा dmz_mblock *from_mblk, *to_mblk;
	sector_t chunk_block = 0;

	/* Get the zones biपंचांगap blocks */
	जबतक (chunk_block < zmd->zone_nr_blocks) अणु
		from_mblk = dmz_get_biपंचांगap(zmd, from_zone, chunk_block);
		अगर (IS_ERR(from_mblk))
			वापस PTR_ERR(from_mblk);
		to_mblk = dmz_get_biपंचांगap(zmd, to_zone, chunk_block);
		अगर (IS_ERR(to_mblk)) अणु
			dmz_release_mblock(zmd, from_mblk);
			वापस PTR_ERR(to_mblk);
		पूर्ण

		स_नकल(to_mblk->data, from_mblk->data, DMZ_BLOCK_SIZE);
		dmz_dirty_mblock(zmd, to_mblk);

		dmz_release_mblock(zmd, to_mblk);
		dmz_release_mblock(zmd, from_mblk);

		chunk_block += zmd->zone_bits_per_mblk;
	पूर्ण

	to_zone->weight = from_zone->weight;

	वापस 0;
पूर्ण

/*
 * Merge the valid blocks biपंचांगap of from_zone पूर्णांकo the biपंचांगap of to_zone,
 * starting from chunk_block.
 */
पूर्णांक dmz_merge_valid_blocks(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *from_zone,
			   काष्ठा dm_zone *to_zone, sector_t chunk_block)
अणु
	अचिन्हित पूर्णांक nr_blocks;
	पूर्णांक ret;

	/* Get the zones biपंचांगap blocks */
	जबतक (chunk_block < zmd->zone_nr_blocks) अणु
		/* Get a valid region from the source zone */
		ret = dmz_first_valid_block(zmd, from_zone, &chunk_block);
		अगर (ret <= 0)
			वापस ret;

		nr_blocks = ret;
		ret = dmz_validate_blocks(zmd, to_zone, chunk_block, nr_blocks);
		अगर (ret)
			वापस ret;

		chunk_block += nr_blocks;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Validate all the blocks in the range [block..block+nr_blocks-1].
 */
पूर्णांक dmz_validate_blocks(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
			sector_t chunk_block, अचिन्हित पूर्णांक nr_blocks)
अणु
	अचिन्हित पूर्णांक count, bit, nr_bits;
	अचिन्हित पूर्णांक zone_nr_blocks = zmd->zone_nr_blocks;
	काष्ठा dmz_mblock *mblk;
	अचिन्हित पूर्णांक n = 0;

	dmz_zmd_debug(zmd, "=> VALIDATE zone %u, block %llu, %u blocks",
		      zone->id, (अचिन्हित दीर्घ दीर्घ)chunk_block,
		      nr_blocks);

	WARN_ON(chunk_block + nr_blocks > zone_nr_blocks);

	जबतक (nr_blocks) अणु
		/* Get biपंचांगap block */
		mblk = dmz_get_biपंचांगap(zmd, zone, chunk_block);
		अगर (IS_ERR(mblk))
			वापस PTR_ERR(mblk);

		/* Set bits */
		bit = chunk_block & DMZ_BLOCK_MASK_BITS;
		nr_bits = min(nr_blocks, zmd->zone_bits_per_mblk - bit);

		count = dmz_set_bits((अचिन्हित दीर्घ *)mblk->data, bit, nr_bits);
		अगर (count) अणु
			dmz_dirty_mblock(zmd, mblk);
			n += count;
		पूर्ण
		dmz_release_mblock(zmd, mblk);

		nr_blocks -= nr_bits;
		chunk_block += nr_bits;
	पूर्ण

	अगर (likely(zone->weight + n <= zone_nr_blocks))
		zone->weight += n;
	अन्यथा अणु
		dmz_zmd_warn(zmd, "Zone %u: weight %u should be <= %u",
			     zone->id, zone->weight,
			     zone_nr_blocks - n);
		zone->weight = zone_nr_blocks;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Clear nr_bits bits in biपंचांगap starting from bit.
 * Return the number of bits cleared.
 */
अटल पूर्णांक dmz_clear_bits(अचिन्हित दीर्घ *biपंचांगap, पूर्णांक bit, पूर्णांक nr_bits)
अणु
	अचिन्हित दीर्घ *addr;
	पूर्णांक end = bit + nr_bits;
	पूर्णांक n = 0;

	जबतक (bit < end) अणु
		अगर (((bit & (BITS_PER_LONG - 1)) == 0) &&
		    ((end - bit) >= BITS_PER_LONG)) अणु
			/* Try to clear whole word at once */
			addr = biपंचांगap + BIT_WORD(bit);
			अगर (*addr == अच_दीर्घ_उच्च) अणु
				*addr = 0;
				n += BITS_PER_LONG;
				bit += BITS_PER_LONG;
				जारी;
			पूर्ण
		पूर्ण

		अगर (test_and_clear_bit(bit, biपंचांगap))
			n++;
		bit++;
	पूर्ण

	वापस n;
पूर्ण

/*
 * Invalidate all the blocks in the range [block..block+nr_blocks-1].
 */
पूर्णांक dmz_invalidate_blocks(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
			  sector_t chunk_block, अचिन्हित पूर्णांक nr_blocks)
अणु
	अचिन्हित पूर्णांक count, bit, nr_bits;
	काष्ठा dmz_mblock *mblk;
	अचिन्हित पूर्णांक n = 0;

	dmz_zmd_debug(zmd, "=> INVALIDATE zone %u, block %llu, %u blocks",
		      zone->id, (u64)chunk_block, nr_blocks);

	WARN_ON(chunk_block + nr_blocks > zmd->zone_nr_blocks);

	जबतक (nr_blocks) अणु
		/* Get biपंचांगap block */
		mblk = dmz_get_biपंचांगap(zmd, zone, chunk_block);
		अगर (IS_ERR(mblk))
			वापस PTR_ERR(mblk);

		/* Clear bits */
		bit = chunk_block & DMZ_BLOCK_MASK_BITS;
		nr_bits = min(nr_blocks, zmd->zone_bits_per_mblk - bit);

		count = dmz_clear_bits((अचिन्हित दीर्घ *)mblk->data,
				       bit, nr_bits);
		अगर (count) अणु
			dmz_dirty_mblock(zmd, mblk);
			n += count;
		पूर्ण
		dmz_release_mblock(zmd, mblk);

		nr_blocks -= nr_bits;
		chunk_block += nr_bits;
	पूर्ण

	अगर (zone->weight >= n)
		zone->weight -= n;
	अन्यथा अणु
		dmz_zmd_warn(zmd, "Zone %u: weight %u should be >= %u",
			     zone->id, zone->weight, n);
		zone->weight = 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get a block bit value.
 */
अटल पूर्णांक dmz_test_block(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
			  sector_t chunk_block)
अणु
	काष्ठा dmz_mblock *mblk;
	पूर्णांक ret;

	WARN_ON(chunk_block >= zmd->zone_nr_blocks);

	/* Get biपंचांगap block */
	mblk = dmz_get_biपंचांगap(zmd, zone, chunk_block);
	अगर (IS_ERR(mblk))
		वापस PTR_ERR(mblk);

	/* Get offset */
	ret = test_bit(chunk_block & DMZ_BLOCK_MASK_BITS,
		       (अचिन्हित दीर्घ *) mblk->data) != 0;

	dmz_release_mblock(zmd, mblk);

	वापस ret;
पूर्ण

/*
 * Return the number of blocks from chunk_block to the first block with a bit
 * value specअगरied by set. Search at most nr_blocks blocks from chunk_block.
 */
अटल पूर्णांक dmz_to_next_set_block(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
				 sector_t chunk_block, अचिन्हित पूर्णांक nr_blocks,
				 पूर्णांक set)
अणु
	काष्ठा dmz_mblock *mblk;
	अचिन्हित पूर्णांक bit, set_bit, nr_bits;
	अचिन्हित पूर्णांक zone_bits = zmd->zone_bits_per_mblk;
	अचिन्हित दीर्घ *biपंचांगap;
	पूर्णांक n = 0;

	WARN_ON(chunk_block + nr_blocks > zmd->zone_nr_blocks);

	जबतक (nr_blocks) अणु
		/* Get biपंचांगap block */
		mblk = dmz_get_biपंचांगap(zmd, zone, chunk_block);
		अगर (IS_ERR(mblk))
			वापस PTR_ERR(mblk);

		/* Get offset */
		biपंचांगap = (अचिन्हित दीर्घ *) mblk->data;
		bit = chunk_block & DMZ_BLOCK_MASK_BITS;
		nr_bits = min(nr_blocks, zone_bits - bit);
		अगर (set)
			set_bit = find_next_bit(biपंचांगap, zone_bits, bit);
		अन्यथा
			set_bit = find_next_zero_bit(biपंचांगap, zone_bits, bit);
		dmz_release_mblock(zmd, mblk);

		n += set_bit - bit;
		अगर (set_bit < zone_bits)
			अवरोध;

		nr_blocks -= nr_bits;
		chunk_block += nr_bits;
	पूर्ण

	वापस n;
पूर्ण

/*
 * Test अगर chunk_block is valid. If it is, the number of consecutive
 * valid blocks from chunk_block will be वापसed.
 */
पूर्णांक dmz_block_valid(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
		    sector_t chunk_block)
अणु
	पूर्णांक valid;

	valid = dmz_test_block(zmd, zone, chunk_block);
	अगर (valid <= 0)
		वापस valid;

	/* The block is valid: get the number of valid blocks from block */
	वापस dmz_to_next_set_block(zmd, zone, chunk_block,
				     zmd->zone_nr_blocks - chunk_block, 0);
पूर्ण

/*
 * Find the first valid block from @chunk_block in @zone.
 * If such a block is found, its number is वापसed using
 * @chunk_block and the total number of valid blocks from @chunk_block
 * is वापसed.
 */
पूर्णांक dmz_first_valid_block(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone,
			  sector_t *chunk_block)
अणु
	sector_t start_block = *chunk_block;
	पूर्णांक ret;

	ret = dmz_to_next_set_block(zmd, zone, start_block,
				    zmd->zone_nr_blocks - start_block, 1);
	अगर (ret < 0)
		वापस ret;

	start_block += ret;
	*chunk_block = start_block;

	वापस dmz_to_next_set_block(zmd, zone, start_block,
				     zmd->zone_nr_blocks - start_block, 0);
पूर्ण

/*
 * Count the number of bits set starting from bit up to bit + nr_bits - 1.
 */
अटल पूर्णांक dmz_count_bits(व्योम *biपंचांगap, पूर्णांक bit, पूर्णांक nr_bits)
अणु
	अचिन्हित दीर्घ *addr;
	पूर्णांक end = bit + nr_bits;
	पूर्णांक n = 0;

	जबतक (bit < end) अणु
		अगर (((bit & (BITS_PER_LONG - 1)) == 0) &&
		    ((end - bit) >= BITS_PER_LONG)) अणु
			addr = (अचिन्हित दीर्घ *)biपंचांगap + BIT_WORD(bit);
			अगर (*addr == अच_दीर्घ_उच्च) अणु
				n += BITS_PER_LONG;
				bit += BITS_PER_LONG;
				जारी;
			पूर्ण
		पूर्ण

		अगर (test_bit(bit, biपंचांगap))
			n++;
		bit++;
	पूर्ण

	वापस n;
पूर्ण

/*
 * Get a zone weight.
 */
अटल व्योम dmz_get_zone_weight(काष्ठा dmz_metadata *zmd, काष्ठा dm_zone *zone)
अणु
	काष्ठा dmz_mblock *mblk;
	sector_t chunk_block = 0;
	अचिन्हित पूर्णांक bit, nr_bits;
	अचिन्हित पूर्णांक nr_blocks = zmd->zone_nr_blocks;
	व्योम *biपंचांगap;
	पूर्णांक n = 0;

	जबतक (nr_blocks) अणु
		/* Get biपंचांगap block */
		mblk = dmz_get_biपंचांगap(zmd, zone, chunk_block);
		अगर (IS_ERR(mblk)) अणु
			n = 0;
			अवरोध;
		पूर्ण

		/* Count bits in this block */
		biपंचांगap = mblk->data;
		bit = chunk_block & DMZ_BLOCK_MASK_BITS;
		nr_bits = min(nr_blocks, zmd->zone_bits_per_mblk - bit);
		n += dmz_count_bits(biपंचांगap, bit, nr_bits);

		dmz_release_mblock(zmd, mblk);

		nr_blocks -= nr_bits;
		chunk_block += nr_bits;
	पूर्ण

	zone->weight = n;
पूर्ण

/*
 * Cleanup the zoned metadata resources.
 */
अटल व्योम dmz_cleanup_metadata(काष्ठा dmz_metadata *zmd)
अणु
	काष्ठा rb_root *root;
	काष्ठा dmz_mblock *mblk, *next;
	पूर्णांक i;

	/* Release zone mapping resources */
	अगर (zmd->map_mblk) अणु
		क्रम (i = 0; i < zmd->nr_map_blocks; i++)
			dmz_release_mblock(zmd, zmd->map_mblk[i]);
		kमुक्त(zmd->map_mblk);
		zmd->map_mblk = शून्य;
	पूर्ण

	/* Release super blocks */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (zmd->sb[i].mblk) अणु
			dmz_मुक्त_mblock(zmd, zmd->sb[i].mblk);
			zmd->sb[i].mblk = शून्य;
		पूर्ण
	पूर्ण

	/* Free cached blocks */
	जबतक (!list_empty(&zmd->mblk_dirty_list)) अणु
		mblk = list_first_entry(&zmd->mblk_dirty_list,
					काष्ठा dmz_mblock, link);
		dmz_zmd_warn(zmd, "mblock %llu still in dirty list (ref %u)",
			     (u64)mblk->no, mblk->ref);
		list_del_init(&mblk->link);
		rb_erase(&mblk->node, &zmd->mblk_rbtree);
		dmz_मुक्त_mblock(zmd, mblk);
	पूर्ण

	जबतक (!list_empty(&zmd->mblk_lru_list)) अणु
		mblk = list_first_entry(&zmd->mblk_lru_list,
					काष्ठा dmz_mblock, link);
		list_del_init(&mblk->link);
		rb_erase(&mblk->node, &zmd->mblk_rbtree);
		dmz_मुक्त_mblock(zmd, mblk);
	पूर्ण

	/* Sanity checks: the mblock rbtree should now be empty */
	root = &zmd->mblk_rbtree;
	rbtree_postorder_क्रम_each_entry_safe(mblk, next, root, node) अणु
		dmz_zmd_warn(zmd, "mblock %llu ref %u still in rbtree",
			     (u64)mblk->no, mblk->ref);
		mblk->ref = 0;
		dmz_मुक्त_mblock(zmd, mblk);
	पूर्ण

	/* Free the zone descriptors */
	dmz_drop_zones(zmd);

	mutex_destroy(&zmd->mblk_flush_lock);
	mutex_destroy(&zmd->map_lock);
पूर्ण

अटल व्योम dmz_prपूर्णांक_dev(काष्ठा dmz_metadata *zmd, पूर्णांक num)
अणु
	काष्ठा dmz_dev *dev = &zmd->dev[num];

	अगर (bdev_zoned_model(dev->bdev) == BLK_ZONED_NONE)
		dmz_dev_info(dev, "Regular block device");
	अन्यथा
		dmz_dev_info(dev, "Host-%s zoned block device",
			     bdev_zoned_model(dev->bdev) == BLK_ZONED_HA ?
			     "aware" : "managed");
	अगर (zmd->sb_version > 1) अणु
		sector_t sector_offset =
			dev->zone_offset << zmd->zone_nr_sectors_shअगरt;

		dmz_dev_info(dev, "  %llu 512-byte logical sectors (offset %llu)",
			     (u64)dev->capacity, (u64)sector_offset);
		dmz_dev_info(dev, "  %u zones of %llu 512-byte logical sectors (offset %llu)",
			     dev->nr_zones, (u64)zmd->zone_nr_sectors,
			     (u64)dev->zone_offset);
	पूर्ण अन्यथा अणु
		dmz_dev_info(dev, "  %llu 512-byte logical sectors",
			     (u64)dev->capacity);
		dmz_dev_info(dev, "  %u zones of %llu 512-byte logical sectors",
			     dev->nr_zones, (u64)zmd->zone_nr_sectors);
	पूर्ण
पूर्ण

/*
 * Initialize the zoned metadata.
 */
पूर्णांक dmz_ctr_metadata(काष्ठा dmz_dev *dev, पूर्णांक num_dev,
		     काष्ठा dmz_metadata **metadata,
		     स्थिर अक्षर *devname)
अणु
	काष्ठा dmz_metadata *zmd;
	अचिन्हित पूर्णांक i;
	काष्ठा dm_zone *zone;
	पूर्णांक ret;

	zmd = kzalloc(माप(काष्ठा dmz_metadata), GFP_KERNEL);
	अगर (!zmd)
		वापस -ENOMEM;

	म_नकल(zmd->devname, devname);
	zmd->dev = dev;
	zmd->nr_devs = num_dev;
	zmd->mblk_rbtree = RB_ROOT;
	init_rwsem(&zmd->mblk_sem);
	mutex_init(&zmd->mblk_flush_lock);
	spin_lock_init(&zmd->mblk_lock);
	INIT_LIST_HEAD(&zmd->mblk_lru_list);
	INIT_LIST_HEAD(&zmd->mblk_dirty_list);

	mutex_init(&zmd->map_lock);

	atomic_set(&zmd->unmap_nr_cache, 0);
	INIT_LIST_HEAD(&zmd->unmap_cache_list);
	INIT_LIST_HEAD(&zmd->map_cache_list);

	atomic_set(&zmd->nr_reserved_seq_zones, 0);
	INIT_LIST_HEAD(&zmd->reserved_seq_zones_list);

	init_रुकोqueue_head(&zmd->मुक्त_wq);

	/* Initialize zone descriptors */
	ret = dmz_init_zones(zmd);
	अगर (ret)
		जाओ err;

	/* Get super block */
	ret = dmz_load_sb(zmd);
	अगर (ret)
		जाओ err;

	/* Set metadata zones starting from sb_zone */
	क्रम (i = 0; i < zmd->nr_meta_zones << 1; i++) अणु
		zone = dmz_get(zmd, zmd->sb[0].zone->id + i);
		अगर (!zone) अणु
			dmz_zmd_err(zmd,
				    "metadata zone %u not present", i);
			ret = -ENXIO;
			जाओ err;
		पूर्ण
		अगर (!dmz_is_rnd(zone) && !dmz_is_cache(zone)) अणु
			dmz_zmd_err(zmd,
				    "metadata zone %d is not random", i);
			ret = -ENXIO;
			जाओ err;
		पूर्ण
		set_bit(DMZ_META, &zone->flags);
	पूर्ण
	/* Load mapping table */
	ret = dmz_load_mapping(zmd);
	अगर (ret)
		जाओ err;

	/*
	 * Cache size boundaries: allow at least 2 super blocks, the chunk map
	 * blocks and enough blocks to be able to cache the biपंचांगap blocks of
	 * up to 16 zones when idle (min_nr_mblks). Otherwise, अगर busy, allow
	 * the cache to add 512 more metadata blocks.
	 */
	zmd->min_nr_mblks = 2 + zmd->nr_map_blocks + zmd->zone_nr_biपंचांगap_blocks * 16;
	zmd->max_nr_mblks = zmd->min_nr_mblks + 512;
	zmd->mblk_shrinker.count_objects = dmz_mblock_shrinker_count;
	zmd->mblk_shrinker.scan_objects = dmz_mblock_shrinker_scan;
	zmd->mblk_shrinker.seeks = DEFAULT_SEEKS;

	/* Metadata cache shrinker */
	ret = रेजिस्टर_shrinker(&zmd->mblk_shrinker);
	अगर (ret) अणु
		dmz_zmd_err(zmd, "Register metadata cache shrinker failed");
		जाओ err;
	पूर्ण

	dmz_zmd_info(zmd, "DM-Zoned metadata version %d", zmd->sb_version);
	क्रम (i = 0; i < zmd->nr_devs; i++)
		dmz_prपूर्णांक_dev(zmd, i);

	dmz_zmd_info(zmd, "  %u zones of %llu 512-byte logical sectors",
		     zmd->nr_zones, (u64)zmd->zone_nr_sectors);
	dmz_zmd_debug(zmd, "  %u metadata zones",
		      zmd->nr_meta_zones * 2);
	dmz_zmd_debug(zmd, "  %u data zones for %u chunks",
		      zmd->nr_data_zones, zmd->nr_chunks);
	dmz_zmd_debug(zmd, "    %u cache zones (%u unmapped)",
		      zmd->nr_cache, atomic_पढ़ो(&zmd->unmap_nr_cache));
	क्रम (i = 0; i < zmd->nr_devs; i++) अणु
		dmz_zmd_debug(zmd, "    %u random zones (%u unmapped)",
			      dmz_nr_rnd_zones(zmd, i),
			      dmz_nr_unmap_rnd_zones(zmd, i));
		dmz_zmd_debug(zmd, "    %u sequential zones (%u unmapped)",
			      dmz_nr_seq_zones(zmd, i),
			      dmz_nr_unmap_seq_zones(zmd, i));
	पूर्ण
	dmz_zmd_debug(zmd, "  %u reserved sequential data zones",
		      zmd->nr_reserved_seq);
	dmz_zmd_debug(zmd, "Format:");
	dmz_zmd_debug(zmd, "%u metadata blocks per set (%u max cache)",
		      zmd->nr_meta_blocks, zmd->max_nr_mblks);
	dmz_zmd_debug(zmd, "  %u data zone mapping blocks",
		      zmd->nr_map_blocks);
	dmz_zmd_debug(zmd, "  %u bitmap blocks",
		      zmd->nr_biपंचांगap_blocks);

	*metadata = zmd;

	वापस 0;
err:
	dmz_cleanup_metadata(zmd);
	kमुक्त(zmd);
	*metadata = शून्य;

	वापस ret;
पूर्ण

/*
 * Cleanup the zoned metadata resources.
 */
व्योम dmz_dtr_metadata(काष्ठा dmz_metadata *zmd)
अणु
	unरेजिस्टर_shrinker(&zmd->mblk_shrinker);
	dmz_cleanup_metadata(zmd);
	kमुक्त(zmd);
पूर्ण

/*
 * Check zone inक्रमmation on resume.
 */
पूर्णांक dmz_resume_metadata(काष्ठा dmz_metadata *zmd)
अणु
	काष्ठा dm_zone *zone;
	sector_t wp_block;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Check zones */
	क्रम (i = 0; i < zmd->nr_zones; i++) अणु
		zone = dmz_get(zmd, i);
		अगर (!zone) अणु
			dmz_zmd_err(zmd, "Unable to get zone %u", i);
			वापस -EIO;
		पूर्ण
		wp_block = zone->wp_block;

		ret = dmz_update_zone(zmd, zone);
		अगर (ret) अणु
			dmz_zmd_err(zmd, "Broken zone %u", i);
			वापस ret;
		पूर्ण

		अगर (dmz_is_offline(zone)) अणु
			dmz_zmd_warn(zmd, "Zone %u is offline", i);
			जारी;
		पूर्ण

		/* Check ग_लिखो poपूर्णांकer */
		अगर (!dmz_is_seq(zone))
			zone->wp_block = 0;
		अन्यथा अगर (zone->wp_block != wp_block) अणु
			dmz_zmd_err(zmd, "Zone %u: Invalid wp (%llu / %llu)",
				    i, (u64)zone->wp_block, (u64)wp_block);
			zone->wp_block = wp_block;
			dmz_invalidate_blocks(zmd, zone, zone->wp_block,
					      zmd->zone_nr_blocks - zone->wp_block);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
