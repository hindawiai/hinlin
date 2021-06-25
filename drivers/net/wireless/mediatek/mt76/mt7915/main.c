<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश "mt7915.h"
#समावेश "mcu.h"

अटल bool mt7915_dev_running(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt7915_phy *phy;

	अगर (test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
		वापस true;

	phy = mt7915_ext_phy(dev);

	वापस phy && test_bit(MT76_STATE_RUNNING, &phy->mt76->state);
पूर्ण

अटल पूर्णांक mt7915_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	bool running;
	पूर्णांक ret;

	flush_work(&dev->init_work);

	mutex_lock(&dev->mt76.mutex);

	running = mt7915_dev_running(dev);

	अगर (!running) अणु
		ret = mt7915_mcu_set_pm(dev, 0, 0);
		अगर (ret)
			जाओ out;

		ret = mt7915_mcu_set_mac(dev, 0, true, true);
		अगर (ret)
			जाओ out;

		ret = mt7915_mcu_set_scs(dev, 0, true);
		अगर (ret)
			जाओ out;

		mt7915_mac_enable_nf(dev, 0);
	पूर्ण

	अगर (phy != &dev->phy) अणु
		ret = mt7915_mcu_set_pm(dev, 1, 0);
		अगर (ret)
			जाओ out;

		ret = mt7915_mcu_set_mac(dev, 1, true, true);
		अगर (ret)
			जाओ out;

		ret = mt7915_mcu_set_scs(dev, 1, true);
		अगर (ret)
			जाओ out;

		mt7915_mac_enable_nf(dev, 1);
	पूर्ण

	ret = mt7915_mcu_set_rts_thresh(phy, 0x92b);
	अगर (ret)
		जाओ out;

	ret = mt7915_mcu_set_sku_en(phy, true);
	अगर (ret)
		जाओ out;

	ret = mt7915_mcu_set_chan_info(phy, MCU_EXT_CMD(SET_RX_PATH));
	अगर (ret)
		जाओ out;

	set_bit(MT76_STATE_RUNNING, &phy->mt76->state);

	अगर (!mt76_tesपंचांगode_enabled(phy->mt76))
		ieee80211_queue_delayed_work(hw, &phy->mt76->mac_work,
					     MT7915_WATCHDOG_TIME);

	अगर (!running)
		mt7915_mac_reset_counters(phy);

out:
	mutex_unlock(&dev->mt76.mutex);

	वापस ret;
पूर्ण

अटल व्योम mt7915_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);

	cancel_delayed_work_sync(&phy->mt76->mac_work);

	mutex_lock(&dev->mt76.mutex);

	mt76_tesपंचांगode_reset(phy->mt76, true);

	clear_bit(MT76_STATE_RUNNING, &phy->mt76->state);

	अगर (phy != &dev->phy) अणु
		mt7915_mcu_set_pm(dev, 1, 1);
		mt7915_mcu_set_mac(dev, 1, false, false);
	पूर्ण

	अगर (!mt7915_dev_running(dev)) अणु
		mt7915_mcu_set_pm(dev, 0, 1);
		mt7915_mcu_set_mac(dev, 0, false, false);
	पूर्ण

	mutex_unlock(&dev->mt76.mutex);
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

अटल पूर्णांक mt7915_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	काष्ठा mt76_txq *mtxq;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक idx, ret = 0;

	mutex_lock(&dev->mt76.mutex);

	mt76_tesपंचांगode_reset(phy->mt76, true);

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR &&
	    is_zero_ether_addr(vअगर->addr))
		phy->monitor_vअगर = vअगर;

	mvअगर->idx = ffs(~dev->mt76.vअगर_mask) - 1;
	अगर (mvअगर->idx >= MT7915_MAX_INTERFACES) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	idx = get_omac_idx(vअगर->type, phy->omac_mask);
	अगर (idx < 0) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण
	mvअगर->omac_idx = idx;
	mvअगर->phy = phy;
	mvअगर->band_idx = ext_phy;

	अगर (ext_phy)
		mvअगर->wmm_idx = ext_phy * (MT7915_MAX_WMM_SETS / 2) +
				mvअगर->idx % (MT7915_MAX_WMM_SETS / 2);
	अन्यथा
		mvअगर->wmm_idx = mvअगर->idx % MT7915_MAX_WMM_SETS;

	ret = mt7915_mcu_add_dev_info(phy, vअगर, true);
	अगर (ret)
		जाओ out;

	dev->mt76.vअगर_mask |= BIT(mvअगर->idx);
	phy->omac_mask |= BIT_ULL(mvअगर->omac_idx);

	idx = MT7915_WTBL_RESERVED - mvअगर->idx;

	INIT_LIST_HEAD(&mvअगर->sta.rc_list);
	INIT_LIST_HEAD(&mvअगर->sta.stats_list);
	INIT_LIST_HEAD(&mvअगर->sta.poll_list);
	mvअगर->sta.wcid.idx = idx;
	mvअगर->sta.wcid.ext_phy = mvअगर->band_idx;
	mvअगर->sta.wcid.hw_key_idx = -1;
	mvअगर->sta.wcid.tx_info |= MT_WCID_TX_INFO_SET;
	mt7915_mac_wtbl_update(dev, idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], &mvअगर->sta.wcid);
	अगर (vअगर->txq) अणु
		mtxq = (काष्ठा mt76_txq *)vअगर->txq->drv_priv;
		mtxq->wcid = &mvअगर->sta.wcid;
	पूर्ण

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    (!mvअगर->omac_idx || mvअगर->omac_idx > 3))
		vअगर->offload_flags = 0;
	vअगर->offload_flags |= IEEE80211_OFFLOAD_ENCAP_4ADDR;

out:
	mutex_unlock(&dev->mt76.mutex);

	वापस ret;
पूर्ण

अटल व्योम mt7915_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_sta *msta = &mvअगर->sta;
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	पूर्णांक idx = msta->wcid.idx;

	mt7915_mcu_add_bss_info(phy, vअगर, false);
	mt7915_mcu_add_sta(dev, vअगर, शून्य, false);

	mutex_lock(&dev->mt76.mutex);
	mt76_tesपंचांगode_reset(phy->mt76, true);
	mutex_unlock(&dev->mt76.mutex);

	अगर (vअगर == phy->monitor_vअगर)
		phy->monitor_vअगर = शून्य;

	mt7915_mcu_add_dev_info(phy, vअगर, false);

	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], शून्य);

	mutex_lock(&dev->mt76.mutex);
	dev->mt76.vअगर_mask &= ~BIT(mvअगर->idx);
	phy->omac_mask &= ~BIT_ULL(mvअगर->omac_idx);
	mutex_unlock(&dev->mt76.mutex);

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (!list_empty(&msta->poll_list))
		list_del_init(&msta->poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);
पूर्ण

अटल व्योम mt7915_init_dfs_state(काष्ठा mt7915_phy *phy)
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

पूर्णांक mt7915_set_channel(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	पूर्णांक ret;

	cancel_delayed_work_sync(&phy->mt76->mac_work);

	mutex_lock(&dev->mt76.mutex);
	set_bit(MT76_RESET, &phy->mt76->state);

	mt7915_init_dfs_state(phy);
	mt76_set_channel(phy->mt76);

	अगर (dev->flash_mode) अणु
		ret = mt7915_mcu_apply_tx_dpd(phy);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = mt7915_mcu_set_chan_info(phy, MCU_EXT_CMD(CHANNEL_SWITCH));
	अगर (ret)
		जाओ out;

	mt7915_mac_set_timing(phy);
	ret = mt7915_dfs_init_radar_detector(phy);
	mt7915_mac_cca_stats_reset(phy);

	mt7915_mac_reset_counters(phy);
	phy->noise = 0;

out:
	clear_bit(MT76_RESET, &phy->mt76->state);
	mutex_unlock(&dev->mt76.mutex);

	mt76_txq_schedule_all(phy->mt76);

	अगर (!mt76_tesपंचांगode_enabled(phy->mt76))
		ieee80211_queue_delayed_work(phy->mt76->hw,
					     &phy->mt76->mac_work,
					     MT7915_WATCHDOG_TIME);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7915_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			  काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_sta *msta = sta ? (काष्ठा mt7915_sta *)sta->drv_priv :
				  &mvअगर->sta;
	काष्ठा mt76_wcid *wcid = &msta->wcid;
	u8 *wcid_keyidx = &wcid->hw_key_idx;
	पूर्णांक idx = key->keyidx;
	पूर्णांक err = 0;

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

	mutex_lock(&dev->mt76.mutex);

	अगर (cmd == SET_KEY)
		*wcid_keyidx = idx;
	अन्यथा अगर (idx == *wcid_keyidx)
		*wcid_keyidx = -1;
	अन्यथा
		जाओ out;

	mt76_wcid_key_setup(&dev->mt76, wcid,
			    cmd == SET_KEY ? key : शून्य);

	err = mt7915_mcu_add_key(dev, vअगर, msta, key, cmd);

out:
	mutex_unlock(&dev->mt76.mutex);

	वापस err;
पूर्ण

अटल पूर्णांक mt7915_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	bool band = phy != &dev->phy;
	पूर्णांक ret;

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
		अगर (phy->mt76->test.state != MT76_TM_STATE_OFF) अणु
			mutex_lock(&dev->mt76.mutex);
			mt76_tesपंचांगode_reset(phy->mt76, false);
			mutex_unlock(&dev->mt76.mutex);
		पूर्ण
#पूर्ण_अगर
		ieee80211_stop_queues(hw);
		ret = mt7915_set_channel(phy);
		अगर (ret)
			वापस ret;
		ieee80211_wake_queues(hw);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		ret = mt7915_mcu_set_txघातer_sku(phy);
		अगर (ret)
			वापस ret;
	पूर्ण

	mutex_lock(&dev->mt76.mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		bool enabled = !!(hw->conf.flags & IEEE80211_CONF_MONITOR);

		अगर (!enabled)
			phy->rxfilter |= MT_WF_RFCR_DROP_OTHER_UC;
		अन्यथा
			phy->rxfilter &= ~MT_WF_RFCR_DROP_OTHER_UC;

		mt76_rmw_field(dev, MT_DMA_DCR0(band), MT_DMA_DCR0_RXD_G5_EN,
			       enabled);
		mt76_tesपंचांगode_reset(phy->mt76, true);
		mt76_wr(dev, MT_WF_RFCR(band), phy->rxfilter);
	पूर्ण

	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7915_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर, u16 queue,
	       स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;

	/* no need to update right away, we'll get BSS_CHANGED_QOS */
	queue = mt7915_lmac_mapping(dev, queue);
	mvअगर->queue_params[queue] = *params;

	वापस 0;
पूर्ण

अटल व्योम mt7915_configure_filter(काष्ठा ieee80211_hw *hw,
				    अचिन्हित पूर्णांक changed_flags,
				    अचिन्हित पूर्णांक *total_flags,
				    u64 multicast)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	bool band = phy != &dev->phy;
	u32 ctl_flags = MT_WF_RFCR1_DROP_ACK |
			MT_WF_RFCR1_DROP_BF_POLL |
			MT_WF_RFCR1_DROP_BA |
			MT_WF_RFCR1_DROP_CFEND |
			MT_WF_RFCR1_DROP_CFACK;
	u32 flags = 0;

#घोषणा MT76_FILTER(_flag, _hw) करो अणु					\
		flags |= *total_flags & FIF_##_flag;			\
		phy->rxfilter &= ~(_hw);				\
		phy->rxfilter |= !(flags & FIF_##_flag) * (_hw);	\
	पूर्ण जबतक (0)

	mutex_lock(&dev->mt76.mutex);

	phy->rxfilter &= ~(MT_WF_RFCR_DROP_OTHER_BSS |
			   MT_WF_RFCR_DROP_OTHER_BEACON |
			   MT_WF_RFCR_DROP_FRAME_REPORT |
			   MT_WF_RFCR_DROP_PROBEREQ |
			   MT_WF_RFCR_DROP_MCAST_FILTERED |
			   MT_WF_RFCR_DROP_MCAST |
			   MT_WF_RFCR_DROP_BCAST |
			   MT_WF_RFCR_DROP_DUPLICATE |
			   MT_WF_RFCR_DROP_A2_BSSID |
			   MT_WF_RFCR_DROP_UNWANTED_CTL |
			   MT_WF_RFCR_DROP_STBC_MULTI);

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

	mutex_unlock(&dev->mt76.mutex);
पूर्ण

अटल व्योम mt7915_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *info,
				    u32 changed)
अणु
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);

	mutex_lock(&dev->mt76.mutex);

	/*
	 * station mode uses BSSID to map the wlan entry to a peer,
	 * and then peer references bss_info_rfch to set bandwidth cap.
	 */
	अगर (changed & BSS_CHANGED_BSSID &&
	    vअगर->type == NL80211_IFTYPE_STATION) अणु
		bool join = !is_zero_ether_addr(info->bssid);

		mt7915_mcu_add_bss_info(phy, vअगर, join);
		mt7915_mcu_add_sta(dev, vअगर, शून्य, join);
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		mt7915_mcu_add_bss_info(phy, vअगर, info->assoc);
		mt7915_mcu_add_obss_spr(dev, vअगर, info->he_obss_pd.enable);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		पूर्णांक slotसमय = info->use_लघु_slot ? 9 : 20;

		अगर (slotसमय != phy->slotसमय) अणु
			phy->slotसमय = slotसमय;
			mt7915_mac_set_timing(phy);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED && info->enable_beacon) अणु
		mt7915_mcu_add_bss_info(phy, vअगर, true);
		mt7915_mcu_add_sta(dev, vअगर, शून्य, true);
	पूर्ण

	/* ensure that enable txcmd_mode after bss_info */
	अगर (changed & (BSS_CHANGED_QOS | BSS_CHANGED_BEACON_ENABLED))
		mt7915_mcu_set_tx(dev, vअगर);

	अगर (changed & BSS_CHANGED_HE_OBSS_PD)
		mt7915_mcu_add_obss_spr(dev, vअगर, info->he_obss_pd.enable);

	अगर (changed & (BSS_CHANGED_BEACON |
		       BSS_CHANGED_BEACON_ENABLED))
		mt7915_mcu_add_beacon(hw, vअगर, info->enable_beacon);

	mutex_unlock(&dev->mt76.mutex);
पूर्ण

अटल व्योम
mt7915_channel_चयन_beacon(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);

	mutex_lock(&dev->mt76.mutex);
	mt7915_mcu_add_beacon(hw, vअगर, true);
	mutex_unlock(&dev->mt76.mutex);
पूर्ण

पूर्णांक mt7915_mac_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	पूर्णांक ret, idx;

	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7915_WTBL_STA - 1);
	अगर (idx < 0)
		वापस -ENOSPC;

	INIT_LIST_HEAD(&msta->rc_list);
	INIT_LIST_HEAD(&msta->stats_list);
	INIT_LIST_HEAD(&msta->poll_list);
	msta->vअगर = mvअगर;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.ext_phy = mvअगर->band_idx;
	msta->wcid.tx_info |= MT_WCID_TX_INFO_SET;
	msta->stats.jअगरfies = jअगरfies;

	mt7915_mac_wtbl_update(dev, idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	ret = mt7915_mcu_add_sta(dev, vअगर, sta, true);
	अगर (ret)
		वापस ret;

	वापस mt7915_mcu_add_sta_adv(dev, vअगर, sta, true);
पूर्ण

व्योम mt7915_mac_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;

	mt7915_mcu_add_sta_adv(dev, vअगर, sta, false);
	mt7915_mcu_add_sta(dev, vअगर, sta, false);

	mt7915_mac_wtbl_update(dev, msta->wcid.idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (!list_empty(&msta->poll_list))
		list_del_init(&msta->poll_list);
	अगर (!list_empty(&msta->stats_list))
		list_del_init(&msta->stats_list);
	अगर (!list_empty(&msta->rc_list))
		list_del_init(&msta->rc_list);
	spin_unlock_bh(&dev->sta_poll_lock);
पूर्ण

अटल व्योम mt7915_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_tx_control *control,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt76_wcid *wcid = &dev->mt76.global_wcid;

	अगर (control->sta) अणु
		काष्ठा mt7915_sta *sta;

		sta = (काष्ठा mt7915_sta *)control->sta->drv_priv;
		wcid = &sta->wcid;
	पूर्ण

	अगर (vअगर && !control->sta) अणु
		काष्ठा mt7915_vअगर *mvअगर;

		mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
		wcid = &mvअगर->sta.wcid;
	पूर्ण

	mt76_tx(mphy, control->sta, wcid, skb);
पूर्ण

अटल पूर्णांक mt7915_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 val)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	पूर्णांक ret;

	mutex_lock(&dev->mt76.mutex);
	ret = mt7915_mcu_set_rts_thresh(phy, val);
	mutex_unlock(&dev->mt76.mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7915_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_ampdu_params *params)
अणु
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा ieee80211_sta *sta = params->sta;
	काष्ठा ieee80211_txq *txq = sta->txq[params->tid];
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	u16 tid = params->tid;
	u16 ssn = params->ssn;
	काष्ठा mt76_txq *mtxq;
	पूर्णांक ret = 0;

	अगर (!txq)
		वापस -EINVAL;

	mtxq = (काष्ठा mt76_txq *)txq->drv_priv;

	mutex_lock(&dev->mt76.mutex);
	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		mt76_rx_aggr_start(&dev->mt76, &msta->wcid, tid, ssn,
				   params->buf_size);
		ret = mt7915_mcu_add_rx_ba(dev, params, true);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		mt76_rx_aggr_stop(&dev->mt76, &msta->wcid, tid);
		ret = mt7915_mcu_add_rx_ba(dev, params, false);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		mtxq->aggr = true;
		mtxq->send_bar = false;
		ret = mt7915_mcu_add_tx_ba(dev, params, true);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		mtxq->aggr = false;
		clear_bit(tid, &msta->ampdu_state);
		ret = mt7915_mcu_add_tx_ba(dev, params, false);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		set_bit(tid, &msta->ampdu_state);
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggr = false;
		clear_bit(tid, &msta->ampdu_state);
		ret = mt7915_mcu_add_tx_ba(dev, params, false);
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	पूर्ण
	mutex_unlock(&dev->mt76.mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7915_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       काष्ठा ieee80211_sta *sta)
अणु
	वापस mt76_sta_state(hw, vअगर, sta, IEEE80211_STA_NOTEXIST,
			      IEEE80211_STA_NONE);
पूर्ण

अटल पूर्णांक
mt7915_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_sta *sta)
अणु
	वापस mt76_sta_state(hw, vअगर, sta, IEEE80211_STA_NONE,
			      IEEE80211_STA_NOTEXIST);
पूर्ण

अटल पूर्णांक
mt7915_get_stats(काष्ठा ieee80211_hw *hw,
		 काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mib_stats *mib = &phy->mib;

	mutex_lock(&dev->mt76.mutex);
	stats->करोt11RTSSuccessCount = mib->rts_cnt;
	stats->करोt11RTSFailureCount = mib->rts_retries_cnt;
	stats->करोt11FCSErrorCount = mib->fcs_err_cnt;
	stats->करोt11ACKFailureCount = mib->ack_fail_cnt;

	स_रखो(mib, 0, माप(*mib));

	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण

अटल u64
mt7915_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	bool band = phy != &dev->phy;
	जोड़ अणु
		u64 t64;
		u32 t32[2];
	पूर्ण tsf;
	u16 n;

	mutex_lock(&dev->mt76.mutex);

	n = mvअगर->omac_idx > HW_BSSID_MAX ? HW_BSSID_0 : mvअगर->omac_idx;
	/* TSF software पढ़ो */
	mt76_set(dev, MT_LPON_TCR(band, n), MT_LPON_TCR_SW_MODE);
	tsf.t32[0] = mt76_rr(dev, MT_LPON_UTTR0(band));
	tsf.t32[1] = mt76_rr(dev, MT_LPON_UTTR1(band));

	mutex_unlock(&dev->mt76.mutex);

	वापस tsf.t64;
पूर्ण

अटल व्योम
mt7915_set_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       u64 बारtamp)
अणु
	काष्ठा mt7915_vअगर *mvअगर = (काष्ठा mt7915_vअगर *)vअगर->drv_priv;
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	bool band = phy != &dev->phy;
	जोड़ अणु
		u64 t64;
		u32 t32[2];
	पूर्ण tsf = अणु .t64 = बारtamp, पूर्ण;
	u16 n;

	mutex_lock(&dev->mt76.mutex);

	n = mvअगर->omac_idx > HW_BSSID_MAX ? HW_BSSID_0 : mvअगर->omac_idx;
	mt76_wr(dev, MT_LPON_UTTR0(band), tsf.t32[0]);
	mt76_wr(dev, MT_LPON_UTTR1(band), tsf.t32[1]);
	/* TSF software overग_लिखो */
	mt76_set(dev, MT_LPON_TCR(band, n), MT_LPON_TCR_SW_WRITE);

	mutex_unlock(&dev->mt76.mutex);
पूर्ण

अटल व्योम
mt7915_set_coverage_class(काष्ठा ieee80211_hw *hw, s16 coverage_class)
अणु
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	काष्ठा mt7915_dev *dev = phy->dev;

	mutex_lock(&dev->mt76.mutex);
	phy->coverage_class = max_t(s16, coverage_class, 0);
	mt7915_mac_set_timing(phy);
	mutex_unlock(&dev->mt76.mutex);
पूर्ण

अटल पूर्णांक
mt7915_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	पूर्णांक max_nss = hweight8(hw->wiphy->available_antennas_tx);
	bool ext_phy = phy != &dev->phy;

	अगर (!tx_ant || tx_ant != rx_ant || ffs(tx_ant) > max_nss)
		वापस -EINVAL;

	अगर ((BIT(hweight8(tx_ant)) - 1) != tx_ant)
		tx_ant = BIT(ffs(tx_ant) - 1) - 1;

	mutex_lock(&dev->mt76.mutex);

	phy->mt76->antenna_mask = tx_ant;

	अगर (ext_phy) अणु
		अगर (dev->chainmask == 0xf)
			tx_ant <<= 2;
		अन्यथा
			tx_ant <<= 1;
	पूर्ण
	phy->mt76->chainmask = tx_ant;

	mt76_set_stream_caps(phy->mt76, true);
	mt7915_set_stream_vht_txbf_caps(phy);
	mt7915_set_stream_he_caps(phy);

	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण

अटल व्योम mt7915_sta_statistics(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा station_info *sinfo)
अणु
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा mt7915_sta_stats *stats = &msta->stats;
	काष्ठा rate_info rxrate = अणुपूर्ण;

	अगर (!mt7915_mcu_get_rx_rate(phy, vअगर, sta, &rxrate)) अणु
		sinfo->rxrate = rxrate;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BITRATE);
	पूर्ण

	अगर (!stats->tx_rate.legacy && !stats->tx_rate.flags)
		वापस;

	अगर (stats->tx_rate.legacy) अणु
		sinfo->txrate.legacy = stats->tx_rate.legacy;
	पूर्ण अन्यथा अणु
		sinfo->txrate.mcs = stats->tx_rate.mcs;
		sinfo->txrate.nss = stats->tx_rate.nss;
		sinfo->txrate.bw = stats->tx_rate.bw;
		sinfo->txrate.he_gi = stats->tx_rate.he_gi;
		sinfo->txrate.he_dcm = stats->tx_rate.he_dcm;
		sinfo->txrate.he_ru_alloc = stats->tx_rate.he_ru_alloc;
	पूर्ण
	sinfo->txrate.flags = stats->tx_rate.flags;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
पूर्ण

अटल व्योम
mt7915_sta_rc_update(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_vअगर *vअगर,
		     काष्ठा ieee80211_sta *sta,
		     u32 changed)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;

	spin_lock_bh(&dev->sta_poll_lock);
	msta->stats.changed |= changed;
	अगर (list_empty(&msta->rc_list))
		list_add_tail(&msta->rc_list, &dev->sta_rc_list);
	spin_unlock_bh(&dev->sta_poll_lock);

	ieee80211_queue_work(hw, &dev->rc_work);
पूर्ण

अटल व्योम mt7915_sta_set_4addr(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta,
				 bool enabled)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;

	अगर (enabled)
		set_bit(MT_WCID_FLAG_4ADDR, &msta->wcid.flags);
	अन्यथा
		clear_bit(MT_WCID_FLAG_4ADDR, &msta->wcid.flags);

	mt7915_mcu_sta_update_hdr_trans(dev, vअगर, sta);
पूर्ण

अटल व्योम mt7915_sta_set_decap_offload(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta,
				 bool enabled)
अणु
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;

	अगर (enabled)
		set_bit(MT_WCID_FLAG_HDR_TRANS, &msta->wcid.flags);
	अन्यथा
		clear_bit(MT_WCID_FLAG_HDR_TRANS, &msta->wcid.flags);

	mt7915_mcu_sta_update_hdr_trans(dev, vअगर, sta);
पूर्ण

स्थिर काष्ठा ieee80211_ops mt7915_ops = अणु
	.tx = mt7915_tx,
	.start = mt7915_start,
	.stop = mt7915_stop,
	.add_पूर्णांकerface = mt7915_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = mt7915_हटाओ_पूर्णांकerface,
	.config = mt7915_config,
	.conf_tx = mt7915_conf_tx,
	.configure_filter = mt7915_configure_filter,
	.bss_info_changed = mt7915_bss_info_changed,
	.sta_add = mt7915_sta_add,
	.sta_हटाओ = mt7915_sta_हटाओ,
	.sta_pre_rcu_हटाओ = mt76_sta_pre_rcu_हटाओ,
	.sta_rc_update = mt7915_sta_rc_update,
	.set_key = mt7915_set_key,
	.ampdu_action = mt7915_ampdu_action,
	.set_rts_threshold = mt7915_set_rts_threshold,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sw_scan_start = mt76_sw_scan,
	.sw_scan_complete = mt76_sw_scan_complete,
	.release_buffered_frames = mt76_release_buffered_frames,
	.get_txघातer = mt76_get_txघातer,
	.channel_चयन_beacon = mt7915_channel_चयन_beacon,
	.get_stats = mt7915_get_stats,
	.get_tsf = mt7915_get_tsf,
	.set_tsf = mt7915_set_tsf,
	.get_survey = mt76_get_survey,
	.get_antenna = mt76_get_antenna,
	.set_antenna = mt7915_set_antenna,
	.set_coverage_class = mt7915_set_coverage_class,
	.sta_statistics = mt7915_sta_statistics,
	.sta_set_4addr = mt7915_sta_set_4addr,
	.sta_set_decap_offload = mt7915_sta_set_decap_offload,
	CFG80211_TESTMODE_CMD(mt76_tesपंचांगode_cmd)
	CFG80211_TESTMODE_DUMP(mt76_tesपंचांगode_dump)
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	.sta_add_debugfs = mt7915_sta_add_debugfs,
#पूर्ण_अगर
पूर्ण;
