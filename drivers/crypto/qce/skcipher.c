<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "cipher.h"

अटल अचिन्हित पूर्णांक aes_sw_max_len = CONFIG_CRYPTO_DEV_QCE_SW_MAX_LEN;
module_param(aes_sw_max_len, uपूर्णांक, 0644);
MODULE_PARM_DESC(aes_sw_max_len,
		 "Only use hardware for AES requests larger than this "
		 "[0=always use hardware; anything <16 breaks AES-GCM; default="
		 __stringअगरy(CONFIG_CRYPTO_DEV_QCE_SW_MAX_LEN)"]");

अटल LIST_HEAD(skcipher_algs);

अटल व्योम qce_skcipher_करोne(व्योम *data)
अणु
	काष्ठा crypto_async_request *async_req = data;
	काष्ठा skcipher_request *req = skcipher_request_cast(async_req);
	काष्ठा qce_cipher_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_cipher_पंचांगpl(crypto_skcipher_reqtfm(req));
	काष्ठा qce_device *qce = पंचांगpl->qce;
	काष्ठा qce_result_dump *result_buf = qce->dma.result_buf;
	क्रमागत dma_data_direction dir_src, dir_dst;
	u32 status;
	पूर्णांक error;
	bool dअगरf_dst;

	dअगरf_dst = (req->src != req->dst) ? true : false;
	dir_src = dअगरf_dst ? DMA_TO_DEVICE : DMA_BIसूचीECTIONAL;
	dir_dst = dअगरf_dst ? DMA_FROM_DEVICE : DMA_BIसूचीECTIONAL;

	error = qce_dma_terminate_all(&qce->dma);
	अगर (error)
		dev_dbg(qce->dev, "skcipher dma termination error (%d)\n",
			error);

	अगर (dअगरf_dst)
		dma_unmap_sg(qce->dev, rctx->src_sg, rctx->src_nents, dir_src);
	dma_unmap_sg(qce->dev, rctx->dst_sg, rctx->dst_nents, dir_dst);

	sg_मुक्त_table(&rctx->dst_tbl);

	error = qce_check_status(qce, &status);
	अगर (error < 0)
		dev_dbg(qce->dev, "skcipher operation error (%x)\n", status);

	स_नकल(rctx->iv, result_buf->encr_cntr_iv, rctx->ivsize);
	qce->async_req_करोne(पंचांगpl->qce, error);
पूर्ण

अटल पूर्णांक
qce_skcipher_async_req_handle(काष्ठा crypto_async_request *async_req)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(async_req);
	काष्ठा qce_cipher_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_cipher_पंचांगpl(crypto_skcipher_reqtfm(req));
	काष्ठा qce_device *qce = पंचांगpl->qce;
	क्रमागत dma_data_direction dir_src, dir_dst;
	काष्ठा scatterlist *sg;
	bool dअगरf_dst;
	gfp_t gfp;
	पूर्णांक ret;

	rctx->iv = req->iv;
	rctx->ivsize = crypto_skcipher_ivsize(skcipher);
	rctx->cryptlen = req->cryptlen;

	dअगरf_dst = (req->src != req->dst) ? true : false;
	dir_src = dअगरf_dst ? DMA_TO_DEVICE : DMA_BIसूचीECTIONAL;
	dir_dst = dअगरf_dst ? DMA_FROM_DEVICE : DMA_BIसूचीECTIONAL;

	rctx->src_nents = sg_nents_क्रम_len(req->src, req->cryptlen);
	अगर (dअगरf_dst)
		rctx->dst_nents = sg_nents_क्रम_len(req->dst, req->cryptlen);
	अन्यथा
		rctx->dst_nents = rctx->src_nents;
	अगर (rctx->src_nents < 0) अणु
		dev_err(qce->dev, "Invalid numbers of src SG.\n");
		वापस rctx->src_nents;
	पूर्ण
	अगर (rctx->dst_nents < 0) अणु
		dev_err(qce->dev, "Invalid numbers of dst SG.\n");
		वापस -rctx->dst_nents;
	पूर्ण

	rctx->dst_nents += 1;

	gfp = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
						GFP_KERNEL : GFP_ATOMIC;

	ret = sg_alloc_table(&rctx->dst_tbl, rctx->dst_nents, gfp);
	अगर (ret)
		वापस ret;

	sg_init_one(&rctx->result_sg, qce->dma.result_buf, QCE_RESULT_BUF_SZ);

	sg = qce_sgtable_add(&rctx->dst_tbl, req->dst, req->cryptlen);
	अगर (IS_ERR(sg)) अणु
		ret = PTR_ERR(sg);
		जाओ error_मुक्त;
	पूर्ण

	sg = qce_sgtable_add(&rctx->dst_tbl, &rctx->result_sg,
			     QCE_RESULT_BUF_SZ);
	अगर (IS_ERR(sg)) अणु
		ret = PTR_ERR(sg);
		जाओ error_मुक्त;
	पूर्ण

	sg_mark_end(sg);
	rctx->dst_sg = rctx->dst_tbl.sgl;

	ret = dma_map_sg(qce->dev, rctx->dst_sg, rctx->dst_nents, dir_dst);
	अगर (ret < 0)
		जाओ error_मुक्त;

	अगर (dअगरf_dst) अणु
		ret = dma_map_sg(qce->dev, req->src, rctx->src_nents, dir_src);
		अगर (ret < 0)
			जाओ error_unmap_dst;
		rctx->src_sg = req->src;
	पूर्ण अन्यथा अणु
		rctx->src_sg = rctx->dst_sg;
	पूर्ण

	ret = qce_dma_prep_sgs(&qce->dma, rctx->src_sg, rctx->src_nents,
			       rctx->dst_sg, rctx->dst_nents,
			       qce_skcipher_करोne, async_req);
	अगर (ret)
		जाओ error_unmap_src;

	qce_dma_issue_pending(&qce->dma);

	ret = qce_start(async_req, पंचांगpl->crypto_alg_type);
	अगर (ret)
		जाओ error_terminate;

	वापस 0;

error_terminate:
	qce_dma_terminate_all(&qce->dma);
error_unmap_src:
	अगर (dअगरf_dst)
		dma_unmap_sg(qce->dev, req->src, rctx->src_nents, dir_src);
error_unmap_dst:
	dma_unmap_sg(qce->dev, rctx->dst_sg, rctx->dst_nents, dir_dst);
error_मुक्त:
	sg_मुक्त_table(&rctx->dst_tbl);
	वापस ret;
पूर्ण

अटल पूर्णांक qce_skcipher_setkey(काष्ठा crypto_skcipher *ablk, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(ablk);
	काष्ठा qce_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	अचिन्हित दीर्घ flags = to_cipher_पंचांगpl(ablk)->alg_flags;
	अचिन्हित पूर्णांक __keylen;
	पूर्णांक ret;

	अगर (!key || !keylen)
		वापस -EINVAL;

	/*
	 * AES XTS key1 = key2 not supported by crypto engine.
	 * Revisit to request a fallback cipher in this हाल.
	 */
	अगर (IS_XTS(flags)) अणु
		__keylen = keylen >> 1;
		अगर (!स_भेद(key, key + __keylen, __keylen))
			वापस -ENOKEY;
	पूर्ण अन्यथा अणु
		__keylen = keylen;
	पूर्ण

	चयन (__keylen) अणु
	हाल AES_KEYSIZE_128:
	हाल AES_KEYSIZE_256:
		स_नकल(ctx->enc_key, key, keylen);
		अवरोध;
	हाल AES_KEYSIZE_192:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = crypto_skcipher_setkey(ctx->fallback, key, keylen);
	अगर (!ret)
		ctx->enc_keylen = keylen;
	वापस ret;
पूर्ण

अटल पूर्णांक qce_des_setkey(काष्ठा crypto_skcipher *ablk, स्थिर u8 *key,
			  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा qce_cipher_ctx *ctx = crypto_skcipher_ctx(ablk);
	पूर्णांक err;

	err = verअगरy_skcipher_des_key(ablk, key);
	अगर (err)
		वापस err;

	ctx->enc_keylen = keylen;
	स_नकल(ctx->enc_key, key, keylen);
	वापस 0;
पूर्ण

अटल पूर्णांक qce_des3_setkey(काष्ठा crypto_skcipher *ablk, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा qce_cipher_ctx *ctx = crypto_skcipher_ctx(ablk);
	u32 _key[6];
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(ablk, key);
	अगर (err)
		वापस err;

	/*
	 * The crypto engine करोes not support any two keys
	 * being the same क्रम triple des algorithms. The
	 * verअगरy_skcipher_des3_key करोes not check क्रम all the
	 * below conditions. Return -ENOKEY in हाल any two keys
	 * are the same. Revisit to see अगर a fallback cipher
	 * is needed to handle this condition.
	 */
	स_नकल(_key, key, DES3_EDE_KEY_SIZE);
	अगर (!((_key[0] ^ _key[2]) | (_key[1] ^ _key[3])) ||
	    !((_key[2] ^ _key[4]) | (_key[3] ^ _key[5])) ||
	    !((_key[0] ^ _key[4]) | (_key[1] ^ _key[5])))
		वापस -ENOKEY;

	ctx->enc_keylen = keylen;
	स_नकल(ctx->enc_key, key, keylen);
	वापस 0;
पूर्ण

अटल पूर्णांक qce_skcipher_crypt(काष्ठा skcipher_request *req, पूर्णांक encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा qce_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा qce_cipher_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा qce_alg_ढाँचा *पंचांगpl = to_cipher_पंचांगpl(tfm);
	अचिन्हित पूर्णांक blocksize = crypto_skcipher_blocksize(tfm);
	पूर्णांक keylen;
	पूर्णांक ret;

	rctx->flags = पंचांगpl->alg_flags;
	rctx->flags |= encrypt ? QCE_ENCRYPT : QCE_DECRYPT;
	keylen = IS_XTS(rctx->flags) ? ctx->enc_keylen >> 1 : ctx->enc_keylen;

	/* CE करोes not handle 0 length messages */
	अगर (!req->cryptlen)
		वापस 0;

	/*
	 * ECB and CBC algorithms require message lengths to be
	 * multiples of block size.
	 */
	अगर (IS_ECB(rctx->flags) || IS_CBC(rctx->flags))
		अगर (!IS_ALIGNED(req->cryptlen, blocksize))
			वापस -EINVAL;

	/*
	 * Conditions क्रम requesting a fallback cipher
	 * AES-192 (not supported by crypto engine (CE))
	 * AES-XTS request with len <= 512 byte (not recommended to use CE)
	 * AES-XTS request with len > QCE_SECTOR_SIZE and
	 * is not a multiple of it.(Revisit this condition to check अगर it is
	 * needed in all versions of CE)
	 */
	अगर (IS_AES(rctx->flags) &&
	    ((keylen != AES_KEYSIZE_128 && keylen != AES_KEYSIZE_256) ||
	    (IS_XTS(rctx->flags) && ((req->cryptlen <= aes_sw_max_len) ||
	    (req->cryptlen > QCE_SECTOR_SIZE &&
	    req->cryptlen % QCE_SECTOR_SIZE))))) अणु
		skcipher_request_set_tfm(&rctx->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&rctx->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&rctx->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);
		ret = encrypt ? crypto_skcipher_encrypt(&rctx->fallback_req) :
				crypto_skcipher_decrypt(&rctx->fallback_req);
		वापस ret;
	पूर्ण

	वापस पंचांगpl->qce->async_req_enqueue(पंचांगpl->qce, &req->base);
पूर्ण

अटल पूर्णांक qce_skcipher_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस qce_skcipher_crypt(req, 1);
पूर्ण

अटल पूर्णांक qce_skcipher_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस qce_skcipher_crypt(req, 0);
पूर्ण

अटल पूर्णांक qce_skcipher_init(काष्ठा crypto_skcipher *tfm)
अणु
	/* take the size without the fallback skcipher_request at the end */
	crypto_skcipher_set_reqsize(tfm, दुरत्व(काष्ठा qce_cipher_reqctx,
						  fallback_req));
	वापस 0;
पूर्ण

अटल पूर्णांक qce_skcipher_init_fallback(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा qce_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->fallback = crypto_alloc_skcipher(crypto_tfm_alg_name(&tfm->base),
					      0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->fallback))
		वापस PTR_ERR(ctx->fallback);

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा qce_cipher_reqctx) +
					 crypto_skcipher_reqsize(ctx->fallback));
	वापस 0;
पूर्ण

अटल व्योम qce_skcipher_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा qce_cipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(ctx->fallback);
पूर्ण

काष्ठा qce_skcipher_def अणु
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *name;
	स्थिर अक्षर *drv_name;
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक chunksize;
	अचिन्हित पूर्णांक ivsize;
	अचिन्हित पूर्णांक min_keysize;
	अचिन्हित पूर्णांक max_keysize;
पूर्ण;

अटल स्थिर काष्ठा qce_skcipher_def skcipher_def[] = अणु
	अणु
		.flags		= QCE_ALG_AES | QCE_MODE_ECB,
		.name		= "ecb(aes)",
		.drv_name	= "ecb-aes-qce",
		.blocksize	= AES_BLOCK_SIZE,
		.ivsize		= 0,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
	पूर्ण,
	अणु
		.flags		= QCE_ALG_AES | QCE_MODE_CBC,
		.name		= "cbc(aes)",
		.drv_name	= "cbc-aes-qce",
		.blocksize	= AES_BLOCK_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
	पूर्ण,
	अणु
		.flags		= QCE_ALG_AES | QCE_MODE_CTR,
		.name		= "ctr(aes)",
		.drv_name	= "ctr-aes-qce",
		.blocksize	= 1,
		.chunksize	= AES_BLOCK_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
	पूर्ण,
	अणु
		.flags		= QCE_ALG_AES | QCE_MODE_XTS,
		.name		= "xts(aes)",
		.drv_name	= "xts-aes-qce",
		.blocksize	= AES_BLOCK_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.min_keysize	= AES_MIN_KEY_SIZE * 2,
		.max_keysize	= AES_MAX_KEY_SIZE * 2,
	पूर्ण,
	अणु
		.flags		= QCE_ALG_DES | QCE_MODE_ECB,
		.name		= "ecb(des)",
		.drv_name	= "ecb-des-qce",
		.blocksize	= DES_BLOCK_SIZE,
		.ivsize		= 0,
		.min_keysize	= DES_KEY_SIZE,
		.max_keysize	= DES_KEY_SIZE,
	पूर्ण,
	अणु
		.flags		= QCE_ALG_DES | QCE_MODE_CBC,
		.name		= "cbc(des)",
		.drv_name	= "cbc-des-qce",
		.blocksize	= DES_BLOCK_SIZE,
		.ivsize		= DES_BLOCK_SIZE,
		.min_keysize	= DES_KEY_SIZE,
		.max_keysize	= DES_KEY_SIZE,
	पूर्ण,
	अणु
		.flags		= QCE_ALG_3DES | QCE_MODE_ECB,
		.name		= "ecb(des3_ede)",
		.drv_name	= "ecb-3des-qce",
		.blocksize	= DES3_EDE_BLOCK_SIZE,
		.ivsize		= 0,
		.min_keysize	= DES3_EDE_KEY_SIZE,
		.max_keysize	= DES3_EDE_KEY_SIZE,
	पूर्ण,
	अणु
		.flags		= QCE_ALG_3DES | QCE_MODE_CBC,
		.name		= "cbc(des3_ede)",
		.drv_name	= "cbc-3des-qce",
		.blocksize	= DES3_EDE_BLOCK_SIZE,
		.ivsize		= DES3_EDE_BLOCK_SIZE,
		.min_keysize	= DES3_EDE_KEY_SIZE,
		.max_keysize	= DES3_EDE_KEY_SIZE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक qce_skcipher_रेजिस्टर_one(स्थिर काष्ठा qce_skcipher_def *def,
				       काष्ठा qce_device *qce)
अणु
	काष्ठा qce_alg_ढाँचा *पंचांगpl;
	काष्ठा skcipher_alg *alg;
	पूर्णांक ret;

	पंचांगpl = kzalloc(माप(*पंचांगpl), GFP_KERNEL);
	अगर (!पंचांगpl)
		वापस -ENOMEM;

	alg = &पंचांगpl->alg.skcipher;

	snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->drv_name);

	alg->base.cra_blocksize		= def->blocksize;
	alg->chunksize			= def->chunksize;
	alg->ivsize			= def->ivsize;
	alg->min_keysize		= def->min_keysize;
	alg->max_keysize		= def->max_keysize;
	alg->setkey			= IS_3DES(def->flags) ? qce_des3_setkey :
					  IS_DES(def->flags) ? qce_des_setkey :
					  qce_skcipher_setkey;
	alg->encrypt			= qce_skcipher_encrypt;
	alg->decrypt			= qce_skcipher_decrypt;

	alg->base.cra_priority		= 300;
	alg->base.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_ALLOCATES_MEMORY |
					  CRYPTO_ALG_KERN_DRIVER_ONLY;
	alg->base.cra_ctxsize		= माप(काष्ठा qce_cipher_ctx);
	alg->base.cra_alignmask		= 0;
	alg->base.cra_module		= THIS_MODULE;

	अगर (IS_AES(def->flags)) अणु
		alg->base.cra_flags    |= CRYPTO_ALG_NEED_FALLBACK;
		alg->init		= qce_skcipher_init_fallback;
		alg->निकास		= qce_skcipher_निकास;
	पूर्ण अन्यथा अणु
		alg->init		= qce_skcipher_init;
	पूर्ण

	INIT_LIST_HEAD(&पंचांगpl->entry);
	पंचांगpl->crypto_alg_type = CRYPTO_ALG_TYPE_SKCIPHER;
	पंचांगpl->alg_flags = def->flags;
	पंचांगpl->qce = qce;

	ret = crypto_रेजिस्टर_skcipher(alg);
	अगर (ret) अणु
		kमुक्त(पंचांगpl);
		dev_err(qce->dev, "%s registration failed\n", alg->base.cra_name);
		वापस ret;
	पूर्ण

	list_add_tail(&पंचांगpl->entry, &skcipher_algs);
	dev_dbg(qce->dev, "%s is registered\n", alg->base.cra_name);
	वापस 0;
पूर्ण

अटल व्योम qce_skcipher_unरेजिस्टर(काष्ठा qce_device *qce)
अणु
	काष्ठा qce_alg_ढाँचा *पंचांगpl, *n;

	list_क्रम_each_entry_safe(पंचांगpl, n, &skcipher_algs, entry) अणु
		crypto_unरेजिस्टर_skcipher(&पंचांगpl->alg.skcipher);
		list_del(&पंचांगpl->entry);
		kमुक्त(पंचांगpl);
	पूर्ण
पूर्ण

अटल पूर्णांक qce_skcipher_रेजिस्टर(काष्ठा qce_device *qce)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(skcipher_def); i++) अणु
		ret = qce_skcipher_रेजिस्टर_one(&skcipher_def[i], qce);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	qce_skcipher_unरेजिस्टर(qce);
	वापस ret;
पूर्ण

स्थिर काष्ठा qce_algo_ops skcipher_ops = अणु
	.type = CRYPTO_ALG_TYPE_SKCIPHER,
	.रेजिस्टर_algs = qce_skcipher_रेजिस्टर,
	.unरेजिस्टर_algs = qce_skcipher_unरेजिस्टर,
	.async_req_handle = qce_skcipher_async_req_handle,
पूर्ण;
