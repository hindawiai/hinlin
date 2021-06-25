<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1251
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008 Nokia Corporation
 */

#अगर_अघोषित __WL1251_CMD_H__
#घोषणा __WL1251_CMD_H__

#समावेश "wl1251.h"

#समावेश <net/cfg80211.h>

काष्ठा acx_header;

पूर्णांक wl1251_cmd_send(काष्ठा wl1251 *wl, u16 type, व्योम *buf, माप_प्रकार buf_len);
पूर्णांक wl1251_cmd_test(काष्ठा wl1251 *wl, व्योम *buf, माप_प्रकार buf_len, u8 answer);
पूर्णांक wl1251_cmd_पूर्णांकerrogate(काष्ठा wl1251 *wl, u16 id, व्योम *buf, माप_प्रकार len);
पूर्णांक wl1251_cmd_configure(काष्ठा wl1251 *wl, u16 id, व्योम *buf, माप_प्रकार len);
पूर्णांक wl1251_cmd_vbm(काष्ठा wl1251 *wl, u8 identity,
		   व्योम *biपंचांगap, u16 biपंचांगap_len, u8 biपंचांगap_control);
पूर्णांक wl1251_cmd_data_path_rx(काष्ठा wl1251 *wl, u8 channel, bool enable);
पूर्णांक wl1251_cmd_data_path_tx(काष्ठा wl1251 *wl, u8 channel, bool enable);
पूर्णांक wl1251_cmd_join(काष्ठा wl1251 *wl, u8 bss_type, u8 channel,
		    u16 beacon_पूर्णांकerval, u8 dtim_पूर्णांकerval);
पूर्णांक wl1251_cmd_ps_mode(काष्ठा wl1251 *wl, u8 ps_mode);
पूर्णांक wl1251_cmd_पढ़ो_memory(काष्ठा wl1251 *wl, u32 addr, व्योम *answer,
			   माप_प्रकार len);
पूर्णांक wl1251_cmd_ढाँचा_set(काष्ठा wl1251 *wl, u16 cmd_id,
			    व्योम *buf, माप_प्रकार buf_len);
पूर्णांक wl1251_cmd_scan(काष्ठा wl1251 *wl, u8 *ssid, माप_प्रकार ssid_len,
		    काष्ठा ieee80211_channel *channels[],
		    अचिन्हित पूर्णांक n_channels, अचिन्हित पूर्णांक n_probes);
पूर्णांक wl1251_cmd_trigger_scan_to(काष्ठा wl1251 *wl, u32 समयout);

/* unit ms */
#घोषणा WL1251_COMMAND_TIMEOUT 2000

क्रमागत wl1251_commands अणु
	CMD_RESET           = 0,
	CMD_INTERROGATE     = 1,    /*use this to पढ़ो inक्रमmation elements*/
	CMD_CONFIGURE       = 2,    /*use this to ग_लिखो inक्रमmation elements*/
	CMD_ENABLE_RX       = 3,
	CMD_ENABLE_TX       = 4,
	CMD_DISABLE_RX      = 5,
	CMD_DISABLE_TX      = 6,
	CMD_SCAN            = 8,
	CMD_STOP_SCAN       = 9,
	CMD_VBM             = 10,
	CMD_START_JOIN      = 11,
	CMD_SET_KEYS        = 12,
	CMD_READ_MEMORY     = 13,
	CMD_WRITE_MEMORY    = 14,
	CMD_BEACON          = 19,
	CMD_PROBE_RESP      = 20,
	CMD_शून्य_DATA       = 21,
	CMD_PROBE_REQ       = 22,
	CMD_TEST            = 23,
	CMD_RADIO_CALIBRATE     = 25,   /* OBSOLETE */
	CMD_ENABLE_RX_PATH      = 27,   /* OBSOLETE */
	CMD_NOISE_HIST      = 28,
	CMD_RX_RESET        = 29,
	CMD_PS_POLL         = 30,
	CMD_QOS_शून्य_DATA   = 31,
	CMD_LNA_CONTROL     = 32,
	CMD_SET_BCN_MODE    = 33,
	CMD_MEASUREMENT      = 34,
	CMD_STOP_MEASUREMENT = 35,
	CMD_DISCONNECT       = 36,
	CMD_SET_PS_MODE      = 37,
	CMD_CHANNEL_SWITCH   = 38,
	CMD_STOP_CHANNEL_SWICTH = 39,
	CMD_AP_DISCOVERY     = 40,
	CMD_STOP_AP_DISCOVERY = 41,
	CMD_SPS_SCAN = 42,
	CMD_STOP_SPS_SCAN = 43,
	CMD_HEALTH_CHECK     = 45,
	CMD_DEBUG            = 46,
	CMD_TRIGGER_SCAN_TO  = 47,

	NUM_COMMANDS,
	MAX_COMMAND_ID = 0xFFFF,
पूर्ण;

#घोषणा MAX_CMD_PARAMS 572

काष्ठा wl1251_cmd_header अणु
	u16 id;
	u16 status;
	/* payload */
	u8 data[];
पूर्ण __packed;

काष्ठा  wl1251_command अणु
	काष्ठा wl1251_cmd_header header;
	u8  parameters[MAX_CMD_PARAMS];
पूर्ण __packed;

क्रमागत अणु
	CMD_MAILBOX_IDLE              		=  0,
	CMD_STATUS_SUCCESS            		=  1,
	CMD_STATUS_UNKNOWN_CMD        		=  2,
	CMD_STATUS_UNKNOWN_IE         		=  3,
	CMD_STATUS_REJECT_MEAS_SG_ACTIVE 	= 11,
	CMD_STATUS_RX_BUSY            		= 13,
	CMD_STATUS_INVALID_PARAM      		= 14,
	CMD_STATUS_TEMPLATE_TOO_LARGE 		= 15,
	CMD_STATUS_OUT_OF_MEMORY      		= 16,
	CMD_STATUS_STA_TABLE_FULL     		= 17,
	CMD_STATUS_RADIO_ERROR        		= 18,
	CMD_STATUS_WRONG_NESTING      		= 19,
	CMD_STATUS_TIMEOUT            		= 21, /* Driver पूर्णांकernal use.*/
	CMD_STATUS_FW_RESET           		= 22, /* Driver पूर्णांकernal use.*/
	MAX_COMMAND_STATUS            		= 0xff
पूर्ण;


/*
 * CMD_READ_MEMORY
 *
 * The host issues this command to पढ़ो the WiLink device memory/रेजिस्टरs.
 *
 * Note: The Base Band address has special handling (16 bits रेजिस्टरs and
 * addresses). For more inक्रमmation, see the hardware specअगरication.
 */
/*
 * CMD_WRITE_MEMORY
 *
 * The host issues this command to ग_लिखो the WiLink device memory/रेजिस्टरs.
 *
 * The Base Band address has special handling (16 bits रेजिस्टरs and
 * addresses). For more inक्रमmation, see the hardware specअगरication.
 */
#घोषणा MAX_READ_SIZE 256

काष्ठा cmd_पढ़ो_ग_लिखो_memory अणु
	काष्ठा wl1251_cmd_header header;

	/* The address of the memory to पढ़ो from or ग_लिखो to.*/
	u32 addr;

	/* The amount of data in bytes to पढ़ो from or ग_लिखो to the WiLink
	 * device.*/
	u32 size;

	/* The actual value पढ़ो from or written to the Wilink. The source
	   of this field is the Host in WRITE command or the Wilink in READ
	   command. */
	u8 value[MAX_READ_SIZE];
पूर्ण __packed;

#घोषणा CMDMBOX_HEADER_LEN 4
#घोषणा CMDMBOX_INFO_ELEM_HEADER_LEN 4

#घोषणा WL1251_SCAN_OPT_PASSIVE		1
#घोषणा WL1251_SCAN_OPT_5GHZ_BAND	2
#घोषणा WL1251_SCAN_OPT_TRIGGERD_SCAN	4
#घोषणा WL1251_SCAN_OPT_PRIORITY_HIGH	8

#घोषणा WL1251_SCAN_MIN_DURATION 30000
#घोषणा WL1251_SCAN_MAX_DURATION 60000

#घोषणा WL1251_SCAN_NUM_PROBES 3

काष्ठा wl1251_scan_parameters अणु
	__le32 rx_config_options;
	__le32 rx_filter_options;

	/*
	 * Scan options:
	 * bit 0: When this bit is set, passive scan.
	 * bit 1: Band, when this bit is set we scan
	 * in the 5Ghz band.
	 * bit 2: voice mode, 0 क्रम normal scan.
	 * bit 3: scan priority, 1 क्रम high priority.
	 */
	__le16 scan_options;

	/* Number of channels to scan */
	u8 num_channels;

	/* Number opf probe requests to send, per channel */
	u8 num_probe_requests;

	/* Rate and modulation क्रम probe requests */
	__le16 tx_rate;

	u8 tid_trigger;
	u8 ssid_len;
	u8 ssid[32];

पूर्ण __packed;

काष्ठा wl1251_scan_ch_parameters अणु
	__le32 min_duration; /* in TU */
	__le32 max_duration; /* in TU */
	u32 bssid_lsb;
	u16 bssid_msb;

	/*
	 * bits 0-3: Early termination count.
	 * bits 4-5: Early termination condition.
	 */
	u8 early_termination;

	u8 tx_घातer_att;
	u8 channel;
	u8 pad[3];
पूर्ण __packed;

/* SCAN parameters */
#घोषणा SCAN_MAX_NUM_OF_CHANNELS 16

काष्ठा wl1251_cmd_scan अणु
	काष्ठा wl1251_cmd_header header;

	काष्ठा wl1251_scan_parameters params;
	काष्ठा wl1251_scan_ch_parameters channels[SCAN_MAX_NUM_OF_CHANNELS];
पूर्ण __packed;

क्रमागत अणु
	BSS_TYPE_IBSS = 0,
	BSS_TYPE_STA_BSS = 2,
	BSS_TYPE_AP_BSS = 3,
	MAX_BSS_TYPE = 0xFF
पूर्ण;

#घोषणा JOIN_CMD_CTRL_TX_FLUSH             0x80 /* Firmware flushes all Tx */
#घोषणा JOIN_CMD_CTRL_EARLY_WAKEUP_ENABLE  0x01 /* Early wakeup समय */


काष्ठा cmd_join अणु
	काष्ठा wl1251_cmd_header header;

	u32 bssid_lsb;
	u16 bssid_msb;
	u16 beacon_पूर्णांकerval; /* in TBTTs */
	u32 rx_config_options;
	u32 rx_filter_options;

	/*
	 * The target uses this field to determine the rate at
	 * which to transmit control frame responses (such as
	 * ACK or CTS frames).
	 */
	u16 basic_rate_set;
	u8 dtim_पूर्णांकerval;
	u8 tx_ctrl_frame_rate; /* OBSOLETE */
	u8 tx_ctrl_frame_mod;  /* OBSOLETE */
	/*
	 * bits 0-2: This bitwise field specअगरies the type
	 * of BSS to start or join (BSS_TYPE_*).
	 * bit 4: Band - The radio band in which to join
	 * or start.
	 *  0 - 2.4GHz band
	 *  1 - 5GHz band
	 * bits 3, 5-7: Reserved
	 */
	u8 bss_type;
	u8 channel;
	u8 ssid_len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 ctrl; /* JOIN_CMD_CTRL_* */
	u8 tx_mgt_frame_rate; /* OBSOLETE */
	u8 tx_mgt_frame_mod;  /* OBSOLETE */
	u8 reserved;
पूर्ण __packed;

काष्ठा cmd_enabledisable_path अणु
	काष्ठा wl1251_cmd_header header;

	u8 channel;
	u8 padding[3];
पूर्ण __packed;

#घोषणा WL1251_MAX_TEMPLATE_SIZE 300

काष्ठा wl1251_cmd_packet_ढाँचा अणु
	काष्ठा wl1251_cmd_header header;

	__le16 size;
	u8 data[];
पूर्ण __packed;

#घोषणा TIM_ELE_ID    5
#घोषणा PARTIAL_VBM_MAX    251

काष्ठा wl1251_tim अणु
	u8 identity;
	u8 length;
	u8 dtim_count;
	u8 dtim_period;
	u8 biपंचांगap_ctrl;
	u8 pvb_field[PARTIAL_VBM_MAX]; /* Partial Virtual Biपंचांगap */
पूर्ण __packed;

/* Virtual Bit Map update */
काष्ठा wl1251_cmd_vbm_update अणु
	काष्ठा wl1251_cmd_header header;
	__le16 len;
	u8  padding[2];
	काष्ठा wl1251_tim tim;
पूर्ण __packed;

क्रमागत wl1251_cmd_ps_mode अणु
	CHIP_ACTIVE_MODE,
	CHIP_POWER_SAVE_MODE
पूर्ण;

काष्ठा wl1251_cmd_ps_params अणु
	काष्ठा wl1251_cmd_header header;

	u8 ps_mode; /* STATION_* */
	u8 send_null_data; /* Do we have to send शून्य data packet ? */
	u8 retries; /* Number of retires क्रम the initial शून्य data packet */

	 /*
	  * TUs during which the target stays awake after चयनing
	  * to घातer save mode.
	  */
	u8 hang_over_period;
	u16 null_data_rate;
	u8 pad[2];
पूर्ण __packed;

काष्ठा wl1251_cmd_trigger_scan_to अणु
	काष्ठा wl1251_cmd_header header;

	u32 समयout;
पूर्ण __packed;

/* HW encryption keys */
#घोषणा NUM_ACCESS_CATEGORIES_COPY 4
#घोषणा MAX_KEY_SIZE 32

/* When set, disable HW encryption */
#घोषणा DF_ENCRYPTION_DISABLE      0x01
/* When set, disable HW decryption */
#घोषणा DF_SNIFF_MODE_ENABLE       0x80

क्रमागत wl1251_cmd_key_action अणु
	KEY_ADD_OR_REPLACE = 1,
	KEY_REMOVE         = 2,
	KEY_SET_ID         = 3,
	MAX_KEY_ACTION     = 0xffff,
पूर्ण;

क्रमागत wl1251_cmd_key_type अणु
	KEY_WEP_DEFAULT       = 0,
	KEY_WEP_ADDR          = 1,
	KEY_AES_GROUP         = 4,
	KEY_AES_PAIRWISE      = 5,
	KEY_WEP_GROUP         = 6,
	KEY_TKIP_MIC_GROUP    = 10,
	KEY_TKIP_MIC_PAIRWISE = 11,
पूर्ण;

/*
 *
 * key_type_e   key size    key क्रमmat
 * ----------   ---------   ----------
 * 0x00         5, 13, 29   Key data
 * 0x01         5, 13, 29   Key data
 * 0x04         16          16 bytes of key data
 * 0x05         16          16 bytes of key data
 * 0x0a         32          16 bytes of TKIP key data
 *                          8 bytes of RX MIC key data
 *                          8 bytes of TX MIC key data
 * 0x0b         32          16 bytes of TKIP key data
 *                          8 bytes of RX MIC key data
 *                          8 bytes of TX MIC key data
 *
 */

काष्ठा wl1251_cmd_set_keys अणु
	काष्ठा wl1251_cmd_header header;

	/* Ignored क्रम शेष WEP key */
	u8 addr[ETH_ALEN];

	/* key_action_e */
	u16 key_action;

	u16 reserved_1;

	/* key size in bytes */
	u8 key_size;

	/* key_type_e */
	u8 key_type;
	u8 ssid_profile;

	/*
	 * TKIP, AES: frame's key id field.
	 * For WEP शेष key: key id;
	 */
	u8 id;
	u8 reserved_2[6];
	u8 key[MAX_KEY_SIZE];
	u16 ac_seq_num16[NUM_ACCESS_CATEGORIES_COPY];
	u32 ac_seq_num32[NUM_ACCESS_CATEGORIES_COPY];
पूर्ण __packed;


#पूर्ण_अगर /* __WL1251_CMD_H__ */
