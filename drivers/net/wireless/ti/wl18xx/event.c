<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2012 Texas Instruments. All rights reserved.
 */

#समावेश <net/genetlink.h>
#समावेश "event.h"
#समावेश "scan.h"
#समावेश "conf.h"
#समावेश "../wlcore/cmd.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/vendor_cmd.h"

पूर्णांक wl18xx_रुको_क्रम_event(काष्ठा wl1271 *wl, क्रमागत wlcore_रुको_event event,
			  bool *समयout)
अणु
	u32 local_event;

	चयन (event) अणु
	हाल WLCORE_EVENT_PEER_REMOVE_COMPLETE:
		local_event = PEER_REMOVE_COMPLETE_EVENT_ID;
		अवरोध;

	हाल WLCORE_EVENT_DFS_CONFIG_COMPLETE:
		local_event = DFS_CHANNELS_CONFIG_COMPLETE_EVENT;
		अवरोध;

	शेष:
		/* event not implemented */
		वापस 0;
	पूर्ण
	वापस wlcore_cmd_रुको_क्रम_event_or_समयout(wl, local_event, समयout);
पूर्ण

अटल स्थिर अक्षर *wl18xx_radar_type_decode(u8 radar_type)
अणु
	चयन (radar_type) अणु
	हाल RADAR_TYPE_REGULAR:
		वापस "REGULAR";
	हाल RADAR_TYPE_CHIRP:
		वापस "CHIRP";
	हाल RADAR_TYPE_NONE:
	शेष:
		वापस "N/A";
	पूर्ण
पूर्ण

अटल पूर्णांक wlcore_smart_config_sync_event(काष्ठा wl1271 *wl, u8 sync_channel,
					  u8 sync_band)
अणु
	काष्ठा sk_buff *skb;
	क्रमागत nl80211_band band;
	पूर्णांक freq;

	अगर (sync_band == WLCORE_BAND_5GHZ)
		band = NL80211_BAND_5GHZ;
	अन्यथा
		band = NL80211_BAND_2GHZ;

	freq = ieee80211_channel_to_frequency(sync_channel, band);

	wl1271_debug(DEBUG_EVENT,
		     "SMART_CONFIG_SYNC_EVENT_ID, freq: %d (chan: %d band %d)",
		     freq, sync_channel, sync_band);
	skb = cfg80211_venकरोr_event_alloc(wl->hw->wiphy, शून्य, 20,
					  WLCORE_VENDOR_EVENT_SC_SYNC,
					  GFP_KERNEL);

	अगर (nla_put_u32(skb, WLCORE_VENDOR_ATTR_FREQ, freq)) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण
	cfg80211_venकरोr_event(skb, GFP_KERNEL);
	वापस 0;
पूर्ण

अटल पूर्णांक wlcore_smart_config_decode_event(काष्ठा wl1271 *wl,
					    u8 ssid_len, u8 *ssid,
					    u8 pwd_len, u8 *pwd)
अणु
	काष्ठा sk_buff *skb;

	wl1271_debug(DEBUG_EVENT, "SMART_CONFIG_DECODE_EVENT_ID");
	wl1271_dump_ascii(DEBUG_EVENT, "SSID:", ssid, ssid_len);

	skb = cfg80211_venकरोr_event_alloc(wl->hw->wiphy, शून्य,
					  ssid_len + pwd_len + 20,
					  WLCORE_VENDOR_EVENT_SC_DECODE,
					  GFP_KERNEL);

	अगर (nla_put(skb, WLCORE_VENDOR_ATTR_SSID, ssid_len, ssid) ||
	    nla_put(skb, WLCORE_VENDOR_ATTR_PSK, pwd_len, pwd)) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण
	cfg80211_venकरोr_event(skb, GFP_KERNEL);
	वापस 0;
पूर्ण

अटल व्योम wlcore_event_समय_sync(काष्ठा wl1271 *wl,
				   u16 tsf_high_msb, u16 tsf_high_lsb,
				   u16 tsf_low_msb, u16 tsf_low_lsb)
अणु
	u32 घड़ी_low;
	u32 घड़ी_high;

	घड़ी_high = (tsf_high_msb << 16) | tsf_high_lsb;
	घड़ी_low = (tsf_low_msb << 16) | tsf_low_lsb;

	wl1271_info("TIME_SYNC_EVENT_ID: clock_high %u, clock low %u",
		    घड़ी_high, घड़ी_low);
पूर्ण

पूर्णांक wl18xx_process_mailbox_events(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl18xx_event_mailbox *mbox = wl->mbox;
	u32 vector;

	vector = le32_to_cpu(mbox->events_vector);
	wl1271_debug(DEBUG_EVENT, "MBOX vector: 0x%x", vector);

	अगर (vector & SCAN_COMPLETE_EVENT_ID) अणु
		wl1271_debug(DEBUG_EVENT, "scan results: %d",
			     mbox->number_of_scan_results);

		अगर (wl->scan_wlvअगर)
			wl18xx_scan_completed(wl, wl->scan_wlvअगर);
	पूर्ण

	अगर (vector & TIME_SYNC_EVENT_ID)
		wlcore_event_समय_sync(wl,
			mbox->समय_sync_tsf_high_msb,
			mbox->समय_sync_tsf_high_lsb,
			mbox->समय_sync_tsf_low_msb,
			mbox->समय_sync_tsf_low_lsb);

	अगर (vector & RADAR_DETECTED_EVENT_ID) अणु
		wl1271_info("radar event: channel %d type %s",
			    mbox->radar_channel,
			    wl18xx_radar_type_decode(mbox->radar_type));

		अगर (!wl->radar_debug_mode)
			ieee80211_radar_detected(wl->hw);
	पूर्ण

	अगर (vector & PERIODIC_SCAN_REPORT_EVENT_ID) अणु
		wl1271_debug(DEBUG_EVENT,
			     "PERIODIC_SCAN_REPORT_EVENT (results %d)",
			     mbox->number_of_sched_scan_results);

		wlcore_scan_sched_scan_results(wl);
	पूर्ण

	अगर (vector & PERIODIC_SCAN_COMPLETE_EVENT_ID)
		wlcore_event_sched_scan_completed(wl, 1);

	अगर (vector & RSSI_SNR_TRIGGER_0_EVENT_ID)
		wlcore_event_rssi_trigger(wl, mbox->rssi_snr_trigger_metric);

	अगर (vector & BA_SESSION_RX_CONSTRAINT_EVENT_ID)
		wlcore_event_ba_rx_स्थिरraपूर्णांक(wl,
				le16_to_cpu(mbox->rx_ba_role_id_biपंचांगap),
				le16_to_cpu(mbox->rx_ba_allowed_biपंचांगap));

	अगर (vector & BSS_LOSS_EVENT_ID)
		wlcore_event_beacon_loss(wl,
					 le16_to_cpu(mbox->bss_loss_biपंचांगap));

	अगर (vector & CHANNEL_SWITCH_COMPLETE_EVENT_ID)
		wlcore_event_channel_चयन(wl,
			le16_to_cpu(mbox->channel_चयन_role_id_biपंचांगap),
			true);

	अगर (vector & DUMMY_PACKET_EVENT_ID)
		wlcore_event_dummy_packet(wl);

	/*
	 * "TX retries exceeded" has a dअगरferent meaning according to mode.
	 * In AP mode the offending station is disconnected.
	 */
	अगर (vector & MAX_TX_FAILURE_EVENT_ID)
		wlcore_event_max_tx_failure(wl,
				le16_to_cpu(mbox->tx_retry_exceeded_biपंचांगap));

	अगर (vector & INACTIVE_STA_EVENT_ID)
		wlcore_event_inactive_sta(wl,
				le16_to_cpu(mbox->inactive_sta_biपंचांगap));

	अगर (vector & REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID)
		wlcore_event_roc_complete(wl);

	अगर (vector & SMART_CONFIG_SYNC_EVENT_ID)
		wlcore_smart_config_sync_event(wl, mbox->sc_sync_channel,
					       mbox->sc_sync_band);

	अगर (vector & SMART_CONFIG_DECODE_EVENT_ID)
		wlcore_smart_config_decode_event(wl,
						 mbox->sc_ssid_len,
						 mbox->sc_ssid,
						 mbox->sc_pwd_len,
						 mbox->sc_pwd);
	अगर (vector & FW_LOGGER_INDICATION)
		wlcore_event_fw_logger(wl);

	अगर (vector & RX_BA_WIN_SIZE_CHANGE_EVENT_ID) अणु
		काष्ठा wl12xx_vअगर *wlvअगर;
		काष्ठा ieee80211_vअगर *vअगर;
		काष्ठा ieee80211_sta *sta;
		u8 link_id = mbox->rx_ba_link_id;
		u8 win_size = mbox->rx_ba_win_size;
		स्थिर u8 *addr;

		wlvअगर = wl->links[link_id].wlvअगर;
		vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

		/* Update RX aggregation winकरोw size and call
		 * MAC routine to stop active RX aggregations क्रम this link
		 */
		अगर (wlvअगर->bss_type != BSS_TYPE_AP_BSS)
			addr = vअगर->bss_conf.bssid;
		अन्यथा
			addr = wl->links[link_id].addr;

		sta = ieee80211_find_sta(vअगर, addr);
		अगर (sta) अणु
			sta->max_rx_aggregation_subframes = win_size;
			ieee80211_stop_rx_ba_session(vअगर,
						wl->links[link_id].ba_biपंचांगap,
						addr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
