<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR Apache-2.0)
/*
 * Generic implementation of the BLAKE2b digest algorithm.  Based on the BLAKE2b
 * reference implementation, but it has been heavily modअगरied क्रम use in the
 * kernel.  The reference implementation was:
 *
 *	Copyright 2012, Samuel Neves <sneves@dei.uc.pt>.  You may use this under
 *	the terms of the CC0, the OpenSSL Licence, or the Apache Public License
 *	2.0, at your option.  The terms of these licenses can be found at:
 *
 *	- CC0 1.0 Universal : http://creativecommons.org/खुलाकरोमुख्य/zero/1.0
 *	- OpenSSL license   : https://www.खोलोssl.org/source/license.hपंचांगl
 *	- Apache 2.0        : https://www.apache.org/licenses/LICENSE-2.0
 *
 * More inक्रमmation about BLAKE2 can be found at https://blake2.net.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <crypto/पूर्णांकernal/blake2b.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

अटल स्थिर u8 blake2b_sigma[12][16] = अणु
	अणु  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 पूर्ण,
	अणु 14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3 पूर्ण,
	अणु 11,  8, 12,  0,  5,  2, 15, 13, 10, 14,  3,  6,  7,  1,  9,  4 पूर्ण,
	अणु  7,  9,  3,  1, 13, 12, 11, 14,  2,  6,  5, 10,  4,  0, 15,  8 पूर्ण,
	अणु  9,  0,  5,  7,  2,  4, 10, 15, 14,  1, 11, 12,  6,  8,  3, 13 पूर्ण,
	अणु  2, 12,  6, 10,  0, 11,  8,  3,  4, 13,  7,  5, 15, 14,  1,  9 पूर्ण,
	अणु 12,  5,  1, 15, 14, 13,  4, 10,  0,  7,  6,  3,  9,  2,  8, 11 पूर्ण,
	अणु 13, 11,  7, 14, 12,  1,  3,  9,  5,  0, 15,  4,  8,  6,  2, 10 पूर्ण,
	अणु  6, 15, 14,  9, 11,  3,  0,  8, 12,  2, 13,  7,  1,  4, 10,  5 पूर्ण,
	अणु 10,  2,  8,  4,  7,  6,  1,  5, 15, 11,  9, 14,  3, 12, 13,  0 पूर्ण,
	अणु  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 पूर्ण,
	अणु 14, 10,  4,  8,  9, 15, 13,  6,  1, 12,  0,  2, 11,  7,  5,  3 पूर्ण
पूर्ण;

अटल व्योम blake2b_increment_counter(काष्ठा blake2b_state *S, स्थिर u64 inc)
अणु
	S->t[0] += inc;
	S->t[1] += (S->t[0] < inc);
पूर्ण

#घोषणा G(r,i,a,b,c,d)                                  \
	करो अणु                                            \
		a = a + b + m[blake2b_sigma[r][2*i+0]]; \
		d = ror64(d ^ a, 32);                   \
		c = c + d;                              \
		b = ror64(b ^ c, 24);                   \
		a = a + b + m[blake2b_sigma[r][2*i+1]]; \
		d = ror64(d ^ a, 16);                   \
		c = c + d;                              \
		b = ror64(b ^ c, 63);                   \
	पूर्ण जबतक (0)

#घोषणा ROUND(r)                                \
	करो अणु                                    \
		G(r,0,v[ 0],v[ 4],v[ 8],v[12]); \
		G(r,1,v[ 1],v[ 5],v[ 9],v[13]); \
		G(r,2,v[ 2],v[ 6],v[10],v[14]); \
		G(r,3,v[ 3],v[ 7],v[11],v[15]); \
		G(r,4,v[ 0],v[ 5],v[10],v[15]); \
		G(r,5,v[ 1],v[ 6],v[11],v[12]); \
		G(r,6,v[ 2],v[ 7],v[ 8],v[13]); \
		G(r,7,v[ 3],v[ 4],v[ 9],v[14]); \
	पूर्ण जबतक (0)

अटल व्योम blake2b_compress_one_generic(काष्ठा blake2b_state *S,
					 स्थिर u8 block[BLAKE2B_BLOCK_SIZE])
अणु
	u64 m[16];
	u64 v[16];
	माप_प्रकार i;

	क्रम (i = 0; i < 16; ++i)
		m[i] = get_unaligned_le64(block + i * माप(m[i]));

	क्रम (i = 0; i < 8; ++i)
		v[i] = S->h[i];

	v[ 8] = BLAKE2B_IV0;
	v[ 9] = BLAKE2B_IV1;
	v[10] = BLAKE2B_IV2;
	v[11] = BLAKE2B_IV3;
	v[12] = BLAKE2B_IV4 ^ S->t[0];
	v[13] = BLAKE2B_IV5 ^ S->t[1];
	v[14] = BLAKE2B_IV6 ^ S->f[0];
	v[15] = BLAKE2B_IV7 ^ S->f[1];

	ROUND(0);
	ROUND(1);
	ROUND(2);
	ROUND(3);
	ROUND(4);
	ROUND(5);
	ROUND(6);
	ROUND(7);
	ROUND(8);
	ROUND(9);
	ROUND(10);
	ROUND(11);
#अगर_घोषित CONFIG_CC_IS_CLANG
#आशय nounroll /* https://bugs.llvm.org/show_bug.cgi?id=45803 */
#पूर्ण_अगर
	क्रम (i = 0; i < 8; ++i)
		S->h[i] = S->h[i] ^ v[i] ^ v[i + 8];
पूर्ण

#अघोषित G
#अघोषित ROUND

व्योम blake2b_compress_generic(काष्ठा blake2b_state *state,
			      स्थिर u8 *block, माप_प्रकार nblocks, u32 inc)
अणु
	करो अणु
		blake2b_increment_counter(state, inc);
		blake2b_compress_one_generic(state, block);
		block += BLAKE2B_BLOCK_SIZE;
	पूर्ण जबतक (--nblocks);
पूर्ण
EXPORT_SYMBOL(blake2b_compress_generic);

अटल पूर्णांक crypto_blake2b_update_generic(काष्ठा shash_desc *desc,
					 स्थिर u8 *in, अचिन्हित पूर्णांक inlen)
अणु
	वापस crypto_blake2b_update(desc, in, inlen, blake2b_compress_generic);
पूर्ण

अटल पूर्णांक crypto_blake2b_final_generic(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस crypto_blake2b_final(desc, out, blake2b_compress_generic);
पूर्ण

#घोषणा BLAKE2B_ALG(name, driver_name, digest_size)			\
	अणु								\
		.base.cra_name		= name,				\
		.base.cra_driver_name	= driver_name,			\
		.base.cra_priority	= 100,				\
		.base.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,	\
		.base.cra_blocksize	= BLAKE2B_BLOCK_SIZE,		\
		.base.cra_ctxsize	= माप(काष्ठा blake2b_tfm_ctx), \
		.base.cra_module	= THIS_MODULE,			\
		.digestsize		= digest_size,			\
		.setkey			= crypto_blake2b_setkey,	\
		.init			= crypto_blake2b_init,		\
		.update			= crypto_blake2b_update_generic, \
		.final			= crypto_blake2b_final_generic,	\
		.descsize		= माप(काष्ठा blake2b_state),	\
	पूर्ण

अटल काष्ठा shash_alg blake2b_algs[] = अणु
	BLAKE2B_ALG("blake2b-160", "blake2b-160-generic",
		    BLAKE2B_160_HASH_SIZE),
	BLAKE2B_ALG("blake2b-256", "blake2b-256-generic",
		    BLAKE2B_256_HASH_SIZE),
	BLAKE2B_ALG("blake2b-384", "blake2b-384-generic",
		    BLAKE2B_384_HASH_SIZE),
	BLAKE2B_ALG("blake2b-512", "blake2b-512-generic",
		    BLAKE2B_512_HASH_SIZE),
पूर्ण;

अटल पूर्णांक __init blake2b_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shashes(blake2b_algs, ARRAY_SIZE(blake2b_algs));
पूर्ण

अटल व्योम __निकास blake2b_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(blake2b_algs, ARRAY_SIZE(blake2b_algs));
पूर्ण

subsys_initcall(blake2b_mod_init);
module_निकास(blake2b_mod_fini);

MODULE_AUTHOR("David Sterba <kdave@kernel.org>");
MODULE_DESCRIPTION("BLAKE2b generic implementation");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CRYPTO("blake2b-160");
MODULE_ALIAS_CRYPTO("blake2b-160-generic");
MODULE_ALIAS_CRYPTO("blake2b-256");
MODULE_ALIAS_CRYPTO("blake2b-256-generic");
MODULE_ALIAS_CRYPTO("blake2b-384");
MODULE_ALIAS_CRYPTO("blake2b-384-generic");
MODULE_ALIAS_CRYPTO("blake2b-512");
MODULE_ALIAS_CRYPTO("blake2b-512-generic");
