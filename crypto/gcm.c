<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GCM: Galois/Counter Mode.
 *
 * Copyright (c) 2007 Nokia Siemens Networks - Mikko Herranen <mh1@iki.fi>
 */

#समावेश <crypto/gf128mul.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/null.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/hash.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

काष्ठा gcm_instance_ctx अणु
	काष्ठा crypto_skcipher_spawn ctr;
	काष्ठा crypto_ahash_spawn ghash;
पूर्ण;

काष्ठा crypto_gcm_ctx अणु
	काष्ठा crypto_skcipher *ctr;
	काष्ठा crypto_ahash *ghash;
पूर्ण;

काष्ठा crypto_rfc4106_ctx अणु
	काष्ठा crypto_aead *child;
	u8 nonce[4];
पूर्ण;

काष्ठा crypto_rfc4106_req_ctx अणु
	काष्ठा scatterlist src[3];
	काष्ठा scatterlist dst[3];
	काष्ठा aead_request subreq;
पूर्ण;

काष्ठा crypto_rfc4543_instance_ctx अणु
	काष्ठा crypto_aead_spawn aead;
पूर्ण;

काष्ठा crypto_rfc4543_ctx अणु
	काष्ठा crypto_aead *child;
	काष्ठा crypto_sync_skcipher *null;
	u8 nonce[4];
पूर्ण;

काष्ठा crypto_rfc4543_req_ctx अणु
	काष्ठा aead_request subreq;
पूर्ण;

काष्ठा crypto_gcm_ghash_ctx अणु
	अचिन्हित पूर्णांक cryptlen;
	काष्ठा scatterlist *src;
	पूर्णांक (*complete)(काष्ठा aead_request *req, u32 flags);
पूर्ण;

काष्ठा crypto_gcm_req_priv_ctx अणु
	u8 iv[16];
	u8 auth_tag[16];
	u8 iauth_tag[16];
	काष्ठा scatterlist src[3];
	काष्ठा scatterlist dst[3];
	काष्ठा scatterlist sg;
	काष्ठा crypto_gcm_ghash_ctx ghash_ctx;
	जोड़ अणु
		काष्ठा ahash_request ahreq;
		काष्ठा skcipher_request skreq;
	पूर्ण u;
पूर्ण;

अटल काष्ठा अणु
	u8 buf[16];
	काष्ठा scatterlist sg;
पूर्ण *gcm_zeroes;

अटल पूर्णांक crypto_rfc4543_copy_src_to_dst(काष्ठा aead_request *req, bool enc);

अटल अंतरभूत काष्ठा crypto_gcm_req_priv_ctx *crypto_gcm_reqctx(
	काष्ठा aead_request *req)
अणु
	अचिन्हित दीर्घ align = crypto_aead_alignmask(crypto_aead_reqtfm(req));

	वापस (व्योम *)PTR_ALIGN((u8 *)aead_request_ctx(req), align + 1);
पूर्ण

अटल पूर्णांक crypto_gcm_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_gcm_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा crypto_ahash *ghash = ctx->ghash;
	काष्ठा crypto_skcipher *ctr = ctx->ctr;
	काष्ठा अणु
		be128 hash;
		u8 iv[16];

		काष्ठा crypto_रुको रुको;

		काष्ठा scatterlist sg[1];
		काष्ठा skcipher_request req;
	पूर्ण *data;
	पूर्णांक err;

	crypto_skcipher_clear_flags(ctr, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(ctr, crypto_aead_get_flags(aead) &
				       CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(ctr, key, keylen);
	अगर (err)
		वापस err;

	data = kzalloc(माप(*data) + crypto_skcipher_reqsize(ctr),
		       GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	crypto_init_रुको(&data->रुको);
	sg_init_one(data->sg, &data->hash, माप(data->hash));
	skcipher_request_set_tfm(&data->req, ctr);
	skcipher_request_set_callback(&data->req, CRYPTO_TFM_REQ_MAY_SLEEP |
						  CRYPTO_TFM_REQ_MAY_BACKLOG,
				      crypto_req_करोne,
				      &data->रुको);
	skcipher_request_set_crypt(&data->req, data->sg, data->sg,
				   माप(data->hash), data->iv);

	err = crypto_रुको_req(crypto_skcipher_encrypt(&data->req),
							&data->रुको);

	अगर (err)
		जाओ out;

	crypto_ahash_clear_flags(ghash, CRYPTO_TFM_REQ_MASK);
	crypto_ahash_set_flags(ghash, crypto_aead_get_flags(aead) &
			       CRYPTO_TFM_REQ_MASK);
	err = crypto_ahash_setkey(ghash, (u8 *)&data->hash, माप(be128));
out:
	kमुक्त_sensitive(data);
	वापस err;
पूर्ण

अटल पूर्णांक crypto_gcm_setauthsize(काष्ठा crypto_aead *tfm,
				  अचिन्हित पूर्णांक authsize)
अणु
	वापस crypto_gcm_check_authsize(authsize);
पूर्ण

अटल व्योम crypto_gcm_init_common(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	__be32 counter = cpu_to_be32(1);
	काष्ठा scatterlist *sg;

	स_रखो(pctx->auth_tag, 0, माप(pctx->auth_tag));
	स_नकल(pctx->iv, req->iv, GCM_AES_IV_SIZE);
	स_नकल(pctx->iv + GCM_AES_IV_SIZE, &counter, 4);

	sg_init_table(pctx->src, 3);
	sg_set_buf(pctx->src, pctx->auth_tag, माप(pctx->auth_tag));
	sg = scatterwalk_ffwd(pctx->src + 1, req->src, req->assoclen);
	अगर (sg != pctx->src + 1)
		sg_chain(pctx->src, 2, sg);

	अगर (req->src != req->dst) अणु
		sg_init_table(pctx->dst, 3);
		sg_set_buf(pctx->dst, pctx->auth_tag, माप(pctx->auth_tag));
		sg = scatterwalk_ffwd(pctx->dst + 1, req->dst, req->assoclen);
		अगर (sg != pctx->dst + 1)
			sg_chain(pctx->dst, 2, sg);
	पूर्ण
पूर्ण

अटल व्योम crypto_gcm_init_crypt(काष्ठा aead_request *req,
				  अचिन्हित पूर्णांक cryptlen)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_gcm_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा skcipher_request *skreq = &pctx->u.skreq;
	काष्ठा scatterlist *dst;

	dst = req->src == req->dst ? pctx->src : pctx->dst;

	skcipher_request_set_tfm(skreq, ctx->ctr);
	skcipher_request_set_crypt(skreq, pctx->src, dst,
				     cryptlen + माप(pctx->auth_tag),
				     pctx->iv);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक gcm_reमुख्य(अचिन्हित पूर्णांक len)
अणु
	len &= 0xfU;
	वापस len ? 16 - len : 0;
पूर्ण

अटल व्योम gcm_hash_len_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err);

अटल पूर्णांक gcm_hash_update(काष्ठा aead_request *req,
			   crypto_completion_t compl,
			   काष्ठा scatterlist *src,
			   अचिन्हित पूर्णांक len, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा ahash_request *ahreq = &pctx->u.ahreq;

	ahash_request_set_callback(ahreq, flags, compl, req);
	ahash_request_set_crypt(ahreq, src, शून्य, len);

	वापस crypto_ahash_update(ahreq);
पूर्ण

अटल पूर्णांक gcm_hash_reमुख्य(काष्ठा aead_request *req,
			   अचिन्हित पूर्णांक reमुख्य,
			   crypto_completion_t compl, u32 flags)
अणु
	वापस gcm_hash_update(req, compl, &gcm_zeroes->sg, reमुख्य, flags);
पूर्ण

अटल पूर्णांक gcm_hash_len(काष्ठा aead_request *req, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा ahash_request *ahreq = &pctx->u.ahreq;
	काष्ठा crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	be128 lengths;

	lengths.a = cpu_to_be64(req->assoclen * 8);
	lengths.b = cpu_to_be64(gctx->cryptlen * 8);
	स_नकल(pctx->iauth_tag, &lengths, 16);
	sg_init_one(&pctx->sg, pctx->iauth_tag, 16);
	ahash_request_set_callback(ahreq, flags, gcm_hash_len_करोne, req);
	ahash_request_set_crypt(ahreq, &pctx->sg,
				pctx->iauth_tag, माप(lengths));

	वापस crypto_ahash_finup(ahreq);
पूर्ण

अटल पूर्णांक gcm_hash_len_जारी(काष्ठा aead_request *req, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	वापस gctx->complete(req, flags);
पूर्ण

अटल व्योम gcm_hash_len_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = gcm_hash_len_जारी(req, 0);
	अगर (err == -EINPROGRESS)
		वापस;

out:
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक gcm_hash_crypt_reमुख्य_जारी(काष्ठा aead_request *req, u32 flags)
अणु
	वापस gcm_hash_len(req, flags) ?:
	       gcm_hash_len_जारी(req, flags);
पूर्ण

अटल व्योम gcm_hash_crypt_reमुख्य_करोne(काष्ठा crypto_async_request *areq,
				       पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = gcm_hash_crypt_reमुख्य_जारी(req, 0);
	अगर (err == -EINPROGRESS)
		वापस;

out:
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक gcm_hash_crypt_जारी(काष्ठा aead_request *req, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	अचिन्हित पूर्णांक reमुख्य;

	reमुख्य = gcm_reमुख्य(gctx->cryptlen);
	अगर (reमुख्य)
		वापस gcm_hash_reमुख्य(req, reमुख्य,
				       gcm_hash_crypt_reमुख्य_करोne, flags) ?:
		       gcm_hash_crypt_reमुख्य_जारी(req, flags);

	वापस gcm_hash_crypt_reमुख्य_जारी(req, flags);
पूर्ण

अटल व्योम gcm_hash_crypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = gcm_hash_crypt_जारी(req, 0);
	अगर (err == -EINPROGRESS)
		वापस;

out:
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक gcm_hash_assoc_reमुख्य_जारी(काष्ठा aead_request *req, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	अगर (gctx->cryptlen)
		वापस gcm_hash_update(req, gcm_hash_crypt_करोne,
				       gctx->src, gctx->cryptlen, flags) ?:
		       gcm_hash_crypt_जारी(req, flags);

	वापस gcm_hash_crypt_reमुख्य_जारी(req, flags);
पूर्ण

अटल व्योम gcm_hash_assoc_reमुख्य_करोne(काष्ठा crypto_async_request *areq,
				       पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = gcm_hash_assoc_reमुख्य_जारी(req, 0);
	अगर (err == -EINPROGRESS)
		वापस;

out:
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक gcm_hash_assoc_जारी(काष्ठा aead_request *req, u32 flags)
अणु
	अचिन्हित पूर्णांक reमुख्य;

	reमुख्य = gcm_reमुख्य(req->assoclen);
	अगर (reमुख्य)
		वापस gcm_hash_reमुख्य(req, reमुख्य,
				       gcm_hash_assoc_reमुख्य_करोne, flags) ?:
		       gcm_hash_assoc_reमुख्य_जारी(req, flags);

	वापस gcm_hash_assoc_reमुख्य_जारी(req, flags);
पूर्ण

अटल व्योम gcm_hash_assoc_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = gcm_hash_assoc_जारी(req, 0);
	अगर (err == -EINPROGRESS)
		वापस;

out:
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक gcm_hash_init_जारी(काष्ठा aead_request *req, u32 flags)
अणु
	अगर (req->assoclen)
		वापस gcm_hash_update(req, gcm_hash_assoc_करोne,
				       req->src, req->assoclen, flags) ?:
		       gcm_hash_assoc_जारी(req, flags);

	वापस gcm_hash_assoc_reमुख्य_जारी(req, flags);
पूर्ण

अटल व्योम gcm_hash_init_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = gcm_hash_init_जारी(req, 0);
	अगर (err == -EINPROGRESS)
		वापस;

out:
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक gcm_hash(काष्ठा aead_request *req, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा ahash_request *ahreq = &pctx->u.ahreq;
	काष्ठा crypto_gcm_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));

	ahash_request_set_tfm(ahreq, ctx->ghash);

	ahash_request_set_callback(ahreq, flags, gcm_hash_init_करोne, req);
	वापस crypto_ahash_init(ahreq) ?:
	       gcm_hash_init_जारी(req, flags);
पूर्ण

अटल पूर्णांक gcm_enc_copy_hash(काष्ठा aead_request *req, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	u8 *auth_tag = pctx->auth_tag;

	crypto_xor(auth_tag, pctx->iauth_tag, 16);
	scatterwalk_map_and_copy(auth_tag, req->dst,
				 req->assoclen + req->cryptlen,
				 crypto_aead_authsize(aead), 1);
	वापस 0;
पूर्ण

अटल पूर्णांक gcm_encrypt_जारी(काष्ठा aead_request *req, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	gctx->src = sg_next(req->src == req->dst ? pctx->src : pctx->dst);
	gctx->cryptlen = req->cryptlen;
	gctx->complete = gcm_enc_copy_hash;

	वापस gcm_hash(req, flags);
पूर्ण

अटल व्योम gcm_encrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (err)
		जाओ out;

	err = gcm_encrypt_जारी(req, 0);
	अगर (err == -EINPROGRESS)
		वापस;

out:
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक crypto_gcm_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा skcipher_request *skreq = &pctx->u.skreq;
	u32 flags = aead_request_flags(req);

	crypto_gcm_init_common(req);
	crypto_gcm_init_crypt(req, req->cryptlen);
	skcipher_request_set_callback(skreq, flags, gcm_encrypt_करोne, req);

	वापस crypto_skcipher_encrypt(skreq) ?:
	       gcm_encrypt_जारी(req, flags);
पूर्ण

अटल पूर्णांक crypto_gcm_verअगरy(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	u8 *auth_tag = pctx->auth_tag;
	u8 *iauth_tag = pctx->iauth_tag;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen - authsize;

	crypto_xor(auth_tag, iauth_tag, 16);
	scatterwalk_map_and_copy(iauth_tag, req->src,
				 req->assoclen + cryptlen, authsize, 0);
	वापस crypto_memneq(iauth_tag, auth_tag, authsize) ? -EBADMSG : 0;
पूर्ण

अटल व्योम gcm_decrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;

	अगर (!err)
		err = crypto_gcm_verअगरy(req);

	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक gcm_dec_hash_जारी(काष्ठा aead_request *req, u32 flags)
अणु
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा skcipher_request *skreq = &pctx->u.skreq;
	काष्ठा crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	crypto_gcm_init_crypt(req, gctx->cryptlen);
	skcipher_request_set_callback(skreq, flags, gcm_decrypt_करोne, req);
	वापस crypto_skcipher_decrypt(skreq) ?: crypto_gcm_verअगरy(req);
पूर्ण

अटल पूर्णांक crypto_gcm_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	काष्ठा crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	u32 flags = aead_request_flags(req);

	cryptlen -= authsize;

	crypto_gcm_init_common(req);

	gctx->src = sg_next(pctx->src);
	gctx->cryptlen = cryptlen;
	gctx->complete = gcm_dec_hash_जारी;

	वापस gcm_hash(req, flags);
पूर्ण

अटल पूर्णांक crypto_gcm_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा gcm_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा crypto_gcm_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_skcipher *ctr;
	काष्ठा crypto_ahash *ghash;
	अचिन्हित दीर्घ align;
	पूर्णांक err;

	ghash = crypto_spawn_ahash(&ictx->ghash);
	अगर (IS_ERR(ghash))
		वापस PTR_ERR(ghash);

	ctr = crypto_spawn_skcipher(&ictx->ctr);
	err = PTR_ERR(ctr);
	अगर (IS_ERR(ctr))
		जाओ err_मुक्त_hash;

	ctx->ctr = ctr;
	ctx->ghash = ghash;

	align = crypto_aead_alignmask(tfm);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(tfm,
		align + दुरत्व(काष्ठा crypto_gcm_req_priv_ctx, u) +
		max(माप(काष्ठा skcipher_request) +
		    crypto_skcipher_reqsize(ctr),
		    माप(काष्ठा ahash_request) +
		    crypto_ahash_reqsize(ghash)));

	वापस 0;

err_मुक्त_hash:
	crypto_मुक्त_ahash(ghash);
	वापस err;
पूर्ण

अटल व्योम crypto_gcm_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा crypto_gcm_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_ahash(ctx->ghash);
	crypto_मुक्त_skcipher(ctx->ctr);
पूर्ण

अटल व्योम crypto_gcm_मुक्त(काष्ठा aead_instance *inst)
अणु
	काष्ठा gcm_instance_ctx *ctx = aead_instance_ctx(inst);

	crypto_drop_skcipher(&ctx->ctr);
	crypto_drop_ahash(&ctx->ghash);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक crypto_gcm_create_common(काष्ठा crypto_ढाँचा *पंचांगpl,
				    काष्ठा rtattr **tb,
				    स्थिर अक्षर *ctr_name,
				    स्थिर अक्षर *ghash_name)
अणु
	u32 mask;
	काष्ठा aead_instance *inst;
	काष्ठा gcm_instance_ctx *ctx;
	काष्ठा skcipher_alg *ctr;
	काष्ठा hash_alg_common *ghash;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AEAD, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	ctx = aead_instance_ctx(inst);

	err = crypto_grab_ahash(&ctx->ghash, aead_crypto_instance(inst),
				ghash_name, 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	ghash = crypto_spawn_ahash_alg(&ctx->ghash);

	err = -EINVAL;
	अगर (म_भेद(ghash->base.cra_name, "ghash") != 0 ||
	    ghash->digestsize != 16)
		जाओ err_मुक्त_inst;

	err = crypto_grab_skcipher(&ctx->ctr, aead_crypto_instance(inst),
				   ctr_name, 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	ctr = crypto_spawn_skcipher_alg(&ctx->ctr);

	/* The skcipher algorithm must be CTR mode, using 16-byte blocks. */
	err = -EINVAL;
	अगर (म_भेदन(ctr->base.cra_name, "ctr(", 4) != 0 ||
	    crypto_skcipher_alg_ivsize(ctr) != 16 ||
	    ctr->base.cra_blocksize != 1)
		जाओ err_मुक्त_inst;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "gcm(%s", ctr->base.cra_name + 4) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	अगर (snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "gcm_base(%s,%s)", ctr->base.cra_driver_name,
		     ghash->base.cra_driver_name) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = (ghash->base.cra_priority +
				       ctr->base.cra_priority) / 2;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = ghash->base.cra_alignmask |
				       ctr->base.cra_alignmask;
	inst->alg.base.cra_ctxsize = माप(काष्ठा crypto_gcm_ctx);
	inst->alg.ivsize = GCM_AES_IV_SIZE;
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(ctr);
	inst->alg.maxauthsize = 16;
	inst->alg.init = crypto_gcm_init_tfm;
	inst->alg.निकास = crypto_gcm_निकास_tfm;
	inst->alg.setkey = crypto_gcm_setkey;
	inst->alg.setauthsize = crypto_gcm_setauthsize;
	inst->alg.encrypt = crypto_gcm_encrypt;
	inst->alg.decrypt = crypto_gcm_decrypt;

	inst->मुक्त = crypto_gcm_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		crypto_gcm_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक crypto_gcm_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	स्थिर अक्षर *cipher_name;
	अक्षर ctr_name[CRYPTO_MAX_ALG_NAME];

	cipher_name = crypto_attr_alg_name(tb[1]);
	अगर (IS_ERR(cipher_name))
		वापस PTR_ERR(cipher_name);

	अगर (snम_लिखो(ctr_name, CRYPTO_MAX_ALG_NAME, "ctr(%s)", cipher_name) >=
	    CRYPTO_MAX_ALG_NAME)
		वापस -ENAMETOOLONG;

	वापस crypto_gcm_create_common(पंचांगpl, tb, ctr_name, "ghash");
पूर्ण

अटल पूर्णांक crypto_gcm_base_create(काष्ठा crypto_ढाँचा *पंचांगpl,
				  काष्ठा rtattr **tb)
अणु
	स्थिर अक्षर *ctr_name;
	स्थिर अक्षर *ghash_name;

	ctr_name = crypto_attr_alg_name(tb[1]);
	अगर (IS_ERR(ctr_name))
		वापस PTR_ERR(ctr_name);

	ghash_name = crypto_attr_alg_name(tb[2]);
	अगर (IS_ERR(ghash_name))
		वापस PTR_ERR(ghash_name);

	वापस crypto_gcm_create_common(पंचांगpl, tb, ctr_name, ghash_name);
पूर्ण

अटल पूर्णांक crypto_rfc4106_setkey(काष्ठा crypto_aead *parent, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_rfc4106_ctx *ctx = crypto_aead_ctx(parent);
	काष्ठा crypto_aead *child = ctx->child;

	अगर (keylen < 4)
		वापस -EINVAL;

	keylen -= 4;
	स_नकल(ctx->nonce, key + keylen, 4);

	crypto_aead_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(child, crypto_aead_get_flags(parent) &
				     CRYPTO_TFM_REQ_MASK);
	वापस crypto_aead_setkey(child, key, keylen);
पूर्ण

अटल पूर्णांक crypto_rfc4106_setauthsize(काष्ठा crypto_aead *parent,
				      अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा crypto_rfc4106_ctx *ctx = crypto_aead_ctx(parent);
	पूर्णांक err;

	err = crypto_rfc4106_check_authsize(authsize);
	अगर (err)
		वापस err;

	वापस crypto_aead_setauthsize(ctx->child, authsize);
पूर्ण

अटल काष्ठा aead_request *crypto_rfc4106_crypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_rfc4106_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_rfc4106_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा aead_request *subreq = &rctx->subreq;
	काष्ठा crypto_aead *child = ctx->child;
	काष्ठा scatterlist *sg;
	u8 *iv = PTR_ALIGN((u8 *)(subreq + 1) + crypto_aead_reqsize(child),
			   crypto_aead_alignmask(child) + 1);

	scatterwalk_map_and_copy(iv + GCM_AES_IV_SIZE, req->src, 0, req->assoclen - 8, 0);

	स_नकल(iv, ctx->nonce, 4);
	स_नकल(iv + 4, req->iv, 8);

	sg_init_table(rctx->src, 3);
	sg_set_buf(rctx->src, iv + GCM_AES_IV_SIZE, req->assoclen - 8);
	sg = scatterwalk_ffwd(rctx->src + 1, req->src, req->assoclen);
	अगर (sg != rctx->src + 1)
		sg_chain(rctx->src, 2, sg);

	अगर (req->src != req->dst) अणु
		sg_init_table(rctx->dst, 3);
		sg_set_buf(rctx->dst, iv + GCM_AES_IV_SIZE, req->assoclen - 8);
		sg = scatterwalk_ffwd(rctx->dst + 1, req->dst, req->assoclen);
		अगर (sg != rctx->dst + 1)
			sg_chain(rctx->dst, 2, sg);
	पूर्ण

	aead_request_set_tfm(subreq, child);
	aead_request_set_callback(subreq, req->base.flags, req->base.complete,
				  req->base.data);
	aead_request_set_crypt(subreq, rctx->src,
			       req->src == req->dst ? rctx->src : rctx->dst,
			       req->cryptlen, iv);
	aead_request_set_ad(subreq, req->assoclen - 8);

	वापस subreq;
पूर्ण

अटल पूर्णांक crypto_rfc4106_encrypt(काष्ठा aead_request *req)
अणु
	पूर्णांक err;

	err = crypto_ipsec_check_assoclen(req->assoclen);
	अगर (err)
		वापस err;

	req = crypto_rfc4106_crypt(req);

	वापस crypto_aead_encrypt(req);
पूर्ण

अटल पूर्णांक crypto_rfc4106_decrypt(काष्ठा aead_request *req)
अणु
	पूर्णांक err;

	err = crypto_ipsec_check_assoclen(req->assoclen);
	अगर (err)
		वापस err;

	req = crypto_rfc4106_crypt(req);

	वापस crypto_aead_decrypt(req);
पूर्ण

अटल पूर्णांक crypto_rfc4106_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा crypto_aead_spawn *spawn = aead_instance_ctx(inst);
	काष्ठा crypto_rfc4106_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *aead;
	अचिन्हित दीर्घ align;

	aead = crypto_spawn_aead(spawn);
	अगर (IS_ERR(aead))
		वापस PTR_ERR(aead);

	ctx->child = aead;

	align = crypto_aead_alignmask(aead);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(
		tfm,
		माप(काष्ठा crypto_rfc4106_req_ctx) +
		ALIGN(crypto_aead_reqsize(aead), crypto_tfm_ctx_alignment()) +
		align + 24);

	वापस 0;
पूर्ण

अटल व्योम crypto_rfc4106_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा crypto_rfc4106_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_aead(ctx->child);
पूर्ण

अटल व्योम crypto_rfc4106_मुक्त(काष्ठा aead_instance *inst)
अणु
	crypto_drop_aead(aead_instance_ctx(inst));
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक crypto_rfc4106_create(काष्ठा crypto_ढाँचा *पंचांगpl,
				 काष्ठा rtattr **tb)
अणु
	u32 mask;
	काष्ठा aead_instance *inst;
	काष्ठा crypto_aead_spawn *spawn;
	काष्ठा aead_alg *alg;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AEAD, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	spawn = aead_instance_ctx(inst);
	err = crypto_grab_aead(spawn, aead_crypto_instance(inst),
			       crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_spawn_aead_alg(spawn);

	err = -EINVAL;

	/* Underlying IV size must be 12. */
	अगर (crypto_aead_alg_ivsize(alg) != GCM_AES_IV_SIZE)
		जाओ err_मुक्त_inst;

	/* Not a stream cipher? */
	अगर (alg->base.cra_blocksize != 1)
		जाओ err_मुक्त_inst;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "rfc4106(%s)", alg->base.cra_name) >=
	    CRYPTO_MAX_ALG_NAME ||
	    snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "rfc4106(%s)", alg->base.cra_driver_name) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->base.cra_priority;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = alg->base.cra_alignmask;

	inst->alg.base.cra_ctxsize = माप(काष्ठा crypto_rfc4106_ctx);

	inst->alg.ivsize = GCM_RFC4106_IV_SIZE;
	inst->alg.chunksize = crypto_aead_alg_chunksize(alg);
	inst->alg.maxauthsize = crypto_aead_alg_maxauthsize(alg);

	inst->alg.init = crypto_rfc4106_init_tfm;
	inst->alg.निकास = crypto_rfc4106_निकास_tfm;

	inst->alg.setkey = crypto_rfc4106_setkey;
	inst->alg.setauthsize = crypto_rfc4106_setauthsize;
	inst->alg.encrypt = crypto_rfc4106_encrypt;
	inst->alg.decrypt = crypto_rfc4106_decrypt;

	inst->मुक्त = crypto_rfc4106_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		crypto_rfc4106_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक crypto_rfc4543_setkey(काष्ठा crypto_aead *parent, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_rfc4543_ctx *ctx = crypto_aead_ctx(parent);
	काष्ठा crypto_aead *child = ctx->child;

	अगर (keylen < 4)
		वापस -EINVAL;

	keylen -= 4;
	स_नकल(ctx->nonce, key + keylen, 4);

	crypto_aead_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(child, crypto_aead_get_flags(parent) &
				     CRYPTO_TFM_REQ_MASK);
	वापस crypto_aead_setkey(child, key, keylen);
पूर्ण

अटल पूर्णांक crypto_rfc4543_setauthsize(काष्ठा crypto_aead *parent,
				      अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा crypto_rfc4543_ctx *ctx = crypto_aead_ctx(parent);

	अगर (authsize != 16)
		वापस -EINVAL;

	वापस crypto_aead_setauthsize(ctx->child, authsize);
पूर्ण

अटल पूर्णांक crypto_rfc4543_crypt(काष्ठा aead_request *req, bool enc)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_rfc4543_ctx *ctx = crypto_aead_ctx(aead);
	काष्ठा crypto_rfc4543_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा aead_request *subreq = &rctx->subreq;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	u8 *iv = PTR_ALIGN((u8 *)(rctx + 1) + crypto_aead_reqsize(ctx->child),
			   crypto_aead_alignmask(ctx->child) + 1);
	पूर्णांक err;

	अगर (req->src != req->dst) अणु
		err = crypto_rfc4543_copy_src_to_dst(req, enc);
		अगर (err)
			वापस err;
	पूर्ण

	स_नकल(iv, ctx->nonce, 4);
	स_नकल(iv + 4, req->iv, 8);

	aead_request_set_tfm(subreq, ctx->child);
	aead_request_set_callback(subreq, req->base.flags,
				  req->base.complete, req->base.data);
	aead_request_set_crypt(subreq, req->src, req->dst,
			       enc ? 0 : authsize, iv);
	aead_request_set_ad(subreq, req->assoclen + req->cryptlen -
				    subreq->cryptlen);

	वापस enc ? crypto_aead_encrypt(subreq) : crypto_aead_decrypt(subreq);
पूर्ण

अटल पूर्णांक crypto_rfc4543_copy_src_to_dst(काष्ठा aead_request *req, bool enc)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_rfc4543_ctx *ctx = crypto_aead_ctx(aead);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(aead);
	अचिन्हित पूर्णांक nbytes = req->assoclen + req->cryptlen -
			      (enc ? 0 : authsize);
	SYNC_SKCIPHER_REQUEST_ON_STACK(nreq, ctx->null);

	skcipher_request_set_sync_tfm(nreq, ctx->null);
	skcipher_request_set_callback(nreq, req->base.flags, शून्य, शून्य);
	skcipher_request_set_crypt(nreq, req->src, req->dst, nbytes, शून्य);

	वापस crypto_skcipher_encrypt(nreq);
पूर्ण

अटल पूर्णांक crypto_rfc4543_encrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ?:
	       crypto_rfc4543_crypt(req, true);
पूर्ण

अटल पूर्णांक crypto_rfc4543_decrypt(काष्ठा aead_request *req)
अणु
	वापस crypto_ipsec_check_assoclen(req->assoclen) ?:
	       crypto_rfc4543_crypt(req, false);
पूर्ण

अटल पूर्णांक crypto_rfc4543_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा crypto_rfc4543_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा crypto_aead_spawn *spawn = &ictx->aead;
	काष्ठा crypto_rfc4543_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *aead;
	काष्ठा crypto_sync_skcipher *null;
	अचिन्हित दीर्घ align;
	पूर्णांक err = 0;

	aead = crypto_spawn_aead(spawn);
	अगर (IS_ERR(aead))
		वापस PTR_ERR(aead);

	null = crypto_get_शेष_null_skcipher();
	err = PTR_ERR(null);
	अगर (IS_ERR(null))
		जाओ err_मुक्त_aead;

	ctx->child = aead;
	ctx->null = null;

	align = crypto_aead_alignmask(aead);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(
		tfm,
		माप(काष्ठा crypto_rfc4543_req_ctx) +
		ALIGN(crypto_aead_reqsize(aead), crypto_tfm_ctx_alignment()) +
		align + GCM_AES_IV_SIZE);

	वापस 0;

err_मुक्त_aead:
	crypto_मुक्त_aead(aead);
	वापस err;
पूर्ण

अटल व्योम crypto_rfc4543_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा crypto_rfc4543_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_aead(ctx->child);
	crypto_put_शेष_null_skcipher();
पूर्ण

अटल व्योम crypto_rfc4543_मुक्त(काष्ठा aead_instance *inst)
अणु
	काष्ठा crypto_rfc4543_instance_ctx *ctx = aead_instance_ctx(inst);

	crypto_drop_aead(&ctx->aead);

	kमुक्त(inst);
पूर्ण

अटल पूर्णांक crypto_rfc4543_create(काष्ठा crypto_ढाँचा *पंचांगpl,
				काष्ठा rtattr **tb)
अणु
	u32 mask;
	काष्ठा aead_instance *inst;
	काष्ठा aead_alg *alg;
	काष्ठा crypto_rfc4543_instance_ctx *ctx;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AEAD, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	ctx = aead_instance_ctx(inst);
	err = crypto_grab_aead(&ctx->aead, aead_crypto_instance(inst),
			       crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_spawn_aead_alg(&ctx->aead);

	err = -EINVAL;

	/* Underlying IV size must be 12. */
	अगर (crypto_aead_alg_ivsize(alg) != GCM_AES_IV_SIZE)
		जाओ err_मुक्त_inst;

	/* Not a stream cipher? */
	अगर (alg->base.cra_blocksize != 1)
		जाओ err_मुक्त_inst;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "rfc4543(%s)", alg->base.cra_name) >=
	    CRYPTO_MAX_ALG_NAME ||
	    snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "rfc4543(%s)", alg->base.cra_driver_name) >=
	    CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->base.cra_priority;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = alg->base.cra_alignmask;

	inst->alg.base.cra_ctxsize = माप(काष्ठा crypto_rfc4543_ctx);

	inst->alg.ivsize = GCM_RFC4543_IV_SIZE;
	inst->alg.chunksize = crypto_aead_alg_chunksize(alg);
	inst->alg.maxauthsize = crypto_aead_alg_maxauthsize(alg);

	inst->alg.init = crypto_rfc4543_init_tfm;
	inst->alg.निकास = crypto_rfc4543_निकास_tfm;

	inst->alg.setkey = crypto_rfc4543_setkey;
	inst->alg.setauthsize = crypto_rfc4543_setauthsize;
	inst->alg.encrypt = crypto_rfc4543_encrypt;
	inst->alg.decrypt = crypto_rfc4543_decrypt;

	inst->मुक्त = crypto_rfc4543_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		crypto_rfc4543_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_gcm_पंचांगpls[] = अणु
	अणु
		.name = "gcm_base",
		.create = crypto_gcm_base_create,
		.module = THIS_MODULE,
	पूर्ण, अणु
		.name = "gcm",
		.create = crypto_gcm_create,
		.module = THIS_MODULE,
	पूर्ण, अणु
		.name = "rfc4106",
		.create = crypto_rfc4106_create,
		.module = THIS_MODULE,
	पूर्ण, अणु
		.name = "rfc4543",
		.create = crypto_rfc4543_create,
		.module = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init crypto_gcm_module_init(व्योम)
अणु
	पूर्णांक err;

	gcm_zeroes = kzalloc(माप(*gcm_zeroes), GFP_KERNEL);
	अगर (!gcm_zeroes)
		वापस -ENOMEM;

	sg_init_one(&gcm_zeroes->sg, gcm_zeroes->buf, माप(gcm_zeroes->buf));

	err = crypto_रेजिस्टर_ढाँचाs(crypto_gcm_पंचांगpls,
					ARRAY_SIZE(crypto_gcm_पंचांगpls));
	अगर (err)
		kमुक्त(gcm_zeroes);

	वापस err;
पूर्ण

अटल व्योम __निकास crypto_gcm_module_निकास(व्योम)
अणु
	kमुक्त(gcm_zeroes);
	crypto_unरेजिस्टर_ढाँचाs(crypto_gcm_पंचांगpls,
				    ARRAY_SIZE(crypto_gcm_पंचांगpls));
पूर्ण

subsys_initcall(crypto_gcm_module_init);
module_निकास(crypto_gcm_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Galois/Counter Mode");
MODULE_AUTHOR("Mikko Herranen <mh1@iki.fi>");
MODULE_ALIAS_CRYPTO("gcm_base");
MODULE_ALIAS_CRYPTO("rfc4106");
MODULE_ALIAS_CRYPTO("rfc4543");
MODULE_ALIAS_CRYPTO("gcm");
