<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NHPoly1305 - Nग-almost-ै-universal hash function क्रम Adiantum
 * (AVX2 accelerated version)
 *
 * Copyright 2018 Google LLC
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/nhpoly1305.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम nh_avx2(स्थिर u32 *key, स्थिर u8 *message, माप_प्रकार message_len,
			u8 hash[NH_HASH_BYTES]);

/* wrapper to aव्योम indirect call to assembly, which करोesn't work with CFI */
अटल व्योम _nh_avx2(स्थिर u32 *key, स्थिर u8 *message, माप_प्रकार message_len,
		     __le64 hash[NH_NUM_PASSES])
अणु
	nh_avx2(key, message, message_len, (u8 *)hash);
पूर्ण

अटल पूर्णांक nhpoly1305_avx2_update(काष्ठा shash_desc *desc,
				  स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	अगर (srclen < 64 || !crypto_simd_usable())
		वापस crypto_nhpoly1305_update(desc, src, srclen);

	करो अणु
		अचिन्हित पूर्णांक n = min_t(अचिन्हित पूर्णांक, srclen, SZ_4K);

		kernel_fpu_begin();
		crypto_nhpoly1305_update_helper(desc, src, n, _nh_avx2);
		kernel_fpu_end();
		src += n;
		srclen -= n;
	पूर्ण जबतक (srclen);
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg nhpoly1305_alg = अणु
	.base.cra_name		= "nhpoly1305",
	.base.cra_driver_name	= "nhpoly1305-avx2",
	.base.cra_priority	= 300,
	.base.cra_ctxsize	= माप(काष्ठा nhpoly1305_key),
	.base.cra_module	= THIS_MODULE,
	.digestsize		= POLY1305_DIGEST_SIZE,
	.init			= crypto_nhpoly1305_init,
	.update			= nhpoly1305_avx2_update,
	.final			= crypto_nhpoly1305_final,
	.setkey			= crypto_nhpoly1305_setkey,
	.descsize		= माप(काष्ठा nhpoly1305_state),
पूर्ण;

अटल पूर्णांक __init nhpoly1305_mod_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_AVX2) ||
	    !boot_cpu_has(X86_FEATURE_OSXSAVE))
		वापस -ENODEV;

	वापस crypto_रेजिस्टर_shash(&nhpoly1305_alg);
पूर्ण

अटल व्योम __निकास nhpoly1305_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&nhpoly1305_alg);
पूर्ण

module_init(nhpoly1305_mod_init);
module_निकास(nhpoly1305_mod_निकास);

MODULE_DESCRIPTION("NHPoly1305 Nग-almost-ै-universal hash function (AVX2-accelerated)");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Eric Biggers <ebiggers@google.com>");
MODULE_ALIAS_CRYPTO("nhpoly1305");
MODULE_ALIAS_CRYPTO("nhpoly1305-avx2");
