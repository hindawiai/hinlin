<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spinlock.h>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "io.h"
#समावेश "ps.h"
#समावेश "tx.h"
#समावेश "event.h"
#समावेश "hw_ops.h"

/*
 * TODO: this is here just क्रम now, it must be हटाओd when the data
 * operations are in place.
 */
#समावेश "../wl12xx/reg.h"

अटल पूर्णांक wl1271_set_शेष_wep_key(काष्ठा wl1271 *wl,
				      काष्ठा wl12xx_vअगर *wlvअगर, u8 id)
अणु
	पूर्णांक ret;
	bool is_ap = (wlvअगर->bss_type == BSS_TYPE_AP_BSS);

	अगर (is_ap)
		ret = wl12xx_cmd_set_शेष_wep_key(wl, id,
						     wlvअगर->ap.bcast_hlid);
	अन्यथा
		ret = wl12xx_cmd_set_शेष_wep_key(wl, id, wlvअगर->sta.hlid);

	अगर (ret < 0)
		वापस ret;

	wl1271_debug(DEBUG_CRYPT, "default wep key idx: %d", (पूर्णांक)id);
	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_alloc_tx_id(काष्ठा wl1271 *wl, काष्ठा sk_buff *skb)
अणु
	पूर्णांक id;

	id = find_first_zero_bit(wl->tx_frames_map, wl->num_tx_desc);
	अगर (id >= wl->num_tx_desc)
		वापस -EBUSY;

	__set_bit(id, wl->tx_frames_map);
	wl->tx_frames[id] = skb;
	wl->tx_frames_cnt++;
	वापस id;
पूर्ण

व्योम wl1271_मुक्त_tx_id(काष्ठा wl1271 *wl, पूर्णांक id)
अणु
	अगर (__test_and_clear_bit(id, wl->tx_frames_map)) अणु
		अगर (unlikely(wl->tx_frames_cnt == wl->num_tx_desc))
			clear_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags);

		wl->tx_frames[id] = शून्य;
		wl->tx_frames_cnt--;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(wl1271_मुक्त_tx_id);

अटल व्योम wl1271_tx_ap_update_inconnection_sta(काष्ठा wl1271 *wl,
						 काष्ठा wl12xx_vअगर *wlvअगर,
						 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data +
				       माप(काष्ठा wl1271_tx_hw_descr));
	अगर (!ieee80211_is_auth(hdr->frame_control))
		वापस;

	/*
	 * add the station to the known list beक्रमe transmitting the
	 * authentication response. this way it won't get de-authed by FW
	 * when transmitting too soon.
	 */
	wl1271_acx_set_inconnection_sta(wl, wlvअगर, hdr->addr1);

	/*
	 * ROC क्रम 1 second on the AP channel क्रम completing the connection.
	 * Note the ROC will be जारीd by the update_sta_state callbacks
	 * once the station reaches the associated state.
	 */
	wlcore_update_inconn_sta(wl, wlvअगर, शून्य, true);
	wlvअगर->pending_auth_reply_समय = jअगरfies;
	cancel_delayed_work(&wlvअगर->pending_auth_complete_work);
	ieee80211_queue_delayed_work(wl->hw,
				&wlvअगर->pending_auth_complete_work,
				msecs_to_jअगरfies(WLCORE_PEND_AUTH_ROC_TIMEOUT));
पूर्ण

अटल व्योम wl1271_tx_regulate_link(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर,
				    u8 hlid)
अणु
	bool fw_ps;
	u8 tx_pkts;

	अगर (WARN_ON(!test_bit(hlid, wlvअगर->links_map)))
		वापस;

	fw_ps = test_bit(hlid, &wl->ap_fw_ps_map);
	tx_pkts = wl->links[hlid].allocated_pkts;

	/*
	 * अगर in FW PS and there is enough data in FW we can put the link
	 * पूर्णांकo high-level PS and clean out its TX queues.
	 * Make an exception अगर this is the only connected link. In this
	 * हाल FW-memory congestion is less of a problem.
	 * Note that a single connected STA means 2*ap_count + 1 active links,
	 * since we must account क्रम the global and broadcast AP links
	 * क्रम each AP. The "fw_ps" check assures us the other link is a STA
	 * connected to the AP. Otherwise the FW would not set the PSM bit.
	 */
	अगर (wl->active_link_count > (wl->ap_count*2 + 1) && fw_ps &&
	    tx_pkts >= WL1271_PS_STA_MAX_PACKETS)
		wl12xx_ps_link_start(wl, wlvअगर, hlid, true);
पूर्ण

bool wl12xx_is_dummy_packet(काष्ठा wl1271 *wl, काष्ठा sk_buff *skb)
अणु
	वापस wl->dummy_packet == skb;
पूर्ण
EXPORT_SYMBOL(wl12xx_is_dummy_packet);

अटल u8 wl12xx_tx_get_hlid_ap(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta)
अणु
	अगर (sta) अणु
		काष्ठा wl1271_station *wl_sta;

		wl_sta = (काष्ठा wl1271_station *)sta->drv_priv;
		वापस wl_sta->hlid;
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_hdr *hdr;

		अगर (!test_bit(WLVIF_FLAG_AP_STARTED, &wlvअगर->flags))
			वापस wl->प्रणाली_hlid;

		hdr = (काष्ठा ieee80211_hdr *)skb->data;
		अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)))
			वापस wlvअगर->ap.bcast_hlid;
		अन्यथा
			वापस wlvअगर->ap.global_hlid;
	पूर्ण
पूर्ण

u8 wl12xx_tx_get_hlid(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		      काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_tx_info *control;

	अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS)
		वापस wl12xx_tx_get_hlid_ap(wl, wlvअगर, skb, sta);

	control = IEEE80211_SKB_CB(skb);
	अगर (control->flags & IEEE80211_TX_CTL_TX_OFFCHAN) अणु
		wl1271_debug(DEBUG_TX, "tx offchannel");
		वापस wlvअगर->dev_hlid;
	पूर्ण

	वापस wlvअगर->sta.hlid;
पूर्ण

अचिन्हित पूर्णांक wlcore_calc_packet_alignment(काष्ठा wl1271 *wl,
					  अचिन्हित पूर्णांक packet_length)
अणु
	अगर ((wl->quirks & WLCORE_QUIRK_TX_PAD_LAST_FRAME) ||
	    !(wl->quirks & WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN))
		वापस ALIGN(packet_length, WL1271_TX_ALIGN_TO);
	अन्यथा
		वापस ALIGN(packet_length, WL12XX_BUS_BLOCK_SIZE);
पूर्ण
EXPORT_SYMBOL(wlcore_calc_packet_alignment);

अटल पूर्णांक wl1271_tx_allocate(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा sk_buff *skb, u32 extra, u32 buf_offset,
			      u8 hlid, bool is_gem)
अणु
	काष्ठा wl1271_tx_hw_descr *desc;
	u32 total_len = skb->len + माप(काष्ठा wl1271_tx_hw_descr) + extra;
	u32 total_blocks;
	पूर्णांक id, ret = -EBUSY, ac;
	u32 spare_blocks;

	अगर (buf_offset + total_len > wl->aggr_buf_size)
		वापस -EAGAIN;

	spare_blocks = wlcore_hw_get_spare_blocks(wl, is_gem);

	/* allocate मुक्त identअगरier क्रम the packet */
	id = wl1271_alloc_tx_id(wl, skb);
	अगर (id < 0)
		वापस id;

	total_blocks = wlcore_hw_calc_tx_blocks(wl, total_len, spare_blocks);

	अगर (total_blocks <= wl->tx_blocks_available) अणु
		desc = skb_push(skb, total_len - skb->len);

		wlcore_hw_set_tx_desc_blocks(wl, desc, total_blocks,
					     spare_blocks);

		desc->id = id;

		wl->tx_blocks_available -= total_blocks;
		wl->tx_allocated_blocks += total_blocks;

		/*
		 * If the FW was empty beक्रमe, arm the Tx watchकरोg. Also करो
		 * this on the first Tx after resume, as we always cancel the
		 * watchकरोg on suspend.
		 */
		अगर (wl->tx_allocated_blocks == total_blocks ||
		    test_and_clear_bit(WL1271_FLAG_REINIT_TX_WDOG, &wl->flags))
			wl12xx_rearm_tx_watchकरोg_locked(wl);

		ac = wl1271_tx_get_queue(skb_get_queue_mapping(skb));
		wl->tx_allocated_pkts[ac]++;

		अगर (test_bit(hlid, wl->links_map))
			wl->links[hlid].allocated_pkts++;

		ret = 0;

		wl1271_debug(DEBUG_TX,
			     "tx_allocate: size: %d, blocks: %d, id: %d",
			     total_len, total_blocks, id);
	पूर्ण अन्यथा अणु
		wl1271_मुक्त_tx_id(wl, id);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम wl1271_tx_fill_hdr(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			       काष्ठा sk_buff *skb, u32 extra,
			       काष्ठा ieee80211_tx_info *control, u8 hlid)
अणु
	काष्ठा wl1271_tx_hw_descr *desc;
	पूर्णांक ac, rate_idx;
	s64 hostसमय;
	u16 tx_attr = 0;
	__le16 frame_control;
	काष्ठा ieee80211_hdr *hdr;
	u8 *frame_start;
	bool is_dummy;

	desc = (काष्ठा wl1271_tx_hw_descr *) skb->data;
	frame_start = (u8 *)(desc + 1);
	hdr = (काष्ठा ieee80211_hdr *)(frame_start + extra);
	frame_control = hdr->frame_control;

	/* relocate space क्रम security header */
	अगर (extra) अणु
		पूर्णांक hdrlen = ieee80211_hdrlen(frame_control);
		स_हटाओ(frame_start, hdr, hdrlen);
		skb_set_network_header(skb, skb_network_offset(skb) + extra);
	पूर्ण

	/* configure packet lअगरe समय */
	hostसमय = (kसमय_get_bootसमय_ns() >> 10);
	desc->start_समय = cpu_to_le32(hostसमय - wl->समय_offset);

	is_dummy = wl12xx_is_dummy_packet(wl, skb);
	अगर (is_dummy || !wlvअगर || wlvअगर->bss_type != BSS_TYPE_AP_BSS)
		desc->lअगरe_समय = cpu_to_le16(TX_HW_MGMT_PKT_LIFETIME_TU);
	अन्यथा
		desc->lअगरe_समय = cpu_to_le16(TX_HW_AP_MODE_PKT_LIFETIME_TU);

	/* queue */
	ac = wl1271_tx_get_queue(skb_get_queue_mapping(skb));
	desc->tid = skb->priority;

	अगर (is_dummy) अणु
		/*
		 * FW expects the dummy packet to have an invalid session id -
		 * any session id that is dअगरferent than the one set in the join
		 */
		tx_attr = (SESSION_COUNTER_INVALID <<
			   TX_HW_ATTR_OFST_SESSION_COUNTER) &
			   TX_HW_ATTR_SESSION_COUNTER;

		tx_attr |= TX_HW_ATTR_TX_DUMMY_REQ;
	पूर्ण अन्यथा अगर (wlvअगर) अणु
		u8 session_id = wl->session_ids[hlid];

		अगर ((wl->quirks & WLCORE_QUIRK_AP_ZERO_SESSION_ID) &&
		    (wlvअगर->bss_type == BSS_TYPE_AP_BSS))
			session_id = 0;

		/* configure the tx attributes */
		tx_attr = session_id << TX_HW_ATTR_OFST_SESSION_COUNTER;
	पूर्ण

	desc->hlid = hlid;
	अगर (is_dummy || !wlvअगर)
		rate_idx = 0;
	अन्यथा अगर (wlvअगर->bss_type != BSS_TYPE_AP_BSS) अणु
		/*
		 * अगर the packets are data packets
		 * send them with AP rate policies (EAPOLs are an exception),
		 * otherwise use शेष basic rates
		 */
		अगर (skb->protocol == cpu_to_be16(ETH_P_PAE))
			rate_idx = wlvअगर->sta.basic_rate_idx;
		अन्यथा अगर (control->flags & IEEE80211_TX_CTL_NO_CCK_RATE)
			rate_idx = wlvअगर->sta.p2p_rate_idx;
		अन्यथा अगर (ieee80211_is_data(frame_control))
			rate_idx = wlvअगर->sta.ap_rate_idx;
		अन्यथा
			rate_idx = wlvअगर->sta.basic_rate_idx;
	पूर्ण अन्यथा अणु
		अगर (hlid == wlvअगर->ap.global_hlid)
			rate_idx = wlvअगर->ap.mgmt_rate_idx;
		अन्यथा अगर (hlid == wlvअगर->ap.bcast_hlid ||
			 skb->protocol == cpu_to_be16(ETH_P_PAE) ||
			 !ieee80211_is_data(frame_control))
			/*
			 * send non-data, bcast and EAPOLs using the
			 * min basic rate
			 */
			rate_idx = wlvअगर->ap.bcast_rate_idx;
		अन्यथा
			rate_idx = wlvअगर->ap.ucast_rate_idx[ac];
	पूर्ण

	tx_attr |= rate_idx << TX_HW_ATTR_OFST_RATE_POLICY;

	/* क्रम WEP shared auth - no fw encryption is needed */
	अगर (ieee80211_is_auth(frame_control) &&
	    ieee80211_has_रक्षित(frame_control))
		tx_attr |= TX_HW_ATTR_HOST_ENCRYPT;

	/* send EAPOL frames as voice */
	अगर (control->control.flags & IEEE80211_TX_CTRL_PORT_CTRL_PROTO)
		tx_attr |= TX_HW_ATTR_EAPOL_FRAME;

	desc->tx_attr = cpu_to_le16(tx_attr);

	wlcore_hw_set_tx_desc_csum(wl, desc, skb);
	wlcore_hw_set_tx_desc_data_len(wl, desc, skb);
पूर्ण

/* caller must hold wl->mutex */
अटल पूर्णांक wl1271_prepare_tx_frame(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				   काष्ठा sk_buff *skb, u32 buf_offset, u8 hlid)
अणु
	काष्ठा ieee80211_tx_info *info;
	u32 extra = 0;
	पूर्णांक ret = 0;
	u32 total_len;
	bool is_dummy;
	bool is_gem = false;

	अगर (!skb) अणु
		wl1271_error("discarding null skb");
		वापस -EINVAL;
	पूर्ण

	अगर (hlid == WL12XX_INVALID_LINK_ID) अणु
		wl1271_error("invalid hlid. dropping skb 0x%p", skb);
		वापस -EINVAL;
	पूर्ण

	info = IEEE80211_SKB_CB(skb);

	is_dummy = wl12xx_is_dummy_packet(wl, skb);

	अगर ((wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE) &&
	    info->control.hw_key &&
	    info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP)
		extra = WL1271_EXTRA_SPACE_TKIP;

	अगर (info->control.hw_key) अणु
		bool is_wep;
		u8 idx = info->control.hw_key->hw_key_idx;
		u32 cipher = info->control.hw_key->cipher;

		is_wep = (cipher == WLAN_CIPHER_SUITE_WEP40) ||
			 (cipher == WLAN_CIPHER_SUITE_WEP104);

		अगर (WARN_ON(is_wep && wlvअगर && wlvअगर->शेष_key != idx)) अणु
			ret = wl1271_set_शेष_wep_key(wl, wlvअगर, idx);
			अगर (ret < 0)
				वापस ret;
			wlvअगर->शेष_key = idx;
		पूर्ण

		is_gem = (cipher == WL1271_CIPHER_SUITE_GEM);
	पूर्ण

	ret = wl1271_tx_allocate(wl, wlvअगर, skb, extra, buf_offset, hlid,
				 is_gem);
	अगर (ret < 0)
		वापस ret;

	wl1271_tx_fill_hdr(wl, wlvअगर, skb, extra, info, hlid);

	अगर (!is_dummy && wlvअगर && wlvअगर->bss_type == BSS_TYPE_AP_BSS) अणु
		wl1271_tx_ap_update_inconnection_sta(wl, wlvअगर, skb);
		wl1271_tx_regulate_link(wl, wlvअगर, hlid);
	पूर्ण

	/*
	 * The length of each packet is stored in terms of
	 * words. Thus, we must pad the skb data to make sure its
	 * length is aligned.  The number of padding bytes is computed
	 * and set in wl1271_tx_fill_hdr.
	 * In special हालs, we want to align to a specअगरic block size
	 * (eg. क्रम wl128x with SDIO we align to 256).
	 */
	total_len = wlcore_calc_packet_alignment(wl, skb->len);

	स_नकल(wl->aggr_buf + buf_offset, skb->data, skb->len);
	स_रखो(wl->aggr_buf + buf_offset + skb->len, 0, total_len - skb->len);

	/* Revert side effects in the dummy packet skb, so it can be reused */
	अगर (is_dummy)
		skb_pull(skb, माप(काष्ठा wl1271_tx_hw_descr));

	वापस total_len;
पूर्ण

u32 wl1271_tx_enabled_rates_get(काष्ठा wl1271 *wl, u32 rate_set,
				क्रमागत nl80211_band rate_band)
अणु
	काष्ठा ieee80211_supported_band *band;
	u32 enabled_rates = 0;
	पूर्णांक bit;

	band = wl->hw->wiphy->bands[rate_band];
	क्रम (bit = 0; bit < band->n_bitrates; bit++) अणु
		अगर (rate_set & 0x1)
			enabled_rates |= band->bitrates[bit].hw_value;
		rate_set >>= 1;
	पूर्ण

	/* MCS rates indication are on bits 16 - 31 */
	rate_set >>= HW_HT_RATES_OFFSET - band->n_bitrates;

	क्रम (bit = 0; bit < 16; bit++) अणु
		अगर (rate_set & 0x1)
			enabled_rates |= (CONF_HW_BIT_RATE_MCS_0 << bit);
		rate_set >>= 1;
	पूर्ण

	वापस enabled_rates;
पूर्ण

व्योम wl1271_handle_tx_low_watermark(काष्ठा wl1271 *wl)
अणु
	पूर्णांक i;
	काष्ठा wl12xx_vअगर *wlvअगर;

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
			अगर (wlcore_is_queue_stopped_by_reason(wl, wlvअगर, i,
					WLCORE_QUEUE_STOP_REASON_WATERMARK) &&
			    wlvअगर->tx_queue_count[i] <=
					WL1271_TX_QUEUE_LOW_WATERMARK)
				/* firmware buffer has space, restart queues */
				wlcore_wake_queue(wl, wlvअगर, i,
					WLCORE_QUEUE_STOP_REASON_WATERMARK);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक wlcore_select_ac(काष्ठा wl1271 *wl)
अणु
	पूर्णांक i, q = -1, ac;
	u32 min_pkts = 0xffffffff;

	/*
	 * Find a non-empty ac where:
	 * 1. There are packets to transmit
	 * 2. The FW has the least allocated blocks
	 *
	 * We prioritize the ACs according to VO>VI>BE>BK
	 */
	क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
		ac = wl1271_tx_get_queue(i);
		अगर (wl->tx_queue_count[ac] &&
		    wl->tx_allocated_pkts[ac] < min_pkts) अणु
			q = ac;
			min_pkts = wl->tx_allocated_pkts[q];
		पूर्ण
	पूर्ण

	वापस q;
पूर्ण

अटल काष्ठा sk_buff *wlcore_lnk_dequeue(काष्ठा wl1271 *wl,
					  काष्ठा wl1271_link *lnk, u8 q)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	skb = skb_dequeue(&lnk->tx_queue[q]);
	अगर (skb) अणु
		spin_lock_irqsave(&wl->wl_lock, flags);
		WARN_ON_ONCE(wl->tx_queue_count[q] <= 0);
		wl->tx_queue_count[q]--;
		अगर (lnk->wlvअगर) अणु
			WARN_ON_ONCE(lnk->wlvअगर->tx_queue_count[q] <= 0);
			lnk->wlvअगर->tx_queue_count[q]--;
		पूर्ण
		spin_unlock_irqrestore(&wl->wl_lock, flags);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *wlcore_lnk_dequeue_high_prio(काष्ठा wl1271 *wl,
						    u8 hlid, u8 ac,
						    u8 *low_prio_hlid)
अणु
	काष्ठा wl1271_link *lnk = &wl->links[hlid];

	अगर (!wlcore_hw_lnk_high_prio(wl, hlid, lnk)) अणु
		अगर (*low_prio_hlid == WL12XX_INVALID_LINK_ID &&
		    !skb_queue_empty(&lnk->tx_queue[ac]) &&
		    wlcore_hw_lnk_low_prio(wl, hlid, lnk))
			/* we found the first non-empty low priority queue */
			*low_prio_hlid = hlid;

		वापस शून्य;
	पूर्ण

	वापस wlcore_lnk_dequeue(wl, lnk, ac);
पूर्ण

अटल काष्ठा sk_buff *wlcore_vअगर_dequeue_high_prio(काष्ठा wl1271 *wl,
						    काष्ठा wl12xx_vअगर *wlvअगर,
						    u8 ac, u8 *hlid,
						    u8 *low_prio_hlid)
अणु
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक i, h, start_hlid;

	/* start from the link after the last one */
	start_hlid = (wlvअगर->last_tx_hlid + 1) % wl->num_links;

	/* dequeue according to AC, round robin on each link */
	क्रम (i = 0; i < wl->num_links; i++) अणु
		h = (start_hlid + i) % wl->num_links;

		/* only consider connected stations */
		अगर (!test_bit(h, wlvअगर->links_map))
			जारी;

		skb = wlcore_lnk_dequeue_high_prio(wl, h, ac,
						   low_prio_hlid);
		अगर (!skb)
			जारी;

		wlvअगर->last_tx_hlid = h;
		अवरोध;
	पूर्ण

	अगर (!skb)
		wlvअगर->last_tx_hlid = 0;

	*hlid = wlvअगर->last_tx_hlid;
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *wl1271_skb_dequeue(काष्ठा wl1271 *wl, u8 *hlid)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा wl12xx_vअगर *wlvअगर = wl->last_wlvअगर;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ac;
	u8 low_prio_hlid = WL12XX_INVALID_LINK_ID;

	ac = wlcore_select_ac(wl);
	अगर (ac < 0)
		जाओ out;

	/* जारी from last wlvअगर (round robin) */
	अगर (wlvअगर) अणु
		wl12xx_क्रम_each_wlvअगर_जारी(wl, wlvअगर) अणु
			अगर (!wlvअगर->tx_queue_count[ac])
				जारी;

			skb = wlcore_vअगर_dequeue_high_prio(wl, wlvअगर, ac, hlid,
							   &low_prio_hlid);
			अगर (!skb)
				जारी;

			wl->last_wlvअगर = wlvअगर;
			अवरोध;
		पूर्ण
	पूर्ण

	/* dequeue from the प्रणाली HLID beक्रमe the restarting wlvअगर list */
	अगर (!skb) अणु
		skb = wlcore_lnk_dequeue_high_prio(wl, wl->प्रणाली_hlid,
						   ac, &low_prio_hlid);
		अगर (skb) अणु
			*hlid = wl->प्रणाली_hlid;
			wl->last_wlvअगर = शून्य;
		पूर्ण
	पूर्ण

	/* Do a new pass over the wlvअगर list. But no need to जारी
	 * after last_wlvअगर. The previous pass should have found it. */
	अगर (!skb) अणु
		wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
			अगर (!wlvअगर->tx_queue_count[ac])
				जाओ next;

			skb = wlcore_vअगर_dequeue_high_prio(wl, wlvअगर, ac, hlid,
							   &low_prio_hlid);
			अगर (skb) अणु
				wl->last_wlvअगर = wlvअगर;
				अवरोध;
			पूर्ण

next:
			अगर (wlvअगर == wl->last_wlvअगर)
				अवरोध;
		पूर्ण
	पूर्ण

	/* no high priority skbs found - but maybe a low priority one? */
	अगर (!skb && low_prio_hlid != WL12XX_INVALID_LINK_ID) अणु
		काष्ठा wl1271_link *lnk = &wl->links[low_prio_hlid];
		skb = wlcore_lnk_dequeue(wl, lnk, ac);

		WARN_ON(!skb); /* we checked this beक्रमe */
		*hlid = low_prio_hlid;

		/* ensure proper round robin in the vअगर/link levels */
		wl->last_wlvअगर = lnk->wlvअगर;
		अगर (lnk->wlvअगर)
			lnk->wlvअगर->last_tx_hlid = low_prio_hlid;

	पूर्ण

out:
	अगर (!skb &&
	    test_and_clear_bit(WL1271_FLAG_DUMMY_PACKET_PENDING, &wl->flags)) अणु
		पूर्णांक q;

		skb = wl->dummy_packet;
		*hlid = wl->प्रणाली_hlid;
		q = wl1271_tx_get_queue(skb_get_queue_mapping(skb));
		spin_lock_irqsave(&wl->wl_lock, flags);
		WARN_ON_ONCE(wl->tx_queue_count[q] <= 0);
		wl->tx_queue_count[q]--;
		spin_unlock_irqrestore(&wl->wl_lock, flags);
	पूर्ण

	वापस skb;
पूर्ण

अटल व्योम wl1271_skb_queue_head(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				  काष्ठा sk_buff *skb, u8 hlid)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक q = wl1271_tx_get_queue(skb_get_queue_mapping(skb));

	अगर (wl12xx_is_dummy_packet(wl, skb)) अणु
		set_bit(WL1271_FLAG_DUMMY_PACKET_PENDING, &wl->flags);
	पूर्ण अन्यथा अणु
		skb_queue_head(&wl->links[hlid].tx_queue[q], skb);

		/* make sure we dequeue the same packet next समय */
		wlvअगर->last_tx_hlid = (hlid + wl->num_links - 1) %
				      wl->num_links;
	पूर्ण

	spin_lock_irqsave(&wl->wl_lock, flags);
	wl->tx_queue_count[q]++;
	अगर (wlvअगर)
		wlvअगर->tx_queue_count[q]++;
	spin_unlock_irqrestore(&wl->wl_lock, flags);
पूर्ण

अटल bool wl1271_tx_is_data_present(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)(skb->data);

	वापस ieee80211_is_data_present(hdr->frame_control);
पूर्ण

व्योम wl12xx_rearm_rx_streaming(काष्ठा wl1271 *wl, अचिन्हित दीर्घ *active_hlids)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;
	u32 समयout;
	u8 hlid;

	अगर (!wl->conf.rx_streaming.पूर्णांकerval)
		वापस;

	अगर (!wl->conf.rx_streaming.always &&
	    !test_bit(WL1271_FLAG_SOFT_GEMINI, &wl->flags))
		वापस;

	समयout = wl->conf.rx_streaming.duration;
	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		bool found = false;
		क्रम_each_set_bit(hlid, active_hlids, wl->num_links) अणु
			अगर (test_bit(hlid, wlvअगर->links_map)) अणु
				found  = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found)
			जारी;

		/* enable rx streaming */
		अगर (!test_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvअगर->flags))
			ieee80211_queue_work(wl->hw,
					     &wlvअगर->rx_streaming_enable_work);

		mod_समयr(&wlvअगर->rx_streaming_समयr,
			  jअगरfies + msecs_to_jअगरfies(समयout));
	पूर्ण
पूर्ण

/*
 * Returns failure values only in हाल of failed bus ops within this function.
 * wl1271_prepare_tx_frame retvals won't be वापसed in order to aव्योम
 * triggering recovery by higher layers when not necessary.
 * In हाल a FW command fails within wl1271_prepare_tx_frame fails a recovery
 * will be queued in wl1271_cmd_send. -EAGAIN/-EBUSY from prepare_tx_frame
 * can occur and are legitimate so करोn't propagate. -EINVAL will emit a WARNING
 * within prepare_tx_frame code but there's nothing we should करो about those
 * as well.
 */
पूर्णांक wlcore_tx_work_locked(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा sk_buff *skb;
	काष्ठा wl1271_tx_hw_descr *desc;
	u32 buf_offset = 0, last_len = 0;
	bool sent_packets = false;
	अचिन्हित दीर्घ active_hlids[BITS_TO_LONGS(WLCORE_MAX_LINKS)] = अणु0पूर्ण;
	पूर्णांक ret = 0;
	पूर्णांक bus_ret = 0;
	u8 hlid;

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		वापस 0;

	जबतक ((skb = wl1271_skb_dequeue(wl, &hlid))) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		bool has_data = false;

		wlvअगर = शून्य;
		अगर (!wl12xx_is_dummy_packet(wl, skb))
			wlvअगर = wl12xx_vअगर_to_data(info->control.vअगर);
		अन्यथा
			hlid = wl->प्रणाली_hlid;

		has_data = wlvअगर && wl1271_tx_is_data_present(skb);
		ret = wl1271_prepare_tx_frame(wl, wlvअगर, skb, buf_offset,
					      hlid);
		अगर (ret == -EAGAIN) अणु
			/*
			 * Aggregation buffer is full.
			 * Flush buffer and try again.
			 */
			wl1271_skb_queue_head(wl, wlvअगर, skb, hlid);

			buf_offset = wlcore_hw_pre_pkt_send(wl, buf_offset,
							    last_len);
			bus_ret = wlcore_ग_लिखो_data(wl, REG_SLV_MEM_DATA,
					     wl->aggr_buf, buf_offset, true);
			अगर (bus_ret < 0)
				जाओ out;

			sent_packets = true;
			buf_offset = 0;
			जारी;
		पूर्ण अन्यथा अगर (ret == -EBUSY) अणु
			/*
			 * Firmware buffer is full.
			 * Queue back last skb, and stop aggregating.
			 */
			wl1271_skb_queue_head(wl, wlvअगर, skb, hlid);
			/* No work left, aव्योम scheduling redundant tx work */
			set_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags);
			जाओ out_ack;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			अगर (wl12xx_is_dummy_packet(wl, skb))
				/*
				 * fw still expects dummy packet,
				 * so re-enqueue it
				 */
				wl1271_skb_queue_head(wl, wlvअगर, skb, hlid);
			अन्यथा
				ieee80211_मुक्त_txskb(wl->hw, skb);
			जाओ out_ack;
		पूर्ण
		last_len = ret;
		buf_offset += last_len;
		wl->tx_packets_count++;
		अगर (has_data) अणु
			desc = (काष्ठा wl1271_tx_hw_descr *) skb->data;
			__set_bit(desc->hlid, active_hlids);
		पूर्ण
	पूर्ण

out_ack:
	अगर (buf_offset) अणु
		buf_offset = wlcore_hw_pre_pkt_send(wl, buf_offset, last_len);
		bus_ret = wlcore_ग_लिखो_data(wl, REG_SLV_MEM_DATA, wl->aggr_buf,
					     buf_offset, true);
		अगर (bus_ret < 0)
			जाओ out;

		sent_packets = true;
	पूर्ण
	अगर (sent_packets) अणु
		/*
		 * Interrupt the firmware with the new packets. This is only
		 * required क्रम older hardware revisions
		 */
		अगर (wl->quirks & WLCORE_QUIRK_END_OF_TRANSACTION) अणु
			bus_ret = wlcore_ग_लिखो32(wl, WL12XX_HOST_WR_ACCESS,
					     wl->tx_packets_count);
			अगर (bus_ret < 0)
				जाओ out;
		पूर्ण

		wl1271_handle_tx_low_watermark(wl);
	पूर्ण
	wl12xx_rearm_rx_streaming(wl, active_hlids);

out:
	वापस bus_ret;
पूर्ण

व्योम wl1271_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wl1271 *wl = container_of(work, काष्ठा wl1271, tx_work);
	पूर्णांक ret;

	mutex_lock(&wl->mutex);
	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wlcore_tx_work_locked(wl);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		wl12xx_queue_recovery_work(wl);
		जाओ out;
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
पूर्ण

अटल u8 wl1271_tx_get_rate_flags(u8 rate_class_index)
अणु
	u8 flags = 0;

	/*
	 * TODO: use wl12xx स्थिरants when this code is moved to wl12xx, as
	 * only it uses Tx-completion.
	 */
	अगर (rate_class_index <= 8)
		flags |= IEEE80211_TX_RC_MCS;

	/*
	 * TODO: use wl12xx स्थिरants when this code is moved to wl12xx, as
	 * only it uses Tx-completion.
	 */
	अगर (rate_class_index == 0)
		flags |= IEEE80211_TX_RC_SHORT_GI;

	वापस flags;
पूर्ण

अटल व्योम wl1271_tx_complete_packet(काष्ठा wl1271 *wl,
				      काष्ठा wl1271_tx_hw_res_descr *result)
अणु
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा sk_buff *skb;
	पूर्णांक id = result->id;
	पूर्णांक rate = -1;
	u8 rate_flags = 0;
	u8 retries = 0;

	/* check क्रम id legality */
	अगर (unlikely(id >= wl->num_tx_desc || wl->tx_frames[id] == शून्य)) अणु
		wl1271_warning("TX result illegal id: %d", id);
		वापस;
	पूर्ण

	skb = wl->tx_frames[id];
	info = IEEE80211_SKB_CB(skb);

	अगर (wl12xx_is_dummy_packet(wl, skb)) अणु
		wl1271_मुक्त_tx_id(wl, id);
		वापस;
	पूर्ण

	/* info->control is valid as दीर्घ as we करोn't update info->status */
	vअगर = info->control.vअगर;
	wlvअगर = wl12xx_vअगर_to_data(vअगर);

	/* update the TX status info */
	अगर (result->status == TX_SUCCESS) अणु
		अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
			info->flags |= IEEE80211_TX_STAT_ACK;
		rate = wlcore_rate_to_idx(wl, result->rate_class_index,
					  wlvअगर->band);
		rate_flags = wl1271_tx_get_rate_flags(result->rate_class_index);
		retries = result->ack_failures;
	पूर्ण अन्यथा अगर (result->status == TX_RETRY_EXCEEDED) अणु
		wl->stats.excessive_retries++;
		retries = result->ack_failures;
	पूर्ण

	info->status.rates[0].idx = rate;
	info->status.rates[0].count = retries;
	info->status.rates[0].flags = rate_flags;
	info->status.ack_संकेत = -1;

	wl->stats.retry_count += result->ack_failures;

	/* हटाओ निजी header from packet */
	skb_pull(skb, माप(काष्ठा wl1271_tx_hw_descr));

	/* हटाओ TKIP header space अगर present */
	अगर ((wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE) &&
	    info->control.hw_key &&
	    info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
		पूर्णांक hdrlen = ieee80211_get_hdrlen_from_skb(skb);
		स_हटाओ(skb->data + WL1271_EXTRA_SPACE_TKIP, skb->data,
			hdrlen);
		skb_pull(skb, WL1271_EXTRA_SPACE_TKIP);
	पूर्ण

	wl1271_debug(DEBUG_TX, "tx status id %u skb 0x%p failures %u rate 0x%x"
		     " status 0x%x",
		     result->id, skb, result->ack_failures,
		     result->rate_class_index, result->status);

	/* वापस the packet to the stack */
	skb_queue_tail(&wl->deferred_tx_queue, skb);
	queue_work(wl->मुक्तzable_wq, &wl->netstack_work);
	wl1271_मुक्त_tx_id(wl, result->id);
पूर्ण

/* Called upon reception of a TX complete पूर्णांकerrupt */
पूर्णांक wlcore_tx_complete(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_acx_mem_map *memmap = wl->target_mem_map;
	u32 count, fw_counter;
	u32 i;
	पूर्णांक ret;

	/* पढ़ो the tx results from the chipset */
	ret = wlcore_पढ़ो(wl, le32_to_cpu(memmap->tx_result),
			  wl->tx_res_अगर, माप(*wl->tx_res_अगर), false);
	अगर (ret < 0)
		जाओ out;

	fw_counter = le32_to_cpu(wl->tx_res_अगर->tx_result_fw_counter);

	/* ग_लिखो host counter to chipset (to ack) */
	ret = wlcore_ग_लिखो32(wl, le32_to_cpu(memmap->tx_result) +
			     दुरत्व(काष्ठा wl1271_tx_hw_res_अगर,
				      tx_result_host_counter), fw_counter);
	अगर (ret < 0)
		जाओ out;

	count = fw_counter - wl->tx_results_count;
	wl1271_debug(DEBUG_TX, "tx_complete received, packets: %d", count);

	/* verअगरy that the result buffer is not getting overrun */
	अगर (unlikely(count > TX_HW_RESULT_QUEUE_LEN))
		wl1271_warning("TX result overflow from chipset: %d", count);

	/* process the results */
	क्रम (i = 0; i < count; i++) अणु
		काष्ठा wl1271_tx_hw_res_descr *result;
		u8 offset = wl->tx_results_count & TX_HW_RESULT_QUEUE_LEN_MASK;

		/* process the packet */
		result =  &(wl->tx_res_अगर->tx_results_queue[offset]);
		wl1271_tx_complete_packet(wl, result);

		wl->tx_results_count++;
	पूर्ण

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(wlcore_tx_complete);

व्योम wl1271_tx_reset_link_queues(काष्ठा wl1271 *wl, u8 hlid)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा ieee80211_tx_info *info;
	पूर्णांक total[NUM_TX_QUEUES];
	काष्ठा wl1271_link *lnk = &wl->links[hlid];

	क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
		total[i] = 0;
		जबतक ((skb = skb_dequeue(&lnk->tx_queue[i]))) अणु
			wl1271_debug(DEBUG_TX, "link freeing skb 0x%p", skb);

			अगर (!wl12xx_is_dummy_packet(wl, skb)) अणु
				info = IEEE80211_SKB_CB(skb);
				info->status.rates[0].idx = -1;
				info->status.rates[0].count = 0;
				ieee80211_tx_status_ni(wl->hw, skb);
			पूर्ण

			total[i]++;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&wl->wl_lock, flags);
	क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
		wl->tx_queue_count[i] -= total[i];
		अगर (lnk->wlvअगर)
			lnk->wlvअगर->tx_queue_count[i] -= total[i];
	पूर्ण
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	wl1271_handle_tx_low_watermark(wl);
पूर्ण

/* caller must hold wl->mutex and TX must be stopped */
व्योम wl12xx_tx_reset_wlvअगर(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक i;

	/* TX failure */
	क्रम_each_set_bit(i, wlvअगर->links_map, wl->num_links) अणु
		अगर (wlvअगर->bss_type == BSS_TYPE_AP_BSS &&
		    i != wlvअगर->ap.bcast_hlid && i != wlvअगर->ap.global_hlid) अणु
			/* this calls wl12xx_मुक्त_link */
			wl1271_मुक्त_sta(wl, wlvअगर, i);
		पूर्ण अन्यथा अणु
			u8 hlid = i;
			wl12xx_मुक्त_link(wl, wlvअगर, &hlid);
		पूर्ण
	पूर्ण
	wlvअगर->last_tx_hlid = 0;

	क्रम (i = 0; i < NUM_TX_QUEUES; i++)
		wlvअगर->tx_queue_count[i] = 0;
पूर्ण
/* caller must hold wl->mutex and TX must be stopped */
व्योम wl12xx_tx_reset(काष्ठा wl1271 *wl)
अणु
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;

	/* only reset the queues अगर something bad happened */
	अगर (wl1271_tx_total_queue_count(wl) != 0) अणु
		क्रम (i = 0; i < wl->num_links; i++)
			wl1271_tx_reset_link_queues(wl, i);

		क्रम (i = 0; i < NUM_TX_QUEUES; i++)
			wl->tx_queue_count[i] = 0;
	पूर्ण

	/*
	 * Make sure the driver is at a consistent state, in हाल this
	 * function is called from a context other than पूर्णांकerface removal.
	 * This call will always wake the TX queues.
	 */
	wl1271_handle_tx_low_watermark(wl);

	क्रम (i = 0; i < wl->num_tx_desc; i++) अणु
		अगर (wl->tx_frames[i] == शून्य)
			जारी;

		skb = wl->tx_frames[i];
		wl1271_मुक्त_tx_id(wl, i);
		wl1271_debug(DEBUG_TX, "freeing skb 0x%p", skb);

		अगर (!wl12xx_is_dummy_packet(wl, skb)) अणु
			/*
			 * Remove निजी headers beक्रमe passing the skb to
			 * mac80211
			 */
			info = IEEE80211_SKB_CB(skb);
			skb_pull(skb, माप(काष्ठा wl1271_tx_hw_descr));
			अगर ((wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE) &&
			    info->control.hw_key &&
			    info->control.hw_key->cipher ==
			    WLAN_CIPHER_SUITE_TKIP) अणु
				पूर्णांक hdrlen = ieee80211_get_hdrlen_from_skb(skb);
				स_हटाओ(skb->data + WL1271_EXTRA_SPACE_TKIP,
					skb->data, hdrlen);
				skb_pull(skb, WL1271_EXTRA_SPACE_TKIP);
			पूर्ण

			info->status.rates[0].idx = -1;
			info->status.rates[0].count = 0;

			ieee80211_tx_status_ni(wl->hw, skb);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा WL1271_TX_FLUSH_TIMEOUT 500000

/* caller must *NOT* hold wl->mutex */
व्योम wl1271_tx_flush(काष्ठा wl1271 *wl)
अणु
	अचिन्हित दीर्घ समयout, start_समय;
	पूर्णांक i;
	start_समय = jअगरfies;
	समयout = start_समय + usecs_to_jअगरfies(WL1271_TX_FLUSH_TIMEOUT);

	/* only one flush should be in progress, क्रम consistent queue state */
	mutex_lock(&wl->flush_mutex);

	mutex_lock(&wl->mutex);
	अगर (wl->tx_frames_cnt == 0 && wl1271_tx_total_queue_count(wl) == 0) अणु
		mutex_unlock(&wl->mutex);
		जाओ out;
	पूर्ण

	wlcore_stop_queues(wl, WLCORE_QUEUE_STOP_REASON_FLUSH);

	जबतक (!समय_after(jअगरfies, समयout)) अणु
		wl1271_debug(DEBUG_MAC80211, "flushing tx buffer: %d %d",
			     wl->tx_frames_cnt,
			     wl1271_tx_total_queue_count(wl));

		/* क्रमce Tx and give the driver some समय to flush data */
		mutex_unlock(&wl->mutex);
		अगर (wl1271_tx_total_queue_count(wl))
			wl1271_tx_work(&wl->tx_work);
		msleep(20);
		mutex_lock(&wl->mutex);

		अगर ((wl->tx_frames_cnt == 0) &&
		    (wl1271_tx_total_queue_count(wl) == 0)) अणु
			wl1271_debug(DEBUG_MAC80211, "tx flush took %d ms",
				     jअगरfies_to_msecs(jअगरfies - start_समय));
			जाओ out_wake;
		पूर्ण
	पूर्ण

	wl1271_warning("Unable to flush all TX buffers, "
		       "timed out (timeout %d ms",
		       WL1271_TX_FLUSH_TIMEOUT / 1000);

	/* क्रमcibly flush all Tx buffers on our queues */
	क्रम (i = 0; i < wl->num_links; i++)
		wl1271_tx_reset_link_queues(wl, i);

out_wake:
	wlcore_wake_queues(wl, WLCORE_QUEUE_STOP_REASON_FLUSH);
	mutex_unlock(&wl->mutex);
out:
	mutex_unlock(&wl->flush_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_tx_flush);

u32 wl1271_tx_min_rate_get(काष्ठा wl1271 *wl, u32 rate_set)
अणु
	अगर (WARN_ON(!rate_set))
		वापस 0;

	वापस BIT(__ffs(rate_set));
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_tx_min_rate_get);

व्योम wlcore_stop_queue_locked(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			      u8 queue, क्रमागत wlcore_queue_stop_reason reason)
अणु
	पूर्णांक hwq = wlcore_tx_get_mac80211_queue(wlvअगर, queue);
	bool stopped = !!wl->queue_stop_reasons[hwq];

	/* queue should not be stopped क्रम this reason */
	WARN_ON_ONCE(test_and_set_bit(reason, &wl->queue_stop_reasons[hwq]));

	अगर (stopped)
		वापस;

	ieee80211_stop_queue(wl->hw, hwq);
पूर्ण

व्योम wlcore_stop_queue(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 queue,
		       क्रमागत wlcore_queue_stop_reason reason)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wl->wl_lock, flags);
	wlcore_stop_queue_locked(wl, wlvअगर, queue, reason);
	spin_unlock_irqrestore(&wl->wl_lock, flags);
पूर्ण

व्योम wlcore_wake_queue(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 queue,
		       क्रमागत wlcore_queue_stop_reason reason)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक hwq = wlcore_tx_get_mac80211_queue(wlvअगर, queue);

	spin_lock_irqsave(&wl->wl_lock, flags);

	/* queue should not be clear क्रम this reason */
	WARN_ON_ONCE(!test_and_clear_bit(reason, &wl->queue_stop_reasons[hwq]));

	अगर (wl->queue_stop_reasons[hwq])
		जाओ out;

	ieee80211_wake_queue(wl->hw, hwq);

out:
	spin_unlock_irqrestore(&wl->wl_lock, flags);
पूर्ण

व्योम wlcore_stop_queues(काष्ठा wl1271 *wl,
			क्रमागत wlcore_queue_stop_reason reason)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wl->wl_lock, flags);

	/* mark all possible queues as stopped */
        क्रम (i = 0; i < WLCORE_NUM_MAC_ADDRESSES * NUM_TX_QUEUES; i++)
                WARN_ON_ONCE(test_and_set_bit(reason,
					      &wl->queue_stop_reasons[i]));

	/* use the global version to make sure all vअगरs in mac80211 we करोn't
	 * know are stopped.
	 */
	ieee80211_stop_queues(wl->hw);

	spin_unlock_irqrestore(&wl->wl_lock, flags);
पूर्ण

व्योम wlcore_wake_queues(काष्ठा wl1271 *wl,
			क्रमागत wlcore_queue_stop_reason reason)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wl->wl_lock, flags);

	/* mark all possible queues as awake */
        क्रम (i = 0; i < WLCORE_NUM_MAC_ADDRESSES * NUM_TX_QUEUES; i++)
		WARN_ON_ONCE(!test_and_clear_bit(reason,
						 &wl->queue_stop_reasons[i]));

	/* use the global version to make sure all vअगरs in mac80211 we करोn't
	 * know are woken up.
	 */
	ieee80211_wake_queues(wl->hw);

	spin_unlock_irqrestore(&wl->wl_lock, flags);
पूर्ण

bool wlcore_is_queue_stopped_by_reason(काष्ठा wl1271 *wl,
				       काष्ठा wl12xx_vअगर *wlvअगर, u8 queue,
				       क्रमागत wlcore_queue_stop_reason reason)
अणु
	अचिन्हित दीर्घ flags;
	bool stopped;

	spin_lock_irqsave(&wl->wl_lock, flags);
	stopped = wlcore_is_queue_stopped_by_reason_locked(wl, wlvअगर, queue,
							   reason);
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	वापस stopped;
पूर्ण

bool wlcore_is_queue_stopped_by_reason_locked(काष्ठा wl1271 *wl,
				       काष्ठा wl12xx_vअगर *wlvअगर, u8 queue,
				       क्रमागत wlcore_queue_stop_reason reason)
अणु
	पूर्णांक hwq = wlcore_tx_get_mac80211_queue(wlvअगर, queue);

	निश्चित_spin_locked(&wl->wl_lock);
	वापस test_bit(reason, &wl->queue_stop_reasons[hwq]);
पूर्ण

bool wlcore_is_queue_stopped_locked(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				    u8 queue)
अणु
	पूर्णांक hwq = wlcore_tx_get_mac80211_queue(wlvअगर, queue);

	निश्चित_spin_locked(&wl->wl_lock);
	वापस !!wl->queue_stop_reasons[hwq];
पूर्ण
