<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Roy Luo <royluo@google.com>
 *         Ryder Lee <ryder.lee@mediatek.com>
 *         Felix Fietkau <nbd@nbd.name>
 *         Lorenzo Bianconi <lorenzo@kernel.org>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश "mt7615.h"
#समावेश "mcu.h"

अटल bool mt7615_dev_running(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt7615_phy *phy;

	अगर (test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
		वापस true;

	phy = mt7615_ext_phy(dev);

	वापस phy && test_bit(MT76_STATE_RUNNING, &phy->mt76->state);
पूर्ण

अटल पूर्णांक mt7615_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	bool running;
	पूर्णांक ret;

	अगर (!mt7615_रुको_क्रम_mcu_init(dev))
		वापस -EIO;

	mt7615_mutex_acquire(dev);

	running = mt7615_dev_running(dev);

	अगर (!running) अणु
		ret = mt7615_mcu_set_pm(dev, 0, 0);
		अगर (ret)
			जाओ out;

		ret = mt76_connac_mcu_set_mac_enable(&dev->mt76, 0, true, false);
		अगर (ret)
			जाओ out;

		mt7615_mac_enable_nf(dev, 0);
	पूर्ण

	अगर (phy != &dev->phy) अणु
		ret = mt7615_mcu_set_pm(dev, 1, 0);
		अगर (ret)
			जाओ out;

		ret = mt76_connac_mcu_set_mac_enable(&dev->mt76, 1, true, false);
		अगर (ret)
			जाओ out;

		mt7615_mac_enable_nf(dev, 1);
	पूर्ण

	अगर (mt7615_firmware_offload(dev)) अणु
		ret = mt76_connac_mcu_set_channel_करोमुख्य(phy->mt76);
		अगर (ret)
			जाओ out;

		ret = mt76_connac_mcu_set_rate_txघातer(phy->mt76);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = mt7615_mcu_set_chan_info(phy, MCU_EXT_CMD_SET_RX_PATH);
	अगर (ret)
		जाओ out;

	set_bit(MT76_STATE_RUNNING, &phy->mt76->state);

	ieee80211_queue_delayed_work(hw, &phy->mt76->mac_work,
				     MT7615_WATCHDOG_TIME);

	अगर (!running)
		mt7615_mac_reset_counters(dev);

out:
	mt7615_mutex_release(dev);

	वापस ret;
पूर्ण

अटल व्योम mt7615_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);

	cancel_delayed_work_sync(&phy->mt76->mac_work);
	del_समयr_sync(&phy->roc_समयr);
	cancel_work_sync(&phy->roc_work);

	cancel_delayed_work_sync(&dev->pm.ps_work);
	cancel_work_sync(&dev->pm.wake_work);

	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, शून्य);

	mt7615_mutex_acquire(dev);

	mt76_tesपंचांगode_reset(phy->mt76, true);

	clear_bit(MT76_STATE_RUNNING, &phy->mt76->state);
	cancel_delayed_work_sync(&phy->scan_work);

	अगर (phy != &dev->phy) अणु
		mt7615_mcu_set_pm(dev, 1, 1);
		mt76_connac_mcu_set_mac_enable(&dev->mt76, 1, false, false);
	पूर्ण

	अगर (!mt7615_dev_running(dev)) अणु
		mt7615_mcu_set_pm(dev, 0, 1);
		mt76_connac_mcu_set_mac_enable(&dev->mt76, 0, false, false);
	पूर्ण

	mt7615_mutex_release(dev);
पूर्ण

अटल अंतरभूत पूर्णांक get_मुक्त_idx(u32 mask, u8 start, u8 end)
अणु
	वापस ffs(~mask & GENMASK(end, start));
पूर्ण

अटल पूर्णांक get_omac_idx(क्रमागत nl80211_अगरtype type, u64 mask)
अणु
	पूर्णांक i;

	चयन (type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_STATION:
		/* prefer hw bssid slot 1-3 */
		i = get_मुक्त_idx(mask, HW_BSSID_1, HW_BSSID_3);
		अगर (i)
			वापस i - 1;

		अगर (type != NL80211_IFTYPE_STATION)
			अवरोध;

		/* next, try to find a मुक्त repeater entry क्रम the sta */
		i = get_मुक्त_idx(mask >> REPEATER_BSSID_START, 0,
				 REPEATER_BSSID_MAX - REPEATER_BSSID_START);
		अगर (i)
			वापस i + 32 - 1;

		i = get_मुक्त_idx(mask, EXT_BSSID_1, EXT_BSSID_MAX);
		अगर (i)
			वापस i - 1;

		अगर (~mask & BIT(HW_BSSID_0))
			वापस HW_BSSID_0;

		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_AP:
		/* ap uses hw bssid 0 and ext bssid */
		अगर (~mask & BIT(HW_BSSID_0))
			वापस HW_BSSID_0;

		i = get_मुक्त_idx(mask, EXT_BSSID_1, EXT_BSSID_MAX);
		अगर (i)
			वापस i - 1;

		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक mt7615_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	काष्ठा mt76_txq *mtxq;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक idx, ret = 0;

	mt7615_mutex_acquire(dev);

	mt76_tesपंचांगode_reset(phy->mt76, true);

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR &&
	    is_zero_ether_addr(vअगर->addr))
		phy->monitor_vअगर = vअगर;

	mvअगर->mt76.idx = ffs(~dev->mt76.vअगर_mask) - 1;
	अगर (mvअगर->mt76.idx >= MT7615_MAX_INTERFACES) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	idx = get_omac_idx(vअगर->type, dev->omac_mask);
	अगर (idx < 0) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण
	mvअगर->mt76.omac_idx = idx;

	mvअगर->mt76.band_idx = ext_phy;
	अगर (mt7615_ext_phy(dev))
		mvअगर->mt76.wmm_idx = ext_phy * (MT7615_MAX_WMM_SETS / 2) +
				mvअगर->mt76.idx % (MT7615_MAX_WMM_SETS / 2);
	अन्यथा
		mvअगर->mt76.wmm_idx = mvअगर->mt76.idx % MT7615_MAX_WMM_SETS;

	dev->mt76.vअगर_mask |= BIT(mvअगर->mt76.idx);
	dev->omac_mask |= BIT_ULL(mvअगर->mt76.omac_idx);
	phy->omac_mask |= BIT_ULL(mvअगर->mt76.omac_idx);

	ret = mt7615_mcu_set_dbdc(dev);
	अगर (ret)
		जाओ out;

	idx = MT7615_WTBL_RESERVED - mvअगर->mt76.idx;

	INIT_LIST_HEAD(&mvअगर->sta.poll_list);
	mvअगर->sta.wcid.idx = idx;
	mvअगर->sta.wcid.ext_phy = mvअगर->mt76.band_idx;
	mvअगर->sta.wcid.hw_key_idx = -1;
	mt7615_mac_wtbl_update(dev, idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], &mvअगर->sta.wcid);
	अगर (vअगर->txq) अणु
		mtxq = (काष्ठा mt76_txq *)vअगर->txq->drv_priv;
		mtxq->wcid = &mvअगर->sta.wcid;
	पूर्ण

	ret = mt7615_mcu_add_dev_info(phy, vअगर, true);
	अगर (ret)
		जाओ out;
out:
	mt7615_mutex_release(dev);

	वापस ret;
पूर्ण

अटल व्योम mt7615_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_sta *msta = &mvअगर->sta;
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	पूर्णांक idx = msta->wcid.idx;

	mt7615_mutex_acquire(dev);

	mt7615_mcu_add_bss_info(phy, vअगर, शून्य, false);
	mt7615_mcu_sta_add(phy, vअगर, शून्य, false);

	mt76_tesपंचांगode_reset(phy->mt76, true);
	अगर (vअगर == phy->monitor_vअगर)
	    phy->monitor_vअगर = शून्य;

	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, &msta->wcid);

	mt7615_mcu_add_dev_info(phy, vअगर, false);

	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], शून्य);

	dev->mt76.vअगर_mask &= ~BIT(mvअगर->mt76.idx);
	dev->omac_mask &= ~BIT_ULL(mvअगर->mt76.omac_idx);
	phy->omac_mask &= ~BIT_ULL(mvअगर->mt76.omac_idx);

	mt7615_mutex_release(dev);

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (!list_empty(&msta->poll_list))
		list_del_init(&msta->poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);
पूर्ण

अटल व्योम mt7615_init_dfs_state(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt76_phy *mphy = phy->mt76;
	काष्ठा ieee80211_hw *hw = mphy->hw;
	काष्ठा cfg80211_chan_def *chandef = &hw->conf.chandef;

	अगर (hw->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		वापस;

	अगर (!(chandef->chan->flags & IEEE80211_CHAN_RADAR))
		वापस;

	अगर (mphy->chandef.chan->center_freq == chandef->chan->center_freq &&
	    mphy->chandef.width == chandef->width)
		वापस;

	phy->dfs_state = -1;
पूर्ण

पूर्णांक mt7615_set_channel(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक ret;

	cancel_delayed_work_sync(&phy->mt76->mac_work);

	mt7615_mutex_acquire(dev);

	set_bit(MT76_RESET, &phy->mt76->state);

	mt7615_init_dfs_state(phy);
	mt76_set_channel(phy->mt76);

	अगर (is_mt7615(&dev->mt76) && dev->flash_eeprom) अणु
		ret = mt7615_mcu_apply_rx_dcoc(phy);
		अगर (ret)
			जाओ out;

		ret = mt7615_mcu_apply_tx_dpd(phy);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = mt7615_mcu_set_chan_info(phy, MCU_EXT_CMD_CHANNEL_SWITCH);
	अगर (ret)
		जाओ out;

	mt7615_mac_set_timing(phy);
	ret = mt7615_dfs_init_radar_detector(phy);
	अगर (ret)
		जाओ out;

	mt7615_mac_cca_stats_reset(phy);
	ret = mt7615_mcu_set_sku_en(phy, true);
	अगर (ret)
		जाओ out;

	mt7615_mac_reset_counters(dev);
	phy->noise = 0;
	phy->chfreq = mt76_rr(dev, MT_CHFREQ(ext_phy));

out:
	clear_bit(MT76_RESET, &phy->mt76->state);

	mt7615_mutex_release(dev);

	mt76_worker_schedule(&dev->mt76.tx_worker);
	अगर (!mt76_tesपंचांगode_enabled(phy->mt76))
		ieee80211_queue_delayed_work(phy->mt76->hw,
					     &phy->mt76->mac_work,
					     MT7615_WATCHDOG_TIME);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7615_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			  काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_sta *msta = sta ? (काष्ठा mt7615_sta *)sta->drv_priv :
				  &mvअगर->sta;
	काष्ठा mt76_wcid *wcid = &msta->wcid;
	पूर्णांक idx = key->keyidx, err = 0;
	u8 *wcid_keyidx = &wcid->hw_key_idx;

	/* The hardware करोes not support per-STA RX GTK, fallback
	 * to software mode क्रम these.
	 */
	अगर ((vअगर->type == NL80211_IFTYPE_ADHOC ||
	     vअगर->type == NL80211_IFTYPE_MESH_POINT) &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		वापस -EOPNOTSUPP;

	/* fall back to sw encryption क्रम unsupported ciphers */
	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		wcid_keyidx = &wcid->hw_key_idx2;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIE;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
	हाल WLAN_CIPHER_SUITE_SMS4:
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	mt7615_mutex_acquire(dev);

	अगर (cmd == SET_KEY)
		*wcid_keyidx = idx;
	अन्यथा अगर (idx == *wcid_keyidx)
		*wcid_keyidx = -1;
	अन्यथा
		जाओ out;

	mt76_wcid_key_setup(&dev->mt76, wcid,
			    cmd == SET_KEY ? key : शून्य);

	अगर (mt76_is_mmio(&dev->mt76))
		err = mt7615_mac_wtbl_set_key(dev, wcid, key, cmd);
	अन्यथा
		err = __mt7615_mac_wtbl_set_key(dev, wcid, key, cmd);

out:
	mt7615_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक mt7615_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	bool band = phy != &dev->phy;
	पूर्णांक ret = 0;

	अगर (changed & (IEEE80211_CONF_CHANGE_CHANNEL |
		       IEEE80211_CONF_CHANGE_POWER)) अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
		अगर (phy->mt76->test.state != MT76_TM_STATE_OFF) अणु
			mt7615_mutex_acquire(dev);
			mt76_tesपंचांगode_reset(phy->mt76, false);
			mt7615_mutex_release(dev);
		पूर्ण
#पूर्ण_अगर
		ieee80211_stop_queues(hw);
		ret = mt7615_set_channel(phy);
		ieee80211_wake_queues(hw);
	पूर्ण

	mt7615_mutex_acquire(dev);

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		mt76_tesपंचांगode_reset(phy->mt76, true);

		अगर (!(hw->conf.flags & IEEE80211_CONF_MONITOR))
			phy->rxfilter |= MT_WF_RFCR_DROP_OTHER_UC;
		अन्यथा
			phy->rxfilter &= ~MT_WF_RFCR_DROP_OTHER_UC;

		mt76_wr(dev, MT_WF_RFCR(band), phy->rxfilter);
	पूर्ण

	mt7615_mutex_release(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7615_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर, u16 queue,
	       स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	पूर्णांक err;

	mt7615_mutex_acquire(dev);

	queue = mt7615_lmac_mapping(dev, queue);
	queue += mvअगर->wmm_idx * MT7615_MAX_WMM_SETS;
	err = mt7615_mcu_set_wmm(dev, queue, params);

	mt7615_mutex_release(dev);

	वापस err;
पूर्ण

अटल व्योम mt7615_configure_filter(काष्ठा ieee80211_hw *hw,
				    अचिन्हित पूर्णांक changed_flags,
				    अचिन्हित पूर्णांक *total_flags,
				    u64 multicast)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	bool band = phy != &dev->phy;

	u32 ctl_flags = MT_WF_RFCR1_DROP_ACK |
			MT_WF_RFCR1_DROP_BF_POLL |
			MT_WF_RFCR1_DROP_BA |
			MT_WF_RFCR1_DROP_CFEND |
			MT_WF_RFCR1_DROP_CFACK;
	u32 flags = 0;

	mt7615_mutex_acquire(dev);

#घोषणा MT76_FILTER(_flag, _hw) करो अणु \
		flags |= *total_flags & FIF_##_flag;			\
		phy->rxfilter &= ~(_hw);				\
		अगर (!mt76_tesपंचांगode_enabled(phy->mt76))			\
			phy->rxfilter |= !(flags & FIF_##_flag) * (_hw);\
	पूर्ण जबतक (0)

	phy->rxfilter &= ~(MT_WF_RFCR_DROP_OTHER_BSS |
			   MT_WF_RFCR_DROP_FRAME_REPORT |
			   MT_WF_RFCR_DROP_PROBEREQ |
			   MT_WF_RFCR_DROP_MCAST_FILTERED |
			   MT_WF_RFCR_DROP_MCAST |
			   MT_WF_RFCR_DROP_BCAST |
			   MT_WF_RFCR_DROP_DUPLICATE |
			   MT_WF_RFCR_DROP_A2_BSSID |
			   MT_WF_RFCR_DROP_UNWANTED_CTL |
			   MT_WF_RFCR_DROP_STBC_MULTI);

	अगर (phy->n_beacon_vअगर || !mt7615_firmware_offload(dev))
		phy->rxfilter &= ~MT_WF_RFCR_DROP_OTHER_BEACON;

	MT76_FILTER(OTHER_BSS, MT_WF_RFCR_DROP_OTHER_TIM |
			       MT_WF_RFCR_DROP_A3_MAC |
			       MT_WF_RFCR_DROP_A3_BSSID);

	MT76_FILTER(FCSFAIL, MT_WF_RFCR_DROP_FCSFAIL);

	MT76_FILTER(CONTROL, MT_WF_RFCR_DROP_CTS |
			     MT_WF_RFCR_DROP_RTS |
			     MT_WF_RFCR_DROP_CTL_RSV |
			     MT_WF_RFCR_DROP_NDPA);

	*total_flags = flags;
	mt76_wr(dev, MT_WF_RFCR(band), phy->rxfilter);

	अगर (*total_flags & FIF_CONTROL)
		mt76_clear(dev, MT_WF_RFCR1(band), ctl_flags);
	अन्यथा
		mt76_set(dev, MT_WF_RFCR1(band), ctl_flags);

	mt7615_mutex_release(dev);
पूर्ण

अटल व्योम mt7615_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *info,
				    u32 changed)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);

	mt7615_mutex_acquire(dev);

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		पूर्णांक slotसमय = info->use_लघु_slot ? 9 : 20;

		अगर (slotसमय != phy->slotसमय) अणु
			phy->slotसमय = slotसमय;
			mt7615_mac_set_timing(phy);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED && info->enable_beacon) अणु
		mt7615_mcu_add_bss_info(phy, vअगर, शून्य, true);
		mt7615_mcu_sta_add(phy, vअगर, शून्य, true);

		अगर (vअगर->p2p)
			mt7615_mcu_set_p2p_oppps(hw, vअगर);
	पूर्ण

	अगर (changed & (BSS_CHANGED_BEACON |
		       BSS_CHANGED_BEACON_ENABLED))
		mt7615_mcu_add_beacon(dev, hw, vअगर, info->enable_beacon);

	अगर (changed & BSS_CHANGED_PS)
		mt76_connac_mcu_set_vअगर_ps(&dev->mt76, vअगर);

	अगर ((changed & BSS_CHANGED_ARP_FILTER) &&
	    mt7615_firmware_offload(dev)) अणु
		काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;

		mt76_connac_mcu_update_arp_filter(&dev->mt76, &mvअगर->mt76,
						  info);
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC)
		mt7615_mac_set_beacon_filter(phy, vअगर, info->assoc);

	mt7615_mutex_release(dev);
पूर्ण

अटल व्योम
mt7615_channel_चयन_beacon(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);

	mt7615_mutex_acquire(dev);
	mt7615_mcu_add_beacon(dev, hw, vअगर, true);
	mt7615_mutex_release(dev);
पूर्ण

पूर्णांक mt7615_mac_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)sta->drv_priv;
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_phy *phy;
	पूर्णांक idx, err;

	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7615_WTBL_STA - 1);
	अगर (idx < 0)
		वापस -ENOSPC;

	INIT_LIST_HEAD(&msta->poll_list);
	msta->vअगर = mvअगर;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.ext_phy = mvअगर->mt76.band_idx;

	phy = mvअगर->mt76.band_idx ? mt7615_ext_phy(dev) : &dev->phy;
	err = mt76_connac_pm_wake(phy->mt76, &dev->pm);
	अगर (err)
		वापस err;

	अगर (vअगर->type == NL80211_IFTYPE_STATION && !sta->tdls) अणु
		err = mt7615_mcu_add_bss_info(phy, vअगर, sta, true);
		अगर (err)
			वापस err;
	पूर्ण

	mt7615_mac_wtbl_update(dev, idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
	err = mt7615_mcu_sta_add(&dev->phy, vअगर, sta, true);
	अगर (err)
		वापस err;

	mt76_connac_घातer_save_sched(phy->mt76, &dev->pm);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mac_sta_add);

व्योम mt7615_mac_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)sta->drv_priv;
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_phy *phy;

	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, &msta->wcid);

	phy = mvअगर->mt76.band_idx ? mt7615_ext_phy(dev) : &dev->phy;
	mt76_connac_pm_wake(phy->mt76, &dev->pm);

	mt7615_mcu_sta_add(&dev->phy, vअगर, sta, false);
	mt7615_mac_wtbl_update(dev, msta->wcid.idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
	अगर (vअगर->type == NL80211_IFTYPE_STATION && !sta->tdls)
		mt7615_mcu_add_bss_info(phy, vअगर, sta, false);

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (!list_empty(&msta->poll_list))
		list_del_init(&msta->poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);

	mt76_connac_घातer_save_sched(phy->mt76, &dev->pm);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mac_sta_हटाओ);

अटल व्योम mt7615_sta_rate_tbl_update(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)sta->drv_priv;
	काष्ठा ieee80211_sta_rates *sta_rates = rcu_dereference(sta->rates);
	पूर्णांक i;

	spin_lock_bh(&dev->mt76.lock);
	क्रम (i = 0; i < ARRAY_SIZE(msta->rates); i++) अणु
		msta->rates[i].idx = sta_rates->rate[i].idx;
		msta->rates[i].count = sta_rates->rate[i].count;
		msta->rates[i].flags = sta_rates->rate[i].flags;

		अगर (msta->rates[i].idx < 0 || !msta->rates[i].count)
			अवरोध;
	पूर्ण
	msta->n_rates = i;
	अगर (mt76_connac_pm_ref(phy->mt76, &dev->pm)) अणु
		mt7615_mac_set_rates(phy, msta, शून्य, msta->rates);
		mt76_connac_pm_unref(&dev->pm);
	पूर्ण
	spin_unlock_bh(&dev->mt76.lock);
पूर्ण

व्योम mt7615_tx_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt7615_dev *dev = container_of(w, काष्ठा mt7615_dev,
					      mt76.tx_worker);

	अगर (!mt76_connac_pm_ref(&dev->mphy, &dev->pm)) अणु
		queue_work(dev->mt76.wq, &dev->pm.wake_work);
		वापस;
	पूर्ण

	mt76_tx_worker_run(&dev->mt76);
	mt76_connac_pm_unref(&dev->pm);
पूर्ण

अटल व्योम mt7615_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_tx_control *control,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt76_wcid *wcid = &dev->mt76.global_wcid;
	काष्ठा mt7615_sta *msta = शून्य;
	पूर्णांक qid;

	अगर (control->sta) अणु
		msta = (काष्ठा mt7615_sta *)control->sta->drv_priv;
		wcid = &msta->wcid;
	पूर्ण

	अगर (vअगर && !control->sta) अणु
		काष्ठा mt7615_vअगर *mvअगर;

		mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
		msta = &mvअगर->sta;
		wcid = &msta->wcid;
	पूर्ण

	अगर (mt76_connac_pm_ref(mphy, &dev->pm)) अणु
		mt76_tx(mphy, control->sta, wcid, skb);
		mt76_connac_pm_unref(&dev->pm);
		वापस;
	पूर्ण

	qid = skb_get_queue_mapping(skb);
	अगर (qid >= MT_TXQ_PSD) अणु
		qid = IEEE80211_AC_BE;
		skb_set_queue_mapping(skb, qid);
	पूर्ण

	mt76_connac_pm_queue_skb(hw, &dev->pm, wcid, skb);
पूर्ण

अटल पूर्णांक mt7615_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 val)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	पूर्णांक err, band = phy != &dev->phy;

	mt7615_mutex_acquire(dev);
	err = mt76_connac_mcu_set_rts_thresh(&dev->mt76, val, band);
	mt7615_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक
mt7615_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_ampdu_params *params)
अणु
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा ieee80211_sta *sta = params->sta;
	काष्ठा ieee80211_txq *txq = sta->txq[params->tid];
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)sta->drv_priv;
	u16 tid = params->tid;
	u16 ssn = params->ssn;
	काष्ठा mt76_txq *mtxq;
	पूर्णांक ret = 0;

	अगर (!txq)
		वापस -EINVAL;

	mtxq = (काष्ठा mt76_txq *)txq->drv_priv;

	mt7615_mutex_acquire(dev);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		mt76_rx_aggr_start(&dev->mt76, &msta->wcid, tid, ssn,
				   params->buf_size);
		ret = mt7615_mcu_add_rx_ba(dev, params, true);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		mt76_rx_aggr_stop(&dev->mt76, &msta->wcid, tid);
		ret = mt7615_mcu_add_rx_ba(dev, params, false);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		mtxq->aggr = true;
		mtxq->send_bar = false;
		ret = mt7615_mcu_add_tx_ba(dev, params, true);
		ssn = mt7615_mac_get_sta_tid_sn(dev, msta->wcid.idx, tid);
		ieee80211_send_bar(vअगर, sta->addr, tid,
				   IEEE80211_SN_TO_SEQ(ssn));
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		mtxq->aggr = false;
		ret = mt7615_mcu_add_tx_ba(dev, params, false);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		ssn = mt7615_mac_get_sta_tid_sn(dev, msta->wcid.idx, tid);
		params->ssn = ssn;
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggr = false;
		ret = mt7615_mcu_add_tx_ba(dev, params, false);
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	पूर्ण
	mt7615_mutex_release(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7615_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       काष्ठा ieee80211_sta *sta)
अणु
    वापस mt76_sta_state(hw, vअगर, sta, IEEE80211_STA_NOTEXIST,
			  IEEE80211_STA_NONE);
पूर्ण

अटल पूर्णांक
mt7615_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_sta *sta)
अणु
    वापस mt76_sta_state(hw, vअगर, sta, IEEE80211_STA_NONE,
			  IEEE80211_STA_NOTEXIST);
पूर्ण

अटल पूर्णांक
mt7615_get_stats(काष्ठा ieee80211_hw *hw,
		 काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	काष्ठा mib_stats *mib = &phy->mib;

	mt7615_mutex_acquire(phy->dev);

	stats->करोt11RTSSuccessCount = mib->rts_cnt;
	stats->करोt11RTSFailureCount = mib->rts_retries_cnt;
	stats->करोt11FCSErrorCount = mib->fcs_err_cnt;
	stats->करोt11ACKFailureCount = mib->ack_fail_cnt;

	स_रखो(mib, 0, माप(*mib));

	mt7615_mutex_release(phy->dev);

	वापस 0;
पूर्ण

अटल u64
mt7615_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	जोड़ अणु
		u64 t64;
		u32 t32[2];
	पूर्ण tsf;
	u16 idx = mvअगर->mt76.omac_idx;
	u32 reg;

	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	reg = idx > 1 ? MT_LPON_TCR2(idx): MT_LPON_TCR0(idx);

	mt7615_mutex_acquire(dev);

	mt76_set(dev, reg, MT_LPON_TCR_MODE); /* TSF पढ़ो */
	tsf.t32[0] = mt76_rr(dev, MT_LPON_UTTR0);
	tsf.t32[1] = mt76_rr(dev, MT_LPON_UTTR1);

	mt7615_mutex_release(dev);

	वापस tsf.t64;
पूर्ण

अटल व्योम
mt7615_set_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       u64 बारtamp)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	जोड़ अणु
		u64 t64;
		u32 t32[2];
	पूर्ण tsf = अणु .t64 = बारtamp, पूर्ण;
	u16 idx = mvअगर->mt76.omac_idx;
	u32 reg;

	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	reg = idx > 1 ? MT_LPON_TCR2(idx): MT_LPON_TCR0(idx);

	mt7615_mutex_acquire(dev);

	mt76_wr(dev, MT_LPON_UTTR0, tsf.t32[0]);
	mt76_wr(dev, MT_LPON_UTTR1, tsf.t32[1]);
	/* TSF software overग_लिखो */
	mt76_set(dev, reg, MT_LPON_TCR_WRITE);

	mt7615_mutex_release(dev);
पूर्ण

अटल व्योम
mt7615_set_coverage_class(काष्ठा ieee80211_hw *hw, s16 coverage_class)
अणु
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	काष्ठा mt7615_dev *dev = phy->dev;

	mt7615_mutex_acquire(dev);
	phy->coverage_class = max_t(s16, coverage_class, 0);
	mt7615_mac_set_timing(phy);
	mt7615_mutex_release(dev);
पूर्ण

अटल पूर्णांक
mt7615_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	पूर्णांक max_nss = hweight8(hw->wiphy->available_antennas_tx);
	bool ext_phy = phy != &dev->phy;

	अगर (!tx_ant || tx_ant != rx_ant || ffs(tx_ant) > max_nss)
		वापस -EINVAL;

	अगर ((BIT(hweight8(tx_ant)) - 1) != tx_ant)
		tx_ant = BIT(ffs(tx_ant) - 1) - 1;

	mt7615_mutex_acquire(dev);

	phy->mt76->antenna_mask = tx_ant;
	अगर (ext_phy) अणु
		अगर (dev->chainmask == 0xf)
			tx_ant <<= 2;
		अन्यथा
			tx_ant <<= 1;
	पूर्ण
	phy->mt76->chainmask = tx_ant;

	mt76_set_stream_caps(phy->mt76, true);

	mt7615_mutex_release(dev);

	वापस 0;
पूर्ण

अटल व्योम mt7615_roc_iter(व्योम *priv, u8 *mac,
			    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_phy *phy = priv;

	mt7615_mcu_set_roc(phy, vअगर, शून्य, 0);
पूर्ण

व्योम mt7615_roc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_phy *phy;

	phy = (काष्ठा mt7615_phy *)container_of(work, काष्ठा mt7615_phy,
						roc_work);

	अगर (!test_and_clear_bit(MT76_STATE_ROC, &phy->mt76->state))
		वापस;

	mt7615_mutex_acquire(phy->dev);
	ieee80211_iterate_active_पूर्णांकerfaces(phy->mt76->hw,
					    IEEE80211_IFACE_ITER_RESUME_ALL,
					    mt7615_roc_iter, phy);
	mt7615_mutex_release(phy->dev);
	ieee80211_reमुख्य_on_channel_expired(phy->mt76->hw);
पूर्ण

व्योम mt7615_roc_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा mt7615_phy *phy = from_समयr(phy, समयr, roc_समयr);

	ieee80211_queue_work(phy->mt76->hw, &phy->roc_work);
पूर्ण

व्योम mt7615_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_phy *phy;

	phy = (काष्ठा mt7615_phy *)container_of(work, काष्ठा mt7615_phy,
						scan_work.work);

	जबतक (true) अणु
		काष्ठा mt7615_mcu_rxd *rxd;
		काष्ठा sk_buff *skb;

		spin_lock_bh(&phy->dev->mt76.lock);
		skb = __skb_dequeue(&phy->scan_event_list);
		spin_unlock_bh(&phy->dev->mt76.lock);

		अगर (!skb)
			अवरोध;

		rxd = (काष्ठा mt7615_mcu_rxd *)skb->data;
		अगर (rxd->eid == MCU_EVENT_SCHED_SCAN_DONE) अणु
			ieee80211_sched_scan_results(phy->mt76->hw);
		पूर्ण अन्यथा अगर (test_and_clear_bit(MT76_HW_SCANNING,
					      &phy->mt76->state)) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = false,
			पूर्ण;

			ieee80211_scan_completed(phy->mt76->hw, &info);
		पूर्ण
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक
mt7615_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       काष्ठा ieee80211_scan_request *req)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	पूर्णांक err;

	/* fall-back to sw-scan */
	अगर (!mt7615_firmware_offload(dev))
		वापस 1;

	mt7615_mutex_acquire(dev);
	err = mt76_connac_mcu_hw_scan(mphy, vअगर, req);
	mt7615_mutex_release(dev);

	वापस err;
पूर्ण

अटल व्योम
mt7615_cancel_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;

	mt7615_mutex_acquire(dev);
	mt76_connac_mcu_cancel_hw_scan(mphy, vअगर);
	mt7615_mutex_release(dev);
पूर्ण

अटल पूर्णांक
mt7615_start_sched_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा cfg80211_sched_scan_request *req,
			काष्ठा ieee80211_scan_ies *ies)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	पूर्णांक err;

	अगर (!mt7615_firmware_offload(dev))
		वापस -EOPNOTSUPP;

	mt7615_mutex_acquire(dev);

	err = mt76_connac_mcu_sched_scan_req(mphy, vअगर, req);
	अगर (err < 0)
		जाओ out;

	err = mt76_connac_mcu_sched_scan_enable(mphy, vअगर, true);
out:
	mt7615_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक
mt7615_stop_sched_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	पूर्णांक err;

	अगर (!mt7615_firmware_offload(dev))
		वापस -EOPNOTSUPP;

	mt7615_mutex_acquire(dev);
	err = mt76_connac_mcu_sched_scan_enable(mphy, vअगर, false);
	mt7615_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक mt7615_reमुख्य_on_channel(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_channel *chan,
				    पूर्णांक duration,
				    क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	पूर्णांक err;

	अगर (test_and_set_bit(MT76_STATE_ROC, &phy->mt76->state))
		वापस 0;

	mt7615_mutex_acquire(phy->dev);

	err = mt7615_mcu_set_roc(phy, vअगर, chan, duration);
	अगर (err < 0) अणु
		clear_bit(MT76_STATE_ROC, &phy->mt76->state);
		जाओ out;
	पूर्ण

	अगर (!रुको_event_समयout(phy->roc_रुको, phy->roc_grant, HZ)) अणु
		mt7615_mcu_set_roc(phy, vअगर, शून्य, 0);
		clear_bit(MT76_STATE_ROC, &phy->mt76->state);
		err = -ETIMEDOUT;
	पूर्ण

out:
	mt7615_mutex_release(phy->dev);

	वापस err;
पूर्ण

अटल पूर्णांक mt7615_cancel_reमुख्य_on_channel(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	पूर्णांक err;

	अगर (!test_and_clear_bit(MT76_STATE_ROC, &phy->mt76->state))
		वापस 0;

	del_समयr_sync(&phy->roc_समयr);
	cancel_work_sync(&phy->roc_work);

	mt7615_mutex_acquire(phy->dev);
	err = mt7615_mcu_set_roc(phy, vअगर, शून्य, 0);
	mt7615_mutex_release(phy->dev);

	वापस err;
पूर्ण

अटल व्योम mt7615_sta_set_decap_offload(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta,
				 bool enabled)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)sta->drv_priv;

	अगर (enabled)
		set_bit(MT_WCID_FLAG_HDR_TRANS, &msta->wcid.flags);
	अन्यथा
		clear_bit(MT_WCID_FLAG_HDR_TRANS, &msta->wcid.flags);

	mt7615_mcu_sta_update_hdr_trans(dev, vअगर, sta);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mt7615_suspend(काष्ठा ieee80211_hw *hw,
			  काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	पूर्णांक err = 0;

	cancel_delayed_work_sync(&dev->pm.ps_work);
	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, शून्य);

	mt7615_mutex_acquire(dev);

	clear_bit(MT76_STATE_RUNNING, &phy->mt76->state);
	cancel_delayed_work_sync(&phy->scan_work);
	cancel_delayed_work_sync(&phy->mt76->mac_work);

	set_bit(MT76_STATE_SUSPEND, &phy->mt76->state);
	ieee80211_iterate_active_पूर्णांकerfaces(hw,
					    IEEE80211_IFACE_ITER_RESUME_ALL,
					    mt76_connac_mcu_set_suspend_iter,
					    phy->mt76);

	अगर (!mt7615_dev_running(dev))
		err = mt76_connac_mcu_set_hअगर_suspend(&dev->mt76, true);

	mt7615_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक mt7615_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	bool running;

	mt7615_mutex_acquire(dev);

	running = mt7615_dev_running(dev);
	set_bit(MT76_STATE_RUNNING, &phy->mt76->state);

	अगर (!running) अणु
		पूर्णांक err;

		err = mt76_connac_mcu_set_hअगर_suspend(&dev->mt76, false);
		अगर (err < 0) अणु
			mt7615_mutex_release(dev);
			वापस err;
		पूर्ण
	पूर्ण

	clear_bit(MT76_STATE_SUSPEND, &phy->mt76->state);
	ieee80211_iterate_active_पूर्णांकerfaces(hw,
					    IEEE80211_IFACE_ITER_RESUME_ALL,
					    mt76_connac_mcu_set_suspend_iter,
					    phy->mt76);

	ieee80211_queue_delayed_work(hw, &phy->mt76->mac_work,
				     MT7615_WATCHDOG_TIME);

	mt7615_mutex_release(dev);

	वापस 0;
पूर्ण

अटल व्योम mt7615_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt76_dev *mdev = &dev->mt76;

	device_set_wakeup_enable(mdev->dev, enabled);
पूर्ण

अटल व्योम mt7615_set_rekey_data(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);

	mt7615_mutex_acquire(dev);
	mt76_connac_mcu_update_gtk_rekey(hw, vअगर, data);
	mt7615_mutex_release(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

स्थिर काष्ठा ieee80211_ops mt7615_ops = अणु
	.tx = mt7615_tx,
	.start = mt7615_start,
	.stop = mt7615_stop,
	.add_पूर्णांकerface = mt7615_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = mt7615_हटाओ_पूर्णांकerface,
	.config = mt7615_config,
	.conf_tx = mt7615_conf_tx,
	.configure_filter = mt7615_configure_filter,
	.bss_info_changed = mt7615_bss_info_changed,
	.sta_add = mt7615_sta_add,
	.sta_हटाओ = mt7615_sta_हटाओ,
	.sta_pre_rcu_हटाओ = mt76_sta_pre_rcu_हटाओ,
	.set_key = mt7615_set_key,
	.sta_set_decap_offload = mt7615_sta_set_decap_offload,
	.ampdu_action = mt7615_ampdu_action,
	.set_rts_threshold = mt7615_set_rts_threshold,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sta_rate_tbl_update = mt7615_sta_rate_tbl_update,
	.sw_scan_start = mt76_sw_scan,
	.sw_scan_complete = mt76_sw_scan_complete,
	.release_buffered_frames = mt76_release_buffered_frames,
	.get_txघातer = mt76_get_txघातer,
	.channel_चयन_beacon = mt7615_channel_चयन_beacon,
	.get_stats = mt7615_get_stats,
	.get_tsf = mt7615_get_tsf,
	.set_tsf = mt7615_set_tsf,
	.get_survey = mt76_get_survey,
	.get_antenna = mt76_get_antenna,
	.set_antenna = mt7615_set_antenna,
	.set_coverage_class = mt7615_set_coverage_class,
	.hw_scan = mt7615_hw_scan,
	.cancel_hw_scan = mt7615_cancel_hw_scan,
	.sched_scan_start = mt7615_start_sched_scan,
	.sched_scan_stop = mt7615_stop_sched_scan,
	.reमुख्य_on_channel = mt7615_reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel = mt7615_cancel_reमुख्य_on_channel,
	CFG80211_TESTMODE_CMD(mt76_tesपंचांगode_cmd)
	CFG80211_TESTMODE_DUMP(mt76_tesपंचांगode_dump)
#अगर_घोषित CONFIG_PM
	.suspend = mt7615_suspend,
	.resume = mt7615_resume,
	.set_wakeup = mt7615_set_wakeup,
	.set_rekey_data = mt7615_set_rekey_data,
#पूर्ण_अगर /* CONFIG_PM */
पूर्ण;
EXPORT_SYMBOL_GPL(mt7615_ops);

MODULE_LICENSE("Dual BSD/GPL");
