<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/etherdevice.h>
#समावेश "mt7915.h"
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

अटल काष्ठा ieee80211_rate mt7915_rates[] = अणु
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
		.max = 1,
		.types = BIT(NL80211_IFTYPE_ADHOC)
	पूर्ण, अणु
		.max = 16,
		.types = BIT(NL80211_IFTYPE_AP)
#अगर_घोषित CONFIG_MAC80211_MESH
			 | BIT(NL80211_IFTYPE_MESH_POINT)
#पूर्ण_अगर
	पूर्ण, अणु
		.max = MT7915_MAX_INTERFACES,
		.types = BIT(NL80211_IFTYPE_STATION)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb[] = अणु
	अणु
		.limits = अगर_limits,
		.n_limits = ARRAY_SIZE(अगर_limits),
		.max_पूर्णांकerfaces = MT7915_MAX_INTERFACES,
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

अटल व्योम
mt7915_init_txघातer(काष्ठा mt7915_dev *dev,
		    काष्ठा ieee80211_supported_band *sband)
अणु
	पूर्णांक i, n_chains = hweight8(dev->mphy.antenna_mask);
	पूर्णांक nss_delta = mt76_tx_घातer_nss_delta(n_chains);
	पूर्णांक pwr_delta = mt7915_eeprom_get_घातer_delta(dev, sband->band);
	काष्ठा mt76_घातer_limits limits;

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		काष्ठा ieee80211_channel *chan = &sband->channels[i];
		u32 target_घातer = 0;
		पूर्णांक j;

		क्रम (j = 0; j < n_chains; j++) अणु
			u32 val;

			val = mt7915_eeprom_get_target_घातer(dev, chan, j);
			target_घातer = max(target_घातer, val);
		पूर्ण

		target_घातer += pwr_delta;
		target_घातer = mt76_get_rate_घातer_limits(&dev->mphy, chan,
							  &limits,
							  target_घातer);
		target_घातer += nss_delta;
		target_घातer = DIV_ROUND_UP(target_घातer, 2);
		chan->max_घातer = min_t(पूर्णांक, chan->max_reg_घातer,
					target_घातer);
		chan->orig_mpwr = target_घातer;
	पूर्ण
पूर्ण

अटल व्योम
mt7915_regd_notअगरier(काष्ठा wiphy *wiphy,
		     काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा mt7915_dev *dev = mt7915_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	काष्ठा mt7915_phy *phy = mphy->priv;
	काष्ठा cfg80211_chan_def *chandef = &mphy->chandef;

	स_नकल(dev->mt76.alpha2, request->alpha2, माप(dev->mt76.alpha2));
	dev->mt76.region = request->dfs_region;

	mt7915_init_txघातer(dev, &mphy->sband_2g.sband);
	mt7915_init_txघातer(dev, &mphy->sband_5g.sband);

	अगर (!(chandef->chan->flags & IEEE80211_CHAN_RADAR))
		वापस;

	mt7915_dfs_init_radar_detector(phy);
पूर्ण

अटल व्योम
mt7915_init_wiphy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7915_phy *phy = mt7915_hw_phy(hw);
	काष्ठा wiphy *wiphy = hw->wiphy;

	hw->queues = 4;
	hw->max_rx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF;
	hw->max_tx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF;
	hw->netdev_features = NETIF_F_RXCSUM;

	hw->radiotap_बारtamp.units_pos =
		IEEE80211_RADIOTAP_TIMESTAMP_UNIT_US;

	phy->slotसमय = 9;

	hw->sta_data_size = माप(काष्ठा mt7915_sta);
	hw->vअगर_data_size = माप(काष्ठा mt7915_vअगर);

	wiphy->अगरace_combinations = अगर_comb;
	wiphy->n_अगरace_combinations = ARRAY_SIZE(अगर_comb);
	wiphy->reg_notअगरier = mt7915_regd_notअगरier;
	wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_VHT_IBSS);

	ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(hw, SUPPORTS_TX_ENCAP_OFFLOAD);
	ieee80211_hw_set(hw, SUPPORTS_RX_DECAP_OFFLOAD);
	ieee80211_hw_set(hw, WANT_MONITOR_VIF);

	hw->max_tx_fragments = 4;

	अगर (phy->mt76->cap.has_2ghz)
		phy->mt76->sband_2g.sband.ht_cap.cap |=
			IEEE80211_HT_CAP_LDPC_CODING |
			IEEE80211_HT_CAP_MAX_AMSDU;

	अगर (phy->mt76->cap.has_5ghz) अणु
		phy->mt76->sband_5g.sband.ht_cap.cap |=
			IEEE80211_HT_CAP_LDPC_CODING |
			IEEE80211_HT_CAP_MAX_AMSDU;
		phy->mt76->sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991 |
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
	पूर्ण

	mt76_set_stream_caps(phy->mt76, true);
	mt7915_set_stream_vht_txbf_caps(phy);
	mt7915_set_stream_he_caps(phy);
पूर्ण

अटल व्योम
mt7915_mac_init_band(काष्ठा mt7915_dev *dev, u8 band)
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

अटल व्योम mt7915_mac_init(काष्ठा mt7915_dev *dev)
अणु
	पूर्णांक i;

	mt76_rmw_field(dev, MT_MDP_DCR1, MT_MDP_DCR1_MAX_RX_LEN, 1536);
	/* enable hardware de-agg */
	mt76_set(dev, MT_MDP_DCR0, MT_MDP_DCR0_DAMSDU_EN);

	क्रम (i = 0; i < MT7915_WTBL_SIZE; i++)
		mt7915_mac_wtbl_update(dev, i,
				       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);
	क्रम (i = 0; i < 2; i++)
		mt7915_mac_init_band(dev, i);
पूर्ण

अटल पूर्णांक mt7915_txbf_init(काष्ठा mt7915_dev *dev)
अणु
	पूर्णांक ret;


	अगर (dev->dbdc_support) अणु
		ret = mt7915_mcu_set_txbf_module(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* trigger sounding packets */
	ret = mt7915_mcu_set_txbf_sounding(dev);
	अगर (ret)
		वापस ret;

	/* enable eBF */
	वापस mt7915_mcu_set_txbf_type(dev);
पूर्ण

अटल पूर्णांक mt7915_रेजिस्टर_ext_phy(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt7915_phy *phy = mt7915_ext_phy(dev);
	काष्ठा mt76_phy *mphy;
	पूर्णांक ret;

	अगर (!dev->dbdc_support)
		वापस 0;

	अगर (phy)
		वापस 0;

	mphy = mt76_alloc_phy(&dev->mt76, माप(*phy), &mt7915_ops);
	अगर (!mphy)
		वापस -ENOMEM;

	phy = mphy->priv;
	phy->dev = dev;
	phy->mt76 = mphy;
	mphy->chainmask = dev->chainmask & ~dev->mphy.chainmask;
	mphy->antenna_mask = BIT(hweight8(mphy->chainmask)) - 1;

	INIT_LIST_HEAD(&phy->stats_list);
	INIT_DELAYED_WORK(&mphy->mac_work, mt7915_mac_work);

	mt7915_eeprom_parse_band_config(phy);
	mt7915_init_wiphy(mphy->hw);

	स_नकल(mphy->macaddr, dev->mt76.eeprom.data + MT_EE_MAC_ADDR2,
	       ETH_ALEN);
	mt76_eeprom_override(mphy);

	ret = mt7915_init_tx_queues(phy, MT7915_TXQ_BAND1,
				    MT7915_TX_RING_SIZE);
	अगर (ret)
		जाओ error;

	ret = mt76_रेजिस्टर_phy(mphy, true, mt7915_rates,
				ARRAY_SIZE(mt7915_rates));
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	ieee80211_मुक्त_hw(mphy->hw);
	वापस ret;
पूर्ण

अटल व्योम mt7915_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7915_dev *dev = container_of(work, काष्ठा mt7915_dev,
				 init_work);

	mt7915_mcu_set_eeprom(dev);
	mt7915_mac_init(dev);
	mt7915_init_txघातer(dev, &dev->mphy.sband_2g.sband);
	mt7915_init_txघातer(dev, &dev->mphy.sband_5g.sband);
	mt7915_txbf_init(dev);
पूर्ण

अटल व्योम mt7915_wfsys_reset(काष्ठा mt7915_dev *dev)
अणु
	u32 val = MT_TOP_PWR_KEY | MT_TOP_PWR_SW_PWR_ON | MT_TOP_PWR_PWR_ON;

#घोषणा MT_MCU_DUMMY_RANDOM	GENMASK(15, 0)
#घोषणा MT_MCU_DUMMY_DEFAULT	GENMASK(31, 16)

	mt76_wr(dev, MT_MCU_WFDMA0_DUMMY_CR, MT_MCU_DUMMY_RANDOM);

	/* change to software control */
	val |= MT_TOP_PWR_SW_RST;
	mt76_wr(dev, MT_TOP_PWR_CTRL, val);

	/* reset wfsys */
	val &= ~MT_TOP_PWR_SW_RST;
	mt76_wr(dev, MT_TOP_PWR_CTRL, val);

	/* release wfsys then mcu re-excutes romcode */
	val |= MT_TOP_PWR_SW_RST;
	mt76_wr(dev, MT_TOP_PWR_CTRL, val);

	/* चयन to hw control */
	val &= ~MT_TOP_PWR_SW_RST;
	val |= MT_TOP_PWR_HW_CTRL;
	mt76_wr(dev, MT_TOP_PWR_CTRL, val);

	/* check whether mcu resets to शेष */
	अगर (!mt76_poll_msec(dev, MT_MCU_WFDMA0_DUMMY_CR, MT_MCU_DUMMY_DEFAULT,
			    MT_MCU_DUMMY_DEFAULT, 1000)) अणु
		dev_err(dev->mt76.dev, "wifi subsystem reset failure\n");
		वापस;
	पूर्ण

	/* wfsys reset won't clear host रेजिस्टरs */
	mt76_clear(dev, MT_TOP_MISC, MT_TOP_MISC_FW_STATE);

	msleep(100);
पूर्ण

अटल पूर्णांक mt7915_init_hardware(काष्ठा mt7915_dev *dev)
अणु
	पूर्णांक ret, idx;

	mt76_wr(dev, MT_INT_SOURCE_CSR, ~0);

	INIT_WORK(&dev->init_work, mt7915_init_work);
	dev->dbdc_support = !!(mt76_rr(dev, MT_HW_BOUND) & BIT(5));

	/* If MCU was alपढ़ोy running, it is likely in a bad state */
	अगर (mt76_get_field(dev, MT_TOP_MISC, MT_TOP_MISC_FW_STATE) >
	    FW_STATE_FW_DOWNLOAD)
		mt7915_wfsys_reset(dev);

	ret = mt7915_dma_init(dev);
	अगर (ret)
		वापस ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	/*
	 * क्रमce firmware operation mode पूर्णांकo normal state,
	 * which should be set beक्रमe firmware करोwnload stage.
	 */
	mt76_wr(dev, MT_SWDEF_MODE, MT_SWDEF_NORMAL_MODE);

	ret = mt7915_mcu_init(dev);
	अगर (ret) अणु
		/* Reset and try again */
		mt7915_wfsys_reset(dev);

		ret = mt7915_mcu_init(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mt7915_eeprom_init(dev);
	अगर (ret < 0)
		वापस ret;


	अगर (dev->flash_mode) अणु
		ret = mt7915_mcu_apply_group_cal(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Beacon and mgmt frames should occupy wcid 0 */
	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7915_WTBL_STA - 1);
	अगर (idx)
		वापस -ENOSPC;

	dev->mt76.global_wcid.idx = idx;
	dev->mt76.global_wcid.hw_key_idx = -1;
	dev->mt76.global_wcid.tx_info |= MT_WCID_TX_INFO_SET;
	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], &dev->mt76.global_wcid);

	वापस 0;
पूर्ण

व्योम mt7915_set_stream_vht_txbf_caps(काष्ठा mt7915_phy *phy)
अणु
	पूर्णांक nss;
	u32 *cap;

	अगर (!phy->mt76->cap.has_5ghz)
		वापस;

	nss = hweight8(phy->mt76->chainmask);
	cap = &phy->mt76->sband_5g.sband.vht_cap.cap;

	*cap |= IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
		IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE |
		(3 << IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT);

	*cap &= ~(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK |
		  IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
		  IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE);

	अगर (nss < 2)
		वापस;

	*cap |= IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
		IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE |
		FIELD_PREP(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK,
			   nss - 1);
पूर्ण

अटल व्योम
mt7915_set_stream_he_txbf_caps(काष्ठा ieee80211_sta_he_cap *he_cap,
			       पूर्णांक vअगर, पूर्णांक nss)
अणु
	काष्ठा ieee80211_he_cap_elem *elem = &he_cap->he_cap_elem;
	काष्ठा ieee80211_he_mcs_nss_supp *mcs = &he_cap->he_mcs_nss_supp;
	u8 c;

#अगर_घोषित CONFIG_MAC80211_MESH
	अगर (vअगर == NL80211_IFTYPE_MESH_POINT)
		वापस;
#पूर्ण_अगर

	elem->phy_cap_info[3] &= ~IEEE80211_HE_PHY_CAP3_SU_BEAMFORMER;
	elem->phy_cap_info[4] &= ~IEEE80211_HE_PHY_CAP4_MU_BEAMFORMER;

	c = IEEE80211_HE_PHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_MASK |
	    IEEE80211_HE_PHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK;
	elem->phy_cap_info[5] &= ~c;

	c = IEEE80211_HE_PHY_CAP6_TRIG_SU_BEAMFORMING_FB |
	    IEEE80211_HE_PHY_CAP6_TRIG_MU_BEAMFORMING_PARTIAL_BW_FB;
	elem->phy_cap_info[6] &= ~c;

	elem->phy_cap_info[7] &= ~IEEE80211_HE_PHY_CAP7_MAX_NC_MASK;

	c = IEEE80211_HE_PHY_CAP2_NDP_4x_LTF_AND_3_2US |
	    IEEE80211_HE_PHY_CAP2_UL_MU_FULL_MU_MIMO |
	    IEEE80211_HE_PHY_CAP2_UL_MU_PARTIAL_MU_MIMO;
	elem->phy_cap_info[2] |= c;

	c = IEEE80211_HE_PHY_CAP4_SU_BEAMFORMEE |
	    IEEE80211_HE_PHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_4 |
	    IEEE80211_HE_PHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_4;
	elem->phy_cap_info[4] |= c;

	/* करो not support NG16 due to spec D4.0 changes subcarrier idx */
	c = IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_42_SU |
	    IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_75_MU;

	अगर (vअगर == NL80211_IFTYPE_STATION)
		c |= IEEE80211_HE_PHY_CAP6_PARTIAL_BANDWIDTH_DL_MUMIMO;

	elem->phy_cap_info[6] |= c;

	अगर (nss < 2)
		वापस;

	अगर (vअगर != NL80211_IFTYPE_AP)
		वापस;

	elem->phy_cap_info[3] |= IEEE80211_HE_PHY_CAP3_SU_BEAMFORMER;
	elem->phy_cap_info[4] |= IEEE80211_HE_PHY_CAP4_MU_BEAMFORMER;

	/* num_snd_dim */
	c = (nss - 1) | (max_t(पूर्णांक, le16_to_cpu(mcs->tx_mcs_160), 1) << 3);
	elem->phy_cap_info[5] |= c;

	c = IEEE80211_HE_PHY_CAP6_TRIG_SU_BEAMFORMING_FB |
	    IEEE80211_HE_PHY_CAP6_TRIG_MU_BEAMFORMING_PARTIAL_BW_FB;
	elem->phy_cap_info[6] |= c;

	/* the maximum cap is 4 x 3, (Nr, Nc) = (3, 2) */
	elem->phy_cap_info[7] |= min_t(पूर्णांक, nss - 1, 2) << 3;
पूर्ण

अटल व्योम
mt7915_gen_ppe_thresh(u8 *he_ppet, पूर्णांक nss)
अणु
	u8 i, ppet_bits, ppet_size, ru_bit_mask = 0x7; /* HE80 */
	u8 ppet16_ppet8_ru3_ru0[] = अणु0x1c, 0xc7, 0x71पूर्ण;

	he_ppet[0] = FIELD_PREP(IEEE80211_PPE_THRES_NSS_MASK, nss - 1) |
		     FIELD_PREP(IEEE80211_PPE_THRES_RU_INDEX_BITMASK_MASK,
				ru_bit_mask);

	ppet_bits = IEEE80211_PPE_THRES_INFO_PPET_SIZE *
		    nss * hweight8(ru_bit_mask) * 2;
	ppet_size = DIV_ROUND_UP(ppet_bits, 8);

	क्रम (i = 0; i < ppet_size - 1; i++)
		he_ppet[i + 1] = ppet16_ppet8_ru3_ru0[i % 3];

	he_ppet[i + 1] = ppet16_ppet8_ru3_ru0[i % 3] &
			 (0xff >> (8 - (ppet_bits - 1) % 8));
पूर्ण

अटल पूर्णांक
mt7915_init_he_caps(काष्ठा mt7915_phy *phy, क्रमागत nl80211_band band,
		    काष्ठा ieee80211_sband_अगरtype_data *data)
अणु
	पूर्णांक i, idx = 0, nss = hweight8(phy->mt76->chainmask);
	u16 mcs_map = 0;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (i < nss)
			mcs_map |= (IEEE80211_HE_MCS_SUPPORT_0_11 << (i * 2));
		अन्यथा
			mcs_map |= (IEEE80211_HE_MCS_NOT_SUPPORTED << (i * 2));
	पूर्ण

	क्रम (i = 0; i < NUM_NL80211_IFTYPES; i++) अणु
		काष्ठा ieee80211_sta_he_cap *he_cap = &data[idx].he_cap;
		काष्ठा ieee80211_he_cap_elem *he_cap_elem =
				&he_cap->he_cap_elem;
		काष्ठा ieee80211_he_mcs_nss_supp *he_mcs =
				&he_cap->he_mcs_nss_supp;

		चयन (i) अणु
		हाल NL80211_IFTYPE_STATION:
		हाल NL80211_IFTYPE_AP:
#अगर_घोषित CONFIG_MAC80211_MESH
		हाल NL80211_IFTYPE_MESH_POINT:
#पूर्ण_अगर
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		data[idx].types_mask = BIT(i);
		he_cap->has_he = true;

		he_cap_elem->mac_cap_info[0] =
			IEEE80211_HE_MAC_CAP0_HTC_HE;
		he_cap_elem->mac_cap_info[3] =
			IEEE80211_HE_MAC_CAP3_OMI_CONTROL |
			IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_3;
		he_cap_elem->mac_cap_info[4] =
			IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU;

		अगर (band == NL80211_BAND_2GHZ)
			he_cap_elem->phy_cap_info[0] =
				IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G;
		अन्यथा अगर (band == NL80211_BAND_5GHZ)
			he_cap_elem->phy_cap_info[0] =
				IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G |
				IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G |
				IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;

		he_cap_elem->phy_cap_info[1] =
			IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD;
		he_cap_elem->phy_cap_info[2] =
			IEEE80211_HE_PHY_CAP2_STBC_TX_UNDER_80MHZ |
			IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ;

		चयन (i) अणु
		हाल NL80211_IFTYPE_AP:
			he_cap_elem->mac_cap_info[0] |=
				IEEE80211_HE_MAC_CAP0_TWT_RES;
			he_cap_elem->mac_cap_info[2] |=
				IEEE80211_HE_MAC_CAP2_BSR;
			he_cap_elem->mac_cap_info[4] |=
				IEEE80211_HE_MAC_CAP4_BQR;
			he_cap_elem->mac_cap_info[5] |=
				IEEE80211_HE_MAC_CAP5_OM_CTRL_UL_MU_DATA_DIS_RX;
			he_cap_elem->phy_cap_info[3] |=
				IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_QPSK |
				IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_QPSK;
			he_cap_elem->phy_cap_info[6] |=
				IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT;
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
			he_cap_elem->mac_cap_info[0] |=
				IEEE80211_HE_MAC_CAP0_TWT_REQ;
			he_cap_elem->mac_cap_info[1] |=
				IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUR_16US;

			अगर (band == NL80211_BAND_2GHZ)
				he_cap_elem->phy_cap_info[0] |=
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_RU_MAPPING_IN_2G;
			अन्यथा अगर (band == NL80211_BAND_5GHZ)
				he_cap_elem->phy_cap_info[0] |=
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_RU_MAPPING_IN_5G;

			he_cap_elem->phy_cap_info[1] |=
				IEEE80211_HE_PHY_CAP1_DEVICE_CLASS_A |
				IEEE80211_HE_PHY_CAP1_HE_LTF_AND_GI_FOR_HE_PPDUS_0_8US;
			he_cap_elem->phy_cap_info[3] |=
				IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_QPSK |
				IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_QPSK;
			he_cap_elem->phy_cap_info[6] |=
				IEEE80211_HE_PHY_CAP6_TRIG_CQI_FB |
				IEEE80211_HE_PHY_CAP6_PARTIAL_BW_EXT_RANGE |
				IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT;
			he_cap_elem->phy_cap_info[7] |=
				IEEE80211_HE_PHY_CAP7_POWER_BOOST_FACTOR_SUPP |
				IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XLTF_AND_08_US_GI;
			he_cap_elem->phy_cap_info[8] |=
				IEEE80211_HE_PHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
				IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
				IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU |
				IEEE80211_HE_PHY_CAP8_DCM_MAX_RU_484;
			he_cap_elem->phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_LONGER_THAN_16_SIGB_OFDM_SYM |
				IEEE80211_HE_PHY_CAP9_NON_TRIGGERED_CQI_FEEDBACK |
				IEEE80211_HE_PHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU |
				IEEE80211_HE_PHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU |
				IEEE80211_HE_PHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_COMP_SIGB |
				IEEE80211_HE_PHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_NON_COMP_SIGB;
			अवरोध;
		पूर्ण

		he_mcs->rx_mcs_80 = cpu_to_le16(mcs_map);
		he_mcs->tx_mcs_80 = cpu_to_le16(mcs_map);
		he_mcs->rx_mcs_160 = cpu_to_le16(mcs_map);
		he_mcs->tx_mcs_160 = cpu_to_le16(mcs_map);
		he_mcs->rx_mcs_80p80 = cpu_to_le16(mcs_map);
		he_mcs->tx_mcs_80p80 = cpu_to_le16(mcs_map);

		mt7915_set_stream_he_txbf_caps(he_cap, i, nss);

		स_रखो(he_cap->ppe_thres, 0, माप(he_cap->ppe_thres));
		अगर (he_cap_elem->phy_cap_info[6] &
		    IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT) अणु
			mt7915_gen_ppe_thresh(he_cap->ppe_thres, nss);
		पूर्ण अन्यथा अणु
			he_cap_elem->phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_16US;
		पूर्ण
		idx++;
	पूर्ण

	वापस idx;
पूर्ण

व्योम mt7915_set_stream_he_caps(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा ieee80211_sband_अगरtype_data *data;
	काष्ठा ieee80211_supported_band *band;
	पूर्णांक n;

	अगर (phy->mt76->cap.has_2ghz) अणु
		data = phy->अगरtype[NL80211_BAND_2GHZ];
		n = mt7915_init_he_caps(phy, NL80211_BAND_2GHZ, data);

		band = &phy->mt76->sband_2g.sband;
		band->अगरtype_data = data;
		band->n_अगरtype_data = n;
	पूर्ण

	अगर (phy->mt76->cap.has_5ghz) अणु
		data = phy->अगरtype[NL80211_BAND_5GHZ];
		n = mt7915_init_he_caps(phy, NL80211_BAND_5GHZ, data);

		band = &phy->mt76->sband_5g.sband;
		band->अगरtype_data = data;
		band->n_अगरtype_data = n;
	पूर्ण
पूर्ण

अटल व्योम mt7915_unरेजिस्टर_ext_phy(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt7915_phy *phy = mt7915_ext_phy(dev);
	काष्ठा mt76_phy *mphy = dev->mt76.phy2;

	अगर (!phy)
		वापस;

	mt76_unरेजिस्टर_phy(mphy);
	ieee80211_मुक्त_hw(mphy->hw);
पूर्ण

पूर्णांक mt7915_रेजिस्टर_device(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	पूर्णांक ret;

	dev->phy.dev = dev;
	dev->phy.mt76 = &dev->mt76.phy;
	dev->mt76.phy.priv = &dev->phy;
	INIT_LIST_HEAD(&dev->phy.stats_list);
	INIT_WORK(&dev->rc_work, mt7915_mac_sta_rc_work);
	INIT_DELAYED_WORK(&dev->mphy.mac_work, mt7915_mac_work);
	INIT_LIST_HEAD(&dev->sta_rc_list);
	INIT_LIST_HEAD(&dev->sta_poll_list);
	spin_lock_init(&dev->sta_poll_lock);

	init_रुकोqueue_head(&dev->reset_रुको);
	INIT_WORK(&dev->reset_work, mt7915_mac_reset_work);

	ret = mt7915_init_hardware(dev);
	अगर (ret)
		वापस ret;

	mt7915_init_wiphy(hw);

	अगर (!dev->dbdc_support)
		dev->mphy.sband_5g.sband.vht_cap.cap |=
			IEEE80211_VHT_CAP_SHORT_GI_160 |
			IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ;

	dev->mphy.hw->wiphy->available_antennas_rx = dev->mphy.chainmask;
	dev->mphy.hw->wiphy->available_antennas_tx = dev->mphy.chainmask;
	dev->phy.dfs_state = -1;

#अगर_घोषित CONFIG_NL80211_TESTMODE
	dev->mt76.test_ops = &mt7915_tesपंचांगode_ops;
#पूर्ण_अगर

	ret = mt76_रेजिस्टर_device(&dev->mt76, true, mt7915_rates,
				   ARRAY_SIZE(mt7915_rates));
	अगर (ret)
		वापस ret;

	ieee80211_queue_work(mt76_hw(dev), &dev->init_work);

	ret = mt7915_रेजिस्टर_ext_phy(dev);
	अगर (ret)
		वापस ret;

	वापस mt7915_init_debugfs(dev);
पूर्ण

व्योम mt7915_unरेजिस्टर_device(काष्ठा mt7915_dev *dev)
अणु
	mt7915_unरेजिस्टर_ext_phy(dev);
	mt76_unरेजिस्टर_device(&dev->mt76);
	mt7915_mcu_निकास(dev);
	mt7915_tx_token_put(dev);
	mt7915_dma_cleanup(dev);

	mt76_मुक्त_device(&dev->mt76);
पूर्ण
