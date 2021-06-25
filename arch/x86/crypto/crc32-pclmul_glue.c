<शैली गुरु>
/* GPL HEADER START
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS खाता HEADER.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 only,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License version 2 क्रम more details (a copy is included
 * in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU General Public License
 * version 2 aदीर्घ with this program; If not, see http://www.gnu.org/licenses
 *
 * Please  visit http://www.xyratex.com/contact अगर you need additional
 * inक्रमmation or have any questions.
 *
 * GPL HEADER END
 */

/*
 * Copyright 2012 Xyratex Technology Limited
 *
 * Wrappers क्रम kernel crypto shash api to pclmulqdq crc32 implementation.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/crc32.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>

#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/simd.h>

#घोषणा CHKSUM_BLOCK_SIZE	1
#घोषणा CHKSUM_DIGEST_SIZE	4

#घोषणा PCLMUL_MIN_LEN		64L     /* minimum size of buffer
					 * क्रम crc32_pclmul_le_16 */
#घोषणा SCALE_F			16L	/* size of xmm रेजिस्टर */
#घोषणा SCALE_F_MASK		(SCALE_F - 1)

u32 crc32_pclmul_le_16(अचिन्हित अक्षर स्थिर *buffer, माप_प्रकार len, u32 crc32);

अटल u32 __attribute__((pure))
	crc32_pclmul_le(u32 crc, अचिन्हित अक्षर स्थिर *p, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक iquotient;
	अचिन्हित पूर्णांक ireमुख्यder;
	अचिन्हित पूर्णांक prealign;

	अगर (len < PCLMUL_MIN_LEN + SCALE_F_MASK || !crypto_simd_usable())
		वापस crc32_le(crc, p, len);

	अगर ((दीर्घ)p & SCALE_F_MASK) अणु
		/* align p to 16 byte */
		prealign = SCALE_F - ((दीर्घ)p & SCALE_F_MASK);

		crc = crc32_le(crc, p, prealign);
		len -= prealign;
		p = (अचिन्हित अक्षर *)(((अचिन्हित दीर्घ)p + SCALE_F_MASK) &
				     ~SCALE_F_MASK);
	पूर्ण
	iquotient = len & (~SCALE_F_MASK);
	ireमुख्यder = len & SCALE_F_MASK;

	kernel_fpu_begin();
	crc = crc32_pclmul_le_16(p, iquotient, crc);
	kernel_fpu_end();

	अगर (ireमुख्यder)
		crc = crc32_le(crc, p + iquotient, ireमुख्यder);

	वापस crc;
पूर्ण

अटल पूर्णांक crc32_pclmul_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	u32 *key = crypto_tfm_ctx(tfm);

	*key = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक crc32_pclmul_setkey(काष्ठा crypto_shash *hash, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	u32 *mctx = crypto_shash_ctx(hash);

	अगर (keylen != माप(u32))
		वापस -EINVAL;
	*mctx = le32_to_cpup((__le32 *)key);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_pclmul_init(काष्ठा shash_desc *desc)
अणु
	u32 *mctx = crypto_shash_ctx(desc->tfm);
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = *mctx;

	वापस 0;
पूर्ण

अटल पूर्णांक crc32_pclmul_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = crc32_pclmul_le(*crcp, data, len);
	वापस 0;
पूर्ण

/* No final XOR 0xFFFFFFFF, like crc32_le */
अटल पूर्णांक __crc32_pclmul_finup(u32 *crcp, स्थिर u8 *data, अचिन्हित पूर्णांक len,
				u8 *out)
अणु
	*(__le32 *)out = cpu_to_le32(crc32_pclmul_le(*crcp, data, len));
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_pclmul_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32_pclmul_finup(shash_desc_ctx(desc), data, len, out);
पूर्ण

अटल पूर्णांक crc32_pclmul_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	u32 *crcp = shash_desc_ctx(desc);

	*(__le32 *)out = cpu_to_le32p(crcp);
	वापस 0;
पूर्ण

अटल पूर्णांक crc32_pclmul_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस __crc32_pclmul_finup(crypto_shash_ctx(desc->tfm), data, len,
				    out);
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.setkey		= crc32_pclmul_setkey,
	.init		= crc32_pclmul_init,
	.update		= crc32_pclmul_update,
	.final		= crc32_pclmul_final,
	.finup		= crc32_pclmul_finup,
	.digest		= crc32_pclmul_digest,
	.descsize	= माप(u32),
	.digestsize	= CHKSUM_DIGEST_SIZE,
	.base		= अणु
			.cra_name		= "crc32",
			.cra_driver_name	= "crc32-pclmul",
			.cra_priority		= 200,
			.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,
			.cra_blocksize		= CHKSUM_BLOCK_SIZE,
			.cra_ctxsize		= माप(u32),
			.cra_module		= THIS_MODULE,
			.cra_init		= crc32_pclmul_cra_init,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id crc32pclmul_cpu_id[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_PCLMULQDQ, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, crc32pclmul_cpu_id);


अटल पूर्णांक __init crc32_pclmul_mod_init(व्योम)
अणु

	अगर (!x86_match_cpu(crc32pclmul_cpu_id)) अणु
		pr_info("PCLMULQDQ-NI instructions are not detected.\n");
		वापस -ENODEV;
	पूर्ण
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास crc32_pclmul_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(crc32_pclmul_mod_init);
module_निकास(crc32_pclmul_mod_fini);

MODULE_AUTHOR("Alexander Boyko <alexander_boyko@xyratex.com>");
MODULE_LICENSE("GPL");

MODULE_ALIAS_CRYPTO("crc32");
MODULE_ALIAS_CRYPTO("crc32-pclmul");
