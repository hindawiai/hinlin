<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values and helper functions क्रम the ChaCha and XChaCha stream ciphers.
 *
 * XChaCha extends ChaCha's nonce to 192 bits, while provably retaining ChaCha's
 * security.  Here they share the same key size, tfm context, and setkey
 * function; only their IV size and encrypt/decrypt function dअगरfer.
 *
 * The ChaCha paper specअगरies 20, 12, and 8-round variants.  In general, it is
 * recommended to use the 20-round variant ChaCha20.  However, the other
 * variants can be needed in some perक्रमmance-sensitive scenarios.  The generic
 * ChaCha code currently allows only the 20 and 12-round variants.
 */

#अगर_अघोषित _CRYPTO_CHACHA_H
#घोषणा _CRYPTO_CHACHA_H

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/types.h>

/* 32-bit stream position, then 96-bit nonce (RFC7539 convention) */
#घोषणा CHACHA_IV_SIZE		16

#घोषणा CHACHA_KEY_SIZE		32
#घोषणा CHACHA_BLOCK_SIZE	64
#घोषणा CHACHAPOLY_IV_SIZE	12

#घोषणा CHACHA_STATE_WORDS	(CHACHA_BLOCK_SIZE / माप(u32))

/* 192-bit nonce, then 64-bit stream position */
#घोषणा XCHACHA_IV_SIZE		32

व्योम chacha_block_generic(u32 *state, u8 *stream, पूर्णांक nrounds);
अटल अंतरभूत व्योम chacha20_block(u32 *state, u8 *stream)
अणु
	chacha_block_generic(state, stream, 20);
पूर्ण

व्योम hchacha_block_arch(स्थिर u32 *state, u32 *out, पूर्णांक nrounds);
व्योम hchacha_block_generic(स्थिर u32 *state, u32 *out, पूर्णांक nrounds);

अटल अंतरभूत व्योम hchacha_block(स्थिर u32 *state, u32 *out, पूर्णांक nrounds)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_CHACHA))
		hchacha_block_arch(state, out, nrounds);
	अन्यथा
		hchacha_block_generic(state, out, nrounds);
पूर्ण

अटल अंतरभूत व्योम chacha_init_स्थिरs(u32 *state)
अणु
	state[0]  = 0x61707865; /* "expa" */
	state[1]  = 0x3320646e; /* "nd 3" */
	state[2]  = 0x79622d32; /* "2-by" */
	state[3]  = 0x6b206574; /* "te k" */
पूर्ण

व्योम chacha_init_arch(u32 *state, स्थिर u32 *key, स्थिर u8 *iv);
अटल अंतरभूत व्योम chacha_init_generic(u32 *state, स्थिर u32 *key, स्थिर u8 *iv)
अणु
	chacha_init_स्थिरs(state);
	state[4]  = key[0];
	state[5]  = key[1];
	state[6]  = key[2];
	state[7]  = key[3];
	state[8]  = key[4];
	state[9]  = key[5];
	state[10] = key[6];
	state[11] = key[7];
	state[12] = get_unaligned_le32(iv +  0);
	state[13] = get_unaligned_le32(iv +  4);
	state[14] = get_unaligned_le32(iv +  8);
	state[15] = get_unaligned_le32(iv + 12);
पूर्ण

अटल अंतरभूत व्योम chacha_init(u32 *state, स्थिर u32 *key, स्थिर u8 *iv)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_CHACHA))
		chacha_init_arch(state, key, iv);
	अन्यथा
		chacha_init_generic(state, key, iv);
पूर्ण

व्योम chacha_crypt_arch(u32 *state, u8 *dst, स्थिर u8 *src,
		       अचिन्हित पूर्णांक bytes, पूर्णांक nrounds);
व्योम chacha_crypt_generic(u32 *state, u8 *dst, स्थिर u8 *src,
			  अचिन्हित पूर्णांक bytes, पूर्णांक nrounds);

अटल अंतरभूत व्योम chacha_crypt(u32 *state, u8 *dst, स्थिर u8 *src,
				अचिन्हित पूर्णांक bytes, पूर्णांक nrounds)
अणु
	अगर (IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_CHACHA))
		chacha_crypt_arch(state, dst, src, bytes, nrounds);
	अन्यथा
		chacha_crypt_generic(state, dst, src, bytes, nrounds);
पूर्ण

अटल अंतरभूत व्योम chacha20_crypt(u32 *state, u8 *dst, स्थिर u8 *src,
				  अचिन्हित पूर्णांक bytes)
अणु
	chacha_crypt(state, dst, src, bytes, 20);
पूर्ण

#पूर्ण_अगर /* _CRYPTO_CHACHA_H */
