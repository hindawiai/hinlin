<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2010 Willow Garage <http://www.willowgarage.com>
	Copyright (C) 2004 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 generic device routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"

/*
 * Utility functions.
 */
u32 rt2x00lib_get_bssidx(काष्ठा rt2x00_dev *rt2x00dev,
			 काष्ठा ieee80211_vअगर *vअगर)
अणु
	/*
	 * When in STA mode, bssidx is always 0 otherwise local_address[5]
	 * contains the bss number, see BSS_ID_MASK comments क्रम details.
	 */
	अगर (rt2x00dev->पूर्णांकf_sta_count)
		वापस 0;
	वापस vअगर->addr[5] & (rt2x00dev->ops->max_ap_पूर्णांकf - 1);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_get_bssidx);

/*
 * Radio control handlers.
 */
पूर्णांक rt2x00lib_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक status;

	/*
	 * Don't enable the radio twice.
	 * And check अगर the hardware button has been disabled.
	 */
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस 0;

	/*
	 * Initialize all data queues.
	 */
	rt2x00queue_init_queues(rt2x00dev);

	/*
	 * Enable radio.
	 */
	status =
	    rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_RADIO_ON);
	अगर (status)
		वापस status;

	rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_RADIO_IRQ_ON);

	rt2x00leds_led_radio(rt2x00dev, true);
	rt2x00led_led_activity(rt2x00dev, true);

	set_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags);

	/*
	 * Enable queues.
	 */
	rt2x00queue_start_queues(rt2x00dev);
	rt2x00link_start_tuner(rt2x00dev);

	/*
	 * Start watchकरोg monitoring.
	 */
	rt2x00link_start_watchकरोg(rt2x00dev);

	वापस 0;
पूर्ण

व्योम rt2x00lib_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (!test_and_clear_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस;

	/*
	 * Stop watchकरोg monitoring.
	 */
	rt2x00link_stop_watchकरोg(rt2x00dev);

	/*
	 * Stop all queues
	 */
	rt2x00link_stop_tuner(rt2x00dev);
	rt2x00queue_stop_queues(rt2x00dev);
	rt2x00queue_flush_queues(rt2x00dev, true);

	/*
	 * Disable radio.
	 */
	rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_RADIO_OFF);
	rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_RADIO_IRQ_OFF);
	rt2x00led_led_activity(rt2x00dev, false);
	rt2x00leds_led_radio(rt2x00dev, false);
पूर्ण

अटल व्योम rt2x00lib_पूर्णांकf_scheduled_iter(व्योम *data, u8 *mac,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = data;
	काष्ठा rt2x00_पूर्णांकf *पूर्णांकf = vअगर_to_पूर्णांकf(vअगर);

	/*
	 * It is possible the radio was disabled जबतक the work had been
	 * scheduled. If that happens we should वापस here immediately,
	 * note that in the spinlock रक्षित area above the delayed_flags
	 * have been cleared correctly.
	 */
	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस;

	अगर (test_and_clear_bit(DELAYED_UPDATE_BEACON, &पूर्णांकf->delayed_flags)) अणु
		mutex_lock(&पूर्णांकf->beacon_skb_mutex);
		rt2x00queue_update_beacon(rt2x00dev, vअगर);
		mutex_unlock(&पूर्णांकf->beacon_skb_mutex);
	पूर्ण
पूर्ण

अटल व्योम rt2x00lib_पूर्णांकf_scheduled(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, पूर्णांकf_work);

	/*
	 * Iterate over each पूर्णांकerface and perक्रमm the
	 * requested configurations.
	 */
	ieee80211_iterate_active_पूर्णांकerfaces(rt2x00dev->hw,
					    IEEE80211_IFACE_ITER_RESUME_ALL,
					    rt2x00lib_पूर्णांकf_scheduled_iter,
					    rt2x00dev);
पूर्ण

अटल व्योम rt2x00lib_स्वतःwakeup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, स्वतःwakeup_work.work);

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस;

	अगर (rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_AWAKE))
		rt2x00_err(rt2x00dev, "Device failed to wakeup\n");
	clear_bit(CONFIG_POWERSAVING, &rt2x00dev->flags);
पूर्ण

/*
 * Interrupt context handlers.
 */
अटल व्योम rt2x00lib_bc_buffer_iter(व्योम *data, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_tx_control control = अणुपूर्ण;
	काष्ठा rt2x00_dev *rt2x00dev = data;
	काष्ठा sk_buff *skb;

	/*
	 * Only AP mode पूर्णांकerfaces करो broad- and multicast buffering
	 */
	अगर (vअगर->type != NL80211_IFTYPE_AP)
		वापस;

	/*
	 * Send out buffered broad- and multicast frames
	 */
	skb = ieee80211_get_buffered_bc(rt2x00dev->hw, vअगर);
	जबतक (skb) अणु
		rt2x00mac_tx(rt2x00dev->hw, &control, skb);
		skb = ieee80211_get_buffered_bc(rt2x00dev->hw, vअगर);
	पूर्ण
पूर्ण

अटल व्योम rt2x00lib_beaconupdate_iter(व्योम *data, u8 *mac,
					काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = data;

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_ADHOC &&
	    vअगर->type != NL80211_IFTYPE_MESH_POINT)
		वापस;

	/*
	 * Update the beacon without locking. This is safe on PCI devices
	 * as they only update the beacon periodically here. This should
	 * never be called क्रम USB devices.
	 */
	WARN_ON(rt2x00_is_usb(rt2x00dev));
	rt2x00queue_update_beacon(rt2x00dev, vअगर);
पूर्ण

व्योम rt2x00lib_beaconकरोne(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस;

	/* send buffered bc/mc frames out क्रम every bssid */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		rt2x00dev->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		rt2x00lib_bc_buffer_iter, rt2x00dev);
	/*
	 * Devices with pre tbtt पूर्णांकerrupt करोn't need to update the beacon
	 * here as they will fetch the next beacon directly prior to
	 * transmission.
	 */
	अगर (rt2x00_has_cap_pre_tbtt_पूर्णांकerrupt(rt2x00dev))
		वापस;

	/* fetch next beacon */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		rt2x00dev->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		rt2x00lib_beaconupdate_iter, rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_beaconकरोne);

व्योम rt2x00lib_pretbtt(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस;

	/* fetch next beacon */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		rt2x00dev->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		rt2x00lib_beaconupdate_iter, rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_pretbtt);

व्योम rt2x00lib_dmastart(काष्ठा queue_entry *entry)
अणु
	set_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags);
	rt2x00queue_index_inc(entry, Q_INDEX);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_dmastart);

व्योम rt2x00lib_dmaकरोne(काष्ठा queue_entry *entry)
अणु
	set_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags);
	clear_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags);
	rt2x00queue_index_inc(entry, Q_INDEX_DMA_DONE);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_dmaकरोne);

अटल अंतरभूत पूर्णांक rt2x00lib_txकरोne_bar_status(काष्ठा queue_entry *entry)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा ieee80211_bar *bar = (व्योम *) entry->skb->data;
	काष्ठा rt2x00_bar_list_entry *bar_entry;
	पूर्णांक ret;

	अगर (likely(!ieee80211_is_back_req(bar->frame_control)))
		वापस 0;

	/*
	 * Unlike all other frames, the status report क्रम BARs करोes
	 * not directly come from the hardware as it is incapable of
	 * matching a BA to a previously send BAR. The hardware will
	 * report all BARs as अगर they weren't acked at all.
	 *
	 * Instead the RX-path will scan क्रम incoming BAs and set the
	 * block_acked flag अगर it sees one that was likely caused by
	 * a BAR from us.
	 *
	 * Remove reमुख्यing BARs here and वापस their status क्रम
	 * TX करोne processing.
	 */
	ret = 0;
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(bar_entry, &rt2x00dev->bar_list, list) अणु
		अगर (bar_entry->entry != entry)
			जारी;

		spin_lock_bh(&rt2x00dev->bar_list_lock);
		/* Return whether this BAR was blockacked or not */
		ret = bar_entry->block_acked;
		/* Remove the BAR from our checklist */
		list_del_rcu(&bar_entry->list);
		spin_unlock_bh(&rt2x00dev->bar_list_lock);
		kमुक्त_rcu(bar_entry, head);

		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल व्योम rt2x00lib_fill_tx_status(काष्ठा rt2x00_dev *rt2x00dev,
				     काष्ठा ieee80211_tx_info *tx_info,
				     काष्ठा skb_frame_desc *skbdesc,
				     काष्ठा txकरोne_entry_desc *txdesc,
				     bool success)
अणु
	u8 rate_idx, rate_flags, retry_rates;
	पूर्णांक i;

	rate_idx = skbdesc->tx_rate_idx;
	rate_flags = skbdesc->tx_rate_flags;
	retry_rates = test_bit(TXDONE_FALLBACK, &txdesc->flags) ?
	    (txdesc->retry + 1) : 1;

	/*
	 * Initialize TX status
	 */
	स_रखो(&tx_info->status, 0, माप(tx_info->status));
	tx_info->status.ack_संकेत = 0;

	/*
	 * Frame was send with retries, hardware tried
	 * dअगरferent rates to send out the frame, at each
	 * retry it lowered the rate 1 step except when the
	 * lowest rate was used.
	 */
	क्रम (i = 0; i < retry_rates && i < IEEE80211_TX_MAX_RATES; i++) अणु
		tx_info->status.rates[i].idx = rate_idx - i;
		tx_info->status.rates[i].flags = rate_flags;

		अगर (rate_idx - i == 0) अणु
			/*
			 * The lowest rate (index 0) was used until the
			 * number of max retries was reached.
			 */
			tx_info->status.rates[i].count = retry_rates - i;
			i++;
			अवरोध;
		पूर्ण
		tx_info->status.rates[i].count = 1;
	पूर्ण
	अगर (i < (IEEE80211_TX_MAX_RATES - 1))
		tx_info->status.rates[i].idx = -1; /* terminate */

	अगर (test_bit(TXDONE_NO_ACK_REQ, &txdesc->flags))
		tx_info->flags |= IEEE80211_TX_CTL_NO_ACK;

	अगर (!(tx_info->flags & IEEE80211_TX_CTL_NO_ACK)) अणु
		अगर (success)
			tx_info->flags |= IEEE80211_TX_STAT_ACK;
		अन्यथा
			rt2x00dev->low_level_stats.करोt11ACKFailureCount++;
	पूर्ण

	/*
	 * Every single frame has it's own tx status, hence report
	 * every frame as ampdu of size 1.
	 *
	 * TODO: अगर we can find out how many frames were aggregated
	 * by the hw we could provide the real ampdu_len to mac80211
	 * which would allow the rc algorithm to better decide on
	 * which rates are suitable.
	 */
	अगर (test_bit(TXDONE_AMPDU, &txdesc->flags) ||
	    tx_info->flags & IEEE80211_TX_CTL_AMPDU) अणु
		tx_info->flags |= IEEE80211_TX_STAT_AMPDU |
				  IEEE80211_TX_CTL_AMPDU;
		tx_info->status.ampdu_len = 1;
		tx_info->status.ampdu_ack_len = success ? 1 : 0;
	पूर्ण

	अगर (rate_flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
		अगर (success)
			rt2x00dev->low_level_stats.करोt11RTSSuccessCount++;
		अन्यथा
			rt2x00dev->low_level_stats.करोt11RTSFailureCount++;
	पूर्ण
पूर्ण

अटल व्योम rt2x00lib_clear_entry(काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा queue_entry *entry)
अणु
	/*
	 * Make this entry available क्रम reuse.
	 */
	entry->skb = शून्य;
	entry->flags = 0;

	rt2x00dev->ops->lib->clear_entry(entry);

	rt2x00queue_index_inc(entry, Q_INDEX_DONE);

	/*
	 * If the data queue was below the threshold beक्रमe the txकरोne
	 * handler we must make sure the packet queue in the mac80211 stack
	 * is reenabled when the txकरोne handler has finished. This has to be
	 * serialized with rt2x00mac_tx(), otherwise we can wake up queue
	 * beक्रमe it was stopped.
	 */
	spin_lock_bh(&entry->queue->tx_lock);
	अगर (!rt2x00queue_threshold(entry->queue))
		rt2x00queue_unछोड़ो_queue(entry->queue);
	spin_unlock_bh(&entry->queue->tx_lock);
पूर्ण

व्योम rt2x00lib_txकरोne_nomatch(काष्ठा queue_entry *entry,
			      काष्ठा txकरोne_entry_desc *txdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	काष्ठा ieee80211_tx_info txinfo = अणुपूर्ण;
	bool success;

	/*
	 * Unmap the skb.
	 */
	rt2x00queue_unmap_skb(entry);

	/*
	 * Signal that the TX descriptor is no दीर्घer in the skb.
	 */
	skbdesc->flags &= ~SKBDESC_DESC_IN_SKB;

	/*
	 * Send frame to debugfs immediately, after this call is completed
	 * we are going to overग_लिखो the skb->cb array.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_TXDONE, entry);

	/*
	 * Determine अगर the frame has been successfully transmitted and
	 * हटाओ BARs from our check list जबतक checking क्रम their
	 * TX status.
	 */
	success =
	    rt2x00lib_txकरोne_bar_status(entry) ||
	    test_bit(TXDONE_SUCCESS, &txdesc->flags);

	अगर (!test_bit(TXDONE_UNKNOWN, &txdesc->flags)) अणु
		/*
		 * Update TX statistics.
		 */
		rt2x00dev->link.qual.tx_success += success;
		rt2x00dev->link.qual.tx_failed += !success;

		rt2x00lib_fill_tx_status(rt2x00dev, &txinfo, skbdesc, txdesc,
					 success);
		ieee80211_tx_status_noskb(rt2x00dev->hw, skbdesc->sta, &txinfo);
	पूर्ण

	dev_kमुक्त_skb_any(entry->skb);
	rt2x00lib_clear_entry(rt2x00dev, entry);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_txकरोne_nomatch);

व्योम rt2x00lib_txकरोne(काष्ठा queue_entry *entry,
		      काष्ठा txकरोne_entry_desc *txdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(entry->skb);
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	u8 skbdesc_flags = skbdesc->flags;
	अचिन्हित पूर्णांक header_length;
	bool success;

	/*
	 * Unmap the skb.
	 */
	rt2x00queue_unmap_skb(entry);

	/*
	 * Remove the extra tx headroom from the skb.
	 */
	skb_pull(entry->skb, rt2x00dev->extra_tx_headroom);

	/*
	 * Signal that the TX descriptor is no दीर्घer in the skb.
	 */
	skbdesc->flags &= ~SKBDESC_DESC_IN_SKB;

	/*
	 * Determine the length of 802.11 header.
	 */
	header_length = ieee80211_get_hdrlen_from_skb(entry->skb);

	/*
	 * Remove L2 padding which was added during
	 */
	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_L2PAD))
		rt2x00queue_हटाओ_l2pad(entry->skb, header_length);

	/*
	 * If the IV/EIV data was stripped from the frame beक्रमe it was
	 * passed to the hardware, we should now reinsert it again because
	 * mac80211 will expect the same data to be present it the
	 * frame as it was passed to us.
	 */
	अगर (rt2x00_has_cap_hw_crypto(rt2x00dev))
		rt2x00crypto_tx_insert_iv(entry->skb, header_length);

	/*
	 * Send frame to debugfs immediately, after this call is completed
	 * we are going to overग_लिखो the skb->cb array.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_TXDONE, entry);

	/*
	 * Determine अगर the frame has been successfully transmitted and
	 * हटाओ BARs from our check list जबतक checking क्रम their
	 * TX status.
	 */
	success =
	    rt2x00lib_txकरोne_bar_status(entry) ||
	    test_bit(TXDONE_SUCCESS, &txdesc->flags) ||
	    test_bit(TXDONE_UNKNOWN, &txdesc->flags);

	/*
	 * Update TX statistics.
	 */
	rt2x00dev->link.qual.tx_success += success;
	rt2x00dev->link.qual.tx_failed += !success;

	rt2x00lib_fill_tx_status(rt2x00dev, tx_info, skbdesc, txdesc, success);

	/*
	 * Only send the status report to mac80211 when it's a frame
	 * that originated in mac80211. If this was a extra frame coming
	 * through a mac80211 library call (RTS/CTS) then we should not
	 * send the status report back.
	 */
	अगर (!(skbdesc_flags & SKBDESC_NOT_MAC80211)) अणु
		अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_TASKLET_CONTEXT))
			ieee80211_tx_status(rt2x00dev->hw, entry->skb);
		अन्यथा
			ieee80211_tx_status_ni(rt2x00dev->hw, entry->skb);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(entry->skb);
	पूर्ण

	rt2x00lib_clear_entry(rt2x00dev, entry);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_txकरोne);

व्योम rt2x00lib_txकरोne_noinfo(काष्ठा queue_entry *entry, u32 status)
अणु
	काष्ठा txकरोne_entry_desc txdesc;

	txdesc.flags = 0;
	__set_bit(status, &txdesc.flags);
	txdesc.retry = 0;

	rt2x00lib_txकरोne(entry, &txdesc);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_txकरोne_noinfo);

अटल u8 *rt2x00lib_find_ie(u8 *data, अचिन्हित पूर्णांक len, u8 ie)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)data;
	u8 *pos, *end;

	pos = (u8 *)mgmt->u.beacon.variable;
	end = data + len;
	जबतक (pos < end) अणु
		अगर (pos + 2 + pos[1] > end)
			वापस शून्य;

		अगर (pos[0] == ie)
			वापस pos;

		pos += 2 + pos[1];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम rt2x00lib_sleep(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, sleep_work);

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस;

	/*
	 * Check again is घातersaving is enabled, to prevent races from delayed
	 * work execution.
	 */
	अगर (!test_bit(CONFIG_POWERSAVING, &rt2x00dev->flags))
		rt2x00lib_config(rt2x00dev, &rt2x00dev->hw->conf,
				 IEEE80211_CONF_CHANGE_PS);
पूर्ण

अटल व्योम rt2x00lib_rxकरोne_check_ba(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा sk_buff *skb,
				      काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा rt2x00_bar_list_entry *entry;
	काष्ठा ieee80211_bar *ba = (व्योम *)skb->data;

	अगर (likely(!ieee80211_is_back(ba->frame_control)))
		वापस;

	अगर (rxdesc->size < माप(*ba) + FCS_LEN)
		वापस;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(entry, &rt2x00dev->bar_list, list) अणु

		अगर (ba->start_seq_num != entry->start_seq_num)
			जारी;

#घोषणा TID_CHECK(a, b) (						\
	((a) & cpu_to_le16(IEEE80211_BAR_CTRL_TID_INFO_MASK)) ==	\
	((b) & cpu_to_le16(IEEE80211_BAR_CTRL_TID_INFO_MASK)))		\

		अगर (!TID_CHECK(ba->control, entry->control))
			जारी;

#अघोषित TID_CHECK

		अगर (!ether_addr_equal_64bits(ba->ra, entry->ta))
			जारी;

		अगर (!ether_addr_equal_64bits(ba->ta, entry->ra))
			जारी;

		/* Mark BAR since we received the according BA */
		spin_lock_bh(&rt2x00dev->bar_list_lock);
		entry->block_acked = 1;
		spin_unlock_bh(&rt2x00dev->bar_list_lock);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

पूर्ण

अटल व्योम rt2x00lib_rxकरोne_check_ps(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा sk_buff *skb,
				      काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *) skb->data;
	काष्ठा ieee80211_tim_ie *tim_ie;
	u8 *tim;
	u8 tim_len;
	bool cam;

	/* If this is not a beacon, or अगर mac80211 has no घातersaving
	 * configured, or अगर the device is alपढ़ोy in घातersaving mode
	 * we can निकास now. */
	अगर (likely(!ieee80211_is_beacon(hdr->frame_control) ||
		   !(rt2x00dev->hw->conf.flags & IEEE80211_CONF_PS)))
		वापस;

	/* min. beacon length + FCS_LEN */
	अगर (skb->len <= 40 + FCS_LEN)
		वापस;

	/* and only beacons from the associated BSSID, please */
	अगर (!(rxdesc->dev_flags & RXDONE_MY_BSS) ||
	    !rt2x00dev->aid)
		वापस;

	rt2x00dev->last_beacon = jअगरfies;

	tim = rt2x00lib_find_ie(skb->data, skb->len - FCS_LEN, WLAN_EID_TIM);
	अगर (!tim)
		वापस;

	अगर (tim[1] < माप(*tim_ie))
		वापस;

	tim_len = tim[1];
	tim_ie = (काष्ठा ieee80211_tim_ie *) &tim[2];

	/* Check whenever the PHY can be turned off again. */

	/* 1. What about buffered unicast traffic क्रम our AID? */
	cam = ieee80211_check_tim(tim_ie, tim_len, rt2x00dev->aid);

	/* 2. Maybe the AP wants to send multicast/broadcast data? */
	cam |= (tim_ie->biपंचांगap_ctrl & 0x01);

	अगर (!cam && !test_bit(CONFIG_POWERSAVING, &rt2x00dev->flags))
		queue_work(rt2x00dev->workqueue, &rt2x00dev->sleep_work);
पूर्ण

अटल पूर्णांक rt2x00lib_rxकरोne_पढ़ो_संकेत(काष्ठा rt2x00_dev *rt2x00dev,
					काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा rt2x00_rate *rate;
	अचिन्हित पूर्णांक i;
	पूर्णांक संकेत = rxdesc->संकेत;
	पूर्णांक type = (rxdesc->dev_flags & RXDONE_SIGNAL_MASK);

	चयन (rxdesc->rate_mode) अणु
	हाल RATE_MODE_CCK:
	हाल RATE_MODE_OFDM:
		/*
		 * For non-HT rates the MCS value needs to contain the
		 * actually used rate modulation (CCK or OFDM).
		 */
		अगर (rxdesc->dev_flags & RXDONE_SIGNAL_MCS)
			संकेत = RATE_MCS(rxdesc->rate_mode, संकेत);

		sband = &rt2x00dev->bands[rt2x00dev->curr_band];
		क्रम (i = 0; i < sband->n_bitrates; i++) अणु
			rate = rt2x00_get_rate(sband->bitrates[i].hw_value);
			अगर (((type == RXDONE_SIGNAL_PLCP) &&
			     (rate->plcp == संकेत)) ||
			    ((type == RXDONE_SIGNAL_BITRATE) &&
			      (rate->bitrate == संकेत)) ||
			    ((type == RXDONE_SIGNAL_MCS) &&
			      (rate->mcs == संकेत))) अणु
				वापस i;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल RATE_MODE_HT_MIX:
	हाल RATE_MODE_HT_GREENFIELD:
		अगर (संकेत >= 0 && संकेत <= 76)
			वापस संकेत;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rt2x00_warn(rt2x00dev, "Frame received with unrecognized signal, mode=0x%.4x, signal=0x%.4x, type=%d\n",
		    rxdesc->rate_mode, संकेत, type);
	वापस 0;
पूर्ण

व्योम rt2x00lib_rxकरोne(काष्ठा queue_entry *entry, gfp_t gfp)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा rxकरोne_entry_desc rxdesc;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_rx_status *rx_status;
	अचिन्हित पूर्णांक header_length;
	पूर्णांक rate_idx;

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) ||
	    !test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		जाओ submit_entry;

	अगर (test_bit(ENTRY_DATA_IO_FAILED, &entry->flags))
		जाओ submit_entry;

	/*
	 * Allocate a new sk_buffer. If no new buffer available, drop the
	 * received frame and reuse the existing buffer.
	 */
	skb = rt2x00queue_alloc_rxskb(entry, gfp);
	अगर (!skb)
		जाओ submit_entry;

	/*
	 * Unmap the skb.
	 */
	rt2x00queue_unmap_skb(entry);

	/*
	 * Extract the RXD details.
	 */
	स_रखो(&rxdesc, 0, माप(rxdesc));
	rt2x00dev->ops->lib->fill_rxकरोne(entry, &rxdesc);

	/*
	 * Check क्रम valid size in हाल we get corrupted descriptor from
	 * hardware.
	 */
	अगर (unlikely(rxdesc.size == 0 ||
		     rxdesc.size > entry->queue->data_size)) अणु
		rt2x00_err(rt2x00dev, "Wrong frame size %d max %d\n",
			   rxdesc.size, entry->queue->data_size);
		dev_kमुक्त_skb(entry->skb);
		जाओ renew_skb;
	पूर्ण

	/*
	 * The data behind the ieee80211 header must be
	 * aligned on a 4 byte boundary.
	 */
	header_length = ieee80211_get_hdrlen_from_skb(entry->skb);

	/*
	 * Hardware might have stripped the IV/EIV/ICV data,
	 * in that हाल it is possible that the data was
	 * provided separately (through hardware descriptor)
	 * in which हाल we should reinsert the data पूर्णांकo the frame.
	 */
	अगर ((rxdesc.dev_flags & RXDONE_CRYPTO_IV) &&
	    (rxdesc.flags & RX_FLAG_IV_STRIPPED))
		rt2x00crypto_rx_insert_iv(entry->skb, header_length,
					  &rxdesc);
	अन्यथा अगर (header_length &&
		 (rxdesc.size > header_length) &&
		 (rxdesc.dev_flags & RXDONE_L2PAD))
		rt2x00queue_हटाओ_l2pad(entry->skb, header_length);

	/* Trim buffer to correct size */
	skb_trim(entry->skb, rxdesc.size);

	/*
	 * Translate the संकेत to the correct bitrate index.
	 */
	rate_idx = rt2x00lib_rxकरोne_पढ़ो_संकेत(rt2x00dev, &rxdesc);
	अगर (rxdesc.rate_mode == RATE_MODE_HT_MIX ||
	    rxdesc.rate_mode == RATE_MODE_HT_GREENFIELD)
		rxdesc.encoding = RX_ENC_HT;

	/*
	 * Check अगर this is a beacon, and more frames have been
	 * buffered जबतक we were in घातersaving mode.
	 */
	rt2x00lib_rxकरोne_check_ps(rt2x00dev, entry->skb, &rxdesc);

	/*
	 * Check क्रम incoming BlockAcks to match to the BlockAckReqs
	 * we've send out.
	 */
	rt2x00lib_rxकरोne_check_ba(rt2x00dev, entry->skb, &rxdesc);

	/*
	 * Update extra components
	 */
	rt2x00link_update_stats(rt2x00dev, entry->skb, &rxdesc);
	rt2x00debug_update_crypto(rt2x00dev, &rxdesc);
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_RXDONE, entry);

	/*
	 * Initialize RX status inक्रमmation, and send frame
	 * to mac80211.
	 */
	rx_status = IEEE80211_SKB_RXCB(entry->skb);

	/* Ensure that all fields of rx_status are initialized
	 * properly. The skb->cb array was used क्रम driver
	 * specअगरic inक्रमmations, so rx_status might contain
	 * garbage.
	 */
	स_रखो(rx_status, 0, माप(*rx_status));

	rx_status->maस_समय = rxdesc.बारtamp;
	rx_status->band = rt2x00dev->curr_band;
	rx_status->freq = rt2x00dev->curr_freq;
	rx_status->rate_idx = rate_idx;
	rx_status->संकेत = rxdesc.rssi;
	rx_status->flag = rxdesc.flags;
	rx_status->enc_flags = rxdesc.enc_flags;
	rx_status->encoding = rxdesc.encoding;
	rx_status->bw = rxdesc.bw;
	rx_status->antenna = rt2x00dev->link.ant.active.rx;

	ieee80211_rx_ni(rt2x00dev->hw, entry->skb);

renew_skb:
	/*
	 * Replace the skb with the freshly allocated one.
	 */
	entry->skb = skb;

submit_entry:
	entry->flags = 0;
	rt2x00queue_index_inc(entry, Q_INDEX_DONE);
	अगर (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) &&
	    test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2x00dev->ops->lib->clear_entry(entry);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_rxकरोne);

/*
 * Driver initialization handlers.
 */
स्थिर काष्ठा rt2x00_rate rt2x00_supported_rates[12] = अणु
	अणु
		.flags = DEV_RATE_CCK,
		.bitrate = 10,
		.ratemask = BIT(0),
		.plcp = 0x00,
		.mcs = RATE_MCS(RATE_MODE_CCK, 0),
	पूर्ण,
	अणु
		.flags = DEV_RATE_CCK | DEV_RATE_SHORT_PREAMBLE,
		.bitrate = 20,
		.ratemask = BIT(1),
		.plcp = 0x01,
		.mcs = RATE_MCS(RATE_MODE_CCK, 1),
	पूर्ण,
	अणु
		.flags = DEV_RATE_CCK | DEV_RATE_SHORT_PREAMBLE,
		.bitrate = 55,
		.ratemask = BIT(2),
		.plcp = 0x02,
		.mcs = RATE_MCS(RATE_MODE_CCK, 2),
	पूर्ण,
	अणु
		.flags = DEV_RATE_CCK | DEV_RATE_SHORT_PREAMBLE,
		.bitrate = 110,
		.ratemask = BIT(3),
		.plcp = 0x03,
		.mcs = RATE_MCS(RATE_MODE_CCK, 3),
	पूर्ण,
	अणु
		.flags = DEV_RATE_OFDM,
		.bitrate = 60,
		.ratemask = BIT(4),
		.plcp = 0x0b,
		.mcs = RATE_MCS(RATE_MODE_OFDM, 0),
	पूर्ण,
	अणु
		.flags = DEV_RATE_OFDM,
		.bitrate = 90,
		.ratemask = BIT(5),
		.plcp = 0x0f,
		.mcs = RATE_MCS(RATE_MODE_OFDM, 1),
	पूर्ण,
	अणु
		.flags = DEV_RATE_OFDM,
		.bitrate = 120,
		.ratemask = BIT(6),
		.plcp = 0x0a,
		.mcs = RATE_MCS(RATE_MODE_OFDM, 2),
	पूर्ण,
	अणु
		.flags = DEV_RATE_OFDM,
		.bitrate = 180,
		.ratemask = BIT(7),
		.plcp = 0x0e,
		.mcs = RATE_MCS(RATE_MODE_OFDM, 3),
	पूर्ण,
	अणु
		.flags = DEV_RATE_OFDM,
		.bitrate = 240,
		.ratemask = BIT(8),
		.plcp = 0x09,
		.mcs = RATE_MCS(RATE_MODE_OFDM, 4),
	पूर्ण,
	अणु
		.flags = DEV_RATE_OFDM,
		.bitrate = 360,
		.ratemask = BIT(9),
		.plcp = 0x0d,
		.mcs = RATE_MCS(RATE_MODE_OFDM, 5),
	पूर्ण,
	अणु
		.flags = DEV_RATE_OFDM,
		.bitrate = 480,
		.ratemask = BIT(10),
		.plcp = 0x08,
		.mcs = RATE_MCS(RATE_MODE_OFDM, 6),
	पूर्ण,
	अणु
		.flags = DEV_RATE_OFDM,
		.bitrate = 540,
		.ratemask = BIT(11),
		.plcp = 0x0c,
		.mcs = RATE_MCS(RATE_MODE_OFDM, 7),
	पूर्ण,
पूर्ण;

अटल व्योम rt2x00lib_channel(काष्ठा ieee80211_channel *entry,
			      स्थिर पूर्णांक channel, स्थिर पूर्णांक tx_घातer,
			      स्थिर पूर्णांक value)
अणु
	/* XXX: this assumption about the band is wrong क्रम 802.11j */
	entry->band = channel <= 14 ? NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
	entry->center_freq = ieee80211_channel_to_frequency(channel,
							    entry->band);
	entry->hw_value = value;
	entry->max_घातer = tx_घातer;
	entry->max_antenna_gain = 0xff;
पूर्ण

अटल व्योम rt2x00lib_rate(काष्ठा ieee80211_rate *entry,
			   स्थिर u16 index, स्थिर काष्ठा rt2x00_rate *rate)
अणु
	entry->flags = 0;
	entry->bitrate = rate->bitrate;
	entry->hw_value = index;
	entry->hw_value_लघु = index;

	अगर (rate->flags & DEV_RATE_SHORT_PREAMBLE)
		entry->flags |= IEEE80211_RATE_SHORT_PREAMBLE;
पूर्ण

व्योम rt2x00lib_set_mac_address(काष्ठा rt2x00_dev *rt2x00dev, u8 *eeprom_mac_addr)
अणु
	of_get_mac_address(rt2x00dev->dev->of_node, eeprom_mac_addr);

	अगर (!is_valid_ether_addr(eeprom_mac_addr)) अणु
		eth_अक्रमom_addr(eeprom_mac_addr);
		rt2x00_eeprom_dbg(rt2x00dev, "MAC: %pM\n", eeprom_mac_addr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_set_mac_address);

अटल पूर्णांक rt2x00lib_probe_hw_modes(काष्ठा rt2x00_dev *rt2x00dev,
				    काष्ठा hw_mode_spec *spec)
अणु
	काष्ठा ieee80211_hw *hw = rt2x00dev->hw;
	काष्ठा ieee80211_channel *channels;
	काष्ठा ieee80211_rate *rates;
	अचिन्हित पूर्णांक num_rates;
	अचिन्हित पूर्णांक i;

	num_rates = 0;
	अगर (spec->supported_rates & SUPPORT_RATE_CCK)
		num_rates += 4;
	अगर (spec->supported_rates & SUPPORT_RATE_OFDM)
		num_rates += 8;

	channels = kसुस्मृति(spec->num_channels, माप(*channels), GFP_KERNEL);
	अगर (!channels)
		वापस -ENOMEM;

	rates = kसुस्मृति(num_rates, माप(*rates), GFP_KERNEL);
	अगर (!rates)
		जाओ निकास_मुक्त_channels;

	/*
	 * Initialize Rate list.
	 */
	क्रम (i = 0; i < num_rates; i++)
		rt2x00lib_rate(&rates[i], i, rt2x00_get_rate(i));

	/*
	 * Initialize Channel list.
	 */
	क्रम (i = 0; i < spec->num_channels; i++) अणु
		rt2x00lib_channel(&channels[i],
				  spec->channels[i].channel,
				  spec->channels_info[i].max_घातer, i);
	पूर्ण

	/*
	 * Intitialize 802.11b, 802.11g
	 * Rates: CCK, OFDM.
	 * Channels: 2.4 GHz
	 */
	अगर (spec->supported_bands & SUPPORT_BAND_2GHZ) अणु
		rt2x00dev->bands[NL80211_BAND_2GHZ].n_channels = 14;
		rt2x00dev->bands[NL80211_BAND_2GHZ].n_bitrates = num_rates;
		rt2x00dev->bands[NL80211_BAND_2GHZ].channels = channels;
		rt2x00dev->bands[NL80211_BAND_2GHZ].bitrates = rates;
		hw->wiphy->bands[NL80211_BAND_2GHZ] =
		    &rt2x00dev->bands[NL80211_BAND_2GHZ];
		स_नकल(&rt2x00dev->bands[NL80211_BAND_2GHZ].ht_cap,
		       &spec->ht, माप(spec->ht));
	पूर्ण

	/*
	 * Intitialize 802.11a
	 * Rates: OFDM.
	 * Channels: OFDM, UNII, HiperLAN2.
	 */
	अगर (spec->supported_bands & SUPPORT_BAND_5GHZ) अणु
		rt2x00dev->bands[NL80211_BAND_5GHZ].n_channels =
		    spec->num_channels - 14;
		rt2x00dev->bands[NL80211_BAND_5GHZ].n_bitrates =
		    num_rates - 4;
		rt2x00dev->bands[NL80211_BAND_5GHZ].channels = &channels[14];
		rt2x00dev->bands[NL80211_BAND_5GHZ].bitrates = &rates[4];
		hw->wiphy->bands[NL80211_BAND_5GHZ] =
		    &rt2x00dev->bands[NL80211_BAND_5GHZ];
		स_नकल(&rt2x00dev->bands[NL80211_BAND_5GHZ].ht_cap,
		       &spec->ht, माप(spec->ht));
	पूर्ण

	वापस 0;

 निकास_मुक्त_channels:
	kमुक्त(channels);
	rt2x00_err(rt2x00dev, "Allocation ieee80211 modes failed\n");
	वापस -ENOMEM;
पूर्ण

अटल व्योम rt2x00lib_हटाओ_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (test_bit(DEVICE_STATE_REGISTERED_HW, &rt2x00dev->flags))
		ieee80211_unरेजिस्टर_hw(rt2x00dev->hw);

	अगर (likely(rt2x00dev->hw->wiphy->bands[NL80211_BAND_2GHZ])) अणु
		kमुक्त(rt2x00dev->hw->wiphy->bands[NL80211_BAND_2GHZ]->channels);
		kमुक्त(rt2x00dev->hw->wiphy->bands[NL80211_BAND_2GHZ]->bitrates);
		rt2x00dev->hw->wiphy->bands[NL80211_BAND_2GHZ] = शून्य;
		rt2x00dev->hw->wiphy->bands[NL80211_BAND_5GHZ] = शून्य;
	पूर्ण

	kमुक्त(rt2x00dev->spec.channels_info);
पूर्ण

अटल पूर्णांक rt2x00lib_probe_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा hw_mode_spec *spec = &rt2x00dev->spec;
	पूर्णांक status;

	अगर (test_bit(DEVICE_STATE_REGISTERED_HW, &rt2x00dev->flags))
		वापस 0;

	/*
	 * Initialize HW modes.
	 */
	status = rt2x00lib_probe_hw_modes(rt2x00dev, spec);
	अगर (status)
		वापस status;

	/*
	 * Initialize HW fields.
	 */
	rt2x00dev->hw->queues = rt2x00dev->ops->tx_queues;

	/*
	 * Initialize extra TX headroom required.
	 */
	rt2x00dev->hw->extra_tx_headroom =
		max_t(अचिन्हित पूर्णांक, IEEE80211_TX_STATUS_HEADROOM,
		      rt2x00dev->extra_tx_headroom);

	/*
	 * Take TX headroom required क्रम alignment पूर्णांकo account.
	 */
	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_L2PAD))
		rt2x00dev->hw->extra_tx_headroom += RT2X00_L2PAD_SIZE;
	अन्यथा अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DMA))
		rt2x00dev->hw->extra_tx_headroom += RT2X00_ALIGN_SIZE;

	/*
	 * Tell mac80211 about the size of our निजी STA काष्ठाure.
	 */
	rt2x00dev->hw->sta_data_size = माप(काष्ठा rt2x00_sta);

	/*
	 * Allocate tx status FIFO क्रम driver use.
	 */
	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_TXSTATUS_FIFO)) अणु
		/*
		 * Allocate the txstatus fअगरo. In the worst हाल the tx
		 * status fअगरo has to hold the tx status of all entries
		 * in all tx queues. Hence, calculate the kfअगरo size as
		 * tx_queues * entry_num and round up to the nearest
		 * घातer of 2.
		 */
		पूर्णांक kfअगरo_size =
			roundup_घात_of_two(rt2x00dev->ops->tx_queues *
					   rt2x00dev->tx->limit *
					   माप(u32));

		status = kfअगरo_alloc(&rt2x00dev->txstatus_fअगरo, kfअगरo_size,
				     GFP_KERNEL);
		अगर (status)
			वापस status;
	पूर्ण

	/*
	 * Initialize tasklets अगर used by the driver. Tasklets are
	 * disabled until the पूर्णांकerrupts are turned on. The driver
	 * has to handle that.
	 */
#घोषणा RT2X00_TASKLET_INIT(taskletname) \
	अगर (rt2x00dev->ops->lib->taskletname) अणु \
		tasklet_setup(&rt2x00dev->taskletname, \
			     rt2x00dev->ops->lib->taskletname); \
	पूर्ण

	RT2X00_TASKLET_INIT(txstatus_tasklet);
	RT2X00_TASKLET_INIT(pretbtt_tasklet);
	RT2X00_TASKLET_INIT(tbtt_tasklet);
	RT2X00_TASKLET_INIT(rxकरोne_tasklet);
	RT2X00_TASKLET_INIT(स्वतःwake_tasklet);

#अघोषित RT2X00_TASKLET_INIT

	/*
	 * Register HW.
	 */
	status = ieee80211_रेजिस्टर_hw(rt2x00dev->hw);
	अगर (status)
		वापस status;

	set_bit(DEVICE_STATE_REGISTERED_HW, &rt2x00dev->flags);

	वापस 0;
पूर्ण

/*
 * Initialization/uninitialization handlers.
 */
अटल व्योम rt2x00lib_uninitialize(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (!test_and_clear_bit(DEVICE_STATE_INITIALIZED, &rt2x00dev->flags))
		वापस;

	/*
	 * Stop rfसमाप्त polling.
	 */
	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DELAYED_RFKILL))
		rt2x00rfसमाप्त_unरेजिस्टर(rt2x00dev);

	/*
	 * Allow the HW to uninitialize.
	 */
	rt2x00dev->ops->lib->uninitialize(rt2x00dev);

	/*
	 * Free allocated queue entries.
	 */
	rt2x00queue_uninitialize(rt2x00dev);
पूर्ण

अटल पूर्णांक rt2x00lib_initialize(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक status;

	अगर (test_bit(DEVICE_STATE_INITIALIZED, &rt2x00dev->flags))
		वापस 0;

	/*
	 * Allocate all queue entries.
	 */
	status = rt2x00queue_initialize(rt2x00dev);
	अगर (status)
		वापस status;

	/*
	 * Initialize the device.
	 */
	status = rt2x00dev->ops->lib->initialize(rt2x00dev);
	अगर (status) अणु
		rt2x00queue_uninitialize(rt2x00dev);
		वापस status;
	पूर्ण

	set_bit(DEVICE_STATE_INITIALIZED, &rt2x00dev->flags);

	/*
	 * Start rfसमाप्त polling.
	 */
	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DELAYED_RFKILL))
		rt2x00rfसमाप्त_रेजिस्टर(rt2x00dev);

	वापस 0;
पूर्ण

पूर्णांक rt2x00lib_start(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval = 0;

	/*
	 * If this is the first पूर्णांकerface which is added,
	 * we should load the firmware now.
	 */
	retval = rt2x00lib_load_firmware(rt2x00dev);
	अगर (retval)
		जाओ out;

	/*
	 * Initialize the device.
	 */
	retval = rt2x00lib_initialize(rt2x00dev);
	अगर (retval)
		जाओ out;

	rt2x00dev->पूर्णांकf_ap_count = 0;
	rt2x00dev->पूर्णांकf_sta_count = 0;
	rt2x00dev->पूर्णांकf_associated = 0;

	/* Enable the radio */
	retval = rt2x00lib_enable_radio(rt2x00dev);
	अगर (retval)
		जाओ out;

	set_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags);

out:
	वापस retval;
पूर्ण

व्योम rt2x00lib_stop(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (!test_and_clear_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags))
		वापस;

	/*
	 * Perhaps we can add something smarter here,
	 * but क्रम now just disabling the radio should करो.
	 */
	rt2x00lib_disable_radio(rt2x00dev);

	rt2x00dev->पूर्णांकf_ap_count = 0;
	rt2x00dev->पूर्णांकf_sta_count = 0;
	rt2x00dev->पूर्णांकf_associated = 0;
पूर्ण

अटल अंतरभूत व्योम rt2x00lib_set_अगर_combinations(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा ieee80211_अगरace_limit *अगर_limit;
	काष्ठा ieee80211_अगरace_combination *अगर_combination;

	अगर (rt2x00dev->ops->max_ap_पूर्णांकf < 2)
		वापस;

	/*
	 * Build up AP पूर्णांकerface limits काष्ठाure.
	 */
	अगर_limit = &rt2x00dev->अगर_limits_ap;
	अगर_limit->max = rt2x00dev->ops->max_ap_पूर्णांकf;
	अगर_limit->types = BIT(NL80211_IFTYPE_AP);
#अगर_घोषित CONFIG_MAC80211_MESH
	अगर_limit->types |= BIT(NL80211_IFTYPE_MESH_POINT);
#पूर्ण_अगर

	/*
	 * Build up AP पूर्णांकerface combinations काष्ठाure.
	 */
	अगर_combination = &rt2x00dev->अगर_combinations[IF_COMB_AP];
	अगर_combination->limits = अगर_limit;
	अगर_combination->n_limits = 1;
	अगर_combination->max_पूर्णांकerfaces = अगर_limit->max;
	अगर_combination->num_dअगरferent_channels = 1;

	/*
	 * Finally, specअगरy the possible combinations to mac80211.
	 */
	rt2x00dev->hw->wiphy->अगरace_combinations = rt2x00dev->अगर_combinations;
	rt2x00dev->hw->wiphy->n_अगरace_combinations = 1;
पूर्ण

अटल अचिन्हित पूर्णांक rt2x00dev_extra_tx_headroom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (WARN_ON(!rt2x00dev->tx))
		वापस 0;

	अगर (rt2x00_is_usb(rt2x00dev))
		वापस rt2x00dev->tx[0].winfo_size + rt2x00dev->tx[0].desc_size;

	वापस rt2x00dev->tx[0].winfo_size;
पूर्ण

/*
 * driver allocation handlers.
 */
पूर्णांक rt2x00lib_probe_dev(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval = -ENOMEM;

	/*
	 * Set possible पूर्णांकerface combinations.
	 */
	rt2x00lib_set_अगर_combinations(rt2x00dev);

	/*
	 * Allocate the driver data memory, अगर necessary.
	 */
	अगर (rt2x00dev->ops->drv_data_size > 0) अणु
		rt2x00dev->drv_data = kzalloc(rt2x00dev->ops->drv_data_size,
			                      GFP_KERNEL);
		अगर (!rt2x00dev->drv_data) अणु
			retval = -ENOMEM;
			जाओ निकास;
		पूर्ण
	पूर्ण

	spin_lock_init(&rt2x00dev->irqmask_lock);
	mutex_init(&rt2x00dev->csr_mutex);
	mutex_init(&rt2x00dev->conf_mutex);
	INIT_LIST_HEAD(&rt2x00dev->bar_list);
	spin_lock_init(&rt2x00dev->bar_list_lock);
	hrसमयr_init(&rt2x00dev->txstatus_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);

	set_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags);

	/*
	 * Make room क्रम rt2x00_पूर्णांकf inside the per-पूर्णांकerface
	 * काष्ठाure ieee80211_vअगर.
	 */
	rt2x00dev->hw->vअगर_data_size = माप(काष्ठा rt2x00_पूर्णांकf);

	/*
	 * rt2x00 devices can only use the last n bits of the MAC address
	 * क्रम भव पूर्णांकerfaces.
	 */
	rt2x00dev->hw->wiphy->addr_mask[ETH_ALEN - 1] =
		(rt2x00dev->ops->max_ap_पूर्णांकf - 1);

	/*
	 * Initialize work.
	 */
	rt2x00dev->workqueue =
	    alloc_ordered_workqueue("%s", 0, wiphy_name(rt2x00dev->hw->wiphy));
	अगर (!rt2x00dev->workqueue) अणु
		retval = -ENOMEM;
		जाओ निकास;
	पूर्ण

	INIT_WORK(&rt2x00dev->पूर्णांकf_work, rt2x00lib_पूर्णांकf_scheduled);
	INIT_DELAYED_WORK(&rt2x00dev->स्वतःwakeup_work, rt2x00lib_स्वतःwakeup);
	INIT_WORK(&rt2x00dev->sleep_work, rt2x00lib_sleep);

	/*
	 * Let the driver probe the device to detect the capabilities.
	 */
	retval = rt2x00dev->ops->lib->probe_hw(rt2x00dev);
	अगर (retval) अणु
		rt2x00_err(rt2x00dev, "Failed to allocate device\n");
		जाओ निकास;
	पूर्ण

	/*
	 * Allocate queue array.
	 */
	retval = rt2x00queue_allocate(rt2x00dev);
	अगर (retval)
		जाओ निकास;

	/* Cache TX headroom value */
	rt2x00dev->extra_tx_headroom = rt2x00dev_extra_tx_headroom(rt2x00dev);

	/*
	 * Determine which operating modes are supported, all modes
	 * which require beaconing, depend on the availability of
	 * beacon entries.
	 */
	rt2x00dev->hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION);
	अगर (rt2x00dev->bcn->limit > 0)
		rt2x00dev->hw->wiphy->पूर्णांकerface_modes |=
		    BIT(NL80211_IFTYPE_ADHOC) |
#अगर_घोषित CONFIG_MAC80211_MESH
		    BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
		    BIT(NL80211_IFTYPE_AP);

	rt2x00dev->hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	wiphy_ext_feature_set(rt2x00dev->hw->wiphy,
			      NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	/*
	 * Initialize ieee80211 काष्ठाure.
	 */
	retval = rt2x00lib_probe_hw(rt2x00dev);
	अगर (retval) अणु
		rt2x00_err(rt2x00dev, "Failed to initialize hw\n");
		जाओ निकास;
	पूर्ण

	/*
	 * Register extra components.
	 */
	rt2x00link_रेजिस्टर(rt2x00dev);
	rt2x00leds_रेजिस्टर(rt2x00dev);
	rt2x00debug_रेजिस्टर(rt2x00dev);

	/*
	 * Start rfसमाप्त polling.
	 */
	अगर (!rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DELAYED_RFKILL))
		rt2x00rfसमाप्त_रेजिस्टर(rt2x00dev);

	वापस 0;

निकास:
	rt2x00lib_हटाओ_dev(rt2x00dev);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_probe_dev);

व्योम rt2x00lib_हटाओ_dev(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	clear_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags);

	/*
	 * Stop rfसमाप्त polling.
	 */
	अगर (!rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DELAYED_RFKILL))
		rt2x00rfसमाप्त_unरेजिस्टर(rt2x00dev);

	/*
	 * Disable radio.
	 */
	rt2x00lib_disable_radio(rt2x00dev);

	/*
	 * Stop all work.
	 */
	cancel_work_sync(&rt2x00dev->पूर्णांकf_work);
	cancel_delayed_work_sync(&rt2x00dev->स्वतःwakeup_work);
	cancel_work_sync(&rt2x00dev->sleep_work);

	hrसमयr_cancel(&rt2x00dev->txstatus_समयr);

	/*
	 * Kill the tx status tasklet.
	 */
	tasklet_समाप्त(&rt2x00dev->txstatus_tasklet);
	tasklet_समाप्त(&rt2x00dev->pretbtt_tasklet);
	tasklet_समाप्त(&rt2x00dev->tbtt_tasklet);
	tasklet_समाप्त(&rt2x00dev->rxकरोne_tasklet);
	tasklet_समाप्त(&rt2x00dev->स्वतःwake_tasklet);

	/*
	 * Uninitialize device.
	 */
	rt2x00lib_uninitialize(rt2x00dev);

	अगर (rt2x00dev->workqueue)
		destroy_workqueue(rt2x00dev->workqueue);

	/*
	 * Free the tx status fअगरo.
	 */
	kfअगरo_मुक्त(&rt2x00dev->txstatus_fअगरo);

	/*
	 * Free extra components
	 */
	rt2x00debug_deरेजिस्टर(rt2x00dev);
	rt2x00leds_unरेजिस्टर(rt2x00dev);

	/*
	 * Free ieee80211_hw memory.
	 */
	rt2x00lib_हटाओ_hw(rt2x00dev);

	/*
	 * Free firmware image.
	 */
	rt2x00lib_मुक्त_firmware(rt2x00dev);

	/*
	 * Free queue काष्ठाures.
	 */
	rt2x00queue_मुक्त(rt2x00dev);

	/*
	 * Free the driver data.
	 */
	kमुक्त(rt2x00dev->drv_data);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_हटाओ_dev);

/*
 * Device state handlers
 */
पूर्णांक rt2x00lib_suspend(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2x00_dbg(rt2x00dev, "Going to sleep\n");

	/*
	 * Prevent mac80211 from accessing driver जबतक suspended.
	 */
	अगर (!test_and_clear_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस 0;

	/*
	 * Cleanup as much as possible.
	 */
	rt2x00lib_uninitialize(rt2x00dev);

	/*
	 * Suspend/disable extra components.
	 */
	rt2x00leds_suspend(rt2x00dev);
	rt2x00debug_deरेजिस्टर(rt2x00dev);

	/*
	 * Set device mode to sleep क्रम घातer management,
	 * on some hardware this call seems to consistently fail.
	 * From the specअगरications it is hard to tell why it fails,
	 * and अगर this is a "bad thing".
	 * Overall it is safe to just ignore the failure and
	 * जारी suspending. The only करोwnside is that the
	 * device will not be in optimal घातer save mode, but with
	 * the radio and the other components alपढ़ोy disabled the
	 * device is as good as disabled.
	 */
	अगर (rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_SLEEP))
		rt2x00_warn(rt2x00dev, "Device failed to enter sleep state, continue suspending\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_suspend);

पूर्णांक rt2x00lib_resume(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2x00_dbg(rt2x00dev, "Waking up\n");

	/*
	 * Restore/enable extra components.
	 */
	rt2x00debug_रेजिस्टर(rt2x00dev);
	rt2x00leds_resume(rt2x00dev);

	/*
	 * We are पढ़ोy again to receive requests from mac80211.
	 */
	set_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00lib_resume);

/*
 * rt2x00lib module inक्रमmation.
 */
MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("rt2x00 library");
MODULE_LICENSE("GPL");
