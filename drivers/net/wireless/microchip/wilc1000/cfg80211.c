<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#समावेश "cfg80211.h"

#घोषणा GO_NEG_REQ			0x00
#घोषणा GO_NEG_RSP			0x01
#घोषणा GO_NEG_CONF			0x02
#घोषणा P2P_INV_REQ			0x03
#घोषणा P2P_INV_RSP			0x04

#घोषणा WILC_INVALID_CHANNEL		0

/* Operation at 2.4 GHz with channels 1-13 */
#घोषणा WILC_WLAN_OPERATING_CLASS_2_4GHZ		0x51

अटल स्थिर काष्ठा ieee80211_txrx_stypes
	wilc_wfi_cfg80211_mgmt_types[NUM_NL80211_IFTYPES] = अणु
	[NL80211_IFTYPE_STATION] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_AP] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_CLIENT] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
			BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4)
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा wiphy_wowlan_support wowlan_support = अणु
	.flags = WIPHY_WOWLAN_ANY
पूर्ण;
#पूर्ण_अगर

काष्ठा wilc_p2p_mgmt_data अणु
	पूर्णांक size;
	u8 *buff;
पूर्ण;

काष्ठा wilc_p2p_pub_act_frame अणु
	u8 category;
	u8 action;
	u8 oui[3];
	u8 oui_type;
	u8 oui_subtype;
	u8 dialog_token;
	u8 elem[];
पूर्ण __packed;

काष्ठा wilc_venकरोr_specअगरic_ie अणु
	u8 tag_number;
	u8 tag_len;
	u8 oui[3];
	u8 oui_type;
	u8 attr[];
पूर्ण __packed;

काष्ठा wilc_attr_entry अणु
	u8  attr_type;
	__le16 attr_len;
	u8 val[];
पूर्ण __packed;

काष्ठा wilc_attr_oper_ch अणु
	u8 attr_type;
	__le16 attr_len;
	u8 country_code[IEEE80211_COUNTRY_STRING_LEN];
	u8 op_class;
	u8 op_channel;
पूर्ण __packed;

काष्ठा wilc_attr_ch_list अणु
	u8 attr_type;
	__le16 attr_len;
	u8 country_code[IEEE80211_COUNTRY_STRING_LEN];
	u8 elem[];
पूर्ण __packed;

काष्ठा wilc_ch_list_elem अणु
	u8 op_class;
	u8 no_of_channels;
	u8 ch_list[];
पूर्ण __packed;

अटल व्योम cfg_scan_result(क्रमागत scan_event scan_event,
			    काष्ठा wilc_rcvd_net_info *info, व्योम *user_व्योम)
अणु
	काष्ठा wilc_priv *priv = user_व्योम;

	अगर (!priv->cfg_scanning)
		वापस;

	अगर (scan_event == SCAN_EVENT_NETWORK_FOUND) अणु
		s32 freq;
		काष्ठा ieee80211_channel *channel;
		काष्ठा cfg80211_bss *bss;
		काष्ठा wiphy *wiphy = priv->dev->ieee80211_ptr->wiphy;

		अगर (!wiphy || !info)
			वापस;

		freq = ieee80211_channel_to_frequency((s32)info->ch,
						      NL80211_BAND_2GHZ);
		channel = ieee80211_get_channel(wiphy, freq);
		अगर (!channel)
			वापस;

		bss = cfg80211_inक्रमm_bss_frame(wiphy, channel, info->mgmt,
						info->frame_len,
						(s32)info->rssi * 100,
						GFP_KERNEL);
		अगर (!bss)
			cfg80211_put_bss(wiphy, bss);
	पूर्ण अन्यथा अगर (scan_event == SCAN_EVENT_DONE) अणु
		mutex_lock(&priv->scan_req_lock);

		अगर (priv->scan_req) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = false,
			पूर्ण;

			cfg80211_scan_करोne(priv->scan_req, &info);
			priv->cfg_scanning = false;
			priv->scan_req = शून्य;
		पूर्ण
		mutex_unlock(&priv->scan_req_lock);
	पूर्ण अन्यथा अगर (scan_event == SCAN_EVENT_ABORTED) अणु
		mutex_lock(&priv->scan_req_lock);

		अगर (priv->scan_req) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = false,
			पूर्ण;

			cfg80211_scan_करोne(priv->scan_req, &info);
			priv->cfg_scanning = false;
			priv->scan_req = शून्य;
		पूर्ण
		mutex_unlock(&priv->scan_req_lock);
	पूर्ण
पूर्ण

अटल व्योम cfg_connect_result(क्रमागत conn_event conn_disconn_evt, u8 mac_status,
			       व्योम *priv_data)
अणु
	काष्ठा wilc_priv *priv = priv_data;
	काष्ठा net_device *dev = priv->dev;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc *wl = vअगर->wilc;
	काष्ठा host_अगर_drv *wfi_drv = priv->hअगर_drv;
	काष्ठा wilc_conn_info *conn_info = &wfi_drv->conn_info;
	काष्ठा wiphy *wiphy = dev->ieee80211_ptr->wiphy;

	vअगर->connecting = false;

	अगर (conn_disconn_evt == CONN_DISCONN_EVENT_CONN_RESP) अणु
		u16 connect_status = conn_info->status;

		अगर (mac_status == WILC_MAC_STATUS_DISCONNECTED &&
		    connect_status == WLAN_STATUS_SUCCESS) अणु
			connect_status = WLAN_STATUS_UNSPECIFIED_FAILURE;
			wilc_wlan_set_bssid(priv->dev, शून्य, WILC_STATION_MODE);

			अगर (vअगर->अगरtype != WILC_CLIENT_MODE)
				wl->sta_ch = WILC_INVALID_CHANNEL;

			netdev_err(dev, "Unspecified failure\n");
		पूर्ण

		अगर (connect_status == WLAN_STATUS_SUCCESS)
			स_नकल(priv->associated_bss, conn_info->bssid,
			       ETH_ALEN);

		cfg80211_ref_bss(wiphy, vअगर->bss);
		cfg80211_connect_bss(dev, conn_info->bssid, vअगर->bss,
				     conn_info->req_ies,
				     conn_info->req_ies_len,
				     conn_info->resp_ies,
				     conn_info->resp_ies_len,
				     connect_status, GFP_KERNEL,
				     NL80211_TIMEOUT_UNSPECIFIED);

		vअगर->bss = शून्य;
	पूर्ण अन्यथा अगर (conn_disconn_evt == CONN_DISCONN_EVENT_DISCONN_NOTIF) अणु
		u16 reason = 0;

		eth_zero_addr(priv->associated_bss);
		wilc_wlan_set_bssid(priv->dev, शून्य, WILC_STATION_MODE);

		अगर (vअगर->अगरtype != WILC_CLIENT_MODE) अणु
			wl->sta_ch = WILC_INVALID_CHANNEL;
		पूर्ण अन्यथा अणु
			अगर (wfi_drv->अगरc_up)
				reason = 3;
			अन्यथा
				reason = 1;
		पूर्ण

		cfg80211_disconnected(dev, reason, शून्य, 0, false, GFP_KERNEL);
	पूर्ण
पूर्ण

काष्ठा wilc_vअगर *wilc_get_wl_to_vअगर(काष्ठा wilc *wl)
अणु
	काष्ठा wilc_vअगर *vअगर;

	vअगर = list_first_or_null_rcu(&wl->vअगर_list, typeof(*vअगर), list);
	अगर (!vअगर)
		वापस ERR_PTR(-EINVAL);

	वापस vअगर;
पूर्ण

अटल पूर्णांक set_channel(काष्ठा wiphy *wiphy,
		       काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा wilc *wl = wiphy_priv(wiphy);
	काष्ठा wilc_vअगर *vअगर;
	u32 channelnum;
	पूर्णांक result;
	पूर्णांक srcu_idx;

	srcu_idx = srcu_पढ़ो_lock(&wl->srcu);
	vअगर = wilc_get_wl_to_vअगर(wl);
	अगर (IS_ERR(vअगर)) अणु
		srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
		वापस PTR_ERR(vअगर);
	पूर्ण

	channelnum = ieee80211_frequency_to_channel(chandef->chan->center_freq);

	wl->op_ch = channelnum;
	result = wilc_set_mac_chnl_num(vअगर, channelnum);
	अगर (result)
		netdev_err(vअगर->ndev, "Error in setting channel\n");

	srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
	वापस result;
पूर्ण

अटल पूर्णांक scan(काष्ठा wiphy *wiphy, काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(request->wdev->netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	u32 i;
	पूर्णांक ret = 0;
	u8 scan_ch_list[WILC_MAX_NUM_SCANNED_CH];
	u8 scan_type;

	अगर (request->n_channels > WILC_MAX_NUM_SCANNED_CH) अणु
		netdev_err(vअगर->ndev, "Requested scanned channels over\n");
		वापस -EINVAL;
	पूर्ण

	priv->scan_req = request;
	priv->cfg_scanning = true;
	क्रम (i = 0; i < request->n_channels; i++) अणु
		u16 freq = request->channels[i]->center_freq;

		scan_ch_list[i] = ieee80211_frequency_to_channel(freq);
	पूर्ण

	अगर (request->n_ssids)
		scan_type = WILC_FW_ACTIVE_SCAN;
	अन्यथा
		scan_type = WILC_FW_PASSIVE_SCAN;

	ret = wilc_scan(vअगर, WILC_FW_USER_SCAN, scan_type, scan_ch_list,
			request->n_channels, cfg_scan_result, (व्योम *)priv,
			request);

	अगर (ret) अणु
		priv->scan_req = शून्य;
		priv->cfg_scanning = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक connect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		   काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा host_अगर_drv *wfi_drv = priv->hअगर_drv;
	पूर्णांक ret;
	u32 i;
	u8 security = WILC_FW_SEC_NO;
	क्रमागत authtype auth_type = WILC_FW_AUTH_ANY;
	u32 cipher_group;
	काष्ठा cfg80211_bss *bss;
	व्योम *join_params;
	u8 ch;

	vअगर->connecting = true;

	स_रखो(priv->wep_key, 0, माप(priv->wep_key));
	स_रखो(priv->wep_key_len, 0, माप(priv->wep_key_len));

	cipher_group = sme->crypto.cipher_group;
	अगर (cipher_group != 0) अणु
		अगर (cipher_group == WLAN_CIPHER_SUITE_WEP40) अणु
			security = WILC_FW_SEC_WEP;

			priv->wep_key_len[sme->key_idx] = sme->key_len;
			स_नकल(priv->wep_key[sme->key_idx], sme->key,
			       sme->key_len);

			wilc_set_wep_शेष_keyid(vअगर, sme->key_idx);
			wilc_add_wep_key_bss_sta(vअगर, sme->key, sme->key_len,
						 sme->key_idx);
		पूर्ण अन्यथा अगर (cipher_group == WLAN_CIPHER_SUITE_WEP104) अणु
			security = WILC_FW_SEC_WEP_EXTENDED;

			priv->wep_key_len[sme->key_idx] = sme->key_len;
			स_नकल(priv->wep_key[sme->key_idx], sme->key,
			       sme->key_len);

			wilc_set_wep_शेष_keyid(vअगर, sme->key_idx);
			wilc_add_wep_key_bss_sta(vअगर, sme->key, sme->key_len,
						 sme->key_idx);
		पूर्ण अन्यथा अगर (sme->crypto.wpa_versions & NL80211_WPA_VERSION_2) अणु
			अगर (cipher_group == WLAN_CIPHER_SUITE_TKIP)
				security = WILC_FW_SEC_WPA2_TKIP;
			अन्यथा
				security = WILC_FW_SEC_WPA2_AES;
		पूर्ण अन्यथा अगर (sme->crypto.wpa_versions & NL80211_WPA_VERSION_1) अणु
			अगर (cipher_group == WLAN_CIPHER_SUITE_TKIP)
				security = WILC_FW_SEC_WPA_TKIP;
			अन्यथा
				security = WILC_FW_SEC_WPA_AES;
		पूर्ण अन्यथा अणु
			ret = -ENOTSUPP;
			netdev_err(dev, "%s: Unsupported cipher\n",
				   __func__);
			जाओ out_error;
		पूर्ण
	पूर्ण

	अगर ((sme->crypto.wpa_versions & NL80211_WPA_VERSION_1) ||
	    (sme->crypto.wpa_versions & NL80211_WPA_VERSION_2)) अणु
		क्रम (i = 0; i < sme->crypto.n_ciphers_pairwise; i++) अणु
			u32 ciphers_pairwise = sme->crypto.ciphers_pairwise[i];

			अगर (ciphers_pairwise == WLAN_CIPHER_SUITE_TKIP)
				security |= WILC_FW_TKIP;
			अन्यथा
				security |= WILC_FW_AES;
		पूर्ण
	पूर्ण

	चयन (sme->auth_type) अणु
	हाल NL80211_AUTHTYPE_OPEN_SYSTEM:
		auth_type = WILC_FW_AUTH_OPEN_SYSTEM;
		अवरोध;

	हाल NL80211_AUTHTYPE_SHARED_KEY:
		auth_type = WILC_FW_AUTH_SHARED_KEY;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (sme->crypto.n_akm_suites) अणु
		अगर (sme->crypto.akm_suites[0] == WLAN_AKM_SUITE_8021X)
			auth_type = WILC_FW_AUTH_IEEE8021;
	पूर्ण

	अगर (wfi_drv->usr_scan_req.scan_result) अणु
		netdev_err(vअगर->ndev, "%s: Scan in progress\n", __func__);
		ret = -EBUSY;
		जाओ out_error;
	पूर्ण

	bss = cfg80211_get_bss(wiphy, sme->channel, sme->bssid, sme->ssid,
			       sme->ssid_len, IEEE80211_BSS_TYPE_ANY,
			       IEEE80211_PRIVACY(sme->privacy));
	अगर (!bss) अणु
		ret = -EINVAL;
		जाओ out_error;
	पूर्ण

	अगर (ether_addr_equal_unaligned(vअगर->bssid, bss->bssid)) अणु
		ret = -EALREADY;
		जाओ out_put_bss;
	पूर्ण

	join_params = wilc_parse_join_bss_param(bss, &sme->crypto);
	अगर (!join_params) अणु
		netdev_err(dev, "%s: failed to construct join param\n",
			   __func__);
		ret = -EINVAL;
		जाओ out_put_bss;
	पूर्ण

	ch = ieee80211_frequency_to_channel(bss->channel->center_freq);
	vअगर->wilc->op_ch = ch;
	अगर (vअगर->अगरtype != WILC_CLIENT_MODE)
		vअगर->wilc->sta_ch = ch;

	wilc_wlan_set_bssid(dev, bss->bssid, WILC_STATION_MODE);

	wfi_drv->conn_info.security = security;
	wfi_drv->conn_info.auth_type = auth_type;
	wfi_drv->conn_info.ch = ch;
	wfi_drv->conn_info.conn_result = cfg_connect_result;
	wfi_drv->conn_info.arg = priv;
	wfi_drv->conn_info.param = join_params;

	ret = wilc_set_join_req(vअगर, bss->bssid, sme->ie, sme->ie_len);
	अगर (ret) अणु
		netdev_err(dev, "wilc_set_join_req(): Error\n");
		ret = -ENOENT;
		अगर (vअगर->अगरtype != WILC_CLIENT_MODE)
			vअगर->wilc->sta_ch = WILC_INVALID_CHANNEL;
		wilc_wlan_set_bssid(dev, शून्य, WILC_STATION_MODE);
		wfi_drv->conn_info.conn_result = शून्य;
		kमुक्त(join_params);
		जाओ out_put_bss;
	पूर्ण
	kमुक्त(join_params);
	vअगर->bss = bss;
	cfg80211_put_bss(wiphy, bss);
	वापस 0;

out_put_bss:
	cfg80211_put_bss(wiphy, bss);

out_error:
	vअगर->connecting = false;
	वापस ret;
पूर्ण

अटल पूर्णांक disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		      u16 reason_code)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा wilc *wilc = vअगर->wilc;
	पूर्णांक ret;

	vअगर->connecting = false;

	अगर (!wilc)
		वापस -EIO;

	अगर (wilc->बंद) अणु
		/* alपढ़ोy disconnected करोne */
		cfg80211_disconnected(dev, 0, शून्य, 0, true, GFP_KERNEL);
		वापस 0;
	पूर्ण

	अगर (vअगर->अगरtype != WILC_CLIENT_MODE)
		wilc->sta_ch = WILC_INVALID_CHANNEL;
	wilc_wlan_set_bssid(priv->dev, शून्य, WILC_STATION_MODE);

	priv->hअगर_drv->p2p_समयout = 0;

	ret = wilc_disconnect(vअगर);
	अगर (ret != 0) अणु
		netdev_err(priv->dev, "Error in disconnecting\n");
		ret = -EINVAL;
	पूर्ण

	vअगर->bss = शून्य;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम wilc_wfi_cfg_copy_wep_info(काष्ठा wilc_priv *priv,
					      u8 key_index,
					      काष्ठा key_params *params)
अणु
	priv->wep_key_len[key_index] = params->key_len;
	स_नकल(priv->wep_key[key_index], params->key, params->key_len);
पूर्ण

अटल पूर्णांक wilc_wfi_cfg_allocate_wpa_entry(काष्ठा wilc_priv *priv, u8 idx)
अणु
	अगर (!priv->wilc_gtk[idx]) अणु
		priv->wilc_gtk[idx] = kzalloc(माप(*priv->wilc_gtk[idx]),
					      GFP_KERNEL);
		अगर (!priv->wilc_gtk[idx])
			वापस -ENOMEM;
	पूर्ण

	अगर (!priv->wilc_ptk[idx]) अणु
		priv->wilc_ptk[idx] = kzalloc(माप(*priv->wilc_ptk[idx]),
					      GFP_KERNEL);
		अगर (!priv->wilc_ptk[idx])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_wfi_cfg_copy_wpa_info(काष्ठा wilc_wfi_key *key_info,
				      काष्ठा key_params *params)
अणु
	kमुक्त(key_info->key);

	key_info->key = kmemdup(params->key, params->key_len, GFP_KERNEL);
	अगर (!key_info->key)
		वापस -ENOMEM;

	kमुक्त(key_info->seq);

	अगर (params->seq_len > 0) अणु
		key_info->seq = kmemdup(params->seq, params->seq_len,
					GFP_KERNEL);
		अगर (!key_info->seq)
			वापस -ENOMEM;
	पूर्ण

	key_info->cipher = params->cipher;
	key_info->key_len = params->key_len;
	key_info->seq_len = params->seq_len;

	वापस 0;
पूर्ण

अटल पूर्णांक add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index,
		   bool pairwise, स्थिर u8 *mac_addr, काष्ठा key_params *params)

अणु
	पूर्णांक ret = 0, keylen = params->key_len;
	स्थिर u8 *rx_mic = शून्य;
	स्थिर u8 *tx_mic = शून्य;
	u8 mode = WILC_FW_SEC_NO;
	u8 op_mode;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	चयन (params->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		अगर (priv->wdev.अगरtype == NL80211_IFTYPE_AP) अणु
			wilc_wfi_cfg_copy_wep_info(priv, key_index, params);

			अगर (params->cipher == WLAN_CIPHER_SUITE_WEP40)
				mode = WILC_FW_SEC_WEP;
			अन्यथा
				mode = WILC_FW_SEC_WEP_EXTENDED;

			ret = wilc_add_wep_key_bss_ap(vअगर, params->key,
						      params->key_len,
						      key_index, mode,
						      WILC_FW_AUTH_OPEN_SYSTEM);
			अवरोध;
		पूर्ण
		अगर (स_भेद(params->key, priv->wep_key[key_index],
			   params->key_len)) अणु
			wilc_wfi_cfg_copy_wep_info(priv, key_index, params);

			ret = wilc_add_wep_key_bss_sta(vअगर, params->key,
						       params->key_len,
						       key_index);
		पूर्ण

		अवरोध;

	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_CCMP:
		अगर (priv->wdev.अगरtype == NL80211_IFTYPE_AP ||
		    priv->wdev.अगरtype == NL80211_IFTYPE_P2P_GO) अणु
			काष्ठा wilc_wfi_key *key;

			ret = wilc_wfi_cfg_allocate_wpa_entry(priv, key_index);
			अगर (ret)
				वापस -ENOMEM;

			अगर (params->key_len > 16 &&
			    params->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
				tx_mic = params->key + 24;
				rx_mic = params->key + 16;
				keylen = params->key_len - 16;
			पूर्ण

			अगर (!pairwise) अणु
				अगर (params->cipher == WLAN_CIPHER_SUITE_TKIP)
					mode = WILC_FW_SEC_WPA_TKIP;
				अन्यथा
					mode = WILC_FW_SEC_WPA2_AES;

				priv->wilc_groupkey = mode;

				key = priv->wilc_gtk[key_index];
			पूर्ण अन्यथा अणु
				अगर (params->cipher == WLAN_CIPHER_SUITE_TKIP)
					mode = WILC_FW_SEC_WPA_TKIP;
				अन्यथा
					mode = priv->wilc_groupkey | WILC_FW_AES;

				key = priv->wilc_ptk[key_index];
			पूर्ण
			ret = wilc_wfi_cfg_copy_wpa_info(key, params);
			अगर (ret)
				वापस -ENOMEM;

			op_mode = WILC_AP_MODE;
		पूर्ण अन्यथा अणु
			अगर (params->key_len > 16 &&
			    params->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
				rx_mic = params->key + 24;
				tx_mic = params->key + 16;
				keylen = params->key_len - 16;
			पूर्ण

			op_mode = WILC_STATION_MODE;
		पूर्ण

		अगर (!pairwise)
			ret = wilc_add_rx_gtk(vअगर, params->key, keylen,
					      key_index, params->seq_len,
					      params->seq, rx_mic, tx_mic,
					      op_mode, mode);
		अन्यथा
			ret = wilc_add_ptk(vअगर, params->key, keylen, mac_addr,
					   rx_mic, tx_mic, op_mode, mode,
					   key_index);

		अवरोध;

	शेष:
		netdev_err(netdev, "%s: Unsupported cipher\n", __func__);
		ret = -ENOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		   u8 key_index,
		   bool pairwise,
		   स्थिर u8 *mac_addr)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	अगर (priv->wilc_gtk[key_index]) अणु
		kमुक्त(priv->wilc_gtk[key_index]->key);
		priv->wilc_gtk[key_index]->key = शून्य;
		kमुक्त(priv->wilc_gtk[key_index]->seq);
		priv->wilc_gtk[key_index]->seq = शून्य;

		kमुक्त(priv->wilc_gtk[key_index]);
		priv->wilc_gtk[key_index] = शून्य;
	पूर्ण

	अगर (priv->wilc_ptk[key_index]) अणु
		kमुक्त(priv->wilc_ptk[key_index]->key);
		priv->wilc_ptk[key_index]->key = शून्य;
		kमुक्त(priv->wilc_ptk[key_index]->seq);
		priv->wilc_ptk[key_index]->seq = शून्य;
		kमुक्त(priv->wilc_ptk[key_index]);
		priv->wilc_ptk[key_index] = शून्य;
	पूर्ण

	अगर (key_index <= 3 && priv->wep_key_len[key_index]) अणु
		स_रखो(priv->wep_key[key_index], 0,
		       priv->wep_key_len[key_index]);
		priv->wep_key_len[key_index] = 0;
		wilc_हटाओ_wep_key(vअगर, key_index);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev, u8 key_index,
		   bool pairwise, स्थिर u8 *mac_addr, व्योम *cookie,
		   व्योम (*callback)(व्योम *cookie, काष्ठा key_params *))
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा  key_params key_params;

	अगर (!pairwise) अणु
		key_params.key = priv->wilc_gtk[key_index]->key;
		key_params.cipher = priv->wilc_gtk[key_index]->cipher;
		key_params.key_len = priv->wilc_gtk[key_index]->key_len;
		key_params.seq = priv->wilc_gtk[key_index]->seq;
		key_params.seq_len = priv->wilc_gtk[key_index]->seq_len;
	पूर्ण अन्यथा अणु
		key_params.key = priv->wilc_ptk[key_index]->key;
		key_params.cipher = priv->wilc_ptk[key_index]->cipher;
		key_params.key_len = priv->wilc_ptk[key_index]->key_len;
		key_params.seq = priv->wilc_ptk[key_index]->seq;
		key_params.seq_len = priv->wilc_ptk[key_index]->seq_len;
	पूर्ण

	callback(cookie, &key_params);

	वापस 0;
पूर्ण

अटल पूर्णांक set_शेष_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			   u8 key_index, bool unicast, bool multicast)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(netdev);

	wilc_set_wep_शेष_keyid(vअगर, key_index);

	वापस 0;
पूर्ण

अटल पूर्णांक get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		       स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	u32 i = 0;
	u32 associatedsta = ~0;
	u32 inactive_समय = 0;

	अगर (vअगर->अगरtype == WILC_AP_MODE || vअगर->अगरtype == WILC_GO_MODE) अणु
		क्रम (i = 0; i < NUM_STA_ASSOCIATED; i++) अणु
			अगर (!(स_भेद(mac,
				     priv->assoc_stainfo.sta_associated_bss[i],
				     ETH_ALEN))) अणु
				associatedsta = i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (associatedsta == ~0) अणु
			netdev_err(dev, "sta required is not associated\n");
			वापस -ENOENT;
		पूर्ण

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_INACTIVE_TIME);

		wilc_get_inactive_समय(vअगर, mac, &inactive_समय);
		sinfo->inactive_समय = 1000 * inactive_समय;
	पूर्ण अन्यथा अगर (vअगर->अगरtype == WILC_STATION_MODE) अणु
		काष्ठा rf_info stats;

		wilc_get_statistics(vअगर, &stats);

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL) |
				 BIT_ULL(NL80211_STA_INFO_RX_PACKETS) |
				 BIT_ULL(NL80211_STA_INFO_TX_PACKETS) |
				 BIT_ULL(NL80211_STA_INFO_TX_FAILED) |
				 BIT_ULL(NL80211_STA_INFO_TX_BITRATE);

		sinfo->संकेत = stats.rssi;
		sinfo->rx_packets = stats.rx_cnt;
		sinfo->tx_packets = stats.tx_cnt + stats.tx_fail_cnt;
		sinfo->tx_failed = stats.tx_fail_cnt;
		sinfo->txrate.legacy = stats.link_speed * 10;

		अगर (stats.link_speed > TCP_ACK_FILTER_LINK_SPEED_THRESH &&
		    stats.link_speed != DEFAULT_LINK_SPEED)
			wilc_enable_tcp_ack_filter(vअगर, true);
		अन्यथा अगर (stats.link_speed != DEFAULT_LINK_SPEED)
			wilc_enable_tcp_ack_filter(vअगर, false);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक change_bss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		      काष्ठा bss_parameters *params)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा cfg_param_attr cfg_param_val;
	काष्ठा wilc *wl = wiphy_priv(wiphy);
	काष्ठा wilc_vअगर *vअगर;
	काष्ठा wilc_priv *priv;
	पूर्णांक srcu_idx;

	srcu_idx = srcu_पढ़ो_lock(&wl->srcu);
	vअगर = wilc_get_wl_to_vअगर(wl);
	अगर (IS_ERR(vअगर))
		जाओ out;

	priv = &vअगर->priv;
	cfg_param_val.flag = 0;

	अगर (changed & WIPHY_PARAM_RETRY_SHORT) अणु
		netdev_dbg(vअगर->ndev,
			   "Setting WIPHY_PARAM_RETRY_SHORT %d\n",
			   wiphy->retry_लघु);
		cfg_param_val.flag  |= WILC_CFG_PARAM_RETRY_SHORT;
		cfg_param_val.लघु_retry_limit = wiphy->retry_लघु;
	पूर्ण
	अगर (changed & WIPHY_PARAM_RETRY_LONG) अणु
		netdev_dbg(vअगर->ndev,
			   "Setting WIPHY_PARAM_RETRY_LONG %d\n",
			   wiphy->retry_दीर्घ);
		cfg_param_val.flag |= WILC_CFG_PARAM_RETRY_LONG;
		cfg_param_val.दीर्घ_retry_limit = wiphy->retry_दीर्घ;
	पूर्ण
	अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD) अणु
		अगर (wiphy->frag_threshold > 255 &&
		    wiphy->frag_threshold < 7937) अणु
			netdev_dbg(vअगर->ndev,
				   "Setting WIPHY_PARAM_FRAG_THRESHOLD %d\n",
				   wiphy->frag_threshold);
			cfg_param_val.flag |= WILC_CFG_PARAM_FRAG_THRESHOLD;
			cfg_param_val.frag_threshold = wiphy->frag_threshold;
		पूर्ण अन्यथा अणु
			netdev_err(vअगर->ndev,
				   "Fragmentation threshold out of range\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (changed & WIPHY_PARAM_RTS_THRESHOLD) अणु
		अगर (wiphy->rts_threshold > 255) अणु
			netdev_dbg(vअगर->ndev,
				   "Setting WIPHY_PARAM_RTS_THRESHOLD %d\n",
				   wiphy->rts_threshold);
			cfg_param_val.flag |= WILC_CFG_PARAM_RTS_THRESHOLD;
			cfg_param_val.rts_threshold = wiphy->rts_threshold;
		पूर्ण अन्यथा अणु
			netdev_err(vअगर->ndev, "RTS threshold out of range\n");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = wilc_hअगर_set_cfg(vअगर, &cfg_param_val);
	अगर (ret)
		netdev_err(priv->dev, "Error in setting WIPHY PARAMS\n");

out:
	srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
	वापस ret;
पूर्ण

अटल पूर्णांक set_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		     काष्ठा cfg80211_pmksa *pmksa)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	u32 i;
	पूर्णांक ret = 0;
	u8 flag = 0;

	क्रम (i = 0; i < priv->pmkid_list.numpmkid; i++)	अणु
		अगर (!स_भेद(pmksa->bssid, priv->pmkid_list.pmkidlist[i].bssid,
			    ETH_ALEN)) अणु
			flag = PMKID_FOUND;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i < WILC_MAX_NUM_PMKIDS) अणु
		स_नकल(priv->pmkid_list.pmkidlist[i].bssid, pmksa->bssid,
		       ETH_ALEN);
		स_नकल(priv->pmkid_list.pmkidlist[i].pmkid, pmksa->pmkid,
		       WLAN_PMKID_LEN);
		अगर (!(flag == PMKID_FOUND))
			priv->pmkid_list.numpmkid++;
	पूर्ण अन्यथा अणु
		netdev_err(netdev, "Invalid PMKID index\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!ret)
		ret = wilc_set_pmkid_info(vअगर, &priv->pmkid_list);

	वापस ret;
पूर्ण

अटल पूर्णांक del_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
		     काष्ठा cfg80211_pmksa *pmksa)
अणु
	u32 i;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	क्रम (i = 0; i < priv->pmkid_list.numpmkid; i++)	अणु
		अगर (!स_भेद(pmksa->bssid, priv->pmkid_list.pmkidlist[i].bssid,
			    ETH_ALEN)) अणु
			स_रखो(&priv->pmkid_list.pmkidlist[i], 0,
			       माप(काष्ठा wilc_pmkid));
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == priv->pmkid_list.numpmkid)
		वापस -EINVAL;

	क्रम (; i < (priv->pmkid_list.numpmkid - 1); i++) अणु
		स_नकल(priv->pmkid_list.pmkidlist[i].bssid,
		       priv->pmkid_list.pmkidlist[i + 1].bssid,
		       ETH_ALEN);
		स_नकल(priv->pmkid_list.pmkidlist[i].pmkid,
		       priv->pmkid_list.pmkidlist[i + 1].pmkid,
		       WLAN_PMKID_LEN);
	पूर्ण
	priv->pmkid_list.numpmkid--;

	वापस 0;
पूर्ण

अटल पूर्णांक flush_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(netdev);

	स_रखो(&vअगर->priv.pmkid_list, 0, माप(काष्ठा wilc_pmkid_attr));

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम wilc_wfi_cfg_parse_ch_attr(u8 *buf, u32 len, u8 sta_ch)
अणु
	काष्ठा wilc_attr_entry *e;
	काष्ठा wilc_attr_ch_list *ch_list;
	काष्ठा wilc_attr_oper_ch *op_ch;
	u32 index = 0;
	u8 ch_list_idx = 0;
	u8 op_ch_idx = 0;

	अगर (sta_ch == WILC_INVALID_CHANNEL)
		वापस;

	जबतक (index + माप(*e) <= len) अणु
		e = (काष्ठा wilc_attr_entry *)&buf[index];
		अगर (e->attr_type == IEEE80211_P2P_ATTR_CHANNEL_LIST)
			ch_list_idx = index;
		अन्यथा अगर (e->attr_type == IEEE80211_P2P_ATTR_OPER_CHANNEL)
			op_ch_idx = index;
		अगर (ch_list_idx && op_ch_idx)
			अवरोध;
		index += le16_to_cpu(e->attr_len) + माप(*e);
	पूर्ण

	अगर (ch_list_idx) अणु
		u16 attr_size;
		काष्ठा wilc_ch_list_elem *e;
		पूर्णांक i;

		ch_list = (काष्ठा wilc_attr_ch_list *)&buf[ch_list_idx];
		attr_size = le16_to_cpu(ch_list->attr_len);
		क्रम (i = 0; i < attr_size;) अणु
			e = (काष्ठा wilc_ch_list_elem *)(ch_list->elem + i);
			अगर (e->op_class == WILC_WLAN_OPERATING_CLASS_2_4GHZ) अणु
				स_रखो(e->ch_list, sta_ch, e->no_of_channels);
				अवरोध;
			पूर्ण
			i += e->no_of_channels;
		पूर्ण
	पूर्ण

	अगर (op_ch_idx) अणु
		op_ch = (काष्ठा wilc_attr_oper_ch *)&buf[op_ch_idx];
		op_ch->op_class = WILC_WLAN_OPERATING_CLASS_2_4GHZ;
		op_ch->op_channel = sta_ch;
	पूर्ण
पूर्ण

व्योम wilc_wfi_p2p_rx(काष्ठा wilc_vअगर *vअगर, u8 *buff, u32 size)
अणु
	काष्ठा wilc *wl = vअगर->wilc;
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा host_अगर_drv *wfi_drv = priv->hअगर_drv;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा wilc_venकरोr_specअगरic_ie *p;
	काष्ठा wilc_p2p_pub_act_frame *d;
	पूर्णांक ie_offset = दुरत्व(काष्ठा ieee80211_mgmt, u) + माप(*d);
	स्थिर u8 *venकरोr_ie;
	u32 header, pkt_offset;
	s32 freq;

	header = get_unaligned_le32(buff - HOST_HDR_OFFSET);
	pkt_offset = FIELD_GET(WILC_PKT_HDR_OFFSET_FIELD, header);

	अगर (pkt_offset & IS_MANAGMEMENT_CALLBACK) अणु
		bool ack = false;
		काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)buff;

		अगर (ieee80211_is_probe_resp(hdr->frame_control) ||
		    pkt_offset & IS_MGMT_STATUS_SUCCES)
			ack = true;

		cfg80211_mgmt_tx_status(&priv->wdev, priv->tx_cookie, buff,
					size, ack, GFP_KERNEL);
		वापस;
	पूर्ण

	freq = ieee80211_channel_to_frequency(wl->op_ch, NL80211_BAND_2GHZ);

	mgmt = (काष्ठा ieee80211_mgmt *)buff;
	अगर (!ieee80211_is_action(mgmt->frame_control))
		जाओ out_rx_mgmt;

	अगर (priv->cfg_scanning &&
	    समय_after_eq(jअगरfies, (अचिन्हित दीर्घ)wfi_drv->p2p_समयout)) अणु
		netdev_dbg(vअगर->ndev, "Receiving action wrong ch\n");
		वापस;
	पूर्ण

	अगर (!ieee80211_is_खुला_action((काष्ठा ieee80211_hdr *)buff, size))
		जाओ out_rx_mgmt;

	d = (काष्ठा wilc_p2p_pub_act_frame *)(&mgmt->u.action);
	अगर (d->oui_subtype != GO_NEG_REQ && d->oui_subtype != GO_NEG_RSP &&
	    d->oui_subtype != P2P_INV_REQ && d->oui_subtype != P2P_INV_RSP)
		जाओ out_rx_mgmt;

	venकरोr_ie = cfg80211_find_venकरोr_ie(WLAN_OUI_WFA, WLAN_OUI_TYPE_WFA_P2P,
					    buff + ie_offset, size - ie_offset);
	अगर (!venकरोr_ie)
		जाओ out_rx_mgmt;

	p = (काष्ठा wilc_venकरोr_specअगरic_ie *)venकरोr_ie;
	wilc_wfi_cfg_parse_ch_attr(p->attr, p->tag_len - 4, vअगर->wilc->sta_ch);

out_rx_mgmt:
	cfg80211_rx_mgmt(&priv->wdev, freq, 0, buff, size, 0);
पूर्ण

अटल व्योम wilc_wfi_mgmt_tx_complete(व्योम *priv, पूर्णांक status)
अणु
	काष्ठा wilc_p2p_mgmt_data *pv_data = priv;

	kमुक्त(pv_data->buff);
	kमुक्त(pv_data);
पूर्ण

अटल व्योम wilc_wfi_reमुख्य_on_channel_expired(व्योम *data, u64 cookie)
अणु
	काष्ठा wilc_vअगर *vअगर = data;
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा wilc_wfi_p2p_listen_params *params = &priv->reमुख्य_on_ch_params;

	अगर (cookie != params->listen_cookie)
		वापस;

	priv->p2p_listen_state = false;

	cfg80211_reमुख्य_on_channel_expired(&priv->wdev, params->listen_cookie,
					   params->listen_ch, GFP_KERNEL);
पूर्ण

अटल पूर्णांक reमुख्य_on_channel(काष्ठा wiphy *wiphy,
			     काष्ठा wireless_dev *wdev,
			     काष्ठा ieee80211_channel *chan,
			     अचिन्हित पूर्णांक duration, u64 *cookie)
अणु
	पूर्णांक ret = 0;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(wdev->netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	u64 id;

	अगर (wdev->अगरtype == NL80211_IFTYPE_AP) अणु
		netdev_dbg(vअगर->ndev, "Required while in AP mode\n");
		वापस ret;
	पूर्ण

	id = ++priv->inc_roc_cookie;
	अगर (id == 0)
		id = ++priv->inc_roc_cookie;

	ret = wilc_reमुख्य_on_channel(vअगर, id, duration, chan->hw_value,
				     wilc_wfi_reमुख्य_on_channel_expired,
				     (व्योम *)vअगर);
	अगर (ret)
		वापस ret;

	vअगर->wilc->op_ch = chan->hw_value;

	priv->reमुख्य_on_ch_params.listen_ch = chan;
	priv->reमुख्य_on_ch_params.listen_cookie = id;
	*cookie = id;
	priv->p2p_listen_state = true;
	priv->reमुख्य_on_ch_params.listen_duration = duration;

	cfg80211_पढ़ोy_on_channel(wdev, *cookie, chan, duration, GFP_KERNEL);
	mod_समयr(&vअगर->hअगर_drv->reमुख्य_on_ch_समयr,
		  jअगरfies + msecs_to_jअगरfies(duration + 1000));

	वापस ret;
पूर्ण

अटल पूर्णांक cancel_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
				    काष्ठा wireless_dev *wdev,
				    u64 cookie)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(wdev->netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	अगर (cookie != priv->reमुख्य_on_ch_params.listen_cookie)
		वापस -ENOENT;

	वापस wilc_listen_state_expired(vअगर, cookie);
पूर्ण

अटल पूर्णांक mgmt_tx(काष्ठा wiphy *wiphy,
		   काष्ठा wireless_dev *wdev,
		   काष्ठा cfg80211_mgmt_tx_params *params,
		   u64 *cookie)
अणु
	काष्ठा ieee80211_channel *chan = params->chan;
	अचिन्हित पूर्णांक रुको = params->रुको;
	स्थिर u8 *buf = params->buf;
	माप_प्रकार len = params->len;
	स्थिर काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा wilc_p2p_mgmt_data *mgmt_tx;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(wdev->netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा host_अगर_drv *wfi_drv = priv->hअगर_drv;
	काष्ठा wilc_venकरोr_specअगरic_ie *p;
	काष्ठा wilc_p2p_pub_act_frame *d;
	पूर्णांक ie_offset = दुरत्व(काष्ठा ieee80211_mgmt, u) + माप(*d);
	स्थिर u8 *venकरोr_ie;
	पूर्णांक ret = 0;

	*cookie = pअक्रमom_u32();
	priv->tx_cookie = *cookie;
	mgmt = (स्थिर काष्ठा ieee80211_mgmt *)buf;

	अगर (!ieee80211_is_mgmt(mgmt->frame_control))
		जाओ out;

	mgmt_tx = kदो_स्मृति(माप(*mgmt_tx), GFP_KERNEL);
	अगर (!mgmt_tx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mgmt_tx->buff = kmemdup(buf, len, GFP_KERNEL);
	अगर (!mgmt_tx->buff) अणु
		ret = -ENOMEM;
		kमुक्त(mgmt_tx);
		जाओ out;
	पूर्ण

	mgmt_tx->size = len;

	अगर (ieee80211_is_probe_resp(mgmt->frame_control)) अणु
		wilc_set_mac_chnl_num(vअगर, chan->hw_value);
		vअगर->wilc->op_ch = chan->hw_value;
		जाओ out_txq_add_pkt;
	पूर्ण

	अगर (!ieee80211_is_खुला_action((काष्ठा ieee80211_hdr *)buf, len))
		जाओ out_set_समयout;

	d = (काष्ठा wilc_p2p_pub_act_frame *)(&mgmt->u.action);
	अगर (d->oui_type != WLAN_OUI_TYPE_WFA_P2P ||
	    d->oui_subtype != GO_NEG_CONF) अणु
		wilc_set_mac_chnl_num(vअगर, chan->hw_value);
		vअगर->wilc->op_ch = chan->hw_value;
	पूर्ण

	अगर (d->oui_subtype != P2P_INV_REQ && d->oui_subtype != P2P_INV_RSP)
		जाओ out_set_समयout;

	venकरोr_ie = cfg80211_find_venकरोr_ie(WLAN_OUI_WFA, WLAN_OUI_TYPE_WFA_P2P,
					    mgmt_tx->buff + ie_offset,
					    len - ie_offset);
	अगर (!venकरोr_ie)
		जाओ out_set_समयout;

	p = (काष्ठा wilc_venकरोr_specअगरic_ie *)venकरोr_ie;
	wilc_wfi_cfg_parse_ch_attr(p->attr, p->tag_len - 4, vअगर->wilc->sta_ch);

out_set_समयout:
	wfi_drv->p2p_समयout = (jअगरfies + msecs_to_jअगरfies(रुको));

out_txq_add_pkt:

	wilc_wlan_txq_add_mgmt_pkt(wdev->netdev, mgmt_tx,
				   mgmt_tx->buff, mgmt_tx->size,
				   wilc_wfi_mgmt_tx_complete);

out:

	वापस ret;
पूर्ण

अटल पूर्णांक mgmt_tx_cancel_रुको(काष्ठा wiphy *wiphy,
			       काष्ठा wireless_dev *wdev,
			       u64 cookie)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(wdev->netdev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा host_अगर_drv *wfi_drv = priv->hअगर_drv;

	wfi_drv->p2p_समयout = jअगरfies;

	अगर (!priv->p2p_listen_state) अणु
		काष्ठा wilc_wfi_p2p_listen_params *params;

		params = &priv->reमुख्य_on_ch_params;

		cfg80211_reमुख्य_on_channel_expired(wdev,
						   params->listen_cookie,
						   params->listen_ch,
						   GFP_KERNEL);
	पूर्ण

	वापस 0;
पूर्ण

व्योम wilc_update_mgmt_frame_registrations(काष्ठा wiphy *wiphy,
					  काष्ठा wireless_dev *wdev,
					  काष्ठा mgmt_frame_regs *upd)
अणु
	काष्ठा wilc *wl = wiphy_priv(wiphy);
	काष्ठा wilc_vअगर *vअगर = netdev_priv(wdev->netdev);
	u32 presp_bit = BIT(IEEE80211_STYPE_PROBE_REQ >> 4);
	u32 action_bit = BIT(IEEE80211_STYPE_ACTION >> 4);

	अगर (wl->initialized) अणु
		bool prev = vअगर->mgmt_reg_stypes & presp_bit;
		bool now = upd->पूर्णांकerface_stypes & presp_bit;

		अगर (now != prev)
			wilc_frame_रेजिस्टर(vअगर, IEEE80211_STYPE_PROBE_REQ, now);

		prev = vअगर->mgmt_reg_stypes & action_bit;
		now = upd->पूर्णांकerface_stypes & action_bit;

		अगर (now != prev)
			wilc_frame_रेजिस्टर(vअगर, IEEE80211_STYPE_ACTION, now);
	पूर्ण

	vअगर->mgmt_reg_stypes =
		upd->पूर्णांकerface_stypes & (presp_bit | action_bit);
पूर्ण

अटल पूर्णांक set_cqm_rssi_config(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       s32 rssi_thold, u32 rssi_hyst)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	पूर्णांक ret;

	अगर (idx != 0)
		वापस -ENOENT;

	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);

	ret = wilc_get_rssi(vअगर, &sinfo->संकेत);
	अगर (ret)
		वापस ret;

	स_नकल(mac, vअगर->priv.associated_bss, ETH_ALEN);
	वापस 0;
पूर्ण

अटल पूर्णांक set_घातer_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  bool enabled, पूर्णांक समयout)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	अगर (!priv->hअगर_drv)
		वापस -EIO;

	wilc_set_घातer_mgmt(vअगर, enabled, समयout);

	वापस 0;
पूर्ण

अटल पूर्णांक change_भव_पूर्णांकf(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       क्रमागत nl80211_अगरtype type,
			       काष्ठा vअगर_params *params)
अणु
	काष्ठा wilc *wl = wiphy_priv(wiphy);
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	चयन (type) अणु
	हाल NL80211_IFTYPE_STATION:
		vअगर->connecting = false;
		dev->ieee80211_ptr->अगरtype = type;
		priv->wdev.अगरtype = type;
		vअगर->monitor_flag = 0;
		अगर (vअगर->अगरtype == WILC_AP_MODE || vअगर->अगरtype == WILC_GO_MODE)
			wilc_wfi_deinit_mon_पूर्णांकerface(wl, true);
		vअगर->अगरtype = WILC_STATION_MODE;

		अगर (wl->initialized)
			wilc_set_operation_mode(vअगर, wilc_get_vअगर_idx(vअगर),
						WILC_STATION_MODE, vअगर->idx);

		स_रखो(priv->assoc_stainfo.sta_associated_bss, 0,
		       WILC_MAX_NUM_STA * ETH_ALEN);
		अवरोध;

	हाल NL80211_IFTYPE_P2P_CLIENT:
		vअगर->connecting = false;
		dev->ieee80211_ptr->अगरtype = type;
		priv->wdev.अगरtype = type;
		vअगर->monitor_flag = 0;
		vअगर->अगरtype = WILC_CLIENT_MODE;

		अगर (wl->initialized)
			wilc_set_operation_mode(vअगर, wilc_get_vअगर_idx(vअगर),
						WILC_STATION_MODE, vअगर->idx);
		अवरोध;

	हाल NL80211_IFTYPE_AP:
		dev->ieee80211_ptr->अगरtype = type;
		priv->wdev.अगरtype = type;
		vअगर->अगरtype = WILC_AP_MODE;

		अगर (wl->initialized)
			wilc_set_operation_mode(vअगर, wilc_get_vअगर_idx(vअगर),
						WILC_AP_MODE, vअगर->idx);
		अवरोध;

	हाल NL80211_IFTYPE_P2P_GO:
		dev->ieee80211_ptr->अगरtype = type;
		priv->wdev.अगरtype = type;
		vअगर->अगरtype = WILC_GO_MODE;

		अगर (wl->initialized)
			wilc_set_operation_mode(vअगर, wilc_get_vअगर_idx(vअगर),
						WILC_AP_MODE, vअगर->idx);
		अवरोध;

	शेष:
		netdev_err(dev, "Unknown interface type= %d\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक start_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		    काष्ठा cfg80211_ap_settings *settings)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	पूर्णांक ret;

	ret = set_channel(wiphy, &settings->chandef);
	अगर (ret != 0)
		netdev_err(dev, "Error in setting channel\n");

	wilc_wlan_set_bssid(dev, dev->dev_addr, WILC_AP_MODE);

	वापस wilc_add_beacon(vअगर, settings->beacon_पूर्णांकerval,
				   settings->dtim_period, &settings->beacon);
पूर्ण

अटल पूर्णांक change_beacon(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			 काष्ठा cfg80211_beacon_data *beacon)
अणु
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);

	वापस wilc_add_beacon(vअगर, 0, 0, beacon);
पूर्ण

अटल पूर्णांक stop_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);

	wilc_wlan_set_bssid(dev, शून्य, WILC_AP_MODE);

	ret = wilc_del_beacon(vअगर);

	अगर (ret)
		netdev_err(dev, "Host delete beacon fail\n");

	वापस ret;
पूर्ण

अटल पूर्णांक add_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		       स्थिर u8 *mac, काष्ठा station_parameters *params)
अणु
	पूर्णांक ret = 0;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	अगर (vअगर->अगरtype == WILC_AP_MODE || vअगर->अगरtype == WILC_GO_MODE) अणु
		स_नकल(priv->assoc_stainfo.sta_associated_bss[params->aid], mac,
		       ETH_ALEN);

		ret = wilc_add_station(vअगर, mac, params);
		अगर (ret)
			netdev_err(dev, "Host add station fail\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक del_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		       काष्ठा station_del_parameters *params)
अणु
	स्थिर u8 *mac = params->mac;
	पूर्णांक ret = 0;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);
	काष्ठा wilc_priv *priv = &vअगर->priv;
	काष्ठा sta_info *info;

	अगर (!(vअगर->अगरtype == WILC_AP_MODE || vअगर->अगरtype == WILC_GO_MODE))
		वापस ret;

	info = &priv->assoc_stainfo;

	अगर (!mac)
		ret = wilc_del_allstation(vअगर, info->sta_associated_bss);

	ret = wilc_del_station(vअगर, mac);
	अगर (ret)
		netdev_err(dev, "Host delete station fail\n");
	वापस ret;
पूर्ण

अटल पूर्णांक change_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  स्थिर u8 *mac, काष्ठा station_parameters *params)
अणु
	पूर्णांक ret = 0;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(dev);

	अगर (vअगर->अगरtype == WILC_AP_MODE || vअगर->अगरtype == WILC_GO_MODE) अणु
		ret = wilc_edit_station(vअगर, mac, params);
		अगर (ret)
			netdev_err(dev, "Host edit station fail\n");
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा wilc_vअगर *wilc_get_vअगर_from_type(काष्ठा wilc *wl, पूर्णांक type)
अणु
	काष्ठा wilc_vअगर *vअगर;

	list_क्रम_each_entry_rcu(vअगर, &wl->vअगर_list, list) अणु
		अगर (vअगर->अगरtype == type)
			वापस vअगर;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा wireless_dev *add_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
					     स्थिर अक्षर *name,
					     अचिन्हित अक्षर name_assign_type,
					     क्रमागत nl80211_अगरtype type,
					     काष्ठा vअगर_params *params)
अणु
	काष्ठा wilc *wl = wiphy_priv(wiphy);
	काष्ठा wilc_vअगर *vअगर;
	काष्ठा wireless_dev *wdev;
	पूर्णांक अगरtype;

	अगर (type == NL80211_IFTYPE_MONITOR) अणु
		काष्ठा net_device *ndev;
		पूर्णांक srcu_idx;

		srcu_idx = srcu_पढ़ो_lock(&wl->srcu);
		vअगर = wilc_get_vअगर_from_type(wl, WILC_AP_MODE);
		अगर (!vअगर) अणु
			vअगर = wilc_get_vअगर_from_type(wl, WILC_GO_MODE);
			अगर (!vअगर) अणु
				srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
				जाओ validate_पूर्णांकerface;
			पूर्ण
		पूर्ण

		अगर (vअगर->monitor_flag) अणु
			srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
			जाओ validate_पूर्णांकerface;
		पूर्ण

		ndev = wilc_wfi_init_mon_पूर्णांकerface(wl, name, vअगर->ndev);
		अगर (ndev) अणु
			vअगर->monitor_flag = 1;
		पूर्ण अन्यथा अणु
			srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		wdev = &vअगर->priv.wdev;
		srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
		वापस wdev;
	पूर्ण

validate_पूर्णांकerface:
	mutex_lock(&wl->vअगर_mutex);
	अगर (wl->vअगर_num == WILC_NUM_CONCURRENT_IFC) अणु
		pr_err("Reached maximum number of interface\n");
		mutex_unlock(&wl->vअगर_mutex);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	mutex_unlock(&wl->vअगर_mutex);

	चयन (type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगरtype = WILC_STATION_MODE;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		अगरtype = WILC_AP_MODE;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	vअगर = wilc_netdev_अगरc_init(wl, name, अगरtype, type, true);
	अगर (IS_ERR(vअगर))
		वापस ERR_CAST(vअगर);

	वापस &vअगर->priv.wdev;
पूर्ण

अटल पूर्णांक del_भव_पूर्णांकf(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा wilc *wl = wiphy_priv(wiphy);
	काष्ठा wilc_vअगर *vअगर;

	अगर (wdev->अगरtype == NL80211_IFTYPE_AP ||
	    wdev->अगरtype == NL80211_IFTYPE_P2P_GO)
		wilc_wfi_deinit_mon_पूर्णांकerface(wl, true);
	vअगर = netdev_priv(wdev->netdev);
	cfg80211_stop_अगरace(wiphy, wdev, GFP_KERNEL);
	cfg80211_unरेजिस्टर_netdevice(vअगर->ndev);
	vअगर->monitor_flag = 0;

	wilc_set_operation_mode(vअगर, 0, 0, 0);
	mutex_lock(&wl->vअगर_mutex);
	list_del_rcu(&vअगर->list);
	wl->vअगर_num--;
	mutex_unlock(&wl->vअगर_mutex);
	synchronize_srcu(&wl->srcu);
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_suspend(काष्ठा wiphy *wiphy, काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा wilc *wl = wiphy_priv(wiphy);

	अगर (!wow && wilc_wlan_get_num_conn_अगरcs(wl))
		wl->suspend_event = true;
	अन्यथा
		wl->suspend_event = false;

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_resume(काष्ठा wiphy *wiphy)
अणु
	वापस 0;
पूर्ण

अटल व्योम wilc_set_wakeup(काष्ठा wiphy *wiphy, bool enabled)
अणु
	काष्ठा wilc *wl = wiphy_priv(wiphy);
	काष्ठा wilc_vअगर *vअगर;
	पूर्णांक srcu_idx;

	srcu_idx = srcu_पढ़ो_lock(&wl->srcu);
	vअगर = wilc_get_wl_to_vअगर(wl);
	अगर (IS_ERR(vअगर)) अणु
		srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
		वापस;
	पूर्ण

	netdev_info(vअगर->ndev, "cfg set wake up = %d\n", enabled);
	srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
पूर्ण

अटल पूर्णांक set_tx_घातer(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm)
अणु
	पूर्णांक ret;
	पूर्णांक srcu_idx;
	s32 tx_घातer = MBM_TO_DBM(mbm);
	काष्ठा wilc *wl = wiphy_priv(wiphy);
	काष्ठा wilc_vअगर *vअगर;

	अगर (!wl->initialized)
		वापस -EIO;

	srcu_idx = srcu_पढ़ो_lock(&wl->srcu);
	vअगर = wilc_get_wl_to_vअगर(wl);
	अगर (IS_ERR(vअगर)) अणु
		srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);
		वापस -EINVAL;
	पूर्ण

	netdev_info(vअगर->ndev, "Setting tx power %d\n", tx_घातer);
	अगर (tx_घातer < 0)
		tx_घातer = 0;
	अन्यथा अगर (tx_घातer > 18)
		tx_घातer = 18;
	ret = wilc_set_tx_घातer(vअगर, tx_घातer);
	अगर (ret)
		netdev_err(vअगर->ndev, "Failed to set tx power\n");
	srcu_पढ़ो_unlock(&wl->srcu, srcu_idx);

	वापस ret;
पूर्ण

अटल पूर्णांक get_tx_घातer(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			पूर्णांक *dbm)
अणु
	पूर्णांक ret;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(wdev->netdev);
	काष्ठा wilc *wl = vअगर->wilc;

	/* If firmware is not started, वापस. */
	अगर (!wl->initialized)
		वापस -EIO;

	ret = wilc_get_tx_घातer(vअगर, (u8 *)dbm);
	अगर (ret)
		netdev_err(vअगर->ndev, "Failed to get tx power\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा cfg80211_ops wilc_cfg80211_ops = अणु
	.set_monitor_channel = set_channel,
	.scan = scan,
	.connect = connect,
	.disconnect = disconnect,
	.add_key = add_key,
	.del_key = del_key,
	.get_key = get_key,
	.set_शेष_key = set_शेष_key,
	.add_भव_पूर्णांकf = add_भव_पूर्णांकf,
	.del_भव_पूर्णांकf = del_भव_पूर्णांकf,
	.change_भव_पूर्णांकf = change_भव_पूर्णांकf,

	.start_ap = start_ap,
	.change_beacon = change_beacon,
	.stop_ap = stop_ap,
	.add_station = add_station,
	.del_station = del_station,
	.change_station = change_station,
	.get_station = get_station,
	.dump_station = dump_station,
	.change_bss = change_bss,
	.set_wiphy_params = set_wiphy_params,

	.set_pmksa = set_pmksa,
	.del_pmksa = del_pmksa,
	.flush_pmksa = flush_pmksa,
	.reमुख्य_on_channel = reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel = cancel_reमुख्य_on_channel,
	.mgmt_tx_cancel_रुको = mgmt_tx_cancel_रुको,
	.mgmt_tx = mgmt_tx,
	.update_mgmt_frame_registrations = wilc_update_mgmt_frame_registrations,
	.set_घातer_mgmt = set_घातer_mgmt,
	.set_cqm_rssi_config = set_cqm_rssi_config,

	.suspend = wilc_suspend,
	.resume = wilc_resume,
	.set_wakeup = wilc_set_wakeup,
	.set_tx_घातer = set_tx_घातer,
	.get_tx_घातer = get_tx_घातer,

पूर्ण;

अटल व्योम wlan_init_locks(काष्ठा wilc *wl)
अणु
	mutex_init(&wl->hअगर_cs);
	mutex_init(&wl->rxq_cs);
	mutex_init(&wl->cfg_cmd_lock);
	mutex_init(&wl->vअगर_mutex);

	spin_lock_init(&wl->txq_spinlock);
	mutex_init(&wl->txq_add_to_head_cs);

	init_completion(&wl->txq_event);
	init_completion(&wl->cfg_event);
	init_completion(&wl->sync_event);
	init_completion(&wl->txq_thपढ़ो_started);
	init_srcu_काष्ठा(&wl->srcu);
पूर्ण

व्योम wlan_deinit_locks(काष्ठा wilc *wilc)
अणु
	mutex_destroy(&wilc->hअगर_cs);
	mutex_destroy(&wilc->rxq_cs);
	mutex_destroy(&wilc->cfg_cmd_lock);
	mutex_destroy(&wilc->txq_add_to_head_cs);
	mutex_destroy(&wilc->vअगर_mutex);
	cleanup_srcu_काष्ठा(&wilc->srcu);
पूर्ण

पूर्णांक wilc_cfg80211_init(काष्ठा wilc **wilc, काष्ठा device *dev, पूर्णांक io_type,
		       स्थिर काष्ठा wilc_hअगर_func *ops)
अणु
	काष्ठा wilc *wl;
	काष्ठा wilc_vअगर *vअगर;
	पूर्णांक ret, i;

	wl = wilc_create_wiphy(dev);
	अगर (!wl)
		वापस -EINVAL;

	wlan_init_locks(wl);

	ret = wilc_wlan_cfg_init(wl);
	अगर (ret)
		जाओ मुक्त_wl;

	*wilc = wl;
	wl->io_type = io_type;
	wl->hअगर_func = ops;
	wl->chip_ps_state = WILC_CHIP_WAKEDUP;

	क्रम (i = 0; i < NQUEUES; i++)
		INIT_LIST_HEAD(&wl->txq[i].txq_head.list);

	INIT_LIST_HEAD(&wl->rxq_head.list);
	INIT_LIST_HEAD(&wl->vअगर_list);

	wl->hअगर_workqueue = create_singlethपढ़ो_workqueue("WILC_wq");
	अगर (!wl->hअगर_workqueue) अणु
		ret = -ENOMEM;
		जाओ मुक्त_cfg;
	पूर्ण
	vअगर = wilc_netdev_अगरc_init(wl, "wlan%d", WILC_STATION_MODE,
				   NL80211_IFTYPE_STATION, false);
	अगर (IS_ERR(vअगर)) अणु
		ret = PTR_ERR(vअगर);
		जाओ मुक्त_hq;
	पूर्ण

	वापस 0;

मुक्त_hq:
	destroy_workqueue(wl->hअगर_workqueue);

मुक्त_cfg:
	wilc_wlan_cfg_deinit(wl);

मुक्त_wl:
	wlan_deinit_locks(wl);
	wiphy_unरेजिस्टर(wl->wiphy);
	wiphy_मुक्त(wl->wiphy);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wilc_cfg80211_init);

काष्ठा wilc *wilc_create_wiphy(काष्ठा device *dev)
अणु
	काष्ठा wiphy *wiphy;
	काष्ठा wilc *wl;
	पूर्णांक ret;

	wiphy = wiphy_new(&wilc_cfg80211_ops, माप(*wl));
	अगर (!wiphy)
		वापस शून्य;

	wl = wiphy_priv(wiphy);

	स_नकल(wl->bitrates, wilc_bitrates, माप(wilc_bitrates));
	स_नकल(wl->channels, wilc_2ghz_channels, माप(wilc_2ghz_channels));
	wl->band.bitrates = wl->bitrates;
	wl->band.n_bitrates = ARRAY_SIZE(wl->bitrates);
	wl->band.channels = wl->channels;
	wl->band.n_channels = ARRAY_SIZE(wilc_2ghz_channels);

	wl->band.ht_cap.ht_supported = 1;
	wl->band.ht_cap.cap |= (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);
	wl->band.ht_cap.mcs.rx_mask[0] = 0xff;
	wl->band.ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_8K;
	wl->band.ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE;

	wiphy->bands[NL80211_BAND_2GHZ] = &wl->band;

	wiphy->max_scan_ssids = WILC_MAX_NUM_PROBED_SSID;
#अगर_घोषित CONFIG_PM
	wiphy->wowlan = &wowlan_support;
#पूर्ण_अगर
	wiphy->max_num_pmkids = WILC_MAX_NUM_PMKIDS;
	wiphy->max_scan_ie_len = 1000;
	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;
	स_नकल(wl->cipher_suites, wilc_cipher_suites,
	       माप(wilc_cipher_suites));
	wiphy->cipher_suites = wl->cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(wilc_cipher_suites);
	wiphy->mgmt_stypes = wilc_wfi_cfg80211_mgmt_types;

	wiphy->max_reमुख्य_on_channel_duration = 500;
	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				BIT(NL80211_IFTYPE_AP) |
				BIT(NL80211_IFTYPE_MONITOR) |
				BIT(NL80211_IFTYPE_P2P_GO) |
				BIT(NL80211_IFTYPE_P2P_CLIENT);
	wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;

	set_wiphy_dev(wiphy, dev);
	wl->wiphy = wiphy;
	ret = wiphy_रेजिस्टर(wiphy);
	अगर (ret) अणु
		wiphy_मुक्त(wiphy);
		वापस शून्य;
	पूर्ण
	वापस wl;
पूर्ण

पूर्णांक wilc_init_host_पूर्णांक(काष्ठा net_device *net)
अणु
	पूर्णांक ret;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(net);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	priv->p2p_listen_state = false;

	mutex_init(&priv->scan_req_lock);
	ret = wilc_init(net, &priv->hअगर_drv);
	अगर (ret)
		netdev_err(net, "Error while initializing hostinterface\n");

	वापस ret;
पूर्ण

व्योम wilc_deinit_host_पूर्णांक(काष्ठा net_device *net)
अणु
	पूर्णांक ret;
	काष्ठा wilc_vअगर *vअगर = netdev_priv(net);
	काष्ठा wilc_priv *priv = &vअगर->priv;

	priv->p2p_listen_state = false;

	flush_workqueue(vअगर->wilc->hअगर_workqueue);
	mutex_destroy(&priv->scan_req_lock);
	ret = wilc_deinit(vअगर);

	अगर (ret)
		netdev_err(net, "Error while deinitializing host interface\n");
पूर्ण

