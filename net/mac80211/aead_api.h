<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित _AEAD_API_H
#घोषणा _AEAD_API_H

#समावेश <crypto/aead.h>
#समावेश <linux/crypto.h>

काष्ठा crypto_aead *
aead_key_setup_encrypt(स्थिर अक्षर *alg, स्थिर u8 key[],
		       माप_प्रकार key_len, माप_प्रकार mic_len);

पूर्णांक aead_encrypt(काष्ठा crypto_aead *tfm, u8 *b_0, u8 *aad,
		 माप_प्रकार aad_len, u8 *data,
		 माप_प्रकार data_len, u8 *mic);

पूर्णांक aead_decrypt(काष्ठा crypto_aead *tfm, u8 *b_0, u8 *aad,
		 माप_प्रकार aad_len, u8 *data,
		 माप_प्रकार data_len, u8 *mic);

व्योम aead_key_मुक्त(काष्ठा crypto_aead *tfm);

#पूर्ण_अगर /* _AEAD_API_H */
