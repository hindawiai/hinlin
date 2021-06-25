<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) AES XTS crypto API support
 *
 * Copyright (C) 2013,2017 Advanced Micro Devices, Inc.
 *
 * Author: Gary R Hook <gary.hook@amd.com>
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/xts.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "ccp-crypto.h"

काष्ठा ccp_aes_xts_def अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *drv_name;
पूर्ण;

अटल स्थिर काष्ठा ccp_aes_xts_def aes_xts_algs[] = अणु
	अणु
		.name		= "xts(aes)",
		.drv_name	= "xts-aes-ccp",
	पूर्ण,
पूर्ण;

काष्ठा ccp_unit_size_map अणु
	अचिन्हित पूर्णांक size;
	u32 value;
पूर्ण;

अटल काष्ठा ccp_unit_size_map xts_unit_sizes[] = अणु
	अणु
		.size   = 16,
		.value	= CCP_XTS_AES_UNIT_SIZE_16,
	पूर्ण,
	अणु
		.size   = 512,
		.value	= CCP_XTS_AES_UNIT_SIZE_512,
	पूर्ण,
	अणु
		.size   = 1024,
		.value	= CCP_XTS_AES_UNIT_SIZE_1024,
	पूर्ण,
	अणु
		.size   = 2048,
		.value	= CCP_XTS_AES_UNIT_SIZE_2048,
	पूर्ण,
	अणु
		.size   = 4096,
		.value	= CCP_XTS_AES_UNIT_SIZE_4096,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ccp_aes_xts_complete(काष्ठा crypto_async_request *async_req, पूर्णांक ret)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(async_req);
	काष्ठा ccp_aes_req_ctx *rctx = skcipher_request_ctx(req);

	अगर (ret)
		वापस ret;

	स_नकल(req->iv, rctx->iv, AES_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_xts_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);
	अचिन्हित पूर्णांक ccpversion = ccp_version();
	पूर्णांक ret;

	ret = xts_verअगरy_key(tfm, key, key_len);
	अगर (ret)
		वापस ret;

	/* Version 3 devices support 128-bit keys; version 5 devices can
	 * accommodate 128- and 256-bit keys.
	 */
	चयन (key_len) अणु
	हाल AES_KEYSIZE_128 * 2:
		स_नकल(ctx->u.aes.key, key, key_len);
		अवरोध;
	हाल AES_KEYSIZE_256 * 2:
		अगर (ccpversion > CCP_VERSION(3, 0))
			स_नकल(ctx->u.aes.key, key, key_len);
		अवरोध;
	पूर्ण
	ctx->u.aes.key_len = key_len / 2;
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_len);

	वापस crypto_skcipher_setkey(ctx->u.aes.tfm_skcipher, key, key_len);
पूर्ण

अटल पूर्णांक ccp_aes_xts_crypt(काष्ठा skcipher_request *req,
			     अचिन्हित पूर्णांक encrypt)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा ccp_aes_req_ctx *rctx = skcipher_request_ctx(req);
	अचिन्हित पूर्णांक ccpversion = ccp_version();
	अचिन्हित पूर्णांक fallback = 0;
	अचिन्हित पूर्णांक unit;
	u32 unit_size;
	पूर्णांक ret;

	अगर (!ctx->u.aes.key_len)
		वापस -EINVAL;

	अगर (!req->iv)
		वापस -EINVAL;

	/* Check conditions under which the CCP can fulfill a request. The
	 * device can handle input plaपूर्णांकext of a length that is a multiple
	 * of the unit_size, bug the crypto implementation only supports
	 * the unit_size being equal to the input length. This limits the
	 * number of scenarios we can handle.
	 */
	unit_size = CCP_XTS_AES_UNIT_SIZE__LAST;
	क्रम (unit = 0; unit < ARRAY_SIZE(xts_unit_sizes); unit++) अणु
		अगर (req->cryptlen == xts_unit_sizes[unit].size) अणु
			unit_size = unit;
			अवरोध;
		पूर्ण
	पूर्ण
	/* The CCP has restrictions on block sizes. Also, a version 3 device
	 * only supports AES-128 operations; version 5 CCPs support both
	 * AES-128 and -256 operations.
	 */
	अगर (unit_size == CCP_XTS_AES_UNIT_SIZE__LAST)
		fallback = 1;
	अगर ((ccpversion < CCP_VERSION(5, 0)) &&
	    (ctx->u.aes.key_len != AES_KEYSIZE_128))
		fallback = 1;
	अगर ((ctx->u.aes.key_len != AES_KEYSIZE_128) &&
	    (ctx->u.aes.key_len != AES_KEYSIZE_256))
		fallback = 1;
	अगर (fallback) अणु
		/* Use the fallback to process the request क्रम any
		 * unsupported unit sizes or key sizes
		 */
		skcipher_request_set_tfm(&rctx->fallback_req,
					 ctx->u.aes.tfm_skcipher);
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

	स_नकल(rctx->iv, req->iv, AES_BLOCK_SIZE);
	sg_init_one(&rctx->iv_sg, rctx->iv, AES_BLOCK_SIZE);

	स_रखो(&rctx->cmd, 0, माप(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_XTS_AES_128;
	rctx->cmd.u.xts.type = CCP_AES_TYPE_128;
	rctx->cmd.u.xts.action = (encrypt) ? CCP_AES_ACTION_ENCRYPT
					   : CCP_AES_ACTION_DECRYPT;
	rctx->cmd.u.xts.unit_size = unit_size;
	rctx->cmd.u.xts.key = &ctx->u.aes.key_sg;
	rctx->cmd.u.xts.key_len = ctx->u.aes.key_len;
	rctx->cmd.u.xts.iv = &rctx->iv_sg;
	rctx->cmd.u.xts.iv_len = AES_BLOCK_SIZE;
	rctx->cmd.u.xts.src = req->src;
	rctx->cmd.u.xts.src_len = req->cryptlen;
	rctx->cmd.u.xts.dst = req->dst;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_aes_xts_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस ccp_aes_xts_crypt(req, 1);
पूर्ण

अटल पूर्णांक ccp_aes_xts_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस ccp_aes_xts_crypt(req, 0);
पूर्ण

अटल पूर्णांक ccp_aes_xts_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *fallback_tfm;

	ctx->complete = ccp_aes_xts_complete;
	ctx->u.aes.key_len = 0;

	fallback_tfm = crypto_alloc_skcipher("xts(aes)", 0,
					     CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(fallback_tfm)) अणु
		pr_warn("could not load fallback driver xts(aes)\n");
		वापस PTR_ERR(fallback_tfm);
	पूर्ण
	ctx->u.aes.tfm_skcipher = fallback_tfm;

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा ccp_aes_req_ctx) +
					 crypto_skcipher_reqsize(fallback_tfm));

	वापस 0;
पूर्ण

अटल व्योम ccp_aes_xts_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(ctx->u.aes.tfm_skcipher);
पूर्ण

अटल पूर्णांक ccp_रेजिस्टर_aes_xts_alg(काष्ठा list_head *head,
				    स्थिर काष्ठा ccp_aes_xts_def *def)
अणु
	काष्ठा ccp_crypto_skcipher_alg *ccp_alg;
	काष्ठा skcipher_alg *alg;
	पूर्णांक ret;

	ccp_alg = kzalloc(माप(*ccp_alg), GFP_KERNEL);
	अगर (!ccp_alg)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ccp_alg->entry);

	alg = &ccp_alg->alg;

	snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->drv_name);
	alg->base.cra_flags	= CRYPTO_ALG_ASYNC |
				  CRYPTO_ALG_ALLOCATES_MEMORY |
				  CRYPTO_ALG_KERN_DRIVER_ONLY |
				  CRYPTO_ALG_NEED_FALLBACK;
	alg->base.cra_blocksize	= AES_BLOCK_SIZE;
	alg->base.cra_ctxsize	= माप(काष्ठा ccp_ctx);
	alg->base.cra_priority	= CCP_CRA_PRIORITY;
	alg->base.cra_module	= THIS_MODULE;

	alg->setkey		= ccp_aes_xts_setkey;
	alg->encrypt		= ccp_aes_xts_encrypt;
	alg->decrypt		= ccp_aes_xts_decrypt;
	alg->min_keysize	= AES_MIN_KEY_SIZE * 2;
	alg->max_keysize	= AES_MAX_KEY_SIZE * 2;
	alg->ivsize		= AES_BLOCK_SIZE;
	alg->init		= ccp_aes_xts_init_tfm;
	alg->निकास		= ccp_aes_xts_निकास_tfm;

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

पूर्णांक ccp_रेजिस्टर_aes_xts_algs(काष्ठा list_head *head)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(aes_xts_algs); i++) अणु
		ret = ccp_रेजिस्टर_aes_xts_alg(head, &aes_xts_algs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
