<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue Code क्रम SSE2 assembler versions of Serpent Cipher
 *
 * Copyright (c) 2011 Jussi Kivilinna <jussi.kivilinna@mbnet.fi>
 *
 * Glue code based on aesni-पूर्णांकel_glue.c by:
 *  Copyright (C) 2008, Intel Corp.
 *    Author: Huang Ying <ying.huang@पूर्णांकel.com>
 *
 * CBC & ECB parts based on code (crypto/cbc.c,ecb.c) by:
 *   Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/b128ops.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/serpent.h>

#समावेश "serpent-sse2.h"
#समावेश "ecb_cbc_helpers.h"

अटल पूर्णांक serpent_setkey_skcipher(काष्ठा crypto_skcipher *tfm,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस __serpent_setkey(crypto_skcipher_ctx(tfm), key, keylen);
पूर्ण

अटल व्योम serpent_decrypt_cbc_xway(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	u8 buf[SERPENT_PARALLEL_BLOCKS - 1][SERPENT_BLOCK_SIZE];
	स्थिर u8 *s = src;

	अगर (dst == src)
		s = स_नकल(buf, src, माप(buf));
	serpent_dec_blk_xway(ctx, dst, src);
	crypto_xor(dst + SERPENT_BLOCK_SIZE, s, माप(buf));
पूर्ण

अटल पूर्णांक ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, SERPENT_BLOCK_SIZE, SERPENT_PARALLEL_BLOCKS);
	ECB_BLOCK(SERPENT_PARALLEL_BLOCKS, serpent_enc_blk_xway);
	ECB_BLOCK(1, __serpent_encrypt);
	ECB_WALK_END();
पूर्ण

अटल पूर्णांक ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	ECB_WALK_START(req, SERPENT_BLOCK_SIZE, SERPENT_PARALLEL_BLOCKS);
	ECB_BLOCK(SERPENT_PARALLEL_BLOCKS, serpent_dec_blk_xway);
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
	CBC_DEC_BLOCK(SERPENT_PARALLEL_BLOCKS, serpent_decrypt_cbc_xway);
	CBC_DEC_BLOCK(1, __serpent_decrypt);
	CBC_WALK_END();
पूर्ण

अटल काष्ठा skcipher_alg serpent_algs[] = अणु
	अणु
		.base.cra_name		= "__ecb(serpent)",
		.base.cra_driver_name	= "__ecb-serpent-sse2",
		.base.cra_priority	= 400,
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
		.base.cra_driver_name	= "__cbc-serpent-sse2",
		.base.cra_priority	= 400,
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

अटल पूर्णांक __init serpent_sse2_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_XMM2)) अणु
		prपूर्णांकk(KERN_INFO "SSE2 instructions are not detected.\n");
		वापस -ENODEV;
	पूर्ण

	वापस simd_रेजिस्टर_skciphers_compat(serpent_algs,
					      ARRAY_SIZE(serpent_algs),
					      serpent_simd_algs);
पूर्ण

अटल व्योम __निकास serpent_sse2_निकास(व्योम)
अणु
	simd_unरेजिस्टर_skciphers(serpent_algs, ARRAY_SIZE(serpent_algs),
				  serpent_simd_algs);
पूर्ण

module_init(serpent_sse2_init);
module_निकास(serpent_sse2_निकास);

MODULE_DESCRIPTION("Serpent Cipher Algorithm, SSE2 optimized");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("serpent");
