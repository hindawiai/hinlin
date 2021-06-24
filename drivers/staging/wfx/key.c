<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Key management related functions.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>

#समावेश "key.h"
#समावेश "wfx.h"
#समावेश "hif_tx_mib.h"

अटल पूर्णांक wfx_alloc_key(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक idx;

	idx = ffs(~wdev->key_map) - 1;
	अगर (idx < 0 || idx >= MAX_KEY_ENTRIES)
		वापस -1;

	wdev->key_map |= BIT(idx);
	वापस idx;
पूर्ण

अटल व्योम wfx_मुक्त_key(काष्ठा wfx_dev *wdev, पूर्णांक idx)
अणु
	WARN(!(wdev->key_map & BIT(idx)), "inconsistent key allocation");
	wdev->key_map &= ~BIT(idx);
पूर्ण

अटल u8 fill_wep_pair(काष्ठा hअगर_wep_pairwise_key *msg,
			     काष्ठा ieee80211_key_conf *key, u8 *peer_addr)
अणु
	WARN(key->keylen > माप(msg->key_data), "inconsistent data");
	msg->key_length = key->keylen;
	स_नकल(msg->key_data, key->key, key->keylen);
	ether_addr_copy(msg->peer_address, peer_addr);
	वापस HIF_KEY_TYPE_WEP_PAIRWISE;
पूर्ण

अटल u8 fill_wep_group(काष्ठा hअगर_wep_group_key *msg,
			      काष्ठा ieee80211_key_conf *key)
अणु
	WARN(key->keylen > माप(msg->key_data), "inconsistent data");
	msg->key_id = key->keyidx;
	msg->key_length = key->keylen;
	स_नकल(msg->key_data, key->key, key->keylen);
	वापस HIF_KEY_TYPE_WEP_DEFAULT;
पूर्ण

अटल u8 fill_tkip_pair(काष्ठा hअगर_tkip_pairwise_key *msg,
			      काष्ठा ieee80211_key_conf *key, u8 *peer_addr)
अणु
	u8 *keybuf = key->key;

	WARN(key->keylen != माप(msg->tkip_key_data)
			    + माप(msg->tx_mic_key)
			    + माप(msg->rx_mic_key), "inconsistent data");
	स_नकल(msg->tkip_key_data, keybuf, माप(msg->tkip_key_data));
	keybuf += माप(msg->tkip_key_data);
	स_नकल(msg->tx_mic_key, keybuf, माप(msg->tx_mic_key));
	keybuf += माप(msg->tx_mic_key);
	स_नकल(msg->rx_mic_key, keybuf, माप(msg->rx_mic_key));
	ether_addr_copy(msg->peer_address, peer_addr);
	वापस HIF_KEY_TYPE_TKIP_PAIRWISE;
पूर्ण

अटल u8 fill_tkip_group(काष्ठा hअगर_tkip_group_key *msg,
			       काष्ठा ieee80211_key_conf *key,
			       काष्ठा ieee80211_key_seq *seq,
			       क्रमागत nl80211_अगरtype अगरtype)
अणु
	u8 *keybuf = key->key;

	WARN(key->keylen != माप(msg->tkip_key_data)
			    + 2 * माप(msg->rx_mic_key), "inconsistent data");
	msg->key_id = key->keyidx;
	स_नकल(msg->rx_sequence_counter,
	       &seq->tkip.iv16, माप(seq->tkip.iv16));
	स_नकल(msg->rx_sequence_counter + माप(u16),
	       &seq->tkip.iv32, माप(seq->tkip.iv32));
	स_नकल(msg->tkip_key_data, keybuf, माप(msg->tkip_key_data));
	keybuf += माप(msg->tkip_key_data);
	अगर (अगरtype == NL80211_IFTYPE_AP)
		// Use Tx MIC Key
		स_नकल(msg->rx_mic_key, keybuf + 0, माप(msg->rx_mic_key));
	अन्यथा
		// Use Rx MIC Key
		स_नकल(msg->rx_mic_key, keybuf + 8, माप(msg->rx_mic_key));
	वापस HIF_KEY_TYPE_TKIP_GROUP;
पूर्ण

अटल u8 fill_ccmp_pair(काष्ठा hअगर_aes_pairwise_key *msg,
			      काष्ठा ieee80211_key_conf *key, u8 *peer_addr)
अणु
	WARN(key->keylen != माप(msg->aes_key_data), "inconsistent data");
	ether_addr_copy(msg->peer_address, peer_addr);
	स_नकल(msg->aes_key_data, key->key, key->keylen);
	वापस HIF_KEY_TYPE_AES_PAIRWISE;
पूर्ण

अटल u8 fill_ccmp_group(काष्ठा hअगर_aes_group_key *msg,
			       काष्ठा ieee80211_key_conf *key,
			       काष्ठा ieee80211_key_seq *seq)
अणु
	WARN(key->keylen != माप(msg->aes_key_data), "inconsistent data");
	स_नकल(msg->aes_key_data, key->key, key->keylen);
	स_नकल(msg->rx_sequence_counter, seq->ccmp.pn, माप(seq->ccmp.pn));
	memreverse(msg->rx_sequence_counter, माप(seq->ccmp.pn));
	msg->key_id = key->keyidx;
	वापस HIF_KEY_TYPE_AES_GROUP;
पूर्ण

अटल u8 fill_sms4_pair(काष्ठा hअगर_wapi_pairwise_key *msg,
			      काष्ठा ieee80211_key_conf *key, u8 *peer_addr)
अणु
	u8 *keybuf = key->key;

	WARN(key->keylen != माप(msg->wapi_key_data)
			    + माप(msg->mic_key_data), "inconsistent data");
	ether_addr_copy(msg->peer_address, peer_addr);
	स_नकल(msg->wapi_key_data, keybuf, माप(msg->wapi_key_data));
	keybuf += माप(msg->wapi_key_data);
	स_नकल(msg->mic_key_data, keybuf, माप(msg->mic_key_data));
	msg->key_id = key->keyidx;
	वापस HIF_KEY_TYPE_WAPI_PAIRWISE;
पूर्ण

अटल u8 fill_sms4_group(काष्ठा hअगर_wapi_group_key *msg,
			       काष्ठा ieee80211_key_conf *key)
अणु
	u8 *keybuf = key->key;

	WARN(key->keylen != माप(msg->wapi_key_data)
			    + माप(msg->mic_key_data), "inconsistent data");
	स_नकल(msg->wapi_key_data, keybuf, माप(msg->wapi_key_data));
	keybuf += माप(msg->wapi_key_data);
	स_नकल(msg->mic_key_data, keybuf, माप(msg->mic_key_data));
	msg->key_id = key->keyidx;
	वापस HIF_KEY_TYPE_WAPI_GROUP;
पूर्ण

अटल u8 fill_aes_cmac_group(काष्ठा hअगर_igtk_group_key *msg,
				   काष्ठा ieee80211_key_conf *key,
				   काष्ठा ieee80211_key_seq *seq)
अणु
	WARN(key->keylen != माप(msg->igtk_key_data), "inconsistent data");
	स_नकल(msg->igtk_key_data, key->key, key->keylen);
	स_नकल(msg->ipn, seq->aes_cmac.pn, माप(seq->aes_cmac.pn));
	memreverse(msg->ipn, माप(seq->aes_cmac.pn));
	msg->key_id = key->keyidx;
	वापस HIF_KEY_TYPE_IGTK_GROUP;
पूर्ण

अटल पूर्णांक wfx_add_key(काष्ठा wfx_vअगर *wvअगर, काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key)
अणु
	पूर्णांक ret;
	काष्ठा hअगर_req_add_key k = अणु पूर्ण;
	काष्ठा ieee80211_key_seq seq;
	काष्ठा wfx_dev *wdev = wvअगर->wdev;
	पूर्णांक idx = wfx_alloc_key(wvअगर->wdev);
	bool pairwise = key->flags & IEEE80211_KEY_FLAG_PAIRWISE;

	WARN(key->flags & IEEE80211_KEY_FLAG_PAIRWISE && !sta, "inconsistent data");
	ieee80211_get_key_rx_seq(key, 0, &seq);
	अगर (idx < 0)
		वापस -EINVAL;
	k.पूर्णांक_id = wvअगर->id;
	k.entry_index = idx;
	अगर (key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	    key->cipher == WLAN_CIPHER_SUITE_WEP104) अणु
		अगर (pairwise)
			k.type = fill_wep_pair(&k.key.wep_pairwise_key, key,
					       sta->addr);
		अन्यथा
			k.type = fill_wep_group(&k.key.wep_group_key, key);
	पूर्ण अन्यथा अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
		अगर (pairwise)
			k.type = fill_tkip_pair(&k.key.tkip_pairwise_key, key,
						sta->addr);
		अन्यथा
			k.type = fill_tkip_group(&k.key.tkip_group_key, key,
						 &seq, wvअगर->vअगर->type);
	पूर्ण अन्यथा अगर (key->cipher == WLAN_CIPHER_SUITE_CCMP) अणु
		अगर (pairwise)
			k.type = fill_ccmp_pair(&k.key.aes_pairwise_key, key,
						sta->addr);
		अन्यथा
			k.type = fill_ccmp_group(&k.key.aes_group_key, key,
						 &seq);
	पूर्ण अन्यथा अगर (key->cipher == WLAN_CIPHER_SUITE_SMS4) अणु
		अगर (pairwise)
			k.type = fill_sms4_pair(&k.key.wapi_pairwise_key, key,
						sta->addr);
		अन्यथा
			k.type = fill_sms4_group(&k.key.wapi_group_key, key);
	पूर्ण अन्यथा अगर (key->cipher == WLAN_CIPHER_SUITE_AES_CMAC) अणु
		k.type = fill_aes_cmac_group(&k.key.igtk_group_key, key, &seq);
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIE;
	पूर्ण अन्यथा अणु
		dev_warn(wdev->dev, "unsupported key type %d\n", key->cipher);
		wfx_मुक्त_key(wdev, idx);
		वापस -EOPNOTSUPP;
	पूर्ण
	ret = hअगर_add_key(wdev, &k);
	अगर (ret) अणु
		wfx_मुक्त_key(wdev, idx);
		वापस -EOPNOTSUPP;
	पूर्ण
	key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE |
		      IEEE80211_KEY_FLAG_RESERVE_TAILROOM;
	key->hw_key_idx = idx;
	वापस 0;
पूर्ण

अटल पूर्णांक wfx_हटाओ_key(काष्ठा wfx_vअगर *wvअगर, काष्ठा ieee80211_key_conf *key)
अणु
	WARN(key->hw_key_idx >= MAX_KEY_ENTRIES, "corrupted hw_key_idx");
	wfx_मुक्त_key(wvअगर->wdev, key->hw_key_idx);
	वापस hअगर_हटाओ_key(wvअगर->wdev, key->hw_key_idx);
पूर्ण

पूर्णांक wfx_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		काष्ठा ieee80211_key_conf *key)
अणु
	पूर्णांक ret = -EOPNOTSUPP;
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	mutex_lock(&wvअगर->wdev->conf_mutex);
	अगर (cmd == SET_KEY)
		ret = wfx_add_key(wvअगर, sta, key);
	अगर (cmd == DISABLE_KEY)
		ret = wfx_हटाओ_key(wvअगर, key);
	mutex_unlock(&wvअगर->wdev->conf_mutex);
	वापस ret;
पूर्ण

