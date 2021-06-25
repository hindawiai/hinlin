<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cryptographic API.
 *
 * Support क्रम ATMEL AES HW acceleration.
 *
 * Copyright (c) 2012 Eukrथऊa Electromatique - ATMEL
 * Author: Nicolas Royer <nicolas@eukrea.com>
 *
 * Some ideas are from omap-aes.c driver.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/xts.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश "atmel-aes-regs.h"
#समावेश "atmel-authenc.h"

#घोषणा ATMEL_AES_PRIORITY	300

#घोषणा ATMEL_AES_BUFFER_ORDER	2
#घोषणा ATMEL_AES_BUFFER_SIZE	(PAGE_SIZE << ATMEL_AES_BUFFER_ORDER)

#घोषणा CFB8_BLOCK_SIZE		1
#घोषणा CFB16_BLOCK_SIZE	2
#घोषणा CFB32_BLOCK_SIZE	4
#घोषणा CFB64_BLOCK_SIZE	8

#घोषणा SIZE_IN_WORDS(x)	((x) >> 2)

/* AES flags */
/* Reserve bits [18:16] [14:12] [1:0] क्रम mode (same as क्रम AES_MR) */
#घोषणा AES_FLAGS_ENCRYPT	AES_MR_CYPHER_ENC
#घोषणा AES_FLAGS_GTAGEN	AES_MR_GTAGEN
#घोषणा AES_FLAGS_OPMODE_MASK	(AES_MR_OPMOD_MASK | AES_MR_CFBS_MASK)
#घोषणा AES_FLAGS_ECB		AES_MR_OPMOD_ECB
#घोषणा AES_FLAGS_CBC		AES_MR_OPMOD_CBC
#घोषणा AES_FLAGS_OFB		AES_MR_OPMOD_OFB
#घोषणा AES_FLAGS_CFB128	(AES_MR_OPMOD_CFB | AES_MR_CFBS_128b)
#घोषणा AES_FLAGS_CFB64		(AES_MR_OPMOD_CFB | AES_MR_CFBS_64b)
#घोषणा AES_FLAGS_CFB32		(AES_MR_OPMOD_CFB | AES_MR_CFBS_32b)
#घोषणा AES_FLAGS_CFB16		(AES_MR_OPMOD_CFB | AES_MR_CFBS_16b)
#घोषणा AES_FLAGS_CFB8		(AES_MR_OPMOD_CFB | AES_MR_CFBS_8b)
#घोषणा AES_FLAGS_CTR		AES_MR_OPMOD_CTR
#घोषणा AES_FLAGS_GCM		AES_MR_OPMOD_GCM
#घोषणा AES_FLAGS_XTS		AES_MR_OPMOD_XTS

#घोषणा AES_FLAGS_MODE_MASK	(AES_FLAGS_OPMODE_MASK |	\
				 AES_FLAGS_ENCRYPT |		\
				 AES_FLAGS_GTAGEN)

#घोषणा AES_FLAGS_BUSY		BIT(3)
#घोषणा AES_FLAGS_DUMP_REG	BIT(4)
#घोषणा AES_FLAGS_OWN_SHA	BIT(5)

#घोषणा AES_FLAGS_PERSISTENT	AES_FLAGS_BUSY

#घोषणा ATMEL_AES_QUEUE_LENGTH	50

#घोषणा ATMEL_AES_DMA_THRESHOLD		256


काष्ठा aपंचांगel_aes_caps अणु
	bool			has_dualbuff;
	bool			has_cfb64;
	bool			has_gcm;
	bool			has_xts;
	bool			has_authenc;
	u32			max_burst_size;
पूर्ण;

काष्ठा aपंचांगel_aes_dev;


प्रकार पूर्णांक (*aपंचांगel_aes_fn_t)(काष्ठा aपंचांगel_aes_dev *);


काष्ठा aपंचांगel_aes_base_ctx अणु
	काष्ठा aपंचांगel_aes_dev	*dd;
	aपंचांगel_aes_fn_t		start;
	पूर्णांक			keylen;
	u32			key[AES_KEYSIZE_256 / माप(u32)];
	u16			block_size;
	bool			is_aead;
पूर्ण;

काष्ठा aपंचांगel_aes_ctx अणु
	काष्ठा aपंचांगel_aes_base_ctx	base;
पूर्ण;

काष्ठा aपंचांगel_aes_ctr_ctx अणु
	काष्ठा aपंचांगel_aes_base_ctx	base;

	__be32			iv[AES_BLOCK_SIZE / माप(u32)];
	माप_प्रकार			offset;
	काष्ठा scatterlist	src[2];
	काष्ठा scatterlist	dst[2];
	u32			blocks;
पूर्ण;

काष्ठा aपंचांगel_aes_gcm_ctx अणु
	काष्ठा aपंचांगel_aes_base_ctx	base;

	काष्ठा scatterlist	src[2];
	काष्ठा scatterlist	dst[2];

	__be32			j0[AES_BLOCK_SIZE / माप(u32)];
	u32			tag[AES_BLOCK_SIZE / माप(u32)];
	__be32			ghash[AES_BLOCK_SIZE / माप(u32)];
	माप_प्रकार			textlen;

	स्थिर __be32		*ghash_in;
	__be32			*ghash_out;
	aपंचांगel_aes_fn_t		ghash_resume;
पूर्ण;

काष्ठा aपंचांगel_aes_xts_ctx अणु
	काष्ठा aपंचांगel_aes_base_ctx	base;

	u32			key2[AES_KEYSIZE_256 / माप(u32)];
पूर्ण;

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
काष्ठा aपंचांगel_aes_authenc_ctx अणु
	काष्ठा aपंचांगel_aes_base_ctx	base;
	काष्ठा aपंचांगel_sha_authenc_ctx	*auth;
पूर्ण;
#पूर्ण_अगर

काष्ठा aपंचांगel_aes_reqctx अणु
	अचिन्हित दीर्घ		mode;
	u8			lastc[AES_BLOCK_SIZE];
पूर्ण;

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
काष्ठा aपंचांगel_aes_authenc_reqctx अणु
	काष्ठा aपंचांगel_aes_reqctx	base;

	काष्ठा scatterlist	src[2];
	काष्ठा scatterlist	dst[2];
	माप_प्रकार			textlen;
	u32			digest[SHA512_DIGEST_SIZE / माप(u32)];

	/* auth_req MUST be place last. */
	काष्ठा ahash_request	auth_req;
पूर्ण;
#पूर्ण_अगर

काष्ठा aपंचांगel_aes_dma अणु
	काष्ठा dma_chan		*chan;
	काष्ठा scatterlist	*sg;
	पूर्णांक			nents;
	अचिन्हित पूर्णांक		reमुख्यder;
	अचिन्हित पूर्णांक		sg_len;
पूर्ण;

काष्ठा aपंचांगel_aes_dev अणु
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		phys_base;
	व्योम __iomem		*io_base;

	काष्ठा crypto_async_request	*areq;
	काष्ठा aपंचांगel_aes_base_ctx	*ctx;

	bool			is_async;
	aपंचांगel_aes_fn_t		resume;
	aपंचांगel_aes_fn_t		cpu_transfer_complete;

	काष्ठा device		*dev;
	काष्ठा clk		*iclk;
	पूर्णांक			irq;

	अचिन्हित दीर्घ		flags;

	spinlock_t		lock;
	काष्ठा crypto_queue	queue;

	काष्ठा tasklet_काष्ठा	करोne_task;
	काष्ठा tasklet_काष्ठा	queue_task;

	माप_प्रकार			total;
	माप_प्रकार			datalen;
	u32			*data;

	काष्ठा aपंचांगel_aes_dma	src;
	काष्ठा aपंचांगel_aes_dma	dst;

	माप_प्रकार			buflen;
	व्योम			*buf;
	काष्ठा scatterlist	aligned_sg;
	काष्ठा scatterlist	*real_dst;

	काष्ठा aपंचांगel_aes_caps	caps;

	u32			hw_version;
पूर्ण;

काष्ठा aपंचांगel_aes_drv अणु
	काष्ठा list_head	dev_list;
	spinlock_t		lock;
पूर्ण;

अटल काष्ठा aपंचांगel_aes_drv aपंचांगel_aes = अणु
	.dev_list = LIST_HEAD_INIT(aपंचांगel_aes.dev_list),
	.lock = __SPIN_LOCK_UNLOCKED(aपंचांगel_aes.lock),
पूर्ण;

#अगर_घोषित VERBOSE_DEBUG
अटल स्थिर अक्षर *aपंचांगel_aes_reg_name(u32 offset, अक्षर *पंचांगp, माप_प्रकार sz)
अणु
	चयन (offset) अणु
	हाल AES_CR:
		वापस "CR";

	हाल AES_MR:
		वापस "MR";

	हाल AES_ISR:
		वापस "ISR";

	हाल AES_IMR:
		वापस "IMR";

	हाल AES_IER:
		वापस "IER";

	हाल AES_IDR:
		वापस "IDR";

	हाल AES_KEYWR(0):
	हाल AES_KEYWR(1):
	हाल AES_KEYWR(2):
	हाल AES_KEYWR(3):
	हाल AES_KEYWR(4):
	हाल AES_KEYWR(5):
	हाल AES_KEYWR(6):
	हाल AES_KEYWR(7):
		snम_लिखो(पंचांगp, sz, "KEYWR[%u]", (offset - AES_KEYWR(0)) >> 2);
		अवरोध;

	हाल AES_IDATAR(0):
	हाल AES_IDATAR(1):
	हाल AES_IDATAR(2):
	हाल AES_IDATAR(3):
		snम_लिखो(पंचांगp, sz, "IDATAR[%u]", (offset - AES_IDATAR(0)) >> 2);
		अवरोध;

	हाल AES_ODATAR(0):
	हाल AES_ODATAR(1):
	हाल AES_ODATAR(2):
	हाल AES_ODATAR(3):
		snम_लिखो(पंचांगp, sz, "ODATAR[%u]", (offset - AES_ODATAR(0)) >> 2);
		अवरोध;

	हाल AES_IVR(0):
	हाल AES_IVR(1):
	हाल AES_IVR(2):
	हाल AES_IVR(3):
		snम_लिखो(पंचांगp, sz, "IVR[%u]", (offset - AES_IVR(0)) >> 2);
		अवरोध;

	हाल AES_AADLENR:
		वापस "AADLENR";

	हाल AES_CLENR:
		वापस "CLENR";

	हाल AES_GHASHR(0):
	हाल AES_GHASHR(1):
	हाल AES_GHASHR(2):
	हाल AES_GHASHR(3):
		snम_लिखो(पंचांगp, sz, "GHASHR[%u]", (offset - AES_GHASHR(0)) >> 2);
		अवरोध;

	हाल AES_TAGR(0):
	हाल AES_TAGR(1):
	हाल AES_TAGR(2):
	हाल AES_TAGR(3):
		snम_लिखो(पंचांगp, sz, "TAGR[%u]", (offset - AES_TAGR(0)) >> 2);
		अवरोध;

	हाल AES_CTRR:
		वापस "CTRR";

	हाल AES_GCMHR(0):
	हाल AES_GCMHR(1):
	हाल AES_GCMHR(2):
	हाल AES_GCMHR(3):
		snम_लिखो(पंचांगp, sz, "GCMHR[%u]", (offset - AES_GCMHR(0)) >> 2);
		अवरोध;

	हाल AES_EMR:
		वापस "EMR";

	हाल AES_TWR(0):
	हाल AES_TWR(1):
	हाल AES_TWR(2):
	हाल AES_TWR(3):
		snम_लिखो(पंचांगp, sz, "TWR[%u]", (offset - AES_TWR(0)) >> 2);
		अवरोध;

	हाल AES_ALPHAR(0):
	हाल AES_ALPHAR(1):
	हाल AES_ALPHAR(2):
	हाल AES_ALPHAR(3):
		snम_लिखो(पंचांगp, sz, "ALPHAR[%u]", (offset - AES_ALPHAR(0)) >> 2);
		अवरोध;

	शेष:
		snम_लिखो(पंचांगp, sz, "0x%02x", offset);
		अवरोध;
	पूर्ण

	वापस पंचांगp;
पूर्ण
#पूर्ण_अगर /* VERBOSE_DEBUG */

/* Shared functions */

अटल अंतरभूत u32 aपंचांगel_aes_पढ़ो(काष्ठा aपंचांगel_aes_dev *dd, u32 offset)
अणु
	u32 value = पढ़ोl_relaxed(dd->io_base + offset);

#अगर_घोषित VERBOSE_DEBUG
	अगर (dd->flags & AES_FLAGS_DUMP_REG) अणु
		अक्षर पंचांगp[16];

		dev_vdbg(dd->dev, "read 0x%08x from %s\n", value,
			 aपंचांगel_aes_reg_name(offset, पंचांगp, माप(पंचांगp)));
	पूर्ण
#पूर्ण_अगर /* VERBOSE_DEBUG */

	वापस value;
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_aes_ग_लिखो(काष्ठा aपंचांगel_aes_dev *dd,
					u32 offset, u32 value)
अणु
#अगर_घोषित VERBOSE_DEBUG
	अगर (dd->flags & AES_FLAGS_DUMP_REG) अणु
		अक्षर पंचांगp[16];

		dev_vdbg(dd->dev, "write 0x%08x into %s\n", value,
			 aपंचांगel_aes_reg_name(offset, पंचांगp, माप(पंचांगp)));
	पूर्ण
#पूर्ण_अगर /* VERBOSE_DEBUG */

	ग_लिखोl_relaxed(value, dd->io_base + offset);
पूर्ण

अटल व्योम aपंचांगel_aes_पढ़ो_n(काष्ठा aपंचांगel_aes_dev *dd, u32 offset,
					u32 *value, पूर्णांक count)
अणु
	क्रम (; count--; value++, offset += 4)
		*value = aपंचांगel_aes_पढ़ो(dd, offset);
पूर्ण

अटल व्योम aपंचांगel_aes_ग_लिखो_n(काष्ठा aपंचांगel_aes_dev *dd, u32 offset,
			      स्थिर u32 *value, पूर्णांक count)
अणु
	क्रम (; count--; value++, offset += 4)
		aपंचांगel_aes_ग_लिखो(dd, offset, *value);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_aes_पढ़ो_block(काष्ठा aपंचांगel_aes_dev *dd, u32 offset,
					व्योम *value)
अणु
	aपंचांगel_aes_पढ़ो_n(dd, offset, value, SIZE_IN_WORDS(AES_BLOCK_SIZE));
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_aes_ग_लिखो_block(काष्ठा aपंचांगel_aes_dev *dd, u32 offset,
					 स्थिर व्योम *value)
अणु
	aपंचांगel_aes_ग_लिखो_n(dd, offset, value, SIZE_IN_WORDS(AES_BLOCK_SIZE));
पूर्ण

अटल अंतरभूत पूर्णांक aपंचांगel_aes_रुको_क्रम_data_पढ़ोy(काष्ठा aपंचांगel_aes_dev *dd,
						aपंचांगel_aes_fn_t resume)
अणु
	u32 isr = aपंचांगel_aes_पढ़ो(dd, AES_ISR);

	अगर (unlikely(isr & AES_INT_DATARDY))
		वापस resume(dd);

	dd->resume = resume;
	aपंचांगel_aes_ग_लिखो(dd, AES_IER, AES_INT_DATARDY);
	वापस -EINPROGRESS;
पूर्ण

अटल अंतरभूत माप_प्रकार aपंचांगel_aes_padlen(माप_प्रकार len, माप_प्रकार block_size)
अणु
	len &= block_size - 1;
	वापस len ? block_size - len : 0;
पूर्ण

अटल काष्ठा aपंचांगel_aes_dev *aपंचांगel_aes_find_dev(काष्ठा aपंचांगel_aes_base_ctx *ctx)
अणु
	काष्ठा aपंचांगel_aes_dev *aes_dd = शून्य;
	काष्ठा aपंचांगel_aes_dev *पंचांगp;

	spin_lock_bh(&aपंचांगel_aes.lock);
	अगर (!ctx->dd) अणु
		list_क्रम_each_entry(पंचांगp, &aपंचांगel_aes.dev_list, list) अणु
			aes_dd = पंचांगp;
			अवरोध;
		पूर्ण
		ctx->dd = aes_dd;
	पूर्ण अन्यथा अणु
		aes_dd = ctx->dd;
	पूर्ण

	spin_unlock_bh(&aपंचांगel_aes.lock);

	वापस aes_dd;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_hw_init(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	पूर्णांक err;

	err = clk_enable(dd->iclk);
	अगर (err)
		वापस err;

	aपंचांगel_aes_ग_लिखो(dd, AES_CR, AES_CR_SWRST);
	aपंचांगel_aes_ग_लिखो(dd, AES_MR, 0xE << AES_MR_CKEY_OFFSET);

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक aपंचांगel_aes_get_version(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	वापस aपंचांगel_aes_पढ़ो(dd, AES_HW_VERSION) & 0x00000fff;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_hw_version_init(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	पूर्णांक err;

	err = aपंचांगel_aes_hw_init(dd);
	अगर (err)
		वापस err;

	dd->hw_version = aपंचांगel_aes_get_version(dd);

	dev_info(dd->dev, "version: 0x%x\n", dd->hw_version);

	clk_disable(dd->iclk);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_aes_set_mode(काष्ठा aपंचांगel_aes_dev *dd,
				      स्थिर काष्ठा aपंचांगel_aes_reqctx *rctx)
अणु
	/* Clear all but persistent flags and set request flags. */
	dd->flags = (dd->flags & AES_FLAGS_PERSISTENT) | rctx->mode;
पूर्ण

अटल अंतरभूत bool aपंचांगel_aes_is_encrypt(स्थिर काष्ठा aपंचांगel_aes_dev *dd)
अणु
	वापस (dd->flags & AES_FLAGS_ENCRYPT);
पूर्ण

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
अटल व्योम aपंचांगel_aes_authenc_complete(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err);
#पूर्ण_अगर

अटल व्योम aपंचांगel_aes_set_iv_as_last_ciphertext_block(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

	अगर (req->cryptlen < ivsize)
		वापस;

	अगर (rctx->mode & AES_FLAGS_ENCRYPT) अणु
		scatterwalk_map_and_copy(req->iv, req->dst,
					 req->cryptlen - ivsize, ivsize, 0);
	पूर्ण अन्यथा अणु
		अगर (req->src == req->dst)
			स_नकल(req->iv, rctx->lastc, ivsize);
		अन्यथा
			scatterwalk_map_and_copy(req->iv, req->src,
						 req->cryptlen - ivsize,
						 ivsize, 0);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा aपंचांगel_aes_ctr_ctx *
aपंचांगel_aes_ctr_ctx_cast(काष्ठा aपंचांगel_aes_base_ctx *ctx)
अणु
	वापस container_of(ctx, काष्ठा aपंचांगel_aes_ctr_ctx, base);
पूर्ण

अटल व्योम aपंचांगel_aes_ctr_update_req_iv(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_ctr_ctx *ctx = aपंचांगel_aes_ctr_ctx_cast(dd->ctx);
	काष्ठा skcipher_request *req = skcipher_request_cast(dd->areq);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);
	पूर्णांक i;

	/*
	 * The CTR transfer works in fragments of data of maximum 1 MByte
	 * because of the 16 bit CTR counter embedded in the IP. When reaching
	 * here, ctx->blocks contains the number of blocks of the last fragment
	 * processed, there is no need to explicit cast it to u16.
	 */
	क्रम (i = 0; i < ctx->blocks; i++)
		crypto_inc((u8 *)ctx->iv, AES_BLOCK_SIZE);

	स_नकल(req->iv, ctx->iv, ivsize);
पूर्ण

अटल अंतरभूत पूर्णांक aपंचांगel_aes_complete(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_reqctx *rctx = skcipher_request_ctx(req);

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
	अगर (dd->ctx->is_aead)
		aपंचांगel_aes_authenc_complete(dd, err);
#पूर्ण_अगर

	clk_disable(dd->iclk);
	dd->flags &= ~AES_FLAGS_BUSY;

	अगर (!err && !dd->ctx->is_aead &&
	    (rctx->mode & AES_FLAGS_OPMODE_MASK) != AES_FLAGS_ECB) अणु
		अगर ((rctx->mode & AES_FLAGS_OPMODE_MASK) != AES_FLAGS_CTR)
			aपंचांगel_aes_set_iv_as_last_ciphertext_block(dd);
		अन्यथा
			aपंचांगel_aes_ctr_update_req_iv(dd);
	पूर्ण

	अगर (dd->is_async)
		dd->areq->complete(dd->areq, err);

	tasklet_schedule(&dd->queue_task);

	वापस err;
पूर्ण

अटल व्योम aपंचांगel_aes_ग_लिखो_ctrl_key(काष्ठा aपंचांगel_aes_dev *dd, bool use_dma,
				     स्थिर __be32 *iv, स्थिर u32 *key, पूर्णांक keylen)
अणु
	u32 valmr = 0;

	/* MR रेजिस्टर must be set beक्रमe IV रेजिस्टरs */
	अगर (keylen == AES_KEYSIZE_128)
		valmr |= AES_MR_KEYSIZE_128;
	अन्यथा अगर (keylen == AES_KEYSIZE_192)
		valmr |= AES_MR_KEYSIZE_192;
	अन्यथा
		valmr |= AES_MR_KEYSIZE_256;

	valmr |= dd->flags & AES_FLAGS_MODE_MASK;

	अगर (use_dma) अणु
		valmr |= AES_MR_SMOD_IDATAR0;
		अगर (dd->caps.has_dualbuff)
			valmr |= AES_MR_DUALBUFF;
	पूर्ण अन्यथा अणु
		valmr |= AES_MR_SMOD_AUTO;
	पूर्ण

	aपंचांगel_aes_ग_लिखो(dd, AES_MR, valmr);

	aपंचांगel_aes_ग_लिखो_n(dd, AES_KEYWR(0), key, SIZE_IN_WORDS(keylen));

	अगर (iv && (valmr & AES_MR_OPMOD_MASK) != AES_MR_OPMOD_ECB)
		aपंचांगel_aes_ग_लिखो_block(dd, AES_IVR(0), iv);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_aes_ग_लिखो_ctrl(काष्ठा aपंचांगel_aes_dev *dd, bool use_dma,
					स्थिर __be32 *iv)

अणु
	aपंचांगel_aes_ग_लिखो_ctrl_key(dd, use_dma, iv,
				 dd->ctx->key, dd->ctx->keylen);
पूर्ण

/* CPU transfer */

अटल पूर्णांक aपंचांगel_aes_cpu_transfer(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	पूर्णांक err = 0;
	u32 isr;

	क्रम (;;) अणु
		aपंचांगel_aes_पढ़ो_block(dd, AES_ODATAR(0), dd->data);
		dd->data += 4;
		dd->datalen -= AES_BLOCK_SIZE;

		अगर (dd->datalen < AES_BLOCK_SIZE)
			अवरोध;

		aपंचांगel_aes_ग_लिखो_block(dd, AES_IDATAR(0), dd->data);

		isr = aपंचांगel_aes_पढ़ो(dd, AES_ISR);
		अगर (!(isr & AES_INT_DATARDY)) अणु
			dd->resume = aपंचांगel_aes_cpu_transfer;
			aपंचांगel_aes_ग_लिखो(dd, AES_IER, AES_INT_DATARDY);
			वापस -EINPROGRESS;
		पूर्ण
	पूर्ण

	अगर (!sg_copy_from_buffer(dd->real_dst, sg_nents(dd->real_dst),
				 dd->buf, dd->total))
		err = -EINVAL;

	अगर (err)
		वापस aपंचांगel_aes_complete(dd, err);

	वापस dd->cpu_transfer_complete(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cpu_start(काष्ठा aपंचांगel_aes_dev *dd,
			       काष्ठा scatterlist *src,
			       काष्ठा scatterlist *dst,
			       माप_प्रकार len,
			       aपंचांगel_aes_fn_t resume)
अणु
	माप_प्रकार padlen = aपंचांगel_aes_padlen(len, AES_BLOCK_SIZE);

	अगर (unlikely(len == 0))
		वापस -EINVAL;

	sg_copy_to_buffer(src, sg_nents(src), dd->buf, len);

	dd->total = len;
	dd->real_dst = dst;
	dd->cpu_transfer_complete = resume;
	dd->datalen = len + padlen;
	dd->data = (u32 *)dd->buf;
	aपंचांगel_aes_ग_लिखो_block(dd, AES_IDATAR(0), dd->data);
	वापस aपंचांगel_aes_रुको_क्रम_data_पढ़ोy(dd, aपंचांगel_aes_cpu_transfer);
पूर्ण


/* DMA transfer */

अटल व्योम aपंचांगel_aes_dma_callback(व्योम *data);

अटल bool aपंचांगel_aes_check_aligned(काष्ठा aपंचांगel_aes_dev *dd,
				    काष्ठा scatterlist *sg,
				    माप_प्रकार len,
				    काष्ठा aपंचांगel_aes_dma *dma)
अणु
	पूर्णांक nents;

	अगर (!IS_ALIGNED(len, dd->ctx->block_size))
		वापस false;

	क्रम (nents = 0; sg; sg = sg_next(sg), ++nents) अणु
		अगर (!IS_ALIGNED(sg->offset, माप(u32)))
			वापस false;

		अगर (len <= sg->length) अणु
			अगर (!IS_ALIGNED(len, dd->ctx->block_size))
				वापस false;

			dma->nents = nents+1;
			dma->reमुख्यder = sg->length - len;
			sg->length = len;
			वापस true;
		पूर्ण

		अगर (!IS_ALIGNED(sg->length, dd->ctx->block_size))
			वापस false;

		len -= sg->length;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_aes_restore_sg(स्थिर काष्ठा aपंचांगel_aes_dma *dma)
अणु
	काष्ठा scatterlist *sg = dma->sg;
	पूर्णांक nents = dma->nents;

	अगर (!dma->reमुख्यder)
		वापस;

	जबतक (--nents > 0 && sg)
		sg = sg_next(sg);

	अगर (!sg)
		वापस;

	sg->length += dma->reमुख्यder;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_map(काष्ठा aपंचांगel_aes_dev *dd,
			 काष्ठा scatterlist *src,
			 काष्ठा scatterlist *dst,
			 माप_प्रकार len)
अणु
	bool src_aligned, dst_aligned;
	माप_प्रकार padlen;

	dd->total = len;
	dd->src.sg = src;
	dd->dst.sg = dst;
	dd->real_dst = dst;

	src_aligned = aपंचांगel_aes_check_aligned(dd, src, len, &dd->src);
	अगर (src == dst)
		dst_aligned = src_aligned;
	अन्यथा
		dst_aligned = aपंचांगel_aes_check_aligned(dd, dst, len, &dd->dst);
	अगर (!src_aligned || !dst_aligned) अणु
		padlen = aपंचांगel_aes_padlen(len, dd->ctx->block_size);

		अगर (dd->buflen < len + padlen)
			वापस -ENOMEM;

		अगर (!src_aligned) अणु
			sg_copy_to_buffer(src, sg_nents(src), dd->buf, len);
			dd->src.sg = &dd->aligned_sg;
			dd->src.nents = 1;
			dd->src.reमुख्यder = 0;
		पूर्ण

		अगर (!dst_aligned) अणु
			dd->dst.sg = &dd->aligned_sg;
			dd->dst.nents = 1;
			dd->dst.reमुख्यder = 0;
		पूर्ण

		sg_init_table(&dd->aligned_sg, 1);
		sg_set_buf(&dd->aligned_sg, dd->buf, len + padlen);
	पूर्ण

	अगर (dd->src.sg == dd->dst.sg) अणु
		dd->src.sg_len = dma_map_sg(dd->dev, dd->src.sg, dd->src.nents,
					    DMA_BIसूचीECTIONAL);
		dd->dst.sg_len = dd->src.sg_len;
		अगर (!dd->src.sg_len)
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		dd->src.sg_len = dma_map_sg(dd->dev, dd->src.sg, dd->src.nents,
					    DMA_TO_DEVICE);
		अगर (!dd->src.sg_len)
			वापस -EFAULT;

		dd->dst.sg_len = dma_map_sg(dd->dev, dd->dst.sg, dd->dst.nents,
					    DMA_FROM_DEVICE);
		अगर (!dd->dst.sg_len) अणु
			dma_unmap_sg(dd->dev, dd->src.sg, dd->src.nents,
				     DMA_TO_DEVICE);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_aes_unmap(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	अगर (dd->src.sg == dd->dst.sg) अणु
		dma_unmap_sg(dd->dev, dd->src.sg, dd->src.nents,
			     DMA_BIसूचीECTIONAL);

		अगर (dd->src.sg != &dd->aligned_sg)
			aपंचांगel_aes_restore_sg(&dd->src);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(dd->dev, dd->dst.sg, dd->dst.nents,
			     DMA_FROM_DEVICE);

		अगर (dd->dst.sg != &dd->aligned_sg)
			aपंचांगel_aes_restore_sg(&dd->dst);

		dma_unmap_sg(dd->dev, dd->src.sg, dd->src.nents,
			     DMA_TO_DEVICE);

		अगर (dd->src.sg != &dd->aligned_sg)
			aपंचांगel_aes_restore_sg(&dd->src);
	पूर्ण

	अगर (dd->dst.sg == &dd->aligned_sg)
		sg_copy_from_buffer(dd->real_dst, sg_nents(dd->real_dst),
				    dd->buf, dd->total);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_dma_transfer_start(काष्ठा aपंचांगel_aes_dev *dd,
					क्रमागत dma_slave_buswidth addr_width,
					क्रमागत dma_transfer_direction dir,
					u32 maxburst)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_slave_config config;
	dma_async_tx_callback callback;
	काष्ठा aपंचांगel_aes_dma *dma;
	पूर्णांक err;

	स_रखो(&config, 0, माप(config));
	config.src_addr_width = addr_width;
	config.dst_addr_width = addr_width;
	config.src_maxburst = maxburst;
	config.dst_maxburst = maxburst;

	चयन (dir) अणु
	हाल DMA_MEM_TO_DEV:
		dma = &dd->src;
		callback = शून्य;
		config.dst_addr = dd->phys_base + AES_IDATAR(0);
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		dma = &dd->dst;
		callback = aपंचांगel_aes_dma_callback;
		config.src_addr = dd->phys_base + AES_ODATAR(0);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	err = dmaengine_slave_config(dma->chan, &config);
	अगर (err)
		वापस err;

	desc = dmaengine_prep_slave_sg(dma->chan, dma->sg, dma->sg_len, dir,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc)
		वापस -ENOMEM;

	desc->callback = callback;
	desc->callback_param = dd;
	dmaengine_submit(desc);
	dma_async_issue_pending(dma->chan);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_dma_start(काष्ठा aपंचांगel_aes_dev *dd,
			       काष्ठा scatterlist *src,
			       काष्ठा scatterlist *dst,
			       माप_प्रकार len,
			       aपंचांगel_aes_fn_t resume)
अणु
	क्रमागत dma_slave_buswidth addr_width;
	u32 maxburst;
	पूर्णांक err;

	चयन (dd->ctx->block_size) अणु
	हाल CFB8_BLOCK_SIZE:
		addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		maxburst = 1;
		अवरोध;

	हाल CFB16_BLOCK_SIZE:
		addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		maxburst = 1;
		अवरोध;

	हाल CFB32_BLOCK_SIZE:
	हाल CFB64_BLOCK_SIZE:
		addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		maxburst = 1;
		अवरोध;

	हाल AES_BLOCK_SIZE:
		addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		maxburst = dd->caps.max_burst_size;
		अवरोध;

	शेष:
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	err = aपंचांगel_aes_map(dd, src, dst, len);
	अगर (err)
		जाओ निकास;

	dd->resume = resume;

	/* Set output DMA transfer first */
	err = aपंचांगel_aes_dma_transfer_start(dd, addr_width, DMA_DEV_TO_MEM,
					   maxburst);
	अगर (err)
		जाओ unmap;

	/* Then set input DMA transfer */
	err = aपंचांगel_aes_dma_transfer_start(dd, addr_width, DMA_MEM_TO_DEV,
					   maxburst);
	अगर (err)
		जाओ output_transfer_stop;

	वापस -EINPROGRESS;

output_transfer_stop:
	dmaengine_terminate_sync(dd->dst.chan);
unmap:
	aपंचांगel_aes_unmap(dd);
निकास:
	वापस aपंचांगel_aes_complete(dd, err);
पूर्ण

अटल व्योम aपंचांगel_aes_dma_callback(व्योम *data)
अणु
	काष्ठा aपंचांगel_aes_dev *dd = data;

	aपंचांगel_aes_unmap(dd);
	dd->is_async = true;
	(व्योम)dd->resume(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_handle_queue(काष्ठा aपंचांगel_aes_dev *dd,
				  काष्ठा crypto_async_request *new_areq)
अणु
	काष्ठा crypto_async_request *areq, *backlog;
	काष्ठा aपंचांगel_aes_base_ctx *ctx;
	अचिन्हित दीर्घ flags;
	bool start_async;
	पूर्णांक err, ret = 0;

	spin_lock_irqsave(&dd->lock, flags);
	अगर (new_areq)
		ret = crypto_enqueue_request(&dd->queue, new_areq);
	अगर (dd->flags & AES_FLAGS_BUSY) अणु
		spin_unlock_irqrestore(&dd->lock, flags);
		वापस ret;
	पूर्ण
	backlog = crypto_get_backlog(&dd->queue);
	areq = crypto_dequeue_request(&dd->queue);
	अगर (areq)
		dd->flags |= AES_FLAGS_BUSY;
	spin_unlock_irqrestore(&dd->lock, flags);

	अगर (!areq)
		वापस ret;

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	ctx = crypto_tfm_ctx(areq->tfm);

	dd->areq = areq;
	dd->ctx = ctx;
	start_async = (areq != new_areq);
	dd->is_async = start_async;

	/* WARNING: ctx->start() MAY change dd->is_async. */
	err = ctx->start(dd);
	वापस (start_async) ? ret : err;
पूर्ण


/* AES async block ciphers */

अटल पूर्णांक aपंचांगel_aes_transfer_complete(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	वापस aपंचांगel_aes_complete(dd, 0);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_start(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_reqctx *rctx = skcipher_request_ctx(req);
	bool use_dma = (req->cryptlen >= ATMEL_AES_DMA_THRESHOLD ||
			dd->ctx->block_size != AES_BLOCK_SIZE);
	पूर्णांक err;

	aपंचांगel_aes_set_mode(dd, rctx);

	err = aपंचांगel_aes_hw_init(dd);
	अगर (err)
		वापस aपंचांगel_aes_complete(dd, err);

	aपंचांगel_aes_ग_लिखो_ctrl(dd, use_dma, (व्योम *)req->iv);
	अगर (use_dma)
		वापस aपंचांगel_aes_dma_start(dd, req->src, req->dst,
					   req->cryptlen,
					   aपंचांगel_aes_transfer_complete);

	वापस aपंचांगel_aes_cpu_start(dd, req->src, req->dst, req->cryptlen,
				   aपंचांगel_aes_transfer_complete);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ctr_transfer(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_ctr_ctx *ctx = aपंचांगel_aes_ctr_ctx_cast(dd->ctx);
	काष्ठा skcipher_request *req = skcipher_request_cast(dd->areq);
	काष्ठा scatterlist *src, *dst;
	माप_प्रकार datalen;
	u32 ctr;
	u16 start, end;
	bool use_dma, fragmented = false;

	/* Check क्रम transfer completion. */
	ctx->offset += dd->total;
	अगर (ctx->offset >= req->cryptlen)
		वापस aपंचांगel_aes_transfer_complete(dd);

	/* Compute data length. */
	datalen = req->cryptlen - ctx->offset;
	ctx->blocks = DIV_ROUND_UP(datalen, AES_BLOCK_SIZE);
	ctr = be32_to_cpu(ctx->iv[3]);

	/* Check 16bit counter overflow. */
	start = ctr & 0xffff;
	end = start + ctx->blocks - 1;

	अगर (ctx->blocks >> 16 || end < start) अणु
		ctr |= 0xffff;
		datalen = AES_BLOCK_SIZE * (0x10000 - start);
		fragmented = true;
	पूर्ण

	use_dma = (datalen >= ATMEL_AES_DMA_THRESHOLD);

	/* Jump to offset. */
	src = scatterwalk_ffwd(ctx->src, req->src, ctx->offset);
	dst = ((req->src == req->dst) ? src :
	       scatterwalk_ffwd(ctx->dst, req->dst, ctx->offset));

	/* Configure hardware. */
	aपंचांगel_aes_ग_लिखो_ctrl(dd, use_dma, ctx->iv);
	अगर (unlikely(fragmented)) अणु
		/*
		 * Increment the counter manually to cope with the hardware
		 * counter overflow.
		 */
		ctx->iv[3] = cpu_to_be32(ctr);
		crypto_inc((u8 *)ctx->iv, AES_BLOCK_SIZE);
	पूर्ण

	अगर (use_dma)
		वापस aपंचांगel_aes_dma_start(dd, src, dst, datalen,
					   aपंचांगel_aes_ctr_transfer);

	वापस aपंचांगel_aes_cpu_start(dd, src, dst, datalen,
				   aपंचांगel_aes_ctr_transfer);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ctr_start(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_ctr_ctx *ctx = aपंचांगel_aes_ctr_ctx_cast(dd->ctx);
	काष्ठा skcipher_request *req = skcipher_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_reqctx *rctx = skcipher_request_ctx(req);
	पूर्णांक err;

	aपंचांगel_aes_set_mode(dd, rctx);

	err = aपंचांगel_aes_hw_init(dd);
	अगर (err)
		वापस aपंचांगel_aes_complete(dd, err);

	स_नकल(ctx->iv, req->iv, AES_BLOCK_SIZE);
	ctx->offset = 0;
	dd->total = 0;
	वापस aपंचांगel_aes_ctr_transfer(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा aपंचांगel_aes_base_ctx *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा aपंचांगel_aes_reqctx *rctx;
	काष्ठा aपंचांगel_aes_dev *dd;

	चयन (mode & AES_FLAGS_OPMODE_MASK) अणु
	हाल AES_FLAGS_CFB8:
		ctx->block_size = CFB8_BLOCK_SIZE;
		अवरोध;

	हाल AES_FLAGS_CFB16:
		ctx->block_size = CFB16_BLOCK_SIZE;
		अवरोध;

	हाल AES_FLAGS_CFB32:
		ctx->block_size = CFB32_BLOCK_SIZE;
		अवरोध;

	हाल AES_FLAGS_CFB64:
		ctx->block_size = CFB64_BLOCK_SIZE;
		अवरोध;

	शेष:
		ctx->block_size = AES_BLOCK_SIZE;
		अवरोध;
	पूर्ण
	ctx->is_aead = false;

	dd = aपंचांगel_aes_find_dev(ctx);
	अगर (!dd)
		वापस -ENODEV;

	rctx = skcipher_request_ctx(req);
	rctx->mode = mode;

	अगर ((mode & AES_FLAGS_OPMODE_MASK) != AES_FLAGS_ECB &&
	    !(mode & AES_FLAGS_ENCRYPT) && req->src == req->dst) अणु
		अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(skcipher);

		अगर (req->cryptlen >= ivsize)
			scatterwalk_map_and_copy(rctx->lastc, req->src,
						 req->cryptlen - ivsize,
						 ivsize, 0);
	पूर्ण

	वापस aपंचांगel_aes_handle_queue(dd, &req->base);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aपंचांगel_aes_base_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (keylen != AES_KEYSIZE_128 &&
	    keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_256)
		वापस -EINVAL;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_ECB | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_ECB);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CBC | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CBC);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ofb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_OFB | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ofb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_OFB);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB128 | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB128);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb64_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB64 | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb64_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB64);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb32_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB32 | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb32_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB32);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb16_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB16 | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb16_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB16);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb8_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB8 | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_cfb8_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CFB8);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CTR | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ctr_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_CTR);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा aपंचांगel_aes_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा aपंचांगel_aes_reqctx));
	ctx->base.start = aपंचांगel_aes_start;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_ctr_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा aपंचांगel_aes_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा aपंचांगel_aes_reqctx));
	ctx->base.start = aपंचांगel_aes_ctr_start;

	वापस 0;
पूर्ण

अटल काष्ठा skcipher_alg aes_algs[] = अणु
अणु
	.base.cra_name		= "ecb(aes)",
	.base.cra_driver_name	= "atmel-ecb-aes",
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctx),

	.init			= aपंचांगel_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_ecb_encrypt,
	.decrypt		= aपंचांगel_aes_ecb_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cbc(aes)",
	.base.cra_driver_name	= "atmel-cbc-aes",
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctx),

	.init			= aपंचांगel_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_cbc_encrypt,
	.decrypt		= aपंचांगel_aes_cbc_decrypt,
	.ivsize			= AES_BLOCK_SIZE,
पूर्ण,
अणु
	.base.cra_name		= "ofb(aes)",
	.base.cra_driver_name	= "atmel-ofb-aes",
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctx),

	.init			= aपंचांगel_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_ofb_encrypt,
	.decrypt		= aपंचांगel_aes_ofb_decrypt,
	.ivsize			= AES_BLOCK_SIZE,
पूर्ण,
अणु
	.base.cra_name		= "cfb(aes)",
	.base.cra_driver_name	= "atmel-cfb-aes",
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctx),

	.init			= aपंचांगel_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_cfb_encrypt,
	.decrypt		= aपंचांगel_aes_cfb_decrypt,
	.ivsize			= AES_BLOCK_SIZE,
पूर्ण,
अणु
	.base.cra_name		= "cfb32(aes)",
	.base.cra_driver_name	= "atmel-cfb32-aes",
	.base.cra_blocksize	= CFB32_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctx),

	.init			= aपंचांगel_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_cfb32_encrypt,
	.decrypt		= aपंचांगel_aes_cfb32_decrypt,
	.ivsize			= AES_BLOCK_SIZE,
पूर्ण,
अणु
	.base.cra_name		= "cfb16(aes)",
	.base.cra_driver_name	= "atmel-cfb16-aes",
	.base.cra_blocksize	= CFB16_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctx),

	.init			= aपंचांगel_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_cfb16_encrypt,
	.decrypt		= aपंचांगel_aes_cfb16_decrypt,
	.ivsize			= AES_BLOCK_SIZE,
पूर्ण,
अणु
	.base.cra_name		= "cfb8(aes)",
	.base.cra_driver_name	= "atmel-cfb8-aes",
	.base.cra_blocksize	= CFB8_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctx),

	.init			= aपंचांगel_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_cfb8_encrypt,
	.decrypt		= aपंचांगel_aes_cfb8_decrypt,
	.ivsize			= AES_BLOCK_SIZE,
पूर्ण,
अणु
	.base.cra_name		= "ctr(aes)",
	.base.cra_driver_name	= "atmel-ctr-aes",
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctr_ctx),

	.init			= aपंचांगel_aes_ctr_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_ctr_encrypt,
	.decrypt		= aपंचांगel_aes_ctr_decrypt,
	.ivsize			= AES_BLOCK_SIZE,
पूर्ण,
पूर्ण;

अटल काष्ठा skcipher_alg aes_cfb64_alg = अणु
	.base.cra_name		= "cfb64(aes)",
	.base.cra_driver_name	= "atmel-cfb64-aes",
	.base.cra_blocksize	= CFB64_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_ctx),

	.init			= aपंचांगel_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= aपंचांगel_aes_setkey,
	.encrypt		= aपंचांगel_aes_cfb64_encrypt,
	.decrypt		= aपंचांगel_aes_cfb64_decrypt,
	.ivsize			= AES_BLOCK_SIZE,
पूर्ण;


/* gcm aead functions */

अटल पूर्णांक aपंचांगel_aes_gcm_ghash(काष्ठा aपंचांगel_aes_dev *dd,
			       स्थिर u32 *data, माप_प्रकार datalen,
			       स्थिर __be32 *ghash_in, __be32 *ghash_out,
			       aपंचांगel_aes_fn_t resume);
अटल पूर्णांक aपंचांगel_aes_gcm_ghash_init(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_gcm_ghash_finalize(काष्ठा aपंचांगel_aes_dev *dd);

अटल पूर्णांक aपंचांगel_aes_gcm_start(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_gcm_process(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_gcm_length(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_gcm_data(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_gcm_tag_init(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_gcm_tag(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_gcm_finalize(काष्ठा aपंचांगel_aes_dev *dd);

अटल अंतरभूत काष्ठा aपंचांगel_aes_gcm_ctx *
aपंचांगel_aes_gcm_ctx_cast(काष्ठा aपंचांगel_aes_base_ctx *ctx)
अणु
	वापस container_of(ctx, काष्ठा aपंचांगel_aes_gcm_ctx, base);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_ghash(काष्ठा aपंचांगel_aes_dev *dd,
			       स्थिर u32 *data, माप_प्रकार datalen,
			       स्थिर __be32 *ghash_in, __be32 *ghash_out,
			       aपंचांगel_aes_fn_t resume)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);

	dd->data = (u32 *)data;
	dd->datalen = datalen;
	ctx->ghash_in = ghash_in;
	ctx->ghash_out = ghash_out;
	ctx->ghash_resume = resume;

	aपंचांगel_aes_ग_लिखो_ctrl(dd, false, शून्य);
	वापस aपंचांगel_aes_रुको_क्रम_data_पढ़ोy(dd, aपंचांगel_aes_gcm_ghash_init);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_ghash_init(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);

	/* Set the data length. */
	aपंचांगel_aes_ग_लिखो(dd, AES_AADLENR, dd->total);
	aपंचांगel_aes_ग_लिखो(dd, AES_CLENR, 0);

	/* If needed, overग_लिखो the GCM Intermediate Hash Word Registers */
	अगर (ctx->ghash_in)
		aपंचांगel_aes_ग_लिखो_block(dd, AES_GHASHR(0), ctx->ghash_in);

	वापस aपंचांगel_aes_gcm_ghash_finalize(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_ghash_finalize(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);
	u32 isr;

	/* Write data पूर्णांकo the Input Data Registers. */
	जबतक (dd->datalen > 0) अणु
		aपंचांगel_aes_ग_लिखो_block(dd, AES_IDATAR(0), dd->data);
		dd->data += 4;
		dd->datalen -= AES_BLOCK_SIZE;

		isr = aपंचांगel_aes_पढ़ो(dd, AES_ISR);
		अगर (!(isr & AES_INT_DATARDY)) अणु
			dd->resume = aपंचांगel_aes_gcm_ghash_finalize;
			aपंचांगel_aes_ग_लिखो(dd, AES_IER, AES_INT_DATARDY);
			वापस -EINPROGRESS;
		पूर्ण
	पूर्ण

	/* Read the computed hash from GHASHRx. */
	aपंचांगel_aes_पढ़ो_block(dd, AES_GHASHR(0), ctx->ghash_out);

	वापस ctx->ghash_resume(dd);
पूर्ण


अटल पूर्णांक aपंचांगel_aes_gcm_start(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा aपंचांगel_aes_reqctx *rctx = aead_request_ctx(req);
	माप_प्रकार ivsize = crypto_aead_ivsize(tfm);
	माप_प्रकार datalen, padlen;
	स्थिर व्योम *iv = req->iv;
	u8 *data = dd->buf;
	पूर्णांक err;

	aपंचांगel_aes_set_mode(dd, rctx);

	err = aपंचांगel_aes_hw_init(dd);
	अगर (err)
		वापस aपंचांगel_aes_complete(dd, err);

	अगर (likely(ivsize == GCM_AES_IV_SIZE)) अणु
		स_नकल(ctx->j0, iv, ivsize);
		ctx->j0[3] = cpu_to_be32(1);
		वापस aपंचांगel_aes_gcm_process(dd);
	पूर्ण

	padlen = aपंचांगel_aes_padlen(ivsize, AES_BLOCK_SIZE);
	datalen = ivsize + padlen + AES_BLOCK_SIZE;
	अगर (datalen > dd->buflen)
		वापस aपंचांगel_aes_complete(dd, -EINVAL);

	स_नकल(data, iv, ivsize);
	स_रखो(data + ivsize, 0, padlen + माप(u64));
	((__be64 *)(data + datalen))[-1] = cpu_to_be64(ivsize * 8);

	वापस aपंचांगel_aes_gcm_ghash(dd, (स्थिर u32 *)data, datalen,
				   शून्य, ctx->j0, aपंचांगel_aes_gcm_process);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_process(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	bool enc = aपंचांगel_aes_is_encrypt(dd);
	u32 authsize;

	/* Compute text length. */
	authsize = crypto_aead_authsize(tfm);
	ctx->textlen = req->cryptlen - (enc ? 0 : authsize);

	/*
	 * According to tcrypt test suite, the GCM Automatic Tag Generation
	 * fails when both the message and its associated data are empty.
	 */
	अगर (likely(req->assoclen != 0 || ctx->textlen != 0))
		dd->flags |= AES_FLAGS_GTAGEN;

	aपंचांगel_aes_ग_लिखो_ctrl(dd, false, शून्य);
	वापस aपंचांगel_aes_रुको_क्रम_data_पढ़ोy(dd, aपंचांगel_aes_gcm_length);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_length(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	__be32 j0_lsw, *j0 = ctx->j0;
	माप_प्रकार padlen;

	/* Write incr32(J0) पूर्णांकo IV. */
	j0_lsw = j0[3];
	be32_add_cpu(&j0[3], 1);
	aपंचांगel_aes_ग_लिखो_block(dd, AES_IVR(0), j0);
	j0[3] = j0_lsw;

	/* Set aad and text lengths. */
	aपंचांगel_aes_ग_लिखो(dd, AES_AADLENR, req->assoclen);
	aपंचांगel_aes_ग_लिखो(dd, AES_CLENR, ctx->textlen);

	/* Check whether AAD are present. */
	अगर (unlikely(req->assoclen == 0)) अणु
		dd->datalen = 0;
		वापस aपंचांगel_aes_gcm_data(dd);
	पूर्ण

	/* Copy assoc data and add padding. */
	padlen = aपंचांगel_aes_padlen(req->assoclen, AES_BLOCK_SIZE);
	अगर (unlikely(req->assoclen + padlen > dd->buflen))
		वापस aपंचांगel_aes_complete(dd, -EINVAL);
	sg_copy_to_buffer(req->src, sg_nents(req->src), dd->buf, req->assoclen);

	/* Write assoc data पूर्णांकo the Input Data रेजिस्टर. */
	dd->data = (u32 *)dd->buf;
	dd->datalen = req->assoclen + padlen;
	वापस aपंचांगel_aes_gcm_data(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_data(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	bool use_dma = (ctx->textlen >= ATMEL_AES_DMA_THRESHOLD);
	काष्ठा scatterlist *src, *dst;
	u32 isr, mr;

	/* Write AAD first. */
	जबतक (dd->datalen > 0) अणु
		aपंचांगel_aes_ग_लिखो_block(dd, AES_IDATAR(0), dd->data);
		dd->data += 4;
		dd->datalen -= AES_BLOCK_SIZE;

		isr = aपंचांगel_aes_पढ़ो(dd, AES_ISR);
		अगर (!(isr & AES_INT_DATARDY)) अणु
			dd->resume = aपंचांगel_aes_gcm_data;
			aपंचांगel_aes_ग_लिखो(dd, AES_IER, AES_INT_DATARDY);
			वापस -EINPROGRESS;
		पूर्ण
	पूर्ण

	/* GMAC only. */
	अगर (unlikely(ctx->textlen == 0))
		वापस aपंचांगel_aes_gcm_tag_init(dd);

	/* Prepare src and dst scatter lists to transfer cipher/plain texts */
	src = scatterwalk_ffwd(ctx->src, req->src, req->assoclen);
	dst = ((req->src == req->dst) ? src :
	       scatterwalk_ffwd(ctx->dst, req->dst, req->assoclen));

	अगर (use_dma) अणु
		/* Update the Mode Register क्रम DMA transfers. */
		mr = aपंचांगel_aes_पढ़ो(dd, AES_MR);
		mr &= ~(AES_MR_SMOD_MASK | AES_MR_DUALBUFF);
		mr |= AES_MR_SMOD_IDATAR0;
		अगर (dd->caps.has_dualbuff)
			mr |= AES_MR_DUALBUFF;
		aपंचांगel_aes_ग_लिखो(dd, AES_MR, mr);

		वापस aपंचांगel_aes_dma_start(dd, src, dst, ctx->textlen,
					   aपंचांगel_aes_gcm_tag_init);
	पूर्ण

	वापस aपंचांगel_aes_cpu_start(dd, src, dst, ctx->textlen,
				   aपंचांगel_aes_gcm_tag_init);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_tag_init(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	__be64 *data = dd->buf;

	अगर (likely(dd->flags & AES_FLAGS_GTAGEN)) अणु
		अगर (!(aपंचांगel_aes_पढ़ो(dd, AES_ISR) & AES_INT_TAGRDY)) अणु
			dd->resume = aपंचांगel_aes_gcm_tag_init;
			aपंचांगel_aes_ग_लिखो(dd, AES_IER, AES_INT_TAGRDY);
			वापस -EINPROGRESS;
		पूर्ण

		वापस aपंचांगel_aes_gcm_finalize(dd);
	पूर्ण

	/* Read the GCM Intermediate Hash Word Registers. */
	aपंचांगel_aes_पढ़ो_block(dd, AES_GHASHR(0), ctx->ghash);

	data[0] = cpu_to_be64(req->assoclen * 8);
	data[1] = cpu_to_be64(ctx->textlen * 8);

	वापस aपंचांगel_aes_gcm_ghash(dd, (स्थिर u32 *)data, AES_BLOCK_SIZE,
				   ctx->ghash, ctx->ghash, aपंचांगel_aes_gcm_tag);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_tag(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);
	अचिन्हित दीर्घ flags;

	/*
	 * Change mode to CTR to complete the tag generation.
	 * Use J0 as Initialization Vector.
	 */
	flags = dd->flags;
	dd->flags &= ~(AES_FLAGS_OPMODE_MASK | AES_FLAGS_GTAGEN);
	dd->flags |= AES_FLAGS_CTR;
	aपंचांगel_aes_ग_लिखो_ctrl(dd, false, ctx->j0);
	dd->flags = flags;

	aपंचांगel_aes_ग_लिखो_block(dd, AES_IDATAR(0), ctx->ghash);
	वापस aपंचांगel_aes_रुको_क्रम_data_पढ़ोy(dd, aपंचांगel_aes_gcm_finalize);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_finalize(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = aपंचांगel_aes_gcm_ctx_cast(dd->ctx);
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	bool enc = aपंचांगel_aes_is_encrypt(dd);
	u32 offset, authsize, itag[4], *otag = ctx->tag;
	पूर्णांक err;

	/* Read the computed tag. */
	अगर (likely(dd->flags & AES_FLAGS_GTAGEN))
		aपंचांगel_aes_पढ़ो_block(dd, AES_TAGR(0), ctx->tag);
	अन्यथा
		aपंचांगel_aes_पढ़ो_block(dd, AES_ODATAR(0), ctx->tag);

	offset = req->assoclen + ctx->textlen;
	authsize = crypto_aead_authsize(tfm);
	अगर (enc) अणु
		scatterwalk_map_and_copy(otag, req->dst, offset, authsize, 1);
		err = 0;
	पूर्ण अन्यथा अणु
		scatterwalk_map_and_copy(itag, req->src, offset, authsize, 0);
		err = crypto_memneq(itag, otag, authsize) ? -EBADMSG : 0;
	पूर्ण

	वापस aपंचांगel_aes_complete(dd, err);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_crypt(काष्ठा aead_request *req,
			       अचिन्हित दीर्घ mode)
अणु
	काष्ठा aपंचांगel_aes_base_ctx *ctx;
	काष्ठा aपंचांगel_aes_reqctx *rctx;
	काष्ठा aपंचांगel_aes_dev *dd;

	ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	ctx->block_size = AES_BLOCK_SIZE;
	ctx->is_aead = true;

	dd = aपंचांगel_aes_find_dev(ctx);
	अगर (!dd)
		वापस -ENODEV;

	rctx = aead_request_ctx(req);
	rctx->mode = AES_FLAGS_GCM | mode;

	वापस aपंचांगel_aes_handle_queue(dd, &req->base);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aपंचांगel_aes_base_ctx *ctx = crypto_aead_ctx(tfm);

	अगर (keylen != AES_KEYSIZE_256 &&
	    keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_128)
		वापस -EINVAL;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_setauthsize(काष्ठा crypto_aead *tfm,
				     अचिन्हित पूर्णांक authsize)
अणु
	वापस crypto_gcm_check_authsize(authsize);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस aपंचांगel_aes_gcm_crypt(req, AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस aपंचांगel_aes_gcm_crypt(req, 0);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_gcm_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aपंचांगel_aes_gcm_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_aead_set_reqsize(tfm, माप(काष्ठा aपंचांगel_aes_reqctx));
	ctx->base.start = aपंचांगel_aes_gcm_start;

	वापस 0;
पूर्ण

अटल काष्ठा aead_alg aes_gcm_alg = अणु
	.setkey		= aपंचांगel_aes_gcm_setkey,
	.setauthsize	= aपंचांगel_aes_gcm_setauthsize,
	.encrypt	= aपंचांगel_aes_gcm_encrypt,
	.decrypt	= aपंचांगel_aes_gcm_decrypt,
	.init		= aपंचांगel_aes_gcm_init,
	.ivsize		= GCM_AES_IV_SIZE,
	.maxauthsize	= AES_BLOCK_SIZE,

	.base = अणु
		.cra_name		= "gcm(aes)",
		.cra_driver_name	= "atmel-gcm-aes",
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा aपंचांगel_aes_gcm_ctx),
	पूर्ण,
पूर्ण;


/* xts functions */

अटल अंतरभूत काष्ठा aपंचांगel_aes_xts_ctx *
aपंचांगel_aes_xts_ctx_cast(काष्ठा aपंचांगel_aes_base_ctx *ctx)
अणु
	वापस container_of(ctx, काष्ठा aपंचांगel_aes_xts_ctx, base);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_xts_process_data(काष्ठा aपंचांगel_aes_dev *dd);

अटल पूर्णांक aपंचांगel_aes_xts_start(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aपंचांगel_aes_xts_ctx *ctx = aपंचांगel_aes_xts_ctx_cast(dd->ctx);
	काष्ठा skcipher_request *req = skcipher_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_reqctx *rctx = skcipher_request_ctx(req);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	aपंचांगel_aes_set_mode(dd, rctx);

	err = aपंचांगel_aes_hw_init(dd);
	अगर (err)
		वापस aपंचांगel_aes_complete(dd, err);

	/* Compute the tweak value from req->iv with ecb(aes). */
	flags = dd->flags;
	dd->flags &= ~AES_FLAGS_MODE_MASK;
	dd->flags |= (AES_FLAGS_ECB | AES_FLAGS_ENCRYPT);
	aपंचांगel_aes_ग_लिखो_ctrl_key(dd, false, शून्य,
				 ctx->key2, ctx->base.keylen);
	dd->flags = flags;

	aपंचांगel_aes_ग_लिखो_block(dd, AES_IDATAR(0), req->iv);
	वापस aपंचांगel_aes_रुको_क्रम_data_पढ़ोy(dd, aपंचांगel_aes_xts_process_data);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_xts_process_data(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(dd->areq);
	bool use_dma = (req->cryptlen >= ATMEL_AES_DMA_THRESHOLD);
	u32 tweak[AES_BLOCK_SIZE / माप(u32)];
	अटल स्थिर __le32 one[AES_BLOCK_SIZE / माप(u32)] = अणुcpu_to_le32(1), पूर्ण;
	u8 *tweak_bytes = (u8 *)tweak;
	पूर्णांक i;

	/* Read the computed ciphered tweak value. */
	aपंचांगel_aes_पढ़ो_block(dd, AES_ODATAR(0), tweak);
	/*
	 * Hardware quirk:
	 * the order of the ciphered tweak bytes need to be reversed beक्रमe
	 * writing them पूर्णांकo the ODATARx रेजिस्टरs.
	 */
	क्रम (i = 0; i < AES_BLOCK_SIZE/2; ++i) अणु
		u8 पंचांगp = tweak_bytes[AES_BLOCK_SIZE - 1 - i];

		tweak_bytes[AES_BLOCK_SIZE - 1 - i] = tweak_bytes[i];
		tweak_bytes[i] = पंचांगp;
	पूर्ण

	/* Process the data. */
	aपंचांगel_aes_ग_लिखो_ctrl(dd, use_dma, शून्य);
	aपंचांगel_aes_ग_लिखो_block(dd, AES_TWR(0), tweak);
	aपंचांगel_aes_ग_लिखो_block(dd, AES_ALPHAR(0), one);
	अगर (use_dma)
		वापस aपंचांगel_aes_dma_start(dd, req->src, req->dst,
					   req->cryptlen,
					   aपंचांगel_aes_transfer_complete);

	वापस aपंचांगel_aes_cpu_start(dd, req->src, req->dst, req->cryptlen,
				   aपंचांगel_aes_transfer_complete);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_xts_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aपंचांगel_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = xts_check_key(crypto_skcipher_tfm(tfm), key, keylen);
	अगर (err)
		वापस err;

	स_नकल(ctx->base.key, key, keylen/2);
	स_नकल(ctx->key2, key + keylen/2, keylen/2);
	ctx->base.keylen = keylen/2;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_xts_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_XTS | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_xts_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस aपंचांगel_aes_crypt(req, AES_FLAGS_XTS);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_xts_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा aपंचांगel_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा aपंचांगel_aes_reqctx));
	ctx->base.start = aपंचांगel_aes_xts_start;

	वापस 0;
पूर्ण

अटल काष्ठा skcipher_alg aes_xts_alg = अणु
	.base.cra_name		= "xts(aes)",
	.base.cra_driver_name	= "atmel-xts-aes",
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा aपंचांगel_aes_xts_ctx),

	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= aपंचांगel_aes_xts_setkey,
	.encrypt		= aपंचांगel_aes_xts_encrypt,
	.decrypt		= aपंचांगel_aes_xts_decrypt,
	.init			= aपंचांगel_aes_xts_init_tfm,
पूर्ण;

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
/* authenc aead functions */

अटल पूर्णांक aपंचांगel_aes_authenc_start(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_authenc_init(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err,
				  bool is_async);
अटल पूर्णांक aपंचांगel_aes_authenc_transfer(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err,
				      bool is_async);
अटल पूर्णांक aपंचांगel_aes_authenc_digest(काष्ठा aपंचांगel_aes_dev *dd);
अटल पूर्णांक aपंचांगel_aes_authenc_final(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err,
				   bool is_async);

अटल व्योम aपंचांगel_aes_authenc_complete(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err)
अणु
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_authenc_reqctx *rctx = aead_request_ctx(req);

	अगर (err && (dd->flags & AES_FLAGS_OWN_SHA))
		aपंचांगel_sha_authenc_पात(&rctx->auth_req);
	dd->flags &= ~AES_FLAGS_OWN_SHA;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_start(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_authenc_reqctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा aपंचांगel_aes_authenc_ctx *ctx = crypto_aead_ctx(tfm);
	पूर्णांक err;

	aपंचांगel_aes_set_mode(dd, &rctx->base);

	err = aपंचांगel_aes_hw_init(dd);
	अगर (err)
		वापस aपंचांगel_aes_complete(dd, err);

	वापस aपंचांगel_sha_authenc_schedule(&rctx->auth_req, ctx->auth,
					  aपंचांगel_aes_authenc_init, dd);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_init(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err,
				  bool is_async)
अणु
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_authenc_reqctx *rctx = aead_request_ctx(req);

	अगर (is_async)
		dd->is_async = true;
	अगर (err)
		वापस aपंचांगel_aes_complete(dd, err);

	/* If here, we've got the ownership of the SHA device. */
	dd->flags |= AES_FLAGS_OWN_SHA;

	/* Configure the SHA device. */
	वापस aपंचांगel_sha_authenc_init(&rctx->auth_req,
				      req->src, req->assoclen,
				      rctx->textlen,
				      aपंचांगel_aes_authenc_transfer, dd);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_transfer(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err,
				      bool is_async)
अणु
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_authenc_reqctx *rctx = aead_request_ctx(req);
	bool enc = aपंचांगel_aes_is_encrypt(dd);
	काष्ठा scatterlist *src, *dst;
	__be32 iv[AES_BLOCK_SIZE / माप(u32)];
	u32 emr;

	अगर (is_async)
		dd->is_async = true;
	अगर (err)
		वापस aपंचांगel_aes_complete(dd, err);

	/* Prepare src and dst scatter-lists to transfer cipher/plain texts. */
	src = scatterwalk_ffwd(rctx->src, req->src, req->assoclen);
	dst = src;

	अगर (req->src != req->dst)
		dst = scatterwalk_ffwd(rctx->dst, req->dst, req->assoclen);

	/* Configure the AES device. */
	स_नकल(iv, req->iv, माप(iv));

	/*
	 * Here we always set the 2nd parameter of aपंचांगel_aes_ग_लिखो_ctrl() to
	 * 'true' even अगर the data transfer is actually perक्रमmed by the CPU (so
	 * not by the DMA) because we must क्रमce the AES_MR_SMOD bitfield to the
	 * value AES_MR_SMOD_IDATAR0. Indeed, both AES_MR_SMOD and SHA_MR_SMOD
	 * must be set to *_MR_SMOD_IDATAR0.
	 */
	aपंचांगel_aes_ग_लिखो_ctrl(dd, true, iv);
	emr = AES_EMR_PLIPEN;
	अगर (!enc)
		emr |= AES_EMR_PLIPD;
	aपंचांगel_aes_ग_लिखो(dd, AES_EMR, emr);

	/* Transfer data. */
	वापस aपंचांगel_aes_dma_start(dd, src, dst, rctx->textlen,
				   aपंचांगel_aes_authenc_digest);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_digest(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_authenc_reqctx *rctx = aead_request_ctx(req);

	/* aपंचांगel_sha_authenc_final() releases the SHA device. */
	dd->flags &= ~AES_FLAGS_OWN_SHA;
	वापस aपंचांगel_sha_authenc_final(&rctx->auth_req,
				       rctx->digest, माप(rctx->digest),
				       aपंचांगel_aes_authenc_final, dd);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_final(काष्ठा aपंचांगel_aes_dev *dd, पूर्णांक err,
				   bool is_async)
अणु
	काष्ठा aead_request *req = aead_request_cast(dd->areq);
	काष्ठा aपंचांगel_aes_authenc_reqctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	bool enc = aपंचांगel_aes_is_encrypt(dd);
	u32 idigest[SHA512_DIGEST_SIZE / माप(u32)], *odigest = rctx->digest;
	u32 offs, authsize;

	अगर (is_async)
		dd->is_async = true;
	अगर (err)
		जाओ complete;

	offs = req->assoclen + rctx->textlen;
	authsize = crypto_aead_authsize(tfm);
	अगर (enc) अणु
		scatterwalk_map_and_copy(odigest, req->dst, offs, authsize, 1);
	पूर्ण अन्यथा अणु
		scatterwalk_map_and_copy(idigest, req->src, offs, authsize, 0);
		अगर (crypto_memneq(idigest, odigest, authsize))
			err = -EBADMSG;
	पूर्ण

complete:
	वापस aपंचांगel_aes_complete(dd, err);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aपंचांगel_aes_authenc_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक err;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		जाओ badkey;

	अगर (keys.enckeylen > माप(ctx->base.key))
		जाओ badkey;

	/* Save auth key. */
	err = aपंचांगel_sha_authenc_setkey(ctx->auth,
				       keys.authkey, keys.authkeylen,
				       crypto_aead_get_flags(tfm));
	अगर (err) अणु
		memzero_explicit(&keys, माप(keys));
		वापस err;
	पूर्ण

	/* Save enc key. */
	ctx->base.keylen = keys.enckeylen;
	स_नकल(ctx->base.key, keys.enckey, keys.enckeylen);

	memzero_explicit(&keys, माप(keys));
	वापस 0;

badkey:
	memzero_explicit(&keys, माप(keys));
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_init_tfm(काष्ठा crypto_aead *tfm,
				      अचिन्हित दीर्घ auth_mode)
अणु
	काष्ठा aपंचांगel_aes_authenc_ctx *ctx = crypto_aead_ctx(tfm);
	अचिन्हित पूर्णांक auth_reqsize = aपंचांगel_sha_authenc_get_reqsize();

	ctx->auth = aपंचांगel_sha_authenc_spawn(auth_mode);
	अगर (IS_ERR(ctx->auth))
		वापस PTR_ERR(ctx->auth);

	crypto_aead_set_reqsize(tfm, (माप(काष्ठा aपंचांगel_aes_authenc_reqctx) +
				      auth_reqsize));
	ctx->base.start = aपंचांगel_aes_authenc_start;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_hmac_sha1_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	वापस aपंचांगel_aes_authenc_init_tfm(tfm, SHA_FLAGS_HMAC_SHA1);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_hmac_sha224_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	वापस aपंचांगel_aes_authenc_init_tfm(tfm, SHA_FLAGS_HMAC_SHA224);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_hmac_sha256_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	वापस aपंचांगel_aes_authenc_init_tfm(tfm, SHA_FLAGS_HMAC_SHA256);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_hmac_sha384_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	वापस aपंचांगel_aes_authenc_init_tfm(tfm, SHA_FLAGS_HMAC_SHA384);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_hmac_sha512_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	वापस aपंचांगel_aes_authenc_init_tfm(tfm, SHA_FLAGS_HMAC_SHA512);
पूर्ण

अटल व्योम aपंचांगel_aes_authenc_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aपंचांगel_aes_authenc_ctx *ctx = crypto_aead_ctx(tfm);

	aपंचांगel_sha_authenc_मुक्त(ctx->auth);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_crypt(काष्ठा aead_request *req,
				   अचिन्हित दीर्घ mode)
अणु
	काष्ठा aपंचांगel_aes_authenc_reqctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा aपंचांगel_aes_base_ctx *ctx = crypto_aead_ctx(tfm);
	u32 authsize = crypto_aead_authsize(tfm);
	bool enc = (mode & AES_FLAGS_ENCRYPT);
	काष्ठा aपंचांगel_aes_dev *dd;

	/* Compute text length. */
	अगर (!enc && req->cryptlen < authsize)
		वापस -EINVAL;
	rctx->textlen = req->cryptlen - (enc ? 0 : authsize);

	/*
	 * Currently, empty messages are not supported yet:
	 * the SHA स्वतः-padding can be used only on non-empty messages.
	 * Hence a special हाल needs to be implemented क्रम empty message.
	 */
	अगर (!rctx->textlen && !req->assoclen)
		वापस -EINVAL;

	rctx->base.mode = mode;
	ctx->block_size = AES_BLOCK_SIZE;
	ctx->is_aead = true;

	dd = aपंचांगel_aes_find_dev(ctx);
	अगर (!dd)
		वापस -ENODEV;

	वापस aपंचांगel_aes_handle_queue(dd, &req->base);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_cbc_aes_encrypt(काष्ठा aead_request *req)
अणु
	वापस aपंचांगel_aes_authenc_crypt(req, AES_FLAGS_CBC | AES_FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_authenc_cbc_aes_decrypt(काष्ठा aead_request *req)
अणु
	वापस aपंचांगel_aes_authenc_crypt(req, AES_FLAGS_CBC);
पूर्ण

अटल काष्ठा aead_alg aes_authenc_algs[] = अणु
अणु
	.setkey		= aपंचांगel_aes_authenc_setkey,
	.encrypt	= aपंचांगel_aes_authenc_cbc_aes_encrypt,
	.decrypt	= aपंचांगel_aes_authenc_cbc_aes_decrypt,
	.init		= aपंचांगel_aes_authenc_hmac_sha1_init_tfm,
	.निकास		= aपंचांगel_aes_authenc_निकास_tfm,
	.ivsize		= AES_BLOCK_SIZE,
	.maxauthsize	= SHA1_DIGEST_SIZE,

	.base = अणु
		.cra_name		= "authenc(hmac(sha1),cbc(aes))",
		.cra_driver_name	= "atmel-authenc-hmac-sha1-cbc-aes",
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा aपंचांगel_aes_authenc_ctx),
	पूर्ण,
पूर्ण,
अणु
	.setkey		= aपंचांगel_aes_authenc_setkey,
	.encrypt	= aपंचांगel_aes_authenc_cbc_aes_encrypt,
	.decrypt	= aपंचांगel_aes_authenc_cbc_aes_decrypt,
	.init		= aपंचांगel_aes_authenc_hmac_sha224_init_tfm,
	.निकास		= aपंचांगel_aes_authenc_निकास_tfm,
	.ivsize		= AES_BLOCK_SIZE,
	.maxauthsize	= SHA224_DIGEST_SIZE,

	.base = अणु
		.cra_name		= "authenc(hmac(sha224),cbc(aes))",
		.cra_driver_name	= "atmel-authenc-hmac-sha224-cbc-aes",
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा aपंचांगel_aes_authenc_ctx),
	पूर्ण,
पूर्ण,
अणु
	.setkey		= aपंचांगel_aes_authenc_setkey,
	.encrypt	= aपंचांगel_aes_authenc_cbc_aes_encrypt,
	.decrypt	= aपंचांगel_aes_authenc_cbc_aes_decrypt,
	.init		= aपंचांगel_aes_authenc_hmac_sha256_init_tfm,
	.निकास		= aपंचांगel_aes_authenc_निकास_tfm,
	.ivsize		= AES_BLOCK_SIZE,
	.maxauthsize	= SHA256_DIGEST_SIZE,

	.base = अणु
		.cra_name		= "authenc(hmac(sha256),cbc(aes))",
		.cra_driver_name	= "atmel-authenc-hmac-sha256-cbc-aes",
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा aपंचांगel_aes_authenc_ctx),
	पूर्ण,
पूर्ण,
अणु
	.setkey		= aपंचांगel_aes_authenc_setkey,
	.encrypt	= aपंचांगel_aes_authenc_cbc_aes_encrypt,
	.decrypt	= aपंचांगel_aes_authenc_cbc_aes_decrypt,
	.init		= aपंचांगel_aes_authenc_hmac_sha384_init_tfm,
	.निकास		= aपंचांगel_aes_authenc_निकास_tfm,
	.ivsize		= AES_BLOCK_SIZE,
	.maxauthsize	= SHA384_DIGEST_SIZE,

	.base = अणु
		.cra_name		= "authenc(hmac(sha384),cbc(aes))",
		.cra_driver_name	= "atmel-authenc-hmac-sha384-cbc-aes",
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा aपंचांगel_aes_authenc_ctx),
	पूर्ण,
पूर्ण,
अणु
	.setkey		= aपंचांगel_aes_authenc_setkey,
	.encrypt	= aपंचांगel_aes_authenc_cbc_aes_encrypt,
	.decrypt	= aपंचांगel_aes_authenc_cbc_aes_decrypt,
	.init		= aपंचांगel_aes_authenc_hmac_sha512_init_tfm,
	.निकास		= aपंचांगel_aes_authenc_निकास_tfm,
	.ivsize		= AES_BLOCK_SIZE,
	.maxauthsize	= SHA512_DIGEST_SIZE,

	.base = अणु
		.cra_name		= "authenc(hmac(sha512),cbc(aes))",
		.cra_driver_name	= "atmel-authenc-hmac-sha512-cbc-aes",
		.cra_blocksize		= AES_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा aपंचांगel_aes_authenc_ctx),
	पूर्ण,
पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_ATMEL_AUTHENC */

/* Probe functions */

अटल पूर्णांक aपंचांगel_aes_buff_init(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	dd->buf = (व्योम *)__get_मुक्त_pages(GFP_KERNEL, ATMEL_AES_BUFFER_ORDER);
	dd->buflen = ATMEL_AES_BUFFER_SIZE;
	dd->buflen &= ~(AES_BLOCK_SIZE - 1);

	अगर (!dd->buf) अणु
		dev_err(dd->dev, "unable to alloc pages.\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_aes_buff_cleanup(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	मुक्त_page((अचिन्हित दीर्घ)dd->buf);
पूर्ण

अटल पूर्णांक aपंचांगel_aes_dma_init(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	पूर्णांक ret;

	/* Try to grab 2 DMA channels */
	dd->src.chan = dma_request_chan(dd->dev, "tx");
	अगर (IS_ERR(dd->src.chan)) अणु
		ret = PTR_ERR(dd->src.chan);
		जाओ err_dma_in;
	पूर्ण

	dd->dst.chan = dma_request_chan(dd->dev, "rx");
	अगर (IS_ERR(dd->dst.chan)) अणु
		ret = PTR_ERR(dd->dst.chan);
		जाओ err_dma_out;
	पूर्ण

	वापस 0;

err_dma_out:
	dma_release_channel(dd->src.chan);
err_dma_in:
	dev_err(dd->dev, "no DMA channel available\n");
	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_aes_dma_cleanup(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	dma_release_channel(dd->dst.chan);
	dma_release_channel(dd->src.chan);
पूर्ण

अटल व्योम aपंचांगel_aes_queue_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा aपंचांगel_aes_dev *dd = (काष्ठा aपंचांगel_aes_dev *)data;

	aपंचांगel_aes_handle_queue(dd, शून्य);
पूर्ण

अटल व्योम aपंचांगel_aes_करोne_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा aपंचांगel_aes_dev *dd = (काष्ठा aपंचांगel_aes_dev *)data;

	dd->is_async = true;
	(व्योम)dd->resume(dd);
पूर्ण

अटल irqवापस_t aपंचांगel_aes_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_aes_dev *aes_dd = dev_id;
	u32 reg;

	reg = aपंचांगel_aes_पढ़ो(aes_dd, AES_ISR);
	अगर (reg & aपंचांगel_aes_पढ़ो(aes_dd, AES_IMR)) अणु
		aपंचांगel_aes_ग_लिखो(aes_dd, AES_IDR, reg);
		अगर (AES_FLAGS_BUSY & aes_dd->flags)
			tasklet_schedule(&aes_dd->करोne_task);
		अन्यथा
			dev_warn(aes_dd->dev, "AES interrupt when no active requests.\n");
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम aपंचांगel_aes_unरेजिस्टर_algs(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	पूर्णांक i;

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
	अगर (dd->caps.has_authenc)
		क्रम (i = 0; i < ARRAY_SIZE(aes_authenc_algs); i++)
			crypto_unरेजिस्टर_aead(&aes_authenc_algs[i]);
#पूर्ण_अगर

	अगर (dd->caps.has_xts)
		crypto_unरेजिस्टर_skcipher(&aes_xts_alg);

	अगर (dd->caps.has_gcm)
		crypto_unरेजिस्टर_aead(&aes_gcm_alg);

	अगर (dd->caps.has_cfb64)
		crypto_unरेजिस्टर_skcipher(&aes_cfb64_alg);

	क्रम (i = 0; i < ARRAY_SIZE(aes_algs); i++)
		crypto_unरेजिस्टर_skcipher(&aes_algs[i]);
पूर्ण

अटल व्योम aपंचांगel_aes_crypto_alg_init(काष्ठा crypto_alg *alg)
अणु
	alg->cra_flags = CRYPTO_ALG_ASYNC;
	alg->cra_alignmask = 0xf;
	alg->cra_priority = ATMEL_AES_PRIORITY;
	alg->cra_module = THIS_MODULE;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_रेजिस्टर_algs(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	पूर्णांक err, i, j;

	क्रम (i = 0; i < ARRAY_SIZE(aes_algs); i++) अणु
		aपंचांगel_aes_crypto_alg_init(&aes_algs[i].base);

		err = crypto_रेजिस्टर_skcipher(&aes_algs[i]);
		अगर (err)
			जाओ err_aes_algs;
	पूर्ण

	अगर (dd->caps.has_cfb64) अणु
		aपंचांगel_aes_crypto_alg_init(&aes_cfb64_alg.base);

		err = crypto_रेजिस्टर_skcipher(&aes_cfb64_alg);
		अगर (err)
			जाओ err_aes_cfb64_alg;
	पूर्ण

	अगर (dd->caps.has_gcm) अणु
		aपंचांगel_aes_crypto_alg_init(&aes_gcm_alg.base);

		err = crypto_रेजिस्टर_aead(&aes_gcm_alg);
		अगर (err)
			जाओ err_aes_gcm_alg;
	पूर्ण

	अगर (dd->caps.has_xts) अणु
		aपंचांगel_aes_crypto_alg_init(&aes_xts_alg.base);

		err = crypto_रेजिस्टर_skcipher(&aes_xts_alg);
		अगर (err)
			जाओ err_aes_xts_alg;
	पूर्ण

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
	अगर (dd->caps.has_authenc) अणु
		क्रम (i = 0; i < ARRAY_SIZE(aes_authenc_algs); i++) अणु
			aपंचांगel_aes_crypto_alg_init(&aes_authenc_algs[i].base);

			err = crypto_रेजिस्टर_aead(&aes_authenc_algs[i]);
			अगर (err)
				जाओ err_aes_authenc_alg;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस 0;

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
	/* i = ARRAY_SIZE(aes_authenc_algs); */
err_aes_authenc_alg:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_aead(&aes_authenc_algs[j]);
	crypto_unरेजिस्टर_skcipher(&aes_xts_alg);
#पूर्ण_अगर
err_aes_xts_alg:
	crypto_unरेजिस्टर_aead(&aes_gcm_alg);
err_aes_gcm_alg:
	crypto_unरेजिस्टर_skcipher(&aes_cfb64_alg);
err_aes_cfb64_alg:
	i = ARRAY_SIZE(aes_algs);
err_aes_algs:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_skcipher(&aes_algs[j]);

	वापस err;
पूर्ण

अटल व्योम aपंचांगel_aes_get_cap(काष्ठा aपंचांगel_aes_dev *dd)
अणु
	dd->caps.has_dualbuff = 0;
	dd->caps.has_cfb64 = 0;
	dd->caps.has_gcm = 0;
	dd->caps.has_xts = 0;
	dd->caps.has_authenc = 0;
	dd->caps.max_burst_size = 1;

	/* keep only major version number */
	चयन (dd->hw_version & 0xff0) अणु
	हाल 0x500:
		dd->caps.has_dualbuff = 1;
		dd->caps.has_cfb64 = 1;
		dd->caps.has_gcm = 1;
		dd->caps.has_xts = 1;
		dd->caps.has_authenc = 1;
		dd->caps.max_burst_size = 4;
		अवरोध;
	हाल 0x200:
		dd->caps.has_dualbuff = 1;
		dd->caps.has_cfb64 = 1;
		dd->caps.has_gcm = 1;
		dd->caps.max_burst_size = 4;
		अवरोध;
	हाल 0x130:
		dd->caps.has_dualbuff = 1;
		dd->caps.has_cfb64 = 1;
		dd->caps.max_burst_size = 4;
		अवरोध;
	हाल 0x120:
		अवरोध;
	शेष:
		dev_warn(dd->dev,
				"Unmanaged aes version, set minimum capabilities\n");
		अवरोध;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id aपंचांगel_aes_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9g46-aes" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_aes_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक aपंचांगel_aes_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_aes_dev *aes_dd;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *aes_res;
	पूर्णांक err;

	aes_dd = devm_kzalloc(&pdev->dev, माप(*aes_dd), GFP_KERNEL);
	अगर (!aes_dd)
		वापस -ENOMEM;

	aes_dd->dev = dev;

	platक्रमm_set_drvdata(pdev, aes_dd);

	INIT_LIST_HEAD(&aes_dd->list);
	spin_lock_init(&aes_dd->lock);

	tasklet_init(&aes_dd->करोne_task, aपंचांगel_aes_करोne_task,
					(अचिन्हित दीर्घ)aes_dd);
	tasklet_init(&aes_dd->queue_task, aपंचांगel_aes_queue_task,
					(अचिन्हित दीर्घ)aes_dd);

	crypto_init_queue(&aes_dd->queue, ATMEL_AES_QUEUE_LENGTH);

	/* Get the base address */
	aes_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!aes_res) अणु
		dev_err(dev, "no MEM resource info\n");
		err = -ENODEV;
		जाओ err_tasklet_समाप्त;
	पूर्ण
	aes_dd->phys_base = aes_res->start;

	/* Get the IRQ */
	aes_dd->irq = platक्रमm_get_irq(pdev,  0);
	अगर (aes_dd->irq < 0) अणु
		err = aes_dd->irq;
		जाओ err_tasklet_समाप्त;
	पूर्ण

	err = devm_request_irq(&pdev->dev, aes_dd->irq, aपंचांगel_aes_irq,
			       IRQF_SHARED, "atmel-aes", aes_dd);
	अगर (err) अणु
		dev_err(dev, "unable to request aes irq.\n");
		जाओ err_tasklet_समाप्त;
	पूर्ण

	/* Initializing the घड़ी */
	aes_dd->iclk = devm_clk_get(&pdev->dev, "aes_clk");
	अगर (IS_ERR(aes_dd->iclk)) अणु
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(aes_dd->iclk);
		जाओ err_tasklet_समाप्त;
	पूर्ण

	aes_dd->io_base = devm_ioremap_resource(&pdev->dev, aes_res);
	अगर (IS_ERR(aes_dd->io_base)) अणु
		dev_err(dev, "can't ioremap\n");
		err = PTR_ERR(aes_dd->io_base);
		जाओ err_tasklet_समाप्त;
	पूर्ण

	err = clk_prepare(aes_dd->iclk);
	अगर (err)
		जाओ err_tasklet_समाप्त;

	err = aपंचांगel_aes_hw_version_init(aes_dd);
	अगर (err)
		जाओ err_iclk_unprepare;

	aपंचांगel_aes_get_cap(aes_dd);

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
	अगर (aes_dd->caps.has_authenc && !aपंचांगel_sha_authenc_is_पढ़ोy()) अणु
		err = -EPROBE_DEFER;
		जाओ err_iclk_unprepare;
	पूर्ण
#पूर्ण_अगर

	err = aपंचांगel_aes_buff_init(aes_dd);
	अगर (err)
		जाओ err_iclk_unprepare;

	err = aपंचांगel_aes_dma_init(aes_dd);
	अगर (err)
		जाओ err_buff_cleanup;

	spin_lock(&aपंचांगel_aes.lock);
	list_add_tail(&aes_dd->list, &aपंचांगel_aes.dev_list);
	spin_unlock(&aपंचांगel_aes.lock);

	err = aपंचांगel_aes_रेजिस्टर_algs(aes_dd);
	अगर (err)
		जाओ err_algs;

	dev_info(dev, "Atmel AES - Using %s, %s for DMA transfers\n",
			dma_chan_name(aes_dd->src.chan),
			dma_chan_name(aes_dd->dst.chan));

	वापस 0;

err_algs:
	spin_lock(&aपंचांगel_aes.lock);
	list_del(&aes_dd->list);
	spin_unlock(&aपंचांगel_aes.lock);
	aपंचांगel_aes_dma_cleanup(aes_dd);
err_buff_cleanup:
	aपंचांगel_aes_buff_cleanup(aes_dd);
err_iclk_unprepare:
	clk_unprepare(aes_dd->iclk);
err_tasklet_समाप्त:
	tasklet_समाप्त(&aes_dd->करोne_task);
	tasklet_समाप्त(&aes_dd->queue_task);

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_aes_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_aes_dev *aes_dd;

	aes_dd = platक्रमm_get_drvdata(pdev);
	अगर (!aes_dd)
		वापस -ENODEV;
	spin_lock(&aपंचांगel_aes.lock);
	list_del(&aes_dd->list);
	spin_unlock(&aपंचांगel_aes.lock);

	aपंचांगel_aes_unरेजिस्टर_algs(aes_dd);

	tasklet_समाप्त(&aes_dd->करोne_task);
	tasklet_समाप्त(&aes_dd->queue_task);

	aपंचांगel_aes_dma_cleanup(aes_dd);
	aपंचांगel_aes_buff_cleanup(aes_dd);

	clk_unprepare(aes_dd->iclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_aes_driver = अणु
	.probe		= aपंचांगel_aes_probe,
	.हटाओ		= aपंचांगel_aes_हटाओ,
	.driver		= अणु
		.name	= "atmel_aes",
		.of_match_table = of_match_ptr(aपंचांगel_aes_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aपंचांगel_aes_driver);

MODULE_DESCRIPTION("Atmel AES hw acceleration support.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Nicolas Royer - Eukrथऊa Electromatique");
