<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2012 Texas Instruments. All rights reserved.
 */

#समावेश "event.h"
#समावेश "scan.h"
#समावेश "../wlcore/cmd.h"
#समावेश "../wlcore/debug.h"

पूर्णांक wl12xx_रुको_क्रम_event(काष्ठा wl1271 *wl, क्रमागत wlcore_रुको_event event,
			  bool *समयout)
अणु
	u32 local_event;

	चयन (event) अणु
	हाल WLCORE_EVENT_ROLE_STOP_COMPLETE:
		local_event = ROLE_STOP_COMPLETE_EVENT_ID;
		अवरोध;

	हाल WLCORE_EVENT_PEER_REMOVE_COMPLETE:
		local_event = PEER_REMOVE_COMPLETE_EVENT_ID;
		अवरोध;

	शेष:
		/* event not implemented */
		वापस 0;
	पूर्ण
	वापस wlcore_cmd_रुको_क्रम_event_or_समयout(wl, local_event, समयout);
पूर्ण

पूर्णांक wl12xx_process_mailbox_events(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_event_mailbox *mbox = wl->mbox;
	u32 vector;


	vector = le32_to_cpu(mbox->events_vector);
	vector &= ~(le32_to_cpu(mbox->events_mask));

	wl1271_debug(DEBUG_EVENT, "MBOX vector: 0x%x", vector);

	अगर (vector & SCAN_COMPLETE_EVENT_ID) अणु
		wl1271_debug(DEBUG_EVENT, "status: 0x%x",
			     mbox->scheduled_scan_status);

		अगर (wl->scan_wlvअगर)
			wl12xx_scan_completed(wl, wl->scan_wlvअगर);
	पूर्ण

	अगर (vector & PERIODIC_SCAN_REPORT_EVENT_ID) अणु
		wl1271_debug(DEBUG_EVENT,
			     "PERIODIC_SCAN_REPORT_EVENT (status 0x%0x)",
			     mbox->scheduled_scan_status);

		wlcore_scan_sched_scan_results(wl);
	पूर्ण

	अगर (vector & PERIODIC_SCAN_COMPLETE_EVENT_ID)
		wlcore_event_sched_scan_completed(wl,
						  mbox->scheduled_scan_status);
	अगर (vector & SOFT_GEMINI_SENSE_EVENT_ID)
		wlcore_event_soft_gemini_sense(wl,
					       mbox->soft_gemini_sense_info);

	अगर (vector & BSS_LOSE_EVENT_ID)
		wlcore_event_beacon_loss(wl, 0xff);

	अगर (vector & RSSI_SNR_TRIGGER_0_EVENT_ID)
		wlcore_event_rssi_trigger(wl, mbox->rssi_snr_trigger_metric);

	अगर (vector & BA_SESSION_RX_CONSTRAINT_EVENT_ID)
		wlcore_event_ba_rx_स्थिरraपूर्णांक(wl,
					      BIT(mbox->role_id),
					      mbox->rx_ba_allowed);

	अगर (vector & CHANNEL_SWITCH_COMPLETE_EVENT_ID)
		wlcore_event_channel_चयन(wl, 0xff,
					    mbox->channel_चयन_status);

	अगर (vector & DUMMY_PACKET_EVENT_ID)
		wlcore_event_dummy_packet(wl);

	/*
	 * "TX retries exceeded" has a dअगरferent meaning according to mode.
	 * In AP mode the offending station is disconnected.
	 */
	अगर (vector & MAX_TX_RETRY_EVENT_ID)
		wlcore_event_max_tx_failure(wl,
				le16_to_cpu(mbox->sta_tx_retry_exceeded));

	अगर (vector & INACTIVE_STA_EVENT_ID)
		wlcore_event_inactive_sta(wl,
					  le16_to_cpu(mbox->sta_aging_status));

	अगर (vector & REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID)
		wlcore_event_roc_complete(wl);

	वापस 0;
पूर्ण
