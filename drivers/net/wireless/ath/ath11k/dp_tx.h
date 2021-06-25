<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_DP_TX_H
#घोषणा ATH11K_DP_TX_H

#समावेश "core.h"
#समावेश "hal_tx.h"

काष्ठा ath11k_dp_htt_wbm_tx_status अणु
	u32 msdu_id;
	bool acked;
	पूर्णांक ack_rssi;
पूर्ण;

पूर्णांक ath11k_dp_tx_htt_h2t_ver_req_msg(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_dp_tx(काष्ठा ath11k *ar, काष्ठा ath11k_vअगर *arvअगर,
		 काष्ठा sk_buff *skb);
व्योम ath11k_dp_tx_completion_handler(काष्ठा ath11k_base *ab, पूर्णांक ring_id);
पूर्णांक ath11k_dp_tx_send_reo_cmd(काष्ठा ath11k_base *ab, काष्ठा dp_rx_tid *rx_tid,
			      क्रमागत hal_reo_cmd_type type,
			      काष्ठा ath11k_hal_reo_cmd *cmd,
			      व्योम (*func)(काष्ठा ath11k_dp *, व्योम *,
					   क्रमागत hal_reo_cmd_status));

पूर्णांक ath11k_dp_tx_htt_h2t_ppdu_stats_req(काष्ठा ath11k *ar, u32 mask);
पूर्णांक
ath11k_dp_tx_htt_h2t_ext_stats_req(काष्ठा ath11k *ar, u8 type,
				   काष्ठा htt_ext_stats_cfg_params *cfg_params,
				   u64 cookie);
पूर्णांक ath11k_dp_tx_htt_monitor_mode_ring_config(काष्ठा ath11k *ar, bool reset);

पूर्णांक ath11k_dp_tx_htt_rx_filter_setup(काष्ठा ath11k_base *ab, u32 ring_id,
				     पूर्णांक mac_id, क्रमागत hal_ring_type ring_type,
				     पूर्णांक rx_buf_size,
				     काष्ठा htt_rx_ring_tlv_filter *tlv_filter);

#पूर्ण_अगर
