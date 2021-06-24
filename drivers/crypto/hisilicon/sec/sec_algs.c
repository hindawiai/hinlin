<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2016-2017 HiSilicon Limited. */
#समावेश <linux/crypto.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/xts.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "sec_drv.h"

#घोषणा SEC_MAX_CIPHER_KEY		64
#घोषणा SEC_REQ_LIMIT SZ_32M

काष्ठा sec_c_alg_cfg अणु
	अचिन्हित c_alg		: 3;
	अचिन्हित c_mode		: 3;
	अचिन्हित key_len	: 2;
	अचिन्हित c_width	: 2;
पूर्ण;

अटल स्थिर काष्ठा sec_c_alg_cfg sec_c_alg_cfgs[] =  अणु
	[SEC_C_DES_ECB_64] = अणु
		.c_alg = SEC_C_ALG_DES,
		.c_mode = SEC_C_MODE_ECB,
		.key_len = SEC_KEY_LEN_DES,
	पूर्ण,
	[SEC_C_DES_CBC_64] = अणु
		.c_alg = SEC_C_ALG_DES,
		.c_mode = SEC_C_MODE_CBC,
		.key_len = SEC_KEY_LEN_DES,
	पूर्ण,
	[SEC_C_3DES_ECB_192_3KEY] = अणु
		.c_alg = SEC_C_ALG_3DES,
		.c_mode = SEC_C_MODE_ECB,
		.key_len = SEC_KEY_LEN_3DES_3_KEY,
	पूर्ण,
	[SEC_C_3DES_ECB_192_2KEY] = अणु
		.c_alg = SEC_C_ALG_3DES,
		.c_mode = SEC_C_MODE_ECB,
		.key_len = SEC_KEY_LEN_3DES_2_KEY,
	पूर्ण,
	[SEC_C_3DES_CBC_192_3KEY] = अणु
		.c_alg = SEC_C_ALG_3DES,
		.c_mode = SEC_C_MODE_CBC,
		.key_len = SEC_KEY_LEN_3DES_3_KEY,
	पूर्ण,
	[SEC_C_3DES_CBC_192_2KEY] = अणु
		.c_alg = SEC_C_ALG_3DES,
		.c_mode = SEC_C_MODE_CBC,
		.key_len = SEC_KEY_LEN_3DES_2_KEY,
	पूर्ण,
	[SEC_C_AES_ECB_128] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_ECB,
		.key_len = SEC_KEY_LEN_AES_128,
	पूर्ण,
	[SEC_C_AES_ECB_192] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_ECB,
		.key_len = SEC_KEY_LEN_AES_192,
	पूर्ण,
	[SEC_C_AES_ECB_256] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_ECB,
		.key_len = SEC_KEY_LEN_AES_256,
	पूर्ण,
	[SEC_C_AES_CBC_128] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_CBC,
		.key_len = SEC_KEY_LEN_AES_128,
	पूर्ण,
	[SEC_C_AES_CBC_192] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_CBC,
		.key_len = SEC_KEY_LEN_AES_192,
	पूर्ण,
	[SEC_C_AES_CBC_256] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_CBC,
		.key_len = SEC_KEY_LEN_AES_256,
	पूर्ण,
	[SEC_C_AES_CTR_128] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_CTR,
		.key_len = SEC_KEY_LEN_AES_128,
	पूर्ण,
	[SEC_C_AES_CTR_192] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_CTR,
		.key_len = SEC_KEY_LEN_AES_192,
	पूर्ण,
	[SEC_C_AES_CTR_256] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_CTR,
		.key_len = SEC_KEY_LEN_AES_256,
	पूर्ण,
	[SEC_C_AES_XTS_128] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_XTS,
		.key_len = SEC_KEY_LEN_AES_128,
	पूर्ण,
	[SEC_C_AES_XTS_256] = अणु
		.c_alg = SEC_C_ALG_AES,
		.c_mode = SEC_C_MODE_XTS,
		.key_len = SEC_KEY_LEN_AES_256,
	पूर्ण,
	[SEC_C_शून्य] = अणु
	पूर्ण,
पूर्ण;

/*
 * Mutex used to ensure safe operation of reference count of
 * alg providers
 */
अटल DEFINE_MUTEX(algs_lock);
अटल अचिन्हित पूर्णांक active_devs;

अटल व्योम sec_alg_skcipher_init_ढाँचा(काष्ठा sec_alg_tfm_ctx *ctx,
					   काष्ठा sec_bd_info *req,
					   क्रमागत sec_cipher_alg alg)
अणु
	स्थिर काष्ठा sec_c_alg_cfg *cfg = &sec_c_alg_cfgs[alg];

	स_रखो(req, 0, माप(*req));
	req->w0 |= cfg->c_mode << SEC_BD_W0_C_MODE_S;
	req->w1 |= cfg->c_alg << SEC_BD_W1_C_ALG_S;
	req->w3 |= cfg->key_len << SEC_BD_W3_C_KEY_LEN_S;
	req->w0 |= cfg->c_width << SEC_BD_W0_C_WIDTH_S;

	req->cipher_key_addr_lo = lower_32_bits(ctx->pkey);
	req->cipher_key_addr_hi = upper_32_bits(ctx->pkey);
पूर्ण

अटल व्योम sec_alg_skcipher_init_context(काष्ठा crypto_skcipher *atfm,
					  स्थिर u8 *key,
					  अचिन्हित पूर्णांक keylen,
					  क्रमागत sec_cipher_alg alg)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(atfm);
	काष्ठा sec_alg_tfm_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->cipher_alg = alg;
	स_नकल(ctx->key, key, keylen);
	sec_alg_skcipher_init_ढाँचा(ctx, &ctx->req_ढाँचा,
				       ctx->cipher_alg);
पूर्ण

अटल व्योम sec_मुक्त_hw_sgl(काष्ठा sec_hw_sgl *hw_sgl,
			    dma_addr_t psec_sgl, काष्ठा sec_dev_info *info)
अणु
	काष्ठा sec_hw_sgl *sgl_current, *sgl_next;
	dma_addr_t sgl_next_dma;

	sgl_current = hw_sgl;
	जबतक (sgl_current) अणु
		sgl_next = sgl_current->next;
		sgl_next_dma = sgl_current->next_sgl;

		dma_pool_मुक्त(info->hw_sgl_pool, sgl_current, psec_sgl);

		sgl_current = sgl_next;
		psec_sgl = sgl_next_dma;
	पूर्ण
पूर्ण

अटल पूर्णांक sec_alloc_and_fill_hw_sgl(काष्ठा sec_hw_sgl **sec_sgl,
				     dma_addr_t *psec_sgl,
				     काष्ठा scatterlist *sgl,
				     पूर्णांक count,
				     काष्ठा sec_dev_info *info,
				     gfp_t gfp)
अणु
	काष्ठा sec_hw_sgl *sgl_current = शून्य;
	काष्ठा sec_hw_sgl *sgl_next;
	dma_addr_t sgl_next_dma;
	काष्ठा scatterlist *sg;
	पूर्णांक ret, sge_index, i;

	अगर (!count)
		वापस -EINVAL;

	क्रम_each_sg(sgl, sg, count, i) अणु
		sge_index = i % SEC_MAX_SGE_NUM;
		अगर (sge_index == 0) अणु
			sgl_next = dma_pool_zalloc(info->hw_sgl_pool,
						   gfp, &sgl_next_dma);
			अगर (!sgl_next) अणु
				ret = -ENOMEM;
				जाओ err_मुक्त_hw_sgls;
			पूर्ण

			अगर (!sgl_current) अणु /* First one */
				*psec_sgl = sgl_next_dma;
				*sec_sgl = sgl_next;
			पूर्ण अन्यथा अणु /* Chained */
				sgl_current->entry_sum_in_sgl = SEC_MAX_SGE_NUM;
				sgl_current->next_sgl = sgl_next_dma;
				sgl_current->next = sgl_next;
			पूर्ण
			sgl_current = sgl_next;
		पूर्ण
		sgl_current->sge_entries[sge_index].buf = sg_dma_address(sg);
		sgl_current->sge_entries[sge_index].len = sg_dma_len(sg);
		sgl_current->data_bytes_in_sgl += sg_dma_len(sg);
	पूर्ण
	sgl_current->entry_sum_in_sgl = count % SEC_MAX_SGE_NUM;
	sgl_current->next_sgl = 0;
	(*sec_sgl)->entry_sum_in_chain = count;

	वापस 0;

err_मुक्त_hw_sgls:
	sec_मुक्त_hw_sgl(*sec_sgl, *psec_sgl, info);
	*psec_sgl = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey(काष्ठा crypto_skcipher *tfm,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen,
				   क्रमागत sec_cipher_alg alg)
अणु
	काष्ठा sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा device *dev = ctx->queue->dev_info->dev;

	mutex_lock(&ctx->lock);
	अगर (ctx->key) अणु
		/* rekeying */
		स_रखो(ctx->key, 0, SEC_MAX_CIPHER_KEY);
	पूर्ण अन्यथा अणु
		/* new key */
		ctx->key = dma_alloc_coherent(dev, SEC_MAX_CIPHER_KEY,
					      &ctx->pkey, GFP_KERNEL);
		अगर (!ctx->key) अणु
			mutex_unlock(&ctx->lock);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	mutex_unlock(&ctx->lock);
	sec_alg_skcipher_init_context(tfm, key, keylen, alg);

	वापस 0;
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey_aes_ecb(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	क्रमागत sec_cipher_alg alg;

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		alg = SEC_C_AES_ECB_128;
		अवरोध;
	हाल AES_KEYSIZE_192:
		alg = SEC_C_AES_ECB_192;
		अवरोध;
	हाल AES_KEYSIZE_256:
		alg = SEC_C_AES_ECB_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sec_alg_skcipher_setkey(tfm, key, keylen, alg);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey_aes_cbc(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	क्रमागत sec_cipher_alg alg;

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		alg = SEC_C_AES_CBC_128;
		अवरोध;
	हाल AES_KEYSIZE_192:
		alg = SEC_C_AES_CBC_192;
		अवरोध;
	हाल AES_KEYSIZE_256:
		alg = SEC_C_AES_CBC_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sec_alg_skcipher_setkey(tfm, key, keylen, alg);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey_aes_ctr(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	क्रमागत sec_cipher_alg alg;

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		alg = SEC_C_AES_CTR_128;
		अवरोध;
	हाल AES_KEYSIZE_192:
		alg = SEC_C_AES_CTR_192;
		अवरोध;
	हाल AES_KEYSIZE_256:
		alg = SEC_C_AES_CTR_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sec_alg_skcipher_setkey(tfm, key, keylen, alg);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey_aes_xts(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	क्रमागत sec_cipher_alg alg;
	पूर्णांक ret;

	ret = xts_verअगरy_key(tfm, key, keylen);
	अगर (ret)
		वापस ret;

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128 * 2:
		alg = SEC_C_AES_XTS_128;
		अवरोध;
	हाल AES_KEYSIZE_256 * 2:
		alg = SEC_C_AES_XTS_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sec_alg_skcipher_setkey(tfm, key, keylen, alg);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey_des_ecb(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des_key(tfm, key) ?:
	       sec_alg_skcipher_setkey(tfm, key, keylen, SEC_C_DES_ECB_64);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey_des_cbc(काष्ठा crypto_skcipher *tfm,
					   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des_key(tfm, key) ?:
	       sec_alg_skcipher_setkey(tfm, key, keylen, SEC_C_DES_CBC_64);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey_3des_ecb(काष्ठा crypto_skcipher *tfm,
					    स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des3_key(tfm, key) ?:
	       sec_alg_skcipher_setkey(tfm, key, keylen,
				       SEC_C_3DES_ECB_192_3KEY);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_setkey_3des_cbc(काष्ठा crypto_skcipher *tfm,
					    स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des3_key(tfm, key) ?:
	       sec_alg_skcipher_setkey(tfm, key, keylen,
				       SEC_C_3DES_CBC_192_3KEY);
पूर्ण

अटल व्योम sec_alg_मुक्त_el(काष्ठा sec_request_el *el,
			    काष्ठा sec_dev_info *info)
अणु
	sec_मुक्त_hw_sgl(el->out, el->dma_out, info);
	sec_मुक्त_hw_sgl(el->in, el->dma_in, info);
	kमुक्त(el->sgl_in);
	kमुक्त(el->sgl_out);
	kमुक्त(el);
पूर्ण

/* queuelock must be held */
अटल पूर्णांक sec_send_request(काष्ठा sec_request *sec_req, काष्ठा sec_queue *queue)
अणु
	काष्ठा sec_request_el *el, *temp;
	पूर्णांक ret = 0;

	mutex_lock(&sec_req->lock);
	list_क्रम_each_entry_safe(el, temp, &sec_req->elements, head) अणु
		/*
		 * Add to hardware queue only under following circumstances
		 * 1) Software and hardware queue empty so no chain dependencies
		 * 2) No dependencies as new IV - (check software queue empty
		 *    to मुख्यtain order)
		 * 3) No dependencies because the mode करोes no chaining.
		 *
		 * In other हालs first insert onto the software queue which
		 * is then emptied as requests complete
		 */
		अगर (!queue->havesoftqueue ||
		    (kfअगरo_is_empty(&queue->softqueue) &&
		     sec_queue_empty(queue))) अणु
			ret = sec_queue_send(queue, &el->req, sec_req);
			अगर (ret == -EAGAIN) अणु
				/* Wait unti we can send then try again */
				/* DEAD अगर here - should not happen */
				ret = -EBUSY;
				जाओ err_unlock;
			पूर्ण
		पूर्ण अन्यथा अणु
			kfअगरo_put(&queue->softqueue, el);
		पूर्ण
	पूर्ण
err_unlock:
	mutex_unlock(&sec_req->lock);

	वापस ret;
पूर्ण

अटल व्योम sec_skcipher_alg_callback(काष्ठा sec_bd_info *sec_resp,
				      काष्ठा crypto_async_request *req_base)
अणु
	काष्ठा skcipher_request *skreq = container_of(req_base,
						      काष्ठा skcipher_request,
						      base);
	काष्ठा sec_request *sec_req = skcipher_request_ctx(skreq);
	काष्ठा sec_request *backlog_req;
	काष्ठा sec_request_el *sec_req_el, *nextrequest;
	काष्ठा sec_alg_tfm_ctx *ctx = sec_req->tfm_ctx;
	काष्ठा crypto_skcipher *atfm = crypto_skcipher_reqtfm(skreq);
	काष्ठा device *dev = ctx->queue->dev_info->dev;
	पूर्णांक icv_or_skey_en, ret;
	bool करोne;

	sec_req_el = list_first_entry(&sec_req->elements, काष्ठा sec_request_el,
				      head);
	icv_or_skey_en = (sec_resp->w0 & SEC_BD_W0_ICV_OR_SKEY_EN_M) >>
		SEC_BD_W0_ICV_OR_SKEY_EN_S;
	अगर (sec_resp->w1 & SEC_BD_W1_BD_INVALID || icv_or_skey_en == 3) अणु
		dev_err(dev, "Got an invalid answer %lu %d\n",
			sec_resp->w1 & SEC_BD_W1_BD_INVALID,
			icv_or_skey_en);
		sec_req->err = -EINVAL;
		/*
		 * We need to muddle on to aव्योम getting stuck with elements
		 * on the queue. Error will be reported so requester so
		 * it should be able to handle appropriately.
		 */
	पूर्ण

	mutex_lock(&ctx->queue->queuelock);
	/* Put the IV in place क्रम chained हालs */
	चयन (ctx->cipher_alg) अणु
	हाल SEC_C_AES_CBC_128:
	हाल SEC_C_AES_CBC_192:
	हाल SEC_C_AES_CBC_256:
		अगर (sec_req_el->req.w0 & SEC_BD_W0_DE)
			sg_pcopy_to_buffer(sec_req_el->sgl_out,
					   sg_nents(sec_req_el->sgl_out),
					   skreq->iv,
					   crypto_skcipher_ivsize(atfm),
					   sec_req_el->el_length -
					   crypto_skcipher_ivsize(atfm));
		अन्यथा
			sg_pcopy_to_buffer(sec_req_el->sgl_in,
					   sg_nents(sec_req_el->sgl_in),
					   skreq->iv,
					   crypto_skcipher_ivsize(atfm),
					   sec_req_el->el_length -
					   crypto_skcipher_ivsize(atfm));
		/* No need to sync to the device as coherent DMA */
		अवरोध;
	हाल SEC_C_AES_CTR_128:
	हाल SEC_C_AES_CTR_192:
	हाल SEC_C_AES_CTR_256:
		crypto_inc(skreq->iv, 16);
		अवरोध;
	शेष:
		/* Do not update */
		अवरोध;
	पूर्ण

	अगर (ctx->queue->havesoftqueue &&
	    !kfअगरo_is_empty(&ctx->queue->softqueue) &&
	    sec_queue_empty(ctx->queue)) अणु
		ret = kfअगरo_get(&ctx->queue->softqueue, &nextrequest);
		अगर (ret <= 0)
			dev_err(dev,
				"Error getting next element from kfifo %d\n",
				ret);
		अन्यथा
			/* We know there is space so this cannot fail */
			sec_queue_send(ctx->queue, &nextrequest->req,
				       nextrequest->sec_req);
	पूर्ण अन्यथा अगर (!list_empty(&ctx->backlog)) अणु
		/* Need to verअगरy there is room first */
		backlog_req = list_first_entry(&ctx->backlog,
					       typeof(*backlog_req),
					       backlog_head);
		अगर (sec_queue_can_enqueue(ctx->queue,
		    backlog_req->num_elements) ||
		    (ctx->queue->havesoftqueue &&
		     kfअगरo_avail(&ctx->queue->softqueue) >
		     backlog_req->num_elements)) अणु
			sec_send_request(backlog_req, ctx->queue);
			backlog_req->req_base->complete(backlog_req->req_base,
							-EINPROGRESS);
			list_del(&backlog_req->backlog_head);
		पूर्ण
	पूर्ण
	mutex_unlock(&ctx->queue->queuelock);

	mutex_lock(&sec_req->lock);
	list_del(&sec_req_el->head);
	mutex_unlock(&sec_req->lock);
	sec_alg_मुक्त_el(sec_req_el, ctx->queue->dev_info);

	/*
	 * Request is करोne.
	 * The dance is needed as the lock is मुक्तd in the completion
	 */
	mutex_lock(&sec_req->lock);
	करोne = list_empty(&sec_req->elements);
	mutex_unlock(&sec_req->lock);
	अगर (करोne) अणु
		अगर (crypto_skcipher_ivsize(atfm)) अणु
			dma_unmap_single(dev, sec_req->dma_iv,
					 crypto_skcipher_ivsize(atfm),
					 DMA_TO_DEVICE);
		पूर्ण
		dma_unmap_sg(dev, skreq->src, sec_req->len_in,
			     DMA_BIसूचीECTIONAL);
		अगर (skreq->src != skreq->dst)
			dma_unmap_sg(dev, skreq->dst, sec_req->len_out,
				     DMA_BIसूचीECTIONAL);
		skreq->base.complete(&skreq->base, sec_req->err);
	पूर्ण
पूर्ण

व्योम sec_alg_callback(काष्ठा sec_bd_info *resp, व्योम *shaकरोw)
अणु
	काष्ठा sec_request *sec_req = shaकरोw;

	sec_req->cb(resp, sec_req->req_base);
पूर्ण

अटल पूर्णांक sec_alg_alloc_and_calc_split_sizes(पूर्णांक length, माप_प्रकार **split_sizes,
					      पूर्णांक *steps, gfp_t gfp)
अणु
	माप_प्रकार *sizes;
	पूर्णांक i;

	/* Split पूर्णांकo suitable sized blocks */
	*steps = roundup(length, SEC_REQ_LIMIT) / SEC_REQ_LIMIT;
	sizes = kसुस्मृति(*steps, माप(*sizes), gfp);
	अगर (!sizes)
		वापस -ENOMEM;

	क्रम (i = 0; i < *steps - 1; i++)
		sizes[i] = SEC_REQ_LIMIT;
	sizes[*steps - 1] = length - SEC_REQ_LIMIT * (*steps - 1);
	*split_sizes = sizes;

	वापस 0;
पूर्ण

अटल पूर्णांक sec_map_and_split_sg(काष्ठा scatterlist *sgl, माप_प्रकार *split_sizes,
				पूर्णांक steps, काष्ठा scatterlist ***splits,
				पूर्णांक **splits_nents,
				पूर्णांक sgl_len_in,
				काष्ठा device *dev, gfp_t gfp)
अणु
	पूर्णांक ret, count;

	count = dma_map_sg(dev, sgl, sgl_len_in, DMA_BIसूचीECTIONAL);
	अगर (!count)
		वापस -EINVAL;

	*splits = kसुस्मृति(steps, माप(काष्ठा scatterlist *), gfp);
	अगर (!*splits) अणु
		ret = -ENOMEM;
		जाओ err_unmap_sg;
	पूर्ण
	*splits_nents = kसुस्मृति(steps, माप(पूर्णांक), gfp);
	अगर (!*splits_nents) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_splits;
	पूर्ण

	/* output the scatter list beक्रमe and after this */
	ret = sg_split(sgl, count, 0, steps, split_sizes,
		       *splits, *splits_nents, gfp);
	अगर (ret) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_splits_nents;
	पूर्ण

	वापस 0;

err_मुक्त_splits_nents:
	kमुक्त(*splits_nents);
err_मुक्त_splits:
	kमुक्त(*splits);
err_unmap_sg:
	dma_unmap_sg(dev, sgl, sgl_len_in, DMA_BIसूचीECTIONAL);

	वापस ret;
पूर्ण

/*
 * Reverses the sec_map_and_split_sg call क्रम messages not yet added to
 * the queues.
 */
अटल व्योम sec_unmap_sg_on_err(काष्ठा scatterlist *sgl, पूर्णांक steps,
				काष्ठा scatterlist **splits, पूर्णांक *splits_nents,
				पूर्णांक sgl_len_in, काष्ठा device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < steps; i++)
		kमुक्त(splits[i]);
	kमुक्त(splits_nents);
	kमुक्त(splits);

	dma_unmap_sg(dev, sgl, sgl_len_in, DMA_BIसूचीECTIONAL);
पूर्ण

अटल काष्ठा sec_request_el
*sec_alg_alloc_and_fill_el(काष्ठा sec_bd_info *ढाँचा, पूर्णांक encrypt,
			   पूर्णांक el_size, bool dअगरferent_dest,
			   काष्ठा scatterlist *sgl_in, पूर्णांक n_ents_in,
			   काष्ठा scatterlist *sgl_out, पूर्णांक n_ents_out,
			   काष्ठा sec_dev_info *info, gfp_t gfp)
अणु
	काष्ठा sec_request_el *el;
	काष्ठा sec_bd_info *req;
	पूर्णांक ret;

	el = kzalloc(माप(*el), gfp);
	अगर (!el)
		वापस ERR_PTR(-ENOMEM);
	el->el_length = el_size;
	req = &el->req;
	स_नकल(req, ढाँचा, माप(*req));

	req->w0 &= ~SEC_BD_W0_CIPHER_M;
	अगर (encrypt)
		req->w0 |= SEC_CIPHER_ENCRYPT << SEC_BD_W0_CIPHER_S;
	अन्यथा
		req->w0 |= SEC_CIPHER_DECRYPT << SEC_BD_W0_CIPHER_S;

	req->w0 &= ~SEC_BD_W0_C_GRAN_SIZE_19_16_M;
	req->w0 |= ((el_size >> 16) << SEC_BD_W0_C_GRAN_SIZE_19_16_S) &
		SEC_BD_W0_C_GRAN_SIZE_19_16_M;

	req->w0 &= ~SEC_BD_W0_C_GRAN_SIZE_21_20_M;
	req->w0 |= ((el_size >> 20) << SEC_BD_W0_C_GRAN_SIZE_21_20_S) &
		SEC_BD_W0_C_GRAN_SIZE_21_20_M;

	/* Writing whole u32 so no need to take care of masking */
	req->w2 = ((1 << SEC_BD_W2_GRAN_NUM_S) & SEC_BD_W2_GRAN_NUM_M) |
		((el_size << SEC_BD_W2_C_GRAN_SIZE_15_0_S) &
		 SEC_BD_W2_C_GRAN_SIZE_15_0_M);

	req->w3 &= ~SEC_BD_W3_CIPHER_LEN_OFFSET_M;
	req->w1 |= SEC_BD_W1_ADDR_TYPE;

	el->sgl_in = sgl_in;

	ret = sec_alloc_and_fill_hw_sgl(&el->in, &el->dma_in, el->sgl_in,
					n_ents_in, info, gfp);
	अगर (ret)
		जाओ err_मुक्त_el;

	req->data_addr_lo = lower_32_bits(el->dma_in);
	req->data_addr_hi = upper_32_bits(el->dma_in);

	अगर (dअगरferent_dest) अणु
		el->sgl_out = sgl_out;
		ret = sec_alloc_and_fill_hw_sgl(&el->out, &el->dma_out,
						el->sgl_out,
						n_ents_out, info, gfp);
		अगर (ret)
			जाओ err_मुक्त_hw_sgl_in;

		req->w0 |= SEC_BD_W0_DE;
		req->cipher_destin_addr_lo = lower_32_bits(el->dma_out);
		req->cipher_destin_addr_hi = upper_32_bits(el->dma_out);

	पूर्ण अन्यथा अणु
		req->w0 &= ~SEC_BD_W0_DE;
		req->cipher_destin_addr_lo = lower_32_bits(el->dma_in);
		req->cipher_destin_addr_hi = upper_32_bits(el->dma_in);
	पूर्ण

	वापस el;

err_मुक्त_hw_sgl_in:
	sec_मुक्त_hw_sgl(el->in, el->dma_in, info);
err_मुक्त_el:
	kमुक्त(el);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_crypto(काष्ठा skcipher_request *skreq,
				   bool encrypt)
अणु
	काष्ठा crypto_skcipher *atfm = crypto_skcipher_reqtfm(skreq);
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(atfm);
	काष्ठा sec_alg_tfm_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा sec_queue *queue = ctx->queue;
	काष्ठा sec_request *sec_req = skcipher_request_ctx(skreq);
	काष्ठा sec_dev_info *info = queue->dev_info;
	पूर्णांक i, ret, steps;
	माप_प्रकार *split_sizes;
	काष्ठा scatterlist **splits_in;
	काष्ठा scatterlist **splits_out = शून्य;
	पूर्णांक *splits_in_nents;
	पूर्णांक *splits_out_nents = शून्य;
	काष्ठा sec_request_el *el, *temp;
	bool split = skreq->src != skreq->dst;
	gfp_t gfp = skreq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL : GFP_ATOMIC;

	mutex_init(&sec_req->lock);
	sec_req->req_base = &skreq->base;
	sec_req->err = 0;
	/* SGL mapping out here to allow us to अवरोध it up as necessary */
	sec_req->len_in = sg_nents(skreq->src);

	ret = sec_alg_alloc_and_calc_split_sizes(skreq->cryptlen, &split_sizes,
						 &steps, gfp);
	अगर (ret)
		वापस ret;
	sec_req->num_elements = steps;
	ret = sec_map_and_split_sg(skreq->src, split_sizes, steps, &splits_in,
				   &splits_in_nents, sec_req->len_in,
				   info->dev, gfp);
	अगर (ret)
		जाओ err_मुक्त_split_sizes;

	अगर (split) अणु
		sec_req->len_out = sg_nents(skreq->dst);
		ret = sec_map_and_split_sg(skreq->dst, split_sizes, steps,
					   &splits_out, &splits_out_nents,
					   sec_req->len_out, info->dev, gfp);
		अगर (ret)
			जाओ err_unmap_in_sg;
	पूर्ण
	/* Shared info stored in seq_req - applies to all BDs */
	sec_req->tfm_ctx = ctx;
	sec_req->cb = sec_skcipher_alg_callback;
	INIT_LIST_HEAD(&sec_req->elements);

	/*
	 * Future optimization.
	 * In the chaining हाल we can't use a dma pool bounce buffer
	 * but in the हाल where we know there is no chaining we can
	 */
	अगर (crypto_skcipher_ivsize(atfm)) अणु
		sec_req->dma_iv = dma_map_single(info->dev, skreq->iv,
						 crypto_skcipher_ivsize(atfm),
						 DMA_TO_DEVICE);
		अगर (dma_mapping_error(info->dev, sec_req->dma_iv)) अणु
			ret = -ENOMEM;
			जाओ err_unmap_out_sg;
		पूर्ण
	पूर्ण

	/* Set them all up then queue - cleaner error handling. */
	क्रम (i = 0; i < steps; i++) अणु
		el = sec_alg_alloc_and_fill_el(&ctx->req_ढाँचा,
					       encrypt ? 1 : 0,
					       split_sizes[i],
					       skreq->src != skreq->dst,
					       splits_in[i], splits_in_nents[i],
					       split ? splits_out[i] : शून्य,
					       split ? splits_out_nents[i] : 0,
					       info, gfp);
		अगर (IS_ERR(el)) अणु
			ret = PTR_ERR(el);
			जाओ err_मुक्त_elements;
		पूर्ण
		el->req.cipher_iv_addr_lo = lower_32_bits(sec_req->dma_iv);
		el->req.cipher_iv_addr_hi = upper_32_bits(sec_req->dma_iv);
		el->sec_req = sec_req;
		list_add_tail(&el->head, &sec_req->elements);
	पूर्ण

	/*
	 * Only attempt to queue अगर the whole lot can fit in the queue -
	 * we can't successfully cleanup after a partial queing so this
	 * must succeed or fail atomically.
	 *
	 * Big hammer test of both software and hardware queues - could be
	 * more refined but this is unlikely to happen so no need.
	 */

	/* Grab a big lock क्रम a दीर्घ समय to aव्योम concurrency issues */
	mutex_lock(&queue->queuelock);

	/*
	 * Can go on to queue अगर we have space in either:
	 * 1) The hardware queue and no software queue
	 * 2) The software queue
	 * AND there is nothing in the backlog.  If there is backlog we
	 * have to only queue to the backlog queue and वापस busy.
	 */
	अगर ((!sec_queue_can_enqueue(queue, steps) &&
	     (!queue->havesoftqueue ||
	      kfअगरo_avail(&queue->softqueue) > steps)) ||
	    !list_empty(&ctx->backlog)) अणु
		ret = -EBUSY;
		अगर ((skreq->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)) अणु
			list_add_tail(&sec_req->backlog_head, &ctx->backlog);
			mutex_unlock(&queue->queuelock);
			जाओ out;
		पूर्ण

		mutex_unlock(&queue->queuelock);
		जाओ err_मुक्त_elements;
	पूर्ण
	ret = sec_send_request(sec_req, queue);
	mutex_unlock(&queue->queuelock);
	अगर (ret)
		जाओ err_मुक्त_elements;

	ret = -EINPROGRESS;
out:
	/* Cleanup - all elements in poपूर्णांकer arrays have been copied */
	kमुक्त(splits_in_nents);
	kमुक्त(splits_in);
	kमुक्त(splits_out_nents);
	kमुक्त(splits_out);
	kमुक्त(split_sizes);
	वापस ret;

err_मुक्त_elements:
	list_क्रम_each_entry_safe(el, temp, &sec_req->elements, head) अणु
		list_del(&el->head);
		sec_alg_मुक्त_el(el, info);
	पूर्ण
	अगर (crypto_skcipher_ivsize(atfm))
		dma_unmap_single(info->dev, sec_req->dma_iv,
				 crypto_skcipher_ivsize(atfm),
				 DMA_BIसूचीECTIONAL);
err_unmap_out_sg:
	अगर (split)
		sec_unmap_sg_on_err(skreq->dst, steps, splits_out,
				    splits_out_nents, sec_req->len_out,
				    info->dev);
err_unmap_in_sg:
	sec_unmap_sg_on_err(skreq->src, steps, splits_in, splits_in_nents,
			    sec_req->len_in, info->dev);
err_मुक्त_split_sizes:
	kमुक्त(split_sizes);

	वापस ret;
पूर्ण

अटल पूर्णांक sec_alg_skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sec_alg_skcipher_crypto(req, true);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sec_alg_skcipher_crypto(req, false);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);

	mutex_init(&ctx->lock);
	INIT_LIST_HEAD(&ctx->backlog);
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा sec_request));

	ctx->queue = sec_queue_alloc_start_safe();
	अगर (IS_ERR(ctx->queue))
		वापस PTR_ERR(ctx->queue);

	mutex_init(&ctx->queue->queuelock);
	ctx->queue->havesoftqueue = false;

	वापस 0;
पूर्ण

अटल व्योम sec_alg_skcipher_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा device *dev = ctx->queue->dev_info->dev;

	अगर (ctx->key) अणु
		memzero_explicit(ctx->key, SEC_MAX_CIPHER_KEY);
		dma_मुक्त_coherent(dev, SEC_MAX_CIPHER_KEY, ctx->key,
				  ctx->pkey);
	पूर्ण
	sec_queue_stop_release(ctx->queue);
पूर्ण

अटल पूर्णांक sec_alg_skcipher_init_with_queue(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक ret;

	ret = sec_alg_skcipher_init(tfm);
	अगर (ret)
		वापस ret;

	INIT_KFIFO(ctx->queue->softqueue);
	ret = kfअगरo_alloc(&ctx->queue->softqueue, 512, GFP_KERNEL);
	अगर (ret) अणु
		sec_alg_skcipher_निकास(tfm);
		वापस ret;
	पूर्ण
	ctx->queue->havesoftqueue = true;

	वापस 0;
पूर्ण

अटल व्योम sec_alg_skcipher_निकास_with_queue(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);

	kfअगरo_मुक्त(&ctx->queue->softqueue);
	sec_alg_skcipher_निकास(tfm);
पूर्ण

अटल काष्ठा skcipher_alg sec_algs[] = अणु
	अणु
		.base = अणु
			.cra_name = "ecb(aes)",
			.cra_driver_name = "hisi_sec_aes_ecb",
			.cra_priority = 4001,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा sec_alg_tfm_ctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = sec_alg_skcipher_init,
		.निकास = sec_alg_skcipher_निकास,
		.setkey = sec_alg_skcipher_setkey_aes_ecb,
		.decrypt = sec_alg_skcipher_decrypt,
		.encrypt = sec_alg_skcipher_encrypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = 0,
	पूर्ण, अणु
		.base = अणु
			.cra_name = "cbc(aes)",
			.cra_driver_name = "hisi_sec_aes_cbc",
			.cra_priority = 4001,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा sec_alg_tfm_ctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = sec_alg_skcipher_init_with_queue,
		.निकास = sec_alg_skcipher_निकास_with_queue,
		.setkey = sec_alg_skcipher_setkey_aes_cbc,
		.decrypt = sec_alg_skcipher_decrypt,
		.encrypt = sec_alg_skcipher_encrypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
	पूर्ण, अणु
		.base = अणु
			.cra_name = "ctr(aes)",
			.cra_driver_name = "hisi_sec_aes_ctr",
			.cra_priority = 4001,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा sec_alg_tfm_ctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = sec_alg_skcipher_init_with_queue,
		.निकास = sec_alg_skcipher_निकास_with_queue,
		.setkey = sec_alg_skcipher_setkey_aes_ctr,
		.decrypt = sec_alg_skcipher_decrypt,
		.encrypt = sec_alg_skcipher_encrypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
	पूर्ण, अणु
		.base = अणु
			.cra_name = "xts(aes)",
			.cra_driver_name = "hisi_sec_aes_xts",
			.cra_priority = 4001,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा sec_alg_tfm_ctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = sec_alg_skcipher_init,
		.निकास = sec_alg_skcipher_निकास,
		.setkey = sec_alg_skcipher_setkey_aes_xts,
		.decrypt = sec_alg_skcipher_decrypt,
		.encrypt = sec_alg_skcipher_encrypt,
		.min_keysize = 2 * AES_MIN_KEY_SIZE,
		.max_keysize = 2 * AES_MAX_KEY_SIZE,
		.ivsize = AES_BLOCK_SIZE,
	पूर्ण, अणु
	/* Unable to find any test vectors so untested */
		.base = अणु
			.cra_name = "ecb(des)",
			.cra_driver_name = "hisi_sec_des_ecb",
			.cra_priority = 4001,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा sec_alg_tfm_ctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = sec_alg_skcipher_init,
		.निकास = sec_alg_skcipher_निकास,
		.setkey = sec_alg_skcipher_setkey_des_ecb,
		.decrypt = sec_alg_skcipher_decrypt,
		.encrypt = sec_alg_skcipher_encrypt,
		.min_keysize = DES_KEY_SIZE,
		.max_keysize = DES_KEY_SIZE,
		.ivsize = 0,
	पूर्ण, अणु
		.base = अणु
			.cra_name = "cbc(des)",
			.cra_driver_name = "hisi_sec_des_cbc",
			.cra_priority = 4001,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = DES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा sec_alg_tfm_ctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = sec_alg_skcipher_init_with_queue,
		.निकास = sec_alg_skcipher_निकास_with_queue,
		.setkey = sec_alg_skcipher_setkey_des_cbc,
		.decrypt = sec_alg_skcipher_decrypt,
		.encrypt = sec_alg_skcipher_encrypt,
		.min_keysize = DES_KEY_SIZE,
		.max_keysize = DES_KEY_SIZE,
		.ivsize = DES_BLOCK_SIZE,
	पूर्ण, अणु
		.base = अणु
			.cra_name = "cbc(des3_ede)",
			.cra_driver_name = "hisi_sec_3des_cbc",
			.cra_priority = 4001,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा sec_alg_tfm_ctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = sec_alg_skcipher_init_with_queue,
		.निकास = sec_alg_skcipher_निकास_with_queue,
		.setkey = sec_alg_skcipher_setkey_3des_cbc,
		.decrypt = sec_alg_skcipher_decrypt,
		.encrypt = sec_alg_skcipher_encrypt,
		.min_keysize = DES3_EDE_KEY_SIZE,
		.max_keysize = DES3_EDE_KEY_SIZE,
		.ivsize = DES3_EDE_BLOCK_SIZE,
	पूर्ण, अणु
		.base = अणु
			.cra_name = "ecb(des3_ede)",
			.cra_driver_name = "hisi_sec_3des_ecb",
			.cra_priority = 4001,
			.cra_flags = CRYPTO_ALG_ASYNC |
				     CRYPTO_ALG_ALLOCATES_MEMORY,
			.cra_blocksize = DES3_EDE_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा sec_alg_tfm_ctx),
			.cra_alignmask = 0,
			.cra_module = THIS_MODULE,
		पूर्ण,
		.init = sec_alg_skcipher_init,
		.निकास = sec_alg_skcipher_निकास,
		.setkey = sec_alg_skcipher_setkey_3des_ecb,
		.decrypt = sec_alg_skcipher_decrypt,
		.encrypt = sec_alg_skcipher_encrypt,
		.min_keysize = DES3_EDE_KEY_SIZE,
		.max_keysize = DES3_EDE_KEY_SIZE,
		.ivsize = 0,
	पूर्ण
पूर्ण;

पूर्णांक sec_algs_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&algs_lock);
	अगर (++active_devs != 1)
		जाओ unlock;

	ret = crypto_रेजिस्टर_skciphers(sec_algs, ARRAY_SIZE(sec_algs));
	अगर (ret)
		--active_devs;
unlock:
	mutex_unlock(&algs_lock);

	वापस ret;
पूर्ण

व्योम sec_algs_unरेजिस्टर(व्योम)
अणु
	mutex_lock(&algs_lock);
	अगर (--active_devs != 0)
		जाओ unlock;
	crypto_unरेजिस्टर_skciphers(sec_algs, ARRAY_SIZE(sec_algs));

unlock:
	mutex_unlock(&algs_lock);
पूर्ण
