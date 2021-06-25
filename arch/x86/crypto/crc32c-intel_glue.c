<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Using hardware provided CRC32 inकाष्ठाion to accelerate the CRC32 disposal.
 * CRC32C polynomial:0x1EDC6F41(BE)/0x82F63B78(LE)
 * CRC32 is a new inकाष्ठाion in Intel SSE4.2, the reference can be found at:
 * http://www.पूर्णांकel.com/products/processor/manuals/
 * Intel(R) 64 and IA-32 Architectures Software Developer's Manual
 * Volume 2A: Inकाष्ठाion Set Reference, A-M
 *
 * Copyright (C) 2008 Intel Corporation
 * Authors: Austin Zhang <austin_zhang@linux.पूर्णांकel.com>
 *          Kent Liu <kent.liu@पूर्णांकel.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>

#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/simd.h>

#घोषणा CHKSUM_BLOCK_SIZE	1
#घोषणा CHKSUM_DIGEST_SIZE	4

#घोषणा SCALE_F	माप(अचिन्हित दीर्घ)

#अगर_घोषित CONFIG_X86_64
#घोषणा CRC32_INST "crc32q %1, %q0"
#अन्यथा
#घोषणा CRC32_INST "crc32l %1, %0"
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
/*
 * use carryless multiply version of crc32c when buffer
 * size is >= 512 to account
 * क्रम fpu state save/restore overhead.
 */
#घोषणा CRC32C_PCL_BREAKEVEN	512

यंत्रlinkage अचिन्हित पूर्णांक crc_pcl(स्थिर u8 *buffer, पूर्णांक len,
				अचिन्हित पूर्णांक crc_init);
#पूर्ण_अगर /* CONFIG_X86_64 */

अटल u32 crc32c_पूर्णांकel_le_hw_byte(u32 crc, अचिन्हित अक्षर स्थिर *data, माप_प्रकार length)
अणु
	जबतक (length--) अणु
		यंत्र("crc32b %1, %0"
		    : "+r" (crc) : "rm" (*data));
		data++;
	पूर्ण

	वापस crc;
पूर्ण

अटल u32 __pure crc32c_पूर्णांकel_le_hw(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक iquotient = len / SCALE_F;
	अचिन्हित पूर्णांक ireमुख्यder = len % SCALE_F;
	अचिन्हित दीर्घ *pपंचांगp = (अचिन्हित दीर्घ *)p;

	जबतक (iquotient--) अणु
		यंत्र(CRC32_INST
		    : "+r" (crc) : "rm" (*pपंचांगp));
		pपंचांगp++;
	पूर्ण

	अगर (ireमुख्यder)
		crc = crc32c_पूर्णांकel_le_hw_byte(crc, (अचिन्हित अक्षर *)pपंचांगp,
				 ireमुख्यder);

	वापस crc;
पूर्ण

/*
 * Setting the seed allows arbitrary accumulators and flexible XOR policy
 * If your algorithm starts with ~0, then XOR with ~0 beक्रमe you set
 * the seed.
 */
अटल पूर्णांक crc32c_पूर्णांकel_setkey(काष्ठा crypto_shash *hash, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	u32 *mctx = crypto_shash_ctx(hash);

	अगर (keylen != माप(u32))
		वापस -EINVAL;
	*mctx = le32_to_cpup((__le32 *)key);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_पूर्णांकel_init(काष्ठा shash_desc *desc)
अणु
	u32 *mctx = crypto_shash_ctx(desc->tfm);
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = *mctx;

	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_पूर्णांकel_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = crc32c_पूर्णांकel_le_hw(*crcp, data, len);
	वापस 0;
पूर्ण

अटल पूर्णांक __crc32c_पूर्णांकel_finup(u32 *crcp, स्थिर u8 *data, अचिन्हित पूर्णांक len,
				u8 *out)
अणु
	*(__le32 *)out = ~cpu_to_le32(crc32c_पूर्णांकel_le_hw(*crcp, data, len));
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_पूर्णांकel_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32c_पूर्णांकel_finup(shash_desc_ctx(desc), data, len, out);
पूर्ण

अटल पूर्णांक crc32c_पूर्णांकel_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	*(__le32 *)out = ~cpu_to_le32p(crcp);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_पूर्णांकel_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32c_पूर्णांकel_finup(crypto_shash_ctx(desc->tfm), data, len,
				    out);
पूर्ण

अटल पूर्णांक crc32c_पूर्णांकel_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	u32 *key = crypto_tfm_ctx(tfm);

	*key = ~0;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल पूर्णांक crc32c_pcl_पूर्णांकel_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	/*
	 * use faster PCL version अगर datasize is large enough to
	 * overcome kernel fpu state save/restore overhead
	 */
	अगर (len >= CRC32C_PCL_BREAKEVEN && crypto_simd_usable()) अणु
		kernel_fpu_begin();
		*crcp = crc_pcl(data, len, *crcp);
		kernel_fpu_end();
	पूर्ण अन्यथा
		*crcp = crc32c_पूर्णांकel_le_hw(*crcp, data, len);
	वापस 0;
पूर्ण

अटल पूर्णांक __crc32c_pcl_पूर्णांकel_finup(u32 *crcp, स्थिर u8 *data, अचिन्हित पूर्णांक len,
				u8 *out)
अणु
	अगर (len >= CRC32C_PCL_BREAKEVEN && crypto_simd_usable()) अणु
		kernel_fpu_begin();
		*(__le32 *)out = ~cpu_to_le32(crc_pcl(data, len, *crcp));
		kernel_fpu_end();
	पूर्ण अन्यथा
		*(__le32 *)out =
			~cpu_to_le32(crc32c_पूर्णांकel_le_hw(*crcp, data, len));
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_pcl_पूर्णांकel_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32c_pcl_पूर्णांकel_finup(shash_desc_ctx(desc), data, len, out);
पूर्ण

अटल पूर्णांक crc32c_pcl_पूर्णांकel_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32c_pcl_पूर्णांकel_finup(crypto_shash_ctx(desc->tfm), data, len,
				    out);
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_64 */

अटल काष्ठा shash_alg alg = अणु
	.setkey			=	crc32c_पूर्णांकel_setkey,
	.init			=	crc32c_पूर्णांकel_init,
	.update			=	crc32c_पूर्णांकel_update,
	.final			=	crc32c_पूर्णांकel_final,
	.finup			=	crc32c_पूर्णांकel_finup,
	.digest			=	crc32c_पूर्णांकel_digest,
	.descsize		=	माप(u32),
	.digestsize		=	CHKSUM_DIGEST_SIZE,
	.base			=	अणु
		.cra_name		=	"crc32c",
		.cra_driver_name	=	"crc32c-intel",
		.cra_priority		=	200,
		.cra_flags		=	CRYPTO_ALG_OPTIONAL_KEY,
		.cra_blocksize		=	CHKSUM_BLOCK_SIZE,
		.cra_ctxsize		=	माप(u32),
		.cra_module		=	THIS_MODULE,
		.cra_init		=	crc32c_पूर्णांकel_cra_init,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id crc32c_cpu_id[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_XMM4_2, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, crc32c_cpu_id);

अटल पूर्णांक __init crc32c_पूर्णांकel_mod_init(व्योम)
अणु
	अगर (!x86_match_cpu(crc32c_cpu_id))
		वापस -ENODEV;
#अगर_घोषित CONFIG_X86_64
	अगर (boot_cpu_has(X86_FEATURE_PCLMULQDQ)) अणु
		alg.update = crc32c_pcl_पूर्णांकel_update;
		alg.finup = crc32c_pcl_पूर्णांकel_finup;
		alg.digest = crc32c_pcl_पूर्णांकel_digest;
	पूर्ण
#पूर्ण_अगर
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास crc32c_पूर्णांकel_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(crc32c_पूर्णांकel_mod_init);
module_निकास(crc32c_पूर्णांकel_mod_fini);

MODULE_AUTHOR("Austin Zhang <austin.zhang@intel.com>, Kent Liu <kent.liu@intel.com>");
MODULE_DESCRIPTION("CRC32c (Castagnoli) optimization using Intel Hardware.");
MODULE_LICENSE("GPL");

MODULE_ALIAS_CRYPTO("crc32c");
MODULE_ALIAS_CRYPTO("crc32c-intel");
