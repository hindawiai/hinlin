<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cryptographic API.
 *
 * s390 implementation of the GHASH algorithm क्रम GCM (Galois/Counter Mode).
 *
 * Copyright IBM Corp. 2011
 * Author(s): Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <यंत्र/cpacf.h>

#घोषणा GHASH_BLOCK_SIZE	16
#घोषणा GHASH_DIGEST_SIZE	16

काष्ठा ghash_ctx अणु
	u8 key[GHASH_BLOCK_SIZE];
पूर्ण;

काष्ठा ghash_desc_ctx अणु
	u8 icv[GHASH_BLOCK_SIZE];
	u8 key[GHASH_BLOCK_SIZE];
	u8 buffer[GHASH_BLOCK_SIZE];
	u32 bytes;
पूर्ण;

अटल पूर्णांक ghash_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	काष्ठा ghash_ctx *ctx = crypto_shash_ctx(desc->tfm);

	स_रखो(dctx, 0, माप(*dctx));
	स_नकल(dctx->key, ctx->key, GHASH_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक ghash_setkey(काष्ठा crypto_shash *tfm,
			स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ghash_ctx *ctx = crypto_shash_ctx(tfm);

	अगर (keylen != GHASH_BLOCK_SIZE)
		वापस -EINVAL;

	स_नकल(ctx->key, key, GHASH_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक ghash_update(काष्ठा shash_desc *desc,
			 स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक n;
	u8 *buf = dctx->buffer;

	अगर (dctx->bytes) अणु
		u8 *pos = buf + (GHASH_BLOCK_SIZE - dctx->bytes);

		n = min(srclen, dctx->bytes);
		dctx->bytes -= n;
		srclen -= n;

		स_नकल(pos, src, n);
		src += n;

		अगर (!dctx->bytes) अणु
			cpacf_kimd(CPACF_KIMD_GHASH, dctx, buf,
				   GHASH_BLOCK_SIZE);
		पूर्ण
	पूर्ण

	n = srclen & ~(GHASH_BLOCK_SIZE - 1);
	अगर (n) अणु
		cpacf_kimd(CPACF_KIMD_GHASH, dctx, src, n);
		src += n;
		srclen -= n;
	पूर्ण

	अगर (srclen) अणु
		dctx->bytes = GHASH_BLOCK_SIZE - srclen;
		स_नकल(buf, src, srclen);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ghash_flush(काष्ठा ghash_desc_ctx *dctx)
अणु
	u8 *buf = dctx->buffer;

	अगर (dctx->bytes) अणु
		u8 *pos = buf + (GHASH_BLOCK_SIZE - dctx->bytes);

		स_रखो(pos, 0, dctx->bytes);
		cpacf_kimd(CPACF_KIMD_GHASH, dctx, buf, GHASH_BLOCK_SIZE);
		dctx->bytes = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ghash_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	पूर्णांक ret;

	ret = ghash_flush(dctx);
	अगर (!ret)
		स_नकल(dst, dctx->icv, GHASH_BLOCK_SIZE);
	वापस ret;
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
		.cra_driver_name	= "ghash-s390",
		.cra_priority		= 300,
		.cra_blocksize		= GHASH_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा ghash_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ghash_mod_init(व्योम)
अणु
	अगर (!cpacf_query_func(CPACF_KIMD, CPACF_KIMD_GHASH))
		वापस -ENODEV;

	वापस crypto_रेजिस्टर_shash(&ghash_alg);
पूर्ण

अटल व्योम __निकास ghash_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&ghash_alg);
पूर्ण

module_cpu_feature_match(MSA, ghash_mod_init);
module_निकास(ghash_mod_निकास);

MODULE_ALIAS_CRYPTO("ghash");

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GHASH hash function, s390 implementation");
