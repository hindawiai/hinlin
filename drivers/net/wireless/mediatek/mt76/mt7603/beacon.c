<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश "mt7603.h"

काष्ठा beacon_bc_data अणु
	काष्ठा mt7603_dev *dev;
	काष्ठा sk_buff_head q;
	काष्ठा sk_buff *tail[MT7603_MAX_INTERFACES];
	पूर्णांक count[MT7603_MAX_INTERFACES];
पूर्ण;

अटल व्योम
mt7603_update_beacon_iter(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7603_dev *dev = (काष्ठा mt7603_dev *)priv;
	काष्ठा mt76_dev *mdev = &dev->mt76;
	काष्ठा mt7603_vअगर *mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;
	काष्ठा sk_buff *skb = शून्य;

	अगर (!(mdev->beacon_mask & BIT(mvअगर->idx)))
		वापस;

	skb = ieee80211_beacon_get(mt76_hw(dev), vअगर);
	अगर (!skb)
		वापस;

	mt76_tx_queue_skb(dev, dev->mphy.q_tx[MT_TXQ_BEACON], skb,
			  &mvअगर->sta.wcid, शून्य);

	spin_lock_bh(&dev->ps_lock);
	mt76_wr(dev, MT_DMA_FQCR0, MT_DMA_FQCR0_BUSY |
		FIELD_PREP(MT_DMA_FQCR0_TARGET_WCID, mvअगर->sta.wcid.idx) |
		FIELD_PREP(MT_DMA_FQCR0_TARGET_QID,
			   dev->mphy.q_tx[MT_TXQ_CAB]->hw_idx) |
		FIELD_PREP(MT_DMA_FQCR0_DEST_PORT_ID, 3) |
		FIELD_PREP(MT_DMA_FQCR0_DEST_QUEUE_ID, 8));

	अगर (!mt76_poll(dev, MT_DMA_FQCR0, MT_DMA_FQCR0_BUSY, 0, 5000))
		dev->beacon_check = MT7603_WATCHDOG_TIMEOUT;

	spin_unlock_bh(&dev->ps_lock);
पूर्ण

अटल व्योम
mt7603_add_buffered_bc(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा beacon_bc_data *data = priv;
	काष्ठा mt7603_dev *dev = data->dev;
	काष्ठा mt7603_vअगर *mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *skb;

	अगर (!(dev->mt76.beacon_mask & BIT(mvअगर->idx)))
		वापस;

	skb = ieee80211_get_buffered_bc(mt76_hw(dev), vअगर);
	अगर (!skb)
		वापस;

	info = IEEE80211_SKB_CB(skb);
	info->control.vअगर = vअगर;
	info->flags |= IEEE80211_TX_CTL_ASSIGN_SEQ;
	mt76_skb_set_moredata(skb, true);
	__skb_queue_tail(&data->q, skb);
	data->tail[mvअगर->idx] = skb;
	data->count[mvअगर->idx]++;
पूर्ण

व्योम mt7603_pre_tbtt_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mt7603_dev *dev = from_tasklet(dev, t, mt76.pre_tbtt_tasklet);
	काष्ठा mt76_dev *mdev = &dev->mt76;
	काष्ठा mt76_queue *q;
	काष्ठा beacon_bc_data data = अणुपूर्ण;
	काष्ठा sk_buff *skb;
	पूर्णांक i, nframes;

	अगर (mt76_hw(dev)->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		वापस;

	data.dev = dev;
	__skb_queue_head_init(&data.q);

	q = dev->mphy.q_tx[MT_TXQ_BEACON];
	spin_lock_bh(&q->lock);
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mt76_hw(dev),
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt7603_update_beacon_iter, dev);
	mt76_queue_kick(dev, q);
	spin_unlock_bh(&q->lock);

	/* Flush all previous CAB queue packets */
	mt76_wr(dev, MT_WF_ARB_CAB_FLUSH, GENMASK(30, 16) | BIT(0));

	mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[MT_TXQ_CAB], false);

	mt76_csa_check(mdev);
	अगर (mdev->csa_complete)
		जाओ out;

	q = dev->mphy.q_tx[MT_TXQ_CAB];
	करो अणु
		nframes = skb_queue_len(&data.q);
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(mt76_hw(dev),
			IEEE80211_IFACE_ITER_RESUME_ALL,
			mt7603_add_buffered_bc, &data);
	पूर्ण जबतक (nframes != skb_queue_len(&data.q) &&
		 skb_queue_len(&data.q) < 8);

	अगर (skb_queue_empty(&data.q))
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(data.tail); i++) अणु
		अगर (!data.tail[i])
			जारी;

		mt76_skb_set_moredata(data.tail[i], false);
	पूर्ण

	spin_lock_bh(&q->lock);
	जबतक ((skb = __skb_dequeue(&data.q)) != शून्य) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
		काष्ठा mt7603_vअगर *mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;

		mt76_tx_queue_skb(dev, q, skb, &mvअगर->sta.wcid, शून्य);
	पूर्ण
	mt76_queue_kick(dev, q);
	spin_unlock_bh(&q->lock);

	क्रम (i = 0; i < ARRAY_SIZE(data.count); i++)
		mt76_wr(dev, MT_WF_ARB_CAB_COUNT_B0_REG(i),
			data.count[i] << MT_WF_ARB_CAB_COUNT_B0_SHIFT(i));

	mt76_wr(dev, MT_WF_ARB_CAB_START,
		MT_WF_ARB_CAB_START_BSSn(0) |
		(MT_WF_ARB_CAB_START_BSS0n(1) *
		 ((1 << (MT7603_MAX_INTERFACES - 1)) - 1)));

out:
	mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[MT_TXQ_BEACON], false);
	अगर (dev->mphy.q_tx[MT_TXQ_BEACON]->queued > hweight8(mdev->beacon_mask))
		dev->beacon_check++;
पूर्ण

व्योम mt7603_beacon_set_समयr(काष्ठा mt7603_dev *dev, पूर्णांक idx, पूर्णांक पूर्णांकval)
अणु
	u32 pre_tbtt = MT7603_PRE_TBTT_TIME / 64;

	अगर (idx >= 0) अणु
		अगर (पूर्णांकval)
			dev->mt76.beacon_mask |= BIT(idx);
		अन्यथा
			dev->mt76.beacon_mask &= ~BIT(idx);
	पूर्ण

	अगर (!dev->mt76.beacon_mask || (!पूर्णांकval && idx < 0)) अणु
		mt7603_irq_disable(dev, MT_INT_MAC_IRQ3);
		mt76_clear(dev, MT_ARB_SCR, MT_ARB_SCR_BCNQ_OPMODE_MASK);
		mt76_wr(dev, MT_HW_INT_MASK(3), 0);
		वापस;
	पूर्ण

	dev->mt76.beacon_पूर्णांक = पूर्णांकval;
	mt76_wr(dev, MT_TBTT,
		FIELD_PREP(MT_TBTT_PERIOD, पूर्णांकval) | MT_TBTT_CAL_ENABLE);

	mt76_wr(dev, MT_TBTT_TIMER_CFG, 0x99); /* start समयr */

	mt76_rmw_field(dev, MT_ARB_SCR, MT_ARB_SCR_BCNQ_OPMODE_MASK,
		       MT_BCNQ_OPMODE_AP);
	mt76_clear(dev, MT_ARB_SCR, MT_ARB_SCR_TBTT_BCN_PRIO);
	mt76_set(dev, MT_ARB_SCR, MT_ARB_SCR_TBTT_BCAST_PRIO);

	mt76_wr(dev, MT_PRE_TBTT, pre_tbtt);

	mt76_set(dev, MT_HW_INT_MASK(3),
		 MT_HW_INT3_PRE_TBTT0 | MT_HW_INT3_TBTT0);

	mt76_set(dev, MT_WF_ARB_BCN_START,
		 MT_WF_ARB_BCN_START_BSSn(0) |
		 ((dev->mt76.beacon_mask >> 1) *
		  MT_WF_ARB_BCN_START_BSS0n(1)));
	mt7603_irq_enable(dev, MT_INT_MAC_IRQ3);

	अगर (dev->mt76.beacon_mask & ~BIT(0))
		mt76_set(dev, MT_LPON_SBTOR(0), MT_LPON_SBTOR_SUB_BSS_EN);
	अन्यथा
		mt76_clear(dev, MT_LPON_SBTOR(0), MT_LPON_SBTOR_SUB_BSS_EN);
पूर्ण
