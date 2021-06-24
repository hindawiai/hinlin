<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _CORE_H_
#घोषणा _CORE_H_

#समावेश <linux/completion.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/uuid.h>
#समावेश <linux/समय.स>

#समावेश "htt.h"
#समावेश "htc.h"
#समावेश "hw.h"
#समावेश "targaddrs.h"
#समावेश "wmi.h"
#समावेश "../ath.h"
#समावेश "../regd.h"
#समावेश "../dfs_pattern_detector.h"
#समावेश "spectral.h"
#समावेश "thermal.h"
#समावेश "wow.h"
#समावेश "swap.h"

#घोषणा MS(_v, _f) (((_v) & _f##_MASK) >> _f##_LSB)
#घोषणा SM(_v, _f) (((_v) << _f##_LSB) & _f##_MASK)
#घोषणा WO(_f)      ((_f##_OFFSET) >> 2)

#घोषणा ATH10K_SCAN_ID 0
#घोषणा ATH10K_SCAN_CHANNEL_SWITCH_WMI_EVT_OVERHEAD 10 /* msec */
#घोषणा WMI_READY_TIMEOUT (5 * HZ)
#घोषणा ATH10K_FLUSH_TIMEOUT_HZ (5 * HZ)
#घोषणा ATH10K_CONNECTION_LOSS_HZ (3 * HZ)
#घोषणा ATH10K_NUM_CHANS 41
#घोषणा ATH10K_MAX_5G_CHAN 173

/* Antenna noise न्यूनमान */
#घोषणा ATH10K_DEFAULT_NOISE_FLOOR -95

#घोषणा ATH10K_INVALID_RSSI 128

#घोषणा ATH10K_MAX_NUM_MGMT_PENDING 128

/* number of failed packets (20 packets with 16 sw reties each) */
#घोषणा ATH10K_KICKOUT_THRESHOLD (20 * 16)

/*
 * Use insanely high numbers to make sure that the firmware implementation
 * won't start, we have the same functionality alपढ़ोy in hostapd. Unit
 * is seconds.
 */
#घोषणा ATH10K_KEEPALIVE_MIN_IDLE 3747
#घोषणा ATH10K_KEEPALIVE_MAX_IDLE 3895
#घोषणा ATH10K_KEEPALIVE_MAX_UNRESPONSIVE 3900

/* NAPI poll budget */
#घोषणा ATH10K_NAPI_BUDGET      64

/* SMBIOS type containing Board Data File Name Extension */
#घोषणा ATH10K_SMBIOS_BDF_EXT_TYPE 0xF8

/* SMBIOS type काष्ठाure length (excluding strings-set) */
#घोषणा ATH10K_SMBIOS_BDF_EXT_LENGTH 0x9

/* Offset poपूर्णांकing to Board Data File Name Extension */
#घोषणा ATH10K_SMBIOS_BDF_EXT_OFFSET 0x8

/* Board Data File Name Extension string length.
 * String क्रमmat: BDF_<Customer ID>_<Extension>\0
 */
#घोषणा ATH10K_SMBIOS_BDF_EXT_STR_LENGTH 0x20

/* The magic used by QCA spec */
#घोषणा ATH10K_SMBIOS_BDF_EXT_MAGIC "BDF_"

/* Default Airसमय weight multipler (Tuned क्रम multiclient perक्रमmance) */
#घोषणा ATH10K_AIRTIME_WEIGHT_MULTIPLIER  4

#घोषणा ATH10K_MAX_RETRY_COUNT 30

#घोषणा ATH10K_ITER_NORMAL_FLAGS (IEEE80211_IFACE_ITER_NORMAL | \
				  IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DRIVER)
#घोषणा ATH10K_ITER_RESUME_FLAGS (IEEE80211_IFACE_ITER_RESUME_ALL |\
				  IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DRIVER)

काष्ठा ath10k;

अटल अंतरभूत स्थिर अक्षर *ath10k_bus_str(क्रमागत ath10k_bus bus)
अणु
	चयन (bus) अणु
	हाल ATH10K_BUS_PCI:
		वापस "pci";
	हाल ATH10K_BUS_AHB:
		वापस "ahb";
	हाल ATH10K_BUS_SDIO:
		वापस "sdio";
	हाल ATH10K_BUS_USB:
		वापस "usb";
	हाल ATH10K_BUS_SNOC:
		वापस "snoc";
	पूर्ण

	वापस "unknown";
पूर्ण

क्रमागत ath10k_skb_flags अणु
	ATH10K_SKB_F_NO_HWCRYPT = BIT(0),
	ATH10K_SKB_F_DTIM_ZERO = BIT(1),
	ATH10K_SKB_F_DELIVER_CAB = BIT(2),
	ATH10K_SKB_F_MGMT = BIT(3),
	ATH10K_SKB_F_QOS = BIT(4),
	ATH10K_SKB_F_RAW_TX = BIT(5),
	ATH10K_SKB_F_NOACK_TID = BIT(6),
पूर्ण;

काष्ठा ath10k_skb_cb अणु
	dma_addr_t paddr;
	u8 flags;
	u8 eid;
	u16 msdu_id;
	u16 airसमय_est;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_txq *txq;
	u32 ucast_cipher;
पूर्ण __packed;

काष्ठा ath10k_skb_rxcb अणु
	dma_addr_t paddr;
	काष्ठा hlist_node hlist;
	u8 eid;
पूर्ण;

अटल अंतरभूत काष्ठा ath10k_skb_cb *ATH10K_SKB_CB(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा ath10k_skb_cb) >
		     IEEE80211_TX_INFO_DRIVER_DATA_SIZE);
	वापस (काष्ठा ath10k_skb_cb *)&IEEE80211_SKB_CB(skb)->driver_data;
पूर्ण

अटल अंतरभूत काष्ठा ath10k_skb_rxcb *ATH10K_SKB_RXCB(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा ath10k_skb_rxcb) > माप(skb->cb));
	वापस (काष्ठा ath10k_skb_rxcb *)skb->cb;
पूर्ण

#घोषणा ATH10K_RXCB_SKB(rxcb) \
		container_of((व्योम *)rxcb, काष्ठा sk_buff, cb)

अटल अंतरभूत u32 host_पूर्णांकerest_item_address(u32 item_offset)
अणु
	वापस QCA988X_HOST_INTEREST_ADDRESS + item_offset;
पूर्ण

क्रमागत ath10k_phy_mode अणु
	ATH10K_PHY_MODE_LEGACY = 0,
	ATH10K_PHY_MODE_HT = 1,
	ATH10K_PHY_MODE_VHT = 2,
पूर्ण;

/* Data rate 100KBPS based on IE Index */
काष्ठा ath10k_index_ht_data_rate_type अणु
	u8   beacon_rate_index;
	u16  supported_rate[4];
पूर्ण;

/* Data rate 100KBPS based on IE Index */
काष्ठा ath10k_index_vht_data_rate_type अणु
	u8   beacon_rate_index;
	u16  supported_VHT80_rate[2];
	u16  supported_VHT40_rate[2];
	u16  supported_VHT20_rate[2];
पूर्ण;

काष्ठा ath10k_bmi अणु
	bool करोne_sent;
पूर्ण;

काष्ठा ath10k_mem_chunk अणु
	व्योम *vaddr;
	dma_addr_t paddr;
	u32 len;
	u32 req_id;
पूर्ण;

काष्ठा ath10k_wmi अणु
	क्रमागत ath10k_htc_ep_id eid;
	काष्ठा completion service_पढ़ोy;
	काष्ठा completion unअगरied_पढ़ोy;
	काष्ठा completion barrier;
	काष्ठा completion radar_confirm;
	रुको_queue_head_t tx_credits_wq;
	DECLARE_BITMAP(svc_map, WMI_SERVICE_MAX);
	काष्ठा wmi_cmd_map *cmd;
	काष्ठा wmi_vdev_param_map *vdev_param;
	काष्ठा wmi_pdev_param_map *pdev_param;
	काष्ठा wmi_peer_param_map *peer_param;
	स्थिर काष्ठा wmi_ops *ops;
	स्थिर काष्ठा wmi_peer_flags_map *peer_flags;

	u32 mgmt_max_num_pending_tx;

	/* Protected by data_lock */
	काष्ठा idr mgmt_pending_tx;

	u32 num_mem_chunks;
	u32 rx_decap_mode;
	काष्ठा ath10k_mem_chunk mem_chunks[WMI_MAX_MEM_REQS];
पूर्ण;

काष्ठा ath10k_fw_stats_peer अणु
	काष्ठा list_head list;

	u8 peer_macaddr[ETH_ALEN];
	u32 peer_rssi;
	u32 peer_tx_rate;
	u32 peer_rx_rate; /* 10x only */
	u64 rx_duration;
पूर्ण;

काष्ठा ath10k_fw_extd_stats_peer अणु
	काष्ठा list_head list;

	u8 peer_macaddr[ETH_ALEN];
	u64 rx_duration;
पूर्ण;

काष्ठा ath10k_fw_stats_vdev अणु
	काष्ठा list_head list;

	u32 vdev_id;
	u32 beacon_snr;
	u32 data_snr;
	u32 num_tx_frames[4];
	u32 num_rx_frames;
	u32 num_tx_frames_retries[4];
	u32 num_tx_frames_failures[4];
	u32 num_rts_fail;
	u32 num_rts_success;
	u32 num_rx_err;
	u32 num_rx_discard;
	u32 num_tx_not_acked;
	u32 tx_rate_history[10];
	u32 beacon_rssi_history[10];
पूर्ण;

काष्ठा ath10k_fw_stats_vdev_extd अणु
	काष्ठा list_head list;

	u32 vdev_id;
	u32 ppdu_aggr_cnt;
	u32 ppdu_noack;
	u32 mpdu_queued;
	u32 ppdu_nonaggr_cnt;
	u32 mpdu_sw_requeued;
	u32 mpdu_suc_retry;
	u32 mpdu_suc_multitry;
	u32 mpdu_fail_retry;
	u32 tx_fपंचांग_suc;
	u32 tx_fपंचांग_suc_retry;
	u32 tx_fपंचांग_fail;
	u32 rx_fपंचांगr_cnt;
	u32 rx_fपंचांगr_dup_cnt;
	u32 rx_अगरपंचांगr_cnt;
	u32 rx_अगरपंचांगr_dup_cnt;
पूर्ण;

काष्ठा ath10k_fw_stats_pdev अणु
	काष्ठा list_head list;

	/* PDEV stats */
	s32 ch_noise_न्यूनमान;
	u32 tx_frame_count; /* Cycles spent transmitting frames */
	u32 rx_frame_count; /* Cycles spent receiving frames */
	u32 rx_clear_count; /* Total channel busy समय, evidently */
	u32 cycle_count; /* Total on-channel समय */
	u32 phy_err_count;
	u32 chan_tx_घातer;
	u32 ack_rx_bad;
	u32 rts_bad;
	u32 rts_good;
	u32 fcs_bad;
	u32 no_beacons;
	u32 mib_पूर्णांक_count;

	/* PDEV TX stats */
	s32 comp_queued;
	s32 comp_delivered;
	s32 msdu_enqued;
	s32 mpdu_enqued;
	s32 wmm_drop;
	s32 local_enqued;
	s32 local_मुक्तd;
	s32 hw_queued;
	s32 hw_reaped;
	s32 underrun;
	u32 hw_छोड़ोd;
	s32 tx_पात;
	s32 mpdus_requed;
	u32 tx_ko;
	u32 data_rc;
	u32 self_triggers;
	u32 sw_retry_failure;
	u32 illgl_rate_phy_err;
	u32 pdev_cont_xretry;
	u32 pdev_tx_समयout;
	u32 pdev_resets;
	u32 phy_underrun;
	u32 txop_ovf;
	u32 seq_posted;
	u32 seq_failed_queueing;
	u32 seq_completed;
	u32 seq_restarted;
	u32 mu_seq_posted;
	u32 mpdus_sw_flush;
	u32 mpdus_hw_filter;
	u32 mpdus_truncated;
	u32 mpdus_ack_failed;
	u32 mpdus_expired;

	/* PDEV RX stats */
	s32 mid_ppdu_route_change;
	s32 status_rcvd;
	s32 r0_frags;
	s32 r1_frags;
	s32 r2_frags;
	s32 r3_frags;
	s32 htt_msdus;
	s32 htt_mpdus;
	s32 loc_msdus;
	s32 loc_mpdus;
	s32 oversize_amsdu;
	s32 phy_errs;
	s32 phy_err_drop;
	s32 mpdu_errs;
	s32 rx_ovfl_errs;
पूर्ण;

काष्ठा ath10k_fw_stats अणु
	bool extended;
	काष्ठा list_head pdevs;
	काष्ठा list_head vdevs;
	काष्ठा list_head peers;
	काष्ठा list_head peers_extd;
पूर्ण;

#घोषणा ATH10K_TPC_TABLE_TYPE_FLAG	1
#घोषणा ATH10K_TPC_PREAM_TABLE_END	0xFFFF

काष्ठा ath10k_tpc_table अणु
	u32 pream_idx[WMI_TPC_RATE_MAX];
	u8 rate_code[WMI_TPC_RATE_MAX];
	अक्षर tpc_value[WMI_TPC_RATE_MAX][WMI_TPC_TX_N_CHAIN * WMI_TPC_BUF_SIZE];
पूर्ण;

काष्ठा ath10k_tpc_stats अणु
	u32 reg_करोमुख्य;
	u32 chan_freq;
	u32 phy_mode;
	u32 twice_antenna_reduction;
	u32 twice_max_rd_घातer;
	s32 twice_antenna_gain;
	u32 घातer_limit;
	u32 num_tx_chain;
	u32 ctl;
	u32 rate_max;
	u8 flag[WMI_TPC_FLAG];
	काष्ठा ath10k_tpc_table tpc_table[WMI_TPC_FLAG];
पूर्ण;

काष्ठा ath10k_tpc_table_final अणु
	u32 pream_idx[WMI_TPC_FINAL_RATE_MAX];
	u8 rate_code[WMI_TPC_FINAL_RATE_MAX];
	अक्षर tpc_value[WMI_TPC_FINAL_RATE_MAX][WMI_TPC_TX_N_CHAIN * WMI_TPC_BUF_SIZE];
पूर्ण;

काष्ठा ath10k_tpc_stats_final अणु
	u32 reg_करोमुख्य;
	u32 chan_freq;
	u32 phy_mode;
	u32 twice_antenna_reduction;
	u32 twice_max_rd_घातer;
	s32 twice_antenna_gain;
	u32 घातer_limit;
	u32 num_tx_chain;
	u32 ctl;
	u32 rate_max;
	u8 flag[WMI_TPC_FLAG];
	काष्ठा ath10k_tpc_table_final tpc_table_final[WMI_TPC_FLAG];
पूर्ण;

काष्ठा ath10k_dfs_stats अणु
	u32 phy_errors;
	u32 pulses_total;
	u32 pulses_detected;
	u32 pulses_discarded;
	u32 radar_detected;
पूर्ण;

क्रमागत ath10k_radar_confirmation_state अणु
	ATH10K_RADAR_CONFIRMATION_IDLE = 0,
	ATH10K_RADAR_CONFIRMATION_INPROGRESS,
	ATH10K_RADAR_CONFIRMATION_STOPPED,
पूर्ण;

काष्ठा ath10k_radar_found_info अणु
	u32 pri_min;
	u32 pri_max;
	u32 width_min;
	u32 width_max;
	u32 sidx_min;
	u32 sidx_max;
पूर्ण;

#घोषणा ATH10K_MAX_NUM_PEER_IDS (1 << 11) /* htt rx_desc limit */

काष्ठा ath10k_peer अणु
	काष्ठा list_head list;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_sta *sta;

	bool हटाओd;
	पूर्णांक vdev_id;
	u8 addr[ETH_ALEN];
	DECLARE_BITMAP(peer_ids, ATH10K_MAX_NUM_PEER_IDS);

	/* रक्षित by ar->data_lock */
	काष्ठा ieee80211_key_conf *keys[WMI_MAX_KEY_INDEX + 1];
	जोड़ htt_rx_pn_t tids_last_pn[ATH10K_TXRX_NUM_EXT_TIDS];
	bool tids_last_pn_valid[ATH10K_TXRX_NUM_EXT_TIDS];
	जोड़ htt_rx_pn_t frag_tids_last_pn[ATH10K_TXRX_NUM_EXT_TIDS];
	u32 frag_tids_seq[ATH10K_TXRX_NUM_EXT_TIDS];
	काष्ठा अणु
		क्रमागत htt_security_types sec_type;
		पूर्णांक pn_len;
	पूर्ण rx_pn[ATH10K_HTT_TXRX_PEER_SECURITY_MAX];
पूर्ण;

काष्ठा ath10k_txq अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ num_fw_queued;
	अचिन्हित दीर्घ num_push_allowed;
पूर्ण;

क्रमागत ath10k_pkt_rx_err अणु
	ATH10K_PKT_RX_ERR_FCS,
	ATH10K_PKT_RX_ERR_TKIP,
	ATH10K_PKT_RX_ERR_CRYPT,
	ATH10K_PKT_RX_ERR_PEER_IDX_INVAL,
	ATH10K_PKT_RX_ERR_MAX,
पूर्ण;

क्रमागत ath10k_ampdu_subfrm_num अणु
	ATH10K_AMPDU_SUBFRM_NUM_10,
	ATH10K_AMPDU_SUBFRM_NUM_20,
	ATH10K_AMPDU_SUBFRM_NUM_30,
	ATH10K_AMPDU_SUBFRM_NUM_40,
	ATH10K_AMPDU_SUBFRM_NUM_50,
	ATH10K_AMPDU_SUBFRM_NUM_60,
	ATH10K_AMPDU_SUBFRM_NUM_MORE,
	ATH10K_AMPDU_SUBFRM_NUM_MAX,
पूर्ण;

क्रमागत ath10k_amsdu_subfrm_num अणु
	ATH10K_AMSDU_SUBFRM_NUM_1,
	ATH10K_AMSDU_SUBFRM_NUM_2,
	ATH10K_AMSDU_SUBFRM_NUM_3,
	ATH10K_AMSDU_SUBFRM_NUM_4,
	ATH10K_AMSDU_SUBFRM_NUM_MORE,
	ATH10K_AMSDU_SUBFRM_NUM_MAX,
पूर्ण;

काष्ठा ath10k_sta_tid_stats अणु
	अचिन्हित दीर्घ rx_pkt_from_fw;
	अचिन्हित दीर्घ rx_pkt_unchained;
	अचिन्हित दीर्घ rx_pkt_drop_chained;
	अचिन्हित दीर्घ rx_pkt_drop_filter;
	अचिन्हित दीर्घ rx_pkt_err[ATH10K_PKT_RX_ERR_MAX];
	अचिन्हित दीर्घ rx_pkt_queued_क्रम_mac;
	अचिन्हित दीर्घ rx_pkt_ampdu[ATH10K_AMPDU_SUBFRM_NUM_MAX];
	अचिन्हित दीर्घ rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_MAX];
पूर्ण;

क्रमागत ath10k_counter_type अणु
	ATH10K_COUNTER_TYPE_BYTES,
	ATH10K_COUNTER_TYPE_PKTS,
	ATH10K_COUNTER_TYPE_MAX,
पूर्ण;

क्रमागत ath10k_stats_type अणु
	ATH10K_STATS_TYPE_SUCC,
	ATH10K_STATS_TYPE_FAIL,
	ATH10K_STATS_TYPE_RETRY,
	ATH10K_STATS_TYPE_AMPDU,
	ATH10K_STATS_TYPE_MAX,
पूर्ण;

काष्ठा ath10k_htt_data_stats अणु
	u64 legacy[ATH10K_COUNTER_TYPE_MAX][ATH10K_LEGACY_NUM];
	u64 ht[ATH10K_COUNTER_TYPE_MAX][ATH10K_HT_MCS_NUM];
	u64 vht[ATH10K_COUNTER_TYPE_MAX][ATH10K_VHT_MCS_NUM];
	u64 bw[ATH10K_COUNTER_TYPE_MAX][ATH10K_BW_NUM];
	u64 nss[ATH10K_COUNTER_TYPE_MAX][ATH10K_NSS_NUM];
	u64 gi[ATH10K_COUNTER_TYPE_MAX][ATH10K_GI_NUM];
	u64 rate_table[ATH10K_COUNTER_TYPE_MAX][ATH10K_RATE_TABLE_NUM];
पूर्ण;

काष्ठा ath10k_htt_tx_stats अणु
	काष्ठा ath10k_htt_data_stats stats[ATH10K_STATS_TYPE_MAX];
	u64 tx_duration;
	u64 ba_fails;
	u64 ack_fails;
पूर्ण;

#घोषणा ATH10K_TID_MAX	8

काष्ठा ath10k_sta अणु
	काष्ठा ath10k_vअगर *arvअगर;

	/* the following are रक्षित by ar->data_lock */
	u32 changed; /* IEEE80211_RC_* */
	u32 bw;
	u32 nss;
	u32 smps;
	u16 peer_id;
	काष्ठा rate_info txrate;
	काष्ठा ieee80211_tx_info tx_info;
	u32 tx_retries;
	u32 tx_failed;
	u32 last_tx_bitrate;

	u32 rx_rate_code;
	u32 rx_bitrate_kbps;
	u32 tx_rate_code;
	u32 tx_bitrate_kbps;
	काष्ठा work_काष्ठा update_wk;
	u64 rx_duration;
	काष्ठा ath10k_htt_tx_stats *tx_stats;
	u32 ucast_cipher;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	/* रक्षित by conf_mutex */
	bool aggr_mode;

	/* Protected with ar->data_lock */
	काष्ठा ath10k_sta_tid_stats tid_stats[IEEE80211_NUM_TIDS + 1];
#पूर्ण_अगर
	/* Protected with ar->data_lock */
	u32 peer_ps_state;
	काष्ठा work_काष्ठा tid_config_wk;
	पूर्णांक noack[ATH10K_TID_MAX];
	पूर्णांक retry_दीर्घ[ATH10K_TID_MAX];
	पूर्णांक ampdu[ATH10K_TID_MAX];
	u8 rate_ctrl[ATH10K_TID_MAX];
	u32 rate_code[ATH10K_TID_MAX];
	पूर्णांक rtscts[ATH10K_TID_MAX];
पूर्ण;

#घोषणा ATH10K_VDEV_SETUP_TIMEOUT_HZ	(5 * HZ)
#घोषणा ATH10K_VDEV_DELETE_TIMEOUT_HZ	(5 * HZ)

क्रमागत ath10k_beacon_state अणु
	ATH10K_BEACON_SCHEDULED = 0,
	ATH10K_BEACON_SENDING,
	ATH10K_BEACON_SENT,
पूर्ण;

काष्ठा ath10k_vअगर अणु
	काष्ठा list_head list;

	u32 vdev_id;
	u16 peer_id;
	क्रमागत wmi_vdev_type vdev_type;
	क्रमागत wmi_vdev_subtype vdev_subtype;
	u32 beacon_पूर्णांकerval;
	u32 dtim_period;
	काष्ठा sk_buff *beacon;
	/* रक्षित by data_lock */
	क्रमागत ath10k_beacon_state beacon_state;
	व्योम *beacon_buf;
	dma_addr_t beacon_paddr;
	अचिन्हित दीर्घ tx_छोड़ोd; /* arbitrary values defined by target */

	काष्ठा ath10k *ar;
	काष्ठा ieee80211_vअगर *vअगर;

	bool is_started;
	bool is_up;
	bool spectral_enabled;
	bool ps;
	u32 aid;
	u8 bssid[ETH_ALEN];

	काष्ठा ieee80211_key_conf *wep_keys[WMI_MAX_KEY_INDEX + 1];
	s8 def_wep_key_idx;

	u16 tx_seq_no;

	जोड़ अणु
		काष्ठा अणु
			u32 uapsd;
		पूर्ण sta;
		काष्ठा अणु
			/* 512 stations */
			u8 tim_biपंचांगap[64];
			u8 tim_len;
			u32 ssid_len;
			u8 ssid[IEEE80211_MAX_SSID_LEN];
			bool hidden_ssid;
			/* P2P_IE with NoA attribute क्रम P2P_GO हाल */
			u32 noa_len;
			u8 *noa_data;
		पूर्ण ap;
	पूर्ण u;

	bool use_cts_prot;
	bool nohwcrypt;
	पूर्णांक num_legacy_stations;
	पूर्णांक txघातer;
	bool fपंचांग_responder;
	काष्ठा wmi_wmm_params_all_arg wmm_params;
	काष्ठा work_काष्ठा ap_csa_work;
	काष्ठा delayed_work connection_loss_work;
	काष्ठा cfg80211_bitrate_mask bitrate_mask;

	/* For setting VHT peer fixed rate, रक्षित by conf_mutex */
	पूर्णांक vht_num_rates;
	u8 vht_pfr;
	u32 tid_conf_changed[ATH10K_TID_MAX];
	पूर्णांक noack[ATH10K_TID_MAX];
	पूर्णांक retry_दीर्घ[ATH10K_TID_MAX];
	पूर्णांक ampdu[ATH10K_TID_MAX];
	u8 rate_ctrl[ATH10K_TID_MAX];
	u32 rate_code[ATH10K_TID_MAX];
	पूर्णांक rtscts[ATH10K_TID_MAX];
	u32 tids_rst;
पूर्ण;

काष्ठा ath10k_vअगर_iter अणु
	u32 vdev_id;
	काष्ठा ath10k_vअगर *arvअगर;
पूर्ण;

/* Copy Engine रेजिस्टर dump, रक्षित by ce-lock */
काष्ठा ath10k_ce_crash_data अणु
	__le32 base_addr;
	__le32 src_wr_idx;
	__le32 src_r_idx;
	__le32 dst_wr_idx;
	__le32 dst_r_idx;
पूर्ण;

काष्ठा ath10k_ce_crash_hdr अणु
	__le32 ce_count;
	__le32 reserved[3]; /* क्रम future use */
	काष्ठा ath10k_ce_crash_data entries[];
पूर्ण;

#घोषणा MAX_MEM_DUMP_TYPE	5

/* used क्रम crash-dump storage, रक्षित by data-lock */
काष्ठा ath10k_fw_crash_data अणु
	guid_t guid;
	काष्ठा बारpec64 बारtamp;
	__le32 रेजिस्टरs[REG_DUMP_COUNT_QCA988X];
	काष्ठा ath10k_ce_crash_data ce_crash_data[CE_COUNT_MAX];

	u8 *ramdump_buf;
	माप_प्रकार ramdump_buf_len;
पूर्ण;

काष्ठा ath10k_debug अणु
	काष्ठा dentry *debugfs_phy;

	काष्ठा ath10k_fw_stats fw_stats;
	काष्ठा completion fw_stats_complete;
	bool fw_stats_करोne;

	अचिन्हित दीर्घ htt_stats_mask;
	अचिन्हित दीर्घ reset_htt_stats;
	काष्ठा delayed_work htt_stats_dwork;
	काष्ठा ath10k_dfs_stats dfs_stats;
	काष्ठा ath_dfs_pool_stats dfs_pool_stats;

	/* used क्रम tpc-dump storage, रक्षित by data-lock */
	काष्ठा ath10k_tpc_stats *tpc_stats;
	काष्ठा ath10k_tpc_stats_final *tpc_stats_final;

	काष्ठा completion tpc_complete;

	/* रक्षित by conf_mutex */
	u64 fw_dbglog_mask;
	u32 fw_dbglog_level;
	u32 reg_addr;
	u32 nf_cal_period;
	व्योम *cal_data;
	u32 enable_extd_tx_stats;
	u8 fw_dbglog_mode;
पूर्ण;

क्रमागत ath10k_state अणु
	ATH10K_STATE_OFF = 0,
	ATH10K_STATE_ON,

	/* When करोing firmware recovery the device is first घातered करोwn.
	 * mac80211 is supposed to call in to start() hook later on. It is
	 * however possible that driver unloading and firmware crash overlap.
	 * mac80211 can रुको on conf_mutex in stop() जबतक the device is
	 * stopped in ath10k_core_restart() work holding conf_mutex. The state
	 * RESTARTED means that the device is up and mac80211 has started hw
	 * reconfiguration. Once mac80211 is करोne with the reconfiguration we
	 * set the state to STATE_ON in reconfig_complete().
	 */
	ATH10K_STATE_RESTARTING,
	ATH10K_STATE_RESTARTED,

	/* The device has crashed जबतक restarting hw. This state is like ON
	 * but commands are blocked in HTC and -ECOMM response is given. This
	 * prevents completion समयouts and makes the driver more responsive to
	 * userspace commands. This is also prevents recursive recovery.
	 */
	ATH10K_STATE_WEDGED,

	/* factory tests */
	ATH10K_STATE_UTF,
पूर्ण;

क्रमागत ath10k_firmware_mode अणु
	/* the शेष mode, standard 802.11 functionality */
	ATH10K_FIRMWARE_MODE_NORMAL,

	/* factory tests etc */
	ATH10K_FIRMWARE_MODE_UTF,
पूर्ण;

क्रमागत ath10k_fw_features अणु
	/* wmi_mgmt_rx_hdr contains extra RSSI inक्रमmation */
	ATH10K_FW_FEATURE_EXT_WMI_MGMT_RX = 0,

	/* Firmware from 10X branch. Deprecated, करोn't use in new code. */
	ATH10K_FW_FEATURE_WMI_10X = 1,

	/* firmware support tx frame management over WMI, otherwise it's HTT */
	ATH10K_FW_FEATURE_HAS_WMI_MGMT_TX = 2,

	/* Firmware करोes not support P2P */
	ATH10K_FW_FEATURE_NO_P2P = 3,

	/* Firmware 10.2 feature bit. The ATH10K_FW_FEATURE_WMI_10X feature
	 * bit is required to be set as well. Deprecated, करोn't use in new
	 * code.
	 */
	ATH10K_FW_FEATURE_WMI_10_2 = 4,

	/* Some firmware revisions lack proper multi-पूर्णांकerface client घातersave
	 * implementation. Enabling PS could result in connection drops,
	 * traffic stalls, etc.
	 */
	ATH10K_FW_FEATURE_MULTI_VIF_PS_SUPPORT = 5,

	/* Some firmware revisions have an incomplete WoWLAN implementation
	 * despite WMI service bit being advertised. This feature flag is used
	 * to distinguish whether WoWLAN is really supported or not.
	 */
	ATH10K_FW_FEATURE_WOWLAN_SUPPORT = 6,

	/* Don't trust error code from otp.bin */
	ATH10K_FW_FEATURE_IGNORE_OTP_RESULT = 7,

	/* Some firmware revisions pad 4th hw address to 4 byte boundary making
	 * it 8 bytes दीर्घ in Native Wअगरi Rx decap.
	 */
	ATH10K_FW_FEATURE_NO_NWIFI_DECAP_4ADDR_PADDING = 8,

	/* Firmware supports bypassing PLL setting on init. */
	ATH10K_FW_FEATURE_SUPPORTS_SKIP_CLOCK_INIT = 9,

	/* Raw mode support. If supported, FW supports receiving and trयंत्रitting
	 * frames in raw mode.
	 */
	ATH10K_FW_FEATURE_RAW_MODE_SUPPORT = 10,

	/* Firmware Supports Adaptive CCA*/
	ATH10K_FW_FEATURE_SUPPORTS_ADAPTIVE_CCA = 11,

	/* Firmware supports management frame protection */
	ATH10K_FW_FEATURE_MFP_SUPPORT = 12,

	/* Firmware supports pull-push model where host shares it's software
	 * queue state with firmware and firmware generates fetch requests
	 * telling host which queues to dequeue tx from.
	 *
	 * Primary function of this is improved MU-MIMO perक्रमmance with
	 * multiple clients.
	 */
	ATH10K_FW_FEATURE_PEER_FLOW_CONTROL = 13,

	/* Firmware supports BT-Coex without reloading firmware via pdev param.
	 * To support Bluetooth coexistence pdev param, WMI_COEX_GPIO_SUPPORT of
	 * extended resource config should be enabled always. This firmware IE
	 * is used to configure WMI_COEX_GPIO_SUPPORT.
	 */
	ATH10K_FW_FEATURE_BTCOEX_PARAM = 14,

	/* Unused flag and proven to be not working, enable this अगर you want
	 * to experiment sending शून्य func data frames in HTT TX
	 */
	ATH10K_FW_FEATURE_SKIP_शून्य_FUNC_WAR = 15,

	/* Firmware allow other BSS mesh broadcast/multicast frames without
	 * creating monitor पूर्णांकerface. Appropriate rxfilters are programmed क्रम
	 * mesh vdev by firmware itself. This feature flags will be used क्रम
	 * not creating monitor vdev जबतक configuring mesh node.
	 */
	ATH10K_FW_FEATURE_ALLOWS_MESH_BCAST = 16,

	/* Firmware करोes not support घातer save in station mode. */
	ATH10K_FW_FEATURE_NO_PS = 17,

	/* Firmware allows management tx by reference instead of by value. */
	ATH10K_FW_FEATURE_MGMT_TX_BY_REF = 18,

	/* Firmware load is करोne बाह्यally, not by bmi */
	ATH10K_FW_FEATURE_NON_BMI = 19,

	/* Firmware sends only one chan_info event per channel */
	ATH10K_FW_FEATURE_SINGLE_CHAN_INFO_PER_CHANNEL = 20,

	/* Firmware allows setting peer fixed rate */
	ATH10K_FW_FEATURE_PEER_FIXED_RATE = 21,

	/* Firmware support IRAM recovery */
	ATH10K_FW_FEATURE_IRAM_RECOVERY = 22,

	/* keep last */
	ATH10K_FW_FEATURE_COUNT,
पूर्ण;

क्रमागत ath10k_dev_flags अणु
	/* Indicates that ath10k device is during CAC phase of DFS */
	ATH10K_CAC_RUNNING,
	ATH10K_FLAG_CORE_REGISTERED,

	/* Device has crashed and needs to restart. This indicates any pending
	 * रुकोers should immediately cancel instead of रुकोing क्रम a समय out.
	 */
	ATH10K_FLAG_CRASH_FLUSH,

	/* Use Raw mode instead of native WiFi Tx/Rx encap mode.
	 * Raw mode supports both hardware and software crypto. Native WiFi only
	 * supports hardware crypto.
	 */
	ATH10K_FLAG_RAW_MODE,

	/* Disable HW crypto engine */
	ATH10K_FLAG_HW_CRYPTO_DISABLED,

	/* Bluetooth coexistance enabled */
	ATH10K_FLAG_BTCOEX,

	/* Per Station statistics service */
	ATH10K_FLAG_PEER_STATS,

	/* Indicates that ath10k device is during recovery process and not complete */
	ATH10K_FLAG_RESTARTING,

	/* रक्षित by conf_mutex */
	ATH10K_FLAG_NAPI_ENABLED,
पूर्ण;

क्रमागत ath10k_cal_mode अणु
	ATH10K_CAL_MODE_खाता,
	ATH10K_CAL_MODE_OTP,
	ATH10K_CAL_MODE_DT,
	ATH10K_PRE_CAL_MODE_खाता,
	ATH10K_PRE_CAL_MODE_DT,
	ATH10K_CAL_MODE_EEPROM,
पूर्ण;

क्रमागत ath10k_crypt_mode अणु
	/* Only use hardware crypto engine */
	ATH10K_CRYPT_MODE_HW,
	/* Only use software crypto engine */
	ATH10K_CRYPT_MODE_SW,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *ath10k_cal_mode_str(क्रमागत ath10k_cal_mode mode)
अणु
	चयन (mode) अणु
	हाल ATH10K_CAL_MODE_खाता:
		वापस "file";
	हाल ATH10K_CAL_MODE_OTP:
		वापस "otp";
	हाल ATH10K_CAL_MODE_DT:
		वापस "dt";
	हाल ATH10K_PRE_CAL_MODE_खाता:
		वापस "pre-cal-file";
	हाल ATH10K_PRE_CAL_MODE_DT:
		वापस "pre-cal-dt";
	हाल ATH10K_CAL_MODE_EEPROM:
		वापस "eeprom";
	पूर्ण

	वापस "unknown";
पूर्ण

क्रमागत ath10k_scan_state अणु
	ATH10K_SCAN_IDLE,
	ATH10K_SCAN_STARTING,
	ATH10K_SCAN_RUNNING,
	ATH10K_SCAN_ABORTING,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *ath10k_scan_state_str(क्रमागत ath10k_scan_state state)
अणु
	चयन (state) अणु
	हाल ATH10K_SCAN_IDLE:
		वापस "idle";
	हाल ATH10K_SCAN_STARTING:
		वापस "starting";
	हाल ATH10K_SCAN_RUNNING:
		वापस "running";
	हाल ATH10K_SCAN_ABORTING:
		वापस "aborting";
	पूर्ण

	वापस "unknown";
पूर्ण

क्रमागत ath10k_tx_छोड़ो_reason अणु
	ATH10K_TX_PAUSE_Q_FULL,
	ATH10K_TX_PAUSE_MAX,
पूर्ण;

काष्ठा ath10k_fw_file अणु
	स्थिर काष्ठा firmware *firmware;

	अक्षर fw_version[ETHTOOL_FWVERS_LEN];

	DECLARE_BITMAP(fw_features, ATH10K_FW_FEATURE_COUNT);

	क्रमागत ath10k_fw_wmi_op_version wmi_op_version;
	क्रमागत ath10k_fw_htt_op_version htt_op_version;

	स्थिर व्योम *firmware_data;
	माप_प्रकार firmware_len;

	स्थिर व्योम *otp_data;
	माप_प्रकार otp_len;

	स्थिर व्योम *codeswap_data;
	माप_प्रकार codeswap_len;

	/* The original idea of काष्ठा ath10k_fw_file was that it only
	 * contains काष्ठा firmware and poपूर्णांकers to various parts (actual
	 * firmware binary, otp, metadata etc) of the file. This seg_info
	 * is actually created separate but as this is used similarly as
	 * the other firmware components it's more convenient to have it
	 * here.
	 */
	काष्ठा ath10k_swap_code_seg_info *firmware_swap_code_seg_info;
पूर्ण;

काष्ठा ath10k_fw_components अणु
	स्थिर काष्ठा firmware *board;
	स्थिर व्योम *board_data;
	माप_प्रकार board_len;
	स्थिर काष्ठा firmware *ext_board;
	स्थिर व्योम *ext_board_data;
	माप_प्रकार ext_board_len;

	काष्ठा ath10k_fw_file fw_file;
पूर्ण;

काष्ठा ath10k_per_peer_tx_stats अणु
	u32	succ_bytes;
	u32	retry_bytes;
	u32	failed_bytes;
	u8	ratecode;
	u8	flags;
	u16	peer_id;
	u16	succ_pkts;
	u16	retry_pkts;
	u16	failed_pkts;
	u16	duration;
	u32	reserved1;
	u32	reserved2;
पूर्ण;

क्रमागत ath10k_dev_type अणु
	ATH10K_DEV_TYPE_LL,
	ATH10K_DEV_TYPE_HL,
पूर्ण;

काष्ठा ath10k_bus_params अणु
	u32 chip_id;
	क्रमागत ath10k_dev_type dev_type;
	bool link_can_suspend;
	bool hl_msdu_ids;
पूर्ण;

काष्ठा ath10k अणु
	काष्ठा ath_common ath_common;
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_ops *ops;
	काष्ठा device *dev;
	काष्ठा msa_region अणु
		dma_addr_t paddr;
		u32 mem_size;
		व्योम *vaddr;
	पूर्ण msa;
	u8 mac_addr[ETH_ALEN];

	क्रमागत ath10k_hw_rev hw_rev;
	u16 dev_id;
	u32 chip_id;
	u32 target_version;
	u8 fw_version_major;
	u32 fw_version_minor;
	u16 fw_version_release;
	u16 fw_version_build;
	u32 fw_stats_req_mask;
	u32 phy_capability;
	u32 hw_min_tx_घातer;
	u32 hw_max_tx_घातer;
	u32 hw_eeprom_rd;
	u32 ht_cap_info;
	u32 vht_cap_info;
	u32 vht_supp_mcs;
	u32 num_rf_chains;
	u32 max_spatial_stream;
	/* रक्षित by conf_mutex */
	u32 low_2ghz_chan;
	u32 high_2ghz_chan;
	u32 low_5ghz_chan;
	u32 high_5ghz_chan;
	bool ani_enabled;
	u32 sys_cap_info;

	/* रक्षित by data_lock */
	bool hw_rfसमाप्त_on;

	/* रक्षित by conf_mutex */
	u8 ps_state_enable;

	bool nlo_enabled;
	bool p2p;

	काष्ठा अणु
		क्रमागत ath10k_bus bus;
		स्थिर काष्ठा ath10k_hअगर_ops *ops;
	पूर्ण hअगर;

	काष्ठा completion target_suspend;
	काष्ठा completion driver_recovery;

	स्थिर काष्ठा ath10k_hw_regs *regs;
	स्थिर काष्ठा ath10k_hw_ce_regs *hw_ce_regs;
	स्थिर काष्ठा ath10k_hw_values *hw_values;
	काष्ठा ath10k_bmi bmi;
	काष्ठा ath10k_wmi wmi;
	काष्ठा ath10k_htc htc;
	काष्ठा ath10k_htt htt;

	काष्ठा ath10k_hw_params hw_params;

	/* contains the firmware images used with ATH10K_FIRMWARE_MODE_NORMAL */
	काष्ठा ath10k_fw_components normal_mode_fw;

	/* READ-ONLY images of the running firmware, which can be either
	 * normal or UTF. Do not modअगरy, release etc!
	 */
	स्थिर काष्ठा ath10k_fw_components *running_fw;

	स्थिर काष्ठा firmware *pre_cal_file;
	स्थिर काष्ठा firmware *cal_file;

	काष्ठा अणु
		u32 venकरोr;
		u32 device;
		u32 subप्रणाली_venकरोr;
		u32 subप्रणाली_device;

		bool bmi_ids_valid;
		bool qmi_ids_valid;
		u32 qmi_board_id;
		u32 qmi_chip_id;
		u8 bmi_board_id;
		u8 bmi_eboard_id;
		u8 bmi_chip_id;
		bool ext_bid_supported;

		अक्षर bdf_ext[ATH10K_SMBIOS_BDF_EXT_STR_LENGTH];
	पूर्ण id;

	पूर्णांक fw_api;
	पूर्णांक bd_api;
	क्रमागत ath10k_cal_mode cal_mode;

	काष्ठा अणु
		काष्ठा completion started;
		काष्ठा completion completed;
		काष्ठा completion on_channel;
		काष्ठा delayed_work समयout;
		क्रमागत ath10k_scan_state state;
		bool is_roc;
		पूर्णांक vdev_id;
		पूर्णांक roc_freq;
		bool roc_notअगरy;
	पूर्ण scan;

	काष्ठा अणु
		काष्ठा ieee80211_supported_band sbands[NUM_NL80211_BANDS];
	पूर्ण mac;

	/* should never be शून्य; needed क्रम regular htt rx */
	काष्ठा ieee80211_channel *rx_channel;

	/* valid during scan; needed क्रम mgmt rx during scan */
	काष्ठा ieee80211_channel *scan_channel;

	/* current operating channel definition */
	काष्ठा cfg80211_chan_def chandef;

	/* currently configured operating channel in firmware */
	काष्ठा ieee80211_channel *tgt_oper_chan;

	अचिन्हित दीर्घ दीर्घ मुक्त_vdev_map;
	काष्ठा ath10k_vअगर *monitor_arvअगर;
	bool monitor;
	पूर्णांक monitor_vdev_id;
	bool monitor_started;
	अचिन्हित पूर्णांक filter_flags;
	अचिन्हित दीर्घ dev_flags;
	bool dfs_block_radar_events;

	/* रक्षित by conf_mutex */
	bool radar_enabled;
	पूर्णांक num_started_vdevs;

	/* Protected by conf-mutex */
	u8 cfg_tx_chainmask;
	u8 cfg_rx_chainmask;

	काष्ठा completion install_key_करोne;

	पूर्णांक last_wmi_vdev_start_status;
	काष्ठा completion vdev_setup_करोne;
	काष्ठा completion vdev_delete_करोne;
	काष्ठा completion peer_stats_info_complete;

	काष्ठा workqueue_काष्ठा *workqueue;
	/* Auxiliary workqueue */
	काष्ठा workqueue_काष्ठा *workqueue_aux;
	काष्ठा workqueue_काष्ठा *workqueue_tx_complete;
	/* prevents concurrent FW reconfiguration */
	काष्ठा mutex conf_mutex;

	/* protects coredump data */
	काष्ठा mutex dump_mutex;

	/* protects shared काष्ठाure data */
	spinlock_t data_lock;

	काष्ठा list_head arvअगरs;
	काष्ठा list_head peers;
	काष्ठा ath10k_peer *peer_map[ATH10K_MAX_NUM_PEER_IDS];
	रुको_queue_head_t peer_mapping_wq;

	/* रक्षित by conf_mutex */
	पूर्णांक num_peers;
	पूर्णांक num_stations;

	पूर्णांक max_num_peers;
	पूर्णांक max_num_stations;
	पूर्णांक max_num_vdevs;
	पूर्णांक max_num_tdls_vdevs;
	पूर्णांक num_active_peers;
	पूर्णांक num_tids;

	काष्ठा work_काष्ठा svc_rdy_work;
	काष्ठा sk_buff *svc_rdy_skb;

	काष्ठा work_काष्ठा offchan_tx_work;
	काष्ठा sk_buff_head offchan_tx_queue;
	काष्ठा completion offchan_tx_completed;
	काष्ठा sk_buff *offchan_tx_skb;

	काष्ठा work_काष्ठा wmi_mgmt_tx_work;
	काष्ठा sk_buff_head wmi_mgmt_tx_queue;

	क्रमागत ath10k_state state;

	काष्ठा work_काष्ठा रेजिस्टर_work;
	काष्ठा work_काष्ठा restart_work;
	काष्ठा work_काष्ठा bundle_tx_work;
	काष्ठा work_काष्ठा tx_complete_work;

	/* cycle count is reported twice क्रम each visited channel during scan.
	 * access रक्षित by data_lock
	 */
	u32 survey_last_rx_clear_count;
	u32 survey_last_cycle_count;
	काष्ठा survey_info survey[ATH10K_NUM_CHANS];

	/* Channel info events are expected to come in pairs without and with
	 * COMPLETE flag set respectively क्रम each channel visit during scan.
	 *
	 * However there are deviations from this rule. This flag is used to
	 * aव्योम reporting garbage data.
	 */
	bool ch_info_can_report_survey;
	काष्ठा completion bss_survey_करोne;

	काष्ठा dfs_pattern_detector *dfs_detector;

	अचिन्हित दीर्घ tx_छोड़ोd; /* see ATH10K_TX_PAUSE_ */

#अगर_घोषित CONFIG_ATH10K_DEBUGFS
	काष्ठा ath10k_debug debug;
	काष्ठा अणु
		/* relay(fs) channel क्रम spectral scan */
		काष्ठा rchan *rfs_chan_spec_scan;

		/* spectral_mode and spec_config are रक्षित by conf_mutex */
		क्रमागत ath10k_spectral_mode mode;
		काष्ठा ath10k_spec_scan config;
	पूर्ण spectral;
#पूर्ण_अगर

	u32 pktlog_filter;

#अगर_घोषित CONFIG_DEV_COREDUMP
	काष्ठा अणु
		काष्ठा ath10k_fw_crash_data *fw_crash_data;
	पूर्ण coredump;
#पूर्ण_अगर

	काष्ठा अणु
		/* रक्षित by conf_mutex */
		काष्ठा ath10k_fw_components utf_mode_fw;

		/* रक्षित by data_lock */
		bool utf_monitor;
	पूर्ण tesपंचांगode;

	काष्ठा अणु
		/* रक्षित by data_lock */
		u32 rx_crc_err_drop;
		u32 fw_crash_counter;
		u32 fw_warm_reset_counter;
		u32 fw_cold_reset_counter;
	पूर्ण stats;

	काष्ठा ath10k_thermal thermal;
	काष्ठा ath10k_wow wow;
	काष्ठा ath10k_per_peer_tx_stats peer_tx_stats;

	/* NAPI */
	काष्ठा net_device napi_dev;
	काष्ठा napi_काष्ठा napi;

	काष्ठा work_काष्ठा set_coverage_class_work;
	/* रक्षित by conf_mutex */
	काष्ठा अणु
		/* writing also रक्षित by data_lock */
		s16 coverage_class;

		u32 reg_phyclk;
		u32 reg_slotसमय_conf;
		u32 reg_slotसमय_orig;
		u32 reg_ack_cts_समयout_conf;
		u32 reg_ack_cts_समयout_orig;
	पूर्ण fw_coverage;

	u32 ampdu_reference;

	स्थिर u8 *wmi_key_cipher;
	व्योम *ce_priv;

	u32 sta_tid_stats_mask;

	/* रक्षित by data_lock */
	क्रमागत ath10k_radar_confirmation_state radar_conf_state;
	काष्ठा ath10k_radar_found_info last_radar_info;
	काष्ठा work_काष्ठा radar_confirmation_work;
	काष्ठा ath10k_bus_params bus_param;
	काष्ठा completion peer_delete_करोne;

	bool coex_support;
	पूर्णांक coex_gpio_pin;

	s32 tx_घातer_2g_limit;
	s32 tx_घातer_5g_limit;

	/* must be last */
	u8 drv_priv[] __aligned(माप(व्योम *));
पूर्ण;

अटल अंतरभूत bool ath10k_peer_stats_enabled(काष्ठा ath10k *ar)
अणु
	अगर (test_bit(ATH10K_FLAG_PEER_STATS, &ar->dev_flags) &&
	    test_bit(WMI_SERVICE_PEER_STATS, ar->wmi.svc_map))
		वापस true;

	वापस false;
पूर्ण

बाह्य अचिन्हित दीर्घ ath10k_coredump_mask;

व्योम ath10k_core_napi_sync_disable(काष्ठा ath10k *ar);
व्योम ath10k_core_napi_enable(काष्ठा ath10k *ar);
काष्ठा ath10k *ath10k_core_create(माप_प्रकार priv_size, काष्ठा device *dev,
				  क्रमागत ath10k_bus bus,
				  क्रमागत ath10k_hw_rev hw_rev,
				  स्थिर काष्ठा ath10k_hअगर_ops *hअगर_ops);
व्योम ath10k_core_destroy(काष्ठा ath10k *ar);
व्योम ath10k_core_get_fw_features_str(काष्ठा ath10k *ar,
				     अक्षर *buf,
				     माप_प्रकार max_len);
पूर्णांक ath10k_core_fetch_firmware_api_n(काष्ठा ath10k *ar, स्थिर अक्षर *name,
				     काष्ठा ath10k_fw_file *fw_file);

पूर्णांक ath10k_core_start(काष्ठा ath10k *ar, क्रमागत ath10k_firmware_mode mode,
		      स्थिर काष्ठा ath10k_fw_components *fw_components);
पूर्णांक ath10k_रुको_क्रम_suspend(काष्ठा ath10k *ar, u32 suspend_opt);
व्योम ath10k_core_stop(काष्ठा ath10k *ar);
व्योम ath10k_core_start_recovery(काष्ठा ath10k *ar);
पूर्णांक ath10k_core_रेजिस्टर(काष्ठा ath10k *ar,
			 स्थिर काष्ठा ath10k_bus_params *bus_params);
व्योम ath10k_core_unरेजिस्टर(काष्ठा ath10k *ar);
पूर्णांक ath10k_core_fetch_board_file(काष्ठा ath10k *ar, पूर्णांक bd_ie_type);
पूर्णांक ath10k_core_check_dt(काष्ठा ath10k *ar);
व्योम ath10k_core_मुक्त_board_files(काष्ठा ath10k *ar);

#पूर्ण_अगर /* _CORE_H_ */
