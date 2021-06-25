<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश "mt76x2.h"
#समावेश "../mt76x02_mac.h"

अटल पूर्णांक
mt76x2_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	mt76x02_mac_start(dev);
	mt76x2_phy_start(dev);

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mphy.mac_work,
				     MT_MAC_WORK_INTERVAL);
	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->wdt_work,
				     MT_WATCHDOG_TIME);

	set_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	वापस 0;
पूर्ण

अटल व्योम
mt76x2_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	clear_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	mt76x2_stop_hardware(dev);
पूर्ण

अटल व्योम
mt76x2_set_channel(काष्ठा mt76x02_dev *dev, काष्ठा cfg80211_chan_def *chandef)
अणु
	cancel_delayed_work_sync(&dev->cal_work);
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	tasklet_disable(&dev->dfs_pd.dfs_tasklet);

	mutex_lock(&dev->mt76.mutex);
	set_bit(MT76_RESET, &dev->mphy.state);

	mt76_set_channel(&dev->mphy);

	mt76x2_mac_stop(dev, true);
	mt76x2_phy_set_channel(dev, chandef);

	mt76x02_mac_cc_reset(dev);
	mt76x02_dfs_init_params(dev);

	mt76x2_mac_resume(dev);

	clear_bit(MT76_RESET, &dev->mphy.state);
	mutex_unlock(&dev->mt76.mutex);

	tasklet_enable(&dev->dfs_pd.dfs_tasklet);
	tasklet_enable(&dev->mt76.pre_tbtt_tasklet);

	mt76_txq_schedule_all(&dev->mphy);
पूर्ण

अटल पूर्णांक
mt76x2_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	mutex_lock(&dev->mt76.mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		अगर (!(hw->conf.flags & IEEE80211_CONF_MONITOR))
			dev->mt76.rxfilter |= MT_RX_FILTR_CFG_PROMISC;
		अन्यथा
			dev->mt76.rxfilter &= ~MT_RX_FILTR_CFG_PROMISC;

		mt76_wr(dev, MT_RX_FILTR_CFG, dev->mt76.rxfilter);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		dev->txघातer_conf = hw->conf.घातer_level * 2;

		/* convert to per-chain घातer क्रम 2x2 devices */
		dev->txघातer_conf -= 6;

		अगर (test_bit(MT76_STATE_RUNNING, &dev->mphy.state)) अणु
			mt76x2_phy_set_txघातer(dev);
			mt76x02_tx_set_txpwr_स्वतः(dev, dev->txघातer_conf);
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->mt76.mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		ieee80211_stop_queues(hw);
		mt76x2_set_channel(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mt76x2_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	     u32 queues, bool drop)
अणु
पूर्ण

अटल पूर्णांक mt76x2_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant,
			      u32 rx_ant)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	अगर (!tx_ant || tx_ant > 3 || tx_ant != rx_ant)
		वापस -EINVAL;

	mutex_lock(&dev->mt76.mutex);

	dev->mphy.chainmask = (tx_ant == 3) ? 0x202 : 0x101;
	dev->mphy.antenna_mask = tx_ant;

	mt76_set_stream_caps(&dev->mphy, true);
	mt76x2_phy_set_antenna(dev);

	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण

स्थिर काष्ठा ieee80211_ops mt76x2_ops = अणु
	.tx = mt76x02_tx,
	.start = mt76x2_start,
	.stop = mt76x2_stop,
	.add_पूर्णांकerface = mt76x02_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = mt76x02_हटाओ_पूर्णांकerface,
	.config = mt76x2_config,
	.configure_filter = mt76x02_configure_filter,
	.bss_info_changed = mt76x02_bss_info_changed,
	.sta_state = mt76_sta_state,
	.sta_pre_rcu_हटाओ = mt76_sta_pre_rcu_हटाओ,
	.set_key = mt76x02_set_key,
	.conf_tx = mt76x02_conf_tx,
	.sw_scan_start = mt76_sw_scan,
	.sw_scan_complete = mt76x02_sw_scan_complete,
	.flush = mt76x2_flush,
	.ampdu_action = mt76x02_ampdu_action,
	.get_txघातer = mt76_get_txघातer,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sta_rate_tbl_update = mt76x02_sta_rate_tbl_update,
	.release_buffered_frames = mt76_release_buffered_frames,
	.set_coverage_class = mt76x02_set_coverage_class,
	.get_survey = mt76_get_survey,
	.set_tim = mt76_set_tim,
	.set_antenna = mt76x2_set_antenna,
	.get_antenna = mt76_get_antenna,
	.set_rts_threshold = mt76x02_set_rts_threshold,
	.reconfig_complete = mt76x02_reconfig_complete,
पूर्ण;

