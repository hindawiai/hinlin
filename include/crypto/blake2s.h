<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _CRYPTO_BLAKE2S_H
#घोषणा _CRYPTO_BLAKE2S_H

#समावेश <linux/bug.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

क्रमागत blake2s_lengths अणु
	BLAKE2S_BLOCK_SIZE = 64,
	BLAKE2S_HASH_SIZE = 32,
	BLAKE2S_KEY_SIZE = 32,

	BLAKE2S_128_HASH_SIZE = 16,
	BLAKE2S_160_HASH_SIZE = 20,
	BLAKE2S_224_HASH_SIZE = 28,
	BLAKE2S_256_HASH_SIZE = 32,
पूर्ण;

काष्ठा blake2s_state अणु
	/* 'h', 't', and 'f' are used in assembly code, so keep them as-is. */
	u32 h[8];
	u32 t[2];
	u32 f[2];
	u8 buf[BLAKE2S_BLOCK_SIZE];
	अचिन्हित पूर्णांक buflen;
	अचिन्हित पूर्णांक outlen;
पूर्ण;

क्रमागत blake2s_iv अणु
	BLAKE2S_IV0 = 0x6A09E667UL,
	BLAKE2S_IV1 = 0xBB67AE85UL,
	BLAKE2S_IV2 = 0x3C6EF372UL,
	BLAKE2S_IV3 = 0xA54FF53AUL,
	BLAKE2S_IV4 = 0x510E527FUL,
	BLAKE2S_IV5 = 0x9B05688CUL,
	BLAKE2S_IV6 = 0x1F83D9ABUL,
	BLAKE2S_IV7 = 0x5BE0CD19UL,
पूर्ण;

अटल अंतरभूत व्योम __blake2s_init(काष्ठा blake2s_state *state, माप_प्रकार outlen,
				  स्थिर व्योम *key, माप_प्रकार keylen)
अणु
	state->h[0] = BLAKE2S_IV0 ^ (0x01010000 | keylen << 8 | outlen);
	state->h[1] = BLAKE2S_IV1;
	state->h[2] = BLAKE2S_IV2;
	state->h[3] = BLAKE2S_IV3;
	state->h[4] = BLAKE2S_IV4;
	state->h[5] = BLAKE2S_IV5;
	state->h[6] = BLAKE2S_IV6;
	state->h[7] = BLAKE2S_IV7;
	state->t[0] = 0;
	state->t[1] = 0;
	state->f[0] = 0;
	state->f[1] = 0;
	state->buflen = 0;
	state->outlen = outlen;
	अगर (keylen) अणु
		स_नकल(state->buf, key, keylen);
		स_रखो(&state->buf[keylen], 0, BLAKE2S_BLOCK_SIZE - keylen);
		state->buflen = BLAKE2S_BLOCK_SIZE;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम blake2s_init(काष्ठा blake2s_state *state,
				स्थिर माप_प्रकार outlen)
अणु
	__blake2s_init(state, outlen, शून्य, 0);
पूर्ण

अटल अंतरभूत व्योम blake2s_init_key(काष्ठा blake2s_state *state,
				    स्थिर माप_प्रकार outlen, स्थिर व्योम *key,
				    स्थिर माप_प्रकार keylen)
अणु
	WARN_ON(IS_ENABLED(DEBUG) && (!outlen || outlen > BLAKE2S_HASH_SIZE ||
		!key || !keylen || keylen > BLAKE2S_KEY_SIZE));

	__blake2s_init(state, outlen, key, keylen);
पूर्ण

व्योम blake2s_update(काष्ठा blake2s_state *state, स्थिर u8 *in, माप_प्रकार inlen);
व्योम blake2s_final(काष्ठा blake2s_state *state, u8 *out);

अटल अंतरभूत व्योम blake2s(u8 *out, स्थिर u8 *in, स्थिर u8 *key,
			   स्थिर माप_प्रकार outlen, स्थिर माप_प्रकार inlen,
			   स्थिर माप_प्रकार keylen)
अणु
	काष्ठा blake2s_state state;

	WARN_ON(IS_ENABLED(DEBUG) && ((!in && inlen > 0) || !out || !outlen ||
		outlen > BLAKE2S_HASH_SIZE || keylen > BLAKE2S_KEY_SIZE ||
		(!key && keylen)));

	__blake2s_init(&state, outlen, key, keylen);
	blake2s_update(&state, in, inlen);
	blake2s_final(&state, out);
पूर्ण

व्योम blake2s256_hmac(u8 *out, स्थिर u8 *in, स्थिर u8 *key, स्थिर माप_प्रकार inlen,
		     स्थिर माप_प्रकार keylen);

#पूर्ण_अगर /* _CRYPTO_BLAKE2S_H */
