<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश "mt7601u.h"
#समावेश "mac.h"
#समावेश <linux/etherdevice.h>

अटल पूर्णांक mt7601u_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	पूर्णांक ret;

	mutex_lock(&dev->mutex);

	ret = mt7601u_mac_start(dev);
	अगर (ret)
		जाओ out;

	ieee80211_queue_delayed_work(dev->hw, &dev->mac_work,
				     MT_CALIBRATE_INTERVAL);
	ieee80211_queue_delayed_work(dev->hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
out:
	mutex_unlock(&dev->mutex);
	वापस ret;
पूर्ण

अटल व्योम mt7601u_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;

	mutex_lock(&dev->mutex);

	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->mac_work);
	mt7601u_mac_stop(dev);

	mutex_unlock(&dev->mutex);
पूर्ण

अटल पूर्णांक mt7601u_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *) vअगर->drv_priv;
	अचिन्हित पूर्णांक idx = 0;
	अचिन्हित पूर्णांक wcid = GROUP_WCID(idx);

	/* Note: क्रम AP करो the AP-STA things mt76 करोes:
	 *	- beacon offsets
	 *	- करो mac address tricks
	 *	- shअगरt vअगर idx
	 */
	mvअगर->idx = idx;

	अगर (!ether_addr_equal(dev->macaddr, vअगर->addr))
		mt7601u_set_macaddr(dev, vअगर->addr);

	अगर (dev->wcid_mask[wcid / BITS_PER_LONG] & BIT(wcid % BITS_PER_LONG))
		वापस -ENOSPC;
	dev->wcid_mask[wcid / BITS_PER_LONG] |= BIT(wcid % BITS_PER_LONG);
	mvअगर->group_wcid.idx = wcid;
	mvअगर->group_wcid.hw_key_idx = -1;

	वापस 0;
पूर्ण

अटल व्योम mt7601u_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *) vअगर->drv_priv;
	अचिन्हित पूर्णांक wcid = mvअगर->group_wcid.idx;

	dev->wcid_mask[wcid / BITS_PER_LONG] &= ~BIT(wcid % BITS_PER_LONG);
पूर्ण

अटल पूर्णांक mt7601u_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	पूर्णांक ret = 0;

	mutex_lock(&dev->mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		ieee80211_stop_queues(hw);
		ret = mt7601u_phy_set_channel(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	पूर्ण

	mutex_unlock(&dev->mutex);

	वापस ret;
पूर्ण

अटल व्योम
mt76_configure_filter(काष्ठा ieee80211_hw *hw, अचिन्हित पूर्णांक changed_flags,
		      अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	u32 flags = 0;

#घोषणा MT76_FILTER(_flag, _hw) करो अणु \
		flags |= *total_flags & FIF_##_flag;			\
		dev->rxfilter &= ~(_hw);				\
		dev->rxfilter |= !(flags & FIF_##_flag) * (_hw);	\
	पूर्ण जबतक (0)

	mutex_lock(&dev->mutex);

	dev->rxfilter &= ~MT_RX_FILTR_CFG_OTHER_BSS;

	MT76_FILTER(OTHER_BSS, MT_RX_FILTR_CFG_PROMISC);
	MT76_FILTER(FCSFAIL, MT_RX_FILTR_CFG_CRC_ERR);
	MT76_FILTER(PLCPFAIL, MT_RX_FILTR_CFG_PHY_ERR);
	MT76_FILTER(CONTROL, MT_RX_FILTR_CFG_ACK |
			     MT_RX_FILTR_CFG_CTS |
			     MT_RX_FILTR_CFG_CFEND |
			     MT_RX_FILTR_CFG_CFACK |
			     MT_RX_FILTR_CFG_BA |
			     MT_RX_FILTR_CFG_CTRL_RSV);
	MT76_FILTER(PSPOLL, MT_RX_FILTR_CFG_PSPOLL);

	*total_flags = flags;
	mt76_wr(dev, MT_RX_FILTR_CFG, dev->rxfilter);

	mutex_unlock(&dev->mutex);
पूर्ण

अटल व्योम
mt7601u_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_bss_conf *info, u32 changed)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;

	mutex_lock(&dev->mutex);

	अगर (changed & BSS_CHANGED_ASSOC)
		mt7601u_phy_con_cal_onoff(dev, info);

	अगर (changed & BSS_CHANGED_BSSID) अणु
		mt7601u_addr_wr(dev, MT_MAC_BSSID_DW0, info->bssid);

		/* Note: this is a hack because beacon_पूर्णांक is not changed
		 *	 on leave nor is any more appropriate event generated.
		 *	 rt2x00 करोesn't seem to be bothered though.
		 */
		अगर (is_zero_ether_addr(info->bssid))
			mt7601u_mac_config_tsf(dev, false, 0);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		mt7601u_wr(dev, MT_LEGACY_BASIC_RATE, info->basic_rates);
		mt7601u_wr(dev, MT_HT_FBK_CFG0, 0x65432100);
		mt7601u_wr(dev, MT_HT_FBK_CFG1, 0xedcba980);
		mt7601u_wr(dev, MT_LG_FBK_CFG0, 0xedcba988);
		mt7601u_wr(dev, MT_LG_FBK_CFG1, 0x00002100);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_INT)
		mt7601u_mac_config_tsf(dev, true, info->beacon_पूर्णांक);

	अगर (changed & BSS_CHANGED_HT || changed & BSS_CHANGED_ERP_CTS_PROT)
		mt7601u_mac_set_protection(dev, info->use_cts_prot,
					   info->ht_operation_mode);

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE)
		mt7601u_mac_set_लघु_preamble(dev, info->use_लघु_preamble);

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		पूर्णांक slotसमय = info->use_लघु_slot ? 9 : 20;

		mt76_rmw_field(dev, MT_BKOFF_SLOT_CFG,
			       MT_BKOFF_SLOT_CFG_SLOTTIME, slotसमय);
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC)
		mt7601u_phy_recalibrate_after_assoc(dev);

	mutex_unlock(&dev->mutex);
पूर्ण

अटल पूर्णांक
mt76_wcid_alloc(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i, idx = 0;

	क्रम (i = 0; i < ARRAY_SIZE(dev->wcid_mask); i++) अणु
		idx = ffs(~dev->wcid_mask[i]);
		अगर (!idx)
			जारी;

		idx--;
		dev->wcid_mask[i] |= BIT(idx);
		अवरोध;
	पूर्ण

	idx = i * BITS_PER_LONG + idx;
	अगर (idx > 119)
		वापस -1;

	वापस idx;
पूर्ण

अटल पूर्णांक
mt7601u_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	काष्ठा mt76_sta *msta = (काष्ठा mt76_sta *) sta->drv_priv;
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *) vअगर->drv_priv;
	पूर्णांक ret = 0;
	पूर्णांक idx = 0;

	mutex_lock(&dev->mutex);

	idx = mt76_wcid_alloc(dev);
	अगर (idx < 0) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	msta->wcid.idx = idx;
	msta->wcid.hw_key_idx = -1;
	mt7601u_mac_wcid_setup(dev, idx, mvअगर->idx, sta->addr);
	mt76_clear(dev, MT_WCID_DROP(idx), MT_WCID_DROP_MASK(idx));
	rcu_assign_poपूर्णांकer(dev->wcid[idx], &msta->wcid);
	mt7601u_mac_set_ampdu_factor(dev);

out:
	mutex_unlock(&dev->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7601u_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	काष्ठा mt76_sta *msta = (काष्ठा mt76_sta *) sta->drv_priv;
	पूर्णांक idx = msta->wcid.idx;

	mutex_lock(&dev->mutex);
	rcu_assign_poपूर्णांकer(dev->wcid[idx], शून्य);
	mt76_set(dev, MT_WCID_DROP(idx), MT_WCID_DROP_MASK(idx));
	dev->wcid_mask[idx / BITS_PER_LONG] &= ~BIT(idx % BITS_PER_LONG);
	mt7601u_mac_wcid_setup(dev, idx, 0, शून्य);
	mt7601u_mac_set_ampdu_factor(dev);
	mutex_unlock(&dev->mutex);

	वापस 0;
पूर्ण

अटल व्योम
mt7601u_sta_notअगरy(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   क्रमागत sta_notअगरy_cmd cmd, काष्ठा ieee80211_sta *sta)
अणु
पूर्ण

अटल व्योम
mt7601u_sw_scan(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_vअगर *vअगर,
		स्थिर u8 *mac_addr)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;

	mt7601u_agc_save(dev);
	set_bit(MT7601U_STATE_SCANNING, &dev->state);
पूर्ण

अटल व्योम
mt7601u_sw_scan_complete(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;

	mt7601u_agc_restore(dev);
	clear_bit(MT7601U_STATE_SCANNING, &dev->state);

	ieee80211_queue_delayed_work(dev->hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
	अगर (dev->freq_cal.enabled)
		ieee80211_queue_delayed_work(dev->hw, &dev->freq_cal.work,
					     MT_FREQ_CAL_INIT_DELAY);
पूर्ण

अटल पूर्णांक
mt7601u_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *) vअगर->drv_priv;
	काष्ठा mt76_sta *msta = sta ? (काष्ठा mt76_sta *) sta->drv_priv : शून्य;
	काष्ठा mt76_wcid *wcid = msta ? &msta->wcid : &mvअगर->group_wcid;
	पूर्णांक idx = key->keyidx;
	पूर्णांक ret;

	/* fall back to sw encryption क्रम unsupported ciphers */
	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_CCMP:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (cmd == SET_KEY) अणु
		key->hw_key_idx = wcid->idx;
		wcid->hw_key_idx = idx;
	पूर्ण अन्यथा अणु
		अगर (idx == wcid->hw_key_idx)
			wcid->hw_key_idx = -1;

		key = शून्य;
	पूर्ण

	अगर (!msta) अणु
		अगर (key || wcid->hw_key_idx == idx) अणु
			ret = mt76_mac_wcid_set_key(dev, wcid->idx, key);
			अगर (ret)
				वापस ret;
		पूर्ण

		वापस mt76_mac_shared_key_setup(dev, mvअगर->idx, idx, key);
	पूर्ण

	वापस mt76_mac_wcid_set_key(dev, msta->wcid.idx, key);
पूर्ण

अटल पूर्णांक mt7601u_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;

	mt76_rmw_field(dev, MT_TX_RTS_CFG, MT_TX_RTS_CFG_THRESH, value);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 ssn = params->ssn;
	काष्ठा mt76_sta *msta = (काष्ठा mt76_sta *) sta->drv_priv;

	WARN_ON(msta->wcid.idx > GROUP_WCID(0));

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		mt76_set(dev, MT_WCID_ADDR(msta->wcid.idx) + 4, BIT(16 + tid));
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		mt76_clear(dev, MT_WCID_ADDR(msta->wcid.idx) + 4,
			   BIT(16 + tid));
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		ieee80211_send_bar(vअगर, sta->addr, tid, msta->agg_ssn[tid]);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		msta->agg_ssn[tid] = ssn << 4;
		वापस IEEE80211_AMPDU_TX_START_IMMEDIATE;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mt76_sta_rate_tbl_update(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7601u_dev *dev = hw->priv;
	काष्ठा mt76_sta *msta = (काष्ठा mt76_sta *) sta->drv_priv;
	काष्ठा ieee80211_sta_rates *rates;
	काष्ठा ieee80211_tx_rate rate = अणुपूर्ण;

	rcu_पढ़ो_lock();
	rates = rcu_dereference(sta->rates);

	अगर (!rates)
		जाओ out;

	rate.idx = rates->rate[0].idx;
	rate.flags = rates->rate[0].flags;
	mt76_mac_wcid_set_rate(dev, &msta->wcid, &rate);

out:
	rcu_पढ़ो_unlock();
पूर्ण

स्थिर काष्ठा ieee80211_ops mt7601u_ops = अणु
	.tx = mt7601u_tx,
	.start = mt7601u_start,
	.stop = mt7601u_stop,
	.add_पूर्णांकerface = mt7601u_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = mt7601u_हटाओ_पूर्णांकerface,
	.config = mt7601u_config,
	.configure_filter = mt76_configure_filter,
	.bss_info_changed = mt7601u_bss_info_changed,
	.sta_add = mt7601u_sta_add,
	.sta_हटाओ = mt7601u_sta_हटाओ,
	.sta_notअगरy = mt7601u_sta_notअगरy,
	.set_key = mt7601u_set_key,
	.conf_tx = mt7601u_conf_tx,
	.sw_scan_start = mt7601u_sw_scan,
	.sw_scan_complete = mt7601u_sw_scan_complete,
	.ampdu_action = mt76_ampdu_action,
	.sta_rate_tbl_update = mt76_sta_rate_tbl_update,
	.set_rts_threshold = mt7601u_set_rts_threshold,
पूर्ण;
