<शैली गुरु>
/*
 * Copyright (C) 2011-2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-thin-metadata.h"
#समावेश "persistent-data/dm-btree.h"
#समावेश "persistent-data/dm-space-map.h"
#समावेश "persistent-data/dm-space-map-disk.h"
#समावेश "persistent-data/dm-transaction-manager.h"

#समावेश <linux/list.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/workqueue.h>

/*--------------------------------------------------------------------------
 * As far as the metadata goes, there is:
 *
 * - A superblock in block zero, taking up fewer than 512 bytes क्रम
 *   atomic ग_लिखोs.
 *
 * - A space map managing the metadata blocks.
 *
 * - A space map managing the data blocks.
 *
 * - A btree mapping our पूर्णांकernal thin dev ids onto काष्ठा disk_device_details.
 *
 * - A hierarchical btree, with 2 levels which effectively maps (thin
 *   dev id, भव block) -> block_समय.  Block समय is a 64-bit
 *   field holding the समय in the low 24 bits, and block in the top 40
 *   bits.
 *
 * BTrees consist solely of btree_nodes, that fill a block.  Some are
 * पूर्णांकernal nodes, as such their values are a __le64 poपूर्णांकing to other
 * nodes.  Leaf nodes can store data of any reasonable size (ie. much
 * smaller than the block size).  The nodes consist of the header,
 * followed by an array of keys, followed by an array of values.  We have
 * to binary search on the keys so they're all held together to help the
 * cpu cache.
 *
 * Space maps have 2 btrees:
 *
 * - One maps a uपूर्णांक64_t onto a काष्ठा index_entry.  Which poपूर्णांकs to a
 *   biपंचांगap block, and has some details about how many मुक्त entries there
 *   are etc.
 *
 * - The biपंचांगap blocks have a header (क्रम the checksum).  Then the rest
 *   of the block is pairs of bits.  With the meaning being:
 *
 *   0 - ref count is 0
 *   1 - ref count is 1
 *   2 - ref count is 2
 *   3 - ref count is higher than 2
 *
 * - If the count is higher than 2 then the ref count is entered in a
 *   second btree that directly maps the block_address to a uपूर्णांक32_t ref
 *   count.
 *
 * The space map metadata variant करोesn't have a biपंचांगaps btree.  Instead
 * it has one single blocks worth of index_entries.  This aव्योमs
 * recursive issues with the biपंचांगap btree needing to allocate space in
 * order to insert.  With a small data block size such as 64k the
 * metadata support data devices that are hundreds of terrabytes.
 *
 * The space maps allocate space linearly from front to back.  Space that
 * is मुक्तd in a transaction is never recycled within that transaction.
 * To try and aव्योम fragmenting _मुक्त_ space the allocator always goes
 * back and fills in gaps.
 *
 * All metadata io is in THIN_METADATA_BLOCK_SIZE sized/aligned chunks
 * from the block manager.
 *--------------------------------------------------------------------------*/

#घोषणा DM_MSG_PREFIX   "thin metadata"

#घोषणा THIN_SUPERBLOCK_MAGIC 27022010
#घोषणा THIN_SUPERBLOCK_LOCATION 0
#घोषणा THIN_VERSION 2
#घोषणा SECTOR_TO_BLOCK_SHIFT 3

/*
 * For btree insert:
 *  3 क्रम btree insert +
 *  2 क्रम btree lookup used within space map
 * For btree हटाओ:
 *  2 क्रम shaकरोw spine +
 *  4 क्रम rebalance 3 child node
 */
#घोषणा THIN_MAX_CONCURRENT_LOCKS 6

/* This should be plenty */
#घोषणा SPACE_MAP_ROOT_SIZE 128

/*
 * Little endian on-disk superblock and device details.
 */
काष्ठा thin_disk_superblock अणु
	__le32 csum;	/* Checksum of superblock except क्रम this field. */
	__le32 flags;
	__le64 blocknr;	/* This block number, dm_block_t. */

	__u8 uuid[16];
	__le64 magic;
	__le32 version;
	__le32 समय;

	__le64 trans_id;

	/*
	 * Root held by userspace transactions.
	 */
	__le64 held_root;

	__u8 data_space_map_root[SPACE_MAP_ROOT_SIZE];
	__u8 metadata_space_map_root[SPACE_MAP_ROOT_SIZE];

	/*
	 * 2-level btree mapping (dev_id, (dev block, समय)) -> data block
	 */
	__le64 data_mapping_root;

	/*
	 * Device detail root mapping dev_id -> device_details
	 */
	__le64 device_details_root;

	__le32 data_block_size;		/* In 512-byte sectors. */

	__le32 metadata_block_size;	/* In 512-byte sectors. */
	__le64 metadata_nr_blocks;

	__le32 compat_flags;
	__le32 compat_ro_flags;
	__le32 incompat_flags;
पूर्ण __packed;

काष्ठा disk_device_details अणु
	__le64 mapped_blocks;
	__le64 transaction_id;		/* When created. */
	__le32 creation_समय;
	__le32 snapshotted_समय;
पूर्ण __packed;

काष्ठा dm_pool_metadata अणु
	काष्ठा hlist_node hash;

	काष्ठा block_device *bdev;
	काष्ठा dm_block_manager *bm;
	काष्ठा dm_space_map *metadata_sm;
	काष्ठा dm_space_map *data_sm;
	काष्ठा dm_transaction_manager *पंचांग;
	काष्ठा dm_transaction_manager *nb_पंचांग;

	/*
	 * Two-level btree.
	 * First level holds thin_dev_t.
	 * Second level holds mappings.
	 */
	काष्ठा dm_btree_info info;

	/*
	 * Non-blocking version of the above.
	 */
	काष्ठा dm_btree_info nb_info;

	/*
	 * Just the top level क्रम deleting whole devices.
	 */
	काष्ठा dm_btree_info tl_info;

	/*
	 * Just the bottom level क्रम creating new devices.
	 */
	काष्ठा dm_btree_info bl_info;

	/*
	 * Describes the device details btree.
	 */
	काष्ठा dm_btree_info details_info;

	काष्ठा rw_semaphore root_lock;
	uपूर्णांक32_t समय;
	dm_block_t root;
	dm_block_t details_root;
	काष्ठा list_head thin_devices;
	uपूर्णांक64_t trans_id;
	अचिन्हित दीर्घ flags;
	sector_t data_block_size;

	/*
	 * Pre-commit callback.
	 *
	 * This allows the thin provisioning target to run a callback beक्रमe
	 * the metadata are committed.
	 */
	dm_pool_pre_commit_fn pre_commit_fn;
	व्योम *pre_commit_context;

	/*
	 * We reserve a section of the metadata क्रम commit overhead.
	 * All reported space करोes *not* include this.
	 */
	dm_block_t metadata_reserve;

	/*
	 * Set अगर a transaction has to be पातed but the attempt to roll back
	 * to the previous (good) transaction failed.  The only pool metadata
	 * operation possible in this state is the closing of the device.
	 */
	bool fail_io:1;

	/*
	 * Set once a thin-pool has been accessed through one of the पूर्णांकerfaces
	 * that imply the pool is in-service (e.g. thin devices created/deleted,
	 * thin-pool message, metadata snapshots, etc).
	 */
	bool in_service:1;

	/*
	 * Reading the space map roots can fail, so we पढ़ो it पूर्णांकo these
	 * buffers beक्रमe the superblock is locked and updated.
	 */
	__u8 data_space_map_root[SPACE_MAP_ROOT_SIZE];
	__u8 metadata_space_map_root[SPACE_MAP_ROOT_SIZE];
पूर्ण;

काष्ठा dm_thin_device अणु
	काष्ठा list_head list;
	काष्ठा dm_pool_metadata *pmd;
	dm_thin_id id;

	पूर्णांक खोलो_count;
	bool changed:1;
	bool पातed_with_changes:1;
	uपूर्णांक64_t mapped_blocks;
	uपूर्णांक64_t transaction_id;
	uपूर्णांक32_t creation_समय;
	uपूर्णांक32_t snapshotted_समय;
पूर्ण;

/*----------------------------------------------------------------
 * superblock validator
 *--------------------------------------------------------------*/

#घोषणा SUPERBLOCK_CSUM_XOR 160774

अटल व्योम sb_prepare_क्रम_ग_लिखो(काष्ठा dm_block_validator *v,
				 काष्ठा dm_block *b,
				 माप_प्रकार block_size)
अणु
	काष्ठा thin_disk_superblock *disk_super = dm_block_data(b);

	disk_super->blocknr = cpu_to_le64(dm_block_location(b));
	disk_super->csum = cpu_to_le32(dm_bm_checksum(&disk_super->flags,
						      block_size - माप(__le32),
						      SUPERBLOCK_CSUM_XOR));
पूर्ण

अटल पूर्णांक sb_check(काष्ठा dm_block_validator *v,
		    काष्ठा dm_block *b,
		    माप_प्रकार block_size)
अणु
	काष्ठा thin_disk_superblock *disk_super = dm_block_data(b);
	__le32 csum_le;

	अगर (dm_block_location(b) != le64_to_cpu(disk_super->blocknr)) अणु
		DMERR("sb_check failed: blocknr %llu: "
		      "wanted %llu", le64_to_cpu(disk_super->blocknr),
		      (अचिन्हित दीर्घ दीर्घ)dm_block_location(b));
		वापस -ENOTBLK;
	पूर्ण

	अगर (le64_to_cpu(disk_super->magic) != THIN_SUPERBLOCK_MAGIC) अणु
		DMERR("sb_check failed: magic %llu: "
		      "wanted %llu", le64_to_cpu(disk_super->magic),
		      (अचिन्हित दीर्घ दीर्घ)THIN_SUPERBLOCK_MAGIC);
		वापस -EILSEQ;
	पूर्ण

	csum_le = cpu_to_le32(dm_bm_checksum(&disk_super->flags,
					     block_size - माप(__le32),
					     SUPERBLOCK_CSUM_XOR));
	अगर (csum_le != disk_super->csum) अणु
		DMERR("sb_check failed: csum %u: wanted %u",
		      le32_to_cpu(csum_le), le32_to_cpu(disk_super->csum));
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dm_block_validator sb_validator = अणु
	.name = "superblock",
	.prepare_क्रम_ग_लिखो = sb_prepare_क्रम_ग_लिखो,
	.check = sb_check
पूर्ण;

/*----------------------------------------------------------------
 * Methods क्रम the btree value types
 *--------------------------------------------------------------*/

अटल uपूर्णांक64_t pack_block_समय(dm_block_t b, uपूर्णांक32_t t)
अणु
	वापस (b << 24) | t;
पूर्ण

अटल व्योम unpack_block_समय(uपूर्णांक64_t v, dm_block_t *b, uपूर्णांक32_t *t)
अणु
	*b = v >> 24;
	*t = v & ((1 << 24) - 1);
पूर्ण

अटल व्योम data_block_inc(व्योम *context, स्थिर व्योम *value_le)
अणु
	काष्ठा dm_space_map *sm = context;
	__le64 v_le;
	uपूर्णांक64_t b;
	uपूर्णांक32_t t;

	स_नकल(&v_le, value_le, माप(v_le));
	unpack_block_समय(le64_to_cpu(v_le), &b, &t);
	dm_sm_inc_block(sm, b);
पूर्ण

अटल व्योम data_block_dec(व्योम *context, स्थिर व्योम *value_le)
अणु
	काष्ठा dm_space_map *sm = context;
	__le64 v_le;
	uपूर्णांक64_t b;
	uपूर्णांक32_t t;

	स_नकल(&v_le, value_le, माप(v_le));
	unpack_block_समय(le64_to_cpu(v_le), &b, &t);
	dm_sm_dec_block(sm, b);
पूर्ण

अटल पूर्णांक data_block_equal(व्योम *context, स्थिर व्योम *value1_le, स्थिर व्योम *value2_le)
अणु
	__le64 v1_le, v2_le;
	uपूर्णांक64_t b1, b2;
	uपूर्णांक32_t t;

	स_नकल(&v1_le, value1_le, माप(v1_le));
	स_नकल(&v2_le, value2_le, माप(v2_le));
	unpack_block_समय(le64_to_cpu(v1_le), &b1, &t);
	unpack_block_समय(le64_to_cpu(v2_le), &b2, &t);

	वापस b1 == b2;
पूर्ण

अटल व्योम subtree_inc(व्योम *context, स्थिर व्योम *value)
अणु
	काष्ठा dm_btree_info *info = context;
	__le64 root_le;
	uपूर्णांक64_t root;

	स_नकल(&root_le, value, माप(root_le));
	root = le64_to_cpu(root_le);
	dm_पंचांग_inc(info->पंचांग, root);
पूर्ण

अटल व्योम subtree_dec(व्योम *context, स्थिर व्योम *value)
अणु
	काष्ठा dm_btree_info *info = context;
	__le64 root_le;
	uपूर्णांक64_t root;

	स_नकल(&root_le, value, माप(root_le));
	root = le64_to_cpu(root_le);
	अगर (dm_btree_del(info, root))
		DMERR("btree delete failed");
पूर्ण

अटल पूर्णांक subtree_equal(व्योम *context, स्थिर व्योम *value1_le, स्थिर व्योम *value2_le)
अणु
	__le64 v1_le, v2_le;
	स_नकल(&v1_le, value1_le, माप(v1_le));
	स_नकल(&v2_le, value2_le, माप(v2_le));

	वापस v1_le == v2_le;
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Variant that is used क्रम in-core only changes or code that
 * shouldn't put the pool in service on its own (e.g. commit).
 */
अटल अंतरभूत व्योम pmd_ग_लिखो_lock_in_core(काष्ठा dm_pool_metadata *pmd)
	__acquires(pmd->root_lock)
अणु
	करोwn_ग_लिखो(&pmd->root_lock);
पूर्ण

अटल अंतरभूत व्योम pmd_ग_लिखो_lock(काष्ठा dm_pool_metadata *pmd)
अणु
	pmd_ग_लिखो_lock_in_core(pmd);
	अगर (unlikely(!pmd->in_service))
		pmd->in_service = true;
पूर्ण

अटल अंतरभूत व्योम pmd_ग_लिखो_unlock(काष्ठा dm_pool_metadata *pmd)
	__releases(pmd->root_lock)
अणु
	up_ग_लिखो(&pmd->root_lock);
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक superblock_lock_zero(काष्ठा dm_pool_metadata *pmd,
				काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_ग_लिखो_lock_zero(pmd->bm, THIN_SUPERBLOCK_LOCATION,
				     &sb_validator, sblock);
पूर्ण

अटल पूर्णांक superblock_lock(काष्ठा dm_pool_metadata *pmd,
			   काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_ग_लिखो_lock(pmd->bm, THIN_SUPERBLOCK_LOCATION,
				&sb_validator, sblock);
पूर्ण

अटल पूर्णांक __superblock_all_zeroes(काष्ठा dm_block_manager *bm, पूर्णांक *result)
अणु
	पूर्णांक r;
	अचिन्हित i;
	काष्ठा dm_block *b;
	__le64 *data_le, zero = cpu_to_le64(0);
	अचिन्हित block_size = dm_bm_block_size(bm) / माप(__le64);

	/*
	 * We can't use a validator here - it may be all zeroes.
	 */
	r = dm_bm_पढ़ो_lock(bm, THIN_SUPERBLOCK_LOCATION, शून्य, &b);
	अगर (r)
		वापस r;

	data_le = dm_block_data(b);
	*result = 1;
	क्रम (i = 0; i < block_size; i++) अणु
		अगर (data_le[i] != zero) अणु
			*result = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	dm_bm_unlock(b);

	वापस 0;
पूर्ण

अटल व्योम __setup_btree_details(काष्ठा dm_pool_metadata *pmd)
अणु
	pmd->info.पंचांग = pmd->पंचांग;
	pmd->info.levels = 2;
	pmd->info.value_type.context = pmd->data_sm;
	pmd->info.value_type.size = माप(__le64);
	pmd->info.value_type.inc = data_block_inc;
	pmd->info.value_type.dec = data_block_dec;
	pmd->info.value_type.equal = data_block_equal;

	स_नकल(&pmd->nb_info, &pmd->info, माप(pmd->nb_info));
	pmd->nb_info.पंचांग = pmd->nb_पंचांग;

	pmd->tl_info.पंचांग = pmd->पंचांग;
	pmd->tl_info.levels = 1;
	pmd->tl_info.value_type.context = &pmd->bl_info;
	pmd->tl_info.value_type.size = माप(__le64);
	pmd->tl_info.value_type.inc = subtree_inc;
	pmd->tl_info.value_type.dec = subtree_dec;
	pmd->tl_info.value_type.equal = subtree_equal;

	pmd->bl_info.पंचांग = pmd->पंचांग;
	pmd->bl_info.levels = 1;
	pmd->bl_info.value_type.context = pmd->data_sm;
	pmd->bl_info.value_type.size = माप(__le64);
	pmd->bl_info.value_type.inc = data_block_inc;
	pmd->bl_info.value_type.dec = data_block_dec;
	pmd->bl_info.value_type.equal = data_block_equal;

	pmd->details_info.पंचांग = pmd->पंचांग;
	pmd->details_info.levels = 1;
	pmd->details_info.value_type.context = शून्य;
	pmd->details_info.value_type.size = माप(काष्ठा disk_device_details);
	pmd->details_info.value_type.inc = शून्य;
	pmd->details_info.value_type.dec = शून्य;
	pmd->details_info.value_type.equal = शून्य;
पूर्ण

अटल पूर्णांक save_sm_roots(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	माप_प्रकार len;

	r = dm_sm_root_size(pmd->metadata_sm, &len);
	अगर (r < 0)
		वापस r;

	r = dm_sm_copy_root(pmd->metadata_sm, &pmd->metadata_space_map_root, len);
	अगर (r < 0)
		वापस r;

	r = dm_sm_root_size(pmd->data_sm, &len);
	अगर (r < 0)
		वापस r;

	वापस dm_sm_copy_root(pmd->data_sm, &pmd->data_space_map_root, len);
पूर्ण

अटल व्योम copy_sm_roots(काष्ठा dm_pool_metadata *pmd,
			  काष्ठा thin_disk_superblock *disk)
अणु
	स_नकल(&disk->metadata_space_map_root,
	       &pmd->metadata_space_map_root,
	       माप(pmd->metadata_space_map_root));

	स_नकल(&disk->data_space_map_root,
	       &pmd->data_space_map_root,
	       माप(pmd->data_space_map_root));
पूर्ण

अटल पूर्णांक __ग_लिखो_initial_superblock(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा thin_disk_superblock *disk_super;
	sector_t bdev_size = i_size_पढ़ो(pmd->bdev->bd_inode) >> SECTOR_SHIFT;

	अगर (bdev_size > THIN_METADATA_MAX_SECTORS)
		bdev_size = THIN_METADATA_MAX_SECTORS;

	r = dm_sm_commit(pmd->data_sm);
	अगर (r < 0)
		वापस r;

	r = dm_पंचांग_pre_commit(pmd->पंचांग);
	अगर (r < 0)
		वापस r;

	r = save_sm_roots(pmd);
	अगर (r < 0)
		वापस r;

	r = superblock_lock_zero(pmd, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);
	disk_super->flags = 0;
	स_रखो(disk_super->uuid, 0, माप(disk_super->uuid));
	disk_super->magic = cpu_to_le64(THIN_SUPERBLOCK_MAGIC);
	disk_super->version = cpu_to_le32(THIN_VERSION);
	disk_super->समय = 0;
	disk_super->trans_id = 0;
	disk_super->held_root = 0;

	copy_sm_roots(pmd, disk_super);

	disk_super->data_mapping_root = cpu_to_le64(pmd->root);
	disk_super->device_details_root = cpu_to_le64(pmd->details_root);
	disk_super->metadata_block_size = cpu_to_le32(THIN_METADATA_BLOCK_SIZE);
	disk_super->metadata_nr_blocks = cpu_to_le64(bdev_size >> SECTOR_TO_BLOCK_SHIFT);
	disk_super->data_block_size = cpu_to_le32(pmd->data_block_size);

	वापस dm_पंचांग_commit(pmd->पंचांग, sblock);
पूर्ण

अटल पूर्णांक __क्रमmat_metadata(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;

	r = dm_पंचांग_create_with_sm(pmd->bm, THIN_SUPERBLOCK_LOCATION,
				 &pmd->पंचांग, &pmd->metadata_sm);
	अगर (r < 0) अणु
		DMERR("tm_create_with_sm failed");
		वापस r;
	पूर्ण

	pmd->data_sm = dm_sm_disk_create(pmd->पंचांग, 0);
	अगर (IS_ERR(pmd->data_sm)) अणु
		DMERR("sm_disk_create failed");
		r = PTR_ERR(pmd->data_sm);
		जाओ bad_cleanup_पंचांग;
	पूर्ण

	pmd->nb_पंचांग = dm_पंचांग_create_non_blocking_clone(pmd->पंचांग);
	अगर (!pmd->nb_पंचांग) अणु
		DMERR("could not create non-blocking clone tm");
		r = -ENOMEM;
		जाओ bad_cleanup_data_sm;
	पूर्ण

	__setup_btree_details(pmd);

	r = dm_btree_empty(&pmd->info, &pmd->root);
	अगर (r < 0)
		जाओ bad_cleanup_nb_पंचांग;

	r = dm_btree_empty(&pmd->details_info, &pmd->details_root);
	अगर (r < 0) अणु
		DMERR("couldn't create devices root");
		जाओ bad_cleanup_nb_पंचांग;
	पूर्ण

	r = __ग_लिखो_initial_superblock(pmd);
	अगर (r)
		जाओ bad_cleanup_nb_पंचांग;

	वापस 0;

bad_cleanup_nb_पंचांग:
	dm_पंचांग_destroy(pmd->nb_पंचांग);
bad_cleanup_data_sm:
	dm_sm_destroy(pmd->data_sm);
bad_cleanup_पंचांग:
	dm_पंचांग_destroy(pmd->पंचांग);
	dm_sm_destroy(pmd->metadata_sm);

	वापस r;
पूर्ण

अटल पूर्णांक __check_incompat_features(काष्ठा thin_disk_superblock *disk_super,
				     काष्ठा dm_pool_metadata *pmd)
अणु
	uपूर्णांक32_t features;

	features = le32_to_cpu(disk_super->incompat_flags) & ~THIN_FEATURE_INCOMPAT_SUPP;
	अगर (features) अणु
		DMERR("could not access metadata due to unsupported optional features (%lx).",
		      (अचिन्हित दीर्घ)features);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check क्रम पढ़ो-only metadata to skip the following RDWR checks.
	 */
	अगर (bdev_पढ़ो_only(pmd->bdev))
		वापस 0;

	features = le32_to_cpu(disk_super->compat_ro_flags) & ~THIN_FEATURE_COMPAT_RO_SUPP;
	अगर (features) अणु
		DMERR("could not access metadata RDWR due to unsupported optional features (%lx).",
		      (अचिन्हित दीर्घ)features);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __खोलो_metadata(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा thin_disk_superblock *disk_super;

	r = dm_bm_पढ़ो_lock(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			    &sb_validator, &sblock);
	अगर (r < 0) अणु
		DMERR("couldn't read superblock");
		वापस r;
	पूर्ण

	disk_super = dm_block_data(sblock);

	/* Verअगरy the data block size hasn't changed */
	अगर (le32_to_cpu(disk_super->data_block_size) != pmd->data_block_size) अणु
		DMERR("changing the data block size (from %u to %llu) is not supported",
		      le32_to_cpu(disk_super->data_block_size),
		      (अचिन्हित दीर्घ दीर्घ)pmd->data_block_size);
		r = -EINVAL;
		जाओ bad_unlock_sblock;
	पूर्ण

	r = __check_incompat_features(disk_super, pmd);
	अगर (r < 0)
		जाओ bad_unlock_sblock;

	r = dm_पंचांग_खोलो_with_sm(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			       disk_super->metadata_space_map_root,
			       माप(disk_super->metadata_space_map_root),
			       &pmd->पंचांग, &pmd->metadata_sm);
	अगर (r < 0) अणु
		DMERR("tm_open_with_sm failed");
		जाओ bad_unlock_sblock;
	पूर्ण

	pmd->data_sm = dm_sm_disk_खोलो(pmd->पंचांग, disk_super->data_space_map_root,
				       माप(disk_super->data_space_map_root));
	अगर (IS_ERR(pmd->data_sm)) अणु
		DMERR("sm_disk_open failed");
		r = PTR_ERR(pmd->data_sm);
		जाओ bad_cleanup_पंचांग;
	पूर्ण

	pmd->nb_पंचांग = dm_पंचांग_create_non_blocking_clone(pmd->पंचांग);
	अगर (!pmd->nb_पंचांग) अणु
		DMERR("could not create non-blocking clone tm");
		r = -ENOMEM;
		जाओ bad_cleanup_data_sm;
	पूर्ण

	__setup_btree_details(pmd);
	dm_bm_unlock(sblock);

	वापस 0;

bad_cleanup_data_sm:
	dm_sm_destroy(pmd->data_sm);
bad_cleanup_पंचांग:
	dm_पंचांग_destroy(pmd->पंचांग);
	dm_sm_destroy(pmd->metadata_sm);
bad_unlock_sblock:
	dm_bm_unlock(sblock);

	वापस r;
पूर्ण

अटल पूर्णांक __खोलो_or_क्रमmat_metadata(काष्ठा dm_pool_metadata *pmd, bool क्रमmat_device)
अणु
	पूर्णांक r, unक्रमmatted;

	r = __superblock_all_zeroes(pmd->bm, &unक्रमmatted);
	अगर (r)
		वापस r;

	अगर (unक्रमmatted)
		वापस क्रमmat_device ? __क्रमmat_metadata(pmd) : -EPERM;

	वापस __खोलो_metadata(pmd);
पूर्ण

अटल पूर्णांक __create_persistent_data_objects(काष्ठा dm_pool_metadata *pmd, bool क्रमmat_device)
अणु
	पूर्णांक r;

	pmd->bm = dm_block_manager_create(pmd->bdev, THIN_METADATA_BLOCK_SIZE << SECTOR_SHIFT,
					  THIN_MAX_CONCURRENT_LOCKS);
	अगर (IS_ERR(pmd->bm)) अणु
		DMERR("could not create block manager");
		r = PTR_ERR(pmd->bm);
		pmd->bm = शून्य;
		वापस r;
	पूर्ण

	r = __खोलो_or_क्रमmat_metadata(pmd, क्रमmat_device);
	अगर (r) अणु
		dm_block_manager_destroy(pmd->bm);
		pmd->bm = शून्य;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम __destroy_persistent_data_objects(काष्ठा dm_pool_metadata *pmd)
अणु
	dm_sm_destroy(pmd->data_sm);
	dm_sm_destroy(pmd->metadata_sm);
	dm_पंचांग_destroy(pmd->nb_पंचांग);
	dm_पंचांग_destroy(pmd->पंचांग);
	dm_block_manager_destroy(pmd->bm);
पूर्ण

अटल पूर्णांक __begin_transaction(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	काष्ठा thin_disk_superblock *disk_super;
	काष्ठा dm_block *sblock;

	/*
	 * We re-पढ़ो the superblock every समय.  Shouldn't need to करो this
	 * really.
	 */
	r = dm_bm_पढ़ो_lock(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			    &sb_validator, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);
	pmd->समय = le32_to_cpu(disk_super->समय);
	pmd->root = le64_to_cpu(disk_super->data_mapping_root);
	pmd->details_root = le64_to_cpu(disk_super->device_details_root);
	pmd->trans_id = le64_to_cpu(disk_super->trans_id);
	pmd->flags = le32_to_cpu(disk_super->flags);
	pmd->data_block_size = le32_to_cpu(disk_super->data_block_size);

	dm_bm_unlock(sblock);
	वापस 0;
पूर्ण

अटल पूर्णांक __ग_लिखो_changed_details(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	काष्ठा dm_thin_device *td, *पंचांगp;
	काष्ठा disk_device_details details;
	uपूर्णांक64_t key;

	list_क्रम_each_entry_safe(td, पंचांगp, &pmd->thin_devices, list) अणु
		अगर (!td->changed)
			जारी;

		key = td->id;

		details.mapped_blocks = cpu_to_le64(td->mapped_blocks);
		details.transaction_id = cpu_to_le64(td->transaction_id);
		details.creation_समय = cpu_to_le32(td->creation_समय);
		details.snapshotted_समय = cpu_to_le32(td->snapshotted_समय);
		__dm_bless_क्रम_disk(&details);

		r = dm_btree_insert(&pmd->details_info, pmd->details_root,
				    &key, &details, &pmd->details_root);
		अगर (r)
			वापस r;

		अगर (td->खोलो_count)
			td->changed = false;
		अन्यथा अणु
			list_del(&td->list);
			kमुक्त(td);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __commit_transaction(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	काष्ठा thin_disk_superblock *disk_super;
	काष्ठा dm_block *sblock;

	/*
	 * We need to know अगर the thin_disk_superblock exceeds a 512-byte sector.
	 */
	BUILD_BUG_ON(माप(काष्ठा thin_disk_superblock) > 512);
	BUG_ON(!rwsem_is_locked(&pmd->root_lock));

	अगर (unlikely(!pmd->in_service))
		वापस 0;

	अगर (pmd->pre_commit_fn) अणु
		r = pmd->pre_commit_fn(pmd->pre_commit_context);
		अगर (r < 0) अणु
			DMERR("pre-commit callback failed");
			वापस r;
		पूर्ण
	पूर्ण

	r = __ग_लिखो_changed_details(pmd);
	अगर (r < 0)
		वापस r;

	r = dm_sm_commit(pmd->data_sm);
	अगर (r < 0)
		वापस r;

	r = dm_पंचांग_pre_commit(pmd->पंचांग);
	अगर (r < 0)
		वापस r;

	r = save_sm_roots(pmd);
	अगर (r < 0)
		वापस r;

	r = superblock_lock(pmd, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);
	disk_super->समय = cpu_to_le32(pmd->समय);
	disk_super->data_mapping_root = cpu_to_le64(pmd->root);
	disk_super->device_details_root = cpu_to_le64(pmd->details_root);
	disk_super->trans_id = cpu_to_le64(pmd->trans_id);
	disk_super->flags = cpu_to_le32(pmd->flags);

	copy_sm_roots(pmd, disk_super);

	वापस dm_पंचांग_commit(pmd->पंचांग, sblock);
पूर्ण

अटल व्योम __set_metadata_reserve(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	dm_block_t total;
	dm_block_t max_blocks = 4096; /* 16M */

	r = dm_sm_get_nr_blocks(pmd->metadata_sm, &total);
	अगर (r) अणु
		DMERR("could not get size of metadata device");
		pmd->metadata_reserve = max_blocks;
	पूर्ण अन्यथा
		pmd->metadata_reserve = min(max_blocks, भाग_u64(total, 10));
पूर्ण

काष्ठा dm_pool_metadata *dm_pool_metadata_खोलो(काष्ठा block_device *bdev,
					       sector_t data_block_size,
					       bool क्रमmat_device)
अणु
	पूर्णांक r;
	काष्ठा dm_pool_metadata *pmd;

	pmd = kदो_स्मृति(माप(*pmd), GFP_KERNEL);
	अगर (!pmd) अणु
		DMERR("could not allocate metadata struct");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	init_rwsem(&pmd->root_lock);
	pmd->समय = 0;
	INIT_LIST_HEAD(&pmd->thin_devices);
	pmd->fail_io = false;
	pmd->in_service = false;
	pmd->bdev = bdev;
	pmd->data_block_size = data_block_size;
	pmd->pre_commit_fn = शून्य;
	pmd->pre_commit_context = शून्य;

	r = __create_persistent_data_objects(pmd, क्रमmat_device);
	अगर (r) अणु
		kमुक्त(pmd);
		वापस ERR_PTR(r);
	पूर्ण

	r = __begin_transaction(pmd);
	अगर (r < 0) अणु
		अगर (dm_pool_metadata_बंद(pmd) < 0)
			DMWARN("%s: dm_pool_metadata_close() failed.", __func__);
		वापस ERR_PTR(r);
	पूर्ण

	__set_metadata_reserve(pmd);

	वापस pmd;
पूर्ण

पूर्णांक dm_pool_metadata_बंद(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	अचिन्हित खोलो_devices = 0;
	काष्ठा dm_thin_device *td, *पंचांगp;

	करोwn_पढ़ो(&pmd->root_lock);
	list_क्रम_each_entry_safe(td, पंचांगp, &pmd->thin_devices, list) अणु
		अगर (td->खोलो_count)
			खोलो_devices++;
		अन्यथा अणु
			list_del(&td->list);
			kमुक्त(td);
		पूर्ण
	पूर्ण
	up_पढ़ो(&pmd->root_lock);

	अगर (खोलो_devices) अणु
		DMERR("attempt to close pmd when %u device(s) are still open",
		       खोलो_devices);
		वापस -EBUSY;
	पूर्ण

	pmd_ग_लिखो_lock_in_core(pmd);
	अगर (!pmd->fail_io && !dm_bm_is_पढ़ो_only(pmd->bm)) अणु
		r = __commit_transaction(pmd);
		अगर (r < 0)
			DMWARN("%s: __commit_transaction() failed, error = %d",
			       __func__, r);
	पूर्ण
	pmd_ग_लिखो_unlock(pmd);
	अगर (!pmd->fail_io)
		__destroy_persistent_data_objects(pmd);

	kमुक्त(pmd);
	वापस 0;
पूर्ण

/*
 * __खोलो_device: Returns @td corresponding to device with id @dev,
 * creating it अगर @create is set and incrementing @td->खोलो_count.
 * On failure, @td is undefined.
 */
अटल पूर्णांक __खोलो_device(काष्ठा dm_pool_metadata *pmd,
			 dm_thin_id dev, पूर्णांक create,
			 काष्ठा dm_thin_device **td)
अणु
	पूर्णांक r, changed = 0;
	काष्ठा dm_thin_device *td2;
	uपूर्णांक64_t key = dev;
	काष्ठा disk_device_details details_le;

	/*
	 * If the device is alपढ़ोy खोलो, वापस it.
	 */
	list_क्रम_each_entry(td2, &pmd->thin_devices, list)
		अगर (td2->id == dev) अणु
			/*
			 * May not create an alपढ़ोy-खोलो device.
			 */
			अगर (create)
				वापस -EEXIST;

			td2->खोलो_count++;
			*td = td2;
			वापस 0;
		पूर्ण

	/*
	 * Check the device exists.
	 */
	r = dm_btree_lookup(&pmd->details_info, pmd->details_root,
			    &key, &details_le);
	अगर (r) अणु
		अगर (r != -ENODATA || !create)
			वापस r;

		/*
		 * Create new device.
		 */
		changed = 1;
		details_le.mapped_blocks = 0;
		details_le.transaction_id = cpu_to_le64(pmd->trans_id);
		details_le.creation_समय = cpu_to_le32(pmd->समय);
		details_le.snapshotted_समय = cpu_to_le32(pmd->समय);
	पूर्ण

	*td = kदो_स्मृति(माप(**td), GFP_NOIO);
	अगर (!*td)
		वापस -ENOMEM;

	(*td)->pmd = pmd;
	(*td)->id = dev;
	(*td)->खोलो_count = 1;
	(*td)->changed = changed;
	(*td)->पातed_with_changes = false;
	(*td)->mapped_blocks = le64_to_cpu(details_le.mapped_blocks);
	(*td)->transaction_id = le64_to_cpu(details_le.transaction_id);
	(*td)->creation_समय = le32_to_cpu(details_le.creation_समय);
	(*td)->snapshotted_समय = le32_to_cpu(details_le.snapshotted_समय);

	list_add(&(*td)->list, &pmd->thin_devices);

	वापस 0;
पूर्ण

अटल व्योम __बंद_device(काष्ठा dm_thin_device *td)
अणु
	--td->खोलो_count;
पूर्ण

अटल पूर्णांक __create_thin(काष्ठा dm_pool_metadata *pmd,
			 dm_thin_id dev)
अणु
	पूर्णांक r;
	dm_block_t dev_root;
	uपूर्णांक64_t key = dev;
	काष्ठा dm_thin_device *td;
	__le64 value;

	r = dm_btree_lookup(&pmd->details_info, pmd->details_root,
			    &key, शून्य);
	अगर (!r)
		वापस -EEXIST;

	/*
	 * Create an empty btree क्रम the mappings.
	 */
	r = dm_btree_empty(&pmd->bl_info, &dev_root);
	अगर (r)
		वापस r;

	/*
	 * Insert it पूर्णांकo the मुख्य mapping tree.
	 */
	value = cpu_to_le64(dev_root);
	__dm_bless_क्रम_disk(&value);
	r = dm_btree_insert(&pmd->tl_info, pmd->root, &key, &value, &pmd->root);
	अगर (r) अणु
		dm_btree_del(&pmd->bl_info, dev_root);
		वापस r;
	पूर्ण

	r = __खोलो_device(pmd, dev, 1, &td);
	अगर (r) अणु
		dm_btree_हटाओ(&pmd->tl_info, pmd->root, &key, &pmd->root);
		dm_btree_del(&pmd->bl_info, dev_root);
		वापस r;
	पूर्ण
	__बंद_device(td);

	वापस r;
पूर्ण

पूर्णांक dm_pool_create_thin(काष्ठा dm_pool_metadata *pmd, dm_thin_id dev)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (!pmd->fail_io)
		r = __create_thin(pmd, dev);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

अटल पूर्णांक __set_snapshot_details(काष्ठा dm_pool_metadata *pmd,
				  काष्ठा dm_thin_device *snap,
				  dm_thin_id origin, uपूर्णांक32_t समय)
अणु
	पूर्णांक r;
	काष्ठा dm_thin_device *td;

	r = __खोलो_device(pmd, origin, 0, &td);
	अगर (r)
		वापस r;

	td->changed = true;
	td->snapshotted_समय = समय;

	snap->mapped_blocks = td->mapped_blocks;
	snap->snapshotted_समय = समय;
	__बंद_device(td);

	वापस 0;
पूर्ण

अटल पूर्णांक __create_snap(काष्ठा dm_pool_metadata *pmd,
			 dm_thin_id dev, dm_thin_id origin)
अणु
	पूर्णांक r;
	dm_block_t origin_root;
	uपूर्णांक64_t key = origin, dev_key = dev;
	काष्ठा dm_thin_device *td;
	__le64 value;

	/* check this device is unused */
	r = dm_btree_lookup(&pmd->details_info, pmd->details_root,
			    &dev_key, शून्य);
	अगर (!r)
		वापस -EEXIST;

	/* find the mapping tree क्रम the origin */
	r = dm_btree_lookup(&pmd->tl_info, pmd->root, &key, &value);
	अगर (r)
		वापस r;
	origin_root = le64_to_cpu(value);

	/* clone the origin, an inc will करो */
	dm_पंचांग_inc(pmd->पंचांग, origin_root);

	/* insert पूर्णांकo the मुख्य mapping tree */
	value = cpu_to_le64(origin_root);
	__dm_bless_क्रम_disk(&value);
	key = dev;
	r = dm_btree_insert(&pmd->tl_info, pmd->root, &key, &value, &pmd->root);
	अगर (r) अणु
		dm_पंचांग_dec(pmd->पंचांग, origin_root);
		वापस r;
	पूर्ण

	pmd->समय++;

	r = __खोलो_device(pmd, dev, 1, &td);
	अगर (r)
		जाओ bad;

	r = __set_snapshot_details(pmd, td, origin, pmd->समय);
	__बंद_device(td);

	अगर (r)
		जाओ bad;

	वापस 0;

bad:
	dm_btree_हटाओ(&pmd->tl_info, pmd->root, &key, &pmd->root);
	dm_btree_हटाओ(&pmd->details_info, pmd->details_root,
			&key, &pmd->details_root);
	वापस r;
पूर्ण

पूर्णांक dm_pool_create_snap(काष्ठा dm_pool_metadata *pmd,
				 dm_thin_id dev,
				 dm_thin_id origin)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (!pmd->fail_io)
		r = __create_snap(pmd, dev, origin);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

अटल पूर्णांक __delete_device(काष्ठा dm_pool_metadata *pmd, dm_thin_id dev)
अणु
	पूर्णांक r;
	uपूर्णांक64_t key = dev;
	काष्ठा dm_thin_device *td;

	/* TODO: failure should mark the transaction invalid */
	r = __खोलो_device(pmd, dev, 0, &td);
	अगर (r)
		वापस r;

	अगर (td->खोलो_count > 1) अणु
		__बंद_device(td);
		वापस -EBUSY;
	पूर्ण

	list_del(&td->list);
	kमुक्त(td);
	r = dm_btree_हटाओ(&pmd->details_info, pmd->details_root,
			    &key, &pmd->details_root);
	अगर (r)
		वापस r;

	r = dm_btree_हटाओ(&pmd->tl_info, pmd->root, &key, &pmd->root);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

पूर्णांक dm_pool_delete_thin_device(काष्ठा dm_pool_metadata *pmd,
			       dm_thin_id dev)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (!pmd->fail_io)
		r = __delete_device(pmd, dev);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

पूर्णांक dm_pool_set_metadata_transaction_id(काष्ठा dm_pool_metadata *pmd,
					uपूर्णांक64_t current_id,
					uपूर्णांक64_t new_id)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);

	अगर (pmd->fail_io)
		जाओ out;

	अगर (pmd->trans_id != current_id) अणु
		DMERR("mismatched transaction id");
		जाओ out;
	पूर्ण

	pmd->trans_id = new_id;
	r = 0;

out:
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

पूर्णांक dm_pool_get_metadata_transaction_id(काष्ठा dm_pool_metadata *pmd,
					uपूर्णांक64_t *result)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io) अणु
		*result = pmd->trans_id;
		r = 0;
	पूर्ण
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

अटल पूर्णांक __reserve_metadata_snap(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r, inc;
	काष्ठा thin_disk_superblock *disk_super;
	काष्ठा dm_block *copy, *sblock;
	dm_block_t held_root;

	/*
	 * We commit to ensure the btree roots which we increment in a
	 * moment are up to date.
	 */
	r = __commit_transaction(pmd);
	अगर (r < 0) अणु
		DMWARN("%s: __commit_transaction() failed, error = %d",
		       __func__, r);
		वापस r;
	पूर्ण

	/*
	 * Copy the superblock.
	 */
	dm_sm_inc_block(pmd->metadata_sm, THIN_SUPERBLOCK_LOCATION);
	r = dm_पंचांग_shaकरोw_block(pmd->पंचांग, THIN_SUPERBLOCK_LOCATION,
			       &sb_validator, &copy, &inc);
	अगर (r)
		वापस r;

	BUG_ON(!inc);

	held_root = dm_block_location(copy);
	disk_super = dm_block_data(copy);

	अगर (le64_to_cpu(disk_super->held_root)) अणु
		DMWARN("Pool metadata snapshot already exists: release this before taking another.");

		dm_पंचांग_dec(pmd->पंचांग, held_root);
		dm_पंचांग_unlock(pmd->पंचांग, copy);
		वापस -EBUSY;
	पूर्ण

	/*
	 * Wipe the spacemap since we're not publishing this.
	 */
	स_रखो(&disk_super->data_space_map_root, 0,
	       माप(disk_super->data_space_map_root));
	स_रखो(&disk_super->metadata_space_map_root, 0,
	       माप(disk_super->metadata_space_map_root));

	/*
	 * Increment the data काष्ठाures that need to be preserved.
	 */
	dm_पंचांग_inc(pmd->पंचांग, le64_to_cpu(disk_super->data_mapping_root));
	dm_पंचांग_inc(pmd->पंचांग, le64_to_cpu(disk_super->device_details_root));
	dm_पंचांग_unlock(pmd->पंचांग, copy);

	/*
	 * Write the held root पूर्णांकo the superblock.
	 */
	r = superblock_lock(pmd, &sblock);
	अगर (r) अणु
		dm_पंचांग_dec(pmd->पंचांग, held_root);
		वापस r;
	पूर्ण

	disk_super = dm_block_data(sblock);
	disk_super->held_root = cpu_to_le64(held_root);
	dm_bm_unlock(sblock);
	वापस 0;
पूर्ण

पूर्णांक dm_pool_reserve_metadata_snap(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (!pmd->fail_io)
		r = __reserve_metadata_snap(pmd);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

अटल पूर्णांक __release_metadata_snap(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r;
	काष्ठा thin_disk_superblock *disk_super;
	काष्ठा dm_block *sblock, *copy;
	dm_block_t held_root;

	r = superblock_lock(pmd, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);
	held_root = le64_to_cpu(disk_super->held_root);
	disk_super->held_root = cpu_to_le64(0);

	dm_bm_unlock(sblock);

	अगर (!held_root) अणु
		DMWARN("No pool metadata snapshot found: nothing to release.");
		वापस -EINVAL;
	पूर्ण

	r = dm_पंचांग_पढ़ो_lock(pmd->पंचांग, held_root, &sb_validator, &copy);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(copy);
	dm_btree_del(&pmd->info, le64_to_cpu(disk_super->data_mapping_root));
	dm_btree_del(&pmd->details_info, le64_to_cpu(disk_super->device_details_root));
	dm_sm_dec_block(pmd->metadata_sm, held_root);

	dm_पंचांग_unlock(pmd->पंचांग, copy);

	वापस 0;
पूर्ण

पूर्णांक dm_pool_release_metadata_snap(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (!pmd->fail_io)
		r = __release_metadata_snap(pmd);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

अटल पूर्णांक __get_metadata_snap(काष्ठा dm_pool_metadata *pmd,
			       dm_block_t *result)
अणु
	पूर्णांक r;
	काष्ठा thin_disk_superblock *disk_super;
	काष्ठा dm_block *sblock;

	r = dm_bm_पढ़ो_lock(pmd->bm, THIN_SUPERBLOCK_LOCATION,
			    &sb_validator, &sblock);
	अगर (r)
		वापस r;

	disk_super = dm_block_data(sblock);
	*result = le64_to_cpu(disk_super->held_root);

	dm_bm_unlock(sblock);

	वापस 0;
पूर्ण

पूर्णांक dm_pool_get_metadata_snap(काष्ठा dm_pool_metadata *pmd,
			      dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io)
		r = __get_metadata_snap(pmd, result);
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

पूर्णांक dm_pool_खोलो_thin_device(काष्ठा dm_pool_metadata *pmd, dm_thin_id dev,
			     काष्ठा dm_thin_device **td)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock_in_core(pmd);
	अगर (!pmd->fail_io)
		r = __खोलो_device(pmd, dev, 0, td);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

पूर्णांक dm_pool_बंद_thin_device(काष्ठा dm_thin_device *td)
अणु
	pmd_ग_लिखो_lock_in_core(td->pmd);
	__बंद_device(td);
	pmd_ग_लिखो_unlock(td->pmd);

	वापस 0;
पूर्ण

dm_thin_id dm_thin_dev_id(काष्ठा dm_thin_device *td)
अणु
	वापस td->id;
पूर्ण

/*
 * Check whether @समय (of block creation) is older than @td's last snapshot.
 * If so then the associated block is shared with the last snapshot device.
 * Any block on a device created *after* the device last got snapshotted is
 * necessarily not shared.
 */
अटल bool __snapshotted_since(काष्ठा dm_thin_device *td, uपूर्णांक32_t समय)
अणु
	वापस td->snapshotted_समय > समय;
पूर्ण

अटल व्योम unpack_lookup_result(काष्ठा dm_thin_device *td, __le64 value,
				 काष्ठा dm_thin_lookup_result *result)
अणु
	uपूर्णांक64_t block_समय = 0;
	dm_block_t exception_block;
	uपूर्णांक32_t exception_समय;

	block_समय = le64_to_cpu(value);
	unpack_block_समय(block_समय, &exception_block, &exception_समय);
	result->block = exception_block;
	result->shared = __snapshotted_since(td, exception_समय);
पूर्ण

अटल पूर्णांक __find_block(काष्ठा dm_thin_device *td, dm_block_t block,
			पूर्णांक can_issue_io, काष्ठा dm_thin_lookup_result *result)
अणु
	पूर्णांक r;
	__le64 value;
	काष्ठा dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = अणु td->id, block पूर्ण;
	काष्ठा dm_btree_info *info;

	अगर (can_issue_io) अणु
		info = &pmd->info;
	पूर्ण अन्यथा
		info = &pmd->nb_info;

	r = dm_btree_lookup(info, pmd->root, keys, &value);
	अगर (!r)
		unpack_lookup_result(td, value, result);

	वापस r;
पूर्ण

पूर्णांक dm_thin_find_block(काष्ठा dm_thin_device *td, dm_block_t block,
		       पूर्णांक can_issue_io, काष्ठा dm_thin_lookup_result *result)
अणु
	पूर्णांक r;
	काष्ठा dm_pool_metadata *pmd = td->pmd;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (pmd->fail_io) अणु
		up_पढ़ो(&pmd->root_lock);
		वापस -EINVAL;
	पूर्ण

	r = __find_block(td, block, can_issue_io, result);

	up_पढ़ो(&pmd->root_lock);
	वापस r;
पूर्ण

अटल पूर्णांक __find_next_mapped_block(काष्ठा dm_thin_device *td, dm_block_t block,
					  dm_block_t *vblock,
					  काष्ठा dm_thin_lookup_result *result)
अणु
	पूर्णांक r;
	__le64 value;
	काष्ठा dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = अणु td->id, block पूर्ण;

	r = dm_btree_lookup_next(&pmd->info, pmd->root, keys, vblock, &value);
	अगर (!r)
		unpack_lookup_result(td, value, result);

	वापस r;
पूर्ण

अटल पूर्णांक __find_mapped_range(काष्ठा dm_thin_device *td,
			       dm_block_t begin, dm_block_t end,
			       dm_block_t *thin_begin, dm_block_t *thin_end,
			       dm_block_t *pool_begin, bool *maybe_shared)
अणु
	पूर्णांक r;
	dm_block_t pool_end;
	काष्ठा dm_thin_lookup_result lookup;

	अगर (end < begin)
		वापस -ENODATA;

	r = __find_next_mapped_block(td, begin, &begin, &lookup);
	अगर (r)
		वापस r;

	अगर (begin >= end)
		वापस -ENODATA;

	*thin_begin = begin;
	*pool_begin = lookup.block;
	*maybe_shared = lookup.shared;

	begin++;
	pool_end = *pool_begin + 1;
	जबतक (begin != end) अणु
		r = __find_block(td, begin, true, &lookup);
		अगर (r) अणु
			अगर (r == -ENODATA)
				अवरोध;
			अन्यथा
				वापस r;
		पूर्ण

		अगर ((lookup.block != pool_end) ||
		    (lookup.shared != *maybe_shared))
			अवरोध;

		pool_end++;
		begin++;
	पूर्ण

	*thin_end = begin;
	वापस 0;
पूर्ण

पूर्णांक dm_thin_find_mapped_range(काष्ठा dm_thin_device *td,
			      dm_block_t begin, dm_block_t end,
			      dm_block_t *thin_begin, dm_block_t *thin_end,
			      dm_block_t *pool_begin, bool *maybe_shared)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा dm_pool_metadata *pmd = td->pmd;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io) अणु
		r = __find_mapped_range(td, begin, end, thin_begin, thin_end,
					pool_begin, maybe_shared);
	पूर्ण
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

अटल पूर्णांक __insert(काष्ठा dm_thin_device *td, dm_block_t block,
		    dm_block_t data_block)
अणु
	पूर्णांक r, inserted;
	__le64 value;
	काष्ठा dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = अणु td->id, block पूर्ण;

	value = cpu_to_le64(pack_block_समय(data_block, pmd->समय));
	__dm_bless_क्रम_disk(&value);

	r = dm_btree_insert_notअगरy(&pmd->info, pmd->root, keys, &value,
				   &pmd->root, &inserted);
	अगर (r)
		वापस r;

	td->changed = true;
	अगर (inserted)
		td->mapped_blocks++;

	वापस 0;
पूर्ण

पूर्णांक dm_thin_insert_block(काष्ठा dm_thin_device *td, dm_block_t block,
			 dm_block_t data_block)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(td->pmd);
	अगर (!td->pmd->fail_io)
		r = __insert(td, block, data_block);
	pmd_ग_लिखो_unlock(td->pmd);

	वापस r;
पूर्ण

अटल पूर्णांक __हटाओ(काष्ठा dm_thin_device *td, dm_block_t block)
अणु
	पूर्णांक r;
	काष्ठा dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = अणु td->id, block पूर्ण;

	r = dm_btree_हटाओ(&pmd->info, pmd->root, keys, &pmd->root);
	अगर (r)
		वापस r;

	td->mapped_blocks--;
	td->changed = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __हटाओ_range(काष्ठा dm_thin_device *td, dm_block_t begin, dm_block_t end)
अणु
	पूर्णांक r;
	अचिन्हित count, total_count = 0;
	काष्ठा dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[1] = अणु td->id पूर्ण;
	__le64 value;
	dm_block_t mapping_root;

	/*
	 * Find the mapping tree
	 */
	r = dm_btree_lookup(&pmd->tl_info, pmd->root, keys, &value);
	अगर (r)
		वापस r;

	/*
	 * Remove from the mapping tree, taking care to inc the
	 * ref count so it करोesn't get deleted.
	 */
	mapping_root = le64_to_cpu(value);
	dm_पंचांग_inc(pmd->पंचांग, mapping_root);
	r = dm_btree_हटाओ(&pmd->tl_info, pmd->root, keys, &pmd->root);
	अगर (r)
		वापस r;

	/*
	 * Remove leaves stops at the first unmapped entry, so we have to
	 * loop round finding mapped ranges.
	 */
	जबतक (begin < end) अणु
		r = dm_btree_lookup_next(&pmd->bl_info, mapping_root, &begin, &begin, &value);
		अगर (r == -ENODATA)
			अवरोध;

		अगर (r)
			वापस r;

		अगर (begin >= end)
			अवरोध;

		r = dm_btree_हटाओ_leaves(&pmd->bl_info, mapping_root, &begin, end, &mapping_root, &count);
		अगर (r)
			वापस r;

		total_count += count;
	पूर्ण

	td->mapped_blocks -= total_count;
	td->changed = true;

	/*
	 * Reinsert the mapping tree.
	 */
	value = cpu_to_le64(mapping_root);
	__dm_bless_क्रम_disk(&value);
	वापस dm_btree_insert(&pmd->tl_info, pmd->root, keys, &value, &pmd->root);
पूर्ण

पूर्णांक dm_thin_हटाओ_block(काष्ठा dm_thin_device *td, dm_block_t block)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(td->pmd);
	अगर (!td->pmd->fail_io)
		r = __हटाओ(td, block);
	pmd_ग_लिखो_unlock(td->pmd);

	वापस r;
पूर्ण

पूर्णांक dm_thin_हटाओ_range(काष्ठा dm_thin_device *td,
			 dm_block_t begin, dm_block_t end)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(td->pmd);
	अगर (!td->pmd->fail_io)
		r = __हटाओ_range(td, begin, end);
	pmd_ग_लिखो_unlock(td->pmd);

	वापस r;
पूर्ण

पूर्णांक dm_pool_block_is_shared(काष्ठा dm_pool_metadata *pmd, dm_block_t b, bool *result)
अणु
	पूर्णांक r;
	uपूर्णांक32_t ref_count;

	करोwn_पढ़ो(&pmd->root_lock);
	r = dm_sm_get_count(pmd->data_sm, b, &ref_count);
	अगर (!r)
		*result = (ref_count > 1);
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

पूर्णांक dm_pool_inc_data_range(काष्ठा dm_pool_metadata *pmd, dm_block_t b, dm_block_t e)
अणु
	पूर्णांक r = 0;

	pmd_ग_लिखो_lock(pmd);
	क्रम (; b != e; b++) अणु
		r = dm_sm_inc_block(pmd->data_sm, b);
		अगर (r)
			अवरोध;
	पूर्ण
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

पूर्णांक dm_pool_dec_data_range(काष्ठा dm_pool_metadata *pmd, dm_block_t b, dm_block_t e)
अणु
	पूर्णांक r = 0;

	pmd_ग_लिखो_lock(pmd);
	क्रम (; b != e; b++) अणु
		r = dm_sm_dec_block(pmd->data_sm, b);
		अगर (r)
			अवरोध;
	पूर्ण
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

bool dm_thin_changed_this_transaction(काष्ठा dm_thin_device *td)
अणु
	पूर्णांक r;

	करोwn_पढ़ो(&td->pmd->root_lock);
	r = td->changed;
	up_पढ़ो(&td->pmd->root_lock);

	वापस r;
पूर्ण

bool dm_pool_changed_this_transaction(काष्ठा dm_pool_metadata *pmd)
अणु
	bool r = false;
	काष्ठा dm_thin_device *td, *पंचांगp;

	करोwn_पढ़ो(&pmd->root_lock);
	list_क्रम_each_entry_safe(td, पंचांगp, &pmd->thin_devices, list) अणु
		अगर (td->changed) अणु
			r = td->changed;
			अवरोध;
		पूर्ण
	पूर्ण
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

bool dm_thin_पातed_changes(काष्ठा dm_thin_device *td)
अणु
	bool r;

	करोwn_पढ़ो(&td->pmd->root_lock);
	r = td->पातed_with_changes;
	up_पढ़ो(&td->pmd->root_lock);

	वापस r;
पूर्ण

पूर्णांक dm_pool_alloc_data_block(काष्ठा dm_pool_metadata *pmd, dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (!pmd->fail_io)
		r = dm_sm_new_block(pmd->data_sm, result);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

पूर्णांक dm_pool_commit_metadata(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r = -EINVAL;

	/*
	 * Care is taken to not have commit be what
	 * triggers putting the thin-pool in-service.
	 */
	pmd_ग_लिखो_lock_in_core(pmd);
	अगर (pmd->fail_io)
		जाओ out;

	r = __commit_transaction(pmd);
	अगर (r < 0)
		जाओ out;

	/*
	 * Open the next transaction.
	 */
	r = __begin_transaction(pmd);
out:
	pmd_ग_लिखो_unlock(pmd);
	वापस r;
पूर्ण

अटल व्योम __set_पात_with_changes_flags(काष्ठा dm_pool_metadata *pmd)
अणु
	काष्ठा dm_thin_device *td;

	list_क्रम_each_entry(td, &pmd->thin_devices, list)
		td->पातed_with_changes = td->changed;
पूर्ण

पूर्णांक dm_pool_पात_metadata(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (pmd->fail_io)
		जाओ out;

	__set_पात_with_changes_flags(pmd);
	__destroy_persistent_data_objects(pmd);
	r = __create_persistent_data_objects(pmd, false);
	अगर (r)
		pmd->fail_io = true;

out:
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

पूर्णांक dm_pool_get_मुक्त_block_count(काष्ठा dm_pool_metadata *pmd, dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io)
		r = dm_sm_get_nr_मुक्त(pmd->data_sm, result);
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

पूर्णांक dm_pool_get_मुक्त_metadata_block_count(काष्ठा dm_pool_metadata *pmd,
					  dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io)
		r = dm_sm_get_nr_मुक्त(pmd->metadata_sm, result);

	अगर (!r) अणु
		अगर (*result < pmd->metadata_reserve)
			*result = 0;
		अन्यथा
			*result -= pmd->metadata_reserve;
	पूर्ण
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

पूर्णांक dm_pool_get_metadata_dev_size(काष्ठा dm_pool_metadata *pmd,
				  dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io)
		r = dm_sm_get_nr_blocks(pmd->metadata_sm, result);
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

पूर्णांक dm_pool_get_data_dev_size(काष्ठा dm_pool_metadata *pmd, dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io)
		r = dm_sm_get_nr_blocks(pmd->data_sm, result);
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

पूर्णांक dm_thin_get_mapped_count(काष्ठा dm_thin_device *td, dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा dm_pool_metadata *pmd = td->pmd;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io) अणु
		*result = td->mapped_blocks;
		r = 0;
	पूर्ण
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

अटल पूर्णांक __highest_block(काष्ठा dm_thin_device *td, dm_block_t *result)
अणु
	पूर्णांक r;
	__le64 value_le;
	dm_block_t thin_root;
	काष्ठा dm_pool_metadata *pmd = td->pmd;

	r = dm_btree_lookup(&pmd->tl_info, pmd->root, &td->id, &value_le);
	अगर (r)
		वापस r;

	thin_root = le64_to_cpu(value_le);

	वापस dm_btree_find_highest_key(&pmd->bl_info, thin_root, result);
पूर्ण

पूर्णांक dm_thin_get_highest_mapped_block(काष्ठा dm_thin_device *td,
				     dm_block_t *result)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा dm_pool_metadata *pmd = td->pmd;

	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io)
		r = __highest_block(td, result);
	up_पढ़ो(&pmd->root_lock);

	वापस r;
पूर्ण

अटल पूर्णांक __resize_space_map(काष्ठा dm_space_map *sm, dm_block_t new_count)
अणु
	पूर्णांक r;
	dm_block_t old_count;

	r = dm_sm_get_nr_blocks(sm, &old_count);
	अगर (r)
		वापस r;

	अगर (new_count == old_count)
		वापस 0;

	अगर (new_count < old_count) अणु
		DMERR("cannot reduce size of space map");
		वापस -EINVAL;
	पूर्ण

	वापस dm_sm_extend(sm, new_count - old_count);
पूर्ण

पूर्णांक dm_pool_resize_data_dev(काष्ठा dm_pool_metadata *pmd, dm_block_t new_count)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (!pmd->fail_io)
		r = __resize_space_map(pmd->data_sm, new_count);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

पूर्णांक dm_pool_resize_metadata_dev(काष्ठा dm_pool_metadata *pmd, dm_block_t new_count)
अणु
	पूर्णांक r = -EINVAL;

	pmd_ग_लिखो_lock(pmd);
	अगर (!pmd->fail_io) अणु
		r = __resize_space_map(pmd->metadata_sm, new_count);
		अगर (!r)
			__set_metadata_reserve(pmd);
	पूर्ण
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

व्योम dm_pool_metadata_पढ़ो_only(काष्ठा dm_pool_metadata *pmd)
अणु
	pmd_ग_लिखो_lock_in_core(pmd);
	dm_bm_set_पढ़ो_only(pmd->bm);
	pmd_ग_लिखो_unlock(pmd);
पूर्ण

व्योम dm_pool_metadata_पढ़ो_ग_लिखो(काष्ठा dm_pool_metadata *pmd)
अणु
	pmd_ग_लिखो_lock_in_core(pmd);
	dm_bm_set_पढ़ो_ग_लिखो(pmd->bm);
	pmd_ग_लिखो_unlock(pmd);
पूर्ण

पूर्णांक dm_pool_रेजिस्टर_metadata_threshold(काष्ठा dm_pool_metadata *pmd,
					dm_block_t threshold,
					dm_sm_threshold_fn fn,
					व्योम *context)
अणु
	पूर्णांक r;

	pmd_ग_लिखो_lock_in_core(pmd);
	r = dm_sm_रेजिस्टर_threshold_callback(pmd->metadata_sm, threshold, fn, context);
	pmd_ग_लिखो_unlock(pmd);

	वापस r;
पूर्ण

व्योम dm_pool_रेजिस्टर_pre_commit_callback(काष्ठा dm_pool_metadata *pmd,
					  dm_pool_pre_commit_fn fn,
					  व्योम *context)
अणु
	pmd_ग_लिखो_lock_in_core(pmd);
	pmd->pre_commit_fn = fn;
	pmd->pre_commit_context = context;
	pmd_ग_लिखो_unlock(pmd);
पूर्ण

पूर्णांक dm_pool_metadata_set_needs_check(काष्ठा dm_pool_metadata *pmd)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा dm_block *sblock;
	काष्ठा thin_disk_superblock *disk_super;

	pmd_ग_लिखो_lock(pmd);
	अगर (pmd->fail_io)
		जाओ out;

	pmd->flags |= THIN_METADATA_NEEDS_CHECK_FLAG;

	r = superblock_lock(pmd, &sblock);
	अगर (r) अणु
		DMERR("couldn't lock superblock");
		जाओ out;
	पूर्ण

	disk_super = dm_block_data(sblock);
	disk_super->flags = cpu_to_le32(pmd->flags);

	dm_bm_unlock(sblock);
out:
	pmd_ग_लिखो_unlock(pmd);
	वापस r;
पूर्ण

bool dm_pool_metadata_needs_check(काष्ठा dm_pool_metadata *pmd)
अणु
	bool needs_check;

	करोwn_पढ़ो(&pmd->root_lock);
	needs_check = pmd->flags & THIN_METADATA_NEEDS_CHECK_FLAG;
	up_पढ़ो(&pmd->root_lock);

	वापस needs_check;
पूर्ण

व्योम dm_pool_issue_prefetches(काष्ठा dm_pool_metadata *pmd)
अणु
	करोwn_पढ़ो(&pmd->root_lock);
	अगर (!pmd->fail_io)
		dm_पंचांग_issue_prefetches(pmd->पंचांग);
	up_पढ़ो(&pmd->root_lock);
पूर्ण
