<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AEGIS common definitions
 *
 * Copyright (c) 2018 Ondrej Mosnacek <omosnacek@gmail.com>
 * Copyright (c) 2018 Red Hat, Inc. All rights reserved.
 */

#अगर_अघोषित _CRYPTO_AEGIS_H
#घोषणा _CRYPTO_AEGIS_H

#समावेश <crypto/aes.h>
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>

#घोषणा AEGIS_BLOCK_SIZE 16

जोड़ aegis_block अणु
	__le64 words64[AEGIS_BLOCK_SIZE / माप(__le64)];
	__le32 words32[AEGIS_BLOCK_SIZE / माप(__le32)];
	u8 bytes[AEGIS_BLOCK_SIZE];
पूर्ण;

काष्ठा aegis_state;

बाह्य पूर्णांक aegis128_have_aes_insn;

#घोषणा AEGIS_BLOCK_ALIGN (__alignof__(जोड़ aegis_block))
#घोषणा AEGIS_ALIGNED(p) IS_ALIGNED((uपूर्णांकptr_t)p, AEGIS_BLOCK_ALIGN)

bool crypto_aegis128_have_simd(व्योम);
व्योम crypto_aegis128_update_simd(काष्ठा aegis_state *state, स्थिर व्योम *msg);
व्योम crypto_aegis128_init_simd(काष्ठा aegis_state *state,
			       स्थिर जोड़ aegis_block *key,
			       स्थिर u8 *iv);
व्योम crypto_aegis128_encrypt_chunk_simd(काष्ठा aegis_state *state, u8 *dst,
					स्थिर u8 *src, अचिन्हित पूर्णांक size);
व्योम crypto_aegis128_decrypt_chunk_simd(काष्ठा aegis_state *state, u8 *dst,
					स्थिर u8 *src, अचिन्हित पूर्णांक size);
पूर्णांक crypto_aegis128_final_simd(काष्ठा aegis_state *state,
			       जोड़ aegis_block *tag_xor,
			       अचिन्हित पूर्णांक assoclen,
			       अचिन्हित पूर्णांक cryptlen,
			       अचिन्हित पूर्णांक authsize);

अटल __always_अंतरभूत व्योम crypto_aegis_block_xor(जोड़ aegis_block *dst,
						   स्थिर जोड़ aegis_block *src)
अणु
	dst->words64[0] ^= src->words64[0];
	dst->words64[1] ^= src->words64[1];
पूर्ण

अटल __always_अंतरभूत व्योम crypto_aegis_block_and(जोड़ aegis_block *dst,
						   स्थिर जोड़ aegis_block *src)
अणु
	dst->words64[0] &= src->words64[0];
	dst->words64[1] &= src->words64[1];
पूर्ण

अटल __always_अंतरभूत व्योम crypto_aegis_aesenc(जोड़ aegis_block *dst,
						स्थिर जोड़ aegis_block *src,
						स्थिर जोड़ aegis_block *key)
अणु
	स्थिर u8  *s  = src->bytes;
	स्थिर u32 *t = crypto_ft_tab[0];
	u32 d0, d1, d2, d3;

	d0 = t[s[ 0]] ^ rol32(t[s[ 5]], 8) ^ rol32(t[s[10]], 16) ^ rol32(t[s[15]], 24);
	d1 = t[s[ 4]] ^ rol32(t[s[ 9]], 8) ^ rol32(t[s[14]], 16) ^ rol32(t[s[ 3]], 24);
	d2 = t[s[ 8]] ^ rol32(t[s[13]], 8) ^ rol32(t[s[ 2]], 16) ^ rol32(t[s[ 7]], 24);
	d3 = t[s[12]] ^ rol32(t[s[ 1]], 8) ^ rol32(t[s[ 6]], 16) ^ rol32(t[s[11]], 24);

	dst->words32[0] = cpu_to_le32(d0) ^ key->words32[0];
	dst->words32[1] = cpu_to_le32(d1) ^ key->words32[1];
	dst->words32[2] = cpu_to_le32(d2) ^ key->words32[2];
	dst->words32[3] = cpu_to_le32(d3) ^ key->words32[3];
पूर्ण

#पूर्ण_अगर /* _CRYPTO_AEGIS_H */
