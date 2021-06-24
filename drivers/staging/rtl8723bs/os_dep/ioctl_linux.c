<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _IOCTL_LINUX_C_

#समावेश <linux/etherdevice.h>
#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtw_mp.h>
#समावेश <hal_btcoex.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>

#घोषणा RTL_IOCTL_WPA_SUPPLICANT	(SIOCIWFIRSTPRIV+30)

#घोषणा SCAN_ITEM_SIZE 768
#घोषणा MAX_CUSTOM_LEN 64
#घोषणा RATE_COUNT 4

/*  combo scan */
#घोषणा WEXT_CSCAN_HEADER		"CSCAN S\x01\x00\x00S\x00"
#घोषणा WEXT_CSCAN_HEADER_SIZE		12
#घोषणा WEXT_CSCAN_SSID_SECTION		'S'
#घोषणा WEXT_CSCAN_CHANNEL_SECTION	'C'
#घोषणा WEXT_CSCAN_ACTV_DWELL_SECTION	'A'
#घोषणा WEXT_CSCAN_PASV_DWELL_SECTION	'P'
#घोषणा WEXT_CSCAN_HOME_DWELL_SECTION	'H'
#घोषणा WEXT_CSCAN_TYPE_SECTION		'T'

अटल u32 rtw_rates[] = अणु1000000, 2000000, 5500000, 11000000,
	6000000, 9000000, 12000000, 18000000, 24000000, 36000000, 48000000, 54000000पूर्ण;

व्योम indicate_wx_scan_complete_event(काष्ठा adapter *padapter)
अणु
	जोड़ iwreq_data wrqu;

	स_रखो(&wrqu, 0, माप(जोड़ iwreq_data));
पूर्ण


व्योम rtw_indicate_wx_assoc_event(काष्ठा adapter *padapter)
अणु
	जोड़ iwreq_data wrqu;
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex		*pnetwork = (काष्ठा wlan_bssid_ex *)(&(pmlmeinfo->network));

	स_रखो(&wrqu, 0, माप(जोड़ iwreq_data));

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)
		स_नकल(wrqu.ap_addr.sa_data, pnetwork->MacAddress, ETH_ALEN);
	अन्यथा
		स_नकल(wrqu.ap_addr.sa_data, pmlmepriv->cur_network.network.MacAddress, ETH_ALEN);

	netdev_dbg(padapter->pnetdev, "assoc success\n");
पूर्ण

व्योम rtw_indicate_wx_disassoc_event(काष्ठा adapter *padapter)
अणु
	जोड़ iwreq_data wrqu;

	स_रखो(&wrqu, 0, माप(जोड़ iwreq_data));

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	eth_zero_addr(wrqu.ap_addr.sa_data);
पूर्ण

अटल अक्षर *translate_scan(काष्ठा adapter *padapter,
				काष्ठा iw_request_info *info, काष्ठा wlan_network *pnetwork,
				अक्षर *start, अक्षर *stop)
अणु
	काष्ठा iw_event iwe;
	u16 cap;
	u32 ht_ielen = 0;
	अक्षर *custom = शून्य;
	अक्षर *p;
	u16 max_rate = 0, rate, ht_cap = false, vht_cap = false;
	u32 i = 0;
	u8 bw_40MHz = 0, लघु_GI = 0;
	u16 mcs_rate = 0, vht_data_rate = 0;
	u8 ie_offset = (pnetwork->network.Reserved[0] == 2 ? 0 : 12);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	u8 ss, sq;

	/*  AP MAC address  */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;

	स_नकल(iwe.u.ap_addr.sa_data, pnetwork->network.MacAddress, ETH_ALEN);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_ADDR_LEN);

	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	iwe.u.data.length = min((u16)pnetwork->network.Ssid.SsidLength, (u16)32);
	start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, pnetwork->network.Ssid.Ssid);

	/* parsing HT_CAP_IE */
	अगर (pnetwork->network.Reserved[0] == 2) अणु /*  Probe Request */
		p = rtw_get_ie(&pnetwork->network.IEs[0], WLAN_EID_HT_CAPABILITY, &ht_ielen, pnetwork->network.IELength);
	पूर्ण अन्यथा अणु
		p = rtw_get_ie(&pnetwork->network.IEs[12], WLAN_EID_HT_CAPABILITY, &ht_ielen, pnetwork->network.IELength-12);
	पूर्ण
	अगर (p && ht_ielen > 0) अणु
		काष्ठा ieee80211_ht_cap *pht_capie;
		ht_cap = true;
		pht_capie = (काष्ठा ieee80211_ht_cap *)(p+2);
		स_नकल(&mcs_rate, pht_capie->mcs.rx_mask, 2);
		bw_40MHz = (le16_to_cpu(pht_capie->cap_info) & IEEE80211_HT_CAP_SUP_WIDTH) ? 1 : 0;
		लघु_GI = (le16_to_cpu(pht_capie->cap_info) & (IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40)) ? 1 : 0;
	पूर्ण

	/* Add the protocol name */
	iwe.cmd = SIOCGIWNAME;
	अगर (rtw_is_cckratesonly_included((u8 *)&pnetwork->network.SupportedRates)) अणु
		अगर (ht_cap)
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11bn");
		अन्यथा
		snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11b");
	पूर्ण अन्यथा अगर (rtw_is_cckrates_included((u8 *)&pnetwork->network.SupportedRates)) अणु
		अगर (ht_cap)
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11bgn");
		अन्यथा
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11bg");
	पूर्ण अन्यथा अणु
		अगर (pnetwork->network.Configuration.DSConfig > 14) अणु
			अगर (vht_cap)
				snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11AC");
			अन्यथा अगर (ht_cap)
				snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11an");
			अन्यथा
				snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11a");
		पूर्ण अन्यथा अणु
			अगर (ht_cap)
				snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11gn");
			अन्यथा
				snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11g");
		पूर्ण
	पूर्ण

	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_CHAR_LEN);

	  /* Add mode */
	अगर (pnetwork->network.Reserved[0] == 2) अणु /*  Probe Request */
		cap = 0;
	पूर्ण अन्यथा अणु
		__le16 le_पंचांगp;

	        iwe.cmd = SIOCGIWMODE;
		स_नकल((u8 *)&le_पंचांगp, rtw_get_capability_from_ie(pnetwork->network.IEs), 2);
		cap = le16_to_cpu(le_पंचांगp);
	पूर्ण

	अगर (cap & (WLAN_CAPABILITY_IBSS | WLAN_CAPABILITY_ESS)) अणु
		अगर (cap & WLAN_CAPABILITY_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;

		start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_UINT_LEN);
	पूर्ण

	अगर (pnetwork->network.Configuration.DSConfig < 1 /*|| pnetwork->network.Configuration.DSConfig > 14*/)
		pnetwork->network.Configuration.DSConfig = 1;

	 /* Add frequency/channel */
	iwe.cmd = SIOCGIWFREQ;
	iwe.u.freq.m = rtw_ch2freq(pnetwork->network.Configuration.DSConfig) * 100000;
	iwe.u.freq.e = 1;
	iwe.u.freq.i = pnetwork->network.Configuration.DSConfig;
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_FREQ_LEN);

	/* Add encryption capability */
	iwe.cmd = SIOCGIWENCODE;
	अगर (cap & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	अन्यथा
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, pnetwork->network.Ssid.Ssid);

	/*Add basic and extended rates */
	max_rate = 0;
	custom = kzalloc(MAX_CUSTOM_LEN, GFP_ATOMIC);
	अगर (!custom)
		वापस start;
	p = custom;
	p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom), " Rates (Mb/s): ");
	जबतक (pnetwork->network.SupportedRates[i] != 0) अणु
		rate = pnetwork->network.SupportedRates[i]&0x7F;
		अगर (rate > max_rate)
			max_rate = rate;
		p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom),
			      "%d%s ", rate >> 1, (rate & 1) ? ".5" : "");
		i++;
	पूर्ण

	अगर (vht_cap) अणु
		max_rate = vht_data_rate;
	पूर्ण अन्यथा अगर (ht_cap) अणु
		अगर (mcs_rate & 0x8000) /* MCS15 */
			max_rate = (bw_40MHz) ? ((लघु_GI)?300:270):((लघु_GI)?144:130);
		अन्यथा /* शेष MCS7 */
			max_rate = (bw_40MHz) ? ((लघु_GI)?150:135):((लघु_GI)?72:65);

		max_rate = max_rate*2;/* Mbps/2; */
	पूर्ण

	iwe.cmd = SIOCGIWRATE;
	iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;
	iwe.u.bitrate.value = max_rate * 500000;
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_PARAM_LEN);

	/* parsing WPA/WPA2 IE */
	अगर (pnetwork->network.Reserved[0] != 2) अणु /*  Probe Request */
		u8 *buf;
		u8 wpa_ie[255], rsn_ie[255];
		u16 wpa_len = 0, rsn_len = 0;
		u8 *p;
		rtw_get_sec_ie(pnetwork->network.IEs, pnetwork->network.IELength, rsn_ie, &rsn_len, wpa_ie, &wpa_len);

		buf = kzalloc(MAX_WPA_IE_LEN*2, GFP_ATOMIC);
		अगर (!buf)
			वापस start;
		अगर (wpa_len > 0) अणु
			p = buf;
			p += scnम_लिखो(p, (MAX_WPA_IE_LEN * 2) - (p - buf), "wpa_ie =");
			क्रम (i = 0; i < wpa_len; i++)
				p += scnम_लिखो(p, (MAX_WPA_IE_LEN * 2) - (p - buf),
						"%02x", wpa_ie[i]);

			अगर (wpa_len > 100) अणु
				prपूर्णांकk("-----------------Len %d----------------\n", wpa_len);
				क्रम (i = 0; i < wpa_len; i++)
					prपूर्णांकk("%02x ", wpa_ie[i]);
				prपूर्णांकk("\n");
				prपूर्णांकk("-----------------Len %d----------------\n", wpa_len);
			पूर्ण

			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = IWEVCUSTOM;
			iwe.u.data.length = म_माप(buf);
			start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, buf);

			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = IWEVGENIE;
			iwe.u.data.length = wpa_len;
			start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, wpa_ie);
		पूर्ण
		अगर (rsn_len > 0) अणु
			p = buf;
			स_रखो(buf, 0, MAX_WPA_IE_LEN*2);
			p += scnम_लिखो(p, (MAX_WPA_IE_LEN * 2) - (p - buf), "rsn_ie =");
			क्रम (i = 0; i < rsn_len; i++)
				p += scnम_लिखो(p, (MAX_WPA_IE_LEN * 2) - (p - buf),
						"%02x", rsn_ie[i]);
			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = IWEVCUSTOM;
			iwe.u.data.length = म_माप(buf);
			start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, buf);

			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = IWEVGENIE;
			iwe.u.data.length = rsn_len;
			start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, rsn_ie);
		पूर्ण
		kमुक्त(buf);
	पूर्ण

	अणु /* parsing WPS IE */
		uपूर्णांक cnt = 0, total_ielen;
		u8 *wpsie_ptr = शून्य;
		uपूर्णांक wps_ielen = 0;

		u8 *ie_ptr;
		total_ielen = pnetwork->network.IELength - ie_offset;

		अगर (pnetwork->network.Reserved[0] == 2) अणु /*  Probe Request */
			ie_ptr = pnetwork->network.IEs;
			total_ielen = pnetwork->network.IELength;
		पूर्ण अन्यथा अणु    /*  Beacon or Probe Respones */
			ie_ptr = pnetwork->network.IEs + _FIXED_IE_LENGTH_;
			total_ielen = pnetwork->network.IELength - _FIXED_IE_LENGTH_;
		पूर्ण

		जबतक (cnt < total_ielen) अणु
			अगर (rtw_is_wps_ie(&ie_ptr[cnt], &wps_ielen) && (wps_ielen > 2)) अणु
				wpsie_ptr = &ie_ptr[cnt];
				iwe.cmd = IWEVGENIE;
				iwe.u.data.length = (u16)wps_ielen;
				start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, wpsie_ptr);
			पूर्ण
			cnt += ie_ptr[cnt + 1] + 2; /* जाओ next */
		पूर्ण
	पूर्ण

	/* Add quality statistics */
	iwe.cmd = IWEVQUAL;
	iwe.u.qual.updated = IW_QUAL_QUAL_UPDATED | IW_QUAL_LEVEL_UPDATED
		| IW_QUAL_NOISE_INVALID;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true &&
		is_same_network(&pmlmepriv->cur_network.network, &pnetwork->network, 0)) अणु
		ss = padapter->recvpriv.संकेत_strength;
		sq = padapter->recvpriv.संकेत_qual;
	पूर्ण अन्यथा अणु
		ss = pnetwork->network.PhyInfo.SignalStrength;
		sq = pnetwork->network.PhyInfo.SignalQuality;
	पूर्ण


	iwe.u.qual.level = (u8)ss;/*  */

	iwe.u.qual.qual = (u8)sq;   /*  संकेत quality */

	iwe.u.qual.noise = 0; /*  noise level */

	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_QUAL_LEN);

	अणु
		u8 *buf;
		u8 *pos;

		buf = kzalloc(MAX_WPA_IE_LEN, GFP_ATOMIC);
		अगर (!buf)
			जाओ निकास;

		pos = pnetwork->network.Reserved;
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVCUSTOM;
		iwe.u.data.length = scnम_लिखो(buf, MAX_WPA_IE_LEN, "fm =%02X%02X", pos[1], pos[0]);
		start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, buf);
		kमुक्त(buf);
	पूर्ण
निकास:
	kमुक्त(custom);

	वापस start;
पूर्ण

अटल पूर्णांक wpa_set_auth_algs(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर ((value & WLAN_AUTH_SHARED_KEY) && (value & WLAN_AUTH_OPEN)) अणु
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
		padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeAutoSwitch;
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Auto;
	पूर्ण अन्यथा अगर (value & WLAN_AUTH_SHARED_KEY)	अणु
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;

		padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeShared;
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Shared;
	पूर्ण अन्यथा अगर (value & WLAN_AUTH_OPEN) अणु
		/* padapter->securitypriv.ndisencryptstatus = Ndis802_11EncryptionDisabled; */
		अगर (padapter->securitypriv.ndisauthtype < Ndis802_11AuthModeWPAPSK) अणु
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
			padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक wpa_set_encryption(काष्ठा net_device *dev, काष्ठा ieee_param *param, u32 param_len)
अणु
	पूर्णांक ret = 0;
	u32 wep_key_idx, wep_key_len, wep_total_len;
	काष्ठा ndis_802_11_wep	 *pwep = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';

	अगर (param_len < (u32)((u8 *)param->u.crypt.key - (u8 *)param) + param->u.crypt.key_len) अणु
		ret =  -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff) अणु
		अगर (param->u.crypt.idx >= WEP_KEYS ||
		    param->u.crypt.idx >= BIP_MAX_KEYID) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु

		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
		padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP40_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _WEP40_;

		wep_key_idx = param->u.crypt.idx;
		wep_key_len = param->u.crypt.key_len;

		अगर (wep_key_idx > WEP_KEYS)
			वापस -EINVAL;

		अगर (wep_key_len > 0) अणु
			wep_key_len = wep_key_len <= 5 ? 5 : 13;
			wep_total_len = wep_key_len + FIELD_OFFSET(काष्ठा ndis_802_11_wep, KeyMaterial);
			pwep = kzalloc(wep_total_len, GFP_KERNEL);
			अगर (!pwep)
				जाओ निकास;

			pwep->KeyLength = wep_key_len;
			pwep->Length = wep_total_len;

			अगर (wep_key_len == 13) अणु
				padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP104_;
				padapter->securitypriv.करोt118021XGrpPrivacy = _WEP104_;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण

		pwep->KeyIndex = wep_key_idx;
		pwep->KeyIndex |= 0x80000000;

		स_नकल(pwep->KeyMaterial,  param->u.crypt.key, pwep->KeyLength);

		अगर (param->u.crypt.set_tx) अणु
			अगर (rtw_set_802_11_add_wep(padapter, pwep) == (u8)_FAIL)
				ret = -EOPNOTSUPP;
		पूर्ण अन्यथा अणु
			/* करोn't update "psecuritypriv->dot11PrivacyAlgrthm" and */
			/* psecuritypriv->करोt11PrivacyKeyIndex =keyid", but can rtw_set_key to fw/cam */

			अगर (wep_key_idx >= WEP_KEYS) अणु
				ret = -EOPNOTSUPP;
				जाओ निकास;
			पूर्ण

			स_नकल(&(psecuritypriv->करोt11DefKey[wep_key_idx].skey[0]), pwep->KeyMaterial, pwep->KeyLength);
			psecuritypriv->करोt11DefKeylen[wep_key_idx] = pwep->KeyLength;
			rtw_set_key(padapter, psecuritypriv, wep_key_idx, 0, true);
		पूर्ण

		जाओ निकास;
	पूर्ण

	अगर (padapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X) अणु /*  802_1x */
		काष्ठा sta_info *psta, *pbcmc_sta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_MP_STATE) == true) अणु /* sta mode */
			psta = rtw_get_stainfo(pstapriv, get_bssid(pmlmepriv));
			अगर (psta == शून्य) अणु
				/* DEBUG_ERR(("Set wpa_set_encryption: Obtain Sta_info fail\n")); */
			पूर्ण अन्यथा अणु
				/* Jeff: करोn't disable ieee8021x_blocked जबतक clearing key */
				अगर (म_भेद(param->u.crypt.alg, "none") != 0)
					psta->ieee8021x_blocked = false;

				अगर ((padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption2Enabled) ||
						(padapter->securitypriv.ndisencryptstatus ==  Ndis802_11Encryption3Enabled)) अणु
					psta->करोt118021XPrivacy = padapter->securitypriv.करोt11PrivacyAlgrthm;
				पूर्ण

				अगर (param->u.crypt.set_tx == 1) अणु /* pairwise key */
					स_नकल(psta->करोt118021x_UncstKey.skey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

					अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु /* set mic key */
						/* DEBUG_ERR(("\nset key length :param->u.crypt.key_len =%d\n", param->u.crypt.key_len)); */
						स_नकल(psta->करोt11tkiptxmickey.skey, &(param->u.crypt.key[16]), 8);
						स_नकल(psta->करोt11tkiprxmickey.skey, &(param->u.crypt.key[24]), 8);

						padapter->securitypriv.busetkipkey = false;
						/* _set_समयr(&padapter->securitypriv.tkip_समयr, 50); */
					पूर्ण

					rtw_setstakey_cmd(padapter, psta, true, true);
				पूर्ण अन्यथा अणु /* group key */
					अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0 || म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु
						स_नकल(padapter->securitypriv.करोt118021XGrpKey[param->u.crypt.idx].skey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));
						/* only TKIP group key need to install this */
						अगर (param->u.crypt.key_len > 16) अणु
							स_नकल(padapter->securitypriv.करोt118021XGrptxmickey[param->u.crypt.idx].skey, &(param->u.crypt.key[16]), 8);
							स_नकल(padapter->securitypriv.करोt118021XGrprxmickey[param->u.crypt.idx].skey, &(param->u.crypt.key[24]), 8);
						पूर्ण
						padapter->securitypriv.binstallGrpkey = true;

						padapter->securitypriv.करोt118021XGrpKeyid = param->u.crypt.idx;

						rtw_set_key(padapter, &padapter->securitypriv, param->u.crypt.idx, 1, true);
					पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "BIP") == 0) अणु
						/* prपूर्णांकk("BIP key_len =%d , index =%d @@@@@@@@@@@@@@@@@@\n", param->u.crypt.key_len, param->u.crypt.idx); */
						/* save the IGTK key, length 16 bytes */
						स_नकल(padapter->securitypriv.करोt11wBIPKey[param->u.crypt.idx].skey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));
						/*prपूर्णांकk("IGTK key below:\n");
						क्रम (no = 0;no<16;no++)
							prपूर्णांकk(" %02x ", padapter->securitypriv.करोt11wBIPKey[param->u.crypt.idx].skey[no]);
						prपूर्णांकk("\n");*/
						padapter->securitypriv.करोt11wBIPKeyid = param->u.crypt.idx;
						padapter->securitypriv.binstallBIPkey = true;
					पूर्ण
				पूर्ण
			पूर्ण

			pbcmc_sta = rtw_get_bcmc_stainfo(padapter);
			अगर (pbcmc_sta == शून्य) अणु
				/* DEBUG_ERR(("Set OID_802_11_ADD_KEY: bcmc stainfo is null\n")); */
			पूर्ण अन्यथा अणु
				/* Jeff: करोn't disable ieee8021x_blocked जबतक clearing key */
				अगर (म_भेद(param->u.crypt.alg, "none") != 0)
					pbcmc_sta->ieee8021x_blocked = false;

				अगर ((padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption2Enabled) ||
						(padapter->securitypriv.ndisencryptstatus ==  Ndis802_11Encryption3Enabled)) अणु
					pbcmc_sta->करोt118021XPrivacy = padapter->securitypriv.करोt11PrivacyAlgrthm;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
			/* adhoc mode */
		पूर्ण
	पूर्ण

निकास:

	kमुक्त(pwep);
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_set_wpa_ie(काष्ठा adapter *padapter, अक्षर *pie, अचिन्हित लघु ielen)
अणु
	u8 *buf = शून्य;
	पूर्णांक group_cipher = 0, pairwise_cipher = 0;
	पूर्णांक ret = 0;
	u8 null_addr[] = अणु0, 0, 0, 0, 0, 0पूर्ण;

	अगर ((ielen > MAX_WPA_IE_LEN) || (pie == शून्य)) अणु
		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
		अगर (pie == शून्य)
			वापस ret;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (ielen) अणु
		buf = rtw_zदो_स्मृति(ielen);
		अगर (buf == शून्य) अणु
			ret =  -ENOMEM;
			जाओ निकास;
		पूर्ण

		स_नकल(buf, pie, ielen);

		अगर (ielen < RSN_HEADER_LEN) अणु
			ret  = -1;
			जाओ निकास;
		पूर्ण

		अगर (rtw_parse_wpa_ie(buf, ielen, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPAPSK;
			स_नकल(padapter->securitypriv.supplicant_ie, &buf[0], ielen);
		पूर्ण

		अगर (rtw_parse_wpa2_ie(buf, ielen, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPA2PSK;
			स_नकल(padapter->securitypriv.supplicant_ie, &buf[0], ielen);
		पूर्ण

		अगर (group_cipher == 0)
			group_cipher = WPA_CIPHER_NONE;
		अगर (pairwise_cipher == 0)
			pairwise_cipher = WPA_CIPHER_NONE;

		चयन (group_cipher) अणु
		हाल WPA_CIPHER_NONE:
			padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11EncryptionDisabled;
			अवरोध;
		हाल WPA_CIPHER_WEP40:
			padapter->securitypriv.करोt118021XGrpPrivacy = _WEP40_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
			अवरोध;
		हाल WPA_CIPHER_TKIP:
			padapter->securitypriv.करोt118021XGrpPrivacy = _TKIP_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
			अवरोध;
		हाल WPA_CIPHER_CCMP:
			padapter->securitypriv.करोt118021XGrpPrivacy = _AES_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
			अवरोध;
		हाल WPA_CIPHER_WEP104:
			padapter->securitypriv.करोt118021XGrpPrivacy = _WEP104_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
			अवरोध;
		पूर्ण

		चयन (pairwise_cipher) अणु
		हाल WPA_CIPHER_NONE:
			padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11EncryptionDisabled;
			अवरोध;
		हाल WPA_CIPHER_WEP40:
			padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP40_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
			अवरोध;
		हाल WPA_CIPHER_TKIP:
			padapter->securitypriv.करोt11PrivacyAlgrthm = _TKIP_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
			अवरोध;
		हाल WPA_CIPHER_CCMP:
			padapter->securitypriv.करोt11PrivacyAlgrthm = _AES_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
			अवरोध;
		हाल WPA_CIPHER_WEP104:
			padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP104_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
			अवरोध;
		पूर्ण

		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
		अणु/* set wps_ie */
			u16 cnt = 0;
			u8 eid, wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;

			जबतक (cnt < ielen) अणु
				eid = buf[cnt];

				अगर ((eid == WLAN_EID_VENDOR_SPECIFIC) && (!स_भेद(&buf[cnt+2], wps_oui, 4))) अणु
					padapter->securitypriv.wps_ie_len = ((buf[cnt+1]+2) < MAX_WPS_IE_LEN) ? (buf[cnt+1]+2):MAX_WPS_IE_LEN;

					स_नकल(padapter->securitypriv.wps_ie, &buf[cnt], padapter->securitypriv.wps_ie_len);

					set_fwstate(&padapter->mlmepriv, WIFI_UNDER_WPS);

					cnt += buf[cnt+1]+2;

					अवरोध;
				पूर्ण अन्यथा अणु
					cnt += buf[cnt+1]+2; /* जाओ next */
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* TKIP and AES disallow multicast packets until installing group key */
        अगर (padapter->securitypriv.करोt11PrivacyAlgrthm == _TKIP_
                || padapter->securitypriv.करोt11PrivacyAlgrthm == _TKIP_WTMIC_
                || padapter->securitypriv.करोt11PrivacyAlgrthm == _AES_)
                /* WPS खोलो need to enable multicast */
                /*  check_fwstate(&padapter->mlmepriv, WIFI_UNDER_WPS) == true) */
                rtw_hal_set_hwreg(padapter, HW_VAR_OFF_RCR_AM, null_addr);

निकास:

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_name(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	u32 ht_ielen = 0;
	अक्षर *p;
	u8 ht_cap = false, vht_cap = false;
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_bssid_ex  *pcur_bss = &pmlmepriv->cur_network.network;
	NDIS_802_11_RATES_EX *prates = शून्य;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED|WIFI_ADHOC_MASTER_STATE) == true) अणु
		/* parsing HT_CAP_IE */
		p = rtw_get_ie(&pcur_bss->IEs[12], WLAN_EID_HT_CAPABILITY, &ht_ielen, pcur_bss->IELength-12);
		अगर (p && ht_ielen > 0)
			ht_cap = true;

		prates = &pcur_bss->SupportedRates;

		अगर (rtw_is_cckratesonly_included((u8 *)prates)) अणु
			अगर (ht_cap)
				snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11bn");
			अन्यथा
				snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11b");
		पूर्ण अन्यथा अगर (rtw_is_cckrates_included((u8 *)prates)) अणु
			अगर (ht_cap)
				snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11bgn");
			अन्यथा
				snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11bg");
		पूर्ण अन्यथा अणु
			अगर (pcur_bss->Configuration.DSConfig > 14) अणु
				अगर (vht_cap)
					snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11AC");
				अन्यथा अगर (ht_cap)
					snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11an");
				अन्यथा
					snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11a");
			पूर्ण अन्यथा अणु
				अगर (ht_cap)
					snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11gn");
				अन्यथा
					snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11g");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* prates = &padapter->registrypriv.dev_network.SupportedRates; */
		/* snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11g"); */
		snम_लिखो(wrqu->name, IFNAMSIZ, "unassociated");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_freq(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_freq(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_bssid_ex  *pcur_bss = &pmlmepriv->cur_network.network;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true) अणु
		/* wrqu->freq.m = ieee80211_wlan_frequencies[pcur_bss->Configuration.DSConfig-1] * 100000; */
		wrqu->freq.m = rtw_ch2freq(pcur_bss->Configuration.DSConfig) * 100000;
		wrqu->freq.e = 1;
		wrqu->freq.i = pcur_bss->Configuration.DSConfig;

	पूर्ण अन्यथा अणु
		wrqu->freq.m = rtw_ch2freq(padapter->mlmeextpriv.cur_channel) * 100000;
		wrqu->freq.e = 1;
		wrqu->freq.i = padapter->mlmeextpriv.cur_channel;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	क्रमागत ndis_802_11_network_infraकाष्ठाure networkType;
	पूर्णांक ret = 0;

	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (!padapter->hw_init_completed) अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	चयन (wrqu->mode) अणु
	हाल IW_MODE_AUTO:
		networkType = Ndis802_11AutoUnknown;
		अवरोध;
	हाल IW_MODE_ADHOC:
		networkType = Ndis802_11IBSS;
		अवरोध;
	हाल IW_MODE_MASTER:
		networkType = Ndis802_11APMode;
		/* rtw_setopmode_cmd(padapter, networkType, true); */
		अवरोध;
	हाल IW_MODE_INFRA:
		networkType = Ndis802_11Infraकाष्ठाure;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

/*
	अगर (Ndis802_11APMode == networkType)
	अणु
		rtw_setopmode_cmd(padapter, networkType, true);
	पूर्ण
	अन्यथा
	अणु
		rtw_setopmode_cmd(padapter, Ndis802_11AutoUnknown, true);
	पूर्ण
*/

	अगर (rtw_set_802_11_infraकाष्ठाure_mode(padapter, networkType) == false) अणु

		ret = -EPERM;
		जाओ निकास;

	पूर्ण

	rtw_setopmode_cmd(padapter, networkType, true);

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true) अणु
		wrqu->mode = IW_MODE_INFRA;
	पूर्ण अन्यथा अगर  ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true) ||
		       (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true)) अणु
		wrqu->mode = IW_MODE_ADHOC;
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) अणु
		wrqu->mode = IW_MODE_MASTER;
	पूर्ण अन्यथा अणु
		wrqu->mode = IW_MODE_AUTO;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक rtw_wx_set_pmkid(काष्ठा net_device *dev,
	                     काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	u8          j, blInserted = false;
	पूर्णांक         पूर्णांकReturn = false;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
        काष्ठा iw_pmksa *pPMK = (काष्ठा iw_pmksa *)extra;
        u8     strZeroMacAddress[ETH_ALEN] = अणु 0x00 पूर्ण;
        u8     strIssueBssid[ETH_ALEN] = अणु 0x00 पूर्ण;

	/*
        There are the BSSID inक्रमmation in the bssid.sa_data array.
        If cmd is IW_PMKSA_FLUSH, it means the wpa_suppplicant wants to clear all the PMKID inक्रमmation.
        If cmd is IW_PMKSA_ADD, it means the wpa_supplicant wants to add a PMKID/BSSID to driver.
        If cmd is IW_PMKSA_REMOVE, it means the wpa_supplicant wants to हटाओ a PMKID/BSSID from driver.
        */

	स_नकल(strIssueBssid, pPMK->bssid.sa_data, ETH_ALEN);
        अगर (pPMK->cmd == IW_PMKSA_ADD) अणु
                अगर (!स_भेद(strIssueBssid, strZeroMacAddress, ETH_ALEN))
			वापस पूर्णांकReturn;
                अन्यथा
                    पूर्णांकReturn = true;

		blInserted = false;

		/* overग_लिखो PMKID */
		क्रम (j = 0; j < NUM_PMKID_CACHE; j++) अणु
			अगर (!स_भेद(psecuritypriv->PMKIDList[j].Bssid, strIssueBssid, ETH_ALEN)) अणु

				स_नकल(psecuritypriv->PMKIDList[j].PMKID, pPMK->pmkid, IW_PMKID_LEN);
                                psecuritypriv->PMKIDList[j].bUsed = true;
				psecuritypriv->PMKIDIndex = j+1;
				blInserted = true;
				अवरोध;
			पूर्ण
	        पूर्ण

	        अगर (!blInserted) अणु

	            स_नकल(psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].Bssid, strIssueBssid, ETH_ALEN);
		    स_नकल(psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].PMKID, pPMK->pmkid, IW_PMKID_LEN);

                    psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].bUsed = true;
		    psecuritypriv->PMKIDIndex++;
		    अगर (psecuritypriv->PMKIDIndex == 16)
		        psecuritypriv->PMKIDIndex = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (pPMK->cmd == IW_PMKSA_REMOVE) अणु
		पूर्णांकReturn = true;
		क्रम (j = 0; j < NUM_PMKID_CACHE; j++) अणु
			अगर (!स_भेद(psecuritypriv->PMKIDList[j].Bssid, strIssueBssid, ETH_ALEN)) अणु
				/*  BSSID is matched, the same AP => Remove this PMKID inक्रमmation and reset it. */
				eth_zero_addr(psecuritypriv->PMKIDList[j].Bssid);
				psecuritypriv->PMKIDList[j].bUsed = false;
				अवरोध;
			पूर्ण
	        पूर्ण
	पूर्ण अन्यथा अगर (pPMK->cmd == IW_PMKSA_FLUSH) अणु
		स_रखो(&psecuritypriv->PMKIDList[0], 0x00, माप(काष्ठा rt_pmkid_list) * NUM_PMKID_CACHE);
		psecuritypriv->PMKIDIndex = 0;
		पूर्णांकReturn = true;
	पूर्ण
	वापस पूर्णांकReturn;
पूर्ण

अटल पूर्णांक rtw_wx_get_sens(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	अणु
		wrqu->sens.value = 0;
		wrqu->sens.fixed = 0;	/* no स्वतः select */
		wrqu->sens.disabled = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_range(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	u16 val;
	पूर्णांक i;

	wrqu->data.length = माप(*range);
	स_रखो(range, 0, माप(*range));

	/* Let's try to keep this काष्ठा in the same order as in
	 * linux/include/wireless.h
	 */

	/* TODO: See what values we can set, and हटाओ the ones we can't
	 * set, or fill them with some शेष data.
	 */

	/* ~5 Mb/s real (802.11b) */
	range->throughput = 5 * 1000 * 1000;

	/* संकेत level threshold range */

	/* percent values between 0 and 100. */
	range->max_qual.qual = 100;
	range->max_qual.level = 100;
	range->max_qual.noise = 100;
	range->max_qual.updated = 7; /* Updated all three */


	range->avg_qual.qual = 92; /* > 8% missed beacons is 'bad' */
	/* TODO: Find real 'good' to 'bad' threshol value क्रम RSSI */
	range->avg_qual.level = 256 - 78;
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7; /* Updated all three */

	range->num_bitrates = RATE_COUNT;

	क्रम (i = 0; i < RATE_COUNT && i < IW_MAX_BITRATES; i++)
		range->bitrate[i] = rtw_rates[i];

	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;

	range->pm_capa = 0;

	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 16;

	क्रम (i = 0, val = 0; i < MAX_CHANNEL_NUM; i++) अणु

		/*  Include only legal frequencies क्रम some countries */
		अगर (pmlmeext->channel_set[i].ChannelNum != 0) अणु
			range->freq[val].i = pmlmeext->channel_set[i].ChannelNum;
			range->freq[val].m = rtw_ch2freq(pmlmeext->channel_set[i].ChannelNum) * 100000;
			range->freq[val].e = 1;
			val++;
		पूर्ण

		अगर (val == IW_MAX_FREQUENCIES)
			अवरोध;
	पूर्ण

	range->num_channels = val;
	range->num_frequency = val;

/*  Commented by Albert 2009/10/13 */
/*  The following code will proivde the security capability to network manager. */
/*  If the driver करोesn't provide this capability to network manager, */
/*  the WPA/WPA2 routers can't be chosen in the network manager. */

/*
#घोषणा IW_SCAN_CAPA_NONE		0x00
#घोषणा IW_SCAN_CAPA_ESSID		0x01
#घोषणा IW_SCAN_CAPA_BSSID		0x02
#घोषणा IW_SCAN_CAPA_CHANNEL	0x04
#घोषणा IW_SCAN_CAPA_MODE		0x08
#घोषणा IW_SCAN_CAPA_RATE		0x10
#घोषणा IW_SCAN_CAPA_TYPE		0x20
#घोषणा IW_SCAN_CAPA_TIME		0x40
*/

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
			  IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;

	range->scan_capa = IW_SCAN_CAPA_ESSID | IW_SCAN_CAPA_TYPE | IW_SCAN_CAPA_BSSID |
					IW_SCAN_CAPA_CHANNEL | IW_SCAN_CAPA_MODE | IW_SCAN_CAPA_RATE;

	वापस 0;
पूर्ण

/* set bssid flow */
/* s1. rtw_set_802_11_infraकाष्ठाure_mode() */
/* s2. rtw_set_802_11_authentication_mode() */
/* s3. set_802_11_encryption_mode() */
/* s4. rtw_set_802_11_bssid() */
अटल पूर्णांक rtw_wx_set_wap(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *awrq,
			 अक्षर *extra)
अणु
	uपूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा sockaddr *temp = (काष्ठा sockaddr *)awrq;
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा list_head	*phead;
	u8 *dst_bssid, *src_bssid;
	काष्ठा __queue	*queue	= &(pmlmepriv->scanned_queue);
	काष्ठा	wlan_network	*pnetwork = शून्य;
	क्रमागत ndis_802_11_authentication_mode	authmode;

	rtw_ps_deny(padapter, PS_DENY_JOIN);
	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	अगर (!padapter->bup) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण


	अगर (temp->sa_family != ARPHRD_ETHER) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	authmode = padapter->securitypriv.ndisauthtype;
	spin_lock_bh(&queue->lock);
	phead = get_list_head(queue);
	pmlmepriv->pscanned = get_next(phead);

	जबतक (1) अणु
		अगर (phead == pmlmepriv->pscanned)
			अवरोध;

		pnetwork = container_of(pmlmepriv->pscanned, काष्ठा wlan_network, list);

		pmlmepriv->pscanned = get_next(pmlmepriv->pscanned);

		dst_bssid = pnetwork->network.MacAddress;

		src_bssid = temp->sa_data;

		अगर ((!स_भेद(dst_bssid, src_bssid, ETH_ALEN))) अणु
			अगर (!rtw_set_802_11_infraकाष्ठाure_mode(padapter, pnetwork->network.Infraकाष्ठाureMode)) अणु
				ret = -1;
				spin_unlock_bh(&queue->lock);
				जाओ निकास;
			पूर्ण
			अवरोध;
		पूर्ण

	पूर्ण
	spin_unlock_bh(&queue->lock);

	rtw_set_802_11_authentication_mode(padapter, authmode);
	/* set_802_11_encryption_mode(padapter, padapter->securitypriv.ndisencryptstatus); */
	अगर (rtw_set_802_11_bssid(padapter, temp->sa_data) == false) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

निकास:

	rtw_ps_deny_cancel(padapter, PS_DENY_JOIN);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_wap(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_bssid_ex  *pcur_bss = &pmlmepriv->cur_network.network;

	wrqu->ap_addr.sa_family = ARPHRD_ETHER;

	eth_zero_addr(wrqu->ap_addr.sa_data);

	अगर  (((check_fwstate(pmlmepriv, _FW_LINKED)) == true) ||
			((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) == true) ||
			((check_fwstate(pmlmepriv, WIFI_AP_STATE)) == true)) अणु
		स_नकल(wrqu->ap_addr.sa_data, pcur_bss->MacAddress, ETH_ALEN);
	पूर्ण अन्यथा अणु
		eth_zero_addr(wrqu->ap_addr.sa_data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_mlme(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *)extra;


	अगर (mlme == शून्य)
		वापस -1;

	चयन (mlme->cmd) अणु
	हाल IW_MLME_DEAUTH:
		अगर (!rtw_set_802_11_disassociate(padapter))
			ret = -1;
		अवरोध;
	हाल IW_MLME_DISASSOC:
		अगर (!rtw_set_802_11_disassociate(padapter))
			ret = -1;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_set_scan(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u8 _status = false;
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ndis_802_11_ssid ssid[RTW_SSID_SCAN_AMOUNT];

	rtw_ps_deny(padapter, PS_DENY_SCAN);
	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	अगर (padapter->bDriverStopped) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	अगर (!padapter->bup) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	अगर (!padapter->hw_init_completed) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	/*  When Busy Traffic, driver करो not site survey. So driver वापस success. */
	/*  wpa_supplicant will not issue SIOCSIWSCAN cmd again after scan समयout. */
	/*  modअगरy by thomas 2011-02-22. */
	अगर (pmlmepriv->LinkDetectInfo.bBusyTraffic) अणु
		indicate_wx_scan_complete_event(padapter);
		जाओ निकास;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == true) अणु
		indicate_wx_scan_complete_event(padapter);
		जाओ निकास;
	पूर्ण

	स_रखो(ssid, 0, माप(काष्ठा ndis_802_11_ssid)*RTW_SSID_SCAN_AMOUNT);

	अगर (wrqu->data.length == माप(काष्ठा iw_scan_req)) अणु
		काष्ठा iw_scan_req *req = (काष्ठा iw_scan_req *)extra;

		अगर (wrqu->data.flags & IW_SCAN_THIS_ESSID) अणु
			पूर्णांक len = min((पूर्णांक)req->essid_len, IW_ESSID_MAX_SIZE);

			स_नकल(ssid[0].Ssid, req->essid, len);
			ssid[0].SsidLength = len;

			spin_lock_bh(&pmlmepriv->lock);

			_status = rtw_sitesurvey_cmd(padapter, ssid, 1, शून्य, 0);

			spin_unlock_bh(&pmlmepriv->lock);

		पूर्ण

	पूर्ण अन्यथा अगर (wrqu->data.length >= WEXT_CSCAN_HEADER_SIZE
		&& !स_भेद(extra, WEXT_CSCAN_HEADER, WEXT_CSCAN_HEADER_SIZE)) अणु
		पूर्णांक len = wrqu->data.length - WEXT_CSCAN_HEADER_SIZE;
		अक्षर *pos = extra+WEXT_CSCAN_HEADER_SIZE;
		अक्षर section;
		अक्षर sec_len;
		पूर्णांक ssid_index = 0;

		जबतक (len >= 1) अणु
			section = *(pos++); len -= 1;

			चयन (section) अणु
			हाल WEXT_CSCAN_SSID_SECTION:
				अगर (len < 1) अणु
					len = 0;
					अवरोध;
				पूर्ण

				sec_len = *(pos++); len -= 1;

				अगर (sec_len > 0 && sec_len <= len) अणु
					ssid[ssid_index].SsidLength = sec_len;
					स_नकल(ssid[ssid_index].Ssid, pos, ssid[ssid_index].SsidLength);
					ssid_index++;
				पूर्ण

				pos += sec_len; len -= sec_len;
				अवरोध;


			हाल WEXT_CSCAN_CHANNEL_SECTION:
				pos += 1; len -= 1;
				अवरोध;
			हाल WEXT_CSCAN_ACTV_DWELL_SECTION:
				pos += 2; len -= 2;
				अवरोध;
			हाल WEXT_CSCAN_PASV_DWELL_SECTION:
				pos += 2; len -= 2;
				अवरोध;
			हाल WEXT_CSCAN_HOME_DWELL_SECTION:
				pos += 2; len -= 2;
				अवरोध;
			हाल WEXT_CSCAN_TYPE_SECTION:
				pos += 1; len -= 1;
				अवरोध;
			शेष:
				len = 0; /*  stop parsing */
			पूर्ण
		पूर्ण

		/* jeff: it has still some scan parameter to parse, we only करो this now... */
		_status = rtw_set_802_11_bssid_list_scan(padapter, ssid, RTW_SSID_SCAN_AMOUNT);

	पूर्ण अन्यथा अणु
		_status = rtw_set_802_11_bssid_list_scan(padapter, शून्य, 0);
	पूर्ण

	अगर (_status == false)
		ret = -1;

निकास:

	rtw_ps_deny_cancel(padapter, PS_DENY_SCAN);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_scan(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा list_head					*plist, *phead;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा __queue				*queue	= &(pmlmepriv->scanned_queue);
	काष्ठा	wlan_network	*pnetwork = शून्य;
	अक्षर *ev = extra;
	अक्षर *stop = ev + wrqu->data.length;
	u32 ret = 0;
	चिन्हित पूर्णांक रुको_status;

	अगर (adapter_to_pwrctl(padapter)->brfoffbyhw && padapter->bDriverStopped) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	रुको_status = _FW_UNDER_SURVEY | _FW_UNDER_LINKING;

	अगर (check_fwstate(pmlmepriv, रुको_status))
		वापस -EAGAIN;

	spin_lock_bh(&(pmlmepriv->scanned_queue.lock));

	phead = get_list_head(queue);
	plist = get_next(phead);

	जबतक (1) अणु
		अगर (phead == plist)
			अवरोध;

		अगर ((stop - ev) < SCAN_ITEM_SIZE) अणु
			ret = -E2BIG;
			अवरोध;
		पूर्ण

		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		/* report network only अगर the current channel set contains the channel to which this network beदीर्घs */
		अगर (rtw_ch_set_search_ch(padapter->mlmeextpriv.channel_set, pnetwork->network.Configuration.DSConfig) >= 0
			&& rtw_mlme_band_check(padapter, pnetwork->network.Configuration.DSConfig) == true
			&& true == rtw_validate_ssid(&(pnetwork->network.Ssid))) अणु

			ev = translate_scan(padapter, a, pnetwork, ev, stop);
		पूर्ण

		plist = get_next(plist);

	पूर्ण

	spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));

	wrqu->data.length = ev-extra;
	wrqu->data.flags = 0;

निकास:

	वापस ret;

पूर्ण

/* set ssid flow */
/* s1. rtw_set_802_11_infraकाष्ठाure_mode() */
/* s2. set_802_11_authenticaion_mode() */
/* s3. set_802_11_encryption_mode() */
/* s4. rtw_set_802_11_ssid() */
अटल पूर्णांक rtw_wx_set_essid(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *a,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा list_head *phead;
	काष्ठा wlan_network *pnetwork = शून्य;
	क्रमागत ndis_802_11_authentication_mode authmode;
	काष्ठा ndis_802_11_ssid ndis_ssid;
	u8 *dst_ssid, *src_ssid;

	uपूर्णांक ret = 0, len;

	rtw_ps_deny(padapter, PS_DENY_JOIN);
	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	अगर (!padapter->bup) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	अगर (wrqu->essid.length > IW_ESSID_MAX_SIZE) अणु
		ret = -E2BIG;
		जाओ निकास;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	authmode = padapter->securitypriv.ndisauthtype;
	अगर (wrqu->essid.flags && wrqu->essid.length) अणु
		len = (wrqu->essid.length < IW_ESSID_MAX_SIZE) ? wrqu->essid.length : IW_ESSID_MAX_SIZE;

		स_रखो(&ndis_ssid, 0, माप(काष्ठा ndis_802_11_ssid));
		ndis_ssid.SsidLength = len;
		स_नकल(ndis_ssid.Ssid, extra, len);
		src_ssid = ndis_ssid.Ssid;

		spin_lock_bh(&queue->lock);
		phead = get_list_head(queue);
		pmlmepriv->pscanned = get_next(phead);

		जबतक (1) अणु
			अगर (phead == pmlmepriv->pscanned)
				अवरोध;

			pnetwork = container_of(pmlmepriv->pscanned, काष्ठा wlan_network, list);

			pmlmepriv->pscanned = get_next(pmlmepriv->pscanned);

			dst_ssid = pnetwork->network.Ssid.Ssid;

			अगर ((!स_भेद(dst_ssid, src_ssid, ndis_ssid.SsidLength)) &&
				(pnetwork->network.Ssid.SsidLength == ndis_ssid.SsidLength)) अणु
				अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true) अणु
					अगर (pnetwork->network.Infraकाष्ठाureMode != pmlmepriv->cur_network.network.Infraकाष्ठाureMode)
						जारी;
				पूर्ण

				अगर (rtw_set_802_11_infraकाष्ठाure_mode(padapter, pnetwork->network.Infraकाष्ठाureMode) == false) अणु
					ret = -1;
					spin_unlock_bh(&queue->lock);
					जाओ निकास;
				पूर्ण

				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&queue->lock);
		rtw_set_802_11_authentication_mode(padapter, authmode);
		/* set_802_11_encryption_mode(padapter, padapter->securitypriv.ndisencryptstatus); */
		अगर (rtw_set_802_11_ssid(padapter, &ndis_ssid) == false) अणु
			ret = -1;
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:

	rtw_ps_deny_cancel(padapter, PS_DENY_JOIN);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_essid(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *a,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u32 len, ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_bssid_ex  *pcur_bss = &pmlmepriv->cur_network.network;

	अगर ((check_fwstate(pmlmepriv, _FW_LINKED) == true) ||
	      (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)) अणु
		len = pcur_bss->Ssid.SsidLength;

		wrqu->essid.length = len;

		स_नकल(extra, pcur_bss->Ssid.Ssid, len);

		wrqu->essid.flags = 1;
	पूर्ण अन्यथा अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_set_rate(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *a,
			      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक	i, ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	u8 datarates[NumRates];
	u32 target_rate = wrqu->bitrate.value;
	u32 fixed = wrqu->bitrate.fixed;
	u32 ratevalue = 0;
	u8 mpdatarate[NumRates] = अणु11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0xffपूर्ण;

	अगर (target_rate == -1) अणु
		ratevalue = 11;
		जाओ set_rate;
	पूर्ण
	target_rate = target_rate/100000;

	चयन (target_rate) अणु
	हाल 10:
		ratevalue = 0;
		अवरोध;
	हाल 20:
		ratevalue = 1;
		अवरोध;
	हाल 55:
		ratevalue = 2;
		अवरोध;
	हाल 60:
		ratevalue = 3;
		अवरोध;
	हाल 90:
		ratevalue = 4;
		अवरोध;
	हाल 110:
		ratevalue = 5;
		अवरोध;
	हाल 120:
		ratevalue = 6;
		अवरोध;
	हाल 180:
		ratevalue = 7;
		अवरोध;
	हाल 240:
		ratevalue = 8;
		अवरोध;
	हाल 360:
		ratevalue = 9;
		अवरोध;
	हाल 480:
		ratevalue = 10;
		अवरोध;
	हाल 540:
		ratevalue = 11;
		अवरोध;
	शेष:
		ratevalue = 11;
		अवरोध;
	पूर्ण

set_rate:

	क्रम (i = 0; i < NumRates; i++) अणु
		अगर (ratevalue == mpdatarate[i]) अणु
			datarates[i] = mpdatarate[i];
			अगर (fixed == 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			datarates[i] = 0xff;
		पूर्ण
	पूर्ण

	अगर (rtw_setdatarate_cmd(padapter, datarates) != _SUCCESS)
		ret = -1;

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_rate(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u16 max_rate = 0;

	max_rate = rtw_get_cur_max_rate(rtw_netdev_priv(dev));

	अगर (max_rate == 0)
		वापस -EPERM;

	wrqu->bitrate.fixed = 0;	/* no स्वतः select */
	wrqu->bitrate.value = max_rate * 100000;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_rts(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	अगर (wrqu->rts.disabled)
		padapter->registrypriv.rts_thresh = 2347;
	अन्यथा अणु
		अगर (wrqu->rts.value < 0 ||
		    wrqu->rts.value > 2347)
			वापस -EINVAL;

		padapter->registrypriv.rts_thresh = wrqu->rts.value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_rts(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	wrqu->rts.value = padapter->registrypriv.rts_thresh;
	wrqu->rts.fixed = 0;	/* no स्वतः select */
	/* wrqu->rts.disabled = (wrqu->rts.value == DEFAULT_RTS_THRESHOLD); */

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_frag(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	अगर (wrqu->frag.disabled)
		padapter->xmitpriv.frag_len = MAX_FRAG_THRESHOLD;
	अन्यथा अणु
		अगर (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD)
			वापस -EINVAL;

		padapter->xmitpriv.frag_len = wrqu->frag.value & ~0x1;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rtw_wx_get_frag(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	wrqu->frag.value = padapter->xmitpriv.frag_len;
	wrqu->frag.fixed = 0;	/* no स्वतः select */
	/* wrqu->frag.disabled = (wrqu->frag.value == DEFAULT_FRAG_THRESHOLD); */

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_retry(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/* काष्ठा adapter *padapter = rtw_netdev_priv(dev); */


	wrqu->retry.value = 7;
	wrqu->retry.fixed = 0;	/* no स्वतः select */
	wrqu->retry.disabled = 1;

	वापस 0;

पूर्ण

अटल पूर्णांक rtw_wx_set_enc(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	u32 key, ret = 0;
	u32 keyindex_provided;
	काष्ठा ndis_802_11_wep	 wep;
	क्रमागत ndis_802_11_authentication_mode authmode;

	काष्ठा iw_poपूर्णांक *erq = &(wrqu->encoding);
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);

	स_रखो(&wep, 0, माप(काष्ठा ndis_802_11_wep));

	key = erq->flags & IW_ENCODE_INDEX;

	अगर (erq->flags & IW_ENCODE_DISABLED) अणु
		padapter->securitypriv.ndisencryptstatus = Ndis802_11EncryptionDisabled;
		padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open; /* खोलो प्रणाली */
		authmode = Ndis802_11AuthModeOpen;
		padapter->securitypriv.ndisauthtype = authmode;

		जाओ निकास;
	पूर्ण

	अगर (key) अणु
		अगर (key > WEP_KEYS)
			वापस -EINVAL;
		key--;
		keyindex_provided = 1;
	पूर्ण अन्यथा अणु
		keyindex_provided = 0;
		key = padapter->securitypriv.करोt11PrivacyKeyIndex;
	पूर्ण

	/* set authentication mode */
	अगर (erq->flags & IW_ENCODE_OPEN) अणु
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;/* Ndis802_11EncryptionDisabled; */

		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;

		padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
		authmode = Ndis802_11AuthModeOpen;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण अन्यथा अगर (erq->flags & IW_ENCODE_RESTRICTED) अणु
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;

		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Shared;

		padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP40_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _WEP40_;
		authmode = Ndis802_11AuthModeShared;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण अन्यथा अणु
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;/* Ndis802_11EncryptionDisabled; */
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open; /* खोलो प्रणाली */
		padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
		authmode = Ndis802_11AuthModeOpen;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण

	wep.KeyIndex = key;
	अगर (erq->length > 0) अणु
		wep.KeyLength = erq->length <= 5 ? 5 : 13;

		wep.Length = wep.KeyLength + FIELD_OFFSET(काष्ठा ndis_802_11_wep, KeyMaterial);
	पूर्ण अन्यथा अणु
		wep.KeyLength = 0;

		अगर (keyindex_provided == 1) अणु /*  set key_id only, no given KeyMaterial(erq->length == 0). */
			padapter->securitypriv.करोt11PrivacyKeyIndex = key;

			चयन (padapter->securitypriv.करोt11DefKeylen[key]) अणु
			हाल 5:
				padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP40_;
				अवरोध;
			हाल 13:
				padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP104_;
				अवरोध;
			शेष:
				padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
				अवरोध;
			पूर्ण

			जाओ निकास;

		पूर्ण

	पूर्ण

	wep.KeyIndex |= 0x80000000;

	स_नकल(wep.KeyMaterial, keybuf, wep.KeyLength);

	अगर (rtw_set_802_11_add_wep(padapter, &wep) == false) अणु
		अगर (rf_on == pwrpriv->rf_pwrstate)
			ret = -EOPNOTSUPP;
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_enc(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	uपूर्णांक key, ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *erq = &(wrqu->encoding);
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) != true) अणु
		 अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) != true) अणु
			 erq->length = 0;
			 erq->flags |= IW_ENCODE_DISABLED;
			 वापस 0;
		 पूर्ण
	पूर्ण


	key = erq->flags & IW_ENCODE_INDEX;

	अगर (key) अणु
		अगर (key > WEP_KEYS)
			वापस -EINVAL;
		key--;
	पूर्ण अन्यथा अणु
		key = padapter->securitypriv.करोt11PrivacyKeyIndex;
	पूर्ण

	erq->flags = key + 1;

	/* अगर (padapter->securitypriv.ndisauthtype == Ndis802_11AuthModeOpen) */
	/*  */
	/*       erq->flags |= IW_ENCODE_OPEN; */
	/*  */

	चयन (padapter->securitypriv.ndisencryptstatus) अणु
	हाल Ndis802_11EncryptionNotSupported:
	हाल Ndis802_11EncryptionDisabled:
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		अवरोध;
	हाल Ndis802_11Encryption1Enabled:
		erq->length = padapter->securitypriv.करोt11DefKeylen[key];

		अगर (erq->length) अणु
			स_नकल(keybuf, padapter->securitypriv.करोt11DefKey[key].skey, padapter->securitypriv.करोt11DefKeylen[key]);

			erq->flags |= IW_ENCODE_ENABLED;

			अगर (padapter->securitypriv.ndisauthtype == Ndis802_11AuthModeOpen)
				erq->flags |= IW_ENCODE_OPEN;
			अन्यथा अगर (padapter->securitypriv.ndisauthtype == Ndis802_11AuthModeShared)
				erq->flags |= IW_ENCODE_RESTRICTED;
		पूर्ण अन्यथा अणु
			erq->length = 0;
			erq->flags |= IW_ENCODE_DISABLED;
		पूर्ण
		अवरोध;
	हाल Ndis802_11Encryption2Enabled:
	हाल Ndis802_11Encryption3Enabled:
		erq->length = 16;
		erq->flags |= (IW_ENCODE_ENABLED | IW_ENCODE_OPEN | IW_ENCODE_NOKEY);
		अवरोध;
	शेष:
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_घातer(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/* काष्ठा adapter *padapter = rtw_netdev_priv(dev); */

	wrqu->घातer.value = 0;
	wrqu->घातer.fixed = 0;	/* no स्वतः select */
	wrqu->घातer.disabled = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_gen_ie(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	वापस rtw_set_wpa_ie(padapter, extra, wrqu->data.length);
पूर्ण

अटल पूर्णांक rtw_wx_set_auth(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा iw_param *param = (काष्ठा iw_param *)&(wrqu->param);
	पूर्णांक ret = 0;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
		अवरोध;
	हाल IW_AUTH_CIPHER_PAIRWISE:
		अवरोध;
	हाल IW_AUTH_CIPHER_GROUP:
		अवरोध;
	हाल IW_AUTH_KEY_MGMT:
		/*
		 *  ??? करोes not use these parameters
		 */
		अवरोध;
	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		/* wpa_supplicant is setting the tkip countermeasure. */
		अगर (param->value) /* enabling */
			padapter->securitypriv.btkip_countermeasure = true;
		अन्यथा /* disabling */
			padapter->securitypriv.btkip_countermeasure = false;
		अवरोध;
	हाल IW_AUTH_DROP_UNENCRYPTED:
		/* HACK:
		 *
		 * wpa_supplicant calls set_wpa_enabled when the driver
		 * is loaded and unloaded, regardless of अगर WPA is being
		 * used.  No other calls are made which can be used to
		 * determine अगर encryption will be used or not prior to
		 * association being expected.  If encryption is not being
		 * used, drop_unencrypted is set to false, अन्यथा true -- we
		 * can use this to determine अगर the CAP_PRIVACY_ON bit should
		 * be set.
		 */

		/*
		 * This means init value, or using wep, ndisencryptstatus =
		 * Ndis802_11Encryption1Enabled, then it needn't reset it;
		 */
		अगर (padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption1Enabled)
			अवरोध;

		अगर (param->value) अणु
			padapter->securitypriv.ndisencryptstatus = Ndis802_11EncryptionDisabled;
			padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
			padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
			padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open; /* खोलो प्रणाली */
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
		पूर्ण

		अवरोध;
	हाल IW_AUTH_80211_AUTH_ALG:
		/*
		 *  It's the starting poपूर्णांक of a link layer connection using wpa_supplicant
		 */
		अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
			LeaveAllPowerSaveMode(padapter);
			rtw_disassoc_cmd(padapter, 500, false);
			rtw_indicate_disconnect(padapter);
			rtw_मुक्त_assoc_resources(padapter, 1);
		पूर्ण

		ret = wpa_set_auth_algs(dev, (u32)param->value);
		अवरोध;
	हाल IW_AUTH_WPA_ENABLED:
		अवरोध;
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		अवरोध;
	हाल IW_AUTH_PRIVACY_INVOKED:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_set_enc_ext(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	अक्षर *alg_name;
	u32 param_len;
	काष्ठा ieee_param *param = शून्य;
	काष्ठा iw_poपूर्णांक *pencoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *pext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक ret = 0;

	param_len = माप(काष्ठा ieee_param) + pext->key_len;
	param = kzalloc(param_len, GFP_KERNEL);
	अगर (param == शून्य)
		वापस -1;

	param->cmd = IEEE_CMD_SET_ENCRYPTION;
	स_रखो(param->sta_addr, 0xff, ETH_ALEN);


	चयन (pext->alg) अणु
	हाल IW_ENCODE_ALG_NONE:
		/* toकरो: हटाओ key */
		/* हटाओ = 1; */
		alg_name = "none";
		अवरोध;
	हाल IW_ENCODE_ALG_WEP:
		alg_name = "WEP";
		अवरोध;
	हाल IW_ENCODE_ALG_TKIP:
		alg_name = "TKIP";
		अवरोध;
	हाल IW_ENCODE_ALG_CCMP:
		alg_name = "CCMP";
		अवरोध;
	हाल IW_ENCODE_ALG_AES_CMAC:
		alg_name = "BIP";
		अवरोध;
	शेष:
		ret = -1;
		जाओ निकास;
	पूर्ण

	म_नकलन((अक्षर *)param->u.crypt.alg, alg_name, IEEE_CRYPT_ALG_NAME_LEN);

	अगर (pext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY)
		param->u.crypt.set_tx = 1;

	/* cliW: WEP करोes not have group key
	 * just not checking GROUP key setting
	 */
	अगर ((pext->alg != IW_ENCODE_ALG_WEP) &&
		((pext->ext_flags & IW_ENCODE_EXT_GROUP_KEY)
		|| (pext->ext_flags & IW_ENCODE_ALG_AES_CMAC)))	अणु
		param->u.crypt.set_tx = 0;
	पूर्ण

	param->u.crypt.idx = (pencoding->flags & 0x00FF) - 1;

	अगर (pext->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID)
		स_नकल(param->u.crypt.seq, pext->rx_seq, 8);

	अगर (pext->key_len) अणु
		param->u.crypt.key_len = pext->key_len;
		/* स_नकल(param + 1, pext + 1, pext->key_len); */
		स_नकल(param->u.crypt.key, pext + 1, pext->key_len);
	पूर्ण

	अगर (pencoding->flags & IW_ENCODE_DISABLED) अणु
		/* toकरो: हटाओ key */
		/* हटाओ = 1; */
	पूर्ण

	ret =  wpa_set_encryption(dev, param, param_len);

निकास:
	kमुक्त(param);

	वापस ret;
पूर्ण


अटल पूर्णांक rtw_wx_get_nick(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	/* काष्ठा adapter *padapter = rtw_netdev_priv(dev); */
	 /* काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv); */
	 /* काष्ठा security_priv *psecuritypriv = &padapter->securitypriv; */

	अगर (extra) अणु
		wrqu->data.length = 14;
		wrqu->data.flags = 1;
		स_नकल(extra, "<WIFI@REALTEK>", 14);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_पढ़ो32(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter;
	काष्ठा iw_poपूर्णांक *p;
	u16 len;
	u32 addr;
	u32 data32;
	u32 bytes;
	u8 *pपंचांगp;
	पूर्णांक ret;


	ret = 0;
	padapter = rtw_netdev_priv(dev);
	p = &wrqu->data;
	len = p->length;
	अगर (0 == len)
		वापस -EINVAL;

	pपंचांगp = rtw_दो_स्मृति(len);
	अगर (शून्य == pपंचांगp)
		वापस -ENOMEM;

	अगर (copy_from_user(pपंचांगp, p->poपूर्णांकer, len)) अणु
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण

	bytes = 0;
	addr = 0;
	माला_पूछो(pपंचांगp, "%d,%x", &bytes, &addr);

	चयन (bytes) अणु
	हाल 1:
		data32 = rtw_पढ़ो8(padapter, addr);
		प्र_लिखो(extra, "0x%02X", data32);
		अवरोध;
	हाल 2:
		data32 = rtw_पढ़ो16(padapter, addr);
		प्र_लिखो(extra, "0x%04X", data32);
		अवरोध;
	हाल 4:
		data32 = rtw_पढ़ो32(padapter, addr);
		प्र_लिखो(extra, "0x%08X", data32);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

निकास:
	kमुक्त(pपंचांगp);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_ग_लिखो32(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	u32 addr;
	u32 data32;
	u32 bytes;


	bytes = 0;
	addr = 0;
	data32 = 0;
	माला_पूछो(extra, "%d,%x,%x", &bytes, &addr, &data32);

	चयन (bytes) अणु
	हाल 1:
		rtw_ग_लिखो8(padapter, addr, (u8)data32);
		अवरोध;
	हाल 2:
		rtw_ग_लिखो16(padapter, addr, (u16)data32);
		अवरोध;
	हाल 4:
		rtw_ग_लिखो32(padapter, addr, data32);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_पढ़ो_rf(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	u32 path, addr, data32;


	path = *(u32 *)extra;
	addr = *((u32 *)extra + 1);
	data32 = rtw_hal_पढ़ो_rfreg(padapter, path, addr, 0xFFFFF);
	/*
	 * IMPORTANT!!
	 * Only when wireless निजी ioctl is at odd order,
	 * "extra" would be copied to user space.
	 */
	प्र_लिखो(extra, "0x%05x", data32);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_ग_लिखो_rf(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	u32 path, addr, data32;


	path = *(u32 *)extra;
	addr = *((u32 *)extra + 1);
	data32 = *((u32 *)extra + 2);
	rtw_hal_ग_लिखो_rfreg(padapter, path, addr, 0xFFFFF, data32);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_priv_null(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
		 जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक dummy(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
		 जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	/* काष्ठा adapter *padapter = rtw_netdev_priv(dev); */
	/* काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv); */

	वापस -1;

पूर्ण

अटल पूर्णांक rtw_wx_set_channel_plan(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info,
				   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	u8 channel_plan_req = (u8)(*((पूर्णांक *)wrqu));

	अगर (rtw_set_chplan_cmd(padapter, channel_plan_req, 1, 1) != _SUCCESS)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_mtk_wps_probe_ie(काष्ठा net_device *dev,
		काष्ठा iw_request_info *a,
		जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_sensitivity(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_mtk_wps_ie(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	वापस 0;
पूर्ण

/*
प्रकार पूर्णांक (*iw_handler)(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra);
*/
/*
 *For all data larger than 16 octets, we need to use a
 *poपूर्णांकer to memory allocated in user space.
 */
अटल  पूर्णांक rtw_drvext_hdl(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
						जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_get_ap_info(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	पूर्णांक wpa_ielen;
	u32 cnt = 0;
	काष्ठा list_head	*plist, *phead;
	अचिन्हित अक्षर *pbuf;
	u8 bssid[ETH_ALEN];
	अक्षर data[32];
	काष्ठा wlan_network *pnetwork = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा __queue *queue = &(pmlmepriv->scanned_queue);
	काष्ठा iw_poपूर्णांक *pdata = &wrqu->data;

	अगर ((padapter->bDriverStopped) || (pdata == शून्य)) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	जबतक ((check_fwstate(pmlmepriv, (_FW_UNDER_SURVEY|_FW_UNDER_LINKING))) == true) अणु
		msleep(30);
		cnt++;
		अगर (cnt > 100)
			अवरोध;
	पूर्ण


	/* pdata->length = 0;? */
	pdata->flags = 0;
	अगर (pdata->length >= 32) अणु
		अगर (copy_from_user(data, pdata->poपूर्णांकer, 32)) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&(pmlmepriv->scanned_queue.lock));

	phead = get_list_head(queue);
	plist = get_next(phead);

	जबतक (1) अणु
		अगर (phead == plist)
			अवरोध;


		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		अगर (!mac_pton(data, bssid)) अणु
			spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
			वापस -EINVAL;
		पूर्ण


		अगर (!स_भेद(bssid, pnetwork->network.MacAddress, ETH_ALEN)) अणु /* BSSID match, then check अगर supporting wpa/wpa2 */

			pbuf = rtw_get_wpa_ie(&pnetwork->network.IEs[12], &wpa_ielen, pnetwork->network.IELength-12);
			अगर (pbuf && (wpa_ielen > 0)) अणु
				pdata->flags = 1;
				अवरोध;
			पूर्ण

			pbuf = rtw_get_wpa2_ie(&pnetwork->network.IEs[12], &wpa_ielen, pnetwork->network.IELength-12);
			अगर (pbuf && (wpa_ielen > 0)) अणु
				pdata->flags = 2;
				अवरोध;
			पूर्ण
		पूर्ण

		plist = get_next(plist);

	पूर्ण

	spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));

	अगर (pdata->length >= 34) अणु
		अगर (copy_to_user((u8 __क्रमce __user *)pdata->poपूर्णांकer+32, (u8 *)&pdata->flags, 1)) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_set_pid(काष्ठा net_device *dev,
		       काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	पूर्णांक *pdata = (पूर्णांक *)wrqu;
	पूर्णांक selector;

	अगर ((padapter->bDriverStopped) || (pdata == शून्य)) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	selector = *pdata;
	अगर (selector < 3 && selector >= 0)
		padapter->pid[selector] = *(pdata+1);

निकास:

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_wps_start(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *pdata = &wrqu->data;
	u32   u32wps_start = 0;

	अगर ((true == padapter->bDriverStopped) || (true == padapter->bSurpriseRemoved) || (शून्य == pdata)) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (copy_from_user((व्योम *)&u32wps_start, pdata->poपूर्णांकer, 4)) अणु
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण
	अगर (u32wps_start == 0)
		u32wps_start = *extra;

निकास:

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_p2p_set(काष्ठा net_device *dev,
		       काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	वापस 0;

पूर्ण

अटल पूर्णांक rtw_p2p_get(काष्ठा net_device *dev,
		       काष्ठा iw_request_info *info,
		       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	वापस 0;

पूर्ण

अटल पूर्णांक rtw_p2p_get2(काष्ठा net_device *dev,
						काष्ठा iw_request_info *info,
						जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु

	वापस 0;

पूर्ण

अटल पूर्णांक rtw_rereg_nd_name(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा rereg_nd_name_data *rereg_priv = &padapter->rereg_nd_name_priv;
	अक्षर new_अगरname[IFNAMSIZ];

	अगर (rereg_priv->old_अगरname[0] == 0) अणु
		अक्षर *reg_अगरname;
		reg_अगरname = padapter->registrypriv.अगरname;

		म_नकलन(rereg_priv->old_अगरname, reg_अगरname, IFNAMSIZ);
		rereg_priv->old_अगरname[IFNAMSIZ-1] = 0;
	पूर्ण

	अगर (wrqu->data.length > IFNAMSIZ)
		वापस -EFAULT;

	अगर (copy_from_user(new_अगरname, wrqu->data.poपूर्णांकer, IFNAMSIZ))
		वापस -EFAULT;

	अगर (0 == म_भेद(rereg_priv->old_अगरname, new_अगरname))
		वापस ret;

	ret = rtw_change_अगरname(padapter, new_अगरname);
	अगर (ret != 0)
		जाओ निकास;

	म_नकलन(rereg_priv->old_अगरname, new_अगरname, IFNAMSIZ);
	rereg_priv->old_अगरname[IFNAMSIZ-1] = 0;

	अगर (!स_भेद(new_अगरname, "disable%d", 9)) अणु
		/*  मुक्त network queue क्रम Android's timming issue */
		rtw_मुक्त_network_queue(padapter, true);

		/*  the पूर्णांकerface is being "disabled", we can करो deeper IPS */
		/* rtw_ips_mode_req(&padapter->pwrctrlpriv, IPS_NORMAL); */
	पूर्ण
निकास:
	वापस ret;

पूर्ण

अटल पूर्णांक rtw_dbg_port(काष्ठा net_device *dev,
			काष्ठा iw_request_info *info,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u8 major_cmd, minor_cmd;
	u16 arg;
	u32 extra_arg, *pdata, val32;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	pdata = (u32 *)&wrqu->data;

	val32 = *pdata;
	arg = (u16)(val32&0x0000ffff);
	major_cmd = (u8)(val32>>24);
	minor_cmd = (u8)((val32>>16)&0x00ff);

	extra_arg = *(pdata+1);

	चयन (major_cmd) अणु
		हाल 0x70:/* पढ़ो_reg */
			चयन (minor_cmd) अणु
				हाल 1:
					अवरोध;
				हाल 2:
					अवरोध;
				हाल 4:
					अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x71:/* ग_लिखो_reg */
			चयन (minor_cmd) अणु
				हाल 1:
					rtw_ग_लिखो8(padapter, arg, extra_arg);
					अवरोध;
				हाल 2:
					rtw_ग_लिखो16(padapter, arg, extra_arg);
					अवरोध;
				हाल 4:
					rtw_ग_लिखो32(padapter, arg, extra_arg);
					अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x72:/* पढ़ो_bb */
			अवरोध;
		हाल 0x73:/* ग_लिखो_bb */
			rtw_hal_ग_लिखो_bbreg(padapter, arg, 0xffffffff, extra_arg);
			अवरोध;
		हाल 0x74:/* पढ़ो_rf */
			अवरोध;
		हाल 0x75:/* ग_लिखो_rf */
			rtw_hal_ग_लिखो_rfreg(padapter, minor_cmd, arg, 0xffffffff, extra_arg);
			अवरोध;

		हाल 0x76:
			चयन (minor_cmd) अणु
				हाल 0x00: /* normal mode, */
					padapter->recvpriv.is_संकेत_dbg = 0;
					अवरोध;
				हाल 0x01: /* dbg mode */
					padapter->recvpriv.is_संकेत_dbg = 1;
					extra_arg = extra_arg > 100 ? 100 : extra_arg;
					padapter->recvpriv.संकेत_strength_dbg = extra_arg;
					अवरोध;
			पूर्ण
			अवरोध;
		हाल 0x78: /* IOL test */
			अवरोध;
		हाल 0x79:
			अणु
				/*
				* dbg 0x79000000 [value], set RESP_TXAGC to + value, value:0~15
				* dbg 0x79010000 [value], set RESP_TXAGC to - value, value:0~15
				*/
				u8 value =  extra_arg & 0x0f;
				u8 sign = minor_cmd;
				u16 ग_लिखो_value = 0;

				अगर (sign)
					value = value | 0x10;

				ग_लिखो_value = value | (value << 5);
				rtw_ग_लिखो16(padapter, 0x6d9, ग_लिखो_value);
			पूर्ण
			अवरोध;
		हाल 0x7a:
			receive_disconnect(padapter, pmlmeinfo->network.MacAddress
				, WLAN_REASON_EXPIRATION_CHK);
			अवरोध;
		हाल 0x7F:
			चयन (minor_cmd) अणु
				हाल 0x0:
					अवरोध;
				हाल 0x01:
					अवरोध;
				हाल 0x02:
					अवरोध;
				हाल 0x03:
					अवरोध;
				हाल 0x04:

					अवरोध;
				हाल 0x05:
					अवरोध;
				हाल 0x06:
					अणु
						u32 ODMFlag;
						rtw_hal_get_hwreg(padapter, HW_VAR_DM_FLAG, (u8 *)(&ODMFlag));
						ODMFlag = (u32)(0x0f&arg);
						rtw_hal_set_hwreg(padapter, HW_VAR_DM_FLAG, (u8 *)(&ODMFlag));
					पूर्ण
					अवरोध;
				हाल 0x07:
					अवरोध;
				हाल 0x08:
					अणु
					पूर्ण
					अवरोध;
				हाल 0x09:
					अवरोध;
				हाल 0x0a:
					अणु
						पूर्णांक max_mac_id = 0;
						max_mac_id = rtw_search_max_mac_id(padapter);
						prपूर्णांकk("%s ==> max_mac_id = %d\n", __func__, max_mac_id);
					पूर्ण
					अवरोध;
				हाल 0x0b: /* Enable = 1, Disable = 0 driver control vrtl_carrier_sense. */
					अगर (arg == 0) अणु
						padapter->driver_vcs_en = 0;
					पूर्ण अन्यथा अगर (arg == 1) अणु
						padapter->driver_vcs_en = 1;

						अगर (extra_arg > 2)
							padapter->driver_vcs_type = 1;
						अन्यथा
							padapter->driver_vcs_type = extra_arg;
					पूर्ण
					अवरोध;
				हाल 0x0c:/* dump rx/tx packet */
					अणु
						अगर (arg == 0)
							/* pHalData->bDumpRxPkt =extra_arg; */
							rtw_hal_set_def_var(padapter, HAL_DEF_DBG_DUMP_RXPKT, &(extra_arg));
						अन्यथा अगर (arg == 1)
							rtw_hal_set_def_var(padapter, HAL_DEF_DBG_DUMP_TXPKT, &(extra_arg));
					पूर्ण
					अवरोध;
				हाल 0x0e:
					अणु
						अगर (arg == 0) अणु
							padapter->driver_rx_ampdu_factor = 0xFF;
						पूर्ण अन्यथा अगर (arg == 1) अणु

							अगर ((extra_arg & 0x03) > 0x03)
								padapter->driver_rx_ampdu_factor = 0xFF;
							अन्यथा
								padapter->driver_rx_ampdu_factor = extra_arg;
						पूर्ण
					पूर्ण
					अवरोध;

				हाल 0x10:/*  driver version display */
					netdev_dbg(dev, "%s %s\n", "rtl8723bs", DRIVERVERSION);
					अवरोध;
				हाल 0x11:/* dump linked status */
					अणु
						 linked_info_dump(padapter, extra_arg);
					पूर्ण
					अवरोध;
				हाल 0x12: /* set rx_stbc */
				अणु
					काष्ठा registry_priv *pregpriv = &padapter->registrypriv;
					/*  0: disable, bit(0):enable 2.4g, bit(1):enable 5g, 0x3: enable both 2.4g and 5g */
					/* शेष is set to enable 2.4GHZ क्रम IOT issue with bufflao's AP at 5GHZ */
					अगर (extra_arg == 0 || extra_arg == 1 ||
					    extra_arg == 2 || extra_arg == 3)
						pregpriv->rx_stbc = extra_arg;
				पूर्ण
				अवरोध;
				हाल 0x13: /* set ampdu_enable */
				अणु
					काष्ठा registry_priv *pregpriv = &padapter->registrypriv;
					/*  0: disable, 0x1:enable (but wअगरi_spec should be 0), 0x2: क्रमce enable (करोn't care wअगरi_spec) */
					अगर (extra_arg < 3)
						pregpriv->ampdu_enable = extra_arg;
				पूर्ण
				अवरोध;
				हाल 0x14:
				अणु
				पूर्ण
				अवरोध;
				हाल 0x16:
				अणु
					अगर (arg == 0xff) अणु
						rtw_odm_dbg_comp_msg(padapter);
					पूर्ण अन्यथा अणु
						u64 dbg_comp = (u64)extra_arg;
						rtw_odm_dbg_comp_set(padapter, dbg_comp);
					पूर्ण
				पूर्ण
					अवरोध;
#अगर_घोषित DBG_FIXED_CHAN
				हाल 0x17:
					अणु
						काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
						prपूर्णांकk("===>  Fixed channel to %d\n", extra_arg);
						pmlmeext->fixed_chan = extra_arg;

					पूर्ण
					अवरोध;
#पूर्ण_अगर
				हाल 0x18:
					अणु
						prपूर्णांकk("===>  Switch USB Mode %d\n", extra_arg);
						rtw_hal_set_hwreg(padapter, HW_VAR_USB_MODE, (u8 *)&extra_arg);
					पूर्ण
					अवरोध;
				हाल 0x19:
					अणु
						काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
						/*  extra_arg : */
						/*  BIT0: Enable VHT LDPC Rx, BIT1: Enable VHT LDPC Tx, */
						/*  BIT4: Enable HT LDPC Rx, BIT5: Enable HT LDPC Tx */
						अगर (arg == 0)
							pregistrypriv->ldpc_cap = 0x00;
						अन्यथा अगर (arg == 1)
							pregistrypriv->ldpc_cap = (u8)(extra_arg&0x33);
					पूर्ण
					अवरोध;
				हाल 0x1a:
					अणु
						काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
						/*  extra_arg : */
						/*  BIT0: Enable VHT STBC Rx, BIT1: Enable VHT STBC Tx, */
						/*  BIT4: Enable HT STBC Rx, BIT5: Enable HT STBC Tx */
						अगर (arg == 0)
							pregistrypriv->stbc_cap = 0x00;
						अन्यथा अगर (arg == 1)
							pregistrypriv->stbc_cap = (u8)(extra_arg&0x33);
					पूर्ण
					अवरोध;
				हाल 0x1b:
					अणु
						काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;

						अगर (arg == 0) अणु
							init_mlme_शेष_rate_set(padapter);
							pregistrypriv->ht_enable = (u8)rtw_ht_enable;
						पूर्ण अन्यथा अगर (arg == 1) अणु

							पूर्णांक i;
							u8 max_rx_rate;

							max_rx_rate = (u8)extra_arg;

							अगर (max_rx_rate < 0xc) अणु /*  max_rx_rate < MSC0 -> B or G -> disable HT */
								pregistrypriv->ht_enable = 0;
								क्रम (i = 0; i < NumRates; i++) अणु
									अगर (pmlmeext->datarate[i] > max_rx_rate)
										pmlmeext->datarate[i] = 0xff;
								पूर्ण

							पूर्ण
							अन्यथा अगर (max_rx_rate < 0x1c) अणु /*  mcs0~mcs15 */
								u32 mcs_biपंचांगap = 0x0;

								क्रम (i = 0; i < ((max_rx_rate + 1) - 0xc); i++)
									mcs_biपंचांगap |= BIT(i);

								set_mcs_rate_by_mask(pmlmeext->शेष_supported_mcs_set, mcs_biपंचांगap);
							पूर्ण
						पूर्ण
					पूर्ण
					अवरोध;
				हाल 0x1c: /* enable/disable driver control AMPDU Density क्रम peer sta's rx */
					अणु
						अगर (arg == 0) अणु
							padapter->driver_ampdu_spacing = 0xFF;
						पूर्ण अन्यथा अगर (arg == 1) अणु

							अगर (extra_arg > 0x07)
								padapter->driver_ampdu_spacing = 0xFF;
							अन्यथा
								padapter->driver_ampdu_spacing = extra_arg;
						पूर्ण
					पूर्ण
					अवरोध;
				हाल 0x23:
					अणु
						padapter->bNotअगरyChannelChange = extra_arg;
						अवरोध;
					पूर्ण
				हाल 0x24:
					अणु
						अवरोध;
					पूर्ण
				हाल 0xaa:
					अणु
						अगर ((extra_arg & 0x7F) > 0x3F)
							extra_arg = 0xFF;
						padapter->fix_rate = extra_arg;
					पूर्ण
					अवरोध;
				हाल 0xdd:/* रेजिस्टरs dump , 0 क्रम mac reg, 1 क्रम bb reg, 2 क्रम rf reg */
					अणु
						अगर (extra_arg == 0)
							mac_reg_dump(RTW_DBGDUMP, padapter);
						अन्यथा अगर (extra_arg == 1)
							bb_reg_dump(RTW_DBGDUMP, padapter);
						अन्यथा अगर (extra_arg == 2)
							rf_reg_dump(RTW_DBGDUMP, padapter);
					पूर्ण
					अवरोध;

				हाल 0xee:/* turn on/off dynamic funcs */
					अणु
						u32 odm_flag;

						अगर (0xf == extra_arg) अणु
							rtw_hal_get_def_var(padapter, HAL_DEF_DBG_DM_FUNC, &odm_flag);
						पूर्ण अन्यथा अणु
							/*extra_arg = 0  - disable all dynamic func
								extra_arg = 1  - disable DIG
								extra_arg = 2  - disable tx घातer tracking
								extra_arg = 3  - turn on all dynamic func
							*/
							rtw_hal_set_def_var(padapter, HAL_DEF_DBG_DM_FUNC, &(extra_arg));
							rtw_hal_get_def_var(padapter, HAL_DEF_DBG_DM_FUNC, &odm_flag);
						पूर्ण
					पूर्ण
					अवरोध;

				हाल 0xfd:
					rtw_ग_लिखो8(padapter, 0xc50, arg);
					rtw_ग_लिखो8(padapter, 0xc58, arg);
					अवरोध;
				हाल 0xfe:
					अवरोध;
				हाल 0xff:
					अणु
					पूर्ण
					अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण


	वापस 0;

पूर्ण

अटल पूर्णांक wpa_set_param(काष्ठा net_device *dev, u8 name, u32 value)
अणु
	uपूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	चयन (name) अणु
	हाल IEEE_PARAM_WPA_ENABLED:

		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X; /* 802.1x */

		/* ret = ieee80211_wpa_enable(ieee, value); */

		चयन ((value)&0xff) अणु
		हाल 1: /* WPA */
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPAPSK; /* WPA_PSK */
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
			अवरोध;
		हाल 2: /* WPA2 */
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPA2PSK; /* WPA2_PSK */
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल IEEE_PARAM_TKIP_COUNTERMEASURES:
		/* ieee->tkip_countermeasures =value; */
		अवरोध;

	हाल IEEE_PARAM_DROP_UNENCRYPTED:
	अणु
		/* HACK:
		 *
		 * wpa_supplicant calls set_wpa_enabled when the driver
		 * is loaded and unloaded, regardless of अगर WPA is being
		 * used.  No other calls are made which can be used to
		 * determine अगर encryption will be used or not prior to
		 * association being expected.  If encryption is not being
		 * used, drop_unencrypted is set to false, अन्यथा true -- we
		 * can use this to determine अगर the CAP_PRIVACY_ON bit should
		 * be set.
		 */
		अवरोध;

	पूर्ण
	हाल IEEE_PARAM_PRIVACY_INVOKED:

		/* ieee->privacy_invoked =value; */

		अवरोध;

	हाल IEEE_PARAM_AUTH_ALGS:

		ret = wpa_set_auth_algs(dev, value);

		अवरोध;

	हाल IEEE_PARAM_IEEE_802_1X:

		/* ieee->ieee802_1x =value; */

		अवरोध;

	हाल IEEE_PARAM_WPAX_SELECT:

		/*  added क्रम WPA2 mixed mode */
		/*
		spin_lock_irqsave(&ieee->wpax_suitlist_lock, flags);
		ieee->wpax_type_set = 1;
		ieee->wpax_type_notअगरy = value;
		spin_unlock_irqrestore(&ieee->wpax_suitlist_lock, flags);
		*/

		अवरोध;

	शेष:



		ret = -EOPNOTSUPP;


		अवरोध;

	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक wpa_mlme(काष्ठा net_device *dev, u32 command, u32 reason)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	चयन (command) अणु
	हाल IEEE_MLME_STA_DEAUTH:

		अगर (!rtw_set_802_11_disassociate(padapter))
			ret = -1;

		अवरोध;

	हाल IEEE_MLME_STA_DISASSOC:

		अगर (!rtw_set_802_11_disassociate(padapter))
			ret = -1;

		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक wpa_supplicant_ioctl(काष्ठा net_device *dev, काष्ठा iw_poपूर्णांक *p)
अणु
	काष्ठा ieee_param *param;
	uपूर्णांक ret = 0;

	/* करोwn(&ieee->wx_sem); */

	अगर (!p->poपूर्णांकer || p->length != माप(काष्ठा ieee_param))
		वापस -EINVAL;

	param = rtw_दो_स्मृति(p->length);
	अगर (param == शून्य)
		वापस -ENOMEM;

	अगर (copy_from_user(param, p->poपूर्णांकer, p->length)) अणु
		kमुक्त(param);
		वापस -EFAULT;
	पूर्ण

	चयन (param->cmd) अणु

	हाल IEEE_CMD_SET_WPA_PARAM:
		ret = wpa_set_param(dev, param->u.wpa_param.name, param->u.wpa_param.value);
		अवरोध;

	हाल IEEE_CMD_SET_WPA_IE:
		/* ret = wpa_set_wpa_ie(dev, param, p->length); */
		ret =  rtw_set_wpa_ie(rtw_netdev_priv(dev), (अक्षर *)param->u.wpa_ie.data, (u16)param->u.wpa_ie.len);
		अवरोध;

	हाल IEEE_CMD_SET_ENCRYPTION:
		ret = wpa_set_encryption(dev, param, p->length);
		अवरोध;

	हाल IEEE_CMD_MLME:
		ret = wpa_mlme(dev, param->u.mlme.command, param->u.mlme.reason_code);
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;

	पूर्ण

	अगर (ret == 0 && copy_to_user(p->poपूर्णांकer, param, p->length))
		ret = -EFAULT;

	kमुक्त(param);

	/* up(&ieee->wx_sem); */
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_set_encryption(काष्ठा net_device *dev, काष्ठा ieee_param *param, u32 param_len)
अणु
	पूर्णांक ret = 0;
	u32 wep_key_idx, wep_key_len, wep_total_len;
	काष्ठा ndis_802_11_wep	 *pwep = शून्य;
	काष्ठा sta_info *psta = शून्य, *pbcmc_sta = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &(padapter->securitypriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	अक्षर *txkey = padapter->securitypriv.करोt118021XGrptxmickey[param->u.crypt.idx].skey;
	अक्षर *rxkey = padapter->securitypriv.करोt118021XGrprxmickey[param->u.crypt.idx].skey;
	अक्षर *grpkey = psecuritypriv->करोt118021XGrpKey[param->u.crypt.idx].skey;

	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';

	/* माप(काष्ठा ieee_param) = 64 bytes; */
	/* अगर (param_len !=  (u32) ((u8 *) param->u.crypt.key - (u8 *) param) + param->u.crypt.key_len) */
	अगर (param_len !=  माप(काष्ठा ieee_param) + param->u.crypt.key_len) अणु
		ret =  -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff) अणु
		अगर (param->u.crypt.idx >= WEP_KEYS) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		psta = rtw_get_stainfo(pstapriv, param->sta_addr);
		अगर (!psta)
			/* ret = -EINVAL; */
			जाओ निकास;
	पूर्ण

	अगर (म_भेद(param->u.crypt.alg, "none") == 0 && (psta == शून्य)) अणु
		/* toकरो:clear शेष encryption keys */

		psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
		psecuritypriv->ndisencryptstatus = Ndis802_11EncryptionDisabled;
		psecuritypriv->करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;

		जाओ निकास;
	पूर्ण


	अगर (म_भेद(param->u.crypt.alg, "WEP") == 0 && (psta == शून्य)) अणु
		wep_key_idx = param->u.crypt.idx;
		wep_key_len = param->u.crypt.key_len;

		अगर ((wep_key_idx >= WEP_KEYS) || (wep_key_len <= 0)) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण


		अगर (wep_key_len > 0) अणु
			wep_key_len = wep_key_len <= 5 ? 5 : 13;
			wep_total_len = wep_key_len + FIELD_OFFSET(काष्ठा ndis_802_11_wep, KeyMaterial);
			pwep = kzalloc(wep_total_len, GFP_KERNEL);
			अगर (!pwep)
				जाओ निकास;

			pwep->KeyLength = wep_key_len;
			pwep->Length = wep_total_len;

		पूर्ण

		pwep->KeyIndex = wep_key_idx;

		स_नकल(pwep->KeyMaterial,  param->u.crypt.key, pwep->KeyLength);

		अगर (param->u.crypt.set_tx) अणु
			psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Auto;
			psecuritypriv->ndisencryptstatus = Ndis802_11Encryption1Enabled;
			psecuritypriv->करोt11PrivacyAlgrthm = _WEP40_;
			psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;

			अगर (pwep->KeyLength == 13) अणु
				psecuritypriv->करोt11PrivacyAlgrthm = _WEP104_;
				psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
			पूर्ण


			psecuritypriv->करोt11PrivacyKeyIndex = wep_key_idx;

			स_नकल(&(psecuritypriv->करोt11DefKey[wep_key_idx].skey[0]), pwep->KeyMaterial, pwep->KeyLength);

			psecuritypriv->करोt11DefKeylen[wep_key_idx] = pwep->KeyLength;

			rtw_ap_set_wep_key(padapter, pwep->KeyMaterial, pwep->KeyLength, wep_key_idx, 1);
		पूर्ण अन्यथा अणु
			/* करोn't update "psecuritypriv->dot11PrivacyAlgrthm" and */
			/* psecuritypriv->करोt11PrivacyKeyIndex =keyid", but can rtw_set_key to cam */

			स_नकल(&(psecuritypriv->करोt11DefKey[wep_key_idx].skey[0]), pwep->KeyMaterial, pwep->KeyLength);

			psecuritypriv->करोt11DefKeylen[wep_key_idx] = pwep->KeyLength;

			rtw_ap_set_wep_key(padapter, pwep->KeyMaterial, pwep->KeyLength, wep_key_idx, 0);
		पूर्ण

		जाओ निकास;

	पूर्ण


	अगर (!psta && check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु /*  group key */
		अगर (param->u.crypt.set_tx == 1) अणु
			अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
				स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

				psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;
				अगर (param->u.crypt.key_len == 13)
						psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;

			पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु
				psecuritypriv->करोt118021XGrpPrivacy = _TKIP_;

				स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

				/* DEBUG_ERR("set key length :param->u.crypt.key_len =%d\n", param->u.crypt.key_len); */
				/* set mic key */
				स_नकल(txkey, &(param->u.crypt.key[16]), 8);
				स_नकल(psecuritypriv->करोt118021XGrprxmickey[param->u.crypt.idx].skey, &(param->u.crypt.key[24]), 8);

				psecuritypriv->busetkipkey = true;

			पूर्ण
			अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु
				psecuritypriv->करोt118021XGrpPrivacy = _AES_;

				स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));
			पूर्ण अन्यथा अणु
				psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
			पूर्ण

			psecuritypriv->करोt118021XGrpKeyid = param->u.crypt.idx;

			psecuritypriv->binstallGrpkey = true;

			psecuritypriv->करोt11PrivacyAlgrthm = psecuritypriv->करोt118021XGrpPrivacy;/*  */

			rtw_ap_set_group_key(padapter, param->u.crypt.key, psecuritypriv->करोt118021XGrpPrivacy, param->u.crypt.idx);

			pbcmc_sta = rtw_get_bcmc_stainfo(padapter);
			अगर (pbcmc_sta) अणु
				pbcmc_sta->ieee8021x_blocked = false;
				pbcmc_sta->करोt118021XPrivacy = psecuritypriv->करोt118021XGrpPrivacy;/* rx will use bmc_sta's करोt118021XPrivacy */
			पूर्ण
		पूर्ण

		जाओ निकास;

	पूर्ण

	अगर (psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X && psta) अणु /*  psk/802_1x */
		अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
			अगर (param->u.crypt.set_tx == 1)	अणु
				स_नकल(psta->करोt118021x_UncstKey.skey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

				अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
					psta->करोt118021XPrivacy = _WEP40_;
					अगर (param->u.crypt.key_len == 13)
						psta->करोt118021XPrivacy = _WEP104_;
				पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु
					psta->करोt118021XPrivacy = _TKIP_;

					/* DEBUG_ERR("set key length :param->u.crypt.key_len =%d\n", param->u.crypt.key_len); */
					/* set mic key */
					स_नकल(psta->करोt11tkiptxmickey.skey, &(param->u.crypt.key[16]), 8);
					स_नकल(psta->करोt11tkiprxmickey.skey, &(param->u.crypt.key[24]), 8);

					psecuritypriv->busetkipkey = true;

				पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु

					psta->करोt118021XPrivacy = _AES_;
				पूर्ण अन्यथा अणु
					psta->करोt118021XPrivacy = _NO_PRIVACY_;
				पूर्ण

				rtw_ap_set_pairwise_key(padapter, psta);

				psta->ieee8021x_blocked = false;

			पूर्ण अन्यथा अणु /* group key??? */
				अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
					स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

					psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;
					अगर (param->u.crypt.key_len == 13)
						psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
				पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु
					psecuritypriv->करोt118021XGrpPrivacy = _TKIP_;

					स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

					/* DEBUG_ERR("set key length :param->u.crypt.key_len =%d\n", param->u.crypt.key_len); */
					/* set mic key */
					स_नकल(txkey, &(param->u.crypt.key[16]), 8);
					स_नकल(rxkey, &(param->u.crypt.key[24]), 8);

					psecuritypriv->busetkipkey = true;

				पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु
					psecuritypriv->करोt118021XGrpPrivacy = _AES_;

					स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));
				पूर्ण अन्यथा अणु
					psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
				पूर्ण

				psecuritypriv->करोt118021XGrpKeyid = param->u.crypt.idx;

				psecuritypriv->binstallGrpkey = true;

				psecuritypriv->करोt11PrivacyAlgrthm = psecuritypriv->करोt118021XGrpPrivacy;/*  */

				rtw_ap_set_group_key(padapter, param->u.crypt.key, psecuritypriv->करोt118021XGrpPrivacy, param->u.crypt.idx);

				pbcmc_sta = rtw_get_bcmc_stainfo(padapter);
				अगर (pbcmc_sta) अणु
					pbcmc_sta->ieee8021x_blocked = false;
					pbcmc_sta->करोt118021XPrivacy = psecuritypriv->करोt118021XGrpPrivacy;/* rx will use bmc_sta's करोt118021XPrivacy */
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

निकास:
	kमुक्त(pwep);

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_set_beacon(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	अचिन्हित अक्षर *pbuf = param->u.bcn_ie.buf;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) != true)
		वापस -EINVAL;

	स_नकल(&pstapriv->max_num_sta, param->u.bcn_ie.reserved, 2);

	अगर ((pstapriv->max_num_sta > NUM_STA) || (pstapriv->max_num_sta <= 0))
		pstapriv->max_num_sta = NUM_STA;


	अगर (rtw_check_beacon_data(padapter, pbuf,  (len-12-2)) == _SUCCESS)/*  12 = param header, 2:no packed */
		ret = 0;
	अन्यथा
		ret = -EINVAL;


	वापस ret;

पूर्ण

अटल व्योम rtw_hostapd_sta_flush(काष्ठा net_device *dev)
अणु
	/* _irqL irqL; */
	/* काष्ठा list_head	*phead, *plist; */
	/* काष्ठा sta_info *psta = शून्य; */
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	/* काष्ठा sta_priv *pstapriv = &padapter->stapriv; */

	flush_all_cam_entry(padapter);	/* clear CAM */

	rtw_sta_flush(padapter);
पूर्ण

अटल पूर्णांक rtw_add_sta(काष्ठा net_device *dev, काष्ठा ieee_param *param)
अणु
	पूर्णांक ret = 0;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	अगर (check_fwstate(pmlmepriv, (_FW_LINKED|WIFI_AP_STATE)) != true)
		वापस -EINVAL;

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff) अणु
		वापस -EINVAL;
	पूर्ण

/*
	psta = rtw_get_stainfo(pstapriv, param->sta_addr);
	अगर (psta)
	अणु
		spin_lock_bh(&(pstapriv->sta_hash_lock));
		rtw_मुक्त_stainfo(padapter,  psta);
		spin_unlock_bh(&(pstapriv->sta_hash_lock));

		psta = शून्य;
	पूर्ण
*/
	/* psta = rtw_alloc_stainfo(pstapriv, param->sta_addr); */
	psta = rtw_get_stainfo(pstapriv, param->sta_addr);
	अगर (psta) अणु
		पूर्णांक flags = param->u.add_sta.flags;

		psta->aid = param->u.add_sta.aid;/* aid = 1~2007 */

		स_नकल(psta->bssrateset, param->u.add_sta.tx_supp_rates, 16);


		/* check wmm cap. */
		अगर (WLAN_STA_WME&flags)
			psta->qos_option = 1;
		अन्यथा
			psta->qos_option = 0;

		अगर (pmlmepriv->qospriv.qos_option == 0)
			psta->qos_option = 0;

		/* chec 802.11n ht cap. */
		अगर (WLAN_STA_HT&flags) अणु
			psta->htpriv.ht_option = true;
			psta->qos_option = 1;
			स_नकल((व्योम *)&psta->htpriv.ht_cap, (व्योम *)&param->u.add_sta.ht_cap, माप(काष्ठा ieee80211_ht_cap));
		पूर्ण अन्यथा अणु
			psta->htpriv.ht_option = false;
		पूर्ण

		अगर (pmlmepriv->htpriv.ht_option == false)
			psta->htpriv.ht_option = false;

		update_sta_info_apmode(padapter, psta);


	पूर्ण अन्यथा अणु
		ret = -ENOMEM;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_del_sta(काष्ठा net_device *dev, काष्ठा ieee_param *param)
अणु
	पूर्णांक ret = 0;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	अगर (check_fwstate(pmlmepriv, (_FW_LINKED|WIFI_AP_STATE)) != true)
		वापस -EINVAL;

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff) अणु
		वापस -EINVAL;
	पूर्ण

	psta = rtw_get_stainfo(pstapriv, param->sta_addr);
	अगर (psta) अणु
		u8 updated = false;

		spin_lock_bh(&pstapriv->asoc_list_lock);
		अगर (list_empty(&psta->asoc_list) == false) अणु
			list_del_init(&psta->asoc_list);
			pstapriv->asoc_list_cnt--;
			updated = ap_मुक्त_sta(padapter, psta, true, WLAN_REASON_DEAUTH_LEAVING);

		पूर्ण
		spin_unlock_bh(&pstapriv->asoc_list_lock);

		associated_clients_update(padapter, updated);

		psta = शून्य;

	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_ioctl_get_sta_data(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा ieee_param_ex *param_ex = (काष्ठा ieee_param_ex *)param;
	काष्ठा sta_data *psta_data = (काष्ठा sta_data *)param_ex->data;

	अगर (check_fwstate(pmlmepriv, (_FW_LINKED|WIFI_AP_STATE)) != true)
		वापस -EINVAL;

	अगर (param_ex->sta_addr[0] == 0xff && param_ex->sta_addr[1] == 0xff &&
	    param_ex->sta_addr[2] == 0xff && param_ex->sta_addr[3] == 0xff &&
	    param_ex->sta_addr[4] == 0xff && param_ex->sta_addr[5] == 0xff) अणु
		वापस -EINVAL;
	पूर्ण

	psta = rtw_get_stainfo(pstapriv, param_ex->sta_addr);
	अगर (psta) अणु
		psta_data->aid = (u16)psta->aid;
		psta_data->capability = psta->capability;
		psta_data->flags = psta->flags;

/*
		nonerp_set : BIT(0)
		no_लघु_slot_समय_set : BIT(1)
		no_लघु_preamble_set : BIT(2)
		no_ht_gf_set : BIT(3)
		no_ht_set : BIT(4)
		ht_20mhz_set : BIT(5)
*/

		psta_data->sta_set = ((psta->nonerp_set) |
							 (psta->no_लघु_slot_समय_set << 1) |
							 (psta->no_लघु_preamble_set << 2) |
							 (psta->no_ht_gf_set << 3) |
							 (psta->no_ht_set << 4) |
							 (psta->ht_20mhz_set << 5));

		psta_data->tx_supp_rates_len =  psta->bssratelen;
		स_नकल(psta_data->tx_supp_rates, psta->bssrateset, psta->bssratelen);
		स_नकल(&psta_data->ht_cap, &psta->htpriv.ht_cap, माप(काष्ठा ieee80211_ht_cap));
		psta_data->rx_pkts = psta->sta_stats.rx_data_pkts;
		psta_data->rx_bytes = psta->sta_stats.rx_bytes;
		psta_data->rx_drops = psta->sta_stats.rx_drops;

		psta_data->tx_pkts = psta->sta_stats.tx_pkts;
		psta_data->tx_bytes = psta->sta_stats.tx_bytes;
		psta_data->tx_drops = psta->sta_stats.tx_drops;


	पूर्ण अन्यथा अणु
		ret = -1;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_get_sta_wpaie(काष्ठा net_device *dev, काष्ठा ieee_param *param)
अणु
	पूर्णांक ret = 0;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	अगर (check_fwstate(pmlmepriv, (_FW_LINKED|WIFI_AP_STATE)) != true)
		वापस -EINVAL;

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff) अणु
		वापस -EINVAL;
	पूर्ण

	psta = rtw_get_stainfo(pstapriv, param->sta_addr);
	अगर (psta) अणु
		अगर ((psta->wpa_ie[0] == WLAN_EID_RSN) || (psta->wpa_ie[0] == WLAN_EID_VENDOR_SPECIFIC)) अणु
			पूर्णांक wpa_ie_len;
			पूर्णांक copy_len;

			wpa_ie_len = psta->wpa_ie[1];

			copy_len = ((wpa_ie_len+2) > माप(psta->wpa_ie)) ? (माप(psta->wpa_ie)):(wpa_ie_len+2);

			param->u.wpa_ie.len = copy_len;

			स_नकल(param->u.wpa_ie.reserved, psta->wpa_ie, copy_len);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -1;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_set_wps_beacon(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	अचिन्हित अक्षर wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	पूर्णांक ie_len;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) != true)
		वापस -EINVAL;

	ie_len = len-12-2;/*  12 = param header, 2:no packed */


	kमुक्त(pmlmepriv->wps_beacon_ie);
	pmlmepriv->wps_beacon_ie = शून्य;

	अगर (ie_len > 0) अणु
		pmlmepriv->wps_beacon_ie = rtw_दो_स्मृति(ie_len);
		pmlmepriv->wps_beacon_ie_len = ie_len;
		अगर (!pmlmepriv->wps_beacon_ie)
			वापस -EINVAL;

		स_नकल(pmlmepriv->wps_beacon_ie, param->u.bcn_ie.buf, ie_len);

		update_beacon(padapter, WLAN_EID_VENDOR_SPECIFIC, wps_oui, true);

		pmlmeext->bstart_bss = true;
	पूर्ण


	वापस ret;

पूर्ण

अटल पूर्णांक rtw_set_wps_probe_resp(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	पूर्णांक ie_len;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) != true)
		वापस -EINVAL;

	ie_len = len-12-2;/*  12 = param header, 2:no packed */


	kमुक्त(pmlmepriv->wps_probe_resp_ie);
	pmlmepriv->wps_probe_resp_ie = शून्य;

	अगर (ie_len > 0) अणु
		pmlmepriv->wps_probe_resp_ie = rtw_दो_स्मृति(ie_len);
		pmlmepriv->wps_probe_resp_ie_len = ie_len;
		अगर (!pmlmepriv->wps_probe_resp_ie)
			वापस -EINVAL;

		स_नकल(pmlmepriv->wps_probe_resp_ie, param->u.bcn_ie.buf, ie_len);
	पूर्ण


	वापस ret;

पूर्ण

अटल पूर्णांक rtw_set_wps_assoc_resp(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	पूर्णांक ie_len;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) != true)
		वापस -EINVAL;

	ie_len = len-12-2;/*  12 = param header, 2:no packed */


	kमुक्त(pmlmepriv->wps_assoc_resp_ie);
	pmlmepriv->wps_assoc_resp_ie = शून्य;

	अगर (ie_len > 0) अणु
		pmlmepriv->wps_assoc_resp_ie = rtw_दो_स्मृति(ie_len);
		pmlmepriv->wps_assoc_resp_ie_len = ie_len;
		अगर (!pmlmepriv->wps_assoc_resp_ie)
			वापस -EINVAL;

		स_नकल(pmlmepriv->wps_assoc_resp_ie, param->u.bcn_ie.buf, ie_len);
	पूर्ण


	वापस ret;

पूर्ण

अटल पूर्णांक rtw_set_hidden_ssid(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *adapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *mlmepriv = &(adapter->mlmepriv);
	काष्ठा mlme_ext_priv *mlmeext = &(adapter->mlmeextpriv);
	काष्ठा mlme_ext_info *mlmeinfo = &(mlmeext->mlmext_info);
	पूर्णांक ie_len;
	u8 *ssid_ie;
	अक्षर ssid[NDIS_802_11_LENGTH_SSID + 1];
	चिन्हित पूर्णांक ssid_len;
	u8 ignore_broadcast_ssid;

	अगर (check_fwstate(mlmepriv, WIFI_AP_STATE) != true)
		वापस -EPERM;

	अगर (param->u.bcn_ie.reserved[0] != 0xea)
		वापस -EINVAL;

	mlmeinfo->hidden_ssid_mode = ignore_broadcast_ssid = param->u.bcn_ie.reserved[1];

	ie_len = len-12-2;/*  12 = param header, 2:no packed */
	ssid_ie = rtw_get_ie(param->u.bcn_ie.buf,  WLAN_EID_SSID, &ssid_len, ie_len);

	अगर (ssid_ie && ssid_len > 0 && ssid_len <= NDIS_802_11_LENGTH_SSID) अणु
		काष्ठा wlan_bssid_ex *pbss_network = &mlmepriv->cur_network.network;
		काष्ठा wlan_bssid_ex *pbss_network_ext = &mlmeinfo->network;

		स_नकल(ssid, ssid_ie+2, ssid_len);
		ssid[ssid_len] = 0x0;

		स_नकल(pbss_network->Ssid.Ssid, (व्योम *)ssid, ssid_len);
		pbss_network->Ssid.SsidLength = ssid_len;
		स_नकल(pbss_network_ext->Ssid.Ssid, (व्योम *)ssid, ssid_len);
		pbss_network_ext->Ssid.SsidLength = ssid_len;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_ioctl_acl_हटाओ_sta(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) != true)
		वापस -EINVAL;

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff) अणु
		वापस -EINVAL;
	पूर्ण

	rtw_acl_हटाओ_sta(padapter, param->sta_addr);
	वापस 0;

पूर्ण

अटल पूर्णांक rtw_ioctl_acl_add_sta(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) != true)
		वापस -EINVAL;

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff) अणु
		वापस -EINVAL;
	पूर्ण

	वापस rtw_acl_add_sta(padapter, param->sta_addr);

पूर्ण

अटल पूर्णांक rtw_ioctl_set_macaddr_acl(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) != true)
		वापस -EINVAL;

	rtw_set_macaddr_acl(padapter, param->u.mlme.command);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_hostapd_ioctl(काष्ठा net_device *dev, काष्ठा iw_poपूर्णांक *p)
अणु
	काष्ठा ieee_param *param;
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	/*
	* this function is expect to call in master mode, which allows no घातer saving
	* so, we just check hw_init_completed
	*/

	अगर (!padapter->hw_init_completed)
		वापस -EPERM;

	अगर (!p->poपूर्णांकer || p->length != माप(*param))
		वापस -EINVAL;

	param = rtw_दो_स्मृति(p->length);
	अगर (param == शून्य)
		वापस -ENOMEM;

	अगर (copy_from_user(param, p->poपूर्णांकer, p->length)) अणु
		kमुक्त(param);
		वापस -EFAULT;
	पूर्ण

	चयन (param->cmd) अणु
	हाल RTL871X_HOSTAPD_FLUSH:

		rtw_hostapd_sta_flush(dev);

		अवरोध;

	हाल RTL871X_HOSTAPD_ADD_STA:

		ret = rtw_add_sta(dev, param);

		अवरोध;

	हाल RTL871X_HOSTAPD_REMOVE_STA:

		ret = rtw_del_sta(dev, param);

		अवरोध;

	हाल RTL871X_HOSTAPD_SET_BEACON:

		ret = rtw_set_beacon(dev, param, p->length);

		अवरोध;

	हाल RTL871X_SET_ENCRYPTION:

		ret = rtw_set_encryption(dev, param, p->length);

		अवरोध;

	हाल RTL871X_HOSTAPD_GET_WPAIE_STA:

		ret = rtw_get_sta_wpaie(dev, param);

		अवरोध;

	हाल RTL871X_HOSTAPD_SET_WPS_BEACON:

		ret = rtw_set_wps_beacon(dev, param, p->length);

		अवरोध;

	हाल RTL871X_HOSTAPD_SET_WPS_PROBE_RESP:

		ret = rtw_set_wps_probe_resp(dev, param, p->length);

		अवरोध;

	हाल RTL871X_HOSTAPD_SET_WPS_ASSOC_RESP:

		ret = rtw_set_wps_assoc_resp(dev, param, p->length);

		अवरोध;

	हाल RTL871X_HOSTAPD_SET_HIDDEN_SSID:

		ret = rtw_set_hidden_ssid(dev, param, p->length);

		अवरोध;

	हाल RTL871X_HOSTAPD_GET_INFO_STA:

		ret = rtw_ioctl_get_sta_data(dev, param, p->length);

		अवरोध;

	हाल RTL871X_HOSTAPD_SET_MACADDR_ACL:

		ret = rtw_ioctl_set_macaddr_acl(dev, param, p->length);

		अवरोध;

	हाल RTL871X_HOSTAPD_ACL_ADD_STA:

		ret = rtw_ioctl_acl_add_sta(dev, param, p->length);

		अवरोध;

	हाल RTL871X_HOSTAPD_ACL_REMOVE_STA:

		ret = rtw_ioctl_acl_हटाओ_sta(dev, param, p->length);

		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;

	पूर्ण

	अगर (ret == 0 && copy_to_user(p->poपूर्णांकer, param, p->length))
		ret = -EFAULT;

	kमुक्त(param);
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_set_priv(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *awrq,
				अक्षर *extra)
अणु

#अगर_घोषित DEBUG_RTW_WX_SET_PRIV
	अक्षर *ext_dbg;
#पूर्ण_अगर

	पूर्णांक ret = 0;
	पूर्णांक len = 0;
	अक्षर *ext;

	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *dwrq = (काष्ठा iw_poपूर्णांक *)awrq;

	अगर (dwrq->length == 0)
		वापस -EFAULT;

	len = dwrq->length;
	ext = vदो_स्मृति(len);
	अगर (!ext)
		वापस -ENOMEM;

	अगर (copy_from_user(ext, dwrq->poपूर्णांकer, len)) अणु
		vमुक्त(ext);
		वापस -EFAULT;
	पूर्ण

	#अगर_घोषित DEBUG_RTW_WX_SET_PRIV
	ext_dbg = vदो_स्मृति(len);
	अगर (!ext_dbg) अणु
		vमुक्त(ext, len);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(ext_dbg, ext, len);
	#पूर्ण_अगर

	/* added क्रम wps2.0 @20110524 */
	अगर (dwrq->flags == 0x8766 && len > 8) अणु
		u32 cp_sz;
		काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
		u8 *probereq_wpsie = ext;
		पूर्णांक probereq_wpsie_len = len;
		u8 wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;

		अगर ((WLAN_EID_VENDOR_SPECIFIC == probereq_wpsie[0]) &&
			(!स_भेद(&probereq_wpsie[2], wps_oui, 4))) अणु
			cp_sz = probereq_wpsie_len > MAX_WPS_IE_LEN ? MAX_WPS_IE_LEN : probereq_wpsie_len;

			अगर (pmlmepriv->wps_probe_req_ie) अणु
				pmlmepriv->wps_probe_req_ie_len = 0;
				kमुक्त(pmlmepriv->wps_probe_req_ie);
				pmlmepriv->wps_probe_req_ie = शून्य;
			पूर्ण

			pmlmepriv->wps_probe_req_ie = rtw_दो_स्मृति(cp_sz);
			अगर (pmlmepriv->wps_probe_req_ie == शून्य) अणु
				prपूर्णांकk("%s()-%d: rtw_malloc() ERROR!\n", __func__, __LINE__);
				ret =  -EINVAL;
				जाओ FREE_EXT;

			पूर्ण

			स_नकल(pmlmepriv->wps_probe_req_ie, probereq_wpsie, cp_sz);
			pmlmepriv->wps_probe_req_ie_len = cp_sz;

		पूर्ण

		जाओ FREE_EXT;

	पूर्ण

	अगर (len >= WEXT_CSCAN_HEADER_SIZE
		&& !स_भेद(ext, WEXT_CSCAN_HEADER, WEXT_CSCAN_HEADER_SIZE)) अणु
		ret = rtw_wx_set_scan(dev, info, awrq, ext);
		जाओ FREE_EXT;
	पूर्ण

FREE_EXT:

	vमुक्त(ext);
	#अगर_घोषित DEBUG_RTW_WX_SET_PRIV
	vमुक्त(ext_dbg);
	#पूर्ण_अगर

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_pm_set(काष्ठा net_device *dev,
		      काष्ठा iw_request_info *info,
		      जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	अचिन्हित	mode = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);

	अगर (!स_भेद(extra, "lps =", 4)) अणु
		माला_पूछो(extra+4, "%u", &mode);
		ret = rtw_pm_set_lps(padapter, mode);
	पूर्ण अन्यथा अगर (!स_भेद(extra, "ips =", 4)) अणु
		माला_पूछो(extra+4, "%u", &mode);
		ret = rtw_pm_set_ips(padapter, mode);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_test(
	काष्ठा net_device *dev,
	काष्ठा iw_request_info *info,
	जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u32 len;
	u8 *pbuf, *pch;
	अक्षर *pपंचांगp;
	u8 *delim = ",";
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);


	len = wrqu->data.length;

	pbuf = rtw_zदो_स्मृति(len);
	अगर (!pbuf)
		वापस -ENOMEM;

	अगर (copy_from_user(pbuf, wrqu->data.poपूर्णांकer, len)) अणु
		kमुक्त(pbuf);
		वापस -EFAULT;
	पूर्ण

	pपंचांगp = (अक्षर *)pbuf;
	pch = strsep(&pपंचांगp, delim);
	अगर ((pch == शून्य) || (म_माप(pch) == 0)) अणु
		kमुक्त(pbuf);
		वापस -EFAULT;
	पूर्ण

	अगर (म_भेद(pch, "bton") == 0)
		hal_btcoex_SetManualControl(padapter, false);

	अगर (म_भेद(pch, "btoff") == 0)
		hal_btcoex_SetManualControl(padapter, true);

	अगर (म_भेद(pch, "h2c") == 0) अणु
		u8 param[8];
		u8 count = 0;
		u32 पंचांगp;
		u8 i;
		u32 pos;
		s32 ret;


		करो अणु
			pch = strsep(&pपंचांगp, delim);
			अगर ((pch == शून्य) || (म_माप(pch) == 0))
				अवरोध;

			माला_पूछो(pch, "%x", &पंचांगp);
			param[count++] = (u8)पंचांगp;
		पूर्ण जबतक (count < 8);

		अगर (count == 0) अणु
			kमुक्त(pbuf);
			वापस -EFAULT;
		पूर्ण

		ret = rtw_hal_fill_h2c_cmd(padapter, param[0], count-1, &param[1]);

		pos = प्र_लिखो(extra, "H2C ID = 0x%02x content =", param[0]);
		क्रम (i = 1; i < count; i++)
			pos += प्र_लिखो(extra+pos, "%02x,", param[i]);
		extra[pos] = 0;
		pos--;
		pos += प्र_लिखो(extra+pos, " %s", ret == _FAIL?"FAIL":"OK");

		wrqu->data.length = म_माप(extra) + 1;
	पूर्ण

	kमुक्त(pbuf);
	वापस 0;
पूर्ण

अटल iw_handler rtw_handlers[] = अणु
	शून्य,					/* SIOCSIWCOMMIT */
	rtw_wx_get_name,		/* SIOCGIWNAME */
	dummy,					/* SIOCSIWNWID */
	dummy,					/* SIOCGIWNWID */
	rtw_wx_set_freq,		/* SIOCSIWFREQ */
	rtw_wx_get_freq,		/* SIOCGIWFREQ */
	rtw_wx_set_mode,		/* SIOCSIWMODE */
	rtw_wx_get_mode,		/* SIOCGIWMODE */
	dummy,					/* SIOCSIWSENS */
	rtw_wx_get_sens,		/* SIOCGIWSENS */
	शून्य,					/* SIOCSIWRANGE */
	rtw_wx_get_range,		/* SIOCGIWRANGE */
	rtw_wx_set_priv,		/* SIOCSIWPRIV */
	शून्य,					/* SIOCGIWPRIV */
	शून्य,					/* SIOCSIWSTATS */
	शून्य,					/* SIOCGIWSTATS */
	dummy,					/* SIOCSIWSPY */
	dummy,					/* SIOCGIWSPY */
	शून्य,					/* SIOCGIWTHRSPY */
	शून्य,					/* SIOCWIWTHRSPY */
	rtw_wx_set_wap,		/* SIOCSIWAP */
	rtw_wx_get_wap,		/* SIOCGIWAP */
	rtw_wx_set_mlme,		/* request MLME operation; uses काष्ठा iw_mlme */
	dummy,					/* SIOCGIWAPLIST -- depricated */
	rtw_wx_set_scan,		/* SIOCSIWSCAN */
	rtw_wx_get_scan,		/* SIOCGIWSCAN */
	rtw_wx_set_essid,		/* SIOCSIWESSID */
	rtw_wx_get_essid,		/* SIOCGIWESSID */
	dummy,					/* SIOCSIWNICKN */
	rtw_wx_get_nick,		/* SIOCGIWNICKN */
	शून्य,					/* -- hole -- */
	शून्य,					/* -- hole -- */
	rtw_wx_set_rate,		/* SIOCSIWRATE */
	rtw_wx_get_rate,		/* SIOCGIWRATE */
	rtw_wx_set_rts,			/* SIOCSIWRTS */
	rtw_wx_get_rts,			/* SIOCGIWRTS */
	rtw_wx_set_frag,		/* SIOCSIWFRAG */
	rtw_wx_get_frag,		/* SIOCGIWFRAG */
	dummy,					/* SIOCSIWTXPOW */
	dummy,					/* SIOCGIWTXPOW */
	dummy,					/* SIOCSIWRETRY */
	rtw_wx_get_retry,		/* SIOCGIWRETRY */
	rtw_wx_set_enc,			/* SIOCSIWENCODE */
	rtw_wx_get_enc,			/* SIOCGIWENCODE */
	dummy,					/* SIOCSIWPOWER */
	rtw_wx_get_घातer,		/* SIOCGIWPOWER */
	शून्य,					/*---hole---*/
	शून्य,					/*---hole---*/
	rtw_wx_set_gen_ie,		/* SIOCSIWGENIE */
	शून्य,					/* SIOCGWGENIE */
	rtw_wx_set_auth,		/* SIOCSIWAUTH */
	शून्य,					/* SIOCGIWAUTH */
	rtw_wx_set_enc_ext,		/* SIOCSIWENCODEEXT */
	शून्य,					/* SIOCGIWENCODEEXT */
	rtw_wx_set_pmkid,		/* SIOCSIWPMKSA */
	शून्य,					/*---hole---*/
पूर्ण;

अटल स्थिर काष्ठा iw_priv_args rtw_निजी_args[] = अणु
	अणु
		SIOCIWFIRSTPRIV + 0x0,
		IW_PRIV_TYPE_CHAR | 0x7FF, 0, "write"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x1,
		IW_PRIV_TYPE_CHAR | 0x7FF,
		IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | IFNAMSIZ, "read"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x2, 0, 0, "driver_ext"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x3, 0, 0, "mp_ioctl"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x4,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "apinfo"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x5,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 2, 0, "setpid"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x6,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "wps_start"
	पूर्ण,
/* क्रम PLATFORM_MT53XX */
	अणु
		SIOCIWFIRSTPRIV + 0x7,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "get_sensitivity"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x8,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "wps_prob_req_ie"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x9,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "wps_assoc_req_ie"
	पूर्ण,

/* क्रम RTK_DMP_PLATFORM */
	अणु
		SIOCIWFIRSTPRIV + 0xA,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "channel_plan"
	पूर्ण,

	अणु
		SIOCIWFIRSTPRIV + 0xB,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 2, 0, "dbg"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0xC,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 3, 0, "rfw"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0xD,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 2, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | IFNAMSIZ, "rfr"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x10,
		IW_PRIV_TYPE_CHAR | 1024, 0, "p2p_set"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x11,
		IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_MASK, "p2p_get"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x12, 0, 0, "NULL"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x13,
		IW_PRIV_TYPE_CHAR | 64, IW_PRIV_TYPE_CHAR | 64, "p2p_get2"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x14,
		IW_PRIV_TYPE_CHAR  | 64, 0, "tdls"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x15,
		IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024, "tdls_get"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x16,
		IW_PRIV_TYPE_CHAR | 64, 0, "pm_set"
	पूर्ण,

	अणुSIOCIWFIRSTPRIV + 0x18, IW_PRIV_TYPE_CHAR | IFNAMSIZ, 0, "rereg_nd_name"पूर्ण,
	अणुSIOCIWFIRSTPRIV + 0x1A, IW_PRIV_TYPE_CHAR | 1024, 0, "efuse_set"पूर्ण,
	अणुSIOCIWFIRSTPRIV + 0x1B, IW_PRIV_TYPE_CHAR | 128, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_MASK, "efuse_get"पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x1D,
		IW_PRIV_TYPE_CHAR | 40, IW_PRIV_TYPE_CHAR | 0x7FF, "test"
	पूर्ण,
पूर्ण;

अटल iw_handler rtw_निजी_handler[] = अणु
	rtw_wx_ग_लिखो32,					/* 0x00 */
	rtw_wx_पढ़ो32,					/* 0x01 */
	rtw_drvext_hdl,					/* 0x02 */
	शून्य,						/* 0x03 */

/*  क्रम MM DTV platक्रमm */
	rtw_get_ap_info,					/* 0x04 */

	rtw_set_pid,						/* 0x05 */
	rtw_wps_start,					/* 0x06 */

/*  क्रम PLATFORM_MT53XX */
	rtw_wx_get_sensitivity,			/* 0x07 */
	rtw_wx_set_mtk_wps_probe_ie,	/* 0x08 */
	rtw_wx_set_mtk_wps_ie,			/* 0x09 */

/*  क्रम RTK_DMP_PLATFORM */
/*  Set Channel depend on the country code */
	rtw_wx_set_channel_plan,		/* 0x0A */

	rtw_dbg_port,					/* 0x0B */
	rtw_wx_ग_लिखो_rf,					/* 0x0C */
	rtw_wx_पढ़ो_rf,					/* 0x0D */
	rtw_wx_priv_null,				/* 0x0E */
	rtw_wx_priv_null,				/* 0x0F */
	rtw_p2p_set,					/* 0x10 */
	rtw_p2p_get,					/* 0x11 */
	शून्य,							/* 0x12 */
	rtw_p2p_get2,					/* 0x13 */

	शून्य,						/* 0x14 */
	शून्य,						/* 0x15 */

	rtw_pm_set,						/* 0x16 */
	rtw_wx_priv_null,				/* 0x17 */
	rtw_rereg_nd_name,				/* 0x18 */
	rtw_wx_priv_null,				/* 0x19 */
	शून्य,						/* 0x1A */
	शून्य,						/* 0x1B */
	शून्य,							/*  0x1C is reserved क्रम hostapd */
	rtw_test,						/*  0x1D */
पूर्ण;

अटल काष्ठा iw_statistics *rtw_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा iw_statistics *piwstats = &padapter->iwstats;
	पूर्णांक पंचांगp_level = 0;
	पूर्णांक पंचांगp_qual = 0;
	पूर्णांक पंचांगp_noise = 0;

	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED) != true) अणु
		piwstats->qual.qual = 0;
		piwstats->qual.level = 0;
		piwstats->qual.noise = 0;
	पूर्ण अन्यथा अणु
		पंचांगp_level = padapter->recvpriv.संकेत_strength;
		पंचांगp_qual = padapter->recvpriv.संकेत_qual;
		पंचांगp_noise = padapter->recvpriv.noise;

		piwstats->qual.level = पंचांगp_level;
		piwstats->qual.qual = पंचांगp_qual;
		piwstats->qual.noise = पंचांगp_noise;
	पूर्ण
	piwstats->qual.updated = IW_QUAL_ALL_UPDATED ;/* IW_QUAL_DBM; */

	वापस &padapter->iwstats;
पूर्ण

काष्ठा iw_handler_def rtw_handlers_def = अणु
	.standard = rtw_handlers,
	.num_standard = ARRAY_SIZE(rtw_handlers),
#अगर defined(CONFIG_WEXT_PRIV)
	.निजी = rtw_निजी_handler,
	.निजी_args = (काष्ठा iw_priv_args *)rtw_निजी_args,
	.num_निजी = ARRAY_SIZE(rtw_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(rtw_निजी_args),
#पूर्ण_अगर
	.get_wireless_stats = rtw_get_wireless_stats,
पूर्ण;

/*  copy from net/wireless/wext.c start */
/* ---------------------------------------------------------------- */
/*
 * Calculate size of निजी arguments
 */
अटल स्थिर अक्षर iw_priv_type_size[] = अणु
	0,                              /* IW_PRIV_TYPE_NONE */
	1,                              /* IW_PRIV_TYPE_BYTE */
	1,                              /* IW_PRIV_TYPE_CHAR */
	0,                              /* Not defined */
	माप(__u32),                  /* IW_PRIV_TYPE_INT */
	माप(काष्ठा iw_freq),         /* IW_PRIV_TYPE_FLOAT */
	माप(काष्ठा sockaddr),        /* IW_PRIV_TYPE_ADDR */
	0,                              /* Not defined */
पूर्ण;

अटल पूर्णांक get_priv_size(__u16 args)
अणु
	पूर्णांक num = args & IW_PRIV_SIZE_MASK;
	पूर्णांक type = (args & IW_PRIV_TYPE_MASK) >> 12;

	वापस num * iw_priv_type_size[type];
पूर्ण
/*  copy from net/wireless/wext.c end */

अटल पूर्णांक rtw_ioctl_wext_निजी(काष्ठा net_device *dev, जोड़ iwreq_data *wrq_data)
अणु
	पूर्णांक err = 0;
	u8 *input = शून्य;
	u32 input_len = 0;
	स्थिर अक्षर delim[] = " ";
	u8 *output = शून्य;
	u32 output_len = 0;
	u32 count = 0;
	u8 *buffer = शून्य;
	u32 buffer_len = 0;
	अक्षर *ptr = शून्य;
	u8 cmdname[17] = अणु0पूर्ण; /*  IFNAMSIZ+1 */
	u32 cmdlen;
	s32 len;
	u8 *extra = शून्य;
	u32 extra_size = 0;

	s32 k;
	स्थिर iw_handler *priv;		/* Private ioctl */
	स्थिर काष्ठा iw_priv_args *priv_args;	/* Private ioctl description */
	u32 num_priv_args;			/* Number of descriptions */
	iw_handler handler;
	पूर्णांक temp;
	पूर्णांक subcmd = 0;				/* sub-ioctl index */
	पूर्णांक offset = 0;				/* Space क्रम sub-ioctl index */

	जोड़ iwreq_data wdata;


	स_नकल(&wdata, wrq_data, माप(wdata));

	input_len = 2048;
	input = rtw_zदो_स्मृति(input_len);
	अगर (शून्य == input)
		वापस -ENOMEM;
	अगर (copy_from_user(input, wdata.data.poपूर्णांकer, input_len)) अणु
		err = -EFAULT;
		जाओ निकास;
	पूर्ण
	ptr = input;
	len = म_माप(input);

	माला_पूछो(ptr, "%16s", cmdname);
	cmdlen = म_माप(cmdname);

	/*  skip command string */
	अगर (cmdlen > 0)
		cmdlen += 1; /*  skip one space */
	ptr += cmdlen;
	len -= cmdlen;

	priv = rtw_निजी_handler;
	priv_args = rtw_निजी_args;
	num_priv_args = ARRAY_SIZE(rtw_निजी_args);

	अगर (num_priv_args == 0) अणु
		err = -EOPNOTSUPP;
		जाओ निकास;
	पूर्ण

	/* Search the correct ioctl */
	k = -1;
	जबतक ((++k < num_priv_args) && म_भेद(priv_args[k].name, cmdname));

	/* If not found... */
	अगर (k == num_priv_args) अणु
		err = -EOPNOTSUPP;
		जाओ निकास;
	पूर्ण

	/* Watch out क्रम sub-ioctls ! */
	अगर (priv_args[k].cmd < SIOCDEVPRIVATE) अणु
		पूर्णांक j = -1;

		/* Find the matching *real* ioctl */
		जबतक ((++j < num_priv_args) && ((priv_args[j].name[0] != '\0') ||
			(priv_args[j].set_args != priv_args[k].set_args) ||
			(priv_args[j].get_args != priv_args[k].get_args)));

		/* If not found... */
		अगर (j == num_priv_args) अणु
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		/* Save sub-ioctl number */
		subcmd = priv_args[k].cmd;
		/* Reserve one पूर्णांक (simplअगरy alignment issues) */
		offset = माप(__u32);
		/* Use real ioctl definition from now on */
		k = j;
	पूर्ण

	buffer = rtw_zदो_स्मृति(4096);
	अगर (शून्य == buffer) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	/* If we have to set some data */
	अगर ((priv_args[k].set_args & IW_PRIV_TYPE_MASK) &&
		(priv_args[k].set_args & IW_PRIV_SIZE_MASK)) अणु
		u8 *str;

		चयन (priv_args[k].set_args & IW_PRIV_TYPE_MASK) अणु
		हाल IW_PRIV_TYPE_BYTE:
			/* Fetch args */
			count = 0;
			करो अणु
				str = strsep(&ptr, delim);
				अगर (शून्य == str)
					अवरोध;
				माला_पूछो(str, "%i", &temp);
				buffer[count++] = (u8)temp;
			पूर्ण जबतक (1);
			buffer_len = count;

			/* Number of args to fetch */
			wdata.data.length = count;
			अगर (wdata.data.length > (priv_args[k].set_args & IW_PRIV_SIZE_MASK))
				wdata.data.length = priv_args[k].set_args & IW_PRIV_SIZE_MASK;

			अवरोध;

		हाल IW_PRIV_TYPE_INT:
			/* Fetch args */
			count = 0;
			करो अणु
				str = strsep(&ptr, delim);
				अगर (शून्य == str)
					अवरोध;
				माला_पूछो(str, "%i", &temp);
				((s32 *)buffer)[count++] = (s32)temp;
			पूर्ण जबतक (1);
			buffer_len = count * माप(s32);

			/* Number of args to fetch */
			wdata.data.length = count;
			अगर (wdata.data.length > (priv_args[k].set_args & IW_PRIV_SIZE_MASK))
				wdata.data.length = priv_args[k].set_args & IW_PRIV_SIZE_MASK;

			अवरोध;

		हाल IW_PRIV_TYPE_CHAR:
			अगर (len > 0) अणु
				/* Size of the string to fetch */
				wdata.data.length = len;
				अगर (wdata.data.length > (priv_args[k].set_args & IW_PRIV_SIZE_MASK))
					wdata.data.length = priv_args[k].set_args & IW_PRIV_SIZE_MASK;

				/* Fetch string */
				स_नकल(buffer, ptr, wdata.data.length);
			पूर्ण अन्यथा अणु
				wdata.data.length = 1;
				buffer[0] = '\0';
			पूर्ण
			buffer_len = wdata.data.length;
			अवरोध;

		शेष:
			err = -1;
			जाओ निकास;
		पूर्ण

		अगर ((priv_args[k].set_args & IW_PRIV_SIZE_FIXED) &&
			(wdata.data.length != (priv_args[k].set_args & IW_PRIV_SIZE_MASK))) अणु
			err = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु /* अगर args to set */
		wdata.data.length = 0L;
	पूर्ण

	/* Those two tests are important. They define how the driver
	* will have to handle the data */
	अगर ((priv_args[k].set_args & IW_PRIV_SIZE_FIXED) &&
		((get_priv_size(priv_args[k].set_args) + offset) <= IFNAMSIZ)) अणु
		/* First हाल : all SET args fit within wrq */
		अगर (offset)
			wdata.mode = subcmd;
		स_नकल(wdata.name + offset, buffer, IFNAMSIZ - offset);
	पूर्ण अन्यथा अणु
		अगर ((priv_args[k].set_args == 0) &&
			(priv_args[k].get_args & IW_PRIV_SIZE_FIXED) &&
			(get_priv_size(priv_args[k].get_args) <= IFNAMSIZ)) अणु
			/* Second हाल : no SET args, GET args fit within wrq */
			अगर (offset)
				wdata.mode = subcmd;
		पूर्ण अन्यथा अणु
			/* Third हाल : args won't fit in wrq, or variable number of args */
			अगर (copy_to_user(wdata.data.poपूर्णांकer, buffer, buffer_len)) अणु
				err = -EFAULT;
				जाओ निकास;
			पूर्ण
			wdata.data.flags = subcmd;
		पूर्ण
	पूर्ण

	kमुक्त(input);
	input = शून्य;

	extra_size = 0;
	अगर (IW_IS_SET(priv_args[k].cmd)) अणु
		/* Size of set arguments */
		extra_size = get_priv_size(priv_args[k].set_args);

		/* Does it fits in iwr ? */
		अगर ((priv_args[k].set_args & IW_PRIV_SIZE_FIXED) &&
			((extra_size + offset) <= IFNAMSIZ))
			extra_size = 0;
	पूर्ण अन्यथा अणु
		/* Size of get arguments */
		extra_size = get_priv_size(priv_args[k].get_args);

		/* Does it fits in iwr ? */
		अगर ((priv_args[k].get_args & IW_PRIV_SIZE_FIXED) &&
			(extra_size <= IFNAMSIZ))
			extra_size = 0;
	पूर्ण

	अगर (extra_size == 0) अणु
		extra = (u8 *)&wdata;
		kमुक्त(buffer);
		buffer = शून्य;
	पूर्ण अन्यथा
		extra = buffer;

	handler = priv[priv_args[k].cmd - SIOCIWFIRSTPRIV];
	err = handler(dev, शून्य, &wdata, extra);

	/* If we have to get some data */
	अगर ((priv_args[k].get_args & IW_PRIV_TYPE_MASK) &&
		(priv_args[k].get_args & IW_PRIV_SIZE_MASK)) अणु
		पूर्णांक j;
		पूर्णांक n = 0;	/* number of args */
		u8 str[20] = अणु0पूर्ण;

		/* Check where is the वापसed data */
		अगर ((priv_args[k].get_args & IW_PRIV_SIZE_FIXED) &&
			(get_priv_size(priv_args[k].get_args) <= IFNAMSIZ))
			n = priv_args[k].get_args & IW_PRIV_SIZE_MASK;
		अन्यथा
			n = wdata.data.length;

		output = rtw_zदो_स्मृति(4096);
		अगर (शून्य == output) अणु
			err =  -ENOMEM;
			जाओ निकास;
		पूर्ण

		चयन (priv_args[k].get_args & IW_PRIV_TYPE_MASK) अणु
		हाल IW_PRIV_TYPE_BYTE:
			/* Display args */
			क्रम (j = 0; j < n; j++) अणु
				len = scnम_लिखो(str, माप(str), "%d  ", extra[j]);
				output_len = म_माप(output);
				अगर ((output_len + len + 1) > 4096) अणु
					err = -E2BIG;
					जाओ निकास;
				पूर्ण
				स_नकल(output+output_len, str, len);
			पूर्ण
			अवरोध;

		हाल IW_PRIV_TYPE_INT:
			/* Display args */
			क्रम (j = 0; j < n; j++) अणु
				len = scnम_लिखो(str, माप(str), "%d  ", ((__s32 *)extra)[j]);
				output_len = म_माप(output);
				अगर ((output_len + len + 1) > 4096) अणु
					err = -E2BIG;
					जाओ निकास;
				पूर्ण
				स_नकल(output+output_len, str, len);
			पूर्ण
			अवरोध;

		हाल IW_PRIV_TYPE_CHAR:
			/* Display args */
			स_नकल(output, extra, n);
			अवरोध;

		शेष:
			err = -1;
			जाओ निकास;
		पूर्ण

		output_len = म_माप(output) + 1;
		wrq_data->data.length = output_len;
		अगर (copy_to_user(wrq_data->data.poपूर्णांकer, output, output_len)) अणु
			err = -EFAULT;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु /* अगर args to set */
		wrq_data->data.length = 0;
	पूर्ण

निकास:
	kमुक्त(input);
	kमुक्त(buffer);
	kमुक्त(output);

	वापस err;
पूर्ण

पूर्णांक rtw_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा iwreq *wrq = (काष्ठा iwreq *)rq;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल RTL_IOCTL_WPA_SUPPLICANT:
		ret = wpa_supplicant_ioctl(dev, &wrq->u.data);
		अवरोध;
	हाल RTL_IOCTL_HOSTAPD:
		ret = rtw_hostapd_ioctl(dev, &wrq->u.data);
		अवरोध;
	हाल SIOCDEVPRIVATE:
		ret = rtw_ioctl_wext_निजी(dev, &wrq->u);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
