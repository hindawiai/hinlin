<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/module.h>
#समावेश "mt76x02.h"

#घोषणा CCK_RATE(_idx, _rate) अणु					\
	.bitrate = _rate,					\
	.flags = IEEE80211_RATE_SHORT_PREAMBLE,			\
	.hw_value = (MT_PHY_TYPE_CCK << 8) | (_idx),		\
	.hw_value_लघु = (MT_PHY_TYPE_CCK << 8) | (8 + (_idx)),	\
पूर्ण

#घोषणा OFDM_RATE(_idx, _rate) अणु				\
	.bitrate = _rate,					\
	.hw_value = (MT_PHY_TYPE_OFDM << 8) | (_idx),		\
	.hw_value_लघु = (MT_PHY_TYPE_OFDM << 8) | (_idx),	\
पूर्ण

काष्ठा ieee80211_rate mt76x02_rates[] = अणु
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
EXPORT_SYMBOL_GPL(mt76x02_rates);

अटल स्थिर काष्ठा ieee80211_अगरace_limit mt76x02_अगर_limits[] = अणु
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_ADHOC)
	पूर्ण, अणु
		.max = 8,
		.types = BIT(NL80211_IFTYPE_STATION) |
#अगर_घोषित CONFIG_MAC80211_MESH
			 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
			 BIT(NL80211_IFTYPE_P2P_CLIENT) |
			 BIT(NL80211_IFTYPE_P2P_GO) |
			 BIT(NL80211_IFTYPE_AP)
	 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit mt76x02u_अगर_limits[] = अणु
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_ADHOC)
	पूर्ण, अणु
		.max = 2,
		.types = BIT(NL80211_IFTYPE_STATION) |
#अगर_घोषित CONFIG_MAC80211_MESH
			 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
			 BIT(NL80211_IFTYPE_P2P_CLIENT) |
			 BIT(NL80211_IFTYPE_P2P_GO) |
			 BIT(NL80211_IFTYPE_AP)
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination mt76x02_अगर_comb[] = अणु
	अणु
		.limits = mt76x02_अगर_limits,
		.n_limits = ARRAY_SIZE(mt76x02_अगर_limits),
		.max_पूर्णांकerfaces = 8,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
		.radar_detect_widths = BIT(NL80211_CHAN_WIDTH_20_NOHT) |
				       BIT(NL80211_CHAN_WIDTH_20) |
				       BIT(NL80211_CHAN_WIDTH_40) |
				       BIT(NL80211_CHAN_WIDTH_80),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination mt76x02u_अगर_comb[] = अणु
	अणु
		.limits = mt76x02u_अगर_limits,
		.n_limits = ARRAY_SIZE(mt76x02u_अगर_limits),
		.max_पूर्णांकerfaces = 2,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
	पूर्ण
पूर्ण;

अटल व्योम
mt76x02_led_set_config(काष्ठा mt76_dev *mdev, u8 delay_on,
		       u8 delay_off)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev,
					       mt76);
	u32 val;

	val = FIELD_PREP(MT_LED_STATUS_DURATION, 0xff) |
	      FIELD_PREP(MT_LED_STATUS_OFF, delay_off) |
	      FIELD_PREP(MT_LED_STATUS_ON, delay_on);

	mt76_wr(dev, MT_LED_S0(mdev->led_pin), val);
	mt76_wr(dev, MT_LED_S1(mdev->led_pin), val);

	val = MT_LED_CTRL_REPLAY(mdev->led_pin) |
	      MT_LED_CTRL_KICK(mdev->led_pin);
	अगर (mdev->led_al)
		val |= MT_LED_CTRL_POLARITY(mdev->led_pin);
	mt76_wr(dev, MT_LED_CTRL, val);
पूर्ण

अटल पूर्णांक
mt76x02_led_set_blink(काष्ठा led_classdev *led_cdev,
		      अचिन्हित दीर्घ *delay_on,
		      अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा mt76_dev *mdev = container_of(led_cdev, काष्ठा mt76_dev,
					     led_cdev);
	u8 delta_on, delta_off;

	delta_off = max_t(u8, *delay_off / 10, 1);
	delta_on = max_t(u8, *delay_on / 10, 1);

	mt76x02_led_set_config(mdev, delta_on, delta_off);

	वापस 0;
पूर्ण

अटल व्योम
mt76x02_led_set_brightness(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness brightness)
अणु
	काष्ठा mt76_dev *mdev = container_of(led_cdev, काष्ठा mt76_dev,
					     led_cdev);

	अगर (!brightness)
		mt76x02_led_set_config(mdev, 0, 0xff);
	अन्यथा
		mt76x02_led_set_config(mdev, 0xff, 0);
पूर्ण

व्योम mt76x02_init_device(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	काष्ठा wiphy *wiphy = hw->wiphy;

	INIT_DELAYED_WORK(&dev->mphy.mac_work, mt76x02_mac_work);

	hw->queues = 4;
	hw->max_rates = 1;
	hw->max_report_rates = 7;
	hw->max_rate_tries = 1;
	hw->extra_tx_headroom = 2;

	अगर (mt76_is_usb(&dev->mt76)) अणु
		hw->extra_tx_headroom += माप(काष्ठा mt76x02_txwi) +
					 MT_DMA_HDR_LEN;
		wiphy->अगरace_combinations = mt76x02u_अगर_comb;
		wiphy->n_अगरace_combinations = ARRAY_SIZE(mt76x02u_अगर_comb);
	पूर्ण अन्यथा अणु
		INIT_DELAYED_WORK(&dev->wdt_work, mt76x02_wdt_work);

		mt76x02_dfs_init_detector(dev);

		wiphy->reg_notअगरier = mt76x02_regd_notअगरier;
		wiphy->अगरace_combinations = mt76x02_अगर_comb;
		wiphy->n_अगरace_combinations = ARRAY_SIZE(mt76x02_अगर_comb);

		/* init led callbacks */
		अगर (IS_ENABLED(CONFIG_MT76_LEDS)) अणु
			dev->mt76.led_cdev.brightness_set =
					mt76x02_led_set_brightness;
			dev->mt76.led_cdev.blink_set = mt76x02_led_set_blink;
		पूर्ण
	पूर्ण

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_VHT_IBSS);

	hw->sta_data_size = माप(काष्ठा mt76x02_sta);
	hw->vअगर_data_size = माप(काष्ठा mt76x02_vअगर);

	ieee80211_hw_set(hw, SUPPORTS_HT_CCK_RATES);
	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(hw, NEEDS_UNIQUE_STA_ADDR);

	dev->mt76.global_wcid.idx = 255;
	dev->mt76.global_wcid.hw_key_idx = -1;
	dev->slotसमय = 9;

	अगर (is_mt76x2(dev)) अणु
		dev->mphy.sband_2g.sband.ht_cap.cap |=
				IEEE80211_HT_CAP_LDPC_CODING;
		dev->mphy.sband_5g.sband.ht_cap.cap |=
				IEEE80211_HT_CAP_LDPC_CODING;
		dev->mphy.chainmask = 0x202;
		dev->mphy.antenna_mask = 3;
	पूर्ण अन्यथा अणु
		dev->mphy.chainmask = 0x101;
		dev->mphy.antenna_mask = 1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_init_device);

व्योम mt76x02_configure_filter(काष्ठा ieee80211_hw *hw,
			      अचिन्हित पूर्णांक changed_flags,
			      अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	u32 flags = 0;

#घोषणा MT76_FILTER(_flag, _hw) करो अणु \
		flags |= *total_flags & FIF_##_flag;			\
		dev->mt76.rxfilter &= ~(_hw);				\
		dev->mt76.rxfilter |= !(flags & FIF_##_flag) * (_hw);	\
	पूर्ण जबतक (0)

	mutex_lock(&dev->mt76.mutex);

	dev->mt76.rxfilter &= ~MT_RX_FILTR_CFG_OTHER_BSS;

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
	mt76_wr(dev, MT_RX_FILTR_CFG, dev->mt76.rxfilter);

	mutex_unlock(&dev->mt76.mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_configure_filter);

पूर्णांक mt76x02_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	काष्ठा mt76x02_sta *msta = (काष्ठा mt76x02_sta *)sta->drv_priv;
	काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;
	पूर्णांक idx = 0;

	स_रखो(msta, 0, माप(*msta));

	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT76x02_N_WCIDS);
	अगर (idx < 0)
		वापस -ENOSPC;

	msta->vअगर = mvअगर;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.hw_key_idx = -1;
	mt76x02_mac_wcid_setup(dev, idx, mvअगर->idx, sta->addr);
	mt76x02_mac_wcid_set_drop(dev, idx, false);
	ewma_pktlen_init(&msta->pktlen);

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		set_bit(MT_WCID_FLAG_CHECK_PS, &msta->wcid.flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_sta_add);

व्योम mt76x02_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;
	पूर्णांक idx = wcid->idx;

	mt76x02_mac_wcid_set_drop(dev, idx, true);
	mt76x02_mac_wcid_setup(dev, idx, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_sta_हटाओ);

अटल व्योम
mt76x02_vअगर_init(काष्ठा mt76x02_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		 अचिन्हित पूर्णांक idx)
अणु
	काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_txq *mtxq;

	स_रखो(mvअगर, 0, माप(*mvअगर));

	mvअगर->idx = idx;
	mvअगर->group_wcid.idx = MT_VIF_WCID(idx);
	mvअगर->group_wcid.hw_key_idx = -1;
	mtxq = (काष्ठा mt76_txq *)vअगर->txq->drv_priv;
	mtxq->wcid = &mvअगर->group_wcid;
पूर्ण

पूर्णांक
mt76x02_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	अचिन्हित पूर्णांक idx = 0;

	/* Allow to change address in HW अगर we create first पूर्णांकerface. */
	अगर (!dev->mt76.vअगर_mask &&
	    (((vअगर->addr[0] ^ dev->mphy.macaddr[0]) & ~GENMASK(4, 1)) ||
	     स_भेद(vअगर->addr + 1, dev->mphy.macaddr + 1, ETH_ALEN - 1)))
		mt76x02_mac_setaddr(dev, vअगर->addr);

	अगर (vअगर->addr[0] & BIT(1))
		idx = 1 + (((dev->mphy.macaddr[0] ^ vअगर->addr[0]) >> 2) & 7);

	/*
	 * Client mode typically only has one configurable BSSID रेजिस्टर,
	 * which is used क्रम bssidx=0. This is linked to the MAC address.
	 * Since mac80211 allows changing पूर्णांकerface types, and we cannot
	 * क्रमce the use of the primary MAC address क्रम a station mode
	 * पूर्णांकerface, we need some other way of configuring a per-पूर्णांकerface
	 * remote BSSID.
	 * The hardware provides an AP-Client feature, where bssidx 0-7 are
	 * used क्रम AP mode and bssidx 8-15 क्रम client mode.
	 * We shअगरt the station पूर्णांकerface bss index by 8 to क्रमce the
	 * hardware to recognize the BSSID.
	 * The resulting bssidx mismatch क्रम unicast frames is ignored by hw.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		idx += 8;

	/* vअगर is alपढ़ोy set or idx is 8 क्रम AP/Mesh/... */
	अगर (dev->mt76.vअगर_mask & BIT(idx) ||
	    (vअगर->type != NL80211_IFTYPE_STATION && idx > 7))
		वापस -EBUSY;

	dev->mt76.vअगर_mask |= BIT(idx);

	mt76x02_vअगर_init(dev, vअगर, idx);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_add_पूर्णांकerface);

व्योम mt76x02_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;

	dev->mt76.vअगर_mask &= ~BIT(mvअगर->idx);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_हटाओ_पूर्णांकerface);

पूर्णांक mt76x02_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_ampdu_params *params)
अणु
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	काष्ठा ieee80211_sta *sta = params->sta;
	काष्ठा mt76x02_dev *dev = hw->priv;
	काष्ठा mt76x02_sta *msta = (काष्ठा mt76x02_sta *)sta->drv_priv;
	काष्ठा ieee80211_txq *txq = sta->txq[params->tid];
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
		mt76_rx_aggr_start(&dev->mt76, &msta->wcid, tid,
				   ssn, params->buf_size);
		mt76_set(dev, MT_WCID_ADDR(msta->wcid.idx) + 4, BIT(16 + tid));
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		mt76_rx_aggr_stop(&dev->mt76, &msta->wcid, tid);
		mt76_clear(dev, MT_WCID_ADDR(msta->wcid.idx) + 4,
			   BIT(16 + tid));
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		mtxq->aggr = true;
		mtxq->send_bar = false;
		ieee80211_send_bar(vअगर, sta->addr, tid, mtxq->agg_ssn);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		mtxq->aggr = false;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		mtxq->agg_ssn = IEEE80211_SN_TO_SEQ(ssn);
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggr = false;
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	पूर्ण
	mutex_unlock(&dev->mt76.mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_ampdu_action);

पूर्णांक mt76x02_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		    काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		    काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;
	काष्ठा mt76x02_sta *msta;
	काष्ठा mt76_wcid *wcid;
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

	/*
	 * The hardware करोes not support per-STA RX GTK, fall back
	 * to software mode क्रम these.
	 */
	अगर ((vअगर->type == NL80211_IFTYPE_ADHOC ||
	     vअगर->type == NL80211_IFTYPE_MESH_POINT) &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		वापस -EOPNOTSUPP;

	/*
	 * In USB AP mode, broadcast/multicast frames are setup in beacon
	 * data रेजिस्टरs and sent via HW beacons engine, they require to
	 * be alपढ़ोy encrypted.
	 */
	अगर (mt76_is_usb(&dev->mt76) &&
	    vअगर->type == NL80211_IFTYPE_AP &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		वापस -EOPNOTSUPP;

	/* MT76x0 GTK offloading करोes not work with more than one VIF */
	अगर (is_mt76x0(dev) && !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		वापस -EOPNOTSUPP;

	msta = sta ? (काष्ठा mt76x02_sta *)sta->drv_priv : शून्य;
	wcid = msta ? &msta->wcid : &mvअगर->group_wcid;

	अगर (cmd == SET_KEY) अणु
		key->hw_key_idx = wcid->idx;
		wcid->hw_key_idx = idx;
		अगर (key->flags & IEEE80211_KEY_FLAG_RX_MGMT) अणु
			key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
			wcid->sw_iv = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (idx == wcid->hw_key_idx) अणु
			wcid->hw_key_idx = -1;
			wcid->sw_iv = false;
		पूर्ण

		key = शून्य;
	पूर्ण
	mt76_wcid_key_setup(&dev->mt76, wcid, key);

	अगर (!msta) अणु
		अगर (key || wcid->hw_key_idx == idx) अणु
			ret = mt76x02_mac_wcid_set_key(dev, wcid->idx, key);
			अगर (ret)
				वापस ret;
		पूर्ण

		वापस mt76x02_mac_shared_key_setup(dev, mvअगर->idx, idx, key);
	पूर्ण

	वापस mt76x02_mac_wcid_set_key(dev, msta->wcid.idx, key);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_set_key);

पूर्णांक mt76x02_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	u8 cw_min = 5, cw_max = 10, qid;
	u32 val;

	qid = dev->mphy.q_tx[queue]->hw_idx;

	अगर (params->cw_min)
		cw_min = fls(params->cw_min);
	अगर (params->cw_max)
		cw_max = fls(params->cw_max);

	val = FIELD_PREP(MT_EDCA_CFG_TXOP, params->txop) |
	      FIELD_PREP(MT_EDCA_CFG_AIFSN, params->aअगरs) |
	      FIELD_PREP(MT_EDCA_CFG_CWMIN, cw_min) |
	      FIELD_PREP(MT_EDCA_CFG_CWMAX, cw_max);
	mt76_wr(dev, MT_EDCA_CFG_AC(qid), val);

	val = mt76_rr(dev, MT_WMM_TXOP(qid));
	val &= ~(MT_WMM_TXOP_MASK << MT_WMM_TXOP_SHIFT(qid));
	val |= params->txop << MT_WMM_TXOP_SHIFT(qid);
	mt76_wr(dev, MT_WMM_TXOP(qid), val);

	val = mt76_rr(dev, MT_WMM_AIFSN);
	val &= ~(MT_WMM_AIFSN_MASK << MT_WMM_AIFSN_SHIFT(qid));
	val |= params->aअगरs << MT_WMM_AIFSN_SHIFT(qid);
	mt76_wr(dev, MT_WMM_AIFSN, val);

	val = mt76_rr(dev, MT_WMM_CWMIN);
	val &= ~(MT_WMM_CWMIN_MASK << MT_WMM_CWMIN_SHIFT(qid));
	val |= cw_min << MT_WMM_CWMIN_SHIFT(qid);
	mt76_wr(dev, MT_WMM_CWMIN, val);

	val = mt76_rr(dev, MT_WMM_CWMAX);
	val &= ~(MT_WMM_CWMAX_MASK << MT_WMM_CWMAX_SHIFT(qid));
	val |= cw_max << MT_WMM_CWMAX_SHIFT(qid);
	mt76_wr(dev, MT_WMM_CWMAX, val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_conf_tx);

व्योम mt76x02_set_tx_ackto(काष्ठा mt76x02_dev *dev)
अणु
	u8 ackto, sअगरs, slotसमय = dev->slotसमय;

	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	slotसमय += 3 * dev->coverage_class;
	mt76_rmw_field(dev, MT_BKOFF_SLOT_CFG,
		       MT_BKOFF_SLOT_CFG_SLOTTIME, slotसमय);

	sअगरs = mt76_get_field(dev, MT_XIFS_TIME_CFG,
			      MT_XIFS_TIME_CFG_OFDM_SIFS);

	ackto = slotसमय + sअगरs;
	mt76_rmw_field(dev, MT_TX_TIMEOUT_CFG,
		       MT_TX_TIMEOUT_CFG_ACKTO, ackto);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_set_tx_ackto);

व्योम mt76x02_set_coverage_class(काष्ठा ieee80211_hw *hw,
				s16 coverage_class)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	mutex_lock(&dev->mt76.mutex);
	dev->coverage_class = max_t(s16, coverage_class, 0);
	mt76x02_set_tx_ackto(dev);
	mutex_unlock(&dev->mt76.mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_set_coverage_class);

पूर्णांक mt76x02_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 val)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	अगर (val != ~0 && val > 0xffff)
		वापस -EINVAL;

	mutex_lock(&dev->mt76.mutex);
	mt76x02_mac_set_rts_thresh(dev, val);
	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_set_rts_threshold);

व्योम mt76x02_sta_rate_tbl_update(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	काष्ठा mt76x02_sta *msta = (काष्ठा mt76x02_sta *)sta->drv_priv;
	काष्ठा ieee80211_sta_rates *rates = rcu_dereference(sta->rates);
	काष्ठा ieee80211_tx_rate rate = अणुपूर्ण;

	अगर (!rates)
		वापस;

	rate.idx = rates->rate[0].idx;
	rate.flags = rates->rate[0].flags;
	mt76x02_mac_wcid_set_rate(dev, &msta->wcid, &rate);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_sta_rate_tbl_update);

व्योम mt76x02_हटाओ_hdr_pad(काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	पूर्णांक hdrlen;

	अगर (!len)
		वापस;

	hdrlen = ieee80211_get_hdrlen_from_skb(skb);
	स_हटाओ(skb->data + len, skb->data, hdrlen);
	skb_pull(skb, len);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_हटाओ_hdr_pad);

व्योम mt76x02_sw_scan_complete(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	clear_bit(MT76_SCANNING, &dev->mphy.state);
	अगर (dev->cal.gain_init_करोne) अणु
		/* Restore AGC gain and resume calibration after scanning. */
		dev->cal.low_gain = -1;
		ieee80211_queue_delayed_work(hw, &dev->cal_work, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_sw_scan_complete);

व्योम mt76x02_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta,
		    bool ps)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	काष्ठा mt76x02_sta *msta = (काष्ठा mt76x02_sta *)sta->drv_priv;
	पूर्णांक idx = msta->wcid.idx;

	mt76_stop_tx_queues(&dev->mphy, sta, true);
	अगर (mt76_is_mmio(mdev))
		mt76x02_mac_wcid_set_drop(dev, idx, ps);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_sta_ps);

व्योम mt76x02_bss_info_changed(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_bss_conf *info,
			      u32 changed)
अणु
	काष्ठा mt76x02_vअगर *mvअगर = (काष्ठा mt76x02_vअगर *)vअगर->drv_priv;
	काष्ठा mt76x02_dev *dev = hw->priv;

	mutex_lock(&dev->mt76.mutex);

	अगर (changed & BSS_CHANGED_BSSID)
		mt76x02_mac_set_bssid(dev, mvअगर->idx, info->bssid);

	अगर (changed & BSS_CHANGED_HT || changed & BSS_CHANGED_ERP_CTS_PROT)
		mt76x02_mac_set_tx_protection(dev, info->use_cts_prot,
					      info->ht_operation_mode);

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		mt76_rmw_field(dev, MT_BEACON_TIME_CFG,
			       MT_BEACON_TIME_CFG_INTVAL,
			       info->beacon_पूर्णांक << 4);
		dev->mt76.beacon_पूर्णांक = info->beacon_पूर्णांक;
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED)
		mt76x02_mac_set_beacon_enable(dev, vअगर, info->enable_beacon);

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE)
		mt76x02_mac_set_लघु_preamble(dev, info->use_लघु_preamble);

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		पूर्णांक slotसमय = info->use_लघु_slot ? 9 : 20;

		dev->slotसमय = slotसमय;
		mt76x02_set_tx_ackto(dev);
	पूर्ण

	mutex_unlock(&dev->mt76.mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_bss_info_changed);

व्योम mt76x02_config_mac_addr_list(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	काष्ठा wiphy *wiphy = hw->wiphy;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dev->macaddr_list); i++) अणु
		u8 *addr = dev->macaddr_list[i].addr;

		स_नकल(addr, dev->mphy.macaddr, ETH_ALEN);

		अगर (!i)
			जारी;

		addr[0] |= BIT(1);
		addr[0] ^= ((i - 1) << 2);
	पूर्ण
	wiphy->addresses = dev->macaddr_list;
	wiphy->n_addresses = ARRAY_SIZE(dev->macaddr_list);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_config_mac_addr_list);

MODULE_LICENSE("Dual BSD/GPL");
