<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */
#समावेश <linux/sched.h>
#समावेश <linux/of.h>
#समावेश "mt76.h"

#घोषणा CHAN2G(_idx, _freq) अणु			\
	.band = NL80211_BAND_2GHZ,		\
	.center_freq = (_freq),			\
	.hw_value = (_idx),			\
	.max_घातer = 30,			\
पूर्ण

#घोषणा CHAN5G(_idx, _freq) अणु			\
	.band = NL80211_BAND_5GHZ,		\
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

अटल स्थिर काष्ठा ieee80211_channel mt76_channels_5ghz[] = अणु
	CHAN5G(36, 5180),
	CHAN5G(40, 5200),
	CHAN5G(44, 5220),
	CHAN5G(48, 5240),

	CHAN5G(52, 5260),
	CHAN5G(56, 5280),
	CHAN5G(60, 5300),
	CHAN5G(64, 5320),

	CHAN5G(100, 5500),
	CHAN5G(104, 5520),
	CHAN5G(108, 5540),
	CHAN5G(112, 5560),
	CHAN5G(116, 5580),
	CHAN5G(120, 5600),
	CHAN5G(124, 5620),
	CHAN5G(128, 5640),
	CHAN5G(132, 5660),
	CHAN5G(136, 5680),
	CHAN5G(140, 5700),
	CHAN5G(144, 5720),

	CHAN5G(149, 5745),
	CHAN5G(153, 5765),
	CHAN5G(157, 5785),
	CHAN5G(161, 5805),
	CHAN5G(165, 5825),
	CHAN5G(169, 5845),
	CHAN5G(173, 5865),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_tpt_blink mt76_tpt_blink[] = अणु
	अणु .throughput =   0 * 1024, .blink_समय = 334 पूर्ण,
	अणु .throughput =   1 * 1024, .blink_समय = 260 पूर्ण,
	अणु .throughput =   5 * 1024, .blink_समय = 220 पूर्ण,
	अणु .throughput =  10 * 1024, .blink_समय = 190 पूर्ण,
	अणु .throughput =  20 * 1024, .blink_समय = 170 पूर्ण,
	अणु .throughput =  50 * 1024, .blink_समय = 150 पूर्ण,
	अणु .throughput =  70 * 1024, .blink_समय = 130 पूर्ण,
	अणु .throughput = 100 * 1024, .blink_समय = 110 पूर्ण,
	अणु .throughput = 200 * 1024, .blink_समय =  80 पूर्ण,
	अणु .throughput = 300 * 1024, .blink_समय =  50 पूर्ण,
पूर्ण;

अटल पूर्णांक mt76_led_init(काष्ठा mt76_dev *dev)
अणु
	काष्ठा device_node *np = dev->dev->of_node;
	काष्ठा ieee80211_hw *hw = dev->hw;
	पूर्णांक led_pin;

	अगर (!dev->led_cdev.brightness_set && !dev->led_cdev.blink_set)
		वापस 0;

	snम_लिखो(dev->led_name, माप(dev->led_name),
		 "mt76-%s", wiphy_name(hw->wiphy));

	dev->led_cdev.name = dev->led_name;
	dev->led_cdev.शेष_trigger =
		ieee80211_create_tpt_led_trigger(hw,
					IEEE80211_TPT_LEDTRIG_FL_RADIO,
					mt76_tpt_blink,
					ARRAY_SIZE(mt76_tpt_blink));

	np = of_get_child_by_name(np, "led");
	अगर (np) अणु
		अगर (!of_property_पढ़ो_u32(np, "led-sources", &led_pin))
			dev->led_pin = led_pin;
		dev->led_al = of_property_पढ़ो_bool(np, "led-active-low");
	पूर्ण

	वापस led_classdev_रेजिस्टर(dev->dev, &dev->led_cdev);
पूर्ण

अटल व्योम mt76_led_cleanup(काष्ठा mt76_dev *dev)
अणु
	अगर (!dev->led_cdev.brightness_set && !dev->led_cdev.blink_set)
		वापस;

	led_classdev_unरेजिस्टर(&dev->led_cdev);
पूर्ण

अटल व्योम mt76_init_stream_cap(काष्ठा mt76_phy *phy,
				 काष्ठा ieee80211_supported_band *sband,
				 bool vht)
अणु
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sband->ht_cap;
	पूर्णांक i, nstream = hweight8(phy->antenna_mask);
	काष्ठा ieee80211_sta_vht_cap *vht_cap;
	u16 mcs_map = 0;

	अगर (nstream > 1)
		ht_cap->cap |= IEEE80211_HT_CAP_TX_STBC;
	अन्यथा
		ht_cap->cap &= ~IEEE80211_HT_CAP_TX_STBC;

	क्रम (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++)
		ht_cap->mcs.rx_mask[i] = i < nstream ? 0xff : 0;

	अगर (!vht)
		वापस;

	vht_cap = &sband->vht_cap;
	अगर (nstream > 1)
		vht_cap->cap |= IEEE80211_VHT_CAP_TXSTBC;
	अन्यथा
		vht_cap->cap &= ~IEEE80211_VHT_CAP_TXSTBC;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (i < nstream)
			mcs_map |= (IEEE80211_VHT_MCS_SUPPORT_0_9 << (i * 2));
		अन्यथा
			mcs_map |=
				(IEEE80211_VHT_MCS_NOT_SUPPORTED << (i * 2));
	पूर्ण
	vht_cap->vht_mcs.rx_mcs_map = cpu_to_le16(mcs_map);
	vht_cap->vht_mcs.tx_mcs_map = cpu_to_le16(mcs_map);
पूर्ण

व्योम mt76_set_stream_caps(काष्ठा mt76_phy *phy, bool vht)
अणु
	अगर (phy->cap.has_2ghz)
		mt76_init_stream_cap(phy, &phy->sband_2g.sband, false);
	अगर (phy->cap.has_5ghz)
		mt76_init_stream_cap(phy, &phy->sband_5g.sband, vht);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_set_stream_caps);

अटल पूर्णांक
mt76_init_sband(काष्ठा mt76_phy *phy, काष्ठा mt76_sband *msband,
		स्थिर काष्ठा ieee80211_channel *chan, पूर्णांक n_chan,
		काष्ठा ieee80211_rate *rates, पूर्णांक n_rates, bool vht)
अणु
	काष्ठा ieee80211_supported_band *sband = &msband->sband;
	काष्ठा ieee80211_sta_vht_cap *vht_cap;
	काष्ठा ieee80211_sta_ht_cap *ht_cap;
	काष्ठा mt76_dev *dev = phy->dev;
	व्योम *chanlist;
	पूर्णांक size;

	size = n_chan * माप(*chan);
	chanlist = devm_kmemdup(dev->dev, chan, size, GFP_KERNEL);
	अगर (!chanlist)
		वापस -ENOMEM;

	msband->chan = devm_kसुस्मृति(dev->dev, n_chan, माप(*msband->chan),
				    GFP_KERNEL);
	अगर (!msband->chan)
		वापस -ENOMEM;

	sband->channels = chanlist;
	sband->n_channels = n_chan;
	sband->bitrates = rates;
	sband->n_bitrates = n_rates;

	ht_cap = &sband->ht_cap;
	ht_cap->ht_supported = true;
	ht_cap->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_GRN_FLD |
		       IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_SGI_40 |
		       (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);

	ht_cap->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	ht_cap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;

	mt76_init_stream_cap(phy, sband, vht);

	अगर (!vht)
		वापस 0;

	vht_cap = &sband->vht_cap;
	vht_cap->vht_supported = true;
	vht_cap->cap |= IEEE80211_VHT_CAP_RXLDPC |
			IEEE80211_VHT_CAP_RXSTBC_1 |
			IEEE80211_VHT_CAP_SHORT_GI_80 |
			IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN |
			IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN |
			(3 << IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_init_sband_2g(काष्ठा mt76_phy *phy, काष्ठा ieee80211_rate *rates,
		   पूर्णांक n_rates)
अणु
	phy->hw->wiphy->bands[NL80211_BAND_2GHZ] = &phy->sband_2g.sband;

	वापस mt76_init_sband(phy, &phy->sband_2g, mt76_channels_2ghz,
			       ARRAY_SIZE(mt76_channels_2ghz), rates,
			       n_rates, false);
पूर्ण

अटल पूर्णांक
mt76_init_sband_5g(काष्ठा mt76_phy *phy, काष्ठा ieee80211_rate *rates,
		   पूर्णांक n_rates, bool vht)
अणु
	phy->hw->wiphy->bands[NL80211_BAND_5GHZ] = &phy->sband_5g.sband;

	वापस mt76_init_sband(phy, &phy->sband_5g, mt76_channels_5ghz,
			       ARRAY_SIZE(mt76_channels_5ghz), rates,
			       n_rates, vht);
पूर्ण

अटल व्योम
mt76_check_sband(काष्ठा mt76_phy *phy, काष्ठा mt76_sband *msband,
		 क्रमागत nl80211_band band)
अणु
	काष्ठा ieee80211_supported_band *sband = &msband->sband;
	bool found = false;
	पूर्णांक i;

	अगर (!sband)
		वापस;

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		अगर (sband->channels[i].flags & IEEE80211_CHAN_DISABLED)
			जारी;

		found = true;
		अवरोध;
	पूर्ण

	अगर (found) अणु
		phy->chandef.chan = &sband->channels[0];
		phy->chan_state = &msband->chan[0];
		वापस;
	पूर्ण

	sband->n_channels = 0;
	phy->hw->wiphy->bands[band] = शून्य;
पूर्ण

अटल व्योम
mt76_phy_init(काष्ठा mt76_phy *phy, काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा wiphy *wiphy = hw->wiphy;

	SET_IEEE80211_DEV(hw, dev->dev);
	SET_IEEE80211_PERM_ADDR(hw, phy->macaddr);

	wiphy->features |= NL80211_FEATURE_ACTIVE_MONITOR;
	wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH |
			WIPHY_FLAG_SUPPORTS_TDLS |
			WIPHY_FLAG_AP_UAPSD;

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_AIRTIME_FAIRNESS);
	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_AQL);

	wiphy->available_antennas_tx = dev->phy.antenna_mask;
	wiphy->available_antennas_rx = dev->phy.antenna_mask;

	hw->txq_data_size = माप(काष्ठा mt76_txq);
	hw->uapsd_max_sp_len = IEEE80211_WMM_IE_STA_QOSINFO_SP_ALL;

	अगर (!hw->max_tx_fragments)
		hw->max_tx_fragments = 16;

	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPORTS_CLONED_SKBS);
	ieee80211_hw_set(hw, SUPPORTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, SUPPORTS_REORDERING_BUFFER);

	अगर (!(dev->drv->drv_flags & MT_DRV_AMSDU_OFFLOAD)) अणु
		ieee80211_hw_set(hw, TX_AMSDU);
		ieee80211_hw_set(hw, TX_FRAG_LIST);
	पूर्ण

	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, AP_LINK_PS);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);

	wiphy->flags |= WIPHY_FLAG_IBSS_RSN;
	wiphy->पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_AP) |
#अगर_घोषित CONFIG_MAC80211_MESH
		BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
		BIT(NL80211_IFTYPE_P2P_CLIENT) |
		BIT(NL80211_IFTYPE_P2P_GO) |
		BIT(NL80211_IFTYPE_ADHOC);
पूर्ण

काष्ठा mt76_phy *
mt76_alloc_phy(काष्ठा mt76_dev *dev, अचिन्हित पूर्णांक size,
	       स्थिर काष्ठा ieee80211_ops *ops)
अणु
	काष्ठा ieee80211_hw *hw;
	अचिन्हित पूर्णांक phy_size;
	काष्ठा mt76_phy *phy;

	phy_size = ALIGN(माप(*phy), 8);
	hw = ieee80211_alloc_hw(size + phy_size, ops);
	अगर (!hw)
		वापस शून्य;

	phy = hw->priv;
	phy->dev = dev;
	phy->hw = hw;
	phy->priv = hw->priv + phy_size;

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_alloc_phy);

पूर्णांक mt76_रेजिस्टर_phy(काष्ठा mt76_phy *phy, bool vht,
		      काष्ठा ieee80211_rate *rates, पूर्णांक n_rates)
अणु
	पूर्णांक ret;

	mt76_phy_init(phy, phy->hw);

	अगर (phy->cap.has_2ghz) अणु
		ret = mt76_init_sband_2g(phy, rates, n_rates);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (phy->cap.has_5ghz) अणु
		ret = mt76_init_sband_5g(phy, rates + 4, n_rates - 4, vht);
		अगर (ret)
			वापस ret;
	पूर्ण

	wiphy_पढ़ो_of_freq_limits(phy->hw->wiphy);
	mt76_check_sband(phy, &phy->sband_2g, NL80211_BAND_2GHZ);
	mt76_check_sband(phy, &phy->sband_5g, NL80211_BAND_5GHZ);

	ret = ieee80211_रेजिस्टर_hw(phy->hw);
	अगर (ret)
		वापस ret;

	phy->dev->phy2 = phy;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_रेजिस्टर_phy);

व्योम mt76_unरेजिस्टर_phy(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_dev *dev = phy->dev;

	mt76_tx_status_check(dev, शून्य, true);
	ieee80211_unरेजिस्टर_hw(phy->hw);
	dev->phy2 = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_unरेजिस्टर_phy);

काष्ठा mt76_dev *
mt76_alloc_device(काष्ठा device *pdev, अचिन्हित पूर्णांक size,
		  स्थिर काष्ठा ieee80211_ops *ops,
		  स्थिर काष्ठा mt76_driver_ops *drv_ops)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा mt76_phy *phy;
	काष्ठा mt76_dev *dev;
	पूर्णांक i;

	hw = ieee80211_alloc_hw(size, ops);
	अगर (!hw)
		वापस शून्य;

	dev = hw->priv;
	dev->hw = hw;
	dev->dev = pdev;
	dev->drv = drv_ops;

	phy = &dev->phy;
	phy->dev = dev;
	phy->hw = hw;

	spin_lock_init(&dev->rx_lock);
	spin_lock_init(&dev->lock);
	spin_lock_init(&dev->cc_lock);
	mutex_init(&dev->mutex);
	init_रुकोqueue_head(&dev->tx_रुको);
	skb_queue_head_init(&dev->status_list);

	skb_queue_head_init(&dev->mcu.res_q);
	init_रुकोqueue_head(&dev->mcu.रुको);
	mutex_init(&dev->mcu.mutex);
	dev->tx_worker.fn = mt76_tx_worker;

	spin_lock_init(&dev->token_lock);
	idr_init(&dev->token);

	INIT_LIST_HEAD(&dev->txwi_cache);

	क्रम (i = 0; i < ARRAY_SIZE(dev->q_rx); i++)
		skb_queue_head_init(&dev->rx_skb[i]);

	dev->wq = alloc_ordered_workqueue("mt76", 0);
	अगर (!dev->wq) अणु
		ieee80211_मुक्त_hw(hw);
		वापस शून्य;
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_alloc_device);

पूर्णांक mt76_रेजिस्टर_device(काष्ठा mt76_dev *dev, bool vht,
			 काष्ठा ieee80211_rate *rates, पूर्णांक n_rates)
अणु
	काष्ठा ieee80211_hw *hw = dev->hw;
	काष्ठा mt76_phy *phy = &dev->phy;
	पूर्णांक ret;

	dev_set_drvdata(dev->dev, dev);
	mt76_phy_init(phy, hw);

	अगर (phy->cap.has_2ghz) अणु
		ret = mt76_init_sband_2g(phy, rates, n_rates);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (phy->cap.has_5ghz) अणु
		ret = mt76_init_sband_5g(phy, rates + 4, n_rates - 4, vht);
		अगर (ret)
			वापस ret;
	पूर्ण

	wiphy_पढ़ो_of_freq_limits(hw->wiphy);
	mt76_check_sband(&dev->phy, &phy->sband_2g, NL80211_BAND_2GHZ);
	mt76_check_sband(&dev->phy, &phy->sband_5g, NL80211_BAND_5GHZ);

	अगर (IS_ENABLED(CONFIG_MT76_LEDS)) अणु
		ret = mt76_led_init(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = ieee80211_रेजिस्टर_hw(hw);
	अगर (ret)
		वापस ret;

	WARN_ON(mt76_worker_setup(hw, &dev->tx_worker, शून्य, "tx"));
	sched_set_fअगरo_low(dev->tx_worker.task);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_रेजिस्टर_device);

व्योम mt76_unरेजिस्टर_device(काष्ठा mt76_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = dev->hw;

	अगर (IS_ENABLED(CONFIG_MT76_LEDS))
		mt76_led_cleanup(dev);
	mt76_tx_status_check(dev, शून्य, true);
	ieee80211_unरेजिस्टर_hw(hw);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_unरेजिस्टर_device);

व्योम mt76_मुक्त_device(काष्ठा mt76_dev *dev)
अणु
	mt76_worker_tearकरोwn(&dev->tx_worker);
	अगर (dev->wq) अणु
		destroy_workqueue(dev->wq);
		dev->wq = शून्य;
	पूर्ण
	ieee80211_मुक्त_hw(dev->hw);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_मुक्त_device);

अटल व्योम mt76_rx_release_amsdu(काष्ठा mt76_phy *phy, क्रमागत mt76_rxq_id q)
अणु
	काष्ठा sk_buff *skb = phy->rx_amsdu[q].head;
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt76_dev *dev = phy->dev;

	phy->rx_amsdu[q].head = शून्य;
	phy->rx_amsdu[q].tail = शून्य;

	/*
	 * Validate अगर the amsdu has a proper first subframe.
	 * A single MSDU can be parsed as A-MSDU when the unauthenticated A-MSDU
	 * flag of the QoS header माला_लो flipped. In such हालs, the first
	 * subframe has a LLC/SNAP header in the location of the destination
	 * address.
	 */
	अगर (skb_shinfo(skb)->frag_list) अणु
		पूर्णांक offset = 0;

		अगर (!(status->flag & RX_FLAG_8023)) अणु
			offset = ieee80211_get_hdrlen_from_skb(skb);

			अगर ((status->flag &
			     (RX_FLAG_DECRYPTED | RX_FLAG_IV_STRIPPED)) ==
			    RX_FLAG_DECRYPTED)
				offset += 8;
		पूर्ण

		अगर (ether_addr_equal(skb->data + offset, rfc1042_header)) अणु
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण
	__skb_queue_tail(&dev->rx_skb[q], skb);
पूर्ण

अटल व्योम mt76_rx_release_burst(काष्ठा mt76_phy *phy, क्रमागत mt76_rxq_id q,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;

	अगर (phy->rx_amsdu[q].head &&
	    (!status->amsdu || status->first_amsdu ||
	     status->seqno != phy->rx_amsdu[q].seqno))
		mt76_rx_release_amsdu(phy, q);

	अगर (!phy->rx_amsdu[q].head) अणु
		phy->rx_amsdu[q].tail = &skb_shinfo(skb)->frag_list;
		phy->rx_amsdu[q].seqno = status->seqno;
		phy->rx_amsdu[q].head = skb;
	पूर्ण अन्यथा अणु
		*phy->rx_amsdu[q].tail = skb;
		phy->rx_amsdu[q].tail = &skb->next;
	पूर्ण

	अगर (!status->amsdu || status->last_amsdu)
		mt76_rx_release_amsdu(phy, q);
पूर्ण

व्योम mt76_rx(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id q, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt76_phy *phy = mt76_dev_phy(dev, status->ext_phy);

	अगर (!test_bit(MT76_STATE_RUNNING, &phy->state)) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE
	अगर (phy->test.state == MT76_TM_STATE_RX_FRAMES) अणु
		phy->test.rx_stats.packets[q]++;
		अगर (status->flag & RX_FLAG_FAILED_FCS_CRC)
			phy->test.rx_stats.fcs_error[q]++;
	पूर्ण
#पूर्ण_अगर

	mt76_rx_release_burst(phy, q, skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_rx);

bool mt76_has_tx_pending(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_queue *q;
	पूर्णांक i;

	क्रम (i = 0; i < __MT_TXQ_MAX; i++) अणु
		q = phy->q_tx[i];
		अगर (q && q->queued)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_has_tx_pending);

अटल काष्ठा mt76_channel_state *
mt76_channel_state(काष्ठा mt76_phy *phy, काष्ठा ieee80211_channel *c)
अणु
	काष्ठा mt76_sband *msband;
	पूर्णांक idx;

	अगर (c->band == NL80211_BAND_2GHZ)
		msband = &phy->sband_2g;
	अन्यथा
		msband = &phy->sband_5g;

	idx = c - &msband->sband.channels[0];
	वापस &msband->chan[idx];
पूर्ण

व्योम mt76_update_survey_active_समय(काष्ठा mt76_phy *phy, kसमय_प्रकार समय)
अणु
	काष्ठा mt76_channel_state *state = phy->chan_state;

	state->cc_active += kसमय_प्रकारo_us(kसमय_sub(समय,
						  phy->survey_समय));
	phy->survey_समय = समय;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_update_survey_active_समय);

व्योम mt76_update_survey(काष्ठा mt76_dev *dev)
अणु
	kसमय_प्रकार cur_समय;

	अगर (dev->drv->update_survey)
		dev->drv->update_survey(dev);

	cur_समय = kसमय_get_bootसमय();
	mt76_update_survey_active_समय(&dev->phy, cur_समय);
	अगर (dev->phy2)
		mt76_update_survey_active_समय(dev->phy2, cur_समय);

	अगर (dev->drv->drv_flags & MT_DRV_SW_RX_AIRTIME) अणु
		काष्ठा mt76_channel_state *state = dev->phy.chan_state;

		spin_lock_bh(&dev->cc_lock);
		state->cc_bss_rx += dev->cur_cc_bss_rx;
		dev->cur_cc_bss_rx = 0;
		spin_unlock_bh(&dev->cc_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76_update_survey);

व्योम mt76_set_channel(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा ieee80211_hw *hw = phy->hw;
	काष्ठा cfg80211_chan_def *chandef = &hw->conf.chandef;
	bool offchannel = hw->conf.flags & IEEE80211_CONF_OFFCHANNEL;
	पूर्णांक समयout = HZ / 5;

	रुको_event_समयout(dev->tx_रुको, !mt76_has_tx_pending(phy), समयout);
	mt76_update_survey(dev);

	phy->chandef = *chandef;
	phy->chan_state = mt76_channel_state(phy, chandef->chan);

	अगर (!offchannel)
		phy->मुख्य_chan = chandef->chan;

	अगर (chandef->chan != phy->मुख्य_chan)
		स_रखो(phy->chan_state, 0, माप(*phy->chan_state));
पूर्ण
EXPORT_SYMBOL_GPL(mt76_set_channel);

पूर्णांक mt76_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
		    काष्ठा survey_info *survey)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा mt76_sband *sband;
	काष्ठा ieee80211_channel *chan;
	काष्ठा mt76_channel_state *state;
	पूर्णांक ret = 0;

	mutex_lock(&dev->mutex);
	अगर (idx == 0 && dev->drv->update_survey)
		mt76_update_survey(dev);

	sband = &phy->sband_2g;
	अगर (idx >= sband->sband.n_channels) अणु
		idx -= sband->sband.n_channels;
		sband = &phy->sband_5g;
	पूर्ण

	अगर (idx >= sband->sband.n_channels) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	chan = &sband->sband.channels[idx];
	state = mt76_channel_state(phy, chan);

	स_रखो(survey, 0, माप(*survey));
	survey->channel = chan;
	survey->filled = SURVEY_INFO_TIME | SURVEY_INFO_TIME_BUSY;
	survey->filled |= dev->drv->survey_flags;
	अगर (state->noise)
		survey->filled |= SURVEY_INFO_NOISE_DBM;

	अगर (chan == phy->मुख्य_chan) अणु
		survey->filled |= SURVEY_INFO_IN_USE;

		अगर (dev->drv->drv_flags & MT_DRV_SW_RX_AIRTIME)
			survey->filled |= SURVEY_INFO_TIME_BSS_RX;
	पूर्ण

	survey->समय_busy = भाग_u64(state->cc_busy, 1000);
	survey->समय_rx = भाग_u64(state->cc_rx, 1000);
	survey->समय = भाग_u64(state->cc_active, 1000);
	survey->noise = state->noise;

	spin_lock_bh(&dev->cc_lock);
	survey->समय_bss_rx = भाग_u64(state->cc_bss_rx, 1000);
	survey->समय_प्रकारx = भाग_u64(state->cc_tx, 1000);
	spin_unlock_bh(&dev->cc_lock);

out:
	mutex_unlock(&dev->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_get_survey);

व्योम mt76_wcid_key_setup(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid,
			 काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ieee80211_key_seq seq;
	पूर्णांक i;

	wcid->rx_check_pn = false;

	अगर (!key)
		वापस;

	अगर (key->cipher != WLAN_CIPHER_SUITE_CCMP)
		वापस;

	wcid->rx_check_pn = true;
	क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++) अणु
		ieee80211_get_key_rx_seq(key, i, &seq);
		स_नकल(wcid->rx_key_pn[i], seq.ccmp.pn, माप(seq.ccmp.pn));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mt76_wcid_key_setup);

अटल व्योम
mt76_rx_convert(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
		काष्ठा ieee80211_hw **hw,
		काष्ठा ieee80211_sta **sta)
अणु
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा mt76_rx_status mstat;

	mstat = *((काष्ठा mt76_rx_status *)skb->cb);
	स_रखो(status, 0, माप(*status));

	status->flag = mstat.flag;
	status->freq = mstat.freq;
	status->enc_flags = mstat.enc_flags;
	status->encoding = mstat.encoding;
	status->bw = mstat.bw;
	status->he_ru = mस्थिति.सe_ru;
	status->he_gi = mस्थिति.सe_gi;
	status->he_dcm = mस्थिति.सe_dcm;
	status->rate_idx = mstat.rate_idx;
	status->nss = mstat.nss;
	status->band = mstat.band;
	status->संकेत = mstat.संकेत;
	status->chains = mstat.chains;
	status->ampdu_reference = mstat.ampdu_ref;
	status->device_बारtamp = mstat.बारtamp;
	status->maस_समय = mstat.बारtamp;

	BUILD_BUG_ON(माप(mstat) > माप(skb->cb));
	BUILD_BUG_ON(माप(status->chain_संकेत) !=
		     माप(mstat.chain_संकेत));
	स_नकल(status->chain_संकेत, mstat.chain_संकेत,
	       माप(mstat.chain_संकेत));

	*sta = wcid_to_sta(mstat.wcid);
	*hw = mt76_phy_hw(dev, mstat.ext_phy);
पूर्ण

अटल पूर्णांक
mt76_check_ccmp_pn(काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt76_wcid *wcid = status->wcid;
	काष्ठा ieee80211_hdr *hdr;
	u8 tidno = status->qos_ctl & IEEE80211_QOS_CTL_TID_MASK;
	पूर्णांक ret;

	अगर (!(status->flag & RX_FLAG_DECRYPTED))
		वापस 0;

	अगर (!wcid || !wcid->rx_check_pn)
		वापस 0;

	अगर (!(status->flag & RX_FLAG_IV_STRIPPED)) अणु
		/*
		 * Validate the first fragment both here and in mac80211
		 * All further fragments will be validated by mac80211 only.
		 */
		hdr = mt76_skb_get_hdr(skb);
		अगर (ieee80211_is_frag(hdr) &&
		    !ieee80211_is_first_frag(hdr->frame_control))
			वापस 0;
	पूर्ण

	BUILD_BUG_ON(माप(status->iv) != माप(wcid->rx_key_pn[0]));
	ret = स_भेद(status->iv, wcid->rx_key_pn[tidno],
		     माप(status->iv));
	अगर (ret <= 0)
		वापस -EINVAL; /* replay */

	स_नकल(wcid->rx_key_pn[tidno], status->iv, माप(status->iv));

	अगर (status->flag & RX_FLAG_IV_STRIPPED)
		status->flag |= RX_FLAG_PN_VALIDATED;

	वापस 0;
पूर्ण

अटल व्योम
mt76_airसमय_report(काष्ठा mt76_dev *dev, काष्ठा mt76_rx_status *status,
		    पूर्णांक len)
अणु
	काष्ठा mt76_wcid *wcid = status->wcid;
	काष्ठा ieee80211_rx_status info = अणु
		.enc_flags = status->enc_flags,
		.rate_idx = status->rate_idx,
		.encoding = status->encoding,
		.band = status->band,
		.nss = status->nss,
		.bw = status->bw,
	पूर्ण;
	काष्ठा ieee80211_sta *sta;
	u32 airसमय;
	u8 tidno = status->qos_ctl & IEEE80211_QOS_CTL_TID_MASK;

	airसमय = ieee80211_calc_rx_airसमय(dev->hw, &info, len);
	spin_lock(&dev->cc_lock);
	dev->cur_cc_bss_rx += airसमय;
	spin_unlock(&dev->cc_lock);

	अगर (!wcid || !wcid->sta)
		वापस;

	sta = container_of((व्योम *)wcid, काष्ठा ieee80211_sta, drv_priv);
	ieee80211_sta_रेजिस्टर_airसमय(sta, tidno, 0, airसमय);
पूर्ण

अटल व्योम
mt76_airसमय_flush_ampdu(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_wcid *wcid;
	पूर्णांक wcid_idx;

	अगर (!dev->rx_ampdu_len)
		वापस;

	wcid_idx = dev->rx_ampdu_status.wcid_idx;
	अगर (wcid_idx < ARRAY_SIZE(dev->wcid))
		wcid = rcu_dereference(dev->wcid[wcid_idx]);
	अन्यथा
		wcid = शून्य;
	dev->rx_ampdu_status.wcid = wcid;

	mt76_airसमय_report(dev, &dev->rx_ampdu_status, dev->rx_ampdu_len);

	dev->rx_ampdu_len = 0;
	dev->rx_ampdu_ref = 0;
पूर्ण

अटल व्योम
mt76_airसमय_check(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt76_wcid *wcid = status->wcid;

	अगर (!(dev->drv->drv_flags & MT_DRV_SW_RX_AIRTIME))
		वापस;

	अगर (!wcid || !wcid->sta) अणु
		काष्ठा ieee80211_hdr *hdr = mt76_skb_get_hdr(skb);

		अगर (status->flag & RX_FLAG_8023)
			वापस;

		अगर (!ether_addr_equal(hdr->addr1, dev->phy.macaddr))
			वापस;

		wcid = शून्य;
	पूर्ण

	अगर (!(status->flag & RX_FLAG_AMPDU_DETAILS) ||
	    status->ampdu_ref != dev->rx_ampdu_ref)
		mt76_airसमय_flush_ampdu(dev);

	अगर (status->flag & RX_FLAG_AMPDU_DETAILS) अणु
		अगर (!dev->rx_ampdu_len ||
		    status->ampdu_ref != dev->rx_ampdu_ref) अणु
			dev->rx_ampdu_status = *status;
			dev->rx_ampdu_status.wcid_idx = wcid ? wcid->idx : 0xff;
			dev->rx_ampdu_ref = status->ampdu_ref;
		पूर्ण

		dev->rx_ampdu_len += skb->len;
		वापस;
	पूर्ण

	mt76_airसमय_report(dev, status, skb->len);
पूर्ण

अटल व्योम
mt76_check_sta(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा ieee80211_hdr *hdr = mt76_skb_get_hdr(skb);
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_hw *hw;
	काष्ठा mt76_wcid *wcid = status->wcid;
	u8 tidno = status->qos_ctl & IEEE80211_QOS_CTL_TID_MASK;
	bool ps;

	hw = mt76_phy_hw(dev, status->ext_phy);
	अगर (ieee80211_is_pspoll(hdr->frame_control) && !wcid &&
	    !(status->flag & RX_FLAG_8023)) अणु
		sta = ieee80211_find_sta_by_अगरaddr(hw, hdr->addr2, शून्य);
		अगर (sta)
			wcid = status->wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
	पूर्ण

	mt76_airसमय_check(dev, skb);

	अगर (!wcid || !wcid->sta)
		वापस;

	sta = container_of((व्योम *)wcid, काष्ठा ieee80211_sta, drv_priv);

	अगर (status->संकेत <= 0)
		ewma_संकेत_add(&wcid->rssi, -status->संकेत);

	wcid->inactive_count = 0;

	अगर (status->flag & RX_FLAG_8023)
		वापस;

	अगर (!test_bit(MT_WCID_FLAG_CHECK_PS, &wcid->flags))
		वापस;

	अगर (ieee80211_is_pspoll(hdr->frame_control)) अणु
		ieee80211_sta_pspoll(sta);
		वापस;
	पूर्ण

	अगर (ieee80211_has_morefrags(hdr->frame_control) ||
	    !(ieee80211_is_mgmt(hdr->frame_control) ||
	      ieee80211_is_data(hdr->frame_control)))
		वापस;

	ps = ieee80211_has_pm(hdr->frame_control);

	अगर (ps && (ieee80211_is_data_qos(hdr->frame_control) ||
		   ieee80211_is_qos_nullfunc(hdr->frame_control)))
		ieee80211_sta_uapsd_trigger(sta, tidno);

	अगर (!!test_bit(MT_WCID_FLAG_PS, &wcid->flags) == ps)
		वापस;

	अगर (ps)
		set_bit(MT_WCID_FLAG_PS, &wcid->flags);
	अन्यथा
		clear_bit(MT_WCID_FLAG_PS, &wcid->flags);

	dev->drv->sta_ps(dev, sta, ps);
	ieee80211_sta_ps_transition(sta, ps);
पूर्ण

व्योम mt76_rx_complete(काष्ठा mt76_dev *dev, काष्ठा sk_buff_head *frames,
		      काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_hw *hw;
	काष्ठा sk_buff *skb, *पंचांगp;
	LIST_HEAD(list);

	spin_lock(&dev->rx_lock);
	जबतक ((skb = __skb_dequeue(frames)) != शून्य) अणु
		काष्ठा sk_buff *nskb = skb_shinfo(skb)->frag_list;

		अगर (mt76_check_ccmp_pn(skb)) अणु
			dev_kमुक्त_skb(skb);
			जारी;
		पूर्ण

		skb_shinfo(skb)->frag_list = शून्य;
		mt76_rx_convert(dev, skb, &hw, &sta);
		ieee80211_rx_list(hw, sta, skb, &list);

		/* subsequent amsdu frames */
		जबतक (nskb) अणु
			skb = nskb;
			nskb = nskb->next;
			skb->next = शून्य;

			mt76_rx_convert(dev, skb, &hw, &sta);
			ieee80211_rx_list(hw, sta, skb, &list);
		पूर्ण
	पूर्ण
	spin_unlock(&dev->rx_lock);

	अगर (!napi) अणु
		netअगर_receive_skb_list(&list);
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(skb, पंचांगp, &list, list) अणु
		skb_list_del_init(skb);
		napi_gro_receive(napi, skb);
	पूर्ण
पूर्ण

व्योम mt76_rx_poll_complete(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id q,
			   काष्ठा napi_काष्ठा *napi)
अणु
	काष्ठा sk_buff_head frames;
	काष्ठा sk_buff *skb;

	__skb_queue_head_init(&frames);

	जबतक ((skb = __skb_dequeue(&dev->rx_skb[q])) != शून्य) अणु
		mt76_check_sta(dev, skb);
		mt76_rx_aggr_reorder(skb, &frames);
	पूर्ण

	mt76_rx_complete(dev, &frames, napi);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_rx_poll_complete);

अटल पूर्णांक
mt76_sta_add(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
	     काष्ठा ieee80211_sta *sta, bool ext_phy)
अणु
	काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&dev->mutex);

	ret = dev->drv->sta_add(dev, vअगर, sta);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(sta->txq); i++) अणु
		काष्ठा mt76_txq *mtxq;

		अगर (!sta->txq[i])
			जारी;

		mtxq = (काष्ठा mt76_txq *)sta->txq[i]->drv_priv;
		mtxq->wcid = wcid;
	पूर्ण

	ewma_संकेत_init(&wcid->rssi);
	अगर (ext_phy)
		mt76_wcid_mask_set(dev->wcid_phy_mask, wcid->idx);
	wcid->ext_phy = ext_phy;
	rcu_assign_poपूर्णांकer(dev->wcid[wcid->idx], wcid);

out:
	mutex_unlock(&dev->mutex);

	वापस ret;
पूर्ण

व्योम __mt76_sta_हटाओ(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
	पूर्णांक i, idx = wcid->idx;

	क्रम (i = 0; i < ARRAY_SIZE(wcid->aggr); i++)
		mt76_rx_aggr_stop(dev, wcid, i);

	अगर (dev->drv->sta_हटाओ)
		dev->drv->sta_हटाओ(dev, vअगर, sta);

	mt76_tx_status_check(dev, wcid, true);
	mt76_wcid_mask_clear(dev->wcid_mask, idx);
	mt76_wcid_mask_clear(dev->wcid_phy_mask, idx);
पूर्ण
EXPORT_SYMBOL_GPL(__mt76_sta_हटाओ);

अटल व्योम
mt76_sta_हटाओ(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		काष्ठा ieee80211_sta *sta)
अणु
	mutex_lock(&dev->mutex);
	__mt76_sta_हटाओ(dev, vअगर, sta);
	mutex_unlock(&dev->mutex);
पूर्ण

पूर्णांक mt76_sta_state(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta,
		   क्रमागत ieee80211_sta_state old_state,
		   क्रमागत ieee80211_sta_state new_state)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा mt76_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;

	अगर (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE)
		वापस mt76_sta_add(dev, vअगर, sta, ext_phy);

	अगर (old_state == IEEE80211_STA_AUTH &&
	    new_state == IEEE80211_STA_ASSOC &&
	    dev->drv->sta_assoc)
		dev->drv->sta_assoc(dev, vअगर, sta);

	अगर (old_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST)
		mt76_sta_हटाओ(dev, vअगर, sta);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_sta_state);

व्योम mt76_sta_pre_rcu_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;

	mutex_lock(&dev->mutex);
	rcu_assign_poपूर्णांकer(dev->wcid[wcid->idx], शून्य);
	mutex_unlock(&dev->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_sta_pre_rcu_हटाओ);

पूर्णांक mt76_get_txघातer(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		     पूर्णांक *dbm)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	पूर्णांक n_chains = hweight8(phy->antenna_mask);
	पूर्णांक delta = mt76_tx_घातer_nss_delta(n_chains);

	*dbm = DIV_ROUND_UP(phy->txघातer_cur + delta, 2);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_get_txघातer);

अटल व्योम
__mt76_csa_finish(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (vअगर->csa_active && ieee80211_beacon_cntdwn_is_complete(vअगर))
		ieee80211_csa_finish(vअगर);
पूर्ण

व्योम mt76_csa_finish(काष्ठा mt76_dev *dev)
अणु
	अगर (!dev->csa_complete)
		वापस;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(dev->hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		__mt76_csa_finish, dev);

	dev->csa_complete = 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_csa_finish);

अटल व्योम
__mt76_csa_check(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76_dev *dev = priv;

	अगर (!vअगर->csa_active)
		वापस;

	dev->csa_complete |= ieee80211_beacon_cntdwn_is_complete(vअगर);
पूर्ण

व्योम mt76_csa_check(काष्ठा mt76_dev *dev)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(dev->hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		__mt76_csa_check, dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_csa_check);

पूर्णांक
mt76_set_tim(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta, bool set)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_set_tim);

व्योम mt76_insert_ccmp_hdr(काष्ठा sk_buff *skb, u8 key_id)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	पूर्णांक hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	u8 *hdr, *pn = status->iv;

	__skb_push(skb, 8);
	स_हटाओ(skb->data, skb->data + 8, hdr_len);
	hdr = skb->data + hdr_len;

	hdr[0] = pn[5];
	hdr[1] = pn[4];
	hdr[2] = 0;
	hdr[3] = 0x20 | (key_id << 6);
	hdr[4] = pn[3];
	hdr[5] = pn[2];
	hdr[6] = pn[1];
	hdr[7] = pn[0];

	status->flag &= ~RX_FLAG_IV_STRIPPED;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_insert_ccmp_hdr);

पूर्णांक mt76_get_rate(काष्ठा mt76_dev *dev,
		  काष्ठा ieee80211_supported_band *sband,
		  पूर्णांक idx, bool cck)
अणु
	पूर्णांक i, offset = 0, len = sband->n_bitrates;

	अगर (cck) अणु
		अगर (sband == &dev->phy.sband_5g.sband)
			वापस 0;

		idx &= ~BIT(2); /* लघु preamble */
	पूर्ण अन्यथा अगर (sband == &dev->phy.sband_2g.sband) अणु
		offset = 4;
	पूर्ण

	क्रम (i = offset; i < len; i++) अणु
		अगर ((sband->bitrates[i].hw_value & GENMASK(7, 0)) == idx)
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_get_rate);

व्योम mt76_sw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  स्थिर u8 *mac)
अणु
	काष्ठा mt76_phy *phy = hw->priv;

	set_bit(MT76_SCANNING, &phy->state);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_sw_scan);

व्योम mt76_sw_scan_complete(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76_phy *phy = hw->priv;

	clear_bit(MT76_SCANNING, &phy->state);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_sw_scan_complete);

पूर्णांक mt76_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा mt76_dev *dev = phy->dev;

	mutex_lock(&dev->mutex);
	*tx_ant = phy->antenna_mask;
	*rx_ant = phy->antenna_mask;
	mutex_unlock(&dev->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_get_antenna);

काष्ठा mt76_queue *
mt76_init_queue(काष्ठा mt76_dev *dev, पूर्णांक qid, पूर्णांक idx, पूर्णांक n_desc,
		पूर्णांक ring_base)
अणु
	काष्ठा mt76_queue *hwq;
	पूर्णांक err;

	hwq = devm_kzalloc(dev->dev, माप(*hwq), GFP_KERNEL);
	अगर (!hwq)
		वापस ERR_PTR(-ENOMEM);

	err = dev->queue_ops->alloc(dev, hwq, idx, n_desc, 0, ring_base);
	अगर (err < 0)
		वापस ERR_PTR(err);

	वापस hwq;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_init_queue);
