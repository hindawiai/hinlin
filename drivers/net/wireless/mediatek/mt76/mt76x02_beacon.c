<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#समावेश "mt76x02.h"

अटल व्योम mt76x02_set_beacon_offsets(काष्ठा mt76x02_dev *dev)
अणु
	u32 regs[4] = अणुपूर्ण;
	u16 val;
	पूर्णांक i;

	क्रम (i = 0; i < dev->beacon_ops->nslots; i++) अणु
		val = i * dev->beacon_ops->slot_size;
		regs[i / 4] |= (val / 64) << (8 * (i % 4));
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		mt76_wr(dev, MT_BCN_OFFSET(i), regs[i]);
पूर्ण

अटल पूर्णांक
mt76x02_ग_लिखो_beacon(काष्ठा mt76x02_dev *dev, पूर्णांक offset, काष्ठा sk_buff *skb)
अणु
	पूर्णांक beacon_len = dev->beacon_ops->slot_size;

	अगर (WARN_ON_ONCE(beacon_len < skb->len + माप(काष्ठा mt76x02_txwi)))
		वापस -ENOSPC;

	/* USB devices alपढ़ोy reserve enough skb headroom क्रम txwi's. This
	 * helps to save slow copies over USB.
	 */
	अगर (mt76_is_usb(&dev->mt76)) अणु
		काष्ठा mt76x02_txwi *txwi;

		txwi = (काष्ठा mt76x02_txwi *)(skb->data - माप(*txwi));
		mt76x02_mac_ग_लिखो_txwi(dev, txwi, skb, शून्य, शून्य, skb->len);
		skb_push(skb, माप(*txwi));
	पूर्ण अन्यथा अणु
		काष्ठा mt76x02_txwi txwi;

		mt76x02_mac_ग_लिखो_txwi(dev, &txwi, skb, शून्य, शून्य, skb->len);
		mt76_wr_copy(dev, offset, &txwi, माप(txwi));
		offset += माप(txwi);
	पूर्ण

	mt76_wr_copy(dev, offset, skb->data, skb->len);
	वापस 0;
पूर्ण

व्योम mt76x02_mac_set_beacon(काष्ठा mt76x02_dev *dev,
			    काष्ठा sk_buff *skb)
अणु
	पूर्णांक bcn_len = dev->beacon_ops->slot_size;
	पूर्णांक bcn_addr = MT_BEACON_BASE + (bcn_len * dev->beacon_data_count);

	अगर (!mt76x02_ग_लिखो_beacon(dev, bcn_addr, skb))
		dev->beacon_data_count++;
	dev_kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mac_set_beacon);

व्योम mt76x02_mac_set_beacon_enable(काष्ठा mt76x02_dev *dev,
				   काष्ठा ieee80211_vअगर *vअगर, bool enable)
अणु
	काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;
	u8 old_mask = dev->mt76.beacon_mask;

	mt76x02_pre_tbtt_enable(dev, false);

	अगर (!dev->mt76.beacon_mask)
		dev->tbtt_count = 0;

	अगर (enable) अणु
		dev->mt76.beacon_mask |= BIT(mvअगर->idx);
	पूर्ण अन्यथा अणु
		dev->mt76.beacon_mask &= ~BIT(mvअगर->idx);
	पूर्ण

	अगर (!!old_mask == !!dev->mt76.beacon_mask)
		जाओ out;

	अगर (dev->mt76.beacon_mask)
		mt76_set(dev, MT_BEACON_TIME_CFG,
			 MT_BEACON_TIME_CFG_BEACON_TX |
			 MT_BEACON_TIME_CFG_TBTT_EN |
			 MT_BEACON_TIME_CFG_TIMER_EN);
	अन्यथा
		mt76_clear(dev, MT_BEACON_TIME_CFG,
			   MT_BEACON_TIME_CFG_BEACON_TX |
			   MT_BEACON_TIME_CFG_TBTT_EN |
			   MT_BEACON_TIME_CFG_TIMER_EN);
	mt76x02_beacon_enable(dev, !!dev->mt76.beacon_mask);

out:
	mt76x02_pre_tbtt_enable(dev, true);
पूर्ण

व्योम
mt76x02_resync_beacon_समयr(काष्ठा mt76x02_dev *dev)
अणु
	u32 समयr_val = dev->mt76.beacon_पूर्णांक << 4;

	dev->tbtt_count++;

	/*
	 * Beacon समयr drअगरts by 1us every tick, the समयr is configured
	 * in 1/16 TU (64us) units.
	 */
	अगर (dev->tbtt_count < 63)
		वापस;

	/*
	 * The updated beacon पूर्णांकerval takes effect after two TBTT, because
	 * at this poपूर्णांक the original पूर्णांकerval has alपढ़ोy been loaded पूर्णांकo
	 * the next TBTT_TIMER value
	 */
	अगर (dev->tbtt_count == 63)
		समयr_val -= 1;

	mt76_rmw_field(dev, MT_BEACON_TIME_CFG,
		       MT_BEACON_TIME_CFG_INTVAL, समयr_val);

	अगर (dev->tbtt_count >= 64)
		dev->tbtt_count = 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_resync_beacon_समयr);

व्योम
mt76x02_update_beacon_iter(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76x02_dev *dev = (काष्ठा mt76x02_dev *)priv;
	काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;
	काष्ठा sk_buff *skb = शून्य;

	अगर (!(dev->mt76.beacon_mask & BIT(mvअगर->idx)))
		वापस;

	skb = ieee80211_beacon_get(mt76_hw(dev), vअगर);
	अगर (!skb)
		वापस;

	mt76x02_mac_set_beacon(dev, skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_update_beacon_iter);

अटल व्योम
mt76x02_add_buffered_bc(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा beacon_bc_data *data = priv;
	काष्ठा mt76x02_dev *dev = data->dev;
	काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;
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
पूर्ण

व्योम
mt76x02_enqueue_buffered_bc(काष्ठा mt76x02_dev *dev,
			    काष्ठा beacon_bc_data *data,
			    पूर्णांक max_nframes)
अणु
	पूर्णांक i, nframes;

	data->dev = dev;
	__skb_queue_head_init(&data->q);

	करो अणु
		nframes = skb_queue_len(&data->q);
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(mt76_hw(dev),
			IEEE80211_IFACE_ITER_RESUME_ALL,
			mt76x02_add_buffered_bc, data);
	पूर्ण जबतक (nframes != skb_queue_len(&data->q) &&
		 skb_queue_len(&data->q) < max_nframes);

	अगर (!skb_queue_len(&data->q))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(data->tail); i++) अणु
		अगर (!data->tail[i])
			जारी;
		mt76_skb_set_moredata(data->tail[i], false);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_enqueue_buffered_bc);

व्योम mt76x02_init_beacon_config(काष्ठा mt76x02_dev *dev)
अणु
	mt76_clear(dev, MT_BEACON_TIME_CFG, (MT_BEACON_TIME_CFG_TIMER_EN |
					     MT_BEACON_TIME_CFG_TBTT_EN |
					     MT_BEACON_TIME_CFG_BEACON_TX));
	mt76_set(dev, MT_BEACON_TIME_CFG, MT_BEACON_TIME_CFG_SYNC_MODE);
	mt76_wr(dev, MT_BCN_BYPASS_MASK, 0xffff);
	mt76x02_set_beacon_offsets(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_init_beacon_config);

