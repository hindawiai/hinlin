<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2016 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश "core.h"
#समावेश "txrx.h"
#समावेश "htt.h"
#समावेश "mac.h"
#समावेश "debug.h"

अटल व्योम ath10k_report_offchan_tx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	अगर (likely(!(info->flags & IEEE80211_TX_CTL_TX_OFFCHAN)))
		वापस;

	अगर (ath10k_mac_tx_frm_has_freq(ar))
		वापस;

	/* If the original रुको_क्रम_completion() समयd out beक्रमe
	 * अणुdata,mgmtपूर्ण_tx_completed() was called then we could complete
	 * offchan_tx_completed क्रम a dअगरferent skb. Prevent this by using
	 * offchan_tx_skb.
	 */
	spin_lock_bh(&ar->data_lock);
	अगर (ar->offchan_tx_skb != skb) अणु
		ath10k_warn(ar, "completed old offchannel frame\n");
		जाओ out;
	पूर्ण

	complete(&ar->offchan_tx_completed);
	ar->offchan_tx_skb = शून्य; /* just क्रम sanity */

	ath10k_dbg(ar, ATH10K_DBG_HTT, "completed offchannel skb %pK\n", skb);
out:
	spin_unlock_bh(&ar->data_lock);
पूर्ण

पूर्णांक ath10k_txrx_tx_unref(काष्ठा ath10k_htt *htt,
			 स्थिर काष्ठा htt_tx_करोne *tx_करोne)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा device *dev = ar->dev;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_txq *txq;
	काष्ठा ath10k_skb_cb *skb_cb;
	काष्ठा ath10k_txq *artxq;
	काष्ठा sk_buff *msdu;
	u8 flags;

	ath10k_dbg(ar, ATH10K_DBG_HTT,
		   "htt tx completion msdu_id %u status %d\n",
		   tx_करोne->msdu_id, tx_करोne->status);

	अगर (tx_करोne->msdu_id >= htt->max_num_pending_tx) अणु
		ath10k_warn(ar, "warning: msdu_id %d too big, ignoring\n",
			    tx_करोne->msdu_id);
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&htt->tx_lock);
	msdu = idr_find(&htt->pending_tx, tx_करोne->msdu_id);
	अगर (!msdu) अणु
		ath10k_warn(ar, "received tx completion for invalid msdu_id: %d\n",
			    tx_करोne->msdu_id);
		spin_unlock_bh(&htt->tx_lock);
		वापस -ENOENT;
	पूर्ण

	skb_cb = ATH10K_SKB_CB(msdu);
	txq = skb_cb->txq;

	अगर (txq) अणु
		artxq = (व्योम *)txq->drv_priv;
		artxq->num_fw_queued--;
	पूर्ण

	flags = skb_cb->flags;
	ath10k_htt_tx_मुक्त_msdu_id(htt, tx_करोne->msdu_id);
	ath10k_htt_tx_dec_pending(htt);
	अगर (htt->num_pending_tx == 0)
		wake_up(&htt->empty_tx_wq);
	spin_unlock_bh(&htt->tx_lock);

	rcu_पढ़ो_lock();
	अगर (txq && txq->sta && skb_cb->airसमय_est)
		ieee80211_sta_रेजिस्टर_airसमय(txq->sta, txq->tid,
					       skb_cb->airसमय_est, 0);
	rcu_पढ़ो_unlock();

	अगर (ar->bus_param.dev_type != ATH10K_DEV_TYPE_HL)
		dma_unmap_single(dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);

	ath10k_report_offchan_tx(htt->ar, msdu);

	info = IEEE80211_SKB_CB(msdu);
	स_रखो(&info->status, 0, माप(info->status));
	info->status.rates[0].idx = -1;

	trace_ath10k_txrx_tx_unref(ar, tx_करोne->msdu_id);

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK) &&
	    !(flags & ATH10K_SKB_F_NOACK_TID))
		info->flags |= IEEE80211_TX_STAT_ACK;

	अगर (tx_करोne->status == HTT_TX_COMPL_STATE_NOACK)
		info->flags &= ~IEEE80211_TX_STAT_ACK;

	अगर ((tx_करोne->status == HTT_TX_COMPL_STATE_ACK) &&
	    ((info->flags & IEEE80211_TX_CTL_NO_ACK) ||
	    (flags & ATH10K_SKB_F_NOACK_TID)))
		info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;

	अगर (tx_करोne->status == HTT_TX_COMPL_STATE_DISCARD) अणु
		अगर ((info->flags & IEEE80211_TX_CTL_NO_ACK) ||
		    (flags & ATH10K_SKB_F_NOACK_TID))
			info->flags &= ~IEEE80211_TX_STAT_NOACK_TRANSMITTED;
		अन्यथा
			info->flags &= ~IEEE80211_TX_STAT_ACK;
	पूर्ण

	अगर (tx_करोne->status == HTT_TX_COMPL_STATE_ACK &&
	    tx_करोne->ack_rssi != ATH10K_INVALID_RSSI) अणु
		info->status.ack_संकेत = ATH10K_DEFAULT_NOISE_FLOOR +
						tx_करोne->ack_rssi;
		info->status.is_valid_ack_संकेत = true;
	पूर्ण

	ieee80211_tx_status(htt->ar->hw, msdu);
	/* we करो not own the msdu anymore */

	वापस 0;
पूर्ण

काष्ठा ath10k_peer *ath10k_peer_find(काष्ठा ath10k *ar, पूर्णांक vdev_id,
				     स्थिर u8 *addr)
अणु
	काष्ठा ath10k_peer *peer;

	lockdep_निश्चित_held(&ar->data_lock);

	list_क्रम_each_entry(peer, &ar->peers, list) अणु
		अगर (peer->vdev_id != vdev_id)
			जारी;
		अगर (!ether_addr_equal(peer->addr, addr))
			जारी;

		वापस peer;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ath10k_peer *ath10k_peer_find_by_id(काष्ठा ath10k *ar, पूर्णांक peer_id)
अणु
	काष्ठा ath10k_peer *peer;

	अगर (peer_id >= BITS_PER_TYPE(peer->peer_ids))
		वापस शून्य;

	lockdep_निश्चित_held(&ar->data_lock);

	list_क्रम_each_entry(peer, &ar->peers, list)
		अगर (test_bit(peer_id, peer->peer_ids))
			वापस peer;

	वापस शून्य;
पूर्ण

अटल पूर्णांक ath10k_रुको_क्रम_peer_common(काष्ठा ath10k *ar, पूर्णांक vdev_id,
				       स्थिर u8 *addr, bool expect_mapped)
अणु
	दीर्घ समय_left;

	समय_left = रुको_event_समयout(ar->peer_mapping_wq, (अणु
			bool mapped;

			spin_lock_bh(&ar->data_lock);
			mapped = !!ath10k_peer_find(ar, vdev_id, addr);
			spin_unlock_bh(&ar->data_lock);

			(mapped == expect_mapped ||
			 test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags));
		पूर्ण), 3 * HZ);

	अगर (समय_left == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

पूर्णांक ath10k_रुको_क्रम_peer_created(काष्ठा ath10k *ar, पूर्णांक vdev_id, स्थिर u8 *addr)
अणु
	वापस ath10k_रुको_क्रम_peer_common(ar, vdev_id, addr, true);
पूर्ण

पूर्णांक ath10k_रुको_क्रम_peer_deleted(काष्ठा ath10k *ar, पूर्णांक vdev_id, स्थिर u8 *addr)
अणु
	वापस ath10k_रुको_क्रम_peer_common(ar, vdev_id, addr, false);
पूर्ण

व्योम ath10k_peer_map_event(काष्ठा ath10k_htt *htt,
			   काष्ठा htt_peer_map_event *ev)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा ath10k_peer *peer;

	अगर (ev->peer_id >= ATH10K_MAX_NUM_PEER_IDS) अणु
		ath10k_warn(ar,
			    "received htt peer map event with idx out of bounds: %u\n",
			    ev->peer_id);
		वापस;
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, ev->vdev_id, ev->addr);
	अगर (!peer) अणु
		peer = kzalloc(माप(*peer), GFP_ATOMIC);
		अगर (!peer)
			जाओ निकास;

		peer->vdev_id = ev->vdev_id;
		ether_addr_copy(peer->addr, ev->addr);
		list_add(&peer->list, &ar->peers);
		wake_up(&ar->peer_mapping_wq);
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt peer map vdev %d peer %pM id %d\n",
		   ev->vdev_id, ev->addr, ev->peer_id);

	WARN_ON(ar->peer_map[ev->peer_id] && (ar->peer_map[ev->peer_id] != peer));
	ar->peer_map[ev->peer_id] = peer;
	set_bit(ev->peer_id, peer->peer_ids);
निकास:
	spin_unlock_bh(&ar->data_lock);
पूर्ण

व्योम ath10k_peer_unmap_event(काष्ठा ath10k_htt *htt,
			     काष्ठा htt_peer_unmap_event *ev)
अणु
	काष्ठा ath10k *ar = htt->ar;
	काष्ठा ath10k_peer *peer;

	अगर (ev->peer_id >= ATH10K_MAX_NUM_PEER_IDS) अणु
		ath10k_warn(ar,
			    "received htt peer unmap event with idx out of bounds: %u\n",
			    ev->peer_id);
		वापस;
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find_by_id(ar, ev->peer_id);
	अगर (!peer) अणु
		ath10k_warn(ar, "peer-unmap-event: unknown peer id %d\n",
			    ev->peer_id);
		जाओ निकास;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt peer unmap vdev %d peer %pM id %d\n",
		   peer->vdev_id, peer->addr, ev->peer_id);

	ar->peer_map[ev->peer_id] = शून्य;
	clear_bit(ev->peer_id, peer->peer_ids);

	अगर (biपंचांगap_empty(peer->peer_ids, ATH10K_MAX_NUM_PEER_IDS)) अणु
		list_del(&peer->list);
		kमुक्त(peer);
		wake_up(&ar->peer_mapping_wq);
	पूर्ण

निकास:
	spin_unlock_bh(&ar->data_lock);
पूर्ण
