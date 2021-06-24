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
#समावेश "mt7615.h"
#समावेश "mac.h"
#समावेश "mcu.h"
#समावेश "eeprom.h"

अटल व्योम
mt7615_phy_init(काष्ठा mt7615_dev *dev)
अणु
	/* disable rf low घातer beacon mode */
	mt76_set(dev, MT_WF_PHY_WF2_RFCTRL0(0), MT_WF_PHY_WF2_RFCTRL0_LPBCN_EN);
	mt76_set(dev, MT_WF_PHY_WF2_RFCTRL0(1), MT_WF_PHY_WF2_RFCTRL0_LPBCN_EN);
पूर्ण

अटल व्योम
mt7615_init_mac_chain(काष्ठा mt7615_dev *dev, पूर्णांक chain)
अणु
	u32 val;

	अगर (!chain)
		val = MT_CFG_CCR_MAC_D0_1X_GC_EN | MT_CFG_CCR_MAC_D0_2X_GC_EN;
	अन्यथा
		val = MT_CFG_CCR_MAC_D1_1X_GC_EN | MT_CFG_CCR_MAC_D1_2X_GC_EN;

	/* enable band 0/1 clk */
	mt76_set(dev, MT_CFG_CCR, val);

	mt76_rmw(dev, MT_TMAC_TRCR(chain),
		 MT_TMAC_TRCR_CCA_SEL | MT_TMAC_TRCR_SEC_CCA_SEL,
		 FIELD_PREP(MT_TMAC_TRCR_CCA_SEL, 2) |
		 FIELD_PREP(MT_TMAC_TRCR_SEC_CCA_SEL, 0));

	mt76_wr(dev, MT_AGG_ACR(chain),
		MT_AGG_ACR_PKT_TIME_EN | MT_AGG_ACR_NO_BA_AR_RULE |
		FIELD_PREP(MT_AGG_ACR_CFEND_RATE, MT7615_CFEND_RATE_DEFAULT) |
		FIELD_PREP(MT_AGG_ACR_BAR_RATE, MT7615_BAR_RATE_DEFAULT));

	mt76_wr(dev, MT_AGG_ARUCR(chain),
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(0), 7) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(1), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(2), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(3), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(4), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(5), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(6), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(7), 1));

	mt76_wr(dev, MT_AGG_ARDCR(chain),
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(0), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(1), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(2), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(3), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(4), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(5), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(6), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(7), MT7615_RATE_RETRY - 1));

	mt76_clear(dev, MT_DMA_RCFR0(chain), MT_DMA_RCFR0_MCU_RX_TDLS);
	अगर (!mt7615_firmware_offload(dev)) अणु
		u32 mask, set;

		mask = MT_DMA_RCFR0_MCU_RX_MGMT |
		       MT_DMA_RCFR0_MCU_RX_CTL_NON_BAR |
		       MT_DMA_RCFR0_MCU_RX_CTL_BAR |
		       MT_DMA_RCFR0_MCU_RX_BYPASS |
		       MT_DMA_RCFR0_RX_DROPPED_UCAST |
		       MT_DMA_RCFR0_RX_DROPPED_MCAST;
		set = FIELD_PREP(MT_DMA_RCFR0_RX_DROPPED_UCAST, 2) |
		      FIELD_PREP(MT_DMA_RCFR0_RX_DROPPED_MCAST, 2);
		mt76_rmw(dev, MT_DMA_RCFR0(chain), mask, set);
	पूर्ण
पूर्ण

अटल व्योम
mt7615_mac_init(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक i;

	mt7615_init_mac_chain(dev, 0);

	mt76_rmw_field(dev, MT_TMAC_CTCR0,
		       MT_TMAC_CTCR0_INS_DDLMT_REFTIME, 0x3f);
	mt76_rmw_field(dev, MT_TMAC_CTCR0,
		       MT_TMAC_CTCR0_INS_DDLMT_DENSITY, 0x3);
	mt76_rmw(dev, MT_TMAC_CTCR0,
		 MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCR0_INS_DDLMT_EN,
		 MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCR0_INS_DDLMT_EN);

	mt76_connac_mcu_set_rts_thresh(&dev->mt76, 0x92b, 0);
	mt7615_mac_set_scs(&dev->phy, true);

	mt76_rmw(dev, MT_AGG_SCR, MT_AGG_SCR_NLNAV_MID_PTEC_DIS,
		 MT_AGG_SCR_NLNAV_MID_PTEC_DIS);

	mt76_wr(dev, MT_AGG_ARCR,
		FIELD_PREP(MT_AGG_ARCR_RTS_RATE_THR, 2) |
		MT_AGG_ARCR_RATE_DOWN_RATIO_EN |
		FIELD_PREP(MT_AGG_ARCR_RATE_DOWN_RATIO, 1) |
		FIELD_PREP(MT_AGG_ARCR_RATE_UP_EXTRA_TH, 4));

	क्रम (i = 0; i < MT7615_WTBL_SIZE; i++)
		mt7615_mac_wtbl_update(dev, i,
				       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	mt76_set(dev, MT_WF_RMAC_MIB_TIME0, MT_WF_RMAC_MIB_RXTIME_EN);
	mt76_set(dev, MT_WF_RMAC_MIB_AIRTIME0, MT_WF_RMAC_MIB_RXTIME_EN);

	mt76_wr(dev, MT_DMA_DCR0,
		FIELD_PREP(MT_DMA_DCR0_MAX_RX_LEN, 3072) |
		MT_DMA_DCR0_RX_VEC_DROP | MT_DMA_DCR0_DAMSDU_EN |
		MT_DMA_DCR0_RX_HDR_TRANS_EN);
	/* disable TDLS filtering */
	mt76_clear(dev, MT_WF_PFCR, MT_WF_PFCR_TDLS_EN);
	mt76_set(dev, MT_WF_MIB_SCR0, MT_MIB_SCR0_AGG_CNT_RANGE_EN);
	अगर (is_mt7663(&dev->mt76)) अणु
		mt76_wr(dev, MT_WF_AGG(0x160), 0x5c341c02);
		mt76_wr(dev, MT_WF_AGG(0x164), 0x70708040);
	पूर्ण अन्यथा अणु
		mt7615_init_mac_chain(dev, 1);
	पूर्ण
	mt7615_mcu_set_rx_hdr_trans_blacklist(dev);
पूर्ण

अटल व्योम
mt7615_check_offload_capability(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	काष्ठा wiphy *wiphy = hw->wiphy;

	अगर (mt7615_firmware_offload(dev)) अणु
		ieee80211_hw_set(hw, SUPPORTS_PS);
		ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);

		wiphy->max_reमुख्य_on_channel_duration = 5000;
		wiphy->features |= NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR |
				   NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR |
				   WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
				   NL80211_FEATURE_P2P_GO_CTWIN |
				   NL80211_FEATURE_P2P_GO_OPPPS;
	पूर्ण अन्यथा अणु
		dev->ops->hw_scan = शून्य;
		dev->ops->cancel_hw_scan = शून्य;
		dev->ops->sched_scan_start = शून्य;
		dev->ops->sched_scan_stop = शून्य;
		dev->ops->set_rekey_data = शून्य;
		dev->ops->reमुख्य_on_channel = शून्य;
		dev->ops->cancel_reमुख्य_on_channel = शून्य;

		wiphy->max_sched_scan_plan_पूर्णांकerval = 0;
		wiphy->max_sched_scan_ie_len = 0;
		wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;
		wiphy->max_sched_scan_ssids = 0;
		wiphy->max_match_sets = 0;
		wiphy->max_sched_scan_reqs = 0;
	पूर्ण
पूर्ण

bool mt7615_रुको_क्रम_mcu_init(काष्ठा mt7615_dev *dev)
अणु
	flush_work(&dev->mcu_work);

	वापस test_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_रुको_क्रम_mcu_init);

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

काष्ठा ieee80211_rate mt7615_rates[] = अणु
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
EXPORT_SYMBOL_GPL(mt7615_rates);

अटल स्थिर काष्ठा ieee80211_अगरace_limit अगर_limits[] = अणु
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_ADHOC)
	पूर्ण, अणु
		.max = MT7615_MAX_INTERFACES,
		.types = BIT(NL80211_IFTYPE_AP) |
#अगर_घोषित CONFIG_MAC80211_MESH
			 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
			 BIT(NL80211_IFTYPE_P2P_CLIENT) |
			 BIT(NL80211_IFTYPE_P2P_GO) |
			 BIT(NL80211_IFTYPE_STATION)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb_radar[] = अणु
	अणु
		.limits = अगर_limits,
		.n_limits = ARRAY_SIZE(अगर_limits),
		.max_पूर्णांकerfaces = MT7615_MAX_INTERFACES,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
		.radar_detect_widths = BIT(NL80211_CHAN_WIDTH_20_NOHT) |
				       BIT(NL80211_CHAN_WIDTH_20) |
				       BIT(NL80211_CHAN_WIDTH_40) |
				       BIT(NL80211_CHAN_WIDTH_80) |
				       BIT(NL80211_CHAN_WIDTH_160) |
				       BIT(NL80211_CHAN_WIDTH_80P80),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb[] = अणु
	अणु
		.limits = अगर_limits,
		.n_limits = ARRAY_SIZE(अगर_limits),
		.max_पूर्णांकerfaces = MT7615_MAX_INTERFACES,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
	पूर्ण
पूर्ण;

व्योम mt7615_init_txघातer(काष्ठा mt7615_dev *dev,
			 काष्ठा ieee80211_supported_band *sband)
अणु
	पूर्णांक i, n_chains = hweight8(dev->mphy.antenna_mask), target_chains;
	पूर्णांक delta_idx, delta = mt76_tx_घातer_nss_delta(n_chains);
	u8 *eep = (u8 *)dev->mt76.eeprom.data;
	क्रमागत nl80211_band band = sband->band;
	काष्ठा mt76_घातer_limits limits;
	u8 rate_val;

	delta_idx = mt7615_eeprom_get_घातer_delta_index(dev, band);
	rate_val = eep[delta_idx];
	अगर ((rate_val & ~MT_EE_RATE_POWER_MASK) ==
	    (MT_EE_RATE_POWER_EN | MT_EE_RATE_POWER_SIGN))
		delta += rate_val & MT_EE_RATE_POWER_MASK;

	अगर (!is_mt7663(&dev->mt76) && mt7615_ext_pa_enabled(dev, band))
		target_chains = 1;
	अन्यथा
		target_chains = n_chains;

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		काष्ठा ieee80211_channel *chan = &sband->channels[i];
		u8 target_घातer = 0;
		पूर्णांक j;

		क्रम (j = 0; j < target_chains; j++) अणु
			पूर्णांक index;

			index = mt7615_eeprom_get_target_घातer_index(dev, chan, j);
			अगर (index < 0)
				जारी;

			target_घातer = max(target_घातer, eep[index]);
		पूर्ण

		target_घातer = mt76_get_rate_घातer_limits(&dev->mphy, chan,
							  &limits,
							  target_घातer);
		target_घातer += delta;
		target_घातer = DIV_ROUND_UP(target_घातer, 2);
		chan->max_घातer = min_t(पूर्णांक, chan->max_reg_घातer,
					target_घातer);
		chan->orig_mpwr = target_घातer;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_init_txघातer);

व्योम mt7615_init_work(काष्ठा mt7615_dev *dev)
अणु
	mt7615_mcu_set_eeprom(dev);
	mt7615_mac_init(dev);
	mt7615_phy_init(dev);
	mt7615_mcu_del_wtbl_all(dev);
	mt7615_check_offload_capability(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_init_work);

अटल व्योम
mt7615_regd_notअगरier(काष्ठा wiphy *wiphy,
		     काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	काष्ठा mt7615_phy *phy = mphy->priv;
	काष्ठा cfg80211_chan_def *chandef = &mphy->chandef;

	स_नकल(dev->mt76.alpha2, request->alpha2, माप(dev->mt76.alpha2));
	dev->mt76.region = request->dfs_region;

	mt7615_init_txघातer(dev, &mphy->sband_2g.sband);
	mt7615_init_txघातer(dev, &mphy->sband_5g.sband);

	mt7615_mutex_acquire(dev);

	अगर (chandef->chan->flags & IEEE80211_CHAN_RADAR)
		mt7615_dfs_init_radar_detector(phy);

	अगर (mt7615_firmware_offload(phy->dev)) अणु
		mt76_connac_mcu_set_channel_करोमुख्य(mphy);
		mt76_connac_mcu_set_rate_txघातer(mphy);
	पूर्ण

	mt7615_mutex_release(dev);
पूर्ण

अटल व्योम
mt7615_init_wiphy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	काष्ठा wiphy *wiphy = hw->wiphy;

	hw->queues = 4;
	hw->max_rates = 3;
	hw->max_report_rates = 7;
	hw->max_rate_tries = 11;
	hw->netdev_features = NETIF_F_RXCSUM;

	hw->radiotap_बारtamp.units_pos =
		IEEE80211_RADIOTAP_TIMESTAMP_UNIT_US;

	phy->slotसमय = 9;

	hw->sta_data_size = माप(काष्ठा mt7615_sta);
	hw->vअगर_data_size = माप(काष्ठा mt7615_vअगर);

	अगर (is_mt7663(&phy->dev->mt76)) अणु
		wiphy->अगरace_combinations = अगर_comb;
		wiphy->n_अगरace_combinations = ARRAY_SIZE(अगर_comb);
	पूर्ण अन्यथा अणु
		wiphy->अगरace_combinations = अगर_comb_radar;
		wiphy->n_अगरace_combinations = ARRAY_SIZE(अगर_comb_radar);
	पूर्ण
	wiphy->reg_notअगरier = mt7615_regd_notअगरier;

	wiphy->max_sched_scan_plan_पूर्णांकerval =
		MT76_CONNAC_MAX_SCHED_SCAN_INTERVAL;
	wiphy->max_sched_scan_ie_len = IEEE80211_MAX_DATA_LEN;
	wiphy->max_scan_ie_len = MT76_CONNAC_SCAN_IE_LEN;
	wiphy->max_sched_scan_ssids = MT76_CONNAC_MAX_SCHED_SCAN_SSID;
	wiphy->max_match_sets = MT76_CONNAC_MAX_SCAN_MATCH;
	wiphy->max_sched_scan_reqs = 1;
	wiphy->max_scan_ssids = 4;

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_SET_SCAN_DWELL);
	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_VHT_IBSS);

	ieee80211_hw_set(hw, SINGLE_SCAN_ON_ALL_BANDS);
	ieee80211_hw_set(hw, TX_STATUS_NO_AMPDU_LEN);
	ieee80211_hw_set(hw, WANT_MONITOR_VIF);
	ieee80211_hw_set(hw, SUPPORTS_RX_DECAP_OFFLOAD);

	अगर (is_mt7615(&phy->dev->mt76))
		hw->max_tx_fragments = MT_TXP_MAX_BUF_NUM;
	अन्यथा
		hw->max_tx_fragments = MT_HW_TXP_MAX_BUF_NUM;

	phy->mt76->sband_2g.sband.ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;
	phy->mt76->sband_5g.sband.ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;
	phy->mt76->sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
पूर्ण

अटल व्योम
mt7615_cap_dbdc_enable(काष्ठा mt7615_dev *dev)
अणु
	dev->mphy.sband_5g.sband.vht_cap.cap &=
			~(IEEE80211_VHT_CAP_SHORT_GI_160 |
			  IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ);
	अगर (dev->chainmask == 0xf)
		dev->mphy.antenna_mask = dev->chainmask >> 2;
	अन्यथा
		dev->mphy.antenna_mask = dev->chainmask >> 1;
	dev->mphy.chainmask = dev->mphy.antenna_mask;
	dev->mphy.hw->wiphy->available_antennas_rx = dev->mphy.chainmask;
	dev->mphy.hw->wiphy->available_antennas_tx = dev->mphy.chainmask;
	mt76_set_stream_caps(&dev->mphy, true);
पूर्ण

अटल व्योम
mt7615_cap_dbdc_disable(काष्ठा mt7615_dev *dev)
अणु
	dev->mphy.sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_SHORT_GI_160 |
			IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ;
	dev->mphy.antenna_mask = dev->chainmask;
	dev->mphy.chainmask = dev->chainmask;
	dev->mphy.hw->wiphy->available_antennas_rx = dev->chainmask;
	dev->mphy.hw->wiphy->available_antennas_tx = dev->chainmask;
	mt76_set_stream_caps(&dev->mphy, true);
पूर्ण

पूर्णांक mt7615_रेजिस्टर_ext_phy(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt7615_phy *phy = mt7615_ext_phy(dev);
	काष्ठा mt76_phy *mphy;
	पूर्णांक i, ret;

	अगर (!is_mt7615(&dev->mt76))
		वापस -EOPNOTSUPP;

	अगर (test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
		वापस -EINVAL;

	अगर (phy)
		वापस 0;

	mt7615_cap_dbdc_enable(dev);
	mphy = mt76_alloc_phy(&dev->mt76, माप(*phy), &mt7615_ops);
	अगर (!mphy)
		वापस -ENOMEM;

	phy = mphy->priv;
	phy->dev = dev;
	phy->mt76 = mphy;
	mphy->chainmask = dev->chainmask & ~dev->mphy.chainmask;
	mphy->antenna_mask = BIT(hweight8(mphy->chainmask)) - 1;
	mt7615_init_wiphy(mphy->hw);

	INIT_DELAYED_WORK(&mphy->mac_work, mt7615_mac_work);
	INIT_DELAYED_WORK(&phy->scan_work, mt7615_scan_work);
	skb_queue_head_init(&phy->scan_event_list);

	INIT_WORK(&phy->roc_work, mt7615_roc_work);
	समयr_setup(&phy->roc_समयr, mt7615_roc_समयr, 0);
	init_रुकोqueue_head(&phy->roc_रुको);

	mt7615_mac_set_scs(phy, true);

	/*
	 * Make the secondary PHY MAC address local without overlapping with
	 * the usual MAC address allocation scheme on multiple भव पूर्णांकerfaces
	 */
	स_नकल(mphy->macaddr, dev->mt76.eeprom.data + MT_EE_MAC_ADDR,
	       ETH_ALEN);
	mphy->macaddr[0] |= 2;
	mphy->macaddr[0] ^= BIT(7);
	mt76_eeprom_override(mphy);

	/* second phy can only handle 5 GHz */
	mphy->cap.has_5ghz = true;

	/* mt7615 second phy shares the same hw queues with the primary one */
	क्रम (i = 0; i <= MT_TXQ_PSD ; i++)
		mphy->q_tx[i] = dev->mphy.q_tx[i];

	ret = mt76_रेजिस्टर_phy(mphy, true, mt7615_rates,
				ARRAY_SIZE(mt7615_rates));
	अगर (ret)
		ieee80211_मुक्त_hw(mphy->hw);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_रेजिस्टर_ext_phy);

व्योम mt7615_unरेजिस्टर_ext_phy(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt7615_phy *phy = mt7615_ext_phy(dev);
	काष्ठा mt76_phy *mphy = dev->mt76.phy2;

	अगर (!phy)
		वापस;

	mt7615_cap_dbdc_disable(dev);
	mt76_unरेजिस्टर_phy(mphy);
	ieee80211_मुक्त_hw(mphy->hw);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_unरेजिस्टर_ext_phy);

व्योम mt7615_init_device(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);

	dev->phy.dev = dev;
	dev->phy.mt76 = &dev->mt76.phy;
	dev->mt76.phy.priv = &dev->phy;
	dev->mt76.tx_worker.fn = mt7615_tx_worker;

	INIT_DELAYED_WORK(&dev->pm.ps_work, mt7615_pm_घातer_save_work);
	INIT_WORK(&dev->pm.wake_work, mt7615_pm_wake_work);
	spin_lock_init(&dev->pm.wake.lock);
	mutex_init(&dev->pm.mutex);
	init_रुकोqueue_head(&dev->pm.रुको);
	spin_lock_init(&dev->pm.txq_lock);
	INIT_DELAYED_WORK(&dev->mphy.mac_work, mt7615_mac_work);
	INIT_DELAYED_WORK(&dev->phy.scan_work, mt7615_scan_work);
	INIT_DELAYED_WORK(&dev->coredump.work, mt7615_coredump_work);
	skb_queue_head_init(&dev->phy.scan_event_list);
	skb_queue_head_init(&dev->coredump.msg_list);
	INIT_LIST_HEAD(&dev->sta_poll_list);
	spin_lock_init(&dev->sta_poll_lock);
	init_रुकोqueue_head(&dev->reset_रुको);
	init_रुकोqueue_head(&dev->phy.roc_रुको);

	INIT_WORK(&dev->phy.roc_work, mt7615_roc_work);
	समयr_setup(&dev->phy.roc_समयr, mt7615_roc_समयr, 0);

	mt7615_init_wiphy(hw);
	dev->pm.idle_समयout = MT7615_PM_TIMEOUT;
	dev->pm.stats.last_wake_event = jअगरfies;
	dev->pm.stats.last_करोze_event = jअगरfies;
	mt7615_cap_dbdc_disable(dev);
	dev->phy.dfs_state = -1;

#अगर_घोषित CONFIG_NL80211_TESTMODE
	dev->mt76.test_ops = &mt7615_tesपंचांगode_ops;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_init_device);
