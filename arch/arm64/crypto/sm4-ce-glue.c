<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <crypto/sm4.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/types.h>

MODULE_ALIAS_CRYPTO("sm4");
MODULE_ALIAS_CRYPTO("sm4-ce");
MODULE_DESCRIPTION("SM4 symmetric cipher using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

यंत्रlinkage व्योम sm4_ce_करो_crypt(स्थिर u32 *rk, व्योम *out, स्थिर व्योम *in);

अटल व्योम sm4_ce_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	स्थिर काष्ठा crypto_sm4_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (!crypto_simd_usable()) अणु
		crypto_sm4_encrypt(tfm, out, in);
	पूर्ण अन्यथा अणु
		kernel_neon_begin();
		sm4_ce_करो_crypt(ctx->rkey_enc, out, in);
		kernel_neon_end();
	पूर्ण
पूर्ण

अटल व्योम sm4_ce_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	स्थिर काष्ठा crypto_sm4_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (!crypto_simd_usable()) अणु
		crypto_sm4_decrypt(tfm, out, in);
	पूर्ण अन्यथा अणु
		kernel_neon_begin();
		sm4_ce_करो_crypt(ctx->rkey_dec, out, in);
		kernel_neon_end();
	पूर्ण
पूर्ण

अटल काष्ठा crypto_alg sm4_ce_alg = अणु
	.cra_name			= "sm4",
	.cra_driver_name		= "sm4-ce",
	.cra_priority			= 200,
	.cra_flags			= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize			= SM4_BLOCK_SIZE,
	.cra_ctxsize			= माप(काष्ठा crypto_sm4_ctx),
	.cra_module			= THIS_MODULE,
	.cra_u.cipher = अणु
		.cia_min_keysize	= SM4_KEY_SIZE,
		.cia_max_keysize	= SM4_KEY_SIZE,
		.cia_setkey		= crypto_sm4_set_key,
		.cia_encrypt		= sm4_ce_encrypt,
		.cia_decrypt		= sm4_ce_decrypt
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sm4_ce_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_alg(&sm4_ce_alg);
पूर्ण

अटल व्योम __निकास sm4_ce_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&sm4_ce_alg);
पूर्ण

module_cpu_feature_match(SM4, sm4_ce_mod_init);
module_निकास(sm4_ce_mod_fini);
