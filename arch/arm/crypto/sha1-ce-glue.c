<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sha1-ce-glue.c - SHA-1 secure hash using ARMv8 Crypto Extensions
 *
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha1_base.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>

#समावेश "sha1.h"

MODULE_DESCRIPTION("SHA1 secure hash using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

यंत्रlinkage व्योम sha1_ce_transक्रमm(काष्ठा sha1_state *sst, u8 स्थिर *src,
				  पूर्णांक blocks);

अटल पूर्णांक sha1_ce_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			  अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable() ||
	    (sctx->count % SHA1_BLOCK_SIZE) + len < SHA1_BLOCK_SIZE)
		वापस sha1_update_arm(desc, data, len);

	kernel_neon_begin();
	sha1_base_करो_update(desc, data, len, sha1_ce_transक्रमm);
	kernel_neon_end();

	वापस 0;
पूर्ण

अटल पूर्णांक sha1_ce_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (!crypto_simd_usable())
		वापस sha1_finup_arm(desc, data, len, out);

	kernel_neon_begin();
	अगर (len)
		sha1_base_करो_update(desc, data, len, sha1_ce_transक्रमm);
	sha1_base_करो_finalize(desc, sha1_ce_transक्रमm);
	kernel_neon_end();

	वापस sha1_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha1_ce_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha1_ce_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.init			= sha1_base_init,
	.update			= sha1_ce_update,
	.final			= sha1_ce_final,
	.finup			= sha1_ce_finup,
	.descsize		= माप(काष्ठा sha1_state),
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
