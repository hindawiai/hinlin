<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश "ps.h"
#समावेश "io.h"
#समावेश "tx.h"
#समावेश "debug.h"

पूर्णांक wl1271_ps_set_mode(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       क्रमागत wl1271_cmd_ps_mode mode)
अणु
	पूर्णांक ret;
	u16 समयout = wl->conf.conn.dynamic_ps_समयout;

	चयन (mode) अणु
	हाल STATION_AUTO_PS_MODE:
	हाल STATION_POWER_SAVE_MODE:
		wl1271_debug(DEBUG_PSM, "entering psm (mode=%d,timeout=%u)",
			     mode, समयout);

		ret = wl1271_acx_wake_up_conditions(wl, wlvअगर,
					    wl->conf.conn.wake_up_event,
					    wl->conf.conn.listen_पूर्णांकerval);
		अगर (ret < 0) अणु
			wl1271_error("couldn't set wake up conditions");
			वापस ret;
		पूर्ण

		ret = wl1271_cmd_ps_mode(wl, wlvअगर, mode, समयout);
		अगर (ret < 0)
			वापस ret;

		set_bit(WLVIF_FLAG_IN_PS, &wlvअगर->flags);

		/*
		 * enable beacon early termination.
		 * Not relevant क्रम 5GHz and क्रम high rates.
		 */
		अगर ((wlvअगर->band == NL80211_BAND_2GHZ) &&
		    (wlvअगर->basic_rate < CONF_HW_BIT_RATE_9MBPS)) अणु
			ret = wl1271_acx_bet_enable(wl, wlvअगर, true);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		अवरोध;
	हाल STATION_ACTIVE_MODE:
		wl1271_debug(DEBUG_PSM, "leaving psm");

		/* disable beacon early termination */
		अगर ((wlvअगर->band == NL80211_BAND_2GHZ) &&
		    (wlvअगर->basic_rate < CONF_HW_BIT_RATE_9MBPS)) अणु
			ret = wl1271_acx_bet_enable(wl, wlvअगर, false);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ret = wl1271_cmd_ps_mode(wl, wlvअगर, mode, 0);
		अगर (ret < 0)
			वापस ret;

		clear_bit(WLVIF_FLAG_IN_PS, &wlvअगर->flags);
		अवरोध;
	शेष:
		wl1271_warning("trying to set ps to unsupported mode %d", mode);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम wl1271_ps_filter_frames(काष्ठा wl1271 *wl, u8 hlid)
अणु
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	अचिन्हित दीर्घ flags;
	पूर्णांक filtered[NUM_TX_QUEUES];
	काष्ठा wl1271_link *lnk = &wl->links[hlid];

	/* filter all frames currently in the low level queues क्रम this hlid */
	क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
		filtered[i] = 0;
		जबतक ((skb = skb_dequeue(&lnk->tx_queue[i]))) अणु
			filtered[i]++;

			अगर (WARN_ON(wl12xx_is_dummy_packet(wl, skb)))
				जारी;

			info = IEEE80211_SKB_CB(skb);
			info->flags |= IEEE80211_TX_STAT_TX_FILTERED;
			info->status.rates[0].idx = -1;
			ieee80211_tx_status_ni(wl->hw, skb);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&wl->wl_lock, flags);
	क्रम (i = 0; i < NUM_TX_QUEUES; i++) अणु
		wl->tx_queue_count[i] -= filtered[i];
		अगर (lnk->wlvअगर)
			lnk->wlvअगर->tx_queue_count[i] -= filtered[i];
	पूर्ण
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	wl1271_handle_tx_low_watermark(wl);
पूर्ण

व्योम wl12xx_ps_link_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			  u8 hlid, bool clean_queues)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

	अगर (WARN_ON_ONCE(wlvअगर->bss_type != BSS_TYPE_AP_BSS))
		वापस;

	अगर (!test_bit(hlid, wlvअगर->ap.sta_hlid_map) ||
	    test_bit(hlid, &wl->ap_ps_map))
		वापस;

	wl1271_debug(DEBUG_PSM, "start mac80211 PSM on hlid %d pkts %d "
		     "clean_queues %d", hlid, wl->links[hlid].allocated_pkts,
		     clean_queues);

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(vअगर, wl->links[hlid].addr);
	अगर (!sta) अणु
		wl1271_error("could not find sta %pM for starting ps",
			     wl->links[hlid].addr);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	ieee80211_sta_ps_transition_ni(sta, true);
	rcu_पढ़ो_unlock();

	/* करो we want to filter all frames from this link's queues? */
	अगर (clean_queues)
		wl1271_ps_filter_frames(wl, hlid);

	__set_bit(hlid, &wl->ap_ps_map);
पूर्ण

व्योम wl12xx_ps_link_end(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 hlid)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

	अगर (!test_bit(hlid, &wl->ap_ps_map))
		वापस;

	wl1271_debug(DEBUG_PSM, "end mac80211 PSM on hlid %d", hlid);

	__clear_bit(hlid, &wl->ap_ps_map);

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(vअगर, wl->links[hlid].addr);
	अगर (!sta) अणु
		wl1271_error("could not find sta %pM for ending ps",
			     wl->links[hlid].addr);
		जाओ end;
	पूर्ण

	ieee80211_sta_ps_transition_ni(sta, false);
end:
	rcu_पढ़ो_unlock();
पूर्ण
