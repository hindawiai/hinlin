<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "wl1251.h"
#समावेश "reg.h"
#समावेश "tx.h"
#समावेश "ps.h"
#समावेश "io.h"
#समावेश "event.h"

अटल bool wl1251_tx_द्विगुन_buffer_busy(काष्ठा wl1251 *wl, u32 data_out_count)
अणु
	पूर्णांक used, data_in_count;

	data_in_count = wl->data_in_count;

	अगर (data_in_count < data_out_count)
		/* data_in_count has wrapped */
		data_in_count += TX_STATUS_DATA_OUT_COUNT_MASK + 1;

	used = data_in_count - data_out_count;

	WARN_ON(used < 0);
	WARN_ON(used > DP_TX_PACKET_RING_CHUNK_NUM);

	अगर (used >= DP_TX_PACKET_RING_CHUNK_NUM)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक wl1251_tx_path_status(काष्ठा wl1251 *wl)
अणु
	u32 status, addr, data_out_count;
	bool busy;

	addr = wl->data_path->tx_control_addr;
	status = wl1251_mem_पढ़ो32(wl, addr);
	data_out_count = status & TX_STATUS_DATA_OUT_COUNT_MASK;
	busy = wl1251_tx_द्विगुन_buffer_busy(wl, data_out_count);

	अगर (busy)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_tx_id(काष्ठा wl1251 *wl, काष्ठा sk_buff *skb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < FW_TX_CMPLT_BLOCK_SIZE; i++)
		अगर (wl->tx_frames[i] == शून्य) अणु
			wl->tx_frames[i] = skb;
			वापस i;
		पूर्ण

	वापस -EBUSY;
पूर्ण

अटल व्योम wl1251_tx_control(काष्ठा tx_द्विगुन_buffer_desc *tx_hdr,
			      काष्ठा ieee80211_tx_info *control, u16 fc)
अणु
	*(u16 *)&tx_hdr->control = 0;

	tx_hdr->control.rate_policy = 0;

	/* 802.11 packets */
	tx_hdr->control.packet_type = 0;

	/* Also disable retry and ACK policy क्रम injected packets */
	अगर ((control->flags & IEEE80211_TX_CTL_NO_ACK) ||
	    (control->flags & IEEE80211_TX_CTL_INJECTED)) अणु
		tx_hdr->control.rate_policy = 1;
		tx_hdr->control.ack_policy = 1;
	पूर्ण

	tx_hdr->control.tx_complete = 1;

	अगर ((fc & IEEE80211_FTYPE_DATA) &&
	    ((fc & IEEE80211_STYPE_QOS_DATA) ||
	     (fc & IEEE80211_STYPE_QOS_शून्यFUNC)))
		tx_hdr->control.qos = 1;
पूर्ण

/* RSN + MIC = 8 + 8 = 16 bytes (worst हाल - AES). */
#घोषणा MAX_MSDU_SECURITY_LENGTH      16
#घोषणा MAX_MPDU_SECURITY_LENGTH      16
#घोषणा WLAN_QOS_HDR_LEN              26
#घोषणा MAX_MPDU_HEADER_AND_SECURITY  (MAX_MPDU_SECURITY_LENGTH + \
				       WLAN_QOS_HDR_LEN)
#घोषणा HW_BLOCK_SIZE                 252
अटल व्योम wl1251_tx_frag_block_num(काष्ठा tx_द्विगुन_buffer_desc *tx_hdr)
अणु
	u16 payload_len, frag_threshold, mem_blocks;
	u16 num_mpdus, mem_blocks_per_frag;

	frag_threshold = IEEE80211_MAX_FRAG_THRESHOLD;
	tx_hdr->frag_threshold = cpu_to_le16(frag_threshold);

	payload_len = le16_to_cpu(tx_hdr->length) + MAX_MSDU_SECURITY_LENGTH;

	अगर (payload_len > frag_threshold) अणु
		mem_blocks_per_frag =
			((frag_threshold + MAX_MPDU_HEADER_AND_SECURITY) /
			 HW_BLOCK_SIZE) + 1;
		num_mpdus = payload_len / frag_threshold;
		mem_blocks = num_mpdus * mem_blocks_per_frag;
		payload_len -= num_mpdus * frag_threshold;
		num_mpdus++;

	पूर्ण अन्यथा अणु
		mem_blocks_per_frag = 0;
		mem_blocks = 0;
		num_mpdus = 1;
	पूर्ण

	mem_blocks += (payload_len / HW_BLOCK_SIZE) + 1;

	अगर (num_mpdus > 1)
		mem_blocks += min(num_mpdus, mem_blocks_per_frag);

	tx_hdr->num_mem_blocks = mem_blocks;
पूर्ण

अटल पूर्णांक wl1251_tx_fill_hdr(काष्ठा wl1251 *wl, काष्ठा sk_buff *skb,
			      काष्ठा ieee80211_tx_info *control)
अणु
	काष्ठा tx_द्विगुन_buffer_desc *tx_hdr;
	काष्ठा ieee80211_rate *rate;
	पूर्णांक id;
	u16 fc;

	अगर (!skb)
		वापस -EINVAL;

	id = wl1251_tx_id(wl, skb);
	अगर (id < 0)
		वापस id;

	fc = *(u16 *)skb->data;
	tx_hdr = skb_push(skb, माप(*tx_hdr));

	tx_hdr->length = cpu_to_le16(skb->len - माप(*tx_hdr));
	rate = ieee80211_get_tx_rate(wl->hw, control);
	tx_hdr->rate = cpu_to_le16(rate->hw_value);
	tx_hdr->expiry_समय = cpu_to_le32(1 << 16);
	tx_hdr->id = id;

	tx_hdr->xmit_queue = wl1251_tx_get_queue(skb_get_queue_mapping(skb));

	wl1251_tx_control(tx_hdr, control, fc);
	wl1251_tx_frag_block_num(tx_hdr);

	वापस 0;
पूर्ण

/* We copy the packet to the target */
अटल पूर्णांक wl1251_tx_send_packet(काष्ठा wl1251 *wl, काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_tx_info *control)
अणु
	काष्ठा tx_द्विगुन_buffer_desc *tx_hdr;
	पूर्णांक len;
	u32 addr;

	अगर (!skb)
		वापस -EINVAL;

	tx_hdr = (काष्ठा tx_द्विगुन_buffer_desc *) skb->data;

	अगर (control->control.hw_key &&
	    control->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
		पूर्णांक hdrlen;
		__le16 fc;
		u16 length;
		u8 *pos;

		fc = *(__le16 *)(skb->data + माप(*tx_hdr));
		length = le16_to_cpu(tx_hdr->length) + WL1251_TKIP_IV_SPACE;
		tx_hdr->length = cpu_to_le16(length);

		hdrlen = ieee80211_hdrlen(fc);

		pos = skb_push(skb, WL1251_TKIP_IV_SPACE);
		स_हटाओ(pos, pos + WL1251_TKIP_IV_SPACE,
			माप(*tx_hdr) + hdrlen);
	पूर्ण

	/* Revisit. This is a workaround क्रम getting non-aligned packets.
	   This happens at least with EAPOL packets from the user space.
	   Our DMA requires packets to be aligned on a 4-byte boundary.
	*/
	अगर (unlikely((दीर्घ)skb->data & 0x03)) अणु
		पूर्णांक offset = (4 - (दीर्घ)skb->data) & 0x03;
		wl1251_debug(DEBUG_TX, "skb offset %d", offset);

		/* check whether the current skb can be used */
		अगर (skb_cloned(skb) || (skb_tailroom(skb) < offset)) अणु
			काष्ठा sk_buff *newskb = skb_copy_expand(skb, 0, 3,
								 GFP_KERNEL);

			अगर (unlikely(newskb == शून्य))
				वापस -EINVAL;

			tx_hdr = (काष्ठा tx_द्विगुन_buffer_desc *) newskb->data;

			dev_kमुक्त_skb_any(skb);
			wl->tx_frames[tx_hdr->id] = skb = newskb;

			offset = (4 - (दीर्घ)skb->data) & 0x03;
			wl1251_debug(DEBUG_TX, "new skb offset %d", offset);
		पूर्ण

		/* align the buffer on a 4-byte boundary */
		अगर (offset) अणु
			अचिन्हित अक्षर *src = skb->data;
			skb_reserve(skb, offset);
			स_हटाओ(skb->data, src, skb->len);
			tx_hdr = (काष्ठा tx_द्विगुन_buffer_desc *) skb->data;
		पूर्ण
	पूर्ण

	/* Our skb->data at this poपूर्णांक includes the HW header */
	len = WL1251_TX_ALIGN(skb->len);

	अगर (wl->data_in_count & 0x1)
		addr = wl->data_path->tx_packet_ring_addr +
			wl->data_path->tx_packet_ring_chunk_size;
	अन्यथा
		addr = wl->data_path->tx_packet_ring_addr;

	wl1251_mem_ग_लिखो(wl, addr, skb->data, len);

	wl1251_debug(DEBUG_TX, "tx id %u skb 0x%p payload %u rate 0x%x "
		     "queue %d", tx_hdr->id, skb, tx_hdr->length,
		     tx_hdr->rate, tx_hdr->xmit_queue);

	वापस 0;
पूर्ण

अटल व्योम wl1251_tx_trigger(काष्ठा wl1251 *wl)
अणु
	u32 data, addr;

	अगर (wl->data_in_count & 0x1) अणु
		addr = ACX_REG_INTERRUPT_TRIG_H;
		data = INTR_TRIG_TX_PROC1;
	पूर्ण अन्यथा अणु
		addr = ACX_REG_INTERRUPT_TRIG;
		data = INTR_TRIG_TX_PROC0;
	पूर्ण

	wl1251_reg_ग_लिखो32(wl, addr, data);

	/* Bumping data in */
	wl->data_in_count = (wl->data_in_count + 1) &
		TX_STATUS_DATA_OUT_COUNT_MASK;
पूर्ण

अटल व्योम enable_tx_क्रम_packet_injection(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_cmd_join(wl, BSS_TYPE_STA_BSS, wl->channel,
			      wl->beacon_पूर्णांक, wl->dtim_period);
	अगर (ret < 0) अणु
		wl1251_warning("join failed");
		वापस;
	पूर्ण

	ret = wl1251_event_रुको(wl, JOIN_EVENT_COMPLETE_ID, 100);
	अगर (ret < 0) अणु
		wl1251_warning("join timeout");
		वापस;
	पूर्ण

	wl->joined = true;
पूर्ण

/* caller must hold wl->mutex */
अटल पूर्णांक wl1251_tx_frame(काष्ठा wl1251 *wl, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info;
	पूर्णांक ret = 0;
	u8 idx;

	info = IEEE80211_SKB_CB(skb);

	अगर (info->control.hw_key) अणु
		अगर (unlikely(wl->monitor_present))
			वापस -EINVAL;

		idx = info->control.hw_key->hw_key_idx;
		अगर (unlikely(wl->शेष_key != idx)) अणु
			ret = wl1251_acx_शेष_key(wl, idx);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Enable tx path in monitor mode क्रम packet injection */
	अगर ((wl->vअगर == शून्य) && !wl->joined)
		enable_tx_क्रम_packet_injection(wl);

	ret = wl1251_tx_path_status(wl);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_tx_fill_hdr(wl, skb, info);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_tx_send_packet(wl, skb, info);
	अगर (ret < 0)
		वापस ret;

	wl1251_tx_trigger(wl);

	वापस ret;
पूर्ण

व्योम wl1251_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wl1251 *wl = container_of(work, काष्ठा wl1251, tx_work);
	काष्ठा sk_buff *skb;
	bool woken_up = false;
	पूर्णांक ret;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state == WL1251_STATE_OFF))
		जाओ out;

	जबतक ((skb = skb_dequeue(&wl->tx_queue))) अणु
		अगर (!woken_up) अणु
			ret = wl1251_ps_elp_wakeup(wl);
			अगर (ret < 0)
				जाओ out;
			woken_up = true;
		पूर्ण

		ret = wl1251_tx_frame(wl, skb);
		अगर (ret == -EBUSY) अणु
			skb_queue_head(&wl->tx_queue, skb);
			जाओ out;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			dev_kमुक्त_skb(skb);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (woken_up)
		wl1251_ps_elp_sleep(wl);

	mutex_unlock(&wl->mutex);
पूर्ण

अटल स्थिर अक्षर *wl1251_tx_parse_status(u8 status)
अणु
	/* 8 bit status field, one अक्षरacter per bit plus null */
	अटल अक्षर buf[9];
	पूर्णांक i = 0;

	स_रखो(buf, 0, माप(buf));

	अगर (status & TX_DMA_ERROR)
		buf[i++] = 'm';
	अगर (status & TX_DISABLED)
		buf[i++] = 'd';
	अगर (status & TX_RETRY_EXCEEDED)
		buf[i++] = 'r';
	अगर (status & TX_TIMEOUT)
		buf[i++] = 't';
	अगर (status & TX_KEY_NOT_FOUND)
		buf[i++] = 'k';
	अगर (status & TX_ENCRYPT_FAIL)
		buf[i++] = 'e';
	अगर (status & TX_UNAVAILABLE_PRIORITY)
		buf[i++] = 'p';

	/* bit 0 is unused apparently */

	वापस buf;
पूर्ण

अटल व्योम wl1251_tx_packet_cb(काष्ठा wl1251 *wl,
				काष्ठा tx_result *result)
अणु
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *skb;
	पूर्णांक hdrlen;
	u8 *frame;

	skb = wl->tx_frames[result->id];
	अगर (skb == शून्य) अणु
		wl1251_error("SKB for packet %d is NULL", result->id);
		वापस;
	पूर्ण

	info = IEEE80211_SKB_CB(skb);

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK) &&
	    !(info->flags & IEEE80211_TX_CTL_INJECTED) &&
	    (result->status == TX_SUCCESS))
		info->flags |= IEEE80211_TX_STAT_ACK;

	info->status.rates[0].count = result->ack_failures + 1;
	wl->stats.retry_count += result->ack_failures;

	/*
	 * We have to हटाओ our निजी TX header beक्रमe pushing
	 * the skb back to mac80211.
	 */
	frame = skb_pull(skb, माप(काष्ठा tx_द्विगुन_buffer_desc));
	अगर (info->control.hw_key &&
	    info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) अणु
		hdrlen = ieee80211_get_hdrlen_from_skb(skb);
		स_हटाओ(frame + WL1251_TKIP_IV_SPACE, frame, hdrlen);
		skb_pull(skb, WL1251_TKIP_IV_SPACE);
	पूर्ण

	wl1251_debug(DEBUG_TX, "tx status id %u skb 0x%p failures %u rate 0x%x"
		     " status 0x%x (%s)",
		     result->id, skb, result->ack_failures, result->rate,
		     result->status, wl1251_tx_parse_status(result->status));


	ieee80211_tx_status(wl->hw, skb);

	wl->tx_frames[result->id] = शून्य;
पूर्ण

/* Called upon reception of a TX complete पूर्णांकerrupt */
व्योम wl1251_tx_complete(काष्ठा wl1251 *wl)
अणु
	पूर्णांक i, result_index, num_complete = 0, queue_len;
	काष्ठा tx_result result[FW_TX_CMPLT_BLOCK_SIZE], *result_ptr;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(wl->state != WL1251_STATE_ON))
		वापस;

	/* First we पढ़ो the result */
	wl1251_mem_पढ़ो(wl, wl->data_path->tx_complete_addr,
			    result, माप(result));

	result_index = wl->next_tx_complete;

	क्रम (i = 0; i < ARRAY_SIZE(result); i++) अणु
		result_ptr = &result[result_index];

		अगर (result_ptr->करोne_1 == 1 &&
		    result_ptr->करोne_2 == 1) अणु
			wl1251_tx_packet_cb(wl, result_ptr);

			result_ptr->करोne_1 = 0;
			result_ptr->करोne_2 = 0;

			result_index = (result_index + 1) &
				(FW_TX_CMPLT_BLOCK_SIZE - 1);
			num_complete++;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	queue_len = skb_queue_len(&wl->tx_queue);

	अगर ((num_complete > 0) && (queue_len > 0)) अणु
		/* firmware buffer has space, reschedule tx_work */
		wl1251_debug(DEBUG_TX, "tx_complete: reschedule tx_work");
		ieee80211_queue_work(wl->hw, &wl->tx_work);
	पूर्ण

	अगर (wl->tx_queue_stopped &&
	    queue_len <= WL1251_TX_QUEUE_LOW_WATERMARK) अणु
		/* tx_queue has space, restart queues */
		wl1251_debug(DEBUG_TX, "tx_complete: waking queues");
		spin_lock_irqsave(&wl->wl_lock, flags);
		ieee80211_wake_queues(wl->hw);
		wl->tx_queue_stopped = false;
		spin_unlock_irqrestore(&wl->wl_lock, flags);
	पूर्ण

	/* Every completed frame needs to be acknowledged */
	अगर (num_complete) अणु
		/*
		 * If we've wrapped, we have to clear
		 * the results in 2 steps.
		 */
		अगर (result_index > wl->next_tx_complete) अणु
			/* Only 1 ग_लिखो is needed */
			wl1251_mem_ग_लिखो(wl,
					 wl->data_path->tx_complete_addr +
					 (wl->next_tx_complete *
					  माप(काष्ठा tx_result)),
					 &result[wl->next_tx_complete],
					 num_complete *
					 माप(काष्ठा tx_result));


		पूर्ण अन्यथा अगर (result_index < wl->next_tx_complete) अणु
			/* 2 ग_लिखोs are needed */
			wl1251_mem_ग_लिखो(wl,
					 wl->data_path->tx_complete_addr +
					 (wl->next_tx_complete *
					  माप(काष्ठा tx_result)),
					 &result[wl->next_tx_complete],
					 (FW_TX_CMPLT_BLOCK_SIZE -
					  wl->next_tx_complete) *
					 माप(काष्ठा tx_result));

			wl1251_mem_ग_लिखो(wl,
					 wl->data_path->tx_complete_addr,
					 result,
					 (num_complete -
					  FW_TX_CMPLT_BLOCK_SIZE +
					  wl->next_tx_complete) *
					 माप(काष्ठा tx_result));

		पूर्ण अन्यथा अणु
			/* We have to ग_लिखो the whole array */
			wl1251_mem_ग_लिखो(wl,
					 wl->data_path->tx_complete_addr,
					 result,
					 FW_TX_CMPLT_BLOCK_SIZE *
					 माप(काष्ठा tx_result));
		पूर्ण

	पूर्ण

	wl->next_tx_complete = result_index;
पूर्ण

/* caller must hold wl->mutex */
व्योम wl1251_tx_flush(काष्ठा wl1251 *wl)
अणु
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;

	/* TX failure */
/* 	control->flags = 0; FIXME */

	जबतक ((skb = skb_dequeue(&wl->tx_queue))) अणु
		info = IEEE80211_SKB_CB(skb);

		wl1251_debug(DEBUG_TX, "flushing skb 0x%p", skb);

		अगर (!(info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS))
				जारी;

		ieee80211_tx_status(wl->hw, skb);
	पूर्ण

	क्रम (i = 0; i < FW_TX_CMPLT_BLOCK_SIZE; i++)
		अगर (wl->tx_frames[i] != शून्य) अणु
			skb = wl->tx_frames[i];
			info = IEEE80211_SKB_CB(skb);

			अगर (!(info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS))
				जारी;

			ieee80211_tx_status(wl->hw, skb);
			wl->tx_frames[i] = शून्य;
		पूर्ण
पूर्ण
