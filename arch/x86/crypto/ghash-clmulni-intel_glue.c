<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Accelerated GHASH implementation with Intel PCLMULQDQ-NI
 * inकाष्ठाions. This file contains glue code.
 *
 * Copyright (c) 2009 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/cryptd.h>
#समावेश <crypto/gf128mul.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/simd.h>

#घोषणा GHASH_BLOCK_SIZE	16
#घोषणा GHASH_DIGEST_SIZE	16

व्योम clmul_ghash_mul(अक्षर *dst, स्थिर u128 *shash);

व्योम clmul_ghash_update(अक्षर *dst, स्थिर अक्षर *src, अचिन्हित पूर्णांक srclen,
			स्थिर u128 *shash);

काष्ठा ghash_async_ctx अणु
	काष्ठा cryptd_ahash *cryptd_tfm;
पूर्ण;

काष्ठा ghash_ctx अणु
	u128 shash;
पूर्ण;

काष्ठा ghash_desc_ctx अणु
	u8 buffer[GHASH_BLOCK_SIZE];
	u32 bytes;
पूर्ण;

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
	be128 *x = (be128 *)key;
	u64 a, b;

	अगर (keylen != GHASH_BLOCK_SIZE)
		वापस -EINVAL;

	/* perक्रमm multiplication by 'x' in GF(2^128) */
	a = be64_to_cpu(x->a);
	b = be64_to_cpu(x->b);

	ctx->shash.a = (b << 1) | (a >> 63);
	ctx->shash.b = (a << 1) | (b >> 63);

	अगर (a >> 63)
		ctx->shash.b ^= ((u64)0xc2) << 56;

	वापस 0;
पूर्ण

अटल पूर्णांक ghash_update(काष्ठा shash_desc *desc,
			 स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	काष्ठा ghash_ctx *ctx = crypto_shash_ctx(desc->tfm);
	u8 *dst = dctx->buffer;

	kernel_fpu_begin();
	अगर (dctx->bytes) अणु
		पूर्णांक n = min(srclen, dctx->bytes);
		u8 *pos = dst + (GHASH_BLOCK_SIZE - dctx->bytes);

		dctx->bytes -= n;
		srclen -= n;

		जबतक (n--)
			*pos++ ^= *src++;

		अगर (!dctx->bytes)
			clmul_ghash_mul(dst, &ctx->shash);
	पूर्ण

	clmul_ghash_update(dst, src, srclen, &ctx->shash);
	kernel_fpu_end();

	अगर (srclen & 0xf) अणु
		src += srclen - (srclen & 0xf);
		srclen &= 0xf;
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

		kernel_fpu_begin();
		clmul_ghash_mul(dst, &ctx->shash);
		kernel_fpu_end();
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

अटल काष्ठा shash_alg ghash_alg = अणु
	.digestsize	= GHASH_DIGEST_SIZE,
	.init		= ghash_init,
	.update		= ghash_update,
	.final		= ghash_final,
	.setkey		= ghash_setkey,
	.descsize	= माप(काष्ठा ghash_desc_ctx),
	.base		= अणु
		.cra_name		= "__ghash",
		.cra_driver_name	= "__ghash-pclmulqdqni",
		.cra_priority		= 0,
		.cra_flags		= CRYPTO_ALG_INTERNAL,
		.cra_blocksize		= GHASH_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा ghash_ctx),
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ghash_async_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *cryptd_req = ahash_request_ctx(req);
	काष्ठा cryptd_ahash *cryptd_tfm = ctx->cryptd_tfm;
	काष्ठा shash_desc *desc = cryptd_shash_desc(cryptd_req);
	काष्ठा crypto_shash *child = cryptd_ahash_child(cryptd_tfm);

	desc->tfm = child;
	वापस crypto_shash_init(desc);
पूर्ण

अटल पूर्णांक ghash_async_update(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_request *cryptd_req = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा cryptd_ahash *cryptd_tfm = ctx->cryptd_tfm;

	अगर (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_ahash_queued(cryptd_tfm))) अणु
		स_नकल(cryptd_req, req, माप(*req));
		ahash_request_set_tfm(cryptd_req, &cryptd_tfm->base);
		वापस crypto_ahash_update(cryptd_req);
	पूर्ण अन्यथा अणु
		काष्ठा shash_desc *desc = cryptd_shash_desc(cryptd_req);
		वापस shash_ahash_update(req, desc);
	पूर्ण
पूर्ण

अटल पूर्णांक ghash_async_final(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_request *cryptd_req = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा cryptd_ahash *cryptd_tfm = ctx->cryptd_tfm;

	अगर (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_ahash_queued(cryptd_tfm))) अणु
		स_नकल(cryptd_req, req, माप(*req));
		ahash_request_set_tfm(cryptd_req, &cryptd_tfm->base);
		वापस crypto_ahash_final(cryptd_req);
	पूर्ण अन्यथा अणु
		काष्ठा shash_desc *desc = cryptd_shash_desc(cryptd_req);
		वापस crypto_shash_final(desc, req->result);
	पूर्ण
पूर्ण

अटल पूर्णांक ghash_async_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा ahash_request *cryptd_req = ahash_request_ctx(req);
	काष्ठा shash_desc *desc = cryptd_shash_desc(cryptd_req);
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	ghash_async_init(req);
	स_नकल(dctx, in, माप(*dctx));
	वापस 0;

पूर्ण

अटल पूर्णांक ghash_async_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा ahash_request *cryptd_req = ahash_request_ctx(req);
	काष्ठा shash_desc *desc = cryptd_shash_desc(cryptd_req);
	काष्ठा ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	स_नकल(out, dctx, माप(*dctx));
	वापस 0;

पूर्ण

अटल पूर्णांक ghash_async_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा ahash_request *cryptd_req = ahash_request_ctx(req);
	काष्ठा cryptd_ahash *cryptd_tfm = ctx->cryptd_tfm;

	अगर (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_ahash_queued(cryptd_tfm))) अणु
		स_नकल(cryptd_req, req, माप(*req));
		ahash_request_set_tfm(cryptd_req, &cryptd_tfm->base);
		वापस crypto_ahash_digest(cryptd_req);
	पूर्ण अन्यथा अणु
		काष्ठा shash_desc *desc = cryptd_shash_desc(cryptd_req);
		काष्ठा crypto_shash *child = cryptd_ahash_child(cryptd_tfm);

		desc->tfm = child;
		वापस shash_ahash_digest(req, desc);
	पूर्ण
पूर्ण

अटल पूर्णांक ghash_async_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा crypto_ahash *child = &ctx->cryptd_tfm->base;

	crypto_ahash_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_ahash_set_flags(child, crypto_ahash_get_flags(tfm)
			       & CRYPTO_TFM_REQ_MASK);
	वापस crypto_ahash_setkey(child, key, keylen);
पूर्ण

अटल पूर्णांक ghash_async_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cryptd_ahash *cryptd_tfm;
	काष्ठा ghash_async_ctx *ctx = crypto_tfm_ctx(tfm);

	cryptd_tfm = cryptd_alloc_ahash("__ghash-pclmulqdqni",
					CRYPTO_ALG_INTERNAL,
					CRYPTO_ALG_INTERNAL);
	अगर (IS_ERR(cryptd_tfm))
		वापस PTR_ERR(cryptd_tfm);
	ctx->cryptd_tfm = cryptd_tfm;
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा ahash_request) +
				 crypto_ahash_reqsize(&cryptd_tfm->base));

	वापस 0;
पूर्ण

अटल व्योम ghash_async_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा ghash_async_ctx *ctx = crypto_tfm_ctx(tfm);

	cryptd_मुक्त_ahash(ctx->cryptd_tfm);
पूर्ण

अटल काष्ठा ahash_alg ghash_async_alg = अणु
	.init		= ghash_async_init,
	.update		= ghash_async_update,
	.final		= ghash_async_final,
	.setkey		= ghash_async_setkey,
	.digest		= ghash_async_digest,
	.export		= ghash_async_export,
	.import		= ghash_async_import,
	.halg = अणु
		.digestsize	= GHASH_DIGEST_SIZE,
		.statesize = माप(काष्ठा ghash_desc_ctx),
		.base = अणु
			.cra_name		= "ghash",
			.cra_driver_name	= "ghash-clmulni",
			.cra_priority		= 400,
			.cra_ctxsize		= माप(काष्ठा ghash_async_ctx),
			.cra_flags		= CRYPTO_ALG_ASYNC,
			.cra_blocksize		= GHASH_BLOCK_SIZE,
			.cra_module		= THIS_MODULE,
			.cra_init		= ghash_async_init_tfm,
			.cra_निकास		= ghash_async_निकास_tfm,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id pcmul_cpu_id[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_PCLMULQDQ, शून्य), /* Pickle-Mickle-Duck */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, pcmul_cpu_id);

अटल पूर्णांक __init ghash_pclmulqdqni_mod_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!x86_match_cpu(pcmul_cpu_id))
		वापस -ENODEV;

	err = crypto_रेजिस्टर_shash(&ghash_alg);
	अगर (err)
		जाओ err_out;
	err = crypto_रेजिस्टर_ahash(&ghash_async_alg);
	अगर (err)
		जाओ err_shash;

	वापस 0;

err_shash:
	crypto_unरेजिस्टर_shash(&ghash_alg);
err_out:
	वापस err;
पूर्ण

अटल व्योम __निकास ghash_pclmulqdqni_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ahash(&ghash_async_alg);
	crypto_unरेजिस्टर_shash(&ghash_alg);
पूर्ण

module_init(ghash_pclmulqdqni_mod_init);
module_निकास(ghash_pclmulqdqni_mod_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GHASH hash function, accelerated by PCLMULQDQ-NI");
MODULE_ALIAS_CRYPTO("ghash");
