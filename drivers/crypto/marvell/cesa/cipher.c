<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cipher algorithms supported by the CESA: DES, 3DES and AES.
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 * Author: Arnaud Ebalard <arno@natisbad.org>
 *
 * This work is based on an initial version written by
 * Sebastian Andrzej Siewior < sebastian at अवरोधpoपूर्णांक करोt cc >
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>

#समावेश "cesa.h"

काष्ठा mv_cesa_des_ctx अणु
	काष्ठा mv_cesa_ctx base;
	u8 key[DES_KEY_SIZE];
पूर्ण;

काष्ठा mv_cesa_des3_ctx अणु
	काष्ठा mv_cesa_ctx base;
	u8 key[DES3_EDE_KEY_SIZE];
पूर्ण;

काष्ठा mv_cesa_aes_ctx अणु
	काष्ठा mv_cesa_ctx base;
	काष्ठा crypto_aes_ctx aes;
पूर्ण;

काष्ठा mv_cesa_skcipher_dma_iter अणु
	काष्ठा mv_cesa_dma_iter base;
	काष्ठा mv_cesa_sg_dma_iter src;
	काष्ठा mv_cesa_sg_dma_iter dst;
पूर्ण;

अटल अंतरभूत व्योम
mv_cesa_skcipher_req_iter_init(काष्ठा mv_cesa_skcipher_dma_iter *iter,
			       काष्ठा skcipher_request *req)
अणु
	mv_cesa_req_dma_iter_init(&iter->base, req->cryptlen);
	mv_cesa_sg_dma_iter_init(&iter->src, req->src, DMA_TO_DEVICE);
	mv_cesa_sg_dma_iter_init(&iter->dst, req->dst, DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत bool
mv_cesa_skcipher_req_iter_next_op(काष्ठा mv_cesa_skcipher_dma_iter *iter)
अणु
	iter->src.op_offset = 0;
	iter->dst.op_offset = 0;

	वापस mv_cesa_req_dma_iter_next_op(&iter->base);
पूर्ण

अटल अंतरभूत व्योम
mv_cesa_skcipher_dma_cleanup(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);

	अगर (req->dst != req->src) अणु
		dma_unmap_sg(cesa_dev->dev, req->dst, creq->dst_nents,
			     DMA_FROM_DEVICE);
		dma_unmap_sg(cesa_dev->dev, req->src, creq->src_nents,
			     DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(cesa_dev->dev, req->src, creq->src_nents,
			     DMA_BIसूचीECTIONAL);
	पूर्ण
	mv_cesa_dma_cleanup(&creq->base);
पूर्ण

अटल अंतरभूत व्योम mv_cesa_skcipher_cleanup(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_skcipher_dma_cleanup(req);
पूर्ण

अटल व्योम mv_cesa_skcipher_std_step(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	काष्ठा mv_cesa_skcipher_std_req *sreq = &creq->std;
	काष्ठा mv_cesa_engine *engine = creq->base.engine;
	माप_प्रकार  len = min_t(माप_प्रकार, req->cryptlen - sreq->offset,
			    CESA_SA_SRAM_PAYLOAD_SIZE);

	mv_cesa_adjust_op(engine, &sreq->op);
	अगर (engine->pool)
		स_नकल(engine->sram_pool, &sreq->op, माप(sreq->op));
	अन्यथा
		स_नकल_toio(engine->sram, &sreq->op, माप(sreq->op));

	len = mv_cesa_sg_copy_to_sram(engine, req->src, creq->src_nents,
				      CESA_SA_DATA_SRAM_OFFSET, len,
				      sreq->offset);

	sreq->size = len;
	mv_cesa_set_crypt_op_len(&sreq->op, len);

	/* FIXME: only update enc_len field */
	अगर (!sreq->skip_ctx) अणु
		अगर (engine->pool)
			स_नकल(engine->sram_pool, &sreq->op, माप(sreq->op));
		अन्यथा
			स_नकल_toio(engine->sram, &sreq->op, माप(sreq->op));
		sreq->skip_ctx = true;
	पूर्ण अन्यथा अगर (engine->pool)
		स_नकल(engine->sram_pool, &sreq->op, माप(sreq->op.desc));
	अन्यथा
		स_नकल_toio(engine->sram, &sreq->op, माप(sreq->op.desc));

	mv_cesa_set_पूर्णांक_mask(engine, CESA_SA_INT_ACCEL0_DONE);
	ग_लिखोl_relaxed(CESA_SA_CFG_PARA_DIS, engine->regs + CESA_SA_CFG);
	WARN_ON(पढ़ोl(engine->regs + CESA_SA_CMD) &
		CESA_SA_CMD_EN_CESA_SA_ACCL0);
	ग_लिखोl(CESA_SA_CMD_EN_CESA_SA_ACCL0, engine->regs + CESA_SA_CMD);
पूर्ण

अटल पूर्णांक mv_cesa_skcipher_std_process(काष्ठा skcipher_request *req,
					u32 status)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	काष्ठा mv_cesa_skcipher_std_req *sreq = &creq->std;
	काष्ठा mv_cesa_engine *engine = creq->base.engine;
	माप_प्रकार len;

	len = mv_cesa_sg_copy_from_sram(engine, req->dst, creq->dst_nents,
					CESA_SA_DATA_SRAM_OFFSET, sreq->size,
					sreq->offset);

	sreq->offset += len;
	अगर (sreq->offset < req->cryptlen)
		वापस -EINPROGRESS;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_skcipher_process(काष्ठा crypto_async_request *req,
				    u32 status)
अणु
	काष्ठा skcipher_request *skreq = skcipher_request_cast(req);
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(skreq);
	काष्ठा mv_cesa_req *basereq = &creq->base;

	अगर (mv_cesa_req_get_type(basereq) == CESA_STD_REQ)
		वापस mv_cesa_skcipher_std_process(skreq, status);

	वापस mv_cesa_dma_process(basereq, status);
पूर्ण

अटल व्योम mv_cesa_skcipher_step(काष्ठा crypto_async_request *req)
अणु
	काष्ठा skcipher_request *skreq = skcipher_request_cast(req);
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(skreq);

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_dma_step(&creq->base);
	अन्यथा
		mv_cesa_skcipher_std_step(skreq);
पूर्ण

अटल अंतरभूत व्योम
mv_cesa_skcipher_dma_prepare(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	काष्ठा mv_cesa_req *basereq = &creq->base;

	mv_cesa_dma_prepare(basereq, basereq->engine);
पूर्ण

अटल अंतरभूत व्योम
mv_cesa_skcipher_std_prepare(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	काष्ठा mv_cesa_skcipher_std_req *sreq = &creq->std;

	sreq->size = 0;
	sreq->offset = 0;
पूर्ण

अटल अंतरभूत व्योम mv_cesa_skcipher_prepare(काष्ठा crypto_async_request *req,
					    काष्ठा mv_cesa_engine *engine)
अणु
	काष्ठा skcipher_request *skreq = skcipher_request_cast(req);
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(skreq);

	creq->base.engine = engine;

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ)
		mv_cesa_skcipher_dma_prepare(skreq);
	अन्यथा
		mv_cesa_skcipher_std_prepare(skreq);
पूर्ण

अटल अंतरभूत व्योम
mv_cesa_skcipher_req_cleanup(काष्ठा crypto_async_request *req)
अणु
	काष्ठा skcipher_request *skreq = skcipher_request_cast(req);

	mv_cesa_skcipher_cleanup(skreq);
पूर्ण

अटल व्योम
mv_cesa_skcipher_complete(काष्ठा crypto_async_request *req)
अणु
	काष्ठा skcipher_request *skreq = skcipher_request_cast(req);
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(skreq);
	काष्ठा mv_cesa_engine *engine = creq->base.engine;
	अचिन्हित पूर्णांक ivsize;

	atomic_sub(skreq->cryptlen, &engine->load);
	ivsize = crypto_skcipher_ivsize(crypto_skcipher_reqtfm(skreq));

	अगर (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ) अणु
		काष्ठा mv_cesa_req *basereq;

		basereq = &creq->base;
		स_नकल(skreq->iv, basereq->chain.last->op->ctx.skcipher.iv,
		       ivsize);
	पूर्ण अन्यथा अगर (engine->pool)
		स_नकल(skreq->iv,
		       engine->sram_pool + CESA_SA_CRYPT_IV_SRAM_OFFSET,
		       ivsize);
	अन्यथा
		स_नकल_fromio(skreq->iv,
			      engine->sram + CESA_SA_CRYPT_IV_SRAM_OFFSET,
			      ivsize);
पूर्ण

अटल स्थिर काष्ठा mv_cesa_req_ops mv_cesa_skcipher_req_ops = अणु
	.step = mv_cesa_skcipher_step,
	.process = mv_cesa_skcipher_process,
	.cleanup = mv_cesa_skcipher_req_cleanup,
	.complete = mv_cesa_skcipher_complete,
पूर्ण;

अटल व्योम mv_cesa_skcipher_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	व्योम *ctx = crypto_tfm_ctx(tfm);

	memzero_explicit(ctx, tfm->__crt_alg->cra_ctxsize);
पूर्ण

अटल पूर्णांक mv_cesa_skcipher_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा mv_cesa_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->ops = &mv_cesa_skcipher_req_ops;

	crypto_skcipher_set_reqsize(__crypto_skcipher_cast(tfm),
				    माप(काष्ठा mv_cesa_skcipher_req));

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_aes_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा mv_cesa_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक reमुख्यing;
	पूर्णांक offset;
	पूर्णांक ret;
	पूर्णांक i;

	ret = aes_expandkey(&ctx->aes, key, len);
	अगर (ret)
		वापस ret;

	reमुख्यing = (ctx->aes.key_length - 16) / 4;
	offset = ctx->aes.key_length + 24 - reमुख्यing;
	क्रम (i = 0; i < reमुख्यing; i++)
		ctx->aes.key_dec[4 + i] = ctx->aes.key_enc[offset + i];

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_des_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा mv_cesa_des_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	err = verअगरy_skcipher_des_key(cipher, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, DES_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_des3_ede_setkey(काष्ठा crypto_skcipher *cipher,
				   स्थिर u8 *key, अचिन्हित पूर्णांक len)
अणु
	काष्ठा mv_cesa_des_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(cipher, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, DES3_EDE_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_skcipher_dma_req_init(काष्ठा skcipher_request *req,
					 स्थिर काष्ठा mv_cesa_op_ctx *op_templ)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	काष्ठा mv_cesa_req *basereq = &creq->base;
	काष्ठा mv_cesa_skcipher_dma_iter iter;
	bool skip_ctx = false;
	पूर्णांक ret;

	basereq->chain.first = शून्य;
	basereq->chain.last = शून्य;

	अगर (req->src != req->dst) अणु
		ret = dma_map_sg(cesa_dev->dev, req->src, creq->src_nents,
				 DMA_TO_DEVICE);
		अगर (!ret)
			वापस -ENOMEM;

		ret = dma_map_sg(cesa_dev->dev, req->dst, creq->dst_nents,
				 DMA_FROM_DEVICE);
		अगर (!ret) अणु
			ret = -ENOMEM;
			जाओ err_unmap_src;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = dma_map_sg(cesa_dev->dev, req->src, creq->src_nents,
				 DMA_BIसूचीECTIONAL);
		अगर (!ret)
			वापस -ENOMEM;
	पूर्ण

	mv_cesa_tdma_desc_iter_init(&basereq->chain);
	mv_cesa_skcipher_req_iter_init(&iter, req);

	करो अणु
		काष्ठा mv_cesa_op_ctx *op;

		op = mv_cesa_dma_add_op(&basereq->chain, op_templ, skip_ctx,
					flags);
		अगर (IS_ERR(op)) अणु
			ret = PTR_ERR(op);
			जाओ err_मुक्त_tdma;
		पूर्ण
		skip_ctx = true;

		mv_cesa_set_crypt_op_len(op, iter.base.op_len);

		/* Add input transfers */
		ret = mv_cesa_dma_add_op_transfers(&basereq->chain, &iter.base,
						   &iter.src, flags);
		अगर (ret)
			जाओ err_मुक्त_tdma;

		/* Add dummy desc to launch the crypto operation */
		ret = mv_cesa_dma_add_dummy_launch(&basereq->chain, flags);
		अगर (ret)
			जाओ err_मुक्त_tdma;

		/* Add output transfers */
		ret = mv_cesa_dma_add_op_transfers(&basereq->chain, &iter.base,
						   &iter.dst, flags);
		अगर (ret)
			जाओ err_मुक्त_tdma;

	पूर्ण जबतक (mv_cesa_skcipher_req_iter_next_op(&iter));

	/* Add output data क्रम IV */
	ret = mv_cesa_dma_add_result_op(&basereq->chain,
					CESA_SA_CFG_SRAM_OFFSET,
					CESA_SA_DATA_SRAM_OFFSET,
					CESA_TDMA_SRC_IN_SRAM, flags);

	अगर (ret)
		जाओ err_मुक्त_tdma;

	basereq->chain.last->flags |= CESA_TDMA_END_OF_REQ;

	वापस 0;

err_मुक्त_tdma:
	mv_cesa_dma_cleanup(basereq);
	अगर (req->dst != req->src)
		dma_unmap_sg(cesa_dev->dev, req->dst, creq->dst_nents,
			     DMA_FROM_DEVICE);

err_unmap_src:
	dma_unmap_sg(cesa_dev->dev, req->src, creq->src_nents,
		     req->dst != req->src ? DMA_TO_DEVICE : DMA_BIसूचीECTIONAL);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
mv_cesa_skcipher_std_req_init(काष्ठा skcipher_request *req,
			      स्थिर काष्ठा mv_cesa_op_ctx *op_templ)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	काष्ठा mv_cesa_skcipher_std_req *sreq = &creq->std;
	काष्ठा mv_cesa_req *basereq = &creq->base;

	sreq->op = *op_templ;
	sreq->skip_ctx = false;
	basereq->chain.first = शून्य;
	basereq->chain.last = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_cesa_skcipher_req_init(काष्ठा skcipher_request *req,
				     काष्ठा mv_cesa_op_ctx *पंचांगpl)
अणु
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	अचिन्हित पूर्णांक blksize = crypto_skcipher_blocksize(tfm);
	पूर्णांक ret;

	अगर (!IS_ALIGNED(req->cryptlen, blksize))
		वापस -EINVAL;

	creq->src_nents = sg_nents_क्रम_len(req->src, req->cryptlen);
	अगर (creq->src_nents < 0) अणु
		dev_err(cesa_dev->dev, "Invalid number of src SG");
		वापस creq->src_nents;
	पूर्ण
	creq->dst_nents = sg_nents_क्रम_len(req->dst, req->cryptlen);
	अगर (creq->dst_nents < 0) अणु
		dev_err(cesa_dev->dev, "Invalid number of dst SG");
		वापस creq->dst_nents;
	पूर्ण

	mv_cesa_update_op_cfg(पंचांगpl, CESA_SA_DESC_CFG_OP_CRYPT_ONLY,
			      CESA_SA_DESC_CFG_OP_MSK);

	अगर (cesa_dev->caps->has_tdma)
		ret = mv_cesa_skcipher_dma_req_init(req, पंचांगpl);
	अन्यथा
		ret = mv_cesa_skcipher_std_req_init(req, पंचांगpl);

	वापस ret;
पूर्ण

अटल पूर्णांक mv_cesa_skcipher_queue_req(काष्ठा skcipher_request *req,
				      काष्ठा mv_cesa_op_ctx *पंचांगpl)
अणु
	पूर्णांक ret;
	काष्ठा mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	काष्ठा mv_cesa_engine *engine;

	ret = mv_cesa_skcipher_req_init(req, पंचांगpl);
	अगर (ret)
		वापस ret;

	engine = mv_cesa_select_engine(req->cryptlen);
	mv_cesa_skcipher_prepare(&req->base, engine);

	ret = mv_cesa_queue_req(&req->base, &creq->base);

	अगर (mv_cesa_req_needs_cleanup(&req->base, ret))
		mv_cesa_skcipher_cleanup(req);

	वापस ret;
पूर्ण

अटल पूर्णांक mv_cesa_des_op(काष्ठा skcipher_request *req,
			  काष्ठा mv_cesa_op_ctx *पंचांगpl)
अणु
	काष्ठा mv_cesa_des_ctx *ctx = crypto_tfm_ctx(req->base.tfm);

	mv_cesa_update_op_cfg(पंचांगpl, CESA_SA_DESC_CFG_CRYPTM_DES,
			      CESA_SA_DESC_CFG_CRYPTM_MSK);

	स_नकल(पंचांगpl->ctx.skcipher.key, ctx->key, DES_KEY_SIZE);

	वापस mv_cesa_skcipher_queue_req(req, पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_ecb_des_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl,
			   CESA_SA_DESC_CFG_CRYPTCM_ECB |
			   CESA_SA_DESC_CFG_सूची_ENC);

	वापस mv_cesa_des_op(req, &पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_ecb_des_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl,
			   CESA_SA_DESC_CFG_CRYPTCM_ECB |
			   CESA_SA_DESC_CFG_सूची_DEC);

	वापस mv_cesa_des_op(req, &पंचांगpl);
पूर्ण

काष्ठा skcipher_alg mv_cesa_ecb_des_alg = अणु
	.setkey = mv_cesa_des_setkey,
	.encrypt = mv_cesa_ecb_des_encrypt,
	.decrypt = mv_cesa_ecb_des_decrypt,
	.min_keysize = DES_KEY_SIZE,
	.max_keysize = DES_KEY_SIZE,
	.base = अणु
		.cra_name = "ecb(des)",
		.cra_driver_name = "mv-ecb-des",
		.cra_priority = 300,
		.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC |
			     CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = DES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा mv_cesa_des_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
		.cra_init = mv_cesa_skcipher_cra_init,
		.cra_निकास = mv_cesa_skcipher_cra_निकास,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mv_cesa_cbc_des_op(काष्ठा skcipher_request *req,
			      काष्ठा mv_cesa_op_ctx *पंचांगpl)
अणु
	mv_cesa_update_op_cfg(पंचांगpl, CESA_SA_DESC_CFG_CRYPTCM_CBC,
			      CESA_SA_DESC_CFG_CRYPTCM_MSK);

	स_नकल(पंचांगpl->ctx.skcipher.iv, req->iv, DES_BLOCK_SIZE);

	वापस mv_cesa_des_op(req, पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_cbc_des_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_सूची_ENC);

	वापस mv_cesa_cbc_des_op(req, &पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_cbc_des_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_सूची_DEC);

	वापस mv_cesa_cbc_des_op(req, &पंचांगpl);
पूर्ण

काष्ठा skcipher_alg mv_cesa_cbc_des_alg = अणु
	.setkey = mv_cesa_des_setkey,
	.encrypt = mv_cesa_cbc_des_encrypt,
	.decrypt = mv_cesa_cbc_des_decrypt,
	.min_keysize = DES_KEY_SIZE,
	.max_keysize = DES_KEY_SIZE,
	.ivsize = DES_BLOCK_SIZE,
	.base = अणु
		.cra_name = "cbc(des)",
		.cra_driver_name = "mv-cbc-des",
		.cra_priority = 300,
		.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC |
			     CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = DES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा mv_cesa_des_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
		.cra_init = mv_cesa_skcipher_cra_init,
		.cra_निकास = mv_cesa_skcipher_cra_निकास,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mv_cesa_des3_op(काष्ठा skcipher_request *req,
			   काष्ठा mv_cesa_op_ctx *पंचांगpl)
अणु
	काष्ठा mv_cesa_des3_ctx *ctx = crypto_tfm_ctx(req->base.tfm);

	mv_cesa_update_op_cfg(पंचांगpl, CESA_SA_DESC_CFG_CRYPTM_3DES,
			      CESA_SA_DESC_CFG_CRYPTM_MSK);

	स_नकल(पंचांगpl->ctx.skcipher.key, ctx->key, DES3_EDE_KEY_SIZE);

	वापस mv_cesa_skcipher_queue_req(req, पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_ecb_des3_ede_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl,
			   CESA_SA_DESC_CFG_CRYPTCM_ECB |
			   CESA_SA_DESC_CFG_3DES_EDE |
			   CESA_SA_DESC_CFG_सूची_ENC);

	वापस mv_cesa_des3_op(req, &पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_ecb_des3_ede_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl,
			   CESA_SA_DESC_CFG_CRYPTCM_ECB |
			   CESA_SA_DESC_CFG_3DES_EDE |
			   CESA_SA_DESC_CFG_सूची_DEC);

	वापस mv_cesa_des3_op(req, &पंचांगpl);
पूर्ण

काष्ठा skcipher_alg mv_cesa_ecb_des3_ede_alg = अणु
	.setkey = mv_cesa_des3_ede_setkey,
	.encrypt = mv_cesa_ecb_des3_ede_encrypt,
	.decrypt = mv_cesa_ecb_des3_ede_decrypt,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES3_EDE_BLOCK_SIZE,
	.base = अणु
		.cra_name = "ecb(des3_ede)",
		.cra_driver_name = "mv-ecb-des3-ede",
		.cra_priority = 300,
		.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC |
			     CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = DES3_EDE_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा mv_cesa_des3_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
		.cra_init = mv_cesa_skcipher_cra_init,
		.cra_निकास = mv_cesa_skcipher_cra_निकास,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mv_cesa_cbc_des3_op(काष्ठा skcipher_request *req,
			       काष्ठा mv_cesa_op_ctx *पंचांगpl)
अणु
	स_नकल(पंचांगpl->ctx.skcipher.iv, req->iv, DES3_EDE_BLOCK_SIZE);

	वापस mv_cesa_des3_op(req, पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_cbc_des3_ede_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl,
			   CESA_SA_DESC_CFG_CRYPTCM_CBC |
			   CESA_SA_DESC_CFG_3DES_EDE |
			   CESA_SA_DESC_CFG_सूची_ENC);

	वापस mv_cesa_cbc_des3_op(req, &पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_cbc_des3_ede_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl,
			   CESA_SA_DESC_CFG_CRYPTCM_CBC |
			   CESA_SA_DESC_CFG_3DES_EDE |
			   CESA_SA_DESC_CFG_सूची_DEC);

	वापस mv_cesa_cbc_des3_op(req, &पंचांगpl);
पूर्ण

काष्ठा skcipher_alg mv_cesa_cbc_des3_ede_alg = अणु
	.setkey = mv_cesa_des3_ede_setkey,
	.encrypt = mv_cesa_cbc_des3_ede_encrypt,
	.decrypt = mv_cesa_cbc_des3_ede_decrypt,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES3_EDE_BLOCK_SIZE,
	.base = अणु
		.cra_name = "cbc(des3_ede)",
		.cra_driver_name = "mv-cbc-des3-ede",
		.cra_priority = 300,
		.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC |
			     CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = DES3_EDE_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा mv_cesa_des3_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
		.cra_init = mv_cesa_skcipher_cra_init,
		.cra_निकास = mv_cesa_skcipher_cra_निकास,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mv_cesa_aes_op(काष्ठा skcipher_request *req,
			  काष्ठा mv_cesa_op_ctx *पंचांगpl)
अणु
	काष्ठा mv_cesa_aes_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	पूर्णांक i;
	u32 *key;
	u32 cfg;

	cfg = CESA_SA_DESC_CFG_CRYPTM_AES;

	अगर (mv_cesa_get_op_cfg(पंचांगpl) & CESA_SA_DESC_CFG_सूची_DEC)
		key = ctx->aes.key_dec;
	अन्यथा
		key = ctx->aes.key_enc;

	क्रम (i = 0; i < ctx->aes.key_length / माप(u32); i++)
		पंचांगpl->ctx.skcipher.key[i] = cpu_to_le32(key[i]);

	अगर (ctx->aes.key_length == 24)
		cfg |= CESA_SA_DESC_CFG_AES_LEN_192;
	अन्यथा अगर (ctx->aes.key_length == 32)
		cfg |= CESA_SA_DESC_CFG_AES_LEN_256;

	mv_cesa_update_op_cfg(पंचांगpl, cfg,
			      CESA_SA_DESC_CFG_CRYPTM_MSK |
			      CESA_SA_DESC_CFG_AES_LEN_MSK);

	वापस mv_cesa_skcipher_queue_req(req, पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_ecb_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl,
			   CESA_SA_DESC_CFG_CRYPTCM_ECB |
			   CESA_SA_DESC_CFG_सूची_ENC);

	वापस mv_cesa_aes_op(req, &पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_ecb_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl,
			   CESA_SA_DESC_CFG_CRYPTCM_ECB |
			   CESA_SA_DESC_CFG_सूची_DEC);

	वापस mv_cesa_aes_op(req, &पंचांगpl);
पूर्ण

काष्ठा skcipher_alg mv_cesa_ecb_aes_alg = अणु
	.setkey = mv_cesa_aes_setkey,
	.encrypt = mv_cesa_ecb_aes_encrypt,
	.decrypt = mv_cesa_ecb_aes_decrypt,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.base = अणु
		.cra_name = "ecb(aes)",
		.cra_driver_name = "mv-ecb-aes",
		.cra_priority = 300,
		.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC |
			     CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा mv_cesa_aes_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
		.cra_init = mv_cesa_skcipher_cra_init,
		.cra_निकास = mv_cesa_skcipher_cra_निकास,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mv_cesa_cbc_aes_op(काष्ठा skcipher_request *req,
			      काष्ठा mv_cesa_op_ctx *पंचांगpl)
अणु
	mv_cesa_update_op_cfg(पंचांगpl, CESA_SA_DESC_CFG_CRYPTCM_CBC,
			      CESA_SA_DESC_CFG_CRYPTCM_MSK);
	स_नकल(पंचांगpl->ctx.skcipher.iv, req->iv, AES_BLOCK_SIZE);

	वापस mv_cesa_aes_op(req, पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_cbc_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_सूची_ENC);

	वापस mv_cesa_cbc_aes_op(req, &पंचांगpl);
पूर्ण

अटल पूर्णांक mv_cesa_cbc_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा mv_cesa_op_ctx पंचांगpl;

	mv_cesa_set_op_cfg(&पंचांगpl, CESA_SA_DESC_CFG_सूची_DEC);

	वापस mv_cesa_cbc_aes_op(req, &पंचांगpl);
पूर्ण

काष्ठा skcipher_alg mv_cesa_cbc_aes_alg = अणु
	.setkey = mv_cesa_aes_setkey,
	.encrypt = mv_cesa_cbc_aes_encrypt,
	.decrypt = mv_cesa_cbc_aes_decrypt,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
	.base = अणु
		.cra_name = "cbc(aes)",
		.cra_driver_name = "mv-cbc-aes",
		.cra_priority = 300,
		.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC |
			     CRYPTO_ALG_ALLOCATES_MEMORY,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_ctxsize = माप(काष्ठा mv_cesa_aes_ctx),
		.cra_alignmask = 0,
		.cra_module = THIS_MODULE,
		.cra_init = mv_cesa_skcipher_cra_init,
		.cra_निकास = mv_cesa_skcipher_cra_निकास,
	पूर्ण,
पूर्ण;
