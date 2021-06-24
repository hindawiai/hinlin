<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cryptographic API.
 *
 * Support क्रम ATMEL SHA1/SHA256 HW acceleration.
 *
 * Copyright (c) 2012 Eukrथऊa Electromatique - ATMEL
 * Author: Nicolas Royer <nicolas@eukrea.com>
 *
 * Some ideas are from omap-sham.c drivers.
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
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश "atmel-sha-regs.h"
#समावेश "atmel-authenc.h"

#घोषणा ATMEL_SHA_PRIORITY	300

/* SHA flags */
#घोषणा SHA_FLAGS_BUSY			BIT(0)
#घोषणा	SHA_FLAGS_FINAL			BIT(1)
#घोषणा SHA_FLAGS_DMA_ACTIVE	BIT(2)
#घोषणा SHA_FLAGS_OUTPUT_READY	BIT(3)
#घोषणा SHA_FLAGS_INIT			BIT(4)
#घोषणा SHA_FLAGS_CPU			BIT(5)
#घोषणा SHA_FLAGS_DMA_READY		BIT(6)
#घोषणा SHA_FLAGS_DUMP_REG	BIT(7)

/* bits[11:8] are reserved. */

#घोषणा SHA_FLAGS_FINUP		BIT(16)
#घोषणा SHA_FLAGS_SG		BIT(17)
#घोषणा SHA_FLAGS_ERROR		BIT(23)
#घोषणा SHA_FLAGS_PAD		BIT(24)
#घोषणा SHA_FLAGS_RESTORE	BIT(25)
#घोषणा SHA_FLAGS_IDATAR0	BIT(26)
#घोषणा SHA_FLAGS_WAIT_DATARDY	BIT(27)

#घोषणा SHA_OP_INIT	0
#घोषणा SHA_OP_UPDATE	1
#घोषणा SHA_OP_FINAL	2
#घोषणा SHA_OP_DIGEST	3

#घोषणा SHA_BUFFER_LEN		(PAGE_SIZE / 16)

#घोषणा ATMEL_SHA_DMA_THRESHOLD		56

काष्ठा aपंचांगel_sha_caps अणु
	bool	has_dma;
	bool	has_dualbuff;
	bool	has_sha224;
	bool	has_sha_384_512;
	bool	has_uihv;
	bool	has_hmac;
पूर्ण;

काष्ठा aपंचांगel_sha_dev;

/*
 * .statesize = माप(काष्ठा aपंचांगel_sha_reqctx) must be <= PAGE_SIZE / 8 as
 * tested by the ahash_prepare_alg() function.
 */
काष्ठा aपंचांगel_sha_reqctx अणु
	काष्ठा aपंचांगel_sha_dev	*dd;
	अचिन्हित दीर्घ	flags;
	अचिन्हित दीर्घ	op;

	u8	digest[SHA512_DIGEST_SIZE] __aligned(माप(u32));
	u64	digcnt[2];
	माप_प्रकार	bufcnt;
	माप_प्रकार	buflen;
	dma_addr_t	dma_addr;

	/* walk state */
	काष्ठा scatterlist	*sg;
	अचिन्हित पूर्णांक	offset;	/* offset in current sg */
	अचिन्हित पूर्णांक	total;	/* total request */

	माप_प्रकार block_size;
	माप_प्रकार hash_size;

	u8 buffer[SHA_BUFFER_LEN + SHA512_BLOCK_SIZE] __aligned(माप(u32));
पूर्ण;

प्रकार पूर्णांक (*aपंचांगel_sha_fn_t)(काष्ठा aपंचांगel_sha_dev *);

काष्ठा aपंचांगel_sha_ctx अणु
	काष्ठा aपंचांगel_sha_dev	*dd;
	aपंचांगel_sha_fn_t		start;

	अचिन्हित दीर्घ		flags;
पूर्ण;

#घोषणा ATMEL_SHA_QUEUE_LENGTH	50

काष्ठा aपंचांगel_sha_dma अणु
	काष्ठा dma_chan			*chan;
	काष्ठा dma_slave_config dma_conf;
	काष्ठा scatterlist	*sg;
	पूर्णांक			nents;
	अचिन्हित पूर्णांक		last_sg_length;
पूर्ण;

काष्ठा aपंचांगel_sha_dev अणु
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		phys_base;
	काष्ठा device		*dev;
	काष्ठा clk			*iclk;
	पूर्णांक					irq;
	व्योम __iomem		*io_base;

	spinlock_t		lock;
	काष्ठा tasklet_काष्ठा	करोne_task;
	काष्ठा tasklet_काष्ठा	queue_task;

	अचिन्हित दीर्घ		flags;
	काष्ठा crypto_queue	queue;
	काष्ठा ahash_request	*req;
	bool			is_async;
	bool			क्रमce_complete;
	aपंचांगel_sha_fn_t		resume;
	aपंचांगel_sha_fn_t		cpu_transfer_complete;

	काष्ठा aपंचांगel_sha_dma	dma_lch_in;

	काष्ठा aपंचांगel_sha_caps	caps;

	काष्ठा scatterlist	पंचांगp;

	u32	hw_version;
पूर्ण;

काष्ठा aपंचांगel_sha_drv अणु
	काष्ठा list_head	dev_list;
	spinlock_t		lock;
पूर्ण;

अटल काष्ठा aपंचांगel_sha_drv aपंचांगel_sha = अणु
	.dev_list = LIST_HEAD_INIT(aपंचांगel_sha.dev_list),
	.lock = __SPIN_LOCK_UNLOCKED(aपंचांगel_sha.lock),
पूर्ण;

#अगर_घोषित VERBOSE_DEBUG
अटल स्थिर अक्षर *aपंचांगel_sha_reg_name(u32 offset, अक्षर *पंचांगp, माप_प्रकार sz, bool wr)
अणु
	चयन (offset) अणु
	हाल SHA_CR:
		वापस "CR";

	हाल SHA_MR:
		वापस "MR";

	हाल SHA_IER:
		वापस "IER";

	हाल SHA_IDR:
		वापस "IDR";

	हाल SHA_IMR:
		वापस "IMR";

	हाल SHA_ISR:
		वापस "ISR";

	हाल SHA_MSR:
		वापस "MSR";

	हाल SHA_BCR:
		वापस "BCR";

	हाल SHA_REG_DIN(0):
	हाल SHA_REG_DIN(1):
	हाल SHA_REG_DIN(2):
	हाल SHA_REG_DIN(3):
	हाल SHA_REG_DIN(4):
	हाल SHA_REG_DIN(5):
	हाल SHA_REG_DIN(6):
	हाल SHA_REG_DIN(7):
	हाल SHA_REG_DIN(8):
	हाल SHA_REG_DIN(9):
	हाल SHA_REG_DIN(10):
	हाल SHA_REG_DIN(11):
	हाल SHA_REG_DIN(12):
	हाल SHA_REG_DIN(13):
	हाल SHA_REG_DIN(14):
	हाल SHA_REG_DIN(15):
		snम_लिखो(पंचांगp, sz, "IDATAR[%u]", (offset - SHA_REG_DIN(0)) >> 2);
		अवरोध;

	हाल SHA_REG_DIGEST(0):
	हाल SHA_REG_DIGEST(1):
	हाल SHA_REG_DIGEST(2):
	हाल SHA_REG_DIGEST(3):
	हाल SHA_REG_DIGEST(4):
	हाल SHA_REG_DIGEST(5):
	हाल SHA_REG_DIGEST(6):
	हाल SHA_REG_DIGEST(7):
	हाल SHA_REG_DIGEST(8):
	हाल SHA_REG_DIGEST(9):
	हाल SHA_REG_DIGEST(10):
	हाल SHA_REG_DIGEST(11):
	हाल SHA_REG_DIGEST(12):
	हाल SHA_REG_DIGEST(13):
	हाल SHA_REG_DIGEST(14):
	हाल SHA_REG_DIGEST(15):
		अगर (wr)
			snम_लिखो(पंचांगp, sz, "IDATAR[%u]",
				 16u + ((offset - SHA_REG_DIGEST(0)) >> 2));
		अन्यथा
			snम_लिखो(पंचांगp, sz, "ODATAR[%u]",
				 (offset - SHA_REG_DIGEST(0)) >> 2);
		अवरोध;

	हाल SHA_HW_VERSION:
		वापस "HWVER";

	शेष:
		snम_लिखो(पंचांगp, sz, "0x%02x", offset);
		अवरोध;
	पूर्ण

	वापस पंचांगp;
पूर्ण

#पूर्ण_अगर /* VERBOSE_DEBUG */

अटल अंतरभूत u32 aपंचांगel_sha_पढ़ो(काष्ठा aपंचांगel_sha_dev *dd, u32 offset)
अणु
	u32 value = पढ़ोl_relaxed(dd->io_base + offset);

#अगर_घोषित VERBOSE_DEBUG
	अगर (dd->flags & SHA_FLAGS_DUMP_REG) अणु
		अक्षर पंचांगp[16];

		dev_vdbg(dd->dev, "read 0x%08x from %s\n", value,
			 aपंचांगel_sha_reg_name(offset, पंचांगp, माप(पंचांगp), false));
	पूर्ण
#पूर्ण_अगर /* VERBOSE_DEBUG */

	वापस value;
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_sha_ग_लिखो(काष्ठा aपंचांगel_sha_dev *dd,
					u32 offset, u32 value)
अणु
#अगर_घोषित VERBOSE_DEBUG
	अगर (dd->flags & SHA_FLAGS_DUMP_REG) अणु
		अक्षर पंचांगp[16];

		dev_vdbg(dd->dev, "write 0x%08x into %s\n", value,
			 aपंचांगel_sha_reg_name(offset, पंचांगp, माप(पंचांगp), true));
	पूर्ण
#पूर्ण_अगर /* VERBOSE_DEBUG */

	ग_लिखोl_relaxed(value, dd->io_base + offset);
पूर्ण

अटल अंतरभूत पूर्णांक aपंचांगel_sha_complete(काष्ठा aपंचांगel_sha_dev *dd, पूर्णांक err)
अणु
	काष्ठा ahash_request *req = dd->req;

	dd->flags &= ~(SHA_FLAGS_BUSY | SHA_FLAGS_FINAL | SHA_FLAGS_CPU |
		       SHA_FLAGS_DMA_READY | SHA_FLAGS_OUTPUT_READY |
		       SHA_FLAGS_DUMP_REG);

	clk_disable(dd->iclk);

	अगर ((dd->is_async || dd->क्रमce_complete) && req->base.complete)
		req->base.complete(&req->base, err);

	/* handle new request */
	tasklet_schedule(&dd->queue_task);

	वापस err;
पूर्ण

अटल माप_प्रकार aपंचांगel_sha_append_sg(काष्ठा aपंचांगel_sha_reqctx *ctx)
अणु
	माप_प्रकार count;

	जबतक ((ctx->bufcnt < ctx->buflen) && ctx->total) अणु
		count = min(ctx->sg->length - ctx->offset, ctx->total);
		count = min(count, ctx->buflen - ctx->bufcnt);

		अगर (count <= 0) अणु
			/*
			* Check अगर count <= 0 because the buffer is full or
			* because the sg length is 0. In the latest हाल,
			* check अगर there is another sg in the list, a 0 length
			* sg करोesn't necessarily mean the end of the sg list.
			*/
			अगर ((ctx->sg->length == 0) && !sg_is_last(ctx->sg)) अणु
				ctx->sg = sg_next(ctx->sg);
				जारी;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		scatterwalk_map_and_copy(ctx->buffer + ctx->bufcnt, ctx->sg,
			ctx->offset, count, 0);

		ctx->bufcnt += count;
		ctx->offset += count;
		ctx->total -= count;

		अगर (ctx->offset == ctx->sg->length) अणु
			ctx->sg = sg_next(ctx->sg);
			अगर (ctx->sg)
				ctx->offset = 0;
			अन्यथा
				ctx->total = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The purpose of this padding is to ensure that the padded message is a
 * multiple of 512 bits (SHA1/SHA224/SHA256) or 1024 bits (SHA384/SHA512).
 * The bit "1" is appended at the end of the message followed by
 * "padlen-1" zero bits. Then a 64 bits block (SHA1/SHA224/SHA256) or
 * 128 bits block (SHA384/SHA512) equals to the message length in bits
 * is appended.
 *
 * For SHA1/SHA224/SHA256, padlen is calculated as followed:
 *  - अगर message length < 56 bytes then padlen = 56 - message length
 *  - अन्यथा padlen = 64 + 56 - message length
 *
 * For SHA384/SHA512, padlen is calculated as followed:
 *  - अगर message length < 112 bytes then padlen = 112 - message length
 *  - अन्यथा padlen = 128 + 112 - message length
 */
अटल व्योम aपंचांगel_sha_fill_padding(काष्ठा aपंचांगel_sha_reqctx *ctx, पूर्णांक length)
अणु
	अचिन्हित पूर्णांक index, padlen;
	__be64 bits[2];
	u64 size[2];

	size[0] = ctx->digcnt[0];
	size[1] = ctx->digcnt[1];

	size[0] += ctx->bufcnt;
	अगर (size[0] < ctx->bufcnt)
		size[1]++;

	size[0] += length;
	अगर (size[0]  < length)
		size[1]++;

	bits[1] = cpu_to_be64(size[0] << 3);
	bits[0] = cpu_to_be64(size[1] << 3 | size[0] >> 61);

	चयन (ctx->flags & SHA_FLAGS_ALGO_MASK) अणु
	हाल SHA_FLAGS_SHA384:
	हाल SHA_FLAGS_SHA512:
		index = ctx->bufcnt & 0x7f;
		padlen = (index < 112) ? (112 - index) : ((128+112) - index);
		*(ctx->buffer + ctx->bufcnt) = 0x80;
		स_रखो(ctx->buffer + ctx->bufcnt + 1, 0, padlen-1);
		स_नकल(ctx->buffer + ctx->bufcnt + padlen, bits, 16);
		ctx->bufcnt += padlen + 16;
		ctx->flags |= SHA_FLAGS_PAD;
		अवरोध;

	शेष:
		index = ctx->bufcnt & 0x3f;
		padlen = (index < 56) ? (56 - index) : ((64+56) - index);
		*(ctx->buffer + ctx->bufcnt) = 0x80;
		स_रखो(ctx->buffer + ctx->bufcnt + 1, 0, padlen-1);
		स_नकल(ctx->buffer + ctx->bufcnt + padlen, &bits[1], 8);
		ctx->bufcnt += padlen + 8;
		ctx->flags |= SHA_FLAGS_PAD;
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा aपंचांगel_sha_dev *aपंचांगel_sha_find_dev(काष्ठा aपंचांगel_sha_ctx *tctx)
अणु
	काष्ठा aपंचांगel_sha_dev *dd = शून्य;
	काष्ठा aपंचांगel_sha_dev *पंचांगp;

	spin_lock_bh(&aपंचांगel_sha.lock);
	अगर (!tctx->dd) अणु
		list_क्रम_each_entry(पंचांगp, &aपंचांगel_sha.dev_list, list) अणु
			dd = पंचांगp;
			अवरोध;
		पूर्ण
		tctx->dd = dd;
	पूर्ण अन्यथा अणु
		dd = tctx->dd;
	पूर्ण

	spin_unlock_bh(&aपंचांगel_sha.lock);

	वापस dd;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_ctx *tctx = crypto_ahash_ctx(tfm);
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_dev *dd = aपंचांगel_sha_find_dev(tctx);

	ctx->dd = dd;

	ctx->flags = 0;

	dev_dbg(dd->dev, "init: digest size: %u\n",
		crypto_ahash_digestsize(tfm));

	चयन (crypto_ahash_digestsize(tfm)) अणु
	हाल SHA1_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA1;
		ctx->block_size = SHA1_BLOCK_SIZE;
		अवरोध;
	हाल SHA224_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA224;
		ctx->block_size = SHA224_BLOCK_SIZE;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA256;
		ctx->block_size = SHA256_BLOCK_SIZE;
		अवरोध;
	हाल SHA384_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA384;
		ctx->block_size = SHA384_BLOCK_SIZE;
		अवरोध;
	हाल SHA512_DIGEST_SIZE:
		ctx->flags |= SHA_FLAGS_SHA512;
		ctx->block_size = SHA512_BLOCK_SIZE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ctx->bufcnt = 0;
	ctx->digcnt[0] = 0;
	ctx->digcnt[1] = 0;
	ctx->buflen = SHA_BUFFER_LEN;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_sha_ग_लिखो_ctrl(काष्ठा aपंचांगel_sha_dev *dd, पूर्णांक dma)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	u32 valmr = SHA_MR_MODE_AUTO;
	अचिन्हित पूर्णांक i, hashsize = 0;

	अगर (likely(dma)) अणु
		अगर (!dd->caps.has_dma)
			aपंचांगel_sha_ग_लिखो(dd, SHA_IER, SHA_INT_TXBUFE);
		valmr = SHA_MR_MODE_PDC;
		अगर (dd->caps.has_dualbuff)
			valmr |= SHA_MR_DUALBUFF;
	पूर्ण अन्यथा अणु
		aपंचांगel_sha_ग_लिखो(dd, SHA_IER, SHA_INT_DATARDY);
	पूर्ण

	चयन (ctx->flags & SHA_FLAGS_ALGO_MASK) अणु
	हाल SHA_FLAGS_SHA1:
		valmr |= SHA_MR_ALGO_SHA1;
		hashsize = SHA1_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA224:
		valmr |= SHA_MR_ALGO_SHA224;
		hashsize = SHA256_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA256:
		valmr |= SHA_MR_ALGO_SHA256;
		hashsize = SHA256_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA384:
		valmr |= SHA_MR_ALGO_SHA384;
		hashsize = SHA512_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA512:
		valmr |= SHA_MR_ALGO_SHA512;
		hashsize = SHA512_DIGEST_SIZE;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Setting CR_FIRST only क्रम the first iteration */
	अगर (!(ctx->digcnt[0] || ctx->digcnt[1])) अणु
		aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_FIRST);
	पूर्ण अन्यथा अगर (dd->caps.has_uihv && (ctx->flags & SHA_FLAGS_RESTORE)) अणु
		स्थिर u32 *hash = (स्थिर u32 *)ctx->digest;

		/*
		 * Restore the hardware context: update the User Initialize
		 * Hash Value (UIHV) with the value saved when the latest
		 * 'update' operation completed on this very same crypto
		 * request.
		 */
		ctx->flags &= ~SHA_FLAGS_RESTORE;
		aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_WUIHV);
		क्रम (i = 0; i < hashsize / माप(u32); ++i)
			aपंचांगel_sha_ग_लिखो(dd, SHA_REG_DIN(i), hash[i]);
		aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_FIRST);
		valmr |= SHA_MR_UIHV;
	पूर्ण
	/*
	 * WARNING: If the UIHV feature is not available, the hardware CANNOT
	 * process concurrent requests: the पूर्णांकernal रेजिस्टरs used to store
	 * the hash/digest are still set to the partial digest output values
	 * computed during the latest round.
	 */

	aपंचांगel_sha_ग_लिखो(dd, SHA_MR, valmr);
पूर्ण

अटल अंतरभूत पूर्णांक aपंचांगel_sha_रुको_क्रम_data_पढ़ोy(काष्ठा aपंचांगel_sha_dev *dd,
						aपंचांगel_sha_fn_t resume)
अणु
	u32 isr = aपंचांगel_sha_पढ़ो(dd, SHA_ISR);

	अगर (unlikely(isr & SHA_INT_DATARDY))
		वापस resume(dd);

	dd->resume = resume;
	aपंचांगel_sha_ग_लिखो(dd, SHA_IER, SHA_INT_DATARDY);
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_xmit_cpu(काष्ठा aपंचांगel_sha_dev *dd, स्थिर u8 *buf,
			      माप_प्रकार length, पूर्णांक final)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	पूर्णांक count, len32;
	स्थिर u32 *buffer = (स्थिर u32 *)buf;

	dev_dbg(dd->dev, "xmit_cpu: digcnt: 0x%llx 0x%llx, length: %zd, final: %d\n",
		ctx->digcnt[1], ctx->digcnt[0], length, final);

	aपंचांगel_sha_ग_लिखो_ctrl(dd, 0);

	/* should be non-zero beक्रमe next lines to disable घड़ीs later */
	ctx->digcnt[0] += length;
	अगर (ctx->digcnt[0] < length)
		ctx->digcnt[1]++;

	अगर (final)
		dd->flags |= SHA_FLAGS_FINAL; /* catch last पूर्णांकerrupt */

	len32 = DIV_ROUND_UP(length, माप(u32));

	dd->flags |= SHA_FLAGS_CPU;

	क्रम (count = 0; count < len32; count++)
		aपंचांगel_sha_ग_लिखो(dd, SHA_REG_DIN(count), buffer[count]);

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_xmit_pdc(काष्ठा aपंचांगel_sha_dev *dd, dma_addr_t dma_addr1,
		माप_प्रकार length1, dma_addr_t dma_addr2, माप_प्रकार length2, पूर्णांक final)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	पूर्णांक len32;

	dev_dbg(dd->dev, "xmit_pdc: digcnt: 0x%llx 0x%llx, length: %zd, final: %d\n",
		ctx->digcnt[1], ctx->digcnt[0], length1, final);

	len32 = DIV_ROUND_UP(length1, माप(u32));
	aपंचांगel_sha_ग_लिखो(dd, SHA_PTCR, SHA_PTCR_TXTDIS);
	aपंचांगel_sha_ग_लिखो(dd, SHA_TPR, dma_addr1);
	aपंचांगel_sha_ग_लिखो(dd, SHA_TCR, len32);

	len32 = DIV_ROUND_UP(length2, माप(u32));
	aपंचांगel_sha_ग_लिखो(dd, SHA_TNPR, dma_addr2);
	aपंचांगel_sha_ग_लिखो(dd, SHA_TNCR, len32);

	aपंचांगel_sha_ग_लिखो_ctrl(dd, 1);

	/* should be non-zero beक्रमe next lines to disable घड़ीs later */
	ctx->digcnt[0] += length1;
	अगर (ctx->digcnt[0] < length1)
		ctx->digcnt[1]++;

	अगर (final)
		dd->flags |= SHA_FLAGS_FINAL; /* catch last पूर्णांकerrupt */

	dd->flags |=  SHA_FLAGS_DMA_ACTIVE;

	/* Start DMA transfer */
	aपंचांगel_sha_ग_लिखो(dd, SHA_PTCR, SHA_PTCR_TXTEN);

	वापस -EINPROGRESS;
पूर्ण

अटल व्योम aपंचांगel_sha_dma_callback(व्योम *data)
अणु
	काष्ठा aपंचांगel_sha_dev *dd = data;

	dd->is_async = true;

	/* dma_lch_in - completed - रुको DATRDY */
	aपंचांगel_sha_ग_लिखो(dd, SHA_IER, SHA_INT_DATARDY);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_xmit_dma(काष्ठा aपंचांगel_sha_dev *dd, dma_addr_t dma_addr1,
		माप_प्रकार length1, dma_addr_t dma_addr2, माप_प्रकार length2, पूर्णांक final)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	काष्ठा dma_async_tx_descriptor	*in_desc;
	काष्ठा scatterlist sg[2];

	dev_dbg(dd->dev, "xmit_dma: digcnt: 0x%llx 0x%llx, length: %zd, final: %d\n",
		ctx->digcnt[1], ctx->digcnt[0], length1, final);

	dd->dma_lch_in.dma_conf.src_maxburst = 16;
	dd->dma_lch_in.dma_conf.dst_maxburst = 16;

	dmaengine_slave_config(dd->dma_lch_in.chan, &dd->dma_lch_in.dma_conf);

	अगर (length2) अणु
		sg_init_table(sg, 2);
		sg_dma_address(&sg[0]) = dma_addr1;
		sg_dma_len(&sg[0]) = length1;
		sg_dma_address(&sg[1]) = dma_addr2;
		sg_dma_len(&sg[1]) = length2;
		in_desc = dmaengine_prep_slave_sg(dd->dma_lch_in.chan, sg, 2,
			DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	पूर्ण अन्यथा अणु
		sg_init_table(sg, 1);
		sg_dma_address(&sg[0]) = dma_addr1;
		sg_dma_len(&sg[0]) = length1;
		in_desc = dmaengine_prep_slave_sg(dd->dma_lch_in.chan, sg, 1,
			DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	पूर्ण
	अगर (!in_desc)
		वापस aपंचांगel_sha_complete(dd, -EINVAL);

	in_desc->callback = aपंचांगel_sha_dma_callback;
	in_desc->callback_param = dd;

	aपंचांगel_sha_ग_लिखो_ctrl(dd, 1);

	/* should be non-zero beक्रमe next lines to disable घड़ीs later */
	ctx->digcnt[0] += length1;
	अगर (ctx->digcnt[0] < length1)
		ctx->digcnt[1]++;

	अगर (final)
		dd->flags |= SHA_FLAGS_FINAL; /* catch last पूर्णांकerrupt */

	dd->flags |=  SHA_FLAGS_DMA_ACTIVE;

	/* Start DMA transfer */
	dmaengine_submit(in_desc);
	dma_async_issue_pending(dd->dma_lch_in.chan);

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_xmit_start(काष्ठा aपंचांगel_sha_dev *dd, dma_addr_t dma_addr1,
		माप_प्रकार length1, dma_addr_t dma_addr2, माप_प्रकार length2, पूर्णांक final)
अणु
	अगर (dd->caps.has_dma)
		वापस aपंचांगel_sha_xmit_dma(dd, dma_addr1, length1,
				dma_addr2, length2, final);
	अन्यथा
		वापस aपंचांगel_sha_xmit_pdc(dd, dma_addr1, length1,
				dma_addr2, length2, final);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_update_cpu(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	पूर्णांक bufcnt;

	aपंचांगel_sha_append_sg(ctx);
	aपंचांगel_sha_fill_padding(ctx, 0);
	bufcnt = ctx->bufcnt;
	ctx->bufcnt = 0;

	वापस aपंचांगel_sha_xmit_cpu(dd, ctx->buffer, bufcnt, 1);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_xmit_dma_map(काष्ठा aपंचांगel_sha_dev *dd,
					काष्ठा aपंचांगel_sha_reqctx *ctx,
					माप_प्रकार length, पूर्णांक final)
अणु
	ctx->dma_addr = dma_map_single(dd->dev, ctx->buffer,
				ctx->buflen + ctx->block_size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dd->dev, ctx->dma_addr)) अणु
		dev_err(dd->dev, "dma %zu bytes error\n", ctx->buflen +
				ctx->block_size);
		वापस aपंचांगel_sha_complete(dd, -EINVAL);
	पूर्ण

	ctx->flags &= ~SHA_FLAGS_SG;

	/* next call करोes not fail... so no unmap in the हाल of error */
	वापस aपंचांगel_sha_xmit_start(dd, ctx->dma_addr, length, 0, 0, final);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_update_dma_slow(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	अचिन्हित पूर्णांक final;
	माप_प्रकार count;

	aपंचांगel_sha_append_sg(ctx);

	final = (ctx->flags & SHA_FLAGS_FINUP) && !ctx->total;

	dev_dbg(dd->dev, "slow: bufcnt: %zu, digcnt: 0x%llx 0x%llx, final: %d\n",
		 ctx->bufcnt, ctx->digcnt[1], ctx->digcnt[0], final);

	अगर (final)
		aपंचांगel_sha_fill_padding(ctx, 0);

	अगर (final || (ctx->bufcnt == ctx->buflen)) अणु
		count = ctx->bufcnt;
		ctx->bufcnt = 0;
		वापस aपंचांगel_sha_xmit_dma_map(dd, ctx, count, final);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_update_dma_start(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	अचिन्हित पूर्णांक length, final, tail;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक count;

	अगर (!ctx->total)
		वापस 0;

	अगर (ctx->bufcnt || ctx->offset)
		वापस aपंचांगel_sha_update_dma_slow(dd);

	dev_dbg(dd->dev, "fast: digcnt: 0x%llx 0x%llx, bufcnt: %zd, total: %u\n",
		ctx->digcnt[1], ctx->digcnt[0], ctx->bufcnt, ctx->total);

	sg = ctx->sg;

	अगर (!IS_ALIGNED(sg->offset, माप(u32)))
		वापस aपंचांगel_sha_update_dma_slow(dd);

	अगर (!sg_is_last(sg) && !IS_ALIGNED(sg->length, ctx->block_size))
		/* size is not ctx->block_size aligned */
		वापस aपंचांगel_sha_update_dma_slow(dd);

	length = min(ctx->total, sg->length);

	अगर (sg_is_last(sg)) अणु
		अगर (!(ctx->flags & SHA_FLAGS_FINUP)) अणु
			/* not last sg must be ctx->block_size aligned */
			tail = length & (ctx->block_size - 1);
			length -= tail;
		पूर्ण
	पूर्ण

	ctx->total -= length;
	ctx->offset = length; /* offset where to start slow */

	final = (ctx->flags & SHA_FLAGS_FINUP) && !ctx->total;

	/* Add padding */
	अगर (final) अणु
		tail = length & (ctx->block_size - 1);
		length -= tail;
		ctx->total += tail;
		ctx->offset = length; /* offset where to start slow */

		sg = ctx->sg;
		aपंचांगel_sha_append_sg(ctx);

		aपंचांगel_sha_fill_padding(ctx, length);

		ctx->dma_addr = dma_map_single(dd->dev, ctx->buffer,
			ctx->buflen + ctx->block_size, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dd->dev, ctx->dma_addr)) अणु
			dev_err(dd->dev, "dma %zu bytes error\n",
				ctx->buflen + ctx->block_size);
			वापस aपंचांगel_sha_complete(dd, -EINVAL);
		पूर्ण

		अगर (length == 0) अणु
			ctx->flags &= ~SHA_FLAGS_SG;
			count = ctx->bufcnt;
			ctx->bufcnt = 0;
			वापस aपंचांगel_sha_xmit_start(dd, ctx->dma_addr, count, 0,
					0, final);
		पूर्ण अन्यथा अणु
			ctx->sg = sg;
			अगर (!dma_map_sg(dd->dev, ctx->sg, 1,
				DMA_TO_DEVICE)) अणु
					dev_err(dd->dev, "dma_map_sg  error\n");
					वापस aपंचांगel_sha_complete(dd, -EINVAL);
			पूर्ण

			ctx->flags |= SHA_FLAGS_SG;

			count = ctx->bufcnt;
			ctx->bufcnt = 0;
			वापस aपंचांगel_sha_xmit_start(dd, sg_dma_address(ctx->sg),
					length, ctx->dma_addr, count, final);
		पूर्ण
	पूर्ण

	अगर (!dma_map_sg(dd->dev, ctx->sg, 1, DMA_TO_DEVICE)) अणु
		dev_err(dd->dev, "dma_map_sg  error\n");
		वापस aपंचांगel_sha_complete(dd, -EINVAL);
	पूर्ण

	ctx->flags |= SHA_FLAGS_SG;

	/* next call करोes not fail... so no unmap in the हाल of error */
	वापस aपंचांगel_sha_xmit_start(dd, sg_dma_address(ctx->sg), length, 0,
								0, final);
पूर्ण

अटल व्योम aपंचांगel_sha_update_dma_stop(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(dd->req);

	अगर (ctx->flags & SHA_FLAGS_SG) अणु
		dma_unmap_sg(dd->dev, ctx->sg, 1, DMA_TO_DEVICE);
		अगर (ctx->sg->length == ctx->offset) अणु
			ctx->sg = sg_next(ctx->sg);
			अगर (ctx->sg)
				ctx->offset = 0;
		पूर्ण
		अगर (ctx->flags & SHA_FLAGS_PAD) अणु
			dma_unmap_single(dd->dev, ctx->dma_addr,
				ctx->buflen + ctx->block_size, DMA_TO_DEVICE);
		पूर्ण
	पूर्ण अन्यथा अणु
		dma_unmap_single(dd->dev, ctx->dma_addr, ctx->buflen +
						ctx->block_size, DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगel_sha_update_req(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err;

	dev_dbg(dd->dev, "update_req: total: %u, digcnt: 0x%llx 0x%llx\n",
		ctx->total, ctx->digcnt[1], ctx->digcnt[0]);

	अगर (ctx->flags & SHA_FLAGS_CPU)
		err = aपंचांगel_sha_update_cpu(dd);
	अन्यथा
		err = aपंचांगel_sha_update_dma_start(dd);

	/* रुको क्रम dma completion beक्रमe can take more data */
	dev_dbg(dd->dev, "update: err: %d, digcnt: 0x%llx 0%llx\n",
			err, ctx->digcnt[1], ctx->digcnt[0]);

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_final_req(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err = 0;
	पूर्णांक count;

	अगर (ctx->bufcnt >= ATMEL_SHA_DMA_THRESHOLD) अणु
		aपंचांगel_sha_fill_padding(ctx, 0);
		count = ctx->bufcnt;
		ctx->bufcnt = 0;
		err = aपंचांगel_sha_xmit_dma_map(dd, ctx, count, 1);
	पूर्ण
	/* faster to handle last block with cpu */
	अन्यथा अणु
		aपंचांगel_sha_fill_padding(ctx, 0);
		count = ctx->bufcnt;
		ctx->bufcnt = 0;
		err = aपंचांगel_sha_xmit_cpu(dd, ctx->buffer, count, 1);
	पूर्ण

	dev_dbg(dd->dev, "final_req: err: %d\n", err);

	वापस err;
पूर्ण

अटल व्योम aपंचांगel_sha_copy_hash(काष्ठा ahash_request *req)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	u32 *hash = (u32 *)ctx->digest;
	अचिन्हित पूर्णांक i, hashsize;

	चयन (ctx->flags & SHA_FLAGS_ALGO_MASK) अणु
	हाल SHA_FLAGS_SHA1:
		hashsize = SHA1_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA224:
	हाल SHA_FLAGS_SHA256:
		hashsize = SHA256_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA384:
	हाल SHA_FLAGS_SHA512:
		hashsize = SHA512_DIGEST_SIZE;
		अवरोध;

	शेष:
		/* Should not happen... */
		वापस;
	पूर्ण

	क्रम (i = 0; i < hashsize / माप(u32); ++i)
		hash[i] = aपंचांगel_sha_पढ़ो(ctx->dd, SHA_REG_DIGEST(i));
	ctx->flags |= SHA_FLAGS_RESTORE;
पूर्ण

अटल व्योम aपंचांगel_sha_copy_पढ़ोy_hash(काष्ठा ahash_request *req)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);

	अगर (!req->result)
		वापस;

	चयन (ctx->flags & SHA_FLAGS_ALGO_MASK) अणु
	शेष:
	हाल SHA_FLAGS_SHA1:
		स_नकल(req->result, ctx->digest, SHA1_DIGEST_SIZE);
		अवरोध;

	हाल SHA_FLAGS_SHA224:
		स_नकल(req->result, ctx->digest, SHA224_DIGEST_SIZE);
		अवरोध;

	हाल SHA_FLAGS_SHA256:
		स_नकल(req->result, ctx->digest, SHA256_DIGEST_SIZE);
		अवरोध;

	हाल SHA_FLAGS_SHA384:
		स_नकल(req->result, ctx->digest, SHA384_DIGEST_SIZE);
		अवरोध;

	हाल SHA_FLAGS_SHA512:
		स_नकल(req->result, ctx->digest, SHA512_DIGEST_SIZE);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगel_sha_finish(काष्ठा ahash_request *req)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_dev *dd = ctx->dd;

	अगर (ctx->digcnt[0] || ctx->digcnt[1])
		aपंचांगel_sha_copy_पढ़ोy_hash(req);

	dev_dbg(dd->dev, "digcnt: 0x%llx 0x%llx, bufcnt: %zd\n", ctx->digcnt[1],
		ctx->digcnt[0], ctx->bufcnt);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_sha_finish_req(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_dev *dd = ctx->dd;

	अगर (!err) अणु
		aपंचांगel_sha_copy_hash(req);
		अगर (SHA_FLAGS_FINAL & dd->flags)
			err = aपंचांगel_sha_finish(req);
	पूर्ण अन्यथा अणु
		ctx->flags |= SHA_FLAGS_ERROR;
	पूर्ण

	/* atomic operation is not needed here */
	(व्योम)aपंचांगel_sha_complete(dd, err);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hw_init(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	पूर्णांक err;

	err = clk_enable(dd->iclk);
	अगर (err)
		वापस err;

	अगर (!(SHA_FLAGS_INIT & dd->flags)) अणु
		aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_SWRST);
		dd->flags |= SHA_FLAGS_INIT;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक aपंचांगel_sha_get_version(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	वापस aपंचांगel_sha_पढ़ो(dd, SHA_HW_VERSION) & 0x00000fff;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hw_version_init(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	पूर्णांक err;

	err = aपंचांगel_sha_hw_init(dd);
	अगर (err)
		वापस err;

	dd->hw_version = aपंचांगel_sha_get_version(dd);

	dev_info(dd->dev,
			"version: 0x%x\n", dd->hw_version);

	clk_disable(dd->iclk);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_handle_queue(काष्ठा aपंचांगel_sha_dev *dd,
				  काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_async_request *async_req, *backlog;
	काष्ठा aपंचांगel_sha_ctx *ctx;
	अचिन्हित दीर्घ flags;
	bool start_async;
	पूर्णांक err = 0, ret = 0;

	spin_lock_irqsave(&dd->lock, flags);
	अगर (req)
		ret = ahash_enqueue_request(&dd->queue, req);

	अगर (SHA_FLAGS_BUSY & dd->flags) अणु
		spin_unlock_irqrestore(&dd->lock, flags);
		वापस ret;
	पूर्ण

	backlog = crypto_get_backlog(&dd->queue);
	async_req = crypto_dequeue_request(&dd->queue);
	अगर (async_req)
		dd->flags |= SHA_FLAGS_BUSY;

	spin_unlock_irqrestore(&dd->lock, flags);

	अगर (!async_req)
		वापस ret;

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	ctx = crypto_tfm_ctx(async_req->tfm);

	dd->req = ahash_request_cast(async_req);
	start_async = (dd->req != req);
	dd->is_async = start_async;
	dd->क्रमce_complete = false;

	/* WARNING: ctx->start() MAY change dd->is_async. */
	err = ctx->start(dd);
	वापस (start_async) ? ret : err;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_करोne(काष्ठा aपंचांगel_sha_dev *dd);

अटल पूर्णांक aपंचांगel_sha_start(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err;

	dev_dbg(dd->dev, "handling new req, op: %lu, nbytes: %u\n",
						ctx->op, req->nbytes);

	err = aपंचांगel_sha_hw_init(dd);
	अगर (err)
		वापस aपंचांगel_sha_complete(dd, err);

	/*
	 * aपंचांगel_sha_update_req() and aपंचांगel_sha_final_req() can वापस either:
	 *  -EINPROGRESS: the hardware is busy and the SHA driver will resume
	 *                its job later in the करोne_task.
	 *                This is the मुख्य path.
	 *
	 * 0: the SHA driver can जारी its job then release the hardware
	 *    later, अगर needed, with aपंचांगel_sha_finish_req().
	 *    This is the alternate path.
	 *
	 * < 0: an error has occurred so aपंचांगel_sha_complete(dd, err) has alपढ़ोy
	 *      been called, hence the hardware has been released.
	 *      The SHA driver must stop its job without calling
	 *      aपंचांगel_sha_finish_req(), otherwise aपंचांगel_sha_complete() would be
	 *      called a second समय.
	 *
	 * Please note that currently, aपंचांगel_sha_final_req() never वापसs 0.
	 */

	dd->resume = aपंचांगel_sha_करोne;
	अगर (ctx->op == SHA_OP_UPDATE) अणु
		err = aपंचांगel_sha_update_req(dd);
		अगर (!err && (ctx->flags & SHA_FLAGS_FINUP))
			/* no final() after finup() */
			err = aपंचांगel_sha_final_req(dd);
	पूर्ण अन्यथा अगर (ctx->op == SHA_OP_FINAL) अणु
		err = aपंचांगel_sha_final_req(dd);
	पूर्ण

	अगर (!err)
		/* करोne_task will not finish it, so करो it here */
		aपंचांगel_sha_finish_req(req, err);

	dev_dbg(dd->dev, "exit, err: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_enqueue(काष्ठा ahash_request *req, अचिन्हित पूर्णांक op)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_ctx *tctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा aपंचांगel_sha_dev *dd = tctx->dd;

	ctx->op = op;

	वापस aपंचांगel_sha_handle_queue(dd, req);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_update(काष्ठा ahash_request *req)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);

	अगर (!req->nbytes)
		वापस 0;

	ctx->total = req->nbytes;
	ctx->sg = req->src;
	ctx->offset = 0;

	अगर (ctx->flags & SHA_FLAGS_FINUP) अणु
		अगर (ctx->bufcnt + ctx->total < ATMEL_SHA_DMA_THRESHOLD)
			/* faster to use CPU क्रम लघु transfers */
			ctx->flags |= SHA_FLAGS_CPU;
	पूर्ण अन्यथा अगर (ctx->bufcnt + ctx->total < ctx->buflen) अणु
		aपंचांगel_sha_append_sg(ctx);
		वापस 0;
	पूर्ण
	वापस aपंचांगel_sha_enqueue(req, SHA_OP_UPDATE);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_final(काष्ठा ahash_request *req)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);

	ctx->flags |= SHA_FLAGS_FINUP;

	अगर (ctx->flags & SHA_FLAGS_ERROR)
		वापस 0; /* uncompleted hash is not needed */

	अगर (ctx->flags & SHA_FLAGS_PAD)
		/* copy पढ़ोy hash (+ finalize hmac) */
		वापस aपंचांगel_sha_finish(req);

	वापस aपंचांगel_sha_enqueue(req, SHA_OP_FINAL);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err1, err2;

	ctx->flags |= SHA_FLAGS_FINUP;

	err1 = aपंचांगel_sha_update(req);
	अगर (err1 == -EINPROGRESS ||
	    (err1 == -EBUSY && (ahash_request_flags(req) &
				CRYPTO_TFM_REQ_MAY_BACKLOG)))
		वापस err1;

	/*
	 * final() has to be always called to cleanup resources
	 * even अगर udpate() failed, except EINPROGRESS
	 */
	err2 = aपंचांगel_sha_final(req);

	वापस err1 ?: err2;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_digest(काष्ठा ahash_request *req)
अणु
	वापस aपंचांगel_sha_init(req) ?: aपंचांगel_sha_finup(req);
पूर्ण


अटल पूर्णांक aपंचांगel_sha_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	स्थिर काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);

	स_नकल(out, ctx, माप(*ctx));
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);

	स_नकल(ctx, in, माप(*ctx));
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा aपंचांगel_sha_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा aपंचांगel_sha_reqctx));
	ctx->start = aपंचांगel_sha_start;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_sha_alg_init(काष्ठा ahash_alg *alg)
अणु
	alg->halg.base.cra_priority = ATMEL_SHA_PRIORITY;
	alg->halg.base.cra_flags = CRYPTO_ALG_ASYNC;
	alg->halg.base.cra_ctxsize = माप(काष्ठा aपंचांगel_sha_ctx);
	alg->halg.base.cra_module = THIS_MODULE;
	alg->halg.base.cra_init = aपंचांगel_sha_cra_init;

	alg->halg.statesize = माप(काष्ठा aपंचांगel_sha_reqctx);

	alg->init = aपंचांगel_sha_init;
	alg->update = aपंचांगel_sha_update;
	alg->final = aपंचांगel_sha_final;
	alg->finup = aपंचांगel_sha_finup;
	alg->digest = aपंचांगel_sha_digest;
	alg->export = aपंचांगel_sha_export;
	alg->import = aपंचांगel_sha_import;
पूर्ण

अटल काष्ठा ahash_alg sha_1_256_algs[] = अणु
अणु
	.halg.base.cra_name		= "sha1",
	.halg.base.cra_driver_name	= "atmel-sha1",
	.halg.base.cra_blocksize	= SHA1_BLOCK_SIZE,

	.halg.digestsize = SHA1_DIGEST_SIZE,
पूर्ण,
अणु
	.halg.base.cra_name		= "sha256",
	.halg.base.cra_driver_name	= "atmel-sha256",
	.halg.base.cra_blocksize	= SHA256_BLOCK_SIZE,

	.halg.digestsize = SHA256_DIGEST_SIZE,
पूर्ण,
पूर्ण;

अटल काष्ठा ahash_alg sha_224_alg = अणु
	.halg.base.cra_name		= "sha224",
	.halg.base.cra_driver_name	= "atmel-sha224",
	.halg.base.cra_blocksize	= SHA224_BLOCK_SIZE,

	.halg.digestsize = SHA224_DIGEST_SIZE,
पूर्ण;

अटल काष्ठा ahash_alg sha_384_512_algs[] = अणु
अणु
	.halg.base.cra_name		= "sha384",
	.halg.base.cra_driver_name	= "atmel-sha384",
	.halg.base.cra_blocksize	= SHA384_BLOCK_SIZE,
	.halg.base.cra_alignmask	= 0x3,

	.halg.digestsize = SHA384_DIGEST_SIZE,
पूर्ण,
अणु
	.halg.base.cra_name		= "sha512",
	.halg.base.cra_driver_name	= "atmel-sha512",
	.halg.base.cra_blocksize	= SHA512_BLOCK_SIZE,
	.halg.base.cra_alignmask	= 0x3,

	.halg.digestsize = SHA512_DIGEST_SIZE,
पूर्ण,
पूर्ण;

अटल व्योम aपंचांगel_sha_queue_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा aपंचांगel_sha_dev *dd = (काष्ठा aपंचांगel_sha_dev *)data;

	aपंचांगel_sha_handle_queue(dd, शून्य);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_करोne(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	पूर्णांक err = 0;

	अगर (SHA_FLAGS_CPU & dd->flags) अणु
		अगर (SHA_FLAGS_OUTPUT_READY & dd->flags) अणु
			dd->flags &= ~SHA_FLAGS_OUTPUT_READY;
			जाओ finish;
		पूर्ण
	पूर्ण अन्यथा अगर (SHA_FLAGS_DMA_READY & dd->flags) अणु
		अगर (SHA_FLAGS_DMA_ACTIVE & dd->flags) अणु
			dd->flags &= ~SHA_FLAGS_DMA_ACTIVE;
			aपंचांगel_sha_update_dma_stop(dd);
		पूर्ण
		अगर (SHA_FLAGS_OUTPUT_READY & dd->flags) अणु
			/* hash or semi-hash पढ़ोy */
			dd->flags &= ~(SHA_FLAGS_DMA_READY |
						SHA_FLAGS_OUTPUT_READY);
			err = aपंचांगel_sha_update_dma_start(dd);
			अगर (err != -EINPROGRESS)
				जाओ finish;
		पूर्ण
	पूर्ण
	वापस err;

finish:
	/* finish curent request */
	aपंचांगel_sha_finish_req(dd->req, err);

	वापस err;
पूर्ण

अटल व्योम aपंचांगel_sha_करोne_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा aपंचांगel_sha_dev *dd = (काष्ठा aपंचांगel_sha_dev *)data;

	dd->is_async = true;
	(व्योम)dd->resume(dd);
पूर्ण

अटल irqवापस_t aपंचांगel_sha_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_sha_dev *sha_dd = dev_id;
	u32 reg;

	reg = aपंचांगel_sha_पढ़ो(sha_dd, SHA_ISR);
	अगर (reg & aपंचांगel_sha_पढ़ो(sha_dd, SHA_IMR)) अणु
		aपंचांगel_sha_ग_लिखो(sha_dd, SHA_IDR, reg);
		अगर (SHA_FLAGS_BUSY & sha_dd->flags) अणु
			sha_dd->flags |= SHA_FLAGS_OUTPUT_READY;
			अगर (!(SHA_FLAGS_CPU & sha_dd->flags))
				sha_dd->flags |= SHA_FLAGS_DMA_READY;
			tasklet_schedule(&sha_dd->करोne_task);
		पूर्ण अन्यथा अणु
			dev_warn(sha_dd->dev, "SHA interrupt when no active requests.\n");
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण


/* DMA transfer functions */

अटल bool aपंचांगel_sha_dma_check_aligned(काष्ठा aपंचांगel_sha_dev *dd,
					काष्ठा scatterlist *sg,
					माप_प्रकार len)
अणु
	काष्ठा aपंचांगel_sha_dma *dma = &dd->dma_lch_in;
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	माप_प्रकार bs = ctx->block_size;
	पूर्णांक nents;

	क्रम (nents = 0; sg; sg = sg_next(sg), ++nents) अणु
		अगर (!IS_ALIGNED(sg->offset, माप(u32)))
			वापस false;

		/*
		 * This is the last sg, the only one that is allowed to
		 * have an unaligned length.
		 */
		अगर (len <= sg->length) अणु
			dma->nents = nents + 1;
			dma->last_sg_length = sg->length;
			sg->length = ALIGN(len, माप(u32));
			वापस true;
		पूर्ण

		/* All other sg lengths MUST be aligned to the block size. */
		अगर (!IS_ALIGNED(sg->length, bs))
			वापस false;

		len -= sg->length;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम aपंचांगel_sha_dma_callback2(व्योम *data)
अणु
	काष्ठा aपंचांगel_sha_dev *dd = data;
	काष्ठा aपंचांगel_sha_dma *dma = &dd->dma_lch_in;
	काष्ठा scatterlist *sg;
	पूर्णांक nents;

	dma_unmap_sg(dd->dev, dma->sg, dma->nents, DMA_TO_DEVICE);

	sg = dma->sg;
	क्रम (nents = 0; nents < dma->nents - 1; ++nents)
		sg = sg_next(sg);
	sg->length = dma->last_sg_length;

	dd->is_async = true;
	(व्योम)aपंचांगel_sha_रुको_क्रम_data_पढ़ोy(dd, dd->resume);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_dma_start(काष्ठा aपंचांगel_sha_dev *dd,
			       काष्ठा scatterlist *src,
			       माप_प्रकार len,
			       aपंचांगel_sha_fn_t resume)
अणु
	काष्ठा aपंचांगel_sha_dma *dma = &dd->dma_lch_in;
	काष्ठा dma_slave_config *config = &dma->dma_conf;
	काष्ठा dma_chan *chan = dma->chan;
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	अचिन्हित पूर्णांक sg_len;
	पूर्णांक err;

	dd->resume = resume;

	/*
	 * dma->nents has alपढ़ोy been initialized by
	 * aपंचांगel_sha_dma_check_aligned().
	 */
	dma->sg = src;
	sg_len = dma_map_sg(dd->dev, dma->sg, dma->nents, DMA_TO_DEVICE);
	अगर (!sg_len) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	config->src_maxburst = 16;
	config->dst_maxburst = 16;
	err = dmaengine_slave_config(chan, config);
	अगर (err)
		जाओ unmap_sg;

	desc = dmaengine_prep_slave_sg(chan, dma->sg, sg_len, DMA_MEM_TO_DEV,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		err = -ENOMEM;
		जाओ unmap_sg;
	पूर्ण

	desc->callback = aपंचांगel_sha_dma_callback2;
	desc->callback_param = dd;
	cookie = dmaengine_submit(desc);
	err = dma_submit_error(cookie);
	अगर (err)
		जाओ unmap_sg;

	dma_async_issue_pending(chan);

	वापस -EINPROGRESS;

unmap_sg:
	dma_unmap_sg(dd->dev, dma->sg, dma->nents, DMA_TO_DEVICE);
निकास:
	वापस aपंचांगel_sha_complete(dd, err);
पूर्ण


/* CPU transfer functions */

अटल पूर्णांक aपंचांगel_sha_cpu_transfer(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	स्थिर u32 *words = (स्थिर u32 *)ctx->buffer;
	माप_प्रकार i, num_words;
	u32 isr, din, din_inc;

	din_inc = (ctx->flags & SHA_FLAGS_IDATAR0) ? 0 : 1;
	क्रम (;;) अणु
		/* Write data पूर्णांकo the Input Data Registers. */
		num_words = DIV_ROUND_UP(ctx->bufcnt, माप(u32));
		क्रम (i = 0, din = 0; i < num_words; ++i, din += din_inc)
			aपंचांगel_sha_ग_लिखो(dd, SHA_REG_DIN(din), words[i]);

		ctx->offset += ctx->bufcnt;
		ctx->total -= ctx->bufcnt;

		अगर (!ctx->total)
			अवरोध;

		/*
		 * Prepare next block:
		 * Fill ctx->buffer now with the next data to be written पूर्णांकo
		 * IDATARx: it gives समय क्रम the SHA hardware to process
		 * the current data so the SHA_INT_DATARDY flag might be set
		 * in SHA_ISR when polling this रेजिस्टर at the beginning of
		 * the next loop.
		 */
		ctx->bufcnt = min_t(माप_प्रकार, ctx->block_size, ctx->total);
		scatterwalk_map_and_copy(ctx->buffer, ctx->sg,
					 ctx->offset, ctx->bufcnt, 0);

		/* Wait क्रम hardware to be पढ़ोy again. */
		isr = aपंचांगel_sha_पढ़ो(dd, SHA_ISR);
		अगर (!(isr & SHA_INT_DATARDY)) अणु
			/* Not पढ़ोy yet. */
			dd->resume = aपंचांगel_sha_cpu_transfer;
			aपंचांगel_sha_ग_लिखो(dd, SHA_IER, SHA_INT_DATARDY);
			वापस -EINPROGRESS;
		पूर्ण
	पूर्ण

	अगर (unlikely(!(ctx->flags & SHA_FLAGS_WAIT_DATARDY)))
		वापस dd->cpu_transfer_complete(dd);

	वापस aपंचांगel_sha_रुको_क्रम_data_पढ़ोy(dd, dd->cpu_transfer_complete);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_cpu_start(काष्ठा aपंचांगel_sha_dev *dd,
			       काष्ठा scatterlist *sg,
			       अचिन्हित पूर्णांक len,
			       bool idatar0_only,
			       bool रुको_data_पढ़ोy,
			       aपंचांगel_sha_fn_t resume)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);

	अगर (!len)
		वापस resume(dd);

	ctx->flags &= ~(SHA_FLAGS_IDATAR0 | SHA_FLAGS_WAIT_DATARDY);

	अगर (idatar0_only)
		ctx->flags |= SHA_FLAGS_IDATAR0;

	अगर (रुको_data_पढ़ोy)
		ctx->flags |= SHA_FLAGS_WAIT_DATARDY;

	ctx->sg = sg;
	ctx->total = len;
	ctx->offset = 0;

	/* Prepare the first block to be written. */
	ctx->bufcnt = min_t(माप_प्रकार, ctx->block_size, ctx->total);
	scatterwalk_map_and_copy(ctx->buffer, ctx->sg,
				 ctx->offset, ctx->bufcnt, 0);

	dd->cpu_transfer_complete = resume;
	वापस aपंचांगel_sha_cpu_transfer(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_cpu_hash(काष्ठा aपंचांगel_sha_dev *dd,
			      स्थिर व्योम *data, अचिन्हित पूर्णांक datalen,
			      bool स्वतः_padding,
			      aपंचांगel_sha_fn_t resume)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	u32 msglen = (स्वतः_padding) ? datalen : 0;
	u32 mr = SHA_MR_MODE_AUTO;

	अगर (!(IS_ALIGNED(datalen, ctx->block_size) || स्वतः_padding))
		वापस aपंचांगel_sha_complete(dd, -EINVAL);

	mr |= (ctx->flags & SHA_FLAGS_ALGO_MASK);
	aपंचांगel_sha_ग_लिखो(dd, SHA_MR, mr);
	aपंचांगel_sha_ग_लिखो(dd, SHA_MSR, msglen);
	aपंचांगel_sha_ग_लिखो(dd, SHA_BCR, msglen);
	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_FIRST);

	sg_init_one(&dd->पंचांगp, data, datalen);
	वापस aपंचांगel_sha_cpu_start(dd, &dd->पंचांगp, datalen, false, true, resume);
पूर्ण


/* hmac functions */

काष्ठा aपंचांगel_sha_hmac_key अणु
	bool			valid;
	अचिन्हित पूर्णांक		keylen;
	u8			buffer[SHA512_BLOCK_SIZE];
	u8			*keydup;
पूर्ण;

अटल अंतरभूत व्योम aपंचांगel_sha_hmac_key_init(काष्ठा aपंचांगel_sha_hmac_key *hkey)
अणु
	स_रखो(hkey, 0, माप(*hkey));
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_sha_hmac_key_release(काष्ठा aपंचांगel_sha_hmac_key *hkey)
अणु
	kमुक्त(hkey->keydup);
	स_रखो(hkey, 0, माप(*hkey));
पूर्ण

अटल अंतरभूत पूर्णांक aपंचांगel_sha_hmac_key_set(काष्ठा aपंचांगel_sha_hmac_key *hkey,
					 स्थिर u8 *key,
					 अचिन्हित पूर्णांक keylen)
अणु
	aपंचांगel_sha_hmac_key_release(hkey);

	अगर (keylen > माप(hkey->buffer)) अणु
		hkey->keydup = kmemdup(key, keylen, GFP_KERNEL);
		अगर (!hkey->keydup)
			वापस -ENOMEM;

	पूर्ण अन्यथा अणु
		स_नकल(hkey->buffer, key, keylen);
	पूर्ण

	hkey->valid = true;
	hkey->keylen = keylen;
	वापस 0;
पूर्ण

अटल अंतरभूत bool aपंचांगel_sha_hmac_key_get(स्थिर काष्ठा aपंचांगel_sha_hmac_key *hkey,
					  स्थिर u8 **key,
					  अचिन्हित पूर्णांक *keylen)
अणु
	अगर (!hkey->valid)
		वापस false;

	*keylen = hkey->keylen;
	*key = (hkey->keydup) ? hkey->keydup : hkey->buffer;
	वापस true;
पूर्ण


काष्ठा aपंचांगel_sha_hmac_ctx अणु
	काष्ठा aपंचांगel_sha_ctx	base;

	काष्ठा aपंचांगel_sha_hmac_key	hkey;
	u32			ipad[SHA512_BLOCK_SIZE / माप(u32)];
	u32			opad[SHA512_BLOCK_SIZE / माप(u32)];
	aपंचांगel_sha_fn_t		resume;
पूर्ण;

अटल पूर्णांक aपंचांगel_sha_hmac_setup(काष्ठा aपंचांगel_sha_dev *dd,
				aपंचांगel_sha_fn_t resume);
अटल पूर्णांक aपंचांगel_sha_hmac_prehash_key(काष्ठा aपंचांगel_sha_dev *dd,
				      स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
अटल पूर्णांक aपंचांगel_sha_hmac_prehash_key_करोne(काष्ठा aपंचांगel_sha_dev *dd);
अटल पूर्णांक aपंचांगel_sha_hmac_compute_ipad_hash(काष्ठा aपंचांगel_sha_dev *dd);
अटल पूर्णांक aपंचांगel_sha_hmac_compute_opad_hash(काष्ठा aपंचांगel_sha_dev *dd);
अटल पूर्णांक aपंचांगel_sha_hmac_setup_करोne(काष्ठा aपंचांगel_sha_dev *dd);

अटल पूर्णांक aपंचांगel_sha_hmac_init_करोne(काष्ठा aपंचांगel_sha_dev *dd);
अटल पूर्णांक aपंचांगel_sha_hmac_final(काष्ठा aपंचांगel_sha_dev *dd);
अटल पूर्णांक aपंचांगel_sha_hmac_final_करोne(काष्ठा aपंचांगel_sha_dev *dd);
अटल पूर्णांक aपंचांगel_sha_hmac_digest2(काष्ठा aपंचांगel_sha_dev *dd);

अटल पूर्णांक aपंचांगel_sha_hmac_setup(काष्ठा aपंचांगel_sha_dev *dd,
				aपंचांगel_sha_fn_t resume)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	अचिन्हित पूर्णांक keylen;
	स्थिर u8 *key;
	माप_प्रकार bs;

	hmac->resume = resume;
	चयन (ctx->flags & SHA_FLAGS_ALGO_MASK) अणु
	हाल SHA_FLAGS_SHA1:
		ctx->block_size = SHA1_BLOCK_SIZE;
		ctx->hash_size = SHA1_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA224:
		ctx->block_size = SHA224_BLOCK_SIZE;
		ctx->hash_size = SHA256_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA256:
		ctx->block_size = SHA256_BLOCK_SIZE;
		ctx->hash_size = SHA256_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA384:
		ctx->block_size = SHA384_BLOCK_SIZE;
		ctx->hash_size = SHA512_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA512:
		ctx->block_size = SHA512_BLOCK_SIZE;
		ctx->hash_size = SHA512_DIGEST_SIZE;
		अवरोध;

	शेष:
		वापस aपंचांगel_sha_complete(dd, -EINVAL);
	पूर्ण
	bs = ctx->block_size;

	अगर (likely(!aपंचांगel_sha_hmac_key_get(&hmac->hkey, &key, &keylen)))
		वापस resume(dd);

	/* Compute K' from K. */
	अगर (unlikely(keylen > bs))
		वापस aपंचांगel_sha_hmac_prehash_key(dd, key, keylen);

	/* Prepare ipad. */
	स_नकल((u8 *)hmac->ipad, key, keylen);
	स_रखो((u8 *)hmac->ipad + keylen, 0, bs - keylen);
	वापस aपंचांगel_sha_hmac_compute_ipad_hash(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_prehash_key(काष्ठा aपंचांगel_sha_dev *dd,
				      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस aपंचांगel_sha_cpu_hash(dd, key, keylen, true,
				  aपंचांगel_sha_hmac_prehash_key_करोne);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_prehash_key_करोne(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	माप_प्रकार ds = crypto_ahash_digestsize(tfm);
	माप_प्रकार bs = ctx->block_size;
	माप_प्रकार i, num_words = ds / माप(u32);

	/* Prepare ipad. */
	क्रम (i = 0; i < num_words; ++i)
		hmac->ipad[i] = aपंचांगel_sha_पढ़ो(dd, SHA_REG_DIGEST(i));
	स_रखो((u8 *)hmac->ipad + ds, 0, bs - ds);
	वापस aपंचांगel_sha_hmac_compute_ipad_hash(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_compute_ipad_hash(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	माप_प्रकार bs = ctx->block_size;
	माप_प्रकार i, num_words = bs / माप(u32);

	स_नकल(hmac->opad, hmac->ipad, bs);
	क्रम (i = 0; i < num_words; ++i) अणु
		hmac->ipad[i] ^= 0x36363636;
		hmac->opad[i] ^= 0x5c5c5c5c;
	पूर्ण

	वापस aपंचांगel_sha_cpu_hash(dd, hmac->ipad, bs, false,
				  aपंचांगel_sha_hmac_compute_opad_hash);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_compute_opad_hash(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	माप_प्रकार bs = ctx->block_size;
	माप_प्रकार hs = ctx->hash_size;
	माप_प्रकार i, num_words = hs / माप(u32);

	क्रम (i = 0; i < num_words; ++i)
		hmac->ipad[i] = aपंचांगel_sha_पढ़ो(dd, SHA_REG_DIGEST(i));
	वापस aपंचांगel_sha_cpu_hash(dd, hmac->opad, bs, false,
				  aपंचांगel_sha_hmac_setup_करोne);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_setup_करोne(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	माप_प्रकार hs = ctx->hash_size;
	माप_प्रकार i, num_words = hs / माप(u32);

	क्रम (i = 0; i < num_words; ++i)
		hmac->opad[i] = aपंचांगel_sha_पढ़ो(dd, SHA_REG_DIGEST(i));
	aपंचांगel_sha_hmac_key_release(&hmac->hkey);
	वापस hmac->resume(dd);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_start(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err;

	err = aपंचांगel_sha_hw_init(dd);
	अगर (err)
		वापस aपंचांगel_sha_complete(dd, err);

	चयन (ctx->op) अणु
	हाल SHA_OP_INIT:
		err = aपंचांगel_sha_hmac_setup(dd, aपंचांगel_sha_hmac_init_करोne);
		अवरोध;

	हाल SHA_OP_UPDATE:
		dd->resume = aपंचांगel_sha_करोne;
		err = aपंचांगel_sha_update_req(dd);
		अवरोध;

	हाल SHA_OP_FINAL:
		dd->resume = aपंचांगel_sha_hmac_final;
		err = aपंचांगel_sha_final_req(dd);
		अवरोध;

	हाल SHA_OP_DIGEST:
		err = aपंचांगel_sha_hmac_setup(dd, aपंचांगel_sha_hmac_digest2);
		अवरोध;

	शेष:
		वापस aपंचांगel_sha_complete(dd, -EINVAL);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);

	वापस aपंचांगel_sha_hmac_key_set(&hmac->hkey, key, keylen);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_init(काष्ठा ahash_request *req)
अणु
	पूर्णांक err;

	err = aपंचांगel_sha_init(req);
	अगर (err)
		वापस err;

	वापस aपंचांगel_sha_enqueue(req, SHA_OP_INIT);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_init_करोne(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	माप_प्रकार bs = ctx->block_size;
	माप_प्रकार hs = ctx->hash_size;

	ctx->bufcnt = 0;
	ctx->digcnt[0] = bs;
	ctx->digcnt[1] = 0;
	ctx->flags |= SHA_FLAGS_RESTORE;
	स_नकल(ctx->digest, hmac->ipad, hs);
	वापस aपंचांगel_sha_complete(dd, 0);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_final(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	u32 *digest = (u32 *)ctx->digest;
	माप_प्रकार ds = crypto_ahash_digestsize(tfm);
	माप_प्रकार bs = ctx->block_size;
	माप_प्रकार hs = ctx->hash_size;
	माप_प्रकार i, num_words;
	u32 mr;

	/* Save d = SHA((K' + ipad) | msg). */
	num_words = ds / माप(u32);
	क्रम (i = 0; i < num_words; ++i)
		digest[i] = aपंचांगel_sha_पढ़ो(dd, SHA_REG_DIGEST(i));

	/* Restore context to finish computing SHA((K' + opad) | d). */
	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_WUIHV);
	num_words = hs / माप(u32);
	क्रम (i = 0; i < num_words; ++i)
		aपंचांगel_sha_ग_लिखो(dd, SHA_REG_DIN(i), hmac->opad[i]);

	mr = SHA_MR_MODE_AUTO | SHA_MR_UIHV;
	mr |= (ctx->flags & SHA_FLAGS_ALGO_MASK);
	aपंचांगel_sha_ग_लिखो(dd, SHA_MR, mr);
	aपंचांगel_sha_ग_लिखो(dd, SHA_MSR, bs + ds);
	aपंचांगel_sha_ग_लिखो(dd, SHA_BCR, ds);
	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_FIRST);

	sg_init_one(&dd->पंचांगp, digest, ds);
	वापस aपंचांगel_sha_cpu_start(dd, &dd->पंचांगp, ds, false, true,
				   aपंचांगel_sha_hmac_final_करोne);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_final_करोne(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	/*
	 * req->result might not be माप(u32) aligned, so copy the
	 * digest पूर्णांकo ctx->digest[] beक्रमe स_नकल() the data पूर्णांकo
	 * req->result.
	 */
	aपंचांगel_sha_copy_hash(dd->req);
	aपंचांगel_sha_copy_पढ़ोy_hash(dd->req);
	वापस aपंचांगel_sha_complete(dd, 0);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक err;

	err = aपंचांगel_sha_init(req);
	अगर (err)
		वापस err;

	वापस aपंचांगel_sha_enqueue(req, SHA_OP_DIGEST);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_digest2(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	माप_प्रकार hs = ctx->hash_size;
	माप_प्रकार i, num_words = hs / माप(u32);
	bool use_dma = false;
	u32 mr;

	/* Special हाल क्रम empty message. */
	अगर (!req->nbytes)
		वापस aपंचांगel_sha_complete(dd, -EINVAL); // TODO:

	/* Check DMA threshold and alignment. */
	अगर (req->nbytes > ATMEL_SHA_DMA_THRESHOLD &&
	    aपंचांगel_sha_dma_check_aligned(dd, req->src, req->nbytes))
		use_dma = true;

	/* Write both initial hash values to compute a HMAC. */
	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_WUIHV);
	क्रम (i = 0; i < num_words; ++i)
		aपंचांगel_sha_ग_लिखो(dd, SHA_REG_DIN(i), hmac->ipad[i]);

	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_WUIEHV);
	क्रम (i = 0; i < num_words; ++i)
		aपंचांगel_sha_ग_लिखो(dd, SHA_REG_DIN(i), hmac->opad[i]);

	/* Write the Mode, Message Size, Bytes Count then Control Registers. */
	mr = (SHA_MR_HMAC | SHA_MR_DUALBUFF);
	mr |= ctx->flags & SHA_FLAGS_ALGO_MASK;
	अगर (use_dma)
		mr |= SHA_MR_MODE_IDATAR0;
	अन्यथा
		mr |= SHA_MR_MODE_AUTO;
	aपंचांगel_sha_ग_लिखो(dd, SHA_MR, mr);

	aपंचांगel_sha_ग_लिखो(dd, SHA_MSR, req->nbytes);
	aपंचांगel_sha_ग_लिखो(dd, SHA_BCR, req->nbytes);

	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_FIRST);

	/* Process data. */
	अगर (use_dma)
		वापस aपंचांगel_sha_dma_start(dd, req->src, req->nbytes,
					   aपंचांगel_sha_hmac_final_करोne);

	वापस aपंचांगel_sha_cpu_start(dd, req->src, req->nbytes, false, true,
				   aपंचांगel_sha_hmac_final_करोne);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_hmac_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_tfm_ctx(tfm);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा aपंचांगel_sha_reqctx));
	hmac->base.start = aपंचांगel_sha_hmac_start;
	aपंचांगel_sha_hmac_key_init(&hmac->hkey);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_sha_hmac_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_tfm_ctx(tfm);

	aपंचांगel_sha_hmac_key_release(&hmac->hkey);
पूर्ण

अटल व्योम aपंचांगel_sha_hmac_alg_init(काष्ठा ahash_alg *alg)
अणु
	alg->halg.base.cra_priority = ATMEL_SHA_PRIORITY;
	alg->halg.base.cra_flags = CRYPTO_ALG_ASYNC;
	alg->halg.base.cra_ctxsize = माप(काष्ठा aपंचांगel_sha_hmac_ctx);
	alg->halg.base.cra_module = THIS_MODULE;
	alg->halg.base.cra_init	= aपंचांगel_sha_hmac_cra_init;
	alg->halg.base.cra_निकास	= aपंचांगel_sha_hmac_cra_निकास;

	alg->halg.statesize = माप(काष्ठा aपंचांगel_sha_reqctx);

	alg->init = aपंचांगel_sha_hmac_init;
	alg->update = aपंचांगel_sha_update;
	alg->final = aपंचांगel_sha_final;
	alg->digest = aपंचांगel_sha_hmac_digest;
	alg->setkey = aपंचांगel_sha_hmac_setkey;
	alg->export = aपंचांगel_sha_export;
	alg->import = aपंचांगel_sha_import;
पूर्ण

अटल काष्ठा ahash_alg sha_hmac_algs[] = अणु
अणु
	.halg.base.cra_name		= "hmac(sha1)",
	.halg.base.cra_driver_name	= "atmel-hmac-sha1",
	.halg.base.cra_blocksize	= SHA1_BLOCK_SIZE,

	.halg.digestsize = SHA1_DIGEST_SIZE,
पूर्ण,
अणु
	.halg.base.cra_name		= "hmac(sha224)",
	.halg.base.cra_driver_name	= "atmel-hmac-sha224",
	.halg.base.cra_blocksize	= SHA224_BLOCK_SIZE,

	.halg.digestsize = SHA224_DIGEST_SIZE,
पूर्ण,
अणु
	.halg.base.cra_name		= "hmac(sha256)",
	.halg.base.cra_driver_name	= "atmel-hmac-sha256",
	.halg.base.cra_blocksize	= SHA256_BLOCK_SIZE,

	.halg.digestsize = SHA256_DIGEST_SIZE,
पूर्ण,
अणु
	.halg.base.cra_name		= "hmac(sha384)",
	.halg.base.cra_driver_name	= "atmel-hmac-sha384",
	.halg.base.cra_blocksize	= SHA384_BLOCK_SIZE,

	.halg.digestsize = SHA384_DIGEST_SIZE,
पूर्ण,
अणु
	.halg.base.cra_name		= "hmac(sha512)",
	.halg.base.cra_driver_name	= "atmel-hmac-sha512",
	.halg.base.cra_blocksize	= SHA512_BLOCK_SIZE,

	.halg.digestsize = SHA512_DIGEST_SIZE,
पूर्ण,
पूर्ण;

#अगर IS_ENABLED(CONFIG_CRYPTO_DEV_ATMEL_AUTHENC)
/* authenc functions */

अटल पूर्णांक aपंचांगel_sha_authenc_init2(काष्ठा aपंचांगel_sha_dev *dd);
अटल पूर्णांक aपंचांगel_sha_authenc_init_करोne(काष्ठा aपंचांगel_sha_dev *dd);
अटल पूर्णांक aपंचांगel_sha_authenc_final_करोne(काष्ठा aपंचांगel_sha_dev *dd);


काष्ठा aपंचांगel_sha_authenc_ctx अणु
	काष्ठा crypto_ahash	*tfm;
पूर्ण;

काष्ठा aपंचांगel_sha_authenc_reqctx अणु
	काष्ठा aपंचांगel_sha_reqctx	base;

	aपंचांगel_aes_authenc_fn_t	cb;
	काष्ठा aपंचांगel_aes_dev	*aes_dev;

	/* _init() parameters. */
	काष्ठा scatterlist	*assoc;
	u32			assoclen;
	u32			textlen;

	/* _final() parameters. */
	u32			*digest;
	अचिन्हित पूर्णांक		digestlen;
पूर्ण;

अटल व्योम aपंचांगel_sha_authenc_complete(काष्ठा crypto_async_request *areq,
				       पूर्णांक err)
अणु
	काष्ठा ahash_request *req = areq->data;
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx  = ahash_request_ctx(req);

	authctx->cb(authctx->aes_dev, err, authctx->base.dd->is_async);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_authenc_start(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx = ahash_request_ctx(req);
	पूर्णांक err;

	/*
	 * Force aपंचांगel_sha_complete() to call req->base.complete(), ie
	 * aपंचांगel_sha_authenc_complete(), which in turn calls authctx->cb().
	 */
	dd->क्रमce_complete = true;

	err = aपंचांगel_sha_hw_init(dd);
	वापस authctx->cb(authctx->aes_dev, err, dd->is_async);
पूर्ण

bool aपंचांगel_sha_authenc_is_पढ़ोy(व्योम)
अणु
	काष्ठा aपंचांगel_sha_ctx dummy;

	dummy.dd = शून्य;
	वापस (aपंचांगel_sha_find_dev(&dummy) != शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_is_पढ़ोy);

अचिन्हित पूर्णांक aपंचांगel_sha_authenc_get_reqsize(व्योम)
अणु
	वापस माप(काष्ठा aपंचांगel_sha_authenc_reqctx);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_get_reqsize);

काष्ठा aपंचांगel_sha_authenc_ctx *aपंचांगel_sha_authenc_spawn(अचिन्हित दीर्घ mode)
अणु
	काष्ठा aपंचांगel_sha_authenc_ctx *auth;
	काष्ठा crypto_ahash *tfm;
	काष्ठा aपंचांगel_sha_ctx *tctx;
	स्थिर अक्षर *name;
	पूर्णांक err = -EINVAL;

	चयन (mode & SHA_FLAGS_MODE_MASK) अणु
	हाल SHA_FLAGS_HMAC_SHA1:
		name = "atmel-hmac-sha1";
		अवरोध;

	हाल SHA_FLAGS_HMAC_SHA224:
		name = "atmel-hmac-sha224";
		अवरोध;

	हाल SHA_FLAGS_HMAC_SHA256:
		name = "atmel-hmac-sha256";
		अवरोध;

	हाल SHA_FLAGS_HMAC_SHA384:
		name = "atmel-hmac-sha384";
		अवरोध;

	हाल SHA_FLAGS_HMAC_SHA512:
		name = "atmel-hmac-sha512";
		अवरोध;

	शेष:
		जाओ error;
	पूर्ण

	tfm = crypto_alloc_ahash(name, 0, 0);
	अगर (IS_ERR(tfm)) अणु
		err = PTR_ERR(tfm);
		जाओ error;
	पूर्ण
	tctx = crypto_ahash_ctx(tfm);
	tctx->start = aपंचांगel_sha_authenc_start;
	tctx->flags = mode;

	auth = kzalloc(माप(*auth), GFP_KERNEL);
	अगर (!auth) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_ahash;
	पूर्ण
	auth->tfm = tfm;

	वापस auth;

err_मुक्त_ahash:
	crypto_मुक्त_ahash(tfm);
error:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_spawn);

व्योम aपंचांगel_sha_authenc_मुक्त(काष्ठा aपंचांगel_sha_authenc_ctx *auth)
अणु
	अगर (auth)
		crypto_मुक्त_ahash(auth->tfm);
	kमुक्त(auth);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_मुक्त);

पूर्णांक aपंचांगel_sha_authenc_setkey(काष्ठा aपंचांगel_sha_authenc_ctx *auth,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen, u32 flags)
अणु
	काष्ठा crypto_ahash *tfm = auth->tfm;

	crypto_ahash_clear_flags(tfm, CRYPTO_TFM_REQ_MASK);
	crypto_ahash_set_flags(tfm, flags & CRYPTO_TFM_REQ_MASK);
	वापस crypto_ahash_setkey(tfm, key, keylen);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_setkey);

पूर्णांक aपंचांगel_sha_authenc_schedule(काष्ठा ahash_request *req,
			       काष्ठा aपंचांगel_sha_authenc_ctx *auth,
			       aपंचांगel_aes_authenc_fn_t cb,
			       काष्ठा aपंचांगel_aes_dev *aes_dev)
अणु
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_reqctx *ctx = &authctx->base;
	काष्ठा crypto_ahash *tfm = auth->tfm;
	काष्ठा aपंचांगel_sha_ctx *tctx = crypto_ahash_ctx(tfm);
	काष्ठा aपंचांगel_sha_dev *dd;

	/* Reset request context (MUST be करोne first). */
	स_रखो(authctx, 0, माप(*authctx));

	/* Get SHA device. */
	dd = aपंचांगel_sha_find_dev(tctx);
	अगर (!dd)
		वापस cb(aes_dev, -ENODEV, false);

	/* Init request context. */
	ctx->dd = dd;
	ctx->buflen = SHA_BUFFER_LEN;
	authctx->cb = cb;
	authctx->aes_dev = aes_dev;
	ahash_request_set_tfm(req, tfm);
	ahash_request_set_callback(req, 0, aपंचांगel_sha_authenc_complete, req);

	वापस aपंचांगel_sha_handle_queue(dd, req);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_schedule);

पूर्णांक aपंचांगel_sha_authenc_init(काष्ठा ahash_request *req,
			   काष्ठा scatterlist *assoc, अचिन्हित पूर्णांक assoclen,
			   अचिन्हित पूर्णांक textlen,
			   aपंचांगel_aes_authenc_fn_t cb,
			   काष्ठा aपंचांगel_aes_dev *aes_dev)
अणु
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_reqctx *ctx = &authctx->base;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	काष्ठा aपंचांगel_sha_dev *dd = ctx->dd;

	अगर (unlikely(!IS_ALIGNED(assoclen, माप(u32))))
		वापस aपंचांगel_sha_complete(dd, -EINVAL);

	authctx->cb = cb;
	authctx->aes_dev = aes_dev;
	authctx->assoc = assoc;
	authctx->assoclen = assoclen;
	authctx->textlen = textlen;

	ctx->flags = hmac->base.flags;
	वापस aपंचांगel_sha_hmac_setup(dd, aपंचांगel_sha_authenc_init2);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_init);

अटल पूर्णांक aपंचांगel_sha_authenc_init2(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_reqctx *ctx = &authctx->base;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा aपंचांगel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);
	माप_प्रकार hs = ctx->hash_size;
	माप_प्रकार i, num_words = hs / माप(u32);
	u32 mr, msg_size;

	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_WUIHV);
	क्रम (i = 0; i < num_words; ++i)
		aपंचांगel_sha_ग_लिखो(dd, SHA_REG_DIN(i), hmac->ipad[i]);

	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_WUIEHV);
	क्रम (i = 0; i < num_words; ++i)
		aपंचांगel_sha_ग_लिखो(dd, SHA_REG_DIN(i), hmac->opad[i]);

	mr = (SHA_MR_MODE_IDATAR0 |
	      SHA_MR_HMAC |
	      SHA_MR_DUALBUFF);
	mr |= ctx->flags & SHA_FLAGS_ALGO_MASK;
	aपंचांगel_sha_ग_लिखो(dd, SHA_MR, mr);

	msg_size = authctx->assoclen + authctx->textlen;
	aपंचांगel_sha_ग_लिखो(dd, SHA_MSR, msg_size);
	aपंचांगel_sha_ग_लिखो(dd, SHA_BCR, msg_size);

	aपंचांगel_sha_ग_लिखो(dd, SHA_CR, SHA_CR_FIRST);

	/* Process assoc data. */
	वापस aपंचांगel_sha_cpu_start(dd, authctx->assoc, authctx->assoclen,
				   true, false,
				   aपंचांगel_sha_authenc_init_करोne);
पूर्ण

अटल पूर्णांक aपंचांगel_sha_authenc_init_करोne(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx = ahash_request_ctx(req);

	वापस authctx->cb(authctx->aes_dev, 0, dd->is_async);
पूर्ण

पूर्णांक aपंचांगel_sha_authenc_final(काष्ठा ahash_request *req,
			    u32 *digest, अचिन्हित पूर्णांक digestlen,
			    aपंचांगel_aes_authenc_fn_t cb,
			    काष्ठा aपंचांगel_aes_dev *aes_dev)
अणु
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_reqctx *ctx = &authctx->base;
	काष्ठा aपंचांगel_sha_dev *dd = ctx->dd;

	चयन (ctx->flags & SHA_FLAGS_ALGO_MASK) अणु
	हाल SHA_FLAGS_SHA1:
		authctx->digestlen = SHA1_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA224:
		authctx->digestlen = SHA224_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA256:
		authctx->digestlen = SHA256_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA384:
		authctx->digestlen = SHA384_DIGEST_SIZE;
		अवरोध;

	हाल SHA_FLAGS_SHA512:
		authctx->digestlen = SHA512_DIGEST_SIZE;
		अवरोध;

	शेष:
		वापस aपंचांगel_sha_complete(dd, -EINVAL);
	पूर्ण
	अगर (authctx->digestlen > digestlen)
		authctx->digestlen = digestlen;

	authctx->cb = cb;
	authctx->aes_dev = aes_dev;
	authctx->digest = digest;
	वापस aपंचांगel_sha_रुको_क्रम_data_पढ़ोy(dd,
					     aपंचांगel_sha_authenc_final_करोne);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_final);

अटल पूर्णांक aपंचांगel_sha_authenc_final_करोne(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	काष्ठा ahash_request *req = dd->req;
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx = ahash_request_ctx(req);
	माप_प्रकार i, num_words = authctx->digestlen / माप(u32);

	क्रम (i = 0; i < num_words; ++i)
		authctx->digest[i] = aपंचांगel_sha_पढ़ो(dd, SHA_REG_DIGEST(i));

	वापस aपंचांगel_sha_complete(dd, 0);
पूर्ण

व्योम aपंचांगel_sha_authenc_पात(काष्ठा ahash_request *req)
अणु
	काष्ठा aपंचांगel_sha_authenc_reqctx *authctx = ahash_request_ctx(req);
	काष्ठा aपंचांगel_sha_reqctx *ctx = &authctx->base;
	काष्ठा aपंचांगel_sha_dev *dd = ctx->dd;

	/* Prevent aपंचांगel_sha_complete() from calling req->base.complete(). */
	dd->is_async = false;
	dd->क्रमce_complete = false;
	(व्योम)aपंचांगel_sha_complete(dd, 0);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_sha_authenc_पात);

#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_ATMEL_AUTHENC */


अटल व्योम aपंचांगel_sha_unरेजिस्टर_algs(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	पूर्णांक i;

	अगर (dd->caps.has_hmac)
		क्रम (i = 0; i < ARRAY_SIZE(sha_hmac_algs); i++)
			crypto_unरेजिस्टर_ahash(&sha_hmac_algs[i]);

	क्रम (i = 0; i < ARRAY_SIZE(sha_1_256_algs); i++)
		crypto_unरेजिस्टर_ahash(&sha_1_256_algs[i]);

	अगर (dd->caps.has_sha224)
		crypto_unरेजिस्टर_ahash(&sha_224_alg);

	अगर (dd->caps.has_sha_384_512) अणु
		क्रम (i = 0; i < ARRAY_SIZE(sha_384_512_algs); i++)
			crypto_unरेजिस्टर_ahash(&sha_384_512_algs[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगel_sha_रेजिस्टर_algs(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	पूर्णांक err, i, j;

	क्रम (i = 0; i < ARRAY_SIZE(sha_1_256_algs); i++) अणु
		aपंचांगel_sha_alg_init(&sha_1_256_algs[i]);

		err = crypto_रेजिस्टर_ahash(&sha_1_256_algs[i]);
		अगर (err)
			जाओ err_sha_1_256_algs;
	पूर्ण

	अगर (dd->caps.has_sha224) अणु
		aपंचांगel_sha_alg_init(&sha_224_alg);

		err = crypto_रेजिस्टर_ahash(&sha_224_alg);
		अगर (err)
			जाओ err_sha_224_algs;
	पूर्ण

	अगर (dd->caps.has_sha_384_512) अणु
		क्रम (i = 0; i < ARRAY_SIZE(sha_384_512_algs); i++) अणु
			aपंचांगel_sha_alg_init(&sha_384_512_algs[i]);

			err = crypto_रेजिस्टर_ahash(&sha_384_512_algs[i]);
			अगर (err)
				जाओ err_sha_384_512_algs;
		पूर्ण
	पूर्ण

	अगर (dd->caps.has_hmac) अणु
		क्रम (i = 0; i < ARRAY_SIZE(sha_hmac_algs); i++) अणु
			aपंचांगel_sha_hmac_alg_init(&sha_hmac_algs[i]);

			err = crypto_रेजिस्टर_ahash(&sha_hmac_algs[i]);
			अगर (err)
				जाओ err_sha_hmac_algs;
		पूर्ण
	पूर्ण

	वापस 0;

	/*i = ARRAY_SIZE(sha_hmac_algs);*/
err_sha_hmac_algs:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_ahash(&sha_hmac_algs[j]);
	i = ARRAY_SIZE(sha_384_512_algs);
err_sha_384_512_algs:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_ahash(&sha_384_512_algs[j]);
	crypto_unरेजिस्टर_ahash(&sha_224_alg);
err_sha_224_algs:
	i = ARRAY_SIZE(sha_1_256_algs);
err_sha_1_256_algs:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_ahash(&sha_1_256_algs[j]);

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_dma_init(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	dd->dma_lch_in.chan = dma_request_chan(dd->dev, "tx");
	अगर (IS_ERR(dd->dma_lch_in.chan)) अणु
		dev_err(dd->dev, "DMA channel is not available\n");
		वापस PTR_ERR(dd->dma_lch_in.chan);
	पूर्ण

	dd->dma_lch_in.dma_conf.dst_addr = dd->phys_base +
		SHA_REG_DIN(0);
	dd->dma_lch_in.dma_conf.src_maxburst = 1;
	dd->dma_lch_in.dma_conf.src_addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dd->dma_lch_in.dma_conf.dst_maxburst = 1;
	dd->dma_lch_in.dma_conf.dst_addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dd->dma_lch_in.dma_conf.device_fc = false;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_sha_dma_cleanup(काष्ठा aपंचांगel_sha_dev *dd)
अणु
	dma_release_channel(dd->dma_lch_in.chan);
पूर्ण

अटल व्योम aपंचांगel_sha_get_cap(काष्ठा aपंचांगel_sha_dev *dd)
अणु

	dd->caps.has_dma = 0;
	dd->caps.has_dualbuff = 0;
	dd->caps.has_sha224 = 0;
	dd->caps.has_sha_384_512 = 0;
	dd->caps.has_uihv = 0;
	dd->caps.has_hmac = 0;

	/* keep only major version number */
	चयन (dd->hw_version & 0xff0) अणु
	हाल 0x510:
		dd->caps.has_dma = 1;
		dd->caps.has_dualbuff = 1;
		dd->caps.has_sha224 = 1;
		dd->caps.has_sha_384_512 = 1;
		dd->caps.has_uihv = 1;
		dd->caps.has_hmac = 1;
		अवरोध;
	हाल 0x420:
		dd->caps.has_dma = 1;
		dd->caps.has_dualbuff = 1;
		dd->caps.has_sha224 = 1;
		dd->caps.has_sha_384_512 = 1;
		dd->caps.has_uihv = 1;
		अवरोध;
	हाल 0x410:
		dd->caps.has_dma = 1;
		dd->caps.has_dualbuff = 1;
		dd->caps.has_sha224 = 1;
		dd->caps.has_sha_384_512 = 1;
		अवरोध;
	हाल 0x400:
		dd->caps.has_dma = 1;
		dd->caps.has_dualbuff = 1;
		dd->caps.has_sha224 = 1;
		अवरोध;
	हाल 0x320:
		अवरोध;
	शेष:
		dev_warn(dd->dev,
				"Unmanaged sha version, set minimum capabilities\n");
		अवरोध;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id aपंचांगel_sha_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9g46-sha" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगel_sha_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक aपंचांगel_sha_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_sha_dev *sha_dd;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *sha_res;
	पूर्णांक err;

	sha_dd = devm_kzalloc(&pdev->dev, माप(*sha_dd), GFP_KERNEL);
	अगर (!sha_dd)
		वापस -ENOMEM;

	sha_dd->dev = dev;

	platक्रमm_set_drvdata(pdev, sha_dd);

	INIT_LIST_HEAD(&sha_dd->list);
	spin_lock_init(&sha_dd->lock);

	tasklet_init(&sha_dd->करोne_task, aपंचांगel_sha_करोne_task,
					(अचिन्हित दीर्घ)sha_dd);
	tasklet_init(&sha_dd->queue_task, aपंचांगel_sha_queue_task,
					(अचिन्हित दीर्घ)sha_dd);

	crypto_init_queue(&sha_dd->queue, ATMEL_SHA_QUEUE_LENGTH);

	/* Get the base address */
	sha_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!sha_res) अणु
		dev_err(dev, "no MEM resource info\n");
		err = -ENODEV;
		जाओ err_tasklet_समाप्त;
	पूर्ण
	sha_dd->phys_base = sha_res->start;

	/* Get the IRQ */
	sha_dd->irq = platक्रमm_get_irq(pdev,  0);
	अगर (sha_dd->irq < 0) अणु
		err = sha_dd->irq;
		जाओ err_tasklet_समाप्त;
	पूर्ण

	err = devm_request_irq(&pdev->dev, sha_dd->irq, aपंचांगel_sha_irq,
			       IRQF_SHARED, "atmel-sha", sha_dd);
	अगर (err) अणु
		dev_err(dev, "unable to request sha irq.\n");
		जाओ err_tasklet_समाप्त;
	पूर्ण

	/* Initializing the घड़ी */
	sha_dd->iclk = devm_clk_get(&pdev->dev, "sha_clk");
	अगर (IS_ERR(sha_dd->iclk)) अणु
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(sha_dd->iclk);
		जाओ err_tasklet_समाप्त;
	पूर्ण

	sha_dd->io_base = devm_ioremap_resource(&pdev->dev, sha_res);
	अगर (IS_ERR(sha_dd->io_base)) अणु
		dev_err(dev, "can't ioremap\n");
		err = PTR_ERR(sha_dd->io_base);
		जाओ err_tasklet_समाप्त;
	पूर्ण

	err = clk_prepare(sha_dd->iclk);
	अगर (err)
		जाओ err_tasklet_समाप्त;

	err = aपंचांगel_sha_hw_version_init(sha_dd);
	अगर (err)
		जाओ err_iclk_unprepare;

	aपंचांगel_sha_get_cap(sha_dd);

	अगर (sha_dd->caps.has_dma) अणु
		err = aपंचांगel_sha_dma_init(sha_dd);
		अगर (err)
			जाओ err_iclk_unprepare;

		dev_info(dev, "using %s for DMA transfers\n",
				dma_chan_name(sha_dd->dma_lch_in.chan));
	पूर्ण

	spin_lock(&aपंचांगel_sha.lock);
	list_add_tail(&sha_dd->list, &aपंचांगel_sha.dev_list);
	spin_unlock(&aपंचांगel_sha.lock);

	err = aपंचांगel_sha_रेजिस्टर_algs(sha_dd);
	अगर (err)
		जाओ err_algs;

	dev_info(dev, "Atmel SHA1/SHA256%s%s\n",
			sha_dd->caps.has_sha224 ? "/SHA224" : "",
			sha_dd->caps.has_sha_384_512 ? "/SHA384/SHA512" : "");

	वापस 0;

err_algs:
	spin_lock(&aपंचांगel_sha.lock);
	list_del(&sha_dd->list);
	spin_unlock(&aपंचांगel_sha.lock);
	अगर (sha_dd->caps.has_dma)
		aपंचांगel_sha_dma_cleanup(sha_dd);
err_iclk_unprepare:
	clk_unprepare(sha_dd->iclk);
err_tasklet_समाप्त:
	tasklet_समाप्त(&sha_dd->queue_task);
	tasklet_समाप्त(&sha_dd->करोne_task);

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_sha_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_sha_dev *sha_dd;

	sha_dd = platक्रमm_get_drvdata(pdev);
	अगर (!sha_dd)
		वापस -ENODEV;
	spin_lock(&aपंचांगel_sha.lock);
	list_del(&sha_dd->list);
	spin_unlock(&aपंचांगel_sha.lock);

	aपंचांगel_sha_unरेजिस्टर_algs(sha_dd);

	tasklet_समाप्त(&sha_dd->queue_task);
	tasklet_समाप्त(&sha_dd->करोne_task);

	अगर (sha_dd->caps.has_dma)
		aपंचांगel_sha_dma_cleanup(sha_dd);

	clk_unprepare(sha_dd->iclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_sha_driver = अणु
	.probe		= aपंचांगel_sha_probe,
	.हटाओ		= aपंचांगel_sha_हटाओ,
	.driver		= अणु
		.name	= "atmel_sha",
		.of_match_table	= of_match_ptr(aपंचांगel_sha_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(aपंचांगel_sha_driver);

MODULE_DESCRIPTION("Atmel SHA (1/256/224/384/512) hw acceleration support.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Nicolas Royer - Eukrथऊa Electromatique");
