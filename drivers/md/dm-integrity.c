<शैली गुरु>
/*
 * Copyright (C) 2016-2017 Red Hat, Inc. All rights reserved.
 * Copyright (C) 2016-2017 Milan Broz
 * Copyright (C) 2016-2017 Mikulas Patocka
 *
 * This file is released under the GPL.
 */

#समावेश "dm-bio-record.h"

#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/dm-पन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sort.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/delay.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/reboot.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/async_tx.h>
#समावेश <linux/dm-bufपन.स>

#घोषणा DM_MSG_PREFIX "integrity"

#घोषणा DEFAULT_INTERLEAVE_SECTORS	32768
#घोषणा DEFAULT_JOURNAL_SIZE_FACTOR	7
#घोषणा DEFAULT_SECTORS_PER_BITMAP_BIT	32768
#घोषणा DEFAULT_BUFFER_SECTORS		128
#घोषणा DEFAULT_JOURNAL_WATERMARK	50
#घोषणा DEFAULT_SYNC_MSEC		10000
#घोषणा DEFAULT_MAX_JOURNAL_SECTORS	131072
#घोषणा MIN_LOG2_INTERLEAVE_SECTORS	3
#घोषणा MAX_LOG2_INTERLEAVE_SECTORS	31
#घोषणा METADATA_WORKQUEUE_MAX_ACTIVE	16
#घोषणा RECALC_SECTORS			32768
#घोषणा RECALC_WRITE_SUPER		16
#घोषणा BITMAP_BLOCK_SIZE		4096	/* करोn't change it */
#घोषणा BITMAP_FLUSH_INTERVAL		(10 * HZ)
#घोषणा DISCARD_FILLER			0xf6
#घोषणा SALT_SIZE			16

/*
 * Warning - DEBUG_PRINT prपूर्णांकs security-sensitive data to the log,
 * so it should not be enabled in the official kernel
 */
//#घोषणा DEBUG_PRINT
//#घोषणा INTERNAL_VERIFY

/*
 * On disk काष्ठाures
 */

#घोषणा SB_MAGIC			"integrt"
#घोषणा SB_VERSION_1			1
#घोषणा SB_VERSION_2			2
#घोषणा SB_VERSION_3			3
#घोषणा SB_VERSION_4			4
#घोषणा SB_VERSION_5			5
#घोषणा SB_SECTORS			8
#घोषणा MAX_SECTORS_PER_BLOCK		8

काष्ठा superblock अणु
	__u8 magic[8];
	__u8 version;
	__u8 log2_पूर्णांकerleave_sectors;
	__le16 पूर्णांकegrity_tag_size;
	__le32 journal_sections;
	__le64 provided_data_sectors;	/* userspace uses this value */
	__le32 flags;
	__u8 log2_sectors_per_block;
	__u8 log2_blocks_per_biपंचांगap_bit;
	__u8 pad[2];
	__le64 recalc_sector;
	__u8 pad2[8];
	__u8 salt[SALT_SIZE];
पूर्ण;

#घोषणा SB_FLAG_HAVE_JOURNAL_MAC	0x1
#घोषणा SB_FLAG_RECALCULATING		0x2
#घोषणा SB_FLAG_सूचीTY_BITMAP		0x4
#घोषणा SB_FLAG_FIXED_PADDING		0x8
#घोषणा SB_FLAG_FIXED_HMAC		0x10

#घोषणा	JOURNAL_ENTRY_ROUNDUP		8

प्रकार __le64 commit_id_t;
#घोषणा JOURNAL_MAC_PER_SECTOR		8

काष्ठा journal_entry अणु
	जोड़ अणु
		काष्ठा अणु
			__le32 sector_lo;
			__le32 sector_hi;
		पूर्ण s;
		__le64 sector;
	पूर्ण u;
	commit_id_t last_bytes[];
	/* __u8 tag[0]; */
पूर्ण;

#घोषणा journal_entry_tag(ic, je)		((__u8 *)&(je)->last_bytes[(ic)->sectors_per_block])

#अगर BITS_PER_LONG == 64
#घोषणा journal_entry_set_sector(je, x)		करो अणु smp_wmb(); WRITE_ONCE((je)->u.sector, cpu_to_le64(x)); पूर्ण जबतक (0)
#अन्यथा
#घोषणा journal_entry_set_sector(je, x)		करो अणु (je)->u.s.sector_lo = cpu_to_le32(x); smp_wmb(); WRITE_ONCE((je)->u.s.sector_hi, cpu_to_le32((x) >> 32)); पूर्ण जबतक (0)
#पूर्ण_अगर
#घोषणा journal_entry_get_sector(je)		le64_to_cpu((je)->u.sector)
#घोषणा journal_entry_is_unused(je)		((je)->u.s.sector_hi == cpu_to_le32(-1))
#घोषणा journal_entry_set_unused(je)		करो अणु ((je)->u.s.sector_hi = cpu_to_le32(-1)); पूर्ण जबतक (0)
#घोषणा journal_entry_is_inprogress(je)		((je)->u.s.sector_hi == cpu_to_le32(-2))
#घोषणा journal_entry_set_inprogress(je)	करो अणु ((je)->u.s.sector_hi = cpu_to_le32(-2)); पूर्ण जबतक (0)

#घोषणा JOURNAL_BLOCK_SECTORS		8
#घोषणा JOURNAL_SECTOR_DATA		((1 << SECTOR_SHIFT) - माप(commit_id_t))
#घोषणा JOURNAL_MAC_SIZE		(JOURNAL_MAC_PER_SECTOR * JOURNAL_BLOCK_SECTORS)

काष्ठा journal_sector अणु
	__u8 entries[JOURNAL_SECTOR_DATA - JOURNAL_MAC_PER_SECTOR];
	__u8 mac[JOURNAL_MAC_PER_SECTOR];
	commit_id_t commit_id;
पूर्ण;

#घोषणा MAX_TAG_SIZE			(JOURNAL_SECTOR_DATA - JOURNAL_MAC_PER_SECTOR - दुरत्व(काष्ठा journal_entry, last_bytes[MAX_SECTORS_PER_BLOCK]))

#घोषणा METADATA_PADDING_SECTORS	8

#घोषणा N_COMMIT_IDS			4

अटल अचिन्हित अक्षर prev_commit_seq(अचिन्हित अक्षर seq)
अणु
	वापस (seq + N_COMMIT_IDS - 1) % N_COMMIT_IDS;
पूर्ण

अटल अचिन्हित अक्षर next_commit_seq(अचिन्हित अक्षर seq)
अणु
	वापस (seq + 1) % N_COMMIT_IDS;
पूर्ण

/*
 * In-memory काष्ठाures
 */

काष्ठा journal_node अणु
	काष्ठा rb_node node;
	sector_t sector;
पूर्ण;

काष्ठा alg_spec अणु
	अक्षर *alg_string;
	अक्षर *key_string;
	__u8 *key;
	अचिन्हित key_size;
पूर्ण;

काष्ठा dm_पूर्णांकegrity_c अणु
	काष्ठा dm_dev *dev;
	काष्ठा dm_dev *meta_dev;
	अचिन्हित tag_size;
	__s8 log2_tag_size;
	sector_t start;
	mempool_t journal_io_mempool;
	काष्ठा dm_io_client *io;
	काष्ठा dm_bufio_client *bufio;
	काष्ठा workqueue_काष्ठा *metadata_wq;
	काष्ठा superblock *sb;
	अचिन्हित journal_pages;
	अचिन्हित n_biपंचांगap_blocks;

	काष्ठा page_list *journal;
	काष्ठा page_list *journal_io;
	काष्ठा page_list *journal_xor;
	काष्ठा page_list *recalc_biपंचांगap;
	काष्ठा page_list *may_ग_लिखो_biपंचांगap;
	काष्ठा biपंचांगap_block_status *bbs;
	अचिन्हित biपंचांगap_flush_पूर्णांकerval;
	पूर्णांक synchronous_mode;
	काष्ठा bio_list synchronous_bios;
	काष्ठा delayed_work biपंचांगap_flush_work;

	काष्ठा crypto_skcipher *journal_crypt;
	काष्ठा scatterlist **journal_scatterlist;
	काष्ठा scatterlist **journal_io_scatterlist;
	काष्ठा skcipher_request **sk_requests;

	काष्ठा crypto_shash *journal_mac;

	काष्ठा journal_node *journal_tree;
	काष्ठा rb_root journal_tree_root;

	sector_t provided_data_sectors;

	अचिन्हित लघु journal_entry_size;
	अचिन्हित अक्षर journal_entries_per_sector;
	अचिन्हित अक्षर journal_section_entries;
	अचिन्हित लघु journal_section_sectors;
	अचिन्हित journal_sections;
	अचिन्हित journal_entries;
	sector_t data_device_sectors;
	sector_t meta_device_sectors;
	अचिन्हित initial_sectors;
	अचिन्हित metadata_run;
	__s8 log2_metadata_run;
	__u8 log2_buffer_sectors;
	__u8 sectors_per_block;
	__u8 log2_blocks_per_biपंचांगap_bit;

	अचिन्हित अक्षर mode;

	पूर्णांक failed;

	काष्ठा crypto_shash *पूर्णांकernal_hash;

	काष्ठा dm_target *ti;

	/* these variables are locked with endio_रुको.lock */
	काष्ठा rb_root in_progress;
	काष्ठा list_head रुको_list;
	रुको_queue_head_t endio_रुको;
	काष्ठा workqueue_काष्ठा *रुको_wq;
	काष्ठा workqueue_काष्ठा *offload_wq;

	अचिन्हित अक्षर commit_seq;
	commit_id_t commit_ids[N_COMMIT_IDS];

	अचिन्हित committed_section;
	अचिन्हित n_committed_sections;

	अचिन्हित uncommitted_section;
	अचिन्हित n_uncommitted_sections;

	अचिन्हित मुक्त_section;
	अचिन्हित अक्षर मुक्त_section_entry;
	अचिन्हित मुक्त_sectors;

	अचिन्हित मुक्त_sectors_threshold;

	काष्ठा workqueue_काष्ठा *commit_wq;
	काष्ठा work_काष्ठा commit_work;

	काष्ठा workqueue_काष्ठा *ग_लिखोr_wq;
	काष्ठा work_काष्ठा ग_लिखोr_work;

	काष्ठा workqueue_काष्ठा *recalc_wq;
	काष्ठा work_काष्ठा recalc_work;
	u8 *recalc_buffer;
	u8 *recalc_tags;

	काष्ठा bio_list flush_bio_list;

	अचिन्हित दीर्घ स्वतःcommit_jअगरfies;
	काष्ठा समयr_list स्वतःcommit_समयr;
	अचिन्हित स्वतःcommit_msec;

	रुको_queue_head_t copy_to_journal_रुको;

	काष्ठा completion crypto_backoff;

	bool journal_uptodate;
	bool just_क्रमmatted;
	bool recalculate_flag;
	bool reset_recalculate_flag;
	bool discard;
	bool fix_padding;
	bool fix_hmac;
	bool legacy_recalculate;

	काष्ठा alg_spec पूर्णांकernal_hash_alg;
	काष्ठा alg_spec journal_crypt_alg;
	काष्ठा alg_spec journal_mac_alg;

	atomic64_t number_of_mismatches;

	काष्ठा notअगरier_block reboot_notअगरier;
पूर्ण;

काष्ठा dm_पूर्णांकegrity_range अणु
	sector_t logical_sector;
	sector_t n_sectors;
	bool रुकोing;
	जोड़ अणु
		काष्ठा rb_node node;
		काष्ठा अणु
			काष्ठा task_काष्ठा *task;
			काष्ठा list_head रुको_entry;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा dm_पूर्णांकegrity_io अणु
	काष्ठा work_काष्ठा work;

	काष्ठा dm_पूर्णांकegrity_c *ic;
	क्रमागत req_opf op;
	bool fua;

	काष्ठा dm_पूर्णांकegrity_range range;

	sector_t metadata_block;
	अचिन्हित metadata_offset;

	atomic_t in_flight;
	blk_status_t bi_status;

	काष्ठा completion *completion;

	काष्ठा dm_bio_details bio_details;
पूर्ण;

काष्ठा journal_completion अणु
	काष्ठा dm_पूर्णांकegrity_c *ic;
	atomic_t in_flight;
	काष्ठा completion comp;
पूर्ण;

काष्ठा journal_io अणु
	काष्ठा dm_पूर्णांकegrity_range range;
	काष्ठा journal_completion *comp;
पूर्ण;

काष्ठा biपंचांगap_block_status अणु
	काष्ठा work_काष्ठा work;
	काष्ठा dm_पूर्णांकegrity_c *ic;
	अचिन्हित idx;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा bio_list bio_queue;
	spinlock_t bio_queue_lock;

पूर्ण;

अटल काष्ठा kmem_cache *journal_io_cache;

#घोषणा JOURNAL_IO_MEMPOOL	32

#अगर_घोषित DEBUG_PRINT
#घोषणा DEBUG_prपूर्णांक(x, ...)	prपूर्णांकk(KERN_DEBUG x, ##__VA_ARGS__)
अटल व्योम __DEBUG_bytes(__u8 *bytes, माप_प्रकार len, स्थिर अक्षर *msg, ...)
अणु
	बहु_सूची args;
	बहु_शुरू(args, msg);
	vprपूर्णांकk(msg, args);
	बहु_पूर्ण(args);
	अगर (len)
		pr_cont(":");
	जबतक (len) अणु
		pr_cont(" %02x", *bytes);
		bytes++;
		len--;
	पूर्ण
	pr_cont("\n");
पूर्ण
#घोषणा DEBUG_bytes(bytes, len, msg, ...)	__DEBUG_bytes(bytes, len, KERN_DEBUG msg, ##__VA_ARGS__)
#अन्यथा
#घोषणा DEBUG_prपूर्णांक(x, ...)			करो अणु पूर्ण जबतक (0)
#घोषणा DEBUG_bytes(bytes, len, msg, ...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम dm_पूर्णांकegrity_prepare(काष्ठा request *rq)
अणु
पूर्ण

अटल व्योम dm_पूर्णांकegrity_complete(काष्ठा request *rq, अचिन्हित पूर्णांक nr_bytes)
अणु
पूर्ण

/*
 * DM Integrity profile, protection is perक्रमmed layer above (dm-crypt)
 */
अटल स्थिर काष्ठा blk_पूर्णांकegrity_profile dm_पूर्णांकegrity_profile = अणु
	.name			= "DM-DIF-EXT-TAG",
	.generate_fn		= शून्य,
	.verअगरy_fn		= शून्य,
	.prepare_fn		= dm_पूर्णांकegrity_prepare,
	.complete_fn		= dm_पूर्णांकegrity_complete,
पूर्ण;

अटल व्योम dm_पूर्णांकegrity_map_जारी(काष्ठा dm_पूर्णांकegrity_io *dio, bool from_map);
अटल व्योम पूर्णांकegrity_bio_रुको(काष्ठा work_काष्ठा *w);
अटल व्योम dm_पूर्णांकegrity_dtr(काष्ठा dm_target *ti);

अटल व्योम dm_पूर्णांकegrity_io_error(काष्ठा dm_पूर्णांकegrity_c *ic, स्थिर अक्षर *msg, पूर्णांक err)
अणु
	अगर (err == -EILSEQ)
		atomic64_inc(&ic->number_of_mismatches);
	अगर (!cmpxchg(&ic->failed, 0, err))
		DMERR("Error on %s: %d", msg, err);
पूर्ण

अटल पूर्णांक dm_पूर्णांकegrity_failed(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	वापस READ_ONCE(ic->failed);
पूर्ण

अटल bool dm_पूर्णांकegrity_disable_recalculate(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	अगर (ic->legacy_recalculate)
		वापस false;
	अगर (!(ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_HMAC)) ?
	    ic->पूर्णांकernal_hash_alg.key || ic->journal_mac_alg.key :
	    ic->पूर्णांकernal_hash_alg.key && !ic->journal_mac_alg.key)
		वापस true;
	वापस false;
पूर्ण

अटल commit_id_t dm_पूर्णांकegrity_commit_id(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित i,
					  अचिन्हित j, अचिन्हित अक्षर seq)
अणु
	/*
	 * Xor the number with section and sector, so that अगर a piece of
	 * journal is written at wrong place, it is detected.
	 */
	वापस ic->commit_ids[seq] ^ cpu_to_le64(((__u64)i << 32) ^ j);
पूर्ण

अटल व्योम get_area_and_offset(काष्ठा dm_पूर्णांकegrity_c *ic, sector_t data_sector,
				sector_t *area, sector_t *offset)
अणु
	अगर (!ic->meta_dev) अणु
		__u8 log2_पूर्णांकerleave_sectors = ic->sb->log2_पूर्णांकerleave_sectors;
		*area = data_sector >> log2_पूर्णांकerleave_sectors;
		*offset = (अचिन्हित)data_sector & ((1U << log2_पूर्णांकerleave_sectors) - 1);
	पूर्ण अन्यथा अणु
		*area = 0;
		*offset = data_sector;
	पूर्ण
पूर्ण

#घोषणा sector_to_block(ic, n)						\
करो अणु									\
	BUG_ON((n) & (अचिन्हित)((ic)->sectors_per_block - 1));		\
	(n) >>= (ic)->sb->log2_sectors_per_block;			\
पूर्ण जबतक (0)

अटल __u64 get_metadata_sector_and_offset(काष्ठा dm_पूर्णांकegrity_c *ic, sector_t area,
					    sector_t offset, अचिन्हित *metadata_offset)
अणु
	__u64 ms;
	अचिन्हित mo;

	ms = area << ic->sb->log2_पूर्णांकerleave_sectors;
	अगर (likely(ic->log2_metadata_run >= 0))
		ms += area << ic->log2_metadata_run;
	अन्यथा
		ms += area * ic->metadata_run;
	ms >>= ic->log2_buffer_sectors;

	sector_to_block(ic, offset);

	अगर (likely(ic->log2_tag_size >= 0)) अणु
		ms += offset >> (SECTOR_SHIFT + ic->log2_buffer_sectors - ic->log2_tag_size);
		mo = (offset << ic->log2_tag_size) & ((1U << SECTOR_SHIFT << ic->log2_buffer_sectors) - 1);
	पूर्ण अन्यथा अणु
		ms += (__u64)offset * ic->tag_size >> (SECTOR_SHIFT + ic->log2_buffer_sectors);
		mo = (offset * ic->tag_size) & ((1U << SECTOR_SHIFT << ic->log2_buffer_sectors) - 1);
	पूर्ण
	*metadata_offset = mo;
	वापस ms;
पूर्ण

अटल sector_t get_data_sector(काष्ठा dm_पूर्णांकegrity_c *ic, sector_t area, sector_t offset)
अणु
	sector_t result;

	अगर (ic->meta_dev)
		वापस offset;

	result = area << ic->sb->log2_पूर्णांकerleave_sectors;
	अगर (likely(ic->log2_metadata_run >= 0))
		result += (area + 1) << ic->log2_metadata_run;
	अन्यथा
		result += (area + 1) * ic->metadata_run;

	result += (sector_t)ic->initial_sectors + offset;
	result += ic->start;

	वापस result;
पूर्ण

अटल व्योम wraparound_section(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित *sec_ptr)
अणु
	अगर (unlikely(*sec_ptr >= ic->journal_sections))
		*sec_ptr -= ic->journal_sections;
पूर्ण

अटल व्योम sb_set_version(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_HMAC))
		ic->sb->version = SB_VERSION_5;
	अन्यथा अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_PADDING))
		ic->sb->version = SB_VERSION_4;
	अन्यथा अगर (ic->mode == 'B' || ic->sb->flags & cpu_to_le32(SB_FLAG_सूचीTY_BITMAP))
		ic->sb->version = SB_VERSION_3;
	अन्यथा अगर (ic->meta_dev || ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING))
		ic->sb->version = SB_VERSION_2;
	अन्यथा
		ic->sb->version = SB_VERSION_1;
पूर्ण

अटल पूर्णांक sb_mac(काष्ठा dm_पूर्णांकegrity_c *ic, bool wr)
अणु
	SHASH_DESC_ON_STACK(desc, ic->journal_mac);
	पूर्णांक r;
	अचिन्हित size = crypto_shash_digestsize(ic->journal_mac);

	अगर (माप(काष्ठा superblock) + size > 1 << SECTOR_SHIFT) अणु
		dm_पूर्णांकegrity_io_error(ic, "digest is too long", -EINVAL);
		वापस -EINVAL;
	पूर्ण

	desc->tfm = ic->journal_mac;

	r = crypto_shash_init(desc);
	अगर (unlikely(r < 0)) अणु
		dm_पूर्णांकegrity_io_error(ic, "crypto_shash_init", r);
		वापस r;
	पूर्ण

	r = crypto_shash_update(desc, (__u8 *)ic->sb, (1 << SECTOR_SHIFT) - size);
	अगर (unlikely(r < 0)) अणु
		dm_पूर्णांकegrity_io_error(ic, "crypto_shash_update", r);
		वापस r;
	पूर्ण

	अगर (likely(wr)) अणु
		r = crypto_shash_final(desc, (__u8 *)ic->sb + (1 << SECTOR_SHIFT) - size);
		अगर (unlikely(r < 0)) अणु
			dm_पूर्णांकegrity_io_error(ic, "crypto_shash_final", r);
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अणु
		__u8 result[HASH_MAX_DIGESTSIZE];
		r = crypto_shash_final(desc, result);
		अगर (unlikely(r < 0)) अणु
			dm_पूर्णांकegrity_io_error(ic, "crypto_shash_final", r);
			वापस r;
		पूर्ण
		अगर (स_भेद((__u8 *)ic->sb + (1 << SECTOR_SHIFT) - size, result, size)) अणु
			dm_पूर्णांकegrity_io_error(ic, "superblock mac", -EILSEQ);
			वापस -EILSEQ;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sync_rw_sb(काष्ठा dm_पूर्णांकegrity_c *ic, पूर्णांक op, पूर्णांक op_flags)
अणु
	काष्ठा dm_io_request io_req;
	काष्ठा dm_io_region io_loc;
	पूर्णांक r;

	io_req.bi_op = op;
	io_req.bi_op_flags = op_flags;
	io_req.mem.type = DM_IO_KMEM;
	io_req.mem.ptr.addr = ic->sb;
	io_req.notअगरy.fn = शून्य;
	io_req.client = ic->io;
	io_loc.bdev = ic->meta_dev ? ic->meta_dev->bdev : ic->dev->bdev;
	io_loc.sector = ic->start;
	io_loc.count = SB_SECTORS;

	अगर (op == REQ_OP_WRITE) अणु
		sb_set_version(ic);
		अगर (ic->journal_mac && ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_HMAC)) अणु
			r = sb_mac(ic, true);
			अगर (unlikely(r))
				वापस r;
		पूर्ण
	पूर्ण

	r = dm_io(&io_req, 1, &io_loc, शून्य);
	अगर (unlikely(r))
		वापस r;

	अगर (op == REQ_OP_READ) अणु
		अगर (ic->mode != 'R' && ic->journal_mac && ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_HMAC)) अणु
			r = sb_mac(ic, false);
			अगर (unlikely(r))
				वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा BITMAP_OP_TEST_ALL_SET		0
#घोषणा BITMAP_OP_TEST_ALL_CLEAR	1
#घोषणा BITMAP_OP_SET			2
#घोषणा BITMAP_OP_CLEAR			3

अटल bool block_biपंचांगap_op(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा page_list *biपंचांगap,
			    sector_t sector, sector_t n_sectors, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ bit, end_bit, this_end_bit, page, end_page;
	अचिन्हित दीर्घ *data;

	अगर (unlikely(((sector | n_sectors) & ((1 << ic->sb->log2_sectors_per_block) - 1)) != 0)) अणु
		DMCRIT("invalid bitmap access (%llx,%llx,%d,%d,%d)",
			sector,
			n_sectors,
			ic->sb->log2_sectors_per_block,
			ic->log2_blocks_per_biपंचांगap_bit,
			mode);
		BUG();
	पूर्ण

	अगर (unlikely(!n_sectors))
		वापस true;

	bit = sector >> (ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit);
	end_bit = (sector + n_sectors - 1) >>
		(ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit);

	page = bit / (PAGE_SIZE * 8);
	bit %= PAGE_SIZE * 8;

	end_page = end_bit / (PAGE_SIZE * 8);
	end_bit %= PAGE_SIZE * 8;

repeat:
	अगर (page < end_page) अणु
		this_end_bit = PAGE_SIZE * 8 - 1;
	पूर्ण अन्यथा अणु
		this_end_bit = end_bit;
	पूर्ण

	data = lowmem_page_address(biपंचांगap[page].page);

	अगर (mode == BITMAP_OP_TEST_ALL_SET) अणु
		जबतक (bit <= this_end_bit) अणु
			अगर (!(bit % BITS_PER_LONG) && this_end_bit >= bit + BITS_PER_LONG - 1) अणु
				करो अणु
					अगर (data[bit / BITS_PER_LONG] != -1)
						वापस false;
					bit += BITS_PER_LONG;
				पूर्ण जबतक (this_end_bit >= bit + BITS_PER_LONG - 1);
				जारी;
			पूर्ण
			अगर (!test_bit(bit, data))
				वापस false;
			bit++;
		पूर्ण
	पूर्ण अन्यथा अगर (mode == BITMAP_OP_TEST_ALL_CLEAR) अणु
		जबतक (bit <= this_end_bit) अणु
			अगर (!(bit % BITS_PER_LONG) && this_end_bit >= bit + BITS_PER_LONG - 1) अणु
				करो अणु
					अगर (data[bit / BITS_PER_LONG] != 0)
						वापस false;
					bit += BITS_PER_LONG;
				पूर्ण जबतक (this_end_bit >= bit + BITS_PER_LONG - 1);
				जारी;
			पूर्ण
			अगर (test_bit(bit, data))
				वापस false;
			bit++;
		पूर्ण
	पूर्ण अन्यथा अगर (mode == BITMAP_OP_SET) अणु
		जबतक (bit <= this_end_bit) अणु
			अगर (!(bit % BITS_PER_LONG) && this_end_bit >= bit + BITS_PER_LONG - 1) अणु
				करो अणु
					data[bit / BITS_PER_LONG] = -1;
					bit += BITS_PER_LONG;
				पूर्ण जबतक (this_end_bit >= bit + BITS_PER_LONG - 1);
				जारी;
			पूर्ण
			__set_bit(bit, data);
			bit++;
		पूर्ण
	पूर्ण अन्यथा अगर (mode == BITMAP_OP_CLEAR) अणु
		अगर (!bit && this_end_bit == PAGE_SIZE * 8 - 1)
			clear_page(data);
		अन्यथा जबतक (bit <= this_end_bit) अणु
			अगर (!(bit % BITS_PER_LONG) && this_end_bit >= bit + BITS_PER_LONG - 1) अणु
				करो अणु
					data[bit / BITS_PER_LONG] = 0;
					bit += BITS_PER_LONG;
				पूर्ण जबतक (this_end_bit >= bit + BITS_PER_LONG - 1);
				जारी;
			पूर्ण
			__clear_bit(bit, data);
			bit++;
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	अगर (unlikely(page < end_page)) अणु
		bit = 0;
		page++;
		जाओ repeat;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम block_biपंचांगap_copy(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा page_list *dst, काष्ठा page_list *src)
अणु
	अचिन्हित n_biपंचांगap_pages = DIV_ROUND_UP(ic->n_biपंचांगap_blocks, PAGE_SIZE / BITMAP_BLOCK_SIZE);
	अचिन्हित i;

	क्रम (i = 0; i < n_biपंचांगap_pages; i++) अणु
		अचिन्हित दीर्घ *dst_data = lowmem_page_address(dst[i].page);
		अचिन्हित दीर्घ *src_data = lowmem_page_address(src[i].page);
		copy_page(dst_data, src_data);
	पूर्ण
पूर्ण

अटल काष्ठा biपंचांगap_block_status *sector_to_biपंचांगap_block(काष्ठा dm_पूर्णांकegrity_c *ic, sector_t sector)
अणु
	अचिन्हित bit = sector >> (ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit);
	अचिन्हित biपंचांगap_block = bit / (BITMAP_BLOCK_SIZE * 8);

	BUG_ON(biपंचांगap_block >= ic->n_biपंचांगap_blocks);
	वापस &ic->bbs[biपंचांगap_block];
पूर्ण

अटल व्योम access_journal_check(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित section, अचिन्हित offset,
				 bool e, स्थिर अक्षर *function)
अणु
#अगर defined(CONFIG_DM_DEBUG) || defined(INTERNAL_VERIFY)
	अचिन्हित limit = e ? ic->journal_section_entries : ic->journal_section_sectors;

	अगर (unlikely(section >= ic->journal_sections) ||
	    unlikely(offset >= limit)) अणु
		DMCRIT("%s: invalid access at (%u,%u), limit (%u,%u)",
		       function, section, offset, ic->journal_sections, limit);
		BUG();
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम page_list_location(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित section, अचिन्हित offset,
			       अचिन्हित *pl_index, अचिन्हित *pl_offset)
अणु
	अचिन्हित sector;

	access_journal_check(ic, section, offset, false, "page_list_location");

	sector = section * ic->journal_section_sectors + offset;

	*pl_index = sector >> (PAGE_SHIFT - SECTOR_SHIFT);
	*pl_offset = (sector << SECTOR_SHIFT) & (PAGE_SIZE - 1);
पूर्ण

अटल काष्ठा journal_sector *access_page_list(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा page_list *pl,
					       अचिन्हित section, अचिन्हित offset, अचिन्हित *n_sectors)
अणु
	अचिन्हित pl_index, pl_offset;
	अक्षर *va;

	page_list_location(ic, section, offset, &pl_index, &pl_offset);

	अगर (n_sectors)
		*n_sectors = (PAGE_SIZE - pl_offset) >> SECTOR_SHIFT;

	va = lowmem_page_address(pl[pl_index].page);

	वापस (काष्ठा journal_sector *)(va + pl_offset);
पूर्ण

अटल काष्ठा journal_sector *access_journal(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित section, अचिन्हित offset)
अणु
	वापस access_page_list(ic, ic->journal, section, offset, शून्य);
पूर्ण

अटल काष्ठा journal_entry *access_journal_entry(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित section, अचिन्हित n)
अणु
	अचिन्हित rel_sector, offset;
	काष्ठा journal_sector *js;

	access_journal_check(ic, section, n, true, "access_journal_entry");

	rel_sector = n % JOURNAL_BLOCK_SECTORS;
	offset = n / JOURNAL_BLOCK_SECTORS;

	js = access_journal(ic, section, rel_sector);
	वापस (काष्ठा journal_entry *)((अक्षर *)js + offset * ic->journal_entry_size);
पूर्ण

अटल काष्ठा journal_sector *access_journal_data(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित section, अचिन्हित n)
अणु
	n <<= ic->sb->log2_sectors_per_block;

	n += JOURNAL_BLOCK_SECTORS;

	access_journal_check(ic, section, n, false, "access_journal_data");

	वापस access_journal(ic, section, n);
पूर्ण

अटल व्योम section_mac(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित section, __u8 result[JOURNAL_MAC_SIZE])
अणु
	SHASH_DESC_ON_STACK(desc, ic->journal_mac);
	पूर्णांक r;
	अचिन्हित j, size;

	desc->tfm = ic->journal_mac;

	r = crypto_shash_init(desc);
	अगर (unlikely(r < 0)) अणु
		dm_पूर्णांकegrity_io_error(ic, "crypto_shash_init", r);
		जाओ err;
	पूर्ण

	अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_HMAC)) अणु
		__le64 section_le;

		r = crypto_shash_update(desc, (__u8 *)&ic->sb->salt, SALT_SIZE);
		अगर (unlikely(r < 0)) अणु
			dm_पूर्णांकegrity_io_error(ic, "crypto_shash_update", r);
			जाओ err;
		पूर्ण

		section_le = cpu_to_le64(section);
		r = crypto_shash_update(desc, (__u8 *)&section_le, माप section_le);
		अगर (unlikely(r < 0)) अणु
			dm_पूर्णांकegrity_io_error(ic, "crypto_shash_update", r);
			जाओ err;
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < ic->journal_section_entries; j++) अणु
		काष्ठा journal_entry *je = access_journal_entry(ic, section, j);
		r = crypto_shash_update(desc, (__u8 *)&je->u.sector, माप je->u.sector);
		अगर (unlikely(r < 0)) अणु
			dm_पूर्णांकegrity_io_error(ic, "crypto_shash_update", r);
			जाओ err;
		पूर्ण
	पूर्ण

	size = crypto_shash_digestsize(ic->journal_mac);

	अगर (likely(size <= JOURNAL_MAC_SIZE)) अणु
		r = crypto_shash_final(desc, result);
		अगर (unlikely(r < 0)) अणु
			dm_पूर्णांकegrity_io_error(ic, "crypto_shash_final", r);
			जाओ err;
		पूर्ण
		स_रखो(result + size, 0, JOURNAL_MAC_SIZE - size);
	पूर्ण अन्यथा अणु
		__u8 digest[HASH_MAX_DIGESTSIZE];

		अगर (WARN_ON(size > माप(digest))) अणु
			dm_पूर्णांकegrity_io_error(ic, "digest_size", -EINVAL);
			जाओ err;
		पूर्ण
		r = crypto_shash_final(desc, digest);
		अगर (unlikely(r < 0)) अणु
			dm_पूर्णांकegrity_io_error(ic, "crypto_shash_final", r);
			जाओ err;
		पूर्ण
		स_नकल(result, digest, JOURNAL_MAC_SIZE);
	पूर्ण

	वापस;
err:
	स_रखो(result, 0, JOURNAL_MAC_SIZE);
पूर्ण

अटल व्योम rw_section_mac(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित section, bool wr)
अणु
	__u8 result[JOURNAL_MAC_SIZE];
	अचिन्हित j;

	अगर (!ic->journal_mac)
		वापस;

	section_mac(ic, section, result);

	क्रम (j = 0; j < JOURNAL_BLOCK_SECTORS; j++) अणु
		काष्ठा journal_sector *js = access_journal(ic, section, j);

		अगर (likely(wr))
			स_नकल(&js->mac, result + (j * JOURNAL_MAC_PER_SECTOR), JOURNAL_MAC_PER_SECTOR);
		अन्यथा अणु
			अगर (स_भेद(&js->mac, result + (j * JOURNAL_MAC_PER_SECTOR), JOURNAL_MAC_PER_SECTOR))
				dm_पूर्णांकegrity_io_error(ic, "journal mac", -EILSEQ);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम complete_journal_op(व्योम *context)
अणु
	काष्ठा journal_completion *comp = context;
	BUG_ON(!atomic_पढ़ो(&comp->in_flight));
	अगर (likely(atomic_dec_and_test(&comp->in_flight)))
		complete(&comp->comp);
पूर्ण

अटल व्योम xor_journal(काष्ठा dm_पूर्णांकegrity_c *ic, bool encrypt, अचिन्हित section,
			अचिन्हित n_sections, काष्ठा journal_completion *comp)
अणु
	काष्ठा async_submit_ctl submit;
	माप_प्रकार n_bytes = (माप_प्रकार)(n_sections * ic->journal_section_sectors) << SECTOR_SHIFT;
	अचिन्हित pl_index, pl_offset, section_index;
	काष्ठा page_list *source_pl, *target_pl;

	अगर (likely(encrypt)) अणु
		source_pl = ic->journal;
		target_pl = ic->journal_io;
	पूर्ण अन्यथा अणु
		source_pl = ic->journal_io;
		target_pl = ic->journal;
	पूर्ण

	page_list_location(ic, section, 0, &pl_index, &pl_offset);

	atomic_add(roundup(pl_offset + n_bytes, PAGE_SIZE) >> PAGE_SHIFT, &comp->in_flight);

	init_async_submit(&submit, ASYNC_TX_XOR_ZERO_DST, शून्य, complete_journal_op, comp, शून्य);

	section_index = pl_index;

	करो अणु
		माप_प्रकार this_step;
		काष्ठा page *src_pages[2];
		काष्ठा page *dst_page;

		जबतक (unlikely(pl_index == section_index)) अणु
			अचिन्हित dummy;
			अगर (likely(encrypt))
				rw_section_mac(ic, section, true);
			section++;
			n_sections--;
			अगर (!n_sections)
				अवरोध;
			page_list_location(ic, section, 0, &section_index, &dummy);
		पूर्ण

		this_step = min(n_bytes, (माप_प्रकार)PAGE_SIZE - pl_offset);
		dst_page = target_pl[pl_index].page;
		src_pages[0] = source_pl[pl_index].page;
		src_pages[1] = ic->journal_xor[pl_index].page;

		async_xor(dst_page, src_pages, pl_offset, 2, this_step, &submit);

		pl_index++;
		pl_offset = 0;
		n_bytes -= this_step;
	पूर्ण जबतक (n_bytes);

	BUG_ON(n_sections);

	async_tx_issue_pending_all();
पूर्ण

अटल व्योम complete_journal_encrypt(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा journal_completion *comp = req->data;
	अगर (unlikely(err)) अणु
		अगर (likely(err == -EINPROGRESS)) अणु
			complete(&comp->ic->crypto_backoff);
			वापस;
		पूर्ण
		dm_पूर्णांकegrity_io_error(comp->ic, "asynchronous encrypt", err);
	पूर्ण
	complete_journal_op(comp);
पूर्ण

अटल bool करो_crypt(bool encrypt, काष्ठा skcipher_request *req, काष्ठा journal_completion *comp)
अणु
	पूर्णांक r;
	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				      complete_journal_encrypt, comp);
	अगर (likely(encrypt))
		r = crypto_skcipher_encrypt(req);
	अन्यथा
		r = crypto_skcipher_decrypt(req);
	अगर (likely(!r))
		वापस false;
	अगर (likely(r == -EINPROGRESS))
		वापस true;
	अगर (likely(r == -EBUSY)) अणु
		रुको_क्रम_completion(&comp->ic->crypto_backoff);
		reinit_completion(&comp->ic->crypto_backoff);
		वापस true;
	पूर्ण
	dm_पूर्णांकegrity_io_error(comp->ic, "encrypt", r);
	वापस false;
पूर्ण

अटल व्योम crypt_journal(काष्ठा dm_पूर्णांकegrity_c *ic, bool encrypt, अचिन्हित section,
			  अचिन्हित n_sections, काष्ठा journal_completion *comp)
अणु
	काष्ठा scatterlist **source_sg;
	काष्ठा scatterlist **target_sg;

	atomic_add(2, &comp->in_flight);

	अगर (likely(encrypt)) अणु
		source_sg = ic->journal_scatterlist;
		target_sg = ic->journal_io_scatterlist;
	पूर्ण अन्यथा अणु
		source_sg = ic->journal_io_scatterlist;
		target_sg = ic->journal_scatterlist;
	पूर्ण

	करो अणु
		काष्ठा skcipher_request *req;
		अचिन्हित ivsize;
		अक्षर *iv;

		अगर (likely(encrypt))
			rw_section_mac(ic, section, true);

		req = ic->sk_requests[section];
		ivsize = crypto_skcipher_ivsize(ic->journal_crypt);
		iv = req->iv;

		स_नकल(iv, iv + ivsize, ivsize);

		req->src = source_sg[section];
		req->dst = target_sg[section];

		अगर (unlikely(करो_crypt(encrypt, req, comp)))
			atomic_inc(&comp->in_flight);

		section++;
		n_sections--;
	पूर्ण जबतक (n_sections);

	atomic_dec(&comp->in_flight);
	complete_journal_op(comp);
पूर्ण

अटल व्योम encrypt_journal(काष्ठा dm_पूर्णांकegrity_c *ic, bool encrypt, अचिन्हित section,
			    अचिन्हित n_sections, काष्ठा journal_completion *comp)
अणु
	अगर (ic->journal_xor)
		वापस xor_journal(ic, encrypt, section, n_sections, comp);
	अन्यथा
		वापस crypt_journal(ic, encrypt, section, n_sections, comp);
पूर्ण

अटल व्योम complete_journal_io(अचिन्हित दीर्घ error, व्योम *context)
अणु
	काष्ठा journal_completion *comp = context;
	अगर (unlikely(error != 0))
		dm_पूर्णांकegrity_io_error(comp->ic, "writing journal", -EIO);
	complete_journal_op(comp);
पूर्ण

अटल व्योम rw_journal_sectors(काष्ठा dm_पूर्णांकegrity_c *ic, पूर्णांक op, पूर्णांक op_flags,
			       अचिन्हित sector, अचिन्हित n_sectors, काष्ठा journal_completion *comp)
अणु
	काष्ठा dm_io_request io_req;
	काष्ठा dm_io_region io_loc;
	अचिन्हित pl_index, pl_offset;
	पूर्णांक r;

	अगर (unlikely(dm_पूर्णांकegrity_failed(ic))) अणु
		अगर (comp)
			complete_journal_io(-1UL, comp);
		वापस;
	पूर्ण

	pl_index = sector >> (PAGE_SHIFT - SECTOR_SHIFT);
	pl_offset = (sector << SECTOR_SHIFT) & (PAGE_SIZE - 1);

	io_req.bi_op = op;
	io_req.bi_op_flags = op_flags;
	io_req.mem.type = DM_IO_PAGE_LIST;
	अगर (ic->journal_io)
		io_req.mem.ptr.pl = &ic->journal_io[pl_index];
	अन्यथा
		io_req.mem.ptr.pl = &ic->journal[pl_index];
	io_req.mem.offset = pl_offset;
	अगर (likely(comp != शून्य)) अणु
		io_req.notअगरy.fn = complete_journal_io;
		io_req.notअगरy.context = comp;
	पूर्ण अन्यथा अणु
		io_req.notअगरy.fn = शून्य;
	पूर्ण
	io_req.client = ic->io;
	io_loc.bdev = ic->meta_dev ? ic->meta_dev->bdev : ic->dev->bdev;
	io_loc.sector = ic->start + SB_SECTORS + sector;
	io_loc.count = n_sectors;

	r = dm_io(&io_req, 1, &io_loc, शून्य);
	अगर (unlikely(r)) अणु
		dm_पूर्णांकegrity_io_error(ic, op == REQ_OP_READ ? "reading journal" : "writing journal", r);
		अगर (comp) अणु
			WARN_ONCE(1, "asynchronous dm_io failed: %d", r);
			complete_journal_io(-1UL, comp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rw_journal(काष्ठा dm_पूर्णांकegrity_c *ic, पूर्णांक op, पूर्णांक op_flags, अचिन्हित section,
		       अचिन्हित n_sections, काष्ठा journal_completion *comp)
अणु
	अचिन्हित sector, n_sectors;

	sector = section * ic->journal_section_sectors;
	n_sectors = n_sections * ic->journal_section_sectors;

	rw_journal_sectors(ic, op, op_flags, sector, n_sectors, comp);
पूर्ण

अटल व्योम ग_लिखो_journal(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित commit_start, अचिन्हित commit_sections)
अणु
	काष्ठा journal_completion io_comp;
	काष्ठा journal_completion crypt_comp_1;
	काष्ठा journal_completion crypt_comp_2;
	अचिन्हित i;

	io_comp.ic = ic;
	init_completion(&io_comp.comp);

	अगर (commit_start + commit_sections <= ic->journal_sections) अणु
		io_comp.in_flight = (atomic_t)ATOMIC_INIT(1);
		अगर (ic->journal_io) अणु
			crypt_comp_1.ic = ic;
			init_completion(&crypt_comp_1.comp);
			crypt_comp_1.in_flight = (atomic_t)ATOMIC_INIT(0);
			encrypt_journal(ic, true, commit_start, commit_sections, &crypt_comp_1);
			रुको_क्रम_completion_io(&crypt_comp_1.comp);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < commit_sections; i++)
				rw_section_mac(ic, commit_start + i, true);
		पूर्ण
		rw_journal(ic, REQ_OP_WRITE, REQ_FUA | REQ_SYNC, commit_start,
			   commit_sections, &io_comp);
	पूर्ण अन्यथा अणु
		अचिन्हित to_end;
		io_comp.in_flight = (atomic_t)ATOMIC_INIT(2);
		to_end = ic->journal_sections - commit_start;
		अगर (ic->journal_io) अणु
			crypt_comp_1.ic = ic;
			init_completion(&crypt_comp_1.comp);
			crypt_comp_1.in_flight = (atomic_t)ATOMIC_INIT(0);
			encrypt_journal(ic, true, commit_start, to_end, &crypt_comp_1);
			अगर (try_रुको_क्रम_completion(&crypt_comp_1.comp)) अणु
				rw_journal(ic, REQ_OP_WRITE, REQ_FUA, commit_start, to_end, &io_comp);
				reinit_completion(&crypt_comp_1.comp);
				crypt_comp_1.in_flight = (atomic_t)ATOMIC_INIT(0);
				encrypt_journal(ic, true, 0, commit_sections - to_end, &crypt_comp_1);
				रुको_क्रम_completion_io(&crypt_comp_1.comp);
			पूर्ण अन्यथा अणु
				crypt_comp_2.ic = ic;
				init_completion(&crypt_comp_2.comp);
				crypt_comp_2.in_flight = (atomic_t)ATOMIC_INIT(0);
				encrypt_journal(ic, true, 0, commit_sections - to_end, &crypt_comp_2);
				रुको_क्रम_completion_io(&crypt_comp_1.comp);
				rw_journal(ic, REQ_OP_WRITE, REQ_FUA, commit_start, to_end, &io_comp);
				रुको_क्रम_completion_io(&crypt_comp_2.comp);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < to_end; i++)
				rw_section_mac(ic, commit_start + i, true);
			rw_journal(ic, REQ_OP_WRITE, REQ_FUA, commit_start, to_end, &io_comp);
			क्रम (i = 0; i < commit_sections - to_end; i++)
				rw_section_mac(ic, i, true);
		पूर्ण
		rw_journal(ic, REQ_OP_WRITE, REQ_FUA, 0, commit_sections - to_end, &io_comp);
	पूर्ण

	रुको_क्रम_completion_io(&io_comp.comp);
पूर्ण

अटल व्योम copy_from_journal(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित section, अचिन्हित offset,
			      अचिन्हित n_sectors, sector_t target, io_notअगरy_fn fn, व्योम *data)
अणु
	काष्ठा dm_io_request io_req;
	काष्ठा dm_io_region io_loc;
	पूर्णांक r;
	अचिन्हित sector, pl_index, pl_offset;

	BUG_ON((target | n_sectors | offset) & (अचिन्हित)(ic->sectors_per_block - 1));

	अगर (unlikely(dm_पूर्णांकegrity_failed(ic))) अणु
		fn(-1UL, data);
		वापस;
	पूर्ण

	sector = section * ic->journal_section_sectors + JOURNAL_BLOCK_SECTORS + offset;

	pl_index = sector >> (PAGE_SHIFT - SECTOR_SHIFT);
	pl_offset = (sector << SECTOR_SHIFT) & (PAGE_SIZE - 1);

	io_req.bi_op = REQ_OP_WRITE;
	io_req.bi_op_flags = 0;
	io_req.mem.type = DM_IO_PAGE_LIST;
	io_req.mem.ptr.pl = &ic->journal[pl_index];
	io_req.mem.offset = pl_offset;
	io_req.notअगरy.fn = fn;
	io_req.notअगरy.context = data;
	io_req.client = ic->io;
	io_loc.bdev = ic->dev->bdev;
	io_loc.sector = target;
	io_loc.count = n_sectors;

	r = dm_io(&io_req, 1, &io_loc, शून्य);
	अगर (unlikely(r)) अणु
		WARN_ONCE(1, "asynchronous dm_io failed: %d", r);
		fn(-1UL, data);
	पूर्ण
पूर्ण

अटल bool ranges_overlap(काष्ठा dm_पूर्णांकegrity_range *range1, काष्ठा dm_पूर्णांकegrity_range *range2)
अणु
	वापस range1->logical_sector < range2->logical_sector + range2->n_sectors &&
	       range1->logical_sector + range1->n_sectors > range2->logical_sector;
पूर्ण

अटल bool add_new_range(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा dm_पूर्णांकegrity_range *new_range, bool check_रुकोing)
अणु
	काष्ठा rb_node **n = &ic->in_progress.rb_node;
	काष्ठा rb_node *parent;

	BUG_ON((new_range->logical_sector | new_range->n_sectors) & (अचिन्हित)(ic->sectors_per_block - 1));

	अगर (likely(check_रुकोing)) अणु
		काष्ठा dm_पूर्णांकegrity_range *range;
		list_क्रम_each_entry(range, &ic->रुको_list, रुको_entry) अणु
			अगर (unlikely(ranges_overlap(range, new_range)))
				वापस false;
		पूर्ण
	पूर्ण

	parent = शून्य;

	जबतक (*n) अणु
		काष्ठा dm_पूर्णांकegrity_range *range = container_of(*n, काष्ठा dm_पूर्णांकegrity_range, node);

		parent = *n;
		अगर (new_range->logical_sector + new_range->n_sectors <= range->logical_sector) अणु
			n = &range->node.rb_left;
		पूर्ण अन्यथा अगर (new_range->logical_sector >= range->logical_sector + range->n_sectors) अणु
			n = &range->node.rb_right;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण

	rb_link_node(&new_range->node, parent, n);
	rb_insert_color(&new_range->node, &ic->in_progress);

	वापस true;
पूर्ण

अटल व्योम हटाओ_range_unlocked(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा dm_पूर्णांकegrity_range *range)
अणु
	rb_erase(&range->node, &ic->in_progress);
	जबतक (unlikely(!list_empty(&ic->रुको_list))) अणु
		काष्ठा dm_पूर्णांकegrity_range *last_range =
			list_first_entry(&ic->रुको_list, काष्ठा dm_पूर्णांकegrity_range, रुको_entry);
		काष्ठा task_काष्ठा *last_range_task;
		last_range_task = last_range->task;
		list_del(&last_range->रुको_entry);
		अगर (!add_new_range(ic, last_range, false)) अणु
			last_range->task = last_range_task;
			list_add(&last_range->रुको_entry, &ic->रुको_list);
			अवरोध;
		पूर्ण
		last_range->रुकोing = false;
		wake_up_process(last_range_task);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_range(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा dm_पूर्णांकegrity_range *range)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ic->endio_रुको.lock, flags);
	हटाओ_range_unlocked(ic, range);
	spin_unlock_irqrestore(&ic->endio_रुको.lock, flags);
पूर्ण

अटल व्योम रुको_and_add_new_range(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा dm_पूर्णांकegrity_range *new_range)
अणु
	new_range->रुकोing = true;
	list_add_tail(&new_range->रुको_entry, &ic->रुको_list);
	new_range->task = current;
	करो अणु
		__set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&ic->endio_रुको.lock);
		io_schedule();
		spin_lock_irq(&ic->endio_रुको.lock);
	पूर्ण जबतक (unlikely(new_range->रुकोing));
पूर्ण

अटल व्योम add_new_range_and_रुको(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा dm_पूर्णांकegrity_range *new_range)
अणु
	अगर (unlikely(!add_new_range(ic, new_range, true)))
		रुको_and_add_new_range(ic, new_range);
पूर्ण

अटल व्योम init_journal_node(काष्ठा journal_node *node)
अणु
	RB_CLEAR_NODE(&node->node);
	node->sector = (sector_t)-1;
पूर्ण

अटल व्योम add_journal_node(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा journal_node *node, sector_t sector)
अणु
	काष्ठा rb_node **link;
	काष्ठा rb_node *parent;

	node->sector = sector;
	BUG_ON(!RB_EMPTY_NODE(&node->node));

	link = &ic->journal_tree_root.rb_node;
	parent = शून्य;

	जबतक (*link) अणु
		काष्ठा journal_node *j;
		parent = *link;
		j = container_of(parent, काष्ठा journal_node, node);
		अगर (sector < j->sector)
			link = &j->node.rb_left;
		अन्यथा
			link = &j->node.rb_right;
	पूर्ण

	rb_link_node(&node->node, parent, link);
	rb_insert_color(&node->node, &ic->journal_tree_root);
पूर्ण

अटल व्योम हटाओ_journal_node(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा journal_node *node)
अणु
	BUG_ON(RB_EMPTY_NODE(&node->node));
	rb_erase(&node->node, &ic->journal_tree_root);
	init_journal_node(node);
पूर्ण

#घोषणा NOT_FOUND	(-1U)

अटल अचिन्हित find_journal_node(काष्ठा dm_पूर्णांकegrity_c *ic, sector_t sector, sector_t *next_sector)
अणु
	काष्ठा rb_node *n = ic->journal_tree_root.rb_node;
	अचिन्हित found = NOT_FOUND;
	*next_sector = (sector_t)-1;
	जबतक (n) अणु
		काष्ठा journal_node *j = container_of(n, काष्ठा journal_node, node);
		अगर (sector == j->sector) अणु
			found = j - ic->journal_tree;
		पूर्ण
		अगर (sector < j->sector) अणु
			*next_sector = j->sector;
			n = j->node.rb_left;
		पूर्ण अन्यथा अणु
			n = j->node.rb_right;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल bool test_journal_node(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित pos, sector_t sector)
अणु
	काष्ठा journal_node *node, *next_node;
	काष्ठा rb_node *next;

	अगर (unlikely(pos >= ic->journal_entries))
		वापस false;
	node = &ic->journal_tree[pos];
	अगर (unlikely(RB_EMPTY_NODE(&node->node)))
		वापस false;
	अगर (unlikely(node->sector != sector))
		वापस false;

	next = rb_next(&node->node);
	अगर (unlikely(!next))
		वापस true;

	next_node = container_of(next, काष्ठा journal_node, node);
	वापस next_node->sector != sector;
पूर्ण

अटल bool find_newer_committed_node(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा journal_node *node)
अणु
	काष्ठा rb_node *next;
	काष्ठा journal_node *next_node;
	अचिन्हित next_section;

	BUG_ON(RB_EMPTY_NODE(&node->node));

	next = rb_next(&node->node);
	अगर (unlikely(!next))
		वापस false;

	next_node = container_of(next, काष्ठा journal_node, node);

	अगर (next_node->sector != node->sector)
		वापस false;

	next_section = (अचिन्हित)(next_node - ic->journal_tree) / ic->journal_section_entries;
	अगर (next_section >= ic->committed_section &&
	    next_section < ic->committed_section + ic->n_committed_sections)
		वापस true;
	अगर (next_section + ic->journal_sections < ic->committed_section + ic->n_committed_sections)
		वापस true;

	वापस false;
पूर्ण

#घोषणा TAG_READ	0
#घोषणा TAG_WRITE	1
#घोषणा TAG_CMP		2

अटल पूर्णांक dm_पूर्णांकegrity_rw_tag(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित अक्षर *tag, sector_t *metadata_block,
			       अचिन्हित *metadata_offset, अचिन्हित total_size, पूर्णांक op)
अणु
#घोषणा MAY_BE_FILLER		1
#घोषणा MAY_BE_HASH		2
	अचिन्हित hash_offset = 0;
	अचिन्हित may_be = MAY_BE_HASH | (ic->discard ? MAY_BE_FILLER : 0);

	करो अणु
		अचिन्हित अक्षर *data, *dp;
		काष्ठा dm_buffer *b;
		अचिन्हित to_copy;
		पूर्णांक r;

		r = dm_पूर्णांकegrity_failed(ic);
		अगर (unlikely(r))
			वापस r;

		data = dm_bufio_पढ़ो(ic->bufio, *metadata_block, &b);
		अगर (IS_ERR(data))
			वापस PTR_ERR(data);

		to_copy = min((1U << SECTOR_SHIFT << ic->log2_buffer_sectors) - *metadata_offset, total_size);
		dp = data + *metadata_offset;
		अगर (op == TAG_READ) अणु
			स_नकल(tag, dp, to_copy);
		पूर्ण अन्यथा अगर (op == TAG_WRITE) अणु
			अगर (स_भेद(dp, tag, to_copy)) अणु
				स_नकल(dp, tag, to_copy);
				dm_bufio_mark_partial_buffer_dirty(b, *metadata_offset, *metadata_offset + to_copy);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* e.g.: op == TAG_CMP */

			अगर (likely(is_घातer_of_2(ic->tag_size))) अणु
				अगर (unlikely(स_भेद(dp, tag, to_copy)))
					अगर (unlikely(!ic->discard) ||
					    unlikely(स_प्रथम_inv(dp, DISCARD_FILLER, to_copy) != शून्य)) अणु
						जाओ thorough_test;
				पूर्ण
			पूर्ण अन्यथा अणु
				अचिन्हित i, ts;
thorough_test:
				ts = total_size;

				क्रम (i = 0; i < to_copy; i++, ts--) अणु
					अगर (unlikely(dp[i] != tag[i]))
						may_be &= ~MAY_BE_HASH;
					अगर (likely(dp[i] != DISCARD_FILLER))
						may_be &= ~MAY_BE_FILLER;
					hash_offset++;
					अगर (unlikely(hash_offset == ic->tag_size)) अणु
						अगर (unlikely(!may_be)) अणु
							dm_bufio_release(b);
							वापस ts;
						पूर्ण
						hash_offset = 0;
						may_be = MAY_BE_HASH | (ic->discard ? MAY_BE_FILLER : 0);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		dm_bufio_release(b);

		tag += to_copy;
		*metadata_offset += to_copy;
		अगर (unlikely(*metadata_offset == 1U << SECTOR_SHIFT << ic->log2_buffer_sectors)) अणु
			(*metadata_block)++;
			*metadata_offset = 0;
		पूर्ण

		अगर (unlikely(!is_घातer_of_2(ic->tag_size))) अणु
			hash_offset = (hash_offset + to_copy) % ic->tag_size;
		पूर्ण

		total_size -= to_copy;
	पूर्ण जबतक (unlikely(total_size));

	वापस 0;
#अघोषित MAY_BE_FILLER
#अघोषित MAY_BE_HASH
पूर्ण

काष्ठा flush_request अणु
	काष्ठा dm_io_request io_req;
	काष्ठा dm_io_region io_reg;
	काष्ठा dm_पूर्णांकegrity_c *ic;
	काष्ठा completion comp;
पूर्ण;

अटल व्योम flush_notअगरy(अचिन्हित दीर्घ error, व्योम *fr_)
अणु
	काष्ठा flush_request *fr = fr_;
	अगर (unlikely(error != 0))
		dm_पूर्णांकegrity_io_error(fr->ic, "flushing disk cache", -EIO);
	complete(&fr->comp);
पूर्ण

अटल व्योम dm_पूर्णांकegrity_flush_buffers(काष्ठा dm_पूर्णांकegrity_c *ic, bool flush_data)
अणु
	पूर्णांक r;

	काष्ठा flush_request fr;

	अगर (!ic->meta_dev)
		flush_data = false;
	अगर (flush_data) अणु
		fr.io_req.bi_op = REQ_OP_WRITE,
		fr.io_req.bi_op_flags = REQ_PREFLUSH | REQ_SYNC,
		fr.io_req.mem.type = DM_IO_KMEM,
		fr.io_req.mem.ptr.addr = शून्य,
		fr.io_req.notअगरy.fn = flush_notअगरy,
		fr.io_req.notअगरy.context = &fr;
		fr.io_req.client = dm_bufio_get_dm_io_client(ic->bufio),
		fr.io_reg.bdev = ic->dev->bdev,
		fr.io_reg.sector = 0,
		fr.io_reg.count = 0,
		fr.ic = ic;
		init_completion(&fr.comp);
		r = dm_io(&fr.io_req, 1, &fr.io_reg, शून्य);
		BUG_ON(r);
	पूर्ण

	r = dm_bufio_ग_लिखो_dirty_buffers(ic->bufio);
	अगर (unlikely(r))
		dm_पूर्णांकegrity_io_error(ic, "writing tags", r);

	अगर (flush_data)
		रुको_क्रम_completion(&fr.comp);
पूर्ण

अटल व्योम sleep_on_endio_रुको(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	__add_रुको_queue(&ic->endio_रुको, &रुको);
	__set_current_state(TASK_UNINTERRUPTIBLE);
	spin_unlock_irq(&ic->endio_रुको.lock);
	io_schedule();
	spin_lock_irq(&ic->endio_रुको.lock);
	__हटाओ_रुको_queue(&ic->endio_रुको, &रुको);
पूर्ण

अटल व्योम स्वतःcommit_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = from_समयr(ic, t, स्वतःcommit_समयr);

	अगर (likely(!dm_पूर्णांकegrity_failed(ic)))
		queue_work(ic->commit_wq, &ic->commit_work);
पूर्ण

अटल व्योम schedule_स्वतःcommit(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	अगर (!समयr_pending(&ic->स्वतःcommit_समयr))
		mod_समयr(&ic->स्वतःcommit_समयr, jअगरfies + ic->स्वतःcommit_jअगरfies);
पूर्ण

अटल व्योम submit_flush_bio(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा dm_पूर्णांकegrity_io *dio)
अणु
	काष्ठा bio *bio;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ic->endio_रुको.lock, flags);
	bio = dm_bio_from_per_bio_data(dio, माप(काष्ठा dm_पूर्णांकegrity_io));
	bio_list_add(&ic->flush_bio_list, bio);
	spin_unlock_irqrestore(&ic->endio_रुको.lock, flags);

	queue_work(ic->commit_wq, &ic->commit_work);
पूर्ण

अटल व्योम करो_endio(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा bio *bio)
अणु
	पूर्णांक r = dm_पूर्णांकegrity_failed(ic);
	अगर (unlikely(r) && !bio->bi_status)
		bio->bi_status = त्रुटि_सं_to_blk_status(r);
	अगर (unlikely(ic->synchronous_mode) && bio_op(bio) == REQ_OP_WRITE) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&ic->endio_रुको.lock, flags);
		bio_list_add(&ic->synchronous_bios, bio);
		queue_delayed_work(ic->commit_wq, &ic->biपंचांगap_flush_work, 0);
		spin_unlock_irqrestore(&ic->endio_रुको.lock, flags);
		वापस;
	पूर्ण
	bio_endio(bio);
पूर्ण

अटल व्योम करो_endio_flush(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा dm_पूर्णांकegrity_io *dio)
अणु
	काष्ठा bio *bio = dm_bio_from_per_bio_data(dio, माप(काष्ठा dm_पूर्णांकegrity_io));

	अगर (unlikely(dio->fua) && likely(!bio->bi_status) && likely(!dm_पूर्णांकegrity_failed(ic)))
		submit_flush_bio(ic, dio);
	अन्यथा
		करो_endio(ic, bio);
पूर्ण

अटल व्योम dec_in_flight(काष्ठा dm_पूर्णांकegrity_io *dio)
अणु
	अगर (atomic_dec_and_test(&dio->in_flight)) अणु
		काष्ठा dm_पूर्णांकegrity_c *ic = dio->ic;
		काष्ठा bio *bio;

		हटाओ_range(ic, &dio->range);

		अगर (dio->op == REQ_OP_WRITE || unlikely(dio->op == REQ_OP_DISCARD))
			schedule_स्वतःcommit(ic);

		bio = dm_bio_from_per_bio_data(dio, माप(काष्ठा dm_पूर्णांकegrity_io));

		अगर (unlikely(dio->bi_status) && !bio->bi_status)
			bio->bi_status = dio->bi_status;
		अगर (likely(!bio->bi_status) && unlikely(bio_sectors(bio) != dio->range.n_sectors)) अणु
			dio->range.logical_sector += dio->range.n_sectors;
			bio_advance(bio, dio->range.n_sectors << SECTOR_SHIFT);
			INIT_WORK(&dio->work, पूर्णांकegrity_bio_रुको);
			queue_work(ic->offload_wq, &dio->work);
			वापस;
		पूर्ण
		करो_endio_flush(ic, dio);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकegrity_end_io(काष्ठा bio *bio)
अणु
	काष्ठा dm_पूर्णांकegrity_io *dio = dm_per_bio_data(bio, माप(काष्ठा dm_पूर्णांकegrity_io));

	dm_bio_restore(&dio->bio_details, bio);
	अगर (bio->bi_पूर्णांकegrity)
		bio->bi_opf |= REQ_INTEGRITY;

	अगर (dio->completion)
		complete(dio->completion);

	dec_in_flight(dio);
पूर्ण

अटल व्योम पूर्णांकegrity_sector_checksum(काष्ठा dm_पूर्णांकegrity_c *ic, sector_t sector,
				      स्थिर अक्षर *data, अक्षर *result)
अणु
	__le64 sector_le = cpu_to_le64(sector);
	SHASH_DESC_ON_STACK(req, ic->पूर्णांकernal_hash);
	पूर्णांक r;
	अचिन्हित digest_size;

	req->tfm = ic->पूर्णांकernal_hash;

	r = crypto_shash_init(req);
	अगर (unlikely(r < 0)) अणु
		dm_पूर्णांकegrity_io_error(ic, "crypto_shash_init", r);
		जाओ failed;
	पूर्ण

	अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_HMAC)) अणु
		r = crypto_shash_update(req, (__u8 *)&ic->sb->salt, SALT_SIZE);
		अगर (unlikely(r < 0)) अणु
			dm_पूर्णांकegrity_io_error(ic, "crypto_shash_update", r);
			जाओ failed;
		पूर्ण
	पूर्ण

	r = crypto_shash_update(req, (स्थिर __u8 *)&sector_le, माप sector_le);
	अगर (unlikely(r < 0)) अणु
		dm_पूर्णांकegrity_io_error(ic, "crypto_shash_update", r);
		जाओ failed;
	पूर्ण

	r = crypto_shash_update(req, data, ic->sectors_per_block << SECTOR_SHIFT);
	अगर (unlikely(r < 0)) अणु
		dm_पूर्णांकegrity_io_error(ic, "crypto_shash_update", r);
		जाओ failed;
	पूर्ण

	r = crypto_shash_final(req, result);
	अगर (unlikely(r < 0)) अणु
		dm_पूर्णांकegrity_io_error(ic, "crypto_shash_final", r);
		जाओ failed;
	पूर्ण

	digest_size = crypto_shash_digestsize(ic->पूर्णांकernal_hash);
	अगर (unlikely(digest_size < ic->tag_size))
		स_रखो(result + digest_size, 0, ic->tag_size - digest_size);

	वापस;

failed:
	/* this shouldn't happen anyway, the hash functions have no reason to fail */
	get_अक्रमom_bytes(result, ic->tag_size);
पूर्ण

अटल व्योम पूर्णांकegrity_metadata(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dm_पूर्णांकegrity_io *dio = container_of(w, काष्ठा dm_पूर्णांकegrity_io, work);
	काष्ठा dm_पूर्णांकegrity_c *ic = dio->ic;

	पूर्णांक r;

	अगर (ic->पूर्णांकernal_hash) अणु
		काष्ठा bvec_iter iter;
		काष्ठा bio_vec bv;
		अचिन्हित digest_size = crypto_shash_digestsize(ic->पूर्णांकernal_hash);
		काष्ठा bio *bio = dm_bio_from_per_bio_data(dio, माप(काष्ठा dm_पूर्णांकegrity_io));
		अक्षर *checksums;
		अचिन्हित extra_space = unlikely(digest_size > ic->tag_size) ? digest_size - ic->tag_size : 0;
		अक्षर checksums_onstack[max((माप_प्रकार)HASH_MAX_DIGESTSIZE, MAX_TAG_SIZE)];
		sector_t sector;
		अचिन्हित sectors_to_process;

		अगर (unlikely(ic->mode == 'R'))
			जाओ skip_io;

		अगर (likely(dio->op != REQ_OP_DISCARD))
			checksums = kदो_स्मृति((PAGE_SIZE >> SECTOR_SHIFT >> ic->sb->log2_sectors_per_block) * ic->tag_size + extra_space,
					    GFP_NOIO | __GFP_NORETRY | __GFP_NOWARN);
		अन्यथा
			checksums = kदो_स्मृति(PAGE_SIZE, GFP_NOIO | __GFP_NORETRY | __GFP_NOWARN);
		अगर (!checksums) अणु
			checksums = checksums_onstack;
			अगर (WARN_ON(extra_space &&
				    digest_size > माप(checksums_onstack))) अणु
				r = -EINVAL;
				जाओ error;
			पूर्ण
		पूर्ण

		अगर (unlikely(dio->op == REQ_OP_DISCARD)) अणु
			sector_t bi_sector = dio->bio_details.bi_iter.bi_sector;
			अचिन्हित bi_size = dio->bio_details.bi_iter.bi_size;
			अचिन्हित max_size = likely(checksums != checksums_onstack) ? PAGE_SIZE : HASH_MAX_DIGESTSIZE;
			अचिन्हित max_blocks = max_size / ic->tag_size;
			स_रखो(checksums, DISCARD_FILLER, max_size);

			जबतक (bi_size) अणु
				अचिन्हित this_step_blocks = bi_size >> (SECTOR_SHIFT + ic->sb->log2_sectors_per_block);
				this_step_blocks = min(this_step_blocks, max_blocks);
				r = dm_पूर्णांकegrity_rw_tag(ic, checksums, &dio->metadata_block, &dio->metadata_offset,
							this_step_blocks * ic->tag_size, TAG_WRITE);
				अगर (unlikely(r)) अणु
					अगर (likely(checksums != checksums_onstack))
						kमुक्त(checksums);
					जाओ error;
				पूर्ण

				/*अगर (bi_size < this_step_blocks << (SECTOR_SHIFT + ic->sb->log2_sectors_per_block)) अणु
					prपूर्णांकk("BUGG: bi_sector: %llx, bi_size: %u\n", bi_sector, bi_size);
					prपूर्णांकk("BUGG: this_step_blocks: %u\n", this_step_blocks);
					BUG();
				पूर्ण*/
				bi_size -= this_step_blocks << (SECTOR_SHIFT + ic->sb->log2_sectors_per_block);
				bi_sector += this_step_blocks << ic->sb->log2_sectors_per_block;
			पूर्ण

			अगर (likely(checksums != checksums_onstack))
				kमुक्त(checksums);
			जाओ skip_io;
		पूर्ण

		sector = dio->range.logical_sector;
		sectors_to_process = dio->range.n_sectors;

		__bio_क्रम_each_segment(bv, bio, iter, dio->bio_details.bi_iter) अणु
			अचिन्हित pos;
			अक्षर *mem, *checksums_ptr;

again:
			mem = (अक्षर *)kmap_atomic(bv.bv_page) + bv.bv_offset;
			pos = 0;
			checksums_ptr = checksums;
			करो अणु
				पूर्णांकegrity_sector_checksum(ic, sector, mem + pos, checksums_ptr);
				checksums_ptr += ic->tag_size;
				sectors_to_process -= ic->sectors_per_block;
				pos += ic->sectors_per_block << SECTOR_SHIFT;
				sector += ic->sectors_per_block;
			पूर्ण जबतक (pos < bv.bv_len && sectors_to_process && checksums != checksums_onstack);
			kunmap_atomic(mem);

			r = dm_पूर्णांकegrity_rw_tag(ic, checksums, &dio->metadata_block, &dio->metadata_offset,
						checksums_ptr - checksums, dio->op == REQ_OP_READ ? TAG_CMP : TAG_WRITE);
			अगर (unlikely(r)) अणु
				अगर (r > 0) अणु
					अक्षर b[BDEVNAME_SIZE];
					DMERR_LIMIT("%s: Checksum failed at sector 0x%llx", bio_devname(bio, b),
						    (sector - ((r + ic->tag_size - 1) / ic->tag_size)));
					r = -EILSEQ;
					atomic64_inc(&ic->number_of_mismatches);
				पूर्ण
				अगर (likely(checksums != checksums_onstack))
					kमुक्त(checksums);
				जाओ error;
			पूर्ण

			अगर (!sectors_to_process)
				अवरोध;

			अगर (unlikely(pos < bv.bv_len)) अणु
				bv.bv_offset += pos;
				bv.bv_len -= pos;
				जाओ again;
			पूर्ण
		पूर्ण

		अगर (likely(checksums != checksums_onstack))
			kमुक्त(checksums);
	पूर्ण अन्यथा अणु
		काष्ठा bio_पूर्णांकegrity_payload *bip = dio->bio_details.bi_पूर्णांकegrity;

		अगर (bip) अणु
			काष्ठा bio_vec biv;
			काष्ठा bvec_iter iter;
			अचिन्हित data_to_process = dio->range.n_sectors;
			sector_to_block(ic, data_to_process);
			data_to_process *= ic->tag_size;

			bip_क्रम_each_vec(biv, bip, iter) अणु
				अचिन्हित अक्षर *tag;
				अचिन्हित this_len;

				BUG_ON(PageHighMem(biv.bv_page));
				tag = lowmem_page_address(biv.bv_page) + biv.bv_offset;
				this_len = min(biv.bv_len, data_to_process);
				r = dm_पूर्णांकegrity_rw_tag(ic, tag, &dio->metadata_block, &dio->metadata_offset,
							this_len, dio->op == REQ_OP_READ ? TAG_READ : TAG_WRITE);
				अगर (unlikely(r))
					जाओ error;
				data_to_process -= this_len;
				अगर (!data_to_process)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
skip_io:
	dec_in_flight(dio);
	वापस;
error:
	dio->bi_status = त्रुटि_सं_to_blk_status(r);
	dec_in_flight(dio);
पूर्ण

अटल पूर्णांक dm_पूर्णांकegrity_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = ti->निजी;
	काष्ठा dm_पूर्णांकegrity_io *dio = dm_per_bio_data(bio, माप(काष्ठा dm_पूर्णांकegrity_io));
	काष्ठा bio_पूर्णांकegrity_payload *bip;

	sector_t area, offset;

	dio->ic = ic;
	dio->bi_status = 0;
	dio->op = bio_op(bio);

	अगर (unlikely(dio->op == REQ_OP_DISCARD)) अणु
		अगर (ti->max_io_len) अणु
			sector_t sec = dm_target_offset(ti, bio->bi_iter.bi_sector);
			अचिन्हित log2_max_io_len = __fls(ti->max_io_len);
			sector_t start_boundary = sec >> log2_max_io_len;
			sector_t end_boundary = (sec + bio_sectors(bio) - 1) >> log2_max_io_len;
			अगर (start_boundary < end_boundary) अणु
				sector_t len = ti->max_io_len - (sec & (ti->max_io_len - 1));
				dm_accept_partial_bio(bio, len);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH)) अणु
		submit_flush_bio(ic, dio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	dio->range.logical_sector = dm_target_offset(ti, bio->bi_iter.bi_sector);
	dio->fua = dio->op == REQ_OP_WRITE && bio->bi_opf & REQ_FUA;
	अगर (unlikely(dio->fua)) अणु
		/*
		 * Don't pass करोwn the FUA flag because we have to flush
		 * disk cache anyway.
		 */
		bio->bi_opf &= ~REQ_FUA;
	पूर्ण
	अगर (unlikely(dio->range.logical_sector + bio_sectors(bio) > ic->provided_data_sectors)) अणु
		DMERR("Too big sector number: 0x%llx + 0x%x > 0x%llx",
		      dio->range.logical_sector, bio_sectors(bio),
		      ic->provided_data_sectors);
		वापस DM_MAPIO_KILL;
	पूर्ण
	अगर (unlikely((dio->range.logical_sector | bio_sectors(bio)) & (अचिन्हित)(ic->sectors_per_block - 1))) अणु
		DMERR("Bio not aligned on %u sectors: 0x%llx, 0x%x",
		      ic->sectors_per_block,
		      dio->range.logical_sector, bio_sectors(bio));
		वापस DM_MAPIO_KILL;
	पूर्ण

	अगर (ic->sectors_per_block > 1 && likely(dio->op != REQ_OP_DISCARD)) अणु
		काष्ठा bvec_iter iter;
		काष्ठा bio_vec bv;
		bio_क्रम_each_segment(bv, bio, iter) अणु
			अगर (unlikely(bv.bv_len & ((ic->sectors_per_block << SECTOR_SHIFT) - 1))) अणु
				DMERR("Bio vector (%u,%u) is not aligned on %u-sector boundary",
					bv.bv_offset, bv.bv_len, ic->sectors_per_block);
				वापस DM_MAPIO_KILL;
			पूर्ण
		पूर्ण
	पूर्ण

	bip = bio_पूर्णांकegrity(bio);
	अगर (!ic->पूर्णांकernal_hash) अणु
		अगर (bip) अणु
			अचिन्हित wanted_tag_size = bio_sectors(bio) >> ic->sb->log2_sectors_per_block;
			अगर (ic->log2_tag_size >= 0)
				wanted_tag_size <<= ic->log2_tag_size;
			अन्यथा
				wanted_tag_size *= ic->tag_size;
			अगर (unlikely(wanted_tag_size != bip->bip_iter.bi_size)) अणु
				DMERR("Invalid integrity data size %u, expected %u",
				      bip->bip_iter.bi_size, wanted_tag_size);
				वापस DM_MAPIO_KILL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(bip != शून्य)) अणु
			DMERR("Unexpected integrity data when using internal hash");
			वापस DM_MAPIO_KILL;
		पूर्ण
	पूर्ण

	अगर (unlikely(ic->mode == 'R') && unlikely(dio->op != REQ_OP_READ))
		वापस DM_MAPIO_KILL;

	get_area_and_offset(ic, dio->range.logical_sector, &area, &offset);
	dio->metadata_block = get_metadata_sector_and_offset(ic, area, offset, &dio->metadata_offset);
	bio->bi_iter.bi_sector = get_data_sector(ic, area, offset);

	dm_पूर्णांकegrity_map_जारी(dio, true);
	वापस DM_MAPIO_SUBMITTED;
पूर्ण

अटल bool __journal_पढ़ो_ग_लिखो(काष्ठा dm_पूर्णांकegrity_io *dio, काष्ठा bio *bio,
				 अचिन्हित journal_section, अचिन्हित journal_entry)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = dio->ic;
	sector_t logical_sector;
	अचिन्हित n_sectors;

	logical_sector = dio->range.logical_sector;
	n_sectors = dio->range.n_sectors;
	करो अणु
		काष्ठा bio_vec bv = bio_iovec(bio);
		अक्षर *mem;

		अगर (unlikely(bv.bv_len >> SECTOR_SHIFT > n_sectors))
			bv.bv_len = n_sectors << SECTOR_SHIFT;
		n_sectors -= bv.bv_len >> SECTOR_SHIFT;
		bio_advance_iter(bio, &bio->bi_iter, bv.bv_len);
retry_kmap:
		mem = kmap_atomic(bv.bv_page);
		अगर (likely(dio->op == REQ_OP_WRITE))
			flush_dcache_page(bv.bv_page);

		करो अणु
			काष्ठा journal_entry *je = access_journal_entry(ic, journal_section, journal_entry);

			अगर (unlikely(dio->op == REQ_OP_READ)) अणु
				काष्ठा journal_sector *js;
				अक्षर *mem_ptr;
				अचिन्हित s;

				अगर (unlikely(journal_entry_is_inprogress(je))) अणु
					flush_dcache_page(bv.bv_page);
					kunmap_atomic(mem);

					__io_रुको_event(ic->copy_to_journal_रुको, !journal_entry_is_inprogress(je));
					जाओ retry_kmap;
				पूर्ण
				smp_rmb();
				BUG_ON(journal_entry_get_sector(je) != logical_sector);
				js = access_journal_data(ic, journal_section, journal_entry);
				mem_ptr = mem + bv.bv_offset;
				s = 0;
				करो अणु
					स_नकल(mem_ptr, js, JOURNAL_SECTOR_DATA);
					*(commit_id_t *)(mem_ptr + JOURNAL_SECTOR_DATA) = je->last_bytes[s];
					js++;
					mem_ptr += 1 << SECTOR_SHIFT;
				पूर्ण जबतक (++s < ic->sectors_per_block);
#अगर_घोषित INTERNAL_VERIFY
				अगर (ic->पूर्णांकernal_hash) अणु
					अक्षर checksums_onstack[max((माप_प्रकार)HASH_MAX_DIGESTSIZE, MAX_TAG_SIZE)];

					पूर्णांकegrity_sector_checksum(ic, logical_sector, mem + bv.bv_offset, checksums_onstack);
					अगर (unlikely(स_भेद(checksums_onstack, journal_entry_tag(ic, je), ic->tag_size))) अणु
						DMERR_LIMIT("Checksum failed when reading from journal, at sector 0x%llx",
							    logical_sector);
					पूर्ण
				पूर्ण
#पूर्ण_अगर
			पूर्ण

			अगर (!ic->पूर्णांकernal_hash) अणु
				काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
				अचिन्हित tag_toकरो = ic->tag_size;
				अक्षर *tag_ptr = journal_entry_tag(ic, je);

				अगर (bip) करो अणु
					काष्ठा bio_vec biv = bvec_iter_bvec(bip->bip_vec, bip->bip_iter);
					अचिन्हित tag_now = min(biv.bv_len, tag_toकरो);
					अक्षर *tag_addr;
					BUG_ON(PageHighMem(biv.bv_page));
					tag_addr = lowmem_page_address(biv.bv_page) + biv.bv_offset;
					अगर (likely(dio->op == REQ_OP_WRITE))
						स_नकल(tag_ptr, tag_addr, tag_now);
					अन्यथा
						स_नकल(tag_addr, tag_ptr, tag_now);
					bvec_iter_advance(bip->bip_vec, &bip->bip_iter, tag_now);
					tag_ptr += tag_now;
					tag_toकरो -= tag_now;
				पूर्ण जबतक (unlikely(tag_toकरो)); अन्यथा अणु
					अगर (likely(dio->op == REQ_OP_WRITE))
						स_रखो(tag_ptr, 0, tag_toकरो);
				पूर्ण
			पूर्ण

			अगर (likely(dio->op == REQ_OP_WRITE)) अणु
				काष्ठा journal_sector *js;
				अचिन्हित s;

				js = access_journal_data(ic, journal_section, journal_entry);
				स_नकल(js, mem + bv.bv_offset, ic->sectors_per_block << SECTOR_SHIFT);

				s = 0;
				करो अणु
					je->last_bytes[s] = js[s].commit_id;
				पूर्ण जबतक (++s < ic->sectors_per_block);

				अगर (ic->पूर्णांकernal_hash) अणु
					अचिन्हित digest_size = crypto_shash_digestsize(ic->पूर्णांकernal_hash);
					अगर (unlikely(digest_size > ic->tag_size)) अणु
						अक्षर checksums_onstack[HASH_MAX_DIGESTSIZE];
						पूर्णांकegrity_sector_checksum(ic, logical_sector, (अक्षर *)js, checksums_onstack);
						स_नकल(journal_entry_tag(ic, je), checksums_onstack, ic->tag_size);
					पूर्ण अन्यथा
						पूर्णांकegrity_sector_checksum(ic, logical_sector, (अक्षर *)js, journal_entry_tag(ic, je));
				पूर्ण

				journal_entry_set_sector(je, logical_sector);
			पूर्ण
			logical_sector += ic->sectors_per_block;

			journal_entry++;
			अगर (unlikely(journal_entry == ic->journal_section_entries)) अणु
				journal_entry = 0;
				journal_section++;
				wraparound_section(ic, &journal_section);
			पूर्ण

			bv.bv_offset += ic->sectors_per_block << SECTOR_SHIFT;
		पूर्ण जबतक (bv.bv_len -= ic->sectors_per_block << SECTOR_SHIFT);

		अगर (unlikely(dio->op == REQ_OP_READ))
			flush_dcache_page(bv.bv_page);
		kunmap_atomic(mem);
	पूर्ण जबतक (n_sectors);

	अगर (likely(dio->op == REQ_OP_WRITE)) अणु
		smp_mb();
		अगर (unlikely(रुकोqueue_active(&ic->copy_to_journal_रुको)))
			wake_up(&ic->copy_to_journal_रुको);
		अगर (READ_ONCE(ic->मुक्त_sectors) <= ic->मुक्त_sectors_threshold) अणु
			queue_work(ic->commit_wq, &ic->commit_work);
		पूर्ण अन्यथा अणु
			schedule_स्वतःcommit(ic);
		पूर्ण
	पूर्ण अन्यथा अणु
		हटाओ_range(ic, &dio->range);
	पूर्ण

	अगर (unlikely(bio->bi_iter.bi_size)) अणु
		sector_t area, offset;

		dio->range.logical_sector = logical_sector;
		get_area_and_offset(ic, dio->range.logical_sector, &area, &offset);
		dio->metadata_block = get_metadata_sector_and_offset(ic, area, offset, &dio->metadata_offset);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम dm_पूर्णांकegrity_map_जारी(काष्ठा dm_पूर्णांकegrity_io *dio, bool from_map)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = dio->ic;
	काष्ठा bio *bio = dm_bio_from_per_bio_data(dio, माप(काष्ठा dm_पूर्णांकegrity_io));
	अचिन्हित journal_section, journal_entry;
	अचिन्हित journal_पढ़ो_pos;
	काष्ठा completion पढ़ो_comp;
	bool discard_retried = false;
	bool need_sync_io = ic->पूर्णांकernal_hash && dio->op == REQ_OP_READ;
	अगर (unlikely(dio->op == REQ_OP_DISCARD) && ic->mode != 'D')
		need_sync_io = true;

	अगर (need_sync_io && from_map) अणु
		INIT_WORK(&dio->work, पूर्णांकegrity_bio_रुको);
		queue_work(ic->offload_wq, &dio->work);
		वापस;
	पूर्ण

lock_retry:
	spin_lock_irq(&ic->endio_रुको.lock);
retry:
	अगर (unlikely(dm_पूर्णांकegrity_failed(ic))) अणु
		spin_unlock_irq(&ic->endio_रुको.lock);
		करो_endio(ic, bio);
		वापस;
	पूर्ण
	dio->range.n_sectors = bio_sectors(bio);
	journal_पढ़ो_pos = NOT_FOUND;
	अगर (ic->mode == 'J' && likely(dio->op != REQ_OP_DISCARD)) अणु
		अगर (dio->op == REQ_OP_WRITE) अणु
			अचिन्हित next_entry, i, pos;
			अचिन्हित ws, we, range_sectors;

			dio->range.n_sectors = min(dio->range.n_sectors,
						   (sector_t)ic->मुक्त_sectors << ic->sb->log2_sectors_per_block);
			अगर (unlikely(!dio->range.n_sectors)) अणु
				अगर (from_map)
					जाओ offload_to_thपढ़ो;
				sleep_on_endio_रुको(ic);
				जाओ retry;
			पूर्ण
			range_sectors = dio->range.n_sectors >> ic->sb->log2_sectors_per_block;
			ic->मुक्त_sectors -= range_sectors;
			journal_section = ic->मुक्त_section;
			journal_entry = ic->मुक्त_section_entry;

			next_entry = ic->मुक्त_section_entry + range_sectors;
			ic->मुक्त_section_entry = next_entry % ic->journal_section_entries;
			ic->मुक्त_section += next_entry / ic->journal_section_entries;
			ic->n_uncommitted_sections += next_entry / ic->journal_section_entries;
			wraparound_section(ic, &ic->मुक्त_section);

			pos = journal_section * ic->journal_section_entries + journal_entry;
			ws = journal_section;
			we = journal_entry;
			i = 0;
			करो अणु
				काष्ठा journal_entry *je;

				add_journal_node(ic, &ic->journal_tree[pos], dio->range.logical_sector + i);
				pos++;
				अगर (unlikely(pos >= ic->journal_entries))
					pos = 0;

				je = access_journal_entry(ic, ws, we);
				BUG_ON(!journal_entry_is_unused(je));
				journal_entry_set_inprogress(je);
				we++;
				अगर (unlikely(we == ic->journal_section_entries)) अणु
					we = 0;
					ws++;
					wraparound_section(ic, &ws);
				पूर्ण
			पूर्ण जबतक ((i += ic->sectors_per_block) < dio->range.n_sectors);

			spin_unlock_irq(&ic->endio_रुको.lock);
			जाओ journal_पढ़ो_ग_लिखो;
		पूर्ण अन्यथा अणु
			sector_t next_sector;
			journal_पढ़ो_pos = find_journal_node(ic, dio->range.logical_sector, &next_sector);
			अगर (likely(journal_पढ़ो_pos == NOT_FOUND)) अणु
				अगर (unlikely(dio->range.n_sectors > next_sector - dio->range.logical_sector))
					dio->range.n_sectors = next_sector - dio->range.logical_sector;
			पूर्ण अन्यथा अणु
				अचिन्हित i;
				अचिन्हित jp = journal_पढ़ो_pos + 1;
				क्रम (i = ic->sectors_per_block; i < dio->range.n_sectors; i += ic->sectors_per_block, jp++) अणु
					अगर (!test_journal_node(ic, jp, dio->range.logical_sector + i))
						अवरोध;
				पूर्ण
				dio->range.n_sectors = i;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (unlikely(!add_new_range(ic, &dio->range, true))) अणु
		/*
		 * We must not sleep in the request routine because it could
		 * stall bios on current->bio_list.
		 * So, we offload the bio to a workqueue अगर we have to sleep.
		 */
		अगर (from_map) अणु
offload_to_thपढ़ो:
			spin_unlock_irq(&ic->endio_रुको.lock);
			INIT_WORK(&dio->work, पूर्णांकegrity_bio_रुको);
			queue_work(ic->रुको_wq, &dio->work);
			वापस;
		पूर्ण
		अगर (journal_पढ़ो_pos != NOT_FOUND)
			dio->range.n_sectors = ic->sectors_per_block;
		रुको_and_add_new_range(ic, &dio->range);
		/*
		 * रुको_and_add_new_range drops the spinlock, so the journal
		 * may have been changed arbitrarily. We need to recheck.
		 * To simplअगरy the code, we restrict I/O size to just one block.
		 */
		अगर (journal_पढ़ो_pos != NOT_FOUND) अणु
			sector_t next_sector;
			अचिन्हित new_pos = find_journal_node(ic, dio->range.logical_sector, &next_sector);
			अगर (unlikely(new_pos != journal_पढ़ो_pos)) अणु
				हटाओ_range_unlocked(ic, &dio->range);
				जाओ retry;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (ic->mode == 'J' && likely(dio->op == REQ_OP_DISCARD) && !discard_retried) अणु
		sector_t next_sector;
		अचिन्हित new_pos = find_journal_node(ic, dio->range.logical_sector, &next_sector);
		अगर (unlikely(new_pos != NOT_FOUND) ||
		    unlikely(next_sector < dio->range.logical_sector - dio->range.n_sectors)) अणु
			हटाओ_range_unlocked(ic, &dio->range);
			spin_unlock_irq(&ic->endio_रुको.lock);
			queue_work(ic->commit_wq, &ic->commit_work);
			flush_workqueue(ic->commit_wq);
			queue_work(ic->ग_लिखोr_wq, &ic->ग_लिखोr_work);
			flush_workqueue(ic->ग_लिखोr_wq);
			discard_retried = true;
			जाओ lock_retry;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&ic->endio_रुको.lock);

	अगर (unlikely(journal_पढ़ो_pos != NOT_FOUND)) अणु
		journal_section = journal_पढ़ो_pos / ic->journal_section_entries;
		journal_entry = journal_पढ़ो_pos % ic->journal_section_entries;
		जाओ journal_पढ़ो_ग_लिखो;
	पूर्ण

	अगर (ic->mode == 'B' && (dio->op == REQ_OP_WRITE || unlikely(dio->op == REQ_OP_DISCARD))) अणु
		अगर (!block_biपंचांगap_op(ic, ic->may_ग_लिखो_biपंचांगap, dio->range.logical_sector,
				     dio->range.n_sectors, BITMAP_OP_TEST_ALL_SET)) अणु
			काष्ठा biपंचांगap_block_status *bbs;

			bbs = sector_to_biपंचांगap_block(ic, dio->range.logical_sector);
			spin_lock(&bbs->bio_queue_lock);
			bio_list_add(&bbs->bio_queue, bio);
			spin_unlock(&bbs->bio_queue_lock);
			queue_work(ic->ग_लिखोr_wq, &bbs->work);
			वापस;
		पूर्ण
	पूर्ण

	dio->in_flight = (atomic_t)ATOMIC_INIT(2);

	अगर (need_sync_io) अणु
		init_completion(&पढ़ो_comp);
		dio->completion = &पढ़ो_comp;
	पूर्ण अन्यथा
		dio->completion = शून्य;

	dm_bio_record(&dio->bio_details, bio);
	bio_set_dev(bio, ic->dev->bdev);
	bio->bi_पूर्णांकegrity = शून्य;
	bio->bi_opf &= ~REQ_INTEGRITY;
	bio->bi_end_io = पूर्णांकegrity_end_io;
	bio->bi_iter.bi_size = dio->range.n_sectors << SECTOR_SHIFT;

	अगर (unlikely(dio->op == REQ_OP_DISCARD) && likely(ic->mode != 'D')) अणु
		पूर्णांकegrity_metadata(&dio->work);
		dm_पूर्णांकegrity_flush_buffers(ic, false);

		dio->in_flight = (atomic_t)ATOMIC_INIT(1);
		dio->completion = शून्य;

		submit_bio_noacct(bio);

		वापस;
	पूर्ण

	submit_bio_noacct(bio);

	अगर (need_sync_io) अणु
		रुको_क्रम_completion_io(&पढ़ो_comp);
		अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING) &&
		    dio->range.logical_sector + dio->range.n_sectors > le64_to_cpu(ic->sb->recalc_sector))
			जाओ skip_check;
		अगर (ic->mode == 'B') अणु
			अगर (!block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, dio->range.logical_sector,
					     dio->range.n_sectors, BITMAP_OP_TEST_ALL_CLEAR))
				जाओ skip_check;
		पूर्ण

		अगर (likely(!bio->bi_status))
			पूर्णांकegrity_metadata(&dio->work);
		अन्यथा
skip_check:
			dec_in_flight(dio);

	पूर्ण अन्यथा अणु
		INIT_WORK(&dio->work, पूर्णांकegrity_metadata);
		queue_work(ic->metadata_wq, &dio->work);
	पूर्ण

	वापस;

journal_पढ़ो_ग_लिखो:
	अगर (unlikely(__journal_पढ़ो_ग_लिखो(dio, bio, journal_section, journal_entry)))
		जाओ lock_retry;

	करो_endio_flush(ic, dio);
पूर्ण


अटल व्योम पूर्णांकegrity_bio_रुको(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dm_पूर्णांकegrity_io *dio = container_of(w, काष्ठा dm_पूर्णांकegrity_io, work);

	dm_पूर्णांकegrity_map_जारी(dio, false);
पूर्ण

अटल व्योम pad_uncommitted(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	अगर (ic->मुक्त_section_entry) अणु
		ic->मुक्त_sectors -= ic->journal_section_entries - ic->मुक्त_section_entry;
		ic->मुक्त_section_entry = 0;
		ic->मुक्त_section++;
		wraparound_section(ic, &ic->मुक्त_section);
		ic->n_uncommitted_sections++;
	पूर्ण
	अगर (WARN_ON(ic->journal_sections * ic->journal_section_entries !=
		    (ic->n_uncommitted_sections + ic->n_committed_sections) *
		    ic->journal_section_entries + ic->मुक्त_sectors)) अणु
		DMCRIT("journal_sections %u, journal_section_entries %u, "
		       "n_uncommitted_sections %u, n_committed_sections %u, "
		       "journal_section_entries %u, free_sectors %u",
		       ic->journal_sections, ic->journal_section_entries,
		       ic->n_uncommitted_sections, ic->n_committed_sections,
		       ic->journal_section_entries, ic->मुक्त_sectors);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकegrity_commit(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = container_of(w, काष्ठा dm_पूर्णांकegrity_c, commit_work);
	अचिन्हित commit_start, commit_sections;
	अचिन्हित i, j, n;
	काष्ठा bio *flushes;

	del_समयr(&ic->स्वतःcommit_समयr);

	spin_lock_irq(&ic->endio_रुको.lock);
	flushes = bio_list_get(&ic->flush_bio_list);
	अगर (unlikely(ic->mode != 'J')) अणु
		spin_unlock_irq(&ic->endio_रुको.lock);
		dm_पूर्णांकegrity_flush_buffers(ic, true);
		जाओ release_flush_bios;
	पूर्ण

	pad_uncommitted(ic);
	commit_start = ic->uncommitted_section;
	commit_sections = ic->n_uncommitted_sections;
	spin_unlock_irq(&ic->endio_रुको.lock);

	अगर (!commit_sections)
		जाओ release_flush_bios;

	i = commit_start;
	क्रम (n = 0; n < commit_sections; n++) अणु
		क्रम (j = 0; j < ic->journal_section_entries; j++) अणु
			काष्ठा journal_entry *je;
			je = access_journal_entry(ic, i, j);
			io_रुको_event(ic->copy_to_journal_रुको, !journal_entry_is_inprogress(je));
		पूर्ण
		क्रम (j = 0; j < ic->journal_section_sectors; j++) अणु
			काष्ठा journal_sector *js;
			js = access_journal(ic, i, j);
			js->commit_id = dm_पूर्णांकegrity_commit_id(ic, i, j, ic->commit_seq);
		पूर्ण
		i++;
		अगर (unlikely(i >= ic->journal_sections))
			ic->commit_seq = next_commit_seq(ic->commit_seq);
		wraparound_section(ic, &i);
	पूर्ण
	smp_rmb();

	ग_लिखो_journal(ic, commit_start, commit_sections);

	spin_lock_irq(&ic->endio_रुको.lock);
	ic->uncommitted_section += commit_sections;
	wraparound_section(ic, &ic->uncommitted_section);
	ic->n_uncommitted_sections -= commit_sections;
	ic->n_committed_sections += commit_sections;
	spin_unlock_irq(&ic->endio_रुको.lock);

	अगर (READ_ONCE(ic->मुक्त_sectors) <= ic->मुक्त_sectors_threshold)
		queue_work(ic->ग_लिखोr_wq, &ic->ग_लिखोr_work);

release_flush_bios:
	जबतक (flushes) अणु
		काष्ठा bio *next = flushes->bi_next;
		flushes->bi_next = शून्य;
		करो_endio(ic, flushes);
		flushes = next;
	पूर्ण
पूर्ण

अटल व्योम complete_copy_from_journal(अचिन्हित दीर्घ error, व्योम *context)
अणु
	काष्ठा journal_io *io = context;
	काष्ठा journal_completion *comp = io->comp;
	काष्ठा dm_पूर्णांकegrity_c *ic = comp->ic;
	हटाओ_range(ic, &io->range);
	mempool_मुक्त(io, &ic->journal_io_mempool);
	अगर (unlikely(error != 0))
		dm_पूर्णांकegrity_io_error(ic, "copying from journal", -EIO);
	complete_journal_op(comp);
पूर्ण

अटल व्योम restore_last_bytes(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा journal_sector *js,
			       काष्ठा journal_entry *je)
अणु
	अचिन्हित s = 0;
	करो अणु
		js->commit_id = je->last_bytes[s];
		js++;
	पूर्ण जबतक (++s < ic->sectors_per_block);
पूर्ण

अटल व्योम करो_journal_ग_लिखो(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित ग_लिखो_start,
			     अचिन्हित ग_लिखो_sections, bool from_replay)
अणु
	अचिन्हित i, j, n;
	काष्ठा journal_completion comp;
	काष्ठा blk_plug plug;

	blk_start_plug(&plug);

	comp.ic = ic;
	comp.in_flight = (atomic_t)ATOMIC_INIT(1);
	init_completion(&comp.comp);

	i = ग_लिखो_start;
	क्रम (n = 0; n < ग_लिखो_sections; n++, i++, wraparound_section(ic, &i)) अणु
#अगर_अघोषित INTERNAL_VERIFY
		अगर (unlikely(from_replay))
#पूर्ण_अगर
			rw_section_mac(ic, i, false);
		क्रम (j = 0; j < ic->journal_section_entries; j++) अणु
			काष्ठा journal_entry *je = access_journal_entry(ic, i, j);
			sector_t sec, area, offset;
			अचिन्हित k, l, next_loop;
			sector_t metadata_block;
			अचिन्हित metadata_offset;
			काष्ठा journal_io *io;

			अगर (journal_entry_is_unused(je))
				जारी;
			BUG_ON(unlikely(journal_entry_is_inprogress(je)) && !from_replay);
			sec = journal_entry_get_sector(je);
			अगर (unlikely(from_replay)) अणु
				अगर (unlikely(sec & (अचिन्हित)(ic->sectors_per_block - 1))) अणु
					dm_पूर्णांकegrity_io_error(ic, "invalid sector in journal", -EIO);
					sec &= ~(sector_t)(ic->sectors_per_block - 1);
				पूर्ण
			पूर्ण
			अगर (unlikely(sec >= ic->provided_data_sectors))
				जारी;
			get_area_and_offset(ic, sec, &area, &offset);
			restore_last_bytes(ic, access_journal_data(ic, i, j), je);
			क्रम (k = j + 1; k < ic->journal_section_entries; k++) अणु
				काष्ठा journal_entry *je2 = access_journal_entry(ic, i, k);
				sector_t sec2, area2, offset2;
				अगर (journal_entry_is_unused(je2))
					अवरोध;
				BUG_ON(unlikely(journal_entry_is_inprogress(je2)) && !from_replay);
				sec2 = journal_entry_get_sector(je2);
				अगर (unlikely(sec2 >= ic->provided_data_sectors))
					अवरोध;
				get_area_and_offset(ic, sec2, &area2, &offset2);
				अगर (area2 != area || offset2 != offset + ((k - j) << ic->sb->log2_sectors_per_block))
					अवरोध;
				restore_last_bytes(ic, access_journal_data(ic, i, k), je2);
			पूर्ण
			next_loop = k - 1;

			io = mempool_alloc(&ic->journal_io_mempool, GFP_NOIO);
			io->comp = &comp;
			io->range.logical_sector = sec;
			io->range.n_sectors = (k - j) << ic->sb->log2_sectors_per_block;

			spin_lock_irq(&ic->endio_रुको.lock);
			add_new_range_and_रुको(ic, &io->range);

			अगर (likely(!from_replay)) अणु
				काष्ठा journal_node *section_node = &ic->journal_tree[i * ic->journal_section_entries];

				/* करोn't ग_लिखो अगर there is newer committed sector */
				जबतक (j < k && find_newer_committed_node(ic, &section_node[j])) अणु
					काष्ठा journal_entry *je2 = access_journal_entry(ic, i, j);

					journal_entry_set_unused(je2);
					हटाओ_journal_node(ic, &section_node[j]);
					j++;
					sec += ic->sectors_per_block;
					offset += ic->sectors_per_block;
				पूर्ण
				जबतक (j < k && find_newer_committed_node(ic, &section_node[k - 1])) अणु
					काष्ठा journal_entry *je2 = access_journal_entry(ic, i, k - 1);

					journal_entry_set_unused(je2);
					हटाओ_journal_node(ic, &section_node[k - 1]);
					k--;
				पूर्ण
				अगर (j == k) अणु
					हटाओ_range_unlocked(ic, &io->range);
					spin_unlock_irq(&ic->endio_रुको.lock);
					mempool_मुक्त(io, &ic->journal_io_mempool);
					जाओ skip_io;
				पूर्ण
				क्रम (l = j; l < k; l++) अणु
					हटाओ_journal_node(ic, &section_node[l]);
				पूर्ण
			पूर्ण
			spin_unlock_irq(&ic->endio_रुको.lock);

			metadata_block = get_metadata_sector_and_offset(ic, area, offset, &metadata_offset);
			क्रम (l = j; l < k; l++) अणु
				पूर्णांक r;
				काष्ठा journal_entry *je2 = access_journal_entry(ic, i, l);

				अगर (
#अगर_अघोषित INTERNAL_VERIFY
				    unlikely(from_replay) &&
#पूर्ण_अगर
				    ic->पूर्णांकernal_hash) अणु
					अक्षर test_tag[max_t(माप_प्रकार, HASH_MAX_DIGESTSIZE, MAX_TAG_SIZE)];

					पूर्णांकegrity_sector_checksum(ic, sec + ((l - j) << ic->sb->log2_sectors_per_block),
								  (अक्षर *)access_journal_data(ic, i, l), test_tag);
					अगर (unlikely(स_भेद(test_tag, journal_entry_tag(ic, je2), ic->tag_size)))
						dm_पूर्णांकegrity_io_error(ic, "tag mismatch when replaying journal", -EILSEQ);
				पूर्ण

				journal_entry_set_unused(je2);
				r = dm_पूर्णांकegrity_rw_tag(ic, journal_entry_tag(ic, je2), &metadata_block, &metadata_offset,
							ic->tag_size, TAG_WRITE);
				अगर (unlikely(r)) अणु
					dm_पूर्णांकegrity_io_error(ic, "reading tags", r);
				पूर्ण
			पूर्ण

			atomic_inc(&comp.in_flight);
			copy_from_journal(ic, i, j << ic->sb->log2_sectors_per_block,
					  (k - j) << ic->sb->log2_sectors_per_block,
					  get_data_sector(ic, area, offset),
					  complete_copy_from_journal, io);
skip_io:
			j = next_loop;
		पूर्ण
	पूर्ण

	dm_bufio_ग_लिखो_dirty_buffers_async(ic->bufio);

	blk_finish_plug(&plug);

	complete_journal_op(&comp);
	रुको_क्रम_completion_io(&comp.comp);

	dm_पूर्णांकegrity_flush_buffers(ic, true);
पूर्ण

अटल व्योम पूर्णांकegrity_ग_लिखोr(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = container_of(w, काष्ठा dm_पूर्णांकegrity_c, ग_लिखोr_work);
	अचिन्हित ग_लिखो_start, ग_लिखो_sections;

	अचिन्हित prev_मुक्त_sectors;

	/* the following test is not needed, but it tests the replay code */
	अगर (unlikely(dm_post_suspending(ic->ti)) && !ic->meta_dev)
		वापस;

	spin_lock_irq(&ic->endio_रुको.lock);
	ग_लिखो_start = ic->committed_section;
	ग_लिखो_sections = ic->n_committed_sections;
	spin_unlock_irq(&ic->endio_रुको.lock);

	अगर (!ग_लिखो_sections)
		वापस;

	करो_journal_ग_लिखो(ic, ग_लिखो_start, ग_लिखो_sections, false);

	spin_lock_irq(&ic->endio_रुको.lock);

	ic->committed_section += ग_लिखो_sections;
	wraparound_section(ic, &ic->committed_section);
	ic->n_committed_sections -= ग_लिखो_sections;

	prev_मुक्त_sectors = ic->मुक्त_sectors;
	ic->मुक्त_sectors += ग_लिखो_sections * ic->journal_section_entries;
	अगर (unlikely(!prev_मुक्त_sectors))
		wake_up_locked(&ic->endio_रुको);

	spin_unlock_irq(&ic->endio_रुको.lock);
पूर्ण

अटल व्योम recalc_ग_लिखो_super(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	पूर्णांक r;

	dm_पूर्णांकegrity_flush_buffers(ic, false);
	अगर (dm_पूर्णांकegrity_failed(ic))
		वापस;

	r = sync_rw_sb(ic, REQ_OP_WRITE, 0);
	अगर (unlikely(r))
		dm_पूर्णांकegrity_io_error(ic, "writing superblock", r);
पूर्ण

अटल व्योम पूर्णांकegrity_recalc(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = container_of(w, काष्ठा dm_पूर्णांकegrity_c, recalc_work);
	काष्ठा dm_पूर्णांकegrity_range range;
	काष्ठा dm_io_request io_req;
	काष्ठा dm_io_region io_loc;
	sector_t area, offset;
	sector_t metadata_block;
	अचिन्हित metadata_offset;
	sector_t logical_sector, n_sectors;
	__u8 *t;
	अचिन्हित i;
	पूर्णांक r;
	अचिन्हित super_counter = 0;

	DEBUG_prपूर्णांक("start recalculation... (position %llx)\n", le64_to_cpu(ic->sb->recalc_sector));

	spin_lock_irq(&ic->endio_रुको.lock);

next_chunk:

	अगर (unlikely(dm_post_suspending(ic->ti)))
		जाओ unlock_ret;

	range.logical_sector = le64_to_cpu(ic->sb->recalc_sector);
	अगर (unlikely(range.logical_sector >= ic->provided_data_sectors)) अणु
		अगर (ic->mode == 'B') अणु
			block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, 0, ic->provided_data_sectors, BITMAP_OP_CLEAR);
			DEBUG_prपूर्णांक("queue_delayed_work: bitmap_flush_work\n");
			queue_delayed_work(ic->commit_wq, &ic->biपंचांगap_flush_work, 0);
		पूर्ण
		जाओ unlock_ret;
	पूर्ण

	get_area_and_offset(ic, range.logical_sector, &area, &offset);
	range.n_sectors = min((sector_t)RECALC_SECTORS, ic->provided_data_sectors - range.logical_sector);
	अगर (!ic->meta_dev)
		range.n_sectors = min(range.n_sectors, ((sector_t)1U << ic->sb->log2_पूर्णांकerleave_sectors) - (अचिन्हित)offset);

	add_new_range_and_रुको(ic, &range);
	spin_unlock_irq(&ic->endio_रुको.lock);
	logical_sector = range.logical_sector;
	n_sectors = range.n_sectors;

	अगर (ic->mode == 'B') अणु
		अगर (block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, logical_sector, n_sectors, BITMAP_OP_TEST_ALL_CLEAR)) अणु
			जाओ advance_and_next;
		पूर्ण
		जबतक (block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, logical_sector,
				       ic->sectors_per_block, BITMAP_OP_TEST_ALL_CLEAR)) अणु
			logical_sector += ic->sectors_per_block;
			n_sectors -= ic->sectors_per_block;
			cond_resched();
		पूर्ण
		जबतक (block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, logical_sector + n_sectors - ic->sectors_per_block,
				       ic->sectors_per_block, BITMAP_OP_TEST_ALL_CLEAR)) अणु
			n_sectors -= ic->sectors_per_block;
			cond_resched();
		पूर्ण
		get_area_and_offset(ic, logical_sector, &area, &offset);
	पूर्ण

	DEBUG_prपूर्णांक("recalculating: %llx, %llx\n", logical_sector, n_sectors);

	अगर (unlikely(++super_counter == RECALC_WRITE_SUPER)) अणु
		recalc_ग_लिखो_super(ic);
		अगर (ic->mode == 'B') अणु
			queue_delayed_work(ic->commit_wq, &ic->biपंचांगap_flush_work, ic->biपंचांगap_flush_पूर्णांकerval);
		पूर्ण
		super_counter = 0;
	पूर्ण

	अगर (unlikely(dm_पूर्णांकegrity_failed(ic)))
		जाओ err;

	io_req.bi_op = REQ_OP_READ;
	io_req.bi_op_flags = 0;
	io_req.mem.type = DM_IO_VMA;
	io_req.mem.ptr.addr = ic->recalc_buffer;
	io_req.notअगरy.fn = शून्य;
	io_req.client = ic->io;
	io_loc.bdev = ic->dev->bdev;
	io_loc.sector = get_data_sector(ic, area, offset);
	io_loc.count = n_sectors;

	r = dm_io(&io_req, 1, &io_loc, शून्य);
	अगर (unlikely(r)) अणु
		dm_पूर्णांकegrity_io_error(ic, "reading data", r);
		जाओ err;
	पूर्ण

	t = ic->recalc_tags;
	क्रम (i = 0; i < n_sectors; i += ic->sectors_per_block) अणु
		पूर्णांकegrity_sector_checksum(ic, logical_sector + i, ic->recalc_buffer + (i << SECTOR_SHIFT), t);
		t += ic->tag_size;
	पूर्ण

	metadata_block = get_metadata_sector_and_offset(ic, area, offset, &metadata_offset);

	r = dm_पूर्णांकegrity_rw_tag(ic, ic->recalc_tags, &metadata_block, &metadata_offset, t - ic->recalc_tags, TAG_WRITE);
	अगर (unlikely(r)) अणु
		dm_पूर्णांकegrity_io_error(ic, "writing tags", r);
		जाओ err;
	पूर्ण

	अगर (ic->mode == 'B') अणु
		sector_t start, end;
		start = (range.logical_sector >>
			 (ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit)) <<
			(ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit);
		end = ((range.logical_sector + range.n_sectors) >>
		       (ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit)) <<
			(ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit);
		block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, start, end - start, BITMAP_OP_CLEAR);
	पूर्ण

advance_and_next:
	cond_resched();

	spin_lock_irq(&ic->endio_रुको.lock);
	हटाओ_range_unlocked(ic, &range);
	ic->sb->recalc_sector = cpu_to_le64(range.logical_sector + range.n_sectors);
	जाओ next_chunk;

err:
	हटाओ_range(ic, &range);
	वापस;

unlock_ret:
	spin_unlock_irq(&ic->endio_रुको.lock);

	recalc_ग_लिखो_super(ic);
पूर्ण

अटल व्योम biपंचांगap_block_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा biपंचांगap_block_status *bbs = container_of(w, काष्ठा biपंचांगap_block_status, work);
	काष्ठा dm_पूर्णांकegrity_c *ic = bbs->ic;
	काष्ठा bio *bio;
	काष्ठा bio_list bio_queue;
	काष्ठा bio_list रुकोing;

	bio_list_init(&रुकोing);

	spin_lock(&bbs->bio_queue_lock);
	bio_queue = bbs->bio_queue;
	bio_list_init(&bbs->bio_queue);
	spin_unlock(&bbs->bio_queue_lock);

	जबतक ((bio = bio_list_pop(&bio_queue))) अणु
		काष्ठा dm_पूर्णांकegrity_io *dio;

		dio = dm_per_bio_data(bio, माप(काष्ठा dm_पूर्णांकegrity_io));

		अगर (block_biपंचांगap_op(ic, ic->may_ग_लिखो_biपंचांगap, dio->range.logical_sector,
				    dio->range.n_sectors, BITMAP_OP_TEST_ALL_SET)) अणु
			हटाओ_range(ic, &dio->range);
			INIT_WORK(&dio->work, पूर्णांकegrity_bio_रुको);
			queue_work(ic->offload_wq, &dio->work);
		पूर्ण अन्यथा अणु
			block_biपंचांगap_op(ic, ic->journal, dio->range.logical_sector,
					dio->range.n_sectors, BITMAP_OP_SET);
			bio_list_add(&रुकोing, bio);
		पूर्ण
	पूर्ण

	अगर (bio_list_empty(&रुकोing))
		वापस;

	rw_journal_sectors(ic, REQ_OP_WRITE, REQ_FUA | REQ_SYNC,
			   bbs->idx * (BITMAP_BLOCK_SIZE >> SECTOR_SHIFT),
			   BITMAP_BLOCK_SIZE >> SECTOR_SHIFT, शून्य);

	जबतक ((bio = bio_list_pop(&रुकोing))) अणु
		काष्ठा dm_पूर्णांकegrity_io *dio = dm_per_bio_data(bio, माप(काष्ठा dm_पूर्णांकegrity_io));

		block_biपंचांगap_op(ic, ic->may_ग_लिखो_biपंचांगap, dio->range.logical_sector,
				dio->range.n_sectors, BITMAP_OP_SET);

		हटाओ_range(ic, &dio->range);
		INIT_WORK(&dio->work, पूर्णांकegrity_bio_रुको);
		queue_work(ic->offload_wq, &dio->work);
	पूर्ण

	queue_delayed_work(ic->commit_wq, &ic->biपंचांगap_flush_work, ic->biपंचांगap_flush_पूर्णांकerval);
पूर्ण

अटल व्योम biपंचांगap_flush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = container_of(work, काष्ठा dm_पूर्णांकegrity_c, biपंचांगap_flush_work.work);
	काष्ठा dm_पूर्णांकegrity_range range;
	अचिन्हित दीर्घ limit;
	काष्ठा bio *bio;

	dm_पूर्णांकegrity_flush_buffers(ic, false);

	range.logical_sector = 0;
	range.n_sectors = ic->provided_data_sectors;

	spin_lock_irq(&ic->endio_रुको.lock);
	add_new_range_and_रुको(ic, &range);
	spin_unlock_irq(&ic->endio_रुको.lock);

	dm_पूर्णांकegrity_flush_buffers(ic, true);

	limit = ic->provided_data_sectors;
	अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING)) अणु
		limit = le64_to_cpu(ic->sb->recalc_sector)
			>> (ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit)
			<< (ic->sb->log2_sectors_per_block + ic->log2_blocks_per_biपंचांगap_bit);
	पूर्ण
	/*DEBUG_prपूर्णांक("zeroing journal\n");*/
	block_biपंचांगap_op(ic, ic->journal, 0, limit, BITMAP_OP_CLEAR);
	block_biपंचांगap_op(ic, ic->may_ग_लिखो_biपंचांगap, 0, limit, BITMAP_OP_CLEAR);

	rw_journal_sectors(ic, REQ_OP_WRITE, REQ_FUA | REQ_SYNC, 0,
			   ic->n_biपंचांगap_blocks * (BITMAP_BLOCK_SIZE >> SECTOR_SHIFT), शून्य);

	spin_lock_irq(&ic->endio_रुको.lock);
	हटाओ_range_unlocked(ic, &range);
	जबतक (unlikely((bio = bio_list_pop(&ic->synchronous_bios)) != शून्य)) अणु
		bio_endio(bio);
		spin_unlock_irq(&ic->endio_रुको.lock);
		spin_lock_irq(&ic->endio_रुको.lock);
	पूर्ण
	spin_unlock_irq(&ic->endio_रुको.lock);
पूर्ण


अटल व्योम init_journal(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित start_section,
			 अचिन्हित n_sections, अचिन्हित अक्षर commit_seq)
अणु
	अचिन्हित i, j, n;

	अगर (!n_sections)
		वापस;

	क्रम (n = 0; n < n_sections; n++) अणु
		i = start_section + n;
		wraparound_section(ic, &i);
		क्रम (j = 0; j < ic->journal_section_sectors; j++) अणु
			काष्ठा journal_sector *js = access_journal(ic, i, j);
			स_रखो(&js->entries, 0, JOURNAL_SECTOR_DATA);
			js->commit_id = dm_पूर्णांकegrity_commit_id(ic, i, j, commit_seq);
		पूर्ण
		क्रम (j = 0; j < ic->journal_section_entries; j++) अणु
			काष्ठा journal_entry *je = access_journal_entry(ic, i, j);
			journal_entry_set_unused(je);
		पूर्ण
	पूर्ण

	ग_लिखो_journal(ic, start_section, n_sections);
पूर्ण

अटल पूर्णांक find_commit_seq(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित i, अचिन्हित j, commit_id_t id)
अणु
	अचिन्हित अक्षर k;
	क्रम (k = 0; k < N_COMMIT_IDS; k++) अणु
		अगर (dm_पूर्णांकegrity_commit_id(ic, i, j, k) == id)
			वापस k;
	पूर्ण
	dm_पूर्णांकegrity_io_error(ic, "journal commit id", -EIO);
	वापस -EIO;
पूर्ण

अटल व्योम replay_journal(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	अचिन्हित i, j;
	bool used_commit_ids[N_COMMIT_IDS];
	अचिन्हित max_commit_id_sections[N_COMMIT_IDS];
	अचिन्हित ग_लिखो_start, ग_लिखो_sections;
	अचिन्हित जारी_section;
	bool journal_empty;
	अचिन्हित अक्षर unused, last_used, want_commit_seq;

	अगर (ic->mode == 'R')
		वापस;

	अगर (ic->journal_uptodate)
		वापस;

	last_used = 0;
	ग_लिखो_start = 0;

	अगर (!ic->just_क्रमmatted) अणु
		DEBUG_prपूर्णांक("reading journal\n");
		rw_journal(ic, REQ_OP_READ, 0, 0, ic->journal_sections, शून्य);
		अगर (ic->journal_io)
			DEBUG_bytes(lowmem_page_address(ic->journal_io[0].page), 64, "read journal");
		अगर (ic->journal_io) अणु
			काष्ठा journal_completion crypt_comp;
			crypt_comp.ic = ic;
			init_completion(&crypt_comp.comp);
			crypt_comp.in_flight = (atomic_t)ATOMIC_INIT(0);
			encrypt_journal(ic, false, 0, ic->journal_sections, &crypt_comp);
			रुको_क्रम_completion(&crypt_comp.comp);
		पूर्ण
		DEBUG_bytes(lowmem_page_address(ic->journal[0].page), 64, "decrypted journal");
	पूर्ण

	अगर (dm_पूर्णांकegrity_failed(ic))
		जाओ clear_journal;

	journal_empty = true;
	स_रखो(used_commit_ids, 0, माप used_commit_ids);
	स_रखो(max_commit_id_sections, 0, माप max_commit_id_sections);
	क्रम (i = 0; i < ic->journal_sections; i++) अणु
		क्रम (j = 0; j < ic->journal_section_sectors; j++) अणु
			पूर्णांक k;
			काष्ठा journal_sector *js = access_journal(ic, i, j);
			k = find_commit_seq(ic, i, j, js->commit_id);
			अगर (k < 0)
				जाओ clear_journal;
			used_commit_ids[k] = true;
			max_commit_id_sections[k] = i;
		पूर्ण
		अगर (journal_empty) अणु
			क्रम (j = 0; j < ic->journal_section_entries; j++) अणु
				काष्ठा journal_entry *je = access_journal_entry(ic, i, j);
				अगर (!journal_entry_is_unused(je)) अणु
					journal_empty = false;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!used_commit_ids[N_COMMIT_IDS - 1]) अणु
		unused = N_COMMIT_IDS - 1;
		जबतक (unused && !used_commit_ids[unused - 1])
			unused--;
	पूर्ण अन्यथा अणु
		क्रम (unused = 0; unused < N_COMMIT_IDS; unused++)
			अगर (!used_commit_ids[unused])
				अवरोध;
		अगर (unused == N_COMMIT_IDS) अणु
			dm_पूर्णांकegrity_io_error(ic, "journal commit ids", -EIO);
			जाओ clear_journal;
		पूर्ण
	पूर्ण
	DEBUG_prपूर्णांक("first unused commit seq %d [%d,%d,%d,%d]\n",
		    unused, used_commit_ids[0], used_commit_ids[1],
		    used_commit_ids[2], used_commit_ids[3]);

	last_used = prev_commit_seq(unused);
	want_commit_seq = prev_commit_seq(last_used);

	अगर (!used_commit_ids[want_commit_seq] && used_commit_ids[prev_commit_seq(want_commit_seq)])
		journal_empty = true;

	ग_लिखो_start = max_commit_id_sections[last_used] + 1;
	अगर (unlikely(ग_लिखो_start >= ic->journal_sections))
		want_commit_seq = next_commit_seq(want_commit_seq);
	wraparound_section(ic, &ग_लिखो_start);

	i = ग_लिखो_start;
	क्रम (ग_लिखो_sections = 0; ग_लिखो_sections < ic->journal_sections; ग_लिखो_sections++) अणु
		क्रम (j = 0; j < ic->journal_section_sectors; j++) अणु
			काष्ठा journal_sector *js = access_journal(ic, i, j);

			अगर (js->commit_id != dm_पूर्णांकegrity_commit_id(ic, i, j, want_commit_seq)) अणु
				/*
				 * This could be caused by crash during writing.
				 * We won't replay the inconsistent part of the
				 * journal.
				 */
				DEBUG_prपूर्णांक("commit id mismatch at position (%u, %u): %d != %d\n",
					    i, j, find_commit_seq(ic, i, j, js->commit_id), want_commit_seq);
				जाओ brk;
			पूर्ण
		पूर्ण
		i++;
		अगर (unlikely(i >= ic->journal_sections))
			want_commit_seq = next_commit_seq(want_commit_seq);
		wraparound_section(ic, &i);
	पूर्ण
brk:

	अगर (!journal_empty) अणु
		DEBUG_prपूर्णांक("replaying %u sections, starting at %u, commit seq %d\n",
			    ग_लिखो_sections, ग_लिखो_start, want_commit_seq);
		करो_journal_ग_लिखो(ic, ग_लिखो_start, ग_लिखो_sections, true);
	पूर्ण

	अगर (ग_लिखो_sections == ic->journal_sections && (ic->mode == 'J' || journal_empty)) अणु
		जारी_section = ग_लिखो_start;
		ic->commit_seq = want_commit_seq;
		DEBUG_prपूर्णांक("continuing from section %u, commit seq %d\n", ग_लिखो_start, ic->commit_seq);
	पूर्ण अन्यथा अणु
		अचिन्हित s;
		अचिन्हित अक्षर erase_seq;
clear_journal:
		DEBUG_prपूर्णांक("clearing journal\n");

		erase_seq = prev_commit_seq(prev_commit_seq(last_used));
		s = ग_लिखो_start;
		init_journal(ic, s, 1, erase_seq);
		s++;
		wraparound_section(ic, &s);
		अगर (ic->journal_sections >= 2) अणु
			init_journal(ic, s, ic->journal_sections - 2, erase_seq);
			s += ic->journal_sections - 2;
			wraparound_section(ic, &s);
			init_journal(ic, s, 1, erase_seq);
		पूर्ण

		जारी_section = 0;
		ic->commit_seq = next_commit_seq(erase_seq);
	पूर्ण

	ic->committed_section = जारी_section;
	ic->n_committed_sections = 0;

	ic->uncommitted_section = जारी_section;
	ic->n_uncommitted_sections = 0;

	ic->मुक्त_section = जारी_section;
	ic->मुक्त_section_entry = 0;
	ic->मुक्त_sectors = ic->journal_entries;

	ic->journal_tree_root = RB_ROOT;
	क्रम (i = 0; i < ic->journal_entries; i++)
		init_journal_node(&ic->journal_tree[i]);
पूर्ण

अटल व्योम dm_पूर्णांकegrity_enter_synchronous_mode(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	DEBUG_prपूर्णांक("dm_integrity_enter_synchronous_mode\n");

	अगर (ic->mode == 'B') अणु
		ic->biपंचांगap_flush_पूर्णांकerval = msecs_to_jअगरfies(10) + 1;
		ic->synchronous_mode = 1;

		cancel_delayed_work_sync(&ic->biपंचांगap_flush_work);
		queue_delayed_work(ic->commit_wq, &ic->biपंचांगap_flush_work, 0);
		flush_workqueue(ic->commit_wq);
	पूर्ण
पूर्ण

अटल पूर्णांक dm_पूर्णांकegrity_reboot(काष्ठा notअगरier_block *n, अचिन्हित दीर्घ code, व्योम *x)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = container_of(n, काष्ठा dm_पूर्णांकegrity_c, reboot_notअगरier);

	DEBUG_prपूर्णांक("dm_integrity_reboot\n");

	dm_पूर्णांकegrity_enter_synchronous_mode(ic);

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम dm_पूर्णांकegrity_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = (काष्ठा dm_पूर्णांकegrity_c *)ti->निजी;
	पूर्णांक r;

	WARN_ON(unरेजिस्टर_reboot_notअगरier(&ic->reboot_notअगरier));

	del_समयr_sync(&ic->स्वतःcommit_समयr);

	अगर (ic->recalc_wq)
		drain_workqueue(ic->recalc_wq);

	अगर (ic->mode == 'B')
		cancel_delayed_work_sync(&ic->biपंचांगap_flush_work);

	queue_work(ic->commit_wq, &ic->commit_work);
	drain_workqueue(ic->commit_wq);

	अगर (ic->mode == 'J') अणु
		अगर (ic->meta_dev)
			queue_work(ic->ग_लिखोr_wq, &ic->ग_लिखोr_work);
		drain_workqueue(ic->ग_लिखोr_wq);
		dm_पूर्णांकegrity_flush_buffers(ic, true);
	पूर्ण

	अगर (ic->mode == 'B') अणु
		dm_पूर्णांकegrity_flush_buffers(ic, true);
#अगर 1
		/* set to 0 to test biपंचांगap replay code */
		init_journal(ic, 0, ic->journal_sections, 0);
		ic->sb->flags &= ~cpu_to_le32(SB_FLAG_सूचीTY_BITMAP);
		r = sync_rw_sb(ic, REQ_OP_WRITE, REQ_FUA);
		अगर (unlikely(r))
			dm_पूर्णांकegrity_io_error(ic, "writing superblock", r);
#पूर्ण_अगर
	पूर्ण

	BUG_ON(!RB_EMPTY_ROOT(&ic->in_progress));

	ic->journal_uptodate = true;
पूर्ण

अटल व्योम dm_पूर्णांकegrity_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = (काष्ठा dm_पूर्णांकegrity_c *)ti->निजी;
	__u64 old_provided_data_sectors = le64_to_cpu(ic->sb->provided_data_sectors);
	पूर्णांक r;

	DEBUG_prपूर्णांक("resume\n");

	अगर (ic->provided_data_sectors != old_provided_data_sectors) अणु
		अगर (ic->provided_data_sectors > old_provided_data_sectors &&
		    ic->mode == 'B' &&
		    ic->sb->log2_blocks_per_biपंचांगap_bit == ic->log2_blocks_per_biपंचांगap_bit) अणु
			rw_journal_sectors(ic, REQ_OP_READ, 0, 0,
					   ic->n_biपंचांगap_blocks * (BITMAP_BLOCK_SIZE >> SECTOR_SHIFT), शून्य);
			block_biपंचांगap_op(ic, ic->journal, old_provided_data_sectors,
					ic->provided_data_sectors - old_provided_data_sectors, BITMAP_OP_SET);
			rw_journal_sectors(ic, REQ_OP_WRITE, REQ_FUA | REQ_SYNC, 0,
					   ic->n_biपंचांगap_blocks * (BITMAP_BLOCK_SIZE >> SECTOR_SHIFT), शून्य);
		पूर्ण

		ic->sb->provided_data_sectors = cpu_to_le64(ic->provided_data_sectors);
		r = sync_rw_sb(ic, REQ_OP_WRITE, REQ_FUA);
		अगर (unlikely(r))
			dm_पूर्णांकegrity_io_error(ic, "writing superblock", r);
	पूर्ण

	अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_सूचीTY_BITMAP)) अणु
		DEBUG_prपूर्णांक("resume dirty_bitmap\n");
		rw_journal_sectors(ic, REQ_OP_READ, 0, 0,
				   ic->n_biपंचांगap_blocks * (BITMAP_BLOCK_SIZE >> SECTOR_SHIFT), शून्य);
		अगर (ic->mode == 'B') अणु
			अगर (ic->sb->log2_blocks_per_biपंचांगap_bit == ic->log2_blocks_per_biपंचांगap_bit &&
			    !ic->reset_recalculate_flag) अणु
				block_biपंचांगap_copy(ic, ic->recalc_biपंचांगap, ic->journal);
				block_biपंचांगap_copy(ic, ic->may_ग_लिखो_biपंचांगap, ic->journal);
				अगर (!block_biपंचांगap_op(ic, ic->journal, 0, ic->provided_data_sectors,
						     BITMAP_OP_TEST_ALL_CLEAR)) अणु
					ic->sb->flags |= cpu_to_le32(SB_FLAG_RECALCULATING);
					ic->sb->recalc_sector = cpu_to_le64(0);
				पूर्ण
			पूर्ण अन्यथा अणु
				DEBUG_prपूर्णांक("non-matching blocks_per_bitmap_bit: %u, %u\n",
					    ic->sb->log2_blocks_per_biपंचांगap_bit, ic->log2_blocks_per_biपंचांगap_bit);
				ic->sb->log2_blocks_per_biपंचांगap_bit = ic->log2_blocks_per_biपंचांगap_bit;
				block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, 0, ic->provided_data_sectors, BITMAP_OP_SET);
				block_biपंचांगap_op(ic, ic->may_ग_लिखो_biपंचांगap, 0, ic->provided_data_sectors, BITMAP_OP_SET);
				block_biपंचांगap_op(ic, ic->journal, 0, ic->provided_data_sectors, BITMAP_OP_SET);
				rw_journal_sectors(ic, REQ_OP_WRITE, REQ_FUA | REQ_SYNC, 0,
						   ic->n_biपंचांगap_blocks * (BITMAP_BLOCK_SIZE >> SECTOR_SHIFT), शून्य);
				ic->sb->flags |= cpu_to_le32(SB_FLAG_RECALCULATING);
				ic->sb->recalc_sector = cpu_to_le64(0);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(ic->sb->log2_blocks_per_biपंचांगap_bit == ic->log2_blocks_per_biपंचांगap_bit &&
			      block_biपंचांगap_op(ic, ic->journal, 0, ic->provided_data_sectors, BITMAP_OP_TEST_ALL_CLEAR)) ||
			    ic->reset_recalculate_flag) अणु
				ic->sb->flags |= cpu_to_le32(SB_FLAG_RECALCULATING);
				ic->sb->recalc_sector = cpu_to_le64(0);
			पूर्ण
			init_journal(ic, 0, ic->journal_sections, 0);
			replay_journal(ic);
			ic->sb->flags &= ~cpu_to_le32(SB_FLAG_सूचीTY_BITMAP);
		पूर्ण
		r = sync_rw_sb(ic, REQ_OP_WRITE, REQ_FUA);
		अगर (unlikely(r))
			dm_पूर्णांकegrity_io_error(ic, "writing superblock", r);
	पूर्ण अन्यथा अणु
		replay_journal(ic);
		अगर (ic->reset_recalculate_flag) अणु
			ic->sb->flags |= cpu_to_le32(SB_FLAG_RECALCULATING);
			ic->sb->recalc_sector = cpu_to_le64(0);
		पूर्ण
		अगर (ic->mode == 'B') अणु
			ic->sb->flags |= cpu_to_le32(SB_FLAG_सूचीTY_BITMAP);
			ic->sb->log2_blocks_per_biपंचांगap_bit = ic->log2_blocks_per_biपंचांगap_bit;
			r = sync_rw_sb(ic, REQ_OP_WRITE, REQ_FUA);
			अगर (unlikely(r))
				dm_पूर्णांकegrity_io_error(ic, "writing superblock", r);

			block_biपंचांगap_op(ic, ic->journal, 0, ic->provided_data_sectors, BITMAP_OP_CLEAR);
			block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, 0, ic->provided_data_sectors, BITMAP_OP_CLEAR);
			block_biपंचांगap_op(ic, ic->may_ग_लिखो_biपंचांगap, 0, ic->provided_data_sectors, BITMAP_OP_CLEAR);
			अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING) &&
			    le64_to_cpu(ic->sb->recalc_sector) < ic->provided_data_sectors) अणु
				block_biपंचांगap_op(ic, ic->journal, le64_to_cpu(ic->sb->recalc_sector),
						ic->provided_data_sectors - le64_to_cpu(ic->sb->recalc_sector), BITMAP_OP_SET);
				block_biपंचांगap_op(ic, ic->recalc_biपंचांगap, le64_to_cpu(ic->sb->recalc_sector),
						ic->provided_data_sectors - le64_to_cpu(ic->sb->recalc_sector), BITMAP_OP_SET);
				block_biपंचांगap_op(ic, ic->may_ग_लिखो_biपंचांगap, le64_to_cpu(ic->sb->recalc_sector),
						ic->provided_data_sectors - le64_to_cpu(ic->sb->recalc_sector), BITMAP_OP_SET);
			पूर्ण
			rw_journal_sectors(ic, REQ_OP_WRITE, REQ_FUA | REQ_SYNC, 0,
					   ic->n_biपंचांगap_blocks * (BITMAP_BLOCK_SIZE >> SECTOR_SHIFT), शून्य);
		पूर्ण
	पूर्ण

	DEBUG_prपूर्णांक("testing recalc: %x\n", ic->sb->flags);
	अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING)) अणु
		__u64 recalc_pos = le64_to_cpu(ic->sb->recalc_sector);
		DEBUG_prपूर्णांक("recalc pos: %llx / %llx\n", recalc_pos, ic->provided_data_sectors);
		अगर (recalc_pos < ic->provided_data_sectors) अणु
			queue_work(ic->recalc_wq, &ic->recalc_work);
		पूर्ण अन्यथा अगर (recalc_pos > ic->provided_data_sectors) अणु
			ic->sb->recalc_sector = cpu_to_le64(ic->provided_data_sectors);
			recalc_ग_लिखो_super(ic);
		पूर्ण
	पूर्ण

	ic->reboot_notअगरier.notअगरier_call = dm_पूर्णांकegrity_reboot;
	ic->reboot_notअगरier.next = शून्य;
	ic->reboot_notअगरier.priority = पूर्णांक_उच्च - 1;	/* be notअगरied after md and beक्रमe hardware drivers */
	WARN_ON(रेजिस्टर_reboot_notअगरier(&ic->reboot_notअगरier));

#अगर 0
	/* set to 1 to stress test synchronous mode */
	dm_पूर्णांकegrity_enter_synchronous_mode(ic);
#पूर्ण_अगर
पूर्ण

अटल व्योम dm_पूर्णांकegrity_status(काष्ठा dm_target *ti, status_type_t type,
				अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = (काष्ठा dm_पूर्णांकegrity_c *)ti->निजी;
	अचिन्हित arg_count;
	माप_प्रकार sz = 0;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%llu %llu",
			(अचिन्हित दीर्घ दीर्घ)atomic64_पढ़ो(&ic->number_of_mismatches),
			ic->provided_data_sectors);
		अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING))
			DMEMIT(" %llu", le64_to_cpu(ic->sb->recalc_sector));
		अन्यथा
			DMEMIT(" -");
		अवरोध;

	हाल STATUSTYPE_TABLE: अणु
		__u64 watermark_percentage = (__u64)(ic->journal_entries - ic->मुक्त_sectors_threshold) * 100;
		watermark_percentage += ic->journal_entries / 2;
		करो_भाग(watermark_percentage, ic->journal_entries);
		arg_count = 3;
		arg_count += !!ic->meta_dev;
		arg_count += ic->sectors_per_block != 1;
		arg_count += !!(ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING));
		arg_count += ic->reset_recalculate_flag;
		arg_count += ic->discard;
		arg_count += ic->mode == 'J';
		arg_count += ic->mode == 'J';
		arg_count += ic->mode == 'B';
		arg_count += ic->mode == 'B';
		arg_count += !!ic->पूर्णांकernal_hash_alg.alg_string;
		arg_count += !!ic->journal_crypt_alg.alg_string;
		arg_count += !!ic->journal_mac_alg.alg_string;
		arg_count += (ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_PADDING)) != 0;
		arg_count += (ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_HMAC)) != 0;
		arg_count += ic->legacy_recalculate;
		DMEMIT("%s %llu %u %c %u", ic->dev->name, ic->start,
		       ic->tag_size, ic->mode, arg_count);
		अगर (ic->meta_dev)
			DMEMIT(" meta_device:%s", ic->meta_dev->name);
		अगर (ic->sectors_per_block != 1)
			DMEMIT(" block_size:%u", ic->sectors_per_block << SECTOR_SHIFT);
		अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING))
			DMEMIT(" recalculate");
		अगर (ic->reset_recalculate_flag)
			DMEMIT(" reset_recalculate");
		अगर (ic->discard)
			DMEMIT(" allow_discards");
		DMEMIT(" journal_sectors:%u", ic->initial_sectors - SB_SECTORS);
		DMEMIT(" interleave_sectors:%u", 1U << ic->sb->log2_पूर्णांकerleave_sectors);
		DMEMIT(" buffer_sectors:%u", 1U << ic->log2_buffer_sectors);
		अगर (ic->mode == 'J') अणु
			DMEMIT(" journal_watermark:%u", (अचिन्हित)watermark_percentage);
			DMEMIT(" commit_time:%u", ic->स्वतःcommit_msec);
		पूर्ण
		अगर (ic->mode == 'B') अणु
			DMEMIT(" sectors_per_bit:%llu", (sector_t)ic->sectors_per_block << ic->log2_blocks_per_biपंचांगap_bit);
			DMEMIT(" bitmap_flush_interval:%u", jअगरfies_to_msecs(ic->biपंचांगap_flush_पूर्णांकerval));
		पूर्ण
		अगर ((ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_PADDING)) != 0)
			DMEMIT(" fix_padding");
		अगर ((ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_HMAC)) != 0)
			DMEMIT(" fix_hmac");
		अगर (ic->legacy_recalculate)
			DMEMIT(" legacy_recalculate");

#घोषणा EMIT_ALG(a, n)							\
		करो अणु							\
			अगर (ic->a.alg_string) अणु				\
				DMEMIT(" %s:%s", n, ic->a.alg_string);	\
				अगर (ic->a.key_string)			\
					DMEMIT(":%s", ic->a.key_string);\
			पूर्ण						\
		पूर्ण जबतक (0)
		EMIT_ALG(पूर्णांकernal_hash_alg, "internal_hash");
		EMIT_ALG(journal_crypt_alg, "journal_crypt");
		EMIT_ALG(journal_mac_alg, "journal_mac");
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dm_पूर्णांकegrity_iterate_devices(काष्ठा dm_target *ti,
					iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = ti->निजी;

	अगर (!ic->meta_dev)
		वापस fn(ti, ic->dev, ic->start + ic->initial_sectors + ic->metadata_run, ti->len, data);
	अन्यथा
		वापस fn(ti, ic->dev, 0, ti->len, data);
पूर्ण

अटल व्योम dm_पूर्णांकegrity_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = ti->निजी;

	अगर (ic->sectors_per_block > 1) अणु
		limits->logical_block_size = ic->sectors_per_block << SECTOR_SHIFT;
		limits->physical_block_size = ic->sectors_per_block << SECTOR_SHIFT;
		blk_limits_io_min(limits, ic->sectors_per_block << SECTOR_SHIFT);
	पूर्ण
पूर्ण

अटल व्योम calculate_journal_section_size(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	अचिन्हित sector_space = JOURNAL_SECTOR_DATA;

	ic->journal_sections = le32_to_cpu(ic->sb->journal_sections);
	ic->journal_entry_size = roundup(दुरत्व(काष्ठा journal_entry, last_bytes[ic->sectors_per_block]) + ic->tag_size,
					 JOURNAL_ENTRY_ROUNDUP);

	अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_HAVE_JOURNAL_MAC))
		sector_space -= JOURNAL_MAC_PER_SECTOR;
	ic->journal_entries_per_sector = sector_space / ic->journal_entry_size;
	ic->journal_section_entries = ic->journal_entries_per_sector * JOURNAL_BLOCK_SECTORS;
	ic->journal_section_sectors = (ic->journal_section_entries << ic->sb->log2_sectors_per_block) + JOURNAL_BLOCK_SECTORS;
	ic->journal_entries = ic->journal_section_entries * ic->journal_sections;
पूर्ण

अटल पूर्णांक calculate_device_limits(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	__u64 initial_sectors;

	calculate_journal_section_size(ic);
	initial_sectors = SB_SECTORS + (__u64)ic->journal_section_sectors * ic->journal_sections;
	अगर (initial_sectors + METADATA_PADDING_SECTORS >= ic->meta_device_sectors || initial_sectors > अच_पूर्णांक_उच्च)
		वापस -EINVAL;
	ic->initial_sectors = initial_sectors;

	अगर (!ic->meta_dev) अणु
		sector_t last_sector, last_area, last_offset;

		/* we have to मुख्यtain excessive padding क्रम compatibility with existing volumes */
		__u64 metadata_run_padding =
			ic->sb->flags & cpu_to_le32(SB_FLAG_FIXED_PADDING) ?
			(__u64)(METADATA_PADDING_SECTORS << SECTOR_SHIFT) :
			(__u64)(1 << SECTOR_SHIFT << METADATA_PADDING_SECTORS);

		ic->metadata_run = round_up((__u64)ic->tag_size << (ic->sb->log2_पूर्णांकerleave_sectors - ic->sb->log2_sectors_per_block),
					    metadata_run_padding) >> SECTOR_SHIFT;
		अगर (!(ic->metadata_run & (ic->metadata_run - 1)))
			ic->log2_metadata_run = __ffs(ic->metadata_run);
		अन्यथा
			ic->log2_metadata_run = -1;

		get_area_and_offset(ic, ic->provided_data_sectors - 1, &last_area, &last_offset);
		last_sector = get_data_sector(ic, last_area, last_offset);
		अगर (last_sector < ic->start || last_sector >= ic->meta_device_sectors)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		__u64 meta_size = (ic->provided_data_sectors >> ic->sb->log2_sectors_per_block) * ic->tag_size;
		meta_size = (meta_size + ((1U << (ic->log2_buffer_sectors + SECTOR_SHIFT)) - 1))
				>> (ic->log2_buffer_sectors + SECTOR_SHIFT);
		meta_size <<= ic->log2_buffer_sectors;
		अगर (ic->initial_sectors + meta_size < ic->initial_sectors ||
		    ic->initial_sectors + meta_size > ic->meta_device_sectors)
			वापस -EINVAL;
		ic->metadata_run = 1;
		ic->log2_metadata_run = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम get_provided_data_sectors(काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	अगर (!ic->meta_dev) अणु
		पूर्णांक test_bit;
		ic->provided_data_sectors = 0;
		क्रम (test_bit = fls64(ic->meta_device_sectors) - 1; test_bit >= 3; test_bit--) अणु
			__u64 prev_data_sectors = ic->provided_data_sectors;

			ic->provided_data_sectors |= (sector_t)1 << test_bit;
			अगर (calculate_device_limits(ic))
				ic->provided_data_sectors = prev_data_sectors;
		पूर्ण
	पूर्ण अन्यथा अणु
		ic->provided_data_sectors = ic->data_device_sectors;
		ic->provided_data_sectors &= ~(sector_t)(ic->sectors_per_block - 1);
	पूर्ण
पूर्ण

अटल पूर्णांक initialize_superblock(काष्ठा dm_पूर्णांकegrity_c *ic, अचिन्हित journal_sectors, अचिन्हित पूर्णांकerleave_sectors)
अणु
	अचिन्हित journal_sections;
	पूर्णांक test_bit;

	स_रखो(ic->sb, 0, SB_SECTORS << SECTOR_SHIFT);
	स_नकल(ic->sb->magic, SB_MAGIC, 8);
	ic->sb->पूर्णांकegrity_tag_size = cpu_to_le16(ic->tag_size);
	ic->sb->log2_sectors_per_block = __ffs(ic->sectors_per_block);
	अगर (ic->journal_mac_alg.alg_string)
		ic->sb->flags |= cpu_to_le32(SB_FLAG_HAVE_JOURNAL_MAC);

	calculate_journal_section_size(ic);
	journal_sections = journal_sectors / ic->journal_section_sectors;
	अगर (!journal_sections)
		journal_sections = 1;

	अगर (ic->fix_hmac && (ic->पूर्णांकernal_hash_alg.alg_string || ic->journal_mac_alg.alg_string)) अणु
		ic->sb->flags |= cpu_to_le32(SB_FLAG_FIXED_HMAC);
		get_अक्रमom_bytes(ic->sb->salt, SALT_SIZE);
	पूर्ण

	अगर (!ic->meta_dev) अणु
		अगर (ic->fix_padding)
			ic->sb->flags |= cpu_to_le32(SB_FLAG_FIXED_PADDING);
		ic->sb->journal_sections = cpu_to_le32(journal_sections);
		अगर (!पूर्णांकerleave_sectors)
			पूर्णांकerleave_sectors = DEFAULT_INTERLEAVE_SECTORS;
		ic->sb->log2_पूर्णांकerleave_sectors = __fls(पूर्णांकerleave_sectors);
		ic->sb->log2_पूर्णांकerleave_sectors = max((__u8)MIN_LOG2_INTERLEAVE_SECTORS, ic->sb->log2_पूर्णांकerleave_sectors);
		ic->sb->log2_पूर्णांकerleave_sectors = min((__u8)MAX_LOG2_INTERLEAVE_SECTORS, ic->sb->log2_पूर्णांकerleave_sectors);

		get_provided_data_sectors(ic);
		अगर (!ic->provided_data_sectors)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ic->sb->log2_पूर्णांकerleave_sectors = 0;

		get_provided_data_sectors(ic);
		अगर (!ic->provided_data_sectors)
			वापस -EINVAL;

try_smaller_buffer:
		ic->sb->journal_sections = cpu_to_le32(0);
		क्रम (test_bit = fls(journal_sections) - 1; test_bit >= 0; test_bit--) अणु
			__u32 prev_journal_sections = le32_to_cpu(ic->sb->journal_sections);
			__u32 test_journal_sections = prev_journal_sections | (1U << test_bit);
			अगर (test_journal_sections > journal_sections)
				जारी;
			ic->sb->journal_sections = cpu_to_le32(test_journal_sections);
			अगर (calculate_device_limits(ic))
				ic->sb->journal_sections = cpu_to_le32(prev_journal_sections);

		पूर्ण
		अगर (!le32_to_cpu(ic->sb->journal_sections)) अणु
			अगर (ic->log2_buffer_sectors > 3) अणु
				ic->log2_buffer_sectors--;
				जाओ try_smaller_buffer;
			पूर्ण
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ic->sb->provided_data_sectors = cpu_to_le64(ic->provided_data_sectors);

	sb_set_version(ic);

	वापस 0;
पूर्ण

अटल व्योम dm_पूर्णांकegrity_set(काष्ठा dm_target *ti, काष्ठा dm_पूर्णांकegrity_c *ic)
अणु
	काष्ठा gendisk *disk = dm_disk(dm_table_get_md(ti->table));
	काष्ठा blk_पूर्णांकegrity bi;

	स_रखो(&bi, 0, माप(bi));
	bi.profile = &dm_पूर्णांकegrity_profile;
	bi.tuple_size = ic->tag_size;
	bi.tag_size = bi.tuple_size;
	bi.पूर्णांकerval_exp = ic->sb->log2_sectors_per_block + SECTOR_SHIFT;

	blk_पूर्णांकegrity_रेजिस्टर(disk, &bi);
	blk_queue_max_पूर्णांकegrity_segments(disk->queue, अच_पूर्णांक_उच्च);
पूर्ण

अटल व्योम dm_पूर्णांकegrity_मुक्त_page_list(काष्ठा page_list *pl)
अणु
	अचिन्हित i;

	अगर (!pl)
		वापस;
	क्रम (i = 0; pl[i].page; i++)
		__मुक्त_page(pl[i].page);
	kvमुक्त(pl);
पूर्ण

अटल काष्ठा page_list *dm_पूर्णांकegrity_alloc_page_list(अचिन्हित n_pages)
अणु
	काष्ठा page_list *pl;
	अचिन्हित i;

	pl = kvदो_स्मृति_array(n_pages + 1, माप(काष्ठा page_list), GFP_KERNEL | __GFP_ZERO);
	अगर (!pl)
		वापस शून्य;

	क्रम (i = 0; i < n_pages; i++) अणु
		pl[i].page = alloc_page(GFP_KERNEL);
		अगर (!pl[i].page) अणु
			dm_पूर्णांकegrity_मुक्त_page_list(pl);
			वापस शून्य;
		पूर्ण
		अगर (i)
			pl[i - 1].next = &pl[i];
	पूर्ण
	pl[i].page = शून्य;
	pl[i].next = शून्य;

	वापस pl;
पूर्ण

अटल व्योम dm_पूर्णांकegrity_मुक्त_journal_scatterlist(काष्ठा dm_पूर्णांकegrity_c *ic, काष्ठा scatterlist **sl)
अणु
	अचिन्हित i;
	क्रम (i = 0; i < ic->journal_sections; i++)
		kvमुक्त(sl[i]);
	kvमुक्त(sl);
पूर्ण

अटल काष्ठा scatterlist **dm_पूर्णांकegrity_alloc_journal_scatterlist(काष्ठा dm_पूर्णांकegrity_c *ic,
								   काष्ठा page_list *pl)
अणु
	काष्ठा scatterlist **sl;
	अचिन्हित i;

	sl = kvदो_स्मृति_array(ic->journal_sections,
			    माप(काष्ठा scatterlist *),
			    GFP_KERNEL | __GFP_ZERO);
	अगर (!sl)
		वापस शून्य;

	क्रम (i = 0; i < ic->journal_sections; i++) अणु
		काष्ठा scatterlist *s;
		अचिन्हित start_index, start_offset;
		अचिन्हित end_index, end_offset;
		अचिन्हित n_pages;
		अचिन्हित idx;

		page_list_location(ic, i, 0, &start_index, &start_offset);
		page_list_location(ic, i, ic->journal_section_sectors - 1,
				   &end_index, &end_offset);

		n_pages = (end_index - start_index + 1);

		s = kvदो_स्मृति_array(n_pages, माप(काष्ठा scatterlist),
				   GFP_KERNEL);
		अगर (!s) अणु
			dm_पूर्णांकegrity_मुक्त_journal_scatterlist(ic, sl);
			वापस शून्य;
		पूर्ण

		sg_init_table(s, n_pages);
		क्रम (idx = start_index; idx <= end_index; idx++) अणु
			अक्षर *va = lowmem_page_address(pl[idx].page);
			अचिन्हित start = 0, end = PAGE_SIZE;
			अगर (idx == start_index)
				start = start_offset;
			अगर (idx == end_index)
				end = end_offset + (1 << SECTOR_SHIFT);
			sg_set_buf(&s[idx - start_index], va + start, end - start);
		पूर्ण

		sl[i] = s;
	पूर्ण

	वापस sl;
पूर्ण

अटल व्योम मुक्त_alg(काष्ठा alg_spec *a)
अणु
	kमुक्त_sensitive(a->alg_string);
	kमुक्त_sensitive(a->key);
	स_रखो(a, 0, माप *a);
पूर्ण

अटल पूर्णांक get_alg_and_key(स्थिर अक्षर *arg, काष्ठा alg_spec *a, अक्षर **error, अक्षर *error_inval)
अणु
	अक्षर *k;

	मुक्त_alg(a);

	a->alg_string = kstrdup(म_अक्षर(arg, ':') + 1, GFP_KERNEL);
	अगर (!a->alg_string)
		जाओ nomem;

	k = म_अक्षर(a->alg_string, ':');
	अगर (k) अणु
		*k = 0;
		a->key_string = k + 1;
		अगर (म_माप(a->key_string) & 1)
			जाओ inval;

		a->key_size = म_माप(a->key_string) / 2;
		a->key = kदो_स्मृति(a->key_size, GFP_KERNEL);
		अगर (!a->key)
			जाओ nomem;
		अगर (hex2bin(a->key, a->key_string, a->key_size))
			जाओ inval;
	पूर्ण

	वापस 0;
inval:
	*error = error_inval;
	वापस -EINVAL;
nomem:
	*error = "Out of memory for an argument";
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक get_mac(काष्ठा crypto_shash **hash, काष्ठा alg_spec *a, अक्षर **error,
		   अक्षर *error_alg, अक्षर *error_key)
अणु
	पूर्णांक r;

	अगर (a->alg_string) अणु
		*hash = crypto_alloc_shash(a->alg_string, 0, CRYPTO_ALG_ALLOCATES_MEMORY);
		अगर (IS_ERR(*hash)) अणु
			*error = error_alg;
			r = PTR_ERR(*hash);
			*hash = शून्य;
			वापस r;
		पूर्ण

		अगर (a->key) अणु
			r = crypto_shash_setkey(*hash, a->key, a->key_size);
			अगर (r) अणु
				*error = error_key;
				वापस r;
			पूर्ण
		पूर्ण अन्यथा अगर (crypto_shash_get_flags(*hash) & CRYPTO_TFM_NEED_KEY) अणु
			*error = error_key;
			वापस -ENOKEY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक create_journal(काष्ठा dm_पूर्णांकegrity_c *ic, अक्षर **error)
अणु
	पूर्णांक r = 0;
	अचिन्हित i;
	__u64 journal_pages, journal_desc_size, journal_tree_size;
	अचिन्हित अक्षर *crypt_data = शून्य, *crypt_iv = शून्य;
	काष्ठा skcipher_request *req = शून्य;

	ic->commit_ids[0] = cpu_to_le64(0x1111111111111111ULL);
	ic->commit_ids[1] = cpu_to_le64(0x2222222222222222ULL);
	ic->commit_ids[2] = cpu_to_le64(0x3333333333333333ULL);
	ic->commit_ids[3] = cpu_to_le64(0x4444444444444444ULL);

	journal_pages = roundup((__u64)ic->journal_sections * ic->journal_section_sectors,
				PAGE_SIZE >> SECTOR_SHIFT) >> (PAGE_SHIFT - SECTOR_SHIFT);
	journal_desc_size = journal_pages * माप(काष्ठा page_list);
	अगर (journal_pages >= totalram_pages() - totalhigh_pages() || journal_desc_size > अच_दीर्घ_उच्च) अणु
		*error = "Journal doesn't fit into memory";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण
	ic->journal_pages = journal_pages;

	ic->journal = dm_पूर्णांकegrity_alloc_page_list(ic->journal_pages);
	अगर (!ic->journal) अणु
		*error = "Could not allocate memory for journal";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण
	अगर (ic->journal_crypt_alg.alg_string) अणु
		अचिन्हित ivsize, blocksize;
		काष्ठा journal_completion comp;

		comp.ic = ic;
		ic->journal_crypt = crypto_alloc_skcipher(ic->journal_crypt_alg.alg_string, 0, CRYPTO_ALG_ALLOCATES_MEMORY);
		अगर (IS_ERR(ic->journal_crypt)) अणु
			*error = "Invalid journal cipher";
			r = PTR_ERR(ic->journal_crypt);
			ic->journal_crypt = शून्य;
			जाओ bad;
		पूर्ण
		ivsize = crypto_skcipher_ivsize(ic->journal_crypt);
		blocksize = crypto_skcipher_blocksize(ic->journal_crypt);

		अगर (ic->journal_crypt_alg.key) अणु
			r = crypto_skcipher_setkey(ic->journal_crypt, ic->journal_crypt_alg.key,
						   ic->journal_crypt_alg.key_size);
			अगर (r) अणु
				*error = "Error setting encryption key";
				जाओ bad;
			पूर्ण
		पूर्ण
		DEBUG_prपूर्णांक("cipher %s, block size %u iv size %u\n",
			    ic->journal_crypt_alg.alg_string, blocksize, ivsize);

		ic->journal_io = dm_पूर्णांकegrity_alloc_page_list(ic->journal_pages);
		अगर (!ic->journal_io) अणु
			*error = "Could not allocate memory for journal io";
			r = -ENOMEM;
			जाओ bad;
		पूर्ण

		अगर (blocksize == 1) अणु
			काष्ठा scatterlist *sg;

			req = skcipher_request_alloc(ic->journal_crypt, GFP_KERNEL);
			अगर (!req) अणु
				*error = "Could not allocate crypt request";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण

			crypt_iv = kzalloc(ivsize, GFP_KERNEL);
			अगर (!crypt_iv) अणु
				*error = "Could not allocate iv";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण

			ic->journal_xor = dm_पूर्णांकegrity_alloc_page_list(ic->journal_pages);
			अगर (!ic->journal_xor) अणु
				*error = "Could not allocate memory for journal xor";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण

			sg = kvदो_स्मृति_array(ic->journal_pages + 1,
					    माप(काष्ठा scatterlist),
					    GFP_KERNEL);
			अगर (!sg) अणु
				*error = "Unable to allocate sg list";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण
			sg_init_table(sg, ic->journal_pages + 1);
			क्रम (i = 0; i < ic->journal_pages; i++) अणु
				अक्षर *va = lowmem_page_address(ic->journal_xor[i].page);
				clear_page(va);
				sg_set_buf(&sg[i], va, PAGE_SIZE);
			पूर्ण
			sg_set_buf(&sg[i], &ic->commit_ids, माप ic->commit_ids);

			skcipher_request_set_crypt(req, sg, sg,
						   PAGE_SIZE * ic->journal_pages + माप ic->commit_ids, crypt_iv);
			init_completion(&comp.comp);
			comp.in_flight = (atomic_t)ATOMIC_INIT(1);
			अगर (करो_crypt(true, req, &comp))
				रुको_क्रम_completion(&comp.comp);
			kvमुक्त(sg);
			r = dm_पूर्णांकegrity_failed(ic);
			अगर (r) अणु
				*error = "Unable to encrypt journal";
				जाओ bad;
			पूर्ण
			DEBUG_bytes(lowmem_page_address(ic->journal_xor[0].page), 64, "xor data");

			crypto_मुक्त_skcipher(ic->journal_crypt);
			ic->journal_crypt = शून्य;
		पूर्ण अन्यथा अणु
			अचिन्हित crypt_len = roundup(ivsize, blocksize);

			req = skcipher_request_alloc(ic->journal_crypt, GFP_KERNEL);
			अगर (!req) अणु
				*error = "Could not allocate crypt request";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण

			crypt_iv = kदो_स्मृति(ivsize, GFP_KERNEL);
			अगर (!crypt_iv) अणु
				*error = "Could not allocate iv";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण

			crypt_data = kदो_स्मृति(crypt_len, GFP_KERNEL);
			अगर (!crypt_data) अणु
				*error = "Unable to allocate crypt data";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण

			ic->journal_scatterlist = dm_पूर्णांकegrity_alloc_journal_scatterlist(ic, ic->journal);
			अगर (!ic->journal_scatterlist) अणु
				*error = "Unable to allocate sg list";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण
			ic->journal_io_scatterlist = dm_पूर्णांकegrity_alloc_journal_scatterlist(ic, ic->journal_io);
			अगर (!ic->journal_io_scatterlist) अणु
				*error = "Unable to allocate sg list";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण
			ic->sk_requests = kvदो_स्मृति_array(ic->journal_sections,
							 माप(काष्ठा skcipher_request *),
							 GFP_KERNEL | __GFP_ZERO);
			अगर (!ic->sk_requests) अणु
				*error = "Unable to allocate sk requests";
				r = -ENOMEM;
				जाओ bad;
			पूर्ण
			क्रम (i = 0; i < ic->journal_sections; i++) अणु
				काष्ठा scatterlist sg;
				काष्ठा skcipher_request *section_req;
				__le32 section_le = cpu_to_le32(i);

				स_रखो(crypt_iv, 0x00, ivsize);
				स_रखो(crypt_data, 0x00, crypt_len);
				स_नकल(crypt_data, &section_le, min((माप_प्रकार)crypt_len, माप(section_le)));

				sg_init_one(&sg, crypt_data, crypt_len);
				skcipher_request_set_crypt(req, &sg, &sg, crypt_len, crypt_iv);
				init_completion(&comp.comp);
				comp.in_flight = (atomic_t)ATOMIC_INIT(1);
				अगर (करो_crypt(true, req, &comp))
					रुको_क्रम_completion(&comp.comp);

				r = dm_पूर्णांकegrity_failed(ic);
				अगर (r) अणु
					*error = "Unable to generate iv";
					जाओ bad;
				पूर्ण

				section_req = skcipher_request_alloc(ic->journal_crypt, GFP_KERNEL);
				अगर (!section_req) अणु
					*error = "Unable to allocate crypt request";
					r = -ENOMEM;
					जाओ bad;
				पूर्ण
				section_req->iv = kदो_स्मृति_array(ivsize, 2,
								GFP_KERNEL);
				अगर (!section_req->iv) अणु
					skcipher_request_मुक्त(section_req);
					*error = "Unable to allocate iv";
					r = -ENOMEM;
					जाओ bad;
				पूर्ण
				स_नकल(section_req->iv + ivsize, crypt_data, ivsize);
				section_req->cryptlen = (माप_प्रकार)ic->journal_section_sectors << SECTOR_SHIFT;
				ic->sk_requests[i] = section_req;
				DEBUG_bytes(crypt_data, ivsize, "iv(%u)", i);
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < N_COMMIT_IDS; i++) अणु
		अचिन्हित j;
retest_commit_id:
		क्रम (j = 0; j < i; j++) अणु
			अगर (ic->commit_ids[j] == ic->commit_ids[i]) अणु
				ic->commit_ids[i] = cpu_to_le64(le64_to_cpu(ic->commit_ids[i]) + 1);
				जाओ retest_commit_id;
			पूर्ण
		पूर्ण
		DEBUG_prपूर्णांक("commit id %u: %016llx\n", i, ic->commit_ids[i]);
	पूर्ण

	journal_tree_size = (__u64)ic->journal_entries * माप(काष्ठा journal_node);
	अगर (journal_tree_size > अच_दीर्घ_उच्च) अणु
		*error = "Journal doesn't fit into memory";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण
	ic->journal_tree = kvदो_स्मृति(journal_tree_size, GFP_KERNEL);
	अगर (!ic->journal_tree) अणु
		*error = "Could not allocate memory for journal tree";
		r = -ENOMEM;
	पूर्ण
bad:
	kमुक्त(crypt_data);
	kमुक्त(crypt_iv);
	skcipher_request_मुक्त(req);

	वापस r;
पूर्ण

/*
 * Conकाष्ठा a पूर्णांकegrity mapping
 *
 * Arguments:
 *	device
 *	offset from the start of the device
 *	tag size
 *	D - direct ग_लिखोs, J - journal ग_लिखोs, B - biपंचांगap mode, R - recovery mode
 *	number of optional arguments
 *	optional arguments:
 *		journal_sectors
 *		पूर्णांकerleave_sectors
 *		buffer_sectors
 *		journal_watermark
 *		commit_समय
 *		meta_device
 *		block_size
 *		sectors_per_bit
 *		biपंचांगap_flush_पूर्णांकerval
 *		पूर्णांकernal_hash
 *		journal_crypt
 *		journal_mac
 *		recalculate
 */
अटल पूर्णांक dm_पूर्णांकegrity_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic;
	अक्षर dummy;
	पूर्णांक r;
	अचिन्हित extra_args;
	काष्ठा dm_arg_set as;
	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 18, "Invalid number of feature args"पूर्ण,
	पूर्ण;
	अचिन्हित journal_sectors, पूर्णांकerleave_sectors, buffer_sectors, journal_watermark, sync_msec;
	bool should_ग_लिखो_sb;
	__u64 threshold;
	अचिन्हित दीर्घ दीर्घ start;
	__s8 log2_sectors_per_biपंचांगap_bit = -1;
	__s8 log2_blocks_per_biपंचांगap_bit;
	__u64 bits_in_journal;
	__u64 n_biपंचांगap_bits;

#घोषणा सूचीECT_ARGUMENTS	4

	अगर (argc <= सूचीECT_ARGUMENTS) अणु
		ti->error = "Invalid argument count";
		वापस -EINVAL;
	पूर्ण

	ic = kzalloc(माप(काष्ठा dm_पूर्णांकegrity_c), GFP_KERNEL);
	अगर (!ic) अणु
		ti->error = "Cannot allocate integrity context";
		वापस -ENOMEM;
	पूर्ण
	ti->निजी = ic;
	ti->per_io_data_size = माप(काष्ठा dm_पूर्णांकegrity_io);
	ic->ti = ti;

	ic->in_progress = RB_ROOT;
	INIT_LIST_HEAD(&ic->रुको_list);
	init_रुकोqueue_head(&ic->endio_रुको);
	bio_list_init(&ic->flush_bio_list);
	init_रुकोqueue_head(&ic->copy_to_journal_रुको);
	init_completion(&ic->crypto_backoff);
	atomic64_set(&ic->number_of_mismatches, 0);
	ic->biपंचांगap_flush_पूर्णांकerval = BITMAP_FLUSH_INTERVAL;

	r = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &ic->dev);
	अगर (r) अणु
		ti->error = "Device lookup failed";
		जाओ bad;
	पूर्ण

	अगर (माला_पूछो(argv[1], "%llu%c", &start, &dummy) != 1 || start != (sector_t)start) अणु
		ti->error = "Invalid starting offset";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	ic->start = start;

	अगर (म_भेद(argv[2], "-")) अणु
		अगर (माला_पूछो(argv[2], "%u%c", &ic->tag_size, &dummy) != 1 || !ic->tag_size) अणु
			ti->error = "Invalid tag size";
			r = -EINVAL;
			जाओ bad;
		पूर्ण
	पूर्ण

	अगर (!म_भेद(argv[3], "J") || !म_भेद(argv[3], "B") ||
	    !म_भेद(argv[3], "D") || !म_भेद(argv[3], "R")) अणु
		ic->mode = argv[3][0];
	पूर्ण अन्यथा अणु
		ti->error = "Invalid mode (expecting J, B, D, R)";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	journal_sectors = 0;
	पूर्णांकerleave_sectors = DEFAULT_INTERLEAVE_SECTORS;
	buffer_sectors = DEFAULT_BUFFER_SECTORS;
	journal_watermark = DEFAULT_JOURNAL_WATERMARK;
	sync_msec = DEFAULT_SYNC_MSEC;
	ic->sectors_per_block = 1;

	as.argc = argc - सूचीECT_ARGUMENTS;
	as.argv = argv + सूचीECT_ARGUMENTS;
	r = dm_पढ़ो_arg_group(_args, &as, &extra_args, &ti->error);
	अगर (r)
		जाओ bad;

	जबतक (extra_args--) अणु
		स्थिर अक्षर *opt_string;
		अचिन्हित val;
		अचिन्हित दीर्घ दीर्घ llval;
		opt_string = dm_shअगरt_arg(&as);
		अगर (!opt_string) अणु
			r = -EINVAL;
			ti->error = "Not enough feature arguments";
			जाओ bad;
		पूर्ण
		अगर (माला_पूछो(opt_string, "journal_sectors:%u%c", &val, &dummy) == 1)
			journal_sectors = val ? val : 1;
		अन्यथा अगर (माला_पूछो(opt_string, "interleave_sectors:%u%c", &val, &dummy) == 1)
			पूर्णांकerleave_sectors = val;
		अन्यथा अगर (माला_पूछो(opt_string, "buffer_sectors:%u%c", &val, &dummy) == 1)
			buffer_sectors = val;
		अन्यथा अगर (माला_पूछो(opt_string, "journal_watermark:%u%c", &val, &dummy) == 1 && val <= 100)
			journal_watermark = val;
		अन्यथा अगर (माला_पूछो(opt_string, "commit_time:%u%c", &val, &dummy) == 1)
			sync_msec = val;
		अन्यथा अगर (!म_भेदन(opt_string, "meta_device:", म_माप("meta_device:"))) अणु
			अगर (ic->meta_dev) अणु
				dm_put_device(ti, ic->meta_dev);
				ic->meta_dev = शून्य;
			पूर्ण
			r = dm_get_device(ti, म_अक्षर(opt_string, ':') + 1,
					  dm_table_get_mode(ti->table), &ic->meta_dev);
			अगर (r) अणु
				ti->error = "Device lookup failed";
				जाओ bad;
			पूर्ण
		पूर्ण अन्यथा अगर (माला_पूछो(opt_string, "block_size:%u%c", &val, &dummy) == 1) अणु
			अगर (val < 1 << SECTOR_SHIFT ||
			    val > MAX_SECTORS_PER_BLOCK << SECTOR_SHIFT ||
			    (val & (val -1))) अणु
				r = -EINVAL;
				ti->error = "Invalid block_size argument";
				जाओ bad;
			पूर्ण
			ic->sectors_per_block = val >> SECTOR_SHIFT;
		पूर्ण अन्यथा अगर (माला_पूछो(opt_string, "sectors_per_bit:%llu%c", &llval, &dummy) == 1) अणु
			log2_sectors_per_biपंचांगap_bit = !llval ? 0 : __ilog2_u64(llval);
		पूर्ण अन्यथा अगर (माला_पूछो(opt_string, "bitmap_flush_interval:%u%c", &val, &dummy) == 1) अणु
			अगर (val >= (uपूर्णांक64_t)अच_पूर्णांक_उच्च * 1000 / HZ) अणु
				r = -EINVAL;
				ti->error = "Invalid bitmap_flush_interval argument";
				जाओ bad;
			पूर्ण
			ic->biपंचांगap_flush_पूर्णांकerval = msecs_to_jअगरfies(val);
		पूर्ण अन्यथा अगर (!म_भेदन(opt_string, "internal_hash:", म_माप("internal_hash:"))) अणु
			r = get_alg_and_key(opt_string, &ic->पूर्णांकernal_hash_alg, &ti->error,
					    "Invalid internal_hash argument");
			अगर (r)
				जाओ bad;
		पूर्ण अन्यथा अगर (!म_भेदन(opt_string, "journal_crypt:", म_माप("journal_crypt:"))) अणु
			r = get_alg_and_key(opt_string, &ic->journal_crypt_alg, &ti->error,
					    "Invalid journal_crypt argument");
			अगर (r)
				जाओ bad;
		पूर्ण अन्यथा अगर (!म_भेदन(opt_string, "journal_mac:", म_माप("journal_mac:"))) अणु
			r = get_alg_and_key(opt_string, &ic->journal_mac_alg, &ti->error,
					    "Invalid journal_mac argument");
			अगर (r)
				जाओ bad;
		पूर्ण अन्यथा अगर (!म_भेद(opt_string, "recalculate")) अणु
			ic->recalculate_flag = true;
		पूर्ण अन्यथा अगर (!म_भेद(opt_string, "reset_recalculate")) अणु
			ic->recalculate_flag = true;
			ic->reset_recalculate_flag = true;
		पूर्ण अन्यथा अगर (!म_भेद(opt_string, "allow_discards")) अणु
			ic->discard = true;
		पूर्ण अन्यथा अगर (!म_भेद(opt_string, "fix_padding")) अणु
			ic->fix_padding = true;
		पूर्ण अन्यथा अगर (!म_भेद(opt_string, "fix_hmac")) अणु
			ic->fix_hmac = true;
		पूर्ण अन्यथा अगर (!म_भेद(opt_string, "legacy_recalculate")) अणु
			ic->legacy_recalculate = true;
		पूर्ण अन्यथा अणु
			r = -EINVAL;
			ti->error = "Invalid argument";
			जाओ bad;
		पूर्ण
	पूर्ण

	ic->data_device_sectors = i_size_पढ़ो(ic->dev->bdev->bd_inode) >> SECTOR_SHIFT;
	अगर (!ic->meta_dev)
		ic->meta_device_sectors = ic->data_device_sectors;
	अन्यथा
		ic->meta_device_sectors = i_size_पढ़ो(ic->meta_dev->bdev->bd_inode) >> SECTOR_SHIFT;

	अगर (!journal_sectors) अणु
		journal_sectors = min((sector_t)DEFAULT_MAX_JOURNAL_SECTORS,
				      ic->data_device_sectors >> DEFAULT_JOURNAL_SIZE_FACTOR);
	पूर्ण

	अगर (!buffer_sectors)
		buffer_sectors = 1;
	ic->log2_buffer_sectors = min((पूर्णांक)__fls(buffer_sectors), 31 - SECTOR_SHIFT);

	r = get_mac(&ic->पूर्णांकernal_hash, &ic->पूर्णांकernal_hash_alg, &ti->error,
		    "Invalid internal hash", "Error setting internal hash key");
	अगर (r)
		जाओ bad;

	r = get_mac(&ic->journal_mac, &ic->journal_mac_alg, &ti->error,
		    "Invalid journal mac", "Error setting journal mac key");
	अगर (r)
		जाओ bad;

	अगर (!ic->tag_size) अणु
		अगर (!ic->पूर्णांकernal_hash) अणु
			ti->error = "Unknown tag size";
			r = -EINVAL;
			जाओ bad;
		पूर्ण
		ic->tag_size = crypto_shash_digestsize(ic->पूर्णांकernal_hash);
	पूर्ण
	अगर (ic->tag_size > MAX_TAG_SIZE) अणु
		ti->error = "Too big tag size";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	अगर (!(ic->tag_size & (ic->tag_size - 1)))
		ic->log2_tag_size = __ffs(ic->tag_size);
	अन्यथा
		ic->log2_tag_size = -1;

	अगर (ic->mode == 'B' && !ic->पूर्णांकernal_hash) अणु
		r = -EINVAL;
		ti->error = "Bitmap mode can be only used with internal hash";
		जाओ bad;
	पूर्ण

	अगर (ic->discard && !ic->पूर्णांकernal_hash) अणु
		r = -EINVAL;
		ti->error = "Discard can be only used with internal hash";
		जाओ bad;
	पूर्ण

	ic->स्वतःcommit_jअगरfies = msecs_to_jअगरfies(sync_msec);
	ic->स्वतःcommit_msec = sync_msec;
	समयr_setup(&ic->स्वतःcommit_समयr, स्वतःcommit_fn, 0);

	ic->io = dm_io_client_create();
	अगर (IS_ERR(ic->io)) अणु
		r = PTR_ERR(ic->io);
		ic->io = शून्य;
		ti->error = "Cannot allocate dm io";
		जाओ bad;
	पूर्ण

	r = mempool_init_slab_pool(&ic->journal_io_mempool, JOURNAL_IO_MEMPOOL, journal_io_cache);
	अगर (r) अणु
		ti->error = "Cannot allocate mempool";
		जाओ bad;
	पूर्ण

	ic->metadata_wq = alloc_workqueue("dm-integrity-metadata",
					  WQ_MEM_RECLAIM, METADATA_WORKQUEUE_MAX_ACTIVE);
	अगर (!ic->metadata_wq) अणु
		ti->error = "Cannot allocate workqueue";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	/*
	 * If this workqueue were percpu, it would cause bio reordering
	 * and reduced perक्रमmance.
	 */
	ic->रुको_wq = alloc_workqueue("dm-integrity-wait", WQ_MEM_RECLAIM | WQ_UNBOUND, 1);
	अगर (!ic->रुको_wq) अणु
		ti->error = "Cannot allocate workqueue";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	ic->offload_wq = alloc_workqueue("dm-integrity-offload", WQ_MEM_RECLAIM,
					  METADATA_WORKQUEUE_MAX_ACTIVE);
	अगर (!ic->offload_wq) अणु
		ti->error = "Cannot allocate workqueue";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	ic->commit_wq = alloc_workqueue("dm-integrity-commit", WQ_MEM_RECLAIM, 1);
	अगर (!ic->commit_wq) अणु
		ti->error = "Cannot allocate workqueue";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण
	INIT_WORK(&ic->commit_work, पूर्णांकegrity_commit);

	अगर (ic->mode == 'J' || ic->mode == 'B') अणु
		ic->ग_लिखोr_wq = alloc_workqueue("dm-integrity-writer", WQ_MEM_RECLAIM, 1);
		अगर (!ic->ग_लिखोr_wq) अणु
			ti->error = "Cannot allocate workqueue";
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
		INIT_WORK(&ic->ग_लिखोr_work, पूर्णांकegrity_ग_लिखोr);
	पूर्ण

	ic->sb = alloc_pages_exact(SB_SECTORS << SECTOR_SHIFT, GFP_KERNEL);
	अगर (!ic->sb) अणु
		r = -ENOMEM;
		ti->error = "Cannot allocate superblock area";
		जाओ bad;
	पूर्ण

	r = sync_rw_sb(ic, REQ_OP_READ, 0);
	अगर (r) अणु
		ti->error = "Error reading superblock";
		जाओ bad;
	पूर्ण
	should_ग_लिखो_sb = false;
	अगर (स_भेद(ic->sb->magic, SB_MAGIC, 8)) अणु
		अगर (ic->mode != 'R') अणु
			अगर (स_प्रथम_inv(ic->sb, 0, SB_SECTORS << SECTOR_SHIFT)) अणु
				r = -EINVAL;
				ti->error = "The device is not initialized";
				जाओ bad;
			पूर्ण
		पूर्ण

		r = initialize_superblock(ic, journal_sectors, पूर्णांकerleave_sectors);
		अगर (r) अणु
			ti->error = "Could not initialize superblock";
			जाओ bad;
		पूर्ण
		अगर (ic->mode != 'R')
			should_ग_लिखो_sb = true;
	पूर्ण

	अगर (!ic->sb->version || ic->sb->version > SB_VERSION_5) अणु
		r = -EINVAL;
		ti->error = "Unknown version";
		जाओ bad;
	पूर्ण
	अगर (le16_to_cpu(ic->sb->पूर्णांकegrity_tag_size) != ic->tag_size) अणु
		r = -EINVAL;
		ti->error = "Tag size doesn't match the information in superblock";
		जाओ bad;
	पूर्ण
	अगर (ic->sb->log2_sectors_per_block != __ffs(ic->sectors_per_block)) अणु
		r = -EINVAL;
		ti->error = "Block size doesn't match the information in superblock";
		जाओ bad;
	पूर्ण
	अगर (!le32_to_cpu(ic->sb->journal_sections)) अणु
		r = -EINVAL;
		ti->error = "Corrupted superblock, journal_sections is 0";
		जाओ bad;
	पूर्ण
	/* make sure that ti->max_io_len करोesn't overflow */
	अगर (!ic->meta_dev) अणु
		अगर (ic->sb->log2_पूर्णांकerleave_sectors < MIN_LOG2_INTERLEAVE_SECTORS ||
		    ic->sb->log2_पूर्णांकerleave_sectors > MAX_LOG2_INTERLEAVE_SECTORS) अणु
			r = -EINVAL;
			ti->error = "Invalid interleave_sectors in the superblock";
			जाओ bad;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ic->sb->log2_पूर्णांकerleave_sectors) अणु
			r = -EINVAL;
			ti->error = "Invalid interleave_sectors in the superblock";
			जाओ bad;
		पूर्ण
	पूर्ण
	अगर (!!(ic->sb->flags & cpu_to_le32(SB_FLAG_HAVE_JOURNAL_MAC)) != !!ic->journal_mac_alg.alg_string) अणु
		r = -EINVAL;
		ti->error = "Journal mac mismatch";
		जाओ bad;
	पूर्ण

	get_provided_data_sectors(ic);
	अगर (!ic->provided_data_sectors) अणु
		r = -EINVAL;
		ti->error = "The device is too small";
		जाओ bad;
	पूर्ण

try_smaller_buffer:
	r = calculate_device_limits(ic);
	अगर (r) अणु
		अगर (ic->meta_dev) अणु
			अगर (ic->log2_buffer_sectors > 3) अणु
				ic->log2_buffer_sectors--;
				जाओ try_smaller_buffer;
			पूर्ण
		पूर्ण
		ti->error = "The device is too small";
		जाओ bad;
	पूर्ण

	अगर (log2_sectors_per_biपंचांगap_bit < 0)
		log2_sectors_per_biपंचांगap_bit = __fls(DEFAULT_SECTORS_PER_BITMAP_BIT);
	अगर (log2_sectors_per_biपंचांगap_bit < ic->sb->log2_sectors_per_block)
		log2_sectors_per_biपंचांगap_bit = ic->sb->log2_sectors_per_block;

	bits_in_journal = ((__u64)ic->journal_section_sectors * ic->journal_sections) << (SECTOR_SHIFT + 3);
	अगर (bits_in_journal > अच_पूर्णांक_उच्च)
		bits_in_journal = अच_पूर्णांक_उच्च;
	जबतक (bits_in_journal < (ic->provided_data_sectors + ((sector_t)1 << log2_sectors_per_biपंचांगap_bit) - 1) >> log2_sectors_per_biपंचांगap_bit)
		log2_sectors_per_biपंचांगap_bit++;

	log2_blocks_per_biपंचांगap_bit = log2_sectors_per_biपंचांगap_bit - ic->sb->log2_sectors_per_block;
	ic->log2_blocks_per_biपंचांगap_bit = log2_blocks_per_biपंचांगap_bit;
	अगर (should_ग_लिखो_sb) अणु
		ic->sb->log2_blocks_per_biपंचांगap_bit = log2_blocks_per_biपंचांगap_bit;
	पूर्ण
	n_biपंचांगap_bits = ((ic->provided_data_sectors >> ic->sb->log2_sectors_per_block)
				+ (((sector_t)1 << log2_blocks_per_biपंचांगap_bit) - 1)) >> log2_blocks_per_biपंचांगap_bit;
	ic->n_biपंचांगap_blocks = DIV_ROUND_UP(n_biपंचांगap_bits, BITMAP_BLOCK_SIZE * 8);

	अगर (!ic->meta_dev)
		ic->log2_buffer_sectors = min(ic->log2_buffer_sectors, (__u8)__ffs(ic->metadata_run));

	अगर (ti->len > ic->provided_data_sectors) अणु
		r = -EINVAL;
		ti->error = "Not enough provided sectors for requested mapping size";
		जाओ bad;
	पूर्ण


	threshold = (__u64)ic->journal_entries * (100 - journal_watermark);
	threshold += 50;
	करो_भाग(threshold, 100);
	ic->मुक्त_sectors_threshold = threshold;

	DEBUG_prपूर्णांक("initialized:\n");
	DEBUG_prपूर्णांक("	integrity_tag_size %u\n", le16_to_cpu(ic->sb->पूर्णांकegrity_tag_size));
	DEBUG_prपूर्णांक("	journal_entry_size %u\n", ic->journal_entry_size);
	DEBUG_prपूर्णांक("	journal_entries_per_sector %u\n", ic->journal_entries_per_sector);
	DEBUG_prपूर्णांक("	journal_section_entries %u\n", ic->journal_section_entries);
	DEBUG_prपूर्णांक("	journal_section_sectors %u\n", ic->journal_section_sectors);
	DEBUG_prपूर्णांक("	journal_sections %u\n", (अचिन्हित)le32_to_cpu(ic->sb->journal_sections));
	DEBUG_prपूर्णांक("	journal_entries %u\n", ic->journal_entries);
	DEBUG_prपूर्णांक("	log2_interleave_sectors %d\n", ic->sb->log2_पूर्णांकerleave_sectors);
	DEBUG_prपूर्णांक("	data_device_sectors 0x%llx\n", i_size_पढ़ो(ic->dev->bdev->bd_inode) >> SECTOR_SHIFT);
	DEBUG_prपूर्णांक("	initial_sectors 0x%x\n", ic->initial_sectors);
	DEBUG_prपूर्णांक("	metadata_run 0x%x\n", ic->metadata_run);
	DEBUG_prपूर्णांक("	log2_metadata_run %d\n", ic->log2_metadata_run);
	DEBUG_prपूर्णांक("	provided_data_sectors 0x%llx (%llu)\n", ic->provided_data_sectors, ic->provided_data_sectors);
	DEBUG_prपूर्णांक("	log2_buffer_sectors %u\n", ic->log2_buffer_sectors);
	DEBUG_prपूर्णांक("	bits_in_journal %llu\n", bits_in_journal);

	अगर (ic->recalculate_flag && !(ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING))) अणु
		ic->sb->flags |= cpu_to_le32(SB_FLAG_RECALCULATING);
		ic->sb->recalc_sector = cpu_to_le64(0);
	पूर्ण

	अगर (ic->पूर्णांकernal_hash) अणु
		ic->recalc_wq = alloc_workqueue("dm-integrity-recalc", WQ_MEM_RECLAIM, 1);
		अगर (!ic->recalc_wq ) अणु
			ti->error = "Cannot allocate workqueue";
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
		INIT_WORK(&ic->recalc_work, पूर्णांकegrity_recalc);
		ic->recalc_buffer = vदो_स्मृति(RECALC_SECTORS << SECTOR_SHIFT);
		अगर (!ic->recalc_buffer) अणु
			ti->error = "Cannot allocate buffer for recalculating";
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
		ic->recalc_tags = kvदो_स्मृति_array(RECALC_SECTORS >> ic->sb->log2_sectors_per_block,
						 ic->tag_size, GFP_KERNEL);
		अगर (!ic->recalc_tags) अणु
			ti->error = "Cannot allocate tags for recalculating";
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING)) अणु
			ti->error = "Recalculate can only be specified with internal_hash";
			r = -EINVAL;
			जाओ bad;
		पूर्ण
	पूर्ण

	अगर (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING) &&
	    le64_to_cpu(ic->sb->recalc_sector) < ic->provided_data_sectors &&
	    dm_पूर्णांकegrity_disable_recalculate(ic)) अणु
		ti->error = "Recalculating with HMAC is disabled for security reasons - if you really need it, use the argument \"legacy_recalculate\"";
		r = -EOPNOTSUPP;
		जाओ bad;
	पूर्ण

	ic->bufio = dm_bufio_client_create(ic->meta_dev ? ic->meta_dev->bdev : ic->dev->bdev,
			1U << (SECTOR_SHIFT + ic->log2_buffer_sectors), 1, 0, शून्य, शून्य);
	अगर (IS_ERR(ic->bufio)) अणु
		r = PTR_ERR(ic->bufio);
		ti->error = "Cannot initialize dm-bufio";
		ic->bufio = शून्य;
		जाओ bad;
	पूर्ण
	dm_bufio_set_sector_offset(ic->bufio, ic->start + ic->initial_sectors);

	अगर (ic->mode != 'R') अणु
		r = create_journal(ic, &ti->error);
		अगर (r)
			जाओ bad;

	पूर्ण

	अगर (ic->mode == 'B') अणु
		अचिन्हित i;
		अचिन्हित n_biपंचांगap_pages = DIV_ROUND_UP(ic->n_biपंचांगap_blocks, PAGE_SIZE / BITMAP_BLOCK_SIZE);

		ic->recalc_biपंचांगap = dm_पूर्णांकegrity_alloc_page_list(n_biपंचांगap_pages);
		अगर (!ic->recalc_biपंचांगap) अणु
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
		ic->may_ग_लिखो_biपंचांगap = dm_पूर्णांकegrity_alloc_page_list(n_biपंचांगap_pages);
		अगर (!ic->may_ग_लिखो_biपंचांगap) अणु
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
		ic->bbs = kvदो_स्मृति_array(ic->n_biपंचांगap_blocks, माप(काष्ठा biपंचांगap_block_status), GFP_KERNEL);
		अगर (!ic->bbs) अणु
			r = -ENOMEM;
			जाओ bad;
		पूर्ण
		INIT_DELAYED_WORK(&ic->biपंचांगap_flush_work, biपंचांगap_flush_work);
		क्रम (i = 0; i < ic->n_biपंचांगap_blocks; i++) अणु
			काष्ठा biपंचांगap_block_status *bbs = &ic->bbs[i];
			अचिन्हित sector, pl_index, pl_offset;

			INIT_WORK(&bbs->work, biपंचांगap_block_work);
			bbs->ic = ic;
			bbs->idx = i;
			bio_list_init(&bbs->bio_queue);
			spin_lock_init(&bbs->bio_queue_lock);

			sector = i * (BITMAP_BLOCK_SIZE >> SECTOR_SHIFT);
			pl_index = sector >> (PAGE_SHIFT - SECTOR_SHIFT);
			pl_offset = (sector << SECTOR_SHIFT) & (PAGE_SIZE - 1);

			bbs->biपंचांगap = lowmem_page_address(ic->journal[pl_index].page) + pl_offset;
		पूर्ण
	पूर्ण

	अगर (should_ग_लिखो_sb) अणु
		पूर्णांक r;

		init_journal(ic, 0, ic->journal_sections, 0);
		r = dm_पूर्णांकegrity_failed(ic);
		अगर (unlikely(r)) अणु
			ti->error = "Error initializing journal";
			जाओ bad;
		पूर्ण
		r = sync_rw_sb(ic, REQ_OP_WRITE, REQ_FUA);
		अगर (r) अणु
			ti->error = "Error initializing superblock";
			जाओ bad;
		पूर्ण
		ic->just_क्रमmatted = true;
	पूर्ण

	अगर (!ic->meta_dev) अणु
		r = dm_set_target_max_io_len(ti, 1U << ic->sb->log2_पूर्णांकerleave_sectors);
		अगर (r)
			जाओ bad;
	पूर्ण
	अगर (ic->mode == 'B') अणु
		अचिन्हित max_io_len = ((sector_t)ic->sectors_per_block << ic->log2_blocks_per_biपंचांगap_bit) * (BITMAP_BLOCK_SIZE * 8);
		अगर (!max_io_len)
			max_io_len = 1U << 31;
		DEBUG_prपूर्णांक("max_io_len: old %u, new %u\n", ti->max_io_len, max_io_len);
		अगर (!ti->max_io_len || ti->max_io_len > max_io_len) अणु
			r = dm_set_target_max_io_len(ti, max_io_len);
			अगर (r)
				जाओ bad;
		पूर्ण
	पूर्ण

	अगर (!ic->पूर्णांकernal_hash)
		dm_पूर्णांकegrity_set(ti, ic);

	ti->num_flush_bios = 1;
	ti->flush_supported = true;
	अगर (ic->discard)
		ti->num_discard_bios = 1;

	वापस 0;

bad:
	dm_पूर्णांकegrity_dtr(ti);
	वापस r;
पूर्ण

अटल व्योम dm_पूर्णांकegrity_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_पूर्णांकegrity_c *ic = ti->निजी;

	BUG_ON(!RB_EMPTY_ROOT(&ic->in_progress));
	BUG_ON(!list_empty(&ic->रुको_list));

	अगर (ic->metadata_wq)
		destroy_workqueue(ic->metadata_wq);
	अगर (ic->रुको_wq)
		destroy_workqueue(ic->रुको_wq);
	अगर (ic->offload_wq)
		destroy_workqueue(ic->offload_wq);
	अगर (ic->commit_wq)
		destroy_workqueue(ic->commit_wq);
	अगर (ic->ग_लिखोr_wq)
		destroy_workqueue(ic->ग_लिखोr_wq);
	अगर (ic->recalc_wq)
		destroy_workqueue(ic->recalc_wq);
	vमुक्त(ic->recalc_buffer);
	kvमुक्त(ic->recalc_tags);
	kvमुक्त(ic->bbs);
	अगर (ic->bufio)
		dm_bufio_client_destroy(ic->bufio);
	mempool_निकास(&ic->journal_io_mempool);
	अगर (ic->io)
		dm_io_client_destroy(ic->io);
	अगर (ic->dev)
		dm_put_device(ti, ic->dev);
	अगर (ic->meta_dev)
		dm_put_device(ti, ic->meta_dev);
	dm_पूर्णांकegrity_मुक्त_page_list(ic->journal);
	dm_पूर्णांकegrity_मुक्त_page_list(ic->journal_io);
	dm_पूर्णांकegrity_मुक्त_page_list(ic->journal_xor);
	dm_पूर्णांकegrity_मुक्त_page_list(ic->recalc_biपंचांगap);
	dm_पूर्णांकegrity_मुक्त_page_list(ic->may_ग_लिखो_biपंचांगap);
	अगर (ic->journal_scatterlist)
		dm_पूर्णांकegrity_मुक्त_journal_scatterlist(ic, ic->journal_scatterlist);
	अगर (ic->journal_io_scatterlist)
		dm_पूर्णांकegrity_मुक्त_journal_scatterlist(ic, ic->journal_io_scatterlist);
	अगर (ic->sk_requests) अणु
		अचिन्हित i;

		क्रम (i = 0; i < ic->journal_sections; i++) अणु
			काष्ठा skcipher_request *req = ic->sk_requests[i];
			अगर (req) अणु
				kमुक्त_sensitive(req->iv);
				skcipher_request_मुक्त(req);
			पूर्ण
		पूर्ण
		kvमुक्त(ic->sk_requests);
	पूर्ण
	kvमुक्त(ic->journal_tree);
	अगर (ic->sb)
		मुक्त_pages_exact(ic->sb, SB_SECTORS << SECTOR_SHIFT);

	अगर (ic->पूर्णांकernal_hash)
		crypto_मुक्त_shash(ic->पूर्णांकernal_hash);
	मुक्त_alg(&ic->पूर्णांकernal_hash_alg);

	अगर (ic->journal_crypt)
		crypto_मुक्त_skcipher(ic->journal_crypt);
	मुक्त_alg(&ic->journal_crypt_alg);

	अगर (ic->journal_mac)
		crypto_मुक्त_shash(ic->journal_mac);
	मुक्त_alg(&ic->journal_mac_alg);

	kमुक्त(ic);
पूर्ण

अटल काष्ठा target_type पूर्णांकegrity_target = अणु
	.name			= "integrity",
	.version		= अणु1, 10, 0पूर्ण,
	.module			= THIS_MODULE,
	.features		= DM_TARGET_SINGLETON | DM_TARGET_INTEGRITY,
	.ctr			= dm_पूर्णांकegrity_ctr,
	.dtr			= dm_पूर्णांकegrity_dtr,
	.map			= dm_पूर्णांकegrity_map,
	.postsuspend		= dm_पूर्णांकegrity_postsuspend,
	.resume			= dm_पूर्णांकegrity_resume,
	.status			= dm_पूर्णांकegrity_status,
	.iterate_devices	= dm_पूर्णांकegrity_iterate_devices,
	.io_hपूर्णांकs		= dm_पूर्णांकegrity_io_hपूर्णांकs,
पूर्ण;

अटल पूर्णांक __init dm_पूर्णांकegrity_init(व्योम)
अणु
	पूर्णांक r;

	journal_io_cache = kmem_cache_create("integrity_journal_io",
					     माप(काष्ठा journal_io), 0, 0, शून्य);
	अगर (!journal_io_cache) अणु
		DMERR("can't allocate journal io cache");
		वापस -ENOMEM;
	पूर्ण

	r = dm_रेजिस्टर_target(&पूर्णांकegrity_target);

	अगर (r < 0)
		DMERR("register failed %d", r);

	वापस r;
पूर्ण

अटल व्योम __निकास dm_पूर्णांकegrity_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&पूर्णांकegrity_target);
	kmem_cache_destroy(journal_io_cache);
पूर्ण

module_init(dm_पूर्णांकegrity_init);
module_निकास(dm_पूर्णांकegrity_निकास);

MODULE_AUTHOR("Milan Broz");
MODULE_AUTHOR("Mikulas Patocka");
MODULE_DESCRIPTION(DM_NAME " target for integrity tags extension");
MODULE_LICENSE("GPL");
