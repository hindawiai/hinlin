<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * Glue code क्रम the SHA1 Secure Hash Algorithm assembler implementation using
 * Supplemental SSE3 inकाष्ठाions.
 *
 * This file is based on sha1_generic.c
 *
 * Copyright (c) Alan Smithee.
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 * Copyright (c) Mathias Krause <minipli@googlemail.com>
 * Copyright (c) Chandramouli Narayanan <mouli@linux.पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha1_base.h>
#समावेश <यंत्र/simd.h>

अटल पूर्णांक sha1_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len, sha1_block_fn *sha1_xक्रमm)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable() ||
	    (sctx->count % SHA1_BLOCK_SIZE) + len < SHA1_BLOCK_SIZE)
		वापस crypto_sha1_update(desc, data, len);

	/*
	 * Make sure काष्ठा sha1_state begins directly with the SHA1
	 * 160-bit पूर्णांकernal state, as this is what the यंत्र functions expect.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा sha1_state, state) != 0);

	kernel_fpu_begin();
	sha1_base_करो_update(desc, data, len, sha1_xक्रमm);
	kernel_fpu_end();

	वापस 0;
पूर्ण

अटल पूर्णांक sha1_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक len, u8 *out, sha1_block_fn *sha1_xक्रमm)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_sha1_finup(desc, data, len, out);

	kernel_fpu_begin();
	अगर (len)
		sha1_base_करो_update(desc, data, len, sha1_xक्रमm);
	sha1_base_करो_finalize(desc, sha1_xक्रमm);
	kernel_fpu_end();

	वापस sha1_base_finish(desc, out);
पूर्ण

यंत्रlinkage व्योम sha1_transक्रमm_ssse3(काष्ठा sha1_state *state,
				     स्थिर u8 *data, पूर्णांक blocks);

अटल पूर्णांक sha1_ssse3_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len)
अणु
	वापस sha1_update(desc, data, len, sha1_transक्रमm_ssse3);
पूर्ण

अटल पूर्णांक sha1_ssse3_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha1_finup(desc, data, len, out, sha1_transक्रमm_ssse3);
पूर्ण

/* Add padding and वापस the message digest. */
अटल पूर्णांक sha1_ssse3_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha1_ssse3_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha1_ssse3_alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_ssse3_update,
	.final		=	sha1_ssse3_final,
	.finup		=	sha1_ssse3_finup,
	.descsize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name =	"sha1-ssse3",
		.cra_priority	=	150,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक रेजिस्टर_sha1_ssse3(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SSSE3))
		वापस crypto_रेजिस्टर_shash(&sha1_ssse3_alg);
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha1_ssse3(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SSSE3))
		crypto_unरेजिस्टर_shash(&sha1_ssse3_alg);
पूर्ण

यंत्रlinkage व्योम sha1_transक्रमm_avx(काष्ठा sha1_state *state,
				   स्थिर u8 *data, पूर्णांक blocks);

अटल पूर्णांक sha1_avx_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len)
अणु
	वापस sha1_update(desc, data, len, sha1_transक्रमm_avx);
पूर्ण

अटल पूर्णांक sha1_avx_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha1_finup(desc, data, len, out, sha1_transक्रमm_avx);
पूर्ण

अटल पूर्णांक sha1_avx_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha1_avx_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha1_avx_alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_avx_update,
	.final		=	sha1_avx_final,
	.finup		=	sha1_avx_finup,
	.descsize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name =	"sha1-avx",
		.cra_priority	=	160,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल bool avx_usable(व्योम)
अणु
	अगर (!cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, शून्य)) अणु
		अगर (boot_cpu_has(X86_FEATURE_AVX))
			pr_info("AVX detected but unusable.\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक रेजिस्टर_sha1_avx(व्योम)
अणु
	अगर (avx_usable())
		वापस crypto_रेजिस्टर_shash(&sha1_avx_alg);
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha1_avx(व्योम)
अणु
	अगर (avx_usable())
		crypto_unरेजिस्टर_shash(&sha1_avx_alg);
पूर्ण

#घोषणा SHA1_AVX2_BLOCK_OPTSIZE	4	/* optimal 4*64 bytes of SHA1 blocks */

यंत्रlinkage व्योम sha1_transक्रमm_avx2(काष्ठा sha1_state *state,
				    स्थिर u8 *data, पूर्णांक blocks);

अटल bool avx2_usable(व्योम)
अणु
	अगर (avx_usable() && boot_cpu_has(X86_FEATURE_AVX2)
		&& boot_cpu_has(X86_FEATURE_BMI1)
		&& boot_cpu_has(X86_FEATURE_BMI2))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम sha1_apply_transक्रमm_avx2(काष्ठा sha1_state *state,
				      स्थिर u8 *data, पूर्णांक blocks)
अणु
	/* Select the optimal transक्रमm based on data block size */
	अगर (blocks >= SHA1_AVX2_BLOCK_OPTSIZE)
		sha1_transक्रमm_avx2(state, data, blocks);
	अन्यथा
		sha1_transक्रमm_avx(state, data, blocks);
पूर्ण

अटल पूर्णांक sha1_avx2_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len)
अणु
	वापस sha1_update(desc, data, len, sha1_apply_transक्रमm_avx2);
पूर्ण

अटल पूर्णांक sha1_avx2_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha1_finup(desc, data, len, out, sha1_apply_transक्रमm_avx2);
पूर्ण

अटल पूर्णांक sha1_avx2_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha1_avx2_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha1_avx2_alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_avx2_update,
	.final		=	sha1_avx2_final,
	.finup		=	sha1_avx2_finup,
	.descsize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name =	"sha1-avx2",
		.cra_priority	=	170,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक रेजिस्टर_sha1_avx2(व्योम)
अणु
	अगर (avx2_usable())
		वापस crypto_रेजिस्टर_shash(&sha1_avx2_alg);
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha1_avx2(व्योम)
अणु
	अगर (avx2_usable())
		crypto_unरेजिस्टर_shash(&sha1_avx2_alg);
पूर्ण

#अगर_घोषित CONFIG_AS_SHA1_NI
यंत्रlinkage व्योम sha1_ni_transक्रमm(काष्ठा sha1_state *digest, स्थिर u8 *data,
				  पूर्णांक rounds);

अटल पूर्णांक sha1_ni_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len)
अणु
	वापस sha1_update(desc, data, len, sha1_ni_transक्रमm);
पूर्ण

अटल पूर्णांक sha1_ni_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha1_finup(desc, data, len, out, sha1_ni_transक्रमm);
पूर्ण

अटल पूर्णांक sha1_ni_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha1_ni_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha1_ni_alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_ni_update,
	.final		=	sha1_ni_final,
	.finup		=	sha1_ni_finup,
	.descsize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name =	"sha1-ni",
		.cra_priority	=	250,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक रेजिस्टर_sha1_ni(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SHA_NI))
		वापस crypto_रेजिस्टर_shash(&sha1_ni_alg);
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha1_ni(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SHA_NI))
		crypto_unरेजिस्टर_shash(&sha1_ni_alg);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक रेजिस्टर_sha1_ni(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_sha1_ni(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init sha1_ssse3_mod_init(व्योम)
अणु
	अगर (रेजिस्टर_sha1_ssse3())
		जाओ fail;

	अगर (रेजिस्टर_sha1_avx()) अणु
		unरेजिस्टर_sha1_ssse3();
		जाओ fail;
	पूर्ण

	अगर (रेजिस्टर_sha1_avx2()) अणु
		unरेजिस्टर_sha1_avx();
		unरेजिस्टर_sha1_ssse3();
		जाओ fail;
	पूर्ण

	अगर (रेजिस्टर_sha1_ni()) अणु
		unरेजिस्टर_sha1_avx2();
		unरेजिस्टर_sha1_avx();
		unरेजिस्टर_sha1_ssse3();
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास sha1_ssse3_mod_fini(व्योम)
अणु
	unरेजिस्टर_sha1_ni();
	unरेजिस्टर_sha1_avx2();
	unरेजिस्टर_sha1_avx();
	unरेजिस्टर_sha1_ssse3();
पूर्ण

module_init(sha1_ssse3_mod_init);
module_निकास(sha1_ssse3_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm, Supplemental SSE3 accelerated");

MODULE_ALIAS_CRYPTO("sha1");
MODULE_ALIAS_CRYPTO("sha1-ssse3");
MODULE_ALIAS_CRYPTO("sha1-avx");
MODULE_ALIAS_CRYPTO("sha1-avx2");
#अगर_घोषित CONFIG_AS_SHA1_NI
MODULE_ALIAS_CRYPTO("sha1-ni");
#पूर्ण_अगर
