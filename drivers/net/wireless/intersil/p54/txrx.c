<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common code क्रम mac80211 Prism54 drivers
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2007-2009, Christian Lamparter <chunkeey@web.de>
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 *
 * Based on:
 * - the islsm (sofपंचांगac prism54) driver, which is:
 *   Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 * - stlc45xx driver
 *   Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 */

#समावेश <linux/export.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <net/mac80211.h>

#समावेश "p54.h"
#समावेश "lmac.h"

#अगर_घोषित P54_MM_DEBUG
अटल व्योम p54_dump_tx_queue(काष्ठा p54_common *priv)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा p54_tx_info *range;
	काष्ठा sk_buff *skb;
	काष्ठा p54_hdr *hdr;
	अचिन्हित पूर्णांक i = 0;
	u32 prev_addr;
	u32 largest_hole = 0, मुक्त;

	spin_lock_irqsave(&priv->tx_queue.lock, flags);
	wiphy_debug(priv->hw->wiphy, "/ --- tx queue dump (%d entries) ---\n",
		    skb_queue_len(&priv->tx_queue));

	prev_addr = priv->rx_start;
	skb_queue_walk(&priv->tx_queue, skb) अणु
		info = IEEE80211_SKB_CB(skb);
		range = (व्योम *) info->rate_driver_data;
		hdr = (व्योम *) skb->data;

		मुक्त = range->start_addr - prev_addr;
		wiphy_debug(priv->hw->wiphy,
			    "| [%02d] => [skb:%p skb_len:0x%04x "
			    "hdr:{flags:%02x len:%04x req_id:%04x type:%02x} "
			    "mem:{start:%04x end:%04x, free:%d}]\n",
			    i++, skb, skb->len,
			    le16_to_cpu(hdr->flags), le16_to_cpu(hdr->len),
			    le32_to_cpu(hdr->req_id), le16_to_cpu(hdr->type),
			    range->start_addr, range->end_addr, मुक्त);

		prev_addr = range->end_addr;
		largest_hole = max(largest_hole, मुक्त);
	पूर्ण
	मुक्त = priv->rx_end - prev_addr;
	largest_hole = max(largest_hole, मुक्त);
	wiphy_debug(priv->hw->wiphy,
		    "\\ --- [free: %d], largest free block: %d ---\n",
		    मुक्त, largest_hole);
	spin_unlock_irqrestore(&priv->tx_queue.lock, flags);
पूर्ण
#पूर्ण_अगर /* P54_MM_DEBUG */

/*
 * So, the firmware is somewhat stupid and करोesn't know what places in its
 * memory incoming data should go to. By poking around in the firmware, we
 * can find some unused memory to upload our packets to. However, data that we
 * want the card to TX needs to stay पूर्णांकact until the card has told us that
 * it is करोne with it. This function finds empty places we can upload to and
 * marks allocated areas as reserved अगर necessary. p54_find_and_unlink_skb or
 * p54_मुक्त_skb मुक्तs allocated areas.
 */
अटल पूर्णांक p54_assign_address(काष्ठा p54_common *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *entry, *target_skb = शून्य;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा p54_tx_info *range;
	काष्ठा p54_hdr *data = (व्योम *) skb->data;
	अचिन्हित दीर्घ flags;
	u32 last_addr = priv->rx_start;
	u32 target_addr = priv->rx_start;
	u16 len = priv->headroom + skb->len + priv->tailroom + 3;

	info = IEEE80211_SKB_CB(skb);
	range = (व्योम *) info->rate_driver_data;
	len = (range->extra_len + len) & ~0x3;

	spin_lock_irqsave(&priv->tx_queue.lock, flags);
	अगर (unlikely(skb_queue_len(&priv->tx_queue) == 32)) अणु
		/*
		 * The tx_queue is now really full.
		 *
		 * TODO: check अगर the device has crashed and reset it.
		 */
		spin_unlock_irqrestore(&priv->tx_queue.lock, flags);
		वापस -EBUSY;
	पूर्ण

	skb_queue_walk(&priv->tx_queue, entry) अणु
		u32 hole_size;
		info = IEEE80211_SKB_CB(entry);
		range = (व्योम *) info->rate_driver_data;
		hole_size = range->start_addr - last_addr;

		अगर (!target_skb && hole_size >= len) अणु
			target_skb = entry->prev;
			hole_size -= len;
			target_addr = last_addr;
			अवरोध;
		पूर्ण
		last_addr = range->end_addr;
	पूर्ण
	अगर (unlikely(!target_skb)) अणु
		अगर (priv->rx_end - last_addr >= len) अणु
			target_skb = skb_peek_tail(&priv->tx_queue);
			अगर (target_skb) अणु
				info = IEEE80211_SKB_CB(target_skb);
				range = (व्योम *)info->rate_driver_data;
				target_addr = range->end_addr;
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&priv->tx_queue.lock, flags);
			वापस -ENOSPC;
		पूर्ण
	पूर्ण

	info = IEEE80211_SKB_CB(skb);
	range = (व्योम *) info->rate_driver_data;
	range->start_addr = target_addr;
	range->end_addr = target_addr + len;
	data->req_id = cpu_to_le32(target_addr + priv->headroom);
	अगर (IS_DATA_FRAME(skb) &&
	    unlikely(GET_HW_QUEUE(skb) == P54_QUEUE_BEACON))
		priv->beacon_req_id = data->req_id;

	अगर (target_skb)
		__skb_queue_after(&priv->tx_queue, target_skb, skb);
	अन्यथा
		__skb_queue_head(&priv->tx_queue, skb);
	spin_unlock_irqrestore(&priv->tx_queue.lock, flags);
	वापस 0;
पूर्ण

अटल व्योम p54_tx_pending(काष्ठा p54_common *priv)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = skb_dequeue(&priv->tx_pending);
	अगर (unlikely(!skb))
		वापस ;

	ret = p54_assign_address(priv, skb);
	अगर (unlikely(ret))
		skb_queue_head(&priv->tx_pending, skb);
	अन्यथा
		priv->tx(priv->hw, skb);
पूर्ण

अटल व्योम p54_wake_queues(काष्ठा p54_common *priv)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	अगर (unlikely(priv->mode == NL80211_IFTYPE_UNSPECIFIED))
		वापस ;

	p54_tx_pending(priv);

	spin_lock_irqsave(&priv->tx_stats_lock, flags);
	क्रम (i = 0; i < priv->hw->queues; i++) अणु
		अगर (priv->tx_stats[i + P54_QUEUE_DATA].len <
		    priv->tx_stats[i + P54_QUEUE_DATA].limit)
			ieee80211_wake_queue(priv->hw, i);
	पूर्ण
	spin_unlock_irqrestore(&priv->tx_stats_lock, flags);
पूर्ण

अटल पूर्णांक p54_tx_qos_accounting_alloc(काष्ठा p54_common *priv,
				       काष्ठा sk_buff *skb,
				       स्थिर u16 p54_queue)
अणु
	काष्ठा p54_tx_queue_stats *queue;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(p54_queue >= P54_QUEUE_NUM))
		वापस -EINVAL;

	queue = &priv->tx_stats[p54_queue];

	spin_lock_irqsave(&priv->tx_stats_lock, flags);
	अगर (unlikely(queue->len >= queue->limit && IS_QOS_QUEUE(p54_queue))) अणु
		spin_unlock_irqrestore(&priv->tx_stats_lock, flags);
		वापस -ENOSPC;
	पूर्ण

	queue->len++;
	queue->count++;

	अगर (unlikely(queue->len == queue->limit && IS_QOS_QUEUE(p54_queue))) अणु
		u16 ac_queue = p54_queue - P54_QUEUE_DATA;
		ieee80211_stop_queue(priv->hw, ac_queue);
	पूर्ण

	spin_unlock_irqrestore(&priv->tx_stats_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम p54_tx_qos_accounting_मुक्त(काष्ठा p54_common *priv,
				       काष्ठा sk_buff *skb)
अणु
	अगर (IS_DATA_FRAME(skb)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&priv->tx_stats_lock, flags);
		priv->tx_stats[GET_HW_QUEUE(skb)].len--;
		spin_unlock_irqrestore(&priv->tx_stats_lock, flags);

		अगर (unlikely(GET_HW_QUEUE(skb) == P54_QUEUE_BEACON)) अणु
			अगर (priv->beacon_req_id == GET_REQ_ID(skb)) अणु
				/* this is the  active beacon set anymore */
				priv->beacon_req_id = 0;
			पूर्ण
			complete(&priv->beacon_comp);
		पूर्ण
	पूर्ण
	p54_wake_queues(priv);
पूर्ण

व्योम p54_मुक्त_skb(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_common *priv = dev->priv;
	अगर (unlikely(!skb))
		वापस ;

	skb_unlink(skb, &priv->tx_queue);
	p54_tx_qos_accounting_मुक्त(priv, skb);
	ieee80211_मुक्त_txskb(dev, skb);
पूर्ण
EXPORT_SYMBOL_GPL(p54_मुक्त_skb);

अटल काष्ठा sk_buff *p54_find_and_unlink_skb(काष्ठा p54_common *priv,
					       स्थिर __le32 req_id)
अणु
	काष्ठा sk_buff *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->tx_queue.lock, flags);
	skb_queue_walk(&priv->tx_queue, entry) अणु
		काष्ठा p54_hdr *hdr = (काष्ठा p54_hdr *) entry->data;

		अगर (hdr->req_id == req_id) अणु
			__skb_unlink(entry, &priv->tx_queue);
			spin_unlock_irqrestore(&priv->tx_queue.lock, flags);
			p54_tx_qos_accounting_मुक्त(priv, entry);
			वापस entry;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->tx_queue.lock, flags);
	वापस शून्य;
पूर्ण

व्योम p54_tx(काष्ठा p54_common *priv, काष्ठा sk_buff *skb)
अणु
	skb_queue_tail(&priv->tx_pending, skb);
	p54_tx_pending(priv);
पूर्ण

अटल पूर्णांक p54_rssi_to_dbm(काष्ठा p54_common *priv, पूर्णांक rssi)
अणु
	अगर (priv->rxhw != 5) अणु
		वापस ((rssi * priv->cur_rssi->mul) / 64 +
			 priv->cur_rssi->add) / 4;
	पूर्ण अन्यथा अणु
		/*
		 * TODO: find the correct क्रमmula
		 */
		वापस rssi / 2 - 110;
	पूर्ण
पूर्ण

/*
 * Even अगर the firmware is capable of dealing with incoming traffic,
 * जबतक करोzing, we have to prepared in हाल mac80211 uses PS-POLL
 * to retrieve outstanding frames from our AP.
 * (see comment in net/mac80211/mlme.c @ line 1993)
 */
अटल व्योम p54_pspoll_workaround(काष्ठा p54_common *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *) skb->data;
	काष्ठा ieee80211_tim_ie *tim_ie;
	u8 *tim;
	u8 tim_len;
	bool new_psm;

	/* only beacons have a TIM IE */
	अगर (!ieee80211_is_beacon(hdr->frame_control))
		वापस;

	अगर (!priv->aid)
		वापस;

	/* only consider beacons from the associated BSSID */
	अगर (!ether_addr_equal_64bits(hdr->addr3, priv->bssid))
		वापस;

	tim = p54_find_ie(skb, WLAN_EID_TIM);
	अगर (!tim)
		वापस;

	tim_len = tim[1];
	tim_ie = (काष्ठा ieee80211_tim_ie *) &tim[2];

	new_psm = ieee80211_check_tim(tim_ie, tim_len, priv->aid);
	अगर (new_psm != priv->घातersave_override) अणु
		priv->घातersave_override = new_psm;
		p54_set_ps(priv);
	पूर्ण
पूर्ण

अटल पूर्णांक p54_rx_data(काष्ठा p54_common *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_rx_data *hdr = (काष्ठा p54_rx_data *) skb->data;
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	u16 freq = le16_to_cpu(hdr->freq);
	माप_प्रकार header_len = माप(*hdr);
	u32 tsf32;
	__le16 fc;
	u8 rate = hdr->rate & 0xf;

	/*
	 * If the device is in a unspecअगरied state we have to
	 * ignore all data frames. Else we could end up with a
	 * nasty crash.
	 */
	अगर (unlikely(priv->mode == NL80211_IFTYPE_UNSPECIFIED))
		वापस 0;

	अगर (!(hdr->flags & cpu_to_le16(P54_HDR_FLAG_DATA_IN_FCS_GOOD)))
		वापस 0;

	अगर (hdr->decrypt_status == P54_DECRYPT_OK)
		rx_status->flag |= RX_FLAG_DECRYPTED;
	अगर ((hdr->decrypt_status == P54_DECRYPT_FAIL_MICHAEL) ||
	    (hdr->decrypt_status == P54_DECRYPT_FAIL_TKIP))
		rx_status->flag |= RX_FLAG_MMIC_ERROR;

	rx_status->संकेत = p54_rssi_to_dbm(priv, hdr->rssi);
	अगर (hdr->rate & 0x10)
		rx_status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
	अगर (priv->hw->conf.chandef.chan->band == NL80211_BAND_5GHZ)
		rx_status->rate_idx = (rate < 4) ? 0 : rate - 4;
	अन्यथा
		rx_status->rate_idx = rate;

	rx_status->freq = freq;
	rx_status->band =  priv->hw->conf.chandef.chan->band;
	rx_status->antenna = hdr->antenna;

	tsf32 = le32_to_cpu(hdr->tsf32);
	अगर (tsf32 < priv->tsf_low32)
		priv->tsf_high32++;
	rx_status->maस_समय = ((u64)priv->tsf_high32) << 32 | tsf32;
	priv->tsf_low32 = tsf32;

	/* LMAC API Page 10/29 - s_lm_data_in - घड़ी
	 * "usec accurate बारtamp of hardware घड़ी
	 * at end of frame (beक्रमe OFDM SIFS खातापूर्ण padding"
	 */
	rx_status->flag |= RX_FLAG_MACTIME_END;

	अगर (hdr->flags & cpu_to_le16(P54_HDR_FLAG_DATA_ALIGN))
		header_len += hdr->align[0];

	skb_pull(skb, header_len);
	skb_trim(skb, le16_to_cpu(hdr->len));

	fc = ((काष्ठा ieee80211_hdr *)skb->data)->frame_control;
	अगर (ieee80211_is_probe_resp(fc) || ieee80211_is_beacon(fc))
		rx_status->bootसमय_ns = kसमय_get_bootसमय_ns();

	अगर (unlikely(priv->hw->conf.flags & IEEE80211_CONF_PS))
		p54_pspoll_workaround(priv, skb);

	ieee80211_rx_irqsafe(priv->hw, skb);

	ieee80211_queue_delayed_work(priv->hw, &priv->work,
			   msecs_to_jअगरfies(P54_STATISTICS_UPDATE));

	वापस -1;
पूर्ण

अटल व्योम p54_rx_frame_sent(काष्ठा p54_common *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_hdr *hdr = (काष्ठा p54_hdr *) skb->data;
	काष्ठा p54_frame_sent *payload = (काष्ठा p54_frame_sent *) hdr->data;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा p54_hdr *entry_hdr;
	काष्ठा p54_tx_data *entry_data;
	काष्ठा sk_buff *entry;
	अचिन्हित पूर्णांक pad = 0, frame_len;
	पूर्णांक count, idx;

	entry = p54_find_and_unlink_skb(priv, hdr->req_id);
	अगर (unlikely(!entry))
		वापस ;

	frame_len = entry->len;
	info = IEEE80211_SKB_CB(entry);
	entry_hdr = (काष्ठा p54_hdr *) entry->data;
	entry_data = (काष्ठा p54_tx_data *) entry_hdr->data;
	priv->stats.करोt11ACKFailureCount += payload->tries - 1;

	/*
	 * Frames in P54_QUEUE_FWSCAN and P54_QUEUE_BEACON are
	 * generated by the driver. Thereक्रमe tx_status is bogus
	 * and we करोn't want to confuse the mac80211 stack.
	 */
	अगर (unlikely(entry_data->hw_queue < P54_QUEUE_FWSCAN)) अणु
		dev_kमुक्त_skb_any(entry);
		वापस ;
	पूर्ण

	/*
	 * Clear manually, ieee80211_tx_info_clear_status would
	 * clear the counts too and we need them.
	 */
	स_रखो(&info->status.ack_संकेत, 0,
	       माप(काष्ठा ieee80211_tx_info) -
	       दुरत्व(काष्ठा ieee80211_tx_info, status.ack_संकेत));
	BUILD_BUG_ON(दुरत्व(काष्ठा ieee80211_tx_info,
			      status.ack_संकेत) != 20);

	अगर (entry_hdr->flags & cpu_to_le16(P54_HDR_FLAG_DATA_ALIGN))
		pad = entry_data->align[0];

	/* walk through the rates array and adjust the counts */
	count = payload->tries;
	क्रम (idx = 0; idx < 4; idx++) अणु
		अगर (count >= info->status.rates[idx].count) अणु
			count -= info->status.rates[idx].count;
		पूर्ण अन्यथा अगर (count > 0) अणु
			info->status.rates[idx].count = count;
			count = 0;
		पूर्ण अन्यथा अणु
			info->status.rates[idx].idx = -1;
			info->status.rates[idx].count = 0;
		पूर्ण
	पूर्ण

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK) &&
	     !(payload->status & P54_TX_FAILED))
		info->flags |= IEEE80211_TX_STAT_ACK;
	अगर (payload->status & P54_TX_PSM_CANCELLED)
		info->flags |= IEEE80211_TX_STAT_TX_FILTERED;
	info->status.ack_संकेत = p54_rssi_to_dbm(priv,
						  (पूर्णांक)payload->ack_rssi);

	/* Unकरो all changes to the frame. */
	चयन (entry_data->key_type) अणु
	हाल P54_CRYPTO_TKIPMICHAEL: अणु
		u8 *iv = (u8 *)(entry_data->align + pad +
				entry_data->crypt_offset);

		/* Restore the original TKIP IV. */
		iv[2] = iv[0];
		iv[0] = iv[1];
		iv[1] = (iv[0] | 0x20) & 0x7f;	/* WEPSeed - 8.3.2.2 */

		frame_len -= 12; /* हटाओ TKIP_MMIC + TKIP_ICV */
		अवरोध;
		पूर्ण
	हाल P54_CRYPTO_AESCCMP:
		frame_len -= 8; /* हटाओ CCMP_MIC */
		अवरोध;
	हाल P54_CRYPTO_WEP:
		frame_len -= 4; /* हटाओ WEP_ICV */
		अवरोध;
	पूर्ण

	skb_trim(entry, frame_len);
	skb_pull(entry, माप(*hdr) + pad + माप(*entry_data));
	ieee80211_tx_status_irqsafe(priv->hw, entry);
पूर्ण

अटल व्योम p54_rx_eeprom_पढ़ोback(काष्ठा p54_common *priv,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_hdr *hdr = (काष्ठा p54_hdr *) skb->data;
	काष्ठा p54_eeprom_lm86 *eeprom = (काष्ठा p54_eeprom_lm86 *) hdr->data;
	काष्ठा sk_buff *पंचांगp;

	अगर (!priv->eeprom)
		वापस ;

	अगर (priv->fw_var >= 0x509) अणु
		स_नकल(priv->eeprom, eeprom->v2.data,
		       le16_to_cpu(eeprom->v2.len));
	पूर्ण अन्यथा अणु
		स_नकल(priv->eeprom, eeprom->v1.data,
		       le16_to_cpu(eeprom->v1.len));
	पूर्ण

	priv->eeprom = शून्य;
	पंचांगp = p54_find_and_unlink_skb(priv, hdr->req_id);
	dev_kमुक्त_skb_any(पंचांगp);
	complete(&priv->eeprom_comp);
पूर्ण

अटल व्योम p54_rx_stats(काष्ठा p54_common *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_hdr *hdr = (काष्ठा p54_hdr *) skb->data;
	काष्ठा p54_statistics *stats = (काष्ठा p54_statistics *) hdr->data;
	काष्ठा sk_buff *पंचांगp;
	काष्ठा ieee80211_channel *chan;
	अचिन्हित पूर्णांक i, rssi, tx, cca, dसमय, dtotal, dcca, dtx, drssi, unit;
	u32 tsf32;

	अगर (unlikely(priv->mode == NL80211_IFTYPE_UNSPECIFIED))
		वापस ;

	tsf32 = le32_to_cpu(stats->tsf32);
	अगर (tsf32 < priv->tsf_low32)
		priv->tsf_high32++;
	priv->tsf_low32 = tsf32;

	priv->stats.करोt11RTSFailureCount = le32_to_cpu(stats->rts_fail);
	priv->stats.करोt11RTSSuccessCount = le32_to_cpu(stats->rts_success);
	priv->stats.करोt11FCSErrorCount = le32_to_cpu(stats->rx_bad_fcs);

	priv->noise = p54_rssi_to_dbm(priv, le32_to_cpu(stats->noise));

	/*
	 * STSW450X LMAC API page 26 - 3.8 Statistics
	 * "The exact measurement period can be derived from the
	 * बारtamp member".
	 */
	dसमय = tsf32 - priv->survey_raw.बारtamp;

	/*
	 * STSW450X LMAC API page 26 - 3.8.1 Noise histogram
	 * The LMAC samples RSSI, CCA and transmit state at regular
	 * periods (typically 8 बार per 1k [as in 1024] usec).
	 */
	cca = le32_to_cpu(stats->sample_cca);
	tx = le32_to_cpu(stats->sample_tx);
	rssi = 0;
	क्रम (i = 0; i < ARRAY_SIZE(stats->sample_noise); i++)
		rssi += le32_to_cpu(stats->sample_noise[i]);

	dcca = cca - priv->survey_raw.cached_cca;
	drssi = rssi - priv->survey_raw.cached_rssi;
	dtx = tx - priv->survey_raw.cached_tx;
	dtotal = dcca + drssi + dtx;

	/*
	 * update statistics when more than a second is over since the
	 * last call, or when a update is badly needed.
	 */
	अगर (dtotal && (priv->update_stats || dसमय >= USEC_PER_SEC) &&
	    dसमय >= dtotal) अणु
		priv->survey_raw.बारtamp = tsf32;
		priv->update_stats = false;
		unit = dसमय / dtotal;

		अगर (dcca) अणु
			priv->survey_raw.cca += dcca * unit;
			priv->survey_raw.cached_cca = cca;
		पूर्ण
		अगर (dtx) अणु
			priv->survey_raw.tx += dtx * unit;
			priv->survey_raw.cached_tx = tx;
		पूर्ण
		अगर (drssi) अणु
			priv->survey_raw.rssi += drssi * unit;
			priv->survey_raw.cached_rssi = rssi;
		पूर्ण

		/* 1024 usec / 8 बार = 128 usec / समय */
		अगर (!(priv->phy_ps || priv->phy_idle))
			priv->survey_raw.active += dtotal * unit;
		अन्यथा
			priv->survey_raw.active += (dcca + dtx) * unit;
	पूर्ण

	chan = priv->curchan;
	अगर (chan) अणु
		काष्ठा survey_info *survey = &priv->survey[chan->hw_value];
		survey->noise = clamp(priv->noise, -128, 127);
		survey->समय = priv->survey_raw.active;
		survey->समय_प्रकारx = priv->survey_raw.tx;
		survey->समय_busy = priv->survey_raw.tx +
			priv->survey_raw.cca;
		करो_भाग(survey->समय, 1024);
		करो_भाग(survey->समय_प्रकारx, 1024);
		करो_भाग(survey->समय_busy, 1024);
	पूर्ण

	पंचांगp = p54_find_and_unlink_skb(priv, hdr->req_id);
	dev_kमुक्त_skb_any(पंचांगp);
	complete(&priv->stat_comp);
पूर्ण

अटल व्योम p54_rx_trap(काष्ठा p54_common *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_hdr *hdr = (काष्ठा p54_hdr *) skb->data;
	काष्ठा p54_trap *trap = (काष्ठा p54_trap *) hdr->data;
	u16 event = le16_to_cpu(trap->event);
	u16 freq = le16_to_cpu(trap->frequency);

	चयन (event) अणु
	हाल P54_TRAP_BEACON_TX:
		अवरोध;
	हाल P54_TRAP_RADAR:
		wiphy_info(priv->hw->wiphy, "radar (freq:%d MHz)\n", freq);
		अवरोध;
	हाल P54_TRAP_NO_BEACON:
		अगर (priv->vअगर)
			ieee80211_beacon_loss(priv->vअगर);
		अवरोध;
	हाल P54_TRAP_SCAN:
		अवरोध;
	हाल P54_TRAP_TBTT:
		अवरोध;
	हाल P54_TRAP_TIMER:
		अवरोध;
	हाल P54_TRAP_FAA_RADIO_OFF:
		wiphy_rfसमाप्त_set_hw_state(priv->hw->wiphy, true);
		अवरोध;
	हाल P54_TRAP_FAA_RADIO_ON:
		wiphy_rfसमाप्त_set_hw_state(priv->hw->wiphy, false);
		अवरोध;
	शेष:
		wiphy_info(priv->hw->wiphy, "received event:%x freq:%d\n",
			   event, freq);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक p54_rx_control(काष्ठा p54_common *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_hdr *hdr = (काष्ठा p54_hdr *) skb->data;

	चयन (le16_to_cpu(hdr->type)) अणु
	हाल P54_CONTROL_TYPE_TXDONE:
		p54_rx_frame_sent(priv, skb);
		अवरोध;
	हाल P54_CONTROL_TYPE_TRAP:
		p54_rx_trap(priv, skb);
		अवरोध;
	हाल P54_CONTROL_TYPE_BBP:
		अवरोध;
	हाल P54_CONTROL_TYPE_STAT_READBACK:
		p54_rx_stats(priv, skb);
		अवरोध;
	हाल P54_CONTROL_TYPE_EEPROM_READBACK:
		p54_rx_eeprom_पढ़ोback(priv, skb);
		अवरोध;
	शेष:
		wiphy_debug(priv->hw->wiphy,
			    "not handling 0x%02x type control frame\n",
			    le16_to_cpu(hdr->type));
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* वापसs zero अगर skb can be reused */
पूर्णांक p54_rx(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_common *priv = dev->priv;
	u16 type = le16_to_cpu(*((__le16 *)skb->data));

	अगर (type & P54_HDR_FLAG_CONTROL)
		वापस p54_rx_control(priv, skb);
	अन्यथा
		वापस p54_rx_data(priv, skb);
पूर्ण
EXPORT_SYMBOL_GPL(p54_rx);

अटल व्योम p54_tx_80211_header(काष्ठा p54_common *priv, काष्ठा sk_buff *skb,
				काष्ठा ieee80211_tx_info *info,
				काष्ठा ieee80211_sta *sta,
				u8 *queue, u32 *extra_len, u16 *flags, u16 *aid,
				bool *burst_possible)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		*burst_possible = true;
	अन्यथा
		*burst_possible = false;

	अगर (!(info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ))
		*flags |= P54_HDR_FLAG_DATA_OUT_SEQNR;

	अगर (info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER)
		*flags |= P54_HDR_FLAG_DATA_OUT_NOCANCEL;

	अगर (info->flags & IEEE80211_TX_CTL_CLEAR_PS_FILT)
		*flags |= P54_HDR_FLAG_DATA_OUT_NOCANCEL;

	*queue = skb_get_queue_mapping(skb) + P54_QUEUE_DATA;

	चयन (priv->mode) अणु
	हाल NL80211_IFTYPE_MONITOR:
		/*
		 * We have to set P54_HDR_FLAG_DATA_OUT_PROMISC क्रम
		 * every frame in promiscuous/monitor mode.
		 * see STSW45x0C LMAC API - page 12.
		 */
		*aid = 0;
		*flags |= P54_HDR_FLAG_DATA_OUT_PROMISC;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		*aid = 1;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) अणु
			*aid = 0;
			*queue = P54_QUEUE_CAB;
			वापस;
		पूर्ण

		अगर (unlikely(ieee80211_is_mgmt(hdr->frame_control))) अणु
			अगर (ieee80211_is_probe_resp(hdr->frame_control)) अणु
				*aid = 0;
				*flags |= P54_HDR_FLAG_DATA_OUT_TIMESTAMP |
					  P54_HDR_FLAG_DATA_OUT_NOCANCEL;
				वापस;
			पूर्ण अन्यथा अगर (ieee80211_is_beacon(hdr->frame_control)) अणु
				*aid = 0;

				अगर (info->flags & IEEE80211_TX_CTL_INJECTED) अणु
					/*
					 * Injecting beacons on top of a AP is
					 * not a good idea... nevertheless,
					 * it should be करोable.
					 */

					वापस;
				पूर्ण

				*flags |= P54_HDR_FLAG_DATA_OUT_TIMESTAMP;
				*queue = P54_QUEUE_BEACON;
				*extra_len = IEEE80211_MAX_TIM_LEN;
				वापस;
			पूर्ण
		पूर्ण

		अगर (sta)
			*aid = sta->aid;
		अवरोध;
	पूर्ण
पूर्ण

अटल u8 p54_convert_algo(u32 cipher)
अणु
	चयन (cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस P54_CRYPTO_WEP;
	हाल WLAN_CIPHER_SUITE_TKIP:
		वापस P54_CRYPTO_TKIPMICHAEL;
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस P54_CRYPTO_AESCCMP;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

व्योम p54_tx_80211(काष्ठा ieee80211_hw *dev,
		  काष्ठा ieee80211_tx_control *control,
		  काष्ठा sk_buff *skb)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा p54_tx_info *p54info;
	काष्ठा p54_hdr *hdr;
	काष्ठा p54_tx_data *txhdr;
	अचिन्हित पूर्णांक padding, len, extra_len = 0;
	पूर्णांक i, j, ridx;
	u16 hdr_flags = 0, aid = 0;
	u8 rate, queue = 0, crypt_offset = 0;
	u8 cts_rate = 0x20;
	u8 rc_flags;
	u8 calculated_tries[4];
	u8 nrates = 0, nreमुख्यing = 8;
	bool burst_allowed = false;

	p54_tx_80211_header(priv, skb, info, control->sta, &queue, &extra_len,
			    &hdr_flags, &aid, &burst_allowed);

	अगर (p54_tx_qos_accounting_alloc(priv, skb, queue)) अणु
		ieee80211_मुक्त_txskb(dev, skb);
		वापस;
	पूर्ण

	padding = (अचिन्हित दीर्घ)(skb->data - (माप(*hdr) + माप(*txhdr))) & 3;
	len = skb->len;

	अगर (info->control.hw_key) अणु
		crypt_offset = ieee80211_get_hdrlen_from_skb(skb);
		अगर (info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
			u8 *iv = (u8 *)(skb->data + crypt_offset);
			/*
			 * The firmware excepts that the IV has to have
			 * this special क्रमmat
			 */
			iv[1] = iv[0];
			iv[0] = iv[2];
			iv[2] = 0;
		पूर्ण
	पूर्ण

	txhdr = skb_push(skb, माप(*txhdr) + padding);
	hdr = skb_push(skb, माप(*hdr));

	अगर (padding)
		hdr_flags |= P54_HDR_FLAG_DATA_ALIGN;
	hdr->type = cpu_to_le16(aid);
	hdr->rts_tries = info->control.rates[0].count;

	/*
	 * we रेजिस्टर the rates in perfect order, and
	 * RTS/CTS won't happen on 5 GHz
	 */
	cts_rate = info->control.rts_cts_rate_idx;

	स_रखो(&txhdr->rateset, 0, माप(txhdr->rateset));

	/* see how many rates got used */
	क्रम (i = 0; i < dev->max_rates; i++) अणु
		अगर (info->control.rates[i].idx < 0)
			अवरोध;
		nrates++;
	पूर्ण

	/* limit tries to 8/nrates per rate */
	क्रम (i = 0; i < nrates; i++) अणु
		/*
		 * The magic expression here is equivalent to 8/nrates क्रम
		 * all values that matter, but aव्योमs भागision and jumps.
		 * Note that nrates can only take the values 1 through 4.
		 */
		calculated_tries[i] = min_t(पूर्णांक, ((15 >> nrates) | 1) + 1,
						 info->control.rates[i].count);
		nreमुख्यing -= calculated_tries[i];
	पूर्ण

	/* अगर there are tries left, distribute from back to front */
	क्रम (i = nrates - 1; nreमुख्यing > 0 && i >= 0; i--) अणु
		पूर्णांक पंचांगp = info->control.rates[i].count - calculated_tries[i];

		अगर (पंचांगp <= 0)
			जारी;
		/* RC requested more tries at this rate */

		पंचांगp = min_t(पूर्णांक, पंचांगp, nreमुख्यing);
		calculated_tries[i] += पंचांगp;
		nreमुख्यing -= पंचांगp;
	पूर्ण

	ridx = 0;
	क्रम (i = 0; i < nrates && ridx < 8; i++) अणु
		/* we रेजिस्टर the rates in perfect order */
		rate = info->control.rates[i].idx;
		अगर (info->band == NL80211_BAND_5GHZ)
			rate += 4;

		/* store the count we actually calculated क्रम TX status */
		info->control.rates[i].count = calculated_tries[i];

		rc_flags = info->control.rates[i].flags;
		अगर (rc_flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE) अणु
			rate |= 0x10;
			cts_rate |= 0x10;
		पूर्ण
		अगर (rc_flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
			burst_allowed = false;
			rate |= 0x40;
		पूर्ण अन्यथा अगर (rc_flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
			rate |= 0x20;
			burst_allowed = false;
		पूर्ण
		क्रम (j = 0; j < calculated_tries[i] && ridx < 8; j++) अणु
			txhdr->rateset[ridx] = rate;
			ridx++;
		पूर्ण
	पूर्ण

	अगर (burst_allowed)
		hdr_flags |= P54_HDR_FLAG_DATA_OUT_BURST;

	/* TODO: enable bursting */
	hdr->flags = cpu_to_le16(hdr_flags);
	hdr->tries = ridx;
	txhdr->rts_rate_idx = 0;
	अगर (info->control.hw_key) अणु
		txhdr->key_type = p54_convert_algo(info->control.hw_key->cipher);
		txhdr->key_len = min((u8)16, info->control.hw_key->keylen);
		स_नकल(txhdr->key, info->control.hw_key->key, txhdr->key_len);
		अगर (info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
			/* reserve space क्रम the MIC key */
			len += 8;
			skb_put_data(skb,
				     &(info->control.hw_key->key[NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY]),
				     8);
		पूर्ण
		/* reserve some space क्रम ICV */
		len += info->control.hw_key->icv_len;
		skb_put_zero(skb, info->control.hw_key->icv_len);
	पूर्ण अन्यथा अणु
		txhdr->key_type = 0;
		txhdr->key_len = 0;
	पूर्ण
	txhdr->crypt_offset = crypt_offset;
	txhdr->hw_queue = queue;
	txhdr->backlog = priv->tx_stats[queue].len - 1;
	स_रखो(txhdr->durations, 0, माप(txhdr->durations));
	txhdr->tx_antenna = 2 & priv->tx_भागersity_mask;
	अगर (priv->rxhw == 5) अणु
		txhdr->दीर्घbow.cts_rate = cts_rate;
		txhdr->दीर्घbow.output_घातer = cpu_to_le16(priv->output_घातer);
	पूर्ण अन्यथा अणु
		txhdr->normal.output_घातer = priv->output_घातer;
		txhdr->normal.cts_rate = cts_rate;
	पूर्ण
	अगर (padding)
		txhdr->align[0] = padding;

	hdr->len = cpu_to_le16(len);
	/* modअगरies skb->cb and with it info, so must be last! */
	p54info = (व्योम *) info->rate_driver_data;
	p54info->extra_len = extra_len;

	p54_tx(priv, skb);
पूर्ण
