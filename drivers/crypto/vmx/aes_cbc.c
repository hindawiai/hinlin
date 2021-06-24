<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES CBC routines supporting VMX inकाष्ठाions on the Power 8
 *
 * Copyright (C) 2015 International Business Machines Inc.
 *
 * Author: Marcelo Henrique Cerri <mhcerri@br.ibm.com>
 */

#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#समावेश "aesp8-ppc.h"

काष्ठा p8_aes_cbc_ctx अणु
	काष्ठा crypto_skcipher *fallback;
	काष्ठा aes_key enc_key;
	काष्ठा aes_key dec_key;
पूर्ण;

अटल पूर्णांक p8_aes_cbc_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा p8_aes_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *fallback;

	fallback = crypto_alloc_skcipher("cbc(aes)", 0,
					 CRYPTO_ALG_NEED_FALLBACK |
					 CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(fallback)) अणु
		pr_err("Failed to allocate cbc(aes) fallback: %ld\n",
		       PTR_ERR(fallback));
		वापस PTR_ERR(fallback);
	पूर्ण

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा skcipher_request) +
				    crypto_skcipher_reqsize(fallback));
	ctx->fallback = fallback;
	वापस 0;
पूर्ण

अटल व्योम p8_aes_cbc_निकास(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा p8_aes_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(ctx->fallback);
पूर्ण

अटल पूर्णांक p8_aes_cbc_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा p8_aes_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक ret;

	preempt_disable();
	pagefault_disable();
	enable_kernel_vsx();
	ret = aes_p8_set_encrypt_key(key, keylen * 8, &ctx->enc_key);
	ret |= aes_p8_set_decrypt_key(key, keylen * 8, &ctx->dec_key);
	disable_kernel_vsx();
	pagefault_enable();
	preempt_enable();

	ret |= crypto_skcipher_setkey(ctx->fallback, key, keylen);

	वापस ret ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक p8_aes_cbc_crypt(काष्ठा skcipher_request *req, पूर्णांक enc)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	स्थिर काष्ठा p8_aes_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक ret;

	अगर (!crypto_simd_usable()) अणु
		काष्ठा skcipher_request *subreq = skcipher_request_ctx(req);

		*subreq = *req;
		skcipher_request_set_tfm(subreq, ctx->fallback);
		वापस enc ? crypto_skcipher_encrypt(subreq) :
			     crypto_skcipher_decrypt(subreq);
	पूर्ण

	ret = skcipher_walk_virt(&walk, req, false);
	जबतक ((nbytes = walk.nbytes) != 0) अणु
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		aes_p8_cbc_encrypt(walk.src.virt.addr,
				   walk.dst.virt.addr,
				   round_करोwn(nbytes, AES_BLOCK_SIZE),
				   enc ? &ctx->enc_key : &ctx->dec_key,
				   walk.iv, enc);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();

		ret = skcipher_walk_करोne(&walk, nbytes % AES_BLOCK_SIZE);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक p8_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस p8_aes_cbc_crypt(req, 1);
पूर्ण

अटल पूर्णांक p8_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस p8_aes_cbc_crypt(req, 0);
पूर्ण

काष्ठा skcipher_alg p8_aes_cbc_alg = अणु
	.base.cra_name = "cbc(aes)",
	.base.cra_driver_name = "p8_aes_cbc",
	.base.cra_module = THIS_MODULE,
	.base.cra_priority = 2000,
	.base.cra_flags = CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize = AES_BLOCK_SIZE,
	.base.cra_ctxsize = माप(काष्ठा p8_aes_cbc_ctx),
	.setkey = p8_aes_cbc_setkey,
	.encrypt = p8_aes_cbc_encrypt,
	.decrypt = p8_aes_cbc_decrypt,
	.init = p8_aes_cbc_init,
	.निकास = p8_aes_cbc_निकास,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BLOCK_SIZE,
पूर्ण;
