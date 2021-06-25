<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Accelerated CRC32(C) using ARM CRC, NEON and Crypto Extensions inकाष्ठाions
 *
 * Copyright (C) 2016 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/cpufeature.h>
#समावेश <linux/crc32.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा PMULL_MIN_LEN		64L	/* minimum size of buffer
					 * क्रम crc32_pmull_le_16 */
#घोषणा SCALE_F			16L	/* size of NEON रेजिस्टर */

यंत्रlinkage u32 crc32_pmull_le(स्थिर u8 buf[], u32 len, u32 init_crc);
यंत्रlinkage u32 crc32_armv8_le(u32 init_crc, स्थिर u8 buf[], u32 len);

यंत्रlinkage u32 crc32c_pmull_le(स्थिर u8 buf[], u32 len, u32 init_crc);
यंत्रlinkage u32 crc32c_armv8_le(u32 init_crc, स्थिर u8 buf[], u32 len);

अटल u32 (*fallback_crc32)(u32 init_crc, स्थिर u8 buf[], u32 len);
अटल u32 (*fallback_crc32c)(u32 init_crc, स्थिर u8 buf[], u32 len);

अटल पूर्णांक crc32_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	u32 *key = crypto_tfm_ctx(tfm);

	*key = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	u32 *key = crypto_tfm_ctx(tfm);

	*key = ~0;
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_setkey(काष्ठा crypto_shash *hash, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	u32 *mctx = crypto_shash_ctx(hash);

	अगर (keylen != माप(u32))
		वापस -EINVAL;
	*mctx = le32_to_cpup((__le32 *)key);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_init(काष्ठा shash_desc *desc)
अणु
	u32 *mctx = crypto_shash_ctx(desc->tfm);
	u32 *crc = shash_desc_ctx(desc);

	*crc = *mctx;
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक length)
अणु
	u32 *crc = shash_desc_ctx(desc);

	*crc = crc32_armv8_le(*crc, data, length);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक length)
अणु
	u32 *crc = shash_desc_ctx(desc);

	*crc = crc32c_armv8_le(*crc, data, length);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u32 *crc = shash_desc_ctx(desc);

	put_unaligned_le32(*crc, out);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u32 *crc = shash_desc_ctx(desc);

	put_unaligned_le32(~*crc, out);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_pmull_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक length)
अणु
	u32 *crc = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक l;

	अगर (crypto_simd_usable()) अणु
		अगर ((u32)data % SCALE_F) अणु
			l = min_t(u32, length, SCALE_F - ((u32)data % SCALE_F));

			*crc = fallback_crc32(*crc, data, l);

			data += l;
			length -= l;
		पूर्ण

		अगर (length >= PMULL_MIN_LEN) अणु
			l = round_करोwn(length, SCALE_F);

			kernel_neon_begin();
			*crc = crc32_pmull_le(data, l, *crc);
			kernel_neon_end();

			data += l;
			length -= l;
		पूर्ण
	पूर्ण

	अगर (length > 0)
		*crc = fallback_crc32(*crc, data, length);

	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_pmull_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक length)
अणु
	u32 *crc = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक l;

	अगर (crypto_simd_usable()) अणु
		अगर ((u32)data % SCALE_F) अणु
			l = min_t(u32, length, SCALE_F - ((u32)data % SCALE_F));

			*crc = fallback_crc32c(*crc, data, l);

			data += l;
			length -= l;
		पूर्ण

		अगर (length >= PMULL_MIN_LEN) अणु
			l = round_करोwn(length, SCALE_F);

			kernel_neon_begin();
			*crc = crc32c_pmull_le(data, l, *crc);
			kernel_neon_end();

			data += l;
			length -= l;
		पूर्ण
	पूर्ण

	अगर (length > 0)
		*crc = fallback_crc32c(*crc, data, length);

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg crc32_pmull_algs[] = अणु अणु
	.setkey			= crc32_setkey,
	.init			= crc32_init,
	.update			= crc32_update,
	.final			= crc32_final,
	.descsize		= माप(u32),
	.digestsize		= माप(u32),

	.base.cra_ctxsize	= माप(u32),
	.base.cra_init		= crc32_cra_init,
	.base.cra_name		= "crc32",
	.base.cra_driver_name	= "crc32-arm-ce",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,
	.base.cra_blocksize	= 1,
	.base.cra_module	= THIS_MODULE,
पूर्ण, अणु
	.setkey			= crc32_setkey,
	.init			= crc32_init,
	.update			= crc32c_update,
	.final			= crc32c_final,
	.descsize		= माप(u32),
	.digestsize		= माप(u32),

	.base.cra_ctxsize	= माप(u32),
	.base.cra_init		= crc32c_cra_init,
	.base.cra_name		= "crc32c",
	.base.cra_driver_name	= "crc32c-arm-ce",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,
	.base.cra_blocksize	= 1,
	.base.cra_module	= THIS_MODULE,
पूर्ण पूर्ण;

अटल पूर्णांक __init crc32_pmull_mod_init(व्योम)
अणु
	अगर (elf_hwcap2 & HWCAP2_PMULL) अणु
		crc32_pmull_algs[0].update = crc32_pmull_update;
		crc32_pmull_algs[1].update = crc32c_pmull_update;

		अगर (elf_hwcap2 & HWCAP2_CRC32) अणु
			fallback_crc32 = crc32_armv8_le;
			fallback_crc32c = crc32c_armv8_le;
		पूर्ण अन्यथा अणु
			fallback_crc32 = crc32_le;
			fallback_crc32c = __crc32c_le;
		पूर्ण
	पूर्ण अन्यथा अगर (!(elf_hwcap2 & HWCAP2_CRC32)) अणु
		वापस -ENODEV;
	पूर्ण

	वापस crypto_रेजिस्टर_shashes(crc32_pmull_algs,
				       ARRAY_SIZE(crc32_pmull_algs));
पूर्ण

अटल व्योम __निकास crc32_pmull_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(crc32_pmull_algs,
				  ARRAY_SIZE(crc32_pmull_algs));
पूर्ण

अटल स्थिर काष्ठा cpu_feature __maybe_unused crc32_cpu_feature[] = अणु
	अणु cpu_feature(CRC32) पूर्ण, अणु cpu_feature(PMULL) पूर्ण, अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(cpu, crc32_cpu_feature);

module_init(crc32_pmull_mod_init);
module_निकास(crc32_pmull_mod_निकास);

MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("crc32");
MODULE_ALIAS_CRYPTO("crc32c");
