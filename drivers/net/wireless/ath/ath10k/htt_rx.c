<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश "core.h"
#समावेश "htc.h"
#समावेश "htt.h"
#समावेश "txrx.h"
#समावेश "debug.h"
#समावेश "trace.h"
#समावेश "mac.h"

#समावेश <linux/log2.h>
#समावेश <linux/bitfield.h>

/* when under memory pressure rx ring refill may fail and needs a retry */
#घोषणा HTT_RX_RING_REFILL_RETRY_MS 50

#घोषणा HTT_RX_RING_REFILL_RESCHED_MS 5

अटल पूर्णांक ath10k_htt_rx_get_csum_state(काष्ठा sk_buff *skb);

अटल काष्ठा sk_buff *
ath10k_htt_rx_find_skb_paddr(काष्ठा ath10k *ar, u64 paddr)
अणु
	काष्ठा ath10k_skb_rxcb *rxcb;

	hash_क्रम_each_possible(ar->htt.rx_ring.skb_table, rxcb, hlist, paddr)
		अगर (rxcb->paddr == paddr)
			वापस ATH10K_RXCB_SKB(rxcb);

	WARN_ON_ONCE(1);
	वापस शून्य;
पूर्ण

अटल व्योम ath10k_htt_rx_ring_मुक्त(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ath10k_skb_rxcb *rxcb;
	काष्ठा hlist_node *n;
	पूर्णांक i;

	अगर (htt->rx_ring.in_ord_rx) अणु
		hash_क्रम_each_safe(htt->rx_ring.skb_table, i, n, rxcb, hlist) अणु
			skb = ATH10K_RXCB_SKB(rxcb);
			dma_unmap_single(htt->ar->dev, rxcb->paddr,
					 skb->len + skb_tailroom(skb),
					 DMA_FROM_DEVICE);
			hash_del(&rxcb->hlist);
			dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < htt->rx_ring.size; i++) अणु
			skb = htt->rx_ring.netbufs_ring[i];
			अगर (!skb)
				जारी;

			rxcb = ATH10K_SKB_RXCB(skb);
			dma_unmap_single(htt->ar->dev, rxcb->paddr,
					 skb->len + skb_tailroom(skb),
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण

	htt->rx_ring.fill_cnt = 0;
	hash_init(htt->rx_ring.skb_table);
	स_रखो(htt->rx_ring.netbufs_ring, 0,
	       htt->rx_ring.size * माप(htt->rx_ring.netbufs_ring[0]));
पूर्ण

अटल माप_प्रकार ath10k_htt_get_rx_ring_size_32(काष्ठा ath10k_htt *htt)
अणु
	वापस htt->rx_ring.size * माप(htt->rx_ring.paddrs_ring_32);
पूर्ण

अटल माप_प्रकार ath10k_htt_get_rx_ring_size_64(काष्ठा ath10k_htt *htt)
अणु
	वापस htt->rx_ring.size * माप(htt->rx_ring.paddrs_ring_64);
पूर्ण

अटल व्योम ath10k_htt_config_paddrs_ring_32(काष्ठा ath10k_htt *htt,
					     व्योम *vaddr)
अणु
	htt->rx_ring.paddrs_ring_32 = vaddr;
पूर्ण

अटल व्योम ath10k_htt_config_paddrs_ring_64(काष्ठा ath10k_htt *htt,
					     व्योम *vaddr)
अणु
	htt->rx_ring.paddrs_ring_64 = vaddr;
पूर्ण

अटल व्योम ath10k_htt_set_paddrs_ring_32(काष्ठा ath10k_htt *htt,
					  dma_addr_t paddr, पूर्णांक idx)
अणु
	htt->rx_ring.paddrs_ring_32[idx] = __cpu_to_le32(paddr);
पूर्ण

अटल व्योम ath10k_htt_set_paddrs_ring_64(काष्ठा ath10k_htt *htt,
					  dma_addr_t paddr, पूर्णांक idx)
अणु
	htt->rx_ring.paddrs_ring_64[idx] = __cpu_to_le64(paddr);
पूर्ण

अटल व्योम ath10k_htt_reset_paddrs_ring_32(काष्ठा ath10k_htt *htt, पूर्णांक idx)
अणु
	htt->rx_ring.paddrs_ring_32[idx] = 0;
पूर्ण

अटल व्योम ath10k_htt_reset_paddrs_ring_64(काष्ठा ath10k_htt *htt, पूर्णांक idx)
अणु
	htt->rx_ring.paddrs_ring_64[idx] = 0;
पूर्ण

अटल व्योम *ath10k_htt_get_vaddr_ring_32(काष्ठा ath10k_htt *htt)
अणु
	वापस (व्योम *)htt->rx_ring.paddrs_ring_32;
पूर्ण

अटल व्योम *ath10k_htt_get_vaddr_ring_64(काष्ठा ath10k_htt *htt)
अणु
	वापस (व्योम *)htt->rx_ring.paddrs_ring_64;
पूर्ण

अटल पूर्णांक __ath10k_htt_rx_ring_fill_n(काष्ठा ath10k_htt *htt, पूर्णांक num)
अणु
	काष्ठा htt_rx_desc *rx_desc;
	काष्ठा ath10k_skb_rxcb *rxcb;
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	पूर्णांक ret = 0, idx;

	/* The Full Rx Reorder firmware has no way of telling the host
	 * implicitly when it copied HTT Rx Ring buffers to MAC Rx Ring.
	 * To keep things simple make sure ring is always half empty. This
	 * guarantees there'll be no replenishment overruns possible.
	 */
	BUILD_BUG_ON(HTT_RX_RING_FILL_LEVEL >= HTT_RX_RING_SIZE / 2);

	idx = __le32_to_cpu(*htt->rx_ring.alloc_idx.vaddr);

	अगर (idx < 0 || idx >= htt->rx_ring.size) अणु
		ath10k_err(htt->ar, "rx ring index is not valid, firmware malfunctioning?\n");
		idx &= htt->rx_ring.size_mask;
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	जबतक (num > 0) अणु
		skb = dev_alloc_skb(HTT_RX_BUF_SIZE + HTT_RX_DESC_ALIGN);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, HTT_RX_DESC_ALIGN))
			skb_pull(skb,
				 PTR_ALIGN(skb->data, HTT_RX_DESC_ALIGN) -
				 skb->data);

		/* Clear rx_desc attention word beक्रमe posting to Rx ring */
		rx_desc = (काष्ठा htt_rx_desc *)skb->data;
		rx_desc->attention.flags = __cpu_to_le32(0);

		paddr = dma_map_single(htt->ar->dev, skb->data,
				       skb->len + skb_tailroom(skb),
				       DMA_FROM_DEVICE);

		अगर (unlikely(dma_mapping_error(htt->ar->dev, paddr))) अणु
			dev_kमुक्त_skb_any(skb);
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		rxcb = ATH10K_SKB_RXCB(skb);
		rxcb->paddr = paddr;
		htt->rx_ring.netbufs_ring[idx] = skb;
		ath10k_htt_set_paddrs_ring(htt, paddr, idx);
		htt->rx_ring.fill_cnt++;

		अगर (htt->rx_ring.in_ord_rx) अणु
			hash_add(htt->rx_ring.skb_table,
				 &ATH10K_SKB_RXCB(skb)->hlist,
				 paddr);
		पूर्ण

		num--;
		idx++;
		idx &= htt->rx_ring.size_mask;
	पूर्ण

fail:
	/*
	 * Make sure the rx buffer is updated beक्रमe available buffer
	 * index to aव्योम any potential rx ring corruption.
	 */
	mb();
	*htt->rx_ring.alloc_idx.vaddr = __cpu_to_le32(idx);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_ring_fill_n(काष्ठा ath10k_htt *htt, पूर्णांक num)
अणु
	lockdep_निश्चित_held(&htt->rx_ring.lock);
	वापस __ath10k_htt_rx_ring_fill_n(htt, num);
पूर्ण

अटल व्योम ath10k_htt_rx_msdu_buff_replenish(काष्ठा ath10k_htt *htt)
अणु
	पूर्णांक ret, num_deficit, num_to_fill;

	/* Refilling the whole RX ring buffer proves to be a bad idea. The
	 * reason is RX may take up signअगरicant amount of CPU cycles and starve
	 * other tasks, e.g. TX on an ethernet device जबतक acting as a bridge
	 * with ath10k wlan पूर्णांकerface. This ended up with very poor perक्रमmance
	 * once CPU the host प्रणाली was overwhelmed with RX on ath10k.
	 *
	 * By limiting the number of refills the replenishing occurs
	 * progressively. This in turns makes use of the fact tasklets are
	 * processed in FIFO order. This means actual RX processing can starve
	 * out refilling. If there's not enough buffers on RX ring FW will not
	 * report RX until it is refilled with enough buffers. This
	 * स्वतःmatically balances load wrt to CPU घातer.
	 *
	 * This probably comes at a cost of lower maximum throughput but
	 * improves the average and stability.
	 */
	spin_lock_bh(&htt->rx_ring.lock);
	num_deficit = htt->rx_ring.fill_level - htt->rx_ring.fill_cnt;
	num_to_fill = min(ATH10K_HTT_MAX_NUM_REFILL, num_deficit);
	num_deficit -= num_to_fill;
	ret = ath10k_htt_rx_ring_fill_n(htt, num_to_fill);
	अगर (ret == -ENOMEM) अणु
		/*
		 * Failed to fill it to the desired level -
		 * we'll start a समयr and try again next समय.
		 * As दीर्घ as enough buffers are left in the ring क्रम
		 * another A-MPDU rx, no special recovery is needed.
		 */
		mod_समयr(&htt->rx_ring.refill_retry_समयr, jअगरfies +
			  msecs_to_jअगरfies(HTT_RX_RING_REFILL_RETRY_MS));
	पूर्ण अन्यथा अगर (num_deficit > 0) अणु
		mod_समयr(&htt->rx_ring.refill_retry_समयr, jअगरfies +
			  msecs_to_jअगरfies(HTT_RX_RING_REFILL_RESCHED_MS));
	पूर्ण
	spin_unlock_bh(&htt->rx_ring.lock);
पूर्ण

अटल व्योम ath10k_htt_rx_ring_refill_retry(काष्ठा समयr_list *t)
अणु
	काष्ठा ath10k_htt *htt = from_समयr(htt, t, rx_ring.refill_retry_समयr);

	ath10k_htt_rx_msdu_buff_replenish(htt);
पूर्ण

पूर्णांक ath10k_htt_rx_ring_refill(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;
	पूर्णांक ret;

	अगर (ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL)
		वापस 0;

	spin_lock_bh(&htt->rx_ring.lock);
	ret = ath10k_htt_rx_ring_fill_n(htt, (htt->rx_ring.fill_level -
					      htt->rx_ring.fill_cnt));

	अगर (ret)
		ath10k_htt_rx_ring_मुक्त(htt);

	spin_unlock_bh(&htt->rx_ring.lock);

	वापस ret;
पूर्ण

व्योम ath10k_htt_rx_मुक्त(काष्ठा ath10k_htt *htt)
अणु
	अगर (htt->ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL)
		वापस;

	del_समयr_sync(&htt->rx_ring.refill_retry_समयr);

	skb_queue_purge(&htt->rx_msdus_q);
	skb_queue_purge(&htt->rx_in_ord_compl_q);
	skb_queue_purge(&htt->tx_fetch_ind_q);

	spin_lock_bh(&htt->rx_ring.lock);
	ath10k_htt_rx_ring_मुक्त(htt);
	spin_unlock_bh(&htt->rx_ring.lock);

	dma_मुक्त_coherent(htt->ar->dev,
			  ath10k_htt_get_rx_ring_size(htt),
			  ath10k_htt_get_vaddr_ring(htt),
			  htt->rx_ring.base_paddr);

	dma_मुक्त_coherent(htt->ar->dev,
			  माप(*htt->rx_ring.alloc_idx.vaddr),
			  htt->rx_ring.alloc_idx.vaddr,
			  htt->rx_ring.alloc_idx.paddr);

	kमुक्त(htt->rx_ring.netbufs_ring);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *ath10k_htt_rx_netbuf_pop(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	पूर्णांक idx;
	काष्ठा sk_buff *msdu;

	lockdep_निश्चित_held(&htt->rx_ring.lock);

	अगर (htt->rx_ring.fill_cnt == 0) अणु
		ath10k_warn(ar, "tried to pop sk_buff from an empty rx ring\n");
		वापस शून्य;
	पूर्ण

	idx = htt->rx_ring.sw_rd_idx.msdu_payld;
	msdu = htt->rx_ring.netbufs_ring[idx];
	htt->rx_ring.netbufs_ring[idx] = शून्य;
	ath10k_htt_reset_paddrs_ring(htt, idx);

	idx++;
	idx &= htt->rx_ring.size_mask;
	htt->rx_ring.sw_rd_idx.msdu_payld = idx;
	htt->rx_ring.fill_cnt--;

	dma_unmap_single(htt->ar->dev,
			 ATH10K_SKB_RXCB(msdu)->paddr,
			 msdu->len + skb_tailroom(msdu),
			 DMA_FROM_DEVICE);
	ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य, "htt rx netbuf pop: ",
			msdu->data, msdu->len + skb_tailroom(msdu));

	वापस msdu;
पूर्ण

/* वापस: < 0 fatal error, 0 - non chained msdu, 1 chained msdu */
अटल पूर्णांक ath10k_htt_rx_amsdu_pop(काष्ठा ath10k_htt *htt,
				   काष्ठा sk_buff_head *amsdu)
अणु
	काष्ठा ath10k *ar = htt->ar;
	पूर्णांक msdu_len, msdu_chaining = 0;
	काष्ठा sk_buff *msdu;
	काष्ठा htt_rx_desc *rx_desc;

	lockdep_निश्चित_held(&htt->rx_ring.lock);

	क्रम (;;) अणु
		पूर्णांक last_msdu, msdu_len_invalid, msdu_chained;

		msdu = ath10k_htt_rx_netbuf_pop(htt);
		अगर (!msdu) अणु
			__skb_queue_purge(amsdu);
			वापस -ENOENT;
		पूर्ण

		__skb_queue_tail(amsdu, msdu);

		rx_desc = (काष्ठा htt_rx_desc *)msdu->data;

		/* FIXME: we must report msdu payload since this is what caller
		 * expects now
		 */
		skb_put(msdu, दुरत्व(काष्ठा htt_rx_desc, msdu_payload));
		skb_pull(msdu, दुरत्व(काष्ठा htt_rx_desc, msdu_payload));

		/*
		 * Sanity check - confirm the HW is finished filling in the
		 * rx data.
		 * If the HW and SW are working correctly, then it's guaranteed
		 * that the HW's MAC DMA is करोne beक्रमe this poपूर्णांक in the SW.
		 * To prevent the हाल that we handle a stale Rx descriptor,
		 * just निश्चित क्रम now until we have a way to recover.
		 */
		अगर (!(__le32_to_cpu(rx_desc->attention.flags)
				& RX_ATTENTION_FLAGS_MSDU_DONE)) अणु
			__skb_queue_purge(amsdu);
			वापस -EIO;
		पूर्ण

		msdu_len_invalid = !!(__le32_to_cpu(rx_desc->attention.flags)
					& (RX_ATTENTION_FLAGS_MPDU_LENGTH_ERR |
					   RX_ATTENTION_FLAGS_MSDU_LENGTH_ERR));
		msdu_len = MS(__le32_to_cpu(rx_desc->msdu_start.common.info0),
			      RX_MSDU_START_INFO0_MSDU_LENGTH);
		msdu_chained = rx_desc->frag_info.ring2_more_count;

		अगर (msdu_len_invalid)
			msdu_len = 0;

		skb_trim(msdu, 0);
		skb_put(msdu, min(msdu_len, HTT_RX_MSDU_SIZE));
		msdu_len -= msdu->len;

		/* Note: Chained buffers करो not contain rx descriptor */
		जबतक (msdu_chained--) अणु
			msdu = ath10k_htt_rx_netbuf_pop(htt);
			अगर (!msdu) अणु
				__skb_queue_purge(amsdu);
				वापस -ENOENT;
			पूर्ण

			__skb_queue_tail(amsdu, msdu);
			skb_trim(msdu, 0);
			skb_put(msdu, min(msdu_len, HTT_RX_BUF_SIZE));
			msdu_len -= msdu->len;
			msdu_chaining = 1;
		पूर्ण

		last_msdu = __le32_to_cpu(rx_desc->msdu_end.common.info0) &
				RX_MSDU_END_INFO0_LAST_MSDU;

		trace_ath10k_htt_rx_desc(ar, &rx_desc->attention,
					 माप(*rx_desc) - माप(u32));

		अगर (last_msdu)
			अवरोध;
	पूर्ण

	अगर (skb_queue_empty(amsdu))
		msdu_chaining = -1;

	/*
	 * Don't refill the ring yet.
	 *
	 * First, the elements popped here are still in use - it is not
	 * safe to overग_लिखो them until the matching call to
	 * mpdu_desc_list_next. Second, क्रम efficiency it is preferable to
	 * refill the rx ring with 1 PPDU's worth of rx buffers (something
	 * like 32 x 3 buffers), rather than one MPDU's worth of rx buffers
	 * (something like 3 buffers). Consequently, we'll rely on the txrx
	 * SW to tell us when it is करोne pulling all the PPDU's rx buffers
	 * out of the rx ring, and then refill it just once.
	 */

	वापस msdu_chaining;
पूर्ण

अटल काष्ठा sk_buff *ath10k_htt_rx_pop_paddr(काष्ठा ath10k_htt *htt,
					       u64 paddr)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा ath10k_skb_rxcb *rxcb;
	काष्ठा sk_buff *msdu;

	lockdep_निश्चित_held(&htt->rx_ring.lock);

	msdu = ath10k_htt_rx_find_skb_paddr(ar, paddr);
	अगर (!msdu)
		वापस शून्य;

	rxcb = ATH10K_SKB_RXCB(msdu);
	hash_del(&rxcb->hlist);
	htt->rx_ring.fill_cnt--;

	dma_unmap_single(htt->ar->dev, rxcb->paddr,
			 msdu->len + skb_tailroom(msdu),
			 DMA_FROM_DEVICE);
	ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य, "htt rx netbuf pop: ",
			msdu->data, msdu->len + skb_tailroom(msdu));

	वापस msdu;
पूर्ण

अटल अंतरभूत व्योम ath10k_htt_append_frag_list(काष्ठा sk_buff *skb_head,
					       काष्ठा sk_buff *frag_list,
					       अचिन्हित पूर्णांक frag_len)
अणु
	skb_shinfo(skb_head)->frag_list = frag_list;
	skb_head->data_len = frag_len;
	skb_head->len += skb_head->data_len;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_handle_amsdu_mon_32(काष्ठा ath10k_htt *htt,
					     काष्ठा sk_buff *msdu,
					     काष्ठा htt_rx_in_ord_msdu_desc **msdu_desc)
अणु
	काष्ठा ath10k *ar = htt->ar;
	u32 paddr;
	काष्ठा sk_buff *frag_buf;
	काष्ठा sk_buff *prev_frag_buf;
	u8 last_frag;
	काष्ठा htt_rx_in_ord_msdu_desc *ind_desc = *msdu_desc;
	काष्ठा htt_rx_desc *rxd;
	पूर्णांक amsdu_len = __le16_to_cpu(ind_desc->msdu_len);

	rxd = (व्योम *)msdu->data;
	trace_ath10k_htt_rx_desc(ar, rxd, माप(*rxd));

	skb_put(msdu, माप(काष्ठा htt_rx_desc));
	skb_pull(msdu, माप(काष्ठा htt_rx_desc));
	skb_put(msdu, min(amsdu_len, HTT_RX_MSDU_SIZE));
	amsdu_len -= msdu->len;

	last_frag = ind_desc->reserved;
	अगर (last_frag) अणु
		अगर (amsdu_len) अणु
			ath10k_warn(ar, "invalid amsdu len %u, left %d",
				    __le16_to_cpu(ind_desc->msdu_len),
				    amsdu_len);
		पूर्ण
		वापस 0;
	पूर्ण

	ind_desc++;
	paddr = __le32_to_cpu(ind_desc->msdu_paddr);
	frag_buf = ath10k_htt_rx_pop_paddr(htt, paddr);
	अगर (!frag_buf) अणु
		ath10k_warn(ar, "failed to pop frag-1 paddr: 0x%x", paddr);
		वापस -ENOENT;
	पूर्ण

	skb_put(frag_buf, min(amsdu_len, HTT_RX_BUF_SIZE));
	ath10k_htt_append_frag_list(msdu, frag_buf, amsdu_len);

	amsdu_len -= frag_buf->len;
	prev_frag_buf = frag_buf;
	last_frag = ind_desc->reserved;
	जबतक (!last_frag) अणु
		ind_desc++;
		paddr = __le32_to_cpu(ind_desc->msdu_paddr);
		frag_buf = ath10k_htt_rx_pop_paddr(htt, paddr);
		अगर (!frag_buf) अणु
			ath10k_warn(ar, "failed to pop frag-n paddr: 0x%x",
				    paddr);
			prev_frag_buf->next = शून्य;
			वापस -ENOENT;
		पूर्ण

		skb_put(frag_buf, min(amsdu_len, HTT_RX_BUF_SIZE));
		last_frag = ind_desc->reserved;
		amsdu_len -= frag_buf->len;

		prev_frag_buf->next = frag_buf;
		prev_frag_buf = frag_buf;
	पूर्ण

	अगर (amsdu_len) अणु
		ath10k_warn(ar, "invalid amsdu len %u, left %d",
			    __le16_to_cpu(ind_desc->msdu_len), amsdu_len);
	पूर्ण

	*msdu_desc = ind_desc;

	prev_frag_buf->next = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_htt_rx_handle_amsdu_mon_64(काष्ठा ath10k_htt *htt,
				  काष्ठा sk_buff *msdu,
				  काष्ठा htt_rx_in_ord_msdu_desc_ext **msdu_desc)
अणु
	काष्ठा ath10k *ar = htt->ar;
	u64 paddr;
	काष्ठा sk_buff *frag_buf;
	काष्ठा sk_buff *prev_frag_buf;
	u8 last_frag;
	काष्ठा htt_rx_in_ord_msdu_desc_ext *ind_desc = *msdu_desc;
	काष्ठा htt_rx_desc *rxd;
	पूर्णांक amsdu_len = __le16_to_cpu(ind_desc->msdu_len);

	rxd = (व्योम *)msdu->data;
	trace_ath10k_htt_rx_desc(ar, rxd, माप(*rxd));

	skb_put(msdu, माप(काष्ठा htt_rx_desc));
	skb_pull(msdu, माप(काष्ठा htt_rx_desc));
	skb_put(msdu, min(amsdu_len, HTT_RX_MSDU_SIZE));
	amsdu_len -= msdu->len;

	last_frag = ind_desc->reserved;
	अगर (last_frag) अणु
		अगर (amsdu_len) अणु
			ath10k_warn(ar, "invalid amsdu len %u, left %d",
				    __le16_to_cpu(ind_desc->msdu_len),
				    amsdu_len);
		पूर्ण
		वापस 0;
	पूर्ण

	ind_desc++;
	paddr = __le64_to_cpu(ind_desc->msdu_paddr);
	frag_buf = ath10k_htt_rx_pop_paddr(htt, paddr);
	अगर (!frag_buf) अणु
		ath10k_warn(ar, "failed to pop frag-1 paddr: 0x%llx", paddr);
		वापस -ENOENT;
	पूर्ण

	skb_put(frag_buf, min(amsdu_len, HTT_RX_BUF_SIZE));
	ath10k_htt_append_frag_list(msdu, frag_buf, amsdu_len);

	amsdu_len -= frag_buf->len;
	prev_frag_buf = frag_buf;
	last_frag = ind_desc->reserved;
	जबतक (!last_frag) अणु
		ind_desc++;
		paddr = __le64_to_cpu(ind_desc->msdu_paddr);
		frag_buf = ath10k_htt_rx_pop_paddr(htt, paddr);
		अगर (!frag_buf) अणु
			ath10k_warn(ar, "failed to pop frag-n paddr: 0x%llx",
				    paddr);
			prev_frag_buf->next = शून्य;
			वापस -ENOENT;
		पूर्ण

		skb_put(frag_buf, min(amsdu_len, HTT_RX_BUF_SIZE));
		last_frag = ind_desc->reserved;
		amsdu_len -= frag_buf->len;

		prev_frag_buf->next = frag_buf;
		prev_frag_buf = frag_buf;
	पूर्ण

	अगर (amsdu_len) अणु
		ath10k_warn(ar, "invalid amsdu len %u, left %d",
			    __le16_to_cpu(ind_desc->msdu_len), amsdu_len);
	पूर्ण

	*msdu_desc = ind_desc;

	prev_frag_buf->next = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_pop_paddr32_list(काष्ठा ath10k_htt *htt,
					  काष्ठा htt_rx_in_ord_ind *ev,
					  काष्ठा sk_buff_head *list)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा htt_rx_in_ord_msdu_desc *msdu_desc = ev->msdu_descs32;
	काष्ठा htt_rx_desc *rxd;
	काष्ठा sk_buff *msdu;
	पूर्णांक msdu_count, ret;
	bool is_offload;
	u32 paddr;

	lockdep_निश्चित_held(&htt->rx_ring.lock);

	msdu_count = __le16_to_cpu(ev->msdu_count);
	is_offload = !!(ev->info & HTT_RX_IN_ORD_IND_INFO_OFFLOAD_MASK);

	जबतक (msdu_count--) अणु
		paddr = __le32_to_cpu(msdu_desc->msdu_paddr);

		msdu = ath10k_htt_rx_pop_paddr(htt, paddr);
		अगर (!msdu) अणु
			__skb_queue_purge(list);
			वापस -ENOENT;
		पूर्ण

		अगर (!is_offload && ar->monitor_arvअगर) अणु
			ret = ath10k_htt_rx_handle_amsdu_mon_32(htt, msdu,
								&msdu_desc);
			अगर (ret) अणु
				__skb_queue_purge(list);
				वापस ret;
			पूर्ण
			__skb_queue_tail(list, msdu);
			msdu_desc++;
			जारी;
		पूर्ण

		__skb_queue_tail(list, msdu);

		अगर (!is_offload) अणु
			rxd = (व्योम *)msdu->data;

			trace_ath10k_htt_rx_desc(ar, rxd, माप(*rxd));

			skb_put(msdu, माप(*rxd));
			skb_pull(msdu, माप(*rxd));
			skb_put(msdu, __le16_to_cpu(msdu_desc->msdu_len));

			अगर (!(__le32_to_cpu(rxd->attention.flags) &
			      RX_ATTENTION_FLAGS_MSDU_DONE)) अणु
				ath10k_warn(htt->ar, "tried to pop an incomplete frame, oops!\n");
				वापस -EIO;
			पूर्ण
		पूर्ण

		msdu_desc++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_pop_paddr64_list(काष्ठा ath10k_htt *htt,
					  काष्ठा htt_rx_in_ord_ind *ev,
					  काष्ठा sk_buff_head *list)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा htt_rx_in_ord_msdu_desc_ext *msdu_desc = ev->msdu_descs64;
	काष्ठा htt_rx_desc *rxd;
	काष्ठा sk_buff *msdu;
	पूर्णांक msdu_count, ret;
	bool is_offload;
	u64 paddr;

	lockdep_निश्चित_held(&htt->rx_ring.lock);

	msdu_count = __le16_to_cpu(ev->msdu_count);
	is_offload = !!(ev->info & HTT_RX_IN_ORD_IND_INFO_OFFLOAD_MASK);

	जबतक (msdu_count--) अणु
		paddr = __le64_to_cpu(msdu_desc->msdu_paddr);
		msdu = ath10k_htt_rx_pop_paddr(htt, paddr);
		अगर (!msdu) अणु
			__skb_queue_purge(list);
			वापस -ENOENT;
		पूर्ण

		अगर (!is_offload && ar->monitor_arvअगर) अणु
			ret = ath10k_htt_rx_handle_amsdu_mon_64(htt, msdu,
								&msdu_desc);
			अगर (ret) अणु
				__skb_queue_purge(list);
				वापस ret;
			पूर्ण
			__skb_queue_tail(list, msdu);
			msdu_desc++;
			जारी;
		पूर्ण

		__skb_queue_tail(list, msdu);

		अगर (!is_offload) अणु
			rxd = (व्योम *)msdu->data;

			trace_ath10k_htt_rx_desc(ar, rxd, माप(*rxd));

			skb_put(msdu, माप(*rxd));
			skb_pull(msdu, माप(*rxd));
			skb_put(msdu, __le16_to_cpu(msdu_desc->msdu_len));

			अगर (!(__le32_to_cpu(rxd->attention.flags) &
			      RX_ATTENTION_FLAGS_MSDU_DONE)) अणु
				ath10k_warn(htt->ar, "tried to pop an incomplete frame, oops!\n");
				वापस -EIO;
			पूर्ण
		पूर्ण

		msdu_desc++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_htt_rx_alloc(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	dma_addr_t paddr;
	व्योम *vaddr, *vaddr_ring;
	माप_प्रकार size;
	काष्ठा समयr_list *समयr = &htt->rx_ring.refill_retry_समयr;

	अगर (ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL)
		वापस 0;

	htt->rx_confused = false;

	/* XXX: The fill level could be changed during runसमय in response to
	 * the host processing latency. Is this really worth it?
	 */
	htt->rx_ring.size = HTT_RX_RING_SIZE;
	htt->rx_ring.size_mask = htt->rx_ring.size - 1;
	htt->rx_ring.fill_level = ar->hw_params.rx_ring_fill_level;

	अगर (!is_घातer_of_2(htt->rx_ring.size)) अणु
		ath10k_warn(ar, "htt rx ring size is not power of 2\n");
		वापस -EINVAL;
	पूर्ण

	htt->rx_ring.netbufs_ring =
		kसुस्मृति(htt->rx_ring.size, माप(काष्ठा sk_buff *),
			GFP_KERNEL);
	अगर (!htt->rx_ring.netbufs_ring)
		जाओ err_netbuf;

	size = ath10k_htt_get_rx_ring_size(htt);

	vaddr_ring = dma_alloc_coherent(htt->ar->dev, size, &paddr, GFP_KERNEL);
	अगर (!vaddr_ring)
		जाओ err_dma_ring;

	ath10k_htt_config_paddrs_ring(htt, vaddr_ring);
	htt->rx_ring.base_paddr = paddr;

	vaddr = dma_alloc_coherent(htt->ar->dev,
				   माप(*htt->rx_ring.alloc_idx.vaddr),
				   &paddr, GFP_KERNEL);
	अगर (!vaddr)
		जाओ err_dma_idx;

	htt->rx_ring.alloc_idx.vaddr = vaddr;
	htt->rx_ring.alloc_idx.paddr = paddr;
	htt->rx_ring.sw_rd_idx.msdu_payld = htt->rx_ring.size_mask;
	*htt->rx_ring.alloc_idx.vaddr = 0;

	/* Initialize the Rx refill retry समयr */
	समयr_setup(समयr, ath10k_htt_rx_ring_refill_retry, 0);

	spin_lock_init(&htt->rx_ring.lock);

	htt->rx_ring.fill_cnt = 0;
	htt->rx_ring.sw_rd_idx.msdu_payld = 0;
	hash_init(htt->rx_ring.skb_table);

	skb_queue_head_init(&htt->rx_msdus_q);
	skb_queue_head_init(&htt->rx_in_ord_compl_q);
	skb_queue_head_init(&htt->tx_fetch_ind_q);
	atomic_set(&htt->num_mpdus_पढ़ोy, 0);

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "htt rx ring size %d fill_level %d\n",
		   htt->rx_ring.size, htt->rx_ring.fill_level);
	वापस 0;

err_dma_idx:
	dma_मुक्त_coherent(htt->ar->dev,
			  ath10k_htt_get_rx_ring_size(htt),
			  vaddr_ring,
			  htt->rx_ring.base_paddr);
err_dma_ring:
	kमुक्त(htt->rx_ring.netbufs_ring);
err_netbuf:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_crypto_param_len(काष्ठा ath10k *ar,
					  क्रमागत htt_rx_mpdu_encrypt_type type)
अणु
	चयन (type) अणु
	हाल HTT_RX_MPDU_ENCRYPT_NONE:
		वापस 0;
	हाल HTT_RX_MPDU_ENCRYPT_WEP40:
	हाल HTT_RX_MPDU_ENCRYPT_WEP104:
		वापस IEEE80211_WEP_IV_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_TKIP_WITHOUT_MIC:
	हाल HTT_RX_MPDU_ENCRYPT_TKIP_WPA:
		वापस IEEE80211_TKIP_IV_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_AES_CCM_WPA2:
		वापस IEEE80211_CCMP_HDR_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_AES_CCM256_WPA2:
		वापस IEEE80211_CCMP_256_HDR_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_AES_GCMP_WPA2:
	हाल HTT_RX_MPDU_ENCRYPT_AES_GCMP256_WPA2:
		वापस IEEE80211_GCMP_HDR_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_WEP128:
	हाल HTT_RX_MPDU_ENCRYPT_WAPI:
		अवरोध;
	पूर्ण

	ath10k_warn(ar, "unsupported encryption type %d\n", type);
	वापस 0;
पूर्ण

#घोषणा MICHAEL_MIC_LEN 8

अटल पूर्णांक ath10k_htt_rx_crypto_mic_len(काष्ठा ath10k *ar,
					क्रमागत htt_rx_mpdu_encrypt_type type)
अणु
	चयन (type) अणु
	हाल HTT_RX_MPDU_ENCRYPT_NONE:
	हाल HTT_RX_MPDU_ENCRYPT_WEP40:
	हाल HTT_RX_MPDU_ENCRYPT_WEP104:
	हाल HTT_RX_MPDU_ENCRYPT_TKIP_WITHOUT_MIC:
	हाल HTT_RX_MPDU_ENCRYPT_TKIP_WPA:
		वापस 0;
	हाल HTT_RX_MPDU_ENCRYPT_AES_CCM_WPA2:
		वापस IEEE80211_CCMP_MIC_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_AES_CCM256_WPA2:
		वापस IEEE80211_CCMP_256_MIC_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_AES_GCMP_WPA2:
	हाल HTT_RX_MPDU_ENCRYPT_AES_GCMP256_WPA2:
		वापस IEEE80211_GCMP_MIC_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_WEP128:
	हाल HTT_RX_MPDU_ENCRYPT_WAPI:
		अवरोध;
	पूर्ण

	ath10k_warn(ar, "unsupported encryption type %d\n", type);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_crypto_icv_len(काष्ठा ath10k *ar,
					क्रमागत htt_rx_mpdu_encrypt_type type)
अणु
	चयन (type) अणु
	हाल HTT_RX_MPDU_ENCRYPT_NONE:
	हाल HTT_RX_MPDU_ENCRYPT_AES_CCM_WPA2:
	हाल HTT_RX_MPDU_ENCRYPT_AES_CCM256_WPA2:
	हाल HTT_RX_MPDU_ENCRYPT_AES_GCMP_WPA2:
	हाल HTT_RX_MPDU_ENCRYPT_AES_GCMP256_WPA2:
		वापस 0;
	हाल HTT_RX_MPDU_ENCRYPT_WEP40:
	हाल HTT_RX_MPDU_ENCRYPT_WEP104:
		वापस IEEE80211_WEP_ICV_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_TKIP_WITHOUT_MIC:
	हाल HTT_RX_MPDU_ENCRYPT_TKIP_WPA:
		वापस IEEE80211_TKIP_ICV_LEN;
	हाल HTT_RX_MPDU_ENCRYPT_WEP128:
	हाल HTT_RX_MPDU_ENCRYPT_WAPI:
		अवरोध;
	पूर्ण

	ath10k_warn(ar, "unsupported encryption type %d\n", type);
	वापस 0;
पूर्ण

काष्ठा amsdu_subframe_hdr अणु
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	__be16 len;
पूर्ण __packed;

#घोषणा GROUP_ID_IS_SU_MIMO(x) ((x) == 0 || (x) == 63)

अटल अंतरभूत u8 ath10k_bw_to_mac80211_bw(u8 bw)
अणु
	u8 ret = 0;

	चयन (bw) अणु
	हाल 0:
		ret = RATE_INFO_BW_20;
		अवरोध;
	हाल 1:
		ret = RATE_INFO_BW_40;
		अवरोध;
	हाल 2:
		ret = RATE_INFO_BW_80;
		अवरोध;
	हाल 3:
		ret = RATE_INFO_BW_160;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ath10k_htt_rx_h_rates(काष्ठा ath10k *ar,
				  काष्ठा ieee80211_rx_status *status,
				  काष्ठा htt_rx_desc *rxd)
अणु
	काष्ठा ieee80211_supported_band *sband;
	u8 cck, rate, bw, sgi, mcs, nss;
	u8 preamble = 0;
	u8 group_id;
	u32 info1, info2, info3;
	u32 stbc, nsts_su;

	info1 = __le32_to_cpu(rxd->ppdu_start.info1);
	info2 = __le32_to_cpu(rxd->ppdu_start.info2);
	info3 = __le32_to_cpu(rxd->ppdu_start.info3);

	preamble = MS(info1, RX_PPDU_START_INFO1_PREAMBLE_TYPE);

	चयन (preamble) अणु
	हाल HTT_RX_LEGACY:
		/* To get legacy rate index band is required. Since band can't
		 * be undefined check अगर freq is non-zero.
		 */
		अगर (!status->freq)
			वापस;

		cck = info1 & RX_PPDU_START_INFO1_L_SIG_RATE_SELECT;
		rate = MS(info1, RX_PPDU_START_INFO1_L_SIG_RATE);
		rate &= ~RX_PPDU_START_RATE_FLAG;

		sband = &ar->mac.sbands[status->band];
		status->rate_idx = ath10k_mac_hw_rate_to_idx(sband, rate, cck);
		अवरोध;
	हाल HTT_RX_HT:
	हाल HTT_RX_HT_WITH_TXBF:
		/* HT-SIG - Table 20-11 in info2 and info3 */
		mcs = info2 & 0x1F;
		nss = mcs >> 3;
		bw = (info2 >> 7) & 1;
		sgi = (info3 >> 7) & 1;

		status->rate_idx = mcs;
		status->encoding = RX_ENC_HT;
		अगर (sgi)
			status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
		अगर (bw)
			status->bw = RATE_INFO_BW_40;
		अवरोध;
	हाल HTT_RX_VHT:
	हाल HTT_RX_VHT_WITH_TXBF:
		/* VHT-SIG-A1 in info2, VHT-SIG-A2 in info3
		 * TODO check this
		 */
		bw = info2 & 3;
		sgi = info3 & 1;
		stbc = (info2 >> 3) & 1;
		group_id = (info2 >> 4) & 0x3F;

		अगर (GROUP_ID_IS_SU_MIMO(group_id)) अणु
			mcs = (info3 >> 4) & 0x0F;
			nsts_su = ((info2 >> 10) & 0x07);
			अगर (stbc)
				nss = (nsts_su >> 2) + 1;
			अन्यथा
				nss = (nsts_su + 1);
		पूर्ण अन्यथा अणु
			/* Hardware करोesn't decode VHT-SIG-B पूर्णांकo Rx descriptor
			 * so it's impossible to decode MCS. Also since
			 * firmware consumes Group Id Management frames host
			 * has no knowledge regarding group/user position
			 * mapping so it's impossible to pick the correct Nsts
			 * from VHT-SIG-A1.
			 *
			 * Bandwidth and SGI are valid so report the rateinfo
			 * on best-efक्रमt basis.
			 */
			mcs = 0;
			nss = 1;
		पूर्ण

		अगर (mcs > 0x09) अणु
			ath10k_warn(ar, "invalid MCS received %u\n", mcs);
			ath10k_warn(ar, "rxd %08x mpdu start %08x %08x msdu start %08x %08x ppdu start %08x %08x %08x %08x %08x\n",
				    __le32_to_cpu(rxd->attention.flags),
				    __le32_to_cpu(rxd->mpdu_start.info0),
				    __le32_to_cpu(rxd->mpdu_start.info1),
				    __le32_to_cpu(rxd->msdu_start.common.info0),
				    __le32_to_cpu(rxd->msdu_start.common.info1),
				    rxd->ppdu_start.info0,
				    __le32_to_cpu(rxd->ppdu_start.info1),
				    __le32_to_cpu(rxd->ppdu_start.info2),
				    __le32_to_cpu(rxd->ppdu_start.info3),
				    __le32_to_cpu(rxd->ppdu_start.info4));

			ath10k_warn(ar, "msdu end %08x mpdu end %08x\n",
				    __le32_to_cpu(rxd->msdu_end.common.info0),
				    __le32_to_cpu(rxd->mpdu_end.info0));

			ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य,
					"rx desc msdu payload: ",
					rxd->msdu_payload, 50);
		पूर्ण

		status->rate_idx = mcs;
		status->nss = nss;

		अगर (sgi)
			status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

		status->bw = ath10k_bw_to_mac80211_bw(bw);
		status->encoding = RX_ENC_VHT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा ieee80211_channel *
ath10k_htt_rx_h_peer_channel(काष्ठा ath10k *ar, काष्ठा htt_rx_desc *rxd)
अणु
	काष्ठा ath10k_peer *peer;
	काष्ठा ath10k_vअगर *arvअगर;
	काष्ठा cfg80211_chan_def def;
	u16 peer_id;

	lockdep_निश्चित_held(&ar->data_lock);

	अगर (!rxd)
		वापस शून्य;

	अगर (rxd->attention.flags &
	    __cpu_to_le32(RX_ATTENTION_FLAGS_PEER_IDX_INVALID))
		वापस शून्य;

	अगर (!(rxd->msdu_end.common.info0 &
	      __cpu_to_le32(RX_MSDU_END_INFO0_FIRST_MSDU)))
		वापस शून्य;

	peer_id = MS(__le32_to_cpu(rxd->mpdu_start.info0),
		     RX_MPDU_START_INFO0_PEER_IDX);

	peer = ath10k_peer_find_by_id(ar, peer_id);
	अगर (!peer)
		वापस शून्य;

	arvअगर = ath10k_get_arvअगर(ar, peer->vdev_id);
	अगर (WARN_ON_ONCE(!arvअगर))
		वापस शून्य;

	अगर (ath10k_mac_vअगर_chan(arvअगर->vअगर, &def))
		वापस शून्य;

	वापस def.chan;
पूर्ण

अटल काष्ठा ieee80211_channel *
ath10k_htt_rx_h_vdev_channel(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	काष्ठा cfg80211_chan_def def;

	lockdep_निश्चित_held(&ar->data_lock);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		अगर (arvअगर->vdev_id == vdev_id &&
		    ath10k_mac_vअगर_chan(arvअगर->vअगर, &def) == 0)
			वापस def.chan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
ath10k_htt_rx_h_any_chan_iter(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_chanctx_conf *conf,
			      व्योम *data)
अणु
	काष्ठा cfg80211_chan_def *def = data;

	*def = conf->def;
पूर्ण

अटल काष्ठा ieee80211_channel *
ath10k_htt_rx_h_any_channel(काष्ठा ath10k *ar)
अणु
	काष्ठा cfg80211_chan_def def = अणुपूर्ण;

	ieee80211_iter_chan_contexts_atomic(ar->hw,
					    ath10k_htt_rx_h_any_chan_iter,
					    &def);

	वापस def.chan;
पूर्ण

अटल bool ath10k_htt_rx_h_channel(काष्ठा ath10k *ar,
				    काष्ठा ieee80211_rx_status *status,
				    काष्ठा htt_rx_desc *rxd,
				    u32 vdev_id)
अणु
	काष्ठा ieee80211_channel *ch;

	spin_lock_bh(&ar->data_lock);
	ch = ar->scan_channel;
	अगर (!ch)
		ch = ar->rx_channel;
	अगर (!ch)
		ch = ath10k_htt_rx_h_peer_channel(ar, rxd);
	अगर (!ch)
		ch = ath10k_htt_rx_h_vdev_channel(ar, vdev_id);
	अगर (!ch)
		ch = ath10k_htt_rx_h_any_channel(ar);
	अगर (!ch)
		ch = ar->tgt_oper_chan;
	spin_unlock_bh(&ar->data_lock);

	अगर (!ch)
		वापस false;

	status->band = ch->band;
	status->freq = ch->center_freq;

	वापस true;
पूर्ण

अटल व्योम ath10k_htt_rx_h_संकेत(काष्ठा ath10k *ar,
				   काष्ठा ieee80211_rx_status *status,
				   काष्ठा htt_rx_desc *rxd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_MAX_CHAINS ; i++) अणु
		status->chains &= ~BIT(i);

		अगर (rxd->ppdu_start.rssi_chains[i].pri20_mhz != 0x80) अणु
			status->chain_संकेत[i] = ATH10K_DEFAULT_NOISE_FLOOR +
				rxd->ppdu_start.rssi_chains[i].pri20_mhz;

			status->chains |= BIT(i);
		पूर्ण
	पूर्ण

	/* FIXME: Get real NF */
	status->संकेत = ATH10K_DEFAULT_NOISE_FLOOR +
			 rxd->ppdu_start.rssi_comb;
	status->flag &= ~RX_FLAG_NO_SIGNAL_VAL;
पूर्ण

अटल व्योम ath10k_htt_rx_h_maस_समय(काष्ठा ath10k *ar,
				    काष्ठा ieee80211_rx_status *status,
				    काष्ठा htt_rx_desc *rxd)
अणु
	/* FIXME: TSF is known only at the end of PPDU, in the last MPDU. This
	 * means all prior MSDUs in a PPDU are reported to mac80211 without the
	 * TSF. Is it worth holding frames until end of PPDU is known?
	 *
	 * FIXME: Can we get/compute 64bit TSF?
	 */
	status->maस_समय = __le32_to_cpu(rxd->ppdu_end.common.tsf_बारtamp);
	status->flag |= RX_FLAG_MACTIME_END;
पूर्ण

अटल व्योम ath10k_htt_rx_h_ppdu(काष्ठा ath10k *ar,
				 काष्ठा sk_buff_head *amsdu,
				 काष्ठा ieee80211_rx_status *status,
				 u32 vdev_id)
अणु
	काष्ठा sk_buff *first;
	काष्ठा htt_rx_desc *rxd;
	bool is_first_ppdu;
	bool is_last_ppdu;

	अगर (skb_queue_empty(amsdu))
		वापस;

	first = skb_peek(amsdu);
	rxd = (व्योम *)first->data - माप(*rxd);

	is_first_ppdu = !!(rxd->attention.flags &
			   __cpu_to_le32(RX_ATTENTION_FLAGS_FIRST_MPDU));
	is_last_ppdu = !!(rxd->attention.flags &
			  __cpu_to_le32(RX_ATTENTION_FLAGS_LAST_MPDU));

	अगर (is_first_ppdu) अणु
		/* New PPDU starts so clear out the old per-PPDU status. */
		status->freq = 0;
		status->rate_idx = 0;
		status->nss = 0;
		status->encoding = RX_ENC_LEGACY;
		status->bw = RATE_INFO_BW_20;

		status->flag &= ~RX_FLAG_MACTIME_END;
		status->flag |= RX_FLAG_NO_SIGNAL_VAL;

		status->flag &= ~(RX_FLAG_AMPDU_IS_LAST);
		status->flag |= RX_FLAG_AMPDU_DETAILS | RX_FLAG_AMPDU_LAST_KNOWN;
		status->ampdu_reference = ar->ampdu_reference;

		ath10k_htt_rx_h_संकेत(ar, status, rxd);
		ath10k_htt_rx_h_channel(ar, status, rxd, vdev_id);
		ath10k_htt_rx_h_rates(ar, status, rxd);
	पूर्ण

	अगर (is_last_ppdu) अणु
		ath10k_htt_rx_h_maस_समय(ar, status, rxd);

		/* set ampdu last segment flag */
		status->flag |= RX_FLAG_AMPDU_IS_LAST;
		ar->ampdu_reference++;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर tid_to_ac[] = अणु
	"BE",
	"BK",
	"BK",
	"BE",
	"VI",
	"VI",
	"VO",
	"VO",
पूर्ण;

अटल अक्षर *ath10k_get_tid(काष्ठा ieee80211_hdr *hdr, अक्षर *out, माप_प्रकार size)
अणु
	u8 *qc;
	पूर्णांक tid;

	अगर (!ieee80211_is_data_qos(hdr->frame_control))
		वापस "";

	qc = ieee80211_get_qos_ctl(hdr);
	tid = *qc & IEEE80211_QOS_CTL_TID_MASK;
	अगर (tid < 8)
		snम_लिखो(out, size, "tid %d (%s)", tid, tid_to_ac[tid]);
	अन्यथा
		snम_लिखो(out, size, "tid %d", tid);

	वापस out;
पूर्ण

अटल व्योम ath10k_htt_rx_h_queue_msdu(काष्ठा ath10k *ar,
				       काष्ठा ieee80211_rx_status *rx_status,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *status;

	status = IEEE80211_SKB_RXCB(skb);
	*status = *rx_status;

	skb_queue_tail(&ar->htt.rx_msdus_q, skb);
पूर्ण

अटल व्योम ath10k_process_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *status;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अक्षर tid[32];

	status = IEEE80211_SKB_RXCB(skb);

	अगर (!(ar->filter_flags & FIF_FCSFAIL) &&
	    status->flag & RX_FLAG_FAILED_FCS_CRC) अणु
		ar->stats.rx_crc_err_drop++;
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_DATA,
		   "rx skb %pK len %u peer %pM %s %s sn %u %s%s%s%s%s%s %srate_idx %u vht_nss %u freq %u band %u flag 0x%x fcs-err %i mic-err %i amsdu-more %i\n",
		   skb,
		   skb->len,
		   ieee80211_get_SA(hdr),
		   ath10k_get_tid(hdr, tid, माप(tid)),
		   is_multicast_ether_addr(ieee80211_get_DA(hdr)) ?
							"mcast" : "ucast",
		   (__le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4,
		   (status->encoding == RX_ENC_LEGACY) ? "legacy" : "",
		   (status->encoding == RX_ENC_HT) ? "ht" : "",
		   (status->encoding == RX_ENC_VHT) ? "vht" : "",
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
	ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य, "rx skb: ",
			skb->data, skb->len);
	trace_ath10k_rx_hdr(ar, skb->data, skb->len);
	trace_ath10k_rx_payload(ar, skb->data, skb->len);

	ieee80211_rx_napi(ar->hw, शून्य, skb, &ar->napi);
पूर्ण

अटल पूर्णांक ath10k_htt_rx_nwअगरi_hdrlen(काष्ठा ath10k *ar,
				      काष्ठा ieee80211_hdr *hdr)
अणु
	पूर्णांक len = ieee80211_hdrlen(hdr->frame_control);

	अगर (!test_bit(ATH10K_FW_FEATURE_NO_NWIFI_DECAP_4ADDR_PADDING,
		      ar->running_fw->fw_file.fw_features))
		len = round_up(len, 4);

	वापस len;
पूर्ण

अटल व्योम ath10k_htt_rx_h_undecap_raw(काष्ठा ath10k *ar,
					काष्ठा sk_buff *msdu,
					काष्ठा ieee80211_rx_status *status,
					क्रमागत htt_rx_mpdu_encrypt_type enctype,
					bool is_decrypted,
					स्थिर u8 first_hdr[64])
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा htt_rx_desc *rxd;
	माप_प्रकार hdr_len;
	माप_प्रकार crypto_len;
	bool is_first;
	bool is_last;
	bool msdu_limit_err;
	पूर्णांक bytes_aligned = ar->hw_params.decap_align_bytes;
	u8 *qos;

	rxd = (व्योम *)msdu->data - माप(*rxd);
	is_first = !!(rxd->msdu_end.common.info0 &
		      __cpu_to_le32(RX_MSDU_END_INFO0_FIRST_MSDU));
	is_last = !!(rxd->msdu_end.common.info0 &
		     __cpu_to_le32(RX_MSDU_END_INFO0_LAST_MSDU));

	/* Delivered decapped frame:
	 * [802.11 header]
	 * [crypto param] <-- can be trimmed अगर !fcs_err &&
	 *                    !decrypt_err && !peer_idx_invalid
	 * [amsdu header] <-- only अगर A-MSDU
	 * [rfc1042/llc]
	 * [payload]
	 * [FCS] <-- at end, needs to be trimmed
	 */

	/* Some hardwares(QCA99x0 variants) limit number of msdus in a-msdu when
	 * deaggregate, so that unwanted MSDU-deaggregation is aव्योमed क्रम
	 * error packets. If limit exceeds, hw sends all reमुख्यing MSDUs as
	 * a single last MSDU with this msdu limit error set.
	 */
	msdu_limit_err = ath10k_rx_desc_msdu_limit_error(&ar->hw_params, rxd);

	/* If MSDU limit error happens, then करोn't warn on, the partial raw MSDU
	 * without first MSDU is expected in that हाल, and handled later here.
	 */
	/* This probably shouldn't happen but warn just in हाल */
	अगर (WARN_ON_ONCE(!is_first && !msdu_limit_err))
		वापस;

	/* This probably shouldn't happen but warn just in हाल */
	अगर (WARN_ON_ONCE(!(is_first && is_last) && !msdu_limit_err))
		वापस;

	skb_trim(msdu, msdu->len - FCS_LEN);

	/* Push original 80211 header */
	अगर (unlikely(msdu_limit_err)) अणु
		hdr = (काष्ठा ieee80211_hdr *)first_hdr;
		hdr_len = ieee80211_hdrlen(hdr->frame_control);
		crypto_len = ath10k_htt_rx_crypto_param_len(ar, enctype);

		अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
			qos = ieee80211_get_qos_ctl(hdr);
			qos[0] |= IEEE80211_QOS_CTL_A_MSDU_PRESENT;
		पूर्ण

		अगर (crypto_len)
			स_नकल(skb_push(msdu, crypto_len),
			       (व्योम *)hdr + round_up(hdr_len, bytes_aligned),
			       crypto_len);

		स_नकल(skb_push(msdu, hdr_len), hdr, hdr_len);
	पूर्ण

	/* In most हालs this will be true क्रम snअगरfed frames. It makes sense
	 * to deliver them as-is without stripping the crypto param. This is
	 * necessary क्रम software based decryption.
	 *
	 * If there's no error then the frame is decrypted. At least that is
	 * the हाल क्रम frames that come in via fragmented rx indication.
	 */
	अगर (!is_decrypted)
		वापस;

	/* The payload is decrypted so strip crypto params. Start from tail
	 * since hdr is used to compute some stuff.
	 */

	hdr = (व्योम *)msdu->data;

	/* Tail */
	अगर (status->flag & RX_FLAG_IV_STRIPPED) अणु
		skb_trim(msdu, msdu->len -
			 ath10k_htt_rx_crypto_mic_len(ar, enctype));

		skb_trim(msdu, msdu->len -
			 ath10k_htt_rx_crypto_icv_len(ar, enctype));
	पूर्ण अन्यथा अणु
		/* MIC */
		अगर (status->flag & RX_FLAG_MIC_STRIPPED)
			skb_trim(msdu, msdu->len -
				 ath10k_htt_rx_crypto_mic_len(ar, enctype));

		/* ICV */
		अगर (status->flag & RX_FLAG_ICV_STRIPPED)
			skb_trim(msdu, msdu->len -
				 ath10k_htt_rx_crypto_icv_len(ar, enctype));
	पूर्ण

	/* MMIC */
	अगर ((status->flag & RX_FLAG_MMIC_STRIPPED) &&
	    !ieee80211_has_morefrags(hdr->frame_control) &&
	    enctype == HTT_RX_MPDU_ENCRYPT_TKIP_WPA)
		skb_trim(msdu, msdu->len - MICHAEL_MIC_LEN);

	/* Head */
	अगर (status->flag & RX_FLAG_IV_STRIPPED) अणु
		hdr_len = ieee80211_hdrlen(hdr->frame_control);
		crypto_len = ath10k_htt_rx_crypto_param_len(ar, enctype);

		स_हटाओ((व्योम *)msdu->data + crypto_len,
			(व्योम *)msdu->data, hdr_len);
		skb_pull(msdu, crypto_len);
	पूर्ण
पूर्ण

अटल व्योम ath10k_htt_rx_h_undecap_nwअगरi(काष्ठा ath10k *ar,
					  काष्ठा sk_buff *msdu,
					  काष्ठा ieee80211_rx_status *status,
					  स्थिर u8 first_hdr[64],
					  क्रमागत htt_rx_mpdu_encrypt_type enctype)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा htt_rx_desc *rxd;
	माप_प्रकार hdr_len;
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
	पूर्णांक l3_pad_bytes;
	पूर्णांक bytes_aligned = ar->hw_params.decap_align_bytes;

	/* Delivered decapped frame:
	 * [nwअगरi 802.11 header] <-- replaced with 802.11 hdr
	 * [rfc1042/llc]
	 *
	 * Note: The nwअगरi header करोesn't have QoS Control and is
	 * (always?) a 3addr frame.
	 *
	 * Note2: There's no A-MSDU subframe header. Even if it's part
	 * of an A-MSDU.
	 */

	/* pull decapped header and copy SA & DA */
	rxd = (व्योम *)msdu->data - माप(*rxd);

	l3_pad_bytes = ath10k_rx_desc_get_l3_pad_bytes(&ar->hw_params, rxd);
	skb_put(msdu, l3_pad_bytes);

	hdr = (काष्ठा ieee80211_hdr *)(msdu->data + l3_pad_bytes);

	hdr_len = ath10k_htt_rx_nwअगरi_hdrlen(ar, hdr);
	ether_addr_copy(da, ieee80211_get_DA(hdr));
	ether_addr_copy(sa, ieee80211_get_SA(hdr));
	skb_pull(msdu, hdr_len);

	/* push original 802.11 header */
	hdr = (काष्ठा ieee80211_hdr *)first_hdr;
	hdr_len = ieee80211_hdrlen(hdr->frame_control);

	अगर (!(status->flag & RX_FLAG_IV_STRIPPED)) अणु
		स_नकल(skb_push(msdu,
				ath10k_htt_rx_crypto_param_len(ar, enctype)),
		       (व्योम *)hdr + round_up(hdr_len, bytes_aligned),
			ath10k_htt_rx_crypto_param_len(ar, enctype));
	पूर्ण

	स_नकल(skb_push(msdu, hdr_len), hdr, hdr_len);

	/* original 802.11 header has a dअगरferent DA and in
	 * हाल of 4addr it may also have dअगरferent SA
	 */
	hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	ether_addr_copy(ieee80211_get_DA(hdr), da);
	ether_addr_copy(ieee80211_get_SA(hdr), sa);
पूर्ण

अटल व्योम *ath10k_htt_rx_h_find_rfc1042(काष्ठा ath10k *ar,
					  काष्ठा sk_buff *msdu,
					  क्रमागत htt_rx_mpdu_encrypt_type enctype)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा htt_rx_desc *rxd;
	माप_प्रकार hdr_len, crypto_len;
	व्योम *rfc1042;
	bool is_first, is_last, is_amsdu;
	पूर्णांक bytes_aligned = ar->hw_params.decap_align_bytes;

	rxd = (व्योम *)msdu->data - माप(*rxd);
	hdr = (व्योम *)rxd->rx_hdr_status;

	is_first = !!(rxd->msdu_end.common.info0 &
		      __cpu_to_le32(RX_MSDU_END_INFO0_FIRST_MSDU));
	is_last = !!(rxd->msdu_end.common.info0 &
		     __cpu_to_le32(RX_MSDU_END_INFO0_LAST_MSDU));
	is_amsdu = !(is_first && is_last);

	rfc1042 = hdr;

	अगर (is_first) अणु
		hdr_len = ieee80211_hdrlen(hdr->frame_control);
		crypto_len = ath10k_htt_rx_crypto_param_len(ar, enctype);

		rfc1042 += round_up(hdr_len, bytes_aligned) +
			   round_up(crypto_len, bytes_aligned);
	पूर्ण

	अगर (is_amsdu)
		rfc1042 += माप(काष्ठा amsdu_subframe_hdr);

	वापस rfc1042;
पूर्ण

अटल व्योम ath10k_htt_rx_h_undecap_eth(काष्ठा ath10k *ar,
					काष्ठा sk_buff *msdu,
					काष्ठा ieee80211_rx_status *status,
					स्थिर u8 first_hdr[64],
					क्रमागत htt_rx_mpdu_encrypt_type enctype)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ethhdr *eth;
	माप_प्रकार hdr_len;
	व्योम *rfc1042;
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
	पूर्णांक l3_pad_bytes;
	काष्ठा htt_rx_desc *rxd;
	पूर्णांक bytes_aligned = ar->hw_params.decap_align_bytes;

	/* Delivered decapped frame:
	 * [eth header] <-- replaced with 802.11 hdr & rfc1042/llc
	 * [payload]
	 */

	rfc1042 = ath10k_htt_rx_h_find_rfc1042(ar, msdu, enctype);
	अगर (WARN_ON_ONCE(!rfc1042))
		वापस;

	rxd = (व्योम *)msdu->data - माप(*rxd);
	l3_pad_bytes = ath10k_rx_desc_get_l3_pad_bytes(&ar->hw_params, rxd);
	skb_put(msdu, l3_pad_bytes);
	skb_pull(msdu, l3_pad_bytes);

	/* pull decapped header and copy SA & DA */
	eth = (काष्ठा ethhdr *)msdu->data;
	ether_addr_copy(da, eth->h_dest);
	ether_addr_copy(sa, eth->h_source);
	skb_pull(msdu, माप(काष्ठा ethhdr));

	/* push rfc1042/llc/snap */
	स_नकल(skb_push(msdu, माप(काष्ठा rfc1042_hdr)), rfc1042,
	       माप(काष्ठा rfc1042_hdr));

	/* push original 802.11 header */
	hdr = (काष्ठा ieee80211_hdr *)first_hdr;
	hdr_len = ieee80211_hdrlen(hdr->frame_control);

	अगर (!(status->flag & RX_FLAG_IV_STRIPPED)) अणु
		स_नकल(skb_push(msdu,
				ath10k_htt_rx_crypto_param_len(ar, enctype)),
		       (व्योम *)hdr + round_up(hdr_len, bytes_aligned),
			ath10k_htt_rx_crypto_param_len(ar, enctype));
	पूर्ण

	स_नकल(skb_push(msdu, hdr_len), hdr, hdr_len);

	/* original 802.11 header has a dअगरferent DA and in
	 * हाल of 4addr it may also have dअगरferent SA
	 */
	hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	ether_addr_copy(ieee80211_get_DA(hdr), da);
	ether_addr_copy(ieee80211_get_SA(hdr), sa);
पूर्ण

अटल व्योम ath10k_htt_rx_h_undecap_snap(काष्ठा ath10k *ar,
					 काष्ठा sk_buff *msdu,
					 काष्ठा ieee80211_rx_status *status,
					 स्थिर u8 first_hdr[64],
					 क्रमागत htt_rx_mpdu_encrypt_type enctype)
अणु
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdr_len;
	पूर्णांक l3_pad_bytes;
	काष्ठा htt_rx_desc *rxd;
	पूर्णांक bytes_aligned = ar->hw_params.decap_align_bytes;

	/* Delivered decapped frame:
	 * [amsdu header] <-- replaced with 802.11 hdr
	 * [rfc1042/llc]
	 * [payload]
	 */

	rxd = (व्योम *)msdu->data - माप(*rxd);
	l3_pad_bytes = ath10k_rx_desc_get_l3_pad_bytes(&ar->hw_params, rxd);

	skb_put(msdu, l3_pad_bytes);
	skb_pull(msdu, माप(काष्ठा amsdu_subframe_hdr) + l3_pad_bytes);

	hdr = (काष्ठा ieee80211_hdr *)first_hdr;
	hdr_len = ieee80211_hdrlen(hdr->frame_control);

	अगर (!(status->flag & RX_FLAG_IV_STRIPPED)) अणु
		स_नकल(skb_push(msdu,
				ath10k_htt_rx_crypto_param_len(ar, enctype)),
		       (व्योम *)hdr + round_up(hdr_len, bytes_aligned),
			ath10k_htt_rx_crypto_param_len(ar, enctype));
	पूर्ण

	स_नकल(skb_push(msdu, hdr_len), hdr, hdr_len);
पूर्ण

अटल व्योम ath10k_htt_rx_h_undecap(काष्ठा ath10k *ar,
				    काष्ठा sk_buff *msdu,
				    काष्ठा ieee80211_rx_status *status,
				    u8 first_hdr[64],
				    क्रमागत htt_rx_mpdu_encrypt_type enctype,
				    bool is_decrypted)
अणु
	काष्ठा htt_rx_desc *rxd;
	क्रमागत rx_msdu_decap_क्रमmat decap;

	/* First msdu's decapped header:
	 * [802.11 header] <-- padded to 4 bytes दीर्घ
	 * [crypto param] <-- padded to 4 bytes दीर्घ
	 * [amsdu header] <-- only अगर A-MSDU
	 * [rfc1042/llc]
	 *
	 * Other (2nd, 3rd, ..) msdu's decapped header:
	 * [amsdu header] <-- only अगर A-MSDU
	 * [rfc1042/llc]
	 */

	rxd = (व्योम *)msdu->data - माप(*rxd);
	decap = MS(__le32_to_cpu(rxd->msdu_start.common.info1),
		   RX_MSDU_START_INFO1_DECAP_FORMAT);

	चयन (decap) अणु
	हाल RX_MSDU_DECAP_RAW:
		ath10k_htt_rx_h_undecap_raw(ar, msdu, status, enctype,
					    is_decrypted, first_hdr);
		अवरोध;
	हाल RX_MSDU_DECAP_NATIVE_WIFI:
		ath10k_htt_rx_h_undecap_nwअगरi(ar, msdu, status, first_hdr,
					      enctype);
		अवरोध;
	हाल RX_MSDU_DECAP_ETHERNET2_DIX:
		ath10k_htt_rx_h_undecap_eth(ar, msdu, status, first_hdr, enctype);
		अवरोध;
	हाल RX_MSDU_DECAP_8023_SNAP_LLC:
		ath10k_htt_rx_h_undecap_snap(ar, msdu, status, first_hdr,
					     enctype);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_htt_rx_get_csum_state(काष्ठा sk_buff *skb)
अणु
	काष्ठा htt_rx_desc *rxd;
	u32 flags, info;
	bool is_ip4, is_ip6;
	bool is_tcp, is_udp;
	bool ip_csum_ok, tcpudp_csum_ok;

	rxd = (व्योम *)skb->data - माप(*rxd);
	flags = __le32_to_cpu(rxd->attention.flags);
	info = __le32_to_cpu(rxd->msdu_start.common.info1);

	is_ip4 = !!(info & RX_MSDU_START_INFO1_IPV4_PROTO);
	is_ip6 = !!(info & RX_MSDU_START_INFO1_IPV6_PROTO);
	is_tcp = !!(info & RX_MSDU_START_INFO1_TCP_PROTO);
	is_udp = !!(info & RX_MSDU_START_INFO1_UDP_PROTO);
	ip_csum_ok = !(flags & RX_ATTENTION_FLAGS_IP_CHKSUM_FAIL);
	tcpudp_csum_ok = !(flags & RX_ATTENTION_FLAGS_TCP_UDP_CHKSUM_FAIL);

	अगर (!is_ip4 && !is_ip6)
		वापस CHECKSUM_NONE;
	अगर (!is_tcp && !is_udp)
		वापस CHECKSUM_NONE;
	अगर (!ip_csum_ok)
		वापस CHECKSUM_NONE;
	अगर (!tcpudp_csum_ok)
		वापस CHECKSUM_NONE;

	वापस CHECKSUM_UNNECESSARY;
पूर्ण

अटल व्योम ath10k_htt_rx_h_csum_offload(काष्ठा sk_buff *msdu)
अणु
	msdu->ip_summed = ath10k_htt_rx_get_csum_state(msdu);
पूर्ण

अटल u64 ath10k_htt_rx_h_get_pn(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				  u16 offset,
				  क्रमागत htt_rx_mpdu_encrypt_type enctype)
अणु
	काष्ठा ieee80211_hdr *hdr;
	u64 pn = 0;
	u8 *ehdr;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + offset);
	ehdr = skb->data + offset + ieee80211_hdrlen(hdr->frame_control);

	अगर (enctype == HTT_RX_MPDU_ENCRYPT_AES_CCM_WPA2) अणु
		pn = ehdr[0];
		pn |= (u64)ehdr[1] << 8;
		pn |= (u64)ehdr[4] << 16;
		pn |= (u64)ehdr[5] << 24;
		pn |= (u64)ehdr[6] << 32;
		pn |= (u64)ehdr[7] << 40;
	पूर्ण
	वापस pn;
पूर्ण

अटल bool ath10k_htt_rx_h_frag_multicast_check(काष्ठा ath10k *ar,
						 काष्ठा sk_buff *skb,
						 u16 offset)
अणु
	काष्ठा ieee80211_hdr *hdr;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + offset);
	वापस !is_multicast_ether_addr(hdr->addr1);
पूर्ण

अटल bool ath10k_htt_rx_h_frag_pn_check(काष्ठा ath10k *ar,
					  काष्ठा sk_buff *skb,
					  u16 peer_id,
					  u16 offset,
					  क्रमागत htt_rx_mpdu_encrypt_type enctype)
अणु
	काष्ठा ath10k_peer *peer;
	जोड़ htt_rx_pn_t *last_pn, new_pn = अणु0पूर्ण;
	काष्ठा ieee80211_hdr *hdr;
	bool more_frags;
	u8 tid, frag_number;
	u32 seq;

	peer = ath10k_peer_find_by_id(ar, peer_id);
	अगर (!peer) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTT, "invalid peer for frag pn check\n");
		वापस false;
	पूर्ण

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + offset);
	अगर (ieee80211_is_data_qos(hdr->frame_control))
		tid = ieee80211_get_tid(hdr);
	अन्यथा
		tid = ATH10K_TXRX_NON_QOS_TID;

	last_pn = &peer->frag_tids_last_pn[tid];
	new_pn.pn48 = ath10k_htt_rx_h_get_pn(ar, skb, offset, enctype);
	more_frags = ieee80211_has_morefrags(hdr->frame_control);
	frag_number = le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_FRAG;
	seq = (__le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;

	अगर (frag_number == 0) अणु
		last_pn->pn48 = new_pn.pn48;
		peer->frag_tids_seq[tid] = seq;
	पूर्ण अन्यथा अणु
		अगर (seq != peer->frag_tids_seq[tid])
			वापस false;

		अगर (new_pn.pn48 != last_pn->pn48 + 1)
			वापस false;

		last_pn->pn48 = new_pn.pn48;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम ath10k_htt_rx_h_mpdu(काष्ठा ath10k *ar,
				 काष्ठा sk_buff_head *amsdu,
				 काष्ठा ieee80211_rx_status *status,
				 bool fill_crypt_header,
				 u8 *rx_hdr,
				 क्रमागत ath10k_pkt_rx_err *err,
				 u16 peer_id,
				 bool frag)
अणु
	काष्ठा sk_buff *first;
	काष्ठा sk_buff *last;
	काष्ठा sk_buff *msdu, *temp;
	काष्ठा htt_rx_desc *rxd;
	काष्ठा ieee80211_hdr *hdr;
	क्रमागत htt_rx_mpdu_encrypt_type enctype;
	u8 first_hdr[64];
	u8 *qos;
	bool has_fcs_err;
	bool has_crypto_err;
	bool has_tkip_err;
	bool has_peer_idx_invalid;
	bool is_decrypted;
	bool is_mgmt;
	u32 attention;
	bool frag_pn_check = true, multicast_check = true;

	अगर (skb_queue_empty(amsdu))
		वापस;

	first = skb_peek(amsdu);
	rxd = (व्योम *)first->data - माप(*rxd);

	is_mgmt = !!(rxd->attention.flags &
		     __cpu_to_le32(RX_ATTENTION_FLAGS_MGMT_TYPE));

	enctype = MS(__le32_to_cpu(rxd->mpdu_start.info0),
		     RX_MPDU_START_INFO0_ENCRYPT_TYPE);

	/* First MSDU's Rx descriptor in an A-MSDU contains full 802.11
	 * decapped header. It'll be used क्रम undecapping of each MSDU.
	 */
	hdr = (व्योम *)rxd->rx_hdr_status;
	स_नकल(first_hdr, hdr, RX_HTT_HDR_STATUS_LEN);

	अगर (rx_hdr)
		स_नकल(rx_hdr, hdr, RX_HTT_HDR_STATUS_LEN);

	/* Each A-MSDU subframe will use the original header as the base and be
	 * reported as a separate MSDU so strip the A-MSDU bit from QoS Ctl.
	 */
	hdr = (व्योम *)first_hdr;

	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		qos = ieee80211_get_qos_ctl(hdr);
		qos[0] &= ~IEEE80211_QOS_CTL_A_MSDU_PRESENT;
	पूर्ण

	/* Some attention flags are valid only in the last MSDU. */
	last = skb_peek_tail(amsdu);
	rxd = (व्योम *)last->data - माप(*rxd);
	attention = __le32_to_cpu(rxd->attention.flags);

	has_fcs_err = !!(attention & RX_ATTENTION_FLAGS_FCS_ERR);
	has_crypto_err = !!(attention & RX_ATTENTION_FLAGS_DECRYPT_ERR);
	has_tkip_err = !!(attention & RX_ATTENTION_FLAGS_TKIP_MIC_ERR);
	has_peer_idx_invalid = !!(attention & RX_ATTENTION_FLAGS_PEER_IDX_INVALID);

	/* Note: If hardware captures an encrypted frame that it can't decrypt,
	 * e.g. due to fcs error, missing peer or invalid key data it will
	 * report the frame as raw.
	 */
	is_decrypted = (enctype != HTT_RX_MPDU_ENCRYPT_NONE &&
			!has_fcs_err &&
			!has_crypto_err &&
			!has_peer_idx_invalid);

	/* Clear per-MPDU flags जबतक leaving per-PPDU flags पूर्णांकact. */
	status->flag &= ~(RX_FLAG_FAILED_FCS_CRC |
			  RX_FLAG_MMIC_ERROR |
			  RX_FLAG_DECRYPTED |
			  RX_FLAG_IV_STRIPPED |
			  RX_FLAG_ONLY_MONITOR |
			  RX_FLAG_MMIC_STRIPPED);

	अगर (has_fcs_err)
		status->flag |= RX_FLAG_FAILED_FCS_CRC;

	अगर (has_tkip_err)
		status->flag |= RX_FLAG_MMIC_ERROR;

	अगर (err) अणु
		अगर (has_fcs_err)
			*err = ATH10K_PKT_RX_ERR_FCS;
		अन्यथा अगर (has_tkip_err)
			*err = ATH10K_PKT_RX_ERR_TKIP;
		अन्यथा अगर (has_crypto_err)
			*err = ATH10K_PKT_RX_ERR_CRYPT;
		अन्यथा अगर (has_peer_idx_invalid)
			*err = ATH10K_PKT_RX_ERR_PEER_IDX_INVAL;
	पूर्ण

	/* Firmware reports all necessary management frames via WMI alपढ़ोy.
	 * They are not reported to monitor पूर्णांकerfaces at all so pass the ones
	 * coming via HTT to monitor पूर्णांकerfaces instead. This simplअगरies
	 * matters a lot.
	 */
	अगर (is_mgmt)
		status->flag |= RX_FLAG_ONLY_MONITOR;

	अगर (is_decrypted) अणु
		status->flag |= RX_FLAG_DECRYPTED;

		अगर (likely(!is_mgmt))
			status->flag |= RX_FLAG_MMIC_STRIPPED;

		अगर (fill_crypt_header)
			status->flag |= RX_FLAG_MIC_STRIPPED |
					RX_FLAG_ICV_STRIPPED;
		अन्यथा
			status->flag |= RX_FLAG_IV_STRIPPED;
	पूर्ण

	skb_queue_walk(amsdu, msdu) अणु
		अगर (frag && !fill_crypt_header && is_decrypted &&
		    enctype == HTT_RX_MPDU_ENCRYPT_AES_CCM_WPA2)
			frag_pn_check = ath10k_htt_rx_h_frag_pn_check(ar,
								      msdu,
								      peer_id,
								      0,
								      enctype);

		अगर (frag)
			multicast_check = ath10k_htt_rx_h_frag_multicast_check(ar,
									       msdu,
									       0);

		अगर (!frag_pn_check || !multicast_check) अणु
			/* Discard the fragment with invalid PN or multicast DA
			 */
			temp = msdu->prev;
			__skb_unlink(msdu, amsdu);
			dev_kमुक्त_skb_any(msdu);
			msdu = temp;
			frag_pn_check = true;
			multicast_check = true;
			जारी;
		पूर्ण

		ath10k_htt_rx_h_csum_offload(msdu);

		अगर (frag && !fill_crypt_header &&
		    enctype == HTT_RX_MPDU_ENCRYPT_TKIP_WPA)
			status->flag &= ~RX_FLAG_MMIC_STRIPPED;

		ath10k_htt_rx_h_undecap(ar, msdu, status, first_hdr, enctype,
					is_decrypted);

		/* Undecapping involves copying the original 802.11 header back
		 * to sk_buff. If frame is रक्षित and hardware has decrypted
		 * it then हटाओ the रक्षित bit.
		 */
		अगर (!is_decrypted)
			जारी;
		अगर (is_mgmt)
			जारी;

		अगर (fill_crypt_header)
			जारी;

		hdr = (व्योम *)msdu->data;
		hdr->frame_control &= ~__cpu_to_le16(IEEE80211_FCTL_PROTECTED);

		अगर (frag && !fill_crypt_header &&
		    enctype == HTT_RX_MPDU_ENCRYPT_TKIP_WPA)
			status->flag &= ~RX_FLAG_IV_STRIPPED &
					~RX_FLAG_MMIC_STRIPPED;
	पूर्ण
पूर्ण

अटल व्योम ath10k_htt_rx_h_enqueue(काष्ठा ath10k *ar,
				    काष्ठा sk_buff_head *amsdu,
				    काष्ठा ieee80211_rx_status *status)
अणु
	काष्ठा sk_buff *msdu;
	काष्ठा sk_buff *first_subframe;

	first_subframe = skb_peek(amsdu);

	जबतक ((msdu = __skb_dequeue(amsdu))) अणु
		/* Setup per-MSDU flags */
		अगर (skb_queue_empty(amsdu))
			status->flag &= ~RX_FLAG_AMSDU_MORE;
		अन्यथा
			status->flag |= RX_FLAG_AMSDU_MORE;

		अगर (msdu == first_subframe) अणु
			first_subframe = शून्य;
			status->flag &= ~RX_FLAG_ALLOW_SAME_PN;
		पूर्ण अन्यथा अणु
			status->flag |= RX_FLAG_ALLOW_SAME_PN;
		पूर्ण

		ath10k_htt_rx_h_queue_msdu(ar, status, msdu);
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_unchain_msdu(काष्ठा sk_buff_head *amsdu,
			       अचिन्हित दीर्घ *unchain_cnt)
अणु
	काष्ठा sk_buff *skb, *first;
	पूर्णांक space;
	पूर्णांक total_len = 0;
	पूर्णांक amsdu_len = skb_queue_len(amsdu);

	/* TODO:  Might could optimize this by using
	 * skb_try_coalesce or similar method to
	 * decrease copying, or maybe get mac80211 to
	 * provide a way to just receive a list of
	 * skb?
	 */

	first = __skb_dequeue(amsdu);

	/* Allocate total length all at once. */
	skb_queue_walk(amsdu, skb)
		total_len += skb->len;

	space = total_len - skb_tailroom(first);
	अगर ((space > 0) &&
	    (pskb_expand_head(first, 0, space, GFP_ATOMIC) < 0)) अणु
		/* TODO:  bump some rx-oom error stat */
		/* put it back together so we can मुक्त the
		 * whole list at once.
		 */
		__skb_queue_head(amsdu, first);
		वापस -1;
	पूर्ण

	/* Walk list again, copying contents पूर्णांकo
	 * msdu_head
	 */
	जबतक ((skb = __skb_dequeue(amsdu))) अणु
		skb_copy_from_linear_data(skb, skb_put(first, skb->len),
					  skb->len);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	__skb_queue_head(amsdu, first);

	*unchain_cnt += amsdu_len - 1;

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_rx_h_unchain(काष्ठा ath10k *ar,
				    काष्ठा sk_buff_head *amsdu,
				    अचिन्हित दीर्घ *drop_cnt,
				    अचिन्हित दीर्घ *unchain_cnt)
अणु
	काष्ठा sk_buff *first;
	काष्ठा htt_rx_desc *rxd;
	क्रमागत rx_msdu_decap_क्रमmat decap;

	first = skb_peek(amsdu);
	rxd = (व्योम *)first->data - माप(*rxd);
	decap = MS(__le32_to_cpu(rxd->msdu_start.common.info1),
		   RX_MSDU_START_INFO1_DECAP_FORMAT);

	/* FIXME: Current unchaining logic can only handle simple हाल of raw
	 * msdu chaining. If decapping is other than raw the chaining may be
	 * more complex and this isn't handled by the current code. Don't even
	 * try re-स्थिरructing such frames - it'll be pretty much garbage.
	 */
	अगर (decap != RX_MSDU_DECAP_RAW ||
	    skb_queue_len(amsdu) != 1 + rxd->frag_info.ring2_more_count) अणु
		*drop_cnt += skb_queue_len(amsdu);
		__skb_queue_purge(amsdu);
		वापस;
	पूर्ण

	ath10k_unchain_msdu(amsdu, unchain_cnt);
पूर्ण

अटल bool ath10k_htt_rx_validate_amsdu(काष्ठा ath10k *ar,
					 काष्ठा sk_buff_head *amsdu)
अणु
	u8 *subframe_hdr;
	काष्ठा sk_buff *first;
	bool is_first, is_last;
	काष्ठा htt_rx_desc *rxd;
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार hdr_len, crypto_len;
	क्रमागत htt_rx_mpdu_encrypt_type enctype;
	पूर्णांक bytes_aligned = ar->hw_params.decap_align_bytes;

	first = skb_peek(amsdu);

	rxd = (व्योम *)first->data - माप(*rxd);
	hdr = (व्योम *)rxd->rx_hdr_status;

	is_first = !!(rxd->msdu_end.common.info0 &
		      __cpu_to_le32(RX_MSDU_END_INFO0_FIRST_MSDU));
	is_last = !!(rxd->msdu_end.common.info0 &
		     __cpu_to_le32(RX_MSDU_END_INFO0_LAST_MSDU));

	/* Return in हाल of non-aggregated msdu */
	अगर (is_first && is_last)
		वापस true;

	/* First msdu flag is not set क्रम the first msdu of the list */
	अगर (!is_first)
		वापस false;

	enctype = MS(__le32_to_cpu(rxd->mpdu_start.info0),
		     RX_MPDU_START_INFO0_ENCRYPT_TYPE);

	hdr_len = ieee80211_hdrlen(hdr->frame_control);
	crypto_len = ath10k_htt_rx_crypto_param_len(ar, enctype);

	subframe_hdr = (u8 *)hdr + round_up(hdr_len, bytes_aligned) +
		       crypto_len;

	/* Validate अगर the amsdu has a proper first subframe.
	 * There are chances a single msdu can be received as amsdu when
	 * the unauthenticated amsdu flag of a QoS header
	 * माला_लो flipped in non-SPP AMSDU's, in such हालs the first
	 * subframe has llc/snap header in place of a valid da.
	 * वापस false अगर the da matches rfc1042 pattern
	 */
	अगर (ether_addr_equal(subframe_hdr, rfc1042_header))
		वापस false;

	वापस true;
पूर्ण

अटल bool ath10k_htt_rx_amsdu_allowed(काष्ठा ath10k *ar,
					काष्ठा sk_buff_head *amsdu,
					काष्ठा ieee80211_rx_status *rx_status)
अणु
	अगर (!rx_status->freq) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTT, "no channel configured; ignoring frame(s)!\n");
		वापस false;
	पूर्ण

	अगर (test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags)) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx cac running\n");
		वापस false;
	पूर्ण

	अगर (!ath10k_htt_rx_validate_amsdu(ar, amsdu)) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTT, "invalid amsdu received\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम ath10k_htt_rx_h_filter(काष्ठा ath10k *ar,
				   काष्ठा sk_buff_head *amsdu,
				   काष्ठा ieee80211_rx_status *rx_status,
				   अचिन्हित दीर्घ *drop_cnt)
अणु
	अगर (skb_queue_empty(amsdu))
		वापस;

	अगर (ath10k_htt_rx_amsdu_allowed(ar, amsdu, rx_status))
		वापस;

	अगर (drop_cnt)
		*drop_cnt += skb_queue_len(amsdu);

	__skb_queue_purge(amsdu);
पूर्ण

अटल पूर्णांक ath10k_htt_rx_handle_amsdu(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा ieee80211_rx_status *rx_status = &htt->rx_status;
	काष्ठा sk_buff_head amsdu;
	पूर्णांक ret;
	अचिन्हित दीर्घ drop_cnt = 0;
	अचिन्हित दीर्घ unchain_cnt = 0;
	अचिन्हित दीर्घ drop_cnt_filter = 0;
	अचिन्हित दीर्घ msdus_to_queue, num_msdus;
	क्रमागत ath10k_pkt_rx_err err = ATH10K_PKT_RX_ERR_MAX;
	u8 first_hdr[RX_HTT_HDR_STATUS_LEN];

	__skb_queue_head_init(&amsdu);

	spin_lock_bh(&htt->rx_ring.lock);
	अगर (htt->rx_confused) अणु
		spin_unlock_bh(&htt->rx_ring.lock);
		वापस -EIO;
	पूर्ण
	ret = ath10k_htt_rx_amsdu_pop(htt, &amsdu);
	spin_unlock_bh(&htt->rx_ring.lock);

	अगर (ret < 0) अणु
		ath10k_warn(ar, "rx ring became corrupted: %d\n", ret);
		__skb_queue_purge(&amsdu);
		/* FIXME: It's probably a good idea to reboot the
		 * device instead of leaving it inoperable.
		 */
		htt->rx_confused = true;
		वापस ret;
	पूर्ण

	num_msdus = skb_queue_len(&amsdu);

	ath10k_htt_rx_h_ppdu(ar, &amsdu, rx_status, 0xffff);

	/* only क्रम ret = 1 indicates chained msdus */
	अगर (ret > 0)
		ath10k_htt_rx_h_unchain(ar, &amsdu, &drop_cnt, &unchain_cnt);

	ath10k_htt_rx_h_filter(ar, &amsdu, rx_status, &drop_cnt_filter);
	ath10k_htt_rx_h_mpdu(ar, &amsdu, rx_status, true, first_hdr, &err, 0,
			     false);
	msdus_to_queue = skb_queue_len(&amsdu);
	ath10k_htt_rx_h_enqueue(ar, &amsdu, rx_status);

	ath10k_sta_update_rx_tid_stats(ar, first_hdr, num_msdus, err,
				       unchain_cnt, drop_cnt, drop_cnt_filter,
				       msdus_to_queue);

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_rx_mpdu_desc_pn_hl(काष्ठा htt_hl_rx_desc *rx_desc,
					  जोड़ htt_rx_pn_t *pn,
					  पूर्णांक pn_len_bits)
अणु
	चयन (pn_len_bits) अणु
	हाल 48:
		pn->pn48 = __le32_to_cpu(rx_desc->pn_31_0) +
			   ((u64)(__le32_to_cpu(rx_desc->u0.pn_63_32) & 0xFFFF) << 32);
		अवरोध;
	हाल 24:
		pn->pn24 = __le32_to_cpu(rx_desc->pn_31_0);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool ath10k_htt_rx_pn_cmp48(जोड़ htt_rx_pn_t *new_pn,
				   जोड़ htt_rx_pn_t *old_pn)
अणु
	वापस ((new_pn->pn48 & 0xffffffffffffULL) <=
		(old_pn->pn48 & 0xffffffffffffULL));
पूर्ण

अटल bool ath10k_htt_rx_pn_check_replay_hl(काष्ठा ath10k *ar,
					     काष्ठा ath10k_peer *peer,
					     काष्ठा htt_rx_indication_hl *rx)
अणु
	bool last_pn_valid, pn_invalid = false;
	क्रमागत htt_txrx_sec_cast_type sec_index;
	क्रमागत htt_security_types sec_type;
	जोड़ htt_rx_pn_t new_pn = अणु0पूर्ण;
	काष्ठा htt_hl_rx_desc *rx_desc;
	जोड़ htt_rx_pn_t *last_pn;
	u32 rx_desc_info, tid;
	पूर्णांक num_mpdu_ranges;

	lockdep_निश्चित_held(&ar->data_lock);

	अगर (!peer)
		वापस false;

	अगर (!(rx->fw_desc.flags & FW_RX_DESC_FLAGS_FIRST_MSDU))
		वापस false;

	num_mpdu_ranges = MS(__le32_to_cpu(rx->hdr.info1),
			     HTT_RX_INDICATION_INFO1_NUM_MPDU_RANGES);

	rx_desc = (काष्ठा htt_hl_rx_desc *)&rx->mpdu_ranges[num_mpdu_ranges];
	rx_desc_info = __le32_to_cpu(rx_desc->info);

	अगर (!MS(rx_desc_info, HTT_RX_DESC_HL_INFO_ENCRYPTED))
		वापस false;

	tid = MS(rx->hdr.info0, HTT_RX_INDICATION_INFO0_EXT_TID);
	last_pn_valid = peer->tids_last_pn_valid[tid];
	last_pn = &peer->tids_last_pn[tid];

	अगर (MS(rx_desc_info, HTT_RX_DESC_HL_INFO_MCAST_BCAST))
		sec_index = HTT_TXRX_SEC_MCAST;
	अन्यथा
		sec_index = HTT_TXRX_SEC_UCAST;

	sec_type = peer->rx_pn[sec_index].sec_type;
	ath10k_htt_rx_mpdu_desc_pn_hl(rx_desc, &new_pn, peer->rx_pn[sec_index].pn_len);

	अगर (sec_type != HTT_SECURITY_AES_CCMP &&
	    sec_type != HTT_SECURITY_TKIP &&
	    sec_type != HTT_SECURITY_TKIP_NOMIC)
		वापस false;

	अगर (last_pn_valid)
		pn_invalid = ath10k_htt_rx_pn_cmp48(&new_pn, last_pn);
	अन्यथा
		peer->tids_last_pn_valid[tid] = true;

	अगर (!pn_invalid)
		last_pn->pn48 = new_pn.pn48;

	वापस pn_invalid;
पूर्ण

अटल bool ath10k_htt_rx_proc_rx_ind_hl(काष्ठा ath10k_htt *htt,
					 काष्ठा htt_rx_indication_hl *rx,
					 काष्ठा sk_buff *skb,
					 क्रमागत htt_rx_pn_check_type check_pn_type,
					 क्रमागत htt_rx_tkip_demic_type tkip_mic_type)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा ath10k_peer *peer;
	काष्ठा htt_rx_indication_mpdu_range *mpdu_ranges;
	काष्ठा fw_rx_desc_hl *fw_desc;
	क्रमागत htt_txrx_sec_cast_type sec_index;
	क्रमागत htt_security_types sec_type;
	जोड़ htt_rx_pn_t new_pn = अणु0पूर्ण;
	काष्ठा htt_hl_rx_desc *rx_desc;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_rx_status *rx_status;
	u16 peer_id;
	u8 rx_desc_len;
	पूर्णांक num_mpdu_ranges;
	माप_प्रकार tot_hdr_len;
	काष्ठा ieee80211_channel *ch;
	bool pn_invalid, qos, first_msdu;
	u32 tid, rx_desc_info;

	peer_id = __le16_to_cpu(rx->hdr.peer_id);
	tid = MS(rx->hdr.info0, HTT_RX_INDICATION_INFO0_EXT_TID);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	spin_unlock_bh(&ar->data_lock);
	अगर (!peer && peer_id != HTT_INVALID_PEERID)
		ath10k_warn(ar, "Got RX ind from invalid peer: %u\n", peer_id);

	अगर (!peer)
		वापस true;

	num_mpdu_ranges = MS(__le32_to_cpu(rx->hdr.info1),
			     HTT_RX_INDICATION_INFO1_NUM_MPDU_RANGES);
	mpdu_ranges = htt_rx_ind_get_mpdu_ranges_hl(rx);
	fw_desc = &rx->fw_desc;
	rx_desc_len = fw_desc->len;

	अगर (fw_desc->u.bits.discard) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTT, "htt discard mpdu\n");
		जाओ err;
	पूर्ण

	/* I have not yet seen any हाल where num_mpdu_ranges > 1.
	 * qcacld करोes not seem handle that हाल either, so we पूर्णांकroduce the
	 * same limitiation here as well.
	 */
	अगर (num_mpdu_ranges > 1)
		ath10k_warn(ar,
			    "Unsupported number of MPDU ranges: %d, ignoring all but the first\n",
			    num_mpdu_ranges);

	अगर (mpdu_ranges->mpdu_range_status !=
	    HTT_RX_IND_MPDU_STATUS_OK &&
	    mpdu_ranges->mpdu_range_status !=
	    HTT_RX_IND_MPDU_STATUS_TKIP_MIC_ERR) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTT, "htt mpdu_range_status %d\n",
			   mpdu_ranges->mpdu_range_status);
		जाओ err;
	पूर्ण

	rx_desc = (काष्ठा htt_hl_rx_desc *)&rx->mpdu_ranges[num_mpdu_ranges];
	rx_desc_info = __le32_to_cpu(rx_desc->info);

	अगर (MS(rx_desc_info, HTT_RX_DESC_HL_INFO_MCAST_BCAST))
		sec_index = HTT_TXRX_SEC_MCAST;
	अन्यथा
		sec_index = HTT_TXRX_SEC_UCAST;

	sec_type = peer->rx_pn[sec_index].sec_type;
	first_msdu = rx->fw_desc.flags & FW_RX_DESC_FLAGS_FIRST_MSDU;

	ath10k_htt_rx_mpdu_desc_pn_hl(rx_desc, &new_pn, peer->rx_pn[sec_index].pn_len);

	अगर (check_pn_type == HTT_RX_PN_CHECK && tid >= IEEE80211_NUM_TIDS) अणु
		spin_lock_bh(&ar->data_lock);
		pn_invalid = ath10k_htt_rx_pn_check_replay_hl(ar, peer, rx);
		spin_unlock_bh(&ar->data_lock);

		अगर (pn_invalid)
			जाओ err;
	पूर्ण

	/* Strip off all headers beक्रमe the MAC header beक्रमe delivery to
	 * mac80211
	 */
	tot_hdr_len = माप(काष्ठा htt_resp_hdr) + माप(rx->hdr) +
		      माप(rx->ppdu) + माप(rx->prefix) +
		      माप(rx->fw_desc) +
		      माप(*mpdu_ranges) * num_mpdu_ranges + rx_desc_len;

	skb_pull(skb, tot_hdr_len);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	qos = ieee80211_is_data_qos(hdr->frame_control);

	rx_status = IEEE80211_SKB_RXCB(skb);
	स_रखो(rx_status, 0, माप(*rx_status));

	अगर (rx->ppdu.combined_rssi == 0) अणु
		/* SDIO firmware करोes not provide संकेत */
		rx_status->संकेत = 0;
		rx_status->flag |= RX_FLAG_NO_SIGNAL_VAL;
	पूर्ण अन्यथा अणु
		rx_status->संकेत = ATH10K_DEFAULT_NOISE_FLOOR +
			rx->ppdu.combined_rssi;
		rx_status->flag &= ~RX_FLAG_NO_SIGNAL_VAL;
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	ch = ar->scan_channel;
	अगर (!ch)
		ch = ar->rx_channel;
	अगर (!ch)
		ch = ath10k_htt_rx_h_any_channel(ar);
	अगर (!ch)
		ch = ar->tgt_oper_chan;
	spin_unlock_bh(&ar->data_lock);

	अगर (ch) अणु
		rx_status->band = ch->band;
		rx_status->freq = ch->center_freq;
	पूर्ण
	अगर (rx->fw_desc.flags & FW_RX_DESC_FLAGS_LAST_MSDU)
		rx_status->flag &= ~RX_FLAG_AMSDU_MORE;
	अन्यथा
		rx_status->flag |= RX_FLAG_AMSDU_MORE;

	/* Not entirely sure about this, but all frames from the chipset has
	 * the रक्षित flag set even though they have alपढ़ोy been decrypted.
	 * Unmasking this flag is necessary in order क्रम mac80211 not to drop
	 * the frame.
	 * TODO: Verअगरy this is always the हाल or find out a way to check
	 * अगर there has been hw decryption.
	 */
	अगर (ieee80211_has_रक्षित(hdr->frame_control)) अणु
		hdr->frame_control &= ~__cpu_to_le16(IEEE80211_FCTL_PROTECTED);
		rx_status->flag |= RX_FLAG_DECRYPTED |
				   RX_FLAG_IV_STRIPPED |
				   RX_FLAG_MMIC_STRIPPED;

		अगर (tid < IEEE80211_NUM_TIDS &&
		    first_msdu &&
		    check_pn_type == HTT_RX_PN_CHECK &&
		   (sec_type == HTT_SECURITY_AES_CCMP ||
		    sec_type == HTT_SECURITY_TKIP ||
		    sec_type == HTT_SECURITY_TKIP_NOMIC)) अणु
			u8 offset, *ivp, i;
			s8 keyidx = 0;
			__le64 pn48 = cpu_to_le64(new_pn.pn48);

			hdr = (काष्ठा ieee80211_hdr *)skb->data;
			offset = ieee80211_hdrlen(hdr->frame_control);
			hdr->frame_control |= __cpu_to_le16(IEEE80211_FCTL_PROTECTED);
			rx_status->flag &= ~RX_FLAG_IV_STRIPPED;

			स_हटाओ(skb->data - IEEE80211_CCMP_HDR_LEN,
				skb->data, offset);
			skb_push(skb, IEEE80211_CCMP_HDR_LEN);
			ivp = skb->data + offset;
			स_रखो(skb->data + offset, 0, IEEE80211_CCMP_HDR_LEN);
			/* Ext IV */
			ivp[IEEE80211_WEP_IV_LEN - 1] |= ATH10K_IEEE80211_EXTIV;

			क्रम (i = 0; i < ARRAY_SIZE(peer->keys); i++) अणु
				अगर (peer->keys[i] &&
				    peer->keys[i]->flags & IEEE80211_KEY_FLAG_PAIRWISE)
					keyidx = peer->keys[i]->keyidx;
			पूर्ण

			/* Key ID */
			ivp[IEEE80211_WEP_IV_LEN - 1] |= keyidx << 6;

			अगर (sec_type == HTT_SECURITY_AES_CCMP) अणु
				rx_status->flag |= RX_FLAG_MIC_STRIPPED;
				/* pn 0, pn 1 */
				स_नकल(skb->data + offset, &pn48, 2);
				/* pn 1, pn 3 , pn 34 , pn 5 */
				स_नकल(skb->data + offset + 4, ((u8 *)&pn48) + 2, 4);
			पूर्ण अन्यथा अणु
				rx_status->flag |= RX_FLAG_ICV_STRIPPED;
				/* TSC 0 */
				स_नकल(skb->data + offset + 2, &pn48, 1);
				/* TSC 1 */
				स_नकल(skb->data + offset, ((u8 *)&pn48) + 1, 1);
				/* TSC 2 , TSC 3 , TSC 4 , TSC 5*/
				स_नकल(skb->data + offset + 4, ((u8 *)&pn48) + 2, 4);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tkip_mic_type == HTT_RX_TKIP_MIC)
		rx_status->flag &= ~RX_FLAG_IV_STRIPPED &
				   ~RX_FLAG_MMIC_STRIPPED;

	अगर (mpdu_ranges->mpdu_range_status == HTT_RX_IND_MPDU_STATUS_TKIP_MIC_ERR)
		rx_status->flag |= RX_FLAG_MMIC_ERROR;

	अगर (!qos && tid < IEEE80211_NUM_TIDS) अणु
		u8 offset;
		__le16 qos_ctrl = 0;

		hdr = (काष्ठा ieee80211_hdr *)skb->data;
		offset = ieee80211_hdrlen(hdr->frame_control);

		hdr->frame_control |= cpu_to_le16(IEEE80211_STYPE_QOS_DATA);
		स_हटाओ(skb->data - IEEE80211_QOS_CTL_LEN, skb->data, offset);
		skb_push(skb, IEEE80211_QOS_CTL_LEN);
		qos_ctrl = cpu_to_le16(tid);
		स_नकल(skb->data + offset, &qos_ctrl, IEEE80211_QOS_CTL_LEN);
	पूर्ण

	अगर (ar->napi.dev)
		ieee80211_rx_napi(ar->hw, शून्य, skb, &ar->napi);
	अन्यथा
		ieee80211_rx_ni(ar->hw, skb);

	/* We have delivered the skb to the upper layers (mac80211) so we
	 * must not मुक्त it.
	 */
	वापस false;
err:
	/* Tell the caller that it must मुक्त the skb since we have not
	 * consumed it
	 */
	वापस true;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_frag_tkip_decap_nomic(काष्ठा sk_buff *skb,
					       u16 head_len,
					       u16 hdr_len)
अणु
	u8 *ivp, *orig_hdr;

	orig_hdr = skb->data;
	ivp = orig_hdr + hdr_len + head_len;

	/* the ExtIV bit is always set to 1 क्रम TKIP */
	अगर (!(ivp[IEEE80211_WEP_IV_LEN - 1] & ATH10K_IEEE80211_EXTIV))
		वापस -EINVAL;

	स_हटाओ(orig_hdr + IEEE80211_TKIP_IV_LEN, orig_hdr, head_len + hdr_len);
	skb_pull(skb, IEEE80211_TKIP_IV_LEN);
	skb_trim(skb, skb->len - ATH10K_IEEE80211_TKIP_MICLEN);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_frag_tkip_decap_withmic(काष्ठा sk_buff *skb,
						 u16 head_len,
						 u16 hdr_len)
अणु
	u8 *ivp, *orig_hdr;

	orig_hdr = skb->data;
	ivp = orig_hdr + hdr_len + head_len;

	/* the ExtIV bit is always set to 1 क्रम TKIP */
	अगर (!(ivp[IEEE80211_WEP_IV_LEN - 1] & ATH10K_IEEE80211_EXTIV))
		वापस -EINVAL;

	स_हटाओ(orig_hdr + IEEE80211_TKIP_IV_LEN, orig_hdr, head_len + hdr_len);
	skb_pull(skb, IEEE80211_TKIP_IV_LEN);
	skb_trim(skb, skb->len - IEEE80211_TKIP_ICV_LEN);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_frag_ccmp_decap(काष्ठा sk_buff *skb,
					 u16 head_len,
					 u16 hdr_len)
अणु
	u8 *ivp, *orig_hdr;

	orig_hdr = skb->data;
	ivp = orig_hdr + hdr_len + head_len;

	/* the ExtIV bit is always set to 1 क्रम CCMP */
	अगर (!(ivp[IEEE80211_WEP_IV_LEN - 1] & ATH10K_IEEE80211_EXTIV))
		वापस -EINVAL;

	skb_trim(skb, skb->len - IEEE80211_CCMP_MIC_LEN);
	स_हटाओ(orig_hdr + IEEE80211_CCMP_HDR_LEN, orig_hdr, head_len + hdr_len);
	skb_pull(skb, IEEE80211_CCMP_HDR_LEN);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_rx_frag_wep_decap(काष्ठा sk_buff *skb,
					u16 head_len,
					u16 hdr_len)
अणु
	u8 *orig_hdr;

	orig_hdr = skb->data;

	स_हटाओ(orig_hdr + IEEE80211_WEP_IV_LEN,
		orig_hdr, head_len + hdr_len);
	skb_pull(skb, IEEE80211_WEP_IV_LEN);
	skb_trim(skb, skb->len - IEEE80211_WEP_ICV_LEN);
	वापस 0;
पूर्ण

अटल bool ath10k_htt_rx_proc_rx_frag_ind_hl(काष्ठा ath10k_htt *htt,
					      काष्ठा htt_rx_fragment_indication *rx,
					      काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k *ar = htt->ar;
	क्रमागत htt_rx_tkip_demic_type tkip_mic = HTT_RX_NON_TKIP_MIC;
	क्रमागत htt_txrx_sec_cast_type sec_index;
	काष्ठा htt_rx_indication_hl *rx_hl;
	क्रमागत htt_security_types sec_type;
	u32 tid, frag, seq, rx_desc_info;
	जोड़ htt_rx_pn_t new_pn = अणु0पूर्ण;
	काष्ठा htt_hl_rx_desc *rx_desc;
	u16 peer_id, sc, hdr_space;
	जोड़ htt_rx_pn_t *last_pn;
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक ret, num_mpdu_ranges;
	काष्ठा ath10k_peer *peer;
	काष्ठा htt_resp *resp;
	माप_प्रकार tot_hdr_len;

	resp = (काष्ठा htt_resp *)(skb->data + HTT_RX_FRAG_IND_INFO0_HEADER_LEN);
	skb_pull(skb, HTT_RX_FRAG_IND_INFO0_HEADER_LEN);
	skb_trim(skb, skb->len - FCS_LEN);

	peer_id = __le16_to_cpu(rx->peer_id);
	rx_hl = (काष्ठा htt_rx_indication_hl *)(&resp->rx_ind_hl);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	अगर (!peer) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTT, "invalid peer: %u\n", peer_id);
		जाओ err;
	पूर्ण

	num_mpdu_ranges = MS(__le32_to_cpu(rx_hl->hdr.info1),
			     HTT_RX_INDICATION_INFO1_NUM_MPDU_RANGES);

	tot_hdr_len = माप(काष्ठा htt_resp_hdr) +
		      माप(rx_hl->hdr) +
		      माप(rx_hl->ppdu) +
		      माप(rx_hl->prefix) +
		      माप(rx_hl->fw_desc) +
		      माप(काष्ठा htt_rx_indication_mpdu_range) * num_mpdu_ranges;

	tid =  MS(rx_hl->hdr.info0, HTT_RX_INDICATION_INFO0_EXT_TID);
	rx_desc = (काष्ठा htt_hl_rx_desc *)(skb->data + tot_hdr_len);
	rx_desc_info = __le32_to_cpu(rx_desc->info);

	hdr = (काष्ठा ieee80211_hdr *)((u8 *)rx_desc + rx_hl->fw_desc.len);

	अगर (is_multicast_ether_addr(hdr->addr1)) अणु
		/* Discard the fragment with multicast DA */
		जाओ err;
	पूर्ण

	अगर (!MS(rx_desc_info, HTT_RX_DESC_HL_INFO_ENCRYPTED)) अणु
		spin_unlock_bh(&ar->data_lock);
		वापस ath10k_htt_rx_proc_rx_ind_hl(htt, &resp->rx_ind_hl, skb,
						    HTT_RX_NON_PN_CHECK,
						    HTT_RX_NON_TKIP_MIC);
	पूर्ण

	अगर (ieee80211_has_retry(hdr->frame_control))
		जाओ err;

	hdr_space = ieee80211_hdrlen(hdr->frame_control);
	sc = __le16_to_cpu(hdr->seq_ctrl);
	seq = (sc & IEEE80211_SCTL_SEQ) >> 4;
	frag = sc & IEEE80211_SCTL_FRAG;

	sec_index = MS(rx_desc_info, HTT_RX_DESC_HL_INFO_MCAST_BCAST) ?
		    HTT_TXRX_SEC_MCAST : HTT_TXRX_SEC_UCAST;
	sec_type = peer->rx_pn[sec_index].sec_type;
	ath10k_htt_rx_mpdu_desc_pn_hl(rx_desc, &new_pn, peer->rx_pn[sec_index].pn_len);

	चयन (sec_type) अणु
	हाल HTT_SECURITY_TKIP:
		tkip_mic = HTT_RX_TKIP_MIC;
		ret = ath10k_htt_rx_frag_tkip_decap_withmic(skb,
							    tot_hdr_len +
							    rx_hl->fw_desc.len,
							    hdr_space);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल HTT_SECURITY_TKIP_NOMIC:
		ret = ath10k_htt_rx_frag_tkip_decap_nomic(skb,
							  tot_hdr_len +
							  rx_hl->fw_desc.len,
							  hdr_space);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल HTT_SECURITY_AES_CCMP:
		ret = ath10k_htt_rx_frag_ccmp_decap(skb,
						    tot_hdr_len + rx_hl->fw_desc.len,
						    hdr_space);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल HTT_SECURITY_WEP128:
	हाल HTT_SECURITY_WEP104:
	हाल HTT_SECURITY_WEP40:
		ret = ath10k_htt_rx_frag_wep_decap(skb,
						   tot_hdr_len + rx_hl->fw_desc.len,
						   hdr_space);
		अगर (ret)
			जाओ err;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	resp = (काष्ठा htt_resp *)(skb->data);

	अगर (sec_type != HTT_SECURITY_AES_CCMP &&
	    sec_type != HTT_SECURITY_TKIP &&
	    sec_type != HTT_SECURITY_TKIP_NOMIC) अणु
		spin_unlock_bh(&ar->data_lock);
		वापस ath10k_htt_rx_proc_rx_ind_hl(htt, &resp->rx_ind_hl, skb,
						    HTT_RX_NON_PN_CHECK,
						    HTT_RX_NON_TKIP_MIC);
	पूर्ण

	last_pn = &peer->frag_tids_last_pn[tid];

	अगर (frag == 0) अणु
		अगर (ath10k_htt_rx_pn_check_replay_hl(ar, peer, &resp->rx_ind_hl))
			जाओ err;

		last_pn->pn48 = new_pn.pn48;
		peer->frag_tids_seq[tid] = seq;
	पूर्ण अन्यथा अगर (sec_type == HTT_SECURITY_AES_CCMP) अणु
		अगर (seq != peer->frag_tids_seq[tid])
			जाओ err;

		अगर (new_pn.pn48 != last_pn->pn48 + 1)
			जाओ err;

		last_pn->pn48 = new_pn.pn48;
		last_pn = &peer->tids_last_pn[tid];
		last_pn->pn48 = new_pn.pn48;
	पूर्ण

	spin_unlock_bh(&ar->data_lock);

	वापस ath10k_htt_rx_proc_rx_ind_hl(htt, &resp->rx_ind_hl, skb,
					    HTT_RX_NON_PN_CHECK, tkip_mic);

err:
	spin_unlock_bh(&ar->data_lock);

	/* Tell the caller that it must मुक्त the skb since we have not
	 * consumed it
	 */
	वापस true;
पूर्ण

अटल व्योम ath10k_htt_rx_proc_rx_ind_ll(काष्ठा ath10k_htt *htt,
					 काष्ठा htt_rx_indication *rx)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा htt_rx_indication_mpdu_range *mpdu_ranges;
	पूर्णांक num_mpdu_ranges;
	पूर्णांक i, mpdu_count = 0;
	u16 peer_id;
	u8 tid;

	num_mpdu_ranges = MS(__le32_to_cpu(rx->hdr.info1),
			     HTT_RX_INDICATION_INFO1_NUM_MPDU_RANGES);
	peer_id = __le16_to_cpu(rx->hdr.peer_id);
	tid =  MS(rx->hdr.info0, HTT_RX_INDICATION_INFO0_EXT_TID);

	mpdu_ranges = htt_rx_ind_get_mpdu_ranges(rx);

	ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य, "htt rx ind: ",
			rx, काष्ठा_size(rx, mpdu_ranges, num_mpdu_ranges));

	क्रम (i = 0; i < num_mpdu_ranges; i++)
		mpdu_count += mpdu_ranges[i].mpdu_count;

	atomic_add(mpdu_count, &htt->num_mpdus_पढ़ोy);

	ath10k_sta_update_rx_tid_stats_ampdu(ar, peer_id, tid, mpdu_ranges,
					     num_mpdu_ranges);
पूर्ण

अटल व्योम ath10k_htt_rx_tx_compl_ind(काष्ठा ath10k *ar,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा htt_resp *resp = (काष्ठा htt_resp *)skb->data;
	काष्ठा htt_tx_करोne tx_करोne = अणुपूर्ण;
	पूर्णांक status = MS(resp->data_tx_completion.flags, HTT_DATA_TX_STATUS);
	__le16 msdu_id, *msdus;
	bool rssi_enabled = false;
	u8 msdu_count = 0, num_airसमय_records, tid;
	पूर्णांक i, htt_pad = 0;
	काष्ठा htt_data_tx_compl_ppdu_dur *ppdu_info;
	काष्ठा ath10k_peer *peer;
	u16 ppdu_info_offset = 0, peer_id;
	u32 tx_duration;

	चयन (status) अणु
	हाल HTT_DATA_TX_STATUS_NO_ACK:
		tx_करोne.status = HTT_TX_COMPL_STATE_NOACK;
		अवरोध;
	हाल HTT_DATA_TX_STATUS_OK:
		tx_करोne.status = HTT_TX_COMPL_STATE_ACK;
		अवरोध;
	हाल HTT_DATA_TX_STATUS_DISCARD:
	हाल HTT_DATA_TX_STATUS_POSTPONE:
	हाल HTT_DATA_TX_STATUS_DOWNLOAD_FAIL:
		tx_करोne.status = HTT_TX_COMPL_STATE_DISCARD;
		अवरोध;
	शेष:
		ath10k_warn(ar, "unhandled tx completion status %d\n", status);
		tx_करोne.status = HTT_TX_COMPL_STATE_DISCARD;
		अवरोध;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx completion num_msdus %d\n",
		   resp->data_tx_completion.num_msdus);

	msdu_count = resp->data_tx_completion.num_msdus;
	msdus = resp->data_tx_completion.msdus;
	rssi_enabled = ath10k_is_rssi_enable(&ar->hw_params, resp);

	अगर (rssi_enabled)
		htt_pad = ath10k_tx_data_rssi_get_pad_bytes(&ar->hw_params,
							    resp);

	क्रम (i = 0; i < msdu_count; i++) अणु
		msdu_id = msdus[i];
		tx_करोne.msdu_id = __le16_to_cpu(msdu_id);

		अगर (rssi_enabled) अणु
			/* Total no of MSDUs should be even,
			 * अगर odd MSDUs are sent firmware fills
			 * last msdu id with 0xffff
			 */
			अगर (msdu_count & 0x01) अणु
				msdu_id = msdus[msdu_count +  i + 1 + htt_pad];
				tx_करोne.ack_rssi = __le16_to_cpu(msdu_id);
			पूर्ण अन्यथा अणु
				msdu_id = msdus[msdu_count +  i + htt_pad];
				tx_करोne.ack_rssi = __le16_to_cpu(msdu_id);
			पूर्ण
		पूर्ण

		/* kfअगरo_put: In practice firmware shouldn't fire off per-CE
		 * पूर्णांकerrupt and मुख्य पूर्णांकerrupt (MSI/-X range हाल) क्रम the same
		 * HTC service so it should be safe to use kfअगरo_put w/o lock.
		 *
		 * From kfअगरo_put() करोcumentation:
		 *  Note that with only one concurrent पढ़ोer and one concurrent
		 *  ग_लिखोr, you करोn't need extra locking to use these macro.
		 */
		अगर (ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL) अणु
			ath10k_txrx_tx_unref(htt, &tx_करोne);
		पूर्ण अन्यथा अगर (!kfअगरo_put(&htt->txकरोne_fअगरo, tx_करोne)) अणु
			ath10k_warn(ar, "txdone fifo overrun, msdu_id %d status %d\n",
				    tx_करोne.msdu_id, tx_करोne.status);
			ath10k_txrx_tx_unref(htt, &tx_करोne);
		पूर्ण
	पूर्ण

	अगर (!(resp->data_tx_completion.flags2 & HTT_TX_CMPL_FLAG_PPDU_DURATION_PRESENT))
		वापस;

	ppdu_info_offset = (msdu_count & 0x01) ? msdu_count + 1 : msdu_count;

	अगर (rssi_enabled)
		ppdu_info_offset += ppdu_info_offset;

	अगर (resp->data_tx_completion.flags2 &
	    (HTT_TX_CMPL_FLAG_PPID_PRESENT | HTT_TX_CMPL_FLAG_PA_PRESENT))
		ppdu_info_offset += 2;

	ppdu_info = (काष्ठा htt_data_tx_compl_ppdu_dur *)&msdus[ppdu_info_offset];
	num_airसमय_records = FIELD_GET(HTT_TX_COMPL_PPDU_DUR_INFO0_NUM_ENTRIES_MASK,
					__le32_to_cpu(ppdu_info->info0));

	क्रम (i = 0; i < num_airसमय_records; i++) अणु
		काष्ठा htt_data_tx_ppdu_dur *ppdu_dur;
		u32 info0;

		ppdu_dur = &ppdu_info->ppdu_dur[i];
		info0 = __le32_to_cpu(ppdu_dur->info0);

		peer_id = FIELD_GET(HTT_TX_PPDU_DUR_INFO0_PEER_ID_MASK,
				    info0);
		rcu_पढ़ो_lock();
		spin_lock_bh(&ar->data_lock);

		peer = ath10k_peer_find_by_id(ar, peer_id);
		अगर (!peer || !peer->sta) अणु
			spin_unlock_bh(&ar->data_lock);
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण

		tid = FIELD_GET(HTT_TX_PPDU_DUR_INFO0_TID_MASK, info0) &
						IEEE80211_QOS_CTL_TID_MASK;
		tx_duration = __le32_to_cpu(ppdu_dur->tx_duration);

		ieee80211_sta_रेजिस्टर_airसमय(peer->sta, tid, tx_duration, 0);

		spin_unlock_bh(&ar->data_lock);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम ath10k_htt_rx_addba(काष्ठा ath10k *ar, काष्ठा htt_resp *resp)
अणु
	काष्ठा htt_rx_addba *ev = &resp->rx_addba;
	काष्ठा ath10k_peer *peer;
	काष्ठा ath10k_vअगर *arvअगर;
	u16 info0, tid, peer_id;

	info0 = __le16_to_cpu(ev->info0);
	tid = MS(info0, HTT_RX_BA_INFO0_TID);
	peer_id = MS(info0, HTT_RX_BA_INFO0_PEER_ID);

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt rx addba tid %u peer_id %u size %u\n",
		   tid, peer_id, ev->winकरोw_size);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	अगर (!peer) अणु
		ath10k_warn(ar, "received addba event for invalid peer_id: %u\n",
			    peer_id);
		spin_unlock_bh(&ar->data_lock);
		वापस;
	पूर्ण

	arvअगर = ath10k_get_arvअगर(ar, peer->vdev_id);
	अगर (!arvअगर) अणु
		ath10k_warn(ar, "received addba event for invalid vdev_id: %u\n",
			    peer->vdev_id);
		spin_unlock_bh(&ar->data_lock);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt rx start rx ba session sta %pM tid %u size %u\n",
		   peer->addr, tid, ev->winकरोw_size);

	ieee80211_start_rx_ba_session_offl(arvअगर->vअगर, peer->addr, tid);
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल व्योम ath10k_htt_rx_delba(काष्ठा ath10k *ar, काष्ठा htt_resp *resp)
अणु
	काष्ठा htt_rx_delba *ev = &resp->rx_delba;
	काष्ठा ath10k_peer *peer;
	काष्ठा ath10k_vअगर *arvअगर;
	u16 info0, tid, peer_id;

	info0 = __le16_to_cpu(ev->info0);
	tid = MS(info0, HTT_RX_BA_INFO0_TID);
	peer_id = MS(info0, HTT_RX_BA_INFO0_PEER_ID);

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt rx delba tid %u peer_id %u\n",
		   tid, peer_id);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	अगर (!peer) अणु
		ath10k_warn(ar, "received addba event for invalid peer_id: %u\n",
			    peer_id);
		spin_unlock_bh(&ar->data_lock);
		वापस;
	पूर्ण

	arvअगर = ath10k_get_arvअगर(ar, peer->vdev_id);
	अगर (!arvअगर) अणु
		ath10k_warn(ar, "received addba event for invalid vdev_id: %u\n",
			    peer->vdev_id);
		spin_unlock_bh(&ar->data_lock);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt rx stop rx ba session sta %pM tid %u\n",
		   peer->addr, tid);

	ieee80211_stop_rx_ba_session_offl(arvअगर->vअगर, peer->addr, tid);
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल पूर्णांक ath10k_htt_rx_extract_amsdu(काष्ठा sk_buff_head *list,
				       काष्ठा sk_buff_head *amsdu)
अणु
	काष्ठा sk_buff *msdu;
	काष्ठा htt_rx_desc *rxd;

	अगर (skb_queue_empty(list))
		वापस -ENOBUFS;

	अगर (WARN_ON(!skb_queue_empty(amsdu)))
		वापस -EINVAL;

	जबतक ((msdu = __skb_dequeue(list))) अणु
		__skb_queue_tail(amsdu, msdu);

		rxd = (व्योम *)msdu->data - माप(*rxd);
		अगर (rxd->msdu_end.common.info0 &
		    __cpu_to_le32(RX_MSDU_END_INFO0_LAST_MSDU))
			अवरोध;
	पूर्ण

	msdu = skb_peek_tail(amsdu);
	rxd = (व्योम *)msdu->data - माप(*rxd);
	अगर (!(rxd->msdu_end.common.info0 &
	      __cpu_to_le32(RX_MSDU_END_INFO0_LAST_MSDU))) अणु
		skb_queue_splice_init(amsdu, list);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_rx_h_rx_offload_prot(काष्ठा ieee80211_rx_status *status,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (!ieee80211_has_रक्षित(hdr->frame_control))
		वापस;

	/* Offloaded frames are alपढ़ोy decrypted but firmware insists they are
	 * रक्षित in the 802.11 header. Strip the flag.  Otherwise mac80211
	 * will drop the frame.
	 */

	hdr->frame_control &= ~__cpu_to_le16(IEEE80211_FCTL_PROTECTED);
	status->flag |= RX_FLAG_DECRYPTED |
			RX_FLAG_IV_STRIPPED |
			RX_FLAG_MMIC_STRIPPED;
पूर्ण

अटल व्योम ath10k_htt_rx_h_rx_offload(काष्ठा ath10k *ar,
				       काष्ठा sk_buff_head *list)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा ieee80211_rx_status *status = &htt->rx_status;
	काष्ठा htt_rx_offload_msdu *rx;
	काष्ठा sk_buff *msdu;
	माप_प्रकार offset;

	जबतक ((msdu = __skb_dequeue(list))) अणु
		/* Offloaded frames करोn't have Rx descriptor. Instead they have
		 * a लघु meta inक्रमmation header.
		 */

		rx = (व्योम *)msdu->data;

		skb_put(msdu, माप(*rx));
		skb_pull(msdu, माप(*rx));

		अगर (skb_tailroom(msdu) < __le16_to_cpu(rx->msdu_len)) अणु
			ath10k_warn(ar, "dropping frame: offloaded rx msdu is too long!\n");
			dev_kमुक्त_skb_any(msdu);
			जारी;
		पूर्ण

		skb_put(msdu, __le16_to_cpu(rx->msdu_len));

		/* Offloaded rx header length isn't multiple of 2 nor 4 so the
		 * actual payload is unaligned. Align the frame.  Otherwise
		 * mac80211 complains.  This shouldn't reduce perक्रमmance much
		 * because these offloaded frames are rare.
		 */
		offset = 4 - ((अचिन्हित दीर्घ)msdu->data & 3);
		skb_put(msdu, offset);
		स_हटाओ(msdu->data + offset, msdu->data, msdu->len);
		skb_pull(msdu, offset);

		/* FIXME: The frame is NWअगरi. Re-स्थिरruct QoS Control
		 * अगर possible later.
		 */

		स_रखो(status, 0, माप(*status));
		status->flag |= RX_FLAG_NO_SIGNAL_VAL;

		ath10k_htt_rx_h_rx_offload_prot(status, msdu);
		ath10k_htt_rx_h_channel(ar, status, शून्य, rx->vdev_id);
		ath10k_htt_rx_h_queue_msdu(ar, status, msdu);
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_htt_rx_in_ord_ind(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा htt_resp *resp = (व्योम *)skb->data;
	काष्ठा ieee80211_rx_status *status = &htt->rx_status;
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff_head amsdu;
	u16 peer_id;
	u16 msdu_count;
	u8 vdev_id;
	u8 tid;
	bool offload;
	bool frag;
	पूर्णांक ret;

	lockdep_निश्चित_held(&htt->rx_ring.lock);

	अगर (htt->rx_confused)
		वापस -EIO;

	skb_pull(skb, माप(resp->hdr));
	skb_pull(skb, माप(resp->rx_in_ord_ind));

	peer_id = __le16_to_cpu(resp->rx_in_ord_ind.peer_id);
	msdu_count = __le16_to_cpu(resp->rx_in_ord_ind.msdu_count);
	vdev_id = resp->rx_in_ord_ind.vdev_id;
	tid = SM(resp->rx_in_ord_ind.info, HTT_RX_IN_ORD_IND_INFO_TID);
	offload = !!(resp->rx_in_ord_ind.info &
			HTT_RX_IN_ORD_IND_INFO_OFFLOAD_MASK);
	frag = !!(resp->rx_in_ord_ind.info & HTT_RX_IN_ORD_IND_INFO_FRAG_MASK);

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt rx in ord vdev %i peer %i tid %i offload %i frag %i msdu count %i\n",
		   vdev_id, peer_id, tid, offload, frag, msdu_count);

	अगर (skb->len < msdu_count * माप(*resp->rx_in_ord_ind.msdu_descs32)) अणु
		ath10k_warn(ar, "dropping invalid in order rx indication\n");
		वापस -EINVAL;
	पूर्ण

	/* The event can deliver more than 1 A-MSDU. Each A-MSDU is later
	 * extracted and processed.
	 */
	__skb_queue_head_init(&list);
	अगर (ar->hw_params.target_64bit)
		ret = ath10k_htt_rx_pop_paddr64_list(htt, &resp->rx_in_ord_ind,
						     &list);
	अन्यथा
		ret = ath10k_htt_rx_pop_paddr32_list(htt, &resp->rx_in_ord_ind,
						     &list);

	अगर (ret < 0) अणु
		ath10k_warn(ar, "failed to pop paddr list: %d\n", ret);
		htt->rx_confused = true;
		वापस -EIO;
	पूर्ण

	/* Offloaded frames are very dअगरferent and need to be handled
	 * separately.
	 */
	अगर (offload)
		ath10k_htt_rx_h_rx_offload(ar, &list);

	जबतक (!skb_queue_empty(&list)) अणु
		__skb_queue_head_init(&amsdu);
		ret = ath10k_htt_rx_extract_amsdu(&list, &amsdu);
		चयन (ret) अणु
		हाल 0:
			/* Note: The in-order indication may report पूर्णांकerleaved
			 * frames from dअगरferent PPDUs meaning reported rx rate
			 * to mac80211 isn't accurate/reliable. It's still
			 * better to report something than nothing though. This
			 * should still give an idea about rx rate to the user.
			 */
			ath10k_htt_rx_h_ppdu(ar, &amsdu, status, vdev_id);
			ath10k_htt_rx_h_filter(ar, &amsdu, status, शून्य);
			ath10k_htt_rx_h_mpdu(ar, &amsdu, status, false, शून्य,
					     शून्य, peer_id, frag);
			ath10k_htt_rx_h_enqueue(ar, &amsdu, status);
			अवरोध;
		हाल -EAGAIN:
			fallthrough;
		शेष:
			/* Should not happen. */
			ath10k_warn(ar, "failed to extract amsdu: %d\n", ret);
			htt->rx_confused = true;
			__skb_queue_purge(&list);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ath10k_htt_rx_tx_fetch_resp_id_confirm(काष्ठा ath10k *ar,
						   स्थिर __le32 *resp_ids,
						   पूर्णांक num_resp_ids)
अणु
	पूर्णांक i;
	u32 resp_id;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx fetch confirm num_resp_ids %d\n",
		   num_resp_ids);

	क्रम (i = 0; i < num_resp_ids; i++) अणु
		resp_id = le32_to_cpu(resp_ids[i]);

		ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx fetch confirm resp_id %u\n",
			   resp_id);

		/* TODO: मुक्त resp_id */
	पूर्ण
पूर्ण

अटल व्योम ath10k_htt_rx_tx_fetch_ind(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hw *hw = ar->hw;
	काष्ठा ieee80211_txq *txq;
	काष्ठा htt_resp *resp = (काष्ठा htt_resp *)skb->data;
	काष्ठा htt_tx_fetch_record *record;
	माप_प्रकार len;
	माप_प्रकार max_num_bytes;
	माप_प्रकार max_num_msdus;
	माप_प्रकार num_bytes;
	माप_प्रकार num_msdus;
	स्थिर __le32 *resp_ids;
	u16 num_records;
	u16 num_resp_ids;
	u16 peer_id;
	u8 tid;
	पूर्णांक ret;
	पूर्णांक i;
	bool may_tx;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx fetch ind\n");

	len = माप(resp->hdr) + माप(resp->tx_fetch_ind);
	अगर (unlikely(skb->len < len)) अणु
		ath10k_warn(ar, "received corrupted tx_fetch_ind event: buffer too short\n");
		वापस;
	पूर्ण

	num_records = le16_to_cpu(resp->tx_fetch_ind.num_records);
	num_resp_ids = le16_to_cpu(resp->tx_fetch_ind.num_resp_ids);

	len += माप(resp->tx_fetch_ind.records[0]) * num_records;
	len += माप(resp->tx_fetch_ind.resp_ids[0]) * num_resp_ids;

	अगर (unlikely(skb->len < len)) अणु
		ath10k_warn(ar, "received corrupted tx_fetch_ind event: too many records/resp_ids\n");
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx fetch ind num records %u num resps %u seq %u\n",
		   num_records, num_resp_ids,
		   le16_to_cpu(resp->tx_fetch_ind.fetch_seq_num));

	अगर (!ar->htt.tx_q_state.enabled) अणु
		ath10k_warn(ar, "received unexpected tx_fetch_ind event: not enabled\n");
		वापस;
	पूर्ण

	अगर (ar->htt.tx_q_state.mode == HTT_TX_MODE_SWITCH_PUSH) अणु
		ath10k_warn(ar, "received unexpected tx_fetch_ind event: in push mode\n");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();

	क्रम (i = 0; i < num_records; i++) अणु
		record = &resp->tx_fetch_ind.records[i];
		peer_id = MS(le16_to_cpu(record->info),
			     HTT_TX_FETCH_RECORD_INFO_PEER_ID);
		tid = MS(le16_to_cpu(record->info),
			 HTT_TX_FETCH_RECORD_INFO_TID);
		max_num_msdus = le16_to_cpu(record->num_msdus);
		max_num_bytes = le32_to_cpu(record->num_bytes);

		ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx fetch record %i peer_id %u tid %u msdus %zu bytes %zu\n",
			   i, peer_id, tid, max_num_msdus, max_num_bytes);

		अगर (unlikely(peer_id >= ar->htt.tx_q_state.num_peers) ||
		    unlikely(tid >= ar->htt.tx_q_state.num_tids)) अणु
			ath10k_warn(ar, "received out of range peer_id %u tid %u\n",
				    peer_id, tid);
			जारी;
		पूर्ण

		spin_lock_bh(&ar->data_lock);
		txq = ath10k_mac_txq_lookup(ar, peer_id, tid);
		spin_unlock_bh(&ar->data_lock);

		/* It is okay to release the lock and use txq because RCU पढ़ो
		 * lock is held.
		 */

		अगर (unlikely(!txq)) अणु
			ath10k_warn(ar, "failed to lookup txq for peer_id %u tid %u\n",
				    peer_id, tid);
			जारी;
		पूर्ण

		num_msdus = 0;
		num_bytes = 0;

		ieee80211_txq_schedule_start(hw, txq->ac);
		may_tx = ieee80211_txq_may_transmit(hw, txq);
		जबतक (num_msdus < max_num_msdus &&
		       num_bytes < max_num_bytes) अणु
			अगर (!may_tx)
				अवरोध;

			ret = ath10k_mac_tx_push_txq(hw, txq);
			अगर (ret < 0)
				अवरोध;

			num_msdus++;
			num_bytes += ret;
		पूर्ण
		ieee80211_वापस_txq(hw, txq, false);
		ieee80211_txq_schedule_end(hw, txq->ac);

		record->num_msdus = cpu_to_le16(num_msdus);
		record->num_bytes = cpu_to_le32(num_bytes);

		ath10k_htt_tx_txq_recalc(hw, txq);
	पूर्ण

	rcu_पढ़ो_unlock();

	resp_ids = ath10k_htt_get_tx_fetch_ind_resp_ids(&resp->tx_fetch_ind);
	ath10k_htt_rx_tx_fetch_resp_id_confirm(ar, resp_ids, num_resp_ids);

	ret = ath10k_htt_tx_fetch_resp(ar,
				       resp->tx_fetch_ind.token,
				       resp->tx_fetch_ind.fetch_seq_num,
				       resp->tx_fetch_ind.records,
				       num_records);
	अगर (unlikely(ret)) अणु
		ath10k_warn(ar, "failed to submit tx fetch resp for token 0x%08x: %d\n",
			    le32_to_cpu(resp->tx_fetch_ind.token), ret);
		/* FIXME: request fw restart */
	पूर्ण

	ath10k_htt_tx_txq_sync(ar);
पूर्ण

अटल व्योम ath10k_htt_rx_tx_fetch_confirm(काष्ठा ath10k *ar,
					   काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा htt_resp *resp = (व्योम *)skb->data;
	माप_प्रकार len;
	पूर्णांक num_resp_ids;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx fetch confirm\n");

	len = माप(resp->hdr) + माप(resp->tx_fetch_confirm);
	अगर (unlikely(skb->len < len)) अणु
		ath10k_warn(ar, "received corrupted tx_fetch_confirm event: buffer too short\n");
		वापस;
	पूर्ण

	num_resp_ids = le16_to_cpu(resp->tx_fetch_confirm.num_resp_ids);
	len += माप(resp->tx_fetch_confirm.resp_ids[0]) * num_resp_ids;

	अगर (unlikely(skb->len < len)) अणु
		ath10k_warn(ar, "received corrupted tx_fetch_confirm event: resp_ids buffer overflow\n");
		वापस;
	पूर्ण

	ath10k_htt_rx_tx_fetch_resp_id_confirm(ar,
					       resp->tx_fetch_confirm.resp_ids,
					       num_resp_ids);
पूर्ण

अटल व्योम ath10k_htt_rx_tx_mode_चयन_ind(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा htt_resp *resp = (व्योम *)skb->data;
	स्थिर काष्ठा htt_tx_mode_चयन_record *record;
	काष्ठा ieee80211_txq *txq;
	काष्ठा ath10k_txq *artxq;
	माप_प्रकार len;
	माप_प्रकार num_records;
	क्रमागत htt_tx_mode_चयन_mode mode;
	bool enable;
	u16 info0;
	u16 info1;
	u16 threshold;
	u16 peer_id;
	u8 tid;
	पूर्णांक i;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx mode switch ind\n");

	len = माप(resp->hdr) + माप(resp->tx_mode_चयन_ind);
	अगर (unlikely(skb->len < len)) अणु
		ath10k_warn(ar, "received corrupted tx_mode_switch_ind event: buffer too short\n");
		वापस;
	पूर्ण

	info0 = le16_to_cpu(resp->tx_mode_चयन_ind.info0);
	info1 = le16_to_cpu(resp->tx_mode_चयन_ind.info1);

	enable = !!(info0 & HTT_TX_MODE_SWITCH_IND_INFO0_ENABLE);
	num_records = MS(info0, HTT_TX_MODE_SWITCH_IND_INFO1_THRESHOLD);
	mode = MS(info1, HTT_TX_MODE_SWITCH_IND_INFO1_MODE);
	threshold = MS(info1, HTT_TX_MODE_SWITCH_IND_INFO1_THRESHOLD);

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt rx tx mode switch ind info0 0x%04hx info1 0x%04x enable %d num records %zd mode %d threshold %u\n",
		   info0, info1, enable, num_records, mode, threshold);

	len += माप(resp->tx_mode_चयन_ind.records[0]) * num_records;

	अगर (unlikely(skb->len < len)) अणु
		ath10k_warn(ar, "received corrupted tx_mode_switch_mode_ind event: too many records\n");
		वापस;
	पूर्ण

	चयन (mode) अणु
	हाल HTT_TX_MODE_SWITCH_PUSH:
	हाल HTT_TX_MODE_SWITCH_PUSH_PULL:
		अवरोध;
	शेष:
		ath10k_warn(ar, "received invalid tx_mode_switch_mode_ind mode %d, ignoring\n",
			    mode);
		वापस;
	पूर्ण

	अगर (!enable)
		वापस;

	ar->htt.tx_q_state.enabled = enable;
	ar->htt.tx_q_state.mode = mode;
	ar->htt.tx_q_state.num_push_allowed = threshold;

	rcu_पढ़ो_lock();

	क्रम (i = 0; i < num_records; i++) अणु
		record = &resp->tx_mode_चयन_ind.records[i];
		info0 = le16_to_cpu(record->info0);
		peer_id = MS(info0, HTT_TX_MODE_SWITCH_RECORD_INFO0_PEER_ID);
		tid = MS(info0, HTT_TX_MODE_SWITCH_RECORD_INFO0_TID);

		अगर (unlikely(peer_id >= ar->htt.tx_q_state.num_peers) ||
		    unlikely(tid >= ar->htt.tx_q_state.num_tids)) अणु
			ath10k_warn(ar, "received out of range peer_id %u tid %u\n",
				    peer_id, tid);
			जारी;
		पूर्ण

		spin_lock_bh(&ar->data_lock);
		txq = ath10k_mac_txq_lookup(ar, peer_id, tid);
		spin_unlock_bh(&ar->data_lock);

		/* It is okay to release the lock and use txq because RCU पढ़ो
		 * lock is held.
		 */

		अगर (unlikely(!txq)) अणु
			ath10k_warn(ar, "failed to lookup txq for peer_id %u tid %u\n",
				    peer_id, tid);
			जारी;
		पूर्ण

		spin_lock_bh(&ar->htt.tx_lock);
		artxq = (व्योम *)txq->drv_priv;
		artxq->num_push_allowed = le16_to_cpu(record->num_max_msdus);
		spin_unlock_bh(&ar->htt.tx_lock);
	पूर्ण

	rcu_पढ़ो_unlock();

	ath10k_mac_tx_push_pending(ar);
पूर्ण

व्योम ath10k_htt_htc_t2h_msg_handler(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	bool release;

	release = ath10k_htt_t2h_msg_handler(ar, skb);

	/* Free the indication buffer */
	अगर (release)
		dev_kमुक्त_skb_any(skb);
पूर्ण

अटल अंतरभूत s8 ath10k_get_legacy_rate_idx(काष्ठा ath10k *ar, u8 rate)
अणु
	अटल स्थिर u8 legacy_rates[] = अणु1, 2, 5, 11, 6, 9, 12,
					  18, 24, 36, 48, 54पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(legacy_rates); i++) अणु
		अगर (rate == legacy_rates[i])
			वापस i;
	पूर्ण

	ath10k_warn(ar, "Invalid legacy rate %d peer stats", rate);
	वापस -EINVAL;
पूर्ण

अटल व्योम
ath10k_accumulate_per_peer_tx_stats(काष्ठा ath10k *ar,
				    काष्ठा ath10k_sta *arsta,
				    काष्ठा ath10k_per_peer_tx_stats *pstats,
				    s8 legacy_rate_idx)
अणु
	काष्ठा rate_info *txrate = &arsta->txrate;
	काष्ठा ath10k_htt_tx_stats *tx_stats;
	पूर्णांक idx, ht_idx, gi, mcs, bw, nss;
	अचिन्हित दीर्घ flags;

	अगर (!arsta->tx_stats)
		वापस;

	tx_stats = arsta->tx_stats;
	flags = txrate->flags;
	gi = test_bit(ATH10K_RATE_INFO_FLAGS_SGI_BIT, &flags);
	mcs = ATH10K_HW_MCS_RATE(pstats->ratecode);
	bw = txrate->bw;
	nss = txrate->nss;
	ht_idx = mcs + (nss - 1) * 8;
	idx = mcs * 8 + 8 * 10 * (nss - 1);
	idx += bw * 2 + gi;

#घोषणा STATS_OP_FMT(name) tx_stats->stats[ATH10K_STATS_TYPE_##name]

	अगर (txrate->flags & RATE_INFO_FLAGS_VHT_MCS) अणु
		STATS_OP_FMT(SUCC).vht[0][mcs] += pstats->succ_bytes;
		STATS_OP_FMT(SUCC).vht[1][mcs] += pstats->succ_pkts;
		STATS_OP_FMT(FAIL).vht[0][mcs] += pstats->failed_bytes;
		STATS_OP_FMT(FAIL).vht[1][mcs] += pstats->failed_pkts;
		STATS_OP_FMT(RETRY).vht[0][mcs] += pstats->retry_bytes;
		STATS_OP_FMT(RETRY).vht[1][mcs] += pstats->retry_pkts;
	पूर्ण अन्यथा अगर (txrate->flags & RATE_INFO_FLAGS_MCS) अणु
		STATS_OP_FMT(SUCC).ht[0][ht_idx] += pstats->succ_bytes;
		STATS_OP_FMT(SUCC).ht[1][ht_idx] += pstats->succ_pkts;
		STATS_OP_FMT(FAIL).ht[0][ht_idx] += pstats->failed_bytes;
		STATS_OP_FMT(FAIL).ht[1][ht_idx] += pstats->failed_pkts;
		STATS_OP_FMT(RETRY).ht[0][ht_idx] += pstats->retry_bytes;
		STATS_OP_FMT(RETRY).ht[1][ht_idx] += pstats->retry_pkts;
	पूर्ण अन्यथा अणु
		mcs = legacy_rate_idx;

		STATS_OP_FMT(SUCC).legacy[0][mcs] += pstats->succ_bytes;
		STATS_OP_FMT(SUCC).legacy[1][mcs] += pstats->succ_pkts;
		STATS_OP_FMT(FAIL).legacy[0][mcs] += pstats->failed_bytes;
		STATS_OP_FMT(FAIL).legacy[1][mcs] += pstats->failed_pkts;
		STATS_OP_FMT(RETRY).legacy[0][mcs] += pstats->retry_bytes;
		STATS_OP_FMT(RETRY).legacy[1][mcs] += pstats->retry_pkts;
	पूर्ण

	अगर (ATH10K_HW_AMPDU(pstats->flags)) अणु
		tx_stats->ba_fails += ATH10K_HW_BA_FAIL(pstats->flags);

		अगर (txrate->flags & RATE_INFO_FLAGS_MCS) अणु
			STATS_OP_FMT(AMPDU).ht[0][ht_idx] +=
				pstats->succ_bytes + pstats->retry_bytes;
			STATS_OP_FMT(AMPDU).ht[1][ht_idx] +=
				pstats->succ_pkts + pstats->retry_pkts;
		पूर्ण अन्यथा अणु
			STATS_OP_FMT(AMPDU).vht[0][mcs] +=
				pstats->succ_bytes + pstats->retry_bytes;
			STATS_OP_FMT(AMPDU).vht[1][mcs] +=
				pstats->succ_pkts + pstats->retry_pkts;
		पूर्ण
		STATS_OP_FMT(AMPDU).bw[0][bw] +=
			pstats->succ_bytes + pstats->retry_bytes;
		STATS_OP_FMT(AMPDU).nss[0][nss - 1] +=
			pstats->succ_bytes + pstats->retry_bytes;
		STATS_OP_FMT(AMPDU).gi[0][gi] +=
			pstats->succ_bytes + pstats->retry_bytes;
		STATS_OP_FMT(AMPDU).rate_table[0][idx] +=
			pstats->succ_bytes + pstats->retry_bytes;
		STATS_OP_FMT(AMPDU).bw[1][bw] +=
			pstats->succ_pkts + pstats->retry_pkts;
		STATS_OP_FMT(AMPDU).nss[1][nss - 1] +=
			pstats->succ_pkts + pstats->retry_pkts;
		STATS_OP_FMT(AMPDU).gi[1][gi] +=
			pstats->succ_pkts + pstats->retry_pkts;
		STATS_OP_FMT(AMPDU).rate_table[1][idx] +=
			pstats->succ_pkts + pstats->retry_pkts;
	पूर्ण अन्यथा अणु
		tx_stats->ack_fails +=
				ATH10K_HW_BA_FAIL(pstats->flags);
	पूर्ण

	STATS_OP_FMT(SUCC).bw[0][bw] += pstats->succ_bytes;
	STATS_OP_FMT(SUCC).nss[0][nss - 1] += pstats->succ_bytes;
	STATS_OP_FMT(SUCC).gi[0][gi] += pstats->succ_bytes;

	STATS_OP_FMT(SUCC).bw[1][bw] += pstats->succ_pkts;
	STATS_OP_FMT(SUCC).nss[1][nss - 1] += pstats->succ_pkts;
	STATS_OP_FMT(SUCC).gi[1][gi] += pstats->succ_pkts;

	STATS_OP_FMT(FAIL).bw[0][bw] += pstats->failed_bytes;
	STATS_OP_FMT(FAIL).nss[0][nss - 1] += pstats->failed_bytes;
	STATS_OP_FMT(FAIL).gi[0][gi] += pstats->failed_bytes;

	STATS_OP_FMT(FAIL).bw[1][bw] += pstats->failed_pkts;
	STATS_OP_FMT(FAIL).nss[1][nss - 1] += pstats->failed_pkts;
	STATS_OP_FMT(FAIL).gi[1][gi] += pstats->failed_pkts;

	STATS_OP_FMT(RETRY).bw[0][bw] += pstats->retry_bytes;
	STATS_OP_FMT(RETRY).nss[0][nss - 1] += pstats->retry_bytes;
	STATS_OP_FMT(RETRY).gi[0][gi] += pstats->retry_bytes;

	STATS_OP_FMT(RETRY).bw[1][bw] += pstats->retry_pkts;
	STATS_OP_FMT(RETRY).nss[1][nss - 1] += pstats->retry_pkts;
	STATS_OP_FMT(RETRY).gi[1][gi] += pstats->retry_pkts;

	अगर (txrate->flags >= RATE_INFO_FLAGS_MCS) अणु
		STATS_OP_FMT(SUCC).rate_table[0][idx] += pstats->succ_bytes;
		STATS_OP_FMT(SUCC).rate_table[1][idx] += pstats->succ_pkts;
		STATS_OP_FMT(FAIL).rate_table[0][idx] += pstats->failed_bytes;
		STATS_OP_FMT(FAIL).rate_table[1][idx] += pstats->failed_pkts;
		STATS_OP_FMT(RETRY).rate_table[0][idx] += pstats->retry_bytes;
		STATS_OP_FMT(RETRY).rate_table[1][idx] += pstats->retry_pkts;
	पूर्ण

	tx_stats->tx_duration += pstats->duration;
पूर्ण

अटल व्योम
ath10k_update_per_peer_tx_stats(काष्ठा ath10k *ar,
				काष्ठा ieee80211_sta *sta,
				काष्ठा ath10k_per_peer_tx_stats *peer_stats)
अणु
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ieee80211_chanctx_conf *conf = शून्य;
	u8 rate = 0, sgi;
	s8 rate_idx = 0;
	bool skip_स्वतः_rate;
	काष्ठा rate_info txrate;

	lockdep_निश्चित_held(&ar->data_lock);

	txrate.flags = ATH10K_HW_PREAMBLE(peer_stats->ratecode);
	txrate.bw = ATH10K_HW_BW(peer_stats->flags);
	txrate.nss = ATH10K_HW_NSS(peer_stats->ratecode);
	txrate.mcs = ATH10K_HW_MCS_RATE(peer_stats->ratecode);
	sgi = ATH10K_HW_GI(peer_stats->flags);
	skip_स्वतः_rate = ATH10K_FW_SKIPPED_RATE_CTRL(peer_stats->flags);

	/* Firmware's rate control skips broadcast/management frames,
	 * अगर host has configure fixed rates and in some other special हालs.
	 */
	अगर (skip_स्वतः_rate)
		वापस;

	अगर (txrate.flags == WMI_RATE_PREAMBLE_VHT && txrate.mcs > 9) अणु
		ath10k_warn(ar, "Invalid VHT mcs %d peer stats",  txrate.mcs);
		वापस;
	पूर्ण

	अगर (txrate.flags == WMI_RATE_PREAMBLE_HT &&
	    (txrate.mcs > 7 || txrate.nss < 1)) अणु
		ath10k_warn(ar, "Invalid HT mcs %d nss %d peer stats",
			    txrate.mcs, txrate.nss);
		वापस;
	पूर्ण

	स_रखो(&arsta->txrate, 0, माप(arsta->txrate));
	स_रखो(&arsta->tx_info.status, 0, माप(arsta->tx_info.status));
	अगर (txrate.flags == WMI_RATE_PREAMBLE_CCK ||
	    txrate.flags == WMI_RATE_PREAMBLE_OFDM) अणु
		rate = ATH10K_HW_LEGACY_RATE(peer_stats->ratecode);
		/* This is hacky, FW sends CCK rate 5.5Mbps as 6 */
		अगर (rate == 6 && txrate.flags == WMI_RATE_PREAMBLE_CCK)
			rate = 5;
		rate_idx = ath10k_get_legacy_rate_idx(ar, rate);
		अगर (rate_idx < 0)
			वापस;
		arsta->txrate.legacy = rate;
	पूर्ण अन्यथा अगर (txrate.flags == WMI_RATE_PREAMBLE_HT) अणु
		arsta->txrate.flags = RATE_INFO_FLAGS_MCS;
		arsta->txrate.mcs = txrate.mcs + 8 * (txrate.nss - 1);
	पूर्ण अन्यथा अणु
		arsta->txrate.flags = RATE_INFO_FLAGS_VHT_MCS;
		arsta->txrate.mcs = txrate.mcs;
	पूर्ण

	चयन (txrate.flags) अणु
	हाल WMI_RATE_PREAMBLE_OFDM:
		अगर (arsta->arvअगर && arsta->arvअगर->vअगर)
			conf = rcu_dereference(arsta->arvअगर->vअगर->chanctx_conf);
		अगर (conf && conf->def.chan->band == NL80211_BAND_5GHZ)
			arsta->tx_info.status.rates[0].idx = rate_idx - 4;
		अवरोध;
	हाल WMI_RATE_PREAMBLE_CCK:
		arsta->tx_info.status.rates[0].idx = rate_idx;
		अगर (sgi)
			arsta->tx_info.status.rates[0].flags |=
				(IEEE80211_TX_RC_USE_SHORT_PREAMBLE |
				 IEEE80211_TX_RC_SHORT_GI);
		अवरोध;
	हाल WMI_RATE_PREAMBLE_HT:
		arsta->tx_info.status.rates[0].idx =
				txrate.mcs + ((txrate.nss - 1) * 8);
		अगर (sgi)
			arsta->tx_info.status.rates[0].flags |=
					IEEE80211_TX_RC_SHORT_GI;
		arsta->tx_info.status.rates[0].flags |= IEEE80211_TX_RC_MCS;
		अवरोध;
	हाल WMI_RATE_PREAMBLE_VHT:
		ieee80211_rate_set_vht(&arsta->tx_info.status.rates[0],
				       txrate.mcs, txrate.nss);
		अगर (sgi)
			arsta->tx_info.status.rates[0].flags |=
						IEEE80211_TX_RC_SHORT_GI;
		arsta->tx_info.status.rates[0].flags |= IEEE80211_TX_RC_VHT_MCS;
		अवरोध;
	पूर्ण

	arsta->txrate.nss = txrate.nss;
	arsta->txrate.bw = ath10k_bw_to_mac80211_bw(txrate.bw);
	arsta->last_tx_bitrate = cfg80211_calculate_bitrate(&arsta->txrate);
	अगर (sgi)
		arsta->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;

	चयन (arsta->txrate.bw) अणु
	हाल RATE_INFO_BW_40:
		arsta->tx_info.status.rates[0].flags |=
				IEEE80211_TX_RC_40_MHZ_WIDTH;
		अवरोध;
	हाल RATE_INFO_BW_80:
		arsta->tx_info.status.rates[0].flags |=
				IEEE80211_TX_RC_80_MHZ_WIDTH;
		अवरोध;
	पूर्ण

	अगर (peer_stats->succ_pkts) अणु
		arsta->tx_info.flags = IEEE80211_TX_STAT_ACK;
		arsta->tx_info.status.rates[0].count = 1;
		ieee80211_tx_rate_update(ar->hw, sta, &arsta->tx_info);
	पूर्ण

	अगर (ar->htt.disable_tx_comp) अणु
		arsta->tx_failed += peer_stats->failed_pkts;
		ath10k_dbg(ar, ATH10K_DBG_HTT, "tx failed %d\n",
			   arsta->tx_failed);
	पूर्ण

	arsta->tx_retries += peer_stats->retry_pkts;
	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx retries %d", arsta->tx_retries);

	अगर (ath10k_debug_is_extd_tx_stats_enabled(ar))
		ath10k_accumulate_per_peer_tx_stats(ar, arsta, peer_stats,
						    rate_idx);
पूर्ण

अटल व्योम ath10k_htt_fetch_peer_stats(काष्ठा ath10k *ar,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा htt_resp *resp = (काष्ठा htt_resp *)skb->data;
	काष्ठा ath10k_per_peer_tx_stats *p_tx_stats = &ar->peer_tx_stats;
	काष्ठा htt_per_peer_tx_stats_ind *tx_stats;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath10k_peer *peer;
	पूर्णांक peer_id, i;
	u8 ppdu_len, num_ppdu;

	num_ppdu = resp->peer_tx_stats.num_ppdu;
	ppdu_len = resp->peer_tx_stats.ppdu_len * माप(__le32);

	अगर (skb->len < माप(काष्ठा htt_resp_hdr) + num_ppdu * ppdu_len) अणु
		ath10k_warn(ar, "Invalid peer stats buf length %d\n", skb->len);
		वापस;
	पूर्ण

	tx_stats = (काष्ठा htt_per_peer_tx_stats_ind *)
			(resp->peer_tx_stats.payload);
	peer_id = __le16_to_cpu(tx_stats->peer_id);

	rcu_पढ़ो_lock();
	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	अगर (!peer || !peer->sta) अणु
		ath10k_warn(ar, "Invalid peer id %d peer stats buffer\n",
			    peer_id);
		जाओ out;
	पूर्ण

	sta = peer->sta;
	क्रम (i = 0; i < num_ppdu; i++) अणु
		tx_stats = (काष्ठा htt_per_peer_tx_stats_ind *)
			   (resp->peer_tx_stats.payload + i * ppdu_len);

		p_tx_stats->succ_bytes = __le32_to_cpu(tx_stats->succ_bytes);
		p_tx_stats->retry_bytes = __le32_to_cpu(tx_stats->retry_bytes);
		p_tx_stats->failed_bytes =
				__le32_to_cpu(tx_stats->failed_bytes);
		p_tx_stats->ratecode = tx_stats->ratecode;
		p_tx_stats->flags = tx_stats->flags;
		p_tx_stats->succ_pkts = __le16_to_cpu(tx_stats->succ_pkts);
		p_tx_stats->retry_pkts = __le16_to_cpu(tx_stats->retry_pkts);
		p_tx_stats->failed_pkts = __le16_to_cpu(tx_stats->failed_pkts);
		p_tx_stats->duration = __le16_to_cpu(tx_stats->tx_duration);

		ath10k_update_per_peer_tx_stats(ar, sta, p_tx_stats);
	पूर्ण

out:
	spin_unlock_bh(&ar->data_lock);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath10k_fetch_10_2_tx_stats(काष्ठा ath10k *ar, u8 *data)
अणु
	काष्ठा ath10k_pktlog_hdr *hdr = (काष्ठा ath10k_pktlog_hdr *)data;
	काष्ठा ath10k_per_peer_tx_stats *p_tx_stats = &ar->peer_tx_stats;
	काष्ठा ath10k_10_2_peer_tx_stats *tx_stats;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath10k_peer *peer;
	u16 log_type = __le16_to_cpu(hdr->log_type);
	u32 peer_id = 0, i;

	अगर (log_type != ATH_PKTLOG_TYPE_TX_STAT)
		वापस;

	tx_stats = (काष्ठा ath10k_10_2_peer_tx_stats *)((hdr->payload) +
		    ATH10K_10_2_TX_STATS_OFFSET);

	अगर (!tx_stats->tx_ppdu_cnt)
		वापस;

	peer_id = tx_stats->peer_id;

	rcu_पढ़ो_lock();
	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, peer_id);
	अगर (!peer || !peer->sta) अणु
		ath10k_warn(ar, "Invalid peer id %d in peer stats buffer\n",
			    peer_id);
		जाओ out;
	पूर्ण

	sta = peer->sta;
	क्रम (i = 0; i < tx_stats->tx_ppdu_cnt; i++) अणु
		p_tx_stats->succ_bytes =
			__le16_to_cpu(tx_stats->success_bytes[i]);
		p_tx_stats->retry_bytes =
			__le16_to_cpu(tx_stats->retry_bytes[i]);
		p_tx_stats->failed_bytes =
			__le16_to_cpu(tx_stats->failed_bytes[i]);
		p_tx_stats->ratecode = tx_stats->ratecode[i];
		p_tx_stats->flags = tx_stats->flags[i];
		p_tx_stats->succ_pkts = tx_stats->success_pkts[i];
		p_tx_stats->retry_pkts = tx_stats->retry_pkts[i];
		p_tx_stats->failed_pkts = tx_stats->failed_pkts[i];

		ath10k_update_per_peer_tx_stats(ar, sta, p_tx_stats);
	पूर्ण
	spin_unlock_bh(&ar->data_lock);
	rcu_पढ़ो_unlock();

	वापस;

out:
	spin_unlock_bh(&ar->data_lock);
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक ath10k_htt_rx_pn_len(क्रमागत htt_security_types sec_type)
अणु
	चयन (sec_type) अणु
	हाल HTT_SECURITY_TKIP:
	हाल HTT_SECURITY_TKIP_NOMIC:
	हाल HTT_SECURITY_AES_CCMP:
		वापस 48;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ath10k_htt_rx_sec_ind_handler(काष्ठा ath10k *ar,
					  काष्ठा htt_security_indication *ev)
अणु
	क्रमागत htt_txrx_sec_cast_type sec_index;
	क्रमागत htt_security_types sec_type;
	काष्ठा ath10k_peer *peer;

	spin_lock_bh(&ar->data_lock);

	peer = ath10k_peer_find_by_id(ar, __le16_to_cpu(ev->peer_id));
	अगर (!peer) अणु
		ath10k_warn(ar, "failed to find peer id %d for security indication",
			    __le16_to_cpu(ev->peer_id));
		जाओ out;
	पूर्ण

	sec_type = MS(ev->flags, HTT_SECURITY_TYPE);

	अगर (ev->flags & HTT_SECURITY_IS_UNICAST)
		sec_index = HTT_TXRX_SEC_UCAST;
	अन्यथा
		sec_index = HTT_TXRX_SEC_MCAST;

	peer->rx_pn[sec_index].sec_type = sec_type;
	peer->rx_pn[sec_index].pn_len = ath10k_htt_rx_pn_len(sec_type);

	स_रखो(peer->tids_last_pn_valid, 0, माप(peer->tids_last_pn_valid));
	स_रखो(peer->tids_last_pn, 0, माप(peer->tids_last_pn));

out:
	spin_unlock_bh(&ar->data_lock);
पूर्ण

bool ath10k_htt_t2h_msg_handler(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा htt_resp *resp = (काष्ठा htt_resp *)skb->data;
	क्रमागत htt_t2h_msg_type type;

	/* confirm alignment */
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, 4))
		ath10k_warn(ar, "unaligned htt message, expect trouble\n");

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx, msg_type: 0x%0X\n",
		   resp->hdr.msg_type);

	अगर (resp->hdr.msg_type >= ar->htt.t2h_msg_types_max) अणु
		ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx, unsupported msg_type: 0x%0X\n max: 0x%0X",
			   resp->hdr.msg_type, ar->htt.t2h_msg_types_max);
		वापस true;
	पूर्ण
	type = ar->htt.t2h_msg_types[resp->hdr.msg_type];

	चयन (type) अणु
	हाल HTT_T2H_MSG_TYPE_VERSION_CONF: अणु
		htt->target_version_major = resp->ver_resp.major;
		htt->target_version_minor = resp->ver_resp.minor;
		complete(&htt->target_version_received);
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_RX_IND:
		अगर (ar->bus_param.dev_type != ATH10K_DEV_TYPE_HL) अणु
			ath10k_htt_rx_proc_rx_ind_ll(htt, &resp->rx_ind);
		पूर्ण अन्यथा अणु
			skb_queue_tail(&htt->rx_indication_head, skb);
			वापस false;
		पूर्ण
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_PEER_MAP: अणु
		काष्ठा htt_peer_map_event ev = अणु
			.vdev_id = resp->peer_map.vdev_id,
			.peer_id = __le16_to_cpu(resp->peer_map.peer_id),
		पूर्ण;
		स_नकल(ev.addr, resp->peer_map.addr, माप(ev.addr));
		ath10k_peer_map_event(htt, &ev);
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_PEER_UNMAP: अणु
		काष्ठा htt_peer_unmap_event ev = अणु
			.peer_id = __le16_to_cpu(resp->peer_unmap.peer_id),
		पूर्ण;
		ath10k_peer_unmap_event(htt, &ev);
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_MGMT_TX_COMPLETION: अणु
		काष्ठा htt_tx_करोne tx_करोne = अणुपूर्ण;
		काष्ठा ath10k_htt *htt = &ar->htt;
		काष्ठा ath10k_htc *htc = &ar->htc;
		काष्ठा ath10k_htc_ep *ep = &ar->htc.endpoपूर्णांक[htt->eid];
		पूर्णांक status = __le32_to_cpu(resp->mgmt_tx_completion.status);
		पूर्णांक info = __le32_to_cpu(resp->mgmt_tx_completion.info);

		tx_करोne.msdu_id = __le32_to_cpu(resp->mgmt_tx_completion.desc_id);

		चयन (status) अणु
		हाल HTT_MGMT_TX_STATUS_OK:
			tx_करोne.status = HTT_TX_COMPL_STATE_ACK;
			अगर (test_bit(WMI_SERVICE_HTT_MGMT_TX_COMP_VALID_FLAGS,
				     ar->wmi.svc_map) &&
			    (resp->mgmt_tx_completion.flags &
			     HTT_MGMT_TX_CMPL_FLAG_ACK_RSSI)) अणु
				tx_करोne.ack_rssi =
				FIELD_GET(HTT_MGMT_TX_CMPL_INFO_ACK_RSSI_MASK,
					  info);
			पूर्ण
			अवरोध;
		हाल HTT_MGMT_TX_STATUS_RETRY:
			tx_करोne.status = HTT_TX_COMPL_STATE_NOACK;
			अवरोध;
		हाल HTT_MGMT_TX_STATUS_DROP:
			tx_करोne.status = HTT_TX_COMPL_STATE_DISCARD;
			अवरोध;
		पूर्ण

		अगर (htt->disable_tx_comp) अणु
			spin_lock_bh(&htc->tx_lock);
			ep->tx_credits++;
			spin_unlock_bh(&htc->tx_lock);
		पूर्ण

		status = ath10k_txrx_tx_unref(htt, &tx_करोne);
		अगर (!status) अणु
			spin_lock_bh(&htt->tx_lock);
			ath10k_htt_tx_mgmt_dec_pending(htt);
			spin_unlock_bh(&htt->tx_lock);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_TX_COMPL_IND:
		ath10k_htt_rx_tx_compl_ind(htt->ar, skb);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_SEC_IND: अणु
		काष्ठा ath10k *ar = htt->ar;
		काष्ठा htt_security_indication *ev = &resp->security_indication;

		ath10k_htt_rx_sec_ind_handler(ar, ev);
		ath10k_dbg(ar, ATH10K_DBG_HTT,
			   "sec ind peer_id %d unicast %d type %d\n",
			  __le16_to_cpu(ev->peer_id),
			  !!(ev->flags & HTT_SECURITY_IS_UNICAST),
			  MS(ev->flags, HTT_SECURITY_TYPE));
		complete(&ar->install_key_करोne);
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_RX_FRAG_IND: अणु
		ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य, "htt event: ",
				skb->data, skb->len);
		atomic_inc(&htt->num_mpdus_पढ़ोy);

		वापस ath10k_htt_rx_proc_rx_frag_ind(htt,
						      &resp->rx_frag_ind,
						      skb);
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_TEST:
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_STATS_CONF:
		trace_ath10k_htt_stats(ar, skb->data, skb->len);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_TX_INSPECT_IND:
		/* Firmware can वापस tx frames अगर it's unable to fully
		 * process them and suspects host may be able to fix it. ath10k
		 * sends all tx frames as alपढ़ोy inspected so this shouldn't
		 * happen unless fw has a bug.
		 */
		ath10k_warn(ar, "received an unexpected htt tx inspect event\n");
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_RX_ADDBA:
		ath10k_htt_rx_addba(ar, resp);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_RX_DELBA:
		ath10k_htt_rx_delba(ar, resp);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_PKTLOG: अणु
		trace_ath10k_htt_pktlog(ar, resp->pktlog_msg.payload,
					skb->len -
					दुरत्व(काष्ठा htt_resp,
						 pktlog_msg.payload));

		अगर (ath10k_peer_stats_enabled(ar))
			ath10k_fetch_10_2_tx_stats(ar,
						   resp->pktlog_msg.payload);
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_RX_FLUSH: अणु
		/* Ignore this event because mac80211 takes care of Rx
		 * aggregation reordering.
		 */
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_RX_IN_ORD_PADDR_IND: अणु
		skb_queue_tail(&htt->rx_in_ord_compl_q, skb);
		वापस false;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_TX_CREDIT_UPDATE_IND: अणु
		काष्ठा ath10k_htt *htt = &ar->htt;
		काष्ठा ath10k_htc *htc = &ar->htc;
		काष्ठा ath10k_htc_ep *ep = &ar->htc.endpoपूर्णांक[htt->eid];
		u32 msg_word = __le32_to_cpu(*(__le32 *)resp);
		पूर्णांक htt_credit_delta;

		htt_credit_delta = HTT_TX_CREDIT_DELTA_ABS_GET(msg_word);
		अगर (HTT_TX_CREDIT_SIGN_BIT_GET(msg_word))
			htt_credit_delta = -htt_credit_delta;

		ath10k_dbg(ar, ATH10K_DBG_HTT,
			   "htt credit update delta %d\n",
			   htt_credit_delta);

		अगर (htt->disable_tx_comp) अणु
			spin_lock_bh(&htc->tx_lock);
			ep->tx_credits += htt_credit_delta;
			spin_unlock_bh(&htc->tx_lock);
			ath10k_dbg(ar, ATH10K_DBG_HTT,
				   "htt credit total %d\n",
				   ep->tx_credits);
			ep->ep_ops.ep_tx_credits(htc->ar);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_CHAN_CHANGE: अणु
		u32 phymode = __le32_to_cpu(resp->chan_change.phymode);
		u32 freq = __le32_to_cpu(resp->chan_change.freq);

		ar->tgt_oper_chan = ieee80211_get_channel(ar->hw->wiphy, freq);
		ath10k_dbg(ar, ATH10K_DBG_HTT,
			   "htt chan change freq %u phymode %s\n",
			   freq, ath10k_wmi_phymode_str(phymode));
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_AGGR_CONF:
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_TX_FETCH_IND: अणु
		काष्ठा sk_buff *tx_fetch_ind = skb_copy(skb, GFP_ATOMIC);

		अगर (!tx_fetch_ind) अणु
			ath10k_warn(ar, "failed to copy htt tx fetch ind\n");
			अवरोध;
		पूर्ण
		skb_queue_tail(&htt->tx_fetch_ind_q, tx_fetch_ind);
		अवरोध;
	पूर्ण
	हाल HTT_T2H_MSG_TYPE_TX_FETCH_CONFIRM:
		ath10k_htt_rx_tx_fetch_confirm(ar, skb);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_TX_MODE_SWITCH_IND:
		ath10k_htt_rx_tx_mode_चयन_ind(ar, skb);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_PEER_STATS:
		ath10k_htt_fetch_peer_stats(ar, skb);
		अवरोध;
	हाल HTT_T2H_MSG_TYPE_EN_STATS:
	शेष:
		ath10k_warn(ar, "htt event (%d) not handled\n",
			    resp->hdr.msg_type);
		ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य, "htt event: ",
				skb->data, skb->len);
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL(ath10k_htt_t2h_msg_handler);

व्योम ath10k_htt_rx_pktlog_completion_handler(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb)
अणु
	trace_ath10k_htt_pktlog(ar, skb->data, skb->len);
	dev_kमुक्त_skb_any(skb);
पूर्ण
EXPORT_SYMBOL(ath10k_htt_rx_pktlog_completion_handler);

अटल पूर्णांक ath10k_htt_rx_deliver_msdu(काष्ठा ath10k *ar, पूर्णांक quota, पूर्णांक budget)
अणु
	काष्ठा sk_buff *skb;

	जबतक (quota < budget) अणु
		अगर (skb_queue_empty(&ar->htt.rx_msdus_q))
			अवरोध;

		skb = skb_dequeue(&ar->htt.rx_msdus_q);
		अगर (!skb)
			अवरोध;
		ath10k_process_rx(ar, skb);
		quota++;
	पूर्ण

	वापस quota;
पूर्ण

पूर्णांक ath10k_htt_rx_hl_indication(काष्ठा ath10k *ar, पूर्णांक budget)
अणु
	काष्ठा htt_resp *resp;
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा sk_buff *skb;
	bool release;
	पूर्णांक quota;

	क्रम (quota = 0; quota < budget; quota++) अणु
		skb = skb_dequeue(&htt->rx_indication_head);
		अगर (!skb)
			अवरोध;

		resp = (काष्ठा htt_resp *)skb->data;

		release = ath10k_htt_rx_proc_rx_ind_hl(htt,
						       &resp->rx_ind_hl,
						       skb,
						       HTT_RX_PN_CHECK,
						       HTT_RX_NON_TKIP_MIC);

		अगर (release)
			dev_kमुक्त_skb_any(skb);

		ath10k_dbg(ar, ATH10K_DBG_HTT, "rx indication poll pending count:%d\n",
			   skb_queue_len(&htt->rx_indication_head));
	पूर्ण
	वापस quota;
पूर्ण
EXPORT_SYMBOL(ath10k_htt_rx_hl_indication);

पूर्णांक ath10k_htt_txrx_compl_task(काष्ठा ath10k *ar, पूर्णांक budget)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा htt_tx_करोne tx_करोne = अणुपूर्ण;
	काष्ठा sk_buff_head tx_ind_q;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक quota = 0, करोne, ret;
	bool resched_napi = false;

	__skb_queue_head_init(&tx_ind_q);

	/* Process pending frames beक्रमe dequeuing more data
	 * from hardware.
	 */
	quota = ath10k_htt_rx_deliver_msdu(ar, quota, budget);
	अगर (quota == budget) अणु
		resched_napi = true;
		जाओ निकास;
	पूर्ण

	जबतक ((skb = skb_dequeue(&htt->rx_in_ord_compl_q))) अणु
		spin_lock_bh(&htt->rx_ring.lock);
		ret = ath10k_htt_rx_in_ord_ind(ar, skb);
		spin_unlock_bh(&htt->rx_ring.lock);

		dev_kमुक्त_skb_any(skb);
		अगर (ret == -EIO) अणु
			resched_napi = true;
			जाओ निकास;
		पूर्ण
	पूर्ण

	जबतक (atomic_पढ़ो(&htt->num_mpdus_पढ़ोy)) अणु
		ret = ath10k_htt_rx_handle_amsdu(htt);
		अगर (ret == -EIO) अणु
			resched_napi = true;
			जाओ निकास;
		पूर्ण
		atomic_dec(&htt->num_mpdus_पढ़ोy);
	पूर्ण

	/* Deliver received data after processing data from hardware */
	quota = ath10k_htt_rx_deliver_msdu(ar, quota, budget);

	/* From NAPI करोcumentation:
	 *  The napi poll() function may also process TX completions, in which
	 *  हाल अगर it processes the entire TX ring then it should count that
	 *  work as the rest of the budget.
	 */
	अगर ((quota < budget) && !kfअगरo_is_empty(&htt->txकरोne_fअगरo))
		quota = budget;

	/* kfअगरo_get: called only within txrx_tasklet so it's neatly serialized.
	 * From kfअगरo_get() करोcumentation:
	 *  Note that with only one concurrent पढ़ोer and one concurrent ग_लिखोr,
	 *  you करोn't need extra locking to use these macro.
	 */
	जबतक (kfअगरo_get(&htt->txकरोne_fअगरo, &tx_करोne))
		ath10k_txrx_tx_unref(htt, &tx_करोne);

	ath10k_mac_tx_push_pending(ar);

	spin_lock_irqsave(&htt->tx_fetch_ind_q.lock, flags);
	skb_queue_splice_init(&htt->tx_fetch_ind_q, &tx_ind_q);
	spin_unlock_irqrestore(&htt->tx_fetch_ind_q.lock, flags);

	जबतक ((skb = __skb_dequeue(&tx_ind_q))) अणु
		ath10k_htt_rx_tx_fetch_ind(ar, skb);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

निकास:
	ath10k_htt_rx_msdu_buff_replenish(htt);
	/* In हाल of rx failure or more data to पढ़ो, report budget
	 * to reschedule NAPI poll
	 */
	करोne = resched_napi ? budget : quota;

	वापस करोne;
पूर्ण
EXPORT_SYMBOL(ath10k_htt_txrx_compl_task);

अटल स्थिर काष्ठा ath10k_htt_rx_ops htt_rx_ops_32 = अणु
	.htt_get_rx_ring_size = ath10k_htt_get_rx_ring_size_32,
	.htt_config_paddrs_ring = ath10k_htt_config_paddrs_ring_32,
	.htt_set_paddrs_ring = ath10k_htt_set_paddrs_ring_32,
	.htt_get_vaddr_ring = ath10k_htt_get_vaddr_ring_32,
	.htt_reset_paddrs_ring = ath10k_htt_reset_paddrs_ring_32,
पूर्ण;

अटल स्थिर काष्ठा ath10k_htt_rx_ops htt_rx_ops_64 = अणु
	.htt_get_rx_ring_size = ath10k_htt_get_rx_ring_size_64,
	.htt_config_paddrs_ring = ath10k_htt_config_paddrs_ring_64,
	.htt_set_paddrs_ring = ath10k_htt_set_paddrs_ring_64,
	.htt_get_vaddr_ring = ath10k_htt_get_vaddr_ring_64,
	.htt_reset_paddrs_ring = ath10k_htt_reset_paddrs_ring_64,
पूर्ण;

अटल स्थिर काष्ठा ath10k_htt_rx_ops htt_rx_ops_hl = अणु
	.htt_rx_proc_rx_frag_ind = ath10k_htt_rx_proc_rx_frag_ind_hl,
पूर्ण;

व्योम ath10k_htt_set_rx_ops(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;

	अगर (ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL)
		htt->rx_ops = &htt_rx_ops_hl;
	अन्यथा अगर (ar->hw_params.target_64bit)
		htt->rx_ops = &htt_rx_ops_64;
	अन्यथा
		htt->rx_ops = &htt_rx_ops_32;
पूर्ण
