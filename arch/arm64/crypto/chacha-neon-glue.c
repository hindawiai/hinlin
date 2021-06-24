<शैली गुरु>
/*
 * ARM NEON and scalar accelerated ChaCha and XChaCha stream ciphers,
 * including ChaCha20 (RFC7539)
 *
 * Copyright (C) 2016 - 2017 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Based on:
 * ChaCha20 256-bit cipher algorithm, RFC7539, SIMD glue code
 *
 * Copyright (C) 2015 Martin Willi
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/chacha.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम chacha_block_xor_neon(u32 *state, u8 *dst, स्थिर u8 *src,
				      पूर्णांक nrounds);
यंत्रlinkage व्योम chacha_4block_xor_neon(u32 *state, u8 *dst, स्थिर u8 *src,
				       पूर्णांक nrounds, पूर्णांक bytes);
यंत्रlinkage व्योम hchacha_block_neon(स्थिर u32 *state, u32 *out, पूर्णांक nrounds);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(have_neon);

अटल व्योम chacha_करोneon(u32 *state, u8 *dst, स्थिर u8 *src,
			  पूर्णांक bytes, पूर्णांक nrounds)
अणु
	जबतक (bytes > 0) अणु
		पूर्णांक l = min(bytes, CHACHA_BLOCK_SIZE * 5);

		अगर (l <= CHACHA_BLOCK_SIZE) अणु
			u8 buf[CHACHA_BLOCK_SIZE];

			स_नकल(buf, src, l);
			chacha_block_xor_neon(state, buf, buf, nrounds);
			स_नकल(dst, buf, l);
			state[12] += 1;
			अवरोध;
		पूर्ण
		chacha_4block_xor_neon(state, dst, src, nrounds, l);
		bytes -= l;
		src += l;
		dst += l;
		state[12] += DIV_ROUND_UP(l, CHACHA_BLOCK_SIZE);
	पूर्ण
पूर्ण

व्योम hchacha_block_arch(स्थिर u32 *state, u32 *stream, पूर्णांक nrounds)
अणु
	अगर (!अटल_branch_likely(&have_neon) || !crypto_simd_usable()) अणु
		hchacha_block_generic(state, stream, nrounds);
	पूर्ण अन्यथा अणु
		kernel_neon_begin();
		hchacha_block_neon(state, stream, nrounds);
		kernel_neon_end();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(hchacha_block_arch);

व्योम chacha_init_arch(u32 *state, स्थिर u32 *key, स्थिर u8 *iv)
अणु
	chacha_init_generic(state, key, iv);
पूर्ण
EXPORT_SYMBOL(chacha_init_arch);

व्योम chacha_crypt_arch(u32 *state, u8 *dst, स्थिर u8 *src, अचिन्हित पूर्णांक bytes,
		       पूर्णांक nrounds)
अणु
	अगर (!अटल_branch_likely(&have_neon) || bytes <= CHACHA_BLOCK_SIZE ||
	    !crypto_simd_usable())
		वापस chacha_crypt_generic(state, dst, src, bytes, nrounds);

	करो अणु
		अचिन्हित पूर्णांक toकरो = min_t(अचिन्हित पूर्णांक, bytes, SZ_4K);

		kernel_neon_begin();
		chacha_करोneon(state, dst, src, toकरो, nrounds);
		kernel_neon_end();

		bytes -= toकरो;
		src += toकरो;
		dst += toकरो;
	पूर्ण जबतक (bytes);
पूर्ण
EXPORT_SYMBOL(chacha_crypt_arch);

अटल पूर्णांक chacha_neon_stream_xor(काष्ठा skcipher_request *req,
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
			nbytes = roundकरोwn(nbytes, walk.stride);

		अगर (!अटल_branch_likely(&have_neon) ||
		    !crypto_simd_usable()) अणु
			chacha_crypt_generic(state, walk.dst.virt.addr,
					     walk.src.virt.addr, nbytes,
					     ctx->nrounds);
		पूर्ण अन्यथा अणु
			kernel_neon_begin();
			chacha_करोneon(state, walk.dst.virt.addr,
				      walk.src.virt.addr, nbytes, ctx->nrounds);
			kernel_neon_end();
		पूर्ण
		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक chacha_neon(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस chacha_neon_stream_xor(req, ctx, req->iv);
पूर्ण

अटल पूर्णांक xchacha_neon(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा chacha_ctx subctx;
	u32 state[16];
	u8 real_iv[16];

	chacha_init_generic(state, ctx->key, req->iv);
	hchacha_block_arch(state, subctx.key, ctx->nrounds);
	subctx.nrounds = ctx->nrounds;

	स_नकल(&real_iv[0], req->iv + 24, 8);
	स_नकल(&real_iv[8], req->iv + 16, 8);
	वापस chacha_neon_stream_xor(req, &subctx, real_iv);
पूर्ण

अटल काष्ठा skcipher_alg algs[] = अणु
	अणु
		.base.cra_name		= "chacha20",
		.base.cra_driver_name	= "chacha20-neon",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.walksize		= 5 * CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= chacha_neon,
		.decrypt		= chacha_neon,
	पूर्ण, अणु
		.base.cra_name		= "xchacha20",
		.base.cra_driver_name	= "xchacha20-neon",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.walksize		= 5 * CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= xchacha_neon,
		.decrypt		= xchacha_neon,
	पूर्ण, अणु
		.base.cra_name		= "xchacha12",
		.base.cra_driver_name	= "xchacha12-neon",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.walksize		= 5 * CHACHA_BLOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encrypt		= xchacha_neon,
		.decrypt		= xchacha_neon,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init chacha_simd_mod_init(व्योम)
अणु
	अगर (!cpu_have_named_feature(ASIMD))
		वापस 0;

	अटल_branch_enable(&have_neon);

	वापस IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER) ?
		crypto_रेजिस्टर_skciphers(algs, ARRAY_SIZE(algs)) : 0;
पूर्ण

अटल व्योम __निकास chacha_simd_mod_fini(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER) && cpu_have_named_feature(ASIMD))
		crypto_unरेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
पूर्ण

module_init(chacha_simd_mod_init);
module_निकास(chacha_simd_mod_fini);

MODULE_DESCRIPTION("ChaCha and XChaCha stream ciphers (NEON accelerated)");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("chacha20");
MODULE_ALIAS_CRYPTO("chacha20-neon");
MODULE_ALIAS_CRYPTO("xchacha20");
MODULE_ALIAS_CRYPTO("xchacha20-neon");
MODULE_ALIAS_CRYPTO("xchacha12");
MODULE_ALIAS_CRYPTO("xchacha12-neon");
