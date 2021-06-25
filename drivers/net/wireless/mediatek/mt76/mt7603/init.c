<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश <linux/etherdevice.h>
#समावेश "mt7603.h"
#समावेश "mac.h"
#समावेश "eeprom.h"

स्थिर काष्ठा mt76_driver_ops mt7603_drv_ops = अणु
	.txwi_size = MT_TXD_SIZE,
	.drv_flags = MT_DRV_SW_RX_AIRTIME,
	.survey_flags = SURVEY_INFO_TIME_TX,
	.tx_prepare_skb = mt7603_tx_prepare_skb,
	.tx_complete_skb = mt7603_tx_complete_skb,
	.rx_skb = mt7603_queue_rx_skb,
	.rx_poll_complete = mt7603_rx_poll_complete,
	.sta_ps = mt7603_sta_ps,
	.sta_add = mt7603_sta_add,
	.sta_assoc = mt7603_sta_assoc,
	.sta_हटाओ = mt7603_sta_हटाओ,
	.update_survey = mt7603_update_channel,
पूर्ण;

अटल व्योम
mt7603_set_पंचांगac_ढाँचा(काष्ठा mt7603_dev *dev)
अणु
	u32 desc[5] = अणु
		[1] = FIELD_PREP(MT_TXD3_REM_TX_COUNT, 0xf),
		[3] = MT_TXD5_SW_POWER_MGMT
	पूर्ण;
	u32 addr;
	पूर्णांक i;

	addr = mt7603_reg_map(dev, MT_CLIENT_BASE_PHYS_ADDR);
	addr += MT_CLIENT_TMAC_INFO_TEMPLATE;
	क्रम (i = 0; i < ARRAY_SIZE(desc); i++)
		mt76_wr(dev, addr + 4 * i, desc[i]);
पूर्ण

अटल व्योम
mt7603_dma_sched_init(काष्ठा mt7603_dev *dev)
अणु
	पूर्णांक page_size = 128;
	पूर्णांक page_count;
	पूर्णांक max_len = 1792;
	पूर्णांक max_amsdu_pages = 4096 / page_size;
	पूर्णांक max_mcu_len = 4096;
	पूर्णांक max_beacon_len = 512 * 4 + max_len;
	पूर्णांक max_mcast_pages = 4 * max_len / page_size;
	पूर्णांक reserved_count = 0;
	पूर्णांक beacon_pages;
	पूर्णांक mcu_pages;
	पूर्णांक i;

	page_count = mt76_get_field(dev, MT_PSE_FC_P0,
				    MT_PSE_FC_P0_MAX_QUOTA);
	beacon_pages = 4 * (max_beacon_len / page_size);
	mcu_pages = max_mcu_len / page_size;

	mt76_wr(dev, MT_PSE_FRP,
		FIELD_PREP(MT_PSE_FRP_P0, 7) |
		FIELD_PREP(MT_PSE_FRP_P1, 6) |
		FIELD_PREP(MT_PSE_FRP_P2_RQ2, 4));

	mt76_wr(dev, MT_HIGH_PRIORITY_1, 0x55555553);
	mt76_wr(dev, MT_HIGH_PRIORITY_2, 0x78555555);

	mt76_wr(dev, MT_QUEUE_PRIORITY_1, 0x2b1a096e);
	mt76_wr(dev, MT_QUEUE_PRIORITY_2, 0x785f4d3c);

	mt76_wr(dev, MT_PRIORITY_MASK, 0xffffffff);

	mt76_wr(dev, MT_SCH_1, page_count | (2 << 28));
	mt76_wr(dev, MT_SCH_2, max_amsdu_pages);

	क्रम (i = 0; i <= 4; i++)
		mt76_wr(dev, MT_PAGE_COUNT(i), max_amsdu_pages);
	reserved_count += 5 * max_amsdu_pages;

	mt76_wr(dev, MT_PAGE_COUNT(5), mcu_pages);
	reserved_count += mcu_pages;

	mt76_wr(dev, MT_PAGE_COUNT(7), beacon_pages);
	reserved_count += beacon_pages;

	mt76_wr(dev, MT_PAGE_COUNT(8), max_mcast_pages);
	reserved_count += max_mcast_pages;

	अगर (is_mt7603(dev))
		reserved_count = 0;

	mt76_wr(dev, MT_RSV_MAX_THRESH, page_count - reserved_count);

	अगर (is_mt7603(dev) && mt76xx_rev(dev) >= MT7603_REV_E2) अणु
		mt76_wr(dev, MT_GROUP_THRESH(0),
			page_count - beacon_pages - mcu_pages);
		mt76_wr(dev, MT_GROUP_THRESH(1), beacon_pages);
		mt76_wr(dev, MT_BMAP_0, 0x0080ff5f);
		mt76_wr(dev, MT_GROUP_THRESH(2), mcu_pages);
		mt76_wr(dev, MT_BMAP_1, 0x00000020);
	पूर्ण अन्यथा अणु
		mt76_wr(dev, MT_GROUP_THRESH(0), page_count);
		mt76_wr(dev, MT_BMAP_0, 0xffff);
	पूर्ण

	mt76_wr(dev, MT_SCH_4, 0);

	क्रम (i = 0; i <= 15; i++)
		mt76_wr(dev, MT_TXTIME_THRESH(i), 0xfffff);

	mt76_set(dev, MT_SCH_4, BIT(6));
पूर्ण

अटल व्योम
mt7603_phy_init(काष्ठा mt7603_dev *dev)
अणु
	पूर्णांक rx_chains = dev->mphy.antenna_mask;
	पूर्णांक tx_chains = hweight8(rx_chains) - 1;

	mt76_rmw(dev, MT_WF_RMAC_RMCR,
		 (MT_WF_RMAC_RMCR_SMPS_MODE |
		  MT_WF_RMAC_RMCR_RX_STREAMS),
		 (FIELD_PREP(MT_WF_RMAC_RMCR_SMPS_MODE, 3) |
		  FIELD_PREP(MT_WF_RMAC_RMCR_RX_STREAMS, rx_chains)));

	mt76_rmw_field(dev, MT_TMAC_TCR, MT_TMAC_TCR_TX_STREAMS,
		       tx_chains);

	dev->agc0 = mt76_rr(dev, MT_AGC(0));
	dev->agc3 = mt76_rr(dev, MT_AGC(3));
पूर्ण

अटल व्योम
mt7603_mac_init(काष्ठा mt7603_dev *dev)
अणु
	u8 bc_addr[ETH_ALEN];
	u32 addr;
	पूर्णांक i;

	mt76_wr(dev, MT_AGG_BA_SIZE_LIMIT_0,
		(MT_AGG_SIZE_LIMIT(0) << 0 * MT_AGG_BA_SIZE_LIMIT_SHIFT) |
		(MT_AGG_SIZE_LIMIT(1) << 1 * MT_AGG_BA_SIZE_LIMIT_SHIFT) |
		(MT_AGG_SIZE_LIMIT(2) << 2 * MT_AGG_BA_SIZE_LIMIT_SHIFT) |
		(MT_AGG_SIZE_LIMIT(3) << 3 * MT_AGG_BA_SIZE_LIMIT_SHIFT));

	mt76_wr(dev, MT_AGG_BA_SIZE_LIMIT_1,
		(MT_AGG_SIZE_LIMIT(4) << 0 * MT_AGG_BA_SIZE_LIMIT_SHIFT) |
		(MT_AGG_SIZE_LIMIT(5) << 1 * MT_AGG_BA_SIZE_LIMIT_SHIFT) |
		(MT_AGG_SIZE_LIMIT(6) << 2 * MT_AGG_BA_SIZE_LIMIT_SHIFT) |
		(MT_AGG_SIZE_LIMIT(7) << 3 * MT_AGG_BA_SIZE_LIMIT_SHIFT));

	mt76_wr(dev, MT_AGG_LIMIT,
		FIELD_PREP(MT_AGG_LIMIT_AC(0), 24) |
		FIELD_PREP(MT_AGG_LIMIT_AC(1), 24) |
		FIELD_PREP(MT_AGG_LIMIT_AC(2), 24) |
		FIELD_PREP(MT_AGG_LIMIT_AC(3), 24));

	mt76_wr(dev, MT_AGG_LIMIT_1,
		FIELD_PREP(MT_AGG_LIMIT_AC(0), 24) |
		FIELD_PREP(MT_AGG_LIMIT_AC(1), 24) |
		FIELD_PREP(MT_AGG_LIMIT_AC(2), 24) |
		FIELD_PREP(MT_AGG_LIMIT_AC(3), 24));

	mt76_wr(dev, MT_AGG_CONTROL,
		FIELD_PREP(MT_AGG_CONTROL_BAR_RATE, 0x4b) |
		FIELD_PREP(MT_AGG_CONTROL_CFEND_RATE, 0x69) |
		MT_AGG_CONTROL_NO_BA_AR_RULE);

	mt76_wr(dev, MT_AGG_RETRY_CONTROL,
		FIELD_PREP(MT_AGG_RETRY_CONTROL_BAR_LIMIT, 1) |
		FIELD_PREP(MT_AGG_RETRY_CONTROL_RTS_LIMIT, 15));

	mt76_wr(dev, MT_DMA_DCR0, MT_DMA_DCR0_RX_VEC_DROP |
		FIELD_PREP(MT_DMA_DCR0_MAX_RX_LEN, 4096));

	mt76_rmw(dev, MT_DMA_VCFR0, BIT(0), BIT(13));
	mt76_rmw(dev, MT_DMA_TMCFR0, BIT(0) | BIT(1), BIT(13));

	mt76_clear(dev, MT_WF_RMAC_TMR_PA, BIT(31));

	mt76_set(dev, MT_WF_RMACDR, MT_WF_RMACDR_MAXLEN_20BIT);
	mt76_rmw(dev, MT_WF_RMAC_MAXMINLEN, 0xffffff, 0x19000);

	mt76_wr(dev, MT_WF_RFCR1, 0);

	mt76_set(dev, MT_TMAC_TCR, MT_TMAC_TCR_RX_RIFS_MODE);

	mt7603_set_पंचांगac_ढाँचा(dev);

	/* Enable RX group to HIF */
	addr = mt7603_reg_map(dev, MT_CLIENT_BASE_PHYS_ADDR);
	mt76_set(dev, addr + MT_CLIENT_RXINF, MT_CLIENT_RXINF_RXSH_GROUPS);

	/* Enable RX group to MCU */
	mt76_set(dev, MT_DMA_DCR1, GENMASK(13, 11));

	mt76_rmw_field(dev, MT_AGG_PCR_RTS, MT_AGG_PCR_RTS_PKT_THR, 3);
	mt76_set(dev, MT_TMAC_PCR, MT_TMAC_PCR_SPE_EN);

	/* include preamble detection in CCA trigger संकेत */
	mt76_rmw_field(dev, MT_TXREQ, MT_TXREQ_CCA_SRC_SEL, 2);

	mt76_wr(dev, MT_RXREQ, 4);

	/* Configure all rx packets to HIF */
	mt76_wr(dev, MT_DMA_RCFR0, 0xc0000000);

	/* Configure MCU txs selection with aggregation */
	mt76_wr(dev, MT_DMA_TCFR0,
		FIELD_PREP(MT_DMA_TCFR_TXS_AGGR_TIMEOUT, 1) | /* 32 us */
		MT_DMA_TCFR_TXS_AGGR_COUNT);

	/* Configure HIF txs selection with aggregation */
	mt76_wr(dev, MT_DMA_TCFR1,
		FIELD_PREP(MT_DMA_TCFR_TXS_AGGR_TIMEOUT, 1) | /* 32 us */
		MT_DMA_TCFR_TXS_AGGR_COUNT | /* Maximum count */
		MT_DMA_TCFR_TXS_BIT_MAP);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_1, MT_PSE_WTBL_2_PHYS_ADDR);

	क्रम (i = 0; i < MT7603_WTBL_SIZE; i++)
		mt7603_wtbl_clear(dev, i);

	eth_broadcast_addr(bc_addr);
	mt7603_wtbl_init(dev, MT7603_WTBL_RESERVED, -1, bc_addr);
	dev->global_sta.wcid.idx = MT7603_WTBL_RESERVED;
	rcu_assign_poपूर्णांकer(dev->mt76.wcid[MT7603_WTBL_RESERVED],
			   &dev->global_sta.wcid);

	mt76_rmw_field(dev, MT_LPON_BTEIR, MT_LPON_BTEIR_MBSS_MODE, 2);
	mt76_rmw_field(dev, MT_WF_RMACDR, MT_WF_RMACDR_MBSSID_MASK, 2);

	mt76_wr(dev, MT_AGG_ARUCR,
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(0), 7) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(1), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(2), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(3), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(4), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(5), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(6), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(7), 1));

	mt76_wr(dev, MT_AGG_ARDCR,
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(0), MT7603_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(1), MT7603_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(2), MT7603_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(3), MT7603_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(4), MT7603_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(5), MT7603_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(6), MT7603_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(7), MT7603_RATE_RETRY - 1));

	mt76_wr(dev, MT_AGG_ARCR,
		(FIELD_PREP(MT_AGG_ARCR_RTS_RATE_THR, 2) |
		 MT_AGG_ARCR_RATE_DOWN_RATIO_EN |
		 FIELD_PREP(MT_AGG_ARCR_RATE_DOWN_RATIO, 1) |
		 FIELD_PREP(MT_AGG_ARCR_RATE_UP_EXTRA_TH, 4)));

	mt76_set(dev, MT_WTBL_RMVTCR, MT_WTBL_RMVTCR_RX_MV_MODE);

	mt76_clear(dev, MT_SEC_SCR, MT_SEC_SCR_MASK_ORDER);
	mt76_clear(dev, MT_SEC_SCR, BIT(18));

	/* Set secondary beacon समय offsets */
	क्रम (i = 0; i <= 4; i++)
		mt76_rmw_field(dev, MT_LPON_SBTOR(i), MT_LPON_SBTOR_TIME_OFFSET,
			       (i + 1) * (20 + 4096));
पूर्ण

अटल पूर्णांक
mt7603_init_hardware(काष्ठा mt7603_dev *dev)
अणु
	पूर्णांक i, ret;

	mt76_wr(dev, MT_INT_SOURCE_CSR, ~0);

	ret = mt7603_eeprom_init(dev);
	अगर (ret < 0)
		वापस ret;

	ret = mt7603_dma_init(dev);
	अगर (ret)
		वापस ret;

	mt76_wr(dev, MT_WPDMA_GLO_CFG, 0x52000850);
	mt7603_mac_dma_start(dev);
	dev->rxfilter = mt76_rr(dev, MT_WF_RFCR);
	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	क्रम (i = 0; i < MT7603_WTBL_SIZE; i++) अणु
		mt76_wr(dev, MT_PSE_RTA, MT_PSE_RTA_BUSY | MT_PSE_RTA_WRITE |
			FIELD_PREP(MT_PSE_RTA_TAG_ID, i));
		mt76_poll(dev, MT_PSE_RTA, MT_PSE_RTA_BUSY, 0, 5000);
	पूर्ण

	ret = mt7603_mcu_init(dev);
	अगर (ret)
		वापस ret;

	mt7603_dma_sched_init(dev);
	mt7603_mcu_set_eeprom(dev);
	mt7603_phy_init(dev);
	mt7603_mac_init(dev);

	वापस 0;
पूर्ण

#घोषणा CCK_RATE(_idx, _rate) अणु					\
	.bitrate = _rate,					\
	.flags = IEEE80211_RATE_SHORT_PREAMBLE,			\
	.hw_value = (MT_PHY_TYPE_CCK << 8) | (_idx),		\
	.hw_value_लघु = (MT_PHY_TYPE_CCK << 8) | (4 + _idx),	\
पूर्ण

#घोषणा OFDM_RATE(_idx, _rate) अणु				\
	.bitrate = _rate,					\
	.hw_value = (MT_PHY_TYPE_OFDM << 8) | (_idx),		\
	.hw_value_लघु = (MT_PHY_TYPE_OFDM << 8) | (_idx),	\
पूर्ण

अटल काष्ठा ieee80211_rate mt7603_rates[] = अणु
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
		.max = MT7603_MAX_INTERFACES,
		.types = BIT(NL80211_IFTYPE_STATION) |
#अगर_घोषित CONFIG_MAC80211_MESH
			 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
			 BIT(NL80211_IFTYPE_P2P_CLIENT) |
			 BIT(NL80211_IFTYPE_P2P_GO) |
			 BIT(NL80211_IFTYPE_AP)
	 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb[] = अणु
	अणु
		.limits = अगर_limits,
		.n_limits = ARRAY_SIZE(अगर_limits),
		.max_पूर्णांकerfaces = 4,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
	पूर्ण
पूर्ण;

अटल व्योम mt7603_led_set_config(काष्ठा mt76_dev *mt76, u8 delay_on,
				  u8 delay_off)
अणु
	काष्ठा mt7603_dev *dev = container_of(mt76, काष्ठा mt7603_dev,
					      mt76);
	u32 val, addr;

	val = FIELD_PREP(MT_LED_STATUS_DURATION, 0xffff) |
	      FIELD_PREP(MT_LED_STATUS_OFF, delay_off) |
	      FIELD_PREP(MT_LED_STATUS_ON, delay_on);

	addr = mt7603_reg_map(dev, MT_LED_STATUS_0(mt76->led_pin));
	mt76_wr(dev, addr, val);
	addr = mt7603_reg_map(dev, MT_LED_STATUS_1(mt76->led_pin));
	mt76_wr(dev, addr, val);

	val = MT_LED_CTRL_REPLAY(mt76->led_pin) |
	      MT_LED_CTRL_KICK(mt76->led_pin);
	अगर (mt76->led_al)
		val |= MT_LED_CTRL_POLARITY(mt76->led_pin);
	addr = mt7603_reg_map(dev, MT_LED_CTRL);
	mt76_wr(dev, addr, val);
पूर्ण

अटल पूर्णांक mt7603_led_set_blink(काष्ठा led_classdev *led_cdev,
				अचिन्हित दीर्घ *delay_on,
				अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा mt76_dev *mt76 = container_of(led_cdev, काष्ठा mt76_dev,
					     led_cdev);
	u8 delta_on, delta_off;

	delta_off = max_t(u8, *delay_off / 10, 1);
	delta_on = max_t(u8, *delay_on / 10, 1);

	mt7603_led_set_config(mt76, delta_on, delta_off);
	वापस 0;
पूर्ण

अटल व्योम mt7603_led_set_brightness(काष्ठा led_classdev *led_cdev,
				      क्रमागत led_brightness brightness)
अणु
	काष्ठा mt76_dev *mt76 = container_of(led_cdev, काष्ठा mt76_dev,
					     led_cdev);

	अगर (!brightness)
		mt7603_led_set_config(mt76, 0, 0xff);
	अन्यथा
		mt7603_led_set_config(mt76, 0xff, 0);
पूर्ण

अटल u32 __mt7603_reg_addr(काष्ठा mt7603_dev *dev, u32 addr)
अणु
	अगर (addr < 0x100000)
		वापस addr;

	वापस mt7603_reg_map(dev, addr);
पूर्ण

अटल u32 mt7603_rr(काष्ठा mt76_dev *mdev, u32 offset)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	u32 addr = __mt7603_reg_addr(dev, offset);

	वापस dev->bus_ops->rr(mdev, addr);
पूर्ण

अटल व्योम mt7603_wr(काष्ठा mt76_dev *mdev, u32 offset, u32 val)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	u32 addr = __mt7603_reg_addr(dev, offset);

	dev->bus_ops->wr(mdev, addr, val);
पूर्ण

अटल u32 mt7603_rmw(काष्ठा mt76_dev *mdev, u32 offset, u32 mask, u32 val)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	u32 addr = __mt7603_reg_addr(dev, offset);

	वापस dev->bus_ops->rmw(mdev, addr, mask, val);
पूर्ण

अटल व्योम
mt7603_regd_notअगरier(काष्ठा wiphy *wiphy,
		     काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा mt7603_dev *dev = hw->priv;

	dev->mt76.region = request->dfs_region;
	dev->ed_monitor = dev->ed_monitor_enabled &&
			  dev->mt76.region == NL80211_DFS_ETSI;
पूर्ण

अटल पूर्णांक
mt7603_txघातer_चिन्हित(पूर्णांक val)
अणु
	bool sign = val & BIT(6);

	अगर (!(val & BIT(7)))
		वापस 0;

	val &= GENMASK(5, 0);
	अगर (!sign)
		val = -val;

	वापस val;
पूर्ण

अटल व्योम
mt7603_init_txघातer(काष्ठा mt7603_dev *dev,
		    काष्ठा ieee80211_supported_band *sband)
अणु
	काष्ठा ieee80211_channel *chan;
	u8 *eeprom = (u8 *)dev->mt76.eeprom.data;
	पूर्णांक target_घातer = eeprom[MT_EE_TX_POWER_0_START_2G + 2] & ~BIT(7);
	u8 *rate_घातer = &eeprom[MT_EE_TX_POWER_CCK];
	bool ext_pa = eeprom[MT_EE_NIC_CONF_0 + 1] & BIT(1);
	पूर्णांक max_offset, cur_offset;
	पूर्णांक i;

	अगर (ext_pa && is_mt7603(dev))
		target_घातer = eeprom[MT_EE_TX_POWER_TSSI_OFF] & ~BIT(7);

	अगर (target_घातer & BIT(6))
		target_घातer = -(target_घातer & GENMASK(5, 0));

	max_offset = 0;
	क्रम (i = 0; i < 14; i++) अणु
		cur_offset = mt7603_txघातer_चिन्हित(rate_घातer[i]);
		max_offset = max(max_offset, cur_offset);
	पूर्ण

	target_घातer += max_offset;

	dev->tx_घातer_limit = target_घातer;
	dev->mphy.txघातer_cur = target_घातer;

	target_घातer = DIV_ROUND_UP(target_घातer, 2);

	/* add 3 dBm क्रम 2SS devices (combined output) */
	अगर (dev->mphy.antenna_mask & BIT(1))
		target_घातer += 3;

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		chan = &sband->channels[i];
		chan->max_घातer = min_t(पूर्णांक, chan->max_reg_घातer, target_घातer);
		chan->orig_mpwr = target_घातer;
	पूर्ण
पूर्ण

पूर्णांक mt7603_रेजिस्टर_device(काष्ठा mt7603_dev *dev)
अणु
	काष्ठा mt76_bus_ops *bus_ops;
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	काष्ठा wiphy *wiphy = hw->wiphy;
	पूर्णांक ret;

	dev->bus_ops = dev->mt76.bus;
	bus_ops = devm_kmemdup(dev->mt76.dev, dev->bus_ops, माप(*bus_ops),
			       GFP_KERNEL);
	अगर (!bus_ops)
		वापस -ENOMEM;

	bus_ops->rr = mt7603_rr;
	bus_ops->wr = mt7603_wr;
	bus_ops->rmw = mt7603_rmw;
	dev->mt76.bus = bus_ops;

	INIT_LIST_HEAD(&dev->sta_poll_list);
	spin_lock_init(&dev->sta_poll_lock);
	spin_lock_init(&dev->ps_lock);

	INIT_DELAYED_WORK(&dev->mphy.mac_work, mt7603_mac_work);
	tasklet_setup(&dev->mt76.pre_tbtt_tasklet, mt7603_pre_tbtt_tasklet);

	dev->slotसमय = 9;
	dev->sensitivity_limit = 28;
	dev->dynamic_sensitivity = true;

	ret = mt7603_init_hardware(dev);
	अगर (ret)
		वापस ret;

	hw->queues = 4;
	hw->max_rates = 3;
	hw->max_report_rates = 7;
	hw->max_rate_tries = 11;

	hw->radiotap_बारtamp.units_pos =
		IEEE80211_RADIOTAP_TIMESTAMP_UNIT_US;

	hw->sta_data_size = माप(काष्ठा mt7603_sta);
	hw->vअगर_data_size = माप(काष्ठा mt7603_vअगर);

	wiphy->अगरace_combinations = अगर_comb;
	wiphy->n_अगरace_combinations = ARRAY_SIZE(अगर_comb);

	ieee80211_hw_set(hw, TX_STATUS_NO_AMPDU_LEN);
	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(hw, NEEDS_UNIQUE_STA_ADDR);

	/* init led callbacks */
	अगर (IS_ENABLED(CONFIG_MT76_LEDS)) अणु
		dev->mt76.led_cdev.brightness_set = mt7603_led_set_brightness;
		dev->mt76.led_cdev.blink_set = mt7603_led_set_blink;
	पूर्ण

	wiphy->reg_notअगरier = mt7603_regd_notअगरier;

	ret = mt76_रेजिस्टर_device(&dev->mt76, true, mt7603_rates,
				   ARRAY_SIZE(mt7603_rates));
	अगर (ret)
		वापस ret;

	mt7603_init_debugfs(dev);
	mt7603_init_txघातer(dev, &dev->mphy.sband_2g.sband);

	वापस 0;
पूर्ण

व्योम mt7603_unरेजिस्टर_device(काष्ठा mt7603_dev *dev)
अणु
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	mt76_unरेजिस्टर_device(&dev->mt76);
	mt7603_mcu_निकास(dev);
	mt7603_dma_cleanup(dev);
	mt76_मुक्त_device(&dev->mt76);
पूर्ण
