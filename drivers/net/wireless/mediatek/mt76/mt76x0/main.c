<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#समावेश <linux/etherdevice.h>
#समावेश "mt76x0.h"

अटल व्योम
mt76x0_set_channel(काष्ठा mt76x02_dev *dev, काष्ठा cfg80211_chan_def *chandef)
अणु
	cancel_delayed_work_sync(&dev->cal_work);
	mt76x02_pre_tbtt_enable(dev, false);
	अगर (mt76_is_mmio(&dev->mt76))
		tasklet_disable(&dev->dfs_pd.dfs_tasklet);

	mt76_set_channel(&dev->mphy);
	mt76x0_phy_set_channel(dev, chandef);

	mt76x02_mac_cc_reset(dev);
	mt76x02_edcca_init(dev);

	अगर (mt76_is_mmio(&dev->mt76)) अणु
		mt76x02_dfs_init_params(dev);
		tasklet_enable(&dev->dfs_pd.dfs_tasklet);
	पूर्ण
	mt76x02_pre_tbtt_enable(dev, true);

	mt76_txq_schedule_all(&dev->mphy);
पूर्ण

पूर्णांक mt76x0_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	mutex_lock(&dev->mt76.mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		ieee80211_stop_queues(hw);
		mt76x0_set_channel(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		dev->txघातer_conf = hw->conf.घातer_level * 2;

		अगर (test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
			mt76x0_phy_set_txघातer(dev);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		अगर (!(hw->conf.flags & IEEE80211_CONF_MONITOR))
			dev->mt76.rxfilter |= MT_RX_FILTR_CFG_PROMISC;
		अन्यथा
			dev->mt76.rxfilter &= ~MT_RX_FILTR_CFG_PROMISC;

		mt76_wr(dev, MT_RX_FILTR_CFG, dev->mt76.rxfilter);
	पूर्ण

	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x0_config);
