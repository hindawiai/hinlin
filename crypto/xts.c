<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* XTS: as defined in IEEE1619/D16
 *	http://grouper.ieee.org/groups/1619/email/pdf00086.pdf
 *
 * Copyright (c) 2007 Rik Snel <rsnel@cube.dyndns.org>
 *
 * Based on ecb.c
 * Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

#समावेश <crypto/xts.h>
#समावेश <crypto/b128ops.h>
#समावेश <crypto/gf128mul.h>

काष्ठा xts_tfm_ctx अणु
	काष्ठा crypto_skcipher *child;
	काष्ठा crypto_cipher *tweak;
पूर्ण;

काष्ठा xts_instance_ctx अणु
	काष्ठा crypto_skcipher_spawn spawn;
	अक्षर name[CRYPTO_MAX_ALG_NAME];
पूर्ण;

काष्ठा xts_request_ctx अणु
	le128 t;
	काष्ठा scatterlist *tail;
	काष्ठा scatterlist sg[2];
	काष्ठा skcipher_request subreq;
पूर्ण;

अटल पूर्णांक xts_setkey(काष्ठा crypto_skcipher *parent, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा xts_tfm_ctx *ctx = crypto_skcipher_ctx(parent);
	काष्ठा crypto_skcipher *child;
	काष्ठा crypto_cipher *tweak;
	पूर्णांक err;

	err = xts_verअगरy_key(parent, key, keylen);
	अगर (err)
		वापस err;

	keylen /= 2;

	/* we need two cipher instances: one to compute the initial 'tweak'
	 * by encrypting the IV (usually the 'plain' iv) and the other
	 * one to encrypt and decrypt the data */

	/* tweak cipher, uses Key2 i.e. the second half of *key */
	tweak = ctx->tweak;
	crypto_cipher_clear_flags(tweak, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(tweak, crypto_skcipher_get_flags(parent) &
				       CRYPTO_TFM_REQ_MASK);
	err = crypto_cipher_setkey(tweak, key + keylen, keylen);
	अगर (err)
		वापस err;

	/* data cipher, uses Key1 i.e. the first half of *key */
	child = ctx->child;
	crypto_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(child, crypto_skcipher_get_flags(parent) &
					 CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(child, key, keylen);
पूर्ण

/*
 * We compute the tweak masks twice (both beक्रमe and after the ECB encryption or
 * decryption) to aव्योम having to allocate a temporary buffer and/or make
 * mutliple calls to the 'ecb(..)' instance, which usually would be slower than
 * just करोing the gf128mul_x_ble() calls again.
 */
अटल पूर्णांक xts_xor_tweak(काष्ठा skcipher_request *req, bool second_pass,
			 bool enc)
अणु
	काष्ठा xts_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर bool cts = (req->cryptlen % XTS_BLOCK_SIZE);
	स्थिर पूर्णांक bs = XTS_BLOCK_SIZE;
	काष्ठा skcipher_walk w;
	le128 t = rctx->t;
	पूर्णांक err;

	अगर (second_pass) अणु
		req = &rctx->subreq;
		/* set to our TFM to enक्रमce correct alignment: */
		skcipher_request_set_tfm(req, tfm);
	पूर्ण
	err = skcipher_walk_virt(&w, req, false);

	जबतक (w.nbytes) अणु
		अचिन्हित पूर्णांक avail = w.nbytes;
		le128 *wsrc;
		le128 *wdst;

		wsrc = w.src.virt.addr;
		wdst = w.dst.virt.addr;

		करो अणु
			अगर (unlikely(cts) &&
			    w.total - w.nbytes + avail < 2 * XTS_BLOCK_SIZE) अणु
				अगर (!enc) अणु
					अगर (second_pass)
						rctx->t = t;
					gf128mul_x_ble(&t, &t);
				पूर्ण
				le128_xor(wdst, &t, wsrc);
				अगर (enc && second_pass)
					gf128mul_x_ble(&rctx->t, &t);
				skcipher_walk_करोne(&w, avail - bs);
				वापस 0;
			पूर्ण

			le128_xor(wdst++, &t, wsrc++);
			gf128mul_x_ble(&t, &t);
		पूर्ण जबतक ((avail -= bs) >= bs);

		err = skcipher_walk_करोne(&w, avail);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक xts_xor_tweak_pre(काष्ठा skcipher_request *req, bool enc)
अणु
	वापस xts_xor_tweak(req, false, enc);
पूर्ण

अटल पूर्णांक xts_xor_tweak_post(काष्ठा skcipher_request *req, bool enc)
अणु
	वापस xts_xor_tweak(req, true, enc);
पूर्ण

अटल व्योम xts_cts_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;
	le128 b;

	अगर (!err) अणु
		काष्ठा xts_request_ctx *rctx = skcipher_request_ctx(req);

		scatterwalk_map_and_copy(&b, rctx->tail, 0, XTS_BLOCK_SIZE, 0);
		le128_xor(&b, &rctx->t, &b);
		scatterwalk_map_and_copy(&b, rctx->tail, 0, XTS_BLOCK_SIZE, 1);
	पूर्ण

	skcipher_request_complete(req, err);
पूर्ण

अटल पूर्णांक xts_cts_final(काष्ठा skcipher_request *req,
			 पूर्णांक (*crypt)(काष्ठा skcipher_request *req))
अणु
	स्थिर काष्ठा xts_tfm_ctx *ctx =
		crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	पूर्णांक offset = req->cryptlen & ~(XTS_BLOCK_SIZE - 1);
	काष्ठा xts_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;
	पूर्णांक tail = req->cryptlen % XTS_BLOCK_SIZE;
	le128 b[2];
	पूर्णांक err;

	rctx->tail = scatterwalk_ffwd(rctx->sg, req->dst,
				      offset - XTS_BLOCK_SIZE);

	scatterwalk_map_and_copy(b, rctx->tail, 0, XTS_BLOCK_SIZE, 0);
	b[1] = b[0];
	scatterwalk_map_and_copy(b, req->src, offset, tail, 0);

	le128_xor(b, &rctx->t, b);

	scatterwalk_map_and_copy(b, rctx->tail, 0, XTS_BLOCK_SIZE + tail, 1);

	skcipher_request_set_tfm(subreq, ctx->child);
	skcipher_request_set_callback(subreq, req->base.flags, xts_cts_करोne,
				      req);
	skcipher_request_set_crypt(subreq, rctx->tail, rctx->tail,
				   XTS_BLOCK_SIZE, शून्य);

	err = crypt(subreq);
	अगर (err)
		वापस err;

	scatterwalk_map_and_copy(b, rctx->tail, 0, XTS_BLOCK_SIZE, 0);
	le128_xor(b, &rctx->t, b);
	scatterwalk_map_and_copy(b, rctx->tail, 0, XTS_BLOCK_SIZE, 1);

	वापस 0;
पूर्ण

अटल व्योम xts_encrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;

	अगर (!err) अणु
		काष्ठा xts_request_ctx *rctx = skcipher_request_ctx(req);

		rctx->subreq.base.flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
		err = xts_xor_tweak_post(req, true);

		अगर (!err && unlikely(req->cryptlen % XTS_BLOCK_SIZE)) अणु
			err = xts_cts_final(req, crypto_skcipher_encrypt);
			अगर (err == -EINPROGRESS)
				वापस;
		पूर्ण
	पूर्ण

	skcipher_request_complete(req, err);
पूर्ण

अटल व्योम xts_decrypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;

	अगर (!err) अणु
		काष्ठा xts_request_ctx *rctx = skcipher_request_ctx(req);

		rctx->subreq.base.flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
		err = xts_xor_tweak_post(req, false);

		अगर (!err && unlikely(req->cryptlen % XTS_BLOCK_SIZE)) अणु
			err = xts_cts_final(req, crypto_skcipher_decrypt);
			अगर (err == -EINPROGRESS)
				वापस;
		पूर्ण
	पूर्ण

	skcipher_request_complete(req, err);
पूर्ण

अटल पूर्णांक xts_init_crypt(काष्ठा skcipher_request *req,
			  crypto_completion_t compl)
अणु
	स्थिर काष्ठा xts_tfm_ctx *ctx =
		crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	काष्ठा xts_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;

	अगर (req->cryptlen < XTS_BLOCK_SIZE)
		वापस -EINVAL;

	skcipher_request_set_tfm(subreq, ctx->child);
	skcipher_request_set_callback(subreq, req->base.flags, compl, req);
	skcipher_request_set_crypt(subreq, req->dst, req->dst,
				   req->cryptlen & ~(XTS_BLOCK_SIZE - 1), शून्य);

	/* calculate first value of T */
	crypto_cipher_encrypt_one(ctx->tweak, (u8 *)&rctx->t, req->iv);

	वापस 0;
पूर्ण

अटल पूर्णांक xts_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा xts_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;
	पूर्णांक err;

	err = xts_init_crypt(req, xts_encrypt_करोne) ?:
	      xts_xor_tweak_pre(req, true) ?:
	      crypto_skcipher_encrypt(subreq) ?:
	      xts_xor_tweak_post(req, true);

	अगर (err || likely((req->cryptlen % XTS_BLOCK_SIZE) == 0))
		वापस err;

	वापस xts_cts_final(req, crypto_skcipher_encrypt);
पूर्ण

अटल पूर्णांक xts_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा xts_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;
	पूर्णांक err;

	err = xts_init_crypt(req, xts_decrypt_करोne) ?:
	      xts_xor_tweak_pre(req, false) ?:
	      crypto_skcipher_decrypt(subreq) ?:
	      xts_xor_tweak_post(req, false);

	अगर (err || likely((req->cryptlen % XTS_BLOCK_SIZE) == 0))
		वापस err;

	वापस xts_cts_final(req, crypto_skcipher_decrypt);
पूर्ण

अटल पूर्णांक xts_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_instance *inst = skcipher_alg_instance(tfm);
	काष्ठा xts_instance_ctx *ictx = skcipher_instance_ctx(inst);
	काष्ठा xts_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *child;
	काष्ठा crypto_cipher *tweak;

	child = crypto_spawn_skcipher(&ictx->spawn);
	अगर (IS_ERR(child))
		वापस PTR_ERR(child);

	ctx->child = child;

	tweak = crypto_alloc_cipher(ictx->name, 0, 0);
	अगर (IS_ERR(tweak)) अणु
		crypto_मुक्त_skcipher(ctx->child);
		वापस PTR_ERR(tweak);
	पूर्ण

	ctx->tweak = tweak;

	crypto_skcipher_set_reqsize(tfm, crypto_skcipher_reqsize(child) +
					 माप(काष्ठा xts_request_ctx));

	वापस 0;
पूर्ण

अटल व्योम xts_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा xts_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(ctx->child);
	crypto_मुक्त_cipher(ctx->tweak);
पूर्ण

अटल व्योम xts_मुक्त_instance(काष्ठा skcipher_instance *inst)
अणु
	काष्ठा xts_instance_ctx *ictx = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(&ictx->spawn);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक xts_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा skcipher_instance *inst;
	काष्ठा xts_instance_ctx *ctx;
	काष्ठा skcipher_alg *alg;
	स्थिर अक्षर *cipher_name;
	u32 mask;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SKCIPHER, &mask);
	अगर (err)
		वापस err;

	cipher_name = crypto_attr_alg_name(tb[1]);
	अगर (IS_ERR(cipher_name))
		वापस PTR_ERR(cipher_name);

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	ctx = skcipher_instance_ctx(inst);

	err = crypto_grab_skcipher(&ctx->spawn, skcipher_crypto_instance(inst),
				   cipher_name, 0, mask);
	अगर (err == -ENOENT) अणु
		err = -ENAMETOOLONG;
		अगर (snम_लिखो(ctx->name, CRYPTO_MAX_ALG_NAME, "ecb(%s)",
			     cipher_name) >= CRYPTO_MAX_ALG_NAME)
			जाओ err_मुक्त_inst;

		err = crypto_grab_skcipher(&ctx->spawn,
					   skcipher_crypto_instance(inst),
					   ctx->name, 0, mask);
	पूर्ण

	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_skcipher_spawn_alg(&ctx->spawn);

	err = -EINVAL;
	अगर (alg->base.cra_blocksize != XTS_BLOCK_SIZE)
		जाओ err_मुक्त_inst;

	अगर (crypto_skcipher_alg_ivsize(alg))
		जाओ err_मुक्त_inst;

	err = crypto_inst_setname(skcipher_crypto_instance(inst), "xts",
				  &alg->base);
	अगर (err)
		जाओ err_मुक्त_inst;

	err = -EINVAL;
	cipher_name = alg->base.cra_name;

	/* Alas we screwed up the naming so we have to mangle the
	 * cipher name.
	 */
	अगर (!म_भेदन(cipher_name, "ecb(", 4)) अणु
		अचिन्हित len;

		len = strlcpy(ctx->name, cipher_name + 4, माप(ctx->name));
		अगर (len < 2 || len >= माप(ctx->name))
			जाओ err_मुक्त_inst;

		अगर (ctx->name[len - 1] != ')')
			जाओ err_मुक्त_inst;

		ctx->name[len - 1] = 0;

		अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
			     "xts(%s)", ctx->name) >= CRYPTO_MAX_ALG_NAME) अणु
			err = -ENAMETOOLONG;
			जाओ err_मुक्त_inst;
		पूर्ण
	पूर्ण अन्यथा
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->base.cra_priority;
	inst->alg.base.cra_blocksize = XTS_BLOCK_SIZE;
	inst->alg.base.cra_alignmask = alg->base.cra_alignmask |
				       (__alignof__(u64) - 1);

	inst->alg.ivsize = XTS_BLOCK_SIZE;
	inst->alg.min_keysize = crypto_skcipher_alg_min_keysize(alg) * 2;
	inst->alg.max_keysize = crypto_skcipher_alg_max_keysize(alg) * 2;

	inst->alg.base.cra_ctxsize = माप(काष्ठा xts_tfm_ctx);

	inst->alg.init = xts_init_tfm;
	inst->alg.निकास = xts_निकास_tfm;

	inst->alg.setkey = xts_setkey;
	inst->alg.encrypt = xts_encrypt;
	inst->alg.decrypt = xts_decrypt;

	inst->मुक्त = xts_मुक्त_instance;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		xts_मुक्त_instance(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा xts_पंचांगpl = अणु
	.name = "xts",
	.create = xts_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init xts_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&xts_पंचांगpl);
पूर्ण

अटल व्योम __निकास xts_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&xts_पंचांगpl);
पूर्ण

subsys_initcall(xts_module_init);
module_निकास(xts_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("XTS block cipher mode");
MODULE_ALIAS_CRYPTO("xts");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
