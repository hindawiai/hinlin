<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2003-2004, Instant802 Networks, Inc.
 * Copyright 2006, Devicescape Software, Inc.
 */

#अगर_अघोषित AES_CCM_H
#घोषणा AES_CCM_H

#समावेश "aead_api.h"

#घोषणा CCM_AAD_LEN	32

अटल अंतरभूत काष्ठा crypto_aead *
ieee80211_aes_key_setup_encrypt(स्थिर u8 key[], माप_प्रकार key_len, माप_प्रकार mic_len)
अणु
	वापस aead_key_setup_encrypt("ccm(aes)", key, key_len, mic_len);
पूर्ण

अटल अंतरभूत पूर्णांक
ieee80211_aes_ccm_encrypt(काष्ठा crypto_aead *tfm,
			  u8 *b_0, u8 *aad, u8 *data,
			  माप_प्रकार data_len, u8 *mic)
अणु
	वापस aead_encrypt(tfm, b_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_len, mic);
पूर्ण

अटल अंतरभूत पूर्णांक
ieee80211_aes_ccm_decrypt(काष्ठा crypto_aead *tfm,
			  u8 *b_0, u8 *aad, u8 *data,
			  माप_प्रकार data_len, u8 *mic)
अणु
	वापस aead_decrypt(tfm, b_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_len, mic);
पूर्ण

अटल अंतरभूत व्योम ieee80211_aes_key_मुक्त(काष्ठा crypto_aead *tfm)
अणु
	वापस aead_key_मुक्त(tfm);
पूर्ण

#पूर्ण_अगर /* AES_CCM_H */
