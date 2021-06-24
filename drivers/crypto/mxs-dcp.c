<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale i.MX23/i.MX28 Data Co-Processor driver
 *
 * Copyright (C) 2013 Marek Vasut <marex@denx.de>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <linux/clk.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>

#घोषणा DCP_MAX_CHANS	4
#घोषणा DCP_BUF_SZ	PAGE_SIZE
#घोषणा DCP_SHA_PAY_SZ  64

#घोषणा DCP_ALIGNMENT	64

/*
 * Null hashes to align with hw behavior on imx6sl and ull
 * these are flipped क्रम consistency with hw output
 */
अटल स्थिर uपूर्णांक8_t sha1_null_hash[] =
	"\x09\x07\xd8\xaf\x90\x18\x60\x95\xef\xbf"
	"\x55\x32\x0d\x4b\x6b\x5e\xee\xa3\x39\xda";

अटल स्थिर uपूर्णांक8_t sha256_null_hash[] =
	"\x55\xb8\x52\x78\x1b\x99\x95\xa4"
	"\x4c\x93\x9b\x64\xe4\x41\xae\x27"
	"\x24\xb9\x6f\x99\xc8\xf4\xfb\x9a"
	"\x14\x1c\xfc\x98\x42\xc4\xb0\xe3";

/* DCP DMA descriptor. */
काष्ठा dcp_dma_desc अणु
	uपूर्णांक32_t	next_cmd_addr;
	uपूर्णांक32_t	control0;
	uपूर्णांक32_t	control1;
	uपूर्णांक32_t	source;
	uपूर्णांक32_t	destination;
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	payload;
	uपूर्णांक32_t	status;
पूर्ण;

/* Coherent aligned block क्रम bounce buffering. */
काष्ठा dcp_coherent_block अणु
	uपूर्णांक8_t			aes_in_buf[DCP_BUF_SZ];
	uपूर्णांक8_t			aes_out_buf[DCP_BUF_SZ];
	uपूर्णांक8_t			sha_in_buf[DCP_BUF_SZ];
	uपूर्णांक8_t			sha_out_buf[DCP_SHA_PAY_SZ];

	uपूर्णांक8_t			aes_key[2 * AES_KEYSIZE_128];

	काष्ठा dcp_dma_desc	desc[DCP_MAX_CHANS];
पूर्ण;

काष्ठा dcp अणु
	काष्ठा device			*dev;
	व्योम __iomem			*base;

	uपूर्णांक32_t			caps;

	काष्ठा dcp_coherent_block	*coh;

	काष्ठा completion		completion[DCP_MAX_CHANS];
	spinlock_t			lock[DCP_MAX_CHANS];
	काष्ठा task_काष्ठा		*thपढ़ो[DCP_MAX_CHANS];
	काष्ठा crypto_queue		queue[DCP_MAX_CHANS];
	काष्ठा clk			*dcp_clk;
पूर्ण;

क्रमागत dcp_chan अणु
	DCP_CHAN_HASH_SHA	= 0,
	DCP_CHAN_CRYPTO		= 2,
पूर्ण;

काष्ठा dcp_async_ctx अणु
	/* Common context */
	क्रमागत dcp_chan	chan;
	uपूर्णांक32_t	fill;

	/* SHA Hash-specअगरic context */
	काष्ठा mutex			mutex;
	uपूर्णांक32_t			alg;
	अचिन्हित पूर्णांक			hot:1;

	/* Crypto-specअगरic context */
	काष्ठा crypto_skcipher		*fallback;
	अचिन्हित पूर्णांक			key_len;
	uपूर्णांक8_t				key[AES_KEYSIZE_128];
पूर्ण;

काष्ठा dcp_aes_req_ctx अणु
	अचिन्हित पूर्णांक	enc:1;
	अचिन्हित पूर्णांक	ecb:1;
	काष्ठा skcipher_request fallback_req;	// keep at the end
पूर्ण;

काष्ठा dcp_sha_req_ctx अणु
	अचिन्हित पूर्णांक	init:1;
	अचिन्हित पूर्णांक	fini:1;
पूर्ण;

काष्ठा dcp_export_state अणु
	काष्ठा dcp_sha_req_ctx req_ctx;
	काष्ठा dcp_async_ctx async_ctx;
पूर्ण;

/*
 * There can even be only one instance of the MXS DCP due to the
 * design of Linux Crypto API.
 */
अटल काष्ठा dcp *global_sdcp;

/* DCP रेजिस्टर layout. */
#घोषणा MXS_DCP_CTRL				0x00
#घोषणा MXS_DCP_CTRL_GATHER_RESIDUAL_WRITES	(1 << 23)
#घोषणा MXS_DCP_CTRL_ENABLE_CONTEXT_CACHING	(1 << 22)

#घोषणा MXS_DCP_STAT				0x10
#घोषणा MXS_DCP_STAT_CLR			0x18
#घोषणा MXS_DCP_STAT_IRQ_MASK			0xf

#घोषणा MXS_DCP_CHANNELCTRL			0x20
#घोषणा MXS_DCP_CHANNELCTRL_ENABLE_CHANNEL_MASK	0xff

#घोषणा MXS_DCP_CAPABILITY1			0x40
#घोषणा MXS_DCP_CAPABILITY1_SHA256		(4 << 16)
#घोषणा MXS_DCP_CAPABILITY1_SHA1		(1 << 16)
#घोषणा MXS_DCP_CAPABILITY1_AES128		(1 << 0)

#घोषणा MXS_DCP_CONTEXT				0x50

#घोषणा MXS_DCP_CH_N_CMDPTR(n)			(0x100 + ((n) * 0x40))

#घोषणा MXS_DCP_CH_N_SEMA(n)			(0x110 + ((n) * 0x40))

#घोषणा MXS_DCP_CH_N_STAT(n)			(0x120 + ((n) * 0x40))
#घोषणा MXS_DCP_CH_N_STAT_CLR(n)		(0x128 + ((n) * 0x40))

/* DMA descriptor bits. */
#घोषणा MXS_DCP_CONTROL0_HASH_TERM		(1 << 13)
#घोषणा MXS_DCP_CONTROL0_HASH_INIT		(1 << 12)
#घोषणा MXS_DCP_CONTROL0_PAYLOAD_KEY		(1 << 11)
#घोषणा MXS_DCP_CONTROL0_CIPHER_ENCRYPT		(1 << 8)
#घोषणा MXS_DCP_CONTROL0_CIPHER_INIT		(1 << 9)
#घोषणा MXS_DCP_CONTROL0_ENABLE_HASH		(1 << 6)
#घोषणा MXS_DCP_CONTROL0_ENABLE_CIPHER		(1 << 5)
#घोषणा MXS_DCP_CONTROL0_DECR_SEMAPHORE		(1 << 1)
#घोषणा MXS_DCP_CONTROL0_INTERRUPT		(1 << 0)

#घोषणा MXS_DCP_CONTROL1_HASH_SELECT_SHA256	(2 << 16)
#घोषणा MXS_DCP_CONTROL1_HASH_SELECT_SHA1	(0 << 16)
#घोषणा MXS_DCP_CONTROL1_CIPHER_MODE_CBC	(1 << 4)
#घोषणा MXS_DCP_CONTROL1_CIPHER_MODE_ECB	(0 << 4)
#घोषणा MXS_DCP_CONTROL1_CIPHER_SELECT_AES128	(0 << 0)

अटल पूर्णांक mxs_dcp_start_dma(काष्ठा dcp_async_ctx *actx)
अणु
	काष्ठा dcp *sdcp = global_sdcp;
	स्थिर पूर्णांक chan = actx->chan;
	uपूर्णांक32_t stat;
	अचिन्हित दीर्घ ret;
	काष्ठा dcp_dma_desc *desc = &sdcp->coh->desc[actx->chan];

	dma_addr_t desc_phys = dma_map_single(sdcp->dev, desc, माप(*desc),
					      DMA_TO_DEVICE);

	reinit_completion(&sdcp->completion[chan]);

	/* Clear status रेजिस्टर. */
	ग_लिखोl(0xffffffff, sdcp->base + MXS_DCP_CH_N_STAT_CLR(chan));

	/* Load the DMA descriptor. */
	ग_लिखोl(desc_phys, sdcp->base + MXS_DCP_CH_N_CMDPTR(chan));

	/* Increment the semaphore to start the DMA transfer. */
	ग_लिखोl(1, sdcp->base + MXS_DCP_CH_N_SEMA(chan));

	ret = रुको_क्रम_completion_समयout(&sdcp->completion[chan],
					  msecs_to_jअगरfies(1000));
	अगर (!ret) अणु
		dev_err(sdcp->dev, "Channel %i timeout (DCP_STAT=0x%08x)\n",
			chan, पढ़ोl(sdcp->base + MXS_DCP_STAT));
		वापस -ETIMEDOUT;
	पूर्ण

	stat = पढ़ोl(sdcp->base + MXS_DCP_CH_N_STAT(chan));
	अगर (stat & 0xff) अणु
		dev_err(sdcp->dev, "Channel %i error (CH_STAT=0x%08x)\n",
			chan, stat);
		वापस -EINVAL;
	पूर्ण

	dma_unmap_single(sdcp->dev, desc_phys, माप(*desc), DMA_TO_DEVICE);

	वापस 0;
पूर्ण

/*
 * Encryption (AES128)
 */
अटल पूर्णांक mxs_dcp_run_aes(काष्ठा dcp_async_ctx *actx,
			   काष्ठा skcipher_request *req, पूर्णांक init)
अणु
	काष्ठा dcp *sdcp = global_sdcp;
	काष्ठा dcp_dma_desc *desc = &sdcp->coh->desc[actx->chan];
	काष्ठा dcp_aes_req_ctx *rctx = skcipher_request_ctx(req);
	पूर्णांक ret;

	dma_addr_t key_phys = dma_map_single(sdcp->dev, sdcp->coh->aes_key,
					     2 * AES_KEYSIZE_128,
					     DMA_TO_DEVICE);
	dma_addr_t src_phys = dma_map_single(sdcp->dev, sdcp->coh->aes_in_buf,
					     DCP_BUF_SZ, DMA_TO_DEVICE);
	dma_addr_t dst_phys = dma_map_single(sdcp->dev, sdcp->coh->aes_out_buf,
					     DCP_BUF_SZ, DMA_FROM_DEVICE);

	अगर (actx->fill % AES_BLOCK_SIZE) अणु
		dev_err(sdcp->dev, "Invalid block size!\n");
		ret = -EINVAL;
		जाओ aes_करोne_run;
	पूर्ण

	/* Fill in the DMA descriptor. */
	desc->control0 = MXS_DCP_CONTROL0_DECR_SEMAPHORE |
		    MXS_DCP_CONTROL0_INTERRUPT |
		    MXS_DCP_CONTROL0_ENABLE_CIPHER;

	/* Payload contains the key. */
	desc->control0 |= MXS_DCP_CONTROL0_PAYLOAD_KEY;

	अगर (rctx->enc)
		desc->control0 |= MXS_DCP_CONTROL0_CIPHER_ENCRYPT;
	अगर (init)
		desc->control0 |= MXS_DCP_CONTROL0_CIPHER_INIT;

	desc->control1 = MXS_DCP_CONTROL1_CIPHER_SELECT_AES128;

	अगर (rctx->ecb)
		desc->control1 |= MXS_DCP_CONTROL1_CIPHER_MODE_ECB;
	अन्यथा
		desc->control1 |= MXS_DCP_CONTROL1_CIPHER_MODE_CBC;

	desc->next_cmd_addr = 0;
	desc->source = src_phys;
	desc->destination = dst_phys;
	desc->size = actx->fill;
	desc->payload = key_phys;
	desc->status = 0;

	ret = mxs_dcp_start_dma(actx);

aes_करोne_run:
	dma_unmap_single(sdcp->dev, key_phys, 2 * AES_KEYSIZE_128,
			 DMA_TO_DEVICE);
	dma_unmap_single(sdcp->dev, src_phys, DCP_BUF_SZ, DMA_TO_DEVICE);
	dma_unmap_single(sdcp->dev, dst_phys, DCP_BUF_SZ, DMA_FROM_DEVICE);

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_dcp_aes_block_crypt(काष्ठा crypto_async_request *arq)
अणु
	काष्ठा dcp *sdcp = global_sdcp;

	काष्ठा skcipher_request *req = skcipher_request_cast(arq);
	काष्ठा dcp_async_ctx *actx = crypto_tfm_ctx(arq->tfm);
	काष्ठा dcp_aes_req_ctx *rctx = skcipher_request_ctx(req);

	काष्ठा scatterlist *dst = req->dst;
	काष्ठा scatterlist *src = req->src;
	स्थिर पूर्णांक nents = sg_nents(req->src);

	स्थिर पूर्णांक out_off = DCP_BUF_SZ;
	uपूर्णांक8_t *in_buf = sdcp->coh->aes_in_buf;
	uपूर्णांक8_t *out_buf = sdcp->coh->aes_out_buf;

	uपूर्णांक8_t *out_पंचांगp, *src_buf, *dst_buf = शून्य;
	uपूर्णांक32_t dst_off = 0;
	uपूर्णांक32_t last_out_len = 0;

	uपूर्णांक8_t *key = sdcp->coh->aes_key;

	पूर्णांक ret = 0;
	पूर्णांक split = 0;
	अचिन्हित पूर्णांक i, len, clen, rem = 0, tlen = 0;
	पूर्णांक init = 0;
	bool limit_hit = false;

	actx->fill = 0;

	/* Copy the key from the temporary location. */
	स_नकल(key, actx->key, actx->key_len);

	अगर (!rctx->ecb) अणु
		/* Copy the CBC IV just past the key. */
		स_नकल(key + AES_KEYSIZE_128, req->iv, AES_KEYSIZE_128);
		/* CBC needs the INIT set. */
		init = 1;
	पूर्ण अन्यथा अणु
		स_रखो(key + AES_KEYSIZE_128, 0, AES_KEYSIZE_128);
	पूर्ण

	क्रम_each_sg(req->src, src, nents, i) अणु
		src_buf = sg_virt(src);
		len = sg_dma_len(src);
		tlen += len;
		limit_hit = tlen > req->cryptlen;

		अगर (limit_hit)
			len = req->cryptlen - (tlen - len);

		करो अणु
			अगर (actx->fill + len > out_off)
				clen = out_off - actx->fill;
			अन्यथा
				clen = len;

			स_नकल(in_buf + actx->fill, src_buf, clen);
			len -= clen;
			src_buf += clen;
			actx->fill += clen;

			/*
			 * If we filled the buffer or this is the last SG,
			 * submit the buffer.
			 */
			अगर (actx->fill == out_off || sg_is_last(src) ||
				limit_hit) अणु
				ret = mxs_dcp_run_aes(actx, req, init);
				अगर (ret)
					वापस ret;
				init = 0;

				out_पंचांगp = out_buf;
				last_out_len = actx->fill;
				जबतक (dst && actx->fill) अणु
					अगर (!split) अणु
						dst_buf = sg_virt(dst);
						dst_off = 0;
					पूर्ण
					rem = min(sg_dma_len(dst) - dst_off,
						  actx->fill);

					स_नकल(dst_buf + dst_off, out_पंचांगp, rem);
					out_पंचांगp += rem;
					dst_off += rem;
					actx->fill -= rem;

					अगर (dst_off == sg_dma_len(dst)) अणु
						dst = sg_next(dst);
						split = 0;
					पूर्ण अन्यथा अणु
						split = 1;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण जबतक (len);

		अगर (limit_hit)
			अवरोध;
	पूर्ण

	/* Copy the IV क्रम CBC क्रम chaining */
	अगर (!rctx->ecb) अणु
		अगर (rctx->enc)
			स_नकल(req->iv, out_buf+(last_out_len-AES_BLOCK_SIZE),
				AES_BLOCK_SIZE);
		अन्यथा
			स_नकल(req->iv, in_buf+(last_out_len-AES_BLOCK_SIZE),
				AES_BLOCK_SIZE);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dcp_chan_thपढ़ो_aes(व्योम *data)
अणु
	काष्ठा dcp *sdcp = global_sdcp;
	स्थिर पूर्णांक chan = DCP_CHAN_CRYPTO;

	काष्ठा crypto_async_request *backlog;
	काष्ठा crypto_async_request *arq;

	पूर्णांक ret;

	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		spin_lock(&sdcp->lock[chan]);
		backlog = crypto_get_backlog(&sdcp->queue[chan]);
		arq = crypto_dequeue_request(&sdcp->queue[chan]);
		spin_unlock(&sdcp->lock[chan]);

		अगर (!backlog && !arq) अणु
			schedule();
			जारी;
		पूर्ण

		set_current_state(TASK_RUNNING);

		अगर (backlog)
			backlog->complete(backlog, -EINPROGRESS);

		अगर (arq) अणु
			ret = mxs_dcp_aes_block_crypt(arq);
			arq->complete(arq, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_dcp_block_fallback(काष्ठा skcipher_request *req, पूर्णांक enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा dcp_aes_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा dcp_async_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक ret;

	skcipher_request_set_tfm(&rctx->fallback_req, ctx->fallback);
	skcipher_request_set_callback(&rctx->fallback_req, req->base.flags,
				      req->base.complete, req->base.data);
	skcipher_request_set_crypt(&rctx->fallback_req, req->src, req->dst,
				   req->cryptlen, req->iv);

	अगर (enc)
		ret = crypto_skcipher_encrypt(&rctx->fallback_req);
	अन्यथा
		ret = crypto_skcipher_decrypt(&rctx->fallback_req);

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_dcp_aes_enqueue(काष्ठा skcipher_request *req, पूर्णांक enc, पूर्णांक ecb)
अणु
	काष्ठा dcp *sdcp = global_sdcp;
	काष्ठा crypto_async_request *arq = &req->base;
	काष्ठा dcp_async_ctx *actx = crypto_tfm_ctx(arq->tfm);
	काष्ठा dcp_aes_req_ctx *rctx = skcipher_request_ctx(req);
	पूर्णांक ret;

	अगर (unlikely(actx->key_len != AES_KEYSIZE_128))
		वापस mxs_dcp_block_fallback(req, enc);

	rctx->enc = enc;
	rctx->ecb = ecb;
	actx->chan = DCP_CHAN_CRYPTO;

	spin_lock(&sdcp->lock[actx->chan]);
	ret = crypto_enqueue_request(&sdcp->queue[actx->chan], &req->base);
	spin_unlock(&sdcp->lock[actx->chan]);

	wake_up_process(sdcp->thपढ़ो[actx->chan]);

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_dcp_aes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस mxs_dcp_aes_enqueue(req, 0, 1);
पूर्ण

अटल पूर्णांक mxs_dcp_aes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस mxs_dcp_aes_enqueue(req, 1, 1);
पूर्ण

अटल पूर्णांक mxs_dcp_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस mxs_dcp_aes_enqueue(req, 0, 0);
पूर्ण

अटल पूर्णांक mxs_dcp_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस mxs_dcp_aes_enqueue(req, 1, 0);
पूर्ण

अटल पूर्णांक mxs_dcp_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा dcp_async_ctx *actx = crypto_skcipher_ctx(tfm);

	/*
	 * AES 128 is supposed by the hardware, store key पूर्णांकo temporary
	 * buffer and निकास. We must use the temporary buffer here, since
	 * there can still be an operation in progress.
	 */
	actx->key_len = len;
	अगर (len == AES_KEYSIZE_128) अणु
		स_नकल(actx->key, key, len);
		वापस 0;
	पूर्ण

	/*
	 * If the requested AES key size is not supported by the hardware,
	 * but is supported by in-kernel software implementation, we use
	 * software fallback.
	 */
	crypto_skcipher_clear_flags(actx->fallback, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(actx->fallback,
				  tfm->base.crt_flags & CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(actx->fallback, key, len);
पूर्ण

अटल पूर्णांक mxs_dcp_aes_fallback_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	स्थिर अक्षर *name = crypto_tfm_alg_name(crypto_skcipher_tfm(tfm));
	काष्ठा dcp_async_ctx *actx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *blk;

	blk = crypto_alloc_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(blk))
		वापस PTR_ERR(blk);

	actx->fallback = blk;
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा dcp_aes_req_ctx) +
					 crypto_skcipher_reqsize(blk));
	वापस 0;
पूर्ण

अटल व्योम mxs_dcp_aes_fallback_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा dcp_async_ctx *actx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(actx->fallback);
पूर्ण

/*
 * Hashing (SHA1/SHA256)
 */
अटल पूर्णांक mxs_dcp_run_sha(काष्ठा ahash_request *req)
अणु
	काष्ठा dcp *sdcp = global_sdcp;
	पूर्णांक ret;

	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा dcp_async_ctx *actx = crypto_ahash_ctx(tfm);
	काष्ठा dcp_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा dcp_dma_desc *desc = &sdcp->coh->desc[actx->chan];

	dma_addr_t digest_phys = 0;
	dma_addr_t buf_phys = dma_map_single(sdcp->dev, sdcp->coh->sha_in_buf,
					     DCP_BUF_SZ, DMA_TO_DEVICE);

	/* Fill in the DMA descriptor. */
	desc->control0 = MXS_DCP_CONTROL0_DECR_SEMAPHORE |
		    MXS_DCP_CONTROL0_INTERRUPT |
		    MXS_DCP_CONTROL0_ENABLE_HASH;
	अगर (rctx->init)
		desc->control0 |= MXS_DCP_CONTROL0_HASH_INIT;

	desc->control1 = actx->alg;
	desc->next_cmd_addr = 0;
	desc->source = buf_phys;
	desc->destination = 0;
	desc->size = actx->fill;
	desc->payload = 0;
	desc->status = 0;

	/*
	 * Align driver with hw behavior when generating null hashes
	 */
	अगर (rctx->init && rctx->fini && desc->size == 0) अणु
		काष्ठा hash_alg_common *halg = crypto_hash_alg_common(tfm);
		स्थिर uपूर्णांक8_t *sha_buf =
			(actx->alg == MXS_DCP_CONTROL1_HASH_SELECT_SHA1) ?
			sha1_null_hash : sha256_null_hash;
		स_नकल(sdcp->coh->sha_out_buf, sha_buf, halg->digestsize);
		ret = 0;
		जाओ करोne_run;
	पूर्ण

	/* Set HASH_TERM bit क्रम last transfer block. */
	अगर (rctx->fini) अणु
		digest_phys = dma_map_single(sdcp->dev, sdcp->coh->sha_out_buf,
					     DCP_SHA_PAY_SZ, DMA_FROM_DEVICE);
		desc->control0 |= MXS_DCP_CONTROL0_HASH_TERM;
		desc->payload = digest_phys;
	पूर्ण

	ret = mxs_dcp_start_dma(actx);

	अगर (rctx->fini)
		dma_unmap_single(sdcp->dev, digest_phys, DCP_SHA_PAY_SZ,
				 DMA_FROM_DEVICE);

करोne_run:
	dma_unmap_single(sdcp->dev, buf_phys, DCP_BUF_SZ, DMA_TO_DEVICE);

	वापस ret;
पूर्ण

अटल पूर्णांक dcp_sha_req_to_buf(काष्ठा crypto_async_request *arq)
अणु
	काष्ठा dcp *sdcp = global_sdcp;

	काष्ठा ahash_request *req = ahash_request_cast(arq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा dcp_async_ctx *actx = crypto_ahash_ctx(tfm);
	काष्ठा dcp_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा hash_alg_common *halg = crypto_hash_alg_common(tfm);

	uपूर्णांक8_t *in_buf = sdcp->coh->sha_in_buf;
	uपूर्णांक8_t *out_buf = sdcp->coh->sha_out_buf;

	काष्ठा scatterlist *src;

	अचिन्हित पूर्णांक i, len, clen, oft = 0;
	पूर्णांक ret;

	पूर्णांक fin = rctx->fini;
	अगर (fin)
		rctx->fini = 0;

	src = req->src;
	len = req->nbytes;

	जबतक (len) अणु
		अगर (actx->fill + len > DCP_BUF_SZ)
			clen = DCP_BUF_SZ - actx->fill;
		अन्यथा
			clen = len;

		scatterwalk_map_and_copy(in_buf + actx->fill, src, oft, clen,
					 0);

		len -= clen;
		oft += clen;
		actx->fill += clen;

		/*
		 * If we filled the buffer and still have some
		 * more data, submit the buffer.
		 */
		अगर (len && actx->fill == DCP_BUF_SZ) अणु
			ret = mxs_dcp_run_sha(req);
			अगर (ret)
				वापस ret;
			actx->fill = 0;
			rctx->init = 0;
		पूर्ण
	पूर्ण

	अगर (fin) अणु
		rctx->fini = 1;

		/* Submit whatever is left. */
		अगर (!req->result)
			वापस -EINVAL;

		ret = mxs_dcp_run_sha(req);
		अगर (ret)
			वापस ret;

		actx->fill = 0;

		/* For some reason the result is flipped */
		क्रम (i = 0; i < halg->digestsize; i++)
			req->result[i] = out_buf[halg->digestsize - i - 1];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dcp_chan_thपढ़ो_sha(व्योम *data)
अणु
	काष्ठा dcp *sdcp = global_sdcp;
	स्थिर पूर्णांक chan = DCP_CHAN_HASH_SHA;

	काष्ठा crypto_async_request *backlog;
	काष्ठा crypto_async_request *arq;
	पूर्णांक ret;

	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		spin_lock(&sdcp->lock[chan]);
		backlog = crypto_get_backlog(&sdcp->queue[chan]);
		arq = crypto_dequeue_request(&sdcp->queue[chan]);
		spin_unlock(&sdcp->lock[chan]);

		अगर (!backlog && !arq) अणु
			schedule();
			जारी;
		पूर्ण

		set_current_state(TASK_RUNNING);

		अगर (backlog)
			backlog->complete(backlog, -EINPROGRESS);

		अगर (arq) अणु
			ret = dcp_sha_req_to_buf(arq);
			arq->complete(arq, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dcp_sha_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा dcp_async_ctx *actx = crypto_ahash_ctx(tfm);

	काष्ठा hash_alg_common *halg = crypto_hash_alg_common(tfm);

	/*
	 * Start hashing session. The code below only inits the
	 * hashing session context, nothing more.
	 */
	स_रखो(actx, 0, माप(*actx));

	अगर (म_भेद(halg->base.cra_name, "sha1") == 0)
		actx->alg = MXS_DCP_CONTROL1_HASH_SELECT_SHA1;
	अन्यथा
		actx->alg = MXS_DCP_CONTROL1_HASH_SELECT_SHA256;

	actx->fill = 0;
	actx->hot = 0;
	actx->chan = DCP_CHAN_HASH_SHA;

	mutex_init(&actx->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक dcp_sha_update_fx(काष्ठा ahash_request *req, पूर्णांक fini)
अणु
	काष्ठा dcp *sdcp = global_sdcp;

	काष्ठा dcp_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा dcp_async_ctx *actx = crypto_ahash_ctx(tfm);

	पूर्णांक ret;

	/*
	 * Ignore requests that have no data in them and are not
	 * the trailing requests in the stream of requests.
	 */
	अगर (!req->nbytes && !fini)
		वापस 0;

	mutex_lock(&actx->mutex);

	rctx->fini = fini;

	अगर (!actx->hot) अणु
		actx->hot = 1;
		rctx->init = 1;
	पूर्ण

	spin_lock(&sdcp->lock[actx->chan]);
	ret = crypto_enqueue_request(&sdcp->queue[actx->chan], &req->base);
	spin_unlock(&sdcp->lock[actx->chan]);

	wake_up_process(sdcp->thपढ़ो[actx->chan]);
	mutex_unlock(&actx->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक dcp_sha_update(काष्ठा ahash_request *req)
अणु
	वापस dcp_sha_update_fx(req, 0);
पूर्ण

अटल पूर्णांक dcp_sha_final(काष्ठा ahash_request *req)
अणु
	ahash_request_set_crypt(req, शून्य, req->result, 0);
	req->nbytes = 0;
	वापस dcp_sha_update_fx(req, 1);
पूर्ण

अटल पूर्णांक dcp_sha_finup(काष्ठा ahash_request *req)
अणु
	वापस dcp_sha_update_fx(req, 1);
पूर्ण

अटल पूर्णांक dcp_sha_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = dcp_sha_init(req);
	अगर (ret)
		वापस ret;

	वापस dcp_sha_finup(req);
पूर्ण

अटल पूर्णांक dcp_sha_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा dcp_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा dcp_async_ctx *actx = crypto_ahash_ctx(tfm);
	स्थिर काष्ठा dcp_export_state *export = in;

	स_रखो(rctx, 0, माप(काष्ठा dcp_sha_req_ctx));
	स_रखो(actx, 0, माप(काष्ठा dcp_async_ctx));
	स_नकल(rctx, &export->req_ctx, माप(काष्ठा dcp_sha_req_ctx));
	स_नकल(actx, &export->async_ctx, माप(काष्ठा dcp_async_ctx));

	वापस 0;
पूर्ण

अटल पूर्णांक dcp_sha_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा dcp_sha_req_ctx *rctx_state = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा dcp_async_ctx *actx_state = crypto_ahash_ctx(tfm);
	काष्ठा dcp_export_state *export = out;

	स_नकल(&export->req_ctx, rctx_state, माप(काष्ठा dcp_sha_req_ctx));
	स_नकल(&export->async_ctx, actx_state, माप(काष्ठा dcp_async_ctx));

	वापस 0;
पूर्ण

अटल पूर्णांक dcp_sha_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा dcp_sha_req_ctx));
	वापस 0;
पूर्ण

अटल व्योम dcp_sha_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
पूर्ण

/* AES 128 ECB and AES 128 CBC */
अटल काष्ठा skcipher_alg dcp_aes_algs[] = अणु
	अणु
		.base.cra_name		= "ecb(aes)",
		.base.cra_driver_name	= "ecb-aes-dcp",
		.base.cra_priority	= 400,
		.base.cra_alignmask	= 15,
		.base.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_NEED_FALLBACK,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा dcp_async_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.setkey			= mxs_dcp_aes_setkey,
		.encrypt		= mxs_dcp_aes_ecb_encrypt,
		.decrypt		= mxs_dcp_aes_ecb_decrypt,
		.init			= mxs_dcp_aes_fallback_init_tfm,
		.निकास			= mxs_dcp_aes_fallback_निकास_tfm,
	पूर्ण, अणु
		.base.cra_name		= "cbc(aes)",
		.base.cra_driver_name	= "cbc-aes-dcp",
		.base.cra_priority	= 400,
		.base.cra_alignmask	= 15,
		.base.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_NEED_FALLBACK,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा dcp_async_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.setkey			= mxs_dcp_aes_setkey,
		.encrypt		= mxs_dcp_aes_cbc_encrypt,
		.decrypt		= mxs_dcp_aes_cbc_decrypt,
		.ivsize			= AES_BLOCK_SIZE,
		.init			= mxs_dcp_aes_fallback_init_tfm,
		.निकास			= mxs_dcp_aes_fallback_निकास_tfm,
	पूर्ण,
पूर्ण;

/* SHA1 */
अटल काष्ठा ahash_alg dcp_sha1_alg = अणु
	.init	= dcp_sha_init,
	.update	= dcp_sha_update,
	.final	= dcp_sha_final,
	.finup	= dcp_sha_finup,
	.digest	= dcp_sha_digest,
	.import = dcp_sha_import,
	.export = dcp_sha_export,
	.halg	= अणु
		.digestsize	= SHA1_DIGEST_SIZE,
		.statesize	= माप(काष्ठा dcp_export_state),
		.base		= अणु
			.cra_name		= "sha1",
			.cra_driver_name	= "sha1-dcp",
			.cra_priority		= 400,
			.cra_alignmask		= 63,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA1_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा dcp_async_ctx),
			.cra_module		= THIS_MODULE,
			.cra_init		= dcp_sha_cra_init,
			.cra_निकास		= dcp_sha_cra_निकास,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* SHA256 */
अटल काष्ठा ahash_alg dcp_sha256_alg = अणु
	.init	= dcp_sha_init,
	.update	= dcp_sha_update,
	.final	= dcp_sha_final,
	.finup	= dcp_sha_finup,
	.digest	= dcp_sha_digest,
	.import = dcp_sha_import,
	.export = dcp_sha_export,
	.halg	= अणु
		.digestsize	= SHA256_DIGEST_SIZE,
		.statesize	= माप(काष्ठा dcp_export_state),
		.base		= अणु
			.cra_name		= "sha256",
			.cra_driver_name	= "sha256-dcp",
			.cra_priority		= 400,
			.cra_alignmask		= 63,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA256_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा dcp_async_ctx),
			.cra_module		= THIS_MODULE,
			.cra_init		= dcp_sha_cra_init,
			.cra_निकास		= dcp_sha_cra_निकास,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल irqवापस_t mxs_dcp_irq(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा dcp *sdcp = context;
	uपूर्णांक32_t stat;
	पूर्णांक i;

	stat = पढ़ोl(sdcp->base + MXS_DCP_STAT);
	stat &= MXS_DCP_STAT_IRQ_MASK;
	अगर (!stat)
		वापस IRQ_NONE;

	/* Clear the पूर्णांकerrupts. */
	ग_लिखोl(stat, sdcp->base + MXS_DCP_STAT_CLR);

	/* Complete the DMA requests that finished. */
	क्रम (i = 0; i < DCP_MAX_CHANS; i++)
		अगर (stat & (1 << i))
			complete(&sdcp->completion[i]);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxs_dcp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dcp *sdcp = शून्य;
	पूर्णांक i, ret;
	पूर्णांक dcp_vmi_irq, dcp_irq;

	अगर (global_sdcp) अणु
		dev_err(dev, "Only one DCP instance allowed!\n");
		वापस -ENODEV;
	पूर्ण

	dcp_vmi_irq = platक्रमm_get_irq(pdev, 0);
	अगर (dcp_vmi_irq < 0)
		वापस dcp_vmi_irq;

	dcp_irq = platक्रमm_get_irq(pdev, 1);
	अगर (dcp_irq < 0)
		वापस dcp_irq;

	sdcp = devm_kzalloc(dev, माप(*sdcp), GFP_KERNEL);
	अगर (!sdcp)
		वापस -ENOMEM;

	sdcp->dev = dev;
	sdcp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sdcp->base))
		वापस PTR_ERR(sdcp->base);


	ret = devm_request_irq(dev, dcp_vmi_irq, mxs_dcp_irq, 0,
			       "dcp-vmi-irq", sdcp);
	अगर (ret) अणु
		dev_err(dev, "Failed to claim DCP VMI IRQ!\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(dev, dcp_irq, mxs_dcp_irq, 0,
			       "dcp-irq", sdcp);
	अगर (ret) अणु
		dev_err(dev, "Failed to claim DCP IRQ!\n");
		वापस ret;
	पूर्ण

	/* Allocate coherent helper block. */
	sdcp->coh = devm_kzalloc(dev, माप(*sdcp->coh) + DCP_ALIGNMENT,
				   GFP_KERNEL);
	अगर (!sdcp->coh)
		वापस -ENOMEM;

	/* Re-align the काष्ठाure so it fits the DCP स्थिरraपूर्णांकs. */
	sdcp->coh = PTR_ALIGN(sdcp->coh, DCP_ALIGNMENT);

	/* DCP घड़ी is optional, only used on some SOCs */
	sdcp->dcp_clk = devm_clk_get(dev, "dcp");
	अगर (IS_ERR(sdcp->dcp_clk)) अणु
		अगर (sdcp->dcp_clk != ERR_PTR(-ENOENT))
			वापस PTR_ERR(sdcp->dcp_clk);
		sdcp->dcp_clk = शून्य;
	पूर्ण
	ret = clk_prepare_enable(sdcp->dcp_clk);
	अगर (ret)
		वापस ret;

	/* Restart the DCP block. */
	ret = sपंचांगp_reset_block(sdcp->base);
	अगर (ret) अणु
		dev_err(dev, "Failed reset\n");
		जाओ err_disable_unprepare_clk;
	पूर्ण

	/* Initialize control रेजिस्टर. */
	ग_लिखोl(MXS_DCP_CTRL_GATHER_RESIDUAL_WRITES |
	       MXS_DCP_CTRL_ENABLE_CONTEXT_CACHING | 0xf,
	       sdcp->base + MXS_DCP_CTRL);

	/* Enable all DCP DMA channels. */
	ग_लिखोl(MXS_DCP_CHANNELCTRL_ENABLE_CHANNEL_MASK,
	       sdcp->base + MXS_DCP_CHANNELCTRL);

	/*
	 * We करो not enable context चयनing. Give the context buffer a
	 * poपूर्णांकer to an illegal address so अगर context चयनing is
	 * inadvertantly enabled, the DCP will वापस an error instead of
	 * trashing good memory. The DCP DMA cannot access ROM, so any ROM
	 * address will करो.
	 */
	ग_लिखोl(0xffff0000, sdcp->base + MXS_DCP_CONTEXT);
	क्रम (i = 0; i < DCP_MAX_CHANS; i++)
		ग_लिखोl(0xffffffff, sdcp->base + MXS_DCP_CH_N_STAT_CLR(i));
	ग_लिखोl(0xffffffff, sdcp->base + MXS_DCP_STAT_CLR);

	global_sdcp = sdcp;

	platक्रमm_set_drvdata(pdev, sdcp);

	क्रम (i = 0; i < DCP_MAX_CHANS; i++) अणु
		spin_lock_init(&sdcp->lock[i]);
		init_completion(&sdcp->completion[i]);
		crypto_init_queue(&sdcp->queue[i], 50);
	पूर्ण

	/* Create the SHA and AES handler thपढ़ोs. */
	sdcp->thपढ़ो[DCP_CHAN_HASH_SHA] = kthपढ़ो_run(dcp_chan_thपढ़ो_sha,
						      शून्य, "mxs_dcp_chan/sha");
	अगर (IS_ERR(sdcp->thपढ़ो[DCP_CHAN_HASH_SHA])) अणु
		dev_err(dev, "Error starting SHA thread!\n");
		ret = PTR_ERR(sdcp->thपढ़ो[DCP_CHAN_HASH_SHA]);
		जाओ err_disable_unprepare_clk;
	पूर्ण

	sdcp->thपढ़ो[DCP_CHAN_CRYPTO] = kthपढ़ो_run(dcp_chan_thपढ़ो_aes,
						    शून्य, "mxs_dcp_chan/aes");
	अगर (IS_ERR(sdcp->thपढ़ो[DCP_CHAN_CRYPTO])) अणु
		dev_err(dev, "Error starting SHA thread!\n");
		ret = PTR_ERR(sdcp->thपढ़ो[DCP_CHAN_CRYPTO]);
		जाओ err_destroy_sha_thपढ़ो;
	पूर्ण

	/* Register the various crypto algorithms. */
	sdcp->caps = पढ़ोl(sdcp->base + MXS_DCP_CAPABILITY1);

	अगर (sdcp->caps & MXS_DCP_CAPABILITY1_AES128) अणु
		ret = crypto_रेजिस्टर_skciphers(dcp_aes_algs,
						ARRAY_SIZE(dcp_aes_algs));
		अगर (ret) अणु
			/* Failed to रेजिस्टर algorithm. */
			dev_err(dev, "Failed to register AES crypto!\n");
			जाओ err_destroy_aes_thपढ़ो;
		पूर्ण
	पूर्ण

	अगर (sdcp->caps & MXS_DCP_CAPABILITY1_SHA1) अणु
		ret = crypto_रेजिस्टर_ahash(&dcp_sha1_alg);
		अगर (ret) अणु
			dev_err(dev, "Failed to register %s hash!\n",
				dcp_sha1_alg.halg.base.cra_name);
			जाओ err_unरेजिस्टर_aes;
		पूर्ण
	पूर्ण

	अगर (sdcp->caps & MXS_DCP_CAPABILITY1_SHA256) अणु
		ret = crypto_रेजिस्टर_ahash(&dcp_sha256_alg);
		अगर (ret) अणु
			dev_err(dev, "Failed to register %s hash!\n",
				dcp_sha256_alg.halg.base.cra_name);
			जाओ err_unरेजिस्टर_sha1;
		पूर्ण
	पूर्ण

	वापस 0;

err_unरेजिस्टर_sha1:
	अगर (sdcp->caps & MXS_DCP_CAPABILITY1_SHA1)
		crypto_unरेजिस्टर_ahash(&dcp_sha1_alg);

err_unरेजिस्टर_aes:
	अगर (sdcp->caps & MXS_DCP_CAPABILITY1_AES128)
		crypto_unरेजिस्टर_skciphers(dcp_aes_algs, ARRAY_SIZE(dcp_aes_algs));

err_destroy_aes_thपढ़ो:
	kthपढ़ो_stop(sdcp->thपढ़ो[DCP_CHAN_CRYPTO]);

err_destroy_sha_thपढ़ो:
	kthपढ़ो_stop(sdcp->thपढ़ो[DCP_CHAN_HASH_SHA]);

err_disable_unprepare_clk:
	clk_disable_unprepare(sdcp->dcp_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_dcp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dcp *sdcp = platक्रमm_get_drvdata(pdev);

	अगर (sdcp->caps & MXS_DCP_CAPABILITY1_SHA256)
		crypto_unरेजिस्टर_ahash(&dcp_sha256_alg);

	अगर (sdcp->caps & MXS_DCP_CAPABILITY1_SHA1)
		crypto_unरेजिस्टर_ahash(&dcp_sha1_alg);

	अगर (sdcp->caps & MXS_DCP_CAPABILITY1_AES128)
		crypto_unरेजिस्टर_skciphers(dcp_aes_algs, ARRAY_SIZE(dcp_aes_algs));

	kthपढ़ो_stop(sdcp->thपढ़ो[DCP_CHAN_HASH_SHA]);
	kthपढ़ो_stop(sdcp->thपढ़ो[DCP_CHAN_CRYPTO]);

	clk_disable_unprepare(sdcp->dcp_clk);

	platक्रमm_set_drvdata(pdev, शून्य);

	global_sdcp = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxs_dcp_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-dcp", .data = शून्य, पूर्ण,
	अणु .compatible = "fsl,imx28-dcp", .data = शून्य, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, mxs_dcp_dt_ids);

अटल काष्ठा platक्रमm_driver mxs_dcp_driver = अणु
	.probe	= mxs_dcp_probe,
	.हटाओ	= mxs_dcp_हटाओ,
	.driver	= अणु
		.name		= "mxs-dcp",
		.of_match_table	= mxs_dcp_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mxs_dcp_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("Freescale MXS DCP Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mxs-dcp");
