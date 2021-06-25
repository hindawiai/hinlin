<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश "mt76x2u.h"
#समावेश "../mt76x02_usb.h"

अटल पूर्णांक mt76x2u_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	पूर्णांक ret;

	ret = mt76x02u_mac_start(dev);
	अगर (ret)
		वापस ret;

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mphy.mac_work,
				     MT_MAC_WORK_INTERVAL);
	set_bit(MT76_STATE_RUNNING, &dev->mphy.state);

	वापस 0;
पूर्ण

अटल व्योम mt76x2u_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	clear_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	mt76u_stop_tx(&dev->mt76);
	mt76x2u_stop_hw(dev);
पूर्ण

अटल पूर्णांक
mt76x2u_set_channel(काष्ठा mt76x02_dev *dev,
		    काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक err;

	cancel_delayed_work_sync(&dev->cal_work);
	mt76x02_pre_tbtt_enable(dev, false);

	mutex_lock(&dev->mt76.mutex);
	set_bit(MT76_RESET, &dev->mphy.state);

	mt76_set_channel(&dev->mphy);

	mt76x2_mac_stop(dev, false);

	err = mt76x2u_phy_set_channel(dev, chandef);

	mt76x02_mac_cc_reset(dev);
	mt76x2_mac_resume(dev);

	clear_bit(MT76_RESET, &dev->mphy.state);
	mutex_unlock(&dev->mt76.mutex);

	mt76x02_pre_tbtt_enable(dev, true);
	mt76_txq_schedule_all(&dev->mphy);

	वापस err;
पूर्ण

अटल पूर्णांक
mt76x2u_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	पूर्णांक err = 0;

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

		अगर (test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
			mt76x2_phy_set_txघातer(dev);
	पूर्ण

	mutex_unlock(&dev->mt76.mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		ieee80211_stop_queues(hw);
		err = mt76x2u_set_channel(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	पूर्ण

	वापस err;
पूर्ण

स्थिर काष्ठा ieee80211_ops mt76x2u_ops = अणु
	.tx = mt76x02_tx,
	.start = mt76x2u_start,
	.stop = mt76x2u_stop,
	.add_पूर्णांकerface = mt76x02_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = mt76x02_हटाओ_पूर्णांकerface,
	.sta_state = mt76_sta_state,
	.sta_pre_rcu_हटाओ = mt76_sta_pre_rcu_हटाओ,
	.set_key = mt76x02_set_key,
	.ampdu_action = mt76x02_ampdu_action,
	.config = mt76x2u_config,
	.wake_tx_queue = mt76_wake_tx_queue,
	.bss_info_changed = mt76x02_bss_info_changed,
	.configure_filter = mt76x02_configure_filter,
	.conf_tx = mt76x02_conf_tx,
	.sw_scan_start = mt76_sw_scan,
	.sw_scan_complete = mt76x02_sw_scan_complete,
	.sta_rate_tbl_update = mt76x02_sta_rate_tbl_update,
	.get_txघातer = mt76_get_txघातer,
	.get_survey = mt76_get_survey,
	.set_tim = mt76_set_tim,
	.release_buffered_frames = mt76_release_buffered_frames,
	.get_antenna = mt76_get_antenna,
पूर्ण;
