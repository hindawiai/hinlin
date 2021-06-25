<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/cmd.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/acx.h"
#समावेश "../wlcore/tx.h"

#समावेश "wl18xx.h"
#समावेश "tx.h"

अटल
व्योम wl18xx_get_last_tx_rate(काष्ठा wl1271 *wl, काष्ठा ieee80211_vअगर *vअगर,
			     u8 band, काष्ठा ieee80211_tx_rate *rate, u8 hlid)
अणु
	u8 fw_rate = wl->links[hlid].fw_rate_idx;

	अगर (fw_rate > CONF_HW_RATE_INDEX_MAX) अणु
		wl1271_error("last Tx rate invalid: %d", fw_rate);
		rate->idx = 0;
		rate->flags = 0;
		वापस;
	पूर्ण

	अगर (fw_rate <= CONF_HW_RATE_INDEX_54MBPS) अणु
		rate->idx = fw_rate;
		अगर (band == NL80211_BAND_5GHZ)
			rate->idx -= CONF_HW_RATE_INDEX_6MBPS;
		rate->flags = 0;
	पूर्ण अन्यथा अणु
		rate->flags = IEEE80211_TX_RC_MCS;
		rate->idx = fw_rate - CONF_HW_RATE_INDEX_MCS0;

		/* SGI modअगरier is counted as a separate rate */
		अगर (fw_rate >= CONF_HW_RATE_INDEX_MCS7_SGI)
			(rate->idx)--;
		अगर (fw_rate == CONF_HW_RATE_INDEX_MCS15_SGI)
			(rate->idx)--;

		/* this also covers the 40Mhz SGI हाल (= MCS15) */
		अगर (fw_rate == CONF_HW_RATE_INDEX_MCS7_SGI ||
		    fw_rate == CONF_HW_RATE_INDEX_MCS15_SGI)
			rate->flags |= IEEE80211_TX_RC_SHORT_GI;

		अगर (fw_rate > CONF_HW_RATE_INDEX_MCS7_SGI && vअगर) अणु
			काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
			अगर (wlvअगर->channel_type == NL80211_CHAN_HT40MINUS ||
			    wlvअगर->channel_type == NL80211_CHAN_HT40PLUS) अणु
				/* adjusपंचांगent needed क्रम range 0-7 */
				rate->idx -= 8;
				rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wl18xx_tx_complete_packet(काष्ठा wl1271 *wl, u8 tx_stat_byte)
अणु
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *skb;
	पूर्णांक id = tx_stat_byte & WL18XX_TX_STATUS_DESC_ID_MASK;
	bool tx_success;
	काष्ठा wl1271_tx_hw_descr *tx_desc;

	/* check क्रम id legality */
	अगर (unlikely(id >= wl->num_tx_desc || wl->tx_frames[id] == शून्य)) अणु
		wl1271_warning("illegal id in tx completion: %d", id);
		वापस;
	पूर्ण

	/* a zero bit indicates Tx success */
	tx_success = !(tx_stat_byte & BIT(WL18XX_TX_STATUS_STAT_BIT_IDX));

	skb = wl->tx_frames[id];
	info = IEEE80211_SKB_CB(skb);
	tx_desc = (काष्ठा wl1271_tx_hw_descr *)skb->data;

	अगर (wl12xx_is_dummy_packet(wl, skb)) अणु
		wl1271_मुक्त_tx_id(wl, id);
		वापस;
	पूर्ण

	/* update the TX status info */
	अगर (tx_success && !(info->flags & IEEE80211_TX_CTL_NO_ACK))
		info->flags |= IEEE80211_TX_STAT_ACK;
	/*
	 * first pass info->control.vअगर जबतक it's valid, and then fill out
	 * the info->status काष्ठाures
	 */
	wl18xx_get_last_tx_rate(wl, info->control.vअगर,
				info->band,
				&info->status.rates[0],
				tx_desc->hlid);

	info->status.rates[0].count = 1; /* no data about retries */
	info->status.ack_संकेत = -1;

	अगर (!tx_success)
		wl->stats.retry_count++;

	/*
	 * TODO: update sequence number क्रम encryption? seems to be
	 * unsupported क्रम now. needed क्रम recovery with encryption.
	 */

	/* हटाओ निजी header from packet */
	skb_pull(skb, माप(काष्ठा wl1271_tx_hw_descr));

	/* हटाओ TKIP header space अगर present */
	अगर ((wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE) &&
	    info->control.hw_key &&
	    info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
		पूर्णांक hdrlen = ieee80211_get_hdrlen_from_skb(skb);
		स_हटाओ(skb->data + WL1271_EXTRA_SPACE_TKIP, skb->data, hdrlen);
		skb_pull(skb, WL1271_EXTRA_SPACE_TKIP);
	पूर्ण

	wl1271_debug(DEBUG_TX, "tx status id %u skb 0x%p success %d",
		     id, skb, tx_success);

	/* वापस the packet to the stack */
	skb_queue_tail(&wl->deferred_tx_queue, skb);
	queue_work(wl->मुक्तzable_wq, &wl->netstack_work);
	wl1271_मुक्त_tx_id(wl, id);
पूर्ण

व्योम wl18xx_tx_immediate_complete(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl18xx_fw_status_priv *status_priv =
		(काष्ठा wl18xx_fw_status_priv *)wl->fw_status->priv;
	काष्ठा wl18xx_priv *priv = wl->priv;
	u8 i, hlid;

	/* nothing to करो here */
	अगर (priv->last_fw_rls_idx == status_priv->fw_release_idx)
		वापस;

	/* update rates per link */
	hlid = wl->fw_status->counters.hlid;

	अगर (hlid < WLCORE_MAX_LINKS) अणु
		wl->links[hlid].fw_rate_idx =
				wl->fw_status->counters.tx_last_rate;
		wl->links[hlid].fw_rate_mbps =
				wl->fw_status->counters.tx_last_rate_mbps;
	पूर्ण

	/* मुक्तd Tx descriptors */
	wl1271_debug(DEBUG_TX, "last released desc = %d, current idx = %d",
		     priv->last_fw_rls_idx, status_priv->fw_release_idx);

	अगर (status_priv->fw_release_idx >= WL18XX_FW_MAX_TX_STATUS_DESC) अणु
		wl1271_error("invalid desc release index %d",
			     status_priv->fw_release_idx);
		WARN_ON(1);
		वापस;
	पूर्ण

	क्रम (i = priv->last_fw_rls_idx;
	     i != status_priv->fw_release_idx;
	     i = (i + 1) % WL18XX_FW_MAX_TX_STATUS_DESC) अणु
		wl18xx_tx_complete_packet(wl,
			status_priv->released_tx_desc[i]);

		wl->tx_results_count++;
	पूर्ण

	priv->last_fw_rls_idx = status_priv->fw_release_idx;
पूर्ण
