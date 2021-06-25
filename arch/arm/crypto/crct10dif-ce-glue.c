<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Accelerated CRC-T10DIF using ARM NEON and Crypto Extensions inकाष्ठाions
 *
 * Copyright (C) 2016 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

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

यंत्रlinkage u16 crc_t10dअगर_pmull(u16 init_crc, स्थिर u8 *buf, माप_प्रकार len);

अटल पूर्णांक crct10dअगर_init(काष्ठा shash_desc *desc)
अणु
	u16 *crc = shash_desc_ctx(desc);

	*crc = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक crct10dअगर_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक length)
अणु
	u16 *crc = shash_desc_ctx(desc);

	अगर (length >= CRC_T10DIF_PMULL_CHUNK_SIZE && crypto_simd_usable()) अणु
		kernel_neon_begin();
		*crc = crc_t10dअगर_pmull(*crc, data, length);
		kernel_neon_end();
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

अटल काष्ठा shash_alg crc_t10dअगर_alg = अणु
	.digestsize		= CRC_T10DIF_DIGEST_SIZE,
	.init			= crct10dअगर_init,
	.update			= crct10dअगर_update,
	.final			= crct10dअगर_final,
	.descsize		= CRC_T10DIF_DIGEST_SIZE,

	.base.cra_name		= "crct10dif",
	.base.cra_driver_name	= "crct10dif-arm-ce",
	.base.cra_priority	= 200,
	.base.cra_blocksize	= CRC_T10DIF_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crc_t10dअगर_mod_init(व्योम)
अणु
	अगर (!(elf_hwcap2 & HWCAP2_PMULL))
		वापस -ENODEV;

	वापस crypto_रेजिस्टर_shash(&crc_t10dअगर_alg);
पूर्ण

अटल व्योम __निकास crc_t10dअगर_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&crc_t10dअगर_alg);
पूर्ण

module_init(crc_t10dअगर_mod_init);
module_निकास(crc_t10dअगर_mod_निकास);

MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("crct10dif");
