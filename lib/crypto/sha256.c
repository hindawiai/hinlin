<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SHA-256, as specअगरied in
 * http://csrc.nist.gov/groups/STM/cavp/करोcuments/shs/sha256-384-512.pdf
 *
 * SHA-256 code by Jean-Luc Cooke <jlcooke@certainkey.com>.
 *
 * Copyright (c) Jean-Luc Cooke <jlcooke@certainkey.com>
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2014 Red Hat Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <crypto/sha2.h>
#समावेश <यंत्र/unaligned.h>

अटल स्थिर u32 SHA256_K[] = अणु
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
पूर्ण;

अटल अंतरभूत u32 Ch(u32 x, u32 y, u32 z)
अणु
	वापस z ^ (x & (y ^ z));
पूर्ण

अटल अंतरभूत u32 Maj(u32 x, u32 y, u32 z)
अणु
	वापस (x & y) | (z & (x | y));
पूर्ण

#घोषणा e0(x)       (ror32(x, 2) ^ ror32(x, 13) ^ ror32(x, 22))
#घोषणा e1(x)       (ror32(x, 6) ^ ror32(x, 11) ^ ror32(x, 25))
#घोषणा s0(x)       (ror32(x, 7) ^ ror32(x, 18) ^ (x >> 3))
#घोषणा s1(x)       (ror32(x, 17) ^ ror32(x, 19) ^ (x >> 10))

अटल अंतरभूत व्योम LOAD_OP(पूर्णांक I, u32 *W, स्थिर u8 *input)
अणु
	W[I] = get_unaligned_be32((__u32 *)input + I);
पूर्ण

अटल अंतरभूत व्योम BLEND_OP(पूर्णांक I, u32 *W)
अणु
	W[I] = s1(W[I-2]) + W[I-7] + s0(W[I-15]) + W[I-16];
पूर्ण

#घोषणा SHA256_ROUND(i, a, b, c, d, e, f, g, h) करो अणु		\
	u32 t1, t2;						\
	t1 = h + e1(e) + Ch(e, f, g) + SHA256_K[i] + W[i];	\
	t2 = e0(a) + Maj(a, b, c);				\
	d += t1;						\
	h = t1 + t2;						\
पूर्ण जबतक (0)

अटल व्योम sha256_transक्रमm(u32 *state, स्थिर u8 *input, u32 *W)
अणु
	u32 a, b, c, d, e, f, g, h;
	पूर्णांक i;

	/* load the input */
	क्रम (i = 0; i < 16; i += 8) अणु
		LOAD_OP(i + 0, W, input);
		LOAD_OP(i + 1, W, input);
		LOAD_OP(i + 2, W, input);
		LOAD_OP(i + 3, W, input);
		LOAD_OP(i + 4, W, input);
		LOAD_OP(i + 5, W, input);
		LOAD_OP(i + 6, W, input);
		LOAD_OP(i + 7, W, input);
	पूर्ण

	/* now blend */
	क्रम (i = 16; i < 64; i += 8) अणु
		BLEND_OP(i + 0, W);
		BLEND_OP(i + 1, W);
		BLEND_OP(i + 2, W);
		BLEND_OP(i + 3, W);
		BLEND_OP(i + 4, W);
		BLEND_OP(i + 5, W);
		BLEND_OP(i + 6, W);
		BLEND_OP(i + 7, W);
	पूर्ण

	/* load the state पूर्णांकo our रेजिस्टरs */
	a = state[0];  b = state[1];  c = state[2];  d = state[3];
	e = state[4];  f = state[5];  g = state[6];  h = state[7];

	/* now iterate */
	क्रम (i = 0; i < 64; i += 8) अणु
		SHA256_ROUND(i + 0, a, b, c, d, e, f, g, h);
		SHA256_ROUND(i + 1, h, a, b, c, d, e, f, g);
		SHA256_ROUND(i + 2, g, h, a, b, c, d, e, f);
		SHA256_ROUND(i + 3, f, g, h, a, b, c, d, e);
		SHA256_ROUND(i + 4, e, f, g, h, a, b, c, d);
		SHA256_ROUND(i + 5, d, e, f, g, h, a, b, c);
		SHA256_ROUND(i + 6, c, d, e, f, g, h, a, b);
		SHA256_ROUND(i + 7, b, c, d, e, f, g, h, a);
	पूर्ण

	state[0] += a; state[1] += b; state[2] += c; state[3] += d;
	state[4] += e; state[5] += f; state[6] += g; state[7] += h;
पूर्ण

व्योम sha256_update(काष्ठा sha256_state *sctx, स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक partial, करोne;
	स्थिर u8 *src;
	u32 W[64];

	partial = sctx->count & 0x3f;
	sctx->count += len;
	करोne = 0;
	src = data;

	अगर ((partial + len) > 63) अणु
		अगर (partial) अणु
			करोne = -partial;
			स_नकल(sctx->buf + partial, data, करोne + 64);
			src = sctx->buf;
		पूर्ण

		करो अणु
			sha256_transक्रमm(sctx->state, src, W);
			करोne += 64;
			src = data + करोne;
		पूर्ण जबतक (करोne + 63 < len);

		memzero_explicit(W, माप(W));

		partial = 0;
	पूर्ण
	स_नकल(sctx->buf + partial, src, len - करोne);
पूर्ण
EXPORT_SYMBOL(sha256_update);

व्योम sha224_update(काष्ठा sha256_state *sctx, स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	sha256_update(sctx, data, len);
पूर्ण
EXPORT_SYMBOL(sha224_update);

अटल व्योम __sha256_final(काष्ठा sha256_state *sctx, u8 *out, पूर्णांक digest_words)
अणु
	__be32 *dst = (__be32 *)out;
	__be64 bits;
	अचिन्हित पूर्णांक index, pad_len;
	पूर्णांक i;
	अटल स्थिर u8 padding[64] = अणु 0x80, पूर्ण;

	/* Save number of bits */
	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64. */
	index = sctx->count & 0x3f;
	pad_len = (index < 56) ? (56 - index) : ((64+56) - index);
	sha256_update(sctx, padding, pad_len);

	/* Append length (beक्रमe padding) */
	sha256_update(sctx, (स्थिर u8 *)&bits, माप(bits));

	/* Store state in digest */
	क्रम (i = 0; i < digest_words; i++)
		put_unaligned_be32(sctx->state[i], &dst[i]);

	/* Zeroize sensitive inक्रमmation. */
	memzero_explicit(sctx, माप(*sctx));
पूर्ण

व्योम sha256_final(काष्ठा sha256_state *sctx, u8 *out)
अणु
	__sha256_final(sctx, out, 8);
पूर्ण
EXPORT_SYMBOL(sha256_final);

व्योम sha224_final(काष्ठा sha256_state *sctx, u8 *out)
अणु
	__sha256_final(sctx, out, 7);
पूर्ण
EXPORT_SYMBOL(sha224_final);

व्योम sha256(स्थिर u8 *data, अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा sha256_state sctx;

	sha256_init(&sctx);
	sha256_update(&sctx, data, len);
	sha256_final(&sctx, out);
पूर्ण
EXPORT_SYMBOL(sha256);

MODULE_LICENSE("GPL");
