<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Accelerated CRC-T10DIF using arm64 NEON and Crypto Extensions inकाष्ठाions
 *
 * Copyright (C) 2016 - 2017 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/cpufeature.h>
#समावेश <linux/crc-t10dअगर.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>

#घोषणा CRC_T10DIF_PMULL_CHUNK_SIZE	16U

यंत्रlinkage u16 crc_t10dअगर_pmull_p8(u16 init_crc, स्थिर u8 *buf, माप_प्रकार len);
यंत्रlinkage u16 crc_t10dअगर_pmull_p64(u16 init_crc, स्थिर u8 *buf, माप_प्रकार len);

अटल पूर्णांक crct10dअगर_init(काष्ठा shash_desc *desc)
अणु
	u16 *crc = shash_desc_ctx(desc);

	*crc = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक crct10dअगर_update_pmull_p8(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक length)
अणु
	u16 *crc = shash_desc_ctx(desc);

	अगर (length >= CRC_T10DIF_PMULL_CHUNK_SIZE && crypto_simd_usable()) अणु
		करो अणु
			अचिन्हित पूर्णांक chunk = length;

			अगर (chunk > SZ_4K + CRC_T10DIF_PMULL_CHUNK_SIZE)
				chunk = SZ_4K;

			kernel_neon_begin();
			*crc = crc_t10dअगर_pmull_p8(*crc, data, chunk);
			kernel_neon_end();
			data += chunk;
			length -= chunk;
		पूर्ण जबतक (length);
	पूर्ण अन्यथा अणु
		*crc = crc_t10dअगर_generic(*crc, data, length);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crct10dअगर_update_pmull_p64(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक length)
अणु
	u16 *crc = shash_desc_ctx(desc);

	अगर (length >= CRC_T10DIF_PMULL_CHUNK_SIZE && crypto_simd_usable()) अणु
		करो अणु
			अचिन्हित पूर्णांक chunk = length;

			अगर (chunk > SZ_4K + CRC_T10DIF_PMULL_CHUNK_SIZE)
				chunk = SZ_4K;

			kernel_neon_begin();
			*crc = crc_t10dअगर_pmull_p64(*crc, data, chunk);
			kernel_neon_end();
			data += chunk;
			length -= chunk;
		पूर्ण जबतक (length);
	पूर्ण अन्यथा अणु
		*crc = crc_t10dअगर_generic(*crc, data, length);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crct10dअगर_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u16 *crc = shash_desc_ctx(desc);

	*(u16 *)out = *crc;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg crc_t10dअगर_alg[] = अणुअणु
	.digestsize		= CRC_T10DIF_DIGEST_SIZE,
	.init			= crct10dअगर_init,
	.update			= crct10dअगर_update_pmull_p8,
	.final			= crct10dअगर_final,
	.descsize		= CRC_T10DIF_DIGEST_SIZE,

	.base.cra_name		= "crct10dif",
	.base.cra_driver_name	= "crct10dif-arm64-neon",
	.base.cra_priority	= 100,
	.base.cra_blocksize	= CRC_T10DIF_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण, अणु
	.digestsize		= CRC_T10DIF_DIGEST_SIZE,
	.init			= crct10dअगर_init,
	.update			= crct10dअगर_update_pmull_p64,
	.final			= crct10dअगर_final,
	.descsize		= CRC_T10DIF_DIGEST_SIZE,

	.base.cra_name		= "crct10dif",
	.base.cra_driver_name	= "crct10dif-arm64-ce",
	.base.cra_priority	= 200,
	.base.cra_blocksize	= CRC_T10DIF_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्णपूर्ण;

अटल पूर्णांक __init crc_t10dअगर_mod_init(व्योम)
अणु
	अगर (cpu_have_named_feature(PMULL))
		वापस crypto_रेजिस्टर_shashes(crc_t10dअगर_alg,
					       ARRAY_SIZE(crc_t10dअगर_alg));
	अन्यथा
		/* only रेजिस्टर the first array element */
		वापस crypto_रेजिस्टर_shash(crc_t10dअगर_alg);
पूर्ण

अटल व्योम __निकास crc_t10dअगर_mod_निकास(व्योम)
अणु
	अगर (cpu_have_named_feature(PMULL))
		crypto_unरेजिस्टर_shashes(crc_t10dअगर_alg,
					  ARRAY_SIZE(crc_t10dअगर_alg));
	अन्यथा
		crypto_unरेजिस्टर_shash(crc_t10dअगर_alg);
पूर्ण

module_cpu_feature_match(ASIMD, crc_t10dअगर_mod_init);
module_निकास(crc_t10dअगर_mod_निकास);

MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("crct10dif");
MODULE_ALIAS_CRYPTO("crct10dif-arm64-ce");
