<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/gfp.h>
#समावेश <net/mac80211.h>

#समावेश "wl1251.h"
#समावेश "reg.h"
#समावेश "io.h"
#समावेश "rx.h"
#समावेश "cmd.h"
#समावेश "acx.h"

अटल व्योम wl1251_rx_header(काष्ठा wl1251 *wl,
			     काष्ठा wl1251_rx_descriptor *desc)
अणु
	u32 rx_packet_ring_addr;

	rx_packet_ring_addr = wl->data_path->rx_packet_ring_addr;
	अगर (wl->rx_current_buffer)
		rx_packet_ring_addr += wl->data_path->rx_packet_ring_chunk_size;

	wl1251_mem_पढ़ो(wl, rx_packet_ring_addr, desc, माप(*desc));
पूर्ण

अटल व्योम wl1251_rx_status(काष्ठा wl1251 *wl,
			     काष्ठा wl1251_rx_descriptor *desc,
			     काष्ठा ieee80211_rx_status *status,
			     u8 beacon)
अणु
	u64 maस_समय;
	पूर्णांक ret;

	स_रखो(status, 0, माप(काष्ठा ieee80211_rx_status));

	status->band = NL80211_BAND_2GHZ;
	status->maस_समय = desc->बारtamp;

	/*
	 * The rx status बारtamp is a 32 bits value जबतक the TSF is a
	 * 64 bits one.
	 * For IBSS merging, TSF is mandatory, so we have to get it
	 * somehow, so we ask क्रम ACX_TSF_INFO.
	 * That could be moved to the get_tsf() hook, but unक्रमtunately,
	 * this one must be atomic, जबतक our SPI routines can sleep.
	 */
	अगर ((wl->bss_type == BSS_TYPE_IBSS) && beacon) अणु
		ret = wl1251_acx_tsf_info(wl, &maस_समय);
		अगर (ret == 0)
			status->maस_समय = maस_समय;
	पूर्ण

	status->संकेत = desc->rssi;

	/*
	 * FIXME: guessing that snr needs to be भागided by two, otherwise
	 * the values करोn't make any sense
	 */
	wl->noise = desc->rssi - desc->snr / 2;

	status->freq = ieee80211_channel_to_frequency(desc->channel,
						      status->band);

	status->flag |= RX_FLAG_MACTIME_START;

	अगर (!wl->monitor_present && (desc->flags & RX_DESC_ENCRYPTION_MASK)) अणु
		status->flag |= RX_FLAG_IV_STRIPPED | RX_FLAG_MMIC_STRIPPED;

		अगर (likely(!(desc->flags & RX_DESC_DECRYPT_FAIL)))
			status->flag |= RX_FLAG_DECRYPTED;

		अगर (unlikely(desc->flags & RX_DESC_MIC_FAIL))
			status->flag |= RX_FLAG_MMIC_ERROR;
	पूर्ण

	अगर (unlikely(!(desc->flags & RX_DESC_VALID_FCS)))
		status->flag |= RX_FLAG_FAILED_FCS_CRC;

	चयन (desc->rate) अणु
		/* skip 1 and 12 Mbps because they have same value 0x0a */
	हाल RATE_2MBPS:
		status->rate_idx = 1;
		अवरोध;
	हाल RATE_5_5MBPS:
		status->rate_idx = 2;
		अवरोध;
	हाल RATE_11MBPS:
		status->rate_idx = 3;
		अवरोध;
	हाल RATE_6MBPS:
		status->rate_idx = 4;
		अवरोध;
	हाल RATE_9MBPS:
		status->rate_idx = 5;
		अवरोध;
	हाल RATE_18MBPS:
		status->rate_idx = 7;
		अवरोध;
	हाल RATE_24MBPS:
		status->rate_idx = 8;
		अवरोध;
	हाल RATE_36MBPS:
		status->rate_idx = 9;
		अवरोध;
	हाल RATE_48MBPS:
		status->rate_idx = 10;
		अवरोध;
	हाल RATE_54MBPS:
		status->rate_idx = 11;
		अवरोध;
	पूर्ण

	/* क्रम 1 and 12 Mbps we have to check the modulation */
	अगर (desc->rate == RATE_1MBPS) अणु
		अगर (!(desc->mod_pre & OFDM_RATE_BIT))
			/* CCK -> RATE_1MBPS */
			status->rate_idx = 0;
		अन्यथा
			/* OFDM -> RATE_12MBPS */
			status->rate_idx = 6;
	पूर्ण

	अगर (desc->mod_pre & SHORT_PREAMBLE_BIT)
		status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
पूर्ण

अटल व्योम wl1251_rx_body(काष्ठा wl1251 *wl,
			   काष्ठा wl1251_rx_descriptor *desc)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_rx_status status;
	u8 *rx_buffer, beacon = 0;
	u16 length, *fc;
	u32 curr_id, last_id_inc, rx_packet_ring_addr;

	length = WL1251_RX_ALIGN(desc->length  - PLCP_HEADER_LENGTH);
	curr_id = (desc->flags & RX_DESC_SEQNUM_MASK) >> RX_DESC_PACKETID_SHIFT;
	last_id_inc = (wl->rx_last_id + 1) % (RX_MAX_PACKET_ID + 1);

	अगर (last_id_inc != curr_id) अणु
		wl1251_warning("curr ID:%d, last ID inc:%d",
			       curr_id, last_id_inc);
		wl->rx_last_id = curr_id;
	पूर्ण अन्यथा अणु
		wl->rx_last_id = last_id_inc;
	पूर्ण

	rx_packet_ring_addr = wl->data_path->rx_packet_ring_addr +
		माप(काष्ठा wl1251_rx_descriptor) + 20;
	अगर (wl->rx_current_buffer)
		rx_packet_ring_addr += wl->data_path->rx_packet_ring_chunk_size;

	skb = __dev_alloc_skb(length, GFP_KERNEL);
	अगर (!skb) अणु
		wl1251_error("Couldn't allocate RX frame");
		वापस;
	पूर्ण

	rx_buffer = skb_put(skb, length);
	wl1251_mem_पढ़ो(wl, rx_packet_ring_addr, rx_buffer, length);

	/* The actual length करोesn't include the target's alignment */
	skb_trim(skb, desc->length - PLCP_HEADER_LENGTH);

	fc = (u16 *)skb->data;

	अगर ((*fc & IEEE80211_FCTL_STYPE) == IEEE80211_STYPE_BEACON)
		beacon = 1;

	wl1251_rx_status(wl, desc, &status, beacon);

	wl1251_debug(DEBUG_RX, "rx skb 0x%p: %d B %s", skb, skb->len,
		     beacon ? "beacon" : "");

	स_नकल(IEEE80211_SKB_RXCB(skb), &status, माप(status));
	ieee80211_rx_ni(wl->hw, skb);
पूर्ण

अटल व्योम wl1251_rx_ack(काष्ठा wl1251 *wl)
अणु
	u32 data, addr;

	अगर (wl->rx_current_buffer) अणु
		addr = ACX_REG_INTERRUPT_TRIG_H;
		data = INTR_TRIG_RX_PROC1;
	पूर्ण अन्यथा अणु
		addr = ACX_REG_INTERRUPT_TRIG;
		data = INTR_TRIG_RX_PROC0;
	पूर्ण

	wl1251_reg_ग_लिखो32(wl, addr, data);

	/* Toggle buffer ring */
	wl->rx_current_buffer = !wl->rx_current_buffer;
पूर्ण


व्योम wl1251_rx(काष्ठा wl1251 *wl)
अणु
	काष्ठा wl1251_rx_descriptor *rx_desc;

	अगर (wl->state != WL1251_STATE_ON)
		वापस;

	rx_desc = wl->rx_descriptor;

	/* We first पढ़ो the frame's header */
	wl1251_rx_header(wl, rx_desc);

	/* Now we can पढ़ो the body */
	wl1251_rx_body(wl, rx_desc);

	/* Finally, we need to ACK the RX */
	wl1251_rx_ack(wl);
पूर्ण
