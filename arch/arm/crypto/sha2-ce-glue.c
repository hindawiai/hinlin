<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sha2-ce-glue.c - SHA-224/SHA-256 using ARMv8 Crypto Extensions
 *
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha256_base.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "sha256_glue.h"

MODULE_DESCRIPTION("SHA-224/SHA-256 secure hash using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

यंत्रlinkage व्योम sha2_ce_transक्रमm(काष्ठा sha256_state *sst, u8 स्थिर *src,
				  पूर्णांक blocks);

अटल पूर्णांक sha2_ce_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			  अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable() ||
	    (sctx->count % SHA256_BLOCK_SIZE) + len < SHA256_BLOCK_SIZE)
		वापस crypto_sha256_arm_update(desc, data, len);

	kernel_neon_begin();
	sha256_base_करो_update(desc, data, len,
			      (sha256_block_fn *)sha2_ce_transक्रमm);
	kernel_neon_end();

	वापस 0;
पूर्ण

अटल पूर्णांक sha2_ce_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_sha256_arm_finup(desc, data, len, out);

	kernel_neon_begin();
	अगर (len)
		sha256_base_करो_update(desc, data, len,
				      (sha256_block_fn *)sha2_ce_transक्रमm);
	sha256_base_करो_finalize(desc, (sha256_block_fn *)sha2_ce_transक्रमm);
	kernel_neon_end();

	वापस sha256_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha2_ce_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha2_ce_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg algs[] = अणु अणु
	.init			= sha224_base_init,
	.update			= sha2_ce_update,
	.final			= sha2_ce_final,
	.finup			= sha2_ce_finup,
	.descsize		= माप(काष्ठा sha256_state),
	.digestsize		= SHA224_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha224",
		.cra_driver_name	= "sha224-ce",
		.cra_priority		= 300,
		.cra_blocksize		= SHA256_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.init			= sha256_base_init,
	.update			= sha2_ce_update,
	.final			= sha2_ce_final,
	.finup			= sha2_ce_finup,
	.descsize		= माप(काष्ठा sha256_state),
	.digestsize		= SHA256_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha256",
		.cra_driver_name	= "sha256-ce",
		.cra_priority		= 300,
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
