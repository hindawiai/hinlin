<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Cryptographic API.
 *
 * Support क्रम OMAP AES HW ACCELERATOR defines
 *
 * Copyright (c) 2015 Texas Instruments Incorporated
 */
#अगर_अघोषित __OMAP_AES_H__
#घोषणा __OMAP_AES_H__

#समावेश <crypto/aes.h>
#समावेश <crypto/engine.h>

#घोषणा DST_MAXBURST			4
#घोषणा DMA_MIN				(DST_MAXBURST * माप(u32))

#घोषणा _calc_walked(inout) (dd->inout##_walk.offset - dd->inout##_sg->offset)

/*
 * OMAP TRM gives bitfields as start:end, where start is the higher bit
 * number. For example 7:0
 */
#घोषणा FLD_MASK(start, end)	(((1 << ((start) - (end) + 1)) - 1) << (end))
#घोषणा FLD_VAL(val, start, end) (((val) << (end)) & FLD_MASK(start, end))

#घोषणा AES_REG_KEY(dd, x)		((dd)->pdata->key_ofs - \
						(((x) ^ 0x01) * 0x04))
#घोषणा AES_REG_IV(dd, x)		((dd)->pdata->iv_ofs + ((x) * 0x04))

#घोषणा AES_REG_CTRL(dd)		((dd)->pdata->ctrl_ofs)
#घोषणा AES_REG_CTRL_CONTEXT_READY	BIT(31)
#घोषणा AES_REG_CTRL_CTR_WIDTH_MASK	GENMASK(8, 7)
#घोषणा AES_REG_CTRL_CTR_WIDTH_32	0
#घोषणा AES_REG_CTRL_CTR_WIDTH_64	BIT(7)
#घोषणा AES_REG_CTRL_CTR_WIDTH_96	BIT(8)
#घोषणा AES_REG_CTRL_CTR_WIDTH_128	GENMASK(8, 7)
#घोषणा AES_REG_CTRL_GCM		GENMASK(17, 16)
#घोषणा AES_REG_CTRL_CTR		BIT(6)
#घोषणा AES_REG_CTRL_CBC		BIT(5)
#घोषणा AES_REG_CTRL_KEY_SIZE		GENMASK(4, 3)
#घोषणा AES_REG_CTRL_सूचीECTION		BIT(2)
#घोषणा AES_REG_CTRL_INPUT_READY	BIT(1)
#घोषणा AES_REG_CTRL_OUTPUT_READY	BIT(0)
#घोषणा AES_REG_CTRL_MASK		GENMASK(24, 2)

#घोषणा AES_REG_C_LEN_0			0x54
#घोषणा AES_REG_C_LEN_1			0x58
#घोषणा AES_REG_A_LEN			0x5C

#घोषणा AES_REG_DATA_N(dd, x)		((dd)->pdata->data_ofs + ((x) * 0x04))
#घोषणा AES_REG_TAG_N(dd, x)		(0x70 + ((x) * 0x04))

#घोषणा AES_REG_REV(dd)			((dd)->pdata->rev_ofs)

#घोषणा AES_REG_MASK(dd)		((dd)->pdata->mask_ofs)
#घोषणा AES_REG_MASK_SIDLE		BIT(6)
#घोषणा AES_REG_MASK_START		BIT(5)
#घोषणा AES_REG_MASK_DMA_OUT_EN		BIT(3)
#घोषणा AES_REG_MASK_DMA_IN_EN		BIT(2)
#घोषणा AES_REG_MASK_SOFTRESET		BIT(1)
#घोषणा AES_REG_AUTOIDLE		BIT(0)

#घोषणा AES_REG_LENGTH_N(x)		(0x54 + ((x) * 0x04))

#घोषणा AES_REG_IRQ_STATUS(dd)         ((dd)->pdata->irq_status_ofs)
#घोषणा AES_REG_IRQ_ENABLE(dd)         ((dd)->pdata->irq_enable_ofs)
#घोषणा AES_REG_IRQ_DATA_IN            BIT(1)
#घोषणा AES_REG_IRQ_DATA_OUT           BIT(2)
#घोषणा DEFAULT_TIMEOUT		(5 * HZ)

#घोषणा DEFAULT_AUTOSUSPEND_DELAY	1000

#घोषणा FLAGS_MODE_MASK		0x001f
#घोषणा FLAGS_ENCRYPT		BIT(0)
#घोषणा FLAGS_CBC		BIT(1)
#घोषणा FLAGS_CTR		BIT(2)
#घोषणा FLAGS_GCM		BIT(3)
#घोषणा FLAGS_RFC4106_GCM	BIT(4)

#घोषणा FLAGS_INIT		BIT(5)
#घोषणा FLAGS_FAST		BIT(6)

#घोषणा FLAGS_IN_DATA_ST_SHIFT	8
#घोषणा FLAGS_OUT_DATA_ST_SHIFT	10
#घोषणा FLAGS_ASSOC_DATA_ST_SHIFT	12

#घोषणा AES_BLOCK_WORDS		(AES_BLOCK_SIZE >> 2)

काष्ठा omap_aes_gcm_result अणु
	काष्ठा completion completion;
	पूर्णांक err;
पूर्ण;

काष्ठा omap_aes_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	पूर्णांक		keylen;
	u32		key[AES_KEYSIZE_256 / माप(u32)];
	u8		nonce[4];
	काष्ठा crypto_skcipher	*fallback;
पूर्ण;

काष्ठा omap_aes_gcm_ctx अणु
	काष्ठा omap_aes_ctx	octx;
	काष्ठा crypto_aes_ctx	actx;
पूर्ण;

काष्ठा omap_aes_reqctx अणु
	काष्ठा omap_aes_dev *dd;
	अचिन्हित दीर्घ mode;
	u8 iv[AES_BLOCK_SIZE];
	u32 auth_tag[AES_BLOCK_SIZE / माप(u32)];
	काष्ठा skcipher_request fallback_req;	// keep at the end
पूर्ण;

#घोषणा OMAP_AES_QUEUE_LENGTH	1
#घोषणा OMAP_AES_CACHE_SIZE	0

काष्ठा omap_aes_algs_info अणु
	काष्ठा skcipher_alg	*algs_list;
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		रेजिस्टरed;
पूर्ण;

काष्ठा omap_aes_aead_algs अणु
	काष्ठा aead_alg	*algs_list;
	अचिन्हित पूर्णांक	size;
	अचिन्हित पूर्णांक	रेजिस्टरed;
पूर्ण;

काष्ठा omap_aes_pdata अणु
	काष्ठा omap_aes_algs_info	*algs_info;
	अचिन्हित पूर्णांक	algs_info_size;
	काष्ठा omap_aes_aead_algs	*aead_algs_info;

	व्योम		(*trigger)(काष्ठा omap_aes_dev *dd, पूर्णांक length);

	u32		key_ofs;
	u32		iv_ofs;
	u32		ctrl_ofs;
	u32		data_ofs;
	u32		rev_ofs;
	u32		mask_ofs;
	u32             irq_enable_ofs;
	u32             irq_status_ofs;

	u32		dma_enable_in;
	u32		dma_enable_out;
	u32		dma_start;

	u32		major_mask;
	u32		major_shअगरt;
	u32		minor_mask;
	u32		minor_shअगरt;
पूर्ण;

काष्ठा omap_aes_dev अणु
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		phys_base;
	व्योम __iomem		*io_base;
	काष्ठा omap_aes_ctx	*ctx;
	काष्ठा device		*dev;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			err;

	काष्ठा tasklet_काष्ठा	करोne_task;
	काष्ठा aead_queue	aead_queue;
	spinlock_t		lock;

	काष्ठा skcipher_request		*req;
	काष्ठा aead_request		*aead_req;
	काष्ठा crypto_engine		*engine;

	/*
	 * total is used by PIO mode क्रम book keeping so पूर्णांकroduce
	 * variable total_save as need it to calc page_order
	 */
	माप_प्रकार				total;
	माप_प्रकार				total_save;
	माप_प्रकार				assoc_len;
	माप_प्रकार				authsize;

	काष्ठा scatterlist		*in_sg;
	काष्ठा scatterlist		*out_sg;

	/* Buffers क्रम copying क्रम unaligned हालs */
	काष्ठा scatterlist		in_sgl[2];
	काष्ठा scatterlist		out_sgl;
	काष्ठा scatterlist		*orig_out;

	काष्ठा scatter_walk		in_walk;
	काष्ठा scatter_walk		out_walk;
	काष्ठा dma_chan		*dma_lch_in;
	काष्ठा dma_chan		*dma_lch_out;
	पूर्णांक			in_sg_len;
	पूर्णांक			out_sg_len;
	पूर्णांक			pio_only;
	स्थिर काष्ठा omap_aes_pdata	*pdata;
पूर्ण;

u32 omap_aes_पढ़ो(काष्ठा omap_aes_dev *dd, u32 offset);
व्योम omap_aes_ग_लिखो(काष्ठा omap_aes_dev *dd, u32 offset, u32 value);
काष्ठा omap_aes_dev *omap_aes_find_dev(काष्ठा omap_aes_reqctx *rctx);
पूर्णांक omap_aes_gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen);
पूर्णांक omap_aes_4106gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen);
पूर्णांक omap_aes_gcm_encrypt(काष्ठा aead_request *req);
पूर्णांक omap_aes_gcm_decrypt(काष्ठा aead_request *req);
पूर्णांक omap_aes_gcm_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize);
पूर्णांक omap_aes_4106gcm_encrypt(काष्ठा aead_request *req);
पूर्णांक omap_aes_4106gcm_decrypt(काष्ठा aead_request *req);
पूर्णांक omap_aes_4106gcm_setauthsize(काष्ठा crypto_aead *parent,
				 अचिन्हित पूर्णांक authsize);
पूर्णांक omap_aes_gcm_cra_init(काष्ठा crypto_aead *tfm);
पूर्णांक omap_aes_ग_लिखो_ctrl(काष्ठा omap_aes_dev *dd);
पूर्णांक omap_aes_crypt_dma_start(काष्ठा omap_aes_dev *dd);
पूर्णांक omap_aes_crypt_dma_stop(काष्ठा omap_aes_dev *dd);
व्योम omap_aes_gcm_dma_out_callback(व्योम *data);
व्योम omap_aes_clear_copy_flags(काष्ठा omap_aes_dev *dd);

#पूर्ण_अगर
