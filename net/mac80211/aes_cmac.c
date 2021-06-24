<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES-128-CMAC with TLen 16 क्रम IEEE 802.11w BIP
 * Copyright 2008, Jouni Malinen <j@w1.fi>
 * Copyright (C) 2020 Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <crypto/aes.h>

#समावेश <net/mac80211.h>
#समावेश "key.h"
#समावेश "aes_cmac.h"

#घोषणा CMAC_TLEN 8 /* CMAC TLen = 64 bits (8 octets) */
#घोषणा CMAC_TLEN_256 16 /* CMAC TLen = 128 bits (16 octets) */
#घोषणा AAD_LEN 20

अटल स्थिर u8 zero[CMAC_TLEN_256];

व्योम ieee80211_aes_cmac(काष्ठा crypto_shash *tfm, स्थिर u8 *aad,
			स्थिर u8 *data, माप_प्रकार data_len, u8 *mic)
अणु
	SHASH_DESC_ON_STACK(desc, tfm);
	u8 out[AES_BLOCK_SIZE];
	स्थिर __le16 *fc;

	desc->tfm = tfm;

	crypto_shash_init(desc);
	crypto_shash_update(desc, aad, AAD_LEN);
	fc = (स्थिर __le16 *)aad;
	अगर (ieee80211_is_beacon(*fc)) अणु
		/* mask Timestamp field to zero */
		crypto_shash_update(desc, zero, 8);
		crypto_shash_update(desc, data + 8, data_len - 8 - CMAC_TLEN);
	पूर्ण अन्यथा अणु
		crypto_shash_update(desc, data, data_len - CMAC_TLEN);
	पूर्ण
	crypto_shash_finup(desc, zero, CMAC_TLEN, out);

	स_नकल(mic, out, CMAC_TLEN);
पूर्ण

व्योम ieee80211_aes_cmac_256(काष्ठा crypto_shash *tfm, स्थिर u8 *aad,
			    स्थिर u8 *data, माप_प्रकार data_len, u8 *mic)
अणु
	SHASH_DESC_ON_STACK(desc, tfm);
	स्थिर __le16 *fc;

	desc->tfm = tfm;

	crypto_shash_init(desc);
	crypto_shash_update(desc, aad, AAD_LEN);
	fc = (स्थिर __le16 *)aad;
	अगर (ieee80211_is_beacon(*fc)) अणु
		/* mask Timestamp field to zero */
		crypto_shash_update(desc, zero, 8);
		crypto_shash_update(desc, data + 8,
				    data_len - 8 - CMAC_TLEN_256);
	पूर्ण अन्यथा अणु
		crypto_shash_update(desc, data, data_len - CMAC_TLEN_256);
	पूर्ण
	crypto_shash_finup(desc, zero, CMAC_TLEN_256, mic);
पूर्ण

काष्ठा crypto_shash *ieee80211_aes_cmac_key_setup(स्थिर u8 key[],
						  माप_प्रकार key_len)
अणु
	काष्ठा crypto_shash *tfm;

	tfm = crypto_alloc_shash("cmac(aes)", 0, 0);
	अगर (!IS_ERR(tfm)) अणु
		पूर्णांक err = crypto_shash_setkey(tfm, key, key_len);

		अगर (err) अणु
			crypto_मुक्त_shash(tfm);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	वापस tfm;
पूर्ण

व्योम ieee80211_aes_cmac_key_मुक्त(काष्ठा crypto_shash *tfm)
अणु
	crypto_मुक्त_shash(tfm);
पूर्ण
