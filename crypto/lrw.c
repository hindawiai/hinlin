<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* LRW: as defined by Cyril Guyot in
 *	http://grouper.ieee.org/groups/1619/email/pdf00017.pdf
 *
 * Copyright (c) 2006 Rik Snel <rsnel@cube.dyndns.org>
 *
 * Based on ecb.c
 * Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */
/* This implementation is checked against the test vectors in the above
 * करोcument and by a test vector provided by Ken Buchanan at
 * https://www.mail-archive.com/stds-p1619@listserv.ieee.org/msg00173.hपंचांगl
 *
 * The test vectors are included in the testing module tcrypt.[ch] */

#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

#समावेश <crypto/b128ops.h>
#समावेश <crypto/gf128mul.h>

#घोषणा LRW_BLOCK_SIZE 16

काष्ठा lrw_tfm_ctx अणु
	काष्ठा crypto_skcipher *child;

	/*
	 * optimizes multiplying a अक्रमom (non incrementing, as at the
	 * start of a new sector) value with key2, we could also have
	 * used 4k optimization tables or no optimization at all. In the
	 * latter हाल we would have to store key2 here
	 */
	काष्ठा gf128mul_64k *table;

	/*
	 * stores:
	 *  key2*अणु 0,0,...0,0,0,0,1 पूर्ण, key2*अणु 0,0,...0,0,0,1,1 पूर्ण,
	 *  key2*अणु 0,0,...0,0,1,1,1 पूर्ण, key2*अणु 0,0,...0,1,1,1,1 पूर्ण
	 *  key2*अणु 0,0,...1,1,1,1,1 पूर्ण, etc
	 * needed क्रम optimized multiplication of incrementing values
	 * with key2
	 */
	be128 mulinc[128];
पूर्ण;

काष्ठा lrw_request_ctx अणु
	be128 t;
	काष्ठा skcipher_request subreq;
पूर्ण;

अटल अंतरभूत व्योम lrw_setbit128_bbe(व्योम *b, पूर्णांक bit)
अणु
	__set_bit(bit ^ (0x80 -
#अगर_घोषित __BIG_ENDIAN
			 BITS_PER_LONG
#अन्यथा
			 BITS_PER_BYTE
#पूर्ण_अगर
			), b);
पूर्ण

अटल पूर्णांक lrw_setkey(काष्ठा crypto_skcipher *parent, स्थिर u8 *key,
		      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा lrw_tfm_ctx *ctx = crypto_skcipher_ctx(parent);
	काष्ठा crypto_skcipher *child = ctx->child;
	पूर्णांक err, bsize = LRW_BLOCK_SIZE;
	स्थिर u8 *tweak = key + keylen - bsize;
	be128 पंचांगp = अणु 0 पूर्ण;
	पूर्णांक i;

	crypto_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(child, crypto_skcipher_get_flags(parent) &
					 CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(child, key, keylen - bsize);
	अगर (err)
		वापस err;

	अगर (ctx->table)
		gf128mul_मुक्त_64k(ctx->table);

	/* initialize multiplication table क्रम Key2 */
	ctx->table = gf128mul_init_64k_bbe((be128 *)tweak);
	अगर (!ctx->table)
		वापस -ENOMEM;

	/* initialize optimization table */
	क्रम (i = 0; i < 128; i++) अणु
		lrw_setbit128_bbe(&पंचांगp, i);
		ctx->mulinc[i] = पंचांगp;
		gf128mul_64k_bbe(&ctx->mulinc[i], ctx->table);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Returns the number of trailing '1' bits in the words of the counter, which is
 * represented by 4 32-bit words, arranged from least to most signअगरicant.
 * At the same समय, increments the counter by one.
 *
 * For example:
 *
 * u32 counter[4] = अणु 0xFFFFFFFF, 0x1, 0x0, 0x0 पूर्ण;
 * पूर्णांक i = lrw_next_index(&counter);
 * // i == 33, counter == अणु 0x0, 0x2, 0x0, 0x0 पूर्ण
 */
अटल पूर्णांक lrw_next_index(u32 *counter)
अणु
	पूर्णांक i, res = 0;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (counter[i] + 1 != 0)
			वापस res + ffz(counter[i]++);

		counter[i] = 0;
		res += 32;
	पूर्ण

	/*
	 * If we get here, then x == 128 and we are incrementing the counter
	 * from all ones to all zeros. This means we must वापस index 127, i.e.
	 * the one corresponding to key2*अणु 1,...,1 पूर्ण.
	 */
	वापस 127;
पूर्ण

/*
 * We compute the tweak masks twice (both beक्रमe and after the ECB encryption or
 * decryption) to aव्योम having to allocate a temporary buffer and/or make
 * mutliple calls to the 'ecb(..)' instance, which usually would be slower than
 * just करोing the lrw_next_index() calls again.
 */
अटल पूर्णांक lrw_xor_tweak(काष्ठा skcipher_request *req, bool second_pass)
अणु
	स्थिर पूर्णांक bs = LRW_BLOCK_SIZE;
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा lrw_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा lrw_request_ctx *rctx = skcipher_request_ctx(req);
	be128 t = rctx->t;
	काष्ठा skcipher_walk w;
	__be32 *iv;
	u32 counter[4];
	पूर्णांक err;

	अगर (second_pass) अणु
		req = &rctx->subreq;
		/* set to our TFM to enक्रमce correct alignment: */
		skcipher_request_set_tfm(req, tfm);
	पूर्ण

	err = skcipher_walk_virt(&w, req, false);
	अगर (err)
		वापस err;

	iv = (__be32 *)w.iv;
	counter[0] = be32_to_cpu(iv[3]);
	counter[1] = be32_to_cpu(iv[2]);
	counter[2] = be32_to_cpu(iv[1]);
	counter[3] = be32_to_cpu(iv[0]);

	जबतक (w.nbytes) अणु
		अचिन्हित पूर्णांक avail = w.nbytes;
		be128 *wsrc;
		be128 *wdst;

		wsrc = w.src.virt.addr;
		wdst = w.dst.virt.addr;

		करो अणु
			be128_xor(wdst++, &t, wsrc++);

			/* T <- I*Key2, using the optimization
			 * discussed in the specअगरication */
			be128_xor(&t, &t,
				  &ctx->mulinc[lrw_next_index(counter)]);
		पूर्ण जबतक ((avail -= bs) >= bs);

		अगर (second_pass && w.nbytes == w.total) अणु
			iv[0] = cpu_to_be32(counter[3]);
			iv[1] = cpu_to_be32(counter[2]);
			iv[2] = cpu_to_be32(counter[1]);
			iv[3] = cpu_to_be32(counter[0]);
		पूर्ण

		err = skcipher_walk_करोne(&w, avail);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक lrw_xor_tweak_pre(काष्ठा skcipher_request *req)
अणु
	वापस lrw_xor_tweak(req, false);
पूर्ण

अटल पूर्णांक lrw_xor_tweak_post(काष्ठा skcipher_request *req)
अणु
	वापस lrw_xor_tweak(req, true);
पूर्ण

अटल व्योम lrw_crypt_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = areq->data;

	अगर (!err) अणु
		काष्ठा lrw_request_ctx *rctx = skcipher_request_ctx(req);

		rctx->subreq.base.flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
		err = lrw_xor_tweak_post(req);
	पूर्ण

	skcipher_request_complete(req, err);
पूर्ण

अटल व्योम lrw_init_crypt(काष्ठा skcipher_request *req)
अणु
	स्थिर काष्ठा lrw_tfm_ctx *ctx =
		crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	काष्ठा lrw_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;

	skcipher_request_set_tfm(subreq, ctx->child);
	skcipher_request_set_callback(subreq, req->base.flags, lrw_crypt_करोne,
				      req);
	/* pass req->iv as IV (will be used by xor_tweak, ECB will ignore it) */
	skcipher_request_set_crypt(subreq, req->dst, req->dst,
				   req->cryptlen, req->iv);

	/* calculate first value of T */
	स_नकल(&rctx->t, req->iv, माप(rctx->t));

	/* T <- I*Key2 */
	gf128mul_64k_bbe(&rctx->t, ctx->table);
पूर्ण

अटल पूर्णांक lrw_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा lrw_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;

	lrw_init_crypt(req);
	वापस lrw_xor_tweak_pre(req) ?:
		crypto_skcipher_encrypt(subreq) ?:
		lrw_xor_tweak_post(req);
पूर्ण

अटल पूर्णांक lrw_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा lrw_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा skcipher_request *subreq = &rctx->subreq;

	lrw_init_crypt(req);
	वापस lrw_xor_tweak_pre(req) ?:
		crypto_skcipher_decrypt(subreq) ?:
		lrw_xor_tweak_post(req);
पूर्ण

अटल पूर्णांक lrw_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_instance *inst = skcipher_alg_instance(tfm);
	काष्ठा crypto_skcipher_spawn *spawn = skcipher_instance_ctx(inst);
	काष्ठा lrw_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *cipher;

	cipher = crypto_spawn_skcipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = cipher;

	crypto_skcipher_set_reqsize(tfm, crypto_skcipher_reqsize(cipher) +
					 माप(काष्ठा lrw_request_ctx));

	वापस 0;
पूर्ण

अटल व्योम lrw_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा lrw_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);

	अगर (ctx->table)
		gf128mul_मुक्त_64k(ctx->table);
	crypto_मुक्त_skcipher(ctx->child);
पूर्ण

अटल व्योम lrw_मुक्त_instance(काष्ठा skcipher_instance *inst)
अणु
	crypto_drop_skcipher(skcipher_instance_ctx(inst));
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक lrw_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा crypto_skcipher_spawn *spawn;
	काष्ठा skcipher_instance *inst;
	काष्ठा skcipher_alg *alg;
	स्थिर अक्षर *cipher_name;
	अक्षर ecb_name[CRYPTO_MAX_ALG_NAME];
	u32 mask;
	पूर्णांक err;

	err = crypto_check_attr_type(tb, CRYPTO_ALG_TYPE_SKCIPHER, &mask);
	अगर (err)
		वापस err;

	cipher_name = crypto_attr_alg_name(tb[1]);
	अगर (IS_ERR(cipher_name))
		वापस PTR_ERR(cipher_name);

	inst = kzalloc(माप(*inst) + माप(*spawn), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	spawn = skcipher_instance_ctx(inst);

	err = crypto_grab_skcipher(spawn, skcipher_crypto_instance(inst),
				   cipher_name, 0, mask);
	अगर (err == -ENOENT) अणु
		err = -ENAMETOOLONG;
		अगर (snम_लिखो(ecb_name, CRYPTO_MAX_ALG_NAME, "ecb(%s)",
			     cipher_name) >= CRYPTO_MAX_ALG_NAME)
			जाओ err_मुक्त_inst;

		err = crypto_grab_skcipher(spawn,
					   skcipher_crypto_instance(inst),
					   ecb_name, 0, mask);
	पूर्ण

	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_skcipher_spawn_alg(spawn);

	err = -EINVAL;
	अगर (alg->base.cra_blocksize != LRW_BLOCK_SIZE)
		जाओ err_मुक्त_inst;

	अगर (crypto_skcipher_alg_ivsize(alg))
		जाओ err_मुक्त_inst;

	err = crypto_inst_setname(skcipher_crypto_instance(inst), "lrw",
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

		len = strlcpy(ecb_name, cipher_name + 4, माप(ecb_name));
		अगर (len < 2 || len >= माप(ecb_name))
			जाओ err_मुक्त_inst;

		अगर (ecb_name[len - 1] != ')')
			जाओ err_मुक्त_inst;

		ecb_name[len - 1] = 0;

		अगर (snम_लिखो(inst->alg.base.cra_name, CRYPTO_MAX_ALG_NAME,
			     "lrw(%s)", ecb_name) >= CRYPTO_MAX_ALG_NAME) अणु
			err = -ENAMETOOLONG;
			जाओ err_मुक्त_inst;
		पूर्ण
	पूर्ण अन्यथा
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_priority = alg->base.cra_priority;
	inst->alg.base.cra_blocksize = LRW_BLOCK_SIZE;
	inst->alg.base.cra_alignmask = alg->base.cra_alignmask |
				       (__alignof__(be128) - 1);

	inst->alg.ivsize = LRW_BLOCK_SIZE;
	inst->alg.min_keysize = crypto_skcipher_alg_min_keysize(alg) +
				LRW_BLOCK_SIZE;
	inst->alg.max_keysize = crypto_skcipher_alg_max_keysize(alg) +
				LRW_BLOCK_SIZE;

	inst->alg.base.cra_ctxsize = माप(काष्ठा lrw_tfm_ctx);

	inst->alg.init = lrw_init_tfm;
	inst->alg.निकास = lrw_निकास_tfm;

	inst->alg.setkey = lrw_setkey;
	inst->alg.encrypt = lrw_encrypt;
	inst->alg.decrypt = lrw_decrypt;

	inst->मुक्त = lrw_मुक्त_instance;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		lrw_मुक्त_instance(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा lrw_पंचांगpl = अणु
	.name = "lrw",
	.create = lrw_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init lrw_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&lrw_पंचांगpl);
पूर्ण

अटल व्योम __निकास lrw_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&lrw_पंचांगpl);
पूर्ण

subsys_initcall(lrw_module_init);
module_निकास(lrw_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LRW block cipher mode");
MODULE_ALIAS_CRYPTO("lrw");
