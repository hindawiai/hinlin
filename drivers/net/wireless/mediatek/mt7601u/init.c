<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश "mt7601u.h"
#समावेश "eeprom.h"
#समावेश "trace.h"
#समावेश "mcu.h"

#समावेश "initvals.h"

अटल व्योम
mt7601u_set_wlan_state(काष्ठा mt7601u_dev *dev, u32 val, bool enable)
अणु
	पूर्णांक i;

	/* Note: we करोn't turn off WLAN_CLK because that makes the device
	 *	 not respond properly on the probe path.
	 *	 In हाल anyone (PSM?) wants to use this function we can
	 *	 bring the घड़ी stuff back and fixup the probe path.
	 */

	अगर (enable)
		val |= (MT_WLAN_FUN_CTRL_WLAN_EN |
			MT_WLAN_FUN_CTRL_WLAN_CLK_EN);
	अन्यथा
		val &= ~(MT_WLAN_FUN_CTRL_WLAN_EN);

	mt7601u_wr(dev, MT_WLAN_FUN_CTRL, val);
	udelay(20);

	अगर (enable) अणु
		set_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state);
	पूर्ण अन्यथा अणु
		clear_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state);
		वापस;
	पूर्ण

	क्रम (i = 200; i; i--) अणु
		val = mt7601u_rr(dev, MT_CMB_CTRL);

		अगर (val & MT_CMB_CTRL_XTAL_RDY && val & MT_CMB_CTRL_PLL_LD)
			अवरोध;

		udelay(20);
	पूर्ण

	/* Note: venकरोr driver tries to disable/enable wlan here and retry
	 *       but the code which करोes it is so buggy it must have never
	 *       triggered, so करोn't bother.
	 */
	अगर (!i)
		dev_err(dev->dev, "Error: PLL and XTAL check failed!\n");
पूर्ण

अटल व्योम mt7601u_chip_onoff(काष्ठा mt7601u_dev *dev, bool enable, bool reset)
अणु
	u32 val;

	mutex_lock(&dev->hw_atomic_mutex);

	val = mt7601u_rr(dev, MT_WLAN_FUN_CTRL);

	अगर (reset) अणु
		val |= MT_WLAN_FUN_CTRL_GPIO_OUT_EN;
		val &= ~MT_WLAN_FUN_CTRL_FRC_WL_ANT_SEL;

		अगर (val & MT_WLAN_FUN_CTRL_WLAN_EN) अणु
			val |= (MT_WLAN_FUN_CTRL_WLAN_RESET |
				MT_WLAN_FUN_CTRL_WLAN_RESET_RF);
			mt7601u_wr(dev, MT_WLAN_FUN_CTRL, val);
			udelay(20);

			val &= ~(MT_WLAN_FUN_CTRL_WLAN_RESET |
				 MT_WLAN_FUN_CTRL_WLAN_RESET_RF);
		पूर्ण
	पूर्ण

	mt7601u_wr(dev, MT_WLAN_FUN_CTRL, val);
	udelay(20);

	mt7601u_set_wlan_state(dev, val, enable);

	mutex_unlock(&dev->hw_atomic_mutex);
पूर्ण

अटल व्योम mt7601u_reset_csr_bbp(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_wr(dev, MT_MAC_SYS_CTRL, (MT_MAC_SYS_CTRL_RESET_CSR |
					  MT_MAC_SYS_CTRL_RESET_BBP));
	mt7601u_wr(dev, MT_USB_DMA_CFG, 0);
	msleep(1);
	mt7601u_wr(dev, MT_MAC_SYS_CTRL, 0);
पूर्ण

अटल व्योम mt7601u_init_usb_dma(काष्ठा mt7601u_dev *dev)
अणु
	u32 val;

	val = FIELD_PREP(MT_USB_DMA_CFG_RX_BULK_AGG_TOUT, MT_USB_AGGR_TIMEOUT) |
	      FIELD_PREP(MT_USB_DMA_CFG_RX_BULK_AGG_LMT,
			 MT_USB_AGGR_SIZE_LIMIT) |
	      MT_USB_DMA_CFG_RX_BULK_EN |
	      MT_USB_DMA_CFG_TX_BULK_EN;
	अगर (dev->in_max_packet == 512)
		val |= MT_USB_DMA_CFG_RX_BULK_AGG_EN;
	mt7601u_wr(dev, MT_USB_DMA_CFG, val);

	val |= MT_USB_DMA_CFG_UDMA_RX_WL_DROP;
	mt7601u_wr(dev, MT_USB_DMA_CFG, val);
	val &= ~MT_USB_DMA_CFG_UDMA_RX_WL_DROP;
	mt7601u_wr(dev, MT_USB_DMA_CFG, val);
पूर्ण

अटल पूर्णांक mt7601u_init_bbp(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt7601u_रुको_bbp_पढ़ोy(dev);
	अगर (ret)
		वापस ret;

	ret = mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_BBP, bbp_common_vals,
				      ARRAY_SIZE(bbp_common_vals));
	अगर (ret)
		वापस ret;

	वापस mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_BBP, bbp_chip_vals,
				       ARRAY_SIZE(bbp_chip_vals));
पूर्ण

अटल व्योम
mt76_init_beacon_offsets(काष्ठा mt7601u_dev *dev)
अणु
	u16 base = MT_BEACON_BASE;
	u32 regs[4] = अणुपूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		u16 addr = dev->beacon_offsets[i];

		regs[i / 4] |= ((addr - base) / 64) << (8 * (i % 4));
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		mt7601u_wr(dev, MT_BCN_OFFSET(i), regs[i]);
पूर्ण

अटल पूर्णांक mt7601u_ग_लिखो_mac_initvals(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_WLAN, mac_common_vals,
				      ARRAY_SIZE(mac_common_vals));
	अगर (ret)
		वापस ret;
	ret = mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_WLAN,
				      mac_chip_vals, ARRAY_SIZE(mac_chip_vals));
	अगर (ret)
		वापस ret;

	mt76_init_beacon_offsets(dev);

	mt7601u_wr(dev, MT_AUX_CLK_CFG, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7601u_init_wcid_mem(काष्ठा mt7601u_dev *dev)
अणु
	u32 *vals;
	पूर्णांक i, ret;

	vals = kदो_स्मृति(माप(*vals) * N_WCIDS * 2, GFP_KERNEL);
	अगर (!vals)
		वापस -ENOMEM;

	क्रम (i = 0; i < N_WCIDS; i++)  अणु
		vals[i * 2] = 0xffffffff;
		vals[i * 2 + 1] = 0x00ffffff;
	पूर्ण

	ret = mt7601u_burst_ग_लिखो_regs(dev, MT_WCID_ADDR_BASE,
				       vals, N_WCIDS * 2);
	kमुक्त(vals);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7601u_init_key_mem(काष्ठा mt7601u_dev *dev)
अणु
	u32 vals[4] = अणुपूर्ण;

	वापस mt7601u_burst_ग_लिखो_regs(dev, MT_SKEY_MODE_BASE_0,
					vals, ARRAY_SIZE(vals));
पूर्ण

अटल पूर्णांक mt7601u_init_wcid_attr_mem(काष्ठा mt7601u_dev *dev)
अणु
	u32 *vals;
	पूर्णांक i, ret;

	vals = kदो_स्मृति(माप(*vals) * N_WCIDS * 2, GFP_KERNEL);
	अगर (!vals)
		वापस -ENOMEM;

	क्रम (i = 0; i < N_WCIDS * 2; i++)
		vals[i] = 1;

	ret = mt7601u_burst_ग_लिखो_regs(dev, MT_WCID_ATTR_BASE,
				       vals, N_WCIDS * 2);
	kमुक्त(vals);

	वापस ret;
पूर्ण

अटल व्योम mt7601u_reset_counters(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_rr(dev, MT_RX_STA_CNT0);
	mt7601u_rr(dev, MT_RX_STA_CNT1);
	mt7601u_rr(dev, MT_RX_STA_CNT2);
	mt7601u_rr(dev, MT_TX_STA_CNT0);
	mt7601u_rr(dev, MT_TX_STA_CNT1);
	mt7601u_rr(dev, MT_TX_STA_CNT2);
पूर्ण

पूर्णांक mt7601u_mac_start(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);

	अगर (!mt76_poll(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
		       MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 200000))
		वापस -ETIMEDOUT;

	dev->rxfilter = MT_RX_FILTR_CFG_CRC_ERR |
		MT_RX_FILTR_CFG_PHY_ERR | MT_RX_FILTR_CFG_PROMISC |
		MT_RX_FILTR_CFG_VER_ERR | MT_RX_FILTR_CFG_DUP |
		MT_RX_FILTR_CFG_CFACK | MT_RX_FILTR_CFG_CFEND |
		MT_RX_FILTR_CFG_ACK | MT_RX_FILTR_CFG_CTS |
		MT_RX_FILTR_CFG_RTS | MT_RX_FILTR_CFG_PSPOLL |
		MT_RX_FILTR_CFG_BA | MT_RX_FILTR_CFG_CTRL_RSV;
	mt7601u_wr(dev, MT_RX_FILTR_CFG, dev->rxfilter);

	mt7601u_wr(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_ENABLE_TX | MT_MAC_SYS_CTRL_ENABLE_RX);

	अगर (!mt76_poll(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
		       MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 50))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम mt7601u_mac_stop_hw(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i, ok;

	अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state))
		वापस;

	mt76_clear(dev, MT_BEACON_TIME_CFG, MT_BEACON_TIME_CFG_TIMER_EN |
		   MT_BEACON_TIME_CFG_SYNC_MODE | MT_BEACON_TIME_CFG_TBTT_EN |
		   MT_BEACON_TIME_CFG_BEACON_TX);

	अगर (!mt76_poll(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_TX_BUSY, 0, 1000))
		dev_warn(dev->dev, "Warning: TX DMA did not stop!\n");

	/* Page count on TxQ */
	i = 200;
	जबतक (i-- && ((mt76_rr(dev, 0x0438) & 0xffffffff) ||
		       (mt76_rr(dev, 0x0a30) & 0x000000ff) ||
		       (mt76_rr(dev, 0x0a34) & 0x00ff00ff)))
		msleep(10);

	अगर (!mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_TX, 0, 1000))
		dev_warn(dev->dev, "Warning: MAC TX did not stop!\n");

	mt76_clear(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_RX |
					 MT_MAC_SYS_CTRL_ENABLE_TX);

	/* Page count on RxQ */
	ok = 0;
	i = 200;
	जबतक (i--) अणु
		अगर (!(mt76_rr(dev, MT_RXQ_STA) & 0x00ff0000) &&
		    !mt76_rr(dev, 0x0a30) &&
		    !mt76_rr(dev, 0x0a34)) अणु
			अगर (ok++ > 5)
				अवरोध;
			जारी;
		पूर्ण
		msleep(1);
	पूर्ण

	अगर (!mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_RX, 0, 1000))
		dev_warn(dev->dev, "Warning: MAC RX did not stop!\n");

	अगर (!mt76_poll(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_RX_BUSY, 0, 1000))
		dev_warn(dev->dev, "Warning: RX DMA did not stop!\n");
पूर्ण

व्योम mt7601u_mac_stop(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_mac_stop_hw(dev);
	flush_delayed_work(&dev->stat_work);
	cancel_delayed_work_sync(&dev->stat_work);
पूर्ण

अटल व्योम mt7601u_stop_hardware(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_chip_onoff(dev, false, false);
पूर्ण

पूर्णांक mt7601u_init_hardware(काष्ठा mt7601u_dev *dev)
अणु
	अटल स्थिर u16 beacon_offsets[16] = अणु
		/* 512 byte per beacon */
		0xc000,	0xc200,	0xc400,	0xc600,
		0xc800,	0xca00,	0xcc00,	0xce00,
		0xd000,	0xd200,	0xd400,	0xd600,
		0xd800,	0xda00,	0xdc00,	0xde00
	पूर्ण;
	पूर्णांक ret;

	dev->beacon_offsets = beacon_offsets;

	mt7601u_chip_onoff(dev, true, false);

	ret = mt7601u_रुको_asic_पढ़ोy(dev);
	अगर (ret)
		जाओ err;
	ret = mt7601u_mcu_init(dev);
	अगर (ret)
		जाओ err;

	अगर (!mt76_poll_msec(dev, MT_WPDMA_GLO_CFG,
			    MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
			    MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 100)) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	/* Wait क्रम ASIC पढ़ोy after FW load. */
	ret = mt7601u_रुको_asic_पढ़ोy(dev);
	अगर (ret)
		जाओ err;

	mt7601u_reset_csr_bbp(dev);
	mt7601u_init_usb_dma(dev);

	ret = mt7601u_mcu_cmd_init(dev);
	अगर (ret)
		जाओ err;
	ret = mt7601u_dma_init(dev);
	अगर (ret)
		जाओ err_mcu;
	ret = mt7601u_ग_लिखो_mac_initvals(dev);
	अगर (ret)
		जाओ err_rx;

	अगर (!mt76_poll_msec(dev, MT_MAC_STATUS,
			    MT_MAC_STATUS_TX | MT_MAC_STATUS_RX, 0, 100)) अणु
		ret = -EIO;
		जाओ err_rx;
	पूर्ण

	ret = mt7601u_init_bbp(dev);
	अगर (ret)
		जाओ err_rx;
	ret = mt7601u_init_wcid_mem(dev);
	अगर (ret)
		जाओ err_rx;
	ret = mt7601u_init_key_mem(dev);
	अगर (ret)
		जाओ err_rx;
	ret = mt7601u_init_wcid_attr_mem(dev);
	अगर (ret)
		जाओ err_rx;

	mt76_clear(dev, MT_BEACON_TIME_CFG, (MT_BEACON_TIME_CFG_TIMER_EN |
					     MT_BEACON_TIME_CFG_SYNC_MODE |
					     MT_BEACON_TIME_CFG_TBTT_EN |
					     MT_BEACON_TIME_CFG_BEACON_TX));

	mt7601u_reset_counters(dev);

	mt7601u_rmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);

	mt7601u_wr(dev, MT_TXOP_CTRL_CFG,
		   FIELD_PREP(MT_TXOP_TRUN_EN, 0x3f) |
		   FIELD_PREP(MT_TXOP_EXT_CCA_DLY, 0x58));

	ret = mt7601u_eeprom_init(dev);
	अगर (ret)
		जाओ err_rx;

	ret = mt7601u_phy_init(dev);
	अगर (ret)
		जाओ err_rx;

	mt7601u_set_rx_path(dev, 0);
	mt7601u_set_tx_dac(dev, 0);

	mt7601u_mac_set_ctrlch(dev, false);
	mt7601u_bbp_set_ctrlch(dev, false);
	mt7601u_bbp_set_bw(dev, MT_BW_20);

	वापस 0;

err_rx:
	mt7601u_dma_cleanup(dev);
err_mcu:
	mt7601u_mcu_cmd_deinit(dev);
err:
	mt7601u_chip_onoff(dev, false, false);
	वापस ret;
पूर्ण

व्योम mt7601u_cleanup(काष्ठा mt7601u_dev *dev)
अणु
	अगर (!test_and_clear_bit(MT7601U_STATE_INITIALIZED, &dev->state))
		वापस;

	mt7601u_stop_hardware(dev);
	mt7601u_dma_cleanup(dev);
	mt7601u_mcu_cmd_deinit(dev);
पूर्ण

काष्ठा mt7601u_dev *mt7601u_alloc_device(काष्ठा device *pdev)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा mt7601u_dev *dev;

	hw = ieee80211_alloc_hw(माप(*dev), &mt7601u_ops);
	अगर (!hw)
		वापस शून्य;

	dev = hw->priv;
	dev->dev = pdev;
	dev->hw = hw;
	mutex_init(&dev->venकरोr_req_mutex);
	mutex_init(&dev->reg_atomic_mutex);
	mutex_init(&dev->hw_atomic_mutex);
	mutex_init(&dev->mutex);
	spin_lock_init(&dev->tx_lock);
	spin_lock_init(&dev->rx_lock);
	spin_lock_init(&dev->lock);
	spin_lock_init(&dev->mac_lock);
	spin_lock_init(&dev->con_mon_lock);
	atomic_set(&dev->avg_ampdu_len, 1);
	skb_queue_head_init(&dev->tx_skb_करोne);

	dev->stat_wq = alloc_workqueue("mt7601u", WQ_UNBOUND, 0);
	अगर (!dev->stat_wq) अणु
		ieee80211_मुक्त_hw(hw);
		वापस शून्य;
	पूर्ण

	वापस dev;
पूर्ण

#घोषणा CHAN2G(_idx, _freq) अणु			\
	.band = NL80211_BAND_2GHZ,		\
	.center_freq = (_freq),			\
	.hw_value = (_idx),			\
	.max_घातer = 30,			\
पूर्ण

अटल स्थिर काष्ठा ieee80211_channel mt76_channels_2ghz[] = अणु
	CHAN2G(1, 2412),
	CHAN2G(2, 2417),
	CHAN2G(3, 2422),
	CHAN2G(4, 2427),
	CHAN2G(5, 2432),
	CHAN2G(6, 2437),
	CHAN2G(7, 2442),
	CHAN2G(8, 2447),
	CHAN2G(9, 2452),
	CHAN2G(10, 2457),
	CHAN2G(11, 2462),
	CHAN2G(12, 2467),
	CHAN2G(13, 2472),
	CHAN2G(14, 2484),
पूर्ण;

#घोषणा CCK_RATE(_idx, _rate) अणु					\
	.bitrate = _rate,					\
	.flags = IEEE80211_RATE_SHORT_PREAMBLE,			\
	.hw_value = (MT_PHY_TYPE_CCK << 8) | _idx,		\
	.hw_value_लघु = (MT_PHY_TYPE_CCK << 8) | (8 + _idx),	\
पूर्ण

#घोषणा OFDM_RATE(_idx, _rate) अणु				\
	.bitrate = _rate,					\
	.hw_value = (MT_PHY_TYPE_OFDM << 8) | _idx,		\
	.hw_value_लघु = (MT_PHY_TYPE_OFDM << 8) | _idx,	\
पूर्ण

अटल काष्ठा ieee80211_rate mt76_rates[] = अणु
	CCK_RATE(0, 10),
	CCK_RATE(1, 20),
	CCK_RATE(2, 55),
	CCK_RATE(3, 110),
	OFDM_RATE(0, 60),
	OFDM_RATE(1, 90),
	OFDM_RATE(2, 120),
	OFDM_RATE(3, 180),
	OFDM_RATE(4, 240),
	OFDM_RATE(5, 360),
	OFDM_RATE(6, 480),
	OFDM_RATE(7, 540),
पूर्ण;

अटल पूर्णांक
mt76_init_sband(काष्ठा mt7601u_dev *dev, काष्ठा ieee80211_supported_band *sband,
		स्थिर काष्ठा ieee80211_channel *chan, पूर्णांक n_chan,
		काष्ठा ieee80211_rate *rates, पूर्णांक n_rates)
अणु
	काष्ठा ieee80211_sta_ht_cap *ht_cap;
	व्योम *chanlist;
	पूर्णांक size;

	size = n_chan * माप(*chan);
	chanlist = devm_kmemdup(dev->dev, chan, size, GFP_KERNEL);
	अगर (!chanlist)
		वापस -ENOMEM;

	sband->channels = chanlist;
	sband->n_channels = n_chan;
	sband->bitrates = rates;
	sband->n_bitrates = n_rates;

	ht_cap = &sband->ht_cap;
	ht_cap->ht_supported = true;
	ht_cap->cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		      IEEE80211_HT_CAP_GRN_FLD |
		      IEEE80211_HT_CAP_SGI_20 |
		      IEEE80211_HT_CAP_SGI_40 |
		      (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);

	ht_cap->mcs.rx_mask[0] = 0xff;
	ht_cap->mcs.rx_mask[4] = 0x1;
	ht_cap->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	ht_cap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap->ampdu_density = IEEE80211_HT_MPDU_DENSITY_2;

	dev->chandef.chan = &sband->channels[0];

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_init_sband_2g(काष्ठा mt7601u_dev *dev)
अणु
	dev->sband_2g = devm_kzalloc(dev->dev, माप(*dev->sband_2g),
				     GFP_KERNEL);
	अगर (!dev->sband_2g)
		वापस -ENOMEM;

	dev->hw->wiphy->bands[NL80211_BAND_2GHZ] = dev->sband_2g;

	WARN_ON(dev->ee->reg.start - 1 + dev->ee->reg.num >
		ARRAY_SIZE(mt76_channels_2ghz));

	वापस mt76_init_sband(dev, dev->sband_2g,
			       &mt76_channels_2ghz[dev->ee->reg.start - 1],
			       dev->ee->reg.num,
			       mt76_rates, ARRAY_SIZE(mt76_rates));
पूर्ण

पूर्णांक mt7601u_रेजिस्टर_device(काष्ठा mt7601u_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = dev->hw;
	काष्ठा wiphy *wiphy = hw->wiphy;
	पूर्णांक ret;

	/* Reserve WCID 0 क्रम mcast - thanks to this APs WCID will go to
	 * entry no. 1 like it करोes in the venकरोr driver.
	 */
	dev->wcid_mask[0] |= 1;

	/* init fake wcid क्रम monitor पूर्णांकerfaces */
	dev->mon_wcid = devm_kदो_स्मृति(dev->dev, माप(*dev->mon_wcid),
				     GFP_KERNEL);
	अगर (!dev->mon_wcid)
		वापस -ENOMEM;
	dev->mon_wcid->idx = 0xff;
	dev->mon_wcid->hw_key_idx = -1;

	SET_IEEE80211_DEV(hw, dev->dev);

	hw->queues = 4;
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(hw, SUPPORTS_HT_CCK_RATES);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	hw->max_rates = 1;
	hw->max_report_rates = 7;
	hw->max_rate_tries = 1;

	hw->sta_data_size = माप(काष्ठा mt76_sta);
	hw->vअगर_data_size = माप(काष्ठा mt76_vअगर);

	SET_IEEE80211_PERM_ADDR(hw, dev->macaddr);

	wiphy->features |= NL80211_FEATURE_ACTIVE_MONITOR;
	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION);
	wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS;

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	ret = mt76_init_sband_2g(dev);
	अगर (ret)
		वापस ret;

	INIT_DELAYED_WORK(&dev->mac_work, mt7601u_mac_work);
	INIT_DELAYED_WORK(&dev->stat_work, mt7601u_tx_stat);

	ret = ieee80211_रेजिस्टर_hw(hw);
	अगर (ret)
		वापस ret;

	mt7601u_init_debugfs(dev);

	वापस 0;
पूर्ण
