<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/etherdevice.h>
#समावेश "mt7921.h"
#समावेश "mac.h"
#समावेश "mcu.h"
#समावेश "eeprom.h"

#घोषणा CCK_RATE(_idx, _rate) अणु						\
	.bitrate = _rate,						\
	.flags = IEEE80211_RATE_SHORT_PREAMBLE,				\
	.hw_value = (MT_PHY_TYPE_CCK << 8) | (_idx),			\
	.hw_value_लघु = (MT_PHY_TYPE_CCK << 8) | (4 + (_idx)),	\
पूर्ण

#घोषणा OFDM_RATE(_idx, _rate) अणु					\
	.bitrate = _rate,						\
	.hw_value = (MT_PHY_TYPE_OFDM << 8) | (_idx),			\
	.hw_value_लघु = (MT_PHY_TYPE_OFDM << 8) | (_idx),		\
पूर्ण

अटल काष्ठा ieee80211_rate mt7921_rates[] = अणु
	CCK_RATE(0, 10),
	CCK_RATE(1, 20),
	CCK_RATE(2, 55),
	CCK_RATE(3, 110),
	OFDM_RATE(11, 60),
	OFDM_RATE(15, 90),
	OFDM_RATE(10, 120),
	OFDM_RATE(14, 180),
	OFDM_RATE(9,  240),
	OFDM_RATE(13, 360),
	OFDM_RATE(8,  480),
	OFDM_RATE(12, 540),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit अगर_limits[] = अणु
	अणु
		.max = MT7921_MAX_INTERFACES,
		.types = BIT(NL80211_IFTYPE_STATION)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb[] = अणु
	अणु
		.limits = अगर_limits,
		.n_limits = ARRAY_SIZE(अगर_limits),
		.max_पूर्णांकerfaces = MT7921_MAX_INTERFACES,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
	पूर्ण
पूर्ण;

अटल व्योम
mt7921_regd_notअगरier(काष्ठा wiphy *wiphy,
		     काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);

	स_नकल(dev->mt76.alpha2, request->alpha2, माप(dev->mt76.alpha2));
	dev->mt76.region = request->dfs_region;

	mt7921_mutex_acquire(dev);
	mt76_connac_mcu_set_channel_करोमुख्य(hw->priv);
	mt76_connac_mcu_set_rate_txघातer(phy->mt76);
	mt7921_mutex_release(dev);
पूर्ण

अटल व्योम
mt7921_init_wiphy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	काष्ठा wiphy *wiphy = hw->wiphy;

	hw->queues = 4;
	hw->max_rx_aggregation_subframes = 64;
	hw->max_tx_aggregation_subframes = 128;

	hw->radiotap_बारtamp.units_pos =
		IEEE80211_RADIOTAP_TIMESTAMP_UNIT_US;

	phy->slotसमय = 9;

	hw->sta_data_size = माप(काष्ठा mt7921_sta);
	hw->vअगर_data_size = माप(काष्ठा mt7921_vअगर);

	wiphy->अगरace_combinations = अगर_comb;
	wiphy->n_अगरace_combinations = ARRAY_SIZE(अगर_comb);
	wiphy->max_scan_ie_len = MT76_CONNAC_SCAN_IE_LEN;
	wiphy->max_scan_ssids = 4;
	wiphy->max_sched_scan_plan_पूर्णांकerval =
		MT76_CONNAC_MAX_SCHED_SCAN_INTERVAL;
	wiphy->max_sched_scan_ie_len = IEEE80211_MAX_DATA_LEN;
	wiphy->max_sched_scan_ssids = MT76_CONNAC_MAX_SCHED_SCAN_SSID;
	wiphy->max_match_sets = MT76_CONNAC_MAX_SCAN_MATCH;
	wiphy->max_sched_scan_reqs = 1;
	wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;
	wiphy->reg_notअगरier = mt7921_regd_notअगरier;

	wiphy->features |= NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;
	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_SET_SCAN_DWELL);

	ieee80211_hw_set(hw, SINGLE_SCAN_ON_ALL_BANDS);
	ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(hw, SUPPORTS_TX_ENCAP_OFFLOAD);
	ieee80211_hw_set(hw, WANT_MONITOR_VIF);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);

	hw->max_tx_fragments = 4;
पूर्ण

अटल व्योम
mt7921_mac_init_band(काष्ठा mt7921_dev *dev, u8 band)
अणु
	u32 mask, set;

	mt76_rmw_field(dev, MT_TMAC_CTCR0(band),
		       MT_TMAC_CTCR0_INS_DDLMT_REFTIME, 0x3f);
	mt76_set(dev, MT_TMAC_CTCR0(band),
		 MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCR0_INS_DDLMT_EN);

	mask = MT_MDP_RCFR0_MCU_RX_MGMT |
	       MT_MDP_RCFR0_MCU_RX_CTL_NON_BAR |
	       MT_MDP_RCFR0_MCU_RX_CTL_BAR;
	set = FIELD_PREP(MT_MDP_RCFR0_MCU_RX_MGMT, MT_MDP_TO_HIF) |
	      FIELD_PREP(MT_MDP_RCFR0_MCU_RX_CTL_NON_BAR, MT_MDP_TO_HIF) |
	      FIELD_PREP(MT_MDP_RCFR0_MCU_RX_CTL_BAR, MT_MDP_TO_HIF);
	mt76_rmw(dev, MT_MDP_BNRCFR0(band), mask, set);

	mask = MT_MDP_RCFR1_MCU_RX_BYPASS |
	       MT_MDP_RCFR1_RX_DROPPED_UCAST |
	       MT_MDP_RCFR1_RX_DROPPED_MCAST;
	set = FIELD_PREP(MT_MDP_RCFR1_MCU_RX_BYPASS, MT_MDP_TO_HIF) |
	      FIELD_PREP(MT_MDP_RCFR1_RX_DROPPED_UCAST, MT_MDP_TO_HIF) |
	      FIELD_PREP(MT_MDP_RCFR1_RX_DROPPED_MCAST, MT_MDP_TO_HIF);
	mt76_rmw(dev, MT_MDP_BNRCFR1(band), mask, set);

	mt76_set(dev, MT_WF_RMAC_MIB_TIME0(band), MT_WF_RMAC_MIB_RXTIME_EN);
	mt76_set(dev, MT_WF_RMAC_MIB_AIRTIME0(band), MT_WF_RMAC_MIB_RXTIME_EN);

	mt76_rmw_field(dev, MT_DMA_DCR0(band), MT_DMA_DCR0_MAX_RX_LEN, 1536);
	/* disable rx rate report by शेष due to hw issues */
	mt76_clear(dev, MT_DMA_DCR0(band), MT_DMA_DCR0_RXD_G5_EN);
पूर्ण

व्योम mt7921_mac_init(काष्ठा mt7921_dev *dev)
अणु
	पूर्णांक i;

	mt76_rmw_field(dev, MT_MDP_DCR1, MT_MDP_DCR1_MAX_RX_LEN, 1536);
	/* disable hardware de-agg */
	mt76_clear(dev, MT_MDP_DCR0, MT_MDP_DCR0_DAMSDU_EN);
	mt76_clear(dev, MT_MDP_DCR0, MT_MDP_DCR0_RX_HDR_TRANS_EN);

	क्रम (i = 0; i < MT7921_WTBL_SIZE; i++)
		mt7921_mac_wtbl_update(dev, i,
				       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
	क्रम (i = 0; i < 2; i++)
		mt7921_mac_init_band(dev, i);

	mt76_connac_mcu_set_rts_thresh(&dev->mt76, 0x92b, 0);
पूर्ण

अटल पूर्णांक mt7921_init_hardware(काष्ठा mt7921_dev *dev)
अणु
	पूर्णांक ret, idx;

	ret = mt7921_dma_init(dev);
	अगर (ret)
		वापस ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	/* क्रमce firmware operation mode पूर्णांकo normal state,
	 * which should be set beक्रमe firmware करोwnload stage.
	 */
	mt76_wr(dev, MT_SWDEF_MODE, MT_SWDEF_NORMAL_MODE);

	ret = mt7921_mcu_init(dev);
	अगर (ret)
		वापस ret;

	ret = mt7921_eeprom_init(dev);
	अगर (ret < 0)
		वापस ret;

	ret = mt7921_mcu_set_eeprom(dev);
	अगर (ret)
		वापस ret;

	/* Beacon and mgmt frames should occupy wcid 0 */
	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7921_WTBL_STA - 1);
	अगर (idx)
		वापस -ENOSPC;

	dev->mt76.global_wcid.idx = idx;
	dev->mt76.global_wcid.hw_key_idx = -1;
	dev->mt76.global_wcid.tx_info |= MT_WCID_TX_INFO_SET;
	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], &dev->mt76.global_wcid);

	mt7921_mac_init(dev);

	वापस 0;
पूर्ण

पूर्णांक mt7921_रेजिस्टर_device(काष्ठा mt7921_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	पूर्णांक ret;

	dev->phy.dev = dev;
	dev->phy.mt76 = &dev->mt76.phy;
	dev->mt76.phy.priv = &dev->phy;
	dev->mt76.tx_worker.fn = mt7921_tx_worker;

	INIT_DELAYED_WORK(&dev->pm.ps_work, mt7921_pm_घातer_save_work);
	INIT_WORK(&dev->pm.wake_work, mt7921_pm_wake_work);
	spin_lock_init(&dev->pm.wake.lock);
	mutex_init(&dev->pm.mutex);
	init_रुकोqueue_head(&dev->pm.रुको);
	spin_lock_init(&dev->pm.txq_lock);
	set_bit(MT76_STATE_PM, &dev->mphy.state);
	INIT_LIST_HEAD(&dev->phy.stats_list);
	INIT_DELAYED_WORK(&dev->mphy.mac_work, mt7921_mac_work);
	INIT_DELAYED_WORK(&dev->phy.scan_work, mt7921_scan_work);
	INIT_DELAYED_WORK(&dev->coredump.work, mt7921_coredump_work);
	skb_queue_head_init(&dev->phy.scan_event_list);
	skb_queue_head_init(&dev->coredump.msg_list);
	INIT_LIST_HEAD(&dev->sta_poll_list);
	spin_lock_init(&dev->sta_poll_lock);

	INIT_WORK(&dev->reset_work, mt7921_mac_reset_work);

	dev->pm.idle_समयout = MT7921_PM_TIMEOUT;
	dev->pm.stats.last_wake_event = jअगरfies;
	dev->pm.stats.last_करोze_event = jअगरfies;

	ret = mt7921_init_hardware(dev);
	अगर (ret)
		वापस ret;

	mt7921_init_wiphy(hw);
	dev->mphy.sband_2g.sband.ht_cap.cap |=
			IEEE80211_HT_CAP_LDPC_CODING |
			IEEE80211_HT_CAP_MAX_AMSDU;
	dev->mphy.sband_5g.sband.ht_cap.cap |=
			IEEE80211_HT_CAP_LDPC_CODING |
			IEEE80211_HT_CAP_MAX_AMSDU;
	dev->mphy.sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991 |
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
	dev->mphy.hw->wiphy->available_antennas_rx = dev->mphy.chainmask;
	dev->mphy.hw->wiphy->available_antennas_tx = dev->mphy.chainmask;

	mt76_set_stream_caps(&dev->mphy, true);
	mt7921_set_stream_he_caps(&dev->phy);

	ret = mt76_रेजिस्टर_device(&dev->mt76, true, mt7921_rates,
				   ARRAY_SIZE(mt7921_rates));
	अगर (ret)
		वापस ret;

	वापस mt7921_init_debugfs(dev);
पूर्ण

व्योम mt7921_unरेजिस्टर_device(काष्ठा mt7921_dev *dev)
अणु
	mt76_unरेजिस्टर_device(&dev->mt76);
	mt7921_tx_token_put(dev);
	mt7921_dma_cleanup(dev);
	mt7921_mcu_निकास(dev);

	tasklet_disable(&dev->irq_tasklet);
	mt76_मुक्त_device(&dev->mt76);
पूर्ण
