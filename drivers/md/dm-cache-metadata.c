<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-cache-metadata.h"

#समावेश "persistent-data/dm-array.h"
#समावेश "persistent-data/dm-bitset.h"
#समावेश "persistent-data/dm-space-map.h"
#समावेश "persistent-data/dm-space-map-disk.h"
#समावेश "persistent-data/dm-transaction-manager.h"

#समावेश <linux/device-mapper.h>
#समावेश <linux/refcount.h>

/*----------------------------------------------------------------*/

#घोषणा DM_MSG_PREFIX   "cache metadata"

#घोषणा CACHE_SUPERBLOCK_MAGIC 06142003
#घोषणा CACHE_SUPERBLOCK_LOCATION 0

/*
 * defines a range of metadata versions that this module can handle.
 */
#घोषणा MIN_CACHE_VERSION 1
#घोषणा MAX_CACHE_VERSION 2

/*
 *  3 क्रम btree insert +
 *  2 क्रम btree lookup used within space map
 */
#घोषणा CACHE_MAX_CONCURRENT_LOCKS 5
#घोषणा SPACE_MAP_ROOT_SIZE 128

क्रमागत superblock_flag_bits अणु
	/* क्रम spotting crashes that would invalidate the dirty bitset */
	CLEAN_SHUTDOWN,
	/* metadata must be checked using the tools */
	NEEDS_CHECK,
पूर्ण;

/*
 * Each mapping from cache block -> origin block carries a set of flags.
 */
क्रमागत mapping_bits अणु
	/*
	 * A valid mapping.  Because we're using an array we clear this
	 * flag क्रम an non existant mapping.
	 */
	M_VALID = 1,

	/*
	 * The data on the cache is dअगरferent from that on the origin.
	 * This flag is only used by metadata क्रमmat 1.
	 */
	M_सूचीTY = 2
पूर्ण;

काष्ठा cache_disk_superblock अणु
	__le32 csum;
	__le32 flags;
	__le64 blocknr;

	__u8 uuid[16];
	__le64 magic;
	__le32 version;

	__u8 policy_name[CACHE_POLICY_NAME_SIZE];
	__le32 policy_hपूर्णांक_size;

	__u8 metadata_space_map_root[SPACE_MAP_ROOT_SIZE];
	__le64 mapping_root;
	__le64 hपूर्णांक_root;

	__le64 discard_root;
	__le64 discard_block_size;
	__le64 discard_nr_blocks;

	__le32 data_block_size;
	__le32 metadata_block_size;
	__le32 cache_blocks;

	__le32 compat_flags;
	__le32 compat_ro_flags;
	__le32 incompat_flags;

	__le32 पढ़ो_hits;
	__le32 पढ़ो_misses;
	__le32 ग_लिखो_hits;
	__le32 ग_लिखो_misses;

	__le32 policy_version[CACHE_POLICY_VERSION_SIZE];

	/*
	 * Metadata क्रमmat 2 fields.
	 */
	__le64 dirty_root;
पूर्ण __packed;

काष्ठा dm_cache_metadata अणु
	refcount_t ref_count;
	काष्ठा list_head list;

	अचिन्हित version;
	काष्ठा block_device *bdev;
	काष्ठा dm_block_manager *bm;
	काष्ठा dm_space_map *metadata_sm;
	काष्ठा dm_transaction_manager *पंचांग;

	काष्ठा dm_array_info info;
	काष्ठा dm_array_info hपूर्णांक_info;
	काष्ठा dm_disk_bitset discard_info;

	काष्ठा rw_semaphore root_lock;
	अचिन्हित दीर्घ flags;
	dm_block_t root;
	dm_block_t hपूर्णांक_root;
	dm_block_t discard_root;

	sector_t discard_block_size;
	dm_dblock_t discard_nr_blocks;

	sector_t data_block_size;
	dm_cblock_t cache_blocks;
	bool changed:1;
	bool clean_when_खोलोed:1;

	अक्षर policy_name[CACHE_POLICY_NAME_SIZE];
	अचिन्हित policy_version[CACHE_POLICY_VERSION_SIZE];
	माप_प्रकार policy_hपूर्णांक_size;
	काष्ठा dm_cache_statistics stats;

	/*
	 * Reading the space map root can fail, so we पढ़ो it पूर्णांकo this
	 * buffer beक्रमe the superblock is locked and updated.
	 */
	__u8 metadata_space_map_root[SPACE_MAP_ROOT_SIZE];

	/*
	 * Set अगर a transaction has to be पातed but the attempt to roll
	 * back to the previous (good) transaction failed.  The only
	 * metadata operation permissible in this state is the closing of
	 * the device.
	 */
	bool fail_io:1;

	/*
	 * Metadata क्रमmat 2 fields.
	 */
	dm_block_t dirty_root;
	काष्ठा dm_disk_bitset dirty_info;

	/*
	 * These काष्ठाures are used when loading metadata.  They're too
	 * big to put on the stack.
	 */
	काष्ठा dm_array_cursor mapping_cursor;
	काष्ठा dm_array_cursor hपूर्णांक_cursor;
	काष्ठा dm_bitset_cursor dirty_cursor;
पूर्ण;

/*-------------------------------------------------------------------
 * superblock validator
 *-----------------------------------------------------------------*/

#घोषणा SUPERBLOCK_CSUM_XOR 9031977

अटल व्योम sb_prepare_क्रम_ग_लिखो(काष्ठा dm_block_validator *v,
				 काष्ठा dm_block *b,
				 माप_प्रकार sb_block_size)
अणु
	काष्ठा cache_disk_superblock *disk_super = dm_block_data(b);

	disk_super->blocknr = cpu_to_le64(dm_block_location(b));
	disk_super->csum = cpu_to_le32(dm_bm_checksum(&disk_super->flags,
						      sb_block_size - माप(__le32),
						      SUPERBLOCK_CSUM_XOR));
पूर्ण

अटल पूर्णांक check_metadata_version(काष्ठा cache_disk_superblock *disk_super)
अणु
	uपूर्णांक32_t metadata_version = le32_to_cpu(disk_super->version);

	अगर (metadata_version < MIN_CACHE_VERSION || metadata_version > MAX_CACHE_VERSION) अणु
		DMERR("Cache metadata version %u found, but only versions between %u and %u supported.",
		      metadata_version, MIN_CACHE_VERSION, MAX_CACHE_VERSION);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sb_check(काष्ठा dm_block_validator *v,
		    काष्ठा dm_block *b,
		    माप_प्रकार sb_block_size)
अणु
	काष्ठा cache_disk_superblock *disk_super = dm_block_data(b);
	__le32 csum_le;

	अगर (dm_block_location(b) != le64_to_cpu(disk_super->blocknr)) अणु
		DMERR("sb_check failed: blocknr %llu: wanted %llu",
		      le64_to_cpu(disk_super->blocknr),
		      (अचिन्हित दीर्घ दीर्घ)dm_block_location(b));
		वापस -ENOTBLK;
	पूर्ण

	अगर (le64_to_cpu(disk_super->magic) != CACHE_SUPERBLOCK_MAGIC) अणु
		DMERR("sb_check failed: magic %llu: wanted %llu",
		      le64_to_cpu(disk_super->magic),
		      (अचिन्हित दीर्घ दीर्घ)CACHE_SUPERBLOCK_MAGIC);
		वापस -EILSEQ;
	पूर्ण

	csum_le = cpu_to_le32(dm_bm_checksum(&disk_super->flags,
					     sb_block_size - माप(__le32),
					     SUPERBLOCK_CSUM_XOR));
	अगर (csum_le != disk_super->csum) अणु
		DMERR("sb_check failed: csum %u: wanted %u",
		      le32_to_cpu(csum_le), le32_to_cpu(disk_super->csum));
		वापस -EILSEQ;
	पूर्ण

	वापस check_metadata_version(disk_super);
पूर्ण

अटल काष्ठा dm_block_validator sb_validator = अणु
	.name = "superblock",
	.prepare_क्रम_ग_लिखो = sb_prepare_क्रम_ग_लिखो,
	.check = sb_check
पूर्ण;

/*----------------------------------------------------------------*/

अटल पूर्णांक superblock_पढ़ो_lock(काष्ठा dm_cache_metadata *cmd,
				काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_पढ़ो_lock(cmd->bm, CACHE_SUPERBLOCK_LOCATION,
			       &sb_validator, sblock);
पूर्ण

अटल पूर्णांक superblock_lock_zero(काष्ठा dm_cache_metadata *cmd,
				काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_ग_लिखो_lock_zero(cmd->bm, CACHE_SUPERBLOCK_LOCATION,
				     &sb_validator, sblock);
पूर्ण

अटल पूर्णांक superblock_lock(काष्ठा dm_cache_metadata *cmd,
			   काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_ग_लिखो_lock(cmd->bm, CACHE_SUPERBLOCK_LOCATION,
				&sb_validator, sblock);
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक __superblock_all_zeroes(काष्ठा dm_block_manager *bm, bool *result)
अणु
	पूर्णांक r;
	अचिन्हित i;
	काष्ठा dm_block *b;
	__le64 *data_le, zero = cpu_to_le64(0);
	अचिन्हित sb_block_size = dm_bm_block_size(bm) / माप(__le64);

	/*
	 * We can't use a validator here - it may be all zeroes.
	 */
	r = dm_bm_पढ़ो_lock(bm, CACHE_SUPERBLOCK_LOCATION, शून्य, &b);
	अगर (r)
		वापस r;

	data_le = dm_block_data(b);
	*result = true;
	क्रम (i = 0; i < sb_block_size; i++) अणु
		अगर (data_le[i] != zero) अणु
			*result = false;
			अवरोध;
		पूर्ण
	पूर्ण

	dm_bm_unlock(b);

	वापस 0;
पूर्ण

अटल व्योम __setup_mapping_info(काष्ठा dm_cache_metadata *cmd)
अणु
	काष्ठा dm_btree_value_type vt;

	vt.context = शून्य;
	vt.size = माप(__le64);
	vt.inc = शून्य;
	vt.dec = शून्य;
	vt.equal = शून्य;
	dm_array_info_init(&cmd->info, cmd->पंचांग, &vt);

	अगर (cmd->policy_hपूर्णांक_size) अणु
		vt.size = माप(__le32);
		dm_array_info_init(&cmd->hपूर्णांक_info, cmd->पंचांग, &vt);
	पूर्ण
पूर्ण

अटल पूर्णांक __save_sm_root(काष्ठा dm_cache_metadata *cmd)
अणु
	पूर्णांक r;
	माप_प्रकार metadata_len;

	r = dm_sm_root_size(cmd->metadata_sm, &metadata_len);
	अगर (r < 0)
		वापस r;

	वापस dm_sm_copy_root(cmd->metadata_sm, &cmd->metadata_space_map_root,
			       metadata_len);
पूर्ण

अटल व्योम __copy_sm_root(काष्ठा dm_cache_metadata *cmd,
			   काष्ठा cache_disk_superblock *disk_super)
अणु
	स_नकल(&disk_super->metadata_space_map_root,
	       &cmd->metadata_space_map_root,
	       माप(cmd->metadata_space_map_root));
पूर्ण

अटल bool separate_dirty_bits(काष्ठा dm_cache_metadata *cmd)
अणु
	वापस cmd->version >= 2;
पूर्ण

अटल पूर्णांक __ग_लिखो_initial_superblock(काष्ठा dm_cache_metadata *cmd)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा cache_disk_superblock *disk_super;
	sector_t bdev_size = i_size_पढ़ो(cmd->bdev->bd_inode) >> SECTOR_SHIFT;

	/* FIXME: see अगर we can lose the max sectors limit */
	अगर (bdev_size > DM_CACHE_METADATA_MAX_SECTORS)
		bdev_size = DM_CACHE_METADATA_MAX_SECTORS;

	r = dm_पंचांग_pre_commit(cmd->पंचांग);
	अगर (r < 0)
		वापस r;

	/*
	 * dm_sm_copy_root() can fail.  So we need to करो it beक्रमe we start
	 * updating the superblock.
	 */
	r = __save_sm_root(cmd);
	अगर (r)
		वापस r;

	r = superblock_lock_zero(cmd, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);
	disk_super->flags = 0;
	स_रखो(disk_super->uuid, 0, माप(disk_super->uuid));
	disk_super->magic = cpu_to_le64(CACHE_SUPERBLOCK_MAGIC);
	disk_super->version = cpu_to_le32(cmd->version);
	स_रखो(disk_super->policy_name, 0, माप(disk_super->policy_name));
	स_रखो(disk_super->policy_version, 0, माप(disk_super->policy_version));
	disk_super->policy_hपूर्णांक_size = cpu_to_le32(0);

	__copy_sm_root(cmd, disk_super);

	disk_super->mapping_root = cpu_to_le64(cmd->root);
	disk_super->hपूर्णांक_root = cpu_to_le64(cmd->hपूर्णांक_root);
	disk_super->discard_root = cpu_to_le64(cmd->discard_root);
	disk_super->discard_block_size = cpu_to_le64(cmd->discard_block_size);
	disk_super->discard_nr_blocks = cpu_to_le64(from_dblock(cmd->discard_nr_blocks));
	disk_super->metadata_block_size = cpu_to_le32(DM_CACHE_METADATA_BLOCK_SIZE);
	disk_super->data_block_size = cpu_to_le32(cmd->data_block_size);
	disk_super->cache_blocks = cpu_to_le32(0);

	disk_super->पढ़ो_hits = cpu_to_le32(0);
	disk_super->पढ़ो_misses = cpu_to_le32(0);
	disk_super->ग_लिखो_hits = cpu_to_le32(0);
	disk_super->ग_लिखो_misses = cpu_to_le32(0);

	अगर (separate_dirty_bits(cmd))
		disk_super->dirty_root = cpu_to_le64(cmd->dirty_root);

	वापस dm_पंचांग_commit(cmd->पंचांग, sblock);
पूर्ण

अटल पूर्णांक __क्रमmat_metadata(काष्ठा dm_cache_metadata *cmd)
अणु
	पूर्णांक r;

	r = dm_पंचांग_create_with_sm(cmd->bm, CACHE_SUPERBLOCK_LOCATION,
				 &cmd->पंचांग, &cmd->metadata_sm);
	अगर (r < 0) अणु
		DMERR("tm_create_with_sm failed");
		वापस r;
	पूर्ण

	__setup_mapping_info(cmd);

	r = dm_array_empty(&cmd->info, &cmd->root);
	अगर (r < 0)
		जाओ bad;

	अगर (separate_dirty_bits(cmd)) अणु
		dm_disk_bitset_init(cmd->पंचांग, &cmd->dirty_info);
		r = dm_bitset_empty(&cmd->dirty_info, &cmd->dirty_root);
		अगर (r < 0)
			जाओ bad;
	पूर्ण

	dm_disk_bitset_init(cmd->पंचांग, &cmd->discard_info);
	r = dm_bitset_empty(&cmd->discard_info, &cmd->discard_root);
	अगर (r < 0)
		जाओ bad;

	cmd->discard_block_size = 0;
	cmd->discard_nr_blocks = 0;

	r = __ग_लिखो_initial_superblock(cmd);
	अगर (r)
		जाओ bad;

	cmd->clean_when_खोलोed = true;
	वापस 0;

bad:
	dm_पंचांग_destroy(cmd->पंचांग);
	dm_sm_destroy(cmd->metadata_sm);

	वापस r;
पूर्ण

अटल पूर्णांक __check_incompat_features(काष्ठा cache_disk_superblock *disk_super,
				     काष्ठा dm_cache_metadata *cmd)
अणु
	uपूर्णांक32_t incompat_flags, features;

	incompat_flags = le32_to_cpu(disk_super->incompat_flags);
	features = incompat_flags & ~DM_CACHE_FEATURE_INCOMPAT_SUPP;
	अगर (features) अणु
		DMERR("could not access metadata due to unsupported optional features (%lx).",
		      (अचिन्हित दीर्घ)features);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check क्रम पढ़ो-only metadata to skip the following RDWR checks.
	 */
	अगर (bdev_पढ़ो_only(cmd->bdev))
		वापस 0;

	features = le32_to_cpu(disk_super->compat_ro_flags) & ~DM_CACHE_FEATURE_COMPAT_RO_SUPP;
	अगर (features) अणु
		DMERR("could not access metadata RDWR due to unsupported optional features (%lx).",
		      (अचिन्हित दीर्घ)features);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __खोलो_metadata(काष्ठा dm_cache_metadata *cmd)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा cache_disk_superblock *disk_super;
	अचिन्हित दीर्घ sb_flags;

	r = superblock_पढ़ो_lock(cmd, &sblock);
	अगर (r < 0) अणु
		DMERR("couldn't read lock superblock");
		वापस r;
	पूर्ण

	disk_super = dm_block_data(sblock);

	/* Verअगरy the data block size hasn't changed */
	अगर (le32_to_cpu(disk_super->data_block_size) != cmd->data_block_size) अणु
		DMERR("changing the data block size (from %u to %llu) is not supported",
		      le32_to_cpu(disk_super->data_block_size),
		      (अचिन्हित दीर्घ दीर्घ)cmd->data_block_size);
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	r = __check_incompat_features(disk_super, cmd);
	अगर (r < 0)
		जाओ bad;

	r = dm_पंचांग_खोलो_with_sm(cmd->bm, CACHE_SUPERBLOCK_LOCATION,
			       disk_super->metadata_space_map_root,
			       माप(disk_super->metadata_space_map_root),
			       &cmd->पंचांग, &cmd->metadata_sm);
	अगर (r < 0) अणु
		DMERR("tm_open_with_sm failed");
		जाओ bad;
	पूर्ण

	__setup_mapping_info(cmd);
	dm_disk_bitset_init(cmd->पंचांग, &cmd->dirty_info);
	dm_disk_bitset_init(cmd->पंचांग, &cmd->discard_info);
	sb_flags = le32_to_cpu(disk_super->flags);
	cmd->clean_when_खोलोed = test_bit(CLEAN_SHUTDOWN, &sb_flags);
	dm_bm_unlock(sblock);

	वापस 0;

bad:
	dm_bm_unlock(sblock);
	वापस r;
पूर्ण

अटल पूर्णांक __खोलो_or_क्रमmat_metadata(काष्ठा dm_cache_metadata *cmd,
				     bool क्रमmat_device)
अणु
	पूर्णांक r;
	bool unक्रमmatted = false;

	r = __superblock_all_zeroes(cmd->bm, &unक्रमmatted);
	अगर (r)
		वापस r;

	अगर (unक्रमmatted)
		वापस क्रमmat_device ? __क्रमmat_metadata(cmd) : -EPERM;

	वापस __खोलो_metadata(cmd);
पूर्ण

अटल पूर्णांक __create_persistent_data_objects(काष्ठा dm_cache_metadata *cmd,
					    bool may_क्रमmat_device)
अणु
	पूर्णांक r;
	cmd->bm = dm_block_manager_create(cmd->bdev, DM_CACHE_METADATA_BLOCK_SIZE << SECTOR_SHIFT,
					  CACHE_MAX_CONCURRENT_LOCKS);
	अगर (IS_ERR(cmd->bm)) अणु
		DMERR("could not create block manager");
		r = PTR_ERR(cmd->bm);
		cmd->bm = शून्य;
		वापस r;
	पूर्ण

	r = __खोलो_or_क्रमmat_metadata(cmd, may_क्रमmat_device);
	अगर (r) अणु
		dm_block_manager_destroy(cmd->bm);
		cmd->bm = शून्य;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम __destroy_persistent_data_objects(काष्ठा dm_cache_metadata *cmd)
अणु
	dm_sm_destroy(cmd->metadata_sm);
	dm_पंचांग_destroy(cmd->पंचांग);
	dm_block_manager_destroy(cmd->bm);
पूर्ण

प्रकार अचिन्हित दीर्घ (*flags_mutator)(अचिन्हित दीर्घ);

अटल व्योम update_flags(काष्ठा cache_disk_superblock *disk_super,
			 flags_mutator mutator)
अणु
	uपूर्णांक32_t sb_flags = mutator(le32_to_cpu(disk_super->flags));
	disk_super->flags = cpu_to_le32(sb_flags);
पूर्ण

अटल अचिन्हित दीर्घ set_clean_shutकरोwn(अचिन्हित दीर्घ flags)
अणु
	set_bit(CLEAN_SHUTDOWN, &flags);
	वापस flags;
पूर्ण

अटल अचिन्हित दीर्घ clear_clean_shutकरोwn(अचिन्हित दीर्घ flags)
अणु
	clear_bit(CLEAN_SHUTDOWN, &flags);
	वापस flags;
पूर्ण

अटल व्योम पढ़ो_superblock_fields(काष्ठा dm_cache_metadata *cmd,
				   काष्ठा cache_disk_superblock *disk_super)
अणु
	cmd->version = le32_to_cpu(disk_super->version);
	cmd->flags = le32_to_cpu(disk_super->flags);
	cmd->root = le64_to_cpu(disk_super->mapping_root);
	cmd->hपूर्णांक_root = le64_to_cpu(disk_super->hपूर्णांक_root);
	cmd->discard_root = le64_to_cpu(disk_super->discard_root);
	cmd->discard_block_size = le64_to_cpu(disk_super->discard_block_size);
	cmd->discard_nr_blocks = to_dblock(le64_to_cpu(disk_super->discard_nr_blocks));
	cmd->data_block_size = le32_to_cpu(disk_super->data_block_size);
	cmd->cache_blocks = to_cblock(le32_to_cpu(disk_super->cache_blocks));
	म_नकलन(cmd->policy_name, disk_super->policy_name, माप(cmd->policy_name));
	cmd->policy_version[0] = le32_to_cpu(disk_super->policy_version[0]);
	cmd->policy_version[1] = le32_to_cpu(disk_super->policy_version[1]);
	cmd->policy_version[2] = le32_to_cpu(disk_super->policy_version[2]);
	cmd->policy_hपूर्णांक_size = le32_to_cpu(disk_super->policy_hपूर्णांक_size);

	cmd->stats.पढ़ो_hits = le32_to_cpu(disk_super->पढ़ो_hits);
	cmd->stats.पढ़ो_misses = le32_to_cpu(disk_super->पढ़ो_misses);
	cmd->stats.ग_लिखो_hits = le32_to_cpu(disk_super->ग_लिखो_hits);
	cmd->stats.ग_लिखो_misses = le32_to_cpu(disk_super->ग_लिखो_misses);

	अगर (separate_dirty_bits(cmd))
		cmd->dirty_root = le64_to_cpu(disk_super->dirty_root);

	cmd->changed = false;
पूर्ण

/*
 * The mutator updates the superblock flags.
 */
अटल पूर्णांक __begin_transaction_flags(काष्ठा dm_cache_metadata *cmd,
				     flags_mutator mutator)
अणु
	पूर्णांक r;
	काष्ठा cache_disk_superblock *disk_super;
	काष्ठा dm_block *sblock;

	r = superblock_lock(cmd, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);
	update_flags(disk_super, mutator);
	पढ़ो_superblock_fields(cmd, disk_super);
	dm_bm_unlock(sblock);

	वापस dm_bm_flush(cmd->bm);
पूर्ण

अटल पूर्णांक __begin_transaction(काष्ठा dm_cache_metadata *cmd)
अणु
	पूर्णांक r;
	काष्ठा cache_disk_superblock *disk_super;
	काष्ठा dm_block *sblock;

	/*
	 * We re-पढ़ो the superblock every समय.  Shouldn't need to करो this
	 * really.
	 */
	r = superblock_पढ़ो_lock(cmd, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);
	पढ़ो_superblock_fields(cmd, disk_super);
	dm_bm_unlock(sblock);

	वापस 0;
पूर्ण

अटल पूर्णांक __commit_transaction(काष्ठा dm_cache_metadata *cmd,
				flags_mutator mutator)
अणु
	पूर्णांक r;
	काष्ठा cache_disk_superblock *disk_super;
	काष्ठा dm_block *sblock;

	/*
	 * We need to know अगर the cache_disk_superblock exceeds a 512-byte sector.
	 */
	BUILD_BUG_ON(माप(काष्ठा cache_disk_superblock) > 512);

	अगर (separate_dirty_bits(cmd)) अणु
		r = dm_bitset_flush(&cmd->dirty_info, cmd->dirty_root,
				    &cmd->dirty_root);
		अगर (r)
			वापस r;
	पूर्ण

	r = dm_bitset_flush(&cmd->discard_info, cmd->discard_root,
			    &cmd->discard_root);
	अगर (r)
		वापस r;

	r = dm_पंचांग_pre_commit(cmd->पंचांग);
	अगर (r < 0)
		वापस r;

	r = __save_sm_root(cmd);
	अगर (r)
		वापस r;

	r = superblock_lock(cmd, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);

	disk_super->flags = cpu_to_le32(cmd->flags);
	अगर (mutator)
		update_flags(disk_super, mutator);

	disk_super->mapping_root = cpu_to_le64(cmd->root);
	अगर (separate_dirty_bits(cmd))
		disk_super->dirty_root = cpu_to_le64(cmd->dirty_root);
	disk_super->hपूर्णांक_root = cpu_to_le64(cmd->hपूर्णांक_root);
	disk_super->discard_root = cpu_to_le64(cmd->discard_root);
	disk_super->discard_block_size = cpu_to_le64(cmd->discard_block_size);
	disk_super->discard_nr_blocks = cpu_to_le64(from_dblock(cmd->discard_nr_blocks));
	disk_super->cache_blocks = cpu_to_le32(from_cblock(cmd->cache_blocks));
	म_नकलन(disk_super->policy_name, cmd->policy_name, माप(disk_super->policy_name));
	disk_super->policy_version[0] = cpu_to_le32(cmd->policy_version[0]);
	disk_super->policy_version[1] = cpu_to_le32(cmd->policy_version[1]);
	disk_super->policy_version[2] = cpu_to_le32(cmd->policy_version[2]);
	disk_super->policy_hपूर्णांक_size = cpu_to_le32(cmd->policy_hपूर्णांक_size);

	disk_super->पढ़ो_hits = cpu_to_le32(cmd->stats.पढ़ो_hits);
	disk_super->पढ़ो_misses = cpu_to_le32(cmd->stats.पढ़ो_misses);
	disk_super->ग_लिखो_hits = cpu_to_le32(cmd->stats.ग_लिखो_hits);
	disk_super->ग_लिखो_misses = cpu_to_le32(cmd->stats.ग_लिखो_misses);
	__copy_sm_root(cmd, disk_super);

	वापस dm_पंचांग_commit(cmd->पंचांग, sblock);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * The mappings are held in a dm-array that has 64-bit values stored in
 * little-endian क्रमmat.  The index is the cblock, the high 48bits of the
 * value are the oblock and the low 16 bit the flags.
 */
#घोषणा FLAGS_MASK ((1 << 16) - 1)

अटल __le64 pack_value(dm_oblock_t block, अचिन्हित flags)
अणु
	uपूर्णांक64_t value = from_oblock(block);
	value <<= 16;
	value = value | (flags & FLAGS_MASK);
	वापस cpu_to_le64(value);
पूर्ण

अटल व्योम unpack_value(__le64 value_le, dm_oblock_t *block, अचिन्हित *flags)
अणु
	uपूर्णांक64_t value = le64_to_cpu(value_le);
	uपूर्णांक64_t b = value >> 16;
	*block = to_oblock(b);
	*flags = value & FLAGS_MASK;
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा dm_cache_metadata *metadata_खोलो(काष्ठा block_device *bdev,
					       sector_t data_block_size,
					       bool may_क्रमmat_device,
					       माप_प्रकार policy_hपूर्णांक_size,
					       अचिन्हित metadata_version)
अणु
	पूर्णांक r;
	काष्ठा dm_cache_metadata *cmd;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		DMERR("could not allocate metadata struct");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	cmd->version = metadata_version;
	refcount_set(&cmd->ref_count, 1);
	init_rwsem(&cmd->root_lock);
	cmd->bdev = bdev;
	cmd->data_block_size = data_block_size;
	cmd->cache_blocks = 0;
	cmd->policy_hपूर्णांक_size = policy_hपूर्णांक_size;
	cmd->changed = true;
	cmd->fail_io = false;

	r = __create_persistent_data_objects(cmd, may_क्रमmat_device);
	अगर (r) अणु
		kमुक्त(cmd);
		वापस ERR_PTR(r);
	पूर्ण

	r = __begin_transaction_flags(cmd, clear_clean_shutकरोwn);
	अगर (r < 0) अणु
		dm_cache_metadata_बंद(cmd);
		वापस ERR_PTR(r);
	पूर्ण

	वापस cmd;
पूर्ण

/*
 * We keep a little list of ref counted metadata objects to prevent two
 * dअगरferent target instances creating separate bufio instances.  This is
 * an issue अगर a table is reloaded beक्रमe the suspend.
 */
अटल DEFINE_MUTEX(table_lock);
अटल LIST_HEAD(table);

अटल काष्ठा dm_cache_metadata *lookup(काष्ठा block_device *bdev)
अणु
	काष्ठा dm_cache_metadata *cmd;

	list_क्रम_each_entry(cmd, &table, list)
		अगर (cmd->bdev == bdev) अणु
			refcount_inc(&cmd->ref_count);
			वापस cmd;
		पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा dm_cache_metadata *lookup_or_खोलो(काष्ठा block_device *bdev,
						sector_t data_block_size,
						bool may_क्रमmat_device,
						माप_प्रकार policy_hपूर्णांक_size,
						अचिन्हित metadata_version)
अणु
	काष्ठा dm_cache_metadata *cmd, *cmd2;

	mutex_lock(&table_lock);
	cmd = lookup(bdev);
	mutex_unlock(&table_lock);

	अगर (cmd)
		वापस cmd;

	cmd = metadata_खोलो(bdev, data_block_size, may_क्रमmat_device,
			    policy_hपूर्णांक_size, metadata_version);
	अगर (!IS_ERR(cmd)) अणु
		mutex_lock(&table_lock);
		cmd2 = lookup(bdev);
		अगर (cmd2) अणु
			mutex_unlock(&table_lock);
			__destroy_persistent_data_objects(cmd);
			kमुक्त(cmd);
			वापस cmd2;
		पूर्ण
		list_add(&cmd->list, &table);
		mutex_unlock(&table_lock);
	पूर्ण

	वापस cmd;
पूर्ण

अटल bool same_params(काष्ठा dm_cache_metadata *cmd, sector_t data_block_size)
अणु
	अगर (cmd->data_block_size != data_block_size) अणु
		DMERR("data_block_size (%llu) different from that in metadata (%llu)",
		      (अचिन्हित दीर्घ दीर्घ) data_block_size,
		      (अचिन्हित दीर्घ दीर्घ) cmd->data_block_size);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा dm_cache_metadata *dm_cache_metadata_खोलो(काष्ठा block_device *bdev,
						 sector_t data_block_size,
						 bool may_क्रमmat_device,
						 माप_प्रकार policy_hपूर्णांक_size,
						 अचिन्हित metadata_version)
अणु
	काष्ठा dm_cache_metadata *cmd = lookup_or_खोलो(bdev, data_block_size, may_क्रमmat_device,
						       policy_hपूर्णांक_size, metadata_version);

	अगर (!IS_ERR(cmd) && !same_params(cmd, data_block_size)) अणु
		dm_cache_metadata_बंद(cmd);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस cmd;
पूर्ण

व्योम dm_cache_metadata_बंद(काष्ठा dm_cache_metadata *cmd)
अणु
	अगर (refcount_dec_and_test(&cmd->ref_count)) अणु
		mutex_lock(&table_lock);
		list_del(&cmd->list);
		mutex_unlock(&table_lock);

		अगर (!cmd->fail_io)
			__destroy_persistent_data_objects(cmd);
		kमुक्त(cmd);
	पूर्ण
पूर्ण

/*
 * Checks that the given cache block is either unmapped or clean.
 */
अटल पूर्णांक block_clean_combined_dirty(काष्ठा dm_cache_metadata *cmd, dm_cblock_t b,
				      bool *result)
अणु
	पूर्णांक r;
	__le64 value;
	dm_oblock_t ob;
	अचिन्हित flags;

	r = dm_array_get_value(&cmd->info, cmd->root, from_cblock(b), &value);
	अगर (r)
		वापस r;

	unpack_value(value, &ob, &flags);
	*result = !((flags & M_VALID) && (flags & M_सूचीTY));

	वापस 0;
पूर्ण

अटल पूर्णांक blocks_are_clean_combined_dirty(काष्ठा dm_cache_metadata *cmd,
					   dm_cblock_t begin, dm_cblock_t end,
					   bool *result)
अणु
	पूर्णांक r;
	*result = true;

	जबतक (begin != end) अणु
		r = block_clean_combined_dirty(cmd, begin, result);
		अगर (r) अणु
			DMERR("block_clean_combined_dirty failed");
			वापस r;
		पूर्ण

		अगर (!*result) अणु
			DMERR("cache block %llu is dirty",
			      (अचिन्हित दीर्घ दीर्घ) from_cblock(begin));
			वापस 0;
		पूर्ण

		begin = to_cblock(from_cblock(begin) + 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक blocks_are_clean_separate_dirty(काष्ठा dm_cache_metadata *cmd,
					   dm_cblock_t begin, dm_cblock_t end,
					   bool *result)
अणु
	पूर्णांक r;
	bool dirty_flag;
	*result = true;

	अगर (from_cblock(cmd->cache_blocks) == 0)
		/* Nothing to करो */
		वापस 0;

	r = dm_bitset_cursor_begin(&cmd->dirty_info, cmd->dirty_root,
				   from_cblock(cmd->cache_blocks), &cmd->dirty_cursor);
	अगर (r) अणु
		DMERR("%s: dm_bitset_cursor_begin for dirty failed", __func__);
		वापस r;
	पूर्ण

	r = dm_bitset_cursor_skip(&cmd->dirty_cursor, from_cblock(begin));
	अगर (r) अणु
		DMERR("%s: dm_bitset_cursor_skip for dirty failed", __func__);
		dm_bitset_cursor_end(&cmd->dirty_cursor);
		वापस r;
	पूर्ण

	जबतक (begin != end) अणु
		/*
		 * We assume that unmapped blocks have their dirty bit
		 * cleared.
		 */
		dirty_flag = dm_bitset_cursor_get_value(&cmd->dirty_cursor);
		अगर (dirty_flag) अणु
			DMERR("%s: cache block %llu is dirty", __func__,
			      (अचिन्हित दीर्घ दीर्घ) from_cblock(begin));
			dm_bitset_cursor_end(&cmd->dirty_cursor);
			*result = false;
			वापस 0;
		पूर्ण

		begin = to_cblock(from_cblock(begin) + 1);
		अगर (begin == end)
			अवरोध;

		r = dm_bitset_cursor_next(&cmd->dirty_cursor);
		अगर (r) अणु
			DMERR("%s: dm_bitset_cursor_next for dirty failed", __func__);
			dm_bitset_cursor_end(&cmd->dirty_cursor);
			वापस r;
		पूर्ण
	पूर्ण

	dm_bitset_cursor_end(&cmd->dirty_cursor);

	वापस 0;
पूर्ण

अटल पूर्णांक blocks_are_unmapped_or_clean(काष्ठा dm_cache_metadata *cmd,
					dm_cblock_t begin, dm_cblock_t end,
					bool *result)
अणु
	अगर (separate_dirty_bits(cmd))
		वापस blocks_are_clean_separate_dirty(cmd, begin, end, result);
	अन्यथा
		वापस blocks_are_clean_combined_dirty(cmd, begin, end, result);
पूर्ण

अटल bool cmd_ग_लिखो_lock(काष्ठा dm_cache_metadata *cmd)
अणु
	करोwn_ग_लिखो(&cmd->root_lock);
	अगर (cmd->fail_io || dm_bm_is_पढ़ो_only(cmd->bm)) अणु
		up_ग_लिखो(&cmd->root_lock);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

#घोषणा WRITE_LOCK(cmd)				\
	करो अणु					\
		अगर (!cmd_ग_लिखो_lock((cmd)))	\
			वापस -EINVAL;		\
	पूर्ण जबतक(0)

#घोषणा WRITE_LOCK_VOID(cmd)			\
	करो अणु					\
		अगर (!cmd_ग_लिखो_lock((cmd)))	\
			वापस;			\
	पूर्ण जबतक(0)

#घोषणा WRITE_UNLOCK(cmd) \
	up_ग_लिखो(&(cmd)->root_lock)

अटल bool cmd_पढ़ो_lock(काष्ठा dm_cache_metadata *cmd)
अणु
	करोwn_पढ़ो(&cmd->root_lock);
	अगर (cmd->fail_io) अणु
		up_पढ़ो(&cmd->root_lock);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

#घोषणा READ_LOCK(cmd)				\
	करो अणु					\
		अगर (!cmd_पढ़ो_lock((cmd)))	\
			वापस -EINVAL;		\
	पूर्ण जबतक(0)

#घोषणा READ_LOCK_VOID(cmd)			\
	करो अणु					\
		अगर (!cmd_पढ़ो_lock((cmd)))	\
			वापस;			\
	पूर्ण जबतक(0)

#घोषणा READ_UNLOCK(cmd) \
	up_पढ़ो(&(cmd)->root_lock)

पूर्णांक dm_cache_resize(काष्ठा dm_cache_metadata *cmd, dm_cblock_t new_cache_size)
अणु
	पूर्णांक r;
	bool clean;
	__le64 null_mapping = pack_value(0, 0);

	WRITE_LOCK(cmd);
	__dm_bless_क्रम_disk(&null_mapping);

	अगर (from_cblock(new_cache_size) < from_cblock(cmd->cache_blocks)) अणु
		r = blocks_are_unmapped_or_clean(cmd, new_cache_size, cmd->cache_blocks, &clean);
		अगर (r) अणु
			__dm_unbless_क्रम_disk(&null_mapping);
			जाओ out;
		पूर्ण

		अगर (!clean) अणु
			DMERR("unable to shrink cache due to dirty blocks");
			r = -EINVAL;
			__dm_unbless_क्रम_disk(&null_mapping);
			जाओ out;
		पूर्ण
	पूर्ण

	r = dm_array_resize(&cmd->info, cmd->root, from_cblock(cmd->cache_blocks),
			    from_cblock(new_cache_size),
			    &null_mapping, &cmd->root);
	अगर (r)
		जाओ out;

	अगर (separate_dirty_bits(cmd)) अणु
		r = dm_bitset_resize(&cmd->dirty_info, cmd->dirty_root,
				     from_cblock(cmd->cache_blocks), from_cblock(new_cache_size),
				     false, &cmd->dirty_root);
		अगर (r)
			जाओ out;
	पूर्ण

	cmd->cache_blocks = new_cache_size;
	cmd->changed = true;

out:
	WRITE_UNLOCK(cmd);

	वापस r;
पूर्ण

पूर्णांक dm_cache_discard_bitset_resize(काष्ठा dm_cache_metadata *cmd,
				   sector_t discard_block_size,
				   dm_dblock_t new_nr_entries)
अणु
	पूर्णांक r;

	WRITE_LOCK(cmd);
	r = dm_bitset_resize(&cmd->discard_info,
			     cmd->discard_root,
			     from_dblock(cmd->discard_nr_blocks),
			     from_dblock(new_nr_entries),
			     false, &cmd->discard_root);
	अगर (!r) अणु
		cmd->discard_block_size = discard_block_size;
		cmd->discard_nr_blocks = new_nr_entries;
	पूर्ण

	cmd->changed = true;
	WRITE_UNLOCK(cmd);

	वापस r;
पूर्ण

अटल पूर्णांक __set_discard(काष्ठा dm_cache_metadata *cmd, dm_dblock_t b)
अणु
	वापस dm_bitset_set_bit(&cmd->discard_info, cmd->discard_root,
				 from_dblock(b), &cmd->discard_root);
पूर्ण

अटल पूर्णांक __clear_discard(काष्ठा dm_cache_metadata *cmd, dm_dblock_t b)
अणु
	वापस dm_bitset_clear_bit(&cmd->discard_info, cmd->discard_root,
				   from_dblock(b), &cmd->discard_root);
पूर्ण

अटल पूर्णांक __discard(काष्ठा dm_cache_metadata *cmd,
		     dm_dblock_t dblock, bool discard)
अणु
	पूर्णांक r;

	r = (discard ? __set_discard : __clear_discard)(cmd, dblock);
	अगर (r)
		वापस r;

	cmd->changed = true;
	वापस 0;
पूर्ण

पूर्णांक dm_cache_set_discard(काष्ठा dm_cache_metadata *cmd,
			 dm_dblock_t dblock, bool discard)
अणु
	पूर्णांक r;

	WRITE_LOCK(cmd);
	r = __discard(cmd, dblock, discard);
	WRITE_UNLOCK(cmd);

	वापस r;
पूर्ण

अटल पूर्णांक __load_discards(काष्ठा dm_cache_metadata *cmd,
			   load_discard_fn fn, व्योम *context)
अणु
	पूर्णांक r = 0;
	uपूर्णांक32_t b;
	काष्ठा dm_bitset_cursor c;

	अगर (from_dblock(cmd->discard_nr_blocks) == 0)
		/* nothing to करो */
		वापस 0;

	अगर (cmd->clean_when_खोलोed) अणु
		r = dm_bitset_flush(&cmd->discard_info, cmd->discard_root, &cmd->discard_root);
		अगर (r)
			वापस r;

		r = dm_bitset_cursor_begin(&cmd->discard_info, cmd->discard_root,
					   from_dblock(cmd->discard_nr_blocks), &c);
		अगर (r)
			वापस r;

		क्रम (b = 0; ; b++) अणु
			r = fn(context, cmd->discard_block_size, to_dblock(b),
			       dm_bitset_cursor_get_value(&c));
			अगर (r)
				अवरोध;

			अगर (b >= (from_dblock(cmd->discard_nr_blocks) - 1))
				अवरोध;

			r = dm_bitset_cursor_next(&c);
			अगर (r)
				अवरोध;
		पूर्ण

		dm_bitset_cursor_end(&c);

	पूर्ण अन्यथा अणु
		क्रम (b = 0; b < from_dblock(cmd->discard_nr_blocks); b++) अणु
			r = fn(context, cmd->discard_block_size, to_dblock(b), false);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक dm_cache_load_discards(काष्ठा dm_cache_metadata *cmd,
			   load_discard_fn fn, व्योम *context)
अणु
	पूर्णांक r;

	READ_LOCK(cmd);
	r = __load_discards(cmd, fn, context);
	READ_UNLOCK(cmd);

	वापस r;
पूर्ण

पूर्णांक dm_cache_size(काष्ठा dm_cache_metadata *cmd, dm_cblock_t *result)
अणु
	READ_LOCK(cmd);
	*result = cmd->cache_blocks;
	READ_UNLOCK(cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक __हटाओ(काष्ठा dm_cache_metadata *cmd, dm_cblock_t cblock)
अणु
	पूर्णांक r;
	__le64 value = pack_value(0, 0);

	__dm_bless_क्रम_disk(&value);
	r = dm_array_set_value(&cmd->info, cmd->root, from_cblock(cblock),
			       &value, &cmd->root);
	अगर (r)
		वापस r;

	cmd->changed = true;
	वापस 0;
पूर्ण

पूर्णांक dm_cache_हटाओ_mapping(काष्ठा dm_cache_metadata *cmd, dm_cblock_t cblock)
अणु
	पूर्णांक r;

	WRITE_LOCK(cmd);
	r = __हटाओ(cmd, cblock);
	WRITE_UNLOCK(cmd);

	वापस r;
पूर्ण

अटल पूर्णांक __insert(काष्ठा dm_cache_metadata *cmd,
		    dm_cblock_t cblock, dm_oblock_t oblock)
अणु
	पूर्णांक r;
	__le64 value = pack_value(oblock, M_VALID);
	__dm_bless_क्रम_disk(&value);

	r = dm_array_set_value(&cmd->info, cmd->root, from_cblock(cblock),
			       &value, &cmd->root);
	अगर (r)
		वापस r;

	cmd->changed = true;
	वापस 0;
पूर्ण

पूर्णांक dm_cache_insert_mapping(काष्ठा dm_cache_metadata *cmd,
			    dm_cblock_t cblock, dm_oblock_t oblock)
अणु
	पूर्णांक r;

	WRITE_LOCK(cmd);
	r = __insert(cmd, cblock, oblock);
	WRITE_UNLOCK(cmd);

	वापस r;
पूर्ण

काष्ठा thunk अणु
	load_mapping_fn fn;
	व्योम *context;

	काष्ठा dm_cache_metadata *cmd;
	bool respect_dirty_flags;
	bool hपूर्णांकs_valid;
पूर्ण;

अटल bool policy_unchanged(काष्ठा dm_cache_metadata *cmd,
			     काष्ठा dm_cache_policy *policy)
अणु
	स्थिर अक्षर *policy_name = dm_cache_policy_get_name(policy);
	स्थिर अचिन्हित *policy_version = dm_cache_policy_get_version(policy);
	माप_प्रकार policy_hपूर्णांक_size = dm_cache_policy_get_hपूर्णांक_size(policy);

	/*
	 * Ensure policy names match.
	 */
	अगर (म_भेदन(cmd->policy_name, policy_name, माप(cmd->policy_name)))
		वापस false;

	/*
	 * Ensure policy major versions match.
	 */
	अगर (cmd->policy_version[0] != policy_version[0])
		वापस false;

	/*
	 * Ensure policy hपूर्णांक sizes match.
	 */
	अगर (cmd->policy_hपूर्णांक_size != policy_hपूर्णांक_size)
		वापस false;

	वापस true;
पूर्ण

अटल bool hपूर्णांकs_array_initialized(काष्ठा dm_cache_metadata *cmd)
अणु
	वापस cmd->hपूर्णांक_root && cmd->policy_hपूर्णांक_size;
पूर्ण

अटल bool hपूर्णांकs_array_available(काष्ठा dm_cache_metadata *cmd,
				  काष्ठा dm_cache_policy *policy)
अणु
	वापस cmd->clean_when_खोलोed && policy_unchanged(cmd, policy) &&
		hपूर्णांकs_array_initialized(cmd);
पूर्ण

अटल पूर्णांक __load_mapping_v1(काष्ठा dm_cache_metadata *cmd,
			     uपूर्णांक64_t cb, bool hपूर्णांकs_valid,
			     काष्ठा dm_array_cursor *mapping_cursor,
			     काष्ठा dm_array_cursor *hपूर्णांक_cursor,
			     load_mapping_fn fn, व्योम *context)
अणु
	पूर्णांक r = 0;

	__le64 mapping;
	__le32 hपूर्णांक = 0;

	__le64 *mapping_value_le;
	__le32 *hपूर्णांक_value_le;

	dm_oblock_t oblock;
	अचिन्हित flags;
	bool dirty = true;

	dm_array_cursor_get_value(mapping_cursor, (व्योम **) &mapping_value_le);
	स_नकल(&mapping, mapping_value_le, माप(mapping));
	unpack_value(mapping, &oblock, &flags);

	अगर (flags & M_VALID) अणु
		अगर (hपूर्णांकs_valid) अणु
			dm_array_cursor_get_value(hपूर्णांक_cursor, (व्योम **) &hपूर्णांक_value_le);
			स_नकल(&hपूर्णांक, hपूर्णांक_value_le, माप(hपूर्णांक));
		पूर्ण
		अगर (cmd->clean_when_खोलोed)
			dirty = flags & M_सूचीTY;

		r = fn(context, oblock, to_cblock(cb), dirty,
		       le32_to_cpu(hपूर्णांक), hपूर्णांकs_valid);
		अगर (r) अणु
			DMERR("policy couldn't load cache block %llu",
			      (अचिन्हित दीर्घ दीर्घ) from_cblock(to_cblock(cb)));
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक __load_mapping_v2(काष्ठा dm_cache_metadata *cmd,
			     uपूर्णांक64_t cb, bool hपूर्णांकs_valid,
			     काष्ठा dm_array_cursor *mapping_cursor,
			     काष्ठा dm_array_cursor *hपूर्णांक_cursor,
			     काष्ठा dm_bitset_cursor *dirty_cursor,
			     load_mapping_fn fn, व्योम *context)
अणु
	पूर्णांक r = 0;

	__le64 mapping;
	__le32 hपूर्णांक = 0;

	__le64 *mapping_value_le;
	__le32 *hपूर्णांक_value_le;

	dm_oblock_t oblock;
	अचिन्हित flags;
	bool dirty = true;

	dm_array_cursor_get_value(mapping_cursor, (व्योम **) &mapping_value_le);
	स_नकल(&mapping, mapping_value_le, माप(mapping));
	unpack_value(mapping, &oblock, &flags);

	अगर (flags & M_VALID) अणु
		अगर (hपूर्णांकs_valid) अणु
			dm_array_cursor_get_value(hपूर्णांक_cursor, (व्योम **) &hपूर्णांक_value_le);
			स_नकल(&hपूर्णांक, hपूर्णांक_value_le, माप(hपूर्णांक));
		पूर्ण
		अगर (cmd->clean_when_खोलोed)
			dirty = dm_bitset_cursor_get_value(dirty_cursor);

		r = fn(context, oblock, to_cblock(cb), dirty,
		       le32_to_cpu(hपूर्णांक), hपूर्णांकs_valid);
		अगर (r) अणु
			DMERR("policy couldn't load cache block %llu",
			      (अचिन्हित दीर्घ दीर्घ) from_cblock(to_cblock(cb)));
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक __load_mappings(काष्ठा dm_cache_metadata *cmd,
			   काष्ठा dm_cache_policy *policy,
			   load_mapping_fn fn, व्योम *context)
अणु
	पूर्णांक r;
	uपूर्णांक64_t cb;

	bool hपूर्णांकs_valid = hपूर्णांकs_array_available(cmd, policy);

	अगर (from_cblock(cmd->cache_blocks) == 0)
		/* Nothing to करो */
		वापस 0;

	r = dm_array_cursor_begin(&cmd->info, cmd->root, &cmd->mapping_cursor);
	अगर (r)
		वापस r;

	अगर (hपूर्णांकs_valid) अणु
		r = dm_array_cursor_begin(&cmd->hपूर्णांक_info, cmd->hपूर्णांक_root, &cmd->hपूर्णांक_cursor);
		अगर (r) अणु
			dm_array_cursor_end(&cmd->mapping_cursor);
			वापस r;
		पूर्ण
	पूर्ण

	अगर (separate_dirty_bits(cmd)) अणु
		r = dm_bitset_cursor_begin(&cmd->dirty_info, cmd->dirty_root,
					   from_cblock(cmd->cache_blocks),
					   &cmd->dirty_cursor);
		अगर (r) अणु
			dm_array_cursor_end(&cmd->hपूर्णांक_cursor);
			dm_array_cursor_end(&cmd->mapping_cursor);
			वापस r;
		पूर्ण
	पूर्ण

	क्रम (cb = 0; ; cb++) अणु
		अगर (separate_dirty_bits(cmd))
			r = __load_mapping_v2(cmd, cb, hपूर्णांकs_valid,
					      &cmd->mapping_cursor,
					      &cmd->hपूर्णांक_cursor,
					      &cmd->dirty_cursor,
					      fn, context);
		अन्यथा
			r = __load_mapping_v1(cmd, cb, hपूर्णांकs_valid,
					      &cmd->mapping_cursor, &cmd->hपूर्णांक_cursor,
					      fn, context);
		अगर (r)
			जाओ out;

		/*
		 * We need to अवरोध out beक्रमe we move the cursors.
		 */
		अगर (cb >= (from_cblock(cmd->cache_blocks) - 1))
			अवरोध;

		r = dm_array_cursor_next(&cmd->mapping_cursor);
		अगर (r) अणु
			DMERR("dm_array_cursor_next for mapping failed");
			जाओ out;
		पूर्ण

		अगर (hपूर्णांकs_valid) अणु
			r = dm_array_cursor_next(&cmd->hपूर्णांक_cursor);
			अगर (r) अणु
				dm_array_cursor_end(&cmd->hपूर्णांक_cursor);
				hपूर्णांकs_valid = false;
			पूर्ण
		पूर्ण

		अगर (separate_dirty_bits(cmd)) अणु
			r = dm_bitset_cursor_next(&cmd->dirty_cursor);
			अगर (r) अणु
				DMERR("dm_bitset_cursor_next for dirty failed");
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	dm_array_cursor_end(&cmd->mapping_cursor);
	अगर (hपूर्णांकs_valid)
		dm_array_cursor_end(&cmd->hपूर्णांक_cursor);

	अगर (separate_dirty_bits(cmd))
		dm_bitset_cursor_end(&cmd->dirty_cursor);

	वापस r;
पूर्ण

पूर्णांक dm_cache_load_mappings(काष्ठा dm_cache_metadata *cmd,
			   काष्ठा dm_cache_policy *policy,
			   load_mapping_fn fn, व्योम *context)
अणु
	पूर्णांक r;

	READ_LOCK(cmd);
	r = __load_mappings(cmd, policy, fn, context);
	READ_UNLOCK(cmd);

	वापस r;
पूर्ण

अटल पूर्णांक __dump_mapping(व्योम *context, uपूर्णांक64_t cblock, व्योम *leaf)
अणु
	पूर्णांक r = 0;
	__le64 value;
	dm_oblock_t oblock;
	अचिन्हित flags;

	स_नकल(&value, leaf, माप(value));
	unpack_value(value, &oblock, &flags);

	वापस r;
पूर्ण

अटल पूर्णांक __dump_mappings(काष्ठा dm_cache_metadata *cmd)
अणु
	वापस dm_array_walk(&cmd->info, cmd->root, __dump_mapping, शून्य);
पूर्ण

व्योम dm_cache_dump(काष्ठा dm_cache_metadata *cmd)
अणु
	READ_LOCK_VOID(cmd);
	__dump_mappings(cmd);
	READ_UNLOCK(cmd);
पूर्ण

पूर्णांक dm_cache_changed_this_transaction(काष्ठा dm_cache_metadata *cmd)
अणु
	पूर्णांक r;

	READ_LOCK(cmd);
	r = cmd->changed;
	READ_UNLOCK(cmd);

	वापस r;
पूर्ण

अटल पूर्णांक __dirty(काष्ठा dm_cache_metadata *cmd, dm_cblock_t cblock, bool dirty)
अणु
	पूर्णांक r;
	अचिन्हित flags;
	dm_oblock_t oblock;
	__le64 value;

	r = dm_array_get_value(&cmd->info, cmd->root, from_cblock(cblock), &value);
	अगर (r)
		वापस r;

	unpack_value(value, &oblock, &flags);

	अगर (((flags & M_सूचीTY) && dirty) || (!(flags & M_सूचीTY) && !dirty))
		/* nothing to be करोne */
		वापस 0;

	value = pack_value(oblock, (flags & ~M_सूचीTY) | (dirty ? M_सूचीTY : 0));
	__dm_bless_क्रम_disk(&value);

	r = dm_array_set_value(&cmd->info, cmd->root, from_cblock(cblock),
			       &value, &cmd->root);
	अगर (r)
		वापस r;

	cmd->changed = true;
	वापस 0;

पूर्ण

अटल पूर्णांक __set_dirty_bits_v1(काष्ठा dm_cache_metadata *cmd, अचिन्हित nr_bits, अचिन्हित दीर्घ *bits)
अणु
	पूर्णांक r;
	अचिन्हित i;
	क्रम (i = 0; i < nr_bits; i++) अणु
		r = __dirty(cmd, to_cblock(i), test_bit(i, bits));
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is_dirty_callback(uपूर्णांक32_t index, bool *value, व्योम *context)
अणु
	अचिन्हित दीर्घ *bits = context;
	*value = test_bit(index, bits);
	वापस 0;
पूर्ण

अटल पूर्णांक __set_dirty_bits_v2(काष्ठा dm_cache_metadata *cmd, अचिन्हित nr_bits, अचिन्हित दीर्घ *bits)
अणु
	पूर्णांक r = 0;

	/* nr_bits is really just a sanity check */
	अगर (nr_bits != from_cblock(cmd->cache_blocks)) अणु
		DMERR("dirty bitset is wrong size");
		वापस -EINVAL;
	पूर्ण

	r = dm_bitset_del(&cmd->dirty_info, cmd->dirty_root);
	अगर (r)
		वापस r;

	cmd->changed = true;
	वापस dm_bitset_new(&cmd->dirty_info, &cmd->dirty_root, nr_bits, is_dirty_callback, bits);
पूर्ण

पूर्णांक dm_cache_set_dirty_bits(काष्ठा dm_cache_metadata *cmd,
			    अचिन्हित nr_bits,
			    अचिन्हित दीर्घ *bits)
अणु
	पूर्णांक r;

	WRITE_LOCK(cmd);
	अगर (separate_dirty_bits(cmd))
		r = __set_dirty_bits_v2(cmd, nr_bits, bits);
	अन्यथा
		r = __set_dirty_bits_v1(cmd, nr_bits, bits);
	WRITE_UNLOCK(cmd);

	वापस r;
पूर्ण

व्योम dm_cache_metadata_get_stats(काष्ठा dm_cache_metadata *cmd,
				 काष्ठा dm_cache_statistics *stats)
अणु
	READ_LOCK_VOID(cmd);
	*stats = cmd->stats;
	READ_UNLOCK(cmd);
पूर्ण

व्योम dm_cache_metadata_set_stats(काष्ठा dm_cache_metadata *cmd,
				 काष्ठा dm_cache_statistics *stats)
अणु
	WRITE_LOCK_VOID(cmd);
	cmd->stats = *stats;
	WRITE_UNLOCK(cmd);
पूर्ण

पूर्णांक dm_cache_commit(काष्ठा dm_cache_metadata *cmd, bool clean_shutकरोwn)
अणु
	पूर्णांक r = -EINVAL;
	flags_mutator mutator = (clean_shutकरोwn ? set_clean_shutकरोwn :
				 clear_clean_shutकरोwn);

	WRITE_LOCK(cmd);
	अगर (cmd->fail_io)
		जाओ out;

	r = __commit_transaction(cmd, mutator);
	अगर (r)
		जाओ out;

	r = __begin_transaction(cmd);
out:
	WRITE_UNLOCK(cmd);
	वापस r;
पूर्ण

पूर्णांक dm_cache_get_मुक्त_metadata_block_count(काष्ठा dm_cache_metadata *cmd,
					   dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	READ_LOCK(cmd);
	अगर (!cmd->fail_io)
		r = dm_sm_get_nr_मुक्त(cmd->metadata_sm, result);
	READ_UNLOCK(cmd);

	वापस r;
पूर्ण

पूर्णांक dm_cache_get_metadata_dev_size(काष्ठा dm_cache_metadata *cmd,
				   dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	READ_LOCK(cmd);
	अगर (!cmd->fail_io)
		r = dm_sm_get_nr_blocks(cmd->metadata_sm, result);
	READ_UNLOCK(cmd);

	वापस r;
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक get_hपूर्णांक(uपूर्णांक32_t index, व्योम *value_le, व्योम *context)
अणु
	uपूर्णांक32_t value;
	काष्ठा dm_cache_policy *policy = context;

	value = policy_get_hपूर्णांक(policy, to_cblock(index));
	*((__le32 *) value_le) = cpu_to_le32(value);

	वापस 0;
पूर्ण

/*
 * It's quicker to always delete the hपूर्णांक array, and recreate with
 * dm_array_new().
 */
अटल पूर्णांक ग_लिखो_hपूर्णांकs(काष्ठा dm_cache_metadata *cmd, काष्ठा dm_cache_policy *policy)
अणु
	पूर्णांक r;
	माप_प्रकार hपूर्णांक_size;
	स्थिर अक्षर *policy_name = dm_cache_policy_get_name(policy);
	स्थिर अचिन्हित *policy_version = dm_cache_policy_get_version(policy);

	अगर (!policy_name[0] ||
	    (म_माप(policy_name) > माप(cmd->policy_name) - 1))
		वापस -EINVAL;

	म_नकलन(cmd->policy_name, policy_name, माप(cmd->policy_name));
	स_नकल(cmd->policy_version, policy_version, माप(cmd->policy_version));

	hपूर्णांक_size = dm_cache_policy_get_hपूर्णांक_size(policy);
	अगर (!hपूर्णांक_size)
		वापस 0; /* लघु-circuit hपूर्णांकs initialization */
	cmd->policy_hपूर्णांक_size = hपूर्णांक_size;

	अगर (cmd->hपूर्णांक_root) अणु
		r = dm_array_del(&cmd->hपूर्णांक_info, cmd->hपूर्णांक_root);
		अगर (r)
			वापस r;
	पूर्ण

	वापस dm_array_new(&cmd->hपूर्णांक_info, &cmd->hपूर्णांक_root,
			    from_cblock(cmd->cache_blocks),
			    get_hपूर्णांक, policy);
पूर्ण

पूर्णांक dm_cache_ग_लिखो_hपूर्णांकs(काष्ठा dm_cache_metadata *cmd, काष्ठा dm_cache_policy *policy)
अणु
	पूर्णांक r;

	WRITE_LOCK(cmd);
	r = ग_लिखो_hपूर्णांकs(cmd, policy);
	WRITE_UNLOCK(cmd);

	वापस r;
पूर्ण

पूर्णांक dm_cache_metadata_all_clean(काष्ठा dm_cache_metadata *cmd, bool *result)
अणु
	पूर्णांक r;

	READ_LOCK(cmd);
	r = blocks_are_unmapped_or_clean(cmd, 0, cmd->cache_blocks, result);
	READ_UNLOCK(cmd);

	वापस r;
पूर्ण

व्योम dm_cache_metadata_set_पढ़ो_only(काष्ठा dm_cache_metadata *cmd)
अणु
	WRITE_LOCK_VOID(cmd);
	dm_bm_set_पढ़ो_only(cmd->bm);
	WRITE_UNLOCK(cmd);
पूर्ण

व्योम dm_cache_metadata_set_पढ़ो_ग_लिखो(काष्ठा dm_cache_metadata *cmd)
अणु
	WRITE_LOCK_VOID(cmd);
	dm_bm_set_पढ़ो_ग_लिखो(cmd->bm);
	WRITE_UNLOCK(cmd);
पूर्ण

पूर्णांक dm_cache_metadata_set_needs_check(काष्ठा dm_cache_metadata *cmd)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा cache_disk_superblock *disk_super;

	WRITE_LOCK(cmd);
	set_bit(NEEDS_CHECK, &cmd->flags);

	r = superblock_lock(cmd, &sblock);
	अगर (r) अणु
		DMERR("couldn't read superblock");
		जाओ out;
	पूर्ण

	disk_super = dm_block_data(sblock);
	disk_super->flags = cpu_to_le32(cmd->flags);

	dm_bm_unlock(sblock);

out:
	WRITE_UNLOCK(cmd);
	वापस r;
पूर्ण

पूर्णांक dm_cache_metadata_needs_check(काष्ठा dm_cache_metadata *cmd, bool *result)
अणु
	READ_LOCK(cmd);
	*result = !!test_bit(NEEDS_CHECK, &cmd->flags);
	READ_UNLOCK(cmd);

	वापस 0;
पूर्ण

पूर्णांक dm_cache_metadata_पात(काष्ठा dm_cache_metadata *cmd)
अणु
	पूर्णांक r;

	WRITE_LOCK(cmd);
	__destroy_persistent_data_objects(cmd);
	r = __create_persistent_data_objects(cmd, false);
	अगर (r)
		cmd->fail_io = true;
	WRITE_UNLOCK(cmd);

	वापस r;
पूर्ण
