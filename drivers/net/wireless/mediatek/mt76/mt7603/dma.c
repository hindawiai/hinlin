<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश "mt7603.h"
#समावेश "mac.h"
#समावेश "../dma.h"

अटल व्योम
mt7603_rx_loopback_skb(काष्ठा mt7603_dev *dev, काष्ठा sk_buff *skb)
अणु
	अटल स्थिर u8 tid_to_ac[8] = अणु
		IEEE80211_AC_BE,
		IEEE80211_AC_BK,
		IEEE80211_AC_BK,
		IEEE80211_AC_BE,
		IEEE80211_AC_VI,
		IEEE80211_AC_VI,
		IEEE80211_AC_VO,
		IEEE80211_AC_VO
	पूर्ण;
	__le32 *txd = (__le32 *)skb->data;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_sta *sta;
	काष्ठा mt7603_sta *msta;
	काष्ठा mt76_wcid *wcid;
	व्योम *priv;
	पूर्णांक idx;
	u32 val;
	u8 tid = 0;

	अगर (skb->len < MT_TXD_SIZE + माप(काष्ठा ieee80211_hdr))
		जाओ मुक्त;

	val = le32_to_cpu(txd[1]);
	idx = FIELD_GET(MT_TXD1_WLAN_IDX, val);
	skb->priority = FIELD_GET(MT_TXD1_TID, val);

	अगर (idx >= MT7603_WTBL_STA - 1)
		जाओ मुक्त;

	wcid = rcu_dereference(dev->mt76.wcid[idx]);
	अगर (!wcid)
		जाओ मुक्त;

	priv = msta = container_of(wcid, काष्ठा mt7603_sta, wcid);
	val = le32_to_cpu(txd[0]);
	val &= ~(MT_TXD0_P_IDX | MT_TXD0_Q_IDX);
	val |= FIELD_PREP(MT_TXD0_Q_IDX, MT_TX_HW_QUEUE_MGMT);
	txd[0] = cpu_to_le32(val);

	sta = container_of(priv, काष्ठा ieee80211_sta, drv_priv);
	hdr = (काष्ठा ieee80211_hdr *)&skb->data[MT_TXD_SIZE];
	अगर (ieee80211_is_data_qos(hdr->frame_control))
		tid = *ieee80211_get_qos_ctl(hdr) &
		      IEEE80211_QOS_CTL_TAG1D_MASK;
	skb_set_queue_mapping(skb, tid_to_ac[tid]);
	ieee80211_sta_set_buffered(sta, tid, true);

	spin_lock_bh(&dev->ps_lock);
	__skb_queue_tail(&msta->psq, skb);
	अगर (skb_queue_len(&msta->psq) >= 64) अणु
		skb = __skb_dequeue(&msta->psq);
		dev_kमुक्त_skb(skb);
	पूर्ण
	spin_unlock_bh(&dev->ps_lock);
	वापस;

मुक्त:
	dev_kमुक्त_skb(skb);
पूर्ण

व्योम mt7603_queue_rx_skb(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	__le32 *rxd = (__le32 *)skb->data;
	__le32 *end = (__le32 *)&skb->data[skb->len];
	क्रमागत rx_pkt_type type;

	type = FIELD_GET(MT_RXD0_PKT_TYPE, le32_to_cpu(rxd[0]));

	अगर (q == MT_RXQ_MCU) अणु
		अगर (type == PKT_TYPE_RX_EVENT)
			mt76_mcu_rx_event(&dev->mt76, skb);
		अन्यथा
			mt7603_rx_loopback_skb(dev, skb);
		वापस;
	पूर्ण

	चयन (type) अणु
	हाल PKT_TYPE_TXS:
		क्रम (rxd++; rxd + 5 <= end; rxd += 5)
			mt7603_mac_add_txs(dev, rxd);
		dev_kमुक्त_skb(skb);
		अवरोध;
	हाल PKT_TYPE_RX_EVENT:
		mt76_mcu_rx_event(&dev->mt76, skb);
		वापस;
	हाल PKT_TYPE_NORMAL:
		अगर (mt7603_mac_fill_rx(dev, skb) == 0) अणु
			mt76_rx(&dev->mt76, q, skb);
			वापस;
		पूर्ण
		fallthrough;
	शेष:
		dev_kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
mt7603_init_rx_queue(काष्ठा mt7603_dev *dev, काष्ठा mt76_queue *q,
		     पूर्णांक idx, पूर्णांक n_desc, पूर्णांक bufsize)
अणु
	पूर्णांक err;

	err = mt76_queue_alloc(dev, q, idx, n_desc, bufsize,
			       MT_RX_RING_BASE);
	अगर (err < 0)
		वापस err;

	mt7603_irq_enable(dev, MT_INT_RX_DONE(idx));

	वापस 0;
पूर्ण

अटल पूर्णांक mt7603_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mt7603_dev *dev;
	पूर्णांक i;

	dev = container_of(napi, काष्ठा mt7603_dev, mt76.tx_napi);
	dev->tx_dma_check = 0;

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], false);
	क्रम (i = MT_TXQ_PSD; i >= 0; i--)
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], false);

	अगर (napi_complete_करोne(napi, 0))
		mt7603_irq_enable(dev, MT_INT_TX_DONE_ALL);

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], false);
	क्रम (i = MT_TXQ_PSD; i >= 0; i--)
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], false);

	mt7603_mac_sta_poll(dev);

	mt76_worker_schedule(&dev->mt76.tx_worker);

	वापस 0;
पूर्ण

पूर्णांक mt7603_dma_init(काष्ठा mt7603_dev *dev)
अणु
	अटल स्थिर u8 wmm_queue_map[] = अणु
		[IEEE80211_AC_BK] = 0,
		[IEEE80211_AC_BE] = 1,
		[IEEE80211_AC_VI] = 2,
		[IEEE80211_AC_VO] = 3,
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक i;

	mt76_dma_attach(&dev->mt76);

	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_TX_DMA_EN |
		   MT_WPDMA_GLO_CFG_RX_DMA_EN |
		   MT_WPDMA_GLO_CFG_DMA_BURST_SIZE |
		   MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);

	mt76_wr(dev, MT_WPDMA_RST_IDX, ~0);
	mt7603_pse_client_reset(dev);

	क्रम (i = 0; i < ARRAY_SIZE(wmm_queue_map); i++) अणु
		ret = mt76_init_tx_queue(&dev->mphy, i, wmm_queue_map[i],
					 MT7603_TX_RING_SIZE, MT_TX_RING_BASE);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mt76_init_tx_queue(&dev->mphy, MT_TXQ_PSD, MT_TX_HW_QUEUE_MGMT,
				 MT7603_PSD_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	ret = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT_TX_HW_QUEUE_MCU,
				  MT_MCU_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	ret = mt76_init_tx_queue(&dev->mphy, MT_TXQ_BEACON, MT_TX_HW_QUEUE_BCN,
				 MT_MCU_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	ret = mt76_init_tx_queue(&dev->mphy, MT_TXQ_CAB, MT_TX_HW_QUEUE_BMC,
				 MT_MCU_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	mt7603_irq_enable(dev,
			  MT_INT_TX_DONE(IEEE80211_AC_VO) |
			  MT_INT_TX_DONE(IEEE80211_AC_VI) |
			  MT_INT_TX_DONE(IEEE80211_AC_BE) |
			  MT_INT_TX_DONE(IEEE80211_AC_BK) |
			  MT_INT_TX_DONE(MT_TX_HW_QUEUE_MGMT) |
			  MT_INT_TX_DONE(MT_TX_HW_QUEUE_MCU) |
			  MT_INT_TX_DONE(MT_TX_HW_QUEUE_BCN) |
			  MT_INT_TX_DONE(MT_TX_HW_QUEUE_BMC));

	ret = mt7603_init_rx_queue(dev, &dev->mt76.q_rx[MT_RXQ_MCU], 1,
				   MT7603_MCU_RX_RING_SIZE, MT_RX_BUF_SIZE);
	अगर (ret)
		वापस ret;

	ret = mt7603_init_rx_queue(dev, &dev->mt76.q_rx[MT_RXQ_MAIN], 0,
				   MT7603_RX_RING_SIZE, MT_RX_BUF_SIZE);
	अगर (ret)
		वापस ret;

	mt76_wr(dev, MT_DELAY_INT_CFG, 0);
	ret = mt76_init_queues(dev, mt76_dma_rx_poll);
	अगर (ret)
		वापस ret;

	netअगर_tx_napi_add(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt7603_poll_tx, NAPI_POLL_WEIGHT);
	napi_enable(&dev->mt76.tx_napi);

	वापस 0;
पूर्ण

व्योम mt7603_dma_cleanup(काष्ठा mt7603_dev *dev)
अणु
	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_TX_DMA_EN |
		   MT_WPDMA_GLO_CFG_RX_DMA_EN |
		   MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);

	mt76_dma_cleanup(&dev->mt76);
पूर्ण
