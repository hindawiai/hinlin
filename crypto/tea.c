<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 * Cryptographic API.
 *
 * TEA, XTEA, and XETA crypto alogrithms
 *
 * The TEA and Xtended TEA algorithms were developed by David Wheeler 
 * and Roger Needham at the Computer Laboratory of Cambridge University.
 *
 * Due to the order of evaluation in XTEA many people have incorrectly
 * implemented it.  XETA (XTEA in the wrong order), exists क्रम
 * compatibility with these implementations.
 *
 * Copyright (c) 2004 Aaron Grothe ajgrothe@yahoo.com
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/crypto.h>
#समावेश <linux/types.h>

#घोषणा TEA_KEY_SIZE		16
#घोषणा TEA_BLOCK_SIZE		8
#घोषणा TEA_ROUNDS		32
#घोषणा TEA_DELTA		0x9e3779b9

#घोषणा XTEA_KEY_SIZE		16
#घोषणा XTEA_BLOCK_SIZE		8
#घोषणा XTEA_ROUNDS		32
#घोषणा XTEA_DELTA		0x9e3779b9

काष्ठा tea_ctx अणु
	u32 KEY[4];
पूर्ण;

काष्ठा xtea_ctx अणु
	u32 KEY[4];
पूर्ण;

अटल पूर्णांक tea_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		      अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा tea_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर __le32 *key = (स्थिर __le32 *)in_key;

	ctx->KEY[0] = le32_to_cpu(key[0]);
	ctx->KEY[1] = le32_to_cpu(key[1]);
	ctx->KEY[2] = le32_to_cpu(key[2]);
	ctx->KEY[3] = le32_to_cpu(key[3]);

	वापस 0; 

पूर्ण

अटल व्योम tea_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	u32 y, z, n, sum = 0;
	u32 k0, k1, k2, k3;
	काष्ठा tea_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर __le32 *in = (स्थिर __le32 *)src;
	__le32 *out = (__le32 *)dst;

	y = le32_to_cpu(in[0]);
	z = le32_to_cpu(in[1]);

	k0 = ctx->KEY[0];
	k1 = ctx->KEY[1];
	k2 = ctx->KEY[2];
	k3 = ctx->KEY[3];

	n = TEA_ROUNDS;

	जबतक (n-- > 0) अणु
		sum += TEA_DELTA;
		y += ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
		z += ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
	पूर्ण
	
	out[0] = cpu_to_le32(y);
	out[1] = cpu_to_le32(z);
पूर्ण

अटल व्योम tea_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	u32 y, z, n, sum;
	u32 k0, k1, k2, k3;
	काष्ठा tea_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर __le32 *in = (स्थिर __le32 *)src;
	__le32 *out = (__le32 *)dst;

	y = le32_to_cpu(in[0]);
	z = le32_to_cpu(in[1]);

	k0 = ctx->KEY[0];
	k1 = ctx->KEY[1];
	k2 = ctx->KEY[2];
	k3 = ctx->KEY[3];

	sum = TEA_DELTA << 5;

	n = TEA_ROUNDS;

	जबतक (n-- > 0) अणु
		z -= ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
		y -= ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
		sum -= TEA_DELTA;
	पूर्ण
	
	out[0] = cpu_to_le32(y);
	out[1] = cpu_to_le32(z);
पूर्ण

अटल पूर्णांक xtea_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा xtea_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर __le32 *key = (स्थिर __le32 *)in_key;

	ctx->KEY[0] = le32_to_cpu(key[0]);
	ctx->KEY[1] = le32_to_cpu(key[1]);
	ctx->KEY[2] = le32_to_cpu(key[2]);
	ctx->KEY[3] = le32_to_cpu(key[3]);

	वापस 0; 

पूर्ण

अटल व्योम xtea_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	u32 y, z, sum = 0;
	u32 limit = XTEA_DELTA * XTEA_ROUNDS;
	काष्ठा xtea_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर __le32 *in = (स्थिर __le32 *)src;
	__le32 *out = (__le32 *)dst;

	y = le32_to_cpu(in[0]);
	z = le32_to_cpu(in[1]);

	जबतक (sum != limit) अणु
		y += ((z << 4 ^ z >> 5) + z) ^ (sum + ctx->KEY[sum&3]); 
		sum += XTEA_DELTA;
		z += ((y << 4 ^ y >> 5) + y) ^ (sum + ctx->KEY[sum>>11 &3]); 
	पूर्ण
	
	out[0] = cpu_to_le32(y);
	out[1] = cpu_to_le32(z);
पूर्ण

अटल व्योम xtea_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	u32 y, z, sum;
	काष्ठा tea_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर __le32 *in = (स्थिर __le32 *)src;
	__le32 *out = (__le32 *)dst;

	y = le32_to_cpu(in[0]);
	z = le32_to_cpu(in[1]);

	sum = XTEA_DELTA * XTEA_ROUNDS;

	जबतक (sum) अणु
		z -= ((y << 4 ^ y >> 5) + y) ^ (sum + ctx->KEY[sum>>11 & 3]);
		sum -= XTEA_DELTA;
		y -= ((z << 4 ^ z >> 5) + z) ^ (sum + ctx->KEY[sum & 3]);
	पूर्ण
	
	out[0] = cpu_to_le32(y);
	out[1] = cpu_to_le32(z);
पूर्ण


अटल व्योम xeta_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	u32 y, z, sum = 0;
	u32 limit = XTEA_DELTA * XTEA_ROUNDS;
	काष्ठा xtea_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर __le32 *in = (स्थिर __le32 *)src;
	__le32 *out = (__le32 *)dst;

	y = le32_to_cpu(in[0]);
	z = le32_to_cpu(in[1]);

	जबतक (sum != limit) अणु
		y += (z << 4 ^ z >> 5) + (z ^ sum) + ctx->KEY[sum&3];
		sum += XTEA_DELTA;
		z += (y << 4 ^ y >> 5) + (y ^ sum) + ctx->KEY[sum>>11 &3];
	पूर्ण
	
	out[0] = cpu_to_le32(y);
	out[1] = cpu_to_le32(z);
पूर्ण

अटल व्योम xeta_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	u32 y, z, sum;
	काष्ठा tea_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर __le32 *in = (स्थिर __le32 *)src;
	__le32 *out = (__le32 *)dst;

	y = le32_to_cpu(in[0]);
	z = le32_to_cpu(in[1]);

	sum = XTEA_DELTA * XTEA_ROUNDS;

	जबतक (sum) अणु
		z -= (y << 4 ^ y >> 5) + (y ^ sum) + ctx->KEY[sum>>11 & 3];
		sum -= XTEA_DELTA;
		y -= (z << 4 ^ z >> 5) + (z ^ sum) + ctx->KEY[sum & 3];
	पूर्ण
	
	out[0] = cpu_to_le32(y);
	out[1] = cpu_to_le32(z);
पूर्ण

अटल काष्ठा crypto_alg tea_algs[3] = अणु अणु
	.cra_name		=	"tea",
	.cra_driver_name	=	"tea-generic",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	TEA_BLOCK_SIZE,
	.cra_ctxsize		=	माप (काष्ठा tea_ctx),
	.cra_alignmask		=	3,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु .cipher = अणु
	.cia_min_keysize	=	TEA_KEY_SIZE,
	.cia_max_keysize	=	TEA_KEY_SIZE,
	.cia_setkey		= 	tea_setkey,
	.cia_encrypt		=	tea_encrypt,
	.cia_decrypt		=	tea_decrypt पूर्ण पूर्ण
पूर्ण, अणु
	.cra_name		=	"xtea",
	.cra_driver_name	=	"xtea-generic",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	XTEA_BLOCK_SIZE,
	.cra_ctxsize		=	माप (काष्ठा xtea_ctx),
	.cra_alignmask		=	3,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु .cipher = अणु
	.cia_min_keysize	=	XTEA_KEY_SIZE,
	.cia_max_keysize	=	XTEA_KEY_SIZE,
	.cia_setkey		= 	xtea_setkey,
	.cia_encrypt		=	xtea_encrypt,
	.cia_decrypt		=	xtea_decrypt पूर्ण पूर्ण
पूर्ण, अणु
	.cra_name		=	"xeta",
	.cra_driver_name	=	"xeta-generic",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	XTEA_BLOCK_SIZE,
	.cra_ctxsize		=	माप (काष्ठा xtea_ctx),
	.cra_alignmask		=	3,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु .cipher = अणु
	.cia_min_keysize	=	XTEA_KEY_SIZE,
	.cia_max_keysize	=	XTEA_KEY_SIZE,
	.cia_setkey		= 	xtea_setkey,
	.cia_encrypt		=	xeta_encrypt,
	.cia_decrypt		=	xeta_decrypt पूर्ण पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init tea_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_algs(tea_algs, ARRAY_SIZE(tea_algs));
पूर्ण

अटल व्योम __निकास tea_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_algs(tea_algs, ARRAY_SIZE(tea_algs));
पूर्ण

MODULE_ALIAS_CRYPTO("tea");
MODULE_ALIAS_CRYPTO("xtea");
MODULE_ALIAS_CRYPTO("xeta");

subsys_initcall(tea_mod_init);
module_निकास(tea_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TEA, XTEA & XETA Cryptographic Algorithms");
