<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments. All rights reserved.
 */

#अगर_अघोषित __WL18XX_ACX_H__
#घोषणा __WL18XX_ACX_H__

#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/acx.h"

क्रमागत अणु
	ACX_NS_IPV6_FILTER		 = 0x0050,
	ACX_PEER_HT_OPERATION_MODE_CFG	 = 0x0051,
	ACX_CSUM_CONFIG			 = 0x0052,
	ACX_SIM_CONFIG			 = 0x0053,
	ACX_CLEAR_STATISTICS		 = 0x0054,
	ACX_AUTO_RX_STREAMING		 = 0x0055,
	ACX_PEER_CAP			 = 0x0056,
	ACX_INTERRUPT_NOTIFY		 = 0x0057,
	ACX_RX_BA_FILTER		 = 0x0058,
	ACX_AP_SLEEP_CFG                 = 0x0059,
	ACX_DYNAMIC_TRACES_CFG		 = 0x005A,
	ACX_TIME_SYNC_CFG		 = 0x005B,
पूर्ण;

/* numbers of bits the length field takes (add 1 क्रम the actual number) */
#घोषणा WL18XX_HOST_IF_LEN_SIZE_FIELD 15

#घोषणा WL18XX_ACX_EVENTS_VECTOR	(WL1271_ACX_INTR_WATCHDOG	| \
					 WL1271_ACX_INTR_INIT_COMPLETE	| \
					 WL1271_ACX_INTR_EVENT_A	| \
					 WL1271_ACX_INTR_EVENT_B	| \
					 WL1271_ACX_INTR_CMD_COMPLETE	| \
					 WL1271_ACX_INTR_HW_AVAILABLE	| \
					 WL1271_ACX_INTR_DATA		| \
					 WL1271_ACX_SW_INTR_WATCHDOG)

#घोषणा WL18XX_INTR_MASK		(WL1271_ACX_INTR_WATCHDOG	| \
					 WL1271_ACX_INTR_EVENT_A	| \
					 WL1271_ACX_INTR_EVENT_B	| \
					 WL1271_ACX_INTR_HW_AVAILABLE	| \
					 WL1271_ACX_INTR_DATA		| \
					 WL1271_ACX_SW_INTR_WATCHDOG)

काष्ठा wl18xx_acx_host_config_biपंचांगap अणु
	काष्ठा acx_header header;

	__le32 host_cfg_biपंचांगap;

	__le32 host_sdio_block_size;

	/* extra mem blocks per frame in TX. */
	__le32 extra_mem_blocks;

	/*
	 * number of bits of the length field in the first TX word
	 * (up to 15 - क्रम using the entire 16 bits).
	 */
	__le32 length_field_size;

पूर्ण __packed;

क्रमागत अणु
	CHECKSUM_OFFLOAD_DISABLED = 0,
	CHECKSUM_OFFLOAD_ENABLED  = 1,
	CHECKSUM_OFFLOAD_FAKE_RX  = 2,
	CHECKSUM_OFFLOAD_INVALID  = 0xFF
पूर्ण;

काष्ठा wl18xx_acx_checksum_state अणु
	काष्ठा acx_header header;

	 /* क्रमागत acx_checksum_state */
	u8 checksum_state;
	u8 pad[3];
पूर्ण __packed;


काष्ठा wl18xx_acx_error_stats अणु
	u32 error_frame_non_ctrl;
	u32 error_frame_ctrl;
	u32 error_frame_during_protection;
	u32 null_frame_tx_start;
	u32 null_frame_cts_start;
	u32 bar_retry;
	u32 num_frame_cts_nul_flid;
	u32 tx_पात_failure;
	u32 tx_resume_failure;
	u32 rx_cmplt_db_overflow_cnt;
	u32 elp_जबतक_rx_exch;
	u32 elp_जबतक_tx_exch;
	u32 elp_जबतक_tx;
	u32 elp_जबतक_nvic_pending;
	u32 rx_excessive_frame_len;
	u32 burst_mismatch;
	u32 tbc_exch_mismatch;
पूर्ण __packed;

#घोषणा NUM_OF_RATES_INDEXES 30
काष्ठा wl18xx_acx_tx_stats अणु
	u32 tx_prepared_descs;
	u32 tx_cmplt;
	u32 tx_ढाँचा_prepared;
	u32 tx_data_prepared;
	u32 tx_ढाँचा_programmed;
	u32 tx_data_programmed;
	u32 tx_burst_programmed;
	u32 tx_starts;
	u32 tx_stop;
	u32 tx_start_ढाँचाs;
	u32 tx_start_पूर्णांक_ढाँचाs;
	u32 tx_start_fw_gen;
	u32 tx_start_data;
	u32 tx_start_null_frame;
	u32 tx_exch;
	u32 tx_retry_ढाँचा;
	u32 tx_retry_data;
	u32 tx_retry_per_rate[NUM_OF_RATES_INDEXES];
	u32 tx_exch_pending;
	u32 tx_exch_expiry;
	u32 tx_करोne_ढाँचा;
	u32 tx_करोne_data;
	u32 tx_करोne_पूर्णांक_ढाँचा;
	u32 tx_cfe1;
	u32 tx_cfe2;
	u32 frag_called;
	u32 frag_mpdu_alloc_failed;
	u32 frag_init_called;
	u32 frag_in_process_called;
	u32 frag_tkip_called;
	u32 frag_key_not_found;
	u32 frag_need_fragmentation;
	u32 frag_bad_mblk_num;
	u32 frag_failed;
	u32 frag_cache_hit;
	u32 frag_cache_miss;
पूर्ण __packed;

काष्ठा wl18xx_acx_rx_stats अणु
	u32 rx_beacon_early_term;
	u32 rx_out_of_mpdu_nodes;
	u32 rx_hdr_overflow;
	u32 rx_dropped_frame;
	u32 rx_करोne_stage;
	u32 rx_करोne;
	u32 rx_defrag;
	u32 rx_defrag_end;
	u32 rx_cmplt;
	u32 rx_pre_complt;
	u32 rx_cmplt_task;
	u32 rx_phy_hdr;
	u32 rx_समयout;
	u32 rx_rts_समयout;
	u32 rx_समयout_wa;
	u32 defrag_called;
	u32 defrag_init_called;
	u32 defrag_in_process_called;
	u32 defrag_tkip_called;
	u32 defrag_need_defrag;
	u32 defrag_decrypt_failed;
	u32 decrypt_key_not_found;
	u32 defrag_need_decrypt;
	u32 rx_tkip_replays;
	u32 rx_xfr;
पूर्ण __packed;

काष्ठा wl18xx_acx_isr_stats अणु
	u32 irqs;
पूर्ण __packed;

#घोषणा PWR_STAT_MAX_CONT_MISSED_BCNS_SPREAD 10

काष्ठा wl18xx_acx_pwr_stats अणु
	u32 missing_bcns_cnt;
	u32 rcvd_bcns_cnt;
	u32 connection_out_of_sync;
	u32 cont_miss_bcns_spपढ़ो[PWR_STAT_MAX_CONT_MISSED_BCNS_SPREAD];
	u32 rcvd_awake_bcns_cnt;
	u32 sleep_समय_count;
	u32 sleep_समय_avg;
	u32 sleep_cycle_avg;
	u32 sleep_percent;
	u32 ap_sleep_active_conf;
	u32 ap_sleep_user_conf;
	u32 ap_sleep_counter;
पूर्ण __packed;

काष्ठा wl18xx_acx_rx_filter_stats अणु
	u32 beacon_filter;
	u32 arp_filter;
	u32 mc_filter;
	u32 dup_filter;
	u32 data_filter;
	u32 ibss_filter;
	u32 protection_filter;
	u32 accum_arp_pend_requests;
	u32 max_arp_queue_dep;
पूर्ण __packed;

काष्ठा wl18xx_acx_rx_rate_stats अणु
	u32 rx_frames_per_rates[50];
पूर्ण __packed;

#घोषणा AGGR_STATS_TX_AGG	16
#घोषणा AGGR_STATS_RX_SIZE_LEN	16

काष्ठा wl18xx_acx_aggr_stats अणु
	u32 tx_agg_rate[AGGR_STATS_TX_AGG];
	u32 tx_agg_len[AGGR_STATS_TX_AGG];
	u32 rx_size[AGGR_STATS_RX_SIZE_LEN];
पूर्ण __packed;

#घोषणा PIPE_STATS_HW_FIFO	11

काष्ठा wl18xx_acx_pipeline_stats अणु
	u32 hs_tx_stat_fअगरo_पूर्णांक;
	u32 hs_rx_stat_fअगरo_पूर्णांक;
	u32 enc_tx_stat_fअगरo_पूर्णांक;
	u32 enc_rx_stat_fअगरo_पूर्णांक;
	u32 rx_complete_stat_fअगरo_पूर्णांक;
	u32 pre_proc_swi;
	u32 post_proc_swi;
	u32 sec_frag_swi;
	u32 pre_to_defrag_swi;
	u32 defrag_to_rx_xfer_swi;
	u32 dec_packet_in;
	u32 dec_packet_in_fअगरo_full;
	u32 dec_packet_out;
	u16 pipeline_fअगरo_full[PIPE_STATS_HW_FIFO];
	u16 padding;
पूर्ण __packed;

#घोषणा DIVERSITY_STATS_NUM_OF_ANT	2

काष्ठा wl18xx_acx_भागersity_stats अणु
	u32 num_of_packets_per_ant[DIVERSITY_STATS_NUM_OF_ANT];
	u32 total_num_of_toggles;
पूर्ण __packed;

काष्ठा wl18xx_acx_thermal_stats अणु
	u16 irq_thr_low;
	u16 irq_thr_high;
	u16 tx_stop;
	u16 tx_resume;
	u16 false_irq;
	u16 adc_source_unexpected;
पूर्ण __packed;

#घोषणा WL18XX_NUM_OF_CALIBRATIONS_ERRORS 18
काष्ठा wl18xx_acx_calib_failure_stats अणु
	u16 fail_count[WL18XX_NUM_OF_CALIBRATIONS_ERRORS];
	u32 calib_count;
पूर्ण __packed;

काष्ठा wl18xx_roaming_stats अणु
	s32 rssi_level;
पूर्ण __packed;

काष्ठा wl18xx_dfs_stats अणु
	u32 num_of_radar_detections;
पूर्ण __packed;

काष्ठा wl18xx_acx_statistics अणु
	काष्ठा acx_header header;

	काष्ठा wl18xx_acx_error_stats		error;
	काष्ठा wl18xx_acx_tx_stats		tx;
	काष्ठा wl18xx_acx_rx_stats		rx;
	काष्ठा wl18xx_acx_isr_stats		isr;
	काष्ठा wl18xx_acx_pwr_stats		pwr;
	काष्ठा wl18xx_acx_rx_filter_stats	rx_filter;
	काष्ठा wl18xx_acx_rx_rate_stats		rx_rate;
	काष्ठा wl18xx_acx_aggr_stats		aggr_size;
	काष्ठा wl18xx_acx_pipeline_stats	pipeline;
	काष्ठा wl18xx_acx_भागersity_stats	भागersity;
	काष्ठा wl18xx_acx_thermal_stats		thermal;
	काष्ठा wl18xx_acx_calib_failure_stats	calib;
	काष्ठा wl18xx_roaming_stats		roaming;
	काष्ठा wl18xx_dfs_stats			dfs;
पूर्ण __packed;

काष्ठा wl18xx_acx_clear_statistics अणु
	काष्ठा acx_header header;
पूर्ण;

क्रमागत wlcore_bandwidth अणु
	WLCORE_BANDWIDTH_20MHZ,
	WLCORE_BANDWIDTH_40MHZ,
पूर्ण;

काष्ठा wlcore_peer_ht_operation_mode अणु
	काष्ठा acx_header header;

	u8 hlid;
	u8 bandwidth; /* क्रमागत wlcore_bandwidth */
	u8 padding[2];
पूर्ण;

/*
 * ACX_PEER_CAP
 * this काष्ठा is very similar to wl1271_acx_ht_capabilities, with the
 * addition of supported rates
 */
काष्ठा wlcore_acx_peer_cap अणु
	काष्ठा acx_header header;

	/* biपंचांगask of capability bits supported by the peer */
	__le32 ht_capabilites;

	/* rates supported by the remote peer */
	__le32 supported_rates;

	/* Indicates to which link these capabilities apply. */
	u8 hlid;

	/*
	 * This the maximum A-MPDU length supported by the AP. The FW may not
	 * exceed this length when sending A-MPDUs
	 */
	u8 ampdu_max_length;

	/* This is the minimal spacing required when sending A-MPDUs to the AP*/
	u8 ampdu_min_spacing;

	u8 padding;
पूर्ण __packed;

/*
 * ACX_INTERRUPT_NOTIFY
 * enable/disable fast-link/PSM notअगरication from FW
 */
काष्ठा wl18xx_acx_पूर्णांकerrupt_notअगरy अणु
	काष्ठा acx_header header;
	u32 enable;
पूर्ण;

/*
 * ACX_RX_BA_FILTER
 * enable/disable RX BA filtering in FW
 */
काष्ठा wl18xx_acx_rx_ba_filter अणु
	काष्ठा acx_header header;
	u32 enable;
पूर्ण;

काष्ठा acx_ap_sleep_cfg अणु
	काष्ठा acx_header header;
	/* Duty Cycle (20-80% of staying Awake) क्रम IDLE AP
	 * (0: disable)
	 */
	u8 idle_duty_cycle;
	/* Duty Cycle (20-80% of staying Awake) क्रम Connected AP
	 * (0: disable)
	 */
	u8 connected_duty_cycle;
	/* Maximum stations that are allowed to be connected to AP
	 *  (255: no limit)
	 */
	u8 max_stations_thresh;
	/* Timeout till enabling the Sleep Mechanism after data stops
	 * [unit: 100 msec]
	 */
	u8 idle_conn_thresh;
पूर्ण __packed;

/*
 * ACX_DYNAMIC_TRACES_CFG
 * configure the FW dynamic traces
 */
काष्ठा acx_dynamic_fw_traces_cfg अणु
	काष्ठा acx_header header;
	__le32 dynamic_fw_traces;
पूर्ण __packed;

/*
 * ACX_TIME_SYNC_CFG
 * configure the समय sync parameters
 */
काष्ठा acx_समय_sync_cfg अणु
	काष्ठा acx_header header;
	u8 sync_mode;
	u8 zone_mac_addr[ETH_ALEN];
	u8 padding[1];
पूर्ण __packed;

पूर्णांक wl18xx_acx_host_अगर_cfg_biपंचांगap(काष्ठा wl1271 *wl, u32 host_cfg_biपंचांगap,
				  u32 sdio_blk_size, u32 extra_mem_blks,
				  u32 len_field_size);
पूर्णांक wl18xx_acx_set_checksum_state(काष्ठा wl1271 *wl);
पूर्णांक wl18xx_acx_clear_statistics(काष्ठा wl1271 *wl);
पूर्णांक wl18xx_acx_peer_ht_operation_mode(काष्ठा wl1271 *wl, u8 hlid, bool wide);
पूर्णांक wl18xx_acx_set_peer_cap(काष्ठा wl1271 *wl,
			    काष्ठा ieee80211_sta_ht_cap *ht_cap,
			    bool allow_ht_operation,
			    u32 rate_set, u8 hlid);
पूर्णांक wl18xx_acx_पूर्णांकerrupt_notअगरy_config(काष्ठा wl1271 *wl, bool action);
पूर्णांक wl18xx_acx_rx_ba_filter(काष्ठा wl1271 *wl, bool action);
पूर्णांक wl18xx_acx_ap_sleep(काष्ठा wl1271 *wl);
पूर्णांक wl18xx_acx_dynamic_fw_traces(काष्ठा wl1271 *wl);
पूर्णांक wl18xx_acx_समय_sync_cfg(काष्ठा wl1271 *wl);

#पूर्ण_अगर /* __WL18XX_ACX_H__ */
