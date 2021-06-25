<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_HAL_RX_H
#घोषणा ATH11K_HAL_RX_H

काष्ठा hal_rx_wbm_rel_info अणु
	u32 cookie;
	क्रमागत hal_wbm_rel_src_module err_rel_src;
	क्रमागत hal_reo_dest_ring_push_reason push_reason;
	u32 err_code;
	bool first_msdu;
	bool last_msdu;
पूर्ण;

#घोषणा HAL_INVALID_PEERID 0xffff
#घोषणा VHT_SIG_SU_NSS_MASK 0x7

#घोषणा HAL_RX_MAX_MCS 12
#घोषणा HAL_RX_MAX_NSS 8

काष्ठा hal_rx_mon_status_tlv_hdr अणु
	u32 hdr;
	u8 value[];
पूर्ण;

क्रमागत hal_rx_su_mu_coding अणु
	HAL_RX_SU_MU_CODING_BCC,
	HAL_RX_SU_MU_CODING_LDPC,
	HAL_RX_SU_MU_CODING_MAX,
पूर्ण;

क्रमागत hal_rx_gi अणु
	HAL_RX_GI_0_8_US,
	HAL_RX_GI_0_4_US,
	HAL_RX_GI_1_6_US,
	HAL_RX_GI_3_2_US,
	HAL_RX_GI_MAX,
पूर्ण;

क्रमागत hal_rx_bw अणु
	HAL_RX_BW_20MHZ,
	HAL_RX_BW_40MHZ,
	HAL_RX_BW_80MHZ,
	HAL_RX_BW_160MHZ,
	HAL_RX_BW_MAX,
पूर्ण;

क्रमागत hal_rx_preamble अणु
	HAL_RX_PREAMBLE_11A,
	HAL_RX_PREAMBLE_11B,
	HAL_RX_PREAMBLE_11N,
	HAL_RX_PREAMBLE_11AC,
	HAL_RX_PREAMBLE_11AX,
	HAL_RX_PREAMBLE_MAX,
पूर्ण;

क्रमागत hal_rx_reception_type अणु
	HAL_RX_RECEPTION_TYPE_SU,
	HAL_RX_RECEPTION_TYPE_MU_MIMO,
	HAL_RX_RECEPTION_TYPE_MU_OFDMA,
	HAL_RX_RECEPTION_TYPE_MU_OFDMA_MIMO,
	HAL_RX_RECEPTION_TYPE_MAX,
पूर्ण;

#घोषणा HAL_TLV_STATUS_PPDU_NOT_DONE            0
#घोषणा HAL_TLV_STATUS_PPDU_DONE                1
#घोषणा HAL_TLV_STATUS_BUF_DONE                 2
#घोषणा HAL_TLV_STATUS_PPDU_NON_STD_DONE        3
#घोषणा HAL_RX_FCS_LEN                          4

क्रमागत hal_rx_mon_status अणु
	HAL_RX_MON_STATUS_PPDU_NOT_DONE,
	HAL_RX_MON_STATUS_PPDU_DONE,
	HAL_RX_MON_STATUS_BUF_DONE,
पूर्ण;

काष्ठा hal_rx_mon_ppdu_info अणु
	u32 ppdu_id;
	u32 ppdu_ts;
	u32 num_mpdu_fcs_ok;
	u32 num_mpdu_fcs_err;
	u32 preamble_type;
	u16 chan_num;
	u16 tcp_msdu_count;
	u16 tcp_ack_msdu_count;
	u16 udp_msdu_count;
	u16 other_msdu_count;
	u16 peer_id;
	u8 rate;
	u8 mcs;
	u8 nss;
	u8 bw;
	u8 is_stbc;
	u8 gi;
	u8 ldpc;
	u8 beamक्रमmed;
	u8 rssi_comb;
	u8 tid;
	u8 dcm;
	u8 ru_alloc;
	u8 reception_type;
	u64 rx_duration;
पूर्ण;

#घोषणा HAL_RX_PPDU_START_INFO0_PPDU_ID		GENMASK(15, 0)

काष्ठा hal_rx_ppdu_start अणु
	__le32 info0;
	__le32 chan_num;
	__le32 ppdu_start_ts;
पूर्ण __packed;

#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO0_MPDU_CNT_FCS_ERR	GENMASK(25, 16)

#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO1_MPDU_CNT_FCS_OK	GENMASK(8, 0)
#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO1_FC_VALID		BIT(9)
#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO1_QOS_CTRL_VALID		BIT(10)
#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO1_HT_CTRL_VALID		BIT(11)
#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO1_PKT_TYPE		GENMASK(23, 20)

#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO2_AST_INDEX		GENMASK(15, 0)
#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO2_FRAME_CTRL		GENMASK(31, 16)

#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO3_QOS_CTRL		GENMASK(31, 16)

#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO4_UDP_MSDU_CNT		GENMASK(15, 0)
#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO4_TCP_MSDU_CNT		GENMASK(31, 16)

#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO5_OTHER_MSDU_CNT		GENMASK(15, 0)
#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO5_TCP_ACK_MSDU_CNT	GENMASK(31, 16)

#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO6_TID_BITMAP		GENMASK(15, 0)
#घोषणा HAL_RX_PPDU_END_USER_STATS_INFO6_TID_EOSP_BITMAP	GENMASK(31, 16)

काष्ठा hal_rx_ppdu_end_user_stats अणु
	__le32 rsvd0[2];
	__le32 info0;
	__le32 info1;
	__le32 info2;
	__le32 info3;
	__le32 ht_ctrl;
	__le32 rsvd1[2];
	__le32 info4;
	__le32 info5;
	__le32 info6;
	__le32 rsvd2[11];
पूर्ण __packed;

#घोषणा HAL_RX_HT_SIG_INFO_INFO0_MCS		GENMASK(6, 0)
#घोषणा HAL_RX_HT_SIG_INFO_INFO0_BW		BIT(7)

#घोषणा HAL_RX_HT_SIG_INFO_INFO1_STBC		GENMASK(5, 4)
#घोषणा HAL_RX_HT_SIG_INFO_INFO1_FEC_CODING	BIT(6)
#घोषणा HAL_RX_HT_SIG_INFO_INFO1_GI		BIT(7)

काष्ठा hal_rx_ht_sig_info अणु
	__le32 info0;
	__le32 info1;
पूर्ण __packed;

#घोषणा HAL_RX_LSIG_B_INFO_INFO0_RATE	GENMASK(3, 0)
#घोषणा HAL_RX_LSIG_B_INFO_INFO0_LEN	GENMASK(15, 4)

काष्ठा hal_rx_lsig_b_info अणु
	__le32 info0;
पूर्ण __packed;

#घोषणा HAL_RX_LSIG_A_INFO_INFO0_RATE		GENMASK(3, 0)
#घोषणा HAL_RX_LSIG_A_INFO_INFO0_LEN		GENMASK(16, 5)
#घोषणा HAL_RX_LSIG_A_INFO_INFO0_PKT_TYPE	GENMASK(27, 24)

काष्ठा hal_rx_lsig_a_info अणु
	__le32 info0;
पूर्ण __packed;

#घोषणा HAL_RX_VHT_SIG_A_INFO_INFO0_BW		GENMASK(1, 0)
#घोषणा HAL_RX_VHT_SIG_A_INFO_INFO0_STBC	BIT(3)
#घोषणा HAL_RX_VHT_SIG_A_INFO_INFO0_GROUP_ID	GENMASK(9, 4)
#घोषणा HAL_RX_VHT_SIG_A_INFO_INFO0_NSTS	GENMASK(21, 10)

#घोषणा HAL_RX_VHT_SIG_A_INFO_INFO1_GI_SETTING		GENMASK(1, 0)
#घोषणा HAL_RX_VHT_SIG_A_INFO_INFO1_SU_MU_CODING	BIT(2)
#घोषणा HAL_RX_VHT_SIG_A_INFO_INFO1_MCS			GENMASK(7, 4)
#घोषणा HAL_RX_VHT_SIG_A_INFO_INFO1_BEAMFORMED		BIT(8)

काष्ठा hal_rx_vht_sig_a_info अणु
	__le32 info0;
	__le32 info1;
पूर्ण __packed;

क्रमागत hal_rx_vht_sig_a_gi_setting अणु
	HAL_RX_VHT_SIG_A_NORMAL_GI = 0,
	HAL_RX_VHT_SIG_A_SHORT_GI = 1,
	HAL_RX_VHT_SIG_A_SHORT_GI_AMBIGUITY = 3,
पूर्ण;

#घोषणा HAL_RX_HE_SIG_A_SU_INFO_INFO0_TRANSMIT_MCS	GENMASK(6, 3)
#घोषणा HAL_RX_HE_SIG_A_SU_INFO_INFO0_DCM		BIT(7)
#घोषणा HAL_RX_HE_SIG_A_SU_INFO_INFO0_TRANSMIT_BW	GENMASK(20, 19)
#घोषणा HAL_RX_HE_SIG_A_SU_INFO_INFO0_CP_LTF_SIZE	GENMASK(22, 21)
#घोषणा HAL_RX_HE_SIG_A_SU_INFO_INFO0_NSTS		GENMASK(25, 23)

#घोषणा HAL_RX_HE_SIG_A_SU_INFO_INFO1_CODING		BIT(7)
#घोषणा HAL_RX_HE_SIG_A_SU_INFO_INFO1_STBC		BIT(9)
#घोषणा HAL_RX_HE_SIG_A_SU_INFO_INFO1_TXBF		BIT(10)

काष्ठा hal_rx_he_sig_a_su_info अणु
	__le32 info0;
	__le32 info1;
पूर्ण __packed;

#घोषणा HAL_RX_HE_SIG_A_MU_DL_INFO_INFO0_TRANSMIT_BW	GENMASK(17, 15)
#घोषणा HAL_RX_HE_SIG_A_MU_DL_INFO_INFO0_CP_LTF_SIZE	GENMASK(24, 23)

#घोषणा HAL_RX_HE_SIG_A_MU_DL_INFO_INFO1_STBC		BIT(12)

काष्ठा hal_rx_he_sig_a_mu_dl_info अणु
	__le32 info0;
	__le32 info1;
पूर्ण __packed;

#घोषणा HAL_RX_HE_SIG_B1_MU_INFO_INFO0_RU_ALLOCATION	GENMASK(7, 0)

काष्ठा hal_rx_he_sig_b1_mu_info अणु
	__le32 info0;
पूर्ण __packed;

#घोषणा HAL_RX_HE_SIG_B2_MU_INFO_INFO0_STA_MCS		GENMASK(18, 15)
#घोषणा HAL_RX_HE_SIG_B2_MU_INFO_INFO0_STA_CODING	BIT(20)
#घोषणा HAL_RX_HE_SIG_B2_MU_INFO_INFO0_STA_NSTS		GENMASK(31, 29)

काष्ठा hal_rx_he_sig_b2_mu_info अणु
	__le32 info0;
पूर्ण __packed;

#घोषणा HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_NSTS	GENMASK(13, 11)
#घोषणा HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_TXBF	BIT(19)
#घोषणा HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_MCS	GENMASK(18, 15)
#घोषणा HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_DCM	BIT(19)
#घोषणा HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_CODING	BIT(20)

काष्ठा hal_rx_he_sig_b2_ofdma_info अणु
	__le32 info0;
पूर्ण __packed;

#घोषणा HAL_RX_PHYRX_RSSI_LEGACY_INFO_INFO1_RSSI_COMB	GENMASK(15, 8)

काष्ठा hal_rx_phyrx_rssi_legacy_info अणु
	__le32 rsvd[35];
	__le32 info0;
पूर्ण __packed;

#घोषणा HAL_RX_MPDU_INFO_INFO0_PEERID	GENMASK(31, 16)
काष्ठा hal_rx_mpdu_info अणु
	__le32 rsvd0;
	__le32 info0;
	__le32 rsvd1[21];
पूर्ण __packed;

#घोषणा HAL_RX_PPDU_END_DURATION	GENMASK(23, 0)
काष्ठा hal_rx_ppdu_end_duration अणु
	__le32 rsvd0[9];
	__le32 info0;
	__le32 rsvd1[4];
पूर्ण __packed;

काष्ठा hal_rx_rxpcu_classअगरication_overview अणु
	u32 rsvd0;
पूर्ण __packed;

काष्ठा hal_rx_msdu_desc_info अणु
	u32 msdu_flags;
	u16 msdu_len; /* 14 bits क्रम length */
पूर्ण;

#घोषणा HAL_RX_NUM_MSDU_DESC 6
काष्ठा hal_rx_msdu_list अणु
	काष्ठा hal_rx_msdu_desc_info msdu_info[HAL_RX_NUM_MSDU_DESC];
	u32 sw_cookie[HAL_RX_NUM_MSDU_DESC];
	u8 rbm[HAL_RX_NUM_MSDU_DESC];
पूर्ण;

व्योम ath11k_hal_reo_status_queue_stats(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status);
व्योम ath11k_hal_reo_flush_queue_status(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status);
व्योम ath11k_hal_reo_flush_cache_status(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status);
व्योम ath11k_hal_reo_flush_cache_status(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status);
व्योम ath11k_hal_reo_unblk_cache_status(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status);
व्योम ath11k_hal_reo_flush_समयout_list_status(काष्ठा ath11k_base *ab,
					      u32 *reo_desc,
					      काष्ठा hal_reo_status *status);
व्योम ath11k_hal_reo_desc_thresh_reached_status(काष्ठा ath11k_base *ab,
					       u32 *reo_desc,
					       काष्ठा hal_reo_status *status);
व्योम ath11k_hal_reo_update_rx_reo_queue_status(काष्ठा ath11k_base *ab,
					       u32 *reo_desc,
					       काष्ठा hal_reo_status *status);
पूर्णांक ath11k_hal_reo_process_status(u8 *reo_desc, u8 *status);
व्योम ath11k_hal_rx_msdu_link_info_get(व्योम *link_desc, u32 *num_msdus,
				      u32 *msdu_cookies,
				      क्रमागत hal_rx_buf_वापस_buf_manager *rbm);
व्योम ath11k_hal_rx_msdu_link_desc_set(काष्ठा ath11k_base *ab, व्योम *desc,
				      व्योम *link_desc,
				      क्रमागत hal_wbm_rel_bm_act action);
व्योम ath11k_hal_rx_buf_addr_info_set(व्योम *desc, dma_addr_t paddr,
				     u32 cookie, u8 manager);
व्योम ath11k_hal_rx_buf_addr_info_get(व्योम *desc, dma_addr_t *paddr,
				     u32 *cookie, u8 *rbm);
पूर्णांक ath11k_hal_desc_reo_parse_err(काष्ठा ath11k_base *ab, u32 *rx_desc,
				  dma_addr_t *paddr, u32 *desc_bank);
पूर्णांक ath11k_hal_wbm_desc_parse_err(काष्ठा ath11k_base *ab, व्योम *desc,
				  काष्ठा hal_rx_wbm_rel_info *rel_info);
व्योम ath11k_hal_rx_reo_ent_paddr_get(काष्ठा ath11k_base *ab, व्योम *desc,
				     dma_addr_t *paddr, u32 *desc_bank);
व्योम ath11k_hal_rx_reo_ent_buf_paddr_get(व्योम *rx_desc,
					 dma_addr_t *paddr, u32 *sw_cookie,
					 व्योम **pp_buf_addr_info, u8 *rbm,
					 u32 *msdu_cnt);
क्रमागत hal_rx_mon_status
ath11k_hal_rx_parse_mon_status(काष्ठा ath11k_base *ab,
			       काष्ठा hal_rx_mon_ppdu_info *ppdu_info,
			       काष्ठा sk_buff *skb);

अटल अंतरभूत u32 ath11k_he_ru_tones_to_nl80211_he_ru_alloc(u16 ru_tones)
अणु
	u32 ret = 0;

	चयन (ru_tones) अणु
	हाल RU_26:
		ret = NL80211_RATE_INFO_HE_RU_ALLOC_26;
		अवरोध;
	हाल RU_52:
		ret = NL80211_RATE_INFO_HE_RU_ALLOC_52;
		अवरोध;
	हाल RU_106:
		ret = NL80211_RATE_INFO_HE_RU_ALLOC_106;
		अवरोध;
	हाल RU_242:
		ret = NL80211_RATE_INFO_HE_RU_ALLOC_242;
		अवरोध;
	हाल RU_484:
		ret = NL80211_RATE_INFO_HE_RU_ALLOC_484;
		अवरोध;
	हाल RU_996:
		ret = NL80211_RATE_INFO_HE_RU_ALLOC_996;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा REO_QUEUE_DESC_MAGIC_DEBUG_PATTERN_0 0xDDBEEF
#घोषणा REO_QUEUE_DESC_MAGIC_DEBUG_PATTERN_1 0xADBEEF
#घोषणा REO_QUEUE_DESC_MAGIC_DEBUG_PATTERN_2 0xBDBEEF
#घोषणा REO_QUEUE_DESC_MAGIC_DEBUG_PATTERN_3 0xCDBEEF
#पूर्ण_अगर
