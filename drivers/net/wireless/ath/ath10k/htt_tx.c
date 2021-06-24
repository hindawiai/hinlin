<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 */

#समावेश <linux/etherdevice.h>
#समावेश "htt.h"
#समावेश "mac.h"
#समावेश "hif.h"
#समावेश "txrx.h"
#समावेश "debug.h"

अटल u8 ath10k_htt_tx_txq_calc_size(माप_प्रकार count)
अणु
	पूर्णांक exp;
	पूर्णांक factor;

	exp = 0;
	factor = count >> 7;

	जबतक (factor >= 64 && exp < 4) अणु
		factor >>= 3;
		exp++;
	पूर्ण

	अगर (exp == 4)
		वापस 0xff;

	अगर (count > 0)
		factor = max(1, factor);

	वापस SM(exp, HTT_TX_Q_STATE_ENTRY_EXP) |
	       SM(factor, HTT_TX_Q_STATE_ENTRY_FACTOR);
पूर्ण

अटल व्योम __ath10k_htt_tx_txq_recalc(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_sta *arsta;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)txq->vअगर->drv_priv;
	अचिन्हित दीर्घ frame_cnt;
	अचिन्हित दीर्घ byte_cnt;
	पूर्णांक idx;
	u32 bit;
	u16 peer_id;
	u8 tid;
	u8 count;

	lockdep_निश्चित_held(&ar->htt.tx_lock);

	अगर (!ar->htt.tx_q_state.enabled)
		वापस;

	अगर (ar->htt.tx_q_state.mode != HTT_TX_MODE_SWITCH_PUSH_PULL)
		वापस;

	अगर (txq->sta) अणु
		arsta = (व्योम *)txq->sta->drv_priv;
		peer_id = arsta->peer_id;
	पूर्ण अन्यथा अणु
		peer_id = arvअगर->peer_id;
	पूर्ण

	tid = txq->tid;
	bit = BIT(peer_id % 32);
	idx = peer_id / 32;

	ieee80211_txq_get_depth(txq, &frame_cnt, &byte_cnt);
	count = ath10k_htt_tx_txq_calc_size(byte_cnt);

	अगर (unlikely(peer_id >= ar->htt.tx_q_state.num_peers) ||
	    unlikely(tid >= ar->htt.tx_q_state.num_tids)) अणु
		ath10k_warn(ar, "refusing to update txq for peer_id %u tid %u due to out of bounds\n",
			    peer_id, tid);
		वापस;
	पूर्ण

	ar->htt.tx_q_state.vaddr->count[tid][peer_id] = count;
	ar->htt.tx_q_state.vaddr->map[tid][idx] &= ~bit;
	ar->htt.tx_q_state.vaddr->map[tid][idx] |= count ? bit : 0;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx txq state update peer_id %u tid %u count %u\n",
		   peer_id, tid, count);
पूर्ण

अटल व्योम __ath10k_htt_tx_txq_sync(काष्ठा ath10k *ar)
अणु
	u32 seq;
	माप_प्रकार size;

	lockdep_निश्चित_held(&ar->htt.tx_lock);

	अगर (!ar->htt.tx_q_state.enabled)
		वापस;

	अगर (ar->htt.tx_q_state.mode != HTT_TX_MODE_SWITCH_PUSH_PULL)
		वापस;

	seq = le32_to_cpu(ar->htt.tx_q_state.vaddr->seq);
	seq++;
	ar->htt.tx_q_state.vaddr->seq = cpu_to_le32(seq);

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx txq state update commit seq %u\n",
		   seq);

	size = माप(*ar->htt.tx_q_state.vaddr);
	dma_sync_single_क्रम_device(ar->dev,
				   ar->htt.tx_q_state.paddr,
				   size,
				   DMA_TO_DEVICE);
पूर्ण

व्योम ath10k_htt_tx_txq_recalc(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ath10k *ar = hw->priv;

	spin_lock_bh(&ar->htt.tx_lock);
	__ath10k_htt_tx_txq_recalc(hw, txq);
	spin_unlock_bh(&ar->htt.tx_lock);
पूर्ण

व्योम ath10k_htt_tx_txq_sync(काष्ठा ath10k *ar)
अणु
	spin_lock_bh(&ar->htt.tx_lock);
	__ath10k_htt_tx_txq_sync(ar);
	spin_unlock_bh(&ar->htt.tx_lock);
पूर्ण

व्योम ath10k_htt_tx_txq_update(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ath10k *ar = hw->priv;

	spin_lock_bh(&ar->htt.tx_lock);
	__ath10k_htt_tx_txq_recalc(hw, txq);
	__ath10k_htt_tx_txq_sync(ar);
	spin_unlock_bh(&ar->htt.tx_lock);
पूर्ण

व्योम ath10k_htt_tx_dec_pending(काष्ठा ath10k_htt *htt)
अणु
	lockdep_निश्चित_held(&htt->tx_lock);

	htt->num_pending_tx--;
	अगर (htt->num_pending_tx == htt->max_num_pending_tx - 1)
		ath10k_mac_tx_unlock(htt->ar, ATH10K_TX_PAUSE_Q_FULL);
पूर्ण

पूर्णांक ath10k_htt_tx_inc_pending(काष्ठा ath10k_htt *htt)
अणु
	lockdep_निश्चित_held(&htt->tx_lock);

	अगर (htt->num_pending_tx >= htt->max_num_pending_tx)
		वापस -EBUSY;

	htt->num_pending_tx++;
	अगर (htt->num_pending_tx == htt->max_num_pending_tx)
		ath10k_mac_tx_lock(htt->ar, ATH10K_TX_PAUSE_Q_FULL);

	वापस 0;
पूर्ण

पूर्णांक ath10k_htt_tx_mgmt_inc_pending(काष्ठा ath10k_htt *htt, bool is_mgmt,
				   bool is_presp)
अणु
	काष्ठा ath10k *ar = htt->ar;

	lockdep_निश्चित_held(&htt->tx_lock);

	अगर (!is_mgmt || !ar->hw_params.max_probe_resp_desc_thres)
		वापस 0;

	अगर (is_presp &&
	    ar->hw_params.max_probe_resp_desc_thres < htt->num_pending_mgmt_tx)
		वापस -EBUSY;

	htt->num_pending_mgmt_tx++;

	वापस 0;
पूर्ण

व्योम ath10k_htt_tx_mgmt_dec_pending(काष्ठा ath10k_htt *htt)
अणु
	lockdep_निश्चित_held(&htt->tx_lock);

	अगर (!htt->ar->hw_params.max_probe_resp_desc_thres)
		वापस;

	htt->num_pending_mgmt_tx--;
पूर्ण

पूर्णांक ath10k_htt_tx_alloc_msdu_id(काष्ठा ath10k_htt *htt, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k *ar = htt->ar;
	पूर्णांक ret;

	spin_lock_bh(&htt->tx_lock);
	ret = idr_alloc(&htt->pending_tx, skb, 0,
			htt->max_num_pending_tx, GFP_ATOMIC);
	spin_unlock_bh(&htt->tx_lock);

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx alloc msdu_id %d\n", ret);

	वापस ret;
पूर्ण

व्योम ath10k_htt_tx_मुक्त_msdu_id(काष्ठा ath10k_htt *htt, u16 msdu_id)
अणु
	काष्ठा ath10k *ar = htt->ar;

	lockdep_निश्चित_held(&htt->tx_lock);

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt tx free msdu_id %u\n", msdu_id);

	idr_हटाओ(&htt->pending_tx, msdu_id);
पूर्ण

अटल व्योम ath10k_htt_tx_मुक्त_cont_txbuf_32(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	माप_प्रकार size;

	अगर (!htt->txbuf.vaddr_txbuff_32)
		वापस;

	size = htt->txbuf.size;
	dma_मुक्त_coherent(ar->dev, size, htt->txbuf.vaddr_txbuff_32,
			  htt->txbuf.paddr);
	htt->txbuf.vaddr_txbuff_32 = शून्य;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_alloc_cont_txbuf_32(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	माप_प्रकार size;

	size = htt->max_num_pending_tx *
			माप(काष्ठा ath10k_htt_txbuf_32);

	htt->txbuf.vaddr_txbuff_32 = dma_alloc_coherent(ar->dev, size,
							&htt->txbuf.paddr,
							GFP_KERNEL);
	अगर (!htt->txbuf.vaddr_txbuff_32)
		वापस -ENOMEM;

	htt->txbuf.size = size;

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_tx_मुक्त_cont_txbuf_64(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	माप_प्रकार size;

	अगर (!htt->txbuf.vaddr_txbuff_64)
		वापस;

	size = htt->txbuf.size;
	dma_मुक्त_coherent(ar->dev, size, htt->txbuf.vaddr_txbuff_64,
			  htt->txbuf.paddr);
	htt->txbuf.vaddr_txbuff_64 = शून्य;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_alloc_cont_txbuf_64(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	माप_प्रकार size;

	size = htt->max_num_pending_tx *
			माप(काष्ठा ath10k_htt_txbuf_64);

	htt->txbuf.vaddr_txbuff_64 = dma_alloc_coherent(ar->dev, size,
							&htt->txbuf.paddr,
							GFP_KERNEL);
	अगर (!htt->txbuf.vaddr_txbuff_64)
		वापस -ENOMEM;

	htt->txbuf.size = size;

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_tx_मुक्त_cont_frag_desc_32(काष्ठा ath10k_htt *htt)
अणु
	माप_प्रकार size;

	अगर (!htt->frag_desc.vaddr_desc_32)
		वापस;

	size = htt->max_num_pending_tx *
			माप(काष्ठा htt_msdu_ext_desc);

	dma_मुक्त_coherent(htt->ar->dev,
			  size,
			  htt->frag_desc.vaddr_desc_32,
			  htt->frag_desc.paddr);

	htt->frag_desc.vaddr_desc_32 = शून्य;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_alloc_cont_frag_desc_32(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	माप_प्रकार size;

	अगर (!ar->hw_params.continuous_frag_desc)
		वापस 0;

	size = htt->max_num_pending_tx *
			माप(काष्ठा htt_msdu_ext_desc);
	htt->frag_desc.vaddr_desc_32 = dma_alloc_coherent(ar->dev, size,
							  &htt->frag_desc.paddr,
							  GFP_KERNEL);
	अगर (!htt->frag_desc.vaddr_desc_32) अणु
		ath10k_err(ar, "failed to alloc fragment desc memory\n");
		वापस -ENOMEM;
	पूर्ण
	htt->frag_desc.size = size;

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_tx_मुक्त_cont_frag_desc_64(काष्ठा ath10k_htt *htt)
अणु
	माप_प्रकार size;

	अगर (!htt->frag_desc.vaddr_desc_64)
		वापस;

	size = htt->max_num_pending_tx *
			माप(काष्ठा htt_msdu_ext_desc_64);

	dma_मुक्त_coherent(htt->ar->dev,
			  size,
			  htt->frag_desc.vaddr_desc_64,
			  htt->frag_desc.paddr);

	htt->frag_desc.vaddr_desc_64 = शून्य;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_alloc_cont_frag_desc_64(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	माप_प्रकार size;

	अगर (!ar->hw_params.continuous_frag_desc)
		वापस 0;

	size = htt->max_num_pending_tx *
			माप(काष्ठा htt_msdu_ext_desc_64);

	htt->frag_desc.vaddr_desc_64 = dma_alloc_coherent(ar->dev, size,
							  &htt->frag_desc.paddr,
							  GFP_KERNEL);
	अगर (!htt->frag_desc.vaddr_desc_64) अणु
		ath10k_err(ar, "failed to alloc fragment desc memory\n");
		वापस -ENOMEM;
	पूर्ण
	htt->frag_desc.size = size;

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_tx_मुक्त_txq(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	माप_प्रकार size;

	अगर (!test_bit(ATH10K_FW_FEATURE_PEER_FLOW_CONTROL,
		      ar->running_fw->fw_file.fw_features))
		वापस;

	size = माप(*htt->tx_q_state.vaddr);

	dma_unmap_single(ar->dev, htt->tx_q_state.paddr, size, DMA_TO_DEVICE);
	kमुक्त(htt->tx_q_state.vaddr);
पूर्ण

अटल पूर्णांक ath10k_htt_tx_alloc_txq(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	माप_प्रकार size;
	पूर्णांक ret;

	अगर (!test_bit(ATH10K_FW_FEATURE_PEER_FLOW_CONTROL,
		      ar->running_fw->fw_file.fw_features))
		वापस 0;

	htt->tx_q_state.num_peers = HTT_TX_Q_STATE_NUM_PEERS;
	htt->tx_q_state.num_tids = HTT_TX_Q_STATE_NUM_TIDS;
	htt->tx_q_state.type = HTT_Q_DEPTH_TYPE_BYTES;

	size = माप(*htt->tx_q_state.vaddr);
	htt->tx_q_state.vaddr = kzalloc(size, GFP_KERNEL);
	अगर (!htt->tx_q_state.vaddr)
		वापस -ENOMEM;

	htt->tx_q_state.paddr = dma_map_single(ar->dev, htt->tx_q_state.vaddr,
					       size, DMA_TO_DEVICE);
	ret = dma_mapping_error(ar->dev, htt->tx_q_state.paddr);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to dma map tx_q_state: %d\n", ret);
		kमुक्त(htt->tx_q_state.vaddr);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_tx_मुक्त_txकरोne_fअगरo(काष्ठा ath10k_htt *htt)
अणु
	WARN_ON(!kfअगरo_is_empty(&htt->txकरोne_fअगरo));
	kfअगरo_मुक्त(&htt->txकरोne_fअगरo);
पूर्ण

अटल पूर्णांक ath10k_htt_tx_alloc_txकरोne_fअगरo(काष्ठा ath10k_htt *htt)
अणु
	पूर्णांक ret;
	माप_प्रकार size;

	size = roundup_घात_of_two(htt->max_num_pending_tx);
	ret = kfअगरo_alloc(&htt->txकरोne_fअगरo, size, GFP_KERNEL);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_alloc_buf(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	पूर्णांक ret;

	ret = ath10k_htt_alloc_txbuff(htt);
	अगर (ret) अणु
		ath10k_err(ar, "failed to alloc cont tx buffer: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_htt_alloc_frag_desc(htt);
	अगर (ret) अणु
		ath10k_err(ar, "failed to alloc cont frag desc: %d\n", ret);
		जाओ मुक्त_txbuf;
	पूर्ण

	ret = ath10k_htt_tx_alloc_txq(htt);
	अगर (ret) अणु
		ath10k_err(ar, "failed to alloc txq: %d\n", ret);
		जाओ मुक्त_frag_desc;
	पूर्ण

	ret = ath10k_htt_tx_alloc_txकरोne_fअगरo(htt);
	अगर (ret) अणु
		ath10k_err(ar, "failed to alloc txdone fifo: %d\n", ret);
		जाओ मुक्त_txq;
	पूर्ण

	वापस 0;

मुक्त_txq:
	ath10k_htt_tx_मुक्त_txq(htt);

मुक्त_frag_desc:
	ath10k_htt_मुक्त_frag_desc(htt);

मुक्त_txbuf:
	ath10k_htt_मुक्त_txbuff(htt);

	वापस ret;
पूर्ण

पूर्णांक ath10k_htt_tx_start(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "htt tx max num pending tx %d\n",
		   htt->max_num_pending_tx);

	spin_lock_init(&htt->tx_lock);
	idr_init(&htt->pending_tx);

	अगर (htt->tx_mem_allocated)
		वापस 0;

	अगर (ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL)
		वापस 0;

	ret = ath10k_htt_tx_alloc_buf(htt);
	अगर (ret)
		जाओ मुक्त_idr_pending_tx;

	htt->tx_mem_allocated = true;

	वापस 0;

मुक्त_idr_pending_tx:
	idr_destroy(&htt->pending_tx);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_clean_up_pending(पूर्णांक msdu_id, व्योम *skb, व्योम *ctx)
अणु
	काष्ठा ath10k *ar = ctx;
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा htt_tx_करोne tx_करोne = अणु0पूर्ण;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "force cleanup msdu_id %u\n", msdu_id);

	tx_करोne.msdu_id = msdu_id;
	tx_करोne.status = HTT_TX_COMPL_STATE_DISCARD;

	ath10k_txrx_tx_unref(htt, &tx_करोne);

	वापस 0;
पूर्ण

व्योम ath10k_htt_tx_destroy(काष्ठा ath10k_htt *htt)
अणु
	अगर (!htt->tx_mem_allocated)
		वापस;

	ath10k_htt_मुक्त_txbuff(htt);
	ath10k_htt_tx_मुक्त_txq(htt);
	ath10k_htt_मुक्त_frag_desc(htt);
	ath10k_htt_tx_मुक्त_txकरोne_fअगरo(htt);
	htt->tx_mem_allocated = false;
पूर्ण

अटल व्योम ath10k_htt_flush_tx_queue(काष्ठा ath10k_htt *htt)
अणु
	ath10k_htc_stop_hl(htt->ar);
	idr_क्रम_each(&htt->pending_tx, ath10k_htt_tx_clean_up_pending, htt->ar);
पूर्ण

व्योम ath10k_htt_tx_stop(काष्ठा ath10k_htt *htt)
अणु
	ath10k_htt_flush_tx_queue(htt);
	idr_destroy(&htt->pending_tx);
पूर्ण

व्योम ath10k_htt_tx_मुक्त(काष्ठा ath10k_htt *htt)
अणु
	ath10k_htt_tx_stop(htt);
	ath10k_htt_tx_destroy(htt);
पूर्ण

व्योम ath10k_htt_op_ep_tx_credits(काष्ठा ath10k *ar)
अणु
	queue_work(ar->workqueue, &ar->bundle_tx_work);
पूर्ण

व्योम ath10k_htt_htc_tx_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा htt_tx_करोne tx_करोne = अणु0पूर्ण;
	काष्ठा htt_cmd_hdr *htt_hdr;
	काष्ठा htt_data_tx_desc *desc_hdr = शून्य;
	u16 flags1 = 0;
	u8 msg_type = 0;

	अगर (htt->disable_tx_comp) अणु
		htt_hdr = (काष्ठा htt_cmd_hdr *)skb->data;
		msg_type = htt_hdr->msg_type;

		अगर (msg_type == HTT_H2T_MSG_TYPE_TX_FRM) अणु
			desc_hdr = (काष्ठा htt_data_tx_desc *)
				(skb->data + माप(*htt_hdr));
			flags1 = __le16_to_cpu(desc_hdr->flags1);
			skb_pull(skb, माप(काष्ठा htt_cmd_hdr));
			skb_pull(skb, माप(काष्ठा htt_data_tx_desc));
		पूर्ण
	पूर्ण

	dev_kमुक्त_skb_any(skb);

	अगर ((!htt->disable_tx_comp) || (msg_type != HTT_H2T_MSG_TYPE_TX_FRM))
		वापस;

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt tx complete msdu id:%u ,flags1:%x\n",
		   __le16_to_cpu(desc_hdr->id), flags1);

	अगर (flags1 & HTT_DATA_TX_DESC_FLAGS1_TX_COMPLETE)
		वापस;

	tx_करोne.status = HTT_TX_COMPL_STATE_ACK;
	tx_करोne.msdu_id = __le16_to_cpu(desc_hdr->id);
	ath10k_txrx_tx_unref(&ar->htt, &tx_करोne);
पूर्ण

व्योम ath10k_htt_hअगर_tx_complete(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb_any(skb);
पूर्ण
EXPORT_SYMBOL(ath10k_htt_hअगर_tx_complete);

पूर्णांक ath10k_htt_h2t_ver_req_msg(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	पूर्णांक len = 0;
	पूर्णांक ret;

	len += माप(cmd->hdr);
	len += माप(cmd->ver_req);

	skb = ath10k_htc_alloc_skb(ar, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);
	cmd = (काष्ठा htt_cmd *)skb->data;
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_VERSION_REQ;

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_htt_h2t_stats_req(काष्ठा ath10k_htt *htt, u32 mask, u32 reset_mask,
			     u64 cookie)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा htt_stats_req *req;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	पूर्णांक len = 0, ret;

	len += माप(cmd->hdr);
	len += माप(cmd->stats_req);

	skb = ath10k_htc_alloc_skb(ar, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);
	cmd = (काष्ठा htt_cmd *)skb->data;
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_STATS_REQ;

	req = &cmd->stats_req;

	स_रखो(req, 0, माप(*req));

	/* currently we support only max 24 bit masks so no need to worry
	 * about endian support
	 */
	स_नकल(req->upload_types, &mask, 3);
	स_नकल(req->reset_types, &reset_mask, 3);
	req->stat_type = HTT_STATS_REQ_CFG_STAT_TYPE_INVALID;
	req->cookie_lsb = cpu_to_le32(cookie & 0xffffffff);
	req->cookie_msb = cpu_to_le32((cookie & 0xffffffff00000000ULL) >> 32);

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send htt type stats request: %d",
			    ret);
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_send_frag_desc_bank_cfg_32(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	काष्ठा htt_frag_desc_bank_cfg32 *cfg;
	पूर्णांक ret, size;
	u8 info;

	अगर (!ar->hw_params.continuous_frag_desc)
		वापस 0;

	अगर (!htt->frag_desc.paddr) अणु
		ath10k_warn(ar, "invalid frag desc memory\n");
		वापस -EINVAL;
	पूर्ण

	size = माप(cmd->hdr) + माप(cmd->frag_desc_bank_cfg32);
	skb = ath10k_htc_alloc_skb(ar, size);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, size);
	cmd = (काष्ठा htt_cmd *)skb->data;
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_FRAG_DESC_BANK_CFG;

	info = 0;
	info |= SM(htt->tx_q_state.type,
		   HTT_FRAG_DESC_BANK_CFG_INFO_Q_STATE_DEPTH_TYPE);

	अगर (test_bit(ATH10K_FW_FEATURE_PEER_FLOW_CONTROL,
		     ar->running_fw->fw_file.fw_features))
		info |= HTT_FRAG_DESC_BANK_CFG_INFO_Q_STATE_VALID;

	cfg = &cmd->frag_desc_bank_cfg32;
	cfg->info = info;
	cfg->num_banks = 1;
	cfg->desc_size = माप(काष्ठा htt_msdu_ext_desc);
	cfg->bank_base_addrs[0] = __cpu_to_le32(htt->frag_desc.paddr);
	cfg->bank_id[0].bank_min_id = 0;
	cfg->bank_id[0].bank_max_id = __cpu_to_le16(htt->max_num_pending_tx -
						    1);

	cfg->q_state.paddr = cpu_to_le32(htt->tx_q_state.paddr);
	cfg->q_state.num_peers = cpu_to_le16(htt->tx_q_state.num_peers);
	cfg->q_state.num_tids = cpu_to_le16(htt->tx_q_state.num_tids);
	cfg->q_state.record_size = HTT_TX_Q_STATE_ENTRY_SIZE;
	cfg->q_state.record_multiplier = HTT_TX_Q_STATE_ENTRY_MULTIPLIER;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt frag desc bank cmd\n");

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send frag desc bank cfg request: %d\n",
			    ret);
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_send_frag_desc_bank_cfg_64(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	काष्ठा htt_frag_desc_bank_cfg64 *cfg;
	पूर्णांक ret, size;
	u8 info;

	अगर (!ar->hw_params.continuous_frag_desc)
		वापस 0;

	अगर (!htt->frag_desc.paddr) अणु
		ath10k_warn(ar, "invalid frag desc memory\n");
		वापस -EINVAL;
	पूर्ण

	size = माप(cmd->hdr) + माप(cmd->frag_desc_bank_cfg64);
	skb = ath10k_htc_alloc_skb(ar, size);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, size);
	cmd = (काष्ठा htt_cmd *)skb->data;
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_FRAG_DESC_BANK_CFG;

	info = 0;
	info |= SM(htt->tx_q_state.type,
		   HTT_FRAG_DESC_BANK_CFG_INFO_Q_STATE_DEPTH_TYPE);

	अगर (test_bit(ATH10K_FW_FEATURE_PEER_FLOW_CONTROL,
		     ar->running_fw->fw_file.fw_features))
		info |= HTT_FRAG_DESC_BANK_CFG_INFO_Q_STATE_VALID;

	cfg = &cmd->frag_desc_bank_cfg64;
	cfg->info = info;
	cfg->num_banks = 1;
	cfg->desc_size = माप(काष्ठा htt_msdu_ext_desc_64);
	cfg->bank_base_addrs[0] =  __cpu_to_le64(htt->frag_desc.paddr);
	cfg->bank_id[0].bank_min_id = 0;
	cfg->bank_id[0].bank_max_id = __cpu_to_le16(htt->max_num_pending_tx -
						    1);

	cfg->q_state.paddr = cpu_to_le32(htt->tx_q_state.paddr);
	cfg->q_state.num_peers = cpu_to_le16(htt->tx_q_state.num_peers);
	cfg->q_state.num_tids = cpu_to_le16(htt->tx_q_state.num_tids);
	cfg->q_state.record_size = HTT_TX_Q_STATE_ENTRY_SIZE;
	cfg->q_state.record_multiplier = HTT_TX_Q_STATE_ENTRY_MULTIPLIER;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt frag desc bank cmd\n");

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send frag desc bank cfg request: %d\n",
			    ret);
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_htt_fill_rx_desc_offset_32(व्योम *rx_ring)
अणु
	काष्ठा htt_rx_ring_setup_ring32 *ring =
			(काष्ठा htt_rx_ring_setup_ring32 *)rx_ring;

#घोषणा desc_offset(x) (दुरत्व(काष्ठा htt_rx_desc, x) / 4)
	ring->mac80211_hdr_offset = __cpu_to_le16(desc_offset(rx_hdr_status));
	ring->msdu_payload_offset = __cpu_to_le16(desc_offset(msdu_payload));
	ring->ppdu_start_offset = __cpu_to_le16(desc_offset(ppdu_start));
	ring->ppdu_end_offset = __cpu_to_le16(desc_offset(ppdu_end));
	ring->mpdu_start_offset = __cpu_to_le16(desc_offset(mpdu_start));
	ring->mpdu_end_offset = __cpu_to_le16(desc_offset(mpdu_end));
	ring->msdu_start_offset = __cpu_to_le16(desc_offset(msdu_start));
	ring->msdu_end_offset = __cpu_to_le16(desc_offset(msdu_end));
	ring->rx_attention_offset = __cpu_to_le16(desc_offset(attention));
	ring->frag_info_offset = __cpu_to_le16(desc_offset(frag_info));
#अघोषित desc_offset
पूर्ण

अटल व्योम ath10k_htt_fill_rx_desc_offset_64(व्योम *rx_ring)
अणु
	काष्ठा htt_rx_ring_setup_ring64 *ring =
			(काष्ठा htt_rx_ring_setup_ring64 *)rx_ring;

#घोषणा desc_offset(x) (दुरत्व(काष्ठा htt_rx_desc, x) / 4)
	ring->mac80211_hdr_offset = __cpu_to_le16(desc_offset(rx_hdr_status));
	ring->msdu_payload_offset = __cpu_to_le16(desc_offset(msdu_payload));
	ring->ppdu_start_offset = __cpu_to_le16(desc_offset(ppdu_start));
	ring->ppdu_end_offset = __cpu_to_le16(desc_offset(ppdu_end));
	ring->mpdu_start_offset = __cpu_to_le16(desc_offset(mpdu_start));
	ring->mpdu_end_offset = __cpu_to_le16(desc_offset(mpdu_end));
	ring->msdu_start_offset = __cpu_to_le16(desc_offset(msdu_start));
	ring->msdu_end_offset = __cpu_to_le16(desc_offset(msdu_end));
	ring->rx_attention_offset = __cpu_to_le16(desc_offset(attention));
	ring->frag_info_offset = __cpu_to_le16(desc_offset(frag_info));
#अघोषित desc_offset
पूर्ण

अटल पूर्णांक ath10k_htt_send_rx_ring_cfg_32(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	काष्ठा htt_rx_ring_setup_ring32 *ring;
	स्थिर पूर्णांक num_rx_ring = 1;
	u16 flags;
	u32 fw_idx;
	पूर्णांक len;
	पूर्णांक ret;

	/*
	 * the HW expects the buffer to be an पूर्णांकegral number of 4-byte
	 * "words"
	 */
	BUILD_BUG_ON(!IS_ALIGNED(HTT_RX_BUF_SIZE, 4));
	BUILD_BUG_ON((HTT_RX_BUF_SIZE & HTT_MAX_CACHE_LINE_SIZE_MASK) != 0);

	len = माप(cmd->hdr) + माप(cmd->rx_setup_32.hdr)
	    + (माप(*ring) * num_rx_ring);
	skb = ath10k_htc_alloc_skb(ar, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);

	cmd = (काष्ठा htt_cmd *)skb->data;
	ring = &cmd->rx_setup_32.rings[0];

	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_RX_RING_CFG;
	cmd->rx_setup_32.hdr.num_rings = 1;

	/* FIXME: करो we need all of this? */
	flags = 0;
	flags |= HTT_RX_RING_FLAGS_MAC80211_HDR;
	flags |= HTT_RX_RING_FLAGS_MSDU_PAYLOAD;
	flags |= HTT_RX_RING_FLAGS_PPDU_START;
	flags |= HTT_RX_RING_FLAGS_PPDU_END;
	flags |= HTT_RX_RING_FLAGS_MPDU_START;
	flags |= HTT_RX_RING_FLAGS_MPDU_END;
	flags |= HTT_RX_RING_FLAGS_MSDU_START;
	flags |= HTT_RX_RING_FLAGS_MSDU_END;
	flags |= HTT_RX_RING_FLAGS_RX_ATTENTION;
	flags |= HTT_RX_RING_FLAGS_FRAG_INFO;
	flags |= HTT_RX_RING_FLAGS_UNICAST_RX;
	flags |= HTT_RX_RING_FLAGS_MULTICAST_RX;
	flags |= HTT_RX_RING_FLAGS_CTRL_RX;
	flags |= HTT_RX_RING_FLAGS_MGMT_RX;
	flags |= HTT_RX_RING_FLAGS_शून्य_RX;
	flags |= HTT_RX_RING_FLAGS_PHY_DATA_RX;

	fw_idx = __le32_to_cpu(*htt->rx_ring.alloc_idx.vaddr);

	ring->fw_idx_shaकरोw_reg_paddr =
		__cpu_to_le32(htt->rx_ring.alloc_idx.paddr);
	ring->rx_ring_base_paddr = __cpu_to_le32(htt->rx_ring.base_paddr);
	ring->rx_ring_len = __cpu_to_le16(htt->rx_ring.size);
	ring->rx_ring_bufsize = __cpu_to_le16(HTT_RX_BUF_SIZE);
	ring->flags = __cpu_to_le16(flags);
	ring->fw_idx_init_val = __cpu_to_le16(fw_idx);

	ath10k_htt_fill_rx_desc_offset_32(ring);
	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_send_rx_ring_cfg_64(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	काष्ठा htt_rx_ring_setup_ring64 *ring;
	स्थिर पूर्णांक num_rx_ring = 1;
	u16 flags;
	u32 fw_idx;
	पूर्णांक len;
	पूर्णांक ret;

	/* HW expects the buffer to be an पूर्णांकegral number of 4-byte
	 * "words"
	 */
	BUILD_BUG_ON(!IS_ALIGNED(HTT_RX_BUF_SIZE, 4));
	BUILD_BUG_ON((HTT_RX_BUF_SIZE & HTT_MAX_CACHE_LINE_SIZE_MASK) != 0);

	len = माप(cmd->hdr) + माप(cmd->rx_setup_64.hdr)
	    + (माप(*ring) * num_rx_ring);
	skb = ath10k_htc_alloc_skb(ar, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);

	cmd = (काष्ठा htt_cmd *)skb->data;
	ring = &cmd->rx_setup_64.rings[0];

	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_RX_RING_CFG;
	cmd->rx_setup_64.hdr.num_rings = 1;

	flags = 0;
	flags |= HTT_RX_RING_FLAGS_MAC80211_HDR;
	flags |= HTT_RX_RING_FLAGS_MSDU_PAYLOAD;
	flags |= HTT_RX_RING_FLAGS_PPDU_START;
	flags |= HTT_RX_RING_FLAGS_PPDU_END;
	flags |= HTT_RX_RING_FLAGS_MPDU_START;
	flags |= HTT_RX_RING_FLAGS_MPDU_END;
	flags |= HTT_RX_RING_FLAGS_MSDU_START;
	flags |= HTT_RX_RING_FLAGS_MSDU_END;
	flags |= HTT_RX_RING_FLAGS_RX_ATTENTION;
	flags |= HTT_RX_RING_FLAGS_FRAG_INFO;
	flags |= HTT_RX_RING_FLAGS_UNICAST_RX;
	flags |= HTT_RX_RING_FLAGS_MULTICAST_RX;
	flags |= HTT_RX_RING_FLAGS_CTRL_RX;
	flags |= HTT_RX_RING_FLAGS_MGMT_RX;
	flags |= HTT_RX_RING_FLAGS_शून्य_RX;
	flags |= HTT_RX_RING_FLAGS_PHY_DATA_RX;

	fw_idx = __le32_to_cpu(*htt->rx_ring.alloc_idx.vaddr);

	ring->fw_idx_shaकरोw_reg_paddr = __cpu_to_le64(htt->rx_ring.alloc_idx.paddr);
	ring->rx_ring_base_paddr = __cpu_to_le64(htt->rx_ring.base_paddr);
	ring->rx_ring_len = __cpu_to_le16(htt->rx_ring.size);
	ring->rx_ring_bufsize = __cpu_to_le16(HTT_RX_BUF_SIZE);
	ring->flags = __cpu_to_le16(flags);
	ring->fw_idx_init_val = __cpu_to_le16(fw_idx);

	ath10k_htt_fill_rx_desc_offset_64(ring);
	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_send_rx_ring_cfg_hl(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	काष्ठा htt_rx_ring_setup_ring32 *ring;
	स्थिर पूर्णांक num_rx_ring = 1;
	u16 flags;
	पूर्णांक len;
	पूर्णांक ret;

	/*
	 * the HW expects the buffer to be an पूर्णांकegral number of 4-byte
	 * "words"
	 */
	BUILD_BUG_ON(!IS_ALIGNED(HTT_RX_BUF_SIZE, 4));
	BUILD_BUG_ON((HTT_RX_BUF_SIZE & HTT_MAX_CACHE_LINE_SIZE_MASK) != 0);

	len = माप(cmd->hdr) + माप(cmd->rx_setup_32.hdr)
	    + (माप(*ring) * num_rx_ring);
	skb = ath10k_htc_alloc_skb(ar, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);

	cmd = (काष्ठा htt_cmd *)skb->data;
	ring = &cmd->rx_setup_32.rings[0];

	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_RX_RING_CFG;
	cmd->rx_setup_32.hdr.num_rings = 1;

	flags = 0;
	flags |= HTT_RX_RING_FLAGS_MSDU_PAYLOAD;
	flags |= HTT_RX_RING_FLAGS_UNICAST_RX;
	flags |= HTT_RX_RING_FLAGS_MULTICAST_RX;

	स_रखो(ring, 0, माप(*ring));
	ring->rx_ring_len = __cpu_to_le16(HTT_RX_RING_SIZE_MIN);
	ring->rx_ring_bufsize = __cpu_to_le16(HTT_RX_BUF_SIZE);
	ring->flags = __cpu_to_le16(flags);

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_h2t_aggr_cfg_msg_32(काष्ठा ath10k_htt *htt,
					  u8 max_subfrms_ampdu,
					  u8 max_subfrms_amsdu)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा htt_aggr_conf *aggr_conf;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	पूर्णांक len;
	पूर्णांक ret;

	/* Firmware शेषs are: amsdu = 3 and ampdu = 64 */

	अगर (max_subfrms_ampdu == 0 || max_subfrms_ampdu > 64)
		वापस -EINVAL;

	अगर (max_subfrms_amsdu == 0 || max_subfrms_amsdu > 31)
		वापस -EINVAL;

	len = माप(cmd->hdr);
	len += माप(cmd->aggr_conf);

	skb = ath10k_htc_alloc_skb(ar, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);
	cmd = (काष्ठा htt_cmd *)skb->data;
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_AGGR_CFG;

	aggr_conf = &cmd->aggr_conf;
	aggr_conf->max_num_ampdu_subframes = max_subfrms_ampdu;
	aggr_conf->max_num_amsdu_subframes = max_subfrms_amsdu;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt h2t aggr cfg msg amsdu %d ampdu %d",
		   aggr_conf->max_num_amsdu_subframes,
		   aggr_conf->max_num_ampdu_subframes);

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_htt_h2t_aggr_cfg_msg_v2(काष्ठा ath10k_htt *htt,
					  u8 max_subfrms_ampdu,
					  u8 max_subfrms_amsdu)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा htt_aggr_conf_v2 *aggr_conf;
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	पूर्णांक len;
	पूर्णांक ret;

	/* Firmware शेषs are: amsdu = 3 and ampdu = 64 */

	अगर (max_subfrms_ampdu == 0 || max_subfrms_ampdu > 64)
		वापस -EINVAL;

	अगर (max_subfrms_amsdu == 0 || max_subfrms_amsdu > 31)
		वापस -EINVAL;

	len = माप(cmd->hdr);
	len += माप(cmd->aggr_conf_v2);

	skb = ath10k_htc_alloc_skb(ar, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);
	cmd = (काष्ठा htt_cmd *)skb->data;
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_AGGR_CFG;

	aggr_conf = &cmd->aggr_conf_v2;
	aggr_conf->max_num_ampdu_subframes = max_subfrms_ampdu;
	aggr_conf->max_num_amsdu_subframes = max_subfrms_amsdu;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt h2t aggr cfg msg amsdu %d ampdu %d",
		   aggr_conf->max_num_amsdu_subframes,
		   aggr_conf->max_num_ampdu_subframes);

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_htt_tx_fetch_resp(काष्ठा ath10k *ar,
			     __le32 token,
			     __le16 fetch_seq_num,
			     काष्ठा htt_tx_fetch_record *records,
			     माप_प्रकार num_records)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा htt_cmd *cmd;
	स्थिर u16 resp_id = 0;
	पूर्णांक len = 0;
	पूर्णांक ret;

	/* Response IDs are echo-ed back only क्रम host driver convienence
	 * purposes. They aren't used क्रम anything in the driver yet so use 0.
	 */

	len += माप(cmd->hdr);
	len += माप(cmd->tx_fetch_resp);
	len += माप(cmd->tx_fetch_resp.records[0]) * num_records;

	skb = ath10k_htc_alloc_skb(ar, len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, len);
	cmd = (काष्ठा htt_cmd *)skb->data;
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_TX_FETCH_RESP;
	cmd->tx_fetch_resp.resp_id = cpu_to_le16(resp_id);
	cmd->tx_fetch_resp.fetch_seq_num = fetch_seq_num;
	cmd->tx_fetch_resp.num_records = cpu_to_le16(num_records);
	cmd->tx_fetch_resp.token = token;

	स_नकल(cmd->tx_fetch_resp.records, records,
	       माप(records[0]) * num_records);

	ret = ath10k_htc_send(&ar->htc, ar->htt.eid, skb);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit htc command: %d\n", ret);
		जाओ err_मुक्त_skb;
	पूर्ण

	वापस 0;

err_मुक्त_skb:
	dev_kमुक्त_skb_any(skb);

	वापस ret;
पूर्ण

अटल u8 ath10k_htt_tx_get_vdev_id(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);
	काष्ठा ath10k_vअगर *arvअगर;

	अगर (info->flags & IEEE80211_TX_CTL_TX_OFFCHAN) अणु
		वापस ar->scan.vdev_id;
	पूर्ण अन्यथा अगर (cb->vअगर) अणु
		arvअगर = (व्योम *)cb->vअगर->drv_priv;
		वापस arvअगर->vdev_id;
	पूर्ण अन्यथा अगर (ar->monitor_started) अणु
		वापस ar->monitor_vdev_id;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल u8 ath10k_htt_tx_get_tid(काष्ठा sk_buff *skb, bool is_eth)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);

	अगर (!is_eth && ieee80211_is_mgmt(hdr->frame_control))
		वापस HTT_DATA_TX_EXT_TID_MGMT;
	अन्यथा अगर (cb->flags & ATH10K_SKB_F_QOS)
		वापस skb->priority & IEEE80211_QOS_CTL_TID_MASK;
	अन्यथा
		वापस HTT_DATA_TX_EXT_TID_NON_QOS_MCAST_BCAST;
पूर्ण

पूर्णांक ath10k_htt_mgmt_tx(काष्ठा ath10k_htt *htt, काष्ठा sk_buff *msdu)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा device *dev = ar->dev;
	काष्ठा sk_buff *txdesc = शून्य;
	काष्ठा htt_cmd *cmd;
	काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(ar, msdu);
	पूर्णांक len = 0;
	पूर्णांक msdu_id = -1;
	पूर्णांक res;
	स्थिर u8 *peer_addr;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)msdu->data;

	len += माप(cmd->hdr);
	len += माप(cmd->mgmt_tx);

	res = ath10k_htt_tx_alloc_msdu_id(htt, msdu);
	अगर (res < 0)
		जाओ err;

	msdu_id = res;

	अगर ((ieee80211_is_action(hdr->frame_control) ||
	     ieee80211_is_deauth(hdr->frame_control) ||
	     ieee80211_is_disassoc(hdr->frame_control)) &&
	     ieee80211_has_रक्षित(hdr->frame_control)) अणु
		peer_addr = hdr->addr1;
		अगर (is_multicast_ether_addr(peer_addr)) अणु
			skb_put(msdu, माप(काष्ठा ieee80211_mmie_16));
		पूर्ण अन्यथा अणु
			अगर (skb_cb->ucast_cipher == WLAN_CIPHER_SUITE_GCMP ||
			    skb_cb->ucast_cipher == WLAN_CIPHER_SUITE_GCMP_256)
				skb_put(msdu, IEEE80211_GCMP_MIC_LEN);
			अन्यथा
				skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
		पूर्ण
	पूर्ण

	txdesc = ath10k_htc_alloc_skb(ar, len);
	अगर (!txdesc) अणु
		res = -ENOMEM;
		जाओ err_मुक्त_msdu_id;
	पूर्ण

	skb_cb->paddr = dma_map_single(dev, msdu->data, msdu->len,
				       DMA_TO_DEVICE);
	res = dma_mapping_error(dev, skb_cb->paddr);
	अगर (res) अणु
		res = -EIO;
		जाओ err_मुक्त_txdesc;
	पूर्ण

	skb_put(txdesc, len);
	cmd = (काष्ठा htt_cmd *)txdesc->data;
	स_रखो(cmd, 0, len);

	cmd->hdr.msg_type         = HTT_H2T_MSG_TYPE_MGMT_TX;
	cmd->mgmt_tx.msdu_paddr = __cpu_to_le32(ATH10K_SKB_CB(msdu)->paddr);
	cmd->mgmt_tx.len        = __cpu_to_le32(msdu->len);
	cmd->mgmt_tx.desc_id    = __cpu_to_le32(msdu_id);
	cmd->mgmt_tx.vdev_id    = __cpu_to_le32(vdev_id);
	स_नकल(cmd->mgmt_tx.hdr, msdu->data,
	       min_t(पूर्णांक, msdu->len, HTT_MGMT_FRM_HDR_DOWNLOAD_LEN));

	res = ath10k_htc_send(&htt->ar->htc, htt->eid, txdesc);
	अगर (res)
		जाओ err_unmap_msdu;

	वापस 0;

err_unmap_msdu:
	अगर (ar->bus_param.dev_type != ATH10K_DEV_TYPE_HL)
		dma_unmap_single(dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);
err_मुक्त_txdesc:
	dev_kमुक्त_skb_any(txdesc);
err_मुक्त_msdu_id:
	spin_lock_bh(&htt->tx_lock);
	ath10k_htt_tx_मुक्त_msdu_id(htt, msdu_id);
	spin_unlock_bh(&htt->tx_lock);
err:
	वापस res;
पूर्ण

#घोषणा HTT_TX_HL_NEEDED_HEADROOM \
	(अचिन्हित पूर्णांक)(माप(काष्ठा htt_cmd_hdr) + \
	माप(काष्ठा htt_data_tx_desc) + \
	माप(काष्ठा ath10k_htc_hdr))

अटल पूर्णांक ath10k_htt_tx_hl(काष्ठा ath10k_htt *htt, क्रमागत ath10k_hw_txrx_mode txmode,
			    काष्ठा sk_buff *msdu)
अणु
	काष्ठा ath10k *ar = htt->ar;
	पूर्णांक res, data_len;
	काष्ठा htt_cmd_hdr *cmd_hdr;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	काष्ठा htt_data_tx_desc *tx_desc;
	काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	काष्ठा sk_buff *पंचांगp_skb;
	bool is_eth = (txmode == ATH10K_HW_TXRX_ETHERNET);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(ar, msdu);
	u8 tid = ath10k_htt_tx_get_tid(msdu, is_eth);
	u8 flags0 = 0;
	u16 flags1 = 0;
	u16 msdu_id = 0;

	अगर ((ieee80211_is_action(hdr->frame_control) ||
	     ieee80211_is_deauth(hdr->frame_control) ||
	     ieee80211_is_disassoc(hdr->frame_control)) &&
	     ieee80211_has_रक्षित(hdr->frame_control)) अणु
		skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
	पूर्ण

	data_len = msdu->len;

	चयन (txmode) अणु
	हाल ATH10K_HW_TXRX_RAW:
	हाल ATH10K_HW_TXRX_NATIVE_WIFI:
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT;
		fallthrough;
	हाल ATH10K_HW_TXRX_ETHERNET:
		flags0 |= SM(txmode, HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE);
		अवरोध;
	हाल ATH10K_HW_TXRX_MGMT:
		flags0 |= SM(ATH10K_HW_TXRX_MGMT,
			     HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE);
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT;

		अगर (htt->disable_tx_comp)
			flags1 |= HTT_DATA_TX_DESC_FLAGS1_TX_COMPLETE;
		अवरोध;
	पूर्ण

	अगर (skb_cb->flags & ATH10K_SKB_F_NO_HWCRYPT)
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_NO_ENCRYPT;

	flags1 |= SM((u16)vdev_id, HTT_DATA_TX_DESC_FLAGS1_VDEV_ID);
	flags1 |= SM((u16)tid, HTT_DATA_TX_DESC_FLAGS1_EXT_TID);
	अगर (msdu->ip_summed == CHECKSUM_PARTIAL &&
	    !test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags)) अणु
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_CKSUM_L3_OFFLOAD;
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_CKSUM_L4_OFFLOAD;
	पूर्ण

	/* Prepend the HTT header and TX desc काष्ठा to the data message
	 * and पुनः_स्मृति the skb अगर it करोes not have enough headroom.
	 */
	अगर (skb_headroom(msdu) < HTT_TX_HL_NEEDED_HEADROOM) अणु
		पंचांगp_skb = msdu;

		ath10k_dbg(htt->ar, ATH10K_DBG_HTT,
			   "Not enough headroom in skb. Current headroom: %u, needed: %u. Reallocating...\n",
			   skb_headroom(msdu), HTT_TX_HL_NEEDED_HEADROOM);
		msdu = skb_पुनः_स्मृति_headroom(msdu, HTT_TX_HL_NEEDED_HEADROOM);
		kमुक्त_skb(पंचांगp_skb);
		अगर (!msdu) अणु
			ath10k_warn(htt->ar, "htt hl tx: Unable to realloc skb!\n");
			res = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (ar->bus_param.hl_msdu_ids) अणु
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_POSTPONED;
		res = ath10k_htt_tx_alloc_msdu_id(htt, msdu);
		अगर (res < 0) अणु
			ath10k_err(ar, "msdu_id allocation failed %d\n", res);
			जाओ out;
		पूर्ण
		msdu_id = res;
	पूर्ण

	/* As msdu is मुक्तd by mac80211 (in ieee80211_tx_status()) and by
	 * ath10k (in ath10k_htt_htc_tx_complete()) we have to increase
	 * reference by one to aव्योम a use-after-मुक्त हाल and a द्विगुन
	 * मुक्त.
	 */
	skb_get(msdu);

	skb_push(msdu, माप(*cmd_hdr));
	skb_push(msdu, माप(*tx_desc));
	cmd_hdr = (काष्ठा htt_cmd_hdr *)msdu->data;
	tx_desc = (काष्ठा htt_data_tx_desc *)(msdu->data + माप(*cmd_hdr));

	cmd_hdr->msg_type = HTT_H2T_MSG_TYPE_TX_FRM;
	tx_desc->flags0 = flags0;
	tx_desc->flags1 = __cpu_to_le16(flags1);
	tx_desc->len = __cpu_to_le16(data_len);
	tx_desc->id = __cpu_to_le16(msdu_id);
	tx_desc->frags_paddr = 0; /* always zero */
	/* Initialize peer_id to INVALID_PEER because this is NOT
	 * Reinjection path
	 */
	tx_desc->peerid = __cpu_to_le32(HTT_INVALID_PEERID);

	res = ath10k_htc_send_hl(&htt->ar->htc, htt->eid, msdu);

out:
	वापस res;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_32(काष्ठा ath10k_htt *htt,
			    क्रमागत ath10k_hw_txrx_mode txmode,
			    काष्ठा sk_buff *msdu)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा device *dev = ar->dev;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(msdu);
	काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	काष्ठा ath10k_hअगर_sg_item sg_items[2];
	काष्ठा ath10k_htt_txbuf_32 *txbuf;
	काष्ठा htt_data_tx_desc_frag *frags;
	bool is_eth = (txmode == ATH10K_HW_TXRX_ETHERNET);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(ar, msdu);
	u8 tid = ath10k_htt_tx_get_tid(msdu, is_eth);
	पूर्णांक prefetch_len;
	पूर्णांक res;
	u8 flags0 = 0;
	u16 msdu_id, flags1 = 0;
	u16 freq = 0;
	u32 frags_paddr = 0;
	u32 txbuf_paddr;
	काष्ठा htt_msdu_ext_desc *ext_desc = शून्य;
	काष्ठा htt_msdu_ext_desc *ext_desc_t = शून्य;

	res = ath10k_htt_tx_alloc_msdu_id(htt, msdu);
	अगर (res < 0)
		जाओ err;

	msdu_id = res;

	prefetch_len = min(htt->prefetch_len, msdu->len);
	prefetch_len = roundup(prefetch_len, 4);

	txbuf = htt->txbuf.vaddr_txbuff_32 + msdu_id;
	txbuf_paddr = htt->txbuf.paddr +
		      (माप(काष्ठा ath10k_htt_txbuf_32) * msdu_id);

	अगर ((ieee80211_is_action(hdr->frame_control) ||
	     ieee80211_is_deauth(hdr->frame_control) ||
	     ieee80211_is_disassoc(hdr->frame_control)) &&
	     ieee80211_has_रक्षित(hdr->frame_control)) अणु
		skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
	पूर्ण अन्यथा अगर (!(skb_cb->flags & ATH10K_SKB_F_NO_HWCRYPT) &&
		   txmode == ATH10K_HW_TXRX_RAW &&
		   ieee80211_has_रक्षित(hdr->frame_control)) अणु
		skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
	पूर्ण

	skb_cb->paddr = dma_map_single(dev, msdu->data, msdu->len,
				       DMA_TO_DEVICE);
	res = dma_mapping_error(dev, skb_cb->paddr);
	अगर (res) अणु
		res = -EIO;
		जाओ err_मुक्त_msdu_id;
	पूर्ण

	अगर (unlikely(info->flags & IEEE80211_TX_CTL_TX_OFFCHAN))
		freq = ar->scan.roc_freq;

	चयन (txmode) अणु
	हाल ATH10K_HW_TXRX_RAW:
	हाल ATH10K_HW_TXRX_NATIVE_WIFI:
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT;
		fallthrough;
	हाल ATH10K_HW_TXRX_ETHERNET:
		अगर (ar->hw_params.continuous_frag_desc) अणु
			ext_desc_t = htt->frag_desc.vaddr_desc_32;
			स_रखो(&ext_desc_t[msdu_id], 0,
			       माप(काष्ठा htt_msdu_ext_desc));
			frags = (काष्ठा htt_data_tx_desc_frag *)
				&ext_desc_t[msdu_id].frags;
			ext_desc = &ext_desc_t[msdu_id];
			frags[0].tword_addr.paddr_lo =
				__cpu_to_le32(skb_cb->paddr);
			frags[0].tword_addr.paddr_hi = 0;
			frags[0].tword_addr.len_16 = __cpu_to_le16(msdu->len);

			frags_paddr =  htt->frag_desc.paddr +
				(माप(काष्ठा htt_msdu_ext_desc) * msdu_id);
		पूर्ण अन्यथा अणु
			frags = txbuf->frags;
			frags[0].dword_addr.paddr =
				__cpu_to_le32(skb_cb->paddr);
			frags[0].dword_addr.len = __cpu_to_le32(msdu->len);
			frags[1].dword_addr.paddr = 0;
			frags[1].dword_addr.len = 0;

			frags_paddr = txbuf_paddr;
		पूर्ण
		flags0 |= SM(txmode, HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE);
		अवरोध;
	हाल ATH10K_HW_TXRX_MGMT:
		flags0 |= SM(ATH10K_HW_TXRX_MGMT,
			     HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE);
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT;

		frags_paddr = skb_cb->paddr;
		अवरोध;
	पूर्ण

	/* Normally all commands go through HTC which manages tx credits क्रम
	 * each endpoपूर्णांक and notअगरies when tx is completed.
	 *
	 * HTT endpoपूर्णांक is creditless so there's no need to care about HTC
	 * flags. In that हाल it is trivial to fill the HTC header here.
	 *
	 * MSDU transmission is considered completed upon HTT event. This
	 * implies no relevant resources can be मुक्तd until after the event is
	 * received. That's why HTC tx completion handler itself is ignored by
	 * setting शून्य to transfer_context क्रम all sg items.
	 *
	 * There is simply no poपूर्णांक in pushing HTT TX_FRM through HTC tx path
	 * as it's a waste of resources. By bypassing HTC it is possible to
	 * aव्योम extra memory allocations, compress data काष्ठाures and thus
	 * improve perक्रमmance.
	 */

	txbuf->htc_hdr.eid = htt->eid;
	txbuf->htc_hdr.len = __cpu_to_le16(माप(txbuf->cmd_hdr) +
					   माप(txbuf->cmd_tx) +
					   prefetch_len);
	txbuf->htc_hdr.flags = 0;

	अगर (skb_cb->flags & ATH10K_SKB_F_NO_HWCRYPT)
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_NO_ENCRYPT;

	flags1 |= SM((u16)vdev_id, HTT_DATA_TX_DESC_FLAGS1_VDEV_ID);
	flags1 |= SM((u16)tid, HTT_DATA_TX_DESC_FLAGS1_EXT_TID);
	अगर (msdu->ip_summed == CHECKSUM_PARTIAL &&
	    !test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags)) अणु
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_CKSUM_L3_OFFLOAD;
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_CKSUM_L4_OFFLOAD;
		अगर (ar->hw_params.continuous_frag_desc)
			ext_desc->flags |= HTT_MSDU_CHECKSUM_ENABLE;
	पूर्ण

	/* Prevent firmware from sending up tx inspection requests. There's
	 * nothing ath10k can करो with frames requested क्रम inspection so क्रमce
	 * it to simply rely a regular tx completion with discard status.
	 */
	flags1 |= HTT_DATA_TX_DESC_FLAGS1_POSTPONED;

	txbuf->cmd_hdr.msg_type = HTT_H2T_MSG_TYPE_TX_FRM;
	txbuf->cmd_tx.flags0 = flags0;
	txbuf->cmd_tx.flags1 = __cpu_to_le16(flags1);
	txbuf->cmd_tx.len = __cpu_to_le16(msdu->len);
	txbuf->cmd_tx.id = __cpu_to_le16(msdu_id);
	txbuf->cmd_tx.frags_paddr = __cpu_to_le32(frags_paddr);
	अगर (ath10k_mac_tx_frm_has_freq(ar)) अणु
		txbuf->cmd_tx.offchan_tx.peerid =
				__cpu_to_le16(HTT_INVALID_PEERID);
		txbuf->cmd_tx.offchan_tx.freq =
				__cpu_to_le16(freq);
	पूर्ण अन्यथा अणु
		txbuf->cmd_tx.peerid =
				__cpu_to_le32(HTT_INVALID_PEERID);
	पूर्ण

	trace_ath10k_htt_tx(ar, msdu_id, msdu->len, vdev_id, tid);
	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt tx flags0 %u flags1 %u len %d id %u frags_paddr %pad, msdu_paddr %pad vdev %u tid %u freq %u\n",
		   flags0, flags1, msdu->len, msdu_id, &frags_paddr,
		   &skb_cb->paddr, vdev_id, tid, freq);
	ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य, "htt tx msdu: ",
			msdu->data, msdu->len);
	trace_ath10k_tx_hdr(ar, msdu->data, msdu->len);
	trace_ath10k_tx_payload(ar, msdu->data, msdu->len);

	sg_items[0].transfer_id = 0;
	sg_items[0].transfer_context = शून्य;
	sg_items[0].vaddr = &txbuf->htc_hdr;
	sg_items[0].paddr = txbuf_paddr +
			    माप(txbuf->frags);
	sg_items[0].len = माप(txbuf->htc_hdr) +
			  माप(txbuf->cmd_hdr) +
			  माप(txbuf->cmd_tx);

	sg_items[1].transfer_id = 0;
	sg_items[1].transfer_context = शून्य;
	sg_items[1].vaddr = msdu->data;
	sg_items[1].paddr = skb_cb->paddr;
	sg_items[1].len = prefetch_len;

	res = ath10k_hअगर_tx_sg(htt->ar,
			       htt->ar->htc.endpoपूर्णांक[htt->eid].ul_pipe_id,
			       sg_items, ARRAY_SIZE(sg_items));
	अगर (res)
		जाओ err_unmap_msdu;

	वापस 0;

err_unmap_msdu:
	dma_unmap_single(dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);
err_मुक्त_msdu_id:
	spin_lock_bh(&htt->tx_lock);
	ath10k_htt_tx_मुक्त_msdu_id(htt, msdu_id);
	spin_unlock_bh(&htt->tx_lock);
err:
	वापस res;
पूर्ण

अटल पूर्णांक ath10k_htt_tx_64(काष्ठा ath10k_htt *htt,
			    क्रमागत ath10k_hw_txrx_mode txmode,
			    काष्ठा sk_buff *msdu)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा device *dev = ar->dev;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(msdu);
	काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(msdu);
	काष्ठा ath10k_hअगर_sg_item sg_items[2];
	काष्ठा ath10k_htt_txbuf_64 *txbuf;
	काष्ठा htt_data_tx_desc_frag *frags;
	bool is_eth = (txmode == ATH10K_HW_TXRX_ETHERNET);
	u8 vdev_id = ath10k_htt_tx_get_vdev_id(ar, msdu);
	u8 tid = ath10k_htt_tx_get_tid(msdu, is_eth);
	पूर्णांक prefetch_len;
	पूर्णांक res;
	u8 flags0 = 0;
	u16 msdu_id, flags1 = 0;
	u16 freq = 0;
	dma_addr_t frags_paddr = 0;
	dma_addr_t txbuf_paddr;
	काष्ठा htt_msdu_ext_desc_64 *ext_desc = शून्य;
	काष्ठा htt_msdu_ext_desc_64 *ext_desc_t = शून्य;

	res = ath10k_htt_tx_alloc_msdu_id(htt, msdu);
	अगर (res < 0)
		जाओ err;

	msdu_id = res;

	prefetch_len = min(htt->prefetch_len, msdu->len);
	prefetch_len = roundup(prefetch_len, 4);

	txbuf = htt->txbuf.vaddr_txbuff_64 + msdu_id;
	txbuf_paddr = htt->txbuf.paddr +
		      (माप(काष्ठा ath10k_htt_txbuf_64) * msdu_id);

	अगर ((ieee80211_is_action(hdr->frame_control) ||
	     ieee80211_is_deauth(hdr->frame_control) ||
	     ieee80211_is_disassoc(hdr->frame_control)) &&
	     ieee80211_has_रक्षित(hdr->frame_control)) अणु
		skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
	पूर्ण अन्यथा अगर (!(skb_cb->flags & ATH10K_SKB_F_NO_HWCRYPT) &&
		   txmode == ATH10K_HW_TXRX_RAW &&
		   ieee80211_has_रक्षित(hdr->frame_control)) अणु
		skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
	पूर्ण

	skb_cb->paddr = dma_map_single(dev, msdu->data, msdu->len,
				       DMA_TO_DEVICE);
	res = dma_mapping_error(dev, skb_cb->paddr);
	अगर (res) अणु
		res = -EIO;
		जाओ err_मुक्त_msdu_id;
	पूर्ण

	अगर (unlikely(info->flags & IEEE80211_TX_CTL_TX_OFFCHAN))
		freq = ar->scan.roc_freq;

	चयन (txmode) अणु
	हाल ATH10K_HW_TXRX_RAW:
	हाल ATH10K_HW_TXRX_NATIVE_WIFI:
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT;
		fallthrough;
	हाल ATH10K_HW_TXRX_ETHERNET:
		अगर (ar->hw_params.continuous_frag_desc) अणु
			ext_desc_t = htt->frag_desc.vaddr_desc_64;
			स_रखो(&ext_desc_t[msdu_id], 0,
			       माप(काष्ठा htt_msdu_ext_desc_64));
			frags = (काष्ठा htt_data_tx_desc_frag *)
				&ext_desc_t[msdu_id].frags;
			ext_desc = &ext_desc_t[msdu_id];
			frags[0].tword_addr.paddr_lo =
				__cpu_to_le32(skb_cb->paddr);
			frags[0].tword_addr.paddr_hi =
				__cpu_to_le16(upper_32_bits(skb_cb->paddr));
			frags[0].tword_addr.len_16 = __cpu_to_le16(msdu->len);

			frags_paddr =  htt->frag_desc.paddr +
			   (माप(काष्ठा htt_msdu_ext_desc_64) * msdu_id);
		पूर्ण अन्यथा अणु
			frags = txbuf->frags;
			frags[0].tword_addr.paddr_lo =
						__cpu_to_le32(skb_cb->paddr);
			frags[0].tword_addr.paddr_hi =
				__cpu_to_le16(upper_32_bits(skb_cb->paddr));
			frags[0].tword_addr.len_16 = __cpu_to_le16(msdu->len);
			frags[1].tword_addr.paddr_lo = 0;
			frags[1].tword_addr.paddr_hi = 0;
			frags[1].tword_addr.len_16 = 0;
		पूर्ण
		flags0 |= SM(txmode, HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE);
		अवरोध;
	हाल ATH10K_HW_TXRX_MGMT:
		flags0 |= SM(ATH10K_HW_TXRX_MGMT,
			     HTT_DATA_TX_DESC_FLAGS0_PKT_TYPE);
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_MAC_HDR_PRESENT;

		frags_paddr = skb_cb->paddr;
		अवरोध;
	पूर्ण

	/* Normally all commands go through HTC which manages tx credits क्रम
	 * each endpoपूर्णांक and notअगरies when tx is completed.
	 *
	 * HTT endpoपूर्णांक is creditless so there's no need to care about HTC
	 * flags. In that हाल it is trivial to fill the HTC header here.
	 *
	 * MSDU transmission is considered completed upon HTT event. This
	 * implies no relevant resources can be मुक्तd until after the event is
	 * received. That's why HTC tx completion handler itself is ignored by
	 * setting शून्य to transfer_context क्रम all sg items.
	 *
	 * There is simply no poपूर्णांक in pushing HTT TX_FRM through HTC tx path
	 * as it's a waste of resources. By bypassing HTC it is possible to
	 * aव्योम extra memory allocations, compress data काष्ठाures and thus
	 * improve perक्रमmance.
	 */

	txbuf->htc_hdr.eid = htt->eid;
	txbuf->htc_hdr.len = __cpu_to_le16(माप(txbuf->cmd_hdr) +
					   माप(txbuf->cmd_tx) +
					   prefetch_len);
	txbuf->htc_hdr.flags = 0;

	अगर (skb_cb->flags & ATH10K_SKB_F_NO_HWCRYPT)
		flags0 |= HTT_DATA_TX_DESC_FLAGS0_NO_ENCRYPT;

	flags1 |= SM((u16)vdev_id, HTT_DATA_TX_DESC_FLAGS1_VDEV_ID);
	flags1 |= SM((u16)tid, HTT_DATA_TX_DESC_FLAGS1_EXT_TID);
	अगर (msdu->ip_summed == CHECKSUM_PARTIAL &&
	    !test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags)) अणु
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_CKSUM_L3_OFFLOAD;
		flags1 |= HTT_DATA_TX_DESC_FLAGS1_CKSUM_L4_OFFLOAD;
		अगर (ar->hw_params.continuous_frag_desc) अणु
			स_रखो(ext_desc->tso_flag, 0, माप(ext_desc->tso_flag));
			ext_desc->tso_flag[3] |=
				__cpu_to_le32(HTT_MSDU_CHECKSUM_ENABLE_64);
		पूर्ण
	पूर्ण

	/* Prevent firmware from sending up tx inspection requests. There's
	 * nothing ath10k can करो with frames requested क्रम inspection so क्रमce
	 * it to simply rely a regular tx completion with discard status.
	 */
	flags1 |= HTT_DATA_TX_DESC_FLAGS1_POSTPONED;

	txbuf->cmd_hdr.msg_type = HTT_H2T_MSG_TYPE_TX_FRM;
	txbuf->cmd_tx.flags0 = flags0;
	txbuf->cmd_tx.flags1 = __cpu_to_le16(flags1);
	txbuf->cmd_tx.len = __cpu_to_le16(msdu->len);
	txbuf->cmd_tx.id = __cpu_to_le16(msdu_id);

	/* fill fragment descriptor */
	txbuf->cmd_tx.frags_paddr = __cpu_to_le64(frags_paddr);
	अगर (ath10k_mac_tx_frm_has_freq(ar)) अणु
		txbuf->cmd_tx.offchan_tx.peerid =
				__cpu_to_le16(HTT_INVALID_PEERID);
		txbuf->cmd_tx.offchan_tx.freq =
				__cpu_to_le16(freq);
	पूर्ण अन्यथा अणु
		txbuf->cmd_tx.peerid =
				__cpu_to_le32(HTT_INVALID_PEERID);
	पूर्ण

	trace_ath10k_htt_tx(ar, msdu_id, msdu->len, vdev_id, tid);
	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt tx flags0 %u flags1 %u len %d id %u frags_paddr %pad, msdu_paddr %pad vdev %u tid %u freq %u\n",
		   flags0, flags1, msdu->len, msdu_id, &frags_paddr,
		   &skb_cb->paddr, vdev_id, tid, freq);
	ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, शून्य, "htt tx msdu: ",
			msdu->data, msdu->len);
	trace_ath10k_tx_hdr(ar, msdu->data, msdu->len);
	trace_ath10k_tx_payload(ar, msdu->data, msdu->len);

	sg_items[0].transfer_id = 0;
	sg_items[0].transfer_context = शून्य;
	sg_items[0].vaddr = &txbuf->htc_hdr;
	sg_items[0].paddr = txbuf_paddr +
			    माप(txbuf->frags);
	sg_items[0].len = माप(txbuf->htc_hdr) +
			  माप(txbuf->cmd_hdr) +
			  माप(txbuf->cmd_tx);

	sg_items[1].transfer_id = 0;
	sg_items[1].transfer_context = शून्य;
	sg_items[1].vaddr = msdu->data;
	sg_items[1].paddr = skb_cb->paddr;
	sg_items[1].len = prefetch_len;

	res = ath10k_hअगर_tx_sg(htt->ar,
			       htt->ar->htc.endpoपूर्णांक[htt->eid].ul_pipe_id,
			       sg_items, ARRAY_SIZE(sg_items));
	अगर (res)
		जाओ err_unmap_msdu;

	वापस 0;

err_unmap_msdu:
	dma_unmap_single(dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);
err_मुक्त_msdu_id:
	spin_lock_bh(&htt->tx_lock);
	ath10k_htt_tx_मुक्त_msdu_id(htt, msdu_id);
	spin_unlock_bh(&htt->tx_lock);
err:
	वापस res;
पूर्ण

अटल स्थिर काष्ठा ath10k_htt_tx_ops htt_tx_ops_32 = अणु
	.htt_send_rx_ring_cfg = ath10k_htt_send_rx_ring_cfg_32,
	.htt_send_frag_desc_bank_cfg = ath10k_htt_send_frag_desc_bank_cfg_32,
	.htt_alloc_frag_desc = ath10k_htt_tx_alloc_cont_frag_desc_32,
	.htt_मुक्त_frag_desc = ath10k_htt_tx_मुक्त_cont_frag_desc_32,
	.htt_tx = ath10k_htt_tx_32,
	.htt_alloc_txbuff = ath10k_htt_tx_alloc_cont_txbuf_32,
	.htt_मुक्त_txbuff = ath10k_htt_tx_मुक्त_cont_txbuf_32,
	.htt_h2t_aggr_cfg_msg = ath10k_htt_h2t_aggr_cfg_msg_32,
पूर्ण;

अटल स्थिर काष्ठा ath10k_htt_tx_ops htt_tx_ops_64 = अणु
	.htt_send_rx_ring_cfg = ath10k_htt_send_rx_ring_cfg_64,
	.htt_send_frag_desc_bank_cfg = ath10k_htt_send_frag_desc_bank_cfg_64,
	.htt_alloc_frag_desc = ath10k_htt_tx_alloc_cont_frag_desc_64,
	.htt_मुक्त_frag_desc = ath10k_htt_tx_मुक्त_cont_frag_desc_64,
	.htt_tx = ath10k_htt_tx_64,
	.htt_alloc_txbuff = ath10k_htt_tx_alloc_cont_txbuf_64,
	.htt_मुक्त_txbuff = ath10k_htt_tx_मुक्त_cont_txbuf_64,
	.htt_h2t_aggr_cfg_msg = ath10k_htt_h2t_aggr_cfg_msg_v2,
पूर्ण;

अटल स्थिर काष्ठा ath10k_htt_tx_ops htt_tx_ops_hl = अणु
	.htt_send_rx_ring_cfg = ath10k_htt_send_rx_ring_cfg_hl,
	.htt_send_frag_desc_bank_cfg = ath10k_htt_send_frag_desc_bank_cfg_32,
	.htt_tx = ath10k_htt_tx_hl,
	.htt_h2t_aggr_cfg_msg = ath10k_htt_h2t_aggr_cfg_msg_32,
	.htt_flush_tx = ath10k_htt_flush_tx_queue,
पूर्ण;

व्योम ath10k_htt_set_tx_ops(काष्ठा ath10k_htt *htt)
अणु
	काष्ठा ath10k *ar = htt->ar;

	अगर (ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL)
		htt->tx_ops = &htt_tx_ops_hl;
	अन्यथा अगर (ar->hw_params.target_64bit)
		htt->tx_ops = &htt_tx_ops_64;
	अन्यथा
		htt->tx_ops = &htt_tx_ops_32;
पूर्ण
