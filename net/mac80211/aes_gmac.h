<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2015, Qualcomm Atheros, Inc.
 */

#अगर_अघोषित AES_GMAC_H
#घोषणा AES_GMAC_H

#समावेश <linux/crypto.h>

#घोषणा GMAC_AAD_LEN	20
#घोषणा GMAC_MIC_LEN	16
#घोषणा GMAC_NONCE_LEN	12

काष्ठा crypto_aead *ieee80211_aes_gmac_key_setup(स्थिर u8 key[],
						 माप_प्रकार key_len);
पूर्णांक ieee80211_aes_gmac(काष्ठा crypto_aead *tfm, स्थिर u8 *aad, u8 *nonce,
		       स्थिर u8 *data, माप_प्रकार data_len, u8 *mic);
व्योम ieee80211_aes_gmac_key_मुक्त(काष्ठा crypto_aead *tfm);

#पूर्ण_अगर /* AES_GMAC_H */
