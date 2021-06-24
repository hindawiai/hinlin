<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) RSA crypto API support
 *
 * Copyright (C) 2017 Advanced Micro Devices, Inc.
 *
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/rsa.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "ccp-crypto.h"

अटल अंतरभूत काष्ठा akcipher_request *akcipher_request_cast(
	काष्ठा crypto_async_request *req)
अणु
	वापस container_of(req, काष्ठा akcipher_request, base);
पूर्ण

अटल अंतरभूत पूर्णांक ccp_copy_and_save_keypart(u8 **kpbuf, अचिन्हित पूर्णांक *kplen,
					    स्थिर u8 *buf, माप_प्रकार sz)
अणु
	पूर्णांक nskip;

	क्रम (nskip = 0; nskip < sz; nskip++)
		अगर (buf[nskip])
			अवरोध;
	*kplen = sz - nskip;
	*kpbuf = kmemdup(buf + nskip, *kplen, GFP_KERNEL);
	अगर (!*kpbuf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_rsa_complete(काष्ठा crypto_async_request *async_req, पूर्णांक ret)
अणु
	काष्ठा akcipher_request *req = akcipher_request_cast(async_req);
	काष्ठा ccp_rsa_req_ctx *rctx = akcipher_request_ctx(req);

	अगर (ret)
		वापस ret;

	req->dst_len = rctx->cmd.u.rsa.key_size >> 3;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ccp_rsa_maxsize(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ccp_ctx *ctx = akcipher_tfm_ctx(tfm);

	वापस ctx->u.rsa.n_len;
पूर्ण

अटल पूर्णांक ccp_rsa_crypt(काष्ठा akcipher_request *req, bool encrypt)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा ccp_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा ccp_rsa_req_ctx *rctx = akcipher_request_ctx(req);
	पूर्णांक ret = 0;

	स_रखो(&rctx->cmd, 0, माप(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_RSA;

	rctx->cmd.u.rsa.key_size = ctx->u.rsa.key_len; /* in bits */
	अगर (encrypt) अणु
		rctx->cmd.u.rsa.exp = &ctx->u.rsa.e_sg;
		rctx->cmd.u.rsa.exp_len = ctx->u.rsa.e_len;
	पूर्ण अन्यथा अणु
		rctx->cmd.u.rsa.exp = &ctx->u.rsa.d_sg;
		rctx->cmd.u.rsa.exp_len = ctx->u.rsa.d_len;
	पूर्ण
	rctx->cmd.u.rsa.mod = &ctx->u.rsa.n_sg;
	rctx->cmd.u.rsa.mod_len = ctx->u.rsa.n_len;
	rctx->cmd.u.rsa.src = req->src;
	rctx->cmd.u.rsa.src_len = req->src_len;
	rctx->cmd.u.rsa.dst = req->dst;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_rsa_encrypt(काष्ठा akcipher_request *req)
अणु
	वापस ccp_rsa_crypt(req, true);
पूर्ण

अटल पूर्णांक ccp_rsa_decrypt(काष्ठा akcipher_request *req)
अणु
	वापस ccp_rsa_crypt(req, false);
पूर्ण

अटल पूर्णांक ccp_check_key_length(अचिन्हित पूर्णांक len)
अणु
	/* In bits */
	अगर (len < 8 || len > 4096)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम ccp_rsa_मुक्त_key_bufs(काष्ठा ccp_ctx *ctx)
अणु
	/* Clean up old key data */
	kमुक्त_sensitive(ctx->u.rsa.e_buf);
	ctx->u.rsa.e_buf = शून्य;
	ctx->u.rsa.e_len = 0;
	kमुक्त_sensitive(ctx->u.rsa.n_buf);
	ctx->u.rsa.n_buf = शून्य;
	ctx->u.rsa.n_len = 0;
	kमुक्त_sensitive(ctx->u.rsa.d_buf);
	ctx->u.rsa.d_buf = शून्य;
	ctx->u.rsa.d_len = 0;
पूर्ण

अटल पूर्णांक ccp_rsa_setkey(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			  अचिन्हित पूर्णांक keylen, bool निजी)
अणु
	काष्ठा ccp_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा rsa_key raw_key;
	पूर्णांक ret;

	ccp_rsa_मुक्त_key_bufs(ctx);
	स_रखो(&raw_key, 0, माप(raw_key));

	/* Code borrowed from crypto/rsa.c */
	अगर (निजी)
		ret = rsa_parse_priv_key(&raw_key, key, keylen);
	अन्यथा
		ret = rsa_parse_pub_key(&raw_key, key, keylen);
	अगर (ret)
		जाओ n_key;

	ret = ccp_copy_and_save_keypart(&ctx->u.rsa.n_buf, &ctx->u.rsa.n_len,
					raw_key.n, raw_key.n_sz);
	अगर (ret)
		जाओ key_err;
	sg_init_one(&ctx->u.rsa.n_sg, ctx->u.rsa.n_buf, ctx->u.rsa.n_len);

	ctx->u.rsa.key_len = ctx->u.rsa.n_len << 3; /* convert to bits */
	अगर (ccp_check_key_length(ctx->u.rsa.key_len)) अणु
		ret = -EINVAL;
		जाओ key_err;
	पूर्ण

	ret = ccp_copy_and_save_keypart(&ctx->u.rsa.e_buf, &ctx->u.rsa.e_len,
					raw_key.e, raw_key.e_sz);
	अगर (ret)
		जाओ key_err;
	sg_init_one(&ctx->u.rsa.e_sg, ctx->u.rsa.e_buf, ctx->u.rsa.e_len);

	अगर (निजी) अणु
		ret = ccp_copy_and_save_keypart(&ctx->u.rsa.d_buf,
						&ctx->u.rsa.d_len,
						raw_key.d, raw_key.d_sz);
		अगर (ret)
			जाओ key_err;
		sg_init_one(&ctx->u.rsa.d_sg,
			    ctx->u.rsa.d_buf, ctx->u.rsa.d_len);
	पूर्ण

	वापस 0;

key_err:
	ccp_rsa_मुक्त_key_bufs(ctx);

n_key:
	वापस ret;
पूर्ण

अटल पूर्णांक ccp_rsa_setprivkey(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	वापस ccp_rsa_setkey(tfm, key, keylen, true);
पूर्ण

अटल पूर्णांक ccp_rsa_setpubkey(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	वापस ccp_rsa_setkey(tfm, key, keylen, false);
पूर्ण

अटल पूर्णांक ccp_rsa_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ccp_ctx *ctx = akcipher_tfm_ctx(tfm);

	akcipher_set_reqsize(tfm, माप(काष्ठा ccp_rsa_req_ctx));
	ctx->complete = ccp_rsa_complete;

	वापस 0;
पूर्ण

अटल व्योम ccp_rsa_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ccp_ctx *ctx = crypto_tfm_ctx(&tfm->base);

	ccp_rsa_मुक्त_key_bufs(ctx);
पूर्ण

अटल काष्ठा akcipher_alg ccp_rsa_शेषs = अणु
	.encrypt = ccp_rsa_encrypt,
	.decrypt = ccp_rsa_decrypt,
	.set_pub_key = ccp_rsa_setpubkey,
	.set_priv_key = ccp_rsa_setprivkey,
	.max_size = ccp_rsa_maxsize,
	.init = ccp_rsa_init_tfm,
	.निकास = ccp_rsa_निकास_tfm,
	.base = अणु
		.cra_name = "rsa",
		.cra_driver_name = "rsa-ccp",
		.cra_priority = CCP_CRA_PRIORITY,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = 2 * माप(काष्ठा ccp_ctx),
	पूर्ण,
पूर्ण;

काष्ठा ccp_rsa_def अणु
	अचिन्हित पूर्णांक version;
	स्थिर अक्षर *name;
	स्थिर अक्षर *driver_name;
	अचिन्हित पूर्णांक reqsize;
	काष्ठा akcipher_alg *alg_शेषs;
पूर्ण;

अटल काष्ठा ccp_rsa_def rsa_algs[] = अणु
	अणु
		.version	= CCP_VERSION(3, 0),
		.name		= "rsa",
		.driver_name	= "rsa-ccp",
		.reqsize	= माप(काष्ठा ccp_rsa_req_ctx),
		.alg_शेषs	= &ccp_rsa_शेषs,
	पूर्ण
पूर्ण;

अटल पूर्णांक ccp_रेजिस्टर_rsa_alg(काष्ठा list_head *head,
			        स्थिर काष्ठा ccp_rsa_def *def)
अणु
	काष्ठा ccp_crypto_akcipher_alg *ccp_alg;
	काष्ठा akcipher_alg *alg;
	पूर्णांक ret;

	ccp_alg = kzalloc(माप(*ccp_alg), GFP_KERNEL);
	अगर (!ccp_alg)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ccp_alg->entry);

	alg = &ccp_alg->alg;
	*alg = *def->alg_शेषs;
	snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", def->name);
	snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s",
		 def->driver_name);
	ret = crypto_रेजिस्टर_akcipher(alg);
	अगर (ret) अणु
		pr_err("%s akcipher algorithm registration error (%d)\n",
		       alg->base.cra_name, ret);
		kमुक्त(ccp_alg);
		वापस ret;
	पूर्ण

	list_add(&ccp_alg->entry, head);

	वापस 0;
पूर्ण

पूर्णांक ccp_रेजिस्टर_rsa_algs(काष्ठा list_head *head)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक ccpversion = ccp_version();

	/* Register the RSA algorithm in standard mode
	 * This works क्रम CCP v3 and later
	 */
	क्रम (i = 0; i < ARRAY_SIZE(rsa_algs); i++) अणु
		अगर (rsa_algs[i].version > ccpversion)
			जारी;
		ret = ccp_रेजिस्टर_rsa_alg(head, &rsa_algs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
