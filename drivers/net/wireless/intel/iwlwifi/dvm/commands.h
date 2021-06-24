<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014 Intel Corporation
 */
/*
 * Please use this file (commands.h) only क्रम uCode API definitions.
 * Please use iwl-xxxx-hw.h क्रम hardware-related definitions.
 * Please use dev.h क्रम driver implementation definitions.
 */

#अगर_अघोषित __iwl_commands_h__
#घोषणा __iwl_commands_h__

#समावेश <linux/ieee80211.h>
#समावेश <linux/types.h>


क्रमागत अणु
	REPLY_ALIVE = 0x1,
	REPLY_ERROR = 0x2,
	REPLY_ECHO = 0x3,		/* test command */

	/* RXON and QOS commands */
	REPLY_RXON = 0x10,
	REPLY_RXON_ASSOC = 0x11,
	REPLY_QOS_PARAM = 0x13,
	REPLY_RXON_TIMING = 0x14,

	/* Multi-Station support */
	REPLY_ADD_STA = 0x18,
	REPLY_REMOVE_STA = 0x19,
	REPLY_REMOVE_ALL_STA = 0x1a,	/* not used */
	REPLY_TXFIFO_FLUSH = 0x1e,

	/* Security */
	REPLY_WEPKEY = 0x20,

	/* RX, TX, LEDs */
	REPLY_TX = 0x1c,
	REPLY_LEDS_CMD = 0x48,
	REPLY_TX_LINK_QUALITY_CMD = 0x4e,

	/* WiMAX coexistence */
	COEX_PRIORITY_TABLE_CMD = 0x5a,
	COEX_MEDIUM_NOTIFICATION = 0x5b,
	COEX_EVENT_CMD = 0x5c,

	/* Calibration */
	TEMPERATURE_NOTIFICATION = 0x62,
	CALIBRATION_CFG_CMD = 0x65,
	CALIBRATION_RES_NOTIFICATION = 0x66,
	CALIBRATION_COMPLETE_NOTIFICATION = 0x67,

	/* 802.11h related */
	REPLY_QUIET_CMD = 0x71,		/* not used */
	REPLY_CHANNEL_SWITCH = 0x72,
	CHANNEL_SWITCH_NOTIFICATION = 0x73,
	REPLY_SPECTRUM_MEASUREMENT_CMD = 0x74,
	SPECTRUM_MEASURE_NOTIFICATION = 0x75,

	/* Power Management */
	POWER_TABLE_CMD = 0x77,
	PM_SLEEP_NOTIFICATION = 0x7A,
	PM_DEBUG_STATISTIC_NOTIFIC = 0x7B,

	/* Scan commands and notअगरications */
	REPLY_SCAN_CMD = 0x80,
	REPLY_SCAN_ABORT_CMD = 0x81,
	SCAN_START_NOTIFICATION = 0x82,
	SCAN_RESULTS_NOTIFICATION = 0x83,
	SCAN_COMPLETE_NOTIFICATION = 0x84,

	/* IBSS/AP commands */
	BEACON_NOTIFICATION = 0x90,
	REPLY_TX_BEACON = 0x91,
	WHO_IS_AWAKE_NOTIFICATION = 0x94,	/* not used */

	/* Miscellaneous commands */
	REPLY_TX_POWER_DBM_CMD = 0x95,
	QUIET_NOTIFICATION = 0x96,		/* not used */
	REPLY_TX_PWR_TABLE_CMD = 0x97,
	REPLY_TX_POWER_DBM_CMD_V1 = 0x98,	/* old version of API */
	TX_ANT_CONFIGURATION_CMD = 0x98,
	MEASURE_ABORT_NOTIFICATION = 0x99,	/* not used */

	/* Bluetooth device coexistence config command */
	REPLY_BT_CONFIG = 0x9b,

	/* Statistics */
	REPLY_STATISTICS_CMD = 0x9c,
	STATISTICS_NOTIFICATION = 0x9d,

	/* RF-KILL commands and notअगरications */
	REPLY_CARD_STATE_CMD = 0xa0,
	CARD_STATE_NOTIFICATION = 0xa1,

	/* Missed beacons notअगरication */
	MISSED_BEACONS_NOTIFICATION = 0xa2,

	REPLY_CT_KILL_CONFIG_CMD = 0xa4,
	SENSITIVITY_CMD = 0xa8,
	REPLY_PHY_CALIBRATION_CMD = 0xb0,
	REPLY_RX_PHY_CMD = 0xc0,
	REPLY_RX_MPDU_CMD = 0xc1,
	REPLY_RX = 0xc3,
	REPLY_COMPRESSED_BA = 0xc5,

	/* BT Coex */
	REPLY_BT_COEX_PRIO_TABLE = 0xcc,
	REPLY_BT_COEX_PROT_ENV = 0xcd,
	REPLY_BT_COEX_PROखाता_NOTIF = 0xce,

	/* PAN commands */
	REPLY_WIPAN_PARAMS = 0xb2,
	REPLY_WIPAN_RXON = 0xb3,	/* use REPLY_RXON काष्ठाure */
	REPLY_WIPAN_RXON_TIMING = 0xb4,	/* use REPLY_RXON_TIMING काष्ठाure */
	REPLY_WIPAN_RXON_ASSOC = 0xb6,	/* use REPLY_RXON_ASSOC काष्ठाure */
	REPLY_WIPAN_QOS_PARAM = 0xb7,	/* use REPLY_QOS_PARAM काष्ठाure */
	REPLY_WIPAN_WEPKEY = 0xb8,	/* use REPLY_WEPKEY काष्ठाure */
	REPLY_WIPAN_P2P_CHANNEL_SWITCH = 0xb9,
	REPLY_WIPAN_NOA_NOTIFICATION = 0xbc,
	REPLY_WIPAN_DEACTIVATION_COMPLETE = 0xbd,

	REPLY_WOWLAN_PATTERNS = 0xe0,
	REPLY_WOWLAN_WAKEUP_FILTER = 0xe1,
	REPLY_WOWLAN_TSC_RSC_PARAMS = 0xe2,
	REPLY_WOWLAN_TKIP_PARAMS = 0xe3,
	REPLY_WOWLAN_KEK_KCK_MATERIAL = 0xe4,
	REPLY_WOWLAN_GET_STATUS = 0xe5,
	REPLY_D3_CONFIG = 0xd3,

	REPLY_MAX = 0xff
पूर्ण;

/*
 * Minimum number of queues. MAX_NUM is defined in hw specअगरic files.
 * Set the minimum to accommodate
 *  - 4 standard TX queues
 *  - the command queue
 *  - 4 PAN TX queues
 *  - the PAN multicast queue, and
 *  - the AUX (TX during scan dwell) queue.
 */
#घोषणा IWL_MIN_NUM_QUEUES	11

/*
 * Command queue depends on iPAN support.
 */
#घोषणा IWL_DEFAULT_CMD_QUEUE_NUM	4
#घोषणा IWL_IPAN_CMD_QUEUE_NUM		9

#घोषणा IWL_TX_FIFO_BK		0	/* shared */
#घोषणा IWL_TX_FIFO_BE		1
#घोषणा IWL_TX_FIFO_VI		2	/* shared */
#घोषणा IWL_TX_FIFO_VO		3
#घोषणा IWL_TX_FIFO_BK_IPAN	IWL_TX_FIFO_BK
#घोषणा IWL_TX_FIFO_BE_IPAN	4
#घोषणा IWL_TX_FIFO_VI_IPAN	IWL_TX_FIFO_VI
#घोषणा IWL_TX_FIFO_VO_IPAN	5
/* re-uses the VO FIFO, uCode will properly flush/schedule */
#घोषणा IWL_TX_FIFO_AUX		5
#घोषणा IWL_TX_FIFO_UNUSED	255

#घोषणा IWLAGN_CMD_FIFO_NUM	7

/*
 * This queue number is required क्रम proper operation
 * because the ucode will stop/start the scheduler as
 * required.
 */
#घोषणा IWL_IPAN_MCAST_QUEUE	8

/******************************************************************************
 * (0)
 * Commonly used काष्ठाures and definitions:
 * Command header, rate_n_flags, txघातer
 *
 *****************************************************************************/

/**
 * iwlagn rate_n_flags bit fields
 *
 * rate_n_flags क्रमmat is used in following iwlagn commands:
 *  REPLY_RX (response only)
 *  REPLY_RX_MPDU (response only)
 *  REPLY_TX (both command and response)
 *  REPLY_TX_LINK_QUALITY_CMD
 *
 * High-throughput (HT) rate क्रमmat क्रम bits 7:0 (bit 8 must be "1"):
 *  2-0:  0)   6 Mbps
 *        1)  12 Mbps
 *        2)  18 Mbps
 *        3)  24 Mbps
 *        4)  36 Mbps
 *        5)  48 Mbps
 *        6)  54 Mbps
 *        7)  60 Mbps
 *
 *  4-3:  0)  Single stream (SISO)
 *        1)  Dual stream (MIMO)
 *        2)  Triple stream (MIMO)
 *
 *    5:  Value of 0x20 in bits 7:0 indicates 6 Mbps HT40 duplicate data
 *
 * Legacy OFDM rate क्रमmat क्रम bits 7:0 (bit 8 must be "0", bit 9 "0"):
 *  3-0:  0xD)   6 Mbps
 *        0xF)   9 Mbps
 *        0x5)  12 Mbps
 *        0x7)  18 Mbps
 *        0x9)  24 Mbps
 *        0xB)  36 Mbps
 *        0x1)  48 Mbps
 *        0x3)  54 Mbps
 *
 * Legacy CCK rate क्रमmat क्रम bits 7:0 (bit 8 must be "0", bit 9 "1"):
 *  6-0:   10)  1 Mbps
 *         20)  2 Mbps
 *         55)  5.5 Mbps
 *        110)  11 Mbps
 */
#घोषणा RATE_MCS_CODE_MSK 0x7
#घोषणा RATE_MCS_SPATIAL_POS 3
#घोषणा RATE_MCS_SPATIAL_MSK 0x18
#घोषणा RATE_MCS_HT_DUP_POS 5
#घोषणा RATE_MCS_HT_DUP_MSK 0x20
/* Both legacy and HT use bits 7:0 as the CCK/OFDM rate or HT MCS */
#घोषणा RATE_MCS_RATE_MSK 0xff

/* Bit 8: (1) HT क्रमmat, (0) legacy क्रमmat in bits 7:0 */
#घोषणा RATE_MCS_FLAGS_POS 8
#घोषणा RATE_MCS_HT_POS 8
#घोषणा RATE_MCS_HT_MSK 0x100

/* Bit 9: (1) CCK, (0) OFDM.  HT (bit 8) must be "0" क्रम this bit to be valid */
#घोषणा RATE_MCS_CCK_POS 9
#घोषणा RATE_MCS_CCK_MSK 0x200

/* Bit 10: (1) Use Green Field preamble */
#घोषणा RATE_MCS_GF_POS 10
#घोषणा RATE_MCS_GF_MSK 0x400

/* Bit 11: (1) Use 40Mhz HT40 chnl width, (0) use 20 MHz legacy chnl width */
#घोषणा RATE_MCS_HT40_POS 11
#घोषणा RATE_MCS_HT40_MSK 0x800

/* Bit 12: (1) Duplicate data on both 20MHz chnls. HT40 (bit 11) must be set. */
#घोषणा RATE_MCS_DUP_POS 12
#घोषणा RATE_MCS_DUP_MSK 0x1000

/* Bit 13: (1) Short guard पूर्णांकerval (0.4 usec), (0) normal GI (0.8 usec) */
#घोषणा RATE_MCS_SGI_POS 13
#घोषणा RATE_MCS_SGI_MSK 0x2000

/**
 * rate_n_flags Tx antenna masks
 * bit14:16
 */
#घोषणा RATE_MCS_ANT_POS	14
#घोषणा RATE_MCS_ANT_A_MSK	0x04000
#घोषणा RATE_MCS_ANT_B_MSK	0x08000
#घोषणा RATE_MCS_ANT_C_MSK	0x10000
#घोषणा RATE_MCS_ANT_AB_MSK	(RATE_MCS_ANT_A_MSK | RATE_MCS_ANT_B_MSK)
#घोषणा RATE_MCS_ANT_ABC_MSK	(RATE_MCS_ANT_AB_MSK | RATE_MCS_ANT_C_MSK)
#घोषणा RATE_ANT_NUM 3

#घोषणा POWER_TABLE_NUM_ENTRIES			33
#घोषणा POWER_TABLE_NUM_HT_OFDM_ENTRIES		32
#घोषणा POWER_TABLE_CCK_ENTRY			32

#घोषणा IWL_PWR_NUM_HT_OFDM_ENTRIES		24
#घोषणा IWL_PWR_CCK_ENTRIES			2

/**
 * काष्ठा tx_घातer_dual_stream
 *
 * Table entries in REPLY_TX_PWR_TABLE_CMD, REPLY_CHANNEL_SWITCH
 *
 * Same क्रमmat as iwl_tx_घातer_dual_stream, but __le32
 */
काष्ठा tx_घातer_dual_stream अणु
	__le32 dw;
पूर्ण __packed;

/**
 * Command REPLY_TX_POWER_DBM_CMD = 0x98
 * काष्ठा iwlagn_tx_घातer_dbm_cmd
 */
#घोषणा IWLAGN_TX_POWER_AUTO 0x7f
#घोषणा IWLAGN_TX_POWER_NO_CLOSED (0x1 << 6)

काष्ठा iwlagn_tx_घातer_dbm_cmd अणु
	s8 global_lmt; /*in half-dBm (e.g. 30 = 15 dBm) */
	u8 flags;
	s8 srv_chan_lmt; /*in half-dBm (e.g. 30 = 15 dBm) */
	u8 reserved;
पूर्ण __packed;

/**
 * Command TX_ANT_CONFIGURATION_CMD = 0x98
 * This command is used to configure valid Tx antenna.
 * By शेष uCode concludes the valid antenna according to the radio flavor.
 * This command enables the driver to override/modअगरy this conclusion.
 */
काष्ठा iwl_tx_ant_config_cmd अणु
	__le32 valid;
पूर्ण __packed;

/******************************************************************************
 * (0a)
 * Alive and Error Commands & Responses:
 *
 *****************************************************************************/

#घोषणा UCODE_VALID_OK	cpu_to_le32(0x1)

/**
 * REPLY_ALIVE = 0x1 (response only, not a command)
 *
 * uCode issues this "alive" notअगरication once the runसमय image is पढ़ोy
 * to receive commands from the driver.  This is the *second* "alive"
 * notअगरication that the driver will receive after rebooting uCode;
 * this "alive" is indicated by subtype field != 9.
 *
 * See comments करोcumenting "BSM" (bootstrap state machine).
 *
 * This response includes two poपूर्णांकers to काष्ठाures within the device's
 * data SRAM (access via HBUS_TARG_MEM_* regs) that are useful क्रम debugging:
 *
 * 1)  log_event_table_ptr indicates base of the event log.  This traces
 *     a 256-entry history of uCode execution within a circular buffer.
 *     Its header क्रमmat is:
 *
 *	__le32 log_size;     log capacity (in number of entries)
 *	__le32 type;         (1) बारtamp with each entry, (0) no बारtamp
 *	__le32 wraps;        # बार uCode has wrapped to top of circular buffer
 *      __le32 ग_लिखो_index;  next circular buffer entry that uCode would fill
 *
 *     The header is followed by the circular buffer of log entries.  Entries
 *     with बारtamps have the following क्रमmat:
 *
 *	__le32 event_id;     range 0 - 1500
 *	__le32 बारtamp;    low 32 bits of TSF (of network, अगर associated)
 *	__le32 data;         event_id-specअगरic data value
 *
 *     Entries without बारtamps contain only event_id and data.
 *
 *
 * 2)  error_event_table_ptr indicates base of the error log.  This contains
 *     inक्रमmation about any uCode error that occurs.  For agn, the क्रमmat
 *     of the error log is defined by काष्ठा iwl_error_event_table.
 *
 * The Linux driver can prपूर्णांक both logs to the प्रणाली log when a uCode error
 * occurs.
 */

/*
 * Note: This काष्ठाure is पढ़ो from the device with IO accesses,
 * and the पढ़ोing alपढ़ोy करोes the endian conversion. As it is
 * पढ़ो with u32-sized accesses, any members with a dअगरferent size
 * need to be ordered correctly though!
 */
काष्ठा iwl_error_event_table अणु
	u32 valid;		/* (nonzero) valid, (0) log is empty */
	u32 error_id;		/* type of error */
	u32 pc;			/* program counter */
	u32 blink1;		/* branch link */
	u32 blink2;		/* branch link */
	u32 ilink1;		/* पूर्णांकerrupt link */
	u32 ilink2;		/* पूर्णांकerrupt link */
	u32 data1;		/* error-specअगरic data */
	u32 data2;		/* error-specअगरic data */
	u32 line;		/* source code line of error */
	u32 bcon_समय;		/* beacon समयr */
	u32 tsf_low;		/* network बारtamp function समयr */
	u32 tsf_hi;		/* network बारtamp function समयr */
	u32 gp1;		/* GP1 समयr रेजिस्टर */
	u32 gp2;		/* GP2 समयr रेजिस्टर */
	u32 gp3;		/* GP3 समयr रेजिस्टर */
	u32 ucode_ver;		/* uCode version */
	u32 hw_ver;		/* HW Silicon version */
	u32 brd_ver;		/* HW board version */
	u32 log_pc;		/* log program counter */
	u32 frame_ptr;		/* frame poपूर्णांकer */
	u32 stack_ptr;		/* stack poपूर्णांकer */
	u32 hcmd;		/* last host command header */
	u32 isr0;		/* isr status रेजिस्टर LMPM_NIC_ISR0:
				 * rxtx_flag */
	u32 isr1;		/* isr status रेजिस्टर LMPM_NIC_ISR1:
				 * host_flag */
	u32 isr2;		/* isr status रेजिस्टर LMPM_NIC_ISR2:
				 * enc_flag */
	u32 isr3;		/* isr status रेजिस्टर LMPM_NIC_ISR3:
				 * समय_flag */
	u32 isr4;		/* isr status रेजिस्टर LMPM_NIC_ISR4:
				 * wico पूर्णांकerrupt */
	u32 isr_pref;		/* isr status रेजिस्टर LMPM_NIC_PREF_STAT */
	u32 रुको_event;		/* रुको event() caller address */
	u32 l2p_control;	/* L2pControlField */
	u32 l2p_duration;	/* L2pDurationField */
	u32 l2p_mhvalid;	/* L2pMhValidBits */
	u32 l2p_addr_match;	/* L2pAddrMatchStat */
	u32 lmpm_pmg_sel;	/* indicate which घड़ीs are turned on
				 * (LMPM_PMG_SEL) */
	u32 u_बारtamp;	/* indicate when the date and समय of the
				 * compilation */
	u32 flow_handler;	/* FH पढ़ो/ग_लिखो poपूर्णांकers, RX credit */
पूर्ण __packed;

काष्ठा iwl_alive_resp अणु
	u8 ucode_minor;
	u8 ucode_major;
	__le16 reserved1;
	u8 sw_rev[8];
	u8 ver_type;
	u8 ver_subtype;			/* not "9" क्रम runसमय alive */
	__le16 reserved2;
	__le32 log_event_table_ptr;	/* SRAM address क्रम event log */
	__le32 error_event_table_ptr;	/* SRAM address क्रम error log */
	__le32 बारtamp;
	__le32 is_valid;
पूर्ण __packed;

/*
 * REPLY_ERROR = 0x2 (response only, not a command)
 */
काष्ठा iwl_error_resp अणु
	__le32 error_type;
	u8 cmd_id;
	u8 reserved1;
	__le16 bad_cmd_seq_num;
	__le32 error_info;
	__le64 बारtamp;
पूर्ण __packed;

/******************************************************************************
 * (1)
 * RXON Commands & Responses:
 *
 *****************************************************************************/

/*
 * Rx config defines & काष्ठाure
 */
/* rx_config device types  */
क्रमागत अणु
	RXON_DEV_TYPE_AP = 1,
	RXON_DEV_TYPE_ESS = 3,
	RXON_DEV_TYPE_IBSS = 4,
	RXON_DEV_TYPE_SNIFFER = 6,
	RXON_DEV_TYPE_CP = 7,
	RXON_DEV_TYPE_2STA = 8,
	RXON_DEV_TYPE_P2P = 9,
पूर्ण;


#घोषणा RXON_RX_CHAIN_DRIVER_FORCE_MSK		cpu_to_le16(0x1 << 0)
#घोषणा RXON_RX_CHAIN_DRIVER_FORCE_POS		(0)
#घोषणा RXON_RX_CHAIN_VALID_MSK			cpu_to_le16(0x7 << 1)
#घोषणा RXON_RX_CHAIN_VALID_POS			(1)
#घोषणा RXON_RX_CHAIN_FORCE_SEL_MSK		cpu_to_le16(0x7 << 4)
#घोषणा RXON_RX_CHAIN_FORCE_SEL_POS		(4)
#घोषणा RXON_RX_CHAIN_FORCE_MIMO_SEL_MSK	cpu_to_le16(0x7 << 7)
#घोषणा RXON_RX_CHAIN_FORCE_MIMO_SEL_POS	(7)
#घोषणा RXON_RX_CHAIN_CNT_MSK			cpu_to_le16(0x3 << 10)
#घोषणा RXON_RX_CHAIN_CNT_POS			(10)
#घोषणा RXON_RX_CHAIN_MIMO_CNT_MSK		cpu_to_le16(0x3 << 12)
#घोषणा RXON_RX_CHAIN_MIMO_CNT_POS		(12)
#घोषणा RXON_RX_CHAIN_MIMO_FORCE_MSK		cpu_to_le16(0x1 << 14)
#घोषणा RXON_RX_CHAIN_MIMO_FORCE_POS		(14)

/* rx_config flags */
/* band & modulation selection */
#घोषणा RXON_FLG_BAND_24G_MSK           cpu_to_le32(1 << 0)
#घोषणा RXON_FLG_CCK_MSK                cpu_to_le32(1 << 1)
/* स्वतः detection enable */
#घोषणा RXON_FLG_AUTO_DETECT_MSK        cpu_to_le32(1 << 2)
/* TGg protection when tx */
#घोषणा RXON_FLG_TGG_PROTECT_MSK        cpu_to_le32(1 << 3)
/* cck लघु slot & preamble */
#घोषणा RXON_FLG_SHORT_SLOT_MSK          cpu_to_le32(1 << 4)
#घोषणा RXON_FLG_SHORT_PREAMBLE_MSK     cpu_to_le32(1 << 5)
/* antenna selection */
#घोषणा RXON_FLG_DIS_DIV_MSK            cpu_to_le32(1 << 7)
#घोषणा RXON_FLG_ANT_SEL_MSK            cpu_to_le32(0x0f00)
#घोषणा RXON_FLG_ANT_A_MSK              cpu_to_le32(1 << 8)
#घोषणा RXON_FLG_ANT_B_MSK              cpu_to_le32(1 << 9)
/* radar detection enable */
#घोषणा RXON_FLG_RADAR_DETECT_MSK       cpu_to_le32(1 << 12)
#घोषणा RXON_FLG_TGJ_NARROW_BAND_MSK    cpu_to_le32(1 << 13)
/* rx response to host with 8-byte TSF
* (according to ON_AIR deनिश्चितion) */
#घोषणा RXON_FLG_TSF2HOST_MSK           cpu_to_le32(1 << 15)


/* HT flags */
#घोषणा RXON_FLG_CTRL_CHANNEL_LOC_POS		(22)
#घोषणा RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK	cpu_to_le32(0x1 << 22)

#घोषणा RXON_FLG_HT_OPERATING_MODE_POS		(23)

#घोषणा RXON_FLG_HT_PROT_MSK			cpu_to_le32(0x1 << 23)
#घोषणा RXON_FLG_HT40_PROT_MSK			cpu_to_le32(0x2 << 23)

#घोषणा RXON_FLG_CHANNEL_MODE_POS		(25)
#घोषणा RXON_FLG_CHANNEL_MODE_MSK		cpu_to_le32(0x3 << 25)

/* channel mode */
क्रमागत अणु
	CHANNEL_MODE_LEGACY = 0,
	CHANNEL_MODE_PURE_40 = 1,
	CHANNEL_MODE_MIXED = 2,
	CHANNEL_MODE_RESERVED = 3,
पूर्ण;
#घोषणा RXON_FLG_CHANNEL_MODE_LEGACY	cpu_to_le32(CHANNEL_MODE_LEGACY << RXON_FLG_CHANNEL_MODE_POS)
#घोषणा RXON_FLG_CHANNEL_MODE_PURE_40	cpu_to_le32(CHANNEL_MODE_PURE_40 << RXON_FLG_CHANNEL_MODE_POS)
#घोषणा RXON_FLG_CHANNEL_MODE_MIXED	cpu_to_le32(CHANNEL_MODE_MIXED << RXON_FLG_CHANNEL_MODE_POS)

/* CTS to self (अगर spec allows) flag */
#घोषणा RXON_FLG_SELF_CTS_EN			cpu_to_le32(0x1<<30)

/* rx_config filter flags */
/* accept all data frames */
#घोषणा RXON_FILTER_PROMISC_MSK         cpu_to_le32(1 << 0)
/* pass control & management to host */
#घोषणा RXON_FILTER_CTL2HOST_MSK        cpu_to_le32(1 << 1)
/* accept multi-cast */
#घोषणा RXON_FILTER_ACCEPT_GRP_MSK      cpu_to_le32(1 << 2)
/* करोn't decrypt uni-cast frames */
#घोषणा RXON_FILTER_DIS_DECRYPT_MSK     cpu_to_le32(1 << 3)
/* करोn't decrypt multi-cast frames */
#घोषणा RXON_FILTER_DIS_GRP_DECRYPT_MSK cpu_to_le32(1 << 4)
/* STA is associated */
#घोषणा RXON_FILTER_ASSOC_MSK           cpu_to_le32(1 << 5)
/* transfer to host non bssid beacons in associated state */
#घोषणा RXON_FILTER_BCON_AWARE_MSK      cpu_to_le32(1 << 6)

/**
 * REPLY_RXON = 0x10 (command, has simple generic response)
 *
 * RXON tunes the radio tuner to a service channel, and sets up a number
 * of parameters that are used primarily क्रम Rx, but also क्रम Tx operations.
 *
 * NOTE:  When tuning to a new channel, driver must set the
 *        RXON_FILTER_ASSOC_MSK to 0.  This will clear station-dependent
 *        info within the device, including the station tables, tx retry
 *        rate tables, and txघातer tables.  Driver must build a new station
 *        table and txघातer table beक्रमe transmitting anything on the RXON
 *        channel.
 *
 * NOTE:  All RXONs wipe clean the पूर्णांकernal txघातer table.  Driver must
 *        issue a new REPLY_TX_PWR_TABLE_CMD after each REPLY_RXON (0x10),
 *        regardless of whether RXON_FILTER_ASSOC_MSK is set.
 */

काष्ठा iwl_rxon_cmd अणु
	u8 node_addr[6];
	__le16 reserved1;
	u8 bssid_addr[6];
	__le16 reserved2;
	u8 wlap_bssid_addr[6];
	__le16 reserved3;
	u8 dev_type;
	u8 air_propagation;
	__le16 rx_chain;
	u8 ofdm_basic_rates;
	u8 cck_basic_rates;
	__le16 assoc_id;
	__le32 flags;
	__le32 filter_flags;
	__le16 channel;
	u8 ofdm_ht_single_stream_basic_rates;
	u8 ofdm_ht_dual_stream_basic_rates;
	u8 ofdm_ht_triple_stream_basic_rates;
	u8 reserved5;
	__le16 acquisition_data;
	__le16 reserved6;
पूर्ण __packed;

/*
 * REPLY_RXON_ASSOC = 0x11 (command, has simple generic response)
 */
काष्ठा iwl_rxon_assoc_cmd अणु
	__le32 flags;
	__le32 filter_flags;
	u8 ofdm_basic_rates;
	u8 cck_basic_rates;
	__le16 reserved1;
	u8 ofdm_ht_single_stream_basic_rates;
	u8 ofdm_ht_dual_stream_basic_rates;
	u8 ofdm_ht_triple_stream_basic_rates;
	u8 reserved2;
	__le16 rx_chain_select_flags;
	__le16 acquisition_data;
	__le32 reserved3;
पूर्ण __packed;

#घोषणा IWL_CONN_MAX_LISTEN_INTERVAL	10
#घोषणा IWL_MAX_UCODE_BEACON_INTERVAL	4 /* 4096 */

/*
 * REPLY_RXON_TIMING = 0x14 (command, has simple generic response)
 */
काष्ठा iwl_rxon_समय_cmd अणु
	__le64 बारtamp;
	__le16 beacon_पूर्णांकerval;
	__le16 atim_winकरोw;
	__le32 beacon_init_val;
	__le16 listen_पूर्णांकerval;
	u8 dtim_period;
	u8 delta_cp_bss_tbtts;
पूर्ण __packed;

/*
 * REPLY_CHANNEL_SWITCH = 0x72 (command, has simple generic response)
 */
/**
 * काष्ठा iwl5000_channel_चयन_cmd
 * @band: 0- 5.2GHz, 1- 2.4GHz
 * @expect_beacon: 0- resume transmits after channel चयन
 *		   1- रुको क्रम beacon to resume transmits
 * @channel: new channel number
 * @rxon_flags: Rx on flags
 * @rxon_filter_flags: filtering parameters
 * @चयन_समय: चयन समय in extended beacon क्रमmat
 * @reserved: reserved bytes
 */
काष्ठा iwl5000_channel_चयन_cmd अणु
	u8 band;
	u8 expect_beacon;
	__le16 channel;
	__le32 rxon_flags;
	__le32 rxon_filter_flags;
	__le32 चयन_समय;
	__le32 reserved[2][IWL_PWR_NUM_HT_OFDM_ENTRIES + IWL_PWR_CCK_ENTRIES];
पूर्ण __packed;

/**
 * काष्ठा iwl6000_channel_चयन_cmd
 * @band: 0- 5.2GHz, 1- 2.4GHz
 * @expect_beacon: 0- resume transmits after channel चयन
 *		   1- रुको क्रम beacon to resume transmits
 * @channel: new channel number
 * @rxon_flags: Rx on flags
 * @rxon_filter_flags: filtering parameters
 * @चयन_समय: चयन समय in extended beacon क्रमmat
 * @reserved: reserved bytes
 */
काष्ठा iwl6000_channel_चयन_cmd अणु
	u8 band;
	u8 expect_beacon;
	__le16 channel;
	__le32 rxon_flags;
	__le32 rxon_filter_flags;
	__le32 चयन_समय;
	__le32 reserved[3][IWL_PWR_NUM_HT_OFDM_ENTRIES + IWL_PWR_CCK_ENTRIES];
पूर्ण __packed;

/*
 * CHANNEL_SWITCH_NOTIFICATION = 0x73 (notअगरication only, not a command)
 */
काष्ठा iwl_csa_notअगरication अणु
	__le16 band;
	__le16 channel;
	__le32 status;		/* 0 - OK, 1 - fail */
पूर्ण __packed;

/******************************************************************************
 * (2)
 * Quality-of-Service (QOS) Commands & Responses:
 *
 *****************************************************************************/

/**
 * काष्ठा iwl_ac_qos -- QOS timing params क्रम REPLY_QOS_PARAM
 * One क्रम each of 4 EDCA access categories in काष्ठा iwl_qosparam_cmd
 *
 * @cw_min: Contention winकरोw, start value in numbers of slots.
 *          Should be a घातer-of-2, minus 1.  Device's शेष is 0x0f.
 * @cw_max: Contention winकरोw, max value in numbers of slots.
 *          Should be a घातer-of-2, minus 1.  Device's शेष is 0x3f.
 * @aअगरsn:  Number of slots in Arbitration Interframe Space (beक्रमe
 *          perक्रमming अक्रमom backoff timing prior to Tx).  Device शेष 1.
 * @edca_txop:  Length of Tx opportunity, in uSecs.  Device शेष is 0.
 *
 * Device will स्वतःmatically increase contention winकरोw by (2*CW) + 1 क्रम each
 * transmission retry.  Device uses cw_max as a bit mask, ANDed with new CW
 * value, to cap the CW value.
 */
काष्ठा iwl_ac_qos अणु
	__le16 cw_min;
	__le16 cw_max;
	u8 aअगरsn;
	u8 reserved1;
	__le16 edca_txop;
पूर्ण __packed;

/* QoS flags defines */
#घोषणा QOS_PARAM_FLG_UPDATE_EDCA_MSK	cpu_to_le32(0x01)
#घोषणा QOS_PARAM_FLG_TGN_MSK		cpu_to_le32(0x02)
#घोषणा QOS_PARAM_FLG_TXOP_TYPE_MSK	cpu_to_le32(0x10)

/* Number of Access Categories (AC) (EDCA), queues 0..3 */
#घोषणा AC_NUM                4

/*
 * REPLY_QOS_PARAM = 0x13 (command, has simple generic response)
 *
 * This command sets up timings क्रम each of the 4 prioritized EDCA Tx FIFOs
 * 0: Background, 1: Best Efक्रमt, 2: Video, 3: Voice.
 */
काष्ठा iwl_qosparam_cmd अणु
	__le32 qos_flags;
	काष्ठा iwl_ac_qos ac[AC_NUM];
पूर्ण __packed;

/******************************************************************************
 * (3)
 * Add/Modअगरy Stations Commands & Responses:
 *
 *****************************************************************************/
/*
 * Multi station support
 */

/* Special, dedicated locations within device's station table */
#घोषणा	IWL_AP_ID		0
#घोषणा	IWL_AP_ID_PAN		1
#घोषणा	IWL_STA_ID		2
#घोषणा IWLAGN_PAN_BCAST_ID	14
#घोषणा IWLAGN_BROADCAST_ID	15
#घोषणा	IWLAGN_STATION_COUNT	16

#घोषणा IWL_TID_NON_QOS IWL_MAX_TID_COUNT

#घोषणा STA_FLG_TX_RATE_MSK		cpu_to_le32(1 << 2)
#घोषणा STA_FLG_PWR_SAVE_MSK		cpu_to_le32(1 << 8)
#घोषणा STA_FLG_PAN_STATION		cpu_to_le32(1 << 13)
#घोषणा STA_FLG_RTS_MIMO_PROT_MSK	cpu_to_le32(1 << 17)
#घोषणा STA_FLG_AGG_MPDU_8US_MSK	cpu_to_le32(1 << 18)
#घोषणा STA_FLG_MAX_AGG_SIZE_POS	(19)
#घोषणा STA_FLG_MAX_AGG_SIZE_MSK	cpu_to_le32(3 << 19)
#घोषणा STA_FLG_HT40_EN_MSK		cpu_to_le32(1 << 21)
#घोषणा STA_FLG_MIMO_DIS_MSK		cpu_to_le32(1 << 22)
#घोषणा STA_FLG_AGG_MPDU_DENSITY_POS	(23)
#घोषणा STA_FLG_AGG_MPDU_DENSITY_MSK	cpu_to_le32(7 << 23)

/* Use in mode field.  1: modअगरy existing entry, 0: add new station entry */
#घोषणा STA_CONTROL_MODIFY_MSK		0x01

/* key flags __le16*/
#घोषणा STA_KEY_FLG_ENCRYPT_MSK	cpu_to_le16(0x0007)
#घोषणा STA_KEY_FLG_NO_ENC	cpu_to_le16(0x0000)
#घोषणा STA_KEY_FLG_WEP		cpu_to_le16(0x0001)
#घोषणा STA_KEY_FLG_CCMP	cpu_to_le16(0x0002)
#घोषणा STA_KEY_FLG_TKIP	cpu_to_le16(0x0003)

#घोषणा STA_KEY_FLG_KEYID_POS	8
#घोषणा STA_KEY_FLG_INVALID 	cpu_to_le16(0x0800)
/* wep key is either from global key (0) or from station info array (1) */
#घोषणा STA_KEY_FLG_MAP_KEY_MSK	cpu_to_le16(0x0008)

/* wep key in STA: 5-bytes (0) or 13-bytes (1) */
#घोषणा STA_KEY_FLG_KEY_SIZE_MSK     cpu_to_le16(0x1000)
#घोषणा STA_KEY_MULTICAST_MSK        cpu_to_le16(0x4000)
#घोषणा STA_KEY_MAX_NUM		8
#घोषणा STA_KEY_MAX_NUM_PAN	16
/* must not match WEP_INVALID_OFFSET */
#घोषणा IWLAGN_HW_KEY_DEFAULT	0xfe

/* Flags indicate whether to modअगरy vs. करोn't change various station params */
#घोषणा	STA_MODIFY_KEY_MASK		0x01
#घोषणा	STA_MODIFY_TID_DISABLE_TX	0x02
#घोषणा	STA_MODIFY_TX_RATE_MSK		0x04
#घोषणा STA_MODIFY_ADDBA_TID_MSK	0x08
#घोषणा STA_MODIFY_DELBA_TID_MSK	0x10
#घोषणा STA_MODIFY_SLEEP_TX_COUNT_MSK	0x20

/* agn */
काष्ठा iwl_keyinfo अणु
	__le16 key_flags;
	u8 tkip_rx_tsc_byte2;	/* TSC[2] क्रम key mix ph1 detection */
	u8 reserved1;
	__le16 tkip_rx_ttak[5];	/* 10-byte unicast TKIP TTAK */
	u8 key_offset;
	u8 reserved2;
	u8 key[16];		/* 16-byte unicast decryption key */
	__le64 tx_secur_seq_cnt;
	__le64 hw_tkip_mic_rx_key;
	__le64 hw_tkip_mic_tx_key;
पूर्ण __packed;

/**
 * काष्ठा sta_id_modअगरy
 * @addr[ETH_ALEN]: station's MAC address
 * @sta_id: index of station in uCode's station table
 * @modअगरy_mask: STA_MODIFY_*, 1: modअगरy, 0: करोn't change
 *
 * Driver selects unused table index when adding new station,
 * or the index to a pre-existing station entry when modअगरying that station.
 * Some indexes have special purposes (IWL_AP_ID, index 0, is क्रम AP).
 *
 * modअगरy_mask flags select which parameters to modअगरy vs. leave alone.
 */
काष्ठा sta_id_modअगरy अणु
	u8 addr[ETH_ALEN];
	__le16 reserved1;
	u8 sta_id;
	u8 modअगरy_mask;
	__le16 reserved2;
पूर्ण __packed;

/*
 * REPLY_ADD_STA = 0x18 (command)
 *
 * The device contains an पूर्णांकernal table of per-station inक्रमmation,
 * with info on security keys, aggregation parameters, and Tx rates क्रम
 * initial Tx attempt and any retries (agn devices uses
 * REPLY_TX_LINK_QUALITY_CMD,
 *
 * REPLY_ADD_STA sets up the table entry क्रम one station, either creating
 * a new entry, or modअगरying a pre-existing one.
 *
 * NOTE:  RXON command (without "associated" bit set) wipes the station table
 *        clean.  Moving पूर्णांकo RF_KILL state करोes this also.  Driver must set up
 *        new station table beक्रमe transmitting anything on the RXON channel
 *        (except active scans or active measurements; those commands carry
 *        their own txघातer/rate setup data).
 *
 *        When getting started on a new channel, driver must set up the
 *        IWL_BROADCAST_ID entry (last entry in the table).  For a client
 *        station in a BSS, once an AP is selected, driver sets up the AP STA
 *        in the IWL_AP_ID entry (1st entry in the table).  BROADCAST and AP
 *        are all that are needed क्रम a BSS client station.  If the device is
 *        used as AP, or in an IBSS network, driver must set up station table
 *        entries क्रम all STAs in network, starting with index IWL_STA_ID.
 */

काष्ठा iwl_addsta_cmd अणु
	u8 mode;		/* 1: modअगरy existing, 0: add new station */
	u8 reserved[3];
	काष्ठा sta_id_modअगरy sta;
	काष्ठा iwl_keyinfo key;
	__le32 station_flags;		/* STA_FLG_* */
	__le32 station_flags_msk;	/* STA_FLG_* */

	/* bit field to disable (1) or enable (0) Tx क्रम Traffic ID (TID)
	 * corresponding to bit (e.g. bit 5 controls TID 5).
	 * Set modअगरy_mask bit STA_MODIFY_TID_DISABLE_TX to use this field. */
	__le16 tid_disable_tx;
	__le16 legacy_reserved;

	/* TID क्रम which to add block-ack support.
	 * Set modअगरy_mask bit STA_MODIFY_ADDBA_TID_MSK to use this field. */
	u8 add_immediate_ba_tid;

	/* TID क्रम which to हटाओ block-ack support.
	 * Set modअगरy_mask bit STA_MODIFY_DELBA_TID_MSK to use this field. */
	u8 हटाओ_immediate_ba_tid;

	/* Starting Sequence Number क्रम added block-ack support.
	 * Set modअगरy_mask bit STA_MODIFY_ADDBA_TID_MSK to use this field. */
	__le16 add_immediate_ba_ssn;

	/*
	 * Number of packets OK to transmit to station even though
	 * it is asleep -- used to synchronise PS-poll and u-APSD
	 * responses जबतक ucode keeps track of STA sleep state.
	 */
	__le16 sleep_tx_count;

	__le16 reserved2;
पूर्ण __packed;


#घोषणा ADD_STA_SUCCESS_MSK		0x1
#घोषणा ADD_STA_NO_ROOM_IN_TABLE	0x2
#घोषणा ADD_STA_NO_BLOCK_ACK_RESOURCE	0x4
#घोषणा ADD_STA_MODIFY_NON_EXIST_STA	0x8
/*
 * REPLY_ADD_STA = 0x18 (response)
 */
काष्ठा iwl_add_sta_resp अणु
	u8 status;	/* ADD_STA_* */
पूर्ण __packed;

#घोषणा REM_STA_SUCCESS_MSK              0x1
/*
 *  REPLY_REM_STA = 0x19 (response)
 */
काष्ठा iwl_rem_sta_resp अणु
	u8 status;
पूर्ण __packed;

/*
 *  REPLY_REM_STA = 0x19 (command)
 */
काष्ठा iwl_rem_sta_cmd अणु
	u8 num_sta;     /* number of हटाओd stations */
	u8 reserved[3];
	u8 addr[ETH_ALEN]; /* MAC addr of the first station */
	u8 reserved2[2];
पूर्ण __packed;


/* WiFi queues mask */
#घोषणा IWL_SCD_BK_MSK			BIT(0)
#घोषणा IWL_SCD_BE_MSK			BIT(1)
#घोषणा IWL_SCD_VI_MSK			BIT(2)
#घोषणा IWL_SCD_VO_MSK			BIT(3)
#घोषणा IWL_SCD_MGMT_MSK		BIT(3)

/* PAN queues mask */
#घोषणा IWL_PAN_SCD_BK_MSK		BIT(4)
#घोषणा IWL_PAN_SCD_BE_MSK		BIT(5)
#घोषणा IWL_PAN_SCD_VI_MSK		BIT(6)
#घोषणा IWL_PAN_SCD_VO_MSK		BIT(7)
#घोषणा IWL_PAN_SCD_MGMT_MSK		BIT(7)
#घोषणा IWL_PAN_SCD_MULTICAST_MSK	BIT(8)

#घोषणा IWL_AGG_TX_QUEUE_MSK		0xffc00

#घोषणा IWL_DROP_ALL			BIT(1)

/*
 * REPLY_TXFIFO_FLUSH = 0x1e(command and response)
 *
 * When using full FIFO flush this command checks the scheduler HW block WR/RD
 * poपूर्णांकers to check अगर all the frames were transferred by DMA पूर्णांकo the
 * relevant TX FIFO queue. Only when the DMA is finished and the queue is
 * empty the command can finish.
 * This command is used to flush the TXFIFO from transmit commands, it may
 * operate on single or multiple queues, the command queue can't be flushed by
 * this command. The command response is वापसed when all the queue flush
 * operations are करोne. Each TX command flushed वापस response with the FLUSH
 * status set in the TX response status. When FIFO flush operation is used,
 * the flush operation ends when both the scheduler DMA करोne and TXFIFO empty
 * are set.
 *
 * @queue_control: bit mask क्रम which queues to flush
 * @flush_control: flush controls
 *	0: Dump single MSDU
 *	1: Dump multiple MSDU according to PS, INVALID STA, TTL, TID disable.
 *	2: Dump all FIFO
 */
काष्ठा iwl_txfअगरo_flush_cmd_v3 अणु
	__le32 queue_control;
	__le16 flush_control;
	__le16 reserved;
पूर्ण __packed;

काष्ठा iwl_txfअगरo_flush_cmd_v2 अणु
	__le16 queue_control;
	__le16 flush_control;
पूर्ण __packed;

/*
 * REPLY_WEP_KEY = 0x20
 */
काष्ठा iwl_wep_key अणु
	u8 key_index;
	u8 key_offset;
	u8 reserved1[2];
	u8 key_size;
	u8 reserved2[3];
	u8 key[16];
पूर्ण __packed;

काष्ठा iwl_wep_cmd अणु
	u8 num_keys;
	u8 global_key_type;
	u8 flags;
	u8 reserved;
	काष्ठा iwl_wep_key key[];
पूर्ण __packed;

#घोषणा WEP_KEY_WEP_TYPE 1
#घोषणा WEP_KEYS_MAX 4
#घोषणा WEP_INVALID_OFFSET 0xff
#घोषणा WEP_KEY_LEN_64 5
#घोषणा WEP_KEY_LEN_128 13

/******************************************************************************
 * (4)
 * Rx Responses:
 *
 *****************************************************************************/

#घोषणा RX_RES_STATUS_NO_CRC32_ERROR	cpu_to_le32(1 << 0)
#घोषणा RX_RES_STATUS_NO_RXE_OVERFLOW	cpu_to_le32(1 << 1)

#घोषणा RX_RES_PHY_FLAGS_BAND_24_MSK	cpu_to_le16(1 << 0)
#घोषणा RX_RES_PHY_FLAGS_MOD_CCK_MSK		cpu_to_le16(1 << 1)
#घोषणा RX_RES_PHY_FLAGS_SHORT_PREAMBLE_MSK	cpu_to_le16(1 << 2)
#घोषणा RX_RES_PHY_FLAGS_NARROW_BAND_MSK	cpu_to_le16(1 << 3)
#घोषणा RX_RES_PHY_FLAGS_ANTENNA_MSK		0x70
#घोषणा RX_RES_PHY_FLAGS_ANTENNA_POS		4
#घोषणा RX_RES_PHY_FLAGS_AGG_MSK		cpu_to_le16(1 << 7)

#घोषणा RX_RES_STATUS_SEC_TYPE_MSK	(0x7 << 8)
#घोषणा RX_RES_STATUS_SEC_TYPE_NONE	(0x0 << 8)
#घोषणा RX_RES_STATUS_SEC_TYPE_WEP	(0x1 << 8)
#घोषणा RX_RES_STATUS_SEC_TYPE_CCMP	(0x2 << 8)
#घोषणा RX_RES_STATUS_SEC_TYPE_TKIP	(0x3 << 8)
#घोषणा	RX_RES_STATUS_SEC_TYPE_ERR	(0x7 << 8)

#घोषणा RX_RES_STATUS_STATION_FOUND	(1<<6)
#घोषणा RX_RES_STATUS_NO_STATION_INFO_MISMATCH	(1<<7)

#घोषणा RX_RES_STATUS_DECRYPT_TYPE_MSK	(0x3 << 11)
#घोषणा RX_RES_STATUS_NOT_DECRYPT	(0x0 << 11)
#घोषणा RX_RES_STATUS_DECRYPT_OK	(0x3 << 11)
#घोषणा RX_RES_STATUS_BAD_ICV_MIC	(0x1 << 11)
#घोषणा RX_RES_STATUS_BAD_KEY_TTAK	(0x2 << 11)

#घोषणा RX_MPDU_RES_STATUS_ICV_OK	(0x20)
#घोषणा RX_MPDU_RES_STATUS_MIC_OK	(0x40)
#घोषणा RX_MPDU_RES_STATUS_TTAK_OK	(1 << 7)
#घोषणा RX_MPDU_RES_STATUS_DEC_DONE_MSK	(0x800)


#घोषणा IWLAGN_RX_RES_PHY_CNT 8
#घोषणा IWLAGN_RX_RES_AGC_IDX     1
#घोषणा IWLAGN_RX_RES_RSSI_AB_IDX 2
#घोषणा IWLAGN_RX_RES_RSSI_C_IDX  3
#घोषणा IWLAGN_OFDM_AGC_MSK 0xfe00
#घोषणा IWLAGN_OFDM_AGC_BIT_POS 9
#घोषणा IWLAGN_OFDM_RSSI_INBAND_A_BITMSK 0x00ff
#घोषणा IWLAGN_OFDM_RSSI_ALLBAND_A_BITMSK 0xff00
#घोषणा IWLAGN_OFDM_RSSI_A_BIT_POS 0
#घोषणा IWLAGN_OFDM_RSSI_INBAND_B_BITMSK 0xff0000
#घोषणा IWLAGN_OFDM_RSSI_ALLBAND_B_BITMSK 0xff000000
#घोषणा IWLAGN_OFDM_RSSI_B_BIT_POS 16
#घोषणा IWLAGN_OFDM_RSSI_INBAND_C_BITMSK 0x00ff
#घोषणा IWLAGN_OFDM_RSSI_ALLBAND_C_BITMSK 0xff00
#घोषणा IWLAGN_OFDM_RSSI_C_BIT_POS 0

काष्ठा iwlagn_non_cfg_phy अणु
	__le32 non_cfg_phy[IWLAGN_RX_RES_PHY_CNT];  /* up to 8 phy entries */
पूर्ण __packed;


/*
 * REPLY_RX = 0xc3 (response only, not a command)
 * Used only क्रम legacy (non 11n) frames.
 */
काष्ठा iwl_rx_phy_res अणु
	u8 non_cfg_phy_cnt;     /* non configurable DSP phy data byte count */
	u8 cfg_phy_cnt;		/* configurable DSP phy data byte count */
	u8 stat_id;		/* configurable DSP phy data set ID */
	u8 reserved1;
	__le64 बारtamp;	/* TSF at on air rise */
	__le32 beacon_समय_stamp; /* beacon at on-air rise */
	__le16 phy_flags;	/* general phy flags: band, modulation, ... */
	__le16 channel;		/* channel number */
	u8 non_cfg_phy_buf[32]; /* क्रम various implementations of non_cfg_phy */
	__le32 rate_n_flags;	/* RATE_MCS_* */
	__le16 byte_count;	/* frame's byte-count */
	__le16 frame_समय;	/* frame's समय on the air */
पूर्ण __packed;

काष्ठा iwl_rx_mpdu_res_start अणु
	__le16 byte_count;
	__le16 reserved;
पूर्ण __packed;


/******************************************************************************
 * (5)
 * Tx Commands & Responses:
 *
 * Driver must place each REPLY_TX command पूर्णांकo one of the prioritized Tx
 * queues in host DRAM, shared between driver and device (see comments क्रम
 * SCD रेजिस्टरs and Tx/Rx Queues).  When the device's Tx scheduler and uCode
 * are preparing to transmit, the device pulls the Tx command over the PCI
 * bus via one of the device's Tx DMA channels, to fill an पूर्णांकernal FIFO
 * from which data will be transmitted.
 *
 * uCode handles all timing and protocol related to control frames
 * (RTS/CTS/ACK), based on flags in the Tx command.  uCode and Tx scheduler
 * handle reception of block-acks; uCode updates the host driver via
 * REPLY_COMPRESSED_BA.
 *
 * uCode handles retrying Tx when an ACK is expected but not received.
 * This includes trying lower data rates than the one requested in the Tx
 * command, as set up by the REPLY_TX_LINK_QUALITY_CMD (agn).
 *
 * Driver sets up transmit घातer क्रम various rates via REPLY_TX_PWR_TABLE_CMD.
 * This command must be executed after every RXON command, beक्रमe Tx can occur.
 *****************************************************************************/

/* REPLY_TX Tx flags field */

/*
 * 1: Use RTS/CTS protocol or CTS-to-self अगर spec allows it
 * beक्रमe this frame. अगर CTS-to-self required check
 * RXON_FLG_SELF_CTS_EN status.
 */
#घोषणा TX_CMD_FLG_PROT_REQUIRE_MSK cpu_to_le32(1 << 0)

/* 1: Expect ACK from receiving station
 * 0: Don't expect ACK (MAC header's duration field s/b 0)
 * Set this क्रम unicast frames, but not broadcast/multicast. */
#घोषणा TX_CMD_FLG_ACK_MSK cpu_to_le32(1 << 3)

/* For agn devices:
 * 1: Use rate scale table (see REPLY_TX_LINK_QUALITY_CMD).
 *    Tx command's initial_rate_index indicates first rate to try;
 *    uCode walks through table क्रम additional Tx attempts.
 * 0: Use Tx rate/MCS from Tx command's rate_n_flags field.
 *    This rate will be used क्रम all Tx attempts; it will not be scaled. */
#घोषणा TX_CMD_FLG_STA_RATE_MSK cpu_to_le32(1 << 4)

/* 1: Expect immediate block-ack.
 * Set when Txing a block-ack request frame.  Also set TX_CMD_FLG_ACK_MSK. */
#घोषणा TX_CMD_FLG_IMM_BA_RSP_MASK  cpu_to_le32(1 << 6)

/* Tx antenna selection field; reserved (0) क्रम agn devices. */
#घोषणा TX_CMD_FLG_ANT_SEL_MSK cpu_to_le32(0xf00)

/* 1: Ignore Bluetooth priority क्रम this frame.
 * 0: Delay Tx until Bluetooth device is करोne (normal usage). */
#घोषणा TX_CMD_FLG_IGNORE_BT cpu_to_le32(1 << 12)

/* 1: uCode overrides sequence control field in MAC header.
 * 0: Driver provides sequence control field in MAC header.
 * Set this क्रम management frames, non-QOS data frames, non-unicast frames,
 * and also in Tx command embedded in REPLY_SCAN_CMD क्रम active scans. */
#घोषणा TX_CMD_FLG_SEQ_CTL_MSK cpu_to_le32(1 << 13)

/* 1: This frame is non-last MPDU; more fragments are coming.
 * 0: Last fragment, or not using fragmentation. */
#घोषणा TX_CMD_FLG_MORE_FRAG_MSK cpu_to_le32(1 << 14)

/* 1: uCode calculates and inserts Timestamp Function (TSF) in outgoing frame.
 * 0: No TSF required in outgoing frame.
 * Set this क्रम transmitting beacons and probe responses. */
#घोषणा TX_CMD_FLG_TSF_MSK cpu_to_le32(1 << 16)

/* 1: Driver inserted 2 bytes pad after the MAC header, क्रम (required) dword
 *    alignment of frame's payload data field.
 * 0: No pad
 * Set this क्रम MAC headers with 26 or 30 bytes, i.e. those with QOS or ADDR4
 * field (but not both).  Driver must align frame data (i.e. data following
 * MAC header) to DWORD boundary. */
#घोषणा TX_CMD_FLG_MH_PAD_MSK cpu_to_le32(1 << 20)

/* accelerate aggregation support
 * 0 - no CCMP encryption; 1 - CCMP encryption */
#घोषणा TX_CMD_FLG_AGG_CCMP_MSK cpu_to_le32(1 << 22)

/* HCCA-AP - disable duration overwriting. */
#घोषणा TX_CMD_FLG_DUR_MSK cpu_to_le32(1 << 25)


/*
 * TX command security control
 */
#घोषणा TX_CMD_SEC_WEP  	0x01
#घोषणा TX_CMD_SEC_CCM  	0x02
#घोषणा TX_CMD_SEC_TKIP		0x03
#घोषणा TX_CMD_SEC_MSK		0x03
#घोषणा TX_CMD_SEC_SHIFT	6
#घोषणा TX_CMD_SEC_KEY128	0x08

/*
 * REPLY_TX = 0x1c (command)
 */

/*
 * Used क्रम managing Tx retries when expecting block-acks.
 * Driver should set these fields to 0.
 */
काष्ठा iwl_dram_scratch अणु
	u8 try_cnt;		/* Tx attempts */
	u8 bt_समाप्त_cnt;		/* Tx attempts blocked by Bluetooth device */
	__le16 reserved;
पूर्ण __packed;

काष्ठा iwl_tx_cmd अणु
	/*
	 * MPDU byte count:
	 * MAC header (24/26/30/32 bytes) + 2 bytes pad अगर 26/30 header size,
	 * + 8 byte IV क्रम CCM or TKIP (not used क्रम WEP)
	 * + Data payload
	 * + 8-byte MIC (not used क्रम CCM/WEP)
	 * NOTE:  Does not include Tx command bytes, post-MAC pad bytes,
	 *        MIC (CCM) 8 bytes, ICV (WEP/TKIP/CKIP) 4 bytes, CRC 4 bytes.i
	 * Range: 14-2342 bytes.
	 */
	__le16 len;

	/*
	 * MPDU or MSDU byte count क्रम next frame.
	 * Used क्रम fragmentation and bursting, but not 11n aggregation.
	 * Same as "len", but क्रम next frame.  Set to 0 अगर not applicable.
	 */
	__le16 next_frame_len;

	__le32 tx_flags;	/* TX_CMD_FLG_* */

	/* uCode may modअगरy this field of the Tx command (in host DRAM!).
	 * Driver must also set dram_lsb_ptr and dram_msb_ptr in this cmd. */
	काष्ठा iwl_dram_scratch scratch;

	/* Rate क्रम *all* Tx attempts, अगर TX_CMD_FLG_STA_RATE_MSK is cleared. */
	__le32 rate_n_flags;	/* RATE_MCS_* */

	/* Index of destination station in uCode's station table */
	u8 sta_id;

	/* Type of security encryption:  CCM or TKIP */
	u8 sec_ctl;		/* TX_CMD_SEC_* */

	/*
	 * Index पूर्णांकo rate table (see REPLY_TX_LINK_QUALITY_CMD) क्रम initial
	 * Tx attempt, अगर TX_CMD_FLG_STA_RATE_MSK is set.  Normally "0" क्रम
	 * data frames, this field may be used to selectively reduce initial
	 * rate (via non-0 value) क्रम special frames (e.g. management), जबतक
	 * still supporting rate scaling क्रम all frames.
	 */
	u8 initial_rate_index;
	u8 reserved;
	u8 key[16];
	__le16 next_frame_flags;
	__le16 reserved2;
	जोड़ अणु
		__le32 lअगरe_समय;
		__le32 attempt;
	पूर्ण stop_समय;

	/* Host DRAM physical address poपूर्णांकer to "scratch" in this command.
	 * Must be dword aligned.  "0" in dram_lsb_ptr disables usage. */
	__le32 dram_lsb_ptr;
	u8 dram_msb_ptr;

	u8 rts_retry_limit;	/*byte 50 */
	u8 data_retry_limit;	/*byte 51 */
	u8 tid_tspec;
	जोड़ अणु
		__le16 pm_frame_समयout;
		__le16 attempt_duration;
	पूर्ण समयout;

	/*
	 * Duration of EDCA burst Tx Opportunity, in 32-usec units.
	 * Set this अगर txop समय is not specअगरied by HCCA protocol (e.g. by AP).
	 */
	__le16 driver_txop;

	/*
	 * MAC header goes here, followed by 2 bytes padding अगर MAC header
	 * length is 26 or 30 bytes, followed by payload data
	 */
	u8 payload[0];
	काष्ठा ieee80211_hdr hdr[];
पूर्ण __packed;

/*
 * TX command response is sent after *agn* transmission attempts.
 *
 * both postpone and पात status are expected behavior from uCode. there is
 * no special operation required from driver; except क्रम RFKILL_FLUSH,
 * which required tx flush host command to flush all the tx frames in queues
 */
क्रमागत अणु
	TX_STATUS_SUCCESS = 0x01,
	TX_STATUS_सूचीECT_DONE = 0x02,
	/* postpone TX */
	TX_STATUS_POSTPONE_DELAY = 0x40,
	TX_STATUS_POSTPONE_FEW_BYTES = 0x41,
	TX_STATUS_POSTPONE_BT_PRIO = 0x42,
	TX_STATUS_POSTPONE_QUIET_PERIOD = 0x43,
	TX_STATUS_POSTPONE_CALC_TTAK = 0x44,
	/* पात TX */
	TX_STATUS_FAIL_INTERNAL_CROSSED_RETRY = 0x81,
	TX_STATUS_FAIL_SHORT_LIMIT = 0x82,
	TX_STATUS_FAIL_LONG_LIMIT = 0x83,
	TX_STATUS_FAIL_FIFO_UNDERRUN = 0x84,
	TX_STATUS_FAIL_DRAIN_FLOW = 0x85,
	TX_STATUS_FAIL_RFKILL_FLUSH = 0x86,
	TX_STATUS_FAIL_LIFE_EXPIRE = 0x87,
	TX_STATUS_FAIL_DEST_PS = 0x88,
	TX_STATUS_FAIL_HOST_ABORTED = 0x89,
	TX_STATUS_FAIL_BT_RETRY = 0x8a,
	TX_STATUS_FAIL_STA_INVALID = 0x8b,
	TX_STATUS_FAIL_FRAG_DROPPED = 0x8c,
	TX_STATUS_FAIL_TID_DISABLE = 0x8d,
	TX_STATUS_FAIL_FIFO_FLUSHED = 0x8e,
	TX_STATUS_FAIL_INSUFFICIENT_CF_POLL = 0x8f,
	TX_STATUS_FAIL_PASSIVE_NO_RX = 0x90,
	TX_STATUS_FAIL_NO_BEACON_ON_RADAR = 0x91,
पूर्ण;

#घोषणा	TX_PACKET_MODE_REGULAR		0x0000
#घोषणा	TX_PACKET_MODE_BURST_SEQ	0x0100
#घोषणा	TX_PACKET_MODE_BURST_FIRST	0x0200

क्रमागत अणु
	TX_POWER_PA_NOT_ACTIVE = 0x0,
पूर्ण;

क्रमागत अणु
	TX_STATUS_MSK = 0x000000ff,		/* bits 0:7 */
	TX_STATUS_DELAY_MSK = 0x00000040,
	TX_STATUS_ABORT_MSK = 0x00000080,
	TX_PACKET_MODE_MSK = 0x0000ff00,	/* bits 8:15 */
	TX_FIFO_NUMBER_MSK = 0x00070000,	/* bits 16:18 */
	TX_RESERVED = 0x00780000,		/* bits 19:22 */
	TX_POWER_PA_DETECT_MSK = 0x7f800000,	/* bits 23:30 */
	TX_ABORT_REQUIRED_MSK = 0x80000000,	/* bits 31:31 */
पूर्ण;

/* *******************************
 * TX aggregation status
 ******************************* */

क्रमागत अणु
	AGG_TX_STATE_TRANSMITTED = 0x00,
	AGG_TX_STATE_UNDERRUN_MSK = 0x01,
	AGG_TX_STATE_BT_PRIO_MSK = 0x02,
	AGG_TX_STATE_FEW_BYTES_MSK = 0x04,
	AGG_TX_STATE_ABORT_MSK = 0x08,
	AGG_TX_STATE_LAST_SENT_TTL_MSK = 0x10,
	AGG_TX_STATE_LAST_SENT_TRY_CNT_MSK = 0x20,
	AGG_TX_STATE_LAST_SENT_BT_KILL_MSK = 0x40,
	AGG_TX_STATE_SCD_QUERY_MSK = 0x80,
	AGG_TX_STATE_TEST_BAD_CRC32_MSK = 0x100,
	AGG_TX_STATE_RESPONSE_MSK = 0x1ff,
	AGG_TX_STATE_DUMP_TX_MSK = 0x200,
	AGG_TX_STATE_DELAY_TX_MSK = 0x400
पूर्ण;

#घोषणा AGG_TX_STATUS_MSK	0x00000fff	/* bits 0:11 */
#घोषणा AGG_TX_TRY_MSK		0x0000f000	/* bits 12:15 */
#घोषणा AGG_TX_TRY_POS		12

#घोषणा AGG_TX_STATE_LAST_SENT_MSK  (AGG_TX_STATE_LAST_SENT_TTL_MSK | \
				     AGG_TX_STATE_LAST_SENT_TRY_CNT_MSK | \
				     AGG_TX_STATE_LAST_SENT_BT_KILL_MSK)

/* # tx attempts क्रम first frame in aggregation */
#घोषणा AGG_TX_STATE_TRY_CNT_POS 12
#घोषणा AGG_TX_STATE_TRY_CNT_MSK 0xf000

/* Command ID and sequence number of Tx command क्रम this frame */
#घोषणा AGG_TX_STATE_SEQ_NUM_POS 16
#घोषणा AGG_TX_STATE_SEQ_NUM_MSK 0xffff0000

/*
 * REPLY_TX = 0x1c (response)
 *
 * This response may be in one of two slightly dअगरferent क्रमmats, indicated
 * by the frame_count field:
 *
 * 1)  No aggregation (frame_count == 1).  This reports Tx results क्रम
 *     a single frame.  Multiple attempts, at various bit rates, may have
 *     been made क्रम this frame.
 *
 * 2)  Aggregation (frame_count > 1).  This reports Tx results क्रम
 *     2 or more frames that used block-acknowledge.  All frames were
 *     transmitted at same rate.  Rate scaling may have been used अगर first
 *     frame in this new agg block failed in previous agg block(s).
 *
 *     Note that, क्रम aggregation, ACK (block-ack) status is not delivered here;
 *     block-ack has not been received by the समय the agn device records
 *     this status.
 *     This status relates to reasons the tx might have been blocked or पातed
 *     within the sending station (this agn device), rather than whether it was
 *     received successfully by the destination station.
 */
काष्ठा agg_tx_status अणु
	__le16 status;
	__le16 sequence;
पूर्ण __packed;

/* refer to ra_tid */
#घोषणा IWLAGN_TX_RES_TID_POS	0
#घोषणा IWLAGN_TX_RES_TID_MSK	0x0f
#घोषणा IWLAGN_TX_RES_RA_POS	4
#घोषणा IWLAGN_TX_RES_RA_MSK	0xf0

काष्ठा iwlagn_tx_resp अणु
	u8 frame_count;		/* 1 no aggregation, >1 aggregation */
	u8 bt_समाप्त_count;	/* # blocked by bluetooth (unused क्रम agg) */
	u8 failure_rts;		/* # failures due to unsuccessful RTS */
	u8 failure_frame;	/* # failures due to no ACK (unused क्रम agg) */

	/* For non-agg:  Rate at which frame was successful.
	 * For agg:  Rate at which all frames were transmitted. */
	__le32 rate_n_flags;	/* RATE_MCS_*  */

	/* For non-agg:  RTS + CTS + frame tx attempts समय + ACK.
	 * For agg:  RTS + CTS + aggregation tx समय + block-ack समय. */
	__le16 wireless_media_समय;	/* uSecs */

	u8 pa_status;		/* RF घातer amplअगरier measurement (not used) */
	u8 pa_पूर्णांकeg_res_a[3];
	u8 pa_पूर्णांकeg_res_b[3];
	u8 pa_पूर्णांकeg_res_C[3];

	__le32 tfd_info;
	__le16 seq_ctl;
	__le16 byte_cnt;
	u8 tlc_info;
	u8 ra_tid;		/* tid (0:3), sta_id (4:7) */
	__le16 frame_ctrl;
	/*
	 * For non-agg:  frame status TX_STATUS_*
	 * For agg:  status of 1st frame, AGG_TX_STATE_*; other frame status
	 *           fields follow this one, up to frame_count.
	 *           Bit fields:
	 *           11- 0:  AGG_TX_STATE_* status code
	 *           15-12:  Retry count क्रम 1st frame in aggregation (retries
	 *                   occur अगर tx failed क्रम this frame when it was a
	 *                   member of a previous aggregation block).  If rate
	 *                   scaling is used, retry count indicates the rate
	 *                   table entry used क्रम all frames in the new agg.
	 *           31-16:  Sequence # क्रम this frame's Tx cmd (not SSN!)
	 */
	काष्ठा agg_tx_status status;	/* TX status (in aggregation -
					 * status of 1st frame) */
पूर्ण __packed;
/*
 * REPLY_COMPRESSED_BA = 0xc5 (response only, not a command)
 *
 * Reports Block-Acknowledge from recipient station
 */
काष्ठा iwl_compressed_ba_resp अणु
	__le32 sta_addr_lo32;
	__le16 sta_addr_hi16;
	__le16 reserved;

	/* Index of recipient (BA-sending) station in uCode's station table */
	u8 sta_id;
	u8 tid;
	__le16 seq_ctl;
	__le64 biपंचांगap;
	__le16 scd_flow;
	__le16 scd_ssn;
	u8 txed;	/* number of frames sent */
	u8 txed_2_करोne; /* number of frames acked */
	__le16 reserved1;
पूर्ण __packed;

/*
 * REPLY_TX_PWR_TABLE_CMD = 0x97 (command, has simple generic response)
 *
 */

/*RS_NEW_API: only TLC_RTS reमुख्यs and moved to bit 0 */
#घोषणा  LINK_QUAL_FLAGS_SET_STA_TLC_RTS_MSK	(1 << 0)

/* # of EDCA prioritized tx fअगरos */
#घोषणा  LINK_QUAL_AC_NUM AC_NUM

/* # entries in rate scale table to support Tx retries */
#घोषणा  LINK_QUAL_MAX_RETRY_NUM 16

/* Tx antenna selection values */
#घोषणा  LINK_QUAL_ANT_A_MSK (1 << 0)
#घोषणा  LINK_QUAL_ANT_B_MSK (1 << 1)
#घोषणा  LINK_QUAL_ANT_MSK   (LINK_QUAL_ANT_A_MSK|LINK_QUAL_ANT_B_MSK)


/**
 * काष्ठा iwl_link_qual_general_params
 *
 * Used in REPLY_TX_LINK_QUALITY_CMD
 */
काष्ठा iwl_link_qual_general_params अणु
	u8 flags;

	/* No entries at or above this (driver chosen) index contain MIMO */
	u8 mimo_delimiter;

	/* Best single antenna to use क्रम single stream (legacy, SISO). */
	u8 single_stream_ant_msk;	/* LINK_QUAL_ANT_* */

	/* Best antennas to use क्रम MIMO */
	u8 dual_stream_ant_msk;		/* LINK_QUAL_ANT_* */

	/*
	 * If driver needs to use dअगरferent initial rates क्रम dअगरferent
	 * EDCA QOS access categories (as implemented by tx fअगरos 0-3),
	 * this table will set that up, by indicating the indexes in the
	 * rs_table[LINK_QUAL_MAX_RETRY_NUM] rate table at which to start.
	 * Otherwise, driver should set all entries to 0.
	 *
	 * Entry usage:
	 * 0 = Background, 1 = Best Efक्रमt (normal), 2 = Video, 3 = Voice
	 * TX FIFOs above 3 use same value (typically 0) as TX FIFO 3.
	 */
	u8 start_rate_index[LINK_QUAL_AC_NUM];
पूर्ण __packed;

#घोषणा LINK_QUAL_AGG_TIME_LIMIT_DEF	(4000) /* 4 milliseconds */
#घोषणा LINK_QUAL_AGG_TIME_LIMIT_MAX	(8000)
#घोषणा LINK_QUAL_AGG_TIME_LIMIT_MIN	(100)

#घोषणा LINK_QUAL_AGG_DISABLE_START_DEF	(3)
#घोषणा LINK_QUAL_AGG_DISABLE_START_MAX	(255)
#घोषणा LINK_QUAL_AGG_DISABLE_START_MIN	(0)

#घोषणा LINK_QUAL_AGG_FRAME_LIMIT_DEF	(63)
#घोषणा LINK_QUAL_AGG_FRAME_LIMIT_MAX	(63)
#घोषणा LINK_QUAL_AGG_FRAME_LIMIT_MIN	(0)

/**
 * काष्ठा iwl_link_qual_agg_params
 *
 * Used in REPLY_TX_LINK_QUALITY_CMD
 */
काष्ठा iwl_link_qual_agg_params अणु

	/*
	 *Maximum number of uSec in aggregation.
	 * शेष set to 4000 (4 milliseconds) अगर not configured in .cfg
	 */
	__le16 agg_समय_limit;

	/*
	 * Number of Tx retries allowed क्रम a frame, beक्रमe that frame will
	 * no दीर्घer be considered क्रम the start of an aggregation sequence
	 * (scheduler will then try to tx it as single frame).
	 * Driver should set this to 3.
	 */
	u8 agg_dis_start_th;

	/*
	 * Maximum number of frames in aggregation.
	 * 0 = no limit (शेष).  1 = no aggregation.
	 * Other values = max # frames in aggregation.
	 */
	u8 agg_frame_cnt_limit;

	__le32 reserved;
पूर्ण __packed;

/*
 * REPLY_TX_LINK_QUALITY_CMD = 0x4e (command, has simple generic response)
 *
 * For agn devices
 *
 * Each station in the agn device's पूर्णांकernal station table has its own table
 * of 16
 * Tx rates and modulation modes (e.g. legacy/SISO/MIMO) क्रम retrying Tx when
 * an ACK is not received.  This command replaces the entire table क्रम
 * one station.
 *
 * NOTE:  Station must alपढ़ोy be in agn device's station table.
 *	  Use REPLY_ADD_STA.
 *
 * The rate scaling procedures described below work well.  Of course, other
 * procedures are possible, and may work better क्रम particular environments.
 *
 *
 * FILLING THE RATE TABLE
 *
 * Given a particular initial rate and mode, as determined by the rate
 * scaling algorithm described below, the Linux driver uses the following
 * क्रमmula to fill the rs_table[LINK_QUAL_MAX_RETRY_NUM] rate table in the
 * Link Quality command:
 *
 *
 * 1)  If using High-throughput (HT) (SISO or MIMO) initial rate:
 *     a) Use this same initial rate क्रम first 3 entries.
 *     b) Find next lower available rate using same mode (SISO or MIMO),
 *        use क्रम next 3 entries.  If no lower rate available, चयन to
 *        legacy mode (no HT40 channel, no MIMO, no लघु guard पूर्णांकerval).
 *     c) If using MIMO, set command's mimo_delimiter to number of entries
 *        using MIMO (3 or 6).
 *     d) After trying 2 HT rates, चयन to legacy mode (no HT40 channel,
 *        no MIMO, no लघु guard पूर्णांकerval), at the next lower bit rate
 *        (e.g. अगर second HT bit rate was 54, try 48 legacy), and follow
 *        legacy procedure क्रम reमुख्यing table entries.
 *
 * 2)  If using legacy initial rate:
 *     a) Use the initial rate क्रम only one entry.
 *     b) For each following entry, reduce the rate to next lower available
 *        rate, until reaching the lowest available rate.
 *     c) When reducing rate, also चयन antenna selection.
 *     d) Once lowest available rate is reached, repeat this rate until
 *        rate table is filled (16 entries), चयनing antenna each entry.
 *
 *
 * ACCUMULATING HISTORY
 *
 * The rate scaling algorithm क्रम agn devices, as implemented in Linux driver,
 * uses two sets of frame Tx success history:  One क्रम the current/active
 * modulation mode, and one क्रम a speculative/search mode that is being
 * attempted. If the speculative mode turns out to be more effective (i.e.
 * actual transfer rate is better), then the driver जारीs to use the
 * speculative mode as the new current active mode.
 *
 * Each history set contains, separately क्रम each possible rate, data क्रम a
 * sliding winकरोw of the 62 most recent tx attempts at that rate.  The data
 * includes a shअगरting biपंचांगap of success(1)/failure(0), and sums of successful
 * and attempted frames, from which the driver can additionally calculate a
 * success ratio (success / attempted) and number of failures
 * (attempted - success), and control the size of the winकरोw (attempted).
 * The driver uses the bit map to हटाओ successes from the success sum, as
 * the oldest tx attempts fall out of the winकरोw.
 *
 * When the agn device makes multiple tx attempts क्रम a given frame, each
 * attempt might be at a dअगरferent rate, and have dअगरferent modulation
 * अक्षरacteristics (e.g. antenna, fat channel, लघु guard पूर्णांकerval), as set
 * up in the rate scaling table in the Link Quality command.  The driver must
 * determine which rate table entry was used क्रम each tx attempt, to determine
 * which rate-specअगरic history to update, and record only those attempts that
 * match the modulation अक्षरacteristics of the history set.
 *
 * When using block-ack (aggregation), all frames are transmitted at the same
 * rate, since there is no per-attempt acknowledgment from the destination
 * station.  The Tx response काष्ठा iwl_tx_resp indicates the Tx rate in
 * rate_n_flags field.  After receiving a block-ack, the driver can update
 * history क्रम the entire block all at once.
 *
 *
 * FINDING BEST STARTING RATE:
 *
 * When working with a selected initial modulation mode (see below), the
 * driver attempts to find a best initial rate.  The initial rate is the
 * first entry in the Link Quality command's rate table.
 *
 * 1)  Calculate actual throughput (success ratio * expected throughput, see
 *     table below) क्रम current initial rate.  Do this only अगर enough frames
 *     have been attempted to make the value meaningful:  at least 6 failed
 *     tx attempts, or at least 8 successes.  If not enough, करोn't try rate
 *     scaling yet.
 *
 * 2)  Find available rates adjacent to current initial rate.  Available means:
 *     a)  supported by hardware &&
 *     b)  supported by association &&
 *     c)  within any स्थिरraपूर्णांकs selected by user
 *
 * 3)  Gather measured throughमाला_दो क्रम adjacent rates.  These might not have
 *     enough history to calculate a throughput.  That's okay, we might try
 *     using one of them anyway!
 *
 * 4)  Try decreasing rate अगर, क्रम current rate:
 *     a)  success ratio is < 15% ||
 *     b)  lower adjacent rate has better measured throughput ||
 *     c)  higher adjacent rate has worse throughput, and lower is unmeasured
 *
 *     As a sanity check, अगर decrease was determined above, leave rate
 *     unchanged अगर:
 *     a)  lower rate unavailable
 *     b)  success ratio at current rate > 85% (very good)
 *     c)  current measured throughput is better than expected throughput
 *         of lower rate (under perfect 100% tx conditions, see table below)
 *
 * 5)  Try increasing rate अगर, क्रम current rate:
 *     a)  success ratio is < 15% ||
 *     b)  both adjacent rates' throughमाला_दो are unmeasured (try it!) ||
 *     b)  higher adjacent rate has better measured throughput ||
 *     c)  lower adjacent rate has worse throughput, and higher is unmeasured
 *
 *     As a sanity check, अगर increase was determined above, leave rate
 *     unchanged अगर:
 *     a)  success ratio at current rate < 70%.  This is not particularly
 *         good perक्रमmance; higher rate is sure to have poorer success.
 *
 * 6)  Re-evaluate the rate after each tx frame.  If working with block-
 *     acknowledge, history and statistics may be calculated क्रम the entire
 *     block (including prior history that fits within the history winकरोws),
 *     beक्रमe re-evaluation.
 *
 * FINDING BEST STARTING MODULATION MODE:
 *
 * After working with a modulation mode क्रम a "while" (and करोing rate scaling),
 * the driver searches क्रम a new initial mode in an attempt to improve
 * throughput.  The "while" is measured by numbers of attempted frames:
 *
 * For legacy mode, search क्रम new mode after:
 *   480 successful frames, or 160 failed frames
 * For high-throughput modes (SISO or MIMO), search क्रम new mode after:
 *   4500 successful frames, or 400 failed frames
 *
 * Mode चयन possibilities are (3 क्रम each mode):
 *
 * For legacy:
 *   Change antenna, try SISO (अगर HT association), try MIMO (अगर HT association)
 * For SISO:
 *   Change antenna, try MIMO, try लघुened guard पूर्णांकerval (SGI)
 * For MIMO:
 *   Try SISO antenna A, SISO antenna B, try लघुened guard पूर्णांकerval (SGI)
 *
 * When trying a new mode, use the same bit rate as the old/current mode when
 * trying antenna चयनes and लघुened guard पूर्णांकerval.  When चयनing to
 * SISO from MIMO or legacy, or to MIMO from SISO or legacy, use a rate
 * क्रम which the expected throughput (under perfect conditions) is about the
 * same or slightly better than the actual measured throughput delivered by
 * the old/current mode.
 *
 * Actual throughput can be estimated by multiplying the expected throughput
 * by the success ratio (successful / attempted tx frames).  Frame size is
 * not considered in this calculation; it assumes that frame size will average
 * out to be fairly consistent over several samples.  The following are
 * metric values क्रम expected throughput assuming 100% success ratio.
 * Only G band has support क्रम CCK rates:
 *
 *           RATE:  1    2    5   11    6   9   12   18   24   36   48   54   60
 *
 *              G:  7   13   35   58   40  57   72   98  121  154  177  186  186
 *              A:  0    0    0    0   40  57   72   98  121  154  177  186  186
 *     SISO 20MHz:  0    0    0    0   42  42   76  102  124  159  183  193  202
 * SGI SISO 20MHz:  0    0    0    0   46  46   82  110  132  168  192  202  211
 *     MIMO 20MHz:  0    0    0    0   74  74  123  155  179  214  236  244  251
 * SGI MIMO 20MHz:  0    0    0    0   81  81  131  164  188  222  243  251  257
 *     SISO 40MHz:  0    0    0    0   77  77  127  160  184  220  242  250  257
 * SGI SISO 40MHz:  0    0    0    0   83  83  135  169  193  229  250  257  264
 *     MIMO 40MHz:  0    0    0    0  123 123  182  214  235  264  279  285  289
 * SGI MIMO 40MHz:  0    0    0    0  131 131  191  222  242  270  284  289  293
 *
 * After the new mode has been tried क्रम a लघु जबतक (minimum of 6 failed
 * frames or 8 successful frames), compare success ratio and actual throughput
 * estimate of the new mode with the old.  If either is better with the new
 * mode, जारी to use the new mode.
 *
 * Continue comparing modes until all 3 possibilities have been tried.
 * If moving from legacy to HT, try all 3 possibilities from the new HT
 * mode.  After trying all 3, a best mode is found.  Continue to use this mode
 * क्रम the दीर्घer "while" described above (e.g. 480 successful frames क्रम
 * legacy), and then repeat the search process.
 *
 */
काष्ठा iwl_link_quality_cmd अणु

	/* Index of destination/recipient station in uCode's station table */
	u8 sta_id;
	u8 reserved1;
	__le16 control;		/* not used */
	काष्ठा iwl_link_qual_general_params general_params;
	काष्ठा iwl_link_qual_agg_params agg_params;

	/*
	 * Rate info; when using rate-scaling, Tx command's initial_rate_index
	 * specअगरies 1st Tx rate attempted, via index पूर्णांकo this table.
	 * agn devices works its way through table when retrying Tx.
	 */
	काष्ठा अणु
		__le32 rate_n_flags;	/* RATE_MCS_*, IWL_RATE_* */
	पूर्ण rs_table[LINK_QUAL_MAX_RETRY_NUM];
	__le32 reserved2;
पूर्ण __packed;

/*
 * BT configuration enable flags:
 *   bit 0 - 1: BT channel announcement enabled
 *           0: disable
 *   bit 1 - 1: priority of BT device enabled
 *           0: disable
 *   bit 2 - 1: BT 2 wire support enabled
 *           0: disable
 */
#घोषणा BT_COEX_DISABLE (0x0)
#घोषणा BT_ENABLE_CHANNEL_ANNOUNCE BIT(0)
#घोषणा BT_ENABLE_PRIORITY	   BIT(1)
#घोषणा BT_ENABLE_2_WIRE	   BIT(2)

#घोषणा BT_COEX_DISABLE (0x0)
#घोषणा BT_COEX_ENABLE  (BT_ENABLE_CHANNEL_ANNOUNCE | BT_ENABLE_PRIORITY)

#घोषणा BT_LEAD_TIME_MIN (0x0)
#घोषणा BT_LEAD_TIME_DEF (0x1E)
#घोषणा BT_LEAD_TIME_MAX (0xFF)

#घोषणा BT_MAX_KILL_MIN (0x1)
#घोषणा BT_MAX_KILL_DEF (0x5)
#घोषणा BT_MAX_KILL_MAX (0xFF)

#घोषणा BT_DURATION_LIMIT_DEF	625
#घोषणा BT_DURATION_LIMIT_MAX	1250
#घोषणा BT_DURATION_LIMIT_MIN	625

#घोषणा BT_ON_THRESHOLD_DEF	4
#घोषणा BT_ON_THRESHOLD_MAX	1000
#घोषणा BT_ON_THRESHOLD_MIN	1

#घोषणा BT_FRAG_THRESHOLD_DEF	0
#घोषणा BT_FRAG_THRESHOLD_MAX	0
#घोषणा BT_FRAG_THRESHOLD_MIN	0

#घोषणा BT_AGG_THRESHOLD_DEF	1200
#घोषणा BT_AGG_THRESHOLD_MAX	8000
#घोषणा BT_AGG_THRESHOLD_MIN	400

/*
 * REPLY_BT_CONFIG = 0x9b (command, has simple generic response)
 *
 * agn devices support hardware handshake with Bluetooth device on
 * same platक्रमm.  Bluetooth device alerts wireless device when it will Tx;
 * wireless device can delay or समाप्त its own Tx to accommodate.
 */
काष्ठा iwl_bt_cmd अणु
	u8 flags;
	u8 lead_समय;
	u8 max_समाप्त;
	u8 reserved;
	__le32 समाप्त_ack_mask;
	__le32 समाप्त_cts_mask;
पूर्ण __packed;

#घोषणा IWLAGN_BT_FLAG_CHANNEL_INHIBITION	BIT(0)

#घोषणा IWLAGN_BT_FLAG_COEX_MODE_MASK		(BIT(3)|BIT(4)|BIT(5))
#घोषणा IWLAGN_BT_FLAG_COEX_MODE_SHIFT		3
#घोषणा IWLAGN_BT_FLAG_COEX_MODE_DISABLED	0
#घोषणा IWLAGN_BT_FLAG_COEX_MODE_LEGACY_2W	1
#घोषणा IWLAGN_BT_FLAG_COEX_MODE_3W		2
#घोषणा IWLAGN_BT_FLAG_COEX_MODE_4W		3

#घोषणा IWLAGN_BT_FLAG_UCODE_DEFAULT		BIT(6)
/* Disable Sync PSPoll on SCO/eSCO */
#घोषणा IWLAGN_BT_FLAG_SYNC_2_BT_DISABLE	BIT(7)

#घोषणा IWLAGN_BT_PSP_MIN_RSSI_THRESHOLD	-75 /* dBm */
#घोषणा IWLAGN_BT_PSP_MAX_RSSI_THRESHOLD	-65 /* dBm */

#घोषणा IWLAGN_BT_PRIO_BOOST_MAX	0xFF
#घोषणा IWLAGN_BT_PRIO_BOOST_MIN	0x00
#घोषणा IWLAGN_BT_PRIO_BOOST_DEFAULT	0xF0
#घोषणा IWLAGN_BT_PRIO_BOOST_DEFAULT32	0xF0F0F0F0

#घोषणा IWLAGN_BT_MAX_KILL_DEFAULT	5

#घोषणा IWLAGN_BT3_T7_DEFAULT		1

क्रमागत iwl_bt_समाप्त_idx अणु
	IWL_BT_KILL_DEFAULT = 0,
	IWL_BT_KILL_OVERRIDE = 1,
	IWL_BT_KILL_REDUCE = 2,
पूर्ण;

#घोषणा IWLAGN_BT_KILL_ACK_MASK_DEFAULT	cpu_to_le32(0xffff0000)
#घोषणा IWLAGN_BT_KILL_CTS_MASK_DEFAULT	cpu_to_le32(0xffff0000)
#घोषणा IWLAGN_BT_KILL_ACK_CTS_MASK_SCO	cpu_to_le32(0xffffffff)
#घोषणा IWLAGN_BT_KILL_ACK_CTS_MASK_REDUCE	cpu_to_le32(0)

#घोषणा IWLAGN_BT3_PRIO_SAMPLE_DEFAULT	2

#घोषणा IWLAGN_BT3_T2_DEFAULT		0xc

#घोषणा IWLAGN_BT_VALID_ENABLE_FLAGS	cpu_to_le16(BIT(0))
#घोषणा IWLAGN_BT_VALID_BOOST		cpu_to_le16(BIT(1))
#घोषणा IWLAGN_BT_VALID_MAX_KILL	cpu_to_le16(BIT(2))
#घोषणा IWLAGN_BT_VALID_3W_TIMERS	cpu_to_le16(BIT(3))
#घोषणा IWLAGN_BT_VALID_KILL_ACK_MASK	cpu_to_le16(BIT(4))
#घोषणा IWLAGN_BT_VALID_KILL_CTS_MASK	cpu_to_le16(BIT(5))
#घोषणा IWLAGN_BT_VALID_REDUCED_TX_PWR	cpu_to_le16(BIT(6))
#घोषणा IWLAGN_BT_VALID_3W_LUT		cpu_to_le16(BIT(7))

#घोषणा IWLAGN_BT_ALL_VALID_MSK		(IWLAGN_BT_VALID_ENABLE_FLAGS | \
					IWLAGN_BT_VALID_BOOST | \
					IWLAGN_BT_VALID_MAX_KILL | \
					IWLAGN_BT_VALID_3W_TIMERS | \
					IWLAGN_BT_VALID_KILL_ACK_MASK | \
					IWLAGN_BT_VALID_KILL_CTS_MASK | \
					IWLAGN_BT_VALID_REDUCED_TX_PWR | \
					IWLAGN_BT_VALID_3W_LUT)

#घोषणा IWLAGN_BT_REDUCED_TX_PWR	BIT(0)

#घोषणा IWLAGN_BT_DECISION_LUT_SIZE	12

काष्ठा iwl_basic_bt_cmd अणु
	u8 flags;
	u8 ledसमय; /* unused */
	u8 max_समाप्त;
	u8 bt3_समयr_t7_value;
	__le32 समाप्त_ack_mask;
	__le32 समाप्त_cts_mask;
	u8 bt3_prio_sample_समय;
	u8 bt3_समयr_t2_value;
	__le16 bt4_reaction_समय; /* unused */
	__le32 bt3_lookup_table[IWLAGN_BT_DECISION_LUT_SIZE];
	/*
	 * bit 0: use reduced tx घातer क्रम control frame
	 * bit 1 - 7: reserved
	 */
	u8 reduce_txघातer;
	u8 reserved;
	__le16 valid;
पूर्ण;

काष्ठा iwl_bt_cmd_v1 अणु
	काष्ठा iwl_basic_bt_cmd basic;
	u8 prio_boost;
	/*
	 * set IWLAGN_BT_VALID_BOOST to "1" in "valid" biपंचांगask
	 * अगर configure the following patterns
	 */
	u8 tx_prio_boost;	/* SW boost of WiFi tx priority */
	__le16 rx_prio_boost;	/* SW boost of WiFi rx priority */
पूर्ण;

काष्ठा iwl_bt_cmd_v2 अणु
	काष्ठा iwl_basic_bt_cmd basic;
	__le32 prio_boost;
	/*
	 * set IWLAGN_BT_VALID_BOOST to "1" in "valid" biपंचांगask
	 * अगर configure the following patterns
	 */
	u8 reserved;
	u8 tx_prio_boost;	/* SW boost of WiFi tx priority */
	__le16 rx_prio_boost;	/* SW boost of WiFi rx priority */
पूर्ण;

#घोषणा IWLAGN_BT_SCO_ACTIVE	cpu_to_le32(BIT(0))

काष्ठा iwlagn_bt_sco_cmd अणु
	__le32 flags;
पूर्ण;

/******************************************************************************
 * (6)
 * Spectrum Management (802.11h) Commands, Responses, Notअगरications:
 *
 *****************************************************************************/

/*
 * Spectrum Management
 */
#घोषणा MEASUREMENT_FILTER_FLAG (RXON_FILTER_PROMISC_MSK         | \
				 RXON_FILTER_CTL2HOST_MSK        | \
				 RXON_FILTER_ACCEPT_GRP_MSK      | \
				 RXON_FILTER_DIS_DECRYPT_MSK     | \
				 RXON_FILTER_DIS_GRP_DECRYPT_MSK | \
				 RXON_FILTER_ASSOC_MSK           | \
				 RXON_FILTER_BCON_AWARE_MSK)

काष्ठा iwl_measure_channel अणु
	__le32 duration;	/* measurement duration in extended beacon
				 * क्रमmat */
	u8 channel;		/* channel to measure */
	u8 type;		/* see क्रमागत iwl_measure_type */
	__le16 reserved;
पूर्ण __packed;

/*
 * REPLY_SPECTRUM_MEASUREMENT_CMD = 0x74 (command)
 */
काष्ठा iwl_spectrum_cmd अणु
	__le16 len;		/* number of bytes starting from token */
	u8 token;		/* token id */
	u8 id;			/* measurement id -- 0 or 1 */
	u8 origin;		/* 0 = TGh, 1 = other, 2 = TGk */
	u8 periodic;		/* 1 = periodic */
	__le16 path_loss_समयout;
	__le32 start_समय;	/* start समय in extended beacon क्रमmat */
	__le32 reserved2;
	__le32 flags;		/* rxon flags */
	__le32 filter_flags;	/* rxon filter flags */
	__le16 channel_count;	/* minimum 1, maximum 10 */
	__le16 reserved3;
	काष्ठा iwl_measure_channel channels[10];
पूर्ण __packed;

/*
 * REPLY_SPECTRUM_MEASUREMENT_CMD = 0x74 (response)
 */
काष्ठा iwl_spectrum_resp अणु
	u8 token;
	u8 id;			/* id of the prior command replaced, or 0xff */
	__le16 status;		/* 0 - command will be handled
				 * 1 - cannot handle (conflicts with another
				 *     measurement) */
पूर्ण __packed;

क्रमागत iwl_measurement_state अणु
	IWL_MEASUREMENT_START = 0,
	IWL_MEASUREMENT_STOP = 1,
पूर्ण;

क्रमागत iwl_measurement_status अणु
	IWL_MEASUREMENT_OK = 0,
	IWL_MEASUREMENT_CONCURRENT = 1,
	IWL_MEASUREMENT_CSA_CONFLICT = 2,
	IWL_MEASUREMENT_TGH_CONFLICT = 3,
	/* 4-5 reserved */
	IWL_MEASUREMENT_STOPPED = 6,
	IWL_MEASUREMENT_TIMEOUT = 7,
	IWL_MEASUREMENT_PERIODIC_FAILED = 8,
पूर्ण;

#घोषणा NUM_ELEMENTS_IN_HISTOGRAM 8

काष्ठा iwl_measurement_histogram अणु
	__le32 ofdm[NUM_ELEMENTS_IN_HISTOGRAM];	/* in 0.8usec counts */
	__le32 cck[NUM_ELEMENTS_IN_HISTOGRAM];	/* in 1usec counts */
पूर्ण __packed;

/* clear channel availability counters */
काष्ठा iwl_measurement_cca_counters अणु
	__le32 ofdm;
	__le32 cck;
पूर्ण __packed;

क्रमागत iwl_measure_type अणु
	IWL_MEASURE_BASIC = (1 << 0),
	IWL_MEASURE_CHANNEL_LOAD = (1 << 1),
	IWL_MEASURE_HISTOGRAM_RPI = (1 << 2),
	IWL_MEASURE_HISTOGRAM_NOISE = (1 << 3),
	IWL_MEASURE_FRAME = (1 << 4),
	/* bits 5:6 are reserved */
	IWL_MEASURE_IDLE = (1 << 7),
पूर्ण;

/*
 * SPECTRUM_MEASURE_NOTIFICATION = 0x75 (notअगरication only, not a command)
 */
काष्ठा iwl_spectrum_notअगरication अणु
	u8 id;			/* measurement id -- 0 or 1 */
	u8 token;
	u8 channel_index;	/* index in measurement channel list */
	u8 state;		/* 0 - start, 1 - stop */
	__le32 start_समय;	/* lower 32-bits of TSF */
	u8 band;		/* 0 - 5.2GHz, 1 - 2.4GHz */
	u8 channel;
	u8 type;		/* see क्रमागत iwl_measurement_type */
	u8 reserved1;
	/* NOTE:  cca_ofdm, cca_cck, basic_type, and histogram are only only
	 * valid अगर applicable क्रम measurement type requested. */
	__le32 cca_ofdm;	/* cca fraction समय in 40Mhz घड़ी periods */
	__le32 cca_cck;		/* cca fraction समय in 44Mhz घड़ी periods */
	__le32 cca_समय;	/* channel load समय in usecs */
	u8 basic_type;		/* 0 - bss, 1 - ofdm preamble, 2 -
				 * unidentअगरied */
	u8 reserved2[3];
	काष्ठा iwl_measurement_histogram histogram;
	__le32 stop_समय;	/* lower 32-bits of TSF */
	__le32 status;		/* see iwl_measurement_status */
पूर्ण __packed;

/******************************************************************************
 * (7)
 * Power Management Commands, Responses, Notअगरications:
 *
 *****************************************************************************/

/**
 * काष्ठा iwl_घातertable_cmd - Power Table Command
 * @flags: See below:
 *
 * POWER_TABLE_CMD = 0x77 (command, has simple generic response)
 *
 * PM allow:
 *   bit 0 - '0' Driver not allow घातer management
 *           '1' Driver allow PM (use rest of parameters)
 *
 * uCode send sleep notअगरications:
 *   bit 1 - '0' Don't send sleep notअगरication
 *           '1' send sleep notअगरication (SEND_PM_NOTIFICATION)
 *
 * Sleep over DTIM
 *   bit 2 - '0' PM have to walk up every DTIM
 *           '1' PM could sleep over DTIM till listen Interval.
 *
 * PCI घातer managed
 *   bit 3 - '0' (PCI_CFG_LINK_CTRL & 0x1)
 *           '1' !(PCI_CFG_LINK_CTRL & 0x1)
 *
 * Fast PD
 *   bit 4 - '1' Put radio to sleep when receiving frame क्रम others
 *
 * Force sleep Modes
 *   bit 31/30- '00' use both mac/xtal sleeps
 *              '01' क्रमce Mac sleep
 *              '10' क्रमce xtal sleep
 *              '11' Illegal set
 *
 * NOTE: अगर sleep_पूर्णांकerval[SLEEP_INTRVL_TABLE_SIZE-1] > DTIM period then
 * ucode assume sleep over DTIM is allowed and we करोn't need to wake up
 * क्रम every DTIM.
 */
#घोषणा IWL_POWER_VEC_SIZE 5

#घोषणा IWL_POWER_DRIVER_ALLOW_SLEEP_MSK	cpu_to_le16(BIT(0))
#घोषणा IWL_POWER_POWER_SAVE_ENA_MSK		cpu_to_le16(BIT(0))
#घोषणा IWL_POWER_POWER_MANAGEMENT_ENA_MSK	cpu_to_le16(BIT(1))
#घोषणा IWL_POWER_SLEEP_OVER_DTIM_MSK		cpu_to_le16(BIT(2))
#घोषणा IWL_POWER_PCI_PM_MSK			cpu_to_le16(BIT(3))
#घोषणा IWL_POWER_FAST_PD			cpu_to_le16(BIT(4))
#घोषणा IWL_POWER_BEACON_FILTERING		cpu_to_le16(BIT(5))
#घोषणा IWL_POWER_SHADOW_REG_ENA		cpu_to_le16(BIT(6))
#घोषणा IWL_POWER_CT_KILL_SET			cpu_to_le16(BIT(7))
#घोषणा IWL_POWER_BT_SCO_ENA			cpu_to_le16(BIT(8))
#घोषणा IWL_POWER_ADVANCE_PM_ENA_MSK		cpu_to_le16(BIT(9))

काष्ठा iwl_घातertable_cmd अणु
	__le16 flags;
	u8 keep_alive_seconds;
	u8 debug_flags;
	__le32 rx_data_समयout;
	__le32 tx_data_समयout;
	__le32 sleep_पूर्णांकerval[IWL_POWER_VEC_SIZE];
	__le32 keep_alive_beacons;
पूर्ण __packed;

/*
 * PM_SLEEP_NOTIFICATION = 0x7A (notअगरication only, not a command)
 * all devices identical.
 */
काष्ठा iwl_sleep_notअगरication अणु
	u8 pm_sleep_mode;
	u8 pm_wakeup_src;
	__le16 reserved;
	__le32 sleep_समय;
	__le32 tsf_low;
	__le32 bcon_समयr;
पूर्ण __packed;

/* Sleep states.  all devices identical. */
क्रमागत अणु
	IWL_PM_NO_SLEEP = 0,
	IWL_PM_SLP_MAC = 1,
	IWL_PM_SLP_FULL_MAC_UNASSOCIATE = 2,
	IWL_PM_SLP_FULL_MAC_CARD_STATE = 3,
	IWL_PM_SLP_PHY = 4,
	IWL_PM_SLP_REPENT = 5,
	IWL_PM_WAKEUP_BY_TIMER = 6,
	IWL_PM_WAKEUP_BY_DRIVER = 7,
	IWL_PM_WAKEUP_BY_RFKILL = 8,
	/* 3 reserved */
	IWL_PM_NUM_OF_MODES = 12,
पूर्ण;

/*
 * REPLY_CARD_STATE_CMD = 0xa0 (command, has simple generic response)
 */
#घोषणा CARD_STATE_CMD_DISABLE 0x00	/* Put card to sleep */
#घोषणा CARD_STATE_CMD_ENABLE  0x01	/* Wake up card */
#घोषणा CARD_STATE_CMD_HALT    0x02	/* Power करोwn permanently */
काष्ठा iwl_card_state_cmd अणु
	__le32 status;		/* CARD_STATE_CMD_* request new घातer state */
पूर्ण __packed;

/*
 * CARD_STATE_NOTIFICATION = 0xa1 (notअगरication only, not a command)
 */
काष्ठा iwl_card_state_notअगर अणु
	__le32 flags;
पूर्ण __packed;

#घोषणा HW_CARD_DISABLED   0x01
#घोषणा SW_CARD_DISABLED   0x02
#घोषणा CT_CARD_DISABLED   0x04
#घोषणा RXON_CARD_DISABLED 0x10

काष्ठा iwl_ct_समाप्त_config अणु
	__le32   reserved;
	__le32   critical_temperature_M;
	__le32   critical_temperature_R;
पूर्ण  __packed;

/* 1000, and 6x00 */
काष्ठा iwl_ct_समाप्त_throttling_config अणु
	__le32   critical_temperature_निकास;
	__le32   reserved;
	__le32   critical_temperature_enter;
पूर्ण  __packed;

/******************************************************************************
 * (8)
 * Scan Commands, Responses, Notअगरications:
 *
 *****************************************************************************/

#घोषणा SCAN_CHANNEL_TYPE_PASSIVE cpu_to_le32(0)
#घोषणा SCAN_CHANNEL_TYPE_ACTIVE  cpu_to_le32(1)

/**
 * काष्ठा iwl_scan_channel - entry in REPLY_SCAN_CMD channel table
 *
 * One क्रम each channel in the scan list.
 * Each channel can independently select:
 * 1)  SSID क्रम directed active scans
 * 2)  Txघातer setting (क्रम rate specअगरied within Tx command)
 * 3)  How दीर्घ to stay on-channel (behavior may be modअगरied by quiet_समय,
 *     quiet_plcp_th, good_CRC_th)
 *
 * To aव्योम uCode errors, make sure the following are true (see comments
 * under काष्ठा iwl_scan_cmd about max_out_समय and quiet_समय):
 * 1)  If using passive_dwell (i.e. passive_dwell != 0):
 *     active_dwell <= passive_dwell (< max_out_समय अगर max_out_समय != 0)
 * 2)  quiet_समय <= active_dwell
 * 3)  If restricting off-channel समय (i.e. max_out_समय !=0):
 *     passive_dwell < max_out_समय
 *     active_dwell < max_out_समय
 */

काष्ठा iwl_scan_channel अणु
	/*
	 * type is defined as:
	 * 0:0 1 = active, 0 = passive
	 * 1:20 SSID direct bit map; अगर a bit is set, then corresponding
	 *     SSID IE is transmitted in probe request.
	 * 21:31 reserved
	 */
	__le32 type;
	__le16 channel;	/* band is selected by iwl_scan_cmd "flags" field */
	u8 tx_gain;		/* gain क्रम analog radio */
	u8 dsp_atten;		/* gain क्रम DSP */
	__le16 active_dwell;	/* in 1024-uSec TU (समय units), typ 5-50 */
	__le16 passive_dwell;	/* in 1024-uSec TU (समय units), typ 20-500 */
पूर्ण __packed;

/* set number of direct probes __le32 type */
#घोषणा IWL_SCAN_PROBE_MASK(n) 	cpu_to_le32((BIT(n) | (BIT(n) - BIT(1))))

/**
 * काष्ठा iwl_ssid_ie - directed scan network inक्रमmation element
 *
 * Up to 20 of these may appear in REPLY_SCAN_CMD,
 * selected by "type" bit field in काष्ठा iwl_scan_channel;
 * each channel may select dअगरferent ssids from among the 20 entries.
 * SSID IEs get transmitted in reverse order of entry.
 */
काष्ठा iwl_ssid_ie अणु
	u8 id;
	u8 len;
	u8 ssid[32];
पूर्ण __packed;

#घोषणा PROBE_OPTION_MAX		20
#घोषणा TX_CMD_LIFE_TIME_INFINITE	cpu_to_le32(0xFFFFFFFF)
#घोषणा IWL_GOOD_CRC_TH_DISABLED	0
#घोषणा IWL_GOOD_CRC_TH_DEFAULT		cpu_to_le16(1)
#घोषणा IWL_GOOD_CRC_TH_NEVER		cpu_to_le16(0xffff)
#घोषणा IWL_MAX_CMD_SIZE 4096

/*
 * REPLY_SCAN_CMD = 0x80 (command)
 *
 * The hardware scan command is very घातerful; the driver can set it up to
 * मुख्यtain (relatively) normal network traffic जबतक करोing a scan in the
 * background.  The max_out_समय and suspend_समय control the ratio of how
 * दीर्घ the device stays on an associated network channel ("service channel")
 * vs. how दीर्घ it's away from the service channel, i.e. tuned to other channels
 * क्रम scanning.
 *
 * max_out_समय is the max समय off-channel (in usec), and suspend_समय
 * is how दीर्घ (in "extended beacon" क्रमmat) that the scan is "suspended"
 * after वापसing to the service channel.  That is, suspend_समय is the
 * समय that we stay on the service channel, करोing normal work, between
 * scan segments.  The driver may set these parameters dअगरferently to support
 * scanning when associated vs. not associated, and light vs. heavy traffic
 * loads when associated.
 *
 * After receiving this command, the device's scan engine करोes the following;
 *
 * 1)  Sends SCAN_START notअगरication to driver
 * 2)  Checks to see अगर it has समय to करो scan क्रम one channel
 * 3)  Sends शून्य packet, with घातer-save (PS) bit set to 1,
 *     to tell AP that we're going off-channel
 * 4)  Tunes to first channel in scan list, करोes active or passive scan
 * 5)  Sends SCAN_RESULT notअगरication to driver
 * 6)  Checks to see अगर it has समय to करो scan on *next* channel in list
 * 7)  Repeats 4-6 until it no दीर्घer has समय to scan the next channel
 *     beक्रमe max_out_समय expires
 * 8)  Returns to service channel
 * 9)  Sends शून्य packet with PS=0 to tell AP that we're back
 * 10) Stays on service channel until suspend_समय expires
 * 11) Repeats entire process 2-10 until list is complete
 * 12) Sends SCAN_COMPLETE notअगरication
 *
 * For fast, efficient scans, the scan command also has support क्रम staying on
 * a channel क्रम just a लघु समय, अगर करोing active scanning and getting no
 * responses to the transmitted probe request.  This समय is controlled by
 * quiet_समय, and the number of received packets below which a channel is
 * considered "quiet" is controlled by quiet_plcp_threshold.
 *
 * For active scanning on channels that have regulatory restrictions against
 * blindly transmitting, the scan can listen beक्रमe transmitting, to make sure
 * that there is alपढ़ोy legitimate activity on the channel.  If enough
 * packets are cleanly received on the channel (controlled by good_CRC_th,
 * typical value 1), the scan engine starts transmitting probe requests.
 *
 * Driver must use separate scan commands क्रम 2.4 vs. 5 GHz bands.
 *
 * To aव्योम uCode errors, see timing restrictions described under
 * काष्ठा iwl_scan_channel.
 */

क्रमागत iwl_scan_flags अणु
	/* BIT(0) currently unused */
	IWL_SCAN_FLAGS_ACTION_FRAME_TX	= BIT(1),
	/* bits 2-7 reserved */
पूर्ण;

काष्ठा iwl_scan_cmd अणु
	__le16 len;
	u8 scan_flags;		/* scan flags: see क्रमागत iwl_scan_flags */
	u8 channel_count;	/* # channels in channel list */
	__le16 quiet_समय;	/* dwell only this # millisecs on quiet channel
				 * (only क्रम active scan) */
	__le16 quiet_plcp_th;	/* quiet chnl is < this # pkts (typ. 1) */
	__le16 good_CRC_th;	/* passive -> active promotion threshold */
	__le16 rx_chain;	/* RXON_RX_CHAIN_* */
	__le32 max_out_समय;	/* max usec to be away from associated (service)
				 * channel */
	__le32 suspend_समय;	/* छोड़ो scan this दीर्घ (in "extended beacon
				 * क्रमmat") when वापसing to service chnl:
				 */
	__le32 flags;		/* RXON_FLG_* */
	__le32 filter_flags;	/* RXON_FILTER_* */

	/* For active scans (set to all-0s क्रम passive scans).
	 * Does not include payload.  Must specअगरy Tx rate; no rate scaling. */
	काष्ठा iwl_tx_cmd tx_cmd;

	/* For directed active scans (set to all-0s otherwise) */
	काष्ठा iwl_ssid_ie direct_scan[PROBE_OPTION_MAX];

	/*
	 * Probe request frame, followed by channel list.
	 *
	 * Size of probe request frame is specअगरied by byte count in tx_cmd.
	 * Channel list follows immediately after probe request frame.
	 * Number of channels in list is specअगरied by channel_count.
	 * Each channel in list is of type:
	 *
	 * काष्ठा iwl_scan_channel channels[0];
	 *
	 * NOTE:  Only one band of channels can be scanned per pass.  You
	 * must not mix 2.4GHz channels and 5.2GHz channels, and you must रुको
	 * क्रम one scan to complete (i.e. receive SCAN_COMPLETE_NOTIFICATION)
	 * beक्रमe requesting another scan.
	 */
	u8 data[];
पूर्ण __packed;

/* Can पात will notअगरy by complete notअगरication with पात status. */
#घोषणा CAN_ABORT_STATUS	cpu_to_le32(0x1)
/* complete notअगरication statuses */
#घोषणा ABORT_STATUS            0x2

/*
 * REPLY_SCAN_CMD = 0x80 (response)
 */
काष्ठा iwl_scanreq_notअगरication अणु
	__le32 status;		/* 1: okay, 2: cannot fulfill request */
पूर्ण __packed;

/*
 * SCAN_START_NOTIFICATION = 0x82 (notअगरication only, not a command)
 */
काष्ठा iwl_scanstart_notअगरication अणु
	__le32 tsf_low;
	__le32 tsf_high;
	__le32 beacon_समयr;
	u8 channel;
	u8 band;
	u8 reserved[2];
	__le32 status;
पूर्ण __packed;

#घोषणा  SCAN_OWNER_STATUS 0x1
#घोषणा  MEASURE_OWNER_STATUS 0x2

#घोषणा IWL_PROBE_STATUS_OK		0
#घोषणा IWL_PROBE_STATUS_TX_FAILED	BIT(0)
/* error statuses combined with TX_FAILED */
#घोषणा IWL_PROBE_STATUS_FAIL_TTL	BIT(1)
#घोषणा IWL_PROBE_STATUS_FAIL_BT	BIT(2)

#घोषणा NUMBER_OF_STATISTICS 1	/* first __le32 is good CRC */
/*
 * SCAN_RESULTS_NOTIFICATION = 0x83 (notअगरication only, not a command)
 */
काष्ठा iwl_scanresults_notअगरication अणु
	u8 channel;
	u8 band;
	u8 probe_status;
	u8 num_probe_not_sent; /* not enough समय to send */
	__le32 tsf_low;
	__le32 tsf_high;
	__le32 statistics[NUMBER_OF_STATISTICS];
पूर्ण __packed;

/*
 * SCAN_COMPLETE_NOTIFICATION = 0x84 (notअगरication only, not a command)
 */
काष्ठा iwl_scancomplete_notअगरication अणु
	u8 scanned_channels;
	u8 status;
	u8 bt_status;	/* BT On/Off status */
	u8 last_channel;
	__le32 tsf_low;
	__le32 tsf_high;
पूर्ण __packed;


/******************************************************************************
 * (9)
 * IBSS/AP Commands and Notअगरications:
 *
 *****************************************************************************/

क्रमागत iwl_ibss_manager अणु
	IWL_NOT_IBSS_MANAGER = 0,
	IWL_IBSS_MANAGER = 1,
पूर्ण;

/*
 * BEACON_NOTIFICATION = 0x90 (notअगरication only, not a command)
 */

काष्ठा iwlagn_beacon_notअगर अणु
	काष्ठा iwlagn_tx_resp beacon_notअगरy_hdr;
	__le32 low_tsf;
	__le32 high_tsf;
	__le32 ibss_mgr_status;
पूर्ण __packed;

/*
 * REPLY_TX_BEACON = 0x91 (command, has simple generic response)
 */

काष्ठा iwl_tx_beacon_cmd अणु
	काष्ठा iwl_tx_cmd tx;
	__le16 tim_idx;
	u8 tim_size;
	u8 reserved1;
	काष्ठा ieee80211_hdr frame[];	/* beacon frame */
पूर्ण __packed;

/******************************************************************************
 * (10)
 * Statistics Commands and Notअगरications:
 *
 *****************************************************************************/

#घोषणा IWL_TEMP_CONVERT 260

#घोषणा SUP_RATE_11A_MAX_NUM_CHANNELS  8
#घोषणा SUP_RATE_11B_MAX_NUM_CHANNELS  4
#घोषणा SUP_RATE_11G_MAX_NUM_CHANNELS  12

/* Used क्रम passing to driver number of successes and failures per rate */
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

काष्ठा statistics_dbg अणु
	__le32 burst_check;
	__le32 burst_count;
	__le32 रुको_क्रम_silence_समयout_cnt;
	__le32 reserved[3];
पूर्ण __packed;

काष्ठा statistics_rx_phy अणु
	__le32 ina_cnt;
	__le32 fina_cnt;
	__le32 plcp_err;
	__le32 crc32_err;
	__le32 overrun_err;
	__le32 early_overrun_err;
	__le32 crc32_good;
	__le32 false_alarm_cnt;
	__le32 fina_sync_err_cnt;
	__le32 sfd_समयout;
	__le32 fina_समयout;
	__le32 unresponded_rts;
	__le32 rxe_frame_limit_overrun;
	__le32 sent_ack_cnt;
	__le32 sent_cts_cnt;
	__le32 sent_ba_rsp_cnt;
	__le32 dsp_self_समाप्त;
	__le32 mh_क्रमmat_err;
	__le32 re_acq_मुख्य_rssi_sum;
	__le32 reserved3;
पूर्ण __packed;

काष्ठा statistics_rx_ht_phy अणु
	__le32 plcp_err;
	__le32 overrun_err;
	__le32 early_overrun_err;
	__le32 crc32_good;
	__le32 crc32_err;
	__le32 mh_क्रमmat_err;
	__le32 agg_crc32_good;
	__le32 agg_mpdu_cnt;
	__le32 agg_cnt;
	__le32 unsupport_mcs;
पूर्ण __packed;

#घोषणा INTERFERENCE_DATA_AVAILABLE      cpu_to_le32(1)

काष्ठा statistics_rx_non_phy अणु
	__le32 bogus_cts;	/* CTS received when not expecting CTS */
	__le32 bogus_ack;	/* ACK received when not expecting ACK */
	__le32 non_bssid_frames;	/* number of frames with BSSID that
					 * करोesn't beदीर्घ to the STA BSSID */
	__le32 filtered_frames;	/* count frames that were dumped in the
				 * filtering process */
	__le32 non_channel_beacons;	/* beacons with our bss id but not on
					 * our serving channel */
	__le32 channel_beacons;	/* beacons with our bss id and in our
				 * serving channel */
	__le32 num_missed_bcon;	/* number of missed beacons */
	__le32 adc_rx_saturation_समय;	/* count in 0.8us units the समय the
					 * ADC was in saturation */
	__le32 ina_detection_search_समय;/* total समय (in 0.8us) searched
					  * क्रम INA */
	__le32 beacon_silence_rssi_a;	/* RSSI silence after beacon frame */
	__le32 beacon_silence_rssi_b;	/* RSSI silence after beacon frame */
	__le32 beacon_silence_rssi_c;	/* RSSI silence after beacon frame */
	__le32 पूर्णांकerference_data_flag;	/* flag क्रम पूर्णांकerference data
					 * availability. 1 when data is
					 * available. */
	__le32 channel_load;		/* counts RX Enable समय in uSec */
	__le32 dsp_false_alarms;	/* DSP false alarm (both OFDM
					 * and CCK) counter */
	__le32 beacon_rssi_a;
	__le32 beacon_rssi_b;
	__le32 beacon_rssi_c;
	__le32 beacon_energy_a;
	__le32 beacon_energy_b;
	__le32 beacon_energy_c;
पूर्ण __packed;

काष्ठा statistics_rx_non_phy_bt अणु
	काष्ठा statistics_rx_non_phy common;
	/* additional stats क्रम bt */
	__le32 num_bt_समाप्तs;
	__le32 reserved[2];
पूर्ण __packed;

काष्ठा statistics_rx अणु
	काष्ठा statistics_rx_phy ofdm;
	काष्ठा statistics_rx_phy cck;
	काष्ठा statistics_rx_non_phy general;
	काष्ठा statistics_rx_ht_phy ofdm_ht;
पूर्ण __packed;

काष्ठा statistics_rx_bt अणु
	काष्ठा statistics_rx_phy ofdm;
	काष्ठा statistics_rx_phy cck;
	काष्ठा statistics_rx_non_phy_bt general;
	काष्ठा statistics_rx_ht_phy ofdm_ht;
पूर्ण __packed;

/**
 * काष्ठा statistics_tx_घातer - current tx घातer
 *
 * @ant_a: current tx घातer on chain a in 1/2 dB step
 * @ant_b: current tx घातer on chain b in 1/2 dB step
 * @ant_c: current tx घातer on chain c in 1/2 dB step
 */
काष्ठा statistics_tx_घातer अणु
	u8 ant_a;
	u8 ant_b;
	u8 ant_c;
	u8 reserved;
पूर्ण __packed;

काष्ठा statistics_tx_non_phy_agg अणु
	__le32 ba_समयout;
	__le32 ba_reschedule_frames;
	__le32 scd_query_agg_frame_cnt;
	__le32 scd_query_no_agg;
	__le32 scd_query_agg;
	__le32 scd_query_mismatch;
	__le32 frame_not_पढ़ोy;
	__le32 underrun;
	__le32 bt_prio_समाप्त;
	__le32 rx_ba_rsp_cnt;
पूर्ण __packed;

काष्ठा statistics_tx अणु
	__le32 preamble_cnt;
	__le32 rx_detected_cnt;
	__le32 bt_prio_defer_cnt;
	__le32 bt_prio_समाप्त_cnt;
	__le32 few_bytes_cnt;
	__le32 cts_समयout;
	__le32 ack_समयout;
	__le32 expected_ack_cnt;
	__le32 actual_ack_cnt;
	__le32 dump_msdu_cnt;
	__le32 burst_पात_next_frame_mismatch_cnt;
	__le32 burst_पात_missing_next_frame_cnt;
	__le32 cts_समयout_collision;
	__le32 ack_or_ba_समयout_collision;
	काष्ठा statistics_tx_non_phy_agg agg;
	/*
	 * "tx_power" are optional parameters provided by uCode,
	 * 6000 series is the only device provide the inक्रमmation,
	 * Those are reserved fields क्रम all the other devices
	 */
	काष्ठा statistics_tx_घातer tx_घातer;
	__le32 reserved1;
पूर्ण __packed;


काष्ठा statistics_भाग अणु
	__le32 tx_on_a;
	__le32 tx_on_b;
	__le32 exec_समय;
	__le32 probe_समय;
	__le32 reserved1;
	__le32 reserved2;
पूर्ण __packed;

काष्ठा statistics_general_common अणु
	__le32 temperature;   /* radio temperature */
	__le32 temperature_m; /* radio voltage */
	काष्ठा statistics_dbg dbg;
	__le32 sleep_समय;
	__le32 slots_out;
	__le32 slots_idle;
	__le32 ttl_बारtamp;
	काष्ठा statistics_भाग भाग;
	__le32 rx_enable_counter;
	/*
	 * num_of_sos_states:
	 *  count the number of बार we have to re-tune
	 *  in order to get out of bad PHY status
	 */
	__le32 num_of_sos_states;
पूर्ण __packed;

काष्ठा statistics_bt_activity अणु
	/* Tx statistics */
	__le32 hi_priority_tx_req_cnt;
	__le32 hi_priority_tx_denied_cnt;
	__le32 lo_priority_tx_req_cnt;
	__le32 lo_priority_tx_denied_cnt;
	/* Rx statistics */
	__le32 hi_priority_rx_req_cnt;
	__le32 hi_priority_rx_denied_cnt;
	__le32 lo_priority_rx_req_cnt;
	__le32 lo_priority_rx_denied_cnt;
पूर्ण __packed;

काष्ठा statistics_general अणु
	काष्ठा statistics_general_common common;
	__le32 reserved2;
	__le32 reserved3;
पूर्ण __packed;

काष्ठा statistics_general_bt अणु
	काष्ठा statistics_general_common common;
	काष्ठा statistics_bt_activity activity;
	__le32 reserved2;
	__le32 reserved3;
पूर्ण __packed;

#घोषणा UCODE_STATISTICS_CLEAR_MSK		(0x1 << 0)
#घोषणा UCODE_STATISTICS_FREQUENCY_MSK		(0x1 << 1)
#घोषणा UCODE_STATISTICS_NARROW_BAND_MSK	(0x1 << 2)

/*
 * REPLY_STATISTICS_CMD = 0x9c,
 * all devices identical.
 *
 * This command triggers an immediate response containing uCode statistics.
 * The response is in the same क्रमmat as STATISTICS_NOTIFICATION 0x9d, below.
 *
 * If the CLEAR_STATS configuration flag is set, uCode will clear its
 * पूर्णांकernal copy of the statistics (counters) after issuing the response.
 * This flag करोes not affect STATISTICS_NOTIFICATIONs after beacons (see below).
 *
 * If the DISABLE_NOTIF configuration flag is set, uCode will not issue
 * STATISTICS_NOTIFICATIONs after received beacons (see below).  This flag
 * करोes not affect the response to the REPLY_STATISTICS_CMD 0x9c itself.
 */
#घोषणा IWL_STATS_CONF_CLEAR_STATS cpu_to_le32(0x1)	/* see above */
#घोषणा IWL_STATS_CONF_DISABLE_NOTIF cpu_to_le32(0x2)/* see above */
काष्ठा iwl_statistics_cmd अणु
	__le32 configuration_flags;	/* IWL_STATS_CONF_* */
पूर्ण __packed;

/*
 * STATISTICS_NOTIFICATION = 0x9d (notअगरication only, not a command)
 *
 * By शेष, uCode issues this notअगरication after receiving a beacon
 * जबतक associated.  To disable this behavior, set DISABLE_NOTIF flag in the
 * REPLY_STATISTICS_CMD 0x9c, above.
 *
 * Statistics counters जारी to increment beacon after beacon, but are
 * cleared when changing channels or when driver issues REPLY_STATISTICS_CMD
 * 0x9c with CLEAR_STATS bit set (see above).
 *
 * uCode also issues this notअगरication during scans.  uCode clears statistics
 * appropriately so that each notअगरication contains statistics क्रम only the
 * one channel that has just been scanned.
 */
#घोषणा STATISTICS_REPLY_FLG_BAND_24G_MSK         cpu_to_le32(0x2)
#घोषणा STATISTICS_REPLY_FLG_HT40_MODE_MSK        cpu_to_le32(0x8)

काष्ठा iwl_notअगर_statistics अणु
	__le32 flag;
	काष्ठा statistics_rx rx;
	काष्ठा statistics_tx tx;
	काष्ठा statistics_general general;
पूर्ण __packed;

काष्ठा iwl_bt_notअगर_statistics अणु
	__le32 flag;
	काष्ठा statistics_rx_bt rx;
	काष्ठा statistics_tx tx;
	काष्ठा statistics_general_bt general;
पूर्ण __packed;

/*
 * MISSED_BEACONS_NOTIFICATION = 0xa2 (notअगरication only, not a command)
 *
 * uCode send MISSED_BEACONS_NOTIFICATION to driver when detect beacon missed
 * in regardless of how many missed beacons, which mean when driver receive the
 * notअगरication, inside the command, it can find all the beacons inक्रमmation
 * which include number of total missed beacons, number of consecutive missed
 * beacons, number of beacons received and number of beacons expected to
 * receive.
 *
 * If uCode detected consecutive_missed_beacons > 5, it will reset the radio
 * in order to bring the radio/PHY back to working state; which has no relation
 * to when driver will perक्रमm sensitivity calibration.
 *
 * Driver should set it own missed_beacon_threshold to decide when to perक्रमm
 * sensitivity calibration based on number of consecutive missed beacons in
 * order to improve overall perक्रमmance, especially in noisy environment.
 *
 */

#घोषणा IWL_MISSED_BEACON_THRESHOLD_MIN	(1)
#घोषणा IWL_MISSED_BEACON_THRESHOLD_DEF	(5)
#घोषणा IWL_MISSED_BEACON_THRESHOLD_MAX	IWL_MISSED_BEACON_THRESHOLD_DEF

काष्ठा iwl_missed_beacon_notअगर अणु
	__le32 consecutive_missed_beacons;
	__le32 total_missed_becons;
	__le32 num_expected_beacons;
	__le32 num_recvd_beacons;
पूर्ण __packed;


/******************************************************************************
 * (11)
 * Rx Calibration Commands:
 *
 * With the uCode used क्रम खोलो source drivers, most Tx calibration (except
 * क्रम Tx Power) and most Rx calibration is करोne by uCode during the
 * "initialize" phase of uCode boot.  Driver must calibrate only:
 *
 * 1)  Tx घातer (depends on temperature), described अन्यथाwhere
 * 2)  Receiver gain balance (optimize MIMO, and detect disconnected antennas)
 * 3)  Receiver sensitivity (to optimize संकेत detection)
 *
 *****************************************************************************/

/**
 * SENSITIVITY_CMD = 0xa8 (command, has simple generic response)
 *
 * This command sets up the Rx संकेत detector क्रम a sensitivity level that
 * is high enough to lock onto all संकेतs within the associated network,
 * but low enough to ignore संकेतs that are below a certain threshold, so as
 * not to have too many "false alarms".  False alarms are संकेतs that the
 * Rx DSP tries to lock onto, but then discards after determining that they
 * are noise.
 *
 * The optimum number of false alarms is between 5 and 50 per 200 TUs
 * (200 * 1024 uSecs, i.e. 204.8 milliseconds) of actual Rx समय (i.e.
 * समय listening, not transmitting).  Driver must adjust sensitivity so that
 * the ratio of actual false alarms to actual Rx समय falls within this range.
 *
 * While associated, uCode delivers STATISTICS_NOTIFICATIONs after each
 * received beacon.  These provide inक्रमmation to the driver to analyze the
 * sensitivity.  Don't analyze statistics that come in from scanning, or any
 * other non-associated-network source.  Pertinent statistics include:
 *
 * From "general" statistics (काष्ठा statistics_rx_non_phy):
 *
 * (beacon_energy_[abc] & 0x0FF00) >> 8 (अचिन्हित, higher value is lower level)
 *   Measure of energy of desired संकेत.  Used क्रम establishing a level
 *   below which the device करोes not detect संकेतs.
 *
 * (beacon_silence_rssi_[abc] & 0x0FF00) >> 8 (अचिन्हित, units in dB)
 *   Measure of background noise in silent period after beacon.
 *
 * channel_load
 *   uSecs of actual Rx समय during beacon period (varies according to
 *   how much समय was spent transmitting).
 *
 * From "cck" and "ofdm" statistics (काष्ठा statistics_rx_phy), separately:
 *
 * false_alarm_cnt
 *   Signal locks abanकरोned early (beक्रमe phy-level header).
 *
 * plcp_err
 *   Signal locks abanकरोned late (during phy-level header).
 *
 * NOTE:  Both false_alarm_cnt and plcp_err increment monotonically from
 *        beacon to beacon, i.e. each value is an accumulation of all errors
 *        beक्रमe and including the latest beacon.  Values will wrap around to 0
 *        after counting up to 2^32 - 1.  Driver must dअगरferentiate vs.
 *        previous beacon's values to determine # false alarms in the current
 *        beacon period.
 *
 * Total number of false alarms = false_alarms + plcp_errs
 *
 * For OFDM, adjust the following table entries in काष्ठा iwl_sensitivity_cmd
 * (notice that the start poपूर्णांकs क्रम OFDM are at or बंद to settings क्रम
 * maximum sensitivity):
 *
 *                                             START  /  MIN  /  MAX
 *   HD_AUTO_CORR32_X1_TH_ADD_MIN_INDEX          90   /   85  /  120
 *   HD_AUTO_CORR32_X1_TH_ADD_MIN_MRC_INDEX     170   /  170  /  210
 *   HD_AUTO_CORR32_X4_TH_ADD_MIN_INDEX         105   /  105  /  140
 *   HD_AUTO_CORR32_X4_TH_ADD_MIN_MRC_INDEX     220   /  220  /  270
 *
 *   If actual rate of OFDM false alarms (+ plcp_errors) is too high
 *   (greater than 50 क्रम each 204.8 msecs listening), reduce sensitivity
 *   by *adding* 1 to all 4 of the table entries above, up to the max क्रम
 *   each entry.  Conversely, अगर false alarm rate is too low (less than 5
 *   क्रम each 204.8 msecs listening), *subtract* 1 from each entry to
 *   increase sensitivity.
 *
 * For CCK sensitivity, keep track of the following:
 *
 *   1).  20-beacon history of maximum background noise, indicated by
 *        (beacon_silence_rssi_[abc] & 0x0FF00), units in dB, across the
 *        3 receivers.  For any given beacon, the "silence reference" is
 *        the maximum of last 60 samples (20 beacons * 3 receivers).
 *
 *   2).  10-beacon history of strongest संकेत level, as indicated
 *        by (beacon_energy_[abc] & 0x0FF00) >> 8, across the 3 receivers,
 *        i.e. the strength of the संकेत through the best receiver at the
 *        moment.  These measurements are "upside down", with lower values
 *        क्रम stronger संकेतs, so max energy will be *minimum* value.
 *
 *        Then क्रम any given beacon, the driver must determine the *weakest*
 *        of the strongest संकेतs; this is the minimum level that needs to be
 *        successfully detected, when using the best receiver at the moment.
 *        "Max cck energy" is the maximum (higher value means lower energy!)
 *        of the last 10 minima.  Once this is determined, driver must add
 *        a little margin by adding "6" to it.
 *
 *   3).  Number of consecutive beacon periods with too few false alarms.
 *        Reset this to 0 at the first beacon period that falls within the
 *        "good" range (5 to 50 false alarms per 204.8 milliseconds rx).
 *
 * Then, adjust the following CCK table entries in काष्ठा iwl_sensitivity_cmd
 * (notice that the start poपूर्णांकs क्रम CCK are at maximum sensitivity):
 *
 *                                             START  /  MIN  /  MAX
 *   HD_AUTO_CORR40_X4_TH_ADD_MIN_INDEX         125   /  125  /  200
 *   HD_AUTO_CORR40_X4_TH_ADD_MIN_MRC_INDEX     200   /  200  /  400
 *   HD_MIN_ENERGY_CCK_DET_INDEX                100   /    0  /  100
 *
 *   If actual rate of CCK false alarms (+ plcp_errors) is too high
 *   (greater than 50 क्रम each 204.8 msecs listening), method क्रम reducing
 *   sensitivity is:
 *
 *   1)  *Add* 3 to value in HD_AUTO_CORR40_X4_TH_ADD_MIN_MRC_INDEX,
 *       up to max 400.
 *
 *   2)  If current value in HD_AUTO_CORR40_X4_TH_ADD_MIN_INDEX is < 160,
 *       sensitivity has been reduced a signअगरicant amount; bring it up to
 *       a moderate 161.  Otherwise, *add* 3, up to max 200.
 *
 *   3)  a)  If current value in HD_AUTO_CORR40_X4_TH_ADD_MIN_INDEX is > 160,
 *       sensitivity has been reduced only a moderate or small amount;
 *       *subtract* 2 from value in HD_MIN_ENERGY_CCK_DET_INDEX,
 *       करोwn to min 0.  Otherwise (अगर gain has been signअगरicantly reduced),
 *       करोn't change the HD_MIN_ENERGY_CCK_DET_INDEX value.
 *
 *       b)  Save a snapshot of the "silence reference".
 *
 *   If actual rate of CCK false alarms (+ plcp_errors) is too low
 *   (less than 5 क्रम each 204.8 msecs listening), method क्रम increasing
 *   sensitivity is used only अगर:
 *
 *   1a)  Previous beacon did not have too many false alarms
 *   1b)  AND dअगरference between previous "silence reference" and current
 *        "silence reference" (prev - current) is 2 or more,
 *   OR 2)  100 or more consecutive beacon periods have had rate of
 *          less than 5 false alarms per 204.8 milliseconds rx समय.
 *
 *   Method क्रम increasing sensitivity:
 *
 *   1)  *Subtract* 3 from value in HD_AUTO_CORR40_X4_TH_ADD_MIN_INDEX,
 *       करोwn to min 125.
 *
 *   2)  *Subtract* 3 from value in HD_AUTO_CORR40_X4_TH_ADD_MIN_MRC_INDEX,
 *       करोwn to min 200.
 *
 *   3)  *Add* 2 to value in HD_MIN_ENERGY_CCK_DET_INDEX, up to max 100.
 *
 *   If actual rate of CCK false alarms (+ plcp_errors) is within good range
 *   (between 5 and 50 क्रम each 204.8 msecs listening):
 *
 *   1)  Save a snapshot of the silence reference.
 *
 *   2)  If previous beacon had too many CCK false alarms (+ plcp_errors),
 *       give some extra margin to energy threshold by *subtracting* 8
 *       from value in HD_MIN_ENERGY_CCK_DET_INDEX.
 *
 *   For all हालs (too few, too many, good range), make sure that the CCK
 *   detection threshold (energy) is below the energy level क्रम robust
 *   detection over the past 10 beacon periods, the "Max cck energy".
 *   Lower values mean higher energy; this means making sure that the value
 *   in HD_MIN_ENERGY_CCK_DET_INDEX is at or *above* "Max cck energy".
 *
 */

/*
 * Table entries in SENSITIVITY_CMD (काष्ठा iwl_sensitivity_cmd)
 */
#घोषणा HD_TABLE_SIZE  (11)	/* number of entries */
#घोषणा HD_MIN_ENERGY_CCK_DET_INDEX                 (0)	/* table indexes */
#घोषणा HD_MIN_ENERGY_OFDM_DET_INDEX                (1)
#घोषणा HD_AUTO_CORR32_X1_TH_ADD_MIN_INDEX          (2)
#घोषणा HD_AUTO_CORR32_X1_TH_ADD_MIN_MRC_INDEX      (3)
#घोषणा HD_AUTO_CORR40_X4_TH_ADD_MIN_MRC_INDEX      (4)
#घोषणा HD_AUTO_CORR32_X4_TH_ADD_MIN_INDEX          (5)
#घोषणा HD_AUTO_CORR32_X4_TH_ADD_MIN_MRC_INDEX      (6)
#घोषणा HD_BARKER_CORR_TH_ADD_MIN_INDEX             (7)
#घोषणा HD_BARKER_CORR_TH_ADD_MIN_MRC_INDEX         (8)
#घोषणा HD_AUTO_CORR40_X4_TH_ADD_MIN_INDEX          (9)
#घोषणा HD_OFDM_ENERGY_TH_IN_INDEX                  (10)

/*
 * Additional table entries in enhance SENSITIVITY_CMD
 */
#घोषणा HD_INA_NON_SQUARE_DET_OFDM_INDEX		(11)
#घोषणा HD_INA_NON_SQUARE_DET_CCK_INDEX			(12)
#घोषणा HD_CORR_11_INSTEAD_OF_CORR_9_EN_INDEX		(13)
#घोषणा HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_INDEX		(14)
#घोषणा HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_INDEX	(15)
#घोषणा HD_OFDM_NON_SQUARE_DET_SLOPE_INDEX		(16)
#घोषणा HD_OFDM_NON_SQUARE_DET_INTERCEPT_INDEX		(17)
#घोषणा HD_CCK_NON_SQUARE_DET_SLOPE_MRC_INDEX		(18)
#घोषणा HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_INDEX	(19)
#घोषणा HD_CCK_NON_SQUARE_DET_SLOPE_INDEX		(20)
#घोषणा HD_CCK_NON_SQUARE_DET_INTERCEPT_INDEX		(21)
#घोषणा HD_RESERVED					(22)

/* number of entries क्रम enhanced tbl */
#घोषणा ENHANCE_HD_TABLE_SIZE  (23)

/* number of additional entries क्रम enhanced tbl */
#घोषणा ENHANCE_HD_TABLE_ENTRIES  (ENHANCE_HD_TABLE_SIZE - HD_TABLE_SIZE)

#घोषणा HD_INA_NON_SQUARE_DET_OFDM_DATA_V1		cpu_to_le16(0)
#घोषणा HD_INA_NON_SQUARE_DET_CCK_DATA_V1		cpu_to_le16(0)
#घोषणा HD_CORR_11_INSTEAD_OF_CORR_9_EN_DATA_V1		cpu_to_le16(0)
#घोषणा HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_DATA_V1	cpu_to_le16(668)
#घोषणा HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V1	cpu_to_le16(4)
#घोषणा HD_OFDM_NON_SQUARE_DET_SLOPE_DATA_V1		cpu_to_le16(486)
#घोषणा HD_OFDM_NON_SQUARE_DET_INTERCEPT_DATA_V1	cpu_to_le16(37)
#घोषणा HD_CCK_NON_SQUARE_DET_SLOPE_MRC_DATA_V1		cpu_to_le16(853)
#घोषणा HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V1	cpu_to_le16(4)
#घोषणा HD_CCK_NON_SQUARE_DET_SLOPE_DATA_V1		cpu_to_le16(476)
#घोषणा HD_CCK_NON_SQUARE_DET_INTERCEPT_DATA_V1		cpu_to_le16(99)

#घोषणा HD_INA_NON_SQUARE_DET_OFDM_DATA_V2		cpu_to_le16(1)
#घोषणा HD_INA_NON_SQUARE_DET_CCK_DATA_V2		cpu_to_le16(1)
#घोषणा HD_CORR_11_INSTEAD_OF_CORR_9_EN_DATA_V2		cpu_to_le16(1)
#घोषणा HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_DATA_V2	cpu_to_le16(600)
#घोषणा HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V2	cpu_to_le16(40)
#घोषणा HD_OFDM_NON_SQUARE_DET_SLOPE_DATA_V2		cpu_to_le16(486)
#घोषणा HD_OFDM_NON_SQUARE_DET_INTERCEPT_DATA_V2	cpu_to_le16(45)
#घोषणा HD_CCK_NON_SQUARE_DET_SLOPE_MRC_DATA_V2		cpu_to_le16(853)
#घोषणा HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V2	cpu_to_le16(60)
#घोषणा HD_CCK_NON_SQUARE_DET_SLOPE_DATA_V2		cpu_to_le16(476)
#घोषणा HD_CCK_NON_SQUARE_DET_INTERCEPT_DATA_V2		cpu_to_le16(99)


/* Control field in काष्ठा iwl_sensitivity_cmd */
#घोषणा SENSITIVITY_CMD_CONTROL_DEFAULT_TABLE	cpu_to_le16(0)
#घोषणा SENSITIVITY_CMD_CONTROL_WORK_TABLE	cpu_to_le16(1)

/**
 * काष्ठा iwl_sensitivity_cmd
 * @control:  (1) updates working table, (0) updates शेष table
 * @table:  energy threshold values, use HD_* as index पूर्णांकo table
 *
 * Always use "1" in "control" to update uCode's working table and DSP.
 */
काष्ठा iwl_sensitivity_cmd अणु
	__le16 control;			/* always use "1" */
	__le16 table[HD_TABLE_SIZE];	/* use HD_* as index */
पूर्ण __packed;

/*
 *
 */
काष्ठा iwl_enhance_sensitivity_cmd अणु
	__le16 control;			/* always use "1" */
	__le16 enhance_table[ENHANCE_HD_TABLE_SIZE];	/* use HD_* as index */
पूर्ण __packed;


/**
 * REPLY_PHY_CALIBRATION_CMD = 0xb0 (command, has simple generic response)
 *
 * This command sets the relative gains of agn device's 3 radio receiver chains.
 *
 * After the first association, driver should accumulate संकेत and noise
 * statistics from the STATISTICS_NOTIFICATIONs that follow the first 20
 * beacons from the associated network (करोn't collect statistics that come
 * in from scanning, or any other non-network source).
 *
 * DISCONNECTED ANTENNA:
 *
 * Driver should determine which antennas are actually connected, by comparing
 * average beacon संकेत levels क्रम the 3 Rx chains.  Accumulate (add) the
 * following values over 20 beacons, one accumulator क्रम each of the chains
 * a/b/c, from काष्ठा statistics_rx_non_phy:
 *
 * beacon_rssi_[abc] & 0x0FF (अचिन्हित, units in dB)
 *
 * Find the strongest संकेत from among a/b/c.  Compare the other two to the
 * strongest.  If any संकेत is more than 15 dB (बार 20, unless you
 * भागide the accumulated values by 20) below the strongest, the driver
 * considers that antenna to be disconnected, and should not try to use that
 * antenna/chain क्रम Rx or Tx.  If both A and B seem to be disconnected,
 * driver should declare the stronger one as connected, and attempt to use it
 * (A and B are the only 2 Tx chains!).
 *
 *
 * RX BALANCE:
 *
 * Driver should balance the 3 receivers (but just the ones that are connected
 * to antennas, see above) क्रम gain, by comparing the average संकेत levels
 * detected during the silence after each beacon (background noise).
 * Accumulate (add) the following values over 20 beacons, one accumulator क्रम
 * each of the chains a/b/c, from काष्ठा statistics_rx_non_phy:
 *
 * beacon_silence_rssi_[abc] & 0x0FF (अचिन्हित, units in dB)
 *
 * Find the weakest background noise level from among a/b/c.  This Rx chain
 * will be the reference, with 0 gain adjusपंचांगent.  Attenuate other channels by
 * finding noise dअगरference:
 *
 * (accum_noise[i] - accum_noise[reference]) / 30
 *
 * The "30" adjusts the dB in the 20 accumulated samples to units of 1.5 dB.
 * For use in dअगरf_gain_[abc] fields of काष्ठा iwl_calibration_cmd, the
 * driver should limit the dअगरference results to a range of 0-3 (0-4.5 dB),
 * and set bit 2 to indicate "reduce gain".  The value क्रम the reference
 * (weakest) chain should be "0".
 *
 * dअगरf_gain_[abc] bit fields:
 *   2: (1) reduce gain, (0) increase gain
 * 1-0: amount of gain, units of 1.5 dB
 */

/* Phy calibration command क्रम series */
क्रमागत अणु
	IWL_PHY_CALIBRATE_DC_CMD		= 8,
	IWL_PHY_CALIBRATE_LO_CMD		= 9,
	IWL_PHY_CALIBRATE_TX_IQ_CMD		= 11,
	IWL_PHY_CALIBRATE_CRYSTAL_FRQ_CMD	= 15,
	IWL_PHY_CALIBRATE_BASE_BAND_CMD		= 16,
	IWL_PHY_CALIBRATE_TX_IQ_PERD_CMD	= 17,
	IWL_PHY_CALIBRATE_TEMP_OFFSET_CMD	= 18,
पूर्ण;

/* This क्रमागत defines the biपंचांगap of various calibrations to enable in both
 * init ucode and runसमय ucode through CALIBRATION_CFG_CMD.
 */
क्रमागत iwl_ucode_calib_cfg अणु
	IWL_CALIB_CFG_RX_BB_IDX			= BIT(0),
	IWL_CALIB_CFG_DC_IDX			= BIT(1),
	IWL_CALIB_CFG_LO_IDX			= BIT(2),
	IWL_CALIB_CFG_TX_IQ_IDX			= BIT(3),
	IWL_CALIB_CFG_RX_IQ_IDX			= BIT(4),
	IWL_CALIB_CFG_NOISE_IDX			= BIT(5),
	IWL_CALIB_CFG_CRYSTAL_IDX		= BIT(6),
	IWL_CALIB_CFG_TEMPERATURE_IDX		= BIT(7),
	IWL_CALIB_CFG_PAPD_IDX			= BIT(8),
	IWL_CALIB_CFG_SENSITIVITY_IDX		= BIT(9),
	IWL_CALIB_CFG_TX_PWR_IDX		= BIT(10),
पूर्ण;

#घोषणा IWL_CALIB_INIT_CFG_ALL	cpu_to_le32(IWL_CALIB_CFG_RX_BB_IDX |	\
					IWL_CALIB_CFG_DC_IDX |		\
					IWL_CALIB_CFG_LO_IDX |		\
					IWL_CALIB_CFG_TX_IQ_IDX |	\
					IWL_CALIB_CFG_RX_IQ_IDX |	\
					IWL_CALIB_CFG_CRYSTAL_IDX)

#घोषणा IWL_CALIB_RT_CFG_ALL	cpu_to_le32(IWL_CALIB_CFG_RX_BB_IDX |	\
					IWL_CALIB_CFG_DC_IDX |		\
					IWL_CALIB_CFG_LO_IDX |		\
					IWL_CALIB_CFG_TX_IQ_IDX |	\
					IWL_CALIB_CFG_RX_IQ_IDX |	\
					IWL_CALIB_CFG_TEMPERATURE_IDX |	\
					IWL_CALIB_CFG_PAPD_IDX |	\
					IWL_CALIB_CFG_TX_PWR_IDX |	\
					IWL_CALIB_CFG_CRYSTAL_IDX)

#घोषणा IWL_CALIB_CFG_FLAG_SEND_COMPLETE_NTFY_MSK	cpu_to_le32(BIT(0))

काष्ठा iwl_calib_cfg_elmnt_s अणु
	__le32 is_enable;
	__le32 start;
	__le32 send_res;
	__le32 apply_res;
	__le32 reserved;
पूर्ण __packed;

काष्ठा iwl_calib_cfg_status_s अणु
	काष्ठा iwl_calib_cfg_elmnt_s once;
	काष्ठा iwl_calib_cfg_elmnt_s perd;
	__le32 flags;
पूर्ण __packed;

काष्ठा iwl_calib_cfg_cmd अणु
	काष्ठा iwl_calib_cfg_status_s ucd_calib_cfg;
	काष्ठा iwl_calib_cfg_status_s drv_calib_cfg;
	__le32 reserved1;
पूर्ण __packed;

काष्ठा iwl_calib_hdr अणु
	u8 op_code;
	u8 first_group;
	u8 groups_num;
	u8 data_valid;
पूर्ण __packed;

काष्ठा iwl_calib_cmd अणु
	काष्ठा iwl_calib_hdr hdr;
	u8 data[];
पूर्ण __packed;

काष्ठा iwl_calib_xtal_freq_cmd अणु
	काष्ठा iwl_calib_hdr hdr;
	u8 cap_pin1;
	u8 cap_pin2;
	u8 pad[2];
पूर्ण __packed;

#घोषणा DEFAULT_RADIO_SENSOR_OFFSET    cpu_to_le16(2700)
काष्ठा iwl_calib_temperature_offset_cmd अणु
	काष्ठा iwl_calib_hdr hdr;
	__le16 radio_sensor_offset;
	__le16 reserved;
पूर्ण __packed;

काष्ठा iwl_calib_temperature_offset_v2_cmd अणु
	काष्ठा iwl_calib_hdr hdr;
	__le16 radio_sensor_offset_high;
	__le16 radio_sensor_offset_low;
	__le16 burntVoltageRef;
	__le16 reserved;
पूर्ण __packed;

/* IWL_PHY_CALIBRATE_CHAIN_NOISE_RESET_CMD */
काष्ठा iwl_calib_chain_noise_reset_cmd अणु
	काष्ठा iwl_calib_hdr hdr;
	u8 data[];
पूर्ण;

/* IWL_PHY_CALIBRATE_CHAIN_NOISE_GAIN_CMD */
काष्ठा iwl_calib_chain_noise_gain_cmd अणु
	काष्ठा iwl_calib_hdr hdr;
	u8 delta_gain_1;
	u8 delta_gain_2;
	u8 pad[2];
पूर्ण __packed;

/******************************************************************************
 * (12)
 * Miscellaneous Commands:
 *
 *****************************************************************************/

/*
 * LEDs Command & Response
 * REPLY_LEDS_CMD = 0x48 (command, has simple generic response)
 *
 * For each of 3 possible LEDs (Activity/Link/Tech, selected by "id" field),
 * this command turns it on or off, or sets up a periodic blinking cycle.
 */
काष्ठा iwl_led_cmd अणु
	__le32 पूर्णांकerval;	/* "interval" in uSec */
	u8 id;			/* 1: Activity, 2: Link, 3: Tech */
	u8 off;			/* # पूर्णांकervals off जबतक blinking;
				 * "0", with >0 "on" value, turns LED on */
	u8 on;			/* # पूर्णांकervals on जबतक blinking;
				 * "0", regardless of "off", turns LED off */
	u8 reserved;
पूर्ण __packed;

/*
 * station priority table entries
 * also used as potential "events" value क्रम both
 * COEX_MEDIUM_NOTIFICATION and COEX_EVENT_CMD
 */

/*
 * COEX events entry flag masks
 * RP - Requested Priority
 * WP - Win Medium Priority: priority asचिन्हित when the contention has been won
 */
#घोषणा COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG        (0x1)
#घोषणा COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG        (0x2)
#घोषणा COEX_EVT_FLAG_DELAY_MEDIUM_FREE_NTFY_FLG  (0x4)

#घोषणा COEX_CU_UNASSOC_IDLE_RP               4
#घोषणा COEX_CU_UNASSOC_MANUAL_SCAN_RP        4
#घोषणा COEX_CU_UNASSOC_AUTO_SCAN_RP          4
#घोषणा COEX_CU_CALIBRATION_RP                4
#घोषणा COEX_CU_PERIODIC_CALIBRATION_RP       4
#घोषणा COEX_CU_CONNECTION_ESTAB_RP           4
#घोषणा COEX_CU_ASSOCIATED_IDLE_RP            4
#घोषणा COEX_CU_ASSOC_MANUAL_SCAN_RP          4
#घोषणा COEX_CU_ASSOC_AUTO_SCAN_RP            4
#घोषणा COEX_CU_ASSOC_ACTIVE_LEVEL_RP         4
#घोषणा COEX_CU_RF_ON_RP                      6
#घोषणा COEX_CU_RF_OFF_RP                     4
#घोषणा COEX_CU_STAND_ALONE_DEBUG_RP          6
#घोषणा COEX_CU_IPAN_ASSOC_LEVEL_RP           4
#घोषणा COEX_CU_RSRVD1_RP                     4
#घोषणा COEX_CU_RSRVD2_RP                     4

#घोषणा COEX_CU_UNASSOC_IDLE_WP               3
#घोषणा COEX_CU_UNASSOC_MANUAL_SCAN_WP        3
#घोषणा COEX_CU_UNASSOC_AUTO_SCAN_WP          3
#घोषणा COEX_CU_CALIBRATION_WP                3
#घोषणा COEX_CU_PERIODIC_CALIBRATION_WP       3
#घोषणा COEX_CU_CONNECTION_ESTAB_WP           3
#घोषणा COEX_CU_ASSOCIATED_IDLE_WP            3
#घोषणा COEX_CU_ASSOC_MANUAL_SCAN_WP          3
#घोषणा COEX_CU_ASSOC_AUTO_SCAN_WP            3
#घोषणा COEX_CU_ASSOC_ACTIVE_LEVEL_WP         3
#घोषणा COEX_CU_RF_ON_WP                      3
#घोषणा COEX_CU_RF_OFF_WP                     3
#घोषणा COEX_CU_STAND_ALONE_DEBUG_WP          6
#घोषणा COEX_CU_IPAN_ASSOC_LEVEL_WP           3
#घोषणा COEX_CU_RSRVD1_WP                     3
#घोषणा COEX_CU_RSRVD2_WP                     3

#घोषणा COEX_UNASSOC_IDLE_FLAGS                     0
#घोषणा COEX_UNASSOC_MANUAL_SCAN_FLAGS		\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG)
#घोषणा COEX_UNASSOC_AUTO_SCAN_FLAGS		\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG)
#घोषणा COEX_CALIBRATION_FLAGS			\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG)
#घोषणा COEX_PERIODIC_CALIBRATION_FLAGS             0
/*
 * COEX_CONNECTION_ESTAB:
 * we need DELAY_MEDIUM_FREE_NTFY to let WiMAX disconnect from network.
 */
#घोषणा COEX_CONNECTION_ESTAB_FLAGS		\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG |	\
	COEX_EVT_FLAG_DELAY_MEDIUM_FREE_NTFY_FLG)
#घोषणा COEX_ASSOCIATED_IDLE_FLAGS                  0
#घोषणा COEX_ASSOC_MANUAL_SCAN_FLAGS		\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG)
#घोषणा COEX_ASSOC_AUTO_SCAN_FLAGS		\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	 COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG)
#घोषणा COEX_ASSOC_ACTIVE_LEVEL_FLAGS               0
#घोषणा COEX_RF_ON_FLAGS                            0
#घोषणा COEX_RF_OFF_FLAGS                           0
#घोषणा COEX_STAND_ALONE_DEBUG_FLAGS		\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	 COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG)
#घोषणा COEX_IPAN_ASSOC_LEVEL_FLAGS		\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	 COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG |	\
	 COEX_EVT_FLAG_DELAY_MEDIUM_FREE_NTFY_FLG)
#घोषणा COEX_RSRVD1_FLAGS                           0
#घोषणा COEX_RSRVD2_FLAGS                           0
/*
 * COEX_CU_RF_ON is the event wrapping all radio ownership.
 * We need DELAY_MEDIUM_FREE_NTFY to let WiMAX disconnect from network.
 */
#घोषणा COEX_CU_RF_ON_FLAGS			\
	(COEX_EVT_FLAG_MEDIUM_FREE_NTFY_FLG |	\
	 COEX_EVT_FLAG_MEDIUM_ACTV_NTFY_FLG |	\
	 COEX_EVT_FLAG_DELAY_MEDIUM_FREE_NTFY_FLG)


क्रमागत अणु
	/* un-association part */
	COEX_UNASSOC_IDLE		= 0,
	COEX_UNASSOC_MANUAL_SCAN	= 1,
	COEX_UNASSOC_AUTO_SCAN		= 2,
	/* calibration */
	COEX_CALIBRATION		= 3,
	COEX_PERIODIC_CALIBRATION	= 4,
	/* connection */
	COEX_CONNECTION_ESTAB		= 5,
	/* association part */
	COEX_ASSOCIATED_IDLE		= 6,
	COEX_ASSOC_MANUAL_SCAN		= 7,
	COEX_ASSOC_AUTO_SCAN		= 8,
	COEX_ASSOC_ACTIVE_LEVEL		= 9,
	/* RF ON/OFF */
	COEX_RF_ON			= 10,
	COEX_RF_OFF			= 11,
	COEX_STAND_ALONE_DEBUG		= 12,
	/* IPAN */
	COEX_IPAN_ASSOC_LEVEL		= 13,
	/* reserved */
	COEX_RSRVD1			= 14,
	COEX_RSRVD2			= 15,
	COEX_NUM_OF_EVENTS		= 16
पूर्ण;

/*
 * Coexistence WIFI/WIMAX  Command
 * COEX_PRIORITY_TABLE_CMD = 0x5a
 *
 */
काष्ठा iwl_wimax_coex_event_entry अणु
	u8 request_prio;
	u8 win_medium_prio;
	u8 reserved;
	u8 flags;
पूर्ण __packed;

/* COEX flag masks */

/* Station table is valid */
#घोषणा COEX_FLAGS_STA_TABLE_VALID_MSK      (0x1)
/* UnMask wake up src at unassociated sleep */
#घोषणा COEX_FLAGS_UNASSOC_WA_UNMASK_MSK    (0x4)
/* UnMask wake up src at associated sleep */
#घोषणा COEX_FLAGS_ASSOC_WA_UNMASK_MSK      (0x8)
/* Enable CoEx feature. */
#घोषणा COEX_FLAGS_COEX_ENABLE_MSK          (0x80)

काष्ठा iwl_wimax_coex_cmd अणु
	u8 flags;
	u8 reserved[3];
	काष्ठा iwl_wimax_coex_event_entry sta_prio[COEX_NUM_OF_EVENTS];
पूर्ण __packed;

/*
 * Coexistence MEDIUM NOTIFICATION
 * COEX_MEDIUM_NOTIFICATION = 0x5b
 *
 * notअगरication from uCode to host to indicate medium changes
 *
 */
/*
 * status field
 * bit 0 - 2: medium status
 * bit 3: medium change indication
 * bit 4 - 31: reserved
 */
/* status option values, (0 - 2 bits) */
#घोषणा COEX_MEDIUM_BUSY	(0x0) /* radio beदीर्घs to WiMAX */
#घोषणा COEX_MEDIUM_ACTIVE	(0x1) /* radio beदीर्घs to WiFi */
#घोषणा COEX_MEDIUM_PRE_RELEASE	(0x2) /* received radio release */
#घोषणा COEX_MEDIUM_MSK		(0x7)

/* send notअगरication status (1 bit) */
#घोषणा COEX_MEDIUM_CHANGED	(0x8)
#घोषणा COEX_MEDIUM_CHANGED_MSK	(0x8)
#घोषणा COEX_MEDIUM_SHIFT	(3)

काष्ठा iwl_coex_medium_notअगरication अणु
	__le32 status;
	__le32 events;
पूर्ण __packed;

/*
 * Coexistence EVENT  Command
 * COEX_EVENT_CMD = 0x5c
 *
 * send from host to uCode क्रम coex event request.
 */
/* flags options */
#घोषणा COEX_EVENT_REQUEST_MSK	(0x1)

काष्ठा iwl_coex_event_cmd अणु
	u8 flags;
	u8 event;
	__le16 reserved;
पूर्ण __packed;

काष्ठा iwl_coex_event_resp अणु
	__le32 status;
पूर्ण __packed;


/******************************************************************************
 * Bluetooth Coexistence commands
 *
 *****************************************************************************/

/*
 * BT Status notअगरication
 * REPLY_BT_COEX_PROखाता_NOTIF = 0xce
 */
क्रमागत iwl_bt_coex_profile_traffic_load अणु
	IWL_BT_COEX_TRAFFIC_LOAD_NONE = 	0,
	IWL_BT_COEX_TRAFFIC_LOAD_LOW =		1,
	IWL_BT_COEX_TRAFFIC_LOAD_HIGH = 	2,
	IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS =	3,
/*
 * There are no more even though below is a u8, the
 * indication from the BT device only has two bits.
 */
पूर्ण;

#घोषणा BT_SESSION_ACTIVITY_1_UART_MSG		0x1
#घोषणा BT_SESSION_ACTIVITY_2_UART_MSG		0x2

/* BT UART message - Share Part (BT -> WiFi) */
#घोषणा BT_UART_MSG_FRAME1MSGTYPE_POS		(0)
#घोषणा BT_UART_MSG_FRAME1MSGTYPE_MSK		\
		(0x7 << BT_UART_MSG_FRAME1MSGTYPE_POS)
#घोषणा BT_UART_MSG_FRAME1SSN_POS		(3)
#घोषणा BT_UART_MSG_FRAME1SSN_MSK		\
		(0x3 << BT_UART_MSG_FRAME1SSN_POS)
#घोषणा BT_UART_MSG_FRAME1UPDATEREQ_POS		(5)
#घोषणा BT_UART_MSG_FRAME1UPDATEREQ_MSK		\
		(0x1 << BT_UART_MSG_FRAME1UPDATEREQ_POS)
#घोषणा BT_UART_MSG_FRAME1RESERVED_POS		(6)
#घोषणा BT_UART_MSG_FRAME1RESERVED_MSK		\
		(0x3 << BT_UART_MSG_FRAME1RESERVED_POS)

#घोषणा BT_UART_MSG_FRAME2OPENCONNECTIONS_POS	(0)
#घोषणा BT_UART_MSG_FRAME2OPENCONNECTIONS_MSK	\
		(0x3 << BT_UART_MSG_FRAME2OPENCONNECTIONS_POS)
#घोषणा BT_UART_MSG_FRAME2TRAFFICLOAD_POS	(2)
#घोषणा BT_UART_MSG_FRAME2TRAFFICLOAD_MSK	\
		(0x3 << BT_UART_MSG_FRAME2TRAFFICLOAD_POS)
#घोषणा BT_UART_MSG_FRAME2CHLSEQN_POS		(4)
#घोषणा BT_UART_MSG_FRAME2CHLSEQN_MSK		\
		(0x1 << BT_UART_MSG_FRAME2CHLSEQN_POS)
#घोषणा BT_UART_MSG_FRAME2INBAND_POS		(5)
#घोषणा BT_UART_MSG_FRAME2INBAND_MSK		\
		(0x1 << BT_UART_MSG_FRAME2INBAND_POS)
#घोषणा BT_UART_MSG_FRAME2RESERVED_POS		(6)
#घोषणा BT_UART_MSG_FRAME2RESERVED_MSK		\
		(0x3 << BT_UART_MSG_FRAME2RESERVED_POS)

#घोषणा BT_UART_MSG_FRAME3SCOESCO_POS		(0)
#घोषणा BT_UART_MSG_FRAME3SCOESCO_MSK		\
		(0x1 << BT_UART_MSG_FRAME3SCOESCO_POS)
#घोषणा BT_UART_MSG_FRAME3SNIFF_POS		(1)
#घोषणा BT_UART_MSG_FRAME3SNIFF_MSK		\
		(0x1 << BT_UART_MSG_FRAME3SNIFF_POS)
#घोषणा BT_UART_MSG_FRAME3A2DP_POS		(2)
#घोषणा BT_UART_MSG_FRAME3A2DP_MSK		\
		(0x1 << BT_UART_MSG_FRAME3A2DP_POS)
#घोषणा BT_UART_MSG_FRAME3ACL_POS		(3)
#घोषणा BT_UART_MSG_FRAME3ACL_MSK		\
		(0x1 << BT_UART_MSG_FRAME3ACL_POS)
#घोषणा BT_UART_MSG_FRAME3MASTER_POS		(4)
#घोषणा BT_UART_MSG_FRAME3MASTER_MSK		\
		(0x1 << BT_UART_MSG_FRAME3MASTER_POS)
#घोषणा BT_UART_MSG_FRAME3OBEX_POS		(5)
#घोषणा BT_UART_MSG_FRAME3OBEX_MSK		\
		(0x1 << BT_UART_MSG_FRAME3OBEX_POS)
#घोषणा BT_UART_MSG_FRAME3RESERVED_POS		(6)
#घोषणा BT_UART_MSG_FRAME3RESERVED_MSK		\
		(0x3 << BT_UART_MSG_FRAME3RESERVED_POS)

#घोषणा BT_UART_MSG_FRAME4IDLEDURATION_POS	(0)
#घोषणा BT_UART_MSG_FRAME4IDLEDURATION_MSK	\
		(0x3F << BT_UART_MSG_FRAME4IDLEDURATION_POS)
#घोषणा BT_UART_MSG_FRAME4RESERVED_POS		(6)
#घोषणा BT_UART_MSG_FRAME4RESERVED_MSK		\
		(0x3 << BT_UART_MSG_FRAME4RESERVED_POS)

#घोषणा BT_UART_MSG_FRAME5TXACTIVITY_POS	(0)
#घोषणा BT_UART_MSG_FRAME5TXACTIVITY_MSK	\
		(0x3 << BT_UART_MSG_FRAME5TXACTIVITY_POS)
#घोषणा BT_UART_MSG_FRAME5RXACTIVITY_POS	(2)
#घोषणा BT_UART_MSG_FRAME5RXACTIVITY_MSK	\
		(0x3 << BT_UART_MSG_FRAME5RXACTIVITY_POS)
#घोषणा BT_UART_MSG_FRAME5ESCORETRANSMIT_POS	(4)
#घोषणा BT_UART_MSG_FRAME5ESCORETRANSMIT_MSK	\
		(0x3 << BT_UART_MSG_FRAME5ESCORETRANSMIT_POS)
#घोषणा BT_UART_MSG_FRAME5RESERVED_POS		(6)
#घोषणा BT_UART_MSG_FRAME5RESERVED_MSK		\
		(0x3 << BT_UART_MSG_FRAME5RESERVED_POS)

#घोषणा BT_UART_MSG_FRAME6SNIFFINTERVAL_POS	(0)
#घोषणा BT_UART_MSG_FRAME6SNIFFINTERVAL_MSK	\
		(0x1F << BT_UART_MSG_FRAME6SNIFFINTERVAL_POS)
#घोषणा BT_UART_MSG_FRAME6DISCOVERABLE_POS	(5)
#घोषणा BT_UART_MSG_FRAME6DISCOVERABLE_MSK	\
		(0x1 << BT_UART_MSG_FRAME6DISCOVERABLE_POS)
#घोषणा BT_UART_MSG_FRAME6RESERVED_POS		(6)
#घोषणा BT_UART_MSG_FRAME6RESERVED_MSK		\
		(0x3 << BT_UART_MSG_FRAME6RESERVED_POS)

#घोषणा BT_UART_MSG_FRAME7SNIFFACTIVITY_POS	(0)
#घोषणा BT_UART_MSG_FRAME7SNIFFACTIVITY_MSK	\
		(0x7 << BT_UART_MSG_FRAME7SNIFFACTIVITY_POS)
#घोषणा BT_UART_MSG_FRAME7PAGE_POS		(3)
#घोषणा BT_UART_MSG_FRAME7PAGE_MSK		\
		(0x1 << BT_UART_MSG_FRAME7PAGE_POS)
#घोषणा BT_UART_MSG_FRAME7INQUIRY_POS		(4)
#घोषणा BT_UART_MSG_FRAME7INQUIRY_MSK		\
		(0x1 << BT_UART_MSG_FRAME7INQUIRY_POS)
#घोषणा BT_UART_MSG_FRAME7CONNECTABLE_POS	(5)
#घोषणा BT_UART_MSG_FRAME7CONNECTABLE_MSK	\
		(0x1 << BT_UART_MSG_FRAME7CONNECTABLE_POS)
#घोषणा BT_UART_MSG_FRAME7RESERVED_POS		(6)
#घोषणा BT_UART_MSG_FRAME7RESERVED_MSK		\
		(0x3 << BT_UART_MSG_FRAME7RESERVED_POS)

/* BT Session Activity 2 UART message (BT -> WiFi) */
#घोषणा BT_UART_MSG_2_FRAME1RESERVED1_POS	(5)
#घोषणा BT_UART_MSG_2_FRAME1RESERVED1_MSK	\
		(0x1<<BT_UART_MSG_2_FRAME1RESERVED1_POS)
#घोषणा BT_UART_MSG_2_FRAME1RESERVED2_POS	(6)
#घोषणा BT_UART_MSG_2_FRAME1RESERVED2_MSK	\
		(0x3<<BT_UART_MSG_2_FRAME1RESERVED2_POS)

#घोषणा BT_UART_MSG_2_FRAME2AGGTRAFFICLOAD_POS	(0)
#घोषणा BT_UART_MSG_2_FRAME2AGGTRAFFICLOAD_MSK	\
		(0x3F<<BT_UART_MSG_2_FRAME2AGGTRAFFICLOAD_POS)
#घोषणा BT_UART_MSG_2_FRAME2RESERVED_POS	(6)
#घोषणा BT_UART_MSG_2_FRAME2RESERVED_MSK	\
		(0x3<<BT_UART_MSG_2_FRAME2RESERVED_POS)

#घोषणा BT_UART_MSG_2_FRAME3BRLASTTXPOWER_POS	(0)
#घोषणा BT_UART_MSG_2_FRAME3BRLASTTXPOWER_MSK	\
		(0xF<<BT_UART_MSG_2_FRAME3BRLASTTXPOWER_POS)
#घोषणा BT_UART_MSG_2_FRAME3INQPAGESRMODE_POS	(4)
#घोषणा BT_UART_MSG_2_FRAME3INQPAGESRMODE_MSK	\
		(0x1<<BT_UART_MSG_2_FRAME3INQPAGESRMODE_POS)
#घोषणा BT_UART_MSG_2_FRAME3LEMASTER_POS	(5)
#घोषणा BT_UART_MSG_2_FRAME3LEMASTER_MSK	\
		(0x1<<BT_UART_MSG_2_FRAME3LEMASTER_POS)
#घोषणा BT_UART_MSG_2_FRAME3RESERVED_POS	(6)
#घोषणा BT_UART_MSG_2_FRAME3RESERVED_MSK	\
		(0x3<<BT_UART_MSG_2_FRAME3RESERVED_POS)

#घोषणा BT_UART_MSG_2_FRAME4LELASTTXPOWER_POS	(0)
#घोषणा BT_UART_MSG_2_FRAME4LELASTTXPOWER_MSK	\
		(0xF<<BT_UART_MSG_2_FRAME4LELASTTXPOWER_POS)
#घोषणा BT_UART_MSG_2_FRAME4NUMLECONN_POS	(4)
#घोषणा BT_UART_MSG_2_FRAME4NUMLECONN_MSK	\
		(0x3<<BT_UART_MSG_2_FRAME4NUMLECONN_POS)
#घोषणा BT_UART_MSG_2_FRAME4RESERVED_POS	(6)
#घोषणा BT_UART_MSG_2_FRAME4RESERVED_MSK	\
		(0x3<<BT_UART_MSG_2_FRAME4RESERVED_POS)

#घोषणा BT_UART_MSG_2_FRAME5BTMINRSSI_POS	(0)
#घोषणा BT_UART_MSG_2_FRAME5BTMINRSSI_MSK	\
		(0xF<<BT_UART_MSG_2_FRAME5BTMINRSSI_POS)
#घोषणा BT_UART_MSG_2_FRAME5LESCANINITMODE_POS	(4)
#घोषणा BT_UART_MSG_2_FRAME5LESCANINITMODE_MSK	\
		(0x1<<BT_UART_MSG_2_FRAME5LESCANINITMODE_POS)
#घोषणा BT_UART_MSG_2_FRAME5LEADVERMODE_POS	(5)
#घोषणा BT_UART_MSG_2_FRAME5LEADVERMODE_MSK	\
		(0x1<<BT_UART_MSG_2_FRAME5LEADVERMODE_POS)
#घोषणा BT_UART_MSG_2_FRAME5RESERVED_POS	(6)
#घोषणा BT_UART_MSG_2_FRAME5RESERVED_MSK	\
		(0x3<<BT_UART_MSG_2_FRAME5RESERVED_POS)

#घोषणा BT_UART_MSG_2_FRAME6LECONNINTERVAL_POS	(0)
#घोषणा BT_UART_MSG_2_FRAME6LECONNINTERVAL_MSK	\
		(0x1F<<BT_UART_MSG_2_FRAME6LECONNINTERVAL_POS)
#घोषणा BT_UART_MSG_2_FRAME6RFU_POS		(5)
#घोषणा BT_UART_MSG_2_FRAME6RFU_MSK		\
		(0x1<<BT_UART_MSG_2_FRAME6RFU_POS)
#घोषणा BT_UART_MSG_2_FRAME6RESERVED_POS	(6)
#घोषणा BT_UART_MSG_2_FRAME6RESERVED_MSK	\
		(0x3<<BT_UART_MSG_2_FRAME6RESERVED_POS)

#घोषणा BT_UART_MSG_2_FRAME7LECONNSLAVELAT_POS	(0)
#घोषणा BT_UART_MSG_2_FRAME7LECONNSLAVELAT_MSK	\
		(0x7<<BT_UART_MSG_2_FRAME7LECONNSLAVELAT_POS)
#घोषणा BT_UART_MSG_2_FRAME7LEPROखाता1_POS	(3)
#घोषणा BT_UART_MSG_2_FRAME7LEPROखाता1_MSK	\
		(0x1<<BT_UART_MSG_2_FRAME7LEPROखाता1_POS)
#घोषणा BT_UART_MSG_2_FRAME7LEPROखाता2_POS	(4)
#घोषणा BT_UART_MSG_2_FRAME7LEPROखाता2_MSK	\
		(0x1<<BT_UART_MSG_2_FRAME7LEPROखाता2_POS)
#घोषणा BT_UART_MSG_2_FRAME7LEPROखाताOTHER_POS	(5)
#घोषणा BT_UART_MSG_2_FRAME7LEPROखाताOTHER_MSK	\
		(0x1<<BT_UART_MSG_2_FRAME7LEPROखाताOTHER_POS)
#घोषणा BT_UART_MSG_2_FRAME7RESERVED_POS	(6)
#घोषणा BT_UART_MSG_2_FRAME7RESERVED_MSK	\
		(0x3<<BT_UART_MSG_2_FRAME7RESERVED_POS)


#घोषणा BT_ENABLE_REDUCED_TXPOWER_THRESHOLD	(-62)
#घोषणा BT_DISABLE_REDUCED_TXPOWER_THRESHOLD	(-65)

काष्ठा iwl_bt_uart_msg अणु
	u8 header;
	u8 frame1;
	u8 frame2;
	u8 frame3;
	u8 frame4;
	u8 frame5;
	u8 frame6;
	u8 frame7;
पूर्ण __packed;

काष्ठा iwl_bt_coex_profile_notअगर अणु
	काष्ठा iwl_bt_uart_msg last_bt_uart_msg;
	u8 bt_status; /* 0 - off, 1 - on */
	u8 bt_traffic_load; /* 0 .. 3? */
	u8 bt_ci_compliance; /* 0 - not complied, 1 - complied */
	u8 reserved;
पूर्ण __packed;

#घोषणा IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS	0
#घोषणा IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_MSK	0x1
#घोषणा IWL_BT_COEX_PRIO_TBL_PRIO_POS		1
#घोषणा IWL_BT_COEX_PRIO_TBL_PRIO_MASK		0x0e
#घोषणा IWL_BT_COEX_PRIO_TBL_RESERVED_POS	4
#घोषणा IWL_BT_COEX_PRIO_TBL_RESERVED_MASK	0xf0
#घोषणा IWL_BT_COEX_PRIO_TBL_PRIO_SHIFT		1

/*
 * BT Coexistence Priority table
 * REPLY_BT_COEX_PRIO_TABLE = 0xcc
 */
क्रमागत bt_coex_prio_table_events अणु
	BT_COEX_PRIO_TBL_EVT_INIT_CALIB1 = 0,
	BT_COEX_PRIO_TBL_EVT_INIT_CALIB2 = 1,
	BT_COEX_PRIO_TBL_EVT_PERIODIC_CALIB_LOW1 = 2,
	BT_COEX_PRIO_TBL_EVT_PERIODIC_CALIB_LOW2 = 3, /* DC calib */
	BT_COEX_PRIO_TBL_EVT_PERIODIC_CALIB_HIGH1 = 4,
	BT_COEX_PRIO_TBL_EVT_PERIODIC_CALIB_HIGH2 = 5,
	BT_COEX_PRIO_TBL_EVT_DTIM = 6,
	BT_COEX_PRIO_TBL_EVT_SCAN52 = 7,
	BT_COEX_PRIO_TBL_EVT_SCAN24 = 8,
	BT_COEX_PRIO_TBL_EVT_RESERVED0 = 9,
	BT_COEX_PRIO_TBL_EVT_RESERVED1 = 10,
	BT_COEX_PRIO_TBL_EVT_RESERVED2 = 11,
	BT_COEX_PRIO_TBL_EVT_RESERVED3 = 12,
	BT_COEX_PRIO_TBL_EVT_RESERVED4 = 13,
	BT_COEX_PRIO_TBL_EVT_RESERVED5 = 14,
	BT_COEX_PRIO_TBL_EVT_RESERVED6 = 15,
	/* BT_COEX_PRIO_TBL_EVT_MAX should always be last */
	BT_COEX_PRIO_TBL_EVT_MAX,
पूर्ण;

क्रमागत bt_coex_prio_table_priorities अणु
	BT_COEX_PRIO_TBL_DISABLED = 0,
	BT_COEX_PRIO_TBL_PRIO_LOW = 1,
	BT_COEX_PRIO_TBL_PRIO_HIGH = 2,
	BT_COEX_PRIO_TBL_PRIO_BYPASS = 3,
	BT_COEX_PRIO_TBL_PRIO_COEX_OFF = 4,
	BT_COEX_PRIO_TBL_PRIO_COEX_ON = 5,
	BT_COEX_PRIO_TBL_PRIO_RSRVD1 = 6,
	BT_COEX_PRIO_TBL_PRIO_RSRVD2 = 7,
	BT_COEX_PRIO_TBL_MAX,
पूर्ण;

काष्ठा iwl_bt_coex_prio_table_cmd अणु
	u8 prio_tbl[BT_COEX_PRIO_TBL_EVT_MAX];
पूर्ण __packed;

#घोषणा IWL_BT_COEX_ENV_CLOSE	0
#घोषणा IWL_BT_COEX_ENV_OPEN	1
/*
 * BT Protection Envelope
 * REPLY_BT_COEX_PROT_ENV = 0xcd
 */
काष्ठा iwl_bt_coex_prot_env_cmd अणु
	u8 action; /* 0 = बंदd, 1 = खोलो */
	u8 type; /* 0 .. 15 */
	u8 reserved[2];
पूर्ण __packed;

/*
 * REPLY_D3_CONFIG
 */
क्रमागत iwlagn_d3_wakeup_filters अणु
	IWLAGN_D3_WAKEUP_RFKILL		= BIT(0),
	IWLAGN_D3_WAKEUP_SYSASSERT	= BIT(1),
पूर्ण;

काष्ठा iwlagn_d3_config_cmd अणु
	__le32 min_sleep_समय;
	__le32 wakeup_flags;
पूर्ण __packed;

/*
 * REPLY_WOWLAN_PATTERNS
 */
#घोषणा IWLAGN_WOWLAN_MIN_PATTERN_LEN	16
#घोषणा IWLAGN_WOWLAN_MAX_PATTERN_LEN	128

काष्ठा iwlagn_wowlan_pattern अणु
	u8 mask[IWLAGN_WOWLAN_MAX_PATTERN_LEN / 8];
	u8 pattern[IWLAGN_WOWLAN_MAX_PATTERN_LEN];
	u8 mask_size;
	u8 pattern_size;
	__le16 reserved;
पूर्ण __packed;

#घोषणा IWLAGN_WOWLAN_MAX_PATTERNS	20

काष्ठा iwlagn_wowlan_patterns_cmd अणु
	__le32 n_patterns;
	काष्ठा iwlagn_wowlan_pattern patterns[];
पूर्ण __packed;

/*
 * REPLY_WOWLAN_WAKEUP_FILTER
 */
क्रमागत iwlagn_wowlan_wakeup_filters अणु
	IWLAGN_WOWLAN_WAKEUP_MAGIC_PACKET	= BIT(0),
	IWLAGN_WOWLAN_WAKEUP_PATTERN_MATCH	= BIT(1),
	IWLAGN_WOWLAN_WAKEUP_BEACON_MISS	= BIT(2),
	IWLAGN_WOWLAN_WAKEUP_LINK_CHANGE	= BIT(3),
	IWLAGN_WOWLAN_WAKEUP_GTK_REKEY_FAIL	= BIT(4),
	IWLAGN_WOWLAN_WAKEUP_EAP_IDENT_REQ	= BIT(5),
	IWLAGN_WOWLAN_WAKEUP_4WAY_HANDSHAKE	= BIT(6),
	IWLAGN_WOWLAN_WAKEUP_ALWAYS		= BIT(7),
	IWLAGN_WOWLAN_WAKEUP_ENABLE_NET_DETECT	= BIT(8),
पूर्ण;

काष्ठा iwlagn_wowlan_wakeup_filter_cmd अणु
	__le32 enabled;
	__le16 non_qos_seq;
	__le16 reserved;
	__le16 qos_seq[8];
पूर्ण;

/*
 * REPLY_WOWLAN_TSC_RSC_PARAMS
 */
#घोषणा IWLAGN_NUM_RSC	16

काष्ठा tkip_sc अणु
	__le16 iv16;
	__le16 pad;
	__le32 iv32;
पूर्ण __packed;

काष्ठा iwlagn_tkip_rsc_tsc अणु
	काष्ठा tkip_sc unicast_rsc[IWLAGN_NUM_RSC];
	काष्ठा tkip_sc multicast_rsc[IWLAGN_NUM_RSC];
	काष्ठा tkip_sc tsc;
पूर्ण __packed;

काष्ठा aes_sc अणु
	__le64 pn;
पूर्ण __packed;

काष्ठा iwlagn_aes_rsc_tsc अणु
	काष्ठा aes_sc unicast_rsc[IWLAGN_NUM_RSC];
	काष्ठा aes_sc multicast_rsc[IWLAGN_NUM_RSC];
	काष्ठा aes_sc tsc;
पूर्ण __packed;

जोड़ iwlagn_all_tsc_rsc अणु
	काष्ठा iwlagn_tkip_rsc_tsc tkip;
	काष्ठा iwlagn_aes_rsc_tsc aes;
पूर्ण;

काष्ठा iwlagn_wowlan_rsc_tsc_params_cmd अणु
	जोड़ iwlagn_all_tsc_rsc all_tsc_rsc;
पूर्ण __packed;

/*
 * REPLY_WOWLAN_TKIP_PARAMS
 */
#घोषणा IWLAGN_MIC_KEY_SIZE	8
#घोषणा IWLAGN_P1K_SIZE		5
काष्ठा iwlagn_mic_keys अणु
	u8 tx[IWLAGN_MIC_KEY_SIZE];
	u8 rx_unicast[IWLAGN_MIC_KEY_SIZE];
	u8 rx_mcast[IWLAGN_MIC_KEY_SIZE];
पूर्ण __packed;

काष्ठा iwlagn_p1k_cache अणु
	__le16 p1k[IWLAGN_P1K_SIZE];
पूर्ण __packed;

#घोषणा IWLAGN_NUM_RX_P1K_CACHE	2

काष्ठा iwlagn_wowlan_tkip_params_cmd अणु
	काष्ठा iwlagn_mic_keys mic_keys;
	काष्ठा iwlagn_p1k_cache tx;
	काष्ठा iwlagn_p1k_cache rx_uni[IWLAGN_NUM_RX_P1K_CACHE];
	काष्ठा iwlagn_p1k_cache rx_multi[IWLAGN_NUM_RX_P1K_CACHE];
पूर्ण __packed;

/*
 * REPLY_WOWLAN_KEK_KCK_MATERIAL
 */

#घोषणा IWLAGN_KCK_MAX_SIZE	32
#घोषणा IWLAGN_KEK_MAX_SIZE	32

काष्ठा iwlagn_wowlan_kek_kck_material_cmd अणु
	u8	kck[IWLAGN_KCK_MAX_SIZE];
	u8	kek[IWLAGN_KEK_MAX_SIZE];
	__le16	kck_len;
	__le16	kek_len;
	__le64	replay_ctr;
पूर्ण __packed;

#घोषणा RF_KILL_INDICATOR_FOR_WOWLAN	0x87

/*
 * REPLY_WOWLAN_GET_STATUS = 0xe5
 */
काष्ठा iwlagn_wowlan_status अणु
	__le64 replay_ctr;
	__le32 rekey_status;
	__le32 wakeup_reason;
	u8 pattern_number;
	u8 reserved1;
	__le16 qos_seq_ctr[8];
	__le16 non_qos_seq_ctr;
	__le16 reserved2;
	जोड़ iwlagn_all_tsc_rsc tsc_rsc;
	__le16 reserved3;
पूर्ण __packed;

/*
 * REPLY_WIPAN_PARAMS = 0xb2 (Commands and Notअगरication)
 */

/*
 * Minimum slot समय in TU
 */
#घोषणा IWL_MIN_SLOT_TIME	20

/**
 * काष्ठा iwl_wipan_slot
 * @width: Time in TU
 * @type:
 *   0 - BSS
 *   1 - PAN
 */
काष्ठा iwl_wipan_slot अणु
	__le16 width;
	u8 type;
	u8 reserved;
पूर्ण __packed;

#घोषणा IWL_WIPAN_PARAMS_FLG_LEAVE_CHANNEL_CTS		BIT(1)	/* reserved */
#घोषणा IWL_WIPAN_PARAMS_FLG_LEAVE_CHANNEL_QUIET	BIT(2)	/* reserved */
#घोषणा IWL_WIPAN_PARAMS_FLG_SLOTTED_MODE		BIT(3)	/* reserved */
#घोषणा IWL_WIPAN_PARAMS_FLG_FILTER_BEACON_NOTIF	BIT(4)
#घोषणा IWL_WIPAN_PARAMS_FLG_FULL_SLOTTED_MODE		BIT(5)

/**
 * काष्ठा iwl_wipan_params_cmd
 * @flags:
 *   bit0: reserved
 *   bit1: CP leave channel with CTS
 *   bit2: CP leave channel qith Quiet
 *   bit3: slotted mode
 *     1 - work in slotted mode
 *     0 - work in non slotted mode
 *   bit4: filter beacon notअगरication
 *   bit5: full tx slotted mode. अगर this flag is set,
 *         uCode will perक्रमm leaving channel methods in context चयन
 *         also when working in same channel mode
 * @num_slots: 1 - 10
 */
काष्ठा iwl_wipan_params_cmd अणु
	__le16 flags;
	u8 reserved;
	u8 num_slots;
	काष्ठा iwl_wipan_slot slots[10];
पूर्ण __packed;

/*
 * REPLY_WIPAN_P2P_CHANNEL_SWITCH = 0xb9
 *
 * TODO: Figure out what this is used क्रम,
 *	 it can only चयन between 2.4 GHz
 *	 channels!!
 */

काष्ठा iwl_wipan_p2p_channel_चयन_cmd अणु
	__le16 channel;
	__le16 reserved;
पूर्ण;

/*
 * REPLY_WIPAN_NOA_NOTIFICATION = 0xbc
 *
 * This is used by the device to notअगरy us of the
 * NoA schedule it determined so we can क्रमward it
 * to userspace क्रम inclusion in probe responses.
 *
 * In beacons, the NoA schedule is simply appended
 * to the frame we give the device.
 */

काष्ठा iwl_wipan_noa_descriptor अणु
	u8 count;
	__le32 duration;
	__le32 पूर्णांकerval;
	__le32 startसमय;
पूर्ण __packed;

काष्ठा iwl_wipan_noa_attribute अणु
	u8 id;
	__le16 length;
	u8 index;
	u8 ct_winकरोw;
	काष्ठा iwl_wipan_noa_descriptor descr0, descr1;
	u8 reserved;
पूर्ण __packed;

काष्ठा iwl_wipan_noa_notअगरication अणु
	u32 noa_active;
	काष्ठा iwl_wipan_noa_attribute noa_attribute;
पूर्ण __packed;

#पूर्ण_अगर				/* __iwl_commands_h__ */
