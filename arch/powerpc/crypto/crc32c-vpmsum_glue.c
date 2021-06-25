<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/crc32.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/cpufeature.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/चयन_to.h>

#घोषणा CHKSUM_BLOCK_SIZE	1
#घोषणा CHKSUM_DIGEST_SIZE	4

#घोषणा VMX_ALIGN		16
#घोषणा VMX_ALIGN_MASK		(VMX_ALIGN-1)

#घोषणा VECTOR_BREAKPOINT	512

u32 __crc32c_vpmsum(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len);

अटल u32 crc32c_vpmsum(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक prealign;
	अचिन्हित पूर्णांक tail;

	अगर (len < (VECTOR_BREAKPOINT + VMX_ALIGN) || !crypto_simd_usable())
		वापस __crc32c_le(crc, p, len);

	अगर ((अचिन्हित दीर्घ)p & VMX_ALIGN_MASK) अणु
		prealign = VMX_ALIGN - ((अचिन्हित दीर्घ)p & VMX_ALIGN_MASK);
		crc = __crc32c_le(crc, p, prealign);
		len -= prealign;
		p += prealign;
	पूर्ण

	अगर (len & ~VMX_ALIGN_MASK) अणु
		preempt_disable();
		pagefault_disable();
		enable_kernel_altivec();
		crc = __crc32c_vpmsum(crc, p, len & ~VMX_ALIGN_MASK);
		disable_kernel_altivec();
		pagefault_enable();
		preempt_enable();
	पूर्ण

	tail = len & VMX_ALIGN_MASK;
	अगर (tail) अणु
		p += len & ~VMX_ALIGN_MASK;
		crc = __crc32c_le(crc, p, tail);
	पूर्ण

	वापस crc;
पूर्ण

अटल पूर्णांक crc32c_vpmsum_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	u32 *key = crypto_tfm_ctx(tfm);

	*key = ~0;

	वापस 0;
पूर्ण

/*
 * Setting the seed allows arbitrary accumulators and flexible XOR policy
 * If your algorithm starts with ~0, then XOR with ~0 beक्रमe you set
 * the seed.
 */
अटल पूर्णांक crc32c_vpmsum_setkey(काष्ठा crypto_shash *hash, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	u32 *mctx = crypto_shash_ctx(hash);

	अगर (keylen != माप(u32))
		वापस -EINVAL;
	*mctx = le32_to_cpup((__le32 *)key);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_vpmsum_init(काष्ठा shash_desc *desc)
अणु
	u32 *mctx = crypto_shash_ctx(desc->tfm);
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = *mctx;

	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_vpmsum_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = crc32c_vpmsum(*crcp, data, len);

	वापस 0;
पूर्ण

अटल पूर्णांक __crc32c_vpmsum_finup(u32 *crcp, स्थिर u8 *data, अचिन्हित पूर्णांक len,
				u8 *out)
अणु
	*(__le32 *)out = ~cpu_to_le32(crc32c_vpmsum(*crcp, data, len));

	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_vpmsum_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32c_vpmsum_finup(shash_desc_ctx(desc), data, len, out);
पूर्ण

अटल पूर्णांक crc32c_vpmsum_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	*(__le32 *)out = ~cpu_to_le32p(crcp);

	वापस 0;
पूर्ण

अटल पूर्णांक crc32c_vpmsum_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32c_vpmsum_finup(crypto_shash_ctx(desc->tfm), data, len,
				     out);
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.setkey		= crc32c_vpmsum_setkey,
	.init		= crc32c_vpmsum_init,
	.update		= crc32c_vpmsum_update,
	.final		= crc32c_vpmsum_final,
	.finup		= crc32c_vpmsum_finup,
	.digest		= crc32c_vpmsum_digest,
	.descsize	= माप(u32),
	.digestsize	= CHKSUM_DIGEST_SIZE,
	.base		= अणु
		.cra_name		= "crc32c",
		.cra_driver_name	= "crc32c-vpmsum",
		.cra_priority		= 200,
		.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,
		.cra_blocksize		= CHKSUM_BLOCK_SIZE,
		.cra_ctxsize		= माप(u32),
		.cra_module		= THIS_MODULE,
		.cra_init		= crc32c_vpmsum_cra_init,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init crc32c_vpmsum_mod_init(व्योम)
अणु
	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास crc32c_vpmsum_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_cpu_feature_match(PPC_MODULE_FEATURE_VEC_CRYPTO, crc32c_vpmsum_mod_init);
module_निकास(crc32c_vpmsum_mod_fini);

MODULE_AUTHOR("Anton Blanchard <anton@samba.org>");
MODULE_DESCRIPTION("CRC32C using vector polynomial multiply-sum instructions");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("crc32c");
MODULE_ALIAS_CRYPTO("crc32c-vpmsum");
