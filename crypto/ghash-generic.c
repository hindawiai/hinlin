<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GHASH: hash function क्रम GCM (Galois/Counter Mode).
 *
 * Copyright (c) 2007 Nokia Siemens Networks - Mikko Herranen <mh1@iki.fi>
 * Copyright (c) 2009 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

/*
 * GHASH is a keyed hash function used in GCM authentication tag generation.
 *
 * The original GCM paper [1] presents GHASH as a function GHASH(H, A, C) which
 * takes a 16-byte hash key H, additional authenticated data A, and a ciphertext
 * C.  It क्रमmats A and C पूर्णांकo a single byte string X, पूर्णांकerprets X as a
 * polynomial over GF(2^128), and evaluates this polynomial at the poपूर्णांक H.
 *
 * However, the NIST standard क्रम GCM [2] presents GHASH as GHASH(H, X) where X
 * is the alपढ़ोy-क्रमmatted byte string containing both A and C.
 *
 * "ghash" in the Linux crypto API uses the 'X' (pre-क्रमmatted) convention,
 * since the API supports only a single data stream per hash.  Thus, the
 * क्रमmatting of 'A' and 'C' is करोne in the "gcm" ढाँचा, not in "ghash".
 *
 * The reason "ghash" is separate from "gcm" is to allow "gcm" to use an
 * accelerated "ghash" when a standalone accelerated "gcm(aes)" is unavailable.
 * It is generally inappropriate to use "ghash" क्रम other purposes, since it is
 * an "Nग-almost-XOR-universal hash function", not a cryptographic hash function.
 * It can only be used securely in crypto modes specially deचिन्हित to use it.
 *
 * [1] The Galois/Counter Mode of Operation (GCM)
 *     (http://citeseerx.ist.psu.edu/viewकरोc/करोwnload?करोi=10.1.1.694.695&rep=rep1&type=pdf)
 * [2] Recommendation क्रम Block Cipher Modes of Operation: Galois/Counter Mode (GCM) and GMAC
 *     (https://csrc.nist.gov/खुलाations/detail/sp/800-38d/final)
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/gf128mul.h>
#समावेश <crypto/ghash.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

अटल पूर्णांक ghash_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	स_रखो(dctx, 0, माप(*dctx));

	वापस 0;
पूर्ण

अटल पूर्णांक ghash_setkey(काष्ठा crypto_shash *tfm,
			स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ghash_ctx *ctx = crypto_shash_ctx(tfm);
	be128 k;

	अगर (keylen != GHASH_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (ctx->gf128)
		gf128mul_मुक्त_4k(ctx->gf128);

	BUILD_BUG_ON(माप(k) != GHASH_BLOCK_SIZE);
	स_नकल(&k, key, GHASH_BLOCK_SIZE); /* aव्योम violating alignment rules */
	ctx->gf128 = gf128mul_init_4k_lle(&k);
	memzero_explicit(&k, GHASH_BLOCK_SIZE);

	अगर (!ctx->gf128)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ghash_update(काष्ठा shash_desc *desc,
			 स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	काष्ठा ghash_ctx *ctx = crypto_shash_ctx(desc->tfm);
	u8 *dst = dctx->buffer;

	अगर (dctx->bytes) अणु
		पूर्णांक n = min(srclen, dctx->bytes);
		u8 *pos = dst + (GHASH_BLOCK_SIZE - dctx->bytes);

		dctx->bytes -= n;
		srclen -= n;

		जबतक (n--)
			*pos++ ^= *src++;

		अगर (!dctx->bytes)
			gf128mul_4k_lle((be128 *)dst, ctx->gf128);
	पूर्ण

	जबतक (srclen >= GHASH_BLOCK_SIZE) अणु
		crypto_xor(dst, src, GHASH_BLOCK_SIZE);
		gf128mul_4k_lle((be128 *)dst, ctx->gf128);
		src += GHASH_BLOCK_SIZE;
		srclen -= GHASH_BLOCK_SIZE;
	पूर्ण

	अगर (srclen) अणु
		dctx->bytes = GHASH_BLOCK_SIZE - srclen;
		जबतक (srclen--)
			*dst++ ^= *src++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ghash_flush(काष्ठा ghash_ctx *ctx, काष्ठा ghash_desc_ctx *dctx)
अणु
	u8 *dst = dctx->buffer;

	अगर (dctx->bytes) अणु
		u8 *पंचांगp = dst + (GHASH_BLOCK_SIZE - dctx->bytes);

		जबतक (dctx->bytes--)
			*पंचांगp++ ^= 0;

		gf128mul_4k_lle((be128 *)dst, ctx->gf128);
	पूर्ण

	dctx->bytes = 0;
पूर्ण

अटल पूर्णांक ghash_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	काष्ठा ghash_ctx *ctx = crypto_shash_ctx(desc->tfm);
	u8 *buf = dctx->buffer;

	ghash_flush(ctx, dctx);
	स_नकल(dst, buf, GHASH_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल व्योम ghash_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ghash_ctx *ctx = crypto_tfm_ctx(tfm);
	अगर (ctx->gf128)
		gf128mul_मुक्त_4k(ctx->gf128);
पूर्ण

अटल काष्ठा shash_alg ghash_alg = अणु
	.digestsize	= GHASH_DIGEST_SIZE,
	.init		= ghash_init,
	.update		= ghash_update,
	.final		= ghash_final,
	.setkey		= ghash_setkey,
	.descsize	= माप(काष्ठा ghash_desc_ctx),
	.base		= अणु
		.cra_name		= "ghash",
		.cra_driver_name	= "ghash-generic",
		.cra_priority		= 100,
		.cra_blocksize		= GHASH_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा ghash_ctx),
		.cra_module		= THIS_MODULE,
		.cra_निकास		= ghash_निकास_tfm,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ghash_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&ghash_alg);
पूर्ण

अटल व्योम __निकास ghash_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&ghash_alg);
पूर्ण

subsys_initcall(ghash_mod_init);
module_निकास(ghash_mod_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GHASH hash function");
MODULE_ALIAS_CRYPTO("ghash");
MODULE_ALIAS_CRYPTO("ghash-generic");
