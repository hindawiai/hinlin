<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2019 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 */

#अगर_घोषित CONFIG_ARM64
#समावेश <यंत्र/neon-पूर्णांकrinsics.h>

#घोषणा AES_ROUND	"aese %0.16b, %1.16b \n\t aesmc %0.16b, %0.16b"
#अन्यथा
#समावेश <arm_neon.h>

#घोषणा AES_ROUND	"aese.8 %q0, %q1 \n\t aesmc.8 %q0, %q0"
#पूर्ण_अगर

#घोषणा AEGIS_BLOCK_SIZE	16

#समावेश <मानकघोष.स>

बाह्य पूर्णांक aegis128_have_aes_insn;

व्योम *स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n);

काष्ठा aegis128_state अणु
	uपूर्णांक8x16_t v[5];
पूर्ण;

बाह्य स्थिर uपूर्णांक8_t crypto_aes_sbox[];

अटल काष्ठा aegis128_state aegis128_load_state_neon(स्थिर व्योम *state)
अणु
	वापस (काष्ठा aegis128_state)अणु अणु
		vld1q_u8(state),
		vld1q_u8(state + 16),
		vld1q_u8(state + 32),
		vld1q_u8(state + 48),
		vld1q_u8(state + 64)
	पूर्ण पूर्ण;
पूर्ण

अटल व्योम aegis128_save_state_neon(काष्ठा aegis128_state st, व्योम *state)
अणु
	vst1q_u8(state, st.v[0]);
	vst1q_u8(state + 16, st.v[1]);
	vst1q_u8(state + 32, st.v[2]);
	vst1q_u8(state + 48, st.v[3]);
	vst1q_u8(state + 64, st.v[4]);
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
uपूर्णांक8x16_t aegis_aes_round(uपूर्णांक8x16_t w)
अणु
	uपूर्णांक8x16_t z = अणुपूर्ण;

#अगर_घोषित CONFIG_ARM64
	अगर (!__builtin_expect(aegis128_have_aes_insn, 1)) अणु
		अटल स्थिर uपूर्णांक8_t shअगरt_rows[] = अणु
			0x0, 0x5, 0xa, 0xf, 0x4, 0x9, 0xe, 0x3,
			0x8, 0xd, 0x2, 0x7, 0xc, 0x1, 0x6, 0xb,
		पूर्ण;
		अटल स्थिर uपूर्णांक8_t ror32by8[] = अणु
			0x1, 0x2, 0x3, 0x0, 0x5, 0x6, 0x7, 0x4,
			0x9, 0xa, 0xb, 0x8, 0xd, 0xe, 0xf, 0xc,
		पूर्ण;
		uपूर्णांक8x16_t v;

		// shअगरt rows
		w = vqtbl1q_u8(w, vld1q_u8(shअगरt_rows));

		// sub bytes
#अगर_अघोषित CONFIG_CC_IS_GCC
		v = vqtbl4q_u8(vld1q_u8_x4(crypto_aes_sbox), w);
		v = vqtbx4q_u8(v, vld1q_u8_x4(crypto_aes_sbox + 0x40), w - 0x40);
		v = vqtbx4q_u8(v, vld1q_u8_x4(crypto_aes_sbox + 0x80), w - 0x80);
		v = vqtbx4q_u8(v, vld1q_u8_x4(crypto_aes_sbox + 0xc0), w - 0xc0);
#अन्यथा
		यंत्र("tbl %0.16b, {v16.16b-v19.16b}, %1.16b" : "=w"(v) : "w"(w));
		w -= 0x40;
		यंत्र("tbx %0.16b, {v20.16b-v23.16b}, %1.16b" : "+w"(v) : "w"(w));
		w -= 0x40;
		यंत्र("tbx %0.16b, {v24.16b-v27.16b}, %1.16b" : "+w"(v) : "w"(w));
		w -= 0x40;
		यंत्र("tbx %0.16b, {v28.16b-v31.16b}, %1.16b" : "+w"(v) : "w"(w));
#पूर्ण_अगर

		// mix columns
		w = (v << 1) ^ (uपूर्णांक8x16_t)(((पूर्णांक8x16_t)v >> 7) & 0x1b);
		w ^= (uपूर्णांक8x16_t)vrev32q_u16((uपूर्णांक16x8_t)v);
		w ^= vqtbl1q_u8(v ^ w, vld1q_u8(ror32by8));

		वापस w;
	पूर्ण
#पूर्ण_अगर

	/*
	 * We use अंतरभूत यंत्र here instead of the vaeseq_u8/vaesmcq_u8 पूर्णांकrinsics
	 * to क्रमce the compiler to issue the aese/aesmc inकाष्ठाions in pairs.
	 * This is much faster on many cores, where the inकाष्ठाion pair can
	 * execute in a single cycle.
	 */
	यंत्र(AES_ROUND : "+w"(w) : "w"(z));
	वापस w;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
काष्ठा aegis128_state aegis128_update_neon(काष्ठा aegis128_state st,
					   uपूर्णांक8x16_t m)
अणु
	m       ^= aegis_aes_round(st.v[4]);
	st.v[4] ^= aegis_aes_round(st.v[3]);
	st.v[3] ^= aegis_aes_round(st.v[2]);
	st.v[2] ^= aegis_aes_round(st.v[1]);
	st.v[1] ^= aegis_aes_round(st.v[0]);
	st.v[0] ^= m;

	वापस st;
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
व्योम preload_sbox(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_ARM64) ||
	    !IS_ENABLED(CONFIG_CC_IS_GCC) ||
	    __builtin_expect(aegis128_have_aes_insn, 1))
		वापस;

	यंत्र("ld1	{v16.16b-v19.16b}, [%0], #64	\n\t"
	    "ld1	{v20.16b-v23.16b}, [%0], #64	\n\t"
	    "ld1	{v24.16b-v27.16b}, [%0], #64	\n\t"
	    "ld1	{v28.16b-v31.16b}, [%0]		\n\t"
	    :: "r"(crypto_aes_sbox));
पूर्ण

व्योम crypto_aegis128_init_neon(व्योम *state, स्थिर व्योम *key, स्थिर व्योम *iv)
अणु
	अटल स्थिर uपूर्णांक8_t स्थिर0[] = अणु
		0x00, 0x01, 0x01, 0x02, 0x03, 0x05, 0x08, 0x0d,
		0x15, 0x22, 0x37, 0x59, 0x90, 0xe9, 0x79, 0x62,
	पूर्ण;
	अटल स्थिर uपूर्णांक8_t स्थिर1[] = अणु
		0xdb, 0x3d, 0x18, 0x55, 0x6d, 0xc2, 0x2f, 0xf1,
		0x20, 0x11, 0x31, 0x42, 0x73, 0xb5, 0x28, 0xdd,
	पूर्ण;
	uपूर्णांक8x16_t k = vld1q_u8(key);
	uपूर्णांक8x16_t kiv = k ^ vld1q_u8(iv);
	काष्ठा aegis128_state st = अणुअणु
		kiv,
		vld1q_u8(स्थिर1),
		vld1q_u8(स्थिर0),
		k ^ vld1q_u8(स्थिर0),
		k ^ vld1q_u8(स्थिर1),
	पूर्णपूर्ण;
	पूर्णांक i;

	preload_sbox();

	क्रम (i = 0; i < 5; i++) अणु
		st = aegis128_update_neon(st, k);
		st = aegis128_update_neon(st, kiv);
	पूर्ण
	aegis128_save_state_neon(st, state);
पूर्ण

व्योम crypto_aegis128_update_neon(व्योम *state, स्थिर व्योम *msg)
अणु
	काष्ठा aegis128_state st = aegis128_load_state_neon(state);

	preload_sbox();

	st = aegis128_update_neon(st, vld1q_u8(msg));

	aegis128_save_state_neon(st, state);
पूर्ण

#अगर_घोषित CONFIG_ARM
/*
 * AArch32 करोes not provide these पूर्णांकrinsics natively because it करोes not
 * implement the underlying inकाष्ठाions. AArch32 only provides 64-bit
 * wide vtbl.8/vtbx.8 inकाष्ठाion, so use those instead.
 */
अटल uपूर्णांक8x16_t vqtbl1q_u8(uपूर्णांक8x16_t a, uपूर्णांक8x16_t b)
अणु
	जोड़ अणु
		uपूर्णांक8x16_t	val;
		uपूर्णांक8x8x2_t	pair;
	पूर्ण __a = अणु a पूर्ण;

	वापस vcombine_u8(vtbl2_u8(__a.pair, vget_low_u8(b)),
			   vtbl2_u8(__a.pair, vget_high_u8(b)));
पूर्ण

अटल uपूर्णांक8x16_t vqtbx1q_u8(uपूर्णांक8x16_t v, uपूर्णांक8x16_t a, uपूर्णांक8x16_t b)
अणु
	जोड़ अणु
		uपूर्णांक8x16_t	val;
		uपूर्णांक8x8x2_t	pair;
	पूर्ण __a = अणु a पूर्ण;

	वापस vcombine_u8(vtbx2_u8(vget_low_u8(v), __a.pair, vget_low_u8(b)),
			   vtbx2_u8(vget_high_u8(v), __a.pair, vget_high_u8(b)));
पूर्ण

अटल पूर्णांक8_t vminvq_s8(पूर्णांक8x16_t v)
अणु
	पूर्णांक8x8_t s = vpmin_s8(vget_low_s8(v), vget_high_s8(v));

	s = vpmin_s8(s, s);
	s = vpmin_s8(s, s);
	s = vpmin_s8(s, s);

	वापस vget_lane_s8(s, 0);
पूर्ण
#पूर्ण_अगर

अटल स्थिर uपूर्णांक8_t permute[] __aligned(64) = अणु
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
पूर्ण;

व्योम crypto_aegis128_encrypt_chunk_neon(व्योम *state, व्योम *dst, स्थिर व्योम *src,
					अचिन्हित पूर्णांक size)
अणु
	काष्ठा aegis128_state st = aegis128_load_state_neon(state);
	स्थिर पूर्णांक लघु_input = size < AEGIS_BLOCK_SIZE;
	uपूर्णांक8x16_t msg;

	preload_sbox();

	जबतक (size >= AEGIS_BLOCK_SIZE) अणु
		uपूर्णांक8x16_t s = st.v[1] ^ (st.v[2] & st.v[3]) ^ st.v[4];

		msg = vld1q_u8(src);
		st = aegis128_update_neon(st, msg);
		msg ^= s;
		vst1q_u8(dst, msg);

		size -= AEGIS_BLOCK_SIZE;
		src += AEGIS_BLOCK_SIZE;
		dst += AEGIS_BLOCK_SIZE;
	पूर्ण

	अगर (size > 0) अणु
		uपूर्णांक8x16_t s = st.v[1] ^ (st.v[2] & st.v[3]) ^ st.v[4];
		uपूर्णांक8_t buf[AEGIS_BLOCK_SIZE];
		स्थिर व्योम *in = src;
		व्योम *out = dst;
		uपूर्णांक8x16_t m;

		अगर (__builtin_expect(लघु_input, 0))
			in = out = स_नकल(buf + AEGIS_BLOCK_SIZE - size, src, size);

		m = vqtbl1q_u8(vld1q_u8(in + size - AEGIS_BLOCK_SIZE),
			       vld1q_u8(permute + 32 - size));

		st = aegis128_update_neon(st, m);

		vst1q_u8(out + size - AEGIS_BLOCK_SIZE,
			 vqtbl1q_u8(m ^ s, vld1q_u8(permute + size)));

		अगर (__builtin_expect(लघु_input, 0))
			स_नकल(dst, out, size);
		अन्यथा
			vst1q_u8(out - AEGIS_BLOCK_SIZE, msg);
	पूर्ण

	aegis128_save_state_neon(st, state);
पूर्ण

व्योम crypto_aegis128_decrypt_chunk_neon(व्योम *state, व्योम *dst, स्थिर व्योम *src,
					अचिन्हित पूर्णांक size)
अणु
	काष्ठा aegis128_state st = aegis128_load_state_neon(state);
	स्थिर पूर्णांक लघु_input = size < AEGIS_BLOCK_SIZE;
	uपूर्णांक8x16_t msg;

	preload_sbox();

	जबतक (size >= AEGIS_BLOCK_SIZE) अणु
		msg = vld1q_u8(src) ^ st.v[1] ^ (st.v[2] & st.v[3]) ^ st.v[4];
		st = aegis128_update_neon(st, msg);
		vst1q_u8(dst, msg);

		size -= AEGIS_BLOCK_SIZE;
		src += AEGIS_BLOCK_SIZE;
		dst += AEGIS_BLOCK_SIZE;
	पूर्ण

	अगर (size > 0) अणु
		uपूर्णांक8x16_t s = st.v[1] ^ (st.v[2] & st.v[3]) ^ st.v[4];
		uपूर्णांक8_t buf[AEGIS_BLOCK_SIZE];
		स्थिर व्योम *in = src;
		व्योम *out = dst;
		uपूर्णांक8x16_t m;

		अगर (__builtin_expect(लघु_input, 0))
			in = out = स_नकल(buf + AEGIS_BLOCK_SIZE - size, src, size);

		m = s ^ vqtbx1q_u8(s, vld1q_u8(in + size - AEGIS_BLOCK_SIZE),
				   vld1q_u8(permute + 32 - size));

		st = aegis128_update_neon(st, m);

		vst1q_u8(out + size - AEGIS_BLOCK_SIZE,
			 vqtbl1q_u8(m, vld1q_u8(permute + size)));

		अगर (__builtin_expect(लघु_input, 0))
			स_नकल(dst, out, size);
		अन्यथा
			vst1q_u8(out - AEGIS_BLOCK_SIZE, msg);
	पूर्ण

	aegis128_save_state_neon(st, state);
पूर्ण

पूर्णांक crypto_aegis128_final_neon(व्योम *state, व्योम *tag_xor,
			       अचिन्हित पूर्णांक assoclen,
			       अचिन्हित पूर्णांक cryptlen,
			       अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा aegis128_state st = aegis128_load_state_neon(state);
	uपूर्णांक8x16_t v;
	पूर्णांक i;

	preload_sbox();

	v = st.v[3] ^ (uपूर्णांक8x16_t)vcombine_u64(vmov_n_u64(8ULL * assoclen),
					       vmov_n_u64(8ULL * cryptlen));

	क्रम (i = 0; i < 7; i++)
		st = aegis128_update_neon(st, v);

	v = st.v[0] ^ st.v[1] ^ st.v[2] ^ st.v[3] ^ st.v[4];

	अगर (authsize > 0) अणु
		v = vqtbl1q_u8(~vceqq_u8(v, vld1q_u8(tag_xor)),
			       vld1q_u8(permute + authsize));

		वापस vminvq_s8((पूर्णांक8x16_t)v);
	पूर्ण

	vst1q_u8(tag_xor, v);
	वापस 0;
पूर्ण
