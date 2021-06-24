<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * x64 SIMD accelerated ChaCha and XChaCha stream ciphers,
 * including ChaCha20 (RFC7539)
 *
 * Copyright (C) 2015 Martin Willi
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/chacha.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम chacha_block_xor_ssse3(u32 *state, u8 *dst, स्थिर u8 *src,
				       अचिन्हित पूर्णांक len, पूर्णांक nrounds);
यंत्रlinkage व्योम chacha_4block_xor_ssse3(u32 *state, u8 *dst, स्थिर u8 *src,
					अचिन्हित पूर्णांक len, पूर्णांक nrounds);
यंत्रlinkage व्योम hchacha_block_ssse3(स्थिर u32 *state, u32 *out, पूर्णांक nrounds);

यंत्रlinkage व्योम chacha_2block_xor_avx2(u32 *state, u8 *dst, स्थिर u8 *src,
				       अचिन्हित पूर्णांक len, पूर्णांक nrounds);
यंत्रlinkage व्योम chacha_4block_xor_avx2(u32 *state, u8 *dst, स्थिर u8 *src,
				       अचिन्हित पूर्णांक len, पूर्णांक nrounds);
यंत्रlinkage व्योम chacha_8block_xor_avx2(u32 *state, u8 *dst, स्थिर u8 *src,
				       अचिन्हित पूर्णांक len, पूर्णांक nrounds);

यंत्रlinkage व्योम chacha_2block_xor_avx512vl(u32 *state, u8 *dst, स्थिर u8 *src,
					   अचिन्हित पूर्णांक len, पूर्णांक nrounds);
यंत्रlinkage व्योम chacha_4block_xor_avx512vl(u32 *state, u8 *dst, स्थिर u8 *src,
					   अचिन्हित पूर्णांक len, पूर्णांक nrounds);
यंत्रlinkage व्योम chacha_8block_xor_avx512vl(u32 *state, u8 *dst, स्थिर u8 *src,
					   अचिन्हित पूर्णांक len, पूर्णांक nrounds);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(chacha_use_simd);
अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(chacha_use_avx2);
अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(chacha_use_avx512vl);

अटल अचिन्हित पूर्णांक chacha_advance(अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक maxblocks)
अणु
	len = min(len, maxblocks * CHACHA_BLOCK_SIZE);
	वापस round_up(len, CHACHA_BLOCK_SIZE) / CHACHA_BLOCK_SIZE;
पूर्ण

अटल व्योम chacha_करोsimd(u32 *state, u8 *dst, स्थिर u8 *src,
			  अचिन्हित पूर्णांक bytes, पूर्णांक nrounds)
अणु
	अगर (IS_ENABLED(CONFIG_AS_AVX512) &&
	    अटल_branch_likely(&chacha_use_avx512vl)) अणु
		जबतक (bytes >= CHACHA_BLOCK_SIZE * 8) अणु
			chacha_8block_xor_avx512vl(state, dst, src, bytes,
						   nrounds);
			bytes -= CHACHA_BLOCK_SIZE * 8;
			src += CHACHA_BLOCK_SIZE * 8;
			dst += CHACHA_BLOCK_SIZE * 8;
			state[12] += 8;
		पूर्ण
		अगर (bytes > CHACHA_BLOCK_SIZE * 4) अणु
			chacha_8block_xor_avx512vl(state, dst, src, bytes,
						   nrounds);
			state[12] += chacha_advance(bytes, 8);
			वापस;
		पूर्ण
		अगर (bytes > CHACHA_BLOCK_SIZE * 2) अणु
			chacha_4block_xor_avx512vl(state, dst, src, bytes,
						   nrounds);
			state[12] += chacha_advance(bytes, 4);
			वापस;
		पूर्ण
		अगर (bytes) अणु
			chacha_2block_xor_avx512vl(state, dst, src, bytes,
						   nrounds);
			state[12] += chacha_advance(bytes, 2);
			वापस;
		पूर्ण
	पूर्ण

	अगर (अटल_branch_likely(&chacha_use_avx2)) अणु
		जबतक (bytes >= CHACHA_BLOCK_SIZE * 8) अणु
			chacha_8block_xor_avx2(state, dst, src, bytes, nrounds);
			bytes -= CHACHA_BLOCK_SIZE * 8;
			src += CHACHA_BLOCK_SIZE * 8;
			dst += CHACHA_BLOCK_SIZE * 8;
			state[12] += 8;
		पूर्ण
		अगर (bytes > CHACHA_BLOCK_SIZE * 4) अणु
			chacha_8block_xor_avx2(state, dst, src, bytes, nrounds);
			state[12] += chacha_advance(bytes, 8);
			वापस;
		पूर्ण
		अगर (bytes > CHACHA_BLOCK_SIZE * 2) अणु
			chacha_4block_xor_avx2(state, dst, src, bytes, nrounds);
			state[12] += chacha_advance(bytes, 4);
			वापस;
		पूर्ण
		अगर (bytes > CHACHA_BLOCK_SIZE) अणु
			chacha_2block_xor_avx2(state, dst, src, bytes, nrounds);
			state[12] += chacha_advance(bytes, 2);
			वापस;
		पूर्ण
	पूर्ण

	जबतक (bytes >= CHACHA_BLOCK_SIZE * 4) अणु
		chacha_4block_xor_ssse3(state, dst, src, bytes, nrounds);
		bytes -= CHACHA_BLOCK_SIZE * 4;
		src += CHACHA_BLOCK_SIZE * 4;
		dst += CHACHA_BLOCK_SIZE * 4;
		state[12] += 4;
	पूर्ण
	अगर (bytes > CHACHA_BLOCK_SIZE) अणु
		chacha_4block_xor_ssse3(state, dst, src, bytes, nrounds);
		state[12] += chacha_advance(bytes, 4);
		वापस;
	पूर्ण
	अगर (bytes) अणु
		chacha_block_xor_ssse3(state, dst, src, bytes, nrounds);
		state[12]++;
	पूर्ण
पूर्ण

व्योम hchacha_block_arch(स्थिर u32 *state, u32 *stream, पूर्णांक nrounds)
अणु
	अगर (!अटल_branch_likely(&chacha_use_simd) || !crypto_simd_usable()) अणु
		hchacha_block_generic(state, stream, nrounds);
	पूर्ण अन्यथा अणु
		kernel_fpu_begin();
		hchacha_block_ssse3(state, stream, nrounds);
		kernel_fpu_end();
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
	अगर (!अटल_branch_likely(&chacha_use_simd) || !crypto_simd_usable() ||
	    bytes <= CHACHA_BLOCK_SIZE)
		वापस chacha_crypt_generic(state, dst, src, bytes, nrounds);

	करो अणु
		अचिन्हित पूर्णांक toकरो = min_t(अचिन्हित पूर्णांक, bytes, SZ_4K);

		kernel_fpu_begin();
		chacha_करोsimd(state, dst, src, toकरो, nrounds);
		kernel_fpu_end();

		bytes -= toकरो;
		src += toकरो;
		dst += toकरो;
	पूर्ण जबतक (bytes);
पूर्ण
EXPORT_SYMBOL(chacha_crypt_arch);

अटल पूर्णांक chacha_simd_stream_xor(काष्ठा skcipher_request *req,
				  स्थिर काष्ठा chacha_ctx *ctx, स्थिर u8 *iv)
अणु
	u32 state[CHACHA_STATE_WORDS] __aligned(8);
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	chacha_init_generic(state, ctx->key, iv);

	जबतक (walk.nbytes > 0) अणु
		अचिन्हित पूर्णांक nbytes = walk.nbytes;

		अगर (nbytes < walk.total)
			nbytes = round_करोwn(nbytes, walk.stride);

		अगर (!अटल_branch_likely(&chacha_use_simd) ||
		    !crypto_simd_usable()) अणु
			chacha_crypt_generic(state, walk.dst.virt.addr,
					     walk.src.virt.addr, nbytes,
					     ctx->nrounds);
		पूर्ण अन्यथा अणु
			kernel_fpu_begin();
			chacha_करोsimd(state, walk.dst.virt.addr,
				      walk.src.virt.addr, nbytes,
				      ctx->nrounds);
			kernel_fpu_end();
		पूर्ण
		err = skcipher_walk_करोne(&walk, walk.nbytes - nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक chacha_simd(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस chacha_simd_stream_xor(req, ctx, req->iv);
पूर्ण

अटल पूर्णांक xchacha_simd(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);
	u32 state[CHACHA_STATE_WORDS] __aligned(8);
	काष्ठा chacha_ctx subctx;
	u8 real_iv[16];

	chacha_init_generic(state, ctx->key, req->iv);

	अगर (req->cryptlen > CHACHA_BLOCK_SIZE && crypto_simd_usable()) अणु
		kernel_fpu_begin();
		hchacha_block_ssse3(state, subctx.key, ctx->nrounds);
		kernel_fpu_end();
	पूर्ण अन्यथा अणु
		hchacha_block_generic(state, subctx.key, ctx->nrounds);
	पूर्ण
	subctx.nrounds = ctx->nrounds;

	स_नकल(&real_iv[0], req->iv + 24, 8);
	स_नकल(&real_iv[8], req->iv + 16, 8);
	वापस chacha_simd_stream_xor(req, &subctx, real_iv);
पूर्ण

अटल काष्ठा skcipher_alg algs[] = अणु
	अणु
		.base.cra_name		= "chacha20",
		.base.cra_driver_name	= "chacha20-simd",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= chacha_simd,
		.decrypt		= chacha_simd,
	पूर्ण, अणु
		.base.cra_name		= "xchacha20",
		.base.cra_driver_name	= "xchacha20-simd",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= xchacha_simd,
		.decrypt		= xchacha_simd,
	पूर्ण, अणु
		.base.cra_name		= "xchacha12",
		.base.cra_driver_name	= "xchacha12-simd",
		.base.cra_priority	= 300,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encrypt		= xchacha_simd,
		.decrypt		= xchacha_simd,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init chacha_simd_mod_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_SSSE3))
		वापस 0;

	अटल_branch_enable(&chacha_use_simd);

	अगर (boot_cpu_has(X86_FEATURE_AVX) &&
	    boot_cpu_has(X86_FEATURE_AVX2) &&
	    cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, शून्य)) अणु
		अटल_branch_enable(&chacha_use_avx2);

		अगर (IS_ENABLED(CONFIG_AS_AVX512) &&
		    boot_cpu_has(X86_FEATURE_AVX512VL) &&
		    boot_cpu_has(X86_FEATURE_AVX512BW)) /* kmovq */
			अटल_branch_enable(&chacha_use_avx512vl);
	पूर्ण
	वापस IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER) ?
		crypto_रेजिस्टर_skciphers(algs, ARRAY_SIZE(algs)) : 0;
पूर्ण

अटल व्योम __निकास chacha_simd_mod_fini(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER) && boot_cpu_has(X86_FEATURE_SSSE3))
		crypto_unरेजिस्टर_skciphers(algs, ARRAY_SIZE(algs));
पूर्ण

module_init(chacha_simd_mod_init);
module_निकास(chacha_simd_mod_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Willi <martin@strongswan.org>");
MODULE_DESCRIPTION("ChaCha and XChaCha stream ciphers (x64 SIMD accelerated)");
MODULE_ALIAS_CRYPTO("chacha20");
MODULE_ALIAS_CRYPTO("chacha20-simd");
MODULE_ALIAS_CRYPTO("xchacha20");
MODULE_ALIAS_CRYPTO("xchacha20-simd");
MODULE_ALIAS_CRYPTO("xchacha12");
MODULE_ALIAS_CRYPTO("xchacha12-simd");
