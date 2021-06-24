<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित	__HALBTC_OUT_SRC_H__
#घोषणा __HALBTC_OUT_SRC_H__

#समावेश	"../wifi.h"

#घोषणा		NORMAL_EXEC				false
#घोषणा		FORCE_EXEC				true

#घोषणा		BTC_RF_OFF				0x0
#घोषणा		BTC_RF_ON				0x1

#घोषणा		BTC_RF_A				RF90_PATH_A
#घोषणा		BTC_RF_B				RF90_PATH_B
#घोषणा		BTC_RF_C				RF90_PATH_C
#घोषणा		BTC_RF_D				RF90_PATH_D

#घोषणा		BTC_SMSP				SINGLEMAC_SINGLEPHY
#घोषणा		BTC_DMDP				DUALMAC_DUALPHY
#घोषणा		BTC_DMSP				DUALMAC_SINGLEPHY
#घोषणा		BTC_MP_UNKNOWN				0xff

#घोषणा		IN
#घोषणा		OUT

#घोषणा		BT_TMP_BUF_SIZE				100

#घोषणा		BT_COEX_ANT_TYPE_PG			0
#घोषणा		BT_COEX_ANT_TYPE_ANTDIV			1
#घोषणा		BT_COEX_ANT_TYPE_DETECTED		2

#घोषणा		BTC_MIMO_PS_STATIC			0
#घोषणा		BTC_MIMO_PS_DYNAMIC			1

#घोषणा		BTC_RATE_DISABLE			0
#घोषणा		BTC_RATE_ENABLE				1

/* single Antenna definition */
#घोषणा		BTC_ANT_PATH_WIFI			0
#घोषणा		BTC_ANT_PATH_BT				1
#घोषणा		BTC_ANT_PATH_PTA			2
#घोषणा		BTC_ANT_PATH_WIFI5G			3
#घोषणा		BTC_ANT_PATH_AUTO			4
/* dual Antenna definition */
#घोषणा		BTC_ANT_WIFI_AT_MAIN			0
#घोषणा		BTC_ANT_WIFI_AT_AUX			1
/* coupler Antenna definition */
#घोषणा		BTC_ANT_WIFI_AT_CPL_MAIN		0
#घोषणा		BTC_ANT_WIFI_AT_CPL_AUX			1

क्रमागत btc_bt_reg_type अणु
	BTC_BT_REG_RF		= 0,
	BTC_BT_REG_MODEM	= 1,
	BTC_BT_REG_BLUEWIZE	= 2,
	BTC_BT_REG_VENDOR	= 3,
	BTC_BT_REG_LE		= 4,
	BTC_BT_REG_MAX
पूर्ण;

क्रमागत btc_chip_पूर्णांकerface अणु
	BTC_INTF_UNKNOWN	= 0,
	BTC_INTF_PCI		= 1,
	BTC_INTF_USB		= 2,
	BTC_INTF_SDIO		= 3,
	BTC_INTF_GSPI		= 4,
	BTC_INTF_MAX
पूर्ण;

क्रमागत btc_chip_type अणु
	BTC_CHIP_UNDEF		= 0,
	BTC_CHIP_CSR_BC4	= 1,
	BTC_CHIP_CSR_BC8	= 2,
	BTC_CHIP_RTL8723A	= 3,
	BTC_CHIP_RTL8821	= 4,
	BTC_CHIP_RTL8723B	= 5,
	BTC_CHIP_MAX
पूर्ण;

क्रमागत btc_msg_type अणु
	BTC_MSG_INTERFACE	= 0x0,
	BTC_MSG_ALGORITHM	= 0x1,
	BTC_MSG_MAX
पूर्ण;

/* following is क्रम BTC_MSG_INTERFACE */
#घोषणा		INTF_INIT				BIT0
#घोषणा		INTF_NOTIFY				BIT2

/* following is क्रम BTC_ALGORITHM */
#घोषणा		ALGO_BT_RSSI_STATE			BIT0
#घोषणा		ALGO_WIFI_RSSI_STATE			BIT1
#घोषणा		ALGO_BT_MONITOR				BIT2
#घोषणा		ALGO_TRACE				BIT3
#घोषणा		ALGO_TRACE_FW				BIT4
#घोषणा		ALGO_TRACE_FW_DETAIL			BIT5
#घोषणा		ALGO_TRACE_FW_EXEC			BIT6
#घोषणा		ALGO_TRACE_SW				BIT7
#घोषणा		ALGO_TRACE_SW_DETAIL			BIT8
#घोषणा		ALGO_TRACE_SW_EXEC			BIT9

/* following is क्रम wअगरi link status */
#घोषणा		WIFI_STA_CONNECTED			BIT0
#घोषणा		WIFI_AP_CONNECTED			BIT1
#घोषणा		WIFI_HS_CONNECTED			BIT2
#घोषणा		WIFI_P2P_GO_CONNECTED			BIT3
#घोषणा		WIFI_P2P_GC_CONNECTED			BIT4

#घोषणा	BTC_RSSI_HIGH(_rssi_)	\
	((_rssi_ == BTC_RSSI_STATE_HIGH ||	\
	  _rssi_ == BTC_RSSI_STATE_STAY_HIGH) ? true : false)
#घोषणा	BTC_RSSI_MEDIUM(_rssi_)	\
	((_rssi_ == BTC_RSSI_STATE_MEDIUM ||	\
	  _rssi_ == BTC_RSSI_STATE_STAY_MEDIUM) ? true : false)
#घोषणा	BTC_RSSI_LOW(_rssi_)	\
	((_rssi_ == BTC_RSSI_STATE_LOW ||	\
	  _rssi_ == BTC_RSSI_STATE_STAY_LOW) ? true : false)

क्रमागत btc_घातer_save_type अणु
	BTC_PS_WIFI_NATIVE = 0,
	BTC_PS_LPS_ON = 1,
	BTC_PS_LPS_OFF = 2,
	BTC_PS_LPS_MAX
पूर्ण;

काष्ठा btc_board_info अणु
	/* The following is some board inक्रमmation */
	u8 bt_chip_type;
	u8 pg_ant_num;	/* pg ant number */
	u8 btdm_ant_num;	/* ant number क्रम btdm */
	u8 btdm_ant_pos;
	u8 single_ant_path; /* current used क्रम 8723b only, 1=>s0,  0=>s1 */
	bool tfbga_package;

	u8 rfe_type;
	u8 ant_भाग_cfg;
	u8 customer_id;
पूर्ण;

क्रमागत btc_dbg_opcode अणु
	BTC_DBG_SET_COEX_NORMAL = 0x0,
	BTC_DBG_SET_COEX_WIFI_ONLY = 0x1,
	BTC_DBG_SET_COEX_BT_ONLY = 0x2,
	BTC_DBG_MAX
पूर्ण;

क्रमागत btc_rssi_state अणु
	BTC_RSSI_STATE_HIGH = 0x0,
	BTC_RSSI_STATE_MEDIUM = 0x1,
	BTC_RSSI_STATE_LOW = 0x2,
	BTC_RSSI_STATE_STAY_HIGH = 0x3,
	BTC_RSSI_STATE_STAY_MEDIUM = 0x4,
	BTC_RSSI_STATE_STAY_LOW = 0x5,
	BTC_RSSI_MAX
पूर्ण;

क्रमागत btc_wअगरi_role अणु
	BTC_ROLE_STATION = 0x0,
	BTC_ROLE_AP = 0x1,
	BTC_ROLE_IBSS = 0x2,
	BTC_ROLE_HS_MODE = 0x3,
	BTC_ROLE_MAX
पूर्ण;

क्रमागत btc_wireless_freq अणु
	BTC_FREQ_2_4G = 0x0,
	BTC_FREQ_5G = 0x1,
	BTC_FREQ_MAX
पूर्ण;

क्रमागत btc_wअगरi_bw_mode अणु
	BTC_WIFI_BW_LEGACY = 0x0,
	BTC_WIFI_BW_HT20 = 0x1,
	BTC_WIFI_BW_HT40 = 0x2,
	BTC_WIFI_BW_HT80 = 0x3,
	BTC_WIFI_BW_MAX
पूर्ण;

क्रमागत btc_wअगरi_traffic_dir अणु
	BTC_WIFI_TRAFFIC_TX = 0x0,
	BTC_WIFI_TRAFFIC_RX = 0x1,
	BTC_WIFI_TRAFFIC_MAX
पूर्ण;

क्रमागत btc_wअगरi_pnp अणु
	BTC_WIFI_PNP_WAKE_UP = 0x0,
	BTC_WIFI_PNP_SLEEP = 0x1,
	BTC_WIFI_PNP_SLEEP_KEEP_ANT = 0x2,
	BTC_WIFI_PNP_MAX
पूर्ण;

क्रमागत btc_iot_peer अणु
	BTC_IOT_PEER_UNKNOWN = 0,
	BTC_IOT_PEER_REALTEK = 1,
	BTC_IOT_PEER_REALTEK_92SE = 2,
	BTC_IOT_PEER_BROADCOM = 3,
	BTC_IOT_PEER_RALINK = 4,
	BTC_IOT_PEER_ATHEROS = 5,
	BTC_IOT_PEER_CISCO = 6,
	BTC_IOT_PEER_MERU = 7,
	BTC_IOT_PEER_MARVELL = 8,
	BTC_IOT_PEER_REALTEK_SOFTAP = 9,
	BTC_IOT_PEER_SELF_SOFTAP = 10, /* Self is SoftAP */
	BTC_IOT_PEER_AIRGO = 11,
	BTC_IOT_PEER_REALTEK_JAGUAR_BCUTAP = 12,
	BTC_IOT_PEER_REALTEK_JAGUAR_CCUTAP = 13,
	BTC_IOT_PEER_MAX,
पूर्ण;

/* क्रम 8723b-d cut large current issue */
क्रमागत bt_wअगरi_coex_state अणु
	BTC_WIFI_STAT_INIT,
	BTC_WIFI_STAT_IQK,
	BTC_WIFI_STAT_NORMAL_OFF,
	BTC_WIFI_STAT_MP_OFF,
	BTC_WIFI_STAT_NORMAL,
	BTC_WIFI_STAT_ANT_DIV,
	BTC_WIFI_STAT_MAX
पूर्ण;

क्रमागत bt_ant_type अणु
	BTC_ANT_TYPE_0,
	BTC_ANT_TYPE_1,
	BTC_ANT_TYPE_2,
	BTC_ANT_TYPE_3,
	BTC_ANT_TYPE_4,
	BTC_ANT_TYPE_MAX
पूर्ण;

क्रमागत btc_get_type अणु
	/* type bool */
	BTC_GET_BL_HS_OPERATION,
	BTC_GET_BL_HS_CONNECTING,
	BTC_GET_BL_WIFI_CONNECTED,
	BTC_GET_BL_WIFI_DUAL_BAND_CONNECTED,
	BTC_GET_BL_WIFI_BUSY,
	BTC_GET_BL_WIFI_SCAN,
	BTC_GET_BL_WIFI_LINK,
	BTC_GET_BL_WIFI_DHCP,
	BTC_GET_BL_WIFI_SOFTAP_IDLE,
	BTC_GET_BL_WIFI_SOFTAP_LINKING,
	BTC_GET_BL_WIFI_IN_EARLY_SUSPEND,
	BTC_GET_BL_WIFI_ROAM,
	BTC_GET_BL_WIFI_4_WAY_PROGRESS,
	BTC_GET_BL_WIFI_UNDER_5G,
	BTC_GET_BL_WIFI_AP_MODE_ENABLE,
	BTC_GET_BL_WIFI_ENABLE_ENCRYPTION,
	BTC_GET_BL_WIFI_UNDER_B_MODE,
	BTC_GET_BL_EXT_SWITCH,
	BTC_GET_BL_WIFI_IS_IN_MP_MODE,
	BTC_GET_BL_IS_ASUS_8723B,
	BTC_GET_BL_FW_READY,
	BTC_GET_BL_RF4CE_CONNECTED,

	/* type s4Byte */
	BTC_GET_S4_WIFI_RSSI,
	BTC_GET_S4_HS_RSSI,

	/* type u32 */
	BTC_GET_U4_WIFI_BW,
	BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION,
	BTC_GET_U4_WIFI_FW_VER,
	BTC_GET_U4_WIFI_LINK_STATUS,
	BTC_GET_U4_BT_PATCH_VER,
	BTC_GET_U4_VENDOR,
	BTC_GET_U4_SUPPORTED_VERSION,
	BTC_GET_U4_SUPPORTED_FEATURE,
	BTC_GET_U4_BT_DEVICE_INFO,
	BTC_GET_U4_BT_FORBIDDEN_SLOT_VAL,
	BTC_GET_U4_WIFI_IQK_TOTAL,
	BTC_GET_U4_WIFI_IQK_OK,
	BTC_GET_U4_WIFI_IQK_FAIL,

	/* type u1Byte */
	BTC_GET_U1_WIFI_DOT11_CHNL,
	BTC_GET_U1_WIFI_CENTRAL_CHNL,
	BTC_GET_U1_WIFI_HS_CHNL,
	BTC_GET_U1_MAC_PHY_MODE,
	BTC_GET_U1_AP_NUM,
	BTC_GET_U1_ANT_TYPE,
	BTC_GET_U1_IOT_PEER,

	/* क्रम 1Ant */
	BTC_GET_U1_LPS_MODE,
	BTC_GET_BL_BT_SCO_BUSY,

	/* क्रम test mode */
	BTC_GET_DRIVER_TEST_CFG,
	BTC_GET_MAX
पूर्ण;

क्रमागत btc_venकरोr अणु
	BTC_VENDOR_LENOVO,
	BTC_VENDOR_ASUS,
	BTC_VENDOR_OTHER
पूर्ण;

क्रमागत btc_set_type अणु
	/* type bool */
	BTC_SET_BL_BT_DISABLE,
	BTC_SET_BL_BT_TRAFFIC_BUSY,
	BTC_SET_BL_BT_LIMITED_DIG,
	BTC_SET_BL_FORCE_TO_ROAM,
	BTC_SET_BL_TO_REJ_AP_AGG_PKT,
	BTC_SET_BL_BT_CTRL_AGG_SIZE,
	BTC_SET_BL_INC_SCAN_DEV_NUM,
	BTC_SET_BL_BT_TX_RX_MASK,
	BTC_SET_BL_MIRACAST_PLUS_BT,

	/* type u1Byte */
	BTC_SET_U1_RSSI_ADJ_VAL_FOR_AGC_TABLE_ON,
	BTC_SET_UI_SCAN_SIG_COMPENSATION,
	BTC_SET_U1_AGG_BUF_SIZE,

	/* type trigger some action */
	BTC_SET_ACT_GET_BT_RSSI,
	BTC_SET_ACT_AGGREGATE_CTRL,
	BTC_SET_ACT_ANTPOSREGRISTRY_CTRL,
	BTC_SET_MIMO_PS_MODE,

	/********* क्रम 1Ant **********/
	/* type bool */
	BTC_SET_BL_BT_SCO_BUSY,
	/* type u1Byte */
	BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE,
	BTC_SET_U1_LPS_VAL,
	BTC_SET_U1_RPWM_VAL,
	BTC_SET_U1_1ANT_LPS,
	BTC_SET_U1_1ANT_RPWM,
	/* type trigger some action */
	BTC_SET_ACT_LEAVE_LPS,
	BTC_SET_ACT_ENTER_LPS,
	BTC_SET_ACT_NORMAL_LPS,
	BTC_SET_ACT_PRE_NORMAL_LPS,
	BTC_SET_ACT_POST_NORMAL_LPS,
	BTC_SET_ACT_INC_FORCE_EXEC_PWR_CMD_CNT,
	BTC_SET_ACT_DISABLE_LOW_POWER,
	BTC_SET_BL_BT_LNA_CONSTRAIN_LEVEL,
	BTC_SET_ACT_UPDATE_RAMASK,
	BTC_SET_ACT_SEND_MIMO_PS,
	/* BT Coex related */
	BTC_SET_ACT_CTRL_BT_INFO,
	BTC_SET_ACT_CTRL_BT_COEX,
	BTC_SET_ACT_CTRL_8723B_ANT,
	/***************************/
	BTC_SET_MAX
पूर्ण;

क्रमागत btc_dbg_disp_type अणु
	BTC_DBG_DISP_COEX_STATISTICS = 0x0,
	BTC_DBG_DISP_BT_LINK_INFO = 0x1,
	BTC_DBG_DISP_BT_FW_VER = 0x2,
	BTC_DBG_DISP_FW_PWR_MODE_CMD = 0x3,
	BTC_DBG_DISP_WIFI_STATUS = 0x04,
	BTC_DBG_DISP_MAX
पूर्ण;

क्रमागत btc_notअगरy_type_ips अणु
	BTC_IPS_LEAVE = 0x0,
	BTC_IPS_ENTER = 0x1,
	BTC_IPS_MAX
पूर्ण;

क्रमागत btc_notअगरy_type_lps अणु
	BTC_LPS_DISABLE = 0x0,
	BTC_LPS_ENABLE = 0x1,
	BTC_LPS_MAX
पूर्ण;

क्रमागत btc_notअगरy_type_scan अणु
	BTC_SCAN_FINISH = 0x0,
	BTC_SCAN_START = 0x1,
	BTC_SCAN_START_2G = 0x2,
	BTC_SCAN_MAX
पूर्ण;

क्रमागत btc_notअगरy_type_चयनband अणु
	BTC_NOT_SWITCH = 0x0,
	BTC_SWITCH_TO_24G = 0x1,
	BTC_SWITCH_TO_5G = 0x2,
	BTC_SWITCH_TO_24G_NOFORSCAN = 0x3,
	BTC_SWITCH_MAX
पूर्ण;

क्रमागत btc_notअगरy_type_associate अणु
	BTC_ASSOCIATE_FINISH = 0x0,
	BTC_ASSOCIATE_START = 0x1,
	BTC_ASSOCIATE_5G_FINISH = 0x2,
	BTC_ASSOCIATE_5G_START = 0x3,
	BTC_ASSOCIATE_MAX
पूर्ण;

क्रमागत btc_notअगरy_type_media_status अणु
	BTC_MEDIA_DISCONNECT = 0x0,
	BTC_MEDIA_CONNECT = 0x1,
	BTC_MEDIA_MAX
पूर्ण;

क्रमागत btc_notअगरy_type_special_packet अणु
	BTC_PACKET_UNKNOWN = 0x0,
	BTC_PACKET_DHCP = 0x1,
	BTC_PACKET_ARP = 0x2,
	BTC_PACKET_EAPOL = 0x3,
	BTC_PACKET_MAX
पूर्ण;

क्रमागत hci_ext_bt_operation अणु
	HCI_BT_OP_NONE = 0x0,
	HCI_BT_OP_INQUIRY_START = 0x1,
	HCI_BT_OP_INQUIRY_FINISH = 0x2,
	HCI_BT_OP_PAGING_START = 0x3,
	HCI_BT_OP_PAGING_SUCCESS = 0x4,
	HCI_BT_OP_PAGING_UNSUCCESS = 0x5,
	HCI_BT_OP_PAIRING_START = 0x6,
	HCI_BT_OP_PAIRING_FINISH = 0x7,
	HCI_BT_OP_BT_DEV_ENABLE = 0x8,
	HCI_BT_OP_BT_DEV_DISABLE = 0x9,
	HCI_BT_OP_MAX
पूर्ण;

क्रमागत btc_notअगरy_type_stack_operation अणु
	BTC_STACK_OP_NONE = 0x0,
	BTC_STACK_OP_INQ_PAGE_PAIR_START = 0x1,
	BTC_STACK_OP_INQ_PAGE_PAIR_FINISH = 0x2,
	BTC_STACK_OP_MAX
पूर्ण;

क्रमागत अणु
	BTC_CCK_1,
	BTC_CCK_2,
	BTC_CCK_5_5,
	BTC_CCK_11,
	BTC_OFDM_6,
	BTC_OFDM_9,
	BTC_OFDM_12,
	BTC_OFDM_18,
	BTC_OFDM_24,
	BTC_OFDM_36,
	BTC_OFDM_48,
	BTC_OFDM_54,
	BTC_MCS_0,
	BTC_MCS_1,
	BTC_MCS_2,
	BTC_MCS_3,
	BTC_MCS_4,
	BTC_MCS_5,
	BTC_MCS_6,
	BTC_MCS_7,
	BTC_MCS_8,
	BTC_MCS_9,
	BTC_MCS_10,
	BTC_MCS_11,
	BTC_MCS_12,
	BTC_MCS_13,
	BTC_MCS_14,
	BTC_MCS_15,
	BTC_MCS_16,
	BTC_MCS_17,
	BTC_MCS_18,
	BTC_MCS_19,
	BTC_MCS_20,
	BTC_MCS_21,
	BTC_MCS_22,
	BTC_MCS_23,
	BTC_MCS_24,
	BTC_MCS_25,
	BTC_MCS_26,
	BTC_MCS_27,
	BTC_MCS_28,
	BTC_MCS_29,
	BTC_MCS_30,
	BTC_MCS_31,
	BTC_VHT_1SS_MCS_0,
	BTC_VHT_1SS_MCS_1,
	BTC_VHT_1SS_MCS_2,
	BTC_VHT_1SS_MCS_3,
	BTC_VHT_1SS_MCS_4,
	BTC_VHT_1SS_MCS_5,
	BTC_VHT_1SS_MCS_6,
	BTC_VHT_1SS_MCS_7,
	BTC_VHT_1SS_MCS_8,
	BTC_VHT_1SS_MCS_9,
	BTC_VHT_2SS_MCS_0,
	BTC_VHT_2SS_MCS_1,
	BTC_VHT_2SS_MCS_2,
	BTC_VHT_2SS_MCS_3,
	BTC_VHT_2SS_MCS_4,
	BTC_VHT_2SS_MCS_5,
	BTC_VHT_2SS_MCS_6,
	BTC_VHT_2SS_MCS_7,
	BTC_VHT_2SS_MCS_8,
	BTC_VHT_2SS_MCS_9,
	BTC_VHT_3SS_MCS_0,
	BTC_VHT_3SS_MCS_1,
	BTC_VHT_3SS_MCS_2,
	BTC_VHT_3SS_MCS_3,
	BTC_VHT_3SS_MCS_4,
	BTC_VHT_3SS_MCS_5,
	BTC_VHT_3SS_MCS_6,
	BTC_VHT_3SS_MCS_7,
	BTC_VHT_3SS_MCS_8,
	BTC_VHT_3SS_MCS_9,
	BTC_VHT_4SS_MCS_0,
	BTC_VHT_4SS_MCS_1,
	BTC_VHT_4SS_MCS_2,
	BTC_VHT_4SS_MCS_3,
	BTC_VHT_4SS_MCS_4,
	BTC_VHT_4SS_MCS_5,
	BTC_VHT_4SS_MCS_6,
	BTC_VHT_4SS_MCS_7,
	BTC_VHT_4SS_MCS_8,
	BTC_VHT_4SS_MCS_9,
	BTC_MCS_32,
	BTC_UNKNOWN,
	BTC_PKT_MGNT,
	BTC_PKT_CTRL,
	BTC_PKT_UNKNOWN,
	BTC_PKT_NOT_FOR_ME,
	BTC_RATE_MAX
पूर्ण;

क्रमागत अणु
	BTC_MULTIPORT_SCC,
	BTC_MULTIPORT_MCC_2CHANNEL,
	BTC_MULTIPORT_MCC_2BAND,
	BTC_MULTIPORT_MAX
पूर्ण;

काष्ठा btc_bt_info अणु
	bool bt_disabled;
	u8 rssi_adjust_क्रम_agc_table_on;
	u8 rssi_adjust_क्रम_1ant_coex_type;
	bool pre_bt_ctrl_agg_buf_size;
	bool bt_busy;
	u8 pre_agg_buf_size;
	u8 agg_buf_size;
	bool limited_dig;
	bool pre_reject_agg_pkt;
	bool reject_agg_pkt;
	bool bt_ctrl_buf_size;
	bool increase_scan_dev_num;
	bool miracast_plus_bt;
	bool bt_ctrl_agg_buf_size;
	bool bt_tx_rx_mask;
	u16 bt_hci_ver;
	u16 bt_real_fw_ver;
	u8 bt_fw_ver;
	u32 bt_get_fw_ver;

	bool bt_disable_low_pwr;

	/* the following is क्रम 1Ant solution */
	bool bt_ctrl_lps;
	bool bt_pwr_save_mode;
	bool bt_lps_on;
	bool क्रमce_to_roam;
	u8 क्रमce_exec_pwr_cmd_cnt;
	u8 lps_val;
	u8 rpwm_val;
	u32 ra_mask;

	u32 afh_map_l;
	u32 afh_map_m;
	u16 afh_map_h;
	u32 bt_supported_feature;
	u32 bt_supported_version;
	u32 bt_device_info;
	u32 bt_क्रमb_slot_val;
	u8 bt_ant_det_val;
	u8 bt_ble_scan_type;
	u32 bt_ble_scan_para;
पूर्ण;

काष्ठा btc_stack_info अणु
	bool profile_notअगरied;
	u16 hci_version;	/* stack hci version */
	u8 num_of_link;
	bool bt_link_exist;
	bool sco_exist;
	bool acl_exist;
	bool a2dp_exist;
	bool hid_exist;
	u8 num_of_hid;
	bool pan_exist;
	bool unknown_acl_exist;
	s8 min_bt_rssi;
पूर्ण;

काष्ठा btc_statistics अणु
	u32 cnt_bind;
	u32 cnt_init_hw_config;
	u32 cnt_init_coex_dm;
	u32 cnt_ips_notअगरy;
	u32 cnt_lps_notअगरy;
	u32 cnt_scan_notअगरy;
	u32 cnt_connect_notअगरy;
	u32 cnt_media_status_notअगरy;
	u32 cnt_special_packet_notअगरy;
	u32 cnt_bt_info_notअगरy;
	u32 cnt_periodical;
	u32 cnt_coex_dm_चयन;
	u32 cnt_stack_operation_notअगरy;
	u32 cnt_dbg_ctrl;
	u32 cnt_pre_load_firmware;
	u32 cnt_घातer_on;
पूर्ण;

काष्ठा btc_bt_link_info अणु
	bool bt_link_exist;
	bool bt_hi_pri_link_exist;
	bool sco_exist;
	bool sco_only;
	bool a2dp_exist;
	bool a2dp_only;
	bool hid_exist;
	bool hid_only;
	bool pan_exist;
	bool pan_only;
	bool slave_role;
	bool acl_busy;
पूर्ण;

क्रमागत btc_antenna_pos अणु
	BTC_ANTENNA_AT_MAIN_PORT = 0x1,
	BTC_ANTENNA_AT_AUX_PORT = 0x2,
पूर्ण;

क्रमागत btc_mp_h2c_op_code अणु
	BT_OP_GET_BT_VERSION			= 0,
	BT_OP_WRITE_REG_ADDR			= 12,
	BT_OP_WRITE_REG_VALUE			= 13,
	BT_OP_READ_REG				= 17,
	BT_OP_GET_AFH_MAP_L			= 30,
	BT_OP_GET_AFH_MAP_M			= 31,
	BT_OP_GET_AFH_MAP_H			= 32,
	BT_OP_GET_BT_COEX_SUPPORTED_FEATURE	= 42,
	BT_OP_GET_BT_COEX_SUPPORTED_VERSION	= 43,
	BT_OP_GET_BT_ANT_DET_VAL		= 44,
	BT_OP_GET_BT_BLE_SCAN_PARA		= 45,
	BT_OP_GET_BT_BLE_SCAN_TYPE		= 46,
	BT_OP_GET_BT_DEVICE_INFO		= 48,
	BT_OP_GET_BT_FORBIDDEN_SLOT_VAL		= 49,
	BT_OP_MAX
पूर्ण;

क्रमागत btc_mp_h2c_req_num अणु
	/* 4 bits only */
	BT_SEQ_DONT_CARE			= 0,
	BT_SEQ_GET_BT_VERSION			= 0xE,
	BT_SEQ_GET_AFH_MAP_L			= 0x5,
	BT_SEQ_GET_AFH_MAP_M			= 0x6,
	BT_SEQ_GET_AFH_MAP_H			= 0x9,
	BT_SEQ_GET_BT_COEX_SUPPORTED_FEATURE	= 0x7,
	BT_SEQ_GET_BT_COEX_SUPPORTED_VERSION	= 0x8,
	BT_SEQ_GET_BT_ANT_DET_VAL		= 0x2,
	BT_SEQ_GET_BT_BLE_SCAN_PARA		= 0x3,
	BT_SEQ_GET_BT_BLE_SCAN_TYPE		= 0x4,
	BT_SEQ_GET_BT_DEVICE_INFO		= 0xA,
	BT_SEQ_GET_BT_FORB_SLOT_VAL		= 0xB,
पूर्ण;

काष्ठा btc_coexist अणु
	/* make sure only one adapter can bind the data context  */
	bool binded;
	/* शेष adapter */
	व्योम *adapter;
	काष्ठा btc_board_info board_info;
	/* some bt info referenced by non-bt module */
	काष्ठा btc_bt_info bt_info;
	काष्ठा btc_stack_info stack_info;
	क्रमागत btc_chip_पूर्णांकerface	chip_पूर्णांकerface;
	काष्ठा btc_bt_link_info bt_link_info;

	/* boolean variables to replace BT_AUTO_REPORT_ONLY_XXXXY_ZANT
	 * configuration parameters
	 */
	bool स्वतः_report_1ant;
	bool स्वतः_report_2ant;
	bool dbg_mode_1ant;
	bool dbg_mode_2ant;
	bool initialized;
	bool stop_coex_dm;
	bool manual_control;
	काष्ठा btc_statistics statistics;
	u8 pwr_mode_val[10];

	काष्ठा completion bt_mp_comp;

	/* function poपूर्णांकers - io related */
	u8 (*btc_पढ़ो_1byte)(व्योम *btc_context, u32 reg_addr);
	व्योम (*btc_ग_लिखो_1byte)(व्योम *btc_context, u32 reg_addr, u32 data);
	व्योम (*btc_ग_लिखो_1byte_biपंचांगask)(व्योम *btc_context, u32 reg_addr,
					u32 bit_mask, u8 data1b);
	u16 (*btc_पढ़ो_2byte)(व्योम *btc_context, u32 reg_addr);
	व्योम (*btc_ग_लिखो_2byte)(व्योम *btc_context, u32 reg_addr, u16 data);
	u32 (*btc_पढ़ो_4byte)(व्योम *btc_context, u32 reg_addr);
	व्योम (*btc_ग_लिखो_4byte)(व्योम *btc_context, u32 reg_addr, u32 data);

	व्योम (*btc_ग_लिखो_local_reg_1byte)(व्योम *btc_context, u32 reg_addr,
					  u8 data);
	व्योम (*btc_set_bb_reg)(व्योम *btc_context, u32 reg_addr,
			       u32 bit_mask, u32 data);
	u32 (*btc_get_bb_reg)(व्योम *btc_context, u32 reg_addr,
			      u32 bit_mask);
	व्योम (*btc_set_rf_reg)(व्योम *btc_context, u8 rf_path, u32 reg_addr,
			       u32 bit_mask, u32 data);
	u32 (*btc_get_rf_reg)(व्योम *btc_context, u8 rf_path,
			      u32 reg_addr, u32 bit_mask);

	व्योम (*btc_fill_h2c)(व्योम *btc_context, u8 element_id,
			     u32 cmd_len, u8 *cmd_buffer);

	व्योम (*btc_disp_dbg_msg)(व्योम *btcoexist, u8 disp_type,
				 काष्ठा seq_file *m);

	bool (*btc_get)(व्योम *btcoexist, u8 get_type, व्योम *out_buf);
	bool (*btc_set)(व्योम *btcoexist, u8 set_type, व्योम *in_buf);

	व्योम (*btc_set_bt_reg)(व्योम *btc_context, u8 reg_type, u32 offset,
			       u32 value);
	u32 (*btc_get_bt_reg)(व्योम *btc_context, u8 reg_type, u32 offset);
	u32 (*btc_get_bt_coex_supported_feature)(व्योम *btcoexist);
	u32 (*btc_get_bt_coex_supported_version)(व्योम *btcoexist);
	u32 (*btc_get_bt_phydm_version)(व्योम *btcoexist);
	व्योम (*btc_phydm_modअगरy_ra_pcr_threshold)(व्योम *btcoexist,
						  u8 ra_offset_direction,
						  u8 ra_threshold_offset);
	u32 (*btc_phydm_query_phy_counter)(व्योम *btcoexist,
					   क्रमागत dm_info_query dm_id);
	u8 (*btc_get_ant_det_val_from_bt)(व्योम *btcoexist);
	u8 (*btc_get_ble_scan_type_from_bt)(व्योम *btcoexist);
	u32 (*btc_get_ble_scan_para_from_bt)(व्योम *btcoexist, u8 scan_type);
	bool (*btc_get_bt_afh_map_from_bt)(व्योम *btcoexist, u8 map_type,
					   u8 *afh_map);
पूर्ण;

bool halbtc_is_wअगरi_uplink(काष्ठा rtl_priv *adapter);

#घोषणा rtl_btc_coexist(rtlpriv)				\
	((काष्ठा btc_coexist *)((rtlpriv)->btcoexist.btc_context))
#घोषणा rtl_btc_wअगरi_only(rtlpriv)				\
	((काष्ठा wअगरi_only_cfg *)((rtlpriv)->btcoexist.wअगरi_only_context))

काष्ठा wअगरi_only_cfg;

bool exhalbtc_initlize_variables(काष्ठा rtl_priv *rtlpriv);
bool exhalbtc_initlize_variables_wअगरi_only(काष्ठा rtl_priv *rtlpriv);
bool exhalbtc_bind_bt_coex_withadapter(व्योम *adapter);
व्योम exhalbtc_घातer_on_setting(काष्ठा btc_coexist *btcoexist);
व्योम exhalbtc_pre_load_firmware(काष्ठा btc_coexist *btcoexist);
व्योम exhalbtc_init_hw_config(काष्ठा btc_coexist *btcoexist, bool wअगरi_only);
व्योम exhalbtc_init_hw_config_wअगरi_only(काष्ठा wअगरi_only_cfg *wअगरionly_cfg);
व्योम exhalbtc_init_coex_dm(काष्ठा btc_coexist *btcoexist);
व्योम exhalbtc_ips_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम exhalbtc_lps_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम exhalbtc_scan_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम exhalbtc_scan_notअगरy_wअगरi_only(काष्ठा wअगरi_only_cfg *wअगरionly_cfg,
				    u8 is_5g);
व्योम exhalbtc_connect_notअगरy(काष्ठा btc_coexist *btcoexist, u8 action);
व्योम exhalbtc_mediastatus_notअगरy(काष्ठा btc_coexist *btcoexist,
				 क्रमागत rt_media_status media_status);
व्योम exhalbtc_special_packet_notअगरy(काष्ठा btc_coexist *btcoexist, u8 pkt_type);
व्योम exhalbtc_bt_info_notअगरy(काष्ठा btc_coexist *btcoexist, u8 *पंचांगp_buf,
			     u8 length);
व्योम exhalbtc_rf_status_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम exhalbtc_halt_notअगरy(काष्ठा btc_coexist *btcoexist);
व्योम exhalbtc_pnp_notअगरy(काष्ठा btc_coexist *btcoexist, u8 pnp_state);
व्योम exhalbtc_coex_dm_चयन(काष्ठा btc_coexist *btcoexist);
व्योम exhalbtc_periodical(काष्ठा btc_coexist *btcoexist);
व्योम exhalbtc_dbg_control(काष्ठा btc_coexist *btcoexist, u8 code, u8 len,
			  u8 *data);
व्योम exhalbtc_antenna_detection(काष्ठा btc_coexist *btcoexist, u32 cent_freq,
				u32 offset, u32 span, u32 seconds);
व्योम exhalbtc_stack_update_profile_info(व्योम);
व्योम exhalbtc_set_hci_version(काष्ठा btc_coexist *btcoexist, u16 hci_version);
व्योम exhalbtc_set_bt_patch_version(काष्ठा btc_coexist *btcoexist,
				   u16 bt_hci_version, u16 bt_patch_version);
व्योम exhalbtc_update_min_bt_rssi(काष्ठा btc_coexist *btcoexist, s8 bt_rssi);
व्योम exhalbtc_set_bt_exist(काष्ठा btc_coexist *btcoexist, bool bt_exist);
व्योम exhalbtc_set_chip_type(काष्ठा btc_coexist *btcoexist, u8 chip_type);
व्योम exhalbtc_set_ant_num(काष्ठा rtl_priv *rtlpriv, u8 type, u8 ant_num);
व्योम exhalbtc_display_bt_coex_info(काष्ठा btc_coexist *btcoexist,
				   काष्ठा seq_file *m);
व्योम exhalbtc_चयन_band_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम exhalbtc_चयन_band_notअगरy_wअगरi_only(काष्ठा wअगरi_only_cfg *wअगरionly_cfg,
					   u8 is_5g);
व्योम exhalbtc_संकेत_compensation(काष्ठा btc_coexist *btcoexist,
				  u8 *rssi_wअगरi, u8 *rssi_bt);
व्योम exhalbtc_lps_leave(काष्ठा btc_coexist *btcoexist);
व्योम exhalbtc_low_wअगरi_traffic_notअगरy(काष्ठा btc_coexist *btcoexist);
व्योम exhalbtc_set_single_ant_path(काष्ठा btc_coexist *btcoexist,
				  u8 single_ant_path);
व्योम halbtc_send_wअगरi_port_id_cmd(व्योम *bt_context);
व्योम halbtc_set_शेष_port_id_cmd(व्योम *bt_context);

/* The following are used by wअगरi_only हाल */
क्रमागत wअगरionly_chip_पूर्णांकerface अणु
	WIFIONLY_INTF_UNKNOWN	= 0,
	WIFIONLY_INTF_PCI		= 1,
	WIFIONLY_INTF_USB		= 2,
	WIFIONLY_INTF_SDIO		= 3,
	WIFIONLY_INTF_MAX
पूर्ण;

क्रमागत wअगरionly_customer_id अणु
	CUSTOMER_NORMAL			= 0,
	CUSTOMER_HP_1			= 1,
पूर्ण;

काष्ठा wअगरi_only_haldata अणु
	u16		customer_id;
	u8		efuse_pg_antnum;
	u8		efuse_pg_antpath;
	u8		rfe_type;
	u8		ant_भाग_cfg;
पूर्ण;

काष्ठा wअगरi_only_cfg अणु
	व्योम				*adapter;
	काष्ठा wअगरi_only_haldata	haldata_info;
	क्रमागत wअगरionly_chip_पूर्णांकerface	chip_पूर्णांकerface;
पूर्ण;

अटल अंतरभूत
व्योम halwअगरionly_phy_set_bb_reg(काष्ठा wअगरi_only_cfg *wअगरi_conly_cfg,
				u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = (काष्ठा rtl_priv *)wअगरi_conly_cfg->adapter;

	rtl_set_bbreg(rtlpriv->hw, regaddr, biपंचांगask, data);
पूर्ण

#पूर्ण_अगर
