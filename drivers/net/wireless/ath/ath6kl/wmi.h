<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file contains the definitions of the WMI protocol specअगरied in the
 * Wireless Module Interface (WMI).  It includes definitions of all the
 * commands and events. Commands are messages from the host to the WM.
 * Events and Replies are messages from the WM to the host.
 */

#अगर_अघोषित WMI_H
#घोषणा WMI_H

#समावेश <linux/ieee80211.h>

#समावेश "htc.h"

#घोषणा HTC_PROTOCOL_VERSION		0x0002
#घोषणा WMI_PROTOCOL_VERSION		0x0002
#घोषणा WMI_CONTROL_MSG_MAX_LEN		256
#घोषणा is_ethertype(type_or_len)	((type_or_len) >= 0x0600)

#घोषणा IP_ETHERTYPE		0x0800

#घोषणा WMI_IMPLICIT_PSTREAM	0xFF
#घोषणा WMI_MAX_THINSTREAM	15

#घोषणा SSID_IE_LEN_INDEX	13

/* Host side link management data काष्ठाures */
#घोषणा SIG_QUALITY_THRESH_LVLS		6
#घोषणा SIG_QUALITY_UPPER_THRESH_LVLS	SIG_QUALITY_THRESH_LVLS
#घोषणा SIG_QUALITY_LOWER_THRESH_LVLS	SIG_QUALITY_THRESH_LVLS

#घोषणा A_BAND_24GHZ           0
#घोषणा A_BAND_5GHZ            1
#घोषणा ATH6KL_NUM_BANDS       2

/* in ms */
#घोषणा WMI_IMPLICIT_PSTREAM_INACTIVITY_INT 5000

/*
 * There are no चिन्हित versions of __le16 and __le32, so क्रम a temporary
 * solution come up with our own version. The idea is from fs/ntfs/types.h.
 *
 * Use a_ prefix so that it करोesn't conflict अगर we get proper support to
 * linux/types.h.
 */
प्रकार __s16 __bitwise a_sle16;
प्रकार __s32 __bitwise a_sle32;

अटल अंतरभूत a_sle32 a_cpu_to_sle32(s32 val)
अणु
	वापस (__क्रमce a_sle32) cpu_to_le32(val);
पूर्ण

अटल अंतरभूत s32 a_sle32_to_cpu(a_sle32 val)
अणु
	वापस le32_to_cpu((__क्रमce __le32) val);
पूर्ण

अटल अंतरभूत a_sle16 a_cpu_to_sle16(s16 val)
अणु
	वापस (__क्रमce a_sle16) cpu_to_le16(val);
पूर्ण

अटल अंतरभूत s16 a_sle16_to_cpu(a_sle16 val)
अणु
	वापस le16_to_cpu((__क्रमce __le16) val);
पूर्ण

काष्ठा sq_threshold_params अणु
	s16 upper_threshold[SIG_QUALITY_UPPER_THRESH_LVLS];
	s16 lower_threshold[SIG_QUALITY_LOWER_THRESH_LVLS];
	u32 upper_threshold_valid_count;
	u32 lower_threshold_valid_count;
	u32 polling_पूर्णांकerval;
	u8 weight;
	u8 last_rssi;
	u8 last_rssi_poll_event;
पूर्ण;

काष्ठा wmi_data_sync_bufs अणु
	u8 traffic_class;
	काष्ठा sk_buff *skb;
पूर्ण;

/* WMM stream classes */
#घोषणा WMM_NUM_AC  4
#घोषणा WMM_AC_BE   0		/* best efक्रमt */
#घोषणा WMM_AC_BK   1		/* background */
#घोषणा WMM_AC_VI   2		/* video */
#घोषणा WMM_AC_VO   3		/* voice */

#घोषणा WMI_VOICE_USER_PRIORITY		0x7

काष्ठा wmi अणु
	u16 stream_exist_क्रम_ac[WMM_NUM_AC];
	u8 fat_pipe_exist;
	काष्ठा ath6kl *parent_dev;
	u8 pwr_mode;

	/* protects fat_pipe_exist and stream_exist_क्रम_ac */
	spinlock_t lock;
	क्रमागत htc_endpoपूर्णांक_id ep_id;
	काष्ठा sq_threshold_params
	    sq_threshld[SIGNAL_QUALITY_METRICS_NUM_MAX];
	bool is_wmm_enabled;
	u8 traffic_class;
	bool is_probe_ssid;

	u8 *last_mgmt_tx_frame;
	माप_प्रकार last_mgmt_tx_frame_len;
	u8 saved_pwr_mode;
पूर्ण;

काष्ठा host_app_area अणु
	__le32 wmi_protocol_ver;
पूर्ण __packed;

क्रमागत wmi_msg_type अणु
	DATA_MSGTYPE = 0x0,
	CNTL_MSGTYPE,
	SYNC_MSGTYPE,
	OPT_MSGTYPE,
पूर्ण;

/*
 * Macros क्रम operating on WMI_DATA_HDR (info) field
 */

#घोषणा WMI_DATA_HDR_MSG_TYPE_MASK  0x03
#घोषणा WMI_DATA_HDR_MSG_TYPE_SHIFT 0
#घोषणा WMI_DATA_HDR_UP_MASK        0x07
#घोषणा WMI_DATA_HDR_UP_SHIFT       2

/* In AP mode, the same bit (b5) is used to indicate Power save state in
 * the Rx dir and More data bit state in the tx direction.
 */
#घोषणा WMI_DATA_HDR_PS_MASK        0x1
#घोषणा WMI_DATA_HDR_PS_SHIFT       5

#घोषणा WMI_DATA_HDR_MORE	0x20

क्रमागत wmi_data_hdr_data_type अणु
	WMI_DATA_HDR_DATA_TYPE_802_3 = 0,
	WMI_DATA_HDR_DATA_TYPE_802_11,

	/* used to be used क्रम the PAL */
	WMI_DATA_HDR_DATA_TYPE_ACL,
पूर्ण;

/* Biपंचांगap of data header flags */
क्रमागत wmi_data_hdr_flags अणु
	WMI_DATA_HDR_FLAGS_MORE = 0x1,
	WMI_DATA_HDR_FLAGS_EOSP = 0x2,
	WMI_DATA_HDR_FLAGS_UAPSD = 0x4,
पूर्ण;

#घोषणा WMI_DATA_HDR_DATA_TYPE_MASK     0x3
#घोषणा WMI_DATA_HDR_DATA_TYPE_SHIFT    6

/* Macros क्रम operating on WMI_DATA_HDR (info2) field */
#घोषणा WMI_DATA_HDR_SEQNO_MASK     0xFFF
#घोषणा WMI_DATA_HDR_SEQNO_SHIFT    0

#घोषणा WMI_DATA_HDR_AMSDU_MASK     0x1
#घोषणा WMI_DATA_HDR_AMSDU_SHIFT    12

#घोषणा WMI_DATA_HDR_META_MASK      0x7
#घोषणा WMI_DATA_HDR_META_SHIFT     13

#घोषणा WMI_DATA_HDR_PAD_BEFORE_DATA_MASK               0xFF
#घोषणा WMI_DATA_HDR_PAD_BEFORE_DATA_SHIFT              0x8

/* Macros क्रम operating on WMI_DATA_HDR (info3) field */
#घोषणा WMI_DATA_HDR_IF_IDX_MASK    0xF

#घोषणा WMI_DATA_HDR_TRIG	    0x10
#घोषणा WMI_DATA_HDR_EOSP	    0x10

काष्ठा wmi_data_hdr अणु
	s8 rssi;

	/*
	 * usage of 'info' field(8-bit):
	 *
	 *  b1:b0       - WMI_MSG_TYPE
	 *  b4:b3:b2    - UP(tid)
	 *  b5          - Used in AP mode.
	 *  More-data in tx dir, PS in rx.
	 *  b7:b6       - Dot3 header(0),
	 *                Dot11 Header(1),
	 *                ACL data(2)
	 */
	u8 info;

	/*
	 * usage of 'info2' field(16-bit):
	 *
	 * b11:b0       - seq_no
	 * b12          - A-MSDU?
	 * b15:b13      - META_DATA_VERSION 0 - 7
	 */
	__le16 info2;

	/*
	 * usage of info3, 16-bit:
	 * b3:b0	- Interface index
	 * b4		- uAPSD trigger in rx & EOSP in tx
	 * b15:b5	- Reserved
	 */
	__le16 info3;
पूर्ण __packed;

अटल अंतरभूत u8 wmi_data_hdr_get_up(काष्ठा wmi_data_hdr *dhdr)
अणु
	वापस (dhdr->info >> WMI_DATA_HDR_UP_SHIFT) & WMI_DATA_HDR_UP_MASK;
पूर्ण

अटल अंतरभूत व्योम wmi_data_hdr_set_up(काष्ठा wmi_data_hdr *dhdr,
				       u8 usr_pri)
अणु
	dhdr->info &= ~(WMI_DATA_HDR_UP_MASK << WMI_DATA_HDR_UP_SHIFT);
	dhdr->info |= usr_pri << WMI_DATA_HDR_UP_SHIFT;
पूर्ण

अटल अंतरभूत u8 wmi_data_hdr_get_करोt11(काष्ठा wmi_data_hdr *dhdr)
अणु
	u8 data_type;

	data_type = (dhdr->info >> WMI_DATA_HDR_DATA_TYPE_SHIFT) &
				   WMI_DATA_HDR_DATA_TYPE_MASK;
	वापस (data_type == WMI_DATA_HDR_DATA_TYPE_802_11);
पूर्ण

अटल अंतरभूत u16 wmi_data_hdr_get_seqno(काष्ठा wmi_data_hdr *dhdr)
अणु
	वापस (le16_to_cpu(dhdr->info2) >> WMI_DATA_HDR_SEQNO_SHIFT) &
				WMI_DATA_HDR_SEQNO_MASK;
पूर्ण

अटल अंतरभूत u8 wmi_data_hdr_is_amsdu(काष्ठा wmi_data_hdr *dhdr)
अणु
	वापस (le16_to_cpu(dhdr->info2) >> WMI_DATA_HDR_AMSDU_SHIFT) &
			       WMI_DATA_HDR_AMSDU_MASK;
पूर्ण

अटल अंतरभूत u8 wmi_data_hdr_get_meta(काष्ठा wmi_data_hdr *dhdr)
अणु
	वापस (le16_to_cpu(dhdr->info2) >> WMI_DATA_HDR_META_SHIFT) &
			       WMI_DATA_HDR_META_MASK;
पूर्ण

अटल अंतरभूत u8 wmi_data_hdr_get_अगर_idx(काष्ठा wmi_data_hdr *dhdr)
अणु
	वापस le16_to_cpu(dhdr->info3) & WMI_DATA_HDR_IF_IDX_MASK;
पूर्ण

/* Tx meta version definitions */
#घोषणा WMI_MAX_TX_META_SZ	12
#घोषणा WMI_META_VERSION_1	0x01
#घोषणा WMI_META_VERSION_2	0x02

/* Flag to संकेत to FW to calculate TCP checksum */
#घोषणा WMI_META_V2_FLAG_CSUM_OFFLOAD 0x01

काष्ठा wmi_tx_meta_v1 अणु
	/* packet ID to identअगरy the tx request */
	u8 pkt_id;

	/* rate policy to be used क्रम the tx of this frame */
	u8 rate_plcy_id;
पूर्ण __packed;

काष्ठा wmi_tx_meta_v2 अणु
	/*
	 * Offset from start of the WMI header क्रम csum calculation to
	 * begin.
	 */
	u8 csum_start;

	/* offset from start of WMI header where final csum goes */
	u8 csum_dest;

	/* no of bytes over which csum is calculated */
	u8 csum_flags;
पूर्ण __packed;

काष्ठा wmi_rx_meta_v1 अणु
	u8 status;

	/* rate index mapped to rate at which this packet was received. */
	u8 rix;

	/* rssi of packet */
	u8 rssi;

	/* rf channel during packet reception */
	u8 channel;

	__le16 flags;
पूर्ण __packed;

काष्ठा wmi_rx_meta_v2 अणु
	__le16 csum;

	/* bit 0 set -partial csum valid bit 1 set -test mode */
	u8 csum_flags;
पूर्ण __packed;

#घोषणा WMI_CMD_HDR_IF_ID_MASK 0xF

/* Control Path */
काष्ठा wmi_cmd_hdr अणु
	__le16 cmd_id;

	/* info1 - 16 bits
	 * b03:b00 - id
	 * b15:b04 - unused */
	__le16 info1;

	/* क्रम alignment */
	__le16 reserved;
पूर्ण __packed;

अटल अंतरभूत u8 wmi_cmd_hdr_get_अगर_idx(काष्ठा wmi_cmd_hdr *chdr)
अणु
	वापस le16_to_cpu(chdr->info1) & WMI_CMD_HDR_IF_ID_MASK;
पूर्ण

/* List of WMI commands */
क्रमागत wmi_cmd_id अणु
	WMI_CONNECT_CMDID = 0x0001,
	WMI_RECONNECT_CMDID,
	WMI_DISCONNECT_CMDID,
	WMI_SYNCHRONIZE_CMDID,
	WMI_CREATE_PSTREAM_CMDID,
	WMI_DELETE_PSTREAM_CMDID,
	/* WMI_START_SCAN_CMDID is to be deprecated. Use
	 * WMI_BEGIN_SCAN_CMDID instead. The new cmd supports P2P mgmt
	 * operations using station पूर्णांकerface.
	 */
	WMI_START_SCAN_CMDID,
	WMI_SET_SCAN_PARAMS_CMDID,
	WMI_SET_BSS_FILTER_CMDID,
	WMI_SET_PROBED_SSID_CMDID,	/* 10 */
	WMI_SET_LISTEN_INT_CMDID,
	WMI_SET_BMISS_TIME_CMDID,
	WMI_SET_DISC_TIMEOUT_CMDID,
	WMI_GET_CHANNEL_LIST_CMDID,
	WMI_SET_BEACON_INT_CMDID,
	WMI_GET_STATISTICS_CMDID,
	WMI_SET_CHANNEL_PARAMS_CMDID,
	WMI_SET_POWER_MODE_CMDID,
	WMI_SET_IBSS_PM_CAPS_CMDID,
	WMI_SET_POWER_PARAMS_CMDID,	/* 20 */
	WMI_SET_POWERSAVE_TIMERS_POLICY_CMDID,
	WMI_ADD_CIPHER_KEY_CMDID,
	WMI_DELETE_CIPHER_KEY_CMDID,
	WMI_ADD_KRK_CMDID,
	WMI_DELETE_KRK_CMDID,
	WMI_SET_PMKID_CMDID,
	WMI_SET_TX_PWR_CMDID,
	WMI_GET_TX_PWR_CMDID,
	WMI_SET_ASSOC_INFO_CMDID,
	WMI_ADD_BAD_AP_CMDID,		/* 30 */
	WMI_DELETE_BAD_AP_CMDID,
	WMI_SET_TKIP_COUNTERMEASURES_CMDID,
	WMI_RSSI_THRESHOLD_PARAMS_CMDID,
	WMI_TARGET_ERROR_REPORT_BITMASK_CMDID,
	WMI_SET_ACCESS_PARAMS_CMDID,
	WMI_SET_RETRY_LIMITS_CMDID,
	WMI_SET_OPT_MODE_CMDID,
	WMI_OPT_TX_FRAME_CMDID,
	WMI_SET_VOICE_PKT_SIZE_CMDID,
	WMI_SET_MAX_SP_LEN_CMDID,	/* 40 */
	WMI_SET_ROAM_CTRL_CMDID,
	WMI_GET_ROAM_TBL_CMDID,
	WMI_GET_ROAM_DATA_CMDID,
	WMI_ENABLE_RM_CMDID,
	WMI_SET_MAX_OFFHOME_DURATION_CMDID,
	WMI_EXTENSION_CMDID,	/* Non-wireless extensions */
	WMI_SNR_THRESHOLD_PARAMS_CMDID,
	WMI_LQ_THRESHOLD_PARAMS_CMDID,
	WMI_SET_LPREAMBLE_CMDID,
	WMI_SET_RTS_CMDID,		/* 50 */
	WMI_CLR_RSSI_SNR_CMDID,
	WMI_SET_FIXRATES_CMDID,
	WMI_GET_FIXRATES_CMDID,
	WMI_SET_AUTH_MODE_CMDID,
	WMI_SET_REASSOC_MODE_CMDID,
	WMI_SET_WMM_CMDID,
	WMI_SET_WMM_TXOP_CMDID,
	WMI_TEST_CMDID,

	/* COEX AR6002 only */
	WMI_SET_BT_STATUS_CMDID,
	WMI_SET_BT_PARAMS_CMDID,	/* 60 */

	WMI_SET_KEEPALIVE_CMDID,
	WMI_GET_KEEPALIVE_CMDID,
	WMI_SET_APPIE_CMDID,
	WMI_GET_APPIE_CMDID,
	WMI_SET_WSC_STATUS_CMDID,

	/* Wake on Wireless */
	WMI_SET_HOST_SLEEP_MODE_CMDID,
	WMI_SET_WOW_MODE_CMDID,
	WMI_GET_WOW_LIST_CMDID,
	WMI_ADD_WOW_PATTERN_CMDID,
	WMI_DEL_WOW_PATTERN_CMDID,	/* 70 */

	WMI_SET_FRAMERATES_CMDID,
	WMI_SET_AP_PS_CMDID,
	WMI_SET_QOS_SUPP_CMDID,
	WMI_SET_IE_CMDID,

	/* WMI_THIN_RESERVED_... mark the start and end
	 * values क्रम WMI_THIN_RESERVED command IDs. These
	 * command IDs can be found in wmi_thin.h */
	WMI_THIN_RESERVED_START = 0x8000,
	WMI_THIN_RESERVED_END = 0x8fff,

	/* Developer commands starts at 0xF000 */
	WMI_SET_BITRATE_CMDID = 0xF000,
	WMI_GET_BITRATE_CMDID,
	WMI_SET_WHALPARAM_CMDID,
	WMI_SET_MAC_ADDRESS_CMDID,
	WMI_SET_AKMP_PARAMS_CMDID,
	WMI_SET_PMKID_LIST_CMDID,
	WMI_GET_PMKID_LIST_CMDID,
	WMI_ABORT_SCAN_CMDID,
	WMI_SET_TARGET_EVENT_REPORT_CMDID,

	/* Unused */
	WMI_UNUSED1,
	WMI_UNUSED2,

	/* AP mode commands */
	WMI_AP_HIDDEN_SSID_CMDID,
	WMI_AP_SET_NUM_STA_CMDID,
	WMI_AP_ACL_POLICY_CMDID,
	WMI_AP_ACL_MAC_LIST_CMDID,
	WMI_AP_CONFIG_COMMIT_CMDID,
	WMI_AP_SET_MLME_CMDID,
	WMI_AP_SET_PVB_CMDID,
	WMI_AP_CONN_INACT_CMDID,
	WMI_AP_PROT_SCAN_TIME_CMDID,
	WMI_AP_SET_COUNTRY_CMDID,
	WMI_AP_SET_DTIM_CMDID,
	WMI_AP_MODE_STAT_CMDID,

	WMI_SET_IP_CMDID,
	WMI_SET_PARAMS_CMDID,
	WMI_SET_MCAST_FILTER_CMDID,
	WMI_DEL_MCAST_FILTER_CMDID,

	WMI_ALLOW_AGGR_CMDID,
	WMI_ADDBA_REQ_CMDID,
	WMI_DELBA_REQ_CMDID,
	WMI_SET_HT_CAP_CMDID,
	WMI_SET_HT_OP_CMDID,
	WMI_SET_TX_SELECT_RATES_CMDID,
	WMI_SET_TX_SGI_PARAM_CMDID,
	WMI_SET_RATE_POLICY_CMDID,

	WMI_HCI_CMD_CMDID,
	WMI_RX_FRAME_FORMAT_CMDID,
	WMI_SET_THIN_MODE_CMDID,
	WMI_SET_BT_WLAN_CONN_PRECEDENCE_CMDID,

	WMI_AP_SET_11BG_RATESET_CMDID,
	WMI_SET_PMK_CMDID,
	WMI_MCAST_FILTER_CMDID,

	/* COEX CMDID AR6003 */
	WMI_SET_BTCOEX_FE_ANT_CMDID,
	WMI_SET_BTCOEX_COLOCATED_BT_DEV_CMDID,
	WMI_SET_BTCOEX_SCO_CONFIG_CMDID,
	WMI_SET_BTCOEX_A2DP_CONFIG_CMDID,
	WMI_SET_BTCOEX_ACLCOEX_CONFIG_CMDID,
	WMI_SET_BTCOEX_BTINQUIRY_PAGE_CONFIG_CMDID,
	WMI_SET_BTCOEX_DEBUG_CMDID,
	WMI_SET_BTCOEX_BT_OPERATING_STATUS_CMDID,
	WMI_GET_BTCOEX_STATS_CMDID,
	WMI_GET_BTCOEX_CONFIG_CMDID,

	WMI_SET_DFS_ENABLE_CMDID,	/* F034 */
	WMI_SET_DFS_MINRSSITHRESH_CMDID,
	WMI_SET_DFS_MAXPULSEDUR_CMDID,
	WMI_DFS_RADAR_DETECTED_CMDID,

	/* P2P commands */
	WMI_P2P_SET_CONFIG_CMDID,	/* F038 */
	WMI_WPS_SET_CONFIG_CMDID,
	WMI_SET_REQ_DEV_ATTR_CMDID,
	WMI_P2P_FIND_CMDID,
	WMI_P2P_STOP_FIND_CMDID,
	WMI_P2P_GO_NEG_START_CMDID,
	WMI_P2P_LISTEN_CMDID,

	WMI_CONFIG_TX_MAC_RULES_CMDID,	/* F040 */
	WMI_SET_PROMISCUOUS_MODE_CMDID,
	WMI_RX_FRAME_FILTER_CMDID,
	WMI_SET_CHANNEL_CMDID,

	/* WAC commands */
	WMI_ENABLE_WAC_CMDID,
	WMI_WAC_SCAN_REPLY_CMDID,
	WMI_WAC_CTRL_REQ_CMDID,
	WMI_SET_DIV_PARAMS_CMDID,

	WMI_GET_PMK_CMDID,
	WMI_SET_PASSPHRASE_CMDID,
	WMI_SEND_ASSOC_RES_CMDID,
	WMI_SET_ASSOC_REQ_RELAY_CMDID,

	/* ACS command, consists of sub-commands */
	WMI_ACS_CTRL_CMDID,
	WMI_SET_EXCESS_TX_RETRY_THRES_CMDID,
	WMI_SET_TBD_TIME_CMDID, /*added क्रम wmiconfig command क्रम TBD */

	/* Pktlog cmds */
	WMI_PKTLOG_ENABLE_CMDID,
	WMI_PKTLOG_DISABLE_CMDID,

	/* More P2P Cmds */
	WMI_P2P_GO_NEG_REQ_RSP_CMDID,
	WMI_P2P_GRP_INIT_CMDID,
	WMI_P2P_GRP_FORMATION_DONE_CMDID,
	WMI_P2P_INVITE_CMDID,
	WMI_P2P_INVITE_REQ_RSP_CMDID,
	WMI_P2P_PROV_DISC_REQ_CMDID,
	WMI_P2P_SET_CMDID,

	WMI_GET_RFKILL_MODE_CMDID,
	WMI_SET_RFKILL_MODE_CMDID,
	WMI_AP_SET_APSD_CMDID,
	WMI_AP_APSD_BUFFERED_TRAFFIC_CMDID,

	WMI_P2P_SDPD_TX_CMDID, /* F05C */
	WMI_P2P_STOP_SDPD_CMDID,
	WMI_P2P_CANCEL_CMDID,
	/* Ultra low घातer store / recall commands */
	WMI_STORERECALL_CONFIGURE_CMDID,
	WMI_STORERECALL_RECALL_CMDID,
	WMI_STORERECALL_HOST_READY_CMDID,
	WMI_FORCE_TARGET_ASSERT_CMDID,

	WMI_SET_PROBED_SSID_EX_CMDID,
	WMI_SET_NETWORK_LIST_OFFLOAD_CMDID,
	WMI_SET_ARP_NS_OFFLOAD_CMDID,
	WMI_ADD_WOW_EXT_PATTERN_CMDID,
	WMI_GTK_OFFLOAD_OP_CMDID,
	WMI_REMAIN_ON_CHNL_CMDID,
	WMI_CANCEL_REMAIN_ON_CHNL_CMDID,
	/* WMI_SEND_ACTION_CMDID is to be deprecated. Use
	 * WMI_SEND_MGMT_CMDID instead. The new cmd supports P2P mgmt
	 * operations using station पूर्णांकerface.
	 */
	WMI_SEND_ACTION_CMDID,
	WMI_PROBE_REQ_REPORT_CMDID,
	WMI_DISABLE_11B_RATES_CMDID,
	WMI_SEND_PROBE_RESPONSE_CMDID,
	WMI_GET_P2P_INFO_CMDID,
	WMI_AP_JOIN_BSS_CMDID,

	WMI_SMPS_ENABLE_CMDID,
	WMI_SMPS_CONFIG_CMDID,
	WMI_SET_RATECTRL_PARM_CMDID,
	/*  LPL specअगरic commands*/
	WMI_LPL_FORCE_ENABLE_CMDID,
	WMI_LPL_SET_POLICY_CMDID,
	WMI_LPL_GET_POLICY_CMDID,
	WMI_LPL_GET_HWSTATE_CMDID,
	WMI_LPL_SET_PARAMS_CMDID,
	WMI_LPL_GET_PARAMS_CMDID,

	WMI_SET_BUNDLE_PARAM_CMDID,

	/*GreenTx specअगरic commands*/

	WMI_GREENTX_PARAMS_CMDID,

	WMI_RTT_MEASREQ_CMDID,
	WMI_RTT_CAPREQ_CMDID,
	WMI_RTT_STATUSREQ_CMDID,

	/* WPS Commands */
	WMI_WPS_START_CMDID,
	WMI_GET_WPS_STATUS_CMDID,

	/* More P2P commands */
	WMI_SET_NOA_CMDID,
	WMI_GET_NOA_CMDID,
	WMI_SET_OPPPS_CMDID,
	WMI_GET_OPPPS_CMDID,
	WMI_ADD_PORT_CMDID,
	WMI_DEL_PORT_CMDID,

	/* 802.11w cmd */
	WMI_SET_RSN_CAP_CMDID,
	WMI_GET_RSN_CAP_CMDID,
	WMI_SET_IGTK_CMDID,

	WMI_RX_FILTER_COALESCE_FILTER_OP_CMDID,
	WMI_RX_FILTER_SET_FRAME_TEST_LIST_CMDID,

	WMI_SEND_MGMT_CMDID,
	WMI_BEGIN_SCAN_CMDID,

	WMI_SET_BLACK_LIST,
	WMI_SET_MCASTRATE,

	WMI_STA_BMISS_ENHANCE_CMDID,

	WMI_SET_REGDOMAIN_CMDID,

	WMI_SET_RSSI_FILTER_CMDID,

	WMI_SET_KEEP_ALIVE_EXT,

	WMI_VOICE_DETECTION_ENABLE_CMDID,

	WMI_SET_TXE_NOTIFY_CMDID,

	WMI_SET_RECOVERY_TEST_PARAMETER_CMDID, /*0xf094*/

	WMI_ENABLE_SCHED_SCAN_CMDID,
पूर्ण;

क्रमागत wmi_mgmt_frame_type अणु
	WMI_FRAME_BEACON = 0,
	WMI_FRAME_PROBE_REQ,
	WMI_FRAME_PROBE_RESP,
	WMI_FRAME_ASSOC_REQ,
	WMI_FRAME_ASSOC_RESP,
	WMI_NUM_MGMT_FRAME
पूर्ण;

क्रमागत wmi_ie_field_type अणु
	WMI_RSN_IE_CAPB	= 0x1,
	WMI_IE_FULL	= 0xFF,  /* indicats full IE */
पूर्ण;

/* WMI_CONNECT_CMDID  */
क्रमागत network_type अणु
	INFRA_NETWORK = 0x01,
	ADHOC_NETWORK = 0x02,
	ADHOC_CREATOR = 0x04,
	AP_NETWORK = 0x10,
पूर्ण;

क्रमागत network_subtype अणु
	SUBTYPE_NONE,
	SUBTYPE_BT,
	SUBTYPE_P2PDEV,
	SUBTYPE_P2PCLIENT,
	SUBTYPE_P2PGO,
पूर्ण;

क्रमागत करोt11_auth_mode अणु
	OPEN_AUTH = 0x01,
	SHARED_AUTH = 0x02,

	/* dअगरferent from IEEE_AUTH_MODE definitions */
	LEAP_AUTH = 0x04,
पूर्ण;

क्रमागत auth_mode अणु
	NONE_AUTH = 0x01,
	WPA_AUTH = 0x02,
	WPA2_AUTH = 0x04,
	WPA_PSK_AUTH = 0x08,
	WPA2_PSK_AUTH = 0x10,
	WPA_AUTH_CCKM = 0x20,
	WPA2_AUTH_CCKM = 0x40,
पूर्ण;

#घोषणा WMI_MAX_KEY_INDEX   3

#घोषणा WMI_MAX_KEY_LEN     32

/*
 * NB: these values are ordered carefully; there are lots of
 * of implications in any reordering.  In particular beware
 * that 4 is not used to aव्योम conflicting with IEEE80211_F_PRIVACY.
 */
#घोषणा ATH6KL_CIPHER_WEP            0
#घोषणा ATH6KL_CIPHER_TKIP           1
#घोषणा ATH6KL_CIPHER_AES_OCB        2
#घोषणा ATH6KL_CIPHER_AES_CCM        3
#घोषणा ATH6KL_CIPHER_CKIP           5
#घोषणा ATH6KL_CIPHER_CCKM_KRK       6
#घोषणा ATH6KL_CIPHER_NONE           7 /* pseuकरो value */

/*
 * 802.11 rate set.
 */
#घोषणा ATH6KL_RATE_MAXSIZE  15	/* max rates we'll handle */

#घोषणा ATH_OUI_TYPE            0x01
#घोषणा WPA_OUI_TYPE            0x01
#घोषणा WMM_PARAM_OUI_SUBTYPE   0x01
#घोषणा WMM_OUI_TYPE            0x02
#घोषणा WSC_OUT_TYPE            0x04

क्रमागत wmi_connect_ctrl_flags_bits अणु
	CONNECT_ASSOC_POLICY_USER = 0x0001,
	CONNECT_SEND_REASSOC = 0x0002,
	CONNECT_IGNORE_WPAx_GROUP_CIPHER = 0x0004,
	CONNECT_PROखाता_MATCH_DONE = 0x0008,
	CONNECT_IGNORE_AAC_BEACON = 0x0010,
	CONNECT_CSA_FOLLOW_BSS = 0x0020,
	CONNECT_DO_WPA_OFFLOAD = 0x0040,
	CONNECT_DO_NOT_DEAUTH = 0x0080,
	CONNECT_WPS_FLAG = 0x0100,
पूर्ण;

काष्ठा wmi_connect_cmd अणु
	u8 nw_type;
	u8 करोt11_auth_mode;
	u8 auth_mode;
	u8 prwise_crypto_type;
	u8 prwise_crypto_len;
	u8 grp_crypto_type;
	u8 grp_crypto_len;
	u8 ssid_len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	__le16 ch;
	u8 bssid[ETH_ALEN];
	__le32 ctrl_flags;
	u8 nw_subtype;
पूर्ण __packed;

/* WMI_RECONNECT_CMDID */
काष्ठा wmi_reconnect_cmd अणु
	/* channel hपूर्णांक */
	__le16 channel;

	/* mandatory अगर set */
	u8 bssid[ETH_ALEN];
पूर्ण __packed;

/* WMI_ADD_CIPHER_KEY_CMDID */
क्रमागत key_usage अणु
	PAIRWISE_USAGE = 0x00,
	GROUP_USAGE = 0x01,

	/* शेष Tx Key - अटल WEP only */
	TX_USAGE = 0x02,
पूर्ण;

/*
 * Bit Flag
 * Bit 0 - Initialise TSC - शेष is Initialize
 */
#घोषणा KEY_OP_INIT_TSC     0x01
#घोषणा KEY_OP_INIT_RSC     0x02

/* शेष initialise the TSC & RSC */
#घोषणा KEY_OP_INIT_VAL     0x03
#घोषणा KEY_OP_VALID_MASK   0x03

काष्ठा wmi_add_cipher_key_cmd अणु
	u8 key_index;
	u8 key_type;

	/* क्रमागत key_usage */
	u8 key_usage;

	u8 key_len;

	/* key replay sequence counter */
	u8 key_rsc[8];

	u8 key[WLAN_MAX_KEY_LEN];

	/* additional key control info */
	u8 key_op_ctrl;

	u8 key_mac_addr[ETH_ALEN];
पूर्ण __packed;

/* WMI_DELETE_CIPHER_KEY_CMDID */
काष्ठा wmi_delete_cipher_key_cmd अणु
	u8 key_index;
पूर्ण __packed;

#घोषणा WMI_KRK_LEN     16

/* WMI_ADD_KRK_CMDID */
काष्ठा wmi_add_krk_cmd अणु
	u8 krk[WMI_KRK_LEN];
पूर्ण __packed;

/* WMI_SETPMKID_CMDID */

#घोषणा WMI_PMKID_LEN 16

क्रमागत pmkid_enable_flg अणु
	PMKID_DISABLE = 0,
	PMKID_ENABLE = 1,
पूर्ण;

काष्ठा wmi_setpmkid_cmd अणु
	u8 bssid[ETH_ALEN];

	/* क्रमागत pmkid_enable_flg */
	u8 enable;

	u8 pmkid[WMI_PMKID_LEN];
पूर्ण __packed;

/* WMI_START_SCAN_CMD */
क्रमागत wmi_scan_type अणु
	WMI_LONG_SCAN = 0,
	WMI_SHORT_SCAN = 1,
पूर्ण;

काष्ठा wmi_supp_rates अणु
	u8 nrates;
	u8 rates[ATH6KL_RATE_MAXSIZE];
पूर्ण;

काष्ठा wmi_begin_scan_cmd अणु
	__le32 क्रमce_fg_scan;

	/* क्रम legacy cisco AP compatibility */
	__le32 is_legacy;

	/* max duration in the home channel(msec) */
	__le32 home_dwell_समय;

	/* समय पूर्णांकerval between scans (msec) */
	__le32 क्रमce_scan_पूर्णांकvl;

	/* no CCK rates */
	__le32 no_cck;

	/* क्रमागत wmi_scan_type */
	u8 scan_type;

	/* Supported rates to advertise in the probe request frames */
	काष्ठा wmi_supp_rates supp_rates[ATH6KL_NUM_BANDS];

	/* how many channels follow */
	u8 num_ch;

	/* channels in Mhz */
	__le16 ch_list[1];
पूर्ण __packed;

/* wmi_start_scan_cmd is to be deprecated. Use
 * wmi_begin_scan_cmd instead. The new काष्ठाure supports P2P mgmt
 * operations using station पूर्णांकerface.
 */
काष्ठा wmi_start_scan_cmd अणु
	__le32 क्रमce_fg_scan;

	/* क्रम legacy cisco AP compatibility */
	__le32 is_legacy;

	/* max duration in the home channel(msec) */
	__le32 home_dwell_समय;

	/* समय पूर्णांकerval between scans (msec) */
	__le32 क्रमce_scan_पूर्णांकvl;

	/* क्रमागत wmi_scan_type */
	u8 scan_type;

	/* how many channels follow */
	u8 num_ch;

	/* channels in Mhz */
	__le16 ch_list[1];
पूर्ण __packed;

/*
 *  Warning: scan control flag value of 0xFF is used to disable
 *  all flags in WMI_SCAN_PARAMS_CMD. Do not add any more
 *  flags here
 */
क्रमागत wmi_scan_ctrl_flags_bits अणु
	/* set अगर can scan in the connect cmd */
	CONNECT_SCAN_CTRL_FLAGS = 0x01,

	/* set अगर scan क्रम the SSID it is alपढ़ोy connected to */
	SCAN_CONNECTED_CTRL_FLAGS = 0x02,

	/* set अगर enable active scan */
	ACTIVE_SCAN_CTRL_FLAGS = 0x04,

	/* set अगर enable roam scan when bmiss and lowrssi */
	ROAM_SCAN_CTRL_FLAGS = 0x08,

	/* set अगर follows customer BSSINFO reporting rule */
	REPORT_BSSINFO_CTRL_FLAGS = 0x10,

	/* अगर disabled, target करोesn't scan after a disconnect event  */
	ENABLE_AUTO_CTRL_FLAGS = 0x20,

	/*
	 * Scan complete event with canceled status will be generated when
	 * a scan is prempted beक्रमe it माला_लो completed.
	 */
	ENABLE_SCAN_ABORT_EVENT = 0x40
पूर्ण;

काष्ठा wmi_scan_params_cmd अणु
	  /* sec */
	__le16 fg_start_period;

	/* sec */
	__le16 fg_end_period;

	/* sec */
	__le16 bg_period;

	/* msec */
	__le16 maxact_chdwell_समय;

	/* msec */
	__le16 pas_chdwell_समय;

	  /* how many लघुs scan क्रम one दीर्घ */
	u8 लघु_scan_ratio;

	u8 scan_ctrl_flags;

	/* msec */
	__le16 minact_chdwell_समय;

	/* max active scans per ssid */
	__le16 maxact_scan_per_ssid;

	/* msecs */
	__le32 max_dfsch_act_समय;
पूर्ण __packed;

/* WMI_ENABLE_SCHED_SCAN_CMDID */
काष्ठा wmi_enable_sched_scan_cmd अणु
	u8 enable;
पूर्ण __packed;

/* WMI_SET_BSS_FILTER_CMDID */
क्रमागत wmi_bss_filter अणु
	/* no beacons क्रमwarded */
	NONE_BSS_FILTER = 0x0,

	/* all beacons क्रमwarded */
	ALL_BSS_FILTER,

	/* only beacons matching profile */
	PROखाता_FILTER,

	/* all but beacons matching profile */
	ALL_BUT_PROखाता_FILTER,

	/* only beacons matching current BSS */
	CURRENT_BSS_FILTER,

	/* all but beacons matching BSS */
	ALL_BUT_BSS_FILTER,

	/* beacons matching probed ssid */
	PROBED_SSID_FILTER,

	/* beacons matching matched ssid */
	MATCHED_SSID_FILTER,

	/* marker only */
	LAST_BSS_FILTER,
पूर्ण;

काष्ठा wmi_bss_filter_cmd अणु
	/* see, क्रमागत wmi_bss_filter */
	u8 bss_filter;

	/* क्रम alignment */
	u8 reserved1;

	/* क्रम alignment */
	__le16 reserved2;

	__le32 ie_mask;
पूर्ण __packed;

/* WMI_SET_PROBED_SSID_CMDID */
#घोषणा MAX_PROBED_SSIDS   16

क्रमागत wmi_ssid_flag अणु
	/* disables entry */
	DISABLE_SSID_FLAG = 0,

	/* probes specअगरied ssid */
	SPECIFIC_SSID_FLAG = 0x01,

	/* probes क्रम any ssid */
	ANY_SSID_FLAG = 0x02,

	/* match क्रम ssid */
	MATCH_SSID_FLAG = 0x08,
पूर्ण;

काष्ठा wmi_probed_ssid_cmd अणु
	/* 0 to MAX_PROBED_SSIDS - 1 */
	u8 entry_index;

	/* see, क्रमागत wmi_ssid_flg */
	u8 flag;

	u8 ssid_len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
पूर्ण __packed;

/*
 * WMI_SET_LISTEN_INT_CMDID
 * The Listen पूर्णांकerval is between 15 and 3000 TUs
 */
काष्ठा wmi_listen_पूर्णांक_cmd अणु
	__le16 listen_पूर्णांकvl;
	__le16 num_beacons;
पूर्ण __packed;

/* WMI_SET_BMISS_TIME_CMDID */
काष्ठा wmi_bmiss_समय_cmd अणु
	__le16 bmiss_समय;
	__le16 num_beacons;
पूर्ण;

/* WMI_STA_ENHANCE_BMISS_CMDID */
काष्ठा wmi_sta_bmiss_enhance_cmd अणु
	u8 enable;
पूर्ण __packed;

काष्ठा wmi_set_regकरोमुख्य_cmd अणु
	u8 length;
	u8 iso_name[2];
पूर्ण __packed;

/* WMI_SET_POWER_MODE_CMDID */
क्रमागत wmi_घातer_mode अणु
	REC_POWER = 0x01,
	MAX_PERF_POWER,
पूर्ण;

काष्ठा wmi_घातer_mode_cmd अणु
	/* see, क्रमागत wmi_घातer_mode */
	u8 pwr_mode;
पूर्ण __packed;

/*
 * Policy to determine whether घातer save failure event should be sent to
 * host during scanning
 */
क्रमागत घातer_save_fail_event_policy अणु
	SEND_POWER_SAVE_FAIL_EVENT_ALWAYS = 1,
	IGNORE_PS_FAIL_DURING_SCAN = 2,
पूर्ण;

काष्ठा wmi_घातer_params_cmd अणु
	/* msec */
	__le16 idle_period;

	__le16 pspoll_number;
	__le16 dtim_policy;
	__le16 tx_wakeup_policy;
	__le16 num_tx_to_wakeup;
	__le16 ps_fail_event_policy;
पूर्ण __packed;

/*
 * Ratemask क्रम below modes should be passed
 * to WMI_SET_TX_SELECT_RATES_CMDID.
 * AR6003 has 32 bit mask क्रम each modes.
 * First 12 bits क्रम legacy rates, 13 to 20
 * bits क्रम HT 20 rates and 21 to 28 bits क्रम
 * HT 40 rates
 */
क्रमागत wmi_mode_phy अणु
	WMI_RATES_MODE_11A = 0,
	WMI_RATES_MODE_11G,
	WMI_RATES_MODE_11B,
	WMI_RATES_MODE_11GONLY,
	WMI_RATES_MODE_11A_HT20,
	WMI_RATES_MODE_11G_HT20,
	WMI_RATES_MODE_11A_HT40,
	WMI_RATES_MODE_11G_HT40,
	WMI_RATES_MODE_MAX
पूर्ण;

/* WMI_SET_TX_SELECT_RATES_CMDID */
काष्ठा wmi_set_tx_select_rates32_cmd अणु
	__le32 ratemask[WMI_RATES_MODE_MAX];
पूर्ण __packed;

/* WMI_SET_TX_SELECT_RATES_CMDID */
काष्ठा wmi_set_tx_select_rates64_cmd अणु
	__le64 ratemask[WMI_RATES_MODE_MAX];
पूर्ण __packed;

/* WMI_SET_DISC_TIMEOUT_CMDID */
काष्ठा wmi_disc_समयout_cmd अणु
	/* seconds */
	u8 discon_समयout;
पूर्ण __packed;

क्रमागत dir_type अणु
	UPLINK_TRAFFIC = 0,
	DNLINK_TRAFFIC = 1,
	BIसूची_TRAFFIC = 2,
पूर्ण;

क्रमागत voiceps_cap_type अणु
	DISABLE_FOR_THIS_AC = 0,
	ENABLE_FOR_THIS_AC = 1,
	ENABLE_FOR_ALL_AC = 2,
पूर्ण;

क्रमागत traffic_type अणु
	TRAFFIC_TYPE_APERIODIC = 0,
	TRAFFIC_TYPE_PERIODIC = 1,
पूर्ण;

/* WMI_SYNCHRONIZE_CMDID */
काष्ठा wmi_sync_cmd अणु
	u8 data_sync_map;
पूर्ण __packed;

/* WMI_CREATE_PSTREAM_CMDID */
काष्ठा wmi_create_pstream_cmd अणु
	/* msec */
	__le32 min_service_पूर्णांक;

	/* msec */
	__le32 max_service_पूर्णांक;

	/* msec */
	__le32 inactivity_पूर्णांक;

	/* msec */
	__le32 suspension_पूर्णांक;

	__le32 service_start_समय;

	/* in bps */
	__le32 min_data_rate;

	/* in bps */
	__le32 mean_data_rate;

	/* in bps */
	__le32 peak_data_rate;

	__le32 max_burst_size;
	__le32 delay_bound;

	/* in bps */
	__le32 min_phy_rate;

	__le32 sba;
	__le32 medium_समय;

	/* in octects */
	__le16 nominal_msdu;

	/* in octects */
	__le16 max_msdu;

	u8 traffic_class;

	/* see, क्रमागत dir_type */
	u8 traffic_direc;

	u8 rx_queue_num;

	/* see, क्रमागत traffic_type */
	u8 traffic_type;

	/* see, क्रमागत voiceps_cap_type */
	u8 voice_psc_cap;
	u8 tsid;

	/* 802.1D user priority */
	u8 user_pri;

	/* nominal phy rate */
	u8 nominal_phy;
पूर्ण __packed;

/* WMI_DELETE_PSTREAM_CMDID */
काष्ठा wmi_delete_pstream_cmd अणु
	u8 tx_queue_num;
	u8 rx_queue_num;
	u8 traffic_direc;
	u8 traffic_class;
	u8 tsid;
पूर्ण __packed;

/* WMI_SET_CHANNEL_PARAMS_CMDID */
क्रमागत wmi_phy_mode अणु
	WMI_11A_MODE = 0x1,
	WMI_11G_MODE = 0x2,
	WMI_11AG_MODE = 0x3,
	WMI_11B_MODE = 0x4,
	WMI_11GONLY_MODE = 0x5,
	WMI_11G_HT20	= 0x6,
पूर्ण;

#घोषणा WMI_MAX_CHANNELS        32

/*
 *  WMI_RSSI_THRESHOLD_PARAMS_CMDID
 *  Setting the pollसमय to 0 would disable polling. Threshold values are
 *  in the ascending order, and should agree to:
 *  (lowThreshold_lowerVal < lowThreshold_upperVal < highThreshold_lowerVal
 *   < highThreshold_upperVal)
 */

काष्ठा wmi_rssi_threshold_params_cmd अणु
	/* polling समय as a factor of LI */
	__le32 poll_समय;

	/* lowest of upper */
	a_sle16 thresh_above1_val;

	a_sle16 thresh_above2_val;
	a_sle16 thresh_above3_val;
	a_sle16 thresh_above4_val;
	a_sle16 thresh_above5_val;

	/* highest of upper */
	a_sle16 thresh_above6_val;

	/* lowest of bellow */
	a_sle16 thresh_below1_val;

	a_sle16 thresh_below2_val;
	a_sle16 thresh_below3_val;
	a_sle16 thresh_below4_val;
	a_sle16 thresh_below5_val;

	/* highest of bellow */
	a_sle16 thresh_below6_val;

	/* "alpha" */
	u8 weight;

	u8 reserved[3];
पूर्ण __packed;

/*
 *  WMI_SNR_THRESHOLD_PARAMS_CMDID
 *  Setting the pollसमय to 0 would disable polling.
 */

काष्ठा wmi_snr_threshold_params_cmd अणु
	/* polling समय as a factor of LI */
	__le32 poll_समय;

	/* "alpha" */
	u8 weight;

	/* lowest of uppper */
	u8 thresh_above1_val;

	u8 thresh_above2_val;
	u8 thresh_above3_val;

	/* highest of upper */
	u8 thresh_above4_val;

	/* lowest of bellow */
	u8 thresh_below1_val;

	u8 thresh_below2_val;
	u8 thresh_below3_val;

	/* highest of bellow */
	u8 thresh_below4_val;

	u8 reserved[3];
पूर्ण __packed;

/* Don't report BSSs with संकेत (RSSI) below this threshold */
काष्ठा wmi_set_rssi_filter_cmd अणु
	s8 rssi;
पूर्ण __packed;

क्रमागत wmi_preamble_policy अणु
	WMI_IGNORE_BARKER_IN_ERP = 0,
	WMI_FOLLOW_BARKER_IN_ERP,
पूर्ण;

काष्ठा wmi_set_lpreamble_cmd अणु
	u8 status;
	u8 preamble_policy;
पूर्ण __packed;

काष्ठा wmi_set_rts_cmd अणु
	__le16 threshold;
पूर्ण __packed;

/* WMI_SET_TX_PWR_CMDID */
काष्ठा wmi_set_tx_pwr_cmd अणु
	/* in dbM units */
	u8 dbM;
पूर्ण __packed;

काष्ठा wmi_tx_pwr_reply अणु
	/* in dbM units */
	u8 dbM;
पूर्ण __packed;

काष्ठा wmi_report_sleep_state_event अणु
	__le32 sleep_state;
पूर्ण;

क्रमागत wmi_report_sleep_status अणु
	WMI_REPORT_SLEEP_STATUS_IS_DEEP_SLEEP = 0,
	WMI_REPORT_SLEEP_STATUS_IS_AWAKE
पूर्ण;
क्रमागत target_event_report_config अणु
	/* शेष */
	DISCONN_EVT_IN_RECONN = 0,

	NO_DISCONN_EVT_IN_RECONN
पूर्ण;

काष्ठा wmi_mcast_filter_cmd अणु
	u8 mcast_all_enable;
पूर्ण __packed;

#घोषणा ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE 6
काष्ठा wmi_mcast_filter_add_del_cmd अणु
	u8 mcast_mac[ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE];
पूर्ण __packed;

काष्ठा wmi_set_htcap_cmd अणु
	u8 band;
	u8 ht_enable;
	u8 ht40_supported;
	u8 ht20_sgi;
	u8 ht40_sgi;
	u8 पूर्णांकolerant_40mhz;
	u8 max_ampdu_len_exp;
पूर्ण __packed;

/* Command Replies */

/* WMI_GET_CHANNEL_LIST_CMDID reply */
काष्ठा wmi_channel_list_reply अणु
	u8 reserved;

	/* number of channels in reply */
	u8 num_ch;

	/* channel in Mhz */
	__le16 ch_list[1];
पूर्ण __packed;

/* List of Events (target to host) */
क्रमागत wmi_event_id अणु
	WMI_READY_EVENTID = 0x1001,
	WMI_CONNECT_EVENTID,
	WMI_DISCONNECT_EVENTID,
	WMI_BSSINFO_EVENTID,
	WMI_CMDERROR_EVENTID,
	WMI_REGDOMAIN_EVENTID,
	WMI_PSTREAM_TIMEOUT_EVENTID,
	WMI_NEIGHBOR_REPORT_EVENTID,
	WMI_TKIP_MICERR_EVENTID,
	WMI_SCAN_COMPLETE_EVENTID,	/* 0x100a */
	WMI_REPORT_STATISTICS_EVENTID,
	WMI_RSSI_THRESHOLD_EVENTID,
	WMI_ERROR_REPORT_EVENTID,
	WMI_OPT_RX_FRAME_EVENTID,
	WMI_REPORT_ROAM_TBL_EVENTID,
	WMI_EXTENSION_EVENTID,
	WMI_CAC_EVENTID,
	WMI_SNR_THRESHOLD_EVENTID,
	WMI_LQ_THRESHOLD_EVENTID,
	WMI_TX_RETRY_ERR_EVENTID,	/* 0x1014 */
	WMI_REPORT_ROAM_DATA_EVENTID,
	WMI_TEST_EVENTID,
	WMI_APLIST_EVENTID,
	WMI_GET_WOW_LIST_EVENTID,
	WMI_GET_PMKID_LIST_EVENTID,
	WMI_CHANNEL_CHANGE_EVENTID,
	WMI_PEER_NODE_EVENTID,
	WMI_PSPOLL_EVENTID,
	WMI_DTIMEXPIRY_EVENTID,
	WMI_WLAN_VERSION_EVENTID,
	WMI_SET_PARAMS_REPLY_EVENTID,
	WMI_ADDBA_REQ_EVENTID,		/*0x1020 */
	WMI_ADDBA_RESP_EVENTID,
	WMI_DELBA_REQ_EVENTID,
	WMI_TX_COMPLETE_EVENTID,
	WMI_HCI_EVENT_EVENTID,
	WMI_ACL_DATA_EVENTID,
	WMI_REPORT_SLEEP_STATE_EVENTID,
	WMI_REPORT_BTCOEX_STATS_EVENTID,
	WMI_REPORT_BTCOEX_CONFIG_EVENTID,
	WMI_GET_PMK_EVENTID,

	/* DFS Events */
	WMI_DFS_HOST_ATTACH_EVENTID,
	WMI_DFS_HOST_INIT_EVENTID,
	WMI_DFS_RESET_DELAYLINES_EVENTID,
	WMI_DFS_RESET_RADARQ_EVENTID,
	WMI_DFS_RESET_AR_EVENTID,
	WMI_DFS_RESET_ARQ_EVENTID,
	WMI_DFS_SET_DUR_MULTIPLIER_EVENTID,
	WMI_DFS_SET_BANGRADAR_EVENTID,
	WMI_DFS_SET_DEBUGLEVEL_EVENTID,
	WMI_DFS_PHYERR_EVENTID,

	/* CCX Evants */
	WMI_CCX_RM_STATUS_EVENTID,

	/* P2P Events */
	WMI_P2P_GO_NEG_RESULT_EVENTID,

	WMI_WAC_SCAN_DONE_EVENTID,
	WMI_WAC_REPORT_BSS_EVENTID,
	WMI_WAC_START_WPS_EVENTID,
	WMI_WAC_CTRL_REQ_REPLY_EVENTID,

	WMI_REPORT_WMM_PARAMS_EVENTID,
	WMI_WAC_REJECT_WPS_EVENTID,

	/* More P2P Events */
	WMI_P2P_GO_NEG_REQ_EVENTID,
	WMI_P2P_INVITE_REQ_EVENTID,
	WMI_P2P_INVITE_RCVD_RESULT_EVENTID,
	WMI_P2P_INVITE_SENT_RESULT_EVENTID,
	WMI_P2P_PROV_DISC_RESP_EVENTID,
	WMI_P2P_PROV_DISC_REQ_EVENTID,

	/* RFKILL Events */
	WMI_RFKILL_STATE_CHANGE_EVENTID,
	WMI_RFKILL_GET_MODE_CMD_EVENTID,

	WMI_P2P_START_SDPD_EVENTID,
	WMI_P2P_SDPD_RX_EVENTID,

	WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENTID = 0x1047,

	WMI_THIN_RESERVED_START_EVENTID = 0x8000,
	/* Events in this range are reserved क्रम thinmode */
	WMI_THIN_RESERVED_END_EVENTID = 0x8fff,

	WMI_SET_CHANNEL_EVENTID,
	WMI_ASSOC_REQ_EVENTID,

	/* Generic ACS event */
	WMI_ACS_EVENTID,
	WMI_STORERECALL_STORE_EVENTID,
	WMI_WOW_EXT_WAKE_EVENTID,
	WMI_GTK_OFFLOAD_STATUS_EVENTID,
	WMI_NETWORK_LIST_OFFLOAD_EVENTID,
	WMI_REMAIN_ON_CHNL_EVENTID,
	WMI_CANCEL_REMAIN_ON_CHNL_EVENTID,
	WMI_TX_STATUS_EVENTID,
	WMI_RX_PROBE_REQ_EVENTID,
	WMI_P2P_CAPABILITIES_EVENTID,
	WMI_RX_ACTION_EVENTID,
	WMI_P2P_INFO_EVENTID,

	/* WPS Events */
	WMI_WPS_GET_STATUS_EVENTID,
	WMI_WPS_PROखाता_EVENTID,

	/* more P2P events */
	WMI_NOA_INFO_EVENTID,
	WMI_OPPPS_INFO_EVENTID,
	WMI_PORT_STATUS_EVENTID,

	/* 802.11w */
	WMI_GET_RSN_CAP_EVENTID,

	WMI_TXE_NOTIFY_EVENTID,
पूर्ण;

काष्ठा wmi_पढ़ोy_event_2 अणु
	__le32 sw_version;
	__le32 abi_version;
	u8 mac_addr[ETH_ALEN];
	u8 phy_cap;
पूर्ण __packed;

/* WMI_PHY_CAPABILITY */
क्रमागत wmi_phy_cap अणु
	WMI_11A_CAP = 0x01,
	WMI_11G_CAP = 0x02,
	WMI_11AG_CAP = 0x03,
	WMI_11AN_CAP = 0x04,
	WMI_11GN_CAP = 0x05,
	WMI_11AGN_CAP = 0x06,
पूर्ण;

/* Connect Event */
काष्ठा wmi_connect_event अणु
	जोड़ अणु
		काष्ठा अणु
			__le16 ch;
			u8 bssid[ETH_ALEN];
			__le16 listen_पूर्णांकvl;
			__le16 beacon_पूर्णांकvl;
			__le32 nw_type;
		पूर्ण sta;
		काष्ठा अणु
			u8 aid;
			u8 phymode;
			u8 mac_addr[ETH_ALEN];
			u8 auth;
			u8 keymgmt;
			__le16 cipher;
			u8 apsd_info;
			u8 unused[3];
		पूर्ण ap_sta;
		काष्ठा अणु
			__le16 ch;
			u8 bssid[ETH_ALEN];
			u8 unused[8];
		पूर्ण ap_bss;
	पूर्ण u;
	u8 beacon_ie_len;
	u8 assoc_req_len;
	u8 assoc_resp_len;
	u8 assoc_info[1];
पूर्ण __packed;

/* Disconnect Event */
क्रमागत wmi_disconnect_reason अणु
	NO_NETWORK_AVAIL = 0x01,

	/* bmiss */
	LOST_LINK = 0x02,

	DISCONNECT_CMD = 0x03,
	BSS_DISCONNECTED = 0x04,
	AUTH_FAILED = 0x05,
	ASSOC_FAILED = 0x06,
	NO_RESOURCES_AVAIL = 0x07,
	CSERV_DISCONNECT = 0x08,
	INVALID_PROखाता = 0x0a,
	DOT11H_CHANNEL_SWITCH = 0x0b,
	PROखाता_MISMATCH = 0x0c,
	CONNECTION_EVICTED = 0x0d,
	IBSS_MERGE = 0xe,
पूर्ण;

/* AP mode disconnect proto_reasons */
क्रमागत ap_disconnect_reason अणु
	WMI_AP_REASON_STA_LEFT		= 101,
	WMI_AP_REASON_FROM_HOST		= 102,
	WMI_AP_REASON_COMM_TIMEOUT	= 103,
	WMI_AP_REASON_MAX_STA		= 104,
	WMI_AP_REASON_ACL		= 105,
	WMI_AP_REASON_STA_ROAM		= 106,
	WMI_AP_REASON_DFS_CHANNEL	= 107,
पूर्ण;

#घोषणा ATH6KL_COUNTRY_RD_SHIFT        16

काष्ठा ath6kl_wmi_regकरोमुख्य अणु
	__le32 reg_code;
पूर्ण;

काष्ठा wmi_disconnect_event अणु
	/* reason code, see 802.11 spec. */
	__le16 proto_reason_status;

	/* set अगर known */
	u8 bssid[ETH_ALEN];

	/* see WMI_DISCONNECT_REASON */
	u8 disconn_reason;

	u8 assoc_resp_len;
	u8 assoc_info[1];
पूर्ण __packed;

/*
 * BSS Info Event.
 * Mechanism used to inक्रमm host of the presence and अक्षरacteristic of
 * wireless networks present.  Consists of bss info header followed by
 * the beacon or probe-response frame body.  The 802.11 header is no included.
 */
क्रमागत wmi_bi_ftype अणु
	BEACON_FTYPE = 0x1,
	PROBERESP_FTYPE,
	ACTION_MGMT_FTYPE,
	PROBEREQ_FTYPE,
पूर्ण;

#घोषणा DEF_LRSSI_SCAN_PERIOD		 5
#घोषणा DEF_LRSSI_ROAM_THRESHOLD	20
#घोषणा DEF_LRSSI_ROAM_FLOOR		60
#घोषणा DEF_SCAN_FOR_ROAM_INTVL		 2

क्रमागत wmi_roam_ctrl अणु
	WMI_FORCE_ROAM = 1,
	WMI_SET_ROAM_MODE,
	WMI_SET_HOST_BIAS,
	WMI_SET_LRSSI_SCAN_PARAMS,
पूर्ण;

क्रमागत wmi_roam_mode अणु
	WMI_DEFAULT_ROAM_MODE = 1, /* RSSI based roam */
	WMI_HOST_BIAS_ROAM_MODE = 2, /* Host bias based roam */
	WMI_LOCK_BSS_MODE = 3, /* Lock to the current BSS */
पूर्ण;

काष्ठा bss_bias अणु
	u8 bssid[ETH_ALEN];
	s8 bias;
पूर्ण __packed;

काष्ठा bss_bias_info अणु
	u8 num_bss;
	काष्ठा bss_bias bss_bias[0];
पूर्ण __packed;

काष्ठा low_rssi_scan_params अणु
	__le16 lrssi_scan_period;
	a_sle16 lrssi_scan_threshold;
	a_sle16 lrssi_roam_threshold;
	u8 roam_rssi_न्यूनमान;
	u8 reserved[1];
पूर्ण __packed;

काष्ठा roam_ctrl_cmd अणु
	जोड़ अणु
		u8 bssid[ETH_ALEN]; /* WMI_FORCE_ROAM */
		u8 roam_mode; /* WMI_SET_ROAM_MODE */
		काष्ठा bss_bias_info bss; /* WMI_SET_HOST_BIAS */
		काष्ठा low_rssi_scan_params params; /* WMI_SET_LRSSI_SCAN_PARAMS
						     */
	पूर्ण __packed info;
	u8 roam_ctrl;
पूर्ण __packed;

काष्ठा set_beacon_पूर्णांक_cmd अणु
	__le32 beacon_पूर्णांकvl;
पूर्ण __packed;

काष्ठा set_dtim_cmd अणु
	__le32 dtim_period;
पूर्ण __packed;

/* BSS INFO HDR version 2.0 */
काष्ठा wmi_bss_info_hdr2 अणु
	__le16 ch; /* frequency in MHz */

	/* see, क्रमागत wmi_bi_ftype */
	u8 frame_type;

	u8 snr; /* note: rssi = snr - 95 dBm */
	u8 bssid[ETH_ALEN];
	__le16 ie_mask;
पूर्ण __packed;

/* Command Error Event */
क्रमागत wmi_error_code अणु
	INVALID_PARAM = 0x01,
	ILLEGAL_STATE = 0x02,
	INTERNAL_ERROR = 0x03,
पूर्ण;

काष्ठा wmi_cmd_error_event अणु
	__le16 cmd_id;
	u8 err_code;
पूर्ण __packed;

काष्ठा wmi_pstream_समयout_event अणु
	u8 tx_queue_num;
	u8 rx_queue_num;
	u8 traffic_direc;
	u8 traffic_class;
पूर्ण __packed;

/*
 * The WMI_NEIGHBOR_REPORT Event is generated by the target to inक्रमm
 * the host of BSS's it has found that matches the current profile.
 * It can be used by the host to cache PMKs and/to initiate pre-authentication
 * अगर the BSS supports it.  The first bssid is always the current associated
 * BSS.
 * The bssid and bssFlags inक्रमmation repeats according to the number
 * or APs reported.
 */
क्रमागत wmi_bss_flags अणु
	WMI_DEFAULT_BSS_FLAGS = 0x00,
	WMI_PREAUTH_CAPABLE_BSS = 0x01,
	WMI_PMKID_VALID_BSS = 0x02,
पूर्ण;

काष्ठा wmi_neighbor_info अणु
	u8 bssid[ETH_ALEN];
	u8 bss_flags; /* क्रमागत wmi_bss_flags */
पूर्ण __packed;

काष्ठा wmi_neighbor_report_event अणु
	u8 num_neighbors;
	काष्ठा wmi_neighbor_info neighbor[0];
पूर्ण __packed;

/* TKIP MIC Error Event */
काष्ठा wmi_tkip_micerr_event अणु
	u8 key_id;
	u8 is_mcast;
पूर्ण __packed;

क्रमागत wmi_scan_status अणु
	WMI_SCAN_STATUS_SUCCESS = 0,
पूर्ण;

/* WMI_SCAN_COMPLETE_EVENTID */
काष्ठा wmi_scan_complete_event अणु
	a_sle32 status;
पूर्ण __packed;

#घोषणा MAX_OPT_DATA_LEN 1400

/*
 * Special frame receive Event.
 * Mechanism used to inक्रमm host of the receiption of the special frames.
 * Consists of special frame info header followed by special frame body.
 * The 802.11 header is not included.
 */
काष्ठा wmi_opt_rx_info_hdr अणु
	__le16 ch;
	u8 frame_type;
	s8 snr;
	u8 src_addr[ETH_ALEN];
	u8 bssid[ETH_ALEN];
पूर्ण __packed;

/* Reporting statistic */
काष्ठा tx_stats अणु
	__le32 pkt;
	__le32 byte;
	__le32 ucast_pkt;
	__le32 ucast_byte;
	__le32 mcast_pkt;
	__le32 mcast_byte;
	__le32 bcast_pkt;
	__le32 bcast_byte;
	__le32 rts_success_cnt;
	__le32 pkt_per_ac[4];
	__le32 err_per_ac[4];

	__le32 err;
	__le32 fail_cnt;
	__le32 retry_cnt;
	__le32 mult_retry_cnt;
	__le32 rts_fail_cnt;
	a_sle32 ucast_rate;
पूर्ण __packed;

काष्ठा rx_stats अणु
	__le32 pkt;
	__le32 byte;
	__le32 ucast_pkt;
	__le32 ucast_byte;
	__le32 mcast_pkt;
	__le32 mcast_byte;
	__le32 bcast_pkt;
	__le32 bcast_byte;
	__le32 frgment_pkt;

	__le32 err;
	__le32 crc_err;
	__le32 key_cache_miss;
	__le32 decrypt_err;
	__le32 dupl_frame;
	a_sle32 ucast_rate;
पूर्ण __packed;

#घोषणा RATE_INDEX_WITHOUT_SGI_MASK     0x7f
#घोषणा RATE_INDEX_MSB     0x80

काष्ठा tkip_ccmp_stats अणु
	__le32 tkip_local_mic_fail;
	__le32 tkip_cnter_measures_invoked;
	__le32 tkip_replays;
	__le32 tkip_fmt_err;
	__le32 ccmp_fmt_err;
	__le32 ccmp_replays;
पूर्ण __packed;

काष्ठा pm_stats अणु
	__le32 pwr_save_failure_cnt;
	__le16 stop_tx_failure_cnt;
	__le16 atim_tx_failure_cnt;
	__le16 atim_rx_failure_cnt;
	__le16 bcn_rx_failure_cnt;
पूर्ण __packed;

काष्ठा cserv_stats अणु
	__le32 cs_bmiss_cnt;
	__le32 cs_low_rssi_cnt;
	__le16 cs_connect_cnt;
	__le16 cs_discon_cnt;
	a_sle16 cs_ave_beacon_rssi;
	__le16 cs_roam_count;
	a_sle16 cs_rssi;
	u8 cs_snr;
	u8 cs_ave_beacon_snr;
	u8 cs_last_roam_msec;
पूर्ण __packed;

काष्ठा wlan_net_stats अणु
	काष्ठा tx_stats tx;
	काष्ठा rx_stats rx;
	काष्ठा tkip_ccmp_stats tkip_ccmp_stats;
पूर्ण __packed;

काष्ठा arp_stats अणु
	__le32 arp_received;
	__le32 arp_matched;
	__le32 arp_replied;
पूर्ण __packed;

काष्ठा wlan_wow_stats अणु
	__le32 wow_pkt_dropped;
	__le16 wow_evt_discarded;
	u8 wow_host_pkt_wakeups;
	u8 wow_host_evt_wakeups;
पूर्ण __packed;

काष्ठा wmi_target_stats अणु
	__le32 lq_val;
	a_sle32 noise_न्यूनमान_calib;
	काष्ठा pm_stats pm_stats;
	काष्ठा wlan_net_stats stats;
	काष्ठा wlan_wow_stats wow_stats;
	काष्ठा arp_stats arp_stats;
	काष्ठा cserv_stats cserv_stats;
पूर्ण __packed;

/*
 * WMI_RSSI_THRESHOLD_EVENTID.
 * Indicate the RSSI events to host. Events are indicated when we breach a
 * thresold value.
 */
क्रमागत wmi_rssi_threshold_val अणु
	WMI_RSSI_THRESHOLD1_ABOVE = 0,
	WMI_RSSI_THRESHOLD2_ABOVE,
	WMI_RSSI_THRESHOLD3_ABOVE,
	WMI_RSSI_THRESHOLD4_ABOVE,
	WMI_RSSI_THRESHOLD5_ABOVE,
	WMI_RSSI_THRESHOLD6_ABOVE,
	WMI_RSSI_THRESHOLD1_BELOW,
	WMI_RSSI_THRESHOLD2_BELOW,
	WMI_RSSI_THRESHOLD3_BELOW,
	WMI_RSSI_THRESHOLD4_BELOW,
	WMI_RSSI_THRESHOLD5_BELOW,
	WMI_RSSI_THRESHOLD6_BELOW
पूर्ण;

काष्ठा wmi_rssi_threshold_event अणु
	a_sle16 rssi;
	u8 range;
पूर्ण __packed;

क्रमागत wmi_snr_threshold_val अणु
	WMI_SNR_THRESHOLD1_ABOVE = 1,
	WMI_SNR_THRESHOLD1_BELOW,
	WMI_SNR_THRESHOLD2_ABOVE,
	WMI_SNR_THRESHOLD2_BELOW,
	WMI_SNR_THRESHOLD3_ABOVE,
	WMI_SNR_THRESHOLD3_BELOW,
	WMI_SNR_THRESHOLD4_ABOVE,
	WMI_SNR_THRESHOLD4_BELOW
पूर्ण;

काष्ठा wmi_snr_threshold_event अणु
	/* see, क्रमागत wmi_snr_threshold_val */
	u8 range;

	u8 snr;
पूर्ण __packed;

/* WMI_REPORT_ROAM_TBL_EVENTID */
#घोषणा MAX_ROAM_TBL_CAND   5

काष्ठा wmi_bss_roam_info अणु
	a_sle32 roam_util;
	u8 bssid[ETH_ALEN];
	s8 rssi;
	s8 rssidt;
	s8 last_rssi;
	s8 util;
	s8 bias;

	/* क्रम alignment */
	u8 reserved;
पूर्ण __packed;

काष्ठा wmi_target_roam_tbl अणु
	__le16 roam_mode;
	__le16 num_entries;
	काष्ठा wmi_bss_roam_info info[];
पूर्ण __packed;

/* WMI_CAC_EVENTID */
क्रमागत cac_indication अणु
	CAC_INDICATION_ADMISSION = 0x00,
	CAC_INDICATION_ADMISSION_RESP = 0x01,
	CAC_INDICATION_DELETE = 0x02,
	CAC_INDICATION_NO_RESP = 0x03,
पूर्ण;

#घोषणा WMM_TSPEC_IE_LEN   63

काष्ठा wmi_cac_event अणु
	u8 ac;
	u8 cac_indication;
	u8 status_code;
	u8 tspec_suggestion[WMM_TSPEC_IE_LEN];
पूर्ण __packed;

/* WMI_APLIST_EVENTID */

क्रमागत aplist_ver अणु
	APLIST_VER1 = 1,
पूर्ण;

काष्ठा wmi_ap_info_v1 अणु
	u8 bssid[ETH_ALEN];
	__le16 channel;
पूर्ण __packed;

जोड़ wmi_ap_info अणु
	काष्ठा wmi_ap_info_v1 ap_info_v1;
पूर्ण __packed;

काष्ठा wmi_aplist_event अणु
	u8 ap_list_ver;
	u8 num_ap;
	जोड़ wmi_ap_info ap_list[1];
पूर्ण __packed;

/* Developer Commands */

/*
 * WMI_SET_BITRATE_CMDID
 *
 * Get bit rate cmd uses same definition as set bit rate cmd
 */
क्रमागत wmi_bit_rate अणु
	RATE_AUTO = -1,
	RATE_1Mb = 0,
	RATE_2Mb = 1,
	RATE_5_5Mb = 2,
	RATE_11Mb = 3,
	RATE_6Mb = 4,
	RATE_9Mb = 5,
	RATE_12Mb = 6,
	RATE_18Mb = 7,
	RATE_24Mb = 8,
	RATE_36Mb = 9,
	RATE_48Mb = 10,
	RATE_54Mb = 11,
	RATE_MCS_0_20 = 12,
	RATE_MCS_1_20 = 13,
	RATE_MCS_2_20 = 14,
	RATE_MCS_3_20 = 15,
	RATE_MCS_4_20 = 16,
	RATE_MCS_5_20 = 17,
	RATE_MCS_6_20 = 18,
	RATE_MCS_7_20 = 19,
	RATE_MCS_0_40 = 20,
	RATE_MCS_1_40 = 21,
	RATE_MCS_2_40 = 22,
	RATE_MCS_3_40 = 23,
	RATE_MCS_4_40 = 24,
	RATE_MCS_5_40 = 25,
	RATE_MCS_6_40 = 26,
	RATE_MCS_7_40 = 27,
पूर्ण;

काष्ठा wmi_bit_rate_reply अणु
	/* see, क्रमागत wmi_bit_rate */
	s8 rate_index;
पूर्ण __packed;

/*
 * WMI_SET_FIXRATES_CMDID
 *
 * Get fix rates cmd uses same definition as set fix rates cmd
 */
काष्ठा wmi_fix_rates_reply अणु
	/* see wmi_bit_rate */
	__le32 fix_rate_mask;
पूर्ण __packed;

क्रमागत roam_data_type अणु
	/* get the roam समय data */
	ROAM_DATA_TIME = 1,
पूर्ण;

काष्ठा wmi_target_roam_समय अणु
	__le32 disassoc_समय;
	__le32 no_txrx_समय;
	__le32 assoc_समय;
	__le32 allow_txrx_समय;
	u8 disassoc_bssid[ETH_ALEN];
	s8 disassoc_bss_rssi;
	u8 assoc_bssid[ETH_ALEN];
	s8 assoc_bss_rssi;
पूर्ण __packed;

क्रमागत wmi_txop_cfg अणु
	WMI_TXOP_DISABLED = 0,
	WMI_TXOP_ENABLED
पूर्ण;

काष्ठा wmi_set_wmm_txop_cmd अणु
	u8 txop_enable;
पूर्ण __packed;

काष्ठा wmi_set_keepalive_cmd अणु
	u8 keep_alive_पूर्णांकvl;
पूर्ण __packed;

काष्ठा wmi_get_keepalive_cmd अणु
	__le32 configured;
	u8 keep_alive_पूर्णांकvl;
पूर्ण __packed;

काष्ठा wmi_set_appie_cmd अणु
	u8 mgmt_frm_type; /* क्रमागत wmi_mgmt_frame_type */
	u8 ie_len;
	u8 ie_info[0];
पूर्ण __packed;

काष्ठा wmi_set_ie_cmd अणु
	u8 ie_id;
	u8 ie_field;	/* क्रमागत wmi_ie_field_type */
	u8 ie_len;
	u8 reserved;
	u8 ie_info[0];
पूर्ण __packed;

/* Notअगरy the WSC registration status to the target */
#घोषणा WSC_REG_ACTIVE     1
#घोषणा WSC_REG_INACTIVE   0

#घोषणा WOW_MAX_FILTERS_PER_LIST 4
#घोषणा WOW_PATTERN_SIZE	 64

#घोषणा MAC_MAX_FILTERS_PER_LIST 4

काष्ठा wow_filter अणु
	u8 wow_valid_filter;
	u8 wow_filter_id;
	u8 wow_filter_size;
	u8 wow_filter_offset;
	u8 wow_filter_mask[WOW_PATTERN_SIZE];
	u8 wow_filter_pattern[WOW_PATTERN_SIZE];
पूर्ण __packed;

#घोषणा MAX_IP_ADDRS  2

काष्ठा wmi_set_ip_cmd अणु
	/* IP in network byte order */
	__be32 ips[MAX_IP_ADDRS];
पूर्ण __packed;

क्रमागत ath6kl_wow_filters अणु
	WOW_FILTER_SSID			= BIT(1),
	WOW_FILTER_OPTION_MAGIC_PACKET  = BIT(2),
	WOW_FILTER_OPTION_EAP_REQ	= BIT(3),
	WOW_FILTER_OPTION_PATTERNS	= BIT(4),
	WOW_FILTER_OPTION_OFFLOAD_ARP	= BIT(5),
	WOW_FILTER_OPTION_OFFLOAD_NS	= BIT(6),
	WOW_FILTER_OPTION_OFFLOAD_GTK	= BIT(7),
	WOW_FILTER_OPTION_8021X_4WAYHS	= BIT(8),
	WOW_FILTER_OPTION_NLO_DISCVRY	= BIT(9),
	WOW_FILTER_OPTION_NWK_DISASSOC	= BIT(10),
	WOW_FILTER_OPTION_GTK_ERROR	= BIT(11),
	WOW_FILTER_OPTION_TEST_MODE	= BIT(15),
पूर्ण;

क्रमागत ath6kl_host_mode अणु
	ATH6KL_HOST_MODE_AWAKE,
	ATH6KL_HOST_MODE_ASLEEP,
पूर्ण;

काष्ठा wmi_set_host_sleep_mode_cmd अणु
	__le32 awake;
	__le32 asleep;
पूर्ण __packed;

क्रमागत ath6kl_wow_mode अणु
	ATH6KL_WOW_MODE_DISABLE,
	ATH6KL_WOW_MODE_ENABLE,
पूर्ण;

काष्ठा wmi_set_wow_mode_cmd अणु
	__le32 enable_wow;
	__le32 filter;
	__le16 host_req_delay;
पूर्ण __packed;

काष्ठा wmi_add_wow_pattern_cmd अणु
	u8 filter_list_id;
	u8 filter_size;
	u8 filter_offset;
	u8 filter[0];
पूर्ण __packed;

काष्ठा wmi_del_wow_pattern_cmd अणु
	__le16 filter_list_id;
	__le16 filter_id;
पूर्ण __packed;

/* WMI_SET_TXE_NOTIFY_CMDID */
काष्ठा wmi_txe_notअगरy_cmd अणु
	__le32 rate;
	__le32 pkts;
	__le32 पूर्णांकvl;
पूर्ण __packed;

/* WMI_TXE_NOTIFY_EVENTID */
काष्ठा wmi_txe_notअगरy_event अणु
	__le32 rate;
	__le32 pkts;
पूर्ण __packed;

/* WMI_SET_AKMP_PARAMS_CMD */

काष्ठा wmi_pmkid अणु
	u8 pmkid[WMI_PMKID_LEN];
पूर्ण __packed;

/* WMI_GET_PMKID_LIST_CMD  Reply */
काष्ठा wmi_pmkid_list_reply अणु
	__le32 num_pmkid;
	u8 bssid_list[ETH_ALEN][1];
	काष्ठा wmi_pmkid pmkid_list[1];
पूर्ण __packed;

/* WMI_ADDBA_REQ_EVENTID */
काष्ठा wmi_addba_req_event अणु
	u8 tid;
	u8 win_sz;
	__le16 st_seq_no;

	/* f/w response क्रम ADDBA Req; OK (0) or failure (!=0) */
	u8 status;
पूर्ण __packed;

/* WMI_ADDBA_RESP_EVENTID */
काष्ठा wmi_addba_resp_event अणु
	u8 tid;

	/* OK (0), failure (!=0) */
	u8 status;

	/* three values: not supported(0), 3839, 8k */
	__le16 amsdu_sz;
पूर्ण __packed;

/* WMI_DELBA_EVENTID
 * f/w received a DELBA क्रम peer and processed it.
 * Host is notअगरied of this
 */
काष्ठा wmi_delba_event अणु
	u8 tid;
	u8 is_peer_initiator;
	__le16 reason_code;
पूर्ण __packed;

#घोषणा PEER_NODE_JOIN_EVENT		0x00
#घोषणा PEER_NODE_LEAVE_EVENT		0x01
#घोषणा PEER_FIRST_NODE_JOIN_EVENT	0x10
#घोषणा PEER_LAST_NODE_LEAVE_EVENT	0x11

काष्ठा wmi_peer_node_event अणु
	u8 event_code;
	u8 peer_mac_addr[ETH_ALEN];
पूर्ण __packed;

/* Transmit complete event data काष्ठाure(s) */

/* version 1 of tx complete msg */
काष्ठा tx_complete_msg_v1 अणु
#घोषणा TX_COMPLETE_STATUS_SUCCESS 0
#घोषणा TX_COMPLETE_STATUS_RETRIES 1
#घोषणा TX_COMPLETE_STATUS_NOLINK  2
#घोषणा TX_COMPLETE_STATUS_TIMEOUT 3
#घोषणा TX_COMPLETE_STATUS_OTHER   4

	u8 status;

	/* packet ID to identअगरy parent packet */
	u8 pkt_id;

	/* rate index on successful transmission */
	u8 rate_idx;

	/* number of ACK failures in tx attempt */
	u8 ack_failures;
पूर्ण __packed;

काष्ठा wmi_tx_complete_event अणु
	/* no of tx comp msgs following this काष्ठा */
	u8 num_msg;

	/* length in bytes क्रम each inभागidual msg following this काष्ठा */
	u8 msg_len;

	/* version of tx complete msg data following this काष्ठा */
	u8 msg_type;

	/* inभागidual messages follow this header */
	u8 reserved;
पूर्ण __packed;

/*
 * ------- AP Mode definitions --------------
 */

/*
 * !!! Warning !!!
 * -Changing the following values needs compilation of both driver and firmware
 */
#घोषणा AP_MAX_NUM_STA          10

/* Spl. AID used to set DTIM flag in the beacons */
#घोषणा MCAST_AID               0xFF

#घोषणा DEF_AP_COUNTRY_CODE     "US "

/* Used with WMI_AP_SET_NUM_STA_CMDID */

/*
 * Used with WMI_AP_SET_MLME_CMDID
 */

/* MLME Commands */
#घोषणा WMI_AP_MLME_ASSOC       1   /* associate station */
#घोषणा WMI_AP_DISASSOC         2   /* disassociate station */
#घोषणा WMI_AP_DEAUTH           3   /* deauthenticate station */
#घोषणा WMI_AP_MLME_AUTHORIZE   4   /* authorize station */
#घोषणा WMI_AP_MLME_UNAUTHORIZE 5   /* unauthorize station */

काष्ठा wmi_ap_set_mlme_cmd अणु
	u8 mac[ETH_ALEN];
	__le16 reason;		/* 802.11 reason code */
	u8 cmd;			/* operation to perक्रमm (WMI_AP_*) */
पूर्ण __packed;

काष्ठा wmi_ap_set_pvb_cmd अणु
	__le32 flag;
	__le16 rsvd;
	__le16 aid;
पूर्ण __packed;

काष्ठा wmi_rx_frame_क्रमmat_cmd अणु
	/* version of meta data क्रम rx packets <0 = शेष> (0-7 = valid) */
	u8 meta_ver;

	/*
	 * 1 == leave .11 header पूर्णांकact,
	 * 0 == replace .11 header with .3 <शेष>
	 */
	u8 करोt11_hdr;

	/*
	 * 1 == defragmentation is perक्रमmed by host,
	 * 0 == perक्रमmed by target <शेष>
	 */
	u8 defrag_on_host;

	/* क्रम alignment */
	u8 reserved[1];
पूर्ण __packed;

काष्ठा wmi_ap_hidden_ssid_cmd अणु
	u8 hidden_ssid;
पूर्ण __packed;

काष्ठा wmi_set_inact_period_cmd अणु
	__le32 inact_period;
	u8 num_null_func;
पूर्ण __packed;

/* AP mode events */
काष्ठा wmi_ap_set_apsd_cmd अणु
	u8 enable;
पूर्ण __packed;

क्रमागत wmi_ap_apsd_buffered_traffic_flags अणु
	WMI_AP_APSD_NO_DELIVERY_FRAMES =  0x1,
पूर्ण;

काष्ठा wmi_ap_apsd_buffered_traffic_cmd अणु
	__le16 aid;
	__le16 biपंचांगap;
	__le32 flags;
पूर्ण __packed;

/* WMI_PS_POLL_EVENT */
काष्ठा wmi_pspoll_event अणु
	__le16 aid;
पूर्ण __packed;

काष्ठा wmi_per_sta_stat अणु
	__le32 tx_bytes;
	__le32 tx_pkts;
	__le32 tx_error;
	__le32 tx_discard;
	__le32 rx_bytes;
	__le32 rx_pkts;
	__le32 rx_error;
	__le32 rx_discard;
	__le32 aid;
पूर्ण __packed;

काष्ठा wmi_ap_mode_stat अणु
	__le32 action;
	काष्ठा wmi_per_sta_stat sta[AP_MAX_NUM_STA + 1];
पूर्ण __packed;

/* End of AP mode definitions */

काष्ठा wmi_reमुख्य_on_chnl_cmd अणु
	__le32 freq;
	__le32 duration;
पूर्ण __packed;

/* wmi_send_action_cmd is to be deprecated. Use
 * wmi_send_mgmt_cmd instead. The new काष्ठाure supports P2P mgmt
 * operations using station पूर्णांकerface.
 */
काष्ठा wmi_send_action_cmd अणु
	__le32 id;
	__le32 freq;
	__le32 रुको;
	__le16 len;
	u8 data[0];
पूर्ण __packed;

काष्ठा wmi_send_mgmt_cmd अणु
	__le32 id;
	__le32 freq;
	__le32 रुको;
	__le32 no_cck;
	__le16 len;
	u8 data[0];
पूर्ण __packed;

काष्ठा wmi_tx_status_event अणु
	__le32 id;
	u8 ack_status;
पूर्ण __packed;

काष्ठा wmi_probe_req_report_cmd अणु
	u8 enable;
पूर्ण __packed;

काष्ठा wmi_disable_11b_rates_cmd अणु
	u8 disable;
पूर्ण __packed;

काष्ठा wmi_set_appie_extended_cmd अणु
	u8 role_id;
	u8 mgmt_frm_type;
	u8 ie_len;
	u8 ie_info[0];
पूर्ण __packed;

काष्ठा wmi_reमुख्य_on_chnl_event अणु
	__le32 freq;
	__le32 duration;
पूर्ण __packed;

काष्ठा wmi_cancel_reमुख्य_on_chnl_event अणु
	__le32 freq;
	__le32 duration;
	u8 status;
पूर्ण __packed;

काष्ठा wmi_rx_action_event अणु
	__le32 freq;
	__le16 len;
	u8 data[0];
पूर्ण __packed;

काष्ठा wmi_p2p_capabilities_event अणु
	__le16 len;
	u8 data[0];
पूर्ण __packed;

काष्ठा wmi_p2p_rx_probe_req_event अणु
	__le32 freq;
	__le16 len;
	u8 data[0];
पूर्ण __packed;

#घोषणा P2P_FLAG_CAPABILITIES_REQ   (0x00000001)
#घोषणा P2P_FLAG_MACADDR_REQ        (0x00000002)
#घोषणा P2P_FLAG_HMODEL_REQ         (0x00000002)

काष्ठा wmi_get_p2p_info अणु
	__le32 info_req_flags;
पूर्ण __packed;

काष्ठा wmi_p2p_info_event अणु
	__le32 info_req_flags;
	__le16 len;
	u8 data[0];
पूर्ण __packed;

काष्ठा wmi_p2p_capabilities अणु
	u8 go_घातer_save;
पूर्ण __packed;

काष्ठा wmi_p2p_macaddr अणु
	u8 mac_addr[ETH_ALEN];
पूर्ण __packed;

काष्ठा wmi_p2p_hmodel अणु
	u8 p2p_model;
पूर्ण __packed;

काष्ठा wmi_p2p_probe_response_cmd अणु
	__le32 freq;
	u8 destination_addr[ETH_ALEN];
	__le16 len;
	u8 data[0];
पूर्ण __packed;

/* Extended WMI (WMIX)
 *
 * Extended WMIX commands are encapsulated in a WMI message with
 * cmd=WMI_EXTENSION_CMD.
 *
 * Extended WMI commands are those that are needed during wireless
 * operation, but which are not really wireless commands.  This allows,
 * क्रम instance, platक्रमm-specअगरic commands.  Extended WMI commands are
 * embedded in a WMI command message with WMI_COMMAND_ID=WMI_EXTENSION_CMDID.
 * Extended WMI events are similarly embedded in a WMI event message with
 * WMI_EVENT_ID=WMI_EXTENSION_EVENTID.
 */
काष्ठा wmix_cmd_hdr अणु
	__le32 cmd_id;
पूर्ण __packed;

क्रमागत wmix_command_id अणु
	WMIX_DSETOPEN_REPLY_CMDID = 0x2001,
	WMIX_DSETDATA_REPLY_CMDID,
	WMIX_GPIO_OUTPUT_SET_CMDID,
	WMIX_GPIO_INPUT_GET_CMDID,
	WMIX_GPIO_REGISTER_SET_CMDID,
	WMIX_GPIO_REGISTER_GET_CMDID,
	WMIX_GPIO_INTR_ACK_CMDID,
	WMIX_HB_CHALLENGE_RESP_CMDID,
	WMIX_DBGLOG_CFG_MODULE_CMDID,
	WMIX_PROF_CFG_CMDID,	/* 0x200a */
	WMIX_PROF_ADDR_SET_CMDID,
	WMIX_PROF_START_CMDID,
	WMIX_PROF_STOP_CMDID,
	WMIX_PROF_COUNT_GET_CMDID,
पूर्ण;

क्रमागत wmix_event_id अणु
	WMIX_DSETOPENREQ_EVENTID = 0x3001,
	WMIX_DSETCLOSE_EVENTID,
	WMIX_DSETDATAREQ_EVENTID,
	WMIX_GPIO_INTR_EVENTID,
	WMIX_GPIO_DATA_EVENTID,
	WMIX_GPIO_ACK_EVENTID,
	WMIX_HB_CHALLENGE_RESP_EVENTID,
	WMIX_DBGLOG_EVENTID,
	WMIX_PROF_COUNT_EVENTID,
पूर्ण;

/*
 * ------Error Detection support-------
 */

/*
 * WMIX_HB_CHALLENGE_RESP_CMDID
 * Heartbeat Challenge Response command
 */
काष्ठा wmix_hb_challenge_resp_cmd अणु
	__le32 cookie;
	__le32 source;
पूर्ण __packed;

काष्ठा ath6kl_wmix_dbglog_cfg_module_cmd अणु
	__le32 valid;
	__le32 config;
पूर्ण __packed;

/* End of Extended WMI (WMIX) */

क्रमागत wmi_sync_flag अणु
	NO_SYNC_WMIFLAG = 0,

	/* transmit all queued data beक्रमe cmd */
	SYNC_BEFORE_WMIFLAG,

	/* any new data रुकोs until cmd execs */
	SYNC_AFTER_WMIFLAG,

	SYNC_BOTH_WMIFLAG,

	/* end marker */
	END_WMIFLAG
पूर्ण;

क्रमागत htc_endpoपूर्णांक_id ath6kl_wmi_get_control_ep(काष्ठा wmi *wmi);
व्योम ath6kl_wmi_set_control_ep(काष्ठा wmi *wmi, क्रमागत htc_endpoपूर्णांक_id ep_id);
पूर्णांक ath6kl_wmi_dix_2_करोt3(काष्ठा wmi *wmi, काष्ठा sk_buff *skb);
पूर्णांक ath6kl_wmi_data_hdr_add(काष्ठा wmi *wmi, काष्ठा sk_buff *skb,
			    u8 msg_type, u32 flags,
			    क्रमागत wmi_data_hdr_data_type data_type,
			    u8 meta_ver, व्योम *tx_meta_info, u8 अगर_idx);

पूर्णांक ath6kl_wmi_करोt11_hdr_हटाओ(काष्ठा wmi *wmi, काष्ठा sk_buff *skb);
पूर्णांक ath6kl_wmi_करोt3_2_dix(काष्ठा sk_buff *skb);
पूर्णांक ath6kl_wmi_implicit_create_pstream(काष्ठा wmi *wmi, u8 अगर_idx,
				       काष्ठा sk_buff *skb, u32 layer2_priority,
				       bool wmm_enabled, u8 *ac);

पूर्णांक ath6kl_wmi_control_rx(काष्ठा wmi *wmi, काष्ठा sk_buff *skb);

पूर्णांक ath6kl_wmi_cmd_send(काष्ठा wmi *wmi, u8 अगर_idx, काष्ठा sk_buff *skb,
			क्रमागत wmi_cmd_id cmd_id, क्रमागत wmi_sync_flag sync_flag);

पूर्णांक ath6kl_wmi_connect_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			   क्रमागत network_type nw_type,
			   क्रमागत करोt11_auth_mode करोt11_auth_mode,
			   क्रमागत auth_mode auth_mode,
			   क्रमागत ath6kl_crypto_type pairwise_crypto,
			   u8 pairwise_crypto_len,
			   क्रमागत ath6kl_crypto_type group_crypto,
			   u8 group_crypto_len, पूर्णांक ssid_len, u8 *ssid,
			   u8 *bssid, u16 channel, u32 ctrl_flags,
			   u8 nw_subtype);

पूर्णांक ath6kl_wmi_reconnect_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 *bssid,
			     u16 channel);
पूर्णांक ath6kl_wmi_disconnect_cmd(काष्ठा wmi *wmi, u8 अगर_idx);

पूर्णांक ath6kl_wmi_beginscan_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			     क्रमागत wmi_scan_type scan_type,
			     u32 क्रमce_fgscan, u32 is_legacy,
			     u32 home_dwell_समय, u32 क्रमce_scan_पूर्णांकerval,
			     s8 num_chan, u16 *ch_list, u32 no_cck,
			     u32 *rates);
पूर्णांक ath6kl_wmi_enable_sched_scan_cmd(काष्ठा wmi *wmi, u8 अगर_idx, bool enable);

पूर्णांक ath6kl_wmi_scanparams_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u16 fg_start_sec,
			      u16 fg_end_sec, u16 bg_sec,
			      u16 minact_chdw_msec, u16 maxact_chdw_msec,
			      u16 pas_chdw_msec, u8 लघु_scan_ratio,
			      u8 scan_ctrl_flag, u32 max_dfsch_act_समय,
			      u16 maxact_scan_per_ssid);
पूर्णांक ath6kl_wmi_bssfilter_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 filter,
			     u32 ie_mask);
पूर्णांक ath6kl_wmi_probedssid_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 index, u8 flag,
			      u8 ssid_len, u8 *ssid);
पूर्णांक ath6kl_wmi_listenपूर्णांकerval_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				  u16 listen_पूर्णांकerval,
				  u16 listen_beacons);
पूर्णांक ath6kl_wmi_bmissसमय_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			     u16 bmiss_समय, u16 num_beacons);
पूर्णांक ath6kl_wmi_घातermode_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 pwr_mode);
पूर्णांक ath6kl_wmi_pmparams_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u16 idle_period,
			    u16 ps_poll_num, u16 dtim_policy,
			    u16 tx_wakup_policy, u16 num_tx_to_wakeup,
			    u16 ps_fail_event_policy);
पूर्णांक ath6kl_wmi_create_pstream_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				  काष्ठा wmi_create_pstream_cmd *pstream);
पूर्णांक ath6kl_wmi_delete_pstream_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 traffic_class,
				  u8 tsid);
पूर्णांक ath6kl_wmi_disस_समयout_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 समयout);

पूर्णांक ath6kl_wmi_set_rts_cmd(काष्ठा wmi *wmi, u16 threshold);
पूर्णांक ath6kl_wmi_set_lpreamble_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 status,
				 u8 preamble_policy);

पूर्णांक ath6kl_wmi_get_challenge_resp_cmd(काष्ठा wmi *wmi, u32 cookie, u32 source);
पूर्णांक ath6kl_wmi_config_debug_module_cmd(काष्ठा wmi *wmi, u32 valid, u32 config);

पूर्णांक ath6kl_wmi_get_stats_cmd(काष्ठा wmi *wmi, u8 अगर_idx);
पूर्णांक ath6kl_wmi_addkey_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 key_index,
			  क्रमागत ath6kl_crypto_type key_type,
			  u8 key_usage, u8 key_len,
			  u8 *key_rsc, अचिन्हित पूर्णांक key_rsc_len,
			  u8 *key_material,
			  u8 key_op_ctrl, u8 *mac_addr,
			  क्रमागत wmi_sync_flag sync_flag);
पूर्णांक ath6kl_wmi_add_krk_cmd(काष्ठा wmi *wmi, u8 अगर_idx, स्थिर u8 *krk);
पूर्णांक ath6kl_wmi_deletekey_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 key_index);
पूर्णांक ath6kl_wmi_setpmkid_cmd(काष्ठा wmi *wmi, u8 अगर_idx, स्थिर u8 *bssid,
			    स्थिर u8 *pmkid, bool set);
पूर्णांक ath6kl_wmi_set_tx_pwr_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 dbM);
पूर्णांक ath6kl_wmi_get_tx_pwr_cmd(काष्ठा wmi *wmi, u8 अगर_idx);
पूर्णांक ath6kl_wmi_get_roam_tbl_cmd(काष्ठा wmi *wmi);

पूर्णांक ath6kl_wmi_set_wmm_txop(काष्ठा wmi *wmi, u8 अगर_idx, क्रमागत wmi_txop_cfg cfg);
पूर्णांक ath6kl_wmi_set_keepalive_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				 u8 keep_alive_पूर्णांकvl);
पूर्णांक ath6kl_wmi_set_htcap_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			     क्रमागत nl80211_band band,
			     काष्ठा ath6kl_htcap *htcap);
पूर्णांक ath6kl_wmi_test_cmd(काष्ठा wmi *wmi, व्योम *buf, माप_प्रकार len);

s32 ath6kl_wmi_get_rate(काष्ठा wmi *wmi, s8 rate_index);

पूर्णांक ath6kl_wmi_set_ip_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
			  __be32 ips0, __be32 ips1);
पूर्णांक ath6kl_wmi_set_host_sleep_mode_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				       क्रमागत ath6kl_host_mode host_mode);
पूर्णांक ath6kl_wmi_set_bitrate_mask(काष्ठा wmi *wmi, u8 अगर_idx,
				स्थिर काष्ठा cfg80211_bitrate_mask *mask);
पूर्णांक ath6kl_wmi_set_wow_mode_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				क्रमागत ath6kl_wow_mode wow_mode,
				u32 filter, u16 host_req_delay);
पूर्णांक ath6kl_wmi_add_wow_pattern_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				   u8 list_id, u8 filter_size,
				   u8 filter_offset, स्थिर u8 *filter,
				   स्थिर u8 *mask);
पूर्णांक ath6kl_wmi_del_wow_pattern_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				   u16 list_id, u16 filter_id);
पूर्णांक ath6kl_wmi_set_rssi_filter_cmd(काष्ठा wmi *wmi, u8 अगर_idx, s8 rssi);
पूर्णांक ath6kl_wmi_set_roam_lrssi_cmd(काष्ठा wmi *wmi, u8 lrssi);
पूर्णांक ath6kl_wmi_ap_set_dtim_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 dtim_period);
पूर्णांक ath6kl_wmi_ap_set_beacon_पूर्णांकvl_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				       u32 beacon_पूर्णांकerval);
पूर्णांक ath6kl_wmi_क्रमce_roam_cmd(काष्ठा wmi *wmi, स्थिर u8 *bssid);
पूर्णांक ath6kl_wmi_set_roam_mode_cmd(काष्ठा wmi *wmi, क्रमागत wmi_roam_mode mode);
पूर्णांक ath6kl_wmi_mcast_filter_cmd(काष्ठा wmi *wmi, u8 अगर_idx, bool mc_all_on);
पूर्णांक ath6kl_wmi_add_del_mcast_filter_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
					u8 *filter, bool add_filter);
पूर्णांक ath6kl_wmi_sta_bmiss_enhance_cmd(काष्ठा wmi *wmi, u8 अगर_idx, bool enable);
पूर्णांक ath6kl_wmi_set_txe_notअगरy(काष्ठा wmi *wmi, u8 idx,
			      u32 rate, u32 pkts, u32 पूर्णांकvl);
पूर्णांक ath6kl_wmi_set_regकरोमुख्य_cmd(काष्ठा wmi *wmi, स्थिर अक्षर *alpha2);

/* AP mode uAPSD */
पूर्णांक ath6kl_wmi_ap_set_apsd(काष्ठा wmi *wmi, u8 अगर_idx, u8 enable);

पूर्णांक ath6kl_wmi_set_apsd_bfrd_traf(काष्ठा wmi *wmi,
						u8 अगर_idx, u16 aid,
						u16 biपंचांगap, u32 flags);

u8 ath6kl_wmi_get_traffic_class(u8 user_priority);

u8 ath6kl_wmi_determine_user_priority(u8 *pkt, u32 layer2_pri);
/* AP mode */
पूर्णांक ath6kl_wmi_ap_hidden_ssid(काष्ठा wmi *wmi, u8 अगर_idx, bool enable);
पूर्णांक ath6kl_wmi_ap_profile_commit(काष्ठा wmi *wmip, u8 अगर_idx,
				 काष्ठा wmi_connect_cmd *p);

पूर्णांक ath6kl_wmi_ap_set_mlme(काष्ठा wmi *wmip, u8 अगर_idx, u8 cmd,
			   स्थिर u8 *mac, u16 reason);

पूर्णांक ath6kl_wmi_set_pvb_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u16 aid, bool flag);

पूर्णांक ath6kl_wmi_set_rx_frame_क्रमmat_cmd(काष्ठा wmi *wmi, u8 अगर_idx,
				       u8 rx_meta_version,
				       bool rx_करोt11_hdr, bool defrag_on_host);

पूर्णांक ath6kl_wmi_set_appie_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 mgmt_frm_type,
			     स्थिर u8 *ie, u8 ie_len);

पूर्णांक ath6kl_wmi_set_ie_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 ie_id, u8 ie_field,
			  स्थिर u8 *ie_info, u8 ie_len);

/* P2P */
पूर्णांक ath6kl_wmi_disable_11b_rates_cmd(काष्ठा wmi *wmi, bool disable);

पूर्णांक ath6kl_wmi_reमुख्य_on_chnl_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 freq,
				  u32 dur);

पूर्णांक ath6kl_wmi_send_mgmt_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 id, u32 freq,
			       u32 रुको, स्थिर u8 *data, u16 data_len,
			       u32 no_cck);

पूर्णांक ath6kl_wmi_send_probe_response_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 freq,
				       स्थिर u8 *dst, स्थिर u8 *data,
				       u16 data_len);

पूर्णांक ath6kl_wmi_probe_report_req_cmd(काष्ठा wmi *wmi, u8 अगर_idx, bool enable);

पूर्णांक ath6kl_wmi_info_req_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u32 info_req_flags);

पूर्णांक ath6kl_wmi_cancel_reमुख्य_on_chnl_cmd(काष्ठा wmi *wmi, u8 अगर_idx);

पूर्णांक ath6kl_wmi_set_appie_cmd(काष्ठा wmi *wmi, u8 अगर_idx, u8 mgmt_frm_type,
			     स्थिर u8 *ie, u8 ie_len);

पूर्णांक ath6kl_wmi_set_inact_period(काष्ठा wmi *wmi, u8 अगर_idx, पूर्णांक inact_समयout);

व्योम ath6kl_wmi_sscan_समयr(काष्ठा समयr_list *t);

पूर्णांक ath6kl_wmi_get_challenge_resp_cmd(काष्ठा wmi *wmi, u32 cookie, u32 source);

काष्ठा ath6kl_vअगर *ath6kl_get_vअगर_by_index(काष्ठा ath6kl *ar, u8 अगर_idx);
व्योम *ath6kl_wmi_init(काष्ठा ath6kl *devt);
व्योम ath6kl_wmi_shutकरोwn(काष्ठा wmi *wmi);
व्योम ath6kl_wmi_reset(काष्ठा wmi *wmi);

#पूर्ण_अगर /* WMI_H */
