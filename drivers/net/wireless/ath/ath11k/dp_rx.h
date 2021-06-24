<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित ATH11K_DP_RX_H
#घोषणा ATH11K_DP_RX_H

#समावेश "core.h"
#समावेश "rx_desc.h"
#समावेश "debug.h"

#घोषणा DP_MAX_NWIFI_HDR_LEN	30

#घोषणा DP_RX_MPDU_ERR_FCS			BIT(0)
#घोषणा DP_RX_MPDU_ERR_DECRYPT			BIT(1)
#घोषणा DP_RX_MPDU_ERR_TKIP_MIC			BIT(2)
#घोषणा DP_RX_MPDU_ERR_AMSDU_ERR		BIT(3)
#घोषणा DP_RX_MPDU_ERR_OVERFLOW			BIT(4)
#घोषणा DP_RX_MPDU_ERR_MSDU_LEN			BIT(5)
#घोषणा DP_RX_MPDU_ERR_MPDU_LEN			BIT(6)
#घोषणा DP_RX_MPDU_ERR_UNENCRYPTED_FRAME	BIT(7)

क्रमागत dp_rx_decap_type अणु
	DP_RX_DECAP_TYPE_RAW,
	DP_RX_DECAP_TYPE_NATIVE_WIFI,
	DP_RX_DECAP_TYPE_ETHERNET2_DIX,
	DP_RX_DECAP_TYPE_8023,
पूर्ण;

काष्ठा ath11k_dp_amsdu_subframe_hdr अणु
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	__be16 len;
पूर्ण __packed;

काष्ठा ath11k_dp_rfc1042_hdr अणु
	u8 llc_dsap;
	u8 llc_ssap;
	u8 llc_ctrl;
	u8 snap_oui[3];
	__be16 snap_type;
पूर्ण __packed;

पूर्णांक ath11k_dp_rx_ampdu_start(काष्ठा ath11k *ar,
			     काष्ठा ieee80211_ampdu_params *params);
पूर्णांक ath11k_dp_rx_ampdu_stop(काष्ठा ath11k *ar,
			    काष्ठा ieee80211_ampdu_params *params);
पूर्णांक ath11k_dp_peer_rx_pn_replay_config(काष्ठा ath11k_vअगर *arvअगर,
				       स्थिर u8 *peer_addr,
				       क्रमागत set_key_cmd key_cmd,
				       काष्ठा ieee80211_key_conf *key);
व्योम ath11k_peer_frags_flush(काष्ठा ath11k *ar, काष्ठा ath11k_peer *peer);
व्योम ath11k_peer_rx_tid_cleanup(काष्ठा ath11k *ar, काष्ठा ath11k_peer *peer);
व्योम ath11k_peer_rx_tid_delete(काष्ठा ath11k *ar,
			       काष्ठा ath11k_peer *peer, u8 tid);
पूर्णांक ath11k_peer_rx_tid_setup(काष्ठा ath11k *ar, स्थिर u8 *peer_mac, पूर्णांक vdev_id,
			     u8 tid, u32 ba_win_sz, u16 ssn,
			     क्रमागत hal_pn_type pn_type);
व्योम ath11k_dp_htt_htc_t2h_msg_handler(काष्ठा ath11k_base *ab,
				       काष्ठा sk_buff *skb);
पूर्णांक ath11k_dp_pdev_reo_setup(काष्ठा ath11k_base *ab);
व्योम ath11k_dp_pdev_reo_cleanup(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_dp_rx_pdev_alloc(काष्ठा ath11k_base *ab, पूर्णांक pdev_idx);
व्योम ath11k_dp_rx_pdev_मुक्त(काष्ठा ath11k_base *ab, पूर्णांक pdev_idx);
व्योम ath11k_dp_reo_cmd_list_cleanup(काष्ठा ath11k_base *ab);
व्योम ath11k_dp_process_reo_status(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_dp_process_rxdma_err(काष्ठा ath11k_base *ab, पूर्णांक mac_id, पूर्णांक budget);
पूर्णांक ath11k_dp_rx_process_wbm_err(काष्ठा ath11k_base *ab,
				 काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक ath11k_dp_process_rx_err(काष्ठा ath11k_base *ab, काष्ठा napi_काष्ठा *napi,
			     पूर्णांक budget);
पूर्णांक ath11k_dp_process_rx(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
			 काष्ठा napi_काष्ठा *napi,
			 पूर्णांक budget);
पूर्णांक ath11k_dp_rxbufs_replenish(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
			       काष्ठा dp_rxdma_ring *rx_ring,
			       पूर्णांक req_entries,
			       क्रमागत hal_rx_buf_वापस_buf_manager mgr);
पूर्णांक ath11k_dp_htt_tlv_iter(काष्ठा ath11k_base *ab, स्थिर व्योम *ptr, माप_प्रकार len,
			   पूर्णांक (*iter)(काष्ठा ath11k_base *ar, u16 tag, u16 len,
				       स्थिर व्योम *ptr, व्योम *data),
			   व्योम *data);
पूर्णांक ath11k_dp_rx_process_mon_rings(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
				   काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक ath11k_dp_rx_process_mon_status(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
				    काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक ath11k_dp_rx_mon_status_bufs_replenish(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
					   काष्ठा dp_rxdma_ring *rx_ring,
					   पूर्णांक req_entries,
					   क्रमागत hal_rx_buf_वापस_buf_manager mgr);
पूर्णांक ath11k_dp_rx_pdev_mon_detach(काष्ठा ath11k *ar);
पूर्णांक ath11k_dp_rx_pdev_mon_attach(काष्ठा ath11k *ar);
पूर्णांक ath11k_peer_rx_frag_setup(काष्ठा ath11k *ar, स्थिर u8 *peer_mac, पूर्णांक vdev_id);

पूर्णांक ath11k_dp_rx_pktlog_start(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_dp_rx_pktlog_stop(काष्ठा ath11k_base *ab, bool stop_समयr);

#पूर्ण_अगर /* ATH11K_DP_RX_H */
