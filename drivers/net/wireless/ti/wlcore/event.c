<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "io.h"
#समावेश "event.h"
#समावेश "ps.h"
#समावेश "scan.h"
#समावेश "wl12xx_80211.h"
#समावेश "hw_ops.h"

#घोषणा WL18XX_LOGGER_SDIO_BUFF_MAX	(0x1020)
#घोषणा WL18XX_DATA_RAM_BASE_ADDRESS	(0x20000000)
#घोषणा WL18XX_LOGGER_SDIO_BUFF_ADDR	(0x40159c)
#घोषणा WL18XX_LOGGER_BUFF_OFFSET	(माप(काष्ठा fw_logger_inक्रमmation))
#घोषणा WL18XX_LOGGER_READ_POINT_OFFSET		(12)

पूर्णांक wlcore_event_fw_logger(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;
	काष्ठा fw_logger_inक्रमmation fw_log;
	u8  *buffer;
	u32 पूर्णांकernal_fw_addrbase = WL18XX_DATA_RAM_BASE_ADDRESS;
	u32 addr = WL18XX_LOGGER_SDIO_BUFF_ADDR;
	u32 end_buff_addr = WL18XX_LOGGER_SDIO_BUFF_ADDR +
				WL18XX_LOGGER_BUFF_OFFSET;
	u32 available_len;
	u32 actual_len;
	u32 clear_addr;
	माप_प्रकार len;
	u32 start_loc;

	buffer = kzalloc(WL18XX_LOGGER_SDIO_BUFF_MAX, GFP_KERNEL);
	अगर (!buffer) अणु
		wl1271_error("Fail to allocate fw logger memory");
		fw_log.actual_buff_size = cpu_to_le32(0);
		जाओ out;
	पूर्ण

	ret = wlcore_पढ़ो(wl, addr, buffer, WL18XX_LOGGER_SDIO_BUFF_MAX,
			  false);
	अगर (ret < 0) अणु
		wl1271_error("Fail to read logger buffer, error_id = %d",
			     ret);
		fw_log.actual_buff_size = cpu_to_le32(0);
		जाओ मुक्त_out;
	पूर्ण

	स_नकल(&fw_log, buffer, माप(fw_log));

	अगर (le32_to_cpu(fw_log.actual_buff_size) == 0)
		जाओ मुक्त_out;

	actual_len = le32_to_cpu(fw_log.actual_buff_size);
	start_loc = (le32_to_cpu(fw_log.buff_पढ़ो_ptr) -
			पूर्णांकernal_fw_addrbase) - addr;
	end_buff_addr += le32_to_cpu(fw_log.max_buff_size);
	available_len = end_buff_addr -
			(le32_to_cpu(fw_log.buff_पढ़ो_ptr) -
				 पूर्णांकernal_fw_addrbase);
	actual_len = min(actual_len, available_len);
	len = actual_len;

	wl12xx_copy_fwlog(wl, &buffer[start_loc], len);
	clear_addr = addr + start_loc + le32_to_cpu(fw_log.actual_buff_size) +
			पूर्णांकernal_fw_addrbase;

	len = le32_to_cpu(fw_log.actual_buff_size) - len;
	अगर (len) अणु
		wl12xx_copy_fwlog(wl,
				  &buffer[WL18XX_LOGGER_BUFF_OFFSET],
				  len);
		clear_addr = addr + WL18XX_LOGGER_BUFF_OFFSET + len +
				पूर्णांकernal_fw_addrbase;
	पूर्ण

	/* द्विगुन check that clear address and ग_लिखो poपूर्णांकer are the same */
	अगर (clear_addr != le32_to_cpu(fw_log.buff_ग_लिखो_ptr)) अणु
		wl1271_error("Calculate of clear addr Clear = %x, write = %x",
			     clear_addr, le32_to_cpu(fw_log.buff_ग_लिखो_ptr));
	पूर्ण

	/* indicate FW about Clear buffer */
	ret = wlcore_ग_लिखो32(wl, addr + WL18XX_LOGGER_READ_POINT_OFFSET,
			     fw_log.buff_ग_लिखो_ptr);
मुक्त_out:
	kमुक्त(buffer);
out:
	वापस le32_to_cpu(fw_log.actual_buff_size);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_fw_logger);

व्योम wlcore_event_rssi_trigger(काष्ठा wl1271 *wl, s8 *metric_arr)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा ieee80211_vअगर *vअगर;
	क्रमागत nl80211_cqm_rssi_threshold_event event;
	s8 metric = metric_arr[0];

	wl1271_debug(DEBUG_EVENT, "RSSI trigger metric: %d", metric);

	/* TODO: check actual multi-role support */
	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		अगर (metric <= wlvअगर->rssi_thold)
			event = NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW;
		अन्यथा
			event = NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH;

		vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
		अगर (event != wlvअगर->last_rssi_event)
			ieee80211_cqm_rssi_notअगरy(vअगर, event, metric,
						  GFP_KERNEL);
		wlvअगर->last_rssi_event = event;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_rssi_trigger);

अटल व्योम wl1271_stop_ba_event(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

	अगर (wlvअगर->bss_type != BSS_TYPE_AP_BSS) अणु
		u8 hlid = wlvअगर->sta.hlid;
		अगर (!wl->links[hlid].ba_biपंचांगap)
			वापस;
		ieee80211_stop_rx_ba_session(vअगर, wl->links[hlid].ba_biपंचांगap,
					     vअगर->bss_conf.bssid);
	पूर्ण अन्यथा अणु
		u8 hlid;
		काष्ठा wl1271_link *lnk;
		क्रम_each_set_bit(hlid, wlvअगर->ap.sta_hlid_map,
				 wl->num_links) अणु
			lnk = &wl->links[hlid];
			अगर (!lnk->ba_biपंचांगap)
				जारी;

			ieee80211_stop_rx_ba_session(vअगर,
						     lnk->ba_biपंचांगap,
						     lnk->addr);
		पूर्ण
	पूर्ण
पूर्ण

व्योम wlcore_event_soft_gemini_sense(काष्ठा wl1271 *wl, u8 enable)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;

	अगर (enable) अणु
		set_bit(WL1271_FLAG_SOFT_GEMINI, &wl->flags);
	पूर्ण अन्यथा अणु
		clear_bit(WL1271_FLAG_SOFT_GEMINI, &wl->flags);
		wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
			wl1271_recalc_rx_streaming(wl, wlvअगर);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_soft_gemini_sense);

व्योम wlcore_event_sched_scan_completed(काष्ठा wl1271 *wl,
				       u8 status)
अणु
	wl1271_debug(DEBUG_EVENT, "PERIODIC_SCAN_COMPLETE_EVENT (status 0x%0x)",
		     status);

	अगर (wl->sched_vअगर) अणु
		ieee80211_sched_scan_stopped(wl->hw);
		wl->sched_vअगर = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_sched_scan_completed);

व्योम wlcore_event_ba_rx_स्थिरraपूर्णांक(काष्ठा wl1271 *wl,
				   अचिन्हित दीर्घ roles_biपंचांगap,
				   अचिन्हित दीर्घ allowed_biपंचांगap)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;

	wl1271_debug(DEBUG_EVENT, "%s: roles=0x%lx allowed=0x%lx",
		     __func__, roles_biपंचांगap, allowed_biपंचांगap);

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		अगर (wlvअगर->role_id == WL12XX_INVALID_ROLE_ID ||
		    !test_bit(wlvअगर->role_id , &roles_biपंचांगap))
			जारी;

		wlvअगर->ba_allowed = !!test_bit(wlvअगर->role_id,
					       &allowed_biपंचांगap);
		अगर (!wlvअगर->ba_allowed)
			wl1271_stop_ba_event(wl, wlvअगर);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_ba_rx_स्थिरraपूर्णांक);

व्योम wlcore_event_channel_चयन(काष्ठा wl1271 *wl,
				 अचिन्हित दीर्घ roles_biपंचांगap,
				 bool success)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा ieee80211_vअगर *vअगर;

	wl1271_debug(DEBUG_EVENT, "%s: roles=0x%lx success=%d",
		     __func__, roles_biपंचांगap, success);

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		अगर (wlvअगर->role_id == WL12XX_INVALID_ROLE_ID ||
		    !test_bit(wlvअगर->role_id , &roles_biपंचांगap))
			जारी;

		अगर (!test_and_clear_bit(WLVIF_FLAG_CS_PROGRESS,
					&wlvअगर->flags))
			जारी;

		vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

		अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS) अणु
			ieee80211_chचयन_करोne(vअगर, success);
			cancel_delayed_work(&wlvअगर->channel_चयन_work);
		पूर्ण अन्यथा अणु
			set_bit(WLVIF_FLAG_BEACON_DISABLED, &wlvअगर->flags);
			ieee80211_csa_finish(vअगर);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_channel_चयन);

व्योम wlcore_event_dummy_packet(काष्ठा wl1271 *wl)
अणु
	अगर (wl->plt) अणु
		wl1271_info("Got DUMMY_PACKET event in PLT mode.  FW bug, ignoring.");
		वापस;
	पूर्ण

	wl1271_debug(DEBUG_EVENT, "DUMMY_PACKET_ID_EVENT_ID");
	wl1271_tx_dummy_packet(wl);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_dummy_packet);

अटल व्योम wlcore_disconnect_sta(काष्ठा wl1271 *wl, अचिन्हित दीर्घ sta_biपंचांगap)
अणु
	u32 num_packets = wl->conf.tx.max_tx_retries;
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_sta *sta;
	स्थिर u8 *addr;
	पूर्णांक h;

	क्रम_each_set_bit(h, &sta_biपंचांगap, wl->num_links) अणु
		bool found = false;
		/* find the ap vअगर connected to this sta */
		wl12xx_क्रम_each_wlvअगर_ap(wl, wlvअगर) अणु
			अगर (!test_bit(h, wlvअगर->ap.sta_hlid_map))
				जारी;
			found = true;
			अवरोध;
		पूर्ण
		अगर (!found)
			जारी;

		vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
		addr = wl->links[h].addr;

		rcu_पढ़ो_lock();
		sta = ieee80211_find_sta(vअगर, addr);
		अगर (sta) अणु
			wl1271_debug(DEBUG_EVENT, "remove sta %d", h);
			ieee80211_report_low_ack(sta, num_packets);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

व्योम wlcore_event_max_tx_failure(काष्ठा wl1271 *wl, अचिन्हित दीर्घ sta_biपंचांगap)
अणु
	wl1271_debug(DEBUG_EVENT, "MAX_TX_FAILURE_EVENT_ID");
	wlcore_disconnect_sta(wl, sta_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_max_tx_failure);

व्योम wlcore_event_inactive_sta(काष्ठा wl1271 *wl, अचिन्हित दीर्घ sta_biपंचांगap)
अणु
	wl1271_debug(DEBUG_EVENT, "INACTIVE_STA_EVENT_ID");
	wlcore_disconnect_sta(wl, sta_biपंचांगap);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_inactive_sta);

व्योम wlcore_event_roc_complete(काष्ठा wl1271 *wl)
अणु
	wl1271_debug(DEBUG_EVENT, "REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID");
	अगर (wl->roc_vअगर)
		ieee80211_पढ़ोy_on_channel(wl->hw);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_roc_complete);

व्योम wlcore_event_beacon_loss(काष्ठा wl1271 *wl, अचिन्हित दीर्घ roles_biपंचांगap)
अणु
	/*
	 * We are HW_MONITOR device. On beacon loss - queue
	 * connection loss work. Cancel it on REGAINED event.
	 */
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा ieee80211_vअगर *vअगर;
	पूर्णांक delay = wl->conf.conn.synch_fail_thold *
				wl->conf.conn.bss_lose_समयout;

	wl1271_info("Beacon loss detected. roles:0x%lx", roles_biपंचांगap);

	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		अगर (wlvअगर->role_id == WL12XX_INVALID_ROLE_ID ||
		    !test_bit(wlvअगर->role_id , &roles_biपंचांगap))
			जारी;

		vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);

		/* करोn't attempt roaming in हाल of p2p */
		अगर (wlvअगर->p2p) अणु
			ieee80211_connection_loss(vअगर);
			जारी;
		पूर्ण

		/*
		 * अगर the work is alपढ़ोy queued, it should take place.
		 * We करोn't want to delay the connection loss
		 * indication any more.
		 */
		ieee80211_queue_delayed_work(wl->hw,
					     &wlvअगर->connection_loss_work,
					     msecs_to_jअगरfies(delay));

		ieee80211_cqm_beacon_loss_notअगरy(vअगर, GFP_KERNEL);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_event_beacon_loss);

पूर्णांक wl1271_event_unmask(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	wl1271_debug(DEBUG_EVENT, "unmasking event_mask 0x%x", wl->event_mask);
	ret = wl1271_acx_event_mbox_mask(wl, ~(wl->event_mask));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1271_event_handle(काष्ठा wl1271 *wl, u8 mbox_num)
अणु
	पूर्णांक ret;

	wl1271_debug(DEBUG_EVENT, "EVENT on mbox %d", mbox_num);

	अगर (mbox_num > 1)
		वापस -EINVAL;

	/* first we पढ़ो the mbox descriptor */
	ret = wlcore_पढ़ो(wl, wl->mbox_ptr[mbox_num], wl->mbox,
			  wl->mbox_size, false);
	अगर (ret < 0)
		वापस ret;

	/* process the descriptor */
	ret = wl->ops->process_mailbox_events(wl);
	अगर (ret < 0)
		वापस ret;

	/*
	 * TODO: we just need this because one bit is in a dअगरferent
	 * place.  Is there any better way?
	 */
	ret = wl->ops->ack_event(wl);

	वापस ret;
पूर्ण
