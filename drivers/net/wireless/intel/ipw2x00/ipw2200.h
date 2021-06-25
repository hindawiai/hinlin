<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************

  Copyright(c) 2003 - 2006 Intel Corporation. All rights reserved.


  Contact Inक्रमmation:
  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

******************************************************************************/

#अगर_अघोषित __ipw2200_h__
#घोषणा __ipw2200_h__

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/firmware.h>
#समावेश <linux/wireless.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/पन.स>

#समावेश <net/lib80211.h>
#समावेश <net/ieee80211_radiotap.h>

#घोषणा DRV_NAME	"ipw2200"

#समावेश <linux/workqueue.h>

#समावेश "libipw.h"

/* Authentication  and Association States */
क्रमागत connection_manager_assoc_states अणु
	CMAS_INIT = 0,
	CMAS_TX_AUTH_SEQ_1,
	CMAS_RX_AUTH_SEQ_2,
	CMAS_AUTH_SEQ_1_PASS,
	CMAS_AUTH_SEQ_1_FAIL,
	CMAS_TX_AUTH_SEQ_3,
	CMAS_RX_AUTH_SEQ_4,
	CMAS_AUTH_SEQ_2_PASS,
	CMAS_AUTH_SEQ_2_FAIL,
	CMAS_AUTHENTICATED,
	CMAS_TX_ASSOC,
	CMAS_RX_ASSOC_RESP,
	CMAS_ASSOCIATED,
	CMAS_LAST
पूर्ण;

#घोषणा IPW_WAIT                     (1<<0)
#घोषणा IPW_QUIET                    (1<<1)
#घोषणा IPW_ROAMING                  (1<<2)

#घोषणा IPW_POWER_MODE_CAM           0x00	//(always on)
#घोषणा IPW_POWER_INDEX_1            0x01
#घोषणा IPW_POWER_INDEX_2            0x02
#घोषणा IPW_POWER_INDEX_3            0x03
#घोषणा IPW_POWER_INDEX_4            0x04
#घोषणा IPW_POWER_INDEX_5            0x05
#घोषणा IPW_POWER_AC                 0x06
#घोषणा IPW_POWER_BATTERY            0x07
#घोषणा IPW_POWER_LIMIT              0x07
#घोषणा IPW_POWER_MASK               0x0F
#घोषणा IPW_POWER_ENABLED            0x10
#घोषणा IPW_POWER_LEVEL(x)           ((x) & IPW_POWER_MASK)

#घोषणा IPW_CMD_HOST_COMPLETE                 2
#घोषणा IPW_CMD_POWER_DOWN                    4
#घोषणा IPW_CMD_SYSTEM_CONFIG                 6
#घोषणा IPW_CMD_MULTICAST_ADDRESS             7
#घोषणा IPW_CMD_SSID                          8
#घोषणा IPW_CMD_ADAPTER_ADDRESS              11
#घोषणा IPW_CMD_PORT_TYPE                    12
#घोषणा IPW_CMD_RTS_THRESHOLD                15
#घोषणा IPW_CMD_FRAG_THRESHOLD               16
#घोषणा IPW_CMD_POWER_MODE                   17
#घोषणा IPW_CMD_WEP_KEY                      18
#घोषणा IPW_CMD_TGI_TX_KEY                   19
#घोषणा IPW_CMD_SCAN_REQUEST                 20
#घोषणा IPW_CMD_ASSOCIATE                    21
#घोषणा IPW_CMD_SUPPORTED_RATES              22
#घोषणा IPW_CMD_SCAN_ABORT                   23
#घोषणा IPW_CMD_TX_FLUSH                     24
#घोषणा IPW_CMD_QOS_PARAMETERS               25
#घोषणा IPW_CMD_SCAN_REQUEST_EXT             26
#घोषणा IPW_CMD_DINO_CONFIG                  30
#घोषणा IPW_CMD_RSN_CAPABILITIES             31
#घोषणा IPW_CMD_RX_KEY                       32
#घोषणा IPW_CMD_CARD_DISABLE                 33
#घोषणा IPW_CMD_SEED_NUMBER                  34
#घोषणा IPW_CMD_TX_POWER                     35
#घोषणा IPW_CMD_COUNTRY_INFO                 36
#घोषणा IPW_CMD_AIRONET_INFO                 37
#घोषणा IPW_CMD_AP_TX_POWER                  38
#घोषणा IPW_CMD_CCKM_INFO                    39
#घोषणा IPW_CMD_CCX_VER_INFO                 40
#घोषणा IPW_CMD_SET_CALIBRATION              41
#घोषणा IPW_CMD_SENSITIVITY_CALIB            42
#घोषणा IPW_CMD_RETRY_LIMIT                  51
#घोषणा IPW_CMD_IPW_PRE_POWER_DOWN           58
#घोषणा IPW_CMD_VAP_BEACON_TEMPLATE          60
#घोषणा IPW_CMD_VAP_DTIM_PERIOD              61
#घोषणा IPW_CMD_EXT_SUPPORTED_RATES          62
#घोषणा IPW_CMD_VAP_LOCAL_TX_PWR_CONSTRAINT  63
#घोषणा IPW_CMD_VAP_QUIET_INTERVALS          64
#घोषणा IPW_CMD_VAP_CHANNEL_SWITCH           65
#घोषणा IPW_CMD_VAP_MANDATORY_CHANNELS       66
#घोषणा IPW_CMD_VAP_CELL_PWR_LIMIT           67
#घोषणा IPW_CMD_VAP_CF_PARAM_SET             68
#घोषणा IPW_CMD_VAP_SET_BEACONING_STATE      69
#घोषणा IPW_CMD_MEASUREMENT                  80
#घोषणा IPW_CMD_POWER_CAPABILITY             81
#घोषणा IPW_CMD_SUPPORTED_CHANNELS           82
#घोषणा IPW_CMD_TPC_REPORT                   83
#घोषणा IPW_CMD_WME_INFO                     84
#घोषणा IPW_CMD_PRODUCTION_COMMAND	     85
#घोषणा IPW_CMD_LINKSYS_EOU_INFO             90

#घोषणा RFD_SIZE                              4
#घोषणा NUM_TFD_CHUNKS                        6

#घोषणा TX_QUEUE_SIZE                        32
#घोषणा RX_QUEUE_SIZE                        32

#घोषणा DINO_CMD_WEP_KEY                   0x08
#घोषणा DINO_CMD_TX                        0x0B
#घोषणा DCT_ANTENNA_A                      0x01
#घोषणा DCT_ANTENNA_B                      0x02

#घोषणा IPW_A_MODE                         0
#घोषणा IPW_B_MODE                         1
#घोषणा IPW_G_MODE                         2

/*
 * TX Queue Flag Definitions
 */

/* tx wep key definition */
#घोषणा DCT_WEP_KEY_NOT_IMMIDIATE	0x00
#घोषणा DCT_WEP_KEY_64Bit		0x40
#घोषणा DCT_WEP_KEY_128Bit		0x80
#घोषणा DCT_WEP_KEY_128bitIV		0xC0
#घोषणा DCT_WEP_KEY_SIZE_MASK		0xC0

#घोषणा DCT_WEP_KEY_INDEX_MASK		0x0F
#घोषणा DCT_WEP_INDEX_USE_IMMEDIATE	0x20

/* पात attempt अगर mgmt frame is rx'd */
#घोषणा DCT_FLAG_ABORT_MGMT                0x01

/* require CTS */
#घोषणा DCT_FLAG_CTS_REQUIRED              0x02

/* use लघु preamble */
#घोषणा DCT_FLAG_LONG_PREAMBLE             0x00
#घोषणा DCT_FLAG_SHORT_PREAMBLE            0x04

/* RTS/CTS first */
#घोषणा DCT_FLAG_RTS_REQD                  0x08

/* करोnt calculate duration field */
#घोषणा DCT_FLAG_DUR_SET                   0x10

/* even अगर MAC WEP set (allows pre-encrypt) */
#घोषणा DCT_FLAG_NO_WEP              0x20

/* overग_लिखो TSF field */
#घोषणा DCT_FLAG_TSF_REQD                  0x40

/* ACK rx is expected to follow */
#घोषणा DCT_FLAG_ACK_REQD                  0x80

/* TX flags extension */
#घोषणा DCT_FLAG_EXT_MODE_CCK  0x01
#घोषणा DCT_FLAG_EXT_MODE_OFDM 0x00

#घोषणा DCT_FLAG_EXT_SECURITY_WEP     0x00
#घोषणा DCT_FLAG_EXT_SECURITY_NO      DCT_FLAG_EXT_SECURITY_WEP
#घोषणा DCT_FLAG_EXT_SECURITY_CKIP    0x04
#घोषणा DCT_FLAG_EXT_SECURITY_CCM     0x08
#घोषणा DCT_FLAG_EXT_SECURITY_TKIP    0x0C
#घोषणा DCT_FLAG_EXT_SECURITY_MASK    0x0C

#घोषणा DCT_FLAG_EXT_QOS_ENABLED      0x10

#घोषणा DCT_FLAG_EXT_HC_NO_SIFS_PIFS  0x00
#घोषणा DCT_FLAG_EXT_HC_SIFS          0x20
#घोषणा DCT_FLAG_EXT_HC_PIFS          0x40

#घोषणा TX_RX_TYPE_MASK                    0xFF
#घोषणा TX_FRAME_TYPE                      0x00
#घोषणा TX_HOST_COMMAND_TYPE               0x01
#घोषणा RX_FRAME_TYPE                      0x09
#घोषणा RX_HOST_NOTIFICATION_TYPE          0x03
#घोषणा RX_HOST_CMD_RESPONSE_TYPE          0x04
#घोषणा RX_TX_FRAME_RESPONSE_TYPE          0x05
#घोषणा TFD_NEED_IRQ_MASK                  0x04

#घोषणा HOST_CMD_DINO_CONFIG               30

#घोषणा HOST_NOTIFICATION_STATUS_ASSOCIATED             10
#घोषणा HOST_NOTIFICATION_STATUS_AUTHENTICATE           11
#घोषणा HOST_NOTIFICATION_STATUS_SCAN_CHANNEL_RESULT    12
#घोषणा HOST_NOTIFICATION_STATUS_SCAN_COMPLETED         13
#घोषणा HOST_NOTIFICATION_STATUS_FRAG_LENGTH            14
#घोषणा HOST_NOTIFICATION_STATUS_LINK_DETERIORATION     15
#घोषणा HOST_NOTIFICATION_DINO_CONFIG_RESPONSE          16
#घोषणा HOST_NOTIFICATION_STATUS_BEACON_STATE           17
#घोषणा HOST_NOTIFICATION_STATUS_TGI_TX_KEY             18
#घोषणा HOST_NOTIFICATION_TX_STATUS                     19
#घोषणा HOST_NOTIFICATION_CALIB_KEEP_RESULTS            20
#घोषणा HOST_NOTIFICATION_MEASUREMENT_STARTED           21
#घोषणा HOST_NOTIFICATION_MEASUREMENT_ENDED             22
#घोषणा HOST_NOTIFICATION_CHANNEL_SWITCHED              23
#घोषणा HOST_NOTIFICATION_RX_DURING_QUIET_PERIOD        24
#घोषणा HOST_NOTIFICATION_NOISE_STATS			25
#घोषणा HOST_NOTIFICATION_S36_MEASUREMENT_ACCEPTED      30
#घोषणा HOST_NOTIFICATION_S36_MEASUREMENT_REFUSED       31

#घोषणा HOST_NOTIFICATION_STATUS_BEACON_MISSING         1
#घोषणा IPW_MB_SCAN_CANCEL_THRESHOLD                    3
#घोषणा IPW_MB_ROAMING_THRESHOLD_MIN                    1
#घोषणा IPW_MB_ROAMING_THRESHOLD_DEFAULT                8
#घोषणा IPW_MB_ROAMING_THRESHOLD_MAX                    30
#घोषणा IPW_MB_DISASSOCIATE_THRESHOLD_DEFAULT           3*IPW_MB_ROAMING_THRESHOLD_DEFAULT
#घोषणा IPW_REAL_RATE_RX_PACKET_THRESHOLD               300

#घोषणा MACADRR_BYTE_LEN                     6

#घोषणा DCR_TYPE_AP                       0x01
#घोषणा DCR_TYPE_WLAP                     0x02
#घोषणा DCR_TYPE_MU_ESS                   0x03
#घोषणा DCR_TYPE_MU_IBSS                  0x04
#घोषणा DCR_TYPE_MU_PIBSS                 0x05
#घोषणा DCR_TYPE_SNIFFER                  0x06
#घोषणा DCR_TYPE_MU_BSS        DCR_TYPE_MU_ESS

/* QoS  definitions */

#घोषणा CW_MIN_OFDM          15
#घोषणा CW_MAX_OFDM          1023
#घोषणा CW_MIN_CCK           31
#घोषणा CW_MAX_CCK           1023

#घोषणा QOS_TX0_CW_MIN_OFDM      cpu_to_le16(CW_MIN_OFDM)
#घोषणा QOS_TX1_CW_MIN_OFDM      cpu_to_le16(CW_MIN_OFDM)
#घोषणा QOS_TX2_CW_MIN_OFDM      cpu_to_le16((CW_MIN_OFDM + 1)/2 - 1)
#घोषणा QOS_TX3_CW_MIN_OFDM      cpu_to_le16((CW_MIN_OFDM + 1)/4 - 1)

#घोषणा QOS_TX0_CW_MIN_CCK       cpu_to_le16(CW_MIN_CCK)
#घोषणा QOS_TX1_CW_MIN_CCK       cpu_to_le16(CW_MIN_CCK)
#घोषणा QOS_TX2_CW_MIN_CCK       cpu_to_le16((CW_MIN_CCK + 1)/2 - 1)
#घोषणा QOS_TX3_CW_MIN_CCK       cpu_to_le16((CW_MIN_CCK + 1)/4 - 1)

#घोषणा QOS_TX0_CW_MAX_OFDM      cpu_to_le16(CW_MAX_OFDM)
#घोषणा QOS_TX1_CW_MAX_OFDM      cpu_to_le16(CW_MAX_OFDM)
#घोषणा QOS_TX2_CW_MAX_OFDM      cpu_to_le16(CW_MIN_OFDM)
#घोषणा QOS_TX3_CW_MAX_OFDM      cpu_to_le16((CW_MIN_OFDM + 1)/2 - 1)

#घोषणा QOS_TX0_CW_MAX_CCK       cpu_to_le16(CW_MAX_CCK)
#घोषणा QOS_TX1_CW_MAX_CCK       cpu_to_le16(CW_MAX_CCK)
#घोषणा QOS_TX2_CW_MAX_CCK       cpu_to_le16(CW_MIN_CCK)
#घोषणा QOS_TX3_CW_MAX_CCK       cpu_to_le16((CW_MIN_CCK + 1)/2 - 1)

#घोषणा QOS_TX0_AIFS            (3 - QOS_AIFSN_MIN_VALUE)
#घोषणा QOS_TX1_AIFS            (7 - QOS_AIFSN_MIN_VALUE)
#घोषणा QOS_TX2_AIFS            (2 - QOS_AIFSN_MIN_VALUE)
#घोषणा QOS_TX3_AIFS            (2 - QOS_AIFSN_MIN_VALUE)

#घोषणा QOS_TX0_ACM             0
#घोषणा QOS_TX1_ACM             0
#घोषणा QOS_TX2_ACM             0
#घोषणा QOS_TX3_ACM             0

#घोषणा QOS_TX0_TXOP_LIMIT_CCK          0
#घोषणा QOS_TX1_TXOP_LIMIT_CCK          0
#घोषणा QOS_TX2_TXOP_LIMIT_CCK          cpu_to_le16(6016)
#घोषणा QOS_TX3_TXOP_LIMIT_CCK          cpu_to_le16(3264)

#घोषणा QOS_TX0_TXOP_LIMIT_OFDM      0
#घोषणा QOS_TX1_TXOP_LIMIT_OFDM      0
#घोषणा QOS_TX2_TXOP_LIMIT_OFDM      cpu_to_le16(3008)
#घोषणा QOS_TX3_TXOP_LIMIT_OFDM      cpu_to_le16(1504)

#घोषणा DEF_TX0_CW_MIN_OFDM      cpu_to_le16(CW_MIN_OFDM)
#घोषणा DEF_TX1_CW_MIN_OFDM      cpu_to_le16(CW_MIN_OFDM)
#घोषणा DEF_TX2_CW_MIN_OFDM      cpu_to_le16(CW_MIN_OFDM)
#घोषणा DEF_TX3_CW_MIN_OFDM      cpu_to_le16(CW_MIN_OFDM)

#घोषणा DEF_TX0_CW_MIN_CCK       cpu_to_le16(CW_MIN_CCK)
#घोषणा DEF_TX1_CW_MIN_CCK       cpu_to_le16(CW_MIN_CCK)
#घोषणा DEF_TX2_CW_MIN_CCK       cpu_to_le16(CW_MIN_CCK)
#घोषणा DEF_TX3_CW_MIN_CCK       cpu_to_le16(CW_MIN_CCK)

#घोषणा DEF_TX0_CW_MAX_OFDM      cpu_to_le16(CW_MAX_OFDM)
#घोषणा DEF_TX1_CW_MAX_OFDM      cpu_to_le16(CW_MAX_OFDM)
#घोषणा DEF_TX2_CW_MAX_OFDM      cpu_to_le16(CW_MAX_OFDM)
#घोषणा DEF_TX3_CW_MAX_OFDM      cpu_to_le16(CW_MAX_OFDM)

#घोषणा DEF_TX0_CW_MAX_CCK       cpu_to_le16(CW_MAX_CCK)
#घोषणा DEF_TX1_CW_MAX_CCK       cpu_to_le16(CW_MAX_CCK)
#घोषणा DEF_TX2_CW_MAX_CCK       cpu_to_le16(CW_MAX_CCK)
#घोषणा DEF_TX3_CW_MAX_CCK       cpu_to_le16(CW_MAX_CCK)

#घोषणा DEF_TX0_AIFS            0
#घोषणा DEF_TX1_AIFS            0
#घोषणा DEF_TX2_AIFS            0
#घोषणा DEF_TX3_AIFS            0

#घोषणा DEF_TX0_ACM             0
#घोषणा DEF_TX1_ACM             0
#घोषणा DEF_TX2_ACM             0
#घोषणा DEF_TX3_ACM             0

#घोषणा DEF_TX0_TXOP_LIMIT_CCK        0
#घोषणा DEF_TX1_TXOP_LIMIT_CCK        0
#घोषणा DEF_TX2_TXOP_LIMIT_CCK        0
#घोषणा DEF_TX3_TXOP_LIMIT_CCK        0

#घोषणा DEF_TX0_TXOP_LIMIT_OFDM       0
#घोषणा DEF_TX1_TXOP_LIMIT_OFDM       0
#घोषणा DEF_TX2_TXOP_LIMIT_OFDM       0
#घोषणा DEF_TX3_TXOP_LIMIT_OFDM       0

#घोषणा QOS_QOS_SETS                  3
#घोषणा QOS_PARAM_SET_ACTIVE          0
#घोषणा QOS_PARAM_SET_DEF_CCK         1
#घोषणा QOS_PARAM_SET_DEF_OFDM        2

#घोषणा CTRL_QOS_NO_ACK               (0x0020)

#घोषणा IPW_TX_QUEUE_1        1
#घोषणा IPW_TX_QUEUE_2        2
#घोषणा IPW_TX_QUEUE_3        3
#घोषणा IPW_TX_QUEUE_4        4

/* QoS sturctures */
काष्ठा ipw_qos_info अणु
	पूर्णांक qos_enable;
	काष्ठा libipw_qos_parameters *def_qos_parm_OFDM;
	काष्ठा libipw_qos_parameters *def_qos_parm_CCK;
	u32 burst_duration_CCK;
	u32 burst_duration_OFDM;
	u16 qos_no_ack_mask;
	पूर्णांक burst_enable;
पूर्ण;

/**************************************************************/
/**
 * Generic queue काष्ठाure
 *
 * Contains common data क्रम Rx and Tx queues
 */
काष्ठा clx2_queue अणु
	पूर्णांक n_bd;		       /**< number of BDs in this queue */
	पूर्णांक first_empty;	       /**< 1-st empty entry (index) */
	पूर्णांक last_used;		       /**< last used entry (index) */
	u32 reg_w;		     /**< 'write' reg (queue head), addr in करोमुख्य 1 */
	u32 reg_r;		     /**< 'read' reg (queue tail), addr in करोमुख्य 1 */
	dma_addr_t dma_addr;		/**< physical addr क्रम BD's */
	पूर्णांक low_mark;		       /**< low watermark, resume queue अगर मुक्त space more than this */
	पूर्णांक high_mark;		       /**< high watermark, stop queue अगर मुक्त space less than this */
पूर्ण __packed; /* XXX */

काष्ठा machdr32 अणु
	__le16 frame_ctl;
	__le16 duration;		// watch out क्रम endians!
	u8 addr1[MACADRR_BYTE_LEN];
	u8 addr2[MACADRR_BYTE_LEN];
	u8 addr3[MACADRR_BYTE_LEN];
	__le16 seq_ctrl;		// more endians!
	u8 addr4[MACADRR_BYTE_LEN];
	__le16 qos_ctrl;
पूर्ण __packed;

काष्ठा machdr30 अणु
	__le16 frame_ctl;
	__le16 duration;		// watch out क्रम endians!
	u8 addr1[MACADRR_BYTE_LEN];
	u8 addr2[MACADRR_BYTE_LEN];
	u8 addr3[MACADRR_BYTE_LEN];
	__le16 seq_ctrl;		// more endians!
	u8 addr4[MACADRR_BYTE_LEN];
पूर्ण __packed;

काष्ठा machdr26 अणु
	__le16 frame_ctl;
	__le16 duration;		// watch out क्रम endians!
	u8 addr1[MACADRR_BYTE_LEN];
	u8 addr2[MACADRR_BYTE_LEN];
	u8 addr3[MACADRR_BYTE_LEN];
	__le16 seq_ctrl;		// more endians!
	__le16 qos_ctrl;
पूर्ण __packed;

काष्ठा machdr24 अणु
	__le16 frame_ctl;
	__le16 duration;		// watch out क्रम endians!
	u8 addr1[MACADRR_BYTE_LEN];
	u8 addr2[MACADRR_BYTE_LEN];
	u8 addr3[MACADRR_BYTE_LEN];
	__le16 seq_ctrl;		// more endians!
पूर्ण __packed;

// TX TFD with 32 byte MAC Header
काष्ठा tx_tfd_32 अणु
	काष्ठा machdr32 mchdr;	// 32
	__le32 uivplaceholder[2];	// 8
पूर्ण __packed;

// TX TFD with 30 byte MAC Header
काष्ठा tx_tfd_30 अणु
	काष्ठा machdr30 mchdr;	// 30
	u8 reserved[2];		// 2
	__le32 uivplaceholder[2];	// 8
पूर्ण __packed;

// tx tfd with 26 byte mac header
काष्ठा tx_tfd_26 अणु
	काष्ठा machdr26 mchdr;	// 26
	u8 reserved1[2];	// 2
	__le32 uivplaceholder[2];	// 8
	u8 reserved2[4];	// 4
पूर्ण __packed;

// tx tfd with 24 byte mac header
काष्ठा tx_tfd_24 अणु
	काष्ठा machdr24 mchdr;	// 24
	__le32 uivplaceholder[2];	// 8
	u8 reserved[8];		// 8
पूर्ण __packed;

#घोषणा DCT_WEP_KEY_FIELD_LENGTH 16

काष्ठा tfd_command अणु
	u8 index;
	u8 length;
	__le16 reserved;
	u8 payload[];
पूर्ण __packed;

काष्ठा tfd_data अणु
	/* Header */
	__le32 work_area_ptr;
	u8 station_number;	/* 0 क्रम BSS */
	u8 reserved1;
	__le16 reserved2;

	/* Tx Parameters */
	u8 cmd_id;
	u8 seq_num;
	__le16 len;
	u8 priority;
	u8 tx_flags;
	u8 tx_flags_ext;
	u8 key_index;
	u8 wepkey[DCT_WEP_KEY_FIELD_LENGTH];
	u8 rate;
	u8 antenna;
	__le16 next_packet_duration;
	__le16 next_frag_len;
	__le16 back_off_counter;	//////txop;
	u8 retrylimit;
	__le16 cwcurrent;
	u8 reserved3;

	/* 802.11 MAC Header */
	जोड़ अणु
		काष्ठा tx_tfd_24 tfd_24;
		काष्ठा tx_tfd_26 tfd_26;
		काष्ठा tx_tfd_30 tfd_30;
		काष्ठा tx_tfd_32 tfd_32;
	पूर्ण tfd;

	/* Payload DMA info */
	__le32 num_chunks;
	__le32 chunk_ptr[NUM_TFD_CHUNKS];
	__le16 chunk_len[NUM_TFD_CHUNKS];
पूर्ण __packed;

काष्ठा txrx_control_flags अणु
	u8 message_type;
	u8 rx_seq_num;
	u8 control_bits;
	u8 reserved;
पूर्ण __packed;

#घोषणा  TFD_SIZE                           128
#घोषणा  TFD_CMD_IMMEDIATE_PAYLOAD_LENGTH   (TFD_SIZE - माप(काष्ठा txrx_control_flags))

काष्ठा tfd_frame अणु
	काष्ठा txrx_control_flags control_flags;
	जोड़ अणु
		काष्ठा tfd_data data;
		काष्ठा tfd_command cmd;
		u8 raw[TFD_CMD_IMMEDIATE_PAYLOAD_LENGTH];
	पूर्ण u;
पूर्ण __packed;

प्रकार व्योम deकाष्ठाor_func(स्थिर व्योम *);

/**
 * Tx Queue क्रम DMA. Queue consists of circular buffer of
 * BD's and required locking काष्ठाures.
 */
काष्ठा clx2_tx_queue अणु
	काष्ठा clx2_queue q;
	काष्ठा tfd_frame *bd;
	काष्ठा libipw_txb **txb;
पूर्ण;

/*
 * RX related काष्ठाures and functions
 */
#घोषणा RX_FREE_BUFFERS 32
#घोषणा RX_LOW_WATERMARK 8

#घोषणा SUP_RATE_11A_MAX_NUM_CHANNELS  8
#घोषणा SUP_RATE_11B_MAX_NUM_CHANNELS  4
#घोषणा SUP_RATE_11G_MAX_NUM_CHANNELS  12

// Used क्रम passing to driver number of successes and failures per rate
काष्ठा rate_histogram अणु
	जोड़ अणु
		__le32 a[SUP_RATE_11A_MAX_NUM_CHANNELS];
		__le32 b[SUP_RATE_11B_MAX_NUM_CHANNELS];
		__le32 g[SUP_RATE_11G_MAX_NUM_CHANNELS];
	पूर्ण success;
	जोड़ अणु
		__le32 a[SUP_RATE_11A_MAX_NUM_CHANNELS];
		__le32 b[SUP_RATE_11B_MAX_NUM_CHANNELS];
		__le32 g[SUP_RATE_11G_MAX_NUM_CHANNELS];
	पूर्ण failed;
पूर्ण __packed;

/* statistics command response */
काष्ठा ipw_cmd_stats अणु
	u8 cmd_id;
	u8 seq_num;
	__le16 good_sfd;
	__le16 bad_plcp;
	__le16 wrong_bssid;
	__le16 valid_mpdu;
	__le16 bad_mac_header;
	__le16 reserved_frame_types;
	__le16 rx_ina;
	__le16 bad_crc32;
	__le16 invalid_cts;
	__le16 invalid_acks;
	__le16 दीर्घ_distance_ina_fina;
	__le16 dsp_silence_unreachable;
	__le16 accumulated_rssi;
	__le16 rx_ovfl_frame_tossed;
	__le16 rssi_silence_threshold;
	__le16 rx_ovfl_frame_supplied;
	__le16 last_rx_frame_संकेत;
	__le16 last_rx_frame_noise;
	__le16 rx_स्वतःdetec_no_ofdm;
	__le16 rx_स्वतःdetec_no_barker;
	__le16 reserved;
पूर्ण __packed;

काष्ठा notअगर_channel_result अणु
	u8 channel_num;
	काष्ठा ipw_cmd_stats stats;
	u8 uReserved;
पूर्ण __packed;

#घोषणा SCAN_COMPLETED_STATUS_COMPLETE  1
#घोषणा SCAN_COMPLETED_STATUS_ABORTED   2

काष्ठा notअगर_scan_complete अणु
	u8 scan_type;
	u8 num_channels;
	u8 status;
	u8 reserved;
पूर्ण __packed;

काष्ठा notअगर_frag_length अणु
	__le16 frag_length;
	__le16 reserved;
पूर्ण __packed;

काष्ठा notअगर_beacon_state अणु
	__le32 state;
	__le32 number;
पूर्ण __packed;

काष्ठा notअगर_tgi_tx_key अणु
	u8 key_state;
	u8 security_type;
	u8 station_index;
	u8 reserved;
पूर्ण __packed;

#घोषणा SILENCE_OVER_THRESH (1)
#घोषणा SILENCE_UNDER_THRESH (2)

काष्ठा notअगर_link_deterioration अणु
	काष्ठा ipw_cmd_stats stats;
	u8 rate;
	u8 modulation;
	काष्ठा rate_histogram histogram;
	u8 silence_notअगरication_type;	/* SILENCE_OVER/UNDER_THRESH */
	__le16 silence_count;
पूर्ण __packed;

काष्ठा notअगर_association अणु
	u8 state;
पूर्ण __packed;

काष्ठा notअगर_authenticate अणु
	u8 state;
	काष्ठा machdr24 addr;
	__le16 status;
पूर्ण __packed;

काष्ठा notअगर_calibration अणु
	u8 data[104];
पूर्ण __packed;

काष्ठा notअगर_noise अणु
	__le32 value;
पूर्ण __packed;

काष्ठा ipw_rx_notअगरication अणु
	u8 reserved[8];
	u8 subtype;
	u8 flags;
	__le16 size;
	जोड़ अणु
		काष्ठा notअगर_association assoc;
		काष्ठा notअगर_authenticate auth;
		काष्ठा notअगर_channel_result channel_result;
		काष्ठा notअगर_scan_complete scan_complete;
		काष्ठा notअगर_frag_length frag_len;
		काष्ठा notअगर_beacon_state beacon_state;
		काष्ठा notअगर_tgi_tx_key tgi_tx_key;
		काष्ठा notअगर_link_deterioration link_deterioration;
		काष्ठा notअगर_calibration calibration;
		काष्ठा notअगर_noise noise;
		u8 raw[0];
	पूर्ण u;
पूर्ण __packed;

काष्ठा ipw_rx_frame अणु
	__le32 reserved1;
	u8 parent_tsf[4];	// fw_use[0] is boolean क्रम OUR_TSF_IS_GREATER
	u8 received_channel;	// The channel that this frame was received on.
	// Note that क्रम .11b this करोes not have to be
	// the same as the channel that it was sent.
	// Filled by LMAC
	u8 frameStatus;
	u8 rate;
	u8 rssi;
	u8 agc;
	u8 rssi_dbm;
	__le16 संकेत;
	__le16 noise;
	u8 antennaAndPhy;
	u8 control;		// control bit should be on in bg
	u8 rtscts_rate;		// rate of rts or cts (in rts cts sequence rate
	// is identical)
	u8 rtscts_seen;		// 0x1 RTS seen ; 0x2 CTS seen
	__le16 length;
	u8 data[];
पूर्ण __packed;

काष्ठा ipw_rx_header अणु
	u8 message_type;
	u8 rx_seq_num;
	u8 control_bits;
	u8 reserved;
पूर्ण __packed;

काष्ठा ipw_rx_packet अणु
	काष्ठा ipw_rx_header header;
	जोड़ अणु
		काष्ठा ipw_rx_frame frame;
		काष्ठा ipw_rx_notअगरication notअगरication;
	पूर्ण u;
पूर्ण __packed;

#घोषणा IPW_RX_NOTIFICATION_SIZE माप(काष्ठा ipw_rx_header) + 12
#घोषणा IPW_RX_FRAME_SIZE        (अचिन्हित पूर्णांक)(माप(काष्ठा ipw_rx_header) + \
                                 माप(काष्ठा ipw_rx_frame))

काष्ठा ipw_rx_mem_buffer अणु
	dma_addr_t dma_addr;
	काष्ठा sk_buff *skb;
	काष्ठा list_head list;
पूर्ण;				/* Not transferred over network, so not  __packed */

काष्ठा ipw_rx_queue अणु
	काष्ठा ipw_rx_mem_buffer pool[RX_QUEUE_SIZE + RX_FREE_BUFFERS];
	काष्ठा ipw_rx_mem_buffer *queue[RX_QUEUE_SIZE];
	u32 processed;		/* Internal index to last handled Rx packet */
	u32 पढ़ो;		/* Shared index to newest available Rx buffer */
	u32 ग_लिखो;		/* Shared index to oldest written Rx packet */
	u32 मुक्त_count;		/* Number of pre-allocated buffers in rx_मुक्त */
	/* Each of these lists is used as a FIFO क्रम ipw_rx_mem_buffers */
	काष्ठा list_head rx_मुक्त;	/* Own an SKBs */
	काष्ठा list_head rx_used;	/* No SKB allocated */
	spinlock_t lock;
पूर्ण;				/* Not transferred over network, so not  __packed */

काष्ठा alive_command_responce अणु
	u8 alive_command;
	u8 sequence_number;
	__le16 software_revision;
	u8 device_identअगरier;
	u8 reserved1[5];
	__le16 reserved2;
	__le16 reserved3;
	__le16 घड़ी_settle_समय;
	__le16 घातerup_settle_समय;
	__le16 reserved4;
	u8 समय_stamp[5];	/* month, day, year, hours, minutes */
	u8 ucode_valid;
पूर्ण __packed;

#घोषणा IPW_MAX_RATES 12

काष्ठा ipw_rates अणु
	u8 num_rates;
	u8 rates[IPW_MAX_RATES];
पूर्ण __packed;

काष्ठा command_block अणु
	अचिन्हित पूर्णांक control;
	u32 source_addr;
	u32 dest_addr;
	अचिन्हित पूर्णांक status;
पूर्ण __packed;

#घोषणा CB_NUMBER_OF_ELEMENTS_SMALL 64
काष्ठा fw_image_desc अणु
	अचिन्हित दीर्घ last_cb_index;
	अचिन्हित दीर्घ current_cb_index;
	काष्ठा command_block cb_list[CB_NUMBER_OF_ELEMENTS_SMALL];
	व्योम *v_addr;
	अचिन्हित दीर्घ p_addr;
	अचिन्हित दीर्घ len;
पूर्ण;

काष्ठा ipw_sys_config अणु
	u8 bt_coexistence;
	u8 reserved1;
	u8 answer_broadcast_ssid_probe;
	u8 accept_all_data_frames;
	u8 accept_non_directed_frames;
	u8 exclude_unicast_unencrypted;
	u8 disable_unicast_decryption;
	u8 exclude_multicast_unencrypted;
	u8 disable_multicast_decryption;
	u8 antenna_भागersity;
	u8 pass_crc_to_host;
	u8 करोt11g_स्वतः_detection;
	u8 enable_cts_to_self;
	u8 enable_multicast_filtering;
	u8 bt_coexist_collision_thr;
	u8 silence_threshold;
	u8 accept_all_mgmt_bcpr;
	u8 accept_all_mgmt_frames;
	u8 pass_noise_stats_to_host;
	u8 reserved3;
पूर्ण __packed;

काष्ठा ipw_multicast_addr अणु
	u8 num_of_multicast_addresses;
	u8 reserved[3];
	u8 mac1[6];
	u8 mac2[6];
	u8 mac3[6];
	u8 mac4[6];
पूर्ण __packed;

#घोषणा DCW_WEP_KEY_INDEX_MASK		0x03	/* bits [0:1] */
#घोषणा DCW_WEP_KEY_SEC_TYPE_MASK	0x30	/* bits [4:5] */

#घोषणा DCW_WEP_KEY_SEC_TYPE_WEP	0x00
#घोषणा DCW_WEP_KEY_SEC_TYPE_CCM	0x20
#घोषणा DCW_WEP_KEY_SEC_TYPE_TKIP	0x30

#घोषणा DCW_WEP_KEY_INVALID_SIZE	0x00	/* 0 = Invalid key */
#घोषणा DCW_WEP_KEY64Bit_SIZE		0x05	/* 64-bit encryption */
#घोषणा DCW_WEP_KEY128Bit_SIZE		0x0D	/* 128-bit encryption */
#घोषणा DCW_CCM_KEY128Bit_SIZE		0x10	/* 128-bit key */
//#घोषणा DCW_WEP_KEY128BitIV_SIZE      0x10    /* 128-bit key and 128-bit IV */

काष्ठा ipw_wep_key अणु
	u8 cmd_id;
	u8 seq_num;
	u8 key_index;
	u8 key_size;
	u8 key[16];
पूर्ण __packed;

काष्ठा ipw_tgi_tx_key अणु
	u8 key_id;
	u8 security_type;
	u8 station_index;
	u8 flags;
	u8 key[16];
	__le32 tx_counter[2];
पूर्ण __packed;

#घोषणा IPW_SCAN_CHANNELS 54

काष्ठा ipw_scan_request अणु
	u8 scan_type;
	__le16 dwell_समय;
	u8 channels_list[IPW_SCAN_CHANNELS];
	u8 channels_reserved[3];
पूर्ण __packed;

क्रमागत अणु
	IPW_SCAN_PASSIVE_TILL_FIRST_BEACON_SCAN = 0,
	IPW_SCAN_PASSIVE_FULL_DWELL_SCAN,
	IPW_SCAN_ACTIVE_सूचीECT_SCAN,
	IPW_SCAN_ACTIVE_BROADCAST_SCAN,
	IPW_SCAN_ACTIVE_BROADCAST_AND_सूचीECT_SCAN,
	IPW_SCAN_TYPES
पूर्ण;

काष्ठा ipw_scan_request_ext अणु
	__le32 full_scan_index;
	u8 channels_list[IPW_SCAN_CHANNELS];
	u8 scan_type[IPW_SCAN_CHANNELS / 2];
	u8 reserved;
	__le16 dwell_समय[IPW_SCAN_TYPES];
पूर्ण __packed;

अटल अंतरभूत u8 ipw_get_scan_type(काष्ठा ipw_scan_request_ext *scan, u8 index)
अणु
	अगर (index % 2)
		वापस scan->scan_type[index / 2] & 0x0F;
	अन्यथा
		वापस (scan->scan_type[index / 2] & 0xF0) >> 4;
पूर्ण

अटल अंतरभूत व्योम ipw_set_scan_type(काष्ठा ipw_scan_request_ext *scan,
				     u8 index, u8 scan_type)
अणु
	अगर (index % 2)
		scan->scan_type[index / 2] =
		    (scan->scan_type[index / 2] & 0xF0) | (scan_type & 0x0F);
	अन्यथा
		scan->scan_type[index / 2] =
		    (scan->scan_type[index / 2] & 0x0F) |
		    ((scan_type & 0x0F) << 4);
पूर्ण

काष्ठा ipw_associate अणु
	u8 channel;
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
	u8 auth_type:4, auth_key:4;
#अन्यथा
	u8 auth_key:4, auth_type:4;
#पूर्ण_अगर
	u8 assoc_type;
	u8 reserved;
	__le16 policy_support;
	u8 preamble_length;
	u8 ieee_mode;
	u8 bssid[ETH_ALEN];
	__le32 assoc_tsf_msw;
	__le32 assoc_tsf_lsw;
	__le16 capability;
	__le16 listen_पूर्णांकerval;
	__le16 beacon_पूर्णांकerval;
	u8 dest[ETH_ALEN];
	__le16 atim_winकरोw;
	u8 smr;
	u8 reserved1;
	__le16 reserved2;
पूर्ण __packed;

काष्ठा ipw_supported_rates अणु
	u8 ieee_mode;
	u8 num_rates;
	u8 purpose;
	u8 reserved;
	u8 supported_rates[IPW_MAX_RATES];
पूर्ण __packed;

काष्ठा ipw_rts_threshold अणु
	__le16 rts_threshold;
	__le16 reserved;
पूर्ण __packed;

काष्ठा ipw_frag_threshold अणु
	__le16 frag_threshold;
	__le16 reserved;
पूर्ण __packed;

काष्ठा ipw_retry_limit अणु
	u8 लघु_retry_limit;
	u8 दीर्घ_retry_limit;
	__le16 reserved;
पूर्ण __packed;

काष्ठा ipw_dino_config अणु
	__le32 dino_config_addr;
	__le16 dino_config_size;
	u8 dino_response;
	u8 reserved;
पूर्ण __packed;

काष्ठा ipw_aironet_info अणु
	u8 id;
	u8 length;
	__le16 reserved;
पूर्ण __packed;

काष्ठा ipw_rx_key अणु
	u8 station_index;
	u8 key_type;
	u8 key_id;
	u8 key_flag;
	u8 key[16];
	u8 station_address[6];
	u8 key_index;
	u8 reserved;
पूर्ण __packed;

काष्ठा ipw_country_channel_info अणु
	u8 first_channel;
	u8 no_channels;
	s8 max_tx_घातer;
पूर्ण __packed;

काष्ठा ipw_country_info अणु
	u8 id;
	u8 length;
	u8 country_str[IEEE80211_COUNTRY_STRING_LEN];
	काष्ठा ipw_country_channel_info groups[7];
पूर्ण __packed;

काष्ठा ipw_channel_tx_घातer अणु
	u8 channel_number;
	s8 tx_घातer;
पूर्ण __packed;

#घोषणा SCAN_ASSOCIATED_INTERVAL (HZ)
#घोषणा SCAN_INTERVAL (HZ / 10)
#घोषणा MAX_A_CHANNELS  37
#घोषणा MAX_B_CHANNELS  14

काष्ठा ipw_tx_घातer अणु
	u8 num_channels;
	u8 ieee_mode;
	काष्ठा ipw_channel_tx_घातer channels_tx_घातer[MAX_A_CHANNELS];
पूर्ण __packed;

काष्ठा ipw_rsn_capabilities अणु
	u8 id;
	u8 length;
	__le16 version;
पूर्ण __packed;

काष्ठा ipw_sensitivity_calib अणु
	__le16 beacon_rssi_raw;
	__le16 reserved;
पूर्ण __packed;

/**
 * Host command काष्ठाure.
 *
 * On input, the following fields should be filled:
 * - cmd
 * - len
 * - status_len
 * - param (अगर needed)
 *
 * On output,
 * - \च status contains status;
 * - \च param filled with status parameters.
 */
काष्ठा ipw_cmd अणु	 /* XXX */
	u32 cmd;   /**< Host command */
	u32 status;/**< Status */
	u32 status_len;
		   /**< How many 32 bit parameters in the status */
	u32 len;   /**< incoming parameters length, bytes */
  /**
   * command parameters.
   * There should be enough space क्रम incoming and
   * outcoming parameters.
   * Incoming parameters listed 1-st, followed by outcoming params.
   * nParams=(len+3)/4+status_len
   */
	u32 param[];
पूर्ण __packed;

#घोषणा STATUS_HCMD_ACTIVE      (1<<0)	/**< host command in progress */

#घोषणा STATUS_INT_ENABLED      (1<<1)
#घोषणा STATUS_RF_KILL_HW       (1<<2)
#घोषणा STATUS_RF_KILL_SW       (1<<3)
#घोषणा STATUS_RF_KILL_MASK     (STATUS_RF_KILL_HW | STATUS_RF_KILL_SW)

#घोषणा STATUS_INIT             (1<<5)
#घोषणा STATUS_AUTH             (1<<6)
#घोषणा STATUS_ASSOCIATED       (1<<7)
#घोषणा STATUS_STATE_MASK       (STATUS_INIT | STATUS_AUTH | STATUS_ASSOCIATED)

#घोषणा STATUS_ASSOCIATING      (1<<8)
#घोषणा STATUS_DISASSOCIATING   (1<<9)
#घोषणा STATUS_ROAMING          (1<<10)
#घोषणा STATUS_EXIT_PENDING     (1<<11)
#घोषणा STATUS_DISASSOC_PENDING (1<<12)
#घोषणा STATUS_STATE_PENDING    (1<<13)

#घोषणा STATUS_सूचीECT_SCAN_PENDING (1<<19)
#घोषणा STATUS_SCAN_PENDING     (1<<20)
#घोषणा STATUS_SCANNING         (1<<21)
#घोषणा STATUS_SCAN_ABORTING    (1<<22)
#घोषणा STATUS_SCAN_FORCED      (1<<23)

#घोषणा STATUS_LED_LINK_ON      (1<<24)
#घोषणा STATUS_LED_ACT_ON       (1<<25)

#घोषणा STATUS_INसूचीECT_BYTE    (1<<28)	/* sysfs entry configured क्रम access */
#घोषणा STATUS_INसूचीECT_DWORD   (1<<29)	/* sysfs entry configured क्रम access */
#घोषणा STATUS_सूचीECT_DWORD     (1<<30)	/* sysfs entry configured क्रम access */

#घोषणा STATUS_SECURITY_UPDATED (1<<31)	/* Security sync needed */

#घोषणा CFG_STATIC_CHANNEL      (1<<0)	/* Restrict assoc. to single channel */
#घोषणा CFG_STATIC_ESSID        (1<<1)	/* Restrict assoc. to single SSID */
#घोषणा CFG_STATIC_BSSID        (1<<2)	/* Restrict assoc. to single BSSID */
#घोषणा CFG_CUSTOM_MAC          (1<<3)
#घोषणा CFG_PREAMBLE_LONG       (1<<4)
#घोषणा CFG_ADHOC_PERSIST       (1<<5)
#घोषणा CFG_ASSOCIATE           (1<<6)
#घोषणा CFG_FIXED_RATE          (1<<7)
#घोषणा CFG_ADHOC_CREATE        (1<<8)
#घोषणा CFG_NO_LED              (1<<9)
#घोषणा CFG_BACKGROUND_SCAN     (1<<10)
#घोषणा CFG_SPEED_SCAN          (1<<11)
#घोषणा CFG_NET_STATS           (1<<12)

#घोषणा CAP_SHARED_KEY          (1<<0)	/* Off = OPEN */
#घोषणा CAP_PRIVACY_ON          (1<<1)	/* Off = No privacy */

#घोषणा MAX_STATIONS            32
#घोषणा IPW_INVALID_STATION     (0xff)

काष्ठा ipw_station_entry अणु
	u8 mac_addr[ETH_ALEN];
	u8 reserved;
	u8 support_mode;
पूर्ण;

#घोषणा AVG_ENTRIES 8
काष्ठा average अणु
	s16 entries[AVG_ENTRIES];
	u8 pos;
	u8 init;
	s32 sum;
पूर्ण;

#घोषणा MAX_SPEED_SCAN 100
#घोषणा IPW_IBSS_MAC_HASH_SIZE 31

काष्ठा ipw_ibss_seq अणु
	u8 mac[ETH_ALEN];
	u16 seq_num;
	u16 frag_num;
	अचिन्हित दीर्घ packet_समय;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ipw_error_elem अणु	 /* XXX */
	u32 desc;
	u32 समय;
	u32 blink1;
	u32 blink2;
	u32 link1;
	u32 link2;
	u32 data;
पूर्ण;

काष्ठा ipw_event अणु	 /* XXX */
	u32 event;
	u32 समय;
	u32 data;
पूर्ण __packed;

काष्ठा ipw_fw_error अणु	 /* XXX */
	अचिन्हित दीर्घ jअगरfies;
	u32 status;
	u32 config;
	u32 elem_len;
	u32 log_len;
	काष्ठा ipw_error_elem *elem;
	काष्ठा ipw_event *log;
	u8 payload[];
पूर्ण __packed;

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS

क्रमागत ipw_prom_filter अणु
	IPW_PROM_CTL_HEADER_ONLY = (1 << 0),
	IPW_PROM_MGMT_HEADER_ONLY = (1 << 1),
	IPW_PROM_DATA_HEADER_ONLY = (1 << 2),
	IPW_PROM_ALL_HEADER_ONLY = 0xf, /* bits 0..3 */
	IPW_PROM_NO_TX = (1 << 4),
	IPW_PROM_NO_RX = (1 << 5),
	IPW_PROM_NO_CTL = (1 << 6),
	IPW_PROM_NO_MGMT = (1 << 7),
	IPW_PROM_NO_DATA = (1 << 8),
पूर्ण;

काष्ठा ipw_priv;
काष्ठा ipw_prom_priv अणु
	काष्ठा ipw_priv *priv;
	काष्ठा libipw_device *ieee;
	क्रमागत ipw_prom_filter filter;
	पूर्णांक tx_packets;
	पूर्णांक rx_packets;
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_IPW2200_RADIOTAP) || defined(CONFIG_IPW2200_PROMISCUOUS)
/* Magic काष्ठा that slots पूर्णांकo the radiotap header -- no reason
 * to build this manually element by element, we can ग_लिखो it much
 * more efficiently than we can parse it. ORDER MATTERS HERE
 *
 * When sent to us via the simulated Rx पूर्णांकerface in sysfs, the entire
 * काष्ठाure is provided regardless of any bits unset.
 */
काष्ठा ipw_rt_hdr अणु
	काष्ठा ieee80211_radiotap_header rt_hdr;
	u64 rt_tsf;      /* TSF */	/* XXX */
	u8 rt_flags;	/* radiotap packet flags */
	u8 rt_rate;	/* rate in 500kb/s */
	__le16 rt_channel;	/* channel in mhz */
	__le16 rt_chbiपंचांगask;	/* channel bitfield */
	s8 rt_dbmसंकेत;	/* संकेत in dbM, kluged to चिन्हित */
	s8 rt_dbmnoise;
	u8 rt_antenna;	/* antenna number */
	u8 payload[];  /* payload... */
पूर्ण __packed;
#पूर्ण_अगर

काष्ठा ipw_priv अणु
	/* ieee device used by generic ieee processing code */
	काष्ठा libipw_device *ieee;

	spinlock_t lock;
	spinlock_t irq_lock;
	काष्ठा mutex mutex;

	/* basic pci-network driver stuff */
	काष्ठा pci_dev *pci_dev;
	काष्ठा net_device *net_dev;

#अगर_घोषित CONFIG_IPW2200_PROMISCUOUS
	/* Promiscuous mode */
	काष्ठा ipw_prom_priv *prom_priv;
	काष्ठा net_device *prom_net_dev;
#पूर्ण_अगर

	/* pci hardware address support */
	व्योम __iomem *hw_base;
	अचिन्हित दीर्घ hw_len;

	काष्ठा fw_image_desc sram_desc;

	/* result of ucode करोwnload */
	काष्ठा alive_command_responce dino_alive;

	रुको_queue_head_t रुको_command_queue;
	रुको_queue_head_t रुको_state;

	/* Rx and Tx DMA processing queues */
	काष्ठा ipw_rx_queue *rxq;
	काष्ठा clx2_tx_queue txq_cmd;
	काष्ठा clx2_tx_queue txq[4];
	u32 status;
	u32 config;
	u32 capability;

	काष्ठा average average_missed_beacons;
	s16 exp_avg_rssi;
	s16 exp_avg_noise;
	u32 port_type;
	पूर्णांक rx_bufs_min;	  /**< minimum number of bufs in Rx queue */
	पूर्णांक rx_pend_max;	  /**< maximum pending buffers क्रम one IRQ */
	u32 hcmd_seq;		  /**< sequence number क्रम hcmd */
	u32 disassociate_threshold;
	u32 roaming_threshold;

	काष्ठा ipw_associate assoc_request;
	काष्ठा libipw_network *assoc_network;

	अचिन्हित दीर्घ ts_scan_पात;
	काष्ठा ipw_supported_rates rates;
	काष्ठा ipw_rates phy[3];	   /**< PHY restrictions, per band */
	काष्ठा ipw_rates supp;		   /**< software defined */
	काष्ठा ipw_rates extended;	   /**< use क्रम corresp. IE, AP only */

	काष्ठा notअगर_link_deterioration last_link_deterioration; /** क्रम statistics */
	काष्ठा ipw_cmd *hcmd; /**< host command currently executed */

	रुको_queue_head_t hcmd_wq;     /**< host command रुकोs क्रम execution */
	u32 tsf_bcn[2];		     /**< TSF from latest beacon */

	काष्ठा notअगर_calibration calib;	/**< last calibration */

	/* ordinal पूर्णांकerface with firmware */
	u32 table0_addr;
	u32 table0_len;
	u32 table1_addr;
	u32 table1_len;
	u32 table2_addr;
	u32 table2_len;

	/* context inक्रमmation */
	u8 essid[IW_ESSID_MAX_SIZE];
	u8 essid_len;
	u8 nick[IW_ESSID_MAX_SIZE];
	u16 rates_mask;
	u8 channel;
	काष्ठा ipw_sys_config sys_config;
	u32 घातer_mode;
	u8 bssid[ETH_ALEN];
	u16 rts_threshold;
	u8 mac_addr[ETH_ALEN];
	u8 num_stations;
	u8 stations[MAX_STATIONS][ETH_ALEN];
	u8 लघु_retry_limit;
	u8 दीर्घ_retry_limit;

	u32 notअगर_missed_beacons;

	/* Statistics and counters normalized with each association */
	u32 last_missed_beacons;
	u32 last_tx_packets;
	u32 last_rx_packets;
	u32 last_tx_failures;
	u32 last_rx_err;
	u32 last_rate;

	u32 missed_adhoc_beacons;
	u32 missed_beacons;
	u32 rx_packets;
	u32 tx_packets;
	u32 quality;

	u8 speed_scan[MAX_SPEED_SCAN];
	u8 speed_scan_pos;

	u16 last_seq_num;
	u16 last_frag_num;
	अचिन्हित दीर्घ last_packet_समय;
	काष्ठा list_head ibss_mac_hash[IPW_IBSS_MAC_HASH_SIZE];

	/* eeprom */
	u8 eeprom[0x100];	/* 256 bytes of eeprom */
	u8 country[4];
	पूर्णांक eeprom_delay;

	काष्ठा iw_statistics wstats;

	काष्ठा iw_खुला_data wireless_data;

	पूर्णांक user_requested_scan;
	u8 direct_scan_ssid[IW_ESSID_MAX_SIZE];
	u8 direct_scan_ssid_len;

	काष्ठा delayed_work adhoc_check;
	काष्ठा work_काष्ठा associate;
	काष्ठा work_काष्ठा disassociate;
	काष्ठा work_काष्ठा प्रणाली_config;
	काष्ठा work_काष्ठा rx_replenish;
	काष्ठा delayed_work request_scan;
	काष्ठा delayed_work request_direct_scan;
	काष्ठा delayed_work request_passive_scan;
	काष्ठा delayed_work scan_event;
	काष्ठा work_काष्ठा adapter_restart;
	काष्ठा delayed_work rf_समाप्त;
	काष्ठा work_काष्ठा up;
	काष्ठा work_काष्ठा करोwn;
	काष्ठा delayed_work gather_stats;
	काष्ठा work_काष्ठा पात_scan;
	काष्ठा work_काष्ठा roam;
	काष्ठा delayed_work scan_check;
	काष्ठा work_काष्ठा link_up;
	काष्ठा work_काष्ठा link_करोwn;

	काष्ठा tasklet_काष्ठा irq_tasklet;

	/* LED related variables and work_काष्ठा */
	u8 nic_type;
	u32 led_activity_on;
	u32 led_activity_off;
	u32 led_association_on;
	u32 led_association_off;
	u32 led_ofdm_on;
	u32 led_ofdm_off;

	काष्ठा delayed_work led_link_on;
	काष्ठा delayed_work led_link_off;
	काष्ठा delayed_work led_act_off;
	काष्ठा work_काष्ठा merge_networks;

	काष्ठा ipw_cmd_log *cmdlog;
	पूर्णांक cmdlog_len;
	पूर्णांक cmdlog_pos;

#घोषणा IPW_2200BG  1
#घोषणा IPW_2915ABG 2
	u8 adapter;

	s8 tx_घातer;

	/* Track समय in suspend using CLOCK_BOOTTIME */
	समय64_t suspend_at;
	समय64_t suspend_समय;

#अगर_घोषित CONFIG_PM
	u32 pm_state[16];
#पूर्ण_अगर

	काष्ठा ipw_fw_error *error;

	/* network state */

	/* Used to pass the current INTA value from ISR to Tasklet */
	u32 isr_पूर्णांकa;

	/* QoS */
	काष्ठा ipw_qos_info qos_data;
	काष्ठा work_काष्ठा qos_activate;
	/*********************************/

	/* debugging info */
	u32 indirect_dword;
	u32 direct_dword;
	u32 indirect_byte;
पूर्ण;				/*ipw_priv */

/* debug macros */

/* Debug and म_लिखो string expansion helpers क्रम prपूर्णांकing bitfields */
#घोषणा BIT_FMT8 "%c%c%c%c-%c%c%c%c"
#घोषणा BIT_FMT16 BIT_FMT8 ":" BIT_FMT8
#घोषणा BIT_FMT32 BIT_FMT16 " " BIT_FMT16

#घोषणा BITC(x,y) (((x>>y)&1)?'1':'0')
#घोषणा BIT_ARG8(x) \
BITC(x,7),BITC(x,6),BITC(x,5),BITC(x,4),\
BITC(x,3),BITC(x,2),BITC(x,1),BITC(x,0)

#घोषणा BIT_ARG16(x) \
BITC(x,15),BITC(x,14),BITC(x,13),BITC(x,12),\
BITC(x,11),BITC(x,10),BITC(x,9),BITC(x,8),\
BIT_ARG8(x)

#घोषणा BIT_ARG32(x) \
BITC(x,31),BITC(x,30),BITC(x,29),BITC(x,28),\
BITC(x,27),BITC(x,26),BITC(x,25),BITC(x,24),\
BITC(x,23),BITC(x,22),BITC(x,21),BITC(x,20),\
BITC(x,19),BITC(x,18),BITC(x,17),BITC(x,16),\
BIT_ARG16(x)


#घोषणा IPW_DEBUG(level, fmt, args...) \
करो अणु अगर (ipw_debug_level & (level)) \
  prपूर्णांकk(KERN_DEBUG DRV_NAME": %s " fmt, __func__ , ## args); पूर्ण जबतक (0)

#अगर_घोषित CONFIG_IPW2200_DEBUG
#घोषणा IPW_LL_DEBUG(level, fmt, args...) \
करो अणु अगर (ipw_debug_level & (level)) \
  prपूर्णांकk(KERN_DEBUG DRV_NAME": %s " fmt, __func__ , ## args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा IPW_LL_DEBUG(level, fmt, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर				/* CONFIG_IPW2200_DEBUG */

/*
 * To use the debug प्रणाली;
 *
 * If you are defining a new debug classअगरication, simply add it to the #घोषणा
 * list here in the क्रमm of:
 *
 * #घोषणा IPW_DL_xxxx VALUE
 *
 * shअगरting value to the left one bit from the previous entry.  xxxx should be
 * the name of the classअगरication (क्रम example, WEP)
 *
 * You then need to either add a IPW_xxxx_DEBUG() macro definition क्रम your
 * classअगरication, or use IPW_DEBUG(IPW_DL_xxxx, ...) whenever you want
 * to send output to that classअगरication.
 *
 * To add your debug level to the list of levels seen when you perक्रमm
 *
 * % cat /proc/net/ipw/debug_level
 *
 * you simply need to add your entry to the ipw_debug_levels array.
 *
 * If you करो not see debug_level in /proc/net/ipw then you करो not have
 * CONFIG_IPW2200_DEBUG defined in your kernel configuration
 *
 */

#घोषणा IPW_DL_ERROR         (1<<0)
#घोषणा IPW_DL_WARNING       (1<<1)
#घोषणा IPW_DL_INFO          (1<<2)
#घोषणा IPW_DL_WX            (1<<3)
#घोषणा IPW_DL_HOST_COMMAND  (1<<5)
#घोषणा IPW_DL_STATE         (1<<6)

#घोषणा IPW_DL_NOTIF         (1<<10)
#घोषणा IPW_DL_SCAN          (1<<11)
#घोषणा IPW_DL_ASSOC         (1<<12)
#घोषणा IPW_DL_DROP          (1<<13)
#घोषणा IPW_DL_IOCTL         (1<<14)

#घोषणा IPW_DL_MANAGE        (1<<15)
#घोषणा IPW_DL_FW            (1<<16)
#घोषणा IPW_DL_RF_KILL       (1<<17)
#घोषणा IPW_DL_FW_ERRORS     (1<<18)

#घोषणा IPW_DL_LED           (1<<19)

#घोषणा IPW_DL_ORD           (1<<20)

#घोषणा IPW_DL_FRAG          (1<<21)
#घोषणा IPW_DL_WEP           (1<<22)
#घोषणा IPW_DL_TX            (1<<23)
#घोषणा IPW_DL_RX            (1<<24)
#घोषणा IPW_DL_ISR           (1<<25)
#घोषणा IPW_DL_FW_INFO       (1<<26)
#घोषणा IPW_DL_IO            (1<<27)
#घोषणा IPW_DL_TRACE         (1<<28)

#घोषणा IPW_DL_STATS         (1<<29)
#घोषणा IPW_DL_MERGE         (1<<30)
#घोषणा IPW_DL_QOS           (1<<31)

#घोषणा IPW_ERROR(f, a...) prपूर्णांकk(KERN_ERR DRV_NAME ": " f, ## a)
#घोषणा IPW_WARNING(f, a...) prपूर्णांकk(KERN_WARNING DRV_NAME ": " f, ## a)
#घोषणा IPW_DEBUG_INFO(f, a...)    IPW_DEBUG(IPW_DL_INFO, f, ## a)

#घोषणा IPW_DEBUG_WX(f, a...)     IPW_DEBUG(IPW_DL_WX, f, ## a)
#घोषणा IPW_DEBUG_SCAN(f, a...)   IPW_DEBUG(IPW_DL_SCAN, f, ## a)
#घोषणा IPW_DEBUG_TRACE(f, a...)  IPW_LL_DEBUG(IPW_DL_TRACE, f, ## a)
#घोषणा IPW_DEBUG_RX(f, a...)     IPW_LL_DEBUG(IPW_DL_RX, f, ## a)
#घोषणा IPW_DEBUG_TX(f, a...)     IPW_LL_DEBUG(IPW_DL_TX, f, ## a)
#घोषणा IPW_DEBUG_ISR(f, a...)    IPW_LL_DEBUG(IPW_DL_ISR, f, ## a)
#घोषणा IPW_DEBUG_MANAGEMENT(f, a...) IPW_DEBUG(IPW_DL_MANAGE, f, ## a)
#घोषणा IPW_DEBUG_LED(f, a...) IPW_LL_DEBUG(IPW_DL_LED, f, ## a)
#घोषणा IPW_DEBUG_WEP(f, a...)    IPW_LL_DEBUG(IPW_DL_WEP, f, ## a)
#घोषणा IPW_DEBUG_HC(f, a...) IPW_LL_DEBUG(IPW_DL_HOST_COMMAND, f, ## a)
#घोषणा IPW_DEBUG_FRAG(f, a...) IPW_LL_DEBUG(IPW_DL_FRAG, f, ## a)
#घोषणा IPW_DEBUG_FW(f, a...) IPW_LL_DEBUG(IPW_DL_FW, f, ## a)
#घोषणा IPW_DEBUG_RF_KILL(f, a...) IPW_DEBUG(IPW_DL_RF_KILL, f, ## a)
#घोषणा IPW_DEBUG_DROP(f, a...) IPW_DEBUG(IPW_DL_DROP, f, ## a)
#घोषणा IPW_DEBUG_IO(f, a...) IPW_LL_DEBUG(IPW_DL_IO, f, ## a)
#घोषणा IPW_DEBUG_ORD(f, a...) IPW_LL_DEBUG(IPW_DL_ORD, f, ## a)
#घोषणा IPW_DEBUG_FW_INFO(f, a...) IPW_LL_DEBUG(IPW_DL_FW_INFO, f, ## a)
#घोषणा IPW_DEBUG_NOTIF(f, a...) IPW_DEBUG(IPW_DL_NOTIF, f, ## a)
#घोषणा IPW_DEBUG_STATE(f, a...) IPW_DEBUG(IPW_DL_STATE | IPW_DL_ASSOC | IPW_DL_INFO, f, ## a)
#घोषणा IPW_DEBUG_ASSOC(f, a...) IPW_DEBUG(IPW_DL_ASSOC | IPW_DL_INFO, f, ## a)
#घोषणा IPW_DEBUG_STATS(f, a...) IPW_LL_DEBUG(IPW_DL_STATS, f, ## a)
#घोषणा IPW_DEBUG_MERGE(f, a...) IPW_LL_DEBUG(IPW_DL_MERGE, f, ## a)
#घोषणा IPW_DEBUG_QOS(f, a...)   IPW_LL_DEBUG(IPW_DL_QOS, f, ## a)

#समावेश <linux/प्रकार.स>

/*
* Register bit definitions
*/

#घोषणा IPW_INTA_RW       0x00000008
#घोषणा IPW_INTA_MASK_R   0x0000000C
#घोषणा IPW_INसूचीECT_ADDR 0x00000010
#घोषणा IPW_INसूचीECT_DATA 0x00000014
#घोषणा IPW_AUTOINC_ADDR  0x00000018
#घोषणा IPW_AUTOINC_DATA  0x0000001C
#घोषणा IPW_RESET_REG     0x00000020
#घोषणा IPW_GP_CNTRL_RW   0x00000024

#घोषणा IPW_READ_INT_REGISTER 0xFF4

#घोषणा IPW_GP_CNTRL_BIT_INIT_DONE	0x00000004

#घोषणा IPW_REGISTER_DOMAIN1_END        0x00001000
#घोषणा IPW_SRAM_READ_INT_REGISTER 	0x00000ff4

#घोषणा IPW_SHARED_LOWER_BOUND          0x00000200
#घोषणा IPW_INTERRUPT_AREA_LOWER_BOUND  0x00000f80

#घोषणा IPW_NIC_SRAM_LOWER_BOUND        0x00000000
#घोषणा IPW_NIC_SRAM_UPPER_BOUND        0x00030000

#घोषणा IPW_BIT_INT_HOST_SRAM_READ_INT_REGISTER (1 << 29)
#घोषणा IPW_GP_CNTRL_BIT_CLOCK_READY    0x00000001
#घोषणा IPW_GP_CNTRL_BIT_HOST_ALLOWS_STANDBY 0x00000002

/*
 * RESET Register Bit Indexes
 */
#घोषणा CBD_RESET_REG_PRINCETON_RESET (1<<0)
#घोषणा IPW_START_STANDBY             (1<<2)
#घोषणा IPW_ACTIVITY_LED              (1<<4)
#घोषणा IPW_ASSOCIATED_LED            (1<<5)
#घोषणा IPW_OFDM_LED                  (1<<6)
#घोषणा IPW_RESET_REG_SW_RESET        (1<<7)
#घोषणा IPW_RESET_REG_MASTER_DISABLED (1<<8)
#घोषणा IPW_RESET_REG_STOP_MASTER     (1<<9)
#घोषणा IPW_GATE_ODMA                 (1<<25)
#घोषणा IPW_GATE_IDMA                 (1<<26)
#घोषणा IPW_ARC_KESHET_CONFIG         (1<<27)
#घोषणा IPW_GATE_ADMA                 (1<<29)

#घोषणा IPW_CSR_CIS_UPPER_BOUND	0x00000200
#घोषणा IPW_DOMAIN_0_END 0x1000
#घोषणा CLX_MEM_BAR_SIZE 0x1000

/* Dino/baseband control रेजिस्टरs bits */

#घोषणा DINO_ENABLE_SYSTEM 0x80	/* 1 = baseband processor on, 0 = reset */
#घोषणा DINO_ENABLE_CS     0x40	/* 1 = enable ucode load */
#घोषणा DINO_RXFIFO_DATA   0x01	/* 1 = data available */
#घोषणा IPW_BASEBAND_CONTROL_STATUS	0X00200000
#घोषणा IPW_BASEBAND_TX_FIFO_WRITE	0X00200004
#घोषणा IPW_BASEBAND_RX_FIFO_READ	0X00200004
#घोषणा IPW_BASEBAND_CONTROL_STORE	0X00200010

#घोषणा IPW_INTERNAL_CMD_EVENT 	0X00300004
#घोषणा IPW_BASEBAND_POWER_DOWN 0x00000001

#घोषणा IPW_MEM_HALT_AND_RESET  0x003000e0

/* defgroup bits_halt_reset MEM_HALT_AND_RESET रेजिस्टर bits */
#घोषणा IPW_BIT_HALT_RESET_ON	0x80000000
#घोषणा IPW_BIT_HALT_RESET_OFF 	0x00000000

#घोषणा CB_LAST_VALID     0x20000000
#घोषणा CB_INT_ENABLED    0x40000000
#घोषणा CB_VALID          0x80000000
#घोषणा CB_SRC_LE         0x08000000
#घोषणा CB_DEST_LE        0x04000000
#घोषणा CB_SRC_AUTOINC    0x00800000
#घोषणा CB_SRC_IO_GATED   0x00400000
#घोषणा CB_DEST_AUTOINC   0x00080000
#घोषणा CB_SRC_SIZE_LONG  0x00200000
#घोषणा CB_DEST_SIZE_LONG 0x00020000

/* DMA DEFINES */

#घोषणा DMA_CONTROL_SMALL_CB_CONST_VALUE 0x00540000
#घोषणा DMA_CB_STOP_AND_ABORT            0x00000C00
#घोषणा DMA_CB_START                     0x00000100

#घोषणा IPW_SHARED_SRAM_SIZE               0x00030000
#घोषणा IPW_SHARED_SRAM_DMA_CONTROL        0x00027000
#घोषणा CB_MAX_LENGTH                      0x1FFF

#घोषणा IPW_HOST_EEPROM_DATA_SRAM_SIZE 0xA18
#घोषणा IPW_EEPROM_IMAGE_SIZE          0x100

/* DMA defs */
#घोषणा IPW_DMA_I_CURRENT_CB  0x003000D0
#घोषणा IPW_DMA_O_CURRENT_CB  0x003000D4
#घोषणा IPW_DMA_I_DMA_CONTROL 0x003000A4
#घोषणा IPW_DMA_I_CB_BASE     0x003000A0

#घोषणा IPW_TX_CMD_QUEUE_BD_BASE        0x00000200
#घोषणा IPW_TX_CMD_QUEUE_BD_SIZE        0x00000204
#घोषणा IPW_TX_QUEUE_0_BD_BASE          0x00000208
#घोषणा IPW_TX_QUEUE_0_BD_SIZE          (0x0000020C)
#घोषणा IPW_TX_QUEUE_1_BD_BASE          0x00000210
#घोषणा IPW_TX_QUEUE_1_BD_SIZE          0x00000214
#घोषणा IPW_TX_QUEUE_2_BD_BASE          0x00000218
#घोषणा IPW_TX_QUEUE_2_BD_SIZE          (0x0000021C)
#घोषणा IPW_TX_QUEUE_3_BD_BASE          0x00000220
#घोषणा IPW_TX_QUEUE_3_BD_SIZE          0x00000224
#घोषणा IPW_RX_BD_BASE                  0x00000240
#घोषणा IPW_RX_BD_SIZE                  0x00000244
#घोषणा IPW_RFDS_TABLE_LOWER            0x00000500

#घोषणा IPW_TX_CMD_QUEUE_READ_INDEX     0x00000280
#घोषणा IPW_TX_QUEUE_0_READ_INDEX       0x00000284
#घोषणा IPW_TX_QUEUE_1_READ_INDEX       0x00000288
#घोषणा IPW_TX_QUEUE_2_READ_INDEX       (0x0000028C)
#घोषणा IPW_TX_QUEUE_3_READ_INDEX       0x00000290
#घोषणा IPW_RX_READ_INDEX               (0x000002A0)

#घोषणा IPW_TX_CMD_QUEUE_WRITE_INDEX    (0x00000F80)
#घोषणा IPW_TX_QUEUE_0_WRITE_INDEX      (0x00000F84)
#घोषणा IPW_TX_QUEUE_1_WRITE_INDEX      (0x00000F88)
#घोषणा IPW_TX_QUEUE_2_WRITE_INDEX      (0x00000F8C)
#घोषणा IPW_TX_QUEUE_3_WRITE_INDEX      (0x00000F90)
#घोषणा IPW_RX_WRITE_INDEX              (0x00000FA0)

/*
 * EEPROM Related Definitions
 */

#घोषणा IPW_EEPROM_DATA_SRAM_ADDRESS (IPW_SHARED_LOWER_BOUND + 0x814)
#घोषणा IPW_EEPROM_DATA_SRAM_SIZE    (IPW_SHARED_LOWER_BOUND + 0x818)
#घोषणा IPW_EEPROM_LOAD_DISABLE      (IPW_SHARED_LOWER_BOUND + 0x81C)
#घोषणा IPW_EEPROM_DATA              (IPW_SHARED_LOWER_BOUND + 0x820)
#घोषणा IPW_EEPROM_UPPER_ADDRESS     (IPW_SHARED_LOWER_BOUND + 0x9E0)

#घोषणा IPW_STATION_TABLE_LOWER      (IPW_SHARED_LOWER_BOUND + 0xA0C)
#घोषणा IPW_STATION_TABLE_UPPER      (IPW_SHARED_LOWER_BOUND + 0xB0C)
#घोषणा IPW_REQUEST_ATIM             (IPW_SHARED_LOWER_BOUND + 0xB0C)
#घोषणा IPW_ATIM_SENT                (IPW_SHARED_LOWER_BOUND + 0xB10)
#घोषणा IPW_WHO_IS_AWAKE             (IPW_SHARED_LOWER_BOUND + 0xB14)
#घोषणा IPW_DURING_ATIM_WINDOW       (IPW_SHARED_LOWER_BOUND + 0xB18)

#घोषणा MSB                             1
#घोषणा LSB                             0
#घोषणा WORD_TO_BYTE(_word)             ((_word) * माप(u16))

#घोषणा GET_EEPROM_ADDR(_worकरोffset,_byteoffset) \
    ( WORD_TO_BYTE(_worकरोffset) + (_byteoffset) )

/* EEPROM access by BYTE */
#घोषणा EEPROM_PME_CAPABILITY   (GET_EEPROM_ADDR(0x09,MSB))	/* 1 byte   */
#घोषणा EEPROM_MAC_ADDRESS      (GET_EEPROM_ADDR(0x21,LSB))	/* 6 byte   */
#घोषणा EEPROM_VERSION          (GET_EEPROM_ADDR(0x24,MSB))	/* 1 byte   */
#घोषणा EEPROM_NIC_TYPE         (GET_EEPROM_ADDR(0x25,LSB))	/* 1 byte   */
#घोषणा EEPROM_SKU_CAPABILITY   (GET_EEPROM_ADDR(0x25,MSB))	/* 1 byte   */
#घोषणा EEPROM_COUNTRY_CODE     (GET_EEPROM_ADDR(0x26,LSB))	/* 3 bytes  */
#घोषणा EEPROM_IBSS_CHANNELS_BG (GET_EEPROM_ADDR(0x28,LSB))	/* 2 bytes  */
#घोषणा EEPROM_IBSS_CHANNELS_A  (GET_EEPROM_ADDR(0x29,MSB))	/* 5 bytes  */
#घोषणा EEPROM_BSS_CHANNELS_BG  (GET_EEPROM_ADDR(0x2c,LSB))	/* 2 bytes  */
#घोषणा EEPROM_HW_VERSION       (GET_EEPROM_ADDR(0x72,LSB))	/* 2 bytes  */

/* NIC type as found in the one byte EEPROM_NIC_TYPE offset */
#घोषणा EEPROM_NIC_TYPE_0 0
#घोषणा EEPROM_NIC_TYPE_1 1
#घोषणा EEPROM_NIC_TYPE_2 2
#घोषणा EEPROM_NIC_TYPE_3 3
#घोषणा EEPROM_NIC_TYPE_4 4

/* Bluetooth Coexistence capabilities as found in EEPROM_SKU_CAPABILITY */
#घोषणा EEPROM_SKU_CAP_BT_CHANNEL_SIG  0x01	/* we can tell BT our channel # */
#घोषणा EEPROM_SKU_CAP_BT_PRIORITY     0x02	/* BT can take priority over us */
#घोषणा EEPROM_SKU_CAP_BT_OOB          0x04	/* we can संकेत BT out-of-band */

#घोषणा FW_MEM_REG_LOWER_BOUND          0x00300000
#घोषणा FW_MEM_REG_EEPROM_ACCESS        (FW_MEM_REG_LOWER_BOUND + 0x40)
#घोषणा IPW_EVENT_REG                   (FW_MEM_REG_LOWER_BOUND + 0x04)
#घोषणा EEPROM_BIT_SK                   (1<<0)
#घोषणा EEPROM_BIT_CS                   (1<<1)
#घोषणा EEPROM_BIT_DI                   (1<<2)
#घोषणा EEPROM_BIT_DO                   (1<<4)

#घोषणा EEPROM_CMD_READ                 0x2

/* Interrupts masks */
#घोषणा IPW_INTA_NONE   0x00000000

#घोषणा IPW_INTA_BIT_RX_TRANSFER                   0x00000002
#घोषणा IPW_INTA_BIT_STATUS_CHANGE                 0x00000010
#घोषणा IPW_INTA_BIT_BEACON_PERIOD_EXPIRED         0x00000020

//Inta Bits क्रम CF
#घोषणा IPW_INTA_BIT_TX_CMD_QUEUE                  0x00000800
#घोषणा IPW_INTA_BIT_TX_QUEUE_1                    0x00001000
#घोषणा IPW_INTA_BIT_TX_QUEUE_2                    0x00002000
#घोषणा IPW_INTA_BIT_TX_QUEUE_3                    0x00004000
#घोषणा IPW_INTA_BIT_TX_QUEUE_4                    0x00008000

#घोषणा IPW_INTA_BIT_SLAVE_MODE_HOST_CMD_DONE      0x00010000

#घोषणा IPW_INTA_BIT_PREPARE_FOR_POWER_DOWN        0x00100000
#घोषणा IPW_INTA_BIT_POWER_DOWN                    0x00200000

#घोषणा IPW_INTA_BIT_FW_INITIALIZATION_DONE        0x01000000
#घोषणा IPW_INTA_BIT_FW_CARD_DISABLE_PHY_OFF_DONE  0x02000000
#घोषणा IPW_INTA_BIT_RF_KILL_DONE                  0x04000000
#घोषणा IPW_INTA_BIT_FATAL_ERROR             0x40000000
#घोषणा IPW_INTA_BIT_PARITY_ERROR            0x80000000

/* Interrupts enabled at init समय. */
#घोषणा IPW_INTA_MASK_ALL                        \
        (IPW_INTA_BIT_TX_QUEUE_1               | \
	 IPW_INTA_BIT_TX_QUEUE_2               | \
	 IPW_INTA_BIT_TX_QUEUE_3               | \
	 IPW_INTA_BIT_TX_QUEUE_4               | \
	 IPW_INTA_BIT_TX_CMD_QUEUE             | \
	 IPW_INTA_BIT_RX_TRANSFER              | \
	 IPW_INTA_BIT_FATAL_ERROR              | \
	 IPW_INTA_BIT_PARITY_ERROR             | \
	 IPW_INTA_BIT_STATUS_CHANGE            | \
	 IPW_INTA_BIT_FW_INITIALIZATION_DONE   | \
	 IPW_INTA_BIT_BEACON_PERIOD_EXPIRED    | \
	 IPW_INTA_BIT_SLAVE_MODE_HOST_CMD_DONE | \
	 IPW_INTA_BIT_PREPARE_FOR_POWER_DOWN   | \
	 IPW_INTA_BIT_POWER_DOWN               | \
         IPW_INTA_BIT_RF_KILL_DONE )

/* FW event log definitions */
#घोषणा EVENT_ELEM_SIZE     (3 * माप(u32))
#घोषणा EVENT_START_OFFSET  (1 * माप(u32) + 2 * माप(u16))

/* FW error log definitions */
#घोषणा ERROR_ELEM_SIZE     (7 * माप(u32))
#घोषणा ERROR_START_OFFSET  (1 * माप(u32))

/* TX घातer level (dbm) */
#घोषणा IPW_TX_POWER_MIN	-12
#घोषणा IPW_TX_POWER_MAX	20
#घोषणा IPW_TX_POWER_DEFAULT	IPW_TX_POWER_MAX

क्रमागत अणु
	IPW_FW_ERROR_OK = 0,
	IPW_FW_ERROR_FAIL,
	IPW_FW_ERROR_MEMORY_UNDERFLOW,
	IPW_FW_ERROR_MEMORY_OVERFLOW,
	IPW_FW_ERROR_BAD_PARAM,
	IPW_FW_ERROR_BAD_CHECKSUM,
	IPW_FW_ERROR_NMI_INTERRUPT,
	IPW_FW_ERROR_BAD_DATABASE,
	IPW_FW_ERROR_ALLOC_FAIL,
	IPW_FW_ERROR_DMA_UNDERRUN,
	IPW_FW_ERROR_DMA_STATUS,
	IPW_FW_ERROR_DINO_ERROR,
	IPW_FW_ERROR_EEPROM_ERROR,
	IPW_FW_ERROR_SYSASSERT,
	IPW_FW_ERROR_FATAL_ERROR
पूर्ण;

#घोषणा AUTH_OPEN	0
#घोषणा AUTH_SHARED_KEY	1
#घोषणा AUTH_LEAP	2
#घोषणा AUTH_IGNORE	3

#घोषणा HC_ASSOCIATE      0
#घोषणा HC_REASSOCIATE    1
#घोषणा HC_DISASSOCIATE   2
#घोषणा HC_IBSS_START     3
#घोषणा HC_IBSS_RECONF    4
#घोषणा HC_DISASSOC_QUIET 5

#घोषणा HC_QOS_SUPPORT_ASSOC  cpu_to_le16(0x01)

#घोषणा IPW_RATE_CAPABILITIES 1
#घोषणा IPW_RATE_CONNECT      0

/*
 * Rate values and masks
 */
#घोषणा IPW_TX_RATE_1MB  0x0A
#घोषणा IPW_TX_RATE_2MB  0x14
#घोषणा IPW_TX_RATE_5MB  0x37
#घोषणा IPW_TX_RATE_6MB  0x0D
#घोषणा IPW_TX_RATE_9MB  0x0F
#घोषणा IPW_TX_RATE_11MB 0x6E
#घोषणा IPW_TX_RATE_12MB 0x05
#घोषणा IPW_TX_RATE_18MB 0x07
#घोषणा IPW_TX_RATE_24MB 0x09
#घोषणा IPW_TX_RATE_36MB 0x0B
#घोषणा IPW_TX_RATE_48MB 0x01
#घोषणा IPW_TX_RATE_54MB 0x03

#घोषणा IPW_ORD_TABLE_ID_MASK             0x0000FF00
#घोषणा IPW_ORD_TABLE_VALUE_MASK          0x000000FF

#घोषणा IPW_ORD_TABLE_0_MASK              0x0000F000
#घोषणा IPW_ORD_TABLE_1_MASK              0x0000F100
#घोषणा IPW_ORD_TABLE_2_MASK              0x0000F200
#घोषणा IPW_ORD_TABLE_3_MASK              0x0000F300
#घोषणा IPW_ORD_TABLE_4_MASK              0x0000F400
#घोषणा IPW_ORD_TABLE_5_MASK              0x0000F500
#घोषणा IPW_ORD_TABLE_6_MASK              0x0000F600
#घोषणा IPW_ORD_TABLE_7_MASK              0x0000F700

/*
 * Table 0 Entries (all entries are 32 bits)
 */
क्रमागत अणु
	IPW_ORD_STAT_TX_CURR_RATE = IPW_ORD_TABLE_0_MASK + 1,
	IPW_ORD_STAT_FRAG_TRESHOLD,
	IPW_ORD_STAT_RTS_THRESHOLD,
	IPW_ORD_STAT_TX_HOST_REQUESTS,
	IPW_ORD_STAT_TX_HOST_COMPLETE,
	IPW_ORD_STAT_TX_सूची_DATA,
	IPW_ORD_STAT_TX_सूची_DATA_B_1,
	IPW_ORD_STAT_TX_सूची_DATA_B_2,
	IPW_ORD_STAT_TX_सूची_DATA_B_5_5,
	IPW_ORD_STAT_TX_सूची_DATA_B_11,
	/* Hole */

	IPW_ORD_STAT_TX_सूची_DATA_G_1 = IPW_ORD_TABLE_0_MASK + 19,
	IPW_ORD_STAT_TX_सूची_DATA_G_2,
	IPW_ORD_STAT_TX_सूची_DATA_G_5_5,
	IPW_ORD_STAT_TX_सूची_DATA_G_6,
	IPW_ORD_STAT_TX_सूची_DATA_G_9,
	IPW_ORD_STAT_TX_सूची_DATA_G_11,
	IPW_ORD_STAT_TX_सूची_DATA_G_12,
	IPW_ORD_STAT_TX_सूची_DATA_G_18,
	IPW_ORD_STAT_TX_सूची_DATA_G_24,
	IPW_ORD_STAT_TX_सूची_DATA_G_36,
	IPW_ORD_STAT_TX_सूची_DATA_G_48,
	IPW_ORD_STAT_TX_सूची_DATA_G_54,
	IPW_ORD_STAT_TX_NON_सूची_DATA,
	IPW_ORD_STAT_TX_NON_सूची_DATA_B_1,
	IPW_ORD_STAT_TX_NON_सूची_DATA_B_2,
	IPW_ORD_STAT_TX_NON_सूची_DATA_B_5_5,
	IPW_ORD_STAT_TX_NON_सूची_DATA_B_11,
	/* Hole */

	IPW_ORD_STAT_TX_NON_सूची_DATA_G_1 = IPW_ORD_TABLE_0_MASK + 44,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_2,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_5_5,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_6,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_9,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_11,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_12,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_18,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_24,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_36,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_48,
	IPW_ORD_STAT_TX_NON_सूची_DATA_G_54,
	IPW_ORD_STAT_TX_RETRY,
	IPW_ORD_STAT_TX_FAILURE,
	IPW_ORD_STAT_RX_ERR_CRC,
	IPW_ORD_STAT_RX_ERR_ICV,
	IPW_ORD_STAT_RX_NO_BUFFER,
	IPW_ORD_STAT_FULL_SCANS,
	IPW_ORD_STAT_PARTIAL_SCANS,
	IPW_ORD_STAT_TGH_ABORTED_SCANS,
	IPW_ORD_STAT_TX_TOTAL_BYTES,
	IPW_ORD_STAT_CURR_RSSI_RAW,
	IPW_ORD_STAT_RX_BEACON,
	IPW_ORD_STAT_MISSED_BEACONS,
	IPW_ORD_TABLE_0_LAST
पूर्ण;

#घोषणा IPW_RSSI_TO_DBM 112

/* Table 1 Entries
 */
क्रमागत अणु
	IPW_ORD_TABLE_1_LAST = IPW_ORD_TABLE_1_MASK | 1,
पूर्ण;

/*
 * Table 2 Entries
 *
 * FW_VERSION:    16 byte string
 * FW_DATE:       16 byte string (only 14 bytes used)
 * UCODE_VERSION: 4 byte version code
 * UCODE_DATE:    5 bytes code code
 * ADDAPTER_MAC:  6 byte MAC address
 * RTC:           4 byte घड़ी
 */
क्रमागत अणु
	IPW_ORD_STAT_FW_VERSION = IPW_ORD_TABLE_2_MASK | 1,
	IPW_ORD_STAT_FW_DATE,
	IPW_ORD_STAT_UCODE_VERSION,
	IPW_ORD_STAT_UCODE_DATE,
	IPW_ORD_STAT_ADAPTER_MAC,
	IPW_ORD_STAT_RTC,
	IPW_ORD_TABLE_2_LAST
पूर्ण;

/* Table 3 */
क्रमागत अणु
	IPW_ORD_STAT_TX_PACKET = IPW_ORD_TABLE_3_MASK | 0,
	IPW_ORD_STAT_TX_PACKET_FAILURE,
	IPW_ORD_STAT_TX_PACKET_SUCCESS,
	IPW_ORD_STAT_TX_PACKET_ABORTED,
	IPW_ORD_TABLE_3_LAST
पूर्ण;

/* Table 4 */
क्रमागत अणु
	IPW_ORD_TABLE_4_LAST = IPW_ORD_TABLE_4_MASK
पूर्ण;

/* Table 5 */
क्रमागत अणु
	IPW_ORD_STAT_AVAILABLE_AP_COUNT = IPW_ORD_TABLE_5_MASK,
	IPW_ORD_STAT_AP_ASSNS,
	IPW_ORD_STAT_ROAM,
	IPW_ORD_STAT_ROAM_CAUSE_MISSED_BEACONS,
	IPW_ORD_STAT_ROAM_CAUSE_UNASSOC,
	IPW_ORD_STAT_ROAM_CAUSE_RSSI,
	IPW_ORD_STAT_ROAM_CAUSE_LINK_QUALITY,
	IPW_ORD_STAT_ROAM_CAUSE_AP_LOAD_BALANCE,
	IPW_ORD_STAT_ROAM_CAUSE_AP_NO_TX,
	IPW_ORD_STAT_LINK_UP,
	IPW_ORD_STAT_LINK_DOWN,
	IPW_ORD_ANTENNA_DIVERSITY,
	IPW_ORD_CURR_FREQ,
	IPW_ORD_TABLE_5_LAST
पूर्ण;

/* Table 6 */
क्रमागत अणु
	IPW_ORD_COUNTRY_CODE = IPW_ORD_TABLE_6_MASK,
	IPW_ORD_CURR_BSSID,
	IPW_ORD_CURR_SSID,
	IPW_ORD_TABLE_6_LAST
पूर्ण;

/* Table 7 */
क्रमागत अणु
	IPW_ORD_STAT_PERCENT_MISSED_BEACONS = IPW_ORD_TABLE_7_MASK,
	IPW_ORD_STAT_PERCENT_TX_RETRIES,
	IPW_ORD_STAT_PERCENT_LINK_QUALITY,
	IPW_ORD_STAT_CURR_RSSI_DBM,
	IPW_ORD_TABLE_7_LAST
पूर्ण;

#घोषणा IPW_ERROR_LOG     (IPW_SHARED_LOWER_BOUND + 0x410)
#घोषणा IPW_EVENT_LOG     (IPW_SHARED_LOWER_BOUND + 0x414)
#घोषणा IPW_ORDINALS_TABLE_LOWER        (IPW_SHARED_LOWER_BOUND + 0x500)
#घोषणा IPW_ORDINALS_TABLE_0            (IPW_SHARED_LOWER_BOUND + 0x180)
#घोषणा IPW_ORDINALS_TABLE_1            (IPW_SHARED_LOWER_BOUND + 0x184)
#घोषणा IPW_ORDINALS_TABLE_2            (IPW_SHARED_LOWER_BOUND + 0x188)
#घोषणा IPW_MEM_FIXED_OVERRIDE          (IPW_SHARED_LOWER_BOUND + 0x41C)

काष्ठा ipw_fixed_rate अणु
	__le16 tx_rates;
	__le16 reserved;
पूर्ण __packed;

#घोषणा IPW_INसूचीECT_ADDR_MASK (~0x3ul)

काष्ठा host_cmd अणु
	u8 cmd;
	u8 len;
	u16 reserved;
	u32 *param;
पूर्ण __packed;	/* XXX */

काष्ठा cmdlog_host_cmd अणु
	u8 cmd;
	u8 len;
	__le16 reserved;
	अक्षर param[124];
पूर्ण __packed;

काष्ठा ipw_cmd_log अणु
	अचिन्हित दीर्घ jअगरfies;
	पूर्णांक retcode;
	काष्ठा cmdlog_host_cmd cmd;
पूर्ण;

/* SysConfig command parameters ... */
/* bt_coexistence param */
#घोषणा CFG_BT_COEXISTENCE_SIGNAL_CHNL  0x01	/* tell BT our chnl # */
#घोषणा CFG_BT_COEXISTENCE_DEFER        0x02	/* defer our Tx अगर BT traffic */
#घोषणा CFG_BT_COEXISTENCE_KILL         0x04	/* समाप्त our Tx अगर BT traffic */
#घोषणा CFG_BT_COEXISTENCE_WME_OVER_BT  0x08	/* mulसमयdia extensions */
#घोषणा CFG_BT_COEXISTENCE_OOB          0x10	/* संकेत BT via out-of-band */

/* clear-to-send to self param */
#घोषणा CFG_CTS_TO_ITSELF_ENABLED_MIN	0x00
#घोषणा CFG_CTS_TO_ITSELF_ENABLED_MAX	0x01
#घोषणा CFG_CTS_TO_ITSELF_ENABLED_DEF	CFG_CTS_TO_ITSELF_ENABLED_MIN

/* Antenna भागersity param (h/w can select best antenna, based on संकेत) */
#घोषणा CFG_SYS_ANTENNA_BOTH            0x00	/* NIC selects best antenna */
#घोषणा CFG_SYS_ANTENNA_A               0x01	/* क्रमce antenna A */
#घोषणा CFG_SYS_ANTENNA_B               0x03	/* क्रमce antenna B */
#घोषणा CFG_SYS_ANTENNA_SLOW_DIV        0x02	/* consider background noise */

#घोषणा IPW_MAX_CONFIG_RETRIES 10

#पूर्ण_अगर				/* __ipw2200_h__ */
