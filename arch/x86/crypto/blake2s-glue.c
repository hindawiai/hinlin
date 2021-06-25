<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश <crypto/पूर्णांकernal/blake2s.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश <linux/types.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम blake2s_compress_ssse3(काष्ठा blake2s_state *state,
				       स्थिर u8 *block, स्थिर माप_प्रकार nblocks,
				       स्थिर u32 inc);
यंत्रlinkage व्योम blake2s_compress_avx512(काष्ठा blake2s_state *state,
					स्थिर u8 *block, स्थिर माप_प्रकार nblocks,
					स्थिर u32 inc);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(blake2s_use_ssse3);
अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(blake2s_use_avx512);

व्योम blake2s_compress_arch(काष्ठा blake2s_state *state,
			   स्थिर u8 *block, माप_प्रकार nblocks,
			   स्थिर u32 inc)
अणु
	/* SIMD disables preemption, so relax after processing each page. */
	BUILD_BUG_ON(SZ_4K / BLAKE2S_BLOCK_SIZE < 8);

	अगर (!अटल_branch_likely(&blake2s_use_ssse3) || !crypto_simd_usable()) अणु
		blake2s_compress_generic(state, block, nblocks, inc);
		वापस;
	पूर्ण

	करो अणु
		स्थिर माप_प्रकार blocks = min_t(माप_प्रकार, nblocks,
					    SZ_4K / BLAKE2S_BLOCK_SIZE);

		kernel_fpu_begin();
		अगर (IS_ENABLED(CONFIG_AS_AVX512) &&
		    अटल_branch_likely(&blake2s_use_avx512))
			blake2s_compress_avx512(state, block, blocks, inc);
		अन्यथा
			blake2s_compress_ssse3(state, block, blocks, inc);
		kernel_fpu_end();

		nblocks -= blocks;
		block += blocks * BLAKE2S_BLOCK_SIZE;
	पूर्ण जबतक (nblocks);
पूर्ण
EXPORT_SYMBOL(blake2s_compress_arch);

अटल पूर्णांक crypto_blake2s_update_x86(काष्ठा shash_desc *desc,
				     स्थिर u8 *in, अचिन्हित पूर्णांक inlen)
अणु
	वापस crypto_blake2s_update(desc, in, inlen, blake2s_compress_arch);
पूर्ण

अटल पूर्णांक crypto_blake2s_final_x86(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस crypto_blake2s_final(desc, out, blake2s_compress_arch);
पूर्ण

#घोषणा BLAKE2S_ALG(name, driver_name, digest_size)			\
	अणु								\
		.base.cra_name		= name,				\
		.base.cra_driver_name	= driver_name,			\
		.base.cra_priority	= 200,				\
		.base.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,	\
		.base.cra_blocksize	= BLAKE2S_BLOCK_SIZE,		\
		.base.cra_ctxsize	= माप(काष्ठा blake2s_tfm_ctx), \
		.base.cra_module	= THIS_MODULE,			\
		.digestsize		= digest_size,			\
		.setkey			= crypto_blake2s_setkey,	\
		.init			= crypto_blake2s_init,		\
		.update			= crypto_blake2s_update_x86,	\
		.final			= crypto_blake2s_final_x86,	\
		.descsize		= माप(काष्ठा blake2s_state),	\
	पूर्ण

अटल काष्ठा shash_alg blake2s_algs[] = अणु
	BLAKE2S_ALG("blake2s-128", "blake2s-128-x86", BLAKE2S_128_HASH_SIZE),
	BLAKE2S_ALG("blake2s-160", "blake2s-160-x86", BLAKE2S_160_HASH_SIZE),
	BLAKE2S_ALG("blake2s-224", "blake2s-224-x86", BLAKE2S_224_HASH_SIZE),
	BLAKE2S_ALG("blake2s-256", "blake2s-256-x86", BLAKE2S_256_HASH_SIZE),
पूर्ण;

अटल पूर्णांक __init blake2s_mod_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_SSSE3))
		वापस 0;

	अटल_branch_enable(&blake2s_use_ssse3);

	अगर (IS_ENABLED(CONFIG_AS_AVX512) &&
	    boot_cpu_has(X86_FEATURE_AVX) &&
	    boot_cpu_has(X86_FEATURE_AVX2) &&
	    boot_cpu_has(X86_FEATURE_AVX512F) &&
	    boot_cpu_has(X86_FEATURE_AVX512VL) &&
	    cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM |
			      XFEATURE_MASK_AVX512, शून्य))
		अटल_branch_enable(&blake2s_use_avx512);

	वापस IS_REACHABLE(CONFIG_CRYPTO_HASH) ?
		crypto_रेजिस्टर_shashes(blake2s_algs,
					ARRAY_SIZE(blake2s_algs)) : 0;
पूर्ण

अटल व्योम __निकास blake2s_mod_निकास(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_HASH) && boot_cpu_has(X86_FEATURE_SSSE3))
		crypto_unरेजिस्टर_shashes(blake2s_algs, ARRAY_SIZE(blake2s_algs));
पूर्ण

module_init(blake2s_mod_init);
module_निकास(blake2s_mod_निकास);

MODULE_ALIAS_CRYPTO("blake2s-128");
MODULE_ALIAS_CRYPTO("blake2s-128-x86");
MODULE_ALIAS_CRYPTO("blake2s-160");
MODULE_ALIAS_CRYPTO("blake2s-160-x86");
MODULE_ALIAS_CRYPTO("blake2s-224");
MODULE_ALIAS_CRYPTO("blake2s-224-x86");
MODULE_ALIAS_CRYPTO("blake2s-256");
MODULE_ALIAS_CRYPTO("blake2s-256-x86");
MODULE_LICENSE("GPL v2");
