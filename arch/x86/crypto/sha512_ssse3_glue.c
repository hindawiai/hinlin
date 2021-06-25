<शैली गुरु>
/*
 * Cryptographic API.
 *
 * Glue code क्रम the SHA512 Secure Hash Algorithm assembler
 * implementation using supplemental SSE3 / AVX / AVX2 inकाष्ठाions.
 *
 * This file is based on sha512_generic.c
 *
 * Copyright (C) 2013 Intel Corporation
 * Author: Tim Chen <tim.c.chen@linux.पूर्णांकel.com>
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
 *
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha512_base.h>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम sha512_transक्रमm_ssse3(काष्ठा sha512_state *state,
				       स्थिर u8 *data, पूर्णांक blocks);

अटल पूर्णांक sha512_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len, sha512_block_fn *sha512_xक्रमm)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable() ||
	    (sctx->count[0] % SHA512_BLOCK_SIZE) + len < SHA512_BLOCK_SIZE)
		वापस crypto_sha512_update(desc, data, len);

	/*
	 * Make sure काष्ठा sha512_state begins directly with the SHA512
	 * 512-bit पूर्णांकernal state, as this is what the यंत्र functions expect.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा sha512_state, state) != 0);

	kernel_fpu_begin();
	sha512_base_करो_update(desc, data, len, sha512_xक्रमm);
	kernel_fpu_end();

	वापस 0;
पूर्ण

अटल पूर्णांक sha512_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
	      अचिन्हित पूर्णांक len, u8 *out, sha512_block_fn *sha512_xक्रमm)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_sha512_finup(desc, data, len, out);

	kernel_fpu_begin();
	अगर (len)
		sha512_base_करो_update(desc, data, len, sha512_xक्रमm);
	sha512_base_करो_finalize(desc, sha512_xक्रमm);
	kernel_fpu_end();

	वापस sha512_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha512_ssse3_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len)
अणु
	वापस sha512_update(desc, data, len, sha512_transक्रमm_ssse3);
पूर्ण

अटल पूर्णांक sha512_ssse3_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
	      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha512_finup(desc, data, len, out, sha512_transक्रमm_ssse3);
पूर्ण

/* Add padding and वापस the message digest. */
अटल पूर्णांक sha512_ssse3_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha512_ssse3_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha512_ssse3_algs[] = अणु अणु
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_base_init,
	.update		=	sha512_ssse3_update,
	.final		=	sha512_ssse3_final,
	.finup		=	sha512_ssse3_finup,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha512",
		.cra_driver_name =	"sha512-ssse3",
		.cra_priority	=	150,
		.cra_blocksize	=	SHA512_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण,  अणु
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_base_init,
	.update		=	sha512_ssse3_update,
	.final		=	sha512_ssse3_final,
	.finup		=	sha512_ssse3_finup,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha384",
		.cra_driver_name =	"sha384-ssse3",
		.cra_priority	=	150,
		.cra_blocksize	=	SHA384_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक रेजिस्टर_sha512_ssse3(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SSSE3))
		वापस crypto_रेजिस्टर_shashes(sha512_ssse3_algs,
			ARRAY_SIZE(sha512_ssse3_algs));
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha512_ssse3(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_SSSE3))
		crypto_unरेजिस्टर_shashes(sha512_ssse3_algs,
			ARRAY_SIZE(sha512_ssse3_algs));
पूर्ण

यंत्रlinkage व्योम sha512_transक्रमm_avx(काष्ठा sha512_state *state,
				     स्थिर u8 *data, पूर्णांक blocks);
अटल bool avx_usable(व्योम)
अणु
	अगर (!cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, शून्य)) अणु
		अगर (boot_cpu_has(X86_FEATURE_AVX))
			pr_info("AVX detected but unusable.\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक sha512_avx_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len)
अणु
	वापस sha512_update(desc, data, len, sha512_transक्रमm_avx);
पूर्ण

अटल पूर्णांक sha512_avx_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
	      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha512_finup(desc, data, len, out, sha512_transक्रमm_avx);
पूर्ण

/* Add padding and वापस the message digest. */
अटल पूर्णांक sha512_avx_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha512_avx_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha512_avx_algs[] = अणु अणु
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_base_init,
	.update		=	sha512_avx_update,
	.final		=	sha512_avx_final,
	.finup		=	sha512_avx_finup,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha512",
		.cra_driver_name =	"sha512-avx",
		.cra_priority	=	160,
		.cra_blocksize	=	SHA512_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण,  अणु
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_base_init,
	.update		=	sha512_avx_update,
	.final		=	sha512_avx_final,
	.finup		=	sha512_avx_finup,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha384",
		.cra_driver_name =	"sha384-avx",
		.cra_priority	=	160,
		.cra_blocksize	=	SHA384_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक रेजिस्टर_sha512_avx(व्योम)
अणु
	अगर (avx_usable())
		वापस crypto_रेजिस्टर_shashes(sha512_avx_algs,
			ARRAY_SIZE(sha512_avx_algs));
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha512_avx(व्योम)
अणु
	अगर (avx_usable())
		crypto_unरेजिस्टर_shashes(sha512_avx_algs,
			ARRAY_SIZE(sha512_avx_algs));
पूर्ण

यंत्रlinkage व्योम sha512_transक्रमm_rorx(काष्ठा sha512_state *state,
				      स्थिर u8 *data, पूर्णांक blocks);

अटल पूर्णांक sha512_avx2_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len)
अणु
	वापस sha512_update(desc, data, len, sha512_transक्रमm_rorx);
पूर्ण

अटल पूर्णांक sha512_avx2_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
	      अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस sha512_finup(desc, data, len, out, sha512_transक्रमm_rorx);
पूर्ण

/* Add padding and वापस the message digest. */
अटल पूर्णांक sha512_avx2_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha512_avx2_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg sha512_avx2_algs[] = अणु अणु
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_base_init,
	.update		=	sha512_avx2_update,
	.final		=	sha512_avx2_final,
	.finup		=	sha512_avx2_finup,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha512",
		.cra_driver_name =	"sha512-avx2",
		.cra_priority	=	170,
		.cra_blocksize	=	SHA512_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण,  अणु
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_base_init,
	.update		=	sha512_avx2_update,
	.final		=	sha512_avx2_final,
	.finup		=	sha512_avx2_finup,
	.descsize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha384",
		.cra_driver_name =	"sha384-avx2",
		.cra_priority	=	170,
		.cra_blocksize	=	SHA384_BLOCK_SIZE,
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

अटल पूर्णांक रेजिस्टर_sha512_avx2(व्योम)
अणु
	अगर (avx2_usable())
		वापस crypto_रेजिस्टर_shashes(sha512_avx2_algs,
			ARRAY_SIZE(sha512_avx2_algs));
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_sha512_avx2(व्योम)
अणु
	अगर (avx2_usable())
		crypto_unरेजिस्टर_shashes(sha512_avx2_algs,
			ARRAY_SIZE(sha512_avx2_algs));
पूर्ण

अटल पूर्णांक __init sha512_ssse3_mod_init(व्योम)
अणु

	अगर (रेजिस्टर_sha512_ssse3())
		जाओ fail;

	अगर (रेजिस्टर_sha512_avx()) अणु
		unरेजिस्टर_sha512_ssse3();
		जाओ fail;
	पूर्ण

	अगर (रेजिस्टर_sha512_avx2()) अणु
		unरेजिस्टर_sha512_avx();
		unरेजिस्टर_sha512_ssse3();
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास sha512_ssse3_mod_fini(व्योम)
अणु
	unरेजिस्टर_sha512_avx2();
	unरेजिस्टर_sha512_avx();
	unरेजिस्टर_sha512_ssse3();
पूर्ण

module_init(sha512_ssse3_mod_init);
module_निकास(sha512_ssse3_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA512 Secure Hash Algorithm, Supplemental SSE3 accelerated");

MODULE_ALIAS_CRYPTO("sha512");
MODULE_ALIAS_CRYPTO("sha512-ssse3");
MODULE_ALIAS_CRYPTO("sha512-avx");
MODULE_ALIAS_CRYPTO("sha512-avx2");
MODULE_ALIAS_CRYPTO("sha384");
MODULE_ALIAS_CRYPTO("sha384-ssse3");
MODULE_ALIAS_CRYPTO("sha384-avx");
MODULE_ALIAS_CRYPTO("sha384-avx2");
