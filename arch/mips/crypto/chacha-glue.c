<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MIPS accelerated ChaCha and XChaCha stream ciphers,
 * including ChaCha20 (RFC7539)
 *
 * Copyright (C) 2019 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/byteorder.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/chacha.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

यंत्रlinkage व्योम chacha_crypt_arch(u32 *state, u8 *dst, स्थिर u8 *src,
				  अचिन्हित पूर्णांक bytes, पूर्णांक nrounds);
EXPORT_SYMBOL(chacha_crypt_arch);

यंत्रlinkage व्योम hchacha_block_arch(स्थिर u32 *state, u32 *stream, पूर्णांक nrounds);
EXPORT_SYMBOL(hchacha_block_arch);

व्योम chacha_init_arch(u32 *state, स्थिर u32 *key, स्थिर u8 *iv)
अणु
	chacha_init_generic(state, key, iv);
पूर्ण
EXPORT_SYMBOL(chacha_init_arch);

अटल पूर्णांक chacha_mips_stream_xor(काष्ठा skcipher_request *req,
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
			nbytes = round_करोwn(nbytes, walk.stride);

		chacha_crypt(state, walk.dst.virt.addr, walk.src.virt.addr,
			     nbytes, ctx->nrounds);
		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक chacha_mips(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस chacha_mips_stream_xor(req, ctx, req->iv);
पूर्ण

अटल पूर्णांक xchacha_mips(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा chacha_ctx subctx;
	u32 state[16];
	u8 real_iv[16];

	chacha_init_generic(state, ctx->key, req->iv);

	hchacha_block(state, subctx.key, ctx->nrounds);
	subctx.nrounds = ctx->nrounds;

	स_नकल(&real_iv[0], req->iv + 24, 8);
	स_नकल(&real_iv[8], req->iv + 16, 8);
	वापस chacha_mips_stream_xor(req, &subctx, real_iv);
पूर्ण

अटल काष्ठा skcipher_alg algs[] = अणु
	अणु
		.base.cra_name		= "chacha20",
		.base.cra_driver_name	= "chacha20-mips",
		.base.cra_priority	= 200,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= chacha_mips,
		.decrypt		= chacha_mips,
	पूर्ण, अणु
		.base.cra_name		= "xchacha20",
		.base.cra_driver_name	= "xchacha20-mips",
		.base.cra_priority	= 200,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= xchacha_mips,
		.decrypt		= xchacha_mips,
	पूर्ण, अणु
		.base.cra_name		= "xchacha12",
		.base.cra_driver_name	= "xchacha12-mips",
		.base.cra_priority	= 200,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encrypt		= xchacha_mips,
		.decrypt		= xchacha_mips,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init chacha_simd_mod_init(व्योम)
अणु
	वापस IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER) ?
		crypto_रेजिस्टर_skciphers(algs, ARRAY_SIZE(algs)) : 0;
पूर्ण

अटल व्योम __निकास chacha_simd_mod_fini(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER))
		crypto_unरेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
पूर्ण

module_init(chacha_simd_mod_init);
module_निकास(chacha_simd_mod_fini);

MODULE_DESCRIPTION("ChaCha and XChaCha stream ciphers (MIPS accelerated)");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("chacha20");
MODULE_ALIAS_CRYPTO("chacha20-mips");
MODULE_ALIAS_CRYPTO("xchacha20");
MODULE_ALIAS_CRYPTO("xchacha20-mips");
MODULE_ALIAS_CRYPTO("xchacha12");
MODULE_ALIAS_CRYPTO("xchacha12-mips");
