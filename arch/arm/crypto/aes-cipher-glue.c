<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Scalar AES core transक्रमm
 *
 * Copyright (C) 2017 Linaro Ltd.
 * Author: Ard Biesheuvel <ard.biesheuvel@linaro.org>
 */

#समावेश <crypto/aes.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

यंत्रlinkage व्योम __aes_arm_encrypt(u32 *rk, पूर्णांक rounds, स्थिर u8 *in, u8 *out);
यंत्रlinkage व्योम __aes_arm_decrypt(u32 *rk, पूर्णांक rounds, स्थिर u8 *in, u8 *out);

अटल व्योम aes_arm_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक rounds = 6 + ctx->key_length / 4;

	__aes_arm_encrypt(ctx->key_enc, rounds, in, out);
पूर्ण

अटल व्योम aes_arm_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	पूर्णांक rounds = 6 + ctx->key_length / 4;

	__aes_arm_decrypt(ctx->key_dec, rounds, in, out);
पूर्ण

अटल काष्ठा crypto_alg aes_alg = अणु
	.cra_name			= "aes",
	.cra_driver_name		= "aes-arm",
	.cra_priority			= 200,
	.cra_flags			= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize			= AES_BLOCK_SIZE,
	.cra_ctxsize			= माप(काष्ठा crypto_aes_ctx),
	.cra_module			= THIS_MODULE,

	.cra_cipher.cia_min_keysize	= AES_MIN_KEY_SIZE,
	.cra_cipher.cia_max_keysize	= AES_MAX_KEY_SIZE,
	.cra_cipher.cia_setkey		= crypto_aes_set_key,
	.cra_cipher.cia_encrypt		= aes_arm_encrypt,
	.cra_cipher.cia_decrypt		= aes_arm_decrypt,

#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	.cra_alignmask			= 3,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init aes_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_alg(&aes_alg);
पूर्ण

अटल व्योम __निकास aes_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&aes_alg);
पूर्ण

module_init(aes_init);
module_निकास(aes_fini);

MODULE_DESCRIPTION("Scalar AES cipher for ARM");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("aes");
