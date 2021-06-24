<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ChaCha and XChaCha stream ciphers, including ChaCha20 (RFC7539)
 *
 * Copyright (C) 2015 Martin Willi
 * Copyright (C) 2018 Google LLC
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/chacha.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/module.h>

अटल पूर्णांक chacha_stream_xor(काष्ठा skcipher_request *req,
			     स्थिर काष्ठा chacha_ctx *ctx, स्थिर u8 *iv)
अणु
	काष्ठा skcipher_walk walk;
	u32 state[16];
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	chacha_init_generic(state, ctx->key, iv);

	जबतक (walk.nbytes > 0) अणु
		अचिन्हित पूर्णांक nbytes = walk.nbytes;

		अगर (nbytes < walk.total)
			nbytes = round_करोwn(nbytes, CHACHA_BLOCK_SIZE);

		chacha_crypt_generic(state, walk.dst.virt.addr,
				     walk.src.virt.addr, nbytes, ctx->nrounds);
		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_chacha_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस chacha_stream_xor(req, ctx, req->iv);
पूर्ण

अटल पूर्णांक crypto_xchacha_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा chacha_ctx subctx;
	u32 state[16];
	u8 real_iv[16];

	/* Compute the subkey given the original key and first 128 nonce bits */
	chacha_init_generic(state, ctx->key, req->iv);
	hchacha_block_generic(state, subctx.key, ctx->nrounds);
	subctx.nrounds = ctx->nrounds;

	/* Build the real IV */
	स_नकल(&real_iv[0], req->iv + 24, 8); /* stream position */
	स_नकल(&real_iv[8], req->iv + 16, 8); /* reमुख्यing 64 nonce bits */

	/* Generate the stream and XOR it with the data */
	वापस chacha_stream_xor(req, &subctx, real_iv);
पूर्ण

अटल काष्ठा skcipher_alg algs[] = अणु
	अणु
		.base.cra_name		= "chacha20",
		.base.cra_driver_name	= "chacha20-generic",
		.base.cra_priority	= 100,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= crypto_chacha_crypt,
		.decrypt		= crypto_chacha_crypt,
	पूर्ण, अणु
		.base.cra_name		= "xchacha20",
		.base.cra_driver_name	= "xchacha20-generic",
		.base.cra_priority	= 100,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= crypto_xchacha_crypt,
		.decrypt		= crypto_xchacha_crypt,
	पूर्ण, अणु
		.base.cra_name		= "xchacha12",
		.base.cra_driver_name	= "xchacha12-generic",
		.base.cra_priority	= 100,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encrypt		= crypto_xchacha_crypt,
		.decrypt		= crypto_xchacha_crypt,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init chacha_generic_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
पूर्ण

अटल व्योम __निकास chacha_generic_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
पूर्ण

subsys_initcall(chacha_generic_mod_init);
module_निकास(chacha_generic_mod_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Willi <martin@strongswan.org>");
MODULE_DESCRIPTION("ChaCha and XChaCha stream ciphers (generic)");
MODULE_ALIAS_CRYPTO("chacha20");
MODULE_ALIAS_CRYPTO("chacha20-generic");
MODULE_ALIAS_CRYPTO("xchacha20");
MODULE_ALIAS_CRYPTO("xchacha20-generic");
MODULE_ALIAS_CRYPTO("xchacha12");
MODULE_ALIAS_CRYPTO("xchacha12-generic");
