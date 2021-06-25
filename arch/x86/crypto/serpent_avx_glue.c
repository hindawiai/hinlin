<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue Code क्रम AVX assembler versions of Serpent Cipher
 *
 * Copyright (C) 2012 Johannes Goetzfried
 *     <Johannes.Goetzfried@inक्रमmatik.stud.uni-erlangen.de>
 *
 * Copyright तऊ 2011-2013 Jussi Kivilinna <jussi.kivilinna@iki.fi>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/serpent.h>

#समावेश "serpent-avx.h"
#समावेश "ecb_cbc_helpers.h"

/* 8-way parallel cipher functions */
यंत्रlinkage व्योम serpent_ecb_enc_8way_avx(स्थिर व्योम *ctx, u8 *dst,
					 स्थिर u8 *src);
EXPORT_SYMBOL_GPL(serpent_ecb_enc_8way_avx);

यंत्रlinkage व्योम serpent_ecb_dec_8way_avx(स्थिर व्योम *ctx, u8 *dst,
					 स्थिर u8 *src);
EXPORT_SYMBOL_GPL(serpent_ecb_dec_8way_avx);

यंत्रlinkage व्योम serpent_cbc_dec_8way_avx(स्थिर व्योम *ctx, u8 *dst,
					 स्थिर u8 *src);
EXPORT_SYMBOL_GPL(serpent_cbc_dec_8way_avx);

अटल पूर्णांक serpent_setkey_skcipher(काष्ठा crypto_skcipher *tfm,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस __serpent_setkey(crypto_skcipher_ctx(tfm), key, keylen);
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, SERPENT_BLOCK_SIZE, SERPENT_PARALLEL_BLOCKS);
	ECB_BLOCK(SERPENT_PARALLEL_BLOCKS, serpent_ecb_enc_8way_avx);
	ECB_BLOCK(1, __serpent_encrypt);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, SERPENT_BLOCK_SIZE, SERPENT_PARALLEL_BLOCKS);
	ECB_BLOCK(SERPENT_PARALLEL_BLOCKS, serpent_ecb_dec_8way_avx);
	ECB_BLOCK(1, __serpent_decrypt);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, SERPENT_BLOCK_SIZE, -1);
	CBC_ENC_BLOCK(__serpent_encrypt);
	CBC_WALK_END();
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, SERPENT_BLOCK_SIZE, SERPENT_PARALLEL_BLOCKS);
	CBC_DEC_BLOCK(SERPENT_PARALLEL_BLOCKS, serpent_cbc_dec_8way_avx);
	CBC_DEC_BLOCK(1, __serpent_decrypt);
	CBC_WALK_END();
पूर्ण

अटल काष्ठा skcipher_alg serpent_algs[] = अणु
	अणु
		.base.cra_name		= "__ecb(serpent)",
		.base.cra_driver_name	= "__ecb-serpent-avx",
		.base.cra_priority	= 500,
		.base.cra_flags		= CRYPTO_ALG_INTERNAL,
		.base.cra_blocksize	= SERPENT_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा serpent_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= SERPENT_MIN_KEY_SIZE,
		.max_keysize		= SERPENT_MAX_KEY_SIZE,
		.setkey			= serpent_setkey_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "__cbc(serpent)",
		.base.cra_driver_name	= "__cbc-serpent-avx",
		.base.cra_priority	= 500,
		.base.cra_flags		= CRYPTO_ALG_INTERNAL,
		.base.cra_blocksize	= SERPENT_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा serpent_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= SERPENT_MIN_KEY_SIZE,
		.max_keysize		= SERPENT_MAX_KEY_SIZE,
		.ivsize			= SERPENT_BLOCK_SIZE,
		.setkey			= serpent_setkey_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण,
पूर्ण;

अटल काष्ठा simd_skcipher_alg *serpent_simd_algs[ARRAY_SIZE(serpent_algs)];

अटल पूर्णांक __init serpent_init(व्योम)
अणु
	स्थिर अक्षर *feature_name;

	अगर (!cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM,
				&feature_name)) अणु
		pr_info("CPU feature '%s' is not supported.\n", feature_name);
		वापस -ENODEV;
	पूर्ण

	वापस simd_रेजिस्टर_skciphers_compat(serpent_algs,
					      ARRAY_SIZE(serpent_algs),
					      serpent_simd_algs);
पूर्ण

अटल व्योम __निकास serpent_निकास(व्योम)
अणु
	simd_unरेजिस्टर_skciphers(serpent_algs, ARRAY_SIZE(serpent_algs),
				  serpent_simd_algs);
पूर्ण

module_init(serpent_init);
module_निकास(serpent_निकास);

MODULE_DESCRIPTION("Serpent Cipher Algorithm, AVX optimized");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("serpent");
