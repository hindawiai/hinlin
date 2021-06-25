<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Scalar fixed समय AES core transक्रमm
 *
 * Copyright (C) 2017 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <crypto/aes.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

अटल पूर्णांक aesti_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
			 अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस aes_expandkey(ctx, in_key, key_len);
पूर्ण

अटल व्योम aesti_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	स्थिर काष्ठा crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	अचिन्हित दीर्घ flags;

	/*
	 * Temporarily disable पूर्णांकerrupts to aव्योम races where cachelines are
	 * evicted when the CPU is पूर्णांकerrupted to करो something अन्यथा.
	 */
	local_irq_save(flags);

	aes_encrypt(ctx, out, in);

	local_irq_restore(flags);
पूर्ण

अटल व्योम aesti_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	स्थिर काष्ठा crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	अचिन्हित दीर्घ flags;

	/*
	 * Temporarily disable पूर्णांकerrupts to aव्योम races where cachelines are
	 * evicted when the CPU is पूर्णांकerrupted to करो something अन्यथा.
	 */
	local_irq_save(flags);

	aes_decrypt(ctx, out, in);

	local_irq_restore(flags);
पूर्ण

अटल काष्ठा crypto_alg aes_alg = अणु
	.cra_name			= "aes",
	.cra_driver_name		= "aes-fixed-time",
	.cra_priority			= 100 + 1,
	.cra_flags			= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize			= AES_BLOCK_SIZE,
	.cra_ctxsize			= माप(काष्ठा crypto_aes_ctx),
	.cra_module			= THIS_MODULE,

	.cra_cipher.cia_min_keysize	= AES_MIN_KEY_SIZE,
	.cra_cipher.cia_max_keysize	= AES_MAX_KEY_SIZE,
	.cra_cipher.cia_setkey		= aesti_set_key,
	.cra_cipher.cia_encrypt		= aesti_encrypt,
	.cra_cipher.cia_decrypt		= aesti_decrypt
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

MODULE_DESCRIPTION("Generic fixed time AES");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
