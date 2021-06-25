<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ARM NEON accelerated ChaCha and XChaCha stream ciphers,
 * including ChaCha20 (RFC7539)
 *
 * Copyright (C) 2016-2019 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 * Copyright (C) 2015 Martin Willi
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/chacha.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम chacha_block_xor_neon(स्थिर u32 *state, u8 *dst, स्थिर u8 *src,
				      पूर्णांक nrounds);
यंत्रlinkage व्योम chacha_4block_xor_neon(स्थिर u32 *state, u8 *dst, स्थिर u8 *src,
				       पूर्णांक nrounds, अचिन्हित पूर्णांक nbytes);
यंत्रlinkage व्योम hchacha_block_arm(स्थिर u32 *state, u32 *out, पूर्णांक nrounds);
यंत्रlinkage व्योम hchacha_block_neon(स्थिर u32 *state, u32 *out, पूर्णांक nrounds);

यंत्रlinkage व्योम chacha_करोarm(u8 *dst, स्थिर u8 *src, अचिन्हित पूर्णांक bytes,
			     स्थिर u32 *state, पूर्णांक nrounds);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(use_neon);

अटल अंतरभूत bool neon_usable(व्योम)
अणु
	वापस अटल_branch_likely(&use_neon) && crypto_simd_usable();
पूर्ण

अटल व्योम chacha_करोneon(u32 *state, u8 *dst, स्थिर u8 *src,
			  अचिन्हित पूर्णांक bytes, पूर्णांक nrounds)
अणु
	u8 buf[CHACHA_BLOCK_SIZE];

	जबतक (bytes > CHACHA_BLOCK_SIZE) अणु
		अचिन्हित पूर्णांक l = min(bytes, CHACHA_BLOCK_SIZE * 4U);

		chacha_4block_xor_neon(state, dst, src, nrounds, l);
		bytes -= l;
		src += l;
		dst += l;
		state[12] += DIV_ROUND_UP(l, CHACHA_BLOCK_SIZE);
	पूर्ण
	अगर (bytes) अणु
		स्थिर u8 *s = src;
		u8 *d = dst;

		अगर (bytes != CHACHA_BLOCK_SIZE)
			s = d = स_नकल(buf, src, bytes);
		chacha_block_xor_neon(state, d, s, nrounds);
		अगर (d != dst)
			स_नकल(dst, buf, bytes);
		state[12]++;
	पूर्ण
पूर्ण

व्योम hchacha_block_arch(स्थिर u32 *state, u32 *stream, पूर्णांक nrounds)
अणु
	अगर (!IS_ENABLED(CONFIG_KERNEL_MODE_NEON) || !neon_usable()) अणु
		hchacha_block_arm(state, stream, nrounds);
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
	अगर (!IS_ENABLED(CONFIG_KERNEL_MODE_NEON) || !neon_usable() ||
	    bytes <= CHACHA_BLOCK_SIZE) अणु
		chacha_करोarm(dst, src, bytes, state, nrounds);
		state[12] += DIV_ROUND_UP(bytes, CHACHA_BLOCK_SIZE);
		वापस;
	पूर्ण

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

अटल पूर्णांक chacha_stream_xor(काष्ठा skcipher_request *req,
			     स्थिर काष्ठा chacha_ctx *ctx, स्थिर u8 *iv,
			     bool neon)
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

		अगर (!IS_ENABLED(CONFIG_KERNEL_MODE_NEON) || !neon) अणु
			chacha_करोarm(walk.dst.virt.addr, walk.src.virt.addr,
				     nbytes, state, ctx->nrounds);
			state[12] += DIV_ROUND_UP(nbytes, CHACHA_BLOCK_SIZE);
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

अटल पूर्णांक करो_chacha(काष्ठा skcipher_request *req, bool neon)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);

	वापस chacha_stream_xor(req, ctx, req->iv, neon);
पूर्ण

अटल पूर्णांक chacha_arm(काष्ठा skcipher_request *req)
अणु
	वापस करो_chacha(req, false);
पूर्ण

अटल पूर्णांक chacha_neon(काष्ठा skcipher_request *req)
अणु
	वापस करो_chacha(req, neon_usable());
पूर्ण

अटल पूर्णांक करो_xchacha(काष्ठा skcipher_request *req, bool neon)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा chacha_ctx subctx;
	u32 state[16];
	u8 real_iv[16];

	chacha_init_generic(state, ctx->key, req->iv);

	अगर (!IS_ENABLED(CONFIG_KERNEL_MODE_NEON) || !neon) अणु
		hchacha_block_arm(state, subctx.key, ctx->nrounds);
	पूर्ण अन्यथा अणु
		kernel_neon_begin();
		hchacha_block_neon(state, subctx.key, ctx->nrounds);
		kernel_neon_end();
	पूर्ण
	subctx.nrounds = ctx->nrounds;

	स_नकल(&real_iv[0], req->iv + 24, 8);
	स_नकल(&real_iv[8], req->iv + 16, 8);
	वापस chacha_stream_xor(req, &subctx, real_iv, neon);
पूर्ण

अटल पूर्णांक xchacha_arm(काष्ठा skcipher_request *req)
अणु
	वापस करो_xchacha(req, false);
पूर्ण

अटल पूर्णांक xchacha_neon(काष्ठा skcipher_request *req)
अणु
	वापस करो_xchacha(req, neon_usable());
पूर्ण

अटल काष्ठा skcipher_alg arm_algs[] = अणु
	अणु
		.base.cra_name		= "chacha20",
		.base.cra_driver_name	= "chacha20-arm",
		.base.cra_priority	= 200,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= chacha_arm,
		.decrypt		= chacha_arm,
	पूर्ण, अणु
		.base.cra_name		= "xchacha20",
		.base.cra_driver_name	= "xchacha20-arm",
		.base.cra_priority	= 200,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encrypt		= xchacha_arm,
		.decrypt		= xchacha_arm,
	पूर्ण, अणु
		.base.cra_name		= "xchacha12",
		.base.cra_driver_name	= "xchacha12-arm",
		.base.cra_priority	= 200,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा chacha_ctx),
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BLOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encrypt		= xchacha_arm,
		.decrypt		= xchacha_arm,
	पूर्ण,
पूर्ण;

अटल काष्ठा skcipher_alg neon_algs[] = अणु
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
		.walksize		= 4 * CHACHA_BLOCK_SIZE,
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
		.walksize		= 4 * CHACHA_BLOCK_SIZE,
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
		.walksize		= 4 * CHACHA_BLOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encrypt		= xchacha_neon,
		.decrypt		= xchacha_neon,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init chacha_simd_mod_init(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER)) अणु
		err = crypto_रेजिस्टर_skciphers(arm_algs, ARRAY_SIZE(arm_algs));
		अगर (err)
			वापस err;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_KERNEL_MODE_NEON) && (elf_hwcap & HWCAP_NEON)) अणु
		पूर्णांक i;

		चयन (पढ़ो_cpuid_part()) अणु
		हाल ARM_CPU_PART_CORTEX_A7:
		हाल ARM_CPU_PART_CORTEX_A5:
			/*
			 * The Cortex-A7 and Cortex-A5 करो not perक्रमm well with
			 * the NEON implementation but करो incredibly with the
			 * scalar one and use less घातer.
			 */
			क्रम (i = 0; i < ARRAY_SIZE(neon_algs); i++)
				neon_algs[i].base.cra_priority = 0;
			अवरोध;
		शेष:
			अटल_branch_enable(&use_neon);
		पूर्ण

		अगर (IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER)) अणु
			err = crypto_रेजिस्टर_skciphers(neon_algs, ARRAY_SIZE(neon_algs));
			अगर (err)
				crypto_unरेजिस्टर_skciphers(arm_algs, ARRAY_SIZE(arm_algs));
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम __निकास chacha_simd_mod_fini(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_SKCIPHER)) अणु
		crypto_unरेजिस्टर_skciphers(arm_algs, ARRAY_SIZE(arm_algs));
		अगर (IS_ENABLED(CONFIG_KERNEL_MODE_NEON) && (elf_hwcap & HWCAP_NEON))
			crypto_unरेजिस्टर_skciphers(neon_algs, ARRAY_SIZE(neon_algs));
	पूर्ण
पूर्ण

module_init(chacha_simd_mod_init);
module_निकास(chacha_simd_mod_fini);

MODULE_DESCRIPTION("ChaCha and XChaCha stream ciphers (scalar and NEON accelerated)");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("chacha20");
MODULE_ALIAS_CRYPTO("chacha20-arm");
MODULE_ALIAS_CRYPTO("xchacha20");
MODULE_ALIAS_CRYPTO("xchacha20-arm");
MODULE_ALIAS_CRYPTO("xchacha12");
MODULE_ALIAS_CRYPTO("xchacha12-arm");
#अगर_घोषित CONFIG_KERNEL_MODE_NEON
MODULE_ALIAS_CRYPTO("chacha20-neon");
MODULE_ALIAS_CRYPTO("xchacha20-neon");
MODULE_ALIAS_CRYPTO("xchacha12-neon");
#पूर्ण_अगर
