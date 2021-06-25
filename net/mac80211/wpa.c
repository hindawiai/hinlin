<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2004, Instant802 Networks, Inc.
 * Copyright 2008, Jouni Malinen <j@w1.fi>
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 * Copyright (C) 2020-2021 Intel Corporation
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/compiler.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/gfp.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/mac80211.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>

#समावेश "ieee80211_i.h"
#समावेश "michael.h"
#समावेश "tkip.h"
#समावेश "aes_ccm.h"
#समावेश "aes_cmac.h"
#समावेश "aes_gmac.h"
#समावेश "aes_gcm.h"
#समावेश "wpa.h"

ieee80211_tx_result
ieee80211_tx_h_michael_mic_add(काष्ठा ieee80211_tx_data *tx)
अणु
	u8 *data, *key, *mic;
	माप_प्रकार data_len;
	अचिन्हित पूर्णांक hdrlen;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा sk_buff *skb = tx->skb;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक tail;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अगर (!tx->key || tx->key->conf.cipher != WLAN_CIPHER_SUITE_TKIP ||
	    skb->len < 24 || !ieee80211_is_data_present(hdr->frame_control))
		वापस TX_CONTINUE;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	अगर (skb->len < hdrlen)
		वापस TX_DROP;

	data = skb->data + hdrlen;
	data_len = skb->len - hdrlen;

	अगर (unlikely(info->flags & IEEE80211_TX_INTFL_TKIP_MIC_FAILURE)) अणु
		/* Need to use software crypto क्रम the test */
		info->control.hw_key = शून्य;
	पूर्ण

	अगर (info->control.hw_key &&
	    (info->flags & IEEE80211_TX_CTL_DONTFRAG ||
	     ieee80211_hw_check(&tx->local->hw, SUPPORTS_TX_FRAG)) &&
	    !(tx->key->conf.flags & (IEEE80211_KEY_FLAG_GENERATE_MMIC |
				     IEEE80211_KEY_FLAG_PUT_MIC_SPACE))) अणु
		/* hwaccel - with no need क्रम SW-generated MMIC or MIC space */
		वापस TX_CONTINUE;
	पूर्ण

	tail = MICHAEL_MIC_LEN;
	अगर (!info->control.hw_key)
		tail += IEEE80211_TKIP_ICV_LEN;

	अगर (WARN(skb_tailroom(skb) < tail ||
		 skb_headroom(skb) < IEEE80211_TKIP_IV_LEN,
		 "mmic: not enough head/tail (%d/%d,%d/%d)\n",
		 skb_headroom(skb), IEEE80211_TKIP_IV_LEN,
		 skb_tailroom(skb), tail))
		वापस TX_DROP;

	mic = skb_put(skb, MICHAEL_MIC_LEN);

	अगर (tx->key->conf.flags & IEEE80211_KEY_FLAG_PUT_MIC_SPACE) अणु
		/* Zeroed MIC can help with debug */
		स_रखो(mic, 0, MICHAEL_MIC_LEN);
		वापस TX_CONTINUE;
	पूर्ण

	key = &tx->key->conf.key[NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY];
	michael_mic(key, hdr, data, data_len, mic);
	अगर (unlikely(info->flags & IEEE80211_TX_INTFL_TKIP_MIC_FAILURE))
		mic[0]++;

	वापस TX_CONTINUE;
पूर्ण


ieee80211_rx_result
ieee80211_rx_h_michael_mic_verअगरy(काष्ठा ieee80211_rx_data *rx)
अणु
	u8 *data, *key = शून्य;
	माप_प्रकार data_len;
	अचिन्हित पूर्णांक hdrlen;
	u8 mic[MICHAEL_MIC_LEN];
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	/*
	 * it makes no sense to check क्रम MIC errors on anything other
	 * than data frames.
	 */
	अगर (!ieee80211_is_data_present(hdr->frame_control))
		वापस RX_CONTINUE;

	/*
	 * No way to verअगरy the MIC अगर the hardware stripped it or
	 * the IV with the key index. In this हाल we have solely rely
	 * on the driver to set RX_FLAG_MMIC_ERROR in the event of a
	 * MIC failure report.
	 */
	अगर (status->flag & (RX_FLAG_MMIC_STRIPPED | RX_FLAG_IV_STRIPPED)) अणु
		अगर (status->flag & RX_FLAG_MMIC_ERROR)
			जाओ mic_fail_no_key;

		अगर (!(status->flag & RX_FLAG_IV_STRIPPED) && rx->key &&
		    rx->key->conf.cipher == WLAN_CIPHER_SUITE_TKIP)
			जाओ update_iv;

		वापस RX_CONTINUE;
	पूर्ण

	/*
	 * Some hardware seems to generate Michael MIC failure reports; even
	 * though, the frame was not encrypted with TKIP and thereक्रमe has no
	 * MIC. Ignore the flag them to aव्योम triggering countermeasures.
	 */
	अगर (!rx->key || rx->key->conf.cipher != WLAN_CIPHER_SUITE_TKIP ||
	    !(status->flag & RX_FLAG_DECRYPTED))
		वापस RX_CONTINUE;

	अगर (rx->sdata->vअगर.type == NL80211_IFTYPE_AP && rx->key->conf.keyidx) अणु
		/*
		 * APs with pairwise keys should never receive Michael MIC
		 * errors क्रम non-zero keyidx because these are reserved क्रम
		 * group keys and only the AP is sending real multicast
		 * frames in the BSS.
		 */
		वापस RX_DROP_UNUSABLE;
	पूर्ण

	अगर (status->flag & RX_FLAG_MMIC_ERROR)
		जाओ mic_fail;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	अगर (skb->len < hdrlen + MICHAEL_MIC_LEN)
		वापस RX_DROP_UNUSABLE;

	अगर (skb_linearize(rx->skb))
		वापस RX_DROP_UNUSABLE;
	hdr = (व्योम *)skb->data;

	data = skb->data + hdrlen;
	data_len = skb->len - hdrlen - MICHAEL_MIC_LEN;
	key = &rx->key->conf.key[NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY];
	michael_mic(key, hdr, data, data_len, mic);
	अगर (crypto_memneq(mic, data + data_len, MICHAEL_MIC_LEN))
		जाओ mic_fail;

	/* हटाओ Michael MIC from payload */
	skb_trim(skb, skb->len - MICHAEL_MIC_LEN);

update_iv:
	/* update IV in key inक्रमmation to be able to detect replays */
	rx->key->u.tkip.rx[rx->security_idx].iv32 = rx->tkip.iv32;
	rx->key->u.tkip.rx[rx->security_idx].iv16 = rx->tkip.iv16;

	वापस RX_CONTINUE;

mic_fail:
	rx->key->u.tkip.mic_failures++;

mic_fail_no_key:
	/*
	 * In some हालs the key can be unset - e.g. a multicast packet, in
	 * a driver that supports HW encryption. Send up the key idx only अगर
	 * the key is set.
	 */
	cfg80211_michael_mic_failure(rx->sdata->dev, hdr->addr2,
				     is_multicast_ether_addr(hdr->addr1) ?
				     NL80211_KEYTYPE_GROUP :
				     NL80211_KEYTYPE_PAIRWISE,
				     rx->key ? rx->key->conf.keyidx : -1,
				     शून्य, GFP_ATOMIC);
	वापस RX_DROP_UNUSABLE;
पूर्ण

अटल पूर्णांक tkip_encrypt_skb(काष्ठा ieee80211_tx_data *tx, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_key *key = tx->key;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	अचिन्हित पूर्णांक hdrlen;
	पूर्णांक len, tail;
	u64 pn;
	u8 *pos;

	अगर (info->control.hw_key &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_IV) &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE)) अणु
		/* hwaccel - with no need क्रम software-generated IV */
		वापस 0;
	पूर्ण

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	len = skb->len - hdrlen;

	अगर (info->control.hw_key)
		tail = 0;
	अन्यथा
		tail = IEEE80211_TKIP_ICV_LEN;

	अगर (WARN_ON(skb_tailroom(skb) < tail ||
		    skb_headroom(skb) < IEEE80211_TKIP_IV_LEN))
		वापस -1;

	pos = skb_push(skb, IEEE80211_TKIP_IV_LEN);
	स_हटाओ(pos, pos + IEEE80211_TKIP_IV_LEN, hdrlen);
	pos += hdrlen;

	/* the HW only needs room क्रम the IV, but not the actual IV */
	अगर (info->control.hw_key &&
	    (info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE))
		वापस 0;

	/* Increase IV क्रम the frame */
	pn = atomic64_inc_वापस(&key->conf.tx_pn);
	pos = ieee80211_tkip_add_iv(pos, &key->conf, pn);

	/* hwaccel - with software IV */
	अगर (info->control.hw_key)
		वापस 0;

	/* Add room क्रम ICV */
	skb_put(skb, IEEE80211_TKIP_ICV_LEN);

	वापस ieee80211_tkip_encrypt_data(&tx->local->wep_tx_ctx,
					   key, skb, pos, len);
पूर्ण


ieee80211_tx_result
ieee80211_crypto_tkip_encrypt(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;

	ieee80211_tx_set_रक्षित(tx);

	skb_queue_walk(&tx->skbs, skb) अणु
		अगर (tkip_encrypt_skb(tx, skb) < 0)
			वापस TX_DROP;
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण


ieee80211_rx_result
ieee80211_crypto_tkip_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) rx->skb->data;
	पूर्णांक hdrlen, res, hwaccel = 0;
	काष्ठा ieee80211_key *key = rx->key;
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);

	hdrlen = ieee80211_hdrlen(hdr->frame_control);

	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस RX_CONTINUE;

	अगर (!rx->sta || skb->len - hdrlen < 12)
		वापस RX_DROP_UNUSABLE;

	/* it may be possible to optimize this a bit more */
	अगर (skb_linearize(rx->skb))
		वापस RX_DROP_UNUSABLE;
	hdr = (व्योम *)skb->data;

	/*
	 * Let TKIP code verअगरy IV, but skip decryption.
	 * In the हाल where hardware checks the IV as well,
	 * we करोn't even get here, see ieee80211_rx_h_decrypt()
	 */
	अगर (status->flag & RX_FLAG_DECRYPTED)
		hwaccel = 1;

	res = ieee80211_tkip_decrypt_data(&rx->local->wep_rx_ctx,
					  key, skb->data + hdrlen,
					  skb->len - hdrlen, rx->sta->sta.addr,
					  hdr->addr1, hwaccel, rx->security_idx,
					  &rx->tkip.iv32,
					  &rx->tkip.iv16);
	अगर (res != TKIP_DECRYPT_OK)
		वापस RX_DROP_UNUSABLE;

	/* Trim ICV */
	अगर (!(status->flag & RX_FLAG_ICV_STRIPPED))
		skb_trim(skb, skb->len - IEEE80211_TKIP_ICV_LEN);

	/* Remove IV */
	स_हटाओ(skb->data + IEEE80211_TKIP_IV_LEN, skb->data, hdrlen);
	skb_pull(skb, IEEE80211_TKIP_IV_LEN);

	वापस RX_CONTINUE;
पूर्ण


अटल व्योम ccmp_special_blocks(काष्ठा sk_buff *skb, u8 *pn, u8 *b_0, u8 *aad)
अणु
	__le16 mask_fc;
	पूर्णांक a4_included, mgmt;
	u8 qos_tid;
	u16 len_a;
	अचिन्हित पूर्णांक hdrlen;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	/*
	 * Mask FC: zero subtype b4 b5 b6 (अगर not mgmt)
	 * Retry, PwrMgt, MoreData; set Protected
	 */
	mgmt = ieee80211_is_mgmt(hdr->frame_control);
	mask_fc = hdr->frame_control;
	mask_fc &= ~cpu_to_le16(IEEE80211_FCTL_RETRY |
				IEEE80211_FCTL_PM | IEEE80211_FCTL_MOREDATA);
	अगर (!mgmt)
		mask_fc &= ~cpu_to_le16(0x0070);
	mask_fc |= cpu_to_le16(IEEE80211_FCTL_PROTECTED);

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	len_a = hdrlen - 2;
	a4_included = ieee80211_has_a4(hdr->frame_control);

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		qos_tid = ieee80211_get_tid(hdr);
	अन्यथा
		qos_tid = 0;

	/* In CCM, the initial vectors (IV) used क्रम CTR mode encryption and CBC
	 * mode authentication are not allowed to collide, yet both are derived
	 * from this vector b_0. We only set L := 1 here to indicate that the
	 * data size can be represented in (L+1) bytes. The CCM layer will take
	 * care of storing the data length in the top (L+1) bytes and setting
	 * and clearing the other bits as is required to derive the two IVs.
	 */
	b_0[0] = 0x1;

	/* Nonce: Nonce Flags | A2 | PN
	 * Nonce Flags: Priority (b0..b3) | Management (b4) | Reserved (b5..b7)
	 */
	b_0[1] = qos_tid | (mgmt << 4);
	स_नकल(&b_0[2], hdr->addr2, ETH_ALEN);
	स_नकल(&b_0[8], pn, IEEE80211_CCMP_PN_LEN);

	/* AAD (extra authenticate-only data) / masked 802.11 header
	 * FC | A1 | A2 | A3 | SC | [A4] | [QC] */
	put_unaligned_be16(len_a, &aad[0]);
	put_unaligned(mask_fc, (__le16 *)&aad[2]);
	स_नकल(&aad[4], &hdr->addr1, 3 * ETH_ALEN);

	/* Mask Seq#, leave Frag# */
	aad[22] = *((u8 *) &hdr->seq_ctrl) & 0x0f;
	aad[23] = 0;

	अगर (a4_included) अणु
		स_नकल(&aad[24], hdr->addr4, ETH_ALEN);
		aad[30] = qos_tid;
		aad[31] = 0;
	पूर्ण अन्यथा अणु
		स_रखो(&aad[24], 0, ETH_ALEN + IEEE80211_QOS_CTL_LEN);
		aad[24] = qos_tid;
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम ccmp_pn2hdr(u8 *hdr, u8 *pn, पूर्णांक key_id)
अणु
	hdr[0] = pn[5];
	hdr[1] = pn[4];
	hdr[2] = 0;
	hdr[3] = 0x20 | (key_id << 6);
	hdr[4] = pn[3];
	hdr[5] = pn[2];
	hdr[6] = pn[1];
	hdr[7] = pn[0];
पूर्ण


अटल अंतरभूत व्योम ccmp_hdr2pn(u8 *pn, u8 *hdr)
अणु
	pn[0] = hdr[7];
	pn[1] = hdr[6];
	pn[2] = hdr[5];
	pn[3] = hdr[4];
	pn[4] = hdr[1];
	pn[5] = hdr[0];
पूर्ण


अटल पूर्णांक ccmp_encrypt_skb(काष्ठा ieee80211_tx_data *tx, काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक mic_len)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_key *key = tx->key;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक hdrlen, len, tail;
	u8 *pos;
	u8 pn[6];
	u64 pn64;
	u8 aad[CCM_AAD_LEN];
	u8 b_0[AES_BLOCK_SIZE];

	अगर (info->control.hw_key &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_IV) &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE) &&
	    !((info->control.hw_key->flags &
	       IEEE80211_KEY_FLAG_GENERATE_IV_MGMT) &&
	      ieee80211_is_mgmt(hdr->frame_control))) अणु
		/*
		 * hwaccel has no need क्रम pपुनः_स्मृतिated room क्रम CCMP
		 * header or MIC fields
		 */
		वापस 0;
	पूर्ण

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	len = skb->len - hdrlen;

	अगर (info->control.hw_key)
		tail = 0;
	अन्यथा
		tail = mic_len;

	अगर (WARN_ON(skb_tailroom(skb) < tail ||
		    skb_headroom(skb) < IEEE80211_CCMP_HDR_LEN))
		वापस -1;

	pos = skb_push(skb, IEEE80211_CCMP_HDR_LEN);
	स_हटाओ(pos, pos + IEEE80211_CCMP_HDR_LEN, hdrlen);

	/* the HW only needs room क्रम the IV, but not the actual IV */
	अगर (info->control.hw_key &&
	    (info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE))
		वापस 0;

	hdr = (काष्ठा ieee80211_hdr *) pos;
	pos += hdrlen;

	pn64 = atomic64_inc_वापस(&key->conf.tx_pn);

	pn[5] = pn64;
	pn[4] = pn64 >> 8;
	pn[3] = pn64 >> 16;
	pn[2] = pn64 >> 24;
	pn[1] = pn64 >> 32;
	pn[0] = pn64 >> 40;

	ccmp_pn2hdr(pos, pn, key->conf.keyidx);

	/* hwaccel - with software CCMP header */
	अगर (info->control.hw_key)
		वापस 0;

	pos += IEEE80211_CCMP_HDR_LEN;
	ccmp_special_blocks(skb, pn, b_0, aad);
	वापस ieee80211_aes_ccm_encrypt(key->u.ccmp.tfm, b_0, aad, pos, len,
					 skb_put(skb, mic_len));
पूर्ण


ieee80211_tx_result
ieee80211_crypto_ccmp_encrypt(काष्ठा ieee80211_tx_data *tx,
			      अचिन्हित पूर्णांक mic_len)
अणु
	काष्ठा sk_buff *skb;

	ieee80211_tx_set_रक्षित(tx);

	skb_queue_walk(&tx->skbs, skb) अणु
		अगर (ccmp_encrypt_skb(tx, skb, mic_len) < 0)
			वापस TX_DROP;
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण


ieee80211_rx_result
ieee80211_crypto_ccmp_decrypt(काष्ठा ieee80211_rx_data *rx,
			      अचिन्हित पूर्णांक mic_len)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	पूर्णांक hdrlen;
	काष्ठा ieee80211_key *key = rx->key;
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	u8 pn[IEEE80211_CCMP_PN_LEN];
	पूर्णांक data_len;
	पूर्णांक queue;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);

	अगर (!ieee80211_is_data(hdr->frame_control) &&
	    !ieee80211_is_robust_mgmt_frame(skb))
		वापस RX_CONTINUE;

	अगर (status->flag & RX_FLAG_DECRYPTED) अणु
		अगर (!pskb_may_pull(rx->skb, hdrlen + IEEE80211_CCMP_HDR_LEN))
			वापस RX_DROP_UNUSABLE;
		अगर (status->flag & RX_FLAG_MIC_STRIPPED)
			mic_len = 0;
	पूर्ण अन्यथा अणु
		अगर (skb_linearize(rx->skb))
			वापस RX_DROP_UNUSABLE;
	पूर्ण

	data_len = skb->len - hdrlen - IEEE80211_CCMP_HDR_LEN - mic_len;
	अगर (!rx->sta || data_len < 0)
		वापस RX_DROP_UNUSABLE;

	अगर (!(status->flag & RX_FLAG_PN_VALIDATED)) अणु
		पूर्णांक res;

		ccmp_hdr2pn(pn, skb->data + hdrlen);

		queue = rx->security_idx;

		res = स_भेद(pn, key->u.ccmp.rx_pn[queue],
			     IEEE80211_CCMP_PN_LEN);
		अगर (res < 0 ||
		    (!res && !(status->flag & RX_FLAG_ALLOW_SAME_PN))) अणु
			key->u.ccmp.replays++;
			वापस RX_DROP_UNUSABLE;
		पूर्ण

		अगर (!(status->flag & RX_FLAG_DECRYPTED)) अणु
			u8 aad[2 * AES_BLOCK_SIZE];
			u8 b_0[AES_BLOCK_SIZE];
			/* hardware didn't decrypt/verअगरy MIC */
			ccmp_special_blocks(skb, pn, b_0, aad);

			अगर (ieee80211_aes_ccm_decrypt(
				    key->u.ccmp.tfm, b_0, aad,
				    skb->data + hdrlen + IEEE80211_CCMP_HDR_LEN,
				    data_len,
				    skb->data + skb->len - mic_len))
				वापस RX_DROP_UNUSABLE;
		पूर्ण

		स_नकल(key->u.ccmp.rx_pn[queue], pn, IEEE80211_CCMP_PN_LEN);
		अगर (unlikely(ieee80211_is_frag(hdr)))
			स_नकल(rx->ccm_gcm.pn, pn, IEEE80211_CCMP_PN_LEN);
	पूर्ण

	/* Remove CCMP header and MIC */
	अगर (pskb_trim(skb, skb->len - mic_len))
		वापस RX_DROP_UNUSABLE;
	स_हटाओ(skb->data + IEEE80211_CCMP_HDR_LEN, skb->data, hdrlen);
	skb_pull(skb, IEEE80211_CCMP_HDR_LEN);

	वापस RX_CONTINUE;
पूर्ण

अटल व्योम gcmp_special_blocks(काष्ठा sk_buff *skb, u8 *pn, u8 *j_0, u8 *aad)
अणु
	__le16 mask_fc;
	u8 qos_tid;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	स_नकल(j_0, hdr->addr2, ETH_ALEN);
	स_नकल(&j_0[ETH_ALEN], pn, IEEE80211_GCMP_PN_LEN);
	j_0[13] = 0;
	j_0[14] = 0;
	j_0[AES_BLOCK_SIZE - 1] = 0x01;

	/* AAD (extra authenticate-only data) / masked 802.11 header
	 * FC | A1 | A2 | A3 | SC | [A4] | [QC]
	 */
	put_unaligned_be16(ieee80211_hdrlen(hdr->frame_control) - 2, &aad[0]);
	/* Mask FC: zero subtype b4 b5 b6 (अगर not mgmt)
	 * Retry, PwrMgt, MoreData; set Protected
	 */
	mask_fc = hdr->frame_control;
	mask_fc &= ~cpu_to_le16(IEEE80211_FCTL_RETRY |
				IEEE80211_FCTL_PM | IEEE80211_FCTL_MOREDATA);
	अगर (!ieee80211_is_mgmt(hdr->frame_control))
		mask_fc &= ~cpu_to_le16(0x0070);
	mask_fc |= cpu_to_le16(IEEE80211_FCTL_PROTECTED);

	put_unaligned(mask_fc, (__le16 *)&aad[2]);
	स_नकल(&aad[4], &hdr->addr1, 3 * ETH_ALEN);

	/* Mask Seq#, leave Frag# */
	aad[22] = *((u8 *)&hdr->seq_ctrl) & 0x0f;
	aad[23] = 0;

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		qos_tid = ieee80211_get_tid(hdr);
	अन्यथा
		qos_tid = 0;

	अगर (ieee80211_has_a4(hdr->frame_control)) अणु
		स_नकल(&aad[24], hdr->addr4, ETH_ALEN);
		aad[30] = qos_tid;
		aad[31] = 0;
	पूर्ण अन्यथा अणु
		स_रखो(&aad[24], 0, ETH_ALEN + IEEE80211_QOS_CTL_LEN);
		aad[24] = qos_tid;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम gcmp_pn2hdr(u8 *hdr, स्थिर u8 *pn, पूर्णांक key_id)
अणु
	hdr[0] = pn[5];
	hdr[1] = pn[4];
	hdr[2] = 0;
	hdr[3] = 0x20 | (key_id << 6);
	hdr[4] = pn[3];
	hdr[5] = pn[2];
	hdr[6] = pn[1];
	hdr[7] = pn[0];
पूर्ण

अटल अंतरभूत व्योम gcmp_hdr2pn(u8 *pn, स्थिर u8 *hdr)
अणु
	pn[0] = hdr[7];
	pn[1] = hdr[6];
	pn[2] = hdr[5];
	pn[3] = hdr[4];
	pn[4] = hdr[1];
	pn[5] = hdr[0];
पूर्ण

अटल पूर्णांक gcmp_encrypt_skb(काष्ठा ieee80211_tx_data *tx, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_key *key = tx->key;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक hdrlen, len, tail;
	u8 *pos;
	u8 pn[6];
	u64 pn64;
	u8 aad[GCM_AAD_LEN];
	u8 j_0[AES_BLOCK_SIZE];

	अगर (info->control.hw_key &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_IV) &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE) &&
	    !((info->control.hw_key->flags &
	       IEEE80211_KEY_FLAG_GENERATE_IV_MGMT) &&
	      ieee80211_is_mgmt(hdr->frame_control))) अणु
		/* hwaccel has no need क्रम pपुनः_स्मृतिated room क्रम GCMP
		 * header or MIC fields
		 */
		वापस 0;
	पूर्ण

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	len = skb->len - hdrlen;

	अगर (info->control.hw_key)
		tail = 0;
	अन्यथा
		tail = IEEE80211_GCMP_MIC_LEN;

	अगर (WARN_ON(skb_tailroom(skb) < tail ||
		    skb_headroom(skb) < IEEE80211_GCMP_HDR_LEN))
		वापस -1;

	pos = skb_push(skb, IEEE80211_GCMP_HDR_LEN);
	स_हटाओ(pos, pos + IEEE80211_GCMP_HDR_LEN, hdrlen);
	skb_set_network_header(skb, skb_network_offset(skb) +
				    IEEE80211_GCMP_HDR_LEN);

	/* the HW only needs room क्रम the IV, but not the actual IV */
	अगर (info->control.hw_key &&
	    (info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE))
		वापस 0;

	hdr = (काष्ठा ieee80211_hdr *)pos;
	pos += hdrlen;

	pn64 = atomic64_inc_वापस(&key->conf.tx_pn);

	pn[5] = pn64;
	pn[4] = pn64 >> 8;
	pn[3] = pn64 >> 16;
	pn[2] = pn64 >> 24;
	pn[1] = pn64 >> 32;
	pn[0] = pn64 >> 40;

	gcmp_pn2hdr(pos, pn, key->conf.keyidx);

	/* hwaccel - with software GCMP header */
	अगर (info->control.hw_key)
		वापस 0;

	pos += IEEE80211_GCMP_HDR_LEN;
	gcmp_special_blocks(skb, pn, j_0, aad);
	वापस ieee80211_aes_gcm_encrypt(key->u.gcmp.tfm, j_0, aad, pos, len,
					 skb_put(skb, IEEE80211_GCMP_MIC_LEN));
पूर्ण

ieee80211_tx_result
ieee80211_crypto_gcmp_encrypt(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;

	ieee80211_tx_set_रक्षित(tx);

	skb_queue_walk(&tx->skbs, skb) अणु
		अगर (gcmp_encrypt_skb(tx, skb) < 0)
			वापस TX_DROP;
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण

ieee80211_rx_result
ieee80211_crypto_gcmp_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	पूर्णांक hdrlen;
	काष्ठा ieee80211_key *key = rx->key;
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	u8 pn[IEEE80211_GCMP_PN_LEN];
	पूर्णांक data_len, queue, mic_len = IEEE80211_GCMP_MIC_LEN;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);

	अगर (!ieee80211_is_data(hdr->frame_control) &&
	    !ieee80211_is_robust_mgmt_frame(skb))
		वापस RX_CONTINUE;

	अगर (status->flag & RX_FLAG_DECRYPTED) अणु
		अगर (!pskb_may_pull(rx->skb, hdrlen + IEEE80211_GCMP_HDR_LEN))
			वापस RX_DROP_UNUSABLE;
		अगर (status->flag & RX_FLAG_MIC_STRIPPED)
			mic_len = 0;
	पूर्ण अन्यथा अणु
		अगर (skb_linearize(rx->skb))
			वापस RX_DROP_UNUSABLE;
	पूर्ण

	data_len = skb->len - hdrlen - IEEE80211_GCMP_HDR_LEN - mic_len;
	अगर (!rx->sta || data_len < 0)
		वापस RX_DROP_UNUSABLE;

	अगर (!(status->flag & RX_FLAG_PN_VALIDATED)) अणु
		पूर्णांक res;

		gcmp_hdr2pn(pn, skb->data + hdrlen);

		queue = rx->security_idx;

		res = स_भेद(pn, key->u.gcmp.rx_pn[queue],
			     IEEE80211_GCMP_PN_LEN);
		अगर (res < 0 ||
		    (!res && !(status->flag & RX_FLAG_ALLOW_SAME_PN))) अणु
			key->u.gcmp.replays++;
			वापस RX_DROP_UNUSABLE;
		पूर्ण

		अगर (!(status->flag & RX_FLAG_DECRYPTED)) अणु
			u8 aad[2 * AES_BLOCK_SIZE];
			u8 j_0[AES_BLOCK_SIZE];
			/* hardware didn't decrypt/verअगरy MIC */
			gcmp_special_blocks(skb, pn, j_0, aad);

			अगर (ieee80211_aes_gcm_decrypt(
				    key->u.gcmp.tfm, j_0, aad,
				    skb->data + hdrlen + IEEE80211_GCMP_HDR_LEN,
				    data_len,
				    skb->data + skb->len -
				    IEEE80211_GCMP_MIC_LEN))
				वापस RX_DROP_UNUSABLE;
		पूर्ण

		स_नकल(key->u.gcmp.rx_pn[queue], pn, IEEE80211_GCMP_PN_LEN);
		अगर (unlikely(ieee80211_is_frag(hdr)))
			स_नकल(rx->ccm_gcm.pn, pn, IEEE80211_CCMP_PN_LEN);
	पूर्ण

	/* Remove GCMP header and MIC */
	अगर (pskb_trim(skb, skb->len - mic_len))
		वापस RX_DROP_UNUSABLE;
	स_हटाओ(skb->data + IEEE80211_GCMP_HDR_LEN, skb->data, hdrlen);
	skb_pull(skb, IEEE80211_GCMP_HDR_LEN);

	वापस RX_CONTINUE;
पूर्ण

अटल ieee80211_tx_result
ieee80211_crypto_cs_encrypt(काष्ठा ieee80211_tx_data *tx,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_key *key = tx->key;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक hdrlen;
	u8 *pos, iv_len = key->conf.iv_len;

	अगर (info->control.hw_key &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE)) अणु
		/* hwaccel has no need क्रम pपुनः_स्मृतिated head room */
		वापस TX_CONTINUE;
	पूर्ण

	अगर (unlikely(skb_headroom(skb) < iv_len &&
		     pskb_expand_head(skb, iv_len, 0, GFP_ATOMIC)))
		वापस TX_DROP;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);

	pos = skb_push(skb, iv_len);
	स_हटाओ(pos, pos + iv_len, hdrlen);

	वापस TX_CONTINUE;
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_crypto_cs_pn_compare(u8 *pn1, u8 *pn2, पूर्णांक len)
अणु
	पूर्णांक i;

	/* pn is little endian */
	क्रम (i = len - 1; i >= 0; i--) अणु
		अगर (pn1[i] < pn2[i])
			वापस -1;
		अन्यथा अगर (pn1[i] > pn2[i])
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल ieee80211_rx_result
ieee80211_crypto_cs_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा ieee80211_key *key = rx->key;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;
	स्थिर काष्ठा ieee80211_cipher_scheme *cs = शून्य;
	पूर्णांक hdrlen = ieee80211_hdrlen(hdr->frame_control);
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	पूर्णांक data_len;
	u8 *rx_pn;
	u8 *skb_pn;
	u8 qos_tid;

	अगर (!rx->sta || !rx->sta->cipher_scheme ||
	    !(status->flag & RX_FLAG_DECRYPTED))
		वापस RX_DROP_UNUSABLE;

	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस RX_CONTINUE;

	cs = rx->sta->cipher_scheme;

	data_len = rx->skb->len - hdrlen - cs->hdr_len;

	अगर (data_len < 0)
		वापस RX_DROP_UNUSABLE;

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		qos_tid = ieee80211_get_tid(hdr);
	अन्यथा
		qos_tid = 0;

	अगर (skb_linearize(rx->skb))
		वापस RX_DROP_UNUSABLE;

	hdr = (काष्ठा ieee80211_hdr *)rx->skb->data;

	rx_pn = key->u.gen.rx_pn[qos_tid];
	skb_pn = rx->skb->data + hdrlen + cs->pn_off;

	अगर (ieee80211_crypto_cs_pn_compare(skb_pn, rx_pn, cs->pn_len) <= 0)
		वापस RX_DROP_UNUSABLE;

	स_नकल(rx_pn, skb_pn, cs->pn_len);

	/* हटाओ security header and MIC */
	अगर (pskb_trim(rx->skb, rx->skb->len - cs->mic_len))
		वापस RX_DROP_UNUSABLE;

	स_हटाओ(rx->skb->data + cs->hdr_len, rx->skb->data, hdrlen);
	skb_pull(rx->skb, cs->hdr_len);

	वापस RX_CONTINUE;
पूर्ण

अटल व्योम bip_aad(काष्ठा sk_buff *skb, u8 *aad)
अणु
	__le16 mask_fc;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;

	/* BIP AAD: FC(masked) || A1 || A2 || A3 */

	/* FC type/subtype */
	/* Mask FC Retry, PwrMgt, MoreData flags to zero */
	mask_fc = hdr->frame_control;
	mask_fc &= ~cpu_to_le16(IEEE80211_FCTL_RETRY | IEEE80211_FCTL_PM |
				IEEE80211_FCTL_MOREDATA);
	put_unaligned(mask_fc, (__le16 *) &aad[0]);
	/* A1 || A2 || A3 */
	स_नकल(aad + 2, &hdr->addr1, 3 * ETH_ALEN);
पूर्ण


अटल अंतरभूत व्योम bip_ipn_set64(u8 *d, u64 pn)
अणु
	*d++ = pn;
	*d++ = pn >> 8;
	*d++ = pn >> 16;
	*d++ = pn >> 24;
	*d++ = pn >> 32;
	*d = pn >> 40;
पूर्ण

अटल अंतरभूत व्योम bip_ipn_swap(u8 *d, स्थिर u8 *s)
अणु
	*d++ = s[5];
	*d++ = s[4];
	*d++ = s[3];
	*d++ = s[2];
	*d++ = s[1];
	*d = s[0];
पूर्ण


ieee80211_tx_result
ieee80211_crypto_aes_cmac_encrypt(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_key *key = tx->key;
	काष्ठा ieee80211_mmie *mmie;
	u8 aad[20];
	u64 pn64;

	अगर (WARN_ON(skb_queue_len(&tx->skbs) != 1))
		वापस TX_DROP;

	skb = skb_peek(&tx->skbs);

	info = IEEE80211_SKB_CB(skb);

	अगर (info->control.hw_key &&
	    !(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_MMIE))
		वापस TX_CONTINUE;

	अगर (WARN_ON(skb_tailroom(skb) < माप(*mmie)))
		वापस TX_DROP;

	mmie = skb_put(skb, माप(*mmie));
	mmie->element_id = WLAN_EID_MMIE;
	mmie->length = माप(*mmie) - 2;
	mmie->key_id = cpu_to_le16(key->conf.keyidx);

	/* PN = PN + 1 */
	pn64 = atomic64_inc_वापस(&key->conf.tx_pn);

	bip_ipn_set64(mmie->sequence_number, pn64);

	अगर (info->control.hw_key)
		वापस TX_CONTINUE;

	bip_aad(skb, aad);

	/*
	 * MIC = AES-128-CMAC(IGTK, AAD || Management Frame Body || MMIE, 64)
	 */
	ieee80211_aes_cmac(key->u.aes_cmac.tfm, aad,
			   skb->data + 24, skb->len - 24, mmie->mic);

	वापस TX_CONTINUE;
पूर्ण

ieee80211_tx_result
ieee80211_crypto_aes_cmac_256_encrypt(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_key *key = tx->key;
	काष्ठा ieee80211_mmie_16 *mmie;
	u8 aad[20];
	u64 pn64;

	अगर (WARN_ON(skb_queue_len(&tx->skbs) != 1))
		वापस TX_DROP;

	skb = skb_peek(&tx->skbs);

	info = IEEE80211_SKB_CB(skb);

	अगर (info->control.hw_key)
		वापस TX_CONTINUE;

	अगर (WARN_ON(skb_tailroom(skb) < माप(*mmie)))
		वापस TX_DROP;

	mmie = skb_put(skb, माप(*mmie));
	mmie->element_id = WLAN_EID_MMIE;
	mmie->length = माप(*mmie) - 2;
	mmie->key_id = cpu_to_le16(key->conf.keyidx);

	/* PN = PN + 1 */
	pn64 = atomic64_inc_वापस(&key->conf.tx_pn);

	bip_ipn_set64(mmie->sequence_number, pn64);

	bip_aad(skb, aad);

	/* MIC = AES-256-CMAC(IGTK, AAD || Management Frame Body || MMIE, 128)
	 */
	ieee80211_aes_cmac_256(key->u.aes_cmac.tfm, aad,
			       skb->data + 24, skb->len - 24, mmie->mic);

	वापस TX_CONTINUE;
पूर्ण

ieee80211_rx_result
ieee80211_crypto_aes_cmac_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_key *key = rx->key;
	काष्ठा ieee80211_mmie *mmie;
	u8 aad[20], mic[8], ipn[6];
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;

	अगर (!ieee80211_is_mgmt(hdr->frame_control))
		वापस RX_CONTINUE;

	/* management frames are alपढ़ोy linear */

	अगर (skb->len < 24 + माप(*mmie))
		वापस RX_DROP_UNUSABLE;

	mmie = (काष्ठा ieee80211_mmie *)
		(skb->data + skb->len - माप(*mmie));
	अगर (mmie->element_id != WLAN_EID_MMIE ||
	    mmie->length != माप(*mmie) - 2)
		वापस RX_DROP_UNUSABLE; /* Invalid MMIE */

	bip_ipn_swap(ipn, mmie->sequence_number);

	अगर (स_भेद(ipn, key->u.aes_cmac.rx_pn, 6) <= 0) अणु
		key->u.aes_cmac.replays++;
		वापस RX_DROP_UNUSABLE;
	पूर्ण

	अगर (!(status->flag & RX_FLAG_DECRYPTED)) अणु
		/* hardware didn't decrypt/verअगरy MIC */
		bip_aad(skb, aad);
		ieee80211_aes_cmac(key->u.aes_cmac.tfm, aad,
				   skb->data + 24, skb->len - 24, mic);
		अगर (crypto_memneq(mic, mmie->mic, माप(mmie->mic))) अणु
			key->u.aes_cmac.icverrors++;
			वापस RX_DROP_UNUSABLE;
		पूर्ण
	पूर्ण

	स_नकल(key->u.aes_cmac.rx_pn, ipn, 6);

	/* Remove MMIE */
	skb_trim(skb, skb->len - माप(*mmie));

	वापस RX_CONTINUE;
पूर्ण

ieee80211_rx_result
ieee80211_crypto_aes_cmac_256_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_key *key = rx->key;
	काष्ठा ieee80211_mmie_16 *mmie;
	u8 aad[20], mic[16], ipn[6];
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (!ieee80211_is_mgmt(hdr->frame_control))
		वापस RX_CONTINUE;

	/* management frames are alपढ़ोy linear */

	अगर (skb->len < 24 + माप(*mmie))
		वापस RX_DROP_UNUSABLE;

	mmie = (काष्ठा ieee80211_mmie_16 *)
		(skb->data + skb->len - माप(*mmie));
	अगर (mmie->element_id != WLAN_EID_MMIE ||
	    mmie->length != माप(*mmie) - 2)
		वापस RX_DROP_UNUSABLE; /* Invalid MMIE */

	bip_ipn_swap(ipn, mmie->sequence_number);

	अगर (स_भेद(ipn, key->u.aes_cmac.rx_pn, 6) <= 0) अणु
		key->u.aes_cmac.replays++;
		वापस RX_DROP_UNUSABLE;
	पूर्ण

	अगर (!(status->flag & RX_FLAG_DECRYPTED)) अणु
		/* hardware didn't decrypt/verअगरy MIC */
		bip_aad(skb, aad);
		ieee80211_aes_cmac_256(key->u.aes_cmac.tfm, aad,
				       skb->data + 24, skb->len - 24, mic);
		अगर (crypto_memneq(mic, mmie->mic, माप(mmie->mic))) अणु
			key->u.aes_cmac.icverrors++;
			वापस RX_DROP_UNUSABLE;
		पूर्ण
	पूर्ण

	स_नकल(key->u.aes_cmac.rx_pn, ipn, 6);

	/* Remove MMIE */
	skb_trim(skb, skb->len - माप(*mmie));

	वापस RX_CONTINUE;
पूर्ण

ieee80211_tx_result
ieee80211_crypto_aes_gmac_encrypt(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_key *key = tx->key;
	काष्ठा ieee80211_mmie_16 *mmie;
	काष्ठा ieee80211_hdr *hdr;
	u8 aad[GMAC_AAD_LEN];
	u64 pn64;
	u8 nonce[GMAC_NONCE_LEN];

	अगर (WARN_ON(skb_queue_len(&tx->skbs) != 1))
		वापस TX_DROP;

	skb = skb_peek(&tx->skbs);

	info = IEEE80211_SKB_CB(skb);

	अगर (info->control.hw_key)
		वापस TX_CONTINUE;

	अगर (WARN_ON(skb_tailroom(skb) < माप(*mmie)))
		वापस TX_DROP;

	mmie = skb_put(skb, माप(*mmie));
	mmie->element_id = WLAN_EID_MMIE;
	mmie->length = माप(*mmie) - 2;
	mmie->key_id = cpu_to_le16(key->conf.keyidx);

	/* PN = PN + 1 */
	pn64 = atomic64_inc_वापस(&key->conf.tx_pn);

	bip_ipn_set64(mmie->sequence_number, pn64);

	bip_aad(skb, aad);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	स_नकल(nonce, hdr->addr2, ETH_ALEN);
	bip_ipn_swap(nonce + ETH_ALEN, mmie->sequence_number);

	/* MIC = AES-GMAC(IGTK, AAD || Management Frame Body || MMIE, 128) */
	अगर (ieee80211_aes_gmac(key->u.aes_gmac.tfm, aad, nonce,
			       skb->data + 24, skb->len - 24, mmie->mic) < 0)
		वापस TX_DROP;

	वापस TX_CONTINUE;
पूर्ण

ieee80211_rx_result
ieee80211_crypto_aes_gmac_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	काष्ठा sk_buff *skb = rx->skb;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_key *key = rx->key;
	काष्ठा ieee80211_mmie_16 *mmie;
	u8 aad[GMAC_AAD_LEN], *mic, ipn[6], nonce[GMAC_NONCE_LEN];
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (!ieee80211_is_mgmt(hdr->frame_control))
		वापस RX_CONTINUE;

	/* management frames are alपढ़ोy linear */

	अगर (skb->len < 24 + माप(*mmie))
		वापस RX_DROP_UNUSABLE;

	mmie = (काष्ठा ieee80211_mmie_16 *)
		(skb->data + skb->len - माप(*mmie));
	अगर (mmie->element_id != WLAN_EID_MMIE ||
	    mmie->length != माप(*mmie) - 2)
		वापस RX_DROP_UNUSABLE; /* Invalid MMIE */

	bip_ipn_swap(ipn, mmie->sequence_number);

	अगर (स_भेद(ipn, key->u.aes_gmac.rx_pn, 6) <= 0) अणु
		key->u.aes_gmac.replays++;
		वापस RX_DROP_UNUSABLE;
	पूर्ण

	अगर (!(status->flag & RX_FLAG_DECRYPTED)) अणु
		/* hardware didn't decrypt/verअगरy MIC */
		bip_aad(skb, aad);

		स_नकल(nonce, hdr->addr2, ETH_ALEN);
		स_नकल(nonce + ETH_ALEN, ipn, 6);

		mic = kदो_स्मृति(GMAC_MIC_LEN, GFP_ATOMIC);
		अगर (!mic)
			वापस RX_DROP_UNUSABLE;
		अगर (ieee80211_aes_gmac(key->u.aes_gmac.tfm, aad, nonce,
				       skb->data + 24, skb->len - 24,
				       mic) < 0 ||
		    crypto_memneq(mic, mmie->mic, माप(mmie->mic))) अणु
			key->u.aes_gmac.icverrors++;
			kमुक्त(mic);
			वापस RX_DROP_UNUSABLE;
		पूर्ण
		kमुक्त(mic);
	पूर्ण

	स_नकल(key->u.aes_gmac.rx_pn, ipn, 6);

	/* Remove MMIE */
	skb_trim(skb, skb->len - माप(*mmie));

	वापस RX_CONTINUE;
पूर्ण

ieee80211_tx_result
ieee80211_crypto_hw_encrypt(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info = शून्य;
	ieee80211_tx_result res;

	skb_queue_walk(&tx->skbs, skb) अणु
		info  = IEEE80211_SKB_CB(skb);

		/* handle hw-only algorithm */
		अगर (!info->control.hw_key)
			वापस TX_DROP;

		अगर (tx->key->flags & KEY_FLAG_CIPHER_SCHEME) अणु
			res = ieee80211_crypto_cs_encrypt(tx, skb);
			अगर (res != TX_CONTINUE)
				वापस res;
		पूर्ण
	पूर्ण

	ieee80211_tx_set_रक्षित(tx);

	वापस TX_CONTINUE;
पूर्ण

ieee80211_rx_result
ieee80211_crypto_hw_decrypt(काष्ठा ieee80211_rx_data *rx)
अणु
	अगर (rx->sta && rx->sta->cipher_scheme)
		वापस ieee80211_crypto_cs_decrypt(rx);

	वापस RX_DROP_UNUSABLE;
पूर्ण
