<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश "mt7921.h"
#समावेश "mcu.h"

अटल व्योम
mt7921_gen_ppe_thresh(u8 *he_ppet, पूर्णांक nss)
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
mt7921_init_he_caps(काष्ठा mt7921_phy *phy, क्रमागत nl80211_band band,
		    काष्ठा ieee80211_sband_अगरtype_data *data)
अणु
	पूर्णांक i, idx = 0;
	पूर्णांक nss = hweight8(phy->mt76->chainmask);
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
				IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G;

		he_cap_elem->phy_cap_info[1] =
			IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD;
		he_cap_elem->phy_cap_info[2] =
			IEEE80211_HE_PHY_CAP2_STBC_TX_UNDER_80MHZ |
			IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ;

		चयन (i) अणु
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

		स_रखो(he_cap->ppe_thres, 0, माप(he_cap->ppe_thres));
		अगर (he_cap_elem->phy_cap_info[6] &
		    IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT) अणु
			mt7921_gen_ppe_thresh(he_cap->ppe_thres, nss);
		पूर्ण अन्यथा अणु
			he_cap_elem->phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_16US;
		पूर्ण
		idx++;
	पूर्ण

	वापस idx;
पूर्ण

व्योम mt7921_set_stream_he_caps(काष्ठा mt7921_phy *phy)
अणु
	काष्ठा ieee80211_sband_अगरtype_data *data;
	काष्ठा ieee80211_supported_band *band;
	पूर्णांक n;

	अगर (phy->mt76->cap.has_2ghz) अणु
		data = phy->अगरtype[NL80211_BAND_2GHZ];
		n = mt7921_init_he_caps(phy, NL80211_BAND_2GHZ, data);

		band = &phy->mt76->sband_2g.sband;
		band->अगरtype_data = data;
		band->n_अगरtype_data = n;
	पूर्ण

	अगर (phy->mt76->cap.has_5ghz) अणु
		data = phy->अगरtype[NL80211_BAND_5GHZ];
		n = mt7921_init_he_caps(phy, NL80211_BAND_5GHZ, data);

		band = &phy->mt76->sband_5g.sband;
		band->अगरtype_data = data;
		band->n_अगरtype_data = n;
	पूर्ण
पूर्ण

पूर्णांक __mt7921_start(काष्ठा mt7921_phy *phy)
अणु
	काष्ठा mt76_phy *mphy = phy->mt76;
	पूर्णांक err;

	err = mt76_connac_mcu_set_mac_enable(mphy->dev, 0, true, false);
	अगर (err)
		वापस err;

	err = mt76_connac_mcu_set_channel_करोमुख्य(mphy);
	अगर (err)
		वापस err;

	err = mt7921_mcu_set_chan_info(phy, MCU_EXT_CMD_SET_RX_PATH);
	अगर (err)
		वापस err;

	err = mt76_connac_mcu_set_rate_txघातer(phy->mt76);
	अगर (err)
		वापस err;

	mt7921_mac_reset_counters(phy);
	set_bit(MT76_STATE_RUNNING, &mphy->state);

	ieee80211_queue_delayed_work(mphy->hw, &mphy->mac_work,
				     MT7921_WATCHDOG_TIME);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7921_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	पूर्णांक err;

	mt7921_mutex_acquire(phy->dev);
	err = __mt7921_start(phy);
	mt7921_mutex_release(phy->dev);

	वापस err;
पूर्ण

अटल व्योम mt7921_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);

	cancel_delayed_work_sync(&phy->mt76->mac_work);

	cancel_delayed_work_sync(&dev->pm.ps_work);
	cancel_work_sync(&dev->pm.wake_work);
	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, शून्य);

	mt7921_mutex_acquire(dev);
	clear_bit(MT76_STATE_RUNNING, &phy->mt76->state);
	mt76_connac_mcu_set_mac_enable(&dev->mt76, 0, false, false);
	mt7921_mutex_release(dev);
पूर्ण

अटल अंतरभूत पूर्णांक get_मुक्त_idx(u32 mask, u8 start, u8 end)
अणु
	वापस ffs(~mask & GENMASK(end, start));
पूर्ण

अटल पूर्णांक get_omac_idx(क्रमागत nl80211_अगरtype type, u64 mask)
अणु
	पूर्णांक i;

	चयन (type) अणु
	हाल NL80211_IFTYPE_STATION:
		/* prefer hw bssid slot 1-3 */
		i = get_मुक्त_idx(mask, HW_BSSID_1, HW_BSSID_3);
		अगर (i)
			वापस i - 1;

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

अटल पूर्णांक mt7921_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	काष्ठा mt76_txq *mtxq;
	पूर्णांक idx, ret = 0;

	mt7921_mutex_acquire(dev);

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR &&
	    is_zero_ether_addr(vअगर->addr))
		phy->monitor_vअगर = vअगर;

	mvअगर->mt76.idx = ffs(~dev->mt76.vअगर_mask) - 1;
	अगर (mvअगर->mt76.idx >= MT7921_MAX_INTERFACES) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	idx = get_omac_idx(vअगर->type, phy->omac_mask);
	अगर (idx < 0) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण
	mvअगर->mt76.omac_idx = idx;
	mvअगर->phy = phy;
	mvअगर->mt76.band_idx = 0;
	mvअगर->mt76.wmm_idx = mvअगर->mt76.idx % MT7921_MAX_WMM_SETS;

	ret = mt76_connac_mcu_uni_add_dev(&dev->mphy, vअगर, &mvअगर->sta.wcid,
					  true);
	अगर (ret)
		जाओ out;

	dev->mt76.vअगर_mask |= BIT(mvअगर->mt76.idx);
	phy->omac_mask |= BIT_ULL(mvअगर->mt76.omac_idx);

	idx = MT7921_WTBL_RESERVED - mvअगर->mt76.idx;

	INIT_LIST_HEAD(&mvअगर->sta.stats_list);
	INIT_LIST_HEAD(&mvअगर->sta.poll_list);
	mvअगर->sta.wcid.idx = idx;
	mvअगर->sta.wcid.ext_phy = mvअगर->mt76.band_idx;
	mvअगर->sta.wcid.hw_key_idx = -1;
	mvअगर->sta.wcid.tx_info |= MT_WCID_TX_INFO_SET;
	mt7921_mac_wtbl_update(dev, idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	ewma_rssi_init(&mvअगर->rssi);

	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], &mvअगर->sta.wcid);
	अगर (vअगर->txq) अणु
		mtxq = (काष्ठा mt76_txq *)vअगर->txq->drv_priv;
		mtxq->wcid = &mvअगर->sta.wcid;
	पूर्ण

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    (!mvअगर->mt76.omac_idx || mvअगर->mt76.omac_idx > 3))
		vअगर->offload_flags = 0;

	vअगर->offload_flags |= IEEE80211_OFFLOAD_ENCAP_4ADDR;

out:
	mt7921_mutex_release(dev);

	वापस ret;
पूर्ण

अटल व्योम mt7921_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा mt7921_sta *msta = &mvअगर->sta;
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	पूर्णांक idx = msta->wcid.idx;

	अगर (vअगर == phy->monitor_vअगर)
		phy->monitor_vअगर = शून्य;

	mt7921_mutex_acquire(dev);
	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, &msta->wcid);
	mt76_connac_mcu_uni_add_dev(&dev->mphy, vअगर, &mvअगर->sta.wcid, false);

	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], शून्य);

	dev->mt76.vअगर_mask &= ~BIT(mvअगर->mt76.idx);
	phy->omac_mask &= ~BIT_ULL(mvअगर->mt76.omac_idx);
	mt7921_mutex_release(dev);

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (!list_empty(&msta->poll_list))
		list_del_init(&msta->poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);
पूर्ण

पूर्णांक mt7921_set_channel(काष्ठा mt7921_phy *phy)
अणु
	काष्ठा mt7921_dev *dev = phy->dev;
	पूर्णांक ret;

	cancel_delayed_work_sync(&phy->mt76->mac_work);

	mt7921_mutex_acquire(dev);
	set_bit(MT76_RESET, &phy->mt76->state);

	mt76_set_channel(phy->mt76);

	ret = mt7921_mcu_set_chan_info(phy, MCU_EXT_CMD_CHANNEL_SWITCH);
	अगर (ret)
		जाओ out;

	mt7921_mac_set_timing(phy);

	mt7921_mac_reset_counters(phy);
	phy->noise = 0;

out:
	clear_bit(MT76_RESET, &phy->mt76->state);
	mt7921_mutex_release(dev);

	mt76_worker_schedule(&dev->mt76.tx_worker);
	ieee80211_queue_delayed_work(phy->mt76->hw, &phy->mt76->mac_work,
				     MT7921_WATCHDOG_TIME);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7921_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			  काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा mt7921_sta *msta = sta ? (काष्ठा mt7921_sta *)sta->drv_priv :
				  &mvअगर->sta;
	काष्ठा mt76_wcid *wcid = &msta->wcid;
	u8 *wcid_keyidx = &wcid->hw_key_idx;
	पूर्णांक idx = key->keyidx, err = 0;

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
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIE;
		wcid_keyidx = &wcid->hw_key_idx2;
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

	mt7921_mutex_acquire(dev);

	अगर (cmd == SET_KEY)
		*wcid_keyidx = idx;
	अन्यथा अगर (idx == *wcid_keyidx)
		*wcid_keyidx = -1;
	अन्यथा
		जाओ out;

	mt76_wcid_key_setup(&dev->mt76, wcid,
			    cmd == SET_KEY ? key : शून्य);

	err = mt7921_mcu_add_key(dev, vअगर, msta, key, cmd);
out:
	mt7921_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक mt7921_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	पूर्णांक ret;

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		ieee80211_stop_queues(hw);
		ret = mt7921_set_channel(phy);
		अगर (ret)
			वापस ret;
		ieee80211_wake_queues(hw);
	पूर्ण

	mt7921_mutex_acquire(dev);

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		bool enabled = !!(hw->conf.flags & IEEE80211_CONF_MONITOR);

		अगर (!enabled)
			phy->rxfilter |= MT_WF_RFCR_DROP_OTHER_UC;
		अन्यथा
			phy->rxfilter &= ~MT_WF_RFCR_DROP_OTHER_UC;

		mt76_rmw_field(dev, MT_DMA_DCR0(0), MT_DMA_DCR0_RXD_G5_EN,
			       enabled);
		mt76_wr(dev, MT_WF_RFCR(0), phy->rxfilter);
	पूर्ण

	mt7921_mutex_release(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7921_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर, u16 queue,
	       स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;

	/* no need to update right away, we'll get BSS_CHANGED_QOS */
	queue = mt7921_lmac_mapping(dev, queue);
	mvअगर->queue_params[queue] = *params;

	वापस 0;
पूर्ण

अटल व्योम mt7921_configure_filter(काष्ठा ieee80211_hw *hw,
				    अचिन्हित पूर्णांक changed_flags,
				    अचिन्हित पूर्णांक *total_flags,
				    u64 multicast)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
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

	mt7921_mutex_acquire(dev);

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
	mt76_wr(dev, MT_WF_RFCR(0), phy->rxfilter);

	अगर (*total_flags & FIF_CONTROL)
		mt76_clear(dev, MT_WF_RFCR1(0), ctl_flags);
	अन्यथा
		mt76_set(dev, MT_WF_RFCR1(0), ctl_flags);

	mt7921_mutex_release(dev);
पूर्ण

अटल पूर्णांक
mt7921_bss_bcnft_apply(काष्ठा mt7921_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       bool assoc)
अणु
	पूर्णांक ret;

	अगर (!dev->pm.enable)
		वापस 0;

	अगर (assoc) अणु
		ret = mt7921_mcu_uni_bss_bcnft(dev, vअगर, true);
		अगर (ret)
			वापस ret;

		vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER;
		mt76_set(dev, MT_WF_RFCR(0), MT_WF_RFCR_DROP_OTHER_BEACON);

		वापस 0;
	पूर्ण

	ret = mt7921_mcu_set_bss_pm(dev, vअगर, false);
	अगर (ret)
		वापस ret;

	vअगर->driver_flags &= ~IEEE80211_VIF_BEACON_FILTER;
	mt76_clear(dev, MT_WF_RFCR(0), MT_WF_RFCR_DROP_OTHER_BEACON);

	वापस 0;
पूर्ण

अटल व्योम mt7921_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *info,
				    u32 changed)
अणु
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);

	mt7921_mutex_acquire(dev);

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		पूर्णांक slotसमय = info->use_लघु_slot ? 9 : 20;

		अगर (slotसमय != phy->slotसमय) अणु
			phy->slotसमय = slotसमय;
			mt7921_mac_set_timing(phy);
		पूर्ण
	पूर्ण

	/* ensure that enable txcmd_mode after bss_info */
	अगर (changed & (BSS_CHANGED_QOS | BSS_CHANGED_BEACON_ENABLED))
		mt7921_mcu_set_tx(dev, vअगर);

	अगर (changed & BSS_CHANGED_PS)
		mt7921_mcu_uni_bss_ps(dev, vअगर);

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		mt7921_mcu_sta_add(dev, शून्य, vअगर, true);
		mt7921_bss_bcnft_apply(dev, vअगर, info->assoc);
	पूर्ण

	अगर (changed & BSS_CHANGED_ARP_FILTER) अणु
		काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;

		mt76_connac_mcu_update_arp_filter(&dev->mt76, &mvअगर->mt76,
						  info);
	पूर्ण

	mt7921_mutex_release(dev);
पूर्ण

पूर्णांक mt7921_mac_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	काष्ठा mt7921_sta *msta = (काष्ठा mt7921_sta *)sta->drv_priv;
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	पूर्णांक ret, idx;

	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7921_WTBL_STA - 1);
	अगर (idx < 0)
		वापस -ENOSPC;

	INIT_LIST_HEAD(&msta->stats_list);
	INIT_LIST_HEAD(&msta->poll_list);
	msta->vअगर = mvअगर;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.ext_phy = mvअगर->mt76.band_idx;
	msta->wcid.tx_info |= MT_WCID_TX_INFO_SET;
	msta->stats.jअगरfies = jअगरfies;

	ret = mt76_connac_pm_wake(&dev->mphy, &dev->pm);
	अगर (ret)
		वापस ret;

	अगर (vअगर->type == NL80211_IFTYPE_STATION && !sta->tdls)
		mt76_connac_mcu_uni_add_bss(&dev->mphy, vअगर, &mvअगर->sta.wcid,
					    true);

	mt7921_mac_wtbl_update(dev, idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	ret = mt7921_mcu_sta_add(dev, sta, vअगर, true);
	अगर (ret)
		वापस ret;

	mt76_connac_घातer_save_sched(&dev->mphy, &dev->pm);

	वापस 0;
पूर्ण

व्योम mt7921_mac_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	काष्ठा mt7921_sta *msta = (काष्ठा mt7921_sta *)sta->drv_priv;

	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, &msta->wcid);
	mt76_connac_pm_wake(&dev->mphy, &dev->pm);

	mt7921_mcu_sta_add(dev, sta, vअगर, false);
	mt7921_mac_wtbl_update(dev, msta->wcid.idx,
			       MT_WTBL_UPDATE_ADM_COUNT_CLEAR);

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;

		ewma_rssi_init(&mvअगर->rssi);
		अगर (!sta->tdls)
			mt76_connac_mcu_uni_add_bss(&dev->mphy, vअगर,
						    &mvअगर->sta.wcid, false);
	पूर्ण

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (!list_empty(&msta->poll_list))
		list_del_init(&msta->poll_list);
	अगर (!list_empty(&msta->stats_list))
		list_del_init(&msta->stats_list);
	spin_unlock_bh(&dev->sta_poll_lock);

	mt76_connac_घातer_save_sched(&dev->mphy, &dev->pm);
पूर्ण

व्योम mt7921_tx_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt7921_dev *dev = container_of(w, काष्ठा mt7921_dev,
					      mt76.tx_worker);

	अगर (!mt76_connac_pm_ref(&dev->mphy, &dev->pm)) अणु
		queue_work(dev->mt76.wq, &dev->pm.wake_work);
		वापस;
	पूर्ण

	mt76_txq_schedule_all(&dev->mphy);
	mt76_connac_pm_unref(&dev->pm);
पूर्ण

अटल व्योम mt7921_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_tx_control *control,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt76_wcid *wcid = &dev->mt76.global_wcid;
	पूर्णांक qid;

	अगर (control->sta) अणु
		काष्ठा mt7921_sta *sta;

		sta = (काष्ठा mt7921_sta *)control->sta->drv_priv;
		wcid = &sta->wcid;
	पूर्ण

	अगर (vअगर && !control->sta) अणु
		काष्ठा mt7921_vअगर *mvअगर;

		mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
		wcid = &mvअगर->sta.wcid;
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

अटल पूर्णांक mt7921_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 val)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);

	mt7921_mutex_acquire(dev);
	mt76_connac_mcu_set_rts_thresh(&dev->mt76, val, 0);
	mt7921_mutex_release(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7921_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_ampdu_params *params)
अणु
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा ieee80211_sta *sta = params->sta;
	काष्ठा ieee80211_txq *txq = sta->txq[params->tid];
	काष्ठा mt7921_sta *msta = (काष्ठा mt7921_sta *)sta->drv_priv;
	u16 tid = params->tid;
	u16 ssn = params->ssn;
	काष्ठा mt76_txq *mtxq;
	पूर्णांक ret = 0;

	अगर (!txq)
		वापस -EINVAL;

	mtxq = (काष्ठा mt76_txq *)txq->drv_priv;

	mt7921_mutex_acquire(dev);
	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		mt76_rx_aggr_start(&dev->mt76, &msta->wcid, tid, ssn,
				   params->buf_size);
		mt7921_mcu_uni_rx_ba(dev, params, true);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		mt76_rx_aggr_stop(&dev->mt76, &msta->wcid, tid);
		mt7921_mcu_uni_rx_ba(dev, params, false);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		mtxq->aggr = true;
		mtxq->send_bar = false;
		mt7921_mcu_uni_tx_ba(dev, params, true);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		mtxq->aggr = false;
		clear_bit(tid, &msta->ampdu_state);
		mt7921_mcu_uni_tx_ba(dev, params, false);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		set_bit(tid, &msta->ampdu_state);
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggr = false;
		clear_bit(tid, &msta->ampdu_state);
		mt7921_mcu_uni_tx_ba(dev, params, false);
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	पूर्ण
	mt7921_mutex_release(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7921_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       काष्ठा ieee80211_sta *sta)
अणु
	वापस mt76_sta_state(hw, vअगर, sta, IEEE80211_STA_NOTEXIST,
			      IEEE80211_STA_NONE);
पूर्ण

अटल पूर्णांक
mt7921_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_sta *sta)
अणु
	वापस mt76_sta_state(hw, vअगर, sta, IEEE80211_STA_NONE,
			      IEEE80211_STA_NOTEXIST);
पूर्ण

अटल पूर्णांक
mt7921_get_stats(काष्ठा ieee80211_hw *hw,
		 काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	काष्ठा mib_stats *mib = &phy->mib;

	mt7921_mutex_acquire(phy->dev);

	stats->करोt11RTSSuccessCount = mib->rts_cnt;
	stats->करोt11RTSFailureCount = mib->rts_retries_cnt;
	stats->करोt11FCSErrorCount = mib->fcs_err_cnt;
	stats->करोt11ACKFailureCount = mib->ack_fail_cnt;

	स_रखो(mib, 0, माप(*mib));

	mt7921_mutex_release(phy->dev);

	वापस 0;
पूर्ण

अटल u64
mt7921_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	u8 omac_idx = mvअगर->mt76.omac_idx;
	जोड़ अणु
		u64 t64;
		u32 t32[2];
	पूर्ण tsf;
	u16 n;

	mt7921_mutex_acquire(dev);

	n = omac_idx > HW_BSSID_MAX ? HW_BSSID_0 : omac_idx;
	/* TSF software पढ़ो */
	mt76_set(dev, MT_LPON_TCR(0, n), MT_LPON_TCR_SW_MODE);
	tsf.t32[0] = mt76_rr(dev, MT_LPON_UTTR0(0));
	tsf.t32[1] = mt76_rr(dev, MT_LPON_UTTR1(0));

	mt7921_mutex_release(dev);

	वापस tsf.t64;
पूर्ण

अटल व्योम
mt7921_set_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       u64 बारtamp)
अणु
	काष्ठा mt7921_vअगर *mvअगर = (काष्ठा mt7921_vअगर *)vअगर->drv_priv;
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	u8 omac_idx = mvअगर->mt76.omac_idx;
	जोड़ अणु
		u64 t64;
		u32 t32[2];
	पूर्ण tsf = अणु .t64 = बारtamp, पूर्ण;
	u16 n;

	mt7921_mutex_acquire(dev);

	n = omac_idx > HW_BSSID_MAX ? HW_BSSID_0 : omac_idx;
	mt76_wr(dev, MT_LPON_UTTR0(0), tsf.t32[0]);
	mt76_wr(dev, MT_LPON_UTTR1(0), tsf.t32[1]);
	/* TSF software overग_लिखो */
	mt76_set(dev, MT_LPON_TCR(0, n), MT_LPON_TCR_SW_WRITE);

	mt7921_mutex_release(dev);
पूर्ण

अटल व्योम
mt7921_set_coverage_class(काष्ठा ieee80211_hw *hw, s16 coverage_class)
अणु
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	काष्ठा mt7921_dev *dev = phy->dev;

	mt7921_mutex_acquire(dev);
	phy->coverage_class = max_t(s16, coverage_class, 0);
	mt7921_mac_set_timing(phy);
	mt7921_mutex_release(dev);
पूर्ण

व्योम mt7921_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7921_phy *phy;

	phy = (काष्ठा mt7921_phy *)container_of(work, काष्ठा mt7921_phy,
						scan_work.work);

	जबतक (true) अणु
		काष्ठा mt7921_mcu_rxd *rxd;
		काष्ठा sk_buff *skb;

		spin_lock_bh(&phy->dev->mt76.lock);
		skb = __skb_dequeue(&phy->scan_event_list);
		spin_unlock_bh(&phy->dev->mt76.lock);

		अगर (!skb)
			अवरोध;

		rxd = (काष्ठा mt7921_mcu_rxd *)skb->data;
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
mt7921_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       काष्ठा ieee80211_scan_request *req)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	पूर्णांक err;

	mt7921_mutex_acquire(dev);
	err = mt76_connac_mcu_hw_scan(mphy, vअगर, req);
	mt7921_mutex_release(dev);

	वापस err;
पूर्ण

अटल व्योम
mt7921_cancel_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;

	mt7921_mutex_acquire(dev);
	mt76_connac_mcu_cancel_hw_scan(mphy, vअगर);
	mt7921_mutex_release(dev);
पूर्ण

अटल पूर्णांक
mt7921_start_sched_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा cfg80211_sched_scan_request *req,
			काष्ठा ieee80211_scan_ies *ies)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	पूर्णांक err;

	mt7921_mutex_acquire(dev);

	err = mt76_connac_mcu_sched_scan_req(mphy, vअगर, req);
	अगर (err < 0)
		जाओ out;

	err = mt76_connac_mcu_sched_scan_enable(mphy, vअगर, true);
out:
	mt7921_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक
mt7921_stop_sched_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt76_phy *mphy = hw->priv;
	पूर्णांक err;

	mt7921_mutex_acquire(dev);
	err = mt76_connac_mcu_sched_scan_enable(mphy, vअगर, false);
	mt7921_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक
mt7921_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	पूर्णांक max_nss = hweight8(hw->wiphy->available_antennas_tx);

	अगर (!tx_ant || tx_ant != rx_ant || ffs(tx_ant) > max_nss)
		वापस -EINVAL;

	अगर ((BIT(hweight8(tx_ant)) - 1) != tx_ant)
		tx_ant = BIT(ffs(tx_ant) - 1) - 1;

	mt7921_mutex_acquire(dev);

	phy->mt76->antenna_mask = tx_ant;
	phy->mt76->chainmask = tx_ant;

	mt76_set_stream_caps(phy->mt76, true);
	mt7921_set_stream_he_caps(phy);

	mt7921_mutex_release(dev);

	वापस 0;
पूर्ण

अटल व्योम mt7921_sta_statistics(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा station_info *sinfo)
अणु
	काष्ठा mt7921_sta *msta = (काष्ठा mt7921_sta *)sta->drv_priv;
	काष्ठा mt7921_sta_stats *stats = &msta->stats;

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

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mt7921_suspend(काष्ठा ieee80211_hw *hw,
			  काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	पूर्णांक err;

	cancel_delayed_work_sync(&phy->scan_work);
	cancel_delayed_work_sync(&phy->mt76->mac_work);

	cancel_delayed_work_sync(&dev->pm.ps_work);
	mt76_connac_मुक्त_pending_tx_skbs(&dev->pm, शून्य);

	mt7921_mutex_acquire(dev);

	clear_bit(MT76_STATE_RUNNING, &phy->mt76->state);

	set_bit(MT76_STATE_SUSPEND, &phy->mt76->state);
	ieee80211_iterate_active_पूर्णांकerfaces(hw,
					    IEEE80211_IFACE_ITER_RESUME_ALL,
					    mt76_connac_mcu_set_suspend_iter,
					    &dev->mphy);

	err = mt76_connac_mcu_set_hअगर_suspend(&dev->mt76, true);

	mt7921_mutex_release(dev);

	वापस err;
पूर्ण

अटल पूर्णांक mt7921_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt7921_phy *phy = mt7921_hw_phy(hw);
	पूर्णांक err;

	mt7921_mutex_acquire(dev);

	err = mt76_connac_mcu_set_hअगर_suspend(&dev->mt76, false);
	अगर (err < 0)
		जाओ out;

	set_bit(MT76_STATE_RUNNING, &phy->mt76->state);
	clear_bit(MT76_STATE_SUSPEND, &phy->mt76->state);
	ieee80211_iterate_active_पूर्णांकerfaces(hw,
					    IEEE80211_IFACE_ITER_RESUME_ALL,
					    mt76_connac_mcu_set_suspend_iter,
					    &dev->mphy);

	ieee80211_queue_delayed_work(hw, &phy->mt76->mac_work,
				     MT7921_WATCHDOG_TIME);
out:

	mt7921_mutex_release(dev);

	वापस err;
पूर्ण

अटल व्योम mt7921_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);
	काष्ठा mt76_dev *mdev = &dev->mt76;

	device_set_wakeup_enable(mdev->dev, enabled);
पूर्ण

अटल व्योम mt7921_set_rekey_data(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);

	mt7921_mutex_acquire(dev);
	mt76_connac_mcu_update_gtk_rekey(hw, vअगर, data);
	mt7921_mutex_release(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम mt7921_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 u32 queues, bool drop)
अणु
	काष्ठा mt7921_dev *dev = mt7921_hw_dev(hw);

	रुको_event_समयout(dev->mt76.tx_रुको, !mt76_has_tx_pending(&dev->mphy),
			   HZ / 2);
पूर्ण

स्थिर काष्ठा ieee80211_ops mt7921_ops = अणु
	.tx = mt7921_tx,
	.start = mt7921_start,
	.stop = mt7921_stop,
	.add_पूर्णांकerface = mt7921_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = mt7921_हटाओ_पूर्णांकerface,
	.config = mt7921_config,
	.conf_tx = mt7921_conf_tx,
	.configure_filter = mt7921_configure_filter,
	.bss_info_changed = mt7921_bss_info_changed,
	.sta_add = mt7921_sta_add,
	.sta_हटाओ = mt7921_sta_हटाओ,
	.sta_pre_rcu_हटाओ = mt76_sta_pre_rcu_हटाओ,
	.set_key = mt7921_set_key,
	.ampdu_action = mt7921_ampdu_action,
	.set_rts_threshold = mt7921_set_rts_threshold,
	.wake_tx_queue = mt76_wake_tx_queue,
	.release_buffered_frames = mt76_release_buffered_frames,
	.get_txघातer = mt76_get_txघातer,
	.get_stats = mt7921_get_stats,
	.get_tsf = mt7921_get_tsf,
	.set_tsf = mt7921_set_tsf,
	.get_survey = mt76_get_survey,
	.get_antenna = mt76_get_antenna,
	.set_antenna = mt7921_set_antenna,
	.set_coverage_class = mt7921_set_coverage_class,
	.hw_scan = mt7921_hw_scan,
	.cancel_hw_scan = mt7921_cancel_hw_scan,
	.sta_statistics = mt7921_sta_statistics,
	.sched_scan_start = mt7921_start_sched_scan,
	.sched_scan_stop = mt7921_stop_sched_scan,
#अगर_घोषित CONFIG_PM
	.suspend = mt7921_suspend,
	.resume = mt7921_resume,
	.set_wakeup = mt7921_set_wakeup,
	.set_rekey_data = mt7921_set_rekey_data,
#पूर्ण_अगर /* CONFIG_PM */
	.flush = mt7921_flush,
पूर्ण;
