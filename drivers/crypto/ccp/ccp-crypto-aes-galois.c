<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) AES GCM crypto API support
 *
 * Copyright (C) 2016,2017 Advanced Micro Devices, Inc.
 *
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "ccp-crypto.h"

अटल पूर्णांक ccp_aes_gcm_complete(काष्ठा crypto_async_request *async_req, पूर्णांक ret)
अणु
	वापस ret;
पूर्ण

अटल पूर्णांक ccp_aes_gcm_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ccp_ctx *ctx = crypto_aead_ctx(tfm);

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

	ctx->u.aes.mode = CCP_AES_MODE_GCM;
	ctx->u.aes.key_len = key_len;

	स_नकल(ctx->u.aes.key, key, key_len);
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_len);

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_gcm_setauthsize(काष्ठा crypto_aead *tfm,
				   अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 16:
	हाल 15:
	हाल 14:
	हाल 13:
	हाल 12:
	हाल 8:
	हाल 4:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_gcm_crypt(काष्ठा aead_request *req, bool encrypt)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा ccp_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा ccp_aes_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा scatterlist *iv_sg = शून्य;
	अचिन्हित पूर्णांक iv_len = 0;
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!ctx->u.aes.key_len)
		वापस -EINVAL;

	अगर (ctx->u.aes.mode != CCP_AES_MODE_GCM)
		वापस -EINVAL;

	अगर (!req->iv)
		वापस -EINVAL;

	/*
	 * 5 parts:
	 *   plaपूर्णांकext/ciphertext input
	 *   AAD
	 *   key
	 *   IV
	 *   Destination+tag buffer
	 */

	/* Prepare the IV: 12 bytes + an पूर्णांकeger (counter) */
	स_नकल(rctx->iv, req->iv, GCM_AES_IV_SIZE);
	क्रम (i = 0; i < 3; i++)
		rctx->iv[i + GCM_AES_IV_SIZE] = 0;
	rctx->iv[AES_BLOCK_SIZE - 1] = 1;

	/* Set up a scatterlist क्रम the IV */
	iv_sg = &rctx->iv_sg;
	iv_len = AES_BLOCK_SIZE;
	sg_init_one(iv_sg, rctx->iv, iv_len);

	/* The AAD + plaपूर्णांकext are concatenated in the src buffer */
	स_रखो(&rctx->cmd, 0, माप(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_AES;
	rctx->cmd.u.aes.authsize = crypto_aead_authsize(tfm);
	rctx->cmd.u.aes.type = ctx->u.aes.type;
	rctx->cmd.u.aes.mode = ctx->u.aes.mode;
	rctx->cmd.u.aes.action = encrypt;
	rctx->cmd.u.aes.key = &ctx->u.aes.key_sg;
	rctx->cmd.u.aes.key_len = ctx->u.aes.key_len;
	rctx->cmd.u.aes.iv = iv_sg;
	rctx->cmd.u.aes.iv_len = iv_len;
	rctx->cmd.u.aes.src = req->src;
	rctx->cmd.u.aes.src_len = req->cryptlen;
	rctx->cmd.u.aes.aad_len = req->assoclen;

	/* The cipher text + the tag are in the dst buffer */
	rctx->cmd.u.aes.dst = req->dst;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_aes_gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस ccp_aes_gcm_crypt(req, CCP_AES_ACTION_ENCRYPT);
पूर्ण

अटल पूर्णांक ccp_aes_gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस ccp_aes_gcm_crypt(req, CCP_AES_ACTION_DECRYPT);
पूर्ण

अटल पूर्णांक ccp_aes_gcm_cra_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_aead_ctx(tfm);

	ctx->complete = ccp_aes_gcm_complete;
	ctx->u.aes.key_len = 0;

	crypto_aead_set_reqsize(tfm, माप(काष्ठा ccp_aes_req_ctx));

	वापस 0;
पूर्ण

अटल व्योम ccp_aes_gcm_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
पूर्ण

अटल काष्ठा aead_alg ccp_aes_gcm_शेषs = अणु
	.setkey = ccp_aes_gcm_setkey,
	.setauthsize = ccp_aes_gcm_setauthsize,
	.encrypt = ccp_aes_gcm_encrypt,
	.decrypt = ccp_aes_gcm_decrypt,
	.init = ccp_aes_gcm_cra_init,
	.ivsize = GCM_AES_IV_SIZE,
	.maxauthsize = AES_BLOCK_SIZE,
	.base = अणु
		.cra_flags	= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize	= AES_BLOCK_SIZE,
		.cra_ctxsize	= माप(काष्ठा ccp_ctx),
		.cra_priority	= CCP_CRA_PRIORITY,
		.cra_निकास	= ccp_aes_gcm_cra_निकास,
		.cra_module	= THIS_MODULE,
	पूर्ण,
पूर्ण;

काष्ठा ccp_aes_aead_def अणु
	क्रमागत ccp_aes_mode mode;
	अचिन्हित पूर्णांक version;
	स्थिर अक्षर *name;
	स्थिर अक्षर *driver_name;
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक ivsize;
	काष्ठा aead_alg *alg_शेषs;
पूर्ण;

अटल काष्ठा ccp_aes_aead_def aes_aead_algs[] = अणु
	अणु
		.mode		= CCP_AES_MODE_GHASH,
		.version	= CCP_VERSION(5, 0),
		.name		= "gcm(aes)",
		.driver_name	= "gcm-aes-ccp",
		.blocksize	= 1,
		.ivsize		= AES_BLOCK_SIZE,
		.alg_शेषs	= &ccp_aes_gcm_शेषs,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ccp_रेजिस्टर_aes_aead(काष्ठा list_head *head,
				 स्थिर काष्ठा ccp_aes_aead_def *def)
अणु
	काष्ठा ccp_crypto_aead *ccp_aead;
	काष्ठा aead_alg *alg;
	पूर्णांक ret;

	ccp_aead = kzalloc(माप(*ccp_aead), GFP_KERNEL);
	अगर (!ccp_aead)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ccp_aead->entry);

	ccp_aead->mode = def->mode;

	/* Copy the शेषs and override as necessary */
	alg = &ccp_aead->alg;
	*alg = *def->alg_शेषs;
	snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->driver_name);
	alg->base.cra_blocksize = def->blocksize;

	ret = crypto_रेजिस्टर_aead(alg);
	अगर (ret) अणु
		pr_err("%s aead algorithm registration error (%d)\n",
		       alg->base.cra_name, ret);
		kमुक्त(ccp_aead);
		वापस ret;
	पूर्ण

	list_add(&ccp_aead->entry, head);

	वापस 0;
पूर्ण

पूर्णांक ccp_रेजिस्टर_aes_aeads(काष्ठा list_head *head)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक ccpversion = ccp_version();

	क्रम (i = 0; i < ARRAY_SIZE(aes_aead_algs); i++) अणु
		अगर (aes_aead_algs[i].version > ccpversion)
			जारी;
		ret = ccp_रेजिस्टर_aes_aead(head, &aes_aead_algs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
