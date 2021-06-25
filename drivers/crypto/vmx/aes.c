<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES routines supporting VMX inकाष्ठाions on the Power 8
 *
 * Copyright (C) 2015 International Business Machines Inc.
 *
 * Author: Marcelo Henrique Cerri <mhcerri@br.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/crypto.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/simd.h>

#समावेश "aesp8-ppc.h"

काष्ठा p8_aes_ctx अणु
	काष्ठा crypto_cipher *fallback;
	काष्ठा aes_key enc_key;
	काष्ठा aes_key dec_key;
पूर्ण;

अटल पूर्णांक p8_aes_init(काष्ठा crypto_tfm *tfm)
अणु
	स्थिर अक्षर *alg = crypto_tfm_alg_name(tfm);
	काष्ठा crypto_cipher *fallback;
	काष्ठा p8_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	fallback = crypto_alloc_cipher(alg, 0, CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(fallback)) अणु
		prपूर्णांकk(KERN_ERR
		       "Failed to allocate transformation for '%s': %ld\n",
		       alg, PTR_ERR(fallback));
		वापस PTR_ERR(fallback);
	पूर्ण

	crypto_cipher_set_flags(fallback,
				crypto_cipher_get_flags((काष्ठा
							 crypto_cipher *)
							tfm));
	ctx->fallback = fallback;

	वापस 0;
पूर्ण

अटल व्योम p8_aes_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा p8_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (ctx->fallback) अणु
		crypto_मुक्त_cipher(ctx->fallback);
		ctx->fallback = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक p8_aes_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen)
अणु
	पूर्णांक ret;
	काष्ठा p8_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	preempt_disable();
	pagefault_disable();
	enable_kernel_vsx();
	ret = aes_p8_set_encrypt_key(key, keylen * 8, &ctx->enc_key);
	ret |= aes_p8_set_decrypt_key(key, keylen * 8, &ctx->dec_key);
	disable_kernel_vsx();
	pagefault_enable();
	preempt_enable();

	ret |= crypto_cipher_setkey(ctx->fallback, key, keylen);

	वापस ret ? -EINVAL : 0;
पूर्ण

अटल व्योम p8_aes_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा p8_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (!crypto_simd_usable()) अणु
		crypto_cipher_encrypt_one(ctx->fallback, dst, src);
	पूर्ण अन्यथा अणु
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		aes_p8_encrypt(src, dst, &ctx->enc_key);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();
	पूर्ण
पूर्ण

अटल व्योम p8_aes_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा p8_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (!crypto_simd_usable()) अणु
		crypto_cipher_decrypt_one(ctx->fallback, dst, src);
	पूर्ण अन्यथा अणु
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		aes_p8_decrypt(src, dst, &ctx->dec_key);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();
	पूर्ण
पूर्ण

काष्ठा crypto_alg p8_aes_alg = अणु
	.cra_name = "aes",
	.cra_driver_name = "p8_aes",
	.cra_module = THIS_MODULE,
	.cra_priority = 1000,
	.cra_type = शून्य,
	.cra_flags = CRYPTO_ALG_TYPE_CIPHER | CRYPTO_ALG_NEED_FALLBACK,
	.cra_alignmask = 0,
	.cra_blocksize = AES_BLOCK_SIZE,
	.cra_ctxsize = माप(काष्ठा p8_aes_ctx),
	.cra_init = p8_aes_init,
	.cra_निकास = p8_aes_निकास,
	.cra_cipher = अणु
		       .cia_min_keysize = AES_MIN_KEY_SIZE,
		       .cia_max_keysize = AES_MAX_KEY_SIZE,
		       .cia_setkey = p8_aes_setkey,
		       .cia_encrypt = p8_aes_encrypt,
		       .cia_decrypt = p8_aes_decrypt,
	पूर्ण,
पूर्ण;
