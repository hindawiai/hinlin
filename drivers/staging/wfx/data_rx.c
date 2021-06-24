<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Datapath implementation.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>

#समावेश "data_rx.h"
#समावेश "wfx.h"
#समावेश "bh.h"
#समावेश "sta.h"

अटल व्योम wfx_rx_handle_ba(काष्ठा wfx_vअगर *wvअगर, काष्ठा ieee80211_mgmt *mgmt)
अणु
	पूर्णांक params, tid;

	अगर (wfx_api_older_than(wvअगर->wdev, 3, 6))
		वापस;

	चयन (mgmt->u.action.u.addba_req.action_code) अणु
	हाल WLAN_ACTION_ADDBA_REQ:
		params = le16_to_cpu(mgmt->u.action.u.addba_req.capab);
		tid = (params & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2;
		ieee80211_start_rx_ba_session_offl(wvअगर->vअगर, mgmt->sa, tid);
		अवरोध;
	हाल WLAN_ACTION_DELBA:
		params = le16_to_cpu(mgmt->u.action.u.delba.params);
		tid = (params &  IEEE80211_DELBA_PARAM_TID_MASK) >> 12;
		ieee80211_stop_rx_ba_session_offl(wvअगर->vअगर, mgmt->sa, tid);
		अवरोध;
	पूर्ण
पूर्ण

व्योम wfx_rx_cb(काष्ठा wfx_vअगर *wvअगर,
	       स्थिर काष्ठा hअगर_ind_rx *arg, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *hdr = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *frame = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)skb->data;

	स_रखो(hdr, 0, माप(*hdr));

	अगर (arg->status == HIF_STATUS_RX_FAIL_MIC)
		hdr->flag |= RX_FLAG_MMIC_ERROR | RX_FLAG_IV_STRIPPED;
	अन्यथा अगर (arg->status)
		जाओ drop;

	अगर (skb->len < माप(काष्ठा ieee80211_pspoll)) अणु
		dev_warn(wvअगर->wdev->dev, "malformed SDU received\n");
		जाओ drop;
	पूर्ण

	hdr->band = NL80211_BAND_2GHZ;
	hdr->freq = ieee80211_channel_to_frequency(arg->channel_number,
						   hdr->band);

	अगर (arg->rxed_rate >= 14) अणु
		hdr->encoding = RX_ENC_HT;
		hdr->rate_idx = arg->rxed_rate - 14;
	पूर्ण अन्यथा अगर (arg->rxed_rate >= 4) अणु
		hdr->rate_idx = arg->rxed_rate - 2;
	पूर्ण अन्यथा अणु
		hdr->rate_idx = arg->rxed_rate;
	पूर्ण

	अगर (!arg->rcpi_rssi) अणु
		hdr->flag |= RX_FLAG_NO_SIGNAL_VAL;
		dev_info(wvअगर->wdev->dev, "received frame without RSSI data\n");
	पूर्ण
	hdr->संकेत = arg->rcpi_rssi / 2 - 110;
	hdr->antenna = 0;

	अगर (arg->encryp)
		hdr->flag |= RX_FLAG_DECRYPTED;

	// Block ack negotiation is offloaded by the firmware. However,
	// re-ordering must be करोne by the mac80211.
	अगर (ieee80211_is_action(frame->frame_control) &&
	    mgmt->u.action.category == WLAN_CATEGORY_BACK &&
	    skb->len > IEEE80211_MIN_ACTION_SIZE) अणु
		wfx_rx_handle_ba(wvअगर, mgmt);
		जाओ drop;
	पूर्ण

	ieee80211_rx_irqsafe(wvअगर->wdev->hw, skb);
	वापस;

drop:
	dev_kमुक्त_skb(skb);
पूर्ण
