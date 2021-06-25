<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2014-2015, Qualcomm Atheros, Inc.
 */

#अगर_अघोषित AES_GCM_H
#घोषणा AES_GCM_H

#समावेश "aead_api.h"

#घोषणा GCM_AAD_LEN	32

अटल अंतरभूत पूर्णांक ieee80211_aes_gcm_encrypt(काष्ठा crypto_aead *tfm,
					    u8 *j_0, u8 *aad,  u8 *data,
					    माप_प्रकार data_len, u8 *mic)
अणु
	वापस aead_encrypt(tfm, j_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_len, mic);
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_aes_gcm_decrypt(काष्ठा crypto_aead *tfm,
					    u8 *j_0, u8 *aad, u8 *data,
					    माप_प्रकार data_len, u8 *mic)
अणु
	वापस aead_decrypt(tfm, j_0, aad + 2,
			    be16_to_cpup((__be16 *)aad),
			    data, data_len, mic);
पूर्ण

अटल अंतरभूत काष्ठा crypto_aead *
ieee80211_aes_gcm_key_setup_encrypt(स्थिर u8 key[], माप_प्रकार key_len)
अणु
	वापस aead_key_setup_encrypt("gcm(aes)", key,
				      key_len, IEEE80211_GCMP_MIC_LEN);
पूर्ण

अटल अंतरभूत व्योम ieee80211_aes_gcm_key_मुक्त(काष्ठा crypto_aead *tfm)
अणु
	वापस aead_key_मुक्त(tfm);
पूर्ण

#पूर्ण_अगर /* AES_GCM_H */
