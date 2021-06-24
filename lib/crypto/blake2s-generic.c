<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This is an implementation of the BLAKE2s hash and PRF functions.
 *
 * Inक्रमmation: https://blake2.net/
 *
 */

#समावेश <crypto/पूर्णांकernal/blake2s.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/unaligned.h>

अटल स्थिर u8 blake2s_sigma[10][16] = अणु
	अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 पूर्ण,
	अणु 14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3 पूर्ण,
	अणु 11, 8, 12, 0, 5, 2, 15, 13, 10, 14, 3, 6, 7, 1, 9, 4 पूर्ण,
	अणु 7, 9, 3, 1, 13, 12, 11, 14, 2, 6, 5, 10, 4, 0, 15, 8 पूर्ण,
	अणु 9, 0, 5, 7, 2, 4, 10, 15, 14, 1, 11, 12, 6, 8, 3, 13 पूर्ण,
	अणु 2, 12, 6, 10, 0, 11, 8, 3, 4, 13, 7, 5, 15, 14, 1, 9 पूर्ण,
	अणु 12, 5, 1, 15, 14, 13, 4, 10, 0, 7, 6, 3, 9, 2, 8, 11 पूर्ण,
	अणु 13, 11, 7, 14, 12, 1, 3, 9, 5, 0, 15, 4, 8, 6, 2, 10 पूर्ण,
	अणु 6, 15, 14, 9, 11, 3, 0, 8, 12, 2, 13, 7, 1, 4, 10, 5 पूर्ण,
	अणु 10, 2, 8, 4, 7, 6, 1, 5, 15, 11, 9, 14, 3, 12, 13, 0 पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम blake2s_increment_counter(काष्ठा blake2s_state *state,
					     स्थिर u32 inc)
अणु
	state->t[0] += inc;
	state->t[1] += (state->t[0] < inc);
पूर्ण

व्योम blake2s_compress_generic(काष्ठा blake2s_state *state,स्थिर u8 *block,
			      माप_प्रकार nblocks, स्थिर u32 inc)
अणु
	u32 m[16];
	u32 v[16];
	पूर्णांक i;

	WARN_ON(IS_ENABLED(DEBUG) &&
		(nblocks > 1 && inc != BLAKE2S_BLOCK_SIZE));

	जबतक (nblocks > 0) अणु
		blake2s_increment_counter(state, inc);
		स_नकल(m, block, BLAKE2S_BLOCK_SIZE);
		le32_to_cpu_array(m, ARRAY_SIZE(m));
		स_नकल(v, state->h, 32);
		v[ 8] = BLAKE2S_IV0;
		v[ 9] = BLAKE2S_IV1;
		v[10] = BLAKE2S_IV2;
		v[11] = BLAKE2S_IV3;
		v[12] = BLAKE2S_IV4 ^ state->t[0];
		v[13] = BLAKE2S_IV5 ^ state->t[1];
		v[14] = BLAKE2S_IV6 ^ state->f[0];
		v[15] = BLAKE2S_IV7 ^ state->f[1];

#घोषणा G(r, i, a, b, c, d) करो अणु \
	a += b + m[blake2s_sigma[r][2 * i + 0]]; \
	d = ror32(d ^ a, 16); \
	c += d; \
	b = ror32(b ^ c, 12); \
	a += b + m[blake2s_sigma[r][2 * i + 1]]; \
	d = ror32(d ^ a, 8); \
	c += d; \
	b = ror32(b ^ c, 7); \
पूर्ण जबतक (0)

#घोषणा ROUND(r) करो अणु \
	G(r, 0, v[0], v[ 4], v[ 8], v[12]); \
	G(r, 1, v[1], v[ 5], v[ 9], v[13]); \
	G(r, 2, v[2], v[ 6], v[10], v[14]); \
	G(r, 3, v[3], v[ 7], v[11], v[15]); \
	G(r, 4, v[0], v[ 5], v[10], v[15]); \
	G(r, 5, v[1], v[ 6], v[11], v[12]); \
	G(r, 6, v[2], v[ 7], v[ 8], v[13]); \
	G(r, 7, v[3], v[ 4], v[ 9], v[14]); \
पूर्ण जबतक (0)
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

#अघोषित G
#अघोषित ROUND

		क्रम (i = 0; i < 8; ++i)
			state->h[i] ^= v[i] ^ v[i + 8];

		block += BLAKE2S_BLOCK_SIZE;
		--nblocks;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(blake2s_compress_generic);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BLAKE2s hash function");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
