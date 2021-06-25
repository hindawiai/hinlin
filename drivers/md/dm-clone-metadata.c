<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2019 Arrikto, Inc. All Rights Reserved.
 */

#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/bitops.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/device-mapper.h>

#समावेश "persistent-data/dm-bitset.h"
#समावेश "persistent-data/dm-space-map.h"
#समावेश "persistent-data/dm-block-manager.h"
#समावेश "persistent-data/dm-transaction-manager.h"

#समावेश "dm-clone-metadata.h"

#घोषणा DM_MSG_PREFIX "clone metadata"

#घोषणा SUPERBLOCK_LOCATION 0
#घोषणा SUPERBLOCK_MAGIC 0x8af27f64
#घोषणा SUPERBLOCK_CSUM_XOR 257649492

#घोषणा DM_CLONE_MAX_CONCURRENT_LOCKS 5

#घोषणा UUID_LEN 16

/* Min and max dm-clone metadata versions supported */
#घोषणा DM_CLONE_MIN_METADATA_VERSION 1
#घोषणा DM_CLONE_MAX_METADATA_VERSION 1

/*
 * On-disk metadata layout
 */
काष्ठा superblock_disk अणु
	__le32 csum;
	__le32 flags;
	__le64 blocknr;

	__u8 uuid[UUID_LEN];
	__le64 magic;
	__le32 version;

	__u8 metadata_space_map_root[SPACE_MAP_ROOT_SIZE];

	__le64 region_size;
	__le64 target_size;

	__le64 bitset_root;
पूर्ण __packed;

/*
 * Region and Dirty biपंचांगaps.
 *
 * dm-clone logically splits the source and destination devices in regions of
 * fixed size. The destination device's regions are gradually hydrated, i.e.,
 * we copy (clone) the source's regions to the destination device. Eventually,
 * all regions will get hydrated and all I/O will be served from the
 * destination device.
 *
 * We मुख्यtain an on-disk biपंचांगap which tracks the state of each of the
 * destination device's regions, i.e., whether they are hydrated or not.
 *
 * To save स्थिरantly करोing look ups on disk we keep an in core copy of the
 * on-disk biपंचांगap, the region_map.
 *
 * In order to track which regions are hydrated during a metadata transaction,
 * we use a second set of biपंचांगaps, the dmap (dirty biपंचांगap), which includes two
 * biपंचांगaps, namely dirty_regions and dirty_words. The dirty_regions biपंचांगap
 * tracks the regions that got hydrated during the current metadata
 * transaction. The dirty_words biपंचांगap tracks the dirty words, i.e. दीर्घs, of
 * the dirty_regions biपंचांगap.
 *
 * This allows us to precisely track the regions that were hydrated during the
 * current metadata transaction and update the metadata accordingly, when we
 * commit the current transaction. This is important because dm-clone should
 * only commit the metadata of regions that were properly flushed to the
 * destination device beक्रमehand. Otherwise, in हाल of a crash, we could end
 * up with a corrupted dm-clone device.
 *
 * When a region finishes hydrating dm-clone calls
 * dm_clone_set_region_hydrated(), or क्रम discard requests
 * dm_clone_cond_set_range(), which sets the corresponding bits in region_map
 * and dmap.
 *
 * During a metadata commit we scan dmap->dirty_words and dmap->dirty_regions
 * and update the on-disk metadata accordingly. Thus, we करोn't have to flush to
 * disk the whole region_map. We can just flush the dirty region_map bits.
 *
 * We use the helper dmap->dirty_words biपंचांगap, which is smaller than the
 * original region_map, to reduce the amount of memory accesses during a
 * metadata commit. Moreover, as dm-bitset also accesses the on-disk biपंचांगap in
 * 64-bit word granularity, the dirty_words biपंचांगap helps us aव्योम useless disk
 * accesses.
 *
 * We could update directly the on-disk biपंचांगap, when dm-clone calls either
 * dm_clone_set_region_hydrated() or dm_clone_cond_set_range(), buts this
 * inserts signअगरicant metadata I/O overhead in dm-clone's I/O path. Also, as
 * these two functions करोn't block, we can call them in पूर्णांकerrupt context,
 * e.g., in a hooked overग_लिखो bio's completion routine, and further reduce the
 * I/O completion latency.
 *
 * We मुख्यtain two dirty biपंचांगap sets. During a metadata commit we atomically
 * swap the currently used dmap with the unused one. This allows the metadata
 * update functions to run concurrently with an ongoing commit.
 */
काष्ठा dirty_map अणु
	अचिन्हित दीर्घ *dirty_words;
	अचिन्हित दीर्घ *dirty_regions;
	अचिन्हित पूर्णांक changed;
पूर्ण;

काष्ठा dm_clone_metadata अणु
	/* The metadata block device */
	काष्ठा block_device *bdev;

	sector_t target_size;
	sector_t region_size;
	अचिन्हित दीर्घ nr_regions;
	अचिन्हित दीर्घ nr_words;

	/* Spinlock protecting the region and dirty biपंचांगaps. */
	spinlock_t biपंचांगap_lock;
	काष्ठा dirty_map dmap[2];
	काष्ठा dirty_map *current_dmap;

	/* Protected by lock */
	काष्ठा dirty_map *committing_dmap;

	/*
	 * In core copy of the on-disk biपंचांगap to save स्थिरantly करोing look ups
	 * on disk.
	 */
	अचिन्हित दीर्घ *region_map;

	/* Protected by biपंचांगap_lock */
	अचिन्हित पूर्णांक पढ़ो_only;

	काष्ठा dm_block_manager *bm;
	काष्ठा dm_space_map *sm;
	काष्ठा dm_transaction_manager *पंचांग;

	काष्ठा rw_semaphore lock;

	काष्ठा dm_disk_bitset bitset_info;
	dm_block_t bitset_root;

	/*
	 * Reading the space map root can fail, so we पढ़ो it पूर्णांकo this
	 * buffer beक्रमe the superblock is locked and updated.
	 */
	__u8 metadata_space_map_root[SPACE_MAP_ROOT_SIZE];

	bool hydration_करोne:1;
	bool fail_io:1;
पूर्ण;

/*---------------------------------------------------------------------------*/

/*
 * Superblock validation.
 */
अटल व्योम sb_prepare_क्रम_ग_लिखो(काष्ठा dm_block_validator *v,
				 काष्ठा dm_block *b, माप_प्रकार sb_block_size)
अणु
	काष्ठा superblock_disk *sb;
	u32 csum;

	sb = dm_block_data(b);
	sb->blocknr = cpu_to_le64(dm_block_location(b));

	csum = dm_bm_checksum(&sb->flags, sb_block_size - माप(__le32),
			      SUPERBLOCK_CSUM_XOR);
	sb->csum = cpu_to_le32(csum);
पूर्ण

अटल पूर्णांक sb_check(काष्ठा dm_block_validator *v, काष्ठा dm_block *b,
		    माप_प्रकार sb_block_size)
अणु
	काष्ठा superblock_disk *sb;
	u32 csum, metadata_version;

	sb = dm_block_data(b);

	अगर (dm_block_location(b) != le64_to_cpu(sb->blocknr)) अणु
		DMERR("Superblock check failed: blocknr %llu, expected %llu",
		      le64_to_cpu(sb->blocknr),
		      (अचिन्हित दीर्घ दीर्घ)dm_block_location(b));
		वापस -ENOTBLK;
	पूर्ण

	अगर (le64_to_cpu(sb->magic) != SUPERBLOCK_MAGIC) अणु
		DMERR("Superblock check failed: magic %llu, expected %llu",
		      le64_to_cpu(sb->magic),
		      (अचिन्हित दीर्घ दीर्घ)SUPERBLOCK_MAGIC);
		वापस -EILSEQ;
	पूर्ण

	csum = dm_bm_checksum(&sb->flags, sb_block_size - माप(__le32),
			      SUPERBLOCK_CSUM_XOR);
	अगर (sb->csum != cpu_to_le32(csum)) अणु
		DMERR("Superblock check failed: checksum %u, expected %u",
		      csum, le32_to_cpu(sb->csum));
		वापस -EILSEQ;
	पूर्ण

	/* Check metadata version */
	metadata_version = le32_to_cpu(sb->version);
	अगर (metadata_version < DM_CLONE_MIN_METADATA_VERSION ||
	    metadata_version > DM_CLONE_MAX_METADATA_VERSION) अणु
		DMERR("Clone metadata version %u found, but only versions between %u and %u supported.",
		      metadata_version, DM_CLONE_MIN_METADATA_VERSION,
		      DM_CLONE_MAX_METADATA_VERSION);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dm_block_validator sb_validator = अणु
	.name = "superblock",
	.prepare_क्रम_ग_लिखो = sb_prepare_क्रम_ग_लिखो,
	.check = sb_check
पूर्ण;

/*
 * Check अगर the superblock is क्रमmatted or not. We consider the superblock to
 * be क्रमmatted in हाल we find non-zero bytes in it.
 */
अटल पूर्णांक __superblock_all_zeroes(काष्ठा dm_block_manager *bm, bool *क्रमmatted)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक i, nr_words;
	काष्ठा dm_block *sblock;
	__le64 *data_le, zero = cpu_to_le64(0);

	/*
	 * We करोn't use a validator here because the superblock could be all
	 * zeroes.
	 */
	r = dm_bm_पढ़ो_lock(bm, SUPERBLOCK_LOCATION, शून्य, &sblock);
	अगर (r) अणु
		DMERR("Failed to read_lock superblock");
		वापस r;
	पूर्ण

	data_le = dm_block_data(sblock);
	*क्रमmatted = false;

	/* This assumes that the block size is a multiple of 8 bytes */
	BUG_ON(dm_bm_block_size(bm) % माप(__le64));
	nr_words = dm_bm_block_size(bm) / माप(__le64);
	क्रम (i = 0; i < nr_words; i++) अणु
		अगर (data_le[i] != zero) अणु
			*क्रमmatted = true;
			अवरोध;
		पूर्ण
	पूर्ण

	dm_bm_unlock(sblock);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------*/

/*
 * Low-level metadata handling.
 */
अटल अंतरभूत पूर्णांक superblock_पढ़ो_lock(काष्ठा dm_clone_metadata *cmd,
				       काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_पढ़ो_lock(cmd->bm, SUPERBLOCK_LOCATION, &sb_validator, sblock);
पूर्ण

अटल अंतरभूत पूर्णांक superblock_ग_लिखो_lock_zero(काष्ठा dm_clone_metadata *cmd,
					     काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_ग_लिखो_lock_zero(cmd->bm, SUPERBLOCK_LOCATION, &sb_validator, sblock);
पूर्ण

अटल पूर्णांक __copy_sm_root(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r;
	माप_प्रकार root_size;

	r = dm_sm_root_size(cmd->sm, &root_size);
	अगर (r)
		वापस r;

	वापस dm_sm_copy_root(cmd->sm, &cmd->metadata_space_map_root, root_size);
पूर्ण

/* Save dm-clone metadata in superblock */
अटल व्योम __prepare_superblock(काष्ठा dm_clone_metadata *cmd,
				 काष्ठा superblock_disk *sb)
अणु
	sb->flags = cpu_to_le32(0UL);

	/* FIXME: UUID is currently unused */
	स_रखो(sb->uuid, 0, माप(sb->uuid));

	sb->magic = cpu_to_le64(SUPERBLOCK_MAGIC);
	sb->version = cpu_to_le32(DM_CLONE_MAX_METADATA_VERSION);

	/* Save the metadata space_map root */
	स_नकल(&sb->metadata_space_map_root, &cmd->metadata_space_map_root,
	       माप(cmd->metadata_space_map_root));

	sb->region_size = cpu_to_le64(cmd->region_size);
	sb->target_size = cpu_to_le64(cmd->target_size);
	sb->bitset_root = cpu_to_le64(cmd->bitset_root);
पूर्ण

अटल पूर्णांक __खोलो_metadata(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा superblock_disk *sb;

	r = superblock_पढ़ो_lock(cmd, &sblock);

	अगर (r) अणु
		DMERR("Failed to read_lock superblock");
		वापस r;
	पूर्ण

	sb = dm_block_data(sblock);

	/* Verअगरy that target_size and region_size haven't changed. */
	अगर (cmd->region_size != le64_to_cpu(sb->region_size) ||
	    cmd->target_size != le64_to_cpu(sb->target_size)) अणु
		DMERR("Region and/or target size don't match the ones in metadata");
		r = -EINVAL;
		जाओ out_with_lock;
	पूर्ण

	r = dm_पंचांग_खोलो_with_sm(cmd->bm, SUPERBLOCK_LOCATION,
			       sb->metadata_space_map_root,
			       माप(sb->metadata_space_map_root),
			       &cmd->पंचांग, &cmd->sm);

	अगर (r) अणु
		DMERR("dm_tm_open_with_sm failed");
		जाओ out_with_lock;
	पूर्ण

	dm_disk_bitset_init(cmd->पंचांग, &cmd->bitset_info);
	cmd->bitset_root = le64_to_cpu(sb->bitset_root);

out_with_lock:
	dm_bm_unlock(sblock);

	वापस r;
पूर्ण

अटल पूर्णांक __क्रमmat_metadata(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा superblock_disk *sb;

	r = dm_पंचांग_create_with_sm(cmd->bm, SUPERBLOCK_LOCATION, &cmd->पंचांग, &cmd->sm);
	अगर (r) अणु
		DMERR("Failed to create transaction manager");
		वापस r;
	पूर्ण

	dm_disk_bitset_init(cmd->पंचांग, &cmd->bitset_info);

	r = dm_bitset_empty(&cmd->bitset_info, &cmd->bitset_root);
	अगर (r) अणु
		DMERR("Failed to create empty on-disk bitset");
		जाओ err_with_पंचांग;
	पूर्ण

	r = dm_bitset_resize(&cmd->bitset_info, cmd->bitset_root, 0,
			     cmd->nr_regions, false, &cmd->bitset_root);
	अगर (r) अणु
		DMERR("Failed to resize on-disk bitset to %lu entries", cmd->nr_regions);
		जाओ err_with_पंचांग;
	पूर्ण

	/* Flush to disk all blocks, except the superblock */
	r = dm_पंचांग_pre_commit(cmd->पंचांग);
	अगर (r) अणु
		DMERR("dm_tm_pre_commit failed");
		जाओ err_with_पंचांग;
	पूर्ण

	r = __copy_sm_root(cmd);
	अगर (r) अणु
		DMERR("__copy_sm_root failed");
		जाओ err_with_पंचांग;
	पूर्ण

	r = superblock_ग_लिखो_lock_zero(cmd, &sblock);
	अगर (r) अणु
		DMERR("Failed to write_lock superblock");
		जाओ err_with_पंचांग;
	पूर्ण

	sb = dm_block_data(sblock);
	__prepare_superblock(cmd, sb);
	r = dm_पंचांग_commit(cmd->पंचांग, sblock);
	अगर (r) अणु
		DMERR("Failed to commit superblock");
		जाओ err_with_पंचांग;
	पूर्ण

	वापस 0;

err_with_पंचांग:
	dm_sm_destroy(cmd->sm);
	dm_पंचांग_destroy(cmd->पंचांग);

	वापस r;
पूर्ण

अटल पूर्णांक __खोलो_or_क्रमmat_metadata(काष्ठा dm_clone_metadata *cmd, bool may_क्रमmat_device)
अणु
	पूर्णांक r;
	bool क्रमmatted = false;

	r = __superblock_all_zeroes(cmd->bm, &क्रमmatted);
	अगर (r)
		वापस r;

	अगर (!क्रमmatted)
		वापस may_क्रमmat_device ? __क्रमmat_metadata(cmd) : -EPERM;

	वापस __खोलो_metadata(cmd);
पूर्ण

अटल पूर्णांक __create_persistent_data_काष्ठाures(काष्ठा dm_clone_metadata *cmd,
					       bool may_क्रमmat_device)
अणु
	पूर्णांक r;

	/* Create block manager */
	cmd->bm = dm_block_manager_create(cmd->bdev,
					 DM_CLONE_METADATA_BLOCK_SIZE << SECTOR_SHIFT,
					 DM_CLONE_MAX_CONCURRENT_LOCKS);
	अगर (IS_ERR(cmd->bm)) अणु
		DMERR("Failed to create block manager");
		वापस PTR_ERR(cmd->bm);
	पूर्ण

	r = __खोलो_or_क्रमmat_metadata(cmd, may_क्रमmat_device);
	अगर (r)
		dm_block_manager_destroy(cmd->bm);

	वापस r;
पूर्ण

अटल व्योम __destroy_persistent_data_काष्ठाures(काष्ठा dm_clone_metadata *cmd)
अणु
	dm_sm_destroy(cmd->sm);
	dm_पंचांग_destroy(cmd->पंचांग);
	dm_block_manager_destroy(cmd->bm);
पूर्ण

/*---------------------------------------------------------------------------*/

अटल माप_प्रकार biपंचांगap_size(अचिन्हित दीर्घ nr_bits)
अणु
	वापस BITS_TO_LONGS(nr_bits) * माप(दीर्घ);
पूर्ण

अटल पूर्णांक __dirty_map_init(काष्ठा dirty_map *dmap, अचिन्हित दीर्घ nr_words,
			    अचिन्हित दीर्घ nr_regions)
अणु
	dmap->changed = 0;

	dmap->dirty_words = kvzalloc(biपंचांगap_size(nr_words), GFP_KERNEL);
	अगर (!dmap->dirty_words)
		वापस -ENOMEM;

	dmap->dirty_regions = kvzalloc(biपंचांगap_size(nr_regions), GFP_KERNEL);
	अगर (!dmap->dirty_regions) अणु
		kvमुक्त(dmap->dirty_words);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __dirty_map_निकास(काष्ठा dirty_map *dmap)
अणु
	kvमुक्त(dmap->dirty_words);
	kvमुक्त(dmap->dirty_regions);
पूर्ण

अटल पूर्णांक dirty_map_init(काष्ठा dm_clone_metadata *cmd)
अणु
	अगर (__dirty_map_init(&cmd->dmap[0], cmd->nr_words, cmd->nr_regions)) अणु
		DMERR("Failed to allocate dirty bitmap");
		वापस -ENOMEM;
	पूर्ण

	अगर (__dirty_map_init(&cmd->dmap[1], cmd->nr_words, cmd->nr_regions)) अणु
		DMERR("Failed to allocate dirty bitmap");
		__dirty_map_निकास(&cmd->dmap[0]);
		वापस -ENOMEM;
	पूर्ण

	cmd->current_dmap = &cmd->dmap[0];
	cmd->committing_dmap = शून्य;

	वापस 0;
पूर्ण

अटल व्योम dirty_map_निकास(काष्ठा dm_clone_metadata *cmd)
अणु
	__dirty_map_निकास(&cmd->dmap[0]);
	__dirty_map_निकास(&cmd->dmap[1]);
पूर्ण

अटल पूर्णांक __load_bitset_in_core(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ i;
	काष्ठा dm_bitset_cursor c;

	/* Flush bitset cache */
	r = dm_bitset_flush(&cmd->bitset_info, cmd->bitset_root, &cmd->bitset_root);
	अगर (r)
		वापस r;

	r = dm_bitset_cursor_begin(&cmd->bitset_info, cmd->bitset_root, cmd->nr_regions, &c);
	अगर (r)
		वापस r;

	क्रम (i = 0; ; i++) अणु
		अगर (dm_bitset_cursor_get_value(&c))
			__set_bit(i, cmd->region_map);
		अन्यथा
			__clear_bit(i, cmd->region_map);

		अगर (i >= (cmd->nr_regions - 1))
			अवरोध;

		r = dm_bitset_cursor_next(&c);

		अगर (r)
			अवरोध;
	पूर्ण

	dm_bitset_cursor_end(&c);

	वापस r;
पूर्ण

काष्ठा dm_clone_metadata *dm_clone_metadata_खोलो(काष्ठा block_device *bdev,
						 sector_t target_size,
						 sector_t region_size)
अणु
	पूर्णांक r;
	काष्ठा dm_clone_metadata *cmd;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		DMERR("Failed to allocate memory for dm-clone metadata");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	cmd->bdev = bdev;
	cmd->target_size = target_size;
	cmd->region_size = region_size;
	cmd->nr_regions = dm_sector_भाग_up(cmd->target_size, cmd->region_size);
	cmd->nr_words = BITS_TO_LONGS(cmd->nr_regions);

	init_rwsem(&cmd->lock);
	spin_lock_init(&cmd->biपंचांगap_lock);
	cmd->पढ़ो_only = 0;
	cmd->fail_io = false;
	cmd->hydration_करोne = false;

	cmd->region_map = kvदो_स्मृति(biपंचांगap_size(cmd->nr_regions), GFP_KERNEL);
	अगर (!cmd->region_map) अणु
		DMERR("Failed to allocate memory for region bitmap");
		r = -ENOMEM;
		जाओ out_with_md;
	पूर्ण

	r = __create_persistent_data_काष्ठाures(cmd, true);
	अगर (r)
		जाओ out_with_region_map;

	r = __load_bitset_in_core(cmd);
	अगर (r) अणु
		DMERR("Failed to load on-disk region map");
		जाओ out_with_pds;
	पूर्ण

	r = dirty_map_init(cmd);
	अगर (r)
		जाओ out_with_pds;

	अगर (biपंचांगap_full(cmd->region_map, cmd->nr_regions))
		cmd->hydration_करोne = true;

	वापस cmd;

out_with_pds:
	__destroy_persistent_data_काष्ठाures(cmd);

out_with_region_map:
	kvमुक्त(cmd->region_map);

out_with_md:
	kमुक्त(cmd);

	वापस ERR_PTR(r);
पूर्ण

व्योम dm_clone_metadata_बंद(काष्ठा dm_clone_metadata *cmd)
अणु
	अगर (!cmd->fail_io)
		__destroy_persistent_data_काष्ठाures(cmd);

	dirty_map_निकास(cmd);
	kvमुक्त(cmd->region_map);
	kमुक्त(cmd);
पूर्ण

bool dm_clone_is_hydration_करोne(काष्ठा dm_clone_metadata *cmd)
अणु
	वापस cmd->hydration_करोne;
पूर्ण

bool dm_clone_is_region_hydrated(काष्ठा dm_clone_metadata *cmd, अचिन्हित दीर्घ region_nr)
अणु
	वापस dm_clone_is_hydration_करोne(cmd) || test_bit(region_nr, cmd->region_map);
पूर्ण

bool dm_clone_is_range_hydrated(काष्ठा dm_clone_metadata *cmd,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr_regions)
अणु
	अचिन्हित दीर्घ bit;

	अगर (dm_clone_is_hydration_करोne(cmd))
		वापस true;

	bit = find_next_zero_bit(cmd->region_map, cmd->nr_regions, start);

	वापस (bit >= (start + nr_regions));
पूर्ण

अचिन्हित पूर्णांक dm_clone_nr_of_hydrated_regions(काष्ठा dm_clone_metadata *cmd)
अणु
	वापस biपंचांगap_weight(cmd->region_map, cmd->nr_regions);
पूर्ण

अचिन्हित दीर्घ dm_clone_find_next_unhydrated_region(काष्ठा dm_clone_metadata *cmd,
						   अचिन्हित दीर्घ start)
अणु
	वापस find_next_zero_bit(cmd->region_map, cmd->nr_regions, start);
पूर्ण

अटल पूर्णांक __update_metadata_word(काष्ठा dm_clone_metadata *cmd,
				  अचिन्हित दीर्घ *dirty_regions,
				  अचिन्हित दीर्घ word)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ index = word * BITS_PER_LONG;
	अचिन्हित दीर्घ max_index = min(cmd->nr_regions, (word + 1) * BITS_PER_LONG);

	जबतक (index < max_index) अणु
		अगर (test_bit(index, dirty_regions)) अणु
			r = dm_bitset_set_bit(&cmd->bitset_info, cmd->bitset_root,
					      index, &cmd->bitset_root);
			अगर (r) अणु
				DMERR("dm_bitset_set_bit failed");
				वापस r;
			पूर्ण
			__clear_bit(index, dirty_regions);
		पूर्ण
		index++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __metadata_commit(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा superblock_disk *sb;

	/* Flush bitset cache */
	r = dm_bitset_flush(&cmd->bitset_info, cmd->bitset_root, &cmd->bitset_root);
	अगर (r) अणु
		DMERR("dm_bitset_flush failed");
		वापस r;
	पूर्ण

	/* Flush to disk all blocks, except the superblock */
	r = dm_पंचांग_pre_commit(cmd->पंचांग);
	अगर (r) अणु
		DMERR("dm_tm_pre_commit failed");
		वापस r;
	पूर्ण

	/* Save the space map root in cmd->metadata_space_map_root */
	r = __copy_sm_root(cmd);
	अगर (r) अणु
		DMERR("__copy_sm_root failed");
		वापस r;
	पूर्ण

	/* Lock the superblock */
	r = superblock_ग_लिखो_lock_zero(cmd, &sblock);
	अगर (r) अणु
		DMERR("Failed to write_lock superblock");
		वापस r;
	पूर्ण

	/* Save the metadata in superblock */
	sb = dm_block_data(sblock);
	__prepare_superblock(cmd, sb);

	/* Unlock superblock and commit it to disk */
	r = dm_पंचांग_commit(cmd->पंचांग, sblock);
	अगर (r) अणु
		DMERR("Failed to commit superblock");
		वापस r;
	पूर्ण

	/*
	 * FIXME: Find a more efficient way to check अगर the hydration is करोne.
	 */
	अगर (biपंचांगap_full(cmd->region_map, cmd->nr_regions))
		cmd->hydration_करोne = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __flush_dmap(काष्ठा dm_clone_metadata *cmd, काष्ठा dirty_map *dmap)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ word;

	word = 0;
	करो अणु
		word = find_next_bit(dmap->dirty_words, cmd->nr_words, word);

		अगर (word == cmd->nr_words)
			अवरोध;

		r = __update_metadata_word(cmd, dmap->dirty_regions, word);

		अगर (r)
			वापस r;

		__clear_bit(word, dmap->dirty_words);
		word++;
	पूर्ण जबतक (word < cmd->nr_words);

	r = __metadata_commit(cmd);

	अगर (r)
		वापस r;

	/* Update the changed flag */
	spin_lock_irq(&cmd->biपंचांगap_lock);
	dmap->changed = 0;
	spin_unlock_irq(&cmd->biपंचांगap_lock);

	वापस 0;
पूर्ण

पूर्णांक dm_clone_metadata_pre_commit(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r = 0;
	काष्ठा dirty_map *dmap, *next_dmap;

	करोwn_ग_लिखो(&cmd->lock);

	अगर (cmd->fail_io || dm_bm_is_पढ़ो_only(cmd->bm)) अणु
		r = -EPERM;
		जाओ out;
	पूर्ण

	/* Get current dirty biपंचांगap */
	dmap = cmd->current_dmap;

	/* Get next dirty biपंचांगap */
	next_dmap = (dmap == &cmd->dmap[0]) ? &cmd->dmap[1] : &cmd->dmap[0];

	/*
	 * The last commit failed, so we करोn't have a clean dirty-biपंचांगap to
	 * use.
	 */
	अगर (WARN_ON(next_dmap->changed || cmd->committing_dmap)) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	/* Swap dirty biपंचांगaps */
	spin_lock_irq(&cmd->biपंचांगap_lock);
	cmd->current_dmap = next_dmap;
	spin_unlock_irq(&cmd->biपंचांगap_lock);

	/* Set old dirty biपंचांगap as currently committing */
	cmd->committing_dmap = dmap;
out:
	up_ग_लिखो(&cmd->lock);

	वापस r;
पूर्ण

पूर्णांक dm_clone_metadata_commit(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r = -EPERM;

	करोwn_ग_लिखो(&cmd->lock);

	अगर (cmd->fail_io || dm_bm_is_पढ़ो_only(cmd->bm))
		जाओ out;

	अगर (WARN_ON(!cmd->committing_dmap)) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	r = __flush_dmap(cmd, cmd->committing_dmap);
	अगर (!r) अणु
		/* Clear committing dmap */
		cmd->committing_dmap = शून्य;
	पूर्ण
out:
	up_ग_लिखो(&cmd->lock);

	वापस r;
पूर्ण

पूर्णांक dm_clone_set_region_hydrated(काष्ठा dm_clone_metadata *cmd, अचिन्हित दीर्घ region_nr)
अणु
	पूर्णांक r = 0;
	काष्ठा dirty_map *dmap;
	अचिन्हित दीर्घ word, flags;

	अगर (unlikely(region_nr >= cmd->nr_regions)) अणु
		DMERR("Region %lu out of range (total number of regions %lu)",
		      region_nr, cmd->nr_regions);
		वापस -दुस्फल;
	पूर्ण

	word = region_nr / BITS_PER_LONG;

	spin_lock_irqsave(&cmd->biपंचांगap_lock, flags);

	अगर (cmd->पढ़ो_only) अणु
		r = -EPERM;
		जाओ out;
	पूर्ण

	dmap = cmd->current_dmap;

	__set_bit(word, dmap->dirty_words);
	__set_bit(region_nr, dmap->dirty_regions);
	__set_bit(region_nr, cmd->region_map);
	dmap->changed = 1;

out:
	spin_unlock_irqrestore(&cmd->biपंचांगap_lock, flags);

	वापस r;
पूर्ण

पूर्णांक dm_clone_cond_set_range(काष्ठा dm_clone_metadata *cmd, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ nr_regions)
अणु
	पूर्णांक r = 0;
	काष्ठा dirty_map *dmap;
	अचिन्हित दीर्घ word, region_nr;

	अगर (unlikely(start >= cmd->nr_regions || (start + nr_regions) < start ||
		     (start + nr_regions) > cmd->nr_regions)) अणु
		DMERR("Invalid region range: start %lu, nr_regions %lu (total number of regions %lu)",
		      start, nr_regions, cmd->nr_regions);
		वापस -दुस्फल;
	पूर्ण

	spin_lock_irq(&cmd->biपंचांगap_lock);

	अगर (cmd->पढ़ो_only) अणु
		r = -EPERM;
		जाओ out;
	पूर्ण

	dmap = cmd->current_dmap;
	क्रम (region_nr = start; region_nr < (start + nr_regions); region_nr++) अणु
		अगर (!test_bit(region_nr, cmd->region_map)) अणु
			word = region_nr / BITS_PER_LONG;
			__set_bit(word, dmap->dirty_words);
			__set_bit(region_nr, dmap->dirty_regions);
			__set_bit(region_nr, cmd->region_map);
			dmap->changed = 1;
		पूर्ण
	पूर्ण
out:
	spin_unlock_irq(&cmd->biपंचांगap_lock);

	वापस r;
पूर्ण

/*
 * WARNING: This must not be called concurrently with either
 * dm_clone_set_region_hydrated() or dm_clone_cond_set_range(), as it changes
 * cmd->region_map without taking the cmd->biपंचांगap_lock spinlock. The only
 * exception is after setting the metadata to पढ़ो-only mode, using
 * dm_clone_metadata_set_पढ़ो_only().
 *
 * We करोn't take the spinlock because __load_bitset_in_core() करोes I/O, so it
 * may block.
 */
पूर्णांक dm_clone_reload_in_core_bitset(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_ग_लिखो(&cmd->lock);

	अगर (cmd->fail_io)
		जाओ out;

	r = __load_bitset_in_core(cmd);
out:
	up_ग_लिखो(&cmd->lock);

	वापस r;
पूर्ण

bool dm_clone_changed_this_transaction(काष्ठा dm_clone_metadata *cmd)
अणु
	bool r;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cmd->biपंचांगap_lock, flags);
	r = cmd->dmap[0].changed || cmd->dmap[1].changed;
	spin_unlock_irqrestore(&cmd->biपंचांगap_lock, flags);

	वापस r;
पूर्ण

पूर्णांक dm_clone_metadata_पात(काष्ठा dm_clone_metadata *cmd)
अणु
	पूर्णांक r = -EPERM;

	करोwn_ग_लिखो(&cmd->lock);

	अगर (cmd->fail_io || dm_bm_is_पढ़ो_only(cmd->bm))
		जाओ out;

	__destroy_persistent_data_काष्ठाures(cmd);

	r = __create_persistent_data_काष्ठाures(cmd, false);
	अगर (r) अणु
		/* If something went wrong we can neither ग_लिखो nor पढ़ो the metadata */
		cmd->fail_io = true;
	पूर्ण
out:
	up_ग_लिखो(&cmd->lock);

	वापस r;
पूर्ण

व्योम dm_clone_metadata_set_पढ़ो_only(काष्ठा dm_clone_metadata *cmd)
अणु
	करोwn_ग_लिखो(&cmd->lock);

	spin_lock_irq(&cmd->biपंचांगap_lock);
	cmd->पढ़ो_only = 1;
	spin_unlock_irq(&cmd->biपंचांगap_lock);

	अगर (!cmd->fail_io)
		dm_bm_set_पढ़ो_only(cmd->bm);

	up_ग_लिखो(&cmd->lock);
पूर्ण

व्योम dm_clone_metadata_set_पढ़ो_ग_लिखो(काष्ठा dm_clone_metadata *cmd)
अणु
	करोwn_ग_लिखो(&cmd->lock);

	spin_lock_irq(&cmd->biपंचांगap_lock);
	cmd->पढ़ो_only = 0;
	spin_unlock_irq(&cmd->biपंचांगap_lock);

	अगर (!cmd->fail_io)
		dm_bm_set_पढ़ो_ग_लिखो(cmd->bm);

	up_ग_लिखो(&cmd->lock);
पूर्ण

पूर्णांक dm_clone_get_मुक्त_metadata_block_count(काष्ठा dm_clone_metadata *cmd,
					   dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_पढ़ो(&cmd->lock);

	अगर (!cmd->fail_io)
		r = dm_sm_get_nr_मुक्त(cmd->sm, result);

	up_पढ़ो(&cmd->lock);

	वापस r;
पूर्ण

पूर्णांक dm_clone_get_metadata_dev_size(काष्ठा dm_clone_metadata *cmd,
				   dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_पढ़ो(&cmd->lock);

	अगर (!cmd->fail_io)
		r = dm_sm_get_nr_blocks(cmd->sm, result);

	up_पढ़ो(&cmd->lock);

	वापस r;
पूर्ण
