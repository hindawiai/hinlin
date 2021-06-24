<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00mac
	Abstract: rt2x00 generic mac80211 routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"

अटल पूर्णांक rt2x00mac_tx_rts_cts(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा data_queue *queue,
				काष्ठा sk_buff *frag_skb)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(frag_skb);
	काष्ठा ieee80211_tx_info *rts_info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक data_length;
	पूर्णांक retval = 0;

	अगर (tx_info->control.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		data_length = माप(काष्ठा ieee80211_cts);
	अन्यथा
		data_length = माप(काष्ठा ieee80211_rts);

	skb = dev_alloc_skb(data_length + rt2x00dev->hw->extra_tx_headroom);
	अगर (unlikely(!skb)) अणु
		rt2x00_warn(rt2x00dev, "Failed to create RTS/CTS frame\n");
		वापस -ENOMEM;
	पूर्ण

	skb_reserve(skb, rt2x00dev->hw->extra_tx_headroom);
	skb_put(skb, data_length);

	/*
	 * Copy TX inक्रमmation over from original frame to
	 * RTS/CTS frame. Note that we set the no encryption flag
	 * since we करोn't want this frame to be encrypted.
	 * RTS frames should be acked, जबतक CTS-to-self frames
	 * should not. The पढ़ोy क्रम TX flag is cleared to prevent
	 * it being स्वतःmatically send when the descriptor is
	 * written to the hardware.
	 */
	स_नकल(skb->cb, frag_skb->cb, माप(skb->cb));
	rts_info = IEEE80211_SKB_CB(skb);
	rts_info->control.rates[0].flags &= ~IEEE80211_TX_RC_USE_RTS_CTS;
	rts_info->control.rates[0].flags &= ~IEEE80211_TX_RC_USE_CTS_PROTECT;

	अगर (tx_info->control.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		rts_info->flags |= IEEE80211_TX_CTL_NO_ACK;
	अन्यथा
		rts_info->flags &= ~IEEE80211_TX_CTL_NO_ACK;

	/* Disable hardware encryption */
	rts_info->control.hw_key = शून्य;

	/*
	 * RTS/CTS frame should use the length of the frame plus any
	 * encryption overhead that will be added by the hardware.
	 */
	data_length += rt2x00crypto_tx_overhead(rt2x00dev, skb);

	अगर (tx_info->control.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		ieee80211_ctstoself_get(rt2x00dev->hw, tx_info->control.vअगर,
					frag_skb->data, data_length, tx_info,
					(काष्ठा ieee80211_cts *)(skb->data));
	अन्यथा
		ieee80211_rts_get(rt2x00dev->hw, tx_info->control.vअगर,
				  frag_skb->data, data_length, tx_info,
				  (काष्ठा ieee80211_rts *)(skb->data));

	retval = rt2x00queue_ग_लिखो_tx_frame(queue, skb, शून्य, true);
	अगर (retval) अणु
		dev_kमुक्त_skb_any(skb);
		rt2x00_warn(rt2x00dev, "Failed to send RTS/CTS frame\n");
	पूर्ण

	वापस retval;
पूर्ण

व्योम rt2x00mac_tx(काष्ठा ieee80211_hw *hw,
		  काष्ठा ieee80211_tx_control *control,
		  काष्ठा sk_buff *skb)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	क्रमागत data_queue_qid qid = skb_get_queue_mapping(skb);
	काष्ठा data_queue *queue = शून्य;

	/*
	 * Mac80211 might be calling this function जबतक we are trying
	 * to हटाओ the device or perhaps suspending it.
	 * Note that we can only stop the TX queues inside the TX path
	 * due to possible race conditions in mac80211.
	 */
	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		जाओ निकास_मुक्त_skb;

	/*
	 * Use the ATIM queue अगर appropriate and present.
	 */
	अगर (tx_info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM &&
	    rt2x00_has_cap_flag(rt2x00dev, REQUIRE_ATIM_QUEUE))
		qid = QID_ATIM;

	queue = rt2x00queue_get_tx_queue(rt2x00dev, qid);
	अगर (unlikely(!queue)) अणु
		rt2x00_err(rt2x00dev,
			   "Attempt to send packet over invalid queue %d\n"
			   "Please file bug report to %s\n", qid, DRV_PROJECT);
		जाओ निकास_मुक्त_skb;
	पूर्ण

	/*
	 * If CTS/RTS is required. create and queue that frame first.
	 * Make sure we have at least enough entries available to send
	 * this CTS/RTS frame as well as the data frame.
	 * Note that when the driver has set the set_rts_threshold()
	 * callback function it करोesn't need software generation of
	 * either RTS or CTS-to-self frame and handles everything
	 * inside the hardware.
	 */
	अगर (!rt2x00dev->ops->hw->set_rts_threshold &&
	    (tx_info->control.rates[0].flags & (IEEE80211_TX_RC_USE_RTS_CTS |
						IEEE80211_TX_RC_USE_CTS_PROTECT))) अणु
		अगर (rt2x00queue_available(queue) <= 1) अणु
			/*
			 * Recheck क्रम full queue under lock to aव्योम race
			 * conditions with rt2x00lib_txकरोne().
			 */
			spin_lock(&queue->tx_lock);
			अगर (rt2x00queue_threshold(queue))
				rt2x00queue_छोड़ो_queue(queue);
			spin_unlock(&queue->tx_lock);

			जाओ निकास_मुक्त_skb;
		पूर्ण

		अगर (rt2x00mac_tx_rts_cts(rt2x00dev, queue, skb))
			जाओ निकास_मुक्त_skb;
	पूर्ण

	अगर (unlikely(rt2x00queue_ग_लिखो_tx_frame(queue, skb, control->sta, false)))
		जाओ निकास_मुक्त_skb;

	वापस;

 निकास_मुक्त_skb:
	ieee80211_मुक्त_txskb(hw, skb);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_tx);

पूर्णांक rt2x00mac_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस 0;

	अगर (test_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags)) अणु
		/*
		 * This is special हाल क्रम ieee80211_restart_hw(), otherwise
		 * mac80211 never call start() two बार in row without stop();
		 */
		set_bit(DEVICE_STATE_RESET, &rt2x00dev->flags);
		rt2x00dev->ops->lib->pre_reset_hw(rt2x00dev);
		rt2x00lib_stop(rt2x00dev);
	पूर्ण
	वापस rt2x00lib_start(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_start);

व्योम rt2x00mac_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस;

	rt2x00lib_stop(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_stop);

व्योम
rt2x00mac_reconfig_complete(काष्ठा ieee80211_hw *hw,
			    क्रमागत ieee80211_reconfig_type reconfig_type)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	अगर (reconfig_type == IEEE80211_RECONFIG_TYPE_RESTART)
		clear_bit(DEVICE_STATE_RESET, &rt2x00dev->flags);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_reconfig_complete);

पूर्णांक rt2x00mac_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा rt2x00_पूर्णांकf *पूर्णांकf = vअगर_to_पूर्णांकf(vअगर);
	काष्ठा data_queue *queue = rt2x00dev->bcn;
	काष्ठा queue_entry *entry = शून्य;
	अचिन्हित पूर्णांक i;

	/*
	 * Don't allow पूर्णांकerfaces to be added
	 * the device has disappeared.
	 */
	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) ||
	    !test_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags))
		वापस -ENODEV;

	/*
	 * Loop through all beacon queues to find a मुक्त
	 * entry. Since there are as much beacon entries
	 * as the maximum पूर्णांकerfaces, this search shouldn't
	 * fail.
	 */
	क्रम (i = 0; i < queue->limit; i++) अणु
		entry = &queue->entries[i];
		अगर (!test_and_set_bit(ENTRY_BCN_ASSIGNED, &entry->flags))
			अवरोध;
	पूर्ण

	अगर (unlikely(i == queue->limit))
		वापस -ENOBUFS;

	/*
	 * We are now असलolutely sure the पूर्णांकerface can be created,
	 * increase पूर्णांकerface count and start initialization.
	 */

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		rt2x00dev->पूर्णांकf_ap_count++;
	अन्यथा
		rt2x00dev->पूर्णांकf_sta_count++;

	mutex_init(&पूर्णांकf->beacon_skb_mutex);
	पूर्णांकf->beacon = entry;

	/*
	 * The MAC address must be configured after the device
	 * has been initialized. Otherwise the device can reset
	 * the MAC रेजिस्टरs.
	 * The BSSID address must only be configured in AP mode,
	 * however we should not send an empty BSSID address क्रम
	 * STA पूर्णांकerfaces at this समय, since this can cause
	 * invalid behavior in the device.
	 */
	rt2x00lib_config_पूर्णांकf(rt2x00dev, पूर्णांकf, vअगर->type,
			      vअगर->addr, शून्य);

	/*
	 * Some filters depend on the current working mode. We can क्रमce
	 * an update during the next configure_filter() run by mac80211 by
	 * resetting the current packet_filter state.
	 */
	rt2x00dev->packet_filter = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_add_पूर्णांकerface);

व्योम rt2x00mac_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा rt2x00_पूर्णांकf *पूर्णांकf = vअगर_to_पूर्णांकf(vअगर);

	/*
	 * Don't allow पूर्णांकerfaces to be हटाओ जबतक
	 * either the device has disappeared or when
	 * no पूर्णांकerface is present.
	 */
	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) ||
	    (vअगर->type == NL80211_IFTYPE_AP && !rt2x00dev->पूर्णांकf_ap_count) ||
	    (vअगर->type != NL80211_IFTYPE_AP && !rt2x00dev->पूर्णांकf_sta_count))
		वापस;

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		rt2x00dev->पूर्णांकf_ap_count--;
	अन्यथा
		rt2x00dev->पूर्णांकf_sta_count--;

	/*
	 * Release beacon entry so it is available क्रम
	 * new पूर्णांकerfaces again.
	 */
	clear_bit(ENTRY_BCN_ASSIGNED, &पूर्णांकf->beacon->flags);

	/*
	 * Make sure the bssid and mac address रेजिस्टरs
	 * are cleared to prevent false ACKing of frames.
	 */
	rt2x00lib_config_पूर्णांकf(rt2x00dev, पूर्णांकf,
			      NL80211_IFTYPE_UNSPECIFIED, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_हटाओ_पूर्णांकerface);

पूर्णांक rt2x00mac_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;

	/*
	 * mac80211 might be calling this function जबतक we are trying
	 * to हटाओ the device or perhaps suspending it.
	 */
	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस 0;

	/*
	 * Some configuration parameters (e.g. channel and antenna values) can
	 * only be set when the radio is enabled, but करो require the RX to
	 * be off. During this period we should keep link tuning enabled,
	 * अगर क्रम any reason the link tuner must be reset, this will be
	 * handled by rt2x00lib_config().
	 */
	rt2x00queue_stop_queue(rt2x00dev->rx);

	/* Do not race with with link tuner. */
	mutex_lock(&rt2x00dev->conf_mutex);

	/*
	 * When we've just turned on the radio, we want to reprogram
	 * everything to ensure a consistent state
	 */
	rt2x00lib_config(rt2x00dev, conf, changed);

	/*
	 * After the radio has been enabled we need to configure
	 * the antenna to the शेष settings. rt2x00lib_config_antenna()
	 * should determine अगर any action should be taken based on
	 * checking अगर भागersity has been enabled or no antenna changes
	 * have been made since the last configuration change.
	 */
	rt2x00lib_config_antenna(rt2x00dev, rt2x00dev->शेष_ant);

	mutex_unlock(&rt2x00dev->conf_mutex);

	/* Turn RX back on */
	rt2x00queue_start_queue(rt2x00dev->rx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_config);

व्योम rt2x00mac_configure_filter(काष्ठा ieee80211_hw *hw,
				अचिन्हित पूर्णांक changed_flags,
				अचिन्हित पूर्णांक *total_flags,
				u64 multicast)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	/*
	 * Mask off any flags we are going to ignore
	 * from the total_flags field.
	 */
	*total_flags &=
	    FIF_ALLMULTI |
	    FIF_FCSFAIL |
	    FIF_PLCPFAIL |
	    FIF_CONTROL |
	    FIF_PSPOLL |
	    FIF_OTHER_BSS;

	/*
	 * Apply some rules to the filters:
	 * - Some filters imply dअगरferent filters to be set.
	 * - Some things we can't filter out at all.
	 * - Multicast filter seems to समाप्त broadcast traffic so never use it.
	 */
	*total_flags |= FIF_ALLMULTI;

	/*
	 * If the device has a single filter क्रम all control frames,
	 * FIF_CONTROL and FIF_PSPOLL flags imply each other.
	 * And अगर the device has more than one filter क्रम control frames
	 * of dअगरferent types, but has no a separate filter क्रम PS Poll frames,
	 * FIF_CONTROL flag implies FIF_PSPOLL.
	 */
	अगर (!rt2x00_has_cap_control_filters(rt2x00dev)) अणु
		अगर (*total_flags & FIF_CONTROL || *total_flags & FIF_PSPOLL)
			*total_flags |= FIF_CONTROL | FIF_PSPOLL;
	पूर्ण
	अगर (!rt2x00_has_cap_control_filter_pspoll(rt2x00dev)) अणु
		अगर (*total_flags & FIF_CONTROL)
			*total_flags |= FIF_PSPOLL;
	पूर्ण

	rt2x00dev->packet_filter = *total_flags;

	rt2x00dev->ops->lib->config_filter(rt2x00dev, *total_flags);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_configure_filter);

अटल व्योम rt2x00mac_set_tim_iter(व्योम *data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_पूर्णांकf *पूर्णांकf = vअगर_to_पूर्णांकf(vअगर);

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_ADHOC &&
	    vअगर->type != NL80211_IFTYPE_MESH_POINT)
		वापस;

	set_bit(DELAYED_UPDATE_BEACON, &पूर्णांकf->delayed_flags);
पूर्ण

पूर्णांक rt2x00mac_set_tim(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		      bool set)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस 0;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		rt2x00dev->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		rt2x00mac_set_tim_iter, rt2x00dev);

	/* queue work to upodate the beacon ढाँचा */
	ieee80211_queue_work(rt2x00dev->hw, &rt2x00dev->पूर्णांकf_work);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_set_tim);

#अगर_घोषित CONFIG_RT2X00_LIB_CRYPTO
अटल व्योम स_नकल_tkip(काष्ठा rt2x00lib_crypto *crypto, u8 *key, u8 key_len)
अणु
	अगर (key_len > NL80211_TKIP_DATA_OFFSET_ENCR_KEY)
		स_नकल(crypto->key,
		       &key[NL80211_TKIP_DATA_OFFSET_ENCR_KEY],
		       माप(crypto->key));

	अगर (key_len > NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY)
		स_नकल(crypto->tx_mic,
		       &key[NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY],
		       माप(crypto->tx_mic));

	अगर (key_len > NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY)
		स_नकल(crypto->rx_mic,
		       &key[NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY],
		       माप(crypto->rx_mic));
पूर्ण

पूर्णांक rt2x00mac_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		      काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		      काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	पूर्णांक (*set_key) (काष्ठा rt2x00_dev *rt2x00dev,
			काष्ठा rt2x00lib_crypto *crypto,
			काष्ठा ieee80211_key_conf *key);
	काष्ठा rt2x00lib_crypto crypto;
	अटल स्थिर u8 bcast_addr[ETH_ALEN] =
		अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, पूर्ण;
	काष्ठा rt2x00_sta *sta_priv = शून्य;

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस 0;

	/* The hardware can't करो MFP */
	अगर (!rt2x00_has_cap_hw_crypto(rt2x00dev) || (sta && sta->mfp))
		वापस -EOPNOTSUPP;

	/*
	 * To support IBSS RSN, करोn't program group keys in IBSS, the
	 * hardware will then not attempt to decrypt the frames.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		वापस -EOPNOTSUPP;

	अगर (key->keylen > 32)
		वापस -ENOSPC;

	स_रखो(&crypto, 0, माप(crypto));

	crypto.bssidx = rt2x00lib_get_bssidx(rt2x00dev, vअगर);
	crypto.cipher = rt2x00crypto_key_to_cipher(key);
	अगर (crypto.cipher == CIPHER_NONE)
		वापस -EOPNOTSUPP;
	अगर (crypto.cipher == CIPHER_TKIP && rt2x00_is_usb(rt2x00dev))
		वापस -EOPNOTSUPP;

	crypto.cmd = cmd;

	अगर (sta) अणु
		crypto.address = sta->addr;
		sta_priv = sta_to_rt2x00_sta(sta);
		crypto.wcid = sta_priv->wcid;
	पूर्ण अन्यथा
		crypto.address = bcast_addr;

	अगर (crypto.cipher == CIPHER_TKIP)
		स_नकल_tkip(&crypto, &key->key[0], key->keylen);
	अन्यथा
		स_नकल(crypto.key, &key->key[0], key->keylen);
	/*
	 * Each BSS has a maximum of 4 shared keys.
	 * Shared key index values:
	 *	0) BSS0 key0
	 *	1) BSS0 key1
	 *	...
	 *	4) BSS1 key0
	 *	...
	 *	8) BSS2 key0
	 *	...
	 * Both pairwise as shared key indeces are determined by
	 * driver. This is required because the hardware requires
	 * keys to be asचिन्हित in correct order (When key 1 is
	 * provided but key 0 is not, then the key is not found
	 * by the hardware during RX).
	 */
	अगर (cmd == SET_KEY)
		key->hw_key_idx = 0;

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		set_key = rt2x00dev->ops->lib->config_pairwise_key;
	अन्यथा
		set_key = rt2x00dev->ops->lib->config_shared_key;

	अगर (!set_key)
		वापस -EOPNOTSUPP;

	वापस set_key(rt2x00dev, &crypto, key);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_set_key);
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_CRYPTO */

व्योम rt2x00mac_sw_scan_start(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     स्थिर u8 *mac_addr)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	set_bit(DEVICE_STATE_SCANNING, &rt2x00dev->flags);
	rt2x00link_stop_tuner(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_sw_scan_start);

व्योम rt2x00mac_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	clear_bit(DEVICE_STATE_SCANNING, &rt2x00dev->flags);
	rt2x00link_start_tuner(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_sw_scan_complete);

पूर्णांक rt2x00mac_get_stats(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	/*
	 * The करोt11ACKFailureCount, करोt11RTSFailureCount and
	 * करोt11RTSSuccessCount are updated in पूर्णांकerrupt समय.
	 * करोt11FCSErrorCount is updated in the link tuner.
	 */
	स_नकल(stats, &rt2x00dev->low_level_stats, माप(*stats));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_get_stats);

व्योम rt2x00mac_bss_info_changed(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_bss_conf *bss_conf,
				u32 changes)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा rt2x00_पूर्णांकf *पूर्णांकf = vअगर_to_पूर्णांकf(vअगर);

	/*
	 * mac80211 might be calling this function जबतक we are trying
	 * to हटाओ the device or perhaps suspending it.
	 */
	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस;

	/*
	 * Update the BSSID.
	 */
	अगर (changes & BSS_CHANGED_BSSID)
		rt2x00lib_config_पूर्णांकf(rt2x00dev, पूर्णांकf, vअगर->type, शून्य,
				      bss_conf->bssid);

	/*
	 * Start/stop beaconing.
	 */
	अगर (changes & BSS_CHANGED_BEACON_ENABLED) अणु
		mutex_lock(&पूर्णांकf->beacon_skb_mutex);
		अगर (!bss_conf->enable_beacon && पूर्णांकf->enable_beacon) अणु
			rt2x00dev->पूर्णांकf_beaconing--;
			पूर्णांकf->enable_beacon = false;

			अगर (rt2x00dev->पूर्णांकf_beaconing == 0) अणु
				/*
				 * Last beaconing पूर्णांकerface disabled
				 * -> stop beacon queue.
				 */
				rt2x00queue_stop_queue(rt2x00dev->bcn);
			पूर्ण
			/*
			 * Clear beacon in the H/W क्रम this vअगर. This is needed
			 * to disable beaconing on this particular पूर्णांकerface
			 * and keep it running on other पूर्णांकerfaces.
			 */
			rt2x00queue_clear_beacon(rt2x00dev, vअगर);
		पूर्ण अन्यथा अगर (bss_conf->enable_beacon && !पूर्णांकf->enable_beacon) अणु
			rt2x00dev->पूर्णांकf_beaconing++;
			पूर्णांकf->enable_beacon = true;
			/*
			 * Upload beacon to the H/W. This is only required on
			 * USB devices. PCI devices fetch beacons periodically.
			 */
			अगर (rt2x00_is_usb(rt2x00dev))
				rt2x00queue_update_beacon(rt2x00dev, vअगर);

			अगर (rt2x00dev->पूर्णांकf_beaconing == 1) अणु
				/*
				 * First beaconing पूर्णांकerface enabled
				 * -> start beacon queue.
				 */
				rt2x00queue_start_queue(rt2x00dev->bcn);
			पूर्ण
		पूर्ण
		mutex_unlock(&पूर्णांकf->beacon_skb_mutex);
	पूर्ण

	/*
	 * When the association status has changed we must reset the link
	 * tuner counter. This is because some drivers determine अगर they
	 * should perक्रमm link tuning based on the number of seconds
	 * जबतक associated or not associated.
	 */
	अगर (changes & BSS_CHANGED_ASSOC) अणु
		rt2x00dev->link.count = 0;

		अगर (bss_conf->assoc)
			rt2x00dev->पूर्णांकf_associated++;
		अन्यथा
			rt2x00dev->पूर्णांकf_associated--;

		rt2x00leds_led_assoc(rt2x00dev, !!rt2x00dev->पूर्णांकf_associated);
	पूर्ण

	/*
	 * When the erp inक्रमmation has changed, we should perक्रमm
	 * additional configuration steps. For all other changes we are करोne.
	 */
	अगर (changes & (BSS_CHANGED_ERP_CTS_PROT | BSS_CHANGED_ERP_PREAMBLE |
		       BSS_CHANGED_ERP_SLOT | BSS_CHANGED_BASIC_RATES |
		       BSS_CHANGED_BEACON_INT | BSS_CHANGED_HT))
		rt2x00lib_config_erp(rt2x00dev, पूर्णांकf, bss_conf, changes);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_bss_info_changed);

पूर्णांक rt2x00mac_conf_tx(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_vअगर *vअगर, u16 queue_idx,
		      स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा data_queue *queue;

	queue = rt2x00queue_get_tx_queue(rt2x00dev, queue_idx);
	अगर (unlikely(!queue))
		वापस -EINVAL;

	/*
	 * The passed variables are stored as real value ((2^n)-1).
	 * Ralink रेजिस्टरs require to know the bit number 'n'.
	 */
	अगर (params->cw_min > 0)
		queue->cw_min = fls(params->cw_min);
	अन्यथा
		queue->cw_min = 5; /* cw_min: 2^5 = 32. */

	अगर (params->cw_max > 0)
		queue->cw_max = fls(params->cw_max);
	अन्यथा
		queue->cw_max = 10; /* cw_min: 2^10 = 1024. */

	queue->aअगरs = params->aअगरs;
	queue->txop = params->txop;

	rt2x00_dbg(rt2x00dev,
		   "Configured TX queue %d - CWmin: %d, CWmax: %d, Aifs: %d, TXop: %d\n",
		   queue_idx, queue->cw_min, queue->cw_max, queue->aअगरs,
		   queue->txop);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_conf_tx);

व्योम rt2x00mac_rfसमाप्त_poll(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	bool active = !!rt2x00dev->ops->lib->rfसमाप्त_poll(rt2x00dev);

	wiphy_rfसमाप्त_set_hw_state(hw->wiphy, !active);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_rfसमाप्त_poll);

व्योम rt2x00mac_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		     u32 queues, bool drop)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा data_queue *queue;

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस;

	set_bit(DEVICE_STATE_FLUSHING, &rt2x00dev->flags);

	tx_queue_क्रम_each(rt2x00dev, queue)
		rt2x00queue_flush_queue(queue, drop);

	clear_bit(DEVICE_STATE_FLUSHING, &rt2x00dev->flags);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_flush);

पूर्णांक rt2x00mac_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;
	काष्ठा antenna_setup *def = &rt2x00dev->शेष_ant;
	काष्ठा antenna_setup setup;

	// The antenna value is not supposed to be 0,
	// or exceed the maximum number of antenna's.
	अगर (!tx_ant || (tx_ant & ~3) || !rx_ant || (rx_ant & ~3))
		वापस -EINVAL;

	// When the client tried to configure the antenna to or from
	// भागersity mode, we must reset the शेष antenna as well
	// as that controls the भागersity चयन.
	अगर (ant->flags & ANTENNA_TX_DIVERSITY && tx_ant != 3)
		ant->flags &= ~ANTENNA_TX_DIVERSITY;
	अगर (ant->flags & ANTENNA_RX_DIVERSITY && rx_ant != 3)
		ant->flags &= ~ANTENNA_RX_DIVERSITY;

	// If भागersity is being enabled, check अगर we need hardware
	// or software भागersity. In the latter हाल, reset the value,
	// and make sure we update the antenna flags to have the
	// link tuner pick up the भागersity tuning.
	अगर (tx_ant == 3 && def->tx == ANTENNA_SW_DIVERSITY) अणु
		tx_ant = ANTENNA_SW_DIVERSITY;
		ant->flags |= ANTENNA_TX_DIVERSITY;
	पूर्ण

	अगर (rx_ant == 3 && def->rx == ANTENNA_SW_DIVERSITY) अणु
		rx_ant = ANTENNA_SW_DIVERSITY;
		ant->flags |= ANTENNA_RX_DIVERSITY;
	पूर्ण

	setup.tx = tx_ant;
	setup.rx = rx_ant;
	setup.rx_chain_num = 0;
	setup.tx_chain_num = 0;

	rt2x00lib_config_antenna(rt2x00dev, setup);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_set_antenna);

पूर्णांक rt2x00mac_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा link_ant *ant = &rt2x00dev->link.ant;
	काष्ठा antenna_setup *active = &rt2x00dev->link.ant.active;

	// When software भागersity is active, we must report this to the
	// client and not the current active antenna state.
	अगर (ant->flags & ANTENNA_TX_DIVERSITY)
		*tx_ant = ANTENNA_HW_DIVERSITY;
	अन्यथा
		*tx_ant = active->tx;

	अगर (ant->flags & ANTENNA_RX_DIVERSITY)
		*rx_ant = ANTENNA_HW_DIVERSITY;
	अन्यथा
		*rx_ant = active->rx;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_get_antenna);

व्योम rt2x00mac_get_ringparam(काष्ठा ieee80211_hw *hw,
			     u32 *tx, u32 *tx_max, u32 *rx, u32 *rx_max)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा data_queue *queue;

	tx_queue_क्रम_each(rt2x00dev, queue) अणु
		*tx += queue->length;
		*tx_max += queue->limit;
	पूर्ण

	*rx = rt2x00dev->rx->length;
	*rx_max = rt2x00dev->rx->limit;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_get_ringparam);

bool rt2x00mac_tx_frames_pending(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा data_queue *queue;

	tx_queue_क्रम_each(rt2x00dev, queue) अणु
		अगर (!rt2x00queue_empty(queue))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00mac_tx_frames_pending);
