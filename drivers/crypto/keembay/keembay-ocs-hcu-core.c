<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Keem Bay OCS HCU Crypto Driver.
 *
 * Copyright (C) 2018-2020 Intel Corporation
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#समावेश <crypto/engine.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sm3.h>
#समावेश <crypto/hmac.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश "ocs-hcu.h"

#घोषणा DRV_NAME	"keembay-ocs-hcu"

/* Flag marking a final request. */
#घोषणा REQ_FINAL			BIT(0)
/* Flag marking a HMAC request. */
#घोषणा REQ_FLAGS_HMAC			BIT(1)
/* Flag set when HW HMAC is being used. */
#घोषणा REQ_FLAGS_HMAC_HW		BIT(2)
/* Flag set when SW HMAC is being used. */
#घोषणा REQ_FLAGS_HMAC_SW		BIT(3)

/**
 * काष्ठा ocs_hcu_ctx: OCS HCU Transक्रमm context.
 * @engine_ctx:	 Crypto Engine context.
 * @hcu_dev:	 The OCS HCU device used by the transक्रमmation.
 * @key:	 The key (used only क्रम HMAC transक्रमmations).
 * @key_len:	 The length of the key.
 * @is_sm3_tfm:  Whether or not this is an SM3 transक्रमmation.
 * @is_hmac_tfm: Whether or not this is a HMAC transक्रमmation.
 */
काष्ठा ocs_hcu_ctx अणु
	काष्ठा crypto_engine_ctx engine_ctx;
	काष्ठा ocs_hcu_dev *hcu_dev;
	u8 key[SHA512_BLOCK_SIZE];
	माप_प्रकार key_len;
	bool is_sm3_tfm;
	bool is_hmac_tfm;
पूर्ण;

/**
 * काष्ठा ocs_hcu_rctx - Context क्रम the request.
 * @hcu_dev:	    OCS HCU device to be used to service the request.
 * @flags:	    Flags tracking request status.
 * @algo:	    Algorithm to use क्रम the request.
 * @blk_sz:	    Block size of the transक्रमmation / request.
 * @dig_sz:	    Digest size of the transक्रमmation / request.
 * @dma_list:	    OCS DMA linked list.
 * @hash_ctx:	    OCS HCU hashing context.
 * @buffer:	    Buffer to store: partial block of data and SW HMAC
 *		    artअगरacts (ipad, opad, etc.).
 * @buf_cnt:	    Number of bytes currently stored in the buffer.
 * @buf_dma_addr:   The DMA address of @buffer (when mapped).
 * @buf_dma_count:  The number of bytes in @buffer currently DMA-mapped.
 * @sg:		    Head of the scatterlist entries containing data.
 * @sg_data_total:  Total data in the SG list at any समय.
 * @sg_data_offset: Offset पूर्णांकo the data of the current inभागidual SG node.
 * @sg_dma_nents:   Number of sg entries mapped in dma_list.
 */
काष्ठा ocs_hcu_rctx अणु
	काष्ठा ocs_hcu_dev	*hcu_dev;
	u32			flags;
	क्रमागत ocs_hcu_algo	algo;
	माप_प्रकार			blk_sz;
	माप_प्रकार			dig_sz;
	काष्ठा ocs_hcu_dma_list	*dma_list;
	काष्ठा ocs_hcu_hash_ctx	hash_ctx;
	/*
	 * Buffer is द्विगुन the block size because we need space क्रम SW HMAC
	 * artअगरacts, i.e:
	 * - ipad (1 block) + a possible partial block of data.
	 * - opad (1 block) + digest of H(k ^ ipad || m)
	 */
	u8			buffer[2 * SHA512_BLOCK_SIZE];
	माप_प्रकार			buf_cnt;
	dma_addr_t		buf_dma_addr;
	माप_प्रकार			buf_dma_count;
	काष्ठा scatterlist	*sg;
	अचिन्हित पूर्णांक		sg_data_total;
	अचिन्हित पूर्णांक		sg_data_offset;
	अचिन्हित पूर्णांक		sg_dma_nents;
पूर्ण;

/**
 * काष्ठा ocs_hcu_drv - Driver data
 * @dev_list:	The list of HCU devices.
 * @lock:	The lock protecting dev_list.
 */
काष्ठा ocs_hcu_drv अणु
	काष्ठा list_head dev_list;
	spinlock_t lock; /* Protects dev_list. */
पूर्ण;

अटल काष्ठा ocs_hcu_drv ocs_hcu = अणु
	.dev_list = LIST_HEAD_INIT(ocs_hcu.dev_list),
	.lock = __SPIN_LOCK_UNLOCKED(ocs_hcu.lock),
पूर्ण;

/*
 * Return the total amount of data in the request; that is: the data in the
 * request buffer + the data in the sg list.
 */
अटल अंतरभूत अचिन्हित पूर्णांक kmb_get_total_data(काष्ठा ocs_hcu_rctx *rctx)
अणु
	वापस rctx->sg_data_total + rctx->buf_cnt;
पूर्ण

/* Move reमुख्यing content of scatter-gather list to context buffer. */
अटल पूर्णांक flush_sg_to_ocs_buffer(काष्ठा ocs_hcu_rctx *rctx)
अणु
	माप_प्रकार count;

	अगर (rctx->sg_data_total > (माप(rctx->buffer) - rctx->buf_cnt)) अणु
		WARN(1, "%s: sg data does not fit in buffer\n", __func__);
		वापस -EINVAL;
	पूर्ण

	जबतक (rctx->sg_data_total) अणु
		अगर (!rctx->sg) अणु
			WARN(1, "%s: unexpected NULL sg\n", __func__);
			वापस -EINVAL;
		पूर्ण
		/*
		 * If current sg has been fully processed, skip to the next
		 * one.
		 */
		अगर (rctx->sg_data_offset == rctx->sg->length) अणु
			rctx->sg = sg_next(rctx->sg);
			rctx->sg_data_offset = 0;
			जारी;
		पूर्ण
		/*
		 * Determine the maximum data available to copy from the node.
		 * Minimum of the length left in the sg node, or the total data
		 * in the request.
		 */
		count = min(rctx->sg->length - rctx->sg_data_offset,
			    rctx->sg_data_total);
		/* Copy from scatter-list entry to context buffer. */
		scatterwalk_map_and_copy(&rctx->buffer[rctx->buf_cnt],
					 rctx->sg, rctx->sg_data_offset,
					 count, 0);

		rctx->sg_data_offset += count;
		rctx->sg_data_total -= count;
		rctx->buf_cnt += count;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ocs_hcu_dev *kmb_ocs_hcu_find_dev(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ocs_hcu_ctx *tctx = crypto_ahash_ctx(tfm);

	/* If the HCU device क्रम the request was previously set, वापस it. */
	अगर (tctx->hcu_dev)
		वापस tctx->hcu_dev;

	/*
	 * Otherwise, get the first HCU device available (there should be one
	 * and only one device).
	 */
	spin_lock_bh(&ocs_hcu.lock);
	tctx->hcu_dev = list_first_entry_or_null(&ocs_hcu.dev_list,
						 काष्ठा ocs_hcu_dev,
						 list);
	spin_unlock_bh(&ocs_hcu.lock);

	वापस tctx->hcu_dev;
पूर्ण

/* Free OCS DMA linked list and DMA-able context buffer. */
अटल व्योम kmb_ocs_hcu_dma_cleanup(काष्ठा ahash_request *req,
				    काष्ठा ocs_hcu_rctx *rctx)
अणु
	काष्ठा ocs_hcu_dev *hcu_dev = rctx->hcu_dev;
	काष्ठा device *dev = hcu_dev->dev;

	/* Unmap rctx->buffer (अगर mapped). */
	अगर (rctx->buf_dma_count) अणु
		dma_unmap_single(dev, rctx->buf_dma_addr, rctx->buf_dma_count,
				 DMA_TO_DEVICE);
		rctx->buf_dma_count = 0;
	पूर्ण

	/* Unmap req->src (अगर mapped). */
	अगर (rctx->sg_dma_nents) अणु
		dma_unmap_sg(dev, req->src, rctx->sg_dma_nents, DMA_TO_DEVICE);
		rctx->sg_dma_nents = 0;
	पूर्ण

	/* Free dma_list (अगर allocated). */
	अगर (rctx->dma_list) अणु
		ocs_hcu_dma_list_मुक्त(hcu_dev, rctx->dma_list);
		rctx->dma_list = शून्य;
	पूर्ण
पूर्ण

/*
 * Prepare क्रम DMA operation:
 * - DMA-map request context buffer (अगर needed)
 * - DMA-map SG list (only the entries to be processed, see note below)
 * - Allocate OCS HCU DMA linked list (number of elements =  SG entries to
 *   process + context buffer (अगर not empty)).
 * - Add DMA-mapped request context buffer to OCS HCU DMA list.
 * - Add SG entries to DMA list.
 *
 * Note: अगर this is a final request, we process all the data in the SG list,
 * otherwise we can only process up to the maximum amount of block-aligned data
 * (the reमुख्यder will be put पूर्णांकo the context buffer and processed in the next
 * request).
 */
अटल पूर्णांक kmb_ocs_dma_prepare(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);
	काष्ठा device *dev = rctx->hcu_dev->dev;
	अचिन्हित पूर्णांक reमुख्यder = 0;
	अचिन्हित पूर्णांक total;
	माप_प्रकार nents;
	माप_प्रकार count;
	पूर्णांक rc;
	पूर्णांक i;

	/* This function should be called only when there is data to process. */
	total = kmb_get_total_data(rctx);
	अगर (!total)
		वापस -EINVAL;

	/*
	 * If this is not a final DMA (terminated DMA), the data passed to the
	 * HCU must be aligned to the block size; compute the reमुख्यder data to
	 * be processed in the next request.
	 */
	अगर (!(rctx->flags & REQ_FINAL))
		reमुख्यder = total % rctx->blk_sz;

	/* Determine the number of scatter gather list entries to process. */
	nents = sg_nents_क्रम_len(req->src, rctx->sg_data_total - reमुख्यder);

	/* If there are entries to process, map them. */
	अगर (nents) अणु
		rctx->sg_dma_nents = dma_map_sg(dev, req->src, nents,
						DMA_TO_DEVICE);
		अगर (!rctx->sg_dma_nents) अणु
			dev_err(dev, "Failed to MAP SG\n");
			rc = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		/*
		 * The value वापसed by dma_map_sg() can be < nents; so update
		 * nents accordingly.
		 */
		nents = rctx->sg_dma_nents;
	पूर्ण

	/*
	 * If context buffer is not empty, map it and add extra DMA entry क्रम
	 * it.
	 */
	अगर (rctx->buf_cnt) अणु
		rctx->buf_dma_addr = dma_map_single(dev, rctx->buffer,
						    rctx->buf_cnt,
						    DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, rctx->buf_dma_addr)) अणु
			dev_err(dev, "Failed to map request context buffer\n");
			rc = -ENOMEM;
			जाओ cleanup;
		पूर्ण
		rctx->buf_dma_count = rctx->buf_cnt;
		/* Increase number of dma entries. */
		nents++;
	पूर्ण

	/* Allocate OCS HCU DMA list. */
	rctx->dma_list = ocs_hcu_dma_list_alloc(rctx->hcu_dev, nents);
	अगर (!rctx->dma_list) अणु
		rc = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	/* Add request context buffer (अगर previously DMA-mapped) */
	अगर (rctx->buf_dma_count) अणु
		rc = ocs_hcu_dma_list_add_tail(rctx->hcu_dev, rctx->dma_list,
					       rctx->buf_dma_addr,
					       rctx->buf_dma_count);
		अगर (rc)
			जाओ cleanup;
	पूर्ण

	/* Add the SG nodes to be processed to the DMA linked list. */
	क्रम_each_sg(req->src, rctx->sg, rctx->sg_dma_nents, i) अणु
		/*
		 * The number of bytes to add to the list entry is the minimum
		 * between:
		 * - The DMA length of the SG entry.
		 * - The data left to be processed.
		 */
		count = min(rctx->sg_data_total - reमुख्यder,
			    sg_dma_len(rctx->sg) - rctx->sg_data_offset);
		/*
		 * Do not create a zero length DMA descriptor. Check in हाल of
		 * zero length SG node.
		 */
		अगर (count == 0)
			जारी;
		/* Add sg to HCU DMA list. */
		rc = ocs_hcu_dma_list_add_tail(rctx->hcu_dev,
					       rctx->dma_list,
					       rctx->sg->dma_address,
					       count);
		अगर (rc)
			जाओ cleanup;

		/* Update amount of data reमुख्यing in SG list. */
		rctx->sg_data_total -= count;

		/*
		 * If  reमुख्यing data is equal to reमुख्यder (note: 'less than'
		 * हाल should never happen in practice), we are करोne: update
		 * offset and निकास the loop.
		 */
		अगर (rctx->sg_data_total <= reमुख्यder) अणु
			WARN_ON(rctx->sg_data_total < reमुख्यder);
			rctx->sg_data_offset += count;
			अवरोध;
		पूर्ण

		/*
		 * If we get here is because we need to process the next sg in
		 * the list; set offset within the sg to 0.
		 */
		rctx->sg_data_offset = 0;
	पूर्ण

	वापस 0;
cleanup:
	dev_err(dev, "Failed to prepare DMA.\n");
	kmb_ocs_hcu_dma_cleanup(req, rctx);

	वापस rc;
पूर्ण

अटल व्योम kmb_ocs_hcu_secure_cleanup(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);

	/* Clear buffer of any data. */
	memzero_explicit(rctx->buffer, माप(rctx->buffer));
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_handle_queue(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_dev *hcu_dev = kmb_ocs_hcu_find_dev(req);

	अगर (!hcu_dev)
		वापस -ENOENT;

	वापस crypto_transfer_hash_request_to_engine(hcu_dev->engine, req);
पूर्ण

अटल पूर्णांक prepare_ipad(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ocs_hcu_ctx *ctx = crypto_ahash_ctx(tfm);
	पूर्णांक i;

	WARN(rctx->buf_cnt, "%s: Context buffer is not empty\n", __func__);
	WARN(!(rctx->flags & REQ_FLAGS_HMAC_SW),
	     "%s: HMAC_SW flag is not set\n", __func__);
	/*
	 * Key length must be equal to block size. If key is लघुer,
	 * we pad it with zero (note: key cannot be दीर्घer, since
	 * दीर्घer keys are hashed by kmb_ocs_hcu_setkey()).
	 */
	अगर (ctx->key_len > rctx->blk_sz) अणु
		WARN(1, "%s: Invalid key length in tfm context\n", __func__);
		वापस -EINVAL;
	पूर्ण
	memzero_explicit(&ctx->key[ctx->key_len],
			 rctx->blk_sz - ctx->key_len);
	ctx->key_len = rctx->blk_sz;
	/*
	 * Prepare IPAD क्रम HMAC. Only करोne क्रम first block.
	 * HMAC(k,m) = H(k ^ opad || H(k ^ ipad || m))
	 * k ^ ipad will be first hashed block.
	 * k ^ opad will be calculated in the final request.
	 * Only needed अगर not using HW HMAC.
	 */
	क्रम (i = 0; i < rctx->blk_sz; i++)
		rctx->buffer[i] = ctx->key[i] ^ HMAC_IPAD_VALUE;
	rctx->buf_cnt = rctx->blk_sz;

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_करो_one_request(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा ahash_request *req = container_of(areq, काष्ठा ahash_request,
						 base);
	काष्ठा ocs_hcu_dev *hcu_dev = kmb_ocs_hcu_find_dev(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);
	काष्ठा ocs_hcu_ctx *tctx = crypto_ahash_ctx(tfm);
	पूर्णांक rc;
	पूर्णांक i;

	अगर (!hcu_dev) अणु
		rc = -ENOENT;
		जाओ error;
	पूर्ण

	/*
	 * If hardware HMAC flag is set, perक्रमm HMAC in hardware.
	 *
	 * NOTE: this flag implies REQ_FINAL && kmb_get_total_data(rctx)
	 */
	अगर (rctx->flags & REQ_FLAGS_HMAC_HW) अणु
		/* Map input data पूर्णांकo the HCU DMA linked list. */
		rc = kmb_ocs_dma_prepare(req);
		अगर (rc)
			जाओ error;

		rc = ocs_hcu_hmac(hcu_dev, rctx->algo, tctx->key, tctx->key_len,
				  rctx->dma_list, req->result, rctx->dig_sz);

		/* Unmap data and मुक्त DMA list regardless of वापस code. */
		kmb_ocs_hcu_dma_cleanup(req, rctx);

		/* Process previous वापस code. */
		अगर (rc)
			जाओ error;

		जाओ करोne;
	पूर्ण

	/* Handle update request हाल. */
	अगर (!(rctx->flags & REQ_FINAL)) अणु
		/* Update should always have input data. */
		अगर (!kmb_get_total_data(rctx))
			वापस -EINVAL;

		/* Map input data पूर्णांकo the HCU DMA linked list. */
		rc = kmb_ocs_dma_prepare(req);
		अगर (rc)
			जाओ error;

		/* Do hashing step. */
		rc = ocs_hcu_hash_update(hcu_dev, &rctx->hash_ctx,
					 rctx->dma_list);

		/* Unmap data and मुक्त DMA list regardless of वापस code. */
		kmb_ocs_hcu_dma_cleanup(req, rctx);

		/* Process previous वापस code. */
		अगर (rc)
			जाओ error;

		/*
		 * Reset request buffer count (data in the buffer was just
		 * processed).
		 */
		rctx->buf_cnt = 0;
		/*
		 * Move reमुख्यing sg data पूर्णांकo the request buffer, so that it
		 * will be processed during the next request.
		 *
		 * NOTE: we have reमुख्यing data अगर kmb_get_total_data() was not
		 * a multiple of block size.
		 */
		rc = flush_sg_to_ocs_buffer(rctx);
		अगर (rc)
			जाओ error;

		जाओ करोne;
	पूर्ण

	/* If we get here, this is a final request. */

	/* If there is data to process, use finup. */
	अगर (kmb_get_total_data(rctx)) अणु
		/* Map input data पूर्णांकo the HCU DMA linked list. */
		rc = kmb_ocs_dma_prepare(req);
		अगर (rc)
			जाओ error;

		/* Do hashing step. */
		rc = ocs_hcu_hash_finup(hcu_dev, &rctx->hash_ctx,
					rctx->dma_list,
					req->result, rctx->dig_sz);
		/* Free DMA list regardless of वापस code. */
		kmb_ocs_hcu_dma_cleanup(req, rctx);

		/* Process previous वापस code. */
		अगर (rc)
			जाओ error;

	पूर्ण अन्यथा अणु  /* Otherwise (अगर we have no data), use final. */
		rc = ocs_hcu_hash_final(hcu_dev, &rctx->hash_ctx, req->result,
					rctx->dig_sz);
		अगर (rc)
			जाओ error;
	पूर्ण

	/*
	 * If we are finalizing a SW HMAC request, we just computed the result
	 * of: H(k ^ ipad || m).
	 *
	 * We now need to complete the HMAC calculation with the OPAD step,
	 * that is, we need to compute H(k ^ opad || digest), where digest is
	 * the digest we just obtained, i.e., H(k ^ ipad || m).
	 */
	अगर (rctx->flags & REQ_FLAGS_HMAC_SW) अणु
		/*
		 * Compute k ^ opad and store it in the request buffer (which
		 * is not used anymore at this poपूर्णांक).
		 * Note: key has been padded / hashed alपढ़ोy (so keylen ==
		 * blksz) .
		 */
		WARN_ON(tctx->key_len != rctx->blk_sz);
		क्रम (i = 0; i < rctx->blk_sz; i++)
			rctx->buffer[i] = tctx->key[i] ^ HMAC_OPAD_VALUE;
		/* Now append the digest to the rest of the buffer. */
		क्रम (i = 0; (i < rctx->dig_sz); i++)
			rctx->buffer[rctx->blk_sz + i] = req->result[i];

		/* Now hash the buffer to obtain the final HMAC. */
		rc = ocs_hcu_digest(hcu_dev, rctx->algo, rctx->buffer,
				    rctx->blk_sz + rctx->dig_sz, req->result,
				    rctx->dig_sz);
		अगर (rc)
			जाओ error;
	पूर्ण

	/* Perक्रमm secure clean-up. */
	kmb_ocs_hcu_secure_cleanup(req);
करोne:
	crypto_finalize_hash_request(hcu_dev->engine, req, 0);

	वापस 0;

error:
	kmb_ocs_hcu_secure_cleanup(req);
	वापस rc;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_init(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_dev *hcu_dev = kmb_ocs_hcu_find_dev(req);
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ocs_hcu_ctx *ctx = crypto_ahash_ctx(tfm);

	अगर (!hcu_dev)
		वापस -ENOENT;

	/* Initialize entire request context to zero. */
	स_रखो(rctx, 0, माप(*rctx));

	rctx->hcu_dev = hcu_dev;
	rctx->dig_sz = crypto_ahash_digestsize(tfm);

	चयन (rctx->dig_sz) अणु
#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_HCU_HMAC_SHA224
	हाल SHA224_DIGEST_SIZE:
		rctx->blk_sz = SHA224_BLOCK_SIZE;
		rctx->algo = OCS_HCU_ALGO_SHA224;
		अवरोध;
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_HCU_HMAC_SHA224 */
	हाल SHA256_DIGEST_SIZE:
		rctx->blk_sz = SHA256_BLOCK_SIZE;
		/*
		 * SHA256 and SM3 have the same digest size: use info from tfm
		 * context to find out which one we should use.
		 */
		rctx->algo = ctx->is_sm3_tfm ? OCS_HCU_ALGO_SM3 :
					       OCS_HCU_ALGO_SHA256;
		अवरोध;
	हाल SHA384_DIGEST_SIZE:
		rctx->blk_sz = SHA384_BLOCK_SIZE;
		rctx->algo = OCS_HCU_ALGO_SHA384;
		अवरोध;
	हाल SHA512_DIGEST_SIZE:
		rctx->blk_sz = SHA512_BLOCK_SIZE;
		rctx->algo = OCS_HCU_ALGO_SHA512;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Initialize पूर्णांकermediate data. */
	ocs_hcu_hash_init(&rctx->hash_ctx, rctx->algo);

	/* If this a HMAC request, set HMAC flag. */
	अगर (ctx->is_hmac_tfm)
		rctx->flags |= REQ_FLAGS_HMAC;

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_update(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);
	पूर्णांक rc;

	अगर (!req->nbytes)
		वापस 0;

	rctx->sg_data_total = req->nbytes;
	rctx->sg_data_offset = 0;
	rctx->sg = req->src;

	/*
	 * If we are करोing HMAC, then we must use SW-assisted HMAC, since HW
	 * HMAC करोes not support context चयनing (there it can only be used
	 * with finup() or digest()).
	 */
	अगर (rctx->flags & REQ_FLAGS_HMAC &&
	    !(rctx->flags & REQ_FLAGS_HMAC_SW)) अणु
		rctx->flags |= REQ_FLAGS_HMAC_SW;
		rc = prepare_ipad(req);
		अगर (rc)
			वापस rc;
	पूर्ण

	/*
	 * If reमुख्यing sg_data fits पूर्णांकo ctx buffer, just copy it there; we'll
	 * process it at the next update() or final().
	 */
	अगर (rctx->sg_data_total <= (माप(rctx->buffer) - rctx->buf_cnt))
		वापस flush_sg_to_ocs_buffer(rctx);

	वापस kmb_ocs_hcu_handle_queue(req);
पूर्ण

/* Common logic क्रम kmb_ocs_hcu_final() and kmb_ocs_hcu_finup(). */
अटल पूर्णांक kmb_ocs_hcu_fin_common(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ocs_hcu_ctx *ctx = crypto_ahash_ctx(tfm);
	पूर्णांक rc;

	rctx->flags |= REQ_FINAL;

	/*
	 * If this is a HMAC request and, so far, we didn't have to चयन to
	 * SW HMAC, check अगर we can use HW HMAC.
	 */
	अगर (rctx->flags & REQ_FLAGS_HMAC &&
	    !(rctx->flags & REQ_FLAGS_HMAC_SW)) अणु
		/*
		 * If we are here, it means we never processed any data so far,
		 * so we can use HW HMAC, but only अगर there is some data to
		 * process (since OCS HW MAC करोes not support zero-length
		 * messages) and the key length is supported by the hardware
		 * (OCS HCU HW only supports length <= 64); अगर HW HMAC cannot
		 * be used, fall back to SW-assisted HMAC.
		 */
		अगर (kmb_get_total_data(rctx) &&
		    ctx->key_len <= OCS_HCU_HW_KEY_LEN) अणु
			rctx->flags |= REQ_FLAGS_HMAC_HW;
		पूर्ण अन्यथा अणु
			rctx->flags |= REQ_FLAGS_HMAC_SW;
			rc = prepare_ipad(req);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस kmb_ocs_hcu_handle_queue(req);
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_final(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);

	rctx->sg_data_total = 0;
	rctx->sg_data_offset = 0;
	rctx->sg = शून्य;

	वापस kmb_ocs_hcu_fin_common(req);
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);

	rctx->sg_data_total = req->nbytes;
	rctx->sg_data_offset = 0;
	rctx->sg = req->src;

	वापस kmb_ocs_hcu_fin_common(req);
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक rc = 0;
	काष्ठा ocs_hcu_dev *hcu_dev = kmb_ocs_hcu_find_dev(req);

	अगर (!hcu_dev)
		वापस -ENOENT;

	rc = kmb_ocs_hcu_init(req);
	अगर (rc)
		वापस rc;

	rc = kmb_ocs_hcu_finup(req);

	वापस rc;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);

	/* Intermediate data is always stored and applied per request. */
	स_नकल(out, rctx, माप(*rctx));

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा ocs_hcu_rctx *rctx = ahash_request_ctx(req);

	/* Intermediate data is always stored and applied per request. */
	स_नकल(rctx, in, माप(*rctx));

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(tfm);
	काष्ठा ocs_hcu_ctx *ctx = crypto_ahash_ctx(tfm);
	माप_प्रकार blk_sz = crypto_ahash_blocksize(tfm);
	काष्ठा crypto_ahash *ahash_tfm;
	काष्ठा ahash_request *req;
	काष्ठा crypto_रुको रुको;
	काष्ठा scatterlist sg;
	स्थिर अक्षर *alg_name;
	पूर्णांक rc;

	/*
	 * Key length must be equal to block size:
	 * - If key is लघुer, we are करोne क्रम now (the key will be padded
	 *   later on); this is to maximize the use of HW HMAC (which works
	 *   only क्रम keys <= 64 bytes).
	 * - If key is दीर्घer, we hash it.
	 */
	अगर (keylen <= blk_sz) अणु
		स_नकल(ctx->key, key, keylen);
		ctx->key_len = keylen;
		वापस 0;
	पूर्ण

	चयन (digestsize) अणु
#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_HCU_HMAC_SHA224
	हाल SHA224_DIGEST_SIZE:
		alg_name = "sha224-keembay-ocs";
		अवरोध;
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_HCU_HMAC_SHA224 */
	हाल SHA256_DIGEST_SIZE:
		alg_name = ctx->is_sm3_tfm ? "sm3-keembay-ocs" :
					     "sha256-keembay-ocs";
		अवरोध;
	हाल SHA384_DIGEST_SIZE:
		alg_name = "sha384-keembay-ocs";
		अवरोध;
	हाल SHA512_DIGEST_SIZE:
		alg_name = "sha512-keembay-ocs";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ahash_tfm = crypto_alloc_ahash(alg_name, 0, 0);
	अगर (IS_ERR(ahash_tfm))
		वापस PTR_ERR(ahash_tfm);

	req = ahash_request_alloc(ahash_tfm, GFP_KERNEL);
	अगर (!req) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_ahash;
	पूर्ण

	crypto_init_रुको(&रुको);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &रुको);
	crypto_ahash_clear_flags(ahash_tfm, ~0);

	sg_init_one(&sg, key, keylen);
	ahash_request_set_crypt(req, &sg, ctx->key, keylen);

	rc = crypto_रुको_req(crypto_ahash_digest(req), &रुको);
	अगर (rc == 0)
		ctx->key_len = digestsize;

	ahash_request_मुक्त(req);
err_मुक्त_ahash:
	crypto_मुक्त_ahash(ahash_tfm);

	वापस rc;
पूर्ण

/* Set request size and initialize tfm context. */
अटल व्योम __cra_init(काष्ठा crypto_tfm *tfm, काष्ठा ocs_hcu_ctx *ctx)
अणु
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा ocs_hcu_rctx));

	/* Init context to 0. */
	memzero_explicit(ctx, माप(*ctx));
	/* Set engine ops. */
	ctx->engine_ctx.op.करो_one_request = kmb_ocs_hcu_करो_one_request;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_sha_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ocs_hcu_ctx *ctx = crypto_tfm_ctx(tfm);

	__cra_init(tfm, ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_sm3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ocs_hcu_ctx *ctx = crypto_tfm_ctx(tfm);

	__cra_init(tfm, ctx);

	ctx->is_sm3_tfm = true;

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_hmac_sm3_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ocs_hcu_ctx *ctx = crypto_tfm_ctx(tfm);

	__cra_init(tfm, ctx);

	ctx->is_sm3_tfm = true;
	ctx->is_hmac_tfm = true;

	वापस 0;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_hmac_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ocs_hcu_ctx *ctx = crypto_tfm_ctx(tfm);

	__cra_init(tfm, ctx);

	ctx->is_hmac_tfm = true;

	वापस 0;
पूर्ण

/* Function called when 'tfm' is de-initialized. */
अटल व्योम kmb_ocs_hcu_hmac_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ocs_hcu_ctx *ctx = crypto_tfm_ctx(tfm);

	/* Clear the key. */
	memzero_explicit(ctx->key, माप(ctx->key));
पूर्ण

अटल काष्ठा ahash_alg ocs_hcu_algs[] = अणु
#अगर_घोषित CONFIG_CRYPTO_DEV_KEEMBAY_OCS_HCU_HMAC_SHA224
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.halg = अणु
		.digestsize	= SHA224_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "sha224",
			.cra_driver_name	= "sha224-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA224_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_sha_cra_init,
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.setkey		= kmb_ocs_hcu_setkey,
	.halg = अणु
		.digestsize	= SHA224_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "hmac(sha224)",
			.cra_driver_name	= "hmac-sha224-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA224_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_hmac_cra_init,
			.cra_निकास		= kmb_ocs_hcu_hmac_cra_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_KEEMBAY_OCS_HCU_HMAC_SHA224 */
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.halg = अणु
		.digestsize	= SHA256_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "sha256",
			.cra_driver_name	= "sha256-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA256_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_sha_cra_init,
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.setkey		= kmb_ocs_hcu_setkey,
	.halg = अणु
		.digestsize	= SHA256_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "hmac(sha256)",
			.cra_driver_name	= "hmac-sha256-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA256_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_hmac_cra_init,
			.cra_निकास		= kmb_ocs_hcu_hmac_cra_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.halg = अणु
		.digestsize	= SM3_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "sm3",
			.cra_driver_name	= "sm3-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SM3_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_sm3_cra_init,
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.setkey		= kmb_ocs_hcu_setkey,
	.halg = अणु
		.digestsize	= SM3_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "hmac(sm3)",
			.cra_driver_name	= "hmac-sm3-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SM3_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_hmac_sm3_cra_init,
			.cra_निकास		= kmb_ocs_hcu_hmac_cra_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.halg = अणु
		.digestsize	= SHA384_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "sha384",
			.cra_driver_name	= "sha384-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA384_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_sha_cra_init,
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.setkey		= kmb_ocs_hcu_setkey,
	.halg = अणु
		.digestsize	= SHA384_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "hmac(sha384)",
			.cra_driver_name	= "hmac-sha384-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA384_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_hmac_cra_init,
			.cra_निकास		= kmb_ocs_hcu_hmac_cra_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.halg = अणु
		.digestsize	= SHA512_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "sha512",
			.cra_driver_name	= "sha512-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA512_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_sha_cra_init,
		पूर्ण
	पूर्ण
पूर्ण,
अणु
	.init		= kmb_ocs_hcu_init,
	.update		= kmb_ocs_hcu_update,
	.final		= kmb_ocs_hcu_final,
	.finup		= kmb_ocs_hcu_finup,
	.digest		= kmb_ocs_hcu_digest,
	.export		= kmb_ocs_hcu_export,
	.import		= kmb_ocs_hcu_import,
	.setkey		= kmb_ocs_hcu_setkey,
	.halg = अणु
		.digestsize	= SHA512_DIGEST_SIZE,
		.statesize	= माप(काष्ठा ocs_hcu_rctx),
		.base	= अणु
			.cra_name		= "hmac(sha512)",
			.cra_driver_name	= "hmac-sha512-keembay-ocs",
			.cra_priority		= 255,
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= SHA512_BLOCK_SIZE,
			.cra_ctxsize		= माप(काष्ठा ocs_hcu_ctx),
			.cra_alignmask		= 0,
			.cra_module		= THIS_MODULE,
			.cra_init		= kmb_ocs_hcu_hmac_cra_init,
			.cra_निकास		= kmb_ocs_hcu_hmac_cra_निकास,
		पूर्ण
	पूर्ण
पूर्ण,
पूर्ण;

/* Device tree driver match. */
अटल स्थिर काष्ठा of_device_id kmb_ocs_hcu_of_match[] = अणु
	अणु
		.compatible = "intel,keembay-ocs-hcu",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक kmb_ocs_hcu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ocs_hcu_dev *hcu_dev;
	पूर्णांक rc;

	hcu_dev = platक्रमm_get_drvdata(pdev);
	अगर (!hcu_dev)
		वापस -ENODEV;

	crypto_unरेजिस्टर_ahashes(ocs_hcu_algs, ARRAY_SIZE(ocs_hcu_algs));

	rc = crypto_engine_निकास(hcu_dev->engine);

	spin_lock_bh(&ocs_hcu.lock);
	list_del(&hcu_dev->list);
	spin_unlock_bh(&ocs_hcu.lock);

	वापस rc;
पूर्ण

अटल पूर्णांक kmb_ocs_hcu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ocs_hcu_dev *hcu_dev;
	काष्ठा resource *hcu_mem;
	पूर्णांक rc;

	hcu_dev = devm_kzalloc(dev, माप(*hcu_dev), GFP_KERNEL);
	अगर (!hcu_dev)
		वापस -ENOMEM;

	hcu_dev->dev = dev;

	platक्रमm_set_drvdata(pdev, hcu_dev);
	rc = dma_set_mask_and_coherent(&pdev->dev, OCS_HCU_DMA_BIT_MASK);
	अगर (rc)
		वापस rc;

	/* Get the memory address and remap. */
	hcu_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!hcu_mem) अणु
		dev_err(dev, "Could not retrieve io mem resource.\n");
		वापस -ENODEV;
	पूर्ण

	hcu_dev->io_base = devm_ioremap_resource(dev, hcu_mem);
	अगर (IS_ERR(hcu_dev->io_base))
		वापस PTR_ERR(hcu_dev->io_base);

	init_completion(&hcu_dev->irq_करोne);

	/* Get and request IRQ. */
	hcu_dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (hcu_dev->irq < 0)
		वापस hcu_dev->irq;

	rc = devm_request_thपढ़ोed_irq(&pdev->dev, hcu_dev->irq,
				       ocs_hcu_irq_handler, शून्य, 0,
				       "keembay-ocs-hcu", hcu_dev);
	अगर (rc < 0) अणु
		dev_err(dev, "Could not request IRQ.\n");
		वापस rc;
	पूर्ण

	INIT_LIST_HEAD(&hcu_dev->list);

	spin_lock_bh(&ocs_hcu.lock);
	list_add_tail(&hcu_dev->list, &ocs_hcu.dev_list);
	spin_unlock_bh(&ocs_hcu.lock);

	/* Initialize crypto engine */
	hcu_dev->engine = crypto_engine_alloc_init(dev, 1);
	अगर (!hcu_dev->engine) अणु
		rc = -ENOMEM;
		जाओ list_del;
	पूर्ण

	rc = crypto_engine_start(hcu_dev->engine);
	अगर (rc) अणु
		dev_err(dev, "Could not start engine.\n");
		जाओ cleanup;
	पूर्ण

	/* Security infraकाष्ठाure guarantees OCS घड़ी is enabled. */

	rc = crypto_रेजिस्टर_ahashes(ocs_hcu_algs, ARRAY_SIZE(ocs_hcu_algs));
	अगर (rc) अणु
		dev_err(dev, "Could not register algorithms.\n");
		जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	crypto_engine_निकास(hcu_dev->engine);
list_del:
	spin_lock_bh(&ocs_hcu.lock);
	list_del(&hcu_dev->list);
	spin_unlock_bh(&ocs_hcu.lock);

	वापस rc;
पूर्ण

/* The OCS driver is a platक्रमm device. */
अटल काष्ठा platक्रमm_driver kmb_ocs_hcu_driver = अणु
	.probe = kmb_ocs_hcu_probe,
	.हटाओ = kmb_ocs_hcu_हटाओ,
	.driver = अणु
			.name = DRV_NAME,
			.of_match_table = kmb_ocs_hcu_of_match,
		पूर्ण,
पूर्ण;

module_platक्रमm_driver(kmb_ocs_hcu_driver);

MODULE_LICENSE("GPL");
