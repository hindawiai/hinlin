<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sha512-ce-glue.c - SHA-384/SHA-512 using ARMv8 Crypto Extensions
 *
 * Copyright (C) 2018 Linaro Ltd <ard.biesheuvel@linaro.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha512_base.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

MODULE_DESCRIPTION("SHA-384/SHA-512 secure hash using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("sha384");
MODULE_ALIAS_CRYPTO("sha512");

यंत्रlinkage पूर्णांक sha512_ce_transक्रमm(काष्ठा sha512_state *sst, u8 स्थिर *src,
				   पूर्णांक blocks);

यंत्रlinkage व्योम sha512_block_data_order(u64 *digest, u8 स्थिर *src, पूर्णांक blocks);

अटल व्योम __sha512_ce_transक्रमm(काष्ठा sha512_state *sst, u8 स्थिर *src,
				  पूर्णांक blocks)
अणु
	जबतक (blocks) अणु
		पूर्णांक rem;

		kernel_neon_begin();
		rem = sha512_ce_transक्रमm(sst, src, blocks);
		kernel_neon_end();
		src += (blocks - rem) * SHA512_BLOCK_SIZE;
		blocks = rem;
	पूर्ण
पूर्ण

अटल व्योम __sha512_block_data_order(काष्ठा sha512_state *sst, u8 स्थिर *src,
				      पूर्णांक blocks)
अणु
	sha512_block_data_order(sst->state, src, blocks);
पूर्ण

अटल पूर्णांक sha512_ce_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक len)
अणु
	sha512_block_fn *fn = crypto_simd_usable() ? __sha512_ce_transक्रमm
						   : __sha512_block_data_order;

	sha512_base_करो_update(desc, data, len, fn);
	वापस 0;
पूर्ण

अटल पूर्णांक sha512_ce_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			   अचिन्हित पूर्णांक len, u8 *out)
अणु
	sha512_block_fn *fn = crypto_simd_usable() ? __sha512_ce_transक्रमm
						   : __sha512_block_data_order;

	sha512_base_करो_update(desc, data, len, fn);
	sha512_base_करो_finalize(desc, fn);
	वापस sha512_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha512_ce_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	sha512_block_fn *fn = crypto_simd_usable() ? __sha512_ce_transक्रमm
						   : __sha512_block_data_order;

	sha512_base_करो_finalize(desc, fn);
	वापस sha512_base_finish(desc, out);
पूर्ण

अटल काष्ठा shash_alg algs[] = अणु अणु
	.init			= sha384_base_init,
	.update			= sha512_ce_update,
	.final			= sha512_ce_final,
	.finup			= sha512_ce_finup,
	.descsize		= माप(काष्ठा sha512_state),
	.digestsize		= SHA384_DIGEST_SIZE,
	.base.cra_name		= "sha384",
	.base.cra_driver_name	= "sha384-ce",
	.base.cra_priority	= 200,
	.base.cra_blocksize	= SHA512_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण, अणु
	.init			= sha512_base_init,
	.update			= sha512_ce_update,
	.final			= sha512_ce_final,
	.finup			= sha512_ce_finup,
	.descsize		= माप(काष्ठा sha512_state),
	.digestsize		= SHA512_DIGEST_SIZE,
	.base.cra_name		= "sha512",
	.base.cra_driver_name	= "sha512-ce",
	.base.cra_priority	= 200,
	.base.cra_blocksize	= SHA512_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण पूर्ण;

अटल पूर्णांक __init sha512_ce_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

अटल व्योम __निकास sha512_ce_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

module_cpu_feature_match(SHA512, sha512_ce_mod_init);
module_निकास(sha512_ce_mod_fini);
