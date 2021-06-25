<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __IEEE80211_H
#घोषणा __IEEE80211_H

#समावेश <linux/ieee80211.h>

#घोषणा IEEE_CMD_SET_WPA_PARAM			1
#घोषणा IEEE_CMD_SET_WPA_IE			2
#घोषणा IEEE_CMD_SET_ENCRYPTION			3
#घोषणा IEEE_CMD_MLME				4

#घोषणा IEEE_PARAM_WPA_ENABLED			1
#घोषणा IEEE_PARAM_TKIP_COUNTERMEASURES		2
#घोषणा IEEE_PARAM_DROP_UNENCRYPTED		3
#घोषणा IEEE_PARAM_PRIVACY_INVOKED		4
#घोषणा IEEE_PARAM_AUTH_ALGS			5
#घोषणा IEEE_PARAM_IEEE_802_1X			6
#घोषणा IEEE_PARAM_WPAX_SELECT			7

#घोषणा AUTH_ALG_OPEN_SYSTEM			0x1
#घोषणा AUTH_ALG_SHARED_KEY			0x2
#घोषणा AUTH_ALG_LEAP				0x00000004

#घोषणा IEEE_MLME_STA_DEAUTH			1
#घोषणा IEEE_MLME_STA_DISASSOC			2

#घोषणा IEEE_CRYPT_ERR_UNKNOWN_ALG		2
#घोषणा IEEE_CRYPT_ERR_UNKNOWN_ADDR		3
#घोषणा IEEE_CRYPT_ERR_CRYPT_INIT_FAILED	4
#घोषणा IEEE_CRYPT_ERR_KEY_SET_FAILED		5
#घोषणा IEEE_CRYPT_ERR_TX_KEY_SET_FAILED	6
#घोषणा IEEE_CRYPT_ERR_CARD_CONF_FAILED		7

#घोषणा	IEEE_CRYPT_ALG_NAME_LEN			16

#घोषणा WPA_CIPHER_NONE				BIT(0)
#घोषणा WPA_CIPHER_WEP40			BIT(1)
#घोषणा WPA_CIPHER_WEP104			BIT(2)
#घोषणा WPA_CIPHER_TKIP				BIT(3)
#घोषणा WPA_CIPHER_CCMP				BIT(4)

#घोषणा WPA_SELECTOR_LEN			4
#घोषणा RSN_HEADER_LEN				4

#घोषणा RSN_SELECTOR_LEN 4

क्रमागत NETWORK_TYPE अणु
	WIRELESS_INVALID	= 0,
	WIRELESS_11B		= 1,
	WIRELESS_11G		= 2,
	WIRELESS_11BG		= (WIRELESS_11B | WIRELESS_11G),
	WIRELESS_11A		= 4,
	WIRELESS_11N		= 8,
	WIRELESS_11GN		= (WIRELESS_11G | WIRELESS_11N),
	WIRELESS_11BGN		= (WIRELESS_11B | WIRELESS_11G | WIRELESS_11N),
पूर्ण;

काष्ठा ieee_param अणु
	u32 cmd;
	u8 sta_addr[ETH_ALEN];
	जोड़ अणु
		काष्ठा अणु
			u8 name;
			u32 value;
		पूर्ण wpa_param;
		काष्ठा अणु
			u32 len;
			u8 reserved[32];
			u8 data[0];
		पूर्ण wpa_ie;
		काष्ठा अणु
			पूर्णांक command;
			पूर्णांक reason_code;
		पूर्ण mlme;
		काष्ठा अणु
			u8 alg[IEEE_CRYPT_ALG_NAME_LEN];
			u8 set_tx;
			u32 err;
			u8 idx;
			u8 seq[8]; /* sequence counter (set: RX, get: TX) */
			u16 key_len;
			u8 key[0];
		पूर्ण crypt;
	पूर्ण u;
पूर्ण;

#घोषणा MIN_FRAG_THRESHOLD     256U
#घोषणा	MAX_FRAG_THRESHOLD     2346U

/* QoS,QOS */
#घोषणा NORMAL_ACK			0

/* IEEE 802.11 defines */

#घोषणा P80211_OUI_LEN 3

काष्ठा ieee80211_snap_hdr अणु
	u8    dsap;   /* always 0xAA */
	u8    ssap;   /* always 0xAA */
	u8    ctrl;   /* always 0x03 */
	u8    oui[P80211_OUI_LEN];    /* organizational universal id */
पूर्ण __packed;

#घोषणा SNAP_SIZE माप(काष्ठा ieee80211_snap_hdr)

#घोषणा IEEE80211_CCK_RATE_LEN			4
#घोषणा IEEE80211_NUM_OFDM_RATESLEN	8

#घोषणा IEEE80211_CCK_RATE_1MB		        0x02
#घोषणा IEEE80211_CCK_RATE_2MB		        0x04
#घोषणा IEEE80211_CCK_RATE_5MB		        0x0B
#घोषणा IEEE80211_CCK_RATE_11MB		        0x16
#घोषणा IEEE80211_OFDM_RATE_6MB		        0x0C
#घोषणा IEEE80211_OFDM_RATE_9MB		        0x12
#घोषणा IEEE80211_OFDM_RATE_12MB		0x18
#घोषणा IEEE80211_OFDM_RATE_18MB		0x24
#घोषणा IEEE80211_OFDM_RATE_24MB		0x30
#घोषणा IEEE80211_OFDM_RATE_36MB		0x48
#घोषणा IEEE80211_OFDM_RATE_48MB		0x60
#घोषणा IEEE80211_OFDM_RATE_54MB		0x6C
#घोषणा IEEE80211_BASIC_RATE_MASK		0x80

#घोषणा WEP_KEYS 4

/* MAX_RATES_LENGTH needs to be 12.  The spec says 8, and many APs
 * only use 8, and then use extended rates क्रम the reमुख्यing supported
 * rates.  Other APs, however, stick all of their supported rates on the
 * मुख्य rates inक्रमmation element...
 */
#घोषणा MAX_RATES_LENGTH                  ((u8)12)
#घोषणा MAX_WPA_IE_LEN 128

काष्ठा registry_priv;

u8 *r8712_set_ie(u8 *pbuf, sपूर्णांक index, uपूर्णांक len, u8 *source, uपूर्णांक *frlen);
u8 *r8712_get_ie(u8 *pbuf, sपूर्णांक index, uपूर्णांक *len, sपूर्णांक limit);
अचिन्हित अक्षर *r8712_get_wpa_ie(अचिन्हित अक्षर *pie, uपूर्णांक *rsn_ie_len,
				पूर्णांक limit);
अचिन्हित अक्षर *r8712_get_wpa2_ie(अचिन्हित अक्षर *pie, uपूर्णांक *rsn_ie_len,
				 पूर्णांक limit);
पूर्णांक r8712_parse_wpa_ie(u8 *wpa_ie, पूर्णांक wpa_ie_len, पूर्णांक *group_cipher,
		       पूर्णांक *pairwise_cipher);
पूर्णांक r8712_parse_wpa2_ie(u8 *wpa_ie, पूर्णांक wpa_ie_len, पूर्णांक *group_cipher,
			पूर्णांक *pairwise_cipher);
पूर्णांक r8712_get_sec_ie(u8 *in_ie, uपूर्णांक in_len, u8 *rsn_ie, u16 *rsn_len,
		     u8 *wpa_ie, u16 *wpa_len);
पूर्णांक r8712_get_wps_ie(u8 *in_ie, uपूर्णांक in_len, u8 *wps_ie, uपूर्णांक *wps_ielen);
पूर्णांक r8712_generate_ie(काष्ठा registry_priv *pregistrypriv);
uपूर्णांक r8712_is_cckrates_included(u8 *rate);
uपूर्णांक r8712_is_cckratesonly_included(u8 *rate);

#पूर्ण_अगर /* IEEE80211_H */

