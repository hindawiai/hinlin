<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * ieee80211.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _IEEE80211_C

#समावेश "drv_types.h"
#समावेश "ieee80211.h"
#समावेश "wifi.h"
#समावेश "osdep_service.h"
#समावेश "wlan_bssdef.h"

अटल स्थिर u8 WPA_OUI_TYPE[] = अणु0x00, 0x50, 0xf2, 1पूर्ण;
अटल स्थिर u8 WPA_CIPHER_SUITE_NONE[] = अणु0x00, 0x50, 0xf2, 0पूर्ण;
अटल स्थिर u8 WPA_CIPHER_SUITE_WEP40[] = अणु0x00, 0x50, 0xf2, 1पूर्ण;
अटल स्थिर u8 WPA_CIPHER_SUITE_TKIP[] = अणु0x00, 0x50, 0xf2, 2पूर्ण;
अटल स्थिर u8 WPA_CIPHER_SUITE_CCMP[] = अणु0x00, 0x50, 0xf2, 4पूर्ण;
अटल स्थिर u8 WPA_CIPHER_SUITE_WEP104[] = अणु0x00, 0x50, 0xf2, 5पूर्ण;

अटल स्थिर u8 RSN_CIPHER_SUITE_NONE[] = अणु0x00, 0x0f, 0xac, 0पूर्ण;
अटल स्थिर u8 RSN_CIPHER_SUITE_WEP40[] = अणु0x00, 0x0f, 0xac, 1पूर्ण;
अटल स्थिर u8 RSN_CIPHER_SUITE_TKIP[] = अणु0x00, 0x0f, 0xac, 2पूर्ण;
अटल स्थिर u8 RSN_CIPHER_SUITE_CCMP[] = अणु0x00, 0x0f, 0xac, 4पूर्ण;
अटल स्थिर u8 RSN_CIPHER_SUITE_WEP104[] = अणु0x00, 0x0f, 0xac, 5पूर्ण;

/*-----------------------------------------------------------
 * क्रम adhoc-master to generate ie and provide supported-rate to fw
 *-----------------------------------------------------------
 */

अटल u8 WIFI_CCKRATES[] =  अणु
	(IEEE80211_CCK_RATE_1MB | IEEE80211_BASIC_RATE_MASK),
	(IEEE80211_CCK_RATE_2MB | IEEE80211_BASIC_RATE_MASK),
	(IEEE80211_CCK_RATE_5MB | IEEE80211_BASIC_RATE_MASK),
	(IEEE80211_CCK_RATE_11MB | IEEE80211_BASIC_RATE_MASK)
पूर्ण;

अटल u8 WIFI_OFDMRATES[] = अणु
	(IEEE80211_OFDM_RATE_6MB),
	(IEEE80211_OFDM_RATE_9MB),
	(IEEE80211_OFDM_RATE_12MB),
	(IEEE80211_OFDM_RATE_18MB),
	(IEEE80211_OFDM_RATE_24MB),
	(IEEE80211_OFDM_RATE_36MB),
	(IEEE80211_OFDM_RATE_48MB),
	(IEEE80211_OFDM_RATE_54MB)
पूर्ण;

uपूर्णांक r8712_is_cckrates_included(u8 *rate)
अणु
	u32 i = 0;

	जबतक (rate[i] != 0) अणु
		अगर ((((rate[i]) & 0x7f) == 2) || (((rate[i]) & 0x7f) == 4) ||
		    (((rate[i]) & 0x7f) == 11) || (((rate[i]) & 0x7f) == 22))
			वापस true;
		i++;
	पूर्ण
	वापस false;
पूर्ण

uपूर्णांक r8712_is_cckratesonly_included(u8 *rate)
अणु
	u32 i = 0;

	जबतक (rate[i] != 0) अणु
		अगर ((((rate[i]) & 0x7f) != 2) && (((rate[i]) & 0x7f) != 4) &&
		    (((rate[i]) & 0x7f) != 11)  && (((rate[i]) & 0x7f) != 22))
			वापस false;
		i++;
	पूर्ण
	वापस true;
पूर्ण

/* r8712_set_ie will update frame length */
u8 *r8712_set_ie(u8 *pbuf, sपूर्णांक index, uपूर्णांक len, u8 *source, uपूर्णांक *frlen)
अणु
	*pbuf = (u8)index;
	*(pbuf + 1) = (u8)len;
	अगर (len > 0)
		स_नकल((व्योम *)(pbuf + 2), (व्योम *)source, len);
	*frlen = *frlen + (len + 2);
	वापस pbuf + len + 2;
पूर्ण

/* ---------------------------------------------------------------------------
 * index: the inक्रमmation element id index, limit is the limit क्रम search
 * ---------------------------------------------------------------------------
 */
u8 *r8712_get_ie(u8 *pbuf, sपूर्णांक index, uपूर्णांक *len, sपूर्णांक limit)
अणु
	sपूर्णांक पंचांगp, i;
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

अटल व्योम set_supported_rate(u8 *rates, uपूर्णांक mode)
अणु
	स_रखो(rates, 0, NDIS_802_11_LENGTH_RATES_EX);
	चयन (mode) अणु
	हाल WIRELESS_11B:
		स_नकल(rates, WIFI_CCKRATES, IEEE80211_CCK_RATE_LEN);
		अवरोध;
	हाल WIRELESS_11G:
	हाल WIRELESS_11A:
		स_नकल(rates, WIFI_OFDMRATES, IEEE80211_NUM_OFDM_RATESLEN);
		अवरोध;
	हाल WIRELESS_11BG:
		स_नकल(rates, WIFI_CCKRATES, IEEE80211_CCK_RATE_LEN);
		स_नकल(rates + IEEE80211_CCK_RATE_LEN, WIFI_OFDMRATES,
		       IEEE80211_NUM_OFDM_RATESLEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल uपूर्णांक r8712_get_rateset_len(u8 *rateset)
अणु
	uपूर्णांक i = 0;

	जबतक (1) अणु
		अगर ((rateset[i]) == 0)
			अवरोध;
		अगर (i > 12)
			अवरोध;
		i++;
	पूर्ण
	वापस i;
पूर्ण

पूर्णांक r8712_generate_ie(काष्ठा registry_priv *registrypriv)
अणु
	पूर्णांक rate_len;
	uपूर्णांक sz = 0;
	काष्ठा wlan_bssid_ex *dev_network = &registrypriv->dev_network;
	u8 *ie = dev_network->IEs;
	u16 beaconPeriod = (u16)dev_network->Configuration.BeaconPeriod;

	/*बारtamp will be inserted by hardware*/
	sz += 8;
	ie += sz;
	/*beacon पूर्णांकerval : 2bytes*/
	*(__le16 *)ie = cpu_to_le16(beaconPeriod);
	sz += 2;
	ie += 2;
	/*capability info*/
	*(u16 *)ie = 0;
	*(__le16 *)ie |= cpu_to_le16(WLAN_CAPABILITY_IBSS);
	अगर (registrypriv->preamble == PREAMBLE_SHORT)
		*(__le16 *)ie |= cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE);
	अगर (dev_network->Privacy)
		*(__le16 *)ie |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);
	sz += 2;
	ie += 2;
	/*SSID*/
	ie = r8712_set_ie(ie, WLAN_EID_SSID, dev_network->Ssid.SsidLength,
			  dev_network->Ssid.Ssid, &sz);
	/*supported rates*/
	set_supported_rate(dev_network->rates, registrypriv->wireless_mode);
	rate_len = r8712_get_rateset_len(dev_network->rates);
	अगर (rate_len > 8) अणु
		ie = r8712_set_ie(ie, WLAN_EID_SUPP_RATES, 8,
				  dev_network->rates, &sz);
		ie = r8712_set_ie(ie, WLAN_EID_EXT_SUPP_RATES, (rate_len - 8),
				  (dev_network->rates + 8), &sz);
	पूर्ण अन्यथा अणु
		ie = r8712_set_ie(ie, WLAN_EID_SUPP_RATES,
				  rate_len, dev_network->rates, &sz);
	पूर्ण
	/*DS parameter set*/
	ie = r8712_set_ie(ie, WLAN_EID_DS_PARAMS, 1,
			  (u8 *)&dev_network->Configuration.DSConfig, &sz);
	/*IBSS Parameter Set*/
	ie = r8712_set_ie(ie, WLAN_EID_IBSS_PARAMS, 2,
			  (u8 *)&dev_network->Configuration.ATIMWinकरोw, &sz);
	वापस sz;
पूर्ण

अचिन्हित अक्षर *r8712_get_wpa_ie(अचिन्हित अक्षर *ie, uपूर्णांक *wpa_ie_len, पूर्णांक limit)
अणु
	u32 len;
	u16 val16;
	अचिन्हित अक्षर wpa_oui_type[] = अणु0x00, 0x50, 0xf2, 0x01पूर्ण;
	u8 *buf = ie;

	जबतक (1) अणु
		buf = r8712_get_ie(buf, _WPA_IE_ID_, &len, limit);
		अगर (buf) अणु
			/*check अगर oui matches...*/
			अगर (स_भेद((buf + 2), wpa_oui_type,
				   माप(wpa_oui_type)))
				जाओ check_next_ie;
			/*check version...*/
			स_नकल((u8 *)&val16, (buf + 6), माप(val16));
			le16_to_cpus(&val16);
			अगर (val16 != 0x0001)
				जाओ check_next_ie;
			*wpa_ie_len = *(buf + 1);
			वापस buf;
		पूर्ण
		*wpa_ie_len = 0;
		वापस शून्य;
check_next_ie:
		limit = limit - (buf - ie) - 2 - len;
		अगर (limit <= 0)
			अवरोध;
		buf += (2 + len);
	पूर्ण
	*wpa_ie_len = 0;
	वापस शून्य;
पूर्ण

अचिन्हित अक्षर *r8712_get_wpa2_ie(अचिन्हित अक्षर *pie, uपूर्णांक *rsn_ie_len,
				 पूर्णांक limit)
अणु
	वापस r8712_get_ie(pie, _WPA2_IE_ID_, rsn_ie_len, limit);
पूर्ण

अटल पूर्णांक r8712_get_wpa_cipher_suite(u8 *s)
अणु
	अगर (!स_भेद(s, (व्योम *)WPA_CIPHER_SUITE_NONE, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_NONE;
	अगर (!स_भेद(s, (व्योम *)WPA_CIPHER_SUITE_WEP40, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_WEP40;
	अगर (!स_भेद(s, (व्योम *)WPA_CIPHER_SUITE_TKIP, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_TKIP;
	अगर (!स_भेद(s, (व्योम *)WPA_CIPHER_SUITE_CCMP, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_CCMP;
	अगर (!स_भेद(s, (व्योम *)WPA_CIPHER_SUITE_WEP104, WPA_SELECTOR_LEN))
		वापस WPA_CIPHER_WEP104;
	वापस 0;
पूर्ण

अटल पूर्णांक r8712_get_wpa2_cipher_suite(u8 *s)
अणु
	अगर (!स_भेद(s, (व्योम *)RSN_CIPHER_SUITE_NONE, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_NONE;
	अगर (!स_भेद(s, (व्योम *)RSN_CIPHER_SUITE_WEP40, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_WEP40;
	अगर (!स_भेद(s, (व्योम *)RSN_CIPHER_SUITE_TKIP, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_TKIP;
	अगर (!स_भेद(s, (व्योम *)RSN_CIPHER_SUITE_CCMP, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_CCMP;
	अगर (!स_भेद(s, (व्योम *)RSN_CIPHER_SUITE_WEP104, RSN_SELECTOR_LEN))
		वापस WPA_CIPHER_WEP104;
	वापस 0;
पूर्ण

पूर्णांक r8712_parse_wpa_ie(u8 *wpa_ie, पूर्णांक wpa_ie_len, पूर्णांक *group_cipher,
		       पूर्णांक *pairwise_cipher)
अणु
	पूर्णांक i;
	पूर्णांक left, count;
	u8 *pos;

	अगर (wpa_ie_len <= 0) अणु
		/* No WPA IE - fail silently */
		वापस -EINVAL;
	पूर्ण
	अगर ((*wpa_ie != _WPA_IE_ID_) ||
	    (*(wpa_ie + 1) != (u8)(wpa_ie_len - 2)) ||
	    (स_भेद(wpa_ie + 2, (व्योम *)WPA_OUI_TYPE, WPA_SELECTOR_LEN)))
		वापस -EINVAL;
	pos = wpa_ie;
	pos += 8;
	left = wpa_ie_len - 8;
	/*group_cipher*/
	अगर (left >= WPA_SELECTOR_LEN) अणु
		*group_cipher = r8712_get_wpa_cipher_suite(pos);
		pos += WPA_SELECTOR_LEN;
		left -= WPA_SELECTOR_LEN;
	पूर्ण अन्यथा अगर (left > 0) अणु
		वापस -EINVAL;
	पूर्ण
	/*pairwise_cipher*/
	अगर (left >= 2) अणु
		count = le16_to_cpu(*(__le16 *)pos);
		pos += 2;
		left -= 2;
		अगर (count == 0 || left < count * WPA_SELECTOR_LEN)
			वापस -EINVAL;
		क्रम (i = 0; i < count; i++) अणु
			*pairwise_cipher |= r8712_get_wpa_cipher_suite(pos);
			pos += WPA_SELECTOR_LEN;
			left -= WPA_SELECTOR_LEN;
		पूर्ण
	पूर्ण अन्यथा अगर (left == 1) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक r8712_parse_wpa2_ie(u8 *rsn_ie, पूर्णांक rsn_ie_len, पूर्णांक *group_cipher,
			पूर्णांक *pairwise_cipher)
अणु
	पूर्णांक i;
	पूर्णांक left, count;
	u8 *pos;

	अगर (rsn_ie_len <= 0) अणु
		/* No RSN IE - fail silently */
		वापस -EINVAL;
	पूर्ण
	अगर ((*rsn_ie != _WPA2_IE_ID_) ||
	    (*(rsn_ie + 1) != (u8)(rsn_ie_len - 2)))
		वापस -EINVAL;
	pos = rsn_ie;
	pos += 4;
	left = rsn_ie_len - 4;
	/*group_cipher*/
	अगर (left >= RSN_SELECTOR_LEN) अणु
		*group_cipher = r8712_get_wpa2_cipher_suite(pos);
		pos += RSN_SELECTOR_LEN;
		left -= RSN_SELECTOR_LEN;
	पूर्ण अन्यथा अगर (left > 0) अणु
		वापस -EINVAL;
	पूर्ण
	/*pairwise_cipher*/
	अगर (left >= 2) अणु
		count = le16_to_cpu(*(__le16 *)pos);
		pos += 2;
		left -= 2;
		अगर (count == 0 || left < count * RSN_SELECTOR_LEN)
			वापस -EINVAL;
		क्रम (i = 0; i < count; i++) अणु
			*pairwise_cipher |= r8712_get_wpa2_cipher_suite(pos);
			pos += RSN_SELECTOR_LEN;
			left -= RSN_SELECTOR_LEN;
		पूर्ण
	पूर्ण अन्यथा अगर (left == 1) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक r8712_get_sec_ie(u8 *in_ie, uपूर्णांक in_len, u8 *rsn_ie, u16 *rsn_len,
		     u8 *wpa_ie, u16 *wpa_len)
अणु
	u8 authmode;
	u8 wpa_oui[4] = अणु0x0, 0x50, 0xf2, 0x01पूर्ण;
	uपूर्णांक cnt;

	/*Search required WPA or WPA2 IE and copy to sec_ie[ ]*/
	cnt = _TIMESTAMP_ + _BEACON_ITERVAL_ + _CAPABILITY_;
	जबतक (cnt < in_len) अणु
		authmode = in_ie[cnt];
		अगर ((authmode == _WPA_IE_ID_) &&
		    (!स_भेद(&in_ie[cnt + 2], &wpa_oui[0], 4))) अणु
			स_नकल(wpa_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);
			*wpa_len = in_ie[cnt + 1] + 2;
			cnt += in_ie[cnt + 1] + 2;  /*get next */
		पूर्ण अन्यथा अणु
			अगर (authmode == _WPA2_IE_ID_) अणु
				स_नकल(rsn_ie, &in_ie[cnt],
				       in_ie[cnt + 1] + 2);
				*rsn_len = in_ie[cnt + 1] + 2;
				cnt += in_ie[cnt + 1] + 2;  /*get next*/
			पूर्ण अन्यथा अणु
				cnt += in_ie[cnt + 1] + 2;   /*get next*/
			पूर्ण
		पूर्ण
	पूर्ण
	वापस *rsn_len + *wpa_len;
पूर्ण

पूर्णांक r8712_get_wps_ie(u8 *in_ie, uपूर्णांक in_len, u8 *wps_ie, uपूर्णांक *wps_ielen)
अणु
	पूर्णांक match;
	uपूर्णांक cnt;
	u8 eid, wps_oui[4] = अणु0x0, 0x50, 0xf2, 0x04पूर्ण;

	cnt = 12;
	match = false;
	जबतक (cnt < in_len) अणु
		eid = in_ie[cnt];
		अगर ((eid == _WPA_IE_ID_) &&
		    (!स_भेद(&in_ie[cnt + 2], wps_oui, 4))) अणु
			स_नकल(wps_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);
			*wps_ielen = in_ie[cnt + 1] + 2;
			cnt += in_ie[cnt + 1] + 2;
			match = true;
			अवरोध;
		पूर्ण
		cnt += in_ie[cnt + 1] + 2; /* जाओ next */
	पूर्ण
	वापस match;
पूर्ण
