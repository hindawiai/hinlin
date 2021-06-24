<शैली गुरु>
/* 
 * Cryptographic API.
 *
 * MD5 Message Digest Algorithm (RFC1321).
 *
 * Derived from cryptoapi implementation, originally based on the
 * खुला करोमुख्य implementation written by Colin Plumb in 1993.
 *
 * Copyright (c) Cryptoapi developers.
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * 
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option) 
 * any later version.
 *
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/md5.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

स्थिर u8 md5_zero_message_hash[MD5_DIGEST_SIZE] = अणु
	0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04,
	0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e,
पूर्ण;
EXPORT_SYMBOL_GPL(md5_zero_message_hash);

#घोषणा F1(x, y, z)	(z ^ (x & (y ^ z)))
#घोषणा F2(x, y, z)	F1(z, x, y)
#घोषणा F3(x, y, z)	(x ^ y ^ z)
#घोषणा F4(x, y, z)	(y ^ (x | ~z))

#घोषणा MD5STEP(f, w, x, y, z, in, s) \
	(w += f(x, y, z) + in, w = (w<<s | w>>(32-s)) + x)

अटल व्योम md5_transक्रमm(__u32 *hash, __u32 स्थिर *in)
अणु
	u32 a, b, c, d;

	a = hash[0];
	b = hash[1];
	c = hash[2];
	d = hash[3];

	MD5STEP(F1, a, b, c, d, in[0] + 0xd76aa478, 7);
	MD5STEP(F1, d, a, b, c, in[1] + 0xe8c7b756, 12);
	MD5STEP(F1, c, d, a, b, in[2] + 0x242070db, 17);
	MD5STEP(F1, b, c, d, a, in[3] + 0xc1bdceee, 22);
	MD5STEP(F1, a, b, c, d, in[4] + 0xf57c0faf, 7);
	MD5STEP(F1, d, a, b, c, in[5] + 0x4787c62a, 12);
	MD5STEP(F1, c, d, a, b, in[6] + 0xa8304613, 17);
	MD5STEP(F1, b, c, d, a, in[7] + 0xfd469501, 22);
	MD5STEP(F1, a, b, c, d, in[8] + 0x698098d8, 7);
	MD5STEP(F1, d, a, b, c, in[9] + 0x8b44f7af, 12);
	MD5STEP(F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
	MD5STEP(F1, b, c, d, a, in[11] + 0x895cd7be, 22);
	MD5STEP(F1, a, b, c, d, in[12] + 0x6b901122, 7);
	MD5STEP(F1, d, a, b, c, in[13] + 0xfd987193, 12);
	MD5STEP(F1, c, d, a, b, in[14] + 0xa679438e, 17);
	MD5STEP(F1, b, c, d, a, in[15] + 0x49b40821, 22);

	MD5STEP(F2, a, b, c, d, in[1] + 0xf61e2562, 5);
	MD5STEP(F2, d, a, b, c, in[6] + 0xc040b340, 9);
	MD5STEP(F2, c, d, a, b, in[11] + 0x265e5a51, 14);
	MD5STEP(F2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
	MD5STEP(F2, a, b, c, d, in[5] + 0xd62f105d, 5);
	MD5STEP(F2, d, a, b, c, in[10] + 0x02441453, 9);
	MD5STEP(F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
	MD5STEP(F2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
	MD5STEP(F2, a, b, c, d, in[9] + 0x21e1cde6, 5);
	MD5STEP(F2, d, a, b, c, in[14] + 0xc33707d6, 9);
	MD5STEP(F2, c, d, a, b, in[3] + 0xf4d50d87, 14);
	MD5STEP(F2, b, c, d, a, in[8] + 0x455a14ed, 20);
	MD5STEP(F2, a, b, c, d, in[13] + 0xa9e3e905, 5);
	MD5STEP(F2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
	MD5STEP(F2, c, d, a, b, in[7] + 0x676f02d9, 14);
	MD5STEP(F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

	MD5STEP(F3, a, b, c, d, in[5] + 0xfffa3942, 4);
	MD5STEP(F3, d, a, b, c, in[8] + 0x8771f681, 11);
	MD5STEP(F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
	MD5STEP(F3, b, c, d, a, in[14] + 0xfde5380c, 23);
	MD5STEP(F3, a, b, c, d, in[1] + 0xa4beea44, 4);
	MD5STEP(F3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
	MD5STEP(F3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
	MD5STEP(F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
	MD5STEP(F3, a, b, c, d, in[13] + 0x289b7ec6, 4);
	MD5STEP(F3, d, a, b, c, in[0] + 0xeaa127fa, 11);
	MD5STEP(F3, c, d, a, b, in[3] + 0xd4ef3085, 16);
	MD5STEP(F3, b, c, d, a, in[6] + 0x04881d05, 23);
	MD5STEP(F3, a, b, c, d, in[9] + 0xd9d4d039, 4);
	MD5STEP(F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
	MD5STEP(F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
	MD5STEP(F3, b, c, d, a, in[2] + 0xc4ac5665, 23);

	MD5STEP(F4, a, b, c, d, in[0] + 0xf4292244, 6);
	MD5STEP(F4, d, a, b, c, in[7] + 0x432aff97, 10);
	MD5STEP(F4, c, d, a, b, in[14] + 0xab9423a7, 15);
	MD5STEP(F4, b, c, d, a, in[5] + 0xfc93a039, 21);
	MD5STEP(F4, a, b, c, d, in[12] + 0x655b59c3, 6);
	MD5STEP(F4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
	MD5STEP(F4, c, d, a, b, in[10] + 0xffeff47d, 15);
	MD5STEP(F4, b, c, d, a, in[1] + 0x85845dd1, 21);
	MD5STEP(F4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
	MD5STEP(F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
	MD5STEP(F4, c, d, a, b, in[6] + 0xa3014314, 15);
	MD5STEP(F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
	MD5STEP(F4, a, b, c, d, in[4] + 0xf7537e82, 6);
	MD5STEP(F4, d, a, b, c, in[11] + 0xbd3af235, 10);
	MD5STEP(F4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
	MD5STEP(F4, b, c, d, a, in[9] + 0xeb86d391, 21);

	hash[0] += a;
	hash[1] += b;
	hash[2] += c;
	hash[3] += d;
पूर्ण

अटल अंतरभूत व्योम md5_transक्रमm_helper(काष्ठा md5_state *ctx)
अणु
	le32_to_cpu_array(ctx->block, माप(ctx->block) / माप(u32));
	md5_transक्रमm(ctx->hash, ctx->block);
पूर्ण

अटल पूर्णांक md5_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा md5_state *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = MD5_H0;
	mctx->hash[1] = MD5_H1;
	mctx->hash[2] = MD5_H2;
	mctx->hash[3] = MD5_H3;
	mctx->byte_count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक md5_update(काष्ठा shash_desc *desc, स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा md5_state *mctx = shash_desc_ctx(desc);
	स्थिर u32 avail = माप(mctx->block) - (mctx->byte_count & 0x3f);

	mctx->byte_count += len;

	अगर (avail > len) अणु
		स_नकल((अक्षर *)mctx->block + (माप(mctx->block) - avail),
		       data, len);
		वापस 0;
	पूर्ण

	स_नकल((अक्षर *)mctx->block + (माप(mctx->block) - avail),
	       data, avail);

	md5_transक्रमm_helper(mctx);
	data += avail;
	len -= avail;

	जबतक (len >= माप(mctx->block)) अणु
		स_नकल(mctx->block, data, माप(mctx->block));
		md5_transक्रमm_helper(mctx);
		data += माप(mctx->block);
		len -= माप(mctx->block);
	पूर्ण

	स_नकल(mctx->block, data, len);

	वापस 0;
पूर्ण

अटल पूर्णांक md5_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा md5_state *mctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = mctx->byte_count & 0x3f;
	अक्षर *p = (अक्षर *)mctx->block + offset;
	पूर्णांक padding = 56 - (offset + 1);

	*p++ = 0x80;
	अगर (padding < 0) अणु
		स_रखो(p, 0x00, padding + माप (u64));
		md5_transक्रमm_helper(mctx);
		p = (अक्षर *)mctx->block;
		padding = 56;
	पूर्ण

	स_रखो(p, 0, padding);
	mctx->block[14] = mctx->byte_count << 3;
	mctx->block[15] = mctx->byte_count >> 29;
	le32_to_cpu_array(mctx->block, (माप(mctx->block) -
	                  माप(u64)) / माप(u32));
	md5_transक्रमm(mctx->hash, mctx->block);
	cpu_to_le32_array(mctx->hash, माप(mctx->hash) / माप(u32));
	स_नकल(out, mctx->hash, माप(mctx->hash));
	स_रखो(mctx, 0, माप(*mctx));

	वापस 0;
पूर्ण

अटल पूर्णांक md5_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा md5_state *ctx = shash_desc_ctx(desc);

	स_नकल(out, ctx, माप(*ctx));
	वापस 0;
पूर्ण

अटल पूर्णांक md5_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा md5_state *ctx = shash_desc_ctx(desc);

	स_नकल(ctx, in, माप(*ctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	MD5_DIGEST_SIZE,
	.init		=	md5_init,
	.update		=	md5_update,
	.final		=	md5_final,
	.export		=	md5_export,
	.import		=	md5_import,
	.descsize	=	माप(काष्ठा md5_state),
	.statesize	=	माप(काष्ठा md5_state),
	.base		=	अणु
		.cra_name	 =	"md5",
		.cra_driver_name =	"md5-generic",
		.cra_blocksize	 =	MD5_HMAC_BLOCK_SIZE,
		.cra_module	 =	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init md5_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास md5_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

subsys_initcall(md5_mod_init);
module_निकास(md5_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MD5 Message Digest Algorithm");
MODULE_ALIAS_CRYPTO("md5");
