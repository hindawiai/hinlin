<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue Code क्रम the AVX assembler implementation of the Cast5 Cipher
 *
 * Copyright (C) 2012 Johannes Goetzfried
 *     <Johannes.Goetzfried@inक्रमmatik.stud.uni-erlangen.de>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/cast5.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश "ecb_cbc_helpers.h"

#घोषणा CAST5_PARALLEL_BLOCKS 16

यंत्रlinkage व्योम cast5_ecb_enc_16way(काष्ठा cast5_ctx *ctx, u8 *dst,
				    स्थिर u8 *src);
यंत्रlinkage व्योम cast5_ecb_dec_16way(काष्ठा cast5_ctx *ctx, u8 *dst,
				    स्थिर u8 *src);
यंत्रlinkage व्योम cast5_cbc_dec_16way(काष्ठा cast5_ctx *ctx, u8 *dst,
				    स्थिर u8 *src);

अटल पूर्णांक cast5_setkey_skcipher(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	वापस cast5_setkey(&tfm->base, key, keylen);
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, CAST5_BLOCK_SIZE, CAST5_PARALLEL_BLOCKS);
	ECB_BLOCK(CAST5_PARALLEL_BLOCKS, cast5_ecb_enc_16way);
	ECB_BLOCK(1, __cast5_encrypt);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, CAST5_BLOCK_SIZE, CAST5_PARALLEL_BLOCKS);
	ECB_BLOCK(CAST5_PARALLEL_BLOCKS, cast5_ecb_dec_16way);
	ECB_BLOCK(1, __cast5_decrypt);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, CAST5_BLOCK_SIZE, -1);
	CBC_ENC_BLOCK(__cast5_encrypt);
	CBC_WALK_END();
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, CAST5_BLOCK_SIZE, CAST5_PARALLEL_BLOCKS);
	CBC_DEC_BLOCK(CAST5_PARALLEL_BLOCKS, cast5_cbc_dec_16way);
	CBC_DEC_BLOCK(1, __cast5_decrypt);
	CBC_WALK_END();
पूर्ण

अटल काष्ठा skcipher_alg cast5_algs[] = अणु
	अणु
		.base.cra_name		= "__ecb(cast5)",
		.base.cra_driver_name	= "__ecb-cast5-avx",
		.base.cra_priority	= 200,
		.base.cra_flags		= CRYPTO_ALG_INTERNAL,
		.base.cra_blocksize	= CAST5_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा cast5_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= CAST5_MIN_KEY_SIZE,
		.max_keysize		= CAST5_MAX_KEY_SIZE,
		.setkey			= cast5_setkey_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "__cbc(cast5)",
		.base.cra_driver_name	= "__cbc-cast5-avx",
		.base.cra_priority	= 200,
		.base.cra_flags		= CRYPTO_ALG_INTERNAL,
		.base.cra_blocksize	= CAST5_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा cast5_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= CAST5_MIN_KEY_SIZE,
		.max_keysize		= CAST5_MAX_KEY_SIZE,
		.ivsize			= CAST5_BLOCK_SIZE,
		.setkey			= cast5_setkey_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण
पूर्ण;

अटल काष्ठा simd_skcipher_alg *cast5_simd_algs[ARRAY_SIZE(cast5_algs)];

अटल पूर्णांक __init cast5_init(व्योम)
अणु
	स्थिर अक्षर *feature_name;

	अगर (!cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM,
				&feature_name)) अणु
		pr_info("CPU feature '%s' is not supported.\n", feature_name);
		वापस -ENODEV;
	पूर्ण

	वापस simd_रेजिस्टर_skciphers_compat(cast5_algs,
					      ARRAY_SIZE(cast5_algs),
					      cast5_simd_algs);
पूर्ण

अटल व्योम __निकास cast5_निकास(व्योम)
अणु
	simd_unरेजिस्टर_skciphers(cast5_algs, ARRAY_SIZE(cast5_algs),
				  cast5_simd_algs);
पूर्ण

module_init(cast5_init);
module_निकास(cast5_निकास);

MODULE_DESCRIPTION("Cast5 Cipher Algorithm, AVX optimized");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("cast5");
