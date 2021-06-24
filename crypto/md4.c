<शैली गुरु>
/* 
 * Cryptographic API.
 *
 * MD4 Message Digest Algorithm (RFC1320).
 *
 * Implementation derived from Andrew Tridgell and Steve French's
 * CIFS MD4 implementation, and the cryptoapi implementation
 * originally based on the खुला करोमुख्य implementation written
 * by Colin Plumb in 1993.
 *
 * Copyright (c) Andrew Tridgell 1997-1998.
 * Modअगरied by Steve French (sfrench@us.ibm.com) 2002
 * Copyright (c) Cryptoapi developers.
 * Copyright (c) 2002 David S. Miller (davem@redhat.com)
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा MD4_DIGEST_SIZE		16
#घोषणा MD4_HMAC_BLOCK_SIZE	64
#घोषणा MD4_BLOCK_WORDS		16
#घोषणा MD4_HASH_WORDS		4

काष्ठा md4_ctx अणु
	u32 hash[MD4_HASH_WORDS];
	u32 block[MD4_BLOCK_WORDS];
	u64 byte_count;
पूर्ण;

अटल अंतरभूत u32 lshअगरt(u32 x, अचिन्हित पूर्णांक s)
अणु
	x &= 0xFFFFFFFF;
	वापस ((x << s) & 0xFFFFFFFF) | (x >> (32 - s));
पूर्ण

अटल अंतरभूत u32 F(u32 x, u32 y, u32 z)
अणु
	वापस (x & y) | ((~x) & z);
पूर्ण

अटल अंतरभूत u32 G(u32 x, u32 y, u32 z)
अणु
	वापस (x & y) | (x & z) | (y & z);
पूर्ण

अटल अंतरभूत u32 H(u32 x, u32 y, u32 z)
अणु
	वापस x ^ y ^ z;
पूर्ण

#घोषणा ROUND1(a,b,c,d,k,s) (a = lshअगरt(a + F(b,c,d) + k, s))
#घोषणा ROUND2(a,b,c,d,k,s) (a = lshअगरt(a + G(b,c,d) + k + (u32)0x5A827999,s))
#घोषणा ROUND3(a,b,c,d,k,s) (a = lshअगरt(a + H(b,c,d) + k + (u32)0x6ED9EBA1,s))

अटल व्योम md4_transक्रमm(u32 *hash, u32 स्थिर *in)
अणु
	u32 a, b, c, d;

	a = hash[0];
	b = hash[1];
	c = hash[2];
	d = hash[3];

	ROUND1(a, b, c, d, in[0], 3);
	ROUND1(d, a, b, c, in[1], 7);
	ROUND1(c, d, a, b, in[2], 11);
	ROUND1(b, c, d, a, in[3], 19);
	ROUND1(a, b, c, d, in[4], 3);
	ROUND1(d, a, b, c, in[5], 7);
	ROUND1(c, d, a, b, in[6], 11);
	ROUND1(b, c, d, a, in[7], 19);
	ROUND1(a, b, c, d, in[8], 3);
	ROUND1(d, a, b, c, in[9], 7);
	ROUND1(c, d, a, b, in[10], 11);
	ROUND1(b, c, d, a, in[11], 19);
	ROUND1(a, b, c, d, in[12], 3);
	ROUND1(d, a, b, c, in[13], 7);
	ROUND1(c, d, a, b, in[14], 11);
	ROUND1(b, c, d, a, in[15], 19);

	ROUND2(a, b, c, d,in[ 0], 3);
	ROUND2(d, a, b, c, in[4], 5);
	ROUND2(c, d, a, b, in[8], 9);
	ROUND2(b, c, d, a, in[12], 13);
	ROUND2(a, b, c, d, in[1], 3);
	ROUND2(d, a, b, c, in[5], 5);
	ROUND2(c, d, a, b, in[9], 9);
	ROUND2(b, c, d, a, in[13], 13);
	ROUND2(a, b, c, d, in[2], 3);
	ROUND2(d, a, b, c, in[6], 5);
	ROUND2(c, d, a, b, in[10], 9);
	ROUND2(b, c, d, a, in[14], 13);
	ROUND2(a, b, c, d, in[3], 3);
	ROUND2(d, a, b, c, in[7], 5);
	ROUND2(c, d, a, b, in[11], 9);
	ROUND2(b, c, d, a, in[15], 13);

	ROUND3(a, b, c, d,in[ 0], 3);
	ROUND3(d, a, b, c, in[8], 9);
	ROUND3(c, d, a, b, in[4], 11);
	ROUND3(b, c, d, a, in[12], 15);
	ROUND3(a, b, c, d, in[2], 3);
	ROUND3(d, a, b, c, in[10], 9);
	ROUND3(c, d, a, b, in[6], 11);
	ROUND3(b, c, d, a, in[14], 15);
	ROUND3(a, b, c, d, in[1], 3);
	ROUND3(d, a, b, c, in[9], 9);
	ROUND3(c, d, a, b, in[5], 11);
	ROUND3(b, c, d, a, in[13], 15);
	ROUND3(a, b, c, d, in[3], 3);
	ROUND3(d, a, b, c, in[11], 9);
	ROUND3(c, d, a, b, in[7], 11);
	ROUND3(b, c, d, a, in[15], 15);

	hash[0] += a;
	hash[1] += b;
	hash[2] += c;
	hash[3] += d;
पूर्ण

अटल अंतरभूत व्योम md4_transक्रमm_helper(काष्ठा md4_ctx *ctx)
अणु
	le32_to_cpu_array(ctx->block, ARRAY_SIZE(ctx->block));
	md4_transक्रमm(ctx->hash, ctx->block);
पूर्ण

अटल पूर्णांक md4_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा md4_ctx *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = 0x67452301;
	mctx->hash[1] = 0xefcdab89;
	mctx->hash[2] = 0x98badcfe;
	mctx->hash[3] = 0x10325476;
	mctx->byte_count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक md4_update(काष्ठा shash_desc *desc, स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा md4_ctx *mctx = shash_desc_ctx(desc);
	स्थिर u32 avail = माप(mctx->block) - (mctx->byte_count & 0x3f);

	mctx->byte_count += len;

	अगर (avail > len) अणु
		स_नकल((अक्षर *)mctx->block + (माप(mctx->block) - avail),
		       data, len);
		वापस 0;
	पूर्ण

	स_नकल((अक्षर *)mctx->block + (माप(mctx->block) - avail),
	       data, avail);

	md4_transक्रमm_helper(mctx);
	data += avail;
	len -= avail;

	जबतक (len >= माप(mctx->block)) अणु
		स_नकल(mctx->block, data, माप(mctx->block));
		md4_transक्रमm_helper(mctx);
		data += माप(mctx->block);
		len -= माप(mctx->block);
	पूर्ण

	स_नकल(mctx->block, data, len);

	वापस 0;
पूर्ण

अटल पूर्णांक md4_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा md4_ctx *mctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = mctx->byte_count & 0x3f;
	अक्षर *p = (अक्षर *)mctx->block + offset;
	पूर्णांक padding = 56 - (offset + 1);

	*p++ = 0x80;
	अगर (padding < 0) अणु
		स_रखो(p, 0x00, padding + माप (u64));
		md4_transक्रमm_helper(mctx);
		p = (अक्षर *)mctx->block;
		padding = 56;
	पूर्ण

	स_रखो(p, 0, padding);
	mctx->block[14] = mctx->byte_count << 3;
	mctx->block[15] = mctx->byte_count >> 29;
	le32_to_cpu_array(mctx->block, (माप(mctx->block) -
	                  माप(u64)) / माप(u32));
	md4_transक्रमm(mctx->hash, mctx->block);
	cpu_to_le32_array(mctx->hash, ARRAY_SIZE(mctx->hash));
	स_नकल(out, mctx->hash, माप(mctx->hash));
	स_रखो(mctx, 0, माप(*mctx));

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	MD4_DIGEST_SIZE,
	.init		=	md4_init,
	.update		=	md4_update,
	.final		=	md4_final,
	.descsize	=	माप(काष्ठा md4_ctx),
	.base		=	अणु
		.cra_name	 =	"md4",
		.cra_driver_name =	"md4-generic",
		.cra_blocksize	 =	MD4_HMAC_BLOCK_SIZE,
		.cra_module	 =	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init md4_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास md4_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

subsys_initcall(md4_mod_init);
module_निकास(md4_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MD4 Message Digest Algorithm");
MODULE_ALIAS_CRYPTO("md4");
