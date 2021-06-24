<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/types.h>
#समावेश <crypto/aes.h>

काष्ठा aes_key अणु
	u8 key[AES_MAX_KEYLENGTH];
	पूर्णांक rounds;
पूर्ण;

बाह्य काष्ठा shash_alg p8_ghash_alg;
बाह्य काष्ठा crypto_alg p8_aes_alg;
बाह्य काष्ठा skcipher_alg p8_aes_cbc_alg;
बाह्य काष्ठा skcipher_alg p8_aes_ctr_alg;
बाह्य काष्ठा skcipher_alg p8_aes_xts_alg;

पूर्णांक aes_p8_set_encrypt_key(स्थिर u8 *userKey, स्थिर पूर्णांक bits,
			   काष्ठा aes_key *key);
पूर्णांक aes_p8_set_decrypt_key(स्थिर u8 *userKey, स्थिर पूर्णांक bits,
			   काष्ठा aes_key *key);
व्योम aes_p8_encrypt(स्थिर u8 *in, u8 *out, स्थिर काष्ठा aes_key *key);
व्योम aes_p8_decrypt(स्थिर u8 *in, u8 *out, स्थिर काष्ठा aes_key *key);
व्योम aes_p8_cbc_encrypt(स्थिर u8 *in, u8 *out, माप_प्रकार len,
			स्थिर काष्ठा aes_key *key, u8 *iv, स्थिर पूर्णांक enc);
व्योम aes_p8_ctr32_encrypt_blocks(स्थिर u8 *in, u8 *out,
				 माप_प्रकार len, स्थिर काष्ठा aes_key *key,
				 स्थिर u8 *iv);
व्योम aes_p8_xts_encrypt(स्थिर u8 *in, u8 *out, माप_प्रकार len,
			स्थिर काष्ठा aes_key *key1, स्थिर काष्ठा aes_key *key2, u8 *iv);
व्योम aes_p8_xts_decrypt(स्थिर u8 *in, u8 *out, माप_प्रकार len,
			स्थिर काष्ठा aes_key *key1, स्थिर काष्ठा aes_key *key2, u8 *iv);
