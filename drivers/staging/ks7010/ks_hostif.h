<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *   Driver क्रम KeyStream wireless LAN
 *
 *   Copyright (c) 2005-2008 KeyStream Corp.
 *   Copyright (C) 2009 Renesas Technology Corp.
 */

#अगर_अघोषित _KS_HOSTIF_H_
#घोषणा _KS_HOSTIF_H_

#समावेश <linux/compiler.h>
#समावेश <linux/ieee80211.h>

/*
 * HOST-MAC I/F events
 */
#घोषणा HIF_DATA_REQ		0xE001
#घोषणा HIF_DATA_IND		0xE801
#घोषणा HIF_MIB_GET_REQ		0xE002
#घोषणा HIF_MIB_GET_CONF	0xE802
#घोषणा HIF_MIB_SET_REQ		0xE003
#घोषणा HIF_MIB_SET_CONF	0xE803
#घोषणा HIF_POWER_MGMT_REQ	0xE004
#घोषणा HIF_POWER_MGMT_CONF	0xE804
#घोषणा HIF_START_REQ		0xE005
#घोषणा HIF_START_CONF		0xE805
#घोषणा HIF_CONNECT_IND		0xE806
#घोषणा HIF_STOP_REQ		0xE006
#घोषणा HIF_STOP_CONF		0xE807
#घोषणा HIF_PS_ADH_SET_REQ	0xE007
#घोषणा HIF_PS_ADH_SET_CONF	0xE808
#घोषणा HIF_INFRA_SET_REQ	0xE008
#घोषणा HIF_INFRA_SET_CONF	0xE809
#घोषणा HIF_ADH_SET_REQ		0xE009
#घोषणा HIF_ADH_SET_CONF	0xE80A
#घोषणा HIF_AP_SET_REQ		0xE00A
#घोषणा HIF_AP_SET_CONF		0xE80B
#घोषणा HIF_ASSOC_INFO_IND	0xE80C
#घोषणा HIF_MIC_FAILURE_REQ	0xE00B
#घोषणा HIF_MIC_FAILURE_CONF	0xE80D
#घोषणा HIF_SCAN_REQ		0xE00C
#घोषणा HIF_SCAN_CONF		0xE80E
#घोषणा HIF_PHY_INFO_REQ	0xE00D
#घोषणा HIF_PHY_INFO_CONF	0xE80F
#घोषणा HIF_SLEEP_REQ		0xE00E
#घोषणा HIF_SLEEP_CONF		0xE810
#घोषणा HIF_PHY_INFO_IND	0xE811
#घोषणा HIF_SCAN_IND		0xE812
#घोषणा HIF_INFRA_SET2_REQ	0xE00F
#घोषणा HIF_INFRA_SET2_CONF	0xE813
#घोषणा HIF_ADH_SET2_REQ	0xE010
#घोषणा HIF_ADH_SET2_CONF	0xE814

#घोषणा HIF_REQ_MAX		0xE010

/*
 * HOST-MAC I/F data काष्ठाure
 * Byte alignment Little Endian
 */

काष्ठा hostअगर_hdr अणु
	__le16 size;
	__le16 event;
पूर्ण __packed;

काष्ठा hostअगर_data_request अणु
	काष्ठा hostअगर_hdr header;
	__le16 auth_type;
#घोषणा TYPE_DATA 0x0000
#घोषणा TYPE_AUTH 0x0001
	__le16 reserved;
	u8 data[];
पूर्ण __packed;

#घोषणा TYPE_PMK1 0x0001
#घोषणा TYPE_GMK1 0x0002
#घोषणा TYPE_GMK2 0x0003

#घोषणा CHANNEL_LIST_MAX_SIZE 14
काष्ठा channel_list अणु
	u8 size;
	u8 body[CHANNEL_LIST_MAX_SIZE];
	u8 pad;
पूर्ण __packed;

/**
 * क्रमागत mib_attribute - Management Inक्रमmation Base attribute
 * Attribute value used क्रम accessing and updating MIB
 *
 * @DOT11_MAC_ADDRESS: MAC Address (R)
 * @DOT11_PRODUCT_VERSION: FirmWare Version (R)
 * @DOT11_RTS_THRESHOLD: RTS Threshold (R/W)
 * @DOT11_FRAGMENTATION_THRESHOLD: Fragment Threshold (R/W)
 * @DOT11_PRIVACY_INVOKED: WEP ON/OFF (W)
 * @DOT11_WEP_DEFAULT_KEY_ID: WEP Index (W)
 * @DOT11_WEP_DEFAULT_KEY_VALUE1: WEP Key#1(TKIP AES: PairwiseTemporalKey) (W)
 * @DOT11_WEP_DEFAULT_KEY_VALUE2: WEP Key#2(TKIP AES: GroupKey1) (W)
 * @DOT11_WEP_DEFAULT_KEY_VALUE3: WEP Key#3(TKIP AES: GroupKey2) (W)
 * @DOT11_WEP_DEFAULT_KEY_VALUE4: WEP Key#4 (W)
 * @DOT11_WEP_LIST: WEP LIST
 * @DOT11_DESIRED_SSID: SSID
 * @DOT11_CURRENT_CHANNEL: channel set
 * @DOT11_OPERATION_RATE_SET: rate set
 * @LOCAL_AP_SEARCH_INTERVAL: AP search पूर्णांकerval (R/W)
 * @LOCAL_CURRENTADDRESS: MAC Address change (W)
 * @LOCAL_MULTICAST_ADDRESS: Multicast Address (W)
 * @LOCAL_MULTICAST_FILTER: Multicast Address Filter enable/disable (W)
 * @LOCAL_SEARCHED_AP_LIST: AP list (R)
 * @LOCAL_LINK_AP_STATUS: Link AP status (R)
 * @LOCAL_PACKET_STATISTICS: tx,rx packets statistics
 * @LOCAL_AP_SCAN_LIST_TYPE_SET: AP_SCAN_LIST_TYPE
 * @DOT11_RSN_ENABLED: WPA enable/disable (W)
 * @LOCAL_RSN_MODE: RSN mode WPA/WPA2 (W)
 * @DOT11_RSN_CONFIG_MULTICAST_CIPHER: GroupKeyCipherSuite (W)
 * @DOT11_RSN_CONFIG_UNICAST_CIPHER: PairwiseKeyCipherSuite (W)
 * @DOT11_RSN_CONFIG_AUTH_SUITE: AuthenticationKeyManagementSuite (W)
 * @DOT11_RSN_CONFIG_VERSION: RSN version (W)
 * @LOCAL_RSN_CONFIG_ALL: RSN CONFIG ALL (W)
 * @DOT11_PMK_TSC: PMK_TSC (W)
 * @DOT11_GMK1_TSC: GMK1_TSC (W)
 * @DOT11_GMK2_TSC: GMK2_TSC (W)
 * @DOT11_GMK3_TSC: GMK3_TSC
 * @LOCAL_PMK: Pairwise Master Key cache (W)
 * @LOCAL_REGION: Region setting
 * @LOCAL_WPS_ENABLE: WiFi Protected Setup
 * @LOCAL_WPS_PROBE_REQ: WPS Probe Request
 * @LOCAL_GAIN: Carrer sense threshold क्रम demo ato show
 * @LOCAL_EEPROM_SUM: EEPROM checksum inक्रमmation
 */
क्रमागत mib_attribute अणु
	DOT11_MAC_ADDRESS                 = 0x21010100,
	DOT11_PRODUCT_VERSION             = 0x31024100,
	DOT11_RTS_THRESHOLD               = 0x21020100,
	DOT11_FRAGMENTATION_THRESHOLD     = 0x21050100,
	DOT11_PRIVACY_INVOKED             = 0x15010100,
	DOT11_WEP_DEFAULT_KEY_ID          = 0x15020100,
	DOT11_WEP_DEFAULT_KEY_VALUE1      = 0x13020101,
	DOT11_WEP_DEFAULT_KEY_VALUE2      = 0x13020102,
	DOT11_WEP_DEFAULT_KEY_VALUE3      = 0x13020103,
	DOT11_WEP_DEFAULT_KEY_VALUE4      = 0x13020104,
	DOT11_WEP_LIST                    = 0x13020100,
	DOT11_DESIRED_SSID		  = 0x11090100,
	DOT11_CURRENT_CHANNEL		  = 0x45010100,
	DOT11_OPERATION_RATE_SET	  = 0x11110100,
	LOCAL_AP_SEARCH_INTERVAL          = 0xF1010100,
	LOCAL_CURRENTADDRESS              = 0xF1050100,
	LOCAL_MULTICAST_ADDRESS           = 0xF1060100,
	LOCAL_MULTICAST_FILTER            = 0xF1060200,
	LOCAL_SEARCHED_AP_LIST            = 0xF1030100,
	LOCAL_LINK_AP_STATUS              = 0xF1040100,
	LOCAL_PACKET_STATISTICS		  = 0xF1020100,
	LOCAL_AP_SCAN_LIST_TYPE_SET	  = 0xF1030200,
	DOT11_RSN_ENABLED                 = 0x15070100,
	LOCAL_RSN_MODE                    = 0x56010100,
	DOT11_RSN_CONFIG_MULTICAST_CIPHER = 0x51040100,
	DOT11_RSN_CONFIG_UNICAST_CIPHER   = 0x52020100,
	DOT11_RSN_CONFIG_AUTH_SUITE       = 0x53020100,
	DOT11_RSN_CONFIG_VERSION          = 0x51020100,
	LOCAL_RSN_CONFIG_ALL              = 0x5F010100,
	DOT11_PMK_TSC                     = 0x55010100,
	DOT11_GMK1_TSC                    = 0x55010101,
	DOT11_GMK2_TSC                    = 0x55010102,
	DOT11_GMK3_TSC                    = 0x55010103,
	LOCAL_PMK                         = 0x58010100,
	LOCAL_REGION                      = 0xF10A0100,
	LOCAL_WPS_ENABLE                  = 0xF10B0100,
	LOCAL_WPS_PROBE_REQ               = 0xF10C0100,
	LOCAL_GAIN                        = 0xF10D0100,
	LOCAL_EEPROM_SUM                  = 0xF10E0100
पूर्ण;

काष्ठा hostअगर_mib_get_request अणु
	काष्ठा hostअगर_hdr header;
	__le32 mib_attribute;
पूर्ण __packed;

/**
 * क्रमागत mib_data_type - Message Inक्रमmation Base data type.
 * @MIB_VALUE_TYPE_शून्य: शून्य type
 * @MIB_VALUE_TYPE_INT: INTEGER type
 * @MIB_VALUE_TYPE_BOOL: BOOL type
 * @MIB_VALUE_TYPE_COUNT32: unused
 * @MIB_VALUE_TYPE_OSTRING: Chunk of memory
 */
क्रमागत mib_data_type अणु
	MIB_VALUE_TYPE_शून्य = 0,
	MIB_VALUE_TYPE_INT,
	MIB_VALUE_TYPE_BOOL,
	MIB_VALUE_TYPE_COUNT32,
	MIB_VALUE_TYPE_OSTRING
पूर्ण;

काष्ठा hostअगर_mib_value अणु
	__le16 size;
	__le16 type;
	u8 body[];
पूर्ण __packed;

काष्ठा hostअगर_mib_get_confirm_t अणु
	काष्ठा hostअगर_hdr header;
	__le32 mib_status;
#घोषणा MIB_SUCCESS    0
#घोषणा MIB_INVALID    1
#घोषणा MIB_READ_ONLY  2
#घोषणा MIB_WRITE_ONLY 3
	__le32 mib_attribute;
	काष्ठा hostअगर_mib_value mib_value;
पूर्ण __packed;

काष्ठा hostअगर_mib_set_request_t अणु
	काष्ठा hostअगर_hdr header;
	__le32 mib_attribute;
	काष्ठा hostअगर_mib_value mib_value;
पूर्ण __packed;

काष्ठा hostअगर_घातer_mgmt_request अणु
	काष्ठा hostअगर_hdr header;
	__le32 mode;
#घोषणा POWER_ACTIVE  1
#घोषणा POWER_SAVE    2
	__le32 wake_up;
#घोषणा SLEEP_FALSE 0
#घोषणा SLEEP_TRUE  1	/* not used */
	__le32 receive_dtims;
#घोषणा DTIM_FALSE 0
#घोषणा DTIM_TRUE  1
पूर्ण __packed;

क्रमागत घातer_mgmt_mode_type अणु
	POWER_MGMT_ACTIVE,
	POWER_MGMT_SAVE1,
	POWER_MGMT_SAVE2
पूर्ण;

#घोषणा	RESULT_SUCCESS            0
#घोषणा	RESULT_INVALID_PARAMETERS 1
#घोषणा	RESULT_NOT_SUPPORTED      2
/* #घोषणा	RESULT_ALREADY_RUNNING    3 */
#घोषणा	RESULT_ALREADY_RUNNING    7

काष्ठा hostअगर_start_request अणु
	काष्ठा hostअगर_hdr header;
	__le16 mode;
#घोषणा MODE_PSEUDO_ADHOC   0
#घोषणा MODE_INFRASTRUCTURE 1
#घोषणा MODE_AP             2	/* not used */
#घोषणा MODE_ADHOC          3
पूर्ण __packed;

काष्ठा ssid अणु
	u8 size;
	u8 body[IEEE80211_MAX_SSID_LEN];
	u8 ssid_pad;
पूर्ण __packed;

#घोषणा RATE_SET_MAX_SIZE 16
काष्ठा rate_set8 अणु
	u8 size;
	u8 body[8];
	u8 rate_pad;
पूर्ण __packed;

काष्ठा fh_parms अणु
	__le16 dwell_समय;
	u8 hop_set;
	u8 hop_pattern;
	u8 hop_index;
पूर्ण __packed;

काष्ठा ds_parms अणु
	u8 channel;
पूर्ण __packed;

काष्ठा cf_parms अणु
	u8 count;
	u8 period;
	__le16 max_duration;
	__le16 dur_reमुख्यing;
पूर्ण __packed;

काष्ठा ibss_parms अणु
	__le16 atim_winकरोw;
पूर्ण __packed;

काष्ठा rsn_t अणु
	u8 size;
#घोषणा RSN_BODY_SIZE 64
	u8 body[RSN_BODY_SIZE];
पूर्ण __packed;

काष्ठा erp_params_t अणु
	u8 erp_info;
पूर्ण __packed;

काष्ठा rate_set16 अणु
	u8 size;
	u8 body[16];
	u8 rate_pad;
पूर्ण __packed;

काष्ठा ap_info अणु
	u8 bssid[6];	/* +00 */
	u8 rssi;	/* +06 */
	u8 sq;	/* +07 */
	u8 noise;	/* +08 */
	u8 pad0;	/* +09 */
	__le16 beacon_period;	/* +10 */
	__le16 capability;	/* +12 */
	u8 frame_type;	/* +14 */
	u8 ch_info;	/* +15 */
	__le16 body_size;	/* +16 */
	u8 body[1024];	/* +18 */
	/* +1032 */
पूर्ण __packed;

काष्ठा link_ap_info अणु
	u8 bssid[6];	/* +00 */
	u8 rssi;	/* +06 */
	u8 sq;	/* +07 */
	u8 noise;	/* +08 */
	u8 pad0;	/* +09 */
	__le16 beacon_period;	/* +10 */
	__le16 capability;	/* +12 */
	काष्ठा rate_set8 rate_set;	/* +14 */
	काष्ठा fh_parms fh_parameter;	/* +24 */
	काष्ठा ds_parms ds_parameter;	/* +29 */
	काष्ठा cf_parms cf_parameter;	/* +30 */
	काष्ठा ibss_parms ibss_parameter;	/* +36 */
	काष्ठा erp_params_t erp_parameter;	/* +38 */
	u8 pad1;	/* +39 */
	काष्ठा rate_set8 ext_rate_set;	/* +40 */
	u8 DTIM_period;	/* +50 */
	u8 rsn_mode;	/* +51 */
#घोषणा RSN_MODE_NONE	0
#घोषणा RSN_MODE_WPA	1
#घोषणा RSN_MODE_WPA2	2
	काष्ठा अणु
		u8 size;	/* +52 */
		u8 body[128];	/* +53 */
	पूर्ण __packed rsn;
पूर्ण __packed;

#घोषणा RESULT_CONNECT    0
#घोषणा RESULT_DISCONNECT 1

काष्ठा hostअगर_stop_request अणु
	काष्ठा hostअगर_hdr header;
पूर्ण __packed;

#घोषणा D_11B_ONLY_MODE		0
#घोषणा D_11G_ONLY_MODE		1
#घोषणा D_11BG_COMPATIBLE_MODE	2
#घोषणा D_11A_ONLY_MODE		3

#घोषणा CTS_MODE_FALSE	0
#घोषणा CTS_MODE_TRUE	1

काष्ठा hostअगर_request अणु
	__le16 phy_type;
	__le16 cts_mode;
	__le16 scan_type;
	__le16 capability;
	काष्ठा rate_set16 rate_set;
पूर्ण __packed;

/**
 * काष्ठा hostअगर_ps_adhoc_set_request - pseuकरो adhoc mode
 * @capability: bit5  : preamble
 *              bit6  : pbcc - Not supported always 0
 *              bit10 : ShortSlotTime
 *              bit13 : DSSS-OFDM - Not supported always 0
 */
काष्ठा hostअगर_ps_adhoc_set_request अणु
	काष्ठा hostअगर_hdr header;
	काष्ठा hostअगर_request request;
	__le16 channel;
पूर्ण __packed;

#घोषणा AUTH_TYPE_OPEN_SYSTEM 0
#घोषणा AUTH_TYPE_SHARED_KEY  1

/**
 * काष्ठा hostअगर_infraकाष्ठाure_set_request
 * @capability: bit5  : preamble
 *              bit6  : pbcc - Not supported always 0
 *              bit10 : ShortSlotTime
 *              bit13 : DSSS-OFDM - Not supported always 0
 */
काष्ठा hostअगर_infraकाष्ठाure_set_request अणु
	काष्ठा hostअगर_hdr header;
	काष्ठा hostअगर_request request;
	काष्ठा ssid ssid;
	__le16 beacon_lost_count;
	__le16 auth_type;
	काष्ठा channel_list channel_list;
	u8 bssid[ETH_ALEN];
पूर्ण __packed;

/**
 * काष्ठा hostअगर_adhoc_set_request
 * @capability: bit5  : preamble
 *              bit6  : pbcc - Not supported always 0
 *              bit10 : ShortSlotTime
 *              bit13 : DSSS-OFDM - Not supported always 0
 */
काष्ठा hostअगर_adhoc_set_request अणु
	काष्ठा hostअगर_hdr header;
	काष्ठा hostअगर_request request;
	काष्ठा ssid ssid;
	__le16 channel;
पूर्ण __packed;

/**
 * काष्ठा hostअगर_adhoc_set2_request
 * @capability: bit5  : preamble
 *              bit6  : pbcc - Not supported always 0
 *              bit10 : ShortSlotTime
 *              bit13 : DSSS-OFDM - Not supported always 0
 */
काष्ठा hostअगर_adhoc_set2_request अणु
	काष्ठा hostअगर_hdr header;
	काष्ठा hostअगर_request request;
	__le16 reserved;
	काष्ठा ssid ssid;
	काष्ठा channel_list channel_list;
	u8 bssid[ETH_ALEN];
पूर्ण __packed;

काष्ठा association_request अणु
	u8 type;
	u8 pad;
	__le16 capability;
	__le16 listen_पूर्णांकerval;
	u8 ap_address[6];
	__le16 req_ies_size;
पूर्ण __packed;

काष्ठा association_response अणु
	u8 type;
	u8 pad;
	__le16 capability;
	__le16 status;
	__le16 association_id;
	__le16 resp_ies_size;
पूर्ण __packed;

काष्ठा hostअगर_bss_scan_request अणु
	काष्ठा hostअगर_hdr header;
	u8 scan_type;
#घोषणा ACTIVE_SCAN  0
#घोषणा PASSIVE_SCAN 1
	u8 pad[3];
	__le32 ch_समय_min;
	__le32 ch_समय_max;
	काष्ठा channel_list channel_list;
	काष्ठा ssid ssid;
पूर्ण __packed;

काष्ठा hostअगर_phy_inक्रमmation_request अणु
	काष्ठा hostअगर_hdr header;
	__le16 type;
#घोषणा NORMAL_TYPE	0
#घोषणा TIME_TYPE	1
	__le16 समय;	/* unit 100ms */
पूर्ण __packed;

क्रमागत sleep_mode_type अणु
	SLP_ACTIVE,
	SLP_SLEEP
पूर्ण;

काष्ठा hostअगर_sleep_request अणु
	काष्ठा hostअगर_hdr header;
पूर्ण __packed;

काष्ठा hostअगर_mic_failure_request अणु
	काष्ठा hostअगर_hdr header;
	__le16 failure_count;
	__le16 समयr;
पूर्ण __packed;

#घोषणा BASIC_RATE	0x80
#घोषणा RATE_MASK	0x7F

#घोषणा TX_RATE_AUTO      0xff
#घोषणा TX_RATE_1M_FIXED  0
#घोषणा TX_RATE_2M_FIXED  1
#घोषणा TX_RATE_1_2M_AUTO 2
#घोषणा TX_RATE_5M_FIXED  3
#घोषणा TX_RATE_11M_FIXED 4

#घोषणा TX_RATE_FULL_AUTO	0
#घोषणा TX_RATE_11_AUTO		1
#घोषणा TX_RATE_11B_AUTO	2
#घोषणा TX_RATE_11BG_AUTO	3
#घोषणा TX_RATE_MANUAL_AUTO	4
#घोषणा TX_RATE_FIXED		5

/* 11b rate */
#घोषणा TX_RATE_1M	(u8)(10 / 5)	/* 11b 11g basic rate */
#घोषणा TX_RATE_2M	(u8)(20 / 5)	/* 11b 11g basic rate */
#घोषणा TX_RATE_5M	(u8)(55 / 5)	/* 11g basic rate */
#घोषणा TX_RATE_11M	(u8)(110 / 5)	/* 11g basic rate */

/* 11g rate */
#घोषणा TX_RATE_6M	(u8)(60 / 5)	/* 11g basic rate */
#घोषणा TX_RATE_12M	(u8)(120 / 5)	/* 11g basic rate */
#घोषणा TX_RATE_24M	(u8)(240 / 5)	/* 11g basic rate */
#घोषणा TX_RATE_9M	(u8)(90 / 5)
#घोषणा TX_RATE_18M	(u8)(180 / 5)
#घोषणा TX_RATE_36M	(u8)(360 / 5)
#घोषणा TX_RATE_48M	(u8)(480 / 5)
#घोषणा TX_RATE_54M	(u8)(540 / 5)

अटल अंतरभूत bool is_11b_rate(u8 rate)
अणु
	वापस (((rate & RATE_MASK) == TX_RATE_1M) ||
		((rate & RATE_MASK) == TX_RATE_2M) ||
		((rate & RATE_MASK) == TX_RATE_5M) ||
		((rate & RATE_MASK) == TX_RATE_11M));
पूर्ण

अटल अंतरभूत bool is_ofdm_rate(u8 rate)
अणु
	वापस (((rate & RATE_MASK) == TX_RATE_6M)  ||
		((rate & RATE_MASK) == TX_RATE_12M) ||
		((rate & RATE_MASK) == TX_RATE_24M) ||
		((rate & RATE_MASK) == TX_RATE_9M)  ||
		((rate & RATE_MASK) == TX_RATE_18M) ||
		((rate & RATE_MASK) == TX_RATE_36M) ||
		((rate & RATE_MASK) == TX_RATE_48M) ||
		((rate & RATE_MASK) == TX_RATE_54M));
पूर्ण

अटल अंतरभूत bool is_11bg_rate(u8 rate)
अणु
	वापस (is_11b_rate(rate) || is_ofdm_rate(rate));
पूर्ण

अटल अंतरभूत bool is_ofdm_ext_rate(u8 rate)
अणु
	वापस (((rate & RATE_MASK) == TX_RATE_9M)  ||
		((rate & RATE_MASK) == TX_RATE_18M) ||
		((rate & RATE_MASK) == TX_RATE_36M) ||
		((rate & RATE_MASK) == TX_RATE_48M) ||
		((rate & RATE_MASK) == TX_RATE_54M));
पूर्ण

क्रमागत connect_status_type अणु
	CONNECT_STATUS,
	DISCONNECT_STATUS
पूर्ण;

क्रमागत preamble_type अणु
	LONG_PREAMBLE,
	SHORT_PREAMBLE
पूर्ण;

क्रमागत multicast_filter_type अणु
	MCAST_FILTER_MCAST,
	MCAST_FILTER_MCASTALL,
	MCAST_FILTER_PROMISC,
पूर्ण;

#घोषणा NIC_MAX_MCAST_LIST 32

#घोषणा HIF_EVENT_MASK 0xE800

अटल अंतरभूत bool is_hअगर_ind(अचिन्हित लघु event)
अणु
	वापस (((event & HIF_EVENT_MASK) == HIF_EVENT_MASK) &&
		(((event & ~HIF_EVENT_MASK) == 0x0001) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0006) ||
		 ((event & ~HIF_EVENT_MASK) == 0x000C) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0011) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0012)));
पूर्ण

अटल अंतरभूत bool is_hअगर_conf(अचिन्हित लघु event)
अणु
	वापस (((event & HIF_EVENT_MASK) == HIF_EVENT_MASK) &&
		((event & ~HIF_EVENT_MASK) > 0x0000) &&
		((event & ~HIF_EVENT_MASK) < 0x0012) &&
		!is_hअगर_ind(event));
पूर्ण

#अगर_घोषित __KERNEL__

#समावेश "ks_wlan.h"

/* function prototype */
पूर्णांक hostअगर_data_request(काष्ठा ks_wlan_निजी *priv, काष्ठा sk_buff *skb);
व्योम hostअगर_receive(काष्ठा ks_wlan_निजी *priv, अचिन्हित अक्षर *p,
		    अचिन्हित पूर्णांक size);
व्योम hostअगर_sme_enqueue(काष्ठा ks_wlan_निजी *priv, u16 event);
पूर्णांक hostअगर_init(काष्ठा ks_wlan_निजी *priv);
व्योम hostअगर_निकास(काष्ठा ks_wlan_निजी *priv);
पूर्णांक ks_wlan_hw_tx(काष्ठा ks_wlan_निजी *priv, व्योम *p, अचिन्हित दीर्घ size,
		  व्योम (*complete_handler)(काष्ठा ks_wlan_निजी *priv,
					   काष्ठा sk_buff *skb),
		  काष्ठा sk_buff *skb);
व्योम send_packet_complete(काष्ठा ks_wlan_निजी *priv, काष्ठा sk_buff *skb);

व्योम ks_wlan_hw_wakeup_request(काष्ठा ks_wlan_निजी *priv);
पूर्णांक ks_wlan_hw_घातer_save(काष्ठा ks_wlan_निजी *priv);

#घोषणा KS7010_SIZE_ALIGNMENT	32

अटल अंतरभूत माप_प्रकार hअगर_align_size(माप_प्रकार size)
अणु
	वापस ALIGN(size, KS7010_SIZE_ALIGNMENT);
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _KS_HOSTIF_H_ */
