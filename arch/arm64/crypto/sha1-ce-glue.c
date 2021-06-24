<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sha1-ce-glue.c - SHA-1 secure hash using ARMv8 Crypto Extensions
 *
 * Copyright (C) 2014 - 2017 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha1_base.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

MODULE_DESCRIPTION("SHA1 secure hash using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("sha1");

काष्ठा sha1_ce_state अणु
	काष्ठा sha1_state	sst;
	u32			finalize;
पूर्ण;

बाह्य स्थिर u32 sha1_ce_दुरत्व_count;
बाह्य स्थिर u32 sha1_ce_दुरत्व_finalize;

यंत्रlinkage पूर्णांक sha1_ce_transक्रमm(काष्ठा sha1_ce_state *sst, u8 स्थिर *src,
				 पूर्णांक blocks);

अटल व्योम __sha1_ce_transक्रमm(काष्ठा sha1_state *sst, u8 स्थिर *src,
				पूर्णांक blocks)
अणु
	जबतक (blocks) अणु
		पूर्णांक rem;

		kernel_neon_begin();
		rem = sha1_ce_transक्रमm(container_of(sst, काष्ठा sha1_ce_state,
						     sst), src, blocks);
		kernel_neon_end();
		src += (blocks - rem) * SHA1_BLOCK_SIZE;
		blocks = rem;
	पूर्ण
पूर्ण

स्थिर u32 sha1_ce_दुरत्व_count = दुरत्व(काष्ठा sha1_ce_state, sst.count);
स्थिर u32 sha1_ce_दुरत्व_finalize = दुरत्व(काष्ठा sha1_ce_state, finalize);

अटल पूर्णांक sha1_ce_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			  अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha1_ce_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable())
		वापस crypto_sha1_update(desc, data, len);

	sctx->finalize = 0;
	sha1_base_करो_update(desc, data, len, __sha1_ce_transक्रमm);

	वापस 0;
पूर्ण

अटल पूर्णांक sha1_ce_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा sha1_ce_state *sctx = shash_desc_ctx(desc);
	bool finalize = !sctx->sst.count && !(len % SHA1_BLOCK_SIZE) && len;

	अगर (!crypto_simd_usable())
		वापस crypto_sha1_finup(desc, data, len, out);

	/*
	 * Allow the यंत्र code to perक्रमm the finalization अगर there is no
	 * partial data and the input is a round multiple of the block size.
	 */
	sctx->finalize = finalize;

	sha1_base_करो_update(desc, data, len, __sha1_ce_transक्रमm);
	अगर (!finalize)
		sha1_base_करो_finalize(desc, __sha1_ce_transक्रमm);
	वापस sha1_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha1_ce_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha1_ce_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable())
		वापस crypto_sha1_finup(desc, शून्य, 0, out);

	sctx->finalize = 0;
	sha1_base_करो_finalize(desc, __sha1_ce_transक्रमm);
	वापस sha1_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha1_ce_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha1_ce_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, &sctx->sst, माप(काष्ठा sha1_state));
	वापस 0;
पूर्ण

अटल पूर्णांक sha1_ce_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha1_ce_state *sctx = shash_desc_ctx(desc);

	स_नकल(&sctx->sst, in, माप(काष्ठा sha1_state));
	sctx->finalize = 0;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.init			= sha1_base_init,
	.update			= sha1_ce_update,
	.final			= sha1_ce_final,
	.finup			= sha1_ce_finup,
	.import			= sha1_ce_import,
	.export			= sha1_ce_export,
	.descsize		= माप(काष्ठा sha1_ce_state),
	.statesize		= माप(काष्ठा sha1_state),
	.digestsize		= SHA1_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha1",
		.cra_driver_name	= "sha1-ce",
		.cra_priority		= 200,
		.cra_blocksize		= SHA1_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sha1_ce_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास sha1_ce_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_cpu_feature_match(SHA1, sha1_ce_mod_init);
module_निकास(sha1_ce_mod_fini);
