<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_WIFI_H__
#घोषणा __RTL_WIFI_H__

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/usb.h>
#समावेश <net/mac80211.h>
#समावेश <linux/completion.h>
#समावेश <linux/bitfield.h>
#समावेश "debug.h"

#घोषणा	MASKBYTE0				0xff
#घोषणा	MASKBYTE1				0xff00
#घोषणा	MASKBYTE2				0xff0000
#घोषणा	MASKBYTE3				0xff000000
#घोषणा	MASKHWORD				0xffff0000
#घोषणा	MASKLWORD				0x0000ffff
#घोषणा	MASKDWORD				0xffffffff
#घोषणा	MASK12BITS				0xfff
#घोषणा	MASKH4BITS				0xf0000000
#घोषणा MASKOFDM_D				0xffc00000
#घोषणा	MASKCCK					0x3f3f3f3f

#घोषणा	MASK4BITS				0x0f
#घोषणा	MASK20BITS				0xfffff
#घोषणा RFREG_OFFSET_MASK			0xfffff

#घोषणा	MASKBYTE0				0xff
#घोषणा	MASKBYTE1				0xff00
#घोषणा	MASKBYTE2				0xff0000
#घोषणा	MASKBYTE3				0xff000000
#घोषणा	MASKHWORD				0xffff0000
#घोषणा	MASKLWORD				0x0000ffff
#घोषणा	MASKDWORD				0xffffffff
#घोषणा	MASK12BITS				0xfff
#घोषणा	MASKH4BITS				0xf0000000
#घोषणा MASKOFDM_D				0xffc00000
#घोषणा	MASKCCK					0x3f3f3f3f

#घोषणा	MASK4BITS				0x0f
#घोषणा	MASK20BITS				0xfffff
#घोषणा RFREG_OFFSET_MASK			0xfffff

#घोषणा RF_CHANGE_BY_INIT			0
#घोषणा RF_CHANGE_BY_IPS			BIT(28)
#घोषणा RF_CHANGE_BY_PS				BIT(29)
#घोषणा RF_CHANGE_BY_HW				BIT(30)
#घोषणा RF_CHANGE_BY_SW				BIT(31)

#घोषणा IQK_ADDA_REG_NUM			16
#घोषणा IQK_MAC_REG_NUM				4
#घोषणा IQK_THRESHOLD				8

#घोषणा MAX_KEY_LEN				61
#घोषणा KEY_BUF_SIZE				5

/* QoS related. */
/*aci: 0x00	Best Efक्रमt*/
/*aci: 0x01	Background*/
/*aci: 0x10	Video*/
/*aci: 0x11	Voice*/
/*Max: define total number.*/
#घोषणा AC0_BE					0
#घोषणा AC1_BK					1
#घोषणा AC2_VI					2
#घोषणा AC3_VO					3
#घोषणा AC_MAX					4
#घोषणा QOS_QUEUE_NUM				4
#घोषणा RTL_MAC80211_NUM_QUEUE			5
#घोषणा REALTEK_USB_VENQT_MAX_BUF_SIZE		254
#घोषणा RTL_USB_MAX_RX_COUNT			100
#घोषणा QBSS_LOAD_SIZE				5
#घोषणा MAX_WMMELE_LENGTH			64
#घोषणा ASPM_L1_LATENCY				7

#घोषणा TOTAL_CAM_ENTRY				32

/*slot समय क्रम 11g. */
#घोषणा RTL_SLOT_TIME_9				9
#घोषणा RTL_SLOT_TIME_20			20

/*related to tcp/ip. */
#घोषणा SNAP_SIZE		6
#घोषणा PROTOC_TYPE_SIZE	2

/*related with 802.11 frame*/
#घोषणा MAC80211_3ADDR_LEN			24
#घोषणा MAC80211_4ADDR_LEN			30

#घोषणा CHANNEL_MAX_NUMBER	(14 + 24 + 21)	/* 14 is the max channel no */
#घोषणा CHANNEL_MAX_NUMBER_2G		14
#घोषणा CHANNEL_MAX_NUMBER_5G		49 /* Please refer to
					    *"phy_GetChnlGroup8812A" and
					    * "Hal_ReadTxPowerInfo8812A"
					    */
#घोषणा CHANNEL_MAX_NUMBER_5G_80M	7
#घोषणा CHANNEL_GROUP_MAX	(3 + 9)	/*  ch1~3, 4~9, 10~14 = three groups */
#घोषणा MAX_PG_GROUP			13
#घोषणा	CHANNEL_GROUP_MAX_2G		3
#घोषणा	CHANNEL_GROUP_IDX_5GL		3
#घोषणा	CHANNEL_GROUP_IDX_5GM		6
#घोषणा	CHANNEL_GROUP_IDX_5GH		9
#घोषणा	CHANNEL_GROUP_MAX_5G		9
#घोषणा CHANNEL_MAX_NUMBER_2G		14
#घोषणा AVG_THERMAL_NUM			8
#घोषणा AVG_THERMAL_NUM_88E		4
#घोषणा AVG_THERMAL_NUM_8723BE		4
#घोषणा MAX_TID_COUNT			9

/* क्रम early mode */
#घोषणा FCS_LEN				4
#घोषणा EM_HDR_LEN			8

क्रमागत rtl8192c_h2c_cmd अणु
	H2C_AP_OFFLOAD = 0,
	H2C_SETPWRMODE = 1,
	H2C_JOINBSSRPT = 2,
	H2C_RSVDPAGE = 3,
	H2C_RSSI_REPORT = 5,
	H2C_RA_MASK = 6,
	H2C_MACID_PS_MODE = 7,
	H2C_P2P_PS_OFFLOAD = 8,
	H2C_MAC_MODE_SEL = 9,
	H2C_PWRM = 15,
	H2C_P2P_PS_CTW_CMD = 24,
	MAX_H2CCMD
पूर्ण;

क्रमागत अणु
	H2C_BT_PORT_ID = 0x71,
पूर्ण;

क्रमागत rtl_c2h_evt_v1 अणु
	C2H_DBG = 0,
	C2H_LB = 1,
	C2H_TXBF = 2,
	C2H_TX_REPORT = 3,
	C2H_BT_INFO = 9,
	C2H_BT_MP = 11,
	C2H_RA_RPT = 12,

	C2H_FW_SWCHNL = 0x10,
	C2H_IQK_FINISH = 0x11,

	C2H_EXT_V2 = 0xFF,
पूर्ण;

क्रमागत rtl_c2h_evt_v2 अणु
	C2H_V2_CCX_RPT = 0x0F,
पूर्ण;

#घोषणा GET_C2H_CMD_ID(c2h)	(अणुu8 *__c2h = c2h; __c2h[0]; पूर्ण)
#घोषणा GET_C2H_SEQ(c2h)	(अणुu8 *__c2h = c2h; __c2h[1]; पूर्ण)
#घोषणा C2H_DATA_OFFSET		2
#घोषणा GET_C2H_DATA_PTR(c2h)	(अणुu8 *__c2h = c2h; &__c2h[C2H_DATA_OFFSET]; पूर्ण)

#घोषणा GET_TX_REPORT_SN_V1(c2h)	(c2h[6])
#घोषणा GET_TX_REPORT_ST_V1(c2h)	(c2h[0] & 0xC0)
#घोषणा GET_TX_REPORT_RETRY_V1(c2h)	(c2h[2] & 0x3F)
#घोषणा GET_TX_REPORT_SN_V2(c2h)	(c2h[6])
#घोषणा GET_TX_REPORT_ST_V2(c2h)	(c2h[7] & 0xC0)
#घोषणा GET_TX_REPORT_RETRY_V2(c2h)	(c2h[8] & 0x3F)

#घोषणा MAX_TX_COUNT			4
#घोषणा MAX_REGULATION_NUM		4
#घोषणा MAX_RF_PATH_NUM			4
#घोषणा MAX_RATE_SECTION_NUM		6	/* = MAX_RATE_SECTION */
#घोषणा MAX_2_4G_BANDWIDTH_NUM		4
#घोषणा MAX_5G_BANDWIDTH_NUM		4
#घोषणा	MAX_RF_PATH			4
#घोषणा	MAX_CHNL_GROUP_24G		6
#घोषणा	MAX_CHNL_GROUP_5G		14

#घोषणा TX_PWR_BY_RATE_NUM_BAND		2
#घोषणा TX_PWR_BY_RATE_NUM_RF		4
#घोषणा TX_PWR_BY_RATE_NUM_SECTION	12
#घोषणा TX_PWR_BY_RATE_NUM_RATE		84 /* >= TX_PWR_BY_RATE_NUM_SECTION */
#घोषणा MAX_BASE_NUM_IN_PHY_REG_PG_24G	6  /* MAX_RATE_SECTION */
#घोषणा MAX_BASE_NUM_IN_PHY_REG_PG_5G	5  /* MAX_RATE_SECTION -1 */

#घोषणा BUFDESC_SEG_NUM		1 /* 0:2 seg, 1: 4 seg, 2: 8 seg */

#घोषणा DEL_SW_IDX_SZ		30

/* For now, it's just क्रम 8192ee
 * but not OK yet, keep it 0
 */
#घोषणा RTL8192EE_SEG_NUM		BUFDESC_SEG_NUM

क्रमागत rf_tx_num अणु
	RF_1TX = 0,
	RF_2TX,
	RF_MAX_TX_NUM,
	RF_TX_NUM_NONIMPLEMENT,
पूर्ण;

#घोषणा PACKET_NORMAL			0
#घोषणा PACKET_DHCP			1
#घोषणा PACKET_ARP			2
#घोषणा PACKET_EAPOL			3

#घोषणा	MAX_SUPPORT_WOL_PATTERN_NUM	16
#घोषणा	RSVD_WOL_PATTERN_NUM		1
#घोषणा	WKFMCAM_ADDR_NUM		6
#घोषणा	WKFMCAM_SIZE			24

#घोषणा	MAX_WOL_BIT_MASK_SIZE		16
/* MIN LEN keeps 13 here */
#घोषणा	MIN_WOL_PATTERN_SIZE		13
#घोषणा	MAX_WOL_PATTERN_SIZE		128

#घोषणा	WAKE_ON_MAGIC_PACKET		BIT(0)
#घोषणा	WAKE_ON_PATTERN_MATCH		BIT(1)

#घोषणा	WOL_REASON_PTK_UPDATE		BIT(0)
#घोषणा	WOL_REASON_GTK_UPDATE		BIT(1)
#घोषणा	WOL_REASON_DISASSOC		BIT(2)
#घोषणा	WOL_REASON_DEAUTH		BIT(3)
#घोषणा	WOL_REASON_AP_LOST		BIT(4)
#घोषणा	WOL_REASON_MAGIC_PKT		BIT(5)
#घोषणा	WOL_REASON_UNICAST_PKT		BIT(6)
#घोषणा	WOL_REASON_PATTERN_PKT		BIT(7)
#घोषणा	WOL_REASON_RTD3_SSID_MATCH	BIT(8)
#घोषणा	WOL_REASON_REALWOW_V2_WAKEUPPKT	BIT(9)
#घोषणा	WOL_REASON_REALWOW_V2_ACKLOST	BIT(10)

काष्ठा rtlwअगरi_firmware_header अणु
	__le16 signature;
	u8 category;
	u8 function;
	__le16 version;
	u8 subversion;
	u8 rsvd1;
	u8 month;
	u8 date;
	u8 hour;
	u8 minute;
	__le16 ramcodesize;
	__le16 rsvd2;
	__le32 svnindex;
	__le32 rsvd3;
	__le32 rsvd4;
	__le32 rsvd5;
पूर्ण;

काष्ठा txघातer_info_2g अणु
	u8 index_cck_base[MAX_RF_PATH][MAX_CHNL_GROUP_24G];
	u8 index_bw40_base[MAX_RF_PATH][MAX_CHNL_GROUP_24G];
	/*If only one tx, only BW20 and OFDM are used.*/
	u8 cck_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 ofdm_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 bw20_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 bw40_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 bw80_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 bw160_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
पूर्ण;

काष्ठा txघातer_info_5g अणु
	u8 index_bw40_base[MAX_RF_PATH][MAX_CHNL_GROUP_5G];
	/*If only one tx, only BW20, OFDM, BW80 and BW160 are used.*/
	u8 ofdm_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 bw20_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 bw40_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 bw80_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	u8 bw160_dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
पूर्ण;

क्रमागत rate_section अणु
	CCK = 0,
	OFDM,
	HT_MCS0_MCS7,
	HT_MCS8_MCS15,
	VHT_1SSMCS0_1SSMCS9,
	VHT_2SSMCS0_2SSMCS9,
	MAX_RATE_SECTION,
पूर्ण;

क्रमागत पूर्णांकf_type अणु
	INTF_PCI = 0,
	INTF_USB = 1,
पूर्ण;

क्रमागत radio_path अणु
	RF90_PATH_A = 0,
	RF90_PATH_B = 1,
	RF90_PATH_C = 2,
	RF90_PATH_D = 3,
पूर्ण;

क्रमागत radio_mask अणु
	RF_MASK_A = BIT(0),
	RF_MASK_B = BIT(1),
	RF_MASK_C = BIT(2),
	RF_MASK_D = BIT(3),
पूर्ण;

क्रमागत regulation_txpwr_lmt अणु
	TXPWR_LMT_FCC = 0,
	TXPWR_LMT_MKK = 1,
	TXPWR_LMT_ETSI = 2,
	TXPWR_LMT_WW = 3,

	TXPWR_LMT_MAX_REGULATION_NUM = 4
पूर्ण;

क्रमागत rt_eeprom_type अणु
	EEPROM_93C46,
	EEPROM_93C56,
	EEPROM_BOOT_EFUSE,
पूर्ण;

क्रमागत ttl_status अणु
	RTL_STATUS_INTERFACE_START = 0,
पूर्ण;

क्रमागत hardware_type अणु
	HARDWARE_TYPE_RTL8192E,
	HARDWARE_TYPE_RTL8192U,
	HARDWARE_TYPE_RTL8192SE,
	HARDWARE_TYPE_RTL8192SU,
	HARDWARE_TYPE_RTL8192CE,
	HARDWARE_TYPE_RTL8192CU,
	HARDWARE_TYPE_RTL8192DE,
	HARDWARE_TYPE_RTL8192DU,
	HARDWARE_TYPE_RTL8723AE,
	HARDWARE_TYPE_RTL8723U,
	HARDWARE_TYPE_RTL8188EE,
	HARDWARE_TYPE_RTL8723BE,
	HARDWARE_TYPE_RTL8192EE,
	HARDWARE_TYPE_RTL8821AE,
	HARDWARE_TYPE_RTL8812AE,
	HARDWARE_TYPE_RTL8822BE,

	/* keep it last */
	HARDWARE_TYPE_NUM
पूर्ण;

#घोषणा RTL_HW_TYPE(rtlpriv)	(rtl_hal((काष्ठा rtl_priv *)rtlpriv)->hw_type)
#घोषणा IS_NEW_GENERATION_IC(rtlpriv)			\
			(RTL_HW_TYPE(rtlpriv) >= HARDWARE_TYPE_RTL8192EE)
#घोषणा IS_HARDWARE_TYPE_8192CE(rtlpriv)		\
			(RTL_HW_TYPE(rtlpriv) == HARDWARE_TYPE_RTL8192CE)
#घोषणा IS_HARDWARE_TYPE_8812(rtlpriv)			\
			(RTL_HW_TYPE(rtlpriv) == HARDWARE_TYPE_RTL8812AE)
#घोषणा IS_HARDWARE_TYPE_8821(rtlpriv)			\
			(RTL_HW_TYPE(rtlpriv) == HARDWARE_TYPE_RTL8821AE)
#घोषणा IS_HARDWARE_TYPE_8723A(rtlpriv)			\
			(RTL_HW_TYPE(rtlpriv) == HARDWARE_TYPE_RTL8723AE)
#घोषणा IS_HARDWARE_TYPE_8723B(rtlpriv)			\
			(RTL_HW_TYPE(rtlpriv) == HARDWARE_TYPE_RTL8723BE)
#घोषणा IS_HARDWARE_TYPE_8192E(rtlpriv)			\
			(RTL_HW_TYPE(rtlpriv) == HARDWARE_TYPE_RTL8192EE)
#घोषणा IS_HARDWARE_TYPE_8822B(rtlpriv)			\
			(RTL_HW_TYPE(rtlpriv) == HARDWARE_TYPE_RTL8822BE)

#घोषणा RX_HAL_IS_CCK_RATE(rxmcs)			\
	((rxmcs) == DESC_RATE1M ||			\
	 (rxmcs) == DESC_RATE2M ||			\
	 (rxmcs) == DESC_RATE5_5M ||			\
	 (rxmcs) == DESC_RATE11M)

क्रमागत scan_operation_backup_opt अणु
	SCAN_OPT_BACKUP = 0,
	SCAN_OPT_BACKUP_BAND0 = 0,
	SCAN_OPT_BACKUP_BAND1,
	SCAN_OPT_RESTORE,
	SCAN_OPT_MAX
पूर्ण;

/*RF state.*/
क्रमागत rf_pwrstate अणु
	ERFON,
	ERFSLEEP,
	ERFOFF
पूर्ण;

काष्ठा bb_reg_def अणु
	u32 rfपूर्णांकfs;
	u32 rfपूर्णांकfi;
	u32 rfपूर्णांकfo;
	u32 rfपूर्णांकfe;
	u32 rf3wire_offset;
	u32 rflssi_select;
	u32 rftxgain_stage;
	u32 rfhssi_para1;
	u32 rfhssi_para2;
	u32 rfsw_ctrl;
	u32 rfagc_control1;
	u32 rfagc_control2;
	u32 rfrxiq_imbal;
	u32 rfrx_afe;
	u32 rftxiq_imbal;
	u32 rftx_afe;
	u32 rf_rb;		/* rflssi_पढ़ोback */
	u32 rf_rbpi;		/* rflssi_पढ़ोbackpi */
पूर्ण;

क्रमागत io_type अणु
	IO_CMD_PAUSE_DM_BY_SCAN = 0,
	IO_CMD_PAUSE_BAND0_DM_BY_SCAN = 0,
	IO_CMD_PAUSE_BAND1_DM_BY_SCAN = 1,
	IO_CMD_RESUME_DM_BY_SCAN = 2,
पूर्ण;

क्रमागत hw_variables अणु
	HW_VAR_ETHER_ADDR = 0x0,
	HW_VAR_MULTICAST_REG = 0x1,
	HW_VAR_BASIC_RATE = 0x2,
	HW_VAR_BSSID = 0x3,
	HW_VAR_MEDIA_STATUS = 0x4,
	HW_VAR_SECURITY_CONF = 0x5,
	HW_VAR_BEACON_INTERVAL = 0x6,
	HW_VAR_ATIM_WINDOW = 0x7,
	HW_VAR_LISTEN_INTERVAL = 0x8,
	HW_VAR_CS_COUNTER = 0x9,
	HW_VAR_DEFAULTKEY0 = 0xa,
	HW_VAR_DEFAULTKEY1 = 0xb,
	HW_VAR_DEFAULTKEY2 = 0xc,
	HW_VAR_DEFAULTKEY3 = 0xd,
	HW_VAR_SIFS = 0xe,
	HW_VAR_R2T_SIFS = 0xf,
	HW_VAR_DIFS = 0x10,
	HW_VAR_EIFS = 0x11,
	HW_VAR_SLOT_TIME = 0x12,
	HW_VAR_ACK_PREAMBLE = 0x13,
	HW_VAR_CW_CONFIG = 0x14,
	HW_VAR_CW_VALUES = 0x15,
	HW_VAR_RATE_FALLBACK_CONTROL = 0x16,
	HW_VAR_CONTENTION_WINDOW = 0x17,
	HW_VAR_RETRY_COUNT = 0x18,
	HW_VAR_TR_SWITCH = 0x19,
	HW_VAR_COMMAND = 0x1a,
	HW_VAR_WPA_CONFIG = 0x1b,
	HW_VAR_AMPDU_MIN_SPACE = 0x1c,
	HW_VAR_SHORTGI_DENSITY = 0x1d,
	HW_VAR_AMPDU_FACTOR = 0x1e,
	HW_VAR_MCS_RATE_AVAILABLE = 0x1f,
	HW_VAR_AC_PARAM = 0x20,
	HW_VAR_ACM_CTRL = 0x21,
	HW_VAR_DIS_REQ_QSIZE = 0x22,
	HW_VAR_CCX_CHNL_LOAD = 0x23,
	HW_VAR_CCX_NOISE_HISTOGRAM = 0x24,
	HW_VAR_CCX_CLM_NHM = 0x25,
	HW_VAR_TXOPLIMIT = 0x26,
	HW_VAR_TURBO_MODE = 0x27,
	HW_VAR_RF_STATE = 0x28,
	HW_VAR_RF_OFF_BY_HW = 0x29,
	HW_VAR_BUS_SPEED = 0x2a,
	HW_VAR_SET_DEV_POWER = 0x2b,

	HW_VAR_RCR = 0x2c,
	HW_VAR_RATR_0 = 0x2d,
	HW_VAR_RRSR = 0x2e,
	HW_VAR_CPU_RST = 0x2f,
	HW_VAR_CHECK_BSSID = 0x30,
	HW_VAR_LBK_MODE = 0x31,
	HW_VAR_AES_11N_FIX = 0x32,
	HW_VAR_USB_RX_AGGR = 0x33,
	HW_VAR_USER_CONTROL_TURBO_MODE = 0x34,
	HW_VAR_RETRY_LIMIT = 0x35,
	HW_VAR_INIT_TX_RATE = 0x36,
	HW_VAR_TX_RATE_REG = 0x37,
	HW_VAR_EFUSE_USAGE = 0x38,
	HW_VAR_EFUSE_BYTES = 0x39,
	HW_VAR_AUTOLOAD_STATUS = 0x3a,
	HW_VAR_RF_2R_DISABLE = 0x3b,
	HW_VAR_SET_RPWM = 0x3c,
	HW_VAR_H2C_FW_PWRMODE = 0x3d,
	HW_VAR_H2C_FW_JOINBSSRPT = 0x3e,
	HW_VAR_H2C_FW_MEDIASTATUSRPT = 0x3f,
	HW_VAR_H2C_FW_P2P_PS_OFFLOAD = 0x40,
	HW_VAR_FW_PSMODE_STATUS = 0x41,
	HW_VAR_INIT_RTS_RATE = 0x42,
	HW_VAR_RESUME_CLK_ON = 0x43,
	HW_VAR_FW_LPS_ACTION = 0x44,
	HW_VAR_1X1_RECV_COMBINE = 0x45,
	HW_VAR_STOP_SEND_BEACON = 0x46,
	HW_VAR_TSF_TIMER = 0x47,
	HW_VAR_IO_CMD = 0x48,

	HW_VAR_RF_RECOVERY = 0x49,
	HW_VAR_H2C_FW_UPDATE_GTK = 0x4a,
	HW_VAR_WF_MASK = 0x4b,
	HW_VAR_WF_CRC = 0x4c,
	HW_VAR_WF_IS_MAC_ADDR = 0x4d,
	HW_VAR_H2C_FW_OFFLOAD = 0x4e,
	HW_VAR_RESET_WFCRC = 0x4f,

	HW_VAR_HANDLE_FW_C2H = 0x50,
	HW_VAR_DL_FW_RSVD_PAGE = 0x51,
	HW_VAR_AID = 0x52,
	HW_VAR_HW_SEQ_ENABLE = 0x53,
	HW_VAR_CORRECT_TSF = 0x54,
	HW_VAR_BCN_VALID = 0x55,
	HW_VAR_FWLPS_RF_ON = 0x56,
	HW_VAR_DUAL_TSF_RST = 0x57,
	HW_VAR_SWITCH_EPHY_WOWLAN = 0x58,
	HW_VAR_INT_MIGRATION = 0x59,
	HW_VAR_INT_AC = 0x5a,
	HW_VAR_RF_TIMING = 0x5b,

	HAL_DEF_WOWLAN = 0x5c,
	HW_VAR_MRC = 0x5d,
	HW_VAR_KEEP_ALIVE = 0x5e,
	HW_VAR_NAV_UPPER = 0x5f,

	HW_VAR_MGT_FILTER = 0x60,
	HW_VAR_CTRL_FILTER = 0x61,
	HW_VAR_DATA_FILTER = 0x62,
पूर्ण;

क्रमागत rt_media_status अणु
	RT_MEDIA_DISCONNECT = 0,
	RT_MEDIA_CONNECT = 1
पूर्ण;

क्रमागत rt_oem_id अणु
	RT_CID_DEFAULT = 0,
	RT_CID_8187_ALPHA0 = 1,
	RT_CID_8187_SERCOMM_PS = 2,
	RT_CID_8187_HW_LED = 3,
	RT_CID_8187_NETGEAR = 4,
	RT_CID_WHQL = 5,
	RT_CID_819X_CAMEO = 6,
	RT_CID_819X_RUNTOP = 7,
	RT_CID_819X_SENAO = 8,
	RT_CID_TOSHIBA = 9,
	RT_CID_819X_NETCORE = 10,
	RT_CID_NETTRONIX = 11,
	RT_CID_DLINK = 12,
	RT_CID_PRONET = 13,
	RT_CID_COREGA = 14,
	RT_CID_819X_ALPHA = 15,
	RT_CID_819X_SITECOM = 16,
	RT_CID_CCX = 17,
	RT_CID_819X_LENOVO = 18,
	RT_CID_819X_QMI = 19,
	RT_CID_819X_EDIMAX_BELKIN = 20,
	RT_CID_819X_SERCOMM_BELKIN = 21,
	RT_CID_819X_CAMEO1 = 22,
	RT_CID_819X_MSI = 23,
	RT_CID_819X_ACER = 24,
	RT_CID_819X_HP = 27,
	RT_CID_819X_CLEVO = 28,
	RT_CID_819X_ARCADYAN_BELKIN = 29,
	RT_CID_819X_SAMSUNG = 30,
	RT_CID_819X_WNC_COREGA = 31,
	RT_CID_819X_FOXCOON = 32,
	RT_CID_819X_DELL = 33,
	RT_CID_819X_PRONETS = 34,
	RT_CID_819X_EDIMAX_ASUS = 35,
	RT_CID_NETGEAR = 36,
	RT_CID_PLANEX = 37,
	RT_CID_CC_C = 38,
	RT_CID_LENOVO_CHINA = 40,
पूर्ण;

क्रमागत hw_descs अणु
	HW_DESC_OWN,
	HW_DESC_RXOWN,
	HW_DESC_TX_NEXTDESC_ADDR,
	HW_DESC_TXBUFF_ADDR,
	HW_DESC_RXBUFF_ADDR,
	HW_DESC_RXPKT_LEN,
	HW_DESC_RXERO,
	HW_DESC_RX_PREPARE,
पूर्ण;

क्रमागत prime_sc अणु
	PRIME_CHNL_OFFSET_DONT_CARE = 0,
	PRIME_CHNL_OFFSET_LOWER = 1,
	PRIME_CHNL_OFFSET_UPPER = 2,
पूर्ण;

क्रमागत rf_type अणु
	RF_1T1R = 0,
	RF_1T2R = 1,
	RF_2T2R = 2,
	RF_2T2R_GREEN = 3,
	RF_2T3R = 4,
	RF_2T4R = 5,
	RF_3T3R = 6,
	RF_3T4R = 7,
	RF_4T4R = 8,
पूर्ण;

क्रमागत ht_channel_width अणु
	HT_CHANNEL_WIDTH_20 = 0,
	HT_CHANNEL_WIDTH_20_40 = 1,
	HT_CHANNEL_WIDTH_80 = 2,
	HT_CHANNEL_WIDTH_MAX,
पूर्ण;

/* Ref: 802.11i spec D10.0 7.3.2.25.1
 * Cipher Suites Encryption Algorithms
 */
क्रमागत rt_enc_alg अणु
	NO_ENCRYPTION = 0,
	WEP40_ENCRYPTION = 1,
	TKIP_ENCRYPTION = 2,
	RSERVED_ENCRYPTION = 3,
	AESCCMP_ENCRYPTION = 4,
	WEP104_ENCRYPTION = 5,
	AESCMAC_ENCRYPTION = 6,	/*IEEE802.11w */
पूर्ण;

क्रमागत rtl_hal_state अणु
	_HAL_STATE_STOP = 0,
	_HAL_STATE_START = 1,
पूर्ण;

क्रमागत rtl_desc_rate अणु
	DESC_RATE1M = 0x00,
	DESC_RATE2M = 0x01,
	DESC_RATE5_5M = 0x02,
	DESC_RATE11M = 0x03,

	DESC_RATE6M = 0x04,
	DESC_RATE9M = 0x05,
	DESC_RATE12M = 0x06,
	DESC_RATE18M = 0x07,
	DESC_RATE24M = 0x08,
	DESC_RATE36M = 0x09,
	DESC_RATE48M = 0x0a,
	DESC_RATE54M = 0x0b,

	DESC_RATEMCS0 = 0x0c,
	DESC_RATEMCS1 = 0x0d,
	DESC_RATEMCS2 = 0x0e,
	DESC_RATEMCS3 = 0x0f,
	DESC_RATEMCS4 = 0x10,
	DESC_RATEMCS5 = 0x11,
	DESC_RATEMCS6 = 0x12,
	DESC_RATEMCS7 = 0x13,
	DESC_RATEMCS8 = 0x14,
	DESC_RATEMCS9 = 0x15,
	DESC_RATEMCS10 = 0x16,
	DESC_RATEMCS11 = 0x17,
	DESC_RATEMCS12 = 0x18,
	DESC_RATEMCS13 = 0x19,
	DESC_RATEMCS14 = 0x1a,
	DESC_RATEMCS15 = 0x1b,
	DESC_RATEMCS15_SG = 0x1c,
	DESC_RATEMCS32 = 0x20,

	DESC_RATEVHT1SS_MCS0 = 0x2c,
	DESC_RATEVHT1SS_MCS1 = 0x2d,
	DESC_RATEVHT1SS_MCS2 = 0x2e,
	DESC_RATEVHT1SS_MCS3 = 0x2f,
	DESC_RATEVHT1SS_MCS4 = 0x30,
	DESC_RATEVHT1SS_MCS5 = 0x31,
	DESC_RATEVHT1SS_MCS6 = 0x32,
	DESC_RATEVHT1SS_MCS7 = 0x33,
	DESC_RATEVHT1SS_MCS8 = 0x34,
	DESC_RATEVHT1SS_MCS9 = 0x35,
	DESC_RATEVHT2SS_MCS0 = 0x36,
	DESC_RATEVHT2SS_MCS1 = 0x37,
	DESC_RATEVHT2SS_MCS2 = 0x38,
	DESC_RATEVHT2SS_MCS3 = 0x39,
	DESC_RATEVHT2SS_MCS4 = 0x3a,
	DESC_RATEVHT2SS_MCS5 = 0x3b,
	DESC_RATEVHT2SS_MCS6 = 0x3c,
	DESC_RATEVHT2SS_MCS7 = 0x3d,
	DESC_RATEVHT2SS_MCS8 = 0x3e,
	DESC_RATEVHT2SS_MCS9 = 0x3f,
पूर्ण;

क्रमागत rtl_var_map अणु
	/*reg map */
	SYS_ISO_CTRL = 0,
	SYS_FUNC_EN,
	SYS_CLK,
	MAC_RCR_AM,
	MAC_RCR_AB,
	MAC_RCR_ACRC32,
	MAC_RCR_ACF,
	MAC_RCR_AAP,
	MAC_HIMR,
	MAC_HIMRE,
	MAC_HSISR,

	/*efuse map */
	EFUSE_TEST,
	EFUSE_CTRL,
	EFUSE_CLK,
	EFUSE_CLK_CTRL,
	EFUSE_PWC_EV12V,
	EFUSE_FEN_ELDR,
	EFUSE_LOADER_CLK_EN,
	EFUSE_ANA8M,
	EFUSE_HWSET_MAX_SIZE,
	EFUSE_MAX_SECTION_MAP,
	EFUSE_REAL_CONTENT_SIZE,
	EFUSE_OOB_PROTECT_BYTES_LEN,
	EFUSE_ACCESS,

	/*CAM map */
	RWCAM,
	WCAMI,
	RCAMO,
	CAMDBG,
	SECR,
	SEC_CAM_NONE,
	SEC_CAM_WEP40,
	SEC_CAM_TKIP,
	SEC_CAM_AES,
	SEC_CAM_WEP104,

	/*IMR map */
	RTL_IMR_BCNDMAINT6,	/*Beacon DMA Interrupt 6 */
	RTL_IMR_BCNDMAINT5,	/*Beacon DMA Interrupt 5 */
	RTL_IMR_BCNDMAINT4,	/*Beacon DMA Interrupt 4 */
	RTL_IMR_BCNDMAINT3,	/*Beacon DMA Interrupt 3 */
	RTL_IMR_BCNDMAINT2,	/*Beacon DMA Interrupt 2 */
	RTL_IMR_BCNDMAINT1,	/*Beacon DMA Interrupt 1 */
	RTL_IMR_BCNDOK8,	/*Beacon Queue DMA OK Interrup 8 */
	RTL_IMR_BCNDOK7,	/*Beacon Queue DMA OK Interrup 7 */
	RTL_IMR_BCNDOK6,	/*Beacon Queue DMA OK Interrup 6 */
	RTL_IMR_BCNDOK5,	/*Beacon Queue DMA OK Interrup 5 */
	RTL_IMR_BCNDOK4,	/*Beacon Queue DMA OK Interrup 4 */
	RTL_IMR_BCNDOK3,	/*Beacon Queue DMA OK Interrup 3 */
	RTL_IMR_BCNDOK2,	/*Beacon Queue DMA OK Interrup 2 */
	RTL_IMR_BCNDOK1,	/*Beacon Queue DMA OK Interrup 1 */
	RTL_IMR_TIMEOUT2,	/*Timeout पूर्णांकerrupt 2 */
	RTL_IMR_TIMEOUT1,	/*Timeout पूर्णांकerrupt 1 */
	RTL_IMR_TXFOVW,		/*Transmit FIFO Overflow */
	RTL_IMR_PSTIMEOUT,	/*Power save समय out पूर्णांकerrupt */
	RTL_IMR_BCNINT,		/*Beacon DMA Interrupt 0 */
	RTL_IMR_RXFOVW,		/*Receive FIFO Overflow */
	RTL_IMR_RDU,		/*Receive Descriptor Unavailable */
	RTL_IMR_ATIMEND,	/*For 92C,ATIM Winकरोw End Interrupt */
	RTL_IMR_H2CDOK,		/*H2C Queue DMA OK Interrupt */
	RTL_IMR_BDOK,		/*Beacon Queue DMA OK Interrup */
	RTL_IMR_HIGHDOK,	/*High Queue DMA OK Interrupt */
	RTL_IMR_COMDOK,		/*Command Queue DMA OK Interrupt*/
	RTL_IMR_TBDOK,		/*Transmit Beacon OK पूर्णांकerrup */
	RTL_IMR_MGNTDOK,	/*Management Queue DMA OK Interrupt */
	RTL_IMR_TBDER,		/*For 92C,Transmit Beacon Error Interrupt */
	RTL_IMR_BKDOK,		/*AC_BK DMA OK Interrupt */
	RTL_IMR_BEDOK,		/*AC_BE DMA OK Interrupt */
	RTL_IMR_VIDOK,		/*AC_VI DMA OK Interrupt */
	RTL_IMR_VODOK,		/*AC_VO DMA Interrupt */
	RTL_IMR_ROK,		/*Receive DMA OK Interrupt */
	RTL_IMR_HSISR_IND,	/*HSISR Interrupt*/
	RTL_IBSS_INT_MASKS,	/*(RTL_IMR_BCNINT | RTL_IMR_TBDOK |
				 * RTL_IMR_TBDER)
				 */
	RTL_IMR_C2HCMD,		/*fw पूर्णांकerrupt*/

	/*CCK Rates, TxHT = 0 */
	RTL_RC_CCK_RATE1M,
	RTL_RC_CCK_RATE2M,
	RTL_RC_CCK_RATE5_5M,
	RTL_RC_CCK_RATE11M,

	/*OFDM Rates, TxHT = 0 */
	RTL_RC_OFDM_RATE6M,
	RTL_RC_OFDM_RATE9M,
	RTL_RC_OFDM_RATE12M,
	RTL_RC_OFDM_RATE18M,
	RTL_RC_OFDM_RATE24M,
	RTL_RC_OFDM_RATE36M,
	RTL_RC_OFDM_RATE48M,
	RTL_RC_OFDM_RATE54M,

	RTL_RC_HT_RATEMCS7,
	RTL_RC_HT_RATEMCS15,

	RTL_RC_VHT_RATE_1SS_MCS7,
	RTL_RC_VHT_RATE_1SS_MCS8,
	RTL_RC_VHT_RATE_1SS_MCS9,
	RTL_RC_VHT_RATE_2SS_MCS7,
	RTL_RC_VHT_RATE_2SS_MCS8,
	RTL_RC_VHT_RATE_2SS_MCS9,

	/*keep it last */
	RTL_VAR_MAP_MAX,
पूर्ण;

/*Firmware PS mode क्रम control LPS.*/
क्रमागत _fw_ps_mode अणु
	FW_PS_ACTIVE_MODE = 0,
	FW_PS_MIN_MODE = 1,
	FW_PS_MAX_MODE = 2,
	FW_PS_DTIM_MODE = 3,
	FW_PS_VOIP_MODE = 4,
	FW_PS_UAPSD_WMM_MODE = 5,
	FW_PS_UAPSD_MODE = 6,
	FW_PS_IBSS_MODE = 7,
	FW_PS_WWLAN_MODE = 8,
	FW_PS_PM_RADIO_OFF = 9,
	FW_PS_PM_CARD_DISABLE = 10,
पूर्ण;

क्रमागत rt_psmode अणु
	EACTIVE,		/*Active/Continuous access. */
	EMAXPS,			/*Max घातer save mode. */
	EFASTPS,		/*Fast घातer save mode. */
	EAUTOPS,		/*Auto घातer save mode. */
पूर्ण;

/*LED related.*/
क्रमागत led_ctl_mode अणु
	LED_CTL_POWER_ON = 1,
	LED_CTL_LINK = 2,
	LED_CTL_NO_LINK = 3,
	LED_CTL_TX = 4,
	LED_CTL_RX = 5,
	LED_CTL_SITE_SURVEY = 6,
	LED_CTL_POWER_OFF = 7,
	LED_CTL_START_TO_LINK = 8,
	LED_CTL_START_WPS = 9,
	LED_CTL_STOP_WPS = 10,
पूर्ण;

क्रमागत rtl_led_pin अणु
	LED_PIN_GPIO0,
	LED_PIN_LED0,
	LED_PIN_LED1,
	LED_PIN_LED2
पूर्ण;

/*QoS related.*/
/*acm implementation method.*/
क्रमागत acm_method अणु
	EACMWAY0_SWANDHW = 0,
	EACMWAY1_HW = 1,
	EACMWAY2_SW = 2,
पूर्ण;

क्रमागत macphy_mode अणु
	SINGLEMAC_SINGLEPHY = 0,
	DUALMAC_DUALPHY,
	DUALMAC_SINGLEPHY,
पूर्ण;

क्रमागत band_type अणु
	BAND_ON_2_4G = 0,
	BAND_ON_5G,
	BAND_ON_BOTH,
	BANDMAX
पूर्ण;

/* aci/aअगरsn Field.
 * Ref: WMM spec 2.2.2: WME Parameter Element, p.12.
 */
जोड़ aci_aअगरsn अणु
	u8 अक्षर_data;

	काष्ठा अणु
		u8 aअगरsn:4;
		u8 acm:1;
		u8 aci:2;
		u8 reserved:1;
	पूर्ण f;			/* Field */
पूर्ण;

/*mlme related.*/
क्रमागत wireless_mode अणु
	WIRELESS_MODE_UNKNOWN = 0x00,
	WIRELESS_MODE_A = 0x01,
	WIRELESS_MODE_B = 0x02,
	WIRELESS_MODE_G = 0x04,
	WIRELESS_MODE_AUTO = 0x08,
	WIRELESS_MODE_N_24G = 0x10,
	WIRELESS_MODE_N_5G = 0x20,
	WIRELESS_MODE_AC_5G = 0x40,
	WIRELESS_MODE_AC_24G  = 0x80,
	WIRELESS_MODE_AC_ONLY = 0x100,
	WIRELESS_MODE_MAX = 0x800
पूर्ण;

#घोषणा IS_WIRELESS_MODE_A(wirelessmode)	\
	(wirelessmode == WIRELESS_MODE_A)
#घोषणा IS_WIRELESS_MODE_B(wirelessmode)	\
	(wirelessmode == WIRELESS_MODE_B)
#घोषणा IS_WIRELESS_MODE_G(wirelessmode)	\
	(wirelessmode == WIRELESS_MODE_G)
#घोषणा IS_WIRELESS_MODE_N_24G(wirelessmode)	\
	(wirelessmode == WIRELESS_MODE_N_24G)
#घोषणा IS_WIRELESS_MODE_N_5G(wirelessmode)	\
	(wirelessmode == WIRELESS_MODE_N_5G)

क्रमागत ratr_table_mode अणु
	RATR_INX_WIRELESS_NGB = 0,
	RATR_INX_WIRELESS_NG = 1,
	RATR_INX_WIRELESS_NB = 2,
	RATR_INX_WIRELESS_N = 3,
	RATR_INX_WIRELESS_GB = 4,
	RATR_INX_WIRELESS_G = 5,
	RATR_INX_WIRELESS_B = 6,
	RATR_INX_WIRELESS_MC = 7,
	RATR_INX_WIRELESS_A = 8,
	RATR_INX_WIRELESS_AC_5N = 8,
	RATR_INX_WIRELESS_AC_24N = 9,
पूर्ण;

क्रमागत ratr_table_mode_new अणु
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
	RATEID_IDX_MIX1 = 11,
	RATEID_IDX_MIX2 = 12,
	RATEID_IDX_VHT_3SS = 13,
	RATEID_IDX_BGN_3SS = 14,
पूर्ण;

क्रमागत rtl_link_state अणु
	MAC80211_NOLINK = 0,
	MAC80211_LINKING = 1,
	MAC80211_LINKED = 2,
	MAC80211_LINKED_SCANNING = 3,
पूर्ण;

क्रमागत act_category अणु
	ACT_CAT_QOS = 1,
	ACT_CAT_DLS = 2,
	ACT_CAT_BA = 3,
	ACT_CAT_HT = 7,
	ACT_CAT_WMM = 17,
पूर्ण;

क्रमागत ba_action अणु
	ACT_ADDBAREQ = 0,
	ACT_ADDBARSP = 1,
	ACT_DELBA = 2,
पूर्ण;

क्रमागत rt_polarity_ctl अणु
	RT_POLARITY_LOW_ACT = 0,
	RT_POLARITY_HIGH_ACT = 1,
पूर्ण;

/* After 8188E, we use V2 reason define. 88C/8723A use V1 reason. */
क्रमागत fw_wow_reason_v2 अणु
	FW_WOW_V2_PTK_UPDATE_EVENT = 0x01,
	FW_WOW_V2_GTK_UPDATE_EVENT = 0x02,
	FW_WOW_V2_DISASSOC_EVENT = 0x04,
	FW_WOW_V2_DEAUTH_EVENT = 0x08,
	FW_WOW_V2_FW_DISCONNECT_EVENT = 0x10,
	FW_WOW_V2_MAGIC_PKT_EVENT = 0x21,
	FW_WOW_V2_UNICAST_PKT_EVENT = 0x22,
	FW_WOW_V2_PATTERN_PKT_EVENT = 0x23,
	FW_WOW_V2_RTD3_SSID_MATCH_EVENT = 0x24,
	FW_WOW_V2_REALWOW_V2_WAKEUPPKT = 0x30,
	FW_WOW_V2_REALWOW_V2_ACKLOST = 0x31,
	FW_WOW_V2_REASON_MAX = 0xff,
पूर्ण;

क्रमागत wolpattern_type अणु
	UNICAST_PATTERN = 0,
	MULTICAST_PATTERN = 1,
	BROADCAST_PATTERN = 2,
	DONT_CARE_DA = 3,
	UNKNOWN_TYPE = 4,
पूर्ण;

क्रमागत package_type अणु
	PACKAGE_DEFAULT,
	PACKAGE_QFN68,
	PACKAGE_TFBGA90,
	PACKAGE_TFBGA80,
	PACKAGE_TFBGA79
पूर्ण;

क्रमागत rtl_spec_ver अणु
	RTL_SPEC_NEW_RATEID = BIT(0),	/* use ratr_table_mode_new */
	RTL_SPEC_SUPPORT_VHT = BIT(1),	/* support VHT */
	RTL_SPEC_EXT_C2H = BIT(2),	/* extend FW C2H (e.g. TX REPORT) */
पूर्ण;

क्रमागत dm_info_query अणु
	DM_INFO_FA_OFDM,
	DM_INFO_FA_CCK,
	DM_INFO_FA_TOTAL,
	DM_INFO_CCA_OFDM,
	DM_INFO_CCA_CCK,
	DM_INFO_CCA_ALL,
	DM_INFO_CRC32_OK_VHT,
	DM_INFO_CRC32_OK_HT,
	DM_INFO_CRC32_OK_LEGACY,
	DM_INFO_CRC32_OK_CCK,
	DM_INFO_CRC32_ERROR_VHT,
	DM_INFO_CRC32_ERROR_HT,
	DM_INFO_CRC32_ERROR_LEGACY,
	DM_INFO_CRC32_ERROR_CCK,
	DM_INFO_EDCCA_FLAG,
	DM_INFO_OFDM_ENABLE,
	DM_INFO_CCK_ENABLE,
	DM_INFO_CRC32_OK_HT_AGG,
	DM_INFO_CRC32_ERROR_HT_AGG,
	DM_INFO_DBG_PORT_0,
	DM_INFO_CURR_IGI,
	DM_INFO_RSSI_MIN,
	DM_INFO_RSSI_MAX,
	DM_INFO_CLM_RATIO,
	DM_INFO_NHM_RATIO,
	DM_INFO_IQK_ALL,
	DM_INFO_IQK_OK,
	DM_INFO_IQK_NG,
	DM_INFO_SIZE,
पूर्ण;

क्रमागत rx_packet_type अणु
	NORMAL_RX,
	TX_REPORT1,
	TX_REPORT2,
	HIS_REPORT,
	C2H_PACKET,
पूर्ण;

काष्ठा rtlwअगरi_tx_info अणु
	पूर्णांक sn;
	अचिन्हित दीर्घ send_समय;
पूर्ण;

अटल अंतरभूत काष्ठा rtlwअगरi_tx_info *rtl_tx_skb_cb_info(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	BUILD_BUG_ON(माप(काष्ठा rtlwअगरi_tx_info) >
		     माप(info->status.status_driver_data));

	वापस (काष्ठा rtlwअगरi_tx_info *)(info->status.status_driver_data);
पूर्ण

काष्ठा octet_string अणु
	u8 *octet;
	u16 length;
पूर्ण;

काष्ठा rtl_hdr_3addr अणु
	__le16 frame_ctl;
	__le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	__le16 seq_ctl;
	u8 payload[];
पूर्ण __packed;

काष्ठा rtl_info_element अणु
	u8 id;
	u8 len;
	u8 data[];
पूर्ण __packed;

काष्ठा rtl_probe_rsp अणु
	काष्ठा rtl_hdr_3addr header;
	u32 समय_stamp[2];
	__le16 beacon_पूर्णांकerval;
	__le16 capability;
	/*SSID, supported rates, FH params, DS params,
	 * CF params, IBSS params, TIM (अगर beacon), RSN
	 */
	काष्ठा rtl_info_element info_element[];
पूर्ण __packed;

/*LED related.*/
/*ledpin Identअगरy how to implement this SW led.*/
काष्ठा rtl_led अणु
	व्योम *hw;
	क्रमागत rtl_led_pin ledpin;
	bool leकरोn;
पूर्ण;

काष्ठा rtl_led_ctl अणु
	bool led_खोलोdrain;
	काष्ठा rtl_led sw_led0;
	काष्ठा rtl_led sw_led1;
पूर्ण;

काष्ठा rtl_qos_parameters अणु
	__le16 cw_min;
	__le16 cw_max;
	u8 aअगरs;
	u8 flag;
	__le16 tx_op;
पूर्ण __packed;

काष्ठा rt_smooth_data अणु
	u32 elements[100];	/*array to store values */
	u32 index;		/*index to current array to store */
	u32 total_num;		/*num of valid elements */
	u32 total_val;		/*sum of valid elements */
पूर्ण;

काष्ठा false_alarm_statistics अणु
	u32 cnt_parity_fail;
	u32 cnt_rate_illegal;
	u32 cnt_crc8_fail;
	u32 cnt_mcs_fail;
	u32 cnt_fast_fsync_fail;
	u32 cnt_sb_search_fail;
	u32 cnt_ofdm_fail;
	u32 cnt_cck_fail;
	u32 cnt_all;
	u32 cnt_ofdm_cca;
	u32 cnt_cck_cca;
	u32 cnt_cca_all;
	u32 cnt_bw_usc;
	u32 cnt_bw_lsc;
पूर्ण;

काष्ठा init_gain अणु
	u8 xaagccore1;
	u8 xbagccore1;
	u8 xcagccore1;
	u8 xdagccore1;
	u8 cca;

पूर्ण;

काष्ठा wireless_stats अणु
	u64 txbytesunicast;
	u64 txbytesmulticast;
	u64 txbytesbroadcast;
	u64 rxbytesunicast;

	u64 txbytesunicast_inperiod;
	u64 rxbytesunicast_inperiod;
	u32 txbytesunicast_inperiod_tp;
	u32 rxbytesunicast_inperiod_tp;
	u64 txbytesunicast_last;
	u64 rxbytesunicast_last;

	दीर्घ rx_snr_db[4];
	/*Correct smoothed ss in Dbm, only used
	 * in driver to report real घातer now.
	 */
	दीर्घ recv_संकेत_घातer;
	दीर्घ संकेत_quality;
	दीर्घ last_sigstrength_inpercent;

	u32 rssi_calculate_cnt;
	u32 pwdb_all_cnt;

	/* Transक्रमmed, in dbm. Beautअगरied संकेत
	 * strength क्रम UI, not correct.
	 */
	दीर्घ संकेत_strength;

	u8 rx_rssi_percentage[4];
	u8 rx_evm_dbm[4];
	u8 rx_evm_percentage[2];

	u16 rx_cfo_लघु[4];
	u16 rx_cfo_tail[4];

	काष्ठा rt_smooth_data ui_rssi;
	काष्ठा rt_smooth_data ui_link_quality;
पूर्ण;

काष्ठा rate_adaptive अणु
	u8 rate_adaptive_disabled;
	u8 ratr_state;
	u16 reserve;

	u32 high_rssi_thresh_क्रम_ra;
	u32 high2low_rssi_thresh_क्रम_ra;
	u8 low2high_rssi_thresh_क्रम_ra40m;
	u32 low_rssi_thresh_क्रम_ra40m;
	u8 low2high_rssi_thresh_क्रम_ra20m;
	u32 low_rssi_thresh_क्रम_ra20m;
	u32 upper_rssi_threshold_ratr;
	u32 middleupper_rssi_threshold_ratr;
	u32 middle_rssi_threshold_ratr;
	u32 middlelow_rssi_threshold_ratr;
	u32 low_rssi_threshold_ratr;
	u32 ultralow_rssi_threshold_ratr;
	u32 low_rssi_threshold_ratr_40m;
	u32 low_rssi_threshold_ratr_20m;
	u8 ping_rssi_enable;
	u32 ping_rssi_ratr;
	u32 ping_rssi_thresh_क्रम_ra;
	u32 last_ratr;
	u8 pre_ratr_state;
	u8 ldpc_thres;
	bool use_ldpc;
	bool lower_rts_rate;
	bool is_special_data;
पूर्ण;

काष्ठा regd_pair_mapping अणु
	u16 reg_dmnक्रमागत;
	u16 reg_5ghz_ctl;
	u16 reg_2ghz_ctl;
पूर्ण;

काष्ठा dynamic_primary_cca अणु
	u8 pricca_flag;
	u8 पूर्णांकf_flag;
	u8 पूर्णांकf_type;
	u8 dup_rts_flag;
	u8 monitor_flag;
	u8 ch_offset;
	u8 mf_state;
पूर्ण;

काष्ठा rtl_regulatory अणु
	s8 alpha2[2];
	u16 country_code;
	u16 max_घातer_level;
	u32 tp_scale;
	u16 current_rd;
	u16 current_rd_ext;
	पूर्णांक16_t घातer_limit;
	काष्ठा regd_pair_mapping *regpair;
पूर्ण;

काष्ठा rtl_rfसमाप्त अणु
	bool rfसमाप्त_state;	/*0 is off, 1 is on */
पूर्ण;

/*क्रम P2P PS**/
#घोषणा	P2P_MAX_NOA_NUM		2

क्रमागत p2p_role अणु
	P2P_ROLE_DISABLE = 0,
	P2P_ROLE_DEVICE = 1,
	P2P_ROLE_CLIENT = 2,
	P2P_ROLE_GO = 3
पूर्ण;

क्रमागत p2p_ps_state अणु
	P2P_PS_DISABLE = 0,
	P2P_PS_ENABLE = 1,
	P2P_PS_SCAN = 2,
	P2P_PS_SCAN_DONE = 3,
	P2P_PS_ALLSTASLEEP = 4, /* क्रम P2P GO */
पूर्ण;

क्रमागत p2p_ps_mode अणु
	P2P_PS_NONE = 0,
	P2P_PS_CTWINDOW = 1,
	P2P_PS_NOA	 = 2,
	P2P_PS_MIX = 3, /* CTWinकरोw and NoA */
पूर्ण;

काष्ठा rtl_p2p_ps_info अणु
	क्रमागत p2p_ps_mode p2p_ps_mode; /* indicate p2p ps mode */
	क्रमागत p2p_ps_state p2p_ps_state; /*  indicate p2p ps state */
	u8 noa_index; /*  Identअगरies instance of Notice of Absence timing. */
	/*  Client traffic winकरोw. A period of समय in TU after TBTT. */
	u8 ctwinकरोw;
	u8 opp_ps; /*  opportunistic घातer save. */
	u8 noa_num; /*  number of NoA descriptor in P2P IE. */
	/*  Count क्रम owner, Type of client. */
	u8 noa_count_type[P2P_MAX_NOA_NUM];
	/*  Max duration क्रम owner, preferred or min acceptable duration
	 * क्रम client.
	 */
	u32 noa_duration[P2P_MAX_NOA_NUM];
	/*  Length of पूर्णांकerval क्रम owner, preferred or max acceptable पूर्णांकervali
	 * of client.
	 */
	u32 noa_पूर्णांकerval[P2P_MAX_NOA_NUM];
	/*  schedule in terms of the lower 4 bytes of the TSF समयr. */
	u32 noa_start_समय[P2P_MAX_NOA_NUM];
पूर्ण;

काष्ठा p2p_ps_offload_t अणु
	u8 offload_en:1;
	u8 role:1; /* 1: Owner, 0: Client */
	u8 ctwinकरोw_en:1;
	u8 noa0_en:1;
	u8 noa1_en:1;
	u8 allstasleep:1;
	u8 discovery:1;
	u8 reserved:1;
पूर्ण;

#घोषणा IQK_MATRIX_REG_NUM	8
#घोषणा IQK_MATRIX_SETTINGS_NUM	(1 + 24 + 21)

काष्ठा iqk_matrix_regs अणु
	bool iqk_करोne;
	दीर्घ value[1][IQK_MATRIX_REG_NUM];
पूर्ण;

काष्ठा phy_parameters अणु
	u16 length;
	u32 *pdata;
पूर्ण;

क्रमागत hw_param_tab_index अणु
	PHY_REG_2T,
	PHY_REG_1T,
	PHY_REG_PG,
	RADIOA_2T,
	RADIOB_2T,
	RADIOA_1T,
	RADIOB_1T,
	MAC_REG,
	AGCTAB_2T,
	AGCTAB_1T,
	MAX_TAB
पूर्ण;

काष्ठा rtl_phy अणु
	काष्ठा bb_reg_def phyreg_def[4];	/*Radio A/B/C/D */
	काष्ठा init_gain initgain_backup;
	क्रमागत io_type current_io_type;

	u8 rf_mode;
	u8 rf_type;
	u8 current_chan_bw;
	u8 set_bwmode_inprogress;
	u8 sw_chnl_inprogress;
	u8 sw_chnl_stage;
	u8 sw_chnl_step;
	u8 current_channel;
	u8 h2c_box_num;
	u8 set_io_inprogress;
	u8 lck_inprogress;

	/* record क्रम घातer tracking */
	s32 reg_e94;
	s32 reg_e9c;
	s32 reg_ea4;
	s32 reg_eac;
	s32 reg_eb4;
	s32 reg_ebc;
	s32 reg_ec4;
	s32 reg_ecc;
	u8 rfpienable;
	u8 reserve_0;
	u16 reserve_1;
	u32 reg_c04, reg_c08, reg_874;
	u32 adda_backup[16];
	u32 iqk_mac_backup[IQK_MAC_REG_NUM];
	u32 iqk_bb_backup[10];
	bool iqk_initialized;

	bool rfpath_rx_enable[MAX_RF_PATH];
	u8 reg_837;
	/* Dual mac */
	bool need_iqk;
	काष्ठा iqk_matrix_regs iqk_matrix[IQK_MATRIX_SETTINGS_NUM];

	bool rfpi_enable;
	bool iqk_in_progress;

	u8 pwrgroup_cnt;
	u8 cck_high_घातer;
	/* this is क्रम 88E & 8723A */
	u32 mcs_txpwrlevel_origoffset[MAX_PG_GROUP][16];
	/* MAX_PG_GROUP groups of pwr dअगरf by rates */
	u32 mcs_offset[MAX_PG_GROUP][16];
	u32 tx_घातer_by_rate_offset[TX_PWR_BY_RATE_NUM_BAND]
				   [TX_PWR_BY_RATE_NUM_RF]
				   [TX_PWR_BY_RATE_NUM_RF]
				   [TX_PWR_BY_RATE_NUM_RATE];
	u8 txpwr_by_rate_base_24g[TX_PWR_BY_RATE_NUM_RF]
				 [TX_PWR_BY_RATE_NUM_RF]
				 [MAX_BASE_NUM_IN_PHY_REG_PG_24G];
	u8 txpwr_by_rate_base_5g[TX_PWR_BY_RATE_NUM_RF]
				[TX_PWR_BY_RATE_NUM_RF]
				[MAX_BASE_NUM_IN_PHY_REG_PG_5G];
	u8 शेष_initialgain[4];

	/* the current Tx घातer level */
	u8 cur_cck_txpwridx;
	u8 cur_ofdm24g_txpwridx;
	u8 cur_bw20_txpwridx;
	u8 cur_bw40_txpwridx;

	s8 txpwr_limit_2_4g[MAX_REGULATION_NUM]
			   [MAX_2_4G_BANDWIDTH_NUM]
			   [MAX_RATE_SECTION_NUM]
			   [CHANNEL_MAX_NUMBER_2G]
			   [MAX_RF_PATH_NUM];
	s8 txpwr_limit_5g[MAX_REGULATION_NUM]
			 [MAX_5G_BANDWIDTH_NUM]
			 [MAX_RATE_SECTION_NUM]
			 [CHANNEL_MAX_NUMBER_5G]
			 [MAX_RF_PATH_NUM];

	u32 rfreg_chnlval[2];
	bool apk_करोne;
	u32 reg_rf3c[2];	/* pathA / pathB  */

	u32 backup_rf_0x1a;/*92ee*/
	/* bfsync */
	u8 framesync;
	u32 framesync_c34;

	u8 num_total_rfpath;
	काष्ठा phy_parameters hwparam_tables[MAX_TAB];
	u16 rf_pathmap;

	u8 hw_rof_enable; /*Enable GPIO[9] as WL RF HW PDn source*/
	क्रमागत rt_polarity_ctl polarity_ctl;
पूर्ण;

#घोषणा MAX_TID_COUNT				9
#घोषणा RTL_AGG_STOP				0
#घोषणा RTL_AGG_PROGRESS			1
#घोषणा RTL_AGG_START				2
#घोषणा RTL_AGG_OPERATIONAL			3
#घोषणा RTL_AGG_OFF				0
#घोषणा RTL_AGG_ON				1
#घोषणा RTL_RX_AGG_START			1
#घोषणा RTL_RX_AGG_STOP				0
#घोषणा RTL_AGG_EMPTYING_HW_QUEUE_ADDBA		2
#घोषणा RTL_AGG_EMPTYING_HW_QUEUE_DELBA		3

काष्ठा rtl_ht_agg अणु
	u16 txq_id;
	u16 रुको_क्रम_ba;
	u16 start_idx;
	u64 biपंचांगap;
	u32 rate_n_flags;
	u8 agg_state;
	u8 rx_agg_state;
पूर्ण;

काष्ठा rssi_sta अणु
	दीर्घ undec_sm_pwdb;
	दीर्घ undec_sm_cck;
पूर्ण;

काष्ठा rtl_tid_data अणु
	काष्ठा rtl_ht_agg agg;
पूर्ण;

काष्ठा rtl_sta_info अणु
	काष्ठा list_head list;
	काष्ठा rtl_tid_data tids[MAX_TID_COUNT];
	/* just used क्रम ap adhoc or mesh*/
	काष्ठा rssi_sta rssi_stat;
	u8 rssi_level;
	u16 wireless_mode;
	u8 ratr_index;
	u8 mimo_ps;
	u8 mac_addr[ETH_ALEN];
पूर्ण __packed;

काष्ठा rtl_priv;
काष्ठा rtl_io अणु
	काष्ठा device *dev;
	काष्ठा mutex bb_mutex;

	/*PCI MEM map */
	अचिन्हित दीर्घ pci_mem_end;	/*shared mem end        */
	अचिन्हित दीर्घ pci_mem_start;	/*shared mem start */

	/*PCI IO map */
	अचिन्हित दीर्घ pci_base_addr;	/*device I/O address */

	व्योम (*ग_लिखो8_async)(काष्ठा rtl_priv *rtlpriv, u32 addr, u8 val);
	व्योम (*ग_लिखो16_async)(काष्ठा rtl_priv *rtlpriv, u32 addr, u16 val);
	व्योम (*ग_लिखो32_async)(काष्ठा rtl_priv *rtlpriv, u32 addr, u32 val);
	व्योम (*ग_लिखोn_sync)(काष्ठा rtl_priv *rtlpriv, u32 addr, व्योम *buf,
			    u16 len);

	u8 (*पढ़ो8_sync)(काष्ठा rtl_priv *rtlpriv, u32 addr);
	u16 (*पढ़ो16_sync)(काष्ठा rtl_priv *rtlpriv, u32 addr);
	u32 (*पढ़ो32_sync)(काष्ठा rtl_priv *rtlpriv, u32 addr);

पूर्ण;

काष्ठा rtl_mac अणु
	u8 mac_addr[ETH_ALEN];
	u8 mac80211_रेजिस्टरed;
	u8 beacon_enabled;

	u32 tx_ss_num;
	u32 rx_ss_num;

	काष्ठा ieee80211_supported_band bands[NUM_NL80211_BANDS];
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_vअगर *vअगर;
	क्रमागत nl80211_अगरtype opmode;

	/*Probe Beacon management */
	काष्ठा rtl_tid_data tids[MAX_TID_COUNT];
	क्रमागत rtl_link_state link_state;

	पूर्णांक n_channels;
	पूर्णांक n_bitrates;

	bool offchan_delay;
	u8 p2p;	/*using p2p role*/
	bool p2p_in_use;

	/*filters */
	u32 rx_conf;
	u16 rx_mgt_filter;
	u16 rx_ctrl_filter;
	u16 rx_data_filter;

	bool act_scanning;
	u8 cnt_after_linked;
	bool skip_scan;

	/* early mode */
	/* skb रुको queue */
	काष्ठा sk_buff_head skb_रुकोq[MAX_TID_COUNT];

	u8 ht_stbc_cap;
	u8 ht_cur_stbc;

	/*vht support*/
	u8 vht_enable;
	u8 bw_80;
	u8 vht_cur_ldpc;
	u8 vht_cur_stbc;
	u8 vht_stbc_cap;
	u8 vht_ldpc_cap;

	/*RDG*/
	bool rdg_en;

	/*AP*/
	u8 bssid[ETH_ALEN] __aligned(2);
	u32 venकरोr;
	u8 mcs[16];	/* 16 bytes mcs क्रम HT rates. */
	u32 basic_rates; /* b/g rates */
	u8 ht_enable;
	u8 sgi_40;
	u8 sgi_20;
	u8 bw_40;
	u16 mode;		/* wireless mode */
	u8 slot_समय;
	u8 लघु_preamble;
	u8 use_cts_protect;
	u8 cur_40_prime_sc;
	u8 cur_40_prime_sc_bk;
	u8 cur_80_prime_sc;
	u64 tsf;
	u8 retry_लघु;
	u8 retry_दीर्घ;
	u16 assoc_id;
	bool hiddenssid;

	/*IBSS*/
	पूर्णांक beacon_पूर्णांकerval;

	/*AMPDU*/
	u8 min_space_cfg;	/*For Min spacing configurations */
	u8 max_mss_density;
	u8 current_ampdu_factor;
	u8 current_ampdu_density;

	/*QOS & EDCA */
	काष्ठा ieee80211_tx_queue_params edca_param[RTL_MAC80211_NUM_QUEUE];
	काष्ठा rtl_qos_parameters ac[AC_MAX];

	/* counters */
	u64 last_txok_cnt;
	u64 last_rxok_cnt;
	u32 last_bt_edca_ul;
	u32 last_bt_edca_dl;
पूर्ण;

काष्ठा btdm_8723 अणु
	bool all_off;
	bool agc_table_en;
	bool adc_back_off_on;
	bool b2_ant_hid_en;
	bool low_penalty_rate_adaptive;
	bool rf_rx_lpf_shrink;
	bool reject_aggre_pkt;
	bool tra_tdma_on;
	u8 tra_tdma_nav;
	u8 tra_tdma_ant;
	bool tdma_on;
	u8 tdma_ant;
	u8 tdma_nav;
	u8 tdma_dac_swing;
	u8 fw_dac_swing_lvl;
	bool ps_tdma_on;
	u8 ps_tdma_byte[5];
	bool pta_on;
	u32 val_0x6c0;
	u32 val_0x6c8;
	u32 val_0x6cc;
	bool sw_dac_swing_on;
	u32 sw_dac_swing_lvl;
	u32 wlan_act_hi;
	u32 wlan_act_lo;
	u32 bt_retry_index;
	bool dec_bt_pwr;
	bool ignore_wlan_act;
पूर्ण;

काष्ठा bt_coexist_8723 अणु
	u32 high_priority_tx;
	u32 high_priority_rx;
	u32 low_priority_tx;
	u32 low_priority_rx;
	u8 c2h_bt_info;
	bool c2h_bt_info_req_sent;
	bool c2h_bt_inquiry_page;
	u32 bt_inq_page_start_समय;
	u8 bt_retry_cnt;
	u8 c2h_bt_info_original;
	u8 bt_inquiry_page_cnt;
	काष्ठा btdm_8723 btdm;
पूर्ण;

काष्ठा rtl_hal अणु
	काष्ठा ieee80211_hw *hw;
	bool driver_is_goingto_unload;
	bool up_first_समय;
	bool first_init;
	bool being_init_adapter;
	bool bbrf_पढ़ोy;
	bool mac_func_enable;
	bool pre_edcca_enable;
	काष्ठा bt_coexist_8723 hal_coex_8723;

	क्रमागत पूर्णांकf_type पूर्णांकerface;
	u16 hw_type;		/*92c or 92d or 92s and so on */
	u8 ic_class;
	u8 oem_id;
	u32 version;		/*version of chip */
	u8 state;		/*stop 0, start 1 */
	u8 board_type;
	u8 package_type;
	u8 बाह्यal_pa;

	u8 pa_mode;
	u8 pa_type_2g;
	u8 pa_type_5g;
	u8 lna_type_2g;
	u8 lna_type_5g;
	u8 बाह्यal_pa_2g;
	u8 बाह्यal_lna_2g;
	u8 बाह्यal_pa_5g;
	u8 बाह्यal_lna_5g;
	u8 type_glna;
	u8 type_gpa;
	u8 type_alna;
	u8 type_apa;
	u8 rfe_type;

	/*firmware */
	u32 fwsize;
	u8 *pfirmware;
	u16 fw_version;
	u16 fw_subversion;
	bool h2c_setinprogress;
	u8 last_hmeboxnum;
	bool fw_पढ़ोy;
	/*Reserve page start offset except beacon in TxQ. */
	u8 fw_rsvdpage_startoffset;
	u8 h2c_txcmd_seq;
	u8 current_ra_rate;

	/* FW Cmd IO related */
	u16 fwcmd_iomap;
	u32 fwcmd_ioparam;
	bool set_fwcmd_inprogress;
	u8 current_fwcmd_io;

	काष्ठा p2p_ps_offload_t p2p_ps_offload;
	bool fw_clk_change_in_progress;
	bool allow_sw_to_change_hwclc;
	u8 fw_ps_state;
	/**/
	bool driver_going2unload;

	/*AMPDU init min space*/
	u8 minspace_cfg;	/*For Min spacing configurations */

	/* Dual mac */
	क्रमागत macphy_mode macphymode;
	क्रमागत band_type current_bandtype;	/* 0:2.4G, 1:5G */
	क्रमागत band_type current_bandtypebackup;
	क्रमागत band_type bandset;
	/* dual MAC 0--Mac0 1--Mac1 */
	u32 पूर्णांकerfaceindex;
	/* just क्रम DualMac S3S4 */
	u8 macphyctl_reg;
	bool earlymode_enable;
	u8 max_earlymode_num;
	/* Dual mac*/
	bool during_mac0init_radiob;
	bool during_mac1init_radioa;
	bool reloadtxघातerindex;
	/* True अगर IMR or IQK  have करोne
	 * क्रम 2.4G in scan progress
	 */
	bool load_imअक्रमiqk_setting_क्रम2g;

	bool disable_amsdu_8k;
	bool master_of_dmsp;
	bool slave_of_dmsp;

	u16 rx_tag;/*क्रम 92ee*/
	u8 rts_en;

	/*क्रम wowlan*/
	bool wow_enable;
	bool enter_pnp_sleep;
	bool wake_from_pnp_sleep;
	bool wow_enabled;
	समय64_t last_suspend_sec;
	u32 wowlan_fwsize;
	u8 *wowlan_firmware;

	u8 hw_rof_enable; /*Enable GPIO[9] as WL RF HW PDn source*/

	bool real_wow_v2_enable;
	bool re_init_llt_table;
पूर्ण;

काष्ठा rtl_security अणु
	/*शेष 0 */
	bool use_sw_sec;

	bool being_setkey;
	bool use_शेषkey;
	/*Encryption Algorithm क्रम Unicast Packet */
	क्रमागत rt_enc_alg pairwise_enc_algorithm;
	/*Encryption Algorithm क्रम Brocast/Multicast */
	क्रमागत rt_enc_alg group_enc_algorithm;
	/*Cam Entry Biपंचांगap */
	u32 hwsec_cam_biपंचांगap;
	u8 hwsec_cam_sta_addr[TOTAL_CAM_ENTRY][ETH_ALEN];
	/*local Key buffer, indx 0 is क्रम
	 * pairwise key 1-4 is क्रम agoup key.
	 */
	u8 key_buf[KEY_BUF_SIZE][MAX_KEY_LEN];
	u8 key_len[KEY_BUF_SIZE];

	/*The poपूर्णांकer of Pairwise Key,
	 * it always poपूर्णांकs to KeyBuf[4]
	 */
	u8 *pairwise_key;
पूर्ण;

#घोषणा ASSOCIATE_ENTRY_NUM	33

काष्ठा fast_ant_training अणु
	u8	bssid[6];
	u8	antsel_rx_keep_0;
	u8	antsel_rx_keep_1;
	u8	antsel_rx_keep_2;
	u32	ant_sum[7];
	u32	ant_cnt[7];
	u32	ant_ave[7];
	u8	fat_state;
	u32	train_idx;
	u8	antsel_a[ASSOCIATE_ENTRY_NUM];
	u8	antsel_b[ASSOCIATE_ENTRY_NUM];
	u8	antsel_c[ASSOCIATE_ENTRY_NUM];
	u32	मुख्य_ant_sum[ASSOCIATE_ENTRY_NUM];
	u32	aux_ant_sum[ASSOCIATE_ENTRY_NUM];
	u32	मुख्य_ant_cnt[ASSOCIATE_ENTRY_NUM];
	u32	aux_ant_cnt[ASSOCIATE_ENTRY_NUM];
	u8	rx_idle_ant;
	bool	becomelinked;
पूर्ण;

काष्ठा dm_phy_dbg_info अणु
	s8 rx_snrdb[4];
	u64 num_qry_phy_status;
	u64 num_qry_phy_status_cck;
	u64 num_qry_phy_status_ofdm;
	u16 num_qry_beacon_pkt;
	u16 num_non_be_pkt;
	s32 rx_evm[4];
पूर्ण;

काष्ठा rtl_dm अणु
	/*PHY status क्रम Dynamic Management */
	दीर्घ entry_min_undec_sm_pwdb;
	दीर्घ undec_sm_cck;
	दीर्घ undec_sm_pwdb;	/*out dm */
	दीर्घ entry_max_undec_sm_pwdb;
	s32 ofdm_pkt_cnt;
	bool dm_initialgain_enable;
	bool dynamic_txघातer_enable;
	bool current_turbo_edca;
	bool is_any_nonbepkts;	/*out dm */
	bool is_cur_rdlstate;
	bool txघातer_trackinginit;
	bool disable_framebursting;
	bool cck_inch14;
	bool txघातer_tracking;
	bool useramask;
	bool rfpath_rxenable[4];
	bool inक्रमm_fw_driverctrldm;
	bool current_mrc_चयन;
	u8 txघातercount;
	u8 घातerindex_backup[6];

	u8 thermalvalue_rxgain;
	u8 thermalvalue_iqk;
	u8 thermalvalue_lck;
	u8 thermalvalue;
	u8 last_dtp_lvl;
	u8 thermalvalue_avg[AVG_THERMAL_NUM];
	u8 thermalvalue_avg_index;
	u8 पंचांग_trigger;
	bool करोne_txघातer;
	u8 dynamic_txhighघातer_lvl;	/*Tx high घातer level */
	u8 dm_flag;		/*Indicate each dynamic mechanism's status. */
	u8 dm_flag_पंचांगp;
	u8 dm_type;
	u8 dm_rssi_sel;
	u8 txघातer_track_control;
	bool पूर्णांकerrupt_migration;
	bool disable_tx_पूर्णांक;
	s8 ofdm_index[MAX_RF_PATH];
	u8 शेष_ofdm_index;
	u8 शेष_cck_index;
	s8 cck_index;
	s8 delta_घातer_index[MAX_RF_PATH];
	s8 delta_घातer_index_last[MAX_RF_PATH];
	s8 घातer_index_offset[MAX_RF_PATH];
	s8 असलolute_ofdm_swing_idx[MAX_RF_PATH];
	s8 remnant_ofdm_swing_idx[MAX_RF_PATH];
	s8 remnant_cck_idx;
	bool modअगरy_txagc_flag_path_a;
	bool modअगरy_txagc_flag_path_b;

	bool one_entry_only;
	काष्ठा dm_phy_dbg_info dbginfo;

	/* Dynamic ATC चयन */
	bool atc_status;
	bool large_cfo_hit;
	bool is_मुक्तze;
	पूर्णांक cfo_tail[2];
	पूर्णांक cfo_ave_pre;
	पूर्णांक crystal_cap;
	u8 cfo_threshold;
	u32 packet_count;
	u32 packet_count_pre;
	u8 tx_rate;

	/*88e tx घातer tracking*/
	u8	swing_idx_ofdm[MAX_RF_PATH];
	u8	swing_idx_ofdm_cur;
	u8	swing_idx_ofdm_base[MAX_RF_PATH];
	bool	swing_flag_ofdm;
	u8	swing_idx_cck;
	u8	swing_idx_cck_cur;
	u8	swing_idx_cck_base;
	bool	swing_flag_cck;

	s8	swing_dअगरf_2g;
	s8	swing_dअगरf_5g;

	/* DMSP */
	bool supp_phymode_चयन;

	/* DulMac */
	काष्ठा fast_ant_training fat_table;

	u8	resp_tx_path;
	u8	path_sel;
	u32	patha_sum;
	u32	pathb_sum;
	u32	patha_cnt;
	u32	pathb_cnt;

	u8 pre_channel;
	u8 *p_channel;
	u8 linked_पूर्णांकerval;

	u64 last_tx_ok_cnt;
	u64 last_rx_ok_cnt;
पूर्ण;

#घोषणा	EFUSE_MAX_LOGICAL_SIZE			512

काष्ठा rtl_efuse अणु
	स्थिर काष्ठा rtl_efuse_ops *efuse_ops;
	bool स्वतःload_ok;
	bool bootfromefuse;
	u16 max_physical_size;

	u8 efuse_map[2][EFUSE_MAX_LOGICAL_SIZE];
	u16 efuse_usedbytes;
	u8 efuse_usedpercentage;

	u8 स्वतःload_failflag;
	u8 स्वतःload_status;

	लघु epromtype;
	u16 eeprom_vid;
	u16 eeprom_did;
	u16 eeprom_svid;
	u16 eeprom_smid;
	u8 eeprom_oemid;
	u16 eeprom_channelplan;
	u8 eeprom_version;
	u8 board_type;
	u8 बाह्यal_pa;

	u8 dev_addr[6];
	u8 wowlan_enable;
	u8 antenna_भाग_cfg;
	u8 antenna_भाग_प्रकारype;

	bool txpwr_fromeprom;
	u8 eeprom_crystalcap;
	u8 eeprom_tssi[2];
	u8 eeprom_tssi_5g[3][2]; /* क्रम 5GL/5GM/5GH band. */
	u8 eeprom_pwrlimit_ht20[CHANNEL_GROUP_MAX];
	u8 eeprom_pwrlimit_ht40[CHANNEL_GROUP_MAX];
	u8 eeprom_chnlarea_txpwr_cck[MAX_RF_PATH][CHANNEL_GROUP_MAX_2G];
	u8 eeprom_chnlarea_txpwr_ht40_1s[MAX_RF_PATH][CHANNEL_GROUP_MAX];
	u8 eprom_chnl_txpwr_ht40_2sdf[MAX_RF_PATH][CHANNEL_GROUP_MAX];

	u8 पूर्णांकernal_pa_5g[2];	/* pathA / pathB */
	u8 eeprom_c9;
	u8 eeprom_cc;

	/*For घातer group */
	u8 eeprom_pwrgroup[2][3];
	u8 pwrgroup_ht20[2][CHANNEL_MAX_NUMBER];
	u8 pwrgroup_ht40[2][CHANNEL_MAX_NUMBER];

	u8 txpwrlevel_cck[MAX_RF_PATH][CHANNEL_MAX_NUMBER_2G];
	/*For HT 40MHZ pwr */
	u8 txpwrlevel_ht40_1s[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
	/*For HT 40MHZ pwr */
	u8 txpwrlevel_ht40_2s[MAX_RF_PATH][CHANNEL_MAX_NUMBER];

	/*--------------------------------------------------------*
	 * 8192CE\8192SE\8192DE\8723AE use the following 4 arrays,
	 * other ICs (8188EE\8723BE\8192EE\8812AE...)
	 * define new arrays in Winकरोws code.
	 * BUT, in linux code, we use the same array क्रम all ICs.
	 *
	 * The Correspondance relation between two arrays is:
	 * txpwr_cckdअगरf[][] == CCK_24G_Dअगरf[][]
	 * txpwr_ht20dअगरf[][] == BW20_24G_Dअगरf[][]
	 * txpwr_ht40dअगरf[][] == BW40_24G_Dअगरf[][]
	 * txpwr_legacyhtdअगरf[][] == OFDM_24G_Dअगरf[][]
	 *
	 * Sizes of these arrays are decided by the larger ones.
	 */
	s8 txpwr_cckdअगरf[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
	s8 txpwr_ht20dअगरf[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
	s8 txpwr_ht40dअगरf[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
	s8 txpwr_legacyhtdअगरf[MAX_RF_PATH][CHANNEL_MAX_NUMBER];

	u8 txpwr_5g_bw40base[MAX_RF_PATH][CHANNEL_MAX_NUMBER];
	u8 txpwr_5g_bw80base[MAX_RF_PATH][CHANNEL_MAX_NUMBER_5G_80M];
	s8 txpwr_5g_ofdmdअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 txpwr_5g_bw20dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 txpwr_5g_bw40dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 txpwr_5g_bw80dअगरf[MAX_RF_PATH][MAX_TX_COUNT];

	u8 txpwr_safetyflag;			/* Band edge enable flag */
	u16 eeprom_txघातerdअगरf;
	u8 antenna_txpwdअगरf[3];

	u8 eeprom_regulatory;
	u8 eeprom_thermalmeter;
	u8 thermalmeter[2]; /*ThermalMeter, index 0 क्रम RFIC0, 1 क्रम RFIC1 */
	u16 tssi_13dbm;
	u8 crystalcap;		/* CrystalCap. */
	u8 delta_iqk;
	u8 delta_lck;

	u8 legacy_ht_txघातerdअगरf;	/*Legacy to HT rate घातer dअगरf */
	bool apk_thermalmeterignore;

	bool b1x1_recvcombine;
	bool b1ss_support;

	/*channel plan */
	u8 channel_plan;
पूर्ण;

काष्ठा rtl_efuse_ops अणु
	पूर्णांक (*efuse_onebyte_पढ़ो)(काष्ठा ieee80211_hw *hw, u16 addr, u8 *data);
	व्योम (*efuse_logical_map_पढ़ो)(काष्ठा ieee80211_hw *hw, u8 type,
				       u16 offset, u32 *value);
पूर्ण;

काष्ठा rtl_tx_report अणु
	atomic_t sn;
	u16 last_sent_sn;
	अचिन्हित दीर्घ last_sent_समय;
	u16 last_recv_sn;
	काष्ठा sk_buff_head queue;
पूर्ण;

काष्ठा rtl_ps_ctl अणु
	bool pwrकरोमुख्य_protect;
	bool in_घातersavemode;
	bool rfchange_inprogress;
	bool swrf_processing;
	bool hwradiooff;
	/* just क्रम PCIE ASPM
	 * If it supports ASPM, Offset[560h] = 0x40,
	 * otherwise Offset[560h] = 0x00.
	 */
	bool support_aspm;
	bool support_backकरोor;

	/*क्रम LPS */
	क्रमागत rt_psmode करोt11_psmode;	/*Power save mode configured. */
	bool swctrl_lps;
	bool leisure_ps;
	bool fwctrl_lps;
	u8 fwctrl_psmode;
	/*For Fw control LPS mode */
	u8 reg_fwctrl_lps;
	/*Record Fw PS mode status. */
	bool fw_current_inpsmode;
	u8 reg_max_lps_awakeपूर्णांकvl;
	bool report_linked;
	bool low_घातer_enable;/*क्रम 32k*/

	/*क्रम IPS */
	bool inactiveps;

	u32 rfoff_reason;

	/*RF OFF Level */
	u32 cur_ps_level;
	u32 reg_rfps_level;

	/*just क्रम PCIE ASPM */
	u8 स्थिर_amdpci_aspm;
	bool pwrकरोwn_mode;

	क्रमागत rf_pwrstate inactive_pwrstate;
	क्रमागत rf_pwrstate rfpwr_state;	/*cur घातer state */

	/* क्रम SW LPS*/
	bool sw_ps_enabled;
	bool state;
	bool state_inap;
	bool multi_buffered;
	u16 nullfunc_seq;
	अचिन्हित पूर्णांक dtim_counter;
	अचिन्हित पूर्णांक sleep_ms;
	अचिन्हित दीर्घ last_sleep_jअगरfies;
	अचिन्हित दीर्घ last_awake_jअगरfies;
	अचिन्हित दीर्घ last_delaylps_stamp_jअगरfies;
	अचिन्हित दीर्घ last_dtim;
	अचिन्हित दीर्घ last_beacon;
	अचिन्हित दीर्घ last_action;
	अचिन्हित दीर्घ last_slept;

	/*For P2P PS */
	काष्ठा rtl_p2p_ps_info p2p_ps_info;
	u8 pwr_mode;
	u8 smart_ps;

	/* wake up on line */
	u8 wo_wlan_mode;
	u8 arp_offload_enable;
	u8 gtk_offload_enable;
	/* Used क्रम WOL, indicates the reason क्रम waking event.*/
	u32 wakeup_reason;
पूर्ण;

काष्ठा rtl_stats अणु
	u8 psaddr[ETH_ALEN];
	u32 mac_समय[2];
	s8 rssi;
	u8 संकेत;
	u8 noise;
	u8 rate;		/* hw desc rate */
	u8 received_channel;
	u8 control;
	u8 mask;
	u8 freq;
	u16 len;
	u64 tsf;
	u32 beacon_समय;
	u8 nic_type;
	u16 length;
	u8 संकेतquality;	/*in 0-100 index. */
	/* Real घातer in dBm क्रम this packet,
	 * no beautअगरication and aggregation.
	 */
	s32 recvसंकेतघातer;
	s8 rxघातer;		/*in dBm Translate from PWdB */
	u8 संकेतstrength;	/*in 0-100 index. */
	u16 hwerror:1;
	u16 crc:1;
	u16 icv:1;
	u16 लघुpreamble:1;
	u16 antenna:1;
	u16 decrypted:1;
	u16 wakeup:1;
	u32 बारtamp_low;
	u32 बारtamp_high;
	bool shअगरt;

	u8 rx_drvinfo_size;
	u8 rx_bufshअगरt;
	bool isampdu;
	bool isfirst_ampdu;
	bool rx_is40mhzpacket;
	u8 rx_packet_bw;
	u32 rx_pwdb_all;
	u8 rx_mimo_संकेतstrength[4];	/*in 0~100 index */
	s8 rx_mimo_संकेतquality[4];
	u8 rx_mimo_evm_dbm[4];
	u16 cfo_लघु[4];		/* per-path's Cfo_लघु */
	u16 cfo_tail[4];

	s8 rx_mimo_sig_qual[4];
	u8 rx_pwr[4]; /* per-path's pwdb */
	u8 rx_snr[4]; /* per-path's SNR */
	u8 bandwidth;
	u8 bt_coex_pwr_adjust;
	bool packet_matchbssid;
	bool is_cck;
	bool is_ht;
	bool packet_toself;
	bool packet_beacon;	/*क्रम rssi */
	s8 cck_adc_pwdb[4];	/*क्रम rx path selection */

	bool is_vht;
	bool is_लघु_gi;
	u8 vht_nss;

	u8 packet_report_type;

	u32 macid;
	u32 bt_rx_rssi_percentage;
	u32 macid_valid_entry[2];
पूर्ण;

काष्ठा rt_link_detect अणु
	/* count क्रम roaming */
	u32 bcn_rx_inperiod;
	u32 roam_बार;

	u32 num_tx_in4period[4];
	u32 num_rx_in4period[4];

	u32 num_tx_inperiod;
	u32 num_rx_inperiod;

	bool busytraffic;
	bool tx_busy_traffic;
	bool rx_busy_traffic;
	bool higher_busytraffic;
	bool higher_busyrxtraffic;

	u32 tidtx_in4period[MAX_TID_COUNT][4];
	u32 tidtx_inperiod[MAX_TID_COUNT];
	bool higher_busytxtraffic[MAX_TID_COUNT];
पूर्ण;

काष्ठा rtl_tcb_desc अणु
	u8 packet_bw:2;
	u8 multicast:1;
	u8 broadcast:1;

	u8 rts_stbc:1;
	u8 rts_enable:1;
	u8 cts_enable:1;
	u8 rts_use_लघुpreamble:1;
	u8 rts_use_लघुgi:1;
	u8 rts_sc:1;
	u8 rts_bw:1;
	u8 rts_rate;

	u8 use_लघुgi:1;
	u8 use_लघुpreamble:1;
	u8 use_driver_rate:1;
	u8 disable_ratefallback:1;

	u8 use_spe_rpt:1;

	u8 ratr_index;
	u8 mac_id;
	u8 hw_rate;

	u8 last_inipkt:1;
	u8 cmd_or_init:1;
	u8 queue_index;

	/* early mode */
	u8 empkt_num;
	/* The max value by HW */
	u32 empkt_len[10];
	bool tx_enable_sw_calc_duration;
पूर्ण;

काष्ठा rtl_wow_pattern अणु
	u8 type;
	u16 crc;
	u32 mask[4];
पूर्ण;

/* काष्ठा to store contents of पूर्णांकerrupt vectors */
काष्ठा rtl_पूर्णांक अणु
	u32 पूर्णांकa;
	u32 पूर्णांकb;
	u32 पूर्णांकc;
	u32 पूर्णांकd;
पूर्ण;

काष्ठा rtl_hal_ops अणु
	पूर्णांक (*init_sw_vars)(काष्ठा ieee80211_hw *hw);
	व्योम (*deinit_sw_vars)(काष्ठा ieee80211_hw *hw);
	व्योम (*पढ़ो_chip_version)(काष्ठा ieee80211_hw *hw);
	व्योम (*पढ़ो_eeprom_info)(काष्ठा ieee80211_hw *hw);
	व्योम (*पूर्णांकerrupt_recognized)(काष्ठा ieee80211_hw *hw,
				     काष्ठा rtl_पूर्णांक *पूर्णांकvec);
	पूर्णांक (*hw_init)(काष्ठा ieee80211_hw *hw);
	व्योम (*hw_disable)(काष्ठा ieee80211_hw *hw);
	व्योम (*hw_suspend)(काष्ठा ieee80211_hw *hw);
	व्योम (*hw_resume)(काष्ठा ieee80211_hw *hw);
	व्योम (*enable_पूर्णांकerrupt)(काष्ठा ieee80211_hw *hw);
	व्योम (*disable_पूर्णांकerrupt)(काष्ठा ieee80211_hw *hw);
	पूर्णांक (*set_network_type)(काष्ठा ieee80211_hw *hw,
				क्रमागत nl80211_अगरtype type);
	व्योम (*set_chk_bssid)(काष्ठा ieee80211_hw *hw,
			      bool check_bssid);
	व्योम (*set_bw_mode)(काष्ठा ieee80211_hw *hw,
			    क्रमागत nl80211_channel_type ch_type);
	 u8 (*चयन_channel)(काष्ठा ieee80211_hw *hw);
	व्योम (*set_qos)(काष्ठा ieee80211_hw *hw, पूर्णांक aci);
	व्योम (*set_bcn_reg)(काष्ठा ieee80211_hw *hw);
	व्योम (*set_bcn_पूर्णांकv)(काष्ठा ieee80211_hw *hw);
	व्योम (*update_पूर्णांकerrupt_mask)(काष्ठा ieee80211_hw *hw,
				      u32 add_msr, u32 rm_msr);
	व्योम (*get_hw_reg)(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
	व्योम (*set_hw_reg)(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
	व्योम (*update_rate_tbl)(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_sta *sta, u8 rssi_leve,
				bool update_bw);
	व्योम (*pre_fill_tx_bd_desc)(काष्ठा ieee80211_hw *hw, u8 *tx_bd_desc,
				    u8 *desc, u8 queue_index,
				    काष्ठा sk_buff *skb, dma_addr_t addr);
	व्योम (*update_rate_mask)(काष्ठा ieee80211_hw *hw, u8 rssi_level);
	u16 (*rx_desc_buff_reमुख्यed_cnt)(काष्ठा ieee80211_hw *hw,
					 u8 queue_index);
	व्योम (*rx_check_dma_ok)(काष्ठा ieee80211_hw *hw, u8 *header_desc,
				u8 queue_index);
	व्योम (*fill_tx_desc)(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_hdr *hdr, u8 *pdesc_tx,
			     u8 *pbd_desc_tx,
			     काष्ठा ieee80211_tx_info *info,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा sk_buff *skb, u8 hw_queue,
			     काष्ठा rtl_tcb_desc *ptcb_desc);
	व्योम (*fill_fake_txdesc)(काष्ठा ieee80211_hw *hw, u8 *pdesc,
				 u32 buffer_len, bool bsspspoll);
	व्योम (*fill_tx_cmddesc)(काष्ठा ieee80211_hw *hw, u8 *pdesc,
				bool firstseg, bool lastseg,
				काष्ठा sk_buff *skb);
	व्योम (*fill_tx_special_desc)(काष्ठा ieee80211_hw *hw,
				     u8 *pdesc, u8 *pbd_desc,
				     काष्ठा sk_buff *skb, u8 hw_queue);
	bool (*query_rx_desc)(काष्ठा ieee80211_hw *hw,
			      काष्ठा rtl_stats *stats,
			      काष्ठा ieee80211_rx_status *rx_status,
			      u8 *pdesc, काष्ठा sk_buff *skb);
	व्योम (*set_channel_access)(काष्ठा ieee80211_hw *hw);
	bool (*radio_onoff_checking)(काष्ठा ieee80211_hw *hw, u8 *valid);
	व्योम (*dm_watchकरोg)(काष्ठा ieee80211_hw *hw);
	व्योम (*scan_operation_backup)(काष्ठा ieee80211_hw *hw, u8 operation);
	bool (*set_rf_घातer_state)(काष्ठा ieee80211_hw *hw,
				   क्रमागत rf_pwrstate rfpwr_state);
	व्योम (*led_control)(काष्ठा ieee80211_hw *hw,
			    क्रमागत led_ctl_mode ledaction);
	व्योम (*set_desc)(काष्ठा ieee80211_hw *hw, u8 *pdesc, bool istx,
			 u8 desc_name, u8 *val);
	u64 (*get_desc)(काष्ठा ieee80211_hw *hw, u8 *pdesc, bool istx,
			u8 desc_name);
	bool (*is_tx_desc_बंदd)(काष्ठा ieee80211_hw *hw,
				  u8 hw_queue, u16 index);
	व्योम (*tx_polling)(काष्ठा ieee80211_hw *hw, u8 hw_queue);
	व्योम (*enable_hw_sec)(काष्ठा ieee80211_hw *hw);
	व्योम (*set_key)(काष्ठा ieee80211_hw *hw, u32 key_index,
			u8 *macaddr, bool is_group, u8 enc_algo,
			bool is_wepkey, bool clear_all);
	व्योम (*init_sw_leds)(काष्ठा ieee80211_hw *hw);
	व्योम (*deinit_sw_leds)(काष्ठा ieee80211_hw *hw);
	u32 (*get_bbreg)(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask);
	व्योम (*set_bbreg)(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask,
			  u32 data);
	u32 (*get_rfreg)(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			 u32 regaddr, u32 biपंचांगask);
	व्योम (*set_rfreg)(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			  u32 regaddr, u32 biपंचांगask, u32 data);
	व्योम (*linked_set_reg)(काष्ठा ieee80211_hw *hw);
	व्योम (*chk_चयन_dmdp)(काष्ठा ieee80211_hw *hw);
	व्योम (*dualmac_easy_concurrent)(काष्ठा ieee80211_hw *hw);
	व्योम (*dualmac_चयन_to_dmdp)(काष्ठा ieee80211_hw *hw);
	bool (*phy_rf6052_config)(काष्ठा ieee80211_hw *hw);
	व्योम (*phy_rf6052_set_cck_txघातer)(काष्ठा ieee80211_hw *hw,
					   u8 *घातerlevel);
	व्योम (*phy_rf6052_set_ofdm_txघातer)(काष्ठा ieee80211_hw *hw,
					    u8 *pघातerlevel, u8 channel);
	bool (*config_bb_with_headerfile)(काष्ठा ieee80211_hw *hw,
					  u8 configtype);
	bool (*config_bb_with_pgheaderfile)(काष्ठा ieee80211_hw *hw,
					    u8 configtype);
	व्योम (*phy_lc_calibrate)(काष्ठा ieee80211_hw *hw, bool is2t);
	व्योम (*phy_set_bw_mode_callback)(काष्ठा ieee80211_hw *hw);
	व्योम (*dm_dynamic_txघातer)(काष्ठा ieee80211_hw *hw);
	व्योम (*c2h_command_handle)(काष्ठा ieee80211_hw *hw);
	व्योम (*bt_wअगरi_media_status_notअगरy)(काष्ठा ieee80211_hw *hw,
					    bool mstate);
	व्योम (*bt_coex_off_beक्रमe_lps)(काष्ठा ieee80211_hw *hw);
	व्योम (*fill_h2c_cmd)(काष्ठा ieee80211_hw *hw, u8 element_id,
			     u32 cmd_len, u8 *p_cmdbuffer);
	व्योम (*set_शेष_port_id_cmd)(काष्ठा ieee80211_hw *hw);
	bool (*get_btc_status)(व्योम);
	bool (*is_fw_header)(काष्ठा rtlwअगरi_firmware_header *hdr);
	व्योम (*add_wowlan_pattern)(काष्ठा ieee80211_hw *hw,
				   काष्ठा rtl_wow_pattern *rtl_pattern,
				   u8 index);
	u16 (*get_available_desc)(काष्ठा ieee80211_hw *hw, u8 q_idx);
	व्योम (*c2h_ra_report_handler)(काष्ठा ieee80211_hw *hw,
				      u8 *cmd_buf, u8 cmd_len);
पूर्ण;

काष्ठा rtl_पूर्णांकf_ops अणु
	/*com */
	व्योम (*पढ़ो_efuse_byte)(काष्ठा ieee80211_hw *hw, u16 _offset, u8 *pbuf);
	पूर्णांक (*adapter_start)(काष्ठा ieee80211_hw *hw);
	व्योम (*adapter_stop)(काष्ठा ieee80211_hw *hw);
	bool (*check_buddy_priv)(काष्ठा ieee80211_hw *hw,
				 काष्ठा rtl_priv **buddy_priv);

	पूर्णांक (*adapter_tx)(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff *skb,
			  काष्ठा rtl_tcb_desc *ptcb_desc);
	व्योम (*flush)(काष्ठा ieee80211_hw *hw, u32 queues, bool drop);
	पूर्णांक (*reset_trx_ring)(काष्ठा ieee80211_hw *hw);
	bool (*रुकोq_insert)(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा sk_buff *skb);

	/*pci */
	व्योम (*disable_aspm)(काष्ठा ieee80211_hw *hw);
	व्योम (*enable_aspm)(काष्ठा ieee80211_hw *hw);

	/*usb */
पूर्ण;

काष्ठा rtl_mod_params अणु
	/* शेष: 0,0 */
	u64 debug_mask;
	/* शेष: 0 = using hardware encryption */
	bool sw_crypto;

	/* शेष: 0 = DBG_EMERG (0)*/
	पूर्णांक debug_level;

	/* शेष: 1 = using no linked घातer save */
	bool inactiveps;

	/* शेष: 1 = using linked sw घातer save */
	bool swctrl_lps;

	/* शेष: 1 = using linked fw घातer save */
	bool fwctrl_lps;

	/* शेष: 0 = not using MSI पूर्णांकerrupts mode
	 * submodules should set their own शेष value
	 */
	bool msi_support;

	/* शेष: 0 = dma 32 */
	bool dma64;

	/* शेष: 1 = enable aspm */
	पूर्णांक aspm_support;

	/* शेष 0: 1 means disable */
	bool disable_watchकरोg;

	/* शेष 0: 1 means करो not disable पूर्णांकerrupts */
	bool पूर्णांक_clear;

	/* select antenna */
	पूर्णांक ant_sel;
पूर्ण;

काष्ठा rtl_hal_usbपूर्णांक_cfg अणु
	/* data - rx */
	u32 in_ep_num;
	u32 rx_urb_num;
	u32 rx_max_size;

	/* op - rx */
	व्योम (*usb_rx_hdl)(काष्ठा ieee80211_hw *, काष्ठा sk_buff *);
	व्योम (*usb_rx_segregate_hdl)(काष्ठा ieee80211_hw *, काष्ठा sk_buff *,
				     काष्ठा sk_buff_head *);

	/* tx */
	व्योम (*usb_tx_cleanup)(काष्ठा ieee80211_hw *, काष्ठा sk_buff *);
	पूर्णांक (*usb_tx_post_hdl)(काष्ठा ieee80211_hw *, काष्ठा urb *,
			       काष्ठा sk_buff *);
	काष्ठा sk_buff *(*usb_tx_aggregate_hdl)(काष्ठा ieee80211_hw *,
						काष्ठा sk_buff_head *);

	/* endpoपूर्णांक mapping */
	पूर्णांक (*usb_endpoपूर्णांक_mapping)(काष्ठा ieee80211_hw *hw);
	u16 (*usb_mq_to_hwq)(__le16 fc, u16 mac80211_queue_index);
पूर्ण;

काष्ठा rtl_hal_cfg अणु
	u8 bar_id;
	bool ग_लिखो_पढ़ोback;
	अक्षर *name;
	अक्षर *alt_fw_name;
	काष्ठा rtl_hal_ops *ops;
	काष्ठा rtl_mod_params *mod_params;
	काष्ठा rtl_hal_usbपूर्णांक_cfg *usb_पूर्णांकerface_cfg;
	क्रमागत rtl_spec_ver spec_ver;

	/*this map used क्रम some रेजिस्टरs or vars
	 * defined पूर्णांक HAL but used in MAIN
	 */
	u32 maps[RTL_VAR_MAP_MAX];

पूर्ण;

काष्ठा rtl_locks अणु
	/* mutex */
	काष्ठा mutex conf_mutex;
	काष्ठा mutex ips_mutex;	/* mutex क्रम enter/leave IPS */
	काष्ठा mutex lps_mutex;	/* mutex क्रम enter/leave LPS */

	/*spin lock */
	spinlock_t irq_th_lock;
	spinlock_t h2c_lock;
	spinlock_t rf_ps_lock;
	spinlock_t rf_lock;
	spinlock_t रुकोq_lock;
	spinlock_t entry_list_lock;
	spinlock_t usb_lock;
	spinlock_t scan_list_lock; /* lock क्रम the scan list */

	/*FW घड़ी change */
	spinlock_t fw_ps_lock;

	/*Dual mac*/
	spinlock_t cck_and_rw_pagea_lock;

	spinlock_t iqk_lock;
पूर्ण;

काष्ठा rtl_works अणु
	काष्ठा ieee80211_hw *hw;

	/*समयr */
	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा समयr_list dualmac_easyconcurrent_retryसमयr;
	काष्ठा समयr_list fw_घड़ीoff_समयr;
	काष्ठा समयr_list fast_antenna_training_समयr;
	/*task */
	काष्ठा tasklet_काष्ठा irq_tasklet;
	काष्ठा tasklet_काष्ठा irq_prepare_bcn_tasklet;

	/*work queue */
	काष्ठा workqueue_काष्ठा *rtl_wq;
	काष्ठा delayed_work watchकरोg_wq;
	काष्ठा delayed_work ips_nic_off_wq;
	काष्ठा delayed_work c2hcmd_wq;

	/* For SW LPS */
	काष्ठा delayed_work ps_work;
	काष्ठा delayed_work ps_rfon_wq;
	काष्ठा delayed_work fwevt_wq;

	काष्ठा work_काष्ठा lps_change_work;
	काष्ठा work_काष्ठा fill_h2c_cmd;
	काष्ठा work_काष्ठा update_beacon_work;
पूर्ण;

काष्ठा rtl_debug अणु
	/* add क्रम debug */
	काष्ठा dentry *debugfs_dir;
	अक्षर debugfs_name[20];
पूर्ण;

#घोषणा MIMO_PS_STATIC			0
#घोषणा MIMO_PS_DYNAMIC			1
#घोषणा MIMO_PS_NOLIMIT			3

काष्ठा rtl_dualmac_easy_concurrent_ctl अणु
	क्रमागत band_type currentbandtype_backक्रमdmdp;
	bool बंद_bbandrf_क्रम_dmsp;
	bool change_to_dmdp;
	bool change_to_dmsp;
	bool चयन_in_process;
पूर्ण;

काष्ठा rtl_dmsp_ctl अणु
	bool activescan_क्रम_slaveofdmsp;
	bool scan_क्रम_anothermac_क्रमdmsp;
	bool scan_क्रम_itself_क्रमdmsp;
	bool ग_लिखोdig_क्रम_anothermacofdmsp;
	u32 curdigvalue_क्रम_anothermacofdmsp;
	bool changecckpdstate_क्रम_anothermacofdmsp;
	u8 curcckpdstate_क्रम_anothermacofdmsp;
	bool changetxhighघातerlvl_क्रम_anothermacofdmsp;
	u8 curtxhighlvl_क्रम_anothermacofdmsp;
	दीर्घ rssivalmin_क्रम_anothermacofdmsp;
पूर्ण;

काष्ठा ps_t अणु
	u8 pre_ccastate;
	u8 cur_ccasate;
	u8 pre_rख_स्थितिe;
	u8 cur_rख_स्थितिe;
	u8 initialize;
	दीर्घ rssi_val_min;
पूर्ण;

काष्ठा dig_t अणु
	u32 rssi_lowthresh;
	u32 rssi_highthresh;
	u32 fa_lowthresh;
	u32 fa_highthresh;
	दीर्घ last_min_undec_pwdb_क्रम_dm;
	दीर्घ rssi_highघातer_lowthresh;
	दीर्घ rssi_highघातer_highthresh;
	u32 recover_cnt;
	u32 pre_igvalue;
	u32 cur_igvalue;
	दीर्घ rssi_val;
	u8 dig_enable_flag;
	u8 dig_ext_port_stage;
	u8 dig_algorithm;
	u8 dig_twoport_algorithm;
	u8 dig_dbgmode;
	u8 dig_slgorithm_चयन;
	u8 cursta_cstate;
	u8 presta_cstate;
	u8 curmultista_cstate;
	u8 stop_dig;
	s8 back_val;
	s8 back_range_max;
	s8 back_range_min;
	u8 rx_gain_max;
	u8 rx_gain_min;
	u8 min_undec_pwdb_क्रम_dm;
	u8 rssi_val_min;
	u8 pre_cck_cca_thres;
	u8 cur_cck_cca_thres;
	u8 pre_cck_pd_state;
	u8 cur_cck_pd_state;
	u8 pre_cck_fa_state;
	u8 cur_cck_fa_state;
	u8 pre_ccastate;
	u8 cur_ccasate;
	u8 large_fa_hit;
	u8 क्रमbidden_igi;
	u8 dig_state;
	u8 dig_highpwrstate;
	u8 cur_sta_cstate;
	u8 pre_sta_cstate;
	u8 cur_ap_cstate;
	u8 pre_ap_cstate;
	u8 cur_pd_thstate;
	u8 pre_pd_thstate;
	u8 cur_cs_ratiostate;
	u8 pre_cs_ratiostate;
	u8 backoff_enable_flag;
	s8 backoffval_range_max;
	s8 backoffval_range_min;
	u8 dig_min_0;
	u8 dig_min_1;
	u8 bt30_cur_igi;
	bool media_connect_0;
	bool media_connect_1;

	u32 antभाग_rssi_max;
	u32 rssi_max;
पूर्ण;

काष्ठा rtl_global_var अणु
	/* from this list we can get
	 * other adapter's rtl_priv
	 */
	काष्ठा list_head glb_priv_list;
	spinlock_t glb_list_lock;
पूर्ण;

#घोषणा IN_4WAY_TIMEOUT_TIME	(30 * MSEC_PER_SEC)	/* 30 seconds */

काष्ठा rtl_btc_info अणु
	u8 bt_type;
	u8 btcoexist;
	u8 ant_num;
	u8 single_ant_path;

	u8 ap_num;
	bool in_4way;
	अचिन्हित दीर्घ in_4way_ts;
पूर्ण;

काष्ठा bt_coexist_info अणु
	काष्ठा rtl_btc_ops *btc_ops;
	काष्ठा rtl_btc_info btc_info;
	/* btc context */
	व्योम *btc_context;
	व्योम *wअगरi_only_context;
	/* EEPROM BT info. */
	u8 eeprom_bt_coexist;
	u8 eeprom_bt_type;
	u8 eeprom_bt_ant_num;
	u8 eeprom_bt_ant_isol;
	u8 eeprom_bt_radio_shared;

	u8 bt_coexistence;
	u8 bt_ant_num;
	u8 bt_coexist_type;
	u8 bt_state;
	u8 bt_cur_state;	/* 0:on, 1:off */
	u8 bt_ant_isolation;	/* 0:good, 1:bad */
	u8 bt_pape_ctrl;	/* 0:SW, 1:SW/HW dynamic */
	u8 bt_service;
	u8 bt_radio_shared_type;
	u8 bt_rfreg_origin_1e;
	u8 bt_rfreg_origin_1f;
	u8 bt_rssi_state;
	u32 ratio_tx;
	u32 ratio_pri;
	u32 bt_edca_ul;
	u32 bt_edca_dl;

	bool init_set;
	bool bt_busy_traffic;
	bool bt_traffic_mode_set;
	bool bt_non_traffic_mode_set;

	bool fw_coexist_all_off;
	bool sw_coexist_all_off;
	bool hw_coexist_all_off;
	u32 cstate;
	u32 previous_state;
	u32 cstate_h;
	u32 previous_state_h;

	u8 bt_pre_rssi_state;
	u8 bt_pre_rssi_state1;

	u8 reg_bt_iso;
	u8 reg_bt_sco;
	bool balance_on;
	u8 bt_active_zero_cnt;
	bool cur_bt_disabled;
	bool pre_bt_disabled;

	u8 bt_profile_हाल;
	u8 bt_profile_action;
	bool bt_busy;
	bool hold_क्रम_bt_operation;
	u8 lps_counter;
पूर्ण;

काष्ठा rtl_btc_ops अणु
	व्योम (*btc_init_variables)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_init_variables_wअगरi_only)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_deinit_variables)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_init_hal_vars)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_घातer_on_setting)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_init_hw_config)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_init_hw_config_wअगरi_only)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_ips_notअगरy)(काष्ठा rtl_priv *rtlpriv, u8 type);
	व्योम (*btc_lps_notअगरy)(काष्ठा rtl_priv *rtlpriv, u8 type);
	व्योम (*btc_scan_notअगरy)(काष्ठा rtl_priv *rtlpriv, u8 scantype);
	व्योम (*btc_scan_notअगरy_wअगरi_only)(काष्ठा rtl_priv *rtlpriv,
					  u8 scantype);
	व्योम (*btc_connect_notअगरy)(काष्ठा rtl_priv *rtlpriv, u8 action);
	व्योम (*btc_mediastatus_notअगरy)(काष्ठा rtl_priv *rtlpriv,
				       क्रमागत rt_media_status mstatus);
	व्योम (*btc_periodical)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_halt_notअगरy)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_btinfo_notअगरy)(काष्ठा rtl_priv *rtlpriv,
				  u8 *पंचांगp_buf, u8 length);
	व्योम (*btc_bपंचांगpinfo_notअगरy)(काष्ठा rtl_priv *rtlpriv,
				    u8 *पंचांगp_buf, u8 length);
	bool (*btc_is_limited_dig)(काष्ठा rtl_priv *rtlpriv);
	bool (*btc_is_disable_edca_turbo)(काष्ठा rtl_priv *rtlpriv);
	bool (*btc_is_bt_disabled)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_special_packet_notअगरy)(काष्ठा rtl_priv *rtlpriv,
					  u8 pkt_type);
	व्योम (*btc_चयन_band_notअगरy)(काष्ठा rtl_priv *rtlpriv, u8 type,
				       bool scanning);
	व्योम (*btc_चयन_band_notअगरy_wअगरi_only)(काष्ठा rtl_priv *rtlpriv,
						 u8 type, bool scanning);
	व्योम (*btc_display_bt_coex_info)(काष्ठा rtl_priv *rtlpriv,
					 काष्ठा seq_file *m);
	व्योम (*btc_record_pwr_mode)(काष्ठा rtl_priv *rtlpriv, u8 *buf, u8 len);
	u8   (*btc_get_lps_val)(काष्ठा rtl_priv *rtlpriv);
	u8   (*btc_get_rpwm_val)(काष्ठा rtl_priv *rtlpriv);
	bool (*btc_is_bt_ctrl_lps)(काष्ठा rtl_priv *rtlpriv);
	व्योम (*btc_get_ampdu_cfg)(काष्ठा rtl_priv *rtlpriv, u8 *reject_agg,
				  u8 *ctrl_agg_size, u8 *agg_size);
	bool (*btc_is_bt_lps_on)(काष्ठा rtl_priv *rtlpriv);
पूर्ण;

काष्ठा proxim अणु
	bool proxim_on;

	व्योम *proximity_priv;
	पूर्णांक (*proxim_rx)(काष्ठा ieee80211_hw *hw, काष्ठा rtl_stats *status,
			 काष्ठा sk_buff *skb);
	u8  (*proxim_get_var)(काष्ठा ieee80211_hw *hw, u8 type);
पूर्ण;

काष्ठा rtl_c2hcmd अणु
	काष्ठा list_head list;
	u8 tag;
	u8 len;
	u8 *val;
पूर्ण;

काष्ठा rtl_bssid_entry अणु
	काष्ठा list_head list;
	u8 bssid[ETH_ALEN];
	u32 age;
पूर्ण;

काष्ठा rtl_scan_list अणु
	पूर्णांक num;
	काष्ठा list_head list;	/* sort by age */
पूर्ण;

काष्ठा rtl_priv अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा completion firmware_loading_complete;
	काष्ठा list_head list;
	काष्ठा rtl_priv *buddy_priv;
	काष्ठा rtl_global_var *glb_var;
	काष्ठा rtl_dualmac_easy_concurrent_ctl easy_concurrent_ctl;
	काष्ठा rtl_dmsp_ctl dmsp_ctl;
	काष्ठा rtl_locks locks;
	काष्ठा rtl_works works;
	काष्ठा rtl_mac mac80211;
	काष्ठा rtl_hal rtlhal;
	काष्ठा rtl_regulatory regd;
	काष्ठा rtl_rfसमाप्त rfसमाप्त;
	काष्ठा rtl_io io;
	काष्ठा rtl_phy phy;
	काष्ठा rtl_dm dm;
	काष्ठा rtl_security sec;
	काष्ठा rtl_efuse efuse;
	काष्ठा rtl_led_ctl ledctl;
	काष्ठा rtl_tx_report tx_report;
	काष्ठा rtl_scan_list scan_list;

	काष्ठा rtl_ps_ctl psc;
	काष्ठा rate_adaptive ra;
	काष्ठा dynamic_primary_cca primarycca;
	काष्ठा wireless_stats stats;
	काष्ठा rt_link_detect link_info;
	काष्ठा false_alarm_statistics falsealm_cnt;

	काष्ठा rtl_rate_priv *rate_priv;

	/* sta entry list क्रम ap adhoc or mesh */
	काष्ठा list_head entry_list;

	/* c2hcmd list क्रम kthपढ़ो level access */
	काष्ठा sk_buff_head c2hcmd_queue;

	काष्ठा rtl_debug dbg;
	पूर्णांक max_fw_size;

	/* hal_cfg : क्रम dअगरf cards
	 * पूर्णांकf_ops : क्रम dअगरf पूर्णांकerrface usb/pcie
	 */
	काष्ठा rtl_hal_cfg *cfg;
	स्थिर काष्ठा rtl_पूर्णांकf_ops *पूर्णांकf_ops;

	/* this var will be set by set_bit,
	 * and was used to indicate status of
	 * पूर्णांकerface or hardware
	 */
	अचिन्हित दीर्घ status;

	/* tables क्रम dm */
	काष्ठा dig_t dm_digtable;
	काष्ठा ps_t dm_pstable;

	u32 reg_874;
	u32 reg_c70;
	u32 reg_85c;
	u32 reg_a74;
	bool reg_init;	/* true अगर regs saved */
	bool bt_operation_on;
	__le32 *usb_data;
	पूर्णांक usb_data_index;
	bool initialized;
	bool enter_ps;	/* true when entering PS */
	u8 rate_mask[5];

	/* पूर्णांकel Proximity, should be alloc mem
	 * in पूर्णांकel Proximity module and can only
	 * be used in पूर्णांकel Proximity mode
	 */
	काष्ठा proxim proximity;

	/*क्रम bt coexist use*/
	काष्ठा bt_coexist_info btcoexist;

	/* separate 92ee from other ICs,
	 * 92ee use new trx flow.
	 */
	bool use_new_trx_flow;

#अगर_घोषित CONFIG_PM
	काष्ठा wiphy_wowlan_support wowlan;
#पूर्ण_अगर
	/* This must be the last item so
	 * that it poपूर्णांकs to the data allocated
	 * beyond  this काष्ठाure like:
	 * rtl_pci_priv or rtl_usb_priv
	 */
	u8 priv[0] __aligned(माप(व्योम *));
पूर्ण;

#घोषणा rtl_priv(hw)		(((काष्ठा rtl_priv *)(hw)->priv))
#घोषणा rtl_mac(rtlpriv)	(&((rtlpriv)->mac80211))
#घोषणा rtl_hal(rtlpriv)	(&((rtlpriv)->rtlhal))
#घोषणा rtl_efuse(rtlpriv)	(&((rtlpriv)->efuse))
#घोषणा rtl_psc(rtlpriv)	(&((rtlpriv)->psc))

/* Bluetooth Co-existence Related */

क्रमागत bt_ant_num अणु
	ANT_X2 = 0,
	ANT_X1 = 1,
पूर्ण;

क्रमागत bt_ant_path अणु
	ANT_MAIN = 0,
	ANT_AUX = 1,
पूर्ण;

क्रमागत bt_co_type अणु
	BT_2WIRE = 0,
	BT_ISSC_3WIRE = 1,
	BT_ACCEL = 2,
	BT_CSR_BC4 = 3,
	BT_CSR_BC8 = 4,
	BT_RTL8756 = 5,
	BT_RTL8723A = 6,
	BT_RTL8821A = 7,
	BT_RTL8723B = 8,
	BT_RTL8192E = 9,
	BT_RTL8812A = 11,
पूर्ण;

क्रमागत bt_cur_state अणु
	BT_OFF = 0,
	BT_ON = 1,
पूर्ण;

क्रमागत bt_service_type अणु
	BT_SCO = 0,
	BT_A2DP = 1,
	BT_HID = 2,
	BT_HID_IDLE = 3,
	BT_SCAN = 4,
	BT_IDLE = 5,
	BT_OTHER_ACTION = 6,
	BT_BUSY = 7,
	BT_OTHERBUSY = 8,
	BT_PAN = 9,
पूर्ण;

क्रमागत bt_radio_shared अणु
	BT_RADIO_SHARED = 0,
	BT_RADIO_INDIVIDUAL = 1,
पूर्ण;

/****************************************
 *	mem access macro define start
 *	Call endian मुक्त function when
 *	1. Read/ग_लिखो packet content.
 *	2. Beक्रमe ग_लिखो पूर्णांकeger to IO.
 *	3. After पढ़ो पूर्णांकeger from IO.
 ****************************************/

#घोषणा	N_BYTE_ALIGMENT(__value, __aligment) ((__aligment == 1) ? \
	(__value) : (((__value + __aligment - 1) / __aligment) * __aligment))

/* mem access macro define end */

#घोषणा byte(x, n) ((x >> (8 * n)) & 0xff)

#घोषणा packet_get_type(_packet) (EF1BYTE((_packet).octet[0]) & 0xFC)
#घोषणा RTL_WATCH_DOG_TIME	2000
#घोषणा MSECS(t)		msecs_to_jअगरfies(t)
#घोषणा WLAN_FC_GET_VERS(fc)	(le16_to_cpu(fc) & IEEE80211_FCTL_VERS)
#घोषणा WLAN_FC_GET_TYPE(fc)	(le16_to_cpu(fc) & IEEE80211_FCTL_FTYPE)
#घोषणा WLAN_FC_GET_STYPE(fc)	(le16_to_cpu(fc) & IEEE80211_FCTL_STYPE)
#घोषणा WLAN_FC_MORE_DATA(fc)	(le16_to_cpu(fc) & IEEE80211_FCTL_MOREDATA)
#घोषणा rtl_dm(rtlpriv)		(&((rtlpriv)->dm))

#घोषणा	RT_RF_OFF_LEVL_ASPM		BIT(0)	/*PCI ASPM */
#घोषणा	RT_RF_OFF_LEVL_CLK_REQ		BIT(1)	/*PCI घड़ी request */
#घोषणा	RT_RF_OFF_LEVL_PCI_D3		BIT(2)	/*PCI D3 mode */
/*NIC halt, re-initialize hw parameters*/
#घोषणा	RT_RF_OFF_LEVL_HALT_NIC		BIT(3)
#घोषणा	RT_RF_OFF_LEVL_FREE_FW		BIT(4)	/*FW मुक्त, re-करोwnload the FW */
#घोषणा	RT_RF_OFF_LEVL_FW_32K		BIT(5)	/*FW in 32k */
/*Always enable ASPM and Clock Req in initialization.*/
#घोषणा	RT_RF_PS_LEVEL_ALWAYS_ASPM	BIT(6)
/* no matter RFOFF or SLEEP we set PS_ASPM_LEVL*/
#घोषणा	RT_PS_LEVEL_ASPM		BIT(7)
/*When LPS is on, disable 2R अगर no packet is received or transmittd.*/
#घोषणा	RT_RF_LPS_DISALBE_2R		BIT(30)
#घोषणा	RT_RF_LPS_LEVEL_ASPM		BIT(31)	/*LPS with ASPM */
#घोषणा	RT_IN_PS_LEVEL(ppsc, _ps_flg)		\
	((ppsc->cur_ps_level & _ps_flg) ? true : false)
#घोषणा	RT_CLEAR_PS_LEVEL(ppsc, _ps_flg)	\
	(ppsc->cur_ps_level &= (~(_ps_flg)))
#घोषणा	RT_SET_PS_LEVEL(ppsc, _ps_flg)		\
	(ppsc->cur_ps_level |= _ps_flg)

#घोषणा FILL_OCTET_STRING(_os, _octet, _len)	\
		(_os).octet = (u8 *)(_octet);		\
		(_os).length = (_len);

#घोषणा CP_MACADDR(des, src)	\
	((des)[0] = (src)[0], (des)[1] = (src)[1],\
	(des)[2] = (src)[2], (des)[3] = (src)[3],\
	(des)[4] = (src)[4], (des)[5] = (src)[5])

#घोषणा	LDPC_HT_ENABLE_RX			BIT(0)
#घोषणा	LDPC_HT_ENABLE_TX			BIT(1)
#घोषणा	LDPC_HT_TEST_TX_ENABLE			BIT(2)
#घोषणा	LDPC_HT_CAP_TX				BIT(3)

#घोषणा	STBC_HT_ENABLE_RX			BIT(0)
#घोषणा	STBC_HT_ENABLE_TX			BIT(1)
#घोषणा	STBC_HT_TEST_TX_ENABLE			BIT(2)
#घोषणा	STBC_HT_CAP_TX				BIT(3)

#घोषणा	LDPC_VHT_ENABLE_RX			BIT(0)
#घोषणा	LDPC_VHT_ENABLE_TX			BIT(1)
#घोषणा	LDPC_VHT_TEST_TX_ENABLE			BIT(2)
#घोषणा	LDPC_VHT_CAP_TX				BIT(3)

#घोषणा	STBC_VHT_ENABLE_RX			BIT(0)
#घोषणा	STBC_VHT_ENABLE_TX			BIT(1)
#घोषणा	STBC_VHT_TEST_TX_ENABLE			BIT(2)
#घोषणा	STBC_VHT_CAP_TX				BIT(3)

बाह्य u8 channel5g[CHANNEL_MAX_NUMBER_5G];

बाह्य u8 channel5g_80m[CHANNEL_MAX_NUMBER_5G_80M];

अटल अंतरभूत u8 rtl_पढ़ो_byte(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस rtlpriv->io.पढ़ो8_sync(rtlpriv, addr);
पूर्ण

अटल अंतरभूत u16 rtl_पढ़ो_word(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस rtlpriv->io.पढ़ो16_sync(rtlpriv, addr);
पूर्ण

अटल अंतरभूत u32 rtl_पढ़ो_dword(काष्ठा rtl_priv *rtlpriv, u32 addr)
अणु
	वापस rtlpriv->io.पढ़ो32_sync(rtlpriv, addr);
पूर्ण

अटल अंतरभूत व्योम rtl_ग_लिखो_byte(काष्ठा rtl_priv *rtlpriv, u32 addr, u8 val8)
अणु
	rtlpriv->io.ग_लिखो8_async(rtlpriv, addr, val8);

	अगर (rtlpriv->cfg->ग_लिखो_पढ़ोback)
		rtlpriv->io.पढ़ो8_sync(rtlpriv, addr);
पूर्ण

अटल अंतरभूत व्योम rtl_ग_लिखो_byte_with_val32(काष्ठा ieee80211_hw *hw,
					     u32 addr, u32 val8)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, addr, (u8)val8);
पूर्ण

अटल अंतरभूत व्योम rtl_ग_लिखो_word(काष्ठा rtl_priv *rtlpriv, u32 addr, u16 val16)
अणु
	rtlpriv->io.ग_लिखो16_async(rtlpriv, addr, val16);

	अगर (rtlpriv->cfg->ग_लिखो_पढ़ोback)
		rtlpriv->io.पढ़ो16_sync(rtlpriv, addr);
पूर्ण

अटल अंतरभूत व्योम rtl_ग_लिखो_dword(काष्ठा rtl_priv *rtlpriv,
				   u32 addr, u32 val32)
अणु
	rtlpriv->io.ग_लिखो32_async(rtlpriv, addr, val32);

	अगर (rtlpriv->cfg->ग_लिखो_पढ़ोback)
		rtlpriv->io.पढ़ो32_sync(rtlpriv, addr);
पूर्ण

अटल अंतरभूत u32 rtl_get_bbreg(काष्ठा ieee80211_hw *hw,
				u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = hw->priv;

	वापस rtlpriv->cfg->ops->get_bbreg(hw, regaddr, biपंचांगask);
पूर्ण

अटल अंतरभूत व्योम rtl_set_bbreg(काष्ठा ieee80211_hw *hw, u32 regaddr,
				 u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = hw->priv;

	rtlpriv->cfg->ops->set_bbreg(hw, regaddr, biपंचांगask, data);
पूर्ण

अटल अंतरभूत व्योम rtl_set_bbreg_with_dwmask(काष्ठा ieee80211_hw *hw,
					     u32 regaddr, u32 data)
अणु
	rtl_set_bbreg(hw, regaddr, 0xffffffff, data);
पूर्ण

अटल अंतरभूत u32 rtl_get_rfreg(काष्ठा ieee80211_hw *hw,
				क्रमागत radio_path rfpath, u32 regaddr,
				u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = hw->priv;

	वापस rtlpriv->cfg->ops->get_rfreg(hw, rfpath, regaddr, biपंचांगask);
पूर्ण

अटल अंतरभूत व्योम rtl_set_rfreg(काष्ठा ieee80211_hw *hw,
				 क्रमागत radio_path rfpath, u32 regaddr,
				 u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = hw->priv;

	rtlpriv->cfg->ops->set_rfreg(hw, rfpath, regaddr, biपंचांगask, data);
पूर्ण

अटल अंतरभूत bool is_hal_stop(काष्ठा rtl_hal *rtlhal)
अणु
	वापस (_HAL_STATE_STOP == rtlhal->state);
पूर्ण

अटल अंतरभूत व्योम set_hal_start(काष्ठा rtl_hal *rtlhal)
अणु
	rtlhal->state = _HAL_STATE_START;
पूर्ण

अटल अंतरभूत व्योम set_hal_stop(काष्ठा rtl_hal *rtlhal)
अणु
	rtlhal->state = _HAL_STATE_STOP;
पूर्ण

अटल अंतरभूत u8 get_rf_type(काष्ठा rtl_phy *rtlphy)
अणु
	वापस rtlphy->rf_type;
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_hdr *rtl_get_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ieee80211_hdr *)(skb->data);
पूर्ण

अटल अंतरभूत __le16 rtl_get_fc(काष्ठा sk_buff *skb)
अणु
	वापस rtl_get_hdr(skb)->frame_control;
पूर्ण

अटल अंतरभूत u16 rtl_get_tid(काष्ठा sk_buff *skb)
अणु
	वापस ieee80211_get_tid(rtl_get_hdr(skb));
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_sta *get_sta(काष्ठा ieee80211_hw *hw,
					    काष्ठा ieee80211_vअगर *vअगर,
					    स्थिर u8 *bssid)
अणु
	वापस ieee80211_find_sta(vअगर, bssid);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_sta *rtl_find_sta(काष्ठा ieee80211_hw *hw,
						 u8 *mac_addr)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	वापस ieee80211_find_sta(mac->vअगर, mac_addr);
पूर्ण

#पूर्ण_अगर
