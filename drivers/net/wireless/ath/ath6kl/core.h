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

#अगर_अघोषित CORE_H
#घोषणा CORE_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/firmware.h>
#समावेश <linux/sched.h>
#समावेश <linux/circ_buf.h>
#समावेश <net/cfg80211.h>
#समावेश "htc.h"
#समावेश "wmi.h"
#समावेश "bmi.h"
#समावेश "target.h"

#घोषणा MAX_ATH6KL                        1
#घोषणा ATH6KL_MAX_RX_BUFFERS             16
#घोषणा ATH6KL_BUFFER_SIZE                1664
#घोषणा ATH6KL_MAX_AMSDU_RX_BUFFERS       4
#घोषणा ATH6KL_AMSDU_REFILL_THRESHOLD     3
#घोषणा ATH6KL_AMSDU_BUFFER_SIZE     (WMI_MAX_AMSDU_RX_DATA_FRAME_LENGTH + 128)
#घोषणा MAX_MSDU_SUBFRAME_PAYLOAD_LEN	1508
#घोषणा MIN_MSDU_SUBFRAME_PAYLOAD_LEN	46

#घोषणा USER_SAVEDKEYS_STAT_INIT     0
#घोषणा USER_SAVEDKEYS_STAT_RUN      1

#घोषणा ATH6KL_TX_TIMEOUT      10
#घोषणा ATH6KL_MAX_ENDPOINTS   4
#घोषणा MAX_NODE_NUM           15

#घोषणा ATH6KL_APSD_ALL_FRAME		0xFFFF
#घोषणा ATH6KL_APSD_NUM_OF_AC		0x4
#घोषणा ATH6KL_APSD_FRAME_MASK		0xF

/* Extra bytes क्रम htc header alignment */
#घोषणा ATH6KL_HTC_ALIGN_BYTES 3

/* MAX_HI_COOKIE_NUM are reserved क्रम high priority traffic */
#घोषणा MAX_DEF_COOKIE_NUM                180
#घोषणा MAX_HI_COOKIE_NUM                 18	/* 10% of MAX_COOKIE_NUM */
#घोषणा MAX_COOKIE_NUM                 (MAX_DEF_COOKIE_NUM + MAX_HI_COOKIE_NUM)

#घोषणा MAX_DEFAULT_SEND_QUEUE_DEPTH      (MAX_DEF_COOKIE_NUM / WMM_NUM_AC)

#घोषणा DISCON_TIMER_INTVAL               10000  /* in msec */

/* Channel dwell समय in fg scan */
#घोषणा ATH6KL_FG_SCAN_INTERVAL		50 /* in ms */

/* includes also the null byte */
#घोषणा ATH6KL_FIRMWARE_MAGIC               "QCA-ATH6KL"

क्रमागत ath6kl_fw_ie_type अणु
	ATH6KL_FW_IE_FW_VERSION = 0,
	ATH6KL_FW_IE_TIMESTAMP = 1,
	ATH6KL_FW_IE_OTP_IMAGE = 2,
	ATH6KL_FW_IE_FW_IMAGE = 3,
	ATH6KL_FW_IE_PATCH_IMAGE = 4,
	ATH6KL_FW_IE_RESERVED_RAM_SIZE = 5,
	ATH6KL_FW_IE_CAPABILITIES = 6,
	ATH6KL_FW_IE_PATCH_ADDR = 7,
	ATH6KL_FW_IE_BOARD_ADDR = 8,
	ATH6KL_FW_IE_VIF_MAX = 9,
पूर्ण;

क्रमागत ath6kl_fw_capability अणु
	ATH6KL_FW_CAPABILITY_HOST_P2P = 0,
	ATH6KL_FW_CAPABILITY_SCHED_SCAN = 1,

	/*
	 * Firmware is capable of supporting P2P mgmt operations on a
	 * station पूर्णांकerface. After group क्रमmation, the station
	 * पूर्णांकerface will become a P2P client/GO पूर्णांकerface as the हाल may be
	 */
	ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX,

	/*
	 * Firmware has support to cleanup inactive stations
	 * in AP mode.
	 */
	ATH6KL_FW_CAPABILITY_INACTIVITY_TIMEOUT,

	/* Firmware has support to override rsn cap of rsn ie */
	ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE,

	/*
	 * Multicast support in WOW and host awake mode.
	 * Allow all multicast in host awake mode.
	 * Apply multicast filter in WOW mode.
	 */
	ATH6KL_FW_CAPABILITY_WOW_MULTICAST_FILTER,

	/* Firmware supports enhanced bmiss detection */
	ATH6KL_FW_CAPABILITY_BMISS_ENHANCE,

	/*
	 * FW supports matching of ssid in schedule scan
	 */
	ATH6KL_FW_CAPABILITY_SCHED_SCAN_MATCH_LIST,

	/* Firmware supports filtering BSS results by RSSI */
	ATH6KL_FW_CAPABILITY_RSSI_SCAN_THOLD,

	/* FW sets mac_addr[4] ^= 0x80 क्रम newly created पूर्णांकerfaces */
	ATH6KL_FW_CAPABILITY_CUSTOM_MAC_ADDR,

	/* Firmware supports TX error rate notअगरication */
	ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY,

	/* supports WMI_SET_REGDOMAIN_CMDID command */
	ATH6KL_FW_CAPABILITY_REGDOMAIN,

	/* Firmware supports sched scan decoupled from host sleep */
	ATH6KL_FW_CAPABILITY_SCHED_SCAN_V2,

	/*
	 * Firmware capability क्रम hang detection through heart beat
	 * challenge messages.
	 */
	ATH6KL_FW_CAPABILITY_HEART_BEAT_POLL,

	/* WMI_SET_TX_SELECT_RATES_CMDID uses 64 bit size rate table */
	ATH6KL_FW_CAPABILITY_64BIT_RATES,

	/* WMI_AP_CONN_INACT_CMDID uses minutes as units */
	ATH6KL_FW_CAPABILITY_AP_INACTIVITY_MINS,

	/* use low priority endpoपूर्णांक क्रम all data */
	ATH6KL_FW_CAPABILITY_MAP_LP_ENDPOINT,

	/* ratetable is the 2 stream version (max MCS15) */
	ATH6KL_FW_CAPABILITY_RATETABLE_MCS15,

	/* firmware करोesn't support IP checksumming */
	ATH6KL_FW_CAPABILITY_NO_IP_CHECKSUM,

	/* this needs to be last */
	ATH6KL_FW_CAPABILITY_MAX,
पूर्ण;

#घोषणा ATH6KL_CAPABILITY_LEN (ALIGN(ATH6KL_FW_CAPABILITY_MAX, 32) / 32)

काष्ठा ath6kl_fw_ie अणु
	__le32 id;
	__le32 len;
	u8 data[];
पूर्ण;

क्रमागत ath6kl_hw_flags अणु
	ATH6KL_HW_SDIO_CRC_ERROR_WAR	= BIT(3),
पूर्ण;

#घोषणा ATH6KL_FW_API2_खाता "fw-2.bin"
#घोषणा ATH6KL_FW_API3_खाता "fw-3.bin"
#घोषणा ATH6KL_FW_API4_खाता "fw-4.bin"
#घोषणा ATH6KL_FW_API5_खाता "fw-5.bin"

/* AR6003 1.0 definitions */
#घोषणा AR6003_HW_1_0_VERSION                 0x300002ba

/* AR6003 2.0 definitions */
#घोषणा AR6003_HW_2_0_VERSION                 0x30000384
#घोषणा AR6003_HW_2_0_PATCH_DOWNLOAD_ADDRESS  0x57e910
#घोषणा AR6003_HW_2_0_FW_सूची			"ath6k/AR6003/hw2.0"
#घोषणा AR6003_HW_2_0_OTP_खाता			"otp.bin.z77"
#घोषणा AR6003_HW_2_0_FIRMWARE_खाता		"athwlan.bin.z77"
#घोषणा AR6003_HW_2_0_TCMD_FIRMWARE_खाता	"athtcmd_ram.bin"
#घोषणा AR6003_HW_2_0_PATCH_खाता		"data.patch.bin"
#घोषणा AR6003_HW_2_0_BOARD_DATA_खाता AR6003_HW_2_0_FW_सूची "/bdata.bin"
#घोषणा AR6003_HW_2_0_DEFAULT_BOARD_DATA_खाता \
			AR6003_HW_2_0_FW_सूची "/bdata.SD31.bin"

/* AR6003 3.0 definitions */
#घोषणा AR6003_HW_2_1_1_VERSION                 0x30000582
#घोषणा AR6003_HW_2_1_1_FW_सूची			"ath6k/AR6003/hw2.1.1"
#घोषणा AR6003_HW_2_1_1_OTP_खाता		"otp.bin"
#घोषणा AR6003_HW_2_1_1_FIRMWARE_खाता		"athwlan.bin"
#घोषणा AR6003_HW_2_1_1_TCMD_FIRMWARE_खाता	"athtcmd_ram.bin"
#घोषणा AR6003_HW_2_1_1_UTF_FIRMWARE_खाता	"utf.bin"
#घोषणा AR6003_HW_2_1_1_TESTSCRIPT_खाता	"nullTestFlow.bin"
#घोषणा AR6003_HW_2_1_1_PATCH_खाता		"data.patch.bin"
#घोषणा AR6003_HW_2_1_1_BOARD_DATA_खाता AR6003_HW_2_1_1_FW_सूची "/bdata.bin"
#घोषणा AR6003_HW_2_1_1_DEFAULT_BOARD_DATA_खाता	\
			AR6003_HW_2_1_1_FW_सूची "/bdata.SD31.bin"

/* AR6004 1.0 definitions */
#घोषणा AR6004_HW_1_0_VERSION                 0x30000623
#घोषणा AR6004_HW_1_0_FW_सूची			"ath6k/AR6004/hw1.0"
#घोषणा AR6004_HW_1_0_FIRMWARE_खाता		"fw.ram.bin"
#घोषणा AR6004_HW_1_0_BOARD_DATA_खाता         AR6004_HW_1_0_FW_सूची "/bdata.bin"
#घोषणा AR6004_HW_1_0_DEFAULT_BOARD_DATA_खाता \
	AR6004_HW_1_0_FW_सूची "/bdata.DB132.bin"

/* AR6004 1.1 definitions */
#घोषणा AR6004_HW_1_1_VERSION                 0x30000001
#घोषणा AR6004_HW_1_1_FW_सूची			"ath6k/AR6004/hw1.1"
#घोषणा AR6004_HW_1_1_FIRMWARE_खाता		"fw.ram.bin"
#घोषणा AR6004_HW_1_1_BOARD_DATA_खाता         AR6004_HW_1_1_FW_सूची "/bdata.bin"
#घोषणा AR6004_HW_1_1_DEFAULT_BOARD_DATA_खाता \
	AR6004_HW_1_1_FW_सूची "/bdata.DB132.bin"

/* AR6004 1.2 definitions */
#घोषणा AR6004_HW_1_2_VERSION                 0x300007e8
#घोषणा AR6004_HW_1_2_FW_सूची			"ath6k/AR6004/hw1.2"
#घोषणा AR6004_HW_1_2_FIRMWARE_खाता           "fw.ram.bin"
#घोषणा AR6004_HW_1_2_BOARD_DATA_खाता         AR6004_HW_1_2_FW_सूची "/bdata.bin"
#घोषणा AR6004_HW_1_2_DEFAULT_BOARD_DATA_खाता \
	AR6004_HW_1_2_FW_सूची "/bdata.bin"

/* AR6004 1.3 definitions */
#घोषणा AR6004_HW_1_3_VERSION			0x31c8088a
#घोषणा AR6004_HW_1_3_FW_सूची			"ath6k/AR6004/hw1.3"
#घोषणा AR6004_HW_1_3_FIRMWARE_खाता		"fw.ram.bin"
#घोषणा AR6004_HW_1_3_TCMD_FIRMWARE_खाता	"utf.bin"
#घोषणा AR6004_HW_1_3_UTF_FIRMWARE_खाता		"utf.bin"
#घोषणा AR6004_HW_1_3_TESTSCRIPT_खाता		"nullTestFlow.bin"
#घोषणा AR6004_HW_1_3_BOARD_DATA_खाता	      AR6004_HW_1_3_FW_सूची "/bdata.bin"
#घोषणा AR6004_HW_1_3_DEFAULT_BOARD_DATA_खाता AR6004_HW_1_3_FW_सूची "/bdata.bin"

/* AR6004 3.0 definitions */
#घोषणा AR6004_HW_3_0_VERSION			0x31C809F8
#घोषणा AR6004_HW_3_0_FW_सूची			"ath6k/AR6004/hw3.0"
#घोषणा AR6004_HW_3_0_FIRMWARE_खाता		"fw.ram.bin"
#घोषणा AR6004_HW_3_0_TCMD_FIRMWARE_खाता	"utf.bin"
#घोषणा AR6004_HW_3_0_UTF_FIRMWARE_खाता		"utf.bin"
#घोषणा AR6004_HW_3_0_TESTSCRIPT_खाता		"nullTestFlow.bin"
#घोषणा AR6004_HW_3_0_BOARD_DATA_खाता	      AR6004_HW_3_0_FW_सूची "/bdata.bin"
#घोषणा AR6004_HW_3_0_DEFAULT_BOARD_DATA_खाता AR6004_HW_3_0_FW_सूची "/bdata.bin"

/* Per STA data, used in AP mode */
#घोषणा STA_PS_AWAKE		BIT(0)
#घोषणा	STA_PS_SLEEP		BIT(1)
#घोषणा	STA_PS_POLLED		BIT(2)
#घोषणा STA_PS_APSD_TRIGGER     BIT(3)
#घोषणा STA_PS_APSD_EOSP        BIT(4)

/* HTC TX packet tagging definitions */
#घोषणा ATH6KL_CONTROL_PKT_TAG    HTC_TX_PACKET_TAG_USER_DEFINED
#घोषणा ATH6KL_DATA_PKT_TAG       (ATH6KL_CONTROL_PKT_TAG + 1)

#घोषणा AR6003_CUST_DATA_SIZE 16

#घोषणा AGGR_WIN_IDX(x, y)          ((x) % (y))
#घोषणा AGGR_INCR_IDX(x, y)         AGGR_WIN_IDX(((x) + 1), (y))
#घोषणा AGGR_DCRM_IDX(x, y)         AGGR_WIN_IDX(((x) - 1), (y))
#घोषणा ATH6KL_MAX_SEQ_NO		0xFFF
#घोषणा ATH6KL_NEXT_SEQ_NO(x)		(((x) + 1) & ATH6KL_MAX_SEQ_NO)

#घोषणा NUM_OF_TIDS         8
#घोषणा AGGR_SZ_DEFAULT     8

#घोषणा AGGR_WIN_SZ_MIN     2
#घोषणा AGGR_WIN_SZ_MAX     8

#घोषणा TID_WINDOW_SZ(_x)   ((_x) << 1)

#घोषणा AGGR_NUM_OF_FREE_NETBUFS    16

#घोषणा AGGR_RX_TIMEOUT     100	/* in ms */

#घोषणा WMI_TIMEOUT (2 * HZ)

#घोषणा MBOX_YIELD_LIMIT 99

#घोषणा ATH6KL_DEFAULT_LISTEN_INTVAL	100 /* in TUs */
#घोषणा ATH6KL_DEFAULT_BMISS_TIME	1500
#घोषणा ATH6KL_MAX_WOW_LISTEN_INTL	300 /* in TUs */
#घोषणा ATH6KL_MAX_BMISS_TIME		5000

/* configuration lags */
/*
 * ATH6KL_CONF_IGNORE_ERP_BARKER: Ignore the barker premable in
 * ERP IE of beacon to determine the लघु premable support when
 * sending (Re)Assoc req.
 * ATH6KL_CONF_IGNORE_PS_FAIL_EVT_IN_SCAN: Don't send the घातer
 * module state transition failure events which happen during
 * scan, to the host.
 */
#घोषणा ATH6KL_CONF_IGNORE_ERP_BARKER		BIT(0)
#घोषणा ATH6KL_CONF_IGNORE_PS_FAIL_EVT_IN_SCAN  BIT(1)
#घोषणा ATH6KL_CONF_ENABLE_11N			BIT(2)
#घोषणा ATH6KL_CONF_ENABLE_TX_BURST		BIT(3)
#घोषणा ATH6KL_CONF_UART_DEBUG			BIT(4)

#घोषणा P2P_WILDCARD_SSID_LEN			7 /* सूचीECT- */

क्रमागत wlan_low_pwr_state अणु
	WLAN_POWER_STATE_ON,
	WLAN_POWER_STATE_CUT_PWR,
	WLAN_POWER_STATE_DEEP_SLEEP,
	WLAN_POWER_STATE_WOW
पूर्ण;

क्रमागत sme_state अणु
	SME_DISCONNECTED,
	SME_CONNECTING,
	SME_CONNECTED
पूर्ण;

काष्ठा skb_hold_q अणु
	काष्ठा sk_buff *skb;
	bool is_amsdu;
	u16 seq_no;
पूर्ण;

काष्ठा rxtid अणु
	bool aggr;
	bool समयr_mon;
	u16 win_sz;
	u16 seq_next;
	u32 hold_q_sz;
	काष्ठा skb_hold_q *hold_q;
	काष्ठा sk_buff_head q;

	/*
	 * lock मुख्यly protects seq_next and hold_q. Movement of seq_next
	 * needs to be रक्षित between aggr_समयout() and
	 * aggr_process_recv_frm(). hold_q will be holding the pending
	 * reorder frames and it's access should also be रक्षित.
	 * Some of the other fields like hold_q_sz, win_sz and aggr are
	 * initialized/reset when receiving addba/delba req, also जबतक
	 * deleting aggr state all the pending buffers are flushed beक्रमe
	 * resetting these fields, so there should not be any race in accessing
	 * these fields.
	 */
	spinlock_t lock;
पूर्ण;

काष्ठा rxtid_stats अणु
	u32 num_पूर्णांकo_aggr;
	u32 num_dups;
	u32 num_oow;
	u32 num_mpdu;
	u32 num_amsdu;
	u32 num_delivered;
	u32 num_समयouts;
	u32 num_hole;
	u32 num_bar;
पूर्ण;

काष्ठा aggr_info_conn अणु
	u8 aggr_sz;
	u8 समयr_scheduled;
	काष्ठा समयr_list समयr;
	काष्ठा net_device *dev;
	काष्ठा rxtid rx_tid[NUM_OF_TIDS];
	काष्ठा rxtid_stats stat[NUM_OF_TIDS];
	काष्ठा aggr_info *aggr_info;
पूर्ण;

काष्ठा aggr_info अणु
	काष्ठा aggr_info_conn *aggr_conn;
	काष्ठा sk_buff_head rx_amsdu_मुक्तq;
पूर्ण;

काष्ठा ath6kl_wep_key अणु
	u8 key_index;
	u8 key_len;
	u8 key[64];
पूर्ण;

#घोषणा ATH6KL_KEY_SEQ_LEN 8

काष्ठा ath6kl_key अणु
	u8 key[WLAN_MAX_KEY_LEN];
	u8 key_len;
	u8 seq[ATH6KL_KEY_SEQ_LEN];
	u8 seq_len;
	u32 cipher;
पूर्ण;

काष्ठा ath6kl_node_mapping अणु
	u8 mac_addr[ETH_ALEN];
	u8 ep_id;
	u8 tx_pend;
पूर्ण;

काष्ठा ath6kl_cookie अणु
	काष्ठा sk_buff *skb;
	u32 map_no;
	काष्ठा htc_packet htc_pkt;
	काष्ठा ath6kl_cookie *arc_list_next;
पूर्ण;

काष्ठा ath6kl_mgmt_buff अणु
	काष्ठा list_head list;
	u32 freq;
	u32 रुको;
	u32 id;
	bool no_cck;
	माप_प्रकार len;
	u8 buf[];
पूर्ण;

काष्ठा ath6kl_sta अणु
	u16 sta_flags;
	u8 mac[ETH_ALEN];
	u8 aid;
	u8 keymgmt;
	u8 ucipher;
	u8 auth;
	u8 wpa_ie[ATH6KL_MAX_IE];
	काष्ठा sk_buff_head psq;

	/* protects psq, mgmt_psq, apsdq, and mgmt_psq_len fields */
	spinlock_t psq_lock;

	काष्ठा list_head mgmt_psq;
	माप_प्रकार mgmt_psq_len;
	u8 apsd_info;
	काष्ठा sk_buff_head apsdq;
	काष्ठा aggr_info_conn *aggr_conn;
पूर्ण;

काष्ठा ath6kl_version अणु
	u32 target_ver;
	u32 wlan_ver;
	u32 abi_ver;
पूर्ण;

काष्ठा ath6kl_bmi अणु
	u32 cmd_credits;
	bool करोne_sent;
	u8 *cmd_buf;
	u32 max_data_size;
	u32 max_cmd_size;
पूर्ण;

काष्ठा target_stats अणु
	u64 tx_pkt;
	u64 tx_byte;
	u64 tx_ucast_pkt;
	u64 tx_ucast_byte;
	u64 tx_mcast_pkt;
	u64 tx_mcast_byte;
	u64 tx_bcast_pkt;
	u64 tx_bcast_byte;
	u64 tx_rts_success_cnt;
	u64 tx_pkt_per_ac[4];

	u64 tx_err;
	u64 tx_fail_cnt;
	u64 tx_retry_cnt;
	u64 tx_mult_retry_cnt;
	u64 tx_rts_fail_cnt;

	u64 rx_pkt;
	u64 rx_byte;
	u64 rx_ucast_pkt;
	u64 rx_ucast_byte;
	u64 rx_mcast_pkt;
	u64 rx_mcast_byte;
	u64 rx_bcast_pkt;
	u64 rx_bcast_byte;
	u64 rx_frgment_pkt;

	u64 rx_err;
	u64 rx_crc_err;
	u64 rx_key_cache_miss;
	u64 rx_decrypt_err;
	u64 rx_dupl_frame;

	u64 tkip_local_mic_fail;
	u64 tkip_cnter_measures_invoked;
	u64 tkip_replays;
	u64 tkip_fmt_err;
	u64 ccmp_fmt_err;
	u64 ccmp_replays;

	u64 pwr_save_fail_cnt;

	u64 cs_bmiss_cnt;
	u64 cs_low_rssi_cnt;
	u64 cs_connect_cnt;
	u64 cs_discon_cnt;

	s32 tx_ucast_rate;
	s32 rx_ucast_rate;

	u32 lq_val;

	u32 wow_pkt_dropped;
	u16 wow_evt_discarded;

	s16 noise_न्यूनमान_calib;
	s16 cs_rssi;
	s16 cs_ave_beacon_rssi;
	u8 cs_ave_beacon_snr;
	u8 cs_last_roam_msec;
	u8 cs_snr;

	u8 wow_host_pkt_wakeups;
	u8 wow_host_evt_wakeups;

	u32 arp_received;
	u32 arp_matched;
	u32 arp_replied;
पूर्ण;

काष्ठा ath6kl_mbox_info अणु
	u32 htc_addr;
	u32 htc_ext_addr;
	u32 htc_ext_sz;

	u32 block_size;

	u32 gmbox_addr;

	u32 gmbox_sz;
पूर्ण;

/*
 * 802.11i defines an extended IV क्रम use with non-WEP ciphers.
 * When the EXTIV bit is set in the key id byte an additional
 * 4 bytes immediately follow the IV क्रम TKIP.  For CCMP the
 * EXTIV bit is likewise set but the 8 bytes represent the
 * CCMP header rather than IV+extended-IV.
 */

#घोषणा ATH6KL_KEYBUF_SIZE 16
#घोषणा ATH6KL_MICBUF_SIZE (8+8)	/* space क्रम both tx and rx */

#घोषणा ATH6KL_KEY_XMIT  0x01
#घोषणा ATH6KL_KEY_RECV  0x02
#घोषणा ATH6KL_KEY_DEFAULT   0x80	/* शेष xmit key */

/* Initial group key क्रम AP mode */
काष्ठा ath6kl_req_key अणु
	bool valid;
	u8 key_index;
	पूर्णांक key_type;
	u8 key[WLAN_MAX_KEY_LEN];
	u8 key_len;
पूर्ण;

क्रमागत ath6kl_hअगर_type अणु
	ATH6KL_HIF_TYPE_SDIO,
	ATH6KL_HIF_TYPE_USB,
पूर्ण;

क्रमागत ath6kl_htc_type अणु
	ATH6KL_HTC_TYPE_MBOX,
	ATH6KL_HTC_TYPE_PIPE,
पूर्ण;

/* Max number of filters that hw supports */
#घोषणा ATH6K_MAX_MC_FILTERS_PER_LIST 7
काष्ठा ath6kl_mc_filter अणु
	काष्ठा list_head list;
	अक्षर hw_addr[ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE];
पूर्ण;

काष्ठा ath6kl_htcap अणु
	bool ht_enable;
	u8 ampdu_factor;
	अचिन्हित लघु cap_info;
पूर्ण;

/*
 * Driver's maximum limit, note that some firmwares support only one vअगर
 * and the runसमय (current) limit must be checked from ar->vअगर_max.
 */
#घोषणा ATH6KL_VIF_MAX	3

/* vअगर flags info */
क्रमागत ath6kl_vअगर_state अणु
	CONNECTED,
	CONNECT_PEND,
	WMM_ENABLED,
	NETQ_STOPPED,
	DTIM_EXPIRED,
	CLEAR_BSSFILTER_ON_BEACON,
	DTIM_PERIOD_AVAIL,
	WLAN_ENABLED,
	STATS_UPDATE_PEND,
	HOST_SLEEP_MODE_CMD_PROCESSED,
	NETDEV_MCAST_ALL_ON,
	NETDEV_MCAST_ALL_OFF,
	SCHED_SCANNING,
पूर्ण;

काष्ठा ath6kl_vअगर अणु
	काष्ठा list_head list;
	काष्ठा wireless_dev wdev;
	काष्ठा net_device *ndev;
	काष्ठा ath6kl *ar;
	/* Lock to protect vअगर specअगरic net_stats and flags */
	spinlock_t अगर_lock;
	u8 fw_vअगर_idx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ssid_len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 करोt11_auth_mode;
	u8 auth_mode;
	u8 prwise_crypto;
	u8 prwise_crypto_len;
	u8 grp_crypto;
	u8 grp_crypto_len;
	u8 def_txkey_index;
	u8 next_mode;
	u8 nw_type;
	u8 bssid[ETH_ALEN];
	u8 req_bssid[ETH_ALEN];
	u16 ch_hपूर्णांक;
	u16 bss_ch;
	काष्ठा ath6kl_wep_key wep_key_list[WMI_MAX_KEY_INDEX + 1];
	काष्ठा ath6kl_key keys[WMI_MAX_KEY_INDEX + 1];
	काष्ठा aggr_info *aggr_cntxt;
	काष्ठा ath6kl_htcap htcap[NUM_NL80211_BANDS];

	काष्ठा समयr_list disconnect_समयr;
	काष्ठा समयr_list sched_scan_समयr;

	काष्ठा cfg80211_scan_request *scan_req;
	क्रमागत sme_state sme_state;
	पूर्णांक reconnect_flag;
	u32 last_roc_id;
	u32 last_cancel_roc_id;
	u32 send_action_id;
	bool probe_req_report;
	u16 assoc_bss_beacon_पूर्णांक;
	u16 listen_पूर्णांकvl_t;
	u16 bmiss_समय_प्रकार;
	u32 txe_पूर्णांकvl;
	u16 bg_scan_period;
	u8 assoc_bss_dtim_period;
	काष्ठा target_stats target_stats;
	काष्ठा wmi_connect_cmd profile;
	u16 rsn_capab;

	काष्ठा list_head mc_filter;
पूर्ण;

अटल अंतरभूत काष्ठा ath6kl_vअगर *ath6kl_vअगर_from_wdev(काष्ठा wireless_dev *wdev)
अणु
	वापस container_of(wdev, काष्ठा ath6kl_vअगर, wdev);
पूर्ण

#घोषणा WOW_LIST_ID		0
#घोषणा WOW_HOST_REQ_DELAY	500 /* ms */

#घोषणा ATH6KL_SCHED_SCAN_RESULT_DELAY 5000 /* ms */

/* Flag info */
क्रमागत ath6kl_dev_state अणु
	WMI_ENABLED,
	WMI_READY,
	WMI_CTRL_EP_FULL,
	TESTMODE,
	DESTROY_IN_PROGRESS,
	SKIP_SCAN,
	ROAM_TBL_PEND,
	FIRST_BOOT,
	RECOVERY_CLEANUP,
पूर्ण;

क्रमागत ath6kl_state अणु
	ATH6KL_STATE_OFF,
	ATH6KL_STATE_ON,
	ATH6KL_STATE_SUSPENDING,
	ATH6KL_STATE_RESUMING,
	ATH6KL_STATE_DEEPSLEEP,
	ATH6KL_STATE_CUTPOWER,
	ATH6KL_STATE_WOW,
	ATH6KL_STATE_RECOVERY,
पूर्ण;

/* Fw error recovery */
#घोषणा ATH6KL_HB_RESP_MISS_THRES	5

क्रमागत ath6kl_fw_err अणु
	ATH6KL_FW_ASSERT,
	ATH6KL_FW_HB_RESP_FAILURE,
	ATH6KL_FW_EP_FULL,
पूर्ण;

काष्ठा ath6kl अणु
	काष्ठा device *dev;
	काष्ठा wiphy *wiphy;

	क्रमागत ath6kl_state state;
	अचिन्हित पूर्णांक tesपंचांगode;

	काष्ठा ath6kl_bmi bmi;
	स्थिर काष्ठा ath6kl_hअगर_ops *hअगर_ops;
	स्थिर काष्ठा ath6kl_htc_ops *htc_ops;
	काष्ठा wmi *wmi;
	पूर्णांक tx_pending[ENDPOपूर्णांक_उच्च];
	पूर्णांक total_tx_data_pend;
	काष्ठा htc_target *htc_target;
	क्रमागत ath6kl_hअगर_type hअगर_type;
	व्योम *hअगर_priv;
	काष्ठा list_head vअगर_list;
	/* Lock to aव्योम race in vअगर_list entries among add/del/traverse */
	spinlock_t list_lock;
	u8 num_vअगर;
	अचिन्हित पूर्णांक vअगर_max;
	u8 max_norm_अगरace;
	u8 avail_idx_map;

	/*
	 * Protects at least amsdu_rx_buffer_queue, ath6kl_alloc_cookie()
	 * calls, tx_pending and total_tx_data_pend.
	 */
	spinlock_t lock;

	काष्ठा semaphore sem;
	u8 lrssi_roam_threshold;
	काष्ठा ath6kl_version version;
	u32 target_type;
	u8 tx_pwr;
	काष्ठा ath6kl_node_mapping node_map[MAX_NODE_NUM];
	u8 ibss_ps_enable;
	bool ibss_अगर_active;
	u8 node_num;
	u8 next_ep_id;
	काष्ठा ath6kl_cookie *cookie_list;
	u32 cookie_count;
	क्रमागत htc_endpoपूर्णांक_id ac2ep_map[WMM_NUM_AC];
	bool ac_stream_active[WMM_NUM_AC];
	u8 ac_stream_pri_map[WMM_NUM_AC];
	u8 hiac_stream_active_pri;
	u8 ep2ac_map[ENDPOपूर्णांक_उच्च];
	क्रमागत htc_endpoपूर्णांक_id ctrl_ep;
	काष्ठा ath6kl_htc_credit_info credit_state_info;
	u32 connect_ctrl_flags;
	u32 user_key_ctrl;
	u8 usr_bss_filter;
	काष्ठा ath6kl_sta sta_list[AP_MAX_NUM_STA];
	u8 sta_list_index;
	काष्ठा ath6kl_req_key ap_mode_bkey;
	काष्ठा sk_buff_head mcastpsq;
	u32 want_ch_चयन;
	u16 last_ch;

	/*
	 * FIXME: protects access to mcastpsq but is actually useless as
	 * all skbe_queue_*() functions provide serialisation themselves
	 */
	spinlock_t mcastpsq_lock;

	u8 पूर्णांकra_bss;
	काष्ठा wmi_ap_mode_stat ap_stats;
	u8 ap_country_code[3];
	काष्ठा list_head amsdu_rx_buffer_queue;
	u8 rx_meta_ver;
	क्रमागत wlan_low_pwr_state wlan_pwr_state;
	u8 mac_addr[ETH_ALEN];
#घोषणा AR_MCAST_FILTER_MAC_ADDR_SIZE  4
	काष्ठा अणु
		व्योम *rx_report;
		माप_प्रकार rx_report_len;
	पूर्ण पंचांग;

	काष्ठा ath6kl_hw अणु
		u32 id;
		स्थिर अक्षर *name;
		u32 dataset_patch_addr;
		u32 app_load_addr;
		u32 app_start_override_addr;
		u32 board_ext_data_addr;
		u32 reserved_ram_size;
		u32 board_addr;
		u32 refclk_hz;
		u32 uarttx_pin;
		u32 uarttx_rate;
		u32 testscript_addr;
		u8 tx_ant;
		u8 rx_ant;
		क्रमागत wmi_phy_cap cap;

		u32 flags;

		काष्ठा ath6kl_hw_fw अणु
			स्थिर अक्षर *dir;
			स्थिर अक्षर *otp;
			स्थिर अक्षर *fw;
			स्थिर अक्षर *tcmd;
			स्थिर अक्षर *patch;
			स्थिर अक्षर *utf;
			स्थिर अक्षर *testscript;
		पूर्ण fw;

		स्थिर अक्षर *fw_board;
		स्थिर अक्षर *fw_शेष_board;
	पूर्ण hw;

	u16 conf_flags;
	u16 suspend_mode;
	u16 wow_suspend_mode;
	रुको_queue_head_t event_wq;
	काष्ठा ath6kl_mbox_info mbox_info;

	काष्ठा ath6kl_cookie cookie_mem[MAX_COOKIE_NUM];
	अचिन्हित दीर्घ flag;

	u8 *fw_board;
	माप_प्रकार fw_board_len;

	u8 *fw_otp;
	माप_प्रकार fw_otp_len;

	u8 *fw;
	माप_प्रकार fw_len;

	u8 *fw_patch;
	माप_प्रकार fw_patch_len;

	u8 *fw_testscript;
	माप_प्रकार fw_testscript_len;

	अचिन्हित पूर्णांक fw_api;
	अचिन्हित दीर्घ fw_capabilities[ATH6KL_CAPABILITY_LEN];

	काष्ठा workqueue_काष्ठा *ath6kl_wq;

	काष्ठा dentry *debugfs_phy;

	bool p2p;

	bool wiphy_रेजिस्टरed;

	काष्ठा ath6kl_fw_recovery अणु
		काष्ठा work_काष्ठा recovery_work;
		अचिन्हित दीर्घ err_reason;
		अचिन्हित दीर्घ hb_poll;
		काष्ठा समयr_list hb_समयr;
		u32 seq_num;
		bool hb_pending;
		u8 hb_misscnt;
		bool enable;
	पूर्ण fw_recovery;

#अगर_घोषित CONFIG_ATH6KL_DEBUG
	काष्ठा अणु
		काष्ठा sk_buff_head fwlog_queue;
		काष्ठा completion fwlog_completion;
		bool fwlog_खोलो;

		u32 fwlog_mask;

		अचिन्हित पूर्णांक dbgfs_diag_reg;
		u32 diag_reg_addr_wr;
		u32 diag_reg_val_wr;

		काष्ठा अणु
			अचिन्हित पूर्णांक invalid_rate;
		पूर्ण war_stats;

		u8 *roam_tbl;
		अचिन्हित पूर्णांक roam_tbl_len;

		u8 keepalive;
		u8 disc_समयout;
	पूर्ण debug;
#पूर्ण_अगर /* CONFIG_ATH6KL_DEBUG */
पूर्ण;

अटल अंतरभूत काष्ठा ath6kl *ath6kl_priv(काष्ठा net_device *dev)
अणु
	वापस ((काष्ठा ath6kl_vअगर *) netdev_priv(dev))->ar;
पूर्ण

अटल अंतरभूत u32 ath6kl_get_hi_item_addr(काष्ठा ath6kl *ar,
					  u32 item_offset)
अणु
	u32 addr = 0;

	अगर (ar->target_type == TARGET_TYPE_AR6003)
		addr = ATH6KL_AR6003_HI_START_ADDR + item_offset;
	अन्यथा अगर (ar->target_type == TARGET_TYPE_AR6004)
		addr = ATH6KL_AR6004_HI_START_ADDR + item_offset;

	वापस addr;
पूर्ण

पूर्णांक ath6kl_configure_target(काष्ठा ath6kl *ar);
व्योम ath6kl_detect_error(अचिन्हित दीर्घ ptr);
व्योम disconnect_समयr_handler(काष्ठा समयr_list *t);
व्योम init_netdev(काष्ठा net_device *dev);
व्योम ath6kl_cookie_init(काष्ठा ath6kl *ar);
व्योम ath6kl_cookie_cleanup(काष्ठा ath6kl *ar);
व्योम ath6kl_rx(काष्ठा htc_target *target, काष्ठा htc_packet *packet);
व्योम ath6kl_tx_complete(काष्ठा htc_target *context,
			काष्ठा list_head *packet_queue);
क्रमागत htc_send_full_action ath6kl_tx_queue_full(काष्ठा htc_target *target,
					       काष्ठा htc_packet *packet);
व्योम ath6kl_stop_txrx(काष्ठा ath6kl *ar);
व्योम ath6kl_cleanup_amsdu_rxbufs(काष्ठा ath6kl *ar);
पूर्णांक ath6kl_diag_ग_लिखो32(काष्ठा ath6kl *ar, u32 address, __le32 value);
पूर्णांक ath6kl_diag_ग_लिखो(काष्ठा ath6kl *ar, u32 address, व्योम *data, u32 length);
पूर्णांक ath6kl_diag_पढ़ो32(काष्ठा ath6kl *ar, u32 address, u32 *value);
पूर्णांक ath6kl_diag_पढ़ो(काष्ठा ath6kl *ar, u32 address, व्योम *data, u32 length);
पूर्णांक ath6kl_पढ़ो_fwlogs(काष्ठा ath6kl *ar);
व्योम ath6kl_init_profile_info(काष्ठा ath6kl_vअगर *vअगर);
व्योम ath6kl_tx_data_cleanup(काष्ठा ath6kl *ar);

काष्ठा ath6kl_cookie *ath6kl_alloc_cookie(काष्ठा ath6kl *ar);
व्योम ath6kl_मुक्त_cookie(काष्ठा ath6kl *ar, काष्ठा ath6kl_cookie *cookie);
netdev_tx_t ath6kl_data_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

काष्ठा aggr_info *aggr_init(काष्ठा ath6kl_vअगर *vअगर);
व्योम aggr_conn_init(काष्ठा ath6kl_vअगर *vअगर, काष्ठा aggr_info *aggr_info,
		    काष्ठा aggr_info_conn *aggr_conn);
व्योम ath6kl_rx_refill(काष्ठा htc_target *target,
		      क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक);
व्योम ath6kl_refill_amsdu_rxbufs(काष्ठा ath6kl *ar, पूर्णांक count);
काष्ठा htc_packet *ath6kl_alloc_amsdu_rxbuf(काष्ठा htc_target *target,
					    क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक,
					    पूर्णांक len);
व्योम aggr_module_destroy(काष्ठा aggr_info *aggr_info);
व्योम aggr_reset_state(काष्ठा aggr_info_conn *aggr_conn);

काष्ठा ath6kl_sta *ath6kl_find_sta(काष्ठा ath6kl_vअगर *vअगर, u8 *node_addr);
काष्ठा ath6kl_sta *ath6kl_find_sta_by_aid(काष्ठा ath6kl *ar, u8 aid);

व्योम ath6kl_पढ़ोy_event(व्योम *devt, u8 *datap, u32 sw_ver, u32 abi_ver,
			क्रमागत wmi_phy_cap cap);
पूर्णांक ath6kl_control_tx(व्योम *devt, काष्ठा sk_buff *skb,
		      क्रमागत htc_endpoपूर्णांक_id eid);
व्योम ath6kl_connect_event(काष्ठा ath6kl_vअगर *vअगर, u16 channel,
			  u8 *bssid, u16 listen_पूर्णांक,
			  u16 beacon_पूर्णांक, क्रमागत network_type net_type,
			  u8 beacon_ie_len, u8 assoc_req_len,
			  u8 assoc_resp_len, u8 *assoc_info);
व्योम ath6kl_connect_ap_mode_bss(काष्ठा ath6kl_vअगर *vअगर, u16 channel);
व्योम ath6kl_connect_ap_mode_sta(काष्ठा ath6kl_vअगर *vअगर, u16 aid, u8 *mac_addr,
				u8 keymgmt, u8 ucipher, u8 auth,
				u8 assoc_req_len, u8 *assoc_info, u8 apsd_info);
व्योम ath6kl_disconnect_event(काष्ठा ath6kl_vअगर *vअगर, u8 reason,
			     u8 *bssid, u8 assoc_resp_len,
			     u8 *assoc_info, u16 prot_reason_status);
व्योम ath6kl_tkip_micerr_event(काष्ठा ath6kl_vअगर *vअगर, u8 keyid, bool ismcast);
व्योम ath6kl_txpwr_rx_evt(व्योम *devt, u8 tx_pwr);
व्योम ath6kl_scan_complete_evt(काष्ठा ath6kl_vअगर *vअगर, पूर्णांक status);
व्योम ath6kl_tgt_stats_event(काष्ठा ath6kl_vअगर *vअगर, u8 *ptr, u32 len);
व्योम ath6kl_indicate_tx_activity(व्योम *devt, u8 traffic_class, bool active);
क्रमागत htc_endpoपूर्णांक_id ath6kl_ac2_endpoपूर्णांक_id(व्योम *devt, u8 ac);

व्योम ath6kl_pspoll_event(काष्ठा ath6kl_vअगर *vअगर, u8 aid);

व्योम ath6kl_dसमयxpiry_event(काष्ठा ath6kl_vअगर *vअगर);
व्योम ath6kl_disconnect(काष्ठा ath6kl_vअगर *vअगर);
व्योम aggr_recv_delba_req_evt(काष्ठा ath6kl_vअगर *vअगर, u8 tid);
व्योम aggr_recv_addba_req_evt(काष्ठा ath6kl_vअगर *vअगर, u8 tid, u16 seq_no,
			     u8 win_sz);
व्योम ath6kl_wakeup_event(व्योम *dev);

व्योम ath6kl_init_control_info(काष्ठा ath6kl_vअगर *vअगर);
काष्ठा ath6kl_vअगर *ath6kl_vअगर_first(काष्ठा ath6kl *ar);
व्योम ath6kl_cfg80211_vअगर_stop(काष्ठा ath6kl_vअगर *vअगर, bool wmi_पढ़ोy);
पूर्णांक ath6kl_init_hw_start(काष्ठा ath6kl *ar);
पूर्णांक ath6kl_init_hw_stop(काष्ठा ath6kl *ar);
पूर्णांक ath6kl_init_fetch_firmwares(काष्ठा ath6kl *ar);
पूर्णांक ath6kl_init_hw_params(काष्ठा ath6kl *ar);

व्योम ath6kl_check_wow_status(काष्ठा ath6kl *ar);

व्योम ath6kl_core_tx_complete(काष्ठा ath6kl *ar, काष्ठा sk_buff *skb);
व्योम ath6kl_core_rx_complete(काष्ठा ath6kl *ar, काष्ठा sk_buff *skb, u8 pipe);

काष्ठा ath6kl *ath6kl_core_create(काष्ठा device *dev);
पूर्णांक ath6kl_core_init(काष्ठा ath6kl *ar, क्रमागत ath6kl_htc_type htc_type);
व्योम ath6kl_core_cleanup(काष्ठा ath6kl *ar);
व्योम ath6kl_core_destroy(काष्ठा ath6kl *ar);

/* Fw error recovery */
व्योम ath6kl_init_hw_restart(काष्ठा ath6kl *ar);
व्योम ath6kl_recovery_err_notअगरy(काष्ठा ath6kl *ar, क्रमागत ath6kl_fw_err reason);
व्योम ath6kl_recovery_hb_event(काष्ठा ath6kl *ar, u32 cookie);
व्योम ath6kl_recovery_init(काष्ठा ath6kl *ar);
व्योम ath6kl_recovery_cleanup(काष्ठा ath6kl *ar);
व्योम ath6kl_recovery_suspend(काष्ठा ath6kl *ar);
व्योम ath6kl_recovery_resume(काष्ठा ath6kl *ar);
#पूर्ण_अगर /* CORE_H */
