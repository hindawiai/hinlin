<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: dpc.c
 *
 * Purpose: handle dpc rx functions
 *
 * Author: Lynकरोn Chen
 *
 * Date: May 20, 2003
 *
 * Functions:
 *
 * Revision History:
 *
 */

#समावेश "device.h"
#समावेश "baseband.h"
#समावेश "rf.h"
#समावेश "dpc.h"

अटल bool vnt_rx_data(काष्ठा vnt_निजी *priv, काष्ठा sk_buff *skb,
			u16 bytes_received)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_rx_status rx_status = अणु 0 पूर्ण;
	काष्ठा ieee80211_hdr *hdr;
	__le16 fc;
	u8 *rsr, *new_rsr, *rssi;
	__le64 *tsf_समय;
	u16 frame_size;
	पूर्णांक ii, r;
	u8 *rx_rate;
	u8 *skb_data;
	u8 rate_idx = 0;
	u8 rate[MAX_RATE] = अणु2, 4, 11, 22, 12, 18, 24, 36, 48, 72, 96, 108पूर्ण;
	दीर्घ rx_dbm;

	/* [31:16]RcvByteCount ( not include 4-byte Status ) */
	frame_size = le16_to_cpu(*((__le16 *)(skb->data + 2)));
	अगर (frame_size > 2346 || frame_size < 14) अणु
		dev_dbg(&priv->pcid->dev, "------- WRONG Length 1\n");
		वापस false;
	पूर्ण

	skb_data = (u8 *)skb->data;

	rx_rate = skb_data + 1;

	sband = hw->wiphy->bands[hw->conf.chandef.chan->band];

	क्रम (r = RATE_1M; r < MAX_RATE; r++) अणु
		अगर (*rx_rate == rate[r])
			अवरोध;
	पूर्ण

	priv->rx_rate = r;

	क्रम (ii = 0; ii < sband->n_bitrates; ii++) अणु
		अगर (sband->bitrates[ii].hw_value == r) अणु
			rate_idx = ii;
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ii == sband->n_bitrates) अणु
		dev_dbg(&priv->pcid->dev, "Wrong RxRate %x\n", *rx_rate);
		वापस false;
	पूर्ण

	tsf_समय = (__le64 *)(skb_data + bytes_received - 12);
	new_rsr = skb_data + bytes_received - 3;
	rssi = skb_data + bytes_received - 2;
	rsr = skb_data + bytes_received - 1;
	अगर (*rsr & (RSR_IVLDTYP | RSR_IVLDLEN))
		वापस false;

	RFvRSSITodBm(priv, *rssi, &rx_dbm);

	priv->byBBPreEDRSSI = (u8)rx_dbm + 1;
	priv->uCurrRSSI = *rssi;

	skb_pull(skb, 4);
	skb_trim(skb, frame_size);

	rx_status.maस_समय = le64_to_cpu(*tsf_समय);
	rx_status.band = hw->conf.chandef.chan->band;
	rx_status.संकेत = rx_dbm;
	rx_status.flag = 0;
	rx_status.freq = hw->conf.chandef.chan->center_freq;

	अगर (!(*rsr & RSR_CRCOK))
		rx_status.flag |= RX_FLAG_FAILED_FCS_CRC;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	fc = hdr->frame_control;

	rx_status.rate_idx = rate_idx;

	अगर (ieee80211_has_रक्षित(fc)) अणु
		अगर (priv->byLocalID > REV_ID_VT3253_A1)
			rx_status.flag |= RX_FLAG_DECRYPTED;

		/* Drop packet */
		अगर (!(*new_rsr & NEWRSR_DECRYPTOK))
			वापस false;
	पूर्ण

	स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status, माप(rx_status));

	ieee80211_rx_irqsafe(priv->hw, skb);

	वापस true;
पूर्ण

bool vnt_receive_frame(काष्ठा vnt_निजी *priv, काष्ठा vnt_rx_desc *curr_rd)
अणु
	काष्ठा vnt_rd_info *rd_info = curr_rd->rd_info;
	काष्ठा sk_buff *skb;
	u16 frame_size;

	skb = rd_info->skb;

	dma_unmap_single(&priv->pcid->dev, rd_info->skb_dma,
			 priv->rx_buf_sz, DMA_FROM_DEVICE);

	frame_size = le16_to_cpu(curr_rd->rd1.req_count)
			- le16_to_cpu(curr_rd->rd0.res_count);

	अगर ((frame_size > 2364) || (frame_size < 33)) अणु
		/* Frame Size error drop this packet.*/
		dev_dbg(&priv->pcid->dev, "Wrong frame size %d\n", frame_size);
		dev_kमुक्त_skb_irq(skb);
		वापस true;
	पूर्ण

	अगर (vnt_rx_data(priv, skb, frame_size))
		वापस true;

	dev_kमुक्त_skb_irq(skb);

	वापस true;
पूर्ण
