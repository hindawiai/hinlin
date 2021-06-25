<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * SM4 Cipher Algorithm.
 *
 * Copyright (C) 2018 ARM Limited or its affiliates.
 * All rights reserved.
 */

#समावेश <crypto/sm4.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crypto.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

अटल स्थिर u32 fk[4] = अणु
	0xa3b1bac6, 0x56aa3350, 0x677d9197, 0xb27022dc
पूर्ण;

अटल स्थिर u8 sbox[256] = अणु
	0xd6, 0x90, 0xe9, 0xfe, 0xcc, 0xe1, 0x3d, 0xb7,
	0x16, 0xb6, 0x14, 0xc2, 0x28, 0xfb, 0x2c, 0x05,
	0x2b, 0x67, 0x9a, 0x76, 0x2a, 0xbe, 0x04, 0xc3,
	0xaa, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99,
	0x9c, 0x42, 0x50, 0xf4, 0x91, 0xef, 0x98, 0x7a,
	0x33, 0x54, 0x0b, 0x43, 0xed, 0xcf, 0xac, 0x62,
	0xe4, 0xb3, 0x1c, 0xa9, 0xc9, 0x08, 0xe8, 0x95,
	0x80, 0xdf, 0x94, 0xfa, 0x75, 0x8f, 0x3f, 0xa6,
	0x47, 0x07, 0xa7, 0xfc, 0xf3, 0x73, 0x17, 0xba,
	0x83, 0x59, 0x3c, 0x19, 0xe6, 0x85, 0x4f, 0xa8,
	0x68, 0x6b, 0x81, 0xb2, 0x71, 0x64, 0xda, 0x8b,
	0xf8, 0xeb, 0x0f, 0x4b, 0x70, 0x56, 0x9d, 0x35,
	0x1e, 0x24, 0x0e, 0x5e, 0x63, 0x58, 0xd1, 0xa2,
	0x25, 0x22, 0x7c, 0x3b, 0x01, 0x21, 0x78, 0x87,
	0xd4, 0x00, 0x46, 0x57, 0x9f, 0xd3, 0x27, 0x52,
	0x4c, 0x36, 0x02, 0xe7, 0xa0, 0xc4, 0xc8, 0x9e,
	0xea, 0xbf, 0x8a, 0xd2, 0x40, 0xc7, 0x38, 0xb5,
	0xa3, 0xf7, 0xf2, 0xce, 0xf9, 0x61, 0x15, 0xa1,
	0xe0, 0xae, 0x5d, 0xa4, 0x9b, 0x34, 0x1a, 0x55,
	0xad, 0x93, 0x32, 0x30, 0xf5, 0x8c, 0xb1, 0xe3,
	0x1d, 0xf6, 0xe2, 0x2e, 0x82, 0x66, 0xca, 0x60,
	0xc0, 0x29, 0x23, 0xab, 0x0d, 0x53, 0x4e, 0x6f,
	0xd5, 0xdb, 0x37, 0x45, 0xde, 0xfd, 0x8e, 0x2f,
	0x03, 0xff, 0x6a, 0x72, 0x6d, 0x6c, 0x5b, 0x51,
	0x8d, 0x1b, 0xaf, 0x92, 0xbb, 0xdd, 0xbc, 0x7f,
	0x11, 0xd9, 0x5c, 0x41, 0x1f, 0x10, 0x5a, 0xd8,
	0x0a, 0xc1, 0x31, 0x88, 0xa5, 0xcd, 0x7b, 0xbd,
	0x2d, 0x74, 0xd0, 0x12, 0xb8, 0xe5, 0xb4, 0xb0,
	0x89, 0x69, 0x97, 0x4a, 0x0c, 0x96, 0x77, 0x7e,
	0x65, 0xb9, 0xf1, 0x09, 0xc5, 0x6e, 0xc6, 0x84,
	0x18, 0xf0, 0x7d, 0xec, 0x3a, 0xdc, 0x4d, 0x20,
	0x79, 0xee, 0x5f, 0x3e, 0xd7, 0xcb, 0x39, 0x48
पूर्ण;

अटल स्थिर u32 ck[] = अणु
	0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269,
	0x70777e85, 0x8c939aa1, 0xa8afb6bd, 0xc4cbd2d9,
	0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249,
	0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9,
	0xc0c7ced5, 0xdce3eaf1, 0xf8ff060d, 0x141b2229,
	0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
	0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209,
	0x10171e25, 0x2c333a41, 0x484f565d, 0x646b7279
पूर्ण;

अटल u32 sm4_t_non_lin_sub(u32 x)
अणु
	पूर्णांक i;
	u8 *b = (u8 *)&x;

	क्रम (i = 0; i < 4; ++i)
		b[i] = sbox[b[i]];

	वापस x;
पूर्ण

अटल u32 sm4_key_lin_sub(u32 x)
अणु
	वापस x ^ rol32(x, 13) ^ rol32(x, 23);

पूर्ण

अटल u32 sm4_enc_lin_sub(u32 x)
अणु
	वापस x ^ rol32(x, 2) ^ rol32(x, 10) ^ rol32(x, 18) ^ rol32(x, 24);
पूर्ण

अटल u32 sm4_key_sub(u32 x)
अणु
	वापस sm4_key_lin_sub(sm4_t_non_lin_sub(x));
पूर्ण

अटल u32 sm4_enc_sub(u32 x)
अणु
	वापस sm4_enc_lin_sub(sm4_t_non_lin_sub(x));
पूर्ण

अटल u32 sm4_round(स्थिर u32 *x, स्थिर u32 rk)
अणु
	वापस x[0] ^ sm4_enc_sub(x[1] ^ x[2] ^ x[3] ^ rk);
पूर्ण


/**
 * crypto_sm4_expand_key - Expands the SM4 key as described in GB/T 32907-2016
 * @ctx:	The location where the computed key will be stored.
 * @in_key:	The supplied key.
 * @key_len:	The length of the supplied key.
 *
 * Returns 0 on success. The function fails only अगर an invalid key size (or
 * poपूर्णांकer) is supplied.
 */
पूर्णांक crypto_sm4_expand_key(काष्ठा crypto_sm4_ctx *ctx, स्थिर u8 *in_key,
			  अचिन्हित पूर्णांक key_len)
अणु
	u32 rk[4], t;
	स्थिर u32 *key = (u32 *)in_key;
	पूर्णांक i;

	अगर (key_len != SM4_KEY_SIZE)
		वापस -EINVAL;

	क्रम (i = 0; i < 4; ++i)
		rk[i] = get_unaligned_be32(&key[i]) ^ fk[i];

	क्रम (i = 0; i < 32; ++i) अणु
		t = rk[0] ^ sm4_key_sub(rk[1] ^ rk[2] ^ rk[3] ^ ck[i]);
		ctx->rkey_enc[i] = t;
		rk[0] = rk[1];
		rk[1] = rk[2];
		rk[2] = rk[3];
		rk[3] = t;
	पूर्ण

	क्रम (i = 0; i < 32; ++i)
		ctx->rkey_dec[i] = ctx->rkey_enc[31 - i];

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_sm4_expand_key);

/**
 * crypto_sm4_set_key - Set the SM4 key.
 * @tfm:	The %crypto_tfm that is used in the context.
 * @in_key:	The input key.
 * @key_len:	The size of the key.
 *
 * This function uses crypto_sm4_expand_key() to expand the key.
 * &crypto_sm4_ctx _must_ be the निजी data embedded in @tfm which is
 * retrieved with crypto_tfm_ctx().
 *
 * Return: 0 on success; -EINVAL on failure (only happens क्रम bad key lengths)
 */
पूर्णांक crypto_sm4_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा crypto_sm4_ctx *ctx = crypto_tfm_ctx(tfm);

	वापस crypto_sm4_expand_key(ctx, in_key, key_len);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_sm4_set_key);

अटल व्योम sm4_करो_crypt(स्थिर u32 *rk, u32 *out, स्थिर u32 *in)
अणु
	u32 x[4], i, t;

	क्रम (i = 0; i < 4; ++i)
		x[i] = get_unaligned_be32(&in[i]);

	क्रम (i = 0; i < 32; ++i) अणु
		t = sm4_round(x, rk[i]);
		x[0] = x[1];
		x[1] = x[2];
		x[2] = x[3];
		x[3] = t;
	पूर्ण

	क्रम (i = 0; i < 4; ++i)
		put_unaligned_be32(x[3 - i], &out[i]);
पूर्ण

/* encrypt a block of text */

व्योम crypto_sm4_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	स्थिर काष्ठा crypto_sm4_ctx *ctx = crypto_tfm_ctx(tfm);

	sm4_करो_crypt(ctx->rkey_enc, (u32 *)out, (u32 *)in);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_sm4_encrypt);

/* decrypt a block of text */

व्योम crypto_sm4_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in)
अणु
	स्थिर काष्ठा crypto_sm4_ctx *ctx = crypto_tfm_ctx(tfm);

	sm4_करो_crypt(ctx->rkey_dec, (u32 *)out, (u32 *)in);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_sm4_decrypt);

अटल काष्ठा crypto_alg sm4_alg = अणु
	.cra_name		=	"sm4",
	.cra_driver_name	=	"sm4-generic",
	.cra_priority		=	100,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	SM4_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा crypto_sm4_ctx),
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु
		.cipher = अणु
			.cia_min_keysize	=	SM4_KEY_SIZE,
			.cia_max_keysize	=	SM4_KEY_SIZE,
			.cia_setkey		=	crypto_sm4_set_key,
			.cia_encrypt		=	crypto_sm4_encrypt,
			.cia_decrypt		=	crypto_sm4_decrypt
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sm4_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_alg(&sm4_alg);
पूर्ण

अटल व्योम __निकास sm4_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&sm4_alg);
पूर्ण

subsys_initcall(sm4_init);
module_निकास(sm4_fini);

MODULE_DESCRIPTION("SM4 Cipher Algorithm");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("sm4");
MODULE_ALIAS_CRYPTO("sm4-generic");
