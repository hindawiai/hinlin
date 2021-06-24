<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * Blowfish Cipher Algorithm, by Bruce Schneier.
 * http://www.counterpane.com/blowfish.hपंचांगl
 *
 * Adapted from Kerneli implementation.
 *
 * Copyright (c) Herbert Valerio Riedel <hvr@hvrlab.org>
 * Copyright (c) Kyle McMartin <kyle@debian.org>
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/crypto.h>
#समावेश <linux/types.h>
#समावेश <crypto/blowfish.h>

/*
 * Round loop unrolling macros, S is a poपूर्णांकer to a S-Box array
 * organized in 4 अचिन्हित दीर्घs at a row.
 */
#घोषणा GET32_3(x) (((x) & 0xff))
#घोषणा GET32_2(x) (((x) >> (8)) & (0xff))
#घोषणा GET32_1(x) (((x) >> (16)) & (0xff))
#घोषणा GET32_0(x) (((x) >> (24)) & (0xff))

#घोषणा bf_F(x) (((S[GET32_0(x)] + S[256 + GET32_1(x)]) ^ \
		S[512 + GET32_2(x)]) + S[768 + GET32_3(x)])

#घोषणा ROUND(a, b, n) (अणु b ^= P[n]; a ^= bf_F(b); पूर्ण)

अटल व्योम bf_encrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा bf_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर u32 *P = ctx->p;
	स्थिर u32 *S = ctx->s;
	u32 yl = get_unaligned_be32(src);
	u32 yr = get_unaligned_be32(src + 4);

	ROUND(yr, yl, 0);
	ROUND(yl, yr, 1);
	ROUND(yr, yl, 2);
	ROUND(yl, yr, 3);
	ROUND(yr, yl, 4);
	ROUND(yl, yr, 5);
	ROUND(yr, yl, 6);
	ROUND(yl, yr, 7);
	ROUND(yr, yl, 8);
	ROUND(yl, yr, 9);
	ROUND(yr, yl, 10);
	ROUND(yl, yr, 11);
	ROUND(yr, yl, 12);
	ROUND(yl, yr, 13);
	ROUND(yr, yl, 14);
	ROUND(yl, yr, 15);

	yl ^= P[16];
	yr ^= P[17];

	put_unaligned_be32(yr, dst);
	put_unaligned_be32(yl, dst + 4);
पूर्ण

अटल व्योम bf_decrypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	काष्ठा bf_ctx *ctx = crypto_tfm_ctx(tfm);
	स्थिर u32 *P = ctx->p;
	स्थिर u32 *S = ctx->s;
	u32 yl = get_unaligned_be32(src);
	u32 yr = get_unaligned_be32(src + 4);

	ROUND(yr, yl, 17);
	ROUND(yl, yr, 16);
	ROUND(yr, yl, 15);
	ROUND(yl, yr, 14);
	ROUND(yr, yl, 13);
	ROUND(yl, yr, 12);
	ROUND(yr, yl, 11);
	ROUND(yl, yr, 10);
	ROUND(yr, yl, 9);
	ROUND(yl, yr, 8);
	ROUND(yr, yl, 7);
	ROUND(yl, yr, 6);
	ROUND(yr, yl, 5);
	ROUND(yl, yr, 4);
	ROUND(yr, yl, 3);
	ROUND(yl, yr, 2);

	yl ^= P[1];
	yr ^= P[0];

	put_unaligned_be32(yr, dst);
	put_unaligned_be32(yl, dst + 4);
पूर्ण

अटल काष्ठा crypto_alg alg = अणु
	.cra_name		=	"blowfish",
	.cra_driver_name	=	"blowfish-generic",
	.cra_priority		=	100,
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	BF_BLOCK_SIZE,
	.cra_ctxsize		=	माप(काष्ठा bf_ctx),
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु .cipher = अणु
	.cia_min_keysize	=	BF_MIN_KEY_SIZE,
	.cia_max_keysize	=	BF_MAX_KEY_SIZE,
	.cia_setkey		=	blowfish_setkey,
	.cia_encrypt		=	bf_encrypt,
	.cia_decrypt		=	bf_decrypt पूर्ण पूर्ण
पूर्ण;

अटल पूर्णांक __init blowfish_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_alg(&alg);
पूर्ण

अटल व्योम __निकास blowfish_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_alg(&alg);
पूर्ण

subsys_initcall(blowfish_mod_init);
module_निकास(blowfish_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Blowfish Cipher Algorithm");
MODULE_ALIAS_CRYPTO("blowfish");
MODULE_ALIAS_CRYPTO("blowfish-generic");
