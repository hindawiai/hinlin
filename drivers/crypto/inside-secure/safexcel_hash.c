<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Marvell
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/hmac.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha3.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/sm3.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>

#समावेश "safexcel.h"

काष्ठा safexcel_ahash_ctx अणु
	काष्ठा safexcel_context base;

	u32 alg;
	u8  key_sz;
	bool cbcmac;
	bool करो_fallback;
	bool fb_init_करोne;
	bool fb_करो_setkey;

	काष्ठा crypto_cipher *kaes;
	काष्ठा crypto_ahash *fback;
	काष्ठा crypto_shash *shpre;
	काष्ठा shash_desc *shdesc;
पूर्ण;

काष्ठा safexcel_ahash_req अणु
	bool last_req;
	bool finish;
	bool hmac;
	bool needs_inv;
	bool hmac_zlen;
	bool len_is_le;
	bool not_first;
	bool xcbcmac;

	पूर्णांक nents;
	dma_addr_t result_dma;

	u32 digest;

	u8 state_sz;    /* expected state size, only set once */
	u8 block_sz;    /* block size, only set once */
	u8 digest_sz;   /* output digest size, only set once */
	__le32 state[SHA3_512_BLOCK_SIZE /
		     माप(__le32)] __aligned(माप(__le32));

	u64 len;
	u64 processed;

	u8 cache[HASH_CACHE_SIZE] __aligned(माप(u32));
	dma_addr_t cache_dma;
	अचिन्हित पूर्णांक cache_sz;

	u8 cache_next[HASH_CACHE_SIZE] __aligned(माप(u32));
पूर्ण;

अटल अंतरभूत u64 safexcel_queued_len(काष्ठा safexcel_ahash_req *req)
अणु
	वापस req->len - req->processed;
पूर्ण

अटल व्योम safexcel_hash_token(काष्ठा safexcel_command_desc *cdesc,
				u32 input_length, u32 result_length,
				bool cbcmac)
अणु
	काष्ठा safexcel_token *token =
		(काष्ठा safexcel_token *)cdesc->control_data.token;

	token[0].opcode = EIP197_TOKEN_OPCODE_सूचीECTION;
	token[0].packet_length = input_length;
	token[0].inकाष्ठाions = EIP197_TOKEN_INS_TYPE_HASH;

	input_length &= 15;
	अगर (unlikely(cbcmac && input_length)) अणु
		token[0].stat =  0;
		token[1].opcode = EIP197_TOKEN_OPCODE_INSERT;
		token[1].packet_length = 16 - input_length;
		token[1].stat = EIP197_TOKEN_STAT_LAST_HASH;
		token[1].inकाष्ठाions = EIP197_TOKEN_INS_TYPE_HASH;
	पूर्ण अन्यथा अणु
		token[0].stat = EIP197_TOKEN_STAT_LAST_HASH;
		eip197_noop_token(&token[1]);
	पूर्ण

	token[2].opcode = EIP197_TOKEN_OPCODE_INSERT;
	token[2].stat = EIP197_TOKEN_STAT_LAST_HASH |
			EIP197_TOKEN_STAT_LAST_PACKET;
	token[2].packet_length = result_length;
	token[2].inकाष्ठाions = EIP197_TOKEN_INS_TYPE_OUTPUT |
				EIP197_TOKEN_INS_INSERT_HASH_DIGEST;

	eip197_noop_token(&token[3]);
पूर्ण

अटल व्योम safexcel_context_control(काष्ठा safexcel_ahash_ctx *ctx,
				     काष्ठा safexcel_ahash_req *req,
				     काष्ठा safexcel_command_desc *cdesc)
अणु
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	u64 count = 0;

	cdesc->control_data.control0 = ctx->alg;
	cdesc->control_data.control1 = 0;

	/*
	 * Copy the input digest अगर needed, and setup the context
	 * fields. Do this now as we need it to setup the first command
	 * descriptor.
	 */
	अगर (unlikely(req->digest == CONTEXT_CONTROL_DIGEST_XCM)) अणु
		अगर (req->xcbcmac)
			स_नकल(ctx->base.ctxr->data, &ctx->base.ipad, ctx->key_sz);
		अन्यथा
			स_नकल(ctx->base.ctxr->data, req->state, req->state_sz);

		अगर (!req->finish && req->xcbcmac)
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_DIGEST_XCM |
				CONTEXT_CONTROL_TYPE_HASH_OUT  |
				CONTEXT_CONTROL_NO_FINISH_HASH |
				CONTEXT_CONTROL_SIZE(req->state_sz /
						     माप(u32));
		अन्यथा
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_DIGEST_XCM |
				CONTEXT_CONTROL_TYPE_HASH_OUT  |
				CONTEXT_CONTROL_SIZE(req->state_sz /
						     माप(u32));
		वापस;
	पूर्ण अन्यथा अगर (!req->processed) अणु
		/* First - and possibly only - block of basic hash only */
		अगर (req->finish)
			cdesc->control_data.control0 |= req->digest |
				CONTEXT_CONTROL_TYPE_HASH_OUT |
				CONTEXT_CONTROL_RESTART_HASH  |
				/* ensure its not 0! */
				CONTEXT_CONTROL_SIZE(1);
		अन्यथा
			cdesc->control_data.control0 |= req->digest |
				CONTEXT_CONTROL_TYPE_HASH_OUT  |
				CONTEXT_CONTROL_RESTART_HASH   |
				CONTEXT_CONTROL_NO_FINISH_HASH |
				/* ensure its not 0! */
				CONTEXT_CONTROL_SIZE(1);
		वापस;
	पूर्ण

	/* Hash continuation or HMAC, setup (inner) digest from state */
	स_नकल(ctx->base.ctxr->data, req->state, req->state_sz);

	अगर (req->finish) अणु
		/* Compute digest count क्रम hash/HMAC finish operations */
		अगर ((req->digest == CONTEXT_CONTROL_DIGEST_PRECOMPUTED) ||
		    req->hmac_zlen || (req->processed != req->block_sz)) अणु
			count = req->processed / EIP197_COUNTER_BLOCK_SIZE;

			/* This is a hardware limitation, as the
			 * counter must fit पूर्णांकo an u32. This represents
			 * a fairly big amount of input data, so we
			 * shouldn't see this.
			 */
			अगर (unlikely(count & 0xffffffff00000000ULL)) अणु
				dev_warn(priv->dev,
					 "Input data is too big\n");
				वापस;
			पूर्ण
		पूर्ण

		अगर ((req->digest == CONTEXT_CONTROL_DIGEST_PRECOMPUTED) ||
		    /* Special हाल: zero length HMAC */
		    req->hmac_zlen ||
		    /* PE HW < 4.4 cannot करो HMAC जारी, fake using hash */
		    (req->processed != req->block_sz)) अणु
			/* Basic hash जारी operation, need digest + cnt */
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_SIZE((req->state_sz >> 2) + 1) |
				CONTEXT_CONTROL_TYPE_HASH_OUT |
				CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
			/* For zero-len HMAC, करोn't finalize, alपढ़ोy padded! */
			अगर (req->hmac_zlen)
				cdesc->control_data.control0 |=
					CONTEXT_CONTROL_NO_FINISH_HASH;
			cdesc->control_data.control1 |=
				CONTEXT_CONTROL_DIGEST_CNT;
			ctx->base.ctxr->data[req->state_sz >> 2] =
				cpu_to_le32(count);
			req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;

			/* Clear zero-length HMAC flag क्रम next operation! */
			req->hmac_zlen = false;
		पूर्ण अन्यथा अणु /* HMAC */
			/* Need outer digest क्रम HMAC finalization */
			स_नकल(ctx->base.ctxr->data + (req->state_sz >> 2),
			       &ctx->base.opad, req->state_sz);

			/* Single pass HMAC - no digest count */
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_SIZE(req->state_sz >> 1) |
				CONTEXT_CONTROL_TYPE_HASH_OUT |
				CONTEXT_CONTROL_DIGEST_HMAC;
		पूर्ण
	पूर्ण अन्यथा अणु /* Hash continuation, करो not finish yet */
		cdesc->control_data.control0 |=
			CONTEXT_CONTROL_SIZE(req->state_sz >> 2) |
			CONTEXT_CONTROL_DIGEST_PRECOMPUTED |
			CONTEXT_CONTROL_TYPE_HASH_OUT |
			CONTEXT_CONTROL_NO_FINISH_HASH;
	पूर्ण
पूर्ण

अटल पूर्णांक safexcel_ahash_enqueue(काष्ठा ahash_request *areq);

अटल पूर्णांक safexcel_handle_req_result(काष्ठा safexcel_crypto_priv *priv,
				      पूर्णांक ring,
				      काष्ठा crypto_async_request *async,
				      bool *should_complete, पूर्णांक *ret)
अणु
	काष्ठा safexcel_result_desc *rdesc;
	काष्ठा ahash_request *areq = ahash_request_cast(async);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_req *sreq = ahash_request_ctx(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(ahash);
	u64 cache_len;

	*ret = 0;

	rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
	अगर (IS_ERR(rdesc)) अणु
		dev_err(priv->dev,
			"hash: result: could not retrieve the result descriptor\n");
		*ret = PTR_ERR(rdesc);
	पूर्ण अन्यथा अणु
		*ret = safexcel_rdesc_check_errors(priv, rdesc);
	पूर्ण

	safexcel_complete(priv, ring);

	अगर (sreq->nents) अणु
		dma_unmap_sg(priv->dev, areq->src, sreq->nents, DMA_TO_DEVICE);
		sreq->nents = 0;
	पूर्ण

	अगर (sreq->result_dma) अणु
		dma_unmap_single(priv->dev, sreq->result_dma, sreq->digest_sz,
				 DMA_FROM_DEVICE);
		sreq->result_dma = 0;
	पूर्ण

	अगर (sreq->cache_dma) अणु
		dma_unmap_single(priv->dev, sreq->cache_dma, sreq->cache_sz,
				 DMA_TO_DEVICE);
		sreq->cache_dma = 0;
		sreq->cache_sz = 0;
	पूर्ण

	अगर (sreq->finish) अणु
		अगर (sreq->hmac &&
		    (sreq->digest != CONTEXT_CONTROL_DIGEST_HMAC)) अणु
			/* Faking HMAC using hash - need to करो outer hash */
			स_नकल(sreq->cache, sreq->state,
			       crypto_ahash_digestsize(ahash));

			स_नकल(sreq->state, &ctx->base.opad, sreq->digest_sz);

			sreq->len = sreq->block_sz +
				    crypto_ahash_digestsize(ahash);
			sreq->processed = sreq->block_sz;
			sreq->hmac = 0;

			अगर (priv->flags & EIP197_TRC_CACHE)
				ctx->base.needs_inv = true;
			areq->nbytes = 0;
			safexcel_ahash_enqueue(areq);

			*should_complete = false; /* Not करोne yet */
			वापस 1;
		पूर्ण

		अगर (unlikely(sreq->digest == CONTEXT_CONTROL_DIGEST_XCM &&
			     ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_CRC32)) अणु
			/* Unकरो final XOR with 0xffffffff ...*/
			*(__le32 *)areq->result = ~sreq->state[0];
		पूर्ण अन्यथा अणु
			स_नकल(areq->result, sreq->state,
			       crypto_ahash_digestsize(ahash));
		पूर्ण
	पूर्ण

	cache_len = safexcel_queued_len(sreq);
	अगर (cache_len)
		स_नकल(sreq->cache, sreq->cache_next, cache_len);

	*should_complete = true;

	वापस 1;
पूर्ण

अटल पूर्णांक safexcel_ahash_send_req(काष्ठा crypto_async_request *async, पूर्णांक ring,
				   पूर्णांक *commands, पूर्णांक *results)
अणु
	काष्ठा ahash_request *areq = ahash_request_cast(async);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	काष्ठा safexcel_command_desc *cdesc, *first_cdesc = शून्य;
	काष्ठा safexcel_result_desc *rdesc;
	काष्ठा scatterlist *sg;
	काष्ठा safexcel_token *dmmy;
	पूर्णांक i, extra = 0, n_cdesc = 0, ret = 0, cache_len, skip = 0;
	u64 queued, len;

	queued = safexcel_queued_len(req);
	अगर (queued <= HASH_CACHE_SIZE)
		cache_len = queued;
	अन्यथा
		cache_len = queued - areq->nbytes;

	अगर (!req->finish && !req->last_req) अणु
		/* If this is not the last request and the queued data करोes not
		 * fit पूर्णांकo full cache blocks, cache it क्रम the next send call.
		 */
		extra = queued & (HASH_CACHE_SIZE - 1);

		/* If this is not the last request and the queued data
		 * is a multiple of a block, cache the last one क्रम now.
		 */
		अगर (!extra)
			extra = HASH_CACHE_SIZE;

		sg_pcopy_to_buffer(areq->src, sg_nents(areq->src),
				   req->cache_next, extra,
				   areq->nbytes - extra);

		queued -= extra;

		अगर (!queued) अणु
			*commands = 0;
			*results = 0;
			वापस 0;
		पूर्ण

		extra = 0;
	पूर्ण

	अगर (unlikely(req->xcbcmac && req->processed > AES_BLOCK_SIZE)) अणु
		अगर (unlikely(cache_len < AES_BLOCK_SIZE)) अणु
			/*
			 * Cache contains less than 1 full block, complete.
			 */
			extra = AES_BLOCK_SIZE - cache_len;
			अगर (queued > cache_len) अणु
				/* More data follows: borrow bytes */
				u64 पंचांगp = queued - cache_len;

				skip = min_t(u64, पंचांगp, extra);
				sg_pcopy_to_buffer(areq->src,
					sg_nents(areq->src),
					req->cache + cache_len,
					skip, 0);
			पूर्ण
			extra -= skip;
			स_रखो(req->cache + cache_len + skip, 0, extra);
			अगर (!ctx->cbcmac && extra) अणु
				// 10- padding क्रम XCBCMAC & CMAC
				req->cache[cache_len + skip] = 0x80;
				// HW will use K2 iso K3 - compensate!
				क्रम (i = 0; i < AES_BLOCK_SIZE / 4; i++) अणु
					u32 *cache = (व्योम *)req->cache;
					u32 *ipad = ctx->base.ipad.word;
					u32 x;

					x = ipad[i] ^ ipad[i + 4];
					cache[i] ^= swab(x);
				पूर्ण
			पूर्ण
			cache_len = AES_BLOCK_SIZE;
			queued = queued + extra;
		पूर्ण

		/* XCBC जारी: XOR previous result पूर्णांकo 1st word */
		crypto_xor(req->cache, (स्थिर u8 *)req->state, AES_BLOCK_SIZE);
	पूर्ण

	len = queued;
	/* Add a command descriptor क्रम the cached data, अगर any */
	अगर (cache_len) अणु
		req->cache_dma = dma_map_single(priv->dev, req->cache,
						cache_len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(priv->dev, req->cache_dma))
			वापस -EINVAL;

		req->cache_sz = cache_len;
		first_cdesc = safexcel_add_cdesc(priv, ring, 1,
						 (cache_len == len),
						 req->cache_dma, cache_len,
						 len, ctx->base.ctxr_dma,
						 &dmmy);
		अगर (IS_ERR(first_cdesc)) अणु
			ret = PTR_ERR(first_cdesc);
			जाओ unmap_cache;
		पूर्ण
		n_cdesc++;

		queued -= cache_len;
		अगर (!queued)
			जाओ send_command;
	पूर्ण

	/* Now handle the current ahash request buffer(s) */
	req->nents = dma_map_sg(priv->dev, areq->src,
				sg_nents_क्रम_len(areq->src,
						 areq->nbytes),
				DMA_TO_DEVICE);
	अगर (!req->nents) अणु
		ret = -ENOMEM;
		जाओ cdesc_rollback;
	पूर्ण

	क्रम_each_sg(areq->src, sg, req->nents, i) अणु
		पूर्णांक sglen = sg_dma_len(sg);

		अगर (unlikely(sglen <= skip)) अणु
			skip -= sglen;
			जारी;
		पूर्ण

		/* Do not overflow the request */
		अगर ((queued + skip) <= sglen)
			sglen = queued;
		अन्यथा
			sglen -= skip;

		cdesc = safexcel_add_cdesc(priv, ring, !n_cdesc,
					   !(queued - sglen),
					   sg_dma_address(sg) + skip, sglen,
					   len, ctx->base.ctxr_dma, &dmmy);
		अगर (IS_ERR(cdesc)) अणु
			ret = PTR_ERR(cdesc);
			जाओ unmap_sg;
		पूर्ण

		अगर (!n_cdesc)
			first_cdesc = cdesc;
		n_cdesc++;

		queued -= sglen;
		अगर (!queued)
			अवरोध;
		skip = 0;
	पूर्ण

send_command:
	/* Setup the context options */
	safexcel_context_control(ctx, req, first_cdesc);

	/* Add the token */
	safexcel_hash_token(first_cdesc, len, req->digest_sz, ctx->cbcmac);

	req->result_dma = dma_map_single(priv->dev, req->state, req->digest_sz,
					 DMA_FROM_DEVICE);
	अगर (dma_mapping_error(priv->dev, req->result_dma)) अणु
		ret = -EINVAL;
		जाओ unmap_sg;
	पूर्ण

	/* Add a result descriptor */
	rdesc = safexcel_add_rdesc(priv, ring, 1, 1, req->result_dma,
				   req->digest_sz);
	अगर (IS_ERR(rdesc)) अणु
		ret = PTR_ERR(rdesc);
		जाओ unmap_result;
	पूर्ण

	safexcel_rdr_req_set(priv, ring, rdesc, &areq->base);

	req->processed += len - extra;

	*commands = n_cdesc;
	*results = 1;
	वापस 0;

unmap_result:
	dma_unmap_single(priv->dev, req->result_dma, req->digest_sz,
			 DMA_FROM_DEVICE);
unmap_sg:
	अगर (req->nents) अणु
		dma_unmap_sg(priv->dev, areq->src, req->nents, DMA_TO_DEVICE);
		req->nents = 0;
	पूर्ण
cdesc_rollback:
	क्रम (i = 0; i < n_cdesc; i++)
		safexcel_ring_rollback_wptr(priv, &priv->ring[ring].cdr);
unmap_cache:
	अगर (req->cache_dma) अणु
		dma_unmap_single(priv->dev, req->cache_dma, req->cache_sz,
				 DMA_TO_DEVICE);
		req->cache_dma = 0;
		req->cache_sz = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_handle_inv_result(काष्ठा safexcel_crypto_priv *priv,
				      पूर्णांक ring,
				      काष्ठा crypto_async_request *async,
				      bool *should_complete, पूर्णांक *ret)
अणु
	काष्ठा safexcel_result_desc *rdesc;
	काष्ठा ahash_request *areq = ahash_request_cast(async);
	काष्ठा crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(ahash);
	पूर्णांक enq_ret;

	*ret = 0;

	rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
	अगर (IS_ERR(rdesc)) अणु
		dev_err(priv->dev,
			"hash: invalidate: could not retrieve the result descriptor\n");
		*ret = PTR_ERR(rdesc);
	पूर्ण अन्यथा अणु
		*ret = safexcel_rdesc_check_errors(priv, rdesc);
	पूर्ण

	safexcel_complete(priv, ring);

	अगर (ctx->base.निकास_inv) अणु
		dma_pool_मुक्त(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);

		*should_complete = true;
		वापस 1;
	पूर्ण

	ring = safexcel_select_ring(priv);
	ctx->base.ring = ring;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	enq_ret = crypto_enqueue_request(&priv->ring[ring].queue, async);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	अगर (enq_ret != -EINPROGRESS)
		*ret = enq_ret;

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	*should_complete = false;

	वापस 1;
पूर्ण

अटल पूर्णांक safexcel_handle_result(काष्ठा safexcel_crypto_priv *priv, पूर्णांक ring,
				  काष्ठा crypto_async_request *async,
				  bool *should_complete, पूर्णांक *ret)
अणु
	काष्ठा ahash_request *areq = ahash_request_cast(async);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	पूर्णांक err;

	BUG_ON(!(priv->flags & EIP197_TRC_CACHE) && req->needs_inv);

	अगर (req->needs_inv) अणु
		req->needs_inv = false;
		err = safexcel_handle_inv_result(priv, ring, async,
						 should_complete, ret);
	पूर्ण अन्यथा अणु
		err = safexcel_handle_req_result(priv, ring, async,
						 should_complete, ret);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक safexcel_ahash_send_inv(काष्ठा crypto_async_request *async,
				   पूर्णांक ring, पूर्णांक *commands, पूर्णांक *results)
अणु
	काष्ठा ahash_request *areq = ahash_request_cast(async);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	पूर्णांक ret;

	ret = safexcel_invalidate_cache(async, ctx->base.priv,
					ctx->base.ctxr_dma, ring);
	अगर (unlikely(ret))
		वापस ret;

	*commands = 1;
	*results = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_ahash_send(काष्ठा crypto_async_request *async,
			       पूर्णांक ring, पूर्णांक *commands, पूर्णांक *results)
अणु
	काष्ठा ahash_request *areq = ahash_request_cast(async);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	पूर्णांक ret;

	अगर (req->needs_inv)
		ret = safexcel_ahash_send_inv(async, ring, commands, results);
	अन्यथा
		ret = safexcel_ahash_send_req(async, ring, commands, results);

	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_ahash_निकास_inv(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	EIP197_REQUEST_ON_STACK(req, ahash, EIP197_AHASH_REQ_SIZE);
	काष्ठा safexcel_ahash_req *rctx = ahash_request_ctx(req);
	काष्ठा safexcel_inv_result result = अणुपूर्ण;
	पूर्णांक ring = ctx->base.ring;

	स_रखो(req, 0, EIP197_AHASH_REQ_SIZE);

	/* create invalidation request */
	init_completion(&result.completion);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   safexcel_inv_complete, &result);

	ahash_request_set_tfm(req, __crypto_ahash_cast(tfm));
	ctx = crypto_tfm_ctx(req->base.tfm);
	ctx->base.निकास_inv = true;
	rctx->needs_inv = true;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	crypto_enqueue_request(&priv->ring[ring].queue, &req->base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	रुको_क्रम_completion(&result.completion);

	अगर (result.error) अणु
		dev_warn(priv->dev, "hash: completion error (%d)\n",
			 result.error);
		वापस result.error;
	पूर्ण

	वापस 0;
पूर्ण

/* safexcel_ahash_cache: cache data until at least one request can be sent to
 * the engine, aka. when there is at least 1 block size in the pipe.
 */
अटल पूर्णांक safexcel_ahash_cache(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	u64 cache_len;

	/* cache_len: everything accepted by the driver but not sent yet,
	 * tot sz handled by update() - last req sz - tot sz handled by send()
	 */
	cache_len = safexcel_queued_len(req);

	/*
	 * In हाल there isn't enough bytes to proceed (less than a
	 * block size), cache the data until we have enough.
	 */
	अगर (cache_len + areq->nbytes <= HASH_CACHE_SIZE) अणु
		sg_pcopy_to_buffer(areq->src, sg_nents(areq->src),
				   req->cache + cache_len,
				   areq->nbytes, 0);
		वापस 0;
	पूर्ण

	/* We couldn't cache all the data */
	वापस -E2BIG;
पूर्ण

अटल पूर्णांक safexcel_ahash_enqueue(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret, ring;

	req->needs_inv = false;

	अगर (ctx->base.ctxr) अणु
		अगर (priv->flags & EIP197_TRC_CACHE && !ctx->base.needs_inv &&
		     /* invalidate क्रम *any* non-XCBC continuation */
		   ((req->not_first && !req->xcbcmac) ||
		     /* invalidate अगर (i)digest changed */
		     स_भेद(ctx->base.ctxr->data, req->state, req->state_sz) ||
		     /* invalidate क्रम HMAC finish with odigest changed */
		     (req->finish && req->hmac &&
		      स_भेद(ctx->base.ctxr->data + (req->state_sz>>2),
			     &ctx->base.opad, req->state_sz))))
			/*
			 * We're still setting needs_inv here, even though it is
			 * cleared right away, because the needs_inv flag can be
			 * set in other functions and we want to keep the same
			 * logic.
			 */
			ctx->base.needs_inv = true;

		अगर (ctx->base.needs_inv) अणु
			ctx->base.needs_inv = false;
			req->needs_inv = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctx->base.ring = safexcel_select_ring(priv);
		ctx->base.ctxr = dma_pool_zalloc(priv->context_pool,
						 EIP197_GFP_FLAGS(areq->base),
						 &ctx->base.ctxr_dma);
		अगर (!ctx->base.ctxr)
			वापस -ENOMEM;
	पूर्ण
	req->not_first = true;

	ring = ctx->base.ring;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	ret = crypto_enqueue_request(&priv->ring[ring].queue, &areq->base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_ahash_update(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	पूर्णांक ret;

	/* If the request is 0 length, करो nothing */
	अगर (!areq->nbytes)
		वापस 0;

	/* Add request to the cache अगर it fits */
	ret = safexcel_ahash_cache(areq);

	/* Update total request length */
	req->len += areq->nbytes;

	/* If not all data could fit पूर्णांकo the cache, go process the excess.
	 * Also go process immediately क्रम an HMAC IV precompute, which
	 * will never be finished at all, but needs to be processed anyway.
	 */
	अगर ((ret && !req->finish) || req->last_req)
		वापस safexcel_ahash_enqueue(areq);

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_ahash_final(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));

	req->finish = true;

	अगर (unlikely(!req->len && !areq->nbytes)) अणु
		/*
		 * If we have an overall 0 length *hash* request:
		 * The HW cannot करो 0 length hash, so we provide the correct
		 * result directly here.
		 */
		अगर (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_MD5)
			स_नकल(areq->result, md5_zero_message_hash,
			       MD5_DIGEST_SIZE);
		अन्यथा अगर (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA1)
			स_नकल(areq->result, sha1_zero_message_hash,
			       SHA1_DIGEST_SIZE);
		अन्यथा अगर (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA224)
			स_नकल(areq->result, sha224_zero_message_hash,
			       SHA224_DIGEST_SIZE);
		अन्यथा अगर (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA256)
			स_नकल(areq->result, sha256_zero_message_hash,
			       SHA256_DIGEST_SIZE);
		अन्यथा अगर (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA384)
			स_नकल(areq->result, sha384_zero_message_hash,
			       SHA384_DIGEST_SIZE);
		अन्यथा अगर (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA512)
			स_नकल(areq->result, sha512_zero_message_hash,
			       SHA512_DIGEST_SIZE);
		अन्यथा अगर (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SM3) अणु
			स_नकल(areq->result,
			       EIP197_SM3_ZEROM_HASH, SM3_DIGEST_SIZE);
		पूर्ण

		वापस 0;
	पूर्ण अन्यथा अगर (unlikely(req->digest == CONTEXT_CONTROL_DIGEST_XCM &&
			    ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_MD5 &&
			    req->len == माप(u32) && !areq->nbytes)) अणु
		/* Zero length CRC32 */
		स_नकल(areq->result, &ctx->base.ipad, माप(u32));
		वापस 0;
	पूर्ण अन्यथा अगर (unlikely(ctx->cbcmac && req->len == AES_BLOCK_SIZE &&
			    !areq->nbytes)) अणु
		/* Zero length CBC MAC */
		स_रखो(areq->result, 0, AES_BLOCK_SIZE);
		वापस 0;
	पूर्ण अन्यथा अगर (unlikely(req->xcbcmac && req->len == AES_BLOCK_SIZE &&
			    !areq->nbytes)) अणु
		/* Zero length (X)CBC/CMAC */
		पूर्णांक i;

		क्रम (i = 0; i < AES_BLOCK_SIZE / माप(u32); i++) अणु
			u32 *result = (व्योम *)areq->result;

			/* K3 */
			result[i] = swab(ctx->base.ipad.word[i + 4]);
		पूर्ण
		areq->result[0] ^= 0x80;			// 10- padding
		crypto_cipher_encrypt_one(ctx->kaes, areq->result, areq->result);
		वापस 0;
	पूर्ण अन्यथा अगर (unlikely(req->hmac &&
			    (req->len == req->block_sz) &&
			    !areq->nbytes)) अणु
		/*
		 * If we have an overall 0 length *HMAC* request:
		 * For HMAC, we need to finalize the inner digest
		 * and then perक्रमm the outer hash.
		 */

		/* generate pad block in the cache */
		/* start with a hash block of all zeroes */
		स_रखो(req->cache, 0, req->block_sz);
		/* set the first byte to 0x80 to 'append a 1 bit' */
		req->cache[0] = 0x80;
		/* add the length in bits in the last 2 bytes */
		अगर (req->len_is_le) अणु
			/* Little endian length word (e.g. MD5) */
			req->cache[req->block_sz-8] = (req->block_sz << 3) &
						      255;
			req->cache[req->block_sz-7] = (req->block_sz >> 5);
		पूर्ण अन्यथा अणु
			/* Big endian length word (e.g. any SHA) */
			req->cache[req->block_sz-2] = (req->block_sz >> 5);
			req->cache[req->block_sz-1] = (req->block_sz << 3) &
						      255;
		पूर्ण

		req->len += req->block_sz; /* plus 1 hash block */

		/* Set special zero-length HMAC flag */
		req->hmac_zlen = true;

		/* Finalize HMAC */
		req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	पूर्ण अन्यथा अगर (req->hmac) अणु
		/* Finalize HMAC */
		req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	पूर्ण

	वापस safexcel_ahash_enqueue(areq);
पूर्ण

अटल पूर्णांक safexcel_ahash_finup(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	req->finish = true;

	safexcel_ahash_update(areq);
	वापस safexcel_ahash_final(areq);
पूर्ण

अटल पूर्णांक safexcel_ahash_export(काष्ठा ahash_request *areq, व्योम *out)
अणु
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	काष्ठा safexcel_ahash_export_state *export = out;

	export->len = req->len;
	export->processed = req->processed;

	export->digest = req->digest;

	स_नकल(export->state, req->state, req->state_sz);
	स_नकल(export->cache, req->cache, HASH_CACHE_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_ahash_import(काष्ठा ahash_request *areq, स्थिर व्योम *in)
अणु
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);
	स्थिर काष्ठा safexcel_ahash_export_state *export = in;
	पूर्णांक ret;

	ret = crypto_ahash_init(areq);
	अगर (ret)
		वापस ret;

	req->len = export->len;
	req->processed = export->processed;

	req->digest = export->digest;

	स_नकल(req->cache, export->cache, HASH_CACHE_SIZE);
	स_नकल(req->state, export->state, req->state_sz);

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_ahash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_alg_ढाँचा *पंचांगpl =
		container_of(__crypto_ahash_alg(tfm->__crt_alg),
			     काष्ठा safexcel_alg_ढाँचा, alg.ahash);

	ctx->base.priv = पंचांगpl->priv;
	ctx->base.send = safexcel_ahash_send;
	ctx->base.handle_result = safexcel_handle_result;
	ctx->fb_करो_setkey = false;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा safexcel_ahash_req));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha1_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA1;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA1_DIGEST_SIZE;
	req->digest_sz = SHA1_DIGEST_SIZE;
	req->block_sz = SHA1_BLOCK_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha1_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_sha1_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

अटल व्योम safexcel_ahash_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा safexcel_crypto_priv *priv = ctx->base.priv;
	पूर्णांक ret;

	/* context not allocated, skip invalidation */
	अगर (!ctx->base.ctxr)
		वापस;

	अगर (priv->flags & EIP197_TRC_CACHE) अणु
		ret = safexcel_ahash_निकास_inv(tfm);
		अगर (ret)
			dev_warn(priv->dev, "hash: invalidation error %d\n", ret);
	पूर्ण अन्यथा अणु
		dma_pool_मुक्त(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);
	पूर्ण
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha1 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA1,
	.alg.ahash = अणु
		.init = safexcel_sha1_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sha1_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "safexcel-sha1",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha1_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from ipad precompute */
	स_नकल(req->state, &ctx->base.ipad, SHA1_DIGEST_SIZE);
	/* Alपढ़ोy processed the key^ipad part now! */
	req->len	= SHA1_BLOCK_SIZE;
	req->processed	= SHA1_BLOCK_SIZE;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA1;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA1_DIGEST_SIZE;
	req->digest_sz = SHA1_DIGEST_SIZE;
	req->block_sz = SHA1_BLOCK_SIZE;
	req->hmac = true;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha1_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_hmac_sha1_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_ahash_result अणु
	काष्ठा completion completion;
	पूर्णांक error;
पूर्ण;

अटल व्योम safexcel_ahash_complete(काष्ठा crypto_async_request *req, पूर्णांक error)
अणु
	काष्ठा safexcel_ahash_result *result = req->data;

	अगर (error == -EINPROGRESS)
		वापस;

	result->error = error;
	complete(&result->completion);
पूर्ण

अटल पूर्णांक safexcel_hmac_init_pad(काष्ठा ahash_request *areq,
				  अचिन्हित पूर्णांक blocksize, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keylen, u8 *ipad, u8 *opad)
अणु
	काष्ठा safexcel_ahash_result result;
	काष्ठा scatterlist sg;
	पूर्णांक ret, i;
	u8 *keydup;

	अगर (keylen <= blocksize) अणु
		स_नकल(ipad, key, keylen);
	पूर्ण अन्यथा अणु
		keydup = kmemdup(key, keylen, GFP_KERNEL);
		अगर (!keydup)
			वापस -ENOMEM;

		ahash_request_set_callback(areq, CRYPTO_TFM_REQ_MAY_BACKLOG,
					   safexcel_ahash_complete, &result);
		sg_init_one(&sg, keydup, keylen);
		ahash_request_set_crypt(areq, &sg, ipad, keylen);
		init_completion(&result.completion);

		ret = crypto_ahash_digest(areq);
		अगर (ret == -EINPROGRESS || ret == -EBUSY) अणु
			रुको_क्रम_completion_पूर्णांकerruptible(&result.completion);
			ret = result.error;
		पूर्ण

		/* Aव्योम leaking */
		kमुक्त_sensitive(keydup);

		अगर (ret)
			वापस ret;

		keylen = crypto_ahash_digestsize(crypto_ahash_reqtfm(areq));
	पूर्ण

	स_रखो(ipad + keylen, 0, blocksize - keylen);
	स_नकल(opad, ipad, blocksize);

	क्रम (i = 0; i < blocksize; i++) अणु
		ipad[i] ^= HMAC_IPAD_VALUE;
		opad[i] ^= HMAC_OPAD_VALUE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_init_iv(काष्ठा ahash_request *areq,
				 अचिन्हित पूर्णांक blocksize, u8 *pad, व्योम *state)
अणु
	काष्ठा safexcel_ahash_result result;
	काष्ठा safexcel_ahash_req *req;
	काष्ठा scatterlist sg;
	पूर्णांक ret;

	ahash_request_set_callback(areq, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   safexcel_ahash_complete, &result);
	sg_init_one(&sg, pad, blocksize);
	ahash_request_set_crypt(areq, &sg, pad, blocksize);
	init_completion(&result.completion);

	ret = crypto_ahash_init(areq);
	अगर (ret)
		वापस ret;

	req = ahash_request_ctx(areq);
	req->hmac = true;
	req->last_req = true;

	ret = crypto_ahash_update(areq);
	अगर (ret && ret != -EINPROGRESS && ret != -EBUSY)
		वापस ret;

	रुको_क्रम_completion_पूर्णांकerruptible(&result.completion);
	अगर (result.error)
		वापस result.error;

	वापस crypto_ahash_export(areq, state);
पूर्ण

अटल पूर्णांक __safexcel_hmac_setkey(स्थिर अक्षर *alg, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keylen,
				  व्योम *istate, व्योम *ostate)
अणु
	काष्ठा ahash_request *areq;
	काष्ठा crypto_ahash *tfm;
	अचिन्हित पूर्णांक blocksize;
	u8 *ipad, *opad;
	पूर्णांक ret;

	tfm = crypto_alloc_ahash(alg, 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	areq = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!areq) अणु
		ret = -ENOMEM;
		जाओ मुक्त_ahash;
	पूर्ण

	crypto_ahash_clear_flags(tfm, ~0);
	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	ipad = kसुस्मृति(2, blocksize, GFP_KERNEL);
	अगर (!ipad) अणु
		ret = -ENOMEM;
		जाओ मुक्त_request;
	पूर्ण

	opad = ipad + blocksize;

	ret = safexcel_hmac_init_pad(areq, blocksize, key, keylen, ipad, opad);
	अगर (ret)
		जाओ मुक्त_ipad;

	ret = safexcel_hmac_init_iv(areq, blocksize, ipad, istate);
	अगर (ret)
		जाओ मुक्त_ipad;

	ret = safexcel_hmac_init_iv(areq, blocksize, opad, ostate);

मुक्त_ipad:
	kमुक्त(ipad);
मुक्त_request:
	ahash_request_मुक्त(areq);
मुक्त_ahash:
	crypto_मुक्त_ahash(tfm);

	वापस ret;
पूर्ण

पूर्णांक safexcel_hmac_setkey(काष्ठा safexcel_context *base, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen, स्थिर अक्षर *alg,
			 अचिन्हित पूर्णांक state_sz)
अणु
	काष्ठा safexcel_crypto_priv *priv = base->priv;
	काष्ठा safexcel_ahash_export_state istate, ostate;
	पूर्णांक ret;

	ret = __safexcel_hmac_setkey(alg, key, keylen, &istate, &ostate);
	अगर (ret)
		वापस ret;

	अगर (priv->flags & EIP197_TRC_CACHE && base->ctxr &&
	    (स_भेद(&base->ipad, istate.state, state_sz) ||
	     स_भेद(&base->opad, ostate.state, state_sz)))
		base->needs_inv = true;

	स_नकल(&base->ipad, &istate.state, state_sz);
	स_नकल(&base->opad, &ostate.state, state_sz);

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_alg_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				    अचिन्हित पूर्णांक keylen, स्थिर अक्षर *alg,
				    अचिन्हित पूर्णांक state_sz)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);

	वापस safexcel_hmac_setkey(&ctx->base, key, keylen, alg, state_sz);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha1_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				     अचिन्हित पूर्णांक keylen)
अणु
	वापस safexcel_hmac_alg_setkey(tfm, key, keylen, "safexcel-sha1",
					SHA1_DIGEST_SIZE);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha1 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA1,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha1_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_hmac_sha1_digest,
		.setkey = safexcel_hmac_sha1_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha1)",
				.cra_driver_name = "safexcel-hmac-sha1",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sha256_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA256;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA256_DIGEST_SIZE;
	req->digest_sz = SHA256_DIGEST_SIZE;
	req->block_sz = SHA256_BLOCK_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha256_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_sha256_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha256 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA2_256,
	.alg.ahash = अणु
		.init = safexcel_sha256_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sha256_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA256_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha256",
				.cra_driver_name = "safexcel-sha256",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sha224_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA224;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA256_DIGEST_SIZE;
	req->digest_sz = SHA256_DIGEST_SIZE;
	req->block_sz = SHA256_BLOCK_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha224_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_sha224_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha224 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA2_256,
	.alg.ahash = अणु
		.init = safexcel_sha224_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sha224_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA224_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha224",
				.cra_driver_name = "safexcel-sha224",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha224_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				       अचिन्हित पूर्णांक keylen)
अणु
	वापस safexcel_hmac_alg_setkey(tfm, key, keylen, "safexcel-sha224",
					SHA256_DIGEST_SIZE);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha224_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from ipad precompute */
	स_नकल(req->state, &ctx->base.ipad, SHA256_DIGEST_SIZE);
	/* Alपढ़ोy processed the key^ipad part now! */
	req->len	= SHA256_BLOCK_SIZE;
	req->processed	= SHA256_BLOCK_SIZE;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA224;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA256_DIGEST_SIZE;
	req->digest_sz = SHA256_DIGEST_SIZE;
	req->block_sz = SHA256_BLOCK_SIZE;
	req->hmac = true;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha224_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_hmac_sha224_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha224 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA2_256,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha224_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_hmac_sha224_digest,
		.setkey = safexcel_hmac_sha224_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA224_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha224)",
				.cra_driver_name = "safexcel-hmac-sha224",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha256_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				     अचिन्हित पूर्णांक keylen)
अणु
	वापस safexcel_hmac_alg_setkey(tfm, key, keylen, "safexcel-sha256",
					SHA256_DIGEST_SIZE);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha256_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from ipad precompute */
	स_नकल(req->state, &ctx->base.ipad, SHA256_DIGEST_SIZE);
	/* Alपढ़ोy processed the key^ipad part now! */
	req->len	= SHA256_BLOCK_SIZE;
	req->processed	= SHA256_BLOCK_SIZE;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA256;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA256_DIGEST_SIZE;
	req->digest_sz = SHA256_DIGEST_SIZE;
	req->block_sz = SHA256_BLOCK_SIZE;
	req->hmac = true;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha256_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_hmac_sha256_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha256 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA2_256,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha256_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_hmac_sha256_digest,
		.setkey = safexcel_hmac_sha256_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA256_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha256)",
				.cra_driver_name = "safexcel-hmac-sha256",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sha512_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA512;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA512_DIGEST_SIZE;
	req->digest_sz = SHA512_DIGEST_SIZE;
	req->block_sz = SHA512_BLOCK_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha512_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_sha512_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha512 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA2_512,
	.alg.ahash = अणु
		.init = safexcel_sha512_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sha512_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA512_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha512",
				.cra_driver_name = "safexcel-sha512",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA512_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sha384_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA384;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA512_DIGEST_SIZE;
	req->digest_sz = SHA512_DIGEST_SIZE;
	req->block_sz = SHA512_BLOCK_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha384_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_sha384_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha384 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA2_512,
	.alg.ahash = अणु
		.init = safexcel_sha384_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sha384_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA384_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha384",
				.cra_driver_name = "safexcel-sha384",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA384_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha512_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				       अचिन्हित पूर्णांक keylen)
अणु
	वापस safexcel_hmac_alg_setkey(tfm, key, keylen, "safexcel-sha512",
					SHA512_DIGEST_SIZE);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha512_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from ipad precompute */
	स_नकल(req->state, &ctx->base.ipad, SHA512_DIGEST_SIZE);
	/* Alपढ़ोy processed the key^ipad part now! */
	req->len	= SHA512_BLOCK_SIZE;
	req->processed	= SHA512_BLOCK_SIZE;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA512;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA512_DIGEST_SIZE;
	req->digest_sz = SHA512_DIGEST_SIZE;
	req->block_sz = SHA512_BLOCK_SIZE;
	req->hmac = true;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha512_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_hmac_sha512_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha512 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA2_512,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha512_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_hmac_sha512_digest,
		.setkey = safexcel_hmac_sha512_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA512_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha512)",
				.cra_driver_name = "safexcel-hmac-sha512",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA512_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha384_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				       अचिन्हित पूर्णांक keylen)
अणु
	वापस safexcel_hmac_alg_setkey(tfm, key, keylen, "safexcel-sha384",
					SHA512_DIGEST_SIZE);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha384_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from ipad precompute */
	स_नकल(req->state, &ctx->base.ipad, SHA512_DIGEST_SIZE);
	/* Alपढ़ोy processed the key^ipad part now! */
	req->len	= SHA512_BLOCK_SIZE;
	req->processed	= SHA512_BLOCK_SIZE;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA384;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA512_DIGEST_SIZE;
	req->digest_sz = SHA512_DIGEST_SIZE;
	req->block_sz = SHA512_BLOCK_SIZE;
	req->hmac = true;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha384_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_hmac_sha384_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha384 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA2_512,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha384_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_hmac_sha384_digest,
		.setkey = safexcel_hmac_sha384_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SHA384_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha384)",
				.cra_driver_name = "safexcel-hmac-sha384",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA384_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_md5_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_MD5;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = MD5_DIGEST_SIZE;
	req->digest_sz = MD5_DIGEST_SIZE;
	req->block_sz = MD5_HMAC_BLOCK_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_md5_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_md5_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_md5 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_MD5,
	.alg.ahash = अणु
		.init = safexcel_md5_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_md5_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "md5",
				.cra_driver_name = "safexcel-md5",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_md5_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from ipad precompute */
	स_नकल(req->state, &ctx->base.ipad, MD5_DIGEST_SIZE);
	/* Alपढ़ोy processed the key^ipad part now! */
	req->len	= MD5_HMAC_BLOCK_SIZE;
	req->processed	= MD5_HMAC_BLOCK_SIZE;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_MD5;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = MD5_DIGEST_SIZE;
	req->digest_sz = MD5_DIGEST_SIZE;
	req->block_sz = MD5_HMAC_BLOCK_SIZE;
	req->len_is_le = true; /* MD5 is little endian! ... */
	req->hmac = true;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_md5_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				     अचिन्हित पूर्णांक keylen)
अणु
	वापस safexcel_hmac_alg_setkey(tfm, key, keylen, "safexcel-md5",
					MD5_DIGEST_SIZE);
पूर्ण

अटल पूर्णांक safexcel_hmac_md5_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_hmac_md5_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_md5 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_MD5,
	.alg.ahash = अणु
		.init = safexcel_hmac_md5_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_hmac_md5_digest,
		.setkey = safexcel_hmac_md5_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(md5)",
				.cra_driver_name = "safexcel-hmac-md5",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_crc32_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक ret = safexcel_ahash_cra_init(tfm);

	/* Default 'key' is all zeroes */
	स_रखो(&ctx->base.ipad, 0, माप(u32));
	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_crc32_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from loaded key */
	req->state[0]	= cpu_to_le32(~ctx->base.ipad.word[0]);
	/* Set processed to non-zero to enable invalidation detection */
	req->len	= माप(u32);
	req->processed	= माप(u32);

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_CRC32;
	req->digest = CONTEXT_CONTROL_DIGEST_XCM;
	req->state_sz = माप(u32);
	req->digest_sz = माप(u32);
	req->block_sz = माप(u32);

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_crc32_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));

	अगर (keylen != माप(u32))
		वापस -EINVAL;

	स_नकल(&ctx->base.ipad, key, माप(u32));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_crc32_digest(काष्ठा ahash_request *areq)
अणु
	वापस safexcel_crc32_init(areq) ?: safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_crc32 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = 0,
	.alg.ahash = अणु
		.init = safexcel_crc32_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_crc32_digest,
		.setkey = safexcel_crc32_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = माप(u32),
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "crc32",
				.cra_driver_name = "safexcel-crc32",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_OPTIONAL_KEY |
					     CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = 1,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_crc32_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_cbcmac_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from loaded keys */
	स_नकल(req->state, &ctx->base.ipad, ctx->key_sz);
	/* Set processed to non-zero to enable invalidation detection */
	req->len	= AES_BLOCK_SIZE;
	req->processed	= AES_BLOCK_SIZE;

	req->digest   = CONTEXT_CONTROL_DIGEST_XCM;
	req->state_sz = ctx->key_sz;
	req->digest_sz = AES_BLOCK_SIZE;
	req->block_sz = AES_BLOCK_SIZE;
	req->xcbcmac  = true;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_cbcmac_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक len)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक ret, i;

	ret = aes_expandkey(&aes, key, len);
	अगर (ret)
		वापस ret;

	स_रखो(&ctx->base.ipad, 0, 2 * AES_BLOCK_SIZE);
	क्रम (i = 0; i < len / माप(u32); i++)
		ctx->base.ipad.be[i + 8] = cpu_to_be32(aes.key_enc[i]);

	अगर (len == AES_KEYSIZE_192) अणु
		ctx->alg    = CONTEXT_CONTROL_CRYPTO_ALG_XCBC192;
		ctx->key_sz = AES_MAX_KEY_SIZE + 2 * AES_BLOCK_SIZE;
	पूर्ण अन्यथा अगर (len == AES_KEYSIZE_256) अणु
		ctx->alg    = CONTEXT_CONTROL_CRYPTO_ALG_XCBC256;
		ctx->key_sz = AES_MAX_KEY_SIZE + 2 * AES_BLOCK_SIZE;
	पूर्ण अन्यथा अणु
		ctx->alg    = CONTEXT_CONTROL_CRYPTO_ALG_XCBC128;
		ctx->key_sz = AES_MIN_KEY_SIZE + 2 * AES_BLOCK_SIZE;
	पूर्ण
	ctx->cbcmac  = true;

	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_cbcmac_digest(काष्ठा ahash_request *areq)
अणु
	वापस safexcel_cbcmac_init(areq) ?: safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_cbcmac = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = 0,
	.alg.ahash = अणु
		.init = safexcel_cbcmac_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_cbcmac_digest,
		.setkey = safexcel_cbcmac_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = AES_BLOCK_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "cbcmac(aes)",
				.cra_driver_name = "safexcel-cbcmac-aes",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = 1,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_xcbcmac_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक len)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा crypto_aes_ctx aes;
	u32 key_पंचांगp[3 * AES_BLOCK_SIZE / माप(u32)];
	पूर्णांक ret, i;

	ret = aes_expandkey(&aes, key, len);
	अगर (ret)
		वापस ret;

	/* precompute the XCBC key material */
	crypto_cipher_clear_flags(ctx->kaes, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(ctx->kaes, crypto_ahash_get_flags(tfm) &
				CRYPTO_TFM_REQ_MASK);
	ret = crypto_cipher_setkey(ctx->kaes, key, len);
	अगर (ret)
		वापस ret;

	crypto_cipher_encrypt_one(ctx->kaes, (u8 *)key_पंचांगp + 2 * AES_BLOCK_SIZE,
		"\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1");
	crypto_cipher_encrypt_one(ctx->kaes, (u8 *)key_पंचांगp,
		"\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2");
	crypto_cipher_encrypt_one(ctx->kaes, (u8 *)key_पंचांगp + AES_BLOCK_SIZE,
		"\x3\x3\x3\x3\x3\x3\x3\x3\x3\x3\x3\x3\x3\x3\x3\x3");
	क्रम (i = 0; i < 3 * AES_BLOCK_SIZE / माप(u32); i++)
		ctx->base.ipad.word[i] = swab(key_पंचांगp[i]);

	crypto_cipher_clear_flags(ctx->kaes, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(ctx->kaes, crypto_ahash_get_flags(tfm) &
				CRYPTO_TFM_REQ_MASK);
	ret = crypto_cipher_setkey(ctx->kaes,
				   (u8 *)key_पंचांगp + 2 * AES_BLOCK_SIZE,
				   AES_MIN_KEY_SIZE);
	अगर (ret)
		वापस ret;

	ctx->alg    = CONTEXT_CONTROL_CRYPTO_ALG_XCBC128;
	ctx->key_sz = AES_MIN_KEY_SIZE + 2 * AES_BLOCK_SIZE;
	ctx->cbcmac = false;

	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_xcbcmac_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_ahash_cra_init(tfm);
	ctx->kaes = crypto_alloc_cipher("aes", 0, 0);
	वापस PTR_ERR_OR_ZERO(ctx->kaes);
पूर्ण

अटल व्योम safexcel_xcbcmac_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_cipher(ctx->kaes);
	safexcel_ahash_cra_निकास(tfm);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_xcbcmac = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = 0,
	.alg.ahash = अणु
		.init = safexcel_cbcmac_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_cbcmac_digest,
		.setkey = safexcel_xcbcmac_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = AES_BLOCK_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "xcbc(aes)",
				.cra_driver_name = "safexcel-xcbc-aes",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_xcbcmac_cra_init,
				.cra_निकास = safexcel_xcbcmac_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_cmac_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा crypto_aes_ctx aes;
	__be64 स्थिरs[4];
	u64 _स्थिर[2];
	u8 msb_mask, gfmask;
	पूर्णांक ret, i;

	ret = aes_expandkey(&aes, key, len);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < len / माप(u32); i++)
		ctx->base.ipad.word[i + 8] = swab(aes.key_enc[i]);

	/* precompute the CMAC key material */
	crypto_cipher_clear_flags(ctx->kaes, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(ctx->kaes, crypto_ahash_get_flags(tfm) &
				CRYPTO_TFM_REQ_MASK);
	ret = crypto_cipher_setkey(ctx->kaes, key, len);
	अगर (ret)
		वापस ret;

	/* code below borrowed from crypto/cmac.c */
	/* encrypt the zero block */
	स_रखो(स्थिरs, 0, AES_BLOCK_SIZE);
	crypto_cipher_encrypt_one(ctx->kaes, (u8 *)स्थिरs, (u8 *)स्थिरs);

	gfmask = 0x87;
	_स्थिर[0] = be64_to_cpu(स्थिरs[1]);
	_स्थिर[1] = be64_to_cpu(स्थिरs[0]);

	/* gf(2^128) multiply zero-ciphertext with u and u^2 */
	क्रम (i = 0; i < 4; i += 2) अणु
		msb_mask = ((s64)_स्थिर[1] >> 63) & gfmask;
		_स्थिर[1] = (_स्थिर[1] << 1) | (_स्थिर[0] >> 63);
		_स्थिर[0] = (_स्थिर[0] << 1) ^ msb_mask;

		स्थिरs[i + 0] = cpu_to_be64(_स्थिर[1]);
		स्थिरs[i + 1] = cpu_to_be64(_स्थिर[0]);
	पूर्ण
	/* end of code borrowed from crypto/cmac.c */

	क्रम (i = 0; i < 2 * AES_BLOCK_SIZE / माप(u32); i++)
		ctx->base.ipad.be[i] = cpu_to_be32(((u32 *)स्थिरs)[i]);

	अगर (len == AES_KEYSIZE_192) अणु
		ctx->alg    = CONTEXT_CONTROL_CRYPTO_ALG_XCBC192;
		ctx->key_sz = AES_MAX_KEY_SIZE + 2 * AES_BLOCK_SIZE;
	पूर्ण अन्यथा अगर (len == AES_KEYSIZE_256) अणु
		ctx->alg    = CONTEXT_CONTROL_CRYPTO_ALG_XCBC256;
		ctx->key_sz = AES_MAX_KEY_SIZE + 2 * AES_BLOCK_SIZE;
	पूर्ण अन्यथा अणु
		ctx->alg    = CONTEXT_CONTROL_CRYPTO_ALG_XCBC128;
		ctx->key_sz = AES_MIN_KEY_SIZE + 2 * AES_BLOCK_SIZE;
	पूर्ण
	ctx->cbcmac = false;

	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_cmac = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = 0,
	.alg.ahash = अणु
		.init = safexcel_cbcmac_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_cbcmac_digest,
		.setkey = safexcel_cmac_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = AES_BLOCK_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "cmac(aes)",
				.cra_driver_name = "safexcel-cmac-aes",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = AES_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_xcbcmac_cra_init,
				.cra_निकास = safexcel_xcbcmac_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sm3_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SM3;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SM3_DIGEST_SIZE;
	req->digest_sz = SM3_DIGEST_SIZE;
	req->block_sz = SM3_BLOCK_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sm3_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_sm3_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sm3 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SM3,
	.alg.ahash = अणु
		.init = safexcel_sm3_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sm3_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SM3_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sm3",
				.cra_driver_name = "safexcel-sm3",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SM3_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sm3_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				    अचिन्हित पूर्णांक keylen)
अणु
	वापस safexcel_hmac_alg_setkey(tfm, key, keylen, "safexcel-sm3",
					SM3_DIGEST_SIZE);
पूर्ण

अटल पूर्णांक safexcel_hmac_sm3_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Start from ipad precompute */
	स_नकल(req->state, &ctx->base.ipad, SM3_DIGEST_SIZE);
	/* Alपढ़ोy processed the key^ipad part now! */
	req->len	= SM3_BLOCK_SIZE;
	req->processed	= SM3_BLOCK_SIZE;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SM3;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SM3_DIGEST_SIZE;
	req->digest_sz = SM3_DIGEST_SIZE;
	req->block_sz = SM3_BLOCK_SIZE;
	req->hmac = true;

	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sm3_digest(काष्ठा ahash_request *areq)
अणु
	पूर्णांक ret = safexcel_hmac_sm3_init(areq);

	अगर (ret)
		वापस ret;

	वापस safexcel_ahash_finup(areq);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sm3 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SM3,
	.alg.ahash = अणु
		.init = safexcel_hmac_sm3_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_hmac_sm3_digest,
		.setkey = safexcel_hmac_sm3_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = अणु
			.digestsize = SM3_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sm3)",
				.cra_driver_name = "safexcel-hmac-sm3",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_ALLOCATES_MEMORY |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SM3_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_निकास = safexcel_ahash_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sha3_224_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA3_224;
	req->digest = CONTEXT_CONTROL_DIGEST_INITIAL;
	req->state_sz = SHA3_224_DIGEST_SIZE;
	req->digest_sz = SHA3_224_DIGEST_SIZE;
	req->block_sz = SHA3_224_BLOCK_SIZE;
	ctx->करो_fallback = false;
	ctx->fb_init_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha3_fbcheck(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *subreq = ahash_request_ctx(req);
	पूर्णांक ret = 0;

	अगर (ctx->करो_fallback) अणु
		ahash_request_set_tfm(subreq, ctx->fback);
		ahash_request_set_callback(subreq, req->base.flags,
					   req->base.complete, req->base.data);
		ahash_request_set_crypt(subreq, req->src, req->result,
					req->nbytes);
		अगर (!ctx->fb_init_करोne) अणु
			अगर (ctx->fb_करो_setkey) अणु
				/* Set fallback cipher HMAC key */
				u8 key[SHA3_224_BLOCK_SIZE];

				स_नकल(key, &ctx->base.ipad,
				       crypto_ahash_blocksize(ctx->fback) / 2);
				स_नकल(key +
				       crypto_ahash_blocksize(ctx->fback) / 2,
				       &ctx->base.opad,
				       crypto_ahash_blocksize(ctx->fback) / 2);
				ret = crypto_ahash_setkey(ctx->fback, key,
					crypto_ahash_blocksize(ctx->fback));
				memzero_explicit(key,
					crypto_ahash_blocksize(ctx->fback));
				ctx->fb_करो_setkey = false;
			पूर्ण
			ret = ret ?: crypto_ahash_init(subreq);
			ctx->fb_init_करोne = true;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_sha3_update(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *subreq = ahash_request_ctx(req);

	ctx->करो_fallback = true;
	वापस safexcel_sha3_fbcheck(req) ?: crypto_ahash_update(subreq);
पूर्ण

अटल पूर्णांक safexcel_sha3_final(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *subreq = ahash_request_ctx(req);

	ctx->करो_fallback = true;
	वापस safexcel_sha3_fbcheck(req) ?: crypto_ahash_final(subreq);
पूर्ण

अटल पूर्णांक safexcel_sha3_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *subreq = ahash_request_ctx(req);

	ctx->करो_fallback |= !req->nbytes;
	अगर (ctx->करो_fallback)
		/* Update or ex/import happened or len 0, cannot use the HW */
		वापस safexcel_sha3_fbcheck(req) ?:
		       crypto_ahash_finup(subreq);
	अन्यथा
		वापस safexcel_ahash_finup(req);
पूर्ण

अटल पूर्णांक safexcel_sha3_digest_fallback(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *subreq = ahash_request_ctx(req);

	ctx->करो_fallback = true;
	ctx->fb_init_करोne = false;
	वापस safexcel_sha3_fbcheck(req) ?: crypto_ahash_finup(subreq);
पूर्ण

अटल पूर्णांक safexcel_sha3_224_digest(काष्ठा ahash_request *req)
अणु
	अगर (req->nbytes)
		वापस safexcel_sha3_224_init(req) ?: safexcel_ahash_finup(req);

	/* HW cannot करो zero length hash, use fallback instead */
	वापस safexcel_sha3_digest_fallback(req);
पूर्ण

अटल पूर्णांक safexcel_sha3_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *subreq = ahash_request_ctx(req);

	ctx->करो_fallback = true;
	वापस safexcel_sha3_fbcheck(req) ?: crypto_ahash_export(subreq, out);
पूर्ण

अटल पूर्णांक safexcel_sha3_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *subreq = ahash_request_ctx(req);

	ctx->करो_fallback = true;
	वापस safexcel_sha3_fbcheck(req) ?: crypto_ahash_import(subreq, in);
	// वापस safexcel_ahash_import(req, in);
पूर्ण

अटल पूर्णांक safexcel_sha3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_ahash_cra_init(tfm);

	/* Allocate fallback implementation */
	ctx->fback = crypto_alloc_ahash(crypto_tfm_alg_name(tfm), 0,
					CRYPTO_ALG_ASYNC |
					CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->fback))
		वापस PTR_ERR(ctx->fback);

	/* Update statesize from fallback algorithm! */
	crypto_hash_alg_common(ahash)->statesize =
		crypto_ahash_statesize(ctx->fback);
	crypto_ahash_set_reqsize(ahash, max(माप(काष्ठा safexcel_ahash_req),
					    माप(काष्ठा ahash_request) +
					    crypto_ahash_reqsize(ctx->fback)));
	वापस 0;
पूर्ण

अटल व्योम safexcel_sha3_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_ahash(ctx->fback);
	safexcel_ahash_cra_निकास(tfm);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha3_224 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA3,
	.alg.ahash = अणु
		.init = safexcel_sha3_224_init,
		.update = safexcel_sha3_update,
		.final = safexcel_sha3_final,
		.finup = safexcel_sha3_finup,
		.digest = safexcel_sha3_224_digest,
		.export = safexcel_sha3_export,
		.import = safexcel_sha3_import,
		.halg = अणु
			.digestsize = SHA3_224_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha3-224",
				.cra_driver_name = "safexcel-sha3-224",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY |
					     CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA3_224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_sha3_cra_init,
				.cra_निकास = safexcel_sha3_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sha3_256_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA3_256;
	req->digest = CONTEXT_CONTROL_DIGEST_INITIAL;
	req->state_sz = SHA3_256_DIGEST_SIZE;
	req->digest_sz = SHA3_256_DIGEST_SIZE;
	req->block_sz = SHA3_256_BLOCK_SIZE;
	ctx->करो_fallback = false;
	ctx->fb_init_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha3_256_digest(काष्ठा ahash_request *req)
अणु
	अगर (req->nbytes)
		वापस safexcel_sha3_256_init(req) ?: safexcel_ahash_finup(req);

	/* HW cannot करो zero length hash, use fallback instead */
	वापस safexcel_sha3_digest_fallback(req);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha3_256 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA3,
	.alg.ahash = अणु
		.init = safexcel_sha3_256_init,
		.update = safexcel_sha3_update,
		.final = safexcel_sha3_final,
		.finup = safexcel_sha3_finup,
		.digest = safexcel_sha3_256_digest,
		.export = safexcel_sha3_export,
		.import = safexcel_sha3_import,
		.halg = अणु
			.digestsize = SHA3_256_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha3-256",
				.cra_driver_name = "safexcel-sha3-256",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY |
					     CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA3_256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_sha3_cra_init,
				.cra_निकास = safexcel_sha3_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sha3_384_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA3_384;
	req->digest = CONTEXT_CONTROL_DIGEST_INITIAL;
	req->state_sz = SHA3_384_DIGEST_SIZE;
	req->digest_sz = SHA3_384_DIGEST_SIZE;
	req->block_sz = SHA3_384_BLOCK_SIZE;
	ctx->करो_fallback = false;
	ctx->fb_init_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha3_384_digest(काष्ठा ahash_request *req)
अणु
	अगर (req->nbytes)
		वापस safexcel_sha3_384_init(req) ?: safexcel_ahash_finup(req);

	/* HW cannot करो zero length hash, use fallback instead */
	वापस safexcel_sha3_digest_fallback(req);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha3_384 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA3,
	.alg.ahash = अणु
		.init = safexcel_sha3_384_init,
		.update = safexcel_sha3_update,
		.final = safexcel_sha3_final,
		.finup = safexcel_sha3_finup,
		.digest = safexcel_sha3_384_digest,
		.export = safexcel_sha3_export,
		.import = safexcel_sha3_import,
		.halg = अणु
			.digestsize = SHA3_384_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha3-384",
				.cra_driver_name = "safexcel-sha3-384",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY |
					     CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA3_384_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_sha3_cra_init,
				.cra_निकास = safexcel_sha3_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_sha3_512_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA3_512;
	req->digest = CONTEXT_CONTROL_DIGEST_INITIAL;
	req->state_sz = SHA3_512_DIGEST_SIZE;
	req->digest_sz = SHA3_512_DIGEST_SIZE;
	req->block_sz = SHA3_512_BLOCK_SIZE;
	ctx->करो_fallback = false;
	ctx->fb_init_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_sha3_512_digest(काष्ठा ahash_request *req)
अणु
	अगर (req->nbytes)
		वापस safexcel_sha3_512_init(req) ?: safexcel_ahash_finup(req);

	/* HW cannot करो zero length hash, use fallback instead */
	वापस safexcel_sha3_digest_fallback(req);
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_sha3_512 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA3,
	.alg.ahash = अणु
		.init = safexcel_sha3_512_init,
		.update = safexcel_sha3_update,
		.final = safexcel_sha3_final,
		.finup = safexcel_sha3_finup,
		.digest = safexcel_sha3_512_digest,
		.export = safexcel_sha3_export,
		.import = safexcel_sha3_import,
		.halg = अणु
			.digestsize = SHA3_512_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "sha3-512",
				.cra_driver_name = "safexcel-sha3-512",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY |
					     CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA3_512_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_sha3_cra_init,
				.cra_निकास = safexcel_sha3_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha3_cra_init(काष्ठा crypto_tfm *tfm, स्थिर अक्षर *alg)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक ret;

	ret = safexcel_sha3_cra_init(tfm);
	अगर (ret)
		वापस ret;

	/* Allocate precalc basic digest implementation */
	ctx->shpre = crypto_alloc_shash(alg, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->shpre))
		वापस PTR_ERR(ctx->shpre);

	ctx->shdesc = kदो_स्मृति(माप(*ctx->shdesc) +
			      crypto_shash_descsize(ctx->shpre), GFP_KERNEL);
	अगर (!ctx->shdesc) अणु
		crypto_मुक्त_shash(ctx->shpre);
		वापस -ENOMEM;
	पूर्ण
	ctx->shdesc->tfm = ctx->shpre;
	वापस 0;
पूर्ण

अटल व्योम safexcel_hmac_sha3_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_ahash(ctx->fback);
	crypto_मुक्त_shash(ctx->shpre);
	kमुक्त(ctx->shdesc);
	safexcel_ahash_cra_निकास(tfm);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	पूर्णांक ret = 0;

	अगर (keylen > crypto_ahash_blocksize(tfm)) अणु
		/*
		 * If the key is larger than the blocksize, then hash it
		 * first using our fallback cipher
		 */
		ret = crypto_shash_digest(ctx->shdesc, key, keylen,
					  ctx->base.ipad.byte);
		keylen = crypto_shash_digestsize(ctx->shpre);

		/*
		 * If the digest is larger than half the blocksize, we need to
		 * move the rest to opad due to the way our HMAC infra works.
		 */
		अगर (keylen > crypto_ahash_blocksize(tfm) / 2)
			/* Buffers overlap, need to use स_हटाओ iso स_नकल! */
			स_हटाओ(&ctx->base.opad,
				ctx->base.ipad.byte +
					crypto_ahash_blocksize(tfm) / 2,
				keylen - crypto_ahash_blocksize(tfm) / 2);
	पूर्ण अन्यथा अणु
		/*
		 * Copy the key to our ipad & opad buffers
		 * Note that ipad and opad each contain one half of the key,
		 * to match the existing HMAC driver infraकाष्ठाure.
		 */
		अगर (keylen <= crypto_ahash_blocksize(tfm) / 2) अणु
			स_नकल(&ctx->base.ipad, key, keylen);
		पूर्ण अन्यथा अणु
			स_नकल(&ctx->base.ipad, key,
			       crypto_ahash_blocksize(tfm) / 2);
			स_नकल(&ctx->base.opad,
			       key + crypto_ahash_blocksize(tfm) / 2,
			       keylen - crypto_ahash_blocksize(tfm) / 2);
		पूर्ण
	पूर्ण

	/* Pad key with zeroes */
	अगर (keylen <= crypto_ahash_blocksize(tfm) / 2) अणु
		स_रखो(ctx->base.ipad.byte + keylen, 0,
		       crypto_ahash_blocksize(tfm) / 2 - keylen);
		स_रखो(&ctx->base.opad, 0, crypto_ahash_blocksize(tfm) / 2);
	पूर्ण अन्यथा अणु
		स_रखो(ctx->base.opad.byte + keylen -
		       crypto_ahash_blocksize(tfm) / 2, 0,
		       crypto_ahash_blocksize(tfm) - keylen);
	पूर्ण

	/* If करोing fallback, still need to set the new key! */
	ctx->fb_करो_setkey = true;
	वापस ret;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_224_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Copy (half of) the key */
	स_नकल(req->state, &ctx->base.ipad, SHA3_224_BLOCK_SIZE / 2);
	/* Start of HMAC should have len == processed == blocksize */
	req->len	= SHA3_224_BLOCK_SIZE;
	req->processed	= SHA3_224_BLOCK_SIZE;
	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA3_224;
	req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	req->state_sz = SHA3_224_BLOCK_SIZE / 2;
	req->digest_sz = SHA3_224_DIGEST_SIZE;
	req->block_sz = SHA3_224_BLOCK_SIZE;
	req->hmac = true;
	ctx->करो_fallback = false;
	ctx->fb_init_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_224_digest(काष्ठा ahash_request *req)
अणु
	अगर (req->nbytes)
		वापस safexcel_hmac_sha3_224_init(req) ?:
		       safexcel_ahash_finup(req);

	/* HW cannot करो zero length HMAC, use fallback instead */
	वापस safexcel_sha3_digest_fallback(req);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_224_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस safexcel_hmac_sha3_cra_init(tfm, "sha3-224");
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha3_224 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA3,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha3_224_init,
		.update = safexcel_sha3_update,
		.final = safexcel_sha3_final,
		.finup = safexcel_sha3_finup,
		.digest = safexcel_hmac_sha3_224_digest,
		.setkey = safexcel_hmac_sha3_setkey,
		.export = safexcel_sha3_export,
		.import = safexcel_sha3_import,
		.halg = अणु
			.digestsize = SHA3_224_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha3-224)",
				.cra_driver_name = "safexcel-hmac-sha3-224",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY |
					     CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA3_224_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_hmac_sha3_224_cra_init,
				.cra_निकास = safexcel_hmac_sha3_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha3_256_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Copy (half of) the key */
	स_नकल(req->state, &ctx->base.ipad, SHA3_256_BLOCK_SIZE / 2);
	/* Start of HMAC should have len == processed == blocksize */
	req->len	= SHA3_256_BLOCK_SIZE;
	req->processed	= SHA3_256_BLOCK_SIZE;
	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA3_256;
	req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	req->state_sz = SHA3_256_BLOCK_SIZE / 2;
	req->digest_sz = SHA3_256_DIGEST_SIZE;
	req->block_sz = SHA3_256_BLOCK_SIZE;
	req->hmac = true;
	ctx->करो_fallback = false;
	ctx->fb_init_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_256_digest(काष्ठा ahash_request *req)
अणु
	अगर (req->nbytes)
		वापस safexcel_hmac_sha3_256_init(req) ?:
		       safexcel_ahash_finup(req);

	/* HW cannot करो zero length HMAC, use fallback instead */
	वापस safexcel_sha3_digest_fallback(req);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_256_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस safexcel_hmac_sha3_cra_init(tfm, "sha3-256");
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha3_256 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA3,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha3_256_init,
		.update = safexcel_sha3_update,
		.final = safexcel_sha3_final,
		.finup = safexcel_sha3_finup,
		.digest = safexcel_hmac_sha3_256_digest,
		.setkey = safexcel_hmac_sha3_setkey,
		.export = safexcel_sha3_export,
		.import = safexcel_sha3_import,
		.halg = अणु
			.digestsize = SHA3_256_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha3-256)",
				.cra_driver_name = "safexcel-hmac-sha3-256",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY |
					     CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA3_256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_hmac_sha3_256_cra_init,
				.cra_निकास = safexcel_hmac_sha3_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha3_384_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Copy (half of) the key */
	स_नकल(req->state, &ctx->base.ipad, SHA3_384_BLOCK_SIZE / 2);
	/* Start of HMAC should have len == processed == blocksize */
	req->len	= SHA3_384_BLOCK_SIZE;
	req->processed	= SHA3_384_BLOCK_SIZE;
	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA3_384;
	req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	req->state_sz = SHA3_384_BLOCK_SIZE / 2;
	req->digest_sz = SHA3_384_DIGEST_SIZE;
	req->block_sz = SHA3_384_BLOCK_SIZE;
	req->hmac = true;
	ctx->करो_fallback = false;
	ctx->fb_init_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_384_digest(काष्ठा ahash_request *req)
अणु
	अगर (req->nbytes)
		वापस safexcel_hmac_sha3_384_init(req) ?:
		       safexcel_ahash_finup(req);

	/* HW cannot करो zero length HMAC, use fallback instead */
	वापस safexcel_sha3_digest_fallback(req);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_384_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस safexcel_hmac_sha3_cra_init(tfm, "sha3-384");
पूर्ण

काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha3_384 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA3,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha3_384_init,
		.update = safexcel_sha3_update,
		.final = safexcel_sha3_final,
		.finup = safexcel_sha3_finup,
		.digest = safexcel_hmac_sha3_384_digest,
		.setkey = safexcel_hmac_sha3_setkey,
		.export = safexcel_sha3_export,
		.import = safexcel_sha3_import,
		.halg = अणु
			.digestsize = SHA3_384_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha3-384)",
				.cra_driver_name = "safexcel-hmac-sha3-384",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY |
					     CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA3_384_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_hmac_sha3_384_cra_init,
				.cra_निकास = safexcel_hmac_sha3_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक safexcel_hmac_sha3_512_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	काष्ठा safexcel_ahash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा safexcel_ahash_req *req = ahash_request_ctx(areq);

	स_रखो(req, 0, माप(*req));

	/* Copy (half of) the key */
	स_नकल(req->state, &ctx->base.ipad, SHA3_512_BLOCK_SIZE / 2);
	/* Start of HMAC should have len == processed == blocksize */
	req->len	= SHA3_512_BLOCK_SIZE;
	req->processed	= SHA3_512_BLOCK_SIZE;
	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA3_512;
	req->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	req->state_sz = SHA3_512_BLOCK_SIZE / 2;
	req->digest_sz = SHA3_512_DIGEST_SIZE;
	req->block_sz = SHA3_512_BLOCK_SIZE;
	req->hmac = true;
	ctx->करो_fallback = false;
	ctx->fb_init_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_512_digest(काष्ठा ahash_request *req)
अणु
	अगर (req->nbytes)
		वापस safexcel_hmac_sha3_512_init(req) ?:
		       safexcel_ahash_finup(req);

	/* HW cannot करो zero length HMAC, use fallback instead */
	वापस safexcel_sha3_digest_fallback(req);
पूर्ण

अटल पूर्णांक safexcel_hmac_sha3_512_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस safexcel_hmac_sha3_cra_init(tfm, "sha3-512");
पूर्ण
काष्ठा safexcel_alg_ढाँचा safexcel_alg_hmac_sha3_512 = अणु
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.algo_mask = SAFEXCEL_ALG_SHA3,
	.alg.ahash = अणु
		.init = safexcel_hmac_sha3_512_init,
		.update = safexcel_sha3_update,
		.final = safexcel_sha3_final,
		.finup = safexcel_sha3_finup,
		.digest = safexcel_hmac_sha3_512_digest,
		.setkey = safexcel_hmac_sha3_setkey,
		.export = safexcel_sha3_export,
		.import = safexcel_sha3_import,
		.halg = अणु
			.digestsize = SHA3_512_DIGEST_SIZE,
			.statesize = माप(काष्ठा safexcel_ahash_export_state),
			.base = अणु
				.cra_name = "hmac(sha3-512)",
				.cra_driver_name = "safexcel-hmac-sha3-512",
				.cra_priority = SAFEXCEL_CRA_PRIORITY,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY |
					     CRYPTO_ALG_NEED_FALLBACK,
				.cra_blocksize = SHA3_512_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा safexcel_ahash_ctx),
				.cra_init = safexcel_hmac_sha3_512_cra_init,
				.cra_निकास = safexcel_hmac_sha3_cra_निकास,
				.cra_module = THIS_MODULE,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;
