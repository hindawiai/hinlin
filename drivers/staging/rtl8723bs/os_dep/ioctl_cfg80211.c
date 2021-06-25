<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा  _IOCTL_CFG80211_C_

#समावेश <linux/etherdevice.h>
#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <linux/jअगरfies.h>

#समावेश <rtw_wअगरi_regd.h>

#घोषणा RTW_MAX_MGMT_TX_CNT (8)

#घोषणा RTW_SCAN_IE_LEN_MAX      2304
#घोषणा RTW_MAX_REMAIN_ON_CHANNEL_DURATION 5000 /* ms */
#घोषणा RTW_MAX_NUM_PMKIDS 4

अटल स्थिर u32 rtw_cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104,
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
	WLAN_CIPHER_SUITE_AES_CMAC,
पूर्ण;

#घोषणा RATETAB_ENT(_rate, _rateid, _flags) \
	अणु								\
		.bitrate	= (_rate),				\
		.hw_value	= (_rateid),				\
		.flags		= (_flags),				\
	पूर्ण

#घोषणा CHAN2G(_channel, _freq, _flags) अणु			\
	.band			= NL80211_BAND_2GHZ,		\
	.center_freq		= (_freq),			\
	.hw_value		= (_channel),			\
	.flags			= (_flags),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 30,				\
पूर्ण

/* अगर wowlan is not supported, kernel generate a disconnect at each suspend
 * cf: /net/wireless/sysfs.c, so रेजिस्टर a stub wowlan.
 * Moreover wowlan has to be enabled via a the nl80211_set_wowlan callback.
 * (from user space, e.g. iw phy0 wowlan enable)
 */
अटल स्थिर काष्ठा wiphy_wowlan_support wowlan_stub = अणु
	.flags = WIPHY_WOWLAN_ANY,
	.n_patterns = 0,
	.pattern_max_len = 0,
	.pattern_min_len = 0,
	.max_pkt_offset = 0,
पूर्ण;

अटल काष्ठा ieee80211_rate rtw_rates[] = अणु
	RATETAB_ENT(10,  0x1,   0),
	RATETAB_ENT(20,  0x2,   0),
	RATETAB_ENT(55,  0x4,   0),
	RATETAB_ENT(110, 0x8,   0),
	RATETAB_ENT(60,  0x10,  0),
	RATETAB_ENT(90,  0x20,  0),
	RATETAB_ENT(120, 0x40,  0),
	RATETAB_ENT(180, 0x80,  0),
	RATETAB_ENT(240, 0x100, 0),
	RATETAB_ENT(360, 0x200, 0),
	RATETAB_ENT(480, 0x400, 0),
	RATETAB_ENT(540, 0x800, 0),
पूर्ण;

#घोषणा rtw_a_rates		(rtw_rates + 4)
#घोषणा RTW_A_RATES_NUM	8
#घोषणा rtw_g_rates		(rtw_rates + 0)
#घोषणा RTW_G_RATES_NUM	12

#घोषणा RTW_2G_CHANNELS_NUM 14
#घोषणा RTW_5G_CHANNELS_NUM 37

अटल काष्ठा ieee80211_channel rtw_2ghz_channels[] = अणु
	CHAN2G(1, 2412, 0),
	CHAN2G(2, 2417, 0),
	CHAN2G(3, 2422, 0),
	CHAN2G(4, 2427, 0),
	CHAN2G(5, 2432, 0),
	CHAN2G(6, 2437, 0),
	CHAN2G(7, 2442, 0),
	CHAN2G(8, 2447, 0),
	CHAN2G(9, 2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
पूर्ण;

अटल व्योम rtw_2g_channels_init(काष्ठा ieee80211_channel *channels)
अणु
	स_नकल((व्योम *)channels, (व्योम *)rtw_2ghz_channels,
		माप(काष्ठा ieee80211_channel)*RTW_2G_CHANNELS_NUM
	);
पूर्ण

अटल व्योम rtw_2g_rates_init(काष्ठा ieee80211_rate *rates)
अणु
	स_नकल(rates, rtw_g_rates,
		माप(काष्ठा ieee80211_rate)*RTW_G_RATES_NUM
	);
पूर्ण

अटल काष्ठा ieee80211_supported_band *rtw_spt_band_alloc(
	क्रमागत nl80211_band band
	)
अणु
	काष्ठा ieee80211_supported_band *spt_band = शून्य;
	पूर्णांक n_channels, n_bitrates;

	अगर (band == NL80211_BAND_2GHZ)
	अणु
		n_channels = RTW_2G_CHANNELS_NUM;
		n_bitrates = RTW_G_RATES_NUM;
	पूर्ण
	अन्यथा
	अणु
		जाओ निकास;
	पूर्ण

	spt_band = rtw_zदो_स्मृति(माप(काष्ठा ieee80211_supported_band) +
			       माप(काष्ठा ieee80211_channel) * n_channels +
			       माप(काष्ठा ieee80211_rate) * n_bitrates);
	अगर (!spt_band)
		जाओ निकास;

	spt_band->channels = (काष्ठा ieee80211_channel *)(((u8 *)spt_band)+माप(काष्ठा ieee80211_supported_band));
	spt_band->bitrates = (काष्ठा ieee80211_rate *)(((u8 *)spt_band->channels)+माप(काष्ठा ieee80211_channel)*n_channels);
	spt_band->band = band;
	spt_band->n_channels = n_channels;
	spt_band->n_bitrates = n_bitrates;

	अगर (band == NL80211_BAND_2GHZ)
	अणु
		rtw_2g_channels_init(spt_band->channels);
		rtw_2g_rates_init(spt_band->bitrates);
	पूर्ण

	/* spt_band.ht_cap */

निकास:

	वापस spt_band;
पूर्ण

अटल स्थिर काष्ठा ieee80211_txrx_stypes
rtw_cfg80211_शेष_mgmt_stypes[NUM_NL80211_IFTYPES] = अणु
	[NL80211_IFTYPE_ADHOC] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4)
	पूर्ण,
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
	[NL80211_IFTYPE_AP_VLAN] = अणु
		/* copy AP */
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
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_GO] = अणु
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
		BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
		BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		BIT(IEEE80211_STYPE_AUTH >> 4) |
		BIT(IEEE80211_STYPE_DEAUTH >> 4) |
		BIT(IEEE80211_STYPE_ACTION >> 4)
	पूर्ण,
पूर्ण;

अटल पूर्णांक rtw_ieee80211_channel_to_frequency(पूर्णांक chan, पूर्णांक band)
अणु
	/* see 802.11 17.3.8.3.2 and Annex J
	* there are overlapping channel numbers in 5GHz and 2GHz bands */
	अगर (band == NL80211_BAND_2GHZ) अणु
		अगर (chan == 14)
			वापस 2484;
             अन्यथा अगर (chan < 14)
			वापस 2407 + chan * 5;
	पूर्ण

	वापस 0; /* not supported */
पूर्ण

#घोषणा MAX_BSSINFO_LEN 1000
काष्ठा cfg80211_bss *rtw_cfg80211_inक्रमm_bss(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork)
अणु
	काष्ठा ieee80211_channel *notअगरy_channel;
	काष्ठा cfg80211_bss *bss = शून्य;
	/* काष्ठा ieee80211_supported_band *band; */
	u16 channel;
	u32 freq;
	u64 notअगरy_बारtamp;
	s32 notअगरy_संकेत;
	u8 *buf = शून्य, *pbuf;
	माप_प्रकार len, bssinf_len = 0;
	काष्ठा ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u8 bc_addr[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	काष्ठा wireless_dev *wdev = padapter->rtw_wdev;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	bssinf_len = pnetwork->network.IELength + माप(काष्ठा ieee80211_hdr_3addr);
	अगर (bssinf_len > MAX_BSSINFO_LEN)
		जाओ निकास;

	अणु
		u16 wapi_len = 0;

		अगर (rtw_get_wapi_ie(pnetwork->network.IEs, pnetwork->network.IELength, शून्य, &wapi_len) > 0)
		अणु
			अगर (wapi_len > 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

	/* To reduce PBC Overlap rate */
	/* spin_lock_bh(&pwdev_priv->scan_req_lock); */
	अगर (adapter_wdev_data(padapter)->scan_request)
	अणु
		u8 *psr = शून्य, sr = 0;
		काष्ठा ndis_802_11_ssid *pssid = &pnetwork->network.Ssid;
		काष्ठा cfg80211_scan_request *request = adapter_wdev_data(padapter)->scan_request;
		काष्ठा cfg80211_ssid *ssids = request->ssids;
		u32 wpsielen = 0;
		u8 *wpsie = शून्य;

		wpsie = rtw_get_wps_ie(pnetwork->network.IEs+_FIXED_IE_LENGTH_, pnetwork->network.IELength-_FIXED_IE_LENGTH_, शून्य, &wpsielen);

		अगर (wpsie && wpsielen > 0)
			psr = rtw_get_wps_attr_content(wpsie,  wpsielen, WPS_ATTR_SELECTED_REGISTRAR, (u8 *)(&sr), शून्य);

		अगर (sr != 0)
		अणु
			अगर (request->n_ssids == 1 && request->n_channels == 1) /*  it means under processing WPS */
			अणु
				अगर (ssids[0].ssid_len != 0 &&
				    (pssid->SsidLength != ssids[0].ssid_len ||
				     स_भेद(pssid->Ssid, ssids[0].ssid, ssids[0].ssid_len)))
				अणु
					अगर (psr)
						*psr = 0; /* clear sr */
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/* spin_unlock_bh(&pwdev_priv->scan_req_lock); */


	channel = pnetwork->network.Configuration.DSConfig;
	freq = rtw_ieee80211_channel_to_frequency(channel, NL80211_BAND_2GHZ);

	notअगरy_channel = ieee80211_get_channel(wiphy, freq);

	notअगरy_बारtamp = kसमय_प्रकारo_us(kसमय_get_bootसमय());

	/* We've set wiphy's संकेत_type as CFG80211_SIGNAL_TYPE_MBM: संकेत strength in mBm (100*dBm) */
	अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true &&
		is_same_network(&pmlmepriv->cur_network.network, &pnetwork->network, 0)) अणु
		notअगरy_संकेत = 100*translate_percentage_to_dbm(padapter->recvpriv.संकेत_strength);/* dbm */
	पूर्ण अन्यथा अणु
		notअगरy_संकेत = 100*translate_percentage_to_dbm(pnetwork->network.PhyInfo.SignalStrength);/* dbm */
	पूर्ण

	buf = kzalloc(MAX_BSSINFO_LEN, GFP_ATOMIC);
	अगर (!buf)
		जाओ निकास;
	pbuf = buf;

	pwlanhdr = (काष्ठा ieee80211_hdr *)pbuf;
	fctrl = &(pwlanhdr->frame_control);
	*(fctrl) = 0;

	SetSeqNum(pwlanhdr, 0/*pmlmeext->mgnt_seq*/);
	/* pmlmeext->mgnt_seq++; */

	अगर (pnetwork->network.Reserved[0] == 1) अणु /*  WIFI_BEACON */
		स_नकल(pwlanhdr->addr1, bc_addr, ETH_ALEN);
		SetFrameSubType(pbuf, WIFI_BEACON);
	पूर्ण अन्यथा अणु
		स_नकल(pwlanhdr->addr1, myid(&(padapter->eeprompriv)), ETH_ALEN);
		SetFrameSubType(pbuf, WIFI_PROBERSP);
	पूर्ण

	स_नकल(pwlanhdr->addr2, pnetwork->network.MacAddress, ETH_ALEN);
	स_नकल(pwlanhdr->addr3, pnetwork->network.MacAddress, ETH_ALEN);


	pbuf += माप(काष्ठा ieee80211_hdr_3addr);
	len = माप(काष्ठा ieee80211_hdr_3addr);

	स_नकल(pbuf, pnetwork->network.IEs, pnetwork->network.IELength);
	len += pnetwork->network.IELength;

	*((__le64 *)pbuf) = cpu_to_le64(notअगरy_बारtamp);

	bss = cfg80211_inक्रमm_bss_frame(wiphy, notअगरy_channel, (काष्ठा ieee80211_mgmt *)buf,
		len, notअगरy_संकेत, GFP_ATOMIC);

	अगर (unlikely(!bss))
		जाओ निकास;

	cfg80211_put_bss(wiphy, bss);
	kमुक्त(buf);

निकास:
	वापस bss;

पूर्ण

/*
	Check the given bss is valid by kernel API cfg80211_get_bss()
	@padapter : the given adapter

	वापस true अगर bss is valid,  false क्रम not found.
*/
पूर्णांक rtw_cfg80211_check_bss(काष्ठा adapter *padapter)
अणु
	काष्ठा wlan_bssid_ex  *pnetwork = &(padapter->mlmeextpriv.mlmext_info.network);
	काष्ठा cfg80211_bss *bss = शून्य;
	काष्ठा ieee80211_channel *notअगरy_channel = शून्य;
	u32 freq;

	अगर (!(pnetwork) || !(padapter->rtw_wdev))
		वापस false;

	freq = rtw_ieee80211_channel_to_frequency(pnetwork->Configuration.DSConfig, NL80211_BAND_2GHZ);

	notअगरy_channel = ieee80211_get_channel(padapter->rtw_wdev->wiphy, freq);
	bss = cfg80211_get_bss(padapter->rtw_wdev->wiphy, notअगरy_channel,
			pnetwork->MacAddress, pnetwork->Ssid.Ssid,
			pnetwork->Ssid.SsidLength,
			WLAN_CAPABILITY_ESS, WLAN_CAPABILITY_ESS);

	cfg80211_put_bss(padapter->rtw_wdev->wiphy, bss);

	वापस	(bss != शून्य);
पूर्ण

व्योम rtw_cfg80211_ibss_indicate_connect(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network  *cur_network = &(pmlmepriv->cur_network);
	काष्ठा wireless_dev *pwdev = padapter->rtw_wdev;
	काष्ठा wiphy *wiphy = pwdev->wiphy;
	पूर्णांक freq = (पूर्णांक)cur_network->network.Configuration.DSConfig;
	काष्ठा ieee80211_channel *chan;

	अगर (pwdev->अगरtype != NL80211_IFTYPE_ADHOC)
	अणु
		वापस;
	पूर्ण

	अगर (!rtw_cfg80211_check_bss(padapter)) अणु
		काष्ठा wlan_bssid_ex  *pnetwork = &(padapter->mlmeextpriv.mlmext_info.network);
		काष्ठा wlan_network *scanned = pmlmepriv->cur_network_scanned;

		अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)
		अणु

			स_नकल(&cur_network->network, pnetwork, माप(काष्ठा wlan_bssid_ex));
			rtw_cfg80211_inक्रमm_bss(padapter, cur_network);
		पूर्ण
		अन्यथा
		अणु
			अगर (scanned == शून्य) अणु
				rtw_warn_on(1);
				वापस;
			पूर्ण
			अगर (!स_भेद(&(scanned->network.Ssid), &(pnetwork->Ssid), माप(काष्ठा ndis_802_11_ssid))
				&& !स_भेद(scanned->network.MacAddress, pnetwork->MacAddress, माप(NDIS_802_11_MAC_ADDRESS))
			)
				rtw_cfg80211_inक्रमm_bss(padapter, scanned);
			अन्यथा
				rtw_warn_on(1);
		पूर्ण

		अगर (!rtw_cfg80211_check_bss(padapter))
			netdev_dbg(padapter->pnetdev,
				   FUNC_ADPT_FMT " BSS not found !!\n",
				   FUNC_ADPT_ARG(padapter));
	पूर्ण
	/* notअगरy cfg80211 that device joined an IBSS */
	chan = ieee80211_get_channel(wiphy, freq);
	cfg80211_ibss_joined(padapter->pnetdev, cur_network->network.MacAddress, chan, GFP_ATOMIC);
पूर्ण

व्योम rtw_cfg80211_indicate_connect(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network  *cur_network = &(pmlmepriv->cur_network);
	काष्ठा wireless_dev *pwdev = padapter->rtw_wdev;

	अगर (pwdev->अगरtype != NL80211_IFTYPE_STATION
		&& pwdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT
	) अणु
		वापस;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
		वापस;

	अणु
		काष्ठा wlan_bssid_ex  *pnetwork = &(padapter->mlmeextpriv.mlmext_info.network);
		काष्ठा wlan_network *scanned = pmlmepriv->cur_network_scanned;

		अगर (scanned == शून्य) अणु
			rtw_warn_on(1);
			जाओ check_bss;
		पूर्ण

		अगर (!स_भेद(scanned->network.MacAddress, pnetwork->MacAddress, माप(NDIS_802_11_MAC_ADDRESS))
			&& !स_भेद(&(scanned->network.Ssid), &(pnetwork->Ssid), माप(काष्ठा ndis_802_11_ssid))
		)
			rtw_cfg80211_inक्रमm_bss(padapter, scanned);
		अन्यथा
			rtw_warn_on(1);
	पूर्ण

check_bss:
	अगर (!rtw_cfg80211_check_bss(padapter))
		netdev_dbg(padapter->pnetdev,
			   FUNC_ADPT_FMT " BSS not found !!\n",
			   FUNC_ADPT_ARG(padapter));

	अगर (rtw_to_roam(padapter) > 0) अणु
		काष्ठा wiphy *wiphy = pwdev->wiphy;
		काष्ठा ieee80211_channel *notअगरy_channel;
		u32 freq;
		u16 channel = cur_network->network.Configuration.DSConfig;
		काष्ठा cfg80211_roam_info roam_info = अणुपूर्ण;

		freq = rtw_ieee80211_channel_to_frequency(channel, NL80211_BAND_2GHZ);

		notअगरy_channel = ieee80211_get_channel(wiphy, freq);

		roam_info.channel = notअगरy_channel;
		roam_info.bssid = cur_network->network.MacAddress;
		roam_info.req_ie =
			pmlmepriv->assoc_req+माप(काष्ठा ieee80211_hdr_3addr)+2;
		roam_info.req_ie_len =
			pmlmepriv->assoc_req_len-माप(काष्ठा ieee80211_hdr_3addr)-2;
		roam_info.resp_ie =
			pmlmepriv->assoc_rsp+माप(काष्ठा ieee80211_hdr_3addr)+6;
		roam_info.resp_ie_len =
			pmlmepriv->assoc_rsp_len-माप(काष्ठा ieee80211_hdr_3addr)-6;
		cfg80211_roamed(padapter->pnetdev, &roam_info, GFP_ATOMIC);
	पूर्ण
	अन्यथा
	अणु
		cfg80211_connect_result(padapter->pnetdev, cur_network->network.MacAddress
			, pmlmepriv->assoc_req+माप(काष्ठा ieee80211_hdr_3addr)+2
			, pmlmepriv->assoc_req_len-माप(काष्ठा ieee80211_hdr_3addr)-2
			, pmlmepriv->assoc_rsp+माप(काष्ठा ieee80211_hdr_3addr)+6
			, pmlmepriv->assoc_rsp_len-माप(काष्ठा ieee80211_hdr_3addr)-6
			, WLAN_STATUS_SUCCESS, GFP_ATOMIC);
	पूर्ण
पूर्ण

व्योम rtw_cfg80211_indicate_disconnect(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wireless_dev *pwdev = padapter->rtw_wdev;

	अगर (pwdev->अगरtype != NL80211_IFTYPE_STATION
		&& pwdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT
	) अणु
		वापस;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
		वापस;

	अगर (!padapter->mlmepriv.not_indic_disco) अणु
		अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
			cfg80211_disconnected(padapter->pnetdev, 0,
					      शून्य, 0, true, GFP_ATOMIC);
		पूर्ण अन्यथा अणु
			cfg80211_connect_result(padapter->pnetdev, शून्य, शून्य, 0, शून्य, 0,
				WLAN_STATUS_UNSPECIFIED_FAILURE, GFP_ATOMIC/*GFP_KERNEL*/);
		पूर्ण
	पूर्ण
पूर्ण


अटल पूर्णांक rtw_cfg80211_ap_set_encryption(काष्ठा net_device *dev, काष्ठा ieee_param *param, u32 param_len)
अणु
	पूर्णांक ret = 0;
	u32 wep_key_idx, wep_key_len;
	काष्ठा sta_info *psta = शून्य, *pbcmc_sta = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv =  &(padapter->securitypriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	अक्षर *grpkey = padapter->securitypriv.करोt118021XGrpKey[param->u.crypt.idx].skey;
	अक्षर *txkey = padapter->securitypriv.करोt118021XGrptxmickey[param->u.crypt.idx].skey;
	अक्षर *rxkey = padapter->securitypriv.करोt118021XGrprxmickey[param->u.crypt.idx].skey;

	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';

	अगर (param_len !=  माप(काष्ठा ieee_param) + param->u.crypt.key_len)
	अणु
		ret =  -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff)
	अणु
		अगर (param->u.crypt.idx >= WEP_KEYS)
		अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण
	अन्यथा
	अणु
		psta = rtw_get_stainfo(pstapriv, param->sta_addr);
		अगर (!psta)
			/* ret = -EINVAL; */
			जाओ निकास;
	पूर्ण

	अगर (म_भेद(param->u.crypt.alg, "none") == 0 && (psta == शून्य))
		जाओ निकास;

	अगर (म_भेद(param->u.crypt.alg, "WEP") == 0 && (psta == शून्य))
	अणु
		wep_key_idx = param->u.crypt.idx;
		wep_key_len = param->u.crypt.key_len;

		अगर ((wep_key_idx >= WEP_KEYS) || (wep_key_len <= 0))
		अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण

		अगर (wep_key_len > 0)
		अणु
			wep_key_len = wep_key_len <= 5 ? 5 : 13;
		पूर्ण

		अगर (psecuritypriv->bWepDefaultKeyIdxSet == 0)
		अणु
			/* wep शेष key has not been set, so use this key index as शेष key. */

			psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Auto;
			psecuritypriv->ndisencryptstatus = Ndis802_11Encryption1Enabled;
			psecuritypriv->करोt11PrivacyAlgrthm = _WEP40_;
			psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;

			अगर (wep_key_len == 13)
			अणु
				psecuritypriv->करोt11PrivacyAlgrthm = _WEP104_;
				psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
			पूर्ण

			psecuritypriv->करोt11PrivacyKeyIndex = wep_key_idx;
		पूर्ण

		स_नकल(&(psecuritypriv->करोt11DefKey[wep_key_idx].skey[0]), param->u.crypt.key, wep_key_len);

		psecuritypriv->करोt11DefKeylen[wep_key_idx] = wep_key_len;

		rtw_ap_set_wep_key(padapter, param->u.crypt.key, wep_key_len, wep_key_idx, 1);

		जाओ निकास;

	पूर्ण


	अगर (!psta && check_fwstate(pmlmepriv, WIFI_AP_STATE)) /* group key */
	अणु
		अगर (param->u.crypt.set_tx == 0) /* group key */
		अणु
			अगर (म_भेद(param->u.crypt.alg, "WEP") == 0)
			अणु
				स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

				psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;
				अगर (param->u.crypt.key_len == 13)
				अणु
						psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
				पूर्ण

			पूर्ण
			अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0)
			अणु
				psecuritypriv->करोt118021XGrpPrivacy = _TKIP_;

				स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

				/* DEBUG_ERR("set key length :param->u.crypt.key_len =%d\n", param->u.crypt.key_len); */
				/* set mic key */
				स_नकल(txkey, &(param->u.crypt.key[16]), 8);
				स_नकल(rxkey, &(param->u.crypt.key[24]), 8);

				psecuritypriv->busetkipkey = true;

			पूर्ण
			अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0)
			अणु
				psecuritypriv->करोt118021XGrpPrivacy = _AES_;

				स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));
			पूर्ण
			अन्यथा
			अणु
				psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
			पूर्ण

			psecuritypriv->करोt118021XGrpKeyid = param->u.crypt.idx;

			psecuritypriv->binstallGrpkey = true;

			psecuritypriv->करोt11PrivacyAlgrthm = psecuritypriv->करोt118021XGrpPrivacy;/*  */

			rtw_ap_set_group_key(padapter, param->u.crypt.key, psecuritypriv->करोt118021XGrpPrivacy, param->u.crypt.idx);

			pbcmc_sta = rtw_get_bcmc_stainfo(padapter);
			अगर (pbcmc_sta)
			अणु
				pbcmc_sta->ieee8021x_blocked = false;
				pbcmc_sta->करोt118021XPrivacy = psecuritypriv->करोt118021XGrpPrivacy;/* rx will use bmc_sta's करोt118021XPrivacy */
			पूर्ण

		पूर्ण

		जाओ निकास;

	पूर्ण

	अगर (psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X && psta) /*  psk/802_1x */
	अणु
		अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		अणु
			अगर (param->u.crypt.set_tx == 1) /* pairwise key */
			अणु
				स_नकल(psta->करोt118021x_UncstKey.skey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

				अगर (म_भेद(param->u.crypt.alg, "WEP") == 0)
				अणु
					psta->करोt118021XPrivacy = _WEP40_;
					अगर (param->u.crypt.key_len == 13)
					अणु
						psta->करोt118021XPrivacy = _WEP104_;
					पूर्ण
				पूर्ण
				अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0)
				अणु
					psta->करोt118021XPrivacy = _TKIP_;

					/* DEBUG_ERR("set key length :param->u.crypt.key_len =%d\n", param->u.crypt.key_len); */
					/* set mic key */
					स_नकल(psta->करोt11tkiptxmickey.skey, &(param->u.crypt.key[16]), 8);
					स_नकल(psta->करोt11tkiprxmickey.skey, &(param->u.crypt.key[24]), 8);

					psecuritypriv->busetkipkey = true;

				पूर्ण
				अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0)
				अणु

					psta->करोt118021XPrivacy = _AES_;
				पूर्ण
				अन्यथा
				अणु
					psta->करोt118021XPrivacy = _NO_PRIVACY_;
				पूर्ण

				rtw_ap_set_pairwise_key(padapter, psta);

				psta->ieee8021x_blocked = false;

				psta->bpairwise_key_installed = true;

			पूर्ण
			अन्यथा/* group key??? */
			अणु
				अगर (म_भेद(param->u.crypt.alg, "WEP") == 0)
				अणु
					स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

					psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;
					अगर (param->u.crypt.key_len == 13)
					अणु
						psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
					पूर्ण
				पूर्ण
				अन्यथा अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0)
				अणु
					psecuritypriv->करोt118021XGrpPrivacy = _TKIP_;

					स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

					/* DEBUG_ERR("set key length :param->u.crypt.key_len =%d\n", param->u.crypt.key_len); */
					/* set mic key */
					स_नकल(txkey, &(param->u.crypt.key[16]), 8);
					स_नकल(rxkey, &(param->u.crypt.key[24]), 8);

					psecuritypriv->busetkipkey = true;

				पूर्ण
				अन्यथा अगर (म_भेद(param->u.crypt.alg, "CCMP") == 0)
				अणु
					psecuritypriv->करोt118021XGrpPrivacy = _AES_;

					स_नकल(grpkey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));
				पूर्ण
				अन्यथा
				अणु
					psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
				पूर्ण

				psecuritypriv->करोt118021XGrpKeyid = param->u.crypt.idx;

				psecuritypriv->binstallGrpkey = true;

				psecuritypriv->करोt11PrivacyAlgrthm = psecuritypriv->करोt118021XGrpPrivacy;/*  */

				rtw_ap_set_group_key(padapter, param->u.crypt.key, psecuritypriv->करोt118021XGrpPrivacy, param->u.crypt.idx);

				pbcmc_sta = rtw_get_bcmc_stainfo(padapter);
				अगर (pbcmc_sta)
				अणु
					pbcmc_sta->ieee8021x_blocked = false;
					pbcmc_sta->करोt118021XPrivacy = psecuritypriv->करोt118021XGrpPrivacy;/* rx will use bmc_sta's करोt118021XPrivacy */
				पूर्ण

			पूर्ण

		पूर्ण

	पूर्ण

निकास:

	वापस ret;

पूर्ण

अटल पूर्णांक rtw_cfg80211_set_encryption(काष्ठा net_device *dev, काष्ठा ieee_param *param, u32 param_len)
अणु
	पूर्णांक ret = 0;
	u32 wep_key_idx, wep_key_len;
	काष्ठा adapter *padapter = rtw_netdev_priv(dev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	param->u.crypt.err = 0;
	param->u.crypt.alg[IEEE_CRYPT_ALG_NAME_LEN - 1] = '\0';

	अगर (param_len < (u32) ((u8 *) param->u.crypt.key - (u8 *) param) + param->u.crypt.key_len)
	अणु
		ret =  -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (param->sta_addr[0] == 0xff && param->sta_addr[1] == 0xff &&
	    param->sta_addr[2] == 0xff && param->sta_addr[3] == 0xff &&
	    param->sta_addr[4] == 0xff && param->sta_addr[5] == 0xff)
	अणु
		अगर (param->u.crypt.idx >= WEP_KEYS
			|| param->u.crypt.idx >= BIP_MAX_KEYID
		)
		अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण
	पूर्ण

	अगर (म_भेद(param->u.crypt.alg, "WEP") == 0)
	अणु
		wep_key_idx = param->u.crypt.idx;
		wep_key_len = param->u.crypt.key_len;

		अगर ((wep_key_idx >= WEP_KEYS) || (wep_key_len <= 0))
		अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण

		अगर (psecuritypriv->bWepDefaultKeyIdxSet == 0)
		अणु
			/* wep शेष key has not been set, so use this key index as शेष key. */

			wep_key_len = wep_key_len <= 5 ? 5 : 13;

			psecuritypriv->ndisencryptstatus = Ndis802_11Encryption1Enabled;
			psecuritypriv->करोt11PrivacyAlgrthm = _WEP40_;
			psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;

			अगर (wep_key_len == 13)
			अणु
				psecuritypriv->करोt11PrivacyAlgrthm = _WEP104_;
				psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
			पूर्ण

			psecuritypriv->करोt11PrivacyKeyIndex = wep_key_idx;
		पूर्ण

		स_नकल(&(psecuritypriv->करोt11DefKey[wep_key_idx].skey[0]), param->u.crypt.key, wep_key_len);

		psecuritypriv->करोt11DefKeylen[wep_key_idx] = wep_key_len;

		rtw_set_key(padapter, psecuritypriv, wep_key_idx, 0, true);

		जाओ निकास;
	पूर्ण

	अगर (padapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X) /*  802_1x */
	अणु
		काष्ठा sta_info *psta, *pbcmc_sta;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_MP_STATE) == true) /* sta mode */
		अणु
			psta = rtw_get_stainfo(pstapriv, get_bssid(pmlmepriv));
			अगर (psta) अणु
				/* Jeff: करोn't disable ieee8021x_blocked जबतक clearing key */
				अगर (म_भेद(param->u.crypt.alg, "none") != 0)
					psta->ieee8021x_blocked = false;


				अगर ((padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption2Enabled) ||
						(padapter->securitypriv.ndisencryptstatus ==  Ndis802_11Encryption3Enabled))
				अणु
					psta->करोt118021XPrivacy = padapter->securitypriv.करोt11PrivacyAlgrthm;
				पूर्ण

				अगर (param->u.crypt.set_tx == 1)/* pairwise key */
				अणु

					स_नकल(psta->करोt118021x_UncstKey.skey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));

					अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0)/* set mic key */
					अणु
						/* DEBUG_ERR(("\nset key length :param->u.crypt.key_len =%d\n", param->u.crypt.key_len)); */
						स_नकल(psta->करोt11tkiptxmickey.skey, &(param->u.crypt.key[16]), 8);
						स_नकल(psta->करोt11tkiprxmickey.skey, &(param->u.crypt.key[24]), 8);

						padapter->securitypriv.busetkipkey = false;
						/* _set_समयr(&padapter->securitypriv.tkip_समयr, 50); */
					पूर्ण

					rtw_setstakey_cmd(padapter, psta, true, true);
				पूर्ण
				अन्यथा/* group key */
				अणु
					अगर (म_भेद(param->u.crypt.alg, "TKIP") == 0 || म_भेद(param->u.crypt.alg, "CCMP") == 0)
					अणु
						स_नकल(padapter->securitypriv.करोt118021XGrpKey[param->u.crypt.idx].skey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));
						स_नकल(padapter->securitypriv.करोt118021XGrptxmickey[param->u.crypt.idx].skey, &(param->u.crypt.key[16]), 8);
						स_नकल(padapter->securitypriv.करोt118021XGrprxmickey[param->u.crypt.idx].skey, &(param->u.crypt.key[24]), 8);
	                                        padapter->securitypriv.binstallGrpkey = true;

						padapter->securitypriv.करोt118021XGrpKeyid = param->u.crypt.idx;
						rtw_set_key(padapter, &padapter->securitypriv, param->u.crypt.idx, 1, true);
					पूर्ण
					अन्यथा अगर (म_भेद(param->u.crypt.alg, "BIP") == 0)
					अणु
						/* save the IGTK key, length 16 bytes */
						स_नकल(padapter->securitypriv.करोt11wBIPKey[param->u.crypt.idx].skey, param->u.crypt.key, (param->u.crypt.key_len > 16 ? 16 : param->u.crypt.key_len));
						/*
						क्रम (no = 0;no<16;no++)
							prपूर्णांकk(" %02x ", padapter->securitypriv.करोt11wBIPKey[param->u.crypt.idx].skey[no]);
						*/
						padapter->securitypriv.करोt11wBIPKeyid = param->u.crypt.idx;
						padapter->securitypriv.binstallBIPkey = true;
					पूर्ण
				पूर्ण
			पूर्ण

			pbcmc_sta = rtw_get_bcmc_stainfo(padapter);
			अगर (pbcmc_sta == शून्य)
			अणु
				/* DEBUG_ERR(("Set OID_802_11_ADD_KEY: bcmc stainfo is null\n")); */
			पूर्ण
			अन्यथा
			अणु
				/* Jeff: करोn't disable ieee8021x_blocked जबतक clearing key */
				अगर (म_भेद(param->u.crypt.alg, "none") != 0)
					pbcmc_sta->ieee8021x_blocked = false;

				अगर ((padapter->securitypriv.ndisencryptstatus == Ndis802_11Encryption2Enabled) ||
						(padapter->securitypriv.ndisencryptstatus ==  Ndis802_11Encryption3Enabled))
				अणु
					pbcmc_sta->करोt118021XPrivacy = padapter->securitypriv.करोt11PrivacyAlgrthm;
				पूर्ण
			पूर्ण
		पूर्ण
		अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) /* adhoc mode */
		अणु
		पूर्ण
	पूर्ण

निकास:

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_rtw_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
				काष्ठा key_params *params)
अणु
	अक्षर *alg_name;
	u32 param_len;
	काष्ठा ieee_param *param = शून्य;
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	param_len = माप(काष्ठा ieee_param) + params->key_len;
	param = rtw_दो_स्मृति(param_len);
	अगर (param == शून्य)
		वापस -1;

	स_रखो(param, 0, param_len);

	param->cmd = IEEE_CMD_SET_ENCRYPTION;
	स_रखो(param->sta_addr, 0xff, ETH_ALEN);

	चयन (params->cipher) अणु
	हाल IW_AUTH_CIPHER_NONE:
		/* toकरो: हटाओ key */
		/* हटाओ = 1; */
		alg_name = "none";
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		alg_name = "WEP";
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		alg_name = "TKIP";
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		alg_name = "CCMP";
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		alg_name = "BIP";
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		जाओ addkey_end;
	पूर्ण

	म_नकलन((अक्षर *)param->u.crypt.alg, alg_name, IEEE_CRYPT_ALG_NAME_LEN);


	अगर (!mac_addr || is_broadcast_ether_addr(mac_addr))
	अणु
		param->u.crypt.set_tx = 0; /* क्रम wpa/wpa2 group key */
	पूर्ण अन्यथा अणु
		param->u.crypt.set_tx = 1; /* क्रम wpa/wpa2 pairwise key */
	पूर्ण

	param->u.crypt.idx = key_index;

	अगर (params->seq_len && params->seq)
	अणु
		स_नकल(param->u.crypt.seq, (u8 *)params->seq, params->seq_len);
	पूर्ण

	अगर (params->key_len && params->key)
	अणु
		param->u.crypt.key_len = params->key_len;
		स_नकल(param->u.crypt.key, (u8 *)params->key, params->key_len);
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true)
	अणु
		ret =  rtw_cfg80211_set_encryption(ndev, param, param_len);
	पूर्ण
	अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
	अणु
		अगर (mac_addr)
			स_नकल(param->sta_addr, (व्योम *)mac_addr, ETH_ALEN);

		ret = rtw_cfg80211_ap_set_encryption(ndev, param, param_len);
	पूर्ण
        अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true
                || check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)
        अणु
                ret =  rtw_cfg80211_set_encryption(ndev, param, param_len);
        पूर्ण

addkey_end:
	kमुक्त(param);

	वापस ret;

पूर्ण

अटल पूर्णांक cfg80211_rtw_get_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
				व्योम *cookie,
				व्योम (*callback)(व्योम *cookie,
						 काष्ठा key_params*))
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_rtw_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				u8 key_index, bool pairwise, स्थिर u8 *mac_addr)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	अगर (key_index == psecuritypriv->करोt11PrivacyKeyIndex)
	अणु
		/* clear the flag of wep शेष key set. */
		psecuritypriv->bWepDefaultKeyIdxSet = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_rtw_set_शेष_key(काष्ठा wiphy *wiphy,
	काष्ठा net_device *ndev, u8 key_index
	, bool unicast, bool multicast
	)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	अगर ((key_index < WEP_KEYS) && ((psecuritypriv->करोt11PrivacyAlgrthm == _WEP40_) || (psecuritypriv->करोt11PrivacyAlgrthm == _WEP104_))) /* set wep शेष key */
	अणु
		psecuritypriv->ndisencryptstatus = Ndis802_11Encryption1Enabled;

		psecuritypriv->करोt11PrivacyKeyIndex = key_index;

		psecuritypriv->करोt11PrivacyAlgrthm = _WEP40_;
		psecuritypriv->करोt118021XGrpPrivacy = _WEP40_;
		अगर (psecuritypriv->करोt11DefKeylen[key_index] == 13)
		अणु
			psecuritypriv->करोt11PrivacyAlgrthm = _WEP104_;
			psecuritypriv->करोt118021XGrpPrivacy = _WEP104_;
		पूर्ण

		psecuritypriv->bWepDefaultKeyIdxSet = 1; /* set the flag to represent that wep शेष key has been set */
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक cfg80211_rtw_get_station(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *ndev,
				स्थिर u8 *mac,
				काष्ठा station_info *sinfo)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	sinfo->filled = 0;

	अगर (!mac) अणु
		ret = -ENOENT;
		जाओ निकास;
	पूर्ण

	psta = rtw_get_stainfo(pstapriv, (u8 *)mac);
	अगर (psta == शून्य) अणु
		ret = -ENOENT;
		जाओ निकास;
	पूर्ण

	/* क्रम infra./P2PClient mode */
	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)
		&& check_fwstate(pmlmepriv, _FW_LINKED)
	)
	अणु
		काष्ठा wlan_network  *cur_network = &(pmlmepriv->cur_network);

		अगर (स_भेद((u8 *)mac, cur_network->network.MacAddress, ETH_ALEN)) अणु
			ret = -ENOENT;
			जाओ निकास;
		पूर्ण

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
		sinfo->संकेत = translate_percentage_to_dbm(padapter->recvpriv.संकेत_strength);

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
		sinfo->txrate.legacy = rtw_get_cur_max_rate(padapter);

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_PACKETS);
		sinfo->rx_packets = sta_rx_data_pkts(psta);

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_PACKETS);
		sinfo->tx_packets = psta->sta_stats.tx_pkts;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_FAILED);
	पूर्ण

	/* क्रम Ad-Hoc/AP mode */
	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)
 || check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)
 || check_fwstate(pmlmepriv, WIFI_AP_STATE))
		&& check_fwstate(pmlmepriv, _FW_LINKED)
	)
	अणु
		/* TODO: should acquire station info... */
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_rtw_change_अगरace(काष्ठा wiphy *wiphy,
				     काष्ठा net_device *ndev,
				     क्रमागत nl80211_अगरtype type,
				     काष्ठा vअगर_params *params)
अणु
	क्रमागत nl80211_अगरtype old_type;
	क्रमागत ndis_802_11_network_infraकाष्ठाure networkType;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा wireless_dev *rtw_wdev = padapter->rtw_wdev;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	पूर्णांक ret = 0;

	अगर (adapter_to_dvobj(padapter)->processing_dev_हटाओ == true)
	अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	अणु
		अगर (netdev_खोलो(ndev) != 0) अणु
			ret = -EPERM;
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	old_type = rtw_wdev->अगरtype;

	अगर (old_type != type)
	अणु
		pmlmeext->action_खुला_rxseq = 0xffff;
		pmlmeext->action_खुला_dialog_token = 0xff;
	पूर्ण

	चयन (type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		networkType = Ndis802_11IBSS;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		networkType = Ndis802_11Infraकाष्ठाure;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		networkType = Ndis802_11APMode;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		जाओ निकास;
	पूर्ण

	rtw_wdev->अगरtype = type;

	अगर (rtw_set_802_11_infraकाष्ठाure_mode(padapter, networkType) == false)
	अणु
		rtw_wdev->अगरtype = old_type;
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	rtw_setopmode_cmd(padapter, networkType, true);

निकास:

	वापस ret;
पूर्ण

व्योम rtw_cfg80211_indicate_scan_करोne(काष्ठा adapter *adapter, bool पातed)
अणु
	काष्ठा rtw_wdev_priv *pwdev_priv = adapter_wdev_data(adapter);
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = पातed
	पूर्ण;

	spin_lock_bh(&pwdev_priv->scan_req_lock);
	अगर (pwdev_priv->scan_request) अणु
		/* aव्योम WARN_ON(request != wiphy_to_dev(request->wiphy)->scan_req); */
		अगर (pwdev_priv->scan_request->wiphy == pwdev_priv->rtw_wdev->wiphy)
			cfg80211_scan_करोne(pwdev_priv->scan_request, &info);

		pwdev_priv->scan_request = शून्य;
	पूर्ण
	spin_unlock_bh(&pwdev_priv->scan_req_lock);
पूर्ण

व्योम rtw_cfg80211_unlink_bss(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork)
अणु
	काष्ठा wireless_dev *pwdev = padapter->rtw_wdev;
	काष्ठा wiphy *wiphy = pwdev->wiphy;
	काष्ठा cfg80211_bss *bss = शून्य;
	काष्ठा wlan_bssid_ex *select_network = &pnetwork->network;

	bss = cfg80211_get_bss(wiphy, शून्य/*notअगरy_channel*/,
		select_network->MacAddress, select_network->Ssid.Ssid,
		select_network->Ssid.SsidLength, 0/*WLAN_CAPABILITY_ESS*/,
		0/*WLAN_CAPABILITY_ESS*/);

	अगर (bss) अणु
		cfg80211_unlink_bss(wiphy, bss);
		cfg80211_put_bss(padapter->rtw_wdev->wiphy, bss);
	पूर्ण
पूर्ण

व्योम rtw_cfg80211_surveyकरोne_event_callback(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head					*plist, *phead;
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा __queue *queue	= &(pmlmepriv->scanned_queue);
	काष्ठा	wlan_network	*pnetwork = शून्य;

	spin_lock_bh(&(pmlmepriv->scanned_queue.lock));

	phead = get_list_head(queue);
	plist = get_next(phead);

	जबतक (1)
	अणु
		अगर (phead == plist)
			अवरोध;

		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		/* report network only अगर the current channel set contains the channel to which this network beदीर्घs */
		अगर (rtw_ch_set_search_ch(padapter->mlmeextpriv.channel_set, pnetwork->network.Configuration.DSConfig) >= 0
			&& rtw_mlme_band_check(padapter, pnetwork->network.Configuration.DSConfig) == true
			&& true == rtw_validate_ssid(&(pnetwork->network.Ssid))
		)
		अणु
			/* ev =translate_scan(padapter, a, pnetwork, ev, stop); */
			rtw_cfg80211_inक्रमm_bss(padapter, pnetwork);
		पूर्ण

		plist = get_next(plist);

	पूर्ण

	spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
पूर्ण

अटल पूर्णांक rtw_cfg80211_set_probe_req_wpsp2pie(काष्ठा adapter *padapter, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक wps_ielen = 0;
	u8 *wps_ie;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);

	अगर (len > 0)
	अणु
		wps_ie = rtw_get_wps_ie(buf, len, शून्य, &wps_ielen);
		अगर (wps_ie)
		अणु
			अगर (pmlmepriv->wps_probe_req_ie)
			अणु
				pmlmepriv->wps_probe_req_ie_len = 0;
				kमुक्त(pmlmepriv->wps_probe_req_ie);
				pmlmepriv->wps_probe_req_ie = शून्य;
			पूर्ण

			pmlmepriv->wps_probe_req_ie = rtw_दो_स्मृति(wps_ielen);
			अगर (!pmlmepriv->wps_probe_req_ie)
				वापस -EINVAL;

			स_नकल(pmlmepriv->wps_probe_req_ie, wps_ie, wps_ielen);
			pmlmepriv->wps_probe_req_ie_len = wps_ielen;
		पूर्ण
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक cfg80211_rtw_scan(काष्ठा wiphy *wiphy
	, काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा net_device *ndev = wdev_to_ndev(request->wdev);
	पूर्णांक i;
	u8 _status = false;
	पूर्णांक ret = 0;
	काष्ठा ndis_802_11_ssid *ssid = शून्य;
	काष्ठा rtw_ieee80211_channel ch[RTW_CHANNEL_SCAN_AMOUNT];
	u8 survey_बार = 3;
	u8 survey_बार_क्रम_one_ch = 6;
	काष्ठा cfg80211_ssid *ssids = request->ssids;
	पूर्णांक j = 0;
	bool need_indicate_scan_करोne = false;

	काष्ठा adapter *padapter;
	काष्ठा rtw_wdev_priv *pwdev_priv;
	काष्ठा mlme_priv *pmlmepriv;

	अगर (ndev == शून्य) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	padapter = rtw_netdev_priv(ndev);
	pwdev_priv = adapter_wdev_data(padapter);
	pmlmepriv = &padapter->mlmepriv;
/* endअगर */

	spin_lock_bh(&pwdev_priv->scan_req_lock);
	pwdev_priv->scan_request = request;
	spin_unlock_bh(&pwdev_priv->scan_req_lock);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
	अणु
		अगर (check_fwstate(pmlmepriv, WIFI_UNDER_WPS|_FW_UNDER_SURVEY|_FW_UNDER_LINKING) == true)
		अणु
			need_indicate_scan_करोne = true;
			जाओ check_need_indicate_scan_करोne;
		पूर्ण
	पूर्ण

	rtw_ps_deny(padapter, PS_DENY_SCAN);
	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		need_indicate_scan_करोne = true;
		जाओ check_need_indicate_scan_करोne;
	पूर्ण

	अगर (request->ie && request->ie_len > 0)
		rtw_cfg80211_set_probe_req_wpsp2pie(padapter, (u8 *)request->ie, request->ie_len);

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY) == true) अणु
		need_indicate_scan_करोne = true;
		जाओ check_need_indicate_scan_करोne;
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == true) अणु
		ret = -EBUSY;
		जाओ check_need_indicate_scan_करोne;
	पूर्ण

	अगर (pmlmepriv->LinkDetectInfo.bBusyTraffic == true)
	अणु
		अटल अचिन्हित दीर्घ lastscanसमय = 0;
		अचिन्हित दीर्घ passसमय;

		passसमय = jअगरfies_to_msecs(jअगरfies - lastscanसमय);
		lastscanसमय = jअगरfies;
		अगर (passसमय > 12000)
		अणु
			need_indicate_scan_करोne = true;
			जाओ check_need_indicate_scan_करोne;
		पूर्ण
	पूर्ण

	अगर (rtw_is_scan_deny(padapter)) अणु
		need_indicate_scan_करोne = true;
		जाओ check_need_indicate_scan_करोne;
	पूर्ण

	ssid = kzalloc(RTW_SSID_SCAN_AMOUNT * माप(काष्ठा ndis_802_11_ssid),
		       GFP_KERNEL);
	अगर (!ssid) अणु
		ret = -ENOMEM;
		जाओ check_need_indicate_scan_करोne;
	पूर्ण

	/* parsing request ssids, n_ssids */
	क्रम (i = 0; i < request->n_ssids && i < RTW_SSID_SCAN_AMOUNT; i++) अणु
		स_नकल(ssid[i].Ssid, ssids[i].ssid, ssids[i].ssid_len);
		ssid[i].SsidLength = ssids[i].ssid_len;
	पूर्ण

	/* parsing channels, n_channels */
	स_रखो(ch, 0, माप(काष्ठा rtw_ieee80211_channel)*RTW_CHANNEL_SCAN_AMOUNT);
	क्रम (i = 0; i < request->n_channels && i < RTW_CHANNEL_SCAN_AMOUNT; i++) अणु
		ch[i].hw_value = request->channels[i]->hw_value;
		ch[i].flags = request->channels[i]->flags;
	पूर्ण

	spin_lock_bh(&pmlmepriv->lock);
	अगर (request->n_channels == 1) अणु
		क्रम (i = 1; i < survey_बार_क्रम_one_ch; i++)
			स_नकल(&ch[i], &ch[0], माप(काष्ठा rtw_ieee80211_channel));
		_status = rtw_sitesurvey_cmd(padapter, ssid, RTW_SSID_SCAN_AMOUNT, ch, survey_बार_क्रम_one_ch);
	पूर्ण अन्यथा अगर (request->n_channels <= 4) अणु
		क्रम (j = request->n_channels - 1; j >= 0; j--)
			क्रम (i = 0; i < survey_बार; i++)
		अणु
			स_नकल(&ch[j*survey_बार+i], &ch[j], माप(काष्ठा rtw_ieee80211_channel));
		पूर्ण
		_status = rtw_sitesurvey_cmd(padapter, ssid, RTW_SSID_SCAN_AMOUNT, ch, survey_बार * request->n_channels);
	पूर्ण अन्यथा अणु
		_status = rtw_sitesurvey_cmd(padapter, ssid, RTW_SSID_SCAN_AMOUNT, शून्य, 0);
	पूर्ण
	spin_unlock_bh(&pmlmepriv->lock);


	अगर (_status == false)
	अणु
		ret = -1;
	पूर्ण

check_need_indicate_scan_करोne:
	kमुक्त(ssid);
	अगर (need_indicate_scan_करोne)
	अणु
		rtw_cfg80211_surveyकरोne_event_callback(padapter);
		rtw_cfg80211_indicate_scan_करोne(padapter, false);
	पूर्ण

	rtw_ps_deny_cancel(padapter, PS_DENY_SCAN);

निकास:
	वापस ret;

पूर्ण

अटल पूर्णांक cfg80211_rtw_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_cfg80211_set_wpa_version(काष्ठा security_priv *psecuritypriv, u32 wpa_version)
अणु
	अगर (!wpa_version) अणु
		psecuritypriv->ndisauthtype = Ndis802_11AuthModeOpen;
		वापस 0;
	पूर्ण


	अगर (wpa_version & (NL80211_WPA_VERSION_1 | NL80211_WPA_VERSION_2))
	अणु
		psecuritypriv->ndisauthtype = Ndis802_11AuthModeWPAPSK;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rtw_cfg80211_set_auth_type(काष्ठा security_priv *psecuritypriv,
			     क्रमागत nl80211_auth_type sme_auth_type)
अणु
	चयन (sme_auth_type) अणु
	हाल NL80211_AUTHTYPE_AUTOMATIC:

		psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Auto;

		अवरोध;
	हाल NL80211_AUTHTYPE_OPEN_SYSTEM:

		psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;

		अगर (psecuritypriv->ndisauthtype > Ndis802_11AuthModeWPA)
			psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;

		अवरोध;
	हाल NL80211_AUTHTYPE_SHARED_KEY:

		psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Shared;

		psecuritypriv->ndisencryptstatus = Ndis802_11Encryption1Enabled;


		अवरोध;
	शेष:
		psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
		/* वापस -ENOTSUPP; */
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rtw_cfg80211_set_cipher(काष्ठा security_priv *psecuritypriv, u32 cipher, bool ucast)
अणु
	u32 ndisencryptstatus = Ndis802_11EncryptionDisabled;

	u32 *profile_cipher = ucast ? &psecuritypriv->करोt11PrivacyAlgrthm :
		&psecuritypriv->करोt118021XGrpPrivacy;


	अगर (!cipher) अणु
		*profile_cipher = _NO_PRIVACY_;
		psecuritypriv->ndisencryptstatus = ndisencryptstatus;
		वापस 0;
	पूर्ण

	चयन (cipher) अणु
	हाल IW_AUTH_CIPHER_NONE:
		*profile_cipher = _NO_PRIVACY_;
		ndisencryptstatus = Ndis802_11EncryptionDisabled;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
		*profile_cipher = _WEP40_;
		ndisencryptstatus = Ndis802_11Encryption1Enabled;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		*profile_cipher = _WEP104_;
		ndisencryptstatus = Ndis802_11Encryption1Enabled;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		*profile_cipher = _TKIP_;
		ndisencryptstatus = Ndis802_11Encryption2Enabled;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		*profile_cipher = _AES_;
		ndisencryptstatus = Ndis802_11Encryption3Enabled;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (ucast) अणु
		psecuritypriv->ndisencryptstatus = ndisencryptstatus;

		/* अगर (psecuritypriv->करोt11PrivacyAlgrthm >= _AES_) */
		/*	psecuritypriv->ndisauthtype = Ndis802_11AuthModeWPA2PSK; */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_cfg80211_set_key_mgt(काष्ठा security_priv *psecuritypriv, u32 key_mgt)
अणु
	अगर (key_mgt == WLAN_AKM_SUITE_8021X)
		/* auth_type = UMAC_AUTH_TYPE_8021X; */
		psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;
	अन्यथा अगर (key_mgt == WLAN_AKM_SUITE_PSK) अणु
		psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_cfg80211_set_wpa_ie(काष्ठा adapter *padapter, u8 *pie, माप_प्रकार ielen)
अणु
	u8 *buf = शून्य;
	पूर्णांक group_cipher = 0, pairwise_cipher = 0;
	पूर्णांक ret = 0;
	पूर्णांक wpa_ielen = 0;
	पूर्णांक wpa2_ielen = 0;
	u8 *pwpa, *pwpa2;
	u8 null_addr[] = अणु0, 0, 0, 0, 0, 0पूर्ण;

	अगर (pie == शून्य || !ielen) अणु
		/* Treat this as normal हाल, but need to clear WIFI_UNDER_WPS */
		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
		जाओ निकास;
	पूर्ण

	अगर (ielen > MAX_WPA_IE_LEN+MAX_WPS_IE_LEN+MAX_P2P_IE_LEN) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

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

	pwpa = rtw_get_wpa_ie(buf, &wpa_ielen, ielen);
	अगर (pwpa && wpa_ielen > 0) अणु
		अगर (rtw_parse_wpa_ie(pwpa, wpa_ielen+2, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPAPSK;
			स_नकल(padapter->securitypriv.supplicant_ie, &pwpa[0], wpa_ielen+2);
		पूर्ण
	पूर्ण

	pwpa2 = rtw_get_wpa2_ie(buf, &wpa2_ielen, ielen);
	अगर (pwpa2 && wpa2_ielen > 0) अणु
		अगर (rtw_parse_wpa2_ie(pwpa2, wpa2_ielen+2, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			padapter->securitypriv.करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;
			padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeWPA2PSK;
			स_नकल(padapter->securitypriv.supplicant_ie, &pwpa2[0], wpa2_ielen+2);
		पूर्ण
	पूर्ण

	अगर (group_cipher == 0)
		group_cipher = WPA_CIPHER_NONE;

	अगर (pairwise_cipher == 0)
		pairwise_cipher = WPA_CIPHER_NONE;

	चयन (group_cipher)
	अणु
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

	चयन (pairwise_cipher)
	अणु
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

	अणु/* handle wps_ie */
		uपूर्णांक wps_ielen;
		u8 *wps_ie;

		wps_ie = rtw_get_wps_ie(buf, ielen, शून्य, &wps_ielen);
		अगर (wps_ie && wps_ielen > 0) अणु
			padapter->securitypriv.wps_ie_len = wps_ielen < MAX_WPS_IE_LEN ? wps_ielen : MAX_WPS_IE_LEN;
			स_नकल(padapter->securitypriv.wps_ie, wps_ie, padapter->securitypriv.wps_ie_len);
			set_fwstate(&padapter->mlmepriv, WIFI_UNDER_WPS);
		पूर्ण अन्यथा अणु
			_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
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
	अगर (ret)
		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_rtw_join_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				  काष्ठा cfg80211_ibss_params *params)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा ndis_802_11_ssid ndis_ssid;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	पूर्णांक ret = 0;

	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (!params->ssid || !params->ssid_len) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (params->ssid_len > IW_ESSID_MAX_SIZE) अणु

		ret = -E2BIG;
		जाओ निकास;
	पूर्ण

	स_रखो(&ndis_ssid, 0, माप(काष्ठा ndis_802_11_ssid));
	ndis_ssid.SsidLength = params->ssid_len;
	स_नकल(ndis_ssid.Ssid, (u8 *)params->ssid, params->ssid_len);

	psecuritypriv->ndisencryptstatus = Ndis802_11EncryptionDisabled;
	psecuritypriv->करोt11PrivacyAlgrthm = _NO_PRIVACY_;
	psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
	psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open; /* खोलो प्रणाली */
	psecuritypriv->ndisauthtype = Ndis802_11AuthModeOpen;

	ret = rtw_cfg80211_set_auth_type(psecuritypriv, NL80211_AUTHTYPE_OPEN_SYSTEM);
	rtw_set_802_11_authentication_mode(padapter, psecuritypriv->ndisauthtype);

	अगर (rtw_set_802_11_ssid(padapter, &ndis_ssid) == false) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_rtw_leave_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा wireless_dev *rtw_wdev = padapter->rtw_wdev;
	क्रमागत nl80211_अगरtype old_type;
	पूर्णांक ret = 0;

	old_type = rtw_wdev->अगरtype;

	rtw_set_to_roam(padapter, 0);

	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
		rtw_scan_पात(padapter);
		LeaveAllPowerSaveMode(padapter);

		rtw_wdev->अगरtype = NL80211_IFTYPE_STATION;

		अगर (rtw_set_802_11_infraकाष्ठाure_mode(padapter, Ndis802_11Infraकाष्ठाure) == false)
		अणु
			rtw_wdev->अगरtype = old_type;
			ret = -EPERM;
			जाओ leave_ibss;
		पूर्ण
		rtw_setopmode_cmd(padapter, Ndis802_11Infraकाष्ठाure, true);
	पूर्ण

leave_ibss:
	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_rtw_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				 काष्ठा cfg80211_connect_params *sme)
अणु
	पूर्णांक ret = 0;
	क्रमागत ndis_802_11_authentication_mode authmode;
	काष्ठा ndis_802_11_ssid ndis_ssid;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	padapter->mlmepriv.not_indic_disco = true;


	अगर (adapter_wdev_data(padapter)->block == true) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	rtw_ps_deny(padapter, PS_DENY_JOIN);
	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		ret = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (!sme->ssid || !sme->ssid_len) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (sme->ssid_len > IW_ESSID_MAX_SIZE) अणु

		ret = -E2BIG;
		जाओ निकास;
	पूर्ण

	स_रखो(&ndis_ssid, 0, माप(काष्ठा ndis_802_11_ssid));
	ndis_ssid.SsidLength = sme->ssid_len;
	स_नकल(ndis_ssid.Ssid, (u8 *)sme->ssid, sme->ssid_len);

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == true) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY) == true) अणु
		rtw_scan_पात(padapter);
	पूर्ण

	psecuritypriv->ndisencryptstatus = Ndis802_11EncryptionDisabled;
	psecuritypriv->करोt11PrivacyAlgrthm = _NO_PRIVACY_;
	psecuritypriv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
	psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open; /* खोलो प्रणाली */
	psecuritypriv->ndisauthtype = Ndis802_11AuthModeOpen;

	ret = rtw_cfg80211_set_wpa_version(psecuritypriv, sme->crypto.wpa_versions);
	अगर (ret < 0)
		जाओ निकास;

	ret = rtw_cfg80211_set_auth_type(psecuritypriv, sme->auth_type);

	अगर (ret < 0)
		जाओ निकास;

	ret = rtw_cfg80211_set_wpa_ie(padapter, (u8 *)sme->ie, sme->ie_len);
	अगर (ret < 0)
		जाओ निकास;

	अगर (sme->crypto.n_ciphers_pairwise) अणु
		ret = rtw_cfg80211_set_cipher(psecuritypriv, sme->crypto.ciphers_pairwise[0], true);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	/* For WEP Shared auth */
	अगर ((psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_Shared ||
	    psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_Auto) && sme->key) अणु
		u32 wep_key_idx, wep_key_len, wep_total_len;
		काष्ठा ndis_802_11_wep	 *pwep = शून्य;

		wep_key_idx = sme->key_idx;
		wep_key_len = sme->key_len;

		अगर (sme->key_idx > WEP_KEYS) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण

		अगर (wep_key_len > 0) अणु
			wep_key_len = wep_key_len <= 5 ? 5 : 13;
			wep_total_len = wep_key_len + FIELD_OFFSET(काष्ठा ndis_802_11_wep, KeyMaterial);
			pwep = rtw_दो_स्मृति(wep_total_len);
			अगर (pwep == शून्य) अणु
				ret = -ENOMEM;
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

		स_नकल(pwep->KeyMaterial,  (व्योम *)sme->key, pwep->KeyLength);

		अगर (rtw_set_802_11_add_wep(padapter, pwep) == (u8)_FAIL)
			ret = -EOPNOTSUPP;

		kमुक्त(pwep);

		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	ret = rtw_cfg80211_set_cipher(psecuritypriv, sme->crypto.cipher_group, false);
	अगर (ret < 0)
		वापस ret;

	अगर (sme->crypto.n_akm_suites) अणु
		ret = rtw_cfg80211_set_key_mgt(psecuritypriv, sme->crypto.akm_suites[0]);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	authmode = psecuritypriv->ndisauthtype;
	rtw_set_802_11_authentication_mode(padapter, authmode);

	/* rtw_set_802_11_encryption_mode(padapter, padapter->securitypriv.ndisencryptstatus); */

	अगर (rtw_set_802_11_connect(padapter, (u8 *)sme->bssid, &ndis_ssid) == false) अणु
		ret = -1;
		जाओ निकास;
	पूर्ण

निकास:

	rtw_ps_deny_cancel(padapter, PS_DENY_JOIN);

	padapter->mlmepriv.not_indic_disco = false;

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_rtw_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				   u16 reason_code)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);

	rtw_set_to_roam(padapter, 0);

	rtw_scan_पात(padapter);
	LeaveAllPowerSaveMode(padapter);
	rtw_disassoc_cmd(padapter, 500, false);

	rtw_indicate_disconnect(padapter);

	rtw_मुक्त_assoc_resources(padapter, 1);
	rtw_pwr_wakeup(padapter);

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_rtw_set_txघातer(काष्ठा wiphy *wiphy,
	काष्ठा wireless_dev *wdev,
	क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_rtw_get_txघातer(काष्ठा wiphy *wiphy,
	काष्ठा wireless_dev *wdev,
	पूर्णांक *dbm)
अणु
	*dbm = (12);

	वापस 0;
पूर्ण

अंतरभूत bool rtw_cfg80211_pwr_mgmt(काष्ठा adapter *adapter)
अणु
	काष्ठा rtw_wdev_priv *rtw_wdev_priv = adapter_wdev_data(adapter);
	वापस rtw_wdev_priv->घातer_mgmt;
पूर्ण

अटल पूर्णांक cfg80211_rtw_set_घातer_mgmt(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *ndev,
				       bool enabled, पूर्णांक समयout)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा rtw_wdev_priv *rtw_wdev_priv = adapter_wdev_data(padapter);

	rtw_wdev_priv->घातer_mgmt = enabled;

	अगर (!enabled)
		LPS_Leave(padapter, "CFG80211_PWRMGMT");

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_rtw_set_pmksa(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *ndev,
				  काष्ठा cfg80211_pmksa *pmksa)
अणु
	u8 index, blInserted = false;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	u8 strZeroMacAddress[ETH_ALEN] = अणु 0x00 पूर्ण;

	अगर (!स_भेद((u8 *)pmksa->bssid, strZeroMacAddress, ETH_ALEN))
		वापस -EINVAL;

	blInserted = false;

	/* overग_लिखो PMKID */
	क्रम (index = 0 ; index < NUM_PMKID_CACHE; index++) अणु
		अगर (!स_भेद(psecuritypriv->PMKIDList[index].Bssid, (u8 *)pmksa->bssid, ETH_ALEN)) अणु

			स_नकल(psecuritypriv->PMKIDList[index].PMKID, (u8 *)pmksa->pmkid, WLAN_PMKID_LEN);
			psecuritypriv->PMKIDList[index].bUsed = true;
			psecuritypriv->PMKIDIndex = index+1;
			blInserted = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!blInserted) अणु

		स_नकल(psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].Bssid, (u8 *)pmksa->bssid, ETH_ALEN);
		स_नकल(psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].PMKID, (u8 *)pmksa->pmkid, WLAN_PMKID_LEN);

		psecuritypriv->PMKIDList[psecuritypriv->PMKIDIndex].bUsed = true;
		psecuritypriv->PMKIDIndex++;
		अगर (psecuritypriv->PMKIDIndex == 16)
			psecuritypriv->PMKIDIndex = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_rtw_del_pmksa(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *ndev,
				  काष्ठा cfg80211_pmksa *pmksa)
अणु
	u8 index, bMatched = false;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	क्रम (index = 0 ; index < NUM_PMKID_CACHE; index++) अणु
		अगर (!स_भेद(psecuritypriv->PMKIDList[index].Bssid, (u8 *)pmksa->bssid, ETH_ALEN)) अणु
			/*
			 * BSSID is matched, the same AP => Remove this PMKID inक्रमmation
			 * and reset it.
			 */
			eth_zero_addr(psecuritypriv->PMKIDList[index].Bssid);
			स_रखो(psecuritypriv->PMKIDList[index].PMKID, 0x00, WLAN_PMKID_LEN);
			psecuritypriv->PMKIDList[index].bUsed = false;
			bMatched = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!bMatched)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_rtw_flush_pmksa(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *ndev)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;

	स_रखो(&psecuritypriv->PMKIDList[0], 0x00, माप(काष्ठा rt_pmkid_list) * NUM_PMKID_CACHE);
	psecuritypriv->PMKIDIndex = 0;

	वापस 0;
पूर्ण

व्योम rtw_cfg80211_indicate_sta_assoc(काष्ठा adapter *padapter, u8 *pmgmt_frame, uपूर्णांक frame_len)
अणु
	काष्ठा net_device *ndev = padapter->pnetdev;

	अणु
		काष्ठा station_info sinfo = अणुपूर्ण;
		u8 ie_offset;
		अगर (GetFrameSubType(pmgmt_frame) == WIFI_ASSOCREQ)
			ie_offset = _ASOCREQ_IE_OFFSET_;
		अन्यथा /*  WIFI_REASSOCREQ */
			ie_offset = _REASOCREQ_IE_OFFSET_;

		sinfo.filled = 0;
		sinfo.assoc_req_ies = pmgmt_frame + WLAN_HDR_A3_LEN + ie_offset;
		sinfo.assoc_req_ies_len = frame_len - WLAN_HDR_A3_LEN - ie_offset;
		cfg80211_new_sta(ndev, GetAddr2Ptr(pmgmt_frame), &sinfo, GFP_ATOMIC);
	पूर्ण
पूर्ण

व्योम rtw_cfg80211_indicate_sta_disassoc(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, अचिन्हित लघु reason)
अणु
	काष्ठा net_device *ndev = padapter->pnetdev;

	cfg80211_del_sta(ndev, da, GFP_ATOMIC);
पूर्ण



अटल netdev_tx_t rtw_cfg80211_monitor_अगर_xmit_entry(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	पूर्णांक rtap_len;
	पूर्णांक qos_len = 0;
	पूर्णांक करोt11_hdr_len = 24;
	पूर्णांक snap_len = 6;
	अचिन्हित अक्षर *pdata;
	u16 frame_control;
	अचिन्हित अक्षर src_mac_addr[6];
	अचिन्हित अक्षर dst_mac_addr[6];
	काष्ठा ieee80211_hdr *करोt11_hdr;
	काष्ठा ieee80211_radiotap_header *rtap_hdr;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);

	अगर (!skb)
		जाओ fail;

	अगर (unlikely(skb->len < माप(काष्ठा ieee80211_radiotap_header)))
		जाओ fail;

	rtap_hdr = (काष्ठा ieee80211_radiotap_header *)skb->data;
	अगर (unlikely(rtap_hdr->it_version))
		जाओ fail;

	rtap_len = ieee80211_get_radiotap_len(skb->data);
	अगर (unlikely(skb->len < rtap_len))
		जाओ fail;

	अगर (rtap_len != 14)
		जाओ fail;

	/* Skip the ratio tap header */
	skb_pull(skb, rtap_len);

	करोt11_hdr = (काष्ठा ieee80211_hdr *)skb->data;
	frame_control = le16_to_cpu(करोt11_hdr->frame_control);
	/* Check अगर the QoS bit is set */
	अगर ((frame_control & IEEE80211_FCTL_FTYPE) == IEEE80211_FTYPE_DATA) अणु
		/* Check अगर this ia a Wireless Distribution System (WDS) frame
		 * which has 4 MAC addresses
		 */
		अगर (frame_control & 0x0080)
			qos_len = 2;
		अगर ((frame_control & 0x0300) == 0x0300)
			करोt11_hdr_len += 6;

		स_नकल(dst_mac_addr, करोt11_hdr->addr1, माप(dst_mac_addr));
		स_नकल(src_mac_addr, करोt11_hdr->addr2, माप(src_mac_addr));

		/* Skip the 802.11 header, QoS (अगर any) and SNAP, but leave spaces क्रम
		 * क्रम two MAC addresses
		 */
		skb_pull(skb, करोt11_hdr_len + qos_len + snap_len - माप(src_mac_addr) * 2);
		pdata = (अचिन्हित अक्षर *)skb->data;
		स_नकल(pdata, dst_mac_addr, माप(dst_mac_addr));
		स_नकल(pdata + माप(dst_mac_addr), src_mac_addr, माप(src_mac_addr));

		/* Use the real net device to transmit the packet */
		वापस _rtw_xmit_entry(skb, padapter->pnetdev);

	पूर्ण अन्यथा अगर ((frame_control & (IEEE80211_FCTL_FTYPE|IEEE80211_FCTL_STYPE)) ==
		   (IEEE80211_FTYPE_MGMT|IEEE80211_STYPE_ACTION)) अणु
		/* only क्रम action frames */
		काष्ठा xmit_frame		*pmgntframe;
		काष्ठा pkt_attrib	*pattrib;
		अचिन्हित अक्षर *pframe;
		/* u8 category, action, OUI_Subtype, dialogToken = 0; */
		/* अचिन्हित अक्षर *frame_body; */
		काष्ठा ieee80211_hdr *pwlanhdr;
		काष्ठा xmit_priv *pxmitpriv = &(padapter->xmitpriv);
		काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
		u8 *buf = skb->data;
		u32 len = skb->len;
		u8 category, action;

		अगर (rtw_action_frame_parse(buf, len, &category, &action) == false)
			जाओ fail;

		/* starting alloc mgmt frame to dump it */
		pmgntframe = alloc_mgtxmitframe(pxmitpriv);
		अगर (!pmgntframe)
			जाओ fail;

		/* update attribute */
		pattrib = &pmgntframe->attrib;
		update_mgntframe_attrib(padapter, pattrib);
		pattrib->retry_ctrl = false;

		स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

		pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

		स_नकल(pframe, (व्योम *)buf, len);
		pattrib->pktlen = len;

		pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;
		/* update seq number */
		pmlmeext->mgnt_seq = GetSequence(pwlanhdr);
		pattrib->seqnum = pmlmeext->mgnt_seq;
		pmlmeext->mgnt_seq++;


		pattrib->last_txcmdsz = pattrib->pktlen;

		dump_mgntframe(padapter, pmgntframe);

	पूर्ण

fail:

	dev_kमुक्त_skb_any(skb);

	वापस NETDEV_TX_OK;

पूर्ण



अटल स्थिर काष्ठा net_device_ops rtw_cfg80211_monitor_अगर_ops = अणु
	.nकरो_start_xmit = rtw_cfg80211_monitor_अगर_xmit_entry,
पूर्ण;

अटल पूर्णांक rtw_cfg80211_add_monitor_अगर(काष्ठा adapter *padapter, अक्षर *name, काष्ठा net_device **ndev)
अणु
	पूर्णांक ret = 0;
	काष्ठा net_device *mon_ndev = शून्य;
	काष्ठा wireless_dev *mon_wdev = शून्य;
	काष्ठा rtw_netdev_priv_indicator *pnpi;
	काष्ठा rtw_wdev_priv *pwdev_priv = adapter_wdev_data(padapter);

	अगर (!name) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (pwdev_priv->pmon_ndev) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	mon_ndev = alloc_etherdev(माप(काष्ठा rtw_netdev_priv_indicator));
	अगर (!mon_ndev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mon_ndev->type = ARPHRD_IEEE80211_RADIOTAP;
	म_नकलन(mon_ndev->name, name, IFNAMSIZ);
	mon_ndev->name[IFNAMSIZ - 1] = 0;
	mon_ndev->needs_मुक्त_netdev = true;
	mon_ndev->priv_deकाष्ठाor = rtw_ndev_deकाष्ठाor;

	mon_ndev->netdev_ops = &rtw_cfg80211_monitor_अगर_ops;

	pnpi = netdev_priv(mon_ndev);
	pnpi->priv = padapter;
	pnpi->माप_priv = माप(काष्ठा adapter);

	/*  wdev */
	mon_wdev = rtw_zदो_स्मृति(माप(काष्ठा wireless_dev));
	अगर (!mon_wdev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mon_wdev->wiphy = padapter->rtw_wdev->wiphy;
	mon_wdev->netdev = mon_ndev;
	mon_wdev->अगरtype = NL80211_IFTYPE_MONITOR;
	mon_ndev->ieee80211_ptr = mon_wdev;

	ret = cfg80211_रेजिस्टर_netdevice(mon_ndev);
	अगर (ret) अणु
		जाओ out;
	पूर्ण

	*ndev = pwdev_priv->pmon_ndev = mon_ndev;
	स_नकल(pwdev_priv->अगरname_mon, name, IFNAMSIZ+1);

out:
	अगर (ret && mon_wdev) अणु
		kमुक्त(mon_wdev);
		mon_wdev = शून्य;
	पूर्ण

	अगर (ret && mon_ndev) अणु
		मुक्त_netdev(mon_ndev);
		*ndev = mon_ndev = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा wireless_dev *
	cfg80211_rtw_add_भव_पूर्णांकf(
		काष्ठा wiphy *wiphy,
		स्थिर अक्षर *name,
		अचिन्हित अक्षर name_assign_type,
		क्रमागत nl80211_अगरtype type, काष्ठा vअगर_params *params)
अणु
	पूर्णांक ret = 0;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा adapter *padapter = wiphy_to_adapter(wiphy);

	चयन (type) अणु
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_WDS:
	हाल NL80211_IFTYPE_MESH_POINT:
		ret = -ENODEV;
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		ret = rtw_cfg80211_add_monitor_अगर(padapter, (अक्षर *)name, &ndev);
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_STATION:
		ret = -ENODEV;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_AP:
		ret = -ENODEV;
		अवरोध;
	शेष:
		ret = -ENODEV;
		अवरोध;
	पूर्ण

	वापस ndev ? ndev->ieee80211_ptr : ERR_PTR(ret);
पूर्ण

अटल पूर्णांक cfg80211_rtw_del_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
	काष्ठा wireless_dev *wdev
)
अणु
	काष्ठा net_device *ndev = wdev_to_ndev(wdev);
	पूर्णांक ret = 0;
	काष्ठा adapter *adapter;
	काष्ठा rtw_wdev_priv *pwdev_priv;

	अगर (!ndev) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	adapter = rtw_netdev_priv(ndev);
	pwdev_priv = adapter_wdev_data(adapter);

	cfg80211_unरेजिस्टर_netdevice(ndev);

	अगर (ndev == pwdev_priv->pmon_ndev) अणु
		pwdev_priv->pmon_ndev = शून्य;
		pwdev_priv->अगरname_mon[0] = '\0';
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_add_beacon(काष्ठा adapter *adapter, स्थिर u8 *head, माप_प्रकार head_len, स्थिर u8 *tail, माप_प्रकार tail_len)
अणु
	पूर्णांक ret = 0;
	u8 *pbuf = शून्य;
	uपूर्णांक len, wps_ielen = 0;
	काष्ठा mlme_priv *pmlmepriv = &(adapter->mlmepriv);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) != true)
		वापस -EINVAL;

	अगर (head_len < 24)
		वापस -EINVAL;

	pbuf = rtw_zदो_स्मृति(head_len+tail_len);
	अगर (!pbuf)
		वापस -ENOMEM;

	स_नकल(pbuf, (व्योम *)head+24, head_len-24);/*  24 =beacon header len. */
	स_नकल(pbuf+head_len-24, (व्योम *)tail, tail_len);

	len = head_len+tail_len-24;

	/* check wps ie अगर inclued */
	rtw_get_wps_ie(pbuf + _FIXED_IE_LENGTH_, len - _FIXED_IE_LENGTH_, शून्य, &wps_ielen);

	/* pbss_network->IEs will not include p2p_ie, wfd ie */
	rtw_ies_हटाओ_ie(pbuf, &len, _BEACON_IE_OFFSET_, WLAN_EID_VENDOR_SPECIFIC, P2P_OUI, 4);
	rtw_ies_हटाओ_ie(pbuf, &len, _BEACON_IE_OFFSET_, WLAN_EID_VENDOR_SPECIFIC, WFD_OUI, 4);

	अगर (rtw_check_beacon_data(adapter, pbuf,  len) == _SUCCESS) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण


	kमुक्त(pbuf);

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_rtw_start_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
								काष्ठा cfg80211_ap_settings *settings)
अणु
	पूर्णांक ret = 0;
	काष्ठा adapter *adapter = rtw_netdev_priv(ndev);

	ret = rtw_add_beacon(adapter, settings->beacon.head, settings->beacon.head_len,
		settings->beacon.tail, settings->beacon.tail_len);

	adapter->mlmeextpriv.mlmext_info.hidden_ssid_mode = settings->hidden_ssid;

	अगर (settings->ssid && settings->ssid_len) अणु
		काष्ठा wlan_bssid_ex *pbss_network = &adapter->mlmepriv.cur_network.network;
		काष्ठा wlan_bssid_ex *pbss_network_ext = &adapter->mlmeextpriv.mlmext_info.network;

		स_नकल(pbss_network->Ssid.Ssid, (व्योम *)settings->ssid, settings->ssid_len);
		pbss_network->Ssid.SsidLength = settings->ssid_len;
		स_नकल(pbss_network_ext->Ssid.Ssid, (व्योम *)settings->ssid, settings->ssid_len);
		pbss_network_ext->Ssid.SsidLength = settings->ssid_len;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cfg80211_rtw_change_beacon(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
                                काष्ठा cfg80211_beacon_data *info)
अणु
	काष्ठा adapter *adapter = rtw_netdev_priv(ndev);

	वापस rtw_add_beacon(adapter, info->head, info->head_len, info->tail, info->tail_len);
पूर्ण

अटल पूर्णांक cfg80211_rtw_stop_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक	cfg80211_rtw_add_station(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				स्थिर u8 *mac,
			काष्ठा station_parameters *params)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_rtw_del_station(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				    काष्ठा station_del_parameters *params)
अणु
	पूर्णांक ret = 0;
	काष्ठा list_head	*phead, *plist;
	u8 updated = false;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	स्थिर u8 *mac = params->mac;

	अगर (check_fwstate(pmlmepriv, (_FW_LINKED | WIFI_AP_STATE)) != true)
		वापस -EINVAL;

	अगर (!mac) अणु
		flush_all_cam_entry(padapter);	/* clear CAM */

		rtw_sta_flush(padapter);

		वापस 0;
	पूर्ण

	अगर (mac[0] == 0xff && mac[1] == 0xff &&
	    mac[2] == 0xff && mac[3] == 0xff &&
	    mac[4] == 0xff && mac[5] == 0xff) अणु
		वापस -EINVAL;
	पूर्ण


	spin_lock_bh(&pstapriv->asoc_list_lock);

	phead = &pstapriv->asoc_list;
	plist = get_next(phead);

	/* check asoc_queue */
	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, asoc_list);

		plist = get_next(plist);

		अगर (!स_भेद((u8 *)mac, psta->hwaddr, ETH_ALEN)) अणु
			अगर (psta->करोt8021xalg != 1 || psta->bpairwise_key_installed) अणु
				list_del_init(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;

				updated = ap_मुक्त_sta(padapter, psta, true, WLAN_REASON_DEAUTH_LEAVING);

				psta = शून्य;

				अवरोध;
			पूर्ण

		पूर्ण

	पूर्ण

	spin_unlock_bh(&pstapriv->asoc_list_lock);

	associated_clients_update(padapter, updated);

	वापस ret;

पूर्ण

अटल पूर्णांक cfg80211_rtw_change_station(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				  स्थिर u8 *mac, काष्ठा station_parameters *params)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा sta_info *rtw_sta_info_get_by_idx(स्थिर पूर्णांक idx, काष्ठा sta_priv *pstapriv)

अणु
	काष्ठा list_head	*phead, *plist;
	काष्ठा sta_info *psta = शून्य;
	पूर्णांक i = 0;

	phead = &pstapriv->asoc_list;
	plist = get_next(phead);

	/* check asoc_queue */
	जबतक (phead != plist) अणु
		अगर (idx == i)
			psta = container_of(plist, काष्ठा sta_info, asoc_list);
		plist = get_next(plist);
		i++;
	पूर्ण
	वापस psta;
पूर्ण

अटल पूर्णांक	cfg80211_rtw_dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			       पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo)
अणु

	पूर्णांक ret = 0;
	काष्ठा adapter *padapter = rtw_netdev_priv(ndev);
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	spin_lock_bh(&pstapriv->asoc_list_lock);
	psta = rtw_sta_info_get_by_idx(idx, pstapriv);
	spin_unlock_bh(&pstapriv->asoc_list_lock);
	अगर (शून्य == psta) अणु
		ret = -ENOENT;
		जाओ निकास;
	पूर्ण
	स_नकल(mac, psta->hwaddr, ETH_ALEN);
	sinfo->filled = BIT_ULL(NL80211_STA_INFO_SIGNAL);
	sinfo->संकेत = psta->rssi;

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक	cfg80211_rtw_change_bss(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
			      काष्ठा bss_parameters *params)
अणु
	वापस 0;
पूर्ण

व्योम rtw_cfg80211_rx_action(काष्ठा adapter *adapter, u8 *frame, uपूर्णांक frame_len, स्थिर अक्षर *msg)
अणु
	s32 freq;
	पूर्णांक channel;
	u8 category, action;

	channel = rtw_get_oper_ch(adapter);

	rtw_action_frame_parse(frame, frame_len, &category, &action);

	freq = rtw_ieee80211_channel_to_frequency(channel, NL80211_BAND_2GHZ);

	rtw_cfg80211_rx_mgmt(adapter, freq, 0, frame, frame_len, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक _cfg80211_rtw_mgmt_tx(काष्ठा adapter *padapter, u8 tx_ch, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा xmit_frame	*pmgntframe;
	काष्ठा pkt_attrib	*pattrib;
	अचिन्हित अक्षर *pframe;
	पूर्णांक ret = _FAIL;
	bool ack = true;
	काष्ठा ieee80211_hdr *pwlanhdr;
	काष्ठा xmit_priv *pxmitpriv = &(padapter->xmitpriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);

	rtw_set_scan_deny(padapter, 1000);

	rtw_scan_पात(padapter);
	अगर (tx_ch != rtw_get_oper_ch(padapter)) अणु
		अगर (!check_fwstate(&padapter->mlmepriv, _FW_LINKED))
			pmlmeext->cur_channel = tx_ch;
		set_channel_bwmode(padapter, tx_ch, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);
	पूर्ण

	/* starting alloc mgmt frame to dump it */
	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	अगर (!pmgntframe) अणु
		/* ret = -ENOMEM; */
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(padapter, pattrib);
	pattrib->retry_ctrl = false;

	स_रखो(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

	स_नकल(pframe, (व्योम *)buf, len);
	pattrib->pktlen = len;

	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;
	/* update seq number */
	pmlmeext->mgnt_seq = GetSequence(pwlanhdr);
	pattrib->seqnum = pmlmeext->mgnt_seq;
	pmlmeext->mgnt_seq++;

	pattrib->last_txcmdsz = pattrib->pktlen;

	अगर (dump_mgntframe_and_रुको_ack(padapter, pmgntframe) != _SUCCESS) अणु
		ack = false;
		ret = _FAIL;

	पूर्ण अन्यथा अणु
		msleep(50);

		ret = _SUCCESS;
	पूर्ण

निकास:

	वापस ret;

पूर्ण

अटल पूर्णांक cfg80211_rtw_mgmt_tx(काष्ठा wiphy *wiphy,
	काष्ठा wireless_dev *wdev,
	काष्ठा cfg80211_mgmt_tx_params *params,
	u64 *cookie)
अणु
	काष्ठा net_device *ndev = wdev_to_ndev(wdev);
	काष्ठा ieee80211_channel *chan = params->chan;
	स्थिर u8 *buf = params->buf;
	माप_प्रकार len = params->len;
	पूर्णांक ret = 0;
	पूर्णांक tx_ret;
	u32 dump_limit = RTW_MAX_MGMT_TX_CNT;
	u32 dump_cnt = 0;
	bool ack = true;
	u8 tx_ch = (u8)ieee80211_frequency_to_channel(chan->center_freq);
	u8 category, action;
	पूर्णांक type = (-1);
	काष्ठा adapter *padapter;
	काष्ठा rtw_wdev_priv *pwdev_priv;

	अगर (ndev == शून्य) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	padapter = rtw_netdev_priv(ndev);
	pwdev_priv = adapter_wdev_data(padapter);

	/* cookie generation */
	*cookie = (अचिन्हित दीर्घ) buf;

	/* indicate ack beक्रमe issue frame to aव्योम racing with rsp frame */
	rtw_cfg80211_mgmt_tx_status(padapter, *cookie, buf, len, ack, GFP_KERNEL);

	अगर (rtw_action_frame_parse(buf, len, &category, &action) == false)
		जाओ निकास;

	rtw_ps_deny(padapter, PS_DENY_MGNT_TX);
	अगर (_FAIL == rtw_pwr_wakeup(padapter)) अणु
		ret = -EFAULT;
		जाओ cancel_ps_deny;
	पूर्ण

	करो अणु
		dump_cnt++;
		tx_ret = _cfg80211_rtw_mgmt_tx(padapter, tx_ch, buf, len);
	पूर्ण जबतक (dump_cnt < dump_limit && tx_ret != _SUCCESS);

	चयन (type) अणु
	हाल P2P_GO_NEGO_CONF:
		rtw_clear_scan_deny(padapter);
		अवरोध;
	हाल P2P_INVIT_RESP:
		अगर (pwdev_priv->invit_info.flags & BIT(0) && pwdev_priv->invit_info.status == 0) अणु
			rtw_set_scan_deny(padapter, 5000);
			rtw_pwr_wakeup_ex(padapter, 5000);
			rtw_clear_scan_deny(padapter);
		पूर्ण
		अवरोध;
	पूर्ण

cancel_ps_deny:
	rtw_ps_deny_cancel(padapter, PS_DENY_MGNT_TX);
निकास:
	वापस ret;
पूर्ण

अटल व्योम rtw_cfg80211_init_ht_capab(काष्ठा ieee80211_sta_ht_cap *ht_cap, क्रमागत nl80211_band band, u8 rf_type)
अणु

#घोषणा MAX_BIT_RATE_40MHZ_MCS15	300	/* Mbps */
#घोषणा MAX_BIT_RATE_40MHZ_MCS7		150	/* Mbps */

	ht_cap->ht_supported = true;

	ht_cap->cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
					IEEE80211_HT_CAP_SGI_40 | IEEE80211_HT_CAP_SGI_20 |
					IEEE80211_HT_CAP_DSSSCCK40 | IEEE80211_HT_CAP_MAX_AMSDU;

	/*
	 *Maximum length of AMPDU that the STA can receive.
	 *Length = 2 ^ (13 + max_ampdu_length_exp) - 1 (octets)
	 */
	ht_cap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;

	/*Minimum MPDU start spacing , */
	ht_cap->ampdu_density = IEEE80211_HT_MPDU_DENSITY_16;

	ht_cap->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;

	/*
	 *hw->wiphy->bands[NL80211_BAND_2GHZ]
	 *base on ant_num
	 *rx_mask: RX mask
	 *अगर rx_ant = 1 rx_mask[0]= 0xff;==>MCS0-MCS7
	 *अगर rx_ant =2 rx_mask[1]= 0xff;==>MCS8-MCS15
	 *अगर rx_ant >=3 rx_mask[2]= 0xff;
	 *अगर BW_40 rx_mask[4]= 0x01;
	 *highest supported RX rate
	 */
	अगर (rf_type == RF_1T1R) अणु
		ht_cap->mcs.rx_mask[0] = 0xFF;
		ht_cap->mcs.rx_mask[1] = 0x00;
		ht_cap->mcs.rx_mask[4] = 0x01;

		ht_cap->mcs.rx_highest = cpu_to_le16(MAX_BIT_RATE_40MHZ_MCS7);
	पूर्ण अन्यथा अगर ((rf_type == RF_1T2R) || (rf_type == RF_2T2R)) अणु
		ht_cap->mcs.rx_mask[0] = 0xFF;
		ht_cap->mcs.rx_mask[1] = 0xFF;
		ht_cap->mcs.rx_mask[4] = 0x01;

		ht_cap->mcs.rx_highest = cpu_to_le16(MAX_BIT_RATE_40MHZ_MCS15);
	पूर्ण
पूर्ण

व्योम rtw_cfg80211_init_wiphy(काष्ठा adapter *padapter)
अणु
	u8 rf_type;
	काष्ठा ieee80211_supported_band *bands;
	काष्ठा wireless_dev *pwdev = padapter->rtw_wdev;
	काष्ठा wiphy *wiphy = pwdev->wiphy;

	rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));

	अणु
		bands = wiphy->bands[NL80211_BAND_2GHZ];
		अगर (bands)
			rtw_cfg80211_init_ht_capab(&bands->ht_cap, NL80211_BAND_2GHZ, rf_type);
	पूर्ण

	/* copy mac_addr to wiphy */
	स_नकल(wiphy->perm_addr, padapter->eeprompriv.mac_addr, ETH_ALEN);

पूर्ण

अटल व्योम rtw_cfg80211_preinit_wiphy(काष्ठा adapter *padapter, काष्ठा wiphy *wiphy)
अणु

	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;

	wiphy->max_scan_ssids = RTW_SSID_SCAN_AMOUNT;
	wiphy->max_scan_ie_len = RTW_SCAN_IE_LEN_MAX;
	wiphy->max_num_pmkids = RTW_MAX_NUM_PMKIDS;

	wiphy->max_reमुख्य_on_channel_duration = RTW_MAX_REMAIN_ON_CHANNEL_DURATION;

	wiphy->पूर्णांकerface_modes =	BIT(NL80211_IFTYPE_STATION)
								| BIT(NL80211_IFTYPE_ADHOC)
								| BIT(NL80211_IFTYPE_AP)
								| BIT(NL80211_IFTYPE_MONITOR)
								;

	wiphy->mgmt_stypes = rtw_cfg80211_शेष_mgmt_stypes;

	wiphy->software_अगरtypes |= BIT(NL80211_IFTYPE_MONITOR);

	wiphy->cipher_suites = rtw_cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(rtw_cipher_suites);

	/* अगर (padapter->registrypriv.wireless_mode & WIRELESS_11G) */
	wiphy->bands[NL80211_BAND_2GHZ] = rtw_spt_band_alloc(NL80211_BAND_2GHZ);

	wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	wiphy->flags |= WIPHY_FLAG_OFFCHAN_TX | WIPHY_FLAG_HAVE_AP_SME;

#अगर defined(CONFIG_PM)
	wiphy->max_sched_scan_reqs = 1;
#पूर्ण_अगर

#अगर defined(CONFIG_PM)
	wiphy->wowlan = &wowlan_stub;
#पूर्ण_अगर

	अगर (padapter->registrypriv.घातer_mgnt != PS_MODE_ACTIVE)
		wiphy->flags |= WIPHY_FLAG_PS_ON_BY_DEFAULT;
	अन्यथा
		wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;
पूर्ण

अटल काष्ठा cfg80211_ops rtw_cfg80211_ops = अणु
	.change_भव_पूर्णांकf = cfg80211_rtw_change_अगरace,
	.add_key = cfg80211_rtw_add_key,
	.get_key = cfg80211_rtw_get_key,
	.del_key = cfg80211_rtw_del_key,
	.set_शेष_key = cfg80211_rtw_set_शेष_key,
	.get_station = cfg80211_rtw_get_station,
	.scan = cfg80211_rtw_scan,
	.set_wiphy_params = cfg80211_rtw_set_wiphy_params,
	.connect = cfg80211_rtw_connect,
	.disconnect = cfg80211_rtw_disconnect,
	.join_ibss = cfg80211_rtw_join_ibss,
	.leave_ibss = cfg80211_rtw_leave_ibss,
	.set_tx_घातer = cfg80211_rtw_set_txघातer,
	.get_tx_घातer = cfg80211_rtw_get_txघातer,
	.set_घातer_mgmt = cfg80211_rtw_set_घातer_mgmt,
	.set_pmksa = cfg80211_rtw_set_pmksa,
	.del_pmksa = cfg80211_rtw_del_pmksa,
	.flush_pmksa = cfg80211_rtw_flush_pmksa,

	.add_भव_पूर्णांकf = cfg80211_rtw_add_भव_पूर्णांकf,
	.del_भव_पूर्णांकf = cfg80211_rtw_del_भव_पूर्णांकf,

	.start_ap = cfg80211_rtw_start_ap,
	.change_beacon = cfg80211_rtw_change_beacon,
	.stop_ap = cfg80211_rtw_stop_ap,

	.add_station = cfg80211_rtw_add_station,
	.del_station = cfg80211_rtw_del_station,
	.change_station = cfg80211_rtw_change_station,
	.dump_station = cfg80211_rtw_dump_station,
	.change_bss = cfg80211_rtw_change_bss,

	.mgmt_tx = cfg80211_rtw_mgmt_tx,
पूर्ण;

पूर्णांक rtw_wdev_alloc(काष्ठा adapter *padapter, काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा wiphy *wiphy;
	काष्ठा wireless_dev *wdev;
	काष्ठा rtw_wdev_priv *pwdev_priv;
	काष्ठा net_device *pnetdev = padapter->pnetdev;

	/* wiphy */
	wiphy = wiphy_new(&rtw_cfg80211_ops, माप(काष्ठा adapter *));
	अगर (!wiphy) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण
	set_wiphy_dev(wiphy, dev);
	*((काष्ठा adapter **)wiphy_priv(wiphy)) = padapter;
	rtw_cfg80211_preinit_wiphy(padapter, wiphy);

	/* init regulary करोमुख्य */
	rtw_regd_init(wiphy, rtw_reg_notअगरier);

	ret = wiphy_रेजिस्टर(wiphy);
	अगर (ret < 0)
		जाओ मुक्त_wiphy;

	/*  wdev */
	wdev = rtw_zदो_स्मृति(माप(काष्ठा wireless_dev));
	अगर (!wdev) अणु
		ret = -ENOMEM;
		जाओ unरेजिस्टर_wiphy;
	पूर्ण
	wdev->wiphy = wiphy;
	wdev->netdev = pnetdev;

	wdev->अगरtype = NL80211_IFTYPE_STATION; /*  will be init in rtw_hal_init() */
	                                       /*  Must sync with _rtw_init_mlme_priv() */
					   /*  pmlmepriv->fw_state = WIFI_STATION_STATE */
	padapter->rtw_wdev = wdev;
	pnetdev->ieee80211_ptr = wdev;

	/* init pwdev_priv */
	pwdev_priv = adapter_wdev_data(padapter);
	pwdev_priv->rtw_wdev = wdev;
	pwdev_priv->pmon_ndev = शून्य;
	pwdev_priv->अगरname_mon[0] = '\0';
	pwdev_priv->padapter = padapter;
	pwdev_priv->scan_request = शून्य;
	spin_lock_init(&pwdev_priv->scan_req_lock);

	pwdev_priv->p2p_enabled = false;
	pwdev_priv->provdisc_req_issued = false;
	rtw_wdev_invit_info_init(&pwdev_priv->invit_info);
	rtw_wdev_nego_info_init(&pwdev_priv->nego_info);

	pwdev_priv->bandroid_scan = false;

	अगर (padapter->registrypriv.घातer_mgnt != PS_MODE_ACTIVE)
		pwdev_priv->घातer_mgmt = true;
	अन्यथा
		pwdev_priv->घातer_mgmt = false;

	वापस ret;

unरेजिस्टर_wiphy:
	wiphy_unरेजिस्टर(wiphy);
 मुक्त_wiphy:
	wiphy_मुक्त(wiphy);
निकास:
	वापस ret;

पूर्ण

व्योम rtw_wdev_मुक्त(काष्ठा wireless_dev *wdev)
अणु
	अगर (!wdev)
		वापस;

	kमुक्त(wdev->wiphy->bands[NL80211_BAND_2GHZ]);

	wiphy_मुक्त(wdev->wiphy);

	kमुक्त(wdev);
पूर्ण

व्योम rtw_wdev_unरेजिस्टर(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा net_device *ndev;
	काष्ठा adapter *adapter;
	काष्ठा rtw_wdev_priv *pwdev_priv;

	अगर (!wdev)
		वापस;
	ndev = wdev_to_ndev(wdev);
	अगर (!ndev)
		वापस;

	adapter = rtw_netdev_priv(ndev);
	pwdev_priv = adapter_wdev_data(adapter);

	rtw_cfg80211_indicate_scan_करोne(adapter, true);

	अगर (pwdev_priv->pmon_ndev)
		unरेजिस्टर_netdev(pwdev_priv->pmon_ndev);

	wiphy_unरेजिस्टर(wdev->wiphy);
पूर्ण
