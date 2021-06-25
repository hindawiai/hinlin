<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _IOCTL_LINUX_C_

#समावेश <linux/ieee80211.h>

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <wlan_bssdef.h>
#समावेश <rtw_debug.h>
#समावेश <wअगरi.h>
#समावेश <rtw_mlme.h>
#समावेश <rtw_mlme_ext.h>
#समावेश <rtw_ioctl.h>
#समावेश <rtw_ioctl_set.h>
#समावेश <rtl8188e_hal.h>

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/etherdevice.h>

#समावेश "osdep_intf.h"

#घोषणा RTL_IOCTL_WPA_SUPPLICANT	(SIOCIWFIRSTPRIV + 30)

#घोषणा SCAN_ITEM_SIZE 768
#घोषणा MAX_CUSTOM_LEN 64
#घोषणा RATE_COUNT 4

/*  combo scan */
#घोषणा WEXT_CSCAN_AMOUNT 9
#घोषणा WEXT_CSCAN_BUF_LEN		360
#घोषणा WEXT_CSCAN_HEADER		"CSCAN S\x01\x00\x00S\x00"
#घोषणा WEXT_CSCAN_HEADER_SIZE		12
#घोषणा WEXT_CSCAN_SSID_SECTION		'S'
#घोषणा WEXT_CSCAN_CHANNEL_SECTION	'C'
#घोषणा WEXT_CSCAN_NPROBE_SECTION	'N'
#घोषणा WEXT_CSCAN_ACTV_DWELL_SECTION	'A'
#घोषणा WEXT_CSCAN_PASV_DWELL_SECTION	'P'
#घोषणा WEXT_CSCAN_HOME_DWELL_SECTION	'H'
#घोषणा WEXT_CSCAN_TYPE_SECTION		'T'

अटल u32 rtw_rates[] = अणु1000000, 2000000, 5500000, 11000000,
	6000000, 9000000, 12000000, 18000000, 24000000, 36000000,
	48000000, 54000000पूर्ण;

अटल स्थिर अक्षर * स्थिर iw_operation_mode[] = अणु
	"Auto", "Ad-Hoc", "Managed",  "Master", "Repeater",
	"Secondary", "Monitor"
पूर्ण;

व्योम indicate_wx_scan_complete_event(काष्ठा adapter *padapter)
अणु
	जोड़ iwreq_data wrqu;

	स_रखो(&wrqu, 0, माप(जोड़ iwreq_data));
	wireless_send_event(padapter->pnetdev, SIOCGIWSCAN, &wrqu, शून्य);
पूर्ण

व्योम rtw_indicate_wx_assoc_event(काष्ठा adapter *padapter)
अणु
	जोड़ iwreq_data wrqu;
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	स_रखो(&wrqu, 0, माप(जोड़ iwreq_data));

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	स_नकल(wrqu.ap_addr.sa_data, pmlmepriv->cur_network.network.MacAddress, ETH_ALEN);

	DBG_88E_LEVEL(_drv_always_, "assoc success\n");
	wireless_send_event(padapter->pnetdev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण

व्योम rtw_indicate_wx_disassoc_event(काष्ठा adapter *padapter)
अणु
	जोड़ iwreq_data wrqu;

	स_रखो(&wrqu, 0, माप(जोड़ iwreq_data));

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	eth_zero_addr(wrqu.ap_addr.sa_data);

	DBG_88E_LEVEL(_drv_always_, "indicate disassoc\n");
	wireless_send_event(padapter->pnetdev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण

अटल अक्षर *translate_scan(काष्ठा adapter *padapter,
			    काष्ठा iw_request_info *info,
			    काष्ठा wlan_network *pnetwork,
			    अक्षर *start, अक्षर *stop)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा iw_event iwe;
	u16 cap;
	__le16 le_पंचांगp;
	u32 ht_ielen = 0;
	अक्षर custom[MAX_CUSTOM_LEN];
	अक्षर *p;
	u16 max_rate = 0, rate, ht_cap = false;
	u32 i = 0;
	u8 bw_40MHz = 0, लघु_GI = 0;
	u16 mcs_rate = 0;
	u8 ss, sq;

	/*  AP MAC address  */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;

	स_नकल(iwe.u.ap_addr.sa_data, pnetwork->network.MacAddress, ETH_ALEN);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_ADDR_LEN);

	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	iwe.u.data.length = min_t(u16, pnetwork->network.ssid.ssid_length, 32);
	start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, pnetwork->network.ssid.ssid);

	/* parsing HT_CAP_IE */
	p = rtw_get_ie(&pnetwork->network.ies[12], WLAN_EID_HT_CAPABILITY, &ht_ielen, pnetwork->network.ie_length - 12);

	अगर (p && ht_ielen > 0) अणु
		काष्ठा ieee80211_ht_cap *pht_capie;

		ht_cap = true;

		pht_capie = (काष्ठा ieee80211_ht_cap *)(p + 2);
		स_नकल(&mcs_rate, pht_capie->mcs.rx_mask, 2);
		bw_40MHz = !!(le16_to_cpu(pht_capie->cap_info) &
			      IEEE80211_HT_CAP_SUP_WIDTH_20_40);
		लघु_GI = !!(le16_to_cpu(pht_capie->cap_info) &
			      (IEEE80211_HT_CAP_SGI_20 |
			       IEEE80211_HT_CAP_SGI_40));
	पूर्ण

	/* Add the protocol name */
	iwe.cmd = SIOCGIWNAME;
	अगर ((rtw_is_cckratesonly_included((u8 *)&pnetwork->network.SupportedRates))) अणु
		अगर (ht_cap)
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11bn");
		अन्यथा
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11b");
	पूर्ण अन्यथा अगर ((rtw_is_cckrates_included((u8 *)&pnetwork->network.SupportedRates))) अणु
		अगर (ht_cap)
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11bgn");
		अन्यथा
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11bg");
	पूर्ण अन्यथा अणु
		अगर (ht_cap)
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11gn");
		अन्यथा
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11g");
	पूर्ण

	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_CHAR_LEN);

	  /* Add mode */
	iwe.cmd = SIOCGIWMODE;
	स_नकल(&le_पंचांगp, rtw_get_capability_from_ie(pnetwork->network.ies), 2);

	cap = le16_to_cpu(le_पंचांगp);

	अगर (!WLAN_CAPABILITY_IS_STA_BSS(cap)) अणु
		अगर (cap & WLAN_CAPABILITY_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;

		start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_UINT_LEN);
	पूर्ण

	अगर (pnetwork->network.Configuration.DSConfig < 1)
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
	start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe, pnetwork->network.ssid.ssid);

	/*Add basic and extended rates */
	max_rate = 0;
	p = custom;
	p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom), " Rates (Mb/s): ");
	जबतक (pnetwork->network.SupportedRates[i] != 0) अणु
		rate = pnetwork->network.SupportedRates[i] & 0x7F;
		अगर (rate > max_rate)
			max_rate = rate;
		p += scnम_लिखो(p, MAX_CUSTOM_LEN - (p - custom),
			      "%d%s ", rate >> 1, (rate & 1) ? ".5" : "");
		i++;
	पूर्ण

	अगर (ht_cap) अणु
		अगर (mcs_rate & 0x8000)/* MCS15 */
			max_rate = (bw_40MHz) ? ((लघु_GI) ? 300 : 270) : ((लघु_GI) ? 144 : 130);
		अन्यथा अगर (mcs_rate & 0x0080)/* MCS7 */
			;
		अन्यथा/* शेष MCS7 */
			max_rate = (bw_40MHz) ? ((लघु_GI) ? 150 : 135) : ((लघु_GI) ? 72 : 65);

		max_rate *= 2; /* Mbps/2; */
	पूर्ण

	iwe.cmd = SIOCGIWRATE;
	iwe.u.bitrate.fixed = 0;
	iwe.u.bitrate.disabled = 0;
	iwe.u.bitrate.value = max_rate * 500000;
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_PARAM_LEN);

	/* parsing WPA/WPA2 IE */
	अणु
		u8 *buf;
		u8 wpa_ie[255], rsn_ie[255];
		u16 wpa_len = 0, rsn_len = 0;
		u8 *p;

		buf = kzalloc(MAX_WPA_IE_LEN, GFP_ATOMIC);
		अगर (!buf)
			वापस start;

		rtw_get_sec_ie(pnetwork->network.ies, pnetwork->network.ie_length, rsn_ie, &rsn_len, wpa_ie, &wpa_len);
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("rtw_wx_get_scan: ssid =%s\n", pnetwork->network.ssid.ssid));
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("rtw_wx_get_scan: wpa_len =%d rsn_len =%d\n", wpa_len, rsn_len));

		अगर (wpa_len > 0) अणु
			p = buf;
			p += प्र_लिखो(p, "wpa_ie=");
			क्रम (i = 0; i < wpa_len; i++)
				p += प्र_लिखो(p, "%02x", wpa_ie[i]);

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
			p += प्र_लिखो(p, "rsn_ie=");
			क्रम (i = 0; i < rsn_len; i++)
				p += प्र_लिखो(p, "%02x", rsn_ie[i]);
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

	अणु/* parsing WPS IE */
		uपूर्णांक cnt = 0, total_ielen;
		u8 *wpsie_ptr = शून्य;
		uपूर्णांक wps_ielen = 0;
		u8 *ie_ptr = pnetwork->network.ies + _FIXED_IE_LENGTH_;

		total_ielen = pnetwork->network.ie_length - _FIXED_IE_LENGTH_;

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
	iwe.u.qual.updated = IW_QUAL_QUAL_UPDATED | IW_QUAL_LEVEL_UPDATED | IW_QUAL_NOISE_INVALID;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) &&
	    is_same_network(&pmlmepriv->cur_network.network, &pnetwork->network)) अणु
		ss = padapter->recvpriv.संकेत_strength;
		sq = padapter->recvpriv.संकेत_qual;
	पूर्ण अन्यथा अणु
		ss = pnetwork->network.PhyInfo.SignalStrength;
		sq = pnetwork->network.PhyInfo.SignalQuality;
	पूर्ण

	iwe.u.qual.level = (u8)ss;
	iwe.u.qual.qual = (u8)sq;   /*  संकेत quality */
	iwe.u.qual.noise = 0; /*  noise level */
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_QUAL_LEN);
	वापस start;
पूर्ण

अटल पूर्णांक wpa_set_auth_algs(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर ((value & AUTH_ALG_SHARED_KEY) && (value & AUTH_ALG_OPEN_SYSTEM)) अणु
		DBG_88E("%s, AUTH_ALG_SHARED_KEY and  AUTH_ALG_OPEN_SYSTEM [value:0x%x]\n", __func__, value);
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
		padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeAutoSwitch;
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Auto;
	पूर्ण अन्यथा अगर (value & AUTH_ALG_SHARED_KEY) अणु
		DBG_88E("%s, AUTH_ALG_SHARED_KEY  [value:0x%x]\n", __func__, value);
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;

		padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeShared;
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Shared;
	पूर्ण अन्यथा अगर (value & AUTH_ALG_OPEN_SYSTEM) अणु
		DBG_88E("%s, AUTH_ALG_OPEN_SYSTEM\n", __func__);
		अगर (padapter->securitypriv.ndisauthtype < Ndis802_11AuthModeWPAPSK) अणु
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
			padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
		पूर्ण
	पूर्ण अन्यथा अगर (value & AUTH_ALG_LEAP) अणु
		DBG_88E("%s, AUTH_ALG_LEAP\n", __func__);
	पूर्ण अन्यथा अणु
		DBG_88E("%s, error!\n", __func__);
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक wpa_set_encryption(काष्ठा net_device *dev, काष्ठा ieee_param *param, u32 param_len)
अणु
	पूर्णांक ret = 0;
	u32 wep_key_idx, wep_key_len, wep_total_len;
	काष्ठा ndis_802_11_wep *pwep = शून्य;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';

	अगर (param_len < (u32)((u8 *)param->u.crypt.key - (u8 *)param) + param->u.crypt.key_len) अणु
		ret =  -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (is_broadcast_ether_addr(param->sta_addr)) अणु
		अगर (param->u.crypt.idx >= WEP_KEYS) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_err_, ("%s, crypt.alg = WEP\n", __func__));
		DBG_88E("%s, crypt.alg = WEP\n", __func__);

		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
		padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP40_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _WEP40_;

		wep_key_idx = param->u.crypt.idx;
		wep_key_len = param->u.crypt.key_len;

		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_, ("(1)wep_key_idx =%d\n", wep_key_idx));
		DBG_88E("(1)wep_key_idx =%d\n", wep_key_idx);

		अगर (wep_key_idx > WEP_KEYS)
			वापस -EINVAL;

		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_, ("(2)wep_key_idx =%d\n", wep_key_idx));

		अगर (wep_key_len > 0) अणु
			wep_key_len = wep_key_len <= 5 ? 5 : 13;
			wep_total_len = wep_key_len + दुरत्व(काष्ठा ndis_802_11_wep, KeyMaterial);
			pwep = (काष्ठा ndis_802_11_wep *)rtw_दो_स्मृति(wep_total_len);
			अगर (!pwep) अणु
				RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_err_, ("%s: pwep allocate fail !!!\n", __func__));
				जाओ निकास;
			पूर्ण
			स_रखो(pwep, 0, wep_total_len);
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
			DBG_88E("wep, set_tx = 1\n");
			अगर (rtw_set_802_11_add_wep(padapter, pwep) == (u8)_FAIL)
				ret = -EOPNOTSUPP;
		पूर्ण अन्यथा अणु
			DBG_88E("wep, set_tx = 0\n");
			अगर (wep_key_idx >= WEP_KEYS) अणु
				ret = -EOPNOTSUPP;
				जाओ निकास;
			पूर्ण
			स_नकल(&psecuritypriv->करोt11DefKey[wep_key_idx].skey[0], pwep->KeyMaterial, pwep->KeyLength);
			psecuritypriv->करोt11DefKeylen[wep_key_idx] = pwep->KeyLength;
			rtw_set_key(padapter, psecuritypriv, wep_key_idx, 0);
		पूर्ण
		जाओ निकास;
	पूर्ण

	अगर (padapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X) अणु /*  802_1x */
		काष्ठा sta_info *psta, *pbcmc_sta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु /* sta mode */
			psta = rtw_get_stainfo(pstapriv, get_bssid(pmlmepriv));
			अगर (!psta) अणु
				;
			पूर्ण अन्यथा अणु
				अगर (म_भेद(param->u.crypt.alg, "none") != 0)
					psta->ieee8021x_blocked = false;

				अगर ((padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption2Enabled) ||
				    (padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption3Enabled))
					psta->करोt118021XPrivacy = padapter->securitypriv.करोt11PrivacyAlgrthm;

				अगर (param->u.crypt.set_tx == 1) अणु /* pairwise key */
					स_नकल(psta->करोt118021x_UncstKey.skey, param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));

					अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु /* set mic key */
						स_नकल(psta->करोt11tkiptxmickey.skey, &param->u.crypt.key[16], 8);
						स_नकल(psta->करोt11tkiprxmickey.skey, &param->u.crypt.key[24], 8);
						padapter->securitypriv.busetkipkey = false;
					पूर्ण

					DBG_88E(" ~~~~set sta key:unicastkey\n");

					rtw_setstakey_cmd(padapter, (अचिन्हित अक्षर *)psta, true);
				पूर्ण अन्यथा अणु /* group key */
					स_नकल(padapter->securitypriv.करोt118021XGrpKey[param->u.crypt.idx].skey, param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));
					स_नकल(padapter->securitypriv.करोt118021XGrptxmickey[param->u.crypt.idx].skey, &param->u.crypt.key[16], 8);
					स_नकल(padapter->securitypriv.करोt118021XGrprxmickey[param->u.crypt.idx].skey, &param->u.crypt.key[24], 8);
					padapter->securitypriv.binstallGrpkey = true;
					DBG_88E(" ~~~~set sta key:groupkey\n");

					padapter->securitypriv.करोt118021XGrpKeyid = param->u.crypt.idx;

					rtw_set_key(padapter, &padapter->securitypriv, param->u.crypt.idx, 1);
				पूर्ण
			पूर्ण
			pbcmc_sta = rtw_get_bcmc_stainfo(padapter);
			अगर (!pbcmc_sta) अणु
				;
			पूर्ण अन्यथा अणु
				/* Jeff: करोn't disable ieee8021x_blocked जबतक clearing key */
				अगर (म_भेद(param->u.crypt.alg, "none") != 0)
					pbcmc_sta->ieee8021x_blocked = false;

				अगर ((padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption2Enabled) ||
				    (padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption3Enabled))
					pbcmc_sta->करोt118021XPrivacy = padapter->securitypriv.करोt11PrivacyAlgrthm;
			पूर्ण
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

	अगर ((ielen > MAX_WPA_IE_LEN) || (!pie)) अणु
		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
		अगर (!pie)
			वापस ret;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (ielen) अणु
		buf = kmemdup(pie, ielen, GFP_KERNEL);
		अगर (!buf) अणु
			ret =  -ENOMEM;
			जाओ निकास;
		पूर्ण

		/* dump */
		अणु
			पूर्णांक i;

			DBG_88E("\n wpa_ie(length:%d):\n", ielen);
			क्रम (i = 0; i < ielen; i += 8)
				DBG_88E("0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x\n", buf[i], buf[i + 1], buf[i + 2], buf[i + 3], buf[i + 4], buf[i + 5], buf[i + 6], buf[i + 7]);
		पूर्ण

		अगर (ielen < RSN_HEADER_LEN) अणु
			RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_err_, ("Ie len too short %d\n", ielen));
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
				अगर ((eid == WLAN_EID_VENDOR_SPECIFIC) && (!स_भेद(&buf[cnt + 2], wps_oui, 4))) अणु
					DBG_88E("SET WPS_IE\n");

					padapter->securitypriv.wps_ie_len = min(buf[cnt + 1] + 2, MAX_WPA_IE_LEN << 2);

					स_नकल(padapter->securitypriv.wps_ie, &buf[cnt], padapter->securitypriv.wps_ie_len);

					set_fwstate(&padapter->mlmepriv, WIFI_UNDER_WPS);
					cnt += buf[cnt + 1] + 2;
					अवरोध;
				पूर्ण
				cnt += buf[cnt + 1] + 2; /* जाओ next */
			पूर्ण
		पूर्ण
	पूर्ण

	RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
		 ("%s: pairwise_cipher = 0x%08x padapter->securitypriv.ndisencryptstatus =%d padapter->securitypriv.ndisauthtype =%d\n",
		  __func__, pairwise_cipher, padapter->securitypriv.ndisencryptstatus, padapter->securitypriv.ndisauthtype));
निकास:
	kमुक्त(buf);
	वापस ret;
पूर्ण

प्रकार अचिन्हित अक्षर   NDIS_802_11_RATES_EX[NDIS_802_11_LENGTH_RATES_EX];

अटल पूर्णांक rtw_wx_get_name(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	u32 ht_ielen = 0;
	अक्षर *p;
	u8 ht_cap = false;
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex  *pcur_bss = &pmlmepriv->cur_network.network;
	NDIS_802_11_RATES_EX *prates = शून्य;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("cmd_code =%x\n", info->cmd));

	अगर (check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE)) अणु
		/* parsing HT_CAP_IE */
		p = rtw_get_ie(&pcur_bss->ies[12], WLAN_EID_HT_CAPABILITY, &ht_ielen, pcur_bss->ie_length - 12);
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
			अगर (ht_cap)
				snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11gn");
			अन्यथा
				snम_लिखो(wrqu->name, IFNAMSIZ, "IEEE 802.11g");
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(wrqu->name, IFNAMSIZ, "unassociated");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_freq(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_, ("+%s\n", __func__));
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_freq(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex  *pcur_bss = &pmlmepriv->cur_network.network;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
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
	काष्ठा adapter *padapter = netdev_priv(dev);
	क्रमागत ndis_802_11_network_infra networkType;
	पूर्णांक ret = 0;

	अगर (!rtw_pwr_wakeup(padapter)) अणु
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
		DBG_88E("set_mode = IW_MODE_AUTO\n");
		अवरोध;
	हाल IW_MODE_ADHOC:
		networkType = Ndis802_11IBSS;
		DBG_88E("set_mode = IW_MODE_ADHOC\n");
		अवरोध;
	हाल IW_MODE_MASTER:
		networkType = Ndis802_11APMode;
		DBG_88E("set_mode = IW_MODE_MASTER\n");
		अवरोध;
	हाल IW_MODE_INFRA:
		networkType = Ndis802_11Infraकाष्ठाure;
		DBG_88E("set_mode = IW_MODE_INFRA\n");
		अवरोध;
	शेष:
		ret = -EINVAL;
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_err_, ("\n Mode: %s is not supported\n", iw_operation_mode[wrqu->mode]));
		जाओ निकास;
	पूर्ण
	अगर (!rtw_set_802_11_infraकाष्ठाure_mode(padapter, networkType)) अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण
	rtw_setopmode_cmd(padapter, networkType);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			   जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s\n", __func__));

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		wrqu->mode = IW_MODE_INFRA;
	अन्यथा अगर  ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) ||
		  (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)))
		wrqu->mode = IW_MODE_ADHOC;
	अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		wrqu->mode = IW_MODE_MASTER;
	अन्यथा
		wrqu->mode = IW_MODE_AUTO;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_pmkid(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *a,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	u8   j, blInserted = false;
	पूर्णांक  ret = false;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा iw_pmksa *pPMK = (काष्ठा iw_pmksa *)extra;
	u8     strZeroMacAddress[ETH_ALEN] = अणु0x00पूर्ण;
	u8     strIssueBssid[ETH_ALEN] = अणु0x00पूर्ण;

	स_नकल(strIssueBssid, pPMK->bssid.sa_data, ETH_ALEN);
	अगर (pPMK->cmd == IW_PMKSA_ADD) अणु
		DBG_88E("[%s] IW_PMKSA_ADD!\n", __func__);
		अगर (!स_भेद(strIssueBssid, strZeroMacAddress, ETH_ALEN))
			वापस ret;
		ret = true;
		blInserted = false;

		/* overग_लिखो PMKID */
		क्रम (j = 0; j < NUM_PMKID_CACHE; j++) अणु
			अगर (!स_भेद(psecuritypriv->PMKIDList[j].bssid, strIssueBssid, ETH_ALEN)) अणु
				/*  BSSID is matched, the same AP => reग_लिखो with new PMKID. */
				DBG_88E("[%s] BSSID exists in the PMKList.\n", __func__);
				स_नकल(psecuritypriv->PMKIDList[j].PMKID, pPMK->pmkid, IW_PMKID_LEN);
				psecuritypriv->PMKIDList[j].used = true;
				psecuritypriv->PMKIDIndex = j + 1;
				blInserted = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!blInserted) अणु
			/*  Find a new entry */
			DBG_88E("[%s] Use the new entry index = %d for this PMKID.\n",
				__func__, psecuritypriv->PMKIDIndex);

			स_नकल(psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].bssid, strIssueBssid, ETH_ALEN);
			स_नकल(psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].PMKID, pPMK->pmkid, IW_PMKID_LEN);

			psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].used = true;
			psecuritypriv->PMKIDIndex++;
			अगर (psecuritypriv->PMKIDIndex == 16)
				psecuritypriv->PMKIDIndex = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (pPMK->cmd == IW_PMKSA_REMOVE) अणु
		DBG_88E("[%s] IW_PMKSA_REMOVE!\n", __func__);
		ret = true;
		क्रम (j = 0; j < NUM_PMKID_CACHE; j++) अणु
			अगर (!स_भेद(psecuritypriv->PMKIDList[j].bssid, strIssueBssid, ETH_ALEN)) अणु
				/*  BSSID is matched, the same AP => Remove this PMKID inक्रमmation and reset it. */
				eth_zero_addr(psecuritypriv->PMKIDList[j].bssid);
				psecuritypriv->PMKIDList[j].used = false;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (pPMK->cmd == IW_PMKSA_FLUSH) अणु
		DBG_88E("[%s] IW_PMKSA_FLUSH!\n", __func__);
		स_रखो(&psecuritypriv->PMKIDList[0], 0x00, माप(काष्ठा rt_pmkid_list) * NUM_PMKID_CACHE);
		psecuritypriv->PMKIDIndex = 0;
		ret = true;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_sens(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	wrqu->sens.value = 0;
	wrqu->sens.fixed = 0;	/* no स्वतः select */
	wrqu->sens.disabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_range(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;

	u16 val;
	पूर्णांक i;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s. cmd_code =%x\n", __func__, info->cmd));

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
	range->avg_qual.level = 178; /* -78 dBm */
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

/*  The following code will proivde the security capability to network manager. */
/*  If the driver करोesn't provide this capability to network manager, */
/*  the WPA/WPA2 routers can't be chosen in the network manager. */

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
			  IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;

	range->scan_capa = IW_SCAN_CAPA_ESSID | IW_SCAN_CAPA_TYPE |
			   IW_SCAN_CAPA_BSSID | IW_SCAN_CAPA_CHANNEL |
			   IW_SCAN_CAPA_MODE | IW_SCAN_CAPA_RATE;
	वापस 0;
पूर्ण

/* set bssid flow */
/* s1. rtw_set_802_11_infraकाष्ठाure_mode() */
/* s2. rtw_set_802_11_authentication_mode() */
/* s3. set_802_11_encryption_mode() */
/* s4. rtw_set_802_11_bssid() */
अटल पूर्णांक rtw_wx_set_wap(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *awrq, अक्षर *extra)
अणु
	uपूर्णांक ret = 0;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा sockaddr *temp = (काष्ठा sockaddr *)awrq;
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा list_head *phead;
	u8 *dst_bssid, *src_bssid;
	काष्ठा __queue *queue	= &pmlmepriv->scanned_queue;
	काष्ठा	wlan_network	*pnetwork = शून्य;
	क्रमागत ndis_802_11_auth_mode	authmode;

	अगर (!rtw_pwr_wakeup(padapter)) अणु
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
	pmlmepriv->pscanned = phead->next;

	जबतक (phead != pmlmepriv->pscanned) अणु
		pnetwork = container_of(pmlmepriv->pscanned, काष्ठा wlan_network, list);

		pmlmepriv->pscanned = pmlmepriv->pscanned->next;

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
	अगर (!rtw_set_802_11_bssid(padapter, temp->sa_data)) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

निकास:

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_wap(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex  *pcur_bss = &pmlmepriv->cur_network.network;

	wrqu->ap_addr.sa_family = ARPHRD_ETHER;

	eth_zero_addr(wrqu->ap_addr.sa_data);

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s\n", __func__));

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_AP_STATE))
		स_नकल(wrqu->ap_addr.sa_data, pcur_bss->MacAddress, ETH_ALEN);
	अन्यथा
		eth_zero_addr(wrqu->ap_addr.sa_data);
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_mlme(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	u16 reason;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *)extra;

	अगर (!mlme)
		वापस -1;

	DBG_88E("%s\n", __func__);

	reason = mlme->reason_code;

	DBG_88E("%s, cmd =%d, reason =%d\n", __func__, mlme->cmd, reason);

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
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ndis_802_11_ssid ssid[RTW_SSID_SCAN_AMOUNT];

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s\n", __func__));

	अगर (!rtw_pwr_wakeup(padapter)) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

	अगर (padapter->bDriverStopped) अणु
		DBG_88E("bDriverStopped =%d\n", padapter->bDriverStopped);
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

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING)) अणु
		indicate_wx_scan_complete_event(padapter);
		जाओ निकास;
	पूर्ण

/*	For the DMP WiFi Display project, the driver won't to scan because */
/*	the pmlmepriv->scan_पूर्णांकerval is always equal to 3. */
/*	So, the wpa_supplicant won't find out the WPS SoftAP. */

	स_रखो(ssid, 0, माप(काष्ठा ndis_802_11_ssid) * RTW_SSID_SCAN_AMOUNT);

	अगर (wrqu->data.length == माप(काष्ठा iw_scan_req)) अणु
		काष्ठा iw_scan_req *req = (काष्ठा iw_scan_req *)extra;

		अगर (wrqu->data.flags & IW_SCAN_THIS_ESSID) अणु
			पूर्णांक len = min_t(पूर्णांक, req->essid_len,
					IW_ESSID_MAX_SIZE);

			स_नकल(ssid[0].ssid, req->essid, len);
			ssid[0].ssid_length = len;

			DBG_88E("IW_SCAN_THIS_ESSID, ssid =%s, len =%d\n", req->essid, req->essid_len);

			spin_lock_bh(&pmlmepriv->lock);

			_status = rtw_sitesurvey_cmd(padapter, ssid, 1, शून्य, 0);

			spin_unlock_bh(&pmlmepriv->lock);
		पूर्ण अन्यथा अगर (req->scan_type == IW_SCAN_TYPE_PASSIVE) अणु
			DBG_88E("%s, req->scan_type == IW_SCAN_TYPE_PASSIVE\n", __func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (wrqu->data.length >= WEXT_CSCAN_HEADER_SIZE &&
		    !स_भेद(extra, WEXT_CSCAN_HEADER, WEXT_CSCAN_HEADER_SIZE)) अणु
			पूर्णांक len = wrqu->data.length - WEXT_CSCAN_HEADER_SIZE;
			अक्षर *pos = extra + WEXT_CSCAN_HEADER_SIZE;
			अक्षर section;
			अक्षर sec_len;
			पूर्णांक ssid_index = 0;

			जबतक (len >= 1) अणु
				section = *(pos++);
				len -= 1;

				चयन (section) अणु
				हाल WEXT_CSCAN_SSID_SECTION:
					अगर (len < 1) अणु
						len = 0;
						अवरोध;
					पूर्ण
					sec_len = *(pos++); len -= 1;
					अगर (sec_len > 0 &&
					    sec_len <= len &&
					    sec_len <= 32) अणु
						ssid[ssid_index].ssid_length = sec_len;
						स_नकल(ssid[ssid_index].ssid, pos, sec_len);
						ssid_index++;
					पूर्ण
					pos += sec_len;
					len -= sec_len;
					अवरोध;
				हाल WEXT_CSCAN_TYPE_SECTION:
				हाल WEXT_CSCAN_CHANNEL_SECTION:
					pos += 1;
					len -= 1;
					अवरोध;
				हाल WEXT_CSCAN_PASV_DWELL_SECTION:
				हाल WEXT_CSCAN_HOME_DWELL_SECTION:
				हाल WEXT_CSCAN_ACTV_DWELL_SECTION:
					pos += 2;
					len -= 2;
					अवरोध;
				शेष:
					len = 0; /*  stop parsing */
				पूर्ण
			पूर्ण

			/* it has still some scan parameter to parse, we only करो this now... */
			_status = rtw_set_802_11_bssid_list_scan(padapter, ssid, RTW_SSID_SCAN_AMOUNT);
		पूर्ण अन्यथा अणु
			_status = rtw_set_802_11_bssid_list_scan(padapter, शून्य, 0);
		पूर्ण
	पूर्ण

	अगर (!_status)
		ret = -1;

निकास:

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_scan(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा list_head *plist, *phead;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा __queue *queue	= &pmlmepriv->scanned_queue;
	काष्ठा	wlan_network	*pnetwork = शून्य;
	अक्षर *ev = extra;
	अक्षर *stop = ev + wrqu->data.length;
	u32 ret = 0;
	u32 cnt = 0;
	u32 रुको_क्रम_surveyकरोne;
	पूर्णांक रुको_status;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s\n", __func__));
	RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_, (" Start of Query SIOCGIWSCAN .\n"));

	अगर (padapter->pwrctrlpriv.brfoffbyhw && padapter->bDriverStopped) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	रुको_क्रम_surveyकरोne = 100;

	रुको_status = _FW_UNDER_SURVEY | _FW_UNDER_LINKING;

	जबतक (check_fwstate(pmlmepriv, रुको_status)) अणु
		msleep(30);
		cnt++;
		अगर (cnt > रुको_क्रम_surveyकरोne)
			अवरोध;
	पूर्ण

	spin_lock_bh(&pmlmepriv->scanned_queue.lock);

	phead = get_list_head(queue);
	plist = phead->next;

	जबतक (phead != plist) अणु
		अगर ((stop - ev) < SCAN_ITEM_SIZE) अणु
			ret = -E2BIG;
			अवरोध;
		पूर्ण

		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		/* report network only अगर the current channel set contains the channel to which this network beदीर्घs */
		अगर (rtw_ch_set_search_ch(padapter->mlmeextpriv.channel_set, pnetwork->network.Configuration.DSConfig) >= 0)
			ev = translate_scan(padapter, a, pnetwork, ev, stop);

		plist = plist->next;
	पूर्ण

	spin_unlock_bh(&pmlmepriv->scanned_queue.lock);

	wrqu->data.length = ev - extra;
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
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा list_head *phead;
	काष्ठा wlan_network *pnetwork = शून्य;
	क्रमागत ndis_802_11_auth_mode authmode;
	काष्ठा ndis_802_11_ssid ndis_ssid;
	u8 *dst_ssid, *src_ssid;

	uपूर्णांक ret = 0, len;

	RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
		 ("+%s: fw_state = 0x%08x\n", __func__, get_fwstate(pmlmepriv)));
	अगर (!rtw_pwr_wakeup(padapter)) अणु
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
	DBG_88E("=>%s\n", __func__);
	अगर (wrqu->essid.flags && wrqu->essid.length) अणु
		len = min_t(uपूर्णांक, wrqu->essid.length, IW_ESSID_MAX_SIZE);

		अगर (wrqu->essid.length != 33)
			DBG_88E("ssid =%s, len =%d\n", extra, wrqu->essid.length);

		स_रखो(&ndis_ssid, 0, माप(काष्ठा ndis_802_11_ssid));
		ndis_ssid.ssid_length = len;
		स_नकल(ndis_ssid.ssid, extra, len);
		src_ssid = ndis_ssid.ssid;

		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_, ("%s: ssid =[%s]\n", __func__, src_ssid));
		spin_lock_bh(&queue->lock);
		phead = get_list_head(queue);
		pmlmepriv->pscanned = phead->next;

		जबतक (phead != pmlmepriv->pscanned) अणु
			pnetwork = container_of(pmlmepriv->pscanned, काष्ठा wlan_network, list);

			pmlmepriv->pscanned = pmlmepriv->pscanned->next;

			dst_ssid = pnetwork->network.ssid.ssid;

			RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
				 ("%s: dst_ssid =%s\n", __func__,
				  pnetwork->network.ssid.ssid));

			अगर ((!स_भेद(dst_ssid, src_ssid, ndis_ssid.ssid_length)) &&
			    (pnetwork->network.ssid.ssid_length == ndis_ssid.ssid_length)) अणु
				RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
					 ("%s: find match, set infra mode\n", __func__));

				अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
					अगर (pnetwork->network.Infraकाष्ठाureMode != pmlmepriv->cur_network.network.Infraकाष्ठाureMode)
						जारी;
				पूर्ण

				अगर (!rtw_set_802_11_infraकाष्ठाure_mode(padapter, pnetwork->network.Infraकाष्ठाureMode)) अणु
					ret = -1;
					spin_unlock_bh(&queue->lock);
					जाओ निकास;
				पूर्ण

				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&queue->lock);
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
			 ("set ssid: set_802_11_auth. mode =%d\n", authmode));
		rtw_set_802_11_authentication_mode(padapter, authmode);
		अगर (!rtw_set_802_11_ssid(padapter, &ndis_ssid)) अणु
			ret = -1;
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	DBG_88E("<=%s, ret %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wx_get_essid(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *a,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u32 len;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex  *pcur_bss = &pmlmepriv->cur_network.network;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s\n", __func__));

	अगर ((check_fwstate(pmlmepriv, _FW_LINKED)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE))) अणु
		len = pcur_bss->ssid.ssid_length;
		स_नकल(extra, pcur_bss->ssid.ssid, len);
	पूर्ण अन्यथा अणु
		len = 0;
		*extra = 0;
	पूर्ण
	wrqu->essid.length = len;
	wrqu->essid.flags = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_rate(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *a,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक i;
	u8 datarates[NumRates];
	u32	target_rate = wrqu->bitrate.value;
	u32	fixed = wrqu->bitrate.fixed;
	u32	ratevalue = 0;
	u8 mpdatarate[NumRates] = अणु11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0xffपूर्ण;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s\n", __func__));
	RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_, ("target_rate = %d, fixed = %d\n", target_rate, fixed));

	अगर (target_rate == -1) अणु
		ratevalue = 11;
		जाओ set_rate;
	पूर्ण
	target_rate /= 100000;

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

		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_, ("datarate_inx =%d\n", datarates[i]));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_rate(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	u16 max_rate = 0;

	max_rate = rtw_get_cur_max_rate(netdev_priv(dev));

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
	काष्ठा adapter *padapter = netdev_priv(dev);

	अगर (wrqu->rts.disabled) अणु
		padapter->registrypriv.rts_thresh = 2347;
	पूर्ण अन्यथा अणु
		अगर (wrqu->rts.value < 0 ||
		    wrqu->rts.value > 2347)
			वापस -EINVAL;

		padapter->registrypriv.rts_thresh = wrqu->rts.value;
	पूर्ण

	DBG_88E("%s, rts_thresh =%d\n", __func__, padapter->registrypriv.rts_thresh);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_rts(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);

	DBG_88E("%s, rts_thresh =%d\n", __func__, padapter->registrypriv.rts_thresh);

	wrqu->rts.value = padapter->registrypriv.rts_thresh;
	wrqu->rts.fixed = 0;	/* no स्वतः select */
	/* wrqu->rts.disabled = (wrqu->rts.value == DEFAULT_RTS_THRESHOLD); */

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_frag(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);

	अगर (wrqu->frag.disabled) अणु
		padapter->xmitpriv.frag_len = MAX_FRAG_THRESHOLD;
	पूर्ण अन्यथा अणु
		अगर (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD)
			वापस -EINVAL;

		padapter->xmitpriv.frag_len = wrqu->frag.value & ~0x1;
	पूर्ण

	DBG_88E("%s, frag_len =%d\n", __func__, padapter->xmitpriv.frag_len);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_frag(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);

	DBG_88E("%s, frag_len =%d\n", __func__, padapter->xmitpriv.frag_len);

	wrqu->frag.value = padapter->xmitpriv.frag_len;
	wrqu->frag.fixed = 0;	/* no स्वतः select */

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_retry(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
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
	क्रमागत ndis_802_11_auth_mode authmode;

	काष्ठा iw_poपूर्णांक *erq = &wrqu->encoding;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;

	DBG_88E("+%s, flags = 0x%x\n", __func__, erq->flags);

	स_रखो(&wep, 0, माप(काष्ठा ndis_802_11_wep));

	key = erq->flags & IW_ENCODE_INDEX;

	अगर (erq->flags & IW_ENCODE_DISABLED) अणु
		DBG_88E("EncryptionDisabled\n");
		padapter->securitypriv.ndisencryptstatus = Ndis802_11EncryptionDisabled;
		padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
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
		DBG_88E("%s, key =%d\n", __func__, key);
	पूर्ण

	/* set authentication mode */
	अगर (erq->flags & IW_ENCODE_OPEN) अणु
		DBG_88E("%s():IW_ENCODE_OPEN\n", __func__);
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;/* Ndis802_11EncryptionDisabled; */
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
		padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
		authmode = Ndis802_11AuthModeOpen;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण अन्यथा अगर (erq->flags & IW_ENCODE_RESTRICTED) अणु
		DBG_88E("%s():IW_ENCODE_RESTRICTED\n", __func__);
		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Shared;
		padapter->securitypriv.करोt11PrivacyAlgrthm = _WEP40_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _WEP40_;
		authmode = Ndis802_11AuthModeShared;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण अन्यथा अणु
		DBG_88E("%s():erq->flags = 0x%x\n", __func__, erq->flags);

		padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;/* Ndis802_11EncryptionDisabled; */
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
		padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
		authmode = Ndis802_11AuthModeOpen;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण

	wep.KeyIndex = key;
	अगर (erq->length > 0) अणु
		wep.KeyLength = erq->length <= 5 ? 5 : 13;

		wep.Length = wep.KeyLength + दुरत्व(काष्ठा ndis_802_11_wep, KeyMaterial);
	पूर्ण अन्यथा अणु
		wep.KeyLength = 0;

		अगर (keyindex_provided == 1) अणु
			/*  set key_id only, no given KeyMaterial(erq->length == 0). */
			padapter->securitypriv.करोt11PrivacyKeyIndex = key;

			DBG_88E("(keyindex_provided == 1), keyid =%d, key_len =%d\n", key, padapter->securitypriv.करोt11DefKeylen[key]);

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

	अगर (!rtw_set_802_11_add_wep(padapter, &wep)) अणु
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
	uपूर्णांक key;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *erq = &wrqu->encoding;
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;

	अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		अगर (!check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
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

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_get_घातer(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	wrqu->घातer.value = 0;
	wrqu->घातer.fixed = 0;	/* no स्वतः select */
	wrqu->घातer.disabled = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wx_set_gen_ie(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);

	वापस rtw_set_wpa_ie(padapter, extra, wrqu->data.length);
पूर्ण

अटल पूर्णांक rtw_wx_set_auth(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा iw_param *param = (काष्ठा iw_param *)&wrqu->param;
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
		अगर (param->value) अणु
			/*  wpa_supplicant is enabling the tkip countermeasure. */
			padapter->securitypriv.btkip_countermeasure = true;
		पूर्ण अन्यथा अणु
			/*  wpa_supplicant is disabling the tkip countermeasure. */
			padapter->securitypriv.btkip_countermeasure = false;
		पूर्ण
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

		अगर (padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption1Enabled)
			अवरोध;/* it means init value, or using wep, ndisencryptstatus = Ndis802_11Encryption1Enabled, */
					/*  then it needn't reset it; */

		अगर (param->value) अणु
			padapter->securitypriv.ndisencryptstatus = Ndis802_11EncryptionDisabled;
			padapter->securitypriv.करोt11PrivacyAlgrthm = _NO_PRIVACY_;
			padapter->securitypriv.करोt118021XGrpPrivacy = _NO_PRIVACY_;
			padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
		पूर्ण

		अवरोध;
	हाल IW_AUTH_80211_AUTH_ALG:
		/* It's the starting poपूर्णांक of a link layer connection using wpa_supplicant */
		अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
			LeaveAllPowerSaveMode(padapter);
			rtw_disassoc_cmd(padapter, 500, false);
			DBG_88E("%s...call rtw_indicate_disconnect\n ", __func__);
			rtw_indicate_disconnect(padapter);
			rtw_मुक्त_assoc_resources(padapter);
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
	param = (काष्ठा ieee_param *)rtw_दो_स्मृति(param_len);
	अगर (!param)
		वापस -1;

	स_रखो(param, 0, param_len);

	param->cmd = IEEE_CMD_SET_ENCRYPTION;
	eth_broadcast_addr(param->sta_addr);

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
	शेष:
		ret = -1;
		जाओ निकास;
	पूर्ण

	strscpy((अक्षर *)param->u.crypt.alg, alg_name, IEEE_CRYPT_ALG_NAME_LEN);

	अगर (pext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY)
		param->u.crypt.set_tx = 1;

	/* cliW: WEP करोes not have group key
	 * just not checking GROUP key setting
	 */
	अगर ((pext->alg != IW_ENCODE_ALG_WEP) &&
	    (pext->ext_flags & IW_ENCODE_EXT_GROUP_KEY))
		param->u.crypt.set_tx = 0;

	param->u.crypt.idx = (pencoding->flags & 0x00FF) - 1;

	अगर (pext->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID)
		स_नकल(param->u.crypt.seq, pext->rx_seq, 8);

	अगर (pext->key_len) अणु
		param->u.crypt.key_len = pext->key_len;
		स_नकल(param->u.crypt.key, pext + 1, pext->key_len);
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
	अगर (extra) अणु
		wrqu->data.length = 14;
		wrqu->data.flags = 1;
		स_नकल(extra, "<WIFI@REALTEK>", 14);
	पूर्ण

	/* dump debug info here */
	वापस 0;
पूर्ण

अटल पूर्णांक dummy(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
		 जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक wpa_set_param(काष्ठा net_device *dev, u8 name, u32 value)
अणु
	uपूर्णांक ret = 0;
	काष्ठा adapter *padapter = netdev_priv(dev);

	चयन (name) अणु
	हाल IEEE_PARAM_WPA_ENABLED:
		padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X; /* 802.1x */
		चयन (value & 0xff) अणु
		हाल 1: /* WPA */
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPAPSK; /* WPA_PSK */
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
			अवरोध;
		हाल 2: /* WPA2 */
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPA2PSK; /* WPA2_PSK */
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
			अवरोध;
		पूर्ण
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
			 ("%s:padapter->securitypriv.ndisauthtype =%d\n", __func__, padapter->securitypriv.ndisauthtype));
		अवरोध;
	हाल IEEE_PARAM_TKIP_COUNTERMEASURES:
		अवरोध;
	हाल IEEE_PARAM_DROP_UNENCRYPTED: अणु
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
		अवरोध;

	हाल IEEE_PARAM_AUTH_ALGS:
		ret = wpa_set_auth_algs(dev, value);
		अवरोध;
	हाल IEEE_PARAM_IEEE_802_1X:
		अवरोध;
	हाल IEEE_PARAM_WPAX_SELECT:
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
	काष्ठा adapter *padapter = netdev_priv(dev);

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

	अगर (!p->poपूर्णांकer || p->length != माप(काष्ठा ieee_param))
		वापस -EINVAL;

	param = memdup_user(p->poपूर्णांकer, p->length);
	अगर (IS_ERR(param))
		वापस PTR_ERR(param);

	चयन (param->cmd) अणु
	हाल IEEE_CMD_SET_WPA_PARAM:
		ret = wpa_set_param(dev, param->u.wpa_param.name, param->u.wpa_param.value);
		अवरोध;

	हाल IEEE_CMD_SET_WPA_IE:
		ret =  rtw_set_wpa_ie(netdev_priv(dev),
				      (अक्षर *)param->u.wpa_ie.data, (u16)param->u.wpa_ie.len);
		अवरोध;

	हाल IEEE_CMD_SET_ENCRYPTION:
		ret = wpa_set_encryption(dev, param, p->length);
		अवरोध;

	हाल IEEE_CMD_MLME:
		ret = wpa_mlme(dev, param->u.mlme.command, param->u.mlme.reason_code);
		अवरोध;

	शेष:
		DBG_88E("Unknown WPA supplicant request: %d\n", param->cmd);
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर (ret == 0 && copy_to_user(p->poपूर्णांकer, param, p->length))
		ret = -EFAULT;

	kमुक्त(param);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_88EU_AP_MODE
अटल u8 set_pairwise_key(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा set_stakey_parm	*psetstakey_para;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ph2c = kzalloc(माप(काष्ठा cmd_obj), GFP_KERNEL);
	अगर (!ph2c) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	psetstakey_para = kzalloc(माप(काष्ठा set_stakey_parm), GFP_KERNEL);
	अगर (!psetstakey_para) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);

	psetstakey_para->algorithm = (u8)psta->करोt118021XPrivacy;

	स_नकल(psetstakey_para->addr, psta->hwaddr, ETH_ALEN);

	स_नकल(psetstakey_para->key, &psta->करोt118021x_UncstKey, 16);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:

	वापस res;
पूर्ण

अटल पूर्णांक set_group_key(काष्ठा adapter *padapter, u8 *key, u8 alg, पूर्णांक keyid)
अणु
	u8 keylen;
	काष्ठा cmd_obj *pcmd;
	काष्ठा setkey_parm *psetkeyparm;
	काष्ठा cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	पूर्णांक res = _SUCCESS;

	DBG_88E("%s\n", __func__);

	pcmd = kzalloc(माप(काष्ठा	cmd_obj), GFP_KERNEL);
	अगर (!pcmd) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	psetkeyparm = kzalloc(माप(काष्ठा setkey_parm), GFP_KERNEL);
	अगर (!psetkeyparm) अणु
		kमुक्त(pcmd);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	psetkeyparm->keyid = (u8)keyid;

	psetkeyparm->algorithm = alg;

	psetkeyparm->set_tx = 1;

	चयन (alg) अणु
	हाल _WEP40_:
		keylen = 5;
		अवरोध;
	हाल _WEP104_:
		keylen = 13;
		अवरोध;
	हाल _TKIP_:
	हाल _TKIP_WTMIC_:
	हाल _AES_:
	शेष:
		keylen = 16;
	पूर्ण

	स_नकल(&psetkeyparm->key[0], key, keylen);

	pcmd->cmdcode = _SetKey_CMD_;
	pcmd->parmbuf = (u8 *)psetkeyparm;
	pcmd->cmdsz =  (माप(काष्ठा setkey_parm));
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;

	INIT_LIST_HEAD(&pcmd->list);

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);

निकास:

	वापस res;
पूर्ण

अटल पूर्णांक set_wep_key(काष्ठा adapter *padapter, u8 *key, u8 keylen, पूर्णांक keyid)
अणु
	u8 alg;

	चयन (keylen) अणु
	हाल 5:
		alg = _WEP40_;
		अवरोध;
	हाल 13:
		alg = _WEP104_;
		अवरोध;
	शेष:
		alg = _NO_PRIVACY_;
	पूर्ण

	वापस set_group_key(padapter, key, alg, keyid);
पूर्ण

अटल पूर्णांक rtw_set_encryption(काष्ठा net_device *dev, काष्ठा ieee_param *param, u32 param_len)
अणु
	पूर्णांक ret = 0;
	u32 wep_key_idx, wep_key_len, wep_total_len;
	काष्ठा ndis_802_11_wep	 *pwep = शून्य;
	काष्ठा sta_info *psta = शून्य, *pbcmc_sta = शून्य;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	DBG_88E("%s\n", __func__);
	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';
	अगर (param_len !=  माप(काष्ठा ieee_param) + param->u.crypt.key_len) अणु
		ret =  -EINVAL;
		जाओ निकास;
	पूर्ण
	अगर (is_broadcast_ether_addr(param->sta_addr)) अणु
		अगर (param->u.crypt.idx >= WEP_KEYS) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		psta = rtw_get_stainfo(pstapriv, param->sta_addr);
		अगर (!psta) अणु
			DBG_88E("%s(), sta has already been removed or never been added\n", __func__);
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (म_भेद(param->u.crypt.alg, "none") == 0 && (!psta)) अणु
		/* toकरो:clear शेष encryption keys */

		DBG_88E("clear default encryption keys, keyid =%d\n", param->u.crypt.idx);
		जाओ निकास;
	पूर्ण
	अगर (म_भेद(param->u.crypt.alg, "WEP") == 0 && (!psta)) अणु
		DBG_88E("r871x_set_encryption, crypt.alg = WEP\n");
		wep_key_idx = param->u.crypt.idx;
		wep_key_len = param->u.crypt.key_len;
		DBG_88E("r871x_set_encryption, wep_key_idx=%d, len=%d\n", wep_key_idx, wep_key_len);
		अगर ((wep_key_idx >= WEP_KEYS) || (wep_key_len <= 0)) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण

		अगर (wep_key_len > 0) अणु
			wep_key_len = wep_key_len <= 5 ? 5 : 13;
			wep_total_len = wep_key_len + दुरत्व(काष्ठा ndis_802_11_wep, KeyMaterial);
			pwep = (काष्ठा ndis_802_11_wep *)rtw_दो_स्मृति(wep_total_len);
			अगर (!pwep) अणु
				DBG_88E(" r871x_set_encryption: pwep allocate fail !!!\n");
				जाओ निकास;
			पूर्ण

			स_रखो(pwep, 0, wep_total_len);

			pwep->KeyLength = wep_key_len;
			pwep->Length = wep_total_len;
		पूर्ण

		pwep->KeyIndex = wep_key_idx;

		स_नकल(pwep->KeyMaterial,  param->u.crypt.key, pwep->KeyLength);

		अगर (param->u.crypt.set_tx) अणु
			DBG_88E("wep, set_tx = 1\n");

			psecuritypriv->ndisencryptstatus = Ndis802_11Encryption1Enabled;
			psecuritypriv->करोt11PrivacyAlgrthm = _WEP40_;
			psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;

			अगर (pwep->KeyLength == 13) अणु
				psecuritypriv->करोt11PrivacyAlgrthm = _WEP104_;
				psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
			पूर्ण

			psecuritypriv->करोt11PrivacyKeyIndex = wep_key_idx;

			स_नकल(&psecuritypriv->करोt11DefKey[wep_key_idx].skey[0], pwep->KeyMaterial, pwep->KeyLength);

			psecuritypriv->करोt11DefKeylen[wep_key_idx] = pwep->KeyLength;

			set_wep_key(padapter, pwep->KeyMaterial, pwep->KeyLength, wep_key_idx);
		पूर्ण अन्यथा अणु
			DBG_88E("wep, set_tx = 0\n");

			/* करोn't update "psecuritypriv->dot11PrivacyAlgrthm" and */
			/* psecuritypriv->करोt11PrivacyKeyIndex = keyid", but can rtw_set_key to cam */

			स_नकल(&psecuritypriv->करोt11DefKey[wep_key_idx].skey[0], pwep->KeyMaterial, pwep->KeyLength);

			psecuritypriv->करोt11DefKeylen[wep_key_idx] = pwep->KeyLength;

			set_wep_key(padapter, pwep->KeyMaterial, pwep->KeyLength, wep_key_idx);
		पूर्ण

		जाओ निकास;
	पूर्ण

	अगर (!psta && check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु /*  group key */
		अगर (param->u.crypt.set_tx == 1) अणु
			अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
				DBG_88E("%s, set group_key, WEP\n", __func__);

				स_नकल(psecuritypriv->करोt118021XGrpKey[param->u.crypt.idx].skey,
				       param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));

				psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;
				अगर (param->u.crypt.key_len == 13)
					psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
			पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु
				DBG_88E("%s, set group_key, TKIP\n", __func__);
				psecuritypriv->करोt118021XGrpPrivacy = _TKIP_;
				स_नकल(psecuritypriv->करोt118021XGrpKey[param->u.crypt.idx].skey,
				       param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));
				/* set mic key */
				स_नकल(psecuritypriv->करोt118021XGrptxmickey[param->u.crypt.idx].skey, &param->u.crypt.key[16], 8);
				स_नकल(psecuritypriv->करोt118021XGrprxmickey[param->u.crypt.idx].skey, &param->u.crypt.key[24], 8);

				psecuritypriv->busetkipkey = true;
			पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु
				DBG_88E("%s, set group_key, CCMP\n", __func__);
				psecuritypriv->करोt118021XGrpPrivacy = _AES_;
				स_नकल(psecuritypriv->करोt118021XGrpKey[param->u.crypt.idx].skey,
				       param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));
			पूर्ण अन्यथा अणु
				DBG_88E("%s, set group_key, none\n", __func__);
				psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
			पूर्ण
			psecuritypriv->करोt118021XGrpKeyid = param->u.crypt.idx;
			psecuritypriv->binstallGrpkey = true;
			psecuritypriv->करोt11PrivacyAlgrthm = psecuritypriv->करोt118021XGrpPrivacy;/*  */
			set_group_key(padapter, param->u.crypt.key, psecuritypriv->करोt118021XGrpPrivacy, param->u.crypt.idx);
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
			अगर (param->u.crypt.set_tx == 1) अणु
				स_नकल(psta->करोt118021x_UncstKey.skey,  param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));

				अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
					DBG_88E("%s, set pairwise key, WEP\n", __func__);

					psta->करोt118021XPrivacy = _WEP40_;
					अगर (param->u.crypt.key_len == 13)
						psta->करोt118021XPrivacy = _WEP104_;
				पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु
					DBG_88E("%s, set pairwise key, TKIP\n", __func__);

					psta->करोt118021XPrivacy = _TKIP_;

					/* set mic key */
					स_नकल(psta->करोt11tkiptxmickey.skey, &param->u.crypt.key[16], 8);
					स_नकल(psta->करोt11tkiprxmickey.skey, &param->u.crypt.key[24], 8);

					psecuritypriv->busetkipkey = true;
				पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु
					DBG_88E("%s, set pairwise key, CCMP\n", __func__);

					psta->करोt118021XPrivacy = _AES_;
				पूर्ण अन्यथा अणु
					DBG_88E("%s, set pairwise key, none\n", __func__);

					psta->करोt118021XPrivacy = _NO_PRIVACY_;
				पूर्ण

				set_pairwise_key(padapter, psta);

				psta->ieee8021x_blocked = false;
			पूर्ण अन्यथा अणु /* group key??? */
				अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
					स_नकल(psecuritypriv->करोt118021XGrpKey[param->u.crypt.idx].skey,
					       param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));
					psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;
					अगर (param->u.crypt.key_len == 13)
						psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
				पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु
					psecuritypriv->करोt118021XGrpPrivacy = _TKIP_;

					स_नकल(psecuritypriv->करोt118021XGrpKey[param->u.crypt.idx].skey,
					       param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));

					/* set mic key */
					स_नकल(psecuritypriv->करोt118021XGrptxmickey[param->u.crypt.idx].skey, &param->u.crypt.key[16], 8);
					स_नकल(psecuritypriv->करोt118021XGrprxmickey[param->u.crypt.idx].skey, &param->u.crypt.key[24], 8);

					psecuritypriv->busetkipkey = true;
				पूर्ण अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु
					psecuritypriv->करोt118021XGrpPrivacy = _AES_;

					स_नकल(psecuritypriv->करोt118021XGrpKey[param->u.crypt.idx].skey,
					       param->u.crypt.key, min_t(u16, param->u.crypt.key_len, 16));
				पूर्ण अन्यथा अणु
					psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
				पूर्ण

				psecuritypriv->करोt118021XGrpKeyid = param->u.crypt.idx;

				psecuritypriv->binstallGrpkey = true;

				psecuritypriv->करोt11PrivacyAlgrthm = psecuritypriv->करोt118021XGrpPrivacy;/*  */

				set_group_key(padapter, param->u.crypt.key, psecuritypriv->करोt118021XGrpPrivacy, param->u.crypt.idx);

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
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	अचिन्हित अक्षर *pbuf = param->u.bcn_ie.buf;

	DBG_88E("%s, len =%d\n", __func__, len);

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस -EINVAL;

	स_नकल(&pstapriv->max_num_sta, param->u.bcn_ie.reserved, 2);

	अगर ((pstapriv->max_num_sta > NUM_STA) || (pstapriv->max_num_sta <= 0))
		pstapriv->max_num_sta = NUM_STA;

	अगर (rtw_check_beacon_data(padapter, pbuf, len - 12 - 2) == _SUCCESS) /* 12 = param header, 2:no packed */
		ret = 0;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_hostapd_sta_flush(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);

	DBG_88E("%s\n", __func__);

	flush_all_cam_entry(padapter);	/* clear CAM */

	वापस rtw_sta_flush(padapter);
पूर्ण

अटल पूर्णांक rtw_add_sta(काष्ठा net_device *dev, काष्ठा ieee_param *param)
अणु
	पूर्णांक ret = 0;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	DBG_88E("%s(aid =%d) =%pM\n", __func__, param->u.add_sta.aid, (param->sta_addr));

	अगर (!check_fwstate(pmlmepriv, (_FW_LINKED | WIFI_AP_STATE)))
		वापस -EINVAL;

	अगर (is_broadcast_ether_addr(param->sta_addr))
		वापस -EINVAL;

	psta = rtw_get_stainfo(pstapriv, param->sta_addr);
	अगर (psta) अणु
		पूर्णांक flags = param->u.add_sta.flags;

		psta->aid = param->u.add_sta.aid;/* aid = 1~2007 */

		स_नकल(psta->bssrateset, param->u.add_sta.tx_supp_rates, 16);

		/* check wmm cap. */
		अगर (WLAN_STA_WME & flags)
			psta->qos_option = 1;
		अन्यथा
			psta->qos_option = 0;

		अगर (pmlmepriv->qospriv.qos_option == 0)
			psta->qos_option = 0;

		/* chec 802.11n ht cap. */
		अगर (WLAN_STA_HT & flags) अणु
			psta->htpriv.ht_option = true;
			psta->qos_option = 1;
			स_नकल(&psta->htpriv.ht_cap, &param->u.add_sta.ht_cap,
			       माप(काष्ठा ieee80211_ht_cap));
		पूर्ण अन्यथा अणु
			psta->htpriv.ht_option = false;
		पूर्ण

		अगर (!pmlmepriv->htpriv.ht_option)
			psta->htpriv.ht_option = false;

		update_sta_info_apmode(padapter, psta);
	पूर्ण अन्यथा अणु
		ret = -ENOMEM;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_del_sta(काष्ठा net_device *dev, काष्ठा ieee_param *param)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	पूर्णांक updated = 0;

	DBG_88E("%s =%pM\n", __func__, (param->sta_addr));

	अगर (!check_fwstate(pmlmepriv, _FW_LINKED | WIFI_AP_STATE))
		वापस -EINVAL;

	अगर (is_broadcast_ether_addr(param->sta_addr))
		वापस -EINVAL;

	psta = rtw_get_stainfo(pstapriv, param->sta_addr);
	अगर (psta) अणु
		spin_lock_bh(&pstapriv->asoc_list_lock);
		अगर (!list_empty(&psta->asoc_list)) अणु
			list_del_init(&psta->asoc_list);
			pstapriv->asoc_list_cnt--;
			updated = ap_मुक्त_sta(padapter, psta, true, WLAN_REASON_DEAUTH_LEAVING);
		पूर्ण
		spin_unlock_bh(&pstapriv->asoc_list_lock);
		associated_clients_update(padapter, updated);
		psta = शून्य;
	पूर्ण अन्यथा अणु
		DBG_88E("%s(), sta has already been removed or never been added\n", __func__);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_ioctl_get_sta_data(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा ieee_param_ex *param_ex = (काष्ठा ieee_param_ex *)param;
	काष्ठा sta_data *psta_data = (काष्ठा sta_data *)param_ex->data;

	DBG_88E("rtw_ioctl_get_sta_info, sta_addr: %pM\n", (param_ex->sta_addr));

	अगर (!check_fwstate(pmlmepriv, _FW_LINKED | WIFI_AP_STATE))
		वापस -EINVAL;

	अगर (is_broadcast_ether_addr(param_ex->sta_addr))
		वापस -EINVAL;

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
		स_नकल(&psta_data->ht_cap,
		       &psta->htpriv.ht_cap, माप(काष्ठा ieee80211_ht_cap));
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
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	DBG_88E("%s, sta_addr: %pM\n", __func__, (param->sta_addr));

	अगर (!check_fwstate(pmlmepriv, _FW_LINKED | WIFI_AP_STATE))
		वापस -EINVAL;

	अगर (is_broadcast_ether_addr(param->sta_addr))
		वापस -EINVAL;

	psta = rtw_get_stainfo(pstapriv, param->sta_addr);
	अगर (psta) अणु
		अगर (psta->wpa_ie[0] == WLAN_EID_RSN ||
		    psta->wpa_ie[0] == WLAN_EID_VENDOR_SPECIFIC) अणु
			पूर्णांक wpa_ie_len;
			पूर्णांक copy_len;

			wpa_ie_len = psta->wpa_ie[1];
			copy_len = min_t(पूर्णांक, wpa_ie_len + 2, माप(psta->wpa_ie));
			param->u.wpa_ie.len = copy_len;
			स_नकल(param->u.wpa_ie.reserved, psta->wpa_ie, copy_len);
		पूर्ण अन्यथा अणु
			DBG_88E("sta's wpa_ie is NONE\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_set_wps_beacon(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	अचिन्हित अक्षर wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	पूर्णांक ie_len;

	DBG_88E("%s, len =%d\n", __func__, len);

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस -EINVAL;

	ie_len = len - 12 - 2; /* 12 = param header, 2:no packed */

	kमुक्त(pmlmepriv->wps_beacon_ie);
	pmlmepriv->wps_beacon_ie = शून्य;

	अगर (ie_len > 0) अणु
		pmlmepriv->wps_beacon_ie = rtw_दो_स्मृति(ie_len);
		pmlmepriv->wps_beacon_ie_len = ie_len;
		अगर (!pmlmepriv->wps_beacon_ie) अणु
			DBG_88E("%s()-%d: rtw_malloc() ERROR!\n", __func__, __LINE__);
			वापस -EINVAL;
		पूर्ण

		स_नकल(pmlmepriv->wps_beacon_ie, param->u.bcn_ie.buf, ie_len);

		update_beacon(padapter, WLAN_EID_VENDOR_SPECIFIC, wps_oui, true);

		pmlmeext->bstart_bss = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_set_wps_probe_resp(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	पूर्णांक ie_len;

	DBG_88E("%s, len =%d\n", __func__, len);

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस -EINVAL;

	ie_len = len - 12 - 2; /* 12 = param header, 2:no packed */

	kमुक्त(pmlmepriv->wps_probe_resp_ie);
	pmlmepriv->wps_probe_resp_ie = शून्य;

	अगर (ie_len > 0) अणु
		pmlmepriv->wps_probe_resp_ie = rtw_दो_स्मृति(ie_len);
		pmlmepriv->wps_probe_resp_ie_len = ie_len;
		अगर (!pmlmepriv->wps_probe_resp_ie) अणु
			DBG_88E("%s()-%d: rtw_malloc() ERROR!\n", __func__, __LINE__);
			वापस -EINVAL;
		पूर्ण
		स_नकल(pmlmepriv->wps_probe_resp_ie, param->u.bcn_ie.buf, ie_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_set_wps_assoc_resp(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	पूर्णांक ie_len;

	DBG_88E("%s, len =%d\n", __func__, len);

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस -EINVAL;

	ie_len = len - 12 - 2; /* 12 = param header, 2:no packed */

	kमुक्त(pmlmepriv->wps_assoc_resp_ie);
	pmlmepriv->wps_assoc_resp_ie = शून्य;

	अगर (ie_len > 0) अणु
		pmlmepriv->wps_assoc_resp_ie = rtw_दो_स्मृति(ie_len);
		pmlmepriv->wps_assoc_resp_ie_len = ie_len;
		अगर (!pmlmepriv->wps_assoc_resp_ie) अणु
			DBG_88E("%s()-%d: rtw_malloc() ERROR!\n", __func__, __LINE__);
			वापस -EINVAL;
		पूर्ण

		स_नकल(pmlmepriv->wps_assoc_resp_ie, param->u.bcn_ie.buf, ie_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_set_hidden_ssid(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	u8 value;

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस -EINVAL;

	अगर (param->u.wpa_param.name != 0) /* dummy test... */
		DBG_88E("%s name(%u) != 0\n", __func__, param->u.wpa_param.name);
	value = param->u.wpa_param.value;

	/* use the same definition of hostapd's ignore_broadcast_ssid */
	अगर (value != 1 && value != 2)
		value = 0;
	DBG_88E("%s value(%u)\n", __func__, value);
	pmlmeinfo->hidden_ssid_mode = value;
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_ioctl_acl_हटाओ_sta(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस -EINVAL;

	अगर (is_broadcast_ether_addr(param->sta_addr))
		वापस -EINVAL;

	वापस rtw_acl_हटाओ_sta(padapter, param->sta_addr);
पूर्ण

अटल पूर्णांक rtw_ioctl_acl_add_sta(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस -EINVAL;

	अगर (is_broadcast_ether_addr(param->sta_addr))
		वापस -EINVAL;

	वापस rtw_acl_add_sta(padapter, param->sta_addr);
पूर्ण

अटल पूर्णांक rtw_ioctl_set_macaddr_acl(काष्ठा net_device *dev, काष्ठा ieee_param *param, पूर्णांक len)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस -EINVAL;

	rtw_set_macaddr_acl(padapter, param->u.mlme.command);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_hostapd_ioctl(काष्ठा net_device *dev, काष्ठा iw_poपूर्णांक *p)
अणु
	काष्ठा ieee_param *param;
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = netdev_priv(dev);

	/*
	 * this function is expect to call in master mode, which allows no घातer saving
	 * so, we just check hw_init_completed
	 */

	अगर (!padapter->hw_init_completed)
		वापस -EPERM;

	अगर (!p->poपूर्णांकer || p->length != माप(काष्ठा ieee_param))
		वापस -EINVAL;

	param = memdup_user(p->poपूर्णांकer, p->length);
	अगर (IS_ERR(param))
		वापस PTR_ERR(param);

	चयन (param->cmd) अणु
	हाल RTL871X_HOSTAPD_FLUSH:
		ret = rtw_hostapd_sta_flush(dev);
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
		DBG_88E("Unknown hostapd request: %d\n", param->cmd);
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर (ret == 0 && copy_to_user(p->poपूर्णांकer, param, p->length))
		ret = -EFAULT;
	kमुक्त(param);
	वापस ret;
पूर्ण
#पूर्ण_अगर

#समावेश <rtw_android.h>
अटल पूर्णांक rtw_wx_set_priv(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *awrq, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	पूर्णांक len = 0;
	अक्षर *ext;
	काष्ठा adapter *padapter = netdev_priv(dev);
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

	/* added क्रम wps2.0 @20110524 */
	अगर (dwrq->flags == 0x8766 && len > 8) अणु
		u32 cp_sz;
		काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
		u8 *probereq_wpsie = ext;
		पूर्णांक probereq_wpsie_len = len;
		u8 wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;

		अगर ((probereq_wpsie[0] == WLAN_EID_VENDOR_SPECIFIC) &&
		    (!स_भेद(&probereq_wpsie[2], wps_oui, 4))) अणु
			cp_sz = min(probereq_wpsie_len, MAX_WPS_IE_LEN);

			pmlmepriv->wps_probe_req_ie_len = 0;
			kमुक्त(pmlmepriv->wps_probe_req_ie);
			pmlmepriv->wps_probe_req_ie = शून्य;

			pmlmepriv->wps_probe_req_ie = rtw_दो_स्मृति(cp_sz);
			अगर (!pmlmepriv->wps_probe_req_ie) अणु
				pr_info("%s()-%d: rtw_malloc() ERROR!\n", __func__, __LINE__);
				ret =  -EINVAL;
				जाओ FREE_EXT;
			पूर्ण
			स_नकल(pmlmepriv->wps_probe_req_ie, probereq_wpsie, cp_sz);
			pmlmepriv->wps_probe_req_ie_len = cp_sz;
		पूर्ण
		जाओ FREE_EXT;
	पूर्ण

	अगर (len >= WEXT_CSCAN_HEADER_SIZE &&
	    !स_भेद(ext, WEXT_CSCAN_HEADER, WEXT_CSCAN_HEADER_SIZE)) अणु
		ret = rtw_wx_set_scan(dev, info, awrq, ext);
		जाओ FREE_EXT;
	पूर्ण

FREE_EXT:

	vमुक्त(ext);

	वापस ret;
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

अटल काष्ठा iw_statistics *rtw_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *padapter = netdev_priv(dev);
	काष्ठा iw_statistics *piwstats = &padapter->iwstats;
	पूर्णांक पंचांगp_level = 0;
	पूर्णांक पंचांगp_qual = 0;
	पूर्णांक पंचांगp_noise = 0;

	अगर (!check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
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
	piwstats->qual.updated = IW_QUAL_ALL_UPDATED;/* IW_QUAL_DBM; */
	वापस &padapter->iwstats;
पूर्ण

काष्ठा iw_handler_def rtw_handlers_def = अणु
	.standard = rtw_handlers,
	.num_standard = ARRAY_SIZE(rtw_handlers),
	.get_wireless_stats = rtw_get_wireless_stats,
पूर्ण;

पूर्णांक rtw_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा iwreq *wrq = (काष्ठा iwreq *)rq;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल RTL_IOCTL_WPA_SUPPLICANT:
		ret = wpa_supplicant_ioctl(dev, &wrq->u.data);
		अवरोध;
#अगर_घोषित CONFIG_88EU_AP_MODE
	हाल RTL_IOCTL_HOSTAPD:
		ret = rtw_hostapd_ioctl(dev, &wrq->u.data);
		अवरोध;
#पूर्ण_अगर /*  CONFIG_88EU_AP_MODE */
	हाल (SIOCDEVPRIVATE + 1):
		ret = rtw_android_priv_cmd(dev, rq, cmd);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
