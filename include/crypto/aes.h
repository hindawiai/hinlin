<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम AES algorithms
 */

#अगर_अघोषित _CRYPTO_AES_H
#घोषणा _CRYPTO_AES_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>

#घोषणा AES_MIN_KEY_SIZE	16
#घोषणा AES_MAX_KEY_SIZE	32
#घोषणा AES_KEYSIZE_128		16
#घोषणा AES_KEYSIZE_192		24
#घोषणा AES_KEYSIZE_256		32
#घोषणा AES_BLOCK_SIZE		16
#घोषणा AES_MAX_KEYLENGTH	(15 * 16)
#घोषणा AES_MAX_KEYLENGTH_U32	(AES_MAX_KEYLENGTH / माप(u32))

/*
 * Please ensure that the first two fields are 16-byte aligned
 * relative to the start of the काष्ठाure, i.e., करोn't move them!
 */
काष्ठा crypto_aes_ctx अणु
	u32 key_enc[AES_MAX_KEYLENGTH_U32];
	u32 key_dec[AES_MAX_KEYLENGTH_U32];
	u32 key_length;
पूर्ण;

बाह्य स्थिर u32 crypto_ft_tab[4][256] ____cacheline_aligned;
बाह्य स्थिर u32 crypto_it_tab[4][256] ____cacheline_aligned;

/*
 * validate key length क्रम AES algorithms
 */
अटल अंतरभूत पूर्णांक aes_check_keylen(अचिन्हित पूर्णांक keylen)
अणु
	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
	हाल AES_KEYSIZE_192:
	हाल AES_KEYSIZE_256:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक crypto_aes_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		अचिन्हित पूर्णांक key_len);

/**
 * aes_expandkey - Expands the AES key as described in FIPS-197
 * @ctx:	The location where the computed key will be stored.
 * @in_key:	The supplied key.
 * @key_len:	The length of the supplied key.
 *
 * Returns 0 on success. The function fails only अगर an invalid key size (or
 * poपूर्णांकer) is supplied.
 * The expanded key size is 240 bytes (max of 14 rounds with a unique 16 bytes
 * key schedule plus a 16 bytes key which is used beक्रमe the first round).
 * The decryption key is prepared क्रम the "Equivalent Inverse Cipher" as
 * described in FIPS-197. The first slot (16 bytes) of each key (enc or dec) is
 * क्रम the initial combination, the second slot क्रम the first round and so on.
 */
पूर्णांक aes_expandkey(काष्ठा crypto_aes_ctx *ctx, स्थिर u8 *in_key,
		  अचिन्हित पूर्णांक key_len);

/**
 * aes_encrypt - Encrypt a single AES block
 * @ctx:	Context काष्ठा containing the key schedule
 * @out:	Buffer to store the ciphertext
 * @in:		Buffer containing the plaपूर्णांकext
 */
व्योम aes_encrypt(स्थिर काष्ठा crypto_aes_ctx *ctx, u8 *out, स्थिर u8 *in);

/**
 * aes_decrypt - Decrypt a single AES block
 * @ctx:	Context काष्ठा containing the key schedule
 * @out:	Buffer to store the plaपूर्णांकext
 * @in:		Buffer containing the ciphertext
 */
व्योम aes_decrypt(स्थिर काष्ठा crypto_aes_ctx *ctx, u8 *out, स्थिर u8 *in);

बाह्य स्थिर u8 crypto_aes_sbox[];
बाह्य स्थिर u8 crypto_aes_inv_sbox[];

#पूर्ण_अगर
