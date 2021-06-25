<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Host AP crypt: host-based WEP encryption implementation क्रम Host AP driver
 *
 * Copyright (c) 2002-2004, Jouni Malinen <jkmaline@cc.hut.fi>
 */

#समावेश <linux/fips.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>

#समावेश "ieee80211.h"

#समावेश <crypto/arc4.h>
#समावेश <linux/crc32.h>

MODULE_AUTHOR("Jouni Malinen");
MODULE_DESCRIPTION("Host AP crypt: WEP");
MODULE_LICENSE("GPL");

काष्ठा prism2_wep_data अणु
	u32 iv;
#घोषणा WEP_KEY_LEN 13
	u8 key[WEP_KEY_LEN + 1];
	u8 key_len;
	u8 key_idx;
	काष्ठा arc4_ctx rx_ctx_arc4;
	काष्ठा arc4_ctx tx_ctx_arc4;
पूर्ण;


अटल व्योम *prism2_wep_init(पूर्णांक keyidx)
अणु
	काष्ठा prism2_wep_data *priv;

	अगर (fips_enabled)
		वापस शून्य;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;
	priv->key_idx = keyidx;

	/* start WEP IV from a अक्रमom value */
	get_अक्रमom_bytes(&priv->iv, 4);

	वापस priv;
पूर्ण


अटल व्योम prism2_wep_deinit(व्योम *priv)
अणु
	kमुक्त_sensitive(priv);
पूर्ण

/* Perक्रमm WEP encryption on given skb that has at least 4 bytes of headroom
 * क्रम IV and 4 bytes of tailroom क्रम ICV. Both IV and ICV will be transmitted,
 * so the payload length increases with 8 bytes.
 *
 * WEP frame payload: IV + TX key idx, RC4(data), ICV = RC4(CRC32(data))
 */
अटल पूर्णांक prism2_wep_encrypt(काष्ठा sk_buff *skb, पूर्णांक hdr_len, व्योम *priv)
अणु
	काष्ठा prism2_wep_data *wep = priv;
	u32 klen, len;
	u8 key[WEP_KEY_LEN + 3];
	u8 *pos;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u32 crc;
	u8 *icv;

	अगर (skb_headroom(skb) < 4 || skb_tailroom(skb) < 4 ||
	    skb->len < hdr_len)
		वापस -1;

	len = skb->len - hdr_len;
	pos = skb_push(skb, 4);
	स_हटाओ(pos, pos + 4, hdr_len);
	pos += hdr_len;

	klen = 3 + wep->key_len;

	wep->iv++;

	/* Fluhrer, Mantin, and Shamir have reported weaknesses in the key
	 * scheduling algorithm of RC4. At least IVs (KeyByte + 3, 0xff, N)
	 * can be used to speedup attacks, so aव्योम using them.
	 */
	अगर ((wep->iv & 0xff00) == 0xff00) अणु
		u8 B = (wep->iv >> 16) & 0xff;

		अगर (B >= 3 && B < klen)
			wep->iv += 0x0100;
	पूर्ण

	/* Prepend 24-bit IV to RC4 key and TX frame */
	*pos++ = key[0] = (wep->iv >> 16) & 0xff;
	*pos++ = key[1] = (wep->iv >> 8) & 0xff;
	*pos++ = key[2] = wep->iv & 0xff;
	*pos++ = wep->key_idx << 6;

	/* Copy rest of the WEP key (the secret part) */
	स_नकल(key + 3, wep->key, wep->key_len);

	अगर (!tcb_desc->bHwSec) अणु
		/* Append little-endian CRC32 and encrypt it to produce ICV */
		crc = ~crc32_le(~0, pos, len);
		icv = skb_put(skb, 4);
		icv[0] = crc;
		icv[1] = crc >> 8;
		icv[2] = crc >> 16;
		icv[3] = crc >> 24;

		arc4_setkey(&wep->tx_ctx_arc4, key, klen);
		arc4_crypt(&wep->tx_ctx_arc4, pos, pos, len + 4);
	पूर्ण

	वापस 0;
पूर्ण


/* Perक्रमm WEP decryption on given buffer. Buffer includes whole WEP part of
 * the frame: IV (4 bytes), encrypted payload (including SNAP header),
 * ICV (4 bytes). len includes both IV and ICV.
 *
 * Returns 0 अगर frame was decrypted successfully and ICV was correct and -1 on
 * failure. If frame is OK, IV and ICV will be हटाओd.
 */
अटल पूर्णांक prism2_wep_decrypt(काष्ठा sk_buff *skb, पूर्णांक hdr_len, व्योम *priv)
अणु
	काष्ठा prism2_wep_data *wep = priv;
	u32  klen, plen;
	u8 key[WEP_KEY_LEN + 3];
	u8 keyidx, *pos;
	काष्ठा cb_desc *tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u32 crc;
	u8 icv[4];

	अगर (skb->len < hdr_len + 8)
		वापस -1;

	pos = skb->data + hdr_len;
	key[0] = *pos++;
	key[1] = *pos++;
	key[2] = *pos++;
	keyidx = *pos++ >> 6;
	अगर (keyidx != wep->key_idx)
		वापस -1;

	klen = 3 + wep->key_len;

	/* Copy rest of the WEP key (the secret part) */
	स_नकल(key + 3, wep->key, wep->key_len);

	/* Apply RC4 to data and compute CRC32 over decrypted data */
	plen = skb->len - hdr_len - 8;

	अगर (!tcb_desc->bHwSec) अणु
		arc4_setkey(&wep->rx_ctx_arc4, key, klen);
		arc4_crypt(&wep->rx_ctx_arc4, pos, pos, plen + 4);

		crc = ~crc32_le(~0, pos, plen);
		icv[0] = crc;
		icv[1] = crc >> 8;
		icv[2] = crc >> 16;
		icv[3] = crc >> 24;
		अगर (स_भेद(icv, pos + plen, 4) != 0) अणु
			/* ICV mismatch - drop frame */
			वापस -2;
		पूर्ण
	पूर्ण
	/* Remove IV and ICV */
	स_हटाओ(skb->data + 4, skb->data, hdr_len);
	skb_pull(skb, 4);
	skb_trim(skb, skb->len - 4);

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_wep_set_key(व्योम *key, पूर्णांक len, u8 *seq, व्योम *priv)
अणु
	काष्ठा prism2_wep_data *wep = priv;

	अगर (len < 0 || len > WEP_KEY_LEN)
		वापस -1;

	स_नकल(wep->key, key, len);
	wep->key_len = len;

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_wep_get_key(व्योम *key, पूर्णांक len, u8 *seq, व्योम *priv)
अणु
	काष्ठा prism2_wep_data *wep = priv;

	अगर (len < wep->key_len)
		वापस -1;

	स_नकल(key, wep->key, wep->key_len);

	वापस wep->key_len;
पूर्ण


अटल अक्षर *prism2_wep_prपूर्णांक_stats(अक्षर *p, व्योम *priv)
अणु
	काष्ठा prism2_wep_data *wep = priv;

	p += प्र_लिखो(p, "key[%d] alg=WEP len=%d\n",
		     wep->key_idx, wep->key_len);
	वापस p;
पूर्ण


अटल काष्ठा ieee80211_crypto_ops ieee80211_crypt_wep = अणु
	.name			= "WEP",
	.init			= prism2_wep_init,
	.deinit			= prism2_wep_deinit,
	.encrypt_mpdu		= prism2_wep_encrypt,
	.decrypt_mpdu		= prism2_wep_decrypt,
	.encrypt_msdu		= शून्य,
	.decrypt_msdu		= शून्य,
	.set_key		= prism2_wep_set_key,
	.get_key		= prism2_wep_get_key,
	.prपूर्णांक_stats		= prism2_wep_prपूर्णांक_stats,
	.extra_prefix_len	= 4, /* IV */
	.extra_postfix_len	= 4, /* ICV */
	.owner			= THIS_MODULE,
पूर्ण;

पूर्णांक __init ieee80211_crypto_wep_init(व्योम)
अणु
	वापस ieee80211_रेजिस्टर_crypto_ops(&ieee80211_crypt_wep);
पूर्ण

व्योम __निकास ieee80211_crypto_wep_निकास(व्योम)
अणु
	ieee80211_unरेजिस्टर_crypto_ops(&ieee80211_crypt_wep);
पूर्ण

