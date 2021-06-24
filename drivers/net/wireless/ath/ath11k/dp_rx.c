<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <crypto/hash.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "debugfs_htt_stats.h"
#समावेश "debugfs_sta.h"
#समावेश "hal_desc.h"
#समावेश "hw.h"
#समावेश "dp_rx.h"
#समावेश "hal_rx.h"
#समावेश "dp_tx.h"
#समावेश "peer.h"

#घोषणा ATH11K_DP_RX_FRAGMENT_TIMEOUT_MS (2 * HZ)

अटल u8 *ath11k_dp_rx_h_80211_hdr(काष्ठा ath11k_base *ab, काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_hdr_status(desc);
पूर्ण

अटल क्रमागत hal_encrypt_type ath11k_dp_rx_h_mpdu_start_enctype(काष्ठा ath11k_base *ab,
							       काष्ठा hal_rx_desc *desc)
अणु
	अगर (!ab->hw_params.hw_ops->rx_desc_encrypt_valid(desc))
		वापस HAL_ENCRYPT_TYPE_OPEN;

	वापस ab->hw_params.hw_ops->rx_desc_get_encrypt_type(desc);
पूर्ण

अटल u8 ath11k_dp_rx_h_msdu_start_decap_type(काष्ठा ath11k_base *ab,
					       काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_decap_type(desc);
पूर्ण

अटल u8 ath11k_dp_rx_h_msdu_start_mesh_ctl_present(काष्ठा ath11k_base *ab,
						     काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_mesh_ctl(desc);
पूर्ण

अटल bool ath11k_dp_rx_h_mpdu_start_seq_ctrl_valid(काष्ठा ath11k_base *ab,
						     काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_mpdu_seq_ctl_vld(desc);
पूर्ण

अटल bool ath11k_dp_rx_h_mpdu_start_fc_valid(काष्ठा ath11k_base *ab,
					       काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_mpdu_fc_valid(desc);
पूर्ण

अटल bool ath11k_dp_rx_h_mpdu_start_more_frags(काष्ठा ath11k_base *ab,
						 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + ab->hw_params.hal_desc_sz);
	वापस ieee80211_has_morefrags(hdr->frame_control);
पूर्ण

अटल u16 ath11k_dp_rx_h_mpdu_start_frag_no(काष्ठा ath11k_base *ab,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + ab->hw_params.hal_desc_sz);
	वापस le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_FRAG;
पूर्ण

अटल u16 ath11k_dp_rx_h_mpdu_start_seq_no(काष्ठा ath11k_base *ab,
					    काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_mpdu_start_seq_no(desc);
पूर्ण

अटल व्योम *ath11k_dp_rx_get_attention(काष्ठा ath11k_base *ab,
					काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_attention(desc);
पूर्ण

अटल bool ath11k_dp_rx_h_attn_msdu_करोne(काष्ठा rx_attention *attn)
अणु
	वापस !!FIELD_GET(RX_ATTENTION_INFO2_MSDU_DONE,
			   __le32_to_cpu(attn->info2));
पूर्ण

अटल bool ath11k_dp_rx_h_attn_l4_cksum_fail(काष्ठा rx_attention *attn)
अणु
	वापस !!FIELD_GET(RX_ATTENTION_INFO1_TCP_UDP_CKSUM_FAIL,
			   __le32_to_cpu(attn->info1));
पूर्ण

अटल bool ath11k_dp_rx_h_attn_ip_cksum_fail(काष्ठा rx_attention *attn)
अणु
	वापस !!FIELD_GET(RX_ATTENTION_INFO1_IP_CKSUM_FAIL,
			   __le32_to_cpu(attn->info1));
पूर्ण

अटल bool ath11k_dp_rx_h_attn_is_decrypted(काष्ठा rx_attention *attn)
अणु
	वापस (FIELD_GET(RX_ATTENTION_INFO2_DCRYPT_STATUS_CODE,
			  __le32_to_cpu(attn->info2)) ==
		RX_DESC_DECRYPT_STATUS_CODE_OK);
पूर्ण

अटल u32 ath11k_dp_rx_h_attn_mpdu_err(काष्ठा rx_attention *attn)
अणु
	u32 info = __le32_to_cpu(attn->info1);
	u32 errmap = 0;

	अगर (info & RX_ATTENTION_INFO1_FCS_ERR)
		errmap |= DP_RX_MPDU_ERR_FCS;

	अगर (info & RX_ATTENTION_INFO1_DECRYPT_ERR)
		errmap |= DP_RX_MPDU_ERR_DECRYPT;

	अगर (info & RX_ATTENTION_INFO1_TKIP_MIC_ERR)
		errmap |= DP_RX_MPDU_ERR_TKIP_MIC;

	अगर (info & RX_ATTENTION_INFO1_A_MSDU_ERROR)
		errmap |= DP_RX_MPDU_ERR_AMSDU_ERR;

	अगर (info & RX_ATTENTION_INFO1_OVERFLOW_ERR)
		errmap |= DP_RX_MPDU_ERR_OVERFLOW;

	अगर (info & RX_ATTENTION_INFO1_MSDU_LEN_ERR)
		errmap |= DP_RX_MPDU_ERR_MSDU_LEN;

	अगर (info & RX_ATTENTION_INFO1_MPDU_LEN_ERR)
		errmap |= DP_RX_MPDU_ERR_MPDU_LEN;

	वापस errmap;
पूर्ण

अटल u16 ath11k_dp_rx_h_msdu_start_msdu_len(काष्ठा ath11k_base *ab,
					      काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_msdu_len(desc);
पूर्ण

अटल u8 ath11k_dp_rx_h_msdu_start_sgi(काष्ठा ath11k_base *ab,
					काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_msdu_sgi(desc);
पूर्ण

अटल u8 ath11k_dp_rx_h_msdu_start_rate_mcs(काष्ठा ath11k_base *ab,
					     काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_msdu_rate_mcs(desc);
पूर्ण

अटल u8 ath11k_dp_rx_h_msdu_start_rx_bw(काष्ठा ath11k_base *ab,
					  काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_msdu_rx_bw(desc);
पूर्ण

अटल u32 ath11k_dp_rx_h_msdu_start_freq(काष्ठा ath11k_base *ab,
					  काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_msdu_freq(desc);
पूर्ण

अटल u8 ath11k_dp_rx_h_msdu_start_pkt_type(काष्ठा ath11k_base *ab,
					     काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_msdu_pkt_type(desc);
पूर्ण

अटल u8 ath11k_dp_rx_h_msdu_start_nss(काष्ठा ath11k_base *ab,
					काष्ठा hal_rx_desc *desc)
अणु
	वापस hweight8(ab->hw_params.hw_ops->rx_desc_get_msdu_nss(desc));
पूर्ण

अटल u8 ath11k_dp_rx_h_mpdu_start_tid(काष्ठा ath11k_base *ab,
					काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_mpdu_tid(desc);
पूर्ण

अटल u16 ath11k_dp_rx_h_mpdu_start_peer_id(काष्ठा ath11k_base *ab,
					     काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_mpdu_peer_id(desc);
पूर्ण

अटल u8 ath11k_dp_rx_h_msdu_end_l3pad(काष्ठा ath11k_base *ab,
					काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_l3_pad_bytes(desc);
पूर्ण

अटल bool ath11k_dp_rx_h_msdu_end_first_msdu(काष्ठा ath11k_base *ab,
					       काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_first_msdu(desc);
पूर्ण

अटल bool ath11k_dp_rx_h_msdu_end_last_msdu(काष्ठा ath11k_base *ab,
					      काष्ठा hal_rx_desc *desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_last_msdu(desc);
पूर्ण

अटल व्योम ath11k_dp_rx_desc_end_tlv_copy(काष्ठा ath11k_base *ab,
					   काष्ठा hal_rx_desc *fdesc,
					   काष्ठा hal_rx_desc *ldesc)
अणु
	ab->hw_params.hw_ops->rx_desc_copy_attn_end_tlv(fdesc, ldesc);
पूर्ण

अटल u32 ath11k_dp_rxdesc_get_mpdulen_err(काष्ठा rx_attention *attn)
अणु
	वापस FIELD_GET(RX_ATTENTION_INFO1_MPDU_LEN_ERR,
			 __le32_to_cpu(attn->info1));
पूर्ण

अटल u8 *ath11k_dp_rxdesc_get_80211hdr(काष्ठा ath11k_base *ab,
					 काष्ठा hal_rx_desc *rx_desc)
अणु
	u8 *rx_pkt_hdr;

	rx_pkt_hdr = ab->hw_params.hw_ops->rx_desc_get_msdu_payload(rx_desc);

	वापस rx_pkt_hdr;
पूर्ण

अटल bool ath11k_dp_rxdesc_mpdu_valid(काष्ठा ath11k_base *ab,
					काष्ठा hal_rx_desc *rx_desc)
अणु
	u32 tlv_tag;

	tlv_tag = ab->hw_params.hw_ops->rx_desc_get_mpdu_start_tag(rx_desc);

	वापस tlv_tag == HAL_RX_MPDU_START;
पूर्ण

अटल u32 ath11k_dp_rxdesc_get_ppduid(काष्ठा ath11k_base *ab,
				       काष्ठा hal_rx_desc *rx_desc)
अणु
	वापस ab->hw_params.hw_ops->rx_desc_get_mpdu_ppdu_id(rx_desc);
पूर्ण

अटल व्योम ath11k_dp_rxdesc_set_msdu_len(काष्ठा ath11k_base *ab,
					  काष्ठा hal_rx_desc *desc,
					  u16 len)
अणु
	ab->hw_params.hw_ops->rx_desc_set_msdu_len(desc, len);
पूर्ण

अटल bool ath11k_dp_rx_h_attn_is_mcbc(काष्ठा ath11k_base *ab,
					काष्ठा hal_rx_desc *desc)
अणु
	काष्ठा rx_attention *attn = ath11k_dp_rx_get_attention(ab, desc);

	वापस ath11k_dp_rx_h_msdu_end_first_msdu(ab, desc) &&
		(!!FIELD_GET(RX_ATTENTION_INFO1_MCAST_BCAST,
		 __le32_to_cpu(attn->info1)));
पूर्ण

अटल व्योम ath11k_dp_service_mon_ring(काष्ठा समयr_list *t)
अणु
	काष्ठा ath11k_base *ab = from_समयr(ab, t, mon_reap_समयr);
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++)
		ath11k_dp_rx_process_mon_rings(ab, i, शून्य, DP_MON_SERVICE_BUDGET);

	mod_समयr(&ab->mon_reap_समयr, jअगरfies +
		  msecs_to_jअगरfies(ATH11K_MON_TIMER_INTERVAL));
पूर्ण

अटल पूर्णांक ath11k_dp_purge_mon_ring(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i, reaped = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(DP_MON_PURGE_TIMEOUT_MS);

	करो अणु
		क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++)
			reaped += ath11k_dp_rx_process_mon_rings(ab, i,
								 शून्य,
								 DP_MON_SERVICE_BUDGET);

		/* nothing more to reap */
		अगर (reaped < DP_MON_SERVICE_BUDGET)
			वापस 0;

	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	ath11k_warn(ab, "dp mon ring purge timeout");

	वापस -ETIMEDOUT;
पूर्ण

/* Returns number of Rx buffers replenished */
पूर्णांक ath11k_dp_rxbufs_replenish(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
			       काष्ठा dp_rxdma_ring *rx_ring,
			       पूर्णांक req_entries,
			       क्रमागत hal_rx_buf_वापस_buf_manager mgr)
अणु
	काष्ठा hal_srng *srng;
	u32 *desc;
	काष्ठा sk_buff *skb;
	पूर्णांक num_मुक्त;
	पूर्णांक num_reमुख्य;
	पूर्णांक buf_id;
	u32 cookie;
	dma_addr_t paddr;

	req_entries = min(req_entries, rx_ring->bufs_max);

	srng = &ab->hal.srng_list[rx_ring->refill_buf_ring.ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	num_मुक्त = ath11k_hal_srng_src_num_मुक्त(ab, srng, true);
	अगर (!req_entries && (num_मुक्त > (rx_ring->bufs_max * 3) / 4))
		req_entries = num_मुक्त;

	req_entries = min(num_मुक्त, req_entries);
	num_reमुख्य = req_entries;

	जबतक (num_reमुख्य > 0) अणु
		skb = dev_alloc_skb(DP_RX_BUFFER_SIZE +
				    DP_RX_BUFFER_ALIGN_SIZE);
		अगर (!skb)
			अवरोध;

		अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data,
				DP_RX_BUFFER_ALIGN_SIZE)) अणु
			skb_pull(skb,
				 PTR_ALIGN(skb->data, DP_RX_BUFFER_ALIGN_SIZE) -
				 skb->data);
		पूर्ण

		paddr = dma_map_single(ab->dev, skb->data,
				       skb->len + skb_tailroom(skb),
				       DMA_FROM_DEVICE);
		अगर (dma_mapping_error(ab->dev, paddr))
			जाओ fail_मुक्त_skb;

		spin_lock_bh(&rx_ring->idr_lock);
		buf_id = idr_alloc(&rx_ring->bufs_idr, skb, 0,
				   rx_ring->bufs_max * 3, GFP_ATOMIC);
		spin_unlock_bh(&rx_ring->idr_lock);
		अगर (buf_id < 0)
			जाओ fail_dma_unmap;

		desc = ath11k_hal_srng_src_get_next_entry(ab, srng);
		अगर (!desc)
			जाओ fail_idr_हटाओ;

		ATH11K_SKB_RXCB(skb)->paddr = paddr;

		cookie = FIELD_PREP(DP_RXDMA_BUF_COOKIE_PDEV_ID, mac_id) |
			 FIELD_PREP(DP_RXDMA_BUF_COOKIE_BUF_ID, buf_id);

		num_reमुख्य--;

		ath11k_hal_rx_buf_addr_info_set(desc, paddr, cookie, mgr);
	पूर्ण

	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	वापस req_entries - num_reमुख्य;

fail_idr_हटाओ:
	spin_lock_bh(&rx_ring->idr_lock);
	idr_हटाओ(&rx_ring->bufs_idr, buf_id);
	spin_unlock_bh(&rx_ring->idr_lock);
fail_dma_unmap:
	dma_unmap_single(ab->dev, paddr, skb->len + skb_tailroom(skb),
			 DMA_FROM_DEVICE);
fail_मुक्त_skb:
	dev_kमुक्त_skb_any(skb);

	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	वापस req_entries - num_reमुख्य;
पूर्ण

अटल पूर्णांक ath11k_dp_rxdma_buf_ring_मुक्त(काष्ठा ath11k *ar,
					 काष्ठा dp_rxdma_ring *rx_ring)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा sk_buff *skb;
	पूर्णांक buf_id;

	spin_lock_bh(&rx_ring->idr_lock);
	idr_क्रम_each_entry(&rx_ring->bufs_idr, skb, buf_id) अणु
		idr_हटाओ(&rx_ring->bufs_idr, buf_id);
		/* TODO: Understand where पूर्णांकernal driver करोes this dma_unmap
		 * of rxdma_buffer.
		 */
		dma_unmap_single(ar->ab->dev, ATH11K_SKB_RXCB(skb)->paddr,
				 skb->len + skb_tailroom(skb), DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	idr_destroy(&rx_ring->bufs_idr);
	spin_unlock_bh(&rx_ring->idr_lock);

	/* अगर rxdma1_enable is false, mon_status_refill_ring
	 * isn't setup, so don't clean.
	 */
	अगर (!ar->ab->hw_params.rxdma1_enable)
		वापस 0;

	rx_ring = &dp->rx_mon_status_refill_ring[0];

	spin_lock_bh(&rx_ring->idr_lock);
	idr_क्रम_each_entry(&rx_ring->bufs_idr, skb, buf_id) अणु
		idr_हटाओ(&rx_ring->bufs_idr, buf_id);
		/* XXX: Understand where पूर्णांकernal driver करोes this dma_unmap
		 * of rxdma_buffer.
		 */
		dma_unmap_single(ar->ab->dev, ATH11K_SKB_RXCB(skb)->paddr,
				 skb->len + skb_tailroom(skb), DMA_BIसूचीECTIONAL);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	idr_destroy(&rx_ring->bufs_idr);
	spin_unlock_bh(&rx_ring->idr_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_dp_rxdma_pdev_buf_मुक्त(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा dp_rxdma_ring *rx_ring = &dp->rx_refill_buf_ring;
	पूर्णांक i;

	ath11k_dp_rxdma_buf_ring_मुक्त(ar, rx_ring);

	rx_ring = &dp->rxdma_mon_buf_ring;
	ath11k_dp_rxdma_buf_ring_मुक्त(ar, rx_ring);

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		rx_ring = &dp->rx_mon_status_refill_ring[i];
		ath11k_dp_rxdma_buf_ring_मुक्त(ar, rx_ring);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_dp_rxdma_ring_buf_setup(काष्ठा ath11k *ar,
					  काष्ठा dp_rxdma_ring *rx_ring,
					  u32 ringtype)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	पूर्णांक num_entries;

	num_entries = rx_ring->refill_buf_ring.size /
		ath11k_hal_srng_get_entrysize(ar->ab, ringtype);

	rx_ring->bufs_max = num_entries;
	ath11k_dp_rxbufs_replenish(ar->ab, dp->mac_id, rx_ring, num_entries,
				   HAL_RX_BUF_RBM_SW3_BM);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_dp_rxdma_pdev_buf_setup(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा dp_rxdma_ring *rx_ring = &dp->rx_refill_buf_ring;
	पूर्णांक i;

	ath11k_dp_rxdma_ring_buf_setup(ar, rx_ring, HAL_RXDMA_BUF);

	अगर (ar->ab->hw_params.rxdma1_enable) अणु
		rx_ring = &dp->rxdma_mon_buf_ring;
		ath11k_dp_rxdma_ring_buf_setup(ar, rx_ring, HAL_RXDMA_MONITOR_BUF);
	पूर्ण

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		rx_ring = &dp->rx_mon_status_refill_ring[i];
		ath11k_dp_rxdma_ring_buf_setup(ar, rx_ring, HAL_RXDMA_MONITOR_STATUS);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath11k_dp_rx_pdev_srng_मुक्त(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_base *ab = ar->ab;
	पूर्णांक i;

	ath11k_dp_srng_cleanup(ab, &dp->rx_refill_buf_ring.refill_buf_ring);

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		अगर (ab->hw_params.rx_mac_buf_ring)
			ath11k_dp_srng_cleanup(ab, &dp->rx_mac_buf_ring[i]);

		ath11k_dp_srng_cleanup(ab, &dp->rxdma_err_dst_ring[i]);
		ath11k_dp_srng_cleanup(ab,
				       &dp->rx_mon_status_refill_ring[i].refill_buf_ring);
	पूर्ण

	ath11k_dp_srng_cleanup(ab, &dp->rxdma_mon_buf_ring.refill_buf_ring);
पूर्ण

व्योम ath11k_dp_pdev_reo_cleanup(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	पूर्णांक i;

	क्रम (i = 0; i < DP_REO_DST_RING_MAX; i++)
		ath11k_dp_srng_cleanup(ab, &dp->reo_dst_ring[i]);
पूर्ण

पूर्णांक ath11k_dp_pdev_reo_setup(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < DP_REO_DST_RING_MAX; i++) अणु
		ret = ath11k_dp_srng_setup(ab, &dp->reo_dst_ring[i],
					   HAL_REO_DST, i, 0,
					   DP_REO_DST_RING_SIZE);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to setup reo_dst_ring\n");
			जाओ err_reo_cleanup;
		पूर्ण
	पूर्ण

	वापस 0;

err_reo_cleanup:
	ath11k_dp_pdev_reo_cleanup(ab);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_pdev_srng_alloc(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा dp_srng *srng = शून्य;
	पूर्णांक i;
	पूर्णांक ret;

	ret = ath11k_dp_srng_setup(ar->ab,
				   &dp->rx_refill_buf_ring.refill_buf_ring,
				   HAL_RXDMA_BUF, 0,
				   dp->mac_id, DP_RXDMA_BUF_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to setup rx_refill_buf_ring\n");
		वापस ret;
	पूर्ण

	अगर (ar->ab->hw_params.rx_mac_buf_ring) अणु
		क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
			ret = ath11k_dp_srng_setup(ar->ab,
						   &dp->rx_mac_buf_ring[i],
						   HAL_RXDMA_BUF, 1,
						   dp->mac_id + i, 1024);
			अगर (ret) अणु
				ath11k_warn(ar->ab, "failed to setup rx_mac_buf_ring %d\n",
					    i);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		ret = ath11k_dp_srng_setup(ar->ab, &dp->rxdma_err_dst_ring[i],
					   HAL_RXDMA_DST, 0, dp->mac_id + i,
					   DP_RXDMA_ERR_DST_RING_SIZE);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to setup rxdma_err_dst_ring %d\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		srng = &dp->rx_mon_status_refill_ring[i].refill_buf_ring;
		ret = ath11k_dp_srng_setup(ar->ab,
					   srng,
					   HAL_RXDMA_MONITOR_STATUS, 0, dp->mac_id + i,
					   DP_RXDMA_MON_STATUS_RING_SIZE);
		अगर (ret) अणु
			ath11k_warn(ar->ab,
				    "failed to setup rx_mon_status_refill_ring %d\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	/* अगर rxdma1_enable is false, then it करोesn't need
	 * to setup rxdam_mon_buf_ring, rxdma_mon_dst_ring
	 * and rxdma_mon_desc_ring.
	 * init reap समयr क्रम QCA6390.
	 */
	अगर (!ar->ab->hw_params.rxdma1_enable) अणु
		//init mon status buffer reap समयr
		समयr_setup(&ar->ab->mon_reap_समयr,
			    ath11k_dp_service_mon_ring, 0);
		वापस 0;
	पूर्ण

	ret = ath11k_dp_srng_setup(ar->ab,
				   &dp->rxdma_mon_buf_ring.refill_buf_ring,
				   HAL_RXDMA_MONITOR_BUF, 0, dp->mac_id,
				   DP_RXDMA_MONITOR_BUF_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to setup HAL_RXDMA_MONITOR_BUF\n");
		वापस ret;
	पूर्ण

	ret = ath11k_dp_srng_setup(ar->ab, &dp->rxdma_mon_dst_ring,
				   HAL_RXDMA_MONITOR_DST, 0, dp->mac_id,
				   DP_RXDMA_MONITOR_DST_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to setup HAL_RXDMA_MONITOR_DST\n");
		वापस ret;
	पूर्ण

	ret = ath11k_dp_srng_setup(ar->ab, &dp->rxdma_mon_desc_ring,
				   HAL_RXDMA_MONITOR_DESC, 0, dp->mac_id,
				   DP_RXDMA_MONITOR_DESC_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to setup HAL_RXDMA_MONITOR_DESC\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath11k_dp_reo_cmd_list_cleanup(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा dp_reo_cmd *cmd, *पंचांगp;
	काष्ठा dp_reo_cache_flush_elem *cmd_cache, *पंचांगp_cache;

	spin_lock_bh(&dp->reo_cmd_lock);
	list_क्रम_each_entry_safe(cmd, पंचांगp, &dp->reo_cmd_list, list) अणु
		list_del(&cmd->list);
		dma_unmap_single(ab->dev, cmd->data.paddr,
				 cmd->data.size, DMA_BIसूचीECTIONAL);
		kमुक्त(cmd->data.vaddr);
		kमुक्त(cmd);
	पूर्ण

	list_क्रम_each_entry_safe(cmd_cache, पंचांगp_cache,
				 &dp->reo_cmd_cache_flush_list, list) अणु
		list_del(&cmd_cache->list);
		dp->reo_cmd_cache_flush_count--;
		dma_unmap_single(ab->dev, cmd_cache->data.paddr,
				 cmd_cache->data.size, DMA_BIसूचीECTIONAL);
		kमुक्त(cmd_cache->data.vaddr);
		kमुक्त(cmd_cache);
	पूर्ण
	spin_unlock_bh(&dp->reo_cmd_lock);
पूर्ण

अटल व्योम ath11k_dp_reo_cmd_मुक्त(काष्ठा ath11k_dp *dp, व्योम *ctx,
				   क्रमागत hal_reo_cmd_status status)
अणु
	काष्ठा dp_rx_tid *rx_tid = ctx;

	अगर (status != HAL_REO_CMD_SUCCESS)
		ath11k_warn(dp->ab, "failed to flush rx tid hw desc, tid %d status %d\n",
			    rx_tid->tid, status);

	dma_unmap_single(dp->ab->dev, rx_tid->paddr, rx_tid->size,
			 DMA_BIसूचीECTIONAL);
	kमुक्त(rx_tid->vaddr);
पूर्ण

अटल व्योम ath11k_dp_reo_cache_flush(काष्ठा ath11k_base *ab,
				      काष्ठा dp_rx_tid *rx_tid)
अणु
	काष्ठा ath11k_hal_reo_cmd cmd = अणु0पूर्ण;
	अचिन्हित दीर्घ tot_desc_sz, desc_sz;
	पूर्णांक ret;

	tot_desc_sz = rx_tid->size;
	desc_sz = ath11k_hal_reo_qdesc_size(0, HAL_DESC_REO_NON_QOS_TID);

	जबतक (tot_desc_sz > desc_sz) अणु
		tot_desc_sz -= desc_sz;
		cmd.addr_lo = lower_32_bits(rx_tid->paddr + tot_desc_sz);
		cmd.addr_hi = upper_32_bits(rx_tid->paddr);
		ret = ath11k_dp_tx_send_reo_cmd(ab, rx_tid,
						HAL_REO_CMD_FLUSH_CACHE, &cmd,
						शून्य);
		अगर (ret)
			ath11k_warn(ab,
				    "failed to send HAL_REO_CMD_FLUSH_CACHE, tid %d (%d)\n",
				    rx_tid->tid, ret);
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));
	cmd.addr_lo = lower_32_bits(rx_tid->paddr);
	cmd.addr_hi = upper_32_bits(rx_tid->paddr);
	cmd.flag |= HAL_REO_CMD_FLG_NEED_STATUS;
	ret = ath11k_dp_tx_send_reo_cmd(ab, rx_tid,
					HAL_REO_CMD_FLUSH_CACHE,
					&cmd, ath11k_dp_reo_cmd_मुक्त);
	अगर (ret) अणु
		ath11k_err(ab, "failed to send HAL_REO_CMD_FLUSH_CACHE cmd, tid %d (%d)\n",
			   rx_tid->tid, ret);
		dma_unmap_single(ab->dev, rx_tid->paddr, rx_tid->size,
				 DMA_BIसूचीECTIONAL);
		kमुक्त(rx_tid->vaddr);
	पूर्ण
पूर्ण

अटल व्योम ath11k_dp_rx_tid_del_func(काष्ठा ath11k_dp *dp, व्योम *ctx,
				      क्रमागत hal_reo_cmd_status status)
अणु
	काष्ठा ath11k_base *ab = dp->ab;
	काष्ठा dp_rx_tid *rx_tid = ctx;
	काष्ठा dp_reo_cache_flush_elem *elem, *पंचांगp;

	अगर (status == HAL_REO_CMD_DRAIN) अणु
		जाओ मुक्त_desc;
	पूर्ण अन्यथा अगर (status != HAL_REO_CMD_SUCCESS) अणु
		/* Shouldn't happen! Cleanup in हाल of other failure? */
		ath11k_warn(ab, "failed to delete rx tid %d hw descriptor %d\n",
			    rx_tid->tid, status);
		वापस;
	पूर्ण

	elem = kzalloc(माप(*elem), GFP_ATOMIC);
	अगर (!elem)
		जाओ मुक्त_desc;

	elem->ts = jअगरfies;
	स_नकल(&elem->data, rx_tid, माप(*rx_tid));

	spin_lock_bh(&dp->reo_cmd_lock);
	list_add_tail(&elem->list, &dp->reo_cmd_cache_flush_list);
	dp->reo_cmd_cache_flush_count++;

	/* Flush and invalidate aged REO desc from HW cache */
	list_क्रम_each_entry_safe(elem, पंचांगp, &dp->reo_cmd_cache_flush_list,
				 list) अणु
		अगर (dp->reo_cmd_cache_flush_count > DP_REO_DESC_FREE_THRESHOLD ||
		    समय_after(jअगरfies, elem->ts +
			       msecs_to_jअगरfies(DP_REO_DESC_FREE_TIMEOUT_MS))) अणु
			list_del(&elem->list);
			dp->reo_cmd_cache_flush_count--;
			spin_unlock_bh(&dp->reo_cmd_lock);

			ath11k_dp_reo_cache_flush(ab, &elem->data);
			kमुक्त(elem);
			spin_lock_bh(&dp->reo_cmd_lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&dp->reo_cmd_lock);

	वापस;
मुक्त_desc:
	dma_unmap_single(ab->dev, rx_tid->paddr, rx_tid->size,
			 DMA_BIसूचीECTIONAL);
	kमुक्त(rx_tid->vaddr);
पूर्ण

व्योम ath11k_peer_rx_tid_delete(काष्ठा ath11k *ar,
			       काष्ठा ath11k_peer *peer, u8 tid)
अणु
	काष्ठा ath11k_hal_reo_cmd cmd = अणु0पूर्ण;
	काष्ठा dp_rx_tid *rx_tid = &peer->rx_tid[tid];
	पूर्णांक ret;

	अगर (!rx_tid->active)
		वापस;

	cmd.flag = HAL_REO_CMD_FLG_NEED_STATUS;
	cmd.addr_lo = lower_32_bits(rx_tid->paddr);
	cmd.addr_hi = upper_32_bits(rx_tid->paddr);
	cmd.upd0 |= HAL_REO_CMD_UPD0_VLD;
	ret = ath11k_dp_tx_send_reo_cmd(ar->ab, rx_tid,
					HAL_REO_CMD_UPDATE_RX_QUEUE, &cmd,
					ath11k_dp_rx_tid_del_func);
	अगर (ret) अणु
		ath11k_err(ar->ab, "failed to send HAL_REO_CMD_UPDATE_RX_QUEUE cmd, tid %d (%d)\n",
			   tid, ret);
		dma_unmap_single(ar->ab->dev, rx_tid->paddr, rx_tid->size,
				 DMA_BIसूचीECTIONAL);
		kमुक्त(rx_tid->vaddr);
	पूर्ण

	rx_tid->active = false;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_link_desc_वापस(काष्ठा ath11k_base *ab,
					 u32 *link_desc,
					 क्रमागत hal_wbm_rel_bm_act action)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा hal_srng *srng;
	u32 *desc;
	पूर्णांक ret = 0;

	srng = &ab->hal.srng_list[dp->wbm_desc_rel_ring.ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	desc = ath11k_hal_srng_src_get_next_entry(ab, srng);
	अगर (!desc) अणु
		ret = -ENOBUFS;
		जाओ निकास;
	पूर्ण

	ath11k_hal_rx_msdu_link_desc_set(ab, (व्योम *)desc, (व्योम *)link_desc,
					 action);

निकास:
	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	वापस ret;
पूर्ण

अटल व्योम ath11k_dp_rx_frags_cleanup(काष्ठा dp_rx_tid *rx_tid, bool rel_link_desc)
अणु
	काष्ठा ath11k_base *ab = rx_tid->ab;

	lockdep_निश्चित_held(&ab->base_lock);

	अगर (rx_tid->dst_ring_desc) अणु
		अगर (rel_link_desc)
			ath11k_dp_rx_link_desc_वापस(ab, (u32 *)rx_tid->dst_ring_desc,
						      HAL_WBM_REL_BM_ACT_PUT_IN_IDLE);
		kमुक्त(rx_tid->dst_ring_desc);
		rx_tid->dst_ring_desc = शून्य;
	पूर्ण

	rx_tid->cur_sn = 0;
	rx_tid->last_frag_no = 0;
	rx_tid->rx_frag_biपंचांगap = 0;
	__skb_queue_purge(&rx_tid->rx_frags);
पूर्ण

व्योम ath11k_peer_frags_flush(काष्ठा ath11k *ar, काष्ठा ath11k_peer *peer)
अणु
	काष्ठा dp_rx_tid *rx_tid;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->ab->base_lock);

	क्रम (i = 0; i <= IEEE80211_NUM_TIDS; i++) अणु
		rx_tid = &peer->rx_tid[i];

		spin_unlock_bh(&ar->ab->base_lock);
		del_समयr_sync(&rx_tid->frag_समयr);
		spin_lock_bh(&ar->ab->base_lock);

		ath11k_dp_rx_frags_cleanup(rx_tid, true);
	पूर्ण
पूर्ण

व्योम ath11k_peer_rx_tid_cleanup(काष्ठा ath11k *ar, काष्ठा ath11k_peer *peer)
अणु
	काष्ठा dp_rx_tid *rx_tid;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->ab->base_lock);

	क्रम (i = 0; i <= IEEE80211_NUM_TIDS; i++) अणु
		rx_tid = &peer->rx_tid[i];

		ath11k_peer_rx_tid_delete(ar, peer, i);
		ath11k_dp_rx_frags_cleanup(rx_tid, true);

		spin_unlock_bh(&ar->ab->base_lock);
		del_समयr_sync(&rx_tid->frag_समयr);
		spin_lock_bh(&ar->ab->base_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_peer_rx_tid_reo_update(काष्ठा ath11k *ar,
					 काष्ठा ath11k_peer *peer,
					 काष्ठा dp_rx_tid *rx_tid,
					 u32 ba_win_sz, u16 ssn,
					 bool update_ssn)
अणु
	काष्ठा ath11k_hal_reo_cmd cmd = अणु0पूर्ण;
	पूर्णांक ret;

	cmd.addr_lo = lower_32_bits(rx_tid->paddr);
	cmd.addr_hi = upper_32_bits(rx_tid->paddr);
	cmd.flag = HAL_REO_CMD_FLG_NEED_STATUS;
	cmd.upd0 = HAL_REO_CMD_UPD0_BA_WINDOW_SIZE;
	cmd.ba_winकरोw_size = ba_win_sz;

	अगर (update_ssn) अणु
		cmd.upd0 |= HAL_REO_CMD_UPD0_SSN;
		cmd.upd2 = FIELD_PREP(HAL_REO_CMD_UPD2_SSN, ssn);
	पूर्ण

	ret = ath11k_dp_tx_send_reo_cmd(ar->ab, rx_tid,
					HAL_REO_CMD_UPDATE_RX_QUEUE, &cmd,
					शून्य);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to update rx tid queue, tid %d (%d)\n",
			    rx_tid->tid, ret);
		वापस ret;
	पूर्ण

	rx_tid->ba_win_sz = ba_win_sz;

	वापस 0;
पूर्ण

अटल व्योम ath11k_dp_rx_tid_mem_मुक्त(काष्ठा ath11k_base *ab,
				      स्थिर u8 *peer_mac, पूर्णांक vdev_id, u8 tid)
अणु
	काष्ठा ath11k_peer *peer;
	काष्ठा dp_rx_tid *rx_tid;

	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find(ab, vdev_id, peer_mac);
	अगर (!peer) अणु
		ath11k_warn(ab, "failed to find the peer to free up rx tid mem\n");
		जाओ unlock_निकास;
	पूर्ण

	rx_tid = &peer->rx_tid[tid];
	अगर (!rx_tid->active)
		जाओ unlock_निकास;

	dma_unmap_single(ab->dev, rx_tid->paddr, rx_tid->size,
			 DMA_BIसूचीECTIONAL);
	kमुक्त(rx_tid->vaddr);

	rx_tid->active = false;

unlock_निकास:
	spin_unlock_bh(&ab->base_lock);
पूर्ण

पूर्णांक ath11k_peer_rx_tid_setup(काष्ठा ath11k *ar, स्थिर u8 *peer_mac, पूर्णांक vdev_id,
			     u8 tid, u32 ba_win_sz, u16 ssn,
			     क्रमागत hal_pn_type pn_type)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_peer *peer;
	काष्ठा dp_rx_tid *rx_tid;
	u32 hw_desc_sz;
	u32 *addr_aligned;
	व्योम *vaddr;
	dma_addr_t paddr;
	पूर्णांक ret;

	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find(ab, vdev_id, peer_mac);
	अगर (!peer) अणु
		ath11k_warn(ab, "failed to find the peer to set up rx tid\n");
		spin_unlock_bh(&ab->base_lock);
		वापस -ENOENT;
	पूर्ण

	rx_tid = &peer->rx_tid[tid];
	/* Update the tid queue अगर it is alपढ़ोy setup */
	अगर (rx_tid->active) अणु
		paddr = rx_tid->paddr;
		ret = ath11k_peer_rx_tid_reo_update(ar, peer, rx_tid,
						    ba_win_sz, ssn, true);
		spin_unlock_bh(&ab->base_lock);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to update reo for rx tid %d\n", tid);
			वापस ret;
		पूर्ण

		ret = ath11k_wmi_peer_rx_reorder_queue_setup(ar, vdev_id,
							     peer_mac, paddr,
							     tid, 1, ba_win_sz);
		अगर (ret)
			ath11k_warn(ab, "failed to send wmi command to update rx reorder queue, tid :%d (%d)\n",
				    tid, ret);
		वापस ret;
	पूर्ण

	rx_tid->tid = tid;

	rx_tid->ba_win_sz = ba_win_sz;

	/* TODO: Optimize the memory allocation क्रम qos tid based on
	 * the actual BA winकरोw size in REO tid update path.
	 */
	अगर (tid == HAL_DESC_REO_NON_QOS_TID)
		hw_desc_sz = ath11k_hal_reo_qdesc_size(ba_win_sz, tid);
	अन्यथा
		hw_desc_sz = ath11k_hal_reo_qdesc_size(DP_BA_WIN_SZ_MAX, tid);

	vaddr = kzalloc(hw_desc_sz + HAL_LINK_DESC_ALIGN - 1, GFP_ATOMIC);
	अगर (!vaddr) अणु
		spin_unlock_bh(&ab->base_lock);
		वापस -ENOMEM;
	पूर्ण

	addr_aligned = PTR_ALIGN(vaddr, HAL_LINK_DESC_ALIGN);

	ath11k_hal_reo_qdesc_setup(addr_aligned, tid, ba_win_sz,
				   ssn, pn_type);

	paddr = dma_map_single(ab->dev, addr_aligned, hw_desc_sz,
			       DMA_BIसूचीECTIONAL);

	ret = dma_mapping_error(ab->dev, paddr);
	अगर (ret) अणु
		spin_unlock_bh(&ab->base_lock);
		जाओ err_mem_मुक्त;
	पूर्ण

	rx_tid->vaddr = vaddr;
	rx_tid->paddr = paddr;
	rx_tid->size = hw_desc_sz;
	rx_tid->active = true;

	spin_unlock_bh(&ab->base_lock);

	ret = ath11k_wmi_peer_rx_reorder_queue_setup(ar, vdev_id, peer_mac,
						     paddr, tid, 1, ba_win_sz);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to setup rx reorder queue, tid :%d (%d)\n",
			    tid, ret);
		ath11k_dp_rx_tid_mem_मुक्त(ab, peer_mac, vdev_id, tid);
	पूर्ण

	वापस ret;

err_mem_मुक्त:
	kमुक्त(vaddr);

	वापस ret;
पूर्ण

पूर्णांक ath11k_dp_rx_ampdu_start(काष्ठा ath11k *ar,
			     काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_sta *arsta = (व्योम *)params->sta->drv_priv;
	पूर्णांक vdev_id = arsta->arvअगर->vdev_id;
	पूर्णांक ret;

	ret = ath11k_peer_rx_tid_setup(ar, params->sta->addr, vdev_id,
				       params->tid, params->buf_size,
				       params->ssn, arsta->pn_type);
	अगर (ret)
		ath11k_warn(ab, "failed to setup rx tid %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक ath11k_dp_rx_ampdu_stop(काष्ठा ath11k *ar,
			    काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_peer *peer;
	काष्ठा ath11k_sta *arsta = (व्योम *)params->sta->drv_priv;
	पूर्णांक vdev_id = arsta->arvअगर->vdev_id;
	dma_addr_t paddr;
	bool active;
	पूर्णांक ret;

	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find(ab, vdev_id, params->sta->addr);
	अगर (!peer) अणु
		ath11k_warn(ab, "failed to find the peer to stop rx aggregation\n");
		spin_unlock_bh(&ab->base_lock);
		वापस -ENOENT;
	पूर्ण

	paddr = peer->rx_tid[params->tid].paddr;
	active = peer->rx_tid[params->tid].active;

	अगर (!active) अणु
		spin_unlock_bh(&ab->base_lock);
		वापस 0;
	पूर्ण

	ret = ath11k_peer_rx_tid_reo_update(ar, peer, peer->rx_tid, 1, 0, false);
	spin_unlock_bh(&ab->base_lock);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to update reo for rx tid %d: %d\n",
			    params->tid, ret);
		वापस ret;
	पूर्ण

	ret = ath11k_wmi_peer_rx_reorder_queue_setup(ar, vdev_id,
						     params->sta->addr, paddr,
						     params->tid, 1, 1);
	अगर (ret)
		ath11k_warn(ab, "failed to send wmi to delete rx tid %d\n",
			    ret);

	वापस ret;
पूर्ण

पूर्णांक ath11k_dp_peer_rx_pn_replay_config(काष्ठा ath11k_vअगर *arvअगर,
				       स्थिर u8 *peer_addr,
				       क्रमागत set_key_cmd key_cmd,
				       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_hal_reo_cmd cmd = अणु0पूर्ण;
	काष्ठा ath11k_peer *peer;
	काष्ठा dp_rx_tid *rx_tid;
	u8 tid;
	पूर्णांक ret = 0;

	/* NOTE: Enable PN/TSC replay check offload only क्रम unicast frames.
	 * We use mac80211 PN/TSC replay check functionality क्रम bcast/mcast
	 * क्रम now.
	 */
	अगर (!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		वापस 0;

	cmd.flag |= HAL_REO_CMD_FLG_NEED_STATUS;
	cmd.upd0 |= HAL_REO_CMD_UPD0_PN |
		    HAL_REO_CMD_UPD0_PN_SIZE |
		    HAL_REO_CMD_UPD0_PN_VALID |
		    HAL_REO_CMD_UPD0_PN_CHECK |
		    HAL_REO_CMD_UPD0_SVLD;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		अगर (key_cmd == SET_KEY) अणु
			cmd.upd1 |= HAL_REO_CMD_UPD1_PN_CHECK;
			cmd.pn_size = 48;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find(ab, arvअगर->vdev_id, peer_addr);
	अगर (!peer) अणु
		ath11k_warn(ab, "failed to find the peer to configure pn replay detection\n");
		spin_unlock_bh(&ab->base_lock);
		वापस -ENOENT;
	पूर्ण

	क्रम (tid = 0; tid <= IEEE80211_NUM_TIDS; tid++) अणु
		rx_tid = &peer->rx_tid[tid];
		अगर (!rx_tid->active)
			जारी;
		cmd.addr_lo = lower_32_bits(rx_tid->paddr);
		cmd.addr_hi = upper_32_bits(rx_tid->paddr);
		ret = ath11k_dp_tx_send_reo_cmd(ab, rx_tid,
						HAL_REO_CMD_UPDATE_RX_QUEUE,
						&cmd, शून्य);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to configure rx tid %d queue for pn replay detection %d\n",
				    tid, ret);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ab->base_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_get_ppdu_user_index(काष्ठा htt_ppdu_stats *ppdu_stats,
					     u16 peer_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HTT_PPDU_STATS_MAX_USERS - 1; i++) अणु
		अगर (ppdu_stats->user_stats[i].is_valid_peer_id) अणु
			अगर (peer_id == ppdu_stats->user_stats[i].peer_id)
				वापस i;
		पूर्ण अन्यथा अणु
			वापस i;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ath11k_htt_tlv_ppdu_stats_parse(काष्ठा ath11k_base *ab,
					   u16 tag, u16 len, स्थिर व्योम *ptr,
					   व्योम *data)
अणु
	काष्ठा htt_ppdu_stats_info *ppdu_info;
	काष्ठा htt_ppdu_user_stats *user_stats;
	पूर्णांक cur_user;
	u16 peer_id;

	ppdu_info = (काष्ठा htt_ppdu_stats_info *)data;

	चयन (tag) अणु
	हाल HTT_PPDU_STATS_TAG_COMMON:
		अगर (len < माप(काष्ठा htt_ppdu_stats_common)) अणु
			ath11k_warn(ab, "Invalid len %d for the tag 0x%x\n",
				    len, tag);
			वापस -EINVAL;
		पूर्ण
		स_नकल((व्योम *)&ppdu_info->ppdu_stats.common, ptr,
		       माप(काष्ठा htt_ppdu_stats_common));
		अवरोध;
	हाल HTT_PPDU_STATS_TAG_USR_RATE:
		अगर (len < माप(काष्ठा htt_ppdu_stats_user_rate)) अणु
			ath11k_warn(ab, "Invalid len %d for the tag 0x%x\n",
				    len, tag);
			वापस -EINVAL;
		पूर्ण

		peer_id = ((काष्ठा htt_ppdu_stats_user_rate *)ptr)->sw_peer_id;
		cur_user = ath11k_get_ppdu_user_index(&ppdu_info->ppdu_stats,
						      peer_id);
		अगर (cur_user < 0)
			वापस -EINVAL;
		user_stats = &ppdu_info->ppdu_stats.user_stats[cur_user];
		user_stats->peer_id = peer_id;
		user_stats->is_valid_peer_id = true;
		स_नकल((व्योम *)&user_stats->rate, ptr,
		       माप(काष्ठा htt_ppdu_stats_user_rate));
		user_stats->tlv_flags |= BIT(tag);
		अवरोध;
	हाल HTT_PPDU_STATS_TAG_USR_COMPLTN_COMMON:
		अगर (len < माप(काष्ठा htt_ppdu_stats_usr_cmpltn_cmn)) अणु
			ath11k_warn(ab, "Invalid len %d for the tag 0x%x\n",
				    len, tag);
			वापस -EINVAL;
		पूर्ण

		peer_id = ((काष्ठा htt_ppdu_stats_usr_cmpltn_cmn *)ptr)->sw_peer_id;
		cur_user = ath11k_get_ppdu_user_index(&ppdu_info->ppdu_stats,
						      peer_id);
		अगर (cur_user < 0)
			वापस -EINVAL;
		user_stats = &ppdu_info->ppdu_stats.user_stats[cur_user];
		user_stats->peer_id = peer_id;
		user_stats->is_valid_peer_id = true;
		स_नकल((व्योम *)&user_stats->cmpltn_cmn, ptr,
		       माप(काष्ठा htt_ppdu_stats_usr_cmpltn_cmn));
		user_stats->tlv_flags |= BIT(tag);
		अवरोध;
	हाल HTT_PPDU_STATS_TAG_USR_COMPLTN_ACK_BA_STATUS:
		अगर (len <
		    माप(काष्ठा htt_ppdu_stats_usr_cmpltn_ack_ba_status)) अणु
			ath11k_warn(ab, "Invalid len %d for the tag 0x%x\n",
				    len, tag);
			वापस -EINVAL;
		पूर्ण

		peer_id =
		((काष्ठा htt_ppdu_stats_usr_cmpltn_ack_ba_status *)ptr)->sw_peer_id;
		cur_user = ath11k_get_ppdu_user_index(&ppdu_info->ppdu_stats,
						      peer_id);
		अगर (cur_user < 0)
			वापस -EINVAL;
		user_stats = &ppdu_info->ppdu_stats.user_stats[cur_user];
		user_stats->peer_id = peer_id;
		user_stats->is_valid_peer_id = true;
		स_नकल((व्योम *)&user_stats->ack_ba, ptr,
		       माप(काष्ठा htt_ppdu_stats_usr_cmpltn_ack_ba_status));
		user_stats->tlv_flags |= BIT(tag);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_htt_tlv_iter(काष्ठा ath11k_base *ab, स्थिर व्योम *ptr, माप_प्रकार len,
			   पूर्णांक (*iter)(काष्ठा ath11k_base *ar, u16 tag, u16 len,
				       स्थिर व्योम *ptr, व्योम *data),
			   व्योम *data)
अणु
	स्थिर काष्ठा htt_tlv *tlv;
	स्थिर व्योम *begin = ptr;
	u16 tlv_tag, tlv_len;
	पूर्णांक ret = -EINVAL;

	जबतक (len > 0) अणु
		अगर (len < माप(*tlv)) अणु
			ath11k_err(ab, "htt tlv parse failure at byte %zd (%zu bytes left, %zu expected)\n",
				   ptr - begin, len, माप(*tlv));
			वापस -EINVAL;
		पूर्ण
		tlv = (काष्ठा htt_tlv *)ptr;
		tlv_tag = FIELD_GET(HTT_TLV_TAG, tlv->header);
		tlv_len = FIELD_GET(HTT_TLV_LEN, tlv->header);
		ptr += माप(*tlv);
		len -= माप(*tlv);

		अगर (tlv_len > len) अणु
			ath11k_err(ab, "htt tlv parse failure of tag %u at byte %zd (%zu bytes left, %u expected)\n",
				   tlv_tag, ptr - begin, len, tlv_len);
			वापस -EINVAL;
		पूर्ण
		ret = iter(ab, tlv_tag, tlv_len, ptr, data);
		अगर (ret == -ENOMEM)
			वापस ret;

		ptr += tlv_len;
		len -= tlv_len;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u32 ath11k_he_gi_to_nl80211_he_gi(u8 sgi)
अणु
	u32 ret = 0;

	चयन (sgi) अणु
	हाल RX_MSDU_START_SGI_0_8_US:
		ret = NL80211_RATE_INFO_HE_GI_0_8;
		अवरोध;
	हाल RX_MSDU_START_SGI_1_6_US:
		ret = NL80211_RATE_INFO_HE_GI_1_6;
		अवरोध;
	हाल RX_MSDU_START_SGI_3_2_US:
		ret = NL80211_RATE_INFO_HE_GI_3_2;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
ath11k_update_per_peer_tx_stats(काष्ठा ath11k *ar,
				काष्ठा htt_ppdu_stats *ppdu_stats, u8 user)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_peer *peer;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath11k_sta *arsta;
	काष्ठा htt_ppdu_stats_user_rate *user_rate;
	काष्ठा ath11k_per_peer_tx_stats *peer_stats = &ar->peer_tx_stats;
	काष्ठा htt_ppdu_user_stats *usr_stats = &ppdu_stats->user_stats[user];
	काष्ठा htt_ppdu_stats_common *common = &ppdu_stats->common;
	पूर्णांक ret;
	u8 flags, mcs, nss, bw, sgi, dcm, rate_idx = 0;
	u32 succ_bytes = 0;
	u16 rate = 0, succ_pkts = 0;
	u32 tx_duration = 0;
	u8 tid = HTT_PPDU_STATS_NON_QOS_TID;
	bool is_ampdu = false;

	अगर (!usr_stats)
		वापस;

	अगर (!(usr_stats->tlv_flags & BIT(HTT_PPDU_STATS_TAG_USR_RATE)))
		वापस;

	अगर (usr_stats->tlv_flags & BIT(HTT_PPDU_STATS_TAG_USR_COMPLTN_COMMON))
		is_ampdu =
			HTT_USR_CMPLTN_IS_AMPDU(usr_stats->cmpltn_cmn.flags);

	अगर (usr_stats->tlv_flags &
	    BIT(HTT_PPDU_STATS_TAG_USR_COMPLTN_ACK_BA_STATUS)) अणु
		succ_bytes = usr_stats->ack_ba.success_bytes;
		succ_pkts = FIELD_GET(HTT_PPDU_STATS_ACK_BA_INFO_NUM_MSDU_M,
				      usr_stats->ack_ba.info);
		tid = FIELD_GET(HTT_PPDU_STATS_ACK_BA_INFO_TID_NUM,
				usr_stats->ack_ba.info);
	पूर्ण

	अगर (common->fes_duration_us)
		tx_duration = common->fes_duration_us;

	user_rate = &usr_stats->rate;
	flags = HTT_USR_RATE_PREAMBLE(user_rate->rate_flags);
	bw = HTT_USR_RATE_BW(user_rate->rate_flags) - 2;
	nss = HTT_USR_RATE_NSS(user_rate->rate_flags) + 1;
	mcs = HTT_USR_RATE_MCS(user_rate->rate_flags);
	sgi = HTT_USR_RATE_GI(user_rate->rate_flags);
	dcm = HTT_USR_RATE_DCM(user_rate->rate_flags);

	/* Note: If host configured fixed rates and in some other special
	 * हालs, the broadcast/management frames are sent in dअगरferent rates.
	 * Firmware rate's control to be skipped क्रम this?
	 */

	अगर (flags == WMI_RATE_PREAMBLE_HE && mcs > 11) अणु
		ath11k_warn(ab, "Invalid HE mcs %d peer stats",  mcs);
		वापस;
	पूर्ण

	अगर (flags == WMI_RATE_PREAMBLE_HE && mcs > ATH11K_HE_MCS_MAX) अणु
		ath11k_warn(ab, "Invalid HE mcs %d peer stats",  mcs);
		वापस;
	पूर्ण

	अगर (flags == WMI_RATE_PREAMBLE_VHT && mcs > ATH11K_VHT_MCS_MAX) अणु
		ath11k_warn(ab, "Invalid VHT mcs %d peer stats",  mcs);
		वापस;
	पूर्ण

	अगर (flags == WMI_RATE_PREAMBLE_HT && (mcs > ATH11K_HT_MCS_MAX || nss < 1)) अणु
		ath11k_warn(ab, "Invalid HT mcs %d nss %d peer stats",
			    mcs, nss);
		वापस;
	पूर्ण

	अगर (flags == WMI_RATE_PREAMBLE_CCK || flags == WMI_RATE_PREAMBLE_OFDM) अणु
		ret = ath11k_mac_hw_ratecode_to_legacy_rate(mcs,
							    flags,
							    &rate_idx,
							    &rate);
		अगर (ret < 0)
			वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find_by_id(ab, usr_stats->peer_id);

	अगर (!peer || !peer->sta) अणु
		spin_unlock_bh(&ab->base_lock);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	sta = peer->sta;
	arsta = (काष्ठा ath11k_sta *)sta->drv_priv;

	स_रखो(&arsta->txrate, 0, माप(arsta->txrate));

	चयन (flags) अणु
	हाल WMI_RATE_PREAMBLE_OFDM:
		arsta->txrate.legacy = rate;
		अवरोध;
	हाल WMI_RATE_PREAMBLE_CCK:
		arsta->txrate.legacy = rate;
		अवरोध;
	हाल WMI_RATE_PREAMBLE_HT:
		arsta->txrate.mcs = mcs + 8 * (nss - 1);
		arsta->txrate.flags = RATE_INFO_FLAGS_MCS;
		अगर (sgi)
			arsta->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल WMI_RATE_PREAMBLE_VHT:
		arsta->txrate.mcs = mcs;
		arsta->txrate.flags = RATE_INFO_FLAGS_VHT_MCS;
		अगर (sgi)
			arsta->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल WMI_RATE_PREAMBLE_HE:
		arsta->txrate.mcs = mcs;
		arsta->txrate.flags = RATE_INFO_FLAGS_HE_MCS;
		arsta->txrate.he_dcm = dcm;
		arsta->txrate.he_gi = ath11k_he_gi_to_nl80211_he_gi(sgi);
		arsta->txrate.he_ru_alloc = ath11k_he_ru_tones_to_nl80211_he_ru_alloc(
						(user_rate->ru_end -
						 user_rate->ru_start) + 1);
		अवरोध;
	पूर्ण

	arsta->txrate.nss = nss;
	arsta->txrate.bw = ath11k_mac_bw_to_mac80211_bw(bw);
	arsta->tx_duration += tx_duration;
	स_नकल(&arsta->last_txrate, &arsta->txrate, माप(काष्ठा rate_info));

	/* PPDU stats reported क्रम mgmt packet करोesn't have valid tx bytes.
	 * So skip peer stats update क्रम mgmt packets.
	 */
	अगर (tid < HTT_PPDU_STATS_NON_QOS_TID) अणु
		स_रखो(peer_stats, 0, माप(*peer_stats));
		peer_stats->succ_pkts = succ_pkts;
		peer_stats->succ_bytes = succ_bytes;
		peer_stats->is_ampdu = is_ampdu;
		peer_stats->duration = tx_duration;
		peer_stats->ba_fails =
			HTT_USR_CMPLTN_LONG_RETRY(usr_stats->cmpltn_cmn.flags) +
			HTT_USR_CMPLTN_SHORT_RETRY(usr_stats->cmpltn_cmn.flags);

		अगर (ath11k_debugfs_is_extd_tx_stats_enabled(ar))
			ath11k_debugfs_sta_add_tx_stats(arsta, peer_stats, rate_idx);
	पूर्ण

	spin_unlock_bh(&ab->base_lock);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath11k_htt_update_ppdu_stats(काष्ठा ath11k *ar,
					 काष्ठा htt_ppdu_stats *ppdu_stats)
अणु
	u8 user;

	क्रम (user = 0; user < HTT_PPDU_STATS_MAX_USERS - 1; user++)
		ath11k_update_per_peer_tx_stats(ar, ppdu_stats, user);
पूर्ण

अटल
काष्ठा htt_ppdu_stats_info *ath11k_dp_htt_get_ppdu_desc(काष्ठा ath11k *ar,
							u32 ppdu_id)
अणु
	काष्ठा htt_ppdu_stats_info *ppdu_info;

	spin_lock_bh(&ar->data_lock);
	अगर (!list_empty(&ar->ppdu_stats_info)) अणु
		list_क्रम_each_entry(ppdu_info, &ar->ppdu_stats_info, list) अणु
			अगर (ppdu_info->ppdu_id == ppdu_id) अणु
				spin_unlock_bh(&ar->data_lock);
				वापस ppdu_info;
			पूर्ण
		पूर्ण

		अगर (ar->ppdu_stat_list_depth > HTT_PPDU_DESC_MAX_DEPTH) अणु
			ppdu_info = list_first_entry(&ar->ppdu_stats_info,
						     typeof(*ppdu_info), list);
			list_del(&ppdu_info->list);
			ar->ppdu_stat_list_depth--;
			ath11k_htt_update_ppdu_stats(ar, &ppdu_info->ppdu_stats);
			kमुक्त(ppdu_info);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	ppdu_info = kzalloc(माप(*ppdu_info), GFP_ATOMIC);
	अगर (!ppdu_info)
		वापस शून्य;

	spin_lock_bh(&ar->data_lock);
	list_add_tail(&ppdu_info->list, &ar->ppdu_stats_info);
	ar->ppdu_stat_list_depth++;
	spin_unlock_bh(&ar->data_lock);

	वापस ppdu_info;
पूर्ण

अटल पूर्णांक ath11k_htt_pull_ppdu_stats(काष्ठा ath11k_base *ab,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k_htt_ppdu_stats_msg *msg;
	काष्ठा htt_ppdu_stats_info *ppdu_info;
	काष्ठा ath11k *ar;
	पूर्णांक ret;
	u8 pdev_id;
	u32 ppdu_id, len;

	msg = (काष्ठा ath11k_htt_ppdu_stats_msg *)skb->data;
	len = FIELD_GET(HTT_T2H_PPDU_STATS_INFO_PAYLOAD_SIZE, msg->info);
	pdev_id = FIELD_GET(HTT_T2H_PPDU_STATS_INFO_PDEV_ID, msg->info);
	ppdu_id = msg->ppdu_id;

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_pdev_id(ab, pdev_id);
	अगर (!ar) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (ath11k_debugfs_is_pktlog_lite_mode_enabled(ar))
		trace_ath11k_htt_ppdu_stats(ar, skb->data, len);

	ppdu_info = ath11k_dp_htt_get_ppdu_desc(ar, ppdu_id);
	अगर (!ppdu_info) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	ppdu_info->ppdu_id = ppdu_id;
	ret = ath11k_dp_htt_tlv_iter(ab, msg->data, len,
				     ath11k_htt_tlv_ppdu_stats_parse,
				     (व्योम *)ppdu_info);
	अगर (ret) अणु
		ath11k_warn(ab, "Failed to parse tlv %d\n", ret);
		जाओ निकास;
	पूर्ण

निकास:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल व्योम ath11k_htt_pktlog(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा htt_pktlog_msg *data = (काष्ठा htt_pktlog_msg *)skb->data;
	काष्ठा ath_pktlog_hdr *hdr = (काष्ठा ath_pktlog_hdr *)data;
	काष्ठा ath11k *ar;
	u8 pdev_id;

	pdev_id = FIELD_GET(HTT_T2H_PPDU_STATS_INFO_PDEV_ID, data->hdr);
	ar = ath11k_mac_get_ar_by_pdev_id(ab, pdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid pdev id %d on htt pktlog\n", pdev_id);
		वापस;
	पूर्ण

	trace_ath11k_htt_pktlog(ar, data->payload, hdr->size,
				ar->ab->pktlog_defs_checksum);
पूर्ण

अटल व्योम ath11k_htt_backpressure_event_handler(काष्ठा ath11k_base *ab,
						  काष्ठा sk_buff *skb)
अणु
	u32 *data = (u32 *)skb->data;
	u8 pdev_id, ring_type, ring_id, pdev_idx;
	u16 hp, tp;
	u32 backpressure_समय;
	काष्ठा ath11k_bp_stats *bp_stats;

	pdev_id = FIELD_GET(HTT_BACKPRESSURE_EVENT_PDEV_ID_M, *data);
	ring_type = FIELD_GET(HTT_BACKPRESSURE_EVENT_RING_TYPE_M, *data);
	ring_id = FIELD_GET(HTT_BACKPRESSURE_EVENT_RING_ID_M, *data);
	++data;

	hp = FIELD_GET(HTT_BACKPRESSURE_EVENT_HP_M, *data);
	tp = FIELD_GET(HTT_BACKPRESSURE_EVENT_TP_M, *data);
	++data;

	backpressure_समय = *data;

	ath11k_dbg(ab, ATH11K_DBG_DP_HTT, "htt backpressure event, pdev %d, ring type %d,ring id %d, hp %d tp %d, backpressure time %d\n",
		   pdev_id, ring_type, ring_id, hp, tp, backpressure_समय);

	अगर (ring_type == HTT_BACKPRESSURE_UMAC_RING_TYPE) अणु
		अगर (ring_id >= HTT_SW_UMAC_RING_IDX_MAX)
			वापस;

		bp_stats = &ab->soc_stats.bp_stats.umac_ring_bp_stats[ring_id];
	पूर्ण अन्यथा अगर (ring_type == HTT_BACKPRESSURE_LMAC_RING_TYPE) अणु
		pdev_idx = DP_HW2SW_MACID(pdev_id);

		अगर (ring_id >= HTT_SW_LMAC_RING_IDX_MAX || pdev_idx >= MAX_RADIOS)
			वापस;

		bp_stats = &ab->soc_stats.bp_stats.lmac_ring_bp_stats[ring_id][pdev_idx];
	पूर्ण अन्यथा अणु
		ath11k_warn(ab, "unknown ring type received in htt bp event %d\n",
			    ring_type);
		वापस;
	पूर्ण

	spin_lock_bh(&ab->base_lock);
	bp_stats->hp = hp;
	bp_stats->tp = tp;
	bp_stats->count++;
	bp_stats->jअगरfies = jअगरfies;
	spin_unlock_bh(&ab->base_lock);
पूर्ण

व्योम ath11k_dp_htt_htc_t2h_msg_handler(काष्ठा ath11k_base *ab,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा htt_resp_msg *resp = (काष्ठा htt_resp_msg *)skb->data;
	क्रमागत htt_t2h_msg_type type = FIELD_GET(HTT_T2H_MSG_TYPE, *(u32 *)resp);
	u16 peer_id;
	u8 vdev_id;
	u8 mac_addr[ETH_ALEN];
	u16 peer_mac_h16;
	u16 ast_hash;
	u16 hw_peer_id;

	ath11k_dbg(ab, ATH11K_DBG_DP_HTT, "dp_htt rx msg type :0x%0x\n", type);

	चयन (type) अणु
	हाल HTT_T2H_MSG_TYPE_VERSION_CONF:
		dp->htt_tgt_ver_major = FIELD_GET(HTT_T2H_VERSION_CONF_MAJOR,
						  resp->version_msg.version);
		dp->htt_tgt_ver_minor = FIELD_GET(HTT_T2H_VERSION_CONF_MINOR,
						  resp->version_msg.version);
		complete(&dp->htt_tgt_version_received);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_PEER_MAP:
		vdev_id = FIELD_GET(HTT_T2H_PEER_MAP_INFO_VDEV_ID,
				    resp->peer_map_ev.info);
		peer_id = FIELD_GET(HTT_T2H_PEER_MAP_INFO_PEER_ID,
				    resp->peer_map_ev.info);
		peer_mac_h16 = FIELD_GET(HTT_T2H_PEER_MAP_INFO1_MAC_ADDR_H16,
					 resp->peer_map_ev.info1);
		ath11k_dp_get_mac_addr(resp->peer_map_ev.mac_addr_l32,
				       peer_mac_h16, mac_addr);
		ath11k_peer_map_event(ab, vdev_id, peer_id, mac_addr, 0, 0);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_PEER_MAP2:
		vdev_id = FIELD_GET(HTT_T2H_PEER_MAP_INFO_VDEV_ID,
				    resp->peer_map_ev.info);
		peer_id = FIELD_GET(HTT_T2H_PEER_MAP_INFO_PEER_ID,
				    resp->peer_map_ev.info);
		peer_mac_h16 = FIELD_GET(HTT_T2H_PEER_MAP_INFO1_MAC_ADDR_H16,
					 resp->peer_map_ev.info1);
		ath11k_dp_get_mac_addr(resp->peer_map_ev.mac_addr_l32,
				       peer_mac_h16, mac_addr);
		ast_hash = FIELD_GET(HTT_T2H_PEER_MAP_INFO2_AST_HASH_VAL,
				     resp->peer_map_ev.info2);
		hw_peer_id = FIELD_GET(HTT_T2H_PEER_MAP_INFO1_HW_PEER_ID,
				       resp->peer_map_ev.info1);
		ath11k_peer_map_event(ab, vdev_id, peer_id, mac_addr, ast_hash,
				      hw_peer_id);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_PEER_UNMAP:
	हाल HTT_T2H_MSG_TYPE_PEER_UNMAP2:
		peer_id = FIELD_GET(HTT_T2H_PEER_UNMAP_INFO_PEER_ID,
				    resp->peer_unmap_ev.info);
		ath11k_peer_unmap_event(ab, peer_id);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_PPDU_STATS_IND:
		ath11k_htt_pull_ppdu_stats(ab, skb);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_EXT_STATS_CONF:
		ath11k_debugfs_htt_ext_stats_handler(ab, skb);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_PKTLOG:
		ath11k_htt_pktlog(ab, skb);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_BKPRESSURE_EVENT_IND:
		ath11k_htt_backpressure_event_handler(ab, skb);
		अवरोध;
	शेष:
		ath11k_warn(ab, "htt event %d not handled\n", type);
		अवरोध;
	पूर्ण

	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल पूर्णांक ath11k_dp_rx_msdu_coalesce(काष्ठा ath11k *ar,
				      काष्ठा sk_buff_head *msdu_list,
				      काष्ठा sk_buff *first, काष्ठा sk_buff *last,
				      u8 l3pad_bytes, पूर्णांक msdu_len)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा sk_buff *skb;
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(first);
	पूर्णांक buf_first_hdr_len, buf_first_len;
	काष्ठा hal_rx_desc *ldesc;
	पूर्णांक space_extra, rem_len, buf_len;
	u32 hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;

	/* As the msdu is spपढ़ो across multiple rx buffers,
	 * find the offset to the start of msdu क्रम computing
	 * the length of the msdu in the first buffer.
	 */
	buf_first_hdr_len = hal_rx_desc_sz + l3pad_bytes;
	buf_first_len = DP_RX_BUFFER_SIZE - buf_first_hdr_len;

	अगर (WARN_ON_ONCE(msdu_len <= buf_first_len)) अणु
		skb_put(first, buf_first_hdr_len + msdu_len);
		skb_pull(first, buf_first_hdr_len);
		वापस 0;
	पूर्ण

	ldesc = (काष्ठा hal_rx_desc *)last->data;
	rxcb->is_first_msdu = ath11k_dp_rx_h_msdu_end_first_msdu(ab, ldesc);
	rxcb->is_last_msdu = ath11k_dp_rx_h_msdu_end_last_msdu(ab, ldesc);

	/* MSDU spans over multiple buffers because the length of the MSDU
	 * exceeds DP_RX_BUFFER_SIZE - HAL_RX_DESC_SIZE. So assume the data
	 * in the first buf is of length DP_RX_BUFFER_SIZE - HAL_RX_DESC_SIZE.
	 */
	skb_put(first, DP_RX_BUFFER_SIZE);
	skb_pull(first, buf_first_hdr_len);

	/* When an MSDU spपढ़ो over multiple buffers attention, MSDU_END and
	 * MPDU_END tlvs are valid only in the last buffer. Copy those tlvs.
	 */
	ath11k_dp_rx_desc_end_tlv_copy(ab, rxcb->rx_desc, ldesc);

	space_extra = msdu_len - (buf_first_len + skb_tailroom(first));
	अगर (space_extra > 0 &&
	    (pskb_expand_head(first, 0, space_extra, GFP_ATOMIC) < 0)) अणु
		/* Free up all buffers of the MSDU */
		जबतक ((skb = __skb_dequeue(msdu_list)) != शून्य) अणु
			rxcb = ATH11K_SKB_RXCB(skb);
			अगर (!rxcb->is_continuation) अणु
				dev_kमुक्त_skb_any(skb);
				अवरोध;
			पूर्ण
			dev_kमुक्त_skb_any(skb);
		पूर्ण
		वापस -ENOMEM;
	पूर्ण

	rem_len = msdu_len - buf_first_len;
	जबतक ((skb = __skb_dequeue(msdu_list)) != शून्य && rem_len > 0) अणु
		rxcb = ATH11K_SKB_RXCB(skb);
		अगर (rxcb->is_continuation)
			buf_len = DP_RX_BUFFER_SIZE - hal_rx_desc_sz;
		अन्यथा
			buf_len = rem_len;

		अगर (buf_len > (DP_RX_BUFFER_SIZE - hal_rx_desc_sz)) अणु
			WARN_ON_ONCE(1);
			dev_kमुक्त_skb_any(skb);
			वापस -EINVAL;
		पूर्ण

		skb_put(skb, buf_len + hal_rx_desc_sz);
		skb_pull(skb, hal_rx_desc_sz);
		skb_copy_from_linear_data(skb, skb_put(first, buf_len),
					  buf_len);
		dev_kमुक्त_skb_any(skb);

		rem_len -= buf_len;
		अगर (!rxcb->is_continuation)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *ath11k_dp_rx_get_msdu_last_buf(काष्ठा sk_buff_head *msdu_list,
						      काष्ठा sk_buff *first)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(first);

	अगर (!rxcb->is_continuation)
		वापस first;

	skb_queue_walk(msdu_list, skb) अणु
		rxcb = ATH11K_SKB_RXCB(skb);
		अगर (!rxcb->is_continuation)
			वापस skb;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ath11k_dp_rx_h_csum_offload(काष्ठा ath11k *ar, काष्ठा sk_buff *msdu)
अणु
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	काष्ठा rx_attention *rx_attention;
	bool ip_csum_fail, l4_csum_fail;

	rx_attention = ath11k_dp_rx_get_attention(ar->ab, rxcb->rx_desc);
	ip_csum_fail = ath11k_dp_rx_h_attn_ip_cksum_fail(rx_attention);
	l4_csum_fail = ath11k_dp_rx_h_attn_l4_cksum_fail(rx_attention);

	msdu->ip_summed = (ip_csum_fail || l4_csum_fail) ?
			  CHECKSUM_NONE : CHECKSUM_UNNECESSARY;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_crypto_mic_len(काष्ठा ath11k *ar,
				       क्रमागत hal_encrypt_type enctype)
अणु
	चयन (enctype) अणु
	हाल HAL_ENCRYPT_TYPE_OPEN:
	हाल HAL_ENCRYPT_TYPE_TKIP_NO_MIC:
	हाल HAL_ENCRYPT_TYPE_TKIP_MIC:
		वापस 0;
	हाल HAL_ENCRYPT_TYPE_CCMP_128:
		वापस IEEE80211_CCMP_MIC_LEN;
	हाल HAL_ENCRYPT_TYPE_CCMP_256:
		वापस IEEE80211_CCMP_256_MIC_LEN;
	हाल HAL_ENCRYPT_TYPE_GCMP_128:
	हाल HAL_ENCRYPT_TYPE_AES_GCMP_256:
		वापस IEEE80211_GCMP_MIC_LEN;
	हाल HAL_ENCRYPT_TYPE_WEP_40:
	हाल HAL_ENCRYPT_TYPE_WEP_104:
	हाल HAL_ENCRYPT_TYPE_WEP_128:
	हाल HAL_ENCRYPT_TYPE_WAPI_GCM_SM4:
	हाल HAL_ENCRYPT_TYPE_WAPI:
		अवरोध;
	पूर्ण

	ath11k_warn(ar->ab, "unsupported encryption type %d for mic len\n", enctype);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_crypto_param_len(काष्ठा ath11k *ar,
					 क्रमागत hal_encrypt_type enctype)
अणु
	चयन (enctype) अणु
	हाल HAL_ENCRYPT_TYPE_OPEN:
		वापस 0;
	हाल HAL_ENCRYPT_TYPE_TKIP_NO_MIC:
	हाल HAL_ENCRYPT_TYPE_TKIP_MIC:
		वापस IEEE80211_TKIP_IV_LEN;
	हाल HAL_ENCRYPT_TYPE_CCMP_128:
		वापस IEEE80211_CCMP_HDR_LEN;
	हाल HAL_ENCRYPT_TYPE_CCMP_256:
		वापस IEEE80211_CCMP_256_HDR_LEN;
	हाल HAL_ENCRYPT_TYPE_GCMP_128:
	हाल HAL_ENCRYPT_TYPE_AES_GCMP_256:
		वापस IEEE80211_GCMP_HDR_LEN;
	हाल HAL_ENCRYPT_TYPE_WEP_40:
	हाल HAL_ENCRYPT_TYPE_WEP_104:
	हाल HAL_ENCRYPT_TYPE_WEP_128:
	हाल HAL_ENCRYPT_TYPE_WAPI_GCM_SM4:
	हाल HAL_ENCRYPT_TYPE_WAPI:
		अवरोध;
	पूर्ण

	ath11k_warn(ar->ab, "unsupported encryption type %d\n", enctype);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_crypto_icv_len(काष्ठा ath11k *ar,
				       क्रमागत hal_encrypt_type enctype)
अणु
	चयन (enctype) अणु
	हाल HAL_ENCRYPT_TYPE_OPEN:
	हाल HAL_ENCRYPT_TYPE_CCMP_128:
	हाल HAL_ENCRYPT_TYPE_CCMP_256:
	हाल HAL_ENCRYPT_TYPE_GCMP_128:
	हाल HAL_ENCRYPT_TYPE_AES_GCMP_256:
		वापस 0;
	हाल HAL_ENCRYPT_TYPE_TKIP_NO_MIC:
	हाल HAL_ENCRYPT_TYPE_TKIP_MIC:
		वापस IEEE80211_TKIP_ICV_LEN;
	हाल HAL_ENCRYPT_TYPE_WEP_40:
	हाल HAL_ENCRYPT_TYPE_WEP_104:
	हाल HAL_ENCRYPT_TYPE_WEP_128:
	हाल HAL_ENCRYPT_TYPE_WAPI_GCM_SM4:
	हाल HAL_ENCRYPT_TYPE_WAPI:
		अवरोध;
	पूर्ण

	ath11k_warn(ar->ab, "unsupported encryption type %d\n", enctype);
	वापस 0;
पूर्ण

अटल व्योम ath11k_dp_rx_h_undecap_nwअगरi(काष्ठा ath11k *ar,
					 काष्ठा sk_buff *msdu,
					 u8 *first_hdr,
					 क्रमागत hal_encrypt_type enctype,
					 काष्ठा ieee80211_rx_status *status)
अणु
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	u8 decap_hdr[DP_MAX_NWIFI_HDR_LEN];
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdr_len;
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
	u16 qos_ctl = 0;
	u8 *qos;

	/* copy SA & DA and pull decapped header */
	hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	hdr_len = ieee80211_hdrlen(hdr->frame_control);
	ether_addr_copy(da, ieee80211_get_DA(hdr));
	ether_addr_copy(sa, ieee80211_get_SA(hdr));
	skb_pull(msdu, ieee80211_hdrlen(hdr->frame_control));

	अगर (rxcb->is_first_msdu) अणु
		/* original 802.11 header is valid क्रम the first msdu
		 * hence we can reuse the same header
		 */
		hdr = (काष्ठा ieee80211_hdr *)first_hdr;
		hdr_len = ieee80211_hdrlen(hdr->frame_control);

		/* Each A-MSDU subframe will be reported as a separate MSDU,
		 * so strip the A-MSDU bit from QoS Ctl.
		 */
		अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
			qos = ieee80211_get_qos_ctl(hdr);
			qos[0] &= ~IEEE80211_QOS_CTL_A_MSDU_PRESENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*  Rebuild qos header अगर this is a middle/last msdu */
		hdr->frame_control |= __cpu_to_le16(IEEE80211_STYPE_QOS_DATA);

		/* Reset the order bit as the HT_Control header is stripped */
		hdr->frame_control &= ~(__cpu_to_le16(IEEE80211_FCTL_ORDER));

		qos_ctl = rxcb->tid;

		अगर (ath11k_dp_rx_h_msdu_start_mesh_ctl_present(ar->ab, rxcb->rx_desc))
			qos_ctl |= IEEE80211_QOS_CTL_MESH_CONTROL_PRESENT;

		/* TODO Add other QoS ctl fields when required */

		/* copy decap header beक्रमe overwriting क्रम reuse below */
		स_नकल(decap_hdr, (uपूर्णांक8_t *)hdr, hdr_len);
	पूर्ण

	अगर (!(status->flag & RX_FLAG_IV_STRIPPED)) अणु
		स_नकल(skb_push(msdu,
				ath11k_dp_rx_crypto_param_len(ar, enctype)),
		       (व्योम *)hdr + hdr_len,
		       ath11k_dp_rx_crypto_param_len(ar, enctype));
	पूर्ण

	अगर (!rxcb->is_first_msdu) अणु
		स_नकल(skb_push(msdu,
				IEEE80211_QOS_CTL_LEN), &qos_ctl,
				IEEE80211_QOS_CTL_LEN);
		स_नकल(skb_push(msdu, hdr_len), decap_hdr, hdr_len);
		वापस;
	पूर्ण

	स_नकल(skb_push(msdu, hdr_len), hdr, hdr_len);

	/* original 802.11 header has a dअगरferent DA and in
	 * हाल of 4addr it may also have dअगरferent SA
	 */
	hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	ether_addr_copy(ieee80211_get_DA(hdr), da);
	ether_addr_copy(ieee80211_get_SA(hdr), sa);
पूर्ण

अटल व्योम ath11k_dp_rx_h_undecap_raw(काष्ठा ath11k *ar, काष्ठा sk_buff *msdu,
				       क्रमागत hal_encrypt_type enctype,
				       काष्ठा ieee80211_rx_status *status,
				       bool decrypted)
अणु
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdr_len;
	माप_प्रकार crypto_len;

	अगर (!rxcb->is_first_msdu ||
	    !(rxcb->is_first_msdu && rxcb->is_last_msdu)) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	skb_trim(msdu, msdu->len - FCS_LEN);

	अगर (!decrypted)
		वापस;

	hdr = (व्योम *)msdu->data;

	/* Tail */
	अगर (status->flag & RX_FLAG_IV_STRIPPED) अणु
		skb_trim(msdu, msdu->len -
			 ath11k_dp_rx_crypto_mic_len(ar, enctype));

		skb_trim(msdu, msdu->len -
			 ath11k_dp_rx_crypto_icv_len(ar, enctype));
	पूर्ण अन्यथा अणु
		/* MIC */
		अगर (status->flag & RX_FLAG_MIC_STRIPPED)
			skb_trim(msdu, msdu->len -
				 ath11k_dp_rx_crypto_mic_len(ar, enctype));

		/* ICV */
		अगर (status->flag & RX_FLAG_ICV_STRIPPED)
			skb_trim(msdu, msdu->len -
				 ath11k_dp_rx_crypto_icv_len(ar, enctype));
	पूर्ण

	/* MMIC */
	अगर ((status->flag & RX_FLAG_MMIC_STRIPPED) &&
	    !ieee80211_has_morefrags(hdr->frame_control) &&
	    enctype == HAL_ENCRYPT_TYPE_TKIP_MIC)
		skb_trim(msdu, msdu->len - IEEE80211_CCMP_MIC_LEN);

	/* Head */
	अगर (status->flag & RX_FLAG_IV_STRIPPED) अणु
		hdr_len = ieee80211_hdrlen(hdr->frame_control);
		crypto_len = ath11k_dp_rx_crypto_param_len(ar, enctype);

		स_हटाओ((व्योम *)msdu->data + crypto_len,
			(व्योम *)msdu->data, hdr_len);
		skb_pull(msdu, crypto_len);
	पूर्ण
पूर्ण

अटल व्योम *ath11k_dp_rx_h_find_rfc1042(काष्ठा ath11k *ar,
					 काष्ठा sk_buff *msdu,
					 क्रमागत hal_encrypt_type enctype)
अणु
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdr_len, crypto_len;
	व्योम *rfc1042;
	bool is_amsdu;

	is_amsdu = !(rxcb->is_first_msdu && rxcb->is_last_msdu);
	hdr = (काष्ठा ieee80211_hdr *)ath11k_dp_rx_h_80211_hdr(ar->ab, rxcb->rx_desc);
	rfc1042 = hdr;

	अगर (rxcb->is_first_msdu) अणु
		hdr_len = ieee80211_hdrlen(hdr->frame_control);
		crypto_len = ath11k_dp_rx_crypto_param_len(ar, enctype);

		rfc1042 += hdr_len + crypto_len;
	पूर्ण

	अगर (is_amsdu)
		rfc1042 += माप(काष्ठा ath11k_dp_amsdu_subframe_hdr);

	वापस rfc1042;
पूर्ण

अटल व्योम ath11k_dp_rx_h_undecap_eth(काष्ठा ath11k *ar,
				       काष्ठा sk_buff *msdu,
				       u8 *first_hdr,
				       क्रमागत hal_encrypt_type enctype,
				       काष्ठा ieee80211_rx_status *status)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ethhdr *eth;
	माप_प्रकार hdr_len;
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
	व्योम *rfc1042;

	rfc1042 = ath11k_dp_rx_h_find_rfc1042(ar, msdu, enctype);
	अगर (WARN_ON_ONCE(!rfc1042))
		वापस;

	/* pull decapped header and copy SA & DA */
	eth = (काष्ठा ethhdr *)msdu->data;
	ether_addr_copy(da, eth->h_dest);
	ether_addr_copy(sa, eth->h_source);
	skb_pull(msdu, माप(काष्ठा ethhdr));

	/* push rfc1042/llc/snap */
	स_नकल(skb_push(msdu, माप(काष्ठा ath11k_dp_rfc1042_hdr)), rfc1042,
	       माप(काष्ठा ath11k_dp_rfc1042_hdr));

	/* push original 802.11 header */
	hdr = (काष्ठा ieee80211_hdr *)first_hdr;
	hdr_len = ieee80211_hdrlen(hdr->frame_control);

	अगर (!(status->flag & RX_FLAG_IV_STRIPPED)) अणु
		स_नकल(skb_push(msdu,
				ath11k_dp_rx_crypto_param_len(ar, enctype)),
		       (व्योम *)hdr + hdr_len,
		       ath11k_dp_rx_crypto_param_len(ar, enctype));
	पूर्ण

	स_नकल(skb_push(msdu, hdr_len), hdr, hdr_len);

	/* original 802.11 header has a dअगरferent DA and in
	 * हाल of 4addr it may also have dअगरferent SA
	 */
	hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	ether_addr_copy(ieee80211_get_DA(hdr), da);
	ether_addr_copy(ieee80211_get_SA(hdr), sa);
पूर्ण

अटल व्योम ath11k_dp_rx_h_undecap(काष्ठा ath11k *ar, काष्ठा sk_buff *msdu,
				   काष्ठा hal_rx_desc *rx_desc,
				   क्रमागत hal_encrypt_type enctype,
				   काष्ठा ieee80211_rx_status *status,
				   bool decrypted)
अणु
	u8 *first_hdr;
	u8 decap;

	first_hdr = ath11k_dp_rx_h_80211_hdr(ar->ab, rx_desc);
	decap = ath11k_dp_rx_h_msdu_start_decap_type(ar->ab, rx_desc);

	चयन (decap) अणु
	हाल DP_RX_DECAP_TYPE_NATIVE_WIFI:
		ath11k_dp_rx_h_undecap_nwअगरi(ar, msdu, first_hdr,
					     enctype, status);
		अवरोध;
	हाल DP_RX_DECAP_TYPE_RAW:
		ath11k_dp_rx_h_undecap_raw(ar, msdu, enctype, status,
					   decrypted);
		अवरोध;
	हाल DP_RX_DECAP_TYPE_ETHERNET2_DIX:
		/* TODO undecap support क्रम middle/last msdu's of amsdu */
		ath11k_dp_rx_h_undecap_eth(ar, msdu, first_hdr,
					   enctype, status);
		अवरोध;
	हाल DP_RX_DECAP_TYPE_8023:
		/* TODO: Handle undecap क्रम these क्रमmats */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_dp_rx_h_mpdu(काष्ठा ath11k *ar,
				काष्ठा sk_buff *msdu,
				काष्ठा hal_rx_desc *rx_desc,
				काष्ठा ieee80211_rx_status *rx_status)
अणु
	bool  fill_crypto_hdr, mcast;
	क्रमागत hal_encrypt_type enctype;
	bool is_decrypted = false;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath11k_peer *peer;
	काष्ठा rx_attention *rx_attention;
	u32 err_biपंचांगap;

	hdr = (काष्ठा ieee80211_hdr *)msdu->data;

	/* PN क्रम multicast packets will be checked in mac80211 */

	mcast = is_multicast_ether_addr(hdr->addr1);
	fill_crypto_hdr = mcast;

	spin_lock_bh(&ar->ab->base_lock);
	peer = ath11k_peer_find_by_addr(ar->ab, hdr->addr2);
	अगर (peer) अणु
		अगर (mcast)
			enctype = peer->sec_type_grp;
		अन्यथा
			enctype = peer->sec_type;
	पूर्ण अन्यथा अणु
		enctype = HAL_ENCRYPT_TYPE_OPEN;
	पूर्ण
	spin_unlock_bh(&ar->ab->base_lock);

	rx_attention = ath11k_dp_rx_get_attention(ar->ab, rx_desc);
	err_biपंचांगap = ath11k_dp_rx_h_attn_mpdu_err(rx_attention);
	अगर (enctype != HAL_ENCRYPT_TYPE_OPEN && !err_biपंचांगap)
		is_decrypted = ath11k_dp_rx_h_attn_is_decrypted(rx_attention);

	/* Clear per-MPDU flags जबतक leaving per-PPDU flags पूर्णांकact */
	rx_status->flag &= ~(RX_FLAG_FAILED_FCS_CRC |
			     RX_FLAG_MMIC_ERROR |
			     RX_FLAG_DECRYPTED |
			     RX_FLAG_IV_STRIPPED |
			     RX_FLAG_MMIC_STRIPPED);

	अगर (err_biपंचांगap & DP_RX_MPDU_ERR_FCS)
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	अगर (err_biपंचांगap & DP_RX_MPDU_ERR_TKIP_MIC)
		rx_status->flag |= RX_FLAG_MMIC_ERROR;

	अगर (is_decrypted) अणु
		rx_status->flag |= RX_FLAG_DECRYPTED | RX_FLAG_MMIC_STRIPPED;

		अगर (fill_crypto_hdr)
			rx_status->flag |= RX_FLAG_MIC_STRIPPED |
					RX_FLAG_ICV_STRIPPED;
		अन्यथा
			rx_status->flag |= RX_FLAG_IV_STRIPPED |
					   RX_FLAG_PN_VALIDATED;
	पूर्ण

	ath11k_dp_rx_h_csum_offload(ar, msdu);
	ath11k_dp_rx_h_undecap(ar, msdu, rx_desc,
			       enctype, rx_status, is_decrypted);

	अगर (!is_decrypted || fill_crypto_hdr)
		वापस;

	hdr = (व्योम *)msdu->data;
	hdr->frame_control &= ~__cpu_to_le16(IEEE80211_FCTL_PROTECTED);
पूर्ण

अटल व्योम ath11k_dp_rx_h_rate(काष्ठा ath11k *ar, काष्ठा hal_rx_desc *rx_desc,
				काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत rx_msdu_start_pkt_type pkt_type;
	u8 bw;
	u8 rate_mcs, nss;
	u8 sgi;
	bool is_cck;

	pkt_type = ath11k_dp_rx_h_msdu_start_pkt_type(ar->ab, rx_desc);
	bw = ath11k_dp_rx_h_msdu_start_rx_bw(ar->ab, rx_desc);
	rate_mcs = ath11k_dp_rx_h_msdu_start_rate_mcs(ar->ab, rx_desc);
	nss = ath11k_dp_rx_h_msdu_start_nss(ar->ab, rx_desc);
	sgi = ath11k_dp_rx_h_msdu_start_sgi(ar->ab, rx_desc);

	चयन (pkt_type) अणु
	हाल RX_MSDU_START_PKT_TYPE_11A:
	हाल RX_MSDU_START_PKT_TYPE_11B:
		is_cck = (pkt_type == RX_MSDU_START_PKT_TYPE_11B);
		sband = &ar->mac.sbands[rx_status->band];
		rx_status->rate_idx = ath11k_mac_hw_rate_to_idx(sband, rate_mcs,
								is_cck);
		अवरोध;
	हाल RX_MSDU_START_PKT_TYPE_11N:
		rx_status->encoding = RX_ENC_HT;
		अगर (rate_mcs > ATH11K_HT_MCS_MAX) अणु
			ath11k_warn(ar->ab,
				    "Received with invalid mcs in HT mode %d\n",
				     rate_mcs);
			अवरोध;
		पूर्ण
		rx_status->rate_idx = rate_mcs + (8 * (nss - 1));
		अगर (sgi)
			rx_status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
		rx_status->bw = ath11k_mac_bw_to_mac80211_bw(bw);
		अवरोध;
	हाल RX_MSDU_START_PKT_TYPE_11AC:
		rx_status->encoding = RX_ENC_VHT;
		rx_status->rate_idx = rate_mcs;
		अगर (rate_mcs > ATH11K_VHT_MCS_MAX) अणु
			ath11k_warn(ar->ab,
				    "Received with invalid mcs in VHT mode %d\n",
				     rate_mcs);
			अवरोध;
		पूर्ण
		rx_status->nss = nss;
		अगर (sgi)
			rx_status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
		rx_status->bw = ath11k_mac_bw_to_mac80211_bw(bw);
		अवरोध;
	हाल RX_MSDU_START_PKT_TYPE_11AX:
		rx_status->rate_idx = rate_mcs;
		अगर (rate_mcs > ATH11K_HE_MCS_MAX) अणु
			ath11k_warn(ar->ab,
				    "Received with invalid mcs in HE mode %d\n",
				    rate_mcs);
			अवरोध;
		पूर्ण
		rx_status->encoding = RX_ENC_HE;
		rx_status->nss = nss;
		rx_status->he_gi = ath11k_he_gi_to_nl80211_he_gi(sgi);
		rx_status->bw = ath11k_mac_bw_to_mac80211_bw(bw);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_dp_rx_h_ppdu(काष्ठा ath11k *ar, काष्ठा hal_rx_desc *rx_desc,
				काष्ठा ieee80211_rx_status *rx_status)
अणु
	u8 channel_num;
	u32 center_freq, meta_data;
	काष्ठा ieee80211_channel *channel;

	rx_status->freq = 0;
	rx_status->rate_idx = 0;
	rx_status->nss = 0;
	rx_status->encoding = RX_ENC_LEGACY;
	rx_status->bw = RATE_INFO_BW_20;

	rx_status->flag |= RX_FLAG_NO_SIGNAL_VAL;

	meta_data = ath11k_dp_rx_h_msdu_start_freq(ar->ab, rx_desc);
	channel_num = meta_data;
	center_freq = meta_data >> 16;

	अगर (center_freq >= 5935 && center_freq <= 7105) अणु
		rx_status->band = NL80211_BAND_6GHZ;
	पूर्ण अन्यथा अगर (channel_num >= 1 && channel_num <= 14) अणु
		rx_status->band = NL80211_BAND_2GHZ;
	पूर्ण अन्यथा अगर (channel_num >= 36 && channel_num <= 173) अणु
		rx_status->band = NL80211_BAND_5GHZ;
	पूर्ण अन्यथा अणु
		spin_lock_bh(&ar->data_lock);
		channel = ar->rx_channel;
		अगर (channel) अणु
			rx_status->band = channel->band;
			channel_num =
				ieee80211_frequency_to_channel(channel->center_freq);
		पूर्ण
		spin_unlock_bh(&ar->data_lock);
		ath11k_dbg_dump(ar->ab, ATH11K_DBG_DATA, शून्य, "rx_desc: ",
				rx_desc, माप(काष्ठा hal_rx_desc));
	पूर्ण

	rx_status->freq = ieee80211_channel_to_frequency(channel_num,
							 rx_status->band);

	ath11k_dp_rx_h_rate(ar, rx_desc, rx_status);
पूर्ण

अटल अक्षर *ath11k_prपूर्णांक_get_tid(काष्ठा ieee80211_hdr *hdr, अक्षर *out,
				  माप_प्रकार size)
अणु
	u8 *qc;
	पूर्णांक tid;

	अगर (!ieee80211_is_data_qos(hdr->frame_control))
		वापस "";

	qc = ieee80211_get_qos_ctl(hdr);
	tid = *qc & IEEE80211_QOS_CTL_TID_MASK;
	snम_लिखो(out, size, "tid %d", tid);

	वापस out;
पूर्ण

अटल व्योम ath11k_dp_rx_deliver_msdu(काष्ठा ath11k *ar, काष्ठा napi_काष्ठा *napi,
				      काष्ठा sk_buff *msdu)
अणु
	अटल स्थिर काष्ठा ieee80211_radiotap_he known = अणु
		.data1 = cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
				     IEEE80211_RADIOTAP_HE_DATA1_BW_RU_ALLOC_KNOWN),
		.data2 = cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA2_GI_KNOWN),
	पूर्ण;
	काष्ठा ieee80211_rx_status *status;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	काष्ठा ieee80211_radiotap_he *he = शून्य;
	अक्षर tid[32];

	status = IEEE80211_SKB_RXCB(msdu);
	अगर (status->encoding == RX_ENC_HE) अणु
		he = skb_push(msdu, माप(known));
		स_नकल(he, &known, माप(known));
		status->flag |= RX_FLAG_RADIOTAP_HE;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_DATA,
		   "rx skb %pK len %u peer %pM %s %s sn %u %s%s%s%s%s%s%s %srate_idx %u vht_nss %u freq %u band %u flag 0x%x fcs-err %i mic-err %i amsdu-more %i\n",
		   msdu,
		   msdu->len,
		   ieee80211_get_SA(hdr),
		   ath11k_prपूर्णांक_get_tid(hdr, tid, माप(tid)),
		   is_multicast_ether_addr(ieee80211_get_DA(hdr)) ?
							"mcast" : "ucast",
		   (__le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4,
		   (status->encoding == RX_ENC_LEGACY) ? "legacy" : "",
		   (status->encoding == RX_ENC_HT) ? "ht" : "",
		   (status->encoding == RX_ENC_VHT) ? "vht" : "",
		   (status->encoding == RX_ENC_HE) ? "he" : "",
		   (status->bw == RATE_INFO_BW_40) ? "40" : "",
		   (status->bw == RATE_INFO_BW_80) ? "80" : "",
		   (status->bw == RATE_INFO_BW_160) ? "160" : "",
		   status->enc_flags & RX_ENC_FLAG_SHORT_GI ? "sgi " : "",
		   status->rate_idx,
		   status->nss,
		   status->freq,
		   status->band, status->flag,
		   !!(status->flag & RX_FLAG_FAILED_FCS_CRC),
		   !!(status->flag & RX_FLAG_MMIC_ERROR),
		   !!(status->flag & RX_FLAG_AMSDU_MORE));

	ath11k_dbg_dump(ar->ab, ATH11K_DBG_DP_RX, शून्य, "dp rx msdu: ",
			msdu->data, msdu->len);

	/* TODO: trace rx packet */

	ieee80211_rx_napi(ar->hw, शून्य, msdu, napi);
पूर्ण

अटल पूर्णांक ath11k_dp_rx_process_msdu(काष्ठा ath11k *ar,
				     काष्ठा sk_buff *msdu,
				     काष्ठा sk_buff_head *msdu_list)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा hal_rx_desc *rx_desc, *lrx_desc;
	काष्ठा rx_attention *rx_attention;
	काष्ठा ieee80211_rx_status rx_status = अणु0पूर्ण;
	काष्ठा ieee80211_rx_status *status;
	काष्ठा ath11k_skb_rxcb *rxcb;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा sk_buff *last_buf;
	u8 l3_pad_bytes;
	u8 *hdr_status;
	u16 msdu_len;
	पूर्णांक ret;
	u32 hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;

	last_buf = ath11k_dp_rx_get_msdu_last_buf(msdu_list, msdu);
	अगर (!last_buf) अणु
		ath11k_warn(ab,
			    "No valid Rx buffer to access Atten/MSDU_END/MPDU_END tlvs\n");
		ret = -EIO;
		जाओ मुक्त_out;
	पूर्ण

	rx_desc = (काष्ठा hal_rx_desc *)msdu->data;
	lrx_desc = (काष्ठा hal_rx_desc *)last_buf->data;
	rx_attention = ath11k_dp_rx_get_attention(ab, lrx_desc);
	अगर (!ath11k_dp_rx_h_attn_msdu_करोne(rx_attention)) अणु
		ath11k_warn(ab, "msdu_done bit in attention is not set\n");
		ret = -EIO;
		जाओ मुक्त_out;
	पूर्ण

	rxcb = ATH11K_SKB_RXCB(msdu);
	rxcb->rx_desc = rx_desc;
	msdu_len = ath11k_dp_rx_h_msdu_start_msdu_len(ab, rx_desc);
	l3_pad_bytes = ath11k_dp_rx_h_msdu_end_l3pad(ab, lrx_desc);

	अगर (rxcb->is_frag) अणु
		skb_pull(msdu, hal_rx_desc_sz);
	पूर्ण अन्यथा अगर (!rxcb->is_continuation) अणु
		अगर ((msdu_len + hal_rx_desc_sz) > DP_RX_BUFFER_SIZE) अणु
			hdr_status = ath11k_dp_rx_h_80211_hdr(ab, rx_desc);
			ret = -EINVAL;
			ath11k_warn(ab, "invalid msdu len %u\n", msdu_len);
			ath11k_dbg_dump(ab, ATH11K_DBG_DATA, शून्य, "", hdr_status,
					माप(काष्ठा ieee80211_hdr));
			ath11k_dbg_dump(ab, ATH11K_DBG_DATA, शून्य, "", rx_desc,
					माप(काष्ठा hal_rx_desc));
			जाओ मुक्त_out;
		पूर्ण
		skb_put(msdu, hal_rx_desc_sz + l3_pad_bytes + msdu_len);
		skb_pull(msdu, hal_rx_desc_sz + l3_pad_bytes);
	पूर्ण अन्यथा अणु
		ret = ath11k_dp_rx_msdu_coalesce(ar, msdu_list,
						 msdu, last_buf,
						 l3_pad_bytes, msdu_len);
		अगर (ret) अणु
			ath11k_warn(ab,
				    "failed to coalesce msdu rx buffer%d\n", ret);
			जाओ मुक्त_out;
		पूर्ण
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *)msdu->data;

	/* Process only data frames */
	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस -EINVAL;

	ath11k_dp_rx_h_ppdu(ar, rx_desc, &rx_status);
	ath11k_dp_rx_h_mpdu(ar, msdu, rx_desc, &rx_status);

	rx_status.flag |= RX_FLAG_SKIP_MONITOR | RX_FLAG_DUP_VALIDATED;

	status = IEEE80211_SKB_RXCB(msdu);
	*status = rx_status;
	वापस 0;

मुक्त_out:
	वापस ret;
पूर्ण

अटल व्योम ath11k_dp_rx_process_received_packets(काष्ठा ath11k_base *ab,
						  काष्ठा napi_काष्ठा *napi,
						  काष्ठा sk_buff_head *msdu_list,
						  पूर्णांक *quota, पूर्णांक ring_id)
अणु
	काष्ठा ath11k_skb_rxcb *rxcb;
	काष्ठा sk_buff *msdu;
	काष्ठा ath11k *ar;
	u8 mac_id;
	पूर्णांक ret;

	अगर (skb_queue_empty(msdu_list))
		वापस;

	rcu_पढ़ो_lock();

	जबतक (*quota && (msdu = __skb_dequeue(msdu_list))) अणु
		rxcb = ATH11K_SKB_RXCB(msdu);
		mac_id = rxcb->mac_id;
		ar = ab->pdevs[mac_id].ar;
		अगर (!rcu_dereference(ab->pdevs_active[mac_id])) अणु
			dev_kमुक्त_skb_any(msdu);
			जारी;
		पूर्ण

		अगर (test_bit(ATH11K_CAC_RUNNING, &ar->dev_flags)) अणु
			dev_kमुक्त_skb_any(msdu);
			जारी;
		पूर्ण

		ret = ath11k_dp_rx_process_msdu(ar, msdu, msdu_list);
		अगर (ret) अणु
			ath11k_dbg(ab, ATH11K_DBG_DATA,
				   "Unable to process msdu %d", ret);
			dev_kमुक्त_skb_any(msdu);
			जारी;
		पूर्ण

		ath11k_dp_rx_deliver_msdu(ar, napi, msdu);
		(*quota)--;
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक ath11k_dp_process_rx(काष्ठा ath11k_base *ab, पूर्णांक ring_id,
			 काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा dp_rxdma_ring *rx_ring;
	पूर्णांक num_buffs_reaped[MAX_RADIOS] = अणु0पूर्ण;
	काष्ठा sk_buff_head msdu_list;
	काष्ठा ath11k_skb_rxcb *rxcb;
	पूर्णांक total_msdu_reaped = 0;
	काष्ठा hal_srng *srng;
	काष्ठा sk_buff *msdu;
	पूर्णांक quota = budget;
	bool करोne = false;
	पूर्णांक buf_id, mac_id;
	काष्ठा ath11k *ar;
	u32 *rx_desc;
	पूर्णांक i;

	__skb_queue_head_init(&msdu_list);

	srng = &ab->hal.srng_list[dp->reo_dst_ring[ring_id].ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

try_again:
	जबतक ((rx_desc = ath11k_hal_srng_dst_get_next_entry(ab, srng))) अणु
		काष्ठा hal_reo_dest_ring desc = *(काष्ठा hal_reo_dest_ring *)rx_desc;
		क्रमागत hal_reo_dest_ring_push_reason push_reason;
		u32 cookie;

		cookie = FIELD_GET(BUFFER_ADDR_INFO1_SW_COOKIE,
				   desc.buf_addr_info.info1);
		buf_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_BUF_ID,
				   cookie);
		mac_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_PDEV_ID, cookie);

		ar = ab->pdevs[mac_id].ar;
		rx_ring = &ar->dp.rx_refill_buf_ring;
		spin_lock_bh(&rx_ring->idr_lock);
		msdu = idr_find(&rx_ring->bufs_idr, buf_id);
		अगर (!msdu) अणु
			ath11k_warn(ab, "frame rx with invalid buf_id %d\n",
				    buf_id);
			spin_unlock_bh(&rx_ring->idr_lock);
			जारी;
		पूर्ण

		idr_हटाओ(&rx_ring->bufs_idr, buf_id);
		spin_unlock_bh(&rx_ring->idr_lock);

		rxcb = ATH11K_SKB_RXCB(msdu);
		dma_unmap_single(ab->dev, rxcb->paddr,
				 msdu->len + skb_tailroom(msdu),
				 DMA_FROM_DEVICE);

		num_buffs_reaped[mac_id]++;
		total_msdu_reaped++;

		push_reason = FIELD_GET(HAL_REO_DEST_RING_INFO0_PUSH_REASON,
					desc.info0);
		अगर (push_reason !=
		    HAL_REO_DEST_RING_PUSH_REASON_ROUTING_INSTRUCTION) अणु
			dev_kमुक्त_skb_any(msdu);
			ab->soc_stats.hal_reo_error[dp->reo_dst_ring[ring_id].ring_id]++;
			जारी;
		पूर्ण

		rxcb->is_first_msdu = !!(desc.rx_msdu_info.info0 &
					 RX_MSDU_DESC_INFO0_FIRST_MSDU_IN_MPDU);
		rxcb->is_last_msdu = !!(desc.rx_msdu_info.info0 &
					RX_MSDU_DESC_INFO0_LAST_MSDU_IN_MPDU);
		rxcb->is_continuation = !!(desc.rx_msdu_info.info0 &
					   RX_MSDU_DESC_INFO0_MSDU_CONTINUATION);
		rxcb->mac_id = mac_id;
		rxcb->tid = FIELD_GET(HAL_REO_DEST_RING_INFO0_RX_QUEUE_NUM,
				      desc.info0);

		__skb_queue_tail(&msdu_list, msdu);

		अगर (total_msdu_reaped >= quota && !rxcb->is_continuation) अणु
			करोne = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Hw might have updated the head poपूर्णांकer after we cached it.
	 * In this हाल, even though there are entries in the ring we'll
	 * get rx_desc शून्य. Give the पढ़ो another try with updated cached
	 * head poपूर्णांकer so that we can reap complete MPDU in the current
	 * rx processing.
	 */
	अगर (!करोne && ath11k_hal_srng_dst_num_मुक्त(ab, srng, true)) अणु
		ath11k_hal_srng_access_end(ab, srng);
		जाओ try_again;
	पूर्ण

	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	अगर (!total_msdu_reaped)
		जाओ निकास;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		अगर (!num_buffs_reaped[i])
			जारी;

		ar = ab->pdevs[i].ar;
		rx_ring = &ar->dp.rx_refill_buf_ring;

		ath11k_dp_rxbufs_replenish(ab, i, rx_ring, num_buffs_reaped[i],
					   HAL_RX_BUF_RBM_SW3_BM);
	पूर्ण

	ath11k_dp_rx_process_received_packets(ab, napi, &msdu_list,
					      &quota, ring_id);

निकास:
	वापस budget - quota;
पूर्ण

अटल व्योम ath11k_dp_rx_update_peer_stats(काष्ठा ath11k_sta *arsta,
					   काष्ठा hal_rx_mon_ppdu_info *ppdu_info)
अणु
	काष्ठा ath11k_rx_peer_stats *rx_stats = arsta->rx_stats;
	u32 num_msdu;

	अगर (!rx_stats)
		वापस;

	num_msdu = ppdu_info->tcp_msdu_count + ppdu_info->tcp_ack_msdu_count +
		   ppdu_info->udp_msdu_count + ppdu_info->other_msdu_count;

	rx_stats->num_msdu += num_msdu;
	rx_stats->tcp_msdu_count += ppdu_info->tcp_msdu_count +
				    ppdu_info->tcp_ack_msdu_count;
	rx_stats->udp_msdu_count += ppdu_info->udp_msdu_count;
	rx_stats->other_msdu_count += ppdu_info->other_msdu_count;

	अगर (ppdu_info->preamble_type == HAL_RX_PREAMBLE_11A ||
	    ppdu_info->preamble_type == HAL_RX_PREAMBLE_11B) अणु
		ppdu_info->nss = 1;
		ppdu_info->mcs = HAL_RX_MAX_MCS;
		ppdu_info->tid = IEEE80211_NUM_TIDS;
	पूर्ण

	अगर (ppdu_info->nss > 0 && ppdu_info->nss <= HAL_RX_MAX_NSS)
		rx_stats->nss_count[ppdu_info->nss - 1] += num_msdu;

	अगर (ppdu_info->mcs <= HAL_RX_MAX_MCS)
		rx_stats->mcs_count[ppdu_info->mcs] += num_msdu;

	अगर (ppdu_info->gi < HAL_RX_GI_MAX)
		rx_stats->gi_count[ppdu_info->gi] += num_msdu;

	अगर (ppdu_info->bw < HAL_RX_BW_MAX)
		rx_stats->bw_count[ppdu_info->bw] += num_msdu;

	अगर (ppdu_info->ldpc < HAL_RX_SU_MU_CODING_MAX)
		rx_stats->coding_count[ppdu_info->ldpc] += num_msdu;

	अगर (ppdu_info->tid <= IEEE80211_NUM_TIDS)
		rx_stats->tid_count[ppdu_info->tid] += num_msdu;

	अगर (ppdu_info->preamble_type < HAL_RX_PREAMBLE_MAX)
		rx_stats->pream_cnt[ppdu_info->preamble_type] += num_msdu;

	अगर (ppdu_info->reception_type < HAL_RX_RECEPTION_TYPE_MAX)
		rx_stats->reception_type[ppdu_info->reception_type] += num_msdu;

	अगर (ppdu_info->is_stbc)
		rx_stats->stbc_count += num_msdu;

	अगर (ppdu_info->beamक्रमmed)
		rx_stats->beamक्रमmed_count += num_msdu;

	अगर (ppdu_info->num_mpdu_fcs_ok > 1)
		rx_stats->ampdu_msdu_count += num_msdu;
	अन्यथा
		rx_stats->non_ampdu_msdu_count += num_msdu;

	rx_stats->num_mpdu_fcs_ok += ppdu_info->num_mpdu_fcs_ok;
	rx_stats->num_mpdu_fcs_err += ppdu_info->num_mpdu_fcs_err;
	rx_stats->dcm_count += ppdu_info->dcm;
	rx_stats->ru_alloc_cnt[ppdu_info->ru_alloc] += num_msdu;

	arsta->rssi_comb = ppdu_info->rssi_comb;
	rx_stats->rx_duration += ppdu_info->rx_duration;
	arsta->rx_duration = rx_stats->rx_duration;
पूर्ण

अटल काष्ठा sk_buff *ath11k_dp_rx_alloc_mon_status_buf(काष्ठा ath11k_base *ab,
							 काष्ठा dp_rxdma_ring *rx_ring,
							 पूर्णांक *buf_id)
अणु
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;

	skb = dev_alloc_skb(DP_RX_BUFFER_SIZE +
			    DP_RX_BUFFER_ALIGN_SIZE);

	अगर (!skb)
		जाओ fail_alloc_skb;

	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data,
			DP_RX_BUFFER_ALIGN_SIZE)) अणु
		skb_pull(skb, PTR_ALIGN(skb->data, DP_RX_BUFFER_ALIGN_SIZE) -
			 skb->data);
	पूर्ण

	paddr = dma_map_single(ab->dev, skb->data,
			       skb->len + skb_tailroom(skb),
			       DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(ab->dev, paddr)))
		जाओ fail_मुक्त_skb;

	spin_lock_bh(&rx_ring->idr_lock);
	*buf_id = idr_alloc(&rx_ring->bufs_idr, skb, 0,
			    rx_ring->bufs_max, GFP_ATOMIC);
	spin_unlock_bh(&rx_ring->idr_lock);
	अगर (*buf_id < 0)
		जाओ fail_dma_unmap;

	ATH11K_SKB_RXCB(skb)->paddr = paddr;
	वापस skb;

fail_dma_unmap:
	dma_unmap_single(ab->dev, paddr, skb->len + skb_tailroom(skb),
			 DMA_FROM_DEVICE);
fail_मुक्त_skb:
	dev_kमुक्त_skb_any(skb);
fail_alloc_skb:
	वापस शून्य;
पूर्ण

पूर्णांक ath11k_dp_rx_mon_status_bufs_replenish(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
					   काष्ठा dp_rxdma_ring *rx_ring,
					   पूर्णांक req_entries,
					   क्रमागत hal_rx_buf_वापस_buf_manager mgr)
अणु
	काष्ठा hal_srng *srng;
	u32 *desc;
	काष्ठा sk_buff *skb;
	पूर्णांक num_मुक्त;
	पूर्णांक num_reमुख्य;
	पूर्णांक buf_id;
	u32 cookie;
	dma_addr_t paddr;

	req_entries = min(req_entries, rx_ring->bufs_max);

	srng = &ab->hal.srng_list[rx_ring->refill_buf_ring.ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	num_मुक्त = ath11k_hal_srng_src_num_मुक्त(ab, srng, true);

	req_entries = min(num_मुक्त, req_entries);
	num_reमुख्य = req_entries;

	जबतक (num_reमुख्य > 0) अणु
		skb = ath11k_dp_rx_alloc_mon_status_buf(ab, rx_ring,
							&buf_id);
		अगर (!skb)
			अवरोध;
		paddr = ATH11K_SKB_RXCB(skb)->paddr;

		desc = ath11k_hal_srng_src_get_next_entry(ab, srng);
		अगर (!desc)
			जाओ fail_desc_get;

		cookie = FIELD_PREP(DP_RXDMA_BUF_COOKIE_PDEV_ID, mac_id) |
			 FIELD_PREP(DP_RXDMA_BUF_COOKIE_BUF_ID, buf_id);

		num_reमुख्य--;

		ath11k_hal_rx_buf_addr_info_set(desc, paddr, cookie, mgr);
	पूर्ण

	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	वापस req_entries - num_reमुख्य;

fail_desc_get:
	spin_lock_bh(&rx_ring->idr_lock);
	idr_हटाओ(&rx_ring->bufs_idr, buf_id);
	spin_unlock_bh(&rx_ring->idr_lock);
	dma_unmap_single(ab->dev, paddr, skb->len + skb_tailroom(skb),
			 DMA_FROM_DEVICE);
	dev_kमुक्त_skb_any(skb);
	ath11k_hal_srng_access_end(ab, srng);
	spin_unlock_bh(&srng->lock);

	वापस req_entries - num_reमुख्य;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_reap_mon_status_ring(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
					     पूर्णांक *budget, काष्ठा sk_buff_head *skb_list)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev_dp *dp;
	काष्ठा dp_rxdma_ring *rx_ring;
	काष्ठा hal_srng *srng;
	व्योम *rx_mon_status_desc;
	काष्ठा sk_buff *skb;
	काष्ठा ath11k_skb_rxcb *rxcb;
	काष्ठा hal_tlv_hdr *tlv;
	u32 cookie;
	पूर्णांक buf_id, srng_id;
	dma_addr_t paddr;
	u8 rbm;
	पूर्णांक num_buffs_reaped = 0;

	ar = ab->pdevs[ath11k_hw_mac_id_to_pdev_id(&ab->hw_params, mac_id)].ar;
	dp = &ar->dp;
	srng_id = ath11k_hw_mac_id_to_srng_id(&ab->hw_params, mac_id);
	rx_ring = &dp->rx_mon_status_refill_ring[srng_id];

	srng = &ab->hal.srng_list[rx_ring->refill_buf_ring.ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);
	जबतक (*budget) अणु
		*budget -= 1;
		rx_mon_status_desc =
			ath11k_hal_srng_src_peek(ab, srng);
		अगर (!rx_mon_status_desc)
			अवरोध;

		ath11k_hal_rx_buf_addr_info_get(rx_mon_status_desc, &paddr,
						&cookie, &rbm);
		अगर (paddr) अणु
			buf_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_BUF_ID, cookie);

			spin_lock_bh(&rx_ring->idr_lock);
			skb = idr_find(&rx_ring->bufs_idr, buf_id);
			अगर (!skb) अणु
				ath11k_warn(ab, "rx monitor status with invalid buf_id %d\n",
					    buf_id);
				spin_unlock_bh(&rx_ring->idr_lock);
				जाओ move_next;
			पूर्ण

			idr_हटाओ(&rx_ring->bufs_idr, buf_id);
			spin_unlock_bh(&rx_ring->idr_lock);

			rxcb = ATH11K_SKB_RXCB(skb);

			dma_unmap_single(ab->dev, rxcb->paddr,
					 skb->len + skb_tailroom(skb),
					 DMA_FROM_DEVICE);

			tlv = (काष्ठा hal_tlv_hdr *)skb->data;
			अगर (FIELD_GET(HAL_TLV_HDR_TAG, tlv->tl) !=
					HAL_RX_STATUS_BUFFER_DONE) अणु
				ath11k_warn(ab, "mon status DONE not set %lx\n",
					    FIELD_GET(HAL_TLV_HDR_TAG,
						      tlv->tl));
				dev_kमुक्त_skb_any(skb);
				जाओ move_next;
			पूर्ण

			__skb_queue_tail(skb_list, skb);
		पूर्ण
move_next:
		skb = ath11k_dp_rx_alloc_mon_status_buf(ab, rx_ring,
							&buf_id);

		अगर (!skb) अणु
			ath11k_hal_rx_buf_addr_info_set(rx_mon_status_desc, 0, 0,
							HAL_RX_BUF_RBM_SW3_BM);
			num_buffs_reaped++;
			अवरोध;
		पूर्ण
		rxcb = ATH11K_SKB_RXCB(skb);

		cookie = FIELD_PREP(DP_RXDMA_BUF_COOKIE_PDEV_ID, mac_id) |
			 FIELD_PREP(DP_RXDMA_BUF_COOKIE_BUF_ID, buf_id);

		ath11k_hal_rx_buf_addr_info_set(rx_mon_status_desc, rxcb->paddr,
						cookie, HAL_RX_BUF_RBM_SW3_BM);
		ath11k_hal_srng_src_get_next_entry(ab, srng);
		num_buffs_reaped++;
	पूर्ण
	ath11k_hal_srng_access_end(ab, srng);
	spin_unlock_bh(&srng->lock);

	वापस num_buffs_reaped;
पूर्ण

पूर्णांक ath11k_dp_rx_process_mon_status(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
				    काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ath11k *ar = ath11k_ab_to_ar(ab, mac_id);
	क्रमागत hal_rx_mon_status hal_status;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head skb_list;
	काष्ठा hal_rx_mon_ppdu_info ppdu_info;
	काष्ठा ath11k_peer *peer;
	काष्ठा ath11k_sta *arsta;
	पूर्णांक num_buffs_reaped = 0;

	__skb_queue_head_init(&skb_list);

	num_buffs_reaped = ath11k_dp_rx_reap_mon_status_ring(ab, mac_id, &budget,
							     &skb_list);
	अगर (!num_buffs_reaped)
		जाओ निकास;

	जबतक ((skb = __skb_dequeue(&skb_list))) अणु
		स_रखो(&ppdu_info, 0, माप(ppdu_info));
		ppdu_info.peer_id = HAL_INVALID_PEERID;

		अगर (ath11k_debugfs_is_pktlog_rx_stats_enabled(ar))
			trace_ath11k_htt_rxdesc(ar, skb->data, DP_RX_BUFFER_SIZE);

		hal_status = ath11k_hal_rx_parse_mon_status(ab, &ppdu_info, skb);

		अगर (ppdu_info.peer_id == HAL_INVALID_PEERID ||
		    hal_status != HAL_RX_MON_STATUS_PPDU_DONE) अणु
			dev_kमुक्त_skb_any(skb);
			जारी;
		पूर्ण

		rcu_पढ़ो_lock();
		spin_lock_bh(&ab->base_lock);
		peer = ath11k_peer_find_by_id(ab, ppdu_info.peer_id);

		अगर (!peer || !peer->sta) अणु
			ath11k_dbg(ab, ATH11K_DBG_DATA,
				   "failed to find the peer with peer_id %d\n",
				   ppdu_info.peer_id);
			spin_unlock_bh(&ab->base_lock);
			rcu_पढ़ो_unlock();
			dev_kमुक्त_skb_any(skb);
			जारी;
		पूर्ण

		arsta = (काष्ठा ath11k_sta *)peer->sta->drv_priv;
		ath11k_dp_rx_update_peer_stats(arsta, &ppdu_info);

		अगर (ath11k_debugfs_is_pktlog_peer_valid(ar, peer->addr))
			trace_ath11k_htt_rxdesc(ar, skb->data, DP_RX_BUFFER_SIZE);

		spin_unlock_bh(&ab->base_lock);
		rcu_पढ़ो_unlock();

		dev_kमुक्त_skb_any(skb);
	पूर्ण
निकास:
	वापस num_buffs_reaped;
पूर्ण

अटल व्योम ath11k_dp_rx_frag_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा dp_rx_tid *rx_tid = from_समयr(rx_tid, समयr, frag_समयr);

	spin_lock_bh(&rx_tid->ab->base_lock);
	अगर (rx_tid->last_frag_no &&
	    rx_tid->rx_frag_biपंचांगap == GENMASK(rx_tid->last_frag_no, 0)) अणु
		spin_unlock_bh(&rx_tid->ab->base_lock);
		वापस;
	पूर्ण
	ath11k_dp_rx_frags_cleanup(rx_tid, true);
	spin_unlock_bh(&rx_tid->ab->base_lock);
पूर्ण

पूर्णांक ath11k_peer_rx_frag_setup(काष्ठा ath11k *ar, स्थिर u8 *peer_mac, पूर्णांक vdev_id)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा crypto_shash *tfm;
	काष्ठा ath11k_peer *peer;
	काष्ठा dp_rx_tid *rx_tid;
	पूर्णांक i;

	tfm = crypto_alloc_shash("michael_mic", 0, 0);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find(ab, vdev_id, peer_mac);
	अगर (!peer) अणु
		ath11k_warn(ab, "failed to find the peer to set up fragment info\n");
		spin_unlock_bh(&ab->base_lock);
		वापस -ENOENT;
	पूर्ण

	क्रम (i = 0; i <= IEEE80211_NUM_TIDS; i++) अणु
		rx_tid = &peer->rx_tid[i];
		rx_tid->ab = ab;
		समयr_setup(&rx_tid->frag_समयr, ath11k_dp_rx_frag_समयr, 0);
		skb_queue_head_init(&rx_tid->rx_frags);
	पूर्ण

	peer->tfm_mmic = tfm;
	spin_unlock_bh(&ab->base_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_h_michael_mic(काष्ठा crypto_shash *tfm, u8 *key,
				      काष्ठा ieee80211_hdr *hdr, u8 *data,
				      माप_प्रकार data_len, u8 *mic)
अणु
	SHASH_DESC_ON_STACK(desc, tfm);
	u8 mic_hdr[16] = अणु0पूर्ण;
	u8 tid = 0;
	पूर्णांक ret;

	अगर (!tfm)
		वापस -EINVAL;

	desc->tfm = tfm;

	ret = crypto_shash_setkey(tfm, key, 8);
	अगर (ret)
		जाओ out;

	ret = crypto_shash_init(desc);
	अगर (ret)
		जाओ out;

	/* TKIP MIC header */
	स_नकल(mic_hdr, ieee80211_get_DA(hdr), ETH_ALEN);
	स_नकल(mic_hdr + ETH_ALEN, ieee80211_get_SA(hdr), ETH_ALEN);
	अगर (ieee80211_is_data_qos(hdr->frame_control))
		tid = ieee80211_get_tid(hdr);
	mic_hdr[12] = tid;

	ret = crypto_shash_update(desc, mic_hdr, 16);
	अगर (ret)
		जाओ out;
	ret = crypto_shash_update(desc, data, data_len);
	अगर (ret)
		जाओ out;
	ret = crypto_shash_final(desc, mic);
out:
	shash_desc_zero(desc);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_h_verअगरy_tkip_mic(काष्ठा ath11k *ar, काष्ठा ath11k_peer *peer,
					  काष्ठा sk_buff *msdu)
अणु
	काष्ठा hal_rx_desc *rx_desc = (काष्ठा hal_rx_desc *)msdu->data;
	काष्ठा ieee80211_rx_status *rxs = IEEE80211_SKB_RXCB(msdu);
	काष्ठा ieee80211_key_conf *key_conf;
	काष्ठा ieee80211_hdr *hdr;
	u8 mic[IEEE80211_CCMP_MIC_LEN];
	पूर्णांक head_len, tail_len, ret;
	माप_प्रकार data_len;
	u32 hdr_len, hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;
	u8 *key, *data;
	u8 key_idx;

	अगर (ath11k_dp_rx_h_mpdu_start_enctype(ar->ab, rx_desc) !=
	    HAL_ENCRYPT_TYPE_TKIP_MIC)
		वापस 0;

	hdr = (काष्ठा ieee80211_hdr *)(msdu->data + hal_rx_desc_sz);
	hdr_len = ieee80211_hdrlen(hdr->frame_control);
	head_len = hdr_len + hal_rx_desc_sz + IEEE80211_TKIP_IV_LEN;
	tail_len = IEEE80211_CCMP_MIC_LEN + IEEE80211_TKIP_ICV_LEN + FCS_LEN;

	अगर (!is_multicast_ether_addr(hdr->addr1))
		key_idx = peer->ucast_keyidx;
	अन्यथा
		key_idx = peer->mcast_keyidx;

	key_conf = peer->keys[key_idx];

	data = msdu->data + head_len;
	data_len = msdu->len - head_len - tail_len;
	key = &key_conf->key[NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY];

	ret = ath11k_dp_rx_h_michael_mic(peer->tfm_mmic, key, hdr, data, data_len, mic);
	अगर (ret || स_भेद(mic, data + data_len, IEEE80211_CCMP_MIC_LEN))
		जाओ mic_fail;

	वापस 0;

mic_fail:
	(ATH11K_SKB_RXCB(msdu))->is_first_msdu = true;
	(ATH11K_SKB_RXCB(msdu))->is_last_msdu = true;

	rxs->flag |= RX_FLAG_MMIC_ERROR | RX_FLAG_MMIC_STRIPPED |
		    RX_FLAG_IV_STRIPPED | RX_FLAG_DECRYPTED;
	skb_pull(msdu, hal_rx_desc_sz);

	ath11k_dp_rx_h_ppdu(ar, rx_desc, rxs);
	ath11k_dp_rx_h_undecap(ar, msdu, rx_desc,
			       HAL_ENCRYPT_TYPE_TKIP_MIC, rxs, true);
	ieee80211_rx(ar->hw, msdu);
	वापस -EINVAL;
पूर्ण

अटल व्योम ath11k_dp_rx_h_undecap_frag(काष्ठा ath11k *ar, काष्ठा sk_buff *msdu,
					क्रमागत hal_encrypt_type enctype, u32 flags)
अणु
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdr_len;
	माप_प्रकार crypto_len;
	u32 hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;

	अगर (!flags)
		वापस;

	hdr = (काष्ठा ieee80211_hdr *)(msdu->data + hal_rx_desc_sz);

	अगर (flags & RX_FLAG_MIC_STRIPPED)
		skb_trim(msdu, msdu->len -
			 ath11k_dp_rx_crypto_mic_len(ar, enctype));

	अगर (flags & RX_FLAG_ICV_STRIPPED)
		skb_trim(msdu, msdu->len -
			 ath11k_dp_rx_crypto_icv_len(ar, enctype));

	अगर (flags & RX_FLAG_IV_STRIPPED) अणु
		hdr_len = ieee80211_hdrlen(hdr->frame_control);
		crypto_len = ath11k_dp_rx_crypto_param_len(ar, enctype);

		स_हटाओ((व्योम *)msdu->data + hal_rx_desc_sz + crypto_len,
			(व्योम *)msdu->data + hal_rx_desc_sz, hdr_len);
		skb_pull(msdu, crypto_len);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_dp_rx_h_defrag(काष्ठा ath11k *ar,
				 काष्ठा ath11k_peer *peer,
				 काष्ठा dp_rx_tid *rx_tid,
				 काष्ठा sk_buff **defrag_skb)
अणु
	काष्ठा hal_rx_desc *rx_desc;
	काष्ठा sk_buff *skb, *first_frag, *last_frag;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा rx_attention *rx_attention;
	क्रमागत hal_encrypt_type enctype;
	bool is_decrypted = false;
	पूर्णांक msdu_len = 0;
	पूर्णांक extra_space;
	u32 flags, hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;

	first_frag = skb_peek(&rx_tid->rx_frags);
	last_frag = skb_peek_tail(&rx_tid->rx_frags);

	skb_queue_walk(&rx_tid->rx_frags, skb) अणु
		flags = 0;
		rx_desc = (काष्ठा hal_rx_desc *)skb->data;
		hdr = (काष्ठा ieee80211_hdr *)(skb->data + hal_rx_desc_sz);

		enctype = ath11k_dp_rx_h_mpdu_start_enctype(ar->ab, rx_desc);
		अगर (enctype != HAL_ENCRYPT_TYPE_OPEN) अणु
			rx_attention = ath11k_dp_rx_get_attention(ar->ab, rx_desc);
			is_decrypted = ath11k_dp_rx_h_attn_is_decrypted(rx_attention);
		पूर्ण

		अगर (is_decrypted) अणु
			अगर (skb != first_frag)
				flags |=  RX_FLAG_IV_STRIPPED;
			अगर (skb != last_frag)
				flags |= RX_FLAG_ICV_STRIPPED |
					 RX_FLAG_MIC_STRIPPED;
		पूर्ण

		/* RX fragments are always raw packets */
		अगर (skb != last_frag)
			skb_trim(skb, skb->len - FCS_LEN);
		ath11k_dp_rx_h_undecap_frag(ar, skb, enctype, flags);

		अगर (skb != first_frag)
			skb_pull(skb, hal_rx_desc_sz +
				      ieee80211_hdrlen(hdr->frame_control));
		msdu_len += skb->len;
	पूर्ण

	extra_space = msdu_len - (DP_RX_BUFFER_SIZE + skb_tailroom(first_frag));
	अगर (extra_space > 0 &&
	    (pskb_expand_head(first_frag, 0, extra_space, GFP_ATOMIC) < 0))
		वापस -ENOMEM;

	__skb_unlink(first_frag, &rx_tid->rx_frags);
	जबतक ((skb = __skb_dequeue(&rx_tid->rx_frags))) अणु
		skb_put_data(first_frag, skb->data, skb->len);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *)(first_frag->data + hal_rx_desc_sz);
	hdr->frame_control &= ~__cpu_to_le16(IEEE80211_FCTL_MOREFRAGS);
	ATH11K_SKB_RXCB(first_frag)->is_frag = 1;

	अगर (ath11k_dp_rx_h_verअगरy_tkip_mic(ar, peer, first_frag))
		first_frag = शून्य;

	*defrag_skb = first_frag;
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_h_defrag_reo_reinject(काष्ठा ath11k *ar, काष्ठा dp_rx_tid *rx_tid,
					      काष्ठा sk_buff *defrag_skb)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा dp_rxdma_ring *rx_refill_ring = &dp->rx_refill_buf_ring;
	काष्ठा hal_rx_desc *rx_desc = (काष्ठा hal_rx_desc *)defrag_skb->data;
	काष्ठा hal_reo_entrance_ring *reo_ent_ring;
	काष्ठा hal_reo_dest_ring *reo_dest_ring;
	काष्ठा dp_link_desc_bank *link_desc_banks;
	काष्ठा hal_rx_msdu_link *msdu_link;
	काष्ठा hal_rx_msdu_details *msdu0;
	काष्ठा hal_srng *srng;
	dma_addr_t paddr;
	u32 desc_bank, msdu_info, mpdu_info;
	u32 dst_idx, cookie, hal_rx_desc_sz;
	पूर्णांक ret, buf_id;

	hal_rx_desc_sz = ab->hw_params.hal_desc_sz;
	link_desc_banks = ab->dp.link_desc_banks;
	reo_dest_ring = rx_tid->dst_ring_desc;

	ath11k_hal_rx_reo_ent_paddr_get(ab, reo_dest_ring, &paddr, &desc_bank);
	msdu_link = (काष्ठा hal_rx_msdu_link *)(link_desc_banks[desc_bank].vaddr +
			(paddr - link_desc_banks[desc_bank].paddr));
	msdu0 = &msdu_link->msdu_link[0];
	dst_idx = FIELD_GET(RX_MSDU_DESC_INFO0_REO_DEST_IND, msdu0->rx_msdu_info.info0);
	स_रखो(msdu0, 0, माप(*msdu0));

	msdu_info = FIELD_PREP(RX_MSDU_DESC_INFO0_FIRST_MSDU_IN_MPDU, 1) |
		    FIELD_PREP(RX_MSDU_DESC_INFO0_LAST_MSDU_IN_MPDU, 1) |
		    FIELD_PREP(RX_MSDU_DESC_INFO0_MSDU_CONTINUATION, 0) |
		    FIELD_PREP(RX_MSDU_DESC_INFO0_MSDU_LENGTH,
			       defrag_skb->len - hal_rx_desc_sz) |
		    FIELD_PREP(RX_MSDU_DESC_INFO0_REO_DEST_IND, dst_idx) |
		    FIELD_PREP(RX_MSDU_DESC_INFO0_VALID_SA, 1) |
		    FIELD_PREP(RX_MSDU_DESC_INFO0_VALID_DA, 1);
	msdu0->rx_msdu_info.info0 = msdu_info;

	/* change msdu len in hal rx desc */
	ath11k_dp_rxdesc_set_msdu_len(ab, rx_desc, defrag_skb->len - hal_rx_desc_sz);

	paddr = dma_map_single(ab->dev, defrag_skb->data,
			       defrag_skb->len + skb_tailroom(defrag_skb),
			       DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ab->dev, paddr))
		वापस -ENOMEM;

	spin_lock_bh(&rx_refill_ring->idr_lock);
	buf_id = idr_alloc(&rx_refill_ring->bufs_idr, defrag_skb, 0,
			   rx_refill_ring->bufs_max * 3, GFP_ATOMIC);
	spin_unlock_bh(&rx_refill_ring->idr_lock);
	अगर (buf_id < 0) अणु
		ret = -ENOMEM;
		जाओ err_unmap_dma;
	पूर्ण

	ATH11K_SKB_RXCB(defrag_skb)->paddr = paddr;
	cookie = FIELD_PREP(DP_RXDMA_BUF_COOKIE_PDEV_ID, dp->mac_id) |
		 FIELD_PREP(DP_RXDMA_BUF_COOKIE_BUF_ID, buf_id);

	ath11k_hal_rx_buf_addr_info_set(msdu0, paddr, cookie, HAL_RX_BUF_RBM_SW3_BM);

	/* Fill mpdu details पूर्णांकo reo entrace ring */
	srng = &ab->hal.srng_list[ab->dp.reo_reinject_ring.ring_id];

	spin_lock_bh(&srng->lock);
	ath11k_hal_srng_access_begin(ab, srng);

	reo_ent_ring = (काष्ठा hal_reo_entrance_ring *)
			ath11k_hal_srng_src_get_next_entry(ab, srng);
	अगर (!reo_ent_ring) अणु
		ath11k_hal_srng_access_end(ab, srng);
		spin_unlock_bh(&srng->lock);
		ret = -ENOSPC;
		जाओ err_मुक्त_idr;
	पूर्ण
	स_रखो(reo_ent_ring, 0, माप(*reo_ent_ring));

	ath11k_hal_rx_reo_ent_paddr_get(ab, reo_dest_ring, &paddr, &desc_bank);
	ath11k_hal_rx_buf_addr_info_set(reo_ent_ring, paddr, desc_bank,
					HAL_RX_BUF_RBM_WBM_IDLE_DESC_LIST);

	mpdu_info = FIELD_PREP(RX_MPDU_DESC_INFO0_MSDU_COUNT, 1) |
		    FIELD_PREP(RX_MPDU_DESC_INFO0_SEQ_NUM, rx_tid->cur_sn) |
		    FIELD_PREP(RX_MPDU_DESC_INFO0_FRAG_FLAG, 0) |
		    FIELD_PREP(RX_MPDU_DESC_INFO0_VALID_SA, 1) |
		    FIELD_PREP(RX_MPDU_DESC_INFO0_VALID_DA, 1) |
		    FIELD_PREP(RX_MPDU_DESC_INFO0_RAW_MPDU, 1) |
		    FIELD_PREP(RX_MPDU_DESC_INFO0_VALID_PN, 1);

	reo_ent_ring->rx_mpdu_info.info0 = mpdu_info;
	reo_ent_ring->rx_mpdu_info.meta_data = reo_dest_ring->rx_mpdu_info.meta_data;
	reo_ent_ring->queue_addr_lo = reo_dest_ring->queue_addr_lo;
	reo_ent_ring->info0 = FIELD_PREP(HAL_REO_ENTR_RING_INFO0_QUEUE_ADDR_HI,
					 FIELD_GET(HAL_REO_DEST_RING_INFO0_QUEUE_ADDR_HI,
						   reo_dest_ring->info0)) |
			      FIELD_PREP(HAL_REO_ENTR_RING_INFO0_DEST_IND, dst_idx);
	ath11k_hal_srng_access_end(ab, srng);
	spin_unlock_bh(&srng->lock);

	वापस 0;

err_मुक्त_idr:
	spin_lock_bh(&rx_refill_ring->idr_lock);
	idr_हटाओ(&rx_refill_ring->bufs_idr, buf_id);
	spin_unlock_bh(&rx_refill_ring->idr_lock);
err_unmap_dma:
	dma_unmap_single(ab->dev, paddr, defrag_skb->len + skb_tailroom(defrag_skb),
			 DMA_FROM_DEVICE);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_h_cmp_frags(काष्ठा ath11k *ar,
				    काष्ठा sk_buff *a, काष्ठा sk_buff *b)
अणु
	पूर्णांक frag1, frag2;

	frag1 = ath11k_dp_rx_h_mpdu_start_frag_no(ar->ab, a);
	frag2 = ath11k_dp_rx_h_mpdu_start_frag_no(ar->ab, b);

	वापस frag1 - frag2;
पूर्ण

अटल व्योम ath11k_dp_rx_h_sort_frags(काष्ठा ath11k *ar,
				      काष्ठा sk_buff_head *frag_list,
				      काष्ठा sk_buff *cur_frag)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक cmp;

	skb_queue_walk(frag_list, skb) अणु
		cmp = ath11k_dp_rx_h_cmp_frags(ar, skb, cur_frag);
		अगर (cmp < 0)
			जारी;
		__skb_queue_beक्रमe(frag_list, skb, cur_frag);
		वापस;
	पूर्ण
	__skb_queue_tail(frag_list, cur_frag);
पूर्ण

अटल u64 ath11k_dp_rx_h_get_pn(काष्ठा ath11k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	u64 pn = 0;
	u8 *ehdr;
	u32 hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + hal_rx_desc_sz);
	ehdr = skb->data + hal_rx_desc_sz + ieee80211_hdrlen(hdr->frame_control);

	pn = ehdr[0];
	pn |= (u64)ehdr[1] << 8;
	pn |= (u64)ehdr[4] << 16;
	pn |= (u64)ehdr[5] << 24;
	pn |= (u64)ehdr[6] << 32;
	pn |= (u64)ehdr[7] << 40;

	वापस pn;
पूर्ण

अटल bool
ath11k_dp_rx_h_defrag_validate_incr_pn(काष्ठा ath11k *ar, काष्ठा dp_rx_tid *rx_tid)
अणु
	क्रमागत hal_encrypt_type encrypt_type;
	काष्ठा sk_buff *first_frag, *skb;
	काष्ठा hal_rx_desc *desc;
	u64 last_pn;
	u64 cur_pn;

	first_frag = skb_peek(&rx_tid->rx_frags);
	desc = (काष्ठा hal_rx_desc *)first_frag->data;

	encrypt_type = ath11k_dp_rx_h_mpdu_start_enctype(ar->ab, desc);
	अगर (encrypt_type != HAL_ENCRYPT_TYPE_CCMP_128 &&
	    encrypt_type != HAL_ENCRYPT_TYPE_CCMP_256 &&
	    encrypt_type != HAL_ENCRYPT_TYPE_GCMP_128 &&
	    encrypt_type != HAL_ENCRYPT_TYPE_AES_GCMP_256)
		वापस true;

	last_pn = ath11k_dp_rx_h_get_pn(ar, first_frag);
	skb_queue_walk(&rx_tid->rx_frags, skb) अणु
		अगर (skb == first_frag)
			जारी;

		cur_pn = ath11k_dp_rx_h_get_pn(ar, skb);
		अगर (cur_pn != last_pn + 1)
			वापस false;
		last_pn = cur_pn;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_frag_h_mpdu(काष्ठा ath11k *ar,
				    काष्ठा sk_buff *msdu,
				    u32 *ring_desc)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा hal_rx_desc *rx_desc;
	काष्ठा ath11k_peer *peer;
	काष्ठा dp_rx_tid *rx_tid;
	काष्ठा sk_buff *defrag_skb = शून्य;
	u32 peer_id;
	u16 seqno, frag_no;
	u8 tid;
	पूर्णांक ret = 0;
	bool more_frags;
	bool is_mcbc;

	rx_desc = (काष्ठा hal_rx_desc *)msdu->data;
	peer_id = ath11k_dp_rx_h_mpdu_start_peer_id(ar->ab, rx_desc);
	tid = ath11k_dp_rx_h_mpdu_start_tid(ar->ab, rx_desc);
	seqno = ath11k_dp_rx_h_mpdu_start_seq_no(ar->ab, rx_desc);
	frag_no = ath11k_dp_rx_h_mpdu_start_frag_no(ar->ab, msdu);
	more_frags = ath11k_dp_rx_h_mpdu_start_more_frags(ar->ab, msdu);
	is_mcbc = ath11k_dp_rx_h_attn_is_mcbc(ar->ab, rx_desc);

	/* Multicast/Broadcast fragments are not expected */
	अगर (is_mcbc)
		वापस -EINVAL;

	अगर (!ath11k_dp_rx_h_mpdu_start_seq_ctrl_valid(ar->ab, rx_desc) ||
	    !ath11k_dp_rx_h_mpdu_start_fc_valid(ar->ab, rx_desc) ||
	    tid > IEEE80211_NUM_TIDS)
		वापस -EINVAL;

	/* received unfragmented packet in reo
	 * exception ring, this shouldn't happen
	 * as these packets typically come from
	 * reo2sw srngs.
	 */
	अगर (WARN_ON_ONCE(!frag_no && !more_frags))
		वापस -EINVAL;

	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find_by_id(ab, peer_id);
	अगर (!peer) अणु
		ath11k_warn(ab, "failed to find the peer to de-fragment received fragment peer_id %d\n",
			    peer_id);
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण
	rx_tid = &peer->rx_tid[tid];

	अगर ((!skb_queue_empty(&rx_tid->rx_frags) && seqno != rx_tid->cur_sn) ||
	    skb_queue_empty(&rx_tid->rx_frags)) अणु
		/* Flush stored fragments and start a new sequence */
		ath11k_dp_rx_frags_cleanup(rx_tid, true);
		rx_tid->cur_sn = seqno;
	पूर्ण

	अगर (rx_tid->rx_frag_biपंचांगap & BIT(frag_no)) अणु
		/* Fragment alपढ़ोy present */
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (frag_no > __fls(rx_tid->rx_frag_biपंचांगap))
		__skb_queue_tail(&rx_tid->rx_frags, msdu);
	अन्यथा
		ath11k_dp_rx_h_sort_frags(ar, &rx_tid->rx_frags, msdu);

	rx_tid->rx_frag_biपंचांगap |= BIT(frag_no);
	अगर (!more_frags)
		rx_tid->last_frag_no = frag_no;

	अगर (frag_no == 0) अणु
		rx_tid->dst_ring_desc = kmemdup(ring_desc,
						माप(*rx_tid->dst_ring_desc),
						GFP_ATOMIC);
		अगर (!rx_tid->dst_ring_desc) अणु
			ret = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		ath11k_dp_rx_link_desc_वापस(ab, ring_desc,
					      HAL_WBM_REL_BM_ACT_PUT_IN_IDLE);
	पूर्ण

	अगर (!rx_tid->last_frag_no ||
	    rx_tid->rx_frag_biपंचांगap != GENMASK(rx_tid->last_frag_no, 0)) अणु
		mod_समयr(&rx_tid->frag_समयr, jअगरfies +
					       ATH11K_DP_RX_FRAGMENT_TIMEOUT_MS);
		जाओ out_unlock;
	पूर्ण

	spin_unlock_bh(&ab->base_lock);
	del_समयr_sync(&rx_tid->frag_समयr);
	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find_by_id(ab, peer_id);
	अगर (!peer)
		जाओ err_frags_cleanup;

	अगर (!ath11k_dp_rx_h_defrag_validate_incr_pn(ar, rx_tid))
		जाओ err_frags_cleanup;

	अगर (ath11k_dp_rx_h_defrag(ar, peer, rx_tid, &defrag_skb))
		जाओ err_frags_cleanup;

	अगर (!defrag_skb)
		जाओ err_frags_cleanup;

	अगर (ath11k_dp_rx_h_defrag_reo_reinject(ar, rx_tid, defrag_skb))
		जाओ err_frags_cleanup;

	ath11k_dp_rx_frags_cleanup(rx_tid, false);
	जाओ out_unlock;

err_frags_cleanup:
	dev_kमुक्त_skb_any(defrag_skb);
	ath11k_dp_rx_frags_cleanup(rx_tid, true);
out_unlock:
	spin_unlock_bh(&ab->base_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक
ath11k_dp_process_rx_err_buf(काष्ठा ath11k *ar, u32 *ring_desc, पूर्णांक buf_id, bool drop)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा dp_rxdma_ring *rx_ring = &dp->rx_refill_buf_ring;
	काष्ठा sk_buff *msdu;
	काष्ठा ath11k_skb_rxcb *rxcb;
	काष्ठा hal_rx_desc *rx_desc;
	u8 *hdr_status;
	u16 msdu_len;
	u32 hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;

	spin_lock_bh(&rx_ring->idr_lock);
	msdu = idr_find(&rx_ring->bufs_idr, buf_id);
	अगर (!msdu) अणु
		ath11k_warn(ar->ab, "rx err buf with invalid buf_id %d\n",
			    buf_id);
		spin_unlock_bh(&rx_ring->idr_lock);
		वापस -EINVAL;
	पूर्ण

	idr_हटाओ(&rx_ring->bufs_idr, buf_id);
	spin_unlock_bh(&rx_ring->idr_lock);

	rxcb = ATH11K_SKB_RXCB(msdu);
	dma_unmap_single(ar->ab->dev, rxcb->paddr,
			 msdu->len + skb_tailroom(msdu),
			 DMA_FROM_DEVICE);

	अगर (drop) अणु
		dev_kमुक्त_skb_any(msdu);
		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();
	अगर (!rcu_dereference(ar->ab->pdevs_active[ar->pdev_idx])) अणु
		dev_kमुक्त_skb_any(msdu);
		जाओ निकास;
	पूर्ण

	अगर (test_bit(ATH11K_CAC_RUNNING, &ar->dev_flags)) अणु
		dev_kमुक्त_skb_any(msdu);
		जाओ निकास;
	पूर्ण

	rx_desc = (काष्ठा hal_rx_desc *)msdu->data;
	msdu_len = ath11k_dp_rx_h_msdu_start_msdu_len(ar->ab, rx_desc);
	अगर ((msdu_len + hal_rx_desc_sz) > DP_RX_BUFFER_SIZE) अणु
		hdr_status = ath11k_dp_rx_h_80211_hdr(ar->ab, rx_desc);
		ath11k_warn(ar->ab, "invalid msdu leng %u", msdu_len);
		ath11k_dbg_dump(ar->ab, ATH11K_DBG_DATA, शून्य, "", hdr_status,
				माप(काष्ठा ieee80211_hdr));
		ath11k_dbg_dump(ar->ab, ATH11K_DBG_DATA, शून्य, "", rx_desc,
				माप(काष्ठा hal_rx_desc));
		dev_kमुक्त_skb_any(msdu);
		जाओ निकास;
	पूर्ण

	skb_put(msdu, hal_rx_desc_sz + msdu_len);

	अगर (ath11k_dp_rx_frag_h_mpdu(ar, msdu, ring_desc)) अणु
		dev_kमुक्त_skb_any(msdu);
		ath11k_dp_rx_link_desc_वापस(ar->ab, ring_desc,
					      HAL_WBM_REL_BM_ACT_PUT_IN_IDLE);
	पूर्ण
निकास:
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_process_rx_err(काष्ठा ath11k_base *ab, काष्ठा napi_काष्ठा *napi,
			     पूर्णांक budget)
अणु
	u32 msdu_cookies[HAL_NUM_RX_MSDUS_PER_LINK_DESC];
	काष्ठा dp_link_desc_bank *link_desc_banks;
	क्रमागत hal_rx_buf_वापस_buf_manager rbm;
	पूर्णांक tot_n_bufs_reaped, quota, ret, i;
	पूर्णांक n_bufs_reaped[MAX_RADIOS] = अणु0पूर्ण;
	काष्ठा dp_rxdma_ring *rx_ring;
	काष्ठा dp_srng *reo_except;
	u32 desc_bank, num_msdus;
	काष्ठा hal_srng *srng;
	काष्ठा ath11k_dp *dp;
	व्योम *link_desc_va;
	पूर्णांक buf_id, mac_id;
	काष्ठा ath11k *ar;
	dma_addr_t paddr;
	u32 *desc;
	bool is_frag;
	u8 drop = 0;

	tot_n_bufs_reaped = 0;
	quota = budget;

	dp = &ab->dp;
	reo_except = &dp->reo_except_ring;
	link_desc_banks = dp->link_desc_banks;

	srng = &ab->hal.srng_list[reo_except->ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	जबतक (budget &&
	       (desc = ath11k_hal_srng_dst_get_next_entry(ab, srng))) अणु
		काष्ठा hal_reo_dest_ring *reo_desc = (काष्ठा hal_reo_dest_ring *)desc;

		ab->soc_stats.err_ring_pkts++;
		ret = ath11k_hal_desc_reo_parse_err(ab, desc, &paddr,
						    &desc_bank);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to parse error reo desc %d\n",
				    ret);
			जारी;
		पूर्ण
		link_desc_va = link_desc_banks[desc_bank].vaddr +
			       (paddr - link_desc_banks[desc_bank].paddr);
		ath11k_hal_rx_msdu_link_info_get(link_desc_va, &num_msdus, msdu_cookies,
						 &rbm);
		अगर (rbm != HAL_RX_BUF_RBM_WBM_IDLE_DESC_LIST &&
		    rbm != HAL_RX_BUF_RBM_SW3_BM) अणु
			ab->soc_stats.invalid_rbm++;
			ath11k_warn(ab, "invalid return buffer manager %d\n", rbm);
			ath11k_dp_rx_link_desc_वापस(ab, desc,
						      HAL_WBM_REL_BM_ACT_REL_MSDU);
			जारी;
		पूर्ण

		is_frag = !!(reo_desc->rx_mpdu_info.info0 & RX_MPDU_DESC_INFO0_FRAG_FLAG);

		/* Process only rx fragments with one msdu per link desc below, and drop
		 * msdu's indicated due to error reasons.
		 */
		अगर (!is_frag || num_msdus > 1) अणु
			drop = 1;
			/* Return the link desc back to wbm idle list */
			ath11k_dp_rx_link_desc_वापस(ab, desc,
						      HAL_WBM_REL_BM_ACT_PUT_IN_IDLE);
		पूर्ण

		क्रम (i = 0; i < num_msdus; i++) अणु
			buf_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_BUF_ID,
					   msdu_cookies[i]);

			mac_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_PDEV_ID,
					   msdu_cookies[i]);

			ar = ab->pdevs[mac_id].ar;

			अगर (!ath11k_dp_process_rx_err_buf(ar, desc, buf_id, drop)) अणु
				n_bufs_reaped[mac_id]++;
				tot_n_bufs_reaped++;
			पूर्ण
		पूर्ण

		अगर (tot_n_bufs_reaped >= quota) अणु
			tot_n_bufs_reaped = quota;
			जाओ निकास;
		पूर्ण

		budget = quota - tot_n_bufs_reaped;
	पूर्ण

निकास:
	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	क्रम (i = 0; i <  ab->num_radios; i++) अणु
		अगर (!n_bufs_reaped[i])
			जारी;

		ar = ab->pdevs[i].ar;
		rx_ring = &ar->dp.rx_refill_buf_ring;

		ath11k_dp_rxbufs_replenish(ab, i, rx_ring, n_bufs_reaped[i],
					   HAL_RX_BUF_RBM_SW3_BM);
	पूर्ण

	वापस tot_n_bufs_reaped;
पूर्ण

अटल व्योम ath11k_dp_rx_null_q_desc_sg_drop(काष्ठा ath11k *ar,
					     पूर्णांक msdu_len,
					     काष्ठा sk_buff_head *msdu_list)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;
	काष्ठा ath11k_skb_rxcb *rxcb;
	पूर्णांक n_buffs;

	n_buffs = DIV_ROUND_UP(msdu_len,
			       (DP_RX_BUFFER_SIZE - ar->ab->hw_params.hal_desc_sz));

	skb_queue_walk_safe(msdu_list, skb, पंचांगp) अणु
		rxcb = ATH11K_SKB_RXCB(skb);
		अगर (rxcb->err_rel_src == HAL_WBM_REL_SRC_MODULE_REO &&
		    rxcb->err_code == HAL_REO_DEST_RING_ERROR_CODE_DESC_ADDR_ZERO) अणु
			अगर (!n_buffs)
				अवरोध;
			__skb_unlink(skb, msdu_list);
			dev_kमुक्त_skb_any(skb);
			n_buffs--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_dp_rx_h_null_q_desc(काष्ठा ath11k *ar, काष्ठा sk_buff *msdu,
				      काष्ठा ieee80211_rx_status *status,
				      काष्ठा sk_buff_head *msdu_list)
अणु
	u16 msdu_len;
	काष्ठा hal_rx_desc *desc = (काष्ठा hal_rx_desc *)msdu->data;
	काष्ठा rx_attention *rx_attention;
	u8 l3pad_bytes;
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	u32 hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;

	msdu_len = ath11k_dp_rx_h_msdu_start_msdu_len(ar->ab, desc);

	अगर (!rxcb->is_frag && ((msdu_len + hal_rx_desc_sz) > DP_RX_BUFFER_SIZE)) अणु
		/* First buffer will be मुक्तd by the caller, so deduct it's length */
		msdu_len = msdu_len - (DP_RX_BUFFER_SIZE - hal_rx_desc_sz);
		ath11k_dp_rx_null_q_desc_sg_drop(ar, msdu_len, msdu_list);
		वापस -EINVAL;
	पूर्ण

	rx_attention = ath11k_dp_rx_get_attention(ar->ab, desc);
	अगर (!ath11k_dp_rx_h_attn_msdu_करोne(rx_attention)) अणु
		ath11k_warn(ar->ab,
			    "msdu_done bit not set in null_q_des processing\n");
		__skb_queue_purge(msdu_list);
		वापस -EIO;
	पूर्ण

	/* Handle शून्य queue descriptor violations arising out a missing
	 * REO queue क्रम a given peer or a given TID. This typically
	 * may happen अगर a packet is received on a QOS enabled TID beक्रमe the
	 * ADDBA negotiation क्रम that TID, when the TID queue is setup. Or
	 * it may also happen क्रम MC/BC frames अगर they are not routed to the
	 * non-QOS TID queue, in the असलence of any other शेष TID queue.
	 * This error can show up both in a REO destination or WBM release ring.
	 */

	rxcb->is_first_msdu = ath11k_dp_rx_h_msdu_end_first_msdu(ar->ab, desc);
	rxcb->is_last_msdu = ath11k_dp_rx_h_msdu_end_last_msdu(ar->ab, desc);

	अगर (rxcb->is_frag) अणु
		skb_pull(msdu, hal_rx_desc_sz);
	पूर्ण अन्यथा अणु
		l3pad_bytes = ath11k_dp_rx_h_msdu_end_l3pad(ar->ab, desc);

		अगर ((hal_rx_desc_sz + l3pad_bytes + msdu_len) > DP_RX_BUFFER_SIZE)
			वापस -EINVAL;

		skb_put(msdu, hal_rx_desc_sz + l3pad_bytes + msdu_len);
		skb_pull(msdu, hal_rx_desc_sz + l3pad_bytes);
	पूर्ण
	ath11k_dp_rx_h_ppdu(ar, desc, status);

	ath11k_dp_rx_h_mpdu(ar, msdu, desc, status);

	rxcb->tid = ath11k_dp_rx_h_mpdu_start_tid(ar->ab, desc);

	/* Please note that caller will having the access to msdu and completing
	 * rx with mac80211. Need not worry about cleaning up amsdu_list.
	 */

	वापस 0;
पूर्ण

अटल bool ath11k_dp_rx_h_reo_err(काष्ठा ath11k *ar, काष्ठा sk_buff *msdu,
				   काष्ठा ieee80211_rx_status *status,
				   काष्ठा sk_buff_head *msdu_list)
अणु
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	bool drop = false;

	ar->ab->soc_stats.reo_error[rxcb->err_code]++;

	चयन (rxcb->err_code) अणु
	हाल HAL_REO_DEST_RING_ERROR_CODE_DESC_ADDR_ZERO:
		अगर (ath11k_dp_rx_h_null_q_desc(ar, msdu, status, msdu_list))
			drop = true;
		अवरोध;
	हाल HAL_REO_DEST_RING_ERROR_CODE_PN_CHECK_FAILED:
		/* TODO: Do not drop PN failed packets in the driver;
		 * instead, it is good to drop such packets in mac80211
		 * after incrementing the replay counters.
		 */
		fallthrough;
	शेष:
		/* TODO: Review other errors and process them to mac80211
		 * as appropriate.
		 */
		drop = true;
		अवरोध;
	पूर्ण

	वापस drop;
पूर्ण

अटल व्योम ath11k_dp_rx_h_tkip_mic_err(काष्ठा ath11k *ar, काष्ठा sk_buff *msdu,
					काष्ठा ieee80211_rx_status *status)
अणु
	u16 msdu_len;
	काष्ठा hal_rx_desc *desc = (काष्ठा hal_rx_desc *)msdu->data;
	u8 l3pad_bytes;
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	u32 hal_rx_desc_sz = ar->ab->hw_params.hal_desc_sz;

	rxcb->is_first_msdu = ath11k_dp_rx_h_msdu_end_first_msdu(ar->ab, desc);
	rxcb->is_last_msdu = ath11k_dp_rx_h_msdu_end_last_msdu(ar->ab, desc);

	l3pad_bytes = ath11k_dp_rx_h_msdu_end_l3pad(ar->ab, desc);
	msdu_len = ath11k_dp_rx_h_msdu_start_msdu_len(ar->ab, desc);
	skb_put(msdu, hal_rx_desc_sz + l3pad_bytes + msdu_len);
	skb_pull(msdu, hal_rx_desc_sz + l3pad_bytes);

	ath11k_dp_rx_h_ppdu(ar, desc, status);

	status->flag |= (RX_FLAG_MMIC_STRIPPED | RX_FLAG_MMIC_ERROR |
			 RX_FLAG_DECRYPTED);

	ath11k_dp_rx_h_undecap(ar, msdu, desc,
			       HAL_ENCRYPT_TYPE_TKIP_MIC, status, false);
पूर्ण

अटल bool ath11k_dp_rx_h_rxdma_err(काष्ठा ath11k *ar,  काष्ठा sk_buff *msdu,
				     काष्ठा ieee80211_rx_status *status)
अणु
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	bool drop = false;

	ar->ab->soc_stats.rxdma_error[rxcb->err_code]++;

	चयन (rxcb->err_code) अणु
	हाल HAL_REO_ENTR_RING_RXDMA_ECODE_TKIP_MIC_ERR:
		ath11k_dp_rx_h_tkip_mic_err(ar, msdu, status);
		अवरोध;
	शेष:
		/* TODO: Review other rxdma error code to check अगर anything is
		 * worth reporting to mac80211
		 */
		drop = true;
		अवरोध;
	पूर्ण

	वापस drop;
पूर्ण

अटल व्योम ath11k_dp_rx_wbm_err(काष्ठा ath11k *ar,
				 काष्ठा napi_काष्ठा *napi,
				 काष्ठा sk_buff *msdu,
				 काष्ठा sk_buff_head *msdu_list)
अणु
	काष्ठा ath11k_skb_rxcb *rxcb = ATH11K_SKB_RXCB(msdu);
	काष्ठा ieee80211_rx_status rxs = अणु0पूर्ण;
	काष्ठा ieee80211_rx_status *status;
	bool drop = true;

	चयन (rxcb->err_rel_src) अणु
	हाल HAL_WBM_REL_SRC_MODULE_REO:
		drop = ath11k_dp_rx_h_reo_err(ar, msdu, &rxs, msdu_list);
		अवरोध;
	हाल HAL_WBM_REL_SRC_MODULE_RXDMA:
		drop = ath11k_dp_rx_h_rxdma_err(ar, msdu, &rxs);
		अवरोध;
	शेष:
		/* msdu will get मुक्तd */
		अवरोध;
	पूर्ण

	अगर (drop) अणु
		dev_kमुक्त_skb_any(msdu);
		वापस;
	पूर्ण

	status = IEEE80211_SKB_RXCB(msdu);
	*status = rxs;

	ath11k_dp_rx_deliver_msdu(ar, napi, msdu);
पूर्ण

पूर्णांक ath11k_dp_rx_process_wbm_err(काष्ठा ath11k_base *ab,
				 काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा dp_rxdma_ring *rx_ring;
	काष्ठा hal_rx_wbm_rel_info err_info;
	काष्ठा hal_srng *srng;
	काष्ठा sk_buff *msdu;
	काष्ठा sk_buff_head msdu_list[MAX_RADIOS];
	काष्ठा ath11k_skb_rxcb *rxcb;
	u32 *rx_desc;
	पूर्णांक buf_id, mac_id;
	पूर्णांक num_buffs_reaped[MAX_RADIOS] = अणु0पूर्ण;
	पूर्णांक total_num_buffs_reaped = 0;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ab->num_radios; i++)
		__skb_queue_head_init(&msdu_list[i]);

	srng = &ab->hal.srng_list[dp->rx_rel_ring.ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	जबतक (budget) अणु
		rx_desc = ath11k_hal_srng_dst_get_next_entry(ab, srng);
		अगर (!rx_desc)
			अवरोध;

		ret = ath11k_hal_wbm_desc_parse_err(ab, rx_desc, &err_info);
		अगर (ret) अणु
			ath11k_warn(ab,
				    "failed to parse rx error in wbm_rel ring desc %d\n",
				    ret);
			जारी;
		पूर्ण

		buf_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_BUF_ID, err_info.cookie);
		mac_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_PDEV_ID, err_info.cookie);

		ar = ab->pdevs[mac_id].ar;
		rx_ring = &ar->dp.rx_refill_buf_ring;

		spin_lock_bh(&rx_ring->idr_lock);
		msdu = idr_find(&rx_ring->bufs_idr, buf_id);
		अगर (!msdu) अणु
			ath11k_warn(ab, "frame rx with invalid buf_id %d pdev %d\n",
				    buf_id, mac_id);
			spin_unlock_bh(&rx_ring->idr_lock);
			जारी;
		पूर्ण

		idr_हटाओ(&rx_ring->bufs_idr, buf_id);
		spin_unlock_bh(&rx_ring->idr_lock);

		rxcb = ATH11K_SKB_RXCB(msdu);
		dma_unmap_single(ab->dev, rxcb->paddr,
				 msdu->len + skb_tailroom(msdu),
				 DMA_FROM_DEVICE);

		num_buffs_reaped[mac_id]++;
		total_num_buffs_reaped++;
		budget--;

		अगर (err_info.push_reason !=
		    HAL_REO_DEST_RING_PUSH_REASON_ERR_DETECTED) अणु
			dev_kमुक्त_skb_any(msdu);
			जारी;
		पूर्ण

		rxcb->err_rel_src = err_info.err_rel_src;
		rxcb->err_code = err_info.err_code;
		rxcb->rx_desc = (काष्ठा hal_rx_desc *)msdu->data;
		__skb_queue_tail(&msdu_list[mac_id], msdu);
	पूर्ण

	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	अगर (!total_num_buffs_reaped)
		जाओ करोne;

	क्रम (i = 0; i <  ab->num_radios; i++) अणु
		अगर (!num_buffs_reaped[i])
			जारी;

		ar = ab->pdevs[i].ar;
		rx_ring = &ar->dp.rx_refill_buf_ring;

		ath11k_dp_rxbufs_replenish(ab, i, rx_ring, num_buffs_reaped[i],
					   HAL_RX_BUF_RBM_SW3_BM);
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (i = 0; i <  ab->num_radios; i++) अणु
		अगर (!rcu_dereference(ab->pdevs_active[i])) अणु
			__skb_queue_purge(&msdu_list[i]);
			जारी;
		पूर्ण

		ar = ab->pdevs[i].ar;

		अगर (test_bit(ATH11K_CAC_RUNNING, &ar->dev_flags)) अणु
			__skb_queue_purge(&msdu_list[i]);
			जारी;
		पूर्ण

		जबतक ((msdu = __skb_dequeue(&msdu_list[i])) != शून्य)
			ath11k_dp_rx_wbm_err(ar, napi, msdu, &msdu_list[i]);
	पूर्ण
	rcu_पढ़ो_unlock();
करोne:
	वापस total_num_buffs_reaped;
पूर्ण

पूर्णांक ath11k_dp_process_rxdma_err(काष्ठा ath11k_base *ab, पूर्णांक mac_id, पूर्णांक budget)
अणु
	काष्ठा ath11k *ar;
	काष्ठा dp_srng *err_ring;
	काष्ठा dp_rxdma_ring *rx_ring;
	काष्ठा dp_link_desc_bank *link_desc_banks = ab->dp.link_desc_banks;
	काष्ठा hal_srng *srng;
	u32 msdu_cookies[HAL_NUM_RX_MSDUS_PER_LINK_DESC];
	क्रमागत hal_rx_buf_वापस_buf_manager rbm;
	क्रमागत hal_reo_entr_rxdma_ecode rxdma_err_code;
	काष्ठा ath11k_skb_rxcb *rxcb;
	काष्ठा sk_buff *skb;
	काष्ठा hal_reo_entrance_ring *entr_ring;
	व्योम *desc;
	पूर्णांक num_buf_मुक्तd = 0;
	पूर्णांक quota = budget;
	dma_addr_t paddr;
	u32 desc_bank;
	व्योम *link_desc_va;
	पूर्णांक num_msdus;
	पूर्णांक i;
	पूर्णांक buf_id;

	ar = ab->pdevs[ath11k_hw_mac_id_to_pdev_id(&ab->hw_params, mac_id)].ar;
	err_ring = &ar->dp.rxdma_err_dst_ring[ath11k_hw_mac_id_to_srng_id(&ab->hw_params,
									  mac_id)];
	rx_ring = &ar->dp.rx_refill_buf_ring;

	srng = &ab->hal.srng_list[err_ring->ring_id];

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	जबतक (quota-- &&
	       (desc = ath11k_hal_srng_dst_get_next_entry(ab, srng))) अणु
		ath11k_hal_rx_reo_ent_paddr_get(ab, desc, &paddr, &desc_bank);

		entr_ring = (काष्ठा hal_reo_entrance_ring *)desc;
		rxdma_err_code =
			FIELD_GET(HAL_REO_ENTR_RING_INFO1_RXDMA_ERROR_CODE,
				  entr_ring->info1);
		ab->soc_stats.rxdma_error[rxdma_err_code]++;

		link_desc_va = link_desc_banks[desc_bank].vaddr +
			       (paddr - link_desc_banks[desc_bank].paddr);
		ath11k_hal_rx_msdu_link_info_get(link_desc_va, &num_msdus,
						 msdu_cookies, &rbm);

		क्रम (i = 0; i < num_msdus; i++) अणु
			buf_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_BUF_ID,
					   msdu_cookies[i]);

			spin_lock_bh(&rx_ring->idr_lock);
			skb = idr_find(&rx_ring->bufs_idr, buf_id);
			अगर (!skb) अणु
				ath11k_warn(ab, "rxdma error with invalid buf_id %d\n",
					    buf_id);
				spin_unlock_bh(&rx_ring->idr_lock);
				जारी;
			पूर्ण

			idr_हटाओ(&rx_ring->bufs_idr, buf_id);
			spin_unlock_bh(&rx_ring->idr_lock);

			rxcb = ATH11K_SKB_RXCB(skb);
			dma_unmap_single(ab->dev, rxcb->paddr,
					 skb->len + skb_tailroom(skb),
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);

			num_buf_मुक्तd++;
		पूर्ण

		ath11k_dp_rx_link_desc_वापस(ab, desc,
					      HAL_WBM_REL_BM_ACT_PUT_IN_IDLE);
	पूर्ण

	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	अगर (num_buf_मुक्तd)
		ath11k_dp_rxbufs_replenish(ab, mac_id, rx_ring, num_buf_मुक्तd,
					   HAL_RX_BUF_RBM_SW3_BM);

	वापस budget - quota;
पूर्ण

व्योम ath11k_dp_process_reo_status(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा hal_srng *srng;
	काष्ठा dp_reo_cmd *cmd, *पंचांगp;
	bool found = false;
	u32 *reo_desc;
	u16 tag;
	काष्ठा hal_reo_status reo_status;

	srng = &ab->hal.srng_list[dp->reo_status_ring.ring_id];

	स_रखो(&reo_status, 0, माप(reo_status));

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	जबतक ((reo_desc = ath11k_hal_srng_dst_get_next_entry(ab, srng))) अणु
		tag = FIELD_GET(HAL_SRNG_TLV_HDR_TAG, *reo_desc);

		चयन (tag) अणु
		हाल HAL_REO_GET_QUEUE_STATS_STATUS:
			ath11k_hal_reo_status_queue_stats(ab, reo_desc,
							  &reo_status);
			अवरोध;
		हाल HAL_REO_FLUSH_QUEUE_STATUS:
			ath11k_hal_reo_flush_queue_status(ab, reo_desc,
							  &reo_status);
			अवरोध;
		हाल HAL_REO_FLUSH_CACHE_STATUS:
			ath11k_hal_reo_flush_cache_status(ab, reo_desc,
							  &reo_status);
			अवरोध;
		हाल HAL_REO_UNBLOCK_CACHE_STATUS:
			ath11k_hal_reo_unblk_cache_status(ab, reo_desc,
							  &reo_status);
			अवरोध;
		हाल HAL_REO_FLUSH_TIMEOUT_LIST_STATUS:
			ath11k_hal_reo_flush_समयout_list_status(ab, reo_desc,
								 &reo_status);
			अवरोध;
		हाल HAL_REO_DESCRIPTOR_THRESHOLD_REACHED_STATUS:
			ath11k_hal_reo_desc_thresh_reached_status(ab, reo_desc,
								  &reo_status);
			अवरोध;
		हाल HAL_REO_UPDATE_RX_REO_QUEUE_STATUS:
			ath11k_hal_reo_update_rx_reo_queue_status(ab, reo_desc,
								  &reo_status);
			अवरोध;
		शेष:
			ath11k_warn(ab, "Unknown reo status type %d\n", tag);
			जारी;
		पूर्ण

		spin_lock_bh(&dp->reo_cmd_lock);
		list_क्रम_each_entry_safe(cmd, पंचांगp, &dp->reo_cmd_list, list) अणु
			अगर (reo_status.unअगरorm_hdr.cmd_num == cmd->cmd_num) अणु
				found = true;
				list_del(&cmd->list);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&dp->reo_cmd_lock);

		अगर (found) अणु
			cmd->handler(dp, (व्योम *)&cmd->data,
				     reo_status.unअगरorm_hdr.cmd_status);
			kमुक्त(cmd);
		पूर्ण

		found = false;
	पूर्ण

	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);
पूर्ण

व्योम ath11k_dp_rx_pdev_मुक्त(काष्ठा ath11k_base *ab, पूर्णांक mac_id)
अणु
	काष्ठा ath11k *ar = ab->pdevs[mac_id].ar;

	ath11k_dp_rx_pdev_srng_मुक्त(ar);
	ath11k_dp_rxdma_pdev_buf_मुक्त(ar);
पूर्ण

पूर्णांक ath11k_dp_rx_pdev_alloc(काष्ठा ath11k_base *ab, पूर्णांक mac_id)
अणु
	काष्ठा ath11k *ar = ab->pdevs[mac_id].ar;
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	u32 ring_id;
	पूर्णांक i;
	पूर्णांक ret;

	ret = ath11k_dp_rx_pdev_srng_alloc(ar);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to setup rx srngs\n");
		वापस ret;
	पूर्ण

	ret = ath11k_dp_rxdma_pdev_buf_setup(ar);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to setup rxdma ring\n");
		वापस ret;
	पूर्ण

	ring_id = dp->rx_refill_buf_ring.refill_buf_ring.ring_id;
	ret = ath11k_dp_tx_htt_srng_setup(ab, ring_id, mac_id, HAL_RXDMA_BUF);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to configure rx_refill_buf_ring %d\n",
			    ret);
		वापस ret;
	पूर्ण

	अगर (ab->hw_params.rx_mac_buf_ring) अणु
		क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
			ring_id = dp->rx_mac_buf_ring[i].ring_id;
			ret = ath11k_dp_tx_htt_srng_setup(ab, ring_id,
							  mac_id + i, HAL_RXDMA_BUF);
			अगर (ret) अणु
				ath11k_warn(ab, "failed to configure rx_mac_buf_ring%d %d\n",
					    i, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		ring_id = dp->rxdma_err_dst_ring[i].ring_id;
		ret = ath11k_dp_tx_htt_srng_setup(ab, ring_id,
						  mac_id + i, HAL_RXDMA_DST);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to configure rxdma_err_dest_ring%d %d\n",
				    i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!ab->hw_params.rxdma1_enable)
		जाओ config_refill_ring;

	ring_id = dp->rxdma_mon_buf_ring.refill_buf_ring.ring_id;
	ret = ath11k_dp_tx_htt_srng_setup(ab, ring_id,
					  mac_id, HAL_RXDMA_MONITOR_BUF);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to configure rxdma_mon_buf_ring %d\n",
			    ret);
		वापस ret;
	पूर्ण
	ret = ath11k_dp_tx_htt_srng_setup(ab,
					  dp->rxdma_mon_dst_ring.ring_id,
					  mac_id, HAL_RXDMA_MONITOR_DST);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to configure rxdma_mon_dst_ring %d\n",
			    ret);
		वापस ret;
	पूर्ण
	ret = ath11k_dp_tx_htt_srng_setup(ab,
					  dp->rxdma_mon_desc_ring.ring_id,
					  mac_id, HAL_RXDMA_MONITOR_DESC);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to configure rxdma_mon_dst_ring %d\n",
			    ret);
		वापस ret;
	पूर्ण

config_refill_ring:
	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		ring_id = dp->rx_mon_status_refill_ring[i].refill_buf_ring.ring_id;
		ret = ath11k_dp_tx_htt_srng_setup(ab, ring_id, mac_id + i,
						  HAL_RXDMA_MONITOR_STATUS);
		अगर (ret) अणु
			ath11k_warn(ab,
				    "failed to configure mon_status_refill_ring%d %d\n",
				    i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath11k_dp_mon_set_frag_len(u32 *total_len, u32 *frag_len)
अणु
	अगर (*total_len >= (DP_RX_BUFFER_SIZE - माप(काष्ठा hal_rx_desc))) अणु
		*frag_len = DP_RX_BUFFER_SIZE - माप(काष्ठा hal_rx_desc);
		*total_len -= *frag_len;
	पूर्ण अन्यथा अणु
		*frag_len = *total_len;
		*total_len = 0;
	पूर्ण
पूर्ण

अटल
पूर्णांक ath11k_dp_rx_monitor_link_desc_वापस(काष्ठा ath11k *ar,
					  व्योम *p_last_buf_addr_info,
					  u8 mac_id)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा dp_srng *dp_srng;
	व्योम *hal_srng;
	व्योम *src_srng_desc;
	पूर्णांक ret = 0;

	अगर (ar->ab->hw_params.rxdma1_enable) अणु
		dp_srng = &dp->rxdma_mon_desc_ring;
		hal_srng = &ar->ab->hal.srng_list[dp_srng->ring_id];
	पूर्ण अन्यथा अणु
		dp_srng = &ar->ab->dp.wbm_desc_rel_ring;
		hal_srng = &ar->ab->hal.srng_list[dp_srng->ring_id];
	पूर्ण

	ath11k_hal_srng_access_begin(ar->ab, hal_srng);

	src_srng_desc = ath11k_hal_srng_src_get_next_entry(ar->ab, hal_srng);

	अगर (src_srng_desc) अणु
		काष्ठा ath11k_buffer_addr *src_desc =
				(काष्ठा ath11k_buffer_addr *)src_srng_desc;

		*src_desc = *((काष्ठा ath11k_buffer_addr *)p_last_buf_addr_info);
	पूर्ण अन्यथा अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_DATA,
			   "Monitor Link Desc Ring %d Full", mac_id);
		ret = -ENOMEM;
	पूर्ण

	ath11k_hal_srng_access_end(ar->ab, hal_srng);
	वापस ret;
पूर्ण

अटल
व्योम ath11k_dp_rx_mon_next_link_desc_get(व्योम *rx_msdu_link_desc,
					 dma_addr_t *paddr, u32 *sw_cookie,
					 u8 *rbm,
					 व्योम **pp_buf_addr_info)
अणु
	काष्ठा hal_rx_msdu_link *msdu_link =
			(काष्ठा hal_rx_msdu_link *)rx_msdu_link_desc;
	काष्ठा ath11k_buffer_addr *buf_addr_info;

	buf_addr_info = (काष्ठा ath11k_buffer_addr *)&msdu_link->buf_addr_info;

	ath11k_hal_rx_buf_addr_info_get(buf_addr_info, paddr, sw_cookie, rbm);

	*pp_buf_addr_info = (व्योम *)buf_addr_info;
पूर्ण

अटल पूर्णांक ath11k_dp_pkt_set_pktlen(काष्ठा sk_buff *skb, u32 len)
अणु
	अगर (skb->len > len) अणु
		skb_trim(skb, len);
	पूर्ण अन्यथा अणु
		अगर (skb_tailroom(skb) < len - skb->len) अणु
			अगर ((pskb_expand_head(skb, 0,
					      len - skb->len - skb_tailroom(skb),
					      GFP_ATOMIC))) अणु
				dev_kमुक्त_skb_any(skb);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		skb_put(skb, (len - skb->len));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ath11k_hal_rx_msdu_list_get(काष्ठा ath11k *ar,
					व्योम *msdu_link_desc,
					काष्ठा hal_rx_msdu_list *msdu_list,
					u16 *num_msdus)
अणु
	काष्ठा hal_rx_msdu_details *msdu_details = शून्य;
	काष्ठा rx_msdu_desc *msdu_desc_info = शून्य;
	काष्ठा hal_rx_msdu_link *msdu_link = शून्य;
	पूर्णांक i;
	u32 last = FIELD_PREP(RX_MSDU_DESC_INFO0_LAST_MSDU_IN_MPDU, 1);
	u32 first = FIELD_PREP(RX_MSDU_DESC_INFO0_FIRST_MSDU_IN_MPDU, 1);
	u8  पंचांगp  = 0;

	msdu_link = (काष्ठा hal_rx_msdu_link *)msdu_link_desc;
	msdu_details = &msdu_link->msdu_link[0];

	क्रम (i = 0; i < HAL_RX_NUM_MSDU_DESC; i++) अणु
		अगर (FIELD_GET(BUFFER_ADDR_INFO0_ADDR,
			      msdu_details[i].buf_addr_info.info0) == 0) अणु
			msdu_desc_info = &msdu_details[i - 1].rx_msdu_info;
			msdu_desc_info->info0 |= last;
			;
			अवरोध;
		पूर्ण
		msdu_desc_info = &msdu_details[i].rx_msdu_info;

		अगर (!i)
			msdu_desc_info->info0 |= first;
		अन्यथा अगर (i == (HAL_RX_NUM_MSDU_DESC - 1))
			msdu_desc_info->info0 |= last;
		msdu_list->msdu_info[i].msdu_flags = msdu_desc_info->info0;
		msdu_list->msdu_info[i].msdu_len =
			 HAL_RX_MSDU_PKT_LENGTH_GET(msdu_desc_info->info0);
		msdu_list->sw_cookie[i] =
			FIELD_GET(BUFFER_ADDR_INFO1_SW_COOKIE,
				  msdu_details[i].buf_addr_info.info1);
		पंचांगp = FIELD_GET(BUFFER_ADDR_INFO1_RET_BUF_MGR,
				msdu_details[i].buf_addr_info.info1);
		msdu_list->rbm[i] = पंचांगp;
	पूर्ण
	*num_msdus = i;
पूर्ण

अटल u32 ath11k_dp_rx_mon_comp_ppduid(u32 msdu_ppdu_id, u32 *ppdu_id,
					u32 *rx_bufs_used)
अणु
	u32 ret = 0;

	अगर ((*ppdu_id < msdu_ppdu_id) &&
	    ((msdu_ppdu_id - *ppdu_id) < DP_NOT_PPDU_ID_WRAP_AROUND)) अणु
		*ppdu_id = msdu_ppdu_id;
		ret = msdu_ppdu_id;
	पूर्ण अन्यथा अगर ((*ppdu_id > msdu_ppdu_id) &&
		((*ppdu_id - msdu_ppdu_id) > DP_NOT_PPDU_ID_WRAP_AROUND)) अणु
		/* mon_dst is behind than mon_status
		 * skip dst_ring and मुक्त it
		 */
		*rx_bufs_used += 1;
		*ppdu_id = msdu_ppdu_id;
		ret = msdu_ppdu_id;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ath11k_dp_mon_get_buf_len(काष्ठा hal_rx_msdu_desc_info *info,
				      bool *is_frag, u32 *total_len,
				      u32 *frag_len, u32 *msdu_cnt)
अणु
	अगर (info->msdu_flags & RX_MSDU_DESC_INFO0_MSDU_CONTINUATION) अणु
		अगर (!*is_frag) अणु
			*total_len = info->msdu_len;
			*is_frag = true;
		पूर्ण
		ath11k_dp_mon_set_frag_len(total_len,
					   frag_len);
	पूर्ण अन्यथा अणु
		अगर (*is_frag) अणु
			ath11k_dp_mon_set_frag_len(total_len,
						   frag_len);
		पूर्ण अन्यथा अणु
			*frag_len = info->msdu_len;
		पूर्ण
		*is_frag = false;
		*msdu_cnt -= 1;
	पूर्ण
पूर्ण

अटल u32
ath11k_dp_rx_mon_mpdu_pop(काष्ठा ath11k *ar, पूर्णांक mac_id,
			  व्योम *ring_entry, काष्ठा sk_buff **head_msdu,
			  काष्ठा sk_buff **tail_msdu, u32 *npackets,
			  u32 *ppdu_id)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_mon_data *pmon = (काष्ठा ath11k_mon_data *)&dp->mon_data;
	काष्ठा dp_rxdma_ring *rx_ring = &dp->rxdma_mon_buf_ring;
	काष्ठा sk_buff *msdu = शून्य, *last = शून्य;
	काष्ठा hal_rx_msdu_list msdu_list;
	व्योम *p_buf_addr_info, *p_last_buf_addr_info;
	काष्ठा hal_rx_desc *rx_desc;
	व्योम *rx_msdu_link_desc;
	dma_addr_t paddr;
	u16 num_msdus = 0;
	u32 rx_buf_size, rx_pkt_offset, sw_cookie;
	u32 rx_bufs_used = 0, i = 0;
	u32 msdu_ppdu_id = 0, msdu_cnt = 0;
	u32 total_len = 0, frag_len = 0;
	bool is_frag, is_first_msdu;
	bool drop_mpdu = false;
	काष्ठा ath11k_skb_rxcb *rxcb;
	काष्ठा hal_reo_entrance_ring *ent_desc =
			(काष्ठा hal_reo_entrance_ring *)ring_entry;
	पूर्णांक buf_id;
	u32 rx_link_buf_info[2];
	u8 rbm;

	अगर (!ar->ab->hw_params.rxdma1_enable)
		rx_ring = &dp->rx_refill_buf_ring;

	ath11k_hal_rx_reo_ent_buf_paddr_get(ring_entry, &paddr,
					    &sw_cookie,
					    &p_last_buf_addr_info, &rbm,
					    &msdu_cnt);

	अगर (FIELD_GET(HAL_REO_ENTR_RING_INFO1_RXDMA_PUSH_REASON,
		      ent_desc->info1) ==
		      HAL_REO_DEST_RING_PUSH_REASON_ERR_DETECTED) अणु
		u8 rxdma_err =
			FIELD_GET(HAL_REO_ENTR_RING_INFO1_RXDMA_ERROR_CODE,
				  ent_desc->info1);
		अगर (rxdma_err == HAL_REO_ENTR_RING_RXDMA_ECODE_FLUSH_REQUEST_ERR ||
		    rxdma_err == HAL_REO_ENTR_RING_RXDMA_ECODE_MPDU_LEN_ERR ||
		    rxdma_err == HAL_REO_ENTR_RING_RXDMA_ECODE_OVERFLOW_ERR) अणु
			drop_mpdu = true;
			pmon->rx_mon_stats.dest_mpdu_drop++;
		पूर्ण
	पूर्ण

	is_frag = false;
	is_first_msdu = true;

	करो अणु
		अगर (pmon->mon_last_linkdesc_paddr == paddr) अणु
			pmon->rx_mon_stats.dup_mon_linkdesc_cnt++;
			वापस rx_bufs_used;
		पूर्ण

		अगर (ar->ab->hw_params.rxdma1_enable)
			rx_msdu_link_desc =
				(व्योम *)pmon->link_desc_banks[sw_cookie].vaddr +
				(paddr - pmon->link_desc_banks[sw_cookie].paddr);
		अन्यथा
			rx_msdu_link_desc =
				(व्योम *)ar->ab->dp.link_desc_banks[sw_cookie].vaddr +
				(paddr - ar->ab->dp.link_desc_banks[sw_cookie].paddr);

		ath11k_hal_rx_msdu_list_get(ar, rx_msdu_link_desc, &msdu_list,
					    &num_msdus);

		क्रम (i = 0; i < num_msdus; i++) अणु
			u32 l2_hdr_offset;

			अगर (pmon->mon_last_buf_cookie == msdu_list.sw_cookie[i]) अणु
				ath11k_dbg(ar->ab, ATH11K_DBG_DATA,
					   "i %d last_cookie %d is same\n",
					   i, pmon->mon_last_buf_cookie);
				drop_mpdu = true;
				pmon->rx_mon_stats.dup_mon_buf_cnt++;
				जारी;
			पूर्ण
			buf_id = FIELD_GET(DP_RXDMA_BUF_COOKIE_BUF_ID,
					   msdu_list.sw_cookie[i]);

			spin_lock_bh(&rx_ring->idr_lock);
			msdu = idr_find(&rx_ring->bufs_idr, buf_id);
			spin_unlock_bh(&rx_ring->idr_lock);
			अगर (!msdu) अणु
				ath11k_dbg(ar->ab, ATH11K_DBG_DATA,
					   "msdu_pop: invalid buf_id %d\n", buf_id);
				अवरोध;
			पूर्ण
			rxcb = ATH11K_SKB_RXCB(msdu);
			अगर (!rxcb->unmapped) अणु
				dma_unmap_single(ar->ab->dev, rxcb->paddr,
						 msdu->len +
						 skb_tailroom(msdu),
						 DMA_FROM_DEVICE);
				rxcb->unmapped = 1;
			पूर्ण
			अगर (drop_mpdu) अणु
				ath11k_dbg(ar->ab, ATH11K_DBG_DATA,
					   "i %d drop msdu %p *ppdu_id %x\n",
					   i, msdu, *ppdu_id);
				dev_kमुक्त_skb_any(msdu);
				msdu = शून्य;
				जाओ next_msdu;
			पूर्ण

			rx_desc = (काष्ठा hal_rx_desc *)msdu->data;

			rx_pkt_offset = माप(काष्ठा hal_rx_desc);
			l2_hdr_offset = ath11k_dp_rx_h_msdu_end_l3pad(ar->ab, rx_desc);

			अगर (is_first_msdu) अणु
				अगर (!ath11k_dp_rxdesc_mpdu_valid(ar->ab, rx_desc)) अणु
					drop_mpdu = true;
					dev_kमुक्त_skb_any(msdu);
					msdu = शून्य;
					pmon->mon_last_linkdesc_paddr = paddr;
					जाओ next_msdu;
				पूर्ण

				msdu_ppdu_id =
					ath11k_dp_rxdesc_get_ppduid(ar->ab, rx_desc);

				अगर (ath11k_dp_rx_mon_comp_ppduid(msdu_ppdu_id,
								 ppdu_id,
								 &rx_bufs_used)) अणु
					अगर (rx_bufs_used) अणु
						drop_mpdu = true;
						dev_kमुक्त_skb_any(msdu);
						msdu = शून्य;
						जाओ next_msdu;
					पूर्ण
					वापस rx_bufs_used;
				पूर्ण
				pmon->mon_last_linkdesc_paddr = paddr;
				is_first_msdu = false;
			पूर्ण
			ath11k_dp_mon_get_buf_len(&msdu_list.msdu_info[i],
						  &is_frag, &total_len,
						  &frag_len, &msdu_cnt);
			rx_buf_size = rx_pkt_offset + l2_hdr_offset + frag_len;

			ath11k_dp_pkt_set_pktlen(msdu, rx_buf_size);

			अगर (!(*head_msdu))
				*head_msdu = msdu;
			अन्यथा अगर (last)
				last->next = msdu;

			last = msdu;
next_msdu:
			pmon->mon_last_buf_cookie = msdu_list.sw_cookie[i];
			rx_bufs_used++;
			spin_lock_bh(&rx_ring->idr_lock);
			idr_हटाओ(&rx_ring->bufs_idr, buf_id);
			spin_unlock_bh(&rx_ring->idr_lock);
		पूर्ण

		ath11k_hal_rx_buf_addr_info_set(rx_link_buf_info, paddr, sw_cookie, rbm);

		ath11k_dp_rx_mon_next_link_desc_get(rx_msdu_link_desc, &paddr,
						    &sw_cookie, &rbm,
						    &p_buf_addr_info);

		अगर (ar->ab->hw_params.rxdma1_enable) अणु
			अगर (ath11k_dp_rx_monitor_link_desc_वापस(ar,
								  p_last_buf_addr_info,
								  dp->mac_id))
				ath11k_dbg(ar->ab, ATH11K_DBG_DATA,
					   "dp_rx_monitor_link_desc_return failed");
		पूर्ण अन्यथा अणु
			ath11k_dp_rx_link_desc_वापस(ar->ab, rx_link_buf_info,
						      HAL_WBM_REL_BM_ACT_PUT_IN_IDLE);
		पूर्ण

		p_last_buf_addr_info = p_buf_addr_info;

	पूर्ण जबतक (paddr && msdu_cnt);

	अगर (last)
		last->next = शून्य;

	*tail_msdu = msdu;

	अगर (msdu_cnt == 0)
		*npackets = 1;

	वापस rx_bufs_used;
पूर्ण

अटल व्योम ath11k_dp_rx_msdus_set_payload(काष्ठा ath11k *ar, काष्ठा sk_buff *msdu)
अणु
	u32 rx_pkt_offset, l2_hdr_offset;

	rx_pkt_offset = ar->ab->hw_params.hal_desc_sz;
	l2_hdr_offset = ath11k_dp_rx_h_msdu_end_l3pad(ar->ab,
						      (काष्ठा hal_rx_desc *)msdu->data);
	skb_pull(msdu, rx_pkt_offset + l2_hdr_offset);
पूर्ण

अटल काष्ठा sk_buff *
ath11k_dp_rx_mon_merg_msdus(काष्ठा ath11k *ar,
			    u32 mac_id, काष्ठा sk_buff *head_msdu,
			    काष्ठा sk_buff *last_msdu,
			    काष्ठा ieee80211_rx_status *rxs)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा sk_buff *msdu, *mpdu_buf, *prev_buf;
	u32 wअगरi_hdr_len;
	काष्ठा hal_rx_desc *rx_desc;
	अक्षर *hdr_desc;
	u8 *dest, decap_क्रमmat;
	काष्ठा ieee80211_hdr_3addr *wh;
	काष्ठा rx_attention *rx_attention;

	mpdu_buf = शून्य;

	अगर (!head_msdu)
		जाओ err_merge_fail;

	rx_desc = (काष्ठा hal_rx_desc *)head_msdu->data;
	rx_attention = ath11k_dp_rx_get_attention(ab, rx_desc);

	अगर (ath11k_dp_rxdesc_get_mpdulen_err(rx_attention))
		वापस शून्य;

	decap_क्रमmat = ath11k_dp_rx_h_msdu_start_decap_type(ab, rx_desc);

	ath11k_dp_rx_h_ppdu(ar, rx_desc, rxs);

	अगर (decap_क्रमmat == DP_RX_DECAP_TYPE_RAW) अणु
		ath11k_dp_rx_msdus_set_payload(ar, head_msdu);

		prev_buf = head_msdu;
		msdu = head_msdu->next;

		जबतक (msdu) अणु
			ath11k_dp_rx_msdus_set_payload(ar, msdu);

			prev_buf = msdu;
			msdu = msdu->next;
		पूर्ण

		prev_buf->next = शून्य;

		skb_trim(prev_buf, prev_buf->len - HAL_RX_FCS_LEN);
	पूर्ण अन्यथा अगर (decap_क्रमmat == DP_RX_DECAP_TYPE_NATIVE_WIFI) अणु
		__le16 qos_field;
		u8 qos_pkt = 0;

		rx_desc = (काष्ठा hal_rx_desc *)head_msdu->data;
		hdr_desc = ath11k_dp_rxdesc_get_80211hdr(ab, rx_desc);

		/* Base size */
		wअगरi_hdr_len = माप(काष्ठा ieee80211_hdr_3addr);
		wh = (काष्ठा ieee80211_hdr_3addr *)hdr_desc;

		अगर (ieee80211_is_data_qos(wh->frame_control)) अणु
			काष्ठा ieee80211_qos_hdr *qwh =
					(काष्ठा ieee80211_qos_hdr *)hdr_desc;

			qos_field = qwh->qos_ctrl;
			qos_pkt = 1;
		पूर्ण
		msdu = head_msdu;

		जबतक (msdu) अणु
			rx_desc = (काष्ठा hal_rx_desc *)msdu->data;
			hdr_desc = ath11k_dp_rxdesc_get_80211hdr(ab, rx_desc);

			अगर (qos_pkt) अणु
				dest = skb_push(msdu, माप(__le16));
				अगर (!dest)
					जाओ err_merge_fail;
				स_नकल(dest, hdr_desc, wअगरi_hdr_len);
				स_नकल(dest + wअगरi_hdr_len,
				       (u8 *)&qos_field, माप(__le16));
			पूर्ण
			ath11k_dp_rx_msdus_set_payload(ar, msdu);
			prev_buf = msdu;
			msdu = msdu->next;
		पूर्ण
		dest = skb_put(prev_buf, HAL_RX_FCS_LEN);
		अगर (!dest)
			जाओ err_merge_fail;

		ath11k_dbg(ab, ATH11K_DBG_DATA,
			   "mpdu_buf %pK mpdu_buf->len %u",
			   prev_buf, prev_buf->len);
	पूर्ण अन्यथा अणु
		ath11k_dbg(ab, ATH11K_DBG_DATA,
			   "decap format %d is not supported!\n",
			   decap_क्रमmat);
		जाओ err_merge_fail;
	पूर्ण

	वापस head_msdu;

err_merge_fail:
	अगर (mpdu_buf && decap_क्रमmat != DP_RX_DECAP_TYPE_RAW) अणु
		ath11k_dbg(ab, ATH11K_DBG_DATA,
			   "err_merge_fail mpdu_buf %pK", mpdu_buf);
		/* Free the head buffer */
		dev_kमुक्त_skb_any(mpdu_buf);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_mon_deliver(काष्ठा ath11k *ar, u32 mac_id,
				    काष्ठा sk_buff *head_msdu,
				    काष्ठा sk_buff *tail_msdu,
				    काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा sk_buff *mon_skb, *skb_next, *header;
	काष्ठा ieee80211_rx_status *rxs = &dp->rx_status, *status;

	mon_skb = ath11k_dp_rx_mon_merg_msdus(ar, mac_id, head_msdu,
					      tail_msdu, rxs);

	अगर (!mon_skb)
		जाओ mon_deliver_fail;

	header = mon_skb;

	rxs->flag = 0;
	करो अणु
		skb_next = mon_skb->next;
		अगर (!skb_next)
			rxs->flag &= ~RX_FLAG_AMSDU_MORE;
		अन्यथा
			rxs->flag |= RX_FLAG_AMSDU_MORE;

		अगर (mon_skb == header) अणु
			header = शून्य;
			rxs->flag &= ~RX_FLAG_ALLOW_SAME_PN;
		पूर्ण अन्यथा अणु
			rxs->flag |= RX_FLAG_ALLOW_SAME_PN;
		पूर्ण
		rxs->flag |= RX_FLAG_ONLY_MONITOR;

		status = IEEE80211_SKB_RXCB(mon_skb);
		*status = *rxs;

		ath11k_dp_rx_deliver_msdu(ar, napi, mon_skb);
		mon_skb = skb_next;
	पूर्ण जबतक (mon_skb);
	rxs->flag = 0;

	वापस 0;

mon_deliver_fail:
	mon_skb = head_msdu;
	जबतक (mon_skb) अणु
		skb_next = mon_skb->next;
		dev_kमुक्त_skb_any(mon_skb);
		mon_skb = skb_next;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम ath11k_dp_rx_mon_dest_process(काष्ठा ath11k *ar, पूर्णांक mac_id,
					  u32 quota, काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_mon_data *pmon = (काष्ठा ath11k_mon_data *)&dp->mon_data;
	व्योम *ring_entry;
	व्योम *mon_dst_srng;
	u32 ppdu_id;
	u32 rx_bufs_used;
	u32 ring_id;
	काष्ठा ath11k_pdev_mon_stats *rx_mon_stats;
	u32	 npackets = 0;

	अगर (ar->ab->hw_params.rxdma1_enable)
		ring_id = dp->rxdma_mon_dst_ring.ring_id;
	अन्यथा
		ring_id = dp->rxdma_err_dst_ring[mac_id].ring_id;

	mon_dst_srng = &ar->ab->hal.srng_list[ring_id];

	अगर (!mon_dst_srng) अणु
		ath11k_warn(ar->ab,
			    "HAL Monitor Destination Ring Init Failed -- %pK",
			    mon_dst_srng);
		वापस;
	पूर्ण

	spin_lock_bh(&pmon->mon_lock);

	ath11k_hal_srng_access_begin(ar->ab, mon_dst_srng);

	ppdu_id = pmon->mon_ppdu_info.ppdu_id;
	rx_bufs_used = 0;
	rx_mon_stats = &pmon->rx_mon_stats;

	जबतक ((ring_entry = ath11k_hal_srng_dst_peek(ar->ab, mon_dst_srng))) अणु
		काष्ठा sk_buff *head_msdu, *tail_msdu;

		head_msdu = शून्य;
		tail_msdu = शून्य;

		rx_bufs_used += ath11k_dp_rx_mon_mpdu_pop(ar, mac_id, ring_entry,
							  &head_msdu,
							  &tail_msdu,
							  &npackets, &ppdu_id);

		अगर (ppdu_id != pmon->mon_ppdu_info.ppdu_id) अणु
			pmon->mon_ppdu_status = DP_PPDU_STATUS_START;
			ath11k_dbg(ar->ab, ATH11K_DBG_DATA,
				   "dest_rx: new ppdu_id %x != status ppdu_id %x",
				   ppdu_id, pmon->mon_ppdu_info.ppdu_id);
			अवरोध;
		पूर्ण
		अगर (head_msdu && tail_msdu) अणु
			ath11k_dp_rx_mon_deliver(ar, dp->mac_id, head_msdu,
						 tail_msdu, napi);
			rx_mon_stats->dest_mpdu_करोne++;
		पूर्ण

		ring_entry = ath11k_hal_srng_dst_get_next_entry(ar->ab,
								mon_dst_srng);
	पूर्ण
	ath11k_hal_srng_access_end(ar->ab, mon_dst_srng);

	spin_unlock_bh(&pmon->mon_lock);

	अगर (rx_bufs_used) अणु
		rx_mon_stats->dest_ppdu_करोne++;
		अगर (ar->ab->hw_params.rxdma1_enable)
			ath11k_dp_rxbufs_replenish(ar->ab, dp->mac_id,
						   &dp->rxdma_mon_buf_ring,
						   rx_bufs_used,
						   HAL_RX_BUF_RBM_SW3_BM);
		अन्यथा
			ath11k_dp_rxbufs_replenish(ar->ab, dp->mac_id,
						   &dp->rx_refill_buf_ring,
						   rx_bufs_used,
						   HAL_RX_BUF_RBM_SW3_BM);
	पूर्ण
पूर्ण

अटल व्योम ath11k_dp_rx_mon_status_process_tlv(काष्ठा ath11k *ar,
						पूर्णांक mac_id, u32 quota,
						काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_mon_data *pmon = (काष्ठा ath11k_mon_data *)&dp->mon_data;
	काष्ठा hal_rx_mon_ppdu_info *ppdu_info;
	काष्ठा sk_buff *status_skb;
	u32 tlv_status = HAL_TLV_STATUS_BUF_DONE;
	काष्ठा ath11k_pdev_mon_stats *rx_mon_stats;

	ppdu_info = &pmon->mon_ppdu_info;
	rx_mon_stats = &pmon->rx_mon_stats;

	अगर (pmon->mon_ppdu_status != DP_PPDU_STATUS_START)
		वापस;

	जबतक (!skb_queue_empty(&pmon->rx_status_q)) अणु
		status_skb = skb_dequeue(&pmon->rx_status_q);

		tlv_status = ath11k_hal_rx_parse_mon_status(ar->ab, ppdu_info,
							    status_skb);
		अगर (tlv_status == HAL_TLV_STATUS_PPDU_DONE) अणु
			rx_mon_stats->status_ppdu_करोne++;
			pmon->mon_ppdu_status = DP_PPDU_STATUS_DONE;
			ath11k_dp_rx_mon_dest_process(ar, mac_id, quota, napi);
			pmon->mon_ppdu_status = DP_PPDU_STATUS_START;
		पूर्ण
		dev_kमुक्त_skb_any(status_skb);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_dp_mon_process_rx(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
				    काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ath11k *ar = ath11k_ab_to_ar(ab, mac_id);
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_mon_data *pmon = (काष्ठा ath11k_mon_data *)&dp->mon_data;
	पूर्णांक num_buffs_reaped = 0;

	num_buffs_reaped = ath11k_dp_rx_reap_mon_status_ring(ar->ab, mac_id, &budget,
							     &pmon->rx_status_q);
	अगर (num_buffs_reaped)
		ath11k_dp_rx_mon_status_process_tlv(ar, mac_id, budget, napi);

	वापस num_buffs_reaped;
पूर्ण

पूर्णांक ath11k_dp_rx_process_mon_rings(काष्ठा ath11k_base *ab, पूर्णांक mac_id,
				   काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ath11k *ar = ath11k_ab_to_ar(ab, mac_id);
	पूर्णांक ret = 0;

	अगर (test_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags))
		ret = ath11k_dp_mon_process_rx(ab, mac_id, napi, budget);
	अन्यथा
		ret = ath11k_dp_rx_process_mon_status(ab, mac_id, napi, budget);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_dp_rx_pdev_mon_status_attach(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_mon_data *pmon = (काष्ठा ath11k_mon_data *)&dp->mon_data;

	skb_queue_head_init(&pmon->rx_status_q);

	pmon->mon_ppdu_status = DP_PPDU_STATUS_START;

	स_रखो(&pmon->rx_mon_stats, 0,
	       माप(pmon->rx_mon_stats));
	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_rx_pdev_mon_attach(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_mon_data *pmon = &dp->mon_data;
	काष्ठा hal_srng *mon_desc_srng = शून्य;
	काष्ठा dp_srng *dp_srng;
	पूर्णांक ret = 0;
	u32 n_link_desc = 0;

	ret = ath11k_dp_rx_pdev_mon_status_attach(ar);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "pdev_mon_status_attach() failed");
		वापस ret;
	पूर्ण

	/* अगर rxdma1_enable is false, no need to setup
	 * rxdma_mon_desc_ring.
	 */
	अगर (!ar->ab->hw_params.rxdma1_enable)
		वापस 0;

	dp_srng = &dp->rxdma_mon_desc_ring;
	n_link_desc = dp_srng->size /
		ath11k_hal_srng_get_entrysize(ar->ab, HAL_RXDMA_MONITOR_DESC);
	mon_desc_srng =
		&ar->ab->hal.srng_list[dp->rxdma_mon_desc_ring.ring_id];

	ret = ath11k_dp_link_desc_setup(ar->ab, pmon->link_desc_banks,
					HAL_RXDMA_MONITOR_DESC, mon_desc_srng,
					n_link_desc);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "mon_link_desc_pool_setup() failed");
		वापस ret;
	पूर्ण
	pmon->mon_last_linkdesc_paddr = 0;
	pmon->mon_last_buf_cookie = DP_RX_DESC_COOKIE_MAX + 1;
	spin_lock_init(&pmon->mon_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_dp_mon_link_मुक्त(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_dp *dp = &ar->dp;
	काष्ठा ath11k_mon_data *pmon = &dp->mon_data;

	ath11k_dp_link_desc_cleanup(ar->ab, pmon->link_desc_banks,
				    HAL_RXDMA_MONITOR_DESC,
				    &dp->rxdma_mon_desc_ring);
	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_rx_pdev_mon_detach(काष्ठा ath11k *ar)
अणु
	ath11k_dp_mon_link_मुक्त(ar);
	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_rx_pktlog_start(काष्ठा ath11k_base *ab)
अणु
	/* start reap समयr */
	mod_समयr(&ab->mon_reap_समयr,
		  jअगरfies + msecs_to_jअगरfies(ATH11K_MON_TIMER_INTERVAL));

	वापस 0;
पूर्ण

पूर्णांक ath11k_dp_rx_pktlog_stop(काष्ठा ath11k_base *ab, bool stop_समयr)
अणु
	पूर्णांक ret;

	अगर (stop_समयr)
		del_समयr_sync(&ab->mon_reap_समयr);

	/* reap all the monitor related rings */
	ret = ath11k_dp_purge_mon_ring(ab);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to purge dp mon ring: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
