<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश "dm.h"
#समावेश "persistent-data/dm-transaction-manager.h"
#समावेश "persistent-data/dm-bitset.h"
#समावेश "persistent-data/dm-space-map.h"

#समावेश <linux/dm-पन.स>
#समावेश <linux/dm-kcopyd.h>
#समावेश <linux/init.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#घोषणा DM_MSG_PREFIX "era"

#घोषणा SUPERBLOCK_LOCATION 0
#घोषणा SUPERBLOCK_MAGIC 2126579579
#घोषणा SUPERBLOCK_CSUM_XOR 146538381
#घोषणा MIN_ERA_VERSION 1
#घोषणा MAX_ERA_VERSION 1
#घोषणा INVALID_WRITESET_ROOT SUPERBLOCK_LOCATION
#घोषणा MIN_BLOCK_SIZE 8

/*----------------------------------------------------------------
 * Writeset
 *--------------------------------------------------------------*/
काष्ठा ग_लिखोset_metadata अणु
	uपूर्णांक32_t nr_bits;
	dm_block_t root;
पूर्ण;

काष्ठा ग_लिखोset अणु
	काष्ठा ग_लिखोset_metadata md;

	/*
	 * An in core copy of the bits to save स्थिरantly करोing look ups on
	 * disk.
	 */
	अचिन्हित दीर्घ *bits;
पूर्ण;

/*
 * This करोes not मुक्त off the on disk bitset as this will normally be करोne
 * after digesting पूर्णांकo the era array.
 */
अटल व्योम ग_लिखोset_मुक्त(काष्ठा ग_लिखोset *ws)
अणु
	vमुक्त(ws->bits);
	ws->bits = शून्य;
पूर्ण

अटल पूर्णांक setup_on_disk_bitset(काष्ठा dm_disk_bitset *info,
				अचिन्हित nr_bits, dm_block_t *root)
अणु
	पूर्णांक r;

	r = dm_bitset_empty(info, root);
	अगर (r)
		वापस r;

	वापस dm_bitset_resize(info, *root, 0, nr_bits, false, root);
पूर्ण

अटल माप_प्रकार bitset_size(अचिन्हित nr_bits)
अणु
	वापस माप(अचिन्हित दीर्घ) * dm_भाग_up(nr_bits, BITS_PER_LONG);
पूर्ण

/*
 * Allocates memory क्रम the in core bitset.
 */
अटल पूर्णांक ग_लिखोset_alloc(काष्ठा ग_लिखोset *ws, dm_block_t nr_blocks)
अणु
	ws->bits = vzalloc(bitset_size(nr_blocks));
	अगर (!ws->bits) अणु
		DMERR("%s: couldn't allocate in memory bitset", __func__);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wipes the in-core bitset, and creates a new on disk bitset.
 */
अटल पूर्णांक ग_लिखोset_init(काष्ठा dm_disk_bitset *info, काष्ठा ग_लिखोset *ws,
			 dm_block_t nr_blocks)
अणु
	पूर्णांक r;

	स_रखो(ws->bits, 0, bitset_size(nr_blocks));

	ws->md.nr_bits = nr_blocks;
	r = setup_on_disk_bitset(info, ws->md.nr_bits, &ws->md.root);
	अगर (r) अणु
		DMERR("%s: setup_on_disk_bitset failed", __func__);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ग_लिखोset_marked(काष्ठा ग_लिखोset *ws, dm_block_t block)
अणु
	वापस test_bit(block, ws->bits);
पूर्ण

अटल पूर्णांक ग_लिखोset_marked_on_disk(काष्ठा dm_disk_bitset *info,
				   काष्ठा ग_लिखोset_metadata *m, dm_block_t block,
				   bool *result)
अणु
	dm_block_t old = m->root;

	/*
	 * The bitset was flushed when it was archived, so we know there'll
	 * be no change to the root.
	 */
	पूर्णांक r = dm_bitset_test_bit(info, m->root, block, &m->root, result);
	अगर (r) अणु
		DMERR("%s: dm_bitset_test_bit failed", __func__);
		वापस r;
	पूर्ण

	BUG_ON(m->root != old);

	वापस r;
पूर्ण

/*
 * Returns < 0 on error, 0 अगर the bit wasn't previously set, 1 अगर it was.
 */
अटल पूर्णांक ग_लिखोset_test_and_set(काष्ठा dm_disk_bitset *info,
				 काष्ठा ग_लिखोset *ws, uपूर्णांक32_t block)
अणु
	पूर्णांक r;

	अगर (!test_bit(block, ws->bits)) अणु
		r = dm_bitset_set_bit(info, ws->md.root, block, &ws->md.root);
		अगर (r) अणु
			/* FIXME: fail mode */
			वापस r;
		पूर्ण

		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*----------------------------------------------------------------
 * On disk metadata layout
 *--------------------------------------------------------------*/
#घोषणा SPACE_MAP_ROOT_SIZE 128
#घोषणा UUID_LEN 16

काष्ठा ग_लिखोset_disk अणु
	__le32 nr_bits;
	__le64 root;
पूर्ण __packed;

काष्ठा superblock_disk अणु
	__le32 csum;
	__le32 flags;
	__le64 blocknr;

	__u8 uuid[UUID_LEN];
	__le64 magic;
	__le32 version;

	__u8 metadata_space_map_root[SPACE_MAP_ROOT_SIZE];

	__le32 data_block_size;
	__le32 metadata_block_size;
	__le32 nr_blocks;

	__le32 current_era;
	काष्ठा ग_लिखोset_disk current_ग_लिखोset;

	/*
	 * Only these two fields are valid within the metadata snapshot.
	 */
	__le64 ग_लिखोset_tree_root;
	__le64 era_array_root;

	__le64 metadata_snap;
पूर्ण __packed;

/*----------------------------------------------------------------
 * Superblock validation
 *--------------------------------------------------------------*/
अटल व्योम sb_prepare_क्रम_ग_लिखो(काष्ठा dm_block_validator *v,
				 काष्ठा dm_block *b,
				 माप_प्रकार sb_block_size)
अणु
	काष्ठा superblock_disk *disk = dm_block_data(b);

	disk->blocknr = cpu_to_le64(dm_block_location(b));
	disk->csum = cpu_to_le32(dm_bm_checksum(&disk->flags,
						sb_block_size - माप(__le32),
						SUPERBLOCK_CSUM_XOR));
पूर्ण

अटल पूर्णांक check_metadata_version(काष्ठा superblock_disk *disk)
अणु
	uपूर्णांक32_t metadata_version = le32_to_cpu(disk->version);
	अगर (metadata_version < MIN_ERA_VERSION || metadata_version > MAX_ERA_VERSION) अणु
		DMERR("Era metadata version %u found, but only versions between %u and %u supported.",
		      metadata_version, MIN_ERA_VERSION, MAX_ERA_VERSION);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sb_check(काष्ठा dm_block_validator *v,
		    काष्ठा dm_block *b,
		    माप_प्रकार sb_block_size)
अणु
	काष्ठा superblock_disk *disk = dm_block_data(b);
	__le32 csum_le;

	अगर (dm_block_location(b) != le64_to_cpu(disk->blocknr)) अणु
		DMERR("sb_check failed: blocknr %llu: wanted %llu",
		      le64_to_cpu(disk->blocknr),
		      (अचिन्हित दीर्घ दीर्घ)dm_block_location(b));
		वापस -ENOTBLK;
	पूर्ण

	अगर (le64_to_cpu(disk->magic) != SUPERBLOCK_MAGIC) अणु
		DMERR("sb_check failed: magic %llu: wanted %llu",
		      le64_to_cpu(disk->magic),
		      (अचिन्हित दीर्घ दीर्घ) SUPERBLOCK_MAGIC);
		वापस -EILSEQ;
	पूर्ण

	csum_le = cpu_to_le32(dm_bm_checksum(&disk->flags,
					     sb_block_size - माप(__le32),
					     SUPERBLOCK_CSUM_XOR));
	अगर (csum_le != disk->csum) अणु
		DMERR("sb_check failed: csum %u: wanted %u",
		      le32_to_cpu(csum_le), le32_to_cpu(disk->csum));
		वापस -EILSEQ;
	पूर्ण

	वापस check_metadata_version(disk);
पूर्ण

अटल काष्ठा dm_block_validator sb_validator = अणु
	.name = "superblock",
	.prepare_क्रम_ग_लिखो = sb_prepare_क्रम_ग_लिखो,
	.check = sb_check
पूर्ण;

/*----------------------------------------------------------------
 * Low level metadata handling
 *--------------------------------------------------------------*/
#घोषणा DM_ERA_METADATA_BLOCK_SIZE 4096
#घोषणा ERA_MAX_CONCURRENT_LOCKS 5

काष्ठा era_metadata अणु
	काष्ठा block_device *bdev;
	काष्ठा dm_block_manager *bm;
	काष्ठा dm_space_map *sm;
	काष्ठा dm_transaction_manager *पंचांग;

	dm_block_t block_size;
	uपूर्णांक32_t nr_blocks;

	uपूर्णांक32_t current_era;

	/*
	 * We pपुनः_स्मृतिate 2 ग_लिखोsets.  When an era rolls over we
	 * चयन between them. This means the allocation is करोne at
	 * preresume समय, rather than on the io path.
	 */
	काष्ठा ग_लिखोset ग_लिखोsets[2];
	काष्ठा ग_लिखोset *current_ग_लिखोset;

	dm_block_t ग_लिखोset_tree_root;
	dm_block_t era_array_root;

	काष्ठा dm_disk_bitset bitset_info;
	काष्ठा dm_btree_info ग_लिखोset_tree_info;
	काष्ठा dm_array_info era_array_info;

	dm_block_t metadata_snap;

	/*
	 * A flag that is set whenever a ग_लिखोset has been archived.
	 */
	bool archived_ग_लिखोsets;

	/*
	 * Reading the space map root can fail, so we पढ़ो it पूर्णांकo this
	 * buffer beक्रमe the superblock is locked and updated.
	 */
	__u8 metadata_space_map_root[SPACE_MAP_ROOT_SIZE];
पूर्ण;

अटल पूर्णांक superblock_पढ़ो_lock(काष्ठा era_metadata *md,
				काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_पढ़ो_lock(md->bm, SUPERBLOCK_LOCATION,
			       &sb_validator, sblock);
पूर्ण

अटल पूर्णांक superblock_lock_zero(काष्ठा era_metadata *md,
				काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_ग_लिखो_lock_zero(md->bm, SUPERBLOCK_LOCATION,
				     &sb_validator, sblock);
पूर्ण

अटल पूर्णांक superblock_lock(काष्ठा era_metadata *md,
			   काष्ठा dm_block **sblock)
अणु
	वापस dm_bm_ग_लिखो_lock(md->bm, SUPERBLOCK_LOCATION,
				&sb_validator, sblock);
पूर्ण

/* FIXME: duplication with cache and thin */
अटल पूर्णांक superblock_all_zeroes(काष्ठा dm_block_manager *bm, bool *result)
अणु
	पूर्णांक r;
	अचिन्हित i;
	काष्ठा dm_block *b;
	__le64 *data_le, zero = cpu_to_le64(0);
	अचिन्हित sb_block_size = dm_bm_block_size(bm) / माप(__le64);

	/*
	 * We can't use a validator here - it may be all zeroes.
	 */
	r = dm_bm_पढ़ो_lock(bm, SUPERBLOCK_LOCATION, शून्य, &b);
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

/*----------------------------------------------------------------*/

अटल व्योम ws_pack(स्थिर काष्ठा ग_लिखोset_metadata *core, काष्ठा ग_लिखोset_disk *disk)
अणु
	disk->nr_bits = cpu_to_le32(core->nr_bits);
	disk->root = cpu_to_le64(core->root);
पूर्ण

अटल व्योम ws_unpack(स्थिर काष्ठा ग_लिखोset_disk *disk, काष्ठा ग_लिखोset_metadata *core)
अणु
	core->nr_bits = le32_to_cpu(disk->nr_bits);
	core->root = le64_to_cpu(disk->root);
पूर्ण

अटल व्योम ws_inc(व्योम *context, स्थिर व्योम *value)
अणु
	काष्ठा era_metadata *md = context;
	काष्ठा ग_लिखोset_disk ws_d;
	dm_block_t b;

	स_नकल(&ws_d, value, माप(ws_d));
	b = le64_to_cpu(ws_d.root);

	dm_पंचांग_inc(md->पंचांग, b);
पूर्ण

अटल व्योम ws_dec(व्योम *context, स्थिर व्योम *value)
अणु
	काष्ठा era_metadata *md = context;
	काष्ठा ग_लिखोset_disk ws_d;
	dm_block_t b;

	स_नकल(&ws_d, value, माप(ws_d));
	b = le64_to_cpu(ws_d.root);

	dm_bitset_del(&md->bitset_info, b);
पूर्ण

अटल पूर्णांक ws_eq(व्योम *context, स्थिर व्योम *value1, स्थिर व्योम *value2)
अणु
	वापस !स_भेद(value1, value2, माप(काष्ठा ग_लिखोset_disk));
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम setup_ग_लिखोset_tree_info(काष्ठा era_metadata *md)
अणु
	काष्ठा dm_btree_value_type *vt = &md->ग_लिखोset_tree_info.value_type;
	md->ग_लिखोset_tree_info.पंचांग = md->पंचांग;
	md->ग_लिखोset_tree_info.levels = 1;
	vt->context = md;
	vt->size = माप(काष्ठा ग_लिखोset_disk);
	vt->inc = ws_inc;
	vt->dec = ws_dec;
	vt->equal = ws_eq;
पूर्ण

अटल व्योम setup_era_array_info(काष्ठा era_metadata *md)

अणु
	काष्ठा dm_btree_value_type vt;
	vt.context = शून्य;
	vt.size = माप(__le32);
	vt.inc = शून्य;
	vt.dec = शून्य;
	vt.equal = शून्य;

	dm_array_info_init(&md->era_array_info, md->पंचांग, &vt);
पूर्ण

अटल व्योम setup_infos(काष्ठा era_metadata *md)
अणु
	dm_disk_bitset_init(md->पंचांग, &md->bitset_info);
	setup_ग_लिखोset_tree_info(md);
	setup_era_array_info(md);
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक create_fresh_metadata(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;

	r = dm_पंचांग_create_with_sm(md->bm, SUPERBLOCK_LOCATION,
				 &md->पंचांग, &md->sm);
	अगर (r < 0) अणु
		DMERR("dm_tm_create_with_sm failed");
		वापस r;
	पूर्ण

	setup_infos(md);

	r = dm_btree_empty(&md->ग_लिखोset_tree_info, &md->ग_लिखोset_tree_root);
	अगर (r) अणु
		DMERR("couldn't create new writeset tree");
		जाओ bad;
	पूर्ण

	r = dm_array_empty(&md->era_array_info, &md->era_array_root);
	अगर (r) अणु
		DMERR("couldn't create era array");
		जाओ bad;
	पूर्ण

	वापस 0;

bad:
	dm_sm_destroy(md->sm);
	dm_पंचांग_destroy(md->पंचांग);

	वापस r;
पूर्ण

अटल पूर्णांक save_sm_root(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;
	माप_प्रकार metadata_len;

	r = dm_sm_root_size(md->sm, &metadata_len);
	अगर (r < 0)
		वापस r;

	वापस dm_sm_copy_root(md->sm, &md->metadata_space_map_root,
			       metadata_len);
पूर्ण

अटल व्योम copy_sm_root(काष्ठा era_metadata *md, काष्ठा superblock_disk *disk)
अणु
	स_नकल(&disk->metadata_space_map_root,
	       &md->metadata_space_map_root,
	       माप(md->metadata_space_map_root));
पूर्ण

/*
 * Writes a superblock, including the अटल fields that करोn't get updated
 * with every commit (possible optimisation here).  'md' should be fully
 * स्थिरructed when this is called.
 */
अटल व्योम prepare_superblock(काष्ठा era_metadata *md, काष्ठा superblock_disk *disk)
अणु
	disk->magic = cpu_to_le64(SUPERBLOCK_MAGIC);
	disk->flags = cpu_to_le32(0ul);

	/* FIXME: can't keep blanking the uuid (uuid is currently unused though) */
	स_रखो(disk->uuid, 0, माप(disk->uuid));
	disk->version = cpu_to_le32(MAX_ERA_VERSION);

	copy_sm_root(md, disk);

	disk->data_block_size = cpu_to_le32(md->block_size);
	disk->metadata_block_size = cpu_to_le32(DM_ERA_METADATA_BLOCK_SIZE >> SECTOR_SHIFT);
	disk->nr_blocks = cpu_to_le32(md->nr_blocks);
	disk->current_era = cpu_to_le32(md->current_era);

	ws_pack(&md->current_ग_लिखोset->md, &disk->current_ग_लिखोset);
	disk->ग_लिखोset_tree_root = cpu_to_le64(md->ग_लिखोset_tree_root);
	disk->era_array_root = cpu_to_le64(md->era_array_root);
	disk->metadata_snap = cpu_to_le64(md->metadata_snap);
पूर्ण

अटल पूर्णांक ग_लिखो_superblock(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा superblock_disk *disk;

	r = save_sm_root(md);
	अगर (r) अणु
		DMERR("%s: save_sm_root failed", __func__);
		वापस r;
	पूर्ण

	r = superblock_lock_zero(md, &sblock);
	अगर (r)
		वापस r;

	disk = dm_block_data(sblock);
	prepare_superblock(md, disk);

	वापस dm_पंचांग_commit(md->पंचांग, sblock);
पूर्ण

/*
 * Assumes block_size and the infos are set.
 */
अटल पूर्णांक क्रमmat_metadata(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;

	r = create_fresh_metadata(md);
	अगर (r)
		वापस r;

	r = ग_लिखो_superblock(md);
	अगर (r) अणु
		dm_sm_destroy(md->sm);
		dm_पंचांग_destroy(md->पंचांग);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक खोलो_metadata(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;
	काष्ठा superblock_disk *disk;

	r = superblock_पढ़ो_lock(md, &sblock);
	अगर (r) अणु
		DMERR("couldn't read_lock superblock");
		वापस r;
	पूर्ण

	disk = dm_block_data(sblock);

	/* Verअगरy the data block size hasn't changed */
	अगर (le32_to_cpu(disk->data_block_size) != md->block_size) अणु
		DMERR("changing the data block size (from %u to %llu) is not supported",
		      le32_to_cpu(disk->data_block_size), md->block_size);
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	r = dm_पंचांग_खोलो_with_sm(md->bm, SUPERBLOCK_LOCATION,
			       disk->metadata_space_map_root,
			       माप(disk->metadata_space_map_root),
			       &md->पंचांग, &md->sm);
	अगर (r) अणु
		DMERR("dm_tm_open_with_sm failed");
		जाओ bad;
	पूर्ण

	setup_infos(md);

	md->nr_blocks = le32_to_cpu(disk->nr_blocks);
	md->current_era = le32_to_cpu(disk->current_era);

	ws_unpack(&disk->current_ग_लिखोset, &md->current_ग_लिखोset->md);
	md->ग_लिखोset_tree_root = le64_to_cpu(disk->ग_लिखोset_tree_root);
	md->era_array_root = le64_to_cpu(disk->era_array_root);
	md->metadata_snap = le64_to_cpu(disk->metadata_snap);
	md->archived_ग_लिखोsets = true;

	dm_bm_unlock(sblock);

	वापस 0;

bad:
	dm_bm_unlock(sblock);
	वापस r;
पूर्ण

अटल पूर्णांक खोलो_or_क्रमmat_metadata(काष्ठा era_metadata *md,
				   bool may_क्रमmat)
अणु
	पूर्णांक r;
	bool unक्रमmatted = false;

	r = superblock_all_zeroes(md->bm, &unक्रमmatted);
	अगर (r)
		वापस r;

	अगर (unक्रमmatted)
		वापस may_क्रमmat ? क्रमmat_metadata(md) : -EPERM;

	वापस खोलो_metadata(md);
पूर्ण

अटल पूर्णांक create_persistent_data_objects(काष्ठा era_metadata *md,
					  bool may_क्रमmat)
अणु
	पूर्णांक r;

	md->bm = dm_block_manager_create(md->bdev, DM_ERA_METADATA_BLOCK_SIZE,
					 ERA_MAX_CONCURRENT_LOCKS);
	अगर (IS_ERR(md->bm)) अणु
		DMERR("could not create block manager");
		वापस PTR_ERR(md->bm);
	पूर्ण

	r = खोलो_or_क्रमmat_metadata(md, may_क्रमmat);
	अगर (r)
		dm_block_manager_destroy(md->bm);

	वापस r;
पूर्ण

अटल व्योम destroy_persistent_data_objects(काष्ठा era_metadata *md)
अणु
	dm_sm_destroy(md->sm);
	dm_पंचांग_destroy(md->पंचांग);
	dm_block_manager_destroy(md->bm);
पूर्ण

/*
 * This रुकोs until all era_map thपढ़ोs have picked up the new filter.
 */
अटल व्योम swap_ग_लिखोset(काष्ठा era_metadata *md, काष्ठा ग_लिखोset *new_ग_लिखोset)
अणु
	rcu_assign_poपूर्णांकer(md->current_ग_लिखोset, new_ग_लिखोset);
	synchronize_rcu();
पूर्ण

/*----------------------------------------------------------------
 * Writesets get 'digested' पूर्णांकo the मुख्य era array.
 *
 * We're using a coroutine here so the worker thपढ़ो can करो the digestion,
 * thus aव्योमing synchronisation of the metadata.  Digesting a whole
 * ग_लिखोset in one go would cause too much latency.
 *--------------------------------------------------------------*/
काष्ठा digest अणु
	uपूर्णांक32_t era;
	अचिन्हित nr_bits, current_bit;
	काष्ठा ग_लिखोset_metadata ग_लिखोset;
	__le32 value;
	काष्ठा dm_disk_bitset info;

	पूर्णांक (*step)(काष्ठा era_metadata *, काष्ठा digest *);
पूर्ण;

अटल पूर्णांक metadata_digest_lookup_ग_लिखोset(काष्ठा era_metadata *md,
					   काष्ठा digest *d);

अटल पूर्णांक metadata_digest_हटाओ_ग_लिखोset(काष्ठा era_metadata *md,
					   काष्ठा digest *d)
अणु
	पूर्णांक r;
	uपूर्णांक64_t key = d->era;

	r = dm_btree_हटाओ(&md->ग_लिखोset_tree_info, md->ग_लिखोset_tree_root,
			    &key, &md->ग_लिखोset_tree_root);
	अगर (r) अणु
		DMERR("%s: dm_btree_remove failed", __func__);
		वापस r;
	पूर्ण

	d->step = metadata_digest_lookup_ग_लिखोset;
	वापस 0;
पूर्ण

#घोषणा INSERTS_PER_STEP 100

अटल पूर्णांक metadata_digest_transcribe_ग_लिखोset(काष्ठा era_metadata *md,
					       काष्ठा digest *d)
अणु
	पूर्णांक r;
	bool marked;
	अचिन्हित b, e = min(d->current_bit + INSERTS_PER_STEP, d->nr_bits);

	क्रम (b = d->current_bit; b < e; b++) अणु
		r = ग_लिखोset_marked_on_disk(&d->info, &d->ग_लिखोset, b, &marked);
		अगर (r) अणु
			DMERR("%s: writeset_marked_on_disk failed", __func__);
			वापस r;
		पूर्ण

		अगर (!marked)
			जारी;

		__dm_bless_क्रम_disk(&d->value);
		r = dm_array_set_value(&md->era_array_info, md->era_array_root,
				       b, &d->value, &md->era_array_root);
		अगर (r) अणु
			DMERR("%s: dm_array_set_value failed", __func__);
			वापस r;
		पूर्ण
	पूर्ण

	अगर (b == d->nr_bits)
		d->step = metadata_digest_हटाओ_ग_लिखोset;
	अन्यथा
		d->current_bit = b;

	वापस 0;
पूर्ण

अटल पूर्णांक metadata_digest_lookup_ग_लिखोset(काष्ठा era_metadata *md,
					   काष्ठा digest *d)
अणु
	पूर्णांक r;
	uपूर्णांक64_t key;
	काष्ठा ग_लिखोset_disk disk;

	r = dm_btree_find_lowest_key(&md->ग_लिखोset_tree_info,
				     md->ग_लिखोset_tree_root, &key);
	अगर (r < 0)
		वापस r;

	d->era = key;

	r = dm_btree_lookup(&md->ग_लिखोset_tree_info,
			    md->ग_लिखोset_tree_root, &key, &disk);
	अगर (r) अणु
		अगर (r == -ENODATA) अणु
			d->step = शून्य;
			वापस 0;
		पूर्ण

		DMERR("%s: dm_btree_lookup failed", __func__);
		वापस r;
	पूर्ण

	ws_unpack(&disk, &d->ग_लिखोset);
	d->value = cpu_to_le32(key);

	/*
	 * We initialise another bitset info to aव्योम any caching side effects
	 * with the previous one.
	 */
	dm_disk_bitset_init(md->पंचांग, &d->info);

	d->nr_bits = min(d->ग_लिखोset.nr_bits, md->nr_blocks);
	d->current_bit = 0;
	d->step = metadata_digest_transcribe_ग_लिखोset;

	वापस 0;
पूर्ण

अटल पूर्णांक metadata_digest_start(काष्ठा era_metadata *md, काष्ठा digest *d)
अणु
	अगर (d->step)
		वापस 0;

	स_रखो(d, 0, माप(*d));
	d->step = metadata_digest_lookup_ग_लिखोset;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * High level metadata पूर्णांकerface.  Target methods should use these, and not
 * the lower level ones.
 *--------------------------------------------------------------*/
अटल काष्ठा era_metadata *metadata_खोलो(काष्ठा block_device *bdev,
					  sector_t block_size,
					  bool may_क्रमmat)
अणु
	पूर्णांक r;
	काष्ठा era_metadata *md = kzalloc(माप(*md), GFP_KERNEL);

	अगर (!md)
		वापस शून्य;

	md->bdev = bdev;
	md->block_size = block_size;

	md->ग_लिखोsets[0].md.root = INVALID_WRITESET_ROOT;
	md->ग_लिखोsets[1].md.root = INVALID_WRITESET_ROOT;
	md->current_ग_लिखोset = &md->ग_लिखोsets[0];

	r = create_persistent_data_objects(md, may_क्रमmat);
	अगर (r) अणु
		kमुक्त(md);
		वापस ERR_PTR(r);
	पूर्ण

	वापस md;
पूर्ण

अटल व्योम metadata_बंद(काष्ठा era_metadata *md)
अणु
	ग_लिखोset_मुक्त(&md->ग_लिखोsets[0]);
	ग_लिखोset_मुक्त(&md->ग_लिखोsets[1]);
	destroy_persistent_data_objects(md);
	kमुक्त(md);
पूर्ण

अटल bool valid_nr_blocks(dm_block_t n)
अणु
	/*
	 * dm_bitset restricts us to 2^32.  test_bit & co. restrict us
	 * further to 2^31 - 1
	 */
	वापस n < (1ull << 31);
पूर्ण

अटल पूर्णांक metadata_resize(काष्ठा era_metadata *md, व्योम *arg)
अणु
	पूर्णांक r;
	dm_block_t *new_size = arg;
	__le32 value;

	अगर (!valid_nr_blocks(*new_size)) अणु
		DMERR("Invalid number of origin blocks %llu",
		      (अचिन्हित दीर्घ दीर्घ) *new_size);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोset_मुक्त(&md->ग_लिखोsets[0]);
	ग_लिखोset_मुक्त(&md->ग_लिखोsets[1]);

	r = ग_लिखोset_alloc(&md->ग_लिखोsets[0], *new_size);
	अगर (r) अणु
		DMERR("%s: writeset_alloc failed for writeset 0", __func__);
		वापस r;
	पूर्ण

	r = ग_लिखोset_alloc(&md->ग_लिखोsets[1], *new_size);
	अगर (r) अणु
		DMERR("%s: writeset_alloc failed for writeset 1", __func__);
		ग_लिखोset_मुक्त(&md->ग_लिखोsets[0]);
		वापस r;
	पूर्ण

	value = cpu_to_le32(0u);
	__dm_bless_क्रम_disk(&value);
	r = dm_array_resize(&md->era_array_info, md->era_array_root,
			    md->nr_blocks, *new_size,
			    &value, &md->era_array_root);
	अगर (r) अणु
		DMERR("%s: dm_array_resize failed", __func__);
		ग_लिखोset_मुक्त(&md->ग_लिखोsets[0]);
		ग_लिखोset_मुक्त(&md->ग_लिखोsets[1]);
		वापस r;
	पूर्ण

	md->nr_blocks = *new_size;
	वापस 0;
पूर्ण

अटल पूर्णांक metadata_era_archive(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;
	uपूर्णांक64_t keys[1];
	काष्ठा ग_लिखोset_disk value;

	r = dm_bitset_flush(&md->bitset_info, md->current_ग_लिखोset->md.root,
			    &md->current_ग_लिखोset->md.root);
	अगर (r) अणु
		DMERR("%s: dm_bitset_flush failed", __func__);
		वापस r;
	पूर्ण

	ws_pack(&md->current_ग_लिखोset->md, &value);

	keys[0] = md->current_era;
	__dm_bless_क्रम_disk(&value);
	r = dm_btree_insert(&md->ग_लिखोset_tree_info, md->ग_लिखोset_tree_root,
			    keys, &value, &md->ग_लिखोset_tree_root);
	अगर (r) अणु
		DMERR("%s: couldn't insert writeset into btree", __func__);
		/* FIXME: fail mode */
		वापस r;
	पूर्ण

	md->current_ग_लिखोset->md.root = INVALID_WRITESET_ROOT;
	md->archived_ग_लिखोsets = true;

	वापस 0;
पूर्ण

अटल काष्ठा ग_लिखोset *next_ग_लिखोset(काष्ठा era_metadata *md)
अणु
	वापस (md->current_ग_लिखोset == &md->ग_लिखोsets[0]) ?
		&md->ग_लिखोsets[1] : &md->ग_लिखोsets[0];
पूर्ण

अटल पूर्णांक metadata_new_era(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;
	काष्ठा ग_लिखोset *new_ग_लिखोset = next_ग_लिखोset(md);

	r = ग_लिखोset_init(&md->bitset_info, new_ग_लिखोset, md->nr_blocks);
	अगर (r) अणु
		DMERR("%s: writeset_init failed", __func__);
		वापस r;
	पूर्ण

	swap_ग_लिखोset(md, new_ग_लिखोset);
	md->current_era++;

	वापस 0;
पूर्ण

अटल पूर्णांक metadata_era_rollover(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;

	अगर (md->current_ग_लिखोset->md.root != INVALID_WRITESET_ROOT) अणु
		r = metadata_era_archive(md);
		अगर (r) अणु
			DMERR("%s: metadata_archive_era failed", __func__);
			/* FIXME: fail mode? */
			वापस r;
		पूर्ण
	पूर्ण

	r = metadata_new_era(md);
	अगर (r) अणु
		DMERR("%s: new era failed", __func__);
		/* FIXME: fail mode */
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool metadata_current_marked(काष्ठा era_metadata *md, dm_block_t block)
अणु
	bool r;
	काष्ठा ग_लिखोset *ws;

	rcu_पढ़ो_lock();
	ws = rcu_dereference(md->current_ग_लिखोset);
	r = ग_लिखोset_marked(ws, block);
	rcu_पढ़ो_unlock();

	वापस r;
पूर्ण

अटल पूर्णांक metadata_commit(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;
	काष्ठा dm_block *sblock;

	अगर (md->current_ग_लिखोset->md.root != INVALID_WRITESET_ROOT) अणु
		r = dm_bitset_flush(&md->bitset_info, md->current_ग_लिखोset->md.root,
				    &md->current_ग_लिखोset->md.root);
		अगर (r) अणु
			DMERR("%s: bitset flush failed", __func__);
			वापस r;
		पूर्ण
	पूर्ण

	r = dm_पंचांग_pre_commit(md->पंचांग);
	अगर (r) अणु
		DMERR("%s: pre commit failed", __func__);
		वापस r;
	पूर्ण

	r = save_sm_root(md);
	अगर (r) अणु
		DMERR("%s: save_sm_root failed", __func__);
		वापस r;
	पूर्ण

	r = superblock_lock(md, &sblock);
	अगर (r) अणु
		DMERR("%s: superblock lock failed", __func__);
		वापस r;
	पूर्ण

	prepare_superblock(md, dm_block_data(sblock));

	वापस dm_पंचांग_commit(md->पंचांग, sblock);
पूर्ण

अटल पूर्णांक metadata_checkpoपूर्णांक(काष्ठा era_metadata *md)
अणु
	/*
	 * For now we just rollover, but later I want to put a check in to
	 * aव्योम this अगर the filter is still pretty fresh.
	 */
	वापस metadata_era_rollover(md);
पूर्ण

/*
 * Metadata snapshots allow userland to access era data.
 */
अटल पूर्णांक metadata_take_snap(काष्ठा era_metadata *md)
अणु
	पूर्णांक r, inc;
	काष्ठा dm_block *clone;

	अगर (md->metadata_snap != SUPERBLOCK_LOCATION) अणु
		DMERR("%s: metadata snapshot already exists", __func__);
		वापस -EINVAL;
	पूर्ण

	r = metadata_era_rollover(md);
	अगर (r) अणु
		DMERR("%s: era rollover failed", __func__);
		वापस r;
	पूर्ण

	r = metadata_commit(md);
	अगर (r) अणु
		DMERR("%s: pre commit failed", __func__);
		वापस r;
	पूर्ण

	r = dm_sm_inc_block(md->sm, SUPERBLOCK_LOCATION);
	अगर (r) अणु
		DMERR("%s: couldn't increment superblock", __func__);
		वापस r;
	पूर्ण

	r = dm_पंचांग_shaकरोw_block(md->पंचांग, SUPERBLOCK_LOCATION,
			       &sb_validator, &clone, &inc);
	अगर (r) अणु
		DMERR("%s: couldn't shadow superblock", __func__);
		dm_sm_dec_block(md->sm, SUPERBLOCK_LOCATION);
		वापस r;
	पूर्ण
	BUG_ON(!inc);

	r = dm_sm_inc_block(md->sm, md->ग_लिखोset_tree_root);
	अगर (r) अणु
		DMERR("%s: couldn't inc writeset tree root", __func__);
		dm_पंचांग_unlock(md->पंचांग, clone);
		वापस r;
	पूर्ण

	r = dm_sm_inc_block(md->sm, md->era_array_root);
	अगर (r) अणु
		DMERR("%s: couldn't inc era tree root", __func__);
		dm_sm_dec_block(md->sm, md->ग_लिखोset_tree_root);
		dm_पंचांग_unlock(md->पंचांग, clone);
		वापस r;
	पूर्ण

	md->metadata_snap = dm_block_location(clone);

	dm_पंचांग_unlock(md->पंचांग, clone);

	वापस 0;
पूर्ण

अटल पूर्णांक metadata_drop_snap(काष्ठा era_metadata *md)
अणु
	पूर्णांक r;
	dm_block_t location;
	काष्ठा dm_block *clone;
	काष्ठा superblock_disk *disk;

	अगर (md->metadata_snap == SUPERBLOCK_LOCATION) अणु
		DMERR("%s: no snap to drop", __func__);
		वापस -EINVAL;
	पूर्ण

	r = dm_पंचांग_पढ़ो_lock(md->पंचांग, md->metadata_snap, &sb_validator, &clone);
	अगर (r) अणु
		DMERR("%s: couldn't read lock superblock clone", __func__);
		वापस r;
	पूर्ण

	/*
	 * Whatever happens now we'll commit with no record of the metadata
	 * snap.
	 */
	md->metadata_snap = SUPERBLOCK_LOCATION;

	disk = dm_block_data(clone);
	r = dm_btree_del(&md->ग_लिखोset_tree_info,
			 le64_to_cpu(disk->ग_लिखोset_tree_root));
	अगर (r) अणु
		DMERR("%s: error deleting writeset tree clone", __func__);
		dm_पंचांग_unlock(md->पंचांग, clone);
		वापस r;
	पूर्ण

	r = dm_array_del(&md->era_array_info, le64_to_cpu(disk->era_array_root));
	अगर (r) अणु
		DMERR("%s: error deleting era array clone", __func__);
		dm_पंचांग_unlock(md->पंचांग, clone);
		वापस r;
	पूर्ण

	location = dm_block_location(clone);
	dm_पंचांग_unlock(md->पंचांग, clone);

	वापस dm_sm_dec_block(md->sm, location);
पूर्ण

काष्ठा metadata_stats अणु
	dm_block_t used;
	dm_block_t total;
	dm_block_t snap;
	uपूर्णांक32_t era;
पूर्ण;

अटल पूर्णांक metadata_get_stats(काष्ठा era_metadata *md, व्योम *ptr)
अणु
	पूर्णांक r;
	काष्ठा metadata_stats *s = ptr;
	dm_block_t nr_मुक्त, nr_total;

	r = dm_sm_get_nr_मुक्त(md->sm, &nr_मुक्त);
	अगर (r) अणु
		DMERR("dm_sm_get_nr_free returned %d", r);
		वापस r;
	पूर्ण

	r = dm_sm_get_nr_blocks(md->sm, &nr_total);
	अगर (r) अणु
		DMERR("dm_pool_get_metadata_dev_size returned %d", r);
		वापस r;
	पूर्ण

	s->used = nr_total - nr_मुक्त;
	s->total = nr_total;
	s->snap = md->metadata_snap;
	s->era = md->current_era;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा era अणु
	काष्ठा dm_target *ti;

	काष्ठा dm_dev *metadata_dev;
	काष्ठा dm_dev *origin_dev;

	dm_block_t nr_blocks;
	uपूर्णांक32_t sectors_per_block;
	पूर्णांक sectors_per_block_shअगरt;
	काष्ठा era_metadata *md;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा worker;

	spinlock_t deferred_lock;
	काष्ठा bio_list deferred_bios;

	spinlock_t rpc_lock;
	काष्ठा list_head rpc_calls;

	काष्ठा digest digest;
	atomic_t suspended;
पूर्ण;

काष्ठा rpc अणु
	काष्ठा list_head list;

	पूर्णांक (*fn0)(काष्ठा era_metadata *);
	पूर्णांक (*fn1)(काष्ठा era_metadata *, व्योम *);
	व्योम *arg;
	पूर्णांक result;

	काष्ठा completion complete;
पूर्ण;

/*----------------------------------------------------------------
 * Remapping.
 *---------------------------------------------------------------*/
अटल bool block_size_is_घातer_of_two(काष्ठा era *era)
अणु
	वापस era->sectors_per_block_shअगरt >= 0;
पूर्ण

अटल dm_block_t get_block(काष्ठा era *era, काष्ठा bio *bio)
अणु
	sector_t block_nr = bio->bi_iter.bi_sector;

	अगर (!block_size_is_घातer_of_two(era))
		(व्योम) sector_भाग(block_nr, era->sectors_per_block);
	अन्यथा
		block_nr >>= era->sectors_per_block_shअगरt;

	वापस block_nr;
पूर्ण

अटल व्योम remap_to_origin(काष्ठा era *era, काष्ठा bio *bio)
अणु
	bio_set_dev(bio, era->origin_dev->bdev);
पूर्ण

/*----------------------------------------------------------------
 * Worker thपढ़ो
 *--------------------------------------------------------------*/
अटल व्योम wake_worker(काष्ठा era *era)
अणु
	अगर (!atomic_पढ़ो(&era->suspended))
		queue_work(era->wq, &era->worker);
पूर्ण

अटल व्योम process_old_eras(काष्ठा era *era)
अणु
	पूर्णांक r;

	अगर (!era->digest.step)
		वापस;

	r = era->digest.step(era->md, &era->digest);
	अगर (r < 0) अणु
		DMERR("%s: digest step failed, stopping digestion", __func__);
		era->digest.step = शून्य;

	पूर्ण अन्यथा अगर (era->digest.step)
		wake_worker(era);
पूर्ण

अटल व्योम process_deferred_bios(काष्ठा era *era)
अणु
	पूर्णांक r;
	काष्ठा bio_list deferred_bios, marked_bios;
	काष्ठा bio *bio;
	काष्ठा blk_plug plug;
	bool commit_needed = false;
	bool failed = false;
	काष्ठा ग_लिखोset *ws = era->md->current_ग_लिखोset;

	bio_list_init(&deferred_bios);
	bio_list_init(&marked_bios);

	spin_lock(&era->deferred_lock);
	bio_list_merge(&deferred_bios, &era->deferred_bios);
	bio_list_init(&era->deferred_bios);
	spin_unlock(&era->deferred_lock);

	अगर (bio_list_empty(&deferred_bios))
		वापस;

	जबतक ((bio = bio_list_pop(&deferred_bios))) अणु
		r = ग_लिखोset_test_and_set(&era->md->bitset_info, ws,
					  get_block(era, bio));
		अगर (r < 0) अणु
			/*
			 * This is bad news, we need to rollback.
			 * FIXME: finish.
			 */
			failed = true;
		पूर्ण अन्यथा अगर (r == 0)
			commit_needed = true;

		bio_list_add(&marked_bios, bio);
	पूर्ण

	अगर (commit_needed) अणु
		r = metadata_commit(era->md);
		अगर (r)
			failed = true;
	पूर्ण

	अगर (failed)
		जबतक ((bio = bio_list_pop(&marked_bios)))
			bio_io_error(bio);
	अन्यथा अणु
		blk_start_plug(&plug);
		जबतक ((bio = bio_list_pop(&marked_bios))) अणु
			/*
			 * Only update the in-core ग_लिखोset अगर the on-disk one
			 * was updated too.
			 */
			अगर (commit_needed)
				set_bit(get_block(era, bio), ws->bits);
			submit_bio_noacct(bio);
		पूर्ण
		blk_finish_plug(&plug);
	पूर्ण
पूर्ण

अटल व्योम process_rpc_calls(काष्ठा era *era)
अणु
	पूर्णांक r;
	bool need_commit = false;
	काष्ठा list_head calls;
	काष्ठा rpc *rpc, *पंचांगp;

	INIT_LIST_HEAD(&calls);
	spin_lock(&era->rpc_lock);
	list_splice_init(&era->rpc_calls, &calls);
	spin_unlock(&era->rpc_lock);

	list_क्रम_each_entry_safe(rpc, पंचांगp, &calls, list) अणु
		rpc->result = rpc->fn0 ? rpc->fn0(era->md) : rpc->fn1(era->md, rpc->arg);
		need_commit = true;
	पूर्ण

	अगर (need_commit) अणु
		r = metadata_commit(era->md);
		अगर (r)
			list_क्रम_each_entry_safe(rpc, पंचांगp, &calls, list)
				rpc->result = r;
	पूर्ण

	list_क्रम_each_entry_safe(rpc, पंचांगp, &calls, list)
		complete(&rpc->complete);
पूर्ण

अटल व्योम kick_off_digest(काष्ठा era *era)
अणु
	अगर (era->md->archived_ग_लिखोsets) अणु
		era->md->archived_ग_लिखोsets = false;
		metadata_digest_start(era->md, &era->digest);
	पूर्ण
पूर्ण

अटल व्योम करो_work(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा era *era = container_of(ws, काष्ठा era, worker);

	kick_off_digest(era);
	process_old_eras(era);
	process_deferred_bios(era);
	process_rpc_calls(era);
पूर्ण

अटल व्योम defer_bio(काष्ठा era *era, काष्ठा bio *bio)
अणु
	spin_lock(&era->deferred_lock);
	bio_list_add(&era->deferred_bios, bio);
	spin_unlock(&era->deferred_lock);

	wake_worker(era);
पूर्ण

/*
 * Make an rpc call to the worker to change the metadata.
 */
अटल पूर्णांक perक्रमm_rpc(काष्ठा era *era, काष्ठा rpc *rpc)
अणु
	rpc->result = 0;
	init_completion(&rpc->complete);

	spin_lock(&era->rpc_lock);
	list_add(&rpc->list, &era->rpc_calls);
	spin_unlock(&era->rpc_lock);

	wake_worker(era);
	रुको_क्रम_completion(&rpc->complete);

	वापस rpc->result;
पूर्ण

अटल पूर्णांक in_worker0(काष्ठा era *era, पूर्णांक (*fn)(काष्ठा era_metadata *))
अणु
	काष्ठा rpc rpc;
	rpc.fn0 = fn;
	rpc.fn1 = शून्य;

	वापस perक्रमm_rpc(era, &rpc);
पूर्ण

अटल पूर्णांक in_worker1(काष्ठा era *era,
		      पूर्णांक (*fn)(काष्ठा era_metadata *, व्योम *), व्योम *arg)
अणु
	काष्ठा rpc rpc;
	rpc.fn0 = शून्य;
	rpc.fn1 = fn;
	rpc.arg = arg;

	वापस perक्रमm_rpc(era, &rpc);
पूर्ण

अटल व्योम start_worker(काष्ठा era *era)
अणु
	atomic_set(&era->suspended, 0);
पूर्ण

अटल व्योम stop_worker(काष्ठा era *era)
अणु
	atomic_set(&era->suspended, 1);
	flush_workqueue(era->wq);
पूर्ण

/*----------------------------------------------------------------
 * Target methods
 *--------------------------------------------------------------*/
अटल व्योम era_destroy(काष्ठा era *era)
अणु
	अगर (era->md)
		metadata_बंद(era->md);

	अगर (era->wq)
		destroy_workqueue(era->wq);

	अगर (era->origin_dev)
		dm_put_device(era->ti, era->origin_dev);

	अगर (era->metadata_dev)
		dm_put_device(era->ti, era->metadata_dev);

	kमुक्त(era);
पूर्ण

अटल dm_block_t calc_nr_blocks(काष्ठा era *era)
अणु
	वापस dm_sector_भाग_up(era->ti->len, era->sectors_per_block);
पूर्ण

अटल bool valid_block_size(dm_block_t block_size)
अणु
	bool greater_than_zero = block_size > 0;
	bool multiple_of_min_block_size = (block_size & (MIN_BLOCK_SIZE - 1)) == 0;

	वापस greater_than_zero && multiple_of_min_block_size;
पूर्ण

/*
 * <metadata dev> <data dev> <data block size (sectors)>
 */
अटल पूर्णांक era_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	पूर्णांक r;
	अक्षर dummy;
	काष्ठा era *era;
	काष्ठा era_metadata *md;

	अगर (argc != 3) अणु
		ti->error = "Invalid argument count";
		वापस -EINVAL;
	पूर्ण

	era = kzalloc(माप(*era), GFP_KERNEL);
	अगर (!era) अणु
		ti->error = "Error allocating era structure";
		वापस -ENOMEM;
	पूर्ण

	era->ti = ti;

	r = dm_get_device(ti, argv[0], FMODE_READ | FMODE_WRITE, &era->metadata_dev);
	अगर (r) अणु
		ti->error = "Error opening metadata device";
		era_destroy(era);
		वापस -EINVAL;
	पूर्ण

	r = dm_get_device(ti, argv[1], FMODE_READ | FMODE_WRITE, &era->origin_dev);
	अगर (r) अणु
		ti->error = "Error opening data device";
		era_destroy(era);
		वापस -EINVAL;
	पूर्ण

	r = माला_पूछो(argv[2], "%u%c", &era->sectors_per_block, &dummy);
	अगर (r != 1) अणु
		ti->error = "Error parsing block size";
		era_destroy(era);
		वापस -EINVAL;
	पूर्ण

	r = dm_set_target_max_io_len(ti, era->sectors_per_block);
	अगर (r) अणु
		ti->error = "could not set max io len";
		era_destroy(era);
		वापस -EINVAL;
	पूर्ण

	अगर (!valid_block_size(era->sectors_per_block)) अणु
		ti->error = "Invalid block size";
		era_destroy(era);
		वापस -EINVAL;
	पूर्ण
	अगर (era->sectors_per_block & (era->sectors_per_block - 1))
		era->sectors_per_block_shअगरt = -1;
	अन्यथा
		era->sectors_per_block_shअगरt = __ffs(era->sectors_per_block);

	md = metadata_खोलो(era->metadata_dev->bdev, era->sectors_per_block, true);
	अगर (IS_ERR(md)) अणु
		ti->error = "Error reading metadata";
		era_destroy(era);
		वापस PTR_ERR(md);
	पूर्ण
	era->md = md;

	era->wq = alloc_ordered_workqueue("dm-" DM_MSG_PREFIX, WQ_MEM_RECLAIM);
	अगर (!era->wq) अणु
		ti->error = "could not create workqueue for metadata object";
		era_destroy(era);
		वापस -ENOMEM;
	पूर्ण
	INIT_WORK(&era->worker, करो_work);

	spin_lock_init(&era->deferred_lock);
	bio_list_init(&era->deferred_bios);

	spin_lock_init(&era->rpc_lock);
	INIT_LIST_HEAD(&era->rpc_calls);

	ti->निजी = era;
	ti->num_flush_bios = 1;
	ti->flush_supported = true;

	ti->num_discard_bios = 1;

	वापस 0;
पूर्ण

अटल व्योम era_dtr(काष्ठा dm_target *ti)
अणु
	era_destroy(ti->निजी);
पूर्ण

अटल पूर्णांक era_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा era *era = ti->निजी;
	dm_block_t block = get_block(era, bio);

	/*
	 * All bios get remapped to the origin device.  We करो this now, but
	 * it may not get issued until later.  Depending on whether the
	 * block is marked in this era.
	 */
	remap_to_origin(era, bio);

	/*
	 * REQ_PREFLUSH bios carry no data, so we're not पूर्णांकerested in them.
	 */
	अगर (!(bio->bi_opf & REQ_PREFLUSH) &&
	    (bio_data_dir(bio) == WRITE) &&
	    !metadata_current_marked(era->md, block)) अणु
		defer_bio(era, bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल व्योम era_postsuspend(काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	काष्ठा era *era = ti->निजी;

	r = in_worker0(era, metadata_era_archive);
	अगर (r) अणु
		DMERR("%s: couldn't archive current era", __func__);
		/* FIXME: fail mode */
	पूर्ण

	stop_worker(era);
पूर्ण

अटल पूर्णांक era_preresume(काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	काष्ठा era *era = ti->निजी;
	dm_block_t new_size = calc_nr_blocks(era);

	अगर (era->nr_blocks != new_size) अणु
		r = metadata_resize(era->md, &new_size);
		अगर (r) अणु
			DMERR("%s: metadata_resize failed", __func__);
			वापस r;
		पूर्ण

		r = metadata_commit(era->md);
		अगर (r) अणु
			DMERR("%s: metadata_commit failed", __func__);
			वापस r;
		पूर्ण

		era->nr_blocks = new_size;
	पूर्ण

	start_worker(era);

	r = in_worker0(era, metadata_era_rollover);
	अगर (r) अणु
		DMERR("%s: metadata_era_rollover failed", __func__);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Status क्रमmat:
 *
 * <metadata block size> <#used metadata blocks>/<#total metadata blocks>
 * <current era> <held metadata root | '-'>
 */
अटल व्योम era_status(काष्ठा dm_target *ti, status_type_t type,
		       अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r;
	काष्ठा era *era = ti->निजी;
	sमाप_प्रकार sz = 0;
	काष्ठा metadata_stats stats;
	अक्षर buf[BDEVNAME_SIZE];

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		r = in_worker1(era, metadata_get_stats, &stats);
		अगर (r)
			जाओ err;

		DMEMIT("%u %llu/%llu %u",
		       (अचिन्हित) (DM_ERA_METADATA_BLOCK_SIZE >> SECTOR_SHIFT),
		       (अचिन्हित दीर्घ दीर्घ) stats.used,
		       (अचिन्हित दीर्घ दीर्घ) stats.total,
		       (अचिन्हित) stats.era);

		अगर (stats.snap != SUPERBLOCK_LOCATION)
			DMEMIT(" %llu", stats.snap);
		अन्यथा
			DMEMIT(" -");
		अवरोध;

	हाल STATUSTYPE_TABLE:
		क्रमmat_dev_t(buf, era->metadata_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);
		क्रमmat_dev_t(buf, era->origin_dev->bdev->bd_dev);
		DMEMIT("%s %u", buf, era->sectors_per_block);
		अवरोध;
	पूर्ण

	वापस;

err:
	DMEMIT("Error");
पूर्ण

अटल पूर्णांक era_message(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
		       अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा era *era = ti->निजी;

	अगर (argc != 1) अणु
		DMERR("incorrect number of message arguments");
		वापस -EINVAL;
	पूर्ण

	अगर (!strहालcmp(argv[0], "checkpoint"))
		वापस in_worker0(era, metadata_checkpoपूर्णांक);

	अगर (!strहालcmp(argv[0], "take_metadata_snap"))
		वापस in_worker0(era, metadata_take_snap);

	अगर (!strहालcmp(argv[0], "drop_metadata_snap"))
		वापस in_worker0(era, metadata_drop_snap);

	DMERR("unsupported message '%s'", argv[0]);
	वापस -EINVAL;
पूर्ण

अटल sector_t get_dev_size(काष्ठा dm_dev *dev)
अणु
	वापस i_size_पढ़ो(dev->bdev->bd_inode) >> SECTOR_SHIFT;
पूर्ण

अटल पूर्णांक era_iterate_devices(काष्ठा dm_target *ti,
			       iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा era *era = ti->निजी;
	वापस fn(ti, era->origin_dev, 0, get_dev_size(era->origin_dev), data);
पूर्ण

अटल व्योम era_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा era *era = ti->निजी;
	uपूर्णांक64_t io_opt_sectors = limits->io_opt >> SECTOR_SHIFT;

	/*
	 * If the प्रणाली-determined stacked limits are compatible with the
	 * era device's blocksize (io_opt is a factor) करो not override them.
	 */
	अगर (io_opt_sectors < era->sectors_per_block ||
	    करो_भाग(io_opt_sectors, era->sectors_per_block)) अणु
		blk_limits_io_min(limits, 0);
		blk_limits_io_opt(limits, era->sectors_per_block << SECTOR_SHIFT);
	पूर्ण
पूर्ण

/*----------------------------------------------------------------*/

अटल काष्ठा target_type era_target = अणु
	.name = "era",
	.version = अणु1, 0, 0पूर्ण,
	.module = THIS_MODULE,
	.ctr = era_ctr,
	.dtr = era_dtr,
	.map = era_map,
	.postsuspend = era_postsuspend,
	.preresume = era_preresume,
	.status = era_status,
	.message = era_message,
	.iterate_devices = era_iterate_devices,
	.io_hपूर्णांकs = era_io_hपूर्णांकs
पूर्ण;

अटल पूर्णांक __init dm_era_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_रेजिस्टर_target(&era_target);
	अगर (r) अणु
		DMERR("era target registration failed: %d", r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास dm_era_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&era_target);
पूर्ण

module_init(dm_era_init);
module_निकास(dm_era_निकास);

MODULE_DESCRIPTION(DM_NAME " era target");
MODULE_AUTHOR("Joe Thornber <ejt@redhat.com>");
MODULE_LICENSE("GPL");
