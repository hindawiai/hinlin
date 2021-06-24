<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश "wl1251.h"
#समावेश "reg.h"
#समावेश "io.h"
#समावेश "event.h"
#समावेश "ps.h"

अटल पूर्णांक wl1251_event_scan_complete(काष्ठा wl1251 *wl,
				      काष्ठा event_mailbox *mbox)
अणु
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_EVENT, "status: 0x%x, channels: %d",
		     mbox->scheduled_scan_status,
		     mbox->scheduled_scan_channels);

	अगर (wl->scanning) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = false,
		पूर्ण;

		ieee80211_scan_completed(wl->hw, &info);
		wl1251_debug(DEBUG_MAC80211, "mac80211 hw scan completed");
		wl->scanning = false;
		अगर (wl->hw->conf.flags & IEEE80211_CONF_IDLE)
			ret = wl1251_ps_set_mode(wl, STATION_IDLE);
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा WL1251_PSM_ENTRY_RETRIES  3
अटल पूर्णांक wl1251_event_ps_report(काष्ठा wl1251 *wl,
				  काष्ठा event_mailbox *mbox)
अणु
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_EVENT, "ps status: %x", mbox->ps_status);

	चयन (mbox->ps_status) अणु
	हाल EVENT_ENTER_POWER_SAVE_FAIL:
		wl1251_debug(DEBUG_PSM, "PSM entry failed");

		अगर (wl->station_mode != STATION_POWER_SAVE_MODE) अणु
			/* reमुख्य in active mode */
			wl->psm_entry_retry = 0;
			अवरोध;
		पूर्ण

		अगर (wl->psm_entry_retry < WL1251_PSM_ENTRY_RETRIES) अणु
			wl->psm_entry_retry++;
			ret = wl1251_ps_set_mode(wl, STATION_POWER_SAVE_MODE);
		पूर्ण अन्यथा अणु
			wl1251_error("Power save entry failed, giving up");
			wl->psm_entry_retry = 0;
		पूर्ण
		अवरोध;
	हाल EVENT_ENTER_POWER_SAVE_SUCCESS:
	हाल EVENT_EXIT_POWER_SAVE_FAIL:
	हाल EVENT_EXIT_POWER_SAVE_SUCCESS:
	शेष:
		wl->psm_entry_retry = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम wl1251_event_mbox_dump(काष्ठा event_mailbox *mbox)
अणु
	wl1251_debug(DEBUG_EVENT, "MBOX DUMP:");
	wl1251_debug(DEBUG_EVENT, "\tvector: 0x%x", mbox->events_vector);
	wl1251_debug(DEBUG_EVENT, "\tmask: 0x%x", mbox->events_mask);
पूर्ण

अटल पूर्णांक wl1251_event_process(काष्ठा wl1251 *wl, काष्ठा event_mailbox *mbox)
अणु
	पूर्णांक ret;
	u32 vector;

	wl1251_event_mbox_dump(mbox);

	vector = mbox->events_vector & ~(mbox->events_mask);
	wl1251_debug(DEBUG_EVENT, "vector: 0x%x", vector);

	अगर (vector & SCAN_COMPLETE_EVENT_ID) अणु
		ret = wl1251_event_scan_complete(wl, mbox);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (vector & BSS_LOSE_EVENT_ID) अणु
		wl1251_debug(DEBUG_EVENT, "BSS_LOSE_EVENT");

		अगर (wl->psm_requested &&
		    wl->station_mode != STATION_ACTIVE_MODE) अणु
			ret = wl1251_ps_set_mode(wl, STATION_ACTIVE_MODE);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (vector & PS_REPORT_EVENT_ID) अणु
		wl1251_debug(DEBUG_EVENT, "PS_REPORT_EVENT");
		ret = wl1251_event_ps_report(wl, mbox);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (vector & SYNCHRONIZATION_TIMEOUT_EVENT_ID) अणु
		wl1251_debug(DEBUG_EVENT, "SYNCHRONIZATION_TIMEOUT_EVENT");

		/* indicate to the stack, that beacons have been lost */
		अगर (wl->vअगर && wl->vअगर->type == NL80211_IFTYPE_STATION)
			ieee80211_beacon_loss(wl->vअगर);
	पूर्ण

	अगर (vector & REGAINED_BSS_EVENT_ID) अणु
		अगर (wl->psm_requested) अणु
			ret = wl1251_ps_set_mode(wl, STATION_POWER_SAVE_MODE);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (wl->vअगर && wl->rssi_thold) अणु
		अगर (vector & ROAMING_TRIGGER_LOW_RSSI_EVENT_ID) अणु
			wl1251_debug(DEBUG_EVENT,
				     "ROAMING_TRIGGER_LOW_RSSI_EVENT");
			ieee80211_cqm_rssi_notअगरy(wl->vअगर,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
				0, GFP_KERNEL);
		पूर्ण

		अगर (vector & ROAMING_TRIGGER_REGAINED_RSSI_EVENT_ID) अणु
			wl1251_debug(DEBUG_EVENT,
				     "ROAMING_TRIGGER_REGAINED_RSSI_EVENT");
			ieee80211_cqm_rssi_notअगरy(wl->vअगर,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
				0, GFP_KERNEL);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Poll the mailbox event field until any of the bits in the mask is set or a
 * समयout occurs (WL1251_EVENT_TIMEOUT in msecs)
 */
पूर्णांक wl1251_event_रुको(काष्ठा wl1251 *wl, u32 mask, पूर्णांक समयout_ms)
अणु
	u32 events_vector, event;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms);

	करो अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;

		msleep(1);

		/* पढ़ो from both event fields */
		wl1251_mem_पढ़ो(wl, wl->mbox_ptr[0], &events_vector,
				माप(events_vector));
		event = events_vector & mask;
		wl1251_mem_पढ़ो(wl, wl->mbox_ptr[1], &events_vector,
				माप(events_vector));
		event |= events_vector & mask;
	पूर्ण जबतक (!event);

	वापस 0;
पूर्ण

पूर्णांक wl1251_event_unmask(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_event_mbox_mask(wl, ~(wl->event_mask));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

व्योम wl1251_event_mbox_config(काष्ठा wl1251 *wl)
अणु
	wl->mbox_ptr[0] = wl1251_reg_पढ़ो32(wl, REG_EVENT_MAILBOX_PTR);
	wl->mbox_ptr[1] = wl->mbox_ptr[0] + माप(काष्ठा event_mailbox);

	wl1251_debug(DEBUG_EVENT, "MBOX ptrs: 0x%x 0x%x",
		     wl->mbox_ptr[0], wl->mbox_ptr[1]);
पूर्ण

पूर्णांक wl1251_event_handle(काष्ठा wl1251 *wl, u8 mbox_num)
अणु
	काष्ठा event_mailbox mbox;
	पूर्णांक ret;

	wl1251_debug(DEBUG_EVENT, "EVENT on mbox %d", mbox_num);

	अगर (mbox_num > 1)
		वापस -EINVAL;

	/* first we पढ़ो the mbox descriptor */
	wl1251_mem_पढ़ो(wl, wl->mbox_ptr[mbox_num], &mbox,
			    माप(काष्ठा event_mailbox));

	/* process the descriptor */
	ret = wl1251_event_process(wl, &mbox);
	अगर (ret < 0)
		वापस ret;

	/* then we let the firmware know it can go on...*/
	wl1251_reg_ग_लिखो32(wl, ACX_REG_INTERRUPT_TRIG, INTR_TRIG_EVENT_ACK);

	वापस 0;
पूर्ण
