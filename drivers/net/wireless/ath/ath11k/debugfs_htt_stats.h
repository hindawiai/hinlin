<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित DEBUG_HTT_STATS_H
#घोषणा DEBUG_HTT_STATS_H

#घोषणा HTT_STATS_COOKIE_LSB    GENMASK_ULL(31, 0)
#घोषणा HTT_STATS_COOKIE_MSB    GENMASK_ULL(63, 32)
#घोषणा HTT_STATS_MAGIC_VALUE   0xF0F0F0F0

क्रमागत htt_tlv_tag_t अणु
	HTT_STATS_TX_PDEV_CMN_TAG                           = 0,
	HTT_STATS_TX_PDEV_UNDERRUN_TAG                      = 1,
	HTT_STATS_TX_PDEV_SIFS_TAG                          = 2,
	HTT_STATS_TX_PDEV_FLUSH_TAG                         = 3,
	HTT_STATS_TX_PDEV_PHY_ERR_TAG                       = 4,
	HTT_STATS_STRING_TAG                                = 5,
	HTT_STATS_TX_HWQ_CMN_TAG                            = 6,
	HTT_STATS_TX_HWQ_DIFS_LATENCY_TAG                   = 7,
	HTT_STATS_TX_HWQ_CMD_RESULT_TAG                     = 8,
	HTT_STATS_TX_HWQ_CMD_STALL_TAG                      = 9,
	HTT_STATS_TX_HWQ_FES_STATUS_TAG                     = 10,
	HTT_STATS_TX_TQM_GEN_MPDU_TAG                       = 11,
	HTT_STATS_TX_TQM_LIST_MPDU_TAG                      = 12,
	HTT_STATS_TX_TQM_LIST_MPDU_CNT_TAG                  = 13,
	HTT_STATS_TX_TQM_CMN_TAG                            = 14,
	HTT_STATS_TX_TQM_PDEV_TAG                           = 15,
	HTT_STATS_TX_TQM_CMDQ_STATUS_TAG                    = 16,
	HTT_STATS_TX_DE_EAPOL_PACKETS_TAG                   = 17,
	HTT_STATS_TX_DE_CLASSIFY_FAILED_TAG                 = 18,
	HTT_STATS_TX_DE_CLASSIFY_STATS_TAG                  = 19,
	HTT_STATS_TX_DE_CLASSIFY_STATUS_TAG                 = 20,
	HTT_STATS_TX_DE_ENQUEUE_PACKETS_TAG                 = 21,
	HTT_STATS_TX_DE_ENQUEUE_DISCARD_TAG                 = 22,
	HTT_STATS_TX_DE_CMN_TAG                             = 23,
	HTT_STATS_RING_IF_TAG                               = 24,
	HTT_STATS_TX_PDEV_MU_MIMO_STATS_TAG                 = 25,
	HTT_STATS_SFM_CMN_TAG                               = 26,
	HTT_STATS_SRING_STATS_TAG                           = 27,
	HTT_STATS_RX_PDEV_FW_STATS_TAG                      = 28,
	HTT_STATS_RX_PDEV_FW_RING_MPDU_ERR_TAG              = 29,
	HTT_STATS_RX_PDEV_FW_MPDU_DROP_TAG                  = 30,
	HTT_STATS_RX_SOC_FW_STATS_TAG                       = 31,
	HTT_STATS_RX_SOC_FW_REFILL_RING_EMPTY_TAG           = 32,
	HTT_STATS_RX_SOC_FW_REFILL_RING_NUM_REFILL_TAG      = 33,
	HTT_STATS_TX_PDEV_RATE_STATS_TAG                    = 34,
	HTT_STATS_RX_PDEV_RATE_STATS_TAG                    = 35,
	HTT_STATS_TX_PDEV_SCHEDULER_TXQ_STATS_TAG           = 36,
	HTT_STATS_TX_SCHED_CMN_TAG                          = 37,
	HTT_STATS_TX_PDEV_MUMIMO_MPDU_STATS_TAG             = 38,
	HTT_STATS_SCHED_TXQ_CMD_POSTED_TAG                  = 39,
	HTT_STATS_RING_IF_CMN_TAG                           = 40,
	HTT_STATS_SFM_CLIENT_USER_TAG                       = 41,
	HTT_STATS_SFM_CLIENT_TAG                            = 42,
	HTT_STATS_TX_TQM_ERROR_STATS_TAG                    = 43,
	HTT_STATS_SCHED_TXQ_CMD_REAPED_TAG                  = 44,
	HTT_STATS_SRING_CMN_TAG                             = 45,
	HTT_STATS_TX_SELFGEN_AC_ERR_STATS_TAG               = 46,
	HTT_STATS_TX_SELFGEN_CMN_STATS_TAG                  = 47,
	HTT_STATS_TX_SELFGEN_AC_STATS_TAG                   = 48,
	HTT_STATS_TX_SELFGEN_AX_STATS_TAG                   = 49,
	HTT_STATS_TX_SELFGEN_AX_ERR_STATS_TAG               = 50,
	HTT_STATS_TX_HWQ_MUMIMO_SCH_STATS_TAG               = 51,
	HTT_STATS_TX_HWQ_MUMIMO_MPDU_STATS_TAG              = 52,
	HTT_STATS_TX_HWQ_MUMIMO_CMN_STATS_TAG               = 53,
	HTT_STATS_HW_INTR_MISC_TAG                          = 54,
	HTT_STATS_HW_WD_TIMEOUT_TAG                         = 55,
	HTT_STATS_HW_PDEV_ERRS_TAG                          = 56,
	HTT_STATS_COUNTER_NAME_TAG                          = 57,
	HTT_STATS_TX_TID_DETAILS_TAG                        = 58,
	HTT_STATS_RX_TID_DETAILS_TAG                        = 59,
	HTT_STATS_PEER_STATS_CMN_TAG                        = 60,
	HTT_STATS_PEER_DETAILS_TAG                          = 61,
	HTT_STATS_PEER_TX_RATE_STATS_TAG                    = 62,
	HTT_STATS_PEER_RX_RATE_STATS_TAG                    = 63,
	HTT_STATS_PEER_MSDU_FLOWQ_TAG                       = 64,
	HTT_STATS_TX_DE_COMPL_STATS_TAG                     = 65,
	HTT_STATS_WHAL_TX_TAG                               = 66,
	HTT_STATS_TX_PDEV_SIFS_HIST_TAG                     = 67,
	HTT_STATS_RX_PDEV_FW_STATS_PHY_ERR_TAG              = 68,
	HTT_STATS_TX_TID_DETAILS_V1_TAG                     = 69,
	HTT_STATS_PDEV_CCA_1SEC_HIST_TAG                    = 70,
	HTT_STATS_PDEV_CCA_100MSEC_HIST_TAG                 = 71,
	HTT_STATS_PDEV_CCA_STAT_CUMULATIVE_TAG              = 72,
	HTT_STATS_PDEV_CCA_COUNTERS_TAG                     = 73,
	HTT_STATS_TX_PDEV_MPDU_STATS_TAG                    = 74,
	HTT_STATS_PDEV_TWT_SESSIONS_TAG                     = 75,
	HTT_STATS_PDEV_TWT_SESSION_TAG                      = 76,
	HTT_STATS_RX_REFILL_RXDMA_ERR_TAG                   = 77,
	HTT_STATS_RX_REFILL_REO_ERR_TAG                     = 78,
	HTT_STATS_RX_REO_RESOURCE_STATS_TAG                 = 79,
	HTT_STATS_TX_SOUNDING_STATS_TAG                     = 80,
	HTT_STATS_TX_PDEV_TX_PPDU_STATS_TAG                 = 81,
	HTT_STATS_TX_PDEV_TRIED_MPDU_CNT_HIST_TAG           = 82,
	HTT_STATS_TX_HWQ_TRIED_MPDU_CNT_HIST_TAG            = 83,
	HTT_STATS_TX_HWQ_TXOP_USED_CNT_HIST_TAG             = 84,
	HTT_STATS_TX_DE_FW2WBM_RING_FULL_HIST_TAG           = 85,
	HTT_STATS_SCHED_TXQ_SCHED_ORDER_SU_TAG              = 86,
	HTT_STATS_SCHED_TXQ_SCHED_INELIGIBILITY_TAG         = 87,
	HTT_STATS_PDEV_OBSS_PD_TAG                          = 88,
	HTT_STATS_HW_WAR_TAG				    = 89,
	HTT_STATS_RING_BACKPRESSURE_STATS_TAG		    = 90,

	HTT_STATS_MAX_TAG,
पूर्ण;

#घोषणा HTT_STATS_MAX_STRING_SZ32            4
#घोषणा HTT_STATS_MACID_INVALID              0xff
#घोषणा HTT_TX_HWQ_MAX_DIFS_LATENCY_BINS     10
#घोषणा HTT_TX_HWQ_MAX_CMD_RESULT_STATS      13
#घोषणा HTT_TX_HWQ_MAX_CMD_STALL_STATS       5
#घोषणा HTT_TX_HWQ_MAX_FES_RESULT_STATS      10

क्रमागत htt_tx_pdev_underrun_क्रमागत अणु
	HTT_STATS_TX_PDEV_NO_DATA_UNDERRUN           = 0,
	HTT_STATS_TX_PDEV_DATA_UNDERRUN_BETWEEN_MPDU = 1,
	HTT_STATS_TX_PDEV_DATA_UNDERRUN_WITHIN_MPDU  = 2,
	HTT_TX_PDEV_MAX_URRN_STATS                   = 3,
पूर्ण;

#घोषणा HTT_TX_PDEV_MAX_FLUSH_REASON_STATS     71
#घोषणा HTT_TX_PDEV_MAX_SIFS_BURST_STATS       9
#घोषणा HTT_TX_PDEV_MAX_SIFS_BURST_HIST_STATS  10
#घोषणा HTT_TX_PDEV_MAX_PHY_ERR_STATS          18
#घोषणा HTT_TX_PDEV_SCHED_TX_MODE_MAX          4
#घोषणा HTT_TX_PDEV_NUM_SCHED_ORDER_LOG        20

#घोषणा HTT_RX_STATS_REFILL_MAX_RING         4
#घोषणा HTT_RX_STATS_RXDMA_MAX_ERR           16
#घोषणा HTT_RX_STATS_FW_DROP_REASON_MAX      16

/* Bytes stored in little endian order */
/* Length should be multiple of DWORD */
काष्ठा htt_stats_string_tlv अणु
	u32 data[0]; /* Can be variable length */
पूर्ण __packed;

/* == TX PDEV STATS == */
काष्ठा htt_tx_pdev_stats_cmn_tlv अणु
	u32 mac_id__word;
	u32 hw_queued;
	u32 hw_reaped;
	u32 underrun;
	u32 hw_छोड़ोd;
	u32 hw_flush;
	u32 hw_filt;
	u32 tx_पात;
	u32 mpdu_requed;
	u32 tx_xretry;
	u32 data_rc;
	u32 mpdu_dropped_xretry;
	u32 illgl_rate_phy_err;
	u32 cont_xretry;
	u32 tx_समयout;
	u32 pdev_resets;
	u32 phy_underrun;
	u32 txop_ovf;
	u32 seq_posted;
	u32 seq_failed_queueing;
	u32 seq_completed;
	u32 seq_restarted;
	u32 mu_seq_posted;
	u32 seq_चयन_hw_छोड़ोd;
	u32 next_seq_posted_dsr;
	u32 seq_posted_isr;
	u32 seq_ctrl_cached;
	u32 mpdu_count_tqm;
	u32 msdu_count_tqm;
	u32 mpdu_हटाओd_tqm;
	u32 msdu_हटाओd_tqm;
	u32 mpdus_sw_flush;
	u32 mpdus_hw_filter;
	u32 mpdus_truncated;
	u32 mpdus_ack_failed;
	u32 mpdus_expired;
	u32 mpdus_seq_hw_retry;
	u32 ack_tlv_proc;
	u32 coex_पात_mpdu_cnt_valid;
	u32 coex_पात_mpdu_cnt;
	u32 num_total_ppdus_tried_ota;
	u32 num_data_ppdus_tried_ota;
	u32 local_ctrl_mgmt_enqued;
	u32 local_ctrl_mgmt_मुक्तd;
	u32 local_data_enqued;
	u32 local_data_मुक्तd;
	u32 mpdu_tried;
	u32 isr_रुको_seq_posted;

	u32 tx_active_dur_us_low;
	u32 tx_active_dur_us_high;
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_pdev_stats_urrn_tlv_v अणु
	u32 urrn_stats[0]; /* HTT_TX_PDEV_MAX_URRN_STATS */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_pdev_stats_flush_tlv_v अणु
	u32 flush_errs[0]; /* HTT_TX_PDEV_MAX_FLUSH_REASON_STATS */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_pdev_stats_sअगरs_tlv_v अणु
	u32 sअगरs_status[0]; /* HTT_TX_PDEV_MAX_SIFS_BURST_STATS */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_pdev_stats_phy_err_tlv_v अणु
	u32  phy_errs[0]; /* HTT_TX_PDEV_MAX_PHY_ERR_STATS */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_pdev_stats_sअगरs_hist_tlv_v अणु
	u32 sअगरs_hist_status[0]; /* HTT_TX_PDEV_SIFS_BURST_HIST_STATS */
पूर्ण;

काष्ठा htt_tx_pdev_stats_tx_ppdu_stats_tlv_v अणु
	u32 num_data_ppdus_legacy_su;
	u32 num_data_ppdus_ac_su;
	u32 num_data_ppdus_ax_su;
	u32 num_data_ppdus_ac_su_txbf;
	u32 num_data_ppdus_ax_su_txbf;
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size .
 *
 *  Tried_mpdu_cnt_hist is the histogram of MPDUs tries per HWQ.
 *  The tries here is the count of the  MPDUS within a PPDU that the
 *  HW had attempted to transmit on  air, क्रम the HWSCH Schedule
 *  command submitted by FW.It is not the retry attempts.
 *  The histogram bins are  0-29, 30-59, 60-89 and so on. The are
 *   10 bins in this histogram. They are defined in FW using the
 *  following macros
 *  #घोषणा WAL_MAX_TRIED_MPDU_CNT_HISTOGRAM 9
 *  #घोषणा WAL_TRIED_MPDU_CNT_HISTOGRAM_INTERVAL 30
 */
काष्ठा htt_tx_pdev_stats_tried_mpdu_cnt_hist_tlv_v अणु
	u32 hist_bin_size;
	u32 tried_mpdu_cnt_hist[]; /* HTT_TX_PDEV_TRIED_MPDU_CNT_HIST */
पूर्ण;

/* == SOC ERROR STATS == */

/* =============== PDEV ERROR STATS ============== */
#घोषणा HTT_STATS_MAX_HW_INTR_NAME_LEN 8
काष्ठा htt_hw_stats_पूर्णांकr_misc_tlv अणु
	/* Stored as little endian */
	u8 hw_पूर्णांकr_name[HTT_STATS_MAX_HW_INTR_NAME_LEN];
	u32 mask;
	u32 count;
पूर्ण;

#घोषणा HTT_STATS_MAX_HW_MODULE_NAME_LEN 8
काष्ठा htt_hw_stats_wd_समयout_tlv अणु
	/* Stored as little endian */
	u8 hw_module_name[HTT_STATS_MAX_HW_MODULE_NAME_LEN];
	u32 count;
पूर्ण;

काष्ठा htt_hw_stats_pdev_errs_tlv अणु
	u32    mac_id__word; /* BIT [ 7 :  0] : mac_id */
	u32    tx_पात;
	u32    tx_पात_fail_count;
	u32    rx_पात;
	u32    rx_पात_fail_count;
	u32    warm_reset;
	u32    cold_reset;
	u32    tx_flush;
	u32    tx_glb_reset;
	u32    tx_txq_reset;
	u32    rx_समयout_reset;
पूर्ण;

काष्ठा htt_hw_stats_whal_tx_tlv अणु
	u32 mac_id__word;
	u32 last_unछोड़ो_ppdu_id;
	u32 hwsch_unछोड़ो_रुको_tqm_ग_लिखो;
	u32 hwsch_dummy_tlv_skipped;
	u32 hwsch_misaligned_offset_received;
	u32 hwsch_reset_count;
	u32 hwsch_dev_reset_war;
	u32 hwsch_delayed_छोड़ो;
	u32 hwsch_दीर्घ_delayed_छोड़ो;
	u32 sch_rx_ppdu_no_response;
	u32 sch_selfgen_response;
	u32 sch_rx_sअगरs_resp_trigger;
पूर्ण;

/* ============ PEER STATS ============ */
काष्ठा htt_msdu_flow_stats_tlv अणु
	u32 last_update_बारtamp;
	u32 last_add_बारtamp;
	u32 last_हटाओ_बारtamp;
	u32 total_processed_msdu_count;
	u32 cur_msdu_count_in_flowq;
	u32 sw_peer_id;
	u32 tx_flow_no__tid_num__drop_rule;
	u32 last_cycle_enqueue_count;
	u32 last_cycle_dequeue_count;
	u32 last_cycle_drop_count;
	u32 current_drop_th;
पूर्ण;

#घोषणा MAX_HTT_TID_NAME 8

/* Tidq stats */
काष्ठा htt_tx_tid_stats_tlv अणु
	/* Stored as little endian */
	u8     tid_name[MAX_HTT_TID_NAME];
	u32 sw_peer_id__tid_num;
	u32 num_sched_pending__num_ppdu_in_hwq;
	u32 tid_flags;
	u32 hw_queued;
	u32 hw_reaped;
	u32 mpdus_hw_filter;

	u32 qdepth_bytes;
	u32 qdepth_num_msdu;
	u32 qdepth_num_mpdu;
	u32 last_scheduled_tsmp;
	u32 छोड़ो_module_id;
	u32 block_module_id;
	u32 tid_tx_airसमय;
पूर्ण;

/* Tidq stats */
काष्ठा htt_tx_tid_stats_v1_tlv अणु
	/* Stored as little endian */
	u8 tid_name[MAX_HTT_TID_NAME];
	u32 sw_peer_id__tid_num;
	u32 num_sched_pending__num_ppdu_in_hwq;
	u32 tid_flags;
	u32 max_qdepth_bytes;
	u32 max_qdepth_n_msdus;
	u32 rsvd;

	u32 qdepth_bytes;
	u32 qdepth_num_msdu;
	u32 qdepth_num_mpdu;
	u32 last_scheduled_tsmp;
	u32 छोड़ो_module_id;
	u32 block_module_id;
	u32 tid_tx_airसमय;
	u32 allow_n_flags;
	u32 sendn_frms_allowed;
पूर्ण;

काष्ठा htt_rx_tid_stats_tlv अणु
	u32 sw_peer_id__tid_num;
	u8 tid_name[MAX_HTT_TID_NAME];
	u32 dup_in_reorder;
	u32 dup_past_outside_winकरोw;
	u32 dup_past_within_winकरोw;
	u32 rxdesc_err_decrypt;
	u32 tid_rx_airसमय;
पूर्ण;

#घोषणा HTT_MAX_COUNTER_NAME 8
काष्ठा htt_counter_tlv अणु
	u8 counter_name[HTT_MAX_COUNTER_NAME];
	u32 count;
पूर्ण;

काष्ठा htt_peer_stats_cmn_tlv अणु
	u32 ppdu_cnt;
	u32 mpdu_cnt;
	u32 msdu_cnt;
	u32 छोड़ो_biपंचांगap;
	u32 block_biपंचांगap;
	u32 current_बारtamp;
	u32 peer_tx_airसमय;
	u32 peer_rx_airसमय;
	s32 rssi;
	u32 peer_enqueued_count_low;
	u32 peer_enqueued_count_high;
	u32 peer_dequeued_count_low;
	u32 peer_dequeued_count_high;
	u32 peer_dropped_count_low;
	u32 peer_dropped_count_high;
	u32 ppdu_transmitted_bytes_low;
	u32 ppdu_transmitted_bytes_high;
	u32 peer_ttl_हटाओd_count;
	u32 inactive_समय;
पूर्ण;

काष्ठा htt_peer_details_tlv अणु
	u32 peer_type;
	u32 sw_peer_id;
	u32 vdev_pdev_ast_idx;
	काष्ठा htt_mac_addr mac_addr;
	u32 peer_flags;
	u32 qpeer_flags;
पूर्ण;

क्रमागत htt_stats_param_type अणु
	HTT_STATS_PREAM_OFDM,
	HTT_STATS_PREAM_CCK,
	HTT_STATS_PREAM_HT,
	HTT_STATS_PREAM_VHT,
	HTT_STATS_PREAM_HE,
	HTT_STATS_PREAM_RSVD,
	HTT_STATS_PREAM_RSVD1,

	HTT_STATS_PREAM_COUNT,
पूर्ण;

#घोषणा HTT_TX_PEER_STATS_NUM_MCS_COUNTERS        12
#घोषणा HTT_TX_PEER_STATS_NUM_GI_COUNTERS          4
#घोषणा HTT_TX_PEER_STATS_NUM_DCM_COUNTERS         5
#घोषणा HTT_TX_PEER_STATS_NUM_BW_COUNTERS          4
#घोषणा HTT_TX_PEER_STATS_NUM_SPATIAL_STREAMS      8
#घोषणा HTT_TX_PEER_STATS_NUM_PREAMBLE_TYPES       HTT_STATS_PREAM_COUNT

काष्ठा htt_tx_peer_rate_stats_tlv अणु
	u32 tx_ldpc;
	u32 rts_cnt;
	u32 ack_rssi;

	u32 tx_mcs[HTT_TX_PEER_STATS_NUM_MCS_COUNTERS];
	u32 tx_su_mcs[HTT_TX_PEER_STATS_NUM_MCS_COUNTERS];
	u32 tx_mu_mcs[HTT_TX_PEER_STATS_NUM_MCS_COUNTERS];
	/* element 0,1, ...7 -> NSS 1,2, ...8 */
	u32 tx_nss[HTT_TX_PEER_STATS_NUM_SPATIAL_STREAMS];
	/* element 0: 20 MHz, 1: 40 MHz, 2: 80 MHz, 3: 160 and 80+80 MHz */
	u32 tx_bw[HTT_TX_PEER_STATS_NUM_BW_COUNTERS];
	u32 tx_stbc[HTT_TX_PEER_STATS_NUM_MCS_COUNTERS];
	u32 tx_pream[HTT_TX_PEER_STATS_NUM_PREAMBLE_TYPES];

	/* Counters to track number of tx packets in each GI
	 * (400us, 800us, 1600us & 3200us) in each mcs (0-11)
	 */
	u32 tx_gi[HTT_TX_PEER_STATS_NUM_GI_COUNTERS][HTT_TX_PEER_STATS_NUM_MCS_COUNTERS];

	/* Counters to track packets in dcm mcs (MCS 0, 1, 3, 4) */
	u32 tx_dcm[HTT_TX_PEER_STATS_NUM_DCM_COUNTERS];

पूर्ण;

#घोषणा HTT_RX_PEER_STATS_NUM_MCS_COUNTERS        12
#घोषणा HTT_RX_PEER_STATS_NUM_GI_COUNTERS          4
#घोषणा HTT_RX_PEER_STATS_NUM_DCM_COUNTERS         5
#घोषणा HTT_RX_PEER_STATS_NUM_BW_COUNTERS          4
#घोषणा HTT_RX_PEER_STATS_NUM_SPATIAL_STREAMS      8
#घोषणा HTT_RX_PEER_STATS_NUM_PREAMBLE_TYPES       HTT_STATS_PREAM_COUNT

काष्ठा htt_rx_peer_rate_stats_tlv अणु
	u32 nsts;

	/* Number of rx ldpc packets */
	u32 rx_ldpc;
	/* Number of rx rts packets */
	u32 rts_cnt;

	u32 rssi_mgmt; /* units = dB above noise न्यूनमान */
	u32 rssi_data; /* units = dB above noise न्यूनमान */
	u32 rssi_comb; /* units = dB above noise न्यूनमान */
	u32 rx_mcs[HTT_RX_PEER_STATS_NUM_MCS_COUNTERS];
	/* element 0,1, ...7 -> NSS 1,2, ...8 */
	u32 rx_nss[HTT_RX_PEER_STATS_NUM_SPATIAL_STREAMS];
	u32 rx_dcm[HTT_RX_PEER_STATS_NUM_DCM_COUNTERS];
	u32 rx_stbc[HTT_RX_PEER_STATS_NUM_MCS_COUNTERS];
	/* element 0: 20 MHz, 1: 40 MHz, 2: 80 MHz, 3: 160 and 80+80 MHz */
	u32 rx_bw[HTT_RX_PEER_STATS_NUM_BW_COUNTERS];
	u32 rx_pream[HTT_RX_PEER_STATS_NUM_PREAMBLE_TYPES];
	/* units = dB above noise न्यूनमान */
	u8 rssi_chain[HTT_RX_PEER_STATS_NUM_SPATIAL_STREAMS]
		     [HTT_RX_PEER_STATS_NUM_BW_COUNTERS];

	/* Counters to track number of rx packets in each GI in each mcs (0-11) */
	u32 rx_gi[HTT_RX_PEER_STATS_NUM_GI_COUNTERS]
		 [HTT_RX_PEER_STATS_NUM_MCS_COUNTERS];
पूर्ण;

क्रमागत htt_peer_stats_req_mode अणु
	HTT_PEER_STATS_REQ_MODE_NO_QUERY,
	HTT_PEER_STATS_REQ_MODE_QUERY_TQM,
	HTT_PEER_STATS_REQ_MODE_FLUSH_TQM,
पूर्ण;

क्रमागत htt_peer_stats_tlv_क्रमागत अणु
	HTT_PEER_STATS_CMN_TLV       = 0,
	HTT_PEER_DETAILS_TLV         = 1,
	HTT_TX_PEER_RATE_STATS_TLV   = 2,
	HTT_RX_PEER_RATE_STATS_TLV   = 3,
	HTT_TX_TID_STATS_TLV         = 4,
	HTT_RX_TID_STATS_TLV         = 5,
	HTT_MSDU_FLOW_STATS_TLV      = 6,

	HTT_PEER_STATS_MAX_TLV       = 31,
पूर्ण;

/* =========== MUMIMO HWQ stats =========== */
/* MU MIMO stats per hwQ */
काष्ठा htt_tx_hwq_mu_mimo_sch_stats_tlv अणु
	u32 mu_mimo_sch_posted;
	u32 mu_mimo_sch_failed;
	u32 mu_mimo_ppdu_posted;
पूर्ण;

काष्ठा htt_tx_hwq_mu_mimo_mpdu_stats_tlv अणु
	u32 mu_mimo_mpdus_queued_usr;
	u32 mu_mimo_mpdus_tried_usr;
	u32 mu_mimo_mpdus_failed_usr;
	u32 mu_mimo_mpdus_requeued_usr;
	u32 mu_mimo_err_no_ba_usr;
	u32 mu_mimo_mpdu_underrun_usr;
	u32 mu_mimo_ampdu_underrun_usr;
पूर्ण;

काष्ठा htt_tx_hwq_mu_mimo_cmn_stats_tlv अणु
	u32 mac_id__hwq_id__word;
पूर्ण;

/* == TX HWQ STATS == */
काष्ठा htt_tx_hwq_stats_cmn_tlv अणु
	u32 mac_id__hwq_id__word;

	/* PPDU level stats */
	u32 xretry;
	u32 underrun_cnt;
	u32 flush_cnt;
	u32 filt_cnt;
	u32 null_mpdu_bmap;
	u32 user_ack_failure;
	u32 ack_tlv_proc;
	u32 sched_id_proc;
	u32 null_mpdu_tx_count;
	u32 mpdu_bmap_not_recvd;

	/* Selfgen stats per hwQ */
	u32 num_bar;
	u32 rts;
	u32 cts2self;
	u32 qos_null;

	/* MPDU level stats */
	u32 mpdu_tried_cnt;
	u32 mpdu_queued_cnt;
	u32 mpdu_ack_fail_cnt;
	u32 mpdu_filt_cnt;
	u32 false_mpdu_ack_count;

	u32 txq_समयout;
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_hwq_dअगरs_latency_stats_tlv_v अणु
	u32 hist_पूर्णांकvl;
	/* histogram of ppdu post to hwsch - > cmd status received */
	u32 dअगरs_latency_hist[]; /* HTT_TX_HWQ_MAX_DIFS_LATENCY_BINS */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_hwq_cmd_result_stats_tlv_v अणु
	/* Histogram of sched cmd result */
	u32 cmd_result[0]; /* HTT_TX_HWQ_MAX_CMD_RESULT_STATS */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_hwq_cmd_stall_stats_tlv_v अणु
	/* Histogram of various छोड़ो conitions */
	u32 cmd_stall_status[0]; /* HTT_TX_HWQ_MAX_CMD_STALL_STATS */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_hwq_fes_result_stats_tlv_v अणु
	/* Histogram of number of user fes result */
	u32 fes_result[0]; /* HTT_TX_HWQ_MAX_FES_RESULT_STATS */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size
 *
 *  The hwq_tried_mpdu_cnt_hist is a  histogram of MPDUs tries per HWQ.
 *  The tries here is the count of the  MPDUS within a PPDU that the HW
 *  had attempted to transmit on  air, क्रम the HWSCH Schedule command
 *  submitted by FW in this HWQ .It is not the retry attempts. The
 *  histogram bins are  0-29, 30-59, 60-89 and so on. The are 10 bins
 *  in this histogram.
 *  they are defined in FW using the following macros
 *  #घोषणा WAL_MAX_TRIED_MPDU_CNT_HISTOGRAM 9
 *  #घोषणा WAL_TRIED_MPDU_CNT_HISTOGRAM_INTERVAL 30
 */
काष्ठा htt_tx_hwq_tried_mpdu_cnt_hist_tlv_v अणु
	u32 hist_bin_size;
	/* Histogram of number of mpdus on tried mpdu */
	u32 tried_mpdu_cnt_hist[]; /* HTT_TX_HWQ_TRIED_MPDU_CNT_HIST */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size
 *
 * The txop_used_cnt_hist is the histogram of txop per burst. After
 * completing the burst, we identअगरy the txop used in the burst and
 * incr the corresponding bin.
 * Each bin represents 1ms & we have 10 bins in this histogram.
 * they are deined in FW using the following macros
 * #घोषणा WAL_MAX_TXOP_USED_CNT_HISTOGRAM 10
 * #घोषणा WAL_TXOP_USED_HISTOGRAM_INTERVAL 1000 ( 1 ms )
 */
काष्ठा htt_tx_hwq_txop_used_cnt_hist_tlv_v अणु
	/* Histogram of txop used cnt */
	u32 txop_used_cnt_hist[0]; /* HTT_TX_HWQ_TXOP_USED_CNT_HIST */
पूर्ण;

/* == TX SELFGEN STATS == */
काष्ठा htt_tx_selfgen_cmn_stats_tlv अणु
	u32 mac_id__word;
	u32 su_bar;
	u32 rts;
	u32 cts2self;
	u32 qos_null;
	u32 delayed_bar_1; /* MU user 1 */
	u32 delayed_bar_2; /* MU user 2 */
	u32 delayed_bar_3; /* MU user 3 */
	u32 delayed_bar_4; /* MU user 4 */
	u32 delayed_bar_5; /* MU user 5 */
	u32 delayed_bar_6; /* MU user 6 */
	u32 delayed_bar_7; /* MU user 7 */
पूर्ण;

काष्ठा htt_tx_selfgen_ac_stats_tlv अणु
	/* 11AC */
	u32 ac_su_ndpa;
	u32 ac_su_ndp;
	u32 ac_mu_mimo_ndpa;
	u32 ac_mu_mimo_ndp;
	u32 ac_mu_mimo_brpoll_1; /* MU user 1 */
	u32 ac_mu_mimo_brpoll_2; /* MU user 2 */
	u32 ac_mu_mimo_brpoll_3; /* MU user 3 */
पूर्ण;

काष्ठा htt_tx_selfgen_ax_stats_tlv अणु
	/* 11AX */
	u32 ax_su_ndpa;
	u32 ax_su_ndp;
	u32 ax_mu_mimo_ndpa;
	u32 ax_mu_mimo_ndp;
	u32 ax_mu_mimo_brpoll_1; /* MU user 1 */
	u32 ax_mu_mimo_brpoll_2; /* MU user 2 */
	u32 ax_mu_mimo_brpoll_3; /* MU user 3 */
	u32 ax_mu_mimo_brpoll_4; /* MU user 4 */
	u32 ax_mu_mimo_brpoll_5; /* MU user 5 */
	u32 ax_mu_mimo_brpoll_6; /* MU user 6 */
	u32 ax_mu_mimo_brpoll_7; /* MU user 7 */
	u32 ax_basic_trigger;
	u32 ax_bsr_trigger;
	u32 ax_mu_bar_trigger;
	u32 ax_mu_rts_trigger;
पूर्ण;

काष्ठा htt_tx_selfgen_ac_err_stats_tlv अणु
	/* 11AC error stats */
	u32 ac_su_ndp_err;
	u32 ac_su_ndpa_err;
	u32 ac_mu_mimo_ndpa_err;
	u32 ac_mu_mimo_ndp_err;
	u32 ac_mu_mimo_brp1_err;
	u32 ac_mu_mimo_brp2_err;
	u32 ac_mu_mimo_brp3_err;
पूर्ण;

काष्ठा htt_tx_selfgen_ax_err_stats_tlv अणु
	/* 11AX error stats */
	u32 ax_su_ndp_err;
	u32 ax_su_ndpa_err;
	u32 ax_mu_mimo_ndpa_err;
	u32 ax_mu_mimo_ndp_err;
	u32 ax_mu_mimo_brp1_err;
	u32 ax_mu_mimo_brp2_err;
	u32 ax_mu_mimo_brp3_err;
	u32 ax_mu_mimo_brp4_err;
	u32 ax_mu_mimo_brp5_err;
	u32 ax_mu_mimo_brp6_err;
	u32 ax_mu_mimo_brp7_err;
	u32 ax_basic_trigger_err;
	u32 ax_bsr_trigger_err;
	u32 ax_mu_bar_trigger_err;
	u32 ax_mu_rts_trigger_err;
पूर्ण;

/* == TX MU STATS == */
#घोषणा HTT_TX_PDEV_STATS_NUM_AC_MUMIMO_USER_STATS 4
#घोषणा HTT_TX_PDEV_STATS_NUM_AX_MUMIMO_USER_STATS 8
#घोषणा HTT_TX_PDEV_STATS_NUM_OFDMA_USER_STATS    74

काष्ठा htt_tx_pdev_mu_mimo_sch_stats_tlv अणु
	/* mu-mimo sw sched cmd stats */
	u32 mu_mimo_sch_posted;
	u32 mu_mimo_sch_failed;
	/* MU PPDU stats per hwQ */
	u32 mu_mimo_ppdu_posted;
	/*
	 * Counts the number of users in each transmission of
	 * the given TX mode.
	 *
	 * Index is the number of users - 1.
	 */
	u32 ac_mu_mimo_sch_nusers[HTT_TX_PDEV_STATS_NUM_AC_MUMIMO_USER_STATS];
	u32 ax_mu_mimo_sch_nusers[HTT_TX_PDEV_STATS_NUM_AX_MUMIMO_USER_STATS];
	u32 ax_ofdma_sch_nusers[HTT_TX_PDEV_STATS_NUM_OFDMA_USER_STATS];
पूर्ण;

काष्ठा htt_tx_pdev_mu_mimo_mpdu_stats_tlv अणु
	u32 mu_mimo_mpdus_queued_usr;
	u32 mu_mimo_mpdus_tried_usr;
	u32 mu_mimo_mpdus_failed_usr;
	u32 mu_mimo_mpdus_requeued_usr;
	u32 mu_mimo_err_no_ba_usr;
	u32 mu_mimo_mpdu_underrun_usr;
	u32 mu_mimo_ampdu_underrun_usr;

	u32 ax_mu_mimo_mpdus_queued_usr;
	u32 ax_mu_mimo_mpdus_tried_usr;
	u32 ax_mu_mimo_mpdus_failed_usr;
	u32 ax_mu_mimo_mpdus_requeued_usr;
	u32 ax_mu_mimo_err_no_ba_usr;
	u32 ax_mu_mimo_mpdu_underrun_usr;
	u32 ax_mu_mimo_ampdu_underrun_usr;

	u32 ax_ofdma_mpdus_queued_usr;
	u32 ax_ofdma_mpdus_tried_usr;
	u32 ax_ofdma_mpdus_failed_usr;
	u32 ax_ofdma_mpdus_requeued_usr;
	u32 ax_ofdma_err_no_ba_usr;
	u32 ax_ofdma_mpdu_underrun_usr;
	u32 ax_ofdma_ampdu_underrun_usr;
पूर्ण;

#घोषणा HTT_STATS_TX_SCHED_MODE_MU_MIMO_AC  1
#घोषणा HTT_STATS_TX_SCHED_MODE_MU_MIMO_AX  2
#घोषणा HTT_STATS_TX_SCHED_MODE_MU_OFDMA_AX 3

काष्ठा htt_tx_pdev_mpdu_stats_tlv अणु
	/* mpdu level stats */
	u32 mpdus_queued_usr;
	u32 mpdus_tried_usr;
	u32 mpdus_failed_usr;
	u32 mpdus_requeued_usr;
	u32 err_no_ba_usr;
	u32 mpdu_underrun_usr;
	u32 ampdu_underrun_usr;
	u32 user_index;
	u32 tx_sched_mode; /* HTT_STATS_TX_SCHED_MODE_xxx */
पूर्ण;

/* == TX SCHED STATS == */
/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_sched_txq_cmd_posted_tlv_v अणु
	u32 sched_cmd_posted[0]; /* HTT_TX_PDEV_SCHED_TX_MODE_MAX */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_sched_txq_cmd_reaped_tlv_v अणु
	u32 sched_cmd_reaped[0]; /* HTT_TX_PDEV_SCHED_TX_MODE_MAX */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_sched_txq_sched_order_su_tlv_v अणु
	u32 sched_order_su[0]; /* HTT_TX_PDEV_NUM_SCHED_ORDER_LOG */
पूर्ण;

क्रमागत htt_sched_txq_sched_ineligibility_tlv_क्रमागत अणु
	HTT_SCHED_TID_SKIP_SCHED_MASK_DISABLED = 0,
	HTT_SCHED_TID_SKIP_NOTIFY_MPDU,
	HTT_SCHED_TID_SKIP_MPDU_STATE_INVALID,
	HTT_SCHED_TID_SKIP_SCHED_DISABLED,
	HTT_SCHED_TID_SKIP_TQM_BYPASS_CMD_PENDING,
	HTT_SCHED_TID_SKIP_SECOND_SU_SCHEDULE,

	HTT_SCHED_TID_SKIP_CMD_SLOT_NOT_AVAIL,
	HTT_SCHED_TID_SKIP_NO_ENQ,
	HTT_SCHED_TID_SKIP_LOW_ENQ,
	HTT_SCHED_TID_SKIP_PAUSED,
	HTT_SCHED_TID_SKIP_UL,
	HTT_SCHED_TID_REMOVE_PAUSED,
	HTT_SCHED_TID_REMOVE_NO_ENQ,
	HTT_SCHED_TID_REMOVE_UL,
	HTT_SCHED_TID_QUERY,
	HTT_SCHED_TID_SU_ONLY,
	HTT_SCHED_TID_ELIGIBLE,
	HTT_SCHED_INELIGIBILITY_MAX,
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_sched_txq_sched_ineligibility_tlv_v अणु
	/* indexed by htt_sched_txq_sched_ineligibility_tlv_क्रमागत */
	u32 sched_ineligibility[0];
पूर्ण;

काष्ठा htt_tx_pdev_stats_sched_per_txq_tlv अणु
	u32 mac_id__txq_id__word;
	u32 sched_policy;
	u32 last_sched_cmd_posted_बारtamp;
	u32 last_sched_cmd_compl_बारtamp;
	u32 sched_2_tac_lwm_count;
	u32 sched_2_tac_ring_full;
	u32 sched_cmd_post_failure;
	u32 num_active_tids;
	u32 num_ps_schedules;
	u32 sched_cmds_pending;
	u32 num_tid_रेजिस्टर;
	u32 num_tid_unरेजिस्टर;
	u32 num_qstats_queried;
	u32 qstats_update_pending;
	u32 last_qstats_query_बारtamp;
	u32 num_tqm_cmdq_full;
	u32 num_de_sched_algo_trigger;
	u32 num_rt_sched_algo_trigger;
	u32 num_tqm_sched_algo_trigger;
	u32 notअगरy_sched;
	u32 dur_based_sendn_term;
पूर्ण;

काष्ठा htt_stats_tx_sched_cmn_tlv अणु
	/* BIT [ 7 :  0]   :- mac_id
	 * BIT [31 :  8]   :- reserved
	 */
	u32 mac_id__word;
	/* Current बारtamp */
	u32 current_बारtamp;
पूर्ण;

/* == TQM STATS == */
#घोषणा HTT_TX_TQM_MAX_GEN_MPDU_END_REASON          16
#घोषणा HTT_TX_TQM_MAX_LIST_MPDU_END_REASON         16
#घोषणा HTT_TX_TQM_MAX_LIST_MPDU_CNT_HISTOGRAM_BINS 16

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_tqm_gen_mpdu_stats_tlv_v अणु
	u32 gen_mpdu_end_reason[0]; /* HTT_TX_TQM_MAX_GEN_MPDU_END_REASON */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_tqm_list_mpdu_stats_tlv_v अणु
	u32 list_mpdu_end_reason[0]; /* HTT_TX_TQM_MAX_LIST_MPDU_END_REASON */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_tx_tqm_list_mpdu_cnt_tlv_v अणु
	u32 list_mpdu_cnt_hist[0];
			/* HTT_TX_TQM_MAX_LIST_MPDU_CNT_HISTOGRAM_BINS */
पूर्ण;

काष्ठा htt_tx_tqm_pdev_stats_tlv_v अणु
	u32 msdu_count;
	u32 mpdu_count;
	u32 हटाओ_msdu;
	u32 हटाओ_mpdu;
	u32 हटाओ_msdu_ttl;
	u32 send_bar;
	u32 bar_sync;
	u32 notअगरy_mpdu;
	u32 sync_cmd;
	u32 ग_लिखो_cmd;
	u32 hwsch_trigger;
	u32 ack_tlv_proc;
	u32 gen_mpdu_cmd;
	u32 gen_list_cmd;
	u32 हटाओ_mpdu_cmd;
	u32 हटाओ_mpdu_tried_cmd;
	u32 mpdu_queue_stats_cmd;
	u32 mpdu_head_info_cmd;
	u32 msdu_flow_stats_cmd;
	u32 हटाओ_msdu_cmd;
	u32 हटाओ_msdu_ttl_cmd;
	u32 flush_cache_cmd;
	u32 update_mpduq_cmd;
	u32 enqueue;
	u32 enqueue_notअगरy;
	u32 notअगरy_mpdu_at_head;
	u32 notअगरy_mpdu_state_valid;
	/*
	 * On receiving TQM_FLOW_NOT_EMPTY_STATUS from TQM, (on MSDUs being enqueued
	 * the flow is non empty), अगर the number of MSDUs is greater than the threshold,
	 * notअगरy is incremented. UDP_THRESH counters are क्रम UDP MSDUs, and NONUDP are
	 * क्रम non-UDP MSDUs.
	 * MSDUQ_SWNOTIFY_UDP_THRESH1 threshold    - sched_udp_notअगरy1 is incremented
	 * MSDUQ_SWNOTIFY_UDP_THRESH2 threshold    - sched_udp_notअगरy2 is incremented
	 * MSDUQ_SWNOTIFY_NONUDP_THRESH1 threshold - sched_nonudp_notअगरy1 is incremented
	 * MSDUQ_SWNOTIFY_NONUDP_THRESH2 threshold - sched_nonudp_notअगरy2 is incremented
	 *
	 * Notअगरy signअगरies that we trigger the scheduler.
	 */
	u32 sched_udp_notअगरy1;
	u32 sched_udp_notअगरy2;
	u32 sched_nonudp_notअगरy1;
	u32 sched_nonudp_notअगरy2;
पूर्ण;

काष्ठा htt_tx_tqm_cmn_stats_tlv अणु
	u32 mac_id__word;
	u32 max_cmdq_id;
	u32 list_mpdu_cnt_hist_पूर्णांकvl;

	/* Global stats */
	u32 add_msdu;
	u32 q_empty;
	u32 q_not_empty;
	u32 drop_notअगरication;
	u32 desc_threshold;
पूर्ण;

काष्ठा htt_tx_tqm_error_stats_tlv अणु
	/* Error stats */
	u32 q_empty_failure;
	u32 q_not_empty_failure;
	u32 add_msdu_failure;
पूर्ण;

/* == TQM CMDQ stats == */
काष्ठा htt_tx_tqm_cmdq_status_tlv अणु
	u32 mac_id__cmdq_id__word;
	u32 sync_cmd;
	u32 ग_लिखो_cmd;
	u32 gen_mpdu_cmd;
	u32 mpdu_queue_stats_cmd;
	u32 mpdu_head_info_cmd;
	u32 msdu_flow_stats_cmd;
	u32 हटाओ_mpdu_cmd;
	u32 हटाओ_msdu_cmd;
	u32 flush_cache_cmd;
	u32 update_mpduq_cmd;
	u32 update_msduq_cmd;
पूर्ण;

/* == TX-DE STATS == */
/* Structures क्रम tx de stats */
काष्ठा htt_tx_de_eapol_packets_stats_tlv अणु
	u32 m1_packets;
	u32 m2_packets;
	u32 m3_packets;
	u32 m4_packets;
	u32 g1_packets;
	u32 g2_packets;
पूर्ण;

काष्ठा htt_tx_de_classअगरy_failed_stats_tlv अणु
	u32 ap_bss_peer_not_found;
	u32 ap_bcast_mcast_no_peer;
	u32 sta_delete_in_progress;
	u32 ibss_no_bss_peer;
	u32 invalid_vdev_type;
	u32 invalid_ast_peer_entry;
	u32 peer_entry_invalid;
	u32 ethertype_not_ip;
	u32 eapol_lookup_failed;
	u32 qpeer_not_allow_data;
	u32 fse_tid_override;
	u32 ipv6_jumbogram_zero_length;
	u32 qos_to_non_qos_in_prog;
पूर्ण;

काष्ठा htt_tx_de_classअगरy_stats_tlv अणु
	u32 arp_packets;
	u32 igmp_packets;
	u32 dhcp_packets;
	u32 host_inspected;
	u32 htt_included;
	u32 htt_valid_mcs;
	u32 htt_valid_nss;
	u32 htt_valid_preamble_type;
	u32 htt_valid_chainmask;
	u32 htt_valid_guard_पूर्णांकerval;
	u32 htt_valid_retries;
	u32 htt_valid_bw_info;
	u32 htt_valid_घातer;
	u32 htt_valid_key_flags;
	u32 htt_valid_no_encryption;
	u32 fse_entry_count;
	u32 fse_priority_be;
	u32 fse_priority_high;
	u32 fse_priority_low;
	u32 fse_traffic_ptrn_be;
	u32 fse_traffic_ptrn_over_sub;
	u32 fse_traffic_ptrn_bursty;
	u32 fse_traffic_ptrn_पूर्णांकeractive;
	u32 fse_traffic_ptrn_periodic;
	u32 fse_hwqueue_alloc;
	u32 fse_hwqueue_created;
	u32 fse_hwqueue_send_to_host;
	u32 mcast_entry;
	u32 bcast_entry;
	u32 htt_update_peer_cache;
	u32 htt_learning_frame;
	u32 fse_invalid_peer;
	/*
	 * mec_notअगरy is HTT TX WBM multicast echo check notअगरication
	 * from firmware to host.  FW sends SA addresses to host क्रम all
	 * multicast/broadcast packets received on STA side.
	 */
	u32    mec_notअगरy;
पूर्ण;

काष्ठा htt_tx_de_classअगरy_status_stats_tlv अणु
	u32 eok;
	u32 classअगरy_करोne;
	u32 lookup_failed;
	u32 send_host_dhcp;
	u32 send_host_mcast;
	u32 send_host_unknown_dest;
	u32 send_host;
	u32 status_invalid;
पूर्ण;

काष्ठा htt_tx_de_enqueue_packets_stats_tlv अणु
	u32 enqueued_pkts;
	u32 to_tqm;
	u32 to_tqm_bypass;
पूर्ण;

काष्ठा htt_tx_de_enqueue_discard_stats_tlv अणु
	u32 discarded_pkts;
	u32 local_frames;
	u32 is_ext_msdu;
पूर्ण;

काष्ठा htt_tx_de_compl_stats_tlv अणु
	u32 tcl_dummy_frame;
	u32 tqm_dummy_frame;
	u32 tqm_notअगरy_frame;
	u32 fw2wbm_enq;
	u32 tqm_bypass_frame;
पूर्ण;

/*
 *  The htt_tx_de_fw2wbm_ring_full_hist_tlv is a histogram of समय we रुकोed
 *  क्रम the fw2wbm ring buffer.  we are requesting a buffer in FW2WBM release
 *  ring,which may fail, due to non availability of buffer. Hence we sleep क्रम
 *  200us & again request क्रम it. This is a histogram of समय we रुको, with
 *  bin of 200ms & there are 10 bin (2 seconds max)
 *  They are defined by the following macros in FW
 *  #घोषणा ENTRIES_PER_BIN_COUNT 1000  // per bin 1000 * 200us = 200ms
 *  #घोषणा RING_FULL_BIN_ENTRIES (WAL_TX_DE_FW2WBM_ALLOC_TIMEOUT_COUNT /
 *                               ENTRIES_PER_BIN_COUNT)
 */
काष्ठा htt_tx_de_fw2wbm_ring_full_hist_tlv अणु
	u32 fw2wbm_ring_full_hist[0];
पूर्ण;

काष्ठा htt_tx_de_cmn_stats_tlv अणु
	u32   mac_id__word;

	/* Global Stats */
	u32   tcl2fw_entry_count;
	u32   not_to_fw;
	u32   invalid_pdev_vdev_peer;
	u32   tcl_res_invalid_addrx;
	u32   wbm2fw_entry_count;
	u32   invalid_pdev;
पूर्ण;

/* == RING-IF STATS == */
#घोषणा HTT_STATS_LOW_WM_BINS      5
#घोषणा HTT_STATS_HIGH_WM_BINS     5

काष्ठा htt_ring_अगर_stats_tlv अणु
	u32 base_addr; /* DWORD aligned base memory address of the ring */
	u32 elem_size;
	u32 num_elems__prefetch_tail_idx;
	u32 head_idx__tail_idx;
	u32 shaकरोw_head_idx__shaकरोw_tail_idx;
	u32 num_tail_incr;
	u32 lwm_thresh__hwm_thresh;
	u32 overrun_hit_count;
	u32 underrun_hit_count;
	u32 prod_blockरुको_count;
	u32 cons_blockरुको_count;
	u32 low_wm_hit_count[HTT_STATS_LOW_WM_BINS];
	u32 high_wm_hit_count[HTT_STATS_HIGH_WM_BINS];
पूर्ण;

काष्ठा htt_ring_अगर_cmn_tlv अणु
	u32 mac_id__word;
	u32 num_records;
पूर्ण;

/* == SFM STATS == */
/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_sfm_client_user_tlv_v अणु
	/* Number of DWORDS used per user and per client */
	u32 dwords_used_by_user_n[0];
पूर्ण;

काष्ठा htt_sfm_client_tlv अणु
	/* Client ID */
	u32 client_id;
	/* Minimum number of buffers */
	u32 buf_min;
	/* Maximum number of buffers */
	u32 buf_max;
	/* Number of Busy buffers */
	u32 buf_busy;
	/* Number of Allocated buffers */
	u32 buf_alloc;
	/* Number of Available/Usable buffers */
	u32 buf_avail;
	/* Number of users */
	u32 num_users;
पूर्ण;

काष्ठा htt_sfm_cmn_tlv अणु
	u32 mac_id__word;
	/* Indicates the total number of 128 byte buffers
	 * in the CMEM that are available क्रम buffer sharing
	 */
	u32 buf_total;
	/* Indicates क्रम certain client or all the clients
	 * there is no करोwrd saved in SFM, refer to SFM_R1_MEM_EMPTY
	 */
	u32 mem_empty;
	/* DEALLOCATE_BUFFERS, refer to रेजिस्टर SFM_R0_DEALLOCATE_BUFFERS */
	u32 deallocate_bufs;
	/* Number of Records */
	u32 num_records;
पूर्ण;

/* == SRNG STATS == */
काष्ठा htt_sring_stats_tlv अणु
	u32 mac_id__ring_id__arena__ep;
	u32 base_addr_lsb; /* DWORD aligned base memory address of the ring */
	u32 base_addr_msb;
	u32 ring_size;
	u32 elem_size;

	u32 num_avail_words__num_valid_words;
	u32 head_ptr__tail_ptr;
	u32 consumer_empty__producer_full;
	u32 prefetch_count__पूर्णांकernal_tail_ptr;
पूर्ण;

काष्ठा htt_sring_cmn_tlv अणु
	u32 num_records;
पूर्ण;

/* == PDEV TX RATE CTRL STATS == */
#घोषणा HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS        12
#घोषणा HTT_TX_PDEV_STATS_NUM_GI_COUNTERS          4
#घोषणा HTT_TX_PDEV_STATS_NUM_DCM_COUNTERS         5
#घोषणा HTT_TX_PDEV_STATS_NUM_BW_COUNTERS          4
#घोषणा HTT_TX_PDEV_STATS_NUM_SPATIAL_STREAMS      8
#घोषणा HTT_TX_PDEV_STATS_NUM_PREAMBLE_TYPES       HTT_STATS_PREAM_COUNT
#घोषणा HTT_TX_PDEV_STATS_NUM_LEGACY_CCK_STATS     4
#घोषणा HTT_TX_PDEV_STATS_NUM_LEGACY_OFDM_STATS    8
#घोषणा HTT_TX_PDEV_STATS_NUM_LTF                  4

#घोषणा HTT_TX_NUM_OF_SOUNDING_STATS_WORDS \
	(HTT_TX_PDEV_STATS_NUM_BW_COUNTERS * \
	 HTT_TX_PDEV_STATS_NUM_AX_MUMIMO_USER_STATS)

काष्ठा htt_tx_pdev_rate_stats_tlv अणु
	u32 mac_id__word;
	u32 tx_ldpc;
	u32 rts_cnt;
	/* RSSI value of last ack packet (units = dB above noise न्यूनमान) */
	u32 ack_rssi;

	u32 tx_mcs[HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];

	u32 tx_su_mcs[HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];
	u32 tx_mu_mcs[HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];

	/* element 0,1, ...7 -> NSS 1,2, ...8 */
	u32 tx_nss[HTT_TX_PDEV_STATS_NUM_SPATIAL_STREAMS];
	/* element 0: 20 MHz, 1: 40 MHz, 2: 80 MHz, 3: 160 and 80+80 MHz */
	u32 tx_bw[HTT_TX_PDEV_STATS_NUM_BW_COUNTERS];
	u32 tx_stbc[HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];
	u32 tx_pream[HTT_TX_PDEV_STATS_NUM_PREAMBLE_TYPES];

	/* Counters to track number of tx packets
	 * in each GI (400us, 800us, 1600us & 3200us) in each mcs (0-11)
	 */
	u32 tx_gi[HTT_TX_PDEV_STATS_NUM_GI_COUNTERS][HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];

	/* Counters to track packets in dcm mcs (MCS 0, 1, 3, 4) */
	u32 tx_dcm[HTT_TX_PDEV_STATS_NUM_DCM_COUNTERS];
	/* Number of CTS-acknowledged RTS packets */
	u32 rts_success;

	/*
	 * Counters क्रम legacy 11a and 11b transmissions.
	 *
	 * The index corresponds to:
	 *
	 * CCK: 0: 1 Mbps, 1: 2 Mbps, 2: 5.5 Mbps, 3: 11 Mbps
	 *
	 * OFDM: 0: 6 Mbps, 1: 9 Mbps, 2: 12 Mbps, 3: 18 Mbps,
	 *       4: 24 Mbps, 5: 36 Mbps, 6: 48 Mbps, 7: 54 Mbps
	 */
	u32 tx_legacy_cck_rate[HTT_TX_PDEV_STATS_NUM_LEGACY_CCK_STATS];
	u32 tx_legacy_ofdm_rate[HTT_TX_PDEV_STATS_NUM_LEGACY_OFDM_STATS];

	u32 ac_mu_mimo_tx_ldpc;
	u32 ax_mu_mimo_tx_ldpc;
	u32 ofdma_tx_ldpc;

	/*
	 * Counters क्रम 11ax HE LTF selection during TX.
	 *
	 * The index corresponds to:
	 *
	 * 0: unused, 1: 1x LTF, 2: 2x LTF, 3: 4x LTF
	 */
	u32 tx_he_ltf[HTT_TX_PDEV_STATS_NUM_LTF];

	u32 ac_mu_mimo_tx_mcs[HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];
	u32 ax_mu_mimo_tx_mcs[HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];
	u32 ofdma_tx_mcs[HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];

	u32 ac_mu_mimo_tx_nss[HTT_TX_PDEV_STATS_NUM_SPATIAL_STREAMS];
	u32 ax_mu_mimo_tx_nss[HTT_TX_PDEV_STATS_NUM_SPATIAL_STREAMS];
	u32 ofdma_tx_nss[HTT_TX_PDEV_STATS_NUM_SPATIAL_STREAMS];

	u32 ac_mu_mimo_tx_bw[HTT_TX_PDEV_STATS_NUM_BW_COUNTERS];
	u32 ax_mu_mimo_tx_bw[HTT_TX_PDEV_STATS_NUM_BW_COUNTERS];
	u32 ofdma_tx_bw[HTT_TX_PDEV_STATS_NUM_BW_COUNTERS];

	u32 ac_mu_mimo_tx_gi[HTT_TX_PDEV_STATS_NUM_GI_COUNTERS]
			    [HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];
	u32 ax_mu_mimo_tx_gi[HTT_TX_PDEV_STATS_NUM_GI_COUNTERS]
			    [HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];
	u32 ofdma_tx_gi[HTT_TX_PDEV_STATS_NUM_GI_COUNTERS]
		       [HTT_TX_PDEV_STATS_NUM_MCS_COUNTERS];
पूर्ण;

/* == PDEV RX RATE CTRL STATS == */
#घोषणा HTT_RX_PDEV_STATS_NUM_LEGACY_CCK_STATS     4
#घोषणा HTT_RX_PDEV_STATS_NUM_LEGACY_OFDM_STATS    8
#घोषणा HTT_RX_PDEV_STATS_NUM_MCS_COUNTERS        12
#घोषणा HTT_RX_PDEV_STATS_NUM_GI_COUNTERS          4
#घोषणा HTT_RX_PDEV_STATS_NUM_DCM_COUNTERS         5
#घोषणा HTT_RX_PDEV_STATS_NUM_BW_COUNTERS          4
#घोषणा HTT_RX_PDEV_STATS_NUM_SPATIAL_STREAMS      8
#घोषणा HTT_RX_PDEV_STATS_NUM_PREAMBLE_TYPES       HTT_STATS_PREAM_COUNT
#घोषणा HTT_RX_PDEV_MAX_OFDMA_NUM_USER             8
#घोषणा HTT_RX_PDEV_STATS_RXEVM_MAX_PILOTS_PER_NSS 16

काष्ठा htt_rx_pdev_rate_stats_tlv अणु
	u32 mac_id__word;
	u32 nsts;

	u32 rx_ldpc;
	u32 rts_cnt;

	u32 rssi_mgmt; /* units = dB above noise न्यूनमान */
	u32 rssi_data; /* units = dB above noise न्यूनमान */
	u32 rssi_comb; /* units = dB above noise न्यूनमान */
	u32 rx_mcs[HTT_RX_PDEV_STATS_NUM_MCS_COUNTERS];
	/* element 0,1, ...7 -> NSS 1,2, ...8 */
	u32 rx_nss[HTT_RX_PDEV_STATS_NUM_SPATIAL_STREAMS];
	u32 rx_dcm[HTT_RX_PDEV_STATS_NUM_DCM_COUNTERS];
	u32 rx_stbc[HTT_RX_PDEV_STATS_NUM_MCS_COUNTERS];
	/* element 0: 20 MHz, 1: 40 MHz, 2: 80 MHz, 3: 160 and 80+80 MHz */
	u32 rx_bw[HTT_RX_PDEV_STATS_NUM_BW_COUNTERS];
	u32 rx_pream[HTT_RX_PDEV_STATS_NUM_PREAMBLE_TYPES];
	u8 rssi_chain[HTT_RX_PDEV_STATS_NUM_SPATIAL_STREAMS]
		     [HTT_RX_PDEV_STATS_NUM_BW_COUNTERS];
					/* units = dB above noise न्यूनमान */

	/* Counters to track number of rx packets
	 * in each GI in each mcs (0-11)
	 */
	u32 rx_gi[HTT_RX_PDEV_STATS_NUM_GI_COUNTERS][HTT_RX_PDEV_STATS_NUM_MCS_COUNTERS];
	s32 rssi_in_dbm; /* rx Signal Strength value in dBm unit */

	u32 rx_11ax_su_ext;
	u32 rx_11ac_mumimo;
	u32 rx_11ax_mumimo;
	u32 rx_11ax_ofdma;
	u32 txbf;
	u32 rx_legacy_cck_rate[HTT_RX_PDEV_STATS_NUM_LEGACY_CCK_STATS];
	u32 rx_legacy_ofdm_rate[HTT_RX_PDEV_STATS_NUM_LEGACY_OFDM_STATS];
	u32 rx_active_dur_us_low;
	u32 rx_active_dur_us_high;

	u32 rx_11ax_ul_ofdma;

	u32 ul_ofdma_rx_mcs[HTT_RX_PDEV_STATS_NUM_MCS_COUNTERS];
	u32 ul_ofdma_rx_gi[HTT_TX_PDEV_STATS_NUM_GI_COUNTERS]
			  [HTT_RX_PDEV_STATS_NUM_MCS_COUNTERS];
	u32 ul_ofdma_rx_nss[HTT_TX_PDEV_STATS_NUM_SPATIAL_STREAMS];
	u32 ul_ofdma_rx_bw[HTT_TX_PDEV_STATS_NUM_BW_COUNTERS];
	u32 ul_ofdma_rx_stbc;
	u32 ul_ofdma_rx_ldpc;

	/* record the stats क्रम each user index */
	u32 rx_ulofdma_non_data_ppdu[HTT_RX_PDEV_MAX_OFDMA_NUM_USER]; /* ppdu level */
	u32 rx_ulofdma_data_ppdu[HTT_RX_PDEV_MAX_OFDMA_NUM_USER];     /* ppdu level */
	u32 rx_ulofdma_mpdu_ok[HTT_RX_PDEV_MAX_OFDMA_NUM_USER];       /* mpdu level */
	u32 rx_ulofdma_mpdu_fail[HTT_RX_PDEV_MAX_OFDMA_NUM_USER];     /* mpdu level */

	u32 nss_count;
	u32 pilot_count;
	/* RxEVM stats in dB */
	s32 rx_pilot_evm_db[HTT_RX_PDEV_STATS_NUM_SPATIAL_STREAMS]
			   [HTT_RX_PDEV_STATS_RXEVM_MAX_PILOTS_PER_NSS];
	/* rx_pilot_evm_db_mean:
	 * EVM mean across pilots, computed as
	 *     mean(10*log10(rx_pilot_evm_linear)) = mean(rx_pilot_evm_db)
	 */
	s32 rx_pilot_evm_db_mean[HTT_RX_PDEV_STATS_NUM_SPATIAL_STREAMS];
	s8 rx_ul_fd_rssi[HTT_RX_PDEV_STATS_NUM_SPATIAL_STREAMS]
			[HTT_RX_PDEV_MAX_OFDMA_NUM_USER]; /* dBm units */
	/* per_chain_rssi_pkt_type:
	 * This field shows what type of rx frame the per-chain RSSI was computed
	 * on, by recording the frame type and sub-type as bit-fields within this
	 * field:
	 * BIT [3 : 0]    :- IEEE80211_FC0_TYPE
	 * BIT [7 : 4]    :- IEEE80211_FC0_SUBTYPE
	 * BIT [31 : 8]   :- Reserved
	 */
	u32 per_chain_rssi_pkt_type;
	s8 rx_per_chain_rssi_in_dbm[HTT_RX_PDEV_STATS_NUM_SPATIAL_STREAMS]
				   [HTT_RX_PDEV_STATS_NUM_BW_COUNTERS];
पूर्ण;

/* == RX PDEV/SOC STATS == */
काष्ठा htt_rx_soc_fw_stats_tlv अणु
	u32 fw_reo_ring_data_msdu;
	u32 fw_to_host_data_msdu_bcmc;
	u32 fw_to_host_data_msdu_uc;
	u32 ofld_remote_data_buf_recycle_cnt;
	u32 ofld_remote_मुक्त_buf_indication_cnt;

	u32 ofld_buf_to_host_data_msdu_uc;
	u32 reo_fw_ring_to_host_data_msdu_uc;

	u32 wbm_sw_ring_reap;
	u32 wbm_क्रमward_to_host_cnt;
	u32 wbm_target_recycle_cnt;

	u32 target_refill_ring_recycle_cnt;
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_rx_soc_fw_refill_ring_empty_tlv_v अणु
	u32 refill_ring_empty_cnt[0]; /* HTT_RX_STATS_REFILL_MAX_RING */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_rx_soc_fw_refill_ring_num_refill_tlv_v अणु
	u32 refill_ring_num_refill[0]; /* HTT_RX_STATS_REFILL_MAX_RING */
पूर्ण;

/* RXDMA error code from WBM released packets */
क्रमागत htt_rx_rxdma_error_code_क्रमागत अणु
	HTT_RX_RXDMA_OVERFLOW_ERR                           = 0,
	HTT_RX_RXDMA_MPDU_LENGTH_ERR                        = 1,
	HTT_RX_RXDMA_FCS_ERR                                = 2,
	HTT_RX_RXDMA_DECRYPT_ERR                            = 3,
	HTT_RX_RXDMA_TKIP_MIC_ERR                           = 4,
	HTT_RX_RXDMA_UNECRYPTED_ERR                         = 5,
	HTT_RX_RXDMA_MSDU_LEN_ERR                           = 6,
	HTT_RX_RXDMA_MSDU_LIMIT_ERR                         = 7,
	HTT_RX_RXDMA_WIFI_PARSE_ERR                         = 8,
	HTT_RX_RXDMA_AMSDU_PARSE_ERR                        = 9,
	HTT_RX_RXDMA_SA_TIMEOUT_ERR                         = 10,
	HTT_RX_RXDMA_DA_TIMEOUT_ERR                         = 11,
	HTT_RX_RXDMA_FLOW_TIMEOUT_ERR                       = 12,
	HTT_RX_RXDMA_FLUSH_REQUEST                          = 13,
	HTT_RX_RXDMA_ERR_CODE_RVSD0                         = 14,
	HTT_RX_RXDMA_ERR_CODE_RVSD1                         = 15,

	/* This MAX_ERR_CODE should not be used in any host/target messages,
	 * so that even though it is defined within a host/target पूर्णांकerface
	 * definition header file, it isn't actually part of the host/target
	 * पूर्णांकerface, and thus can be modअगरied.
	 */
	HTT_RX_RXDMA_MAX_ERR_CODE
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_rx_soc_fw_refill_ring_num_rxdma_err_tlv_v अणु
	u32 rxdma_err[0]; /* HTT_RX_RXDMA_MAX_ERR_CODE */
पूर्ण;

/* REO error code from WBM released packets */
क्रमागत htt_rx_reo_error_code_क्रमागत अणु
	HTT_RX_REO_QUEUE_DESC_ADDR_ZERO                     = 0,
	HTT_RX_REO_QUEUE_DESC_NOT_VALID                     = 1,
	HTT_RX_AMPDU_IN_NON_BA                              = 2,
	HTT_RX_NON_BA_DUPLICATE                             = 3,
	HTT_RX_BA_DUPLICATE                                 = 4,
	HTT_RX_REGULAR_FRAME_2K_JUMP                        = 5,
	HTT_RX_BAR_FRAME_2K_JUMP                            = 6,
	HTT_RX_REGULAR_FRAME_OOR                            = 7,
	HTT_RX_BAR_FRAME_OOR                                = 8,
	HTT_RX_BAR_FRAME_NO_BA_SESSION                      = 9,
	HTT_RX_BAR_FRAME_SN_EQUALS_SSN                      = 10,
	HTT_RX_PN_CHECK_FAILED                              = 11,
	HTT_RX_2K_ERROR_HANDLING_FLAG_SET                   = 12,
	HTT_RX_PN_ERROR_HANDLING_FLAG_SET                   = 13,
	HTT_RX_QUEUE_DESCRIPTOR_BLOCKED_SET                 = 14,
	HTT_RX_REO_ERR_CODE_RVSD                            = 15,

	/* This MAX_ERR_CODE should not be used in any host/target messages,
	 * so that even though it is defined within a host/target पूर्णांकerface
	 * definition header file, it isn't actually part of the host/target
	 * पूर्णांकerface, and thus can be modअगरied.
	 */
	HTT_RX_REO_MAX_ERR_CODE
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_rx_soc_fw_refill_ring_num_reo_err_tlv_v अणु
	u32 reo_err[0]; /* HTT_RX_REO_MAX_ERR_CODE */
पूर्ण;

/* == RX PDEV STATS == */
#घोषणा HTT_STATS_SUBTYPE_MAX     16

काष्ठा htt_rx_pdev_fw_stats_tlv अणु
	u32 mac_id__word;
	u32 ppdu_recvd;
	u32 mpdu_cnt_fcs_ok;
	u32 mpdu_cnt_fcs_err;
	u32 tcp_msdu_cnt;
	u32 tcp_ack_msdu_cnt;
	u32 udp_msdu_cnt;
	u32 other_msdu_cnt;
	u32 fw_ring_mpdu_ind;
	u32 fw_ring_mgmt_subtype[HTT_STATS_SUBTYPE_MAX];
	u32 fw_ring_ctrl_subtype[HTT_STATS_SUBTYPE_MAX];
	u32 fw_ring_mcast_data_msdu;
	u32 fw_ring_bcast_data_msdu;
	u32 fw_ring_ucast_data_msdu;
	u32 fw_ring_null_data_msdu;
	u32 fw_ring_mpdu_drop;
	u32 ofld_local_data_ind_cnt;
	u32 ofld_local_data_buf_recycle_cnt;
	u32 drx_local_data_ind_cnt;
	u32 drx_local_data_buf_recycle_cnt;
	u32 local_nondata_ind_cnt;
	u32 local_nondata_buf_recycle_cnt;

	u32 fw_status_buf_ring_refill_cnt;
	u32 fw_status_buf_ring_empty_cnt;
	u32 fw_pkt_buf_ring_refill_cnt;
	u32 fw_pkt_buf_ring_empty_cnt;
	u32 fw_link_buf_ring_refill_cnt;
	u32 fw_link_buf_ring_empty_cnt;

	u32 host_pkt_buf_ring_refill_cnt;
	u32 host_pkt_buf_ring_empty_cnt;
	u32 mon_pkt_buf_ring_refill_cnt;
	u32 mon_pkt_buf_ring_empty_cnt;
	u32 mon_status_buf_ring_refill_cnt;
	u32 mon_status_buf_ring_empty_cnt;
	u32 mon_desc_buf_ring_refill_cnt;
	u32 mon_desc_buf_ring_empty_cnt;
	u32 mon_dest_ring_update_cnt;
	u32 mon_dest_ring_full_cnt;

	u32 rx_suspend_cnt;
	u32 rx_suspend_fail_cnt;
	u32 rx_resume_cnt;
	u32 rx_resume_fail_cnt;
	u32 rx_ring_चयन_cnt;
	u32 rx_ring_restore_cnt;
	u32 rx_flush_cnt;
	u32 rx_recovery_reset_cnt;
पूर्ण;

#घोषणा HTT_STATS_PHY_ERR_MAX 43

काष्ठा htt_rx_pdev_fw_stats_phy_err_tlv अणु
	u32 mac_id__word;
	u32 total_phy_err_cnt;
	/* Counts of dअगरferent types of phy errs
	 * The mapping of PHY error types to phy_err array elements is HW dependent.
	 * The only currently-supported mapping is shown below:
	 *
	 * 0 phyrx_err_phy_off Reception पातed due to receiving a PHY_OFF TLV
	 * 1 phyrx_err_synth_off
	 * 2 phyrx_err_ofdma_timing
	 * 3 phyrx_err_ofdma_संकेत_parity
	 * 4 phyrx_err_ofdma_rate_illegal
	 * 5 phyrx_err_ofdma_length_illegal
	 * 6 phyrx_err_ofdma_restart
	 * 7 phyrx_err_ofdma_service
	 * 8 phyrx_err_ppdu_ofdma_घातer_drop
	 * 9 phyrx_err_cck_blokker
	 * 10 phyrx_err_cck_timing
	 * 11 phyrx_err_cck_header_crc
	 * 12 phyrx_err_cck_rate_illegal
	 * 13 phyrx_err_cck_length_illegal
	 * 14 phyrx_err_cck_restart
	 * 15 phyrx_err_cck_service
	 * 16 phyrx_err_cck_घातer_drop
	 * 17 phyrx_err_ht_crc_err
	 * 18 phyrx_err_ht_length_illegal
	 * 19 phyrx_err_ht_rate_illegal
	 * 20 phyrx_err_ht_zlf
	 * 21 phyrx_err_false_radar_ext
	 * 22 phyrx_err_green_field
	 * 23 phyrx_err_bw_gt_dyn_bw
	 * 24 phyrx_err_leg_ht_mismatch
	 * 25 phyrx_err_vht_crc_error
	 * 26 phyrx_err_vht_siga_unsupported
	 * 27 phyrx_err_vht_lsig_len_invalid
	 * 28 phyrx_err_vht_ndp_or_zlf
	 * 29 phyrx_err_vht_nsym_lt_zero
	 * 30 phyrx_err_vht_rx_extra_symbol_mismatch
	 * 31 phyrx_err_vht_rx_skip_group_id0
	 * 32 phyrx_err_vht_rx_skip_group_id1to62
	 * 33 phyrx_err_vht_rx_skip_group_id63
	 * 34 phyrx_err_ofdm_ldpc_decoder_disabled
	 * 35 phyrx_err_defer_nap
	 * 36 phyrx_err_fकरोमुख्य_समयout
	 * 37 phyrx_err_lsig_rel_check
	 * 38 phyrx_err_bt_collision
	 * 39 phyrx_err_unsupported_mu_feedback
	 * 40 phyrx_err_ppdu_tx_पूर्णांकerrupt_rx
	 * 41 phyrx_err_unsupported_cbf
	 * 42 phyrx_err_other
	 */
	u32 phy_err[HTT_STATS_PHY_ERR_MAX];
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_rx_pdev_fw_ring_mpdu_err_tlv_v अणु
	/* Num error MPDU क्रम each RxDMA error type  */
	u32 fw_ring_mpdu_err[0]; /* HTT_RX_STATS_RXDMA_MAX_ERR */
पूर्ण;

/* NOTE: Variable length TLV, use length spec to infer array size */
काष्ठा htt_rx_pdev_fw_mpdu_drop_tlv_v अणु
	/* Num MPDU dropped  */
	u32 fw_mpdu_drop[0]; /* HTT_RX_STATS_FW_DROP_REASON_MAX */
पूर्ण;

#घोषणा HTT_PDEV_CCA_STATS_TX_FRAME_INFO_PRESENT               (0x1)
#घोषणा HTT_PDEV_CCA_STATS_RX_FRAME_INFO_PRESENT               (0x2)
#घोषणा HTT_PDEV_CCA_STATS_RX_CLEAR_INFO_PRESENT               (0x4)
#घोषणा HTT_PDEV_CCA_STATS_MY_RX_FRAME_INFO_PRESENT            (0x8)
#घोषणा HTT_PDEV_CCA_STATS_USEC_CNT_INFO_PRESENT              (0x10)
#घोषणा HTT_PDEV_CCA_STATS_MED_RX_IDLE_INFO_PRESENT           (0x20)
#घोषणा HTT_PDEV_CCA_STATS_MED_TX_IDLE_GLOBAL_INFO_PRESENT    (0x40)
#घोषणा HTT_PDEV_CCA_STATS_CCA_OBBS_USEC_INFO_PRESENT         (0x80)

काष्ठा htt_pdev_stats_cca_counters_tlv अणु
	/* Below values are obtained from the HW Cycles counter रेजिस्टरs */
	u32 tx_frame_usec;
	u32 rx_frame_usec;
	u32 rx_clear_usec;
	u32 my_rx_frame_usec;
	u32 usec_cnt;
	u32 med_rx_idle_usec;
	u32 med_tx_idle_global_usec;
	u32 cca_obss_usec;
पूर्ण;

काष्ठा htt_pdev_cca_stats_hist_v1_tlv अणु
	u32    chan_num;
	/* num of CCA records (Num of htt_pdev_stats_cca_counters_tlv)*/
	u32    num_records;
	u32    valid_cca_counters_biपंचांगap;
	u32    collection_पूर्णांकerval;

	/* This will be followed by an array which contains the CCA stats
	 * collected in the last N पूर्णांकervals,
	 * अगर the indication is क्रम last N पूर्णांकervals CCA stats.
	 * Then the pdev_cca_stats[0] element contains the oldest CCA stats
	 * and pdev_cca_stats[N-1] will have the most recent CCA stats.
	 * htt_pdev_stats_cca_counters_tlv cca_hist_tlv[1];
	 */
पूर्ण;

काष्ठा htt_pdev_stats_twt_session_tlv अणु
	u32 vdev_id;
	काष्ठा htt_mac_addr peer_mac;
	u32 flow_id_flags;

	/* TWT_DIALOG_ID_UNAVAILABLE is used
	 * when TWT session is not initiated by host
	 */
	u32 dialog_id;
	u32 wake_dura_us;
	u32 wake_पूर्णांकvl_us;
	u32 sp_offset_us;
पूर्ण;

काष्ठा htt_pdev_stats_twt_sessions_tlv अणु
	u32 pdev_id;
	u32 num_sessions;
	काष्ठा htt_pdev_stats_twt_session_tlv twt_session[];
पूर्ण;

क्रमागत htt_rx_reo_resource_sample_id_क्रमागत अणु
	/* Global link descriptor queued in REO */
	HTT_RX_REO_RESOURCE_GLOBAL_LINK_DESC_COUNT_0           = 0,
	HTT_RX_REO_RESOURCE_GLOBAL_LINK_DESC_COUNT_1           = 1,
	HTT_RX_REO_RESOURCE_GLOBAL_LINK_DESC_COUNT_2           = 2,
	/*Number of queue descriptors of this aging group */
	HTT_RX_REO_RESOURCE_BUFFERS_USED_AC0                   = 3,
	HTT_RX_REO_RESOURCE_BUFFERS_USED_AC1                   = 4,
	HTT_RX_REO_RESOURCE_BUFFERS_USED_AC2                   = 5,
	HTT_RX_REO_RESOURCE_BUFFERS_USED_AC3                   = 6,
	/* Total number of MSDUs buffered in AC */
	HTT_RX_REO_RESOURCE_AGING_NUM_QUEUES_AC0               = 7,
	HTT_RX_REO_RESOURCE_AGING_NUM_QUEUES_AC1               = 8,
	HTT_RX_REO_RESOURCE_AGING_NUM_QUEUES_AC2               = 9,
	HTT_RX_REO_RESOURCE_AGING_NUM_QUEUES_AC3               = 10,

	HTT_RX_REO_RESOURCE_STATS_MAX                          = 16
पूर्ण;

काष्ठा htt_rx_reo_resource_stats_tlv_v अणु
	/* Variable based on the Number of records. HTT_RX_REO_RESOURCE_STATS_MAX */
	u32 sample_id;
	u32 total_max;
	u32 total_avg;
	u32 total_sample;
	u32 non_zeros_avg;
	u32 non_zeros_sample;
	u32 last_non_zeros_max;
	u32 last_non_zeros_min;
	u32 last_non_zeros_avg;
	u32 last_non_zeros_sample;
पूर्ण;

/* == TX SOUNDING STATS == */

क्रमागत htt_txbf_sound_steer_modes अणु
	HTT_IMPLICIT_TXBF_STEER_STATS                = 0,
	HTT_EXPLICIT_TXBF_SU_SIFS_STEER_STATS        = 1,
	HTT_EXPLICIT_TXBF_SU_RBO_STEER_STATS         = 2,
	HTT_EXPLICIT_TXBF_MU_SIFS_STEER_STATS        = 3,
	HTT_EXPLICIT_TXBF_MU_RBO_STEER_STATS         = 4,
	HTT_TXBF_MAX_NUM_OF_MODES                    = 5
पूर्ण;

क्रमागत htt_stats_sounding_tx_mode अणु
	HTT_TX_AC_SOUNDING_MODE                      = 0,
	HTT_TX_AX_SOUNDING_MODE                      = 1,
पूर्ण;

काष्ठा htt_tx_sounding_stats_tlv अणु
	u32 tx_sounding_mode; /* HTT_TX_XX_SOUNDING_MODE */
	/* Counts number of soundings क्रम all steering modes in each bw */
	u32 cbf_20[HTT_TXBF_MAX_NUM_OF_MODES];
	u32 cbf_40[HTT_TXBF_MAX_NUM_OF_MODES];
	u32 cbf_80[HTT_TXBF_MAX_NUM_OF_MODES];
	u32 cbf_160[HTT_TXBF_MAX_NUM_OF_MODES];
	/*
	 * The sounding array is a 2-D array stored as an 1-D array of
	 * u32. The stats क्रम a particular user/bw combination is
	 * referenced with the following:
	 *
	 *          sounding[(user* max_bw) + bw]
	 *
	 * ... where max_bw == 4 क्रम 160mhz
	 */
	u32 sounding[HTT_TX_NUM_OF_SOUNDING_STATS_WORDS];
पूर्ण;

काष्ठा htt_pdev_obss_pd_stats_tlv अणु
	u32 num_obss_tx_ppdu_success;
	u32 num_obss_tx_ppdu_failure;
	u32 num_sr_tx_transmissions;
	u32 num_spatial_reuse_opportunities;
	u32 num_non_srg_opportunities;
	u32 num_non_srg_ppdu_tried;
	u32 num_non_srg_ppdu_success;
	u32 num_srg_opportunities;
	u32 num_srg_ppdu_tried;
	u32 num_srg_ppdu_success;
	u32 num_psr_opportunities;
	u32 num_psr_ppdu_tried;
	u32 num_psr_ppdu_success;
पूर्ण;

काष्ठा htt_ring_backpressure_stats_tlv अणु
	u32 pdev_id;
	u32 current_head_idx;
	u32 current_tail_idx;
	u32 num_htt_msgs_sent;
	/* Time in milliseconds क्रम which the ring has been in
	 * its current backpressure condition
	 */
	u32 backpressure_समय_ms;
	/* backpressure_hist - histogram showing how many बार
	 * dअगरferent degrees of backpressure duration occurred:
	 * Index 0 indicates the number of बार ring was
	 * continuously in backpressure state क्रम 100 - 200ms.
	 * Index 1 indicates the number of बार ring was
	 * continuously in backpressure state क्रम 200 - 300ms.
	 * Index 2 indicates the number of बार ring was
	 * continuously in backpressure state क्रम 300 - 400ms.
	 * Index 3 indicates the number of बार ring was
	 * continuously in backpressure state क्रम 400 - 500ms.
	 * Index 4 indicates the number of बार ring was
	 * continuously in backpressure state beyond 500ms.
	 */
	u32 backpressure_hist[5];
पूर्ण;

#अगर_घोषित CONFIG_ATH11K_DEBUGFS

व्योम ath11k_debugfs_htt_stats_init(काष्ठा ath11k *ar);
व्योम ath11k_debugfs_htt_ext_stats_handler(काष्ठा ath11k_base *ab,
					  काष्ठा sk_buff *skb);
पूर्णांक ath11k_debugfs_htt_stats_req(काष्ठा ath11k *ar);

#अन्यथा /* CONFIG_ATH11K_DEBUGFS */

अटल अंतरभूत व्योम ath11k_debugfs_htt_stats_init(काष्ठा ath11k *ar)
अणु
पूर्ण

अटल अंतरभूत व्योम ath11k_debugfs_htt_ext_stats_handler(काष्ठा ath11k_base *ab,
							काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_debugfs_htt_stats_req(काष्ठा ath11k *ar)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH11K_DEBUGFS */

#पूर्ण_अगर
