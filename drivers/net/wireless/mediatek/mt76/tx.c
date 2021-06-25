<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश "mt76.h"

अटल पूर्णांक
mt76_txq_get_qid(काष्ठा ieee80211_txq *txq)
अणु
	अगर (!txq->sta)
		वापस MT_TXQ_BE;

	वापस txq->ac;
पूर्ण

व्योम
mt76_tx_check_agg_ssn(काष्ठा ieee80211_sta *sta, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_txq *txq;
	काष्ठा mt76_txq *mtxq;
	u8 tid;

	अगर (!sta || !ieee80211_is_data_qos(hdr->frame_control) ||
	    !ieee80211_is_data_present(hdr->frame_control))
		वापस;

	tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
	txq = sta->txq[tid];
	mtxq = (काष्ठा mt76_txq *)txq->drv_priv;
	अगर (!mtxq->aggr)
		वापस;

	mtxq->agg_ssn = le16_to_cpu(hdr->seq_ctrl) + 0x10;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_check_agg_ssn);

व्योम
mt76_tx_status_lock(काष्ठा mt76_dev *dev, काष्ठा sk_buff_head *list)
		   __acquires(&dev->status_list.lock)
अणु
	__skb_queue_head_init(list);
	spin_lock_bh(&dev->status_list.lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_status_lock);

व्योम
mt76_tx_status_unlock(काष्ठा mt76_dev *dev, काष्ठा sk_buff_head *list)
		      __releases(&dev->status_list.lock)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा sk_buff *skb;

	spin_unlock_bh(&dev->status_list.lock);

	जबतक ((skb = __skb_dequeue(list)) != शून्य) अणु
		hw = mt76_tx_status_get_hw(dev, skb);
		ieee80211_tx_status(hw, skb);
	पूर्ण

पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_status_unlock);

अटल व्योम
__mt76_tx_status_skb_करोne(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb, u8 flags,
			  काष्ठा sk_buff_head *list)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा mt76_tx_cb *cb = mt76_tx_skb_cb(skb);
	u8 करोne = MT_TX_CB_DMA_DONE | MT_TX_CB_TXS_DONE;

	flags |= cb->flags;
	cb->flags = flags;

	अगर ((flags & करोne) != करोne)
		वापस;

	__skb_unlink(skb, &dev->status_list);

	/* Tx status can be unreliable. अगर it fails, mark the frame as ACKed */
	अगर (flags & MT_TX_CB_TXS_FAILED) अणु
		ieee80211_tx_info_clear_status(info);
		info->status.rates[0].idx = -1;
		info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण

	__skb_queue_tail(list, skb);
पूर्ण

व्योम
mt76_tx_status_skb_करोne(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
			काष्ठा sk_buff_head *list)
अणु
	__mt76_tx_status_skb_करोne(dev, skb, MT_TX_CB_TXS_DONE, list);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_status_skb_करोne);

पूर्णांक
mt76_tx_status_skb_add(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा mt76_tx_cb *cb = mt76_tx_skb_cb(skb);
	पूर्णांक pid;

	अगर (!wcid)
		वापस MT_PACKET_ID_NO_ACK;

	अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
		वापस MT_PACKET_ID_NO_ACK;

	अगर (!(info->flags & (IEEE80211_TX_CTL_REQ_TX_STATUS |
			     IEEE80211_TX_CTL_RATE_CTRL_PROBE)))
		वापस MT_PACKET_ID_NO_SKB;

	spin_lock_bh(&dev->status_list.lock);

	स_रखो(cb, 0, माप(*cb));
	wcid->packet_id = (wcid->packet_id + 1) & MT_PACKET_ID_MASK;
	अगर (wcid->packet_id == MT_PACKET_ID_NO_ACK ||
	    wcid->packet_id == MT_PACKET_ID_NO_SKB)
		wcid->packet_id = MT_PACKET_ID_FIRST;

	pid = wcid->packet_id;
	cb->wcid = wcid->idx;
	cb->pktid = pid;
	cb->jअगरfies = jअगरfies;

	__skb_queue_tail(&dev->status_list, skb);
	spin_unlock_bh(&dev->status_list.lock);

	वापस pid;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_status_skb_add);

काष्ठा sk_buff *
mt76_tx_status_skb_get(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid, पूर्णांक pktid,
		       काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;

	skb_queue_walk_safe(&dev->status_list, skb, पंचांगp) अणु
		काष्ठा mt76_tx_cb *cb = mt76_tx_skb_cb(skb);

		अगर (wcid && cb->wcid != wcid->idx)
			जारी;

		अगर (cb->pktid == pktid)
			वापस skb;

		अगर (pktid >= 0 && !समय_after(jअगरfies, cb->jअगरfies +
					      MT_TX_STATUS_SKB_TIMEOUT))
			जारी;

		__mt76_tx_status_skb_करोne(dev, skb, MT_TX_CB_TXS_FAILED |
						    MT_TX_CB_TXS_DONE, list);
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_status_skb_get);

व्योम
mt76_tx_status_check(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid, bool flush)
अणु
	काष्ठा sk_buff_head list;

	mt76_tx_status_lock(dev, &list);
	mt76_tx_status_skb_get(dev, wcid, flush ? -1 : 0, &list);
	mt76_tx_status_unlock(dev, &list);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_status_check);

अटल व्योम
mt76_tx_check_non_aql(काष्ठा mt76_dev *dev, u16 wcid_idx, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा mt76_wcid *wcid;
	पूर्णांक pending;

	अगर (info->tx_समय_est)
		वापस;

	अगर (wcid_idx >= ARRAY_SIZE(dev->wcid))
		वापस;

	rcu_पढ़ो_lock();

	wcid = rcu_dereference(dev->wcid[wcid_idx]);
	अगर (wcid) अणु
		pending = atomic_dec_वापस(&wcid->non_aql_packets);
		अगर (pending < 0)
			atomic_cmpxchg(&wcid->non_aql_packets, pending, 0);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

व्योम mt76_tx_complete_skb(काष्ठा mt76_dev *dev, u16 wcid_idx, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा sk_buff_head list;

	mt76_tx_check_non_aql(dev, wcid_idx, skb);

#अगर_घोषित CONFIG_NL80211_TESTMODE
	अगर (mt76_is_tesपंचांगode_skb(dev, skb, &hw)) अणु
		काष्ठा mt76_phy *phy = hw->priv;

		अगर (skb == phy->test.tx_skb)
			phy->test.tx_करोne++;
		अगर (phy->test.tx_queued == phy->test.tx_करोne)
			wake_up(&dev->tx_रुको);

		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (!skb->prev) अणु
		hw = mt76_tx_status_get_hw(dev, skb);
		ieee80211_मुक्त_txskb(hw, skb);
		वापस;
	पूर्ण

	mt76_tx_status_lock(dev, &list);
	__mt76_tx_status_skb_करोne(dev, skb, MT_TX_CB_DMA_DONE, &list);
	mt76_tx_status_unlock(dev, &list);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_complete_skb);

अटल पूर्णांक
__mt76_tx_queue_skb(काष्ठा mt76_phy *phy, पूर्णांक qid, काष्ठा sk_buff *skb,
		    काष्ठा mt76_wcid *wcid, काष्ठा ieee80211_sta *sta,
		    bool *stop)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा mt76_queue *q = phy->q_tx[qid];
	काष्ठा mt76_dev *dev = phy->dev;
	bool non_aql;
	पूर्णांक pending;
	पूर्णांक idx;

	non_aql = !info->tx_समय_est;
	idx = dev->queue_ops->tx_queue_skb(dev, q, skb, wcid, sta);
	अगर (idx < 0 || !sta || !non_aql)
		वापस idx;

	wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
	q->entry[idx].wcid = wcid->idx;
	pending = atomic_inc_वापस(&wcid->non_aql_packets);
	अगर (stop && pending >= MT_MAX_NON_AQL_PKT)
		*stop = true;

	वापस idx;
पूर्ण

व्योम
mt76_tx(काष्ठा mt76_phy *phy, काष्ठा ieee80211_sta *sta,
	काष्ठा mt76_wcid *wcid, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा mt76_queue *q;
	पूर्णांक qid = skb_get_queue_mapping(skb);
	bool ext_phy = phy != &dev->phy;

	अगर (mt76_tesपंचांगode_enabled(phy)) अणु
		ieee80211_मुक्त_txskb(phy->hw, skb);
		वापस;
	पूर्ण

	अगर (WARN_ON(qid >= MT_TXQ_PSD)) अणु
		qid = MT_TXQ_BE;
		skb_set_queue_mapping(skb, qid);
	पूर्ण

	अगर ((dev->drv->drv_flags & MT_DRV_HW_MGMT_TXQ) &&
	    !(info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP) &&
	    !ieee80211_is_data(hdr->frame_control) &&
	    !ieee80211_is_bufferable_mmpdu(hdr->frame_control)) अणु
		qid = MT_TXQ_PSD;
		skb_set_queue_mapping(skb, qid);
	पूर्ण

	अगर (!(wcid->tx_info & MT_WCID_TX_INFO_SET))
		ieee80211_get_tx_rates(info->control.vअगर, sta, skb,
				       info->control.rates, 1);

	अगर (ext_phy)
		info->hw_queue |= MT_TX_HW_QUEUE_EXT_PHY;

	q = phy->q_tx[qid];

	spin_lock_bh(&q->lock);
	__mt76_tx_queue_skb(phy, qid, skb, wcid, sta, शून्य);
	dev->queue_ops->kick(dev, q);
	spin_unlock_bh(&q->lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx);

अटल काष्ठा sk_buff *
mt76_txq_dequeue(काष्ठा mt76_phy *phy, काष्ठा mt76_txq *mtxq)
अणु
	काष्ठा ieee80211_txq *txq = mtxq_to_txq(mtxq);
	काष्ठा ieee80211_tx_info *info;
	bool ext_phy = phy != &phy->dev->phy;
	काष्ठा sk_buff *skb;

	skb = ieee80211_tx_dequeue(phy->hw, txq);
	अगर (!skb)
		वापस शून्य;

	info = IEEE80211_SKB_CB(skb);
	अगर (ext_phy)
		info->hw_queue |= MT_TX_HW_QUEUE_EXT_PHY;

	वापस skb;
पूर्ण

अटल व्योम
mt76_queue_ps_skb(काष्ठा mt76_phy *phy, काष्ठा ieee80211_sta *sta,
		  काष्ठा sk_buff *skb, bool last)
अणु
	काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	info->control.flags |= IEEE80211_TX_CTRL_PS_RESPONSE;
	अगर (last)
		info->flags |= IEEE80211_TX_STATUS_EOSP |
			       IEEE80211_TX_CTL_REQ_TX_STATUS;

	mt76_skb_set_moredata(skb, !last);
	__mt76_tx_queue_skb(phy, MT_TXQ_PSD, skb, wcid, sta, शून्य);
पूर्ण

व्योम
mt76_release_buffered_frames(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
			     u16 tids, पूर्णांक nframes,
			     क्रमागत ieee80211_frame_release_type reason,
			     bool more_data)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा sk_buff *last_skb = शून्य;
	काष्ठा mt76_queue *hwq = phy->q_tx[MT_TXQ_PSD];
	पूर्णांक i;

	spin_lock_bh(&hwq->lock);
	क्रम (i = 0; tids && nframes; i++, tids >>= 1) अणु
		काष्ठा ieee80211_txq *txq = sta->txq[i];
		काष्ठा mt76_txq *mtxq = (काष्ठा mt76_txq *)txq->drv_priv;
		काष्ठा sk_buff *skb;

		अगर (!(tids & 1))
			जारी;

		करो अणु
			skb = mt76_txq_dequeue(phy, mtxq);
			अगर (!skb)
				अवरोध;

			nframes--;
			अगर (last_skb)
				mt76_queue_ps_skb(phy, sta, last_skb, false);

			last_skb = skb;
		पूर्ण जबतक (nframes);
	पूर्ण

	अगर (last_skb) अणु
		mt76_queue_ps_skb(phy, sta, last_skb, true);
		dev->queue_ops->kick(dev, hwq);
	पूर्ण अन्यथा अणु
		ieee80211_sta_eosp(sta);
	पूर्ण

	spin_unlock_bh(&hwq->lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_release_buffered_frames);

अटल bool
mt76_txq_stopped(काष्ठा mt76_queue *q)
अणु
	वापस q->stopped || q->blocked ||
	       q->queued + MT_TXQ_FREE_THR >= q->ndesc;
पूर्ण

अटल पूर्णांक
mt76_txq_send_burst(काष्ठा mt76_phy *phy, काष्ठा mt76_queue *q,
		    काष्ठा mt76_txq *mtxq)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा ieee80211_txq *txq = mtxq_to_txq(mtxq);
	क्रमागत mt76_txq_id qid = mt76_txq_get_qid(txq);
	काष्ठा mt76_wcid *wcid = mtxq->wcid;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *skb;
	पूर्णांक n_frames = 1;
	bool stop = false;
	पूर्णांक idx;

	अगर (test_bit(MT_WCID_FLAG_PS, &wcid->flags))
		वापस 0;

	अगर (atomic_पढ़ो(&wcid->non_aql_packets) >= MT_MAX_NON_AQL_PKT)
		वापस 0;

	skb = mt76_txq_dequeue(phy, mtxq);
	अगर (!skb)
		वापस 0;

	info = IEEE80211_SKB_CB(skb);
	अगर (!(wcid->tx_info & MT_WCID_TX_INFO_SET))
		ieee80211_get_tx_rates(txq->vअगर, txq->sta, skb,
				       info->control.rates, 1);

	idx = __mt76_tx_queue_skb(phy, qid, skb, wcid, txq->sta, &stop);
	अगर (idx < 0)
		वापस idx;

	करो अणु
		अगर (test_bit(MT76_RESET, &phy->state))
			वापस -EBUSY;

		अगर (stop || mt76_txq_stopped(q))
			अवरोध;

		skb = mt76_txq_dequeue(phy, mtxq);
		अगर (!skb)
			अवरोध;

		info = IEEE80211_SKB_CB(skb);
		अगर (!(wcid->tx_info & MT_WCID_TX_INFO_SET))
			ieee80211_get_tx_rates(txq->vअगर, txq->sta, skb,
					       info->control.rates, 1);

		idx = __mt76_tx_queue_skb(phy, qid, skb, wcid, txq->sta, &stop);
		अगर (idx < 0)
			अवरोध;

		n_frames++;
	पूर्ण जबतक (1);

	dev->queue_ops->kick(dev, q);

	वापस n_frames;
पूर्ण

अटल पूर्णांक
mt76_txq_schedule_list(काष्ठा mt76_phy *phy, क्रमागत mt76_txq_id qid)
अणु
	काष्ठा mt76_queue *q = phy->q_tx[qid];
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा ieee80211_txq *txq;
	काष्ठा mt76_txq *mtxq;
	काष्ठा mt76_wcid *wcid;
	पूर्णांक ret = 0;

	जबतक (1) अणु
		पूर्णांक n_frames = 0;

		अगर (test_bit(MT76_RESET, &phy->state))
			वापस -EBUSY;

		अगर (dev->queue_ops->tx_cleanup &&
		    q->queued + 2 * MT_TXQ_FREE_THR >= q->ndesc) अणु
			dev->queue_ops->tx_cleanup(dev, q, false);
		पूर्ण

		txq = ieee80211_next_txq(phy->hw, qid);
		अगर (!txq)
			अवरोध;

		mtxq = (काष्ठा mt76_txq *)txq->drv_priv;
		wcid = mtxq->wcid;
		अगर (wcid && test_bit(MT_WCID_FLAG_PS, &wcid->flags))
			जारी;

		spin_lock_bh(&q->lock);

		अगर (mtxq->send_bar && mtxq->aggr) अणु
			काष्ठा ieee80211_txq *txq = mtxq_to_txq(mtxq);
			काष्ठा ieee80211_sta *sta = txq->sta;
			काष्ठा ieee80211_vअगर *vअगर = txq->vअगर;
			u16 agg_ssn = mtxq->agg_ssn;
			u8 tid = txq->tid;

			mtxq->send_bar = false;
			spin_unlock_bh(&q->lock);
			ieee80211_send_bar(vअगर, sta->addr, tid, agg_ssn);
			spin_lock_bh(&q->lock);
		पूर्ण

		अगर (!mt76_txq_stopped(q))
			n_frames = mt76_txq_send_burst(phy, q, mtxq);

		spin_unlock_bh(&q->lock);

		ieee80211_वापस_txq(phy->hw, txq, false);

		अगर (unlikely(n_frames < 0))
			वापस n_frames;

		ret += n_frames;
	पूर्ण

	वापस ret;
पूर्ण

व्योम mt76_txq_schedule(काष्ठा mt76_phy *phy, क्रमागत mt76_txq_id qid)
अणु
	पूर्णांक len;

	अगर (qid >= 4)
		वापस;

	rcu_पढ़ो_lock();

	करो अणु
		ieee80211_txq_schedule_start(phy->hw, qid);
		len = mt76_txq_schedule_list(phy, qid);
		ieee80211_txq_schedule_end(phy->hw, qid);
	पूर्ण जबतक (len > 0);

	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(mt76_txq_schedule);

व्योम mt76_txq_schedule_all(काष्ठा mt76_phy *phy)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= MT_TXQ_BK; i++)
		mt76_txq_schedule(phy, i);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_txq_schedule_all);

व्योम mt76_tx_worker_run(काष्ठा mt76_dev *dev)
अणु
	mt76_txq_schedule_all(&dev->phy);
	अगर (dev->phy2)
		mt76_txq_schedule_all(dev->phy2);

#अगर_घोषित CONFIG_NL80211_TESTMODE
	अगर (dev->phy.test.tx_pending)
		mt76_tesपंचांगode_tx_pending(&dev->phy);
	अगर (dev->phy2 && dev->phy2->test.tx_pending)
		mt76_tesपंचांगode_tx_pending(dev->phy2);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(mt76_tx_worker_run);

व्योम mt76_tx_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt76_dev *dev = container_of(w, काष्ठा mt76_dev, tx_worker);

	mt76_tx_worker_run(dev);
पूर्ण

व्योम mt76_stop_tx_queues(काष्ठा mt76_phy *phy, काष्ठा ieee80211_sta *sta,
			 bool send_bar)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sta->txq); i++) अणु
		काष्ठा ieee80211_txq *txq = sta->txq[i];
		काष्ठा mt76_queue *hwq;
		काष्ठा mt76_txq *mtxq;

		अगर (!txq)
			जारी;

		hwq = phy->q_tx[mt76_txq_get_qid(txq)];
		mtxq = (काष्ठा mt76_txq *)txq->drv_priv;

		spin_lock_bh(&hwq->lock);
		mtxq->send_bar = mtxq->aggr && send_bar;
		spin_unlock_bh(&hwq->lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76_stop_tx_queues);

व्योम mt76_wake_tx_queue(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा mt76_dev *dev = phy->dev;

	अगर (!test_bit(MT76_STATE_RUNNING, &phy->state))
		वापस;

	mt76_worker_schedule(&dev->tx_worker);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_wake_tx_queue);

u8 mt76_ac_to_hwq(u8 ac)
अणु
	अटल स्थिर u8 wmm_queue_map[] = अणु
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 2,
		[IEEE80211_AC_VO] = 3,
	पूर्ण;

	अगर (WARN_ON(ac >= IEEE80211_NUM_ACS))
		वापस 0;

	वापस wmm_queue_map[ac];
पूर्ण
EXPORT_SYMBOL_GPL(mt76_ac_to_hwq);

पूर्णांक mt76_skb_adjust_pad(काष्ठा sk_buff *skb, पूर्णांक pad)
अणु
	काष्ठा sk_buff *iter, *last = skb;

	/* First packet of a A-MSDU burst keeps track of the whole burst
	 * length, need to update length of it and the last packet.
	 */
	skb_walk_frags(skb, iter) अणु
		last = iter;
		अगर (!iter->next) अणु
			skb->data_len += pad;
			skb->len += pad;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (skb_pad(last, pad))
		वापस -ENOMEM;

	__skb_put(last, pad);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_skb_adjust_pad);

व्योम mt76_queue_tx_complete(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
			    काष्ठा mt76_queue_entry *e)
अणु
	अगर (e->skb)
		dev->drv->tx_complete_skb(dev, e);

	spin_lock_bh(&q->lock);
	q->tail = (q->tail + 1) % q->ndesc;
	q->queued--;
	spin_unlock_bh(&q->lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_queue_tx_complete);

व्योम __mt76_set_tx_blocked(काष्ठा mt76_dev *dev, bool blocked)
अणु
	काष्ठा mt76_phy *phy = &dev->phy, *phy2 = dev->phy2;
	काष्ठा mt76_queue *q, *q2 = शून्य;

	q = phy->q_tx[0];
	अगर (blocked == q->blocked)
		वापस;

	q->blocked = blocked;
	अगर (phy2) अणु
		q2 = phy2->q_tx[0];
		q2->blocked = blocked;
	पूर्ण

	अगर (!blocked)
		mt76_worker_schedule(&dev->tx_worker);
पूर्ण
EXPORT_SYMBOL_GPL(__mt76_set_tx_blocked);

पूर्णांक mt76_token_consume(काष्ठा mt76_dev *dev, काष्ठा mt76_txwi_cache **ptxwi)
अणु
	पूर्णांक token;

	spin_lock_bh(&dev->token_lock);

	token = idr_alloc(&dev->token, *ptxwi, 0, dev->drv->token_size,
			  GFP_ATOMIC);
	अगर (token >= 0)
		dev->token_count++;

	अगर (dev->token_count >= dev->drv->token_size - MT76_TOKEN_FREE_THR)
		__mt76_set_tx_blocked(dev, true);

	spin_unlock_bh(&dev->token_lock);

	वापस token;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_token_consume);

काष्ठा mt76_txwi_cache *
mt76_token_release(काष्ठा mt76_dev *dev, पूर्णांक token, bool *wake)
अणु
	काष्ठा mt76_txwi_cache *txwi;

	spin_lock_bh(&dev->token_lock);

	txwi = idr_हटाओ(&dev->token, token);
	अगर (txwi)
		dev->token_count--;

	अगर (dev->token_count < dev->drv->token_size - MT76_TOKEN_FREE_THR &&
	    dev->phy.q_tx[0]->blocked)
		*wake = true;

	spin_unlock_bh(&dev->token_lock);

	वापस txwi;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_token_release);
