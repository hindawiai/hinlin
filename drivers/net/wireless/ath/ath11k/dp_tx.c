<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश "core.h"
#समावेश "dp_tx.h"
#समावेश "debug.h"
#समावेश "debugfs_sta.h"
#समावेश "hw.h"
#समावेश "peer.h"

अटल क्रमागत hal_tcl_encap_type
ath11k_dp_tx_get_encap_type(काष्ठा ath11k_vअगर *arvअगर, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ath11k_base *ab = arvअगर->ar->ab;

	अगर (test_bit(ATH11K_FLAG_RAW_MODE, &ab->dev_flags))
		वापस HAL_TCL_ENCAP_TYPE_RAW;

	अगर (tx_info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP)
		वापस HAL_TCL_ENCAP_TYPE_ETHERNET;

	वापस HAL_TCL_ENCAP_TYPE_NATIVE_WIFI;
पूर्ण

अटल व्योम ath11k_dp_tx_encap_nwअगरi(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	u8 *qos_ctl;

	अगर (!ieee80211_is_data_qos(hdr->frame_control))
		वापस;

	qos_ctl = ieee80211_get_qos_ctl(hdr);
	स_हटाओ(skb->data + IEEE80211_QOS_CTL_LEN,
		skb->data, (व्योम *)qos_ctl - (व्योम *)skb->data);
	skb_pull(skb, IEEE80211_QOS_CTL_LEN);

	hdr = (व्योम *)skb->data;
	hdr->frame_control &= ~__cpu_to_le16(IEEE80211_STYPE_QOS_DATA);
पूर्ण

अटल u8 ath11k_dp_tx_get_tid(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा ath11k_skb_cb *cb = ATH11K_SKB_CB(skb);

	अगर (cb->flags & ATH11K_SKB_HW_80211_ENCAP)
		वापस skb->priority & IEEE80211_QOS_CTL_TID_MASK;
	अन्यथा अगर (!ieee80211_is_data_qos(hdr->frame_control))
		वापस HAL_DESC_REO_NON_QOS_TID;
	अन्यथा
		वापस skb->priority & IEEE80211_QOS_CTL_TID_MASK;
पूर्ण

क्रमागत hal_encrypt_type ath11k_dp_tx_get_encrypt_type(u32 cipher)
अणु
	चयन (cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		वापस HAL_ENCRYPT_TYPE_WEP_40;
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस HAL_ENCRYPT_TYPE_WEP_104;
	हाल WLAN_CIPHER_SUITE_TKIP:
		वापस HAL_ENCRYPT_TYPE_TKIP_MIC;
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस HAL_ENCRYPT_TYPE_CCMP_128;
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		वापस HAL_ENCRYPT_TYPE_CCMP_256;
	हाल WLAN_CIPHER_SUITE_GCMP:
		वापस HAL_ENCRYPT_TYPE_GCMP_128;
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		वापस HAL_ENCRYPT_TYPE_AES_GCMP_256;
	शेष:
		वापस HAL_ENCRYPT_TYPE_OPEN;
	पूर्ण
पूर्ण

पूर्णांक ath11k_dp_tx(काष्ठा ath11k *ar, काष्ठा ath11k_vअगर *arvअगर,
		 काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा hal_tx_info ti = अणु0पूर्ण;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ath11k_skb_cb *skb_cb = ATH11K_SKB_CB(skb);
	काष्ठा hal_srng *tcl_ring;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा dp_tx_ring *tx_ring;
	व्योम *hal_tcl_desc;
	u8 pool_id;
	u8 hal_ring_id;
	पूर्णांक ret;
	u8 ring_selector = 0, ring_map = 0;
	bool tcl_ring_retry;

	अगर (test_bit(ATH11K_FLAG_CRASH_FLUSH, &ar->ab->dev_flags))
		वापस -ESHUTDOWN;

	अगर (!(info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP) &&
	    !ieee80211_is_data(hdr->frame_control))
		वापस -ENOTSUPP;

	pool_id = skb_get_queue_mapping(skb) & (ATH11K_HW_MAX_QUEUES - 1);

	/* Let the शेष ring selection be based on current processor
	 * number, where one of the 3 tcl rings are selected based on
	 * the smp_processor_id(). In हाल that ring
	 * is full/busy, we resort to other available rings.
	 * If all rings are full, we drop the packet.
	 * //TODO Add throttling logic when all rings are full
	 */
	ring_selector = smp_processor_id();

tcl_ring_sel:
	tcl_ring_retry = false;
	/* For some chip, it can only use tcl0 to tx */
	अगर (ar->ab->hw_params.tcl_0_only)
		ti.ring_id = 0;
	अन्यथा
		ti.ring_id = ring_selector % DP_TCL_NUM_RING_MAX;

	ring_map |= BIT(ti.ring_id);

	tx_ring = &dp->tx_ring[ti.ring_id];

	spin_lock_bh(&tx_ring->tx_idr_lock);
	ret = idr_alloc(&tx_ring->txbuf_idr, skb, 0,
			DP_TX_IDR_SIZE - 1, GFP_ATOMIC);
	spin_unlock_bh(&tx_ring->tx_idr_lock);

	अगर (ret < 0) अणु
		अगर (ring_map == (BIT(DP_TCL_NUM_RING_MAX) - 1)) अणु
			atomic_inc(&ab->soc_stats.tx_err.misc_fail);
			वापस -ENOSPC;
		पूर्ण

		/* Check अगर the next ring is available */
		ring_selector++;
		जाओ tcl_ring_sel;
	पूर्ण

	ti.desc_id = FIELD_PREP(DP_TX_DESC_ID_MAC_ID, ar->pdev_idx) |
		     FIELD_PREP(DP_TX_DESC_ID_MSDU_ID, ret) |
		     FIELD_PREP(DP_TX_DESC_ID_POOL_ID, pool_id);
	ti.encap_type = ath11k_dp_tx_get_encap_type(arvअगर, skb);
	ti.meta_data_flags = arvअगर->tcl_metadata;

	अगर (ti.encap_type == HAL_TCL_ENCAP_TYPE_RAW) अणु
		अगर (skb_cb->flags & ATH11K_SKB_CIPHER_SET) अणु
			ti.encrypt_type =
				ath11k_dp_tx_get_encrypt_type(skb_cb->cipher);

			अगर (ieee80211_has_रक्षित(hdr->frame_control))
				skb_put(skb, IEEE80211_CCMP_MIC_LEN);
		पूर्ण अन्यथा अणु
			ti.encrypt_type = HAL_ENCRYPT_TYPE_OPEN;
		पूर्ण
	पूर्ण

	ti.addr_search_flags = arvअगर->hal_addr_search_flags;
	ti.search_type = arvअगर->search_type;
	ti.type = HAL_TCL_DESC_TYPE_BUFFER;
	ti.pkt_offset = 0;
	ti.lmac_id = ar->lmac_id;
	ti.bss_ast_hash = arvअगर->ast_hash;
	ti.bss_ast_idx = arvअगर->ast_idx;
	ti.dscp_tid_tbl_idx = 0;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    ti.encap_type != HAL_TCL_ENCAP_TYPE_RAW) अणु
		ti.flags0 |= FIELD_PREP(HAL_TCL_DATA_CMD_INFO1_IP4_CKSUM_EN, 1) |
			     FIELD_PREP(HAL_TCL_DATA_CMD_INFO1_UDP4_CKSUM_EN, 1) |
			     FIELD_PREP(HAL_TCL_DATA_CMD_INFO1_UDP6_CKSUM_EN, 1) |
			     FIELD_PREP(HAL_TCL_DATA_CMD_INFO1_TCP4_CKSUM_EN, 1) |
			     FIELD_PREP(HAL_TCL_DATA_CMD_INFO1_TCP6_CKSUM_EN, 1);
	पूर्ण

	अगर (ieee80211_vअगर_is_mesh(arvअगर->vअगर))
		ti.enable_mesh = true;

	ti.flags1 |= FIELD_PREP(HAL_TCL_DATA_CMD_INFO2_TID_OVERWRITE, 1);

	ti.tid = ath11k_dp_tx_get_tid(skb);

	चयन (ti.encap_type) अणु
	हाल HAL_TCL_ENCAP_TYPE_NATIVE_WIFI:
		ath11k_dp_tx_encap_nwअगरi(skb);
		अवरोध;
	हाल HAL_TCL_ENCAP_TYPE_RAW:
		अगर (!test_bit(ATH11K_FLAG_RAW_MODE, &ab->dev_flags)) अणु
			ret = -EINVAL;
			जाओ fail_हटाओ_idr;
		पूर्ण
		अवरोध;
	हाल HAL_TCL_ENCAP_TYPE_ETHERNET:
		/* no need to encap */
		अवरोध;
	हाल HAL_TCL_ENCAP_TYPE_802_3:
	शेष:
		/* TODO: Take care of other encap modes as well */
		ret = -EINVAL;
		atomic_inc(&ab->soc_stats.tx_err.misc_fail);
		जाओ fail_हटाओ_idr;
	पूर्ण

	ti.paddr = dma_map_single(ab->dev, skb->data, skb->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ab->dev, ti.paddr)) अणु
		atomic_inc(&ab->soc_stats.tx_err.misc_fail);
		ath11k_warn(ab, "failed to DMA map data Tx buffer\n");
		ret = -ENOMEM;
		जाओ fail_हटाओ_idr;
	पूर्ण

	ti.data_len = skb->len;
	skb_cb->paddr = ti.paddr;
	skb_cb->vअगर = arvअगर->vअगर;
	skb_cb->ar = ar;

	hal_ring_id = tx_ring->tcl_data_ring.ring_id;
	tcl_ring = &ab->hal.srng_list[hal_ring_id];

	spin_lock_bh(&tcl_ring->lock);

	ath11k_hal_srng_access_begin(ab, tcl_ring);

	hal_tcl_desc = (व्योम *)ath11k_hal_srng_src_get_next_entry(ab, tcl_ring);
	अगर (!hal_tcl_desc) अणु
		/* NOTE: It is highly unlikely we'll be running out of tcl_ring
		 * desc because the desc is directly enqueued onto hw queue.
		 */
		ath11k_hal_srng_access_end(ab, tcl_ring);
		ab->soc_stats.tx_err.desc_na[ti.ring_id]++;
		spin_unlock_bh(&tcl_ring->lock);
		ret = -ENOMEM;

		/* Checking क्रम available tcl descritors in another ring in
		 * हाल of failure due to full tcl ring now, is better than
		 * checking this ring earlier क्रम each pkt tx.
		 * Restart ring selection अगर some rings are not checked yet.
		 */
		अगर (ring_map != (BIT(DP_TCL_NUM_RING_MAX) - 1) &&
		    !ar->ab->hw_params.tcl_0_only) अणु
			tcl_ring_retry = true;
			ring_selector++;
		पूर्ण

		जाओ fail_unmap_dma;
	पूर्ण

	ath11k_hal_tx_cmd_desc_setup(ab, hal_tcl_desc +
					 माप(काष्ठा hal_tlv_hdr), &ti);

	ath11k_hal_srng_access_end(ab, tcl_ring);

	ath11k_dp_shaकरोw_start_समयr(ab, tcl_ring, &dp->tx_ring_समयr[ti.ring_id]);

	spin_unlock_bh(&tcl_ring->lock);

	ath11k_dbg_dump(ab, ATH11K_DBG_DP_TX, शून्य, "dp tx msdu: ",
			skb->data, skb->len);

	atomic_inc(&ar->dp.num_tx_pending);

	वापस 0;

fail_unmap_dma:
	dma_unmap_single(ab->dev, ti.paddr, ti.data_len, DMA_TO_DEVICE);

fail_हटाओ_idr:
	spin_lock_bh(&tx_ring->tx_idr_lock);
	idr_हटाओ(&tx_ring->txbuf_idr,
		   FIELD_GET(DP_TX_DESC_ID_MSDU_ID, ti.desc_id));
	spin_unlock_bh(&tx_ring->tx_idr_lock);

	अगर (tcl_ring_retry)
		जाओ tcl_ring_sel;

	वापस ret;
पूर्ण

अटल व्योम ath11k_dp_tx_मुक्त_txbuf(काष्ठा ath11k_base *ab, u8 mac_id,
				    पूर्णांक msdu_id,
				    काष्ठा dp_tx_ring *tx_ring)
अणु
	काष्ठा ath11k *ar;
	काष्ठा sk_buff *msdu;
	काष्ठा ath11k_skb_cb *skb_cb;

	spin_lock_bh(&tx_ring->tx_idr_lock);
	msdu = idr_find(&tx_ring->txbuf_idr, msdu_id);
	अगर (!msdu) अणु
		ath11k_warn(ab, "tx completion for unknown msdu_id %d\n",
			    msdu_id);
		spin_unlock_bh(&tx_ring->tx_idr_lock);
		वापस;
	पूर्ण

	skb_cb = ATH11K_SKB_CB(msdu);

	idr_हटाओ(&tx_ring->txbuf_idr, msdu_id);
	spin_unlock_bh(&tx_ring->tx_idr_lock);

	dma_unmap_single(ab->dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);
	dev_kमुक्त_skb_any(msdu);

	ar = ab->pdevs[mac_id].ar;
	अगर (atomic_dec_and_test(&ar->dp.num_tx_pending))
		wake_up(&ar->dp.tx_empty_रुकोq);
पूर्ण

अटल व्योम
ath11k_dp_tx_htt_tx_complete_buf(काष्ठा ath11k_base *ab,
				 काष्ठा dp_tx_ring *tx_ring,
				 काष्ठा ath11k_dp_htt_wbm_tx_status *ts)
अणु
	काष्ठा sk_buff *msdu;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ath11k_skb_cb *skb_cb;
	काष्ठा ath11k *ar;

	spin_lock_bh(&tx_ring->tx_idr_lock);
	msdu = idr_find(&tx_ring->txbuf_idr, ts->msdu_id);
	अगर (!msdu) अणु
		ath11k_warn(ab, "htt tx completion for unknown msdu_id %d\n",
			    ts->msdu_id);
		spin_unlock_bh(&tx_ring->tx_idr_lock);
		वापस;
	पूर्ण

	skb_cb = ATH11K_SKB_CB(msdu);
	info = IEEE80211_SKB_CB(msdu);

	ar = skb_cb->ar;

	idr_हटाओ(&tx_ring->txbuf_idr, ts->msdu_id);
	spin_unlock_bh(&tx_ring->tx_idr_lock);

	अगर (atomic_dec_and_test(&ar->dp.num_tx_pending))
		wake_up(&ar->dp.tx_empty_रुकोq);

	dma_unmap_single(ab->dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);

	स_रखो(&info->status, 0, माप(info->status));

	अगर (ts->acked) अणु
		अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK)) अणु
			info->flags |= IEEE80211_TX_STAT_ACK;
			info->status.ack_संकेत = ATH11K_DEFAULT_NOISE_FLOOR +
						  ts->ack_rssi;
			info->status.is_valid_ack_संकेत = true;
		पूर्ण अन्यथा अणु
			info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;
		पूर्ण
	पूर्ण

	ieee80211_tx_status(ar->hw, msdu);
पूर्ण

अटल व्योम
ath11k_dp_tx_process_htt_tx_complete(काष्ठा ath11k_base *ab,
				     व्योम *desc, u8 mac_id,
				     u32 msdu_id, काष्ठा dp_tx_ring *tx_ring)
अणु
	काष्ठा htt_tx_wbm_completion *status_desc;
	काष्ठा ath11k_dp_htt_wbm_tx_status ts = अणु0पूर्ण;
	क्रमागत hal_wbm_htt_tx_comp_status wbm_status;

	status_desc = desc + HTT_TX_WBM_COMP_STATUS_OFFSET;

	wbm_status = FIELD_GET(HTT_TX_WBM_COMP_INFO0_STATUS,
			       status_desc->info0);
	चयन (wbm_status) अणु
	हाल HAL_WBM_REL_HTT_TX_COMP_STATUS_OK:
	हाल HAL_WBM_REL_HTT_TX_COMP_STATUS_DROP:
	हाल HAL_WBM_REL_HTT_TX_COMP_STATUS_TTL:
		ts.acked = (wbm_status == HAL_WBM_REL_HTT_TX_COMP_STATUS_OK);
		ts.msdu_id = msdu_id;
		ts.ack_rssi = FIELD_GET(HTT_TX_WBM_COMP_INFO1_ACK_RSSI,
					status_desc->info1);
		ath11k_dp_tx_htt_tx_complete_buf(ab, tx_ring, &ts);
		अवरोध;
	हाल HAL_WBM_REL_HTT_TX_COMP_STATUS_REINJ:
	हाल HAL_WBM_REL_HTT_TX_COMP_STATUS_INSPECT:
		ath11k_dp_tx_मुक्त_txbuf(ab, mac_id, msdu_id, tx_ring);
		अवरोध;
	हाल HAL_WBM_REL_HTT_TX_COMP_STATUS_MEC_NOTIFY:
		/* This event is to be handled only when the driver decides to
		 * use WDS offload functionality.
		 */
		अवरोध;
	शेष:
		ath11k_warn(ab, "Unknown htt tx status %d\n", wbm_status);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_dp_tx_cache_peer_stats(काष्ठा ath11k *ar,
					  काष्ठा sk_buff *msdu,
					  काष्ठा hal_tx_status *ts)
अणु
	काष्ठा ath11k_per_peer_tx_stats *peer_stats = &ar->cached_stats;

	अगर (ts->try_cnt > 1) अणु
		peer_stats->retry_pkts += ts->try_cnt - 1;
		peer_stats->retry_bytes += (ts->try_cnt - 1) * msdu->len;

		अगर (ts->status != HAL_WBM_TQM_REL_REASON_FRAME_ACKED) अणु
			peer_stats->failed_pkts += 1;
			peer_stats->failed_bytes += msdu->len;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath11k_dp_tx_complete_msdu(काष्ठा ath11k *ar,
				       काष्ठा sk_buff *msdu,
				       काष्ठा hal_tx_status *ts)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ath11k_skb_cb *skb_cb;

	अगर (WARN_ON_ONCE(ts->buf_rel_source != HAL_WBM_REL_SRC_MODULE_TQM)) अणु
		/* Must not happen */
		वापस;
	पूर्ण

	skb_cb = ATH11K_SKB_CB(msdu);

	dma_unmap_single(ab->dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);

	rcu_पढ़ो_lock();

	अगर (!rcu_dereference(ab->pdevs_active[ar->pdev_idx])) अणु
		dev_kमुक्त_skb_any(msdu);
		जाओ निकास;
	पूर्ण

	अगर (!skb_cb->vअगर) अणु
		dev_kमुक्त_skb_any(msdu);
		जाओ निकास;
	पूर्ण

	info = IEEE80211_SKB_CB(msdu);
	स_रखो(&info->status, 0, माप(info->status));

	/* skip tx rate update from ieee80211_status*/
	info->status.rates[0].idx = -1;

	अगर (ts->status == HAL_WBM_TQM_REL_REASON_FRAME_ACKED &&
	    !(info->flags & IEEE80211_TX_CTL_NO_ACK)) अणु
		info->flags |= IEEE80211_TX_STAT_ACK;
		info->status.ack_संकेत = ATH11K_DEFAULT_NOISE_FLOOR +
					  ts->ack_rssi;
		info->status.is_valid_ack_संकेत = true;
	पूर्ण

	अगर (ts->status == HAL_WBM_TQM_REL_REASON_CMD_REMOVE_TX &&
	    (info->flags & IEEE80211_TX_CTL_NO_ACK))
		info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;

	अगर (ath11k_debugfs_is_extd_tx_stats_enabled(ar)) अणु
		अगर (ts->flags & HAL_TX_STATUS_FLAGS_FIRST_MSDU) अणु
			अगर (ar->last_ppdu_id == 0) अणु
				ar->last_ppdu_id = ts->ppdu_id;
			पूर्ण अन्यथा अगर (ar->last_ppdu_id == ts->ppdu_id ||
				   ar->cached_ppdu_id == ar->last_ppdu_id) अणु
				ar->cached_ppdu_id = ar->last_ppdu_id;
				ar->cached_stats.is_ampdu = true;
				ath11k_debugfs_sta_update_txcompl(ar, msdu, ts);
				स_रखो(&ar->cached_stats, 0,
				       माप(काष्ठा ath11k_per_peer_tx_stats));
			पूर्ण अन्यथा अणु
				ar->cached_stats.is_ampdu = false;
				ath11k_debugfs_sta_update_txcompl(ar, msdu, ts);
				स_रखो(&ar->cached_stats, 0,
				       माप(काष्ठा ath11k_per_peer_tx_stats));
			पूर्ण
			ar->last_ppdu_id = ts->ppdu_id;
		पूर्ण

		ath11k_dp_tx_cache_peer_stats(ar, msdu, ts);
	पूर्ण

	/* NOTE: Tx rate status reporting. Tx completion status करोes not have
	 * necessary inक्रमmation (क्रम example nss) to build the tx rate.
	 * Might end up reporting it out-of-band from HTT stats.
	 */

	ieee80211_tx_status(ar->hw, msdu);

निकास:
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम ath11k_dp_tx_status_parse(काष्ठा ath11k_base *ab,
					     काष्ठा hal_wbm_release_ring *desc,
					     काष्ठा hal_tx_status *ts)
अणु
	ts->buf_rel_source =
		FIELD_GET(HAL_WBM_RELEASE_INFO0_REL_SRC_MODULE, desc->info0);
	अगर (ts->buf_rel_source != HAL_WBM_REL_SRC_MODULE_FW &&
	    ts->buf_rel_source != HAL_WBM_REL_SRC_MODULE_TQM)
		वापस;

	अगर (ts->buf_rel_source == HAL_WBM_REL_SRC_MODULE_FW)
		वापस;

	ts->status = FIELD_GET(HAL_WBM_RELEASE_INFO0_TQM_RELEASE_REASON,
			       desc->info0);
	ts->ppdu_id = FIELD_GET(HAL_WBM_RELEASE_INFO1_TQM_STATUS_NUMBER,
				desc->info1);
	ts->try_cnt = FIELD_GET(HAL_WBM_RELEASE_INFO1_TRANSMIT_COUNT,
				desc->info1);
	ts->ack_rssi = FIELD_GET(HAL_WBM_RELEASE_INFO2_ACK_FRAME_RSSI,
				 desc->info2);
	अगर (desc->info2 & HAL_WBM_RELEASE_INFO2_FIRST_MSDU)
		ts->flags |= HAL_TX_STATUS_FLAGS_FIRST_MSDU;
	ts->peer_id = FIELD_GET(HAL_WBM_RELEASE_INFO3_PEER_ID, desc->info3);
	ts->tid = FIELD_GET(HAL_WBM_RELEASE_INFO3_TID, desc->info3);
	अगर (desc->rate_stats.info0 & HAL_TX_RATE_STATS_INFO0_VALID)
		ts->rate_stats = desc->rate_stats.info0;
	अन्यथा
		ts->rate_stats = 0;
पूर्ण

व्योम ath11k_dp_tx_completion_handler(काष्ठा ath11k_base *ab, पूर्णांक ring_id)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_dp *dp = &ab->dp;
	पूर्णांक hal_ring_id = dp->tx_ring[ring_id].tcl_comp_ring.ring_id;
	काष्ठा hal_srng *status_ring = &ab->hal.srng_list[hal_ring_id];
	काष्ठा sk_buff *msdu;
	काष्ठा hal_tx_status ts = अणु 0 पूर्ण;
	काष्ठा dp_tx_ring *tx_ring = &dp->tx_ring[ring_id];
	u32 *desc;
	u32 msdu_id;
	u8 mac_id;

	spin_lock_bh(&status_ring->lock);

	ath11k_hal_srng_access_begin(ab, status_ring);

	जबतक ((ATH11K_TX_COMPL_NEXT(tx_ring->tx_status_head) !=
		tx_ring->tx_status_tail) &&
	       (desc = ath11k_hal_srng_dst_get_next_entry(ab, status_ring))) अणु
		स_नकल(&tx_ring->tx_status[tx_ring->tx_status_head],
		       desc, माप(काष्ठा hal_wbm_release_ring));
		tx_ring->tx_status_head =
			ATH11K_TX_COMPL_NEXT(tx_ring->tx_status_head);
	पूर्ण

	अगर ((ath11k_hal_srng_dst_peek(ab, status_ring) != शून्य) &&
	    (ATH11K_TX_COMPL_NEXT(tx_ring->tx_status_head) == tx_ring->tx_status_tail)) अणु
		/* TODO: Process pending tx_status messages when kfअगरo_is_full() */
		ath11k_warn(ab, "Unable to process some of the tx_status ring desc because status_fifo is full\n");
	पूर्ण

	ath11k_hal_srng_access_end(ab, status_ring);

	spin_unlock_bh(&status_ring->lock);

	जबतक (ATH11K_TX_COMPL_NEXT(tx_ring->tx_status_tail) != tx_ring->tx_status_head) अणु
		काष्ठा hal_wbm_release_ring *tx_status;
		u32 desc_id;

		tx_ring->tx_status_tail =
			ATH11K_TX_COMPL_NEXT(tx_ring->tx_status_tail);
		tx_status = &tx_ring->tx_status[tx_ring->tx_status_tail];
		ath11k_dp_tx_status_parse(ab, tx_status, &ts);

		desc_id = FIELD_GET(BUFFER_ADDR_INFO1_SW_COOKIE,
				    tx_status->buf_addr_info.info1);
		mac_id = FIELD_GET(DP_TX_DESC_ID_MAC_ID, desc_id);
		msdu_id = FIELD_GET(DP_TX_DESC_ID_MSDU_ID, desc_id);

		अगर (ts.buf_rel_source == HAL_WBM_REL_SRC_MODULE_FW) अणु
			ath11k_dp_tx_process_htt_tx_complete(ab,
							     (व्योम *)tx_status,
							     mac_id, msdu_id,
							     tx_ring);
			जारी;
		पूर्ण

		spin_lock_bh(&tx_ring->tx_idr_lock);
		msdu = idr_find(&tx_ring->txbuf_idr, msdu_id);
		अगर (!msdu) अणु
			ath11k_warn(ab, "tx completion for unknown msdu_id %d\n",
				    msdu_id);
			spin_unlock_bh(&tx_ring->tx_idr_lock);
			जारी;
		पूर्ण
		idr_हटाओ(&tx_ring->txbuf_idr, msdu_id);
		spin_unlock_bh(&tx_ring->tx_idr_lock);

		ar = ab->pdevs[mac_id].ar;

		अगर (atomic_dec_and_test(&ar->dp.num_tx_pending))
			wake_up(&ar->dp.tx_empty_रुकोq);

		ath11k_dp_tx_complete_msdu(ar, msdu, &ts);
	पूर्ण
पूर्ण

पूर्णांक ath11k_dp_tx_send_reo_cmd(काष्ठा ath11k_base *ab, काष्ठा dp_rx_tid *rx_tid,
			      क्रमागत hal_reo_cmd_type type,
			      काष्ठा ath11k_hal_reo_cmd *cmd,
			      व्योम (*cb)(काष्ठा ath11k_dp *, व्योम *,
					 क्रमागत hal_reo_cmd_status))
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा dp_reo_cmd *dp_cmd;
	काष्ठा hal_srng *cmd_ring;
	पूर्णांक cmd_num;

	cmd_ring = &ab->hal.srng_list[dp->reo_cmd_ring.ring_id];
	cmd_num = ath11k_hal_reo_cmd_send(ab, cmd_ring, type, cmd);

	/* cmd_num should start from 1, during failure वापस the error code */
	अगर (cmd_num < 0)
		वापस cmd_num;

	/* reo cmd ring descriptors has cmd_num starting from 1 */
	अगर (cmd_num == 0)
		वापस -EINVAL;

	अगर (!cb)
		वापस 0;

	/* Can this be optimized so that we keep the pending command list only
	 * क्रम tid delete command to मुक्त up the resoruce on the command status
	 * indication?
	 */
	dp_cmd = kzalloc(माप(*dp_cmd), GFP_ATOMIC);

	अगर (!dp_cmd)
		वापस -ENOMEM;

	स_नकल(&dp_cmd->data, rx_tid, माप(काष्ठा dp_rx_tid));
	dp_cmd->cmd_num = cmd_num;
	dp_cmd->handler = cb;

	spin_lock_bh(&dp->reo_cmd_lock);
	list_add_tail(&dp_cmd->list, &dp->reo_cmd_list);
	spin_unlock_bh(&dp->reo_cmd_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_dp_tx_get_ring_id_type(काष्ठा ath11k_base *ab,
			      पूर्णांक mac_id, u32 ring_id,
			      क्रमागत hal_ring_type ring_type,
			      क्रमागत htt_srng_ring_type *htt_ring_type,
			      क्रमागत htt_srng_ring_id *htt_ring_id)
अणु
	पूर्णांक lmac_ring_id_offset = 0;
	पूर्णांक ret = 0;

	चयन (ring_type) अणु
	हाल HAL_RXDMA_BUF:
		lmac_ring_id_offset = mac_id * HAL_SRNG_RINGS_PER_LMAC;

		/* क्रम QCA6390, host fills rx buffer to fw and fw fills to
		 * rxbuf ring क्रम each rxdma
		 */
		अगर (!ab->hw_params.rx_mac_buf_ring) अणु
			अगर (!(ring_id == (HAL_SRNG_RING_ID_WMAC1_SW2RXDMA0_BUF +
					  lmac_ring_id_offset) ||
				ring_id == (HAL_SRNG_RING_ID_WMAC1_SW2RXDMA1_BUF +
					lmac_ring_id_offset))) अणु
				ret = -EINVAL;
			पूर्ण
			*htt_ring_id = HTT_RXDMA_HOST_BUF_RING;
			*htt_ring_type = HTT_SW_TO_HW_RING;
		पूर्ण अन्यथा अणु
			अगर (ring_id == HAL_SRNG_RING_ID_WMAC1_SW2RXDMA0_BUF) अणु
				*htt_ring_id = HTT_HOST1_TO_FW_RXBUF_RING;
				*htt_ring_type = HTT_SW_TO_SW_RING;
			पूर्ण अन्यथा अणु
				*htt_ring_id = HTT_RXDMA_HOST_BUF_RING;
				*htt_ring_type = HTT_SW_TO_HW_RING;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HAL_RXDMA_DST:
		*htt_ring_id = HTT_RXDMA_NON_MONITOR_DEST_RING;
		*htt_ring_type = HTT_HW_TO_SW_RING;
		अवरोध;
	हाल HAL_RXDMA_MONITOR_BUF:
		*htt_ring_id = HTT_RXDMA_MONITOR_BUF_RING;
		*htt_ring_type = HTT_SW_TO_HW_RING;
		अवरोध;
	हाल HAL_RXDMA_MONITOR_STATUS:
		*htt_ring_id = HTT_RXDMA_MONITOR_STATUS_RING;
		*htt_ring_type = HTT_SW_TO_HW_RING;
		अवरोध;
	हाल HAL_RXDMA_MONITOR_DST:
		*htt_ring_id = HTT_RXDMA_MONITOR_DEST_RING;
		*htt_ring_type = HTT_HW_TO_SW_RING;
		अवरोध;
	हाल HAL_RXDMA_MONITOR_DESC:
		*htt_ring_id = HTT_RXDMA_MONITOR_DESC_RING;
		*htt_ring_type = HTT_SW_TO_HW_RING;
		अवरोध;
	शेष:
		ath11k_warn(ab, "Unsupported ring type in DP :%d\n", ring_type);
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ath11k_dp_tx_htt_srng_setup(काष्ठा ath11k_base *ab, u32 ring_id,
				पूर्णांक mac_id, क्रमागत hal_ring_type ring_type)
अणु
	काष्ठा htt_srng_setup_cmd *cmd;
	काष्ठा hal_srng *srng = &ab->hal.srng_list[ring_id];
	काष्ठा hal_srng_params params;
	काष्ठा sk_buff *skb;
	u32 ring_entry_sz;
	पूर्णांक len = माप(*cmd);
	dma_addr_t hp_addr, tp_addr;
	क्रमागत htt_srng_ring_type htt_ring_type;
	क्रमागत htt_srng_ring_id htt_ring_id;
	पूर्णांक ret;

	skb = ath11k_htc_alloc_skb(ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	स_रखो(&params, 0, माप(params));
	ath11k_hal_srng_get_params(ab, srng, &params);

	hp_addr = ath11k_hal_srng_get_hp_addr(ab, srng);
	tp_addr = ath11k_hal_srng_get_tp_addr(ab, srng);

	ret = ath11k_dp_tx_get_ring_id_type(ab, mac_id, ring_id,
					    ring_type, &htt_ring_type,
					    &htt_ring_id);
	अगर (ret)
		जाओ err_मुक्त;

	skb_put(skb, len);
	cmd = (काष्ठा htt_srng_setup_cmd *)skb->data;
	cmd->info0 = FIELD_PREP(HTT_SRNG_SETUP_CMD_INFO0_MSG_TYPE,
				HTT_H2T_MSG_TYPE_SRING_SETUP);
	अगर (htt_ring_type == HTT_SW_TO_HW_RING ||
	    htt_ring_type == HTT_HW_TO_SW_RING)
		cmd->info0 |= FIELD_PREP(HTT_SRNG_SETUP_CMD_INFO0_PDEV_ID,
					 DP_SW2HW_MACID(mac_id));
	अन्यथा
		cmd->info0 |= FIELD_PREP(HTT_SRNG_SETUP_CMD_INFO0_PDEV_ID,
					 mac_id);
	cmd->info0 |= FIELD_PREP(HTT_SRNG_SETUP_CMD_INFO0_RING_TYPE,
				 htt_ring_type);
	cmd->info0 |= FIELD_PREP(HTT_SRNG_SETUP_CMD_INFO0_RING_ID, htt_ring_id);

	cmd->ring_base_addr_lo = params.ring_base_paddr &
				 HAL_ADDR_LSB_REG_MASK;

	cmd->ring_base_addr_hi = (u64)params.ring_base_paddr >>
				 HAL_ADDR_MSB_REG_SHIFT;

	ret = ath11k_hal_srng_get_entrysize(ab, ring_type);
	अगर (ret < 0)
		जाओ err_मुक्त;

	ring_entry_sz = ret;

	ring_entry_sz >>= 2;
	cmd->info1 = FIELD_PREP(HTT_SRNG_SETUP_CMD_INFO1_RING_ENTRY_SIZE,
				ring_entry_sz);
	cmd->info1 |= FIELD_PREP(HTT_SRNG_SETUP_CMD_INFO1_RING_SIZE,
				 params.num_entries * ring_entry_sz);
	cmd->info1 |= FIELD_PREP(HTT_SRNG_SETUP_CMD_INFO1_RING_FLAGS_MSI_SWAP,
				 !!(params.flags & HAL_SRNG_FLAGS_MSI_SWAP));
	cmd->info1 |= FIELD_PREP(
			HTT_SRNG_SETUP_CMD_INFO1_RING_FLAGS_TLV_SWAP,
			!!(params.flags & HAL_SRNG_FLAGS_DATA_TLV_SWAP));
	cmd->info1 |= FIELD_PREP(
			HTT_SRNG_SETUP_CMD_INFO1_RING_FLAGS_HOST_FW_SWAP,
			!!(params.flags & HAL_SRNG_FLAGS_RING_PTR_SWAP));
	अगर (htt_ring_type == HTT_SW_TO_HW_RING)
		cmd->info1 |= HTT_SRNG_SETUP_CMD_INFO1_RING_LOOP_CNT_DIS;

	cmd->ring_head_off32_remote_addr_lo = hp_addr & HAL_ADDR_LSB_REG_MASK;
	cmd->ring_head_off32_remote_addr_hi = (u64)hp_addr >>
					      HAL_ADDR_MSB_REG_SHIFT;

	cmd->ring_tail_off32_remote_addr_lo = tp_addr & HAL_ADDR_LSB_REG_MASK;
	cmd->ring_tail_off32_remote_addr_hi = (u64)tp_addr >>
					      HAL_ADDR_MSB_REG_SHIFT;

	cmd->ring_msi_addr_lo = lower_32_bits(params.msi_addr);
	cmd->ring_msi_addr_hi = upper_32_bits(params.msi_addr);
	cmd->msi_data = params.msi_data;

	cmd->पूर्णांकr_info = FIELD_PREP(
			HTT_SRNG_SETUP_CMD_INTR_INFO_BATCH_COUNTER_THRESH,
			params.पूर्णांकr_batch_cntr_thres_entries * ring_entry_sz);
	cmd->पूर्णांकr_info |= FIELD_PREP(
			HTT_SRNG_SETUP_CMD_INTR_INFO_INTR_TIMER_THRESH,
			params.पूर्णांकr_समयr_thres_us >> 3);

	cmd->info2 = 0;
	अगर (params.flags & HAL_SRNG_FLAGS_LOW_THRESH_INTR_EN) अणु
		cmd->info2 = FIELD_PREP(
				HTT_SRNG_SETUP_CMD_INFO2_INTR_LOW_THRESH,
				params.low_threshold);
	पूर्ण

	ath11k_dbg(ab, ATH11k_DBG_HAL,
		   "%s msi_addr_lo:0x%x, msi_addr_hi:0x%x, msi_data:0x%x\n",
		   __func__, cmd->ring_msi_addr_lo, cmd->ring_msi_addr_hi,
		   cmd->msi_data);

	ath11k_dbg(ab, ATH11k_DBG_HAL,
		   "ring_id:%d, ring_type:%d, intr_info:0x%x, flags:0x%x\n",
		   ring_id, ring_type, cmd->पूर्णांकr_info, cmd->info2);

	ret = ath11k_htc_send(&ab->htc, ab->dp.eid, skb);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	dev_kमुक्त_skb_any(skb);

	वापस ret;
पूर्ण

#घोषणा HTT_TARGET_VERSION_TIMEOUT_HZ (3 * HZ)

पूर्णांक ath11k_dp_tx_htt_h2t_ver_req_msg(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा sk_buff *skb;
	काष्ठा htt_ver_req_cmd *cmd;
	पूर्णांक len = माप(*cmd);
	पूर्णांक ret;

	init_completion(&dp->htt_tgt_version_received);

	skb = ath11k_htc_alloc_skb(ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);
	cmd = (काष्ठा htt_ver_req_cmd *)skb->data;
	cmd->ver_reg_info = FIELD_PREP(HTT_VER_REQ_INFO_MSG_ID,
				       HTT_H2T_MSG_TYPE_VERSION_REQ);

	ret = ath11k_htc_send(&ab->htc, dp->eid, skb);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&dp->htt_tgt_version_received,
					  HTT_TARGET_VERSION_TIMEOUT_HZ);
	अगर (ret == 0) अणु
		ath11k_warn(ab, "htt target version request timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (dp->htt_tgt_ver_major != HTT_TARGET_VERSION_MAJOR) अणु
		ath11k_err(ab, "unsupported htt major version %d supported version is %d\n",
			   dp->htt_tgt_ver_major, HTT_TARGET_VERSION_MAJOR);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_tx_htt_h2t_ppdu_stats_req(काष्ठा ath11k *ar, u32 mask)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा sk_buff *skb;
	काष्ठा htt_ppdu_stats_cfg_cmd *cmd;
	पूर्णांक len = माप(*cmd);
	u8 pdev_mask;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		skb = ath11k_htc_alloc_skb(ab, len);
		अगर (!skb)
			वापस -ENOMEM;

		skb_put(skb, len);
		cmd = (काष्ठा htt_ppdu_stats_cfg_cmd *)skb->data;
		cmd->msg = FIELD_PREP(HTT_PPDU_STATS_CFG_MSG_TYPE,
				      HTT_H2T_MSG_TYPE_PPDU_STATS_CFG);

		pdev_mask = 1 << (i + 1);
		cmd->msg |= FIELD_PREP(HTT_PPDU_STATS_CFG_PDEV_ID, pdev_mask);
		cmd->msg |= FIELD_PREP(HTT_PPDU_STATS_CFG_TLV_TYPE_BITMASK, mask);

		ret = ath11k_htc_send(&ab->htc, dp->eid, skb);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_tx_htt_rx_filter_setup(काष्ठा ath11k_base *ab, u32 ring_id,
				     पूर्णांक mac_id, क्रमागत hal_ring_type ring_type,
				     पूर्णांक rx_buf_size,
				     काष्ठा htt_rx_ring_tlv_filter *tlv_filter)
अणु
	काष्ठा htt_rx_ring_selection_cfg_cmd *cmd;
	काष्ठा hal_srng *srng = &ab->hal.srng_list[ring_id];
	काष्ठा hal_srng_params params;
	काष्ठा sk_buff *skb;
	पूर्णांक len = माप(*cmd);
	क्रमागत htt_srng_ring_type htt_ring_type;
	क्रमागत htt_srng_ring_id htt_ring_id;
	पूर्णांक ret;

	skb = ath11k_htc_alloc_skb(ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	स_रखो(&params, 0, माप(params));
	ath11k_hal_srng_get_params(ab, srng, &params);

	ret = ath11k_dp_tx_get_ring_id_type(ab, mac_id, ring_id,
					    ring_type, &htt_ring_type,
					    &htt_ring_id);
	अगर (ret)
		जाओ err_मुक्त;

	skb_put(skb, len);
	cmd = (काष्ठा htt_rx_ring_selection_cfg_cmd *)skb->data;
	cmd->info0 = FIELD_PREP(HTT_RX_RING_SELECTION_CFG_CMD_INFO0_MSG_TYPE,
				HTT_H2T_MSG_TYPE_RX_RING_SELECTION_CFG);
	अगर (htt_ring_type == HTT_SW_TO_HW_RING ||
	    htt_ring_type == HTT_HW_TO_SW_RING)
		cmd->info0 |=
			FIELD_PREP(HTT_RX_RING_SELECTION_CFG_CMD_INFO0_PDEV_ID,
				   DP_SW2HW_MACID(mac_id));
	अन्यथा
		cmd->info0 |=
			FIELD_PREP(HTT_RX_RING_SELECTION_CFG_CMD_INFO0_PDEV_ID,
				   mac_id);
	cmd->info0 |= FIELD_PREP(HTT_RX_RING_SELECTION_CFG_CMD_INFO0_RING_ID,
				 htt_ring_id);
	cmd->info0 |= FIELD_PREP(HTT_RX_RING_SELECTION_CFG_CMD_INFO0_SS,
				 !!(params.flags & HAL_SRNG_FLAGS_MSI_SWAP));
	cmd->info0 |= FIELD_PREP(HTT_RX_RING_SELECTION_CFG_CMD_INFO0_PS,
				 !!(params.flags & HAL_SRNG_FLAGS_DATA_TLV_SWAP));

	cmd->info1 = FIELD_PREP(HTT_RX_RING_SELECTION_CFG_CMD_INFO1_BUF_SIZE,
				rx_buf_size);
	cmd->pkt_type_en_flags0 = tlv_filter->pkt_filter_flags0;
	cmd->pkt_type_en_flags1 = tlv_filter->pkt_filter_flags1;
	cmd->pkt_type_en_flags2 = tlv_filter->pkt_filter_flags2;
	cmd->pkt_type_en_flags3 = tlv_filter->pkt_filter_flags3;
	cmd->rx_filter_tlv = tlv_filter->rx_filter;

	ret = ath11k_htc_send(&ab->htc, ab->dp.eid, skb);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	dev_kमुक्त_skb_any(skb);

	वापस ret;
पूर्ण

पूर्णांक
ath11k_dp_tx_htt_h2t_ext_stats_req(काष्ठा ath11k *ar, u8 type,
				   काष्ठा htt_ext_stats_cfg_params *cfg_params,
				   u64 cookie)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा sk_buff *skb;
	काष्ठा htt_ext_stats_cfg_cmd *cmd;
	पूर्णांक len = माप(*cmd);
	पूर्णांक ret;

	skb = ath11k_htc_alloc_skb(ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);

	cmd = (काष्ठा htt_ext_stats_cfg_cmd *)skb->data;
	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_EXT_STATS_CFG;

	cmd->hdr.pdev_mask = 1 << ar->pdev->pdev_id;

	cmd->hdr.stats_type = type;
	cmd->cfg_param0 = cfg_params->cfg0;
	cmd->cfg_param1 = cfg_params->cfg1;
	cmd->cfg_param2 = cfg_params->cfg2;
	cmd->cfg_param3 = cfg_params->cfg3;
	cmd->cookie_lsb = lower_32_bits(cookie);
	cmd->cookie_msb = upper_32_bits(cookie);

	ret = ath11k_htc_send(&ab->htc, dp->eid, skb);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to send htt type stats request: %d",
			    ret);
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_tx_htt_monitor_mode_ring_config(काष्ठा ath11k *ar, bool reset)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा htt_rx_ring_tlv_filter tlv_filter = अणु0पूर्ण;
	पूर्णांक ret = 0, ring_id = 0, i;

	ring_id = dp->rxdma_mon_buf_ring.refill_buf_ring.ring_id;

	अगर (!reset) अणु
		tlv_filter.rx_filter = HTT_RX_MON_FILTER_TLV_FLAGS_MON_BUF_RING;
		tlv_filter.pkt_filter_flags0 =
					HTT_RX_MON_FP_MGMT_FILTER_FLAGS0 |
					HTT_RX_MON_MO_MGMT_FILTER_FLAGS0;
		tlv_filter.pkt_filter_flags1 =
					HTT_RX_MON_FP_MGMT_FILTER_FLAGS1 |
					HTT_RX_MON_MO_MGMT_FILTER_FLAGS1;
		tlv_filter.pkt_filter_flags2 =
					HTT_RX_MON_FP_CTRL_FILTER_FLASG2 |
					HTT_RX_MON_MO_CTRL_FILTER_FLASG2;
		tlv_filter.pkt_filter_flags3 =
					HTT_RX_MON_FP_CTRL_FILTER_FLASG3 |
					HTT_RX_MON_MO_CTRL_FILTER_FLASG3 |
					HTT_RX_MON_FP_DATA_FILTER_FLASG3 |
					HTT_RX_MON_MO_DATA_FILTER_FLASG3;
	पूर्ण

	अगर (ab->hw_params.rxdma1_enable) अणु
		ret = ath11k_dp_tx_htt_rx_filter_setup(ar->ab, ring_id, dp->mac_id,
						       HAL_RXDMA_MONITOR_BUF,
						       DP_RXDMA_REFILL_RING_SIZE,
						       &tlv_filter);
	पूर्ण अन्यथा अगर (!reset) अणु
		/* set in monitor mode only */
		क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
			ring_id = dp->rx_mac_buf_ring[i].ring_id;
			ret = ath11k_dp_tx_htt_rx_filter_setup(ar->ab, ring_id,
							       dp->mac_id + i,
							       HAL_RXDMA_BUF,
							       1024,
							       &tlv_filter);
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		ring_id = dp->rx_mon_status_refill_ring[i].refill_buf_ring.ring_id;
		अगर (!reset)
			tlv_filter.rx_filter =
					HTT_RX_MON_FILTER_TLV_FLAGS_MON_STATUS_RING;
		अन्यथा
			tlv_filter = ath11k_mac_mon_status_filter_शेष;

		ret = ath11k_dp_tx_htt_rx_filter_setup(ab, ring_id,
						       dp->mac_id + i,
						       HAL_RXDMA_MONITOR_STATUS,
						       DP_RXDMA_REFILL_RING_SIZE,
						       &tlv_filter);
	पूर्ण

	अगर (!ar->ab->hw_params.rxdma1_enable)
		mod_समयr(&ar->ab->mon_reap_समयr, jअगरfies +
			  msecs_to_jअगरfies(ATH11K_MON_TIMER_INTERVAL));

	वापस ret;
पूर्ण
