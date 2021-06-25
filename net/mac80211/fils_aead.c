<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * FILS AEAD क्रम (Re)Association Request/Response frames
 * Copyright 2016, Qualcomm Atheros, Inc.
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>

#समावेश "ieee80211_i.h"
#समावेश "aes_cmac.h"
#समावेश "fils_aead.h"

अटल व्योम gf_mulx(u8 *pad)
अणु
	u64 a = get_unaligned_be64(pad);
	u64 b = get_unaligned_be64(pad + 8);

	put_unaligned_be64((a << 1) | (b >> 63), pad);
	put_unaligned_be64((b << 1) ^ ((a >> 63) ? 0x87 : 0), pad + 8);
पूर्ण

अटल पूर्णांक aes_s2v(काष्ठा crypto_shash *tfm,
		   माप_प्रकार num_elem, स्थिर u8 *addr[], माप_प्रकार len[], u8 *v)
अणु
	u8 d[AES_BLOCK_SIZE], पंचांगp[AES_BLOCK_SIZE] = अणुपूर्ण;
	SHASH_DESC_ON_STACK(desc, tfm);
	माप_प्रकार i;

	desc->tfm = tfm;

	/* D = AES-CMAC(K, <zero>) */
	crypto_shash_digest(desc, पंचांगp, AES_BLOCK_SIZE, d);

	क्रम (i = 0; i < num_elem - 1; i++) अणु
		/* D = dbl(D) xor AES_CMAC(K, Si) */
		gf_mulx(d); /* dbl */
		crypto_shash_digest(desc, addr[i], len[i], पंचांगp);
		crypto_xor(d, पंचांगp, AES_BLOCK_SIZE);
	पूर्ण

	crypto_shash_init(desc);

	अगर (len[i] >= AES_BLOCK_SIZE) अणु
		/* len(Sn) >= 128 */
		/* T = Sn xorend D */
		crypto_shash_update(desc, addr[i], len[i] - AES_BLOCK_SIZE);
		crypto_xor(d, addr[i] + len[i] - AES_BLOCK_SIZE,
			   AES_BLOCK_SIZE);
	पूर्ण अन्यथा अणु
		/* len(Sn) < 128 */
		/* T = dbl(D) xor pad(Sn) */
		gf_mulx(d); /* dbl */
		crypto_xor(d, addr[i], len[i]);
		d[len[i]] ^= 0x80;
	पूर्ण
	/* V = AES-CMAC(K, T) */
	crypto_shash_finup(desc, d, AES_BLOCK_SIZE, v);

	वापस 0;
पूर्ण

/* Note: addr[] and len[] needs to have one extra slot at the end. */
अटल पूर्णांक aes_siv_encrypt(स्थिर u8 *key, माप_प्रकार key_len,
			   स्थिर u8 *plain, माप_प्रकार plain_len,
			   माप_प्रकार num_elem, स्थिर u8 *addr[],
			   माप_प्रकार len[], u8 *out)
अणु
	u8 v[AES_BLOCK_SIZE];
	काष्ठा crypto_shash *tfm;
	काष्ठा crypto_skcipher *tfm2;
	काष्ठा skcipher_request *req;
	पूर्णांक res;
	काष्ठा scatterlist src[1], dst[1];
	u8 *पंचांगp;

	key_len /= 2; /* S2V key || CTR key */

	addr[num_elem] = plain;
	len[num_elem] = plain_len;
	num_elem++;

	/* S2V */

	tfm = crypto_alloc_shash("cmac(aes)", 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);
	/* K1 क्रम S2V */
	res = crypto_shash_setkey(tfm, key, key_len);
	अगर (!res)
		res = aes_s2v(tfm, num_elem, addr, len, v);
	crypto_मुक्त_shash(tfm);
	अगर (res)
		वापस res;

	/* Use a temporary buffer of the plaपूर्णांकext to handle need क्रम
	 * overwriting this during AES-CTR.
	 */
	पंचांगp = kmemdup(plain, plain_len, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	/* IV क्रम CTR beक्रमe encrypted data */
	स_नकल(out, v, AES_BLOCK_SIZE);

	/* Synthetic IV to be used as the initial counter in CTR:
	 * Q = V bitand (1^64 || 0^1 || 1^31 || 0^1 || 1^31)
	 */
	v[8] &= 0x7f;
	v[12] &= 0x7f;

	/* CTR */

	tfm2 = crypto_alloc_skcipher("ctr(aes)", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm2)) अणु
		kमुक्त(पंचांगp);
		वापस PTR_ERR(tfm2);
	पूर्ण
	/* K2 क्रम CTR */
	res = crypto_skcipher_setkey(tfm2, key + key_len, key_len);
	अगर (res)
		जाओ fail;

	req = skcipher_request_alloc(tfm2, GFP_KERNEL);
	अगर (!req) अणु
		res = -ENOMEM;
		जाओ fail;
	पूर्ण

	sg_init_one(src, पंचांगp, plain_len);
	sg_init_one(dst, out + AES_BLOCK_SIZE, plain_len);
	skcipher_request_set_crypt(req, src, dst, plain_len, v);
	res = crypto_skcipher_encrypt(req);
	skcipher_request_मुक्त(req);
fail:
	kमुक्त(पंचांगp);
	crypto_मुक्त_skcipher(tfm2);
	वापस res;
पूर्ण

/* Note: addr[] and len[] needs to have one extra slot at the end. */
अटल पूर्णांक aes_siv_decrypt(स्थिर u8 *key, माप_प्रकार key_len,
			   स्थिर u8 *iv_crypt, माप_प्रकार iv_c_len,
			   माप_प्रकार num_elem, स्थिर u8 *addr[], माप_प्रकार len[],
			   u8 *out)
अणु
	काष्ठा crypto_shash *tfm;
	काष्ठा crypto_skcipher *tfm2;
	काष्ठा skcipher_request *req;
	काष्ठा scatterlist src[1], dst[1];
	माप_प्रकार crypt_len;
	पूर्णांक res;
	u8 frame_iv[AES_BLOCK_SIZE], iv[AES_BLOCK_SIZE];
	u8 check[AES_BLOCK_SIZE];

	crypt_len = iv_c_len - AES_BLOCK_SIZE;
	key_len /= 2; /* S2V key || CTR key */
	addr[num_elem] = out;
	len[num_elem] = crypt_len;
	num_elem++;

	स_नकल(iv, iv_crypt, AES_BLOCK_SIZE);
	स_नकल(frame_iv, iv_crypt, AES_BLOCK_SIZE);

	/* Synthetic IV to be used as the initial counter in CTR:
	 * Q = V bitand (1^64 || 0^1 || 1^31 || 0^1 || 1^31)
	 */
	iv[8] &= 0x7f;
	iv[12] &= 0x7f;

	/* CTR */

	tfm2 = crypto_alloc_skcipher("ctr(aes)", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm2))
		वापस PTR_ERR(tfm2);
	/* K2 क्रम CTR */
	res = crypto_skcipher_setkey(tfm2, key + key_len, key_len);
	अगर (res) अणु
		crypto_मुक्त_skcipher(tfm2);
		वापस res;
	पूर्ण

	req = skcipher_request_alloc(tfm2, GFP_KERNEL);
	अगर (!req) अणु
		crypto_मुक्त_skcipher(tfm2);
		वापस -ENOMEM;
	पूर्ण

	sg_init_one(src, iv_crypt + AES_BLOCK_SIZE, crypt_len);
	sg_init_one(dst, out, crypt_len);
	skcipher_request_set_crypt(req, src, dst, crypt_len, iv);
	res = crypto_skcipher_decrypt(req);
	skcipher_request_मुक्त(req);
	crypto_मुक्त_skcipher(tfm2);
	अगर (res)
		वापस res;

	/* S2V */

	tfm = crypto_alloc_shash("cmac(aes)", 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);
	/* K1 क्रम S2V */
	res = crypto_shash_setkey(tfm, key, key_len);
	अगर (!res)
		res = aes_s2v(tfm, num_elem, addr, len, check);
	crypto_मुक्त_shash(tfm);
	अगर (res)
		वापस res;
	अगर (स_भेद(check, frame_iv, AES_BLOCK_SIZE) != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक fils_encrypt_assoc_req(काष्ठा sk_buff *skb,
			   काष्ठा ieee80211_mgd_assoc_data *assoc_data)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;
	u8 *capab, *ies, *encr;
	स्थिर u8 *addr[5 + 1], *session;
	माप_प्रकार len[5 + 1];
	माप_प्रकार crypt_len;

	अगर (ieee80211_is_reassoc_req(mgmt->frame_control)) अणु
		capab = (u8 *)&mgmt->u.reassoc_req.capab_info;
		ies = mgmt->u.reassoc_req.variable;
	पूर्ण अन्यथा अणु
		capab = (u8 *)&mgmt->u.assoc_req.capab_info;
		ies = mgmt->u.assoc_req.variable;
	पूर्ण

	session = cfg80211_find_ext_ie(WLAN_EID_EXT_FILS_SESSION,
				       ies, skb->data + skb->len - ies);
	अगर (!session || session[1] != 1 + 8)
		वापस -EINVAL;
	/* encrypt after FILS Session element */
	encr = (u8 *)session + 2 + 1 + 8;

	/* AES-SIV AAD vectors */

	/* The STA's MAC address */
	addr[0] = mgmt->sa;
	len[0] = ETH_ALEN;
	/* The AP's BSSID */
	addr[1] = mgmt->da;
	len[1] = ETH_ALEN;
	/* The STA's nonce */
	addr[2] = assoc_data->fils_nonces;
	len[2] = FILS_NONCE_LEN;
	/* The AP's nonce */
	addr[3] = &assoc_data->fils_nonces[FILS_NONCE_LEN];
	len[3] = FILS_NONCE_LEN;
	/* The (Re)Association Request frame from the Capability Inक्रमmation
	 * field to the FILS Session element (both inclusive).
	 */
	addr[4] = capab;
	len[4] = encr - capab;

	crypt_len = skb->data + skb->len - encr;
	skb_put(skb, AES_BLOCK_SIZE);
	वापस aes_siv_encrypt(assoc_data->fils_kek, assoc_data->fils_kek_len,
			       encr, crypt_len, 5, addr, len, encr);
पूर्ण

पूर्णांक fils_decrypt_assoc_resp(काष्ठा ieee80211_sub_अगर_data *sdata,
			    u8 *frame, माप_प्रकार *frame_len,
			    काष्ठा ieee80211_mgd_assoc_data *assoc_data)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)frame;
	u8 *capab, *ies, *encr;
	स्थिर u8 *addr[5 + 1], *session;
	माप_प्रकार len[5 + 1];
	पूर्णांक res;
	माप_प्रकार crypt_len;

	अगर (*frame_len < 24 + 6)
		वापस -EINVAL;

	capab = (u8 *)&mgmt->u.assoc_resp.capab_info;
	ies = mgmt->u.assoc_resp.variable;
	session = cfg80211_find_ext_ie(WLAN_EID_EXT_FILS_SESSION,
				       ies, frame + *frame_len - ies);
	अगर (!session || session[1] != 1 + 8) अणु
		mlme_dbg(sdata,
			 "No (valid) FILS Session element in (Re)Association Response frame from %pM",
			 mgmt->sa);
		वापस -EINVAL;
	पूर्ण
	/* decrypt after FILS Session element */
	encr = (u8 *)session + 2 + 1 + 8;

	/* AES-SIV AAD vectors */

	/* The AP's BSSID */
	addr[0] = mgmt->sa;
	len[0] = ETH_ALEN;
	/* The STA's MAC address */
	addr[1] = mgmt->da;
	len[1] = ETH_ALEN;
	/* The AP's nonce */
	addr[2] = &assoc_data->fils_nonces[FILS_NONCE_LEN];
	len[2] = FILS_NONCE_LEN;
	/* The STA's nonce */
	addr[3] = assoc_data->fils_nonces;
	len[3] = FILS_NONCE_LEN;
	/* The (Re)Association Response frame from the Capability Inक्रमmation
	 * field to the FILS Session element (both inclusive).
	 */
	addr[4] = capab;
	len[4] = encr - capab;

	crypt_len = frame + *frame_len - encr;
	अगर (crypt_len < AES_BLOCK_SIZE) अणु
		mlme_dbg(sdata,
			 "Not enough room for AES-SIV data after FILS Session element in (Re)Association Response frame from %pM",
			 mgmt->sa);
		वापस -EINVAL;
	पूर्ण
	res = aes_siv_decrypt(assoc_data->fils_kek, assoc_data->fils_kek_len,
			      encr, crypt_len, 5, addr, len, encr);
	अगर (res != 0) अणु
		mlme_dbg(sdata,
			 "AES-SIV decryption of (Re)Association Response frame from %pM failed",
			 mgmt->sa);
		वापस res;
	पूर्ण
	*frame_len -= AES_BLOCK_SIZE;
	वापस 0;
पूर्ण
