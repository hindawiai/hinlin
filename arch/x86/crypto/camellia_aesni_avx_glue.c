<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue Code क्रम x86_64/AVX/AES-NI assembler optimized version of Camellia
 *
 * Copyright तऊ 2012-2013 Jussi Kivilinna <jussi.kivilinna@iki.fi>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश "camellia.h"
#समावेश "ecb_cbc_helpers.h"

#घोषणा CAMELLIA_AESNI_PARALLEL_BLOCKS 16

/* 16-way parallel cipher functions (avx/aes-ni) */
यंत्रlinkage व्योम camellia_ecb_enc_16way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);
EXPORT_SYMBOL_GPL(camellia_ecb_enc_16way);

यंत्रlinkage व्योम camellia_ecb_dec_16way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);
EXPORT_SYMBOL_GPL(camellia_ecb_dec_16way);

यंत्रlinkage व्योम camellia_cbc_dec_16way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);
EXPORT_SYMBOL_GPL(camellia_cbc_dec_16way);

अटल पूर्णांक camellia_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	वापस __camellia_setkey(crypto_skcipher_ctx(tfm), key, keylen);
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, CAMELLIA_BLOCK_SIZE, CAMELLIA_AESNI_PARALLEL_BLOCKS);
	ECB_BLOCK(CAMELLIA_AESNI_PARALLEL_BLOCKS, camellia_ecb_enc_16way);
	ECB_BLOCK(2, camellia_enc_blk_2way);
	ECB_BLOCK(1, camellia_enc_blk);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, CAMELLIA_BLOCK_SIZE, CAMELLIA_AESNI_PARALLEL_BLOCKS);
	ECB_BLOCK(CAMELLIA_AESNI_PARALLEL_BLOCKS, camellia_ecb_dec_16way);
	ECB_BLOCK(2, camellia_dec_blk_2way);
	ECB_BLOCK(1, camellia_dec_blk);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, CAMELLIA_BLOCK_SIZE, -1);
	CBC_ENC_BLOCK(camellia_enc_blk);
	CBC_WALK_END();
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, CAMELLIA_BLOCK_SIZE, CAMELLIA_AESNI_PARALLEL_BLOCKS);
	CBC_DEC_BLOCK(CAMELLIA_AESNI_PARALLEL_BLOCKS, camellia_cbc_dec_16way);
	CBC_DEC_BLOCK(2, camellia_decrypt_cbc_2way);
	CBC_DEC_BLOCK(1, camellia_dec_blk);
	CBC_WALK_END();
पूर्ण

अटल काष्ठा skcipher_alg camellia_algs[] = अणु
	अणु
		.base.cra_name		= "__ecb(camellia)",
		.base.cra_driver_name	= "__ecb-camellia-aesni",
		.base.cra_priority	= 400,
		.base.cra_flags		= CRYPTO_ALG_INTERNAL,
		.base.cra_blocksize	= CAMELLIA_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा camellia_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= CAMELLIA_MIN_KEY_SIZE,
		.max_keysize		= CAMELLIA_MAX_KEY_SIZE,
		.setkey			= camellia_setkey,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "__cbc(camellia)",
		.base.cra_driver_name	= "__cbc-camellia-aesni",
		.base.cra_priority	= 400,
		.base.cra_flags		= CRYPTO_ALG_INTERNAL,
		.base.cra_blocksize	= CAMELLIA_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा camellia_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= CAMELLIA_MIN_KEY_SIZE,
		.max_keysize		= CAMELLIA_MAX_KEY_SIZE,
		.ivsize			= CAMELLIA_BLOCK_SIZE,
		.setkey			= camellia_setkey,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण
पूर्ण;

अटल काष्ठा simd_skcipher_alg *camellia_simd_algs[ARRAY_SIZE(camellia_algs)];

अटल पूर्णांक __init camellia_aesni_init(व्योम)
अणु
	स्थिर अक्षर *feature_name;

	अगर (!boot_cpu_has(X86_FEATURE_AVX) ||
	    !boot_cpu_has(X86_FEATURE_AES) ||
	    !boot_cpu_has(X86_FEATURE_OSXSAVE)) अणु
		pr_info("AVX or AES-NI instructions are not detected.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM,
				&feature_name)) अणु
		pr_info("CPU feature '%s' is not supported.\n", feature_name);
		वापस -ENODEV;
	पूर्ण

	वापस simd_रेजिस्टर_skciphers_compat(camellia_algs,
					      ARRAY_SIZE(camellia_algs),
					      camellia_simd_algs);
पूर्ण

अटल व्योम __निकास camellia_aesni_fini(व्योम)
अणु
	simd_unरेजिस्टर_skciphers(camellia_algs, ARRAY_SIZE(camellia_algs),
				  camellia_simd_algs);
पूर्ण

module_init(camellia_aesni_init);
module_निकास(camellia_aesni_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Camellia Cipher Algorithm, AES-NI/AVX optimized");
MODULE_ALIAS_CRYPTO("camellia");
MODULE_ALIAS_CRYPTO("camellia-asm");
