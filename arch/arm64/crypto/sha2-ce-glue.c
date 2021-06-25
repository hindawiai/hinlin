<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sha2-ce-glue.c - SHA-224/SHA-256 using ARMv8 Crypto Extensions
 *
 * Copyright (C) 2014 - 2017 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha256_base.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

MODULE_DESCRIPTION("SHA-224/SHA-256 secure hash using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("sha224");
MODULE_ALIAS_CRYPTO("sha256");

काष्ठा sha256_ce_state अणु
	काष्ठा sha256_state	sst;
	u32			finalize;
पूर्ण;

बाह्य स्थिर u32 sha256_ce_दुरत्व_count;
बाह्य स्थिर u32 sha256_ce_दुरत्व_finalize;

यंत्रlinkage पूर्णांक sha2_ce_transक्रमm(काष्ठा sha256_ce_state *sst, u8 स्थिर *src,
				 पूर्णांक blocks);

अटल व्योम __sha2_ce_transक्रमm(काष्ठा sha256_state *sst, u8 स्थिर *src,
				पूर्णांक blocks)
अणु
	जबतक (blocks) अणु
		पूर्णांक rem;

		kernel_neon_begin();
		rem = sha2_ce_transक्रमm(container_of(sst, काष्ठा sha256_ce_state,
						     sst), src, blocks);
		kernel_neon_end();
		src += (blocks - rem) * SHA256_BLOCK_SIZE;
		blocks = rem;
	पूर्ण
पूर्ण

स्थिर u32 sha256_ce_दुरत्व_count = दुरत्व(काष्ठा sha256_ce_state,
					      sst.count);
स्थिर u32 sha256_ce_दुरत्व_finalize = दुरत्व(काष्ठा sha256_ce_state,
						 finalize);

यंत्रlinkage व्योम sha256_block_data_order(u32 *digest, u8 स्थिर *src, पूर्णांक blocks);

अटल व्योम __sha256_block_data_order(काष्ठा sha256_state *sst, u8 स्थिर *src,
				      पूर्णांक blocks)
अणु
	sha256_block_data_order(sst->state, src, blocks);
पूर्ण

अटल पूर्णांक sha256_ce_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha256_ce_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable())
		वापस sha256_base_करो_update(desc, data, len,
				__sha256_block_data_order);

	sctx->finalize = 0;
	sha256_base_करो_update(desc, data, len, __sha2_ce_transक्रमm);

	वापस 0;
पूर्ण

अटल पूर्णांक sha256_ce_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			   अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा sha256_ce_state *sctx = shash_desc_ctx(desc);
	bool finalize = !sctx->sst.count && !(len % SHA256_BLOCK_SIZE) && len;

	अगर (!crypto_simd_usable()) अणु
		अगर (len)
			sha256_base_करो_update(desc, data, len,
				__sha256_block_data_order);
		sha256_base_करो_finalize(desc, __sha256_block_data_order);
		वापस sha256_base_finish(desc, out);
	पूर्ण

	/*
	 * Allow the यंत्र code to perक्रमm the finalization अगर there is no
	 * partial data and the input is a round multiple of the block size.
	 */
	sctx->finalize = finalize;

	sha256_base_करो_update(desc, data, len, __sha2_ce_transक्रमm);
	अगर (!finalize)
		sha256_base_करो_finalize(desc, __sha2_ce_transक्रमm);
	वापस sha256_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha256_ce_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha256_ce_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable()) अणु
		sha256_base_करो_finalize(desc, __sha256_block_data_order);
		वापस sha256_base_finish(desc, out);
	पूर्ण

	sctx->finalize = 0;
	sha256_base_करो_finalize(desc, __sha2_ce_transक्रमm);
	वापस sha256_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha256_ce_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha256_ce_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, &sctx->sst, माप(काष्ठा sha256_state));
	वापस 0;
पूर्ण

अटल पूर्णांक sha256_ce_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha256_ce_state *sctx = shash_desc_ctx(desc);

	स_नकल(&sctx->sst, in, माप(काष्ठा sha256_state));
	sctx->finalize = 0;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg algs[] = अणु अणु
	.init			= sha224_base_init,
	.update			= sha256_ce_update,
	.final			= sha256_ce_final,
	.finup			= sha256_ce_finup,
	.export			= sha256_ce_export,
	.import			= sha256_ce_import,
	.descsize		= माप(काष्ठा sha256_ce_state),
	.statesize		= माप(काष्ठा sha256_state),
	.digestsize		= SHA224_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha224",
		.cra_driver_name	= "sha224-ce",
		.cra_priority		= 200,
		.cra_blocksize		= SHA256_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.init			= sha256_base_init,
	.update			= sha256_ce_update,
	.final			= sha256_ce_final,
	.finup			= sha256_ce_finup,
	.export			= sha256_ce_export,
	.import			= sha256_ce_import,
	.descsize		= माप(काष्ठा sha256_ce_state),
	.statesize		= माप(काष्ठा sha256_state),
	.digestsize		= SHA256_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha256",
		.cra_driver_name	= "sha256-ce",
		.cra_priority		= 200,
		.cra_blocksize		= SHA256_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init sha2_ce_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

अटल व्योम __निकास sha2_ce_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

module_cpu_feature_match(SHA2, sha2_ce_mod_init);
module_निकास(sha2_ce_mod_fini);
