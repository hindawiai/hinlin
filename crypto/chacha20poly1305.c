<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ChaCha20-Poly1305 AEAD, RFC7539
 *
 * Copyright (C) 2015 Martin Willi
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/chacha.h>
#समावेश <crypto/poly1305.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

काष्ठा chachapoly_instance_ctx अणु
	काष्ठा crypto_skcipher_spawn chacha;
	काष्ठा crypto_ahash_spawn poly;
	अचिन्हित पूर्णांक saltlen;
पूर्ण;

काष्ठा chachapoly_ctx अणु
	काष्ठा crypto_skcipher *chacha;
	काष्ठा crypto_ahash *poly;
	/* key bytes we use क्रम the ChaCha20 IV */
	अचिन्हित पूर्णांक saltlen;
	u8 salt[];
पूर्ण;

काष्ठा poly_req अणु
	/* zero byte padding क्रम AD/ciphertext, as needed */
	u8 pad[POLY1305_BLOCK_SIZE];
	/* tail data with AD/ciphertext lengths */
	काष्ठा अणु
		__le64 assoclen;
		__le64 cryptlen;
	पूर्ण tail;
	काष्ठा scatterlist src[1];
	काष्ठा ahash_request req; /* must be last member */
पूर्ण;

काष्ठा chacha_req अणु
	u8 iv[CHACHA_IV_SIZE];
	काष्ठा scatterlist src[1];
	काष्ठा skcipher_request req; /* must be last member */
पूर्ण;

काष्ठा chachapoly_req_ctx अणु
	काष्ठा scatterlist src[2];
	काष्ठा scatterlist dst[2];
	/* the key we generate क्रम Poly1305 using Chacha20 */
	u8 key[POLY1305_KEY_SIZE];
	/* calculated Poly1305 tag */
	u8 tag[POLY1305_DIGEST_SIZE];
	/* length of data to en/decrypt, without ICV */
	अचिन्हित पूर्णांक cryptlen;
	/* Actual AD, excluding IV */
	अचिन्हित पूर्णांक assoclen;
	/* request flags, with MAY_SLEEP cleared अगर needed */
	u32 flags;
	जोड़ अणु
		काष्ठा poly_req poly;
		काष्ठा chacha_req chacha;
	पूर्ण u;
पूर्ण;

अटल अंतरभूत व्योम async_करोne_जारी(काष्ठा aead_request *req, पूर्णांक err,
				       पूर्णांक (*cont)(काष्ठा aead_request *))
अणु
	अगर (!err) अणु
		काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);

		rctx->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
		err = cont(req);
	पूर्ण

	अगर (err != -EINPROGRESS && err != -EBUSY)
		aead_request_complete(req, err);
पूर्ण

अटल व्योम chacha_iv(u8 *iv, काष्ठा aead_request *req, u32 icb)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	__le32 leicb = cpu_to_le32(icb);

	स_नकल(iv, &leicb, माप(leicb));
	स_नकल(iv + माप(leicb), ctx->salt, ctx->saltlen);
	स_नकल(iv + माप(leicb) + ctx->saltlen, req->iv,
	       CHACHA_IV_SIZE - माप(leicb) - ctx->saltlen);
पूर्ण

अटल पूर्णांक poly_verअगरy_tag(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	u8 tag[माप(rctx->tag)];

	scatterwalk_map_and_copy(tag, req->src,
				 req->assoclen + rctx->cryptlen,
				 माप(tag), 0);
	अगर (crypto_memneq(tag, rctx->tag, माप(tag)))
		वापस -EBADMSG;
	वापस 0;
पूर्ण

अटल पूर्णांक poly_copy_tag(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);

	scatterwalk_map_and_copy(rctx->tag, req->dst,
				 req->assoclen + rctx->cryptlen,
				 माप(rctx->tag), 1);
	वापस 0;
पूर्ण

अटल व्योम chacha_decrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_verअगरy_tag);
पूर्ण

अटल पूर्णांक chacha_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा chacha_req *creq = &rctx->u.chacha;
	काष्ठा scatterlist *src, *dst;
	पूर्णांक err;

	अगर (rctx->cryptlen == 0)
		जाओ skip;

	chacha_iv(creq->iv, req, 1);

	src = scatterwalk_ffwd(rctx->src, req->src, req->assoclen);
	dst = src;
	अगर (req->src != req->dst)
		dst = scatterwalk_ffwd(rctx->dst, req->dst, req->assoclen);

	skcipher_request_set_callback(&creq->req, rctx->flags,
				      chacha_decrypt_करोne, req);
	skcipher_request_set_tfm(&creq->req, ctx->chacha);
	skcipher_request_set_crypt(&creq->req, src, dst,
				   rctx->cryptlen, creq->iv);
	err = crypto_skcipher_decrypt(&creq->req);
	अगर (err)
		वापस err;

skip:
	वापस poly_verअगरy_tag(req);
पूर्ण

अटल पूर्णांक poly_tail_जारी(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);

	अगर (rctx->cryptlen == req->cryptlen) /* encrypting */
		वापस poly_copy_tag(req);

	वापस chacha_decrypt(req);
पूर्ण

अटल व्योम poly_tail_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_tail_जारी);
पूर्ण

अटल पूर्णांक poly_tail(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा poly_req *preq = &rctx->u.poly;
	पूर्णांक err;

	preq->tail.assoclen = cpu_to_le64(rctx->assoclen);
	preq->tail.cryptlen = cpu_to_le64(rctx->cryptlen);
	sg_init_one(preq->src, &preq->tail, माप(preq->tail));

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_tail_करोne, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, preq->src,
				rctx->tag, माप(preq->tail));

	err = crypto_ahash_finup(&preq->req);
	अगर (err)
		वापस err;

	वापस poly_tail_जारी(req);
पूर्ण

अटल व्योम poly_cipherpad_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_tail);
पूर्ण

अटल पूर्णांक poly_cipherpad(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा poly_req *preq = &rctx->u.poly;
	अचिन्हित पूर्णांक padlen;
	पूर्णांक err;

	padlen = -rctx->cryptlen % POLY1305_BLOCK_SIZE;
	स_रखो(preq->pad, 0, माप(preq->pad));
	sg_init_one(preq->src, preq->pad, padlen);

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_cipherpad_करोne, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, preq->src, शून्य, padlen);

	err = crypto_ahash_update(&preq->req);
	अगर (err)
		वापस err;

	वापस poly_tail(req);
पूर्ण

अटल व्योम poly_cipher_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_cipherpad);
पूर्ण

अटल पूर्णांक poly_cipher(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा poly_req *preq = &rctx->u.poly;
	काष्ठा scatterlist *crypt = req->src;
	पूर्णांक err;

	अगर (rctx->cryptlen == req->cryptlen) /* encrypting */
		crypt = req->dst;

	crypt = scatterwalk_ffwd(rctx->src, crypt, req->assoclen);

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_cipher_करोne, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, crypt, शून्य, rctx->cryptlen);

	err = crypto_ahash_update(&preq->req);
	अगर (err)
		वापस err;

	वापस poly_cipherpad(req);
पूर्ण

अटल व्योम poly_adpad_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_cipher);
पूर्ण

अटल पूर्णांक poly_adpad(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा poly_req *preq = &rctx->u.poly;
	अचिन्हित पूर्णांक padlen;
	पूर्णांक err;

	padlen = -rctx->assoclen % POLY1305_BLOCK_SIZE;
	स_रखो(preq->pad, 0, माप(preq->pad));
	sg_init_one(preq->src, preq->pad, padlen);

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_adpad_करोne, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, preq->src, शून्य, padlen);

	err = crypto_ahash_update(&preq->req);
	अगर (err)
		वापस err;

	वापस poly_cipher(req);
पूर्ण

अटल व्योम poly_ad_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_adpad);
पूर्ण

अटल पूर्णांक poly_ad(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा poly_req *preq = &rctx->u.poly;
	पूर्णांक err;

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_ad_करोne, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, req->src, शून्य, rctx->assoclen);

	err = crypto_ahash_update(&preq->req);
	अगर (err)
		वापस err;

	वापस poly_adpad(req);
पूर्ण

अटल व्योम poly_setkey_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_ad);
पूर्ण

अटल पूर्णांक poly_setkey(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा poly_req *preq = &rctx->u.poly;
	पूर्णांक err;

	sg_init_one(preq->src, rctx->key, माप(rctx->key));

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_setkey_करोne, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);
	ahash_request_set_crypt(&preq->req, preq->src, शून्य, माप(rctx->key));

	err = crypto_ahash_update(&preq->req);
	अगर (err)
		वापस err;

	वापस poly_ad(req);
पूर्ण

अटल व्योम poly_init_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_setkey);
पूर्ण

अटल पूर्णांक poly_init(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा poly_req *preq = &rctx->u.poly;
	पूर्णांक err;

	ahash_request_set_callback(&preq->req, rctx->flags,
				   poly_init_करोne, req);
	ahash_request_set_tfm(&preq->req, ctx->poly);

	err = crypto_ahash_init(&preq->req);
	अगर (err)
		वापस err;

	वापस poly_setkey(req);
पूर्ण

अटल व्योम poly_genkey_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_init);
पूर्ण

अटल पूर्णांक poly_genkey(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा chacha_req *creq = &rctx->u.chacha;
	पूर्णांक err;

	rctx->assoclen = req->assoclen;

	अगर (crypto_aead_ivsize(tfm) == 8) अणु
		अगर (rctx->assoclen < 8)
			वापस -EINVAL;
		rctx->assoclen -= 8;
	पूर्ण

	स_रखो(rctx->key, 0, माप(rctx->key));
	sg_init_one(creq->src, rctx->key, माप(rctx->key));

	chacha_iv(creq->iv, req, 0);

	skcipher_request_set_callback(&creq->req, rctx->flags,
				      poly_genkey_करोne, req);
	skcipher_request_set_tfm(&creq->req, ctx->chacha);
	skcipher_request_set_crypt(&creq->req, creq->src, creq->src,
				   POLY1305_KEY_SIZE, creq->iv);

	err = crypto_skcipher_decrypt(&creq->req);
	अगर (err)
		वापस err;

	वापस poly_init(req);
पूर्ण

अटल व्योम chacha_encrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	async_करोne_जारी(areq->data, err, poly_genkey);
पूर्ण

अटल पूर्णांक chacha_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);
	काष्ठा chacha_req *creq = &rctx->u.chacha;
	काष्ठा scatterlist *src, *dst;
	पूर्णांक err;

	अगर (req->cryptlen == 0)
		जाओ skip;

	chacha_iv(creq->iv, req, 1);

	src = scatterwalk_ffwd(rctx->src, req->src, req->assoclen);
	dst = src;
	अगर (req->src != req->dst)
		dst = scatterwalk_ffwd(rctx->dst, req->dst, req->assoclen);

	skcipher_request_set_callback(&creq->req, rctx->flags,
				      chacha_encrypt_करोne, req);
	skcipher_request_set_tfm(&creq->req, ctx->chacha);
	skcipher_request_set_crypt(&creq->req, src, dst,
				   req->cryptlen, creq->iv);
	err = crypto_skcipher_encrypt(&creq->req);
	अगर (err)
		वापस err;

skip:
	वापस poly_genkey(req);
पूर्ण

अटल पूर्णांक chachapoly_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);

	rctx->cryptlen = req->cryptlen;
	rctx->flags = aead_request_flags(req);

	/* encrypt call chain:
	 * - chacha_encrypt/करोne()
	 * - poly_genkey/करोne()
	 * - poly_init/करोne()
	 * - poly_setkey/करोne()
	 * - poly_ad/करोne()
	 * - poly_adpad/करोne()
	 * - poly_cipher/करोne()
	 * - poly_cipherpad/करोne()
	 * - poly_tail/करोne/जारी()
	 * - poly_copy_tag()
	 */
	वापस chacha_encrypt(req);
पूर्ण

अटल पूर्णांक chachapoly_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा chachapoly_req_ctx *rctx = aead_request_ctx(req);

	rctx->cryptlen = req->cryptlen - POLY1305_DIGEST_SIZE;
	rctx->flags = aead_request_flags(req);

	/* decrypt call chain:
	 * - poly_genkey/करोne()
	 * - poly_init/करोne()
	 * - poly_setkey/करोne()
	 * - poly_ad/करोne()
	 * - poly_adpad/करोne()
	 * - poly_cipher/करोne()
	 * - poly_cipherpad/करोne()
	 * - poly_tail/करोne/जारी()
	 * - chacha_decrypt/करोne()
	 * - poly_verअगरy_tag()
	 */
	वापस poly_genkey(req);
पूर्ण

अटल पूर्णांक chachapoly_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(aead);

	अगर (keylen != ctx->saltlen + CHACHA_KEY_SIZE)
		वापस -EINVAL;

	keylen -= ctx->saltlen;
	स_नकल(ctx->salt, key + keylen, ctx->saltlen);

	crypto_skcipher_clear_flags(ctx->chacha, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(ctx->chacha, crypto_aead_get_flags(aead) &
					       CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(ctx->chacha, key, keylen);
पूर्ण

अटल पूर्णांक chachapoly_setauthsize(काष्ठा crypto_aead *tfm,
				  अचिन्हित पूर्णांक authsize)
अणु
	अगर (authsize != POLY1305_DIGEST_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक chachapoly_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा chachapoly_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_skcipher *chacha;
	काष्ठा crypto_ahash *poly;
	अचिन्हित दीर्घ align;

	poly = crypto_spawn_ahash(&ictx->poly);
	अगर (IS_ERR(poly))
		वापस PTR_ERR(poly);

	chacha = crypto_spawn_skcipher(&ictx->chacha);
	अगर (IS_ERR(chacha)) अणु
		crypto_मुक्त_ahash(poly);
		वापस PTR_ERR(chacha);
	पूर्ण

	ctx->chacha = chacha;
	ctx->poly = poly;
	ctx->saltlen = ictx->saltlen;

	align = crypto_aead_alignmask(tfm);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(
		tfm,
		align + दुरत्व(काष्ठा chachapoly_req_ctx, u) +
		max(दुरत्व(काष्ठा chacha_req, req) +
		    माप(काष्ठा skcipher_request) +
		    crypto_skcipher_reqsize(chacha),
		    दुरत्व(काष्ठा poly_req, req) +
		    माप(काष्ठा ahash_request) +
		    crypto_ahash_reqsize(poly)));

	वापस 0;
पूर्ण

अटल व्योम chachapoly_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा chachapoly_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_ahash(ctx->poly);
	crypto_मुक्त_skcipher(ctx->chacha);
पूर्ण

अटल व्योम chachapoly_मुक्त(काष्ठा aead_instance *inst)
अणु
	काष्ठा chachapoly_instance_ctx *ctx = aead_instance_ctx(inst);

	crypto_drop_skcipher(&ctx->chacha);
	crypto_drop_ahash(&ctx->poly);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक chachapoly_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb,
			     स्थिर अक्षर *name, अचिन्हित पूर्णांक ivsize)
अणु
	u32 mask;
	काष्ठा aead_instance *inst;
	काष्ठा chachapoly_instance_ctx *ctx;
	काष्ठा skcipher_alg *chacha;
	काष्ठा hash_alg_common *poly;
	पूर्णांक err;

	अगर (ivsize > CHACHAPOLY_IV_SIZE)
		वापस -EINVAL;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_AEAD, &mask);
	अगर (err)
		वापस err;

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;
	ctx = aead_instance_ctx(inst);
	ctx->saltlen = CHACHAPOLY_IV_SIZE - ivsize;

	err = crypto_grab_skcipher(&ctx->chacha, aead_crypto_instance(inst),
				   crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	chacha = crypto_spawn_skcipher_alg(&ctx->chacha);

	err = crypto_grab_ahash(&ctx->poly, aead_crypto_instance(inst),
				crypto_attr_alg_name(tb[2]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	poly = crypto_spawn_ahash_alg(&ctx->poly);

	err = -EINVAL;
	अगर (poly->digestsize != POLY1305_DIGEST_SIZE)
		जाओ err_मुक्त_inst;
	/* Need 16-byte IV size, including Initial Block Counter value */
	अगर (crypto_skcipher_alg_ivsize(chacha) != CHACHA_IV_SIZE)
		जाओ err_मुक्त_inst;
	/* Not a stream cipher? */
	अगर (chacha->base.cra_blocksize != 1)
		जाओ err_मुक्त_inst;

	err = -ENAMETOOLONG;
	अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
		     "%s(%s,%s)", name, chacha->base.cra_name,
		     poly->base.cra_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;
	अगर (snम_लिखो(inst->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "%s(%s,%s)", name, chacha->base.cra_driver_name,
		     poly->base.cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = (chacha->base.cra_priority +
				       poly->base.cra_priority) / 2;
	inst->alg.base.cra_blocksize = 1;
	inst->alg.base.cra_alignmask = chacha->base.cra_alignmask |
				       poly->base.cra_alignmask;
	inst->alg.base.cra_ctxsize = माप(काष्ठा chachapoly_ctx) +
				     ctx->saltlen;
	inst->alg.ivsize = ivsize;
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(chacha);
	inst->alg.maxauthsize = POLY1305_DIGEST_SIZE;
	inst->alg.init = chachapoly_init;
	inst->alg.निकास = chachapoly_निकास;
	inst->alg.encrypt = chachapoly_encrypt;
	inst->alg.decrypt = chachapoly_decrypt;
	inst->alg.setkey = chachapoly_setkey;
	inst->alg.setauthsize = chachapoly_setauthsize;

	inst->मुक्त = chachapoly_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		chachapoly_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक rfc7539_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	वापस chachapoly_create(पंचांगpl, tb, "rfc7539", 12);
पूर्ण

अटल पूर्णांक rfc7539esp_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	वापस chachapoly_create(पंचांगpl, tb, "rfc7539esp", 8);
पूर्ण

अटल काष्ठा crypto_ढाँचा rfc7539_पंचांगpls[] = अणु
	अणु
		.name = "rfc7539",
		.create = rfc7539_create,
		.module = THIS_MODULE,
	पूर्ण, अणु
		.name = "rfc7539esp",
		.create = rfc7539esp_create,
		.module = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init chacha20poly1305_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचाs(rfc7539_पंचांगpls,
					 ARRAY_SIZE(rfc7539_पंचांगpls));
पूर्ण

अटल व्योम __निकास chacha20poly1305_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचाs(rfc7539_पंचांगpls,
				    ARRAY_SIZE(rfc7539_पंचांगpls));
पूर्ण

subsys_initcall(chacha20poly1305_module_init);
module_निकास(chacha20poly1305_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Willi <martin@strongswan.org>");
MODULE_DESCRIPTION("ChaCha20-Poly1305 AEAD");
MODULE_ALIAS_CRYPTO("rfc7539");
MODULE_ALIAS_CRYPTO("rfc7539esp");
