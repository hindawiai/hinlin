<शैली गुरु>
/*
 * Cryptographic API.
 *
 * Glue code क्रम the SHA256 Secure Hash Algorithm assembler
 * implementation using supplemental SSE3 / AVX / AVX2 inकाष्ठाions.
 *
 * This file is based on sha256_generic.c
 *
 * Copyright (C) 2013 Intel Corporation.
 *
 * Author:
 *     Tim Chen <tim.c.chen@linux.पूर्णांकel.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha256_base.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम sha256_transक्रमm_ssse3(काष्ठा sha256_state *state,
				       स्थिर u8 *data, पूर्णांक blocks);

अटल पूर्णांक _sha256_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			  अचिन्हित पूर्णांक len, sha256_block_fn *sha256_xक्रमm)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable() ||
	    (sctx->count % SHA256_BLOCK_SIZE) + len < SHA256_BLOCK_SIZE)
		वापस crypto_sha256_update(desc, data, len);

	/*
	 * Make sure काष्ठा sha256_state begins directly with the SHA256
	 * 256-bit पूर्णांकernal state, as this is what the यंत्र functions expect.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा sha256_state, state) != 0);

	kernel_fpu_begin();
	sha256_base_करो_update(desc, data, len, sha256_xक्रमm);
	kernel_fpu_end();

	वापस 0;
पूर्ण

अटल पूर्णांक sha256_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
	      अचिन्हित पूर्णांक len, u8 *out, sha256_block_fn *sha256_xक्रमm)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_sha256_finup(desc, data, len, out);

	kernel_fpu_begin();
	अगर (len)
		sha256_base_करो_update(desc, data, len, sha256_xक्रमm);
	sha256_base_करो_finalize(desc, sha256_xक्रमm);
	kernel_fpu_end();

	वापस sha256_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha256_ssse3_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len)
अणु
	वापस _sha256_update(desc, data, len, sha256_transक्रमm_ssse3);
पूर्ण

अटल पूर्णांक sha256_ssse3_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
	      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha256_finup(desc, data, len, out, sha256_transक्रमm_ssse3);
पूर्ण

/* Add padding and वापस the message digest. */
अटल पूर्णांक sha256_ssse3_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha256_ssse3_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha256_ssse3_algs[] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_ssse3_update,
	.final		=	sha256_ssse3_final,
	.finup		=	sha256_ssse3_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name =	"sha256-ssse3",
		.cra_priority	=	150,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_ssse3_update,
	.final		=	sha256_ssse3_final,
	.finup		=	sha256_ssse3_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name =	"sha224-ssse3",
		.cra_priority	=	150,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक रेजिस्टर_sha256_ssse3(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SSSE3))
		वापस crypto_रेजिस्टर_shashes(sha256_ssse3_algs,
				ARRAY_SIZE(sha256_ssse3_algs));
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha256_ssse3(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SSSE3))
		crypto_unरेजिस्टर_shashes(sha256_ssse3_algs,
				ARRAY_SIZE(sha256_ssse3_algs));
पूर्ण

यंत्रlinkage व्योम sha256_transक्रमm_avx(काष्ठा sha256_state *state,
				     स्थिर u8 *data, पूर्णांक blocks);

अटल पूर्णांक sha256_avx_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len)
अणु
	वापस _sha256_update(desc, data, len, sha256_transक्रमm_avx);
पूर्ण

अटल पूर्णांक sha256_avx_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha256_finup(desc, data, len, out, sha256_transक्रमm_avx);
पूर्ण

अटल पूर्णांक sha256_avx_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha256_avx_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha256_avx_algs[] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_avx_update,
	.final		=	sha256_avx_final,
	.finup		=	sha256_avx_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name =	"sha256-avx",
		.cra_priority	=	160,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_avx_update,
	.final		=	sha256_avx_final,
	.finup		=	sha256_avx_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name =	"sha224-avx",
		.cra_priority	=	160,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल bool avx_usable(व्योम)
अणु
	अगर (!cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, शून्य)) अणु
		अगर (boot_cpu_has(X86_FEATURE_AVX))
			pr_info("AVX detected but unusable.\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक रेजिस्टर_sha256_avx(व्योम)
अणु
	अगर (avx_usable())
		वापस crypto_रेजिस्टर_shashes(sha256_avx_algs,
				ARRAY_SIZE(sha256_avx_algs));
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha256_avx(व्योम)
अणु
	अगर (avx_usable())
		crypto_unरेजिस्टर_shashes(sha256_avx_algs,
				ARRAY_SIZE(sha256_avx_algs));
पूर्ण

यंत्रlinkage व्योम sha256_transक्रमm_rorx(काष्ठा sha256_state *state,
				      स्थिर u8 *data, पूर्णांक blocks);

अटल पूर्णांक sha256_avx2_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len)
अणु
	वापस _sha256_update(desc, data, len, sha256_transक्रमm_rorx);
पूर्ण

अटल पूर्णांक sha256_avx2_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha256_finup(desc, data, len, out, sha256_transक्रमm_rorx);
पूर्ण

अटल पूर्णांक sha256_avx2_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha256_avx2_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha256_avx2_algs[] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_avx2_update,
	.final		=	sha256_avx2_final,
	.finup		=	sha256_avx2_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name =	"sha256-avx2",
		.cra_priority	=	170,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_avx2_update,
	.final		=	sha256_avx2_final,
	.finup		=	sha256_avx2_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name =	"sha224-avx2",
		.cra_priority	=	170,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल bool avx2_usable(व्योम)
अणु
	अगर (avx_usable() && boot_cpu_has(X86_FEATURE_AVX2) &&
		    boot_cpu_has(X86_FEATURE_BMI2))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक रेजिस्टर_sha256_avx2(व्योम)
अणु
	अगर (avx2_usable())
		वापस crypto_रेजिस्टर_shashes(sha256_avx2_algs,
				ARRAY_SIZE(sha256_avx2_algs));
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha256_avx2(व्योम)
अणु
	अगर (avx2_usable())
		crypto_unरेजिस्टर_shashes(sha256_avx2_algs,
				ARRAY_SIZE(sha256_avx2_algs));
पूर्ण

#अगर_घोषित CONFIG_AS_SHA256_NI
यंत्रlinkage व्योम sha256_ni_transक्रमm(काष्ठा sha256_state *digest,
				    स्थिर u8 *data, पूर्णांक rounds);

अटल पूर्णांक sha256_ni_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len)
अणु
	वापस _sha256_update(desc, data, len, sha256_ni_transक्रमm);
पूर्ण

अटल पूर्णांक sha256_ni_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha256_finup(desc, data, len, out, sha256_ni_transक्रमm);
पूर्ण

अटल पूर्णांक sha256_ni_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha256_ni_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha256_ni_algs[] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_ni_update,
	.final		=	sha256_ni_final,
	.finup		=	sha256_ni_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name =	"sha256-ni",
		.cra_priority	=	250,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_ni_update,
	.final		=	sha256_ni_final,
	.finup		=	sha256_ni_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name =	"sha224-ni",
		.cra_priority	=	250,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक रेजिस्टर_sha256_ni(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SHA_NI))
		वापस crypto_रेजिस्टर_shashes(sha256_ni_algs,
				ARRAY_SIZE(sha256_ni_algs));
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha256_ni(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SHA_NI))
		crypto_unरेजिस्टर_shashes(sha256_ni_algs,
				ARRAY_SIZE(sha256_ni_algs));
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक रेजिस्टर_sha256_ni(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_sha256_ni(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init sha256_ssse3_mod_init(व्योम)
अणु
	अगर (रेजिस्टर_sha256_ssse3())
		जाओ fail;

	अगर (रेजिस्टर_sha256_avx()) अणु
		unरेजिस्टर_sha256_ssse3();
		जाओ fail;
	पूर्ण

	अगर (रेजिस्टर_sha256_avx2()) अणु
		unरेजिस्टर_sha256_avx();
		unरेजिस्टर_sha256_ssse3();
		जाओ fail;
	पूर्ण

	अगर (रेजिस्टर_sha256_ni()) अणु
		unरेजिस्टर_sha256_avx2();
		unरेजिस्टर_sha256_avx();
		unरेजिस्टर_sha256_ssse3();
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास sha256_ssse3_mod_fini(व्योम)
अणु
	unरेजिस्टर_sha256_ni();
	unरेजिस्टर_sha256_avx2();
	unरेजिस्टर_sha256_avx();
	unरेजिस्टर_sha256_ssse3();
पूर्ण

module_init(sha256_ssse3_mod_init);
module_निकास(sha256_ssse3_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA256 Secure Hash Algorithm, Supplemental SSE3 accelerated");

MODULE_ALIAS_CRYPTO("sha256");
MODULE_ALIAS_CRYPTO("sha256-ssse3");
MODULE_ALIAS_CRYPTO("sha256-avx");
MODULE_ALIAS_CRYPTO("sha256-avx2");
MODULE_ALIAS_CRYPTO("sha224");
MODULE_ALIAS_CRYPTO("sha224-ssse3");
MODULE_ALIAS_CRYPTO("sha224-avx");
MODULE_ALIAS_CRYPTO("sha224-avx2");
#अगर_घोषित CONFIG_AS_SHA256_NI
MODULE_ALIAS_CRYPTO("sha256-ni");
MODULE_ALIAS_CRYPTO("sha224-ni");
#पूर्ण_अगर
