<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *   Driver क्रम ARTPEC-6 crypto block using the kernel asynchronous crypto api.
 *
 *    Copyright (C) 2014-2017  Axis Communications AB
 */
#घोषणा pr_fmt(fmt)     KBUILD_MODNAME ": " fmt

#समावेश <linux/bitfield.h>
#समावेश <linux/crypto.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/xts.h>

/* Max length of a line in all cache levels क्रम Artpec SoCs. */
#घोषणा ARTPEC_CACHE_LINE_MAX	32

#घोषणा PDMA_OUT_CFG		0x0000
#घोषणा PDMA_OUT_BUF_CFG	0x0004
#घोषणा PDMA_OUT_CMD		0x0008
#घोषणा PDMA_OUT_DESCRQ_PUSH	0x0010
#घोषणा PDMA_OUT_DESCRQ_STAT	0x0014

#घोषणा A6_PDMA_IN_CFG		0x0028
#घोषणा A6_PDMA_IN_BUF_CFG	0x002c
#घोषणा A6_PDMA_IN_CMD		0x0030
#घोषणा A6_PDMA_IN_STATQ_PUSH	0x0038
#घोषणा A6_PDMA_IN_DESCRQ_PUSH	0x0044
#घोषणा A6_PDMA_IN_DESCRQ_STAT	0x0048
#घोषणा A6_PDMA_INTR_MASK	0x0068
#घोषणा A6_PDMA_ACK_INTR	0x006c
#घोषणा A6_PDMA_MASKED_INTR	0x0074

#घोषणा A7_PDMA_IN_CFG		0x002c
#घोषणा A7_PDMA_IN_BUF_CFG	0x0030
#घोषणा A7_PDMA_IN_CMD		0x0034
#घोषणा A7_PDMA_IN_STATQ_PUSH	0x003c
#घोषणा A7_PDMA_IN_DESCRQ_PUSH	0x0048
#घोषणा A7_PDMA_IN_DESCRQ_STAT	0x004C
#घोषणा A7_PDMA_INTR_MASK	0x006c
#घोषणा A7_PDMA_ACK_INTR	0x0070
#घोषणा A7_PDMA_MASKED_INTR	0x0078

#घोषणा PDMA_OUT_CFG_EN				BIT(0)

#घोषणा PDMA_OUT_BUF_CFG_DATA_BUF_SIZE		GENMASK(4, 0)
#घोषणा PDMA_OUT_BUF_CFG_DESCR_BUF_SIZE		GENMASK(9, 5)

#घोषणा PDMA_OUT_CMD_START			BIT(0)
#घोषणा A6_PDMA_OUT_CMD_STOP			BIT(3)
#घोषणा A7_PDMA_OUT_CMD_STOP			BIT(2)

#घोषणा PDMA_OUT_DESCRQ_PUSH_LEN		GENMASK(5, 0)
#घोषणा PDMA_OUT_DESCRQ_PUSH_ADDR		GENMASK(31, 6)

#घोषणा PDMA_OUT_DESCRQ_STAT_LEVEL		GENMASK(3, 0)
#घोषणा PDMA_OUT_DESCRQ_STAT_SIZE		GENMASK(7, 4)

#घोषणा PDMA_IN_CFG_EN				BIT(0)

#घोषणा PDMA_IN_BUF_CFG_DATA_BUF_SIZE		GENMASK(4, 0)
#घोषणा PDMA_IN_BUF_CFG_DESCR_BUF_SIZE		GENMASK(9, 5)
#घोषणा PDMA_IN_BUF_CFG_STAT_BUF_SIZE		GENMASK(14, 10)

#घोषणा PDMA_IN_CMD_START			BIT(0)
#घोषणा A6_PDMA_IN_CMD_FLUSH_STAT		BIT(2)
#घोषणा A6_PDMA_IN_CMD_STOP			BIT(3)
#घोषणा A7_PDMA_IN_CMD_FLUSH_STAT		BIT(1)
#घोषणा A7_PDMA_IN_CMD_STOP			BIT(2)

#घोषणा PDMA_IN_STATQ_PUSH_LEN			GENMASK(5, 0)
#घोषणा PDMA_IN_STATQ_PUSH_ADDR			GENMASK(31, 6)

#घोषणा PDMA_IN_DESCRQ_PUSH_LEN			GENMASK(5, 0)
#घोषणा PDMA_IN_DESCRQ_PUSH_ADDR		GENMASK(31, 6)

#घोषणा PDMA_IN_DESCRQ_STAT_LEVEL		GENMASK(3, 0)
#घोषणा PDMA_IN_DESCRQ_STAT_SIZE		GENMASK(7, 4)

#घोषणा A6_PDMA_INTR_MASK_IN_DATA		BIT(2)
#घोषणा A6_PDMA_INTR_MASK_IN_EOP		BIT(3)
#घोषणा A6_PDMA_INTR_MASK_IN_EOP_FLUSH		BIT(4)

#घोषणा A7_PDMA_INTR_MASK_IN_DATA		BIT(3)
#घोषणा A7_PDMA_INTR_MASK_IN_EOP		BIT(4)
#घोषणा A7_PDMA_INTR_MASK_IN_EOP_FLUSH		BIT(5)

#घोषणा A6_CRY_MD_OPER		GENMASK(19, 16)

#घोषणा A6_CRY_MD_HASH_SEL_CTX	GENMASK(21, 20)
#घोषणा A6_CRY_MD_HASH_HMAC_FIN	BIT(23)

#घोषणा A6_CRY_MD_CIPHER_LEN	GENMASK(21, 20)
#घोषणा A6_CRY_MD_CIPHER_DECR	BIT(22)
#घोषणा A6_CRY_MD_CIPHER_TWEAK	BIT(23)
#घोषणा A6_CRY_MD_CIPHER_DSEQ	BIT(24)

#घोषणा A7_CRY_MD_OPER		GENMASK(11, 8)

#घोषणा A7_CRY_MD_HASH_SEL_CTX	GENMASK(13, 12)
#घोषणा A7_CRY_MD_HASH_HMAC_FIN	BIT(15)

#घोषणा A7_CRY_MD_CIPHER_LEN	GENMASK(13, 12)
#घोषणा A7_CRY_MD_CIPHER_DECR	BIT(14)
#घोषणा A7_CRY_MD_CIPHER_TWEAK	BIT(15)
#घोषणा A7_CRY_MD_CIPHER_DSEQ	BIT(16)

/* DMA metadata स्थिरants */
#घोषणा regk_crypto_aes_cbc     0x00000002
#घोषणा regk_crypto_aes_ctr     0x00000003
#घोषणा regk_crypto_aes_ecb     0x00000001
#घोषणा regk_crypto_aes_gcm     0x00000004
#घोषणा regk_crypto_aes_xts     0x00000005
#घोषणा regk_crypto_cache       0x00000002
#घोषणा a6_regk_crypto_dlkey    0x0000000a
#घोषणा a7_regk_crypto_dlkey    0x0000000e
#घोषणा regk_crypto_ext         0x00000001
#घोषणा regk_crypto_hmac_sha1   0x00000007
#घोषणा regk_crypto_hmac_sha256 0x00000009
#घोषणा regk_crypto_init        0x00000000
#घोषणा regk_crypto_key_128     0x00000000
#घोषणा regk_crypto_key_192     0x00000001
#घोषणा regk_crypto_key_256     0x00000002
#घोषणा regk_crypto_null        0x00000000
#घोषणा regk_crypto_sha1        0x00000006
#घोषणा regk_crypto_sha256      0x00000008

/* DMA descriptor काष्ठाures */
काष्ठा pdma_descr_ctrl  अणु
	अचिन्हित अक्षर लघु_descr : 1;
	अचिन्हित अक्षर pad1        : 1;
	अचिन्हित अक्षर eop         : 1;
	अचिन्हित अक्षर पूर्णांकr        : 1;
	अचिन्हित अक्षर लघु_len   : 3;
	अचिन्हित अक्षर pad2        : 1;
पूर्ण __packed;

काष्ठा pdma_data_descr अणु
	अचिन्हित पूर्णांक len : 24;
	अचिन्हित पूर्णांक buf : 32;
पूर्ण __packed;

काष्ठा pdma_लघु_descr अणु
	अचिन्हित अक्षर data[7];
पूर्ण __packed;

काष्ठा pdma_descr अणु
	काष्ठा pdma_descr_ctrl ctrl;
	जोड़ अणु
		काष्ठा pdma_data_descr   data;
		काष्ठा pdma_लघु_descr  shrt;
	पूर्ण;
पूर्ण;

काष्ठा pdma_stat_descr अणु
	अचिन्हित अक्षर pad1        : 1;
	अचिन्हित अक्षर pad2        : 1;
	अचिन्हित अक्षर eop         : 1;
	अचिन्हित अक्षर pad3        : 5;
	अचिन्हित पूर्णांक  len         : 24;
पूर्ण;

/* Each descriptor array can hold max 64 entries */
#घोषणा PDMA_DESCR_COUNT	64

#घोषणा MODULE_NAME   "Artpec-6 CA"

/* Hash modes (including HMAC variants) */
#घोषणा ARTPEC6_CRYPTO_HASH_SHA1	1
#घोषणा ARTPEC6_CRYPTO_HASH_SHA256	2

/* Crypto modes */
#घोषणा ARTPEC6_CRYPTO_CIPHER_AES_ECB	1
#घोषणा ARTPEC6_CRYPTO_CIPHER_AES_CBC	2
#घोषणा ARTPEC6_CRYPTO_CIPHER_AES_CTR	3
#घोषणा ARTPEC6_CRYPTO_CIPHER_AES_XTS	5

/* The PDMA is a DMA-engine tightly coupled with a ciphering engine.
 * It operates on a descriptor array with up to 64 descriptor entries.
 * The arrays must be 64 byte aligned in memory.
 *
 * The ciphering unit has no रेजिस्टरs and is completely controlled by
 * a 4-byte metadata that is inserted at the beginning of each dma packet.
 *
 * A dma packet is a sequence of descriptors terminated by setting the .eop
 * field in the final descriptor of the packet.
 *
 * Multiple packets are used क्रम providing context data, key data and
 * the plain/ciphertext.
 *
 *   PDMA Descriptors (Array)
 *  +------+------+------+~~+-------+------+----
 *  |  0   |  1   |  2   |~~| 11 EOP|  12  |  ....
 *  +--+---+--+---+----+-+~~+-------+----+-+----
 *     |      |        |       |         |
 *     |      |        |       |         |
 *   __|__  +-------++-------++-------+ +----+
 *  | MD  | |Payload||Payload||Payload| | MD |
 *  +-----+ +-------++-------++-------+ +----+
 */

काष्ठा artpec6_crypto_bounce_buffer अणु
	काष्ठा list_head list;
	माप_प्रकार length;
	काष्ठा scatterlist *sg;
	माप_प्रकार offset;
	/* buf is aligned to ARTPEC_CACHE_LINE_MAX and
	 * holds up to ARTPEC_CACHE_LINE_MAX bytes data.
	 */
	व्योम *buf;
पूर्ण;

काष्ठा artpec6_crypto_dma_map अणु
	dma_addr_t dma_addr;
	माप_प्रकार size;
	क्रमागत dma_data_direction dir;
पूर्ण;

काष्ठा artpec6_crypto_dma_descriptors अणु
	काष्ठा pdma_descr out[PDMA_DESCR_COUNT] __aligned(64);
	काष्ठा pdma_descr in[PDMA_DESCR_COUNT] __aligned(64);
	u32 stat[PDMA_DESCR_COUNT] __aligned(64);
	काष्ठा list_head bounce_buffers;
	/* Enough maps क्रम all out/in buffers, and all three descr. arrays */
	काष्ठा artpec6_crypto_dma_map maps[PDMA_DESCR_COUNT * 2 + 2];
	dma_addr_t out_dma_addr;
	dma_addr_t in_dma_addr;
	dma_addr_t stat_dma_addr;
	माप_प्रकार out_cnt;
	माप_प्रकार in_cnt;
	माप_प्रकार map_count;
पूर्ण;

क्रमागत artpec6_crypto_variant अणु
	ARTPEC6_CRYPTO,
	ARTPEC7_CRYPTO,
पूर्ण;

काष्ठा artpec6_crypto अणु
	व्योम __iomem *base;
	spinlock_t queue_lock;
	काष्ठा list_head queue; /* रुकोing क्रम pdma fअगरo space */
	काष्ठा list_head pending; /* submitted to pdma fअगरo */
	काष्ठा tasklet_काष्ठा task;
	काष्ठा kmem_cache *dma_cache;
	पूर्णांक pending_count;
	काष्ठा समयr_list समयr;
	क्रमागत artpec6_crypto_variant variant;
	व्योम *pad_buffer; /* cache-aligned block padding buffer */
	व्योम *zero_buffer;
पूर्ण;

क्रमागत artpec6_crypto_hash_flags अणु
	HASH_FLAG_INIT_CTX = 2,
	HASH_FLAG_UPDATE = 4,
	HASH_FLAG_FINALIZE = 8,
	HASH_FLAG_HMAC = 16,
	HASH_FLAG_UPDATE_KEY = 32,
पूर्ण;

काष्ठा artpec6_crypto_req_common अणु
	काष्ठा list_head list;
	काष्ठा list_head complete_in_progress;
	काष्ठा artpec6_crypto_dma_descriptors *dma;
	काष्ठा crypto_async_request *req;
	व्योम (*complete)(काष्ठा crypto_async_request *req);
	gfp_t gfp_flags;
पूर्ण;

काष्ठा artpec6_hash_request_context अणु
	अक्षर partial_buffer[SHA256_BLOCK_SIZE];
	अक्षर partial_buffer_out[SHA256_BLOCK_SIZE];
	अक्षर key_buffer[SHA256_BLOCK_SIZE];
	अक्षर pad_buffer[SHA256_BLOCK_SIZE + 32];
	अचिन्हित अक्षर digeststate[SHA256_DIGEST_SIZE];
	माप_प्रकार partial_bytes;
	u64 digcnt;
	u32 key_md;
	u32 hash_md;
	क्रमागत artpec6_crypto_hash_flags hash_flags;
	काष्ठा artpec6_crypto_req_common common;
पूर्ण;

काष्ठा artpec6_hash_export_state अणु
	अक्षर partial_buffer[SHA256_BLOCK_SIZE];
	अचिन्हित अक्षर digeststate[SHA256_DIGEST_SIZE];
	माप_प्रकार partial_bytes;
	u64 digcnt;
	पूर्णांक oper;
	अचिन्हित पूर्णांक hash_flags;
पूर्ण;

काष्ठा artpec6_hashalg_context अणु
	अक्षर hmac_key[SHA256_BLOCK_SIZE];
	माप_प्रकार hmac_key_length;
	काष्ठा crypto_shash *child_hash;
पूर्ण;

काष्ठा artpec6_crypto_request_context अणु
	u32 cipher_md;
	bool decrypt;
	काष्ठा artpec6_crypto_req_common common;
पूर्ण;

काष्ठा artpec6_cryptotfm_context अणु
	अचिन्हित अक्षर aes_key[2*AES_MAX_KEY_SIZE];
	माप_प्रकार key_length;
	u32 key_md;
	पूर्णांक crypto_type;
	काष्ठा crypto_sync_skcipher *fallback;
पूर्ण;

काष्ठा artpec6_crypto_aead_hw_ctx अणु
	__be64	aad_length_bits;
	__be64  text_length_bits;
	__u8	J0[AES_BLOCK_SIZE];
पूर्ण;

काष्ठा artpec6_crypto_aead_req_ctx अणु
	काष्ठा artpec6_crypto_aead_hw_ctx hw_ctx;
	u32 cipher_md;
	bool decrypt;
	काष्ठा artpec6_crypto_req_common common;
	__u8 decryption_tag[AES_BLOCK_SIZE] ____cacheline_aligned;
पूर्ण;

/* The crypto framework makes it hard to aव्योम this global. */
अटल काष्ठा device *artpec6_crypto_dev;

#अगर_घोषित CONFIG_FAULT_INJECTION
अटल DECLARE_FAULT_ATTR(artpec6_crypto_fail_status_पढ़ो);
अटल DECLARE_FAULT_ATTR(artpec6_crypto_fail_dma_array_full);
#पूर्ण_अगर

क्रमागत अणु
	ARTPEC6_CRYPTO_PREPARE_HASH_NO_START,
	ARTPEC6_CRYPTO_PREPARE_HASH_START,
पूर्ण;

अटल पूर्णांक artpec6_crypto_prepare_aead(काष्ठा aead_request *areq);
अटल पूर्णांक artpec6_crypto_prepare_crypto(काष्ठा skcipher_request *areq);
अटल पूर्णांक artpec6_crypto_prepare_hash(काष्ठा ahash_request *areq);

अटल व्योम
artpec6_crypto_complete_crypto(काष्ठा crypto_async_request *req);
अटल व्योम
artpec6_crypto_complete_cbc_encrypt(काष्ठा crypto_async_request *req);
अटल व्योम
artpec6_crypto_complete_cbc_decrypt(काष्ठा crypto_async_request *req);
अटल व्योम
artpec6_crypto_complete_aead(काष्ठा crypto_async_request *req);
अटल व्योम
artpec6_crypto_complete_hash(काष्ठा crypto_async_request *req);

अटल पूर्णांक
artpec6_crypto_common_destroy(काष्ठा artpec6_crypto_req_common *common);

अटल व्योम
artpec6_crypto_start_dma(काष्ठा artpec6_crypto_req_common *common);

काष्ठा artpec6_crypto_walk अणु
	काष्ठा scatterlist *sg;
	माप_प्रकार offset;
पूर्ण;

अटल व्योम artpec6_crypto_walk_init(काष्ठा artpec6_crypto_walk *awalk,
				     काष्ठा scatterlist *sg)
अणु
	awalk->sg = sg;
	awalk->offset = 0;
पूर्ण

अटल माप_प्रकार artpec6_crypto_walk_advance(काष्ठा artpec6_crypto_walk *awalk,
					  माप_प्रकार nbytes)
अणु
	जबतक (nbytes && awalk->sg) अणु
		माप_प्रकार piece;

		WARN_ON(awalk->offset > awalk->sg->length);

		piece = min(nbytes, (माप_प्रकार)awalk->sg->length - awalk->offset);
		nbytes -= piece;
		awalk->offset += piece;
		अगर (awalk->offset == awalk->sg->length) अणु
			awalk->sg = sg_next(awalk->sg);
			awalk->offset = 0;
		पूर्ण

	पूर्ण

	वापस nbytes;
पूर्ण

अटल माप_प्रकार
artpec6_crypto_walk_chunklen(स्थिर काष्ठा artpec6_crypto_walk *awalk)
अणु
	WARN_ON(awalk->sg->length == awalk->offset);

	वापस awalk->sg->length - awalk->offset;
पूर्ण

अटल dma_addr_t
artpec6_crypto_walk_chunk_phys(स्थिर काष्ठा artpec6_crypto_walk *awalk)
अणु
	वापस sg_phys(awalk->sg) + awalk->offset;
पूर्ण

अटल व्योम
artpec6_crypto_copy_bounce_buffers(काष्ठा artpec6_crypto_req_common *common)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	काष्ठा artpec6_crypto_bounce_buffer *b;
	काष्ठा artpec6_crypto_bounce_buffer *next;

	list_क्रम_each_entry_safe(b, next, &dma->bounce_buffers, list) अणु
		pr_debug("bounce entry %p: %zu bytes @ %zu from %p\n",
			 b, b->length, b->offset, b->buf);
		sg_pcopy_from_buffer(b->sg,
				   1,
				   b->buf,
				   b->length,
				   b->offset);

		list_del(&b->list);
		kमुक्त(b);
	पूर्ण
पूर्ण

अटल अंतरभूत bool artpec6_crypto_busy(व्योम)
अणु
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	पूर्णांक fअगरo_count = ac->pending_count;

	वापस fअगरo_count > 6;
पूर्ण

अटल पूर्णांक artpec6_crypto_submit(काष्ठा artpec6_crypto_req_common *req)
अणु
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	पूर्णांक ret = -EBUSY;

	spin_lock_bh(&ac->queue_lock);

	अगर (!artpec6_crypto_busy()) अणु
		list_add_tail(&req->list, &ac->pending);
		artpec6_crypto_start_dma(req);
		ret = -EINPROGRESS;
	पूर्ण अन्यथा अगर (req->req->flags & CRYPTO_TFM_REQ_MAY_BACKLOG) अणु
		list_add_tail(&req->list, &ac->queue);
	पूर्ण अन्यथा अणु
		artpec6_crypto_common_destroy(req);
	पूर्ण

	spin_unlock_bh(&ac->queue_lock);

	वापस ret;
पूर्ण

अटल व्योम artpec6_crypto_start_dma(काष्ठा artpec6_crypto_req_common *common)
अणु
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	क्रमागत artpec6_crypto_variant variant = ac->variant;
	व्योम __iomem *base = ac->base;
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	u32 ind, statd, outd;

	/* Make descriptor content visible to the DMA beक्रमe starting it. */
	wmb();

	ind = FIELD_PREP(PDMA_IN_DESCRQ_PUSH_LEN, dma->in_cnt - 1) |
	      FIELD_PREP(PDMA_IN_DESCRQ_PUSH_ADDR, dma->in_dma_addr >> 6);

	statd = FIELD_PREP(PDMA_IN_STATQ_PUSH_LEN, dma->in_cnt - 1) |
		FIELD_PREP(PDMA_IN_STATQ_PUSH_ADDR, dma->stat_dma_addr >> 6);

	outd = FIELD_PREP(PDMA_OUT_DESCRQ_PUSH_LEN, dma->out_cnt - 1) |
	       FIELD_PREP(PDMA_OUT_DESCRQ_PUSH_ADDR, dma->out_dma_addr >> 6);

	अगर (variant == ARTPEC6_CRYPTO) अणु
		ग_लिखोl_relaxed(ind, base + A6_PDMA_IN_DESCRQ_PUSH);
		ग_लिखोl_relaxed(statd, base + A6_PDMA_IN_STATQ_PUSH);
		ग_लिखोl_relaxed(PDMA_IN_CMD_START, base + A6_PDMA_IN_CMD);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(ind, base + A7_PDMA_IN_DESCRQ_PUSH);
		ग_लिखोl_relaxed(statd, base + A7_PDMA_IN_STATQ_PUSH);
		ग_लिखोl_relaxed(PDMA_IN_CMD_START, base + A7_PDMA_IN_CMD);
	पूर्ण

	ग_लिखोl_relaxed(outd, base + PDMA_OUT_DESCRQ_PUSH);
	ग_लिखोl_relaxed(PDMA_OUT_CMD_START, base + PDMA_OUT_CMD);

	ac->pending_count++;
पूर्ण

अटल व्योम
artpec6_crypto_init_dma_operation(काष्ठा artpec6_crypto_req_common *common)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;

	dma->out_cnt = 0;
	dma->in_cnt = 0;
	dma->map_count = 0;
	INIT_LIST_HEAD(&dma->bounce_buffers);
पूर्ण

अटल bool fault_inject_dma_descr(व्योम)
अणु
#अगर_घोषित CONFIG_FAULT_INJECTION
	वापस should_fail(&artpec6_crypto_fail_dma_array_full, 1);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/** artpec6_crypto_setup_out_descr_phys - Setup an out channel with a
 *                                        physical address
 *
 * @addr: The physical address of the data buffer
 * @len:  The length of the data buffer
 * @eop:  True अगर this is the last buffer in the packet
 *
 * @वापस 0 on success or -ENOSPC अगर there are no more descriptors available
 */
अटल पूर्णांक
artpec6_crypto_setup_out_descr_phys(काष्ठा artpec6_crypto_req_common *common,
				    dma_addr_t addr, माप_प्रकार len, bool eop)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	काष्ठा pdma_descr *d;

	अगर (dma->out_cnt >= PDMA_DESCR_COUNT ||
	    fault_inject_dma_descr()) अणु
		pr_err("No free OUT DMA descriptors available!\n");
		वापस -ENOSPC;
	पूर्ण

	d = &dma->out[dma->out_cnt++];
	स_रखो(d, 0, माप(*d));

	d->ctrl.लघु_descr = 0;
	d->ctrl.eop = eop;
	d->data.len = len;
	d->data.buf = addr;
	वापस 0;
पूर्ण

/** artpec6_crypto_setup_out_descr_लघु - Setup a लघु out descriptor
 *
 * @dst: The भव address of the data
 * @len: The length of the data, must be between 1 to 7 bytes
 * @eop: True अगर this is the last buffer in the packet
 *
 * @वापस 0 on success
 *	-ENOSPC अगर no more descriptors are available
 *	-EINVAL अगर the data length exceeds 7 bytes
 */
अटल पूर्णांक
artpec6_crypto_setup_out_descr_लघु(काष्ठा artpec6_crypto_req_common *common,
				     व्योम *dst, अचिन्हित पूर्णांक len, bool eop)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	काष्ठा pdma_descr *d;

	अगर (dma->out_cnt >= PDMA_DESCR_COUNT ||
	    fault_inject_dma_descr()) अणु
		pr_err("No free OUT DMA descriptors available!\n");
		वापस -ENOSPC;
	पूर्ण अन्यथा अगर (len > 7 || len < 1) अणु
		वापस -EINVAL;
	पूर्ण
	d = &dma->out[dma->out_cnt++];
	स_रखो(d, 0, माप(*d));

	d->ctrl.लघु_descr = 1;
	d->ctrl.लघु_len = len;
	d->ctrl.eop = eop;
	स_नकल(d->shrt.data, dst, len);
	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_dma_map_page(काष्ठा artpec6_crypto_req_common *common,
				      काष्ठा page *page, माप_प्रकार offset,
				      माप_प्रकार size,
				      क्रमागत dma_data_direction dir,
				      dma_addr_t *dma_addr_out)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	काष्ठा device *dev = artpec6_crypto_dev;
	काष्ठा artpec6_crypto_dma_map *map;
	dma_addr_t dma_addr;

	*dma_addr_out = 0;

	अगर (dma->map_count >= ARRAY_SIZE(dma->maps))
		वापस -ENOMEM;

	dma_addr = dma_map_page(dev, page, offset, size, dir);
	अगर (dma_mapping_error(dev, dma_addr))
		वापस -ENOMEM;

	map = &dma->maps[dma->map_count++];
	map->size = size;
	map->dma_addr = dma_addr;
	map->dir = dir;

	*dma_addr_out = dma_addr;

	वापस 0;
पूर्ण

अटल पूर्णांक
artpec6_crypto_dma_map_single(काष्ठा artpec6_crypto_req_common *common,
			      व्योम *ptr, माप_प्रकार size,
			      क्रमागत dma_data_direction dir,
			      dma_addr_t *dma_addr_out)
अणु
	काष्ठा page *page = virt_to_page(ptr);
	माप_प्रकार offset = (uपूर्णांकptr_t)ptr & ~PAGE_MASK;

	वापस artpec6_crypto_dma_map_page(common, page, offset, size, dir,
					  dma_addr_out);
पूर्ण

अटल पूर्णांक
artpec6_crypto_dma_map_descs(काष्ठा artpec6_crypto_req_common *common)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	पूर्णांक ret;

	ret = artpec6_crypto_dma_map_single(common, dma->in,
				माप(dma->in[0]) * dma->in_cnt,
				DMA_TO_DEVICE, &dma->in_dma_addr);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_dma_map_single(common, dma->out,
				माप(dma->out[0]) * dma->out_cnt,
				DMA_TO_DEVICE, &dma->out_dma_addr);
	अगर (ret)
		वापस ret;

	/* We only पढ़ो one stat descriptor */
	dma->stat[dma->in_cnt - 1] = 0;

	/*
	 * DMA_BIसूचीECTIONAL since we need our zeroing of the stat descriptor
	 * to be written.
	 */
	वापस artpec6_crypto_dma_map_single(common,
				dma->stat,
				माप(dma->stat[0]) * dma->in_cnt,
				DMA_BIसूचीECTIONAL,
				&dma->stat_dma_addr);
पूर्ण

अटल व्योम
artpec6_crypto_dma_unmap_all(काष्ठा artpec6_crypto_req_common *common)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	काष्ठा device *dev = artpec6_crypto_dev;
	पूर्णांक i;

	क्रम (i = 0; i < dma->map_count; i++) अणु
		काष्ठा artpec6_crypto_dma_map *map = &dma->maps[i];

		dma_unmap_page(dev, map->dma_addr, map->size, map->dir);
	पूर्ण

	dma->map_count = 0;
पूर्ण

/** artpec6_crypto_setup_out_descr - Setup an out descriptor
 *
 * @dst: The भव address of the data
 * @len: The length of the data
 * @eop: True अगर this is the last buffer in the packet
 * @use_लघु: If this is true and the data length is 7 bytes or less then
 *	a लघु descriptor will be used
 *
 * @वापस 0 on success
 *	Any errors from artpec6_crypto_setup_out_descr_लघु() or
 *	setup_out_descr_phys()
 */
अटल पूर्णांक
artpec6_crypto_setup_out_descr(काष्ठा artpec6_crypto_req_common *common,
			       व्योम *dst, अचिन्हित पूर्णांक len, bool eop,
			       bool use_लघु)
अणु
	अगर (use_लघु && len < 7) अणु
		वापस artpec6_crypto_setup_out_descr_लघु(common, dst, len,
							    eop);
	पूर्ण अन्यथा अणु
		पूर्णांक ret;
		dma_addr_t dma_addr;

		ret = artpec6_crypto_dma_map_single(common, dst, len,
						   DMA_TO_DEVICE,
						   &dma_addr);
		अगर (ret)
			वापस ret;

		वापस artpec6_crypto_setup_out_descr_phys(common, dma_addr,
							   len, eop);
	पूर्ण
पूर्ण

/** artpec6_crypto_setup_in_descr_phys - Setup an in channel with a
 *                                       physical address
 *
 * @addr: The physical address of the data buffer
 * @len:  The length of the data buffer
 * @पूर्णांकr: True अगर an पूर्णांकerrupt should be fired after HW processing of this
 *	  descriptor
 *
 */
अटल पूर्णांक
artpec6_crypto_setup_in_descr_phys(काष्ठा artpec6_crypto_req_common *common,
			       dma_addr_t addr, अचिन्हित पूर्णांक len, bool पूर्णांकr)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	काष्ठा pdma_descr *d;

	अगर (dma->in_cnt >= PDMA_DESCR_COUNT ||
	    fault_inject_dma_descr()) अणु
		pr_err("No free IN DMA descriptors available!\n");
		वापस -ENOSPC;
	पूर्ण
	d = &dma->in[dma->in_cnt++];
	स_रखो(d, 0, माप(*d));

	d->ctrl.पूर्णांकr = पूर्णांकr;
	d->data.len = len;
	d->data.buf = addr;
	वापस 0;
पूर्ण

/** artpec6_crypto_setup_in_descr - Setup an in channel descriptor
 *
 * @buffer: The भव address to of the data buffer
 * @len:    The length of the data buffer
 * @last:   If this is the last data buffer in the request (i.e. an पूर्णांकerrupt
 *	    is needed
 *
 * Short descriptors are not used क्रम the in channel
 */
अटल पूर्णांक
artpec6_crypto_setup_in_descr(काष्ठा artpec6_crypto_req_common *common,
			  व्योम *buffer, अचिन्हित पूर्णांक len, bool last)
अणु
	dma_addr_t dma_addr;
	पूर्णांक ret;

	ret = artpec6_crypto_dma_map_single(common, buffer, len,
					   DMA_FROM_DEVICE, &dma_addr);
	अगर (ret)
		वापस ret;

	वापस artpec6_crypto_setup_in_descr_phys(common, dma_addr, len, last);
पूर्ण

अटल काष्ठा artpec6_crypto_bounce_buffer *
artpec6_crypto_alloc_bounce(gfp_t flags)
अणु
	व्योम *base;
	माप_प्रकार alloc_size = माप(काष्ठा artpec6_crypto_bounce_buffer) +
			    2 * ARTPEC_CACHE_LINE_MAX;
	काष्ठा artpec6_crypto_bounce_buffer *bbuf = kzalloc(alloc_size, flags);

	अगर (!bbuf)
		वापस शून्य;

	base = bbuf + 1;
	bbuf->buf = PTR_ALIGN(base, ARTPEC_CACHE_LINE_MAX);
	वापस bbuf;
पूर्ण

अटल पूर्णांक setup_bounce_buffer_in(काष्ठा artpec6_crypto_req_common *common,
				  काष्ठा artpec6_crypto_walk *walk, माप_प्रकार size)
अणु
	काष्ठा artpec6_crypto_bounce_buffer *bbuf;
	पूर्णांक ret;

	bbuf = artpec6_crypto_alloc_bounce(common->gfp_flags);
	अगर (!bbuf)
		वापस -ENOMEM;

	bbuf->length = size;
	bbuf->sg = walk->sg;
	bbuf->offset = walk->offset;

	ret =  artpec6_crypto_setup_in_descr(common, bbuf->buf, size, false);
	अगर (ret) अणु
		kमुक्त(bbuf);
		वापस ret;
	पूर्ण

	pr_debug("BOUNCE %zu offset %zu\n", size, walk->offset);
	list_add_tail(&bbuf->list, &common->dma->bounce_buffers);
	वापस 0;
पूर्ण

अटल पूर्णांक
artpec6_crypto_setup_sg_descrs_in(काष्ठा artpec6_crypto_req_common *common,
				  काष्ठा artpec6_crypto_walk *walk,
				  माप_प्रकार count)
अणु
	माप_प्रकार chunk;
	पूर्णांक ret;
	dma_addr_t addr;

	जबतक (walk->sg && count) अणु
		chunk = min(count, artpec6_crypto_walk_chunklen(walk));
		addr = artpec6_crypto_walk_chunk_phys(walk);

		/* When destination buffers are not aligned to the cache line
		 * size we need bounce buffers. The DMA-API requires that the
		 * entire line is owned by the DMA buffer and this holds also
		 * क्रम the हाल when coherent DMA is used.
		 */
		अगर (!IS_ALIGNED(addr, ARTPEC_CACHE_LINE_MAX)) अणु
			chunk = min_t(dma_addr_t, chunk,
				      ALIGN(addr, ARTPEC_CACHE_LINE_MAX) -
				      addr);

			pr_debug("CHUNK-b %pad:%zu\n", &addr, chunk);
			ret = setup_bounce_buffer_in(common, walk, chunk);
		पूर्ण अन्यथा अगर (chunk < ARTPEC_CACHE_LINE_MAX) अणु
			pr_debug("CHUNK-b %pad:%zu\n", &addr, chunk);
			ret = setup_bounce_buffer_in(common, walk, chunk);
		पूर्ण अन्यथा अणु
			dma_addr_t dma_addr;

			chunk = chunk & ~(ARTPEC_CACHE_LINE_MAX-1);

			pr_debug("CHUNK %pad:%zu\n", &addr, chunk);

			ret = artpec6_crypto_dma_map_page(common,
							 sg_page(walk->sg),
							 walk->sg->offset +
							 walk->offset,
							 chunk,
							 DMA_FROM_DEVICE,
							 &dma_addr);
			अगर (ret)
				वापस ret;

			ret = artpec6_crypto_setup_in_descr_phys(common,
								 dma_addr,
								 chunk, false);
		पूर्ण

		अगर (ret)
			वापस ret;

		count = count - chunk;
		artpec6_crypto_walk_advance(walk, chunk);
	पूर्ण

	अगर (count)
		pr_err("EOL unexpected %zu bytes left\n", count);

	वापस count ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक
artpec6_crypto_setup_sg_descrs_out(काष्ठा artpec6_crypto_req_common *common,
				   काष्ठा artpec6_crypto_walk *walk,
				   माप_प्रकार count)
अणु
	माप_प्रकार chunk;
	पूर्णांक ret;
	dma_addr_t addr;

	जबतक (walk->sg && count) अणु
		chunk = min(count, artpec6_crypto_walk_chunklen(walk));
		addr = artpec6_crypto_walk_chunk_phys(walk);

		pr_debug("OUT-CHUNK %pad:%zu\n", &addr, chunk);

		अगर (addr & 3) अणु
			अक्षर buf[3];

			chunk = min_t(माप_प्रकार, chunk, (4-(addr&3)));

			sg_pcopy_to_buffer(walk->sg, 1, buf, chunk,
					   walk->offset);

			ret = artpec6_crypto_setup_out_descr_लघु(common, buf,
								   chunk,
								   false);
		पूर्ण अन्यथा अणु
			dma_addr_t dma_addr;

			ret = artpec6_crypto_dma_map_page(common,
							 sg_page(walk->sg),
							 walk->sg->offset +
							 walk->offset,
							 chunk,
							 DMA_TO_DEVICE,
							 &dma_addr);
			अगर (ret)
				वापस ret;

			ret = artpec6_crypto_setup_out_descr_phys(common,
								 dma_addr,
								 chunk, false);
		पूर्ण

		अगर (ret)
			वापस ret;

		count = count - chunk;
		artpec6_crypto_walk_advance(walk, chunk);
	पूर्ण

	अगर (count)
		pr_err("EOL unexpected %zu bytes left\n", count);

	वापस count ? -EINVAL : 0;
पूर्ण


/** artpec6_crypto_terminate_out_descrs - Set the EOP on the last out descriptor
 *
 * If the out descriptor list is non-empty, then the eop flag on the
 * last used out descriptor will be set.
 *
 * @वापस  0 on success
 *	-EINVAL अगर the out descriptor is empty or has overflown
 */
अटल पूर्णांक
artpec6_crypto_terminate_out_descrs(काष्ठा artpec6_crypto_req_common *common)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	काष्ठा pdma_descr *d;

	अगर (!dma->out_cnt || dma->out_cnt > PDMA_DESCR_COUNT) अणु
		pr_err("%s: OUT descriptor list is %s\n",
			MODULE_NAME, dma->out_cnt ? "empty" : "full");
		वापस -EINVAL;

	पूर्ण

	d = &dma->out[dma->out_cnt-1];
	d->ctrl.eop = 1;

	वापस 0;
पूर्ण

/** artpec6_crypto_terminate_in_descrs - Set the पूर्णांकerrupt flag on the last
 *                                       in descriptor
 *
 * See artpec6_crypto_terminate_out_descrs() क्रम वापस values
 */
अटल पूर्णांक
artpec6_crypto_terminate_in_descrs(काष्ठा artpec6_crypto_req_common *common)
अणु
	काष्ठा artpec6_crypto_dma_descriptors *dma = common->dma;
	काष्ठा pdma_descr *d;

	अगर (!dma->in_cnt || dma->in_cnt > PDMA_DESCR_COUNT) अणु
		pr_err("%s: IN descriptor list is %s\n",
			MODULE_NAME, dma->in_cnt ? "empty" : "full");
		वापस -EINVAL;
	पूर्ण

	d = &dma->in[dma->in_cnt-1];
	d->ctrl.पूर्णांकr = 1;
	वापस 0;
पूर्ण

/** create_hash_pad - Create a Secure Hash conक्रमmant pad
 *
 * @dst:      The destination buffer to ग_लिखो the pad. Must be at least 64 bytes
 * @dgstlen:  The total length of the hash digest in bytes
 * @bitcount: The total length of the digest in bits
 *
 * @वापस The total number of padding bytes written to @dst
 */
अटल माप_प्रकार
create_hash_pad(पूर्णांक oper, अचिन्हित अक्षर *dst, u64 dgstlen, u64 bitcount)
अणु
	अचिन्हित पूर्णांक mod, target, dअगरf, pad_bytes, size_bytes;
	__be64 bits = __cpu_to_be64(bitcount);

	चयन (oper) अणु
	हाल regk_crypto_sha1:
	हाल regk_crypto_sha256:
	हाल regk_crypto_hmac_sha1:
	हाल regk_crypto_hmac_sha256:
		target = 448 / 8;
		mod = 512 / 8;
		size_bytes = 8;
		अवरोध;
	शेष:
		target = 896 / 8;
		mod = 1024 / 8;
		size_bytes = 16;
		अवरोध;
	पूर्ण

	target -= 1;
	dअगरf = dgstlen & (mod - 1);
	pad_bytes = dअगरf > target ? target + mod - dअगरf : target - dअगरf;

	स_रखो(dst + 1, 0, pad_bytes);
	dst[0] = 0x80;

	अगर (size_bytes == 16) अणु
		स_रखो(dst + 1 + pad_bytes, 0, 8);
		स_नकल(dst + 1 + pad_bytes + 8, &bits, 8);
	पूर्ण अन्यथा अणु
		स_नकल(dst + 1 + pad_bytes, &bits, 8);
	पूर्ण

	वापस pad_bytes + size_bytes + 1;
पूर्ण

अटल पूर्णांक artpec6_crypto_common_init(काष्ठा artpec6_crypto_req_common *common,
		काष्ठा crypto_async_request *parent,
		व्योम (*complete)(काष्ठा crypto_async_request *req),
		काष्ठा scatterlist *dstsg, अचिन्हित पूर्णांक nbytes)
अणु
	gfp_t flags;
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);

	flags = (parent->flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		 GFP_KERNEL : GFP_ATOMIC;

	common->gfp_flags = flags;
	common->dma = kmem_cache_alloc(ac->dma_cache, flags);
	अगर (!common->dma)
		वापस -ENOMEM;

	common->req = parent;
	common->complete = complete;
	वापस 0;
पूर्ण

अटल व्योम
artpec6_crypto_bounce_destroy(काष्ठा artpec6_crypto_dma_descriptors *dma)
अणु
	काष्ठा artpec6_crypto_bounce_buffer *b;
	काष्ठा artpec6_crypto_bounce_buffer *next;

	list_क्रम_each_entry_safe(b, next, &dma->bounce_buffers, list) अणु
		kमुक्त(b);
	पूर्ण
पूर्ण

अटल पूर्णांक
artpec6_crypto_common_destroy(काष्ठा artpec6_crypto_req_common *common)
अणु
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);

	artpec6_crypto_dma_unmap_all(common);
	artpec6_crypto_bounce_destroy(common->dma);
	kmem_cache_मुक्त(ac->dma_cache, common->dma);
	common->dma = शून्य;
	वापस 0;
पूर्ण

/*
 * Ciphering functions.
 */
अटल पूर्णांक artpec6_crypto_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा artpec6_crypto_request_context *req_ctx = शून्य;
	व्योम (*complete)(काष्ठा crypto_async_request *req);
	पूर्णांक ret;

	req_ctx = skcipher_request_ctx(req);

	चयन (ctx->crypto_type) अणु
	हाल ARTPEC6_CRYPTO_CIPHER_AES_CBC:
	हाल ARTPEC6_CRYPTO_CIPHER_AES_ECB:
	हाल ARTPEC6_CRYPTO_CIPHER_AES_XTS:
		req_ctx->decrypt = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (ctx->crypto_type) अणु
	हाल ARTPEC6_CRYPTO_CIPHER_AES_CBC:
		complete = artpec6_crypto_complete_cbc_encrypt;
		अवरोध;
	शेष:
		complete = artpec6_crypto_complete_crypto;
		अवरोध;
	पूर्ण

	ret = artpec6_crypto_common_init(&req_ctx->common,
				  &req->base,
				  complete,
				  req->dst, req->cryptlen);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_prepare_crypto(req);
	अगर (ret) अणु
		artpec6_crypto_common_destroy(&req_ctx->common);
		वापस ret;
	पूर्ण

	वापस artpec6_crypto_submit(&req_ctx->common);
पूर्ण

अटल पूर्णांक artpec6_crypto_decrypt(काष्ठा skcipher_request *req)
अणु
	पूर्णांक ret;
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा artpec6_crypto_request_context *req_ctx = शून्य;
	व्योम (*complete)(काष्ठा crypto_async_request *req);

	req_ctx = skcipher_request_ctx(req);

	चयन (ctx->crypto_type) अणु
	हाल ARTPEC6_CRYPTO_CIPHER_AES_CBC:
	हाल ARTPEC6_CRYPTO_CIPHER_AES_ECB:
	हाल ARTPEC6_CRYPTO_CIPHER_AES_XTS:
		req_ctx->decrypt = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण


	चयन (ctx->crypto_type) अणु
	हाल ARTPEC6_CRYPTO_CIPHER_AES_CBC:
		complete = artpec6_crypto_complete_cbc_decrypt;
		अवरोध;
	शेष:
		complete = artpec6_crypto_complete_crypto;
		अवरोध;
	पूर्ण

	ret = artpec6_crypto_common_init(&req_ctx->common, &req->base,
				  complete,
				  req->dst, req->cryptlen);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_prepare_crypto(req);
	अगर (ret) अणु
		artpec6_crypto_common_destroy(&req_ctx->common);
		वापस ret;
	पूर्ण

	वापस artpec6_crypto_submit(&req_ctx->common);
पूर्ण

अटल पूर्णांक
artpec6_crypto_ctr_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(cipher);
	माप_प्रकार iv_len = crypto_skcipher_ivsize(cipher);
	अचिन्हित पूर्णांक counter = be32_to_cpup((__be32 *)
					    (req->iv + iv_len - 4));
	अचिन्हित पूर्णांक nblks = ALIGN(req->cryptlen, AES_BLOCK_SIZE) /
			     AES_BLOCK_SIZE;

	/*
	 * The hardware uses only the last 32-bits as the counter जबतक the
	 * kernel tests (aes_ctr_enc_tv_ढाँचा[4] क्रम example) expect that
	 * the whole IV is a counter.  So fallback अगर the counter is going to
	 * overlow.
	 */
	अगर (counter + nblks < counter) अणु
		पूर्णांक ret;

		pr_debug("counter %x will overflow (nblks %u), falling back\n",
			 counter, counter + nblks);

		ret = crypto_sync_skcipher_setkey(ctx->fallback, ctx->aes_key,
						  ctx->key_length);
		अगर (ret)
			वापस ret;

		अणु
			SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, ctx->fallback);

			skcipher_request_set_sync_tfm(subreq, ctx->fallback);
			skcipher_request_set_callback(subreq, req->base.flags,
						      शून्य, शून्य);
			skcipher_request_set_crypt(subreq, req->src, req->dst,
						   req->cryptlen, req->iv);
			ret = encrypt ? crypto_skcipher_encrypt(subreq)
				      : crypto_skcipher_decrypt(subreq);
			skcipher_request_zero(subreq);
		पूर्ण
		वापस ret;
	पूर्ण

	वापस encrypt ? artpec6_crypto_encrypt(req)
		       : artpec6_crypto_decrypt(req);
पूर्ण

अटल पूर्णांक artpec6_crypto_ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस artpec6_crypto_ctr_crypt(req, true);
पूर्ण

अटल पूर्णांक artpec6_crypto_ctr_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस artpec6_crypto_ctr_crypt(req, false);
पूर्ण

/*
 * AEAD functions
 */
अटल पूर्णांक artpec6_crypto_aead_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा artpec6_cryptotfm_context *tfm_ctx = crypto_aead_ctx(tfm);

	स_रखो(tfm_ctx, 0, माप(*tfm_ctx));

	crypto_aead_set_reqsize(tfm,
				माप(काष्ठा artpec6_crypto_aead_req_ctx));

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_aead_set_key(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			       अचिन्हित पूर्णांक len)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_tfm_ctx(&tfm->base);

	अगर (len != 16 && len != 24 && len != 32)
		वापस -EINVAL;

	ctx->key_length = len;

	स_नकल(ctx->aes_key, key, len);
	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_aead_encrypt(काष्ठा aead_request *req)
अणु
	पूर्णांक ret;
	काष्ठा artpec6_crypto_aead_req_ctx *req_ctx = aead_request_ctx(req);

	req_ctx->decrypt = false;
	ret = artpec6_crypto_common_init(&req_ctx->common, &req->base,
				  artpec6_crypto_complete_aead,
				  शून्य, 0);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_prepare_aead(req);
	अगर (ret) अणु
		artpec6_crypto_common_destroy(&req_ctx->common);
		वापस ret;
	पूर्ण

	वापस artpec6_crypto_submit(&req_ctx->common);
पूर्ण

अटल पूर्णांक artpec6_crypto_aead_decrypt(काष्ठा aead_request *req)
अणु
	पूर्णांक ret;
	काष्ठा artpec6_crypto_aead_req_ctx *req_ctx = aead_request_ctx(req);

	req_ctx->decrypt = true;
	अगर (req->cryptlen < AES_BLOCK_SIZE)
		वापस -EINVAL;

	ret = artpec6_crypto_common_init(&req_ctx->common,
				  &req->base,
				  artpec6_crypto_complete_aead,
				  शून्य, 0);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_prepare_aead(req);
	अगर (ret) अणु
		artpec6_crypto_common_destroy(&req_ctx->common);
		वापस ret;
	पूर्ण

	वापस artpec6_crypto_submit(&req_ctx->common);
पूर्ण

अटल पूर्णांक artpec6_crypto_prepare_hash(काष्ठा ahash_request *areq)
अणु
	काष्ठा artpec6_hashalg_context *ctx = crypto_tfm_ctx(areq->base.tfm);
	काष्ठा artpec6_hash_request_context *req_ctx = ahash_request_ctx(areq);
	माप_प्रकार digestsize = crypto_ahash_digestsize(crypto_ahash_reqtfm(areq));
	माप_प्रकार contextsize = digestsize;
	माप_प्रकार blocksize = crypto_tfm_alg_blocksize(
		crypto_ahash_tfm(crypto_ahash_reqtfm(areq)));
	काष्ठा artpec6_crypto_req_common *common = &req_ctx->common;
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	क्रमागत artpec6_crypto_variant variant = ac->variant;
	u32 sel_ctx;
	bool ext_ctx = false;
	bool run_hw = false;
	पूर्णांक error = 0;

	artpec6_crypto_init_dma_operation(common);

	/* Upload HMAC key, must be first the first packet */
	अगर (req_ctx->hash_flags & HASH_FLAG_HMAC) अणु
		अगर (variant == ARTPEC6_CRYPTO) अणु
			req_ctx->key_md = FIELD_PREP(A6_CRY_MD_OPER,
						     a6_regk_crypto_dlkey);
		पूर्ण अन्यथा अणु
			req_ctx->key_md = FIELD_PREP(A7_CRY_MD_OPER,
						     a7_regk_crypto_dlkey);
		पूर्ण

		/* Copy and pad up the key */
		स_नकल(req_ctx->key_buffer, ctx->hmac_key,
		       ctx->hmac_key_length);
		स_रखो(req_ctx->key_buffer + ctx->hmac_key_length, 0,
		       blocksize - ctx->hmac_key_length);

		error = artpec6_crypto_setup_out_descr(common,
					(व्योम *)&req_ctx->key_md,
					माप(req_ctx->key_md), false, false);
		अगर (error)
			वापस error;

		error = artpec6_crypto_setup_out_descr(common,
					req_ctx->key_buffer, blocksize,
					true, false);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (!(req_ctx->hash_flags & HASH_FLAG_INIT_CTX)) अणु
		/* Restore context */
		sel_ctx = regk_crypto_ext;
		ext_ctx = true;
	पूर्ण अन्यथा अणु
		sel_ctx = regk_crypto_init;
	पूर्ण

	अगर (variant == ARTPEC6_CRYPTO) अणु
		req_ctx->hash_md &= ~A6_CRY_MD_HASH_SEL_CTX;
		req_ctx->hash_md |= FIELD_PREP(A6_CRY_MD_HASH_SEL_CTX, sel_ctx);

		/* If this is the final round, set the final flag */
		अगर (req_ctx->hash_flags & HASH_FLAG_FINALIZE)
			req_ctx->hash_md |= A6_CRY_MD_HASH_HMAC_FIN;
	पूर्ण अन्यथा अणु
		req_ctx->hash_md &= ~A7_CRY_MD_HASH_SEL_CTX;
		req_ctx->hash_md |= FIELD_PREP(A7_CRY_MD_HASH_SEL_CTX, sel_ctx);

		/* If this is the final round, set the final flag */
		अगर (req_ctx->hash_flags & HASH_FLAG_FINALIZE)
			req_ctx->hash_md |= A7_CRY_MD_HASH_HMAC_FIN;
	पूर्ण

	/* Setup up metadata descriptors */
	error = artpec6_crypto_setup_out_descr(common,
				(व्योम *)&req_ctx->hash_md,
				माप(req_ctx->hash_md), false, false);
	अगर (error)
		वापस error;

	error = artpec6_crypto_setup_in_descr(common, ac->pad_buffer, 4, false);
	अगर (error)
		वापस error;

	अगर (ext_ctx) अणु
		error = artpec6_crypto_setup_out_descr(common,
					req_ctx->digeststate,
					contextsize, false, false);

		अगर (error)
			वापस error;
	पूर्ण

	अगर (req_ctx->hash_flags & HASH_FLAG_UPDATE) अणु
		माप_प्रकार करोne_bytes = 0;
		माप_प्रकार total_bytes = areq->nbytes + req_ctx->partial_bytes;
		माप_प्रकार पढ़ोy_bytes = round_करोwn(total_bytes, blocksize);
		काष्ठा artpec6_crypto_walk walk;

		run_hw = पढ़ोy_bytes > 0;
		अगर (req_ctx->partial_bytes && पढ़ोy_bytes) अणु
			/* We have a partial buffer and will at least some bytes
			 * to the HW. Empty this partial buffer beक्रमe tackling
			 * the SG lists
			 */
			स_नकल(req_ctx->partial_buffer_out,
				req_ctx->partial_buffer,
				req_ctx->partial_bytes);

			error = artpec6_crypto_setup_out_descr(common,
						req_ctx->partial_buffer_out,
						req_ctx->partial_bytes,
						false, true);
			अगर (error)
				वापस error;

			/* Reset partial buffer */
			करोne_bytes += req_ctx->partial_bytes;
			req_ctx->partial_bytes = 0;
		पूर्ण

		artpec6_crypto_walk_init(&walk, areq->src);

		error = artpec6_crypto_setup_sg_descrs_out(common, &walk,
							   पढ़ोy_bytes -
							   करोne_bytes);
		अगर (error)
			वापस error;

		अगर (walk.sg) अणु
			माप_प्रकार sg_skip = पढ़ोy_bytes - करोne_bytes;
			माप_प्रकार sg_rem = areq->nbytes - sg_skip;

			sg_pcopy_to_buffer(areq->src, sg_nents(areq->src),
					   req_ctx->partial_buffer +
					   req_ctx->partial_bytes,
					   sg_rem, sg_skip);

			req_ctx->partial_bytes += sg_rem;
		पूर्ण

		req_ctx->digcnt += पढ़ोy_bytes;
		req_ctx->hash_flags &= ~(HASH_FLAG_UPDATE);
	पूर्ण

	/* Finalize */
	अगर (req_ctx->hash_flags & HASH_FLAG_FINALIZE) अणु
		माप_प्रकार hash_pad_len;
		u64 digest_bits;
		u32 oper;

		अगर (variant == ARTPEC6_CRYPTO)
			oper = FIELD_GET(A6_CRY_MD_OPER, req_ctx->hash_md);
		अन्यथा
			oper = FIELD_GET(A7_CRY_MD_OPER, req_ctx->hash_md);

		/* Write out the partial buffer अगर present */
		अगर (req_ctx->partial_bytes) अणु
			स_नकल(req_ctx->partial_buffer_out,
			       req_ctx->partial_buffer,
			       req_ctx->partial_bytes);
			error = artpec6_crypto_setup_out_descr(common,
						req_ctx->partial_buffer_out,
						req_ctx->partial_bytes,
						false, true);
			अगर (error)
				वापस error;

			req_ctx->digcnt += req_ctx->partial_bytes;
			req_ctx->partial_bytes = 0;
		पूर्ण

		अगर (req_ctx->hash_flags & HASH_FLAG_HMAC)
			digest_bits = 8 * (req_ctx->digcnt + blocksize);
		अन्यथा
			digest_bits = 8 * req_ctx->digcnt;

		/* Add the hash pad */
		hash_pad_len = create_hash_pad(oper, req_ctx->pad_buffer,
					       req_ctx->digcnt, digest_bits);
		error = artpec6_crypto_setup_out_descr(common,
						      req_ctx->pad_buffer,
						      hash_pad_len, false,
						      true);
		req_ctx->digcnt = 0;

		अगर (error)
			वापस error;

		/* Descriptor क्रम the final result */
		error = artpec6_crypto_setup_in_descr(common, areq->result,
						      digestsize,
						      true);
		अगर (error)
			वापस error;

	पूर्ण अन्यथा अणु /* This is not the final operation क्रम this request */
		अगर (!run_hw)
			वापस ARTPEC6_CRYPTO_PREPARE_HASH_NO_START;

		/* Save the result to the context */
		error = artpec6_crypto_setup_in_descr(common,
						      req_ctx->digeststate,
						      contextsize, false);
		अगर (error)
			वापस error;
		/* fall through */
	पूर्ण

	req_ctx->hash_flags &= ~(HASH_FLAG_INIT_CTX | HASH_FLAG_UPDATE |
				 HASH_FLAG_FINALIZE);

	error = artpec6_crypto_terminate_in_descrs(common);
	अगर (error)
		वापस error;

	error = artpec6_crypto_terminate_out_descrs(common);
	अगर (error)
		वापस error;

	error = artpec6_crypto_dma_map_descs(common);
	अगर (error)
		वापस error;

	वापस ARTPEC6_CRYPTO_PREPARE_HASH_START;
पूर्ण


अटल पूर्णांक artpec6_crypto_aes_ecb_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	tfm->reqsize = माप(काष्ठा artpec6_crypto_request_context);
	ctx->crypto_type = ARTPEC6_CRYPTO_CIPHER_AES_ECB;

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_aes_ctr_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	ctx->fallback =
		crypto_alloc_sync_skcipher(crypto_tfm_alg_name(&tfm->base),
					   0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->fallback))
		वापस PTR_ERR(ctx->fallback);

	tfm->reqsize = माप(काष्ठा artpec6_crypto_request_context);
	ctx->crypto_type = ARTPEC6_CRYPTO_CIPHER_AES_CTR;

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_aes_cbc_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	tfm->reqsize = माप(काष्ठा artpec6_crypto_request_context);
	ctx->crypto_type = ARTPEC6_CRYPTO_CIPHER_AES_CBC;

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_aes_xts_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	tfm->reqsize = माप(काष्ठा artpec6_crypto_request_context);
	ctx->crypto_type = ARTPEC6_CRYPTO_CIPHER_AES_XTS;

	वापस 0;
पूर्ण

अटल व्योम artpec6_crypto_aes_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	स_रखो(ctx, 0, माप(*ctx));
पूर्ण

अटल व्योम artpec6_crypto_aes_ctr_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_sync_skcipher(ctx->fallback);
	artpec6_crypto_aes_निकास(tfm);
पूर्ण

अटल पूर्णांक
artpec6_crypto_cipher_set_key(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx =
		crypto_skcipher_ctx(cipher);

	चयन (keylen) अणु
	हाल 16:
	हाल 24:
	हाल 32:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	स_नकल(ctx->aes_key, key, keylen);
	ctx->key_length = keylen;
	वापस 0;
पूर्ण

अटल पूर्णांक
artpec6_crypto_xts_set_key(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा artpec6_cryptotfm_context *ctx =
		crypto_skcipher_ctx(cipher);
	पूर्णांक ret;

	ret = xts_check_key(&cipher->base, key, keylen);
	अगर (ret)
		वापस ret;

	चयन (keylen) अणु
	हाल 32:
	हाल 48:
	हाल 64:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	स_नकल(ctx->aes_key, key, keylen);
	ctx->key_length = keylen;
	वापस 0;
पूर्ण

/** artpec6_crypto_process_crypto - Prepare an async block cipher crypto request
 *
 * @req: The asynch request to process
 *
 * @वापस 0 अगर the dma job was successfully prepared
 *	  <0 on error
 *
 * This function sets up the PDMA descriptors क्रम a block cipher request.
 *
 * The required padding is added क्रम AES-CTR using a अटलally defined
 * buffer.
 *
 * The PDMA descriptor list will be as follows:
 *
 * OUT: [KEY_MD][KEY][EOP]<CIPHER_MD>[IV]<data_0>...[data_n][AES-CTR_pad]<eop>
 * IN:  <CIPHER_MD><data_0>...[data_n]<पूर्णांकr>
 *
 */
अटल पूर्णांक artpec6_crypto_prepare_crypto(काष्ठा skcipher_request *areq)
अणु
	पूर्णांक ret;
	काष्ठा artpec6_crypto_walk walk;
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा artpec6_crypto_request_context *req_ctx = शून्य;
	माप_प्रकार iv_len = crypto_skcipher_ivsize(cipher);
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	क्रमागत artpec6_crypto_variant variant = ac->variant;
	काष्ठा artpec6_crypto_req_common *common;
	bool cipher_decr = false;
	माप_प्रकार cipher_klen;
	u32 cipher_len = 0; /* Same as regk_crypto_key_128 क्रम शून्य crypto */
	u32 oper;

	req_ctx = skcipher_request_ctx(areq);
	common = &req_ctx->common;

	artpec6_crypto_init_dma_operation(common);

	अगर (variant == ARTPEC6_CRYPTO)
		ctx->key_md = FIELD_PREP(A6_CRY_MD_OPER, a6_regk_crypto_dlkey);
	अन्यथा
		ctx->key_md = FIELD_PREP(A7_CRY_MD_OPER, a7_regk_crypto_dlkey);

	ret = artpec6_crypto_setup_out_descr(common, (व्योम *)&ctx->key_md,
					     माप(ctx->key_md), false, false);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_setup_out_descr(common, ctx->aes_key,
					      ctx->key_length, true, false);
	अगर (ret)
		वापस ret;

	req_ctx->cipher_md = 0;

	अगर (ctx->crypto_type == ARTPEC6_CRYPTO_CIPHER_AES_XTS)
		cipher_klen = ctx->key_length/2;
	अन्यथा
		cipher_klen =  ctx->key_length;

	/* Metadata */
	चयन (cipher_klen) अणु
	हाल 16:
		cipher_len = regk_crypto_key_128;
		अवरोध;
	हाल 24:
		cipher_len = regk_crypto_key_192;
		अवरोध;
	हाल 32:
		cipher_len = regk_crypto_key_256;
		अवरोध;
	शेष:
		pr_err("%s: Invalid key length %d!\n",
			MODULE_NAME, ctx->key_length);
		वापस -EINVAL;
	पूर्ण

	चयन (ctx->crypto_type) अणु
	हाल ARTPEC6_CRYPTO_CIPHER_AES_ECB:
		oper = regk_crypto_aes_ecb;
		cipher_decr = req_ctx->decrypt;
		अवरोध;

	हाल ARTPEC6_CRYPTO_CIPHER_AES_CBC:
		oper = regk_crypto_aes_cbc;
		cipher_decr = req_ctx->decrypt;
		अवरोध;

	हाल ARTPEC6_CRYPTO_CIPHER_AES_CTR:
		oper = regk_crypto_aes_ctr;
		cipher_decr = false;
		अवरोध;

	हाल ARTPEC6_CRYPTO_CIPHER_AES_XTS:
		oper = regk_crypto_aes_xts;
		cipher_decr = req_ctx->decrypt;

		अगर (variant == ARTPEC6_CRYPTO)
			req_ctx->cipher_md |= A6_CRY_MD_CIPHER_DSEQ;
		अन्यथा
			req_ctx->cipher_md |= A7_CRY_MD_CIPHER_DSEQ;
		अवरोध;

	शेष:
		pr_err("%s: Invalid cipher mode %d!\n",
			MODULE_NAME, ctx->crypto_type);
		वापस -EINVAL;
	पूर्ण

	अगर (variant == ARTPEC6_CRYPTO) अणु
		req_ctx->cipher_md |= FIELD_PREP(A6_CRY_MD_OPER, oper);
		req_ctx->cipher_md |= FIELD_PREP(A6_CRY_MD_CIPHER_LEN,
						 cipher_len);
		अगर (cipher_decr)
			req_ctx->cipher_md |= A6_CRY_MD_CIPHER_DECR;
	पूर्ण अन्यथा अणु
		req_ctx->cipher_md |= FIELD_PREP(A7_CRY_MD_OPER, oper);
		req_ctx->cipher_md |= FIELD_PREP(A7_CRY_MD_CIPHER_LEN,
						 cipher_len);
		अगर (cipher_decr)
			req_ctx->cipher_md |= A7_CRY_MD_CIPHER_DECR;
	पूर्ण

	ret = artpec6_crypto_setup_out_descr(common,
					    &req_ctx->cipher_md,
					    माप(req_ctx->cipher_md),
					    false, false);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_setup_in_descr(common, ac->pad_buffer, 4, false);
	अगर (ret)
		वापस ret;

	अगर (iv_len) अणु
		ret = artpec6_crypto_setup_out_descr(common, areq->iv, iv_len,
						     false, false);
		अगर (ret)
			वापस ret;
	पूर्ण
	/* Data out */
	artpec6_crypto_walk_init(&walk, areq->src);
	ret = artpec6_crypto_setup_sg_descrs_out(common, &walk, areq->cryptlen);
	अगर (ret)
		वापस ret;

	/* Data in */
	artpec6_crypto_walk_init(&walk, areq->dst);
	ret = artpec6_crypto_setup_sg_descrs_in(common, &walk, areq->cryptlen);
	अगर (ret)
		वापस ret;

	/* CTR-mode padding required by the HW. */
	अगर (ctx->crypto_type == ARTPEC6_CRYPTO_CIPHER_AES_CTR ||
	    ctx->crypto_type == ARTPEC6_CRYPTO_CIPHER_AES_XTS) अणु
		माप_प्रकार pad = ALIGN(areq->cryptlen, AES_BLOCK_SIZE) -
			     areq->cryptlen;

		अगर (pad) अणु
			ret = artpec6_crypto_setup_out_descr(common,
							     ac->pad_buffer,
							     pad, false, false);
			अगर (ret)
				वापस ret;

			ret = artpec6_crypto_setup_in_descr(common,
							    ac->pad_buffer, pad,
							    false);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = artpec6_crypto_terminate_out_descrs(common);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_terminate_in_descrs(common);
	अगर (ret)
		वापस ret;

	वापस artpec6_crypto_dma_map_descs(common);
पूर्ण

अटल पूर्णांक artpec6_crypto_prepare_aead(काष्ठा aead_request *areq)
अणु
	माप_प्रकार count;
	पूर्णांक ret;
	माप_प्रकार input_length;
	काष्ठा artpec6_cryptotfm_context *ctx = crypto_tfm_ctx(areq->base.tfm);
	काष्ठा artpec6_crypto_aead_req_ctx *req_ctx = aead_request_ctx(areq);
	काष्ठा crypto_aead *cipher = crypto_aead_reqtfm(areq);
	काष्ठा artpec6_crypto_req_common *common = &req_ctx->common;
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	क्रमागत artpec6_crypto_variant variant = ac->variant;
	u32 md_cipher_len;

	artpec6_crypto_init_dma_operation(common);

	/* Key */
	अगर (variant == ARTPEC6_CRYPTO) अणु
		ctx->key_md = FIELD_PREP(A6_CRY_MD_OPER,
					 a6_regk_crypto_dlkey);
	पूर्ण अन्यथा अणु
		ctx->key_md = FIELD_PREP(A7_CRY_MD_OPER,
					 a7_regk_crypto_dlkey);
	पूर्ण
	ret = artpec6_crypto_setup_out_descr(common, (व्योम *)&ctx->key_md,
					     माप(ctx->key_md), false, false);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_setup_out_descr(common, ctx->aes_key,
					     ctx->key_length, true, false);
	अगर (ret)
		वापस ret;

	req_ctx->cipher_md = 0;

	चयन (ctx->key_length) अणु
	हाल 16:
		md_cipher_len = regk_crypto_key_128;
		अवरोध;
	हाल 24:
		md_cipher_len = regk_crypto_key_192;
		अवरोध;
	हाल 32:
		md_cipher_len = regk_crypto_key_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (variant == ARTPEC6_CRYPTO) अणु
		req_ctx->cipher_md |= FIELD_PREP(A6_CRY_MD_OPER,
						 regk_crypto_aes_gcm);
		req_ctx->cipher_md |= FIELD_PREP(A6_CRY_MD_CIPHER_LEN,
						 md_cipher_len);
		अगर (req_ctx->decrypt)
			req_ctx->cipher_md |= A6_CRY_MD_CIPHER_DECR;
	पूर्ण अन्यथा अणु
		req_ctx->cipher_md |= FIELD_PREP(A7_CRY_MD_OPER,
						 regk_crypto_aes_gcm);
		req_ctx->cipher_md |= FIELD_PREP(A7_CRY_MD_CIPHER_LEN,
						 md_cipher_len);
		अगर (req_ctx->decrypt)
			req_ctx->cipher_md |= A7_CRY_MD_CIPHER_DECR;
	पूर्ण

	ret = artpec6_crypto_setup_out_descr(common,
					    (व्योम *) &req_ctx->cipher_md,
					    माप(req_ctx->cipher_md), false,
					    false);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_setup_in_descr(common, ac->pad_buffer, 4, false);
	अगर (ret)
		वापस ret;

	/* For the decryption, cryptlen includes the tag. */
	input_length = areq->cryptlen;
	अगर (req_ctx->decrypt)
		input_length -= crypto_aead_authsize(cipher);

	/* Prepare the context buffer */
	req_ctx->hw_ctx.aad_length_bits =
		__cpu_to_be64(8*areq->assoclen);

	req_ctx->hw_ctx.text_length_bits =
		__cpu_to_be64(8*input_length);

	स_नकल(req_ctx->hw_ctx.J0, areq->iv, crypto_aead_ivsize(cipher));
	// The HW omits the initial increment of the counter field.
	स_नकल(req_ctx->hw_ctx.J0 + GCM_AES_IV_SIZE, "\x00\x00\x00\x01", 4);

	ret = artpec6_crypto_setup_out_descr(common, &req_ctx->hw_ctx,
		माप(काष्ठा artpec6_crypto_aead_hw_ctx), false, false);
	अगर (ret)
		वापस ret;

	अणु
		काष्ठा artpec6_crypto_walk walk;

		artpec6_crypto_walk_init(&walk, areq->src);

		/* Associated data */
		count = areq->assoclen;
		ret = artpec6_crypto_setup_sg_descrs_out(common, &walk, count);
		अगर (ret)
			वापस ret;

		अगर (!IS_ALIGNED(areq->assoclen, 16)) अणु
			माप_प्रकार assoc_pad = 16 - (areq->assoclen % 16);
			/* The HW mandates zero padding here */
			ret = artpec6_crypto_setup_out_descr(common,
							     ac->zero_buffer,
							     assoc_pad, false,
							     false);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* Data to crypto */
		count = input_length;
		ret = artpec6_crypto_setup_sg_descrs_out(common, &walk, count);
		अगर (ret)
			वापस ret;

		अगर (!IS_ALIGNED(input_length, 16)) अणु
			माप_प्रकार crypto_pad = 16 - (input_length % 16);
			/* The HW mandates zero padding here */
			ret = artpec6_crypto_setup_out_descr(common,
							     ac->zero_buffer,
							     crypto_pad,
							     false,
							     false);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Data from crypto */
	अणु
		काष्ठा artpec6_crypto_walk walk;
		माप_प्रकार output_len = areq->cryptlen;

		अगर (req_ctx->decrypt)
			output_len -= crypto_aead_authsize(cipher);

		artpec6_crypto_walk_init(&walk, areq->dst);

		/* skip associated data in the output */
		count = artpec6_crypto_walk_advance(&walk, areq->assoclen);
		अगर (count)
			वापस -EINVAL;

		count = output_len;
		ret = artpec6_crypto_setup_sg_descrs_in(common, &walk, count);
		अगर (ret)
			वापस ret;

		/* Put padding between the cryptotext and the auth tag */
		अगर (!IS_ALIGNED(output_len, 16)) अणु
			माप_प्रकार crypto_pad = 16 - (output_len % 16);

			ret = artpec6_crypto_setup_in_descr(common,
							    ac->pad_buffer,
							    crypto_pad, false);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* The authentication tag shall follow immediately after
		 * the output ciphertext. For decryption it is put in a context
		 * buffer क्रम later compare against the input tag.
		 */

		अगर (req_ctx->decrypt) अणु
			ret = artpec6_crypto_setup_in_descr(common,
				req_ctx->decryption_tag, AES_BLOCK_SIZE, false);
			अगर (ret)
				वापस ret;

		पूर्ण अन्यथा अणु
			/* For encryption the requested tag size may be smaller
			 * than the hardware's generated tag.
			 */
			माप_प्रकार authsize = crypto_aead_authsize(cipher);

			ret = artpec6_crypto_setup_sg_descrs_in(common, &walk,
								authsize);
			अगर (ret)
				वापस ret;

			अगर (authsize < AES_BLOCK_SIZE) अणु
				count = AES_BLOCK_SIZE - authsize;
				ret = artpec6_crypto_setup_in_descr(common,
					ac->pad_buffer,
					count, false);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण

	पूर्ण

	ret = artpec6_crypto_terminate_in_descrs(common);
	अगर (ret)
		वापस ret;

	ret = artpec6_crypto_terminate_out_descrs(common);
	अगर (ret)
		वापस ret;

	वापस artpec6_crypto_dma_map_descs(common);
पूर्ण

अटल व्योम artpec6_crypto_process_queue(काष्ठा artpec6_crypto *ac,
	    काष्ठा list_head *completions)
अणु
	काष्ठा artpec6_crypto_req_common *req;

	जबतक (!list_empty(&ac->queue) && !artpec6_crypto_busy()) अणु
		req = list_first_entry(&ac->queue,
				       काष्ठा artpec6_crypto_req_common,
				       list);
		list_move_tail(&req->list, &ac->pending);
		artpec6_crypto_start_dma(req);

		list_add_tail(&req->complete_in_progress, completions);
	पूर्ण

	/*
	 * In some हालs, the hardware can उठाओ an in_eop_flush पूर्णांकerrupt
	 * beक्रमe actually updating the status, so we have an समयr which will
	 * recheck the status on समयout.  Since the हालs are expected to be
	 * very rare, we use a relatively large समयout value.  There should be
	 * no noticeable negative effect अगर we समयout spuriously.
	 */
	अगर (ac->pending_count)
		mod_समयr(&ac->समयr, jअगरfies + msecs_to_jअगरfies(100));
	अन्यथा
		del_समयr(&ac->समयr);
पूर्ण

अटल व्योम artpec6_crypto_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा artpec6_crypto *ac = from_समयr(ac, t, समयr);

	dev_info_ratelimited(artpec6_crypto_dev, "timeout\n");

	tasklet_schedule(&ac->task);
पूर्ण

अटल व्योम artpec6_crypto_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा artpec6_crypto *ac = (काष्ठा artpec6_crypto *)data;
	काष्ठा artpec6_crypto_req_common *req;
	काष्ठा artpec6_crypto_req_common *n;
	काष्ठा list_head complete_करोne;
	काष्ठा list_head complete_in_progress;

	INIT_LIST_HEAD(&complete_करोne);
	INIT_LIST_HEAD(&complete_in_progress);

	अगर (list_empty(&ac->pending)) अणु
		pr_debug("Spurious IRQ\n");
		वापस;
	पूर्ण

	spin_lock_bh(&ac->queue_lock);

	list_क्रम_each_entry_safe(req, n, &ac->pending, list) अणु
		काष्ठा artpec6_crypto_dma_descriptors *dma = req->dma;
		u32 stat;
		dma_addr_t stataddr;

		stataddr = dma->stat_dma_addr + 4 * (req->dma->in_cnt - 1);
		dma_sync_single_क्रम_cpu(artpec6_crypto_dev,
					stataddr,
					4,
					DMA_BIसूचीECTIONAL);

		stat = req->dma->stat[req->dma->in_cnt-1];

		/* A non-zero final status descriptor indicates
		 * this job has finished.
		 */
		pr_debug("Request %p status is %X\n", req, stat);
		अगर (!stat)
			अवरोध;

		/* Allow testing of समयout handling with fault injection */
#अगर_घोषित CONFIG_FAULT_INJECTION
		अगर (should_fail(&artpec6_crypto_fail_status_पढ़ो, 1))
			जारी;
#पूर्ण_अगर

		pr_debug("Completing request %p\n", req);

		list_move_tail(&req->list, &complete_करोne);

		ac->pending_count--;
	पूर्ण

	artpec6_crypto_process_queue(ac, &complete_in_progress);

	spin_unlock_bh(&ac->queue_lock);

	/* Perक्रमm the completion callbacks without holding the queue lock
	 * to allow new request submissions from the callbacks.
	 */
	list_क्रम_each_entry_safe(req, n, &complete_करोne, list) अणु
		artpec6_crypto_dma_unmap_all(req);
		artpec6_crypto_copy_bounce_buffers(req);
		artpec6_crypto_common_destroy(req);

		req->complete(req->req);
	पूर्ण

	list_क्रम_each_entry_safe(req, n, &complete_in_progress,
				 complete_in_progress) अणु
		req->req->complete(req->req, -EINPROGRESS);
	पूर्ण
पूर्ण

अटल व्योम artpec6_crypto_complete_crypto(काष्ठा crypto_async_request *req)
अणु
	req->complete(req, 0);
पूर्ण

अटल व्योम
artpec6_crypto_complete_cbc_decrypt(काष्ठा crypto_async_request *req)
अणु
	काष्ठा skcipher_request *cipher_req = container_of(req,
		काष्ठा skcipher_request, base);

	scatterwalk_map_and_copy(cipher_req->iv, cipher_req->src,
				 cipher_req->cryptlen - AES_BLOCK_SIZE,
				 AES_BLOCK_SIZE, 0);
	req->complete(req, 0);
पूर्ण

अटल व्योम
artpec6_crypto_complete_cbc_encrypt(काष्ठा crypto_async_request *req)
अणु
	काष्ठा skcipher_request *cipher_req = container_of(req,
		काष्ठा skcipher_request, base);

	scatterwalk_map_and_copy(cipher_req->iv, cipher_req->dst,
				 cipher_req->cryptlen - AES_BLOCK_SIZE,
				 AES_BLOCK_SIZE, 0);
	req->complete(req, 0);
पूर्ण

अटल व्योम artpec6_crypto_complete_aead(काष्ठा crypto_async_request *req)
अणु
	पूर्णांक result = 0;

	/* Verअगरy GCM hashtag. */
	काष्ठा aead_request *areq = container_of(req,
		काष्ठा aead_request, base);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(areq);
	काष्ठा artpec6_crypto_aead_req_ctx *req_ctx = aead_request_ctx(areq);

	अगर (req_ctx->decrypt) अणु
		u8 input_tag[AES_BLOCK_SIZE];
		अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);

		sg_pcopy_to_buffer(areq->src,
				   sg_nents(areq->src),
				   input_tag,
				   authsize,
				   areq->assoclen + areq->cryptlen -
				   authsize);

		अगर (crypto_memneq(req_ctx->decryption_tag,
				  input_tag,
				  authsize)) अणु
			pr_debug("***EBADMSG:\n");
			prपूर्णांक_hex_dump_debug("ref:", DUMP_PREFIX_ADDRESS, 32, 1,
					     input_tag, authsize, true);
			prपूर्णांक_hex_dump_debug("out:", DUMP_PREFIX_ADDRESS, 32, 1,
					     req_ctx->decryption_tag,
					     authsize, true);

			result = -EBADMSG;
		पूर्ण
	पूर्ण

	req->complete(req, result);
पूर्ण

अटल व्योम artpec6_crypto_complete_hash(काष्ठा crypto_async_request *req)
अणु
	req->complete(req, 0);
पूर्ण


/*------------------- Hash functions -----------------------------------------*/
अटल पूर्णांक
artpec6_crypto_hash_set_key(काष्ठा crypto_ahash *tfm,
		    स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा artpec6_hashalg_context *tfm_ctx = crypto_tfm_ctx(&tfm->base);
	माप_प्रकार blocksize;
	पूर्णांक ret;

	अगर (!keylen) अणु
		pr_err("Invalid length (%d) of HMAC key\n",
			keylen);
		वापस -EINVAL;
	पूर्ण

	स_रखो(tfm_ctx->hmac_key, 0, माप(tfm_ctx->hmac_key));

	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	अगर (keylen > blocksize) अणु
		tfm_ctx->hmac_key_length = blocksize;

		ret = crypto_shash_tfm_digest(tfm_ctx->child_hash, key, keylen,
					      tfm_ctx->hmac_key);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		स_नकल(tfm_ctx->hmac_key, key, keylen);
		tfm_ctx->hmac_key_length = keylen;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
artpec6_crypto_init_hash(काष्ठा ahash_request *req, u8 type, पूर्णांक hmac)
अणु
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	क्रमागत artpec6_crypto_variant variant = ac->variant;
	काष्ठा artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);
	u32 oper;

	स_रखो(req_ctx, 0, माप(*req_ctx));

	req_ctx->hash_flags = HASH_FLAG_INIT_CTX;
	अगर (hmac)
		req_ctx->hash_flags |= (HASH_FLAG_HMAC | HASH_FLAG_UPDATE_KEY);

	चयन (type) अणु
	हाल ARTPEC6_CRYPTO_HASH_SHA1:
		oper = hmac ? regk_crypto_hmac_sha1 : regk_crypto_sha1;
		अवरोध;
	हाल ARTPEC6_CRYPTO_HASH_SHA256:
		oper = hmac ? regk_crypto_hmac_sha256 : regk_crypto_sha256;
		अवरोध;
	शेष:
		pr_err("%s: Unsupported hash type 0x%x\n", MODULE_NAME, type);
		वापस -EINVAL;
	पूर्ण

	अगर (variant == ARTPEC6_CRYPTO)
		req_ctx->hash_md = FIELD_PREP(A6_CRY_MD_OPER, oper);
	अन्यथा
		req_ctx->hash_md = FIELD_PREP(A7_CRY_MD_OPER, oper);

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_prepare_submit_hash(काष्ठा ahash_request *req)
अणु
	काष्ठा artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);
	पूर्णांक ret;

	अगर (!req_ctx->common.dma) अणु
		ret = artpec6_crypto_common_init(&req_ctx->common,
					  &req->base,
					  artpec6_crypto_complete_hash,
					  शून्य, 0);

		अगर (ret)
			वापस ret;
	पूर्ण

	ret = artpec6_crypto_prepare_hash(req);
	चयन (ret) अणु
	हाल ARTPEC6_CRYPTO_PREPARE_HASH_START:
		ret = artpec6_crypto_submit(&req_ctx->common);
		अवरोध;

	हाल ARTPEC6_CRYPTO_PREPARE_HASH_NO_START:
		ret = 0;
		fallthrough;

	शेष:
		artpec6_crypto_common_destroy(&req_ctx->common);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक artpec6_crypto_hash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);

	req_ctx->hash_flags |= HASH_FLAG_FINALIZE;

	वापस artpec6_crypto_prepare_submit_hash(req);
पूर्ण

अटल पूर्णांक artpec6_crypto_hash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);

	req_ctx->hash_flags |= HASH_FLAG_UPDATE;

	वापस artpec6_crypto_prepare_submit_hash(req);
पूर्ण

अटल पूर्णांक artpec6_crypto_sha1_init(काष्ठा ahash_request *req)
अणु
	वापस artpec6_crypto_init_hash(req, ARTPEC6_CRYPTO_HASH_SHA1, 0);
पूर्ण

अटल पूर्णांक artpec6_crypto_sha1_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);

	artpec6_crypto_init_hash(req, ARTPEC6_CRYPTO_HASH_SHA1, 0);

	req_ctx->hash_flags |= HASH_FLAG_UPDATE | HASH_FLAG_FINALIZE;

	वापस artpec6_crypto_prepare_submit_hash(req);
पूर्ण

अटल पूर्णांक artpec6_crypto_sha256_init(काष्ठा ahash_request *req)
अणु
	वापस artpec6_crypto_init_hash(req, ARTPEC6_CRYPTO_HASH_SHA256, 0);
पूर्ण

अटल पूर्णांक artpec6_crypto_sha256_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);

	artpec6_crypto_init_hash(req, ARTPEC6_CRYPTO_HASH_SHA256, 0);
	req_ctx->hash_flags |= HASH_FLAG_UPDATE | HASH_FLAG_FINALIZE;

	वापस artpec6_crypto_prepare_submit_hash(req);
पूर्ण

अटल पूर्णांक artpec6_crypto_hmac_sha256_init(काष्ठा ahash_request *req)
अणु
	वापस artpec6_crypto_init_hash(req, ARTPEC6_CRYPTO_HASH_SHA256, 1);
पूर्ण

अटल पूर्णांक artpec6_crypto_hmac_sha256_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा artpec6_hash_request_context *req_ctx = ahash_request_ctx(req);

	artpec6_crypto_init_hash(req, ARTPEC6_CRYPTO_HASH_SHA256, 1);
	req_ctx->hash_flags |= HASH_FLAG_UPDATE | HASH_FLAG_FINALIZE;

	वापस artpec6_crypto_prepare_submit_hash(req);
पूर्ण

अटल पूर्णांक artpec6_crypto_ahash_init_common(काष्ठा crypto_tfm *tfm,
				    स्थिर अक्षर *base_hash_name)
अणु
	काष्ठा artpec6_hashalg_context *tfm_ctx = crypto_tfm_ctx(tfm);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा artpec6_hash_request_context));
	स_रखो(tfm_ctx, 0, माप(*tfm_ctx));

	अगर (base_hash_name) अणु
		काष्ठा crypto_shash *child;

		child = crypto_alloc_shash(base_hash_name, 0,
					   CRYPTO_ALG_NEED_FALLBACK);

		अगर (IS_ERR(child))
			वापस PTR_ERR(child);

		tfm_ctx->child_hash = child;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_ahash_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस artpec6_crypto_ahash_init_common(tfm, शून्य);
पूर्ण

अटल पूर्णांक artpec6_crypto_ahash_init_hmac_sha256(काष्ठा crypto_tfm *tfm)
अणु
	वापस artpec6_crypto_ahash_init_common(tfm, "sha256");
पूर्ण

अटल व्योम artpec6_crypto_ahash_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा artpec6_hashalg_context *tfm_ctx = crypto_tfm_ctx(tfm);

	अगर (tfm_ctx->child_hash)
		crypto_मुक्त_shash(tfm_ctx->child_hash);

	स_रखो(tfm_ctx->hmac_key, 0, माप(tfm_ctx->hmac_key));
	tfm_ctx->hmac_key_length = 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_hash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	स्थिर काष्ठा artpec6_hash_request_context *ctx = ahash_request_ctx(req);
	काष्ठा artpec6_hash_export_state *state = out;
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	क्रमागत artpec6_crypto_variant variant = ac->variant;

	BUILD_BUG_ON(माप(state->partial_buffer) !=
		     माप(ctx->partial_buffer));
	BUILD_BUG_ON(माप(state->digeststate) != माप(ctx->digeststate));

	state->digcnt = ctx->digcnt;
	state->partial_bytes = ctx->partial_bytes;
	state->hash_flags = ctx->hash_flags;

	अगर (variant == ARTPEC6_CRYPTO)
		state->oper = FIELD_GET(A6_CRY_MD_OPER, ctx->hash_md);
	अन्यथा
		state->oper = FIELD_GET(A7_CRY_MD_OPER, ctx->hash_md);

	स_नकल(state->partial_buffer, ctx->partial_buffer,
	       माप(state->partial_buffer));
	स_नकल(state->digeststate, ctx->digeststate,
	       माप(state->digeststate));

	वापस 0;
पूर्ण

अटल पूर्णांक artpec6_crypto_hash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा artpec6_hash_request_context *ctx = ahash_request_ctx(req);
	स्थिर काष्ठा artpec6_hash_export_state *state = in;
	काष्ठा artpec6_crypto *ac = dev_get_drvdata(artpec6_crypto_dev);
	क्रमागत artpec6_crypto_variant variant = ac->variant;

	स_रखो(ctx, 0, माप(*ctx));

	ctx->digcnt = state->digcnt;
	ctx->partial_bytes = state->partial_bytes;
	ctx->hash_flags = state->hash_flags;

	अगर (variant == ARTPEC6_CRYPTO)
		ctx->hash_md = FIELD_PREP(A6_CRY_MD_OPER, state->oper);
	अन्यथा
		ctx->hash_md = FIELD_PREP(A7_CRY_MD_OPER, state->oper);

	स_नकल(ctx->partial_buffer, state->partial_buffer,
	       माप(state->partial_buffer));
	स_नकल(ctx->digeststate, state->digeststate,
	       माप(state->digeststate));

	वापस 0;
पूर्ण

अटल पूर्णांक init_crypto_hw(काष्ठा artpec6_crypto *ac)
अणु
	क्रमागत artpec6_crypto_variant variant = ac->variant;
	व्योम __iomem *base = ac->base;
	u32 out_descr_buf_size;
	u32 out_data_buf_size;
	u32 in_data_buf_size;
	u32 in_descr_buf_size;
	u32 in_stat_buf_size;
	u32 in, out;

	/*
	 * The PDMA unit contains 1984 bytes of पूर्णांकernal memory क्रम the OUT
	 * channels and 1024 bytes क्रम the IN channel. This is an elastic
	 * memory used to पूर्णांकernally store the descriptors and data. The values
	 * ares specअगरied in 64 byte incremements.  Trustzone buffers are not
	 * used at this stage.
	 */
	out_data_buf_size = 16;  /* 1024 bytes क्रम data */
	out_descr_buf_size = 15; /* 960 bytes क्रम descriptors */
	in_data_buf_size = 8;    /* 512 bytes क्रम data */
	in_descr_buf_size = 4;   /* 256 bytes क्रम descriptors */
	in_stat_buf_size = 4;   /* 256 bytes क्रम stat descrs */

	BUILD_BUG_ON_MSG((out_data_buf_size
				+ out_descr_buf_size) * 64 > 1984,
			  "Invalid OUT configuration");

	BUILD_BUG_ON_MSG((in_data_buf_size
				+ in_descr_buf_size
				+ in_stat_buf_size) * 64 > 1024,
			  "Invalid IN configuration");

	in = FIELD_PREP(PDMA_IN_BUF_CFG_DATA_BUF_SIZE, in_data_buf_size) |
	     FIELD_PREP(PDMA_IN_BUF_CFG_DESCR_BUF_SIZE, in_descr_buf_size) |
	     FIELD_PREP(PDMA_IN_BUF_CFG_STAT_BUF_SIZE, in_stat_buf_size);

	out = FIELD_PREP(PDMA_OUT_BUF_CFG_DATA_BUF_SIZE, out_data_buf_size) |
	      FIELD_PREP(PDMA_OUT_BUF_CFG_DESCR_BUF_SIZE, out_descr_buf_size);

	ग_लिखोl_relaxed(out, base + PDMA_OUT_BUF_CFG);
	ग_लिखोl_relaxed(PDMA_OUT_CFG_EN, base + PDMA_OUT_CFG);

	अगर (variant == ARTPEC6_CRYPTO) अणु
		ग_लिखोl_relaxed(in, base + A6_PDMA_IN_BUF_CFG);
		ग_लिखोl_relaxed(PDMA_IN_CFG_EN, base + A6_PDMA_IN_CFG);
		ग_लिखोl_relaxed(A6_PDMA_INTR_MASK_IN_DATA |
			       A6_PDMA_INTR_MASK_IN_EOP_FLUSH,
			       base + A6_PDMA_INTR_MASK);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(in, base + A7_PDMA_IN_BUF_CFG);
		ग_लिखोl_relaxed(PDMA_IN_CFG_EN, base + A7_PDMA_IN_CFG);
		ग_लिखोl_relaxed(A7_PDMA_INTR_MASK_IN_DATA |
			       A7_PDMA_INTR_MASK_IN_EOP_FLUSH,
			       base + A7_PDMA_INTR_MASK);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम artpec6_crypto_disable_hw(काष्ठा artpec6_crypto *ac)
अणु
	क्रमागत artpec6_crypto_variant variant = ac->variant;
	व्योम __iomem *base = ac->base;

	अगर (variant == ARTPEC6_CRYPTO) अणु
		ग_लिखोl_relaxed(A6_PDMA_IN_CMD_STOP, base + A6_PDMA_IN_CMD);
		ग_लिखोl_relaxed(0, base + A6_PDMA_IN_CFG);
		ग_लिखोl_relaxed(A6_PDMA_OUT_CMD_STOP, base + PDMA_OUT_CMD);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(A7_PDMA_IN_CMD_STOP, base + A7_PDMA_IN_CMD);
		ग_लिखोl_relaxed(0, base + A7_PDMA_IN_CFG);
		ग_लिखोl_relaxed(A7_PDMA_OUT_CMD_STOP, base + PDMA_OUT_CMD);
	पूर्ण

	ग_लिखोl_relaxed(0, base + PDMA_OUT_CFG);

पूर्ण

अटल irqवापस_t artpec6_crypto_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा artpec6_crypto *ac = dev_id;
	क्रमागत artpec6_crypto_variant variant = ac->variant;
	व्योम __iomem *base = ac->base;
	u32 mask_in_data, mask_in_eop_flush;
	u32 in_cmd_flush_stat, in_cmd_reg;
	u32 ack_पूर्णांकr_reg;
	u32 ack = 0;
	u32 पूर्णांकr;

	अगर (variant == ARTPEC6_CRYPTO) अणु
		पूर्णांकr = पढ़ोl_relaxed(base + A6_PDMA_MASKED_INTR);
		mask_in_data = A6_PDMA_INTR_MASK_IN_DATA;
		mask_in_eop_flush = A6_PDMA_INTR_MASK_IN_EOP_FLUSH;
		in_cmd_flush_stat = A6_PDMA_IN_CMD_FLUSH_STAT;
		in_cmd_reg = A6_PDMA_IN_CMD;
		ack_पूर्णांकr_reg = A6_PDMA_ACK_INTR;
	पूर्ण अन्यथा अणु
		पूर्णांकr = पढ़ोl_relaxed(base + A7_PDMA_MASKED_INTR);
		mask_in_data = A7_PDMA_INTR_MASK_IN_DATA;
		mask_in_eop_flush = A7_PDMA_INTR_MASK_IN_EOP_FLUSH;
		in_cmd_flush_stat = A7_PDMA_IN_CMD_FLUSH_STAT;
		in_cmd_reg = A7_PDMA_IN_CMD;
		ack_पूर्णांकr_reg = A7_PDMA_ACK_INTR;
	पूर्ण

	/* We get two पूर्णांकerrupt notअगरications from each job.
	 * The in_data means all data was sent to memory and then
	 * we request a status flush command to ग_लिखो the per-job
	 * status to its status vector. This ensures that the
	 * tasklet can detect exactly how many submitted jobs
	 * that have finished.
	 */
	अगर (पूर्णांकr & mask_in_data)
		ack |= mask_in_data;

	अगर (पूर्णांकr & mask_in_eop_flush)
		ack |= mask_in_eop_flush;
	अन्यथा
		ग_लिखोl_relaxed(in_cmd_flush_stat, base + in_cmd_reg);

	ग_लिखोl_relaxed(ack, base + ack_पूर्णांकr_reg);

	अगर (पूर्णांकr & mask_in_eop_flush)
		tasklet_schedule(&ac->task);

	वापस IRQ_HANDLED;
पूर्ण

/*------------------- Algorithm definitions ----------------------------------*/

/* Hashes */
अटल काष्ठा ahash_alg hash_algos[] = अणु
	/* SHA-1 */
	अणु
		.init = artpec6_crypto_sha1_init,
		.update = artpec6_crypto_hash_update,
		.final = artpec6_crypto_hash_final,
		.digest = artpec6_crypto_sha1_digest,
		.import = artpec6_crypto_hash_import,
		.export = artpec6_crypto_hash_export,
		.halg.digestsize = SHA1_DIGEST_SIZE,
		.halg.statesize = माप(काष्ठा artpec6_hash_export_state),
		.halg.base = अणु
			.cra_name = "sha1",
			.cra_driver_name = "artpec-sha1",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = SHA1_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा artpec6_hashalg_context),
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
			.cra_init = artpec6_crypto_ahash_init,
			.cra_निकास = artpec6_crypto_ahash_निकास,
		पूर्ण
	पूर्ण,
	/* SHA-256 */
	अणु
		.init = artpec6_crypto_sha256_init,
		.update = artpec6_crypto_hash_update,
		.final = artpec6_crypto_hash_final,
		.digest = artpec6_crypto_sha256_digest,
		.import = artpec6_crypto_hash_import,
		.export = artpec6_crypto_hash_export,
		.halg.digestsize = SHA256_DIGEST_SIZE,
		.halg.statesize = माप(काष्ठा artpec6_hash_export_state),
		.halg.base = अणु
			.cra_name = "sha256",
			.cra_driver_name = "artpec-sha256",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = SHA256_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा artpec6_hashalg_context),
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
			.cra_init = artpec6_crypto_ahash_init,
			.cra_निकास = artpec6_crypto_ahash_निकास,
		पूर्ण
	पूर्ण,
	/* HMAC SHA-256 */
	अणु
		.init = artpec6_crypto_hmac_sha256_init,
		.update = artpec6_crypto_hash_update,
		.final = artpec6_crypto_hash_final,
		.digest = artpec6_crypto_hmac_sha256_digest,
		.import = artpec6_crypto_hash_import,
		.export = artpec6_crypto_hash_export,
		.setkey = artpec6_crypto_hash_set_key,
		.halg.digestsize = SHA256_DIGEST_SIZE,
		.halg.statesize = माप(काष्ठा artpec6_hash_export_state),
		.halg.base = अणु
			.cra_name = "hmac(sha256)",
			.cra_driver_name = "artpec-hmac-sha256",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = SHA256_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा artpec6_hashalg_context),
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
			.cra_init = artpec6_crypto_ahash_init_hmac_sha256,
			.cra_निकास = artpec6_crypto_ahash_निकास,
		पूर्ण
	पूर्ण,
पूर्ण;

/* Crypto */
अटल काष्ठा skcipher_alg crypto_algos[] = अणु
	/* AES - ECB */
	अणु
		.base = अणु
			.cra_name = "ecb(aes)",
			.cra_driver_name = "artpec6-ecb-aes",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा artpec6_cryptotfm_context),
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.setkey = artpec6_crypto_cipher_set_key,
		.encrypt = artpec6_crypto_encrypt,
		.decrypt = artpec6_crypto_decrypt,
		.init = artpec6_crypto_aes_ecb_init,
		.निकास = artpec6_crypto_aes_निकास,
	पूर्ण,
	/* AES - CTR */
	अणु
		.base = अणु
			.cra_name = "ctr(aes)",
			.cra_driver_name = "artpec6-ctr-aes",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_NEED_FALLBACK,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा artpec6_cryptotfm_context),
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.setkey = artpec6_crypto_cipher_set_key,
		.encrypt = artpec6_crypto_ctr_encrypt,
		.decrypt = artpec6_crypto_ctr_decrypt,
		.init = artpec6_crypto_aes_ctr_init,
		.निकास = artpec6_crypto_aes_ctr_निकास,
	पूर्ण,
	/* AES - CBC */
	अणु
		.base = अणु
			.cra_name = "cbc(aes)",
			.cra_driver_name = "artpec6-cbc-aes",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा artpec6_cryptotfm_context),
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
		.setkey = artpec6_crypto_cipher_set_key,
		.encrypt = artpec6_crypto_encrypt,
		.decrypt = artpec6_crypto_decrypt,
		.init = artpec6_crypto_aes_cbc_init,
		.निकास = artpec6_crypto_aes_निकास
	पूर्ण,
	/* AES - XTS */
	अणु
		.base = अणु
			.cra_name = "xts(aes)",
			.cra_driver_name = "artpec6-xts-aes",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा artpec6_cryptotfm_context),
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = 2*AES_MIN_KEY_SIZE,
		.max_keysize = 2*AES_MAX_KEY_SIZE,
		.ivsize = 16,
		.setkey = artpec6_crypto_xts_set_key,
		.encrypt = artpec6_crypto_encrypt,
		.decrypt = artpec6_crypto_decrypt,
		.init = artpec6_crypto_aes_xts_init,
		.निकास = artpec6_crypto_aes_निकास,
	पूर्ण,
पूर्ण;

अटल काष्ठा aead_alg aead_algos[] = अणु
	अणु
		.init   = artpec6_crypto_aead_init,
		.setkey = artpec6_crypto_aead_set_key,
		.encrypt = artpec6_crypto_aead_encrypt,
		.decrypt = artpec6_crypto_aead_decrypt,
		.ivsize = GCM_AES_IV_SIZE,
		.maxauthsize = AES_BLOCK_SIZE,

		.base = अणु
			.cra_name = "gcm(aes)",
			.cra_driver_name = "artpec-gcm-aes",
			.cra_priority = 300,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY |
				     CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा artpec6_cryptotfm_context),
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
		पूर्ण,
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

काष्ठा dbgfs_u32 अणु
	अक्षर *name;
	mode_t mode;
	u32 *flag;
	अक्षर *desc;
पूर्ण;

अटल काष्ठा dentry *dbgfs_root;

अटल व्योम artpec6_crypto_init_debugfs(व्योम)
अणु
	dbgfs_root = debugfs_create_dir("artpec6_crypto", शून्य);

#अगर_घोषित CONFIG_FAULT_INJECTION
	fault_create_debugfs_attr("fail_status_read", dbgfs_root,
				  &artpec6_crypto_fail_status_पढ़ो);

	fault_create_debugfs_attr("fail_dma_array_full", dbgfs_root,
				  &artpec6_crypto_fail_dma_array_full);
#पूर्ण_अगर
पूर्ण

अटल व्योम artpec6_crypto_मुक्त_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(dbgfs_root);
	dbgfs_root = शून्य;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id artpec6_crypto_of_match[] = अणु
	अणु .compatible = "axis,artpec6-crypto", .data = (व्योम *)ARTPEC6_CRYPTO पूर्ण,
	अणु .compatible = "axis,artpec7-crypto", .data = (व्योम *)ARTPEC7_CRYPTO पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, artpec6_crypto_of_match);

अटल पूर्णांक artpec6_crypto_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	क्रमागत artpec6_crypto_variant variant;
	काष्ठा artpec6_crypto *ac;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *base;
	पूर्णांक irq;
	पूर्णांक err;

	अगर (artpec6_crypto_dev)
		वापस -ENODEV;

	match = of_match_node(artpec6_crypto_of_match, dev->of_node);
	अगर (!match)
		वापस -EINVAL;

	variant = (क्रमागत artpec6_crypto_variant)match->data;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENODEV;

	ac = devm_kzalloc(&pdev->dev, माप(काष्ठा artpec6_crypto),
			  GFP_KERNEL);
	अगर (!ac)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ac);
	ac->variant = variant;

	spin_lock_init(&ac->queue_lock);
	INIT_LIST_HEAD(&ac->queue);
	INIT_LIST_HEAD(&ac->pending);
	समयr_setup(&ac->समयr, artpec6_crypto_समयout, 0);

	ac->base = base;

	ac->dma_cache = kmem_cache_create("artpec6_crypto_dma",
		माप(काष्ठा artpec6_crypto_dma_descriptors),
		64,
		0,
		शून्य);
	अगर (!ac->dma_cache)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_DEBUG_FS
	artpec6_crypto_init_debugfs();
#पूर्ण_अगर

	tasklet_init(&ac->task, artpec6_crypto_task,
		     (अचिन्हित दीर्घ)ac);

	ac->pad_buffer = devm_kzalloc(&pdev->dev, 2 * ARTPEC_CACHE_LINE_MAX,
				      GFP_KERNEL);
	अगर (!ac->pad_buffer)
		वापस -ENOMEM;
	ac->pad_buffer = PTR_ALIGN(ac->pad_buffer, ARTPEC_CACHE_LINE_MAX);

	ac->zero_buffer = devm_kzalloc(&pdev->dev, 2 * ARTPEC_CACHE_LINE_MAX,
				      GFP_KERNEL);
	अगर (!ac->zero_buffer)
		वापस -ENOMEM;
	ac->zero_buffer = PTR_ALIGN(ac->zero_buffer, ARTPEC_CACHE_LINE_MAX);

	err = init_crypto_hw(ac);
	अगर (err)
		जाओ मुक्त_cache;

	err = devm_request_irq(&pdev->dev, irq, artpec6_crypto_irq, 0,
			       "artpec6-crypto", ac);
	अगर (err)
		जाओ disable_hw;

	artpec6_crypto_dev = &pdev->dev;

	err = crypto_रेजिस्टर_ahashes(hash_algos, ARRAY_SIZE(hash_algos));
	अगर (err) अणु
		dev_err(dev, "Failed to register ahashes\n");
		जाओ disable_hw;
	पूर्ण

	err = crypto_रेजिस्टर_skciphers(crypto_algos, ARRAY_SIZE(crypto_algos));
	अगर (err) अणु
		dev_err(dev, "Failed to register ciphers\n");
		जाओ unरेजिस्टर_ahashes;
	पूर्ण

	err = crypto_रेजिस्टर_aeads(aead_algos, ARRAY_SIZE(aead_algos));
	अगर (err) अणु
		dev_err(dev, "Failed to register aeads\n");
		जाओ unरेजिस्टर_algs;
	पूर्ण

	वापस 0;

unरेजिस्टर_algs:
	crypto_unरेजिस्टर_skciphers(crypto_algos, ARRAY_SIZE(crypto_algos));
unरेजिस्टर_ahashes:
	crypto_unरेजिस्टर_ahashes(hash_algos, ARRAY_SIZE(hash_algos));
disable_hw:
	artpec6_crypto_disable_hw(ac);
मुक्त_cache:
	kmem_cache_destroy(ac->dma_cache);
	वापस err;
पूर्ण

अटल पूर्णांक artpec6_crypto_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा artpec6_crypto *ac = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	crypto_unरेजिस्टर_ahashes(hash_algos, ARRAY_SIZE(hash_algos));
	crypto_unरेजिस्टर_skciphers(crypto_algos, ARRAY_SIZE(crypto_algos));
	crypto_unरेजिस्टर_aeads(aead_algos, ARRAY_SIZE(aead_algos));

	tasklet_disable(&ac->task);
	devm_मुक्त_irq(&pdev->dev, irq, ac);
	tasklet_समाप्त(&ac->task);
	del_समयr_sync(&ac->समयr);

	artpec6_crypto_disable_hw(ac);

	kmem_cache_destroy(ac->dma_cache);
#अगर_घोषित CONFIG_DEBUG_FS
	artpec6_crypto_मुक्त_debugfs();
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver artpec6_crypto_driver = अणु
	.probe   = artpec6_crypto_probe,
	.हटाओ  = artpec6_crypto_हटाओ,
	.driver  = अणु
		.name  = "artpec6-crypto",
		.of_match_table = artpec6_crypto_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(artpec6_crypto_driver);

MODULE_AUTHOR("Axis Communications AB");
MODULE_DESCRIPTION("ARTPEC-6 Crypto driver");
MODULE_LICENSE("GPL");
