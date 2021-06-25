<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sm3-ce-glue.c - SM3 secure hash using ARMv8.2 Crypto Extensions
 *
 * Copyright (C) 2018 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sm3.h>
#समावेश <crypto/sm3_base.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

MODULE_DESCRIPTION("SM3 secure hash using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

यंत्रlinkage व्योम sm3_ce_transक्रमm(काष्ठा sm3_state *sst, u8 स्थिर *src,
				 पूर्णांक blocks);

अटल पूर्णांक sm3_ce_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_sm3_update(desc, data, len);

	kernel_neon_begin();
	sm3_base_करो_update(desc, data, len, sm3_ce_transक्रमm);
	kernel_neon_end();

	वापस 0;
पूर्ण

अटल पूर्णांक sm3_ce_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_sm3_finup(desc, शून्य, 0, out);

	kernel_neon_begin();
	sm3_base_करो_finalize(desc, sm3_ce_transक्रमm);
	kernel_neon_end();

	वापस sm3_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sm3_ce_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_sm3_finup(desc, data, len, out);

	kernel_neon_begin();
	sm3_base_करो_update(desc, data, len, sm3_ce_transक्रमm);
	kernel_neon_end();

	वापस sm3_ce_final(desc, out);
पूर्ण

अटल काष्ठा shash_alg sm3_alg = अणु
	.digestsize		= SM3_DIGEST_SIZE,
	.init			= sm3_base_init,
	.update			= sm3_ce_update,
	.final			= sm3_ce_final,
	.finup			= sm3_ce_finup,
	.descsize		= माप(काष्ठा sm3_state),
	.base.cra_name		= "sm3",
	.base.cra_driver_name	= "sm3-ce",
	.base.cra_blocksize	= SM3_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
	.base.cra_priority	= 200,
पूर्ण;

अटल पूर्णांक __init sm3_ce_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&sm3_alg);
पूर्ण

अटल व्योम __निकास sm3_ce_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&sm3_alg);
पूर्ण

module_cpu_feature_match(SM3, sm3_ce_mod_init);
module_निकास(sm3_ce_mod_fini);
