<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* cfg80211 Interface क्रम prism2_usb module */
#समावेश "hfa384x.h"
#समावेश "prism2mgmt.h"

/* Prism2 channel/frequency/bitrate declarations */
अटल स्थिर काष्ठा ieee80211_channel prism2_channels[] = अणु
	अणु .center_freq = 2412 पूर्ण,
	अणु .center_freq = 2417 पूर्ण,
	अणु .center_freq = 2422 पूर्ण,
	अणु .center_freq = 2427 पूर्ण,
	अणु .center_freq = 2432 पूर्ण,
	अणु .center_freq = 2437 पूर्ण,
	अणु .center_freq = 2442 पूर्ण,
	अणु .center_freq = 2447 पूर्ण,
	अणु .center_freq = 2452 पूर्ण,
	अणु .center_freq = 2457 पूर्ण,
	अणु .center_freq = 2462 पूर्ण,
	अणु .center_freq = 2467 पूर्ण,
	अणु .center_freq = 2472 पूर्ण,
	अणु .center_freq = 2484 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_rate prism2_rates[] = अणु
	अणु .bitrate = 10 पूर्ण,
	अणु .bitrate = 20 पूर्ण,
	अणु .bitrate = 55 पूर्ण,
	अणु .bitrate = 110 पूर्ण
पूर्ण;

#घोषणा PRISM2_NUM_CIPHER_SUITES 2
अटल स्थिर u32 prism2_cipher_suites[PRISM2_NUM_CIPHER_SUITES] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104
पूर्ण;

/* prism2 device निजी data */
काष्ठा prism2_wiphy_निजी अणु
	काष्ठा wlandevice *wlandev;

	काष्ठा ieee80211_supported_band band;
	काष्ठा ieee80211_channel channels[ARRAY_SIZE(prism2_channels)];
	काष्ठा ieee80211_rate rates[ARRAY_SIZE(prism2_rates)];

	काष्ठा cfg80211_scan_request *scan_request;
पूर्ण;

अटल स्थिर व्योम * स्थिर prism2_wiphy_privid = &prism2_wiphy_privid;

/* Helper Functions */
अटल पूर्णांक prism2_result2err(पूर्णांक prism2_result)
अणु
	पूर्णांक err = 0;

	चयन (prism2_result) अणु
	हाल P80211ENUM_resultcode_invalid_parameters:
		err = -EINVAL;
		अवरोध;
	हाल P80211ENUM_resultcode_implementation_failure:
		err = -EIO;
		अवरोध;
	हाल P80211ENUM_resultcode_not_supported:
		err = -EOPNOTSUPP;
		अवरोध;
	शेष:
		err = 0;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक prism2_करोmibset_uपूर्णांक32(काष्ठा wlandevice *wlandev,
				  u32 did, u32 data)
अणु
	काष्ठा p80211msg_करोt11req_mibset msg;
	काष्ठा p80211item_uपूर्णांक32 *mibitem =
			(काष्ठा p80211item_uपूर्णांक32 *)&msg.mibattribute.data;

	msg.msgcode = DIDMSG_DOT11REQ_MIBSET;
	mibitem->did = did;
	mibitem->data = data;

	वापस p80211req_करोrequest(wlandev, (u8 *)&msg);
पूर्ण

अटल पूर्णांक prism2_करोmibset_pstr32(काष्ठा wlandevice *wlandev,
				  u32 did, u8 len, स्थिर u8 *data)
अणु
	काष्ठा p80211msg_करोt11req_mibset msg;
	काष्ठा p80211item_pstr32 *mibitem =
			(काष्ठा p80211item_pstr32 *)&msg.mibattribute.data;

	msg.msgcode = DIDMSG_DOT11REQ_MIBSET;
	mibitem->did = did;
	mibitem->data.len = len;
	स_नकल(mibitem->data.data, data, len);

	वापस p80211req_करोrequest(wlandev, (u8 *)&msg);
पूर्ण

/* The पूर्णांकerface functions, called by the cfg80211 layer */
अटल पूर्णांक prism2_change_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev,
				      क्रमागत nl80211_अगरtype type,
				      काष्ठा vअगर_params *params)
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;
	u32 data;
	पूर्णांक result;
	पूर्णांक err = 0;

	चयन (type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		अगर (wlandev->macmode == WLAN_MACMODE_IBSS_STA)
			जाओ निकास;
		wlandev->macmode = WLAN_MACMODE_IBSS_STA;
		data = 0;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (wlandev->macmode == WLAN_MACMODE_ESS_STA)
			जाओ निकास;
		wlandev->macmode = WLAN_MACMODE_ESS_STA;
		data = 1;
		अवरोध;
	शेष:
		netdev_warn(dev, "Operation mode: %d not support\n", type);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Set Operation mode to the PORT TYPE RID */
	result = prism2_करोmibset_uपूर्णांक32(wlandev,
					DIDMIB_P2_STATIC_CNFPORTTYPE,
					data);

	अगर (result)
		err = -EFAULT;

	dev->ieee80211_ptr->अगरtype = type;

निकास:
	वापस err;
पूर्ण

अटल पूर्णांक prism2_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
			  काष्ठा key_params *params)
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;
	u32 did;

	अगर (key_index >= NUM_WEPKEYS)
		वापस -EINVAL;

	अगर (params->cipher != WLAN_CIPHER_SUITE_WEP40 &&
	    params->cipher != WLAN_CIPHER_SUITE_WEP104) अणु
		pr_debug("Unsupported cipher suite\n");
		वापस -EFAULT;
	पूर्ण

	अगर (prism2_करोmibset_uपूर्णांक32(wlandev,
				   DIDMIB_DOT11SMT_PRIVACYTABLE_WEPDEFAULTKEYID,
				   key_index))
		वापस -EFAULT;

	/* send key to driver */
	did = didmib_करोt11smt_wepशेषkeystable_key(key_index + 1);

	अगर (prism2_करोmibset_pstr32(wlandev, did, params->key_len, params->key))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक prism2_get_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  u8 key_index, bool pairwise,
			  स्थिर u8 *mac_addr, व्योम *cookie,
			  व्योम (*callback)(व्योम *cookie, काष्ठा key_params*))
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;
	काष्ठा key_params params;
	पूर्णांक len;

	अगर (key_index >= NUM_WEPKEYS)
		वापस -EINVAL;

	len = wlandev->wep_keylens[key_index];
	स_रखो(&params, 0, माप(params));

	अगर (len == 13)
		params.cipher = WLAN_CIPHER_SUITE_WEP104;
	अन्यथा अगर (len == 5)
		params.cipher = WLAN_CIPHER_SUITE_WEP104;
	अन्यथा
		वापस -ENOENT;
	params.key_len = len;
	params.key = wlandev->wep_keys[key_index];
	params.seq_len = 0;

	callback(cookie, &params);

	वापस 0;
पूर्ण

अटल पूर्णांक prism2_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  u8 key_index, bool pairwise, स्थिर u8 *mac_addr)
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;
	u32 did;
	पूर्णांक err = 0;
	पूर्णांक result = 0;

	/* There is no direct way in the hardware (AFAIK) of removing
	 * a key, so we will cheat by setting the key to a bogus value
	 */

	अगर (key_index >= NUM_WEPKEYS)
		वापस -EINVAL;

	/* send key to driver */
	did = didmib_करोt11smt_wepशेषkeystable_key(key_index + 1);
	result = prism2_करोmibset_pstr32(wlandev, did, 13, "0000000000000");

	अगर (result)
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक prism2_set_शेष_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  u8 key_index, bool unicast, bool multicast)
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;

	वापस  prism2_करोmibset_uपूर्णांक32(wlandev,
				       DIDMIB_DOT11SMT_PRIVACYTABLE_WEPDEFAULTKEYID,
				       key_index);
पूर्ण

अटल पूर्णांक prism2_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;
	काष्ठा p80211msg_lnxreq_commsquality quality;
	पूर्णांक result;

	स_रखो(sinfo, 0, माप(*sinfo));

	अगर (!wlandev || (wlandev->msdstate != WLAN_MSD_RUNNING))
		वापस -EOPNOTSUPP;

	/* build request message */
	quality.msgcode = DIDMSG_LNXREQ_COMMSQUALITY;
	quality.dbm.data = P80211ENUM_truth_true;
	quality.dbm.status = P80211ENUM_msgitem_status_data_ok;

	/* send message to nsd */
	अगर (!wlandev->mlmerequest)
		वापस -EOPNOTSUPP;

	result = wlandev->mlmerequest(wlandev, (काष्ठा p80211msg *)&quality);

	अगर (result == 0) अणु
		sinfo->txrate.legacy = quality.txrate.data;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
		sinfo->संकेत = quality.level.data;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक prism2_scan(काष्ठा wiphy *wiphy,
		       काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा net_device *dev;
	काष्ठा prism2_wiphy_निजी *priv = wiphy_priv(wiphy);
	काष्ठा wlandevice *wlandev;
	काष्ठा p80211msg_करोt11req_scan msg1;
	काष्ठा p80211msg_करोt11req_scan_results msg2;
	काष्ठा cfg80211_bss *bss;
	काष्ठा cfg80211_scan_info info = अणुपूर्ण;

	पूर्णांक result;
	पूर्णांक err = 0;
	पूर्णांक numbss = 0;
	पूर्णांक i = 0;
	u8 ie_buf[46];
	पूर्णांक ie_len;

	अगर (!request)
		वापस -EINVAL;

	dev = request->wdev->netdev;
	wlandev = dev->ml_priv;

	अगर (priv->scan_request && priv->scan_request != request)
		वापस -EBUSY;

	अगर (wlandev->macmode == WLAN_MACMODE_ESS_AP) अणु
		netdev_err(dev, "Can't scan in AP mode\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	priv->scan_request = request;

	स_रखो(&msg1, 0x00, माप(msg1));
	msg1.msgcode = DIDMSG_DOT11REQ_SCAN;
	msg1.bsstype.data = P80211ENUM_bsstype_any;

	स_रखो(&msg1.bssid.data.data, 0xFF, माप(msg1.bssid.data.data));
	msg1.bssid.data.len = 6;

	अगर (request->n_ssids > 0) अणु
		msg1.scantype.data = P80211ENUM_scantype_active;
		msg1.ssid.data.len = request->ssids->ssid_len;
		स_नकल(msg1.ssid.data.data,
		       request->ssids->ssid, request->ssids->ssid_len);
	पूर्ण अन्यथा अणु
		msg1.scantype.data = 0;
	पूर्ण
	msg1.probedelay.data = 0;

	क्रम (i = 0;
		(i < request->n_channels) && i < ARRAY_SIZE(prism2_channels);
		i++)
		msg1.channellist.data.data[i] =
			ieee80211_frequency_to_channel(
				request->channels[i]->center_freq);
	msg1.channellist.data.len = request->n_channels;

	msg1.maxchannelसमय.data = 250;
	msg1.minchannelसमय.data = 200;

	result = p80211req_करोrequest(wlandev, (u8 *)&msg1);
	अगर (result) अणु
		err = prism2_result2err(msg1.resultcode.data);
		जाओ निकास;
	पूर्ण
	/* Now retrieve scan results */
	numbss = msg1.numbss.data;

	क्रम (i = 0; i < numbss; i++) अणु
		पूर्णांक freq;

		स_रखो(&msg2, 0, माप(msg2));
		msg2.msgcode = DIDMSG_DOT11REQ_SCAN_RESULTS;
		msg2.bssindex.data = i;

		result = p80211req_करोrequest(wlandev, (u8 *)&msg2);
		अगर ((result != 0) ||
		    (msg2.resultcode.data != P80211ENUM_resultcode_success)) अणु
			अवरोध;
		पूर्ण

		ie_buf[0] = WLAN_EID_SSID;
		ie_buf[1] = msg2.ssid.data.len;
		ie_len = ie_buf[1] + 2;
		स_नकल(&ie_buf[2], &msg2.ssid.data.data, msg2.ssid.data.len);
		freq = ieee80211_channel_to_frequency(msg2.dschannel.data,
						      NL80211_BAND_2GHZ);
		bss = cfg80211_inक्रमm_bss(wiphy,
					  ieee80211_get_channel(wiphy, freq),
					  CFG80211_BSS_FTYPE_UNKNOWN,
					  (स्थिर u8 *)&msg2.bssid.data.data,
					  msg2.बारtamp.data, msg2.capinfo.data,
					  msg2.beaconperiod.data,
					  ie_buf,
					  ie_len,
					  (msg2.संकेत.data - 65536) * 100, /* Conversion to चिन्हित type */
					  GFP_KERNEL);

		अगर (!bss) अणु
			err = -ENOMEM;
			जाओ निकास;
		पूर्ण

		cfg80211_put_bss(wiphy, bss);
	पूर्ण

	अगर (result)
		err = prism2_result2err(msg2.resultcode.data);

निकास:
	info.पातed = !!(err);
	cfg80211_scan_करोne(request, &info);
	priv->scan_request = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक prism2_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा prism2_wiphy_निजी *priv = wiphy_priv(wiphy);
	काष्ठा wlandevice *wlandev = priv->wlandev;
	u32 data;
	पूर्णांक result;
	पूर्णांक err = 0;

	अगर (changed & WIPHY_PARAM_RTS_THRESHOLD) अणु
		अगर (wiphy->rts_threshold == -1)
			data = 2347;
		अन्यथा
			data = wiphy->rts_threshold;

		result = prism2_करोmibset_uपूर्णांक32(wlandev,
						DIDMIB_DOT11MAC_OPERATIONTABLE_RTSTHRESHOLD,
						data);
		अगर (result) अणु
			err = -EFAULT;
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD) अणु
		अगर (wiphy->frag_threshold == -1)
			data = 2346;
		अन्यथा
			data = wiphy->frag_threshold;

		result = prism2_करोmibset_uपूर्णांक32(wlandev,
						DIDMIB_DOT11MAC_OPERATIONTABLE_FRAGMENTATIONTHRESHOLD,
						data);
		अगर (result) अणु
			err = -EFAULT;
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	वापस err;
पूर्ण

अटल पूर्णांक prism2_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;
	काष्ठा ieee80211_channel *channel = sme->channel;
	काष्ठा p80211msg_lnxreq_स्वतःjoin msg_join;
	u32 did;
	पूर्णांक length = sme->ssid_len;
	पूर्णांक chan = -1;
	पूर्णांक is_wep = (sme->crypto.cipher_group == WLAN_CIPHER_SUITE_WEP40) ||
	    (sme->crypto.cipher_group == WLAN_CIPHER_SUITE_WEP104);
	पूर्णांक result;
	पूर्णांक err = 0;

	/* Set the channel */
	अगर (channel) अणु
		chan = ieee80211_frequency_to_channel(channel->center_freq);
		result = prism2_करोmibset_uपूर्णांक32(wlandev,
						DIDMIB_DOT11PHY_DSSSTABLE_CURRENTCHANNEL,
						chan);
		अगर (result)
			जाओ निकास;
	पूर्ण

	/* Set the authorization */
	अगर ((sme->auth_type == NL80211_AUTHTYPE_OPEN_SYSTEM) ||
	    ((sme->auth_type == NL80211_AUTHTYPE_AUTOMATIC) && !is_wep))
		msg_join.authtype.data = P80211ENUM_authalg_खोलोप्रणाली;
	अन्यथा अगर ((sme->auth_type == NL80211_AUTHTYPE_SHARED_KEY) ||
		 ((sme->auth_type == NL80211_AUTHTYPE_AUTOMATIC) && is_wep))
		msg_join.authtype.data = P80211ENUM_authalg_sharedkey;
	अन्यथा
		netdev_warn(dev,
			    "Unhandled authorisation type for connect (%d)\n",
			    sme->auth_type);

	/* Set the encryption - we only support wep */
	अगर (is_wep) अणु
		अगर (sme->key) अणु
			अगर (sme->key_idx >= NUM_WEPKEYS)
				वापस -EINVAL;

			result = prism2_करोmibset_uपूर्णांक32(wlandev,
				DIDMIB_DOT11SMT_PRIVACYTABLE_WEPDEFAULTKEYID,
				sme->key_idx);
			अगर (result)
				जाओ निकास;

			/* send key to driver */
			did = didmib_करोt11smt_wepशेषkeystable_key(
					sme->key_idx + 1);
			result = prism2_करोmibset_pstr32(wlandev,
							did, sme->key_len,
							(u8 *)sme->key);
			अगर (result)
				जाओ निकास;
		पूर्ण

		/* Assume we should set privacy invoked and exclude unencrypted
		 * We could possible use sme->privacy here, but the assumption
		 * seems reasonable anyways
		 */
		result = prism2_करोmibset_uपूर्णांक32(wlandev,
						DIDMIB_DOT11SMT_PRIVACYTABLE_PRIVACYINVOKED,
						P80211ENUM_truth_true);
		अगर (result)
			जाओ निकास;

		result = prism2_करोmibset_uपूर्णांक32(wlandev,
						DIDMIB_DOT11SMT_PRIVACYTABLE_EXCLUDEUNENCRYPTED,
						P80211ENUM_truth_true);
		अगर (result)
			जाओ निकास;

	पूर्ण अन्यथा अणु
		/* Assume we should unset privacy invoked
		 * and exclude unencrypted
		 */
		result = prism2_करोmibset_uपूर्णांक32(wlandev,
						DIDMIB_DOT11SMT_PRIVACYTABLE_PRIVACYINVOKED,
						P80211ENUM_truth_false);
		अगर (result)
			जाओ निकास;

		result = prism2_करोmibset_uपूर्णांक32(wlandev,
						DIDMIB_DOT11SMT_PRIVACYTABLE_EXCLUDEUNENCRYPTED,
						P80211ENUM_truth_false);
		अगर (result)
			जाओ निकास;
	पूर्ण

	/* Now करो the actual join. Note there is no way that I can
	 * see to request a specअगरic bssid
	 */
	msg_join.msgcode = DIDMSG_LNXREQ_AUTOJOIN;

	स_नकल(msg_join.ssid.data.data, sme->ssid, length);
	msg_join.ssid.data.len = length;

	result = p80211req_करोrequest(wlandev, (u8 *)&msg_join);

निकास:
	अगर (result)
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक prism2_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u16 reason_code)
अणु
	काष्ठा wlandevice *wlandev = dev->ml_priv;
	काष्ठा p80211msg_lnxreq_स्वतःjoin msg_join;
	पूर्णांक result;
	पूर्णांक err = 0;

	/* Do a join, with a bogus ssid. Thats the only way I can think of */
	msg_join.msgcode = DIDMSG_LNXREQ_AUTOJOIN;

	स_नकल(msg_join.ssid.data.data, "---", 3);
	msg_join.ssid.data.len = 3;

	result = p80211req_करोrequest(wlandev, (u8 *)&msg_join);

	अगर (result)
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक prism2_join_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			    काष्ठा cfg80211_ibss_params *params)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक prism2_leave_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक prism2_set_tx_घातer(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			       क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm)
अणु
	काष्ठा prism2_wiphy_निजी *priv = wiphy_priv(wiphy);
	काष्ठा wlandevice *wlandev = priv->wlandev;
	u32 data;
	पूर्णांक result;
	पूर्णांक err = 0;

	अगर (type == NL80211_TX_POWER_AUTOMATIC)
		data = 30;
	अन्यथा
		data = MBM_TO_DBM(mbm);

	result = prism2_करोmibset_uपूर्णांक32(wlandev,
		DIDMIB_DOT11PHY_TXPOWERTABLE_CURRENTTXPOWERLEVEL,
		data);

	अगर (result) अणु
		err = -EFAULT;
		जाओ निकास;
	पूर्ण

निकास:
	वापस err;
पूर्ण

अटल पूर्णांक prism2_get_tx_घातer(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			       पूर्णांक *dbm)
अणु
	काष्ठा prism2_wiphy_निजी *priv = wiphy_priv(wiphy);
	काष्ठा wlandevice *wlandev = priv->wlandev;
	काष्ठा p80211msg_करोt11req_mibget msg;
	काष्ठा p80211item_uपूर्णांक32 *mibitem;
	पूर्णांक result;
	पूर्णांक err = 0;

	mibitem = (काष्ठा p80211item_uपूर्णांक32 *)&msg.mibattribute.data;
	msg.msgcode = DIDMSG_DOT11REQ_MIBGET;
	mibitem->did = DIDMIB_DOT11PHY_TXPOWERTABLE_CURRENTTXPOWERLEVEL;

	result = p80211req_करोrequest(wlandev, (u8 *)&msg);

	अगर (result) अणु
		err = -EFAULT;
		जाओ निकास;
	पूर्ण

	*dbm = mibitem->data;

निकास:
	वापस err;
पूर्ण

/* Interface callback functions, passing data back up to the cfg80211 layer */
व्योम prism2_connect_result(काष्ठा wlandevice *wlandev, u8 failed)
अणु
	u16 status = failed ?
		     WLAN_STATUS_UNSPECIFIED_FAILURE : WLAN_STATUS_SUCCESS;

	cfg80211_connect_result(wlandev->netdev, wlandev->bssid,
				शून्य, 0, शून्य, 0, status, GFP_KERNEL);
पूर्ण

व्योम prism2_disconnected(काष्ठा wlandevice *wlandev)
अणु
	cfg80211_disconnected(wlandev->netdev, 0, शून्य,
			      0, false, GFP_KERNEL);
पूर्ण

व्योम prism2_roamed(काष्ठा wlandevice *wlandev)
अणु
	काष्ठा cfg80211_roam_info roam_info = अणु
		.bssid = wlandev->bssid,
	पूर्ण;

	cfg80211_roamed(wlandev->netdev, &roam_info, GFP_KERNEL);
पूर्ण

/* Structures क्रम declaring wiphy पूर्णांकerface */
अटल स्थिर काष्ठा cfg80211_ops prism2_usb_cfg_ops = अणु
	.change_भव_पूर्णांकf = prism2_change_भव_पूर्णांकf,
	.add_key = prism2_add_key,
	.get_key = prism2_get_key,
	.del_key = prism2_del_key,
	.set_शेष_key = prism2_set_शेष_key,
	.get_station = prism2_get_station,
	.scan = prism2_scan,
	.set_wiphy_params = prism2_set_wiphy_params,
	.connect = prism2_connect,
	.disconnect = prism2_disconnect,
	.join_ibss = prism2_join_ibss,
	.leave_ibss = prism2_leave_ibss,
	.set_tx_घातer = prism2_set_tx_घातer,
	.get_tx_घातer = prism2_get_tx_घातer,
पूर्ण;

/* Functions to create/मुक्त wiphy पूर्णांकerface */
अटल काष्ठा wiphy *wlan_create_wiphy(काष्ठा device *dev,
				       काष्ठा wlandevice *wlandev)
अणु
	काष्ठा wiphy *wiphy;
	काष्ठा prism2_wiphy_निजी *priv;

	wiphy = wiphy_new(&prism2_usb_cfg_ops, माप(*priv));
	अगर (!wiphy)
		वापस शून्य;

	priv = wiphy_priv(wiphy);
	priv->wlandev = wlandev;
	स_नकल(priv->channels, prism2_channels, माप(prism2_channels));
	स_नकल(priv->rates, prism2_rates, माप(prism2_rates));
	priv->band.channels = priv->channels;
	priv->band.n_channels = ARRAY_SIZE(prism2_channels);
	priv->band.bitrates = priv->rates;
	priv->band.n_bitrates = ARRAY_SIZE(prism2_rates);
	priv->band.band = NL80211_BAND_2GHZ;
	priv->band.ht_cap.ht_supported = false;
	wiphy->bands[NL80211_BAND_2GHZ] = &priv->band;

	set_wiphy_dev(wiphy, dev);
	wiphy->privid = prism2_wiphy_privid;
	wiphy->max_scan_ssids = 1;
	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION)
				 | BIT(NL80211_IFTYPE_ADHOC);
	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;
	wiphy->n_cipher_suites = PRISM2_NUM_CIPHER_SUITES;
	wiphy->cipher_suites = prism2_cipher_suites;

	अगर (wiphy_रेजिस्टर(wiphy) < 0) अणु
		wiphy_मुक्त(wiphy);
		वापस शून्य;
	पूर्ण

	वापस wiphy;
पूर्ण

अटल व्योम wlan_मुक्त_wiphy(काष्ठा wiphy *wiphy)
अणु
	wiphy_unरेजिस्टर(wiphy);
	wiphy_मुक्त(wiphy);
पूर्ण
