<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API.
 *
 * Support क्रम OMAP SHA1/MD5 HW acceleration.
 *
 * Copyright (c) 2010 Nokia Corporation
 * Author: Dmitry Kasatkin <dmitry.kasatkin@nokia.com>
 * Copyright (c) 2011 Texas Instruments Incorporated
 *
 * Some ideas are from old omap-sha1-md5.c driver.
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/hmac.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/engine.h>

#घोषणा MD5_DIGEST_SIZE			16

#घोषणा SHA_REG_IDIGEST(dd, x)		((dd)->pdata->idigest_ofs + ((x)*0x04))
#घोषणा SHA_REG_DIN(dd, x)		((dd)->pdata->din_ofs + ((x) * 0x04))
#घोषणा SHA_REG_DIGCNT(dd)		((dd)->pdata->digcnt_ofs)

#घोषणा SHA_REG_ODIGEST(dd, x)		((dd)->pdata->odigest_ofs + (x * 0x04))

#घोषणा SHA_REG_CTRL			0x18
#घोषणा SHA_REG_CTRL_LENGTH		(0xFFFFFFFF << 5)
#घोषणा SHA_REG_CTRL_CLOSE_HASH		(1 << 4)
#घोषणा SHA_REG_CTRL_ALGO_CONST		(1 << 3)
#घोषणा SHA_REG_CTRL_ALGO		(1 << 2)
#घोषणा SHA_REG_CTRL_INPUT_READY	(1 << 1)
#घोषणा SHA_REG_CTRL_OUTPUT_READY	(1 << 0)

#घोषणा SHA_REG_REV(dd)			((dd)->pdata->rev_ofs)

#घोषणा SHA_REG_MASK(dd)		((dd)->pdata->mask_ofs)
#घोषणा SHA_REG_MASK_DMA_EN		(1 << 3)
#घोषणा SHA_REG_MASK_IT_EN		(1 << 2)
#घोषणा SHA_REG_MASK_SOFTRESET		(1 << 1)
#घोषणा SHA_REG_AUTOIDLE		(1 << 0)

#घोषणा SHA_REG_SYSSTATUS(dd)		((dd)->pdata->sysstatus_ofs)
#घोषणा SHA_REG_SYSSTATUS_RESETDONE	(1 << 0)

#घोषणा SHA_REG_MODE(dd)		((dd)->pdata->mode_ofs)
#घोषणा SHA_REG_MODE_HMAC_OUTER_HASH	(1 << 7)
#घोषणा SHA_REG_MODE_HMAC_KEY_PROC	(1 << 5)
#घोषणा SHA_REG_MODE_CLOSE_HASH		(1 << 4)
#घोषणा SHA_REG_MODE_ALGO_CONSTANT	(1 << 3)

#घोषणा SHA_REG_MODE_ALGO_MASK		(7 << 0)
#घोषणा SHA_REG_MODE_ALGO_MD5_128	(0 << 1)
#घोषणा SHA_REG_MODE_ALGO_SHA1_160	(1 << 1)
#घोषणा SHA_REG_MODE_ALGO_SHA2_224	(2 << 1)
#घोषणा SHA_REG_MODE_ALGO_SHA2_256	(3 << 1)
#घोषणा SHA_REG_MODE_ALGO_SHA2_384	(1 << 0)
#घोषणा SHA_REG_MODE_ALGO_SHA2_512	(3 << 0)

#घोषणा SHA_REG_LENGTH(dd)		((dd)->pdata->length_ofs)

#घोषणा SHA_REG_IRQSTATUS		0x118
#घोषणा SHA_REG_IRQSTATUS_CTX_RDY	(1 << 3)
#घोषणा SHA_REG_IRQSTATUS_PARTHASH_RDY (1 << 2)
#घोषणा SHA_REG_IRQSTATUS_INPUT_RDY	(1 << 1)
#घोषणा SHA_REG_IRQSTATUS_OUTPUT_RDY	(1 << 0)

#घोषणा SHA_REG_IRQENA			0x11C
#घोषणा SHA_REG_IRQENA_CTX_RDY		(1 << 3)
#घोषणा SHA_REG_IRQENA_PARTHASH_RDY	(1 << 2)
#घोषणा SHA_REG_IRQENA_INPUT_RDY	(1 << 1)
#घोषणा SHA_REG_IRQENA_OUTPUT_RDY	(1 << 0)

#घोषणा DEFAULT_TIMEOUT_INTERVAL	HZ

#घोषणा DEFAULT_AUTOSUSPEND_DELAY	1000

/* mostly device flags */
#घोषणा FLAGS_FINAL		1
#घोषणा FLAGS_DMA_ACTIVE	2
#घोषणा FLAGS_OUTPUT_READY	3
#घोषणा FLAGS_INIT		4
#घोषणा FLAGS_CPU		5
#घोषणा FLAGS_DMA_READY		6
#घोषणा FLAGS_AUTO_XOR		7
#घोषणा FLAGS_BE32_SHA1		8
#घोषणा FLAGS_SGS_COPIED	9
#घोषणा FLAGS_SGS_ALLOCED	10
#घोषणा FLAGS_HUGE		11

/* context flags */
#घोषणा FLAGS_FINUP		16

#घोषणा FLAGS_MODE_SHIFT	18
#घोषणा FLAGS_MODE_MASK		(SHA_REG_MODE_ALGO_MASK	<< FLAGS_MODE_SHIFT)
#घोषणा FLAGS_MODE_MD5		(SHA_REG_MODE_ALGO_MD5_128 << FLAGS_MODE_SHIFT)
#घोषणा FLAGS_MODE_SHA1		(SHA_REG_MODE_ALGO_SHA1_160 << FLAGS_MODE_SHIFT)
#घोषणा FLAGS_MODE_SHA224	(SHA_REG_MODE_ALGO_SHA2_224 << FLAGS_MODE_SHIFT)
#घोषणा FLAGS_MODE_SHA256	(SHA_REG_MODE_ALGO_SHA2_256 << FLAGS_MODE_SHIFT)
#घोषणा FLAGS_MODE_SHA384	(SHA_REG_MODE_ALGO_SHA2_384 << FLAGS_MODE_SHIFT)
#घोषणा FLAGS_MODE_SHA512	(SHA_REG_MODE_ALGO_SHA2_512 << FLAGS_MODE_SHIFT)

#घोषणा FLAGS_HMAC		21
#घोषणा FLAGS_ERROR		22

#घोषणा OP_UPDATE		1
#घोषणा OP_FINAL		2

#घोषणा OMAP_ALIGN_MASK		(माप(u32)-1)
#घोषणा OMAP_ALIGNED		__attribute__((aligned(माप(u32))))

#घोषणा BUFLEN			SHA512_BLOCK_SIZE
#घोषणा OMAP_SHA_DMA_THRESHOLD	256

#घोषणा OMAP_SHA_MAX_DMA_LEN	(1024 * 2048)

काष्ठा omap_sham_dev;

काष्ठा omap_sham_reqctx अणु
	काष्ठा omap_sham_dev	*dd;
	अचिन्हित दीर्घ		flags;
	u8			op;

	u8			digest[SHA512_DIGEST_SIZE] OMAP_ALIGNED;
	माप_प्रकार			digcnt;
	माप_प्रकार			bufcnt;
	माप_प्रकार			buflen;

	/* walk state */
	काष्ठा scatterlist	*sg;
	काष्ठा scatterlist	sgl[2];
	पूर्णांक			offset;	/* offset in current sg */
	पूर्णांक			sg_len;
	अचिन्हित पूर्णांक		total;	/* total request */

	u8			buffer[] OMAP_ALIGNED;
पूर्ण;

काष्ठा omap_sham_hmac_ctx अणु
	काष्ठा crypto_shash	*shash;
	u8			ipad[SHA512_BLOCK_SIZE] OMAP_ALIGNED;
	u8			opad[SHA512_BLOCK_SIZE] OMAP_ALIGNED;
पूर्ण;

काष्ठा omap_sham_ctx अणु
	काष्ठा crypto_engine_ctx	enginectx;
	अचिन्हित दीर्घ		flags;

	/* fallback stuff */
	काष्ठा crypto_shash	*fallback;

	काष्ठा omap_sham_hmac_ctx base[];
पूर्ण;

#घोषणा OMAP_SHAM_QUEUE_LENGTH	10

काष्ठा omap_sham_algs_info अणु
	काष्ठा ahash_alg	*algs_list;
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		रेजिस्टरed;
पूर्ण;

काष्ठा omap_sham_pdata अणु
	काष्ठा omap_sham_algs_info	*algs_info;
	अचिन्हित पूर्णांक	algs_info_size;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		digest_size;

	व्योम		(*copy_hash)(काष्ठा ahash_request *req, पूर्णांक out);
	व्योम		(*ग_लिखो_ctrl)(काष्ठा omap_sham_dev *dd, माप_प्रकार length,
				      पूर्णांक final, पूर्णांक dma);
	व्योम		(*trigger)(काष्ठा omap_sham_dev *dd, माप_प्रकार length);
	पूर्णांक		(*poll_irq)(काष्ठा omap_sham_dev *dd);
	irqवापस_t	(*पूर्णांकr_hdlr)(पूर्णांक irq, व्योम *dev_id);

	u32		odigest_ofs;
	u32		idigest_ofs;
	u32		din_ofs;
	u32		digcnt_ofs;
	u32		rev_ofs;
	u32		mask_ofs;
	u32		sysstatus_ofs;
	u32		mode_ofs;
	u32		length_ofs;

	u32		major_mask;
	u32		major_shअगरt;
	u32		minor_mask;
	u32		minor_shअगरt;
पूर्ण;

काष्ठा omap_sham_dev अणु
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		phys_base;
	काष्ठा device		*dev;
	व्योम __iomem		*io_base;
	पूर्णांक			irq;
	पूर्णांक			err;
	काष्ठा dma_chan		*dma_lch;
	काष्ठा tasklet_काष्ठा	करोne_task;
	u8			polling_mode;
	u8			xmit_buf[BUFLEN] OMAP_ALIGNED;

	अचिन्हित दीर्घ		flags;
	पूर्णांक			fallback_sz;
	काष्ठा crypto_queue	queue;
	काष्ठा ahash_request	*req;
	काष्ठा crypto_engine	*engine;

	स्थिर काष्ठा omap_sham_pdata	*pdata;
पूर्ण;

काष्ठा omap_sham_drv अणु
	काष्ठा list_head	dev_list;
	spinlock_t		lock;
	अचिन्हित दीर्घ		flags;
पूर्ण;

अटल काष्ठा omap_sham_drv sham = अणु
	.dev_list = LIST_HEAD_INIT(sham.dev_list),
	.lock = __SPIN_LOCK_UNLOCKED(sham.lock),
पूर्ण;

अटल पूर्णांक omap_sham_enqueue(काष्ठा ahash_request *req, अचिन्हित पूर्णांक op);
अटल व्योम omap_sham_finish_req(काष्ठा ahash_request *req, पूर्णांक err);

अटल अंतरभूत u32 omap_sham_पढ़ो(काष्ठा omap_sham_dev *dd, u32 offset)
अणु
	वापस __raw_पढ़ोl(dd->io_base + offset);
पूर्ण

अटल अंतरभूत व्योम omap_sham_ग_लिखो(काष्ठा omap_sham_dev *dd,
					u32 offset, u32 value)
अणु
	__raw_ग_लिखोl(value, dd->io_base + offset);
पूर्ण

अटल अंतरभूत व्योम omap_sham_ग_लिखो_mask(काष्ठा omap_sham_dev *dd, u32 address,
					u32 value, u32 mask)
अणु
	u32 val;

	val = omap_sham_पढ़ो(dd, address);
	val &= ~mask;
	val |= value;
	omap_sham_ग_लिखो(dd, address, val);
पूर्ण

अटल अंतरभूत पूर्णांक omap_sham_रुको(काष्ठा omap_sham_dev *dd, u32 offset, u32 bit)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + DEFAULT_TIMEOUT_INTERVAL;

	जबतक (!(omap_sham_पढ़ो(dd, offset) & bit)) अणु
		अगर (समय_is_beक्रमe_jअगरfies(समयout))
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap_sham_copy_hash_omap2(काष्ठा ahash_request *req, पूर्णांक out)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा omap_sham_dev *dd = ctx->dd;
	u32 *hash = (u32 *)ctx->digest;
	पूर्णांक i;

	क्रम (i = 0; i < dd->pdata->digest_size / माप(u32); i++) अणु
		अगर (out)
			hash[i] = omap_sham_पढ़ो(dd, SHA_REG_IDIGEST(dd, i));
		अन्यथा
			omap_sham_ग_लिखो(dd, SHA_REG_IDIGEST(dd, i), hash[i]);
	पूर्ण
पूर्ण

अटल व्योम omap_sham_copy_hash_omap4(काष्ठा ahash_request *req, पूर्णांक out)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा omap_sham_dev *dd = ctx->dd;
	पूर्णांक i;

	अगर (ctx->flags & BIT(FLAGS_HMAC)) अणु
		काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(dd->req);
		काष्ठा omap_sham_ctx *tctx = crypto_ahash_ctx(tfm);
		काष्ठा omap_sham_hmac_ctx *bctx = tctx->base;
		u32 *opad = (u32 *)bctx->opad;

		क्रम (i = 0; i < dd->pdata->digest_size / माप(u32); i++) अणु
			अगर (out)
				opad[i] = omap_sham_पढ़ो(dd,
						SHA_REG_ODIGEST(dd, i));
			अन्यथा
				omap_sham_ग_लिखो(dd, SHA_REG_ODIGEST(dd, i),
						opad[i]);
		पूर्ण
	पूर्ण

	omap_sham_copy_hash_omap2(req, out);
पूर्ण

अटल व्योम omap_sham_copy_पढ़ोy_hash(काष्ठा ahash_request *req)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	u32 *in = (u32 *)ctx->digest;
	u32 *hash = (u32 *)req->result;
	पूर्णांक i, d, big_endian = 0;

	अगर (!hash)
		वापस;

	चयन (ctx->flags & FLAGS_MODE_MASK) अणु
	हाल FLAGS_MODE_MD5:
		d = MD5_DIGEST_SIZE / माप(u32);
		अवरोध;
	हाल FLAGS_MODE_SHA1:
		/* OMAP2 SHA1 is big endian */
		अगर (test_bit(FLAGS_BE32_SHA1, &ctx->dd->flags))
			big_endian = 1;
		d = SHA1_DIGEST_SIZE / माप(u32);
		अवरोध;
	हाल FLAGS_MODE_SHA224:
		d = SHA224_DIGEST_SIZE / माप(u32);
		अवरोध;
	हाल FLAGS_MODE_SHA256:
		d = SHA256_DIGEST_SIZE / माप(u32);
		अवरोध;
	हाल FLAGS_MODE_SHA384:
		d = SHA384_DIGEST_SIZE / माप(u32);
		अवरोध;
	हाल FLAGS_MODE_SHA512:
		d = SHA512_DIGEST_SIZE / माप(u32);
		अवरोध;
	शेष:
		d = 0;
	पूर्ण

	अगर (big_endian)
		क्रम (i = 0; i < d; i++)
			hash[i] = be32_to_cpup((__be32 *)in + i);
	अन्यथा
		क्रम (i = 0; i < d; i++)
			hash[i] = le32_to_cpup((__le32 *)in + i);
पूर्ण

अटल पूर्णांक omap_sham_hw_init(काष्ठा omap_sham_dev *dd)
अणु
	पूर्णांक err;

	err = pm_runसमय_get_sync(dd->dev);
	अगर (err < 0) अणु
		dev_err(dd->dev, "failed to get sync: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!test_bit(FLAGS_INIT, &dd->flags)) अणु
		set_bit(FLAGS_INIT, &dd->flags);
		dd->err = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap_sham_ग_लिखो_ctrl_omap2(काष्ठा omap_sham_dev *dd, माप_प्रकार length,
				 पूर्णांक final, पूर्णांक dma)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(dd->req);
	u32 val = length << 5, mask;

	अगर (likely(ctx->digcnt))
		omap_sham_ग_लिखो(dd, SHA_REG_DIGCNT(dd), ctx->digcnt);

	omap_sham_ग_लिखो_mask(dd, SHA_REG_MASK(dd),
		SHA_REG_MASK_IT_EN | (dma ? SHA_REG_MASK_DMA_EN : 0),
		SHA_REG_MASK_IT_EN | SHA_REG_MASK_DMA_EN);
	/*
	 * Setting ALGO_CONST only क्रम the first iteration
	 * and CLOSE_HASH only क्रम the last one.
	 */
	अगर ((ctx->flags & FLAGS_MODE_MASK) == FLAGS_MODE_SHA1)
		val |= SHA_REG_CTRL_ALGO;
	अगर (!ctx->digcnt)
		val |= SHA_REG_CTRL_ALGO_CONST;
	अगर (final)
		val |= SHA_REG_CTRL_CLOSE_HASH;

	mask = SHA_REG_CTRL_ALGO_CONST | SHA_REG_CTRL_CLOSE_HASH |
			SHA_REG_CTRL_ALGO | SHA_REG_CTRL_LENGTH;

	omap_sham_ग_लिखो_mask(dd, SHA_REG_CTRL, val, mask);
पूर्ण

अटल व्योम omap_sham_trigger_omap2(काष्ठा omap_sham_dev *dd, माप_प्रकार length)
अणु
पूर्ण

अटल पूर्णांक omap_sham_poll_irq_omap2(काष्ठा omap_sham_dev *dd)
अणु
	वापस omap_sham_रुको(dd, SHA_REG_CTRL, SHA_REG_CTRL_INPUT_READY);
पूर्ण

अटल पूर्णांक get_block_size(काष्ठा omap_sham_reqctx *ctx)
अणु
	पूर्णांक d;

	चयन (ctx->flags & FLAGS_MODE_MASK) अणु
	हाल FLAGS_MODE_MD5:
	हाल FLAGS_MODE_SHA1:
		d = SHA1_BLOCK_SIZE;
		अवरोध;
	हाल FLAGS_MODE_SHA224:
	हाल FLAGS_MODE_SHA256:
		d = SHA256_BLOCK_SIZE;
		अवरोध;
	हाल FLAGS_MODE_SHA384:
	हाल FLAGS_MODE_SHA512:
		d = SHA512_BLOCK_SIZE;
		अवरोध;
	शेष:
		d = 0;
	पूर्ण

	वापस d;
पूर्ण

अटल व्योम omap_sham_ग_लिखो_n(काष्ठा omap_sham_dev *dd, u32 offset,
				    u32 *value, पूर्णांक count)
अणु
	क्रम (; count--; value++, offset += 4)
		omap_sham_ग_लिखो(dd, offset, *value);
पूर्ण

अटल व्योम omap_sham_ग_लिखो_ctrl_omap4(काष्ठा omap_sham_dev *dd, माप_प्रकार length,
				 पूर्णांक final, पूर्णांक dma)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(dd->req);
	u32 val, mask;

	अगर (likely(ctx->digcnt))
		omap_sham_ग_लिखो(dd, SHA_REG_DIGCNT(dd), ctx->digcnt);

	/*
	 * Setting ALGO_CONST only क्रम the first iteration and
	 * CLOSE_HASH only क्रम the last one. Note that flags mode bits
	 * correspond to algorithm encoding in mode रेजिस्टर.
	 */
	val = (ctx->flags & FLAGS_MODE_MASK) >> (FLAGS_MODE_SHIFT);
	अगर (!ctx->digcnt) अणु
		काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(dd->req);
		काष्ठा omap_sham_ctx *tctx = crypto_ahash_ctx(tfm);
		काष्ठा omap_sham_hmac_ctx *bctx = tctx->base;
		पूर्णांक bs, nr_dr;

		val |= SHA_REG_MODE_ALGO_CONSTANT;

		अगर (ctx->flags & BIT(FLAGS_HMAC)) अणु
			bs = get_block_size(ctx);
			nr_dr = bs / (2 * माप(u32));
			val |= SHA_REG_MODE_HMAC_KEY_PROC;
			omap_sham_ग_लिखो_n(dd, SHA_REG_ODIGEST(dd, 0),
					  (u32 *)bctx->ipad, nr_dr);
			omap_sham_ग_लिखो_n(dd, SHA_REG_IDIGEST(dd, 0),
					  (u32 *)bctx->ipad + nr_dr, nr_dr);
			ctx->digcnt += bs;
		पूर्ण
	पूर्ण

	अगर (final) अणु
		val |= SHA_REG_MODE_CLOSE_HASH;

		अगर (ctx->flags & BIT(FLAGS_HMAC))
			val |= SHA_REG_MODE_HMAC_OUTER_HASH;
	पूर्ण

	mask = SHA_REG_MODE_ALGO_CONSTANT | SHA_REG_MODE_CLOSE_HASH |
	       SHA_REG_MODE_ALGO_MASK | SHA_REG_MODE_HMAC_OUTER_HASH |
	       SHA_REG_MODE_HMAC_KEY_PROC;

	dev_dbg(dd->dev, "ctrl: %08x, flags: %08lx\n", val, ctx->flags);
	omap_sham_ग_लिखो_mask(dd, SHA_REG_MODE(dd), val, mask);
	omap_sham_ग_लिखो(dd, SHA_REG_IRQENA, SHA_REG_IRQENA_OUTPUT_RDY);
	omap_sham_ग_लिखो_mask(dd, SHA_REG_MASK(dd),
			     SHA_REG_MASK_IT_EN |
				     (dma ? SHA_REG_MASK_DMA_EN : 0),
			     SHA_REG_MASK_IT_EN | SHA_REG_MASK_DMA_EN);
पूर्ण

अटल व्योम omap_sham_trigger_omap4(काष्ठा omap_sham_dev *dd, माप_प्रकार length)
अणु
	omap_sham_ग_लिखो(dd, SHA_REG_LENGTH(dd), length);
पूर्ण

अटल पूर्णांक omap_sham_poll_irq_omap4(काष्ठा omap_sham_dev *dd)
अणु
	वापस omap_sham_रुको(dd, SHA_REG_IRQSTATUS,
			      SHA_REG_IRQSTATUS_INPUT_RDY);
पूर्ण

अटल पूर्णांक omap_sham_xmit_cpu(काष्ठा omap_sham_dev *dd, माप_प्रकार length,
			      पूर्णांक final)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(dd->req);
	पूर्णांक count, len32, bs32, offset = 0;
	स्थिर u32 *buffer;
	पूर्णांक mlen;
	काष्ठा sg_mapping_iter mi;

	dev_dbg(dd->dev, "xmit_cpu: digcnt: %zd, length: %zd, final: %d\n",
						ctx->digcnt, length, final);

	dd->pdata->ग_लिखो_ctrl(dd, length, final, 0);
	dd->pdata->trigger(dd, length);

	/* should be non-zero beक्रमe next lines to disable घड़ीs later */
	ctx->digcnt += length;
	ctx->total -= length;

	अगर (final)
		set_bit(FLAGS_FINAL, &dd->flags); /* catch last पूर्णांकerrupt */

	set_bit(FLAGS_CPU, &dd->flags);

	len32 = DIV_ROUND_UP(length, माप(u32));
	bs32 = get_block_size(ctx) / माप(u32);

	sg_miter_start(&mi, ctx->sg, ctx->sg_len,
		       SG_MITER_FROM_SG | SG_MITER_ATOMIC);

	mlen = 0;

	जबतक (len32) अणु
		अगर (dd->pdata->poll_irq(dd))
			वापस -ETIMEDOUT;

		क्रम (count = 0; count < min(len32, bs32); count++, offset++) अणु
			अगर (!mlen) अणु
				sg_miter_next(&mi);
				mlen = mi.length;
				अगर (!mlen) अणु
					pr_err("sg miter failure.\n");
					वापस -EINVAL;
				पूर्ण
				offset = 0;
				buffer = mi.addr;
			पूर्ण
			omap_sham_ग_लिखो(dd, SHA_REG_DIN(dd, count),
					buffer[offset]);
			mlen -= 4;
		पूर्ण
		len32 -= min(len32, bs32);
	पूर्ण

	sg_miter_stop(&mi);

	वापस -EINPROGRESS;
पूर्ण

अटल व्योम omap_sham_dma_callback(व्योम *param)
अणु
	काष्ठा omap_sham_dev *dd = param;

	set_bit(FLAGS_DMA_READY, &dd->flags);
	tasklet_schedule(&dd->करोne_task);
पूर्ण

अटल पूर्णांक omap_sham_xmit_dma(काष्ठा omap_sham_dev *dd, माप_प्रकार length,
			      पूर्णांक final)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(dd->req);
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dma_slave_config cfg;
	पूर्णांक ret;

	dev_dbg(dd->dev, "xmit_dma: digcnt: %zd, length: %zd, final: %d\n",
						ctx->digcnt, length, final);

	अगर (!dma_map_sg(dd->dev, ctx->sg, ctx->sg_len, DMA_TO_DEVICE)) अणु
		dev_err(dd->dev, "dma_map_sg error\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&cfg, 0, माप(cfg));

	cfg.dst_addr = dd->phys_base + SHA_REG_DIN(dd, 0);
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.dst_maxburst = get_block_size(ctx) / DMA_SLAVE_BUSWIDTH_4_BYTES;

	ret = dmaengine_slave_config(dd->dma_lch, &cfg);
	अगर (ret) अणु
		pr_err("omap-sham: can't configure dmaengine slave: %d\n", ret);
		वापस ret;
	पूर्ण

	tx = dmaengine_prep_slave_sg(dd->dma_lch, ctx->sg, ctx->sg_len,
				     DMA_MEM_TO_DEV,
				     DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	अगर (!tx) अणु
		dev_err(dd->dev, "prep_slave_sg failed\n");
		वापस -EINVAL;
	पूर्ण

	tx->callback = omap_sham_dma_callback;
	tx->callback_param = dd;

	dd->pdata->ग_लिखो_ctrl(dd, length, final, 1);

	ctx->digcnt += length;
	ctx->total -= length;

	अगर (final)
		set_bit(FLAGS_FINAL, &dd->flags); /* catch last पूर्णांकerrupt */

	set_bit(FLAGS_DMA_ACTIVE, &dd->flags);

	dmaengine_submit(tx);
	dma_async_issue_pending(dd->dma_lch);

	dd->pdata->trigger(dd, length);

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक omap_sham_copy_sg_lists(काष्ठा omap_sham_reqctx *ctx,
				   काष्ठा scatterlist *sg, पूर्णांक bs, पूर्णांक new_len)
अणु
	पूर्णांक n = sg_nents(sg);
	काष्ठा scatterlist *पंचांगp;
	पूर्णांक offset = ctx->offset;

	ctx->total = new_len;

	अगर (ctx->bufcnt)
		n++;

	ctx->sg = kदो_स्मृति_array(n, माप(*sg), GFP_KERNEL);
	अगर (!ctx->sg)
		वापस -ENOMEM;

	sg_init_table(ctx->sg, n);

	पंचांगp = ctx->sg;

	ctx->sg_len = 0;

	अगर (ctx->bufcnt) अणु
		sg_set_buf(पंचांगp, ctx->dd->xmit_buf, ctx->bufcnt);
		पंचांगp = sg_next(पंचांगp);
		ctx->sg_len++;
		new_len -= ctx->bufcnt;
	पूर्ण

	जबतक (sg && new_len) अणु
		पूर्णांक len = sg->length - offset;

		अगर (len <= 0) अणु
			offset -= sg->length;
			sg = sg_next(sg);
			जारी;
		पूर्ण

		अगर (new_len < len)
			len = new_len;

		अगर (len > 0) अणु
			new_len -= len;
			sg_set_page(पंचांगp, sg_page(sg), len, sg->offset + offset);
			offset = 0;
			ctx->offset = 0;
			ctx->sg_len++;
			अगर (new_len <= 0)
				अवरोध;
			पंचांगp = sg_next(पंचांगp);
		पूर्ण

		sg = sg_next(sg);
	पूर्ण

	अगर (पंचांगp)
		sg_mark_end(पंचांगp);

	set_bit(FLAGS_SGS_ALLOCED, &ctx->dd->flags);

	ctx->offset += new_len - ctx->bufcnt;
	ctx->bufcnt = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sham_copy_sgs(काष्ठा omap_sham_reqctx *ctx,
			      काष्ठा scatterlist *sg, पूर्णांक bs,
			      अचिन्हित पूर्णांक new_len)
अणु
	पूर्णांक pages;
	व्योम *buf;

	pages = get_order(new_len);

	buf = (व्योम *)__get_मुक्त_pages(GFP_ATOMIC, pages);
	अगर (!buf) अणु
		pr_err("Couldn't allocate pages for unaligned cases.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (ctx->bufcnt)
		स_नकल(buf, ctx->dd->xmit_buf, ctx->bufcnt);

	scatterwalk_map_and_copy(buf + ctx->bufcnt, sg, ctx->offset,
				 min(new_len, ctx->total) - ctx->bufcnt, 0);
	sg_init_table(ctx->sgl, 1);
	sg_set_buf(ctx->sgl, buf, new_len);
	ctx->sg = ctx->sgl;
	set_bit(FLAGS_SGS_COPIED, &ctx->dd->flags);
	ctx->sg_len = 1;
	ctx->offset += new_len - ctx->bufcnt;
	ctx->bufcnt = 0;
	ctx->total = new_len;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sham_align_sgs(काष्ठा scatterlist *sg,
			       पूर्णांक nbytes, पूर्णांक bs, bool final,
			       काष्ठा omap_sham_reqctx *rctx)
अणु
	पूर्णांक n = 0;
	bool aligned = true;
	bool list_ok = true;
	काष्ठा scatterlist *sg_पंचांगp = sg;
	पूर्णांक new_len;
	पूर्णांक offset = rctx->offset;
	पूर्णांक bufcnt = rctx->bufcnt;

	अगर (!sg || !sg->length || !nbytes) अणु
		अगर (bufcnt) अणु
			bufcnt = DIV_ROUND_UP(bufcnt, bs) * bs;
			sg_init_table(rctx->sgl, 1);
			sg_set_buf(rctx->sgl, rctx->dd->xmit_buf, bufcnt);
			rctx->sg = rctx->sgl;
			rctx->sg_len = 1;
		पूर्ण

		वापस 0;
	पूर्ण

	new_len = nbytes;

	अगर (offset)
		list_ok = false;

	अगर (final)
		new_len = DIV_ROUND_UP(new_len, bs) * bs;
	अन्यथा
		new_len = (new_len - 1) / bs * bs;

	अगर (!new_len)
		वापस 0;

	अगर (nbytes != new_len)
		list_ok = false;

	जबतक (nbytes > 0 && sg_पंचांगp) अणु
		n++;

		अगर (bufcnt) अणु
			अगर (!IS_ALIGNED(bufcnt, bs)) अणु
				aligned = false;
				अवरोध;
			पूर्ण
			nbytes -= bufcnt;
			bufcnt = 0;
			अगर (!nbytes)
				list_ok = false;

			जारी;
		पूर्ण

#अगर_घोषित CONFIG_ZONE_DMA
		अगर (page_zonक्रमागत(sg_page(sg_पंचांगp)) != ZONE_DMA) अणु
			aligned = false;
			अवरोध;
		पूर्ण
#पूर्ण_अगर

		अगर (offset < sg_पंचांगp->length) अणु
			अगर (!IS_ALIGNED(offset + sg_पंचांगp->offset, 4)) अणु
				aligned = false;
				अवरोध;
			पूर्ण

			अगर (!IS_ALIGNED(sg_पंचांगp->length - offset, bs)) अणु
				aligned = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (offset) अणु
			offset -= sg_पंचांगp->length;
			अगर (offset < 0) अणु
				nbytes += offset;
				offset = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			nbytes -= sg_पंचांगp->length;
		पूर्ण

		sg_पंचांगp = sg_next(sg_पंचांगp);

		अगर (nbytes < 0) अणु
			list_ok = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (new_len > OMAP_SHA_MAX_DMA_LEN) अणु
		new_len = OMAP_SHA_MAX_DMA_LEN;
		aligned = false;
	पूर्ण

	अगर (!aligned)
		वापस omap_sham_copy_sgs(rctx, sg, bs, new_len);
	अन्यथा अगर (!list_ok)
		वापस omap_sham_copy_sg_lists(rctx, sg, bs, new_len);

	rctx->total = new_len;
	rctx->offset += new_len;
	rctx->sg_len = n;
	अगर (rctx->bufcnt) अणु
		sg_init_table(rctx->sgl, 2);
		sg_set_buf(rctx->sgl, rctx->dd->xmit_buf, rctx->bufcnt);
		sg_chain(rctx->sgl, 2, sg);
		rctx->sg = rctx->sgl;
	पूर्ण अन्यथा अणु
		rctx->sg = sg;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sham_prepare_request(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा ahash_request *req = container_of(areq, काष्ठा ahash_request,
						 base);
	काष्ठा omap_sham_reqctx *rctx = ahash_request_ctx(req);
	पूर्णांक bs;
	पूर्णांक ret;
	अचिन्हित पूर्णांक nbytes;
	bool final = rctx->flags & BIT(FLAGS_FINUP);
	bool update = rctx->op == OP_UPDATE;
	पूर्णांक hash_later;

	bs = get_block_size(rctx);

	nbytes = rctx->bufcnt;

	अगर (update)
		nbytes += req->nbytes - rctx->offset;

	dev_dbg(rctx->dd->dev,
		"%s: nbytes=%d, bs=%d, total=%d, offset=%d, bufcnt=%zd\n",
		__func__, nbytes, bs, rctx->total, rctx->offset,
		rctx->bufcnt);

	अगर (!nbytes)
		वापस 0;

	rctx->total = nbytes;

	अगर (update && req->nbytes && (!IS_ALIGNED(rctx->bufcnt, bs))) अणु
		पूर्णांक len = bs - rctx->bufcnt % bs;

		अगर (len > req->nbytes)
			len = req->nbytes;
		scatterwalk_map_and_copy(rctx->buffer + rctx->bufcnt, req->src,
					 0, len, 0);
		rctx->bufcnt += len;
		rctx->offset = len;
	पूर्ण

	अगर (rctx->bufcnt)
		स_नकल(rctx->dd->xmit_buf, rctx->buffer, rctx->bufcnt);

	ret = omap_sham_align_sgs(req->src, nbytes, bs, final, rctx);
	अगर (ret)
		वापस ret;

	hash_later = nbytes - rctx->total;
	अगर (hash_later < 0)
		hash_later = 0;

	अगर (hash_later && hash_later <= rctx->buflen) अणु
		scatterwalk_map_and_copy(rctx->buffer,
					 req->src,
					 req->nbytes - hash_later,
					 hash_later, 0);

		rctx->bufcnt = hash_later;
	पूर्ण अन्यथा अणु
		rctx->bufcnt = 0;
	पूर्ण

	अगर (hash_later > rctx->buflen)
		set_bit(FLAGS_HUGE, &rctx->dd->flags);

	rctx->total = min(nbytes, rctx->total);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sham_update_dma_stop(काष्ठा omap_sham_dev *dd)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(dd->req);

	dma_unmap_sg(dd->dev, ctx->sg, ctx->sg_len, DMA_TO_DEVICE);

	clear_bit(FLAGS_DMA_ACTIVE, &dd->flags);

	वापस 0;
पूर्ण

अटल काष्ठा omap_sham_dev *omap_sham_find_dev(काष्ठा omap_sham_reqctx *ctx)
अणु
	काष्ठा omap_sham_dev *dd;

	अगर (ctx->dd)
		वापस ctx->dd;

	spin_lock_bh(&sham.lock);
	dd = list_first_entry(&sham.dev_list, काष्ठा omap_sham_dev, list);
	list_move_tail(&dd->list, &sham.dev_list);
	ctx->dd = dd;
	spin_unlock_bh(&sham.lock);

	वापस dd;
पूर्ण

अटल पूर्णांक omap_sham_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा omap_sham_ctx *tctx = crypto_ahash_ctx(tfm);
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा omap_sham_dev *dd;
	पूर्णांक bs = 0;

	ctx->dd = शून्य;

	dd = omap_sham_find_dev(ctx);
	अगर (!dd)
		वापस -ENODEV;

	ctx->flags = 0;

	dev_dbg(dd->dev, "init: digest size: %d\n",
		crypto_ahash_digestsize(tfm));

	चयन (crypto_ahash_digestsize(tfm)) अणु
	हाल MD5_DIGEST_SIZE:
		ctx->flags |= FLAGS_MODE_MD5;
		bs = SHA1_BLOCK_SIZE;
		अवरोध;
	हाल SHA1_DIGEST_SIZE:
		ctx->flags |= FLAGS_MODE_SHA1;
		bs = SHA1_BLOCK_SIZE;
		अवरोध;
	हाल SHA224_DIGEST_SIZE:
		ctx->flags |= FLAGS_MODE_SHA224;
		bs = SHA224_BLOCK_SIZE;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		ctx->flags |= FLAGS_MODE_SHA256;
		bs = SHA256_BLOCK_SIZE;
		अवरोध;
	हाल SHA384_DIGEST_SIZE:
		ctx->flags |= FLAGS_MODE_SHA384;
		bs = SHA384_BLOCK_SIZE;
		अवरोध;
	हाल SHA512_DIGEST_SIZE:
		ctx->flags |= FLAGS_MODE_SHA512;
		bs = SHA512_BLOCK_SIZE;
		अवरोध;
	पूर्ण

	ctx->bufcnt = 0;
	ctx->digcnt = 0;
	ctx->total = 0;
	ctx->offset = 0;
	ctx->buflen = BUFLEN;

	अगर (tctx->flags & BIT(FLAGS_HMAC)) अणु
		अगर (!test_bit(FLAGS_AUTO_XOR, &dd->flags)) अणु
			काष्ठा omap_sham_hmac_ctx *bctx = tctx->base;

			स_नकल(ctx->buffer, bctx->ipad, bs);
			ctx->bufcnt = bs;
		पूर्ण

		ctx->flags |= BIT(FLAGS_HMAC);
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक omap_sham_update_req(काष्ठा omap_sham_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err;
	bool final = (ctx->flags & BIT(FLAGS_FINUP)) &&
		!(dd->flags & BIT(FLAGS_HUGE));

	dev_dbg(dd->dev, "update_req: total: %u, digcnt: %zd, final: %d",
		ctx->total, ctx->digcnt, final);

	अगर (ctx->total < get_block_size(ctx) ||
	    ctx->total < dd->fallback_sz)
		ctx->flags |= BIT(FLAGS_CPU);

	अगर (ctx->flags & BIT(FLAGS_CPU))
		err = omap_sham_xmit_cpu(dd, ctx->total, final);
	अन्यथा
		err = omap_sham_xmit_dma(dd, ctx->total, final);

	/* रुको क्रम dma completion beक्रमe can take more data */
	dev_dbg(dd->dev, "update: err: %d, digcnt: %zd\n", err, ctx->digcnt);

	वापस err;
पूर्ण

अटल पूर्णांक omap_sham_final_req(काष्ठा omap_sham_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err = 0, use_dma = 1;

	अगर (dd->flags & BIT(FLAGS_HUGE))
		वापस 0;

	अगर ((ctx->total <= get_block_size(ctx)) || dd->polling_mode)
		/*
		 * faster to handle last block with cpu or
		 * use cpu when dma is not present.
		 */
		use_dma = 0;

	अगर (use_dma)
		err = omap_sham_xmit_dma(dd, ctx->total, 1);
	अन्यथा
		err = omap_sham_xmit_cpu(dd, ctx->total, 1);

	ctx->bufcnt = 0;

	dev_dbg(dd->dev, "final_req: err: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक omap_sham_hash_one_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा ahash_request *req = container_of(areq, काष्ठा ahash_request,
						 base);
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा omap_sham_dev *dd = ctx->dd;
	पूर्णांक err;
	bool final = (ctx->flags & BIT(FLAGS_FINUP)) &&
			!(dd->flags & BIT(FLAGS_HUGE));

	dev_dbg(dd->dev, "hash-one: op: %u, total: %u, digcnt: %zd, final: %d",
		ctx->op, ctx->total, ctx->digcnt, final);

	dd->req = req;

	err = omap_sham_hw_init(dd);
	अगर (err)
		वापस err;

	अगर (ctx->digcnt)
		dd->pdata->copy_hash(req, 0);

	अगर (ctx->op == OP_UPDATE)
		err = omap_sham_update_req(dd);
	अन्यथा अगर (ctx->op == OP_FINAL)
		err = omap_sham_final_req(dd);

	अगर (err != -EINPROGRESS)
		omap_sham_finish_req(req, err);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sham_finish_hmac(काष्ठा ahash_request *req)
अणु
	काष्ठा omap_sham_ctx *tctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा omap_sham_hmac_ctx *bctx = tctx->base;
	पूर्णांक bs = crypto_shash_blocksize(bctx->shash);
	पूर्णांक ds = crypto_shash_digestsize(bctx->shash);
	SHASH_DESC_ON_STACK(shash, bctx->shash);

	shash->tfm = bctx->shash;

	वापस crypto_shash_init(shash) ?:
	       crypto_shash_update(shash, bctx->opad, bs) ?:
	       crypto_shash_finup(shash, req->result, ds, req->result);
पूर्ण

अटल पूर्णांक omap_sham_finish(काष्ठा ahash_request *req)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा omap_sham_dev *dd = ctx->dd;
	पूर्णांक err = 0;

	अगर (ctx->digcnt) अणु
		omap_sham_copy_पढ़ोy_hash(req);
		अगर ((ctx->flags & BIT(FLAGS_HMAC)) &&
				!test_bit(FLAGS_AUTO_XOR, &dd->flags))
			err = omap_sham_finish_hmac(req);
	पूर्ण

	dev_dbg(dd->dev, "digcnt: %zd, bufcnt: %zd\n", ctx->digcnt, ctx->bufcnt);

	वापस err;
पूर्ण

अटल व्योम omap_sham_finish_req(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा omap_sham_dev *dd = ctx->dd;

	अगर (test_bit(FLAGS_SGS_COPIED, &dd->flags))
		मुक्त_pages((अचिन्हित दीर्घ)sg_virt(ctx->sg),
			   get_order(ctx->sg->length));

	अगर (test_bit(FLAGS_SGS_ALLOCED, &dd->flags))
		kमुक्त(ctx->sg);

	ctx->sg = शून्य;

	dd->flags &= ~(BIT(FLAGS_SGS_ALLOCED) | BIT(FLAGS_SGS_COPIED) |
		       BIT(FLAGS_CPU) | BIT(FLAGS_DMA_READY) |
		       BIT(FLAGS_OUTPUT_READY));

	अगर (!err)
		dd->pdata->copy_hash(req, 1);

	अगर (dd->flags & BIT(FLAGS_HUGE)) अणु
		/* Re-enqueue the request */
		omap_sham_enqueue(req, ctx->op);
		वापस;
	पूर्ण

	अगर (!err) अणु
		अगर (test_bit(FLAGS_FINAL, &dd->flags))
			err = omap_sham_finish(req);
	पूर्ण अन्यथा अणु
		ctx->flags |= BIT(FLAGS_ERROR);
	पूर्ण

	/* atomic operation is not needed here */
	dd->flags &= ~(BIT(FLAGS_FINAL) | BIT(FLAGS_CPU) |
			BIT(FLAGS_DMA_READY) | BIT(FLAGS_OUTPUT_READY));

	pm_runसमय_mark_last_busy(dd->dev);
	pm_runसमय_put_स्वतःsuspend(dd->dev);

	ctx->offset = 0;

	crypto_finalize_hash_request(dd->engine, req, err);
पूर्ण

अटल पूर्णांक omap_sham_handle_queue(काष्ठा omap_sham_dev *dd,
				  काष्ठा ahash_request *req)
अणु
	वापस crypto_transfer_hash_request_to_engine(dd->engine, req);
पूर्ण

अटल पूर्णांक omap_sham_enqueue(काष्ठा ahash_request *req, अचिन्हित पूर्णांक op)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा omap_sham_dev *dd = ctx->dd;

	ctx->op = op;

	वापस omap_sham_handle_queue(dd, req);
पूर्ण

अटल पूर्णांक omap_sham_update(काष्ठा ahash_request *req)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा omap_sham_dev *dd = omap_sham_find_dev(ctx);

	अगर (!req->nbytes)
		वापस 0;

	अगर (ctx->bufcnt + req->nbytes <= ctx->buflen) अणु
		scatterwalk_map_and_copy(ctx->buffer + ctx->bufcnt, req->src,
					 0, req->nbytes, 0);
		ctx->bufcnt += req->nbytes;
		वापस 0;
	पूर्ण

	अगर (dd->polling_mode)
		ctx->flags |= BIT(FLAGS_CPU);

	वापस omap_sham_enqueue(req, OP_UPDATE);
पूर्ण

अटल पूर्णांक omap_sham_final_shash(काष्ठा ahash_request *req)
अणु
	काष्ठा omap_sham_ctx *tctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक offset = 0;

	/*
	 * If we are running HMAC on limited hardware support, skip
	 * the ipad in the beginning of the buffer अगर we are going क्रम
	 * software fallback algorithm.
	 */
	अगर (test_bit(FLAGS_HMAC, &ctx->flags) &&
	    !test_bit(FLAGS_AUTO_XOR, &ctx->dd->flags))
		offset = get_block_size(ctx);

	वापस crypto_shash_tfm_digest(tctx->fallback, ctx->buffer + offset,
				       ctx->bufcnt - offset, req->result);
पूर्ण

अटल पूर्णांक omap_sham_final(काष्ठा ahash_request *req)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);

	ctx->flags |= BIT(FLAGS_FINUP);

	अगर (ctx->flags & BIT(FLAGS_ERROR))
		वापस 0; /* uncompleted hash is not needed */

	/*
	 * OMAP HW accel works only with buffers >= 9.
	 * HMAC is always >= 9 because ipad == block size.
	 * If buffersize is less than fallback_sz, we use fallback
	 * SW encoding, as using DMA + HW in this हाल करोesn't provide
	 * any benefit.
	 */
	अगर (!ctx->digcnt && ctx->bufcnt < ctx->dd->fallback_sz)
		वापस omap_sham_final_shash(req);
	अन्यथा अगर (ctx->bufcnt)
		वापस omap_sham_enqueue(req, OP_FINAL);

	/* copy पढ़ोy hash (+ finalize hmac) */
	वापस omap_sham_finish(req);
पूर्ण

अटल पूर्णांक omap_sham_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा omap_sham_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err1, err2;

	ctx->flags |= BIT(FLAGS_FINUP);

	err1 = omap_sham_update(req);
	अगर (err1 == -EINPROGRESS || err1 == -EBUSY)
		वापस err1;
	/*
	 * final() has to be always called to cleanup resources
	 * even अगर udpate() failed, except EINPROGRESS
	 */
	err2 = omap_sham_final(req);

	वापस err1 ?: err2;
पूर्ण

अटल पूर्णांक omap_sham_digest(काष्ठा ahash_request *req)
अणु
	वापस omap_sham_init(req) ?: omap_sham_finup(req);
पूर्ण

अटल पूर्णांक omap_sham_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा omap_sham_ctx *tctx = crypto_ahash_ctx(tfm);
	काष्ठा omap_sham_hmac_ctx *bctx = tctx->base;
	पूर्णांक bs = crypto_shash_blocksize(bctx->shash);
	पूर्णांक ds = crypto_shash_digestsize(bctx->shash);
	पूर्णांक err, i;

	err = crypto_shash_setkey(tctx->fallback, key, keylen);
	अगर (err)
		वापस err;

	अगर (keylen > bs) अणु
		err = crypto_shash_tfm_digest(bctx->shash, key, keylen,
					      bctx->ipad);
		अगर (err)
			वापस err;
		keylen = ds;
	पूर्ण अन्यथा अणु
		स_नकल(bctx->ipad, key, keylen);
	पूर्ण

	स_रखो(bctx->ipad + keylen, 0, bs - keylen);

	अगर (!test_bit(FLAGS_AUTO_XOR, &sham.flags)) अणु
		स_नकल(bctx->opad, bctx->ipad, bs);

		क्रम (i = 0; i < bs; i++) अणु
			bctx->ipad[i] ^= HMAC_IPAD_VALUE;
			bctx->opad[i] ^= HMAC_OPAD_VALUE;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक omap_sham_cra_init_alg(काष्ठा crypto_tfm *tfm, स्थिर अक्षर *alg_base)
अणु
	काष्ठा omap_sham_ctx *tctx = crypto_tfm_ctx(tfm);
	स्थिर अक्षर *alg_name = crypto_tfm_alg_name(tfm);

	/* Allocate a fallback and पात अगर it failed. */
	tctx->fallback = crypto_alloc_shash(alg_name, 0,
					    CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(tctx->fallback)) अणु
		pr_err("omap-sham: fallback driver '%s' "
				"could not be loaded.\n", alg_name);
		वापस PTR_ERR(tctx->fallback);
	पूर्ण

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा omap_sham_reqctx) + BUFLEN);

	अगर (alg_base) अणु
		काष्ठा omap_sham_hmac_ctx *bctx = tctx->base;
		tctx->flags |= BIT(FLAGS_HMAC);
		bctx->shash = crypto_alloc_shash(alg_base, 0,
						CRYPTO_ALG_NEED_FALLBACK);
		अगर (IS_ERR(bctx->shash)) अणु
			pr_err("omap-sham: base driver '%s' "
					"could not be loaded.\n", alg_base);
			crypto_मुक्त_shash(tctx->fallback);
			वापस PTR_ERR(bctx->shash);
		पूर्ण

	पूर्ण

	tctx->enginectx.op.करो_one_request = omap_sham_hash_one_req;
	tctx->enginectx.op.prepare_request = omap_sham_prepare_request;
	tctx->enginectx.op.unprepare_request = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sham_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस omap_sham_cra_init_alg(tfm, शून्य);
पूर्ण

अटल पूर्णांक omap_sham_cra_sha1_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस omap_sham_cra_init_alg(tfm, "sha1");
पूर्ण

अटल पूर्णांक omap_sham_cra_sha224_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस omap_sham_cra_init_alg(tfm, "sha224");
पूर्ण

अटल पूर्णांक omap_sham_cra_sha256_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस omap_sham_cra_init_alg(tfm, "sha256");
पूर्ण

अटल पूर्णांक omap_sham_cra_md5_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस omap_sham_cra_init_alg(tfm, "md5");
पूर्ण

अटल पूर्णांक omap_sham_cra_sha384_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस omap_sham_cra_init_alg(tfm, "sha384");
पूर्ण

अटल पूर्णांक omap_sham_cra_sha512_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस omap_sham_cra_init_alg(tfm, "sha512");
पूर्ण

अटल व्योम omap_sham_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा omap_sham_ctx *tctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_shash(tctx->fallback);
	tctx->fallback = शून्य;

	अगर (tctx->flags & BIT(FLAGS_HMAC)) अणु
		काष्ठा omap_sham_hmac_ctx *bctx = tctx->base;
		crypto_मुक्त_shash(bctx->shash);
	पूर्ण
पूर्ण

अटल पूर्णांक omap_sham_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा omap_sham_reqctx *rctx = ahash_request_ctx(req);

	स_नकल(out, rctx, माप(*rctx) + rctx->bufcnt);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sham_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा omap_sham_reqctx *rctx = ahash_request_ctx(req);
	स्थिर काष्ठा omap_sham_reqctx *ctx_in = in;

	स_नकल(rctx, in, माप(*rctx) + ctx_in->bufcnt);

	वापस 0;
पूर्ण

अटल काष्ठा ahash_alg algs_sha1_md5[] = अणु
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.halg.digestsize	= SHA1_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "sha1",
		.cra_driver_name	= "omap-sha1",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA1_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.halg.digestsize	= MD5_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "md5",
		.cra_driver_name	= "omap-md5",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA1_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.setkey		= omap_sham_setkey,
	.halg.digestsize	= SHA1_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "hmac(sha1)",
		.cra_driver_name	= "omap-hmac-sha1",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA1_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx) +
					माप(काष्ठा omap_sham_hmac_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_sha1_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.setkey		= omap_sham_setkey,
	.halg.digestsize	= MD5_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "hmac(md5)",
		.cra_driver_name	= "omap-hmac-md5",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA1_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx) +
					माप(काष्ठा omap_sham_hmac_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_md5_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण
पूर्ण;

/* OMAP4 has some algs in addition to what OMAP2 has */
अटल काष्ठा ahash_alg algs_sha224_sha256[] = अणु
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.halg.digestsize	= SHA224_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "sha224",
		.cra_driver_name	= "omap-sha224",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA224_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.halg.digestsize	= SHA256_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "sha256",
		.cra_driver_name	= "omap-sha256",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA256_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.setkey		= omap_sham_setkey,
	.halg.digestsize	= SHA224_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "hmac(sha224)",
		.cra_driver_name	= "omap-hmac-sha224",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA224_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx) +
					माप(काष्ठा omap_sham_hmac_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_sha224_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.setkey		= omap_sham_setkey,
	.halg.digestsize	= SHA256_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "hmac(sha256)",
		.cra_driver_name	= "omap-hmac-sha256",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA256_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx) +
					माप(काष्ठा omap_sham_hmac_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_sha256_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
पूर्ण;

अटल काष्ठा ahash_alg algs_sha384_sha512[] = अणु
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.halg.digestsize	= SHA384_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "sha384",
		.cra_driver_name	= "omap-sha384",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA384_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.halg.digestsize	= SHA512_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "sha512",
		.cra_driver_name	= "omap-sha512",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA512_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.setkey		= omap_sham_setkey,
	.halg.digestsize	= SHA384_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "hmac(sha384)",
		.cra_driver_name	= "omap-hmac-sha384",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA384_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx) +
					माप(काष्ठा omap_sham_hmac_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_sha384_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= omap_sham_init,
	.update		= omap_sham_update,
	.final		= omap_sham_final,
	.finup		= omap_sham_finup,
	.digest		= omap_sham_digest,
	.setkey		= omap_sham_setkey,
	.halg.digestsize	= SHA512_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "hmac(sha512)",
		.cra_driver_name	= "omap-hmac-sha512",
		.cra_priority		= 400,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA512_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा omap_sham_ctx) +
					माप(काष्ठा omap_sham_hmac_ctx),
		.cra_alignmask		= OMAP_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= omap_sham_cra_sha512_init,
		.cra_निकास		= omap_sham_cra_निकास,
	पूर्ण
पूर्ण,
पूर्ण;

अटल व्योम omap_sham_करोne_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा omap_sham_dev *dd = (काष्ठा omap_sham_dev *)data;
	पूर्णांक err = 0;

	dev_dbg(dd->dev, "%s: flags=%lx\n", __func__, dd->flags);

	अगर (test_bit(FLAGS_CPU, &dd->flags)) अणु
		अगर (test_and_clear_bit(FLAGS_OUTPUT_READY, &dd->flags))
			जाओ finish;
	पूर्ण अन्यथा अगर (test_bit(FLAGS_DMA_READY, &dd->flags)) अणु
		अगर (test_and_clear_bit(FLAGS_DMA_ACTIVE, &dd->flags)) अणु
			omap_sham_update_dma_stop(dd);
			अगर (dd->err) अणु
				err = dd->err;
				जाओ finish;
			पूर्ण
		पूर्ण
		अगर (test_and_clear_bit(FLAGS_OUTPUT_READY, &dd->flags)) अणु
			/* hash or semi-hash पढ़ोy */
			clear_bit(FLAGS_DMA_READY, &dd->flags);
			जाओ finish;
		पूर्ण
	पूर्ण

	वापस;

finish:
	dev_dbg(dd->dev, "update done: err: %d\n", err);
	/* finish curent request */
	omap_sham_finish_req(dd->req, err);
पूर्ण

अटल irqवापस_t omap_sham_irq_common(काष्ठा omap_sham_dev *dd)
अणु
	set_bit(FLAGS_OUTPUT_READY, &dd->flags);
	tasklet_schedule(&dd->करोne_task);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t omap_sham_irq_omap2(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_sham_dev *dd = dev_id;

	अगर (unlikely(test_bit(FLAGS_FINAL, &dd->flags)))
		/* final -> allow device to go to घातer-saving mode */
		omap_sham_ग_लिखो_mask(dd, SHA_REG_CTRL, 0, SHA_REG_CTRL_LENGTH);

	omap_sham_ग_लिखो_mask(dd, SHA_REG_CTRL, SHA_REG_CTRL_OUTPUT_READY,
				 SHA_REG_CTRL_OUTPUT_READY);
	omap_sham_पढ़ो(dd, SHA_REG_CTRL);

	वापस omap_sham_irq_common(dd);
पूर्ण

अटल irqवापस_t omap_sham_irq_omap4(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_sham_dev *dd = dev_id;

	omap_sham_ग_लिखो_mask(dd, SHA_REG_MASK(dd), 0, SHA_REG_MASK_IT_EN);

	वापस omap_sham_irq_common(dd);
पूर्ण

अटल काष्ठा omap_sham_algs_info omap_sham_algs_info_omap2[] = अणु
	अणु
		.algs_list	= algs_sha1_md5,
		.size		= ARRAY_SIZE(algs_sha1_md5),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_sham_pdata omap_sham_pdata_omap2 = अणु
	.algs_info	= omap_sham_algs_info_omap2,
	.algs_info_size	= ARRAY_SIZE(omap_sham_algs_info_omap2),
	.flags		= BIT(FLAGS_BE32_SHA1),
	.digest_size	= SHA1_DIGEST_SIZE,
	.copy_hash	= omap_sham_copy_hash_omap2,
	.ग_लिखो_ctrl	= omap_sham_ग_लिखो_ctrl_omap2,
	.trigger	= omap_sham_trigger_omap2,
	.poll_irq	= omap_sham_poll_irq_omap2,
	.पूर्णांकr_hdlr	= omap_sham_irq_omap2,
	.idigest_ofs	= 0x00,
	.din_ofs	= 0x1c,
	.digcnt_ofs	= 0x14,
	.rev_ofs	= 0x5c,
	.mask_ofs	= 0x60,
	.sysstatus_ofs	= 0x64,
	.major_mask	= 0xf0,
	.major_shअगरt	= 4,
	.minor_mask	= 0x0f,
	.minor_shअगरt	= 0,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा omap_sham_algs_info omap_sham_algs_info_omap4[] = अणु
	अणु
		.algs_list	= algs_sha1_md5,
		.size		= ARRAY_SIZE(algs_sha1_md5),
	पूर्ण,
	अणु
		.algs_list	= algs_sha224_sha256,
		.size		= ARRAY_SIZE(algs_sha224_sha256),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_sham_pdata omap_sham_pdata_omap4 = अणु
	.algs_info	= omap_sham_algs_info_omap4,
	.algs_info_size	= ARRAY_SIZE(omap_sham_algs_info_omap4),
	.flags		= BIT(FLAGS_AUTO_XOR),
	.digest_size	= SHA256_DIGEST_SIZE,
	.copy_hash	= omap_sham_copy_hash_omap4,
	.ग_लिखो_ctrl	= omap_sham_ग_लिखो_ctrl_omap4,
	.trigger	= omap_sham_trigger_omap4,
	.poll_irq	= omap_sham_poll_irq_omap4,
	.पूर्णांकr_hdlr	= omap_sham_irq_omap4,
	.idigest_ofs	= 0x020,
	.odigest_ofs	= 0x0,
	.din_ofs	= 0x080,
	.digcnt_ofs	= 0x040,
	.rev_ofs	= 0x100,
	.mask_ofs	= 0x110,
	.sysstatus_ofs	= 0x114,
	.mode_ofs	= 0x44,
	.length_ofs	= 0x48,
	.major_mask	= 0x0700,
	.major_shअगरt	= 8,
	.minor_mask	= 0x003f,
	.minor_shअगरt	= 0,
पूर्ण;

अटल काष्ठा omap_sham_algs_info omap_sham_algs_info_omap5[] = अणु
	अणु
		.algs_list	= algs_sha1_md5,
		.size		= ARRAY_SIZE(algs_sha1_md5),
	पूर्ण,
	अणु
		.algs_list	= algs_sha224_sha256,
		.size		= ARRAY_SIZE(algs_sha224_sha256),
	पूर्ण,
	अणु
		.algs_list	= algs_sha384_sha512,
		.size		= ARRAY_SIZE(algs_sha384_sha512),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_sham_pdata omap_sham_pdata_omap5 = अणु
	.algs_info	= omap_sham_algs_info_omap5,
	.algs_info_size	= ARRAY_SIZE(omap_sham_algs_info_omap5),
	.flags		= BIT(FLAGS_AUTO_XOR),
	.digest_size	= SHA512_DIGEST_SIZE,
	.copy_hash	= omap_sham_copy_hash_omap4,
	.ग_लिखो_ctrl	= omap_sham_ग_लिखो_ctrl_omap4,
	.trigger	= omap_sham_trigger_omap4,
	.poll_irq	= omap_sham_poll_irq_omap4,
	.पूर्णांकr_hdlr	= omap_sham_irq_omap4,
	.idigest_ofs	= 0x240,
	.odigest_ofs	= 0x200,
	.din_ofs	= 0x080,
	.digcnt_ofs	= 0x280,
	.rev_ofs	= 0x100,
	.mask_ofs	= 0x110,
	.sysstatus_ofs	= 0x114,
	.mode_ofs	= 0x284,
	.length_ofs	= 0x288,
	.major_mask	= 0x0700,
	.major_shअगरt	= 8,
	.minor_mask	= 0x003f,
	.minor_shअगरt	= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_sham_of_match[] = अणु
	अणु
		.compatible	= "ti,omap2-sham",
		.data		= &omap_sham_pdata_omap2,
	पूर्ण,
	अणु
		.compatible	= "ti,omap3-sham",
		.data		= &omap_sham_pdata_omap2,
	पूर्ण,
	अणु
		.compatible	= "ti,omap4-sham",
		.data		= &omap_sham_pdata_omap4,
	पूर्ण,
	अणु
		.compatible	= "ti,omap5-sham",
		.data		= &omap_sham_pdata_omap5,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_sham_of_match);

अटल पूर्णांक omap_sham_get_res_of(काष्ठा omap_sham_dev *dd,
		काष्ठा device *dev, काष्ठा resource *res)
अणु
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक err = 0;

	dd->pdata = of_device_get_match_data(dev);
	अगर (!dd->pdata) अणु
		dev_err(dev, "no compatible OF match\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

	err = of_address_to_resource(node, 0, res);
	अगर (err < 0) अणु
		dev_err(dev, "can't translate OF node address\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

	dd->irq = irq_of_parse_and_map(node, 0);
	अगर (!dd->irq) अणु
		dev_err(dev, "can't translate OF irq value\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

err:
	वापस err;
पूर्ण
#अन्यथा
अटल स्थिर काष्ठा of_device_id omap_sham_of_match[] = अणु
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक omap_sham_get_res_of(काष्ठा omap_sham_dev *dd,
		काष्ठा device *dev, काष्ठा resource *res)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omap_sham_get_res_pdev(काष्ठा omap_sham_dev *dd,
		काष्ठा platक्रमm_device *pdev, काष्ठा resource *res)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *r;
	पूर्णांक err = 0;

	/* Get the base address */
	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(dev, "no MEM resource info\n");
		err = -ENODEV;
		जाओ err;
	पूर्ण
	स_नकल(res, r, माप(*res));

	/* Get the IRQ */
	dd->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dd->irq < 0) अणु
		err = dd->irq;
		जाओ err;
	पूर्ण

	/* Only OMAP2/3 can be non-DT */
	dd->pdata = &omap_sham_pdata_omap2;

err:
	वापस err;
पूर्ण

अटल sमाप_प्रकार fallback_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा omap_sham_dev *dd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dd->fallback_sz);
पूर्ण

अटल sमाप_प्रकार fallback_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा omap_sham_dev *dd = dev_get_drvdata(dev);
	sमाप_प्रकार status;
	दीर्घ value;

	status = kम_से_दीर्घ(buf, 0, &value);
	अगर (status)
		वापस status;

	/* HW accelerator only works with buffers > 9 */
	अगर (value < 9) अणु
		dev_err(dev, "minimum fallback size 9\n");
		वापस -EINVAL;
	पूर्ण

	dd->fallback_sz = value;

	वापस size;
पूर्ण

अटल sमाप_प्रकार queue_len_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा omap_sham_dev *dd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dd->queue.max_qlen);
पूर्ण

अटल sमाप_प्रकार queue_len_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार size)
अणु
	काष्ठा omap_sham_dev *dd = dev_get_drvdata(dev);
	sमाप_प्रकार status;
	दीर्घ value;

	status = kम_से_दीर्घ(buf, 0, &value);
	अगर (status)
		वापस status;

	अगर (value < 1)
		वापस -EINVAL;

	/*
	 * Changing the queue size in fly is safe, अगर size becomes smaller
	 * than current size, it will just not accept new entries until
	 * it has shrank enough.
	 */
	dd->queue.max_qlen = value;

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(queue_len);
अटल DEVICE_ATTR_RW(fallback);

अटल काष्ठा attribute *omap_sham_attrs[] = अणु
	&dev_attr_queue_len.attr,
	&dev_attr_fallback.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group omap_sham_attr_group = अणु
	.attrs = omap_sham_attrs,
पूर्ण;

अटल पूर्णांक omap_sham_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_sham_dev *dd;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource res;
	dma_cap_mask_t mask;
	पूर्णांक err, i, j;
	u32 rev;

	dd = devm_kzalloc(dev, माप(काष्ठा omap_sham_dev), GFP_KERNEL);
	अगर (dd == शून्य) अणु
		dev_err(dev, "unable to alloc data struct.\n");
		err = -ENOMEM;
		जाओ data_err;
	पूर्ण
	dd->dev = dev;
	platक्रमm_set_drvdata(pdev, dd);

	INIT_LIST_HEAD(&dd->list);
	tasklet_init(&dd->करोne_task, omap_sham_करोne_task, (अचिन्हित दीर्घ)dd);
	crypto_init_queue(&dd->queue, OMAP_SHAM_QUEUE_LENGTH);

	err = (dev->of_node) ? omap_sham_get_res_of(dd, dev, &res) :
			       omap_sham_get_res_pdev(dd, pdev, &res);
	अगर (err)
		जाओ data_err;

	dd->io_base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(dd->io_base)) अणु
		err = PTR_ERR(dd->io_base);
		जाओ data_err;
	पूर्ण
	dd->phys_base = res.start;

	err = devm_request_irq(dev, dd->irq, dd->pdata->पूर्णांकr_hdlr,
			       IRQF_TRIGGER_NONE, dev_name(dev), dd);
	अगर (err) अणु
		dev_err(dev, "unable to request irq %d, err = %d\n",
			dd->irq, err);
		जाओ data_err;
	पूर्ण

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	dd->dma_lch = dma_request_chan(dev, "rx");
	अगर (IS_ERR(dd->dma_lch)) अणु
		err = PTR_ERR(dd->dma_lch);
		अगर (err == -EPROBE_DEFER)
			जाओ data_err;

		dd->polling_mode = 1;
		dev_dbg(dev, "using polling mode instead of dma\n");
	पूर्ण

	dd->flags |= dd->pdata->flags;
	sham.flags |= dd->pdata->flags;

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, DEFAULT_AUTOSUSPEND_DELAY);

	dd->fallback_sz = OMAP_SHA_DMA_THRESHOLD;

	pm_runसमय_enable(dev);
	pm_runसमय_irq_safe(dev);

	err = pm_runसमय_get_sync(dev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get sync: %d\n", err);
		जाओ err_pm;
	पूर्ण

	rev = omap_sham_पढ़ो(dd, SHA_REG_REV(dd));
	pm_runसमय_put_sync(&pdev->dev);

	dev_info(dev, "hw accel on OMAP rev %u.%u\n",
		(rev & dd->pdata->major_mask) >> dd->pdata->major_shअगरt,
		(rev & dd->pdata->minor_mask) >> dd->pdata->minor_shअगरt);

	spin_lock(&sham.lock);
	list_add_tail(&dd->list, &sham.dev_list);
	spin_unlock(&sham.lock);

	dd->engine = crypto_engine_alloc_init(dev, 1);
	अगर (!dd->engine) अणु
		err = -ENOMEM;
		जाओ err_engine;
	पूर्ण

	err = crypto_engine_start(dd->engine);
	अगर (err)
		जाओ err_engine_start;

	क्रम (i = 0; i < dd->pdata->algs_info_size; i++) अणु
		अगर (dd->pdata->algs_info[i].रेजिस्टरed)
			अवरोध;

		क्रम (j = 0; j < dd->pdata->algs_info[i].size; j++) अणु
			काष्ठा ahash_alg *alg;

			alg = &dd->pdata->algs_info[i].algs_list[j];
			alg->export = omap_sham_export;
			alg->import = omap_sham_import;
			alg->halg.statesize = माप(काष्ठा omap_sham_reqctx) +
					      BUFLEN;
			err = crypto_रेजिस्टर_ahash(alg);
			अगर (err)
				जाओ err_algs;

			dd->pdata->algs_info[i].रेजिस्टरed++;
		पूर्ण
	पूर्ण

	err = sysfs_create_group(&dev->kobj, &omap_sham_attr_group);
	अगर (err) अणु
		dev_err(dev, "could not create sysfs device attrs\n");
		जाओ err_algs;
	पूर्ण

	वापस 0;

err_algs:
	क्रम (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		क्रम (j = dd->pdata->algs_info[i].रेजिस्टरed - 1; j >= 0; j--)
			crypto_unरेजिस्टर_ahash(
					&dd->pdata->algs_info[i].algs_list[j]);
err_engine_start:
	crypto_engine_निकास(dd->engine);
err_engine:
	spin_lock(&sham.lock);
	list_del(&dd->list);
	spin_unlock(&sham.lock);
err_pm:
	pm_runसमय_disable(dev);
	अगर (!dd->polling_mode)
		dma_release_channel(dd->dma_lch);
data_err:
	dev_err(dev, "initialization failed.\n");

	वापस err;
पूर्ण

अटल पूर्णांक omap_sham_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_sham_dev *dd;
	पूर्णांक i, j;

	dd = platक्रमm_get_drvdata(pdev);
	अगर (!dd)
		वापस -ENODEV;
	spin_lock(&sham.lock);
	list_del(&dd->list);
	spin_unlock(&sham.lock);
	क्रम (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		क्रम (j = dd->pdata->algs_info[i].रेजिस्टरed - 1; j >= 0; j--) अणु
			crypto_unरेजिस्टर_ahash(
					&dd->pdata->algs_info[i].algs_list[j]);
			dd->pdata->algs_info[i].रेजिस्टरed--;
		पूर्ण
	tasklet_समाप्त(&dd->करोne_task);
	pm_runसमय_disable(&pdev->dev);

	अगर (!dd->polling_mode)
		dma_release_channel(dd->dma_lch);

	sysfs_हटाओ_group(&dd->dev->kobj, &omap_sham_attr_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap_sham_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_put_sync(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_sham_resume(काष्ठा device *dev)
अणु
	पूर्णांक err = pm_runसमय_get_sync(dev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get sync: %d\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(omap_sham_pm_ops, omap_sham_suspend, omap_sham_resume);

अटल काष्ठा platक्रमm_driver omap_sham_driver = अणु
	.probe	= omap_sham_probe,
	.हटाओ	= omap_sham_हटाओ,
	.driver	= अणु
		.name	= "omap-sham",
		.pm	= &omap_sham_pm_ops,
		.of_match_table	= omap_sham_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_sham_driver);

MODULE_DESCRIPTION("OMAP SHA1/MD5 hw acceleration support.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Dmitry Kasatkin");
MODULE_ALIAS("platform:omap-sham");
