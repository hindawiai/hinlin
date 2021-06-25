<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: usbpipe.c
 *
 * Purpose: Handle USB control endpoपूर्णांक
 *
 * Author: Warren Hsu
 *
 * Date: Mar. 29, 2005
 *
 * Functions:
 *	vnt_control_out - Write variable length bytes to MEM/BB/MAC/EEPROM
 *	vnt_control_in - Read variable length bytes from MEM/BB/MAC/EEPROM
 *	vnt_control_out_u8 - Write one byte to MEM/BB/MAC/EEPROM
 *	vnt_control_in_u8 - Read one byte from MEM/BB/MAC/EEPROM
 *
 * Revision History:
 *      04-05-2004 Jerry Chen: Initial release
 *      11-24-2004 Warren Hsu: Add ControlvWriteByte,ControlvReadByte,
 *                             ControlvMaskByte
 *
 */

#समावेश "rxtx.h"
#समावेश "desc.h"
#समावेश "device.h"
#समावेश "usbpipe.h"
#समावेश "mac.h"
#समावेश "rf.h"

#घोषणा USB_CTL_WAIT	500 /* ms */

पूर्णांक vnt_control_out(काष्ठा vnt_निजी *priv, u8 request, u16 value,
		    u16 index, u16 length, स्थिर u8 *buffer)
अणु
	पूर्णांक ret = 0;
	u8 *usb_buffer;

	अगर (test_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags)) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	mutex_lock(&priv->usb_lock);

	usb_buffer = kmemdup(buffer, length, GFP_KERNEL);
	अगर (!usb_buffer) अणु
		ret = -ENOMEM;
		जाओ end_unlock;
	पूर्ण

	ret = usb_control_msg(priv->usb,
			      usb_sndctrlpipe(priv->usb, 0),
			      request, 0x40, value,
			      index, usb_buffer, length, USB_CTL_WAIT);

	kमुक्त(usb_buffer);

	अगर (ret == (पूर्णांक)length)
		ret = 0;
	अन्यथा
		ret = -EIO;

end_unlock:
	mutex_unlock(&priv->usb_lock);
end:
	वापस ret;
पूर्ण

पूर्णांक vnt_control_out_u8(काष्ठा vnt_निजी *priv, u8 reg, u8 reg_off, u8 data)
अणु
	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE,
			       reg_off, reg, माप(u8), &data);
पूर्ण

पूर्णांक vnt_control_out_blocks(काष्ठा vnt_निजी *priv,
			   u16 block, u8 reg, u16 length, स्थिर u8 *data)
अणु
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i < length; i += block) अणु
		u16 len = min_t(पूर्णांक, length - i, block);

		ret = vnt_control_out(priv, MESSAGE_TYPE_WRITE,
				      i, reg, len, data + i);
		अगर (ret)
			जाओ end;
	पूर्ण
end:
	वापस ret;
पूर्ण

पूर्णांक vnt_control_in(काष्ठा vnt_निजी *priv, u8 request, u16 value,
		   u16 index, u16 length, u8 *buffer)
अणु
	पूर्णांक ret = 0;
	u8 *usb_buffer;

	अगर (test_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags)) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	mutex_lock(&priv->usb_lock);

	usb_buffer = kदो_स्मृति(length, GFP_KERNEL);
	अगर (!usb_buffer) अणु
		ret = -ENOMEM;
		जाओ end_unlock;
	पूर्ण

	ret = usb_control_msg(priv->usb,
			      usb_rcvctrlpipe(priv->usb, 0),
			      request, 0xc0, value,
			      index, usb_buffer, length, USB_CTL_WAIT);

	अगर (ret == length)
		स_नकल(buffer, usb_buffer, length);

	kमुक्त(usb_buffer);

	अगर (ret == (पूर्णांक)length)
		ret = 0;
	अन्यथा
		ret = -EIO;

end_unlock:
	mutex_unlock(&priv->usb_lock);
end:
	वापस ret;
पूर्ण

पूर्णांक vnt_control_in_u8(काष्ठा vnt_निजी *priv, u8 reg, u8 reg_off, u8 *data)
अणु
	वापस vnt_control_in(priv, MESSAGE_TYPE_READ,
			      reg_off, reg, माप(u8), data);
पूर्ण

अटल पूर्णांक vnt_पूर्णांक_report_rate(काष्ठा vnt_निजी *priv, u8 pkt_no, u8 tsr)
अणु
	काष्ठा vnt_usb_send_context *context;
	काष्ठा ieee80211_tx_info *info;
	u8 tx_retry = (tsr & 0xf0) >> 4;
	s8 idx;

	अगर (pkt_no >= priv->num_tx_context)
		वापस -EINVAL;

	context = priv->tx_context[pkt_no];

	अगर (!context->skb)
		वापस -EINVAL;

	info = IEEE80211_SKB_CB(context->skb);
	idx = info->control.rates[0].idx;

	ieee80211_tx_info_clear_status(info);

	info->status.rates[0].count = tx_retry;

	अगर (!(tsr & TSR_TMO)) अणु
		info->status.rates[0].idx = idx;

		अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
			info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण

	ieee80211_tx_status_irqsafe(priv->hw, context->skb);

	context->in_use = false;

	वापस 0;
पूर्ण

अटल व्योम vnt_पूर्णांक_process_data(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा vnt_पूर्णांकerrupt_data *पूर्णांक_data;
	काष्ठा ieee80211_low_level_stats *low_stats = &priv->low_stats;

	dev_dbg(&priv->usb->dev, "---->s_nsInterruptProcessData\n");

	पूर्णांक_data = (काष्ठा vnt_पूर्णांकerrupt_data *)priv->पूर्णांक_buf.data_buf;

	अगर (पूर्णांक_data->tsr0 & TSR_VALID)
		vnt_पूर्णांक_report_rate(priv, पूर्णांक_data->pkt0, पूर्णांक_data->tsr0);

	अगर (पूर्णांक_data->tsr1 & TSR_VALID)
		vnt_पूर्णांक_report_rate(priv, पूर्णांक_data->pkt1, पूर्णांक_data->tsr1);

	अगर (पूर्णांक_data->tsr2 & TSR_VALID)
		vnt_पूर्णांक_report_rate(priv, पूर्णांक_data->pkt2, पूर्णांक_data->tsr2);

	अगर (पूर्णांक_data->tsr3 & TSR_VALID)
		vnt_पूर्णांक_report_rate(priv, पूर्णांक_data->pkt3, पूर्णांक_data->tsr3);

	अगर (!पूर्णांक_data->isr0)
		वापस;

	अगर (पूर्णांक_data->isr0 & ISR_BNTX && priv->op_mode == NL80211_IFTYPE_AP)
		vnt_schedule_command(priv, WLAN_CMD_BECON_SEND);

	priv->current_tsf = le64_to_cpu(पूर्णांक_data->tsf);

	low_stats->करोt11RTSSuccessCount += पूर्णांक_data->rts_success;
	low_stats->करोt11RTSFailureCount += पूर्णांक_data->rts_fail;
	low_stats->करोt11ACKFailureCount += पूर्णांक_data->ack_fail;
	low_stats->करोt11FCSErrorCount += पूर्णांक_data->fcs_err;
पूर्ण

अटल व्योम vnt_start_पूर्णांकerrupt_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा vnt_निजी *priv = urb->context;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
	हाल -ETIMEDOUT:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	अगर (status)
		dev_dbg(&priv->usb->dev, "%s status = %d\n", __func__, status);
	अन्यथा
		vnt_पूर्णांक_process_data(priv);

	status = usb_submit_urb(priv->पूर्णांकerrupt_urb, GFP_ATOMIC);
	अगर (status)
		dev_dbg(&priv->usb->dev, "Submit int URB failed %d\n", status);
पूर्ण

पूर्णांक vnt_start_पूर्णांकerrupt_urb(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ret = 0;

	dev_dbg(&priv->usb->dev, "---->Interrupt Polling Thread\n");

	usb_fill_पूर्णांक_urb(priv->पूर्णांकerrupt_urb,
			 priv->usb,
			 usb_rcvपूर्णांकpipe(priv->usb, 1),
			 priv->पूर्णांक_buf.data_buf,
			 MAX_INTERRUPT_SIZE,
			 vnt_start_पूर्णांकerrupt_urb_complete,
			 priv,
			 priv->पूर्णांक_पूर्णांकerval);

	ret = usb_submit_urb(priv->पूर्णांकerrupt_urb, GFP_ATOMIC);
	अगर (ret)
		dev_dbg(&priv->usb->dev, "Submit int URB failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक vnt_rx_data(काष्ठा vnt_निजी *priv, काष्ठा vnt_rcb *ptr_rcb,
		       अचिन्हित दीर्घ bytes_received)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा vnt_rx_header *head;
	काष्ठा vnt_rx_tail *tail;
	u32 frame_size;
	पूर्णांक ii;
	u16 rx_bitrate, pay_load_with_padding;
	u8 rate_idx = 0;
	दीर्घ rx_dbm;

	skb = ptr_rcb->skb;
	rx_status = IEEE80211_SKB_RXCB(skb);

	/* [31:16]RcvByteCount ( not include 4-byte Status ) */
	head = (काष्ठा vnt_rx_header *)skb->data;
	frame_size = head->wbk_status >> 16;
	frame_size += 4;

	अगर (bytes_received != frame_size) अणु
		dev_dbg(&priv->usb->dev, "------- WRONG Length 1\n");
		वापस false;
	पूर्ण

	अगर ((bytes_received > 2372) || (bytes_received <= 40)) अणु
		/* Frame Size error drop this packet.*/
		dev_dbg(&priv->usb->dev, "------ WRONG Length 2\n");
		वापस false;
	पूर्ण

	/* real Frame Size = USBframe_size -4WbkStatus - 4RxStatus */
	/* -8TSF - 4RSR - 4SQ3 - ?Padding */

	/* अगर SQ3 the range is 24~27, अगर no SQ3 the range is 20~23 */

	/*Fix hardware bug => PLCP_Length error */
	अगर (((bytes_received - head->pay_load_len) > 27) ||
	    ((bytes_received - head->pay_load_len) < 24) ||
	    (bytes_received < head->pay_load_len)) अणु
		dev_dbg(&priv->usb->dev, "Wrong PLCP Length %x\n",
			head->pay_load_len);
		वापस false;
	पूर्ण

	sband = hw->wiphy->bands[hw->conf.chandef.chan->band];
	rx_bitrate = head->rx_rate * 5; /* rx_rate * 5 */

	क्रम (ii = 0; ii < sband->n_bitrates; ii++) अणु
		अगर (sband->bitrates[ii].bitrate == rx_bitrate) अणु
			rate_idx = ii;
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ii == sband->n_bitrates) अणु
		dev_dbg(&priv->usb->dev, "Wrong Rx Bit Rate %d\n", rx_bitrate);
		वापस false;
	पूर्ण

	pay_load_with_padding = ((head->pay_load_len / 4) +
		((head->pay_load_len % 4) ? 1 : 0)) * 4;

	tail = (काष्ठा vnt_rx_tail *)(skb->data +
				      माप(*head) + pay_load_with_padding);
	priv->tsf_समय = le64_to_cpu(tail->tsf_समय);

	अगर (tail->rsr & (RSR_IVLDTYP | RSR_IVLDLEN))
		वापस false;

	vnt_rf_rssi_to_dbm(priv, tail->rssi, &rx_dbm);

	priv->bb_pre_ed_rssi = (u8)-rx_dbm + 1;
	priv->current_rssi = priv->bb_pre_ed_rssi;

	skb_pull(skb, माप(*head));
	skb_trim(skb, head->pay_load_len);

	rx_status->maस_समय = priv->tsf_समय;
	rx_status->band = hw->conf.chandef.chan->band;
	rx_status->संकेत = rx_dbm;
	rx_status->flag = 0;
	rx_status->freq = hw->conf.chandef.chan->center_freq;

	अगर (!(tail->rsr & RSR_CRCOK))
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;

	rx_status->rate_idx = rate_idx;

	अगर (tail->new_rsr & NEWRSR_DECRYPTOK)
		rx_status->flag |= RX_FLAG_DECRYPTED;

	ieee80211_rx_irqsafe(priv->hw, skb);

	वापस true;
पूर्ण

अटल व्योम vnt_submit_rx_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा vnt_rcb *rcb = urb->context;
	काष्ठा vnt_निजी *priv = rcb->priv;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	हाल -ETIMEDOUT:
	शेष:
		dev_dbg(&priv->usb->dev, "BULK In failed %d\n", urb->status);
		अवरोध;
	पूर्ण

	अगर (urb->actual_length) अणु
		अगर (vnt_rx_data(priv, rcb, urb->actual_length)) अणु
			rcb->skb = dev_alloc_skb(priv->rx_buf_sz);
			अगर (!rcb->skb)
				वापस;
		पूर्ण अन्यथा अणु
			skb_push(rcb->skb, skb_headroom(rcb->skb));
			skb_trim(rcb->skb, 0);
		पूर्ण

		urb->transfer_buffer = skb_put(rcb->skb,
					       skb_tailroom(rcb->skb));
	पूर्ण

	अगर (usb_submit_urb(urb, GFP_ATOMIC))
		dev_dbg(&priv->usb->dev, "Failed to re submit rx skb\n");
पूर्ण

पूर्णांक vnt_submit_rx_urb(काष्ठा vnt_निजी *priv, काष्ठा vnt_rcb *rcb)
अणु
	पूर्णांक ret = 0;
	काष्ठा urb *urb = rcb->urb;

	अगर (!rcb->skb) अणु
		dev_dbg(&priv->usb->dev, "rcb->skb is null\n");
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	usb_fill_bulk_urb(urb,
			  priv->usb,
			  usb_rcvbulkpipe(priv->usb, 2),
			  skb_put(rcb->skb, skb_tailroom(rcb->skb)),
			  MAX_TOTAL_SIZE_WITH_ALL_HEADERS,
			  vnt_submit_rx_urb_complete,
			  rcb);

	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret)
		dev_dbg(&priv->usb->dev, "Submit Rx URB failed %d\n", ret);
end:
	वापस ret;
पूर्ण

अटल व्योम vnt_tx_context_complete(काष्ठा urb *urb)
अणु
	काष्ठा vnt_usb_send_context *context = urb->context;
	काष्ठा vnt_निजी *priv = context->priv;

	चयन (urb->status) अणु
	हाल 0:
		dev_dbg(&priv->usb->dev,
			"Write %d bytes\n", urb->actual_length);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		context->in_use = false;
		वापस;
	हाल -ETIMEDOUT:
	शेष:
		dev_dbg(&priv->usb->dev, "BULK Out failed %d\n", urb->status);
		अवरोध;
	पूर्ण

	अगर (context->type == CONTEXT_DATA_PACKET)
		ieee80211_wake_queues(priv->hw);

	अगर (urb->status || context->type == CONTEXT_BEACON_PACKET) अणु
		अगर (context->skb)
			ieee80211_मुक्त_txskb(priv->hw, context->skb);

		context->in_use = false;
	पूर्ण
पूर्ण

पूर्णांक vnt_tx_context(काष्ठा vnt_निजी *priv,
		   काष्ठा vnt_usb_send_context *context,
		   काष्ठा sk_buff *skb)
अणु
	काष्ठा vnt_tx_usb_header *usb;
	काष्ठा urb *urb;
	पूर्णांक status;
	u16 count = skb->len;

	usb = skb_push(skb, माप(*usb));
	usb->tx_byte_count = cpu_to_le16(count);
	usb->pkt_no = context->pkt_no;
	usb->type = context->type;

	अगर (test_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags)) अणु
		context->in_use = false;
		वापस -ENODEV;
	पूर्ण

	अगर (skb->len > MAX_TOTAL_SIZE_WITH_ALL_HEADERS) अणु
		context->in_use = false;
		वापस -E2BIG;
	पूर्ण

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		context->in_use = false;
		वापस -ENOMEM;
	पूर्ण

	usb_fill_bulk_urb(urb,
			  priv->usb,
			  usb_sndbulkpipe(priv->usb, 3),
			  skb->data,
			  skb->len,
			  vnt_tx_context_complete,
			  context);

	usb_anchor_urb(urb, &priv->tx_submitted);

	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		dev_dbg(&priv->usb->dev, "Submit Tx URB failed %d\n", status);
		usb_unanchor_urb(urb);
		context->in_use = false;
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस status;
पूर्ण
