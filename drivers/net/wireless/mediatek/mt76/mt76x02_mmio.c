<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>

#समावेश "mt76x02.h"
#समावेश "mt76x02_mcu.h"
#समावेश "trace.h"

अटल व्योम mt76x02_pre_tbtt_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mt76x02_dev *dev = from_tasklet(dev, t, mt76.pre_tbtt_tasklet);
	काष्ठा mt76_dev *mdev = &dev->mt76;
	काष्ठा mt76_queue *q = dev->mphy.q_tx[MT_TXQ_PSD];
	काष्ठा beacon_bc_data data = अणुपूर्ण;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	अगर (mt76_hw(dev)->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		वापस;

	mt76x02_resync_beacon_समयr(dev);

	/* Prevent corrupt transmissions during update */
	mt76_set(dev, MT_BCN_BYPASS_MASK, 0xffff);
	dev->beacon_data_count = 0;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mt76_hw(dev),
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt76x02_update_beacon_iter, dev);

	mt76_wr(dev, MT_BCN_BYPASS_MASK,
		0xff00 | ~(0xff00 >> dev->beacon_data_count));

	mt76_csa_check(mdev);

	अगर (mdev->csa_complete)
		वापस;

	mt76x02_enqueue_buffered_bc(dev, &data, 8);

	अगर (!skb_queue_len(&data.q))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(data.tail); i++) अणु
		अगर (!data.tail[i])
			जारी;

		mt76_skb_set_moredata(data.tail[i], false);
	पूर्ण

	spin_lock_bh(&q->lock);
	जबतक ((skb = __skb_dequeue(&data.q)) != शून्य) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
		काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;

		mt76_tx_queue_skb(dev, q, skb, &mvअगर->group_wcid, शून्य);
	पूर्ण
	spin_unlock_bh(&q->lock);
पूर्ण

अटल व्योम mt76x02e_pre_tbtt_enable(काष्ठा mt76x02_dev *dev, bool en)
अणु
	अगर (en)
		tasklet_enable(&dev->mt76.pre_tbtt_tasklet);
	अन्यथा
		tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
पूर्ण

अटल व्योम mt76x02e_beacon_enable(काष्ठा mt76x02_dev *dev, bool en)
अणु
	mt76_rmw_field(dev, MT_INT_TIMER_EN, MT_INT_TIMER_EN_PRE_TBTT_EN, en);
	अगर (en)
		mt76x02_irq_enable(dev, MT_INT_PRE_TBTT | MT_INT_TBTT);
	अन्यथा
		mt76x02_irq_disable(dev, MT_INT_PRE_TBTT | MT_INT_TBTT);
पूर्ण

व्योम mt76x02e_init_beacon_config(काष्ठा mt76x02_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76x02_beacon_ops beacon_ops = अणु
		.nslots = 8,
		.slot_size = 1024,
		.pre_tbtt_enable = mt76x02e_pre_tbtt_enable,
		.beacon_enable = mt76x02e_beacon_enable,
	पूर्ण;

	dev->beacon_ops = &beacon_ops;

	/* Fire a pre-TBTT पूर्णांकerrupt 8 ms beक्रमe TBTT */
	mt76_rmw_field(dev, MT_INT_TIMER_CFG, MT_INT_TIMER_CFG_PRE_TBTT,
		       8 << 4);
	mt76_rmw_field(dev, MT_INT_TIMER_CFG, MT_INT_TIMER_CFG_GP_TIMER,
		       MT_DFS_GP_INTERVAL);
	mt76_wr(dev, MT_INT_TIMER_EN, 0);

	mt76x02_init_beacon_config(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02e_init_beacon_config);

अटल पूर्णांक
mt76x02_init_rx_queue(काष्ठा mt76x02_dev *dev, काष्ठा mt76_queue *q,
		      पूर्णांक idx, पूर्णांक n_desc, पूर्णांक bufsize)
अणु
	पूर्णांक err;

	err = mt76_queue_alloc(dev, q, idx, n_desc, bufsize,
			       MT_RX_RING_BASE);
	अगर (err < 0)
		वापस err;

	mt76x02_irq_enable(dev, MT_INT_RX_DONE(idx));

	वापस 0;
पूर्ण

अटल व्योम mt76x02_process_tx_status_fअगरo(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_tx_status stat;
	u8 update = 1;

	जबतक (kfअगरo_get(&dev->txstatus_fअगरo, &stat))
		mt76x02_send_tx_status(dev, &stat, &update);
पूर्ण

अटल व्योम mt76x02_tx_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt76x02_dev *dev;

	dev = container_of(w, काष्ठा mt76x02_dev, mt76.tx_worker);

	mt76x02_mac_poll_tx_status(dev, false);
	mt76x02_process_tx_status_fअगरo(dev);

	mt76_txq_schedule_all(&dev->mphy);
पूर्ण

अटल पूर्णांक mt76x02_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mt76x02_dev *dev = container_of(napi, काष्ठा mt76x02_dev,
					       mt76.tx_napi);
	पूर्णांक i;

	mt76x02_mac_poll_tx_status(dev, false);

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], false);
	क्रम (i = MT_TXQ_PSD; i >= 0; i--)
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], false);

	अगर (napi_complete_करोne(napi, 0))
		mt76x02_irq_enable(dev, MT_INT_TX_DONE_ALL);

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], false);
	क्रम (i = MT_TXQ_PSD; i >= 0; i--)
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], false);

	mt76_worker_schedule(&dev->mt76.tx_worker);

	वापस 0;
पूर्ण

पूर्णांक mt76x02_dma_init(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76_txwi_cache __maybe_unused *t;
	पूर्णांक i, ret, fअगरo_size;
	काष्ठा mt76_queue *q;
	व्योम *status_fअगरo;

	BUILD_BUG_ON(माप(काष्ठा mt76x02_rxwi) > MT_RX_HEADROOM);

	fअगरo_size = roundup_घात_of_two(32 * माप(काष्ठा mt76x02_tx_status));
	status_fअगरo = devm_kzalloc(dev->mt76.dev, fअगरo_size, GFP_KERNEL);
	अगर (!status_fअगरo)
		वापस -ENOMEM;

	dev->mt76.tx_worker.fn = mt76x02_tx_worker;
	tasklet_setup(&dev->mt76.pre_tbtt_tasklet, mt76x02_pre_tbtt_tasklet);

	spin_lock_init(&dev->txstatus_fअगरo_lock);
	kfअगरo_init(&dev->txstatus_fअगरo, status_fअगरo, fअगरo_size);

	mt76_dma_attach(&dev->mt76);

	mt76_wr(dev, MT_WPDMA_RST_IDX, ~0);

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		ret = mt76_init_tx_queue(&dev->mphy, i, mt76_ac_to_hwq(i),
					 MT76x02_TX_RING_SIZE,
					 MT_TX_RING_BASE);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mt76_init_tx_queue(&dev->mphy, MT_TXQ_PSD, MT_TX_HW_QUEUE_MGMT,
				 MT76x02_PSD_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	ret = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT_TX_HW_QUEUE_MCU,
				  MT_MCU_RING_SIZE, MT_TX_RING_BASE);
	अगर (ret)
		वापस ret;

	mt76x02_irq_enable(dev,
			   MT_INT_TX_DONE(IEEE80211_AC_VO) |
			   MT_INT_TX_DONE(IEEE80211_AC_VI) |
			   MT_INT_TX_DONE(IEEE80211_AC_BE) |
			   MT_INT_TX_DONE(IEEE80211_AC_BK) |
			   MT_INT_TX_DONE(MT_TX_HW_QUEUE_MGMT) |
			   MT_INT_TX_DONE(MT_TX_HW_QUEUE_MCU));

	ret = mt76x02_init_rx_queue(dev, &dev->mt76.q_rx[MT_RXQ_MCU], 1,
				    MT_MCU_RING_SIZE, MT_RX_BUF_SIZE);
	अगर (ret)
		वापस ret;

	q = &dev->mt76.q_rx[MT_RXQ_MAIN];
	q->buf_offset = MT_RX_HEADROOM - माप(काष्ठा mt76x02_rxwi);
	ret = mt76x02_init_rx_queue(dev, q, 0, MT76X02_RX_RING_SIZE,
				    MT_RX_BUF_SIZE);
	अगर (ret)
		वापस ret;

	ret = mt76_init_queues(dev, mt76_dma_rx_poll);
	अगर (ret)
		वापस ret;

	netअगर_tx_napi_add(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt76x02_poll_tx, NAPI_POLL_WEIGHT);
	napi_enable(&dev->mt76.tx_napi);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_dma_init);

व्योम mt76x02_rx_poll_complete(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q)
अणु
	काष्ठा mt76x02_dev *dev;

	dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	mt76x02_irq_enable(dev, MT_INT_RX_DONE(q));
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_rx_poll_complete);

irqवापस_t mt76x02_irq_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mt76x02_dev *dev = dev_instance;
	u32 पूर्णांकr, mask;

	पूर्णांकr = mt76_rr(dev, MT_INT_SOURCE_CSR);
	पूर्णांकr &= dev->mt76.mmio.irqmask;
	mt76_wr(dev, MT_INT_SOURCE_CSR, पूर्णांकr);

	अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->mphy.state))
		वापस IRQ_NONE;

	trace_dev_irq(&dev->mt76, पूर्णांकr, dev->mt76.mmio.irqmask);

	mask = पूर्णांकr & (MT_INT_RX_DONE_ALL | MT_INT_GPTIMER);
	अगर (पूर्णांकr & (MT_INT_TX_DONE_ALL | MT_INT_TX_STAT))
		mask |= MT_INT_TX_DONE_ALL;

	mt76x02_irq_disable(dev, mask);

	अगर (पूर्णांकr & MT_INT_RX_DONE(0))
		napi_schedule(&dev->mt76.napi[0]);

	अगर (पूर्णांकr & MT_INT_RX_DONE(1))
		napi_schedule(&dev->mt76.napi[1]);

	अगर (पूर्णांकr & MT_INT_PRE_TBTT)
		tasklet_schedule(&dev->mt76.pre_tbtt_tasklet);

	/* send buffered multicast frames now */
	अगर (पूर्णांकr & MT_INT_TBTT) अणु
		अगर (dev->mt76.csa_complete)
			mt76_csa_finish(&dev->mt76);
		अन्यथा
			mt76_queue_kick(dev, dev->mphy.q_tx[MT_TXQ_PSD]);
	पूर्ण

	अगर (पूर्णांकr & MT_INT_TX_STAT)
		mt76x02_mac_poll_tx_status(dev, true);

	अगर (पूर्णांकr & (MT_INT_TX_STAT | MT_INT_TX_DONE_ALL))
		napi_schedule(&dev->mt76.tx_napi);

	अगर (पूर्णांकr & MT_INT_GPTIMER)
		tasklet_schedule(&dev->dfs_pd.dfs_tasklet);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_irq_handler);

अटल व्योम mt76x02_dma_enable(काष्ठा mt76x02_dev *dev)
अणु
	u32 val;

	mt76_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);
	mt76x02_रुको_क्रम_wpdma(&dev->mt76, 1000);
	usleep_range(50, 100);

	val = FIELD_PREP(MT_WPDMA_GLO_CFG_DMA_BURST_SIZE, 3) |
	      MT_WPDMA_GLO_CFG_TX_DMA_EN |
	      MT_WPDMA_GLO_CFG_RX_DMA_EN;
	mt76_set(dev, MT_WPDMA_GLO_CFG, val);
	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);
पूर्ण

व्योम mt76x02_dma_disable(काष्ठा mt76x02_dev *dev)
अणु
	u32 val = mt76_rr(dev, MT_WPDMA_GLO_CFG);

	val &= MT_WPDMA_GLO_CFG_DMA_BURST_SIZE |
	       MT_WPDMA_GLO_CFG_BIG_ENDIAN |
	       MT_WPDMA_GLO_CFG_HDR_SEG_LEN;
	val |= MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE;
	mt76_wr(dev, MT_WPDMA_GLO_CFG, val);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_dma_disable);

व्योम mt76x02_mac_start(काष्ठा mt76x02_dev *dev)
अणु
	mt76x02_mac_reset_counters(dev);
	mt76x02_dma_enable(dev);
	mt76_wr(dev, MT_RX_FILTR_CFG, dev->mt76.rxfilter);
	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_ENABLE_TX |
		MT_MAC_SYS_CTRL_ENABLE_RX);
	mt76x02_irq_enable(dev,
			   MT_INT_RX_DONE_ALL | MT_INT_TX_DONE_ALL |
			   MT_INT_TX_STAT);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mac_start);

अटल bool mt76x02_tx_hang(काष्ठा mt76x02_dev *dev)
अणु
	u32 dma_idx, prev_dma_idx;
	काष्ठा mt76_queue *q;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		q = dev->mphy.q_tx[i];

		अगर (!q->queued)
			जारी;

		prev_dma_idx = dev->mt76.tx_dma_idx[i];
		dma_idx = पढ़ोl(&q->regs->dma_idx);
		dev->mt76.tx_dma_idx[i] = dma_idx;

		अगर (prev_dma_idx == dma_idx)
			अवरोध;
	पूर्ण

	वापस i < 4;
पूर्ण

अटल व्योम mt76x02_key_sync(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा ieee80211_key_conf *key, व्योम *data)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	काष्ठा mt76_wcid *wcid;

	अगर (!sta)
		वापस;

	wcid = (काष्ठा mt76_wcid *)sta->drv_priv;

	अगर (wcid->hw_key_idx != key->keyidx || wcid->sw_iv)
		वापस;

	mt76x02_mac_wcid_sync_pn(dev, wcid->idx, key);
पूर्ण

अटल व्योम mt76x02_reset_state(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक i;

	lockdep_निश्चित_held(&dev->mt76.mutex);

	clear_bit(MT76_STATE_RUNNING, &dev->mphy.state);

	rcu_पढ़ो_lock();
	ieee80211_iter_keys_rcu(dev->mt76.hw, शून्य, mt76x02_key_sync, शून्य);
	rcu_पढ़ो_unlock();

	क्रम (i = 0; i < MT76x02_N_WCIDS; i++) अणु
		काष्ठा ieee80211_sta *sta;
		काष्ठा ieee80211_vअगर *vअगर;
		काष्ठा mt76x02_sta *msta;
		काष्ठा mt76_wcid *wcid;
		व्योम *priv;

		wcid = rcu_dereference_रक्षित(dev->mt76.wcid[i],
					lockdep_is_held(&dev->mt76.mutex));
		अगर (!wcid)
			जारी;

		rcu_assign_poपूर्णांकer(dev->mt76.wcid[i], शून्य);

		priv = msta = container_of(wcid, काष्ठा mt76x02_sta, wcid);
		sta = container_of(priv, काष्ठा ieee80211_sta, drv_priv);

		priv = msta->vअगर;
		vअगर = container_of(priv, काष्ठा ieee80211_vअगर, drv_priv);

		__mt76_sta_हटाओ(&dev->mt76, vअगर, sta);
		स_रखो(msta, 0, माप(*msta));
	पूर्ण

	dev->mt76.vअगर_mask = 0;
	dev->mt76.beacon_mask = 0;
पूर्ण

अटल व्योम mt76x02_watchकरोg_reset(काष्ठा mt76x02_dev *dev)
अणु
	u32 mask = dev->mt76.mmio.irqmask;
	bool restart = dev->mt76.mcu_ops->mcu_restart;
	पूर्णांक i;

	ieee80211_stop_queues(dev->mt76.hw);
	set_bit(MT76_RESET, &dev->mphy.state);

	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	mt76_worker_disable(&dev->mt76.tx_worker);
	napi_disable(&dev->mt76.tx_napi);

	mt76_क्रम_each_q_rx(&dev->mt76, i) अणु
		napi_disable(&dev->mt76.napi[i]);
	पूर्ण

	mutex_lock(&dev->mt76.mutex);

	dev->mcu_समयout = 0;
	अगर (restart)
		mt76x02_reset_state(dev);

	अगर (dev->mt76.beacon_mask)
		mt76_clear(dev, MT_BEACON_TIME_CFG,
			   MT_BEACON_TIME_CFG_BEACON_TX |
			   MT_BEACON_TIME_CFG_TBTT_EN);

	mt76x02_irq_disable(dev, mask);

	/* perक्रमm device reset */
	mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
	mt76_wr(dev, MT_MAC_SYS_CTRL, 0);
	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_TX_DMA_EN | MT_WPDMA_GLO_CFG_RX_DMA_EN);
	usleep_range(5000, 10000);
	mt76_wr(dev, MT_INT_SOURCE_CSR, 0xffffffff);

	/* let fw reset DMA */
	mt76_set(dev, 0x734, 0x3);

	अगर (restart)
		mt76_mcu_restart(dev);

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_WM], true);
	क्रम (i = 0; i < __MT_TXQ_MAX; i++)
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], true);

	mt76_क्रम_each_q_rx(&dev->mt76, i) अणु
		mt76_queue_rx_reset(dev, i);
	पूर्ण

	mt76_tx_status_check(&dev->mt76, शून्य, true);

	mt76x02_mac_start(dev);

	अगर (dev->ed_monitor)
		mt76_set(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);

	अगर (dev->mt76.beacon_mask && !restart)
		mt76_set(dev, MT_BEACON_TIME_CFG,
			 MT_BEACON_TIME_CFG_BEACON_TX |
			 MT_BEACON_TIME_CFG_TBTT_EN);

	mt76x02_irq_enable(dev, mask);

	mutex_unlock(&dev->mt76.mutex);

	clear_bit(MT76_RESET, &dev->mphy.state);

	mt76_worker_enable(&dev->mt76.tx_worker);
	napi_enable(&dev->mt76.tx_napi);
	napi_schedule(&dev->mt76.tx_napi);

	tasklet_enable(&dev->mt76.pre_tbtt_tasklet);

	mt76_क्रम_each_q_rx(&dev->mt76, i) अणु
		napi_enable(&dev->mt76.napi[i]);
		napi_schedule(&dev->mt76.napi[i]);
	पूर्ण

	अगर (restart) अणु
		set_bit(MT76_RESTART, &dev->mphy.state);
		mt76x02_mcu_function_select(dev, Q_SELECT, 1);
		ieee80211_restart_hw(dev->mt76.hw);
	पूर्ण अन्यथा अणु
		ieee80211_wake_queues(dev->mt76.hw);
		mt76_txq_schedule_all(&dev->mphy);
	पूर्ण
पूर्ण

व्योम mt76x02_reconfig_complete(काष्ठा ieee80211_hw *hw,
			       क्रमागत ieee80211_reconfig_type reconfig_type)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	अगर (reconfig_type != IEEE80211_RECONFIG_TYPE_RESTART)
		वापस;

	clear_bit(MT76_RESTART, &dev->mphy.state);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_reconfig_complete);

अटल व्योम mt76x02_check_tx_hang(काष्ठा mt76x02_dev *dev)
अणु
	अगर (test_bit(MT76_RESTART, &dev->mphy.state))
		वापस;

	अगर (mt76x02_tx_hang(dev)) अणु
		अगर (++dev->tx_hang_check >= MT_TX_HANG_TH)
			जाओ restart;
	पूर्ण अन्यथा अणु
		dev->tx_hang_check = 0;
	पूर्ण

	अगर (dev->mcu_समयout)
		जाओ restart;

	वापस;

restart:
	mt76x02_watchकरोg_reset(dev);

	dev->tx_hang_reset++;
	dev->tx_hang_check = 0;
	स_रखो(dev->mt76.tx_dma_idx, 0xff,
	       माप(dev->mt76.tx_dma_idx));
पूर्ण

व्योम mt76x02_wdt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt76x02_dev *dev = container_of(work, काष्ठा mt76x02_dev,
					       wdt_work.work);

	mt76x02_check_tx_hang(dev);

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->wdt_work,
				     MT_WATCHDOG_TIME);
पूर्ण
