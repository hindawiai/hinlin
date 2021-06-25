<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) SHA crypto API support
 *
 * Copyright (C) 2013,2018 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/hmac.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/माला.स>

#समावेश "ccp-crypto.h"

अटल पूर्णांक ccp_sha_complete(काष्ठा crypto_async_request *async_req, पूर्णांक ret)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(async_req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ccp_sha_req_ctx *rctx = ahash_request_ctx(req);
	अचिन्हित पूर्णांक digest_size = crypto_ahash_digestsize(tfm);

	अगर (ret)
		जाओ e_मुक्त;

	अगर (rctx->hash_rem) अणु
		/* Save reमुख्यing data to buffer */
		अचिन्हित पूर्णांक offset = rctx->nbytes - rctx->hash_rem;

		scatterwalk_map_and_copy(rctx->buf, rctx->src,
					 offset, rctx->hash_rem, 0);
		rctx->buf_count = rctx->hash_rem;
	पूर्ण अन्यथा अणु
		rctx->buf_count = 0;
	पूर्ण

	/* Update result area अगर supplied */
	अगर (req->result && rctx->final)
		स_नकल(req->result, rctx->ctx, digest_size);

e_मुक्त:
	sg_मुक्त_table(&rctx->data_sg);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_करो_sha_update(काष्ठा ahash_request *req, अचिन्हित पूर्णांक nbytes,
			     अचिन्हित पूर्णांक final)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ccp_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ccp_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक block_size =
		crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	अचिन्हित पूर्णांक sg_count;
	gfp_t gfp;
	u64 len;
	पूर्णांक ret;

	len = (u64)rctx->buf_count + (u64)nbytes;

	अगर (!final && (len <= block_size)) अणु
		scatterwalk_map_and_copy(rctx->buf + rctx->buf_count, req->src,
					 0, nbytes, 0);
		rctx->buf_count += nbytes;

		वापस 0;
	पूर्ण

	rctx->src = req->src;
	rctx->nbytes = nbytes;

	rctx->final = final;
	rctx->hash_rem = final ? 0 : len & (block_size - 1);
	rctx->hash_cnt = len - rctx->hash_rem;
	अगर (!final && !rctx->hash_rem) अणु
		/* CCP can't करो zero length final, so keep some data around */
		rctx->hash_cnt -= block_size;
		rctx->hash_rem = block_size;
	पूर्ण

	/* Initialize the context scatterlist */
	sg_init_one(&rctx->ctx_sg, rctx->ctx, माप(rctx->ctx));

	sg = शून्य;
	अगर (rctx->buf_count && nbytes) अणु
		/* Build the data scatterlist table - allocate enough entries
		 * क्रम both data pieces (buffer and input data)
		 */
		gfp = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ?
			GFP_KERNEL : GFP_ATOMIC;
		sg_count = sg_nents(req->src) + 1;
		ret = sg_alloc_table(&rctx->data_sg, sg_count, gfp);
		अगर (ret)
			वापस ret;

		sg_init_one(&rctx->buf_sg, rctx->buf, rctx->buf_count);
		sg = ccp_crypto_sg_table_add(&rctx->data_sg, &rctx->buf_sg);
		अगर (!sg) अणु
			ret = -EINVAL;
			जाओ e_मुक्त;
		पूर्ण
		sg = ccp_crypto_sg_table_add(&rctx->data_sg, req->src);
		अगर (!sg) अणु
			ret = -EINVAL;
			जाओ e_मुक्त;
		पूर्ण
		sg_mark_end(sg);

		sg = rctx->data_sg.sgl;
	पूर्ण अन्यथा अगर (rctx->buf_count) अणु
		sg_init_one(&rctx->buf_sg, rctx->buf, rctx->buf_count);

		sg = &rctx->buf_sg;
	पूर्ण अन्यथा अगर (nbytes) अणु
		sg = req->src;
	पूर्ण

	rctx->msg_bits += (rctx->hash_cnt << 3);	/* Total in bits */

	स_रखो(&rctx->cmd, 0, माप(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_SHA;
	rctx->cmd.u.sha.type = rctx->type;
	rctx->cmd.u.sha.ctx = &rctx->ctx_sg;

	चयन (rctx->type) अणु
	हाल CCP_SHA_TYPE_1:
		rctx->cmd.u.sha.ctx_len = SHA1_DIGEST_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_224:
		rctx->cmd.u.sha.ctx_len = SHA224_DIGEST_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_256:
		rctx->cmd.u.sha.ctx_len = SHA256_DIGEST_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_384:
		rctx->cmd.u.sha.ctx_len = SHA384_DIGEST_SIZE;
		अवरोध;
	हाल CCP_SHA_TYPE_512:
		rctx->cmd.u.sha.ctx_len = SHA512_DIGEST_SIZE;
		अवरोध;
	शेष:
		/* Should never get here */
		अवरोध;
	पूर्ण

	rctx->cmd.u.sha.src = sg;
	rctx->cmd.u.sha.src_len = rctx->hash_cnt;
	rctx->cmd.u.sha.opad = ctx->u.sha.key_len ?
		&ctx->u.sha.opad_sg : शून्य;
	rctx->cmd.u.sha.opad_len = ctx->u.sha.key_len ?
		ctx->u.sha.opad_count : 0;
	rctx->cmd.u.sha.first = rctx->first;
	rctx->cmd.u.sha.final = rctx->final;
	rctx->cmd.u.sha.msg_bits = rctx->msg_bits;

	rctx->first = 0;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	वापस ret;

e_मुक्त:
	sg_मुक्त_table(&rctx->data_sg);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_sha_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ccp_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ccp_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा ccp_crypto_ahash_alg *alg =
		ccp_crypto_ahash_alg(crypto_ahash_tfm(tfm));
	अचिन्हित पूर्णांक block_size =
		crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	स_रखो(rctx, 0, माप(*rctx));

	rctx->type = alg->type;
	rctx->first = 1;

	अगर (ctx->u.sha.key_len) अणु
		/* Buffer the HMAC key क्रम first update */
		स_नकल(rctx->buf, ctx->u.sha.ipad, block_size);
		rctx->buf_count = block_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_sha_update(काष्ठा ahash_request *req)
अणु
	वापस ccp_करो_sha_update(req, req->nbytes, 0);
पूर्ण

अटल पूर्णांक ccp_sha_final(काष्ठा ahash_request *req)
अणु
	वापस ccp_करो_sha_update(req, 0, 1);
पूर्ण

अटल पूर्णांक ccp_sha_finup(काष्ठा ahash_request *req)
अणु
	वापस ccp_करो_sha_update(req, req->nbytes, 1);
पूर्ण

अटल पूर्णांक ccp_sha_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = ccp_sha_init(req);
	अगर (ret)
		वापस ret;

	वापस ccp_sha_finup(req);
पूर्ण

अटल पूर्णांक ccp_sha_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा ccp_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा ccp_sha_exp_ctx state;

	/* Don't let anything leak to 'out' */
	स_रखो(&state, 0, माप(state));

	state.type = rctx->type;
	state.msg_bits = rctx->msg_bits;
	state.first = rctx->first;
	स_नकल(state.ctx, rctx->ctx, माप(state.ctx));
	state.buf_count = rctx->buf_count;
	स_नकल(state.buf, rctx->buf, माप(state.buf));

	/* 'out' may not be aligned so स_नकल from local variable */
	स_नकल(out, &state, माप(state));

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_sha_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा ccp_sha_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा ccp_sha_exp_ctx state;

	/* 'in' may not be aligned so स_नकल to local variable */
	स_नकल(&state, in, माप(state));

	स_रखो(rctx, 0, माप(*rctx));
	rctx->type = state.type;
	rctx->msg_bits = state.msg_bits;
	rctx->first = state.first;
	स_नकल(rctx->ctx, state.ctx, माप(rctx->ctx));
	rctx->buf_count = state.buf_count;
	स_नकल(rctx->buf, state.buf, माप(rctx->buf));

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_sha_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			  अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा crypto_shash *shash = ctx->u.sha.hmac_tfm;
	अचिन्हित पूर्णांक block_size = crypto_shash_blocksize(shash);
	अचिन्हित पूर्णांक digest_size = crypto_shash_digestsize(shash);
	पूर्णांक i, ret;

	/* Set to zero until complete */
	ctx->u.sha.key_len = 0;

	/* Clear key area to provide zero padding क्रम keys smaller
	 * than the block size
	 */
	स_रखो(ctx->u.sha.key, 0, माप(ctx->u.sha.key));

	अगर (key_len > block_size) अणु
		/* Must hash the input key */
		ret = crypto_shash_tfm_digest(shash, key, key_len,
					      ctx->u.sha.key);
		अगर (ret)
			वापस -EINVAL;

		key_len = digest_size;
	पूर्ण अन्यथा अणु
		स_नकल(ctx->u.sha.key, key, key_len);
	पूर्ण

	क्रम (i = 0; i < block_size; i++) अणु
		ctx->u.sha.ipad[i] = ctx->u.sha.key[i] ^ HMAC_IPAD_VALUE;
		ctx->u.sha.opad[i] = ctx->u.sha.key[i] ^ HMAC_OPAD_VALUE;
	पूर्ण

	sg_init_one(&ctx->u.sha.opad_sg, ctx->u.sha.opad, block_size);
	ctx->u.sha.opad_count = block_size;

	ctx->u.sha.key_len = key_len;

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_sha_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);

	ctx->complete = ccp_sha_complete;
	ctx->u.sha.key_len = 0;

	crypto_ahash_set_reqsize(ahash, माप(काष्ठा ccp_sha_req_ctx));

	वापस 0;
पूर्ण

अटल व्योम ccp_sha_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
पूर्ण

अटल पूर्णांक ccp_hmac_sha_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा ccp_crypto_ahash_alg *alg = ccp_crypto_ahash_alg(tfm);
	काष्ठा crypto_shash *hmac_tfm;

	hmac_tfm = crypto_alloc_shash(alg->child_alg, 0, 0);
	अगर (IS_ERR(hmac_tfm)) अणु
		pr_warn("could not load driver %s need for HMAC support\n",
			alg->child_alg);
		वापस PTR_ERR(hmac_tfm);
	पूर्ण

	ctx->u.sha.hmac_tfm = hmac_tfm;

	वापस ccp_sha_cra_init(tfm);
पूर्ण

अटल व्योम ccp_hmac_sha_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (ctx->u.sha.hmac_tfm)
		crypto_मुक्त_shash(ctx->u.sha.hmac_tfm);

	ccp_sha_cra_निकास(tfm);
पूर्ण

काष्ठा ccp_sha_def अणु
	अचिन्हित पूर्णांक version;
	स्थिर अक्षर *name;
	स्थिर अक्षर *drv_name;
	क्रमागत ccp_sha_type type;
	u32 digest_size;
	u32 block_size;
पूर्ण;

अटल काष्ठा ccp_sha_def sha_algs[] = अणु
	अणु
		.version	= CCP_VERSION(3, 0),
		.name		= "sha1",
		.drv_name	= "sha1-ccp",
		.type		= CCP_SHA_TYPE_1,
		.digest_size	= SHA1_DIGEST_SIZE,
		.block_size	= SHA1_BLOCK_SIZE,
	पूर्ण,
	अणु
		.version	= CCP_VERSION(3, 0),
		.name		= "sha224",
		.drv_name	= "sha224-ccp",
		.type		= CCP_SHA_TYPE_224,
		.digest_size	= SHA224_DIGEST_SIZE,
		.block_size	= SHA224_BLOCK_SIZE,
	पूर्ण,
	अणु
		.version	= CCP_VERSION(3, 0),
		.name		= "sha256",
		.drv_name	= "sha256-ccp",
		.type		= CCP_SHA_TYPE_256,
		.digest_size	= SHA256_DIGEST_SIZE,
		.block_size	= SHA256_BLOCK_SIZE,
	पूर्ण,
	अणु
		.version	= CCP_VERSION(5, 0),
		.name		= "sha384",
		.drv_name	= "sha384-ccp",
		.type		= CCP_SHA_TYPE_384,
		.digest_size	= SHA384_DIGEST_SIZE,
		.block_size	= SHA384_BLOCK_SIZE,
	पूर्ण,
	अणु
		.version	= CCP_VERSION(5, 0),
		.name		= "sha512",
		.drv_name	= "sha512-ccp",
		.type		= CCP_SHA_TYPE_512,
		.digest_size	= SHA512_DIGEST_SIZE,
		.block_size	= SHA512_BLOCK_SIZE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ccp_रेजिस्टर_hmac_alg(काष्ठा list_head *head,
				 स्थिर काष्ठा ccp_sha_def *def,
				 स्थिर काष्ठा ccp_crypto_ahash_alg *base_alg)
अणु
	काष्ठा ccp_crypto_ahash_alg *ccp_alg;
	काष्ठा ahash_alg *alg;
	काष्ठा hash_alg_common *halg;
	काष्ठा crypto_alg *base;
	पूर्णांक ret;

	ccp_alg = kzalloc(माप(*ccp_alg), GFP_KERNEL);
	अगर (!ccp_alg)
		वापस -ENOMEM;

	/* Copy the base algorithm and only change what's necessary */
	*ccp_alg = *base_alg;
	INIT_LIST_HEAD(&ccp_alg->entry);

	strscpy(ccp_alg->child_alg, def->name, CRYPTO_MAX_ALG_NAME);

	alg = &ccp_alg->alg;
	alg->setkey = ccp_sha_setkey;

	halg = &alg->halg;

	base = &halg->base;
	snम_लिखो(base->cra_name, CRYPTO_MAX_ALG_NAME, "hmac(%s)", def->name);
	snम_लिखो(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "hmac-%s",
		 def->drv_name);
	base->cra_init = ccp_hmac_sha_cra_init;
	base->cra_निकास = ccp_hmac_sha_cra_निकास;

	ret = crypto_रेजिस्टर_ahash(alg);
	अगर (ret) अणु
		pr_err("%s ahash algorithm registration error (%d)\n",
		       base->cra_name, ret);
		kमुक्त(ccp_alg);
		वापस ret;
	पूर्ण

	list_add(&ccp_alg->entry, head);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_रेजिस्टर_sha_alg(काष्ठा list_head *head,
				स्थिर काष्ठा ccp_sha_def *def)
अणु
	काष्ठा ccp_crypto_ahash_alg *ccp_alg;
	काष्ठा ahash_alg *alg;
	काष्ठा hash_alg_common *halg;
	काष्ठा crypto_alg *base;
	पूर्णांक ret;

	ccp_alg = kzalloc(माप(*ccp_alg), GFP_KERNEL);
	अगर (!ccp_alg)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ccp_alg->entry);

	ccp_alg->type = def->type;

	alg = &ccp_alg->alg;
	alg->init = ccp_sha_init;
	alg->update = ccp_sha_update;
	alg->final = ccp_sha_final;
	alg->finup = ccp_sha_finup;
	alg->digest = ccp_sha_digest;
	alg->export = ccp_sha_export;
	alg->import = ccp_sha_import;

	halg = &alg->halg;
	halg->digestsize = def->digest_size;
	halg->statesize = माप(काष्ठा ccp_sha_exp_ctx);

	base = &halg->base;
	snम_लिखो(base->cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snम_लिखो(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->drv_name);
	base->cra_flags = CRYPTO_ALG_ASYNC |
			  CRYPTO_ALG_ALLOCATES_MEMORY |
			  CRYPTO_ALG_KERN_DRIVER_ONLY |
			  CRYPTO_ALG_NEED_FALLBACK;
	base->cra_blocksize = def->block_size;
	base->cra_ctxsize = माप(काष्ठा ccp_ctx);
	base->cra_priority = CCP_CRA_PRIORITY;
	base->cra_init = ccp_sha_cra_init;
	base->cra_निकास = ccp_sha_cra_निकास;
	base->cra_module = THIS_MODULE;

	ret = crypto_रेजिस्टर_ahash(alg);
	अगर (ret) अणु
		pr_err("%s ahash algorithm registration error (%d)\n",
		       base->cra_name, ret);
		kमुक्त(ccp_alg);
		वापस ret;
	पूर्ण

	list_add(&ccp_alg->entry, head);

	ret = ccp_रेजिस्टर_hmac_alg(head, def, ccp_alg);

	वापस ret;
पूर्ण

पूर्णांक ccp_रेजिस्टर_sha_algs(काष्ठा list_head *head)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक ccpversion = ccp_version();

	क्रम (i = 0; i < ARRAY_SIZE(sha_algs); i++) अणु
		अगर (sha_algs[i].version > ccpversion)
			जारी;
		ret = ccp_रेजिस्टर_sha_alg(head, &sha_algs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
