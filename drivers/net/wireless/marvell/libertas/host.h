<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file function prototypes, data काष्ठाure
 * and  definitions क्रम all the host/station commands
 */

#अगर_अघोषित _LBS_HOST_H_
#घोषणा _LBS_HOST_H_

#समावेश "types.h"
#समावेश "defs.h"

#घोषणा DEFAULT_AD_HOC_CHANNEL                  6

#घोषणा CMD_OPTION_WAITFORRSP                   0x0002

/* Host command IDs */

/*
 * Return command are almost always the same as the host command, but with
 * bit 15 set high.  There are a few exceptions, though...
 */
#घोषणा CMD_RET(cmd)                            (0x8000 | cmd)

/* Return command convention exceptions: */
#घोषणा CMD_RET_802_11_ASSOCIATE                0x8012

/* Command codes */
#घोषणा CMD_GET_HW_SPEC                         0x0003
#घोषणा CMD_EEPROM_UPDATE                       0x0004
#घोषणा CMD_802_11_RESET                        0x0005
#घोषणा CMD_802_11_SCAN                         0x0006
#घोषणा CMD_802_11_GET_LOG                      0x000b
#घोषणा CMD_MAC_MULTICAST_ADR                   0x0010
#घोषणा CMD_802_11_AUTHENTICATE                 0x0011
#घोषणा CMD_802_11_EEPROM_ACCESS                0x0059
#घोषणा CMD_802_11_ASSOCIATE                    0x0050
#घोषणा CMD_802_11_SET_WEP                      0x0013
#घोषणा CMD_802_11_GET_STAT                     0x0014
#घोषणा CMD_802_3_GET_STAT                      0x0015
#घोषणा CMD_802_11_SNMP_MIB                     0x0016
#घोषणा CMD_MAC_REG_MAP                         0x0017
#घोषणा CMD_BBP_REG_MAP                         0x0018
#घोषणा CMD_MAC_REG_ACCESS                      0x0019
#घोषणा CMD_BBP_REG_ACCESS                      0x001a
#घोषणा CMD_RF_REG_ACCESS                       0x001b
#घोषणा CMD_802_11_RADIO_CONTROL                0x001c
#घोषणा CMD_802_11_RF_CHANNEL                   0x001d
#घोषणा CMD_802_11_RF_TX_POWER                  0x001e
#घोषणा CMD_802_11_RSSI                         0x001f
#घोषणा CMD_802_11_RF_ANTENNA                   0x0020
#घोषणा CMD_802_11_PS_MODE                      0x0021
#घोषणा CMD_802_11_DATA_RATE                    0x0022
#घोषणा CMD_RF_REG_MAP                          0x0023
#घोषणा CMD_802_11_DEAUTHENTICATE               0x0024
#घोषणा CMD_802_11_REASSOCIATE                  0x0025
#घोषणा CMD_MAC_CONTROL                         0x0028
#घोषणा CMD_802_11_AD_HOC_START                 0x002b
#घोषणा CMD_802_11_AD_HOC_JOIN                  0x002c
#घोषणा CMD_802_11_QUERY_TKIP_REPLY_CNTRS       0x002e
#घोषणा CMD_802_11_ENABLE_RSN                   0x002f
#घोषणा CMD_802_11_SET_AFC                      0x003c
#घोषणा CMD_802_11_GET_AFC                      0x003d
#घोषणा CMD_802_11_DEEP_SLEEP                   0x003e
#घोषणा CMD_802_11_AD_HOC_STOP                  0x0040
#घोषणा CMD_802_11_HOST_SLEEP_CFG               0x0043
#घोषणा CMD_802_11_WAKEUP_CONFIRM               0x0044
#घोषणा CMD_802_11_HOST_SLEEP_ACTIVATE          0x0045
#घोषणा CMD_802_11_BEACON_STOP                  0x0049
#घोषणा CMD_802_11_MAC_ADDRESS                  0x004d
#घोषणा CMD_802_11_LED_GPIO_CTRL                0x004e
#घोषणा CMD_802_11_BAND_CONFIG                  0x0058
#घोषणा CMD_GSPI_BUS_CONFIG                     0x005a
#घोषणा CMD_802_11D_DOMAIN_INFO                 0x005b
#घोषणा CMD_802_11_KEY_MATERIAL                 0x005e
#घोषणा CMD_802_11_SLEEP_PARAMS                 0x0066
#घोषणा CMD_802_11_INACTIVITY_TIMEOUT           0x0067
#घोषणा CMD_802_11_SLEEP_PERIOD                 0x0068
#घोषणा CMD_802_11_TPC_CFG                      0x0072
#घोषणा CMD_802_11_PA_CFG                       0x0073
#घोषणा CMD_802_11_FW_WAKE_METHOD               0x0074
#घोषणा CMD_802_11_SUBSCRIBE_EVENT              0x0075
#घोषणा CMD_802_11_RATE_ADAPT_RATESET           0x0076
#घोषणा CMD_802_11_TX_RATE_QUERY                0x007f
#घोषणा CMD_GET_TSF                             0x0080
#घोषणा CMD_BT_ACCESS                           0x0087
#घोषणा CMD_FWT_ACCESS                          0x0095
#घोषणा CMD_802_11_MONITOR_MODE                 0x0098
#घोषणा CMD_MESH_ACCESS                         0x009b
#घोषणा CMD_MESH_CONFIG_OLD                     0x00a3
#घोषणा CMD_MESH_CONFIG                         0x00ac
#घोषणा CMD_SET_BOOT2_VER                       0x00a5
#घोषणा CMD_FUNC_INIT                           0x00a9
#घोषणा CMD_FUNC_SHUTDOWN                       0x00aa
#घोषणा CMD_802_11_BEACON_CTRL                  0x00b0

/* For the IEEE Power Save */
#घोषणा PS_MODE_ACTION_ENTER_PS                 0x0030
#घोषणा PS_MODE_ACTION_EXIT_PS                  0x0031
#घोषणा PS_MODE_ACTION_SLEEP_CONFIRMED          0x0034

#घोषणा CMD_ENABLE_RSN                          0x0001
#घोषणा CMD_DISABLE_RSN                         0x0000

#घोषणा CMD_ACT_GET                             0x0000
#घोषणा CMD_ACT_SET                             0x0001

/* Define action or option क्रम CMD_802_11_SET_WEP */
#घोषणा CMD_ACT_ADD                             0x0002
#घोषणा CMD_ACT_REMOVE                          0x0004

#घोषणा CMD_TYPE_WEP_40_BIT                     0x01
#घोषणा CMD_TYPE_WEP_104_BIT                    0x02

#घोषणा CMD_NUM_OF_WEP_KEYS                     4

#घोषणा CMD_WEP_KEY_INDEX_MASK                  0x3fff

/* Define action or option क्रम CMD_802_11_SCAN */
#घोषणा CMD_BSS_TYPE_BSS                        0x0001
#घोषणा CMD_BSS_TYPE_IBSS                       0x0002
#घोषणा CMD_BSS_TYPE_ANY                        0x0003

/* Define action or option क्रम CMD_802_11_SCAN */
#घोषणा CMD_SCAN_TYPE_ACTIVE                    0x0000
#घोषणा CMD_SCAN_TYPE_PASSIVE                   0x0001

#घोषणा CMD_SCAN_RADIO_TYPE_BG                  0

#घोषणा CMD_SCAN_PROBE_DELAY_TIME               0

/* Define action or option क्रम CMD_MAC_CONTROL */
#घोषणा CMD_ACT_MAC_RX_ON                       0x0001
#घोषणा CMD_ACT_MAC_TX_ON                       0x0002
#घोषणा CMD_ACT_MAC_LOOPBACK_ON                 0x0004
#घोषणा CMD_ACT_MAC_WEP_ENABLE                  0x0008
#घोषणा CMD_ACT_MAC_INT_ENABLE                  0x0010
#घोषणा CMD_ACT_MAC_MULTICAST_ENABLE            0x0020
#घोषणा CMD_ACT_MAC_BROADCAST_ENABLE            0x0040
#घोषणा CMD_ACT_MAC_PROMISCUOUS_ENABLE          0x0080
#घोषणा CMD_ACT_MAC_ALL_MULTICAST_ENABLE        0x0100
#घोषणा CMD_ACT_MAC_STRICT_PROTECTION_ENABLE    0x0400

/* Event flags क्रम CMD_802_11_SUBSCRIBE_EVENT */
#घोषणा CMD_SUBSCRIBE_RSSI_LOW                  0x0001
#घोषणा CMD_SUBSCRIBE_SNR_LOW                   0x0002
#घोषणा CMD_SUBSCRIBE_FAILCOUNT                 0x0004
#घोषणा CMD_SUBSCRIBE_BCNMISS                   0x0008
#घोषणा CMD_SUBSCRIBE_RSSI_HIGH                 0x0010
#घोषणा CMD_SUBSCRIBE_SNR_HIGH                  0x0020

#घोषणा RADIO_PREAMBLE_LONG                     0x00
#घोषणा RADIO_PREAMBLE_SHORT                    0x02
#घोषणा RADIO_PREAMBLE_AUTO                     0x04

/* Define action or option क्रम CMD_802_11_RF_CHANNEL */
#घोषणा CMD_OPT_802_11_RF_CHANNEL_GET           0x00
#घोषणा CMD_OPT_802_11_RF_CHANNEL_SET           0x01

/* Define action or option क्रम CMD_802_11_DATA_RATE */
#घोषणा CMD_ACT_SET_TX_AUTO                     0x0000
#घोषणा CMD_ACT_SET_TX_FIX_RATE                 0x0001
#घोषणा CMD_ACT_GET_TX_RATE                     0x0002

/* Options क्रम CMD_802_11_FW_WAKE_METHOD */
#घोषणा CMD_WAKE_METHOD_UNCHANGED               0x0000
#घोषणा CMD_WAKE_METHOD_COMMAND_INT             0x0001
#घोषणा CMD_WAKE_METHOD_GPIO                    0x0002

/* Object IDs क्रम CMD_802_11_SNMP_MIB */
#घोषणा SNMP_MIB_OID_BSS_TYPE                   0x0000
#घोषणा SNMP_MIB_OID_OP_RATE_SET                0x0001
#घोषणा SNMP_MIB_OID_BEACON_PERIOD              0x0002  /* Reserved on v9+ */
#घोषणा SNMP_MIB_OID_DTIM_PERIOD                0x0003  /* Reserved on v9+ */
#घोषणा SNMP_MIB_OID_ASSOC_TIMEOUT              0x0004  /* Reserved on v9+ */
#घोषणा SNMP_MIB_OID_RTS_THRESHOLD              0x0005
#घोषणा SNMP_MIB_OID_SHORT_RETRY_LIMIT          0x0006
#घोषणा SNMP_MIB_OID_LONG_RETRY_LIMIT           0x0007
#घोषणा SNMP_MIB_OID_FRAG_THRESHOLD             0x0008
#घोषणा SNMP_MIB_OID_11D_ENABLE                 0x0009
#घोषणा SNMP_MIB_OID_11H_ENABLE                 0x000A

/* Define action or option क्रम CMD_BT_ACCESS */
क्रमागत cmd_bt_access_opts अणु
	/* The bt commands start at 5 instead of 1 because the old dft commands
	 * are mapped to 1-4.  These old commands are no दीर्घer मुख्यtained and
	 * should not be called.
	 */
	CMD_ACT_BT_ACCESS_ADD = 5,
	CMD_ACT_BT_ACCESS_DEL,
	CMD_ACT_BT_ACCESS_LIST,
	CMD_ACT_BT_ACCESS_RESET,
	CMD_ACT_BT_ACCESS_SET_INVERT,
	CMD_ACT_BT_ACCESS_GET_INVERT
पूर्ण;

/* Define action or option क्रम CMD_FWT_ACCESS */
क्रमागत cmd_fwt_access_opts अणु
	CMD_ACT_FWT_ACCESS_ADD = 1,
	CMD_ACT_FWT_ACCESS_DEL,
	CMD_ACT_FWT_ACCESS_LOOKUP,
	CMD_ACT_FWT_ACCESS_LIST,
	CMD_ACT_FWT_ACCESS_LIST_ROUTE,
	CMD_ACT_FWT_ACCESS_LIST_NEIGHBOR,
	CMD_ACT_FWT_ACCESS_RESET,
	CMD_ACT_FWT_ACCESS_CLEANUP,
	CMD_ACT_FWT_ACCESS_TIME,
पूर्ण;

/* Define action or option क्रम CMD_802_11_HOST_SLEEP_CFG */
क्रमागत cmd_wol_cfg_opts अणु
	CMD_ACT_ACTION_NONE = 0,
	CMD_ACT_SET_WOL_RULE,
	CMD_ACT_GET_WOL_RULE,
	CMD_ACT_RESET_WOL_RULE,
पूर्ण;

/* Define action or option क्रम CMD_MESH_ACCESS */
क्रमागत cmd_mesh_access_opts अणु
	CMD_ACT_MESH_GET_TTL = 1,
	CMD_ACT_MESH_SET_TTL,
	CMD_ACT_MESH_GET_STATS,
	CMD_ACT_MESH_GET_ANYCAST,
	CMD_ACT_MESH_SET_ANYCAST,
	CMD_ACT_MESH_SET_LINK_COSTS,
	CMD_ACT_MESH_GET_LINK_COSTS,
	CMD_ACT_MESH_SET_BCAST_RATE,
	CMD_ACT_MESH_GET_BCAST_RATE,
	CMD_ACT_MESH_SET_RREQ_DELAY,
	CMD_ACT_MESH_GET_RREQ_DELAY,
	CMD_ACT_MESH_SET_ROUTE_EXP,
	CMD_ACT_MESH_GET_ROUTE_EXP,
	CMD_ACT_MESH_SET_AUTOSTART_ENABLED,
	CMD_ACT_MESH_GET_AUTOSTART_ENABLED,
	CMD_ACT_MESH_SET_GET_PRB_RSP_LIMIT = 17,
पूर्ण;

/* Define actions and types क्रम CMD_MESH_CONFIG */
क्रमागत cmd_mesh_config_actions अणु
	CMD_ACT_MESH_CONFIG_STOP = 0,
	CMD_ACT_MESH_CONFIG_START,
	CMD_ACT_MESH_CONFIG_SET,
	CMD_ACT_MESH_CONFIG_GET,
पूर्ण;

क्रमागत cmd_mesh_config_types अणु
	CMD_TYPE_MESH_SET_BOOTFLAG = 1,
	CMD_TYPE_MESH_SET_BOOTTIME,
	CMD_TYPE_MESH_SET_DEF_CHANNEL,
	CMD_TYPE_MESH_SET_MESH_IE,
	CMD_TYPE_MESH_GET_DEFAULTS,
	CMD_TYPE_MESH_GET_MESH_IE, /* GET_DEFAULTS is superset of GET_MESHIE */
पूर्ण;

/* Card Event definition */
#घोषणा MACREG_INT_CODE_TX_PPA_FREE		0
#घोषणा MACREG_INT_CODE_TX_DMA_DONE		1
#घोषणा MACREG_INT_CODE_LINK_LOST_W_SCAN	2
#घोषणा MACREG_INT_CODE_LINK_LOST_NO_SCAN	3
#घोषणा MACREG_INT_CODE_LINK_SENSED		4
#घोषणा MACREG_INT_CODE_CMD_FINISHED		5
#घोषणा MACREG_INT_CODE_MIB_CHANGED		6
#घोषणा MACREG_INT_CODE_INIT_DONE		7
#घोषणा MACREG_INT_CODE_DEAUTHENTICATED		8
#घोषणा MACREG_INT_CODE_DISASSOCIATED		9
#घोषणा MACREG_INT_CODE_PS_AWAKE		10
#घोषणा MACREG_INT_CODE_PS_SLEEP		11
#घोषणा MACREG_INT_CODE_MIC_ERR_MULTICAST	13
#घोषणा MACREG_INT_CODE_MIC_ERR_UNICAST		14
#घोषणा MACREG_INT_CODE_WM_AWAKE		15
#घोषणा MACREG_INT_CODE_DEEP_SLEEP_AWAKE	16
#घोषणा MACREG_INT_CODE_ADHOC_BCN_LOST		17
#घोषणा MACREG_INT_CODE_HOST_AWAKE		18
#घोषणा MACREG_INT_CODE_STOP_TX			19
#घोषणा MACREG_INT_CODE_START_TX		20
#घोषणा MACREG_INT_CODE_CHANNEL_SWITCH		21
#घोषणा MACREG_INT_CODE_MEASUREMENT_RDY		22
#घोषणा MACREG_INT_CODE_WMM_CHANGE		23
#घोषणा MACREG_INT_CODE_BG_SCAN_REPORT		24
#घोषणा MACREG_INT_CODE_RSSI_LOW		25
#घोषणा MACREG_INT_CODE_SNR_LOW			26
#घोषणा MACREG_INT_CODE_MAX_FAIL		27
#घोषणा MACREG_INT_CODE_RSSI_HIGH		28
#घोषणा MACREG_INT_CODE_SNR_HIGH		29
#घोषणा MACREG_INT_CODE_MESH_AUTO_STARTED	35
#घोषणा MACREG_INT_CODE_FIRMWARE_READY		48


/* 802.11-related definitions */

/* TxPD descriptor */
काष्ठा txpd अणु
	/* जोड़ to cope up with later FW revisions */
	जोड़ अणु
		/* Current Tx packet status */
		__le32 tx_status;
		काष्ठा अणु
			/* BSS type: client, AP, etc. */
			u8 bss_type;
			/* BSS number */
			u8 bss_num;
			/* Reserved */
			__le16 reserved;
		पूर्ण bss;
	पूर्ण u;
	/* Tx control */
	__le32 tx_control;
	__le32 tx_packet_location;
	/* Tx packet length */
	__le16 tx_packet_length;
	/* First 2 byte of destination MAC address */
	u8 tx_dest_addr_high[2];
	/* Last 4 byte of destination MAC address */
	u8 tx_dest_addr_low[4];
	/* Pkt Priority */
	u8 priority;
	/* Pkt Trasnit Power control */
	u8 घातermgmt;
	/* Amount of समय the packet has been queued (units = 2ms) */
	u8 pktdelay_2ms;
	/* reserved */
	u8 reserved1;
पूर्ण __packed;

/* RxPD Descriptor */
काष्ठा rxpd अणु
	/* जोड़ to cope up with later FW revisions */
	जोड़ अणु
		/* Current Rx packet status */
		__le16 status;
		काष्ठा अणु
			/* BSS type: client, AP, etc. */
			u8 bss_type;
			/* BSS number */
			u8 bss_num;
		पूर्ण __packed bss;
	पूर्ण __packed u;

	/* SNR */
	u8 snr;

	/* Tx control */
	u8 rx_control;

	/* Pkt length */
	__le16 pkt_len;

	/* Noise Floor */
	u8 nf;

	/* Rx Packet Rate */
	u8 rx_rate;

	/* Pkt addr */
	__le32 pkt_ptr;

	/* Next Rx RxPD addr */
	__le32 next_rxpd_ptr;

	/* Pkt Priority */
	u8 priority;
	u8 reserved[3];
पूर्ण __packed;

काष्ठा cmd_header अणु
	__le16 command;
	__le16 size;
	__le16 seqnum;
	__le16 result;
पूर्ण __packed;

/* Generic काष्ठाure to hold all key types. */
काष्ठा enc_key अणु
	u16 len;
	u16 flags;  /* KEY_INFO_* from defs.h */
	u16 type; /* KEY_TYPE_* from defs.h */
	u8 key[32];
पूर्ण;

/* lbs_offset_value */
काष्ठा lbs_offset_value अणु
	u32 offset;
	u32 value;
पूर्ण __packed;

#घोषणा MAX_11D_TRIPLETS	83

काष्ठा mrvl_ie_करोमुख्य_param_set अणु
	काष्ठा mrvl_ie_header header;

	u8 country_code[IEEE80211_COUNTRY_STRING_LEN];
	काष्ठा ieee80211_country_ie_triplet triplet[MAX_11D_TRIPLETS];
पूर्ण __packed;

काष्ठा cmd_ds_802_11d_करोमुख्य_info अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	काष्ठा mrvl_ie_करोमुख्य_param_set करोमुख्य;
पूर्ण __packed;

/*
 * Define data काष्ठाure क्रम CMD_GET_HW_SPEC
 * This काष्ठाure defines the response क्रम the GET_HW_SPEC command
 */
काष्ठा cmd_ds_get_hw_spec अणु
	काष्ठा cmd_header hdr;

	/* HW Interface version number */
	__le16 hwअगरversion;
	/* HW version number */
	__le16 version;
	/* Max number of TxPD FW can handle */
	__le16 nr_txpd;
	/* Max no of Multicast address */
	__le16 nr_mcast_adr;
	/* MAC address */
	u8 permanentaddr[6];

	/* region Code */
	__le16 regioncode;

	/* Number of antenna used */
	__le16 nr_antenna;

	/* FW release number, example 0x01030304 = 2.3.4p1 */
	__le32 fwrelease;

	/* Base Address of TxPD queue */
	__le32 wcb_base;
	/* Read Poपूर्णांकer of RxPd queue */
	__le32 rxpd_rdptr;

	/* Write Poपूर्णांकer of RxPd queue */
	__le32 rxpd_wrptr;

	/*FW/HW capability */
	__le32 fwcapinfo;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_subscribe_event अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 events;

	/* A TLV to the CMD_802_11_SUBSCRIBE_EVENT command can contain a
	 * number of TLVs. From the v5.1 manual, those TLVs would add up to
	 * 40 bytes. However, future firmware might add additional TLVs, so I
	 * bump this up a bit.
	 */
	uपूर्णांक8_t tlv[128];
पूर्ण __packed;

/*
 * This scan handle Country Inक्रमmation IE(802.11d compliant)
 * Define data काष्ठाure क्रम CMD_802_11_SCAN
 */
काष्ठा cmd_ds_802_11_scan अणु
	काष्ठा cmd_header hdr;

	uपूर्णांक8_t bsstype;
	uपूर्णांक8_t bssid[ETH_ALEN];
	uपूर्णांक8_t tlvbuffer[];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_scan_rsp अणु
	काष्ठा cmd_header hdr;

	__le16 bssdescriptsize;
	uपूर्णांक8_t nr_sets;
	uपूर्णांक8_t bssdesc_and_tlvbuffer[];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_get_log अणु
	काष्ठा cmd_header hdr;

	__le32 mcasttxframe;
	__le32 failed;
	__le32 retry;
	__le32 multiretry;
	__le32 framedup;
	__le32 rtssuccess;
	__le32 rtsfailure;
	__le32 ackfailure;
	__le32 rxfrag;
	__le32 mcastrxframe;
	__le32 fcserror;
	__le32 txframe;
	__le32 wepundecryptable;
पूर्ण __packed;

काष्ठा cmd_ds_mac_control अणु
	काष्ठा cmd_header hdr;
	__le16 action;
	u16 reserved;
पूर्ण __packed;

काष्ठा cmd_ds_mac_multicast_adr अणु
	काष्ठा cmd_header hdr;
	__le16 action;
	__le16 nr_of_adrs;
	u8 maclist[ETH_ALEN * MRVDRV_MAX_MULTICAST_LIST_SIZE];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_authenticate अणु
	काष्ठा cmd_header hdr;

	u8 bssid[ETH_ALEN];
	u8 authtype;
	u8 reserved[10];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_deauthenticate अणु
	काष्ठा cmd_header hdr;

	u8 macaddr[ETH_ALEN];
	__le16 reasoncode;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_associate अणु
	काष्ठा cmd_header hdr;

	u8 bssid[6];
	__le16 capability;
	__le16 listenपूर्णांकerval;
	__le16 bcnperiod;
	u8 dtimperiod;
	u8 iebuf[512];    /* Enough क्रम required and most optional IEs */
पूर्ण __packed;

काष्ठा cmd_ds_802_11_associate_response अणु
	काष्ठा cmd_header hdr;

	__le16 capability;
	__le16 statuscode;
	__le16 aid;
	u8 iebuf[512];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_set_wep अणु
	काष्ठा cmd_header hdr;

	/* ACT_ADD, ACT_REMOVE or ACT_ENABLE */
	__le16 action;

	/* key Index selected क्रम Tx */
	__le16 keyindex;

	/* 40, 128bit or TXWEP */
	uपूर्णांक8_t keytype[4];
	uपूर्णांक8_t keymaterial[4][16];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_snmp_mib अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 oid;
	__le16 bufsize;
	u8 value[128];
पूर्ण __packed;

काष्ठा cmd_ds_reg_access अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 offset;
	जोड़ अणु
		u8 bbp_rf;  /* क्रम BBP and RF रेजिस्टरs */
		__le32 mac; /* क्रम MAC रेजिस्टरs */
	पूर्ण value;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_radio_control अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 control;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_beacon_control अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 beacon_enable;
	__le16 beacon_period;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_sleep_params अणु
	काष्ठा cmd_header hdr;

	/* ACT_GET/ACT_SET */
	__le16 action;

	/* Sleep घड़ी error in ppm */
	__le16 error;

	/* Wakeup offset in usec */
	__le16 offset;

	/* Clock stabilization समय in usec */
	__le16 stableसमय;

	/* control periodic calibration */
	uपूर्णांक8_t calcontrol;

	/* control the use of बाह्यal sleep घड़ी */
	uपूर्णांक8_t बाह्यalsleepclk;

	/* reserved field, should be set to zero */
	__le16 reserved;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_rf_channel अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 channel;
	__le16 rftype;      /* unused */
	__le16 reserved;    /* unused */
	u8 channellist[32]; /* unused */
पूर्ण __packed;

काष्ठा cmd_ds_802_11_rssi अणु
	काष्ठा cmd_header hdr;

	/*
	 * request:  number of beacons (N) to average the SNR and NF over
	 * response: SNR of most recent beacon
	 */
	__le16 n_or_snr;

	/*
	 * The following fields are only set in the response.
	 * In the request these are reserved and should be set to 0.
	 */
	__le16 nf;       /* most recent beacon noise न्यूनमान */
	__le16 avg_snr;  /* average SNR weighted by N from request */
	__le16 avg_nf;   /* average noise न्यूनमान weighted by N from request */
पूर्ण __packed;

काष्ठा cmd_ds_802_11_mac_address अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	u8 macadd[ETH_ALEN];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_rf_tx_घातer अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 curlevel;
	s8 maxlevel;
	s8 minlevel;
पूर्ण __packed;

/* MONITOR_MODE only exists in OLPC v5 firmware */
काष्ठा cmd_ds_802_11_monitor_mode अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 mode;
पूर्ण __packed;

काष्ठा cmd_ds_set_boot2_ver अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 version;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_fw_wake_method अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 method;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_ps_mode अणु
	काष्ठा cmd_header hdr;

	__le16 action;

	/*
	 * Interval क्रम keepalive in PS mode:
	 * 0x0000 = करोn't change
	 * 0x001E = firmware शेष
	 * 0xFFFF = disable
	 */
	__le16 nullpktपूर्णांकerval;

	/*
	 * Number of DTIM पूर्णांकervals to wake up क्रम:
	 * 0 = करोn't change
	 * 1 = firmware शेष
	 * 5 = max
	 */
	__le16 multipledtim;

	__le16 reserved;
	__le16 locallistenपूर्णांकerval;

	/*
	 * AdHoc awake period (FW v9+ only):
	 * 0 = करोn't change
	 * 1 = always awake (IEEE standard behavior)
	 * 2 - 31 = sleep क्रम (n - 1) periods and awake क्रम 1 period
	 * 32 - 254 = invalid
	 * 255 = sleep at each ATIM
	 */
	__le16 adhoc_awake_period;
पूर्ण __packed;

काष्ठा cmd_confirm_sleep अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 nullpktपूर्णांकerval;
	__le16 multipledtim;
	__le16 reserved;
	__le16 locallistenपूर्णांकerval;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_data_rate अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 reserved;
	u8 rates[MAX_RATES];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_rate_adapt_rateset अणु
	काष्ठा cmd_header hdr;
	__le16 action;
	__le16 enablehwस्वतः;
	__le16 biपंचांगap;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_ad_hoc_start अणु
	काष्ठा cmd_header hdr;

	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 bsstype;
	__le16 beaconperiod;
	u8 dtimperiod;   /* Reserved on v9 and later */
	काष्ठा ieee_ie_ibss_param_set ibss;
	u8 reserved1[4];
	काष्ठा ieee_ie_ds_param_set ds;
	u8 reserved2[4];
	__le16 probedelay;  /* Reserved on v9 and later */
	__le16 capability;
	u8 rates[MAX_RATES];
	u8 tlv_memory_size_pad[100];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_ad_hoc_result अणु
	काष्ठा cmd_header hdr;

	u8 pad[3];
	u8 bssid[ETH_ALEN];
पूर्ण __packed;

काष्ठा adhoc_bssdesc अणु
	u8 bssid[ETH_ALEN];
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 type;
	__le16 beaconperiod;
	u8 dtimperiod;
	__le64 बारtamp;
	__le64 स_स्थानीय;
	काष्ठा ieee_ie_ds_param_set ds;
	u8 reserved1[4];
	काष्ठा ieee_ie_ibss_param_set ibss;
	u8 reserved2[4];
	__le16 capability;
	u8 rates[MAX_RATES];

	/*
	 * DO NOT ADD ANY FIELDS TO THIS STRUCTURE. It is used below in the
	 * Adhoc join command and will cause a binary layout mismatch with
	 * the firmware
	 */
पूर्ण __packed;

काष्ठा cmd_ds_802_11_ad_hoc_join अणु
	काष्ठा cmd_header hdr;

	काष्ठा adhoc_bssdesc bss;
	__le16 failसमयout;   /* Reserved on v9 and later */
	__le16 probedelay;    /* Reserved on v9 and later */
पूर्ण __packed;

काष्ठा cmd_ds_802_11_ad_hoc_stop अणु
	काष्ठा cmd_header hdr;
पूर्ण __packed;

काष्ठा cmd_ds_802_11_enable_rsn अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 enable;
पूर्ण __packed;

काष्ठा MrvlIEtype_keyParamSet अणु
	/* type ID */
	__le16 type;

	/* length of Payload */
	__le16 length;

	/* type of key: WEP=0, TKIP=1, AES=2 */
	__le16 keytypeid;

	/* key control Info specअगरic to a keytypeid */
	__le16 keyinfo;

	/* length of key */
	__le16 keylen;

	/* key material of size keylen */
	u8 key[32];
पूर्ण __packed;

#घोषणा MAX_WOL_RULES 		16

काष्ठा host_wol_rule अणु
	uपूर्णांक8_t rule_no;
	uपूर्णांक8_t rule_ops;
	__le16 sig_offset;
	__le16 sig_length;
	__le16 reserve;
	__be32 sig_mask;
	__be32 signature;
पूर्ण __packed;

काष्ठा wol_config अणु
	uपूर्णांक8_t action;
	uपूर्णांक8_t pattern;
	uपूर्णांक8_t no_rules_in_cmd;
	uपूर्णांक8_t result;
	काष्ठा host_wol_rule rule[MAX_WOL_RULES];
पूर्ण __packed;

काष्ठा cmd_ds_host_sleep अणु
	काष्ठा cmd_header hdr;
	__le32 criteria;
	uपूर्णांक8_t gpio;
	uपूर्णांक16_t gap;
	काष्ठा wol_config wol_conf;
पूर्ण __packed;



काष्ठा cmd_ds_802_11_key_material अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	काष्ठा MrvlIEtype_keyParamSet keyParamSet[2];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_eeprom_access अणु
	काष्ठा cmd_header hdr;
	__le16 action;
	__le16 offset;
	__le16 len;
	/* firmware says it वापसs a maximum of 20 bytes */
#घोषणा LBS_EEPROM_READ_LEN 20
	u8 value[LBS_EEPROM_READ_LEN];
पूर्ण __packed;

काष्ठा cmd_ds_802_11_tpc_cfg अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	uपूर्णांक8_t enable;
	पूर्णांक8_t P0;
	पूर्णांक8_t P1;
	पूर्णांक8_t P2;
	uपूर्णांक8_t usesnr;
पूर्ण __packed;


काष्ठा cmd_ds_802_11_pa_cfg अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	uपूर्णांक8_t enable;
	पूर्णांक8_t P0;
	पूर्णांक8_t P1;
	पूर्णांक8_t P2;
पूर्ण __packed;


काष्ठा cmd_ds_802_11_led_ctrl अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 numled;
	u8 data[256];
पूर्ण __packed;

/* Automatic Frequency Control */
काष्ठा cmd_ds_802_11_afc अणु
	काष्ठा cmd_header hdr;

	__le16 afc_स्वतः;
	जोड़ अणु
		काष्ठा अणु
			__le16 threshold;
			__le16 period;
		पूर्ण;
		काष्ठा अणु
			__le16 timing_offset; /* चिन्हित */
			__le16 carrier_offset; /* चिन्हित */
		पूर्ण;
	पूर्ण;
पूर्ण __packed;

काष्ठा cmd_tx_rate_query अणु
	__le16 txrate;
पूर्ण __packed;

काष्ठा cmd_ds_get_tsf अणु
	__le64 tsfvalue;
पूर्ण __packed;

काष्ठा cmd_ds_bt_access अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le32 id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
पूर्ण __packed;

काष्ठा cmd_ds_fwt_access अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le32 id;
	u8 valid;
	u8 da[ETH_ALEN];
	u8 dir;
	u8 ra[ETH_ALEN];
	__le32 ssn;
	__le32 dsn;
	__le32 metric;
	u8 rate;
	u8 hopcount;
	u8 ttl;
	__le32 expiration;
	u8 sleepmode;
	__le32 snr;
	__le32 references;
	u8 prec[ETH_ALEN];
पूर्ण __packed;

काष्ठा cmd_ds_mesh_config अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le16 channel;
	__le16 type;
	__le16 length;
	u8 data[128];	/* last position reserved */
पूर्ण __packed;

काष्ठा cmd_ds_mesh_access अणु
	काष्ठा cmd_header hdr;

	__le16 action;
	__le32 data[32];	/* last position reserved */
पूर्ण __packed;

/* Number of stats counters वापसed by the firmware */
#घोषणा MESH_STATS_NUM 8
#पूर्ण_अगर
