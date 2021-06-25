<शैली गुरु>
/*
 * NXP Wireless LAN device driver: CFG80211
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "cfg80211.h"
#समावेश "main.h"
#समावेश "11n.h"
#समावेश "wmm.h"

अटल अक्षर *reg_alpha2;
module_param(reg_alpha2, अक्षरp, 0);

अटल स्थिर काष्ठा ieee80211_अगरace_limit mwअगरiex_ap_sta_limits[] = अणु
	अणु
		.max = MWIFIEX_MAX_BSS_NUM,
		.types = BIT(NL80211_IFTYPE_STATION) |
				   BIT(NL80211_IFTYPE_P2P_GO) |
				   BIT(NL80211_IFTYPE_P2P_CLIENT) |
				   BIT(NL80211_IFTYPE_AP),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination
mwअगरiex_अगरace_comb_ap_sta = अणु
	.limits = mwअगरiex_ap_sta_limits,
	.num_dअगरferent_channels = 1,
	.n_limits = ARRAY_SIZE(mwअगरiex_ap_sta_limits),
	.max_पूर्णांकerfaces = MWIFIEX_MAX_BSS_NUM,
	.beacon_पूर्णांक_infra_match = true,
	.radar_detect_widths =	BIT(NL80211_CHAN_WIDTH_20_NOHT) |
				BIT(NL80211_CHAN_WIDTH_20) |
				BIT(NL80211_CHAN_WIDTH_40),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination
mwअगरiex_अगरace_comb_ap_sta_vht = अणु
	.limits = mwअगरiex_ap_sta_limits,
	.num_dअगरferent_channels = 1,
	.n_limits = ARRAY_SIZE(mwअगरiex_ap_sta_limits),
	.max_पूर्णांकerfaces = MWIFIEX_MAX_BSS_NUM,
	.beacon_पूर्णांक_infra_match = true,
	.radar_detect_widths =	BIT(NL80211_CHAN_WIDTH_20_NOHT) |
				BIT(NL80211_CHAN_WIDTH_20) |
				BIT(NL80211_CHAN_WIDTH_40) |
				BIT(NL80211_CHAN_WIDTH_80),
पूर्ण;

अटल स्थिर काष्ठा
ieee80211_अगरace_combination mwअगरiex_अगरace_comb_ap_sta_drcs = अणु
	.limits = mwअगरiex_ap_sta_limits,
	.num_dअगरferent_channels = 2,
	.n_limits = ARRAY_SIZE(mwअगरiex_ap_sta_limits),
	.max_पूर्णांकerfaces = MWIFIEX_MAX_BSS_NUM,
	.beacon_पूर्णांक_infra_match = true,
पूर्ण;

/*
 * This function maps the nl802.11 channel type पूर्णांकo driver channel type.
 *
 * The mapping is as follows -
 *      NL80211_CHAN_NO_HT     -> IEEE80211_HT_PARAM_CHA_SEC_NONE
 *      NL80211_CHAN_HT20      -> IEEE80211_HT_PARAM_CHA_SEC_NONE
 *      NL80211_CHAN_HT40PLUS  -> IEEE80211_HT_PARAM_CHA_SEC_ABOVE
 *      NL80211_CHAN_HT40MINUS -> IEEE80211_HT_PARAM_CHA_SEC_BELOW
 *      Others                 -> IEEE80211_HT_PARAM_CHA_SEC_NONE
 */
u8 mwअगरiex_chan_type_to_sec_chan_offset(क्रमागत nl80211_channel_type chan_type)
अणु
	चयन (chan_type) अणु
	हाल NL80211_CHAN_NO_HT:
	हाल NL80211_CHAN_HT20:
		वापस IEEE80211_HT_PARAM_CHA_SEC_NONE;
	हाल NL80211_CHAN_HT40PLUS:
		वापस IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
	हाल NL80211_CHAN_HT40MINUS:
		वापस IEEE80211_HT_PARAM_CHA_SEC_BELOW;
	शेष:
		वापस IEEE80211_HT_PARAM_CHA_SEC_NONE;
	पूर्ण
पूर्ण

/* This function maps IEEE HT secondary channel type to NL80211 channel type
 */
u8 mwअगरiex_get_chan_type(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_channel_band channel_band;
	पूर्णांक ret;

	ret = mwअगरiex_get_chan_info(priv, &channel_band);

	अगर (!ret) अणु
		चयन (channel_band.band_config.chan_width) अणु
		हाल CHAN_BW_20MHZ:
			अगर (IS_11N_ENABLED(priv))
				वापस NL80211_CHAN_HT20;
			अन्यथा
				वापस NL80211_CHAN_NO_HT;
		हाल CHAN_BW_40MHZ:
			अगर (channel_band.band_config.chan2_offset ==
			    SEC_CHAN_ABOVE)
				वापस NL80211_CHAN_HT40PLUS;
			अन्यथा
				वापस NL80211_CHAN_HT40MINUS;
		शेष:
			वापस NL80211_CHAN_HT20;
		पूर्ण
	पूर्ण

	वापस NL80211_CHAN_HT20;
पूर्ण

/*
 * This function checks whether WEP is set.
 */
अटल पूर्णांक
mwअगरiex_is_alg_wep(u32 cipher)
अणु
	चयन (cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function retrieves the निजी काष्ठाure from kernel wiphy काष्ठाure.
 */
अटल व्योम *mwअगरiex_cfg80211_get_adapter(काष्ठा wiphy *wiphy)
अणु
	वापस (व्योम *) (*(अचिन्हित दीर्घ *) wiphy_priv(wiphy));
पूर्ण

/*
 * CFG802.11 operation handler to delete a network key.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			 u8 key_index, bool pairwise, स्थिर u8 *mac_addr)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(netdev);
	अटल स्थिर u8 bc_mac[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	स्थिर u8 *peer_mac = pairwise ? mac_addr : bc_mac;

	अगर (mwअगरiex_set_encode(priv, शून्य, शून्य, 0, key_index, peer_mac, 1)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "deleting the crypto keys\n");
		वापस -EFAULT;
	पूर्ण

	mwअगरiex_dbg(priv->adapter, INFO, "info: crypto keys deleted\n");
	वापस 0;
पूर्ण

/*
 * This function क्रमms an skb क्रम management frame.
 */
अटल पूर्णांक
mwअगरiex_क्रमm_mgmt_frame(काष्ठा sk_buff *skb, स्थिर u8 *buf, माप_प्रकार len)
अणु
	u8 addr[ETH_ALEN] = अणु0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFFपूर्ण;
	u16 pkt_len;
	u32 tx_control = 0, pkt_type = PKT_TYPE_MGMT;

	pkt_len = len + ETH_ALEN;

	skb_reserve(skb, MWIFIEX_MIN_DATA_HEADER_LEN +
		    MWIFIEX_MGMT_FRAME_HEADER_SIZE + माप(pkt_len));
	स_नकल(skb_push(skb, माप(pkt_len)), &pkt_len, माप(pkt_len));

	स_नकल(skb_push(skb, माप(tx_control)),
	       &tx_control, माप(tx_control));

	स_नकल(skb_push(skb, माप(pkt_type)), &pkt_type, माप(pkt_type));

	/* Add packet data and address4 */
	skb_put_data(skb, buf, माप(काष्ठा ieee80211_hdr_3addr));
	skb_put_data(skb, addr, ETH_ALEN);
	skb_put_data(skb, buf + माप(काष्ठा ieee80211_hdr_3addr),
		     len - माप(काष्ठा ieee80211_hdr_3addr));

	skb->priority = LOW_PRIO_TID;
	__net_बारtamp(skb);

	वापस 0;
पूर्ण

/*
 * CFG802.11 operation handler to transmit a management frame.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_mgmt_tx(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			 काष्ठा cfg80211_mgmt_tx_params *params, u64 *cookie)
अणु
	स्थिर u8 *buf = params->buf;
	माप_प्रकार len = params->len;
	काष्ठा sk_buff *skb;
	u16 pkt_len;
	स्थिर काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा mwअगरiex_txinfo *tx_info;
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(wdev->netdev);

	अगर (!buf || !len) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "invalid buffer and length\n");
		वापस -EFAULT;
	पूर्ण

	mgmt = (स्थिर काष्ठा ieee80211_mgmt *)buf;
	अगर (GET_BSS_ROLE(priv) != MWIFIEX_BSS_ROLE_STA &&
	    ieee80211_is_probe_resp(mgmt->frame_control)) अणु
		/* Since we support offload probe resp, we need to skip probe
		 * resp in AP or GO mode */
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: skip to send probe resp in AP or GO mode\n");
		वापस 0;
	पूर्ण

	pkt_len = len + ETH_ALEN;
	skb = dev_alloc_skb(MWIFIEX_MIN_DATA_HEADER_LEN +
			    MWIFIEX_MGMT_FRAME_HEADER_SIZE +
			    pkt_len + माप(pkt_len));

	अगर (!skb) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "allocate skb failed for management frame\n");
		वापस -ENOMEM;
	पूर्ण

	tx_info = MWIFIEX_SKB_TXCB(skb);
	स_रखो(tx_info, 0, माप(*tx_info));
	tx_info->bss_num = priv->bss_num;
	tx_info->bss_type = priv->bss_type;
	tx_info->pkt_len = pkt_len;

	mwअगरiex_क्रमm_mgmt_frame(skb, buf, len);
	*cookie = pअक्रमom_u32() | 1;

	अगर (ieee80211_is_action(mgmt->frame_control))
		skb = mwअगरiex_clone_skb_क्रम_tx_status(priv,
						      skb,
				MWIFIEX_BUF_FLAG_ACTION_TX_STATUS, cookie);
	अन्यथा
		cfg80211_mgmt_tx_status(wdev, *cookie, buf, len, true,
					GFP_ATOMIC);

	mwअगरiex_queue_tx_pkt(priv, skb);

	mwअगरiex_dbg(priv->adapter, INFO, "info: management frame transmitted\n");
	वापस 0;
पूर्ण

/*
 * CFG802.11 operation handler to रेजिस्टर a mgmt frame.
 */
अटल व्योम
mwअगरiex_cfg80211_update_mgmt_frame_registrations(काष्ठा wiphy *wiphy,
						 काष्ठा wireless_dev *wdev,
						 काष्ठा mgmt_frame_regs *upd)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(wdev->netdev);
	u32 mask = upd->पूर्णांकerface_stypes;

	अगर (mask != priv->mgmt_frame_mask) अणु
		priv->mgmt_frame_mask = mask;
		mwअगरiex_send_cmd(priv, HostCmd_CMD_MGMT_FRAME_REG,
				 HostCmd_ACT_GEN_SET, 0,
				 &priv->mgmt_frame_mask, false);
		mwअगरiex_dbg(priv->adapter, INFO, "info: mgmt frame registered\n");
	पूर्ण
पूर्ण

/*
 * CFG802.11 operation handler to reमुख्य on channel.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
				   काष्ठा wireless_dev *wdev,
				   काष्ठा ieee80211_channel *chan,
				   अचिन्हित पूर्णांक duration, u64 *cookie)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(wdev->netdev);
	पूर्णांक ret;

	अगर (!chan || !cookie) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "Invalid parameter for ROC\n");
		वापस -EINVAL;
	पूर्ण

	अगर (priv->roc_cfg.cookie) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: ongoing ROC, cookie = 0x%llx\n",
			    priv->roc_cfg.cookie);
		वापस -EBUSY;
	पूर्ण

	ret = mwअगरiex_reमुख्य_on_chan_cfg(priv, HostCmd_ACT_GEN_SET, chan,
					 duration);

	अगर (!ret) अणु
		*cookie = pअक्रमom_u32() | 1;
		priv->roc_cfg.cookie = *cookie;
		priv->roc_cfg.chan = *chan;

		cfg80211_पढ़ोy_on_channel(wdev, *cookie, chan,
					  duration, GFP_ATOMIC);

		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: ROC, cookie = 0x%llx\n", *cookie);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * CFG802.11 operation handler to cancel reमुख्य on channel.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_cancel_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
					  काष्ठा wireless_dev *wdev, u64 cookie)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(wdev->netdev);
	पूर्णांक ret;

	अगर (cookie != priv->roc_cfg.cookie)
		वापस -ENOENT;

	ret = mwअगरiex_reमुख्य_on_chan_cfg(priv, HostCmd_ACT_GEN_REMOVE,
					 &priv->roc_cfg.chan, 0);

	अगर (!ret) अणु
		cfg80211_reमुख्य_on_channel_expired(wdev, cookie,
						   &priv->roc_cfg.chan,
						   GFP_ATOMIC);

		स_रखो(&priv->roc_cfg, 0, माप(काष्ठा mwअगरiex_roc_cfg));

		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: cancel ROC, cookie = 0x%llx\n", cookie);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * CFG802.11 operation handler to set Tx घातer.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_set_tx_घातer(काष्ठा wiphy *wiphy,
			      काष्ठा wireless_dev *wdev,
			      क्रमागत nl80211_tx_घातer_setting type,
			      पूर्णांक mbm)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_घातer_cfg घातer_cfg;
	पूर्णांक dbm = MBM_TO_DBM(mbm);

	चयन (type) अणु
	हाल NL80211_TX_POWER_FIXED:
		घातer_cfg.is_घातer_स्वतः = 0;
		घातer_cfg.is_घातer_fixed = 1;
		घातer_cfg.घातer_level = dbm;
		अवरोध;
	हाल NL80211_TX_POWER_LIMITED:
		घातer_cfg.is_घातer_स्वतः = 0;
		घातer_cfg.is_घातer_fixed = 0;
		घातer_cfg.घातer_level = dbm;
		अवरोध;
	हाल NL80211_TX_POWER_AUTOMATIC:
		घातer_cfg.is_घातer_स्वतः = 1;
		अवरोध;
	पूर्ण

	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	वापस mwअगरiex_set_tx_घातer(priv, &घातer_cfg);
पूर्ण

/*
 * CFG802.11 operation handler to get Tx घातer.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_get_tx_घातer(काष्ठा wiphy *wiphy,
			      काष्ठा wireless_dev *wdev,
			      पूर्णांक *dbm)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_get_priv(adapter,
							MWIFIEX_BSS_ROLE_ANY);
	पूर्णांक ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_RF_TX_PWR,
				   HostCmd_ACT_GEN_GET, 0, शून्य, true);

	अगर (ret < 0)
		वापस ret;

	/* tx_घातer_level is set in HostCmd_CMD_RF_TX_PWR command handler */
	*dbm = priv->tx_घातer_level;

	वापस 0;
पूर्ण

/*
 * CFG802.11 operation handler to set Power Save option.
 *
 * The समयout value, अगर provided, is currently ignored.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_set_घातer_mgmt(काष्ठा wiphy *wiphy,
				काष्ठा net_device *dev,
				bool enabled, पूर्णांक समयout)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	u32 ps_mode;

	अगर (समयout)
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: ignore timeout value for IEEE Power Save\n");

	ps_mode = enabled;

	वापस mwअगरiex_drv_set_घातer(priv, &ps_mode);
पूर्ण

/*
 * CFG802.11 operation handler to set the शेष network key.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_set_शेष_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
				 u8 key_index, bool unicast,
				 bool multicast)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(netdev);

	/* Return अगर WEP key not configured */
	अगर (!priv->sec_info.wep_enabled)
		वापस 0;

	अगर (priv->bss_type == MWIFIEX_BSS_TYPE_UAP) अणु
		priv->wep_key_curr_index = key_index;
	पूर्ण अन्यथा अगर (mwअगरiex_set_encode(priv, शून्य, शून्य, 0, key_index,
				      शून्य, 0)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "set default Tx key index\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * CFG802.11 operation handler to add a network key.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			 u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
			 काष्ठा key_params *params)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(netdev);
	काष्ठा mwअगरiex_wep_key *wep_key;
	अटल स्थिर u8 bc_mac[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	स्थिर u8 *peer_mac = pairwise ? mac_addr : bc_mac;

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP &&
	    (params->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	     params->cipher == WLAN_CIPHER_SUITE_WEP104)) अणु
		अगर (params->key && params->key_len) अणु
			wep_key = &priv->wep_key[key_index];
			स_रखो(wep_key, 0, माप(काष्ठा mwअगरiex_wep_key));
			स_नकल(wep_key->key_material, params->key,
			       params->key_len);
			wep_key->key_index = key_index;
			wep_key->key_length = params->key_len;
			priv->sec_info.wep_enabled = 1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (mwअगरiex_set_encode(priv, params, params->key, params->key_len,
			       key_index, peer_mac, 0)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "crypto keys added\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * CFG802.11 operation handler to set शेष mgmt key.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_set_शेष_mgmt_key(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *netdev,
				      u8 key_index)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(netdev);
	काष्ठा mwअगरiex_ds_encrypt_key encrypt_key;

	wiphy_dbg(wiphy, "set default mgmt key, key index=%d\n", key_index);

	स_रखो(&encrypt_key, 0, माप(काष्ठा mwअगरiex_ds_encrypt_key));
	encrypt_key.key_len = WLAN_KEY_LEN_CCMP;
	encrypt_key.key_index = key_index;
	encrypt_key.is_igtk_def_key = true;
	eth_broadcast_addr(encrypt_key.mac_addr);

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_KEY_MATERIAL,
				HostCmd_ACT_GEN_SET, true, &encrypt_key, true);
पूर्ण

/*
 * This function sends करोमुख्य inक्रमmation to the firmware.
 *
 * The following inक्रमmation are passed to the firmware -
 *      - Country codes
 *      - Sub bands (first channel, number of channels, maximum Tx घातer)
 */
पूर्णांक mwअगरiex_send_करोमुख्य_info_cmd_fw(काष्ठा wiphy *wiphy)
अणु
	u8 no_of_triplet = 0;
	काष्ठा ieee80211_country_ie_triplet *t;
	u8 no_of_parsed_chan = 0;
	u8 first_chan = 0, next_chan = 0, max_pwr = 0;
	u8 i, flag = 0;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_802_11d_करोमुख्य_reg *करोमुख्य_info = &adapter->करोमुख्य_reg;

	/* Set country code */
	करोमुख्य_info->country_code[0] = adapter->country_code[0];
	करोमुख्य_info->country_code[1] = adapter->country_code[1];
	करोमुख्य_info->country_code[2] = ' ';

	band = mwअगरiex_band_to_radio_type(adapter->config_bands);
	अगर (!wiphy->bands[band]) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "11D: setting domain info in FW\n");
		वापस -1;
	पूर्ण

	sband = wiphy->bands[band];

	क्रम (i = 0; i < sband->n_channels ; i++) अणु
		ch = &sband->channels[i];
		अगर (ch->flags & IEEE80211_CHAN_DISABLED)
			जारी;

		अगर (!flag) अणु
			flag = 1;
			first_chan = (u32) ch->hw_value;
			next_chan = first_chan;
			max_pwr = ch->max_घातer;
			no_of_parsed_chan = 1;
			जारी;
		पूर्ण

		अगर (ch->hw_value == next_chan + 1 &&
		    ch->max_घातer == max_pwr) अणु
			next_chan++;
			no_of_parsed_chan++;
		पूर्ण अन्यथा अणु
			t = &करोमुख्य_info->triplet[no_of_triplet];
			t->chans.first_channel = first_chan;
			t->chans.num_channels = no_of_parsed_chan;
			t->chans.max_घातer = max_pwr;
			no_of_triplet++;
			first_chan = (u32) ch->hw_value;
			next_chan = first_chan;
			max_pwr = ch->max_घातer;
			no_of_parsed_chan = 1;
		पूर्ण
	पूर्ण

	अगर (flag) अणु
		t = &करोमुख्य_info->triplet[no_of_triplet];
		t->chans.first_channel = first_chan;
		t->chans.num_channels = no_of_parsed_chan;
		t->chans.max_घातer = max_pwr;
		no_of_triplet++;
	पूर्ण

	करोमुख्य_info->no_of_triplet = no_of_triplet;

	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11D_DOMAIN_INFO,
			     HostCmd_ACT_GEN_SET, 0, शून्य, false)) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "11D: setting domain info in FW\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_reg_apply_radar_flags(काष्ठा wiphy *wiphy)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *chan;
	अचिन्हित पूर्णांक i;

	अगर (!wiphy->bands[NL80211_BAND_5GHZ])
		वापस;
	sband = wiphy->bands[NL80211_BAND_5GHZ];

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		chan = &sband->channels[i];
		अगर ((!(chan->flags & IEEE80211_CHAN_DISABLED)) &&
		    (chan->flags & IEEE80211_CHAN_RADAR))
			chan->flags |= IEEE80211_CHAN_NO_IR;
	पूर्ण
पूर्ण

/*
 * CFG802.11 regulatory करोमुख्य callback function.
 *
 * This function is called when the regulatory करोमुख्य is changed due to the
 * following reasons -
 *      - Set by driver
 *      - Set by प्रणाली core
 *      - Set by user
 *      - Set bt Country IE
 */
अटल व्योम mwअगरiex_reg_notअगरier(काष्ठा wiphy *wiphy,
				 काष्ठा regulatory_request *request)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_get_priv(adapter,
							MWIFIEX_BSS_ROLE_ANY);
	mwअगरiex_dbg(adapter, INFO,
		    "info: cfg80211 regulatory domain callback for %c%c\n",
		    request->alpha2[0], request->alpha2[1]);
	mwअगरiex_reg_apply_radar_flags(wiphy);

	चयन (request->initiator) अणु
	हाल NL80211_REGDOM_SET_BY_DRIVER:
	हाल NL80211_REGDOM_SET_BY_CORE:
	हाल NL80211_REGDOM_SET_BY_USER:
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR,
			    "unknown regdom initiator: %d\n",
			    request->initiator);
		वापस;
	पूर्ण

	/* Don't send world or same regकरोm info to firmware */
	अगर (म_भेदन(request->alpha2, "00", 2) &&
	    म_भेदन(request->alpha2, adapter->country_code,
		    माप(request->alpha2))) अणु
		स_नकल(adapter->country_code, request->alpha2,
		       माप(request->alpha2));
		mwअगरiex_send_करोमुख्य_info_cmd_fw(wiphy);
		mwअगरiex_dnld_txpwr_table(priv);
	पूर्ण
पूर्ण

/*
 * This function sets the fragmentation threshold.
 *
 * The fragmentation threshold value must lie between MWIFIEX_FRAG_MIN_VALUE
 * and MWIFIEX_FRAG_MAX_VALUE.
 */
अटल पूर्णांक
mwअगरiex_set_frag(काष्ठा mwअगरiex_निजी *priv, u32 frag_thr)
अणु
	अगर (frag_thr < MWIFIEX_FRAG_MIN_VALUE ||
	    frag_thr > MWIFIEX_FRAG_MAX_VALUE)
		frag_thr = MWIFIEX_FRAG_MAX_VALUE;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
				HostCmd_ACT_GEN_SET, FRAG_THRESH_I,
				&frag_thr, true);
पूर्ण

/*
 * This function sets the RTS threshold.

 * The rts value must lie between MWIFIEX_RTS_MIN_VALUE
 * and MWIFIEX_RTS_MAX_VALUE.
 */
अटल पूर्णांक
mwअगरiex_set_rts(काष्ठा mwअगरiex_निजी *priv, u32 rts_thr)
अणु
	अगर (rts_thr < MWIFIEX_RTS_MIN_VALUE || rts_thr > MWIFIEX_RTS_MAX_VALUE)
		rts_thr = MWIFIEX_RTS_MAX_VALUE;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
				HostCmd_ACT_GEN_SET, RTS_THRESH_I,
				&rts_thr, true);
पूर्ण

/*
 * CFG802.11 operation handler to set wiphy parameters.
 *
 * This function can be used to set the RTS threshold and the
 * Fragmentation threshold of the driver.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_uap_bss_param *bss_cfg;
	पूर्णांक ret;

	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	चयन (priv->bss_role) अणु
	हाल MWIFIEX_BSS_ROLE_UAP:
		अगर (priv->bss_started) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cannot change wiphy params when bss started");
			वापस -EINVAL;
		पूर्ण

		bss_cfg = kzalloc(माप(*bss_cfg), GFP_KERNEL);
		अगर (!bss_cfg)
			वापस -ENOMEM;

		mwअगरiex_set_sys_config_invalid_data(bss_cfg);

		अगर (changed & WIPHY_PARAM_RTS_THRESHOLD)
			bss_cfg->rts_threshold = wiphy->rts_threshold;
		अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD)
			bss_cfg->frag_threshold = wiphy->frag_threshold;
		अगर (changed & WIPHY_PARAM_RETRY_LONG)
			bss_cfg->retry_limit = wiphy->retry_दीर्घ;

		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_UAP_SYS_CONFIG,
				       HostCmd_ACT_GEN_SET,
				       UAP_BSS_PARAMS_I, bss_cfg,
				       false);

		kमुक्त(bss_cfg);
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Failed to set wiphy phy params\n");
			वापस ret;
		पूर्ण
		अवरोध;

	हाल MWIFIEX_BSS_ROLE_STA:
		अगर (priv->media_connected) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cannot change wiphy params when connected");
			वापस -EINVAL;
		पूर्ण
		अगर (changed & WIPHY_PARAM_RTS_THRESHOLD) अणु
			ret = mwअगरiex_set_rts(priv,
					      wiphy->rts_threshold);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD) अणु
			ret = mwअगरiex_set_frag(priv,
					       wiphy->frag_threshold);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_deinit_p2p(काष्ठा mwअगरiex_निजी *priv)
अणु
	u16 mode = P2P_MODE_DISABLE;

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_P2P_MODE_CFG,
			     HostCmd_ACT_GEN_SET, 0, &mode, true))
		वापस -1;

	वापस 0;
पूर्ण

/*
 * This function initializes the functionalities क्रम P2P client.
 * The P2P client initialization sequence is:
 * disable -> device -> client
 */
अटल पूर्णांक
mwअगरiex_cfg80211_init_p2p_client(काष्ठा mwअगरiex_निजी *priv)
अणु
	u16 mode;

	अगर (mwअगरiex_cfg80211_deinit_p2p(priv))
		वापस -1;

	mode = P2P_MODE_DEVICE;
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_P2P_MODE_CFG,
			     HostCmd_ACT_GEN_SET, 0, &mode, true))
		वापस -1;

	mode = P2P_MODE_CLIENT;
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_P2P_MODE_CFG,
			     HostCmd_ACT_GEN_SET, 0, &mode, true))
		वापस -1;

	वापस 0;
पूर्ण

/*
 * This function initializes the functionalities क्रम P2P GO.
 * The P2P GO initialization sequence is:
 * disable -> device -> GO
 */
अटल पूर्णांक
mwअगरiex_cfg80211_init_p2p_go(काष्ठा mwअगरiex_निजी *priv)
अणु
	u16 mode;

	अगर (mwअगरiex_cfg80211_deinit_p2p(priv))
		वापस -1;

	mode = P2P_MODE_DEVICE;
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_P2P_MODE_CFG,
			     HostCmd_ACT_GEN_SET, 0, &mode, true))
		वापस -1;

	mode = P2P_MODE_GO;
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_P2P_MODE_CFG,
			     HostCmd_ACT_GEN_SET, 0, &mode, true))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_deinit_priv_params(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	अचिन्हित दीर्घ flags;

	priv->mgmt_frame_mask = 0;
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_MGMT_FRAME_REG,
			     HostCmd_ACT_GEN_SET, 0,
			     &priv->mgmt_frame_mask, false)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "could not unregister mgmt frame rx\n");
		वापस -1;
	पूर्ण

	mwअगरiex_deauthenticate(priv, शून्य);

	spin_lock_irqsave(&adapter->मुख्य_proc_lock, flags);
	adapter->मुख्य_locked = true;
	अगर (adapter->mwअगरiex_processing) अणु
		spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);
		flush_workqueue(adapter->workqueue);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);
	पूर्ण

	spin_lock_bh(&adapter->rx_proc_lock);
	adapter->rx_locked = true;
	अगर (adapter->rx_processing) अणु
		spin_unlock_bh(&adapter->rx_proc_lock);
		flush_workqueue(adapter->rx_workqueue);
	पूर्ण अन्यथा अणु
	spin_unlock_bh(&adapter->rx_proc_lock);
	पूर्ण

	mwअगरiex_मुक्त_priv(priv);
	priv->wdev.अगरtype = NL80211_IFTYPE_UNSPECIFIED;
	priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->sec_info.authentication_mode = NL80211_AUTHTYPE_OPEN_SYSTEM;

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_init_new_priv_params(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा net_device *dev,
			     क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	अचिन्हित दीर्घ flags;

	mwअगरiex_init_priv(priv);

	priv->bss_mode = type;
	priv->wdev.अगरtype = type;

	mwअगरiex_init_priv_params(priv, priv->netdev);
	priv->bss_started = 0;

	चयन (type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		priv->bss_role =  MWIFIEX_BSS_ROLE_STA;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		priv->bss_role =  MWIFIEX_BSS_ROLE_STA;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		priv->bss_role =  MWIFIEX_BSS_ROLE_UAP;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		priv->bss_role = MWIFIEX_BSS_ROLE_UAP;
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: changing to %d not supported\n",
			    dev->name, type);
		वापस -EOPNOTSUPP;
	पूर्ण

	spin_lock_irqsave(&adapter->मुख्य_proc_lock, flags);
	adapter->मुख्य_locked = false;
	spin_unlock_irqrestore(&adapter->मुख्य_proc_lock, flags);

	spin_lock_bh(&adapter->rx_proc_lock);
	adapter->rx_locked = false;
	spin_unlock_bh(&adapter->rx_proc_lock);

	mwअगरiex_set_mac_address(priv, dev, false, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_change_vअगर_to_p2p(काष्ठा net_device *dev,
			  क्रमागत nl80211_अगरtype curr_अगरtype,
			  क्रमागत nl80211_अगरtype type,
			  काष्ठा vअगर_params *params)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_adapter *adapter;

	priv = mwअगरiex_netdev_get_priv(dev);

	अगर (!priv)
		वापस -1;

	adapter = priv->adapter;

	अगर (adapter->curr_अगरace_comb.p2p_पूर्णांकf ==
	    adapter->अगरace_limit.p2p_पूर्णांकf) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cannot create multiple P2P ifaces\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "%s: changing role to p2p\n", dev->name);

	अगर (mwअगरiex_deinit_priv_params(priv))
		वापस -1;
	अगर (mwअगरiex_init_new_priv_params(priv, dev, type))
		वापस -1;

	चयन (type) अणु
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (mwअगरiex_cfg80211_init_p2p_client(priv))
			वापस -EFAULT;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (mwअगरiex_cfg80211_init_p2p_go(priv))
			वापस -EFAULT;
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: changing to %d not supported\n",
			    dev->name, type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_SET_BSS_MODE,
			     HostCmd_ACT_GEN_SET, 0, शून्य, true))
		वापस -1;

	अगर (mwअगरiex_sta_init_cmd(priv, false, false))
		वापस -1;

	चयन (curr_अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		adapter->curr_अगरace_comb.sta_पूर्णांकf--;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		adapter->curr_अगरace_comb.uap_पूर्णांकf--;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	adapter->curr_अगरace_comb.p2p_पूर्णांकf++;
	dev->ieee80211_ptr->अगरtype = type;

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_change_vअगर_to_sta_adhoc(काष्ठा net_device *dev,
				क्रमागत nl80211_अगरtype curr_अगरtype,
				क्रमागत nl80211_अगरtype type,
				काष्ठा vअगर_params *params)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_adapter *adapter;

	priv = mwअगरiex_netdev_get_priv(dev);

	अगर (!priv)
		वापस -1;

	adapter = priv->adapter;

	अगर ((curr_अगरtype != NL80211_IFTYPE_P2P_CLIENT &&
	     curr_अगरtype != NL80211_IFTYPE_P2P_GO) &&
	    (adapter->curr_अगरace_comb.sta_पूर्णांकf ==
	     adapter->अगरace_limit.sta_पूर्णांकf)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cannot create multiple station/adhoc ifaces\n");
		वापस -1;
	पूर्ण

	अगर (type == NL80211_IFTYPE_STATION)
		mwअगरiex_dbg(adapter, INFO,
			    "%s: changing role to station\n", dev->name);
	अन्यथा
		mwअगरiex_dbg(adapter, INFO,
			    "%s: changing role to adhoc\n", dev->name);

	अगर (mwअगरiex_deinit_priv_params(priv))
		वापस -1;
	अगर (mwअगरiex_init_new_priv_params(priv, dev, type))
		वापस -1;
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_SET_BSS_MODE,
			     HostCmd_ACT_GEN_SET, 0, शून्य, true))
		वापस -1;
	अगर (mwअगरiex_sta_init_cmd(priv, false, false))
		वापस -1;

	चयन (curr_अगरtype) अणु
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
		adapter->curr_अगरace_comb.p2p_पूर्णांकf--;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		adapter->curr_अगरace_comb.uap_पूर्णांकf--;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	adapter->curr_अगरace_comb.sta_पूर्णांकf++;
	dev->ieee80211_ptr->अगरtype = type;
	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_change_vअगर_to_ap(काष्ठा net_device *dev,
			 क्रमागत nl80211_अगरtype curr_अगरtype,
			 क्रमागत nl80211_अगरtype type,
			 काष्ठा vअगर_params *params)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_adapter *adapter;

	priv = mwअगरiex_netdev_get_priv(dev);

	अगर (!priv)
		वापस -1;

	adapter = priv->adapter;

	अगर (adapter->curr_अगरace_comb.uap_पूर्णांकf ==
	    adapter->अगरace_limit.uap_पूर्णांकf) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cannot create multiple AP ifaces\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "%s: changing role to AP\n", dev->name);

	अगर (mwअगरiex_deinit_priv_params(priv))
		वापस -1;
	अगर (mwअगरiex_init_new_priv_params(priv, dev, type))
		वापस -1;
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_SET_BSS_MODE,
			     HostCmd_ACT_GEN_SET, 0, शून्य, true))
		वापस -1;
	अगर (mwअगरiex_sta_init_cmd(priv, false, false))
		वापस -1;

	चयन (curr_अगरtype) अणु
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
		adapter->curr_अगरace_comb.p2p_पूर्णांकf--;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		adapter->curr_अगरace_comb.sta_पूर्णांकf--;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	adapter->curr_अगरace_comb.uap_पूर्णांकf++;
	dev->ieee80211_ptr->अगरtype = type;
	वापस 0;
पूर्ण
/*
 * CFG802.11 operation handler to change पूर्णांकerface type.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_change_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
				     काष्ठा net_device *dev,
				     क्रमागत nl80211_अगरtype type,
				     काष्ठा vअगर_params *params)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	क्रमागत nl80211_अगरtype curr_अगरtype = dev->ieee80211_ptr->अगरtype;

	अगर (priv->scan_request) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "change virtual interface: scan in process\n");
		वापस -EBUSY;
	पूर्ण

	चयन (curr_अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
		चयन (type) अणु
		हाल NL80211_IFTYPE_STATION:
			priv->bss_mode = type;
			priv->sec_info.authentication_mode =
						   NL80211_AUTHTYPE_OPEN_SYSTEM;
			dev->ieee80211_ptr->अगरtype = type;
			mwअगरiex_deauthenticate(priv, शून्य);
			वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_SET_BSS_MODE,
						HostCmd_ACT_GEN_SET, 0, शून्य,
						true);
		हाल NL80211_IFTYPE_P2P_CLIENT:
		हाल NL80211_IFTYPE_P2P_GO:
			वापस mwअगरiex_change_vअगर_to_p2p(dev, curr_अगरtype,
							 type, params);
		हाल NL80211_IFTYPE_AP:
			वापस mwअगरiex_change_vअगर_to_ap(dev, curr_अगरtype, type,
							params);
		हाल NL80211_IFTYPE_UNSPECIFIED:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "%s: kept type as IBSS\n", dev->name);
			fallthrough;
		हाल NL80211_IFTYPE_ADHOC:	/* This shouldn't happen */
			वापस 0;
		शेष:
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "%s: changing to %d not supported\n",
				    dev->name, type);
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		चयन (type) अणु
		हाल NL80211_IFTYPE_ADHOC:
			priv->bss_mode = type;
			priv->sec_info.authentication_mode =
						   NL80211_AUTHTYPE_OPEN_SYSTEM;
			dev->ieee80211_ptr->अगरtype = type;
			mwअगरiex_deauthenticate(priv, शून्य);
			वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_SET_BSS_MODE,
						HostCmd_ACT_GEN_SET, 0, शून्य,
						true);
		हाल NL80211_IFTYPE_P2P_CLIENT:
		हाल NL80211_IFTYPE_P2P_GO:
			वापस mwअगरiex_change_vअगर_to_p2p(dev, curr_अगरtype,
							 type, params);
		हाल NL80211_IFTYPE_AP:
			वापस mwअगरiex_change_vअगर_to_ap(dev, curr_अगरtype, type,
							params);
		हाल NL80211_IFTYPE_UNSPECIFIED:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "%s: kept type as STA\n", dev->name);
			fallthrough;
		हाल NL80211_IFTYPE_STATION:	/* This shouldn't happen */
			वापस 0;
		शेष:
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "%s: changing to %d not supported\n",
				    dev->name, type);
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		चयन (type) अणु
		हाल NL80211_IFTYPE_ADHOC:
			वापस mwअगरiex_change_vअगर_to_sta_adhoc(dev, curr_अगरtype,
							       type, params);
			अवरोध;
		हाल NL80211_IFTYPE_P2P_CLIENT:
		हाल NL80211_IFTYPE_P2P_GO:
			वापस mwअगरiex_change_vअगर_to_p2p(dev, curr_अगरtype,
							 type, params);
		हाल NL80211_IFTYPE_UNSPECIFIED:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "%s: kept type as AP\n", dev->name);
			fallthrough;
		हाल NL80211_IFTYPE_AP:		/* This shouldn't happen */
			वापस 0;
		शेष:
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "%s: changing to %d not supported\n",
				    dev->name, type);
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
		चयन (type) अणु
		हाल NL80211_IFTYPE_STATION:
			अगर (mwअगरiex_cfg80211_deinit_p2p(priv))
				वापस -EFAULT;
			priv->adapter->curr_अगरace_comb.p2p_पूर्णांकf--;
			priv->adapter->curr_अगरace_comb.sta_पूर्णांकf++;
			dev->ieee80211_ptr->अगरtype = type;
			अगर (mwअगरiex_deinit_priv_params(priv))
				वापस -1;
			अगर (mwअगरiex_init_new_priv_params(priv, dev, type))
				वापस -1;
			अगर (mwअगरiex_sta_init_cmd(priv, false, false))
				वापस -1;
			अवरोध;
		हाल NL80211_IFTYPE_ADHOC:
			अगर (mwअगरiex_cfg80211_deinit_p2p(priv))
				वापस -EFAULT;
			वापस mwअगरiex_change_vअगर_to_sta_adhoc(dev, curr_अगरtype,
							       type, params);
			अवरोध;
		हाल NL80211_IFTYPE_AP:
			अगर (mwअगरiex_cfg80211_deinit_p2p(priv))
				वापस -EFAULT;
			वापस mwअगरiex_change_vअगर_to_ap(dev, curr_अगरtype, type,
							params);
		हाल NL80211_IFTYPE_UNSPECIFIED:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "%s: kept type as P2P\n", dev->name);
			fallthrough;
		हाल NL80211_IFTYPE_P2P_CLIENT:
		हाल NL80211_IFTYPE_P2P_GO:
			वापस 0;
		शेष:
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "%s: changing to %d not supported\n",
				    dev->name, type);
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: unknown iftype: %d\n",
			    dev->name, dev->ieee80211_ptr->अगरtype);
		वापस -EOPNOTSUPP;
	पूर्ण


	वापस 0;
पूर्ण

अटल व्योम
mwअगरiex_parse_htinfo(काष्ठा mwअगरiex_निजी *priv, u8 rateinfo, u8 htinfo,
		     काष्ठा rate_info *rate)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	अगर (adapter->is_hw_11ac_capable) अणु
		/* bit[1-0]: 00=LG 01=HT 10=VHT */
		अगर (htinfo & BIT(0)) अणु
			/* HT */
			rate->mcs = rateinfo;
			rate->flags |= RATE_INFO_FLAGS_MCS;
		पूर्ण
		अगर (htinfo & BIT(1)) अणु
			/* VHT */
			rate->mcs = rateinfo & 0x0F;
			rate->flags |= RATE_INFO_FLAGS_VHT_MCS;
		पूर्ण

		अगर (htinfo & (BIT(1) | BIT(0))) अणु
			/* HT or VHT */
			चयन (htinfo & (BIT(3) | BIT(2))) अणु
			हाल 0:
				rate->bw = RATE_INFO_BW_20;
				अवरोध;
			हाल (BIT(2)):
				rate->bw = RATE_INFO_BW_40;
				अवरोध;
			हाल (BIT(3)):
				rate->bw = RATE_INFO_BW_80;
				अवरोध;
			हाल (BIT(3) | BIT(2)):
				rate->bw = RATE_INFO_BW_160;
				अवरोध;
			पूर्ण

			अगर (htinfo & BIT(4))
				rate->flags |= RATE_INFO_FLAGS_SHORT_GI;

			अगर ((rateinfo >> 4) == 1)
				rate->nss = 2;
			अन्यथा
				rate->nss = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Bit 0 in htinfo indicates that current rate is 11n. Valid
		 * MCS index values क्रम us are 0 to 15.
		 */
		अगर ((htinfo & BIT(0)) && (rateinfo < 16)) अणु
			rate->mcs = rateinfo;
			rate->flags |= RATE_INFO_FLAGS_MCS;
			rate->bw = RATE_INFO_BW_20;
			अगर (htinfo & BIT(1))
				rate->bw = RATE_INFO_BW_40;
			अगर (htinfo & BIT(2))
				rate->flags |= RATE_INFO_FLAGS_SHORT_GI;
		पूर्ण
	पूर्ण

	/* Decode legacy rates क्रम non-HT. */
	अगर (!(htinfo & (BIT(0) | BIT(1)))) अणु
		/* Bitrates in multiples of 100kb/s. */
		अटल स्थिर पूर्णांक legacy_rates[] = अणु
			[0] = 10,
			[1] = 20,
			[2] = 55,
			[3] = 110,
			[4] = 60, /* MWIFIEX_RATE_INDEX_OFDM0 */
			[5] = 60,
			[6] = 90,
			[7] = 120,
			[8] = 180,
			[9] = 240,
			[10] = 360,
			[11] = 480,
			[12] = 540,
		पूर्ण;
		अगर (rateinfo < ARRAY_SIZE(legacy_rates))
			rate->legacy = legacy_rates[rateinfo];
	पूर्ण
पूर्ण

/*
 * This function dumps the station inक्रमmation on a buffer.
 *
 * The following inक्रमmation are shown -
 *      - Total bytes transmitted
 *      - Total bytes received
 *      - Total packets transmitted
 *      - Total packets received
 *      - Signal quality level
 *      - Transmission rate
 */
अटल पूर्णांक
mwअगरiex_dump_station_info(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा mwअगरiex_sta_node *node,
			  काष्ठा station_info *sinfo)
अणु
	u32 rate;

	sinfo->filled = BIT_ULL(NL80211_STA_INFO_RX_BYTES) | BIT_ULL(NL80211_STA_INFO_TX_BYTES) |
			BIT_ULL(NL80211_STA_INFO_RX_PACKETS) | BIT_ULL(NL80211_STA_INFO_TX_PACKETS) |
			BIT_ULL(NL80211_STA_INFO_TX_BITRATE) |
			BIT_ULL(NL80211_STA_INFO_SIGNAL) | BIT_ULL(NL80211_STA_INFO_SIGNAL_AVG);

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
		अगर (!node)
			वापस -ENOENT;

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_INACTIVE_TIME) |
				BIT_ULL(NL80211_STA_INFO_TX_FAILED);
		sinfo->inactive_समय =
			jअगरfies_to_msecs(jअगरfies - node->stats.last_rx);

		sinfo->संकेत = node->stats.rssi;
		sinfo->संकेत_avg = node->stats.rssi;
		sinfo->rx_bytes = node->stats.rx_bytes;
		sinfo->tx_bytes = node->stats.tx_bytes;
		sinfo->rx_packets = node->stats.rx_packets;
		sinfo->tx_packets = node->stats.tx_packets;
		sinfo->tx_failed = node->stats.tx_failed;

		mwअगरiex_parse_htinfo(priv, priv->tx_rate,
				     node->stats.last_tx_htinfo,
				     &sinfo->txrate);
		sinfo->txrate.legacy = node->stats.last_tx_rate * 5;

		वापस 0;
	पूर्ण

	/* Get संकेत inक्रमmation from the firmware */
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_RSSI_INFO,
			     HostCmd_ACT_GEN_GET, 0, शून्य, true)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "failed to get signal information\n");
		वापस -EFAULT;
	पूर्ण

	अगर (mwअगरiex_drv_get_data_rate(priv, &rate)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "getting data rate error\n");
		वापस -EFAULT;
	पूर्ण

	/* Get DTIM period inक्रमmation from firmware */
	mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
			 HostCmd_ACT_GEN_GET, DTIM_PERIOD_I,
			 &priv->dtim_period, true);

	mwअगरiex_parse_htinfo(priv, priv->tx_rate, priv->tx_htinfo,
			     &sinfo->txrate);

	sinfo->संकेत_avg = priv->bcn_rssi_avg;
	sinfo->rx_bytes = priv->stats.rx_bytes;
	sinfo->tx_bytes = priv->stats.tx_bytes;
	sinfo->rx_packets = priv->stats.rx_packets;
	sinfo->tx_packets = priv->stats.tx_packets;
	sinfo->संकेत = priv->bcn_rssi_avg;
	/* bit rate is in 500 kb/s units. Convert it to 100kb/s units */
	sinfo->txrate.legacy = rate * 5;

	sinfo->filled |= BIT(NL80211_STA_INFO_RX_BITRATE);
	mwअगरiex_parse_htinfo(priv, priv->rxpd_rate, priv->rxpd_htinfo,
			     &sinfo->rxrate);

	अगर (priv->bss_mode == NL80211_IFTYPE_STATION) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_BSS_PARAM);
		sinfo->bss_param.flags = 0;
		अगर (priv->curr_bss_params.bss_descriptor.cap_info_biपंचांगap &
						WLAN_CAPABILITY_SHORT_PREAMBLE)
			sinfo->bss_param.flags |=
					BSS_PARAM_FLAGS_SHORT_PREAMBLE;
		अगर (priv->curr_bss_params.bss_descriptor.cap_info_biपंचांगap &
						WLAN_CAPABILITY_SHORT_SLOT_TIME)
			sinfo->bss_param.flags |=
					BSS_PARAM_FLAGS_SHORT_SLOT_TIME;
		sinfo->bss_param.dtim_period = priv->dtim_period;
		sinfo->bss_param.beacon_पूर्णांकerval =
			priv->curr_bss_params.bss_descriptor.beacon_period;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * CFG802.11 operation handler to get station inक्रमmation.
 *
 * This function only works in connected mode, and dumps the
 * requested station inक्रमmation, अगर available.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	अगर (!priv->media_connected)
		वापस -ENOENT;
	अगर (स_भेद(mac, priv->cfg_bssid, ETH_ALEN))
		वापस -ENOENT;

	वापस mwअगरiex_dump_station_info(priv, शून्य, sinfo);
पूर्ण

/*
 * CFG802.11 operation handler to dump station inक्रमmation.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा mwअगरiex_sta_node *node;
	पूर्णांक i;

	अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) &&
	    priv->media_connected && idx == 0) अणु
		ether_addr_copy(mac, priv->cfg_bssid);
		वापस mwअगरiex_dump_station_info(priv, शून्य, sinfo);
	पूर्ण अन्यथा अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
		mwअगरiex_send_cmd(priv, HOST_CMD_APCMD_STA_LIST,
				 HostCmd_ACT_GEN_GET, 0, शून्य, true);

		i = 0;
		list_क्रम_each_entry(node, &priv->sta_list, list) अणु
			अगर (i++ != idx)
				जारी;
			ether_addr_copy(mac, node->mac_addr);
			वापस mwअगरiex_dump_station_info(priv, node, sinfo);
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_dump_survey(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     पूर्णांक idx, काष्ठा survey_info *survey)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा mwअगरiex_chan_stats *pchan_stats = priv->adapter->chan_stats;
	क्रमागत nl80211_band band;

	mwअगरiex_dbg(priv->adapter, DUMP, "dump_survey idx=%d\n", idx);

	स_रखो(survey, 0, माप(काष्ठा survey_info));

	अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) &&
	    priv->media_connected && idx == 0) अणु
			u8 curr_bss_band = priv->curr_bss_params.band;
			u32 chan = priv->curr_bss_params.bss_descriptor.channel;

			band = mwअगरiex_band_to_radio_type(curr_bss_band);
			survey->channel = ieee80211_get_channel(wiphy,
				ieee80211_channel_to_frequency(chan, band));

			अगर (priv->bcn_nf_last) अणु
				survey->filled = SURVEY_INFO_NOISE_DBM;
				survey->noise = priv->bcn_nf_last;
			पूर्ण
			वापस 0;
	पूर्ण

	अगर (idx >= priv->adapter->num_in_chan_stats)
		वापस -ENOENT;

	अगर (!pchan_stats[idx].cca_scan_dur)
		वापस 0;

	band = pchan_stats[idx].bandcfg;
	survey->channel = ieee80211_get_channel(wiphy,
	    ieee80211_channel_to_frequency(pchan_stats[idx].chan_num, band));
	survey->filled = SURVEY_INFO_NOISE_DBM |
			 SURVEY_INFO_TIME |
			 SURVEY_INFO_TIME_BUSY;
	survey->noise = pchan_stats[idx].noise;
	survey->समय = pchan_stats[idx].cca_scan_dur;
	survey->समय_busy = pchan_stats[idx].cca_busy_dur;

	वापस 0;
पूर्ण

/* Supported rates to be advertised to the cfg80211 */
अटल काष्ठा ieee80211_rate mwअगरiex_rates[] = अणु
	अणु.bitrate = 10, .hw_value = 2, पूर्ण,
	अणु.bitrate = 20, .hw_value = 4, पूर्ण,
	अणु.bitrate = 55, .hw_value = 11, पूर्ण,
	अणु.bitrate = 110, .hw_value = 22, पूर्ण,
	अणु.bitrate = 60, .hw_value = 12, पूर्ण,
	अणु.bitrate = 90, .hw_value = 18, पूर्ण,
	अणु.bitrate = 120, .hw_value = 24, पूर्ण,
	अणु.bitrate = 180, .hw_value = 36, पूर्ण,
	अणु.bitrate = 240, .hw_value = 48, पूर्ण,
	अणु.bitrate = 360, .hw_value = 72, पूर्ण,
	अणु.bitrate = 480, .hw_value = 96, पूर्ण,
	अणु.bitrate = 540, .hw_value = 108, पूर्ण,
पूर्ण;

/* Channel definitions to be advertised to cfg80211 */
अटल काष्ठा ieee80211_channel mwअगरiex_channels_2ghz[] = अणु
	अणु.center_freq = 2412, .hw_value = 1, पूर्ण,
	अणु.center_freq = 2417, .hw_value = 2, पूर्ण,
	अणु.center_freq = 2422, .hw_value = 3, पूर्ण,
	अणु.center_freq = 2427, .hw_value = 4, पूर्ण,
	अणु.center_freq = 2432, .hw_value = 5, पूर्ण,
	अणु.center_freq = 2437, .hw_value = 6, पूर्ण,
	अणु.center_freq = 2442, .hw_value = 7, पूर्ण,
	अणु.center_freq = 2447, .hw_value = 8, पूर्ण,
	अणु.center_freq = 2452, .hw_value = 9, पूर्ण,
	अणु.center_freq = 2457, .hw_value = 10, पूर्ण,
	अणु.center_freq = 2462, .hw_value = 11, पूर्ण,
	अणु.center_freq = 2467, .hw_value = 12, पूर्ण,
	अणु.center_freq = 2472, .hw_value = 13, पूर्ण,
	अणु.center_freq = 2484, .hw_value = 14, पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_supported_band mwअगरiex_band_2ghz = अणु
	.channels = mwअगरiex_channels_2ghz,
	.n_channels = ARRAY_SIZE(mwअगरiex_channels_2ghz),
	.bitrates = mwअगरiex_rates,
	.n_bitrates = ARRAY_SIZE(mwअगरiex_rates),
पूर्ण;

अटल काष्ठा ieee80211_channel mwअगरiex_channels_5ghz[] = अणु
	अणु.center_freq = 5040, .hw_value = 8, पूर्ण,
	अणु.center_freq = 5060, .hw_value = 12, पूर्ण,
	अणु.center_freq = 5080, .hw_value = 16, पूर्ण,
	अणु.center_freq = 5170, .hw_value = 34, पूर्ण,
	अणु.center_freq = 5190, .hw_value = 38, पूर्ण,
	अणु.center_freq = 5210, .hw_value = 42, पूर्ण,
	अणु.center_freq = 5230, .hw_value = 46, पूर्ण,
	अणु.center_freq = 5180, .hw_value = 36, पूर्ण,
	अणु.center_freq = 5200, .hw_value = 40, पूर्ण,
	अणु.center_freq = 5220, .hw_value = 44, पूर्ण,
	अणु.center_freq = 5240, .hw_value = 48, पूर्ण,
	अणु.center_freq = 5260, .hw_value = 52, पूर्ण,
	अणु.center_freq = 5280, .hw_value = 56, पूर्ण,
	अणु.center_freq = 5300, .hw_value = 60, पूर्ण,
	अणु.center_freq = 5320, .hw_value = 64, पूर्ण,
	अणु.center_freq = 5500, .hw_value = 100, पूर्ण,
	अणु.center_freq = 5520, .hw_value = 104, पूर्ण,
	अणु.center_freq = 5540, .hw_value = 108, पूर्ण,
	अणु.center_freq = 5560, .hw_value = 112, पूर्ण,
	अणु.center_freq = 5580, .hw_value = 116, पूर्ण,
	अणु.center_freq = 5600, .hw_value = 120, पूर्ण,
	अणु.center_freq = 5620, .hw_value = 124, पूर्ण,
	अणु.center_freq = 5640, .hw_value = 128, पूर्ण,
	अणु.center_freq = 5660, .hw_value = 132, पूर्ण,
	अणु.center_freq = 5680, .hw_value = 136, पूर्ण,
	अणु.center_freq = 5700, .hw_value = 140, पूर्ण,
	अणु.center_freq = 5745, .hw_value = 149, पूर्ण,
	अणु.center_freq = 5765, .hw_value = 153, पूर्ण,
	अणु.center_freq = 5785, .hw_value = 157, पूर्ण,
	अणु.center_freq = 5805, .hw_value = 161, पूर्ण,
	अणु.center_freq = 5825, .hw_value = 165, पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_supported_band mwअगरiex_band_5ghz = अणु
	.channels = mwअगरiex_channels_5ghz,
	.n_channels = ARRAY_SIZE(mwअगरiex_channels_5ghz),
	.bitrates = mwअगरiex_rates + 4,
	.n_bitrates = ARRAY_SIZE(mwअगरiex_rates) - 4,
पूर्ण;


/* Supported crypto cipher suits to be advertised to cfg80211 */
अटल स्थिर u32 mwअगरiex_cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104,
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
	WLAN_CIPHER_SUITE_SMS4,
	WLAN_CIPHER_SUITE_AES_CMAC,
पूर्ण;

/* Supported mgmt frame types to be advertised to cfg80211 */
अटल स्थिर काष्ठा ieee80211_txrx_stypes
mwअगरiex_mgmt_stypes[NUM_NL80211_IFTYPES] = अणु
	[NL80211_IFTYPE_STATION] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	पूर्ण,
	[NL80211_IFTYPE_AP] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	पूर्ण,
	[NL80211_IFTYPE_P2P_CLIENT] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	पूर्ण,
	[NL80211_IFTYPE_P2P_GO] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	पूर्ण,
पूर्ण;

/*
 * CFG802.11 operation handler क्रम setting bit rates.
 *
 * Function configures data rates to firmware using bitrate mask
 * provided by cfg80211.
 */
अटल पूर्णांक mwअगरiex_cfg80211_set_bitrate_mask(काष्ठा wiphy *wiphy,
				काष्ठा net_device *dev,
				स्थिर u8 *peer,
				स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	u16 biपंचांगap_rates[MAX_BITMAP_RATES_SIZE];
	क्रमागत nl80211_band band;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	अगर (!priv->media_connected) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Can not set Tx data rate in disconnected state\n");
		वापस -EINVAL;
	पूर्ण

	band = mwअगरiex_band_to_radio_type(priv->curr_bss_params.band);

	स_रखो(biपंचांगap_rates, 0, माप(biपंचांगap_rates));

	/* Fill HR/DSSS rates. */
	अगर (band == NL80211_BAND_2GHZ)
		biपंचांगap_rates[0] = mask->control[band].legacy & 0x000f;

	/* Fill OFDM rates */
	अगर (band == NL80211_BAND_2GHZ)
		biपंचांगap_rates[1] = (mask->control[band].legacy & 0x0ff0) >> 4;
	अन्यथा
		biपंचांगap_rates[1] = mask->control[band].legacy;

	/* Fill HT MCS rates */
	biपंचांगap_rates[2] = mask->control[band].ht_mcs[0];
	अगर (adapter->hw_dev_mcs_support == HT_STREAM_2X2)
		biपंचांगap_rates[2] |= mask->control[band].ht_mcs[1] << 8;

       /* Fill VHT MCS rates */
	अगर (adapter->fw_api_ver == MWIFIEX_FW_V15) अणु
		biपंचांगap_rates[10] = mask->control[band].vht_mcs[0];
		अगर (adapter->hw_dev_mcs_support == HT_STREAM_2X2)
			biपंचांगap_rates[11] = mask->control[band].vht_mcs[1];
	पूर्ण

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_TX_RATE_CFG,
				HostCmd_ACT_GEN_SET, 0, biपंचांगap_rates, true);
पूर्ण

/*
 * CFG802.11 operation handler क्रम connection quality monitoring.
 *
 * This function subscribes/unsubscribes HIGH_RSSI and LOW_RSSI
 * events to FW.
 */
अटल पूर्णांक mwअगरiex_cfg80211_set_cqm_rssi_config(काष्ठा wiphy *wiphy,
						काष्ठा net_device *dev,
						s32 rssi_thold, u32 rssi_hyst)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा mwअगरiex_ds_misc_subsc_evt subsc_evt;

	priv->cqm_rssi_thold = rssi_thold;
	priv->cqm_rssi_hyst = rssi_hyst;

	स_रखो(&subsc_evt, 0x00, माप(काष्ठा mwअगरiex_ds_misc_subsc_evt));
	subsc_evt.events = BITMASK_BCN_RSSI_LOW | BITMASK_BCN_RSSI_HIGH;

	/* Subscribe/unsubscribe low and high rssi events */
	अगर (rssi_thold && rssi_hyst) अणु
		subsc_evt.action = HostCmd_ACT_BITWISE_SET;
		subsc_evt.bcn_l_rssi_cfg.असल_value = असल(rssi_thold);
		subsc_evt.bcn_h_rssi_cfg.असल_value = असल(rssi_thold);
		subsc_evt.bcn_l_rssi_cfg.evt_freq = 1;
		subsc_evt.bcn_h_rssi_cfg.evt_freq = 1;
		वापस mwअगरiex_send_cmd(priv,
					HostCmd_CMD_802_11_SUBSCRIBE_EVENT,
					0, 0, &subsc_evt, true);
	पूर्ण अन्यथा अणु
		subsc_evt.action = HostCmd_ACT_BITWISE_CLR;
		वापस mwअगरiex_send_cmd(priv,
					HostCmd_CMD_802_11_SUBSCRIBE_EVENT,
					0, 0, &subsc_evt, true);
	पूर्ण

	वापस 0;
पूर्ण

/* cfg80211 operation handler क्रम change_beacon.
 * Function retrieves and sets modअगरied management IEs to FW.
 */
अटल पूर्णांक mwअगरiex_cfg80211_change_beacon(काष्ठा wiphy *wiphy,
					  काष्ठा net_device *dev,
					  काष्ठा cfg80211_beacon_data *data)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	mwअगरiex_cancel_scan(adapter);

	अगर (GET_BSS_ROLE(priv) != MWIFIEX_BSS_ROLE_UAP) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: bss_type mismatched\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!priv->bss_started) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: bss not started\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (mwअगरiex_set_mgmt_ies(priv, data)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: setting mgmt ies failed\n", __func__);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/* cfg80211 operation handler क्रम del_station.
 * Function deauthenticates station which value is provided in mac parameter.
 * If mac is शून्य/broadcast, all stations in associated station list are
 * deauthenticated. If bss is not started or there are no stations in
 * associated stations list, no action is taken.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_del_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     काष्ठा station_del_parameters *params)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा mwअगरiex_sta_node *sta_node;
	u8 deauth_mac[ETH_ALEN];

	अगर (!priv->bss_started && priv->wdev.cac_started) अणु
		mwअगरiex_dbg(priv->adapter, INFO, "%s: abort CAC!\n", __func__);
		mwअगरiex_पात_cac(priv);
	पूर्ण

	अगर (list_empty(&priv->sta_list) || !priv->bss_started)
		वापस 0;

	अगर (!params->mac || is_broadcast_ether_addr(params->mac))
		वापस 0;

	mwअगरiex_dbg(priv->adapter, INFO, "%s: mac address %pM\n",
		    __func__, params->mac);

	eth_zero_addr(deauth_mac);

	spin_lock_bh(&priv->sta_list_spinlock);
	sta_node = mwअगरiex_get_sta_entry(priv, params->mac);
	अगर (sta_node)
		ether_addr_copy(deauth_mac, params->mac);
	spin_unlock_bh(&priv->sta_list_spinlock);

	अगर (is_valid_ether_addr(deauth_mac)) अणु
		अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_UAP_STA_DEAUTH,
				     HostCmd_ACT_GEN_SET, 0,
				     deauth_mac, true))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_set_antenna(काष्ठा wiphy *wiphy, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_get_priv(adapter,
							MWIFIEX_BSS_ROLE_ANY);
	काष्ठा mwअगरiex_ds_ant_cfg ant_cfg;

	अगर (!tx_ant || !rx_ant)
		वापस -EOPNOTSUPP;

	अगर (adapter->hw_dev_mcs_support != HT_STREAM_2X2) अणु
		/* Not a MIMO chip. User should provide specअगरic antenna number
		 * क्रम Tx/Rx path or enable all antennas क्रम भागersity
		 */
		अगर (tx_ant != rx_ant)
			वापस -EOPNOTSUPP;

		अगर ((tx_ant & (tx_ant - 1)) &&
		    (tx_ant != BIT(adapter->number_of_antenna) - 1))
			वापस -EOPNOTSUPP;

		अगर ((tx_ant == BIT(adapter->number_of_antenna) - 1) &&
		    (priv->adapter->number_of_antenna > 1)) अणु
			tx_ant = RF_ANTENNA_AUTO;
			rx_ant = RF_ANTENNA_AUTO;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_sta_ht_cap *ht_info;
		पूर्णांक rx_mcs_supp;
		क्रमागत nl80211_band band;

		अगर ((tx_ant == 0x1 && rx_ant == 0x1)) अणु
			adapter->user_dev_mcs_support = HT_STREAM_1X1;
			अगर (adapter->is_hw_11ac_capable)
				adapter->usr_करोt_11ac_mcs_support =
						MWIFIEX_11AC_MCS_MAP_1X1;
		पूर्ण अन्यथा अणु
			adapter->user_dev_mcs_support = HT_STREAM_2X2;
			अगर (adapter->is_hw_11ac_capable)
				adapter->usr_करोt_11ac_mcs_support =
						MWIFIEX_11AC_MCS_MAP_2X2;
		पूर्ण

		क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
			अगर (!adapter->wiphy->bands[band])
				जारी;

			ht_info = &adapter->wiphy->bands[band]->ht_cap;
			rx_mcs_supp =
				GET_RXMCSSUPP(adapter->user_dev_mcs_support);
			स_रखो(&ht_info->mcs, 0, adapter->number_of_antenna);
			स_रखो(&ht_info->mcs, 0xff, rx_mcs_supp);
		पूर्ण
	पूर्ण

	ant_cfg.tx_ant = tx_ant;
	ant_cfg.rx_ant = rx_ant;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_RF_ANTENNA,
				HostCmd_ACT_GEN_SET, 0, &ant_cfg, true);
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_get_antenna(काष्ठा wiphy *wiphy, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_get_priv(adapter,
							MWIFIEX_BSS_ROLE_ANY);
	mwअगरiex_send_cmd(priv, HostCmd_CMD_RF_ANTENNA,
			 HostCmd_ACT_GEN_GET, 0, शून्य, true);

	*tx_ant = priv->tx_ant;
	*rx_ant = priv->rx_ant;

	वापस 0;
पूर्ण

/* cfg80211 operation handler क्रम stop ap.
 * Function stops BSS running at uAP पूर्णांकerface.
 */
अटल पूर्णांक mwअगरiex_cfg80211_stop_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	mwअगरiex_पात_cac(priv);

	अगर (mwअगरiex_del_mgmt_ies(priv))
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to delete mgmt IEs!\n");

	priv->ap_11n_enabled = 0;
	स_रखो(&priv->bss_cfg, 0, माप(priv->bss_cfg));

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_UAP_BSS_STOP,
			     HostCmd_ACT_GEN_SET, 0, शून्य, true)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to stop the BSS\n");
		वापस -1;
	पूर्ण

	अगर (mwअगरiex_send_cmd(priv, HOST_CMD_APCMD_SYS_RESET,
			     HostCmd_ACT_GEN_SET, 0, शून्य, true)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to reset BSS\n");
		वापस -1;
	पूर्ण

	अगर (netअगर_carrier_ok(priv->netdev))
		netअगर_carrier_off(priv->netdev);
	mwअगरiex_stop_net_dev_queue(priv->netdev, priv->adapter);

	वापस 0;
पूर्ण

/* cfg80211 operation handler क्रम start_ap.
 * Function sets beacon period, DTIM period, SSID and security पूर्णांकo
 * AP config काष्ठाure.
 * AP is configured with these settings and BSS is started.
 */
अटल पूर्णांक mwअगरiex_cfg80211_start_ap(काष्ठा wiphy *wiphy,
				     काष्ठा net_device *dev,
				     काष्ठा cfg80211_ap_settings *params)
अणु
	काष्ठा mwअगरiex_uap_bss_param *bss_cfg;
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	अगर (GET_BSS_ROLE(priv) != MWIFIEX_BSS_ROLE_UAP)
		वापस -1;

	bss_cfg = kzalloc(माप(काष्ठा mwअगरiex_uap_bss_param), GFP_KERNEL);
	अगर (!bss_cfg)
		वापस -ENOMEM;

	mwअगरiex_set_sys_config_invalid_data(bss_cfg);

	अगर (params->beacon_पूर्णांकerval)
		bss_cfg->beacon_period = params->beacon_पूर्णांकerval;
	अगर (params->dtim_period)
		bss_cfg->dtim_period = params->dtim_period;

	अगर (params->ssid && params->ssid_len) अणु
		स_नकल(bss_cfg->ssid.ssid, params->ssid, params->ssid_len);
		bss_cfg->ssid.ssid_len = params->ssid_len;
	पूर्ण
	अगर (params->inactivity_समयout > 0) अणु
		/* sta_ao_समयr/ps_sta_ao_समयr is in unit of 100ms */
		bss_cfg->sta_ao_समयr = 10 * params->inactivity_समयout;
		bss_cfg->ps_sta_ao_समयr = 10 * params->inactivity_समयout;
	पूर्ण

	चयन (params->hidden_ssid) अणु
	हाल NL80211_HIDDEN_SSID_NOT_IN_USE:
		bss_cfg->bcast_ssid_ctl = 1;
		अवरोध;
	हाल NL80211_HIDDEN_SSID_ZERO_LEN:
		bss_cfg->bcast_ssid_ctl = 0;
		अवरोध;
	हाल NL80211_HIDDEN_SSID_ZERO_CONTENTS:
		bss_cfg->bcast_ssid_ctl = 2;
		अवरोध;
	शेष:
		kमुक्त(bss_cfg);
		वापस -EINVAL;
	पूर्ण

	mwअगरiex_uap_set_channel(priv, bss_cfg, params->chandef);
	mwअगरiex_set_uap_rates(bss_cfg, params);

	अगर (mwअगरiex_set_secure_params(priv, bss_cfg, params)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to parse security parameters!\n");
		जाओ out;
	पूर्ण

	mwअगरiex_set_ht_params(priv, bss_cfg, params);

	अगर (priv->adapter->is_hw_11ac_capable) अणु
		mwअगरiex_set_vht_params(priv, bss_cfg, params);
		mwअगरiex_set_vht_width(priv, params->chandef.width,
				      priv->ap_11ac_enabled);
	पूर्ण

	अगर (priv->ap_11ac_enabled)
		mwअगरiex_set_11ac_ba_params(priv);
	अन्यथा
		mwअगरiex_set_ba_params(priv);

	mwअगरiex_set_wmm_params(priv, bss_cfg, params);

	अगर (mwअगरiex_is_11h_active(priv))
		mwअगरiex_set_tpc_params(priv, bss_cfg, params);

	अगर (mwअगरiex_is_11h_active(priv) &&
	    !cfg80211_chandef_dfs_required(wiphy, &params->chandef,
					   priv->bss_mode)) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "Disable 11h extensions in FW\n");
		अगर (mwअगरiex_11h_activate(priv, false)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Failed to disable 11h extensions!!");
			जाओ out;
		पूर्ण
		priv->state_11h.is_11h_active = false;
	पूर्ण

	mwअगरiex_config_uap_11d(priv, &params->beacon);

	अगर (mwअगरiex_config_start_uap(priv, bss_cfg)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to start AP\n");
		जाओ out;
	पूर्ण

	अगर (mwअगरiex_set_mgmt_ies(priv, &params->beacon))
		जाओ out;

	अगर (!netअगर_carrier_ok(priv->netdev))
		netअगर_carrier_on(priv->netdev);
	mwअगरiex_wake_up_net_dev_queue(priv->netdev, priv->adapter);

	स_नकल(&priv->bss_cfg, bss_cfg, माप(priv->bss_cfg));
	kमुक्त(bss_cfg);
	वापस 0;

out:
	kमुक्त(bss_cfg);
	वापस -1;
पूर्ण

/*
 * CFG802.11 operation handler क्रम disconnection request.
 *
 * This function करोes not work when there is alपढ़ोy a disconnection
 * procedure going on.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			    u16 reason_code)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	अगर (!mwअगरiex_stop_bg_scan(priv))
		cfg80211_sched_scan_stopped_locked(priv->wdev.wiphy, 0);

	अगर (mwअगरiex_deauthenticate(priv, शून्य))
		वापस -EFAULT;

	eth_zero_addr(priv->cfg_bssid);
	priv->hs2_enabled = false;

	वापस 0;
पूर्ण

/*
 * This function inक्रमms the CFG802.11 subप्रणाली of a new IBSS.
 *
 * The following inक्रमmation are sent to the CFG802.11 subप्रणाली
 * to रेजिस्टर the new IBSS. If we करो not रेजिस्टर the new IBSS,
 * a kernel panic will result.
 *      - SSID
 *      - SSID length
 *      - BSSID
 *      - Channel
 */
अटल पूर्णांक mwअगरiex_cfg80211_inक्रमm_ibss_bss(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा ieee80211_channel *chan;
	काष्ठा mwअगरiex_bss_info bss_info;
	काष्ठा cfg80211_bss *bss;
	पूर्णांक ie_len;
	u8 ie_buf[IEEE80211_MAX_SSID_LEN + माप(काष्ठा ieee_types_header)];
	क्रमागत nl80211_band band;

	अगर (mwअगरiex_get_bss_info(priv, &bss_info))
		वापस -1;

	ie_buf[0] = WLAN_EID_SSID;
	ie_buf[1] = bss_info.ssid.ssid_len;

	स_नकल(&ie_buf[माप(काष्ठा ieee_types_header)],
	       &bss_info.ssid.ssid, bss_info.ssid.ssid_len);
	ie_len = ie_buf[1] + माप(काष्ठा ieee_types_header);

	band = mwअगरiex_band_to_radio_type(priv->curr_bss_params.band);
	chan = ieee80211_get_channel(priv->wdev.wiphy,
			ieee80211_channel_to_frequency(bss_info.bss_chan,
						       band));

	bss = cfg80211_inक्रमm_bss(priv->wdev.wiphy, chan,
				  CFG80211_BSS_FTYPE_UNKNOWN,
				  bss_info.bssid, 0, WLAN_CAPABILITY_IBSS,
				  0, ie_buf, ie_len, 0, GFP_KERNEL);
	अगर (bss) अणु
		cfg80211_put_bss(priv->wdev.wiphy, bss);
		ether_addr_copy(priv->cfg_bssid, bss_info.bssid);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function connects with a BSS.
 *
 * This function handles both Infra and Ad-Hoc modes. It also perक्रमms
 * validity checking on the provided parameters, disconnects from the
 * current BSS (अगर any), sets up the association/scan parameters,
 * including security settings, and perक्रमms specअगरic SSID scan beक्रमe
 * trying to connect.
 *
 * For Infra mode, the function वापसs failure अगर the specअगरied SSID
 * is not found in scan table. However, क्रम Ad-Hoc mode, it can create
 * the IBSS अगर it करोes not exist. On successful completion in either हाल,
 * the function notअगरies the CFG802.11 subप्रणाली of the new BSS connection.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_assoc(काष्ठा mwअगरiex_निजी *priv, माप_प्रकार ssid_len,
		       स्थिर u8 *ssid, स्थिर u8 *bssid, पूर्णांक mode,
		       काष्ठा ieee80211_channel *channel,
		       काष्ठा cfg80211_connect_params *sme, bool privacy,
		       काष्ठा cfg80211_bss **sel_bss)
अणु
	काष्ठा cfg80211_ssid req_ssid;
	पूर्णांक ret, auth_type = 0;
	काष्ठा cfg80211_bss *bss = शून्य;
	u8 is_scanning_required = 0;

	स_रखो(&req_ssid, 0, माप(काष्ठा cfg80211_ssid));

	req_ssid.ssid_len = ssid_len;
	अगर (ssid_len > IEEE80211_MAX_SSID_LEN) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "invalid SSID - aborting\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(req_ssid.ssid, ssid, ssid_len);
	अगर (!req_ssid.ssid_len || req_ssid.ssid[0] < 0x20) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "invalid SSID - aborting\n");
		वापस -EINVAL;
	पूर्ण

	/* As this is new association, clear locally stored
	 * keys and security related flags */
	priv->sec_info.wpa_enabled = false;
	priv->sec_info.wpa2_enabled = false;
	priv->wep_key_curr_index = 0;
	priv->sec_info.encryption_mode = 0;
	priv->sec_info.is_authtype_स्वतः = 0;
	ret = mwअगरiex_set_encode(priv, शून्य, शून्य, 0, 0, शून्य, 1);

	अगर (mode == NL80211_IFTYPE_ADHOC) अणु
		u16 enable = true;

		/* set ibss coalescing_status */
		ret = mwअगरiex_send_cmd(
				priv,
				HostCmd_CMD_802_11_IBSS_COALESCING_STATUS,
				HostCmd_ACT_GEN_SET, 0, &enable, true);
		अगर (ret)
			वापस ret;

		/* "privacy" is set only क्रम ad-hoc mode */
		अगर (privacy) अणु
			/*
			 * Keep WLAN_CIPHER_SUITE_WEP104 क्रम now so that
			 * the firmware can find a matching network from the
			 * scan. The cfg80211 करोes not give us the encryption
			 * mode at this stage so just setting it to WEP here.
			 */
			priv->sec_info.encryption_mode =
					WLAN_CIPHER_SUITE_WEP104;
			priv->sec_info.authentication_mode =
					NL80211_AUTHTYPE_OPEN_SYSTEM;
		पूर्ण

		जाओ करोne;
	पूर्ण

	/* Now handle infra mode. "sme" is valid क्रम infra mode only */
	अगर (sme->auth_type == NL80211_AUTHTYPE_AUTOMATIC) अणु
		auth_type = NL80211_AUTHTYPE_OPEN_SYSTEM;
		priv->sec_info.is_authtype_स्वतः = 1;
	पूर्ण अन्यथा अणु
		auth_type = sme->auth_type;
	पूर्ण

	अगर (sme->crypto.n_ciphers_pairwise) अणु
		priv->sec_info.encryption_mode =
						sme->crypto.ciphers_pairwise[0];
		priv->sec_info.authentication_mode = auth_type;
	पूर्ण

	अगर (sme->crypto.cipher_group) अणु
		priv->sec_info.encryption_mode = sme->crypto.cipher_group;
		priv->sec_info.authentication_mode = auth_type;
	पूर्ण
	अगर (sme->ie)
		ret = mwअगरiex_set_gen_ie(priv, sme->ie, sme->ie_len);

	अगर (sme->key) अणु
		अगर (mwअगरiex_is_alg_wep(priv->sec_info.encryption_mode)) अणु
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: setting wep encryption\t"
				    "with key len %d\n", sme->key_len);
			priv->wep_key_curr_index = sme->key_idx;
			ret = mwअगरiex_set_encode(priv, शून्य, sme->key,
						 sme->key_len, sme->key_idx,
						 शून्य, 0);
		पूर्ण
	पूर्ण
करोne:
	/*
	 * Scan entries are valid क्रम some समय (15 sec). So we can save one
	 * active scan समय अगर we just try cfg80211_get_bss first. If it fails
	 * then request scan and cfg80211_get_bss() again क्रम final output.
	 */
	जबतक (1) अणु
		अगर (is_scanning_required) अणु
			/* Do specअगरic SSID scanning */
			अगर (mwअगरiex_request_scan(priv, &req_ssid)) अणु
				mwअगरiex_dbg(priv->adapter, ERROR, "scan error\n");
				वापस -EFAULT;
			पूर्ण
		पूर्ण

		/* Find the BSS we want using available scan results */
		अगर (mode == NL80211_IFTYPE_ADHOC)
			bss = cfg80211_get_bss(priv->wdev.wiphy, channel,
					       bssid, ssid, ssid_len,
					       IEEE80211_BSS_TYPE_IBSS,
					       IEEE80211_PRIVACY_ANY);
		अन्यथा
			bss = cfg80211_get_bss(priv->wdev.wiphy, channel,
					       bssid, ssid, ssid_len,
					       IEEE80211_BSS_TYPE_ESS,
					       IEEE80211_PRIVACY_ANY);

		अगर (!bss) अणु
			अगर (is_scanning_required) अणु
				mwअगरiex_dbg(priv->adapter, MSG,
					    "assoc: requested bss not found in scan results\n");
				अवरोध;
			पूर्ण
			is_scanning_required = 1;
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(priv->adapter, MSG,
				    "info: trying to associate to bssid %pM\n",
				    bss->bssid);
			स_नकल(&priv->cfg_bssid, bss->bssid, ETH_ALEN);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bss)
		cfg80211_ref_bss(priv->adapter->wiphy, bss);

	ret = mwअगरiex_bss_start(priv, bss, &req_ssid);
	अगर (ret)
		जाओ cleanup;

	अगर (mode == NL80211_IFTYPE_ADHOC) अणु
		/* Inक्रमm the BSS inक्रमmation to kernel, otherwise
		 * kernel will give a panic after successful assoc */
		अगर (mwअगरiex_cfg80211_inक्रमm_ibss_bss(priv)) अणु
			ret = -EFAULT;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/* Pass the selected BSS entry to caller. */
	अगर (sel_bss) अणु
		*sel_bss = bss;
		bss = शून्य;
	पूर्ण

cleanup:
	अगर (bss)
		cfg80211_put_bss(priv->adapter->wiphy, bss);
	वापस ret;
पूर्ण

/*
 * CFG802.11 operation handler क्रम association request.
 *
 * This function करोes not work when the current mode is set to Ad-Hoc, or
 * when there is alपढ़ोy an association procedure going on. The given BSS
 * inक्रमmation is used to associate.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			 काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा cfg80211_bss *bss = शून्य;
	पूर्णांक ret;

	अगर (GET_BSS_ROLE(priv) != MWIFIEX_BSS_ROLE_STA) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: reject infra assoc request in non-STA role\n",
			    dev->name);
		वापस -EINVAL;
	पूर्ण

	अगर (priv->wdev.current_bss) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: already connected\n", dev->name);
		वापस -EALREADY;
	पूर्ण

	अगर (priv->scan_block)
		priv->scan_block = false;

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags) ||
	    test_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: Ignore connection.\t"
			    "Card removed or FW in bad state\n",
			    dev->name);
		वापस -EFAULT;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "info: Trying to associate to bssid %pM\n", sme->bssid);

	अगर (!mwअगरiex_stop_bg_scan(priv))
		cfg80211_sched_scan_stopped_locked(priv->wdev.wiphy, 0);

	ret = mwअगरiex_cfg80211_assoc(priv, sme->ssid_len, sme->ssid, sme->bssid,
				     priv->bss_mode, sme->channel, sme, 0,
				     &bss);
	अगर (!ret) अणु
		cfg80211_connect_bss(priv->netdev, priv->cfg_bssid, bss, शून्य,
				     0, शून्य, 0, WLAN_STATUS_SUCCESS,
				     GFP_KERNEL, NL80211_TIMEOUT_UNSPECIFIED);
		mwअगरiex_dbg(priv->adapter, MSG,
			    "info: associated to bssid %pM successfully\n",
			    priv->cfg_bssid);
		अगर (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
		    priv->adapter->स्वतः_tdls &&
		    priv->bss_type == MWIFIEX_BSS_TYPE_STA)
			mwअगरiex_setup_स्वतः_tdls_समयr(priv);
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "info: association to bssid %pM failed\n",
			    priv->cfg_bssid);
		eth_zero_addr(priv->cfg_bssid);

		अगर (ret > 0)
			cfg80211_connect_result(priv->netdev, priv->cfg_bssid,
						शून्य, 0, शून्य, 0, ret,
						GFP_KERNEL);
		अन्यथा
			cfg80211_connect_result(priv->netdev, priv->cfg_bssid,
						शून्य, 0, शून्य, 0,
						WLAN_STATUS_UNSPECIFIED_FAILURE,
						GFP_KERNEL);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function sets following parameters क्रम ibss network.
 *  -  channel
 *  -  start band
 *  -  11n flag
 *  -  secondary channel offset
 */
अटल पूर्णांक mwअगरiex_set_ibss_params(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा cfg80211_ibss_params *params)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक index = 0, i;
	u8 config_bands = 0;

	अगर (params->chandef.chan->band == NL80211_BAND_2GHZ) अणु
		अगर (!params->basic_rates) अणु
			config_bands = BAND_B | BAND_G;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < mwअगरiex_band_2ghz.n_bitrates; i++) अणु
				/*
				 * Rates below 6 Mbps in the table are CCK
				 * rates; 802.11b and from 6 they are OFDM;
				 * 802.11G
				 */
				अगर (mwअगरiex_rates[i].bitrate == 60) अणु
					index = 1 << i;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (params->basic_rates < index) अणु
				config_bands = BAND_B;
			पूर्ण अन्यथा अणु
				config_bands = BAND_G;
				अगर (params->basic_rates % index)
					config_bands |= BAND_B;
			पूर्ण
		पूर्ण

		अगर (cfg80211_get_chandef_type(&params->chandef) !=
						NL80211_CHAN_NO_HT)
			config_bands |= BAND_G | BAND_GN;
	पूर्ण अन्यथा अणु
		अगर (cfg80211_get_chandef_type(&params->chandef) ==
						NL80211_CHAN_NO_HT)
			config_bands = BAND_A;
		अन्यथा
			config_bands = BAND_AN | BAND_A;
	पूर्ण

	अगर (!((config_bands | adapter->fw_bands) & ~adapter->fw_bands)) अणु
		adapter->config_bands = config_bands;
		adapter->adhoc_start_band = config_bands;

		अगर ((config_bands & BAND_GN) || (config_bands & BAND_AN))
			adapter->adhoc_11n_enabled = true;
		अन्यथा
			adapter->adhoc_11n_enabled = false;
	पूर्ण

	adapter->sec_chan_offset =
		mwअगरiex_chan_type_to_sec_chan_offset(
			cfg80211_get_chandef_type(&params->chandef));
	priv->adhoc_channel = ieee80211_frequency_to_channel(
				params->chandef.chan->center_freq);

	mwअगरiex_dbg(adapter, INFO,
		    "info: set ibss band %d, chan %d, chan offset %d\n",
		    config_bands, priv->adhoc_channel,
		    adapter->sec_chan_offset);

	वापस 0;
पूर्ण

/*
 * CFG802.11 operation handler to join an IBSS.
 *
 * This function करोes not work in any mode other than Ad-Hoc, or अगर
 * a join operation is alपढ़ोy in progress.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_join_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   काष्ठा cfg80211_ibss_params *params)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	पूर्णांक ret = 0;

	अगर (priv->bss_mode != NL80211_IFTYPE_ADHOC) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "request to join ibss received\t"
			    "when station is not in ibss mode\n");
		जाओ करोne;
	पूर्ण

	mwअगरiex_dbg(priv->adapter, MSG, "info: trying to join to bssid %pM\n",
		    params->bssid);

	mwअगरiex_set_ibss_params(priv, params);

	ret = mwअगरiex_cfg80211_assoc(priv, params->ssid_len, params->ssid,
				     params->bssid, priv->bss_mode,
				     params->chandef.chan, शून्य,
				     params->privacy, शून्य);
करोne:
	अगर (!ret) अणु
		cfg80211_ibss_joined(priv->netdev, priv->cfg_bssid,
				     params->chandef.chan, GFP_KERNEL);
		mwअगरiex_dbg(priv->adapter, MSG,
			    "info: joined/created adhoc network with bssid\t"
			    "%pM successfully\n", priv->cfg_bssid);
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "info: failed creating/joining adhoc network\n");
	पूर्ण

	वापस ret;
पूर्ण

/*
 * CFG802.11 operation handler to leave an IBSS.
 *
 * This function करोes not work अगर a leave operation is
 * alपढ़ोy in progress.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_leave_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	mwअगरiex_dbg(priv->adapter, MSG, "info: disconnecting from essid %pM\n",
		    priv->cfg_bssid);
	अगर (mwअगरiex_deauthenticate(priv, शून्य))
		वापस -EFAULT;

	eth_zero_addr(priv->cfg_bssid);

	वापस 0;
पूर्ण

/*
 * CFG802.11 operation handler क्रम scan request.
 *
 * This function issues a scan request to the firmware based upon
 * the user specअगरied scan configuration. On successful completion,
 * it also inक्रमms the results.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_scan(काष्ठा wiphy *wiphy,
		      काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा net_device *dev = request->wdev->netdev;
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	पूर्णांक i, offset, ret;
	काष्ठा ieee80211_channel *chan;
	काष्ठा ieee_types_header *ie;
	काष्ठा mwअगरiex_user_scan_cfg *user_scan_cfg;
	u8 mac_addr[ETH_ALEN];

	mwअगरiex_dbg(priv->adapter, CMD,
		    "info: received scan request on %s\n", dev->name);

	/* Block scan request अगर scan operation or scan cleanup when पूर्णांकerface
	 * is disabled is in process
	 */
	अगर (priv->scan_request || priv->scan_पातing) अणु
		mwअगरiex_dbg(priv->adapter, WARN,
			    "cmd: Scan already in process..\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!priv->wdev.current_bss && priv->scan_block)
		priv->scan_block = false;

	अगर (!mwअगरiex_stop_bg_scan(priv))
		cfg80211_sched_scan_stopped_locked(priv->wdev.wiphy, 0);

	user_scan_cfg = kzalloc(माप(*user_scan_cfg), GFP_KERNEL);
	अगर (!user_scan_cfg)
		वापस -ENOMEM;

	priv->scan_request = request;

	अगर (request->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) अणु
		get_अक्रमom_mask_addr(mac_addr, request->mac_addr,
				     request->mac_addr_mask);
		ether_addr_copy(request->mac_addr, mac_addr);
		ether_addr_copy(user_scan_cfg->अक्रमom_mac, mac_addr);
	पूर्ण

	user_scan_cfg->num_ssids = request->n_ssids;
	user_scan_cfg->ssid_list = request->ssids;

	अगर (request->ie && request->ie_len) अणु
		offset = 0;
		क्रम (i = 0; i < MWIFIEX_MAX_VSIE_NUM; i++) अणु
			अगर (priv->vs_ie[i].mask != MWIFIEX_VSIE_MASK_CLEAR)
				जारी;
			priv->vs_ie[i].mask = MWIFIEX_VSIE_MASK_SCAN;
			ie = (काष्ठा ieee_types_header *)(request->ie + offset);
			स_नकल(&priv->vs_ie[i].ie, ie, माप(*ie) + ie->len);
			offset += माप(*ie) + ie->len;

			अगर (offset >= request->ie_len)
				अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < min_t(u32, request->n_channels,
			      MWIFIEX_USER_SCAN_CHAN_MAX); i++) अणु
		chan = request->channels[i];
		user_scan_cfg->chan_list[i].chan_number = chan->hw_value;
		user_scan_cfg->chan_list[i].radio_type = chan->band;

		अगर ((chan->flags & IEEE80211_CHAN_NO_IR) || !request->n_ssids)
			user_scan_cfg->chan_list[i].scan_type =
						MWIFIEX_SCAN_TYPE_PASSIVE;
		अन्यथा
			user_scan_cfg->chan_list[i].scan_type =
						MWIFIEX_SCAN_TYPE_ACTIVE;

		user_scan_cfg->chan_list[i].scan_समय = 0;
	पूर्ण

	अगर (priv->adapter->scan_chan_gap_enabled &&
	    mwअगरiex_is_any_पूर्णांकf_active(priv))
		user_scan_cfg->scan_chan_gap =
					      priv->adapter->scan_chan_gap_समय;

	ret = mwअगरiex_scan_networks(priv, user_scan_cfg);
	kमुक्त(user_scan_cfg);
	अगर (ret) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "scan failed: %d\n", ret);
		priv->scan_पातing = false;
		priv->scan_request = शून्य;
		वापस ret;
	पूर्ण

	अगर (request->ie && request->ie_len) अणु
		क्रम (i = 0; i < MWIFIEX_MAX_VSIE_NUM; i++) अणु
			अगर (priv->vs_ie[i].mask == MWIFIEX_VSIE_MASK_SCAN) अणु
				priv->vs_ie[i].mask = MWIFIEX_VSIE_MASK_CLEAR;
				स_रखो(&priv->vs_ie[i].ie, 0,
				       MWIFIEX_MAX_VSIE_LEN);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* CFG802.11 operation handler क्रम sched_scan_start.
 *
 * This function issues a bgscan config request to the firmware based upon
 * the user specअगरied sched_scan configuration. On successful completion,
 * firmware will generate BGSCAN_REPORT event, driver should issue bgscan
 * query command to get sched_scan results from firmware.
 */
अटल पूर्णांक
mwअगरiex_cfg80211_sched_scan_start(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *dev,
				  काष्ठा cfg80211_sched_scan_request *request)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	पूर्णांक i, offset;
	काष्ठा ieee80211_channel *chan;
	काष्ठा mwअगरiex_bg_scan_cfg *bgscan_cfg;
	काष्ठा ieee_types_header *ie;

	अगर (!request || (!request->n_ssids && !request->n_match_sets)) अणु
		wiphy_err(wiphy, "%s : Invalid Sched_scan parameters",
			  __func__);
		वापस -EINVAL;
	पूर्ण

	wiphy_info(wiphy, "sched_scan start : n_ssids=%d n_match_sets=%d ",
		   request->n_ssids, request->n_match_sets);
	wiphy_info(wiphy, "n_channels=%d interval=%d ie_len=%d\n",
		   request->n_channels, request->scan_plans->पूर्णांकerval,
		   (पूर्णांक)request->ie_len);

	bgscan_cfg = kzalloc(माप(*bgscan_cfg), GFP_KERNEL);
	अगर (!bgscan_cfg)
		वापस -ENOMEM;

	अगर (priv->scan_request || priv->scan_पातing)
		bgscan_cfg->start_later = true;

	bgscan_cfg->num_ssids = request->n_match_sets;
	bgscan_cfg->ssid_list = request->match_sets;

	अगर (request->ie && request->ie_len) अणु
		offset = 0;
		क्रम (i = 0; i < MWIFIEX_MAX_VSIE_NUM; i++) अणु
			अगर (priv->vs_ie[i].mask != MWIFIEX_VSIE_MASK_CLEAR)
				जारी;
			priv->vs_ie[i].mask = MWIFIEX_VSIE_MASK_BGSCAN;
			ie = (काष्ठा ieee_types_header *)(request->ie + offset);
			स_नकल(&priv->vs_ie[i].ie, ie, माप(*ie) + ie->len);
			offset += माप(*ie) + ie->len;

			अगर (offset >= request->ie_len)
				अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < min_t(u32, request->n_channels,
			      MWIFIEX_BG_SCAN_CHAN_MAX); i++) अणु
		chan = request->channels[i];
		bgscan_cfg->chan_list[i].chan_number = chan->hw_value;
		bgscan_cfg->chan_list[i].radio_type = chan->band;

		अगर ((chan->flags & IEEE80211_CHAN_NO_IR) || !request->n_ssids)
			bgscan_cfg->chan_list[i].scan_type =
						MWIFIEX_SCAN_TYPE_PASSIVE;
		अन्यथा
			bgscan_cfg->chan_list[i].scan_type =
						MWIFIEX_SCAN_TYPE_ACTIVE;

		bgscan_cfg->chan_list[i].scan_समय = 0;
	पूर्ण

	bgscan_cfg->chan_per_scan = min_t(u32, request->n_channels,
					  MWIFIEX_BG_SCAN_CHAN_MAX);

	/* Use at least 15 second क्रम per scan cycle */
	bgscan_cfg->scan_पूर्णांकerval = (request->scan_plans->पूर्णांकerval >
				     MWIFIEX_BGSCAN_INTERVAL) ?
				request->scan_plans->पूर्णांकerval :
				MWIFIEX_BGSCAN_INTERVAL;

	bgscan_cfg->repeat_count = MWIFIEX_BGSCAN_REPEAT_COUNT;
	bgscan_cfg->report_condition = MWIFIEX_BGSCAN_SSID_MATCH |
				MWIFIEX_BGSCAN_WAIT_ALL_CHAN_DONE;
	bgscan_cfg->bss_type = MWIFIEX_BSS_MODE_INFRA;
	bgscan_cfg->action = MWIFIEX_BGSCAN_ACT_SET;
	bgscan_cfg->enable = true;
	अगर (request->min_rssi_thold != NL80211_SCAN_RSSI_THOLD_OFF) अणु
		bgscan_cfg->report_condition |= MWIFIEX_BGSCAN_SSID_RSSI_MATCH;
		bgscan_cfg->rssi_threshold = request->min_rssi_thold;
	पूर्ण

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_BG_SCAN_CONFIG,
			     HostCmd_ACT_GEN_SET, 0, bgscan_cfg, true)) अणु
		kमुक्त(bgscan_cfg);
		वापस -EFAULT;
	पूर्ण

	priv->sched_scanning = true;

	kमुक्त(bgscan_cfg);
	वापस 0;
पूर्ण

/* CFG802.11 operation handler क्रम sched_scan_stop.
 *
 * This function issues a bgscan config command to disable
 * previous bgscan configuration in the firmware
 */
अटल पूर्णांक mwअगरiex_cfg80211_sched_scan_stop(काष्ठा wiphy *wiphy,
					    काष्ठा net_device *dev, u64 reqid)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	wiphy_info(wiphy, "sched scan stop!");
	mwअगरiex_stop_bg_scan(priv);

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_setup_vht_caps(काष्ठा ieee80211_sta_vht_cap *vht_info,
				   काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	vht_info->vht_supported = true;

	vht_info->cap = adapter->hw_करोt_11ac_dev_cap;
	/* Update MCS support क्रम VHT */
	vht_info->vht_mcs.rx_mcs_map = cpu_to_le16(
				adapter->hw_करोt_11ac_mcs_support & 0xFFFF);
	vht_info->vht_mcs.rx_highest = 0;
	vht_info->vht_mcs.tx_mcs_map = cpu_to_le16(
				adapter->hw_करोt_11ac_mcs_support >> 16);
	vht_info->vht_mcs.tx_highest = 0;
पूर्ण

/*
 * This function sets up the CFG802.11 specअगरic HT capability fields
 * with शेष values.
 *
 * The following शेष values are set -
 *      - HT Supported = True
 *      - Maximum AMPDU length factor = IEEE80211_HT_MAX_AMPDU_64K
 *      - Minimum AMPDU spacing = IEEE80211_HT_MPDU_DENSITY_NONE
 *      - HT Capabilities supported by firmware
 *      - MCS inक्रमmation, Rx mask = 0xff
 *      - MCD inक्रमmation, Tx parameters = IEEE80211_HT_MCS_TX_DEFINED (0x01)
 */
अटल व्योम
mwअगरiex_setup_ht_caps(काष्ठा ieee80211_sta_ht_cap *ht_info,
		      काष्ठा mwअगरiex_निजी *priv)
अणु
	पूर्णांक rx_mcs_supp;
	काष्ठा ieee80211_mcs_info mcs_set;
	u8 *mcs = (u8 *)&mcs_set;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	ht_info->ht_supported = true;
	ht_info->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_info->ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE;

	स_रखो(&ht_info->mcs, 0, माप(ht_info->mcs));

	/* Fill HT capability inक्रमmation */
	अगर (ISSUPP_CHANWIDTH40(adapter->hw_करोt_11n_dev_cap))
		ht_info->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	अन्यथा
		ht_info->cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;

	अगर (ISSUPP_SHORTGI20(adapter->hw_करोt_11n_dev_cap))
		ht_info->cap |= IEEE80211_HT_CAP_SGI_20;
	अन्यथा
		ht_info->cap &= ~IEEE80211_HT_CAP_SGI_20;

	अगर (ISSUPP_SHORTGI40(adapter->hw_करोt_11n_dev_cap))
		ht_info->cap |= IEEE80211_HT_CAP_SGI_40;
	अन्यथा
		ht_info->cap &= ~IEEE80211_HT_CAP_SGI_40;

	अगर (adapter->user_dev_mcs_support == HT_STREAM_2X2)
		ht_info->cap |= 2 << IEEE80211_HT_CAP_RX_STBC_SHIFT;
	अन्यथा
		ht_info->cap |= 1 << IEEE80211_HT_CAP_RX_STBC_SHIFT;

	अगर (ISSUPP_TXSTBC(adapter->hw_करोt_11n_dev_cap))
		ht_info->cap |= IEEE80211_HT_CAP_TX_STBC;
	अन्यथा
		ht_info->cap &= ~IEEE80211_HT_CAP_TX_STBC;

	अगर (ISSUPP_GREENFIELD(adapter->hw_करोt_11n_dev_cap))
		ht_info->cap |= IEEE80211_HT_CAP_GRN_FLD;
	अन्यथा
		ht_info->cap &= ~IEEE80211_HT_CAP_GRN_FLD;

	अगर (ISENABLED_40MHZ_INTOLERANT(adapter->hw_करोt_11n_dev_cap))
		ht_info->cap |= IEEE80211_HT_CAP_40MHZ_INTOLERANT;
	अन्यथा
		ht_info->cap &= ~IEEE80211_HT_CAP_40MHZ_INTOLERANT;

	अगर (ISSUPP_RXLDPC(adapter->hw_करोt_11n_dev_cap))
		ht_info->cap |= IEEE80211_HT_CAP_LDPC_CODING;
	अन्यथा
		ht_info->cap &= ~IEEE80211_HT_CAP_LDPC_CODING;

	ht_info->cap &= ~IEEE80211_HT_CAP_MAX_AMSDU;
	ht_info->cap |= IEEE80211_HT_CAP_SM_PS;

	rx_mcs_supp = GET_RXMCSSUPP(adapter->user_dev_mcs_support);
	/* Set MCS क्रम 1x1/2x2 */
	स_रखो(mcs, 0xff, rx_mcs_supp);
	/* Clear all the other values */
	स_रखो(&mcs[rx_mcs_supp], 0,
	       माप(काष्ठा ieee80211_mcs_info) - rx_mcs_supp);
	अगर (priv->bss_mode == NL80211_IFTYPE_STATION ||
	    ISSUPP_CHANWIDTH40(adapter->hw_करोt_11n_dev_cap))
		/* Set MCS32 क्रम infra mode or ad-hoc mode with 40MHz support */
		SETHT_MCS32(mcs_set.rx_mask);

	स_नकल((u8 *) &ht_info->mcs, mcs, माप(काष्ठा ieee80211_mcs_info));

	ht_info->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
पूर्ण

/*
 *  create a new भव पूर्णांकerface with the given name and name assign type
 */
काष्ठा wireless_dev *mwअगरiex_add_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
					      स्थिर अक्षर *name,
					      अचिन्हित अक्षर name_assign_type,
					      क्रमागत nl80211_अगरtype type,
					      काष्ठा vअगर_params *params)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा net_device *dev;
	व्योम *mdev_priv;
	पूर्णांक ret;

	अगर (!adapter)
		वापस ERR_PTR(-EFAULT);

	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		अगर (adapter->curr_अगरace_comb.sta_पूर्णांकf ==
		    adapter->अगरace_limit.sta_पूर्णांकf) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cannot create multiple sta/adhoc ifaces\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		priv = mwअगरiex_get_unused_priv_by_bss_type(
						adapter, MWIFIEX_BSS_TYPE_STA);
		अगर (!priv) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "could not get free private struct\n");
			वापस ERR_PTR(-EFAULT);
		पूर्ण

		priv->wdev.wiphy = wiphy;
		priv->wdev.अगरtype = NL80211_IFTYPE_STATION;

		अगर (type == NL80211_IFTYPE_UNSPECIFIED)
			priv->bss_mode = NL80211_IFTYPE_STATION;
		अन्यथा
			priv->bss_mode = type;

		priv->bss_type = MWIFIEX_BSS_TYPE_STA;
		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = 0;
		priv->bss_role = MWIFIEX_BSS_ROLE_STA;

		अवरोध;
	हाल NL80211_IFTYPE_AP:
		अगर (adapter->curr_अगरace_comb.uap_पूर्णांकf ==
		    adapter->अगरace_limit.uap_पूर्णांकf) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cannot create multiple AP ifaces\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		priv = mwअगरiex_get_unused_priv_by_bss_type(
						adapter, MWIFIEX_BSS_TYPE_UAP);
		अगर (!priv) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "could not get free private struct\n");
			वापस ERR_PTR(-EFAULT);
		पूर्ण

		priv->wdev.wiphy = wiphy;
		priv->wdev.अगरtype = NL80211_IFTYPE_AP;

		priv->bss_type = MWIFIEX_BSS_TYPE_UAP;
		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = 0;
		priv->bss_role = MWIFIEX_BSS_ROLE_UAP;
		priv->bss_started = 0;
		priv->bss_mode = type;

		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (adapter->curr_अगरace_comb.p2p_पूर्णांकf ==
		    adapter->अगरace_limit.p2p_पूर्णांकf) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "cannot create multiple P2P ifaces\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		priv = mwअगरiex_get_unused_priv_by_bss_type(
						adapter, MWIFIEX_BSS_TYPE_P2P);
		अगर (!priv) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "could not get free private struct\n");
			वापस ERR_PTR(-EFAULT);
		पूर्ण

		priv->wdev.wiphy = wiphy;
		/* At start-up, wpa_supplicant tries to change the पूर्णांकerface
		 * to NL80211_IFTYPE_STATION अगर it is not managed mode.
		 */
		priv->wdev.अगरtype = NL80211_IFTYPE_P2P_CLIENT;
		priv->bss_mode = NL80211_IFTYPE_P2P_CLIENT;

		/* Setting bss_type to P2P tells firmware that this पूर्णांकerface
		 * is receiving P2P peers found during find phase and करोing
		 * action frame handshake.
		 */
		priv->bss_type = MWIFIEX_BSS_TYPE_P2P;

		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = MWIFIEX_BSS_ROLE_STA;
		priv->bss_role = MWIFIEX_BSS_ROLE_STA;
		priv->bss_started = 0;

		अगर (mwअगरiex_cfg80211_init_p2p_client(priv)) अणु
			स_रखो(&priv->wdev, 0, माप(priv->wdev));
			priv->wdev.अगरtype = NL80211_IFTYPE_UNSPECIFIED;
			वापस ERR_PTR(-EFAULT);
		पूर्ण

		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR, "type not supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	dev = alloc_netdev_mqs(माप(काष्ठा mwअगरiex_निजी *), name,
			       name_assign_type, ether_setup,
			       IEEE80211_NUM_ACS, 1);
	अगर (!dev) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "no memory available for netdevice\n");
		ret = -ENOMEM;
		जाओ err_alloc_netdev;
	पूर्ण

	mwअगरiex_init_priv_params(priv, dev);

	priv->netdev = dev;

	अगर (!adapter->mfg_mode) अणु
		mwअगरiex_set_mac_address(priv, dev, false, शून्य);

		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_SET_BSS_MODE,
				       HostCmd_ACT_GEN_SET, 0, शून्य, true);
		अगर (ret)
			जाओ err_set_bss_mode;

		ret = mwअगरiex_sta_init_cmd(priv, false, false);
		अगर (ret)
			जाओ err_sta_init;
	पूर्ण

	mwअगरiex_setup_ht_caps(&wiphy->bands[NL80211_BAND_2GHZ]->ht_cap, priv);
	अगर (adapter->is_hw_11ac_capable)
		mwअगरiex_setup_vht_caps(
			&wiphy->bands[NL80211_BAND_2GHZ]->vht_cap, priv);

	अगर (adapter->config_bands & BAND_A)
		mwअगरiex_setup_ht_caps(
			&wiphy->bands[NL80211_BAND_5GHZ]->ht_cap, priv);

	अगर ((adapter->config_bands & BAND_A) && adapter->is_hw_11ac_capable)
		mwअगरiex_setup_vht_caps(
			&wiphy->bands[NL80211_BAND_5GHZ]->vht_cap, priv);

	dev_net_set(dev, wiphy_net(wiphy));
	dev->ieee80211_ptr = &priv->wdev;
	dev->ieee80211_ptr->अगरtype = priv->bss_mode;
	SET_NETDEV_DEV(dev, wiphy_dev(wiphy));

	dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
	dev->watchकरोg_समयo = MWIFIEX_DEFAULT_WATCHDOG_TIMEOUT;
	dev->needed_headroom = MWIFIEX_MIN_DATA_HEADER_LEN;
	dev->ethtool_ops = &mwअगरiex_ethtool_ops;

	mdev_priv = netdev_priv(dev);
	*((अचिन्हित दीर्घ *) mdev_priv) = (अचिन्हित दीर्घ) priv;

	SET_NETDEV_DEV(dev, adapter->dev);

	priv->dfs_cac_workqueue = alloc_workqueue("MWIFIEX_DFS_CAC%s",
						  WQ_HIGHPRI |
						  WQ_MEM_RECLAIM |
						  WQ_UNBOUND, 1, name);
	अगर (!priv->dfs_cac_workqueue) अणु
		mwअगरiex_dbg(adapter, ERROR, "cannot alloc DFS CAC queue\n");
		ret = -ENOMEM;
		जाओ err_alloc_cac;
	पूर्ण

	INIT_DELAYED_WORK(&priv->dfs_cac_work, mwअगरiex_dfs_cac_work_queue);

	priv->dfs_chan_sw_workqueue = alloc_workqueue("MWIFIEX_DFS_CHSW%s",
						      WQ_HIGHPRI | WQ_UNBOUND |
						      WQ_MEM_RECLAIM, 1, name);
	अगर (!priv->dfs_chan_sw_workqueue) अणु
		mwअगरiex_dbg(adapter, ERROR, "cannot alloc DFS channel sw queue\n");
		ret = -ENOMEM;
		जाओ err_alloc_chsw;
	पूर्ण

	INIT_DELAYED_WORK(&priv->dfs_chan_sw_work,
			  mwअगरiex_dfs_chan_sw_work_queue);

	mutex_init(&priv->async_mutex);

	/* Register network device */
	अगर (cfg80211_रेजिस्टर_netdevice(dev)) अणु
		mwअगरiex_dbg(adapter, ERROR, "cannot register network device\n");
		ret = -EFAULT;
		जाओ err_reg_netdev;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "info: %s: Marvell 802.11 Adapter\n", dev->name);

#अगर_घोषित CONFIG_DEBUG_FS
	mwअगरiex_dev_debugfs_init(priv);
#पूर्ण_अगर

	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		adapter->curr_अगरace_comb.sta_पूर्णांकf++;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		adapter->curr_अगरace_comb.uap_पूर्णांकf++;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		adapter->curr_अगरace_comb.p2p_पूर्णांकf++;
		अवरोध;
	शेष:
		/* This should be dead code; checked above */
		mwअगरiex_dbg(adapter, ERROR, "type not supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &priv->wdev;

err_reg_netdev:
	destroy_workqueue(priv->dfs_chan_sw_workqueue);
	priv->dfs_chan_sw_workqueue = शून्य;
err_alloc_chsw:
	destroy_workqueue(priv->dfs_cac_workqueue);
	priv->dfs_cac_workqueue = शून्य;
err_alloc_cac:
	मुक्त_netdev(dev);
	priv->netdev = शून्य;
err_sta_init:
err_set_bss_mode:
err_alloc_netdev:
	स_रखो(&priv->wdev, 0, माप(priv->wdev));
	priv->wdev.अगरtype = NL80211_IFTYPE_UNSPECIFIED;
	priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_add_भव_पूर्णांकf);

/*
 * del_भव_पूर्णांकf: हटाओ the भव पूर्णांकerface determined by dev
 */
पूर्णांक mwअगरiex_del_भव_पूर्णांकf(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(wdev->netdev);
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा sk_buff *skb, *पंचांगp;

#अगर_घोषित CONFIG_DEBUG_FS
	mwअगरiex_dev_debugfs_हटाओ(priv);
#पूर्ण_अगर

	अगर (priv->sched_scanning)
		priv->sched_scanning = false;

	mwअगरiex_stop_net_dev_queue(priv->netdev, adapter);

	skb_queue_walk_safe(&priv->bypass_txq, skb, पंचांगp) अणु
		skb_unlink(skb, &priv->bypass_txq);
		mwअगरiex_ग_लिखो_data_complete(priv->adapter, skb, 0, -1);
	पूर्ण

	अगर (netअगर_carrier_ok(priv->netdev))
		netअगर_carrier_off(priv->netdev);

	अगर (wdev->netdev->reg_state == NETREG_REGISTERED)
		cfg80211_unरेजिस्टर_netdevice(wdev->netdev);

	अगर (priv->dfs_cac_workqueue) अणु
		flush_workqueue(priv->dfs_cac_workqueue);
		destroy_workqueue(priv->dfs_cac_workqueue);
		priv->dfs_cac_workqueue = शून्य;
	पूर्ण

	अगर (priv->dfs_chan_sw_workqueue) अणु
		flush_workqueue(priv->dfs_chan_sw_workqueue);
		destroy_workqueue(priv->dfs_chan_sw_workqueue);
		priv->dfs_chan_sw_workqueue = शून्य;
	पूर्ण
	/* Clear the priv in adapter */
	priv->netdev = शून्य;

	चयन (priv->bss_mode) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
		adapter->curr_अगरace_comb.sta_पूर्णांकf--;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		adapter->curr_अगरace_comb.uap_पूर्णांकf--;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
		adapter->curr_अगरace_comb.p2p_पूर्णांकf--;
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR,
			    "del_virtual_intf: type not supported\n");
		अवरोध;
	पूर्ण

	priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA ||
	    GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP)
		kमुक्त(priv->hist_data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_del_भव_पूर्णांकf);

अटल bool
mwअगरiex_is_pattern_supported(काष्ठा cfg80211_pkt_pattern *pat, s8 *byte_seq,
			     u8 max_byte_seq)
अणु
	पूर्णांक j, k, valid_byte_cnt = 0;
	bool करोnt_care_byte = false;

	क्रम (j = 0; j < DIV_ROUND_UP(pat->pattern_len, 8); j++) अणु
		क्रम (k = 0; k < 8; k++) अणु
			अगर (pat->mask[j] & 1 << k) अणु
				स_नकल(byte_seq + valid_byte_cnt,
				       &pat->pattern[j * 8 + k], 1);
				valid_byte_cnt++;
				अगर (करोnt_care_byte)
					वापस false;
			पूर्ण अन्यथा अणु
				अगर (valid_byte_cnt)
					करोnt_care_byte = true;
			पूर्ण

			/* wildcard bytes record as the offset
			 * beक्रमe the valid byte
			 */
			अगर (!valid_byte_cnt && !करोnt_care_byte)
				pat->pkt_offset++;

			अगर (valid_byte_cnt > max_byte_seq)
				वापस false;
		पूर्ण
	पूर्ण

	byte_seq[max_byte_seq] = valid_byte_cnt;

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम mwअगरiex_set_स्वतः_arp_mef_entry(काष्ठा mwअगरiex_निजी *priv,
					   काष्ठा mwअगरiex_mef_entry *mef_entry)
अणु
	पूर्णांक i, filt_num = 0, num_ipv4 = 0;
	काष्ठा in_device *in_dev;
	काष्ठा in_अगरaddr *अगरa;
	__be32 ips[MWIFIEX_MAX_SUPPORTED_IPADDR];
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	mef_entry->mode = MEF_MODE_HOST_SLEEP;
	mef_entry->action = MEF_ACTION_AUTO_ARP;

	/* Enable ARP offload feature */
	स_रखो(ips, 0, माप(ips));
	क्रम (i = 0; i < MWIFIEX_MAX_BSS_NUM; i++) अणु
		अगर (adapter->priv[i]->netdev) अणु
			in_dev = __in_dev_get_rtnl(adapter->priv[i]->netdev);
			अगर (!in_dev)
				जारी;
			अगरa = rtnl_dereference(in_dev->अगरa_list);
			अगर (!अगरa || !अगरa->अगरa_local)
				जारी;
			ips[i] = अगरa->अगरa_local;
			num_ipv4++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_ipv4; i++) अणु
		अगर (!ips[i])
			जारी;
		mef_entry->filter[filt_num].repeat = 1;
		स_नकल(mef_entry->filter[filt_num].byte_seq,
		       (u8 *)&ips[i], माप(ips[i]));
		mef_entry->filter[filt_num].
			byte_seq[MWIFIEX_MEF_MAX_BYTESEQ] =
			माप(ips[i]);
		mef_entry->filter[filt_num].offset = 46;
		mef_entry->filter[filt_num].filt_type = TYPE_EQ;
		अगर (filt_num) अणु
			mef_entry->filter[filt_num].filt_action =
				TYPE_OR;
		पूर्ण
		filt_num++;
	पूर्ण

	mef_entry->filter[filt_num].repeat = 1;
	mef_entry->filter[filt_num].byte_seq[0] = 0x08;
	mef_entry->filter[filt_num].byte_seq[1] = 0x06;
	mef_entry->filter[filt_num].byte_seq[MWIFIEX_MEF_MAX_BYTESEQ] = 2;
	mef_entry->filter[filt_num].offset = 20;
	mef_entry->filter[filt_num].filt_type = TYPE_EQ;
	mef_entry->filter[filt_num].filt_action = TYPE_AND;
पूर्ण

अटल पूर्णांक mwअगरiex_set_wowlan_mef_entry(काष्ठा mwअगरiex_निजी *priv,
					काष्ठा mwअगरiex_ds_mef_cfg *mef_cfg,
					काष्ठा mwअगरiex_mef_entry *mef_entry,
					काष्ठा cfg80211_wowlan *wowlan)
अणु
	पूर्णांक i, filt_num = 0, ret = 0;
	bool first_pat = true;
	u8 byte_seq[MWIFIEX_MEF_MAX_BYTESEQ + 1];
	अटल स्थिर u8 ipv4_mc_mac[] = अणु0x33, 0x33पूर्ण;
	अटल स्थिर u8 ipv6_mc_mac[] = अणु0x01, 0x00, 0x5eपूर्ण;

	mef_entry->mode = MEF_MODE_HOST_SLEEP;
	mef_entry->action = MEF_ACTION_ALLOW_AND_WAKEUP_HOST;

	क्रम (i = 0; i < wowlan->n_patterns; i++) अणु
		स_रखो(byte_seq, 0, माप(byte_seq));
		अगर (!mwअगरiex_is_pattern_supported(&wowlan->patterns[i],
					byte_seq,
					MWIFIEX_MEF_MAX_BYTESEQ)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Pattern not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!wowlan->patterns[i].pkt_offset) अणु
			अगर (!(byte_seq[0] & 0x01) &&
			    (byte_seq[MWIFIEX_MEF_MAX_BYTESEQ] == 1)) अणु
				mef_cfg->criteria |= MWIFIEX_CRITERIA_UNICAST;
				जारी;
			पूर्ण अन्यथा अगर (is_broadcast_ether_addr(byte_seq)) अणु
				mef_cfg->criteria |= MWIFIEX_CRITERIA_BROADCAST;
				जारी;
			पूर्ण अन्यथा अगर ((!स_भेद(byte_seq, ipv4_mc_mac, 2) &&
				    (byte_seq[MWIFIEX_MEF_MAX_BYTESEQ] == 2)) ||
				   (!स_भेद(byte_seq, ipv6_mc_mac, 3) &&
				    (byte_seq[MWIFIEX_MEF_MAX_BYTESEQ] == 3))) अणु
				mef_cfg->criteria |= MWIFIEX_CRITERIA_MULTICAST;
				जारी;
			पूर्ण
		पूर्ण
		mef_entry->filter[filt_num].repeat = 1;
		mef_entry->filter[filt_num].offset =
			wowlan->patterns[i].pkt_offset;
		स_नकल(mef_entry->filter[filt_num].byte_seq, byte_seq,
				माप(byte_seq));
		mef_entry->filter[filt_num].filt_type = TYPE_EQ;

		अगर (first_pat) अणु
			first_pat = false;
			mwअगरiex_dbg(priv->adapter, INFO, "Wake on patterns\n");
		पूर्ण अन्यथा अणु
			mef_entry->filter[filt_num].filt_action = TYPE_AND;
		पूर्ण

		filt_num++;
	पूर्ण

	अगर (wowlan->magic_pkt) अणु
		mef_cfg->criteria |= MWIFIEX_CRITERIA_UNICAST;
		mef_entry->filter[filt_num].repeat = 16;
		स_नकल(mef_entry->filter[filt_num].byte_seq, priv->curr_addr,
				ETH_ALEN);
		mef_entry->filter[filt_num].byte_seq[MWIFIEX_MEF_MAX_BYTESEQ] =
			ETH_ALEN;
		mef_entry->filter[filt_num].offset = 28;
		mef_entry->filter[filt_num].filt_type = TYPE_EQ;
		अगर (filt_num)
			mef_entry->filter[filt_num].filt_action = TYPE_OR;

		filt_num++;
		mef_entry->filter[filt_num].repeat = 16;
		स_नकल(mef_entry->filter[filt_num].byte_seq, priv->curr_addr,
				ETH_ALEN);
		mef_entry->filter[filt_num].byte_seq[MWIFIEX_MEF_MAX_BYTESEQ] =
			ETH_ALEN;
		mef_entry->filter[filt_num].offset = 56;
		mef_entry->filter[filt_num].filt_type = TYPE_EQ;
		mef_entry->filter[filt_num].filt_action = TYPE_OR;
		mwअगरiex_dbg(priv->adapter, INFO, "Wake on magic packet\n");
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mwअगरiex_set_mef_filter(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा cfg80211_wowlan *wowlan)
अणु
	पूर्णांक ret = 0, num_entries = 1;
	काष्ठा mwअगरiex_ds_mef_cfg mef_cfg;
	काष्ठा mwअगरiex_mef_entry *mef_entry;

	अगर (wowlan->n_patterns || wowlan->magic_pkt)
		num_entries++;

	mef_entry = kसुस्मृति(num_entries, माप(*mef_entry), GFP_KERNEL);
	अगर (!mef_entry)
		वापस -ENOMEM;

	स_रखो(&mef_cfg, 0, माप(mef_cfg));
	mef_cfg.criteria |= MWIFIEX_CRITERIA_BROADCAST |
		MWIFIEX_CRITERIA_UNICAST;
	mef_cfg.num_entries = num_entries;
	mef_cfg.mef_entry = mef_entry;

	mwअगरiex_set_स्वतः_arp_mef_entry(priv, &mef_entry[0]);

	अगर (wowlan->n_patterns || wowlan->magic_pkt) अणु
		ret = mwअगरiex_set_wowlan_mef_entry(priv, &mef_cfg,
						   &mef_entry[1], wowlan);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (!mef_cfg.criteria)
		mef_cfg.criteria = MWIFIEX_CRITERIA_BROADCAST |
			MWIFIEX_CRITERIA_UNICAST |
			MWIFIEX_CRITERIA_MULTICAST;

	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_MEF_CFG,
			HostCmd_ACT_GEN_SET, 0,
			&mef_cfg, true);

err:
	kमुक्त(mef_entry);
	वापस ret;
पूर्ण

अटल पूर्णांक mwअगरiex_cfg80211_suspend(काष्ठा wiphy *wiphy,
				    काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_ds_hs_cfg hs_cfg;
	पूर्णांक i, ret = 0, retry_num = 10;
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_निजी *sta_priv =
			mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA);

	sta_priv->scan_पातing = true;
	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		mwअगरiex_पात_cac(priv);
	पूर्ण

	mwअगरiex_cancel_all_pending_cmd(adapter);

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		अगर (priv && priv->netdev)
			netअगर_device_detach(priv->netdev);
	पूर्ण

	क्रम (i = 0; i < retry_num; i++) अणु
		अगर (!mwअगरiex_wmm_lists_empty(adapter) ||
		    !mwअगरiex_bypass_txlist_empty(adapter) ||
		    !skb_queue_empty(&adapter->tx_data_q))
			usleep_range(10000, 15000);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (!wowlan) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "None of the WOWLAN triggers enabled\n");
		ret = 0;
		जाओ करोne;
	पूर्ण

	अगर (!sta_priv->media_connected && !wowlan->nd_config) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Can not configure WOWLAN in disconnected state\n");
		ret = 0;
		जाओ करोne;
	पूर्ण

	ret = mwअगरiex_set_mef_filter(sta_priv, wowlan);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR, "Failed to set MEF filter\n");
		जाओ करोne;
	पूर्ण

	स_रखो(&hs_cfg, 0, माप(hs_cfg));
	hs_cfg.conditions = le32_to_cpu(adapter->hs_cfg.conditions);

	अगर (wowlan->nd_config) अणु
		mwअगरiex_dbg(adapter, INFO, "Wake on net detect\n");
		hs_cfg.conditions |= HS_CFG_COND_MAC_EVENT;
		mwअगरiex_cfg80211_sched_scan_start(wiphy, sta_priv->netdev,
						  wowlan->nd_config);
	पूर्ण

	अगर (wowlan->disconnect) अणु
		hs_cfg.conditions |= HS_CFG_COND_MAC_EVENT;
		mwअगरiex_dbg(sta_priv->adapter, INFO, "Wake on device disconnect\n");
	पूर्ण

	hs_cfg.is_invoke_hostcmd = false;
	hs_cfg.gpio = adapter->hs_cfg.gpio;
	hs_cfg.gap = adapter->hs_cfg.gap;
	ret = mwअगरiex_set_hs_params(sta_priv, HostCmd_ACT_GEN_SET,
				    MWIFIEX_SYNC_CMD, &hs_cfg);
	अगर (ret)
		mwअगरiex_dbg(adapter, ERROR, "Failed to set HS params\n");

करोne:
	sta_priv->scan_पातing = false;
	वापस ret;
पूर्ण

अटल पूर्णांक mwअगरiex_cfg80211_resume(काष्ठा wiphy *wiphy)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_ds_wakeup_reason wakeup_reason;
	काष्ठा cfg80211_wowlan_wakeup wakeup_report;
	पूर्णांक i;
	bool report_wakeup_reason = true;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		अगर (priv && priv->netdev)
			netअगर_device_attach(priv->netdev);
	पूर्ण

	अगर (!wiphy->wowlan_config)
		जाओ करोne;

	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA);
	mwअगरiex_get_wakeup_reason(priv, HostCmd_ACT_GEN_GET, MWIFIEX_SYNC_CMD,
				  &wakeup_reason);
	स_रखो(&wakeup_report, 0, माप(काष्ठा cfg80211_wowlan_wakeup));

	wakeup_report.pattern_idx = -1;

	चयन (wakeup_reason.hs_wakeup_reason) अणु
	हाल NO_HSWAKEUP_REASON:
		अवरोध;
	हाल BCAST_DATA_MATCHED:
		अवरोध;
	हाल MCAST_DATA_MATCHED:
		अवरोध;
	हाल UCAST_DATA_MATCHED:
		अवरोध;
	हाल MASKTABLE_EVENT_MATCHED:
		अवरोध;
	हाल NON_MASKABLE_EVENT_MATCHED:
		अगर (wiphy->wowlan_config->disconnect)
			wakeup_report.disconnect = true;
		अगर (wiphy->wowlan_config->nd_config)
			wakeup_report.net_detect = adapter->nd_info;
		अवरोध;
	हाल NON_MASKABLE_CONDITION_MATCHED:
		अवरोध;
	हाल MAGIC_PATTERN_MATCHED:
		अगर (wiphy->wowlan_config->magic_pkt)
			wakeup_report.magic_pkt = true;
		अगर (wiphy->wowlan_config->n_patterns)
			wakeup_report.pattern_idx = 1;
		अवरोध;
	हाल GTK_REKEY_FAILURE:
		अगर (wiphy->wowlan_config->gtk_rekey_failure)
			wakeup_report.gtk_rekey_failure = true;
		अवरोध;
	शेष:
		report_wakeup_reason = false;
		अवरोध;
	पूर्ण

	अगर (report_wakeup_reason)
		cfg80211_report_wowlan_wakeup(&priv->wdev, &wakeup_report,
					      GFP_KERNEL);

करोne:
	अगर (adapter->nd_info) अणु
		क्रम (i = 0 ; i < adapter->nd_info->n_matches ; i++)
			kमुक्त(adapter->nd_info->matches[i]);
		kमुक्त(adapter->nd_info);
		adapter->nd_info = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_cfg80211_set_wakeup(काष्ठा wiphy *wiphy,
				       bool enabled)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);

	device_set_wakeup_enable(adapter->dev, enabled);
पूर्ण

अटल पूर्णांक mwअगरiex_set_rekey_data(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	अगर (!ISSUPP_FIRMWARE_SUPPLICANT(priv->adapter->fw_cap_info))
		वापस -EOPNOTSUPP;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG,
				HostCmd_ACT_GEN_SET, 0, data, true);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक mwअगरiex_get_coalesce_pkt_type(u8 *byte_seq)
अणु
	अटल स्थिर u8 ipv4_mc_mac[] = अणु0x33, 0x33पूर्ण;
	अटल स्थिर u8 ipv6_mc_mac[] = अणु0x01, 0x00, 0x5eपूर्ण;
	अटल स्थिर u8 bc_mac[] = अणु0xff, 0xff, 0xff, 0xffपूर्ण;

	अगर ((byte_seq[0] & 0x01) &&
	    (byte_seq[MWIFIEX_COALESCE_MAX_BYTESEQ] == 1))
		वापस PACKET_TYPE_UNICAST;
	अन्यथा अगर (!स_भेद(byte_seq, bc_mac, 4))
		वापस PACKET_TYPE_BROADCAST;
	अन्यथा अगर ((!स_भेद(byte_seq, ipv4_mc_mac, 2) &&
		  byte_seq[MWIFIEX_COALESCE_MAX_BYTESEQ] == 2) ||
		 (!स_भेद(byte_seq, ipv6_mc_mac, 3) &&
		  byte_seq[MWIFIEX_COALESCE_MAX_BYTESEQ] == 3))
		वापस PACKET_TYPE_MULTICAST;

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_fill_coalesce_rule_info(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा cfg80211_coalesce_rules *crule,
				काष्ठा mwअगरiex_coalesce_rule *mrule)
अणु
	u8 byte_seq[MWIFIEX_COALESCE_MAX_BYTESEQ + 1];
	काष्ठा filt_field_param *param;
	पूर्णांक i;

	mrule->max_coalescing_delay = crule->delay;

	param = mrule->params;

	क्रम (i = 0; i < crule->n_patterns; i++) अणु
		स_रखो(byte_seq, 0, माप(byte_seq));
		अगर (!mwअगरiex_is_pattern_supported(&crule->patterns[i],
						  byte_seq,
						MWIFIEX_COALESCE_MAX_BYTESEQ)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Pattern not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!crule->patterns[i].pkt_offset) अणु
			u8 pkt_type;

			pkt_type = mwअगरiex_get_coalesce_pkt_type(byte_seq);
			अगर (pkt_type && mrule->pkt_type) अणु
				mwअगरiex_dbg(priv->adapter, ERROR,
					    "Multiple packet types not allowed\n");
				वापस -EOPNOTSUPP;
			पूर्ण अन्यथा अगर (pkt_type) अणु
				mrule->pkt_type = pkt_type;
				जारी;
			पूर्ण
		पूर्ण

		अगर (crule->condition == NL80211_COALESCE_CONDITION_MATCH)
			param->operation = RECV_FILTER_MATCH_TYPE_EQ;
		अन्यथा
			param->operation = RECV_FILTER_MATCH_TYPE_NE;

		param->opeअक्रम_len = byte_seq[MWIFIEX_COALESCE_MAX_BYTESEQ];
		स_नकल(param->opeअक्रम_byte_stream, byte_seq,
		       param->opeअक्रम_len);
		param->offset = crule->patterns[i].pkt_offset;
		param++;

		mrule->num_of_fields++;
	पूर्ण

	अगर (!mrule->pkt_type) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Packet type can not be determined\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_cfg80211_set_coalesce(काष्ठा wiphy *wiphy,
					 काष्ठा cfg80211_coalesce *coalesce)
अणु
	काष्ठा mwअगरiex_adapter *adapter = mwअगरiex_cfg80211_get_adapter(wiphy);
	पूर्णांक i, ret;
	काष्ठा mwअगरiex_ds_coalesce_cfg coalesce_cfg;
	काष्ठा mwअगरiex_निजी *priv =
			mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA);

	स_रखो(&coalesce_cfg, 0, माप(coalesce_cfg));
	अगर (!coalesce) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "Disable coalesce and reset all previous rules\n");
		वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_COALESCE_CFG,
					HostCmd_ACT_GEN_SET, 0,
					&coalesce_cfg, true);
	पूर्ण

	coalesce_cfg.num_of_rules = coalesce->n_rules;
	क्रम (i = 0; i < coalesce->n_rules; i++) अणु
		ret = mwअगरiex_fill_coalesce_rule_info(priv, &coalesce->rules[i],
						      &coalesce_cfg.rule[i]);
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Recheck the patterns provided for rule %d\n",
				i + 1);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_COALESCE_CFG,
				HostCmd_ACT_GEN_SET, 0, &coalesce_cfg, true);
पूर्ण

/* cfg80211 ops handler क्रम tdls_mgmt.
 * Function prepares TDLS action frame packets and क्रमwards them to FW
 */
अटल पूर्णांक
mwअगरiex_cfg80211_tdls_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   स्थिर u8 *peer, u8 action_code, u8 dialog_token,
			   u16 status_code, u32 peer_capability,
			   bool initiator, स्थिर u8 *extra_ies,
			   माप_प्रकार extra_ies_len)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	पूर्णांक ret;

	अगर (!(wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS))
		वापस -EOPNOTSUPP;

	/* make sure we are in station mode and connected */
	अगर (!(priv->bss_type == MWIFIEX_BSS_TYPE_STA && priv->media_connected))
		वापस -EOPNOTSUPP;

	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
		mwअगरiex_dbg(priv->adapter, MSG,
			    "Send TDLS Setup Request to %pM status_code=%d\n",
			    peer, status_code);
		mwअगरiex_add_स्वतः_tdls_peer(priv, peer);
		ret = mwअगरiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		अवरोध;
	हाल WLAN_TDLS_SETUP_RESPONSE:
		mwअगरiex_add_स्वतः_tdls_peer(priv, peer);
		mwअगरiex_dbg(priv->adapter, MSG,
			    "Send TDLS Setup Response to %pM status_code=%d\n",
			    peer, status_code);
		ret = mwअगरiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		अवरोध;
	हाल WLAN_TDLS_SETUP_CONFIRM:
		mwअगरiex_dbg(priv->adapter, MSG,
			    "Send TDLS Confirm to %pM status_code=%d\n", peer,
			    status_code);
		ret = mwअगरiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		अवरोध;
	हाल WLAN_TDLS_TEARDOWN:
		mwअगरiex_dbg(priv->adapter, MSG,
			    "Send TDLS Tear down to %pM\n", peer);
		ret = mwअगरiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		अवरोध;
	हाल WLAN_TDLS_DISCOVERY_REQUEST:
		mwअगरiex_dbg(priv->adapter, MSG,
			    "Send TDLS Discovery Request to %pM\n", peer);
		ret = mwअगरiex_send_tdls_data_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		अवरोध;
	हाल WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		mwअगरiex_dbg(priv->adapter, MSG,
			    "Send TDLS Discovery Response to %pM\n", peer);
		ret = mwअगरiex_send_tdls_action_frame(priv, peer, action_code,
						   dialog_token, status_code,
						   extra_ies, extra_ies_len);
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Unknown TDLS mgmt/action frame %pM\n", peer);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_tdls_oper(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   स्थिर u8 *peer, क्रमागत nl80211_tdls_operation action)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	अगर (!(wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS) ||
	    !(wiphy->flags & WIPHY_FLAG_TDLS_EXTERNAL_SETUP))
		वापस -EOPNOTSUPP;

	/* make sure we are in station mode and connected */
	अगर (!(priv->bss_type == MWIFIEX_BSS_TYPE_STA && priv->media_connected))
		वापस -EOPNOTSUPP;

	mwअगरiex_dbg(priv->adapter, MSG,
		    "TDLS peer=%pM, oper=%d\n", peer, action);

	चयन (action) अणु
	हाल NL80211_TDLS_ENABLE_LINK:
		action = MWIFIEX_TDLS_ENABLE_LINK;
		अवरोध;
	हाल NL80211_TDLS_DISABLE_LINK:
		action = MWIFIEX_TDLS_DISABLE_LINK;
		अवरोध;
	हाल NL80211_TDLS_TEARDOWN:
		/* shouldn't happen!*/
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "tdls_oper: teardown from driver not supported\n");
		वापस -EINVAL;
	हाल NL80211_TDLS_SETUP:
		/* shouldn't happen!*/
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "tdls_oper: setup from driver not supported\n");
		वापस -EINVAL;
	हाल NL80211_TDLS_DISCOVERY_REQ:
		/* shouldn't happen!*/
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "tdls_oper: discovery from driver not supported\n");
		वापस -EINVAL;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "tdls_oper: operation not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस mwअगरiex_tdls_oper(priv, peer, action);
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_tdls_chan_चयन(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  स्थिर u8 *addr, u8 oper_class,
				  काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	u16 chan;
	u8 second_chan_offset, band;
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	spin_lock_bh(&priv->sta_list_spinlock);
	sta_ptr = mwअगरiex_get_sta_entry(priv, addr);
	अगर (!sta_ptr) अणु
		spin_unlock_bh(&priv->sta_list_spinlock);
		wiphy_err(wiphy, "%s: Invalid TDLS peer %pM\n",
			  __func__, addr);
		वापस -ENOENT;
	पूर्ण

	अगर (!(sta_ptr->tdls_cap.extcap.ext_capab[3] &
	      WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH)) अणु
		spin_unlock_bh(&priv->sta_list_spinlock);
		wiphy_err(wiphy, "%pM do not support tdls cs\n", addr);
		वापस -ENOENT;
	पूर्ण

	अगर (sta_ptr->tdls_status == TDLS_CHAN_SWITCHING ||
	    sta_ptr->tdls_status == TDLS_IN_OFF_CHAN) अणु
		spin_unlock_bh(&priv->sta_list_spinlock);
		wiphy_err(wiphy, "channel switch is running, abort request\n");
		वापस -EALREADY;
	पूर्ण
	spin_unlock_bh(&priv->sta_list_spinlock);

	chan = chandef->chan->hw_value;
	second_chan_offset = mwअगरiex_get_sec_chan_offset(chan);
	band = chandef->chan->band;
	mwअगरiex_start_tdls_cs(priv, addr, chan, second_chan_offset, band);

	वापस 0;
पूर्ण

अटल व्योम
mwअगरiex_cfg80211_tdls_cancel_chan_चयन(काष्ठा wiphy *wiphy,
					 काष्ठा net_device *dev,
					 स्थिर u8 *addr)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	spin_lock_bh(&priv->sta_list_spinlock);
	sta_ptr = mwअगरiex_get_sta_entry(priv, addr);
	अगर (!sta_ptr) अणु
		spin_unlock_bh(&priv->sta_list_spinlock);
		wiphy_err(wiphy, "%s: Invalid TDLS peer %pM\n",
			  __func__, addr);
	पूर्ण अन्यथा अगर (!(sta_ptr->tdls_status == TDLS_CHAN_SWITCHING ||
		     sta_ptr->tdls_status == TDLS_IN_BASE_CHAN ||
		     sta_ptr->tdls_status == TDLS_IN_OFF_CHAN)) अणु
		spin_unlock_bh(&priv->sta_list_spinlock);
		wiphy_err(wiphy, "tdls chan switch not initialize by %pM\n",
			  addr);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&priv->sta_list_spinlock);
		mwअगरiex_stop_tdls_cs(priv, addr);
	पूर्ण
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_add_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     स्थिर u8 *mac, काष्ठा station_parameters *params)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	अगर (!(params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER)))
		वापस -EOPNOTSUPP;

	/* make sure we are in station mode and connected */
	अगर ((priv->bss_type != MWIFIEX_BSS_TYPE_STA) || !priv->media_connected)
		वापस -EOPNOTSUPP;

	वापस mwअगरiex_tdls_oper(priv, mac, MWIFIEX_TDLS_CREATE_LINK);
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_channel_चयन(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				काष्ठा cfg80211_csa_settings *params)
अणु
	काष्ठा ieee_types_header *chsw_ie;
	काष्ठा ieee80211_channel_sw_ie *channel_sw;
	पूर्णांक chsw_msec;
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	अगर (priv->adapter->scan_processing) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "radar detection: scan in process...\n");
		वापस -EBUSY;
	पूर्ण

	अगर (priv->wdev.cac_started)
		वापस -EBUSY;

	अगर (cfg80211_chandef_identical(&params->chandef,
				       &priv->dfs_chandef))
		वापस -EINVAL;

	chsw_ie = (व्योम *)cfg80211_find_ie(WLAN_EID_CHANNEL_SWITCH,
					   params->beacon_csa.tail,
					   params->beacon_csa.tail_len);
	अगर (!chsw_ie) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Could not parse channel switch announcement IE\n");
		वापस -EINVAL;
	पूर्ण

	channel_sw = (व्योम *)(chsw_ie + 1);
	अगर (channel_sw->mode) अणु
		अगर (netअगर_carrier_ok(priv->netdev))
			netअगर_carrier_off(priv->netdev);
		mwअगरiex_stop_net_dev_queue(priv->netdev, priv->adapter);
	पूर्ण

	अगर (mwअगरiex_del_mgmt_ies(priv))
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to delete mgmt IEs!\n");

	अगर (mwअगरiex_set_mgmt_ies(priv, &params->beacon_csa)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: setting mgmt ies failed\n", __func__);
		वापस -EFAULT;
	पूर्ण

	स_नकल(&priv->dfs_chandef, &params->chandef, माप(priv->dfs_chandef));
	स_नकल(&priv->beacon_after, &params->beacon_after,
	       माप(priv->beacon_after));

	chsw_msec = max(channel_sw->count * priv->bss_cfg.beacon_period, 100);
	queue_delayed_work(priv->dfs_chan_sw_workqueue, &priv->dfs_chan_sw_work,
			   msecs_to_jअगरfies(chsw_msec));
	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_cfg80211_get_channel(काष्ठा wiphy *wiphy,
					काष्ठा wireless_dev *wdev,
					काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(wdev->netdev);
	काष्ठा mwअगरiex_bssdescriptor *curr_bss;
	काष्ठा ieee80211_channel *chan;
	क्रमागत nl80211_channel_type chan_type;
	क्रमागत nl80211_band band;
	पूर्णांक freq;
	पूर्णांक ret = -ENODATA;

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP &&
	    cfg80211_chandef_valid(&priv->bss_chandef)) अणु
		*chandef = priv->bss_chandef;
		ret = 0;
	पूर्ण अन्यथा अगर (priv->media_connected) अणु
		curr_bss = &priv->curr_bss_params.bss_descriptor;
		band = mwअगरiex_band_to_radio_type(priv->curr_bss_params.band);
		freq = ieee80211_channel_to_frequency(curr_bss->channel, band);
		chan = ieee80211_get_channel(wiphy, freq);

		अगर (priv->ht_param_present) अणु
			chan_type = mwअगरiex_get_chan_type(priv);
			cfg80211_chandef_create(chandef, chan, chan_type);
		पूर्ण अन्यथा अणु
			cfg80211_chandef_create(chandef, chan,
						NL80211_CHAN_NO_HT);
		पूर्ण
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE

क्रमागत mwअगरiex_पंचांग_attr अणु
	__MWIFIEX_TM_ATTR_INVALID	= 0,
	MWIFIEX_TM_ATTR_CMD		= 1,
	MWIFIEX_TM_ATTR_DATA		= 2,

	/* keep last */
	__MWIFIEX_TM_ATTR_AFTER_LAST,
	MWIFIEX_TM_ATTR_MAX		= __MWIFIEX_TM_ATTR_AFTER_LAST - 1,
पूर्ण;

अटल स्थिर काष्ठा nla_policy mwअगरiex_पंचांग_policy[MWIFIEX_TM_ATTR_MAX + 1] = अणु
	[MWIFIEX_TM_ATTR_CMD]		= अणु .type = NLA_U32 पूर्ण,
	[MWIFIEX_TM_ATTR_DATA]		= अणु .type = NLA_BINARY,
					    .len = MWIFIEX_SIZE_OF_CMD_BUFFER पूर्ण,
पूर्ण;

क्रमागत mwअगरiex_पंचांग_command अणु
	MWIFIEX_TM_CMD_HOSTCMD	= 0,
पूर्ण;

अटल पूर्णांक mwअगरiex_पंचांग_cmd(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			  व्योम *data, पूर्णांक len)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(wdev->netdev);
	काष्ठा mwअगरiex_ds_misc_cmd *hostcmd;
	काष्ठा nlattr *tb[MWIFIEX_TM_ATTR_MAX + 1];
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (!priv)
		वापस -EINVAL;

	err = nla_parse_deprecated(tb, MWIFIEX_TM_ATTR_MAX, data, len,
				   mwअगरiex_पंचांग_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[MWIFIEX_TM_ATTR_CMD])
		वापस -EINVAL;

	चयन (nla_get_u32(tb[MWIFIEX_TM_ATTR_CMD])) अणु
	हाल MWIFIEX_TM_CMD_HOSTCMD:
		अगर (!tb[MWIFIEX_TM_ATTR_DATA])
			वापस -EINVAL;

		hostcmd = kzalloc(माप(*hostcmd), GFP_KERNEL);
		अगर (!hostcmd)
			वापस -ENOMEM;

		hostcmd->len = nla_len(tb[MWIFIEX_TM_ATTR_DATA]);
		स_नकल(hostcmd->cmd, nla_data(tb[MWIFIEX_TM_ATTR_DATA]),
		       hostcmd->len);

		अगर (mwअगरiex_send_cmd(priv, 0, 0, 0, hostcmd, true)) अणु
			dev_err(priv->adapter->dev, "Failed to process hostcmd\n");
			kमुक्त(hostcmd);
			वापस -EFAULT;
		पूर्ण

		/* process hostcmd response*/
		skb = cfg80211_tesपंचांगode_alloc_reply_skb(wiphy, hostcmd->len);
		अगर (!skb) अणु
			kमुक्त(hostcmd);
			वापस -ENOMEM;
		पूर्ण
		err = nla_put(skb, MWIFIEX_TM_ATTR_DATA,
			      hostcmd->len, hostcmd->cmd);
		अगर (err) अणु
			kमुक्त(hostcmd);
			kमुक्त_skb(skb);
			वापस -EMSGSIZE;
		पूर्ण

		err = cfg80211_tesपंचांगode_reply(skb);
		kमुक्त(hostcmd);
		वापस err;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
mwअगरiex_cfg80211_start_radar_detection(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *dev,
				       काष्ठा cfg80211_chan_def *chandef,
				       u32 cac_समय_ms)
अणु
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);
	काष्ठा mwअगरiex_radar_params radar_params;

	अगर (priv->adapter->scan_processing) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "radar detection: scan already in process...\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!mwअगरiex_is_11h_active(priv)) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "Enable 11h extensions in FW\n");
		अगर (mwअगरiex_11h_activate(priv, true)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Failed to activate 11h extensions!!");
			वापस -1;
		पूर्ण
		priv->state_11h.is_11h_active = true;
	पूर्ण

	स_रखो(&radar_params, 0, माप(काष्ठा mwअगरiex_radar_params));
	radar_params.chandef = chandef;
	radar_params.cac_समय_ms = cac_समय_ms;

	स_नकल(&priv->dfs_chandef, chandef, माप(priv->dfs_chandef));

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_CHAN_REPORT_REQUEST,
			     HostCmd_ACT_GEN_SET, 0, &radar_params, true))
		वापस -1;

	queue_delayed_work(priv->dfs_cac_workqueue, &priv->dfs_cac_work,
			   msecs_to_jअगरfies(cac_समय_ms));
	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cfg80211_change_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				स्थिर u8 *mac,
				काष्ठा station_parameters *params)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_निजी *priv = mwअगरiex_netdev_get_priv(dev);

	/* we support change_station handler only क्रम TDLS peers*/
	अगर (!(params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER)))
		वापस -EOPNOTSUPP;

	/* make sure we are in station mode and connected */
	अगर ((priv->bss_type != MWIFIEX_BSS_TYPE_STA) || !priv->media_connected)
		वापस -EOPNOTSUPP;

	priv->sta_params = params;

	ret = mwअगरiex_tdls_oper(priv, mac, MWIFIEX_TDLS_CONFIG_LINK);
	priv->sta_params = शून्य;

	वापस ret;
पूर्ण

/* station cfg80211 operations */
अटल काष्ठा cfg80211_ops mwअगरiex_cfg80211_ops = अणु
	.add_भव_पूर्णांकf = mwअगरiex_add_भव_पूर्णांकf,
	.del_भव_पूर्णांकf = mwअगरiex_del_भव_पूर्णांकf,
	.change_भव_पूर्णांकf = mwअगरiex_cfg80211_change_भव_पूर्णांकf,
	.scan = mwअगरiex_cfg80211_scan,
	.connect = mwअगरiex_cfg80211_connect,
	.disconnect = mwअगरiex_cfg80211_disconnect,
	.get_station = mwअगरiex_cfg80211_get_station,
	.dump_station = mwअगरiex_cfg80211_dump_station,
	.dump_survey = mwअगरiex_cfg80211_dump_survey,
	.set_wiphy_params = mwअगरiex_cfg80211_set_wiphy_params,
	.join_ibss = mwअगरiex_cfg80211_join_ibss,
	.leave_ibss = mwअगरiex_cfg80211_leave_ibss,
	.add_key = mwअगरiex_cfg80211_add_key,
	.del_key = mwअगरiex_cfg80211_del_key,
	.set_शेष_mgmt_key = mwअगरiex_cfg80211_set_शेष_mgmt_key,
	.mgmt_tx = mwअगरiex_cfg80211_mgmt_tx,
	.update_mgmt_frame_registrations =
		mwअगरiex_cfg80211_update_mgmt_frame_registrations,
	.reमुख्य_on_channel = mwअगरiex_cfg80211_reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel = mwअगरiex_cfg80211_cancel_reमुख्य_on_channel,
	.set_शेष_key = mwअगरiex_cfg80211_set_शेष_key,
	.set_घातer_mgmt = mwअगरiex_cfg80211_set_घातer_mgmt,
	.set_tx_घातer = mwअगरiex_cfg80211_set_tx_घातer,
	.get_tx_घातer = mwअगरiex_cfg80211_get_tx_घातer,
	.set_bitrate_mask = mwअगरiex_cfg80211_set_bitrate_mask,
	.start_ap = mwअगरiex_cfg80211_start_ap,
	.stop_ap = mwअगरiex_cfg80211_stop_ap,
	.change_beacon = mwअगरiex_cfg80211_change_beacon,
	.set_cqm_rssi_config = mwअगरiex_cfg80211_set_cqm_rssi_config,
	.set_antenna = mwअगरiex_cfg80211_set_antenna,
	.get_antenna = mwअगरiex_cfg80211_get_antenna,
	.del_station = mwअगरiex_cfg80211_del_station,
	.sched_scan_start = mwअगरiex_cfg80211_sched_scan_start,
	.sched_scan_stop = mwअगरiex_cfg80211_sched_scan_stop,
#अगर_घोषित CONFIG_PM
	.suspend = mwअगरiex_cfg80211_suspend,
	.resume = mwअगरiex_cfg80211_resume,
	.set_wakeup = mwअगरiex_cfg80211_set_wakeup,
	.set_rekey_data = mwअगरiex_set_rekey_data,
#पूर्ण_अगर
	.set_coalesce = mwअगरiex_cfg80211_set_coalesce,
	.tdls_mgmt = mwअगरiex_cfg80211_tdls_mgmt,
	.tdls_oper = mwअगरiex_cfg80211_tdls_oper,
	.tdls_channel_चयन = mwअगरiex_cfg80211_tdls_chan_चयन,
	.tdls_cancel_channel_चयन = mwअगरiex_cfg80211_tdls_cancel_chan_चयन,
	.add_station = mwअगरiex_cfg80211_add_station,
	.change_station = mwअगरiex_cfg80211_change_station,
	CFG80211_TESTMODE_CMD(mwअगरiex_पंचांग_cmd)
	.get_channel = mwअगरiex_cfg80211_get_channel,
	.start_radar_detection = mwअगरiex_cfg80211_start_radar_detection,
	.channel_चयन = mwअगरiex_cfg80211_channel_चयन,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा wiphy_wowlan_support mwअगरiex_wowlan_support = अणु
	.flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_DISCONNECT |
		WIPHY_WOWLAN_NET_DETECT | WIPHY_WOWLAN_SUPPORTS_GTK_REKEY |
		WIPHY_WOWLAN_GTK_REKEY_FAILURE,
	.n_patterns = MWIFIEX_MEF_MAX_FILTERS,
	.pattern_min_len = 1,
	.pattern_max_len = MWIFIEX_MAX_PATTERN_LEN,
	.max_pkt_offset = MWIFIEX_MAX_OFFSET_LEN,
	.max_nd_match_sets = MWIFIEX_MAX_ND_MATCH_SETS,
पूर्ण;

अटल स्थिर काष्ठा wiphy_wowlan_support mwअगरiex_wowlan_support_no_gtk = अणु
	.flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_DISCONNECT |
		 WIPHY_WOWLAN_NET_DETECT,
	.n_patterns = MWIFIEX_MEF_MAX_FILTERS,
	.pattern_min_len = 1,
	.pattern_max_len = MWIFIEX_MAX_PATTERN_LEN,
	.max_pkt_offset = MWIFIEX_MAX_OFFSET_LEN,
	.max_nd_match_sets = MWIFIEX_MAX_ND_MATCH_SETS,
पूर्ण;
#पूर्ण_अगर

अटल bool mwअगरiex_is_valid_alpha2(स्थिर अक्षर *alpha2)
अणु
	अगर (!alpha2 || म_माप(alpha2) != 2)
		वापस false;

	अगर (है_अक्षर(alpha2[0]) && है_अक्षर(alpha2[1]))
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा wiphy_coalesce_support mwअगरiex_coalesce_support = अणु
	.n_rules = MWIFIEX_COALESCE_MAX_RULES,
	.max_delay = MWIFIEX_MAX_COALESCING_DELAY,
	.n_patterns = MWIFIEX_COALESCE_MAX_FILTERS,
	.pattern_min_len = 1,
	.pattern_max_len = MWIFIEX_MAX_PATTERN_LEN,
	.max_pkt_offset = MWIFIEX_MAX_OFFSET_LEN,
पूर्ण;

पूर्णांक mwअगरiex_init_channel_scan_gap(काष्ठा mwअगरiex_adapter *adapter)
अणु
	u32 n_channels_bg, n_channels_a = 0;

	n_channels_bg = mwअगरiex_band_2ghz.n_channels;

	अगर (adapter->config_bands & BAND_A)
		n_channels_a = mwअगरiex_band_5ghz.n_channels;

	/* allocate twice the number total channels, since the driver issues an
	 * additional active scan request क्रम hidden SSIDs on passive channels.
	 */
	adapter->num_in_chan_stats = 2 * (n_channels_bg + n_channels_a);
	adapter->chan_stats = vदो_स्मृति(array_size(माप(*adapter->chan_stats),
						 adapter->num_in_chan_stats));

	अगर (!adapter->chan_stats)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/*
 * This function रेजिस्टरs the device with CFG802.11 subप्रणाली.
 *
 * The function creates the wireless device/wiphy, populates it with
 * शेष parameters and handler function poपूर्णांकers, and finally
 * रेजिस्टरs the device.
 */

पूर्णांक mwअगरiex_रेजिस्टर_cfg80211(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret;
	व्योम *wdev_priv;
	काष्ठा wiphy *wiphy;
	काष्ठा mwअगरiex_निजी *priv = adapter->priv[MWIFIEX_BSS_TYPE_STA];
	u8 *country_code;
	u32 thr, retry;

	/* create a new wiphy क्रम use with cfg80211 */
	wiphy = wiphy_new(&mwअगरiex_cfg80211_ops,
			  माप(काष्ठा mwअगरiex_adapter *));
	अगर (!wiphy) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: creating new wiphy\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	wiphy->max_scan_ssids = MWIFIEX_MAX_SSID_LIST_LENGTH;
	wiphy->max_scan_ie_len = MWIFIEX_MAX_VSIE_LEN;
	wiphy->mgmt_stypes = mwअगरiex_mgmt_stypes;
	wiphy->max_reमुख्य_on_channel_duration = 5000;
	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				 BIT(NL80211_IFTYPE_P2P_CLIENT) |
				 BIT(NL80211_IFTYPE_P2P_GO) |
				 BIT(NL80211_IFTYPE_AP);

	अगर (ISSUPP_ADHOC_ENABLED(adapter->fw_cap_info))
		wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_ADHOC);

	wiphy->bands[NL80211_BAND_2GHZ] = &mwअगरiex_band_2ghz;
	अगर (adapter->config_bands & BAND_A)
		wiphy->bands[NL80211_BAND_5GHZ] = &mwअगरiex_band_5ghz;
	अन्यथा
		wiphy->bands[NL80211_BAND_5GHZ] = शून्य;

	अगर (adapter->drcs_enabled && ISSUPP_DRCS_ENABLED(adapter->fw_cap_info))
		wiphy->अगरace_combinations = &mwअगरiex_अगरace_comb_ap_sta_drcs;
	अन्यथा अगर (adapter->is_hw_11ac_capable)
		wiphy->अगरace_combinations = &mwअगरiex_अगरace_comb_ap_sta_vht;
	अन्यथा
		wiphy->अगरace_combinations = &mwअगरiex_अगरace_comb_ap_sta;
	wiphy->n_अगरace_combinations = 1;

	अगर (adapter->max_sta_conn > adapter->max_p2p_conn)
		wiphy->max_ap_assoc_sta = adapter->max_sta_conn;
	अन्यथा
		wiphy->max_ap_assoc_sta = adapter->max_p2p_conn;

	/* Initialize cipher suits */
	wiphy->cipher_suites = mwअगरiex_cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(mwअगरiex_cipher_suites);

	अगर (adapter->regd) अणु
		wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG |
					   REGULATORY_DISABLE_BEACON_HINTS |
					   REGULATORY_COUNTRY_IE_IGNORE;
		wiphy_apply_custom_regulatory(wiphy, adapter->regd);
	पूर्ण

	ether_addr_copy(wiphy->perm_addr, adapter->perm_addr);
	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;
	wiphy->flags |= WIPHY_FLAG_HAVE_AP_SME |
			WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD |
			WIPHY_FLAG_AP_UAPSD |
			WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
			WIPHY_FLAG_HAS_CHANNEL_SWITCH |
			WIPHY_FLAG_PS_ON_BY_DEFAULT;

	अगर (ISSUPP_TDLS_ENABLED(adapter->fw_cap_info))
		wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS |
				WIPHY_FLAG_TDLS_EXTERNAL_SETUP;

#अगर_घोषित CONFIG_PM
	अगर (ISSUPP_FIRMWARE_SUPPLICANT(priv->adapter->fw_cap_info))
		wiphy->wowlan = &mwअगरiex_wowlan_support;
	अन्यथा
		wiphy->wowlan = &mwअगरiex_wowlan_support_no_gtk;
#पूर्ण_अगर

	wiphy->coalesce = &mwअगरiex_coalesce_support;

	wiphy->probe_resp_offload = NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
				    NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 |
				    NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P;

	wiphy->max_sched_scan_reqs = 1;
	wiphy->max_sched_scan_ssids = MWIFIEX_MAX_SSID_LIST_LENGTH;
	wiphy->max_sched_scan_ie_len = MWIFIEX_MAX_VSIE_LEN;
	wiphy->max_match_sets = MWIFIEX_MAX_SSID_LIST_LENGTH;

	wiphy->available_antennas_tx = BIT(adapter->number_of_antenna) - 1;
	wiphy->available_antennas_rx = BIT(adapter->number_of_antenna) - 1;

	wiphy->features |= NL80211_FEATURE_INACTIVITY_TIMER |
			   NL80211_FEATURE_LOW_PRIORITY_SCAN |
			   NL80211_FEATURE_NEED_OBSS_SCAN;

	अगर (ISSUPP_ADHOC_ENABLED(adapter->fw_cap_info))
		wiphy->features |= NL80211_FEATURE_HT_IBSS;

	अगर (ISSUPP_RANDOM_MAC(adapter->fw_cap_info))
		wiphy->features |= NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR |
				   NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR |
				   NL80211_FEATURE_ND_RANDOM_MAC_ADDR;

	अगर (ISSUPP_TDLS_ENABLED(adapter->fw_cap_info))
		wiphy->features |= NL80211_FEATURE_TDLS_CHANNEL_SWITCH;

	अगर (adapter->fw_api_ver == MWIFIEX_FW_V15)
		wiphy->features |= NL80211_FEATURE_SK_TX_STATUS;

	/* Reserve space क्रम mwअगरiex specअगरic निजी data क्रम BSS */
	wiphy->bss_priv_size = माप(काष्ठा mwअगरiex_bss_priv);

	wiphy->reg_notअगरier = mwअगरiex_reg_notअगरier;

	/* Set काष्ठा mwअगरiex_adapter poपूर्णांकer in wiphy_priv */
	wdev_priv = wiphy_priv(wiphy);
	*(अचिन्हित दीर्घ *)wdev_priv = (अचिन्हित दीर्घ)adapter;

	set_wiphy_dev(wiphy, priv->adapter->dev);

	ret = wiphy_रेजिस्टर(wiphy);
	अगर (ret < 0) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: wiphy_register failed: %d\n", __func__, ret);
		wiphy_मुक्त(wiphy);
		वापस ret;
	पूर्ण

	अगर (!adapter->regd) अणु
		अगर (reg_alpha2 && mwअगरiex_is_valid_alpha2(reg_alpha2)) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "driver hint alpha2: %2.2s\n", reg_alpha2);
			regulatory_hपूर्णांक(wiphy, reg_alpha2);
		पूर्ण अन्यथा अणु
			अगर (adapter->region_code == 0x00) अणु
				mwअगरiex_dbg(adapter, WARN,
					    "Ignore world regulatory domain\n");
			पूर्ण अन्यथा अणु
				wiphy->regulatory_flags |=
					REGULATORY_DISABLE_BEACON_HINTS |
					REGULATORY_COUNTRY_IE_IGNORE;
				country_code =
					mwअगरiex_11d_code_2_region(
						adapter->region_code);
				अगर (country_code &&
				    regulatory_hपूर्णांक(wiphy, country_code))
					mwअगरiex_dbg(priv->adapter, ERROR,
						    "regulatory_hint() failed\n");
			पूर्ण
		पूर्ण
	पूर्ण

	mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
			 HostCmd_ACT_GEN_GET, FRAG_THRESH_I, &thr, true);
	wiphy->frag_threshold = thr;
	mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
			 HostCmd_ACT_GEN_GET, RTS_THRESH_I, &thr, true);
	wiphy->rts_threshold = thr;
	mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
			 HostCmd_ACT_GEN_GET, SHORT_RETRY_LIM_I, &retry, true);
	wiphy->retry_लघु = (u8) retry;
	mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
			 HostCmd_ACT_GEN_GET, LONG_RETRY_LIM_I, &retry, true);
	wiphy->retry_दीर्घ = (u8) retry;

	adapter->wiphy = wiphy;
	वापस ret;
पूर्ण
