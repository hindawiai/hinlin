<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Datapath implementation.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <net/mac80211.h>
#समावेश <linux/etherdevice.h>

#समावेश "data_tx.h"
#समावेश "wfx.h"
#समावेश "bh.h"
#समावेश "sta.h"
#समावेश "queue.h"
#समावेश "debug.h"
#समावेश "traces.h"
#समावेश "hif_tx_mib.h"

अटल पूर्णांक wfx_get_hw_rate(काष्ठा wfx_dev *wdev,
			   स्थिर काष्ठा ieee80211_tx_rate *rate)
अणु
	काष्ठा ieee80211_supported_band *band;

	अगर (rate->idx < 0)
		वापस -1;
	अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		अगर (rate->idx > 7) अणु
			WARN(1, "wrong rate->idx value: %d", rate->idx);
			वापस -1;
		पूर्ण
		वापस rate->idx + 14;
	पूर्ण
	// WFx only support 2GHz, अन्यथा band inक्रमmation should be retrieved
	// from ieee80211_tx_info
	band = wdev->hw->wiphy->bands[NL80211_BAND_2GHZ];
	अगर (rate->idx >= band->n_bitrates) अणु
		WARN(1, "wrong rate->idx value: %d", rate->idx);
		वापस -1;
	पूर्ण
	वापस band->bitrates[rate->idx].hw_value;
पूर्ण

/* TX policy cache implementation */

अटल व्योम wfx_tx_policy_build(काष्ठा wfx_vअगर *wvअगर, काष्ठा tx_policy *policy,
				काष्ठा ieee80211_tx_rate *rates)
अणु
	काष्ठा wfx_dev *wdev = wvअगर->wdev;
	पूर्णांक i, rateid;
	u8 count;

	WARN(rates[0].idx < 0, "invalid rate policy");
	स_रखो(policy, 0, माप(*policy));
	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; ++i) अणु
		अगर (rates[i].idx < 0)
			अवरोध;
		WARN_ON(rates[i].count > 15);
		rateid = wfx_get_hw_rate(wdev, &rates[i]);
		// Pack two values in each byte of policy->rates
		count = rates[i].count;
		अगर (rateid % 2)
			count <<= 4;
		policy->rates[rateid / 2] |= count;
	पूर्ण
पूर्ण

अटल bool tx_policy_is_equal(स्थिर काष्ठा tx_policy *a,
			       स्थिर काष्ठा tx_policy *b)
अणु
	वापस !स_भेद(a->rates, b->rates, माप(a->rates));
पूर्ण

अटल पूर्णांक wfx_tx_policy_find(काष्ठा tx_policy_cache *cache,
			      काष्ठा tx_policy *wanted)
अणु
	काष्ठा tx_policy *it;

	list_क्रम_each_entry(it, &cache->used, link)
		अगर (tx_policy_is_equal(wanted, it))
			वापस it - cache->cache;
	list_क्रम_each_entry(it, &cache->मुक्त, link)
		अगर (tx_policy_is_equal(wanted, it))
			वापस it - cache->cache;
	वापस -1;
पूर्ण

अटल व्योम wfx_tx_policy_use(काष्ठा tx_policy_cache *cache,
			      काष्ठा tx_policy *entry)
अणु
	++entry->usage_count;
	list_move(&entry->link, &cache->used);
पूर्ण

अटल पूर्णांक wfx_tx_policy_release(काष्ठा tx_policy_cache *cache,
				 काष्ठा tx_policy *entry)
अणु
	पूर्णांक ret = --entry->usage_count;

	अगर (!ret)
		list_move(&entry->link, &cache->मुक्त);
	वापस ret;
पूर्ण

अटल पूर्णांक wfx_tx_policy_get(काष्ठा wfx_vअगर *wvअगर,
			     काष्ठा ieee80211_tx_rate *rates, bool *renew)
अणु
	पूर्णांक idx;
	काष्ठा tx_policy_cache *cache = &wvअगर->tx_policy_cache;
	काष्ठा tx_policy wanted;

	wfx_tx_policy_build(wvअगर, &wanted, rates);

	spin_lock_bh(&cache->lock);
	अगर (list_empty(&cache->मुक्त)) अणु
		WARN(1, "unable to get a valid Tx policy");
		spin_unlock_bh(&cache->lock);
		वापस HIF_TX_RETRY_POLICY_INVALID;
	पूर्ण
	idx = wfx_tx_policy_find(cache, &wanted);
	अगर (idx >= 0) अणु
		*renew = false;
	पूर्ण अन्यथा अणु
		काष्ठा tx_policy *entry;
		*renew = true;
		/* If policy is not found create a new one
		 * using the oldest entry in "free" list
		 */
		entry = list_entry(cache->मुक्त.prev, काष्ठा tx_policy, link);
		स_नकल(entry->rates, wanted.rates, माप(entry->rates));
		entry->uploaded = false;
		entry->usage_count = 0;
		idx = entry - cache->cache;
	पूर्ण
	wfx_tx_policy_use(cache, &cache->cache[idx]);
	अगर (list_empty(&cache->मुक्त))
		ieee80211_stop_queues(wvअगर->wdev->hw);
	spin_unlock_bh(&cache->lock);
	वापस idx;
पूर्ण

अटल व्योम wfx_tx_policy_put(काष्ठा wfx_vअगर *wvअगर, पूर्णांक idx)
अणु
	पूर्णांक usage, locked;
	काष्ठा tx_policy_cache *cache = &wvअगर->tx_policy_cache;

	अगर (idx == HIF_TX_RETRY_POLICY_INVALID)
		वापस;
	spin_lock_bh(&cache->lock);
	locked = list_empty(&cache->मुक्त);
	usage = wfx_tx_policy_release(cache, &cache->cache[idx]);
	अगर (locked && !usage)
		ieee80211_wake_queues(wvअगर->wdev->hw);
	spin_unlock_bh(&cache->lock);
पूर्ण

अटल पूर्णांक wfx_tx_policy_upload(काष्ठा wfx_vअगर *wvअगर)
अणु
	काष्ठा tx_policy *policies = wvअगर->tx_policy_cache.cache;
	u8 पंचांगp_rates[12];
	पूर्णांक i, is_used;

	करो अणु
		spin_lock_bh(&wvअगर->tx_policy_cache.lock);
		क्रम (i = 0; i < ARRAY_SIZE(wvअगर->tx_policy_cache.cache); ++i) अणु
			is_used = memzcmp(policies[i].rates,
					  माप(policies[i].rates));
			अगर (!policies[i].uploaded && is_used)
				अवरोध;
		पूर्ण
		अगर (i < ARRAY_SIZE(wvअगर->tx_policy_cache.cache)) अणु
			policies[i].uploaded = true;
			स_नकल(पंचांगp_rates, policies[i].rates, माप(पंचांगp_rates));
			spin_unlock_bh(&wvअगर->tx_policy_cache.lock);
			hअगर_set_tx_rate_retry_policy(wvअगर, i, पंचांगp_rates);
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&wvअगर->tx_policy_cache.lock);
		पूर्ण
	पूर्ण जबतक (i < ARRAY_SIZE(wvअगर->tx_policy_cache.cache));
	वापस 0;
पूर्ण

व्योम wfx_tx_policy_upload_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wfx_vअगर *wvअगर =
		container_of(work, काष्ठा wfx_vअगर, tx_policy_upload_work);

	wfx_tx_policy_upload(wvअगर);
	wfx_tx_unlock(wvअगर->wdev);
पूर्ण

व्योम wfx_tx_policy_init(काष्ठा wfx_vअगर *wvअगर)
अणु
	काष्ठा tx_policy_cache *cache = &wvअगर->tx_policy_cache;
	पूर्णांक i;

	स_रखो(cache, 0, माप(*cache));

	spin_lock_init(&cache->lock);
	INIT_LIST_HEAD(&cache->used);
	INIT_LIST_HEAD(&cache->मुक्त);

	क्रम (i = 0; i < ARRAY_SIZE(cache->cache); ++i)
		list_add(&cache->cache[i].link, &cache->मुक्त);
पूर्ण

/* Tx implementation */

अटल bool ieee80211_is_action_back(काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)hdr;

	अगर (!ieee80211_is_action(mgmt->frame_control))
		वापस false;
	अगर (mgmt->u.action.category != WLAN_CATEGORY_BACK)
		वापस false;
	वापस true;
पूर्ण

अटल u8 wfx_tx_get_link_id(काष्ठा wfx_vअगर *wvअगर, काष्ठा ieee80211_sta *sta,
			     काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा wfx_sta_priv *sta_priv =
		sta ? (काष्ठा wfx_sta_priv *)&sta->drv_priv : शून्य;
	स्थिर u8 *da = ieee80211_get_DA(hdr);

	अगर (sta_priv && sta_priv->link_id)
		वापस sta_priv->link_id;
	अगर (wvअगर->vअगर->type != NL80211_IFTYPE_AP)
		वापस 0;
	अगर (is_multicast_ether_addr(da))
		वापस 0;
	वापस HIF_LINK_ID_NOT_ASSOCIATED;
पूर्ण

अटल व्योम wfx_tx_fixup_rates(काष्ठा ieee80211_tx_rate *rates)
अणु
	पूर्णांक i;
	bool finished;

	// Firmware is not able to mix rates with dअगरferent flags
	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
		अगर (rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
			rates[i].flags |= IEEE80211_TX_RC_SHORT_GI;
		अगर (!(rates[0].flags & IEEE80211_TX_RC_SHORT_GI))
			rates[i].flags &= ~IEEE80211_TX_RC_SHORT_GI;
		अगर (!(rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS))
			rates[i].flags &= ~IEEE80211_TX_RC_USE_RTS_CTS;
	पूर्ण

	// Sort rates and हटाओ duplicates
	करो अणु
		finished = true;
		क्रम (i = 0; i < IEEE80211_TX_MAX_RATES - 1; i++) अणु
			अगर (rates[i + 1].idx == rates[i].idx &&
			    rates[i].idx != -1) अणु
				rates[i].count += rates[i + 1].count;
				अगर (rates[i].count > 15)
					rates[i].count = 15;
				rates[i + 1].idx = -1;
				rates[i + 1].count = 0;

				finished = false;
			पूर्ण
			अगर (rates[i + 1].idx > rates[i].idx) अणु
				swap(rates[i + 1], rates[i]);
				finished = false;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (!finished);
	// Ensure that MCS0 or 1Mbps is present at the end of the retry list
	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
		अगर (rates[i].idx == 0)
			अवरोध;
		अगर (rates[i].idx == -1) अणु
			rates[i].idx = 0;
			rates[i].count = 8; // == hw->max_rate_tries
			rates[i].flags = rates[i - 1].flags &
					 IEEE80211_TX_RC_MCS;
			अवरोध;
		पूर्ण
	पूर्ण
	// All retries use दीर्घ GI
	क्रम (i = 1; i < IEEE80211_TX_MAX_RATES; i++)
		rates[i].flags &= ~IEEE80211_TX_RC_SHORT_GI;
पूर्ण

अटल u8 wfx_tx_get_rate_id(काष्ठा wfx_vअगर *wvअगर,
			     काष्ठा ieee80211_tx_info *tx_info)
अणु
	bool tx_policy_renew = false;
	u8 rate_id;

	rate_id = wfx_tx_policy_get(wvअगर,
				    tx_info->driver_rates, &tx_policy_renew);
	अगर (rate_id == HIF_TX_RETRY_POLICY_INVALID)
		dev_warn(wvअगर->wdev->dev, "unable to get a valid Tx policy");

	अगर (tx_policy_renew) अणु
		wfx_tx_lock(wvअगर->wdev);
		अगर (!schedule_work(&wvअगर->tx_policy_upload_work))
			wfx_tx_unlock(wvअगर->wdev);
	पूर्ण
	वापस rate_id;
पूर्ण

अटल पूर्णांक wfx_tx_get_frame_क्रमmat(काष्ठा ieee80211_tx_info *tx_info)
अणु
	अगर (!(tx_info->driver_rates[0].flags & IEEE80211_TX_RC_MCS))
		वापस HIF_FRAME_FORMAT_NON_HT;
	अन्यथा अगर (!(tx_info->driver_rates[0].flags & IEEE80211_TX_RC_GREEN_FIELD))
		वापस HIF_FRAME_FORMAT_MIXED_FORMAT_HT;
	अन्यथा
		वापस HIF_FRAME_FORMAT_GF_HT_11N;
पूर्ण

अटल पूर्णांक wfx_tx_get_icv_len(काष्ठा ieee80211_key_conf *hw_key)
अणु
	पूर्णांक mic_space;

	अगर (!hw_key)
		वापस 0;
	अगर (hw_key->cipher == WLAN_CIPHER_SUITE_AES_CMAC)
		वापस 0;
	mic_space = (hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) ? 8 : 0;
	वापस hw_key->icv_len + mic_space;
पूर्ण

अटल पूर्णांक wfx_tx_inner(काष्ठा wfx_vअगर *wvअगर, काष्ठा ieee80211_sta *sta,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा hअगर_msg *hअगर_msg;
	काष्ठा hअगर_req_tx *req;
	काष्ठा wfx_tx_priv *tx_priv;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_key_conf *hw_key = tx_info->control.hw_key;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	पूर्णांक queue_id = skb_get_queue_mapping(skb);
	माप_प्रकार offset = (माप_प्रकार)skb->data & 3;
	पूर्णांक wmsg_len = माप(काष्ठा hअगर_msg) +
			माप(काष्ठा hअगर_req_tx) + offset;

	WARN(queue_id >= IEEE80211_NUM_ACS, "unsupported queue_id");
	wfx_tx_fixup_rates(tx_info->driver_rates);

	// From now tx_info->control is unusable
	स_रखो(tx_info->rate_driver_data, 0, माप(काष्ठा wfx_tx_priv));
	// Fill tx_priv
	tx_priv = (काष्ठा wfx_tx_priv *)tx_info->rate_driver_data;
	tx_priv->icv_size = wfx_tx_get_icv_len(hw_key);

	// Fill hअगर_msg
	WARN(skb_headroom(skb) < wmsg_len, "not enough space in skb");
	WARN(offset & 1, "attempt to transmit an unaligned frame");
	skb_put(skb, tx_priv->icv_size);
	skb_push(skb, wmsg_len);
	स_रखो(skb->data, 0, wmsg_len);
	hअगर_msg = (काष्ठा hअगर_msg *)skb->data;
	hअगर_msg->len = cpu_to_le16(skb->len);
	hअगर_msg->id = HIF_REQ_ID_TX;
	hअगर_msg->पूर्णांकerface = wvअगर->id;
	अगर (skb->len > wvअगर->wdev->hw_caps.size_inp_ch_buf) अणु
		dev_warn(wvअगर->wdev->dev,
			 "requested frame size (%d) is larger than maximum supported (%d)\n",
			 skb->len, wvअगर->wdev->hw_caps.size_inp_ch_buf);
		skb_pull(skb, wmsg_len);
		वापस -EIO;
	पूर्ण

	// Fill tx request
	req = (काष्ठा hअगर_req_tx *)hअगर_msg->body;
	// packet_id just need to be unique on device. 32bits are more than
	// necessary क्रम that task, so we tae advantage of it to add some extra
	// data क्रम debug.
	req->packet_id = atomic_add_वापस(1, &wvअगर->wdev->packet_id) & 0xFFFF;
	req->packet_id |= IEEE80211_SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl)) << 16;
	req->packet_id |= queue_id << 28;

	req->fc_offset = offset;
	अगर (tx_info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM)
		req->after_dtim = 1;
	req->peer_sta_id = wfx_tx_get_link_id(wvअगर, sta, hdr);
	// Queue index are inverted between firmware and Linux
	req->queue_id = 3 - queue_id;
	req->retry_policy_index = wfx_tx_get_rate_id(wvअगर, tx_info);
	req->frame_क्रमmat = wfx_tx_get_frame_क्रमmat(tx_info);
	अगर (tx_info->driver_rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
		req->लघु_gi = 1;

	// Auxiliary operations
	wfx_tx_queues_put(wvअगर, skb);
	अगर (tx_info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM)
		schedule_work(&wvअगर->update_tim_work);
	wfx_bh_request_tx(wvअगर->wdev);
	वापस 0;
पूर्ण

व्योम wfx_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_tx_control *control,
	    काष्ठा sk_buff *skb)
अणु
	काष्ठा wfx_dev *wdev = hw->priv;
	काष्ठा wfx_vअगर *wvअगर;
	काष्ठा ieee80211_sta *sta = control ? control->sta : शून्य;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	माप_प्रकार driver_data_room = माप_field(काष्ठा ieee80211_tx_info,
					       rate_driver_data);

	compileसमय_निश्चित(माप(काष्ठा wfx_tx_priv) <= driver_data_room,
			   "struct tx_priv is too large");
	WARN(skb->next || skb->prev, "skb is already member of a list");
	// control.vअगर can be शून्य क्रम injected frames
	अगर (tx_info->control.vअगर)
		wvअगर = (काष्ठा wfx_vअगर *)tx_info->control.vअगर->drv_priv;
	अन्यथा
		wvअगर = wvअगर_iterate(wdev, शून्य);
	अगर (WARN_ON(!wvअगर))
		जाओ drop;
	// Because of TX_AMPDU_SETUP_IN_HW, mac80211 करोes not try to send any
	// BlockAck session management frame. The check below exist just in हाल.
	अगर (ieee80211_is_action_back(hdr)) अणु
		dev_info(wdev->dev, "drop BA action\n");
		जाओ drop;
	पूर्ण
	अगर (wfx_tx_inner(wvअगर, sta, skb))
		जाओ drop;

	वापस;

drop:
	ieee80211_tx_status_irqsafe(wdev->hw, skb);
पूर्ण

अटल व्योम wfx_skb_dtor(काष्ठा wfx_vअगर *wvअगर, काष्ठा sk_buff *skb)
अणु
	काष्ठा hअगर_msg *hअगर = (काष्ठा hअगर_msg *)skb->data;
	काष्ठा hअगर_req_tx *req = (काष्ठा hअगर_req_tx *)hअगर->body;
	अचिन्हित पूर्णांक offset = माप(काष्ठा hअगर_msg) +
			      माप(काष्ठा hअगर_req_tx) +
			      req->fc_offset;

	अगर (!wvअगर) अणु
		pr_warn("%s: vif associated with the skb does not exist anymore\n", __func__);
		वापस;
	पूर्ण
	wfx_tx_policy_put(wvअगर, req->retry_policy_index);
	skb_pull(skb, offset);
	ieee80211_tx_status_irqsafe(wvअगर->wdev->hw, skb);
पूर्ण

अटल व्योम wfx_tx_fill_rates(काष्ठा wfx_dev *wdev,
			      काष्ठा ieee80211_tx_info *tx_info,
			      स्थिर काष्ठा hअगर_cnf_tx *arg)
अणु
	काष्ठा ieee80211_tx_rate *rate;
	पूर्णांक tx_count;
	पूर्णांक i;

	tx_count = arg->ack_failures;
	अगर (!arg->status || arg->ack_failures)
		tx_count += 1; // Also report success
	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
		rate = &tx_info->status.rates[i];
		अगर (rate->idx < 0)
			अवरोध;
		अगर (tx_count < rate->count &&
		    arg->status == HIF_STATUS_TX_FAIL_RETRIES &&
		    arg->ack_failures)
			dev_dbg(wdev->dev, "all retries were not consumed: %d != %d\n",
				rate->count, tx_count);
		अगर (tx_count <= rate->count && tx_count &&
		    arg->txed_rate != wfx_get_hw_rate(wdev, rate))
			dev_dbg(wdev->dev, "inconsistent tx_info rates: %d != %d\n",
				arg->txed_rate, wfx_get_hw_rate(wdev, rate));
		अगर (tx_count > rate->count) अणु
			tx_count -= rate->count;
		पूर्ण अन्यथा अगर (!tx_count) अणु
			rate->count = 0;
			rate->idx = -1;
		पूर्ण अन्यथा अणु
			rate->count = tx_count;
			tx_count = 0;
		पूर्ण
	पूर्ण
	अगर (tx_count)
		dev_dbg(wdev->dev, "%d more retries than expected\n", tx_count);
पूर्ण

व्योम wfx_tx_confirm_cb(काष्ठा wfx_dev *wdev, स्थिर काष्ठा hअगर_cnf_tx *arg)
अणु
	स्थिर काष्ठा wfx_tx_priv *tx_priv;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा wfx_vअगर *wvअगर;
	काष्ठा sk_buff *skb;

	skb = wfx_pending_get(wdev, arg->packet_id);
	अगर (!skb) अणु
		dev_warn(wdev->dev, "received unknown packet_id (%#.8x) from chip\n",
			 arg->packet_id);
		वापस;
	पूर्ण
	tx_info = IEEE80211_SKB_CB(skb);
	tx_priv = wfx_skb_tx_priv(skb);
	wvअगर = wdev_to_wvअगर(wdev, ((काष्ठा hअगर_msg *)skb->data)->पूर्णांकerface);
	WARN_ON(!wvअगर);
	अगर (!wvअगर)
		वापस;

	// Note that wfx_pending_get_pkt_us_delay() get data from tx_info
	_trace_tx_stats(arg, skb, wfx_pending_get_pkt_us_delay(wdev, skb));
	wfx_tx_fill_rates(wdev, tx_info, arg);
	skb_trim(skb, skb->len - tx_priv->icv_size);

	// From now, you can touch to tx_info->status, but करो not touch to
	// tx_priv anymore
	// FIXME: use ieee80211_tx_info_clear_status()
	स_रखो(tx_info->rate_driver_data, 0, माप(tx_info->rate_driver_data));
	स_रखो(tx_info->pad, 0, माप(tx_info->pad));

	अगर (!arg->status) अणु
		tx_info->status.tx_समय =
			le32_to_cpu(arg->media_delay) -
			le32_to_cpu(arg->tx_queue_delay);
		अगर (tx_info->flags & IEEE80211_TX_CTL_NO_ACK)
			tx_info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;
		अन्यथा
			tx_info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण अन्यथा अगर (arg->status == HIF_STATUS_TX_FAIL_REQUEUE) अणु
		WARN(!arg->requeue, "incoherent status and result_flags");
		अगर (tx_info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) अणु
			wvअगर->after_dtim_tx_allowed = false; // DTIM period elapsed
			schedule_work(&wvअगर->update_tim_work);
		पूर्ण
		tx_info->flags |= IEEE80211_TX_STAT_TX_FILTERED;
	पूर्ण
	wfx_skb_dtor(wvअगर, skb);
पूर्ण

अटल व्योम wfx_flush_vअगर(काष्ठा wfx_vअगर *wvअगर, u32 queues,
			  काष्ठा sk_buff_head *dropped)
अणु
	काष्ठा wfx_queue *queue;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		अगर (!(BIT(i) & queues))
			जारी;
		queue = &wvअगर->tx_queue[i];
		अगर (dropped)
			wfx_tx_queue_drop(wvअगर, queue, dropped);
	पूर्ण
	अगर (wvअगर->wdev->chip_frozen)
		वापस;
	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		अगर (!(BIT(i) & queues))
			जारी;
		queue = &wvअगर->tx_queue[i];
		अगर (रुको_event_समयout(wvअगर->wdev->tx_dequeue,
				       wfx_tx_queue_empty(wvअगर, queue),
				       msecs_to_jअगरfies(1000)) <= 0)
			dev_warn(wvअगर->wdev->dev,
				 "frames queued while flushing tx queues?");
	पूर्ण
पूर्ण

व्योम wfx_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       u32 queues, bool drop)
अणु
	काष्ठा wfx_dev *wdev = hw->priv;
	काष्ठा sk_buff_head dropped;
	काष्ठा wfx_vअगर *wvअगर;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा sk_buff *skb;

	skb_queue_head_init(&dropped);
	अगर (vअगर) अणु
		wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
		wfx_flush_vअगर(wvअगर, queues, drop ? &dropped : शून्य);
	पूर्ण अन्यथा अणु
		wvअगर = शून्य;
		जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य)
			wfx_flush_vअगर(wvअगर, queues, drop ? &dropped : शून्य);
	पूर्ण
	wfx_tx_flush(wdev);
	अगर (wdev->chip_frozen)
		wfx_pending_drop(wdev, &dropped);
	जबतक ((skb = skb_dequeue(&dropped)) != शून्य) अणु
		hअगर = (काष्ठा hअगर_msg *)skb->data;
		wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);
		ieee80211_tx_info_clear_status(IEEE80211_SKB_CB(skb));
		wfx_skb_dtor(wvअगर, skb);
	पूर्ण
पूर्ण
