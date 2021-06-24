<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) DES3 crypto API support
 *
 * Copyright (C) 2016,2017 Advanced Micro Devices, Inc.
 *
 * Author: Gary R Hook <ghook@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/des.h>

#समावेश "ccp-crypto.h"

अटल पूर्णांक ccp_des3_complete(काष्ठा crypto_async_request *async_req, पूर्णांक ret)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(async_req);
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा ccp_des3_req_ctx *rctx = skcipher_request_ctx(req);

	अगर (ret)
		वापस ret;

	अगर (ctx->u.des3.mode != CCP_DES3_MODE_ECB)
		स_नकल(req->iv, rctx->iv, DES3_EDE_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_des3_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
		अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ccp_crypto_skcipher_alg *alg = ccp_crypto_skcipher_alg(tfm);
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(tfm, key);
	अगर (err)
		वापस err;

	/* It's not clear that there is any support क्रम a keysize of 112.
	 * If needed, the caller should make K1 == K3
	 */
	ctx->u.des3.type = CCP_DES3_TYPE_168;
	ctx->u.des3.mode = alg->mode;
	ctx->u.des3.key_len = key_len;

	स_नकल(ctx->u.des3.key, key, key_len);
	sg_init_one(&ctx->u.des3.key_sg, ctx->u.des3.key, key_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_des3_crypt(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा ccp_des3_req_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा scatterlist *iv_sg = शून्य;
	अचिन्हित पूर्णांक iv_len = 0;
	पूर्णांक ret;

	अगर (!ctx->u.des3.key_len)
		वापस -EINVAL;

	अगर (((ctx->u.des3.mode == CCP_DES3_MODE_ECB) ||
	     (ctx->u.des3.mode == CCP_DES3_MODE_CBC)) &&
	    (req->cryptlen & (DES3_EDE_BLOCK_SIZE - 1)))
		वापस -EINVAL;

	अगर (ctx->u.des3.mode != CCP_DES3_MODE_ECB) अणु
		अगर (!req->iv)
			वापस -EINVAL;

		स_नकल(rctx->iv, req->iv, DES3_EDE_BLOCK_SIZE);
		iv_sg = &rctx->iv_sg;
		iv_len = DES3_EDE_BLOCK_SIZE;
		sg_init_one(iv_sg, rctx->iv, iv_len);
	पूर्ण

	स_रखो(&rctx->cmd, 0, माप(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_DES3;
	rctx->cmd.u.des3.type = ctx->u.des3.type;
	rctx->cmd.u.des3.mode = ctx->u.des3.mode;
	rctx->cmd.u.des3.action = (encrypt)
				  ? CCP_DES3_ACTION_ENCRYPT
				  : CCP_DES3_ACTION_DECRYPT;
	rctx->cmd.u.des3.key = &ctx->u.des3.key_sg;
	rctx->cmd.u.des3.key_len = ctx->u.des3.key_len;
	rctx->cmd.u.des3.iv = iv_sg;
	rctx->cmd.u.des3.iv_len = iv_len;
	rctx->cmd.u.des3.src = req->src;
	rctx->cmd.u.des3.src_len = req->cryptlen;
	rctx->cmd.u.des3.dst = req->dst;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_des3_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ccp_des3_crypt(req, true);
पूर्ण

अटल पूर्णांक ccp_des3_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ccp_des3_crypt(req, false);
पूर्ण

अटल पूर्णांक ccp_des3_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->complete = ccp_des3_complete;
	ctx->u.des3.key_len = 0;

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा ccp_des3_req_ctx));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा skcipher_alg ccp_des3_शेषs = अणु
	.setkey			= ccp_des3_setkey,
	.encrypt		= ccp_des3_encrypt,
	.decrypt		= ccp_des3_decrypt,
	.min_keysize		= DES3_EDE_KEY_SIZE,
	.max_keysize		= DES3_EDE_KEY_SIZE,
	.init			= ccp_des3_init_tfm,

	.base.cra_flags		= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा ccp_ctx),
	.base.cra_priority	= CCP_CRA_PRIORITY,
	.base.cra_module	= THIS_MODULE,
पूर्ण;

काष्ठा ccp_des3_def अणु
	क्रमागत ccp_des3_mode mode;
	अचिन्हित पूर्णांक version;
	स्थिर अक्षर *name;
	स्थिर अक्षर *driver_name;
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक ivsize;
	स्थिर काष्ठा skcipher_alg *alg_शेषs;
पूर्ण;

अटल स्थिर काष्ठा ccp_des3_def des3_algs[] = अणु
	अणु
		.mode		= CCP_DES3_MODE_ECB,
		.version	= CCP_VERSION(5, 0),
		.name		= "ecb(des3_ede)",
		.driver_name	= "ecb-des3-ccp",
		.blocksize	= DES3_EDE_BLOCK_SIZE,
		.ivsize		= 0,
		.alg_शेषs	= &ccp_des3_शेषs,
	पूर्ण,
	अणु
		.mode		= CCP_DES3_MODE_CBC,
		.version	= CCP_VERSION(5, 0),
		.name		= "cbc(des3_ede)",
		.driver_name	= "cbc-des3-ccp",
		.blocksize	= DES3_EDE_BLOCK_SIZE,
		.ivsize		= DES3_EDE_BLOCK_SIZE,
		.alg_शेषs	= &ccp_des3_शेषs,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ccp_रेजिस्टर_des3_alg(काष्ठा list_head *head,
				 स्थिर काष्ठा ccp_des3_def *def)
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

पूर्णांक ccp_रेजिस्टर_des3_algs(काष्ठा list_head *head)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक ccpversion = ccp_version();

	क्रम (i = 0; i < ARRAY_SIZE(des3_algs); i++) अणु
		अगर (des3_algs[i].version > ccpversion)
			जारी;
		ret = ccp_रेजिस्टर_des3_alg(head, &des3_algs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
