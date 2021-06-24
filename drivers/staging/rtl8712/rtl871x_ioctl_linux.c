<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_ioctl_linux.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL871X_IOCTL_LINUX_C_
#घोषणा _RTL871X_MP_IOCTL_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "wlan_bssdef.h"
#समावेश "rtl871x_debug.h"
#समावेश "wifi.h"
#समावेश "rtl871x_mlme.h"
#समावेश "rtl871x_ioctl.h"
#समावेश "rtl871x_ioctl_set.h"
#समावेश "rtl871x_mp_ioctl.h"
#समावेश "mlme_osdep.h"
#समावेश <linux/wireless.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/semaphore.h>
#समावेश <net/iw_handler.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>

#घोषणा RTL_IOCTL_WPA_SUPPLICANT	(SIOCIWFIRSTPRIV + 0x1E)

#घोषणा SCAN_ITEM_SIZE 768
#घोषणा MAX_CUSTOM_LEN 64
#घोषणा RATE_COUNT 4

अटल स्थिर u32 rtl8180_rates[] = अणु1000000, 2000000, 5500000, 11000000,
		       6000000, 9000000, 12000000, 18000000,
		       24000000, 36000000, 48000000, 54000000पूर्ण;

अटल स्थिर दीर्घ ieee80211_wlan_frequencies[] = अणु
	2412, 2417, 2422, 2427,
	2432, 2437, 2442, 2447,
	2452, 2457, 2462, 2467,
	2472, 2484
पूर्ण;

व्योम r8712_indicate_wx_assoc_event(काष्ठा _adapter *padapter)
अणु
	जोड़ iwreq_data wrqu;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(wrqu.ap_addr.sa_data, pmlmepriv->cur_network.network.MacAddress,
		ETH_ALEN);
	wireless_send_event(padapter->pnetdev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण

व्योम r8712_indicate_wx_disassoc_event(काष्ठा _adapter *padapter)
अणु
	जोड़ iwreq_data wrqu;

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	eth_zero_addr(wrqu.ap_addr.sa_data);
	wireless_send_event(padapter->pnetdev, SIOCGIWAP, &wrqu, शून्य);
पूर्ण

अटल अंतरभूत व्योम handle_pairwise_key(काष्ठा sta_info *psta,
				       काष्ठा ieee_param *param,
				       काष्ठा _adapter *padapter)
अणु
	/* pairwise key */
	स_नकल(psta->x_UncstKey.skey, param->u.crypt.key,
	       (param->u.crypt. key_len > 16 ? 16 : param->u.crypt.key_len));
	अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु /* set mic key */
		स_नकल(psta->tkiptxmickey. skey,
		       &(param->u.crypt.key[16]), 8);
		स_नकल(psta->tkiprxmickey. skey,
		       &(param->u.crypt.key[24]), 8);
		padapter->securitypriv. busetkipkey = false;
		mod_समयr(&padapter->securitypriv.tkip_समयr,
			  jअगरfies + msecs_to_jअगरfies(50));
	पूर्ण
	r8712_setstakey_cmd(padapter, (अचिन्हित अक्षर *)psta, true);
पूर्ण

अटल अंतरभूत व्योम handle_group_key(काष्ठा ieee_param *param,
				    काष्ठा _adapter *padapter)
अणु
	जोड़ Keytype *gk = padapter->securitypriv.XGrpKey;
	जोड़ Keytype *gtk = padapter->securitypriv.XGrptxmickey;
	जोड़ Keytype *grk = padapter->securitypriv.XGrprxmickey;

	अगर (param->u.crypt.idx > 0 &&
	    param->u.crypt.idx < 3) अणु
		/* group key idx is 1 or 2 */
		स_नकल(gk[param->u.crypt.idx - 1].skey,
		       param->u.crypt.key,
		       (param->u.crypt.key_len > 16 ? 16 :
			param->u.crypt.key_len));
		स_नकल(gtk[param->u.crypt.idx - 1].skey,
		       &param->u.crypt.key[16], 8);
		स_नकल(grk[param->u.crypt.idx - 1].skey,
		       &param->u.crypt.key[24], 8);
		padapter->securitypriv.binstallGrpkey = true;
		r8712_set_key(padapter, &padapter->securitypriv,
			param->u.crypt.idx);
		अगर (padapter->registrypriv.घातer_mgnt > PS_MODE_ACTIVE) अणु
			अगर (padapter->registrypriv.घातer_mgnt !=
			    padapter->pwrctrlpriv.pwr_mode)
				mod_समयr(&padapter->mlmepriv.dhcp_समयr,
					  jअगरfies + msecs_to_jअगरfies(60000));
		पूर्ण
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack अक्षर *translate_scan_wpa(काष्ठा iw_request_info *info,
						   काष्ठा wlan_network *pnetwork,
						   काष्ठा iw_event *iwe,
						   अक्षर *start, अक्षर *stop)
अणु
	/* parsing WPA/WPA2 IE */
	u8 buf[MAX_WPA_IE_LEN];
	u8 wpa_ie[255], rsn_ie[255];
	u16 wpa_len = 0, rsn_len = 0;
	पूर्णांक n, i;

	r8712_get_sec_ie(pnetwork->network.IEs,
			 pnetwork->network.IELength, rsn_ie, &rsn_len,
			 wpa_ie, &wpa_len);
	अगर (wpa_len > 0) अणु
		स_रखो(buf, 0, MAX_WPA_IE_LEN);
		n = प्र_लिखो(buf, "wpa_ie=");
		क्रम (i = 0; i < wpa_len; i++) अणु
			n += scnम_लिखो(buf + n, MAX_WPA_IE_LEN - n,
						"%02x", wpa_ie[i]);
			अगर (n == MAX_WPA_IE_LEN - 1)
				अवरोध;
		पूर्ण
		स_रखो(iwe, 0, माप(*iwe));
		iwe->cmd = IWEVCUSTOM;
		iwe->u.data.length = (u16)म_माप(buf);
		start = iwe_stream_add_poपूर्णांक(info, start, stop,
			iwe, buf);
		स_रखो(iwe, 0, माप(*iwe));
		iwe->cmd = IWEVGENIE;
		iwe->u.data.length = (u16)wpa_len;
		start = iwe_stream_add_poपूर्णांक(info, start, stop,
			iwe, wpa_ie);
	पूर्ण
	अगर (rsn_len > 0) अणु
		स_रखो(buf, 0, MAX_WPA_IE_LEN);
		n = प्र_लिखो(buf, "rsn_ie=");
		क्रम (i = 0; i < rsn_len; i++) अणु
			n += scnम_लिखो(buf + n, MAX_WPA_IE_LEN - n,
						"%02x", rsn_ie[i]);
			अगर (n == MAX_WPA_IE_LEN - 1)
				अवरोध;
		पूर्ण
		स_रखो(iwe, 0, माप(*iwe));
		iwe->cmd = IWEVCUSTOM;
		iwe->u.data.length = म_माप(buf);
		start = iwe_stream_add_poपूर्णांक(info, start, stop,
			iwe, buf);
		स_रखो(iwe, 0, माप(*iwe));
		iwe->cmd = IWEVGENIE;
		iwe->u.data.length = rsn_len;
		start = iwe_stream_add_poपूर्णांक(info, start, stop, iwe,
			rsn_ie);
	पूर्ण

	वापस start;
पूर्ण

अटल noअंतरभूत_क्रम_stack अक्षर *translate_scan_wps(काष्ठा iw_request_info *info,
						   काष्ठा wlan_network *pnetwork,
						   काष्ठा iw_event *iwe,
						   अक्षर *start, अक्षर *stop)
अणु
	/* parsing WPS IE */
	u8 wps_ie[512];
	uपूर्णांक wps_ielen;

	अगर (r8712_get_wps_ie(pnetwork->network.IEs,
	    pnetwork->network.IELength,
	    wps_ie, &wps_ielen)) अणु
		अगर (wps_ielen > 2) अणु
			iwe->cmd = IWEVGENIE;
			iwe->u.data.length = (u16)wps_ielen;
			start = iwe_stream_add_poपूर्णांक(info, start, stop,
				iwe, wps_ie);
		पूर्ण
	पूर्ण

	वापस start;
पूर्ण

अटल अक्षर *translate_scan(काष्ठा _adapter *padapter,
			    काष्ठा iw_request_info *info,
			    काष्ठा wlan_network *pnetwork,
			    अक्षर *start, अक्षर *stop)
अणु
	काष्ठा iw_event iwe;
	अक्षर *current_val;
	s8 *p;
	u32 i = 0, ht_ielen = 0;
	u16	cap, ht_cap = false;
	u8 rssi;

	अगर ((pnetwork->network.Configuration.DSConfig < 1) ||
	    (pnetwork->network.Configuration.DSConfig > 14)) अणु
		अगर (pnetwork->network.Configuration.DSConfig < 1)
			pnetwork->network.Configuration.DSConfig = 1;
		अन्यथा
			pnetwork->network.Configuration.DSConfig = 14;
	पूर्ण
	/* AP MAC address */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	ether_addr_copy(iwe.u.ap_addr.sa_data, pnetwork->network.MacAddress);
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_ADDR_LEN);
	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.flags = 1;
	iwe.u.data.length = min_t(u32, pnetwork->network.Ssid.SsidLength, 32);
	start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe,
				     pnetwork->network.Ssid.Ssid);
	/* parsing HT_CAP_IE */
	p = r8712_get_ie(&pnetwork->network.IEs[12], WLAN_EID_HT_CAPABILITY,
			 &ht_ielen, pnetwork->network.IELength - 12);
	अगर (p && ht_ielen > 0)
		ht_cap = true;
	/* Add the protocol name */
	iwe.cmd = SIOCGIWNAME;
	अगर (r8712_is_cckratesonly_included(pnetwork->network.rates)) अणु
		अगर (ht_cap)
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11bn");
		अन्यथा
			snम_लिखो(iwe.u.name, IFNAMSIZ, "IEEE 802.11b");
	पूर्ण अन्यथा अगर (r8712_is_cckrates_included(pnetwork->network.rates)) अणु
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
	स_नकल((u8 *)&cap, r8712_get_capability_from_ie(pnetwork->network.IEs),
		2);
	le16_to_cpus(&cap);
	अगर (cap & (WLAN_CAPABILITY_IBSS | WLAN_CAPABILITY_ESS)) अणु
		अगर (cap & WLAN_CAPABILITY_ESS)
			iwe.u.mode = (u32)IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = (u32)IW_MODE_ADHOC;
		start = iwe_stream_add_event(info, start, stop, &iwe,
			IW_EV_UINT_LEN);
	पूर्ण
	/* Add frequency/channel */
	iwe.cmd = SIOCGIWFREQ;
	अणु
		/*  check legal index */
		u8 dsconfig = pnetwork->network.Configuration.DSConfig;

		अगर (dsconfig >= 1 && dsconfig <= माप(
		    ieee80211_wlan_frequencies) / माप(दीर्घ))
			iwe.u.freq.m =
				(s32)(ieee80211_wlan_frequencies
				      [dsconfig - 1] * 100000);
		अन्यथा
			iwe.u.freq.m = 0;
	पूर्ण
	iwe.u.freq.e = (s16)1;
	iwe.u.freq.i = (u8)pnetwork->network.Configuration.DSConfig;
	start = iwe_stream_add_event(info, start, stop, &iwe,
		IW_EV_FREQ_LEN);
	/* Add encryption capability */
	iwe.cmd = SIOCGIWENCODE;
	अगर (cap & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = (u16)(IW_ENCODE_ENABLED |
				    IW_ENCODE_NOKEY);
	अन्यथा
		iwe.u.data.flags = (u16)(IW_ENCODE_DISABLED);
	iwe.u.data.length = (u16)0;
	start = iwe_stream_add_poपूर्णांक(info, start, stop, &iwe,
		pnetwork->network.Ssid.Ssid);
	/*Add basic and extended rates */
	current_val = start + iwe_stream_lcp_len(info);
	iwe.cmd = SIOCGIWRATE;
	iwe.u.bitrate.fixed = 0;
	iwe.u.bitrate.disabled = 0;
	iwe.u.bitrate.value = 0;
	i = 0;
	जबतक (pnetwork->network.rates[i] != 0) अणु
		/* Bit rate given in 500 kb/s units */
		iwe.u.bitrate.value = (pnetwork->network.rates[i++] &
				      0x7F) * 500000;
		current_val = iwe_stream_add_value(info, start, current_val,
			      stop, &iwe, IW_EV_PARAM_LEN);
	पूर्ण
	/* Check अगर we added any event */
	अगर ((current_val - start) > iwe_stream_lcp_len(info))
		start = current_val;

	start = translate_scan_wpa(info, pnetwork, &iwe, start, stop);

	start = translate_scan_wps(info, pnetwork, &iwe, start, stop);

	/* Add quality statistics */
	iwe.cmd = IWEVQUAL;
	rssi = r8712_संकेत_scale_mapping(pnetwork->network.Rssi);
	/* we only update संकेत_level (संकेत strength) that is rssi. */
	iwe.u.qual.updated = (u8)(IW_QUAL_QUAL_INVALID | IW_QUAL_LEVEL_UPDATED |
				  IW_QUAL_NOISE_INVALID);
	iwe.u.qual.level = rssi;  /* संकेत strength */
	iwe.u.qual.qual = 0; /* संकेत quality */
	iwe.u.qual.noise = 0; /* noise level */
	start = iwe_stream_add_event(info, start, stop, &iwe, IW_EV_QUAL_LEN);
	/* how to translate rssi to ?% */
	वापस start;
पूर्ण

अटल पूर्णांक wpa_set_auth_algs(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर ((value & AUTH_ALG_SHARED_KEY) && (value & AUTH_ALG_OPEN_SYSTEM)) अणु
		padapter->securitypriv.ndisencryptstatus =
						 Ndis802_11Encryption1Enabled;
		padapter->securitypriv.ndisauthtype =
						 Ndis802_11AuthModeAutoSwitch;
		padapter->securitypriv.AuthAlgrthm = 3;
	पूर्ण अन्यथा अगर (value & AUTH_ALG_SHARED_KEY) अणु
		padapter->securitypriv.ndisencryptstatus =
						 Ndis802_11Encryption1Enabled;
		padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeShared;
		padapter->securitypriv.AuthAlgrthm = 1;
	पूर्ण अन्यथा अगर (value & AUTH_ALG_OPEN_SYSTEM) अणु
		अगर (padapter->securitypriv.ndisauthtype <
						 Ndis802_11AuthModeWPAPSK) अणु
			padapter->securitypriv.ndisauthtype =
						 Ndis802_11AuthModeOpen;
			padapter->securitypriv.AuthAlgrthm = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक wpa_set_encryption(काष्ठा net_device *dev, काष्ठा ieee_param *param,
			      u32 param_len)
अणु
	पूर्णांक ret = 0;
	u32 wep_key_idx, wep_key_len = 0;
	काष्ठा NDIS_802_11_WEP	 *pwep = शून्य;
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';
	अगर (param_len != (u32)((u8 *) param->u.crypt.key - (u8 *)param) +
			 param->u.crypt.key_len)
		वापस -EINVAL;
	अगर (!is_broadcast_ether_addr(param->sta_addr))
		वापस -EINVAL;

	अगर (param->u.crypt.idx >= WEP_KEYS) अणु
		/* क्रम large key indices, set the शेष (0) */
		param->u.crypt.idx = 0;
	पूर्ण
	अगर (म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
		netdev_info(dev, "r8712u: %s: crypt.alg = WEP\n", __func__);
		padapter->securitypriv.ndisencryptstatus =
			     Ndis802_11Encryption1Enabled;
		padapter->securitypriv.PrivacyAlgrthm = _WEP40_;
		padapter->securitypriv.XGrpPrivacy = _WEP40_;
		wep_key_idx = param->u.crypt.idx;
		wep_key_len = param->u.crypt.key_len;
		अगर (wep_key_idx >= WEP_KEYS)
			wep_key_idx = 0;
		अगर (wep_key_len <= 0)
			वापस -EINVAL;

		wep_key_len = wep_key_len <= 5 ? 5 : 13;
		pwep = kzalloc(माप(*pwep), GFP_ATOMIC);
		अगर (!pwep)
			वापस -ENOMEM;
		pwep->KeyLength = wep_key_len;
		pwep->Length = wep_key_len +
			दुरत्व(काष्ठा NDIS_802_11_WEP, KeyMaterial);
		अगर (wep_key_len == 13) अणु
			padapter->securitypriv.PrivacyAlgrthm = _WEP104_;
			padapter->securitypriv.XGrpPrivacy = _WEP104_;
		पूर्ण
		pwep->KeyIndex = wep_key_idx;
		pwep->KeyIndex |= 0x80000000;
		स_नकल(pwep->KeyMaterial, param->u.crypt.key, pwep->KeyLength);
		अगर (param->u.crypt.set_tx) अणु
			अगर (r8712_set_802_11_add_wep(padapter, pwep))
				ret = -EOPNOTSUPP;
		पूर्ण अन्यथा अणु
			/* करोn't update "psecuritypriv->PrivacyAlgrthm" and
			 * "psecuritypriv->PrivacyKeyIndex=keyid", but can
			 * r8712_set_key to fw/cam
			 */
			अगर (wep_key_idx >= WEP_KEYS) अणु
				ret = -EOPNOTSUPP;
				जाओ निकास;
			पूर्ण
			स_नकल(&psecuritypriv->DefKey[wep_key_idx].skey[0],
			       pwep->KeyMaterial,
			       pwep->KeyLength);
			psecuritypriv->DefKeylen[wep_key_idx] =
				pwep->KeyLength;
			r8712_set_key(padapter, psecuritypriv, wep_key_idx);
		पूर्ण
		जाओ निकास;
	पूर्ण
	अगर (padapter->securitypriv.AuthAlgrthm == 2) अणु /* 802_1x */
		काष्ठा sta_info *psta, *pbcmc_sta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;
		काष्ठा security_priv *spriv = &padapter->securitypriv;

		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE |
		    WIFI_MP_STATE)) अणु /* sta mode */
			psta = r8712_get_stainfo(pstapriv,
						 get_bssid(pmlmepriv));
			अगर (psta) अणु
				psta->ieee8021x_blocked = false;
				अगर (spriv->ndisencryptstatus ==
				    Ndis802_11Encryption2Enabled ||
				    spriv->ndisencryptstatus ==
				    Ndis802_11Encryption3Enabled)
					psta->XPrivacy = spriv->PrivacyAlgrthm;
				अगर (param->u.crypt.set_tx == 1)
					handle_pairwise_key(psta, param,
							    padapter);
				अन्यथा /* group key */
					handle_group_key(param, padapter);
			पूर्ण
			pbcmc_sta = r8712_get_bcmc_stainfo(padapter);
			अगर (pbcmc_sta) अणु
				pbcmc_sta->ieee8021x_blocked = false;
				अगर (spriv->ndisencryptstatus ==
				    Ndis802_11Encryption2Enabled ||
				    spriv->ndisencryptstatus ==
				    Ndis802_11Encryption3Enabled)
					pbcmc_sta->XPrivacy =
						spriv->PrivacyAlgrthm;
			पूर्ण
		पूर्ण
	पूर्ण
निकास:
	kमुक्त(pwep);
	वापस ret;
पूर्ण

अटल पूर्णांक r871x_set_wpa_ie(काष्ठा _adapter *padapter, अक्षर *pie,
			    अचिन्हित लघु ielen)
अणु
	u8 *buf = शून्य;
	पूर्णांक group_cipher = 0, pairwise_cipher = 0;
	पूर्णांक ret = 0;

	अगर (ielen > MAX_WPA_IE_LEN || !pie)
		वापस -EINVAL;
	अगर (ielen) अणु
		buf = kmemdup(pie, ielen, GFP_ATOMIC);
		अगर (!buf)
			वापस -ENOMEM;
		अगर (ielen < RSN_HEADER_LEN) अणु
			ret  = -EINVAL;
			जाओ निकास;
		पूर्ण
		अगर (r8712_parse_wpa_ie(buf, ielen, &group_cipher,
		    &pairwise_cipher) == 0) अणु
			padapter->securitypriv.AuthAlgrthm = 2;
			padapter->securitypriv.ndisauthtype =
				  Ndis802_11AuthModeWPAPSK;
		पूर्ण
		अगर (r8712_parse_wpa2_ie(buf, ielen, &group_cipher,
		    &pairwise_cipher) == 0) अणु
			padapter->securitypriv.AuthAlgrthm = 2;
			padapter->securitypriv.ndisauthtype =
				  Ndis802_11AuthModeWPA2PSK;
		पूर्ण
		चयन (group_cipher) अणु
		हाल WPA_CIPHER_NONE:
			padapter->securitypriv.XGrpPrivacy =
				 _NO_PRIVACY_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11EncryptionDisabled;
			अवरोध;
		हाल WPA_CIPHER_WEP40:
			padapter->securitypriv.XGrpPrivacy = _WEP40_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
			अवरोध;
		हाल WPA_CIPHER_TKIP:
			padapter->securitypriv.XGrpPrivacy = _TKIP_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption2Enabled;
			अवरोध;
		हाल WPA_CIPHER_CCMP:
			padapter->securitypriv.XGrpPrivacy = _AES_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption3Enabled;
			अवरोध;
		हाल WPA_CIPHER_WEP104:
			padapter->securitypriv.XGrpPrivacy = _WEP104_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
			अवरोध;
		पूर्ण
		चयन (pairwise_cipher) अणु
		हाल WPA_CIPHER_NONE:
			padapter->securitypriv.PrivacyAlgrthm =
				 _NO_PRIVACY_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11EncryptionDisabled;
			अवरोध;
		हाल WPA_CIPHER_WEP40:
			padapter->securitypriv.PrivacyAlgrthm = _WEP40_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
			अवरोध;
		हाल WPA_CIPHER_TKIP:
			padapter->securitypriv.PrivacyAlgrthm = _TKIP_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption2Enabled;
			अवरोध;
		हाल WPA_CIPHER_CCMP:
			padapter->securitypriv.PrivacyAlgrthm = _AES_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption3Enabled;
			अवरोध;
		हाल WPA_CIPHER_WEP104:
			padapter->securitypriv.PrivacyAlgrthm = _WEP104_;
			padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
			अवरोध;
		पूर्ण
		padapter->securitypriv.wps_phase = false;
		अणु/* set wps_ie */
			u16 cnt = 0;
			u8 eid, wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;

			जबतक (cnt < ielen) अणु
				eid = buf[cnt];

				अगर ((eid == WLAN_EID_VENDOR_SPECIFIC) &&
				    (!स_भेद(&buf[cnt + 2], wps_oui, 4))) अणु
					netdev_info(padapter->pnetdev, "r8712u: SET WPS_IE\n");
					padapter->securitypriv.wps_ie_len =
					    ((buf[cnt + 1] + 2) <
					    (MAX_WPA_IE_LEN << 2)) ?
					    (buf[cnt + 1] + 2) :
					    (MAX_WPA_IE_LEN << 2);
					स_नकल(padapter->securitypriv.wps_ie,
					    &buf[cnt],
					    padapter->securitypriv.wps_ie_len);
					padapter->securitypriv.wps_phase =
								 true;
					netdev_info(padapter->pnetdev, "r8712u: SET WPS_IE, wps_phase==true\n");
					cnt += buf[cnt + 1] + 2;
					अवरोध;
				पूर्ण

				cnt += buf[cnt + 1] + 2;
			पूर्ण
		पूर्ण
	पूर्ण
निकास:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक r8711_wx_get_name(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	u32 ht_ielen = 0;
	अक्षर *p;
	u8 ht_cap = false;
	काष्ठा	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;
	u8 *prates;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE) ==
	    true) अणु
		/* parsing HT_CAP_IE */
		p = r8712_get_ie(&pcur_bss->IEs[12], WLAN_EID_HT_CAPABILITY,
				 &ht_ielen, pcur_bss->IELength - 12);
		अगर (p && ht_ielen > 0)
			ht_cap = true;
		prates = pcur_bss->rates;
		अगर (r8712_is_cckratesonly_included(prates)) अणु
			अगर (ht_cap)
				snम_लिखो(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11bn");
			अन्यथा
				snम_लिखो(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11b");
		पूर्ण अन्यथा अगर (r8712_is_cckrates_included(prates)) अणु
			अगर (ht_cap)
				snम_लिखो(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11bgn");
			अन्यथा
				snम_लिखो(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11bg");
		पूर्ण अन्यथा अणु
			अगर (ht_cap)
				snम_लिखो(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11gn");
			अन्यथा
				snम_लिखो(wrqu->name, IFNAMSIZ,
					 "IEEE 802.11g");
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(wrqu->name, IFNAMSIZ, "unassociated");
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर दीर्घ frequency_list[] = अणु
	2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462,
	2467, 2472, 2484, 4915, 4920, 4925, 4935, 4940, 4945, 4960, 4980,
	5035, 5040, 5045, 5055, 5060, 5080, 5170, 5180, 5190, 5200, 5210,
	5220, 5230, 5240, 5260, 5280, 5300, 5320, 5500, 5520, 5540, 5560,
	5580, 5600, 5620, 5640, 5660, 5680, 5700, 5745, 5765, 5785, 5805,
	5825
पूर्ण;

अटल पूर्णांक r8711_wx_set_freq(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_freq *fwrq = &wrqu->freq;
	पूर्णांक rc = 0;

/* If setting by frequency, convert to a channel */
	अगर ((fwrq->e == 1) &&
	  (fwrq->m >= (पूर्णांक) 2.412e8) &&
	  (fwrq->m <= (पूर्णांक) 2.487e8)) अणु
		पूर्णांक f = fwrq->m / 100000;
		पूर्णांक c = 0;

		जबतक ((c < 14) && (f != frequency_list[c]))
			c++;
		fwrq->e = 0;
		fwrq->m = c + 1;
	पूर्ण
	/* Setting by channel number */
	अगर ((fwrq->m > 14) || (fwrq->e > 0)) अणु
		rc = -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		पूर्णांक channel = fwrq->m;

		अगर ((channel < 1) || (channel > 14)) अणु
			rc = -EINVAL;
		पूर्ण अन्यथा अणु
			/* Yes ! We can set it !!! */
			padapter->registrypriv.channel = channel;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक r8711_wx_get_freq(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;

	अगर (!check_fwstate(pmlmepriv, _FW_LINKED))
		वापस -ENOLINK;

	wrqu->freq.m = ieee80211_wlan_frequencies[
		       pcur_bss->Configuration.DSConfig - 1] * 100000;
	wrqu->freq.e = 1;
	wrqu->freq.i = pcur_bss->Configuration.DSConfig;

	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_set_mode(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE networkType;

	चयन (wrqu->mode) अणु
	हाल IW_MODE_AUTO:
		networkType = Ndis802_11AutoUnknown;
		अवरोध;
	हाल IW_MODE_ADHOC:
		networkType = Ndis802_11IBSS;
		अवरोध;
	हाल IW_MODE_MASTER:
		networkType = Ndis802_11APMode;
		अवरोध;
	हाल IW_MODE_INFRA:
		networkType = Ndis802_11Infraकाष्ठाure;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (Ndis802_11APMode == networkType)
		r8712_setopmode_cmd(padapter, networkType);
	अन्यथा
		r8712_setopmode_cmd(padapter, Ndis802_11AutoUnknown);

	r8712_set_802_11_infraकाष्ठाure_mode(padapter, networkType);
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_mode(काष्ठा net_device *dev, काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
		wrqu->mode = IW_MODE_INFRA;
	अन्यथा अगर (check_fwstate(pmlmepriv,
		 WIFI_ADHOC_MASTER_STATE | WIFI_ADHOC_STATE))
		wrqu->mode = IW_MODE_ADHOC;
	अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		wrqu->mode = IW_MODE_MASTER;
	अन्यथा
		wrqu->mode = IW_MODE_AUTO;
	वापस 0;
पूर्ण

अटल पूर्णांक r871x_wx_set_pmkid(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *a,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा iw_pmksa *pPMK = (काष्ठा iw_pmksa *) extra;
	काष्ठा RT_PMKID_LIST *pl = psecuritypriv->PMKIDList;
	u8 strZeroMacAddress[ETH_ALEN] = अणु0x00पूर्ण;
	u8 strIssueBssid[ETH_ALEN] = अणु0x00पूर्ण;
	u8 j, blInserted = false;
	पूर्णांक पूर्णांकReturn = false;

/*
 *	There are the BSSID inक्रमmation in the bssid.sa_data array.
 *	If cmd is IW_PMKSA_FLUSH, it means the wpa_supplicant wants to clear
 *	all the PMKID inक्रमmation. If cmd is IW_PMKSA_ADD, it means the
 *	wpa_supplicant wants to add a PMKID/BSSID to driver.
 *	If cmd is IW_PMKSA_REMOVE, it means the wpa_supplicant wants to
 *	हटाओ a PMKID/BSSID from driver.
 */
	अगर (!pPMK)
		वापस -EINVAL;
	स_नकल(strIssueBssid, pPMK->bssid.sa_data, ETH_ALEN);
	चयन (pPMK->cmd) अणु
	हाल IW_PMKSA_ADD:
		अगर (!स_भेद(strIssueBssid, strZeroMacAddress, ETH_ALEN))
			वापस पूर्णांकReturn;
		पूर्णांकReturn = true;
		blInserted = false;
		/* overग_लिखो PMKID */
		क्रम (j = 0; j < NUM_PMKID_CACHE; j++) अणु
			अगर (!स_भेद(pl[j].Bssid, strIssueBssid, ETH_ALEN)) अणु
				/* BSSID is matched, the same AP => reग_लिखो
				 * with new PMKID.
				 */
				netdev_info(dev, "r8712u: %s: BSSID exists in the PMKList.\n",
					    __func__);
				स_नकल(pl[j].PMKID, pPMK->pmkid, IW_PMKID_LEN);
				pl[j].bUsed = true;
				psecuritypriv->PMKIDIndex = j + 1;
				blInserted = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!blInserted) अणु
			/* Find a new entry */
			netdev_info(dev, "r8712u: %s: Use the new entry index = %d for this PMKID.\n",
				    __func__, psecuritypriv->PMKIDIndex);
			स_नकल(pl[psecuritypriv->PMKIDIndex].Bssid,
			       strIssueBssid, ETH_ALEN);
			स_नकल(pl[psecuritypriv->PMKIDIndex].PMKID,
			       pPMK->pmkid, IW_PMKID_LEN);
			pl[psecuritypriv->PMKIDIndex].bUsed = true;
			psecuritypriv->PMKIDIndex++;
			अगर (psecuritypriv->PMKIDIndex == NUM_PMKID_CACHE)
				psecuritypriv->PMKIDIndex = 0;
		पूर्ण
		अवरोध;
	हाल IW_PMKSA_REMOVE:
		पूर्णांकReturn = true;
		क्रम (j = 0; j < NUM_PMKID_CACHE; j++) अणु
			अगर (!स_भेद(pl[j].Bssid, strIssueBssid, ETH_ALEN)) अणु
				/* BSSID is matched, the same AP => Remove
				 * this PMKID inक्रमmation and reset it.
				 */
				eth_zero_addr(pl[j].Bssid);
				pl[j].bUsed = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IW_PMKSA_FLUSH:
		स_रखो(psecuritypriv->PMKIDList, 0,
			माप(काष्ठा RT_PMKID_LIST) * NUM_PMKID_CACHE);
		psecuritypriv->PMKIDIndex = 0;
		पूर्णांकReturn = true;
		अवरोध;
	शेष:
		netdev_info(dev, "r8712u: %s: unknown Command\n", __func__);
		पूर्णांकReturn = false;
		अवरोध;
	पूर्ण
	वापस पूर्णांकReturn;
पूर्ण

अटल पूर्णांक r8711_wx_get_sens(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	wrqu->sens.value = 0;
	wrqu->sens.fixed = 0;	/* no स्वतः select */
	wrqu->sens.disabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_range(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *)extra;
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
	/* TODO: 8711 sensitivity ? */
	/* संकेत level threshold range */
	/* percent values between 0 and 100. */
	range->max_qual.qual = 100;
	range->max_qual.level = 100;
	range->max_qual.noise = 100;
	range->max_qual.updated = 7; /* Updated all three */
	range->avg_qual.qual = 92; /* > 8% missed beacons is 'bad' */
	/* TODO: Find real 'good' to 'bad' threshold value क्रम RSSI */
	range->avg_qual.level = 0x100 - 78;
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7; /* Updated all three */
	range->num_bitrates = RATE_COUNT;
	क्रम (i = 0; i < RATE_COUNT && i < IW_MAX_BITRATES; i++)
		range->bitrate[i] = rtl8180_rates[i];
	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;
	range->pm_capa = 0;
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 16;
	range->num_channels = 14;
	क्रम (i = 0, val = 0; i < 14; i++) अणु
		/* Include only legal frequencies क्रम some countries */
		range->freq[val].i = i + 1;
		range->freq[val].m = ieee80211_wlan_frequencies[i] * 100000;
		range->freq[val].e = 1;
		val++;
		अगर (val == IW_MAX_FREQUENCIES)
			अवरोध;
	पूर्ण
	range->num_frequency = val;
	range->enc_capa = IW_ENC_CAPA_WPA |
			  IW_ENC_CAPA_WPA2 |
			  IW_ENC_CAPA_CIPHER_TKIP |
			  IW_ENC_CAPA_CIPHER_CCMP;
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_rate(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra);

अटल पूर्णांक r871x_wx_set_priv(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *awrq,
				अक्षर *extra)
अणु
	पूर्णांक ret = 0, len = 0;
	अक्षर *ext;
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *dwrq = (काष्ठा iw_poपूर्णांक *)awrq;

	len = dwrq->length;
	ext = strndup_user(dwrq->poपूर्णांकer, len);
	अगर (IS_ERR(ext))
		वापस PTR_ERR(ext);

	अगर (!strहालcmp(ext, "RSSI")) अणु
		/*Return received संकेत strength indicator in -db क्रम */
		/* current AP */
		/*<ssid> Rssi xx */
		काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
		काष्ठा wlan_network *pcur_network = &pmlmepriv->cur_network;
		/*अटल u8 xxxx; */
		अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
			प्र_लिखो(ext, "%s rssi %d",
				pcur_network->network.Ssid.Ssid,
				/*(xxxx=xxxx+10) */
				((padapter->recvpriv.fw_rssi) >> 1) - 95
				/*pcur_network->network.Rssi */
				);
		पूर्ण अन्यथा अणु
			प्र_लिखो(ext, "OK");
		पूर्ण
	पूर्ण अन्यथा अगर (!strहालcmp(ext, "LINKSPEED")) अणु
		/*Return link speed in MBPS */
		/*LinkSpeed xx */
		जोड़ iwreq_data wrqd;
		पूर्णांक ret_inner;
		पूर्णांक mbps;

		ret_inner = r8711_wx_get_rate(dev, info, &wrqd, extra);
		अगर (ret_inner != 0)
			mbps = 0;
		अन्यथा
			mbps = wrqd.bitrate.value / 1000000;
		प्र_लिखो(ext, "LINKSPEED %d", mbps);
	पूर्ण अन्यथा अगर (!strहालcmp(ext, "MACADDR")) अणु
		/*Return mac address of the station */
		/* Macaddr = xx:xx:xx:xx:xx:xx */
		प्र_लिखो(ext, "MACADDR = %pM", dev->dev_addr);
	पूर्ण अन्यथा अगर (!strहालcmp(ext, "SCAN-ACTIVE")) अणु
		/*Set scan type to active */
		/*OK अगर successful */
		काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

		pmlmepriv->passive_mode = 1;
		प्र_लिखो(ext, "OK");
	पूर्ण अन्यथा अगर (!strहालcmp(ext, "SCAN-PASSIVE")) अणु
		/*Set scan type to passive */
		/*OK अगर successful */
		काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

		pmlmepriv->passive_mode = 0;
		प्र_लिखो(ext, "OK");
	पूर्ण अन्यथा अगर (!म_भेदन(ext, "DCE-E", 5)) अणु
		/*Set scan type to passive */
		/*OK अगर successful */
		r8712_disconnectCtrlEx_cmd(padapter
			, 1 /*u32 enableDrvCtrl */
			, 5 /*u32 tryPktCnt */
			, 100 /*u32 tryPktInterval */
			, 5000 /*u32 firstStageTO */
		);
		प्र_लिखो(ext, "OK");
	पूर्ण अन्यथा अगर (!म_भेदन(ext, "DCE-D", 5)) अणु
		/*Set scan type to passive */
		/*OK अगर successfu */
		r8712_disconnectCtrlEx_cmd(padapter
			, 0 /*u32 enableDrvCtrl */
			, 5 /*u32 tryPktCnt */
			, 100 /*u32 tryPktInterval */
			, 5000 /*u32 firstStageTO */
		);
		प्र_लिखो(ext, "OK");
	पूर्ण अन्यथा अणु
		netdev_info(dev, "r8712u: %s: unknown Command %s.\n",
			    __func__, ext);
		जाओ FREE_EXT;
	पूर्ण
	अगर (copy_to_user(dwrq->poपूर्णांकer, ext,
				min(dwrq->length, (__u16)(म_माप(ext) + 1))))
		ret = -EFAULT;

FREE_EXT:
	kमुक्त(ext);
	वापस ret;
पूर्ण

/* set bssid flow
 * s1. set_802_11_infraकाष्ठाure_mode()
 * s2. set_802_11_authentication_mode()
 * s3. set_802_11_encryption_mode()
 * s4. set_802_11_bssid()
 *
 * This function पूर्णांकends to handle the Set AP command, which specअगरies the
 * MAC# of a preferred Access Poपूर्णांक.
 * Currently, the request comes via Wireless Extensions' SIOCSIWAP ioctl.
 *
 * For this operation to succeed, there is no need क्रम the पूर्णांकerface to be up.
 *
 */
अटल पूर्णांक r8711_wx_set_wap(काष्ठा net_device *dev,
			 काष्ठा iw_request_info *info,
			 जोड़ iwreq_data *awrq,
			 अक्षर *extra)
अणु
	पूर्णांक ret = -EINPROGRESS;
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा  __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा sockaddr *temp = (काष्ठा sockaddr *)awrq;
	अचिन्हित दीर्घ irqL;
	काष्ठा list_head *phead;
	u8 *dst_bssid;
	काष्ठा wlan_network *pnetwork = शून्य;
	क्रमागत NDIS_802_11_AUTHENTICATION_MODE	authmode;

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		वापस -EBUSY;
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
		वापस ret;
	अगर (temp->sa_family != ARPHRD_ETHER)
		वापस -EINVAL;
	authmode = padapter->securitypriv.ndisauthtype;
	spin_lock_irqsave(&queue->lock, irqL);
	phead = &queue->queue;
	pmlmepriv->pscanned = phead->next;
	जबतक (1) अणु
		अगर (end_of_queue_search(phead, pmlmepriv->pscanned))
			अवरोध;
		pnetwork = container_of(pmlmepriv->pscanned,
					काष्ठा wlan_network, list);
		pmlmepriv->pscanned = pmlmepriv->pscanned->next;
		dst_bssid = pnetwork->network.MacAddress;
		अगर (!स_भेद(dst_bssid, temp->sa_data, ETH_ALEN)) अणु
			r8712_set_802_11_infraकाष्ठाure_mode(padapter,
			    pnetwork->network.Infraकाष्ठाureMode);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&queue->lock, irqL);
	अगर (!ret) अणु
		अगर (!r8712_set_802_11_authentication_mode(padapter, authmode)) अणु
			ret = -ENOMEM;
		पूर्ण अन्यथा अणु
			अगर (!r8712_set_802_11_bssid(padapter, temp->sa_data))
				ret = -1;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक r8711_wx_get_wap(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;

	wrqu->ap_addr.sa_family = ARPHRD_ETHER;
	अगर (check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE |
				     WIFI_AP_STATE))
		ether_addr_copy(wrqu->ap_addr.sa_data, pcur_bss->MacAddress);
	अन्यथा
		eth_zero_addr(wrqu->ap_addr.sa_data);
	वापस 0;
पूर्ण

अटल पूर्णांक r871x_wx_set_mlme(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *) extra;

	अगर (!mlme)
		वापस -1;
	चयन (mlme->cmd) अणु
	हाल IW_MLME_DEAUTH:
		अगर (!r8712_set_802_11_disassociate(padapter))
			ret = -1;
		अवरोध;
	हाल IW_MLME_DISASSOC:
		अगर (!r8712_set_802_11_disassociate(padapter))
			ret = -1;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

/*
 *
 * This function पूर्णांकends to handle the Set Scan command.
 * Currently, the request comes via Wireless Extensions' SIOCSIWSCAN ioctl.
 *
 * For this operation to succeed, the पूर्णांकerface is brought Up beक्रमehand.
 *
 */
अटल पूर्णांक r8711_wx_set_scan(काष्ठा net_device *dev,
			काष्ठा iw_request_info *a,
			जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 status = true;

	अगर (padapter->driver_stopped) अणु
		netdev_info(dev, "In %s: driver_stopped=%d\n",
			    __func__, padapter->driver_stopped);
		वापस -1;
	पूर्ण
	अगर (!padapter->bup)
		वापस -ENETDOWN;
	अगर (!padapter->hw_init_completed)
		वापस -1;
	अगर ((check_fwstate(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING)) ||
	    (pmlmepriv->sitesurveyctrl.traffic_busy))
		वापस 0;
	अगर (wrqu->data.length == माप(काष्ठा iw_scan_req)) अणु
		काष्ठा iw_scan_req *req = (काष्ठा iw_scan_req *)extra;

		अगर (wrqu->data.flags & IW_SCAN_THIS_ESSID) अणु
			काष्ठा ndis_802_11_ssid ssid;
			अचिन्हित दीर्घ irqL;
			u32 len = min_t(u8, req->essid_len, IW_ESSID_MAX_SIZE);

			स_रखो((अचिन्हित अक्षर *)&ssid, 0,
				 माप(काष्ठा ndis_802_11_ssid));
			स_नकल(ssid.Ssid, req->essid, len);
			ssid.SsidLength = len;
			spin_lock_irqsave(&pmlmepriv->lock, irqL);
			अगर ((check_fwstate(pmlmepriv, _FW_UNDER_SURVEY |
			     _FW_UNDER_LINKING)) ||
			    (pmlmepriv->sitesurveyctrl.traffic_busy)) अणु
				अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
					status = false;
			पूर्ण अन्यथा अणु
				status = r8712_sitesurvey_cmd(padapter, &ssid);
			पूर्ण
			spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
		पूर्ण
	पूर्ण अन्यथा अणु
		status = r8712_set_802_11_bssid_list_scan(padapter);
	पूर्ण
	अगर (!status)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_scan(काष्ठा net_device *dev,
				काष्ठा iw_request_info *a,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा  __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा wlan_network *pnetwork = शून्य;
	अचिन्हित दीर्घ irqL;
	काष्ठा list_head *plist, *phead;
	अक्षर *ev = extra;
	अक्षर *stop = ev + wrqu->data.length;
	u32 ret = 0, cnt = 0;

	अगर (padapter->driver_stopped)
		वापस -EINVAL;
	जबतक (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY |
			     _FW_UNDER_LINKING)) अणु
		msleep(30);
		cnt++;
		अगर (cnt > 100)
			अवरोध;
	पूर्ण
	spin_lock_irqsave(&queue->lock, irqL);
	phead = &queue->queue;
	plist = phead->next;
	जबतक (1) अणु
		अगर (end_of_queue_search(phead, plist))
			अवरोध;
		अगर ((stop - ev) < SCAN_ITEM_SIZE) अणु
			ret = -E2BIG;
			अवरोध;
		पूर्ण
		pnetwork = container_of(plist, काष्ठा wlan_network, list);
		ev = translate_scan(padapter, a, pnetwork, ev, stop);
		plist = plist->next;
	पूर्ण
	spin_unlock_irqrestore(&queue->lock, irqL);
	wrqu->data.length = ev - extra;
	wrqu->data.flags = 0;
	वापस ret;
पूर्ण

/* set ssid flow
 * s1. set_802_11_infraकाष्ठाure_mode()
 * s2. set_802_11_authenticaion_mode()
 * s3. set_802_11_encryption_mode()
 * s4. set_802_11_ssid()
 *
 * This function पूर्णांकends to handle the Set ESSID command.
 * Currently, the request comes via the Wireless Extensions' SIOCSIWESSID ioctl.
 *
 * For this operation to succeed, there is no need क्रम the पूर्णांकerface to be Up.
 *
 */
अटल पूर्णांक r8711_wx_set_essid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *a,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा  __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा wlan_network *pnetwork = शून्य;
	क्रमागत NDIS_802_11_AUTHENTICATION_MODE	authmode;
	काष्ठा ndis_802_11_ssid ndis_ssid;
	u8 *dst_ssid, *src_ssid;
	काष्ठा list_head *phead;
	u32 len;

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		वापस -EBUSY;
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
		वापस 0;
	अगर (wrqu->essid.length > IW_ESSID_MAX_SIZE)
		वापस -E2BIG;
	authmode = padapter->securitypriv.ndisauthtype;
	अगर (wrqu->essid.flags && wrqu->essid.length) अणु
		len = (wrqu->essid.length < IW_ESSID_MAX_SIZE) ?
		       wrqu->essid.length : IW_ESSID_MAX_SIZE;
		स_रखो(&ndis_ssid, 0, माप(काष्ठा ndis_802_11_ssid));
		ndis_ssid.SsidLength = len;
		स_नकल(ndis_ssid.Ssid, extra, len);
		src_ssid = ndis_ssid.Ssid;
		phead = &queue->queue;
		pmlmepriv->pscanned = phead->next;
		जबतक (1) अणु
			अगर (end_of_queue_search(phead, pmlmepriv->pscanned))
				अवरोध;
			pnetwork = container_of(pmlmepriv->pscanned,
						काष्ठा wlan_network, list);
			pmlmepriv->pscanned = pmlmepriv->pscanned->next;
			dst_ssid = pnetwork->network.Ssid.Ssid;
			अगर ((!स_भेद(dst_ssid, src_ssid, ndis_ssid.SsidLength))
			    && (pnetwork->network.Ssid.SsidLength ==
			     ndis_ssid.SsidLength)) अणु
				अगर (check_fwstate(pmlmepriv,
							WIFI_ADHOC_STATE)) अणु
					अगर (pnetwork->network.
						Infraकाष्ठाureMode
						!=
						padapter->mlmepriv.
						cur_network.network.
						Infraकाष्ठाureMode)
						जारी;
				पूर्ण

				r8712_set_802_11_infraकाष्ठाure_mode(
				     padapter,
				     pnetwork->network.Infraकाष्ठाureMode);
				अवरोध;
			पूर्ण
		पूर्ण
		r8712_set_802_11_authentication_mode(padapter, authmode);
		r8712_set_802_11_ssid(padapter, &ndis_ssid);
	पूर्ण
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक r8711_wx_get_essid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *a,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;
	u32 len, ret = 0;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE)) अणु
		len = pcur_bss->Ssid.SsidLength;
		wrqu->essid.length = len;
		स_नकल(extra, pcur_bss->Ssid.Ssid, len);
		wrqu->essid.flags = 1;
	पूर्ण अन्यथा अणु
		ret = -ENOLINK;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक r8711_wx_set_rate(काष्ठा net_device *dev,
				काष्ठा iw_request_info *a,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	u32 target_rate = wrqu->bitrate.value;
	u32 fixed = wrqu->bitrate.fixed;
	u32 ratevalue = 0;
	u8 datarates[NumRates];
	u8 mpdatarate[NumRates] = अणु11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0xffपूर्ण;
	पूर्णांक i;

	अगर (target_rate == -1) अणु
		ratevalue = 11;
		जाओ set_rate;
	पूर्ण
	target_rate = target_rate / 100000;
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
	वापस r8712_setdatarate_cmd(padapter, datarates);
पूर्ण

अटल पूर्णांक r8711_wx_get_rate(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;
	काष्ठा ieee80211_ht_cap *pht_capie;
	अचिन्हित अक्षर rf_type = padapter->registrypriv.rf_config;
	पूर्णांक i;
	u8 *p;
	u16 rate, max_rate = 0, ht_cap = false;
	u32 ht_ielen = 0;
	u8 bw_40MHz = 0, लघु_GI = 0;
	u16 mcs_rate = 0;

	i = 0;
	अगर (!check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE))
		वापस -ENOLINK;
	p = r8712_get_ie(&pcur_bss->IEs[12], WLAN_EID_HT_CAPABILITY, &ht_ielen,
			 pcur_bss->IELength - 12);
	अगर (p && ht_ielen > 0) अणु
		ht_cap = true;
		pht_capie = (काष्ठा ieee80211_ht_cap *)(p + 2);
		स_नकल(&mcs_rate, &pht_capie->mcs, 2);
		bw_40MHz = (le16_to_cpu(pht_capie->cap_info) &
			    IEEE80211_HT_CAP_SUP_WIDTH_20_40) ? 1 : 0;
		लघु_GI = (le16_to_cpu(pht_capie->cap_info) &
			    (IEEE80211_HT_CAP_SGI_20 |
			    IEEE80211_HT_CAP_SGI_40)) ? 1 : 0;
	पूर्ण
	जबतक ((pcur_bss->rates[i] != 0) &&
	       (pcur_bss->rates[i] != 0xFF)) अणु
		rate = pcur_bss->rates[i] & 0x7F;
		अगर (rate > max_rate)
			max_rate = rate;
		wrqu->bitrate.fixed = 0;	/* no स्वतः select */
		wrqu->bitrate.value = rate * 500000;
		i++;
	पूर्ण
	अगर (ht_cap) अणु
		अगर (mcs_rate & 0x8000 /* MCS15 */
		    &&
		    rf_type == RTL8712_RF_2T2R)
			max_rate = (bw_40MHz) ? ((लघु_GI) ? 300 : 270) :
			((लघु_GI) ? 144 : 130);
		अन्यथा /* शेष MCS7 */
			max_rate = (bw_40MHz) ? ((लघु_GI) ? 150 : 135) :
			((लघु_GI) ? 72 : 65);
		max_rate *= 2; /* Mbps/2 */
	पूर्ण
	wrqu->bitrate.value = max_rate * 500000;
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_rts(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);

	wrqu->rts.value = padapter->registrypriv.rts_thresh;
	wrqu->rts.fixed = 0;	/* no स्वतः select */
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_set_frag(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);

	अगर (wrqu->frag.disabled) अणु
		padapter->xmitpriv.frag_len = MAX_FRAG_THRESHOLD;
	पूर्ण अन्यथा अणु
		अगर (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD)
			वापस -EINVAL;
		padapter->xmitpriv.frag_len = wrqu->frag.value & ~0x1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_frag(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);

	wrqu->frag.value = padapter->xmitpriv.frag_len;
	wrqu->frag.fixed = 0;	/* no स्वतः select */
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_retry(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	wrqu->retry.value = 7;
	wrqu->retry.fixed = 0;	/* no स्वतः select */
	wrqu->retry.disabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_set_enc(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	u32 key;
	u32 keyindex_provided;
	काष्ठा NDIS_802_11_WEP	 wep;
	क्रमागत NDIS_802_11_AUTHENTICATION_MODE authmode;
	काष्ठा iw_poपूर्णांक *erq = &(wrqu->encoding);
	काष्ठा _adapter *padapter = netdev_priv(dev);

	key = erq->flags & IW_ENCODE_INDEX;
	स_रखो(&wep, 0, माप(काष्ठा NDIS_802_11_WEP));
	अगर (erq->flags & IW_ENCODE_DISABLED) अणु
		netdev_info(dev, "r8712u: %s: EncryptionDisabled\n", __func__);
		padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11EncryptionDisabled;
		padapter->securitypriv.PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.XGrpPrivacy = _NO_PRIVACY_;
		padapter->securitypriv.AuthAlgrthm = 0; /* खोलो प्रणाली */
		authmode = Ndis802_11AuthModeOpen;
		padapter->securitypriv.ndisauthtype = authmode;
		वापस 0;
	पूर्ण
	अगर (key) अणु
		अगर (key > WEP_KEYS)
			वापस -EINVAL;
		key--;
		keyindex_provided = 1;
	पूर्ण अन्यथा अणु
		keyindex_provided = 0;
		key = padapter->securitypriv.PrivacyKeyIndex;
	पूर्ण
	/* set authentication mode */
	अगर (erq->flags & IW_ENCODE_OPEN) अणु
		netdev_info(dev, "r8712u: %s: IW_ENCODE_OPEN\n", __func__);
		padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
		padapter->securitypriv.AuthAlgrthm = 0; /* खोलो प्रणाली */
		padapter->securitypriv.PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.XGrpPrivacy = _NO_PRIVACY_;
		authmode = Ndis802_11AuthModeOpen;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण अन्यथा अगर (erq->flags & IW_ENCODE_RESTRICTED) अणु
		netdev_info(dev,
				"r8712u: %s: IW_ENCODE_RESTRICTED\n", __func__);
		padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
		padapter->securitypriv.AuthAlgrthm = 1; /* shared प्रणाली */
		padapter->securitypriv.PrivacyAlgrthm = _WEP40_;
		padapter->securitypriv.XGrpPrivacy = _WEP40_;
		authmode = Ndis802_11AuthModeShared;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण अन्यथा अणु
		padapter->securitypriv.ndisencryptstatus =
				 Ndis802_11Encryption1Enabled;
		padapter->securitypriv.AuthAlgrthm = 0; /* खोलो प्रणाली */
		padapter->securitypriv.PrivacyAlgrthm = _NO_PRIVACY_;
		padapter->securitypriv.XGrpPrivacy = _NO_PRIVACY_;
		authmode = Ndis802_11AuthModeOpen;
		padapter->securitypriv.ndisauthtype = authmode;
	पूर्ण
	wep.KeyIndex = key;
	अगर (erq->length > 0) अणु
		wep.KeyLength = erq->length <= 5 ? 5 : 13;
		wep.Length = wep.KeyLength +
			     दुरत्व(काष्ठा NDIS_802_11_WEP, KeyMaterial);
	पूर्ण अन्यथा अणु
		wep.KeyLength = 0;
		अगर (keyindex_provided == 1) अणु /* set key_id only, no given
					       * KeyMaterial(erq->length==0).
					       */
			padapter->securitypriv.PrivacyKeyIndex = key;
			चयन (padapter->securitypriv.DefKeylen[key]) अणु
			हाल 5:
				padapter->securitypriv.PrivacyAlgrthm =
						 _WEP40_;
				अवरोध;
			हाल 13:
				padapter->securitypriv.PrivacyAlgrthm =
						 _WEP104_;
				अवरोध;
			शेष:
				padapter->securitypriv.PrivacyAlgrthm =
						 _NO_PRIVACY_;
				अवरोध;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण
	wep.KeyIndex |= 0x80000000;	/* transmit key */
	स_नकल(wep.KeyMaterial, keybuf, wep.KeyLength);
	अगर (r8712_set_802_11_add_wep(padapter, &wep))
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_enc(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	uपूर्णांक key;
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *erq = &(wrqu->encoding);
	काष्ठा	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	जोड़ Keytype *dk = padapter->securitypriv.DefKey;

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
		key = padapter->securitypriv.PrivacyKeyIndex;
	पूर्ण
	erq->flags = key + 1;
	चयन (padapter->securitypriv.ndisencryptstatus) अणु
	हाल Ndis802_11EncryptionNotSupported:
	हाल Ndis802_11EncryptionDisabled:
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		अवरोध;
	हाल Ndis802_11Encryption1Enabled:
		erq->length = padapter->securitypriv.DefKeylen[key];
		अगर (erq->length) अणु
			स_नकल(keybuf, dk[key].skey,
			       padapter->securitypriv.DefKeylen[key]);
			erq->flags |= IW_ENCODE_ENABLED;
			अगर (padapter->securitypriv.ndisauthtype ==
			    Ndis802_11AuthModeOpen)
				erq->flags |= IW_ENCODE_OPEN;
			अन्यथा अगर (padapter->securitypriv.ndisauthtype ==
				 Ndis802_11AuthModeShared)
				erq->flags |= IW_ENCODE_RESTRICTED;
		पूर्ण अन्यथा अणु
			erq->length = 0;
			erq->flags |= IW_ENCODE_DISABLED;
		पूर्ण
		अवरोध;
	हाल Ndis802_11Encryption2Enabled:
	हाल Ndis802_11Encryption3Enabled:
		erq->length = 16;
		erq->flags |= (IW_ENCODE_ENABLED | IW_ENCODE_OPEN |
			       IW_ENCODE_NOKEY);
		अवरोध;
	शेष:
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_get_घातer(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	wrqu->घातer.value = 0;
	wrqu->घातer.fixed = 0;	/* no स्वतः select */
	wrqu->घातer.disabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक r871x_wx_set_gen_ie(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);

	वापस r871x_set_wpa_ie(padapter, extra, wrqu->data.length);
पूर्ण

अटल पूर्णांक r871x_wx_set_auth(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_param *param = (काष्ठा iw_param *)&(wrqu->param);
	पूर्णांक paramid;
	पूर्णांक paramval;
	पूर्णांक ret = 0;

	paramid = param->flags & IW_AUTH_INDEX;
	paramval = param->value;
	चयन (paramid) अणु
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
		अगर (paramval) अणु
			/* wpa_supplicant is enabling tkip countermeasure. */
			padapter->securitypriv.btkip_countermeasure = true;
		पूर्ण अन्यथा अणु
			/* wpa_supplicant is disabling tkip countermeasure. */
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
		अगर (padapter->securitypriv.ndisencryptstatus ==
		    Ndis802_11Encryption1Enabled) अणु
			/* it means init value, or using wep,
			 * ndisencryptstatus =
			 *	Ndis802_11Encryption1Enabled,
			 * then it needn't reset it;
			 */
			अवरोध;
		पूर्ण

		अगर (paramval) अणु
			padapter->securitypriv.ndisencryptstatus =
				   Ndis802_11EncryptionDisabled;
			padapter->securitypriv.PrivacyAlgrthm =
				  _NO_PRIVACY_;
			padapter->securitypriv.XGrpPrivacy =
				  _NO_PRIVACY_;
			padapter->securitypriv.AuthAlgrthm = 0;
			padapter->securitypriv.ndisauthtype =
				  Ndis802_11AuthModeOpen;
		पूर्ण
		अवरोध;
	हाल IW_AUTH_80211_AUTH_ALG:
		ret = wpa_set_auth_algs(dev, (u32)paramval);
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

अटल पूर्णांक r871x_wx_set_enc_ext(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा iw_poपूर्णांक *pencoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *pext = (काष्ठा iw_encode_ext *)extra;
	काष्ठा ieee_param *param = शून्य;
	अक्षर *alg_name;
	u32 param_len;
	पूर्णांक ret = 0;

	चयन (pext->alg) अणु
	हाल IW_ENCODE_ALG_NONE:
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
		वापस -EINVAL;
	पूर्ण

	param_len = माप(काष्ठा ieee_param) + pext->key_len;
	param = kzalloc(param_len, GFP_ATOMIC);
	अगर (!param)
		वापस -ENOMEM;
	param->cmd = IEEE_CMD_SET_ENCRYPTION;
	eth_broadcast_addr(param->sta_addr);
	strscpy((अक्षर *)param->u.crypt.alg, alg_name, IEEE_CRYPT_ALG_NAME_LEN);
	अगर (pext->ext_flags & IW_ENCODE_EXT_GROUP_KEY)
		param->u.crypt.set_tx = 0;
	अगर (pext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY)
		param->u.crypt.set_tx = 1;
	param->u.crypt.idx = (pencoding->flags & 0x00FF) - 1;
	अगर (pext->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID)
		स_नकल(param->u.crypt.seq, pext->rx_seq, 8);
	अगर (pext->key_len) अणु
		param->u.crypt.key_len = pext->key_len;
		स_नकल(param + 1, pext + 1, pext->key_len);
	पूर्ण
	ret = wpa_set_encryption(dev, param, param_len);
	kमुक्त(param);
	वापस ret;
पूर्ण

अटल पूर्णांक r871x_wx_get_nick(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	अगर (extra) अणु
		wrqu->data.length = 8;
		wrqu->data.flags = 1;
		स_नकल(extra, "rtl_wifi", 8);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_पढ़ो32(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	u32 addr;
	u32 data32;

	get_user(addr, (u32 __user *)wrqu->data.poपूर्णांकer);
	data32 = r8712_पढ़ो32(padapter, addr);
	put_user(data32, (u32 __user *)wrqu->data.poपूर्णांकer);
	wrqu->data.length = (data32 & 0xffff0000) >> 16;
	wrqu->data.flags = data32 & 0xffff;
	get_user(addr, (u32 __user *)wrqu->data.poपूर्णांकer);
	वापस 0;
पूर्ण

अटल पूर्णांक r8711_wx_ग_लिखो32(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *wrqu, अक्षर *keybuf)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	u32 addr;
	u32 data32;

	get_user(addr, (u32 __user *)wrqu->data.poपूर्णांकer);
	data32 = ((u32)wrqu->data.length << 16) | (u32)wrqu->data.flags;
	r8712_ग_लिखो32(padapter, addr, data32);
	वापस 0;
पूर्ण

अटल पूर्णांक dummy(काष्ठा net_device *dev,
		काष्ठा iw_request_info *a,
		जोड़ iwreq_data *wrqu, अक्षर *b)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक r8711_drvext_hdl(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक r871x_mp_ioctl_hdl(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *p = &wrqu->data;
	काष्ठा oid_par_priv oid_par;
	काष्ठा mp_ioctl_handler *phandler;
	काष्ठा mp_ioctl_param *poidparam;
	अचिन्हित दीर्घ BytesRead, BytesWritten, BytesNeeded;
	u8 *pparmbuf, bset;
	u16 len;
	uपूर्णांक status;
	पूर्णांक ret = 0;

	अगर ((!p->length) || (!p->poपूर्णांकer))
		वापस -EINVAL;

	bset = (u8)(p->flags & 0xFFFF);
	len = p->length;
	pparmbuf = memdup_user(p->poपूर्णांकer, len);
	अगर (IS_ERR(pparmbuf))
		वापस PTR_ERR(pparmbuf);

	poidparam = (काष्ठा mp_ioctl_param *)pparmbuf;
	अगर (poidparam->subcode >= MAX_MP_IOCTL_SUBCODE) अणु
		ret = -EINVAL;
		जाओ _r871x_mp_ioctl_hdl_निकास;
	पूर्ण
	phandler = mp_ioctl_hdl + poidparam->subcode;
	अगर ((phandler->paramsize != 0) &&
	    (poidparam->len < phandler->paramsize)) अणु
		ret = -EINVAL;
		जाओ _r871x_mp_ioctl_hdl_निकास;
	पूर्ण
	अगर (phandler->oid == 0 && phandler->handler) अणु
		status = phandler->handler(&oid_par);
	पूर्ण अन्यथा अगर (phandler->handler) अणु
		oid_par.adapter_context = padapter;
		oid_par.oid = phandler->oid;
		oid_par.inक्रमmation_buf = poidparam->data;
		oid_par.inक्रमmation_buf_len = poidparam->len;
		oid_par.dbg = 0;
		BytesWritten = 0;
		BytesNeeded = 0;
		अगर (bset) अणु
			oid_par.bytes_rw = &BytesRead;
			oid_par.bytes_needed = &BytesNeeded;
			oid_par.type_of_oid = SET_OID;
		पूर्ण अन्यथा अणु
			oid_par.bytes_rw = &BytesWritten;
			oid_par.bytes_needed = &BytesNeeded;
			oid_par.type_of_oid = QUERY_OID;
		पूर्ण
		status = phandler->handler(&oid_par);
		/* toकरो:check status, BytesNeeded, etc. */
	पूर्ण अन्यथा अणु
		netdev_info(dev, "r8712u: %s: err!, subcode=%d, oid=%d, handler=%p\n",
			    __func__, poidparam->subcode, phandler->oid,
			    phandler->handler);
		ret = -EFAULT;
		जाओ _r871x_mp_ioctl_hdl_निकास;
	पूर्ण
	अगर (bset == 0x00) अणु /* query info */
		अगर (copy_to_user(p->poपूर्णांकer, pparmbuf, len))
			ret = -EFAULT;
	पूर्ण
	अगर (status) अणु
		ret = -EFAULT;
		जाओ _r871x_mp_ioctl_hdl_निकास;
	पूर्ण
_r871x_mp_ioctl_hdl_निकास:
	kमुक्त(pparmbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक r871x_get_ap_info(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा  __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा iw_poपूर्णांक *pdata = &wrqu->data;
	काष्ठा wlan_network *pnetwork = शून्य;
	u32 cnt = 0, wpa_ielen;
	अचिन्हित दीर्घ irqL;
	काष्ठा list_head *plist, *phead;
	अचिन्हित अक्षर *pbuf;
	u8 bssid[ETH_ALEN];
	अक्षर data[33];

	अगर (padapter->driver_stopped || !pdata)
		वापस -EINVAL;
	जबतक (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY |
			     _FW_UNDER_LINKING)) अणु
		msleep(30);
		cnt++;
		अगर (cnt > 100)
			अवरोध;
	पूर्ण
	pdata->flags = 0;
	अगर (pdata->length < 32)
		वापस -EINVAL;
	अगर (copy_from_user(data, pdata->poपूर्णांकer, 32))
		वापस -EINVAL;
	data[32] = 0;

	spin_lock_irqsave(&(pmlmepriv->scanned_queue.lock), irqL);
	phead = &queue->queue;
	plist = phead->next;
	जबतक (1) अणु
		अगर (end_of_queue_search(phead, plist))
			अवरोध;
		pnetwork = container_of(plist, काष्ठा wlan_network, list);
		अगर (!mac_pton(data, bssid)) अणु
			netdev_info(dev, "r8712u: Invalid BSSID '%s'.\n",
				    (u8 *)data);
			spin_unlock_irqrestore(&(pmlmepriv->scanned_queue.lock),
					       irqL);
			वापस -EINVAL;
		पूर्ण
		netdev_info(dev, "r8712u: BSSID:%pM\n", bssid);
		अगर (ether_addr_equal(bssid, pnetwork->network.MacAddress)) अणु
			/* BSSID match, then check अगर supporting wpa/wpa2 */
			pbuf = r8712_get_wpa_ie(&pnetwork->network.IEs[12],
			       &wpa_ielen, pnetwork->network.IELength - 12);
			अगर (pbuf && (wpa_ielen > 0)) अणु
				pdata->flags = 1;
				अवरोध;
			पूर्ण
			pbuf = r8712_get_wpa2_ie(&pnetwork->network.IEs[12],
			       &wpa_ielen, pnetwork->network.IELength - 12);
			अगर (pbuf && (wpa_ielen > 0)) अणु
				pdata->flags = 2;
				अवरोध;
			पूर्ण
		पूर्ण
		plist = plist->next;
	पूर्ण
	spin_unlock_irqrestore(&(pmlmepriv->scanned_queue.lock), irqL);
	अगर (pdata->length >= 34) अणु
		अगर (copy_to_user((u8 __user *)pdata->poपूर्णांकer + 32,
		    (u8 *)&pdata->flags, 1))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक r871x_set_pid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *pdata = &wrqu->data;

	अगर (padapter->driver_stopped || !pdata)
		वापस -EINVAL;
	अगर (copy_from_user(&padapter->pid, pdata->poपूर्णांकer, माप(पूर्णांक)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक r871x_set_chplan(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	पूर्णांक ret = 0;
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *pdata = &wrqu->data;
	पूर्णांक ch_plan = -1;

	अगर (padapter->driver_stopped || !pdata) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण
	ch_plan = (पूर्णांक)*extra;
	r8712_set_chplan_cmd(padapter, ch_plan);

निकास:

	वापस ret;
पूर्ण

अटल पूर्णांक r871x_wps_start(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_poपूर्णांक *pdata = &wrqu->data;
	u32   u32wps_start = 0;

	अगर (padapter->driver_stopped || !pdata)
		वापस -EINVAL;
	अगर (copy_from_user((व्योम *)&u32wps_start, pdata->poपूर्णांकer, 4))
		वापस -EFAULT;
	अगर (u32wps_start == 0)
		u32wps_start = *extra;
	अगर (u32wps_start == 1) /* WPS Start */
		padapter->ledpriv.LedControlHandler(padapter,
			   LED_CTL_START_WPS);
	अन्यथा अगर (u32wps_start == 2) /* WPS Stop because of wps success */
		padapter->ledpriv.LedControlHandler(padapter,
			   LED_CTL_STOP_WPS);
	अन्यथा अगर (u32wps_start == 3) /* WPS Stop because of wps fail */
		padapter->ledpriv.LedControlHandler(padapter,
			   LED_CTL_STOP_WPS_FAIL);
	वापस 0;
पूर्ण

अटल पूर्णांक wpa_set_param(काष्ठा net_device *dev, u8 name, u32 value)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);

	चयन (name) अणु
	हाल IEEE_PARAM_WPA_ENABLED:
		padapter->securitypriv.AuthAlgrthm = 2; /* 802.1x */
		चयन ((value) & 0xff) अणु
		हाल 1: /* WPA */
			padapter->securitypriv.ndisauthtype =
				Ndis802_11AuthModeWPAPSK; /* WPA_PSK */
			padapter->securitypriv.ndisencryptstatus =
				Ndis802_11Encryption2Enabled;
			अवरोध;
		हाल 2: /* WPA2 */
			padapter->securitypriv.ndisauthtype =
				Ndis802_11AuthModeWPA2PSK; /* WPA2_PSK */
			padapter->securitypriv.ndisencryptstatus =
				Ndis802_11Encryption3Enabled;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IEEE_PARAM_TKIP_COUNTERMEASURES:
		अवरोध;
	हाल IEEE_PARAM_DROP_UNENCRYPTED:
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
	हाल IEEE_PARAM_PRIVACY_INVOKED:
		अवरोध;
	हाल IEEE_PARAM_AUTH_ALGS:
		वापस wpa_set_auth_algs(dev, value);
	हाल IEEE_PARAM_IEEE_802_1X:
		अवरोध;
	हाल IEEE_PARAM_WPAX_SELECT:
		/* added क्रम WPA2 mixed mode */
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wpa_mlme(काष्ठा net_device *dev, u32 command, u32 reason)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);

	चयन (command) अणु
	हाल IEEE_MLME_STA_DEAUTH:
		अगर (!r8712_set_802_11_disassociate(padapter))
			वापस -1;
		अवरोध;
	हाल IEEE_MLME_STA_DISASSOC:
		अगर (!r8712_set_802_11_disassociate(padapter))
			वापस -1;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wpa_supplicant_ioctl(काष्ठा net_device *dev, काष्ठा iw_poपूर्णांक *p)
अणु
	काष्ठा ieee_param *param;
	पूर्णांक ret = 0;
	काष्ठा _adapter *padapter = netdev_priv(dev);

	अगर (p->length < माप(काष्ठा ieee_param) || !p->poपूर्णांकer)
		वापस -EINVAL;
	param = memdup_user(p->poपूर्णांकer, p->length);
	अगर (IS_ERR(param))
		वापस PTR_ERR(param);
	चयन (param->cmd) अणु
	हाल IEEE_CMD_SET_WPA_PARAM:
		ret = wpa_set_param(dev, param->u.wpa_param.name,
		      param->u.wpa_param.value);
		अवरोध;
	हाल IEEE_CMD_SET_WPA_IE:
		ret =  r871x_set_wpa_ie(padapter, (अक्षर *)param->u.wpa_ie.data,
		       (u16)param->u.wpa_ie.len);
		अवरोध;
	हाल IEEE_CMD_SET_ENCRYPTION:
		ret = wpa_set_encryption(dev, param, p->length);
		अवरोध;
	हाल IEEE_CMD_MLME:
		ret = wpa_mlme(dev, param->u.mlme.command,
		      param->u.mlme.reason_code);
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

/* based on "driver_ipw" and क्रम hostapd */
पूर्णांक r871x_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा iwreq *wrq = (काष्ठा iwreq *)rq;

	चयन (cmd) अणु
	हाल RTL_IOCTL_WPA_SUPPLICANT:
		वापस wpa_supplicant_ioctl(dev, &wrq->u.data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल iw_handler r8711_handlers[] = अणु
	शून्य,				/* SIOCSIWCOMMIT */
	r8711_wx_get_name,		/* SIOCGIWNAME */
	dummy,				/* SIOCSIWNWID */
	dummy,				/* SIOCGIWNWID */
	r8711_wx_set_freq,		/* SIOCSIWFREQ */
	r8711_wx_get_freq,		/* SIOCGIWFREQ */
	r8711_wx_set_mode,		/* SIOCSIWMODE */
	r8711_wx_get_mode,		/* SIOCGIWMODE */
	dummy,				/* SIOCSIWSENS */
	r8711_wx_get_sens,		/* SIOCGIWSENS */
	शून्य,				/* SIOCSIWRANGE */
	r8711_wx_get_range,		/* SIOCGIWRANGE */
	r871x_wx_set_priv,		/* SIOCSIWPRIV */
	शून्य,				/* SIOCGIWPRIV */
	शून्य,				/* SIOCSIWSTATS */
	शून्य,				/* SIOCGIWSTATS */
	dummy,				/* SIOCSIWSPY */
	dummy,				/* SIOCGIWSPY */
	शून्य,				/* SIOCGIWTHRSPY */
	शून्य,				/* SIOCWIWTHRSPY */
	r8711_wx_set_wap,		/* SIOCSIWAP */
	r8711_wx_get_wap,		/* SIOCGIWAP */
	r871x_wx_set_mlme,		/* request MLME operation;
					 *  uses काष्ठा iw_mlme
					 */
	dummy,				/* SIOCGIWAPLIST -- deprecated */
	r8711_wx_set_scan,		/* SIOCSIWSCAN */
	r8711_wx_get_scan,		/* SIOCGIWSCAN */
	r8711_wx_set_essid,		/* SIOCSIWESSID */
	r8711_wx_get_essid,		/* SIOCGIWESSID */
	dummy,				/* SIOCSIWNICKN */
	r871x_wx_get_nick,		/* SIOCGIWNICKN */
	शून्य,				/* -- hole -- */
	शून्य,				/* -- hole -- */
	r8711_wx_set_rate,		/* SIOCSIWRATE */
	r8711_wx_get_rate,		/* SIOCGIWRATE */
	dummy,				/* SIOCSIWRTS */
	r8711_wx_get_rts,		/* SIOCGIWRTS */
	r8711_wx_set_frag,		/* SIOCSIWFRAG */
	r8711_wx_get_frag,		/* SIOCGIWFRAG */
	dummy,				/* SIOCSIWTXPOW */
	dummy,				/* SIOCGIWTXPOW */
	dummy,				/* SIOCSIWRETRY */
	r8711_wx_get_retry,		/* SIOCGIWRETRY */
	r8711_wx_set_enc,		/* SIOCSIWENCODE */
	r8711_wx_get_enc,		/* SIOCGIWENCODE */
	dummy,				/* SIOCSIWPOWER */
	r8711_wx_get_घातer,		/* SIOCGIWPOWER */
	शून्य,				/*---hole---*/
	शून्य,				/*---hole---*/
	r871x_wx_set_gen_ie,		/* SIOCSIWGENIE */
	शून्य,				/* SIOCGIWGENIE */
	r871x_wx_set_auth,		/* SIOCSIWAUTH */
	शून्य,				/* SIOCGIWAUTH */
	r871x_wx_set_enc_ext,		/* SIOCSIWENCODEEXT */
	शून्य,				/* SIOCGIWENCODEEXT */
	r871x_wx_set_pmkid,		/* SIOCSIWPMKSA */
	शून्य,				/*---hole---*/
पूर्ण;

अटल स्थिर काष्ठा iw_priv_args r8711_निजी_args[] = अणु
	अणु
		SIOCIWFIRSTPRIV + 0x0,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "read32"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x1,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "write32"
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
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "setpid"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x6,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "wps_start"
	पूर्ण,
	अणु
		SIOCIWFIRSTPRIV + 0x7,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "chplan"
	पूर्ण
पूर्ण;

अटल iw_handler r8711_निजी_handler[] = अणु
	r8711_wx_पढ़ो32,
	r8711_wx_ग_लिखो32,
	r8711_drvext_hdl,
	r871x_mp_ioctl_hdl,
	r871x_get_ap_info, /*क्रम MM DTV platक्रमm*/
	r871x_set_pid,
	r871x_wps_start,
	r871x_set_chplan
पूर्ण;

अटल काष्ठा iw_statistics *r871x_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा _adapter *padapter = netdev_priv(dev);
	काष्ठा iw_statistics *piwstats = &padapter->iwstats;
	पूर्णांक पंचांगp_level = 0;
	पूर्णांक पंचांगp_qual = 0;
	पूर्णांक पंचांगp_noise = 0;

	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED) != true) अणु
		piwstats->qual.qual = 0;
		piwstats->qual.level = 0;
		piwstats->qual.noise = 0;
	पूर्ण अन्यथा अणु
		/* show percentage, we need transfer dbm to original value. */
		पंचांगp_level = padapter->recvpriv.fw_rssi;
		पंचांगp_qual = padapter->recvpriv.संकेत;
		पंचांगp_noise = padapter->recvpriv.noise;
		piwstats->qual.level = पंचांगp_level;
		piwstats->qual.qual = पंचांगp_qual;
		piwstats->qual.noise = पंचांगp_noise;
	पूर्ण
	piwstats->qual.updated = IW_QUAL_ALL_UPDATED;
	वापस &padapter->iwstats;
पूर्ण

काष्ठा iw_handler_def r871x_handlers_def = अणु
	.standard = r8711_handlers,
	.num_standard = ARRAY_SIZE(r8711_handlers),
	.निजी = r8711_निजी_handler,
	.निजी_args = (काष्ठा iw_priv_args *)r8711_निजी_args,
	.num_निजी = ARRAY_SIZE(r8711_निजी_handler),
	.num_निजी_args = माप(r8711_निजी_args) /
			    माप(काष्ठा iw_priv_args),
	.get_wireless_stats = r871x_get_wireless_stats
पूर्ण;
