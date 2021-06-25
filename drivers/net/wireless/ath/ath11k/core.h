<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_CORE_H
#घोषणा ATH11K_CORE_H

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/bitfield.h>
#समावेश "qmi.h"
#समावेश "htc.h"
#समावेश "wmi.h"
#समावेश "hal.h"
#समावेश "dp.h"
#समावेश "ce.h"
#समावेश "mac.h"
#समावेश "hw.h"
#समावेश "hal_rx.h"
#समावेश "reg.h"
#समावेश "thermal.h"
#समावेश "dbring.h"
#समावेश "spectral.h"

#घोषणा SM(_v, _f) (((_v) << _f##_LSB) & _f##_MASK)

#घोषणा ATH11K_TX_MGMT_NUM_PENDING_MAX	512

#घोषणा ATH11K_TX_MGMT_TARGET_MAX_SUPPORT_WMI 64

/* Pending management packets threshold क्रम dropping probe responses */
#घोषणा ATH11K_PRB_RSP_DROP_THRESHOLD ((ATH11K_TX_MGMT_TARGET_MAX_SUPPORT_WMI * 3) / 4)

#घोषणा ATH11K_INVALID_HW_MAC_ID	0xFF
#घोषणा ATH11K_CONNECTION_LOSS_HZ	(3 * HZ)

बाह्य अचिन्हित पूर्णांक ath11k_frame_mode;

#घोषणा ATH11K_MON_TIMER_INTERVAL  10

क्रमागत ath11k_supported_bw अणु
	ATH11K_BW_20	= 0,
	ATH11K_BW_40	= 1,
	ATH11K_BW_80	= 2,
	ATH11K_BW_160	= 3,
पूर्ण;

क्रमागत wme_ac अणु
	WME_AC_BE,
	WME_AC_BK,
	WME_AC_VI,
	WME_AC_VO,
	WME_NUM_AC
पूर्ण;

#घोषणा ATH11K_HT_MCS_MAX	7
#घोषणा ATH11K_VHT_MCS_MAX	9
#घोषणा ATH11K_HE_MCS_MAX	11

क्रमागत ath11k_crypt_mode अणु
	/* Only use hardware crypto engine */
	ATH11K_CRYPT_MODE_HW,
	/* Only use software crypto */
	ATH11K_CRYPT_MODE_SW,
पूर्ण;

अटल अंतरभूत क्रमागत wme_ac ath11k_tid_to_ac(u32 tid)
अणु
	वापस (((tid == 0) || (tid == 3)) ? WME_AC_BE :
		((tid == 1) || (tid == 2)) ? WME_AC_BK :
		((tid == 4) || (tid == 5)) ? WME_AC_VI :
		WME_AC_VO);
पूर्ण

क्रमागत ath11k_skb_flags अणु
	ATH11K_SKB_HW_80211_ENCAP = BIT(0),
	ATH11K_SKB_CIPHER_SET = BIT(1),
पूर्ण;

काष्ठा ath11k_skb_cb अणु
	dma_addr_t paddr;
	u8 eid;
	u8 flags;
	u32 cipher;
	काष्ठा ath11k *ar;
	काष्ठा ieee80211_vअगर *vअगर;
पूर्ण __packed;

काष्ठा ath11k_skb_rxcb अणु
	dma_addr_t paddr;
	bool is_first_msdu;
	bool is_last_msdu;
	bool is_continuation;
	काष्ठा hal_rx_desc *rx_desc;
	u8 err_rel_src;
	u8 err_code;
	u8 mac_id;
	u8 unmapped;
	u8 is_frag;
	u8 tid;
पूर्ण;

क्रमागत ath11k_hw_rev अणु
	ATH11K_HW_IPQ8074,
	ATH11K_HW_QCA6390_HW20,
	ATH11K_HW_IPQ6018_HW10,
	ATH11K_HW_QCN9074_HW10,
पूर्ण;

क्रमागत ath11k_firmware_mode अणु
	/* the शेष mode, standard 802.11 functionality */
	ATH11K_FIRMWARE_MODE_NORMAL,

	/* factory tests etc */
	ATH11K_FIRMWARE_MODE_FTM,

	/* Cold boot calibration */
	ATH11K_FIRMWARE_MODE_COLD_BOOT = 7,
पूर्ण;

बाह्य bool ath11k_cold_boot_cal;

#घोषणा ATH11K_IRQ_NUM_MAX 52
#घोषणा ATH11K_EXT_IRQ_NUM_MAX	16

काष्ठा ath11k_ext_irq_grp अणु
	काष्ठा ath11k_base *ab;
	u32 irqs[ATH11K_EXT_IRQ_NUM_MAX];
	u32 num_irq;
	u32 grp_id;
	u64 बारtamp;
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device napi_ndev;
पूर्ण;

#घोषणा HEHANDLE_CAP_PHYINFO_SIZE       3
#घोषणा HECAP_PHYINFO_SIZE              9
#घोषणा HECAP_MACINFO_SIZE              5
#घोषणा HECAP_TXRX_MCS_NSS_SIZE         2
#घोषणा HECAP_PPET16_PPET8_MAX_SIZE     25

#घोषणा HE_PPET16_PPET8_SIZE            8

/* 802.11ax PPE (PPDU packet Extension) threshold */
काष्ठा he_ppe_threshold अणु
	u32 numss_m1;
	u32 ru_mask;
	u32 ppet16_ppet8_ru3_ru0[HE_PPET16_PPET8_SIZE];
पूर्ण;

काष्ठा ath11k_he अणु
	u8 hecap_macinfo[HECAP_MACINFO_SIZE];
	u32 hecap_rxmcsnssmap;
	u32 hecap_txmcsnssmap;
	u32 hecap_phyinfo[HEHANDLE_CAP_PHYINFO_SIZE];
	काष्ठा he_ppe_threshold   hecap_ppet;
	u32 heop_param;
पूर्ण;

#घोषणा MAX_RADIOS 3

क्रमागत अणु
	WMI_HOST_TP_SCALE_MAX   = 0,
	WMI_HOST_TP_SCALE_50    = 1,
	WMI_HOST_TP_SCALE_25    = 2,
	WMI_HOST_TP_SCALE_12    = 3,
	WMI_HOST_TP_SCALE_MIN   = 4,
	WMI_HOST_TP_SCALE_SIZE   = 5,
पूर्ण;

क्रमागत ath11k_scan_state अणु
	ATH11K_SCAN_IDLE,
	ATH11K_SCAN_STARTING,
	ATH11K_SCAN_RUNNING,
	ATH11K_SCAN_ABORTING,
पूर्ण;

क्रमागत ath11k_dev_flags अणु
	ATH11K_CAC_RUNNING,
	ATH11K_FLAG_CORE_REGISTERED,
	ATH11K_FLAG_CRASH_FLUSH,
	ATH11K_FLAG_RAW_MODE,
	ATH11K_FLAG_HW_CRYPTO_DISABLED,
	ATH11K_FLAG_BTCOEX,
	ATH11K_FLAG_RECOVERY,
	ATH11K_FLAG_UNREGISTERING,
	ATH11K_FLAG_REGISTERED,
	ATH11K_FLAG_QMI_FAIL,
	ATH11K_FLAG_HTC_SUSPEND_COMPLETE,
पूर्ण;

क्रमागत ath11k_monitor_flags अणु
	ATH11K_FLAG_MONITOR_ENABLED,
पूर्ण;

काष्ठा ath11k_vअगर अणु
	u32 vdev_id;
	क्रमागत wmi_vdev_type vdev_type;
	क्रमागत wmi_vdev_subtype vdev_subtype;
	u32 beacon_पूर्णांकerval;
	u32 dtim_period;
	u16 ast_hash;
	u16 ast_idx;
	u16 tcl_metadata;
	u8 hal_addr_search_flags;
	u8 search_type;

	काष्ठा ath11k *ar;
	काष्ठा ieee80211_vअगर *vअगर;

	u16 tx_seq_no;
	काष्ठा wmi_wmm_params_all_arg wmm_params;
	काष्ठा list_head list;
	जोड़ अणु
		काष्ठा अणु
			u32 uapsd;
		पूर्ण sta;
		काष्ठा अणु
			/* 127 stations; wmi limit */
			u8 tim_biपंचांगap[16];
			u8 tim_len;
			u32 ssid_len;
			u8 ssid[IEEE80211_MAX_SSID_LEN];
			bool hidden_ssid;
			/* P2P_IE with NoA attribute क्रम P2P_GO हाल */
			u32 noa_len;
			u8 *noa_data;
		पूर्ण ap;
	पूर्ण u;

	bool is_started;
	bool is_up;
	bool spectral_enabled;
	u32 aid;
	u8 bssid[ETH_ALEN];
	काष्ठा cfg80211_bitrate_mask bitrate_mask;
	काष्ठा delayed_work connection_loss_work;
	पूर्णांक num_legacy_stations;
	पूर्णांक rtscts_prot_mode;
	पूर्णांक txघातer;
	bool rsnie_present;
	bool wpaie_present;
	काष्ठा ieee80211_chanctx_conf chanctx;
पूर्ण;

काष्ठा ath11k_vअगर_iter अणु
	u32 vdev_id;
	काष्ठा ath11k_vअगर *arvअगर;
पूर्ण;

काष्ठा ath11k_rx_peer_stats अणु
	u64 num_msdu;
	u64 num_mpdu_fcs_ok;
	u64 num_mpdu_fcs_err;
	u64 tcp_msdu_count;
	u64 udp_msdu_count;
	u64 other_msdu_count;
	u64 ampdu_msdu_count;
	u64 non_ampdu_msdu_count;
	u64 stbc_count;
	u64 beamक्रमmed_count;
	u64 mcs_count[HAL_RX_MAX_MCS + 1];
	u64 nss_count[HAL_RX_MAX_NSS];
	u64 bw_count[HAL_RX_BW_MAX];
	u64 gi_count[HAL_RX_GI_MAX];
	u64 coding_count[HAL_RX_SU_MU_CODING_MAX];
	u64 tid_count[IEEE80211_NUM_TIDS + 1];
	u64 pream_cnt[HAL_RX_PREAMBLE_MAX];
	u64 reception_type[HAL_RX_RECEPTION_TYPE_MAX];
	u64 rx_duration;
	u64 dcm_count;
	u64 ru_alloc_cnt[HAL_RX_RU_ALLOC_TYPE_MAX];
पूर्ण;

#घोषणा ATH11K_HE_MCS_NUM       12
#घोषणा ATH11K_VHT_MCS_NUM      10
#घोषणा ATH11K_BW_NUM           4
#घोषणा ATH11K_NSS_NUM          4
#घोषणा ATH11K_LEGACY_NUM       12
#घोषणा ATH11K_GI_NUM           4
#घोषणा ATH11K_HT_MCS_NUM       32

क्रमागत ath11k_pkt_rx_err अणु
	ATH11K_PKT_RX_ERR_FCS,
	ATH11K_PKT_RX_ERR_TKIP,
	ATH11K_PKT_RX_ERR_CRYPT,
	ATH11K_PKT_RX_ERR_PEER_IDX_INVAL,
	ATH11K_PKT_RX_ERR_MAX,
पूर्ण;

क्रमागत ath11k_ampdu_subfrm_num अणु
	ATH11K_AMPDU_SUBFRM_NUM_10,
	ATH11K_AMPDU_SUBFRM_NUM_20,
	ATH11K_AMPDU_SUBFRM_NUM_30,
	ATH11K_AMPDU_SUBFRM_NUM_40,
	ATH11K_AMPDU_SUBFRM_NUM_50,
	ATH11K_AMPDU_SUBFRM_NUM_60,
	ATH11K_AMPDU_SUBFRM_NUM_MORE,
	ATH11K_AMPDU_SUBFRM_NUM_MAX,
पूर्ण;

क्रमागत ath11k_amsdu_subfrm_num अणु
	ATH11K_AMSDU_SUBFRM_NUM_1,
	ATH11K_AMSDU_SUBFRM_NUM_2,
	ATH11K_AMSDU_SUBFRM_NUM_3,
	ATH11K_AMSDU_SUBFRM_NUM_4,
	ATH11K_AMSDU_SUBFRM_NUM_MORE,
	ATH11K_AMSDU_SUBFRM_NUM_MAX,
पूर्ण;

क्रमागत ath11k_counter_type अणु
	ATH11K_COUNTER_TYPE_BYTES,
	ATH11K_COUNTER_TYPE_PKTS,
	ATH11K_COUNTER_TYPE_MAX,
पूर्ण;

क्रमागत ath11k_stats_type अणु
	ATH11K_STATS_TYPE_SUCC,
	ATH11K_STATS_TYPE_FAIL,
	ATH11K_STATS_TYPE_RETRY,
	ATH11K_STATS_TYPE_AMPDU,
	ATH11K_STATS_TYPE_MAX,
पूर्ण;

काष्ठा ath11k_htt_data_stats अणु
	u64 legacy[ATH11K_COUNTER_TYPE_MAX][ATH11K_LEGACY_NUM];
	u64 ht[ATH11K_COUNTER_TYPE_MAX][ATH11K_HT_MCS_NUM];
	u64 vht[ATH11K_COUNTER_TYPE_MAX][ATH11K_VHT_MCS_NUM];
	u64 he[ATH11K_COUNTER_TYPE_MAX][ATH11K_HE_MCS_NUM];
	u64 bw[ATH11K_COUNTER_TYPE_MAX][ATH11K_BW_NUM];
	u64 nss[ATH11K_COUNTER_TYPE_MAX][ATH11K_NSS_NUM];
	u64 gi[ATH11K_COUNTER_TYPE_MAX][ATH11K_GI_NUM];
पूर्ण;

काष्ठा ath11k_htt_tx_stats अणु
	काष्ठा ath11k_htt_data_stats stats[ATH11K_STATS_TYPE_MAX];
	u64 tx_duration;
	u64 ba_fails;
	u64 ack_fails;
पूर्ण;

काष्ठा ath11k_per_ppdu_tx_stats अणु
	u16 succ_pkts;
	u16 failed_pkts;
	u16 retry_pkts;
	u32 succ_bytes;
	u32 failed_bytes;
	u32 retry_bytes;
पूर्ण;

काष्ठा ath11k_sta अणु
	काष्ठा ath11k_vअगर *arvअगर;

	/* the following are रक्षित by ar->data_lock */
	u32 changed; /* IEEE80211_RC_* */
	u32 bw;
	u32 nss;
	u32 smps;
	क्रमागत hal_pn_type pn_type;

	काष्ठा work_काष्ठा update_wk;
	काष्ठा rate_info txrate;
	काष्ठा rate_info last_txrate;
	u64 rx_duration;
	u64 tx_duration;
	u8 rssi_comb;
	काष्ठा ath11k_htt_tx_stats *tx_stats;
	काष्ठा ath11k_rx_peer_stats *rx_stats;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	/* रक्षित by conf_mutex */
	bool aggr_mode;
#पूर्ण_अगर
पूर्ण;

#घोषणा ATH11K_MIN_5G_FREQ 4150
#घोषणा ATH11K_MIN_6G_FREQ 5945
#घोषणा ATH11K_MAX_6G_FREQ 7115
#घोषणा ATH11K_NUM_CHANS 100
#घोषणा ATH11K_MAX_5G_CHAN 173

क्रमागत ath11k_state अणु
	ATH11K_STATE_OFF,
	ATH11K_STATE_ON,
	ATH11K_STATE_RESTARTING,
	ATH11K_STATE_RESTARTED,
	ATH11K_STATE_WEDGED,
	/* Add other states as required */
पूर्ण;

/* Antenna noise न्यूनमान */
#घोषणा ATH11K_DEFAULT_NOISE_FLOOR -95

काष्ठा ath11k_fw_stats अणु
	काष्ठा dentry *debugfs_fwstats;
	u32 pdev_id;
	u32 stats_id;
	काष्ठा list_head pdevs;
	काष्ठा list_head vdevs;
	काष्ठा list_head bcn;
पूर्ण;

काष्ठा ath11k_dbg_htt_stats अणु
	u8 type;
	u8 reset;
	काष्ठा debug_htt_stats_req *stats_req;
	/* protects shared stats req buffer */
	spinlock_t lock;
पूर्ण;

काष्ठा ath11k_debug अणु
	काष्ठा dentry *debugfs_pdev;
	काष्ठा ath11k_dbg_htt_stats htt_stats;
	u32 extd_tx_stats;
	काष्ठा ath11k_fw_stats fw_stats;
	काष्ठा completion fw_stats_complete;
	bool fw_stats_करोne;
	u32 extd_rx_stats;
	u32 pktlog_filter;
	u32 pktlog_mode;
	u32 pktlog_peer_valid;
	u8 pktlog_peer_addr[ETH_ALEN];
	u32 rx_filter;
पूर्ण;

काष्ठा ath11k_per_peer_tx_stats अणु
	u32 succ_bytes;
	u32 retry_bytes;
	u32 failed_bytes;
	u16 succ_pkts;
	u16 retry_pkts;
	u16 failed_pkts;
	u32 duration;
	u8 ba_fails;
	bool is_ampdu;
पूर्ण;

#घोषणा ATH11K_FLUSH_TIMEOUT (5 * HZ)
#घोषणा ATH11K_VDEV_DELETE_TIMEOUT_HZ (5 * HZ)

काष्ठा ath11k अणु
	काष्ठा ath11k_base *ab;
	काष्ठा ath11k_pdev *pdev;
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_ops *ops;
	काष्ठा ath11k_pdev_wmi *wmi;
	काष्ठा ath11k_pdev_dp dp;
	u8 mac_addr[ETH_ALEN];
	u32 ht_cap_info;
	u32 vht_cap_info;
	काष्ठा ath11k_he ar_he;
	क्रमागत ath11k_state state;
	bool supports_6ghz;
	काष्ठा अणु
		काष्ठा completion started;
		काष्ठा completion completed;
		काष्ठा completion on_channel;
		काष्ठा delayed_work समयout;
		क्रमागत ath11k_scan_state state;
		bool is_roc;
		पूर्णांक vdev_id;
		पूर्णांक roc_freq;
		bool roc_notअगरy;
	पूर्ण scan;

	काष्ठा अणु
		काष्ठा ieee80211_supported_band sbands[NUM_NL80211_BANDS];
		काष्ठा ieee80211_sband_अगरtype_data
			अगरtype[NUM_NL80211_BANDS][NUM_NL80211_IFTYPES];
	पूर्ण mac;

	अचिन्हित दीर्घ dev_flags;
	अचिन्हित पूर्णांक filter_flags;
	अचिन्हित दीर्घ monitor_flags;
	u32 min_tx_घातer;
	u32 max_tx_घातer;
	u32 txघातer_limit_2g;
	u32 txघातer_limit_5g;
	u32 txघातer_scale;
	u32 घातer_scale;
	u32 chan_tx_pwr;
	u32 num_stations;
	u32 max_num_stations;
	bool monitor_present;
	/* To synchronize concurrent synchronous mac80211 callback operations,
	 * concurrent debugfs configuration and concurrent FW statistics events.
	 */
	काष्ठा mutex conf_mutex;
	/* protects the radio specअगरic data like debug stats, ppdu_stats_info stats,
	 * vdev_stop_status info, scan data, ath11k_sta info, ath11k_vअगर info,
	 * channel context data, survey info, test mode data.
	 */
	spinlock_t data_lock;

	काष्ठा list_head arvअगरs;
	/* should never be शून्य; needed क्रम regular htt rx */
	काष्ठा ieee80211_channel *rx_channel;

	/* valid during scan; needed क्रम mgmt rx during scan */
	काष्ठा ieee80211_channel *scan_channel;

	u8 cfg_tx_chainmask;
	u8 cfg_rx_chainmask;
	u8 num_rx_chains;
	u8 num_tx_chains;
	/* pdev_idx starts from 0 whereas pdev->pdev_id starts with 1 */
	u8 pdev_idx;
	u8 lmac_id;

	काष्ठा completion peer_assoc_करोne;
	काष्ठा completion peer_delete_करोne;

	पूर्णांक install_key_status;
	काष्ठा completion install_key_करोne;

	पूर्णांक last_wmi_vdev_start_status;
	काष्ठा completion vdev_setup_करोne;
	काष्ठा completion vdev_delete_करोne;

	पूर्णांक num_peers;
	पूर्णांक max_num_peers;
	u32 num_started_vdevs;
	u32 num_created_vdevs;
	अचिन्हित दीर्घ दीर्घ allocated_vdev_map;

	काष्ठा idr txmgmt_idr;
	/* protects txmgmt_idr data */
	spinlock_t txmgmt_idr_lock;
	atomic_t num_pending_mgmt_tx;

	/* cycle count is reported twice क्रम each visited channel during scan.
	 * access रक्षित by data_lock
	 */
	u32 survey_last_rx_clear_count;
	u32 survey_last_cycle_count;

	/* Channel info events are expected to come in pairs without and with
	 * COMPLETE flag set respectively क्रम each channel visit during scan.
	 *
	 * However there are deviations from this rule. This flag is used to
	 * aव्योम reporting garbage data.
	 */
	bool ch_info_can_report_survey;
	काष्ठा survey_info survey[ATH11K_NUM_CHANS];
	काष्ठा completion bss_survey_करोne;

	काष्ठा work_काष्ठा regd_update_work;

	काष्ठा work_काष्ठा wmi_mgmt_tx_work;
	काष्ठा sk_buff_head wmi_mgmt_tx_queue;

	काष्ठा ath11k_per_peer_tx_stats peer_tx_stats;
	काष्ठा list_head ppdu_stats_info;
	u32 ppdu_stat_list_depth;

	काष्ठा ath11k_per_peer_tx_stats cached_stats;
	u32 last_ppdu_id;
	u32 cached_ppdu_id;
#अगर_घोषित CONFIG_ATH11K_DEBUGFS
	काष्ठा ath11k_debug debug;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATH11K_SPECTRAL
	काष्ठा ath11k_spectral spectral;
#पूर्ण_अगर
	bool dfs_block_radar_events;
	काष्ठा ath11k_thermal thermal;
पूर्ण;

काष्ठा ath11k_band_cap अणु
	u32 phy_id;
	u32 max_bw_supported;
	u32 ht_cap_info;
	u32 he_cap_info[2];
	u32 he_mcs;
	u32 he_cap_phy_info[PSOC_HOST_MAX_PHY_SIZE];
	काष्ठा ath11k_ppe_threshold he_ppet;
	u16 he_6ghz_capa;
पूर्ण;

काष्ठा ath11k_pdev_cap अणु
	u32 supported_bands;
	u32 ampdu_density;
	u32 vht_cap;
	u32 vht_mcs;
	u32 he_mcs;
	u32 tx_chain_mask;
	u32 rx_chain_mask;
	u32 tx_chain_mask_shअगरt;
	u32 rx_chain_mask_shअगरt;
	काष्ठा ath11k_band_cap band[NUM_NL80211_BANDS];
पूर्ण;

काष्ठा ath11k_pdev अणु
	काष्ठा ath11k *ar;
	u32 pdev_id;
	काष्ठा ath11k_pdev_cap cap;
	u8 mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा ath11k_board_data अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर व्योम *data;
	माप_प्रकार len;
पूर्ण;

काष्ठा ath11k_bus_params अणु
	bool mhi_support;
	bool m3_fw_support;
	bool fixed_bdf_addr;
	bool fixed_mem_region;
	bool अटल_winकरोw_map;
पूर्ण;

/* IPQ8074 HW channel counters frequency value in hertz */
#घोषणा IPQ8074_CC_FREQ_HERTZ 320000

काष्ठा ath11k_bp_stats अणु
	/* Head Poपूर्णांकer reported by the last HTT Backpressure event क्रम the ring */
	u16 hp;

	/* Tail Poपूर्णांकer reported by the last HTT Backpressure event क्रम the ring */
	u16 tp;

	/* Number of Backpressure events received क्रम the ring */
	u32 count;

	/* Last recorded event बारtamp */
	अचिन्हित दीर्घ jअगरfies;
पूर्ण;

काष्ठा ath11k_dp_ring_bp_stats अणु
	काष्ठा ath11k_bp_stats umac_ring_bp_stats[HTT_SW_UMAC_RING_IDX_MAX];
	काष्ठा ath11k_bp_stats lmac_ring_bp_stats[HTT_SW_LMAC_RING_IDX_MAX][MAX_RADIOS];
पूर्ण;

काष्ठा ath11k_soc_dp_tx_err_stats अणु
	/* TCL Ring Descriptor unavailable */
	u32 desc_na[DP_TCL_NUM_RING_MAX];
	/* Other failures during dp_tx due to mem allocation failure
	 * idr unavailable etc.
	 */
	atomic_t misc_fail;
पूर्ण;

काष्ठा ath11k_soc_dp_stats अणु
	u32 err_ring_pkts;
	u32 invalid_rbm;
	u32 rxdma_error[HAL_REO_ENTR_RING_RXDMA_ECODE_MAX];
	u32 reo_error[HAL_REO_DEST_RING_ERROR_CODE_MAX];
	u32 hal_reo_error[DP_REO_DST_RING_MAX];
	काष्ठा ath11k_soc_dp_tx_err_stats tx_err;
	काष्ठा ath11k_dp_ring_bp_stats bp_stats;
पूर्ण;

/* Master काष्ठाure to hold the hw data which may be used in core module */
काष्ठा ath11k_base अणु
	क्रमागत ath11k_hw_rev hw_rev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *dev;
	काष्ठा ath11k_qmi qmi;
	काष्ठा ath11k_wmi_base wmi_ab;
	काष्ठा completion fw_पढ़ोy;
	पूर्णांक num_radios;
	/* HW channel counters frequency value in hertz common to all MACs */
	u32 cc_freq_hz;

	काष्ठा ath11k_htc htc;

	काष्ठा ath11k_dp dp;

	व्योम __iomem *mem;
	अचिन्हित दीर्घ mem_len;

	काष्ठा अणु
		क्रमागत ath11k_bus bus;
		स्थिर काष्ठा ath11k_hअगर_ops *ops;
	पूर्ण hअगर;

	काष्ठा अणु
		काष्ठा completion wakeup_completed;
	पूर्ण wow;

	काष्ठा ath11k_ce ce;
	काष्ठा समयr_list rx_replenish_retry;
	काष्ठा ath11k_hal hal;
	/* To synchronize core_start/core_stop */
	काष्ठा mutex core_lock;
	/* Protects data like peers */
	spinlock_t base_lock;
	काष्ठा ath11k_pdev pdevs[MAX_RADIOS];
	काष्ठा ath11k_pdev __rcu *pdevs_active[MAX_RADIOS];
	काष्ठा ath11k_hal_reg_capabilities_ext hal_reg_cap[MAX_RADIOS];
	अचिन्हित दीर्घ दीर्घ मुक्त_vdev_map;
	काष्ठा list_head peers;
	रुको_queue_head_t peer_mapping_wq;
	u8 mac_addr[ETH_ALEN];
	bool wmi_पढ़ोy;
	u32 wlan_init_status;
	पूर्णांक irq_num[ATH11K_IRQ_NUM_MAX];
	काष्ठा ath11k_ext_irq_grp ext_irq_grp[ATH11K_EXT_IRQ_GRP_NUM_MAX];
	काष्ठा napi_काष्ठा *napi;
	काष्ठा ath11k_targ_cap target_caps;
	u32 ext_service_biपंचांगap[WMI_SERVICE_EXT_BM_SIZE];
	bool pdevs_macaddr_valid;
	पूर्णांक bd_api;

	काष्ठा ath11k_hw_params hw_params;
	काष्ठा ath11k_bus_params bus_params;

	स्थिर काष्ठा firmware *cal_file;

	/* Below regd's are रक्षित by ab->data_lock */
	/* This is the regd set क्रम every radio
	 * by the firmware during initializatin
	 */
	काष्ठा ieee80211_regकरोमुख्य *शेष_regd[MAX_RADIOS];
	/* This regd is set during dynamic country setting
	 * This may or may not be used during the runसमय
	 */
	काष्ठा ieee80211_regकरोमुख्य *new_regd[MAX_RADIOS];

	/* Current DFS Regulatory */
	क्रमागत ath11k_dfs_region dfs_region;
#अगर_घोषित CONFIG_ATH11K_DEBUGFS
	काष्ठा dentry *debugfs_soc;
	काष्ठा dentry *debugfs_ath11k;
#पूर्ण_अगर
	काष्ठा ath11k_soc_dp_stats soc_stats;

	अचिन्हित दीर्घ dev_flags;
	काष्ठा completion driver_recovery;
	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा work_काष्ठा restart_work;
	काष्ठा अणु
		/* रक्षित by data_lock */
		u32 fw_crash_counter;
	पूर्ण stats;
	u32 pktlog_defs_checksum;

	काष्ठा ath11k_dbring_cap *db_caps;
	u32 num_db_cap;

	काष्ठा समयr_list mon_reap_समयr;

	काष्ठा completion htc_suspend;

	/* must be last */
	u8 drv_priv[0] __aligned(माप(व्योम *));
पूर्ण;

काष्ठा ath11k_fw_stats_pdev अणु
	काष्ठा list_head list;

	/* PDEV stats */
	s32 ch_noise_न्यूनमान;
	/* Cycles spent transmitting frames */
	u32 tx_frame_count;
	/* Cycles spent receiving frames */
	u32 rx_frame_count;
	/* Total channel busy समय, evidently */
	u32 rx_clear_count;
	/* Total on-channel समय */
	u32 cycle_count;
	u32 phy_err_count;
	u32 chan_tx_घातer;
	u32 ack_rx_bad;
	u32 rts_bad;
	u32 rts_good;
	u32 fcs_bad;
	u32 no_beacons;
	u32 mib_पूर्णांक_count;

	/* PDEV TX stats */
	/* Num HTT cookies queued to dispatch list */
	s32 comp_queued;
	/* Num HTT cookies dispatched */
	s32 comp_delivered;
	/* Num MSDU queued to WAL */
	s32 msdu_enqued;
	/* Num MPDU queue to WAL */
	s32 mpdu_enqued;
	/* Num MSDUs dropped by WMM limit */
	s32 wmm_drop;
	/* Num Local frames queued */
	s32 local_enqued;
	/* Num Local frames करोne */
	s32 local_मुक्तd;
	/* Num queued to HW */
	s32 hw_queued;
	/* Num PPDU reaped from HW */
	s32 hw_reaped;
	/* Num underruns */
	s32 underrun;
	/* Num PPDUs cleaned up in TX पात */
	s32 tx_पात;
	/* Num MPDUs requed by SW */
	s32 mpdus_requed;
	/* excessive retries */
	u32 tx_ko;
	/* data hw rate code */
	u32 data_rc;
	/* Scheduler self triggers */
	u32 self_triggers;
	/* frames dropped due to excessive sw retries */
	u32 sw_retry_failure;
	/* illegal rate phy errors	*/
	u32 illgl_rate_phy_err;
	/* wal pdev continuous xretry */
	u32 pdev_cont_xretry;
	/* wal pdev tx समयouts */
	u32 pdev_tx_समयout;
	/* wal pdev resets */
	u32 pdev_resets;
	/* frames dropped due to non-availability of stateless TIDs */
	u32 stateless_tid_alloc_failure;
	/* PhY/BB underrun */
	u32 phy_underrun;
	/* MPDU is more than txop limit */
	u32 txop_ovf;

	/* PDEV RX stats */
	/* Cnts any change in ring routing mid-ppdu */
	s32 mid_ppdu_route_change;
	/* Total number of statuses processed */
	s32 status_rcvd;
	/* Extra frags on rings 0-3 */
	s32 r0_frags;
	s32 r1_frags;
	s32 r2_frags;
	s32 r3_frags;
	/* MSDUs / MPDUs delivered to HTT */
	s32 htt_msdus;
	s32 htt_mpdus;
	/* MSDUs / MPDUs delivered to local stack */
	s32 loc_msdus;
	s32 loc_mpdus;
	/* AMSDUs that have more MSDUs than the status ring size */
	s32 oversize_amsdu;
	/* Number of PHY errors */
	s32 phy_errs;
	/* Number of PHY errors drops */
	s32 phy_err_drop;
	/* Number of mpdu errors - FCS, MIC, ENC etc. */
	s32 mpdu_errs;
पूर्ण;

काष्ठा ath11k_fw_stats_vdev अणु
	काष्ठा list_head list;

	u32 vdev_id;
	u32 beacon_snr;
	u32 data_snr;
	u32 num_tx_frames[WLAN_MAX_AC];
	u32 num_rx_frames;
	u32 num_tx_frames_retries[WLAN_MAX_AC];
	u32 num_tx_frames_failures[WLAN_MAX_AC];
	u32 num_rts_fail;
	u32 num_rts_success;
	u32 num_rx_err;
	u32 num_rx_discard;
	u32 num_tx_not_acked;
	u32 tx_rate_history[MAX_TX_RATE_VALUES];
	u32 beacon_rssi_history[MAX_TX_RATE_VALUES];
पूर्ण;

काष्ठा ath11k_fw_stats_bcn अणु
	काष्ठा list_head list;

	u32 vdev_id;
	u32 tx_bcn_succ_cnt;
	u32 tx_bcn_outage_cnt;
पूर्ण;

बाह्य स्थिर काष्ठा ce_pipe_config ath11k_target_ce_config_wlan_ipq8074[];
बाह्य स्थिर काष्ठा service_to_pipe ath11k_target_service_to_ce_map_wlan_ipq8074[];
बाह्य स्थिर काष्ठा service_to_pipe ath11k_target_service_to_ce_map_wlan_ipq6018[];

बाह्य स्थिर काष्ठा ce_pipe_config ath11k_target_ce_config_wlan_qca6390[];
बाह्य स्थिर काष्ठा service_to_pipe ath11k_target_service_to_ce_map_wlan_qca6390[];

बाह्य स्थिर काष्ठा ce_pipe_config ath11k_target_ce_config_wlan_qcn9074[];
बाह्य स्थिर काष्ठा service_to_pipe ath11k_target_service_to_ce_map_wlan_qcn9074[];
पूर्णांक ath11k_core_qmi_firmware_पढ़ोy(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_core_pre_init(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_core_init(काष्ठा ath11k_base *ath11k);
व्योम ath11k_core_deinit(काष्ठा ath11k_base *ath11k);
काष्ठा ath11k_base *ath11k_core_alloc(काष्ठा device *dev, माप_प्रकार priv_size,
				      क्रमागत ath11k_bus bus,
				      स्थिर काष्ठा ath11k_bus_params *bus_params);
व्योम ath11k_core_मुक्त(काष्ठा ath11k_base *ath11k);
पूर्णांक ath11k_core_fetch_bdf(काष्ठा ath11k_base *ath11k,
			  काष्ठा ath11k_board_data *bd);
व्योम ath11k_core_मुक्त_bdf(काष्ठा ath11k_base *ab, काष्ठा ath11k_board_data *bd);
पूर्णांक ath11k_core_check_dt(काष्ठा ath11k_base *ath11k);

व्योम ath11k_core_halt(काष्ठा ath11k *ar);
पूर्णांक ath11k_core_resume(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_core_suspend(काष्ठा ath11k_base *ab);

स्थिर काष्ठा firmware *ath11k_core_firmware_request(काष्ठा ath11k_base *ab,
						    स्थिर अक्षर *filename);

अटल अंतरभूत स्थिर अक्षर *ath11k_scan_state_str(क्रमागत ath11k_scan_state state)
अणु
	चयन (state) अणु
	हाल ATH11K_SCAN_IDLE:
		वापस "idle";
	हाल ATH11K_SCAN_STARTING:
		वापस "starting";
	हाल ATH11K_SCAN_RUNNING:
		वापस "running";
	हाल ATH11K_SCAN_ABORTING:
		वापस "aborting";
	पूर्ण

	वापस "unknown";
पूर्ण

अटल अंतरभूत काष्ठा ath11k_skb_cb *ATH11K_SKB_CB(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा ath11k_skb_cb) >
		     IEEE80211_TX_INFO_DRIVER_DATA_SIZE);
	वापस (काष्ठा ath11k_skb_cb *)&IEEE80211_SKB_CB(skb)->driver_data;
पूर्ण

अटल अंतरभूत काष्ठा ath11k_skb_rxcb *ATH11K_SKB_RXCB(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा ath11k_skb_rxcb) > माप(skb->cb));
	वापस (काष्ठा ath11k_skb_rxcb *)skb->cb;
पूर्ण

अटल अंतरभूत काष्ठा ath11k_vअगर *ath11k_vअगर_to_arvअगर(काष्ठा ieee80211_vअगर *vअगर)
अणु
	वापस (काष्ठा ath11k_vअगर *)vअगर->drv_priv;
पूर्ण

अटल अंतरभूत काष्ठा ath11k *ath11k_ab_to_ar(काष्ठा ath11k_base *ab,
					     पूर्णांक mac_id)
अणु
	वापस ab->pdevs[ath11k_hw_mac_id_to_pdev_id(&ab->hw_params, mac_id)].ar;
पूर्ण

अटल अंतरभूत व्योम ath11k_core_create_firmware_path(काष्ठा ath11k_base *ab,
						    स्थिर अक्षर *filename,
						    व्योम *buf, माप_प्रकार buf_len)
अणु
	snम_लिखो(buf, buf_len, "%s/%s/%s", ATH11K_FW_सूची,
		 ab->hw_params.fw.dir, filename);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *ath11k_bus_str(क्रमागत ath11k_bus bus)
अणु
	चयन (bus) अणु
	हाल ATH11K_BUS_PCI:
		वापस "pci";
	हाल ATH11K_BUS_AHB:
		वापस "ahb";
	पूर्ण

	वापस "unknown";
पूर्ण

#पूर्ण_अगर /* _CORE_H_ */
