<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * aes-ce-cipher.c - core AES cipher using ARMv8 Crypto Extensions
 *
 * Copyright (C) 2013 - 2017 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

#समावेश "aes-ce-setkey.h"

MODULE_DESCRIPTION("Synchronous AES cipher using ARMv8 Crypto Extensions");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

काष्ठा aes_block अणु
	u8 b[AES_BLOCK_SIZE];
पूर्ण;

यंत्रlinkage व्योम __aes_ce_encrypt(u32 *rk, u8 *out, स्थिर u8 *in, पूर्णांक rounds);
यंत्रlinkage व्योम __aes_ce_decrypt(u32 *rk, u8 *out, स्थिर u8 *in, पूर्णांक rounds);

यंत्रlinkage u32 __aes_ce_sub(u32 l);
यंत्रlinkage व्योम __aes_ce_invert(काष्ठा aes_block *out,
				स्थिर काष्ठा aes_block *in);

अटल पूर्णांक num_rounds(काष्ठा crypto_aes_ctx *ctx)
अणु
	/*
	 * # of rounds specअगरied by AES:
	 * 128 bit key		10 rounds
	 * 192 bit key		12 rounds
	 * 256 bit key		14 rounds
	 * => n byte key	=> 6 + (n/4) rounds
	 */
	वापस 6 + ctx->key_length / 4;
पूर्ण

अटल व्योम aes_cipher_encrypt(काष्ठा crypto_tfm *tfm, u8 dst[], u8 स्थिर src[])
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (!crypto_simd_usable()) अणु
		aes_encrypt(ctx, dst, src);
		वापस;
	पूर्ण

	kernel_neon_begin();
	__aes_ce_encrypt(ctx->key_enc, dst, src, num_rounds(ctx));
	kernel_neon_end();
पूर्ण

अटल व्योम aes_cipher_decrypt(काष्ठा crypto_tfm *tfm, u8 dst[], u8 स्थिर src[])
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (!crypto_simd_usable()) अणु
		aes_decrypt(ctx, dst, src);
		वापस;
	पूर्ण

	kernel_neon_begin();
	__aes_ce_decrypt(ctx->key_dec, dst, src, num_rounds(ctx));
	kernel_neon_end();
पूर्ण

पूर्णांक ce_aes_expandkey(काष्ठा crypto_aes_ctx *ctx, स्थिर u8 *in_key,
		     अचिन्हित पूर्णांक key_len)
अणु
	/*
	 * The AES key schedule round स्थिरants
	 */
	अटल u8 स्थिर rcon[] = अणु
		0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
	पूर्ण;

	u32 kwords = key_len / माप(u32);
	काष्ठा aes_block *key_enc, *key_dec;
	पूर्णांक i, j;

	अगर (key_len != AES_KEYSIZE_128 &&
	    key_len != AES_KEYSIZE_192 &&
	    key_len != AES_KEYSIZE_256)
		वापस -EINVAL;

	ctx->key_length = key_len;
	क्रम (i = 0; i < kwords; i++)
		ctx->key_enc[i] = get_unaligned_le32(in_key + i * माप(u32));

	kernel_neon_begin();
	क्रम (i = 0; i < माप(rcon); i++) अणु
		u32 *rki = ctx->key_enc + (i * kwords);
		u32 *rko = rki + kwords;

		rko[0] = ror32(__aes_ce_sub(rki[kwords - 1]), 8) ^ rcon[i] ^ rki[0];
		rko[1] = rko[0] ^ rki[1];
		rko[2] = rko[1] ^ rki[2];
		rko[3] = rko[2] ^ rki[3];

		अगर (key_len == AES_KEYSIZE_192) अणु
			अगर (i >= 7)
				अवरोध;
			rko[4] = rko[3] ^ rki[4];
			rko[5] = rko[4] ^ rki[5];
		पूर्ण अन्यथा अगर (key_len == AES_KEYSIZE_256) अणु
			अगर (i >= 6)
				अवरोध;
			rko[4] = __aes_ce_sub(rko[3]) ^ rki[4];
			rko[5] = rko[4] ^ rki[5];
			rko[6] = rko[5] ^ rki[6];
			rko[7] = rko[6] ^ rki[7];
		पूर्ण
	पूर्ण

	/*
	 * Generate the decryption keys क्रम the Equivalent Inverse Cipher.
	 * This involves reversing the order of the round keys, and applying
	 * the Inverse Mix Columns transक्रमmation on all but the first and
	 * the last one.
	 */
	key_enc = (काष्ठा aes_block *)ctx->key_enc;
	key_dec = (काष्ठा aes_block *)ctx->key_dec;
	j = num_rounds(ctx);

	key_dec[0] = key_enc[j];
	क्रम (i = 1, j--; j > 0; i++, j--)
		__aes_ce_invert(key_dec + i, key_enc + j);
	key_dec[i] = key_enc[0];

	kernel_neon_end();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ce_aes_expandkey);

पूर्णांक ce_aes_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		  अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस ce_aes_expandkey(ctx, in_key, key_len);
पूर्ण
EXPORT_SYMBOL(ce_aes_setkey);

अटल काष्ठा crypto_alg aes_alg = अणु
	.cra_name		= "aes",
	.cra_driver_name	= "aes-ce",
	.cra_priority		= 250,
	.cra_flags		= CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		= AES_BLOCK_SIZE,
	.cra_ctxsize		= माप(काष्ठा crypto_aes_ctx),
	.cra_module		= THIS_MODULE,
	.cra_cipher = अणु
		.cia_min_keysize	= AES_MIN_KEY_SIZE,
		.cia_max_keysize	= AES_MAX_KEY_SIZE,
		.cia_setkey		= ce_aes_setkey,
		.cia_encrypt		= aes_cipher_encrypt,
		.cia_decrypt		= aes_cipher_decrypt
	पूर्ण
पूर्ण;

अटल पूर्णांक __init aes_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_alg(&aes_alg);
पूर्ण

अटल व्योम __निकास aes_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&aes_alg);
पूर्ण

module_cpu_feature_match(AES, aes_mod_init);
module_निकास(aes_mod_निकास);
