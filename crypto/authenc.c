<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Authenc: Simple AEAD wrapper क्रम IPsec
 *
 * Copyright (c) 2007-2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/null.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

काष्ठा authenc_instance_ctx अणु
	काष्ठा crypto_ahash_spawn auth;
	काष्ठा crypto_skcipher_spawn enc;
	अचिन्हित पूर्णांक reqoff;
पूर्ण;

काष्ठा crypto_authenc_ctx अणु
	काष्ठा crypto_ahash *auth;
	काष्ठा crypto_skcipher *enc;
	काष्ठा crypto_sync_skcipher *null;
पूर्ण;

काष्ठा authenc_request_ctx अणु
	काष्ठा scatterlist src[2];
	काष्ठा scatterlist dst[2];
	अक्षर tail[];
पूर्ण;

अटल व्योम authenc_request_complete(काष्ठा aead_request *req, पूर्णांक err)
अणु
	अगर (err != -EINPROGRESS)
		aead_request_complete(req, err);
पूर्ण

पूर्णांक crypto_authenc_extractkeys(काष्ठा crypto_authenc_keys *keys, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा rtattr *rta = (काष्ठा rtattr *)key;
	काष्ठा crypto_authenc_key_param *param;

	अगर (!RTA_OK(rta, keylen))
		वापस -EINVAL;
	अगर (rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
		वापस -EINVAL;

	/*
	 * RTA_OK() didn't align the rtattr's payload when validating that it
	 * fits in the buffer.  Yet, the keys should start on the next 4-byte
	 * aligned boundary.  To aव्योम confusion, require that the rtattr
	 * payload be exactly the param काष्ठा, which has a 4-byte aligned size.
	 */
	अगर (RTA_PAYLOAD(rta) != माप(*param))
		वापस -EINVAL;
	BUILD_BUG_ON(माप(*param) % RTA_ALIGNTO);

	param = RTA_DATA(rta);
	keys->enckeylen = be32_to_cpu(param->enckeylen);

	key += rta->rta_len;
	keylen -= rta->rta_len;

	अगर (keylen < keys->enckeylen)
		वापस -EINVAL;

	keys->authkeylen = keylen - keys->enckeylen;
	keys->authkey = key;
	keys->enckey = key + keys->authkeylen;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_authenc_extractkeys);

अटल पूर्णांक crypto_authenc_setkey(काष्ठा crypto_aead *authenc, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा crypto_ahash *auth = ctx->auth;
	काष्ठा crypto_skcipher *enc = ctx->enc;
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक err = -EINVAL;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		जाओ out;

	crypto_ahash_clear_flags(auth, CRYPTO_TFM_REQ_MASK);
	crypto_ahash_set_flags(auth, crypto_aead_get_flags(authenc) &
				    CRYPTO_TFM_REQ_MASK);
	err = crypto_ahash_setkey(auth, keys.authkey, keys.authkeylen);
	अगर (err)
		जाओ out;

	crypto_skcipher_clear_flags(enc, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(enc, crypto_aead_get_flags(authenc) &
				       CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(enc, keys.enckey, keys.enckeylen);
out:
	memzero_explicit(&keys, माप(keys));
	वापस err;
पूर्ण

अटल व्योम authenc_geniv_ahash_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	काष्ठा aead_instance *inst = aead_alg_instance(authenc);
	काष्ठा authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा ahash_request *ahreq = (व्योम *)(areq_ctx->tail + ictx->reqoff);

	अगर (err)
		जाओ out;

	scatterwalk_map_and_copy(ahreq->result, req->dst,
				 req->assoclen + req->cryptlen,
				 crypto_aead_authsize(authenc), 1);

out:
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक crypto_authenc_genicv(काष्ठा aead_request *req, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	काष्ठा aead_instance *inst = aead_alg_instance(authenc);
	काष्ठा crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा crypto_ahash *auth = ctx->auth;
	काष्ठा authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा ahash_request *ahreq = (व्योम *)(areq_ctx->tail + ictx->reqoff);
	u8 *hash = areq_ctx->tail;
	पूर्णांक err;

	hash = (u8 *)ALIGN((अचिन्हित दीर्घ)hash + crypto_ahash_alignmask(auth),
			   crypto_ahash_alignmask(auth) + 1);

	ahash_request_set_tfm(ahreq, auth);
	ahash_request_set_crypt(ahreq, req->dst, hash,
				req->assoclen + req->cryptlen);
	ahash_request_set_callback(ahreq, flags,
				   authenc_geniv_ahash_करोne, req);

	err = crypto_ahash_digest(ahreq);
	अगर (err)
		वापस err;

	scatterwalk_map_and_copy(hash, req->dst, req->assoclen + req->cryptlen,
				 crypto_aead_authsize(authenc), 1);

	वापस 0;
पूर्ण

अटल व्योम crypto_authenc_encrypt_करोne(काष्ठा crypto_async_request *req,
					पूर्णांक err)
अणु
	काष्ठा aead_request *areq = req->data;

	अगर (err)
		जाओ out;

	err = crypto_authenc_genicv(areq, 0);

out:
	authenc_request_complete(areq, err);
पूर्ण

अटल पूर्णांक crypto_authenc_copy_assoc(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	काष्ठा crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	SYNC_SKCIPHER_REQUEST_ON_STACK(skreq, ctx->null);

	skcipher_request_set_sync_tfm(skreq, ctx->null);
	skcipher_request_set_callback(skreq, aead_request_flags(req),
				      शून्य, शून्य);
	skcipher_request_set_crypt(skreq, req->src, req->dst, req->assoclen,
				   शून्य);

	वापस crypto_skcipher_encrypt(skreq);
पूर्ण

अटल पूर्णांक crypto_authenc_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	काष्ठा aead_instance *inst = aead_alg_instance(authenc);
	काष्ठा crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा crypto_skcipher *enc = ctx->enc;
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	काष्ठा skcipher_request *skreq = (व्योम *)(areq_ctx->tail +
						  ictx->reqoff);
	काष्ठा scatterlist *src, *dst;
	पूर्णांक err;

	src = scatterwalk_ffwd(areq_ctx->src, req->src, req->assoclen);
	dst = src;

	अगर (req->src != req->dst) अणु
		err = crypto_authenc_copy_assoc(req);
		अगर (err)
			वापस err;

		dst = scatterwalk_ffwd(areq_ctx->dst, req->dst, req->assoclen);
	पूर्ण

	skcipher_request_set_tfm(skreq, enc);
	skcipher_request_set_callback(skreq, aead_request_flags(req),
				      crypto_authenc_encrypt_करोne, req);
	skcipher_request_set_crypt(skreq, src, dst, cryptlen, req->iv);

	err = crypto_skcipher_encrypt(skreq);
	अगर (err)
		वापस err;

	वापस crypto_authenc_genicv(req, aead_request_flags(req));
पूर्ण

अटल पूर्णांक crypto_authenc_decrypt_tail(काष्ठा aead_request *req,
				       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	काष्ठा aead_instance *inst = aead_alg_instance(authenc);
	काष्ठा crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा ahash_request *ahreq = (व्योम *)(areq_ctx->tail + ictx->reqoff);
	काष्ठा skcipher_request *skreq = (व्योम *)(areq_ctx->tail +
						  ictx->reqoff);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(authenc);
	u8 *ihash = ahreq->result + authsize;
	काष्ठा scatterlist *src, *dst;

	scatterwalk_map_and_copy(ihash, req->src, ahreq->nbytes, authsize, 0);

	अगर (crypto_memneq(ihash, ahreq->result, authsize))
		वापस -EBADMSG;

	src = scatterwalk_ffwd(areq_ctx->src, req->src, req->assoclen);
	dst = src;

	अगर (req->src != req->dst)
		dst = scatterwalk_ffwd(areq_ctx->dst, req->dst, req->assoclen);

	skcipher_request_set_tfm(skreq, ctx->enc);
	skcipher_request_set_callback(skreq, aead_request_flags(req),
				      req->base.complete, req->base.data);
	skcipher_request_set_crypt(skreq, src, dst,
				   req->cryptlen - authsize, req->iv);

	वापस crypto_skcipher_decrypt(skreq);
पूर्ण

अटल व्योम authenc_verअगरy_ahash_करोne(काष्ठा crypto_async_request *areq,
				      पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = crypto_authenc_decrypt_tail(req, 0);

out:
	authenc_request_complete(req, err);
पूर्ण

अटल पूर्णांक crypto_authenc_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *authenc = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(authenc);
	काष्ठा aead_instance *inst = aead_alg_instance(authenc);
	काष्ठा crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	काष्ठा authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा crypto_ahash *auth = ctx->auth;
	काष्ठा authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	काष्ठा ahash_request *ahreq = (व्योम *)(areq_ctx->tail + ictx->reqoff);
	u8 *hash = areq_ctx->tail;
	पूर्णांक err;

	hash = (u8 *)ALIGN((अचिन्हित दीर्घ)hash + crypto_ahash_alignmask(auth),
			   crypto_ahash_alignmask(auth) + 1);

	ahash_request_set_tfm(ahreq, auth);
	ahash_request_set_crypt(ahreq, req->src, hash,
				req->assoclen + req->cryptlen - authsize);
	ahash_request_set_callback(ahreq, aead_request_flags(req),
				   authenc_verअगरy_ahash_करोne, req);

	err = crypto_ahash_digest(ahreq);
	अगर (err)
		वापस err;

	वापस crypto_authenc_decrypt_tail(req, aead_request_flags(req));
पूर्ण

अटल पूर्णांक crypto_authenc_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा crypto_authenc_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_ahash *auth;
	काष्ठा crypto_skcipher *enc;
	काष्ठा crypto_sync_skcipher *null;
	पूर्णांक err;

	auth = crypto_spawn_ahash(&ictx->auth);
	अगर (IS_ERR(auth))
		वापस PTR_ERR(auth);

	enc = crypto_spawn_skcipher(&ictx->enc);
	err = PTR_ERR(enc);
	अगर (IS_ERR(enc))
		जाओ err_मुक्त_ahash;

	null = crypto_get_शेष_null_skcipher();
	err = PTR_ERR(null);
	अगर (IS_ERR(null))
		जाओ err_मुक्त_skcipher;

	ctx->auth = auth;
	ctx->enc = enc;
	ctx->null = null;

	crypto_aead_set_reqsize(
		tfm,
		माप(काष्ठा authenc_request_ctx) +
		ictx->reqoff +
		max_t(अचिन्हित पूर्णांक,
		      crypto_ahash_reqsize(auth) +
		      माप(काष्ठा ahash_request),
		      माप(काष्ठा skcipher_request) +
		      crypto_skcipher_reqsize(enc)));

	वापस 0;

err_मुक्त_skcipher:
	crypto_मुक्त_skcipher(enc);
err_मुक्त_ahash:
	crypto_मुक्त_ahash(auth);
	वापस err;
पूर्ण

अटल व्योम crypto_authenc_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा crypto_authenc_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_ahash(ctx->auth);
	crypto_मुक्त_skcipher(ctx->enc);
	crypto_put_शेष_null_skcipher();
पूर्ण

अटल व्योम crypto_authenc_मुक्त(काष्ठा aead_instance *inst)
अणु
	काष्ठा authenc_instance_ctx *ctx = aead_instance_ctx(inst);

	crypto_drop_skcipher(&ctx->enc);
	crypto_drop_ahash(&ctx->auth);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक crypto_authenc_create(काष्ठा crypto_ढाँचा *पंचांगpl,
				 काष्ठा rtattr **tb)
अणु
	u32 mask;
	काष्ठा aead_instance *inst;
	काष्ठा authenc_instance_ctx *ctx;
	काष्ठा hash_alg_common *auth;
	काष्ठा crypto_alg *auth_base;
	काष्ठा skcipher_alg *enc;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AEAD, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	ctx = aead_instance_ctx(inst);

	err = crypto_grab_ahash(&ctx->auth, aead_crypto_instance(inst),
				crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	auth = crypto_spawn_ahash_alg(&ctx->auth);
	auth_base = &auth->base;

	err = crypto_grab_skcipher(&ctx->enc, aead_crypto_instance(inst),
				   crypto_attr_alg_name(tb[2]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	enc = crypto_spawn_skcipher_alg(&ctx->enc);

	ctx->reqoff = ALIGN(2 * auth->digestsize + auth_base->cra_alignmask,
			    auth_base->cra_alignmask + 1);

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "authenc(%s,%s)", auth_base->cra_name,
		     enc->base.cra_name) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	अगर (snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "authenc(%s,%s)", auth_base->cra_driver_name,
		     enc->base.cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = enc->base.cra_priority * 10 +
				      auth_base->cra_priority;
	inst->alg.base.cra_blocksize = enc->base.cra_blocksize;
	inst->alg.base.cra_alignmask = auth_base->cra_alignmask |
				       enc->base.cra_alignmask;
	inst->alg.base.cra_ctxsize = माप(काष्ठा crypto_authenc_ctx);

	inst->alg.ivsize = crypto_skcipher_alg_ivsize(enc);
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(enc);
	inst->alg.maxauthsize = auth->digestsize;

	inst->alg.init = crypto_authenc_init_tfm;
	inst->alg.निकास = crypto_authenc_निकास_tfm;

	inst->alg.setkey = crypto_authenc_setkey;
	inst->alg.encrypt = crypto_authenc_encrypt;
	inst->alg.decrypt = crypto_authenc_decrypt;

	inst->मुक्त = crypto_authenc_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		crypto_authenc_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_authenc_पंचांगpl = अणु
	.name = "authenc",
	.create = crypto_authenc_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_authenc_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_authenc_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_authenc_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_authenc_पंचांगpl);
पूर्ण

subsys_initcall(crypto_authenc_module_init);
module_निकास(crypto_authenc_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple AEAD wrapper for IPsec");
MODULE_ALIAS_CRYPTO("authenc");
