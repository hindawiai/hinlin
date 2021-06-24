<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_MLME_EXT_H_
#घोषणा __RTW_MLME_EXT_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <wlan_bssdef.h>

/*	Commented by Albert 20101105 */
/*	Increase the SURVEY_TO value from 100 to 150  ( 100ms to 150ms ) */
/*	The Realtek 8188CE SoftAP will spend around 100ms to send the probe response after receiving the probe request. */
/*	So, this driver tried to extend the dwell समय क्रम each scanning channel. */
/*	This will increase the chance to receive the probe response from SoftAP. */

#घोषणा SURVEY_TO		(100)
#घोषणा REAUTH_TO		(300) /* 50) */
#घोषणा REASSOC_TO		(300) /* 50) */
/* define DISCONNECT_TO	(3000) */
#घोषणा ADDBA_TO			(2000)

#घोषणा LINKED_TO (1) /* unit:2 sec, 1x2=2 sec */

#घोषणा REAUTH_LIMIT	(4)
#घोषणा REASSOC_LIMIT	(4)
#घोषणा READDBA_LIMIT	(2)

#घोषणा ROAMING_LIMIT	8

#घोषणा	DYNAMIC_FUNC_DISABLE			(0x0)

/*  ====== ODM_ABILITY_E ======== */
/*  BB ODM section BIT 0-15 */
#घोषणा	DYNAMIC_BB_DIG				BIT(0)
#घोषणा	DYNAMIC_BB_RA_MASK			BIT(1)
#घोषणा	DYNAMIC_BB_DYNAMIC_TXPWR	BIT(2)
#घोषणा	DYNAMIC_BB_BB_FA_CNT			BIT(3)

#घोषणा		DYNAMIC_BB_RSSI_MONITOR		BIT(4)
#घोषणा		DYNAMIC_BB_CCK_PD			BIT(5)
#घोषणा		DYNAMIC_BB_ANT_DIV			BIT(6)
#घोषणा		DYNAMIC_BB_PWR_SAVE			BIT(7)
#घोषणा		DYNAMIC_BB_PWR_TRA			BIT(8)
#घोषणा		DYNAMIC_BB_RATE_ADAPTIVE		BIT(9)
#घोषणा		DYNAMIC_BB_PATH_DIV			BIT(10)
#घोषणा		DYNAMIC_BB_PSD				BIT(11)

/*  MAC DM section BIT 16-23 */
#घोषणा		DYNAMIC_MAC_EDCA_TURBO		BIT(16)
#घोषणा		DYNAMIC_MAC_EARLY_MODE		BIT(17)

/*  RF ODM section BIT 24-31 */
#घोषणा		DYNAMIC_RF_TX_PWR_TRACK		BIT(24)
#घोषणा		DYNAMIC_RF_RX_GAIN_TRACK		BIT(25)
#घोषणा		DYNAMIC_RF_CALIBRATION		BIT(26)

#घोषणा		DYNAMIC_ALL_FUNC_ENABLE		0xFFFFFFF

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

बाह्य स्थिर u8 RTW_WPA_OUI[];
बाह्य स्थिर u8 WPS_OUI[];

/*  Channel Plan Type. */
/*  Note: */
/*	We just add new channel plan when the new channel plan is dअगरferent
 *      from any of the following channel plan.
 */
/*	If you just want to customize the actions(scan period or join actions)
 *      about one of the channel plan,
 */
/*	customize them in काष्ठा rt_channel_info in the RT_CHANNEL_LIST. */
क्रमागत RT_CHANNEL_DOMAIN अणु
	/*  old channel plan mapping =====  */
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
	RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN_2G = 0x41,
	/*  Add new channel plan above this line=============== */
	RT_CHANNEL_DOMAIN_MAX,
	RT_CHANNEL_DOMAIN_REALTEK_DEFINE = 0x7F,
पूर्ण;

क्रमागत RT_CHANNEL_DOMAIN_2G अणु
	RT_CHANNEL_DOMAIN_2G_WORLD = 0x00,		/* Worldwide 13 */
	RT_CHANNEL_DOMAIN_2G_ETSI1 = 0x01,		/* Europe */
	RT_CHANNEL_DOMAIN_2G_FCC1 = 0x02,		/* US */
	RT_CHANNEL_DOMAIN_2G_MKK1 = 0x03,		/* Japan */
	RT_CHANNEL_DOMAIN_2G_ETSI2 = 0x04,		/* France */
	RT_CHANNEL_DOMAIN_2G_शून्य = 0x05,
	/*  Add new channel plan above this line=============== */
	RT_CHANNEL_DOMAIN_2G_MAX,
पूर्ण;

#घोषणा rtw_is_channel_plan_valid(chplan)			\
	(chplan < RT_CHANNEL_DOMAIN_MAX ||			\
	 chplan == RT_CHANNEL_DOMAIN_REALTEK_DEFINE)

काष्ठा rt_channel_plan अणु
	अचिन्हित अक्षर	Channel[MAX_CHANNEL_NUM];
	अचिन्हित अक्षर	Len;
पूर्ण;

काष्ठा rt_channel_plan_2g अणु
	अचिन्हित अक्षर	Channel[MAX_CHANNEL_NUM_2G];
	अचिन्हित अक्षर	Len;
पूर्ण;

काष्ठा rt_channel_plan_map अणु
	अचिन्हित अक्षर	Index2G;
पूर्ण;

क्रमागत Associated_AP अणु
	atherosAP	= 0,
	broadcomAP	= 1,
	ciscoAP		= 2,
	marvellAP	= 3,
	ralinkAP	= 4,
	realtekAP	= 5,
	airgocapAP	= 6,
	unknownAP	= 7,
	maxAP,
पूर्ण;

क्रमागत HT_IOT_PEER अणु
	HT_IOT_PEER_UNKNOWN		= 0,
	HT_IOT_PEER_REALTEK		= 1,
	HT_IOT_PEER_REALTEK_92SE	= 2,
	HT_IOT_PEER_BROADCOM		= 3,
	HT_IOT_PEER_RALINK		= 4,
	HT_IOT_PEER_ATHEROS		= 5,
	HT_IOT_PEER_CISCO		= 6,
	HT_IOT_PEER_MERU		= 7,
	HT_IOT_PEER_MARVELL		= 8,
	HT_IOT_PEER_REALTEK_SOFTAP	= 9,/*  peer is RealTek SOFT_AP */
	HT_IOT_PEER_SELF_SOFTAP		= 10, /*  Self is SoftAP */
	HT_IOT_PEER_AIRGO		= 11,
	HT_IOT_PEER_INTEL		= 12,
	HT_IOT_PEER_RTK_APCLIENT	= 13,
	HT_IOT_PEER_REALTEK_81XX	= 14,
	HT_IOT_PEER_REALTEK_WOW		= 15,
	HT_IOT_PEER_TENDA		= 16,
	HT_IOT_PEER_MAX			= 17
पूर्ण;

क्रमागत SCAN_STATE अणु
	SCAN_DISABLE = 0,
	SCAN_START = 1,
	SCAN_TXशून्य = 2,
	SCAN_PROCESS = 3,
	SCAN_COMPLETE = 4,
	SCAN_STATE_MAX,
पूर्ण;

काष्ठा mlme_handler अणु
	अचिन्हित पूर्णांक num;
	स्थिर अक्षर *str;
	अचिन्हित पूर्णांक (*func)(काष्ठा adapter *adapt, काष्ठा recv_frame *frame);
पूर्ण;

काष्ठा action_handler अणु
	अचिन्हित पूर्णांक num;
	स्थिर अक्षर *str;
	अचिन्हित पूर्णांक (*func)(काष्ठा adapter *adapt, काष्ठा recv_frame *frame);
पूर्ण;

काष्ठा ss_res अणु
	पूर्णांक state;
	पूर्णांक bss_cnt;
	पूर्णांक channel_idx;
	पूर्णांक scan_mode;
	u8 ssid_num;
	u8 ch_num;
	काष्ठा ndis_802_11_ssid ssid[RTW_SSID_SCAN_AMOUNT];
	काष्ठा rtw_ieee80211_channel ch[RTW_CHANNEL_SCAN_AMOUNT];
पूर्ण;

/* define AP_MODE				0x0C */
/* define STATION_MODE	0x08 */
/* define AD_HOC_MODE		0x04 */
/* define NO_LINK_MODE	0x00 */

#घोषणा WIFI_FW_शून्य_STATE		_HW_STATE_NOLINK_
#घोषणा	WIFI_FW_STATION_STATE		_HW_STATE_STATION_
#घोषणा	WIFI_FW_AP_STATE		_HW_STATE_AP_
#घोषणा	WIFI_FW_ADHOC_STATE		_HW_STATE_ADHOC_

#घोषणा	WIFI_FW_AUTH_शून्य		0x00000100
#घोषणा	WIFI_FW_AUTH_STATE		0x00000200
#घोषणा	WIFI_FW_AUTH_SUCCESS		0x00000400

#घोषणा	WIFI_FW_ASSOC_STATE		0x00002000
#घोषणा	WIFI_FW_ASSOC_SUCCESS		0x00004000

#घोषणा	WIFI_FW_LINKING_STATE		(WIFI_FW_AUTH_शून्य |		\
					WIFI_FW_AUTH_STATE |		\
					WIFI_FW_AUTH_SUCCESS |		\
					WIFI_FW_ASSOC_STATE)

काष्ठा FW_Sta_Info अणु
	काष्ठा sta_info	*psta;
	u32	status;
	u32	rx_pkt;
	u32	retry;
	अचिन्हित अक्षर SupportedRates[NDIS_802_11_LENGTH_RATES_EX];
पूर्ण;

/*
 * Usage:
 * When one अगरace acted as AP mode and the other अगरace is STA mode and scanning,
 * it should चयन back to AP's operating channel periodically.
 * Parameters info:
 * When the driver scanned RTW_SCAN_NUM_OF_CH channels, it would चयन back to
 * AP's operating channel क्रम
 * RTW_STAY_AP_CH_MILLISECOND * SURVEY_TO milliseconds.
 * Example:
 * For chip supports 2.4G + 5GHz and AP mode is operating in channel 1,
 * RTW_SCAN_NUM_OF_CH is 8, RTW_STAY_AP_CH_MS is 3 and SURVEY_TO is 100.
 * When it's STA mode माला_लो set_scan command,
 * it would
 * 1. Doing the scan on channel 1.2.3.4.5.6.7.8
 * 2. Back to channel 1 क्रम 300 milliseconds
 * 3. Go through करोing site survey on channel 9.10.11.36.40.44.48.52
 * 4. Back to channel 1 क्रम 300 milliseconds
 * 5. ... and so on, till survey करोne.
 */

काष्ठा mlme_ext_info अणु
	u32	state;
	u32	reauth_count;
	u32	reassoc_count;
	u32	link_count;
	u32	auth_seq;
	u32	auth_algo;	/*  802.11 auth, could be खोलो, shared, स्वतः */
	u32	authModeToggle;
	u32	enc_algo;/* encrypt algorithm; */
	u32	key_index;	/*  this is only valid क्रम legacy wep,
				 *  0~3 क्रम key id.
				 */
	u32	iv;
	u8	chg_txt[128];
	u16	aid;
	u16	bcn_पूर्णांकerval;
	u16	capability;
	u8	assoc_AP_venकरोr;
	u8	slotTime;
	u8	preamble_mode;
	u8	WMM_enable;
	u8	ERP_enable;
	u8	ERP_IE;
	u8	HT_enable;
	u8	HT_caps_enable;
	u8	HT_info_enable;
	u8	HT_protection;
	u8	turboMode_cts2self;
	u8	turboMode_rtsen;
	u8	SM_PS;
	u8	agg_enable_biपंचांगap;
	u8	ADDBA_retry_count;
	u8	candidate_tid_biपंचांगap;
	u8	dialogToken;
	/*  Accept ADDBA Request */
	bool accept_addba_req;
	u8	bwmode_updated;
	u8	hidden_ssid_mode;

	काष्ठा ADDBA_request	ADDBA_req;
	काष्ठा WMM_para_element	WMM_param;
	काष्ठा ieee80211_ht_cap HT_caps;
	काष्ठा HT_info_element	HT_info;
	काष्ठा wlan_bssid_ex	network;/* join network or bss_network,
					 * अगर in ap mode, it is the same
					 * as cur_network.network
					 */
	काष्ठा FW_Sta_Info	FW_sta_info[NUM_STA];
पूर्ण;

/*  The channel inक्रमmation about this channel including joining,
 *  scanning, and घातer स्थिरraपूर्णांकs.
 */
काष्ठा rt_channel_info अणु
	u8	ChannelNum;	/*  The channel number. */
	क्रमागत rt_scan_type ScanType;	/*  Scan type such as passive
					 *  or active scan.
					 */
	u32	rx_count;
पूर्ण;

पूर्णांक rtw_ch_set_search_ch(काष्ठा rt_channel_info *ch_set, स्थिर u32 ch);

/*  P2P_MAX_REG_CLASSES - Maximum number of regulatory classes */
#घोषणा P2P_MAX_REG_CLASSES 10

/*  P2P_MAX_REG_CLASS_CHANNELS - Maximum number of chan per regulatory class */
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
	क्रमागत hw_mode अणुIEEE80211Gपूर्ण mode;
	u8 op_class;
	u8 min_chan;
	u8 max_chan;
	u8 inc;
	क्रमागत अणुBW20, BW40PLUS, BW40MINUSपूर्ण bw;
पूर्ण;

काष्ठा mlme_ext_priv अणु
	काष्ठा adapter	*padapter;
	u8	mlmeext_init;
	atomic_t	event_seq;
	u16	mgnt_seq;

	अचिन्हित अक्षर	cur_channel;
	अचिन्हित अक्षर	cur_bwmode;
	अचिन्हित अक्षर	cur_ch_offset;/* PRIME_CHNL_OFFSET */
	अचिन्हित अक्षर	cur_wireless_mode;	/*  NETWORK_TYPE */

	अचिन्हित अक्षर	oper_channel; /* saved chan info when call
				       * set_channel_bw
				       */
	अचिन्हित अक्षर	oper_bwmode;
	अचिन्हित अक्षर	oper_ch_offset;/* PRIME_CHNL_OFFSET */

	अचिन्हित अक्षर	max_chan_nums;
	काष्ठा rt_channel_info channel_set[MAX_CHANNEL_NUM];
	काष्ठा p2p_channels channel_list;
	अचिन्हित अक्षर	basicrate[NumRates];
	अचिन्हित अक्षर	datarate[NumRates];

	काष्ठा ss_res		sitesurvey_res;
	काष्ठा mlme_ext_info	mlmext_info;/* क्रम sta/adhoc mode, including
					     * current scan/connecting/connected
					     * related info. For ap mode,
					     * network includes ap's cap_info
					     */
	काष्ठा समयr_list survey_समयr;
	काष्ठा समयr_list link_समयr;
	u16	chan_scan_समय;

	u8	scan_पात;
	u8	tx_rate; /*  TXRATE when USERATE is set. */

	u32	retry; /* retry क्रम issue probereq */

	u64 TSFValue;

#अगर_घोषित CONFIG_88EU_AP_MODE
	अचिन्हित अक्षर bstart_bss;
#पूर्ण_अगर
	u8 update_channel_plan_by_ap_करोne;
	/* recv_decache check क्रम Action_खुला frame */
	u8 action_खुला_dialog_token;
	u16	 action_खुला_rxseq;
	u8 active_keep_alive_check;
पूर्ण;

पूर्णांक init_mlme_ext_priv(काष्ठा adapter *adapter);
पूर्णांक init_hw_mlme_ext(काष्ठा adapter *padapter);
व्योम मुक्त_mlme_ext_priv(काष्ठा mlme_ext_priv *pmlmeext);
व्योम init_mlme_ext_समयr(काष्ठा adapter *padapter);
व्योम init_addba_retry_समयr(काष्ठा adapter *adapt, काष्ठा sta_info *sta);
काष्ठा xmit_frame *alloc_mgtxmitframe(काष्ठा xmit_priv *pxmitpriv);

अचिन्हित अक्षर networktype_to_raid(अचिन्हित अक्षर network_type);
u8 judge_network_type(काष्ठा adapter *padapter, अचिन्हित अक्षर *rate);
व्योम get_rate_set(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbssrate, पूर्णांक *len);
व्योम UpdateBrateTbl(काष्ठा adapter *padapter, u8 *mBratesOS);
व्योम UpdateBrateTblForSoftAP(u8 *bssrateset, u32 bssratelen);

व्योम Save_DM_Func_Flag(काष्ठा adapter *padapter);
व्योम Restore_DM_Func_Flag(काष्ठा adapter *padapter);
व्योम Switch_DM_Func(काष्ठा adapter *padapter, u32 mode, u8 enable);

व्योम Set_MSR(काष्ठा adapter *padapter, u8 type);

u8 rtw_get_oper_ch(काष्ठा adapter *adapter);
व्योम rtw_set_oper_ch(काष्ठा adapter *adapter, u8 ch);
व्योम rtw_set_oper_bw(काष्ठा adapter *adapter, u8 bw);
व्योम rtw_set_oper_choffset(काष्ठा adapter *adapter, u8 offset);

व्योम set_channel_bwmode(काष्ठा adapter *padapter, अचिन्हित अक्षर channel,
			अचिन्हित अक्षर channel_offset, अचिन्हित लघु bwmode);
व्योम SelectChannel(काष्ठा adapter *padapter, अचिन्हित अक्षर channel);
व्योम SetBWMode(काष्ठा adapter *padapter, अचिन्हित लघु bwmode,
	       अचिन्हित अक्षर channel_offset);

अचिन्हित पूर्णांक decide_रुको_क्रम_beacon_समयout(अचिन्हित पूर्णांक bcn_पूर्णांकerval);

व्योम ग_लिखो_cam(काष्ठा adapter *padapter, u8 entry, u16 ctrl, u8 *mac, u8 *key);
व्योम clear_cam_entry(काष्ठा adapter *padapter, u8 entry);

व्योम invalidate_cam_all(काष्ठा adapter *padapter);

पूर्णांक allocate_fw_sta_entry(काष्ठा adapter *padapter);
व्योम flush_all_cam_entry(काष्ठा adapter *padapter);

व्योम update_network(काष्ठा wlan_bssid_ex *dst, काष्ठा wlan_bssid_ex *src,
		    काष्ठा adapter *adapter, bool update_ie);

u16 get_beacon_पूर्णांकerval(काष्ठा wlan_bssid_ex *bss);

पूर्णांक is_client_associated_to_ap(काष्ठा adapter *padapter);
पूर्णांक is_client_associated_to_ibss(काष्ठा adapter *padapter);
पूर्णांक is_IBSS_empty(काष्ठा adapter *padapter);

अचिन्हित अक्षर check_assoc_AP(u8 *pframe, uपूर्णांक len);

पूर्णांक WMM_param_handler(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE);
व्योम WMMOnAssocRsp(काष्ठा adapter *padapter);

व्योम HT_caps_handler(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE);
व्योम HT_info_handler(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE);
व्योम HTOnAssocRsp(काष्ठा adapter *padapter);

व्योम ERP_IE_handler(काष्ठा adapter *padapter, काष्ठा ndis_802_11_var_ie *pIE);
व्योम VCS_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta);

व्योम update_beacon_info(काष्ठा adapter *padapter, u8 *pframe, uपूर्णांक len,
			काष्ठा sta_info *psta);
पूर्णांक rtw_check_bcn_info(काष्ठा adapter  *Adapter, u8 *pframe, u32 packet_len);
व्योम update_IOT_info(काष्ठा adapter *padapter);
व्योम update_capinfo(काष्ठा adapter *adapter, u16 updatecap);
व्योम update_wireless_mode(काष्ठा adapter *padapter);
व्योम update_tx_basic_rate(काष्ठा adapter *padapter, u8 modulation);
व्योम update_bmc_sta_support_rate(काष्ठा adapter *padapter, u32 mac_id);
पूर्णांक update_sta_support_rate(काष्ठा adapter *padapter, u8 *pvar_ie,
			    uपूर्णांक var_ie_len, पूर्णांक cam_idx);

/* क्रम sta/adhoc mode */
व्योम update_sta_info(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
अचिन्हित पूर्णांक update_basic_rate(अचिन्हित अक्षर *ptn, अचिन्हित पूर्णांक ptn_sz);
अचिन्हित पूर्णांक update_supported_rate(अचिन्हित अक्षर *ptn, अचिन्हित पूर्णांक ptn_sz);
अचिन्हित पूर्णांक update_MSC_rate(काष्ठा ieee80211_ht_cap *pHT_caps);
व्योम Update_RA_Entry(काष्ठा adapter *padapter, u32 mac_id);
व्योम set_sta_rate(काष्ठा adapter *padapter, काष्ठा sta_info *psta);

अचिन्हित अक्षर get_highest_rate_idx(u32 mask);
पूर्णांक support_लघु_GI(काष्ठा adapter *padapter, काष्ठा ieee80211_ht_cap *caps);
अचिन्हित पूर्णांक is_ap_in_tkip(काष्ठा adapter *padapter);

व्योम report_join_res(काष्ठा adapter *padapter, पूर्णांक res);
व्योम report_survey_event(काष्ठा adapter *padapter,
			 काष्ठा recv_frame *precv_frame);
व्योम report_surveyकरोne_event(काष्ठा adapter *padapter);
व्योम report_del_sta_event(काष्ठा adapter *padapter,
			  अचिन्हित अक्षर *addr, अचिन्हित लघु reason);
व्योम report_add_sta_event(काष्ठा adapter *padapter, अचिन्हित अक्षर *addr,
			  पूर्णांक cam_idx);

u8 set_tx_beacon_cmd(काष्ठा adapter *padapter);
अचिन्हित पूर्णांक setup_beacon_frame(काष्ठा adapter *padapter,
				अचिन्हित अक्षर *beacon_frame);
व्योम update_mgnt_tx_rate(काष्ठा adapter *padapter, u8 rate);
व्योम update_mgntframe_attrib(काष्ठा adapter *padapter,
			     काष्ठा pkt_attrib *pattrib);

पूर्णांक issue_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
		   अचिन्हित पूर्णांक घातer_mode, पूर्णांक try_cnt, पूर्णांक रुको_ms);
पूर्णांक issue_qos_nulldata(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
		       u16 tid, पूर्णांक try_cnt, पूर्णांक रुको_ms);
पूर्णांक issue_deauth(काष्ठा adapter *padapter, अचिन्हित अक्षर *da,
		 अचिन्हित लघु reason);
अचिन्हित पूर्णांक send_delba(काष्ठा adapter *padapter, u8 initiator, u8 *addr);
अचिन्हित पूर्णांक send_beacon(काष्ठा adapter *padapter);

व्योम mlmeext_joinbss_event_callback(काष्ठा adapter *padapter, पूर्णांक join_res);
व्योम mlmeext_sta_del_event_callback(काष्ठा adapter *padapter);
व्योम mlmeext_sta_add_event_callback(काष्ठा adapter *padapter,
				    काष्ठा sta_info *psta);

व्योम linked_status_chk(काष्ठा adapter *padapter);

व्योम survey_समयr_hdl(काष्ठा समयr_list *t);
व्योम link_समयr_hdl(काष्ठा समयr_list *t);
व्योम addba_समयr_hdl(काष्ठा समयr_list *t);

#घोषणा set_survey_समयr(mlmeext, ms) \
	mod_समयr(&mlmeext->survey_समयr, jअगरfies +	\
		  msecs_to_jअगरfies(ms))

#घोषणा set_link_समयr(mlmeext, ms) \
	mod_समयr(&mlmeext->link_समयr, jअगरfies +	\
		  msecs_to_jअगरfies(ms))

व्योम process_addba_req(काष्ठा adapter *padapter, u8 *paddba_req, u8 *addr);

व्योम update_TSF(काष्ठा mlme_ext_priv *pmlmeext, u8 *pframe, uपूर्णांक len);
व्योम correct_TSF(काष्ठा adapter *padapter, काष्ठा mlme_ext_priv *pmlmeext);

काष्ठा cmd_hdl अणु
	uपूर्णांक	parmsize;
	u8 (*h2cfuns)(काष्ठा adapter  *padapter, u8 *pbuf);
पूर्ण;

u8 पढ़ो_macreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 ग_लिखो_macreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 पढ़ो_bbreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 ग_लिखो_bbreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 पढ़ो_rfreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 ग_लिखो_rfreg_hdl(काष्ठा adapter *padapter, u8 *pbuf);
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
u8 tx_beacon_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 set_ch_hdl(काष्ठा adapter *padapter, u8 *pbuf);
u8 set_chplan_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 led_blink_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
/* Handling DFS channel चयन announcement ie. */
u8 set_csa_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);
u8 tdls_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);

काष्ठा C2HEvent_Header अणु
#अगर_घोषित __LITTLE_ENDIAN
	अचिन्हित पूर्णांक len:16;
	अचिन्हित पूर्णांक ID:8;
	अचिन्हित पूर्णांक seq:8;
#या_अगर defined(__BIG_ENDIAN)
	अचिन्हित पूर्णांक seq:8;
	अचिन्हित पूर्णांक ID:8;
	अचिन्हित पूर्णांक len:16;
#पूर्ण_अगर
	अचिन्हित पूर्णांक rsvd;
पूर्ण;

व्योम rtw_dummy_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_fwdbg_event_callback(काष्ठा adapter *adapter, u8 *pbuf);

क्रमागत rtw_c2h_event अणु
	_Read_MACREG_EVT_ = 0, /*0*/
	_Read_BBREG_EVT_,
	_Read_RFREG_EVT_,
	_Read_EEPROM_EVT_,
	_Read_EFUSE_EVT_,
	_Read_CAM_EVT_,	/*5*/
	_Get_BasicRate_EVT_,
	_Get_DataRate_EVT_,
	_Survey_EVT_,	 /*8*/
	_SurveyDone_EVT_,	 /*9*/

	_JoinBss_EVT_, /*10*/
	_AddSTA_EVT_,
	_DelSTA_EVT_,
	_AtimDone_EVT_,
	_TX_Report_EVT_,
	_CCX_Report_EVT_,		/*15*/
	_DTM_Report_EVT_,
	_TX_Rate_Statistics_EVT_,
	_C2HLBK_EVT_,
	_FWDBG_EVT_,
	_C2HFEEDBACK_EVT_,             /*20*/
	_ADDBA_EVT_,
	_C2HBCN_EVT_,
	_ReportPwrState_EVT_,	/* filen: only क्रम PCIE, USB */
	_CloseRF_EVT_,		/* filen: only क्रम PCIE,
				 * work around ASPM
				 */
	MAX_C2HEVT
पूर्ण;

#अगर_घोषित _RTW_MLME_EXT_C_

अटल काष्ठा fwevent wlanevents[] = अणु
	अणु0, rtw_dummy_event_callbackपूर्ण,	/*0*/
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, शून्यपूर्ण,
	अणु0, &rtw_survey_event_callbackपूर्ण,		/*8*/
	अणुमाप(काष्ठा surveyकरोne_event), &rtw_surveyकरोne_event_callbackपूर्ण,/*9*/
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
पूर्ण;

#पूर्ण_अगर/* _RTL_MLME_EXT_C_ */

#पूर्ण_अगर /* __RTW_MLME_EXT_H_ */
