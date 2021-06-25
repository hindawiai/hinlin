<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: rxtx.c
 *
 * Purpose: handle WMAC/802.3/802.11 rx & tx functions
 *
 * Author: Lynकरोn Chen
 *
 * Date: May 20, 2003
 *
 * Functions:
 *      vnt_generate_tx_parameter - Generate tx dma required parameter.
 *      vnt_get_rsvसमय- get frame reserved समय
 *      vnt_fill_cts_head- fulfill CTS ctl header
 *
 * Revision History:
 *
 */

#समावेश <linux/etherdevice.h>
#समावेश "device.h"
#समावेश "rxtx.h"
#समावेश "card.h"
#समावेश "mac.h"
#समावेश "rf.h"
#समावेश "usbpipe.h"

अटल स्थिर u16 vnt_समय_stampoff[2][MAX_RATE] = अणु
	/* Long Preamble */
	अणु384, 288, 226, 209, 54, 43, 37, 31, 28, 25, 24, 23पूर्ण,

	/* Short Preamble */
	अणु384, 192, 130, 113, 54, 43, 37, 31, 28, 25, 24, 23पूर्ण,
पूर्ण;

#घोषणा DATADUR_B       10
#घोषणा DATADUR_A       11

अटल स्थिर u8 vnt_phy_संकेत[] = अणु
	0x00,	/* RATE_1M  */
	0x01,	/* RATE_2M  */
	0x02,	/* RATE_5M  */
	0x03,	/* RATE_11M */
	0x8b,	/* RATE_6M  */
	0x8f,	/* RATE_9M  */
	0x8a,	/* RATE_12M */
	0x8e,	/* RATE_18M */
	0x89,	/* RATE_24M */
	0x8d,	/* RATE_36M */
	0x88,	/* RATE_48M */
	0x8c	/* RATE_54M */
पूर्ण;

अटल काष्ठा vnt_usb_send_context
	*vnt_get_मुक्त_context(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा vnt_usb_send_context *context = शून्य;
	पूर्णांक ii;

	dev_dbg(&priv->usb->dev, "%s\n", __func__);

	क्रम (ii = 0; ii < priv->num_tx_context; ii++) अणु
		अगर (!priv->tx_context[ii])
			वापस शून्य;

		context = priv->tx_context[ii];
		अगर (!context->in_use) अणु
			context->in_use = true;
			वापस context;
		पूर्ण
	पूर्ण

	अगर (ii == priv->num_tx_context) अणु
		dev_dbg(&priv->usb->dev, "%s No Free Tx Context\n", __func__);

		ieee80211_stop_queues(priv->hw);
	पूर्ण

	वापस शून्य;
पूर्ण

/* Get Length, Service, and Signal fields of Phy क्रम Tx */
अटल व्योम vnt_get_phy_field(काष्ठा vnt_निजी *priv, u32 frame_length,
			      u16 tx_rate, u8 pkt_type,
			      काष्ठा vnt_phy_field *phy)
अणु
	u32 bit_count;
	u32 count = 0;
	u32 पंचांगp;
	पूर्णांक ext_bit;
	पूर्णांक i;
	u8 mask = 0;
	u8 preamble_type = priv->preamble_type;

	bit_count = frame_length * 8;
	ext_bit = false;

	चयन (tx_rate) अणु
	हाल RATE_1M:
		count = bit_count;
		अवरोध;
	हाल RATE_2M:
		count = bit_count / 2;
		अवरोध;
	हाल RATE_5M:
		count = DIV_ROUND_UP(bit_count * 10, 55);
		अवरोध;
	हाल RATE_11M:
		count = bit_count / 11;
		पंचांगp = count * 11;

		अगर (पंचांगp != bit_count) अणु
			count++;

			अगर ((bit_count - पंचांगp) <= 3)
				ext_bit = true;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (tx_rate > RATE_11M) अणु
		अगर (pkt_type == PK_TYPE_11A)
			mask = BIT(4);
	पूर्ण अन्यथा अगर (tx_rate > RATE_1M) अणु
		अगर (preamble_type == PREAMBLE_SHORT)
			mask = BIT(3);
	पूर्ण

	i = tx_rate > RATE_54M ? RATE_54M : tx_rate;
	phy->संकेत = vnt_phy_संकेत[i] | mask;
	phy->service = 0x00;

	अगर (pkt_type == PK_TYPE_11B) अणु
		अगर (ext_bit)
			phy->service |= 0x80;
		phy->len = cpu_to_le16((u16)count);
	पूर्ण अन्यथा अणु
		phy->len = cpu_to_le16((u16)frame_length);
	पूर्ण
पूर्ण

अटल __le16 vnt_समय_stamp_off(काष्ठा vnt_निजी *priv, u16 rate)
अणु
	वापस cpu_to_le16(vnt_समय_stampoff[priv->preamble_type % 2]
							[rate % MAX_RATE]);
पूर्ण

अटल __le16 vnt_rxtx_rsvसमय_le16(काष्ठा vnt_usb_send_context *context)
अणु
	काष्ठा vnt_निजी *priv = context->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(context->skb);
	काष्ठा ieee80211_rate *rate = ieee80211_get_tx_rate(priv->hw, info);

	वापस ieee80211_generic_frame_duration(priv->hw,
						 info->control.vअगर, info->band,
						 context->frame_len,
						 rate);
पूर्ण

अटल __le16 vnt_get_rts_duration(काष्ठा vnt_usb_send_context *context)
अणु
	काष्ठा vnt_निजी *priv = context->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(context->skb);

	वापस ieee80211_rts_duration(priv->hw, priv->vअगर,
				      context->frame_len, info);
पूर्ण

अटल __le16 vnt_get_cts_duration(काष्ठा vnt_usb_send_context *context)
अणु
	काष्ठा vnt_निजी *priv = context->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(context->skb);

	वापस ieee80211_ctstoself_duration(priv->hw, priv->vअगर,
					    context->frame_len, info);
पूर्ण

अटल व्योम vnt_rxtx_datahead_g(काष्ठा vnt_usb_send_context *tx_context,
				काष्ठा vnt_tx_datahead_g *buf)
अणु
	काष्ठा vnt_निजी *priv = tx_context->priv;
	काष्ठा ieee80211_hdr *hdr =
				(काष्ठा ieee80211_hdr *)tx_context->skb->data;
	u32 frame_len = tx_context->frame_len;
	u16 rate = tx_context->tx_rate;

	/* Get SignalField,ServiceField,Length */
	vnt_get_phy_field(priv, frame_len, rate, tx_context->pkt_type, &buf->a);
	vnt_get_phy_field(priv, frame_len, priv->top_cck_basic_rate,
			  PK_TYPE_11B, &buf->b);

	/* Get Duration and TimeStamp */
	buf->duration_a = hdr->duration_id;
	buf->duration_b = hdr->duration_id;
	buf->समय_stamp_off_a = vnt_समय_stamp_off(priv, rate);
	buf->समय_stamp_off_b = vnt_समय_stamp_off(priv,
						   priv->top_cck_basic_rate);
पूर्ण

अटल व्योम vnt_rxtx_datahead_ab(काष्ठा vnt_usb_send_context *tx_context,
				 काष्ठा vnt_tx_datahead_ab *buf)
अणु
	काष्ठा vnt_निजी *priv = tx_context->priv;
	काष्ठा ieee80211_hdr *hdr =
				(काष्ठा ieee80211_hdr *)tx_context->skb->data;
	u32 frame_len = tx_context->frame_len;
	u16 rate = tx_context->tx_rate;

	/* Get SignalField,ServiceField,Length */
	vnt_get_phy_field(priv, frame_len, rate,
			  tx_context->pkt_type, &buf->ab);

	/* Get Duration and TimeStampOff */
	buf->duration = hdr->duration_id;
	buf->समय_stamp_off = vnt_समय_stamp_off(priv, rate);
पूर्ण

अटल व्योम vnt_fill_ieee80211_rts(काष्ठा vnt_usb_send_context *tx_context,
				   काष्ठा ieee80211_rts *rts, __le16 duration)
अणु
	काष्ठा ieee80211_hdr *hdr =
				(काष्ठा ieee80211_hdr *)tx_context->skb->data;

	rts->duration = duration;
	rts->frame_control =
		cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_RTS);

	ether_addr_copy(rts->ra, hdr->addr1);
	ether_addr_copy(rts->ta, hdr->addr2);
पूर्ण

अटल व्योम vnt_rxtx_rts_g_head(काष्ठा vnt_usb_send_context *tx_context,
				काष्ठा vnt_rts_g *buf)
अणु
	काष्ठा vnt_निजी *priv = tx_context->priv;
	u16 rts_frame_len = 20;

	vnt_get_phy_field(priv, rts_frame_len, priv->top_cck_basic_rate,
			  PK_TYPE_11B, &buf->b);
	vnt_get_phy_field(priv, rts_frame_len, priv->top_ofdm_basic_rate,
			  tx_context->pkt_type, &buf->a);

	buf->duration_bb = vnt_get_rts_duration(tx_context);
	buf->duration_aa = buf->duration_bb;
	buf->duration_ba = buf->duration_bb;

	vnt_fill_ieee80211_rts(tx_context, &buf->data, buf->duration_aa);

	vnt_rxtx_datahead_g(tx_context, &buf->data_head);
पूर्ण

अटल व्योम vnt_rxtx_rts_ab_head(काष्ठा vnt_usb_send_context *tx_context,
				 काष्ठा vnt_rts_ab *buf)
अणु
	काष्ठा vnt_निजी *priv = tx_context->priv;
	u16 rts_frame_len = 20;

	vnt_get_phy_field(priv, rts_frame_len, priv->top_ofdm_basic_rate,
			  tx_context->pkt_type, &buf->ab);

	buf->duration = vnt_get_rts_duration(tx_context);

	vnt_fill_ieee80211_rts(tx_context, &buf->data, buf->duration);

	vnt_rxtx_datahead_ab(tx_context, &buf->data_head);
पूर्ण

अटल व्योम vnt_fill_cts_head(काष्ठा vnt_usb_send_context *tx_context,
			      जोड़ vnt_tx_data_head *head)
अणु
	काष्ठा vnt_निजी *priv = tx_context->priv;
	काष्ठा vnt_cts *buf = &head->cts_g;
	u32 cts_frame_len = 14;

	/* Get SignalField,ServiceField,Length */
	vnt_get_phy_field(priv, cts_frame_len, priv->top_cck_basic_rate,
			  PK_TYPE_11B, &buf->b);
	/* Get CTSDuration_ba */
	buf->duration_ba = vnt_get_cts_duration(tx_context);
	/*Get CTS Frame body*/
	buf->data.duration = buf->duration_ba;
	buf->data.frame_control =
		cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_CTS);

	ether_addr_copy(buf->data.ra, priv->current_net_addr);

	vnt_rxtx_datahead_g(tx_context, &buf->data_head);
पूर्ण

/* वापसs true अगर mic_hdr is needed */
अटल bool vnt_fill_txkey(काष्ठा vnt_tx_buffer *tx_buffer, काष्ठा sk_buff *skb)
अणु
	काष्ठा vnt_tx_fअगरo_head *fअगरo = &tx_buffer->fअगरo_head;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_key_conf *tx_key = info->control.hw_key;
	काष्ठा vnt_mic_hdr *mic_hdr;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	u64 pn64;
	u16 payload_len = skb->len;
	u8 *iv = ((u8 *)hdr + ieee80211_get_hdrlen_from_skb(skb));

	/* strip header and icv len from payload */
	payload_len -= ieee80211_get_hdrlen_from_skb(skb);
	payload_len -= tx_key->icv_len;

	चयन (tx_key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		स_नकल(fअगरo->tx_key, iv, 3);
		स_नकल(fअगरo->tx_key + 3, tx_key->key, tx_key->keylen);

		अगर (tx_key->keylen == WLAN_KEY_LEN_WEP40) अणु
			स_नकल(fअगरo->tx_key + 8, iv, 3);
			स_नकल(fअगरo->tx_key + 11,
			       tx_key->key, WLAN_KEY_LEN_WEP40);
		पूर्ण

		fअगरo->frag_ctl |= cpu_to_le16(FRAGCTL_LEGACY);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		ieee80211_get_tkip_p2k(tx_key, skb, fअगरo->tx_key);

		fअगरo->frag_ctl |= cpu_to_le16(FRAGCTL_TKIP);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		अगर (info->control.use_cts_prot) अणु
			अगर (info->control.use_rts)
				mic_hdr = &tx_buffer->tx_head.tx_rts.tx.mic.hdr;
			अन्यथा
				mic_hdr = &tx_buffer->tx_head.tx_cts.tx.mic.hdr;
		पूर्ण अन्यथा अणु
			mic_hdr = &tx_buffer->tx_head.tx_ab.tx.mic.hdr;
		पूर्ण

		mic_hdr->id = 0x59;
		mic_hdr->payload_len = cpu_to_be16(payload_len);
		ether_addr_copy(mic_hdr->mic_addr2, hdr->addr2);

		pn64 = atomic64_पढ़ो(&tx_key->tx_pn);
		mic_hdr->ccmp_pn[5] = pn64;
		mic_hdr->ccmp_pn[4] = pn64 >> 8;
		mic_hdr->ccmp_pn[3] = pn64 >> 16;
		mic_hdr->ccmp_pn[2] = pn64 >> 24;
		mic_hdr->ccmp_pn[1] = pn64 >> 32;
		mic_hdr->ccmp_pn[0] = pn64 >> 40;

		अगर (ieee80211_has_a4(hdr->frame_control))
			mic_hdr->hlen = cpu_to_be16(28);
		अन्यथा
			mic_hdr->hlen = cpu_to_be16(22);

		ether_addr_copy(mic_hdr->addr1, hdr->addr1);
		ether_addr_copy(mic_hdr->addr2, hdr->addr2);
		ether_addr_copy(mic_hdr->addr3, hdr->addr3);

		mic_hdr->frame_control = cpu_to_le16(
			le16_to_cpu(hdr->frame_control) & 0xc78f);
		mic_hdr->seq_ctrl = cpu_to_le16(
				le16_to_cpu(hdr->seq_ctrl) & 0xf);

		अगर (ieee80211_has_a4(hdr->frame_control))
			ether_addr_copy(mic_hdr->addr4, hdr->addr4);

		स_नकल(fअगरo->tx_key, tx_key->key, WLAN_KEY_LEN_CCMP);

		fअगरo->frag_ctl |= cpu_to_le16(FRAGCTL_AES);
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम vnt_rxtx_rts(काष्ठा vnt_usb_send_context *tx_context)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_context->skb);
	काष्ठा vnt_tx_buffer *tx_buffer = tx_context->tx_buffer;
	जोड़ vnt_tx_head *tx_head = &tx_buffer->tx_head;
	काष्ठा vnt_rrv_समय_rts *buf = &tx_head->tx_rts.rts;
	जोड़ vnt_tx_data_head *head = &tx_head->tx_rts.tx.head;

	buf->rts_rrv_समय_aa = vnt_get_rts_duration(tx_context);
	buf->rts_rrv_समय_ba = buf->rts_rrv_समय_aa;
	buf->rts_rrv_समय_bb = buf->rts_rrv_समय_aa;

	buf->rrv_समय_a = vnt_rxtx_rsvसमय_le16(tx_context);
	buf->rrv_समय_b = buf->rrv_समय_a;

	अगर (info->control.hw_key) अणु
		अगर (vnt_fill_txkey(tx_buffer, tx_context->skb))
			head = &tx_head->tx_rts.tx.mic.head;
	पूर्ण

	vnt_rxtx_rts_g_head(tx_context, &head->rts_g);
पूर्ण

अटल व्योम vnt_rxtx_cts(काष्ठा vnt_usb_send_context *tx_context)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_context->skb);
	काष्ठा vnt_tx_buffer *tx_buffer = tx_context->tx_buffer;
	जोड़ vnt_tx_head *tx_head = &tx_buffer->tx_head;
	काष्ठा vnt_rrv_समय_cts *buf = &tx_head->tx_cts.cts;
	जोड़ vnt_tx_data_head *head = &tx_head->tx_cts.tx.head;

	buf->rrv_समय_a = vnt_rxtx_rsvसमय_le16(tx_context);
	buf->rrv_समय_b = buf->rrv_समय_a;

	buf->cts_rrv_समय_ba = vnt_get_cts_duration(tx_context);

	अगर (info->control.hw_key) अणु
		अगर (vnt_fill_txkey(tx_buffer, tx_context->skb))
			head = &tx_head->tx_cts.tx.mic.head;
	पूर्ण

	vnt_fill_cts_head(tx_context, head);
पूर्ण

अटल व्योम vnt_rxtx_ab(काष्ठा vnt_usb_send_context *tx_context)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_context->skb);
	काष्ठा vnt_tx_buffer *tx_buffer = tx_context->tx_buffer;
	जोड़ vnt_tx_head *tx_head = &tx_buffer->tx_head;
	काष्ठा vnt_rrv_समय_ab *buf = &tx_head->tx_ab.ab;
	जोड़ vnt_tx_data_head *head = &tx_head->tx_ab.tx.head;

	buf->rrv_समय = vnt_rxtx_rsvसमय_le16(tx_context);

	अगर (info->control.hw_key) अणु
		अगर (vnt_fill_txkey(tx_buffer, tx_context->skb))
			head = &tx_head->tx_ab.tx.mic.head;
	पूर्ण

	अगर (info->control.use_rts) अणु
		buf->rts_rrv_समय = vnt_get_rts_duration(tx_context);

		vnt_rxtx_rts_ab_head(tx_context, &head->rts_ab);

		वापस;
	पूर्ण

	vnt_rxtx_datahead_ab(tx_context, &head->data_head_ab);
पूर्ण

अटल व्योम vnt_generate_tx_parameter(काष्ठा vnt_usb_send_context *tx_context)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_context->skb);

	अगर (info->control.use_cts_prot) अणु
		अगर (info->control.use_rts) अणु
			vnt_rxtx_rts(tx_context);

			वापस;
		पूर्ण

		vnt_rxtx_cts(tx_context);

		वापस;
	पूर्ण

	vnt_rxtx_ab(tx_context);
पूर्ण

अटल u16 vnt_get_hdr_size(काष्ठा ieee80211_tx_info *info)
अणु
	u16 size = माप(काष्ठा vnt_tx_datahead_ab);

	अगर (info->control.use_cts_prot) अणु
		अगर (info->control.use_rts)
			size = माप(काष्ठा vnt_rts_g);
		अन्यथा
			size = माप(काष्ठा vnt_cts);
	पूर्ण अन्यथा अगर (info->control.use_rts) अणु
		size = माप(काष्ठा vnt_rts_ab);
	पूर्ण

	अगर (info->control.hw_key) अणु
		अगर (info->control.hw_key->cipher == WLAN_CIPHER_SUITE_CCMP)
			size += माप(काष्ठा vnt_mic_hdr);
	पूर्ण

	/* Get rrv_समय header */
	अगर (info->control.use_cts_prot) अणु
		अगर (info->control.use_rts)
			size += माप(काष्ठा vnt_rrv_समय_rts);
		अन्यथा
			size += माप(काष्ठा vnt_rrv_समय_cts);
	पूर्ण अन्यथा अणु
		size += माप(काष्ठा vnt_rrv_समय_ab);
	पूर्ण

	size += माप(काष्ठा vnt_tx_fअगरo_head);

	वापस size;
पूर्ण

पूर्णांक vnt_tx_packet(काष्ठा vnt_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *tx_rate = &info->control.rates[0];
	काष्ठा ieee80211_rate *rate;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा vnt_tx_buffer *tx_buffer;
	काष्ठा vnt_tx_fअगरo_head *tx_buffer_head;
	काष्ठा vnt_usb_send_context *tx_context;
	अचिन्हित दीर्घ flags;
	u8 pkt_type;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data);

	rate = ieee80211_get_tx_rate(priv->hw, info);

	अगर (rate->hw_value > RATE_11M) अणु
		अगर (info->band == NL80211_BAND_5GHZ) अणु
			pkt_type = PK_TYPE_11A;
		पूर्ण अन्यथा अणु
			अगर (tx_rate->flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
				अगर (priv->basic_rates & VNT_B_RATES)
					pkt_type = PK_TYPE_11GB;
				अन्यथा
					pkt_type = PK_TYPE_11GA;
			पूर्ण अन्यथा अणु
				pkt_type = PK_TYPE_11A;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		pkt_type = PK_TYPE_11B;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	tx_context = vnt_get_मुक्त_context(priv);
	अगर (!tx_context) अणु
		dev_dbg(&priv->usb->dev, "%s No free context\n", __func__);
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	tx_context->pkt_type = pkt_type;
	tx_context->frame_len = skb->len + 4;
	tx_context->tx_rate =  rate->hw_value;

	spin_unlock_irqrestore(&priv->lock, flags);

	tx_context->skb = skb_clone(skb, GFP_ATOMIC);
	अगर (!tx_context->skb) अणु
		tx_context->in_use = false;
		वापस -ENOMEM;
	पूर्ण

	tx_buffer = skb_push(skb, vnt_get_hdr_size(info));
	tx_context->tx_buffer = tx_buffer;
	tx_buffer_head = &tx_buffer->fअगरo_head;

	tx_context->type = CONTEXT_DATA_PACKET;

	/*Set fअगरo controls */
	अगर (pkt_type == PK_TYPE_11A)
		tx_buffer_head->fअगरo_ctl = 0;
	अन्यथा अगर (pkt_type == PK_TYPE_11B)
		tx_buffer_head->fअगरo_ctl = cpu_to_le16(FIFOCTL_11B);
	अन्यथा अगर (pkt_type == PK_TYPE_11GB)
		tx_buffer_head->fअगरo_ctl = cpu_to_le16(FIFOCTL_11GB);
	अन्यथा अगर (pkt_type == PK_TYPE_11GA)
		tx_buffer_head->fअगरo_ctl = cpu_to_le16(FIFOCTL_11GA);

	अगर (!ieee80211_is_data(hdr->frame_control)) अणु
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_GENINT |
							FIFOCTL_ISDMA0);
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_TMOEN);

		tx_buffer_head->समय_stamp =
			cpu_to_le16(DEFAULT_MGN_LIFETIME_RES_64us);
	पूर्ण अन्यथा अणु
		tx_buffer_head->समय_stamp =
			cpu_to_le16(DEFAULT_MSDU_LIFETIME_RES_64us);
	पूर्ण

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_NEEDACK);

	अगर (ieee80211_has_retry(hdr->frame_control))
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_LRETRY);

	अगर (info->control.use_rts)
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_RTS);

	अगर (ieee80211_has_a4(hdr->frame_control))
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_LHEAD);

	tx_buffer_head->frag_ctl =
			cpu_to_le16(ieee80211_hdrlen(hdr->frame_control) << 10);

	अगर (info->control.hw_key)
		tx_context->frame_len += info->control.hw_key->icv_len;

	tx_buffer_head->current_rate = cpu_to_le16(rate->hw_value);

	vnt_generate_tx_parameter(tx_context);

	tx_buffer_head->frag_ctl |= cpu_to_le16(FRAGCTL_NONFRAG);

	priv->seq_counter = (le16_to_cpu(hdr->seq_ctrl) &
						IEEE80211_SCTL_SEQ) >> 4;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (vnt_tx_context(priv, tx_context, skb)) अणु
		dev_kमुक्त_skb(tx_context->skb);
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस -EIO;
	पूर्ण

	dev_kमुक्त_skb(skb);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vnt_beacon_xmit(काष्ठा vnt_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा vnt_tx_लघु_buf_head *लघु_head;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा vnt_usb_send_context *context;
	काष्ठा ieee80211_mgmt *mgmt_hdr;
	अचिन्हित दीर्घ flags;
	u32 frame_size = skb->len + 4;
	u16 current_rate;

	spin_lock_irqsave(&priv->lock, flags);

	context = vnt_get_मुक्त_context(priv);
	अगर (!context) अणु
		dev_dbg(&priv->usb->dev, "%s No free context!\n", __func__);
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	context->skb = skb;

	spin_unlock_irqrestore(&priv->lock, flags);

	mgmt_hdr = (काष्ठा ieee80211_mgmt *)skb->data;
	लघु_head = skb_push(skb, माप(*लघु_head));

	अगर (priv->bb_type == BB_TYPE_11A) अणु
		current_rate = RATE_6M;

		/* Get SignalField,ServiceField,Length */
		vnt_get_phy_field(priv, frame_size, current_rate,
				  PK_TYPE_11A, &लघु_head->ab);

		/* Get TimeStampOff */
		लघु_head->समय_stamp_off =
				vnt_समय_stamp_off(priv, current_rate);
	पूर्ण अन्यथा अणु
		current_rate = RATE_1M;
		लघु_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_11B);

		/* Get SignalField,ServiceField,Length */
		vnt_get_phy_field(priv, frame_size, current_rate,
				  PK_TYPE_11B, &लघु_head->ab);

		/* Get TimeStampOff */
		लघु_head->समय_stamp_off =
			vnt_समय_stamp_off(priv, current_rate);
	पूर्ण

	/* Get Duration */
	लघु_head->duration = mgmt_hdr->duration;

	/* समय stamp always 0 */
	mgmt_hdr->u.beacon.बारtamp = 0;

	info = IEEE80211_SKB_CB(skb);
	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) अणु
		काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)mgmt_hdr;

		hdr->duration_id = 0;
		hdr->seq_ctrl = cpu_to_le16(priv->seq_counter << 4);
	पूर्ण

	priv->seq_counter++;
	अगर (priv->seq_counter > 0x0fff)
		priv->seq_counter = 0;

	context->type = CONTEXT_BEACON_PACKET;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (vnt_tx_context(priv, context, skb))
		ieee80211_मुक्त_txskb(priv->hw, context->skb);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक vnt_beacon_make(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *beacon;

	beacon = ieee80211_beacon_get(priv->hw, vअगर);
	अगर (!beacon)
		वापस -ENOMEM;

	अगर (vnt_beacon_xmit(priv, beacon)) अणु
		ieee80211_मुक्त_txskb(priv->hw, beacon);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vnt_beacon_enable(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_bss_conf *conf)
अणु
	vnt_mac_reg_bits_off(priv, MAC_REG_TCR, TCR_AUTOBCNTX);

	vnt_mac_reg_bits_off(priv, MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	vnt_mac_set_beacon_पूर्णांकerval(priv, conf->beacon_पूर्णांक);

	vnt_clear_current_tsf(priv);

	vnt_mac_reg_bits_on(priv, MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	vnt_reset_next_tbtt(priv, conf->beacon_पूर्णांक);

	वापस vnt_beacon_make(priv, vअगर);
पूर्ण
