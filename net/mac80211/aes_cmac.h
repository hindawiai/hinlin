<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2008, Jouni Malinen <j@w1.fi>
 */

#अगर_अघोषित AES_CMAC_H
#घोषणा AES_CMAC_H

#समावेश <linux/crypto.h>
#समावेश <crypto/hash.h>

काष्ठा crypto_shash *ieee80211_aes_cmac_key_setup(स्थिर u8 key[],
						  माप_प्रकार key_len);
व्योम ieee80211_aes_cmac(काष्ठा crypto_shash *tfm, स्थिर u8 *aad,
			स्थिर u8 *data, माप_प्रकार data_len, u8 *mic);
व्योम ieee80211_aes_cmac_256(काष्ठा crypto_shash *tfm, स्थिर u8 *aad,
			    स्थिर u8 *data, माप_प्रकार data_len, u8 *mic);
व्योम ieee80211_aes_cmac_key_मुक्त(काष्ठा crypto_shash *tfm);

#पूर्ण_अगर /* AES_CMAC_H */
