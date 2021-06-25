<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __IEEE80211_H
#घोषणा __IEEE80211_H

#समावेश <linux/ieee80211.h>

#घोषणा MGMT_QUEUE_NUM 5

#घोषणा ETH_ALEN	6
#घोषणा ETH_TYPE_LEN		2
#घोषणा PAYLOAD_TYPE_LEN	1

#घोषणा RTL_IOCTL_HOSTAPD (SIOCIWFIRSTPRIV + 28)

/* RTL871X_IOCTL_HOSTAPD ioctl() cmd: */
क्रमागत अणु
	RTL871X_HOSTAPD_FLUSH = 1,
	RTL871X_HOSTAPD_ADD_STA = 2,
	RTL871X_HOSTAPD_REMOVE_STA = 3,
	RTL871X_HOSTAPD_GET_INFO_STA = 4,
	/* REMOVED: PRISM2_HOSTAPD_RESET_TXEXC_STA = 5, */
	RTL871X_HOSTAPD_GET_WPAIE_STA = 5,
	RTL871X_SET_ENCRYPTION = 6,
	RTL871X_GET_ENCRYPTION = 7,
	RTL871X_HOSTAPD_SET_FLAGS_STA = 8,
	RTL871X_HOSTAPD_GET_RID = 9,
	RTL871X_HOSTAPD_SET_RID = 10,
	RTL871X_HOSTAPD_SET_ASSOC_AP_ADDR = 11,
	RTL871X_HOSTAPD_SET_GENERIC_ELEMENT = 12,
	RTL871X_HOSTAPD_MLME = 13,
	RTL871X_HOSTAPD_SCAN_REQ = 14,
	RTL871X_HOSTAPD_STA_CLEAR_STATS = 15,
	RTL871X_HOSTAPD_SET_BEACON = 16,
	RTL871X_HOSTAPD_SET_WPS_BEACON = 17,
	RTL871X_HOSTAPD_SET_WPS_PROBE_RESP = 18,
	RTL871X_HOSTAPD_SET_WPS_ASSOC_RESP = 19,
	RTL871X_HOSTAPD_SET_HIDDEN_SSID = 20,
	RTL871X_HOSTAPD_SET_MACADDR_ACL = 21,
	RTL871X_HOSTAPD_ACL_ADD_STA = 22,
	RTL871X_HOSTAPD_ACL_REMOVE_STA = 23,
पूर्ण;

/* STA flags */
#घोषणा WLAN_STA_AUTH BIT(0)
#घोषणा WLAN_STA_ASSOC BIT(1)
#घोषणा WLAN_STA_PS BIT(2)
#घोषणा WLAN_STA_TIM BIT(3)
#घोषणा WLAN_STA_PERM BIT(4)
#घोषणा WLAN_STA_AUTHORIZED BIT(5)
#घोषणा WLAN_STA_PENDING_POLL BIT(6) /* pending activity poll not ACKed */
#घोषणा WLAN_STA_SHORT_PREAMBLE BIT(7)
#घोषणा WLAN_STA_PREAUTH BIT(8)
#घोषणा WLAN_STA_WME BIT(9)
#घोषणा WLAN_STA_MFP BIT(10)
#घोषणा WLAN_STA_HT BIT(11)
#घोषणा WLAN_STA_WPS BIT(12)
#घोषणा WLAN_STA_MAYBE_WPS BIT(13)
#घोषणा WLAN_STA_VHT BIT(14)
#घोषणा WLAN_STA_NONERP BIT(31)

#घोषणा IEEE_CMD_SET_WPA_PARAM			1
#घोषणा IEEE_CMD_SET_WPA_IE				2
#घोषणा IEEE_CMD_SET_ENCRYPTION			3
#घोषणा IEEE_CMD_MLME						4

#घोषणा IEEE_PARAM_WPA_ENABLED				1
#घोषणा IEEE_PARAM_TKIP_COUNTERMEASURES		2
#घोषणा IEEE_PARAM_DROP_UNENCRYPTED			3
#घोषणा IEEE_PARAM_PRIVACY_INVOKED			4
#घोषणा IEEE_PARAM_AUTH_ALGS					5
#घोषणा IEEE_PARAM_IEEE_802_1X				6
#घोषणा IEEE_PARAM_WPAX_SELECT				7

#घोषणा IEEE_MLME_STA_DEAUTH				1
#घोषणा IEEE_MLME_STA_DISASSOC			2

#घोषणा IEEE_CRYPT_ERR_UNKNOWN_ALG			2
#घोषणा IEEE_CRYPT_ERR_UNKNOWN_ADDR			3
#घोषणा IEEE_CRYPT_ERR_CRYPT_INIT_FAILED		4
#घोषणा IEEE_CRYPT_ERR_KEY_SET_FAILED			5
#घोषणा IEEE_CRYPT_ERR_TX_KEY_SET_FAILED		6
#घोषणा IEEE_CRYPT_ERR_CARD_CONF_FAILED		7


#घोषणा	IEEE_CRYPT_ALG_NAME_LEN			16

#घोषणा WPA_CIPHER_NONE		BIT(0)
#घोषणा WPA_CIPHER_WEP40	BIT(1)
#घोषणा WPA_CIPHER_WEP104 BIT(2)
#घोषणा WPA_CIPHER_TKIP		BIT(3)
#घोषणा WPA_CIPHER_CCMP		BIT(4)



#घोषणा WPA_SELECTOR_LEN 4
बाह्य u8 RTW_WPA_OUI_TYPE[];
बाह्य u16 RTW_WPA_VERSION;
बाह्य u8 WPA_AUTH_KEY_MGMT_NONE[];
बाह्य u8 WPA_AUTH_KEY_MGMT_UNSPEC_802_1X[];
बाह्य u8 WPA_AUTH_KEY_MGMT_PSK_OVER_802_1X[];
बाह्य u8 WPA_CIPHER_SUITE_NONE[];
बाह्य u8 WPA_CIPHER_SUITE_WEP40[];
बाह्य u8 WPA_CIPHER_SUITE_TKIP[];
बाह्य u8 WPA_CIPHER_SUITE_WRAP[];
बाह्य u8 WPA_CIPHER_SUITE_CCMP[];
बाह्य u8 WPA_CIPHER_SUITE_WEP104[];


#घोषणा RSN_HEADER_LEN 4
#घोषणा RSN_SELECTOR_LEN 4

बाह्य u16 RSN_VERSION_BSD;
बाह्य u8 RSN_AUTH_KEY_MGMT_UNSPEC_802_1X[];
बाह्य u8 RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X[];
बाह्य u8 RSN_CIPHER_SUITE_NONE[];
बाह्य u8 RSN_CIPHER_SUITE_WEP40[];
बाह्य u8 RSN_CIPHER_SUITE_TKIP[];
बाह्य u8 RSN_CIPHER_SUITE_WRAP[];
बाह्य u8 RSN_CIPHER_SUITE_CCMP[];
बाह्य u8 RSN_CIPHER_SUITE_WEP104[];


क्रमागत अणु
	RATEID_IDX_BGN_40M_2SS = 0,
	RATEID_IDX_BGN_40M_1SS = 1,
	RATEID_IDX_BGN_20M_2SS_BN = 2,
	RATEID_IDX_BGN_20M_1SS_BN = 3,
	RATEID_IDX_GN_N2SS = 4,
	RATEID_IDX_GN_N1SS = 5,
	RATEID_IDX_BG = 6,
	RATEID_IDX_G = 7,
	RATEID_IDX_B = 8,
	RATEID_IDX_VHT_2SS = 9,
	RATEID_IDX_VHT_1SS = 10,
पूर्ण;

क्रमागत network_type अणु
	WIRELESS_INVALID = 0,
	/* Sub-Element */
	WIRELESS_11B = BIT(0), /*  tx: cck only , rx: cck only, hw: cck */
	WIRELESS_11G = BIT(1), /*  tx: ofdm only, rx: ofdm & cck, hw: cck & ofdm */
	WIRELESS_11A = BIT(2), /*  tx: ofdm only, rx: ofdm only, hw: ofdm only */
	WIRELESS_11_24N = BIT(3), /*  tx: MCS only, rx: MCS & cck, hw: MCS & cck */
	WIRELESS_11_5N = BIT(4), /*  tx: MCS only, rx: MCS & ofdm, hw: ofdm only */
	WIRELESS_AUTO = BIT(5),
	WIRELESS_11AC = BIT(6),

	/* Combination */
	/* Type क्रम current wireless mode */
	WIRELESS_11BG = (WIRELESS_11B|WIRELESS_11G), /*  tx: cck & ofdm, rx: cck & ofdm & MCS, hw: cck & ofdm */
	WIRELESS_11G_24N = (WIRELESS_11G|WIRELESS_11_24N), /*  tx: ofdm & MCS, rx: ofdm & cck & MCS, hw: cck & ofdm */
	WIRELESS_11A_5N = (WIRELESS_11A|WIRELESS_11_5N), /*  tx: ofdm & MCS, rx: ofdm & MCS, hw: ofdm only */
	WIRELESS_11B_24N = (WIRELESS_11B|WIRELESS_11_24N), /*  tx: ofdm & cck & MCS, rx: ofdm & cck & MCS, hw: ofdm & cck */
	WIRELESS_11BG_24N = (WIRELESS_11B|WIRELESS_11G|WIRELESS_11_24N), /*  tx: ofdm & cck & MCS, rx: ofdm & cck & MCS, hw: ofdm & cck */
	WIRELESS_11_24AC = (WIRELESS_11G|WIRELESS_11AC),
	WIRELESS_11_5AC = (WIRELESS_11A|WIRELESS_11AC),


	/* Type क्रम registry शेष wireless mode */
	WIRELESS_11AGN = (WIRELESS_11A|WIRELESS_11G|WIRELESS_11_24N|WIRELESS_11_5N), /*  tx: ofdm & MCS, rx: ofdm & MCS, hw: ofdm only */
	WIRELESS_11ABGN = (WIRELESS_11A|WIRELESS_11B|WIRELESS_11G|WIRELESS_11_24N|WIRELESS_11_5N),
	WIRELESS_MODE_24G = (WIRELESS_11B|WIRELESS_11G|WIRELESS_11_24N|WIRELESS_11AC),
	WIRELESS_MODE_MAX = (WIRELESS_11A|WIRELESS_11B|WIRELESS_11G|WIRELESS_11_24N|WIRELESS_11_5N|WIRELESS_11AC),
पूर्ण;

#घोषणा SUPPORTED_24G_NETTYPE_MSK (WIRELESS_11B | WIRELESS_11G | WIRELESS_11_24N)

#घोषणा IsLegacyOnly(NetType)  ((NetType) == ((NetType) & (WIRELESS_11BG|WIRELESS_11A)))

#घोषणा IsSupported24G(NetType) ((NetType) & SUPPORTED_24G_NETTYPE_MSK ? true : false)

#घोषणा IsEnableHWCCK(NetType) IsSupported24G(NetType)
#घोषणा IsEnableHWOFDM(NetType) (((NetType) & (WIRELESS_11G|WIRELESS_11_24N)) ? true : false)

#घोषणा IsSupportedRxCCK(NetType) IsEnableHWCCK(NetType)
#घोषणा IsSupportedRxOFDM(NetType) IsEnableHWOFDM(NetType)
#घोषणा IsSupportedRxHT(NetType) IsEnableHWOFDM(NetType)

#घोषणा IsSupportedTxCCK(NetType) (((NetType) & (WIRELESS_11B)) ? true : false)
#घोषणा IsSupportedTxOFDM(NetType) (((NetType) & (WIRELESS_11G|WIRELESS_11A)) ? true : false)
#घोषणा IsSupportedHT(NetType) (((NetType) & (WIRELESS_11_24N|WIRELESS_11_5N)) ? true : false)

#घोषणा IsSupportedVHT(NetType) (((NetType) & (WIRELESS_11AC)) ? true : false)


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
	        काष्ठाअणु
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
		काष्ठा अणु
			u16 aid;
			u16 capability;
			पूर्णांक flags;
			u8 tx_supp_rates[16];
			काष्ठा ieee80211_ht_cap ht_cap;
		पूर्ण add_sta;
		काष्ठा अणु
			u8 reserved[2];/* क्रम set max_num_sta */
			u8 buf[0];
		पूर्ण bcn_ie;
	पूर्ण u;
पूर्ण;

काष्ठा ieee_param_ex अणु
	u32 cmd;
	u8 sta_addr[ETH_ALEN];
	u8 data[0];
पूर्ण;

काष्ठा sta_data अणु
	u16 aid;
	u16 capability;
	पूर्णांक flags;
	u32 sta_set;
	u8 tx_supp_rates[16];
	u32 tx_supp_rates_len;
	काष्ठा ieee80211_ht_cap ht_cap;
	u64	rx_pkts;
	u64	rx_bytes;
	u64	rx_drops;
	u64	tx_pkts;
	u64	tx_bytes;
	u64	tx_drops;
पूर्ण;

/* this is stolen from ipw2200 driver */
#घोषणा IEEE_IBSS_MAC_HASH_SIZE 31

काष्ठा eapol अणु
	u8 snap[6];
	u16 ethertype;
	u8 version;
	u8 type;
	u16 length;
पूर्ण __attribute__ ((packed));

#घोषणा IEEE80211_FCS_LEN    4

#घोषणा MIN_FRAG_THRESHOLD     256U
#घोषणा	MAX_FRAG_THRESHOLD     2346U

/* sequence control field */
#घोषणा RTW_IEEE80211_SCTL_FRAG	0x000F
#घोषणा RTW_IEEE80211_SCTL_SEQ	0xFFF0


#घोषणा RTW_ERP_INFO_NON_ERP_PRESENT BIT(0)
#घोषणा RTW_ERP_INFO_USE_PROTECTION BIT(1)
#घोषणा RTW_ERP_INFO_BARKER_PREAMBLE_MODE BIT(2)

/* QoS, QOS */
#घोषणा NORMAL_ACK			0
#घोषणा NO_ACK				1
#घोषणा NON_EXPLICIT_ACK	2
#घोषणा BLOCK_ACK			3

#अगर_अघोषित ETH_P_PAE
#घोषणा ETH_P_PAE 0x888E /* Port Access Entity (IEEE 802.1X) */
#पूर्ण_अगर /* ETH_P_PAE */

#घोषणा ETH_P_PREAUTH 0x88C7 /* IEEE 802.11i pre-authentication */

#घोषणा ETH_P_ECONET	0x0018

#अगर_अघोषित ETH_P_80211_RAW
#घोषणा ETH_P_80211_RAW (ETH_P_ECONET + 1)
#पूर्ण_अगर

/* IEEE 802.11 defines */

#घोषणा P80211_OUI_LEN 3

काष्ठा ieee80211_snap_hdr अणु
        u8    dsap;   /* always 0xAA */
        u8    ssap;   /* always 0xAA */
        u8    ctrl;   /* always 0x03 */
        u8    oui[P80211_OUI_LEN];    /* organizational universal id */
पूर्ण __attribute__ ((packed));

#घोषणा SNAP_SIZE माप(काष्ठा ieee80211_snap_hdr)

#घोषणा WLAN_FC_GET_TYPE(fc) ((fc) & IEEE80211_FCTL_FTYPE)
#घोषणा WLAN_FC_GET_STYPE(fc) ((fc) & IEEE80211_FCTL_STYPE)

#घोषणा WLAN_QC_GET_TID(qc) ((qc) & 0x0f)

#घोषणा WLAN_GET_SEQ_FRAG(seq) ((seq) & RTW_IEEE80211_SCTL_FRAG)
#घोषणा WLAN_GET_SEQ_SEQ(seq)  ((seq) & RTW_IEEE80211_SCTL_SEQ)

/* Reason codes */
#घोषणा WLAN_REASON_ACTIVE_ROAM 65533
#घोषणा WLAN_REASON_JOIN_WRONG_CHANNEL       65534
#घोषणा WLAN_REASON_EXPIRATION_CHK 65535

#घोषणा IEEE80211_MGMT_HDR_LEN 24
#घोषणा IEEE80211_DATA_HDR3_LEN 24
#घोषणा IEEE80211_DATA_HDR4_LEN 30


#घोषणा IEEE80211_STATMASK_SIGNAL (1<<0)
#घोषणा IEEE80211_STATMASK_RSSI (1<<1)
#घोषणा IEEE80211_STATMASK_NOISE (1<<2)
#घोषणा IEEE80211_STATMASK_RATE (1<<3)
#घोषणा IEEE80211_STATMASK_WEMASK 0x7


#घोषणा IEEE80211_CCK_MODULATION    (1<<0)
#घोषणा IEEE80211_OFDM_MODULATION   (1<<1)

#घोषणा IEEE80211_24GHZ_BAND     (1<<0)
#घोषणा IEEE80211_52GHZ_BAND     (1<<1)

#घोषणा IEEE80211_CCK_RATE_LEN			4
#घोषणा IEEE80211_NUM_OFDM_RATESLEN	8


#घोषणा IEEE80211_CCK_RATE_1MB		        0x02
#घोषणा IEEE80211_CCK_RATE_2MB		        0x04
#घोषणा IEEE80211_CCK_RATE_5MB		        0x0B
#घोषणा IEEE80211_CCK_RATE_11MB		        0x16
#घोषणा IEEE80211_OFDM_RATE_LEN			8
#घोषणा IEEE80211_OFDM_RATE_6MB		        0x0C
#घोषणा IEEE80211_OFDM_RATE_9MB		        0x12
#घोषणा IEEE80211_OFDM_RATE_12MB		0x18
#घोषणा IEEE80211_OFDM_RATE_18MB		0x24
#घोषणा IEEE80211_OFDM_RATE_24MB		0x30
#घोषणा IEEE80211_OFDM_RATE_36MB		0x48
#घोषणा IEEE80211_OFDM_RATE_48MB		0x60
#घोषणा IEEE80211_OFDM_RATE_54MB		0x6C
#घोषणा IEEE80211_BASIC_RATE_MASK		0x80

#घोषणा IEEE80211_CCK_RATE_1MB_MASK		(1<<0)
#घोषणा IEEE80211_CCK_RATE_2MB_MASK		(1<<1)
#घोषणा IEEE80211_CCK_RATE_5MB_MASK		(1<<2)
#घोषणा IEEE80211_CCK_RATE_11MB_MASK		(1<<3)
#घोषणा IEEE80211_OFDM_RATE_6MB_MASK		(1<<4)
#घोषणा IEEE80211_OFDM_RATE_9MB_MASK		(1<<5)
#घोषणा IEEE80211_OFDM_RATE_12MB_MASK		(1<<6)
#घोषणा IEEE80211_OFDM_RATE_18MB_MASK		(1<<7)
#घोषणा IEEE80211_OFDM_RATE_24MB_MASK		(1<<8)
#घोषणा IEEE80211_OFDM_RATE_36MB_MASK		(1<<9)
#घोषणा IEEE80211_OFDM_RATE_48MB_MASK		(1<<10)
#घोषणा IEEE80211_OFDM_RATE_54MB_MASK		(1<<11)

#घोषणा IEEE80211_CCK_RATES_MASK	        0x0000000F
#घोषणा IEEE80211_CCK_BASIC_RATES_MASK	(IEEE80211_CCK_RATE_1MB_MASK | \
	IEEE80211_CCK_RATE_2MB_MASK)
#घोषणा IEEE80211_CCK_DEFAULT_RATES_MASK	(IEEE80211_CCK_BASIC_RATES_MASK | \
        IEEE80211_CCK_RATE_5MB_MASK | \
        IEEE80211_CCK_RATE_11MB_MASK)

#घोषणा IEEE80211_OFDM_RATES_MASK		0x00000FF0
#घोषणा IEEE80211_OFDM_BASIC_RATES_MASK	(IEEE80211_OFDM_RATE_6MB_MASK | \
	IEEE80211_OFDM_RATE_12MB_MASK | \
	IEEE80211_OFDM_RATE_24MB_MASK)
#घोषणा IEEE80211_OFDM_DEFAULT_RATES_MASK	(IEEE80211_OFDM_BASIC_RATES_MASK | \
	IEEE80211_OFDM_RATE_9MB_MASK  | \
	IEEE80211_OFDM_RATE_18MB_MASK | \
	IEEE80211_OFDM_RATE_36MB_MASK | \
	IEEE80211_OFDM_RATE_48MB_MASK | \
	IEEE80211_OFDM_RATE_54MB_MASK)
#घोषणा IEEE80211_DEFAULT_RATES_MASK (IEEE80211_OFDM_DEFAULT_RATES_MASK | \
                                IEEE80211_CCK_DEFAULT_RATES_MASK)

#घोषणा IEEE80211_NUM_OFDM_RATES	    8
#घोषणा IEEE80211_NUM_CCK_RATES	            4
#घोषणा IEEE80211_OFDM_SHIFT_MASK_A         4


क्रमागत अणु
	MGN_1M		= 0x02,
	MGN_2M		= 0x04,
	MGN_5_5M	= 0x0B,
	MGN_6M		= 0x0C,
	MGN_9M		= 0x12,
	MGN_11M		= 0x16,
	MGN_12M	= 0x18,
	MGN_18M	= 0x24,
	MGN_24M	= 0x30,
	MGN_36M	= 0x48,
	MGN_48M	= 0x60,
	MGN_54M	= 0x6C,
	MGN_MCS32	= 0x7F,
	MGN_MCS0,
	MGN_MCS1,
	MGN_MCS2,
	MGN_MCS3,
	MGN_MCS4,
	MGN_MCS5,
	MGN_MCS6,
	MGN_MCS7,
	MGN_MCS8,
	MGN_MCS9,
	MGN_MCS10,
	MGN_MCS11,
	MGN_MCS12,
	MGN_MCS13,
	MGN_MCS14,
	MGN_MCS15,
	MGN_MCS16,
	MGN_MCS17,
	MGN_MCS18,
	MGN_MCS19,
	MGN_MCS20,
	MGN_MCS21,
	MGN_MCS22,
	MGN_MCS23,
	MGN_MCS24,
	MGN_MCS25,
	MGN_MCS26,
	MGN_MCS27,
	MGN_MCS28,
	MGN_MCS29,
	MGN_MCS30,
	MGN_MCS31,
	MGN_VHT1SS_MCS0,
	MGN_VHT1SS_MCS1,
	MGN_VHT1SS_MCS2,
	MGN_VHT1SS_MCS3,
	MGN_VHT1SS_MCS4,
	MGN_VHT1SS_MCS5,
	MGN_VHT1SS_MCS6,
	MGN_VHT1SS_MCS7,
	MGN_VHT1SS_MCS8,
	MGN_VHT1SS_MCS9,
	MGN_VHT2SS_MCS0,
	MGN_VHT2SS_MCS1,
	MGN_VHT2SS_MCS2,
	MGN_VHT2SS_MCS3,
	MGN_VHT2SS_MCS4,
	MGN_VHT2SS_MCS5,
	MGN_VHT2SS_MCS6,
	MGN_VHT2SS_MCS7,
	MGN_VHT2SS_MCS8,
	MGN_VHT2SS_MCS9,
	MGN_VHT3SS_MCS0,
	MGN_VHT3SS_MCS1,
	MGN_VHT3SS_MCS2,
	MGN_VHT3SS_MCS3,
	MGN_VHT3SS_MCS4,
	MGN_VHT3SS_MCS5,
	MGN_VHT3SS_MCS6,
	MGN_VHT3SS_MCS7,
	MGN_VHT3SS_MCS8,
	MGN_VHT3SS_MCS9,
	MGN_VHT4SS_MCS0,
	MGN_VHT4SS_MCS1,
	MGN_VHT4SS_MCS2,
	MGN_VHT4SS_MCS3,
	MGN_VHT4SS_MCS4,
	MGN_VHT4SS_MCS5,
	MGN_VHT4SS_MCS6,
	MGN_VHT4SS_MCS7,
	MGN_VHT4SS_MCS8,
	MGN_VHT4SS_MCS9,
	MGN_UNKNOWN
पूर्ण;

#घोषणा IS_HT_RATE(_rate)				(_rate >= MGN_MCS0 && _rate <= MGN_MCS31)
#घोषणा IS_VHT_RATE(_rate)				(_rate >= MGN_VHT1SS_MCS0 && _rate <= MGN_VHT4SS_MCS9)
#घोषणा IS_CCK_RATE(_rate)				(MGN_1M == _rate || _rate == MGN_2M || _rate == MGN_5_5M || _rate == MGN_11M)
#घोषणा IS_OFDM_RATE(_rate)				(MGN_6M <= _rate && _rate <= MGN_54M  && _rate != MGN_11M)


/* NOTE: This data is क्रम statistical purposes; not all hardware provides this
 *       inक्रमmation क्रम frames received.  Not setting these will not cause
 *       any adverse affects. */

/* IEEE 802.11 requires that STA supports concurrent reception of at least
 * three fragmented frames. This define can be increased to support more
 * concurrent frames, but it should be noted that each entry can consume about
 * 2 kB of RAM and increasing cache size will slow करोwn frame reassembly. */
#घोषणा IEEE80211_FRAG_CACHE_LEN 4

#घोषणा SEC_KEY_1         (1<<0)
#घोषणा SEC_KEY_2         (1<<1)
#घोषणा SEC_KEY_3         (1<<2)
#घोषणा SEC_KEY_4         (1<<3)
#घोषणा SEC_ACTIVE_KEY    (1<<4)
#घोषणा SEC_AUTH_MODE     (1<<5)
#घोषणा SEC_UNICAST_GROUP (1<<6)
#घोषणा SEC_LEVEL         (1<<7)
#घोषणा SEC_ENABLED       (1<<8)

#घोषणा SEC_LEVEL_0      0 /* None */
#घोषणा SEC_LEVEL_1      1 /* WEP 40 and 104 bit */
#घोषणा SEC_LEVEL_2      2 /* Level 1 + TKIP */
#घोषणा SEC_LEVEL_2_CKIP 3 /* Level 1 + CKIP */
#घोषणा SEC_LEVEL_3      4 /* Level 2 + CCMP */

#घोषणा WEP_KEYS 4
#घोषणा WEP_KEY_LEN 13

#घोषणा BIP_MAX_KEYID 5
#घोषणा BIP_AAD_SIZE  20

/*

 802.11 data frame from AP

      ,-------------------------------------------------------------------.
Bytes |  2   |  2   |    6    |    6    |    6    |  2   | 0..2312 |   4  |
      |------|------|---------|---------|---------|------|---------|------|
Desc. | ctrl | dura |  DA/RA  |   TA    |    SA   | Sequ |  frame  |  fcs |
      |      | tion | (BSSID) |         |         | ence |  data   |      |
      `-------------------------------------------------------------------'

Total: 28-2340 bytes

*/

#घोषणा BEACON_PROBE_SSID_ID_POSITION 12

/* Management Frame Inक्रमmation Element Types */
#घोषणा MFIE_TYPE_SSID       0
#घोषणा MFIE_TYPE_RATES      1
#घोषणा MFIE_TYPE_FH_SET     2
#घोषणा MFIE_TYPE_DS_SET     3
#घोषणा MFIE_TYPE_CF_SET     4
#घोषणा MFIE_TYPE_TIM        5
#घोषणा MFIE_TYPE_IBSS_SET   6
#घोषणा MFIE_TYPE_CHALLENGE  16
#घोषणा MFIE_TYPE_ERP        42
#घोषणा MFIE_TYPE_RSN	     48
#घोषणा MFIE_TYPE_RATES_EX   50
#घोषणा MFIE_TYPE_GENERIC    221

/* SWEEP TABLE ENTRIES NUMBER*/
#घोषणा MAX_SWEEP_TAB_ENTRIES		  42
#घोषणा MAX_SWEEP_TAB_ENTRIES_PER_PACKET  7
/* MAX_RATES_LENGTH needs to be 12.  The spec says 8, and many APs
 * only use 8, and then use extended rates क्रम the reमुख्यing supported
 * rates.  Other APs, however, stick all of their supported rates on the
 * मुख्य rates inक्रमmation element... */
#घोषणा MAX_RATES_LENGTH                  ((u8)12)
#घोषणा MAX_RATES_EX_LENGTH               ((u8)16)
#घोषणा MAX_NETWORK_COUNT                  128
#घोषणा MAX_CHANNEL_NUMBER                 161
#घोषणा IEEE80211_SOFTMAC_SCAN_TIME	  400
/* HZ / 2) */
#घोषणा IEEE80211_SOFTMAC_ASSOC_RETRY_TIME (HZ * 2)

#घोषणा CRC_LENGTH                 4U

#घोषणा MAX_WPA_IE_LEN (256)
#घोषणा MAX_WPS_IE_LEN (512)
#घोषणा MAX_P2P_IE_LEN (256)
#घोषणा MAX_WFD_IE_LEN (128)

#घोषणा NETWORK_EMPTY_ESSID (1<<0)
#घोषणा NETWORK_HAS_OFDM    (1<<1)
#घोषणा NETWORK_HAS_CCK     (1<<2)

#घोषणा IEEE80211_DTIM_MBCAST 4
#घोषणा IEEE80211_DTIM_UCAST 2
#घोषणा IEEE80211_DTIM_VALID 1
#घोषणा IEEE80211_DTIM_INVALID 0

#घोषणा IEEE80211_PS_DISABLED 0
#घोषणा IEEE80211_PS_UNICAST IEEE80211_DTIM_UCAST
#घोषणा IEEE80211_PS_MBCAST IEEE80211_DTIM_MBCAST
#घोषणा IW_ESSID_MAX_SIZE 32
/*
join_res:
-1: authentication fail
-2: association fail
> 0: TID
*/

#घोषणा DEFAULT_MAX_SCAN_AGE (15 * HZ)
#घोषणा DEFAULT_FTS 2346
#घोषणा MAC_ARG(x) (x)
#घोषणा IP_ARG(x) (x)

अटल अंतरभूत पूर्णांक is_multicast_mac_addr(स्थिर u8 *addr)
अणु
        वापस ((addr[0] != 0xff) && (0x01 & addr[0]));
पूर्ण

अटल अंतरभूत पूर्णांक is_broadcast_mac_addr(स्थिर u8 *addr)
अणु
	वापस ((addr[0] == 0xff) && (addr[1] == 0xff) && (addr[2] == 0xff) &&   \
		(addr[3] == 0xff) && (addr[4] == 0xff) && (addr[5] == 0xff));
पूर्ण

अटल अंतरभूत पूर्णांक is_zero_mac_addr(स्थिर u8 *addr)
अणु
	वापस ((addr[0] == 0x00) && (addr[1] == 0x00) && (addr[2] == 0x00) &&   \
		(addr[3] == 0x00) && (addr[4] == 0x00) && (addr[5] == 0x00));
पूर्ण

#घोषणा CFG_IEEE80211_RESERVE_FCS (1<<0)
#घोषणा CFG_IEEE80211_COMPUTE_FCS (1<<1)

#घोषणा MAXTID	16

#घोषणा IEEE_A            (1<<0)
#घोषणा IEEE_B            (1<<1)
#घोषणा IEEE_G            (1<<2)
#घोषणा IEEE_MODE_MASK    (IEEE_A|IEEE_B|IEEE_G)

/* Action category code */
क्रमागत अणु
	RTW_WLAN_CATEGORY_SPECTRUM_MGMT = 0,
	RTW_WLAN_CATEGORY_QOS = 1,
	RTW_WLAN_CATEGORY_DLS = 2,
	RTW_WLAN_CATEGORY_BACK = 3,
	RTW_WLAN_CATEGORY_PUBLIC = 4, /* IEEE 802.11 खुला action frames */
	RTW_WLAN_CATEGORY_RADIO_MEASUREMENT  = 5,
	RTW_WLAN_CATEGORY_FT = 6,
	RTW_WLAN_CATEGORY_HT = 7,
	RTW_WLAN_CATEGORY_SA_QUERY = 8,
	RTW_WLAN_CATEGORY_UNPROTECTED_WNM = 11, /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	RTW_WLAN_CATEGORY_TDLS = 12,
	RTW_WLAN_CATEGORY_SELF_PROTECTED = 15, /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	RTW_WLAN_CATEGORY_WMM = 17,
	RTW_WLAN_CATEGORY_VHT = 21,
	RTW_WLAN_CATEGORY_P2P = 0x7f,/* P2P action frames */
पूर्ण;

क्रमागत अणु
	ACT_PUBLIC_BSSCOEXIST = 0, /*  20/40 BSS Coexistence */
	ACT_PUBLIC_DSE_ENABLE = 1,
	ACT_PUBLIC_DSE_DEENABLE = 2,
	ACT_PUBLIC_DSE_REG_LOCATION = 3,
	ACT_PUBLIC_EXT_CHL_SWITCH = 4,
	ACT_PUBLIC_DSE_MSR_REQ = 5,
	ACT_PUBLIC_DSE_MSR_RPRT = 6,
	ACT_PUBLIC_MP = 7, /*  Measurement Pilot */
	ACT_PUBLIC_DSE_PWR_CONSTRAINT = 8,
	ACT_PUBLIC_VENDOR = 9, /*  क्रम WIFI_सूचीECT */
	ACT_PUBLIC_GAS_INITIAL_REQ = 10,
	ACT_PUBLIC_GAS_INITIAL_RSP = 11,
	ACT_PUBLIC_GAS_COMEBACK_REQ = 12,
	ACT_PUBLIC_GAS_COMEBACK_RSP = 13,
	ACT_PUBLIC_TDLS_DISCOVERY_RSP = 14,
	ACT_PUBLIC_LOCATION_TRACK = 15,
	ACT_PUBLIC_MAX
पूर्ण;

#घोषणा OUI_MICROSOFT 0x0050f2 /* Microsoft (also used in Wi-Fi specs)
				* 00:50:F2 */
#घोषणा WME_OUI_TYPE 2
#घोषणा WME_OUI_SUBTYPE_INFORMATION_ELEMENT 0
#घोषणा WME_OUI_SUBTYPE_PARAMETER_ELEMENT 1
#घोषणा WME_OUI_SUBTYPE_TSPEC_ELEMENT 2
#घोषणा WME_VERSION 1

#घोषणा WME_ACTION_CODE_SETUP_REQUEST 0
#घोषणा WME_ACTION_CODE_SETUP_RESPONSE 1
#घोषणा WME_ACTION_CODE_TEARDOWN 2

#घोषणा WME_SETUP_RESPONSE_STATUS_ADMISSION_ACCEPTED 0
#घोषणा WME_SETUP_RESPONSE_STATUS_INVALID_PARAMETERS 1
#घोषणा WME_SETUP_RESPONSE_STATUS_REFUSED 3

#घोषणा WME_TSPEC_सूचीECTION_UPLINK 0
#घोषणा WME_TSPEC_सूचीECTION_DOWNLINK 1
#घोषणा WME_TSPEC_सूचीECTION_BI_सूचीECTIONAL 3


#घोषणा OUI_BROADCOM 0x00904c /* Broadcom (Epigram) */

#घोषणा VENDOR_HT_CAPAB_OUI_TYPE 0x33 /* 00-90-4c:0x33 */

/**
 * क्रमागत rtw_ieee80211_channel_flags - channel flags
 *
 * Channel flags set by the regulatory control code.
 *
 * @RTW_IEEE80211_CHAN_DISABLED: This channel is disabled.
 * @RTW_IEEE80211_CHAN_PASSIVE_SCAN: Only passive scanning is permitted
 *      on this channel.
 * @RTW_IEEE80211_CHAN_NO_IBSS: IBSS is not allowed on this channel.
 * @RTW_IEEE80211_CHAN_RADAR: Radar detection is required on this channel.
 * @RTW_IEEE80211_CHAN_NO_HT40PLUS: extension channel above this channel
 *      is not permitted.
 * @RTW_IEEE80211_CHAN_NO_HT40MINUS: extension channel below this channel
 *      is not permitted.
 */
  क्रमागत rtw_ieee80211_channel_flags अणु
          RTW_IEEE80211_CHAN_DISABLED         = 1<<0,
          RTW_IEEE80211_CHAN_PASSIVE_SCAN     = 1<<1,
          RTW_IEEE80211_CHAN_NO_IBSS          = 1<<2,
          RTW_IEEE80211_CHAN_RADAR            = 1<<3,
          RTW_IEEE80211_CHAN_NO_HT40PLUS      = 1<<4,
          RTW_IEEE80211_CHAN_NO_HT40MINUS     = 1<<5,
  पूर्ण;

  #घोषणा RTW_IEEE80211_CHAN_NO_HT40 \
          (RTW_IEEE80211_CHAN_NO_HT40PLUS | RTW_IEEE80211_CHAN_NO_HT40MINUS)

/* Represent channel details, subset of ieee80211_channel */
काष्ठा rtw_ieee80211_channel अणु
	/* क्रमागत nl80211_band band; */
	/* u16 center_freq; */
	u16 hw_value;
	u32 flags;
	/* पूर्णांक max_antenna_gain; */
	/* पूर्णांक max_घातer; */
	/* पूर्णांक max_reg_घातer; */
	/* bool beacon_found; */
	/* u32 orig_flags; */
	/* पूर्णांक orig_mag; */
	/* पूर्णांक orig_mpwr; */
पूर्ण;

#घोषणा CHAN_FMT \
	/*"band:%d, "*/ \
	/*"center_freq:%u, "*/ \
	"hw_value:%u, " \
	"flags:0x%08x" \
	/*"max_antenna_gain:%d\n"*/ \
	/*"max_power:%d\n"*/ \
	/*"max_reg_power:%d\n"*/ \
	/*"beacon_found:%u\n"*/ \
	/*"orig_flags:0x%08x\n"*/ \
	/*"orig_mag:%d\n"*/ \
	/*"orig_mpwr:%d\n"*/

#घोषणा CHAN_ARG(channel) \
	/*(channel)->band*/ \
	/*, (channel)->center_freq*/ \
	(channel)->hw_value \
	, (channel)->flags \
	/*, (channel)->max_antenna_gain*/ \
	/*, (channel)->max_घातer*/ \
	/*, (channel)->max_reg_घातer*/ \
	/*, (channel)->beacon_found*/ \
	/*, (channel)->orig_flags*/ \
	/*, (channel)->orig_mag*/ \
	/*, (channel)->orig_mpwr*/ \

/* Parsed Inक्रमmation Elements */
काष्ठा rtw_ieee802_11_elems अणु
	u8 *ssid;
	u8 ssid_len;
	u8 *supp_rates;
	u8 supp_rates_len;
	u8 *fh_params;
	u8 fh_params_len;
	u8 *ds_params;
	u8 ds_params_len;
	u8 *cf_params;
	u8 cf_params_len;
	u8 *tim;
	u8 tim_len;
	u8 *ibss_params;
	u8 ibss_params_len;
	u8 *challenge;
	u8 challenge_len;
	u8 *erp_info;
	u8 erp_info_len;
	u8 *ext_supp_rates;
	u8 ext_supp_rates_len;
	u8 *wpa_ie;
	u8 wpa_ie_len;
	u8 *rsn_ie;
	u8 rsn_ie_len;
	u8 *wme;
	u8 wme_len;
	u8 *wme_tspec;
	u8 wme_tspec_len;
	u8 *wps_ie;
	u8 wps_ie_len;
	u8 *घातer_cap;
	u8 घातer_cap_len;
	u8 *supp_channels;
	u8 supp_channels_len;
	u8 *mdie;
	u8 mdie_len;
	u8 *ftie;
	u8 ftie_len;
	u8 *समयout_पूर्णांक;
	u8 समयout_पूर्णांक_len;
	u8 *ht_capabilities;
	u8 ht_capabilities_len;
	u8 *ht_operation;
	u8 ht_operation_len;
	u8 *venकरोr_ht_cap;
	u8 venकरोr_ht_cap_len;
	u8 *vht_capabilities;
	u8 vht_capabilities_len;
	u8 *vht_operation;
	u8 vht_operation_len;
	u8 *vht_op_mode_notअगरy;
	u8 vht_op_mode_notअगरy_len;
पूर्ण;

क्रमागत ParseRes अणु ParseOK = 0, ParseUnknown = 1, ParseFailed = -1 पूर्ण;

क्रमागत ParseRes rtw_ieee802_11_parse_elems(u8 *start, uपूर्णांक len,
				काष्ठा rtw_ieee802_11_elems *elems,
				पूर्णांक show_errors);

u8 *rtw_set_fixed_ie(अचिन्हित अक्षर *pbuf, अचिन्हित पूर्णांक len, अचिन्हित अक्षर *source, अचिन्हित पूर्णांक *frlen);
u8 *rtw_set_ie(u8 *pbuf, चिन्हित पूर्णांक index, uपूर्णांक len, u8 *source, uपूर्णांक *frlen);

u8 *rtw_get_ie(u8 *pbuf, चिन्हित पूर्णांक index, चिन्हित पूर्णांक *len, चिन्हित पूर्णांक limit);
u8 *rtw_get_ie_ex(u8 *in_ie, uपूर्णांक in_len, u8 eid, u8 *oui, u8 oui_len, u8 *ie, uपूर्णांक *ielen);
पूर्णांक rtw_ies_हटाओ_ie(u8 *ies, uपूर्णांक *ies_len, uपूर्णांक offset, u8 eid, u8 *oui, u8 oui_len);

व्योम rtw_set_supported_rate(u8 *SupportedRates, uपूर्णांक mode);

अचिन्हित अक्षर *rtw_get_wpa_ie(अचिन्हित अक्षर *pie, पूर्णांक *wpa_ie_len, पूर्णांक limit);
अचिन्हित अक्षर *rtw_get_wpa2_ie(अचिन्हित अक्षर *pie, पूर्णांक *rsn_ie_len, पूर्णांक limit);
पूर्णांक rtw_get_wpa_cipher_suite(u8 *s);
पूर्णांक rtw_get_wpa2_cipher_suite(u8 *s);
पूर्णांक rtw_get_wapi_ie(u8 *in_ie, uपूर्णांक in_len, u8 *wapi_ie, u16 *wapi_len);
पूर्णांक rtw_parse_wpa_ie(u8 *wpa_ie, पूर्णांक wpa_ie_len, पूर्णांक *group_cipher, पूर्णांक *pairwise_cipher, पूर्णांक *is_8021x);
पूर्णांक rtw_parse_wpa2_ie(u8 *wpa_ie, पूर्णांक wpa_ie_len, पूर्णांक *group_cipher, पूर्णांक *pairwise_cipher, पूर्णांक *is_8021x);

व्योम rtw_get_sec_ie(u8 *in_ie, uपूर्णांक in_len, u8 *rsn_ie, u16 *rsn_len, u8 *wpa_ie, u16 *wpa_len);

u8 rtw_is_wps_ie(u8 *ie_ptr, uपूर्णांक *wps_ielen);
u8 *rtw_get_wps_ie(u8 *in_ie, uपूर्णांक in_len, u8 *wps_ie, uपूर्णांक *wps_ielen);
u8 *rtw_get_wps_attr(u8 *wps_ie, uपूर्णांक wps_ielen, u16 target_attr_id, u8 *buf_attr, u32 *len_attr);
u8 *rtw_get_wps_attr_content(u8 *wps_ie, uपूर्णांक wps_ielen, u16 target_attr_id, u8 *buf_content, uपूर्णांक *len_content);

/**
 * क्रम_each_ie - iterate over continuous IEs
 * @ie:
 * @buf:
 * @buf_len:
 */
#घोषणा क्रम_each_ie(ie, buf, buf_len) \
	क्रम (ie = (व्योम *)buf; (((u8 *)ie) - ((u8 *)buf) + 1) < buf_len; \
		ie = (व्योम *)(((u8 *)ie) + *(((u8 *)ie) + 1) + 2))

uपूर्णांक	rtw_get_rateset_len(u8 *rateset);

काष्ठा registry_priv;
पूर्णांक rtw_generate_ie(काष्ठा registry_priv *pregistrypriv);


पूर्णांक rtw_get_bit_value_from_ieee_value(u8 val);

bool rtw_is_cckrates_included(u8 *rate);

bool rtw_is_cckratesonly_included(u8 *rate);

पूर्णांक rtw_check_network_type(अचिन्हित अक्षर *rate, पूर्णांक ratelen, पूर्णांक channel);

व्योम rtw_get_bcn_info(काष्ठा wlan_network *pnetwork);

व्योम rtw_macaddr_cfg(काष्ठा device *dev, u8 *mac_addr);

u16 rtw_mcs_rate(u8 rf_type, u8 bw_40MHz, u8 लघु_GI, अचिन्हित अक्षर *MCS_rate);

पूर्णांक rtw_action_frame_parse(स्थिर u8 *frame, u32 frame_len, u8 *category, u8 *action);
स्थिर अक्षर *action_खुला_str(u8 action);

#पूर्ण_अगर /* IEEE80211_H */
