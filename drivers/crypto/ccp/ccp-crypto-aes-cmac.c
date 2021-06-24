<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) AES CMAC crypto API support
 *
 * Copyright (C) 2013,2018 Advanced Micro Devices, Inc.
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
#समावेश <crypto/hash.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "ccp-crypto.h"

अटल पूर्णांक ccp_aes_cmac_complete(काष्ठा crypto_async_request *async_req,
				 पूर्णांक ret)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(async_req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ccp_aes_cmac_req_ctx *rctx = ahash_request_ctx(req);
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
		स_नकल(req->result, rctx->iv, digest_size);

e_मुक्त:
	sg_मुक्त_table(&rctx->data_sg);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_करो_cmac_update(काष्ठा ahash_request *req, अचिन्हित पूर्णांक nbytes,
			      अचिन्हित पूर्णांक final)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ccp_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ccp_aes_cmac_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा scatterlist *sg, *cmac_key_sg = शून्य;
	अचिन्हित पूर्णांक block_size =
		crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	अचिन्हित पूर्णांक need_pad, sg_count;
	gfp_t gfp;
	u64 len;
	पूर्णांक ret;

	अगर (!ctx->u.aes.key_len)
		वापस -EINVAL;

	अगर (nbytes)
		rctx->null_msg = 0;

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

	अगर (final && (rctx->null_msg || (len & (block_size - 1))))
		need_pad = 1;
	अन्यथा
		need_pad = 0;

	sg_init_one(&rctx->iv_sg, rctx->iv, माप(rctx->iv));

	/* Build the data scatterlist table - allocate enough entries क्रम all
	 * possible data pieces (buffer, input data, padding)
	 */
	sg_count = (nbytes) ? sg_nents(req->src) + 2 : 2;
	gfp = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ?
		GFP_KERNEL : GFP_ATOMIC;
	ret = sg_alloc_table(&rctx->data_sg, sg_count, gfp);
	अगर (ret)
		वापस ret;

	sg = शून्य;
	अगर (rctx->buf_count) अणु
		sg_init_one(&rctx->buf_sg, rctx->buf, rctx->buf_count);
		sg = ccp_crypto_sg_table_add(&rctx->data_sg, &rctx->buf_sg);
		अगर (!sg) अणु
			ret = -EINVAL;
			जाओ e_मुक्त;
		पूर्ण
	पूर्ण

	अगर (nbytes) अणु
		sg = ccp_crypto_sg_table_add(&rctx->data_sg, req->src);
		अगर (!sg) अणु
			ret = -EINVAL;
			जाओ e_मुक्त;
		पूर्ण
	पूर्ण

	अगर (need_pad) अणु
		पूर्णांक pad_length = block_size - (len & (block_size - 1));

		rctx->hash_cnt += pad_length;

		स_रखो(rctx->pad, 0, माप(rctx->pad));
		rctx->pad[0] = 0x80;
		sg_init_one(&rctx->pad_sg, rctx->pad, pad_length);
		sg = ccp_crypto_sg_table_add(&rctx->data_sg, &rctx->pad_sg);
		अगर (!sg) अणु
			ret = -EINVAL;
			जाओ e_मुक्त;
		पूर्ण
	पूर्ण
	अगर (sg) अणु
		sg_mark_end(sg);
		sg = rctx->data_sg.sgl;
	पूर्ण

	/* Initialize the K1/K2 scatterlist */
	अगर (final)
		cmac_key_sg = (need_pad) ? &ctx->u.aes.k2_sg
					 : &ctx->u.aes.k1_sg;

	स_रखो(&rctx->cmd, 0, माप(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_AES;
	rctx->cmd.u.aes.type = ctx->u.aes.type;
	rctx->cmd.u.aes.mode = ctx->u.aes.mode;
	rctx->cmd.u.aes.action = CCP_AES_ACTION_ENCRYPT;
	rctx->cmd.u.aes.key = &ctx->u.aes.key_sg;
	rctx->cmd.u.aes.key_len = ctx->u.aes.key_len;
	rctx->cmd.u.aes.iv = &rctx->iv_sg;
	rctx->cmd.u.aes.iv_len = AES_BLOCK_SIZE;
	rctx->cmd.u.aes.src = sg;
	rctx->cmd.u.aes.src_len = rctx->hash_cnt;
	rctx->cmd.u.aes.dst = शून्य;
	rctx->cmd.u.aes.cmac_key = cmac_key_sg;
	rctx->cmd.u.aes.cmac_key_len = ctx->u.aes.kn_len;
	rctx->cmd.u.aes.cmac_final = final;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	वापस ret;

e_मुक्त:
	sg_मुक्त_table(&rctx->data_sg);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_aes_cmac_init(काष्ठा ahash_request *req)
अणु
	काष्ठा ccp_aes_cmac_req_ctx *rctx = ahash_request_ctx(req);

	स_रखो(rctx, 0, माप(*rctx));

	rctx->null_msg = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_cmac_update(काष्ठा ahash_request *req)
अणु
	वापस ccp_करो_cmac_update(req, req->nbytes, 0);
पूर्ण

अटल पूर्णांक ccp_aes_cmac_final(काष्ठा ahash_request *req)
अणु
	वापस ccp_करो_cmac_update(req, 0, 1);
पूर्ण

अटल पूर्णांक ccp_aes_cmac_finup(काष्ठा ahash_request *req)
अणु
	वापस ccp_करो_cmac_update(req, req->nbytes, 1);
पूर्ण

अटल पूर्णांक ccp_aes_cmac_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret;

	ret = ccp_aes_cmac_init(req);
	अगर (ret)
		वापस ret;

	वापस ccp_aes_cmac_finup(req);
पूर्ण

अटल पूर्णांक ccp_aes_cmac_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा ccp_aes_cmac_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा ccp_aes_cmac_exp_ctx state;

	/* Don't let anything leak to 'out' */
	स_रखो(&state, 0, माप(state));

	state.null_msg = rctx->null_msg;
	स_नकल(state.iv, rctx->iv, माप(state.iv));
	state.buf_count = rctx->buf_count;
	स_नकल(state.buf, rctx->buf, माप(state.buf));

	/* 'out' may not be aligned so स_नकल from local variable */
	स_नकल(out, &state, माप(state));

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_cmac_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा ccp_aes_cmac_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा ccp_aes_cmac_exp_ctx state;

	/* 'in' may not be aligned so स_नकल to local variable */
	स_नकल(&state, in, माप(state));

	स_रखो(rctx, 0, माप(*rctx));
	rctx->null_msg = state.null_msg;
	स_नकल(rctx->iv, state.iv, माप(rctx->iv));
	rctx->buf_count = state.buf_count;
	स_नकल(rctx->buf, state.buf, माप(rctx->buf));

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_aes_cmac_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	काष्ठा ccp_crypto_ahash_alg *alg =
		ccp_crypto_ahash_alg(crypto_ahash_tfm(tfm));
	u64 k0_hi, k0_lo, k1_hi, k1_lo, k2_hi, k2_lo;
	u64 rb_hi = 0x00, rb_lo = 0x87;
	काष्ठा crypto_aes_ctx aes;
	__be64 *gk;
	पूर्णांक ret;

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

	/* Set to zero until complete */
	ctx->u.aes.key_len = 0;

	/* Set the key क्रम the AES cipher used to generate the keys */
	ret = aes_expandkey(&aes, key, key_len);
	अगर (ret)
		वापस ret;

	/* Encrypt a block of zeroes - use key area in context */
	स_रखो(ctx->u.aes.key, 0, माप(ctx->u.aes.key));
	aes_encrypt(&aes, ctx->u.aes.key, ctx->u.aes.key);
	memzero_explicit(&aes, माप(aes));

	/* Generate K1 and K2 */
	k0_hi = be64_to_cpu(*((__be64 *)ctx->u.aes.key));
	k0_lo = be64_to_cpu(*((__be64 *)ctx->u.aes.key + 1));

	k1_hi = (k0_hi << 1) | (k0_lo >> 63);
	k1_lo = k0_lo << 1;
	अगर (ctx->u.aes.key[0] & 0x80) अणु
		k1_hi ^= rb_hi;
		k1_lo ^= rb_lo;
	पूर्ण
	gk = (__be64 *)ctx->u.aes.k1;
	*gk = cpu_to_be64(k1_hi);
	gk++;
	*gk = cpu_to_be64(k1_lo);

	k2_hi = (k1_hi << 1) | (k1_lo >> 63);
	k2_lo = k1_lo << 1;
	अगर (ctx->u.aes.k1[0] & 0x80) अणु
		k2_hi ^= rb_hi;
		k2_lo ^= rb_lo;
	पूर्ण
	gk = (__be64 *)ctx->u.aes.k2;
	*gk = cpu_to_be64(k2_hi);
	gk++;
	*gk = cpu_to_be64(k2_lo);

	ctx->u.aes.kn_len = माप(ctx->u.aes.k1);
	sg_init_one(&ctx->u.aes.k1_sg, ctx->u.aes.k1, माप(ctx->u.aes.k1));
	sg_init_one(&ctx->u.aes.k2_sg, ctx->u.aes.k2, माप(ctx->u.aes.k2));

	/* Save the supplied key */
	स_रखो(ctx->u.aes.key, 0, माप(ctx->u.aes.key));
	स_नकल(ctx->u.aes.key, key, key_len);
	ctx->u.aes.key_len = key_len;
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_len);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_aes_cmac_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);

	ctx->complete = ccp_aes_cmac_complete;
	ctx->u.aes.key_len = 0;

	crypto_ahash_set_reqsize(ahash, माप(काष्ठा ccp_aes_cmac_req_ctx));

	वापस 0;
पूर्ण

पूर्णांक ccp_रेजिस्टर_aes_cmac_algs(काष्ठा list_head *head)
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
	ccp_alg->mode = CCP_AES_MODE_CMAC;

	alg = &ccp_alg->alg;
	alg->init = ccp_aes_cmac_init;
	alg->update = ccp_aes_cmac_update;
	alg->final = ccp_aes_cmac_final;
	alg->finup = ccp_aes_cmac_finup;
	alg->digest = ccp_aes_cmac_digest;
	alg->export = ccp_aes_cmac_export;
	alg->import = ccp_aes_cmac_import;
	alg->setkey = ccp_aes_cmac_setkey;

	halg = &alg->halg;
	halg->digestsize = AES_BLOCK_SIZE;
	halg->statesize = माप(काष्ठा ccp_aes_cmac_exp_ctx);

	base = &halg->base;
	snम_लिखो(base->cra_name, CRYPTO_MAX_ALG_NAME, "cmac(aes)");
	snम_लिखो(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "cmac-aes-ccp");
	base->cra_flags = CRYPTO_ALG_ASYNC |
			  CRYPTO_ALG_ALLOCATES_MEMORY |
			  CRYPTO_ALG_KERN_DRIVER_ONLY |
			  CRYPTO_ALG_NEED_FALLBACK;
	base->cra_blocksize = AES_BLOCK_SIZE;
	base->cra_ctxsize = माप(काष्ठा ccp_ctx);
	base->cra_priority = CCP_CRA_PRIORITY;
	base->cra_init = ccp_aes_cmac_cra_init;
	base->cra_module = THIS_MODULE;

	ret = crypto_रेजिस्टर_ahash(alg);
	अगर (ret) अणु
		pr_err("%s ahash algorithm registration error (%d)\n",
		       base->cra_name, ret);
		kमुक्त(ccp_alg);
		वापस ret;
	पूर्ण

	list_add(&ccp_alg->entry, head);

	वापस 0;
पूर्ण
