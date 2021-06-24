<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AES-GMAC क्रम IEEE 802.11 BIP-GMAC-128 and BIP-GMAC-256
 * Copyright 2015, Qualcomm Atheros, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/aes.h>

#समावेश <net/mac80211.h>
#समावेश "key.h"
#समावेश "aes_gmac.h"

पूर्णांक ieee80211_aes_gmac(काष्ठा crypto_aead *tfm, स्थिर u8 *aad, u8 *nonce,
		       स्थिर u8 *data, माप_प्रकार data_len, u8 *mic)
अणु
	काष्ठा scatterlist sg[5];
	u8 *zero, *__aad, iv[AES_BLOCK_SIZE];
	काष्ठा aead_request *aead_req;
	पूर्णांक reqsize = माप(*aead_req) + crypto_aead_reqsize(tfm);
	स्थिर __le16 *fc;
	पूर्णांक ret;

	अगर (data_len < GMAC_MIC_LEN)
		वापस -EINVAL;

	aead_req = kzalloc(reqsize + GMAC_MIC_LEN + GMAC_AAD_LEN, GFP_ATOMIC);
	अगर (!aead_req)
		वापस -ENOMEM;

	zero = (u8 *)aead_req + reqsize;
	__aad = zero + GMAC_MIC_LEN;
	स_नकल(__aad, aad, GMAC_AAD_LEN);

	fc = (स्थिर __le16 *)aad;
	अगर (ieee80211_is_beacon(*fc)) अणु
		/* mask Timestamp field to zero */
		sg_init_table(sg, 5);
		sg_set_buf(&sg[0], __aad, GMAC_AAD_LEN);
		sg_set_buf(&sg[1], zero, 8);
		sg_set_buf(&sg[2], data + 8, data_len - 8 - GMAC_MIC_LEN);
		sg_set_buf(&sg[3], zero, GMAC_MIC_LEN);
		sg_set_buf(&sg[4], mic, GMAC_MIC_LEN);
	पूर्ण अन्यथा अणु
		sg_init_table(sg, 4);
		sg_set_buf(&sg[0], __aad, GMAC_AAD_LEN);
		sg_set_buf(&sg[1], data, data_len - GMAC_MIC_LEN);
		sg_set_buf(&sg[2], zero, GMAC_MIC_LEN);
		sg_set_buf(&sg[3], mic, GMAC_MIC_LEN);
	पूर्ण

	स_नकल(iv, nonce, GMAC_NONCE_LEN);
	स_रखो(iv + GMAC_NONCE_LEN, 0, माप(iv) - GMAC_NONCE_LEN);
	iv[AES_BLOCK_SIZE - 1] = 0x01;

	aead_request_set_tfm(aead_req, tfm);
	aead_request_set_crypt(aead_req, sg, sg, 0, iv);
	aead_request_set_ad(aead_req, GMAC_AAD_LEN + data_len);

	ret = crypto_aead_encrypt(aead_req);
	kमुक्त_sensitive(aead_req);

	वापस ret;
पूर्ण

काष्ठा crypto_aead *ieee80211_aes_gmac_key_setup(स्थिर u8 key[],
						 माप_प्रकार key_len)
अणु
	काष्ठा crypto_aead *tfm;
	पूर्णांक err;

	tfm = crypto_alloc_aead("gcm(aes)", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		वापस tfm;

	err = crypto_aead_setkey(tfm, key, key_len);
	अगर (!err)
		err = crypto_aead_setauthsize(tfm, GMAC_MIC_LEN);
	अगर (!err)
		वापस tfm;

	crypto_मुक्त_aead(tfm);
	वापस ERR_PTR(err);
पूर्ण

व्योम ieee80211_aes_gmac_key_मुक्त(काष्ठा crypto_aead *tfm)
अणु
	crypto_मुक्त_aead(tfm);
पूर्ण
