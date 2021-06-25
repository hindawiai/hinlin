<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Calculate a CRC T10-DIF with vpmsum acceleration
 *
 * Copyright 2017, Daniel Axtens, IBM Corporation.
 * [based on crc32c-vpmsum_glue.c]
 */

#समावेश <linux/crc-t10dअगर.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/cpufeature.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/चयन_to.h>

#घोषणा VMX_ALIGN		16
#घोषणा VMX_ALIGN_MASK		(VMX_ALIGN-1)

#घोषणा VECTOR_BREAKPOINT	64

u32 __crct10dअगर_vpmsum(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len);

अटल u16 crct10dअगर_vpmsum(u16 crci, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक prealign;
	अचिन्हित पूर्णांक tail;
	u32 crc = crci;

	अगर (len < (VECTOR_BREAKPOINT + VMX_ALIGN) || !crypto_simd_usable())
		वापस crc_t10dअगर_generic(crc, p, len);

	अगर ((अचिन्हित दीर्घ)p & VMX_ALIGN_MASK) अणु
		prealign = VMX_ALIGN - ((अचिन्हित दीर्घ)p & VMX_ALIGN_MASK);
		crc = crc_t10dअगर_generic(crc, p, prealign);
		len -= prealign;
		p += prealign;
	पूर्ण

	अगर (len & ~VMX_ALIGN_MASK) अणु
		crc <<= 16;
		preempt_disable();
		pagefault_disable();
		enable_kernel_altivec();
		crc = __crct10dअगर_vpmsum(crc, p, len & ~VMX_ALIGN_MASK);
		disable_kernel_altivec();
		pagefault_enable();
		preempt_enable();
		crc >>= 16;
	पूर्ण

	tail = len & VMX_ALIGN_MASK;
	अगर (tail) अणु
		p += len & ~VMX_ALIGN_MASK;
		crc = crc_t10dअगर_generic(crc, p, tail);
	पूर्ण

	वापस crc & 0xffff;
पूर्ण

अटल पूर्णांक crct10dअगर_vpmsum_init(काष्ठा shash_desc *desc)
अणु
	u16 *crc = shash_desc_ctx(desc);

	*crc = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक crct10dअगर_vpmsum_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक length)
अणु
	u16 *crc = shash_desc_ctx(desc);

	*crc = crct10dअगर_vpmsum(*crc, data, length);

	वापस 0;
पूर्ण


अटल पूर्णांक crct10dअगर_vpmsum_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u16 *crcp = shash_desc_ctx(desc);

	*(u16 *)out = *crcp;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.init		= crct10dअगर_vpmsum_init,
	.update		= crct10dअगर_vpmsum_update,
	.final		= crct10dअगर_vpmsum_final,
	.descsize	= CRC_T10DIF_DIGEST_SIZE,
	.digestsize	= CRC_T10DIF_DIGEST_SIZE,
	.base		= अणु
		.cra_name		= "crct10dif",
		.cra_driver_name	= "crct10dif-vpmsum",
		.cra_priority		= 200,
		.cra_blocksize		= CRC_T10DIF_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init crct10dअगर_vpmsum_mod_init(व्योम)
अणु
	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास crct10dअगर_vpmsum_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_cpu_feature_match(PPC_MODULE_FEATURE_VEC_CRYPTO, crct10dअगर_vpmsum_mod_init);
module_निकास(crct10dअगर_vpmsum_mod_fini);

MODULE_AUTHOR("Daniel Axtens <dja@axtens.net>");
MODULE_DESCRIPTION("CRCT10DIF using vector polynomial multiply-sum instructions");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("crct10dif");
MODULE_ALIAS_CRYPTO("crct10dif-vpmsum");
