<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश "mt7603.h"
#समावेश "mac.h"
#समावेश "eeprom.h"

अटल पूर्णांक
mt7603_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;

	mt7603_mac_reset_counters(dev);
	mt7603_mac_start(dev);
	dev->mphy.survey_समय = kसमय_get_bootसमय();
	set_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	mt7603_mac_work(&dev->mphy.mac_work.work);

	वापस 0;
पूर्ण

अटल व्योम
mt7603_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;

	clear_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	cancel_delayed_work_sync(&dev->mphy.mac_work);
	mt7603_mac_stop(dev);
पूर्ण

अटल पूर्णांक
mt7603_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7603_vअगर *mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;
	काष्ठा mt7603_dev *dev = hw->priv;
	काष्ठा mt76_txq *mtxq;
	u8 bc_addr[ETH_ALEN];
	पूर्णांक idx;
	पूर्णांक ret = 0;

	mutex_lock(&dev->mt76.mutex);

	mvअगर->idx = ffs(~dev->mt76.vअगर_mask) - 1;
	अगर (mvअगर->idx >= MT7603_MAX_INTERFACES) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	mt76_wr(dev, MT_MAC_ADDR0(mvअगर->idx),
		get_unaligned_le32(vअगर->addr));
	mt76_wr(dev, MT_MAC_ADDR1(mvअगर->idx),
		(get_unaligned_le16(vअगर->addr + 4) |
		 MT_MAC_ADDR1_VALID));

	अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
		mt76_wr(dev, MT_BSSID0(mvअगर->idx),
			get_unaligned_le32(vअगर->addr));
		mt76_wr(dev, MT_BSSID1(mvअगर->idx),
			(get_unaligned_le16(vअगर->addr + 4) |
			 MT_BSSID1_VALID));
	पूर्ण

	idx = MT7603_WTBL_RESERVED - 1 - mvअगर->idx;
	dev->mt76.vअगर_mask |= BIT(mvअगर->idx);
	INIT_LIST_HEAD(&mvअगर->sta.poll_list);
	mvअगर->sta.wcid.idx = idx;
	mvअगर->sta.wcid.hw_key_idx = -1;

	eth_broadcast_addr(bc_addr);
	mt7603_wtbl_init(dev, idx, mvअगर->idx, bc_addr);

	mtxq = (काष्ठा mt76_txq *)vअगर->txq->drv_priv;
	mtxq->wcid = &mvअगर->sta.wcid;
	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], &mvअगर->sta.wcid);

out:
	mutex_unlock(&dev->mt76.mutex);

	वापस ret;
पूर्ण

अटल व्योम
mt7603_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7603_vअगर *mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;
	काष्ठा mt7603_sta *msta = &mvअगर->sta;
	काष्ठा mt7603_dev *dev = hw->priv;
	पूर्णांक idx = msta->wcid.idx;

	mt76_wr(dev, MT_MAC_ADDR0(mvअगर->idx), 0);
	mt76_wr(dev, MT_MAC_ADDR1(mvअगर->idx), 0);
	mt76_wr(dev, MT_BSSID0(mvअगर->idx), 0);
	mt76_wr(dev, MT_BSSID1(mvअगर->idx), 0);
	mt7603_beacon_set_समयr(dev, mvअगर->idx, 0);

	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], शून्य);

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (!list_empty(&msta->poll_list))
		list_del_init(&msta->poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);

	mutex_lock(&dev->mt76.mutex);
	dev->mt76.vअगर_mask &= ~BIT(mvअगर->idx);
	mutex_unlock(&dev->mt76.mutex);
पूर्ण

व्योम mt7603_init_edcca(काष्ठा mt7603_dev *dev)
अणु
	/* Set lower संकेत level to -65dBm */
	mt76_rmw_field(dev, MT_RXTD(8), MT_RXTD_8_LOWER_SIGNAL, 0x23);

	/* clear previous energy detect monitor results */
	mt76_rr(dev, MT_MIB_STAT_ED);

	अगर (dev->ed_monitor)
		mt76_set(dev, MT_MIB_CTL, MT_MIB_CTL_ED_TIME);
	अन्यथा
		mt76_clear(dev, MT_MIB_CTL, MT_MIB_CTL_ED_TIME);

	dev->ed_strict_mode = 0xff;
	dev->ed_strong_संकेत = 0;
	dev->ed_समय = kसमय_get_bootसमय();

	mt7603_edcca_set_strict(dev, false);
पूर्ण

अटल पूर्णांक
mt7603_set_channel(काष्ठा mt7603_dev *dev, काष्ठा cfg80211_chan_def *def)
अणु
	u8 *rssi_data = (u8 *)dev->mt76.eeprom.data;
	पूर्णांक idx, ret;
	u8 bw = MT_BW_20;
	bool failed = false;

	cancel_delayed_work_sync(&dev->mphy.mac_work);
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);

	mutex_lock(&dev->mt76.mutex);
	set_bit(MT76_RESET, &dev->mphy.state);

	mt7603_beacon_set_समयr(dev, -1, 0);
	mt76_set_channel(&dev->mphy);
	mt7603_mac_stop(dev);

	अगर (def->width == NL80211_CHAN_WIDTH_40)
		bw = MT_BW_40;

	dev->mphy.chandef = *def;
	mt76_rmw_field(dev, MT_AGG_BWCR, MT_AGG_BWCR_BW, bw);
	ret = mt7603_mcu_set_channel(dev);
	अगर (ret) अणु
		failed = true;
		जाओ out;
	पूर्ण

	अगर (def->chan->band == NL80211_BAND_5GHZ) अणु
		idx = 1;
		rssi_data += MT_EE_RSSI_OFFSET_5G;
	पूर्ण अन्यथा अणु
		idx = 0;
		rssi_data += MT_EE_RSSI_OFFSET_2G;
	पूर्ण

	स_नकल(dev->rssi_offset, rssi_data, माप(dev->rssi_offset));

	idx |= (def->chan -
		mt76_hw(dev)->wiphy->bands[def->chan->band]->channels) << 1;
	mt76_wr(dev, MT_WF_RMAC_CH_FREQ, idx);
	mt7603_mac_set_timing(dev);
	mt7603_mac_start(dev);

	clear_bit(MT76_RESET, &dev->mphy.state);

	mt76_txq_schedule_all(&dev->mphy);

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mphy.mac_work,
				     msecs_to_jअगरfies(MT7603_WATCHDOG_TIME));

	/* reset channel stats */
	mt76_clear(dev, MT_MIB_CTL, MT_MIB_CTL_READ_CLR_DIS);
	mt76_set(dev, MT_MIB_CTL,
		 MT_MIB_CTL_CCA_NAV_TX | MT_MIB_CTL_PSCCA_TIME);
	mt76_rr(dev, MT_MIB_STAT_CCA);
	mt7603_cca_stats_reset(dev);

	dev->mphy.survey_समय = kसमय_get_bootसमय();

	mt7603_init_edcca(dev);

out:
	अगर (!(mt76_hw(dev)->conf.flags & IEEE80211_CONF_OFFCHANNEL))
		mt7603_beacon_set_समयr(dev, -1, dev->mt76.beacon_पूर्णांक);
	mutex_unlock(&dev->mt76.mutex);

	tasklet_enable(&dev->mt76.pre_tbtt_tasklet);

	अगर (failed)
		mt7603_mac_work(&dev->mphy.mac_work.work);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7603_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;
	पूर्णांक ret = 0;

	अगर (changed & (IEEE80211_CONF_CHANGE_CHANNEL |
		       IEEE80211_CONF_CHANGE_POWER)) अणु
		ieee80211_stop_queues(hw);
		ret = mt7603_set_channel(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		mutex_lock(&dev->mt76.mutex);

		अगर (!(hw->conf.flags & IEEE80211_CONF_MONITOR))
			dev->rxfilter |= MT_WF_RFCR_DROP_OTHER_UC;
		अन्यथा
			dev->rxfilter &= ~MT_WF_RFCR_DROP_OTHER_UC;

		mt76_wr(dev, MT_WF_RFCR, dev->rxfilter);

		mutex_unlock(&dev->mt76.mutex);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
mt7603_configure_filter(काष्ठा ieee80211_hw *hw, अचिन्हित पूर्णांक changed_flags,
			अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;
	u32 flags = 0;

#घोषणा MT76_FILTER(_flag, _hw) करो अणु \
		flags |= *total_flags & FIF_##_flag;			\
		dev->rxfilter &= ~(_hw);				\
		dev->rxfilter |= !(flags & FIF_##_flag) * (_hw);	\
	पूर्ण जबतक (0)

	dev->rxfilter &= ~(MT_WF_RFCR_DROP_OTHER_BSS |
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
	mt76_wr(dev, MT_WF_RFCR, dev->rxfilter);
पूर्ण

अटल व्योम
mt7603_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_bss_conf *info, u32 changed)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;
	काष्ठा mt7603_vअगर *mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;

	mutex_lock(&dev->mt76.mutex);

	अगर (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BSSID)) अणु
		अगर (info->assoc || info->ibss_joined) अणु
			mt76_wr(dev, MT_BSSID0(mvअगर->idx),
				get_unaligned_le32(info->bssid));
			mt76_wr(dev, MT_BSSID1(mvअगर->idx),
				(get_unaligned_le16(info->bssid + 4) |
				 MT_BSSID1_VALID));
		पूर्ण अन्यथा अणु
			mt76_wr(dev, MT_BSSID0(mvअगर->idx), 0);
			mt76_wr(dev, MT_BSSID1(mvअगर->idx), 0);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		पूर्णांक slotसमय = info->use_लघु_slot ? 9 : 20;

		अगर (slotसमय != dev->slotसमय) अणु
			dev->slotसमय = slotसमय;
			mt7603_mac_set_timing(dev);
		पूर्ण
	पूर्ण

	अगर (changed & (BSS_CHANGED_BEACON_ENABLED | BSS_CHANGED_BEACON_INT)) अणु
		पूर्णांक beacon_पूर्णांक = !!info->enable_beacon * info->beacon_पूर्णांक;

		tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
		mt7603_beacon_set_समयr(dev, mvअगर->idx, beacon_पूर्णांक);
		tasklet_enable(&dev->mt76.pre_tbtt_tasklet);
	पूर्ण

	mutex_unlock(&dev->mt76.mutex);
पूर्ण

पूर्णांक
mt7603_sta_add(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
	       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	काष्ठा mt7603_sta *msta = (काष्ठा mt7603_sta *)sta->drv_priv;
	काष्ठा mt7603_vअगर *mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;
	पूर्णांक idx;
	पूर्णांक ret = 0;

	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7603_WTBL_STA - 1);
	अगर (idx < 0)
		वापस -ENOSPC;

	INIT_LIST_HEAD(&msta->poll_list);
	__skb_queue_head_init(&msta->psq);
	msta->ps = ~0;
	msta->smps = ~0;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	mt7603_wtbl_init(dev, idx, mvअगर->idx, sta->addr);
	mt7603_wtbl_set_ps(dev, msta, false);

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		set_bit(MT_WCID_FLAG_CHECK_PS, &msta->wcid.flags);

	वापस ret;
पूर्ण

व्योम
mt7603_sta_assoc(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);

	mt7603_wtbl_update_cap(dev, sta);
पूर्ण

व्योम
mt7603_sta_हटाओ(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	काष्ठा mt7603_sta *msta = (काष्ठा mt7603_sta *)sta->drv_priv;
	काष्ठा mt76_wcid *wcid = (काष्ठा mt76_wcid *)sta->drv_priv;

	spin_lock_bh(&dev->ps_lock);
	__skb_queue_purge(&msta->psq);
	mt7603_filter_tx(dev, wcid->idx, true);
	spin_unlock_bh(&dev->ps_lock);

	spin_lock_bh(&dev->sta_poll_lock);
	अगर (!list_empty(&msta->poll_list))
		list_del_init(&msta->poll_list);
	spin_unlock_bh(&dev->sta_poll_lock);

	mt7603_wtbl_clear(dev, wcid->idx);
पूर्ण

अटल व्योम
mt7603_ps_tx_list(काष्ठा mt7603_dev *dev, काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(list)) != शून्य) अणु
		पूर्णांक qid = skb_get_queue_mapping(skb);

		mt76_tx_queue_skb_raw(dev, dev->mphy.q_tx[qid], skb, 0);
	पूर्ण
पूर्ण

व्योम
mt7603_sta_ps(काष्ठा mt76_dev *mdev, काष्ठा ieee80211_sta *sta, bool ps)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	काष्ठा mt7603_sta *msta = (काष्ठा mt7603_sta *)sta->drv_priv;
	काष्ठा sk_buff_head list;

	mt76_stop_tx_queues(&dev->mphy, sta, true);
	mt7603_wtbl_set_ps(dev, msta, ps);
	अगर (ps)
		वापस;

	__skb_queue_head_init(&list);

	spin_lock_bh(&dev->ps_lock);
	skb_queue_splice_tail_init(&msta->psq, &list);
	spin_unlock_bh(&dev->ps_lock);

	mt7603_ps_tx_list(dev, &list);
पूर्ण

अटल व्योम
mt7603_ps_set_more_data(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;

	hdr = (काष्ठा ieee80211_hdr *)&skb->data[MT_TXD_SIZE];
	hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_MOREDATA);
पूर्ण

अटल व्योम
mt7603_release_buffered_frames(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_sta *sta,
			       u16 tids, पूर्णांक nframes,
			       क्रमागत ieee80211_frame_release_type reason,
			       bool more_data)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;
	काष्ठा mt7603_sta *msta = (काष्ठा mt7603_sta *)sta->drv_priv;
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb, *पंचांगp;

	__skb_queue_head_init(&list);

	mt7603_wtbl_set_ps(dev, msta, false);

	spin_lock_bh(&dev->ps_lock);
	skb_queue_walk_safe(&msta->psq, skb, पंचांगp) अणु
		अगर (!nframes)
			अवरोध;

		अगर (!(tids & BIT(skb->priority)))
			जारी;

		skb_set_queue_mapping(skb, MT_TXQ_PSD);
		__skb_unlink(skb, &msta->psq);
		mt7603_ps_set_more_data(skb);
		__skb_queue_tail(&list, skb);
		nframes--;
	पूर्ण
	spin_unlock_bh(&dev->ps_lock);

	अगर (!skb_queue_empty(&list))
		ieee80211_sta_eosp(sta);

	mt7603_ps_tx_list(dev, &list);

	अगर (nframes)
		mt76_release_buffered_frames(hw, sta, tids, nframes, reason,
					     more_data);
पूर्ण

अटल पूर्णांक
mt7603_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
	       काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
	       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;
	काष्ठा mt7603_vअगर *mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;
	काष्ठा mt7603_sta *msta = sta ? (काष्ठा mt7603_sta *)sta->drv_priv :
				  &mvअगर->sta;
	काष्ठा mt76_wcid *wcid = &msta->wcid;
	पूर्णांक idx = key->keyidx;

	/* fall back to sw encryption क्रम unsupported ciphers */
	चयन (key->cipher) अणु
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

	अगर (cmd == SET_KEY) अणु
		key->hw_key_idx = wcid->idx;
		wcid->hw_key_idx = idx;
	पूर्ण अन्यथा अणु
		अगर (idx == wcid->hw_key_idx)
			wcid->hw_key_idx = -1;

		key = शून्य;
	पूर्ण
	mt76_wcid_key_setup(&dev->mt76, wcid, key);

	वापस mt7603_wtbl_set_key(dev, wcid->idx, key);
पूर्ण

अटल पूर्णांक
mt7603_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर, u16 queue,
	       स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;
	u16 cw_min = (1 << 5) - 1;
	u16 cw_max = (1 << 10) - 1;
	u32 val;

	queue = dev->mphy.q_tx[queue]->hw_idx;

	अगर (params->cw_min)
		cw_min = params->cw_min;
	अगर (params->cw_max)
		cw_max = params->cw_max;

	mutex_lock(&dev->mt76.mutex);
	mt7603_mac_stop(dev);

	val = mt76_rr(dev, MT_WMM_TXOP(queue));
	val &= ~(MT_WMM_TXOP_MASK << MT_WMM_TXOP_SHIFT(queue));
	val |= params->txop << MT_WMM_TXOP_SHIFT(queue);
	mt76_wr(dev, MT_WMM_TXOP(queue), val);

	val = mt76_rr(dev, MT_WMM_AIFSN);
	val &= ~(MT_WMM_AIFSN_MASK << MT_WMM_AIFSN_SHIFT(queue));
	val |= params->aअगरs << MT_WMM_AIFSN_SHIFT(queue);
	mt76_wr(dev, MT_WMM_AIFSN, val);

	val = mt76_rr(dev, MT_WMM_CWMIN);
	val &= ~(MT_WMM_CWMIN_MASK << MT_WMM_CWMIN_SHIFT(queue));
	val |= cw_min << MT_WMM_CWMIN_SHIFT(queue);
	mt76_wr(dev, MT_WMM_CWMIN, val);

	val = mt76_rr(dev, MT_WMM_CWMAX(queue));
	val &= ~(MT_WMM_CWMAX_MASK << MT_WMM_CWMAX_SHIFT(queue));
	val |= cw_max << MT_WMM_CWMAX_SHIFT(queue);
	mt76_wr(dev, MT_WMM_CWMAX(queue), val);

	mt7603_mac_start(dev);
	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण

अटल व्योम
mt7603_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	     u32 queues, bool drop)
अणु
पूर्ण

अटल पूर्णांक
mt7603_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_ampdu_params *params)
अणु
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	काष्ठा mt7603_dev *dev = hw->priv;
	काष्ठा ieee80211_sta *sta = params->sta;
	काष्ठा ieee80211_txq *txq = sta->txq[params->tid];
	काष्ठा mt7603_sta *msta = (काष्ठा mt7603_sta *)sta->drv_priv;
	u16 tid = params->tid;
	u16 ssn = params->ssn;
	u8 ba_size = params->buf_size;
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
		mt7603_mac_rx_ba_reset(dev, sta->addr, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		mt76_rx_aggr_stop(&dev->mt76, &msta->wcid, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		mtxq->aggr = true;
		mtxq->send_bar = false;
		mt7603_mac_tx_ba_reset(dev, msta->wcid.idx, tid, ba_size);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		mtxq->aggr = false;
		mt7603_mac_tx_ba_reset(dev, msta->wcid.idx, tid, -1);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		mtxq->agg_ssn = IEEE80211_SN_TO_SEQ(ssn);
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		mtxq->aggr = false;
		mt7603_mac_tx_ba_reset(dev, msta->wcid.idx, tid, -1);
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	पूर्ण
	mutex_unlock(&dev->mt76.mutex);

	वापस ret;
पूर्ण

अटल व्योम
mt7603_sta_rate_tbl_update(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;
	काष्ठा mt7603_sta *msta = (काष्ठा mt7603_sta *)sta->drv_priv;
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
	mt7603_wtbl_set_rates(dev, msta, शून्य, msta->rates);
	msta->rate_probe = false;
	mt7603_wtbl_set_smps(dev, msta,
			     sta->smps_mode == IEEE80211_SMPS_DYNAMIC);
	spin_unlock_bh(&dev->mt76.lock);
पूर्ण

अटल व्योम
mt7603_set_coverage_class(काष्ठा ieee80211_hw *hw, s16 coverage_class)
अणु
	काष्ठा mt7603_dev *dev = hw->priv;

	mutex_lock(&dev->mt76.mutex);
	dev->coverage_class = max_t(s16, coverage_class, 0);
	mt7603_mac_set_timing(dev);
	mutex_unlock(&dev->mt76.mutex);
पूर्ण

अटल व्योम mt7603_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_tx_control *control,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt7603_dev *dev = hw->priv;
	काष्ठा mt76_wcid *wcid = &dev->global_sta.wcid;

	अगर (control->sta) अणु
		काष्ठा mt7603_sta *msta;

		msta = (काष्ठा mt7603_sta *)control->sta->drv_priv;
		wcid = &msta->wcid;
	पूर्ण अन्यथा अगर (vअगर) अणु
		काष्ठा mt7603_vअगर *mvअगर;

		mvअगर = (काष्ठा mt7603_vअगर *)vअगर->drv_priv;
		wcid = &mvअगर->sta.wcid;
	पूर्ण

	mt76_tx(&dev->mphy, control->sta, wcid, skb);
पूर्ण

स्थिर काष्ठा ieee80211_ops mt7603_ops = अणु
	.tx = mt7603_tx,
	.start = mt7603_start,
	.stop = mt7603_stop,
	.add_पूर्णांकerface = mt7603_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = mt7603_हटाओ_पूर्णांकerface,
	.config = mt7603_config,
	.configure_filter = mt7603_configure_filter,
	.bss_info_changed = mt7603_bss_info_changed,
	.sta_state = mt76_sta_state,
	.sta_pre_rcu_हटाओ = mt76_sta_pre_rcu_हटाओ,
	.set_key = mt7603_set_key,
	.conf_tx = mt7603_conf_tx,
	.sw_scan_start = mt76_sw_scan,
	.sw_scan_complete = mt76_sw_scan_complete,
	.flush = mt7603_flush,
	.ampdu_action = mt7603_ampdu_action,
	.get_txघातer = mt76_get_txघातer,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sta_rate_tbl_update = mt7603_sta_rate_tbl_update,
	.release_buffered_frames = mt7603_release_buffered_frames,
	.set_coverage_class = mt7603_set_coverage_class,
	.set_tim = mt76_set_tim,
	.get_survey = mt76_get_survey,
	.get_antenna = mt76_get_antenna,
पूर्ण;

MODULE_LICENSE("Dual BSD/GPL");

अटल पूर्णांक __init mt7603_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&mt76_wmac_driver);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_PCI
	ret = pci_रेजिस्टर_driver(&mt7603_pci_driver);
	अगर (ret)
		platक्रमm_driver_unरेजिस्टर(&mt76_wmac_driver);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम __निकास mt7603_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver(&mt7603_pci_driver);
#पूर्ण_अगर
	platक्रमm_driver_unरेजिस्टर(&mt76_wmac_driver);
पूर्ण

module_init(mt7603_init);
module_निकास(mt7603_निकास);
