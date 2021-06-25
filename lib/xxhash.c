<शैली गुरु>
/*
 * xxHash - Extremely Fast Hash algorithm
 * Copyright (C) 2012-2016, Yann Collet.
 *
 * BSD 2-Clause License (http://www.खोलोsource.org/licenses/bsd-license.php)
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above
 *     copyright notice, this list of conditions and the following disclaimer
 *     in the करोcumentation and/or other materials provided with the
 *     distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it under
 * the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation. This program is dual-licensed; you may select
 * either version 2 of the GNU General Public License ("GPL") or BSD license
 * ("BSD").
 *
 * You can contact the author at:
 * - xxHash homepage: https://cyan4973.github.io/xxHash/
 * - xxHash source repository: https://github.com/Cyan4973/xxHash
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/xxhash.h>

/*-*************************************
 * Macros
 **************************************/
#घोषणा xxh_rotl32(x, r) ((x << r) | (x >> (32 - r)))
#घोषणा xxh_rotl64(x, r) ((x << r) | (x >> (64 - r)))

#अगर_घोषित __LITTLE_ENDIAN
# define XXH_CPU_LITTLE_ENDIAN 1
#अन्यथा
# define XXH_CPU_LITTLE_ENDIAN 0
#पूर्ण_अगर

/*-*************************************
 * Constants
 **************************************/
अटल स्थिर uपूर्णांक32_t PRIME32_1 = 2654435761U;
अटल स्थिर uपूर्णांक32_t PRIME32_2 = 2246822519U;
अटल स्थिर uपूर्णांक32_t PRIME32_3 = 3266489917U;
अटल स्थिर uपूर्णांक32_t PRIME32_4 =  668265263U;
अटल स्थिर uपूर्णांक32_t PRIME32_5 =  374761393U;

अटल स्थिर uपूर्णांक64_t PRIME64_1 = 11400714785074694791ULL;
अटल स्थिर uपूर्णांक64_t PRIME64_2 = 14029467366897019727ULL;
अटल स्थिर uपूर्णांक64_t PRIME64_3 =  1609587929392839161ULL;
अटल स्थिर uपूर्णांक64_t PRIME64_4 =  9650029242287828579ULL;
अटल स्थिर uपूर्णांक64_t PRIME64_5 =  2870177450012600261ULL;

/*-**************************
 *  Utils
 ***************************/
व्योम xxh32_copy_state(काष्ठा xxh32_state *dst, स्थिर काष्ठा xxh32_state *src)
अणु
	स_नकल(dst, src, माप(*dst));
पूर्ण
EXPORT_SYMBOL(xxh32_copy_state);

व्योम xxh64_copy_state(काष्ठा xxh64_state *dst, स्थिर काष्ठा xxh64_state *src)
अणु
	स_नकल(dst, src, माप(*dst));
पूर्ण
EXPORT_SYMBOL(xxh64_copy_state);

/*-***************************
 * Simple Hash Functions
 ****************************/
अटल uपूर्णांक32_t xxh32_round(uपूर्णांक32_t seed, स्थिर uपूर्णांक32_t input)
अणु
	seed += input * PRIME32_2;
	seed = xxh_rotl32(seed, 13);
	seed *= PRIME32_1;
	वापस seed;
पूर्ण

uपूर्णांक32_t xxh32(स्थिर व्योम *input, स्थिर माप_प्रकार len, स्थिर uपूर्णांक32_t seed)
अणु
	स्थिर uपूर्णांक8_t *p = (स्थिर uपूर्णांक8_t *)input;
	स्थिर uपूर्णांक8_t *b_end = p + len;
	uपूर्णांक32_t h32;

	अगर (len >= 16) अणु
		स्थिर uपूर्णांक8_t *स्थिर limit = b_end - 16;
		uपूर्णांक32_t v1 = seed + PRIME32_1 + PRIME32_2;
		uपूर्णांक32_t v2 = seed + PRIME32_2;
		uपूर्णांक32_t v3 = seed + 0;
		uपूर्णांक32_t v4 = seed - PRIME32_1;

		करो अणु
			v1 = xxh32_round(v1, get_unaligned_le32(p));
			p += 4;
			v2 = xxh32_round(v2, get_unaligned_le32(p));
			p += 4;
			v3 = xxh32_round(v3, get_unaligned_le32(p));
			p += 4;
			v4 = xxh32_round(v4, get_unaligned_le32(p));
			p += 4;
		पूर्ण जबतक (p <= limit);

		h32 = xxh_rotl32(v1, 1) + xxh_rotl32(v2, 7) +
			xxh_rotl32(v3, 12) + xxh_rotl32(v4, 18);
	पूर्ण अन्यथा अणु
		h32 = seed + PRIME32_5;
	पूर्ण

	h32 += (uपूर्णांक32_t)len;

	जबतक (p + 4 <= b_end) अणु
		h32 += get_unaligned_le32(p) * PRIME32_3;
		h32 = xxh_rotl32(h32, 17) * PRIME32_4;
		p += 4;
	पूर्ण

	जबतक (p < b_end) अणु
		h32 += (*p) * PRIME32_5;
		h32 = xxh_rotl32(h32, 11) * PRIME32_1;
		p++;
	पूर्ण

	h32 ^= h32 >> 15;
	h32 *= PRIME32_2;
	h32 ^= h32 >> 13;
	h32 *= PRIME32_3;
	h32 ^= h32 >> 16;

	वापस h32;
पूर्ण
EXPORT_SYMBOL(xxh32);

अटल uपूर्णांक64_t xxh64_round(uपूर्णांक64_t acc, स्थिर uपूर्णांक64_t input)
अणु
	acc += input * PRIME64_2;
	acc = xxh_rotl64(acc, 31);
	acc *= PRIME64_1;
	वापस acc;
पूर्ण

अटल uपूर्णांक64_t xxh64_merge_round(uपूर्णांक64_t acc, uपूर्णांक64_t val)
अणु
	val = xxh64_round(0, val);
	acc ^= val;
	acc = acc * PRIME64_1 + PRIME64_4;
	वापस acc;
पूर्ण

uपूर्णांक64_t xxh64(स्थिर व्योम *input, स्थिर माप_प्रकार len, स्थिर uपूर्णांक64_t seed)
अणु
	स्थिर uपूर्णांक8_t *p = (स्थिर uपूर्णांक8_t *)input;
	स्थिर uपूर्णांक8_t *स्थिर b_end = p + len;
	uपूर्णांक64_t h64;

	अगर (len >= 32) अणु
		स्थिर uपूर्णांक8_t *स्थिर limit = b_end - 32;
		uपूर्णांक64_t v1 = seed + PRIME64_1 + PRIME64_2;
		uपूर्णांक64_t v2 = seed + PRIME64_2;
		uपूर्णांक64_t v3 = seed + 0;
		uपूर्णांक64_t v4 = seed - PRIME64_1;

		करो अणु
			v1 = xxh64_round(v1, get_unaligned_le64(p));
			p += 8;
			v2 = xxh64_round(v2, get_unaligned_le64(p));
			p += 8;
			v3 = xxh64_round(v3, get_unaligned_le64(p));
			p += 8;
			v4 = xxh64_round(v4, get_unaligned_le64(p));
			p += 8;
		पूर्ण जबतक (p <= limit);

		h64 = xxh_rotl64(v1, 1) + xxh_rotl64(v2, 7) +
			xxh_rotl64(v3, 12) + xxh_rotl64(v4, 18);
		h64 = xxh64_merge_round(h64, v1);
		h64 = xxh64_merge_round(h64, v2);
		h64 = xxh64_merge_round(h64, v3);
		h64 = xxh64_merge_round(h64, v4);

	पूर्ण अन्यथा अणु
		h64  = seed + PRIME64_5;
	पूर्ण

	h64 += (uपूर्णांक64_t)len;

	जबतक (p + 8 <= b_end) अणु
		स्थिर uपूर्णांक64_t k1 = xxh64_round(0, get_unaligned_le64(p));

		h64 ^= k1;
		h64 = xxh_rotl64(h64, 27) * PRIME64_1 + PRIME64_4;
		p += 8;
	पूर्ण

	अगर (p + 4 <= b_end) अणु
		h64 ^= (uपूर्णांक64_t)(get_unaligned_le32(p)) * PRIME64_1;
		h64 = xxh_rotl64(h64, 23) * PRIME64_2 + PRIME64_3;
		p += 4;
	पूर्ण

	जबतक (p < b_end) अणु
		h64 ^= (*p) * PRIME64_5;
		h64 = xxh_rotl64(h64, 11) * PRIME64_1;
		p++;
	पूर्ण

	h64 ^= h64 >> 33;
	h64 *= PRIME64_2;
	h64 ^= h64 >> 29;
	h64 *= PRIME64_3;
	h64 ^= h64 >> 32;

	वापस h64;
पूर्ण
EXPORT_SYMBOL(xxh64);

/*-**************************************************
 * Advanced Hash Functions
 ***************************************************/
व्योम xxh32_reset(काष्ठा xxh32_state *statePtr, स्थिर uपूर्णांक32_t seed)
अणु
	/* use a local state क्रम स_नकल() to aव्योम strict-aliasing warnings */
	काष्ठा xxh32_state state;

	स_रखो(&state, 0, माप(state));
	state.v1 = seed + PRIME32_1 + PRIME32_2;
	state.v2 = seed + PRIME32_2;
	state.v3 = seed + 0;
	state.v4 = seed - PRIME32_1;
	स_नकल(statePtr, &state, माप(state));
पूर्ण
EXPORT_SYMBOL(xxh32_reset);

व्योम xxh64_reset(काष्ठा xxh64_state *statePtr, स्थिर uपूर्णांक64_t seed)
अणु
	/* use a local state क्रम स_नकल() to aव्योम strict-aliasing warnings */
	काष्ठा xxh64_state state;

	स_रखो(&state, 0, माप(state));
	state.v1 = seed + PRIME64_1 + PRIME64_2;
	state.v2 = seed + PRIME64_2;
	state.v3 = seed + 0;
	state.v4 = seed - PRIME64_1;
	स_नकल(statePtr, &state, माप(state));
पूर्ण
EXPORT_SYMBOL(xxh64_reset);

पूर्णांक xxh32_update(काष्ठा xxh32_state *state, स्थिर व्योम *input, स्थिर माप_प्रकार len)
अणु
	स्थिर uपूर्णांक8_t *p = (स्थिर uपूर्णांक8_t *)input;
	स्थिर uपूर्णांक8_t *स्थिर b_end = p + len;

	अगर (input == शून्य)
		वापस -EINVAL;

	state->total_len_32 += (uपूर्णांक32_t)len;
	state->large_len |= (len >= 16) | (state->total_len_32 >= 16);

	अगर (state->memsize + len < 16) अणु /* fill in पंचांगp buffer */
		स_नकल((uपूर्णांक8_t *)(state->mem32) + state->memsize, input, len);
		state->memsize += (uपूर्णांक32_t)len;
		वापस 0;
	पूर्ण

	अगर (state->memsize) अणु /* some data left from previous update */
		स्थिर uपूर्णांक32_t *p32 = state->mem32;

		स_नकल((uपूर्णांक8_t *)(state->mem32) + state->memsize, input,
			16 - state->memsize);

		state->v1 = xxh32_round(state->v1, get_unaligned_le32(p32));
		p32++;
		state->v2 = xxh32_round(state->v2, get_unaligned_le32(p32));
		p32++;
		state->v3 = xxh32_round(state->v3, get_unaligned_le32(p32));
		p32++;
		state->v4 = xxh32_round(state->v4, get_unaligned_le32(p32));
		p32++;

		p += 16-state->memsize;
		state->memsize = 0;
	पूर्ण

	अगर (p <= b_end - 16) अणु
		स्थिर uपूर्णांक8_t *स्थिर limit = b_end - 16;
		uपूर्णांक32_t v1 = state->v1;
		uपूर्णांक32_t v2 = state->v2;
		uपूर्णांक32_t v3 = state->v3;
		uपूर्णांक32_t v4 = state->v4;

		करो अणु
			v1 = xxh32_round(v1, get_unaligned_le32(p));
			p += 4;
			v2 = xxh32_round(v2, get_unaligned_le32(p));
			p += 4;
			v3 = xxh32_round(v3, get_unaligned_le32(p));
			p += 4;
			v4 = xxh32_round(v4, get_unaligned_le32(p));
			p += 4;
		पूर्ण जबतक (p <= limit);

		state->v1 = v1;
		state->v2 = v2;
		state->v3 = v3;
		state->v4 = v4;
	पूर्ण

	अगर (p < b_end) अणु
		स_नकल(state->mem32, p, (माप_प्रकार)(b_end-p));
		state->memsize = (uपूर्णांक32_t)(b_end-p);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xxh32_update);

uपूर्णांक32_t xxh32_digest(स्थिर काष्ठा xxh32_state *state)
अणु
	स्थिर uपूर्णांक8_t *p = (स्थिर uपूर्णांक8_t *)state->mem32;
	स्थिर uपूर्णांक8_t *स्थिर b_end = (स्थिर uपूर्णांक8_t *)(state->mem32) +
		state->memsize;
	uपूर्णांक32_t h32;

	अगर (state->large_len) अणु
		h32 = xxh_rotl32(state->v1, 1) + xxh_rotl32(state->v2, 7) +
			xxh_rotl32(state->v3, 12) + xxh_rotl32(state->v4, 18);
	पूर्ण अन्यथा अणु
		h32 = state->v3 /* == seed */ + PRIME32_5;
	पूर्ण

	h32 += state->total_len_32;

	जबतक (p + 4 <= b_end) अणु
		h32 += get_unaligned_le32(p) * PRIME32_3;
		h32 = xxh_rotl32(h32, 17) * PRIME32_4;
		p += 4;
	पूर्ण

	जबतक (p < b_end) अणु
		h32 += (*p) * PRIME32_5;
		h32 = xxh_rotl32(h32, 11) * PRIME32_1;
		p++;
	पूर्ण

	h32 ^= h32 >> 15;
	h32 *= PRIME32_2;
	h32 ^= h32 >> 13;
	h32 *= PRIME32_3;
	h32 ^= h32 >> 16;

	वापस h32;
पूर्ण
EXPORT_SYMBOL(xxh32_digest);

पूर्णांक xxh64_update(काष्ठा xxh64_state *state, स्थिर व्योम *input, स्थिर माप_प्रकार len)
अणु
	स्थिर uपूर्णांक8_t *p = (स्थिर uपूर्णांक8_t *)input;
	स्थिर uपूर्णांक8_t *स्थिर b_end = p + len;

	अगर (input == शून्य)
		वापस -EINVAL;

	state->total_len += len;

	अगर (state->memsize + len < 32) अणु /* fill in पंचांगp buffer */
		स_नकल(((uपूर्णांक8_t *)state->mem64) + state->memsize, input, len);
		state->memsize += (uपूर्णांक32_t)len;
		वापस 0;
	पूर्ण

	अगर (state->memsize) अणु /* पंचांगp buffer is full */
		uपूर्णांक64_t *p64 = state->mem64;

		स_नकल(((uपूर्णांक8_t *)p64) + state->memsize, input,
			32 - state->memsize);

		state->v1 = xxh64_round(state->v1, get_unaligned_le64(p64));
		p64++;
		state->v2 = xxh64_round(state->v2, get_unaligned_le64(p64));
		p64++;
		state->v3 = xxh64_round(state->v3, get_unaligned_le64(p64));
		p64++;
		state->v4 = xxh64_round(state->v4, get_unaligned_le64(p64));

		p += 32 - state->memsize;
		state->memsize = 0;
	पूर्ण

	अगर (p + 32 <= b_end) अणु
		स्थिर uपूर्णांक8_t *स्थिर limit = b_end - 32;
		uपूर्णांक64_t v1 = state->v1;
		uपूर्णांक64_t v2 = state->v2;
		uपूर्णांक64_t v3 = state->v3;
		uपूर्णांक64_t v4 = state->v4;

		करो अणु
			v1 = xxh64_round(v1, get_unaligned_le64(p));
			p += 8;
			v2 = xxh64_round(v2, get_unaligned_le64(p));
			p += 8;
			v3 = xxh64_round(v3, get_unaligned_le64(p));
			p += 8;
			v4 = xxh64_round(v4, get_unaligned_le64(p));
			p += 8;
		पूर्ण जबतक (p <= limit);

		state->v1 = v1;
		state->v2 = v2;
		state->v3 = v3;
		state->v4 = v4;
	पूर्ण

	अगर (p < b_end) अणु
		स_नकल(state->mem64, p, (माप_प्रकार)(b_end-p));
		state->memsize = (uपूर्णांक32_t)(b_end - p);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xxh64_update);

uपूर्णांक64_t xxh64_digest(स्थिर काष्ठा xxh64_state *state)
अणु
	स्थिर uपूर्णांक8_t *p = (स्थिर uपूर्णांक8_t *)state->mem64;
	स्थिर uपूर्णांक8_t *स्थिर b_end = (स्थिर uपूर्णांक8_t *)state->mem64 +
		state->memsize;
	uपूर्णांक64_t h64;

	अगर (state->total_len >= 32) अणु
		स्थिर uपूर्णांक64_t v1 = state->v1;
		स्थिर uपूर्णांक64_t v2 = state->v2;
		स्थिर uपूर्णांक64_t v3 = state->v3;
		स्थिर uपूर्णांक64_t v4 = state->v4;

		h64 = xxh_rotl64(v1, 1) + xxh_rotl64(v2, 7) +
			xxh_rotl64(v3, 12) + xxh_rotl64(v4, 18);
		h64 = xxh64_merge_round(h64, v1);
		h64 = xxh64_merge_round(h64, v2);
		h64 = xxh64_merge_round(h64, v3);
		h64 = xxh64_merge_round(h64, v4);
	पूर्ण अन्यथा अणु
		h64  = state->v3 + PRIME64_5;
	पूर्ण

	h64 += (uपूर्णांक64_t)state->total_len;

	जबतक (p + 8 <= b_end) अणु
		स्थिर uपूर्णांक64_t k1 = xxh64_round(0, get_unaligned_le64(p));

		h64 ^= k1;
		h64 = xxh_rotl64(h64, 27) * PRIME64_1 + PRIME64_4;
		p += 8;
	पूर्ण

	अगर (p + 4 <= b_end) अणु
		h64 ^= (uपूर्णांक64_t)(get_unaligned_le32(p)) * PRIME64_1;
		h64 = xxh_rotl64(h64, 23) * PRIME64_2 + PRIME64_3;
		p += 4;
	पूर्ण

	जबतक (p < b_end) अणु
		h64 ^= (*p) * PRIME64_5;
		h64 = xxh_rotl64(h64, 11) * PRIME64_1;
		p++;
	पूर्ण

	h64 ^= h64 >> 33;
	h64 *= PRIME64_2;
	h64 ^= h64 >> 29;
	h64 *= PRIME64_3;
	h64 ^= h64 >> 32;

	वापस h64;
पूर्ण
EXPORT_SYMBOL(xxh64_digest);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("xxHash");
