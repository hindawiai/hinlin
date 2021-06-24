<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SM3 secure hash, as specअगरied by OSCCA GM/T 0004-2012 SM3 and
 * described at https://tools.ietf.org/hपंचांगl/draft-shen-sm3-hash-01
 *
 * Copyright (C) 2017 ARM Limited or its affiliates.
 * Written by Gilad Ben-Yossef <gilad@benyossef.com>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sm3.h>
#समावेश <crypto/sm3_base.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

स्थिर u8 sm3_zero_message_hash[SM3_DIGEST_SIZE] = अणु
	0x1A, 0xB2, 0x1D, 0x83, 0x55, 0xCF, 0xA1, 0x7F,
	0x8e, 0x61, 0x19, 0x48, 0x31, 0xE8, 0x1A, 0x8F,
	0x22, 0xBE, 0xC8, 0xC7, 0x28, 0xFE, 0xFB, 0x74,
	0x7E, 0xD0, 0x35, 0xEB, 0x50, 0x82, 0xAA, 0x2B
पूर्ण;
EXPORT_SYMBOL_GPL(sm3_zero_message_hash);

अटल अंतरभूत u32 p0(u32 x)
अणु
	वापस x ^ rol32(x, 9) ^ rol32(x, 17);
पूर्ण

अटल अंतरभूत u32 p1(u32 x)
अणु
	वापस x ^ rol32(x, 15) ^ rol32(x, 23);
पूर्ण

अटल अंतरभूत u32 ff(अचिन्हित पूर्णांक n, u32 a, u32 b, u32 c)
अणु
	वापस (n < 16) ? (a ^ b ^ c) : ((a & b) | (a & c) | (b & c));
पूर्ण

अटल अंतरभूत u32 gg(अचिन्हित पूर्णांक n, u32 e, u32 f, u32 g)
अणु
	वापस (n < 16) ? (e ^ f ^ g) : ((e & f) | ((~e) & g));
पूर्ण

अटल अंतरभूत u32 t(अचिन्हित पूर्णांक n)
अणु
	वापस (n < 16) ? SM3_T1 : SM3_T2;
पूर्ण

अटल व्योम sm3_expand(u32 *t, u32 *w, u32 *wt)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक पंचांगp;

	/* load the input */
	क्रम (i = 0; i <= 15; i++)
		w[i] = get_unaligned_be32((__u32 *)t + i);

	क्रम (i = 16; i <= 67; i++) अणु
		पंचांगp = w[i - 16] ^ w[i - 9] ^ rol32(w[i - 3], 15);
		w[i] = p1(पंचांगp) ^ (rol32(w[i - 13], 7)) ^ w[i - 6];
	पूर्ण

	क्रम (i = 0; i <= 63; i++)
		wt[i] = w[i] ^ w[i + 4];
पूर्ण

अटल व्योम sm3_compress(u32 *w, u32 *wt, u32 *m)
अणु
	u32 ss1;
	u32 ss2;
	u32 tt1;
	u32 tt2;
	u32 a, b, c, d, e, f, g, h;
	पूर्णांक i;

	a = m[0];
	b = m[1];
	c = m[2];
	d = m[3];
	e = m[4];
	f = m[5];
	g = m[6];
	h = m[7];

	क्रम (i = 0; i <= 63; i++) अणु

		ss1 = rol32((rol32(a, 12) + e + rol32(t(i), i & 31)), 7);

		ss2 = ss1 ^ rol32(a, 12);

		tt1 = ff(i, a, b, c) + d + ss2 + *wt;
		wt++;

		tt2 = gg(i, e, f, g) + h + ss1 + *w;
		w++;

		d = c;
		c = rol32(b, 9);
		b = a;
		a = tt1;
		h = g;
		g = rol32(f, 19);
		f = e;
		e = p0(tt2);
	पूर्ण

	m[0] = a ^ m[0];
	m[1] = b ^ m[1];
	m[2] = c ^ m[2];
	m[3] = d ^ m[3];
	m[4] = e ^ m[4];
	m[5] = f ^ m[5];
	m[6] = g ^ m[6];
	m[7] = h ^ m[7];

	a = b = c = d = e = f = g = h = ss1 = ss2 = tt1 = tt2 = 0;
पूर्ण

अटल व्योम sm3_transक्रमm(काष्ठा sm3_state *sst, u8 स्थिर *src)
अणु
	अचिन्हित पूर्णांक w[68];
	अचिन्हित पूर्णांक wt[64];

	sm3_expand((u32 *)src, w, wt);
	sm3_compress(w, wt, sst->state);

	memzero_explicit(w, माप(w));
	memzero_explicit(wt, माप(wt));
पूर्ण

अटल व्योम sm3_generic_block_fn(काष्ठा sm3_state *sst, u8 स्थिर *src,
				    पूर्णांक blocks)
अणु
	जबतक (blocks--) अणु
		sm3_transक्रमm(sst, src);
		src += SM3_BLOCK_SIZE;
	पूर्ण
पूर्ण

पूर्णांक crypto_sm3_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			  अचिन्हित पूर्णांक len)
अणु
	वापस sm3_base_करो_update(desc, data, len, sm3_generic_block_fn);
पूर्ण
EXPORT_SYMBOL(crypto_sm3_update);

पूर्णांक crypto_sm3_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	sm3_base_करो_finalize(desc, sm3_generic_block_fn);
	वापस sm3_base_finish(desc, out);
पूर्ण
EXPORT_SYMBOL(crypto_sm3_final);

पूर्णांक crypto_sm3_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *hash)
अणु
	sm3_base_करो_update(desc, data, len, sm3_generic_block_fn);
	वापस crypto_sm3_final(desc, hash);
पूर्ण
EXPORT_SYMBOL(crypto_sm3_finup);

अटल काष्ठा shash_alg sm3_alg = अणु
	.digestsize	=	SM3_DIGEST_SIZE,
	.init		=	sm3_base_init,
	.update		=	crypto_sm3_update,
	.final		=	crypto_sm3_final,
	.finup		=	crypto_sm3_finup,
	.descsize	=	माप(काष्ठा sm3_state),
	.base		=	अणु
		.cra_name	 =	"sm3",
		.cra_driver_name =	"sm3-generic",
		.cra_blocksize	 =	SM3_BLOCK_SIZE,
		.cra_module	 =	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sm3_generic_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&sm3_alg);
पूर्ण

अटल व्योम __निकास sm3_generic_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&sm3_alg);
पूर्ण

subsys_initcall(sm3_generic_mod_init);
module_निकास(sm3_generic_mod_fini);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SM3 Secure Hash Algorithm");

MODULE_ALIAS_CRYPTO("sm3");
MODULE_ALIAS_CRYPTO("sm3-generic");
