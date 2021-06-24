<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Accelerated GHASH implementation with ARMv8 vmull.p64 inकाष्ठाions.
 *
 * Copyright (C) 2015 - 2018 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/b128ops.h>
#समावेश <crypto/cryptd.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/gf128mul.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/module.h>

MODULE_DESCRIPTION("GHASH hash function using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("ghash");

#घोषणा GHASH_BLOCK_SIZE	16
#घोषणा GHASH_DIGEST_SIZE	16

काष्ठा ghash_key अणु
	be128	k;
	u64	h[][2];
पूर्ण;

काष्ठा ghash_desc_ctx अणु
	u64 digest[GHASH_DIGEST_SIZE/माप(u64)];
	u8 buf[GHASH_BLOCK_SIZE];
	u32 count;
पूर्ण;

काष्ठा ghash_async_ctx अणु
	काष्ठा cryptd_ahash *cryptd_tfm;
पूर्ण;

यंत्रlinkage व्योम pmull_ghash_update_p64(पूर्णांक blocks, u64 dg[], स्थिर अक्षर *src,
				       u64 स्थिर h[][2], स्थिर अक्षर *head);

यंत्रlinkage व्योम pmull_ghash_update_p8(पूर्णांक blocks, u64 dg[], स्थिर अक्षर *src,
				      u64 स्थिर h[][2], स्थिर अक्षर *head);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(use_p64);

अटल पूर्णांक ghash_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा ghash_desc_ctx *ctx = shash_desc_ctx(desc);

	*ctx = (काष्ठा ghash_desc_ctx)अणुपूर्ण;
	वापस 0;
पूर्ण

अटल व्योम ghash_करो_update(पूर्णांक blocks, u64 dg[], स्थिर अक्षर *src,
			    काष्ठा ghash_key *key, स्थिर अक्षर *head)
अणु
	अगर (likely(crypto_simd_usable())) अणु
		kernel_neon_begin();
		अगर (अटल_branch_likely(&use_p64))
			pmull_ghash_update_p64(blocks, dg, src, key->h, head);
		अन्यथा
			pmull_ghash_update_p8(blocks, dg, src, key->h, head);
		kernel_neon_end();
	पूर्ण अन्यथा अणु
		be128 dst = अणु cpu_to_be64(dg[1]), cpu_to_be64(dg[0]) पूर्ण;

		करो अणु
			स्थिर u8 *in = src;

			अगर (head) अणु
				in = head;
				blocks++;
				head = शून्य;
			पूर्ण अन्यथा अणु
				src += GHASH_BLOCK_SIZE;
			पूर्ण

			crypto_xor((u8 *)&dst, in, GHASH_BLOCK_SIZE);
			gf128mul_lle(&dst, &key->k);
		पूर्ण जबतक (--blocks);

		dg[0] = be64_to_cpu(dst.b);
		dg[1] = be64_to_cpu(dst.a);
	पूर्ण
पूर्ण

अटल पूर्णांक ghash_update(काष्ठा shash_desc *desc, स्थिर u8 *src,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा ghash_desc_ctx *ctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = ctx->count % GHASH_BLOCK_SIZE;

	ctx->count += len;

	अगर ((partial + len) >= GHASH_BLOCK_SIZE) अणु
		काष्ठा ghash_key *key = crypto_shash_ctx(desc->tfm);
		पूर्णांक blocks;

		अगर (partial) अणु
			पूर्णांक p = GHASH_BLOCK_SIZE - partial;

			स_नकल(ctx->buf + partial, src, p);
			src += p;
			len -= p;
		पूर्ण

		blocks = len / GHASH_BLOCK_SIZE;
		len %= GHASH_BLOCK_SIZE;

		ghash_करो_update(blocks, ctx->digest, src, key,
				partial ? ctx->buf : शून्य);
		src += blocks * GHASH_BLOCK_SIZE;
		partial = 0;
	पूर्ण
	अगर (len)
		स_नकल(ctx->buf + partial, src, len);
	वापस 0;
पूर्ण

अटल पूर्णांक ghash_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	काष्ठा ghash_desc_ctx *ctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = ctx->count % GHASH_BLOCK_SIZE;

	अगर (partial) अणु
		काष्ठा ghash_key *key = crypto_shash_ctx(desc->tfm);

		स_रखो(ctx->buf + partial, 0, GHASH_BLOCK_SIZE - partial);
		ghash_करो_update(1, ctx->digest, ctx->buf, key, शून्य);
	पूर्ण
	put_unaligned_be64(ctx->digest[1], dst);
	put_unaligned_be64(ctx->digest[0], dst + 8);

	*ctx = (काष्ठा ghash_desc_ctx)अणुपूर्ण;
	वापस 0;
पूर्ण

अटल व्योम ghash_reflect(u64 h[], स्थिर be128 *k)
अणु
	u64 carry = be64_to_cpu(k->a) >> 63;

	h[0] = (be64_to_cpu(k->b) << 1) | carry;
	h[1] = (be64_to_cpu(k->a) << 1) | (be64_to_cpu(k->b) >> 63);

	अगर (carry)
		h[1] ^= 0xc200000000000000UL;
पूर्ण

अटल पूर्णांक ghash_setkey(काष्ठा crypto_shash *tfm,
			स्थिर u8 *inkey, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ghash_key *key = crypto_shash_ctx(tfm);

	अगर (keylen != GHASH_BLOCK_SIZE)
		वापस -EINVAL;

	/* needed क्रम the fallback */
	स_नकल(&key->k, inkey, GHASH_BLOCK_SIZE);
	ghash_reflect(key->h[0], &key->k);

	अगर (अटल_branch_likely(&use_p64)) अणु
		be128 h = key->k;

		gf128mul_lle(&h, &key->k);
		ghash_reflect(key->h[1], &h);

		gf128mul_lle(&h, &key->k);
		ghash_reflect(key->h[2], &h);

		gf128mul_lle(&h, &key->k);
		ghash_reflect(key->h[3], &h);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg ghash_alg = अणु
	.digestsize		= GHASH_DIGEST_SIZE,
	.init			= ghash_init,
	.update			= ghash_update,
	.final			= ghash_final,
	.setkey			= ghash_setkey,
	.descsize		= माप(काष्ठा ghash_desc_ctx),

	.base.cra_name		= "ghash",
	.base.cra_driver_name	= "ghash-ce-sync",
	.base.cra_priority	= 300 - 1,
	.base.cra_blocksize	= GHASH_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा ghash_key) + माप(u64[2]),
	.base.cra_module	= THIS_MODULE,
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

अटल पूर्णांक ghash_async_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा ahash_request *cryptd_req = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा ghash_async_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा shash_desc *desc = cryptd_shash_desc(cryptd_req);

	desc->tfm = cryptd_ahash_child(ctx->cryptd_tfm);

	वापस crypto_shash_import(desc, in);
पूर्ण

अटल पूर्णांक ghash_async_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा ahash_request *cryptd_req = ahash_request_ctx(req);
	काष्ठा shash_desc *desc = cryptd_shash_desc(cryptd_req);

	वापस crypto_shash_export(desc, out);
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

	cryptd_tfm = cryptd_alloc_ahash("ghash-ce-sync", 0, 0);
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
	.init			= ghash_async_init,
	.update			= ghash_async_update,
	.final			= ghash_async_final,
	.setkey			= ghash_async_setkey,
	.digest			= ghash_async_digest,
	.import			= ghash_async_import,
	.export			= ghash_async_export,
	.halg.digestsize	= GHASH_DIGEST_SIZE,
	.halg.statesize		= माप(काष्ठा ghash_desc_ctx),
	.halg.base		= अणु
		.cra_name	= "ghash",
		.cra_driver_name = "ghash-ce",
		.cra_priority	= 300,
		.cra_flags	= CRYPTO_ALG_ASYNC,
		.cra_blocksize	= GHASH_BLOCK_SIZE,
		.cra_ctxsize	= माप(काष्ठा ghash_async_ctx),
		.cra_module	= THIS_MODULE,
		.cra_init	= ghash_async_init_tfm,
		.cra_निकास	= ghash_async_निकास_tfm,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ghash_ce_mod_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!(elf_hwcap & HWCAP_NEON))
		वापस -ENODEV;

	अगर (elf_hwcap2 & HWCAP2_PMULL) अणु
		ghash_alg.base.cra_ctxsize += 3 * माप(u64[2]);
		अटल_branch_enable(&use_p64);
	पूर्ण

	err = crypto_रेजिस्टर_shash(&ghash_alg);
	अगर (err)
		वापस err;
	err = crypto_रेजिस्टर_ahash(&ghash_async_alg);
	अगर (err)
		जाओ err_shash;

	वापस 0;

err_shash:
	crypto_unरेजिस्टर_shash(&ghash_alg);
	वापस err;
पूर्ण

अटल व्योम __निकास ghash_ce_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ahash(&ghash_async_alg);
	crypto_unरेजिस्टर_shash(&ghash_alg);
पूर्ण

module_init(ghash_ce_mod_init);
module_निकास(ghash_ce_mod_निकास);
