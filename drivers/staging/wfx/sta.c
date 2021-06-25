<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Implementation of mac80211 API.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>

#समावेश "sta.h"
#समावेश "wfx.h"
#समावेश "fwio.h"
#समावेश "bh.h"
#समावेश "key.h"
#समावेश "scan.h"
#समावेश "debug.h"
#समावेश "hif_tx.h"
#समावेश "hif_tx_mib.h"

#घोषणा HIF_MAX_ARP_IP_ADDRTABLE_ENTRIES 2

u32 wfx_rate_mask_to_hw(काष्ठा wfx_dev *wdev, u32 rates)
अणु
	पूर्णांक i;
	u32 ret = 0;
	// WFx only support 2GHz
	काष्ठा ieee80211_supported_band *sband = wdev->hw->wiphy->bands[NL80211_BAND_2GHZ];

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर (rates & BIT(i)) अणु
			अगर (i >= sband->n_bitrates)
				dev_warn(wdev->dev, "unsupported basic rate\n");
			अन्यथा
				ret |= BIT(sband->bitrates[i].hw_value);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम wfx_cooling_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wfx_dev *wdev = container_of(to_delayed_work(work),
					    काष्ठा wfx_dev,
					    cooling_समयout_work);

	wdev->chip_frozen = true;
	wfx_tx_unlock(wdev);
पूर्ण

व्योम wfx_suspend_hot_dev(काष्ठा wfx_dev *wdev, क्रमागत sta_notअगरy_cmd cmd)
अणु
	अगर (cmd == STA_NOTIFY_AWAKE) अणु
		// Device recover normal temperature
		अगर (cancel_delayed_work(&wdev->cooling_समयout_work))
			wfx_tx_unlock(wdev);
	पूर्ण अन्यथा अणु
		// Device is too hot
		schedule_delayed_work(&wdev->cooling_समयout_work, 10 * HZ);
		wfx_tx_lock(wdev);
	पूर्ण
पूर्ण

अटल व्योम wfx_filter_beacon(काष्ठा wfx_vअगर *wvअगर, bool filter_beacon)
अणु
	अटल स्थिर काष्ठा hअगर_ie_table_entry filter_ies[] = अणु
		अणु
			.ie_id        = WLAN_EID_VENDOR_SPECIFIC,
			.has_changed  = 1,
			.no_दीर्घer    = 1,
			.has_appeared = 1,
			.oui          = अणु 0x50, 0x6F, 0x9A पूर्ण,
		पूर्ण, अणु
			.ie_id        = WLAN_EID_HT_OPERATION,
			.has_changed  = 1,
			.no_दीर्घer    = 1,
			.has_appeared = 1,
		पूर्ण, अणु
			.ie_id        = WLAN_EID_ERP_INFO,
			.has_changed  = 1,
			.no_दीर्घer    = 1,
			.has_appeared = 1,
		पूर्ण
	पूर्ण;

	अगर (!filter_beacon) अणु
		hअगर_beacon_filter_control(wvअगर, 0, 1);
	पूर्ण अन्यथा अणु
		hअगर_set_beacon_filter_table(wvअगर, 3, filter_ies);
		hअगर_beacon_filter_control(wvअगर, HIF_BEACON_FILTER_ENABLE, 0);
	पूर्ण
पूर्ण

व्योम wfx_configure_filter(काष्ठा ieee80211_hw *hw, अचिन्हित पूर्णांक changed_flags,
			  अचिन्हित पूर्णांक *total_flags, u64 unused)
अणु
	काष्ठा wfx_vअगर *wvअगर = शून्य;
	काष्ठा wfx_dev *wdev = hw->priv;
	bool filter_bssid, filter_prbreq, filter_beacon;

	// Notes:
	//   - Probe responses (FIF_BCN_PRBRESP_PROMISC) are never filtered
	//   - PS-Poll (FIF_PSPOLL) are never filtered
	//   - RTS, CTS and Ack (FIF_CONTROL) are always filtered
	//   - Broken frames (FIF_FCSFAIL and FIF_PLCPFAIL) are always filtered
	//   - Firmware करोes (yet) allow to क्रमward unicast traffic sent to
	//     other stations (aka. promiscuous mode)
	*total_flags &= FIF_BCN_PRBRESP_PROMISC | FIF_ALLMULTI | FIF_OTHER_BSS |
			FIF_PROBE_REQ | FIF_PSPOLL;

	mutex_lock(&wdev->conf_mutex);
	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य) अणु
		mutex_lock(&wvअगर->scan_lock);

		// Note: FIF_BCN_PRBRESP_PROMISC covers probe response and
		// beacons from other BSS
		अगर (*total_flags & FIF_BCN_PRBRESP_PROMISC)
			filter_beacon = false;
		अन्यथा
			filter_beacon = true;
		wfx_filter_beacon(wvअगर, filter_beacon);

		अगर (*total_flags & FIF_OTHER_BSS)
			filter_bssid = false;
		अन्यथा
			filter_bssid = true;

		// In AP mode, chip can reply to probe request itself
		अगर (*total_flags & FIF_PROBE_REQ &&
		    wvअगर->vअगर->type == NL80211_IFTYPE_AP) अणु
			dev_dbg(wdev->dev, "do not forward probe request in AP mode\n");
			*total_flags &= ~FIF_PROBE_REQ;
		पूर्ण

		अगर (*total_flags & FIF_PROBE_REQ)
			filter_prbreq = false;
		अन्यथा
			filter_prbreq = true;
		hअगर_set_rx_filter(wvअगर, filter_bssid, filter_prbreq);

		mutex_unlock(&wvअगर->scan_lock);
	पूर्ण
	mutex_unlock(&wdev->conf_mutex);
पूर्ण

अटल पूर्णांक wfx_get_ps_समयout(काष्ठा wfx_vअगर *wvअगर, bool *enable_ps)
अणु
	काष्ठा ieee80211_channel *chan0 = शून्य, *chan1 = शून्य;
	काष्ठा ieee80211_conf *conf = &wvअगर->wdev->hw->conf;

	WARN(!wvअगर->vअगर->bss_conf.assoc && enable_ps,
	     "enable_ps is reliable only if associated");
	अगर (wdev_to_wvअगर(wvअगर->wdev, 0))
		chan0 = wdev_to_wvअगर(wvअगर->wdev, 0)->vअगर->bss_conf.chandef.chan;
	अगर (wdev_to_wvअगर(wvअगर->wdev, 1))
		chan1 = wdev_to_wvअगर(wvअगर->wdev, 1)->vअगर->bss_conf.chandef.chan;
	अगर (chan0 && chan1 && chan0->hw_value != chan1->hw_value &&
	    wvअगर->vअगर->type != NL80211_IFTYPE_AP) अणु
		// It is necessary to enable घातersave अगर channels
		// are dअगरferent.
		अगर (enable_ps)
			*enable_ps = true;
		अगर (wvअगर->wdev->क्रमce_ps_समयout > -1)
			वापस wvअगर->wdev->क्रमce_ps_समयout;
		अन्यथा अगर (wfx_api_older_than(wvअगर->wdev, 3, 2))
			वापस 0;
		अन्यथा
			वापस 30;
	पूर्ण
	अगर (enable_ps)
		*enable_ps = wvअगर->vअगर->bss_conf.ps;
	अगर (wvअगर->wdev->क्रमce_ps_समयout > -1)
		वापस wvअगर->wdev->क्रमce_ps_समयout;
	अन्यथा अगर (wvअगर->vअगर->bss_conf.assoc && wvअगर->vअगर->bss_conf.ps)
		वापस conf->dynamic_ps_समयout;
	अन्यथा
		वापस -1;
पूर्ण

पूर्णांक wfx_update_pm(काष्ठा wfx_vअगर *wvअगर)
अणु
	पूर्णांक ps_समयout;
	bool ps;

	अगर (!wvअगर->vअगर->bss_conf.assoc)
		वापस 0;
	ps_समयout = wfx_get_ps_समयout(wvअगर, &ps);
	अगर (!ps)
		ps_समयout = 0;
	WARN_ON(ps_समयout < 0);
	अगर (wvअगर->uapsd_mask)
		ps_समयout = 0;

	अगर (!रुको_क्रम_completion_समयout(&wvअगर->set_pm_mode_complete,
					 TU_TO_JIFFIES(512)))
		dev_warn(wvअगर->wdev->dev,
			 "timeout while waiting of set_pm_mode_complete\n");
	वापस hअगर_set_pm(wvअगर, ps, ps_समयout);
पूर्ण

पूर्णांक wfx_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा wfx_dev *wdev = hw->priv;
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
	पूर्णांक old_uapsd = wvअगर->uapsd_mask;

	WARN_ON(queue >= hw->queues);

	mutex_lock(&wdev->conf_mutex);
	assign_bit(queue, &wvअगर->uapsd_mask, params->uapsd);
	hअगर_set_edca_queue_params(wvअगर, queue, params);
	अगर (wvअगर->vअगर->type == NL80211_IFTYPE_STATION &&
	    old_uapsd != wvअगर->uapsd_mask) अणु
		hअगर_set_uapsd_info(wvअगर, wvअगर->uapsd_mask);
		wfx_update_pm(wvअगर);
	पूर्ण
	mutex_unlock(&wdev->conf_mutex);
	वापस 0;
पूर्ण

पूर्णांक wfx_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा wfx_dev *wdev = hw->priv;
	काष्ठा wfx_vअगर *wvअगर = शून्य;

	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य)
		hअगर_rts_threshold(wvअगर, value);
	वापस 0;
पूर्ण

/* WSM callbacks */

व्योम wfx_event_report_rssi(काष्ठा wfx_vअगर *wvअगर, u8 raw_rcpi_rssi)
अणु
	/* RSSI: चिन्हित Q8.0, RCPI: अचिन्हित Q7.1
	 * RSSI = RCPI / 2 - 110
	 */
	पूर्णांक rcpi_rssi;
	पूर्णांक cqm_evt;

	rcpi_rssi = raw_rcpi_rssi / 2 - 110;
	अगर (rcpi_rssi <= wvअगर->vअगर->bss_conf.cqm_rssi_thold)
		cqm_evt = NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW;
	अन्यथा
		cqm_evt = NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH;
	ieee80211_cqm_rssi_notअगरy(wvअगर->vअगर, cqm_evt, rcpi_rssi, GFP_KERNEL);
पूर्ण

अटल व्योम wfx_beacon_loss_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wfx_vअगर *wvअगर = container_of(to_delayed_work(work),
					    काष्ठा wfx_vअगर, beacon_loss_work);
	काष्ठा ieee80211_bss_conf *bss_conf = &wvअगर->vअगर->bss_conf;

	ieee80211_beacon_loss(wvअगर->vअगर);
	schedule_delayed_work(to_delayed_work(work),
			      msecs_to_jअगरfies(bss_conf->beacon_पूर्णांक));
पूर्ण

व्योम wfx_set_शेष_unicast_key(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर, पूर्णांक idx)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	hअगर_wep_शेष_key_id(wvअगर, idx);
पूर्ण

व्योम wfx_reset(काष्ठा wfx_vअगर *wvअगर)
अणु
	काष्ठा wfx_dev *wdev = wvअगर->wdev;

	wfx_tx_lock_flush(wdev);
	hअगर_reset(wvअगर, false);
	wfx_tx_policy_init(wvअगर);
	अगर (wvअगर_count(wdev) <= 1)
		hअगर_set_block_ack_policy(wvअगर, 0xFF, 0xFF);
	wfx_tx_unlock(wdev);
	wvअगर->join_in_progress = false;
	cancel_delayed_work_sync(&wvअगर->beacon_loss_work);
	wvअगर =  शून्य;
	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य)
		wfx_update_pm(wvअगर);
पूर्ण

पूर्णांक wfx_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
	काष्ठा wfx_sta_priv *sta_priv = (काष्ठा wfx_sta_priv *)&sta->drv_priv;

	sta_priv->vअगर_id = wvअगर->id;

	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		hअगर_set_mfp(wvअगर, sta->mfp, sta->mfp);

	// In station mode, the firmware पूर्णांकerprets new link-id as a TDLS peer.
	अगर (vअगर->type == NL80211_IFTYPE_STATION && !sta->tdls)
		वापस 0;
	sta_priv->link_id = ffz(wvअगर->link_id_map);
	wvअगर->link_id_map |= BIT(sta_priv->link_id);
	WARN_ON(!sta_priv->link_id);
	WARN_ON(sta_priv->link_id >= HIF_LINK_ID_MAX);
	hअगर_map_link(wvअगर, false, sta->addr, sta_priv->link_id, sta->mfp);

	वापस 0;
पूर्ण

पूर्णांक wfx_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
	काष्ठा wfx_sta_priv *sta_priv = (काष्ठा wfx_sta_priv *)&sta->drv_priv;

	// See note in wfx_sta_add()
	अगर (!sta_priv->link_id)
		वापस 0;
	// FIXME add a mutex?
	hअगर_map_link(wvअगर, true, sta->addr, sta_priv->link_id, false);
	wvअगर->link_id_map &= ~BIT(sta_priv->link_id);
	वापस 0;
पूर्ण

अटल पूर्णांक wfx_upload_ap_ढाँचाs(काष्ठा wfx_vअगर *wvअगर)
अणु
	काष्ठा sk_buff *skb;

	skb = ieee80211_beacon_get(wvअगर->wdev->hw, wvअगर->vअगर);
	अगर (!skb)
		वापस -ENOMEM;
	hअगर_set_ढाँचा_frame(wvअगर, skb, HIF_TMPLT_BCN,
			       API_RATE_INDEX_B_1MBPS);
	dev_kमुक्त_skb(skb);

	skb = ieee80211_proberesp_get(wvअगर->wdev->hw, wvअगर->vअगर);
	अगर (!skb)
		वापस -ENOMEM;
	hअगर_set_ढाँचा_frame(wvअगर, skb, HIF_TMPLT_PRBRES,
			       API_RATE_INDEX_B_1MBPS);
	dev_kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम wfx_set_mfp_ap(काष्ठा wfx_vअगर *wvअगर)
अणु
	काष्ठा sk_buff *skb = ieee80211_beacon_get(wvअगर->wdev->hw, wvअगर->vअगर);
	स्थिर पूर्णांक ieoffset = दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
	स्थिर u16 *ptr = (u16 *)cfg80211_find_ie(WLAN_EID_RSN,
						 skb->data + ieoffset,
						 skb->len - ieoffset);
	स्थिर पूर्णांक pairwise_cipher_suite_count_offset = 8 / माप(u16);
	स्थिर पूर्णांक pairwise_cipher_suite_size = 4 / माप(u16);
	स्थिर पूर्णांक akm_suite_size = 4 / माप(u16);

	अगर (ptr) अणु
		ptr += pairwise_cipher_suite_count_offset;
		अगर (WARN_ON(ptr > (u16 *)skb_tail_poपूर्णांकer(skb)))
			वापस;
		ptr += 1 + pairwise_cipher_suite_size * *ptr;
		अगर (WARN_ON(ptr > (u16 *)skb_tail_poपूर्णांकer(skb)))
			वापस;
		ptr += 1 + akm_suite_size * *ptr;
		अगर (WARN_ON(ptr > (u16 *)skb_tail_poपूर्णांकer(skb)))
			वापस;
		hअगर_set_mfp(wvअगर, *ptr & BIT(7), *ptr & BIT(6));
	पूर्ण
पूर्ण

पूर्णांक wfx_start_ap(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
	काष्ठा wfx_dev *wdev = wvअगर->wdev;
	पूर्णांक ret;

	wvअगर =  शून्य;
	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य)
		wfx_update_pm(wvअगर);
	wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
	wfx_upload_ap_ढाँचाs(wvअगर);
	ret = hअगर_start(wvअगर, &vअगर->bss_conf, wvअगर->channel);
	अगर (ret > 0)
		वापस -EIO;
	wfx_set_mfp_ap(wvअगर);
	वापस ret;
पूर्ण

व्योम wfx_stop_ap(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	wfx_reset(wvअगर);
पूर्ण

अटल व्योम wfx_join(काष्ठा wfx_vअगर *wvअगर)
अणु
	पूर्णांक ret;
	काष्ठा ieee80211_bss_conf *conf = &wvअगर->vअगर->bss_conf;
	काष्ठा cfg80211_bss *bss = शून्य;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	स्थिर u8 *ssidie = शून्य;
	पूर्णांक ssidlen = 0;

	wfx_tx_lock_flush(wvअगर->wdev);

	bss = cfg80211_get_bss(wvअगर->wdev->hw->wiphy, wvअगर->channel,
			       conf->bssid, शून्य, 0,
			       IEEE80211_BSS_TYPE_ANY, IEEE80211_PRIVACY_ANY);
	अगर (!bss && !conf->ibss_joined) अणु
		wfx_tx_unlock(wvअगर->wdev);
		वापस;
	पूर्ण

	rcu_पढ़ो_lock(); // protect ssidie
	अगर (bss)
		ssidie = ieee80211_bss_get_ie(bss, WLAN_EID_SSID);
	अगर (ssidie) अणु
		ssidlen = ssidie[1];
		अगर (ssidlen > IEEE80211_MAX_SSID_LEN)
			ssidlen = IEEE80211_MAX_SSID_LEN;
		स_नकल(ssid, &ssidie[2], ssidlen);
	पूर्ण
	rcu_पढ़ो_unlock();

	cfg80211_put_bss(wvअगर->wdev->hw->wiphy, bss);

	wvअगर->join_in_progress = true;
	ret = hअगर_join(wvअगर, conf, wvअगर->channel, ssid, ssidlen);
	अगर (ret) अणु
		ieee80211_connection_loss(wvअगर->vअगर);
		wfx_reset(wvअगर);
	पूर्ण अन्यथा अणु
		/* Due to beacon filtering it is possible that the
		 * AP's beacon is not known क्रम the mac80211 stack.
		 * Disable filtering temporary to make sure the stack
		 * receives at least one
		 */
		wfx_filter_beacon(wvअगर, false);
	पूर्ण
	wfx_tx_unlock(wvअगर->wdev);
पूर्ण

अटल व्योम wfx_join_finalize(काष्ठा wfx_vअगर *wvअगर,
			      काष्ठा ieee80211_bss_conf *info)
अणु
	काष्ठा ieee80211_sta *sta = शून्य;
	पूर्णांक ampdu_density = 0;
	bool greenfield = false;

	rcu_पढ़ो_lock(); // protect sta
	अगर (info->bssid && !info->ibss_joined)
		sta = ieee80211_find_sta(wvअगर->vअगर, info->bssid);
	अगर (sta && sta->ht_cap.ht_supported)
		ampdu_density = sta->ht_cap.ampdu_density;
	अगर (sta && sta->ht_cap.ht_supported &&
	    !(info->ht_operation_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT))
		greenfield = !!(sta->ht_cap.cap & IEEE80211_HT_CAP_GRN_FLD);
	rcu_पढ़ो_unlock();

	wvअगर->join_in_progress = false;
	hअगर_set_association_mode(wvअगर, ampdu_density, greenfield,
				 info->use_लघु_preamble);
	hअगर_keep_alive_period(wvअगर, 0);
	// beacon_loss_count is defined to 7 in net/mac80211/mlme.c. Let's use
	// the same value.
	hअगर_set_bss_params(wvअगर, info->aid, 7);
	hअगर_set_beacon_wakeup_period(wvअगर, 1, 1);
	wfx_update_pm(wvअगर);
पूर्ण

पूर्णांक wfx_join_ibss(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	wfx_upload_ap_ढाँचाs(wvअगर);
	wfx_join(wvअगर);
	वापस 0;
पूर्ण

व्योम wfx_leave_ibss(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	wfx_reset(wvअगर);
पूर्ण

अटल व्योम wfx_enable_beacon(काष्ठा wfx_vअगर *wvअगर, bool enable)
अणु
	// Driver has Content After DTIM Beacon in queue. Driver is रुकोing क्रम
	// a संकेत from the firmware. Since we are going to stop to send
	// beacons, this संकेत will never happens. See also
	// wfx_suspend_resume_mc()
	अगर (!enable && wfx_tx_queues_has_cab(wvअगर)) अणु
		wvअगर->after_dtim_tx_allowed = true;
		wfx_bh_request_tx(wvअगर->wdev);
	पूर्ण
	hअगर_beacon_transmit(wvअगर, enable);
पूर्ण

व्योम wfx_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_bss_conf *info, u32 changed)
अणु
	काष्ठा wfx_dev *wdev = hw->priv;
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
	पूर्णांक i;

	mutex_lock(&wdev->conf_mutex);

	अगर (changed & BSS_CHANGED_BASIC_RATES ||
	    changed & BSS_CHANGED_BEACON_INT ||
	    changed & BSS_CHANGED_BSSID) अणु
		अगर (vअगर->type == NL80211_IFTYPE_STATION)
			wfx_join(wvअगर);
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		अगर (info->assoc || info->ibss_joined)
			wfx_join_finalize(wvअगर, info);
		अन्यथा अगर (!info->assoc && vअगर->type == NL80211_IFTYPE_STATION)
			wfx_reset(wvअगर);
		अन्यथा
			dev_warn(wdev->dev, "%s: misunderstood change: ASSOC\n",
				 __func__);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_INFO) अणु
		अगर (vअगर->type != NL80211_IFTYPE_STATION)
			dev_warn(wdev->dev, "%s: misunderstood change: BEACON_INFO\n",
				 __func__);
		hअगर_set_beacon_wakeup_period(wvअगर, info->dtim_period,
					     info->dtim_period);
		// We temporary क्रमwarded beacon क्रम join process. It is now no
		// more necessary.
		wfx_filter_beacon(wvअगर, true);
	पूर्ण

	अगर (changed & BSS_CHANGED_ARP_FILTER) अणु
		क्रम (i = 0; i < HIF_MAX_ARP_IP_ADDRTABLE_ENTRIES; i++) अणु
			__be32 *arp_addr = &info->arp_addr_list[i];

			अगर (info->arp_addr_cnt > HIF_MAX_ARP_IP_ADDRTABLE_ENTRIES)
				arp_addr = शून्य;
			अगर (i >= info->arp_addr_cnt)
				arp_addr = शून्य;
			hअगर_set_arp_ipv4_filter(wvअगर, i, arp_addr);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_AP_PROBE_RESP ||
	    changed & BSS_CHANGED_BEACON)
		wfx_upload_ap_ढाँचाs(wvअगर);

	अगर (changed & BSS_CHANGED_BEACON_ENABLED)
		wfx_enable_beacon(wvअगर, info->enable_beacon);

	अगर (changed & BSS_CHANGED_KEEP_ALIVE)
		hअगर_keep_alive_period(wvअगर, info->max_idle_period *
					    USEC_PER_TU / USEC_PER_MSEC);

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT)
		hअगर_erp_use_protection(wvअगर, info->use_cts_prot);

	अगर (changed & BSS_CHANGED_ERP_SLOT)
		hअगर_slot_समय(wvअगर, info->use_लघु_slot ? 9 : 20);

	अगर (changed & BSS_CHANGED_CQM)
		hअगर_set_rcpi_rssi_threshold(wvअगर, info->cqm_rssi_thold,
					    info->cqm_rssi_hyst);

	अगर (changed & BSS_CHANGED_TXPOWER)
		hअगर_set_output_घातer(wvअगर, info->txघातer);

	अगर (changed & BSS_CHANGED_PS)
		wfx_update_pm(wvअगर);

	mutex_unlock(&wdev->conf_mutex);
पूर्ण

अटल पूर्णांक wfx_update_tim(काष्ठा wfx_vअगर *wvअगर)
अणु
	काष्ठा sk_buff *skb;
	u16 tim_offset, tim_length;
	u8 *tim_ptr;

	skb = ieee80211_beacon_get_tim(wvअगर->wdev->hw, wvअगर->vअगर,
				       &tim_offset, &tim_length);
	अगर (!skb)
		वापस -ENOENT;
	tim_ptr = skb->data + tim_offset;

	अगर (tim_offset && tim_length >= 6) अणु
		/* Ignore DTIM count from mac80211:
		 * firmware handles DTIM पूर्णांकernally.
		 */
		tim_ptr[2] = 0;

		/* Set/reset aid0 bit */
		अगर (wfx_tx_queues_has_cab(wvअगर))
			tim_ptr[4] |= 1;
		अन्यथा
			tim_ptr[4] &= ~1;
	पूर्ण

	hअगर_update_ie_beacon(wvअगर, tim_ptr, tim_length);
	dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल व्योम wfx_update_tim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wfx_vअगर *wvअगर = container_of(work, काष्ठा wfx_vअगर, update_tim_work);

	wfx_update_tim(wvअगर);
पूर्ण

पूर्णांक wfx_set_tim(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta, bool set)
अणु
	काष्ठा wfx_dev *wdev = hw->priv;
	काष्ठा wfx_sta_priv *sta_dev = (काष्ठा wfx_sta_priv *)&sta->drv_priv;
	काष्ठा wfx_vअगर *wvअगर = wdev_to_wvअगर(wdev, sta_dev->vअगर_id);

	अगर (!wvअगर) अणु
		dev_warn(wdev->dev, "%s: received event for non-existent vif\n", __func__);
		वापस -EIO;
	पूर्ण
	schedule_work(&wvअगर->update_tim_work);
	वापस 0;
पूर्ण

व्योम wfx_suspend_resume_mc(काष्ठा wfx_vअगर *wvअगर, क्रमागत sta_notअगरy_cmd notअगरy_cmd)
अणु
	अगर (notअगरy_cmd != STA_NOTIFY_AWAKE)
		वापस;
	WARN(!wfx_tx_queues_has_cab(wvअगर), "incorrect sequence");
	WARN(wvअगर->after_dtim_tx_allowed, "incorrect sequence");
	wvअगर->after_dtim_tx_allowed = true;
	wfx_bh_request_tx(wvअगर->wdev);
पूर्ण

पूर्णांक wfx_ampdu_action(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_vअगर *vअगर,
		     काष्ठा ieee80211_ampdu_params *params)
अणु
	// Aggregation is implemented fully in firmware
	चयन (params->action) अणु
	हाल IEEE80211_AMPDU_RX_START:
	हाल IEEE80211_AMPDU_RX_STOP:
		// Just acknowledge it to enable frame re-ordering
		वापस 0;
	शेष:
		// Leave the firmware करोing its business क्रम tx aggregation
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक wfx_add_chanctx(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_chanctx_conf *conf)
अणु
	वापस 0;
पूर्ण

व्योम wfx_हटाओ_chanctx(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_chanctx_conf *conf)
अणु
पूर्ण

व्योम wfx_change_chanctx(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_chanctx_conf *conf,
			u32 changed)
अणु
पूर्ण

पूर्णांक wfx_assign_vअगर_chanctx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_chanctx_conf *conf)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
	काष्ठा ieee80211_channel *ch = conf->def.chan;

	WARN(wvअगर->channel, "channel overwrite");
	wvअगर->channel = ch;

	वापस 0;
पूर्ण

व्योम wfx_unassign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_chanctx_conf *conf)
अणु
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;
	काष्ठा ieee80211_channel *ch = conf->def.chan;

	WARN(wvअगर->channel != ch, "channel mismatch");
	wvअगर->channel = शून्य;
पूर्ण

पूर्णांक wfx_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	वापस 0;
पूर्ण

पूर्णांक wfx_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा wfx_dev *wdev = hw->priv;
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
			     IEEE80211_VIF_SUPPORTS_UAPSD |
			     IEEE80211_VIF_SUPPORTS_CQM_RSSI;

	mutex_lock(&wdev->conf_mutex);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP:
		अवरोध;
	शेष:
		mutex_unlock(&wdev->conf_mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	// FIXME: prefer use of container_of() to get vअगर
	wvअगर->vअगर = vअगर;
	wvअगर->wdev = wdev;

	wvअगर->link_id_map = 1; // link-id 0 is reserved क्रम multicast
	INIT_WORK(&wvअगर->update_tim_work, wfx_update_tim_work);
	INIT_DELAYED_WORK(&wvअगर->beacon_loss_work, wfx_beacon_loss_work);

	init_completion(&wvअगर->set_pm_mode_complete);
	complete(&wvअगर->set_pm_mode_complete);
	INIT_WORK(&wvअगर->tx_policy_upload_work, wfx_tx_policy_upload_work);

	mutex_init(&wvअगर->scan_lock);
	init_completion(&wvअगर->scan_complete);
	INIT_WORK(&wvअगर->scan_work, wfx_hw_scan_work);

	wfx_tx_queues_init(wvअगर);
	wfx_tx_policy_init(wvअगर);

	क्रम (i = 0; i < ARRAY_SIZE(wdev->vअगर); i++) अणु
		अगर (!wdev->vअगर[i]) अणु
			wdev->vअगर[i] = vअगर;
			wvअगर->id = i;
			अवरोध;
		पूर्ण
	पूर्ण
	WARN(i == ARRAY_SIZE(wdev->vअगर), "try to instantiate more vif than supported");

	hअगर_set_macaddr(wvअगर, vअगर->addr);

	mutex_unlock(&wdev->conf_mutex);

	wvअगर = शून्य;
	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य) अणु
		// Combo mode करोes not support Block Acks. We can re-enable them
		अगर (wvअगर_count(wdev) == 1)
			hअगर_set_block_ack_policy(wvअगर, 0xFF, 0xFF);
		अन्यथा
			hअगर_set_block_ack_policy(wvअगर, 0x00, 0x00);
	पूर्ण
	वापस ret;
पूर्ण

व्योम wfx_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wfx_dev *wdev = hw->priv;
	काष्ठा wfx_vअगर *wvअगर = (काष्ठा wfx_vअगर *)vअगर->drv_priv;

	रुको_क्रम_completion_समयout(&wvअगर->set_pm_mode_complete, msecs_to_jअगरfies(300));
	wfx_tx_queues_check_empty(wvअगर);

	mutex_lock(&wdev->conf_mutex);
	WARN(wvअगर->link_id_map != 1, "corrupted state");

	hअगर_reset(wvअगर, false);
	hअगर_set_macaddr(wvअगर, शून्य);
	wfx_tx_policy_init(wvअगर);

	cancel_delayed_work_sync(&wvअगर->beacon_loss_work);
	wdev->vअगर[wvअगर->id] = शून्य;
	wvअगर->vअगर = शून्य;

	mutex_unlock(&wdev->conf_mutex);

	wvअगर = शून्य;
	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य) अणु
		// Combo mode करोes not support Block Acks. We can re-enable them
		अगर (wvअगर_count(wdev) == 1)
			hअगर_set_block_ack_policy(wvअगर, 0xFF, 0xFF);
		अन्यथा
			hअगर_set_block_ack_policy(wvअगर, 0x00, 0x00);
	पूर्ण
पूर्ण

पूर्णांक wfx_start(काष्ठा ieee80211_hw *hw)
अणु
	वापस 0;
पूर्ण

व्योम wfx_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wfx_dev *wdev = hw->priv;

	WARN_ON(!skb_queue_empty_lockless(&wdev->tx_pending));
पूर्ण
