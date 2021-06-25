<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) AES crypto API support
 *
 * Copyright (C) 2013-2019 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "ccp-crypto.h"

अटल पूर्णांक ccp_aes_complete(काष्ठा crypto_async_request *async_req, पूर्णांक ret)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(async_req);
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा ccp_aes_req_ctx *rctx = skcipher_request_ctx(req);

	अगर (ret)
		वापस ret;

	अगर (ctx->u.aes.mode != CCP_AES_MODE_ECB)
		स_नकल(req->iv, rctx->iv, AES_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			  अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ccp_crypto_skcipher_alg *alg = ccp_crypto_skcipher_alg(tfm);
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);

	चयन (key_len) अणु
	हाल AES_KEYSIZE_128:
		ctx->u.aes.type = CCP_AES_TYPE_128;
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->u.aes.type = CCP_AES_TYPE_192;
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->u.aes.type = CCP_AES_TYPE_256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ctx->u.aes.mode = alg->mode;
	ctx->u.aes.key_len = key_len;

	स_नकल(ctx->u.aes.key, key, key_len);
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा ccp_aes_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा scatterlist *iv_sg = शून्य;
	अचिन्हित पूर्णांक iv_len = 0;
	पूर्णांक ret;

	अगर (!ctx->u.aes.key_len)
		वापस -EINVAL;

	अगर (((ctx->u.aes.mode == CCP_AES_MODE_ECB) ||
	     (ctx->u.aes.mode == CCP_AES_MODE_CBC)) &&
	    (req->cryptlen & (AES_BLOCK_SIZE - 1)))
		वापस -EINVAL;

	अगर (ctx->u.aes.mode != CCP_AES_MODE_ECB) अणु
		अगर (!req->iv)
			वापस -EINVAL;

		स_नकल(rctx->iv, req->iv, AES_BLOCK_SIZE);
		iv_sg = &rctx->iv_sg;
		iv_len = AES_BLOCK_SIZE;
		sg_init_one(iv_sg, rctx->iv, iv_len);
	पूर्ण

	स_रखो(&rctx->cmd, 0, माप(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_AES;
	rctx->cmd.u.aes.type = ctx->u.aes.type;
	rctx->cmd.u.aes.mode = ctx->u.aes.mode;
	rctx->cmd.u.aes.action =
		(encrypt) ? CCP_AES_ACTION_ENCRYPT : CCP_AES_ACTION_DECRYPT;
	rctx->cmd.u.aes.key = &ctx->u.aes.key_sg;
	rctx->cmd.u.aes.key_len = ctx->u.aes.key_len;
	rctx->cmd.u.aes.iv = iv_sg;
	rctx->cmd.u.aes.iv_len = iv_len;
	rctx->cmd.u.aes.src = req->src;
	rctx->cmd.u.aes.src_len = req->cryptlen;
	rctx->cmd.u.aes.dst = req->dst;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ccp_aes_crypt(req, true);
पूर्ण

अटल पूर्णांक ccp_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ccp_aes_crypt(req, false);
पूर्ण

अटल पूर्णांक ccp_aes_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->complete = ccp_aes_complete;
	ctx->u.aes.key_len = 0;

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा ccp_aes_req_ctx));

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_rfc3686_complete(काष्ठा crypto_async_request *async_req,
				    पूर्णांक ret)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(async_req);
	काष्ठा ccp_aes_req_ctx *rctx = skcipher_request_ctx(req);

	/* Restore the original poपूर्णांकer */
	req->iv = rctx->rfc3686_info;

	वापस ccp_aes_complete(async_req, ret);
पूर्ण

अटल पूर्णांक ccp_aes_rfc3686_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				  अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (key_len < CTR_RFC3686_NONCE_SIZE)
		वापस -EINVAL;

	key_len -= CTR_RFC3686_NONCE_SIZE;
	स_नकल(ctx->u.aes.nonce, key + key_len, CTR_RFC3686_NONCE_SIZE);

	वापस ccp_aes_setkey(tfm, key, key_len);
पूर्ण

अटल पूर्णांक ccp_aes_rfc3686_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा ccp_aes_req_ctx *rctx = skcipher_request_ctx(req);
	u8 *iv;

	/* Initialize the CTR block */
	iv = rctx->rfc3686_iv;
	स_नकल(iv, ctx->u.aes.nonce, CTR_RFC3686_NONCE_SIZE);

	iv += CTR_RFC3686_NONCE_SIZE;
	स_नकल(iv, req->iv, CTR_RFC3686_IV_SIZE);

	iv += CTR_RFC3686_IV_SIZE;
	*(__be32 *)iv = cpu_to_be32(1);

	/* Poपूर्णांक to the new IV */
	rctx->rfc3686_info = req->iv;
	req->iv = rctx->rfc3686_iv;

	वापस ccp_aes_crypt(req, encrypt);
पूर्ण

अटल पूर्णांक ccp_aes_rfc3686_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ccp_aes_rfc3686_crypt(req, true);
पूर्ण

अटल पूर्णांक ccp_aes_rfc3686_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ccp_aes_rfc3686_crypt(req, false);
पूर्ण

अटल पूर्णांक ccp_aes_rfc3686_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->complete = ccp_aes_rfc3686_complete;
	ctx->u.aes.key_len = 0;

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा ccp_aes_req_ctx));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा skcipher_alg ccp_aes_शेषs = अणु
	.setkey			= ccp_aes_setkey,
	.encrypt		= ccp_aes_encrypt,
	.decrypt		= ccp_aes_decrypt,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.init			= ccp_aes_init_tfm,

	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा ccp_ctx),
	.base.cra_priority	= CCP_CRA_PRIORITY,
	.base.cra_module	= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा skcipher_alg ccp_aes_rfc3686_शेषs = अणु
	.setkey			= ccp_aes_rfc3686_setkey,
	.encrypt		= ccp_aes_rfc3686_encrypt,
	.decrypt		= ccp_aes_rfc3686_decrypt,
	.min_keysize		= AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
	.init			= ccp_aes_rfc3686_init_tfm,

	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	= CTR_RFC3686_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा ccp_ctx),
	.base.cra_priority	= CCP_CRA_PRIORITY,
	.base.cra_module	= THIS_MODULE,
पूर्ण;

काष्ठा ccp_aes_def अणु
	क्रमागत ccp_aes_mode mode;
	अचिन्हित पूर्णांक version;
	स्थिर अक्षर *name;
	स्थिर अक्षर *driver_name;
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक ivsize;
	स्थिर काष्ठा skcipher_alg *alg_शेषs;
पूर्ण;

अटल काष्ठा ccp_aes_def aes_algs[] = अणु
	अणु
		.mode		= CCP_AES_MODE_ECB,
		.version	= CCP_VERSION(3, 0),
		.name		= "ecb(aes)",
		.driver_name	= "ecb-aes-ccp",
		.blocksize	= AES_BLOCK_SIZE,
		.ivsize		= 0,
		.alg_शेषs	= &ccp_aes_शेषs,
	पूर्ण,
	अणु
		.mode		= CCP_AES_MODE_CBC,
		.version	= CCP_VERSION(3, 0),
		.name		= "cbc(aes)",
		.driver_name	= "cbc-aes-ccp",
		.blocksize	= AES_BLOCK_SIZE,
		.ivsize		= AES_BLOCK_SIZE,
		.alg_शेषs	= &ccp_aes_शेषs,
	पूर्ण,
	अणु
		.mode		= CCP_AES_MODE_CFB,
		.version	= CCP_VERSION(3, 0),
		.name		= "cfb(aes)",
		.driver_name	= "cfb-aes-ccp",
		.blocksize	= 1,
		.ivsize		= AES_BLOCK_SIZE,
		.alg_शेषs	= &ccp_aes_शेषs,
	पूर्ण,
	अणु
		.mode		= CCP_AES_MODE_OFB,
		.version	= CCP_VERSION(3, 0),
		.name		= "ofb(aes)",
		.driver_name	= "ofb-aes-ccp",
		.blocksize	= 1,
		.ivsize		= AES_BLOCK_SIZE,
		.alg_शेषs	= &ccp_aes_शेषs,
	पूर्ण,
	अणु
		.mode		= CCP_AES_MODE_CTR,
		.version	= CCP_VERSION(3, 0),
		.name		= "ctr(aes)",
		.driver_name	= "ctr-aes-ccp",
		.blocksize	= 1,
		.ivsize		= AES_BLOCK_SIZE,
		.alg_शेषs	= &ccp_aes_शेषs,
	पूर्ण,
	अणु
		.mode		= CCP_AES_MODE_CTR,
		.version	= CCP_VERSION(3, 0),
		.name		= "rfc3686(ctr(aes))",
		.driver_name	= "rfc3686-ctr-aes-ccp",
		.blocksize	= 1,
		.ivsize		= CTR_RFC3686_IV_SIZE,
		.alg_शेषs	= &ccp_aes_rfc3686_शेषs,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ccp_रेजिस्टर_aes_alg(काष्ठा list_head *head,
				स्थिर काष्ठा ccp_aes_def *def)
अणु
	काष्ठा ccp_crypto_skcipher_alg *ccp_alg;
	काष्ठा skcipher_alg *alg;
	पूर्णांक ret;

	ccp_alg = kzalloc(माप(*ccp_alg), GFP_KERNEL);
	अगर (!ccp_alg)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ccp_alg->entry);

	ccp_alg->mode = def->mode;

	/* Copy the शेषs and override as necessary */
	alg = &ccp_alg->alg;
	*alg = *def->alg_शेषs;
	snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->driver_name);
	alg->base.cra_blocksize = def->blocksize;
	alg->ivsize = def->ivsize;

	ret = crypto_रेजिस्टर_skcipher(alg);
	अगर (ret) अणु
		pr_err("%s skcipher algorithm registration error (%d)\n",
		       alg->base.cra_name, ret);
		kमुक्त(ccp_alg);
		वापस ret;
	पूर्ण

	list_add(&ccp_alg->entry, head);

	वापस 0;
पूर्ण

पूर्णांक ccp_रेजिस्टर_aes_algs(काष्ठा list_head *head)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक ccpversion = ccp_version();

	क्रम (i = 0; i < ARRAY_SIZE(aes_algs); i++) अणु
		अगर (aes_algs[i].version > ccpversion)
			जारी;
		ret = ccp_रेजिस्टर_aes_alg(head, &aes_algs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
