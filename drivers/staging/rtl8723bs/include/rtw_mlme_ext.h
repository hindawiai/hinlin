<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_MLME_EXT_H_
#घोषणा __RTW_MLME_EXT_H_


/* 	Commented by Albert 20101105 */
/* 	Increase the SURVEY_TO value from 100 to 150  (100ms to 150ms) */
/* 	The Realtek 8188CE SoftAP will spend around 100ms to send the probe response after receiving the probe request. */
/* 	So, this driver tried to extend the dwell समय क्रम each scanning channel. */
/* 	This will increase the chance to receive the probe response from SoftAP. */

#घोषणा SURVEY_TO		(100)
#घोषणा REAUTH_TO		(300) /* 50) */
#घोषणा REASSOC_TO		(300) /* 50) */
/* define DISCONNECT_TO	(3000) */
#घोषणा ADDBA_TO			(2000)

#घोषणा LINKED_TO (1) /* unit:2 sec, 1x2 =2 sec */

#घोषणा REAUTH_LIMIT	(4)
#घोषणा REASSOC_LIMIT	(4)
#घोषणा READDBA_LIMIT	(2)

#घोषणा ROAMING_LIMIT	8
/* define	IOCMD_REG0		0x10250370 */
/* define	IOCMD_REG1		0x10250374 */
/* define	IOCMD_REG2		0x10250378 */

/* define	FW_DYNAMIC_FUN_SWITCH	0x10250364 */

/* define	WRITE_BB_CMD		0xF0000001 */
/* define	SET_CHANNEL_CMD	0xF3000000 */
/* define	UPDATE_RA_CMD	0xFD0000A2 */

#घोषणा DYNAMIC_FUNC_DISABLE		(0x0)

/*  ====== ODM_ABILITY_E ======== */
/*  BB ODM section BIT 0-15 */
#घोषणा DYNAMIC_BB_DIG				BIT0 /* ODM_BB_DIG */
#घोषणा DYNAMIC_BB_RA_MASK			BIT1 /* ODM_BB_RA_MASK */
#घोषणा DYNAMIC_BB_DYNAMIC_TXPWR	BIT2 /* ODM_BB_DYNAMIC_TXPWR */
#घोषणा DYNAMIC_BB_BB_FA_CNT		BIT3 /* ODM_BB_FA_CNT */
#घोषणा DYNAMIC_BB_RSSI_MONITOR		BIT4 /* ODM_BB_RSSI_MONITOR */
#घोषणा DYNAMIC_BB_CCK_PD			BIT5 /* ODM_BB_CCK_PD */
#घोषणा DYNAMIC_BB_ANT_DIV			BIT6 /* ODM_BB_ANT_DIV */
#घोषणा DYNAMIC_BB_PWR_SAVE			BIT7 /* ODM_BB_PWR_SAVE */
#घोषणा DYNAMIC_BB_PWR_TRAIN		BIT8 /* ODM_BB_PWR_TRAIN */
#घोषणा DYNAMIC_BB_RATE_ADAPTIVE	BIT9 /* ODM_BB_RATE_ADAPTIVE */
#घोषणा DYNAMIC_BB_PATH_DIV			BIT10/* ODM_BB_PATH_DIV */
#घोषणा DYNAMIC_BB_PSD				BIT11/* ODM_BB_PSD */
#घोषणा DYNAMIC_BB_RXHP				BIT12/* ODM_BB_RXHP */
#घोषणा DYNAMIC_BB_ADAPTIVITY		BIT13/* ODM_BB_ADAPTIVITY */
#घोषणा DYNAMIC_BB_DYNAMIC_ATC		BIT14/* ODM_BB_DYNAMIC_ATC */

/*  MAC DM section BIT 16-23 */
#घोषणा DYNAMIC_MAC_EDCA_TURBO		BIT16/* ODM_MAC_EDCA_TURBO */
#घोषणा DYNAMIC_MAC_EARLY_MODE		BIT17/* ODM_MAC_EARLY_MODE */

/*  RF ODM section BIT 24-31 */
#घोषणा DYNAMIC_RF_TX_PWR_TRACK		BIT24/* ODM_RF_TX_PWR_TRACK */
#घोषणा DYNAMIC_RF_RX_GAIN_TRACK	BIT25/* ODM_RF_RX_GAIN_TRACK */
#घोषणा DYNAMIC_RF_CALIBRATION		BIT26/* ODM_RF_CALIBRATION */

#घोषणा DYNAMIC_ALL_FUNC_ENABLE		0xFFFFFFF

#घोषणा _HW_STATE_NOLINK_		0x00
#घोषणा _HW_STATE_ADHOC_		0x01
#घोषणा _HW_STATE_STATION_	0x02
#घोषणा _HW_STATE_AP_			0x03


#घोषणा		_1M_RATE_	0
#घोषणा		_2M_RATE_	1
#घोषणा		_5M_RATE_	2
#घोषणा		_11M_RATE_	3
#घोषणा		_6M_RATE_	4
#घोषणा		_9M_RATE_	5
#घोषणा		_12M_RATE_	6
#घोषणा		_18M_RATE_	7
#घोषणा		_24M_RATE_	8
#घोषणा		_36M_RATE_	9
#घोषणा		_48M_RATE_	10
#घोषणा		_54M_RATE_	11

/********************************************************
MCS rate definitions
*********************************************************/
#घोषणा MCS_RATE_1R	(0x000000ff)
#घोषणा MCS_RATE_2R	(0x0000ffff)
#घोषणा MCS_RATE_3R	(0x00ffffff)
#घोषणा MCS_RATE_4R	(0xffffffff)
#घोषणा MCS_RATE_2R_13TO15_OFF	(0x00001fff)


बाह्य अचिन्हित अक्षर RTW_WPA_OUI[];
बाह्य अचिन्हित अक्षर WMM_OUI[];
बाह्य अचिन्हित अक्षर WPS_OUI[];
बाह्य अचिन्हित अक्षर WFD_OUI[];
बाह्य अचिन्हित अक्षर P2P_OUI[];

बाह्य अचिन्हित अक्षर WMM_INFO_OUI[];
बाह्य अचिन्हित अक्षर WMM_PARA_OUI[];


/*  */
/*  Channel Plan Type. */
/*  Note: */
/* 	We just add new channel plan when the new channel plan is dअगरferent from any of the following */
/* 	channel plan. */
/* 	If you just want to customize the actions(scan period or join actions) about one of the channel plan, */
/* 	customize them in rt_channel_info in the RT_CHANNEL_LIST. */
/*  */
क्रमागत अणु
	/*  old channel plan mapping ===== */
	RT_CHANNEL_DOMAIN_FCC = 0x00,
	RT_CHANNEL_DOMAIN_IC = 0x01,
	RT_CHANNEL_DOMAIN_ETSI = 0x02,
	RT_CHANNEL_DOMAIN_SPAIN = 0x03,
	RT_CHANNEL_DOMAIN_FRANCE = 0x04,
	RT_CHANNEL_DOMAIN_MKK = 0x05,
	RT_CHANNEL_DOMAIN_MKK1 = 0x06,
	RT_CHANNEL_DOMAIN_ISRAEL = 0x07,
	RT_CHANNEL_DOMAIN_TELEC = 0x08,
	RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN = 0x09,
	RT_CHANNEL_DOMAIN_WORLD_WIDE_13 = 0x0A,
	RT_CHANNEL_DOMAIN_TAIWAN = 0x0B,
	RT_CHANNEL_DOMAIN_CHINA = 0x0C,
	RT_CHANNEL_DOMAIN_SINGAPORE_INDIA_MEXICO = 0x0D,
	RT_CHANNEL_DOMAIN_KOREA = 0x0E,
	RT_CHANNEL_DOMAIN_TURKEY = 0x0F,
	RT_CHANNEL_DOMAIN_JAPAN = 0x10,
	RT_CHANNEL_DOMAIN_FCC_NO_DFS = 0x11,
	RT_CHANNEL_DOMAIN_JAPAN_NO_DFS = 0x12,
	RT_CHANNEL_DOMAIN_WORLD_WIDE_5G = 0x13,
	RT_CHANNEL_DOMAIN_TAIWAN_NO_DFS = 0x14,

	/*  new channel plan mapping, (2GDOMAIN_5GDOMAIN) ===== */
	RT_CHANNEL_DOMAIN_WORLD_शून्य = 0x20,
	RT_CHANNEL_DOMAIN_ETSI1_शून्य = 0x21,
	RT_CHANNEL_DOMAIN_FCC1_शून्य = 0x22,
	RT_CHANNEL_DOMAIN_MKK1_शून्य = 0x23,
	RT_CHANNEL_DOMAIN_ETSI2_शून्य = 0x24,
	RT_CHANNEL_DOMAIN_FCC1_FCC1 = 0x25,
	RT_CHANNEL_DOMAIN_WORLD_ETSI1 = 0x26,
	RT_CHANNEL_DOMAIN_MKK1_MKK1 = 0x27,
	RT_CHANNEL_DOMAIN_WORLD_KCC1 = 0x28,
	RT_CHANNEL_DOMAIN_WORLD_FCC2 = 0x29,
	RT_CHANNEL_DOMAIN_WORLD_FCC3 = 0x30,
	RT_CHANNEL_DOMAIN_WORLD_FCC4 = 0x31,
	RT_CHANNEL_DOMAIN_WORLD_FCC5 = 0x32,
	RT_CHANNEL_DOMAIN_WORLD_FCC6 = 0x33,
	RT_CHANNEL_DOMAIN_FCC1_FCC7 = 0x34,
	RT_CHANNEL_DOMAIN_WORLD_ETSI2 = 0x35,
	RT_CHANNEL_DOMAIN_WORLD_ETSI3 = 0x36,
	RT_CHANNEL_DOMAIN_MKK1_MKK2 = 0x37,
	RT_CHANNEL_DOMAIN_MKK1_MKK3 = 0x38,
	RT_CHANNEL_DOMAIN_FCC1_NCC1 = 0x39,
	RT_CHANNEL_DOMAIN_FCC1_NCC2 = 0x40,
	RT_CHANNEL_DOMAIN_GLOBAL_शून्य = 0x41,
	RT_CHANNEL_DOMAIN_ETSI1_ETSI4 = 0x42,
	RT_CHANNEL_DOMAIN_FCC1_FCC2 = 0x43,
	RT_CHANNEL_DOMAIN_FCC1_NCC3 = 0x44,
	RT_CHANNEL_DOMAIN_WORLD_ETSI5 = 0x45,
	RT_CHANNEL_DOMAIN_FCC1_FCC8 = 0x46,
	RT_CHANNEL_DOMAIN_WORLD_ETSI6 = 0x47,
	RT_CHANNEL_DOMAIN_WORLD_ETSI7 = 0x48,
	RT_CHANNEL_DOMAIN_WORLD_ETSI8 = 0x49,
	RT_CHANNEL_DOMAIN_WORLD_ETSI9 = 0x50,
	RT_CHANNEL_DOMAIN_WORLD_ETSI10 = 0x51,
	RT_CHANNEL_DOMAIN_WORLD_ETSI11 = 0x52,
	RT_CHANNEL_DOMAIN_FCC1_NCC4 = 0x53,
	RT_CHANNEL_DOMAIN_WORLD_ETSI12 = 0x54,
	RT_CHANNEL_DOMAIN_FCC1_FCC9 = 0x55,
	RT_CHANNEL_DOMAIN_WORLD_ETSI13 = 0x56,
	RT_CHANNEL_DOMAIN_FCC1_FCC10 = 0x57,
	/*  Add new channel plan above this line =============== */
	RT_CHANNEL_DOMAIN_MAX,
	RT_CHANNEL_DOMAIN_REALTEK_DEFINE = 0x7F,
पूर्ण;

क्रमागत अणु
	RT_CHANNEL_DOMAIN_2G_WORLD = 0x00,		/* Worldwird 13 */
	RT_CHANNEL_DOMAIN_2G_ETSI1 = 0x01,		/* Europe */
	RT_CHANNEL_DOMAIN_2G_FCC1 = 0x02,		/* US */
	RT_CHANNEL_DOMAIN_2G_MKK1 = 0x03,		/* Japan */
	RT_CHANNEL_DOMAIN_2G_ETSI2 = 0x04,		/* France */
	RT_CHANNEL_DOMAIN_2G_GLOBAL = 0x05,		/* Global करोमुख्य */
	RT_CHANNEL_DOMAIN_2G_शून्य = 0x06,
	/*  Add new channel plan above this line =============== */
	RT_CHANNEL_DOMAIN_2G_MAX,
पूर्ण;

क्रमागत अणु
	RT_CHANNEL_DOMAIN_5G_शून्य = 0x00,
	RT_CHANNEL_DOMAIN_5G_ETSI1 = 0x01,		/* Europe */
	RT_CHANNEL_DOMAIN_5G_ETSI2 = 0x02,		/* Australia, New Zealand */
	RT_CHANNEL_DOMAIN_5G_ETSI3 = 0x03,		/* Russia */
	RT_CHANNEL_DOMAIN_5G_FCC1 = 0x04,		/* US */
	RT_CHANNEL_DOMAIN_5G_FCC2 = 0x05,		/* FCC o/w DFS Channels */
	RT_CHANNEL_DOMAIN_5G_FCC3 = 0x06,		/* India, Mexico */
	RT_CHANNEL_DOMAIN_5G_FCC4 = 0x07,		/* Venezuela */
	RT_CHANNEL_DOMAIN_5G_FCC5 = 0x08,		/* China */
	RT_CHANNEL_DOMAIN_5G_FCC6 = 0x09,		/* Israel */
	RT_CHANNEL_DOMAIN_5G_FCC7_IC1 = 0x0A,	/* US, Canada */
	RT_CHANNEL_DOMAIN_5G_KCC1 = 0x0B,		/* Korea */
	RT_CHANNEL_DOMAIN_5G_MKK1 = 0x0C,		/* Japan */
	RT_CHANNEL_DOMAIN_5G_MKK2 = 0x0D,		/* Japan (W52, W53) */
	RT_CHANNEL_DOMAIN_5G_MKK3 = 0x0E,		/* Japan (W56) */
	RT_CHANNEL_DOMAIN_5G_NCC1 = 0x0F,		/* Taiwan */
	RT_CHANNEL_DOMAIN_5G_NCC2 = 0x10,		/* Taiwan o/w DFS */
	RT_CHANNEL_DOMAIN_5G_NCC3 = 0x11,		/* Taiwan w/o DFS, Band4 only */
	RT_CHANNEL_DOMAIN_5G_ETSI4 = 0x12,		/* Europe w/o DFS, Band1 only */
	RT_CHANNEL_DOMAIN_5G_ETSI5 = 0x13,		/* Australia, New Zealand(w/o Weather radar) */
	RT_CHANNEL_DOMAIN_5G_FCC8 = 0x14,		/* Latin America */
	RT_CHANNEL_DOMAIN_5G_ETSI6 = 0x15,		/* Israel, Bahrain, Egypt, India, China, Malaysia */
	RT_CHANNEL_DOMAIN_5G_ETSI7 = 0x16,		/* China */
	RT_CHANNEL_DOMAIN_5G_ETSI8 = 0x17,		/* Jordan */
	RT_CHANNEL_DOMAIN_5G_ETSI9 = 0x18,		/* Lebanon */
	RT_CHANNEL_DOMAIN_5G_ETSI10 = 0x19,		/* Qatar */
	RT_CHANNEL_DOMAIN_5G_ETSI11 = 0x1A,		/* Russia */
	RT_CHANNEL_DOMAIN_5G_NCC4 = 0x1B,		/* Taiwan, (w/o Weather radar) */
	RT_CHANNEL_DOMAIN_5G_ETSI12 = 0x1C,		/* Inकरोnesia */
	RT_CHANNEL_DOMAIN_5G_FCC9 = 0x1D,		/* w/o Weather radar) */
	RT_CHANNEL_DOMAIN_5G_ETSI13 = 0x1E,		/* w/o Weather radar) */
	RT_CHANNEL_DOMAIN_5G_FCC10 = 0x1F,		/* Argentina (w/o Weather radar) */
	/*  Add new channel plan above this line =============== */
	/*  Driver Self Defined ===== */
	RT_CHANNEL_DOMAIN_5G_FCC = 0x20,
	RT_CHANNEL_DOMAIN_5G_JAPAN_NO_DFS = 0x21,
	RT_CHANNEL_DOMAIN_5G_FCC4_NO_DFS = 0x22,
	RT_CHANNEL_DOMAIN_5G_MAX,
पूर्ण;

#घोषणा rtw_is_channel_plan_valid(chplan) (chplan < RT_CHANNEL_DOMAIN_MAX || chplan == RT_CHANNEL_DOMAIN_REALTEK_DEFINE)

काष्ठा rt_channel_plan अणु
	अचिन्हित अक्षर Channel[MAX_CHANNEL_NUM];
	अचिन्हित अक्षर Len;
पूर्ण;

काष्ठा rt_channel_plan_2g अणु
	अचिन्हित अक्षर Channel[MAX_CHANNEL_NUM_2G];
	अचिन्हित अक्षर Len;
पूर्ण;

काष्ठा rt_channel_plan_5g अणु
	अचिन्हित अक्षर Channel[MAX_CHANNEL_NUM_5G];
	अचिन्हित अक्षर Len;
पूर्ण;

काष्ठा rt_channel_plan_map अणु
	अचिन्हित अक्षर Index2G;
	अचिन्हित अक्षर Index5G;
पूर्ण;

क्रमागत अणु
	HT_IOT_PEER_UNKNOWN			= 0,
	HT_IOT_PEER_REALTEK			= 1,
	HT_IOT_PEER_REALTEK_92SE		= 2,
	HT_IOT_PEER_BROADCOM		= 3,
	HT_IOT_PEER_RALINK			= 4,
	HT_IOT_PEER_ATHEROS			= 5,
	HT_IOT_PEER_CISCO				= 6,
	HT_IOT_PEER_MERU				= 7,
	HT_IOT_PEER_MARVELL			= 8,
	HT_IOT_PEER_REALTEK_SOFTAP	= 9,/*  peer is RealTek SOFT_AP, by Bohn, 2009.12.17 */
	HT_IOT_PEER_SELF_SOFTAP			= 10, /*  Self is SoftAP */
	HT_IOT_PEER_AIRGO				= 11,
	HT_IOT_PEER_INTEL				= 12,
	HT_IOT_PEER_RTK_APCLIENT		= 13,
	HT_IOT_PEER_REALTEK_81XX		= 14,
	HT_IOT_PEER_REALTEK_WOW			= 15,
	HT_IOT_PEER_REALTEK_JAGUAR_BCUTAP = 16,
	HT_IOT_PEER_REALTEK_JAGUAR_CCUTAP = 17,
	HT_IOT_PEER_MAX					= 18
पूर्ण;


क्रमागत अणु
	SCAN_DISABLE = 0,
	SCAN_START = 1,
	SCAN_TXशून्य = 2,
	SCAN_PROCESS = 3,
	SCAN_COMPLETE = 4,
	SCAN_STATE_MAX,
पूर्ण;

काष्ठा mlme_handler अणु
	अचिन्हित पूर्णांक   num;
	अक्षर *str;
	अचिन्हित पूर्णांक (*func)(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
पूर्ण;

काष्ठा action_handler अणु
	अचिन्हित पूर्णांक   num;
	अक्षर *str;
	अचिन्हित पूर्णांक (*func)(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
पूर्ण;

काष्ठा	ss_res अणु
	पूर्णांक	state;
	पूर्णांक	bss_cnt;
	पूर्णांक	channel_idx;
	पूर्णांक	scan_mode;
	u8 ssid_num;
	u8 ch_num;
	काष्ठा ndis_802_11_ssid ssid[RTW_SSID_SCAN_AMOUNT];
	काष्ठा rtw_ieee80211_channel ch[RTW_CHANNEL_SCAN_AMOUNT];
पूर्ण;

/* define AP_MODE				0x0C */
/* define STATION_MODE	0x08 */
/* define AD_HOC_MODE		0x04 */
/* define NO_LINK_MODE	0x00 */

#घोषणा		WIFI_FW_शून्य_STATE			_HW_STATE_NOLINK_
#घोषणा	WIFI_FW_STATION_STATE		_HW_STATE_STATION_
#घोषणा	WIFI_FW_AP_STATE				_HW_STATE_AP_
#घोषणा	WIFI_FW_ADHOC_STATE			_HW_STATE_ADHOC_

#घोषणा	WIFI_FW_AUTH_शून्य			0x00000100
#घोषणा	WIFI_FW_AUTH_STATE			0x00000200
#घोषणा	WIFI_FW_AUTH_SUCCESS			0x00000400

#घोषणा	WIFI_FW_ASSOC_STATE			0x00002000
#घोषणा	WIFI_FW_ASSOC_SUCCESS		0x00004000

#घोषणा	WIFI_FW_LINKING_STATE		(WIFI_FW_AUTH_शून्य | WIFI_FW_AUTH_STATE | WIFI_FW_AUTH_SUCCESS | WIFI_FW_ASSOC_STATE)

काष्ठा FW_Sta_Info अणु
	काष्ठा sta_info *psta;
	u32 status;
	u32 rx_pkt;
	u32 retry;
	NDIS_802_11_RATES_EX  SupportedRates;
पूर्ण;

/*
 * Usage:
 * When one अगरace acted as AP mode and the other अगरace is STA mode and scanning,
 * it should चयन back to AP's operating channel periodically.
 * Parameters info:
 * When the driver scanned RTW_SCAN_NUM_OF_CH channels, it would चयन back to AP's operating channel क्रम
 * RTW_STAY_AP_CH_MILLISECOND * SURVEY_TO milliseconds.
 * Example:
 * For chip supports 2.4G + 5GHz and AP mode is operating in channel 1,
 * RTW_SCAN_NUM_OF_CH is 8, RTW_STAY_AP_CH_MILLISECOND is 3 and SURVEY_TO is 100.
 * When it's STA mode माला_लो set_scan command,
 * it would
 * 1. Doing the scan on channel 1.2.3.4.5.6.7.8
 * 2. Back to channel 1 क्रम 300 milliseconds
 * 3. Go through करोing site survey on channel 9.10.11.36.40.44.48.52
 * 4. Back to channel 1 क्रम 300 milliseconds
 * 5. ... and so on, till survey करोne.
 */
काष्ठा mlme_ext_info अणु
	u32 state;
	u32 reauth_count;
	u32 reassoc_count;
	u32 link_count;
	u32 auth_seq;
	u32 auth_algo;	/*  802.11 auth, could be खोलो, shared, स्वतः */
	u32 authModeToggle;
	u32 enc_algo;/* encrypt algorithm; */
	u32 key_index;	/*  this is only valid क्रम legendary wep, 0~3 क्रम key id. */
	u32 iv;
	u8 chg_txt[128];
	u16 aid;
	u16 bcn_पूर्णांकerval;
	u16 capability;
	u8 assoc_AP_venकरोr;
	u8 slotTime;
	u8 preamble_mode;
	u8 WMM_enable;
	u8 ERP_enable;
	u8 ERP_IE;
	u8 HT_enable;
	u8 HT_caps_enable;
	u8 HT_info_enable;
	u8 HT_protection;
	u8 turboMode_cts2self;
	u8 turboMode_rtsen;
	u8 SM_PS;
	u8 agg_enable_biपंचांगap;
	u8 ADDBA_retry_count;
	u8 candidate_tid_biपंचांगap;
	u8 dialogToken;
	/*  Accept ADDBA Request */
	bool accept_addba_req;
	u8 bwmode_updated;
	u8 hidden_ssid_mode;
	u8 VHT_enable;

	काष्ठा ADDBA_request		ADDBA_req;
	काष्ठा WMM_para_element	WMM_param;
	काष्ठा HT_caps_element	HT_caps;
	काष्ठा HT_info_element		HT_info;
	काष्ठा wlan_bssid_ex			network;/* join network or bss_network, अगर in ap mode, it is the same to cur_network.network */
	काष्ठा FW_Sta_Info		FW_sta_info[NUM_STA];
पूर्ण;

/*  The channel inक्रमmation about this channel including joining, scanning, and घातer स्थिरraपूर्णांकs. */
काष्ठा rt_channel_info अणु
	u8 		ChannelNum;		/*  The channel number. */
	क्रमागत rt_scan_type	ScanType;		/*  Scan type such as passive or active scan. */
पूर्ण;

पूर्णांक rtw_ch_set_search_ch(काष्ठा rt_channel_info *ch_set, स्थिर u32 ch);
bool rtw_mlme_band_check(काष्ठा adapter *adapter, स्थिर u32 ch);

/*  P2P_MAX_REG_CLASSES - Maximum number of regulatory classes */
#घोषणा P2P_MAX_REG_CLASSES 10

/*  P2P_MAX_REG_CLASS_CHANNELS - Maximum number of channels per regulatory class */
#घोषणा P2P_MAX_REG_CLASS_CHANNELS 20

/*   काष्ठा p2p_channels - List of supported channels */
काष्ठा p2p_channels अणु
	/*  काष्ठा p2p_reg_class - Supported regulatory class */
	काष्ठा p2p_reg_class अणु
		/*  reg_class - Regulatory class (IEEE 802.11-2007, Annex J) */
		u8 reg_class;

		/*  channel - Supported channels */
		u8 channel[P2P_MAX_REG_CLASS_CHANNELS];

		/*  channels - Number of channel entries in use */
		माप_प्रकार channels;
	पूर्ण reg_class[P2P_MAX_REG_CLASSES];

	/*  reg_classes - Number of reg_class entries in use */
	माप_प्रकार reg_classes;
पूर्ण;

काष्ठा p2p_oper_class_map अणु
	क्रमागत hw_mode अणुIEEE80211G, IEEE80211Aपूर्ण mode;
	u8 op_class;
	u8 min_chan;
	u8 max_chan;
	u8 inc;
	क्रमागत अणु BW20, BW40PLUS, BW40MINUS पूर्ण bw;
पूर्ण;

काष्ठा mlme_ext_priv अणु
	काष्ठा adapter	*padapter;
	u8 mlmeext_init;
	atomic_t		event_seq;
	u16 mgnt_seq;
	u16 sa_query_seq;
	u64 mgnt_80211w_IPN;
	u64 mgnt_80211w_IPN_rx;
	/* काष्ठा fw_priv fwpriv; */

	अचिन्हित अक्षर cur_channel;
	अचिन्हित अक्षर cur_bwmode;
	अचिन्हित अक्षर cur_ch_offset;/* PRIME_CHNL_OFFSET */
	अचिन्हित अक्षर cur_wireless_mode;	/*  NETWORK_TYPE */

	अचिन्हित अक्षर max_chan_nums;
	काष्ठा rt_channel_info		channel_set[MAX_CHANNEL_NUM];
	काष्ठा p2p_channels channel_list;
	अचिन्हित अक्षर basicrate[NumRates];
	अचिन्हित अक्षर datarate[NumRates];
	अचिन्हित अक्षर शेष_supported_mcs_set[16];

	काष्ठा ss_res		sitesurvey_res;
	काष्ठा mlme_ext_info mlmext_info;/* क्रम sta/adhoc mode, including current scanning/connecting/connected related info. */
                                                     /* क्रम ap mode, network includes ap's cap_info */
	काष्ठा समयr_list		survey_समयr;
	काष्ठा समयr_list		link_समयr;
	काष्ठा समयr_list		sa_query_समयr;
	/* काष्ठा समयr_list		ADDBA_समयr; */
	u16 		chan_scan_समय;
	अचिन्हित दीर्घ last_scan_समय;
	u8 scan_पात;
	u8 tx_rate; /*  TXRATE when USERATE is set. */

	u32 retry; /* retry क्रम issue probereq */

	u64 TSFValue;

	/* क्रम LPS-32K to adaptive bcn early and समयout */
	u8 adaptive_tsf_करोne;
	u32 bcn_delay_cnt[9];
	u32 bcn_delay_ratio[9];
	u32 bcn_cnt;
	u8 DrvBcnEarly;
	u8 DrvBcnTimeOut;

	अचिन्हित अक्षर bstart_bss;

	u8 update_channel_plan_by_ap_करोne;

	/* recv_decache check क्रम Action_खुला frame */
	u8 action_खुला_dialog_token;
	u16  action_खुला_rxseq;

	u8 active_keep_alive_check;
#अगर_घोषित DBG_FIXED_CHAN
	u8 fixed_chan;
#पूर्ण_अगर

पूर्ण;

व्योम init_mlme_शेष_rate_set(काष्ठा adapter *padapter);
व्योम init_mlme_ext_priv(काष्ठा adapter *padapter);
पूर्णांक init_hw_mlme_ext(काष्ठा adapter *padapter);
व्योम मुक्त_mlme_ext_priv(काष्ठा mlme_ext_priv *pmlmeext);
बाह्य व्योम init_mlme_ext_समयr(काष्ठा adapter *padapter);
बाह्य व्योम init_addba_retry_समयr(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
बाह्य काष्ठा xmit_frame *alloc_mgtxmitframe(काष्ठा xmit_priv *pxmitpriv);

/* व्योम fill_fwpriv(काष्ठा adapter *padapter, काष्ठा fw_priv *pfwpriv); */

u8 networktype_to_raid_ex(काष्ठा adapter *adapter, काष्ठा sta_info *psta);

व्योम get_rate_set(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbssrate, पूर्णांक *bssrate_len);
व्योम set_mcs_rate_by_mask(u8 *mcs_set, u32 mask);
व्योम UpdateBrateTbl(काष्ठा adapter *padapter, u8 *mBratesOS);
व्योम UpdateBrateTblForSoftAP(u8 *bssrateset, u32 bssratelen);

व्योम Save_DM_Func_Flag(काष्ठा adapter *padapter);
व्योम Restore_DM_Func_Flag(काष्ठा adapter *padapter);
व्योम Switch_DM_Func(काष्ठा adapter *padapter, u32 mode, u8 enable);

व्योम Set_MSR(काष्ठा adapter *padapter, u8 type);

u8 rtw_get_oper_ch(काष्ठा adapter *adapter);
व्योम rtw_set_oper_ch(काष्ठा adapter *adapter, u8 ch);
u8 rtw_get_oper_bw(काष्ठा adapter *adapter);
व्योम rtw_set_oper_bw(काष्ठा adapter *adapter, u8 bw);
u8 rtw_get_oper_choffset(काष्ठा adapter *adapter);
व्योम rtw_set_oper_choffset(काष्ठा adapter *adapter, u8 offset);
u8 rtw_get_center_ch(u8 channel, u8 chnl_bw, u8 chnl_offset);
अचिन्हित दीर्घ rtw_get_on_cur_ch_समय(काष्ठा adapter *adapter);

व्योम set_channel_bwmode(काष्ठा adapter *padapter, अचिन्हित अक्षर channel, अचिन्हित अक्षर channel_offset, अचिन्हित लघु bwmode);
व्योम SelectChannel(काष्ठा adapter *padapter, अचिन्हित अक्षर channel);

अचिन्हित पूर्णांक decide_रुको_क्रम_beacon_समयout(अचिन्हित पूर्णांक bcn_पूर्णांकerval);

व्योम पढ़ो_cam(काष्ठा adapter *padapter, u8 entry, u8 *get_key);

/* modअगरy HW only */
व्योम _ग_लिखो_cam(काष्ठा adapter *padapter, u8 entry, u16 ctrl, u8 *mac, u8 *key);
व्योम _clear_cam_entry(काष्ठा adapter *padapter, u8 entry);

/* modअगरy both HW and cache */
व्योम ग_लिखो_cam(काष्ठा adapter *padapter, u8 id, u16 ctrl, u8 *mac, u8 *key);
व्योम clear_cam_entry(काष्ठा adapter *padapter, u8 id);

/* modअगरy cache only */
व्योम ग_लिखो_cam_cache(काष्ठा adapter *adapter, u8 id, u16 ctrl, u8 *mac, u8 *key);
व्योम clear_cam_cache(काष्ठा adapter *adapter, u8 id);

व्योम invalidate_cam_all(काष्ठा adapter *padapter);


पूर्णांक allocate_fw_sta_entry(काष्ठा adapter *padapter);
व्योम flush_all_cam_entry(काष्ठा adapter *padapter);

व्योम site_survey(काष्ठा adapter *padapter);
u8 collect_bss_info(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame, काष्ठा wlan_bssid_ex *bssid);
व्योम update_network(काष्ठा wlan_bssid_ex *dst, काष्ठा wlan_bssid_ex *src, काष्ठा adapter *padapter, bool update_ie);

u8 *get_my_bssid(काष्ठा wlan_bssid_ex *pnetwork);
u16 get_beacon_पूर्णांकerval(काष्ठा wlan_bssid_ex *bss);

पूर्णांक is_client_associated_to_ap(काष्ठा adapter *padapter);
पूर्णांक is_client_associated_to_ibss(काष्ठा adapter *padapter);
पूर्णांक is_IBSS_empty(काष्ठा adapter *padapter);

अचिन्हित अक्षर check_assoc_AP(u8 *pframe, uपूर्णांक len);

पूर्णांक WMM_param_handler(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE);
व्योम WMMOnAssocRsp(काष्ठा adapter *padapter);

व्योम HT_caps_handler(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE);
व्योम HT_info_handler(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE);
व्योम HTOnAssocRsp(काष्ठा adapter *padapter);

व्योम ERP_IE_handler(काष्ठा adapter *padapter, काष्ठा ndis_80211_var_ie *pIE);
व्योम VCS_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
व्योम update_ldpc_stbc_cap(काष्ठा sta_info *psta);

व्योम update_beacon_info(काष्ठा adapter *padapter, u8 *pframe, uपूर्णांक len, काष्ठा sta_info *psta);
पूर्णांक rtw_check_bcn_info(काष्ठा adapter *Adapter, u8 *pframe, u32 packet_len);
व्योम update_IOT_info(काष्ठा adapter *padapter);
व्योम update_capinfo(काष्ठा adapter *Adapter, u16 updateCap);
व्योम update_wireless_mode(काष्ठा adapter *padapter);
व्योम update_sta_basic_rate(काष्ठा sta_info *psta, u8 wireless_mode);
पूर्णांक update_sta_support_rate(काष्ठा adapter *padapter, u8 *pvar_ie, uपूर्णांक var_ie_len, पूर्णांक cam_idx);

/* क्रम sta/adhoc mode */
व्योम update_sta_info(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
व्योम Update_RA_Entry(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
व्योम set_sta_rate(काष्ठा adapter *padapter, काष्ठा sta_info *psta);

अचिन्हित पूर्णांक receive_disconnect(काष्ठा adapter *padapter, अचिन्हित अक्षर *MacAddr, अचिन्हित लघु reason);

अचिन्हित अक्षर get_highest_rate_idx(u32 mask);
पूर्णांक support_लघु_GI(काष्ठा adapter *padapter, काष्ठा HT_caps_element *pHT_caps, u8 bwmode);
अचिन्हित पूर्णांक is_ap_in_tkip(काष्ठा adapter *padapter);

s16 rtw_camid_search(काष्ठा adapter *adapter, u8 *addr, s16 kid);
s16 rtw_camid_alloc(काष्ठा adapter *adapter, काष्ठा sta_info *sta, u8 kid);
व्योम rtw_camid_मुक्त(काष्ठा adapter *adapter, u8 cam_id);

बाह्य व्योम rtw_alloc_macid(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
बाह्य व्योम rtw_release_macid(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
बाह्य u8 rtw_search_max_mac_id(काष्ठा adapter *padapter);

व्योम report_join_res(काष्ठा adapter *padapter, पूर्णांक res);
व्योम report_survey_event(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
व्योम report_surveyकरोne_event(काष्ठा adapter *padapter);
व्योम report_del_sta_event(काष्ठा adapter *padapter, अचिन्हित अक्षर *MacAddr, अचिन्हित लघु reason);
व्योम report_add_sta_event(काष्ठा adapter *padapter, अचिन्हित अक्षर *MacAddr, पूर्णांक cam_idx);
व्योम report_wmm_edca_update(काष्ठा adapter *padapter);

u8 chk_bmc_sleepq_cmd(काष्ठा adapter *padapter);
बाह्य u8 set_tx_beacon_cmd(काष्ठा adapter *padapter);
अचिन्हित पूर्णांक setup_beacon_frame(काष्ठा adapter *padapter, अचिन्हित अक्षर *beacon_frame);
व्योम update_mgnt_tx_rate(काष्ठा adapter *padapter, u8 rate);
व्योम update_mgntframe_attrib(काष्ठा adapter *padapter, काष्ठा pkt_attrib *pattrib);
व्योम update_mgntframe_attrib_addr(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe);
व्योम dump_mgntframe(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe);
s32 dump_mgntframe_and_रुको(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe, पूर्णांक समयout_ms);
s32 dump_mgntframe_and_रुको_ack(काष्ठा adapter *padapter, काष्ठा xmit_frame *pmgntframe);

व्योम issue_beacon(काष्ठा adapter *padapter, पूर्णांक समयout_ms);
व्योम issue_probersp(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, u8 is_valid_p2p_probereq);
व्योम issue_assocreq(काष्ठा adapter *padapter);
व्योम issue_asocrsp(काष्ठा adapter *padapter, अचिन्हित लघु status, काष्ठा sta_info *pstat, पूर्णांक pkt_type);
व्योम issue_auth(काष्ठा adapter *padapter, काष्ठा sta_info *psta, अचिन्हित लघु status);
व्योम issue_probereq(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *pssid, u8 *da);
s32 issue_probereq_ex(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *pssid, u8 *da, u8 ch, bool append_wps, पूर्णांक try_cnt, पूर्णांक रुको_ms);
पूर्णांक issue_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, अचिन्हित पूर्णांक घातer_mode, पूर्णांक try_cnt, पूर्णांक रुको_ms);
s32 issue_nulldata_in_पूर्णांकerrupt(काष्ठा adapter *padapter, u8 *da);
पूर्णांक issue_qos_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, u16 tid, पूर्णांक try_cnt, पूर्णांक रुको_ms);
पूर्णांक issue_deauth(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, अचिन्हित लघु reason);
पूर्णांक issue_deauth_ex(काष्ठा adapter *padapter, u8 *da, अचिन्हित लघु reason, पूर्णांक try_cnt, पूर्णांक रुको_ms);
व्योम issue_action_BA(काष्ठा adapter *padapter, अचिन्हित अक्षर *raddr, अचिन्हित अक्षर action, अचिन्हित लघु status);
व्योम issue_action_SA_Query(काष्ठा adapter *padapter, अचिन्हित अक्षर *raddr, अचिन्हित अक्षर action, अचिन्हित लघु tid);
अचिन्हित पूर्णांक send_delba(काष्ठा adapter *padapter, u8 initiator, u8 *addr);
अचिन्हित पूर्णांक send_beacon(काष्ठा adapter *padapter);

व्योम start_clnt_assoc(काष्ठा adapter *padapter);
व्योम start_clnt_auth(काष्ठा adapter *padapter);
व्योम start_clnt_join(काष्ठा adapter *padapter);
व्योम start_create_ibss(काष्ठा adapter *padapter);

अचिन्हित पूर्णांक OnAssocReq(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnAssocRsp(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnProbeReq(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnProbeRsp(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक DoReserved(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnBeacon(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnAtim(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnDisassoc(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnAuth(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnAuthClient(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnDeAuth(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnAction(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);

अचिन्हित पूर्णांक on_action_spct(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnAction_back(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक on_action_खुला(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnAction_ht(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);
अचिन्हित पूर्णांक OnAction_sa_query(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame);

व्योम mlmeext_joinbss_event_callback(काष्ठा adapter *padapter, पूर्णांक join_res);
व्योम mlmeext_sta_del_event_callback(काष्ठा adapter *padapter);
व्योम mlmeext_sta_add_event_callback(काष्ठा adapter *padapter, काष्ठा sta_info *psta);

व्योम linked_status_chk(काष्ठा adapter *padapter);

व्योम _linked_info_dump(काष्ठा adapter *padapter);

व्योम survey_समयr_hdl(काष्ठा समयr_list *t);
व्योम link_समयr_hdl(काष्ठा समयr_list *t);
व्योम addba_समयr_hdl(काष्ठा समयr_list *t);
व्योम sa_query_समयr_hdl(काष्ठा समयr_list *t);
/* व्योम reauth_समयr_hdl(काष्ठा adapter *padapter); */
/* व्योम reassoc_समयr_hdl(काष्ठा adapter *padapter); */

#घोषणा set_survey_समयr(mlmeext, ms) \
	करो अणु \
		_set_समयr(&(mlmeext)->survey_समयr, (ms)); \
	पूर्ण जबतक (0)

#घोषणा set_link_समयr(mlmeext, ms) \
	करो अणु \
		_set_समयr(&(mlmeext)->link_समयr, (ms)); \
	पूर्ण जबतक (0)
#घोषणा set_sa_query_समयr(mlmeext, ms) \
	करो अणु \
		_set_समयr(&(mlmeext)->sa_query_समयr, (ms)); \
	पूर्ण जबतक (0)

बाह्य व्योम process_addba_req(काष्ठा adapter *padapter, u8 *paddba_req, u8 *addr);

बाह्य व्योम update_TSF(काष्ठा mlme_ext_priv *pmlmeext, u8 *pframe, uपूर्णांक len);
बाह्य व्योम correct_TSF(काष्ठा adapter *padapter, काष्ठा mlme_ext_priv *pmlmeext);
बाह्य व्योम adaptive_early_32k(काष्ठा mlme_ext_priv *pmlmeext, u8 *pframe, uपूर्णांक len);
बाह्य u8 traffic_status_watchकरोg(काष्ठा adapter *padapter, u8 from_समयr);

पूर्णांक rtw_chk_start_clnt_join(काष्ठा adapter *padapter, u8 *ch, u8 *bw, u8 *offset);
पूर्णांक rtw_get_ch_setting_जोड़(काष्ठा adapter *adapter, u8 *ch, u8 *bw, u8 *offset);

काष्ठा cmd_hdl अणु
	uपूर्णांक	parmsize;
	u8 (*h2cfuns)(काष्ठा adapter *padapter, u8 *pbuf);
पूर्ण;


u8 पढ़ो_macreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 ग_लिखो_macreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 पढ़ो_bbreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 ग_लिखो_bbreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 पढ़ो_rfreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 ग_लिखो_rfreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);


u8 शून्य_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 join_cmd_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 disconnect_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 createbss_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 setopmode_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 sitesurvey_cmd_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 setauth_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 setkey_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 set_stakey_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 set_assocsta_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 del_assocsta_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 add_ba_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);

u8 mlme_evt_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 h2c_msg_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 chk_bmc_sleepq_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 tx_beacon_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 set_ch_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 set_chplan_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 set_csa_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);	/* Kurt: Handling DFS channel चयन announcement ie. */
u8 tdls_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 run_in_thपढ़ो_hdl(काष्ठा adapter *padapter, u8 *pbuf);


#घोषणा GEN_DRV_CMD_HANDLER(size, cmd)	अणुsize, &cmd ## _hdlपूर्ण,
#घोषणा GEN_MLME_EXT_HANDLER(size, cmd)	अणुsize, cmdपूर्ण,

काष्ठा C2HEvent_Header अणु

#अगर_घोषित __LITTLE_ENDIAN

	अचिन्हित पूर्णांक len:16;
	अचिन्हित पूर्णांक ID:8;
	अचिन्हित पूर्णांक seq:8;
#अन्यथा
	अचिन्हित पूर्णांक seq:8;
	अचिन्हित पूर्णांक ID:8;
	अचिन्हित पूर्णांक len:16;
#पूर्ण_अगर
	अचिन्हित पूर्णांक rsvd;
पूर्ण;

व्योम rtw_dummy_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_fwdbg_event_callback(काष्ठा adapter *adapter, u8 *pbuf);

क्रमागत अणु
	GEN_EVT_CODE(_Read_MACREG) = 0, /*0*/
	GEN_EVT_CODE(_Read_BBREG),
	GEN_EVT_CODE(_Read_RFREG),
	GEN_EVT_CODE(_Read_EEPROM),
	GEN_EVT_CODE(_Read_EFUSE),
	GEN_EVT_CODE(_Read_CAM),			/*5*/
	GEN_EVT_CODE(_Get_BasicRate),
	GEN_EVT_CODE(_Get_DataRate),
	GEN_EVT_CODE(_Survey),	 /*8*/
	GEN_EVT_CODE(_SurveyDone),	 /*9*/

	GEN_EVT_CODE(_JoinBss), /*10*/
	GEN_EVT_CODE(_AddSTA),
	GEN_EVT_CODE(_DelSTA),
	GEN_EVT_CODE(_AtimDone),
	GEN_EVT_CODE(_TX_Report),
	GEN_EVT_CODE(_CCX_Report),			/*15*/
	GEN_EVT_CODE(_DTM_Report),
	GEN_EVT_CODE(_TX_Rate_Statistics),
	GEN_EVT_CODE(_C2HLBK),
	GEN_EVT_CODE(_FWDBG),
	GEN_EVT_CODE(_C2HFEEDBACK),               /*20*/
	GEN_EVT_CODE(_ADDBA),
	GEN_EVT_CODE(_C2HBCN),
	GEN_EVT_CODE(_ReportPwrState),		/* filen: only क्रम PCIE, USB */
	GEN_EVT_CODE(_CloseRF),				/* filen: only क्रम PCIE, work around ASPM */
	GEN_EVT_CODE(_WMM),					/*25*/
	MAX_C2HEVT
पूर्ण;


#अगर_घोषित _RTW_MLME_EXT_C_

अटल काष्ठा fwevent wlanevents[] =
अणु
	अणु0, rtw_dummy_event_callbackपूर्ण,	/*0*/
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, &rtw_survey_event_callbackपूर्ण,		/*8*/
	अणुमाप(काष्ठा surveyकरोne_event), &rtw_surveyकरोne_event_callbackपूर्ण,	/*9*/

	अणु0, &rtw_joinbss_event_callbackपूर्ण,		/*10*/
	अणुमाप(काष्ठा stassoc_event), &rtw_stassoc_event_callbackपूर्ण,
	अणुमाप(काष्ठा stadel_event), &rtw_stadel_event_callbackपूर्ण,
	अणु0, &rtw_atimकरोne_event_callbackपूर्ण,
	अणु0, rtw_dummy_event_callbackपूर्ण,
	अणु0, शून्यपूर्ण,	/*15*/
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, rtw_fwdbg_event_callbackपूर्ण,
	अणु0, शून्यपूर्ण,	 /*20*/
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, &rtw_cpwm_event_callbackपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, &rtw_wmm_event_callbackपूर्ण,

पूर्ण;

#पूर्ण_अगर/* _RTL8192C_CMD_C_ */

#पूर्ण_अगर
