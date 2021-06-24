<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Software WEP encryption implementation
 * Copyright 2002, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright 2003, Instant802 Networks, Inc.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/compiler.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/mm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "wep.h"


व्योम ieee80211_wep_init(काष्ठा ieee80211_local *local)
अणु
	/* start WEP IV from a अक्रमom value */
	get_अक्रमom_bytes(&local->wep_iv, IEEE80211_WEP_IV_LEN);
पूर्ण

अटल अंतरभूत bool ieee80211_wep_weak_iv(u32 iv, पूर्णांक keylen)
अणु
	/*
	 * Fluhrer, Mantin, and Shamir have reported weaknesses in the
	 * key scheduling algorithm of RC4. At least IVs (KeyByte + 3,
	 * 0xff, N) can be used to speedup attacks, so aव्योम using them.
	 */
	अगर ((iv & 0xff00) == 0xff00) अणु
		u8 B = (iv >> 16) & 0xff;
		अगर (B >= 3 && B < 3 + keylen)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण


अटल व्योम ieee80211_wep_get_iv(काष्ठा ieee80211_local *local,
				 पूर्णांक keylen, पूर्णांक keyidx, u8 *iv)
अणु
	local->wep_iv++;
	अगर (ieee80211_wep_weak_iv(local->wep_iv, keylen))
		local->wep_iv += 0x0100;

	अगर (!iv)
		वापस;

	*iv++ = (local->wep_iv >> 16) & 0xff;
	*iv++ = (local->wep_iv >> 8) & 0xff;
	*iv++ = local->wep_iv & 0xff;
	*iv++ = keyidx << 6;
पूर्ण


अटल u8 *ieee80211_wep_add_iv(काष्ठा ieee80211_local *local,
				काष्ठा sk_buff *skb,
				पूर्णांक keylen, पूर्णांक keyidx)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	अचिन्हित पूर्णांक hdrlen;
	u8 *newhdr;

	hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PROTECTED);

	अगर (WARN_ON(skb_headroom(skb) < IEEE80211_WEP_IV_LEN))
		वापस शून्य;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	newhdr = skb_push(skb, IEEE80211_WEP_IV_LEN);
	स_हटाओ(newhdr, newhdr + IEEE80211_WEP_IV_LEN, hdrlen);

	/* the HW only needs room क्रम the IV, but not the actual IV */
	अगर (info->control.hw_key &&
	    (info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE))
		वापस newhdr + hdrlen;

	ieee80211_wep_get_iv(local, keylen, keyidx, newhdr + hdrlen);
	वापस newhdr + hdrlen;
पूर्ण


अटल व्योम ieee80211_wep_हटाओ_iv(काष्ठा ieee80211_local *local,
				    काष्ठा sk_buff *skb,
				    काष्ठा ieee80211_key *key)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अचिन्हित पूर्णांक hdrlen;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	स_हटाओ(skb->data + IEEE80211_WEP_IV_LEN, skb->data, hdrlen);
	skb_pull(skb, IEEE80211_WEP_IV_LEN);
पूर्ण


/* Perक्रमm WEP encryption using given key. data buffer must have tailroom
 * क्रम 4-byte ICV. data_len must not include this ICV. Note: this function
 * करोes _not_ add IV. data = RC4(data | CRC32(data)) */
पूर्णांक ieee80211_wep_encrypt_data(काष्ठा arc4_ctx *ctx, u8 *rc4key,
			       माप_प्रकार klen, u8 *data, माप_प्रकार data_len)
अणु
	__le32 icv;

	icv = cpu_to_le32(~crc32_le(~0, data, data_len));
	put_unaligned(icv, (__le32 *)(data + data_len));

	arc4_setkey(ctx, rc4key, klen);
	arc4_crypt(ctx, data, data, data_len + IEEE80211_WEP_ICV_LEN);
	memzero_explicit(ctx, माप(*ctx));

	वापस 0;
पूर्ण


/* Perक्रमm WEP encryption on given skb. 4 bytes of extra space (IV) in the
 * beginning of the buffer 4 bytes of extra space (ICV) in the end of the
 * buffer will be added. Both IV and ICV will be transmitted, so the
 * payload length increases with 8 bytes.
 *
 * WEP frame payload: IV + TX key idx, RC4(data), ICV = RC4(CRC32(data))
 */
पूर्णांक ieee80211_wep_encrypt(काष्ठा ieee80211_local *local,
			  काष्ठा sk_buff *skb,
			  स्थिर u8 *key, पूर्णांक keylen, पूर्णांक keyidx)
अणु
	u8 *iv;
	माप_प्रकार len;
	u8 rc4key[3 + WLAN_KEY_LEN_WEP104];

	अगर (WARN_ON(skb_tailroom(skb) < IEEE80211_WEP_ICV_LEN))
		वापस -1;

	iv = ieee80211_wep_add_iv(local, skb, keylen, keyidx);
	अगर (!iv)
		वापस -1;

	len = skb->len - (iv + IEEE80211_WEP_IV_LEN - skb->data);

	/* Prepend 24-bit IV to RC4 key */
	स_नकल(rc4key, iv, 3);

	/* Copy rest of the WEP key (the secret part) */
	स_नकल(rc4key + 3, key, keylen);

	/* Add room क्रम ICV */
	skb_put(skb, IEEE80211_WEP_ICV_LEN);

	वापस ieee80211_wep_encrypt_data(&local->wep_tx_ctx, rc4key, keylen + 3,
					  iv + IEEE80211_WEP_IV_LEN, len);
पूर्ण


/* Perक्रमm WEP decryption using given key. data buffer includes encrypted
 * payload, including 4-byte ICV, but _not_ IV. data_len must not include ICV.
 * Return 0 on success and -1 on ICV mismatch. */
पूर्णांक ieee80211_wep_decrypt_data(काष्ठा arc4_ctx *ctx, u8 *rc4key,
			       माप_प्रकार klen, u8 *data, माप_प्रकार data_len)
अणु
	__le32 crc;

	arc4_setkey(ctx, rc4key, klen);
	arc4_crypt(ctx, data, data, data_len + IEEE80211_WEP_ICV_LEN);
	memzero_explicit(ctx, माप(*ctx));

	crc = cpu_to_le32(~crc32_le(~0, data, data_len));
	अगर (स_भेद(&crc, data + data_len, IEEE80211_WEP_ICV_LEN) != 0)
		/* ICV mismatch */
		वापस -1;

	वापस 0;
पूर्ण


/* Perक्रमm WEP decryption on given skb. Buffer includes whole WEP part of
 * the frame: IV (4 bytes), encrypted payload (including SNAP header),
 * ICV (4 bytes). skb->len includes both IV and ICV.
 *
 * Returns 0 अगर frame was decrypted successfully and ICV was correct and -1 on
 * failure. If frame is OK, IV and ICV will be हटाओd, i.e., decrypted payload
 * is moved to the beginning of the skb and skb length will be reduced.
 */
अटल पूर्णांक ieee80211_wep_decrypt(काष्ठा ieee80211_local *local,
				 काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_key *key)
अणु
	u32 klen;
	u8 rc4key[3 + WLAN_KEY_LEN_WEP104];
	u8 keyidx;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अचिन्हित पूर्णांक hdrlen;
	माप_प्रकार len;
	पूर्णांक ret = 0;

	अगर (!ieee80211_has_रक्षित(hdr->frame_control))
		वापस -1;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	अगर (skb->len < hdrlen + IEEE80211_WEP_IV_LEN + IEEE80211_WEP_ICV_LEN)
		वापस -1;

	len = skb->len - hdrlen - IEEE80211_WEP_IV_LEN - IEEE80211_WEP_ICV_LEN;

	keyidx = skb->data[hdrlen + 3] >> 6;

	अगर (!key || keyidx != key->conf.keyidx)
		वापस -1;

	klen = 3 + key->conf.keylen;

	/* Prepend 24-bit IV to RC4 key */
	स_नकल(rc4key, skb->data + hdrlen, 3);

	/* Copy rest of the WEP key (the secret part) */
	स_नकल(rc4key + 3, key->conf.key, key->conf.keylen);

	अगर (ieee80211_wep_decrypt_data(&local->wep_rx_ctx, rc4key, klen,
				       skb->data + hdrlen +
				       IEEE80211_WEP_IV_LEN, len))
		ret = -1;

	/* Trim ICV */
	skb_trim(skb, skb->len - IEEE80211_WEP_ICV_LEN);

	/* Remove IV */
	स_हटाओ(skb->data + IEEE80211_WEP_IV_LEN, skb->data, hdrlen);
	skb_pull(skb, IEEE80211_WEP_IV_LEN);

	वापस ret;
पूर्ण

ieee80211_rx_result
ieee80211_crypto_wep_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	__le16 fc = hdr->frame_control;

	अगर (!ieee80211_is_data(fc) && !ieee80211_is_auth(fc))
		वापस RX_CONTINUE;

	अगर (!(status->flag & RX_FLAG_DECRYPTED)) अणु
		अगर (skb_linearize(rx->skb))
			वापस RX_DROP_UNUSABLE;
		अगर (ieee80211_wep_decrypt(rx->local, rx->skb, rx->key))
			वापस RX_DROP_UNUSABLE;
	पूर्ण अन्यथा अगर (!(status->flag & RX_FLAG_IV_STRIPPED)) अणु
		अगर (!pskb_may_pull(rx->skb, ieee80211_hdrlen(fc) +
					    IEEE80211_WEP_IV_LEN))
			वापस RX_DROP_UNUSABLE;
		ieee80211_wep_हटाओ_iv(rx->local, rx->skb, rx->key);
		/* हटाओ ICV */
		अगर (!(status->flag & RX_FLAG_ICV_STRIPPED) &&
		    pskb_trim(rx->skb, rx->skb->len - IEEE80211_WEP_ICV_LEN))
			वापस RX_DROP_UNUSABLE;
	पूर्ण

	वापस RX_CONTINUE;
पूर्ण

अटल पूर्णांक wep_encrypt_skb(काष्ठा ieee80211_tx_data *tx, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_key_conf *hw_key = info->control.hw_key;

	अगर (!hw_key) अणु
		अगर (ieee80211_wep_encrypt(tx->local, skb, tx->key->conf.key,
					  tx->key->conf.keylen,
					  tx->key->conf.keyidx))
			वापस -1;
	पूर्ण अन्यथा अगर ((hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_IV) ||
		   (hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE)) अणु
		अगर (!ieee80211_wep_add_iv(tx->local, skb,
					  tx->key->conf.keylen,
					  tx->key->conf.keyidx))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

ieee80211_tx_result
ieee80211_crypto_wep_encrypt(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;

	ieee80211_tx_set_रक्षित(tx);

	skb_queue_walk(&tx->skbs, skb) अणु
		अगर (wep_encrypt_skb(tx, skb) < 0) अणु
			I802_DEBUG_INC(tx->local->tx_handlers_drop_wep);
			वापस TX_DROP;
		पूर्ण
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण
