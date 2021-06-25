<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश "mt7601u.h"
#समावेश "trace.h"

क्रमागत mt76_txq_id अणु
	MT_TXQ_VO = IEEE80211_AC_VO,
	MT_TXQ_VI = IEEE80211_AC_VI,
	MT_TXQ_BE = IEEE80211_AC_BE,
	MT_TXQ_BK = IEEE80211_AC_BK,
	MT_TXQ_PSD,
	MT_TXQ_MCU,
	__MT_TXQ_MAX
पूर्ण;

/* Hardware uses mirrored order of queues with Q0 having the highest priority */
अटल u8 q2hwq(u8 q)
अणु
	वापस q ^ 0x3;
पूर्ण

/* Take mac80211 Q id from the skb and translate it to hardware Q id */
अटल u8 skb2q(काष्ठा sk_buff *skb)
अणु
	पूर्णांक qid = skb_get_queue_mapping(skb);

	अगर (WARN_ON(qid >= MT_TXQ_PSD)) अणु
		qid = MT_TXQ_BE;
		skb_set_queue_mapping(skb, qid);
	पूर्ण

	वापस q2hwq(qid);
पूर्ण

/* Note: TX retry reporting is a bit broken.
 *	 Retries are reported only once per AMPDU and often come a frame early
 *	 i.e. they are reported in the last status preceding the AMPDU. Apart
 *	 from the fact that it's hard to know the length of the AMPDU (which is
 *	 required to know to how many consecutive frames retries should be
 *	 applied), अगर status comes early on full FIFO it माला_लो lost and retries
 *	 of the whole AMPDU become invisible.
 *	 As a work-around encode the desired rate in PKT_ID of TX descriptor
 *	 and based on that guess the retries (every rate is tried once).
 *	 Only करोwnside here is that क्रम MCS0 we have to rely solely on
 *	 transmission failures as no retries can ever be reported.
 *	 Not having to पढ़ो EXT_FIFO has a nice effect of करोubling the number
 *	 of reports which can be fetched.
 *	 Also the venकरोr driver never uses the EXT_FIFO रेजिस्टर so it may be
 *	 undertested.
 */
अटल u8 mt7601u_tx_pktid_enc(काष्ठा mt7601u_dev *dev, u8 rate, bool is_probe)
अणु
	u8 encoded = (rate + 1) + is_probe *  8;

	/* Because PKT_ID 0 disables status reporting only 15 values are
	 * available but 16 are needed (8 MCS * 2 क्रम encoding is_probe)
	 * - we need to cram together two rates. MCS0 and MCS7 with is_probe
	 * share PKT_ID 9.
	 */
	अगर (is_probe && rate == 7)
		वापस encoded - 7;

	वापस encoded;
पूर्ण

अटल व्योम
mt7601u_tx_pktid_dec(काष्ठा mt7601u_dev *dev, काष्ठा mt76_tx_status *stat)
अणु
	u8 req_rate = stat->pktid;
	u8 eff_rate = stat->rate & 0x7;

	req_rate -= 1;

	अगर (req_rate > 7) अणु
		stat->is_probe = true;
		req_rate -= 8;

		/* Decide between MCS0 and MCS7 which share pktid 9 */
		अगर (!req_rate && eff_rate)
			req_rate = 7;
	पूर्ण

	stat->retry = req_rate - eff_rate;
पूर्ण

अटल व्योम mt7601u_tx_skb_हटाओ_dma_overhead(काष्ठा sk_buff *skb,
					       काष्ठा ieee80211_tx_info *info)
अणु
	पूर्णांक pkt_len = (अचिन्हित दीर्घ)info->status.status_driver_data[0];

	skb_pull(skb, माप(काष्ठा mt76_txwi) + 4);
	अगर (ieee80211_get_hdrlen_from_skb(skb) % 4)
		mt76_हटाओ_hdr_pad(skb);

	skb_trim(skb, pkt_len);
पूर्ण

व्योम mt7601u_tx_status(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	mt7601u_tx_skb_हटाओ_dma_overhead(skb, info);

	ieee80211_tx_info_clear_status(info);
	info->status.rates[0].idx = -1;
	info->flags |= IEEE80211_TX_STAT_ACK;

	spin_lock_bh(&dev->mac_lock);
	ieee80211_tx_status(dev->hw, skb);
	spin_unlock_bh(&dev->mac_lock);
पूर्ण

अटल पूर्णांक mt7601u_skb_rooms(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	u32 need_head;

	need_head = माप(काष्ठा mt76_txwi) + 4;
	अगर (hdr_len % 4)
		need_head += 2;

	वापस skb_cow(skb, need_head);
पूर्ण

अटल काष्ठा mt76_txwi *
mt7601u_push_txwi(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb,
		  काष्ठा ieee80211_sta *sta, काष्ठा mt76_wcid *wcid,
		  पूर्णांक pkt_len)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *rate = &info->control.rates[0];
	काष्ठा mt76_txwi *txwi;
	अचिन्हित दीर्घ flags;
	bool is_probe;
	u32 pkt_id;
	u16 rate_ctl;
	u8 nss;

	txwi = skb_push(skb, माप(काष्ठा mt76_txwi));
	स_रखो(txwi, 0, माप(*txwi));

	अगर (!wcid->tx_rate_set)
		ieee80211_get_tx_rates(info->control.vअगर, sta, skb,
				       info->control.rates, 1);

	spin_lock_irqsave(&dev->lock, flags);
	अगर (rate->idx < 0 || !rate->count)
		rate_ctl = wcid->tx_rate;
	अन्यथा
		rate_ctl = mt76_mac_tx_rate_val(dev, rate, &nss);
	spin_unlock_irqrestore(&dev->lock, flags);
	txwi->rate_ctl = cpu_to_le16(rate_ctl);

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		txwi->ack_ctl |= MT_TXWI_ACK_CTL_REQ;
	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ)
		txwi->ack_ctl |= MT_TXWI_ACK_CTL_NSEQ;

	अगर ((info->flags & IEEE80211_TX_CTL_AMPDU) && sta) अणु
		u8 ba_size = IEEE80211_MIN_AMPDU_BUF;

		ba_size <<= sta->ht_cap.ampdu_factor;
		ba_size = min_t(पूर्णांक, 63, ba_size);
		अगर (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)
			ba_size = 0;
		txwi->ack_ctl |= FIELD_PREP(MT_TXWI_ACK_CTL_BA_WINDOW, ba_size);

		txwi->flags =
			cpu_to_le16(MT_TXWI_FLAGS_AMPDU |
				    FIELD_PREP(MT_TXWI_FLAGS_MPDU_DENSITY,
					       sta->ht_cap.ampdu_density));
		अगर (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)
			txwi->flags = 0;
	पूर्ण

	txwi->wcid = wcid->idx;

	is_probe = !!(info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE);
	pkt_id = mt7601u_tx_pktid_enc(dev, rate_ctl & 0x7, is_probe);
	pkt_len |= FIELD_PREP(MT_TXWI_LEN_PKTID, pkt_id);
	txwi->len_ctl = cpu_to_le16(pkt_len);

	वापस txwi;
पूर्ण

व्योम mt7601u_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_tx_control *control,
		काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा mt7601u_dev *dev = hw->priv;
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा ieee80211_sta *sta = control->sta;
	काष्ठा mt76_sta *msta = शून्य;
	काष्ठा mt76_wcid *wcid = dev->mon_wcid;
	काष्ठा mt76_txwi *txwi;
	पूर्णांक pkt_len = skb->len;
	पूर्णांक hw_q = skb2q(skb);

	BUILD_BUG_ON(ARRAY_SIZE(info->status.status_driver_data) < 1);
	info->status.status_driver_data[0] = (व्योम *)(अचिन्हित दीर्घ)pkt_len;

	अगर (mt7601u_skb_rooms(dev, skb) || mt76_insert_hdr_pad(skb)) अणु
		ieee80211_मुक्त_txskb(dev->hw, skb);
		वापस;
	पूर्ण

	अगर (sta) अणु
		msta = (काष्ठा mt76_sta *) sta->drv_priv;
		wcid = &msta->wcid;
	पूर्ण अन्यथा अगर (vअगर) अणु
		काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;

		wcid = &mvअगर->group_wcid;
	पूर्ण

	txwi = mt7601u_push_txwi(dev, skb, sta, wcid, pkt_len);

	अगर (mt7601u_dma_enqueue_tx(dev, skb, wcid, hw_q))
		वापस;

	trace_mt_tx(dev, skb, msta, txwi);
पूर्ण

व्योम mt7601u_tx_stat(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7601u_dev *dev = container_of(work, काष्ठा mt7601u_dev,
					       stat_work.work);
	काष्ठा mt76_tx_status stat;
	अचिन्हित दीर्घ flags;
	पूर्णांक cleaned = 0;

	जबतक (!test_bit(MT7601U_STATE_REMOVED, &dev->state)) अणु
		stat = mt7601u_mac_fetch_tx_status(dev);
		अगर (!stat.valid)
			अवरोध;

		mt7601u_tx_pktid_dec(dev, &stat);
		mt76_send_tx_status(dev, &stat);

		cleaned++;
	पूर्ण
	trace_mt_tx_status_cleaned(dev, cleaned);

	spin_lock_irqsave(&dev->tx_lock, flags);
	अगर (cleaned)
		queue_delayed_work(dev->stat_wq, &dev->stat_work,
				   msecs_to_jअगरfies(10));
	अन्यथा अगर (test_and_clear_bit(MT7601U_STATE_MORE_STATS, &dev->state))
		queue_delayed_work(dev->stat_wq, &dev->stat_work,
				   msecs_to_jअगरfies(20));
	अन्यथा
		clear_bit(MT7601U_STATE_READING_STATS, &dev->state);
	spin_unlock_irqrestore(&dev->tx_lock, flags);
पूर्ण

पूर्णांक mt7601u_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	u8 cw_min = 5, cw_max = 10, hw_q = q2hwq(queue);
	u32 val;

	/* TODO: should we करो funny things with the parameters?
	 *	 See what mt7601u_set_शेष_edca() used to करो in init.c.
	 */

	अगर (params->cw_min)
		cw_min = fls(params->cw_min);
	अगर (params->cw_max)
		cw_max = fls(params->cw_max);

	WARN_ON(params->txop > 0xff);
	WARN_ON(params->aअगरs > 0xf);
	WARN_ON(cw_min > 0xf);
	WARN_ON(cw_max > 0xf);

	val = FIELD_PREP(MT_EDCA_CFG_AIFSN, params->aअगरs) |
	      FIELD_PREP(MT_EDCA_CFG_CWMIN, cw_min) |
	      FIELD_PREP(MT_EDCA_CFG_CWMAX, cw_max);
	/* TODO: based on user-controlled EnableTxBurst var venकरोr drv sets
	 *	 a really दीर्घ txop on AC0 (see connect.c:2009) but only on
	 *	 connect? When not connected should be 0.
	 */
	अगर (!hw_q)
		val |= 0x60;
	अन्यथा
		val |= FIELD_PREP(MT_EDCA_CFG_TXOP, params->txop);
	mt76_wr(dev, MT_EDCA_CFG_AC(hw_q), val);

	val = mt76_rr(dev, MT_WMM_TXOP(hw_q));
	val &= ~(MT_WMM_TXOP_MASK << MT_WMM_TXOP_SHIFT(hw_q));
	val |= params->txop << MT_WMM_TXOP_SHIFT(hw_q);
	mt76_wr(dev, MT_WMM_TXOP(hw_q), val);

	val = mt76_rr(dev, MT_WMM_AIFSN);
	val &= ~(MT_WMM_AIFSN_MASK << MT_WMM_AIFSN_SHIFT(hw_q));
	val |= params->aअगरs << MT_WMM_AIFSN_SHIFT(hw_q);
	mt76_wr(dev, MT_WMM_AIFSN, val);

	val = mt76_rr(dev, MT_WMM_CWMIN);
	val &= ~(MT_WMM_CWMIN_MASK << MT_WMM_CWMIN_SHIFT(hw_q));
	val |= cw_min << MT_WMM_CWMIN_SHIFT(hw_q);
	mt76_wr(dev, MT_WMM_CWMIN, val);

	val = mt76_rr(dev, MT_WMM_CWMAX);
	val &= ~(MT_WMM_CWMAX_MASK << MT_WMM_CWMAX_SHIFT(hw_q));
	val |= cw_max << MT_WMM_CWMAX_SHIFT(hw_q);
	mt76_wr(dev, MT_WMM_CWMAX, val);

	वापस 0;
पूर्ण
