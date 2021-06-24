<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 crypto specअगरic routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"

क्रमागत cipher rt2x00crypto_key_to_cipher(काष्ठा ieee80211_key_conf *key)
अणु
	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		वापस CIPHER_WEP64;
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस CIPHER_WEP128;
	हाल WLAN_CIPHER_SUITE_TKIP:
		वापस CIPHER_TKIP;
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस CIPHER_AES;
	शेष:
		वापस CIPHER_NONE;
	पूर्ण
पूर्ण

व्योम rt2x00crypto_create_tx_descriptor(काष्ठा rt2x00_dev *rt2x00dev,
				       काष्ठा sk_buff *skb,
				       काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_key_conf *hw_key = tx_info->control.hw_key;

	अगर (!rt2x00_has_cap_hw_crypto(rt2x00dev) || !hw_key)
		वापस;

	__set_bit(ENTRY_TXD_ENCRYPT, &txdesc->flags);

	txdesc->cipher = rt2x00crypto_key_to_cipher(hw_key);

	अगर (hw_key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		__set_bit(ENTRY_TXD_ENCRYPT_PAIRWISE, &txdesc->flags);

	txdesc->key_idx = hw_key->hw_key_idx;
	txdesc->iv_offset = txdesc->header_length;
	txdesc->iv_len = hw_key->iv_len;

	अगर (!(hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_IV))
		__set_bit(ENTRY_TXD_ENCRYPT_IV, &txdesc->flags);

	अगर (!(hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_MMIC))
		__set_bit(ENTRY_TXD_ENCRYPT_MMIC, &txdesc->flags);
पूर्ण

अचिन्हित पूर्णांक rt2x00crypto_tx_overhead(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_key_conf *key = tx_info->control.hw_key;
	अचिन्हित पूर्णांक overhead = 0;

	अगर (!rt2x00_has_cap_hw_crypto(rt2x00dev) || !key)
		वापस overhead;

	/*
	 * Extend frame length to include IV/EIV/ICV/MMIC,
	 * note that these lengths should only be added when
	 * mac80211 करोes not generate it.
	 */
	overhead += key->icv_len;

	अगर (!(key->flags & IEEE80211_KEY_FLAG_GENERATE_IV))
		overhead += key->iv_len;

	अगर (!(key->flags & IEEE80211_KEY_FLAG_GENERATE_MMIC)) अणु
		अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP)
			overhead += 8;
	पूर्ण

	वापस overhead;
पूर्ण

व्योम rt2x00crypto_tx_copy_iv(काष्ठा sk_buff *skb, काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(skb);

	अगर (unlikely(!txdesc->iv_len))
		वापस;

	/* Copy IV/EIV data */
	स_नकल(skbdesc->iv, skb->data + txdesc->iv_offset, txdesc->iv_len);
पूर्ण

व्योम rt2x00crypto_tx_हटाओ_iv(काष्ठा sk_buff *skb, काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(skb);

	अगर (unlikely(!txdesc->iv_len))
		वापस;

	/* Copy IV/EIV data */
	स_नकल(skbdesc->iv, skb->data + txdesc->iv_offset, txdesc->iv_len);

	/* Move ieee80211 header */
	स_हटाओ(skb->data + txdesc->iv_len, skb->data, txdesc->iv_offset);

	/* Pull buffer to correct size */
	skb_pull(skb, txdesc->iv_len);
	txdesc->length -= txdesc->iv_len;

	/* IV/EIV data has officially been stripped */
	skbdesc->flags |= SKBDESC_IV_STRIPPED;
पूर्ण

व्योम rt2x00crypto_tx_insert_iv(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक header_length)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(skb);
	स्थिर अचिन्हित पूर्णांक iv_len =
	    ((!!(skbdesc->iv[0])) * 4) + ((!!(skbdesc->iv[1])) * 4);

	अगर (!(skbdesc->flags & SKBDESC_IV_STRIPPED))
		वापस;

	skb_push(skb, iv_len);

	/* Move ieee80211 header */
	स_हटाओ(skb->data, skb->data + iv_len, header_length);

	/* Copy IV/EIV data */
	स_नकल(skb->data + header_length, skbdesc->iv, iv_len);

	/* IV/EIV data has वापसed पूर्णांकo the frame */
	skbdesc->flags &= ~SKBDESC_IV_STRIPPED;
पूर्ण

व्योम rt2x00crypto_rx_insert_iv(काष्ठा sk_buff *skb,
			       अचिन्हित पूर्णांक header_length,
			       काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	अचिन्हित पूर्णांक payload_len = rxdesc->size - header_length;
	अचिन्हित पूर्णांक align = ALIGN_SIZE(skb, header_length);
	अचिन्हित पूर्णांक iv_len;
	अचिन्हित पूर्णांक icv_len;
	अचिन्हित पूर्णांक transfer = 0;

	/*
	 * WEP64/WEP128: Provides IV & ICV
	 * TKIP: Provides IV/EIV & ICV
	 * AES: Provies IV/EIV & ICV
	 */
	चयन (rxdesc->cipher) अणु
	हाल CIPHER_WEP64:
	हाल CIPHER_WEP128:
		iv_len = 4;
		icv_len = 4;
		अवरोध;
	हाल CIPHER_TKIP:
		iv_len = 8;
		icv_len = 4;
		अवरोध;
	हाल CIPHER_AES:
		iv_len = 8;
		icv_len = 8;
		अवरोध;
	शेष:
		/* Unsupport type */
		वापस;
	पूर्ण

	/*
	 * Make room क्रम new data. There are 2 possibilities
	 * either the alignment is alपढ़ोy present between
	 * the 802.11 header and payload. In that हाल we
	 * have to move the header less than the iv_len
	 * since we can use the alपढ़ोy available l2pad bytes
	 * क्रम the iv data.
	 * When the alignment must be added manually we must
	 * move the header more then iv_len since we must
	 * make room क्रम the payload move as well.
	 */
	अगर (rxdesc->dev_flags & RXDONE_L2PAD) अणु
		skb_push(skb, iv_len - align);
		skb_put(skb, icv_len);

		/* Move ieee80211 header */
		स_हटाओ(skb->data + transfer,
			skb->data + transfer + (iv_len - align),
			header_length);
		transfer += header_length;
	पूर्ण अन्यथा अणु
		skb_push(skb, iv_len + align);
		अगर (align < icv_len)
			skb_put(skb, icv_len - align);
		अन्यथा अगर (align > icv_len)
			skb_trim(skb, rxdesc->size + iv_len + icv_len);

		/* Move ieee80211 header */
		स_हटाओ(skb->data + transfer,
			skb->data + transfer + iv_len + align,
			header_length);
		transfer += header_length;
	पूर्ण

	/* Copy IV/EIV data */
	स_नकल(skb->data + transfer, rxdesc->iv, iv_len);
	transfer += iv_len;

	/*
	 * Move payload क्रम alignment purposes. Note that
	 * this is only needed when no l2 padding is present.
	 */
	अगर (!(rxdesc->dev_flags & RXDONE_L2PAD)) अणु
		स_हटाओ(skb->data + transfer,
			skb->data + transfer + align,
			payload_len);
	पूर्ण

	/*
	 * NOTE: Always count the payload as transferred,
	 * even when alignment was set to zero. This is required
	 * क्रम determining the correct offset क्रम the ICV data.
	 */
	transfer += payload_len;

	/*
	 * Copy ICV data
	 * AES appends 8 bytes, we can't fill the upper
	 * 4 bytes, but mac80211 करोesn't care about what
	 * we provide here anyway and strips it immediately.
	 */
	स_नकल(skb->data + transfer, &rxdesc->icv, 4);
	transfer += icv_len;

	/* IV/EIV/ICV has been inserted पूर्णांकo frame */
	rxdesc->size = transfer;
	rxdesc->flags &= ~RX_FLAG_IV_STRIPPED;
पूर्ण
