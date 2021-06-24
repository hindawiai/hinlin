<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2010 Willow Garage <http://www.willowgarage.com>
	Copyright (C) 2004 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2004 - 2009 Gertjan van Wingerde <gwingerde@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 queue specअगरic routines.
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"

काष्ठा sk_buff *rt2x00queue_alloc_rxskb(काष्ठा queue_entry *entry, gfp_t gfp)
अणु
	काष्ठा data_queue *queue = entry->queue;
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	काष्ठा sk_buff *skb;
	काष्ठा skb_frame_desc *skbdesc;
	अचिन्हित पूर्णांक frame_size;
	अचिन्हित पूर्णांक head_size = 0;
	अचिन्हित पूर्णांक tail_size = 0;

	/*
	 * The frame size includes descriptor size, because the
	 * hardware directly receive the frame पूर्णांकo the skbuffer.
	 */
	frame_size = queue->data_size + queue->desc_size + queue->winfo_size;

	/*
	 * The payload should be aligned to a 4-byte boundary,
	 * this means we need at least 3 bytes क्रम moving the frame
	 * पूर्णांकo the correct offset.
	 */
	head_size = 4;

	/*
	 * For IV/EIV/ICV assembly we must make sure there is
	 * at least 8 bytes bytes available in headroom क्रम IV/EIV
	 * and 8 bytes क्रम ICV data as tailroon.
	 */
	अगर (rt2x00_has_cap_hw_crypto(rt2x00dev)) अणु
		head_size += 8;
		tail_size += 8;
	पूर्ण

	/*
	 * Allocate skbuffer.
	 */
	skb = __dev_alloc_skb(frame_size + head_size + tail_size, gfp);
	अगर (!skb)
		वापस शून्य;

	/*
	 * Make sure we not have a frame with the requested bytes
	 * available in the head and tail.
	 */
	skb_reserve(skb, head_size);
	skb_put(skb, frame_size);

	/*
	 * Populate skbdesc.
	 */
	skbdesc = get_skb_frame_desc(skb);
	स_रखो(skbdesc, 0, माप(*skbdesc));

	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DMA)) अणु
		dma_addr_t skb_dma;

		skb_dma = dma_map_single(rt2x00dev->dev, skb->data, skb->len,
					 DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(rt2x00dev->dev, skb_dma))) अणु
			dev_kमुक्त_skb_any(skb);
			वापस शून्य;
		पूर्ण

		skbdesc->skb_dma = skb_dma;
		skbdesc->flags |= SKBDESC_DMA_MAPPED_RX;
	पूर्ण

	वापस skb;
पूर्ण

पूर्णांक rt2x00queue_map_txskb(काष्ठा queue_entry *entry)
अणु
	काष्ठा device *dev = entry->queue->rt2x00dev->dev;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);

	skbdesc->skb_dma =
	    dma_map_single(dev, entry->skb->data, entry->skb->len, DMA_TO_DEVICE);

	अगर (unlikely(dma_mapping_error(dev, skbdesc->skb_dma)))
		वापस -ENOMEM;

	skbdesc->flags |= SKBDESC_DMA_MAPPED_TX;
	rt2x00lib_dmaकरोne(entry);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_map_txskb);

व्योम rt2x00queue_unmap_skb(काष्ठा queue_entry *entry)
अणु
	काष्ठा device *dev = entry->queue->rt2x00dev->dev;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);

	अगर (skbdesc->flags & SKBDESC_DMA_MAPPED_RX) अणु
		dma_unmap_single(dev, skbdesc->skb_dma, entry->skb->len,
				 DMA_FROM_DEVICE);
		skbdesc->flags &= ~SKBDESC_DMA_MAPPED_RX;
	पूर्ण अन्यथा अगर (skbdesc->flags & SKBDESC_DMA_MAPPED_TX) अणु
		dma_unmap_single(dev, skbdesc->skb_dma, entry->skb->len,
				 DMA_TO_DEVICE);
		skbdesc->flags &= ~SKBDESC_DMA_MAPPED_TX;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_unmap_skb);

व्योम rt2x00queue_मुक्त_skb(काष्ठा queue_entry *entry)
अणु
	अगर (!entry->skb)
		वापस;

	rt2x00queue_unmap_skb(entry);
	dev_kमुक्त_skb_any(entry->skb);
	entry->skb = शून्य;
पूर्ण

व्योम rt2x00queue_align_frame(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक frame_length = skb->len;
	अचिन्हित पूर्णांक align = ALIGN_SIZE(skb, 0);

	अगर (!align)
		वापस;

	skb_push(skb, align);
	स_हटाओ(skb->data, skb->data + align, frame_length);
	skb_trim(skb, frame_length);
पूर्ण

/*
 * H/W needs L2 padding between the header and the paylod अगर header size
 * is not 4 bytes aligned.
 */
व्योम rt2x00queue_insert_l2pad(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hdr_len)
अणु
	अचिन्हित पूर्णांक l2pad = (skb->len > hdr_len) ? L2PAD_SIZE(hdr_len) : 0;

	अगर (!l2pad)
		वापस;

	skb_push(skb, l2pad);
	स_हटाओ(skb->data, skb->data + l2pad, hdr_len);
पूर्ण

व्योम rt2x00queue_हटाओ_l2pad(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hdr_len)
अणु
	अचिन्हित पूर्णांक l2pad = (skb->len > hdr_len) ? L2PAD_SIZE(hdr_len) : 0;

	अगर (!l2pad)
		वापस;

	स_हटाओ(skb->data + l2pad, skb->data, hdr_len);
	skb_pull(skb, l2pad);
पूर्ण

अटल व्योम rt2x00queue_create_tx_descriptor_seq(काष्ठा rt2x00_dev *rt2x00dev,
						 काष्ठा sk_buff *skb,
						 काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा rt2x00_पूर्णांकf *पूर्णांकf = vअगर_to_पूर्णांकf(tx_info->control.vअगर);
	u16 seqno;

	अगर (!(tx_info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ))
		वापस;

	__set_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags);

	अगर (!rt2x00_has_cap_flag(rt2x00dev, REQUIRE_SW_SEQNO)) अणु
		/*
		 * rt2800 has a H/W (or F/W) bug, device incorrectly increase
		 * seqno on retransmitted data (non-QOS) and management frames.
		 * To workaround the problem let's generate seqno in software.
		 * Except क्रम beacons which are transmitted periodically by H/W
		 * hence hardware has to assign seqno क्रम them.
		 */
	    	अगर (ieee80211_is_beacon(hdr->frame_control)) अणु
			__set_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags);
			/* H/W will generate sequence number */
			वापस;
		पूर्ण

		__clear_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags);
	पूर्ण

	/*
	 * The hardware is not able to insert a sequence number. Assign a
	 * software generated one here.
	 *
	 * This is wrong because beacons are not getting sequence
	 * numbers asचिन्हित properly.
	 *
	 * A secondary problem exists क्रम drivers that cannot toggle
	 * sequence counting per-frame, since those will override the
	 * sequence counter given by mac80211.
	 */
	अगर (test_bit(ENTRY_TXD_FIRST_FRAGMENT, &txdesc->flags))
		seqno = atomic_add_वापस(0x10, &पूर्णांकf->seqno);
	अन्यथा
		seqno = atomic_पढ़ो(&पूर्णांकf->seqno);

	hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
	hdr->seq_ctrl |= cpu_to_le16(seqno);
पूर्ण

अटल व्योम rt2x00queue_create_tx_descriptor_plcp(काष्ठा rt2x00_dev *rt2x00dev,
						  काष्ठा sk_buff *skb,
						  काष्ठा txentry_desc *txdesc,
						  स्थिर काष्ठा rt2x00_rate *hwrate)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *txrate = &tx_info->control.rates[0];
	अचिन्हित पूर्णांक data_length;
	अचिन्हित पूर्णांक duration;
	अचिन्हित पूर्णांक residual;

	/*
	 * Determine with what IFS priority this frame should be send.
	 * Set अगरs to IFS_SIFS when the this is not the first fragment,
	 * or this fragment came after RTS/CTS.
	 */
	अगर (test_bit(ENTRY_TXD_FIRST_FRAGMENT, &txdesc->flags))
		txdesc->u.plcp.अगरs = IFS_BACKOFF;
	अन्यथा
		txdesc->u.plcp.अगरs = IFS_SIFS;

	/* Data length + CRC + Crypto overhead (IV/EIV/ICV/MIC) */
	data_length = skb->len + 4;
	data_length += rt2x00crypto_tx_overhead(rt2x00dev, skb);

	/*
	 * PLCP setup
	 * Length calculation depends on OFDM/CCK rate.
	 */
	txdesc->u.plcp.संकेत = hwrate->plcp;
	txdesc->u.plcp.service = 0x04;

	अगर (hwrate->flags & DEV_RATE_OFDM) अणु
		txdesc->u.plcp.length_high = (data_length >> 6) & 0x3f;
		txdesc->u.plcp.length_low = data_length & 0x3f;
	पूर्ण अन्यथा अणु
		/*
		 * Convert length to microseconds.
		 */
		residual = GET_DURATION_RES(data_length, hwrate->bitrate);
		duration = GET_DURATION(data_length, hwrate->bitrate);

		अगर (residual != 0) अणु
			duration++;

			/*
			 * Check अगर we need to set the Length Extension
			 */
			अगर (hwrate->bitrate == 110 && residual <= 30)
				txdesc->u.plcp.service |= 0x80;
		पूर्ण

		txdesc->u.plcp.length_high = (duration >> 8) & 0xff;
		txdesc->u.plcp.length_low = duration & 0xff;

		/*
		 * When preamble is enabled we should set the
		 * preamble bit क्रम the संकेत.
		 */
		अगर (txrate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
			txdesc->u.plcp.संकेत |= 0x08;
	पूर्ण
पूर्ण

अटल व्योम rt2x00queue_create_tx_descriptor_ht(काष्ठा rt2x00_dev *rt2x00dev,
						काष्ठा sk_buff *skb,
						काष्ठा txentry_desc *txdesc,
						काष्ठा ieee80211_sta *sta,
						स्थिर काष्ठा rt2x00_rate *hwrate)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *txrate = &tx_info->control.rates[0];
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा rt2x00_sta *sta_priv = शून्य;
	u8 density = 0;

	अगर (sta) अणु
		sta_priv = sta_to_rt2x00_sta(sta);
		txdesc->u.ht.wcid = sta_priv->wcid;
		density = sta->ht_cap.ampdu_density;
	पूर्ण

	/*
	 * If IEEE80211_TX_RC_MCS is set txrate->idx just contains the
	 * mcs rate to be used
	 */
	अगर (txrate->flags & IEEE80211_TX_RC_MCS) अणु
		txdesc->u.ht.mcs = txrate->idx;

		/*
		 * MIMO PS should be set to 1 क्रम STA's using dynamic SM PS
		 * when using more then one tx stream (>MCS7).
		 */
		अगर (sta && txdesc->u.ht.mcs > 7 &&
		    sta->smps_mode == IEEE80211_SMPS_DYNAMIC)
			__set_bit(ENTRY_TXD_HT_MIMO_PS, &txdesc->flags);
	पूर्ण अन्यथा अणु
		txdesc->u.ht.mcs = rt2x00_get_rate_mcs(hwrate->mcs);
		अगर (txrate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
			txdesc->u.ht.mcs |= 0x08;
	पूर्ण

	अगर (test_bit(CONFIG_HT_DISABLED, &rt2x00dev->flags)) अणु
		अगर (!(tx_info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT))
			txdesc->u.ht.txop = TXOP_SIFS;
		अन्यथा
			txdesc->u.ht.txop = TXOP_BACKOFF;

		/* Left zero on all other settings. */
		वापस;
	पूर्ण

	/*
	 * Only one STBC stream is supported क्रम now.
	 */
	अगर (tx_info->flags & IEEE80211_TX_CTL_STBC)
		txdesc->u.ht.stbc = 1;

	/*
	 * This frame is eligible क्रम an AMPDU, however, करोn't aggregate
	 * frames that are पूर्णांकended to probe a specअगरic tx rate.
	 */
	अगर (tx_info->flags & IEEE80211_TX_CTL_AMPDU &&
	    !(tx_info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)) अणु
		__set_bit(ENTRY_TXD_HT_AMPDU, &txdesc->flags);
		txdesc->u.ht.mpdu_density = density;
		txdesc->u.ht.ba_size = 7; /* FIXME: What value is needed? */
	पूर्ण

	/*
	 * Set 40Mhz mode अगर necessary (क्रम legacy rates this will
	 * duplicate the frame to both channels).
	 */
	अगर (txrate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH ||
	    txrate->flags & IEEE80211_TX_RC_DUP_DATA)
		__set_bit(ENTRY_TXD_HT_BW_40, &txdesc->flags);
	अगर (txrate->flags & IEEE80211_TX_RC_SHORT_GI)
		__set_bit(ENTRY_TXD_HT_SHORT_GI, &txdesc->flags);

	/*
	 * Determine IFS values
	 * - Use TXOP_BACKOFF क्रम management frames except beacons
	 * - Use TXOP_SIFS क्रम fragment bursts
	 * - Use TXOP_HTTXOP क्रम everything अन्यथा
	 *
	 * Note: rt2800 devices won't use CTS protection (अगर used)
	 * क्रम frames not transmitted with TXOP_HTTXOP
	 */
	अगर (ieee80211_is_mgmt(hdr->frame_control) &&
	    !ieee80211_is_beacon(hdr->frame_control))
		txdesc->u.ht.txop = TXOP_BACKOFF;
	अन्यथा अगर (!(tx_info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT))
		txdesc->u.ht.txop = TXOP_SIFS;
	अन्यथा
		txdesc->u.ht.txop = TXOP_HTTXOP;
पूर्ण

अटल व्योम rt2x00queue_create_tx_descriptor(काष्ठा rt2x00_dev *rt2x00dev,
					     काष्ठा sk_buff *skb,
					     काष्ठा txentry_desc *txdesc,
					     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_rate *txrate = &tx_info->control.rates[0];
	काष्ठा ieee80211_rate *rate;
	स्थिर काष्ठा rt2x00_rate *hwrate = शून्य;

	स_रखो(txdesc, 0, माप(*txdesc));

	/*
	 * Header and frame inक्रमmation.
	 */
	txdesc->length = skb->len;
	txdesc->header_length = ieee80211_get_hdrlen_from_skb(skb);

	/*
	 * Check whether this frame is to be acked.
	 */
	अगर (!(tx_info->flags & IEEE80211_TX_CTL_NO_ACK))
		__set_bit(ENTRY_TXD_ACK, &txdesc->flags);

	/*
	 * Check अगर this is a RTS/CTS frame
	 */
	अगर (ieee80211_is_rts(hdr->frame_control) ||
	    ieee80211_is_cts(hdr->frame_control)) अणु
		__set_bit(ENTRY_TXD_BURST, &txdesc->flags);
		अगर (ieee80211_is_rts(hdr->frame_control))
			__set_bit(ENTRY_TXD_RTS_FRAME, &txdesc->flags);
		अन्यथा
			__set_bit(ENTRY_TXD_CTS_FRAME, &txdesc->flags);
		अगर (tx_info->control.rts_cts_rate_idx >= 0)
			rate =
			    ieee80211_get_rts_cts_rate(rt2x00dev->hw, tx_info);
	पूर्ण

	/*
	 * Determine retry inक्रमmation.
	 */
	txdesc->retry_limit = tx_info->control.rates[0].count - 1;
	अगर (txdesc->retry_limit >= rt2x00dev->दीर्घ_retry)
		__set_bit(ENTRY_TXD_RETRY_MODE, &txdesc->flags);

	/*
	 * Check अगर more fragments are pending
	 */
	अगर (ieee80211_has_morefrags(hdr->frame_control)) अणु
		__set_bit(ENTRY_TXD_BURST, &txdesc->flags);
		__set_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags);
	पूर्ण

	/*
	 * Check अगर more frames (!= fragments) are pending
	 */
	अगर (tx_info->flags & IEEE80211_TX_CTL_MORE_FRAMES)
		__set_bit(ENTRY_TXD_BURST, &txdesc->flags);

	/*
	 * Beacons and probe responses require the tsf बारtamp
	 * to be inserted पूर्णांकo the frame.
	 */
	अगर (ieee80211_is_beacon(hdr->frame_control) ||
	    ieee80211_is_probe_resp(hdr->frame_control))
		__set_bit(ENTRY_TXD_REQ_TIMESTAMP, &txdesc->flags);

	अगर ((tx_info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT) &&
	    !test_bit(ENTRY_TXD_RTS_FRAME, &txdesc->flags))
		__set_bit(ENTRY_TXD_FIRST_FRAGMENT, &txdesc->flags);

	/*
	 * Determine rate modulation.
	 */
	अगर (txrate->flags & IEEE80211_TX_RC_GREEN_FIELD)
		txdesc->rate_mode = RATE_MODE_HT_GREENFIELD;
	अन्यथा अगर (txrate->flags & IEEE80211_TX_RC_MCS)
		txdesc->rate_mode = RATE_MODE_HT_MIX;
	अन्यथा अणु
		rate = ieee80211_get_tx_rate(rt2x00dev->hw, tx_info);
		hwrate = rt2x00_get_rate(rate->hw_value);
		अगर (hwrate->flags & DEV_RATE_OFDM)
			txdesc->rate_mode = RATE_MODE_OFDM;
		अन्यथा
			txdesc->rate_mode = RATE_MODE_CCK;
	पूर्ण

	/*
	 * Apply TX descriptor handling by components
	 */
	rt2x00crypto_create_tx_descriptor(rt2x00dev, skb, txdesc);
	rt2x00queue_create_tx_descriptor_seq(rt2x00dev, skb, txdesc);

	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_HT_TX_DESC))
		rt2x00queue_create_tx_descriptor_ht(rt2x00dev, skb, txdesc,
						   sta, hwrate);
	अन्यथा
		rt2x00queue_create_tx_descriptor_plcp(rt2x00dev, skb, txdesc,
						      hwrate);
पूर्ण

अटल पूर्णांक rt2x00queue_ग_लिखो_tx_data(काष्ठा queue_entry *entry,
				     काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;

	/*
	 * This should not happen, we alपढ़ोy checked the entry
	 * was ours. When the hardware disagrees there has been
	 * a queue corruption!
	 */
	अगर (unlikely(rt2x00dev->ops->lib->get_entry_state &&
		     rt2x00dev->ops->lib->get_entry_state(entry))) अणु
		rt2x00_err(rt2x00dev,
			   "Corrupt queue %d, accessing entry which is not ours\n"
			   "Please file bug report to %s\n",
			   entry->queue->qid, DRV_PROJECT);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Add the requested extra tx headroom in front of the skb.
	 */
	skb_push(entry->skb, rt2x00dev->extra_tx_headroom);
	स_रखो(entry->skb->data, 0, rt2x00dev->extra_tx_headroom);

	/*
	 * Call the driver's ग_लिखो_tx_data function, अगर it exists.
	 */
	अगर (rt2x00dev->ops->lib->ग_लिखो_tx_data)
		rt2x00dev->ops->lib->ग_लिखो_tx_data(entry, txdesc);

	/*
	 * Map the skb to DMA.
	 */
	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DMA) &&
	    rt2x00queue_map_txskb(entry))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम rt2x00queue_ग_लिखो_tx_descriptor(काष्ठा queue_entry *entry,
					    काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा data_queue *queue = entry->queue;

	queue->rt2x00dev->ops->lib->ग_लिखो_tx_desc(entry, txdesc);

	/*
	 * All processing on the frame has been completed, this means
	 * it is now पढ़ोy to be dumped to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(queue->rt2x00dev, DUMP_FRAME_TX, entry);
पूर्ण

अटल व्योम rt2x00queue_kick_tx_queue(काष्ठा data_queue *queue,
				      काष्ठा txentry_desc *txdesc)
अणु
	/*
	 * Check अगर we need to kick the queue, there are however a few rules
	 *	1) Don't kick unless this is the last in frame in a burst.
	 *	   When the burst flag is set, this frame is always followed
	 *	   by another frame which in some way are related to eachother.
	 *	   This is true क्रम fragments, RTS or CTS-to-self frames.
	 *	2) Rule 1 can be broken when the available entries
	 *	   in the queue are less then a certain threshold.
	 */
	अगर (rt2x00queue_threshold(queue) ||
	    !test_bit(ENTRY_TXD_BURST, &txdesc->flags))
		queue->rt2x00dev->ops->lib->kick_queue(queue);
पूर्ण

अटल व्योम rt2x00queue_bar_check(काष्ठा queue_entry *entry)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा ieee80211_bar *bar = (व्योम *) (entry->skb->data +
				    rt2x00dev->extra_tx_headroom);
	काष्ठा rt2x00_bar_list_entry *bar_entry;

	अगर (likely(!ieee80211_is_back_req(bar->frame_control)))
		वापस;

	bar_entry = kदो_स्मृति(माप(*bar_entry), GFP_ATOMIC);

	/*
	 * If the alloc fails we still send the BAR out but just करोn't track
	 * it in our bar list. And as a result we will report it to mac80211
	 * back as failed.
	 */
	अगर (!bar_entry)
		वापस;

	bar_entry->entry = entry;
	bar_entry->block_acked = 0;

	/*
	 * Copy the relevant parts of the 802.11 BAR पूर्णांकo out check list
	 * such that we can use RCU क्रम less-overhead in the RX path since
	 * sending BARs and processing the according BlockAck should be
	 * the exception.
	 */
	स_नकल(bar_entry->ra, bar->ra, माप(bar->ra));
	स_नकल(bar_entry->ta, bar->ta, माप(bar->ta));
	bar_entry->control = bar->control;
	bar_entry->start_seq_num = bar->start_seq_num;

	/*
	 * Insert BAR पूर्णांकo our BAR check list.
	 */
	spin_lock_bh(&rt2x00dev->bar_list_lock);
	list_add_tail_rcu(&bar_entry->list, &rt2x00dev->bar_list);
	spin_unlock_bh(&rt2x00dev->bar_list_lock);
पूर्ण

पूर्णांक rt2x00queue_ग_लिखो_tx_frame(काष्ठा data_queue *queue, काष्ठा sk_buff *skb,
			       काष्ठा ieee80211_sta *sta, bool local)
अणु
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा queue_entry *entry;
	काष्ठा txentry_desc txdesc;
	काष्ठा skb_frame_desc *skbdesc;
	u8 rate_idx, rate_flags;
	पूर्णांक ret = 0;

	/*
	 * Copy all TX descriptor inक्रमmation पूर्णांकo txdesc,
	 * after that we are मुक्त to use the skb->cb array
	 * क्रम our inक्रमmation.
	 */
	rt2x00queue_create_tx_descriptor(queue->rt2x00dev, skb, &txdesc, sta);

	/*
	 * All inक्रमmation is retrieved from the skb->cb array,
	 * now we should claim ownership of the driver part of that
	 * array, preserving the bitrate index and flags.
	 */
	tx_info = IEEE80211_SKB_CB(skb);
	rate_idx = tx_info->control.rates[0].idx;
	rate_flags = tx_info->control.rates[0].flags;
	skbdesc = get_skb_frame_desc(skb);
	स_रखो(skbdesc, 0, माप(*skbdesc));
	skbdesc->tx_rate_idx = rate_idx;
	skbdesc->tx_rate_flags = rate_flags;

	अगर (local)
		skbdesc->flags |= SKBDESC_NOT_MAC80211;

	/*
	 * When hardware encryption is supported, and this frame
	 * is to be encrypted, we should strip the IV/EIV data from
	 * the frame so we can provide it to the driver separately.
	 */
	अगर (test_bit(ENTRY_TXD_ENCRYPT, &txdesc.flags) &&
	    !test_bit(ENTRY_TXD_ENCRYPT_IV, &txdesc.flags)) अणु
		अगर (rt2x00_has_cap_flag(queue->rt2x00dev, REQUIRE_COPY_IV))
			rt2x00crypto_tx_copy_iv(skb, &txdesc);
		अन्यथा
			rt2x00crypto_tx_हटाओ_iv(skb, &txdesc);
	पूर्ण

	/*
	 * When DMA allocation is required we should guarantee to the
	 * driver that the DMA is aligned to a 4-byte boundary.
	 * However some drivers require L2 padding to pad the payload
	 * rather then the header. This could be a requirement क्रम
	 * PCI and USB devices, जबतक header alignment only is valid
	 * क्रम PCI devices.
	 */
	अगर (rt2x00_has_cap_flag(queue->rt2x00dev, REQUIRE_L2PAD))
		rt2x00queue_insert_l2pad(skb, txdesc.header_length);
	अन्यथा अगर (rt2x00_has_cap_flag(queue->rt2x00dev, REQUIRE_DMA))
		rt2x00queue_align_frame(skb);

	/*
	 * That function must be called with bh disabled.
	 */
	spin_lock(&queue->tx_lock);

	अगर (unlikely(rt2x00queue_full(queue))) अणु
		rt2x00_dbg(queue->rt2x00dev, "Dropping frame due to full tx queue %d\n",
			   queue->qid);
		ret = -ENOBUFS;
		जाओ out;
	पूर्ण

	entry = rt2x00queue_get_entry(queue, Q_INDEX);

	अगर (unlikely(test_and_set_bit(ENTRY_OWNER_DEVICE_DATA,
				      &entry->flags))) अणु
		rt2x00_err(queue->rt2x00dev,
			   "Arrived at non-free entry in the non-full queue %d\n"
			   "Please file bug report to %s\n",
			   queue->qid, DRV_PROJECT);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	entry->skb = skb;

	/*
	 * It could be possible that the queue was corrupted and this
	 * call failed. Since we always वापस NETDEV_TX_OK to mac80211,
	 * this frame will simply be dropped.
	 */
	अगर (unlikely(rt2x00queue_ग_लिखो_tx_data(entry, &txdesc))) अणु
		clear_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags);
		entry->skb = शून्य;
		ret = -EIO;
		जाओ out;
	पूर्ण

	/*
	 * Put BlockAckReqs पूर्णांकo our check list क्रम driver BA processing.
	 */
	rt2x00queue_bar_check(entry);

	set_bit(ENTRY_DATA_PENDING, &entry->flags);

	rt2x00queue_index_inc(entry, Q_INDEX);
	rt2x00queue_ग_लिखो_tx_descriptor(entry, &txdesc);
	rt2x00queue_kick_tx_queue(queue, &txdesc);

out:
	/*
	 * Pausing queue has to be serialized with rt2x00lib_txकरोne(), so we
	 * करो this under queue->tx_lock. Bottom halve was alपढ़ोy disabled
	 * beक्रमe ieee80211_xmit() call.
	 */
	अगर (rt2x00queue_threshold(queue))
		rt2x00queue_छोड़ो_queue(queue);

	spin_unlock(&queue->tx_lock);
	वापस ret;
पूर्ण

पूर्णांक rt2x00queue_clear_beacon(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_पूर्णांकf *पूर्णांकf = vअगर_to_पूर्णांकf(vअगर);

	अगर (unlikely(!पूर्णांकf->beacon))
		वापस -ENOBUFS;

	/*
	 * Clean up the beacon skb.
	 */
	rt2x00queue_मुक्त_skb(पूर्णांकf->beacon);

	/*
	 * Clear beacon (single bssid devices करोn't need to clear the beacon
	 * since the beacon queue will get stopped anyway).
	 */
	अगर (rt2x00dev->ops->lib->clear_beacon)
		rt2x00dev->ops->lib->clear_beacon(पूर्णांकf->beacon);

	वापस 0;
पूर्ण

पूर्णांक rt2x00queue_update_beacon(काष्ठा rt2x00_dev *rt2x00dev,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_पूर्णांकf *पूर्णांकf = vअगर_to_पूर्णांकf(vअगर);
	काष्ठा skb_frame_desc *skbdesc;
	काष्ठा txentry_desc txdesc;

	अगर (unlikely(!पूर्णांकf->beacon))
		वापस -ENOBUFS;

	/*
	 * Clean up the beacon skb.
	 */
	rt2x00queue_मुक्त_skb(पूर्णांकf->beacon);

	पूर्णांकf->beacon->skb = ieee80211_beacon_get(rt2x00dev->hw, vअगर);
	अगर (!पूर्णांकf->beacon->skb)
		वापस -ENOMEM;

	/*
	 * Copy all TX descriptor inक्रमmation पूर्णांकo txdesc,
	 * after that we are मुक्त to use the skb->cb array
	 * क्रम our inक्रमmation.
	 */
	rt2x00queue_create_tx_descriptor(rt2x00dev, पूर्णांकf->beacon->skb, &txdesc, शून्य);

	/*
	 * Fill in skb descriptor
	 */
	skbdesc = get_skb_frame_desc(पूर्णांकf->beacon->skb);
	स_रखो(skbdesc, 0, माप(*skbdesc));

	/*
	 * Send beacon to hardware.
	 */
	rt2x00dev->ops->lib->ग_लिखो_beacon(पूर्णांकf->beacon, &txdesc);

	वापस 0;

पूर्ण

bool rt2x00queue_क्रम_each_entry(काष्ठा data_queue *queue,
				क्रमागत queue_index start,
				क्रमागत queue_index end,
				व्योम *data,
				bool (*fn)(काष्ठा queue_entry *entry,
					   व्योम *data))
अणु
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक index_start;
	अचिन्हित पूर्णांक index_end;
	अचिन्हित पूर्णांक i;

	अगर (unlikely(start >= Q_INDEX_MAX || end >= Q_INDEX_MAX)) अणु
		rt2x00_err(queue->rt2x00dev,
			   "Entry requested from invalid index range (%d - %d)\n",
			   start, end);
		वापस true;
	पूर्ण

	/*
	 * Only protect the range we are going to loop over,
	 * अगर during our loop a extra entry is set to pending
	 * it should not be kicked during this run, since it
	 * is part of another TX operation.
	 */
	spin_lock_irqsave(&queue->index_lock, irqflags);
	index_start = queue->index[start];
	index_end = queue->index[end];
	spin_unlock_irqrestore(&queue->index_lock, irqflags);

	/*
	 * Start from the TX करोne poपूर्णांकer, this guarantees that we will
	 * send out all frames in the correct order.
	 */
	अगर (index_start < index_end) अणु
		क्रम (i = index_start; i < index_end; i++) अणु
			अगर (fn(&queue->entries[i], data))
				वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = index_start; i < queue->limit; i++) अणु
			अगर (fn(&queue->entries[i], data))
				वापस true;
		पूर्ण

		क्रम (i = 0; i < index_end; i++) अणु
			अगर (fn(&queue->entries[i], data))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_क्रम_each_entry);

काष्ठा queue_entry *rt2x00queue_get_entry(काष्ठा data_queue *queue,
					  क्रमागत queue_index index)
अणु
	काष्ठा queue_entry *entry;
	अचिन्हित दीर्घ irqflags;

	अगर (unlikely(index >= Q_INDEX_MAX)) अणु
		rt2x00_err(queue->rt2x00dev, "Entry requested from invalid index type (%d)\n",
			   index);
		वापस शून्य;
	पूर्ण

	spin_lock_irqsave(&queue->index_lock, irqflags);

	entry = &queue->entries[queue->index[index]];

	spin_unlock_irqrestore(&queue->index_lock, irqflags);

	वापस entry;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_get_entry);

व्योम rt2x00queue_index_inc(काष्ठा queue_entry *entry, क्रमागत queue_index index)
अणु
	काष्ठा data_queue *queue = entry->queue;
	अचिन्हित दीर्घ irqflags;

	अगर (unlikely(index >= Q_INDEX_MAX)) अणु
		rt2x00_err(queue->rt2x00dev,
			   "Index change on invalid index type (%d)\n", index);
		वापस;
	पूर्ण

	spin_lock_irqsave(&queue->index_lock, irqflags);

	queue->index[index]++;
	अगर (queue->index[index] >= queue->limit)
		queue->index[index] = 0;

	entry->last_action = jअगरfies;

	अगर (index == Q_INDEX) अणु
		queue->length++;
	पूर्ण अन्यथा अगर (index == Q_INDEX_DONE) अणु
		queue->length--;
		queue->count++;
	पूर्ण

	spin_unlock_irqrestore(&queue->index_lock, irqflags);
पूर्ण

अटल व्योम rt2x00queue_छोड़ो_queue_nocheck(काष्ठा data_queue *queue)
अणु
	चयन (queue->qid) अणु
	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		/*
		 * For TX queues, we have to disable the queue
		 * inside mac80211.
		 */
		ieee80211_stop_queue(queue->rt2x00dev->hw, queue->qid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
व्योम rt2x00queue_छोड़ो_queue(काष्ठा data_queue *queue)
अणु
	अगर (!test_bit(DEVICE_STATE_PRESENT, &queue->rt2x00dev->flags) ||
	    !test_bit(QUEUE_STARTED, &queue->flags) ||
	    test_and_set_bit(QUEUE_PAUSED, &queue->flags))
		वापस;

	rt2x00queue_छोड़ो_queue_nocheck(queue);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_छोड़ो_queue);

व्योम rt2x00queue_unछोड़ो_queue(काष्ठा data_queue *queue)
अणु
	अगर (!test_bit(DEVICE_STATE_PRESENT, &queue->rt2x00dev->flags) ||
	    !test_bit(QUEUE_STARTED, &queue->flags) ||
	    !test_and_clear_bit(QUEUE_PAUSED, &queue->flags))
		वापस;

	चयन (queue->qid) अणु
	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		/*
		 * For TX queues, we have to enable the queue
		 * inside mac80211.
		 */
		ieee80211_wake_queue(queue->rt2x00dev->hw, queue->qid);
		अवरोध;
	हाल QID_RX:
		/*
		 * For RX we need to kick the queue now in order to
		 * receive frames.
		 */
		queue->rt2x00dev->ops->lib->kick_queue(queue);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_unछोड़ो_queue);

व्योम rt2x00queue_start_queue(काष्ठा data_queue *queue)
अणु
	mutex_lock(&queue->status_lock);

	अगर (!test_bit(DEVICE_STATE_PRESENT, &queue->rt2x00dev->flags) ||
	    test_and_set_bit(QUEUE_STARTED, &queue->flags)) अणु
		mutex_unlock(&queue->status_lock);
		वापस;
	पूर्ण

	set_bit(QUEUE_PAUSED, &queue->flags);

	queue->rt2x00dev->ops->lib->start_queue(queue);

	rt2x00queue_unछोड़ो_queue(queue);

	mutex_unlock(&queue->status_lock);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_start_queue);

व्योम rt2x00queue_stop_queue(काष्ठा data_queue *queue)
अणु
	mutex_lock(&queue->status_lock);

	अगर (!test_and_clear_bit(QUEUE_STARTED, &queue->flags)) अणु
		mutex_unlock(&queue->status_lock);
		वापस;
	पूर्ण

	rt2x00queue_छोड़ो_queue_nocheck(queue);

	queue->rt2x00dev->ops->lib->stop_queue(queue);

	mutex_unlock(&queue->status_lock);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_stop_queue);

व्योम rt2x00queue_flush_queue(काष्ठा data_queue *queue, bool drop)
अणु
	bool tx_queue =
		(queue->qid == QID_AC_VO) ||
		(queue->qid == QID_AC_VI) ||
		(queue->qid == QID_AC_BE) ||
		(queue->qid == QID_AC_BK);

	अगर (rt2x00queue_empty(queue))
		वापस;

	/*
	 * If we are not supposed to drop any pending
	 * frames, this means we must क्रमce a start (=kick)
	 * to the queue to make sure the hardware will
	 * start transmitting.
	 */
	अगर (!drop && tx_queue)
		queue->rt2x00dev->ops->lib->kick_queue(queue);

	/*
	 * Check अगर driver supports flushing, अगर that is the हाल we can
	 * defer the flushing to the driver. Otherwise we must use the
	 * alternative which just रुकोs क्रम the queue to become empty.
	 */
	अगर (likely(queue->rt2x00dev->ops->lib->flush_queue))
		queue->rt2x00dev->ops->lib->flush_queue(queue, drop);

	/*
	 * The queue flush has failed...
	 */
	अगर (unlikely(!rt2x00queue_empty(queue)))
		rt2x00_warn(queue->rt2x00dev, "Queue %d failed to flush\n",
			    queue->qid);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_flush_queue);

व्योम rt2x00queue_start_queues(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;

	/*
	 * rt2x00queue_start_queue will call ieee80211_wake_queue
	 * क्रम each queue after is has been properly initialized.
	 */
	tx_queue_क्रम_each(rt2x00dev, queue)
		rt2x00queue_start_queue(queue);

	rt2x00queue_start_queue(rt2x00dev->rx);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_start_queues);

व्योम rt2x00queue_stop_queues(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;

	/*
	 * rt2x00queue_stop_queue will call ieee80211_stop_queue
	 * as well, but we are completely shutting करोing everything
	 * now, so it is much safer to stop all TX queues at once,
	 * and use rt2x00queue_stop_queue क्रम cleaning up.
	 */
	ieee80211_stop_queues(rt2x00dev->hw);

	tx_queue_क्रम_each(rt2x00dev, queue)
		rt2x00queue_stop_queue(queue);

	rt2x00queue_stop_queue(rt2x00dev->rx);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_stop_queues);

व्योम rt2x00queue_flush_queues(काष्ठा rt2x00_dev *rt2x00dev, bool drop)
अणु
	काष्ठा data_queue *queue;

	tx_queue_क्रम_each(rt2x00dev, queue)
		rt2x00queue_flush_queue(queue, drop);

	rt2x00queue_flush_queue(rt2x00dev->rx, drop);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00queue_flush_queues);

अटल व्योम rt2x00queue_reset(काष्ठा data_queue *queue)
अणु
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&queue->index_lock, irqflags);

	queue->count = 0;
	queue->length = 0;

	क्रम (i = 0; i < Q_INDEX_MAX; i++)
		queue->index[i] = 0;

	spin_unlock_irqrestore(&queue->index_lock, irqflags);
पूर्ण

व्योम rt2x00queue_init_queues(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	अचिन्हित पूर्णांक i;

	queue_क्रम_each(rt2x00dev, queue) अणु
		rt2x00queue_reset(queue);

		क्रम (i = 0; i < queue->limit; i++)
			rt2x00dev->ops->lib->clear_entry(&queue->entries[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक rt2x00queue_alloc_entries(काष्ठा data_queue *queue)
अणु
	काष्ठा queue_entry *entries;
	अचिन्हित पूर्णांक entry_size;
	अचिन्हित पूर्णांक i;

	rt2x00queue_reset(queue);

	/*
	 * Allocate all queue entries.
	 */
	entry_size = माप(*entries) + queue->priv_size;
	entries = kसुस्मृति(queue->limit, entry_size, GFP_KERNEL);
	अगर (!entries)
		वापस -ENOMEM;

#घोषणा QUEUE_ENTRY_PRIV_OFFSET(__base, __index, __limit, __esize, __psize) \
	(((अक्षर *)(__base)) + ((__limit) * (__esize)) + \
	    ((__index) * (__psize)))

	क्रम (i = 0; i < queue->limit; i++) अणु
		entries[i].flags = 0;
		entries[i].queue = queue;
		entries[i].skb = शून्य;
		entries[i].entry_idx = i;
		entries[i].priv_data =
		    QUEUE_ENTRY_PRIV_OFFSET(entries, i, queue->limit,
					    माप(*entries), queue->priv_size);
	पूर्ण

#अघोषित QUEUE_ENTRY_PRIV_OFFSET

	queue->entries = entries;

	वापस 0;
पूर्ण

अटल व्योम rt2x00queue_मुक्त_skbs(काष्ठा data_queue *queue)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!queue->entries)
		वापस;

	क्रम (i = 0; i < queue->limit; i++) अणु
		rt2x00queue_मुक्त_skb(&queue->entries[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक rt2x00queue_alloc_rxskbs(काष्ठा data_queue *queue)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा sk_buff *skb;

	क्रम (i = 0; i < queue->limit; i++) अणु
		skb = rt2x00queue_alloc_rxskb(&queue->entries[i], GFP_KERNEL);
		अगर (!skb)
			वापस -ENOMEM;
		queue->entries[i].skb = skb;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rt2x00queue_initialize(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	पूर्णांक status;

	status = rt2x00queue_alloc_entries(rt2x00dev->rx);
	अगर (status)
		जाओ निकास;

	tx_queue_क्रम_each(rt2x00dev, queue) अणु
		status = rt2x00queue_alloc_entries(queue);
		अगर (status)
			जाओ निकास;
	पूर्ण

	status = rt2x00queue_alloc_entries(rt2x00dev->bcn);
	अगर (status)
		जाओ निकास;

	अगर (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_ATIM_QUEUE)) अणु
		status = rt2x00queue_alloc_entries(rt2x00dev->atim);
		अगर (status)
			जाओ निकास;
	पूर्ण

	status = rt2x00queue_alloc_rxskbs(rt2x00dev->rx);
	अगर (status)
		जाओ निकास;

	वापस 0;

निकास:
	rt2x00_err(rt2x00dev, "Queue entries allocation failed\n");

	rt2x00queue_uninitialize(rt2x00dev);

	वापस status;
पूर्ण

व्योम rt2x00queue_uninitialize(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;

	rt2x00queue_मुक्त_skbs(rt2x00dev->rx);

	queue_क्रम_each(rt2x00dev, queue) अणु
		kमुक्त(queue->entries);
		queue->entries = शून्य;
	पूर्ण
पूर्ण

अटल व्योम rt2x00queue_init(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा data_queue *queue, क्रमागत data_queue_qid qid)
अणु
	mutex_init(&queue->status_lock);
	spin_lock_init(&queue->tx_lock);
	spin_lock_init(&queue->index_lock);

	queue->rt2x00dev = rt2x00dev;
	queue->qid = qid;
	queue->txop = 0;
	queue->aअगरs = 2;
	queue->cw_min = 5;
	queue->cw_max = 10;

	rt2x00dev->ops->queue_init(queue);

	queue->threshold = DIV_ROUND_UP(queue->limit, 10);
पूर्ण

पूर्णांक rt2x00queue_allocate(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	क्रमागत data_queue_qid qid;
	अचिन्हित पूर्णांक req_atim =
	    rt2x00_has_cap_flag(rt2x00dev, REQUIRE_ATIM_QUEUE);

	/*
	 * We need the following queues:
	 * RX: 1
	 * TX: ops->tx_queues
	 * Beacon: 1
	 * Atim: 1 (अगर required)
	 */
	rt2x00dev->data_queues = 2 + rt2x00dev->ops->tx_queues + req_atim;

	queue = kसुस्मृति(rt2x00dev->data_queues, माप(*queue), GFP_KERNEL);
	अगर (!queue)
		वापस -ENOMEM;

	/*
	 * Initialize poपूर्णांकers
	 */
	rt2x00dev->rx = queue;
	rt2x00dev->tx = &queue[1];
	rt2x00dev->bcn = &queue[1 + rt2x00dev->ops->tx_queues];
	rt2x00dev->atim = req_atim ? &queue[2 + rt2x00dev->ops->tx_queues] : शून्य;

	/*
	 * Initialize queue parameters.
	 * RX: qid = QID_RX
	 * TX: qid = QID_AC_VO + index
	 * TX: cw_min: 2^5 = 32.
	 * TX: cw_max: 2^10 = 1024.
	 * BCN: qid = QID_BEACON
	 * ATIM: qid = QID_ATIM
	 */
	rt2x00queue_init(rt2x00dev, rt2x00dev->rx, QID_RX);

	qid = QID_AC_VO;
	tx_queue_क्रम_each(rt2x00dev, queue)
		rt2x00queue_init(rt2x00dev, queue, qid++);

	rt2x00queue_init(rt2x00dev, rt2x00dev->bcn, QID_BEACON);
	अगर (req_atim)
		rt2x00queue_init(rt2x00dev, rt2x00dev->atim, QID_ATIM);

	वापस 0;
पूर्ण

व्योम rt2x00queue_मुक्त(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	kमुक्त(rt2x00dev->rx);
	rt2x00dev->rx = शून्य;
	rt2x00dev->tx = शून्य;
	rt2x00dev->bcn = शून्य;
पूर्ण
