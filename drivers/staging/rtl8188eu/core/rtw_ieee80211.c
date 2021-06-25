<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _IEEE80211_C

#समावेश <linux/ieee80211.h>

#समावेश <drv_types.h>
#समावेश <osdep_पूर्णांकf.h>
#समावेश <ieee80211.h>
#समावेश <wअगरi.h>
#समावेश <osdep_service.h>
#समावेश <wlan_bssdef.h>

u8 RTW_WPA_OUI_TYPE[] = अणु 0x00, 0x50, 0xf2, 1 पूर्ण;
u8 WPA_AUTH_KEY_MGMT_NONE[] = अणु 0x00, 0x50, 0xf2, 0 पूर्ण;
u8 WPA_AUTH_KEY_MGMT_UNSPEC_802_1X[] = अणु 0x00, 0x50, 0xf2, 1 पूर्ण;
u8 WPA_AUTH_KEY_MGMT_PSK_OVER_802_1X[] = अणु 0x00, 0x50, 0xf2, 2 पूर्ण;
u8 WPA_CIPHER_SUITE_NONE[] = अणु 0x00, 0x50, 0xf2, 0 पूर्ण;
u8 WPA_CIPHER_SUITE_WEP40[] = अणु 0x00, 0x50, 0xf2, 1 पूर्ण;
u8 WPA_CIPHER_SUITE_TKIP[] = अणु 0x00, 0x50, 0xf2, 2 पूर्ण;
u8 WPA_CIPHER_SUITE_WRAP[] = अणु 0x00, 0x50, 0xf2, 3 पूर्ण;
u8 WPA_CIPHER_SUITE_CCMP[] = अणु 0x00, 0x50, 0xf2, 4 पूर्ण;
u8 WPA_CIPHER_SUITE_WEP104[] = अणु 0x00, 0x50, 0xf2, 5 पूर्ण;

u16 RSN_VERSION_BSD = 1;
u8 RSN_AUTH_KEY_MGMT_UNSPEC_802_1X[] = अणु 0x00, 0x0f, 0xac, 1 पूर्ण;
u8 RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X[] = अणु 0x00, 0x0f, 0xac, 2 पूर्ण;
u8 RSN_CIPHER_SUITE_NONE[] = अणु 0x00, 0x0f, 0xac, 0 पूर्ण;
u8 RSN_CIPHER_SUITE_WEP40[] = अणु 0x00, 0x0f, 0xac, 1 पूर्ण;
u8 RSN_CIPHER_SUITE_TKIP[] = अणु 0x00, 0x0f, 0xac, 2 पूर्ण;
u8 RSN_CIPHER_SUITE_WRAP[] = अणु 0x00, 0x0f, 0xac, 3 पूर्ण;
u8 RSN_CIPHER_SUITE_CCMP[] = अणु 0x00, 0x0f, 0xac, 4 पूर्ण;
u8 RSN_CIPHER_SUITE_WEP104[] = अणु 0x00, 0x0f, 0xac, 5 पूर्ण;
/*  */
/*  क्रम adhoc-master to generate ie and provide supported-rate to fw */
/*  */

अटल u8 WIFI_CCKRATES[] = अणु
	IEEE80211_CCK_RATE_1MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_2MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_5MB | IEEE80211_BASIC_RATE_MASK,
	IEEE80211_CCK_RATE_11MB | IEEE80211_BASIC_RATE_MASK
पूर्ण;

अटल u8 WIFI_OFDMRATES[] = अणु
	 IEEE80211_OFDM_RATE_6MB,
	 IEEE80211_OFDM_RATE_9MB,
	 IEEE80211_OFDM_RATE_12MB,
	 IEEE80211_OFDM_RATE_18MB,
	 IEEE80211_OFDM_RATE_24MB,
	 IEEE80211_OFDM_RATE_36MB,
	 IEEE80211_OFDM_RATE_48MB,
	 IEEE80211_OFDM_RATE_54MB
पूर्ण;

पूर्णांक rtw_get_bit_value_from_ieee_value(u8 val)
अणु
	अटल स्थिर अचिन्हित अक्षर करोt11_rate_table[] = अणु
		2, 4, 11, 22, 12, 18, 24, 36, 48,
		72, 96, 108, 0पूर्ण; /*  last element must be zero!! */
	पूर्णांक i = 0;

	जबतक (करोt11_rate_table[i] != 0) अणु
		अगर (करोt11_rate_table[i] == val)
			वापस BIT(i);
		i++;
	पूर्ण
	वापस 0;
पूर्ण

bool rtw_is_cckrates_included(u8 *rate)
अणु
	जबतक (*rate) अणु
		u8 r = *rate & 0x7f;

		अगर (r == 2 || r == 4 || r == 11 || r == 22)
			वापस true;
		rate++;
	पूर्ण

	वापस false;
पूर्ण

bool rtw_is_cckratesonly_included(u8 *rate)
अणु
	जबतक (*rate) अणु
		u8 r = *rate & 0x7f;

		अगर (r != 2 && r != 4 && r != 11 && r != 22)
			वापस false;
		rate++;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक rtw_check_network_type(अचिन्हित अक्षर *rate)
अणु
	/*  could be pure B, pure G, or B/G */
	अगर (rtw_is_cckratesonly_included(rate))
		वापस WIRELESS_11B;
	अन्यथा अगर (rtw_is_cckrates_included(rate))
		वापस	WIRELESS_11BG;
	अन्यथा
		वापस WIRELESS_11G;
पूर्ण

u8 *rtw_set_fixed_ie(व्योम *pbuf, अचिन्हित पूर्णांक len, व्योम *source,
		     अचिन्हित पूर्णांक *frlen)
अणु
	स_नकल(pbuf, source, len);
	*frlen = *frlen + len;
	वापस ((u8 *)pbuf) + len;
पूर्ण

/*  rtw_set_ie will update frame length */
u8 *rtw_set_ie
(
	u8 *pbuf,
	पूर्णांक index,
	uपूर्णांक len,
	u8 *source,
	uपूर्णांक *frlen /* frame length */
)
अणु
	*pbuf = (u8)index;

	*(pbuf + 1) = (u8)len;

	अगर (len > 0)
		स_नकल((व्योम *)(pbuf + 2), (व्योम *)source, len);

	*frlen = *frlen + (len + 2);

	वापस pbuf + len + 2;
पूर्ण

/*
 * ----------------------------------------------------------------------------
 * index: the inक्रमmation element id index, limit is the limit क्रम search
 * ----------------------------------------------------------------------------
 */
u8 *rtw_get_ie(u8 *pbuf, पूर्णांक index, uपूर्णांक *len, पूर्णांक limit)
अणु
	पूर्णांक पंचांगp, i;
	u8 *p;

	अगर (limit < 1)
		वापस शून्य;

	p = pbuf;
	i = 0;
	*len = 0;
	जबतक (1) अणु
		अगर (*p == index) अणु
			*len = *(p + 1);
			वापस p;
		पूर्ण
		पंचांगp = *(p + 1);
		p += (पंचांगp + 2);
		i += (पंचांगp + 2);
		अगर (i >= limit)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम rtw_set_supported_rate(u8 *SupportedRates, uपूर्णांक mode)
अणु
	स_रखो(SupportedRates, 0, NDIS_802_11_LENGTH_RATES_EX);

	चयन (mode) अणु
	हाल WIRELESS_11B:
		स_नकल(SupportedRates, WIFI_CCKRATES, IEEE80211_CCK_RATE_LEN);
		अवरोध;
	हाल WIRELESS_11G:
	हाल WIRELESS_11A:
	हाल WIRELESS_11_5N:
	हाल WIRELESS_11A_5N:/* Toकरो: no basic rate क्रम ofdm ? */
		स_नकल(SupportedRates, WIFI_OFDMRATES, IEEE80211_NUM_OFDM_RATESLEN);
		अवरोध;
	हाल WIRELESS_11BG:
	हाल WIRELESS_11G_24N:
	हाल WIRELESS_11_24N:
	हाल WIRELESS_11BG_24N:
		स_नकल(SupportedRates, WIFI_CCKRATES, IEEE80211_CCK_RATE_LEN);
		स_नकल(SupportedRates + IEEE80211_CCK_RATE_LEN, WIFI_OFDMRATES, IEEE80211_NUM_OFDM_RATESLEN);
		अवरोध;
	पूर्ण
पूर्ण

uपूर्णांक rtw_get_rateset_len(u8 *rateset)
अणु
	uपूर्णांक i;

	क्रम (i = 0; i < 13; i++)
		अगर (rateset[i] == 0)
			अवरोध;
	वापस i;
पूर्ण

पूर्णांक rtw_generate_ie(काष्ठा registry_priv *pregistrypriv)
अणु
	u8 wireless_mode;
	पूर्णांक rateLen;
	uपूर्णांक sz = 0;
	काष्ठा wlan_bssid_ex *pdev_network = &pregistrypriv->dev_network;
	u8 *ie = pdev_network->ies;

	/* बारtamp will be inserted by hardware */
	sz += 8;
	ie += sz;

	/* beacon पूर्णांकerval : 2bytes */
	*(__le16 *)ie = cpu_to_le16((u16)pdev_network->Configuration.BeaconPeriod);/* BCN_INTERVAL; */
	sz += 2;
	ie += 2;

	/* capability info */
	*(u16 *)ie = 0;

	*(__le16 *)ie |= cpu_to_le16(WLAN_CAPABILITY_IBSS);

	अगर (pregistrypriv->preamble == PREAMBLE_SHORT)
		*(__le16 *)ie |= cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE);

	अगर (pdev_network->Privacy)
		*(__le16 *)ie |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);

	sz += 2;
	ie += 2;

	/* SSID */
	ie = rtw_set_ie(ie, WLAN_EID_SSID, pdev_network->ssid.ssid_length, pdev_network->ssid.ssid, &sz);

	/* supported rates */
	अगर (pregistrypriv->wireless_mode == WIRELESS_11ABGN)
		wireless_mode = WIRELESS_11BG_24N;
	अन्यथा
		wireless_mode = pregistrypriv->wireless_mode;

	rtw_set_supported_rate(pdev_network->SupportedRates, wireless_mode);

	rateLen = rtw_get_rateset_len(pdev_network->SupportedRates);

	अगर (rateLen > 8) अणु
		ie = rtw_set_ie(ie, WLAN_EID_SUPP_RATES, 8, pdev_network->SupportedRates, &sz);
		/* ie = rtw_set_ie(ie, WLAN_EID_EXT_SUPP_RATES, (rateLen - 8), (pdev_network->SupportedRates + 8), &sz); */
	पूर्ण अन्यथा अणु
		ie = rtw_set_ie(ie, WLAN_EID_SUPP_RATES, rateLen, pdev_network->SupportedRates, &sz);
	पूर्ण

	/* DS parameter set */
	ie = rtw_set_ie(ie, WLAN_EID_DS_PARAMS, 1, (u8 *)&pdev_network->Configuration.DSConfig, &sz);

	/* IBSS Parameter Set */

	ie = rtw_set_ie(ie, WLAN_EID_IBSS_PARAMS, 2, (u8 *)&pdev_network->Configuration.ATIMWinकरोw, &sz);

	अगर (rateLen > 8)
		ie = rtw_set_ie(ie, WLAN_EID_EXT_SUPP_RATES, (rateLen - 8), (pdev_network->SupportedRates + 8), &sz);

	वापस sz;
पूर्ण

अचिन्हित अक्षर *rtw_get_wpa_ie(अचिन्हित अक्षर *pie, uपूर्णांक *wpa_ie_len, पूर्णांक limit)
अणु
	uपूर्णांक len;
	u16 val16;
	__le16 le_पंचांगp;
	अटल स्थिर अचिन्हित अक्षर wpa_oui_type[] = अणु0x00, 0x50, 0xf2, 0x01पूर्ण;
	u8 *pbuf = pie;
	पूर्णांक limit_new = limit;

	जबतक (1) अणु
		pbuf = rtw_get_ie(pbuf, WLAN_EID_VENDOR_SPECIFIC, &len, limit_new);

		अगर (pbuf) अणु
			/* check अगर oui matches... */
			अगर (स_भेद((pbuf + 2), wpa_oui_type, माप(wpa_oui_type)))
				जाओ check_next_ie;

			/* check version... */
			स_नकल((u8 *)&le_पंचांगp, (pbuf + 6), माप(val16));

			val16 = le16_to_cpu(le_पंचांगp);
			अगर (val16 != 0x0001)
				जाओ check_next_ie;
			*wpa_ie_len = *(pbuf + 1);
			वापस pbuf;
		पूर्ण
		*wpa_ie_len = 0;
		वापस शून्य;

check_next_ie:
		limit_new = limit - (pbuf - pie) - 2 - len;
		अगर (limit_new <= 0)
			अवरोध;
		pbuf += (2 + len);
	पूर्ण
	*wpa_ie_len = 0;
	वापस शून्य;
पूर्ण

अचिन्हित अक्षर *rtw_get_wpa2_ie(अचिन्हित अक्षर *pie, uपूर्णांक *rsn_ie_len, पूर्णांक limit)
अणु
	वापस rtw_get_ie(pie, WLAN_EID_RSN, rsn_ie_len, limit);
पूर्ण

पूर्णांक rtw_get_wpa_cipher_suite(u8 *s)
अणु
	अगर (!स_भेद(s, WPA_CIPHER_SUITE_NONE, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_NONE;
	अगर (!स_भेद(s, WPA_CIPHER_SUITE_WEP40, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_WEP40;
	अगर (!स_भेद(s, WPA_CIPHER_SUITE_TKIP, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_TKIP;
	अगर (!स_भेद(s, WPA_CIPHER_SUITE_CCMP, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_CCMP;
	अगर (!स_भेद(s, WPA_CIPHER_SUITE_WEP104, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_WEP104;

	वापस 0;
पूर्ण

पूर्णांक rtw_get_wpa2_cipher_suite(u8 *s)
अणु
	अगर (!स_भेद(s, RSN_CIPHER_SUITE_NONE, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_NONE;
	अगर (!स_भेद(s, RSN_CIPHER_SUITE_WEP40, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_WEP40;
	अगर (!स_भेद(s, RSN_CIPHER_SUITE_TKIP, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_TKIP;
	अगर (!स_भेद(s, RSN_CIPHER_SUITE_CCMP, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_CCMP;
	अगर (!स_भेद(s, RSN_CIPHER_SUITE_WEP104, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_WEP104;

	वापस 0;
पूर्ण

पूर्णांक rtw_parse_wpa_ie(u8 *wpa_ie, पूर्णांक wpa_ie_len, पूर्णांक *group_cipher, पूर्णांक *pairwise_cipher, पूर्णांक *is_8021x)
अणु
	पूर्णांक i, ret = _SUCCESS;
	पूर्णांक left, count;
	u8 *pos;
	u8 SUITE_1X[4] = अणु0x00, 0x50, 0xf2, 1पूर्ण;

	अगर (wpa_ie_len <= 0) अणु
		/* No WPA IE - fail silently */
		वापस _FAIL;
	पूर्ण

	अगर ((*wpa_ie != WLAN_EID_VENDOR_SPECIFIC) || (*(wpa_ie + 1) != (u8)(wpa_ie_len - 2)) ||
	    (स_भेद(wpa_ie + 2, RTW_WPA_OUI_TYPE, WPA_SELECTOR_LEN)))
		वापस _FAIL;

	pos = wpa_ie;

	pos += 8;
	left = wpa_ie_len - 8;

	/* group_cipher */
	अगर (left >= WPA_SELECTOR_LEN) अणु
		*group_cipher = rtw_get_wpa_cipher_suite(pos);
		pos += WPA_SELECTOR_LEN;
		left -= WPA_SELECTOR_LEN;
	पूर्ण अन्यथा अगर (left > 0) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("%s: ie length mismatch, %u too much", __func__, left));
		वापस _FAIL;
	पूर्ण

	/* pairwise_cipher */
	अगर (left >= 2) अणु
		count = get_unaligned_le16(pos);
		pos += 2;
		left -= 2;

		अगर (count == 0 || left < count * WPA_SELECTOR_LEN) अणु
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("%s: ie count botch (pairwise), count %u left %u",
						__func__, count, left));
			वापस _FAIL;
		पूर्ण

		क्रम (i = 0; i < count; i++) अणु
			*pairwise_cipher |= rtw_get_wpa_cipher_suite(pos);

			pos += WPA_SELECTOR_LEN;
			left -= WPA_SELECTOR_LEN;
		पूर्ण
	पूर्ण अन्यथा अगर (left == 1) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("%s: ie too short (for key mgmt)",   __func__));
		वापस _FAIL;
	पूर्ण

	अगर (is_8021x) अणु
		अगर (left >= 6) अणु
			pos += 2;
			अगर (!स_भेद(pos, SUITE_1X, 4)) अणु
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s : there has 802.1x auth\n", __func__));
				*is_8021x = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक rtw_parse_wpa2_ie(u8 *rsn_ie, पूर्णांक rsn_ie_len, पूर्णांक *group_cipher, पूर्णांक *pairwise_cipher, पूर्णांक *is_8021x)
अणु
	पूर्णांक i, ret = _SUCCESS;
	पूर्णांक left, count;
	u8 *pos;
	u8 SUITE_1X[4] = अणु0x00, 0x0f, 0xac, 0x01पूर्ण;

	अगर (rsn_ie_len <= 0) अणु
		/* No RSN IE - fail silently */
		वापस _FAIL;
	पूर्ण

	अगर ((*rsn_ie != WLAN_EID_RSN) || (*(rsn_ie + 1) != (u8)(rsn_ie_len - 2)))
		वापस _FAIL;

	pos = rsn_ie;
	pos += 4;
	left = rsn_ie_len - 4;

	/* group_cipher */
	अगर (left >= RSN_SELECTOR_LEN) अणु
		*group_cipher = rtw_get_wpa2_cipher_suite(pos);

		pos += RSN_SELECTOR_LEN;
		left -= RSN_SELECTOR_LEN;

	पूर्ण अन्यथा अगर (left > 0) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("%s: ie length mismatch, %u too much", __func__, left));
		वापस _FAIL;
	पूर्ण

	/* pairwise_cipher */
	अगर (left >= 2) अणु
		count = get_unaligned_le16(pos);
		pos += 2;
		left -= 2;

		अगर (count == 0 || left < count * RSN_SELECTOR_LEN) अणु
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("%s: ie count botch (pairwise), count %u left %u",
						__func__, count, left));
			वापस _FAIL;
		पूर्ण

		क्रम (i = 0; i < count; i++) अणु
			*pairwise_cipher |= rtw_get_wpa2_cipher_suite(pos);

			pos += RSN_SELECTOR_LEN;
			left -= RSN_SELECTOR_LEN;
		पूर्ण

	पूर्ण अन्यथा अगर (left == 1) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("%s: ie too short (for key mgmt)",  __func__));

		वापस _FAIL;
	पूर्ण

	अगर (is_8021x) अणु
		अगर (left >= 6) अणु
			pos += 2;
			अगर (!स_भेद(pos, SUITE_1X, 4)) अणु
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s (): there has 802.1x auth\n", __func__));
				*is_8021x = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम rtw_get_sec_ie(u8 *in_ie, uपूर्णांक in_len, u8 *rsn_ie, u16 *rsn_len, u8 *wpa_ie, u16 *wpa_len)
अणु
	u8 authmode, sec_idx, i;
	u8 wpa_oui[4] = अणु0x0, 0x50, 0xf2, 0x01पूर्ण;
	uपूर्णांक cnt;

	/* Search required WPA or WPA2 IE and copy to sec_ie[] */

	cnt = _TIMESTAMP_ + _BEACON_ITERVAL_ + _CAPABILITY_;

	sec_idx = 0;

	जबतक (cnt < in_len) अणु
		authmode = in_ie[cnt];

		अगर ((authmode == WLAN_EID_VENDOR_SPECIFIC) && (!स_भेद(&in_ie[cnt + 2], &wpa_oui[0], 4))) अणु
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
				 ("\n rtw_get_wpa_ie: sec_idx =%d in_ie[cnt+1]+2 =%d\n",
				 sec_idx, in_ie[cnt + 1] + 2));

			अगर (wpa_ie) अणु
				स_नकल(wpa_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);

				क्रम (i = 0; i < (in_ie[cnt + 1] + 2); i += 8) अणु
					RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
						 ("\n %2x,%2x,%2x,%2x,%2x,%2x,%2x,%2x\n",
						 wpa_ie[i], wpa_ie[i + 1], wpa_ie[i + 2], wpa_ie[i + 3], wpa_ie[i + 4],
						 wpa_ie[i + 5], wpa_ie[i + 6], wpa_ie[i + 7]));
				पूर्ण
			पूर्ण

			*wpa_len = in_ie[cnt + 1] + 2;
			cnt += in_ie[cnt + 1] + 2;  /* get next */
		पूर्ण अन्यथा अणु
			अगर (authmode == WLAN_EID_RSN) अणु
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
					 ("\n get_rsn_ie: sec_idx =%d in_ie[cnt+1]+2 =%d\n",
					 sec_idx, in_ie[cnt + 1] + 2));

				अगर (rsn_ie) अणु
					स_नकल(rsn_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);

					क्रम (i = 0; i < (in_ie[cnt + 1] + 2); i += 8) अणु
						RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
							 ("\n %2x,%2x,%2x,%2x,%2x,%2x,%2x,%2x\n",
							 rsn_ie[i], rsn_ie[i + 1], rsn_ie[i + 2], rsn_ie[i + 3], rsn_ie[i + 4],
							 rsn_ie[i + 5], rsn_ie[i + 6], rsn_ie[i + 7]));
						पूर्ण
				पूर्ण

				*rsn_len = in_ie[cnt + 1] + 2;
				cnt += in_ie[cnt + 1] + 2;  /* get next */
			पूर्ण अन्यथा अणु
				cnt += in_ie[cnt + 1] + 2;   /* get next */
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

u8 rtw_is_wps_ie(u8 *ie_ptr, uपूर्णांक *wps_ielen)
अणु
	u8 match = false;
	u8 eid, wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;

	अगर (!ie_ptr)
		वापस match;

	eid = ie_ptr[0];

	अगर ((eid == WLAN_EID_VENDOR_SPECIFIC) && (!स_भेद(&ie_ptr[2], wps_oui, 4))) अणु
		*wps_ielen = ie_ptr[1] + 2;
		match = true;
	पूर्ण
	वापस match;
पूर्ण

/**
 * rtw_get_wps_ie - Search WPS IE from a series of ies
 * @in_ie: Address of ies to search
 * @in_len: Length limit from in_ie
 * @wps_ie: If not शून्य and WPS IE is found, WPS IE will be copied to the buf starting from wps_ie
 * @wps_ielen: If not शून्य and WPS IE is found, will set to the length of the entire WPS IE
 *
 * Returns: The address of the WPS IE found, or शून्य
 */
u8 *rtw_get_wps_ie(u8 *in_ie, uपूर्णांक in_len, u8 *wps_ie, uपूर्णांक *wps_ielen)
अणु
	uपूर्णांक cnt;
	u8 *wpsie_ptr = शून्य;
	u8 eid, wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;

	अगर (wps_ielen)
		*wps_ielen = 0;

	अगर (!in_ie || in_len <= 0)
		वापस wpsie_ptr;

	cnt = 0;

	जबतक (cnt < in_len) अणु
		eid = in_ie[cnt];

		अगर ((eid == WLAN_EID_VENDOR_SPECIFIC) && (!स_भेद(&in_ie[cnt + 2], wps_oui, 4))) अणु
			wpsie_ptr = &in_ie[cnt];

			अगर (wps_ie)
				स_नकल(wps_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);

			अगर (wps_ielen)
				*wps_ielen = in_ie[cnt + 1] + 2;

			cnt += in_ie[cnt + 1] + 2;

			अवरोध;
		पूर्ण
		cnt += in_ie[cnt + 1] + 2; /* जाओ next */
	पूर्ण
	वापस wpsie_ptr;
पूर्ण

/**
 * rtw_get_wps_attr - Search a specअगरic WPS attribute from a given WPS IE
 * @wps_ie: Address of WPS IE to search
 * @wps_ielen: Length limit from wps_ie
 * @target_attr_id: The attribute ID of WPS attribute to search
 * @buf_attr: If not शून्य and the WPS attribute is found, WPS attribute will be copied to the buf starting from buf_attr
 * @len_attr: If not शून्य and the WPS attribute is found, will set to the length of the entire WPS attribute
 *
 * Returns: the address of the specअगरic WPS attribute found, or शून्य
 */
u8 *rtw_get_wps_attr(u8 *wps_ie, uपूर्णांक wps_ielen, u16 target_attr_id, u8 *buf_attr, u32 *len_attr)
अणु
	u8 *attr_ptr = शून्य;
	u8 *target_attr_ptr = शून्य;
	u8 wps_oui[4] = अणु0x00, 0x50, 0xF2, 0x04पूर्ण;

	अगर (len_attr)
		*len_attr = 0;

	अगर ((wps_ie[0] != WLAN_EID_VENDOR_SPECIFIC) ||
	    (स_भेद(wps_ie + 2, wps_oui, 4)))
		वापस attr_ptr;

	/*  6 = 1(Element ID) + 1(Length) + 4(WPS OUI) */
	attr_ptr = wps_ie + 6; /* जाओ first attr */

	जबतक (attr_ptr - wps_ie < wps_ielen) अणु
		/*  4 = 2(Attribute ID) + 2(Length) */
		u16 attr_id = get_unaligned_be16(attr_ptr);
		u16 attr_data_len = get_unaligned_be16(attr_ptr + 2);
		u16 attr_len = attr_data_len + 4;

		अगर (attr_id == target_attr_id) अणु
			target_attr_ptr = attr_ptr;
			अगर (buf_attr)
				स_नकल(buf_attr, attr_ptr, attr_len);
			अगर (len_attr)
				*len_attr = attr_len;
			अवरोध;
		पूर्ण
		attr_ptr += attr_len; /* जाओ next */
	पूर्ण
	वापस target_attr_ptr;
पूर्ण

/**
 * rtw_get_wps_attr_content - Search a specअगरic WPS attribute content from a given WPS IE
 * @wps_ie: Address of WPS IE to search
 * @wps_ielen: Length limit from wps_ie
 * @target_attr_id: The attribute ID of WPS attribute to search
 * @buf_content: If not शून्य and the WPS attribute is found, WPS attribute content will be copied to the buf starting from buf_content
 * @len_content: If not शून्य and the WPS attribute is found, will set to the length of the WPS attribute content
 *
 * Returns: the address of the specअगरic WPS attribute content found, or शून्य
 */
u8 *rtw_get_wps_attr_content(u8 *wps_ie, uपूर्णांक wps_ielen, u16 target_attr_id, u8 *buf_content, uपूर्णांक *len_content)
अणु
	u8 *attr_ptr;
	u32 attr_len;

	अगर (len_content)
		*len_content = 0;

	attr_ptr = rtw_get_wps_attr(wps_ie, wps_ielen, target_attr_id, शून्य, &attr_len);

	अगर (attr_ptr && attr_len) अणु
		अगर (buf_content)
			स_नकल(buf_content, attr_ptr + 4, attr_len - 4);

		अगर (len_content)
			*len_content = attr_len - 4;

		वापस attr_ptr + 4;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक rtw_ieee802_11_parse_venकरोr_specअगरic(u8 *pos, uपूर्णांक elen,
						काष्ठा rtw_ieee802_11_elems *elems, पूर्णांक show_errors)
अणु
	अचिन्हित पूर्णांक oui;

	/*
	 * first 3 bytes in venकरोr specअगरic inक्रमmation element are the IEEE
	 * OUI of the venकरोr. The following byte is used a venकरोr specअगरic
	 * sub-type.
	 */
	अगर (elen < 4) अणु
		अगर (show_errors) अणु
			DBG_88E("short vendor specific information element ignored (len=%lu)\n",
				(अचिन्हित दीर्घ)elen);
		पूर्ण
		वापस -1;
	पूर्ण

	oui = RTW_GET_BE24(pos);
	चयन (oui) अणु
	हाल OUI_MICROSOFT:
		/*
		 * Microsoft/Wi-Fi inक्रमmation elements are further typed and
		 * subtyped
		 */
		चयन (pos[3]) अणु
		हाल 1:
			/*
			 * Microsoft OUI (00:50:F2) with OUI Type 1:
			 * real WPA inक्रमmation element
			 */
			elems->wpa_ie = pos;
			elems->wpa_ie_len = elen;
			अवरोध;
		हाल WME_OUI_TYPE: /* this is a Wi-Fi WME info. element */
			अगर (elen < 5) अणु
				DBG_88E("short WME information element ignored (len=%lu)\n",
					(अचिन्हित दीर्घ)elen);
				वापस -1;
			पूर्ण
			चयन (pos[4]) अणु
			हाल WME_OUI_SUBTYPE_INFORMATION_ELEMENT:
			हाल WME_OUI_SUBTYPE_PARAMETER_ELEMENT:
				elems->wme = pos;
				elems->wme_len = elen;
				अवरोध;
			हाल WME_OUI_SUBTYPE_TSPEC_ELEMENT:
				elems->wme_tspec = pos;
				elems->wme_tspec_len = elen;
				अवरोध;
			शेष:
				DBG_88E("unknown WME information element ignored (subtype=%d len=%lu)\n",
					pos[4], (अचिन्हित दीर्घ)elen);
				वापस -1;
			पूर्ण
			अवरोध;
		हाल 4:
			/* Wi-Fi Protected Setup (WPS) IE */
			elems->wps_ie = pos;
			elems->wps_ie_len = elen;
			अवरोध;
		शेष:
			DBG_88E("Unknown Microsoft information element ignored (type=%d len=%lu)\n",
				pos[3], (अचिन्हित दीर्घ)elen);
			वापस -1;
		पूर्ण
		अवरोध;

	हाल OUI_BROADCOM:
		चयन (pos[3]) अणु
		हाल VENDOR_HT_CAPAB_OUI_TYPE:
			elems->venकरोr_ht_cap = pos;
			elems->venकरोr_ht_cap_len = elen;
			अवरोध;
		शेष:
			DBG_88E("Unknown Broadcom information element ignored (type=%d len=%lu)\n",
				pos[3], (अचिन्हित दीर्घ)elen);
			वापस -1;
		पूर्ण
		अवरोध;
	शेष:
		DBG_88E("unknown vendor specific information element ignored (vendor OUI %3phC len=%lu)\n",
			pos, (अचिन्हित दीर्घ)elen);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ieee802_11_parse_elems - Parse inक्रमmation elements in management frames
 * @start: Poपूर्णांकer to the start of ies
 * @len: Length of IE buffer in octets
 * @elems: Data काष्ठाure क्रम parsed elements
 * @show_errors: Whether to show parsing errors in debug log
 * Returns: Parsing result
 */
क्रमागत parse_res rtw_ieee802_11_parse_elems(u8 *start, uपूर्णांक len,
					  काष्ठा rtw_ieee802_11_elems *elems,
					  पूर्णांक show_errors)
अणु
	uपूर्णांक left = len;
	u8 *pos = start;
	पूर्णांक unknown = 0;

	स_रखो(elems, 0, माप(*elems));

	जबतक (left >= 2) अणु
		u8 id, elen;

		id = *pos++;
		elen = *pos++;
		left -= 2;

		अगर (elen > left) अणु
			अगर (show_errors) अणु
				DBG_88E("IEEE 802.11 element parse failed (id=%d elen=%d left=%lu)\n",
					id, elen, (अचिन्हित दीर्घ)left);
			पूर्ण
			वापस ParseFailed;
		पूर्ण

		चयन (id) अणु
		हाल WLAN_EID_SSID:
			elems->ssid = pos;
			elems->ssid_len = elen;
			अवरोध;
		हाल WLAN_EID_SUPP_RATES:
			elems->supp_rates = pos;
			elems->supp_rates_len = elen;
			अवरोध;
		हाल WLAN_EID_FH_PARAMS:
			elems->fh_params = pos;
			elems->fh_params_len = elen;
			अवरोध;
		हाल WLAN_EID_DS_PARAMS:
			elems->ds_params = pos;
			elems->ds_params_len = elen;
			अवरोध;
		हाल WLAN_EID_CF_PARAMS:
			elems->cf_params = pos;
			elems->cf_params_len = elen;
			अवरोध;
		हाल WLAN_EID_TIM:
			elems->tim = pos;
			elems->tim_len = elen;
			अवरोध;
		हाल WLAN_EID_IBSS_PARAMS:
			elems->ibss_params = pos;
			elems->ibss_params_len = elen;
			अवरोध;
		हाल WLAN_EID_CHALLENGE:
			elems->challenge = pos;
			elems->challenge_len = elen;
			अवरोध;
		हाल WLAN_EID_ERP_INFO:
			elems->erp_info = pos;
			elems->erp_info_len = elen;
			अवरोध;
		हाल WLAN_EID_EXT_SUPP_RATES:
			elems->ext_supp_rates = pos;
			elems->ext_supp_rates_len = elen;
			अवरोध;
		हाल WLAN_EID_VENDOR_SPECIFIC:
			अगर (rtw_ieee802_11_parse_venकरोr_specअगरic(pos, elen, elems, show_errors))
				unknown++;
			अवरोध;
		हाल WLAN_EID_RSN:
			elems->rsn_ie = pos;
			elems->rsn_ie_len = elen;
			अवरोध;
		हाल WLAN_EID_PWR_CAPABILITY:
			elems->घातer_cap = pos;
			elems->घातer_cap_len = elen;
			अवरोध;
		हाल WLAN_EID_SUPPORTED_CHANNELS:
			elems->supp_channels = pos;
			elems->supp_channels_len = elen;
			अवरोध;
		हाल WLAN_EID_MOBILITY_DOMAIN:
			elems->mdie = pos;
			elems->mdie_len = elen;
			अवरोध;
		हाल WLAN_EID_FAST_BSS_TRANSITION:
			elems->ftie = pos;
			elems->ftie_len = elen;
			अवरोध;
		हाल WLAN_EID_TIMEOUT_INTERVAL:
			elems->समयout_पूर्णांक = pos;
			elems->समयout_पूर्णांक_len = elen;
			अवरोध;
		हाल WLAN_EID_HT_CAPABILITY:
			elems->ht_capabilities = pos;
			elems->ht_capabilities_len = elen;
			अवरोध;
		हाल WLAN_EID_HT_OPERATION:
			elems->ht_operation = pos;
			elems->ht_operation_len = elen;
			अवरोध;
		शेष:
			unknown++;
			अगर (!show_errors)
				अवरोध;
			DBG_88E("IEEE 802.11 element parse ignored unknown element (id=%d elen=%d)\n",
				id, elen);
			अवरोध;
		पूर्ण
		left -= elen;
		pos += elen;
	पूर्ण
	अगर (left)
		वापस ParseFailed;
	वापस unknown ? ParseUnknown : ParseOK;
पूर्ण

व्योम rtw_macaddr_cfg(u8 *mac_addr)
अणु
	u8 mac[ETH_ALEN];

	अगर (!mac_addr)
		वापस;

	अगर (rtw_iniपंचांगac && mac_pton(rtw_iniपंचांगac, mac)) अणु
		/* Users specअगरy the mac address */
		ether_addr_copy(mac_addr, mac);
	पूर्ण अन्यथा अणु
		/* Use the mac address stored in the Efuse */
		ether_addr_copy(mac, mac_addr);
	पूर्ण

	अगर (is_broadcast_ether_addr(mac) || is_zero_ether_addr(mac)) अणु
		eth_अक्रमom_addr(mac_addr);
		DBG_88E("MAC Address from efuse error, assign random one !!!\n");
	पूर्ण

	DBG_88E("%s MAC Address  = %pM\n", __func__, mac_addr);
पूर्ण

अटल पूर्णांक rtw_get_cipher_info(काष्ठा wlan_network *pnetwork)
अणु
	uपूर्णांक wpa_ielen;
	अचिन्हित अक्षर *pbuf;
	पूर्णांक group_cipher = 0, pairwise_cipher = 0, is8021x = 0;
	पूर्णांक ret = _FAIL;

	pbuf = rtw_get_wpa_ie(&pnetwork->network.ies[12], &wpa_ielen, pnetwork->network.ie_length - 12);

	अगर (pbuf && (wpa_ielen > 0)) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s: wpa_ielen: %d", __func__, wpa_ielen));
		अगर (rtw_parse_wpa_ie(pbuf, wpa_ielen + 2, &group_cipher, &pairwise_cipher, &is8021x) == _SUCCESS) अणु
			pnetwork->BcnInfo.pairwise_cipher = pairwise_cipher;
			pnetwork->BcnInfo.group_cipher = group_cipher;
			pnetwork->BcnInfo.is_8021x = is8021x;
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
				 ("%s: pnetwork->pairwise_cipher: %d, is_8021x is %d",
				  __func__, pnetwork->BcnInfo.pairwise_cipher,
				  pnetwork->BcnInfo.is_8021x));
			ret = _SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अणु
		pbuf = rtw_get_wpa2_ie(&pnetwork->network.ies[12], &wpa_ielen, pnetwork->network.ie_length - 12);

		अगर (pbuf && (wpa_ielen > 0)) अणु
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("get RSN IE\n"));
			अगर (rtw_parse_wpa2_ie(pbuf, wpa_ielen + 2, &group_cipher, &pairwise_cipher, &is8021x) == _SUCCESS) अणु
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("get RSN IE  OK!!!\n"));
				pnetwork->BcnInfo.pairwise_cipher = pairwise_cipher;
				pnetwork->BcnInfo.group_cipher = group_cipher;
				pnetwork->BcnInfo.is_8021x = is8021x;
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s: pnetwork->pairwise_cipher: %d, pnetwork->group_cipher is %d, is_8021x is %d",
							__func__, pnetwork->BcnInfo.pairwise_cipher,
							pnetwork->BcnInfo.group_cipher, pnetwork->BcnInfo.is_8021x));
				ret = _SUCCESS;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम rtw_get_bcn_info(काष्ठा wlan_network *pnetwork)
अणु
	अचिन्हित लघु cap = 0;
	u8 bencrypt = 0;
	__le16 le_पंचांगp;
	u16 wpa_len = 0, rsn_len = 0;
	काष्ठा HT_info_element *pht_info = शून्य;
	uपूर्णांक len;
	अचिन्हित अक्षर *p;

	स_नकल(&le_पंचांगp, rtw_get_capability_from_ie(pnetwork->network.ies), 2);
	cap = le16_to_cpu(le_पंचांगp);
	अगर (cap & WLAN_CAPABILITY_PRIVACY) अणु
		bencrypt = 1;
		pnetwork->network.Privacy = 1;
	पूर्ण अन्यथा अणु
		pnetwork->BcnInfo.encryp_protocol = ENCRYP_PROTOCOL_OPENSYS;
	पूर्ण
	rtw_get_sec_ie(pnetwork->network.ies, pnetwork->network.ie_length, शून्य, &rsn_len, शून्य, &wpa_len);
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s: ssid =%s\n", __func__, pnetwork->network.ssid.ssid));
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s: wpa_len =%d rsn_len =%d\n", __func__, wpa_len, rsn_len));
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s: ssid =%s\n", __func__, pnetwork->network.ssid.ssid));
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s: wpa_len =%d rsn_len =%d\n", __func__, wpa_len, rsn_len));

	अगर (rsn_len > 0) अणु
		pnetwork->BcnInfo.encryp_protocol = ENCRYP_PROTOCOL_WPA2;
	पूर्ण अन्यथा अगर (wpa_len > 0) अणु
		pnetwork->BcnInfo.encryp_protocol = ENCRYP_PROTOCOL_WPA;
	पूर्ण अन्यथा अणु
		अगर (bencrypt)
			pnetwork->BcnInfo.encryp_protocol = ENCRYP_PROTOCOL_WEP;
	पूर्ण
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s: pnetwork->encryp_protocol is %x\n",
							__func__, pnetwork->BcnInfo.encryp_protocol));
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("%s: pnetwork->encryp_protocol is %x\n",
							__func__, pnetwork->BcnInfo.encryp_protocol));
	rtw_get_cipher_info(pnetwork);

	/* get bwmode and ch_offset */
	/* parsing HT_CAP_IE */
	p = rtw_get_ie(pnetwork->network.ies + _FIXED_IE_LENGTH_, WLAN_EID_HT_CAPABILITY, &len, pnetwork->network.ie_length - _FIXED_IE_LENGTH_);
	अगर (p && len > 0) अणु
		काष्ठा ieee80211_ht_cap *ht_cap =
			(काष्ठा ieee80211_ht_cap *)(p + 2);

		pnetwork->BcnInfo.ht_cap_info = le16_to_cpu(ht_cap->cap_info);
	पूर्ण अन्यथा अणु
		pnetwork->BcnInfo.ht_cap_info = 0;
	पूर्ण
	/* parsing HT_INFO_IE */
	p = rtw_get_ie(pnetwork->network.ies + _FIXED_IE_LENGTH_, WLAN_EID_HT_OPERATION, &len, pnetwork->network.ie_length - _FIXED_IE_LENGTH_);
	अगर (p && len > 0) अणु
		pht_info = (काष्ठा HT_info_element *)(p + 2);
		pnetwork->BcnInfo.ht_info_infos_0 = pht_info->infos[0];
	पूर्ण अन्यथा अणु
		pnetwork->BcnInfo.ht_info_infos_0 = 0;
	पूर्ण
पूर्ण

/* show MCS rate, unit: 100Kbps */
u16 rtw_mcs_rate(u8 rf_type, u8 bw_40MHz, u8 लघु_GI_20, u8 लघु_GI_40, अचिन्हित अक्षर *MCS_rate)
अणु
	u16 max_rate = 0;

	अगर (rf_type == RF_1T1R) अणु
		अगर (MCS_rate[0] & BIT(7))
			max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 1500 : 1350) : ((लघु_GI_20) ? 722 : 650);
		अन्यथा अगर (MCS_rate[0] & BIT(6))
			max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 1350 : 1215) : ((लघु_GI_20) ? 650 : 585);
		अन्यथा अगर (MCS_rate[0] & BIT(5))
			max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 1200 : 1080) : ((लघु_GI_20) ? 578 : 520);
		अन्यथा अगर (MCS_rate[0] & BIT(4))
			max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 900 : 810) : ((लघु_GI_20) ? 433 : 390);
		अन्यथा अगर (MCS_rate[0] & BIT(3))
			max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 600 : 540) : ((लघु_GI_20) ? 289 : 260);
		अन्यथा अगर (MCS_rate[0] & BIT(2))
			max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 450 : 405) : ((लघु_GI_20) ? 217 : 195);
		अन्यथा अगर (MCS_rate[0] & BIT(1))
			max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 300 : 270) : ((लघु_GI_20) ? 144 : 130);
		अन्यथा अगर (MCS_rate[0] & BIT(0))
			max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 150 : 135) : ((लघु_GI_20) ? 72 : 65);
	पूर्ण अन्यथा अणु
		अगर (MCS_rate[1]) अणु
			अगर (MCS_rate[1] & BIT(7))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 3000 : 2700) : ((लघु_GI_20) ? 1444 : 1300);
			अन्यथा अगर (MCS_rate[1] & BIT(6))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 2700 : 2430) : ((लघु_GI_20) ? 1300 : 1170);
			अन्यथा अगर (MCS_rate[1] & BIT(5))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 2400 : 2160) : ((लघु_GI_20) ? 1156 : 1040);
			अन्यथा अगर (MCS_rate[1] & BIT(4))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 1800 : 1620) : ((लघु_GI_20) ? 867 : 780);
			अन्यथा अगर (MCS_rate[1] & BIT(3))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 1200 : 1080) : ((लघु_GI_20) ? 578 : 520);
			अन्यथा अगर (MCS_rate[1] & BIT(2))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 900 : 810) : ((लघु_GI_20) ? 433 : 390);
			अन्यथा अगर (MCS_rate[1] & BIT(1))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 600 : 540) : ((लघु_GI_20) ? 289 : 260);
			अन्यथा अगर (MCS_rate[1] & BIT(0))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 300 : 270) : ((लघु_GI_20) ? 144 : 130);
		पूर्ण अन्यथा अणु
			अगर (MCS_rate[0] & BIT(7))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 1500 : 1350) : ((लघु_GI_20) ? 722 : 650);
			अन्यथा अगर (MCS_rate[0] & BIT(6))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 1350 : 1215) : ((लघु_GI_20) ? 650 : 585);
			अन्यथा अगर (MCS_rate[0] & BIT(5))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 1200 : 1080) : ((लघु_GI_20) ? 578 : 520);
			अन्यथा अगर (MCS_rate[0] & BIT(4))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 900 : 810) : ((लघु_GI_20) ? 433 : 390);
			अन्यथा अगर (MCS_rate[0] & BIT(3))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 600 : 540) : ((लघु_GI_20) ? 289 : 260);
			अन्यथा अगर (MCS_rate[0] & BIT(2))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 450 : 405) : ((लघु_GI_20) ? 217 : 195);
			अन्यथा अगर (MCS_rate[0] & BIT(1))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 300 : 270) : ((लघु_GI_20) ? 144 : 130);
			अन्यथा अगर (MCS_rate[0] & BIT(0))
				max_rate = (bw_40MHz) ? ((लघु_GI_40) ? 150 : 135) : ((लघु_GI_20) ? 72 : 65);
		पूर्ण
	पूर्ण
	वापस max_rate;
पूर्ण
