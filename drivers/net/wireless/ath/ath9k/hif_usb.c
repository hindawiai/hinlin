<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश "htc.h"

MODULE_FIRMWARE(HTC_7010_MODULE_FW);
MODULE_FIRMWARE(HTC_9271_MODULE_FW);

अटल स्थिर काष्ठा usb_device_id ath9k_hअगर_usb_ids[] = अणु
	अणु USB_DEVICE(0x0cf3, 0x9271) पूर्ण, /* Atheros */
	अणु USB_DEVICE(0x0cf3, 0x1006) पूर्ण, /* Atheros */
	अणु USB_DEVICE(0x0846, 0x9030) पूर्ण, /* Netgear N150 */
	अणु USB_DEVICE(0x07b8, 0x9271) पूर्ण, /* Altai WA1011N-GU */
	अणु USB_DEVICE(0x07D1, 0x3A10) पूर्ण, /* Dlink Wireless 150 */
	अणु USB_DEVICE(0x13D3, 0x3327) पूर्ण, /* Azurewave */
	अणु USB_DEVICE(0x13D3, 0x3328) पूर्ण, /* Azurewave */
	अणु USB_DEVICE(0x13D3, 0x3346) पूर्ण, /* IMC Networks */
	अणु USB_DEVICE(0x13D3, 0x3348) पूर्ण, /* Azurewave */
	अणु USB_DEVICE(0x13D3, 0x3349) पूर्ण, /* Azurewave */
	अणु USB_DEVICE(0x13D3, 0x3350) पूर्ण, /* Azurewave */
	अणु USB_DEVICE(0x04CA, 0x4605) पूर्ण, /* Liteon */
	अणु USB_DEVICE(0x040D, 0x3801) पूर्ण, /* VIA */
	अणु USB_DEVICE(0x0cf3, 0xb003) पूर्ण, /* Ubiquiti WअगरiStation Ext */
	अणु USB_DEVICE(0x0cf3, 0xb002) पूर्ण, /* Ubiquiti WअगरiStation */
	अणु USB_DEVICE(0x057c, 0x8403) पूर्ण, /* AVM FRITZ!WLAN 11N v2 USB */
	अणु USB_DEVICE(0x0471, 0x209e) पूर्ण, /* Philips (or NXP) PTA01 */
	अणु USB_DEVICE(0x1eda, 0x2315) पूर्ण, /* AirTies */

	अणु USB_DEVICE(0x0cf3, 0x7015),
	  .driver_info = AR9287_USB पूर्ण,  /* Atheros */
	अणु USB_DEVICE(0x1668, 0x1200),
	  .driver_info = AR9287_USB पूर्ण,  /* Verizon */

	अणु USB_DEVICE(0x0cf3, 0x7010),
	  .driver_info = AR9280_USB पूर्ण,  /* Atheros */
	अणु USB_DEVICE(0x0846, 0x9018),
	  .driver_info = AR9280_USB पूर्ण,  /* Netgear WNDA3200 */
	अणु USB_DEVICE(0x083A, 0xA704),
	  .driver_info = AR9280_USB पूर्ण,  /* SMC Networks */
	अणु USB_DEVICE(0x0411, 0x017f),
	  .driver_info = AR9280_USB पूर्ण,  /* Sony UWA-BR100 */
	अणु USB_DEVICE(0x0411, 0x0197),
	  .driver_info = AR9280_USB पूर्ण,  /* Buffalo WLI-UV-AG300P */
	अणु USB_DEVICE(0x04da, 0x3904),
	  .driver_info = AR9280_USB पूर्ण,
	अणु USB_DEVICE(0x0930, 0x0a08),
	  .driver_info = AR9280_USB पूर्ण,  /* Toshiba WLM-20U2 and GN-1080 */

	अणु USB_DEVICE(0x0cf3, 0x20ff),
	  .driver_info = STORAGE_DEVICE पूर्ण,

	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, ath9k_hअगर_usb_ids);

अटल पूर्णांक __hअगर_usb_tx(काष्ठा hअगर_device_usb *hअगर_dev);

अटल व्योम hअगर_usb_regout_cb(काष्ठा urb *urb)
अणु
	काष्ठा cmd_buf *cmd = (काष्ठा cmd_buf *)urb->context;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		जाओ मुक्त;
	शेष:
		अवरोध;
	पूर्ण

	अगर (cmd) अणु
		ath9k_htc_txcompletion_cb(cmd->hअगर_dev->htc_handle,
					  cmd->skb, true);
		kमुक्त(cmd);
	पूर्ण

	वापस;
मुक्त:
	kमुक्त_skb(cmd->skb);
	kमुक्त(cmd);
पूर्ण

अटल पूर्णांक hअगर_usb_send_regout(काष्ठा hअगर_device_usb *hअगर_dev,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा urb *urb;
	काष्ठा cmd_buf *cmd;
	पूर्णांक ret = 0;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (urb == शून्य)
		वापस -ENOMEM;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (cmd == शून्य) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	cmd->skb = skb;
	cmd->hअगर_dev = hअगर_dev;

	usb_fill_पूर्णांक_urb(urb, hअगर_dev->udev,
			 usb_sndपूर्णांकpipe(hअगर_dev->udev, USB_REG_OUT_PIPE),
			 skb->data, skb->len,
			 hअगर_usb_regout_cb, cmd, 1);

	usb_anchor_urb(urb, &hअगर_dev->regout_submitted);
	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret) अणु
		usb_unanchor_urb(urb);
		kमुक्त(cmd);
	पूर्ण
	usb_मुक्त_urb(urb);

	वापस ret;
पूर्ण

अटल व्योम hअगर_usb_mgmt_cb(काष्ठा urb *urb)
अणु
	काष्ठा cmd_buf *cmd = (काष्ठा cmd_buf *)urb->context;
	काष्ठा hअगर_device_usb *hअगर_dev;
	अचिन्हित दीर्घ flags;
	bool txok = true;

	अगर (!cmd || !cmd->skb || !cmd->hअगर_dev)
		वापस;

	hअगर_dev = cmd->hअगर_dev;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		txok = false;

		/*
		 * If the URBs are being flushed, no need to complete
		 * this packet.
		 */
		spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
		अगर (hअगर_dev->tx.flags & HIF_USB_TX_FLUSH) अणु
			spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);
			dev_kमुक्त_skb_any(cmd->skb);
			kमुक्त(cmd);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);

		अवरोध;
	शेष:
		txok = false;
		अवरोध;
	पूर्ण

	skb_pull(cmd->skb, 4);
	ath9k_htc_txcompletion_cb(cmd->hअगर_dev->htc_handle,
				  cmd->skb, txok);
	kमुक्त(cmd);
पूर्ण

अटल पूर्णांक hअगर_usb_send_mgmt(काष्ठा hअगर_device_usb *hअगर_dev,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा urb *urb;
	काष्ठा cmd_buf *cmd;
	पूर्णांक ret = 0;
	__le16 *hdr;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (urb == शून्य)
		वापस -ENOMEM;

	cmd = kzalloc(माप(*cmd), GFP_ATOMIC);
	अगर (cmd == शून्य) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	cmd->skb = skb;
	cmd->hअगर_dev = hअगर_dev;

	hdr = skb_push(skb, 4);
	*hdr++ = cpu_to_le16(skb->len - 4);
	*hdr++ = cpu_to_le16(ATH_USB_TX_STREAM_MODE_TAG);

	usb_fill_bulk_urb(urb, hअगर_dev->udev,
			 usb_sndbulkpipe(hअगर_dev->udev, USB_WLAN_TX_PIPE),
			 skb->data, skb->len,
			 hअगर_usb_mgmt_cb, cmd);

	usb_anchor_urb(urb, &hअगर_dev->mgmt_submitted);
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		usb_unanchor_urb(urb);
		kमुक्त(cmd);
	पूर्ण
	usb_मुक्त_urb(urb);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ath9k_skb_queue_purge(काष्ठा hअगर_device_usb *hअगर_dev,
					 काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(list)) != शून्य) अणु
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ath9k_skb_queue_complete(काष्ठा hअगर_device_usb *hअगर_dev,
					    काष्ठा sk_buff_head *queue,
					    bool txok)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(queue)) != शून्य) अणु
#अगर_घोषित CONFIG_ATH9K_HTC_DEBUGFS
		पूर्णांक ln = skb->len;
#पूर्ण_अगर
		ath9k_htc_txcompletion_cb(hअगर_dev->htc_handle,
					  skb, txok);
		अगर (txok) अणु
			TX_STAT_INC(skb_success);
			TX_STAT_ADD(skb_success_bytes, ln);
		पूर्ण
		अन्यथा
			TX_STAT_INC(skb_failed);
	पूर्ण
पूर्ण

अटल व्योम hअगर_usb_tx_cb(काष्ठा urb *urb)
अणु
	काष्ठा tx_buf *tx_buf = (काष्ठा tx_buf *) urb->context;
	काष्ठा hअगर_device_usb *hअगर_dev;
	bool txok = true;

	अगर (!tx_buf || !tx_buf->hअगर_dev)
		वापस;

	hअगर_dev = tx_buf->hअगर_dev;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		txok = false;

		/*
		 * If the URBs are being flushed, no need to add this
		 * URB to the मुक्त list.
		 */
		spin_lock(&hअगर_dev->tx.tx_lock);
		अगर (hअगर_dev->tx.flags & HIF_USB_TX_FLUSH) अणु
			spin_unlock(&hअगर_dev->tx.tx_lock);
			ath9k_skb_queue_purge(hअगर_dev, &tx_buf->skb_queue);
			वापस;
		पूर्ण
		spin_unlock(&hअगर_dev->tx.tx_lock);

		अवरोध;
	शेष:
		txok = false;
		अवरोध;
	पूर्ण

	ath9k_skb_queue_complete(hअगर_dev, &tx_buf->skb_queue, txok);

	/* Re-initialize the SKB queue */
	tx_buf->len = tx_buf->offset = 0;
	__skb_queue_head_init(&tx_buf->skb_queue);

	/* Add this TX buffer to the मुक्त list */
	spin_lock(&hअगर_dev->tx.tx_lock);
	list_move_tail(&tx_buf->list, &hअगर_dev->tx.tx_buf);
	hअगर_dev->tx.tx_buf_cnt++;
	अगर (!(hअगर_dev->tx.flags & HIF_USB_TX_STOP))
		__hअगर_usb_tx(hअगर_dev); /* Check क्रम pending SKBs */
	TX_STAT_INC(buf_completed);
	spin_unlock(&hअगर_dev->tx.tx_lock);
पूर्ण

/* TX lock has to be taken */
अटल पूर्णांक __hअगर_usb_tx(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	काष्ठा tx_buf *tx_buf = शून्य;
	काष्ठा sk_buff *nskb = शून्य;
	पूर्णांक ret = 0, i;
	u16 tx_skb_cnt = 0;
	u8 *buf;
	__le16 *hdr;

	अगर (hअगर_dev->tx.tx_skb_cnt == 0)
		वापस 0;

	/* Check अगर a मुक्त TX buffer is available */
	अगर (list_empty(&hअगर_dev->tx.tx_buf))
		वापस 0;

	tx_buf = list_first_entry(&hअगर_dev->tx.tx_buf, काष्ठा tx_buf, list);
	list_move_tail(&tx_buf->list, &hअगर_dev->tx.tx_pending);
	hअगर_dev->tx.tx_buf_cnt--;

	tx_skb_cnt = min_t(u16, hअगर_dev->tx.tx_skb_cnt, MAX_TX_AGGR_NUM);

	क्रम (i = 0; i < tx_skb_cnt; i++) अणु
		nskb = __skb_dequeue(&hअगर_dev->tx.tx_skb_queue);

		/* Should never be शून्य */
		BUG_ON(!nskb);

		hअगर_dev->tx.tx_skb_cnt--;

		buf = tx_buf->buf;
		buf += tx_buf->offset;
		hdr = (__le16 *)buf;
		*hdr++ = cpu_to_le16(nskb->len);
		*hdr++ = cpu_to_le16(ATH_USB_TX_STREAM_MODE_TAG);
		buf += 4;
		स_नकल(buf, nskb->data, nskb->len);
		tx_buf->len = nskb->len + 4;

		अगर (i < (tx_skb_cnt - 1))
			tx_buf->offset += (((tx_buf->len - 1) / 4) + 1) * 4;

		अगर (i == (tx_skb_cnt - 1))
			tx_buf->len += tx_buf->offset;

		__skb_queue_tail(&tx_buf->skb_queue, nskb);
		TX_STAT_INC(skb_queued);
	पूर्ण

	usb_fill_bulk_urb(tx_buf->urb, hअगर_dev->udev,
			  usb_sndbulkpipe(hअगर_dev->udev, USB_WLAN_TX_PIPE),
			  tx_buf->buf, tx_buf->len,
			  hअगर_usb_tx_cb, tx_buf);

	ret = usb_submit_urb(tx_buf->urb, GFP_ATOMIC);
	अगर (ret) अणु
		tx_buf->len = tx_buf->offset = 0;
		ath9k_skb_queue_complete(hअगर_dev, &tx_buf->skb_queue, false);
		__skb_queue_head_init(&tx_buf->skb_queue);
		list_move_tail(&tx_buf->list, &hअगर_dev->tx.tx_buf);
		hअगर_dev->tx.tx_buf_cnt++;
	पूर्ण

	अगर (!ret)
		TX_STAT_INC(buf_queued);

	वापस ret;
पूर्ण

अटल पूर्णांक hअगर_usb_send_tx(काष्ठा hअगर_device_usb *hअगर_dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);

	अगर (hअगर_dev->tx.flags & HIF_USB_TX_STOP) अणु
		spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);
		वापस -ENODEV;
	पूर्ण

	/* Check अगर the max queue count has been reached */
	अगर (hअगर_dev->tx.tx_skb_cnt > MAX_TX_BUF_NUM) अणु
		spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);
		वापस -ENOMEM;
	पूर्ण

	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);

	tx_ctl = HTC_SKB_CB(skb);

	/* Mgmt/Beacon frames करोn't use the TX buffer pool */
	अगर ((tx_ctl->type == ATH9K_HTC_MGMT) ||
	    (tx_ctl->type == ATH9K_HTC_BEACON)) अणु
		ret = hअगर_usb_send_mgmt(hअगर_dev, skb);
	पूर्ण

	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);

	अगर ((tx_ctl->type == ATH9K_HTC_NORMAL) ||
	    (tx_ctl->type == ATH9K_HTC_AMPDU)) अणु
		__skb_queue_tail(&hअगर_dev->tx.tx_skb_queue, skb);
		hअगर_dev->tx.tx_skb_cnt++;
	पूर्ण

	/* Check अगर AMPDUs have to be sent immediately */
	अगर ((hअगर_dev->tx.tx_buf_cnt == MAX_TX_URB_NUM) &&
	    (hअगर_dev->tx.tx_skb_cnt < 2)) अणु
		__hअगर_usb_tx(hअगर_dev);
	पूर्ण

	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम hअगर_usb_start(व्योम *hअगर_handle)
अणु
	काष्ठा hअगर_device_usb *hअगर_dev = hअगर_handle;
	अचिन्हित दीर्घ flags;

	hअगर_dev->flags |= HIF_USB_START;

	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	hअगर_dev->tx.flags &= ~HIF_USB_TX_STOP;
	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);
पूर्ण

अटल व्योम hअगर_usb_stop(व्योम *hअगर_handle)
अणु
	काष्ठा hअगर_device_usb *hअगर_dev = hअगर_handle;
	काष्ठा tx_buf *tx_buf = शून्य, *tx_buf_पंचांगp = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	ath9k_skb_queue_complete(hअगर_dev, &hअगर_dev->tx.tx_skb_queue, false);
	hअगर_dev->tx.tx_skb_cnt = 0;
	hअगर_dev->tx.flags |= HIF_USB_TX_STOP;
	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);

	/* The pending URBs have to be canceled. */
	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	list_क्रम_each_entry_safe(tx_buf, tx_buf_पंचांगp,
				 &hअगर_dev->tx.tx_pending, list) अणु
		usb_get_urb(tx_buf->urb);
		spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);
		usb_समाप्त_urb(tx_buf->urb);
		list_del(&tx_buf->list);
		usb_मुक्त_urb(tx_buf->urb);
		kमुक्त(tx_buf->buf);
		kमुक्त(tx_buf);
		spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);

	usb_समाप्त_anchored_urbs(&hअगर_dev->mgmt_submitted);
पूर्ण

अटल पूर्णांक hअगर_usb_send(व्योम *hअगर_handle, u8 pipe_id, काष्ठा sk_buff *skb)
अणु
	काष्ठा hअगर_device_usb *hअगर_dev = hअगर_handle;
	पूर्णांक ret = 0;

	चयन (pipe_id) अणु
	हाल USB_WLAN_TX_PIPE:
		ret = hअगर_usb_send_tx(hअगर_dev, skb);
		अवरोध;
	हाल USB_REG_OUT_PIPE:
		ret = hअगर_usb_send_regout(hअगर_dev, skb);
		अवरोध;
	शेष:
		dev_err(&hअगर_dev->udev->dev,
			"ath9k_htc: Invalid TX pipe: %d\n", pipe_id);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत bool check_index(काष्ठा sk_buff *skb, u8 idx)
अणु
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;

	tx_ctl = HTC_SKB_CB(skb);

	अगर ((tx_ctl->type == ATH9K_HTC_AMPDU) &&
	    (tx_ctl->sta_idx == idx))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम hअगर_usb_sta_drain(व्योम *hअगर_handle, u8 idx)
अणु
	काष्ठा hअगर_device_usb *hअगर_dev = hअगर_handle;
	काष्ठा sk_buff *skb, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);

	skb_queue_walk_safe(&hअगर_dev->tx.tx_skb_queue, skb, पंचांगp) अणु
		अगर (check_index(skb, idx)) अणु
			__skb_unlink(skb, &hअगर_dev->tx.tx_skb_queue);
			ath9k_htc_txcompletion_cb(hअगर_dev->htc_handle,
						  skb, false);
			hअगर_dev->tx.tx_skb_cnt--;
			TX_STAT_INC(skb_failed);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);
पूर्ण

अटल काष्ठा ath9k_htc_hअगर hअगर_usb = अणु
	.transport = ATH9K_HIF_USB,
	.name = "ath9k_hif_usb",

	.control_ul_pipe = USB_REG_OUT_PIPE,
	.control_dl_pipe = USB_REG_IN_PIPE,

	.start = hअगर_usb_start,
	.stop = hअगर_usb_stop,
	.sta_drain = hअगर_usb_sta_drain,
	.send = hअगर_usb_send,
पूर्ण;

अटल व्योम ath9k_hअगर_usb_rx_stream(काष्ठा hअगर_device_usb *hअगर_dev,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nskb, *skb_pool[MAX_PKT_NUM_IN_TRANSFER];
	पूर्णांक index = 0, i, len = skb->len;
	पूर्णांक rx_reमुख्य_len, rx_pkt_len;
	u16 pool_index = 0;
	u8 *ptr;

	spin_lock(&hअगर_dev->rx_lock);

	rx_reमुख्य_len = hअगर_dev->rx_reमुख्य_len;
	rx_pkt_len = hअगर_dev->rx_transfer_len;

	अगर (rx_reमुख्य_len != 0) अणु
		काष्ठा sk_buff *reमुख्य_skb = hअगर_dev->reमुख्य_skb;

		अगर (reमुख्य_skb) अणु
			ptr = (u8 *) reमुख्य_skb->data;

			index = rx_reमुख्य_len;
			rx_reमुख्य_len -= hअगर_dev->rx_pad_len;
			ptr += rx_pkt_len;

			स_नकल(ptr, skb->data, rx_reमुख्य_len);

			rx_pkt_len += rx_reमुख्य_len;
			hअगर_dev->rx_reमुख्य_len = 0;
			skb_put(reमुख्य_skb, rx_pkt_len);

			skb_pool[pool_index++] = reमुख्य_skb;

		पूर्ण अन्यथा अणु
			index = rx_reमुख्य_len;
		पूर्ण
	पूर्ण

	spin_unlock(&hअगर_dev->rx_lock);

	जबतक (index < len) अणु
		u16 pkt_len;
		u16 pkt_tag;
		u16 pad_len;
		पूर्णांक chk_idx;

		ptr = (u8 *) skb->data;

		pkt_len = get_unaligned_le16(ptr + index);
		pkt_tag = get_unaligned_le16(ptr + index + 2);

		अगर (pkt_tag != ATH_USB_RX_STREAM_MODE_TAG) अणु
			RX_STAT_INC(skb_dropped);
			वापस;
		पूर्ण

		pad_len = 4 - (pkt_len & 0x3);
		अगर (pad_len == 4)
			pad_len = 0;

		chk_idx = index;
		index = index + 4 + pkt_len + pad_len;

		अगर (index > MAX_RX_BUF_SIZE) अणु
			spin_lock(&hअगर_dev->rx_lock);
			hअगर_dev->rx_reमुख्य_len = index - MAX_RX_BUF_SIZE;
			hअगर_dev->rx_transfer_len =
				MAX_RX_BUF_SIZE - chk_idx - 4;
			hअगर_dev->rx_pad_len = pad_len;

			nskb = __dev_alloc_skb(pkt_len + 32, GFP_ATOMIC);
			अगर (!nskb) अणु
				dev_err(&hअगर_dev->udev->dev,
					"ath9k_htc: RX memory allocation error\n");
				spin_unlock(&hअगर_dev->rx_lock);
				जाओ err;
			पूर्ण
			skb_reserve(nskb, 32);
			RX_STAT_INC(skb_allocated);

			स_नकल(nskb->data, &(skb->data[chk_idx+4]),
			       hअगर_dev->rx_transfer_len);

			/* Record the buffer poपूर्णांकer */
			hअगर_dev->reमुख्य_skb = nskb;
			spin_unlock(&hअगर_dev->rx_lock);
		पूर्ण अन्यथा अणु
			अगर (pool_index == MAX_PKT_NUM_IN_TRANSFER) अणु
				dev_err(&hअगर_dev->udev->dev,
					"ath9k_htc: over RX MAX_PKT_NUM\n");
				जाओ err;
			पूर्ण
			nskb = __dev_alloc_skb(pkt_len + 32, GFP_ATOMIC);
			अगर (!nskb) अणु
				dev_err(&hअगर_dev->udev->dev,
					"ath9k_htc: RX memory allocation error\n");
				जाओ err;
			पूर्ण
			skb_reserve(nskb, 32);
			RX_STAT_INC(skb_allocated);

			स_नकल(nskb->data, &(skb->data[chk_idx+4]), pkt_len);
			skb_put(nskb, pkt_len);
			skb_pool[pool_index++] = nskb;
		पूर्ण
	पूर्ण

err:
	क्रम (i = 0; i < pool_index; i++) अणु
		RX_STAT_ADD(skb_completed_bytes, skb_pool[i]->len);
		ath9k_htc_rx_msg(hअगर_dev->htc_handle, skb_pool[i],
				 skb_pool[i]->len, USB_WLAN_RX_PIPE);
		RX_STAT_INC(skb_completed);
	पूर्ण
पूर्ण

अटल व्योम ath9k_hअगर_usb_rx_cb(काष्ठा urb *urb)
अणु
	काष्ठा rx_buf *rx_buf = (काष्ठा rx_buf *)urb->context;
	काष्ठा hअगर_device_usb *hअगर_dev = rx_buf->hअगर_dev;
	काष्ठा sk_buff *skb = rx_buf->skb;
	पूर्णांक ret;

	अगर (!skb)
		वापस;

	अगर (!hअगर_dev)
		जाओ मुक्त;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		जाओ मुक्त;
	शेष:
		जाओ resubmit;
	पूर्ण

	अगर (likely(urb->actual_length != 0)) अणु
		skb_put(skb, urb->actual_length);
		ath9k_hअगर_usb_rx_stream(hअगर_dev, skb);
	पूर्ण

resubmit:
	skb_reset_tail_poपूर्णांकer(skb);
	skb_trim(skb, 0);

	usb_anchor_urb(urb, &hअगर_dev->rx_submitted);
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		usb_unanchor_urb(urb);
		जाओ मुक्त;
	पूर्ण

	वापस;
मुक्त:
	kमुक्त_skb(skb);
	kमुक्त(rx_buf);
पूर्ण

अटल व्योम ath9k_hअगर_usb_reg_in_cb(काष्ठा urb *urb)
अणु
	काष्ठा rx_buf *rx_buf = (काष्ठा rx_buf *)urb->context;
	काष्ठा hअगर_device_usb *hअगर_dev = rx_buf->hअगर_dev;
	काष्ठा sk_buff *skb = rx_buf->skb;
	काष्ठा sk_buff *nskb;
	पूर्णांक ret;

	अगर (!skb)
		वापस;

	अगर (!hअगर_dev)
		जाओ मुक्त;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ENODEV:
	हाल -ESHUTDOWN:
		जाओ मुक्त;
	शेष:
		skb_reset_tail_poपूर्णांकer(skb);
		skb_trim(skb, 0);

		जाओ resubmit;
	पूर्ण

	अगर (likely(urb->actual_length != 0)) अणु
		skb_put(skb, urb->actual_length);

		/* Process the command first */
		ath9k_htc_rx_msg(hअगर_dev->htc_handle, skb,
				 skb->len, USB_REG_IN_PIPE);


		nskb = alloc_skb(MAX_REG_IN_BUF_SIZE, GFP_ATOMIC);
		अगर (!nskb) अणु
			dev_err(&hअगर_dev->udev->dev,
				"ath9k_htc: REG_IN memory allocation failure\n");
			urb->context = शून्य;
			वापस;
		पूर्ण

		rx_buf->skb = nskb;

		usb_fill_पूर्णांक_urb(urb, hअगर_dev->udev,
				 usb_rcvपूर्णांकpipe(hअगर_dev->udev,
						 USB_REG_IN_PIPE),
				 nskb->data, MAX_REG_IN_BUF_SIZE,
				 ath9k_hअगर_usb_reg_in_cb, rx_buf, 1);
	पूर्ण

resubmit:
	usb_anchor_urb(urb, &hअगर_dev->reg_in_submitted);
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		usb_unanchor_urb(urb);
		जाओ मुक्त;
	पूर्ण

	वापस;
मुक्त:
	kमुक्त_skb(skb);
	kमुक्त(rx_buf);
	urb->context = शून्य;
पूर्ण

अटल व्योम ath9k_hअगर_usb_dealloc_tx_urbs(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	काष्ठा tx_buf *tx_buf = शून्य, *tx_buf_पंचांगp = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	list_क्रम_each_entry_safe(tx_buf, tx_buf_पंचांगp,
				 &hअगर_dev->tx.tx_buf, list) अणु
		usb_get_urb(tx_buf->urb);
		spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);
		usb_समाप्त_urb(tx_buf->urb);
		list_del(&tx_buf->list);
		usb_मुक्त_urb(tx_buf->urb);
		kमुक्त(tx_buf->buf);
		kमुक्त(tx_buf);
		spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);

	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	hअगर_dev->tx.flags |= HIF_USB_TX_FLUSH;
	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);

	spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	list_क्रम_each_entry_safe(tx_buf, tx_buf_पंचांगp,
				 &hअगर_dev->tx.tx_pending, list) अणु
		usb_get_urb(tx_buf->urb);
		spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);
		usb_समाप्त_urb(tx_buf->urb);
		list_del(&tx_buf->list);
		usb_मुक्त_urb(tx_buf->urb);
		kमुक्त(tx_buf->buf);
		kमुक्त(tx_buf);
		spin_lock_irqsave(&hअगर_dev->tx.tx_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&hअगर_dev->tx.tx_lock, flags);

	usb_समाप्त_anchored_urbs(&hअगर_dev->mgmt_submitted);
पूर्ण

अटल पूर्णांक ath9k_hअगर_usb_alloc_tx_urbs(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	काष्ठा tx_buf *tx_buf;
	पूर्णांक i;

	INIT_LIST_HEAD(&hअगर_dev->tx.tx_buf);
	INIT_LIST_HEAD(&hअगर_dev->tx.tx_pending);
	spin_lock_init(&hअगर_dev->tx.tx_lock);
	__skb_queue_head_init(&hअगर_dev->tx.tx_skb_queue);
	init_usb_anchor(&hअगर_dev->mgmt_submitted);

	क्रम (i = 0; i < MAX_TX_URB_NUM; i++) अणु
		tx_buf = kzalloc(माप(*tx_buf), GFP_KERNEL);
		अगर (!tx_buf)
			जाओ err;

		tx_buf->buf = kzalloc(MAX_TX_BUF_SIZE, GFP_KERNEL);
		अगर (!tx_buf->buf)
			जाओ err;

		tx_buf->urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!tx_buf->urb)
			जाओ err;

		tx_buf->hअगर_dev = hअगर_dev;
		__skb_queue_head_init(&tx_buf->skb_queue);

		list_add_tail(&tx_buf->list, &hअगर_dev->tx.tx_buf);
	पूर्ण

	hअगर_dev->tx.tx_buf_cnt = MAX_TX_URB_NUM;

	वापस 0;
err:
	अगर (tx_buf) अणु
		kमुक्त(tx_buf->buf);
		kमुक्त(tx_buf);
	पूर्ण
	ath9k_hअगर_usb_dealloc_tx_urbs(hअगर_dev);
	वापस -ENOMEM;
पूर्ण

अटल व्योम ath9k_hअगर_usb_dealloc_rx_urbs(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	usb_समाप्त_anchored_urbs(&hअगर_dev->rx_submitted);
पूर्ण

अटल पूर्णांक ath9k_hअगर_usb_alloc_rx_urbs(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	काष्ठा rx_buf *rx_buf = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा urb *urb = शून्य;
	पूर्णांक i, ret;

	init_usb_anchor(&hअगर_dev->rx_submitted);
	spin_lock_init(&hअगर_dev->rx_lock);

	क्रम (i = 0; i < MAX_RX_URB_NUM; i++) अणु

		rx_buf = kzalloc(माप(*rx_buf), GFP_KERNEL);
		अगर (!rx_buf) अणु
			ret = -ENOMEM;
			जाओ err_rxb;
		पूर्ण

		/* Allocate URB */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (urb == शून्य) अणु
			ret = -ENOMEM;
			जाओ err_urb;
		पूर्ण

		/* Allocate buffer */
		skb = alloc_skb(MAX_RX_BUF_SIZE, GFP_KERNEL);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ err_skb;
		पूर्ण

		rx_buf->hअगर_dev = hअगर_dev;
		rx_buf->skb = skb;

		usb_fill_bulk_urb(urb, hअगर_dev->udev,
				  usb_rcvbulkpipe(hअगर_dev->udev,
						  USB_WLAN_RX_PIPE),
				  skb->data, MAX_RX_BUF_SIZE,
				  ath9k_hअगर_usb_rx_cb, rx_buf);

		/* Anchor URB */
		usb_anchor_urb(urb, &hअगर_dev->rx_submitted);

		/* Submit URB */
		ret = usb_submit_urb(urb, GFP_KERNEL);
		अगर (ret) अणु
			usb_unanchor_urb(urb);
			जाओ err_submit;
		पूर्ण

		/*
		 * Drop reference count.
		 * This ensures that the URB is मुक्तd when समाप्तing them.
		 */
		usb_मुक्त_urb(urb);
	पूर्ण

	वापस 0;

err_submit:
	kमुक्त_skb(skb);
err_skb:
	usb_मुक्त_urb(urb);
err_urb:
	kमुक्त(rx_buf);
err_rxb:
	ath9k_hअगर_usb_dealloc_rx_urbs(hअगर_dev);
	वापस ret;
पूर्ण

अटल व्योम ath9k_hअगर_usb_dealloc_reg_in_urbs(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	usb_समाप्त_anchored_urbs(&hअगर_dev->reg_in_submitted);
पूर्ण

अटल पूर्णांक ath9k_hअगर_usb_alloc_reg_in_urbs(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	काष्ठा rx_buf *rx_buf = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा urb *urb = शून्य;
	पूर्णांक i, ret;

	init_usb_anchor(&hअगर_dev->reg_in_submitted);

	क्रम (i = 0; i < MAX_REG_IN_URB_NUM; i++) अणु

		rx_buf = kzalloc(माप(*rx_buf), GFP_KERNEL);
		अगर (!rx_buf) अणु
			ret = -ENOMEM;
			जाओ err_rxb;
		पूर्ण

		/* Allocate URB */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (urb == शून्य) अणु
			ret = -ENOMEM;
			जाओ err_urb;
		पूर्ण

		/* Allocate buffer */
		skb = alloc_skb(MAX_REG_IN_BUF_SIZE, GFP_KERNEL);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ err_skb;
		पूर्ण

		rx_buf->hअगर_dev = hअगर_dev;
		rx_buf->skb = skb;

		usb_fill_पूर्णांक_urb(urb, hअगर_dev->udev,
				  usb_rcvपूर्णांकpipe(hअगर_dev->udev,
						  USB_REG_IN_PIPE),
				  skb->data, MAX_REG_IN_BUF_SIZE,
				  ath9k_hअगर_usb_reg_in_cb, rx_buf, 1);

		/* Anchor URB */
		usb_anchor_urb(urb, &hअगर_dev->reg_in_submitted);

		/* Submit URB */
		ret = usb_submit_urb(urb, GFP_KERNEL);
		अगर (ret) अणु
			usb_unanchor_urb(urb);
			जाओ err_submit;
		पूर्ण

		/*
		 * Drop reference count.
		 * This ensures that the URB is मुक्तd when समाप्तing them.
		 */
		usb_मुक्त_urb(urb);
	पूर्ण

	वापस 0;

err_submit:
	kमुक्त_skb(skb);
err_skb:
	usb_मुक्त_urb(urb);
err_urb:
	kमुक्त(rx_buf);
err_rxb:
	ath9k_hअगर_usb_dealloc_reg_in_urbs(hअगर_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक ath9k_hअगर_usb_alloc_urbs(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	/* Register Write */
	init_usb_anchor(&hअगर_dev->regout_submitted);

	/* TX */
	अगर (ath9k_hअगर_usb_alloc_tx_urbs(hअगर_dev) < 0)
		जाओ err;

	/* RX */
	अगर (ath9k_hअगर_usb_alloc_rx_urbs(hअगर_dev) < 0)
		जाओ err_rx;

	/* Register Read */
	अगर (ath9k_hअगर_usb_alloc_reg_in_urbs(hअगर_dev) < 0)
		जाओ err_reg;

	वापस 0;
err_reg:
	ath9k_hअगर_usb_dealloc_rx_urbs(hअगर_dev);
err_rx:
	ath9k_hअगर_usb_dealloc_tx_urbs(hअगर_dev);
err:
	वापस -ENOMEM;
पूर्ण

व्योम ath9k_hअगर_usb_dealloc_urbs(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	usb_समाप्त_anchored_urbs(&hअगर_dev->regout_submitted);
	ath9k_hअगर_usb_dealloc_reg_in_urbs(hअगर_dev);
	ath9k_hअगर_usb_dealloc_tx_urbs(hअगर_dev);
	ath9k_hअगर_usb_dealloc_rx_urbs(hअगर_dev);
पूर्ण

अटल पूर्णांक ath9k_hअगर_usb_करोwnload_fw(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	पूर्णांक transfer, err;
	स्थिर व्योम *data = hअगर_dev->fw_data;
	माप_प्रकार len = hअगर_dev->fw_size;
	u32 addr = AR9271_FIRMWARE;
	u8 *buf = kzalloc(4096, GFP_KERNEL);
	u32 firm_offset;

	अगर (!buf)
		वापस -ENOMEM;

	जबतक (len) अणु
		transfer = min_t(माप_प्रकार, len, 4096);
		स_नकल(buf, data, transfer);

		err = usb_control_msg(hअगर_dev->udev,
				      usb_sndctrlpipe(hअगर_dev->udev, 0),
				      FIRMWARE_DOWNLOAD, 0x40 | USB_सूची_OUT,
				      addr >> 8, 0, buf, transfer,
				      USB_MSG_TIMEOUT);
		अगर (err < 0) अणु
			kमुक्त(buf);
			वापस err;
		पूर्ण

		len -= transfer;
		data += transfer;
		addr += transfer;
	पूर्ण
	kमुक्त(buf);

	अगर (IS_AR7010_DEVICE(hअगर_dev->usb_device_id->driver_info))
		firm_offset = AR7010_FIRMWARE_TEXT;
	अन्यथा
		firm_offset = AR9271_FIRMWARE_TEXT;

	/*
	 * Issue FW करोwnload complete command to firmware.
	 */
	err = usb_control_msg(hअगर_dev->udev, usb_sndctrlpipe(hअगर_dev->udev, 0),
			      FIRMWARE_DOWNLOAD_COMP,
			      0x40 | USB_सूची_OUT,
			      firm_offset >> 8, 0, शून्य, 0, USB_MSG_TIMEOUT);
	अगर (err)
		वापस -EIO;

	dev_info(&hअगर_dev->udev->dev, "ath9k_htc: Transferred FW: %s, size: %ld\n",
		 hअगर_dev->fw_name, (अचिन्हित दीर्घ) hअगर_dev->fw_size);

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_hअगर_usb_dev_init(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	पूर्णांक ret;

	ret = ath9k_hअगर_usb_करोwnload_fw(hअगर_dev);
	अगर (ret) अणु
		dev_err(&hअगर_dev->udev->dev,
			"ath9k_htc: Firmware - %s download failed\n",
			hअगर_dev->fw_name);
		वापस ret;
	पूर्ण

	/* Alloc URBs */
	ret = ath9k_hअगर_usb_alloc_urbs(hअगर_dev);
	अगर (ret) अणु
		dev_err(&hअगर_dev->udev->dev,
			"ath9k_htc: Unable to allocate URBs\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath9k_hअगर_usb_dev_deinit(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	ath9k_hअगर_usb_dealloc_urbs(hअगर_dev);
पूर्ण

/*
 * If initialization fails or the FW cannot be retrieved,
 * detach the device.
 */
अटल व्योम ath9k_hअगर_usb_firmware_fail(काष्ठा hअगर_device_usb *hअगर_dev)
अणु
	काष्ठा device *dev = &hअगर_dev->udev->dev;
	काष्ठा device *parent = dev->parent;

	complete_all(&hअगर_dev->fw_करोne);

	अगर (parent)
		device_lock(parent);

	device_release_driver(dev);

	अगर (parent)
		device_unlock(parent);
पूर्ण

अटल व्योम ath9k_hअगर_usb_firmware_cb(स्थिर काष्ठा firmware *fw, व्योम *context);

/* taken from iwlwअगरi */
अटल पूर्णांक ath9k_hअगर_request_firmware(काष्ठा hअगर_device_usb *hअगर_dev,
				      bool first)
अणु
	अक्षर index[8], *chip;
	पूर्णांक ret;

	अगर (first) अणु
		अगर (htc_use_dev_fw) अणु
			hअगर_dev->fw_minor_index = FIRMWARE_MINOR_IDX_MAX + 1;
			प्र_लिखो(index, "%s", "dev");
		पूर्ण अन्यथा अणु
			hअगर_dev->fw_minor_index = FIRMWARE_MINOR_IDX_MAX;
			प्र_लिखो(index, "%d", hअगर_dev->fw_minor_index);
		पूर्ण
	पूर्ण अन्यथा अणु
		hअगर_dev->fw_minor_index--;
		प्र_लिखो(index, "%d", hअगर_dev->fw_minor_index);
	पूर्ण

	/* test क्रम FW 1.3 */
	अगर (MAJOR_VERSION_REQ == 1 && hअगर_dev->fw_minor_index == 3) अणु
		स्थिर अक्षर *filename;

		अगर (IS_AR7010_DEVICE(hअगर_dev->usb_device_id->driver_info))
			filename = FIRMWARE_AR7010_1_1;
		अन्यथा
			filename = FIRMWARE_AR9271;

		/* expected fw locations:
		 * - htc_9271.fw   (stable version 1.3, depricated)
		 */
		snम_लिखो(hअगर_dev->fw_name, माप(hअगर_dev->fw_name),
			 "%s", filename);

	पूर्ण अन्यथा अगर (hअगर_dev->fw_minor_index < FIRMWARE_MINOR_IDX_MIN) अणु
		dev_err(&hअगर_dev->udev->dev, "no suitable firmware found!\n");

		वापस -ENOENT;
	पूर्ण अन्यथा अणु
		अगर (IS_AR7010_DEVICE(hअगर_dev->usb_device_id->driver_info))
			chip = "7010";
		अन्यथा
			chip = "9271";

		/* expected fw locations:
		 * - ath9k_htc/htc_9271-1.dev.0.fw (development version)
		 * - ath9k_htc/htc_9271-1.4.0.fw   (stable version)
		 */
		snम_लिखो(hअगर_dev->fw_name, माप(hअगर_dev->fw_name),
			 "%s/htc_%s-%d.%s.0.fw", HTC_FW_PATH,
			 chip, MAJOR_VERSION_REQ, index);
	पूर्ण

	ret = request_firmware_noरुको(THIS_MODULE, true, hअगर_dev->fw_name,
				      &hअगर_dev->udev->dev, GFP_KERNEL,
				      hअगर_dev, ath9k_hअगर_usb_firmware_cb);
	अगर (ret) अणु
		dev_err(&hअगर_dev->udev->dev,
			"ath9k_htc: Async request for firmware %s failed\n",
			hअगर_dev->fw_name);
		वापस ret;
	पूर्ण

	dev_info(&hअगर_dev->udev->dev, "ath9k_htc: Firmware %s requested\n",
		 hअगर_dev->fw_name);

	वापस ret;
पूर्ण

अटल व्योम ath9k_hअगर_usb_firmware_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा hअगर_device_usb *hअगर_dev = context;
	पूर्णांक ret;

	अगर (!fw) अणु
		ret = ath9k_hअगर_request_firmware(hअगर_dev, false);
		अगर (!ret)
			वापस;

		dev_err(&hअगर_dev->udev->dev,
			"ath9k_htc: Failed to get firmware %s\n",
			hअगर_dev->fw_name);
		जाओ err_fw;
	पूर्ण

	hअगर_dev->htc_handle = ath9k_htc_hw_alloc(hअगर_dev, &hअगर_usb,
						 &hअगर_dev->udev->dev);
	अगर (hअगर_dev->htc_handle == शून्य)
		जाओ err_dev_alloc;

	hअगर_dev->fw_data = fw->data;
	hअगर_dev->fw_size = fw->size;

	/* Proceed with initialization */

	ret = ath9k_hअगर_usb_dev_init(hअगर_dev);
	अगर (ret)
		जाओ err_dev_init;

	ret = ath9k_htc_hw_init(hअगर_dev->htc_handle,
				&hअगर_dev->पूर्णांकerface->dev,
				hअगर_dev->usb_device_id->idProduct,
				hअगर_dev->udev->product,
				hअगर_dev->usb_device_id->driver_info);
	अगर (ret) अणु
		ret = -EINVAL;
		जाओ err_htc_hw_init;
	पूर्ण

	release_firmware(fw);
	hअगर_dev->flags |= HIF_USB_READY;
	complete_all(&hअगर_dev->fw_करोne);

	वापस;

err_htc_hw_init:
	ath9k_hअगर_usb_dev_deinit(hअगर_dev);
err_dev_init:
	ath9k_htc_hw_मुक्त(hअगर_dev->htc_handle);
err_dev_alloc:
	release_firmware(fw);
err_fw:
	ath9k_hअगर_usb_firmware_fail(hअगर_dev);
पूर्ण

/*
 * An exact copy of the function from zd1211rw.
 */
अटल पूर्णांक send_eject_command(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = पूर्णांकerface->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	अचिन्हित अक्षर *cmd;
	u8 bulk_out_ep;
	पूर्णांक r;

	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs < 2)
		वापस -ENODEV;

	/* Find bulk out endpoपूर्णांक */
	क्रम (r = 1; r >= 0; r--) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[r].desc;
		अगर (usb_endpoपूर्णांक_dir_out(endpoपूर्णांक) &&
		    usb_endpoपूर्णांक_xfer_bulk(endpoपूर्णांक)) अणु
			bulk_out_ep = endpoपूर्णांक->bEndpoपूर्णांकAddress;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (r == -1) अणु
		dev_err(&udev->dev,
			"ath9k_htc: Could not find bulk out endpoint\n");
		वापस -ENODEV;
	पूर्ण

	cmd = kzalloc(31, GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENODEV;

	/* USB bulk command block */
	cmd[0] = 0x55;	/* bulk command signature */
	cmd[1] = 0x53;	/* bulk command signature */
	cmd[2] = 0x42;	/* bulk command signature */
	cmd[3] = 0x43;	/* bulk command signature */
	cmd[14] = 6;	/* command length */

	cmd[15] = 0x1b;	/* SCSI command: START STOP UNIT */
	cmd[19] = 0x2;	/* eject disc */

	dev_info(&udev->dev, "Ejecting storage device...\n");
	r = usb_bulk_msg(udev, usb_sndbulkpipe(udev, bulk_out_ep),
		cmd, 31, शून्य, 2 * USB_MSG_TIMEOUT);
	kमुक्त(cmd);
	अगर (r)
		वापस r;

	/* At this poपूर्णांक, the device disconnects and reconnects with the real
	 * ID numbers. */

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_hअगर_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा hअगर_device_usb *hअगर_dev;
	पूर्णांक ret = 0;

	अगर (id->driver_info == STORAGE_DEVICE)
		वापस send_eject_command(पूर्णांकerface);

	hअगर_dev = kzalloc(माप(काष्ठा hअगर_device_usb), GFP_KERNEL);
	अगर (!hअगर_dev) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	usb_get_dev(udev);

	hअगर_dev->udev = udev;
	hअगर_dev->पूर्णांकerface = पूर्णांकerface;
	hअगर_dev->usb_device_id = id;
#अगर_घोषित CONFIG_PM
	udev->reset_resume = 1;
#पूर्ण_अगर
	usb_set_पूर्णांकfdata(पूर्णांकerface, hअगर_dev);

	init_completion(&hअगर_dev->fw_करोne);

	ret = ath9k_hअगर_request_firmware(hअगर_dev, true);
	अगर (ret)
		जाओ err_fw_req;

	वापस ret;

err_fw_req:
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	kमुक्त(hअगर_dev);
	usb_put_dev(udev);
err_alloc:
	वापस ret;
पूर्ण

अटल व्योम ath9k_hअगर_usb_reboot(काष्ठा usb_device *udev)
अणु
	u32 reboot_cmd = 0xffffffff;
	व्योम *buf;
	पूर्णांक ret;

	buf = kmemdup(&reboot_cmd, 4, GFP_KERNEL);
	अगर (!buf)
		वापस;

	ret = usb_पूर्णांकerrupt_msg(udev, usb_sndपूर्णांकpipe(udev, USB_REG_OUT_PIPE),
			   buf, 4, शून्य, USB_MSG_TIMEOUT);
	अगर (ret)
		dev_err(&udev->dev, "ath9k_htc: USB reboot failed\n");

	kमुक्त(buf);
पूर्ण

अटल व्योम ath9k_hअगर_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा hअगर_device_usb *hअगर_dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	bool unplugged = (udev->state == USB_STATE_NOTATTACHED) ? true : false;

	अगर (!hअगर_dev)
		वापस;

	रुको_क्रम_completion(&hअगर_dev->fw_करोne);

	अगर (hअगर_dev->flags & HIF_USB_READY) अणु
		ath9k_htc_hw_deinit(hअगर_dev->htc_handle, unplugged);
		ath9k_hअगर_usb_dev_deinit(hअगर_dev);
		ath9k_destroy_wmi(hअगर_dev->htc_handle->drv_priv);
		ath9k_htc_hw_मुक्त(hअगर_dev->htc_handle);
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	/* If firmware was loaded we should drop it
	 * go back to first stage bootloader. */
	अगर (!unplugged && (hअगर_dev->flags & HIF_USB_READY))
		ath9k_hअगर_usb_reboot(udev);

	kमुक्त(hअगर_dev);
	dev_info(&udev->dev, "ath9k_htc: USB layer deinitialized\n");
	usb_put_dev(udev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ath9k_hअगर_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				 pm_message_t message)
अणु
	काष्ठा hअगर_device_usb *hअगर_dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	/*
	 * The device has to be set to FULLSLEEP mode in हाल no
	 * पूर्णांकerface is up.
	 */
	अगर (!(hअगर_dev->flags & HIF_USB_START))
		ath9k_htc_suspend(hअगर_dev->htc_handle);

	रुको_क्रम_completion(&hअगर_dev->fw_करोne);

	अगर (hअगर_dev->flags & HIF_USB_READY)
		ath9k_hअगर_usb_dealloc_urbs(hअगर_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_hअगर_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा hअगर_device_usb *hअगर_dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा htc_target *htc_handle = hअगर_dev->htc_handle;
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw;

	ret = ath9k_hअगर_usb_alloc_urbs(hअगर_dev);
	अगर (ret)
		वापस ret;

	अगर (hअगर_dev->flags & HIF_USB_READY) अणु
		/* request cached firmware during suspend/resume cycle */
		ret = request_firmware(&fw, hअगर_dev->fw_name,
				       &hअगर_dev->udev->dev);
		अगर (ret)
			जाओ fail_resume;

		hअगर_dev->fw_data = fw->data;
		hअगर_dev->fw_size = fw->size;
		ret = ath9k_hअगर_usb_करोwnload_fw(hअगर_dev);
		release_firmware(fw);
		अगर (ret)
			जाओ fail_resume;
	पूर्ण अन्यथा अणु
		ath9k_hअगर_usb_dealloc_urbs(hअगर_dev);
		वापस -EIO;
	पूर्ण

	mdelay(100);

	ret = ath9k_htc_resume(htc_handle);

	अगर (ret)
		जाओ fail_resume;

	वापस 0;

fail_resume:
	ath9k_hअगर_usb_dealloc_urbs(hअगर_dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा usb_driver ath9k_hअगर_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = ath9k_hअगर_usb_probe,
	.disconnect = ath9k_hअगर_usb_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = ath9k_hअगर_usb_suspend,
	.resume = ath9k_hअगर_usb_resume,
	.reset_resume = ath9k_hअगर_usb_resume,
#पूर्ण_अगर
	.id_table = ath9k_hअगर_usb_ids,
	.soft_unbind = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

पूर्णांक ath9k_hअगर_usb_init(व्योम)
अणु
	वापस usb_रेजिस्टर(&ath9k_hअगर_usb_driver);
पूर्ण

व्योम ath9k_hअगर_usb_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&ath9k_hअगर_usb_driver);
पूर्ण
