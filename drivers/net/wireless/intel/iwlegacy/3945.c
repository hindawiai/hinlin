<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2011 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/mac80211.h>

#समावेश "common.h"
#समावेश "3945.h"

/* Send led command */
अटल पूर्णांक
il3945_send_led_cmd(काष्ठा il_priv *il, काष्ठा il_led_cmd *led_cmd)
अणु
	काष्ठा il_host_cmd cmd = अणु
		.id = C_LEDS,
		.len = माप(काष्ठा il_led_cmd),
		.data = led_cmd,
		.flags = CMD_ASYNC,
		.callback = शून्य,
	पूर्ण;

	वापस il_send_cmd(il, &cmd);
पूर्ण

#घोषणा IL_DECLARE_RATE_INFO(r, ip, in, rp, rn, pp, np)    \
	[RATE_##r##M_IDX] = अणु RATE_##r##M_PLCP,   \
				    RATE_##r##M_IEEE,   \
				    RATE_##ip##M_IDX, \
				    RATE_##in##M_IDX, \
				    RATE_##rp##M_IDX, \
				    RATE_##rn##M_IDX, \
				    RATE_##pp##M_IDX, \
				    RATE_##np##M_IDX, \
				    RATE_##r##M_IDX_TBL, \
				    RATE_##ip##M_IDX_TBL पूर्ण

/*
 * Parameter order:
 *   rate, prev rate, next rate, prev tgg rate, next tgg rate
 *
 * If there isn't a valid next or previous rate then INV is used which
 * maps to RATE_INVALID
 *
 */
स्थिर काष्ठा il3945_rate_info il3945_rates[RATE_COUNT_3945] = अणु
	IL_DECLARE_RATE_INFO(1, INV, 2, INV, 2, INV, 2),	/*  1mbps */
	IL_DECLARE_RATE_INFO(2, 1, 5, 1, 5, 1, 5),	/*  2mbps */
	IL_DECLARE_RATE_INFO(5, 2, 6, 2, 11, 2, 11),	/*5.5mbps */
	IL_DECLARE_RATE_INFO(11, 9, 12, 5, 12, 5, 18),	/* 11mbps */
	IL_DECLARE_RATE_INFO(6, 5, 9, 5, 11, 5, 11),	/*  6mbps */
	IL_DECLARE_RATE_INFO(9, 6, 11, 5, 11, 5, 11),	/*  9mbps */
	IL_DECLARE_RATE_INFO(12, 11, 18, 11, 18, 11, 18),	/* 12mbps */
	IL_DECLARE_RATE_INFO(18, 12, 24, 12, 24, 11, 24),	/* 18mbps */
	IL_DECLARE_RATE_INFO(24, 18, 36, 18, 36, 18, 36),	/* 24mbps */
	IL_DECLARE_RATE_INFO(36, 24, 48, 24, 48, 24, 48),	/* 36mbps */
	IL_DECLARE_RATE_INFO(48, 36, 54, 36, 54, 36, 54),	/* 48mbps */
	IL_DECLARE_RATE_INFO(54, 48, INV, 48, INV, 48, INV),	/* 54mbps */
पूर्ण;

अटल अंतरभूत u8
il3945_get_prev_ieee_rate(u8 rate_idx)
अणु
	u8 rate = il3945_rates[rate_idx].prev_ieee;

	अगर (rate == RATE_INVALID)
		rate = rate_idx;
	वापस rate;
पूर्ण

/* 1 = enable the il3945_disable_events() function */
#घोषणा IL_EVT_DISABLE (0)
#घोषणा IL_EVT_DISABLE_SIZE (1532/32)

/*
 * il3945_disable_events - Disable selected events in uCode event log
 *
 * Disable an event by writing "1"s पूर्णांकo "disable"
 *   biपंचांगap in SRAM.  Bit position corresponds to Event # (id/type).
 *   Default values of 0 enable uCode events to be logged.
 * Use क्रम only special debugging.  This function is just a placeholder as-is,
 *   you'll need to provide the special bits! ...
 *   ... and set IL_EVT_DISABLE to 1. */
व्योम
il3945_disable_events(काष्ठा il_priv *il)
अणु
	पूर्णांक i;
	u32 base;		/* SRAM address of event log header */
	u32 disable_ptr;	/* SRAM address of event-disable biपंचांगap array */
	u32 array_size;		/* # of u32 entries in array */
	अटल स्थिर u32 evt_disable[IL_EVT_DISABLE_SIZE] = अणु
		0x00000000,	/*   31 -    0  Event id numbers */
		0x00000000,	/*   63 -   32 */
		0x00000000,	/*   95 -   64 */
		0x00000000,	/*  127 -   96 */
		0x00000000,	/*  159 -  128 */
		0x00000000,	/*  191 -  160 */
		0x00000000,	/*  223 -  192 */
		0x00000000,	/*  255 -  224 */
		0x00000000,	/*  287 -  256 */
		0x00000000,	/*  319 -  288 */
		0x00000000,	/*  351 -  320 */
		0x00000000,	/*  383 -  352 */
		0x00000000,	/*  415 -  384 */
		0x00000000,	/*  447 -  416 */
		0x00000000,	/*  479 -  448 */
		0x00000000,	/*  511 -  480 */
		0x00000000,	/*  543 -  512 */
		0x00000000,	/*  575 -  544 */
		0x00000000,	/*  607 -  576 */
		0x00000000,	/*  639 -  608 */
		0x00000000,	/*  671 -  640 */
		0x00000000,	/*  703 -  672 */
		0x00000000,	/*  735 -  704 */
		0x00000000,	/*  767 -  736 */
		0x00000000,	/*  799 -  768 */
		0x00000000,	/*  831 -  800 */
		0x00000000,	/*  863 -  832 */
		0x00000000,	/*  895 -  864 */
		0x00000000,	/*  927 -  896 */
		0x00000000,	/*  959 -  928 */
		0x00000000,	/*  991 -  960 */
		0x00000000,	/* 1023 -  992 */
		0x00000000,	/* 1055 - 1024 */
		0x00000000,	/* 1087 - 1056 */
		0x00000000,	/* 1119 - 1088 */
		0x00000000,	/* 1151 - 1120 */
		0x00000000,	/* 1183 - 1152 */
		0x00000000,	/* 1215 - 1184 */
		0x00000000,	/* 1247 - 1216 */
		0x00000000,	/* 1279 - 1248 */
		0x00000000,	/* 1311 - 1280 */
		0x00000000,	/* 1343 - 1312 */
		0x00000000,	/* 1375 - 1344 */
		0x00000000,	/* 1407 - 1376 */
		0x00000000,	/* 1439 - 1408 */
		0x00000000,	/* 1471 - 1440 */
		0x00000000,	/* 1503 - 1472 */
	पूर्ण;

	base = le32_to_cpu(il->card_alive.log_event_table_ptr);
	अगर (!il3945_hw_valid_rtc_data_addr(base)) अणु
		IL_ERR("Invalid event log pointer 0x%08X\n", base);
		वापस;
	पूर्ण

	disable_ptr = il_पढ़ो_targ_mem(il, base + (4 * माप(u32)));
	array_size = il_पढ़ो_targ_mem(il, base + (5 * माप(u32)));

	अगर (IL_EVT_DISABLE && array_size == IL_EVT_DISABLE_SIZE) अणु
		D_INFO("Disabling selected uCode log events at 0x%x\n",
		       disable_ptr);
		क्रम (i = 0; i < IL_EVT_DISABLE_SIZE; i++)
			il_ग_लिखो_targ_mem(il, disable_ptr + (i * माप(u32)),
					  evt_disable[i]);

	पूर्ण अन्यथा अणु
		D_INFO("Selected uCode log events may be disabled\n");
		D_INFO("  by writing \"1\"s into disable bitmap\n");
		D_INFO("  in SRAM at 0x%x, size %d u32s\n", disable_ptr,
		       array_size);
	पूर्ण

पूर्ण

अटल पूर्णांक
il3945_hwrate_to_plcp_idx(u8 plcp)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < RATE_COUNT_3945; idx++)
		अगर (il3945_rates[idx].plcp == plcp)
			वापस idx;
	वापस -1;
पूर्ण

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
#घोषणा TX_STATUS_ENTRY(x) हाल TX_3945_STATUS_FAIL_ ## x: वापस #x

अटल स्थिर अक्षर *
il3945_get_tx_fail_reason(u32 status)
अणु
	चयन (status & TX_STATUS_MSK) अणु
	हाल TX_3945_STATUS_SUCCESS:
		वापस "SUCCESS";
		TX_STATUS_ENTRY(SHORT_LIMIT);
		TX_STATUS_ENTRY(LONG_LIMIT);
		TX_STATUS_ENTRY(FIFO_UNDERRUN);
		TX_STATUS_ENTRY(MGMNT_ABORT);
		TX_STATUS_ENTRY(NEXT_FRAG);
		TX_STATUS_ENTRY(LIFE_EXPIRE);
		TX_STATUS_ENTRY(DEST_PS);
		TX_STATUS_ENTRY(ABORTED);
		TX_STATUS_ENTRY(BT_RETRY);
		TX_STATUS_ENTRY(STA_INVALID);
		TX_STATUS_ENTRY(FRAG_DROPPED);
		TX_STATUS_ENTRY(TID_DISABLE);
		TX_STATUS_ENTRY(FRAME_FLUSHED);
		TX_STATUS_ENTRY(INSUFFICIENT_CF_POLL);
		TX_STATUS_ENTRY(TX_LOCKED);
		TX_STATUS_ENTRY(NO_BEACON_ON_RADAR);
	पूर्ण

	वापस "UNKNOWN";
पूर्ण
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *
il3945_get_tx_fail_reason(u32 status)
अणु
	वापस "";
पूर्ण
#पूर्ण_अगर

/*
 * get ieee prev rate from rate scale table.
 * क्रम A and B mode we need to overright prev
 * value
 */
पूर्णांक
il3945_rs_next_rate(काष्ठा il_priv *il, पूर्णांक rate)
अणु
	पूर्णांक next_rate = il3945_get_prev_ieee_rate(rate);

	चयन (il->band) अणु
	हाल NL80211_BAND_5GHZ:
		अगर (rate == RATE_12M_IDX)
			next_rate = RATE_9M_IDX;
		अन्यथा अगर (rate == RATE_6M_IDX)
			next_rate = RATE_6M_IDX;
		अवरोध;
	हाल NL80211_BAND_2GHZ:
		अगर (!(il->_3945.sta_supp_rates & IL_OFDM_RATES_MASK) &&
		    il_is_associated(il)) अणु
			अगर (rate == RATE_11M_IDX)
				next_rate = RATE_5M_IDX;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस next_rate;
पूर्ण

/*
 * il3945_tx_queue_reclaim - Reclaim Tx queue entries alपढ़ोy Tx'd
 *
 * When FW advances 'R' idx, all entries between old and new 'R' idx
 * need to be reclaimed. As result, some मुक्त space क्रमms. If there is
 * enough मुक्त space (> low mark), wake the stack that feeds us.
 */
अटल व्योम
il3945_tx_queue_reclaim(काष्ठा il_priv *il, पूर्णांक txq_id, पूर्णांक idx)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];
	काष्ठा il_queue *q = &txq->q;
	काष्ठा sk_buff *skb;

	BUG_ON(txq_id == IL39_CMD_QUEUE_NUM);

	क्रम (idx = il_queue_inc_wrap(idx, q->n_bd); q->पढ़ो_ptr != idx;
	     q->पढ़ो_ptr = il_queue_inc_wrap(q->पढ़ो_ptr, q->n_bd)) अणु

		skb = txq->skbs[txq->q.पढ़ो_ptr];
		ieee80211_tx_status_irqsafe(il->hw, skb);
		txq->skbs[txq->q.पढ़ो_ptr] = शून्य;
		il->ops->txq_मुक्त_tfd(il, txq);
	पूर्ण

	अगर (il_queue_space(q) > q->low_mark && txq_id >= 0 &&
	    txq_id != IL39_CMD_QUEUE_NUM && il->mac80211_रेजिस्टरed)
		il_wake_queue(il, txq);
पूर्ण

/*
 * il3945_hdl_tx - Handle Tx response
 */
अटल व्योम
il3945_hdl_tx(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	पूर्णांक txq_id = SEQ_TO_QUEUE(sequence);
	पूर्णांक idx = SEQ_TO_IDX(sequence);
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];
	काष्ठा ieee80211_tx_info *info;
	काष्ठा il3945_tx_resp *tx_resp = (व्योम *)&pkt->u.raw[0];
	u32 status = le32_to_cpu(tx_resp->status);
	पूर्णांक rate_idx;
	पूर्णांक fail;

	अगर (idx >= txq->q.n_bd || il_queue_used(&txq->q, idx) == 0) अणु
		IL_ERR("Read idx for DMA queue txq_id (%d) idx %d "
		       "is out of range [0-%d] %d %d\n", txq_id, idx,
		       txq->q.n_bd, txq->q.ग_लिखो_ptr, txq->q.पढ़ो_ptr);
		वापस;
	पूर्ण

	/*
	 * Firmware will not transmit frame on passive channel, अगर it not yet
	 * received some valid frame on that channel. When this error happen
	 * we have to रुको until firmware will unblock itself i.e. when we
	 * note received beacon or other frame. We unblock queues in
	 * il3945_pass_packet_to_mac80211 or in il_mac_bss_info_changed.
	 */
	अगर (unlikely((status & TX_STATUS_MSK) == TX_STATUS_FAIL_PASSIVE_NO_RX) &&
	    il->iw_mode == NL80211_IFTYPE_STATION) अणु
		il_stop_queues_by_reason(il, IL_STOP_REASON_PASSIVE);
		D_INFO("Stopped queues - RX waiting on passive channel\n");
	पूर्ण

	txq->समय_stamp = jअगरfies;
	info = IEEE80211_SKB_CB(txq->skbs[txq->q.पढ़ो_ptr]);
	ieee80211_tx_info_clear_status(info);

	/* Fill the MRR chain with some info about on-chip retransmissions */
	rate_idx = il3945_hwrate_to_plcp_idx(tx_resp->rate);
	अगर (info->band == NL80211_BAND_5GHZ)
		rate_idx -= IL_FIRST_OFDM_RATE;

	fail = tx_resp->failure_frame;

	info->status.rates[0].idx = rate_idx;
	info->status.rates[0].count = fail + 1;	/* add final attempt */

	/* tx_status->rts_retry_count = tx_resp->failure_rts; */
	info->flags |=
	    ((status & TX_STATUS_MSK) ==
	     TX_STATUS_SUCCESS) ? IEEE80211_TX_STAT_ACK : 0;

	D_TX("Tx queue %d Status %s (0x%08x) plcp rate %d retries %d\n", txq_id,
	     il3945_get_tx_fail_reason(status), status, tx_resp->rate,
	     tx_resp->failure_frame);

	D_TX_REPLY("Tx queue reclaim %d\n", idx);
	il3945_tx_queue_reclaim(il, txq_id, idx);

	अगर (status & TX_ABORT_REQUIRED_MSK)
		IL_ERR("TODO:  Implement Tx ABORT REQUIRED!!!\n");
पूर्ण

/*****************************************************************************
 *
 * Intel PRO/Wireless 3945ABG/BG Network Connection
 *
 *  RX handler implementations
 *
 *****************************************************************************/
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
अटल व्योम
il3945_accumulative_stats(काष्ठा il_priv *il, __le32 * stats)
अणु
	पूर्णांक i;
	__le32 *prev_stats;
	u32 *accum_stats;
	u32 *delta, *max_delta;

	prev_stats = (__le32 *) &il->_3945.stats;
	accum_stats = (u32 *) &il->_3945.accum_stats;
	delta = (u32 *) &il->_3945.delta_stats;
	max_delta = (u32 *) &il->_3945.max_delta;

	क्रम (i = माप(__le32); i < माप(काष्ठा il3945_notअगर_stats);
	     i +=
	     माप(__le32), stats++, prev_stats++, delta++, max_delta++,
	     accum_stats++) अणु
		अगर (le32_to_cpu(*stats) > le32_to_cpu(*prev_stats)) अणु
			*delta =
			    (le32_to_cpu(*stats) - le32_to_cpu(*prev_stats));
			*accum_stats += *delta;
			अगर (*delta > *max_delta)
				*max_delta = *delta;
		पूर्ण
	पूर्ण

	/* reset accumulative stats क्रम "no-counter" type stats */
	il->_3945.accum_stats.general.temperature =
	    il->_3945.stats.general.temperature;
	il->_3945.accum_stats.general.ttl_बारtamp =
	    il->_3945.stats.general.ttl_बारtamp;
पूर्ण
#पूर्ण_अगर

व्योम
il3945_hdl_stats(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);

	D_RX("Statistics notification received (%d vs %d).\n",
	     (पूर्णांक)माप(काष्ठा il3945_notअगर_stats),
	     le32_to_cpu(pkt->len_n_flags) & IL_RX_FRAME_SIZE_MSK);
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
	il3945_accumulative_stats(il, (__le32 *) &pkt->u.raw);
#पूर्ण_अगर

	स_नकल(&il->_3945.stats, pkt->u.raw, माप(il->_3945.stats));
पूर्ण

व्योम
il3945_hdl_c_stats(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	__le32 *flag = (__le32 *) &pkt->u.raw;

	अगर (le32_to_cpu(*flag) & UCODE_STATS_CLEAR_MSK) अणु
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
		स_रखो(&il->_3945.accum_stats, 0,
		       माप(काष्ठा il3945_notअगर_stats));
		स_रखो(&il->_3945.delta_stats, 0,
		       माप(काष्ठा il3945_notअगर_stats));
		स_रखो(&il->_3945.max_delta, 0,
		       माप(काष्ठा il3945_notअगर_stats));
#पूर्ण_अगर
		D_RX("Statistics have been cleared\n");
	पूर्ण
	il3945_hdl_stats(il, rxb);
पूर्ण

/******************************************************************************
 *
 * Misc. पूर्णांकernal state and helper functions
 *
 ******************************************************************************/

/* This is necessary only क्रम a number of stats, see the caller. */
अटल पूर्णांक
il3945_is_network_packet(काष्ठा il_priv *il, काष्ठा ieee80211_hdr *header)
अणु
	/* Filter incoming packets to determine अगर they are targeted toward
	 * this network, discarding packets coming from ourselves */
	चयन (il->iw_mode) अणु
	हाल NL80211_IFTYPE_ADHOC:	/* Header: Dest. | Source    | BSSID */
		/* packets to our IBSS update inक्रमmation */
		वापस ether_addr_equal_64bits(header->addr3, il->bssid);
	हाल NL80211_IFTYPE_STATION:	/* Header: Dest. | APअणुBSSIDपूर्ण | Source */
		/* packets to our IBSS update inक्रमmation */
		वापस ether_addr_equal_64bits(header->addr2, il->bssid);
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

#घोषणा SMALL_PACKET_SIZE 256

अटल व्योम
il3945_pass_packet_to_mac80211(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb,
			       काष्ठा ieee80211_rx_status *stats)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)IL_RX_DATA(pkt);
	काष्ठा il3945_rx_frame_hdr *rx_hdr = IL_RX_HDR(pkt);
	काष्ठा il3945_rx_frame_end *rx_end = IL_RX_END(pkt);
	u32 len = le16_to_cpu(rx_hdr->len);
	काष्ठा sk_buff *skb;
	__le16 fc = hdr->frame_control;
	u32 fraglen = PAGE_SIZE << il->hw_params.rx_page_order;

	/* We received data from the HW, so stop the watchकरोg */
	अगर (unlikely(len + IL39_RX_FRAME_SIZE > fraglen)) अणु
		D_DROP("Corruption detected!\n");
		वापस;
	पूर्ण

	/* We only process data packets अगर the पूर्णांकerface is खोलो */
	अगर (unlikely(!il->is_खोलो)) अणु
		D_DROP("Dropping packet while interface is not open.\n");
		वापस;
	पूर्ण

	अगर (unlikely(test_bit(IL_STOP_REASON_PASSIVE, &il->stop_reason))) अणु
		il_wake_queues_by_reason(il, IL_STOP_REASON_PASSIVE);
		D_INFO("Woke queues - frame received on passive channel\n");
	पूर्ण

	skb = dev_alloc_skb(SMALL_PACKET_SIZE);
	अगर (!skb) अणु
		IL_ERR("dev_alloc_skb failed\n");
		वापस;
	पूर्ण

	अगर (!il3945_mod_params.sw_crypto)
		il_set_decrypted_flag(il, (काष्ठा ieee80211_hdr *)pkt,
				      le32_to_cpu(rx_end->status), stats);

	/* If frame is small enough to fit पूर्णांकo skb->head, copy it
	 * and करो not consume a full page
	 */
	अगर (len <= SMALL_PACKET_SIZE) अणु
		skb_put_data(skb, rx_hdr->payload, len);
	पूर्ण अन्यथा अणु
		skb_add_rx_frag(skb, 0, rxb->page,
				(व्योम *)rx_hdr->payload - (व्योम *)pkt, len,
				fraglen);
		il->alloc_rxb_page--;
		rxb->page = शून्य;
	पूर्ण
	il_update_stats(il, false, fc, len);
	स_नकल(IEEE80211_SKB_RXCB(skb), stats, माप(*stats));

	ieee80211_rx(il->hw, skb);
पूर्ण

#घोषणा IL_DELAY_NEXT_SCAN_AFTER_ASSOC (HZ*6)

अटल व्योम
il3945_hdl_rx(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा ieee80211_hdr *header;
	काष्ठा ieee80211_rx_status rx_status = अणुपूर्ण;
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il3945_rx_frame_stats *rx_stats = IL_RX_STATS(pkt);
	काष्ठा il3945_rx_frame_hdr *rx_hdr = IL_RX_HDR(pkt);
	काष्ठा il3945_rx_frame_end *rx_end = IL_RX_END(pkt);
	u16 rx_stats_sig_avg __maybe_unused = le16_to_cpu(rx_stats->sig_avg);
	u16 rx_stats_noise_dअगरf __maybe_unused =
	    le16_to_cpu(rx_stats->noise_dअगरf);
	u8 network_packet;

	rx_status.flag = 0;
	rx_status.maस_समय = le64_to_cpu(rx_end->बारtamp);
	rx_status.band =
	    (rx_hdr->
	     phy_flags & RX_RES_PHY_FLAGS_BAND_24_MSK) ? NL80211_BAND_2GHZ :
	    NL80211_BAND_5GHZ;
	rx_status.freq =
	    ieee80211_channel_to_frequency(le16_to_cpu(rx_hdr->channel),
					   rx_status.band);

	rx_status.rate_idx = il3945_hwrate_to_plcp_idx(rx_hdr->rate);
	अगर (rx_status.band == NL80211_BAND_5GHZ)
		rx_status.rate_idx -= IL_FIRST_OFDM_RATE;

	rx_status.antenna =
	    (le16_to_cpu(rx_hdr->phy_flags) & RX_RES_PHY_FLAGS_ANTENNA_MSK) >>
	    4;

	/* set the preamble flag अगर appropriate */
	अगर (rx_hdr->phy_flags & RX_RES_PHY_FLAGS_SHORT_PREAMBLE_MSK)
		rx_status.enc_flags |= RX_ENC_FLAG_SHORTPRE;

	अगर ((unlikely(rx_stats->phy_count > 20))) अणु
		D_DROP("dsp size out of range [0,20]: %d\n",
		       rx_stats->phy_count);
		वापस;
	पूर्ण

	अगर (!(rx_end->status & RX_RES_STATUS_NO_CRC32_ERROR) ||
	    !(rx_end->status & RX_RES_STATUS_NO_RXE_OVERFLOW)) अणु
		D_RX("Bad CRC or FIFO: 0x%08X.\n", rx_end->status);
		वापस;
	पूर्ण

	/* Convert 3945's rssi indicator to dBm */
	rx_status.संकेत = rx_stats->rssi - IL39_RSSI_OFFSET;

	D_STATS("Rssi %d sig_avg %d noise_diff %d\n", rx_status.संकेत,
		rx_stats_sig_avg, rx_stats_noise_dअगरf);

	header = (काष्ठा ieee80211_hdr *)IL_RX_DATA(pkt);

	network_packet = il3945_is_network_packet(il, header);

	D_STATS("[%c] %d RSSI:%d Signal:%u, Rate:%u\n",
		network_packet ? '*' : ' ', le16_to_cpu(rx_hdr->channel),
		rx_status.संकेत, rx_status.संकेत, rx_status.rate_idx);

	अगर (network_packet) अणु
		il->_3945.last_beacon_समय =
		    le32_to_cpu(rx_end->beacon_बारtamp);
		il->_3945.last_tsf = le64_to_cpu(rx_end->बारtamp);
		il->_3945.last_rx_rssi = rx_status.संकेत;
	पूर्ण

	il3945_pass_packet_to_mac80211(il, rxb, &rx_status);
पूर्ण

पूर्णांक
il3945_hw_txq_attach_buf_to_tfd(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq,
				dma_addr_t addr, u16 len, u8 reset, u8 pad)
अणु
	पूर्णांक count;
	काष्ठा il_queue *q;
	काष्ठा il3945_tfd *tfd, *tfd_पंचांगp;

	q = &txq->q;
	tfd_पंचांगp = (काष्ठा il3945_tfd *)txq->tfds;
	tfd = &tfd_पंचांगp[q->ग_लिखो_ptr];

	अगर (reset)
		स_रखो(tfd, 0, माप(*tfd));

	count = TFD_CTL_COUNT_GET(le32_to_cpu(tfd->control_flags));

	अगर (count >= NUM_TFD_CHUNKS || count < 0) अणु
		IL_ERR("Error can not send more than %d chunks\n",
		       NUM_TFD_CHUNKS);
		वापस -EINVAL;
	पूर्ण

	tfd->tbs[count].addr = cpu_to_le32(addr);
	tfd->tbs[count].len = cpu_to_le32(len);

	count++;

	tfd->control_flags =
	    cpu_to_le32(TFD_CTL_COUNT_SET(count) | TFD_CTL_PAD_SET(pad));

	वापस 0;
पूर्ण

/*
 * il3945_hw_txq_मुक्त_tfd - Free one TFD, those at idx [txq->q.पढ़ो_ptr]
 *
 * Does NOT advance any idxes
 */
व्योम
il3945_hw_txq_मुक्त_tfd(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq)
अणु
	काष्ठा il3945_tfd *tfd_पंचांगp = (काष्ठा il3945_tfd *)txq->tfds;
	पूर्णांक idx = txq->q.पढ़ो_ptr;
	काष्ठा il3945_tfd *tfd = &tfd_पंचांगp[idx];
	काष्ठा pci_dev *dev = il->pci_dev;
	पूर्णांक i;
	पूर्णांक counter;

	/* sanity check */
	counter = TFD_CTL_COUNT_GET(le32_to_cpu(tfd->control_flags));
	अगर (counter > NUM_TFD_CHUNKS) अणु
		IL_ERR("Too many chunks: %i\n", counter);
		/* @toकरो issue fatal error, it is quite serious situation */
		वापस;
	पूर्ण

	/* Unmap tx_cmd */
	अगर (counter)
		pci_unmap_single(dev, dma_unmap_addr(&txq->meta[idx], mapping),
				 dma_unmap_len(&txq->meta[idx], len),
				 PCI_DMA_TODEVICE);

	/* unmap chunks अगर any */

	क्रम (i = 1; i < counter; i++)
		pci_unmap_single(dev, le32_to_cpu(tfd->tbs[i].addr),
				 le32_to_cpu(tfd->tbs[i].len),
				 PCI_DMA_TODEVICE);

	/* मुक्त SKB */
	अगर (txq->skbs) अणु
		काष्ठा sk_buff *skb = txq->skbs[txq->q.पढ़ो_ptr];

		/* can be called from irqs-disabled context */
		अगर (skb) अणु
			dev_kमुक्त_skb_any(skb);
			txq->skbs[txq->q.पढ़ो_ptr] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * il3945_hw_build_tx_cmd_rate - Add rate portion to TX_CMD:
 *
*/
व्योम
il3945_hw_build_tx_cmd_rate(काष्ठा il_priv *il, काष्ठा il_device_cmd *cmd,
			    काष्ठा ieee80211_tx_info *info,
			    काष्ठा ieee80211_hdr *hdr, पूर्णांक sta_id)
अणु
	u16 hw_value = ieee80211_get_tx_rate(il->hw, info)->hw_value;
	u16 rate_idx = min(hw_value & 0xffff, RATE_COUNT_3945 - 1);
	u16 rate_mask;
	पूर्णांक rate;
	स्थिर u8 rts_retry_limit = 7;
	u8 data_retry_limit;
	__le32 tx_flags;
	__le16 fc = hdr->frame_control;
	काष्ठा il3945_tx_cmd *tx_cmd = (काष्ठा il3945_tx_cmd *)cmd->cmd.payload;

	rate = il3945_rates[rate_idx].plcp;
	tx_flags = tx_cmd->tx_flags;

	/* We need to figure out how to get the sta->supp_rates जबतक
	 * in this running context */
	rate_mask = RATES_MASK_3945;

	/* Set retry limit on DATA packets and Probe Responses */
	अगर (ieee80211_is_probe_resp(fc))
		data_retry_limit = 3;
	अन्यथा
		data_retry_limit = IL_DEFAULT_TX_RETRY;
	tx_cmd->data_retry_limit = data_retry_limit;
	/* Set retry limit on RTS packets */
	tx_cmd->rts_retry_limit = min(data_retry_limit, rts_retry_limit);

	tx_cmd->rate = rate;
	tx_cmd->tx_flags = tx_flags;

	/* OFDM */
	tx_cmd->supp_rates[0] =
	    ((rate_mask & IL_OFDM_RATES_MASK) >> IL_FIRST_OFDM_RATE) & 0xFF;

	/* CCK */
	tx_cmd->supp_rates[1] = (rate_mask & 0xF);

	D_RATE("Tx sta id: %d, rate: %d (plcp), flags: 0x%4X "
	       "cck/ofdm mask: 0x%x/0x%x\n", sta_id, tx_cmd->rate,
	       le32_to_cpu(tx_cmd->tx_flags), tx_cmd->supp_rates[1],
	       tx_cmd->supp_rates[0]);
पूर्ण

अटल u8
il3945_sync_sta(काष्ठा il_priv *il, पूर्णांक sta_id, u16 tx_rate)
अणु
	अचिन्हित दीर्घ flags_spin;
	काष्ठा il_station_entry *station;

	अगर (sta_id == IL_INVALID_STATION)
		वापस IL_INVALID_STATION;

	spin_lock_irqsave(&il->sta_lock, flags_spin);
	station = &il->stations[sta_id];

	station->sta.sta.modअगरy_mask = STA_MODIFY_TX_RATE_MSK;
	station->sta.rate_n_flags = cpu_to_le16(tx_rate);
	station->sta.mode = STA_CONTROL_MODIFY_MSK;
	il_send_add_sta(il, &station->sta, CMD_ASYNC);
	spin_unlock_irqrestore(&il->sta_lock, flags_spin);

	D_RATE("SCALE sync station %d to rate %d\n", sta_id, tx_rate);
	वापस sta_id;
पूर्ण

अटल व्योम
il3945_set_pwr_vमुख्य(काष्ठा il_priv *il)
अणु
/*
 * (क्रम करोcumentation purposes)
 * to set घातer to V_AUX, करो

		अगर (pci_pme_capable(il->pci_dev, PCI_D3cold)) अणु
			il_set_bits_mask_prph(il, APMG_PS_CTRL_REG,
					APMG_PS_CTRL_VAL_PWR_SRC_VAUX,
					~APMG_PS_CTRL_MSK_PWR_SRC);

			_il_poll_bit(il, CSR_GPIO_IN,
				     CSR_GPIO_IN_VAL_VAUX_PWR_SRC,
				     CSR_GPIO_IN_BIT_AUX_POWER, 5000);
		पूर्ण
 */

	il_set_bits_mask_prph(il, APMG_PS_CTRL_REG,
			      APMG_PS_CTRL_VAL_PWR_SRC_VMAIN,
			      ~APMG_PS_CTRL_MSK_PWR_SRC);

	_il_poll_bit(il, CSR_GPIO_IN, CSR_GPIO_IN_VAL_VMAIN_PWR_SRC,
		     CSR_GPIO_IN_BIT_AUX_POWER, 5000);
पूर्ण

अटल पूर्णांक
il3945_rx_init(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq)
अणु
	il_wr(il, FH39_RCSR_RBD_BASE(0), rxq->bd_dma);
	il_wr(il, FH39_RCSR_RPTR_ADDR(0), rxq->rb_stts_dma);
	il_wr(il, FH39_RCSR_WPTR(0), 0);
	il_wr(il, FH39_RCSR_CONFIG(0),
	      FH39_RCSR_RX_CONFIG_REG_VAL_DMA_CHNL_EN_ENABLE |
	      FH39_RCSR_RX_CONFIG_REG_VAL_RDRBD_EN_ENABLE |
	      FH39_RCSR_RX_CONFIG_REG_BIT_WR_STTS_EN |
	      FH39_RCSR_RX_CONFIG_REG_VAL_MAX_FRAG_SIZE_128 | (RX_QUEUE_SIZE_LOG
							       <<
							       FH39_RCSR_RX_CONFIG_REG_POS_RBDC_SIZE)
	      | FH39_RCSR_RX_CONFIG_REG_VAL_IRQ_DEST_INT_HOST | (1 <<
								 FH39_RCSR_RX_CONFIG_REG_POS_IRQ_RBTH)
	      | FH39_RCSR_RX_CONFIG_REG_VAL_MSG_MODE_FH);

	/* fake पढ़ो to flush all prev I/O */
	il_rd(il, FH39_RSSR_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक
il3945_tx_reset(काष्ठा il_priv *il)
अणु
	/* bypass mode */
	il_wr_prph(il, ALM_SCD_MODE_REG, 0x2);

	/* RA 0 is active */
	il_wr_prph(il, ALM_SCD_ARASTAT_REG, 0x01);

	/* all 6 fअगरo are active */
	il_wr_prph(il, ALM_SCD_TXFACT_REG, 0x3f);

	il_wr_prph(il, ALM_SCD_SBYP_MODE_1_REG, 0x010000);
	il_wr_prph(il, ALM_SCD_SBYP_MODE_2_REG, 0x030002);
	il_wr_prph(il, ALM_SCD_TXF4MF_REG, 0x000004);
	il_wr_prph(il, ALM_SCD_TXF5MF_REG, 0x000005);

	il_wr(il, FH39_TSSR_CBB_BASE, il->_3945.shared_phys);

	il_wr(il, FH39_TSSR_MSG_CONFIG,
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_SNOOP_RD_TXPD_ON |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RD_TXPD_ON |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_MAX_FRAG_SIZE_128B |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_SNOOP_RD_TFD_ON |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RD_CBB_ON |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_ORDER_RSP_WAIT_TH |
	      FH39_TSSR_TX_MSG_CONFIG_REG_VAL_RSP_WAIT_TH);

	वापस 0;
पूर्ण

/*
 * il3945_txq_ctx_reset - Reset TX queue context
 *
 * Destroys all DMA काष्ठाures and initialize them again
 */
अटल पूर्णांक
il3945_txq_ctx_reset(काष्ठा il_priv *il)
अणु
	पूर्णांक rc, txq_id;

	il3945_hw_txq_ctx_मुक्त(il);

	/* allocate tx queue काष्ठाure */
	rc = il_alloc_txq_mem(il);
	अगर (rc)
		वापस rc;

	/* Tx CMD queue */
	rc = il3945_tx_reset(il);
	अगर (rc)
		जाओ error;

	/* Tx queue(s) */
	क्रम (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++) अणु
		rc = il_tx_queue_init(il, txq_id);
		अगर (rc) अणु
			IL_ERR("Tx %d queue init failed\n", txq_id);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस rc;

error:
	il3945_hw_txq_ctx_मुक्त(il);
	वापस rc;
पूर्ण

/*
 * Start up 3945's basic functionality after it has been reset
 * (e.g. after platक्रमm boot, or shutकरोwn via il_apm_stop())
 * NOTE:  This करोes not load uCode nor start the embedded processor
 */
अटल पूर्णांक
il3945_apm_init(काष्ठा il_priv *il)
अणु
	पूर्णांक ret = il_apm_init(il);

	/* Clear APMG (NIC's पूर्णांकernal घातer management) पूर्णांकerrupts */
	il_wr_prph(il, APMG_RTC_INT_MSK_REG, 0x0);
	il_wr_prph(il, APMG_RTC_INT_STT_REG, 0xFFFFFFFF);

	/* Reset radio chip */
	il_set_bits_prph(il, APMG_PS_CTRL_REG, APMG_PS_CTRL_VAL_RESET_REQ);
	udelay(5);
	il_clear_bits_prph(il, APMG_PS_CTRL_REG, APMG_PS_CTRL_VAL_RESET_REQ);

	वापस ret;
पूर्ण

अटल व्योम
il3945_nic_config(काष्ठा il_priv *il)
अणु
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;
	अचिन्हित दीर्घ flags;
	u8 rev_id = il->pci_dev->revision;

	spin_lock_irqsave(&il->lock, flags);

	/* Determine HW type */
	D_INFO("HW Revision ID = 0x%X\n", rev_id);

	अगर (rev_id & PCI_CFG_REV_ID_BIT_RTP)
		D_INFO("RTP type\n");
	अन्यथा अगर (rev_id & PCI_CFG_REV_ID_BIT_BASIC_SKU) अणु
		D_INFO("3945 RADIO-MB type\n");
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BIT_3945_MB);
	पूर्ण अन्यथा अणु
		D_INFO("3945 RADIO-MM type\n");
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BIT_3945_MM);
	पूर्ण

	अगर (EEPROM_SKU_CAP_OP_MODE_MRC == eeprom->sku_cap) अणु
		D_INFO("SKU OP mode is mrc\n");
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BIT_SKU_MRC);
	पूर्ण अन्यथा
		D_INFO("SKU OP mode is basic\n");

	अगर ((eeprom->board_revision & 0xF0) == 0xD0) अणु
		D_INFO("3945ABG revision is 0x%X\n", eeprom->board_revision);
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BIT_BOARD_TYPE);
	पूर्ण अन्यथा अणु
		D_INFO("3945ABG revision is 0x%X\n", eeprom->board_revision);
		il_clear_bit(il, CSR_HW_IF_CONFIG_REG,
			     CSR39_HW_IF_CONFIG_REG_BIT_BOARD_TYPE);
	पूर्ण

	अगर (eeprom->almgor_m_version <= 1) अणु
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BITS_SILICON_TYPE_A);
		D_INFO("Card M type A version is 0x%X\n",
		       eeprom->almgor_m_version);
	पूर्ण अन्यथा अणु
		D_INFO("Card M type B version is 0x%X\n",
		       eeprom->almgor_m_version);
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR39_HW_IF_CONFIG_REG_BITS_SILICON_TYPE_B);
	पूर्ण
	spin_unlock_irqrestore(&il->lock, flags);

	अगर (eeprom->sku_cap & EEPROM_SKU_CAP_SW_RF_KILL_ENABLE)
		D_RF_KILL("SW RF KILL supported in EEPROM.\n");

	अगर (eeprom->sku_cap & EEPROM_SKU_CAP_HW_RF_KILL_ENABLE)
		D_RF_KILL("HW RF KILL supported in EEPROM.\n");
पूर्ण

पूर्णांक
il3945_hw_nic_init(काष्ठा il_priv *il)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	काष्ठा il_rx_queue *rxq = &il->rxq;

	spin_lock_irqsave(&il->lock, flags);
	il3945_apm_init(il);
	spin_unlock_irqrestore(&il->lock, flags);

	il3945_set_pwr_vमुख्य(il);
	il3945_nic_config(il);

	/* Allocate the RX queue, or reset अगर it is alपढ़ोy allocated */
	अगर (!rxq->bd) अणु
		rc = il_rx_queue_alloc(il);
		अगर (rc) अणु
			IL_ERR("Unable to initialize Rx queue\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा
		il3945_rx_queue_reset(il, rxq);

	il3945_rx_replenish(il);

	il3945_rx_init(il, rxq);

	/* Look at using this instead:
	   rxq->need_update = 1;
	   il_rx_queue_update_ग_लिखो_ptr(il, rxq);
	 */

	il_wr(il, FH39_RCSR_WPTR(0), rxq->ग_लिखो & ~7);

	rc = il3945_txq_ctx_reset(il);
	अगर (rc)
		वापस rc;

	set_bit(S_INIT, &il->status);

	वापस 0;
पूर्ण

/*
 * il3945_hw_txq_ctx_मुक्त - Free TXQ Context
 *
 * Destroy all TX DMA queues and काष्ठाures
 */
व्योम
il3945_hw_txq_ctx_मुक्त(काष्ठा il_priv *il)
अणु
	पूर्णांक txq_id;

	/* Tx queues */
	अगर (il->txq) अणु
		क्रम (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
			अगर (txq_id == IL39_CMD_QUEUE_NUM)
				il_cmd_queue_मुक्त(il);
			अन्यथा
				il_tx_queue_मुक्त(il, txq_id);
	पूर्ण

	/* मुक्त tx queue काष्ठाure */
	il_मुक्त_txq_mem(il);
पूर्ण

व्योम
il3945_hw_txq_ctx_stop(काष्ठा il_priv *il)
अणु
	पूर्णांक txq_id;

	/* stop SCD */
	_il_wr_prph(il, ALM_SCD_MODE_REG, 0);
	_il_wr_prph(il, ALM_SCD_TXFACT_REG, 0);

	/* reset TFD queues */
	क्रम (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++) अणु
		_il_wr(il, FH39_TCSR_CONFIG(txq_id), 0x0);
		_il_poll_bit(il, FH39_TSSR_TX_STATUS,
			     FH39_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(txq_id),
			     FH39_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(txq_id),
			     1000);
	पूर्ण
पूर्ण

/*
 * il3945_hw_reg_adjust_घातer_by_temp
 * वापस idx delta पूर्णांकo घातer gain settings table
*/
अटल पूर्णांक
il3945_hw_reg_adjust_घातer_by_temp(पूर्णांक new_पढ़ोing, पूर्णांक old_पढ़ोing)
अणु
	वापस (new_पढ़ोing - old_पढ़ोing) * (-11) / 100;
पूर्ण

/*
 * il3945_hw_reg_temp_out_of_range - Keep temperature in sane range
 */
अटल अंतरभूत पूर्णांक
il3945_hw_reg_temp_out_of_range(पूर्णांक temperature)
अणु
	वापस (temperature < -260 || temperature > 25) ? 1 : 0;
पूर्ण

पूर्णांक
il3945_hw_get_temperature(काष्ठा il_priv *il)
अणु
	वापस _il_rd(il, CSR_UCODE_DRV_GP2);
पूर्ण

/*
 * il3945_hw_reg_txघातer_get_temperature
 * get the current temperature by पढ़ोing from NIC
*/
अटल पूर्णांक
il3945_hw_reg_txघातer_get_temperature(काष्ठा il_priv *il)
अणु
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;
	पूर्णांक temperature;

	temperature = il3945_hw_get_temperature(il);

	/* driver's okay range is -260 to +25.
	 *   human पढ़ोable okay range is 0 to +285 */
	D_INFO("Temperature: %d\n", temperature + IL_TEMP_CONVERT);

	/* handle insane temp पढ़ोing */
	अगर (il3945_hw_reg_temp_out_of_range(temperature)) अणु
		IL_ERR("Error bad temperature value  %d\n", temperature);

		/* अगर really really hot(?),
		 *   substitute the 3rd band/group's temp measured at factory */
		अगर (il->last_temperature > 100)
			temperature = eeprom->groups[2].temperature;
		अन्यथा		/* अन्यथा use most recent "sane" value from driver */
			temperature = il->last_temperature;
	पूर्ण

	वापस temperature;	/* raw, not "human readable" */
पूर्ण

/* Adjust Txघातer only अगर temperature variance is greater than threshold.
 *
 * Both are lower than older versions' 9 degrees */
#घोषणा IL_TEMPERATURE_LIMIT_TIMER   6

/*
 * il3945_is_temp_calib_needed - determines अगर new calibration is needed
 *
 * records new temperature in tx_mgr->temperature.
 * replaces tx_mgr->last_temperature *only* अगर calib needed
 *    (assumes caller will actually करो the calibration!). */
अटल पूर्णांक
il3945_is_temp_calib_needed(काष्ठा il_priv *il)
अणु
	पूर्णांक temp_dअगरf;

	il->temperature = il3945_hw_reg_txघातer_get_temperature(il);
	temp_dअगरf = il->temperature - il->last_temperature;

	/* get असलolute value */
	अगर (temp_dअगरf < 0) अणु
		D_POWER("Getting cooler, delta %d,\n", temp_dअगरf);
		temp_dअगरf = -temp_dअगरf;
	पूर्ण अन्यथा अगर (temp_dअगरf == 0)
		D_POWER("Same temp,\n");
	अन्यथा
		D_POWER("Getting warmer, delta %d,\n", temp_dअगरf);

	/* अगर we करोn't need calibration, *don't* update last_temperature */
	अगर (temp_dअगरf < IL_TEMPERATURE_LIMIT_TIMER) अणु
		D_POWER("Timed thermal calib not needed\n");
		वापस 0;
	पूर्ण

	D_POWER("Timed thermal calib needed\n");

	/* assume that caller will actually करो calib ...
	 *   update the "last temperature" value */
	il->last_temperature = il->temperature;
	वापस 1;
पूर्ण

#घोषणा IL_MAX_GAIN_ENTRIES 78
#घोषणा IL_CCK_FROM_OFDM_POWER_DIFF  -5
#घोषणा IL_CCK_FROM_OFDM_IDX_DIFF (10)

/* radio and DSP घातer table, each step is 1/2 dB.
 * 1st number is क्रम RF analog gain, 2nd number is क्रम DSP pre-DAC gain. */
अटल काष्ठा il3945_tx_घातer घातer_gain_table[2][IL_MAX_GAIN_ENTRIES] = अणु
	अणु
	 अणु251, 127पूर्ण,		/* 2.4 GHz, highest घातer */
	 अणु251, 127पूर्ण,
	 अणु251, 127पूर्ण,
	 अणु251, 127पूर्ण,
	 अणु251, 125पूर्ण,
	 अणु251, 110पूर्ण,
	 अणु251, 105पूर्ण,
	 अणु251, 98पूर्ण,
	 अणु187, 125पूर्ण,
	 अणु187, 115पूर्ण,
	 अणु187, 108पूर्ण,
	 अणु187, 99पूर्ण,
	 अणु243, 119पूर्ण,
	 अणु243, 111पूर्ण,
	 अणु243, 105पूर्ण,
	 अणु243, 97पूर्ण,
	 अणु243, 92पूर्ण,
	 अणु211, 106पूर्ण,
	 अणु211, 100पूर्ण,
	 अणु179, 120पूर्ण,
	 अणु179, 113पूर्ण,
	 अणु179, 107पूर्ण,
	 अणु147, 125पूर्ण,
	 अणु147, 119पूर्ण,
	 अणु147, 112पूर्ण,
	 अणु147, 106पूर्ण,
	 अणु147, 101पूर्ण,
	 अणु147, 97पूर्ण,
	 अणु147, 91पूर्ण,
	 अणु115, 107पूर्ण,
	 अणु235, 121पूर्ण,
	 अणु235, 115पूर्ण,
	 अणु235, 109पूर्ण,
	 अणु203, 127पूर्ण,
	 अणु203, 121पूर्ण,
	 अणु203, 115पूर्ण,
	 अणु203, 108पूर्ण,
	 अणु203, 102पूर्ण,
	 अणु203, 96पूर्ण,
	 अणु203, 92पूर्ण,
	 अणु171, 110पूर्ण,
	 अणु171, 104पूर्ण,
	 अणु171, 98पूर्ण,
	 अणु139, 116पूर्ण,
	 अणु227, 125पूर्ण,
	 अणु227, 119पूर्ण,
	 अणु227, 113पूर्ण,
	 अणु227, 107पूर्ण,
	 अणु227, 101पूर्ण,
	 अणु227, 96पूर्ण,
	 अणु195, 113पूर्ण,
	 अणु195, 106पूर्ण,
	 अणु195, 102पूर्ण,
	 अणु195, 95पूर्ण,
	 अणु163, 113पूर्ण,
	 अणु163, 106पूर्ण,
	 अणु163, 102पूर्ण,
	 अणु163, 95पूर्ण,
	 अणु131, 113पूर्ण,
	 अणु131, 106पूर्ण,
	 अणु131, 102पूर्ण,
	 अणु131, 95पूर्ण,
	 अणु99, 113पूर्ण,
	 अणु99, 106पूर्ण,
	 अणु99, 102पूर्ण,
	 अणु99, 95पूर्ण,
	 अणु67, 113पूर्ण,
	 अणु67, 106पूर्ण,
	 अणु67, 102पूर्ण,
	 अणु67, 95पूर्ण,
	 अणु35, 113पूर्ण,
	 अणु35, 106पूर्ण,
	 अणु35, 102पूर्ण,
	 अणु35, 95पूर्ण,
	 अणु3, 113पूर्ण,
	 अणु3, 106पूर्ण,
	 अणु3, 102पूर्ण,
	 अणु3, 95पूर्ण		/* 2.4 GHz, lowest घातer */
	पूर्ण,
	अणु
	 अणु251, 127पूर्ण,		/* 5.x GHz, highest घातer */
	 अणु251, 120पूर्ण,
	 अणु251, 114पूर्ण,
	 अणु219, 119पूर्ण,
	 अणु219, 101पूर्ण,
	 अणु187, 113पूर्ण,
	 अणु187, 102पूर्ण,
	 अणु155, 114पूर्ण,
	 अणु155, 103पूर्ण,
	 अणु123, 117पूर्ण,
	 अणु123, 107पूर्ण,
	 अणु123, 99पूर्ण,
	 अणु123, 92पूर्ण,
	 अणु91, 108पूर्ण,
	 अणु59, 125पूर्ण,
	 अणु59, 118पूर्ण,
	 अणु59, 109पूर्ण,
	 अणु59, 102पूर्ण,
	 अणु59, 96पूर्ण,
	 अणु59, 90पूर्ण,
	 अणु27, 104पूर्ण,
	 अणु27, 98पूर्ण,
	 अणु27, 92पूर्ण,
	 अणु115, 118पूर्ण,
	 अणु115, 111पूर्ण,
	 अणु115, 104पूर्ण,
	 अणु83, 126पूर्ण,
	 अणु83, 121पूर्ण,
	 अणु83, 113पूर्ण,
	 अणु83, 105पूर्ण,
	 अणु83, 99पूर्ण,
	 अणु51, 118पूर्ण,
	 अणु51, 111पूर्ण,
	 अणु51, 104पूर्ण,
	 अणु51, 98पूर्ण,
	 अणु19, 116पूर्ण,
	 अणु19, 109पूर्ण,
	 अणु19, 102पूर्ण,
	 अणु19, 98पूर्ण,
	 अणु19, 93पूर्ण,
	 अणु171, 113पूर्ण,
	 अणु171, 107पूर्ण,
	 अणु171, 99पूर्ण,
	 अणु139, 120पूर्ण,
	 अणु139, 113पूर्ण,
	 अणु139, 107पूर्ण,
	 अणु139, 99पूर्ण,
	 अणु107, 120पूर्ण,
	 अणु107, 113पूर्ण,
	 अणु107, 107पूर्ण,
	 अणु107, 99पूर्ण,
	 अणु75, 120पूर्ण,
	 अणु75, 113पूर्ण,
	 अणु75, 107पूर्ण,
	 अणु75, 99पूर्ण,
	 अणु43, 120पूर्ण,
	 अणु43, 113पूर्ण,
	 अणु43, 107पूर्ण,
	 अणु43, 99पूर्ण,
	 अणु11, 120पूर्ण,
	 अणु11, 113पूर्ण,
	 अणु11, 107पूर्ण,
	 अणु11, 99पूर्ण,
	 अणु131, 107पूर्ण,
	 अणु131, 99पूर्ण,
	 अणु99, 120पूर्ण,
	 अणु99, 113पूर्ण,
	 अणु99, 107पूर्ण,
	 अणु99, 99पूर्ण,
	 अणु67, 120पूर्ण,
	 अणु67, 113पूर्ण,
	 अणु67, 107पूर्ण,
	 अणु67, 99पूर्ण,
	 अणु35, 120पूर्ण,
	 अणु35, 113पूर्ण,
	 अणु35, 107पूर्ण,
	 अणु35, 99पूर्ण,
	 अणु3, 120पूर्ण		/* 5.x GHz, lowest घातer */
	पूर्ण
पूर्ण;

अटल अंतरभूत u8
il3945_hw_reg_fix_घातer_idx(पूर्णांक idx)
अणु
	अगर (idx < 0)
		वापस 0;
	अगर (idx >= IL_MAX_GAIN_ENTRIES)
		वापस IL_MAX_GAIN_ENTRIES - 1;
	वापस (u8) idx;
पूर्ण

/* Kick off thermal recalibration check every 60 seconds */
#घोषणा REG_RECALIB_PERIOD (60)

/*
 * il3945_hw_reg_set_scan_घातer - Set Tx घातer क्रम scan probe requests
 *
 * Set (in our channel info database) the direct scan Tx घातer क्रम 1 Mbit (CCK)
 * or 6 Mbit (OFDM) rates.
 */
अटल व्योम
il3945_hw_reg_set_scan_घातer(काष्ठा il_priv *il, u32 scan_tbl_idx, s32 rate_idx,
			     स्थिर s8 *clip_pwrs,
			     काष्ठा il_channel_info *ch_info, पूर्णांक band_idx)
अणु
	काष्ठा il3945_scan_घातer_info *scan_घातer_info;
	s8 घातer;
	u8 घातer_idx;

	scan_घातer_info = &ch_info->scan_pwr_info[scan_tbl_idx];

	/* use this channel group's 6Mbit clipping/saturation pwr,
	 *   but cap at regulatory scan घातer restriction (set during init
	 *   based on eeprom channel data) क्रम this channel.  */
	घातer = min(ch_info->scan_घातer, clip_pwrs[RATE_6M_IDX_TBL]);

	घातer = min(घातer, il->tx_घातer_user_lmt);
	scan_घातer_info->requested_घातer = घातer;

	/* find dअगरference between new scan *घातer* and current "normal"
	 *   Tx *घातer* क्रम 6Mb.  Use this dअगरference (x2) to adjust the
	 *   current "normal" temperature-compensated Tx घातer *idx* क्रम
	 *   this rate (1Mb or 6Mb) to yield new temp-compensated scan घातer
	 *   *idx*. */
	घातer_idx =
	    ch_info->घातer_info[rate_idx].घातer_table_idx - (घातer -
							     ch_info->
							     घातer_info
							     [RATE_6M_IDX_TBL].
							     requested_घातer) *
	    2;

	/* store reference idx that we use when adjusting *all* scan
	 *   घातers.  So we can accommodate user (all channel) or spectrum
	 *   management (single channel) घातer changes "between" temperature
	 *   feedback compensation procedures.
	 * करोn't क्रमce fit this reference idx पूर्णांकo gain table; it may be a
	 *   negative number.  This will help aव्योम errors when we're at
	 *   the lower bounds (highest gains, क्रम warmest temperatures)
	 *   of the table. */

	/* करोn't exceed table bounds क्रम "real" setting */
	घातer_idx = il3945_hw_reg_fix_घातer_idx(घातer_idx);

	scan_घातer_info->घातer_table_idx = घातer_idx;
	scan_घातer_info->tpc.tx_gain =
	    घातer_gain_table[band_idx][घातer_idx].tx_gain;
	scan_घातer_info->tpc.dsp_atten =
	    घातer_gain_table[band_idx][घातer_idx].dsp_atten;
पूर्ण

/*
 * il3945_send_tx_घातer - fill in Tx Power command with gain settings
 *
 * Configures घातer settings क्रम all rates क्रम the current channel,
 * using values from channel info काष्ठा, and send to NIC
 */
अटल पूर्णांक
il3945_send_tx_घातer(काष्ठा il_priv *il)
अणु
	पूर्णांक rate_idx, i;
	स्थिर काष्ठा il_channel_info *ch_info = शून्य;
	काष्ठा il3945_txघातertable_cmd txघातer = अणु
		.channel = il->active.channel,
	पूर्ण;
	u16 chan;

	अगर (WARN_ONCE
	    (test_bit(S_SCAN_HW, &il->status),
	     "TX Power requested while scanning!\n"))
		वापस -EAGAIN;

	chan = le16_to_cpu(il->active.channel);

	txघातer.band = (il->band == NL80211_BAND_5GHZ) ? 0 : 1;
	ch_info = il_get_channel_info(il, il->band, chan);
	अगर (!ch_info) अणु
		IL_ERR("Failed to get channel info for channel %d [%d]\n", chan,
		       il->band);
		वापस -EINVAL;
	पूर्ण

	अगर (!il_is_channel_valid(ch_info)) अणु
		D_POWER("Not calling TX_PWR_TBL_CMD on " "non-Tx channel.\n");
		वापस 0;
	पूर्ण

	/* fill cmd with घातer settings क्रम all rates क्रम current channel */
	/* Fill OFDM rate */
	क्रम (rate_idx = IL_FIRST_OFDM_RATE, i = 0;
	     rate_idx <= IL39_LAST_OFDM_RATE; rate_idx++, i++) अणु

		txघातer.घातer[i].tpc = ch_info->घातer_info[i].tpc;
		txघातer.घातer[i].rate = il3945_rates[rate_idx].plcp;

		D_POWER("ch %d:%d rf %d dsp %3d rate code 0x%02x\n",
			le16_to_cpu(txघातer.channel), txघातer.band,
			txघातer.घातer[i].tpc.tx_gain,
			txघातer.घातer[i].tpc.dsp_atten, txघातer.घातer[i].rate);
	पूर्ण
	/* Fill CCK rates */
	क्रम (rate_idx = IL_FIRST_CCK_RATE; rate_idx <= IL_LAST_CCK_RATE;
	     rate_idx++, i++) अणु
		txघातer.घातer[i].tpc = ch_info->घातer_info[i].tpc;
		txघातer.घातer[i].rate = il3945_rates[rate_idx].plcp;

		D_POWER("ch %d:%d rf %d dsp %3d rate code 0x%02x\n",
			le16_to_cpu(txघातer.channel), txघातer.band,
			txघातer.घातer[i].tpc.tx_gain,
			txघातer.घातer[i].tpc.dsp_atten, txघातer.घातer[i].rate);
	पूर्ण

	वापस il_send_cmd_pdu(il, C_TX_PWR_TBL,
			       माप(काष्ठा il3945_txघातertable_cmd),
			       &txघातer);

पूर्ण

/*
 * il3945_hw_reg_set_new_घातer - Configures घातer tables at new levels
 * @ch_info: Channel to update.  Uses घातer_info.requested_घातer.
 *
 * Replace requested_घातer and base_घातer_idx ch_info fields क्रम
 * one channel.
 *
 * Called अगर user or spectrum management changes घातer preferences.
 * Takes पूर्णांकo account h/w and modulation limitations (clip घातer).
 *
 * This करोes *not* send anything to NIC, just sets up ch_info क्रम one channel.
 *
 * NOTE: reg_compensate_क्रम_temperature_dअगर() *must* be run after this to
 *	 properly fill out the scan घातers, and actual h/w gain settings,
 *	 and send changes to NIC
 */
अटल पूर्णांक
il3945_hw_reg_set_new_घातer(काष्ठा il_priv *il, काष्ठा il_channel_info *ch_info)
अणु
	काष्ठा il3945_channel_घातer_info *घातer_info;
	पूर्णांक घातer_changed = 0;
	पूर्णांक i;
	स्थिर s8 *clip_pwrs;
	पूर्णांक घातer;

	/* Get this chnlgrp's rate-to-max/clip-घातers table */
	clip_pwrs = il->_3945.clip_groups[ch_info->group_idx].clip_घातers;

	/* Get this channel's rate-to-current-घातer settings table */
	घातer_info = ch_info->घातer_info;

	/* update OFDM Txघातer settings */
	क्रम (i = RATE_6M_IDX_TBL; i <= RATE_54M_IDX_TBL; i++, ++घातer_info) अणु
		पूर्णांक delta_idx;

		/* limit new घातer to be no more than h/w capability */
		घातer = min(ch_info->curr_txघात, clip_pwrs[i]);
		अगर (घातer == घातer_info->requested_घातer)
			जारी;

		/* find dअगरference between old and new requested घातers,
		 *    update base (non-temp-compensated) घातer idx */
		delta_idx = (घातer - घातer_info->requested_घातer) * 2;
		घातer_info->base_घातer_idx -= delta_idx;

		/* save new requested घातer value */
		घातer_info->requested_घातer = घातer;

		घातer_changed = 1;
	पूर्ण

	/* update CCK Txघातer settings, based on OFDM 12M setting ...
	 *    ... all CCK घातer settings क्रम a given channel are the *same*. */
	अगर (घातer_changed) अणु
		घातer =
		    ch_info->घातer_info[RATE_12M_IDX_TBL].requested_घातer +
		    IL_CCK_FROM_OFDM_POWER_DIFF;

		/* करो all CCK rates' il3945_channel_घातer_info काष्ठाures */
		क्रम (i = RATE_1M_IDX_TBL; i <= RATE_11M_IDX_TBL; i++) अणु
			घातer_info->requested_घातer = घातer;
			घातer_info->base_घातer_idx =
			    ch_info->घातer_info[RATE_12M_IDX_TBL].
			    base_घातer_idx + IL_CCK_FROM_OFDM_IDX_DIFF;
			++घातer_info;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * il3945_hw_reg_get_ch_txघातer_limit - वापसs new घातer limit क्रम channel
 *
 * NOTE: Returned घातer limit may be less (but not more) than requested,
 *	 based strictly on regulatory (eeprom and spectrum mgt) limitations
 *	 (no consideration क्रम h/w clipping limitations).
 */
अटल पूर्णांक
il3945_hw_reg_get_ch_txघातer_limit(काष्ठा il_channel_info *ch_info)
अणु
	s8 max_घातer;

#अगर 0
	/* अगर we're using TGd limits, use lower of TGd or EEPROM */
	अगर (ch_info->tgd_data.max_घातer != 0)
		max_घातer =
		    min(ch_info->tgd_data.max_घातer,
			ch_info->eeprom.max_घातer_avg);

	/* अन्यथा just use EEPROM limits */
	अन्यथा
#पूर्ण_अगर
		max_घातer = ch_info->eeprom.max_घातer_avg;

	वापस min(max_घातer, ch_info->max_घातer_avg);
पूर्ण

/*
 * il3945_hw_reg_comp_txघातer_temp - Compensate क्रम temperature
 *
 * Compensate txघातer settings of *all* channels क्रम temperature.
 * This only accounts क्रम the dअगरference between current temperature
 *   and the factory calibration temperatures, and bases the new settings
 *   on the channel's base_घातer_idx.
 *
 * If RxOn is "associated", this sends the new Txघातer to NIC!
 */
अटल पूर्णांक
il3945_hw_reg_comp_txघातer_temp(काष्ठा il_priv *il)
अणु
	काष्ठा il_channel_info *ch_info = शून्य;
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;
	पूर्णांक delta_idx;
	स्थिर s8 *clip_pwrs;	/* array of h/w max घातer levels क्रम each rate */
	u8 a_band;
	u8 rate_idx;
	u8 scan_tbl_idx;
	u8 i;
	पूर्णांक ref_temp;
	पूर्णांक temperature = il->temperature;

	अगर (il->disable_tx_घातer_cal || test_bit(S_SCANNING, &il->status)) अणु
		/* करो not perक्रमm tx घातer calibration */
		वापस 0;
	पूर्ण
	/* set up new Tx घातer info क्रम each and every channel, 2.4 and 5.x */
	क्रम (i = 0; i < il->channel_count; i++) अणु
		ch_info = &il->channel_info[i];
		a_band = il_is_channel_a_band(ch_info);

		/* Get this chnlgrp's factory calibration temperature */
		ref_temp = (s16) eeprom->groups[ch_info->group_idx].temperature;

		/* get घातer idx adjusपंचांगent based on current and factory
		 * temps */
		delta_idx =
		    il3945_hw_reg_adjust_घातer_by_temp(temperature, ref_temp);

		/* set tx घातer value क्रम all rates, OFDM and CCK */
		क्रम (rate_idx = 0; rate_idx < RATE_COUNT_3945; rate_idx++) अणु
			पूर्णांक घातer_idx =
			    ch_info->घातer_info[rate_idx].base_घातer_idx;

			/* temperature compensate */
			घातer_idx += delta_idx;

			/* stay within table range */
			घातer_idx = il3945_hw_reg_fix_घातer_idx(घातer_idx);
			ch_info->घातer_info[rate_idx].घातer_table_idx =
			    (u8) घातer_idx;
			ch_info->घातer_info[rate_idx].tpc =
			    घातer_gain_table[a_band][घातer_idx];
		पूर्ण

		/* Get this chnlgrp's rate-to-max/clip-घातers table */
		clip_pwrs =
		    il->_3945.clip_groups[ch_info->group_idx].clip_घातers;

		/* set scan tx घातer, 1Mbit क्रम CCK, 6Mbit क्रम OFDM */
		क्रम (scan_tbl_idx = 0; scan_tbl_idx < IL_NUM_SCAN_RATES;
		     scan_tbl_idx++) अणु
			s32 actual_idx =
			    (scan_tbl_idx ==
			     0) ? RATE_1M_IDX_TBL : RATE_6M_IDX_TBL;
			il3945_hw_reg_set_scan_घातer(il, scan_tbl_idx,
						     actual_idx, clip_pwrs,
						     ch_info, a_band);
		पूर्ण
	पूर्ण

	/* send Txघातer command क्रम current channel to ucode */
	वापस il->ops->send_tx_घातer(il);
पूर्ण

पूर्णांक
il3945_hw_reg_set_txघातer(काष्ठा il_priv *il, s8 घातer)
अणु
	काष्ठा il_channel_info *ch_info;
	s8 max_घातer;
	u8 i;

	अगर (il->tx_घातer_user_lmt == घातer) अणु
		D_POWER("Requested Tx power same as current " "limit: %ddBm.\n",
			घातer);
		वापस 0;
	पूर्ण

	D_POWER("Setting upper limit clamp to %ddBm.\n", घातer);
	il->tx_घातer_user_lmt = घातer;

	/* set up new Tx घातers क्रम each and every channel, 2.4 and 5.x */

	क्रम (i = 0; i < il->channel_count; i++) अणु
		ch_info = &il->channel_info[i];

		/* find minimum घातer of all user and regulatory स्थिरraपूर्णांकs
		 *    (करोes not consider h/w clipping limitations) */
		max_घातer = il3945_hw_reg_get_ch_txघातer_limit(ch_info);
		max_घातer = min(घातer, max_घातer);
		अगर (max_घातer != ch_info->curr_txघात) अणु
			ch_info->curr_txघात = max_घातer;

			/* this considers the h/w clipping limitations */
			il3945_hw_reg_set_new_घातer(il, ch_info);
		पूर्ण
	पूर्ण

	/* update txघातer settings क्रम all channels,
	 *   send to NIC अगर associated. */
	il3945_is_temp_calib_needed(il);
	il3945_hw_reg_comp_txघातer_temp(il);

	वापस 0;
पूर्ण

अटल पूर्णांक
il3945_send_rxon_assoc(काष्ठा il_priv *il)
अणु
	पूर्णांक rc = 0;
	काष्ठा il_rx_pkt *pkt;
	काष्ठा il3945_rxon_assoc_cmd rxon_assoc;
	काष्ठा il_host_cmd cmd = अणु
		.id = C_RXON_ASSOC,
		.len = माप(rxon_assoc),
		.flags = CMD_WANT_SKB,
		.data = &rxon_assoc,
	पूर्ण;
	स्थिर काष्ठा il_rxon_cmd *rxon1 = &il->staging;
	स्थिर काष्ठा il_rxon_cmd *rxon2 = &il->active;

	अगर (rxon1->flags == rxon2->flags &&
	    rxon1->filter_flags == rxon2->filter_flags &&
	    rxon1->cck_basic_rates == rxon2->cck_basic_rates &&
	    rxon1->ofdm_basic_rates == rxon2->ofdm_basic_rates) अणु
		D_INFO("Using current RXON_ASSOC.  Not resending.\n");
		वापस 0;
	पूर्ण

	rxon_assoc.flags = il->staging.flags;
	rxon_assoc.filter_flags = il->staging.filter_flags;
	rxon_assoc.ofdm_basic_rates = il->staging.ofdm_basic_rates;
	rxon_assoc.cck_basic_rates = il->staging.cck_basic_rates;
	rxon_assoc.reserved = 0;

	rc = il_send_cmd_sync(il, &cmd);
	अगर (rc)
		वापस rc;

	pkt = (काष्ठा il_rx_pkt *)cmd.reply_page;
	अगर (pkt->hdr.flags & IL_CMD_FAILED_MSK) अणु
		IL_ERR("Bad return from C_RXON_ASSOC command\n");
		rc = -EIO;
	पूर्ण

	il_मुक्त_pages(il, cmd.reply_page);

	वापस rc;
पूर्ण

/*
 * il3945_commit_rxon - commit staging_rxon to hardware
 *
 * The RXON command in staging_rxon is committed to the hardware and
 * the active_rxon काष्ठाure is updated with the new data.  This
 * function correctly transitions out of the RXON_ASSOC_MSK state अगर
 * a HW tune is required based on the RXON काष्ठाure changes.
 */
पूर्णांक
il3945_commit_rxon(काष्ठा il_priv *il)
अणु
	/* cast away the स्थिर क्रम active_rxon in this function */
	काष्ठा il3945_rxon_cmd *active_rxon = (व्योम *)&il->active;
	काष्ठा il3945_rxon_cmd *staging_rxon = (व्योम *)&il->staging;
	पूर्णांक rc = 0;
	bool new_assoc = !!(staging_rxon->filter_flags & RXON_FILTER_ASSOC_MSK);

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस -EINVAL;

	अगर (!il_is_alive(il))
		वापस -1;

	/* always get बारtamp with Rx frame */
	staging_rxon->flags |= RXON_FLG_TSF2HOST_MSK;

	/* select antenna */
	staging_rxon->flags &= ~(RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_SEL_MSK);
	staging_rxon->flags |= il3945_get_antenna_flags(il);

	rc = il_check_rxon_cmd(il);
	अगर (rc) अणु
		IL_ERR("Invalid RXON configuration.  Not committing.\n");
		वापस -EINVAL;
	पूर्ण

	/* If we करोn't need to send a full RXON, we can use
	 * il3945_rxon_assoc_cmd which is used to reconfigure filter
	 * and other flags क्रम the current radio configuration. */
	अगर (!il_full_rxon_required(il)) अणु
		rc = il_send_rxon_assoc(il);
		अगर (rc) अणु
			IL_ERR("Error setting RXON_ASSOC "
			       "configuration (%d).\n", rc);
			वापस rc;
		पूर्ण

		स_नकल(active_rxon, staging_rxon, माप(*active_rxon));
		/*
		 * We करो not commit tx घातer settings जबतक channel changing,
		 * करो it now अगर tx घातer changed.
		 */
		il_set_tx_घातer(il, il->tx_घातer_next, false);
		वापस 0;
	पूर्ण

	/* If we are currently associated and the new config requires
	 * an RXON_ASSOC and the new config wants the associated mask enabled,
	 * we must clear the associated from the active configuration
	 * beक्रमe we apply the new config */
	अगर (il_is_associated(il) && new_assoc) अणु
		D_INFO("Toggling associated bit on current RXON\n");
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;

		/*
		 * reserved4 and 5 could have been filled by the iwlcore code.
		 * Let's clear them beक्रमe pushing to the 3945.
		 */
		active_rxon->reserved4 = 0;
		active_rxon->reserved5 = 0;
		rc = il_send_cmd_pdu(il, C_RXON, माप(काष्ठा il3945_rxon_cmd),
				     &il->active);

		/* If the mask clearing failed then we set
		 * active_rxon back to what it was previously */
		अगर (rc) अणु
			active_rxon->filter_flags |= RXON_FILTER_ASSOC_MSK;
			IL_ERR("Error clearing ASSOC_MSK on current "
			       "configuration (%d).\n", rc);
			वापस rc;
		पूर्ण
		il_clear_ucode_stations(il);
		il_restore_stations(il);
	पूर्ण

	D_INFO("Sending RXON\n" "* with%s RXON_FILTER_ASSOC_MSK\n"
	       "* channel = %d\n" "* bssid = %pM\n", (new_assoc ? "" : "out"),
	       le16_to_cpu(staging_rxon->channel), staging_rxon->bssid_addr);

	/*
	 * reserved4 and 5 could have been filled by the iwlcore code.
	 * Let's clear them beक्रमe pushing to the 3945.
	 */
	staging_rxon->reserved4 = 0;
	staging_rxon->reserved5 = 0;

	il_set_rxon_hwcrypto(il, !il3945_mod_params.sw_crypto);

	/* Apply the new configuration */
	rc = il_send_cmd_pdu(il, C_RXON, माप(काष्ठा il3945_rxon_cmd),
			     staging_rxon);
	अगर (rc) अणु
		IL_ERR("Error setting new configuration (%d).\n", rc);
		वापस rc;
	पूर्ण

	स_नकल(active_rxon, staging_rxon, माप(*active_rxon));

	अगर (!new_assoc) अणु
		il_clear_ucode_stations(il);
		il_restore_stations(il);
	पूर्ण

	/* If we issue a new RXON command which required a tune then we must
	 * send a new TXPOWER command or we won't be able to Tx any frames */
	rc = il_set_tx_घातer(il, il->tx_घातer_next, true);
	अगर (rc) अणु
		IL_ERR("Error setting Tx power (%d).\n", rc);
		वापस rc;
	पूर्ण

	/* Init the hardware's rate fallback order based on the band */
	rc = il3945_init_hw_rate_table(il);
	अगर (rc) अणु
		IL_ERR("Error setting HW rate table: %02X\n", rc);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * il3945_reg_txघातer_periodic -  called when समय to check our temperature.
 *
 * -- reset periodic समयr
 * -- see अगर temp has changed enough to warrant re-calibration ... अगर so:
 *     -- correct coeffs क्रम temp (can reset temp समयr)
 *     -- save this temp as "last",
 *     -- send new set of gain settings to NIC
 * NOTE:  This should जारी working, even when we're not associated,
 *   so we can keep our पूर्णांकernal table of scan घातers current. */
व्योम
il3945_reg_txघातer_periodic(काष्ठा il_priv *il)
अणु
	/* This will kick in the "brute force"
	 * il3945_hw_reg_comp_txघातer_temp() below */
	अगर (!il3945_is_temp_calib_needed(il))
		जाओ reschedule;

	/* Set up a new set of temp-adjusted TxPowers, send to NIC.
	 * This is based *only* on current temperature,
	 * ignoring any previous घातer measurements */
	il3945_hw_reg_comp_txघातer_temp(il);

reschedule:
	queue_delayed_work(il->workqueue, &il->_3945.thermal_periodic,
			   REG_RECALIB_PERIOD * HZ);
पूर्ण

अटल व्योम
il3945_bg_reg_txघातer_periodic(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा il_priv *il = container_of(work, काष्ठा il_priv,
					  _3945.thermal_periodic.work);

	mutex_lock(&il->mutex);
	अगर (test_bit(S_EXIT_PENDING, &il->status) || il->txq == शून्य)
		जाओ out;

	il3945_reg_txघातer_periodic(il);
out:
	mutex_unlock(&il->mutex);
पूर्ण

/*
 * il3945_hw_reg_get_ch_grp_idx - find the channel-group idx (0-4) क्रम channel.
 *
 * This function is used when initializing channel-info काष्ठाs.
 *
 * NOTE: These channel groups करो *NOT* match the bands above!
 *	 These channel groups are based on factory-tested channels;
 *	 on A-band, EEPROM's "group frequency" entries represent the top
 *	 channel in each group 1-4.  Group 5 All B/G channels are in group 0.
 */
अटल u16
il3945_hw_reg_get_ch_grp_idx(काष्ठा il_priv *il,
			     स्थिर काष्ठा il_channel_info *ch_info)
अणु
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;
	काष्ठा il3945_eeprom_txघातer_group *ch_grp = &eeprom->groups[0];
	u8 group;
	u16 group_idx = 0;	/* based on factory calib frequencies */
	u8 grp_channel;

	/* Find the group idx क्रम the channel ... करोn't use idx 1(?) */
	अगर (il_is_channel_a_band(ch_info)) अणु
		क्रम (group = 1; group < 5; group++) अणु
			grp_channel = ch_grp[group].group_channel;
			अगर (ch_info->channel <= grp_channel) अणु
				group_idx = group;
				अवरोध;
			पूर्ण
		पूर्ण
		/* group 4 has a few channels *above* its factory cal freq */
		अगर (group == 5)
			group_idx = 4;
	पूर्ण अन्यथा
		group_idx = 0;	/* 2.4 GHz, group 0 */

	D_POWER("Chnl %d mapped to grp %d\n", ch_info->channel, group_idx);
	वापस group_idx;
पूर्ण

/*
 * il3945_hw_reg_get_matched_घातer_idx - Interpolate to get nominal idx
 *
 * Interpolate to get nominal (i.e. at factory calibration temperature) idx
 *   पूर्णांकo radio/DSP gain settings table क्रम requested घातer.
 */
अटल पूर्णांक
il3945_hw_reg_get_matched_घातer_idx(काष्ठा il_priv *il, s8 requested_घातer,
				    s32 setting_idx, s32 *new_idx)
अणु
	स्थिर काष्ठा il3945_eeprom_txघातer_group *chnl_grp = शून्य;
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;
	s32 idx0, idx1;
	s32 घातer = 2 * requested_घातer;
	s32 i;
	स्थिर काष्ठा il3945_eeprom_txघातer_sample *samples;
	s32 gains0, gains1;
	s32 res;
	s32 denominator;

	chnl_grp = &eeprom->groups[setting_idx];
	samples = chnl_grp->samples;
	क्रम (i = 0; i < 5; i++) अणु
		अगर (घातer == samples[i].घातer) अणु
			*new_idx = samples[i].gain_idx;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (घातer > samples[1].घातer) अणु
		idx0 = 0;
		idx1 = 1;
	पूर्ण अन्यथा अगर (घातer > samples[2].घातer) अणु
		idx0 = 1;
		idx1 = 2;
	पूर्ण अन्यथा अगर (घातer > samples[3].घातer) अणु
		idx0 = 2;
		idx1 = 3;
	पूर्ण अन्यथा अणु
		idx0 = 3;
		idx1 = 4;
	पूर्ण

	denominator = (s32) samples[idx1].घातer - (s32) samples[idx0].घातer;
	अगर (denominator == 0)
		वापस -EINVAL;
	gains0 = (s32) samples[idx0].gain_idx * (1 << 19);
	gains1 = (s32) samples[idx1].gain_idx * (1 << 19);
	res =
	    gains0 + (gains1 - gains0) * ((s32) घातer -
					  (s32) samples[idx0].घातer) /
	    denominator + (1 << 18);
	*new_idx = res >> 19;
	वापस 0;
पूर्ण

अटल व्योम
il3945_hw_reg_init_channel_groups(काष्ठा il_priv *il)
अणु
	u32 i;
	s32 rate_idx;
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;
	स्थिर काष्ठा il3945_eeprom_txघातer_group *group;

	D_POWER("Initializing factory calib info from EEPROM\n");

	क्रम (i = 0; i < IL_NUM_TX_CALIB_GROUPS; i++) अणु
		s8 *clip_pwrs;	/* table of घातer levels क्रम each rate */
		s8 satur_pwr;	/* saturation घातer क्रम each chnl group */
		group = &eeprom->groups[i];

		/* sanity check on factory saturation घातer value */
		अगर (group->saturation_घातer < 40) अणु
			IL_WARN("Error: saturation power is %d, "
				"less than minimum expected 40\n",
				group->saturation_घातer);
			वापस;
		पूर्ण

		/*
		 * Derive requested घातer levels क्रम each rate, based on
		 *   hardware capabilities (saturation घातer क्रम band).
		 * Basic value is 3dB करोwn from saturation, with further
		 *   घातer reductions क्रम highest 3 data rates.  These
		 *   backoffs provide headroom क्रम high rate modulation
		 *   घातer peaks, without too much distortion (clipping).
		 */
		/* we'll fill in this array with h/w max घातer levels */
		clip_pwrs = (s8 *) il->_3945.clip_groups[i].clip_घातers;

		/* भागide factory saturation घातer by 2 to find -3dB level */
		satur_pwr = (s8) (group->saturation_घातer >> 1);

		/* fill in channel group's nominal घातers क्रम each rate */
		क्रम (rate_idx = 0; rate_idx < RATE_COUNT_3945;
		     rate_idx++, clip_pwrs++) अणु
			चयन (rate_idx) अणु
			हाल RATE_36M_IDX_TBL:
				अगर (i == 0)	/* B/G */
					*clip_pwrs = satur_pwr;
				अन्यथा	/* A */
					*clip_pwrs = satur_pwr - 5;
				अवरोध;
			हाल RATE_48M_IDX_TBL:
				अगर (i == 0)
					*clip_pwrs = satur_pwr - 7;
				अन्यथा
					*clip_pwrs = satur_pwr - 10;
				अवरोध;
			हाल RATE_54M_IDX_TBL:
				अगर (i == 0)
					*clip_pwrs = satur_pwr - 9;
				अन्यथा
					*clip_pwrs = satur_pwr - 12;
				अवरोध;
			शेष:
				*clip_pwrs = satur_pwr;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * il3945_txघातer_set_from_eeprom - Set channel घातer info based on EEPROM
 *
 * Second pass (during init) to set up il->channel_info
 *
 * Set up Tx-घातer settings in our channel info database क्रम each VALID
 * (क्रम this geo/SKU) channel, at all Tx data rates, based on eeprom values
 * and current temperature.
 *
 * Since this is based on current temperature (at init समय), these values may
 * not be valid क्रम very दीर्घ, but it gives us a starting/शेष poपूर्णांक,
 * and allows us to active (i.e. using Tx) scan.
 *
 * This करोes *not* ग_लिखो values to NIC, just sets up our पूर्णांकernal table.
 */
पूर्णांक
il3945_txघातer_set_from_eeprom(काष्ठा il_priv *il)
अणु
	काष्ठा il_channel_info *ch_info = शून्य;
	काष्ठा il3945_channel_घातer_info *pwr_info;
	काष्ठा il3945_eeprom *eeprom = (काष्ठा il3945_eeprom *)il->eeprom;
	पूर्णांक delta_idx;
	u8 rate_idx;
	u8 scan_tbl_idx;
	स्थिर s8 *clip_pwrs;	/* array of घातer levels क्रम each rate */
	u8 gain, dsp_atten;
	s8 घातer;
	u8 pwr_idx, base_pwr_idx, a_band;
	u8 i;
	पूर्णांक temperature;

	/* save temperature reference,
	 *   so we can determine next समय to calibrate */
	temperature = il3945_hw_reg_txघातer_get_temperature(il);
	il->last_temperature = temperature;

	il3945_hw_reg_init_channel_groups(il);

	/* initialize Tx घातer info क्रम each and every channel, 2.4 and 5.x */
	क्रम (i = 0, ch_info = il->channel_info; i < il->channel_count;
	     i++, ch_info++) अणु
		a_band = il_is_channel_a_band(ch_info);
		अगर (!il_is_channel_valid(ch_info))
			जारी;

		/* find this channel's channel group (*not* "band") idx */
		ch_info->group_idx = il3945_hw_reg_get_ch_grp_idx(il, ch_info);

		/* Get this chnlgrp's rate->max/clip-घातers table */
		clip_pwrs =
		    il->_3945.clip_groups[ch_info->group_idx].clip_घातers;

		/* calculate घातer idx *adjusपंचांगent* value according to
		 *  dअगरf between current temperature and factory temperature */
		delta_idx =
		    il3945_hw_reg_adjust_घातer_by_temp(temperature,
						       eeprom->groups[ch_info->
								      group_idx].
						       temperature);

		D_POWER("Delta idx for channel %d: %d [%d]\n", ch_info->channel,
			delta_idx, temperature + IL_TEMP_CONVERT);

		/* set tx घातer value क्रम all OFDM rates */
		क्रम (rate_idx = 0; rate_idx < IL_OFDM_RATES; rate_idx++) अणु
			s32 घातer_idx;
			पूर्णांक rc;

			/* use channel group's clip-घातer table,
			 *   but करोn't exceed channel's max घातer */
			s8 pwr = min(ch_info->max_घातer_avg,
				     clip_pwrs[rate_idx]);

			pwr_info = &ch_info->घातer_info[rate_idx];

			/* get base (i.e. at factory-measured temperature)
			 *    घातer table idx क्रम this rate's घातer */
			rc = il3945_hw_reg_get_matched_घातer_idx(il, pwr,
								 ch_info->
								 group_idx,
								 &घातer_idx);
			अगर (rc) अणु
				IL_ERR("Invalid power idx\n");
				वापस rc;
			पूर्ण
			pwr_info->base_घातer_idx = (u8) घातer_idx;

			/* temperature compensate */
			घातer_idx += delta_idx;

			/* stay within range of gain table */
			घातer_idx = il3945_hw_reg_fix_घातer_idx(घातer_idx);

			/* fill 1 OFDM rate's il3945_channel_घातer_info काष्ठा */
			pwr_info->requested_घातer = pwr;
			pwr_info->घातer_table_idx = (u8) घातer_idx;
			pwr_info->tpc.tx_gain =
			    घातer_gain_table[a_band][घातer_idx].tx_gain;
			pwr_info->tpc.dsp_atten =
			    घातer_gain_table[a_band][घातer_idx].dsp_atten;
		पूर्ण

		/* set tx घातer क्रम CCK rates, based on OFDM 12 Mbit settings */
		pwr_info = &ch_info->घातer_info[RATE_12M_IDX_TBL];
		घातer = pwr_info->requested_घातer + IL_CCK_FROM_OFDM_POWER_DIFF;
		pwr_idx = pwr_info->घातer_table_idx + IL_CCK_FROM_OFDM_IDX_DIFF;
		base_pwr_idx =
		    pwr_info->base_घातer_idx + IL_CCK_FROM_OFDM_IDX_DIFF;

		/* stay within table range */
		pwr_idx = il3945_hw_reg_fix_घातer_idx(pwr_idx);
		gain = घातer_gain_table[a_band][pwr_idx].tx_gain;
		dsp_atten = घातer_gain_table[a_band][pwr_idx].dsp_atten;

		/* fill each CCK rate's il3945_channel_घातer_info काष्ठाure
		 * NOTE:  All CCK-rate Txpwrs are the same क्रम a given chnl!
		 * NOTE:  CCK rates start at end of OFDM rates! */
		क्रम (rate_idx = 0; rate_idx < IL_CCK_RATES; rate_idx++) अणु
			pwr_info =
			    &ch_info->घातer_info[rate_idx + IL_OFDM_RATES];
			pwr_info->requested_घातer = घातer;
			pwr_info->घातer_table_idx = pwr_idx;
			pwr_info->base_घातer_idx = base_pwr_idx;
			pwr_info->tpc.tx_gain = gain;
			pwr_info->tpc.dsp_atten = dsp_atten;
		पूर्ण

		/* set scan tx घातer, 1Mbit क्रम CCK, 6Mbit क्रम OFDM */
		क्रम (scan_tbl_idx = 0; scan_tbl_idx < IL_NUM_SCAN_RATES;
		     scan_tbl_idx++) अणु
			s32 actual_idx =
			    (scan_tbl_idx ==
			     0) ? RATE_1M_IDX_TBL : RATE_6M_IDX_TBL;
			il3945_hw_reg_set_scan_घातer(il, scan_tbl_idx,
						     actual_idx, clip_pwrs,
						     ch_info, a_band);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
il3945_hw_rxq_stop(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;

	_il_wr(il, FH39_RCSR_CONFIG(0), 0);
	ret = _il_poll_bit(il, FH39_RSSR_STATUS,
			   FH39_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
			   FH39_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
			   1000);
	अगर (ret < 0)
		IL_ERR("Can't stop Rx DMA.\n");

	वापस 0;
पूर्ण

पूर्णांक
il3945_hw_tx_queue_init(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq)
अणु
	पूर्णांक txq_id = txq->q.id;

	काष्ठा il3945_shared *shared_data = il->_3945.shared_virt;

	shared_data->tx_base_ptr[txq_id] = cpu_to_le32((u32) txq->q.dma_addr);

	il_wr(il, FH39_CBCC_CTRL(txq_id), 0);
	il_wr(il, FH39_CBCC_BASE(txq_id), 0);

	il_wr(il, FH39_TCSR_CONFIG(txq_id),
	      FH39_TCSR_TX_CONFIG_REG_VAL_CIRQ_RTC_NOINT |
	      FH39_TCSR_TX_CONFIG_REG_VAL_MSG_MODE_TXF |
	      FH39_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_IFTFD |
	      FH39_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE_VAL |
	      FH39_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE);

	/* fake पढ़ो to flush all prev. ग_लिखोs */
	_il_rd(il, FH39_TSSR_CBB_BASE);

	वापस 0;
पूर्ण

/*
 * HCMD utils
 */
अटल u16
il3945_get_hcmd_size(u8 cmd_id, u16 len)
अणु
	चयन (cmd_id) अणु
	हाल C_RXON:
		वापस माप(काष्ठा il3945_rxon_cmd);
	हाल C_POWER_TBL:
		वापस माप(काष्ठा il3945_घातertable_cmd);
	शेष:
		वापस len;
	पूर्ण
पूर्ण

अटल u16
il3945_build_addsta_hcmd(स्थिर काष्ठा il_addsta_cmd *cmd, u8 * data)
अणु
	काष्ठा il3945_addsta_cmd *addsta = (काष्ठा il3945_addsta_cmd *)data;
	addsta->mode = cmd->mode;
	स_नकल(&addsta->sta, &cmd->sta, माप(काष्ठा sta_id_modअगरy));
	स_नकल(&addsta->key, &cmd->key, माप(काष्ठा il4965_keyinfo));
	addsta->station_flags = cmd->station_flags;
	addsta->station_flags_msk = cmd->station_flags_msk;
	addsta->tid_disable_tx = cpu_to_le16(0);
	addsta->rate_n_flags = cmd->rate_n_flags;
	addsta->add_immediate_ba_tid = cmd->add_immediate_ba_tid;
	addsta->हटाओ_immediate_ba_tid = cmd->हटाओ_immediate_ba_tid;
	addsta->add_immediate_ba_ssn = cmd->add_immediate_ba_ssn;

	वापस (u16) माप(काष्ठा il3945_addsta_cmd);
पूर्ण

अटल पूर्णांक
il3945_add_bssid_station(काष्ठा il_priv *il, स्थिर u8 * addr, u8 * sta_id_r)
अणु
	पूर्णांक ret;
	u8 sta_id;
	अचिन्हित दीर्घ flags;

	अगर (sta_id_r)
		*sta_id_r = IL_INVALID_STATION;

	ret = il_add_station_common(il, addr, 0, शून्य, &sta_id);
	अगर (ret) अणु
		IL_ERR("Unable to add station %pM\n", addr);
		वापस ret;
	पूर्ण

	अगर (sta_id_r)
		*sta_id_r = sta_id;

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].used |= IL_STA_LOCAL;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
il3945_manage_ibss_station(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर,
			   bool add)
अणु
	काष्ठा il_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;

	अगर (add) अणु
		ret =
		    il3945_add_bssid_station(il, vअगर->bss_conf.bssid,
					     &vअगर_priv->ibss_bssid_sta_id);
		अगर (ret)
			वापस ret;

		il3945_sync_sta(il, vअगर_priv->ibss_bssid_sta_id,
				(il->band ==
				 NL80211_BAND_5GHZ) ? RATE_6M_PLCP :
				RATE_1M_PLCP);
		il3945_rate_scale_init(il->hw, vअगर_priv->ibss_bssid_sta_id);

		वापस 0;
	पूर्ण

	वापस il_हटाओ_station(il, vअगर_priv->ibss_bssid_sta_id,
				 vअगर->bss_conf.bssid);
पूर्ण

/*
 * il3945_init_hw_rate_table - Initialize the hardware rate fallback table
 */
पूर्णांक
il3945_init_hw_rate_table(काष्ठा il_priv *il)
अणु
	पूर्णांक rc, i, idx, prev_idx;
	काष्ठा il3945_rate_scaling_cmd rate_cmd = अणु
		.reserved = अणु0, 0, 0पूर्ण,
	पूर्ण;
	काष्ठा il3945_rate_scaling_info *table = rate_cmd.table;

	क्रम (i = 0; i < ARRAY_SIZE(il3945_rates); i++) अणु
		idx = il3945_rates[i].table_rs_idx;

		table[idx].rate_n_flags = cpu_to_le16(il3945_rates[i].plcp);
		table[idx].try_cnt = il->retry_rate;
		prev_idx = il3945_get_prev_ieee_rate(i);
		table[idx].next_rate_idx = il3945_rates[prev_idx].table_rs_idx;
	पूर्ण

	चयन (il->band) अणु
	हाल NL80211_BAND_5GHZ:
		D_RATE("Select A mode rate scale\n");
		/* If one of the following CCK rates is used,
		 * have it fall back to the 6M OFDM rate */
		क्रम (i = RATE_1M_IDX_TBL; i <= RATE_11M_IDX_TBL; i++)
			table[i].next_rate_idx =
			    il3945_rates[IL_FIRST_OFDM_RATE].table_rs_idx;

		/* Don't fall back to CCK rates */
		table[RATE_12M_IDX_TBL].next_rate_idx = RATE_9M_IDX_TBL;

		/* Don't drop out of OFDM rates */
		table[RATE_6M_IDX_TBL].next_rate_idx =
		    il3945_rates[IL_FIRST_OFDM_RATE].table_rs_idx;
		अवरोध;

	हाल NL80211_BAND_2GHZ:
		D_RATE("Select B/G mode rate scale\n");
		/* If an OFDM rate is used, have it fall back to the
		 * 1M CCK rates */

		अगर (!(il->_3945.sta_supp_rates & IL_OFDM_RATES_MASK) &&
		    il_is_associated(il)) अणु

			idx = IL_FIRST_CCK_RATE;
			क्रम (i = RATE_6M_IDX_TBL; i <= RATE_54M_IDX_TBL; i++)
				table[i].next_rate_idx =
				    il3945_rates[idx].table_rs_idx;

			idx = RATE_11M_IDX_TBL;
			/* CCK shouldn't fall back to OFDM... */
			table[idx].next_rate_idx = RATE_5M_IDX_TBL;
		पूर्ण
		अवरोध;

	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	/* Update the rate scaling क्रम control frame Tx */
	rate_cmd.table_id = 0;
	rc = il_send_cmd_pdu(il, C_RATE_SCALE, माप(rate_cmd), &rate_cmd);
	अगर (rc)
		वापस rc;

	/* Update the rate scaling क्रम data frame Tx */
	rate_cmd.table_id = 1;
	वापस il_send_cmd_pdu(il, C_RATE_SCALE, माप(rate_cmd), &rate_cmd);
पूर्ण

/* Called when initializing driver */
पूर्णांक
il3945_hw_set_hw_params(काष्ठा il_priv *il)
अणु
	स_रखो((व्योम *)&il->hw_params, 0, माप(काष्ठा il_hw_params));

	il->_3945.shared_virt =
	    dma_alloc_coherent(&il->pci_dev->dev, माप(काष्ठा il3945_shared),
			       &il->_3945.shared_phys, GFP_KERNEL);
	अगर (!il->_3945.shared_virt)
		वापस -ENOMEM;

	il->hw_params.bcast_id = IL3945_BROADCAST_ID;

	/* Assign number of Usable TX queues */
	il->hw_params.max_txq_num = il->cfg->num_of_queues;

	il->hw_params.tfd_size = माप(काष्ठा il3945_tfd);
	il->hw_params.rx_page_order = get_order(IL_RX_BUF_SIZE_3K);
	il->hw_params.max_rxq_size = RX_QUEUE_SIZE;
	il->hw_params.max_rxq_log = RX_QUEUE_SIZE_LOG;
	il->hw_params.max_stations = IL3945_STATION_COUNT;

	il->sta_key_max_num = STA_KEY_MAX_NUM;

	il->hw_params.rx_wrt_ptr_reg = FH39_RSCSR_CHNL0_WPTR;
	il->hw_params.max_beacon_itrvl = IL39_MAX_UCODE_BEACON_INTERVAL;
	il->hw_params.beacon_समय_प्रकारsf_bits = IL3945_EXT_BEACON_TIME_POS;

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक
il3945_hw_get_beacon_cmd(काष्ठा il_priv *il, काष्ठा il3945_frame *frame,
			 u8 rate)
अणु
	काष्ठा il3945_tx_beacon_cmd *tx_beacon_cmd;
	अचिन्हित पूर्णांक frame_size;

	tx_beacon_cmd = (काष्ठा il3945_tx_beacon_cmd *)&frame->u;
	स_रखो(tx_beacon_cmd, 0, माप(*tx_beacon_cmd));

	tx_beacon_cmd->tx.sta_id = il->hw_params.bcast_id;
	tx_beacon_cmd->tx.stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;

	frame_size =
	    il3945_fill_beacon_frame(il, tx_beacon_cmd->frame,
				     माप(frame->u) - माप(*tx_beacon_cmd));

	BUG_ON(frame_size > MAX_MPDU_SIZE);
	tx_beacon_cmd->tx.len = cpu_to_le16((u16) frame_size);

	tx_beacon_cmd->tx.rate = rate;
	tx_beacon_cmd->tx.tx_flags =
	    (TX_CMD_FLG_SEQ_CTL_MSK | TX_CMD_FLG_TSF_MSK);

	/* supp_rates[0] == OFDM start at IL_FIRST_OFDM_RATE */
	tx_beacon_cmd->tx.supp_rates[0] =
	    (IL_OFDM_BASIC_RATES_MASK >> IL_FIRST_OFDM_RATE) & 0xFF;

	tx_beacon_cmd->tx.supp_rates[1] = (IL_CCK_BASIC_RATES_MASK & 0xF);

	वापस माप(काष्ठा il3945_tx_beacon_cmd) + frame_size;
पूर्ण

व्योम
il3945_hw_handler_setup(काष्ठा il_priv *il)
अणु
	il->handlers[C_TX] = il3945_hdl_tx;
	il->handlers[N_3945_RX] = il3945_hdl_rx;
पूर्ण

व्योम
il3945_hw_setup_deferred_work(काष्ठा il_priv *il)
अणु
	INIT_DELAYED_WORK(&il->_3945.thermal_periodic,
			  il3945_bg_reg_txघातer_periodic);
पूर्ण

व्योम
il3945_hw_cancel_deferred_work(काष्ठा il_priv *il)
अणु
	cancel_delayed_work(&il->_3945.thermal_periodic);
पूर्ण

/* check contents of special bootstrap uCode SRAM */
अटल पूर्णांक
il3945_verअगरy_bsm(काष्ठा il_priv *il)
अणु
	__le32 *image = il->ucode_boot.v_addr;
	u32 len = il->ucode_boot.len;
	u32 reg;
	u32 val;

	D_INFO("Begin verify bsm\n");

	/* verअगरy BSM SRAM contents */
	val = il_rd_prph(il, BSM_WR_DWCOUNT_REG);
	क्रम (reg = BSM_SRAM_LOWER_BOUND; reg < BSM_SRAM_LOWER_BOUND + len;
	     reg += माप(u32), image++) अणु
		val = il_rd_prph(il, reg);
		अगर (val != le32_to_cpu(*image)) अणु
			IL_ERR("BSM uCode verification failed at "
			       "addr 0x%08X+%u (of %u), is 0x%x, s/b 0x%x\n",
			       BSM_SRAM_LOWER_BOUND, reg - BSM_SRAM_LOWER_BOUND,
			       len, val, le32_to_cpu(*image));
			वापस -EIO;
		पूर्ण
	पूर्ण

	D_INFO("BSM bootstrap uCode image OK\n");

	वापस 0;
पूर्ण

/******************************************************************************
 *
 * EEPROM related functions
 *
 ******************************************************************************/

/*
 * Clear the OWNER_MSK, to establish driver (instead of uCode running on
 * embedded controller) as EEPROM पढ़ोer; each पढ़ो is a series of pulses
 * to/from the EEPROM chip, not a single event, so even पढ़ोs could conflict
 * अगर they weren't arbitrated by some ownership mechanism.  Here, the driver
 * simply claims ownership, which should be safe when this function is called
 * (i.e. beक्रमe loading uCode!).
 */
अटल पूर्णांक
il3945_eeprom_acquire_semaphore(काष्ठा il_priv *il)
अणु
	_il_clear_bit(il, CSR_EEPROM_GP, CSR_EEPROM_GP_IF_OWNER_MSK);
	वापस 0;
पूर्ण

अटल व्योम
il3945_eeprom_release_semaphore(काष्ठा il_priv *il)
अणु
	वापस;
पूर्ण

 /*
  * il3945_load_bsm - Load bootstrap inकाष्ठाions
  *
  * BSM operation:
  *
  * The Bootstrap State Machine (BSM) stores a लघु bootstrap uCode program
  * in special SRAM that करोes not घातer करोwn during RFKILL.  When घातering back
  * up after घातer-saving sleeps (or during initial uCode load), the BSM loads
  * the bootstrap program पूर्णांकo the on-board processor, and starts it.
  *
  * The bootstrap program loads (via DMA) inकाष्ठाions and data क्रम a new
  * program from host DRAM locations indicated by the host driver in the
  * BSM_DRAM_* रेजिस्टरs.  Once the new program is loaded, it starts
  * स्वतःmatically.
  *
  * When initializing the NIC, the host driver poपूर्णांकs the BSM to the
  * "initialize" uCode image.  This uCode sets up some पूर्णांकernal data, then
  * notअगरies host via "initialize alive" that it is complete.
  *
  * The host then replaces the BSM_DRAM_* poपूर्णांकer values to poपूर्णांक to the
  * normal runसमय uCode inकाष्ठाions and a backup uCode data cache buffer
  * (filled initially with starting data values क्रम the on-board processor),
  * then triggers the "initialize" uCode to load and launch the runसमय uCode,
  * which begins normal operation.
  *
  * When करोing a घातer-save shutकरोwn, runसमय uCode saves data SRAM पूर्णांकo
  * the backup data cache in DRAM beक्रमe SRAM is घातered करोwn.
  *
  * When घातering back up, the BSM loads the bootstrap program.  This reloads
  * the runसमय uCode inकाष्ठाions and the backup data cache पूर्णांकo SRAM,
  * and re-launches the runसमय uCode from where it left off.
  */
अटल पूर्णांक
il3945_load_bsm(काष्ठा il_priv *il)
अणु
	__le32 *image = il->ucode_boot.v_addr;
	u32 len = il->ucode_boot.len;
	dma_addr_t pinst;
	dma_addr_t pdata;
	u32 inst_len;
	u32 data_len;
	पूर्णांक rc;
	पूर्णांक i;
	u32 करोne;
	u32 reg_offset;

	D_INFO("Begin load bsm\n");

	/* make sure bootstrap program is no larger than BSM's SRAM size */
	अगर (len > IL39_MAX_BSM_SIZE)
		वापस -EINVAL;

	/* Tell bootstrap uCode where to find the "Initialize" uCode
	 *   in host DRAM ... host DRAM physical address bits 31:0 क्रम 3945.
	 * NOTE:  il3945_initialize_alive_start() will replace these values,
	 *        after the "initialize" uCode has run, to poपूर्णांक to
	 *        runसमय/protocol inकाष्ठाions and backup data cache. */
	pinst = il->ucode_init.p_addr;
	pdata = il->ucode_init_data.p_addr;
	inst_len = il->ucode_init.len;
	data_len = il->ucode_init_data.len;

	il_wr_prph(il, BSM_DRAM_INST_PTR_REG, pinst);
	il_wr_prph(il, BSM_DRAM_DATA_PTR_REG, pdata);
	il_wr_prph(il, BSM_DRAM_INST_BYTECOUNT_REG, inst_len);
	il_wr_prph(il, BSM_DRAM_DATA_BYTECOUNT_REG, data_len);

	/* Fill BSM memory with bootstrap inकाष्ठाions */
	क्रम (reg_offset = BSM_SRAM_LOWER_BOUND;
	     reg_offset < BSM_SRAM_LOWER_BOUND + len;
	     reg_offset += माप(u32), image++)
		_il_wr_prph(il, reg_offset, le32_to_cpu(*image));

	rc = il3945_verअगरy_bsm(il);
	अगर (rc)
		वापस rc;

	/* Tell BSM to copy from BSM SRAM पूर्णांकo inकाष्ठाion SRAM, when asked */
	il_wr_prph(il, BSM_WR_MEM_SRC_REG, 0x0);
	il_wr_prph(il, BSM_WR_MEM_DST_REG, IL39_RTC_INST_LOWER_BOUND);
	il_wr_prph(il, BSM_WR_DWCOUNT_REG, len / माप(u32));

	/* Load bootstrap code पूर्णांकo inकाष्ठाion SRAM now,
	 *   to prepare to load "initialize" uCode */
	il_wr_prph(il, BSM_WR_CTRL_REG, BSM_WR_CTRL_REG_BIT_START);

	/* Wait क्रम load of bootstrap uCode to finish */
	क्रम (i = 0; i < 100; i++) अणु
		करोne = il_rd_prph(il, BSM_WR_CTRL_REG);
		अगर (!(करोne & BSM_WR_CTRL_REG_BIT_START))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i < 100)
		D_INFO("BSM write complete, poll %d iterations\n", i);
	अन्यथा अणु
		IL_ERR("BSM write did not complete!\n");
		वापस -EIO;
	पूर्ण

	/* Enable future boot loads whenever घातer management unit triggers it
	 *   (e.g. when घातering back up after घातer-save shutकरोwn) */
	il_wr_prph(il, BSM_WR_CTRL_REG, BSM_WR_CTRL_REG_BIT_START_EN);

	वापस 0;
पूर्ण

स्थिर काष्ठा il_ops il3945_ops = अणु
	.txq_attach_buf_to_tfd = il3945_hw_txq_attach_buf_to_tfd,
	.txq_मुक्त_tfd = il3945_hw_txq_मुक्त_tfd,
	.txq_init = il3945_hw_tx_queue_init,
	.load_ucode = il3945_load_bsm,
	.dump_nic_error_log = il3945_dump_nic_error_log,
	.apm_init = il3945_apm_init,
	.send_tx_घातer = il3945_send_tx_घातer,
	.is_valid_rtc_data_addr = il3945_hw_valid_rtc_data_addr,
	.eeprom_acquire_semaphore = il3945_eeprom_acquire_semaphore,
	.eeprom_release_semaphore = il3945_eeprom_release_semaphore,

	.rxon_assoc = il3945_send_rxon_assoc,
	.commit_rxon = il3945_commit_rxon,

	.get_hcmd_size = il3945_get_hcmd_size,
	.build_addsta_hcmd = il3945_build_addsta_hcmd,
	.request_scan = il3945_request_scan,
	.post_scan = il3945_post_scan,

	.post_associate = il3945_post_associate,
	.config_ap = il3945_config_ap,
	.manage_ibss_station = il3945_manage_ibss_station,

	.send_led_cmd = il3945_send_led_cmd,
पूर्ण;

अटल स्थिर काष्ठा il_cfg il3945_bg_cfg = अणु
	.name = "3945BG",
	.fw_name_pre = IL3945_FW_PRE,
	.ucode_api_max = IL3945_UCODE_API_MAX,
	.ucode_api_min = IL3945_UCODE_API_MIN,
	.sku = IL_SKU_G,
	.eeprom_ver = EEPROM_3945_EEPROM_VERSION,
	.mod_params = &il3945_mod_params,
	.led_mode = IL_LED_BLINK,

	.eeprom_size = IL3945_EEPROM_IMG_SIZE,
	.num_of_queues = IL39_NUM_QUEUES,
	.pll_cfg_val = CSR39_ANA_PLL_CFG_VAL,
	.set_l0s = false,
	.use_bsm = true,
	.led_compensation = 64,
	.wd_समयout = IL_DEF_WD_TIMEOUT,

	.regulatory_bands = अणु
		EEPROM_REGULATORY_BAND_1_CHANNELS,
		EEPROM_REGULATORY_BAND_2_CHANNELS,
		EEPROM_REGULATORY_BAND_3_CHANNELS,
		EEPROM_REGULATORY_BAND_4_CHANNELS,
		EEPROM_REGULATORY_BAND_5_CHANNELS,
		EEPROM_REGULATORY_BAND_NO_HT40,
		EEPROM_REGULATORY_BAND_NO_HT40,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा il_cfg il3945_abg_cfg = अणु
	.name = "3945ABG",
	.fw_name_pre = IL3945_FW_PRE,
	.ucode_api_max = IL3945_UCODE_API_MAX,
	.ucode_api_min = IL3945_UCODE_API_MIN,
	.sku = IL_SKU_A | IL_SKU_G,
	.eeprom_ver = EEPROM_3945_EEPROM_VERSION,
	.mod_params = &il3945_mod_params,
	.led_mode = IL_LED_BLINK,

	.eeprom_size = IL3945_EEPROM_IMG_SIZE,
	.num_of_queues = IL39_NUM_QUEUES,
	.pll_cfg_val = CSR39_ANA_PLL_CFG_VAL,
	.set_l0s = false,
	.use_bsm = true,
	.led_compensation = 64,
	.wd_समयout = IL_DEF_WD_TIMEOUT,

	.regulatory_bands = अणु
		EEPROM_REGULATORY_BAND_1_CHANNELS,
		EEPROM_REGULATORY_BAND_2_CHANNELS,
		EEPROM_REGULATORY_BAND_3_CHANNELS,
		EEPROM_REGULATORY_BAND_4_CHANNELS,
		EEPROM_REGULATORY_BAND_5_CHANNELS,
		EEPROM_REGULATORY_BAND_NO_HT40,
		EEPROM_REGULATORY_BAND_NO_HT40,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा pci_device_id il3945_hw_card_ids[] = अणु
	अणुIL_PCI_DEVICE(0x4222, 0x1005, il3945_bg_cfg)पूर्ण,
	अणुIL_PCI_DEVICE(0x4222, 0x1034, il3945_bg_cfg)पूर्ण,
	अणुIL_PCI_DEVICE(0x4222, 0x1044, il3945_bg_cfg)पूर्ण,
	अणुIL_PCI_DEVICE(0x4227, 0x1014, il3945_bg_cfg)पूर्ण,
	अणुIL_PCI_DEVICE(0x4222, PCI_ANY_ID, il3945_abg_cfg)पूर्ण,
	अणुIL_PCI_DEVICE(0x4227, PCI_ANY_ID, il3945_abg_cfg)पूर्ण,
	अणु0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, il3945_hw_card_ids);
