<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue Code क्रम AVX assembler version of Twofish Cipher
 *
 * Copyright (C) 2012 Johannes Goetzfried
 *     <Johannes.Goetzfried@inक्रमmatik.stud.uni-erlangen.de>
 *
 * Copyright तऊ 2013 Jussi Kivilinna <jussi.kivilinna@iki.fi>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/twofish.h>

#समावेश "twofish.h"
#समावेश "ecb_cbc_helpers.h"

#घोषणा TWOFISH_PARALLEL_BLOCKS 8

/* 8-way parallel cipher functions */
यंत्रlinkage व्योम twofish_ecb_enc_8way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);
यंत्रlinkage व्योम twofish_ecb_dec_8way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

यंत्रlinkage व्योम twofish_cbc_dec_8way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

अटल पूर्णांक twofish_setkey_skcipher(काष्ठा crypto_skcipher *tfm,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस twofish_setkey(&tfm->base, key, keylen);
पूर्ण

अटल अंतरभूत व्योम twofish_enc_blk_3way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	__twofish_enc_blk_3way(ctx, dst, src, false);
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, TF_BLOCK_SIZE, TWOFISH_PARALLEL_BLOCKS);
	ECB_BLOCK(TWOFISH_PARALLEL_BLOCKS, twofish_ecb_enc_8way);
	ECB_BLOCK(3, twofish_enc_blk_3way);
	ECB_BLOCK(1, twofish_enc_blk);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, TF_BLOCK_SIZE, TWOFISH_PARALLEL_BLOCKS);
	ECB_BLOCK(TWOFISH_PARALLEL_BLOCKS, twofish_ecb_dec_8way);
	ECB_BLOCK(3, twofish_dec_blk_3way);
	ECB_BLOCK(1, twofish_dec_blk);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, TF_BLOCK_SIZE, -1);
	CBC_ENC_BLOCK(twofish_enc_blk);
	CBC_WALK_END();
पूर्ण

अटल पूर्णांक cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	CBC_WALK_START(req, TF_BLOCK_SIZE, TWOFISH_PARALLEL_BLOCKS);
	CBC_DEC_BLOCK(TWOFISH_PARALLEL_BLOCKS, twofish_cbc_dec_8way);
	CBC_DEC_BLOCK(3, twofish_dec_blk_cbc_3way);
	CBC_DEC_BLOCK(1, twofish_dec_blk);
	CBC_WALK_END();
पूर्ण

अटल काष्ठा skcipher_alg twofish_algs[] = अणु
	अणु
		.base.cra_name		= "__ecb(twofish)",
		.base.cra_driver_name	= "__ecb-twofish-avx",
		.base.cra_priority	= 400,
		.base.cra_flags		= CRYPTO_ALG_INTERNAL,
		.base.cra_blocksize	= TF_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा twofish_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= TF_MIN_KEY_SIZE,
		.max_keysize		= TF_MAX_KEY_SIZE,
		.setkey			= twofish_setkey_skcipher,
		.encrypt		= ecb_encrypt,
		.decrypt		= ecb_decrypt,
	पूर्ण, अणु
		.base.cra_name		= "__cbc(twofish)",
		.base.cra_driver_name	= "__cbc-twofish-avx",
		.base.cra_priority	= 400,
		.base.cra_flags		= CRYPTO_ALG_INTERNAL,
		.base.cra_blocksize	= TF_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा twofish_ctx),
		.base.cra_module	= THIS_MODULE,
		.min_keysize		= TF_MIN_KEY_SIZE,
		.max_keysize		= TF_MAX_KEY_SIZE,
		.ivsize			= TF_BLOCK_SIZE,
		.setkey			= twofish_setkey_skcipher,
		.encrypt		= cbc_encrypt,
		.decrypt		= cbc_decrypt,
	पूर्ण,
पूर्ण;

अटल काष्ठा simd_skcipher_alg *twofish_simd_algs[ARRAY_SIZE(twofish_algs)];

अटल पूर्णांक __init twofish_init(व्योम)
अणु
	स्थिर अक्षर *feature_name;

	अगर (!cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, &feature_name)) अणु
		pr_info("CPU feature '%s' is not supported.\n", feature_name);
		वापस -ENODEV;
	पूर्ण

	वापस simd_रेजिस्टर_skciphers_compat(twofish_algs,
					      ARRAY_SIZE(twofish_algs),
					      twofish_simd_algs);
पूर्ण

अटल व्योम __निकास twofish_निकास(व्योम)
अणु
	simd_unरेजिस्टर_skciphers(twofish_algs, ARRAY_SIZE(twofish_algs),
				  twofish_simd_algs);
पूर्ण

module_init(twofish_init);
module_निकास(twofish_निकास);

MODULE_DESCRIPTION("Twofish Cipher Algorithm, AVX optimized");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("twofish");
