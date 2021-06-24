<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values and helper functions क्रम the NHPoly1305 hash function.
 */

#अगर_अघोषित _NHPOLY1305_H
#घोषणा _NHPOLY1305_H

#समावेश <crypto/hash.h>
#समावेश <crypto/पूर्णांकernal/poly1305.h>

/* NH parameterization: */

/* Endianness: little */
/* Word size: 32 bits (works well on NEON, SSE2, AVX2) */

/* Stride: 2 words (optimal on ARM32 NEON; works okay on other CPUs too) */
#घोषणा NH_PAIR_STRIDE		2
#घोषणा NH_MESSAGE_UNIT		(NH_PAIR_STRIDE * 2 * माप(u32))

/* Num passes (Toeplitz iteration count): 4, to give Nग = 2^अणु-128पूर्ण */
#घोषणा NH_NUM_PASSES		4
#घोषणा NH_HASH_BYTES		(NH_NUM_PASSES * माप(u64))

/* Max message size: 1024 bytes (32x compression factor) */
#घोषणा NH_NUM_STRIDES		64
#घोषणा NH_MESSAGE_WORDS	(NH_PAIR_STRIDE * 2 * NH_NUM_STRIDES)
#घोषणा NH_MESSAGE_BYTES	(NH_MESSAGE_WORDS * माप(u32))
#घोषणा NH_KEY_WORDS		(NH_MESSAGE_WORDS + \
				 NH_PAIR_STRIDE * 2 * (NH_NUM_PASSES - 1))
#घोषणा NH_KEY_BYTES		(NH_KEY_WORDS * माप(u32))

#घोषणा NHPOLY1305_KEY_SIZE	(POLY1305_BLOCK_SIZE + NH_KEY_BYTES)

काष्ठा nhpoly1305_key अणु
	काष्ठा poly1305_core_key poly_key;
	u32 nh_key[NH_KEY_WORDS];
पूर्ण;

काष्ठा nhpoly1305_state अणु

	/* Running total of polynomial evaluation */
	काष्ठा poly1305_state poly_state;

	/* Partial block buffer */
	u8 buffer[NH_MESSAGE_UNIT];
	अचिन्हित पूर्णांक buflen;

	/*
	 * Number of bytes reमुख्यing until the current NH message reaches
	 * NH_MESSAGE_BYTES.  When nonzero, 'nh_hash' holds the partial NH hash.
	 */
	अचिन्हित पूर्णांक nh_reमुख्यing;

	__le64 nh_hash[NH_NUM_PASSES];
पूर्ण;

प्रकार व्योम (*nh_t)(स्थिर u32 *key, स्थिर u8 *message, माप_प्रकार message_len,
		     __le64 hash[NH_NUM_PASSES]);

पूर्णांक crypto_nhpoly1305_setkey(काष्ठा crypto_shash *tfm,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen);

पूर्णांक crypto_nhpoly1305_init(काष्ठा shash_desc *desc);
पूर्णांक crypto_nhpoly1305_update(काष्ठा shash_desc *desc,
			     स्थिर u8 *src, अचिन्हित पूर्णांक srclen);
पूर्णांक crypto_nhpoly1305_update_helper(काष्ठा shash_desc *desc,
				    स्थिर u8 *src, अचिन्हित पूर्णांक srclen,
				    nh_t nh_fn);
पूर्णांक crypto_nhpoly1305_final(काष्ठा shash_desc *desc, u8 *dst);
पूर्णांक crypto_nhpoly1305_final_helper(काष्ठा shash_desc *desc, u8 *dst,
				   nh_t nh_fn);

#पूर्ण_अगर /* _NHPOLY1305_H */
